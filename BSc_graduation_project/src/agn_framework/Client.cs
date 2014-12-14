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
using WebCam_Capture;
using System.Threading;
using System.IO;
using NAudio.Wave;

namespace WindowsFormsApplication1
{
    public partial class Client : Form
    {
        private int volume_out, volume_in;
        private Preference preferences;
        private Streaming strlib;
        private String user_name, server_name = "";
        private Socket server, serv_vid, serv_aud;
        private BackgroundWorker bwListener;
        public String text_to_send="";
        private WebCamCapture web_cam;
        private Mutex write_mutex = new Mutex();
        private int loc_id;
        private IPAddress server_ip;
        private WaveIn audio_input;
        private WaveOut audio_out;
        private bool[] is_client_active = new bool[5];
        private String[] client_names = new String[5];
        private bool is_game_started = false;
        public String incoming = "";
        private GameInterface game = null;
        public int []player_order = new int[5];
        public int porder;
        public int number_of_conn;

        public Client(Socket s0, IPAddress s_ip, Preference pre, int id)
        {
            game = new GameInterface(this, write_mutex);
            int i;
            for (i = 0; i < 5; i++)
            {
                is_client_active[i] = false;
                client_names[i] = "";
            }
            preferences = pre;
            strlib = new Streaming(preferences);
            server = s0;
            server_ip = s_ip;
            loc_id = id - 48;
            user_name = preferences.getName();
            if (user_name == "")
                user_name = "guest";

            web_cam = new WebCamCapture();

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

/*            gameArea.FSCommand += new AxShockwaveFlashObjects._IShockwaveFlashEvents_FSCommandEventHandler(fsCommand);
            gameArea.Stop();*/
        }
        private void refreshUserList()
        {
            int i;
            listUsers.Items.Clear();
            listUsers.Items.Add("server:\t" + server_name);
            for (i = 0; i < 5; i++)
                if(is_client_active[i])
                    listUsers.Items.Add("user" + i.ToString() + ":\t" + client_names[i]);
        }
        private void gameRun(object sender, DoWorkEventArgs e)
        {
            
            game.run_client();
        }
        private void startGame()
        {
            int i, p_order = 1;
            for (i = 0; i < 5; i++)
                if (is_client_active[i])
                {
                    player_order[i] = p_order;
                    p_order++;
                }

            number_of_conn = p_order;
            porder = player_order[loc_id];

            bwListener = new BackgroundWorker();
            bwListener.DoWork += new DoWorkEventHandler(gameRun);
            bwListener.RunWorkerAsync();
            is_game_started = true;
        }
        private void endGame()
        {
            if (is_game_started)
            {          
                //game = null;
                is_game_started = false;
                game.forceEnd_client();
            }
        }
        public void finishGame(String message)
        {
            if (is_game_started)
            {
                write_mutex.WaitOne();
                txtLog.AppendText(message + Environment.NewLine);
                write_mutex.ReleaseMutex();

                is_game_started = false;
            }
        }
        private void exeAdminCommand(String message)
        {
            List<string> arguments;
            int index;
            DialogResult dr = DialogResult.No;
            arguments = message.Split(' ').ToList();
            switch (arguments[0])
            {
                case "join":
                    if (arguments[1] == "s")
                        server_name = arguments[2];
                    else
                    {
                        index = Convert.ToInt32(arguments[1]);
                        client_names[index] = arguments[2];
                        is_client_active[index] = true;
                    }
                    refreshUserList();
                    break;
                
                case "leave":
                    index = Convert.ToInt32(arguments[1]);
                    is_client_active[index] = false;
                    client_names[index] = "";
                    refreshUserList();
                    break;

                case "changename":
                    if (arguments[1] == "s")
                        server_name = arguments[2];
                    else
                    {
                        index = Convert.ToInt32(arguments[1]);
                        client_names[index] = arguments[2];
                    }
                    refreshUserList();
                    break;

                case "startgame":
                    if (arguments[1] == "0001")
                        dr = MessageBox.Show(this, server_name + " wants to start Himbil game. Do you want to play?",
                            "Play Game Request", MessageBoxButtons.YesNo);

                    write_mutex.WaitOne();
                    if (dr == DialogResult.Yes)
                        text_to_send += "<a|>startapprove\n";

                    else
                        text_to_send += "<a|>startreject\n";

                    write_mutex.ReleaseMutex();
                    break;
                
                case "endgame":           
                    dr = MessageBox.Show(this, server_name + " wants to end Himbil game. Do you want to end?",
                        "End Game Request", MessageBoxButtons.YesNo);

                    write_mutex.WaitOne();
                    if (dr == DialogResult.Yes)
                        text_to_send += "<a|>endapprove\n";

                    else
                        text_to_send += "<a|>endreject\n";
                    write_mutex.ReleaseMutex();
                    break;
                case "approvestart":
                    startGame();
                    break;
                case "approveend":
                    endGame();
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
            {
                new_list[i] = new_list[i].TrimStart(to_trim);
                new_list[i] = new_list[i].TrimEnd(to_trim);

                if (new_list[i].StartsWith("<a|>"))
                    exeAdminCommand(new_list[i].Substring(4).TrimEnd(to_trim));
                else if (new_list[i].StartsWith("<c|>"))
                    exeChatCommand(new_list[i].Substring(4).TrimEnd(to_trim));
                else if (new_list[i].StartsWith("<g|>"))
                    exeGameCommand(new_list[i].Substring(4).TrimEnd(to_trim));
                
            }

            new_list.Clear();
            write_mutex.ReleaseMutex();
        }
        private void sendToServer(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                write_mutex.WaitOne();
                if (text_to_send != "")
                    try
                    {
                        server.Send(Encoding.UTF8.GetBytes(text_to_send));
                        text_to_send = "";
                    }
                    catch
                    { }
                write_mutex.ReleaseMutex();
            }
        }
        private void getFromServer()
        {
            byte[] con_data = new byte[1024];
            int receive;
            string temp;
            while (true)
            {
                receive = server.Receive(con_data);
                if (receive != 0)
                {
                    temp = Encoding.UTF8.GetString(con_data, 0, receive);
                    parseIncoming(temp);
                }
            }
        }
        private void getVideo(object sender, DoWorkEventArgs e)
        {
            byte[] con_data = new byte[1];
            byte[] data = new byte[40000];
            int receive;
            string header;

            while (true)
                try
                {
                    receive = serv_vid.Receive(con_data);
                    header = Encoding.UTF8.GetString(con_data, 0, receive);
                    receive = serv_vid.Receive(data);
                    if(receive!= 0)
                        switch (header)
                        {
                            case "0": camBox.Image = strlib.byteToImage(data); break;
                            case "1": camBox0.Image = strlib.byteToImage(data); break;
                            case "2": camBox1.Image = strlib.byteToImage(data); break;
                            case "3": camBox2.Image = strlib.byteToImage(data); break;
                            case "4": camBox3.Image = strlib.byteToImage(data); break;
                            case "5": camBox4.Image = strlib.byteToImage(data); break;
                        }
                }
                catch
                { }
        }
        private void getSound(object sender, DoWorkEventArgs e)
        {
            byte[] data = new byte[20000];
            int receive;

            while (true)
                try
                {
                    receive = serv_aud.Receive(data);
                    if (receive != 0)
                    {
                        System.IO.MemoryStream stream = new System.IO.MemoryStream(data);
                        RawSourceWaveStream rw = new RawSourceWaveStream(stream, new WaveFormat(44000, 1));
                        WaveStream ws = rw;

                        WaveChannel32 play = new WaveChannel32(ws);
                        audio_out = new WaveOut();
                        audio_out.Volume = volume_out;
                        audio_out.DeviceNumber = 0;
                        audio_out.Init(play);
                        audio_out.Play(); 
                    }
                }
                catch
                { }
        }
        private void connectServer(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                try
                {
                    IPEndPoint ipep = new IPEndPoint(server_ip, 9051);
                    serv_vid = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                    serv_vid.Connect(ipep);
                    break;
                }
                catch
                { }
            }
            while (true)
            {
                try
                {
                    IPEndPoint ipep = new IPEndPoint(server_ip, 9052);
                    serv_aud = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                    serv_aud.Connect(ipep);
                    break;
                }
                catch
                { }
            }

