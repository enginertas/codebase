using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace WindowsFormsApplication1
{
    public class Preference
    {
        private String user_name = "";     
        private int max_connection = 5;
        private bool is_camera_active = false;
        private bool is_sound_active = false;
        private int mic_volume = 100;
        private int speaker_volume = 100;
        private int frame_period = 20;
        private int recent_conn_max = 10;

        public Preference()
        {

        }
        public void setName(string name)
        {
            user_name = name;
        }
        public String getName()
        {
            return user_name;
        }
        public void setMaxConnection(int mc)
        {
            max_connection = mc;
        }
        public int getMaxConnection()
        {
            return max_connection;
        }
        public void setCamera(bool cam_open)
        {
            is_camera_active = cam_open;
        }
        public bool getCamera()
        {
            return is_camera_active;
        }
        public void setSound(bool sound_open)
        {
            is_sound_active = sound_open;
        }
        public bool getSound()
        {
            return is_sound_active;
        }
        public void setMicVolume(int volume)
        {
            mic_volume = volume;
        }
        public int getMicVolume()
        {
            return mic_volume;
        }
        public void setSpeakerVolume(int volume)
        {
            speaker_volume = volume;
        }
        public int getSpeakerVolume()
        {
            return speaker_volume;
        }
        public void setFramePeriod(int period)
        {
            frame_period = period;
        }
        public int getFramePeriod()
        {
            return frame_period;
        }
        public void setRecentMax(int max)
        {
            recent_conn_max = max;
        }
        public int getRecentMax()
        {
            return recent_conn_max;
        }
        public void writeToFile()
        {
            string filePath = "pref.pre";
            StreamWriter file = null;
            try
            {
                file = new StreamWriter(filePath);
                file.WriteLine(user_name);
                file.WriteLine(max_connection);
                if (is_sound_active)
                    file.WriteLine("yes");
                else
                    file.WriteLine("no");
                
                if (is_camera_active)
                    file.WriteLine("yes");
                else
                    file.WriteLine("no");

                file.WriteLine(mic_volume);
                file.WriteLine(speaker_volume);
                file.WriteLine(frame_period);
                file.WriteLine(recent_conn_max);
            }
            finally
            {
                if(file != null)
                    file.Close();
            }
        }
    }
}
