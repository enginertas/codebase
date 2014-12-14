/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package himbilgame;
import java.io.*;
import java.net.*;
/**
 *
 * @author Engin
 */
public class agnInterface
{
    /*
    private PrintWriter out;
    private BufferedReader in;
    */

   private DataOutputStream out;
   private BufferedReader in;
   private Socket clientSocket;
    public agnInterface()
    {
        try
        {
            clientSocket = new Socket("localhost", 6007);
            out = new DataOutputStream(clientSocket.getOutputStream());
        }
        catch (UnknownHostException e)
        {
            System.out.println("Unknown host: localhost");
            System.exit(1);
        }
        catch  (IOException e)
        {
            System.out.println("No I/O");
            System.exit(1);
        }
    }
    @SuppressWarnings("empty-statement")
    public int getPlayerCount()
    {
        int a;
        InputStream input = null;
        try
        {   
            out.write("getplayercount\r".getBytes());
            input = clientSocket.getInputStream();         
            in = new BufferedReader(new InputStreamReader(input));
            a = in.read() - 48;
            return a; 
        }
        catch(Exception e)
        {
            return -1;
        }   
    }
    public int getPlayerOrder()
    {     
        int a;
        InputStream input = null;
        try
        {
            out.write("getplayerorder\r".getBytes());
            input = clientSocket.getInputStream();
            in = new BufferedReader(new InputStreamReader(input));
            a = in.read() - 48;   
            return a;
        }
        catch(Exception e)
        {
            return -1;
        }
    }
    @SuppressWarnings("empty-statement")
    public String[] getRemoteMessage()
    {
        try
        {
            InputStream input = null;
            out.write("getremotemessage\r".getBytes());

            input = clientSocket.getInputStream();
            in = new BufferedReader(new InputStreamReader(input));
            while(!in.ready());

            return in.readLine().split("\t");
        }
        catch(Exception e)
        {
            return null;
        }
    }
    public void sendMessage(String[] messages, int size)
    {
        try
        {
            int i;
            String new_message = "sendmessage\n";
            for(i = 0; i < size; i++)
                new_message += messages[i] + "\t";

            new_message = new_message.trim();
            new_message += "\r";
            out.write(new_message.getBytes());
        }
        catch(Exception e)
        {
        }
    }
    public void rejectGame(String message)
    {
        try
        {
            out.write(("reject\n" + message + "\r").getBytes());
        }
        catch(Exception e)
        {    }  
    }
    public void sendWinner(String message)
    {
        //not just for winners, also to flag game ends
        try
        {
            out.write(("winner\n" + message + "\r").getBytes());
        }
        catch(Exception e)
        {    }
    }
}
