using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using WebCam_Capture;
using System.IO;
using NAudio.Wave;

namespace WindowsFormsApplication1
{
    public partial class Server : Form
    {
        public int flag = -1;
        private int volume_out, volume_in;
        private Preference preferences;
        private string server_name;
        private Streaming strlib;
        private BackgroundWorker bwListener;
        private Socket listenerSocket, ls_vid, ls_aud;
        public String text_to_send = "";
        public int number_of_conn = 0 , max_connections = 5;
        private Socket cur_socket;
        private String cur_name = "";
        private int cur_index = 0;
        private bool mutex = true;
        private bool[] is_client_active = new bool[5];
        private Socket[] clients, sound_conn, video_conn;
        private String[] client_names;
        private String Password;
        private Mutex write_mutex = new Mutex();
        private Mutex conn_mutex = new Mutex();
        private WebCamCapture webcam;
        private WaveIn audio_input;
        private WaveOut audio_out;
        private byte[][] audios;
        private bool start_request = false, is_game_started = false, end_request = false;
        int game_count;
        public int[] player_order = new int[5];
        public String incoming = "";
        GameInterface game;
        //private bool is_game_opened = false;

        public Server(Preference pre, String pass)
        {
            game = new GameInterface(this, write_mutex);
            preferences = pre;
            strlib = new Streaming(preferences);
            max_connections = preferences.getMaxConnection();
            server_name = preferences.getName();
            if (server_name == "")
                server_name = "server";

            if (pass.Equals(""))
                pass = "default";
            Password = pass;
            
            webcam = new WebCamCapture();
            audios = new byte[6][];
            clients = new Socket[5];
            sound_conn = new Socket[5];
            video_conn = new Socket[5];
            client_names = new String[5];   

            InitializeComponent();
            if (!preferences.getCamera())
                butCamera.Enabled = false;
            
            volume_out = barOutput.Value = preferences.getSpeakerVolume();
            volume_in = barInput.Value = preferences.getMicVolume();

            if (WaveIn.DeviceCount == 0 || !preferences.getSound())
            {
                butSound.Enabled = false;
                barInput.Enabled = false;
            }
            refreshUserList();

            DirectoryInfo currentDir = new DirectoryInfo(Environment.CurrentDirectory);
            gameArea.Movie = currentDir + @"\games\tabu\tabu.swf";
/*
            gameArea.FSCommand += new AxShockwaveFlashObjects._IShockwaveFlashEvents_FSCommandEventHandler(fsCommand);
            gameArea.Stop();*/
        }
        private void refreshUserList()
        {
            int i;
            listUsers.Items.Clear();
            listUsers.Items.Add("server:\t" + server_name);
            for (i = 0; i < max_connections; i++)
                if (is_client_active[i])
                    listUsers.Items.Add("user" + i.ToString() + ":\t" + client_names[i]);
        }
        private void gameRun(object sender, DoWorkEventArgs e)
        {
            //game = new GameInterface(this, write_mutex);
            game.run_server();          
        }
        private void approveStart()
        {
            int i, p_order = 1;
            for (i = 0; i < max_connections; i++)
                if (is_client_active[i])
                {
                    player_order[i] = p_order;
                    p_order++;
                }
 
            String temp;
            bwListener = new BackgroundWorker();
            bwListener.DoWork += new DoWorkEventHandler(gameRun);
            bwListener.RunWorkerAsync();
            
            temp = server_name + " Game is started! ";
            txtLog.AppendText(temp + Environment.NewLine);
            text_to_send += "<c|>" + temp + "\n"
                + "<a|>approvestart\n";

            game_count = 0;
            start_request = false;
            is_game_started = true;

            menuPlay.Enabled = false;
            butEndGame.Visible = true;
        }
        private void rejectStart()
        {
            String temp = "Start game request is rejected!!";
            txtLog.AppendText(temp + Environment.NewLine);
            text_to_send += "<c|>" + temp + "\n";

            game_count = 0;
            start_request = false;

            menuPlay.Enabled = true;
            butEndGame.Visible = false;
        }
        private void approveEnd()
        {
            if (is_game_started)
            {
                game.forceEnd_server();
                String temp = "It is decided to end game!!";
                txtLog.AppendText(temp + Environment.NewLine);
                text_to_send += "<c|>" + temp + "\n"
                    + "<a|>approveend\n";

                game_count = 0;
                end_request = false;
                is_game_started = false;

                menuPlay.Enabled = true;
                butEndGame.Visible = false;
            }
        }
        public void finishGame(String message)
        {
            if (is_game_started)
            {
                write_mutex.WaitOne();
                txtLog.AppendText(message + Environment.NewLine);
                write_mutex.ReleaseMutex();

                game_count = 0;
                end_request = false;
                is_game_started = false;

                menuPlay.Enabled = true;
                butEndGame.Visible = false;
            }
        }
        private void rejectEnd()
        {
            String temp = "End game request is rejected!!";
            txtLog.AppendText(temp + Environment.NewLine);
            text_to_send += "<c|>" + temp + "\n";

            game_count = 0;
            end_request = false;

            menuPlay.Enabled = false;
            butEndGame.Visible = true;
        }
        private void exeAdminCommand(String message)
        {
            List<string> arguments;
            int index;
            arguments = message.Split(' ').ToList();
            switch (arguments[0])
            {
                case "changename":
                    index = Convert.ToInt32(arguments[1]);
                    client_names[index] = arguments[2];
                    refreshUserList();
                    break;
                case "startapprove":
                    write_mutex.WaitOne();
                    game_count++;
                    if(game_count == number_of_conn && start_request)
                        approveStart();
                    write_mutex.ReleaseMutex();
                    break;
                case "startreject":
                    write_mutex.WaitOne();
                    if(start_request)
                        rejectStart();
                    write_mutex.ReleaseMutex();
                    break;
                case "endapprove":
                    write_mutex.WaitOne();
                    game_count++;
                    if (game_count == number_of_conn && end_request)
                        approveEnd();
                    write_mutex.ReleaseMutex();
                    break;
                case "endreject":
                    write_mutex.WaitOne();
                    if (end_request)
                        rejectEnd();
                    write_mutex.ReleaseMutex();
                    break;
            }
        }
        private void exeChatCommand(String message)
        {
            write_mutex.WaitOne();
            txtLog.AppendText(message + Environment.NewLine);
            write_mutex.ReleaseMutex();
        }
        private void exeGameCommand(String message)
        {
            write_mutex.WaitOne();
            incoming += message;
            write_mutex.ReleaseMutex();
        }
        private void parseIncoming(String message)
        {
            int i, list_size = 0;
            List<String> new_list;
            char[] to_trim = new char[2];
            to_trim[0] = '\n';
            to_trim[1] = ' ';

            new_list = message.Split('\n').ToList();
            list_size = new_list.Count();
            write_mutex.WaitOne();

            for (i = 0; i < list_size; i++)
                if (new_list[i].StartsWith("<a|>"))
                    exeAdminCommand(new_list[i].Substring(4).TrimEnd(to_trim));
                else if (new_list[i].StartsWith("<c|>"))
                    exeChatCommand(new_list[i].Substring(4).TrimEnd(to_trim));
                else if (new_list[i].StartsWith("<g|>"))
                    exeGameCommand(new_list[i].Substring(4).TrimEnd(to_trim));

            new_list.Clear();
            write_mutex.ReleaseMutex();
        }
        private void listenClient(object sender, DoWorkEventArgs e)
        {
            byte[] con_data = new byte[1000];
            int receive, i, own_session = cur_index;
            Socket own_socket = cur_socket;
            String own_name = cur_name, temp = "";
            mutex = false;

            /************** Send the user list at configuration *************/
            try
            {
                conn_mutex.WaitOne();
                temp = "<c|>--- Connected with " + server_name + "\n";
                temp += "<a|>join s " + server_name + "\n";
                for (i = 0; i < max_connections; i++)
                    if (is_client_active[i])
                        temp += "<a|>join " + i.ToString() + " " + client_names[i] + "\n";
                conn_mutex.ReleaseMutex();
                own_socket.Send(Encoding.UTF8.GetBytes(temp));
            }
            catch
            {
                write_mutex.WaitOne();
                temp = "--- Connection is lost with " + client_names[own_session] + "!!";
                txtLog.AppendText(temp + Environment.NewLine);
                text_to_send += "<c|>" + temp + "\n"
                    + "<a|>leave " + own_session.ToString() + "\n";

                approveEnd();

                write_mutex.ReleaseMutex();

                conn_mutex.WaitOne();
                number_of_conn--;
                is_client_active[own_session] = false;
                refreshUserList();
                conn_mutex.ReleaseMutex();
                return;
            }
            /****************** Get Remote Activities *************/
            while (true)
            {
                try
                {
                    receive = own_socket.Receive(con_data);
                    if (receive != 0)
                    {
                        temp = Encoding.UTF8.GetString(con_data, 0, receive); 
                        write_mutex.WaitOne();
                        parseIncoming(temp);        //first virtue
                        text_to_send += temp;       //then forward to clients
                        write_mutex.ReleaseMutex();
                    }
                }
                catch
                {
                    write_mutex.WaitOne();
                    temp = "--- Connection is lost with " + client_names[own_session] + "!!";
                    txtLog.AppendText(temp + Environment.NewLine);
                    text_to_send += "<c|>" + temp + "\n" 
                        + "<a|>leave " + own_session.ToString() + "\n";

                    approveEnd();

                    write_mutex.ReleaseMutex();

                    conn_mutex.WaitOne();
                    number_of_conn--;
                    is_client_active[own_session] = false;
                    refreshUserList();
                    conn_mutex.ReleaseMutex();
                    return;
                }
            }
        }
        private void deliver(object sender, DoWorkEventArgs e)
        {
            int i;
            while (true)
            {
                write_mutex.WaitOne();
                for (i = 0; i < max_connections; i++)
                    if (is_client_active[i])
                        try
                        {
                            if (text_to_send != "")
                                clients[i].Send(Encoding.UTF8.GetBytes(text_to_send));
                        }
                        catch
                        { }
                text_to_send = "";
                write_mutex.ReleaseMutex();
            }
        }
        private void StartToListen(object sender, DoWorkEventArgs e)
        {
            int receive, index;
            byte[] con_data = new byte[1024];
            String temp = "";

            for (index = 0; index < max_connections; index++)
                is_client_active[index] = false;

            listenerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            listenerSocket.Bind(new IPEndPoint(IPAddress.Any, 9050));
            listenerSocket.Listen(10);

            ls_vid = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            ls_vid.Bind(new IPEndPoint(IPAddress.Any, 9051));
            ls_vid.Listen(10);

            ls_aud = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            ls_aud.Bind(new IPEndPoint(IPAddress.Any, 9052));
            ls_aud.Listen(10);

            while (true)
                if (number_of_conn < max_connections)
                {
                    try
                    {
                        cur_socket = this.listenerSocket.Accept();
                        receive = cur_socket.Receive(con_data);
                        temp = Encoding.UTF8.GetString(con_data, 0, receive);

                        /********* Determining a location for new connection ****/
                        for (index = 0; index < max_connections; index++)
                            if (!is_client_active[index])
                                break;

                        //txtLog.AppendText(Password + Environment.NewLine);
                        /************ Password Check **********/
                        if (temp.Equals(Password))      //send location of player if correct
                            cur_socket.Send(Encoding.UTF8.GetBytes(index.ToString()));
                        else
                        {
                            cur_socket.Send(Encoding.UTF8.GetBytes("no"));
                            cur_socket.Close();             //deny if password is incorrect
                            continue;
                        }
                        receive = cur_socket.Receive(con_data);
                    }
                    catch
                    {
                        continue;
                    }
                    /*********** User Name Acquirance *******/
                    cur_index = index;
                    client_names[index] = cur_name = Encoding.UTF8.GetString(con_data, 0, receive);
                    clients[index] = cur_socket;

                    /******* Setting Index and Number of Connections ******/
                    conn_mutex.WaitOne();
                    number_of_conn++;
                    is_client_active[index] = true;
                    refreshUserList();
                    conn_mutex.ReleaseMutex();
                    cur_index = index;

                    /*********** Status Update **********/
                    write_mutex.WaitOne();
                    temp = "--- Connected with " + cur_name;
                    txtLog.AppendText(temp + Environment.NewLine);
                    text_to_send += "<c|>" + temp + "\n"
                        + "<a|>join " + index.ToString() + " " + client_names[index] + "\n";
                    
                    write_mutex.ReleaseMutex();

                    /******** New Communication Channels Opening ******/
                    bwListener = new BackgroundWorker();
                    bwListener.DoWork += new DoWorkEventHandler(listenClient);
                    bwListener.RunWorkerAsync();
                    while (mutex) ;
                    mutex = true;

                    bwListener = new BackgroundWorker();
                    bwListener.DoWork += new DoWorkEventHandler(getVideo);
                    bwListener.RunWorkerAsync();
                    while (mutex) ;
                    mutex = true;

                    bwListener = new BackgroundWorker();
                    bwListener.DoWork += new DoWorkEventHandler(getSound);
                    bwListener.RunWorkerAsync();
                    while (mutex) ;
                    mutex = true;
                }
        }
        private void getVideo(object sender, DoWorkEventArgs e)
        {
            int session_id = cur_index, receive;
            mutex = false;

            byte[] data = new byte[20000];
            video_conn[session_id] = ls_vid.Accept();

            while (is_client_active[session_id])
            {
                try
                {
                    receive = video_conn[session_id].Receive(data);
                    if (receive != 0)
                        switch (session_id)
                        {
                            case 0: camBox0.Image = strlib.byteToImage(data); break;
                            case 1: camBox1.Image = strlib.byteToImage(data); break;
                            case 2: camBox2.Image = strlib.byteToImage(data); break;
                            case 3: camBox3.Image = strlib.byteToImage(data); break;
                            case 4: camBox4.Image = strlib.byteToImage(data); break;
                        }
                }
                catch
                { }
            }
        }
        private void getSound(object sender, DoWorkEventArgs e)
        {
            int session_id = cur_index, receive;
            mutex = false;

            int aud = session_id + 1;
            byte[] data = new byte[10000];
            sound_conn[session_id] = ls_aud.Accept();

            while (is_client_active[session_id])
            {
                try
                {
                    receive = sound_conn[session_id].Receive(data);
                    if (receive != 0)
                    {
                        audios[aud] = data;
                        System.IO.MemoryStream stream = new System.IO.MemoryStream(data);
                        RawSourceWaveStream rw = new RawSourceWaveStream(stream, new WaveFormat(44000, 1));
                        WaveStream ws = rw;

                        WaveChannel32 play = new WaveChannel32(ws);
                        audio_out = new WaveOut();
                        audio_out.DeviceNumber = 0;
                        audio_out.Volume = volume_out;
                        audio_out.Init(play);
                        audio_out.Play();
                    }
                }
                catch { }
            }
        }
        private void Form2_Load(object sender, EventArgs e)
        {
            bwListener = new BackgroundWorker();
            bwListener.DoWork += new DoWorkEventHandler(StartToListen);
            bwListener.RunWorkerAsync();

            bwListener = new BackgroundWorker();
            bwListener.DoWork += new DoWorkEventHandler(deliver);
            bwListener.RunWorkerAsync();

            webcam.CaptureHeight = 176;
            webcam.CaptureWidth = 218;
            webcam.TimeToCapture_milliseconds = 20;
            webcam.ImageCaptured += new WebCamCapture.WebCamEventHandler(webcam_ImageCaptured);
        }
        private void butCamera_Click(object sender, EventArgs e)
        {
            try
            {
                if (butCamera.Text == "Start Camera")
                {
                    webcam.Start(0);
                    butCamera.Text = "Stop Camera";
                }
                else
                {
                    webcam.Stop();
                    butCamera.Text = "Start Camera";
                }
            }
            catch
            {
                butCamera.Text = "Start Camera";
                MessageBox.Show("Camera connection cannot be established!",
                    "WebCam Error", MessageBoxButtons.OK);
            }
        }
        private void butSend_Click(object sender, EventArgs e)
        {
            String temp;
            write_mutex.WaitOne();
            temp = server_name + " -> " + txtMessage.Text;
            txtLog.AppendText(temp + Environment.NewLine);
            text_to_send += "<c|>" + temp + "\n";
            txtMessage.Text = "";         
            write_mutex.ReleaseMutex();
        }
        private void webcam_ImageCaptured(object source, WebcamEventArgs e)
        {
            camBox.Image = e.WebCamImage;
            webcamSend();

        }
        private void webcamSend()
        {
            int i, j;
            byte[] data;

            for (i = 0; i < max_connections; i++)
                if (is_client_active[i])
                    for (j = 0; j < 6; j++)
                        if (i != (j - 1))
                        {
                            try
                            {
                                switch (j)
                                {
                                    case 0: data = strlib.imageToByte(camBox.Image); break;
                                    case 1: data = strlib.imageToByte(camBox0.Image); break;
                                    case 2: data = strlib.imageToByte(camBox1.Image); break;
                                    case 3: data = strlib.imageToByte(camBox2.Image); break;
                                    case 4: data = strlib.imageToByte(camBox3.Image); break;
                                    default: data = strlib.imageToByte(camBox4.Image); break;
                                }
                                if (data.Length != 0)
                                {
                                    video_conn[i].Send(Encoding.UTF8.GetBytes(j.ToString()));
                                    video_conn[i].Send(data);
                                }
                            }
                            catch
                            { }
                        }
        }
        private void audioCaptured(object sender, WaveInEventArgs e)
        {
            int i, j;
            audios[0] = e.Buffer;
            for (i = 0; i < max_connections; i++)
                if (is_client_active[i])
                    for (j = 0; j < 6; j++)
                        if (i != (j - 1))
                            try
                            {
                                if (audios[j] != null)
                                {
                                        sound_conn[i].Send(audios[j]);
                                }
                            }
                            catch
                            { }

             for (j = 0; j < 6; j++)
               audios[j] = null;
        }
        private void butSound_Click(object sender, EventArgs e)
        {
            try
            {
                if (butSound.Text == "Start Microphone")
                {
                    audio_input = new WaveIn();
                    audio_input.DeviceNumber = 0;
                    audio_input.DataAvailable += audioCaptured;
                    audio_input.WaveFormat = new WaveFormat(44000, 1);
                    audio_input.StartRecording();
                    
                    butSound.Text = "Stop Microphone";

                    //input volume adjustment
                }
                else
                {
                    audio_input.StopRecording();
                    butSound.Text = "Start Microphone";
                }
            }
            catch
            {
                MessageBox.Show("Sound Device Cannot be Started",
                    "Sound Error", MessageBoxButtons.OK);
                butSound.Text = "Start Microphone";
            }
        }
        private void Form_Closed(object sender, FormClosedEventArgs e)
        {
            int i;
            conn_mutex.WaitOne();
            for (i = 0; i < max_connections; i++)
                if (is_client_active[i])
                {
                    try
                    {
                        clients[i].Close();
                    }
                    catch
                    { }
                    try
                    {
                        sound_conn[i].Close();
                    }
                    catch
                    { }
                    try
                    {
                        video_conn[i].Close();
                    }
                    catch
                    { }
                }
            conn_mutex.ReleaseMutex();
            webcam.Stop();
            approveEnd();
            if (butSound.Text == "Stop Microphone")
                audio_input.StopRecording();
        }
        private void butPlay_Click(object sender, EventArgs e)
        {
/*            if (is_game_opened)
            {
                gameArea.Stop();
                butPlay.Text = "Start Game";
                is_game_opened = false;
            }
            else
            {
                gameArea.Stop();
                gameArea.Play();
                butPlay.Text = "End Game";
                is_game_opened = true;
            }*/
        }
        private void fsCommand(object sender, AxShockwaveFlashObjects._IShockwaveFlashEvents_FSCommandEvent e)
        {
            String temp;
            // We only want to react if we got our command
            if (e.command == "flashMessage")
            {
                write_mutex.WaitOne();
                temp = server_name + " made a move!!" + Environment.NewLine;
                txtLog.AppendText(temp);
                text_to_send += temp;
                gameArea.Visible = false;
                write_mutex.ReleaseMutex();
            }
        }
        private void butSendFlash_Click(object sender, EventArgs e)
        {
            gameArea.SetVariable("CSharpMessage", "Hi Flash!");
        }
        private void barInput_Scroll(object sender, EventArgs e)
        {
            volume_in = barInput.Value;
        }
        private void barOutput_Scroll(object sender, EventArgs e)
        {
            volume_out = barOutput.Value;
        }
        private void checkNewPreferences()
        {
            String temp, new_name = preferences.getName();
            if (server_name != new_name && new_name != "")
            {
                write_mutex.WaitOne();
                temp = server_name + " changed nickname as " + new_name;
                txtLog.AppendText(temp + Environment.NewLine);
                text_to_send += "<c|>" + temp + "\n"
                    + "<a|>changename s "+ new_name + "\n";
                write_mutex.ReleaseMutex();
                server_name = new_name;
            }
            refreshUserList();

            if (preferences.getCamera())
                butCamera.Enabled = true;
            else
            {
                butCamera.Enabled = false;
                webcam.Stop();
                butCamera.Text = "Start Camera";
            }

            if (preferences.getSound() && WaveIn.DeviceCount > 0)
            {
                butSound.Enabled = true;
                barInput.Enabled = true;
            }
            else
            {
                butSound.Enabled = false;
                barInput.Enabled = false;
                if (butSound.Text == "Stop Microphone")
                {
                    audio_input.StopRecording();
                    butSound.Text = "Start Microphone";
                }
            }
        }
        private void menuUser_Click(object sender, EventArgs e)
        {
            prefWindow pref_window = new prefWindow(preferences, 0, 1);
            pref_window.ShowDialog();
            checkNewPreferences();
        }
        private void menuAudio_Click(object sender, EventArgs e)
        {
            prefWindow pref_window = new prefWindow(preferences, 2, 1);
            pref_window.ShowDialog();
            checkNewPreferences();
        }
        private void menuVideo_Click(object sender, EventArgs e)
        {
            prefWindow pref_window = new prefWindow(preferences, 3, 1);
            pref_window.ShowDialog();
            checkNewPreferences();
        }
        private void menuGeneral_Click(object sender, EventArgs e)
        {
            prefWindow pref_window = new prefWindow(preferences, 4, 1);
            pref_window.ShowDialog();
            checkNewPreferences();
        }

