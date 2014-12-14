using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace WindowsFormsApplication1
{
    class GameInterface
    {
        private Socket listenerSocket, gameSocket;
        private Process proc;
        private Mutex write_mutex;
        private Server sender_s;
        private Client sender_c;
        private bool is_working = true;
        public GameInterface(Server frm, Mutex mut)
        {
            write_mutex = mut;
            sender_s = frm;
        }
        public GameInterface(Client frm, Mutex mut)
        {
            write_mutex = mut;
            sender_c = frm;
        }
        public void run_server()
        {
            listenerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            listenerSocket.Bind(new IPEndPoint(IPAddress.Parse("127.0.0.1"), 6007));
            listenerSocket.Listen(10);

            try
            {
                proc = new Process();

                DirectoryInfo currentDir = new DirectoryInfo(Environment.CurrentDirectory);
                proc.StartInfo.WorkingDirectory = currentDir.FullName + @"\games\himbil\dist\";
                proc.StartInfo.FileName = "java";
                proc.StartInfo.Arguments = "-jar himbilGame.jar";
                proc.StartInfo.CreateNoWindow = false;               
                proc.Start();
                proc.WaitForExit(500);
                gameSocket = listenerSocket.Accept();
                parseIncoming_server();
            }
            catch (Exception)
            {
                sender_s.finishGame("java classpath problem occured");
                //MessageBox.Show(ex.Message);
            }
           
        }
        public void run_client()
        {
            listenerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            listenerSocket.Bind(new IPEndPoint(IPAddress.Parse("127.0.0.1"), 6007));
            listenerSocket.Listen(10);

            try
            {
                proc = new Process();

                DirectoryInfo currentDir = new DirectoryInfo(Environment.CurrentDirectory);
                proc.StartInfo.WorkingDirectory = currentDir.FullName + @"\games\himbil\dist\";
                proc.StartInfo.FileName = "java";
                proc.StartInfo.Arguments = "-jar himbilGame.jar";
                proc.StartInfo.CreateNoWindow = false;
                proc.Start();
                proc.WaitForExit(500);
                gameSocket = listenerSocket.Accept();
                parseIncoming_client();
            }

            catch (Exception)
            {
                sender_s.finishGame("java classpath problem occured");
                //MessageBox.Show(ex.Message);
            }
        }
        public void sendFromRemote_server()
        {
            //code to write
        }
        public void sendFromRemote_client()
        {
            //code to write
        }
        private void executeCommand_server(String message)
        {
            List<String> arguments = message.Split('\n').ToList();
            int i, size = arguments.Count();

            switch (arguments[0])
            {
                case "getplayercount":
                    gameSocket.Send(Encoding.UTF8.GetBytes((sender_s.number_of_conn + 1).ToString()));
                    break;
                case "getplayerorder":
                    gameSocket.Send(Encoding.UTF8.GetBytes("0"));
                    break;
                case "reject":
                    sender_s.finishGame(arguments[1]);
                    is_working = false;
                    break;
                case "getremotemessage":
                    while(sender_s.incoming.Equals("")) ;
                    write_mutex.WaitOne();
                    gameSocket.Send(Encoding.UTF8.GetBytes(sender_s.incoming + "\n"));
                    sender_s.incoming = "";
                    write_mutex.ReleaseMutex(); 
                    break;
                case "sendmessage":
                    write_mutex.WaitOne();

                    String new_st = "<g|>";
                    for (i = 1; i < size; i++)
                        new_st += arguments[i] + "\t";
                    
                    sender_s.text_to_send += new_st+ "\n";
                    write_mutex.ReleaseMutex();
                    break;

                case "winner":
                    write_mutex.WaitOne();
                    sender_s.text_to_send += "<g|>winner " + arguments[1] + "\n";
                    write_mutex.ReleaseMutex();
                    break;
            }
        }
        private void executeCommand_client(String message)
        {
            List<String> arguments = message.Split('\n').ToList();
            int i, size = arguments.Count();

            switch (arguments[0])
            {
                case "getplayercount":
                    gameSocket.Send(Encoding.UTF8.GetBytes(sender_c.number_of_conn.ToString()));
                    break;
                case "getplayerorder":
                    gameSocket.Send(Encoding.UTF8.GetBytes(sender_c.porder.ToString()));
                    break;
                case "reject":
                    sender_c.finishGame(arguments[1]);
                    is_working = false;
                    break;
                case "getremotemessage":
                    while (sender_c.incoming.Equals(""));
                    write_mutex.WaitOne();
                    gameSocket.Send(Encoding.UTF8.GetBytes(sender_c.incoming + "\n"));
                    sender_c.incoming = "";
                    write_mutex.ReleaseMutex();
                    break;
                case "sendmessage":
                    write_mutex.WaitOne();

                    String new_st = "<g|>";
                    for (i = 1; i < size; i++)
                        new_st += arguments[i] + "\t";
                    
                    sender_c.text_to_send += new_st + "\n";

                    write_mutex.ReleaseMutex();
                    break;

                case "winner":
                    write_mutex.WaitOne();
                    sender_c.text_to_send += "<g|>winner " + arguments[1] + "\n";
                    write_mutex.ReleaseMutex();
                    break;
            }
        }
        private void parseIncoming_server()
        {
            byte[] con_data = new byte[1000];
            String temp;
            List<String> messages;
            int receive, i, size;
            while(is_working)
            {   
                //code to write when it is end
                receive = gameSocket.Receive(con_data);
                if (receive != 0)
                {
                    temp = Encoding.UTF8.GetString(con_data, 0, receive);                    
                    messages = temp.Split('\r').ToList();
                    size = messages.Count();

                    for (i = 0; i < size; i++)
                        executeCommand_server(messages[i]);

                    messages.Clear();
                }
            }
        }
        private void parseIncoming_client()
        {
            byte[] con_data = new byte[1000];
            String temp;
            List<String> messages;
            int receive, i, size;
            while (is_working)
            {
                //code to write when it is end
                receive = gameSocket.Receive(con_data);
                if (receive != 0)
                {
                    temp = Encoding.UTF8.GetString(con_data, 0, receive);
                    messages = temp.Split('\r').ToList();
                    size = messages.Count();

                    for (i = 0; i < size; i++)
                        executeCommand_client(messages[i]);

                    messages.Clear();
                }
            }
        }
        public void forceEnd_server()
        {
//            gameSocket.Shutdown(SocketShutdown.Both);
            //code to write
            is_working = false;
            proc.Close();
        }
        public void forceEnd_client()
        {
//            gameSocket.Shutdown(SocketShutdown.Both);
            //code to write
            is_working = false;
            proc.Close();
        }

    }
}
