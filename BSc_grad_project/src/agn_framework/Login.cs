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
using System.IO;

namespace WindowsFormsApplication1
{
    public partial class Login : Form
    {
        private IPAddress new_ip;
        private Socket server;
        private String text_to_send = "";
        private int loc_id;
        public Preference preferences = new Preference();

        public Login()
        { 
            InitializeComponent();
        }

        private void loginHelper()
        {
            byte[] con_data = new byte[1024];
            int receive;
            String message;
            this.UseWaitCursor = true;
            try
            {
                IPEndPoint ipep = new IPEndPoint(new_ip, 9050);
                server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                server.Connect(ipep);
            }
            catch
            {
                this.UseWaitCursor = false;
                lblStatus.Text = "Unconnected";
                MessageBox.Show("Connection is could not established!",
                    "Connection Error", MessageBoxButtons.OK);
                return;
            }
            try
            {
                text_to_send = txtUserPass.Text;
                if (text_to_send == "")
                    text_to_send = "default";
                server.Send(Encoding.UTF8.GetBytes(text_to_send));
                receive = server.Receive(con_data);
                message = Encoding.UTF8.GetString(con_data, 0, receive);
                if (message.Equals("no"))
                {
                    this.UseWaitCursor = false;
                    lblStatus.Text = "Unconnected";
                    MessageBox.Show("Password is incorrect!", "Password Error", MessageBoxButtons.OK);
                    return;
                }
                else
                    loc_id = message[0];

                text_to_send = preferences.getName();
                if (text_to_send == "")
                     text_to_send = "guest";

                server.Send(Encoding.UTF8.GetBytes(text_to_send));
            }
            catch
            {
                this.UseWaitCursor = false;
                lblStatus.Text = "Unconnected";
                MessageBox.Show("Connection is lost before being established!",
                    "Connection Error", MessageBoxButtons.OK);
                return;
            }   
            this.lblStatus.Text = "Connected";
            this.Visible = false;
            Client client_form = new Client(server, new_ip, preferences, loc_id);
            client_form.ShowDialog();
            this.UseWaitCursor = false;
            lblStatus.Text = "Unconnected";
            this.Visible = true;
            Application.ExitThread();
        }
        private void butJoin_Click(object sender, EventArgs e)
        {
            try
            {
                new_ip = IPAddress.Parse(txtIP.Text);
            }
            catch (ArgumentNullException err)
            {
                MessageBox.Show("       " + err.Message  + "       ",
                    "IP Parse Error", MessageBoxButtons.OK);
                lblStatus.Text = "Unconnected";
                return;
            }
            catch (FormatException err)
            {
                MessageBox.Show("       " + err.Message + "       ",
                    "IP Parse Error", MessageBoxButtons.OK);
                lblStatus.Text = "Unconnected";
                return;
            }
            lblStatus.Text = "Connecting.....";
            Thread t = new Thread(new ThreadStart(loginHelper));
            t.SetApartmentState(ApartmentState.STA);
            t.Start();
        }
        private void butCreate_Click(object sender, EventArgs e)
        {
            this.UseWaitCursor = true;
            Server server_form = new Server(preferences, txtSerPass.Text);
            this.UseWaitCursor = false;
            this.Visible = false;
            server_form.ShowDialog();
            butCreate.Enabled = true;
            this.Visible = true;
        }

        private void Login_Load(object sender, EventArgs e)
        {
            //Preferences are read
            string filePath = "pref.pre";
            string line;

            if (File.Exists(filePath))
            {
                StreamReader file = null;
                int new_int;
                try
                {
                    file = new StreamReader(filePath);
                    line = file.ReadLine();
                    if (line != "" && line.Length < 33)
                        preferences.setName(line);

                    line = file.ReadLine();
                    if (line != "")
                    {
                        new_int = Convert.ToInt32(line);
                        if (new_int <= 5)
                            preferences.setMaxConnection(new_int);
                    }

                    line = file.ReadLine();
                    if (line != "" && line == "yes")
                        preferences.setSound(true);

                    line = file.ReadLine();
                    if (line != "" && line == "yes")
                        preferences.setCamera(true);

                    line = file.ReadLine();
                    if (line != "")
                    {
                        new_int = Convert.ToInt32(line);
                        if (new_int <= 100)
                            preferences.setMicVolume(new_int);
                    }

                    line = file.ReadLine();
                    if (line != "")
                    {
                        new_int = Convert.ToInt32(line);
                        if (new_int <= 100)
                            preferences.setSpeakerVolume(new_int);
                    }

                    line = file.ReadLine();
                    if (line != "")
                    {
                        new_int = Convert.ToInt32(line);
                        if (new_int <= 60)
                            preferences.setFramePeriod(new_int);
                    }

                    line = file.ReadLine();
                    if (line != "")
                    {
                        new_int = Convert.ToInt32(line);
                        if (new_int <= 20)
                            preferences.setRecentMax(new_int);
                    }
                }
                finally
                {
                    if (file != null)
                        file.Close();
                }
            }

            //Game Information is read

        }
        private void menuUser_Click(object sender, EventArgs e)
        {
            prefWindow pref_window = new prefWindow(preferences, 0, 0);
            pref_window.ShowDialog();
        }

        private void menuConn_Click(object sender, EventArgs e)
        {
            prefWindow pref_window = new prefWindow(preferences, 1, 0);
            pref_window.ShowDialog();
        }

        private void menuAudio_Click(object sender, EventArgs e)
        {
            prefWindow pref_window = new prefWindow(preferences, 2, 0);
            pref_window.ShowDialog();
        }

        private void menuVideo_Click(object sender, EventArgs e)
        {
            prefWindow pref_window = new prefWindow(preferences, 3, 0);
            pref_window.ShowDialog();
        }

        private void menuGeneral_Click(object sender, EventArgs e)
        {
            prefWindow pref_window = new prefWindow(preferences, 4, 0);
            pref_window.ShowDialog();
        }

        private void menuGames_Click(object sender, EventArgs e)
        {
            String[] s = new String[2];
            s[0] = "t";
            Games games_window = new Games(0, s);
            games_window.ShowDialog();
        }
    }
}
