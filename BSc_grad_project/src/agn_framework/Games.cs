using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Games : Form
    {
        int mode;
        String[] flag;
        public Games(int m, String[] s)
        {
            mode = m;
            flag = s;
            InitializeComponent();
            if (mode == 0)
            {
                butPlay.Enabled = false;
            }
        }
        private void butAdd_Click(object sender, EventArgs e)
        {
            MessageBox.Show("We do not have a server yet! In shortest time, the games will be provided");
        }
        private void butPlay_Click(object sender, EventArgs e)
        {
            if(listGames.SelectedIndex == 0)
            {
                flag[0] = "0";
                this.Close();
            }
        }

        private void butCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