        private void menuPlay_Click(object sender, EventArgs e)
        {
            String[] s = new String[2];
            s[0] = "t";
            Games games_window = new Games(1, s);
            games_window.ShowDialog();

            if (s[0] == "0")
            {
                startGameRequest();
                menuPlay.Enabled = false;
                butEndGame.Visible = false;
            }
        }
        private void butEndGame_Click(object sender, EventArgs e)
        {
            endGameRequest();
            menuPlay.Enabled = false;
            butEndGame.Visible = false;
        }
        private void startGameRequest()
        {
            String temp;
            write_mutex.WaitOne();
            temp = server_name + " requests to play the game Himbil! Please response! ";
            txtLog.AppendText(temp + Environment.NewLine);
            text_to_send += "<c|>" + temp + "\n"
                + "<a|>startgame 0001\n";
            game_count = 0;
            start_request = true;
            write_mutex.ReleaseMutex();
        }
        private void endGameRequest()
        {
            if (is_game_started)
            {
                String temp;
                write_mutex.WaitOne();
                temp = server_name + " requests to end the game Himbil! Please response! ";
                txtLog.AppendText(temp + Environment.NewLine);
                text_to_send += "<c|>" + temp + "\n"
                    + "<a|>endgame\n";
                game_count = 0;
                end_request = true;
                write_mutex.ReleaseMutex();
            }
        }
    }
}