            bwListener = new BackgroundWorker();
            bwListener.DoWork += new DoWorkEventHandler(sendToServer);
            bwListener.RunWorkerAsync();

            bwListener = new BackgroundWorker();
            bwListener.DoWork += new DoWorkEventHandler(getVideo);
            bwListener.RunWorkerAsync();

            bwListener = new BackgroundWorker();
            bwListener.DoWork += new DoWorkEventHandler(getSound);
            bwListener.RunWorkerAsync();

            try{
                getFromServer();
            }
            catch{
                listUsers.Items.Clear();
                txtLog.AppendText("Connection with server is lost!");
                txtLog.AppendText(Environment.NewLine);
                butSend.Enabled = false;
                return;
            }
        }
        private void Client_Load(object sender, EventArgs e)
        {
            bwListener = new BackgroundWorker();
            bwListener.DoWork += new DoWorkEventHandler(connectServer);
            bwListener.RunWorkerAsync();

            web_cam.CaptureHeight = 176;
            web_cam.CaptureWidth = 218;
            web_cam.ImageCaptured += new WebCamCapture.WebCamEventHandler(ImageCaptured);
            web_cam.TimeToCapture_milliseconds = 20;
        }
        private void audioCaptured(object sender, WaveInEventArgs e)
        {
            byte[] data;
            try
            {
                data = e.Buffer;
                serv_aud.Send(data);
            }
            catch
            {  }
        }
        private void ImageCaptured(object sender, WebcamEventArgs e)
        {
            byte[] data;
            try
            {
                switch (loc_id)
                {
                    case 0: camBox0.Image = e.WebCamImage; break;
                    case 1: camBox1.Image = e.WebCamImage; break;
                    case 2: camBox2.Image = e.WebCamImage; break;
                    case 3: camBox3.Image = e.WebCamImage; break;
                    default: camBox4.Image = e.WebCamImage; break;
                }
                data = strlib.imageToByte(e.WebCamImage);
                serv_vid.Send(data);
            }
            catch
            {  }
        }
        private void butSend_Click(object sender, EventArgs e)
        {
            write_mutex.WaitOne();
            text_to_send += "<c|>" + user_name + " -> " + txtMessage.Text + "\n";
            txtMessage.Text = "";
            write_mutex.ReleaseMutex();
        }
        private void butCam_Click(object sender, EventArgs e)
        {
            try
            {
                if (butCamera.Text == "Start Camera")
                {

                    web_cam.Start(0);
                    butCamera.Text = "Stop Camera";
                }
                else
                {
                    web_cam.Stop();
                    butCamera.Text = "Start Camera";
                }
            }
            catch
            {
                butCamera.Text = "Start Camera";
                MessageBox.Show("Camera connection cannot be established!",
                    ".WebCam Error", MessageBoxButtons.OK);
            }
        }
        private void Client_FormClosed(object sender, FormClosedEventArgs e)
        {

            this.server.Close();
            web_cam.Stop();
            endGame();
            
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
 /*       private void butPlay_Click(object sender, EventArgs e)
        {
            if (is_game_opened)
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
            }
        }*/
        private void fsCommand(object sender, AxShockwaveFlashObjects._IShockwaveFlashEvents_FSCommandEvent e)
        {
 /*           String temp;
            // We only want to react if we got our command
            if (e.command == "flashMessage")
            {
                write_mutex.WaitOne();
                temp = user_name + " made a move!!" + Environment.NewLine;
                text_to_send += temp;
                gameArea.Visible = false;
                write_mutex.ReleaseMutex();
            }*/
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
            if (user_name != new_name && new_name != "")
            {
                write_mutex.WaitOne();
                temp = "<c|>" + user_name + " changed nickname as " + new_name + "\n";
                text_to_send += temp + "<a|>changename " + loc_id.ToString() + " " + new_name + "\n";
                write_mutex.ReleaseMutex();
                user_name = new_name;
            }
            refreshUserList();

            if (preferences.getCamera())
                butCamera.Enabled = true;
            else
            {
                butCamera.Enabled = false;
                web_cam.Stop();
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
            prefWindow pref_window = new prefWindow(preferences, 0, 2);
            pref_window.ShowDialog();
            checkNewPreferences();
        }
        private void menuAudio_Click(object sender, EventArgs e)
        {
            prefWindow pref_window = new prefWindow(preferences, 2, 2);
            pref_window.ShowDialog();
            checkNewPreferences();
        }
        private void menuVideo_Click(object sender, EventArgs e)
        {
            prefWindow pref_window = new prefWindow(preferences, 3, 2);
            pref_window.ShowDialog();
            checkNewPreferences();
        }
        private void menuGeneral_Click(object sender, EventArgs e)
        {
            prefWindow pref_window = new prefWindow(preferences, 4, 2);
            pref_window.ShowDialog();
            checkNewPreferences();
        }
    }
}
