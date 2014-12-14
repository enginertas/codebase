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
    public partial class prefWindow : Form
    {
        private Preference pref;
        public prefWindow(Preference p, int i, int m)
        {
            InitializeComponent();
            tabContainer.SelectTab(i);
            pref = p;

            if (m != 0)
            {
                boxMaxConnection.Enabled = false;
            }
        }

        private void barCaptureTime_Scroll(object sender, EventArgs e)
        {
            lblCaptureTime.Text = barCaptureTime.Value.ToString();
            butApply.Enabled = true;
        }

        private void barInputVol_Scroll(object sender, EventArgs e)
        {
            lblInputVol.Text = barInputVol.Value.ToString();
            butApply.Enabled = true;
        }

        private void barOutputVvol_Scroll(object sender, EventArgs e)
        {
            lblOutputVol.Text = barOutputVol.Value.ToString();
            butApply.Enabled = true;
        }

        private void barLastConn_Scroll(object sender, EventArgs e)
        {
            lblLastConn.Text = barLastConn.Value.ToString();
            butApply.Enabled = true;
        }

        private void prefWindow_Load(object sender, EventArgs e)
        {
            boxUser.Text = pref.getName();
            boxMaxConnection.Text = pref.getMaxConnection().ToString();
            checkSound.Checked = pref.getSound();
            checkCamera.Checked = pref.getCamera();

            barInputVol.Value = pref.getMicVolume();
            lblInputVol.Text = barInputVol.Value.ToString();
            barOutputVol.Value = pref.getSpeakerVolume();
            lblOutputVol.Text = barOutputVol.Value.ToString();
            barCaptureTime.Value = pref.getFramePeriod();
            lblCaptureTime.Text = barCaptureTime.Value.ToString();
            barLastConn.Value = pref.getRecentMax();
            lblLastConn.Text = barLastConn.Value.ToString();

            if (checkSound.Checked)
                barInputVol.Enabled = true;

            if (checkCamera.Checked)
                barCaptureTime.Enabled = true;

            butApply.Enabled = false;

        }

        private void checkSound_CheckedChanged(object sender, EventArgs e)
        {
            if (checkSound.Checked)
                barInputVol.Enabled = true;
            else
                barInputVol.Enabled = false;

            butApply.Enabled = true;
        }

        private void checkCamera_CheckedChanged(object sender, EventArgs e)
        {
            if (checkCamera.Checked)
                barCaptureTime.Enabled = true;
            else
                barCaptureTime.Enabled = false;

            butApply.Enabled = true;
        }

        private void butCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void butOK_Click(object sender, EventArgs e)
        {
            pref.setName(boxUser.Text);
            pref.setMaxConnection(Convert.ToInt32(boxMaxConnection.Text));
            pref.setSound(checkSound.Checked);
            pref.setCamera(checkCamera.Checked);
            pref.setMicVolume(barInputVol.Value );
            pref.setSpeakerVolume(barOutputVol.Value);
            pref.setFramePeriod(barCaptureTime.Value);
            pref.setRecentMax(barLastConn.Value);
            pref.writeToFile();
            this.Close();
        }

        private void butApply_Click(object sender, EventArgs e)
        {
            pref.setName(boxUser.Text);
            pref.setMaxConnection(Convert.ToInt32(boxMaxConnection.Text));
            pref.setSound(checkSound.Checked);
            pref.setCamera(checkCamera.Checked);
            pref.setMicVolume(barInputVol.Value);
            pref.setSpeakerVolume(barOutputVol.Value);
            pref.setFramePeriod(barCaptureTime.Value);
            pref.setRecentMax(barLastConn.Value);
            pref.writeToFile();
            butApply.Enabled = false;
        }

        private void boxUser_TextChanged(object sender, EventArgs e)
        {
            butApply.Enabled = true;
        }

        private void boxMaxConnection_SelectedIndexChanged(object sender, EventArgs e)
        {
            butApply.Enabled = true;
        }

    }
}
