namespace WindowsFormsApplication1
{
    partial class prefWindow
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.tabContainer = new System.Windows.Forms.TabControl();
            this.tabUser = new System.Windows.Forms.TabPage();
            this.label4 = new System.Windows.Forms.Label();
            this.butDefault = new System.Windows.Forms.Button();
            this.butUpdate = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.boxUser = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.tabConnection = new System.Windows.Forms.TabPage();
            this.label6 = new System.Windows.Forms.Label();
            this.boxMaxConnection = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.tabAudio = new System.Windows.Forms.TabPage();
            this.lblOutputVol = new System.Windows.Forms.Label();
            this.lblInputVol = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.barOutputVol = new System.Windows.Forms.TrackBar();
            this.barInputVol = new System.Windows.Forms.TrackBar();
            this.label8 = new System.Windows.Forms.Label();
            this.checkSound = new System.Windows.Forms.CheckBox();
            this.label7 = new System.Windows.Forms.Label();
            this.tabVideo = new System.Windows.Forms.TabPage();
            this.label12 = new System.Windows.Forms.Label();
            this.lblCaptureTime = new System.Windows.Forms.Label();
            this.barCaptureTime = new System.Windows.Forms.TrackBar();
            this.label10 = new System.Windows.Forms.Label();
            this.checkCamera = new System.Windows.Forms.CheckBox();
            this.label11 = new System.Windows.Forms.Label();
            this.tabGeneral = new System.Windows.Forms.TabPage();
            this.label14 = new System.Windows.Forms.Label();
            this.lblLastConn = new System.Windows.Forms.Label();
            this.barLastConn = new System.Windows.Forms.TrackBar();
            this.label13 = new System.Windows.Forms.Label();
            this.butOK = new System.Windows.Forms.Button();
            this.butCancel = new System.Windows.Forms.Button();
            this.butApply = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.tabContainer.SuspendLayout();
            this.tabUser.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.tabConnection.SuspendLayout();
            this.tabAudio.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.barOutputVol)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.barInputVol)).BeginInit();
            this.tabVideo.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.barCaptureTime)).BeginInit();
            this.tabGeneral.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.barLastConn)).BeginInit();
            this.SuspendLayout();
            // 
            // tabContainer
            // 
            this.tabContainer.Controls.Add(this.tabUser);
            this.tabContainer.Controls.Add(this.tabConnection);
            this.tabContainer.Controls.Add(this.tabAudio);
            this.tabContainer.Controls.Add(this.tabVideo);
            this.tabContainer.Controls.Add(this.tabGeneral);
            this.tabContainer.Location = new System.Drawing.Point(12, 12);
            this.tabContainer.Name = "tabContainer";
            this.tabContainer.SelectedIndex = 0;
            this.tabContainer.Size = new System.Drawing.Size(430, 325);
            this.tabContainer.TabIndex = 0;
            // 
            // tabUser
            // 
            this.tabUser.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.tabUser.Controls.Add(this.label4);
            this.tabUser.Controls.Add(this.butDefault);
            this.tabUser.Controls.Add(this.butUpdate);
            this.tabUser.Controls.Add(this.pictureBox1);
            this.tabUser.Controls.Add(this.label2);
            this.tabUser.Controls.Add(this.label1);
            this.tabUser.Controls.Add(this.boxUser);
            this.tabUser.Controls.Add(this.label3);
            this.tabUser.Location = new System.Drawing.Point(4, 22);
            this.tabUser.Name = "tabUser";
            this.tabUser.Padding = new System.Windows.Forms.Padding(3);
            this.tabUser.Size = new System.Drawing.Size(422, 299);
            this.tabUser.TabIndex = 0;
            this.tabUser.Text = "User";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(244, 145);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(117, 13);
            this.label4.TabIndex = 22;
            this.label4.Text = "converted to 100 x 120";
            // 
            // butDefault
            // 
            this.butDefault.Location = new System.Drawing.Point(247, 200);
            this.butDefault.Name = "butDefault";
            this.butDefault.Size = new System.Drawing.Size(114, 24);
            this.butDefault.TabIndex = 2;
            this.butDefault.Text = "Return To Default";
            this.butDefault.UseVisualStyleBackColor = true;
            // 
            // butUpdate
            // 
            this.butUpdate.Location = new System.Drawing.Point(247, 170);
            this.butUpdate.Name = "butUpdate";
            this.butUpdate.Size = new System.Drawing.Size(114, 24);
            this.butUpdate.TabIndex = 1;
            this.butUpdate.Text = "Update";
            this.butUpdate.UseVisualStyleBackColor = true;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(105, 104);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(100, 120);
            this.pictureBox1.TabIndex = 21;
            this.pictureBox1.TabStop = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(223, 53);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(124, 13);
            this.label2.TabIndex = 20;
            this.label2.Text = "max 32 characters (ascii)";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label1.Location = new System.Drawing.Point(53, 104);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 18);
            this.label1.TabIndex = 19;
            this.label1.Text = "Photo:";
            // 
            // boxUser
            // 
            this.boxUser.Location = new System.Drawing.Point(105, 30);
            this.boxUser.Name = "boxUser";
            this.boxUser.Size = new System.Drawing.Size(242, 20);
            this.boxUser.TabIndex = 0;
            this.boxUser.TextChanged += new System.EventHandler(this.boxUser_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label3.Location = new System.Drawing.Point(23, 30);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(76, 18);
            this.label3.TabIndex = 17;
            this.label3.Text = "User Name:";
            // 
            // tabConnection
            // 
            this.tabConnection.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.tabConnection.Controls.Add(this.label6);
            this.tabConnection.Controls.Add(this.boxMaxConnection);
            this.tabConnection.Controls.Add(this.label5);
            this.tabConnection.Location = new System.Drawing.Point(4, 22);
            this.tabConnection.Name = "tabConnection";
            this.tabConnection.Padding = new System.Windows.Forms.Padding(3);
            this.tabConnection.Size = new System.Drawing.Size(422, 299);
            this.tabConnection.TabIndex = 1;
            this.tabConnection.Text = "Connection";
            // 
            // label6
            // 
            this.label6.Location = new System.Drawing.Point(192, 95);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(184, 28);
            this.label6.TabIndex = 19;
            this.label6.Text = "While creating a conversation, it sets the maximum incoming clients.";
            // 
            // boxMaxConnection
            // 
            this.boxMaxConnection.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.boxMaxConnection.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5"});
            this.boxMaxConnection.Location = new System.Drawing.Point(211, 53);
            this.boxMaxConnection.Name = "boxMaxConnection";
            this.boxMaxConnection.Size = new System.Drawing.Size(41, 21);
            this.boxMaxConnection.TabIndex = 3;
            this.boxMaxConnection.SelectedIndexChanged += new System.EventHandler(this.boxMaxConnection_SelectedIndexChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label5.Location = new System.Drawing.Point(33, 53);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(162, 18);
            this.label5.TabIndex = 18;
            this.label5.Text = "Maximum Clients Allowed:";
            // 
            // tabAudio
            // 
            this.tabAudio.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.tabAudio.Controls.Add(this.lblOutputVol);
            this.tabAudio.Controls.Add(this.lblInputVol);
            this.tabAudio.Controls.Add(this.label9);
            this.tabAudio.Controls.Add(this.barOutputVol);
            this.tabAudio.Controls.Add(this.barInputVol);
            this.tabAudio.Controls.Add(this.label8);
            this.tabAudio.Controls.Add(this.checkSound);
            this.tabAudio.Controls.Add(this.label7);
            this.tabAudio.Location = new System.Drawing.Point(4, 22);
            this.tabAudio.Name = "tabAudio";
            this.tabAudio.Size = new System.Drawing.Size(422, 299);
            this.tabAudio.TabIndex = 2;
            this.tabAudio.Text = "Audio";
            // 
            // lblOutputVol
            // 
            this.lblOutputVol.AutoSize = true;
            this.lblOutputVol.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.lblOutputVol.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.lblOutputVol.Location = new System.Drawing.Point(334, 177);
            this.lblOutputVol.Name = "lblOutputVol";
            this.lblOutputVol.Size = new System.Drawing.Size(31, 20);
            this.lblOutputVol.TabIndex = 24;
            this.lblOutputVol.Text = "100";
            // 
            // lblInputVol
            // 
            this.lblInputVol.AutoSize = true;
            this.lblInputVol.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.lblInputVol.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.lblInputVol.Location = new System.Drawing.Point(334, 99);
            this.lblInputVol.Name = "lblInputVol";
            this.lblInputVol.Size = new System.Drawing.Size(31, 20);
            this.lblInputVol.TabIndex = 23;
            this.lblInputVol.Text = "100";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label9.Location = new System.Drawing.Point(12, 177);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(145, 18);
            this.label9.TabIndex = 22;
            this.label9.Text = "Default Output Volume:";
            // 
            // barOutputVol
            // 
            this.barOutputVol.LargeChange = 10;
            this.barOutputVol.Location = new System.Drawing.Point(164, 177);
            this.barOutputVol.Maximum = 100;
            this.barOutputVol.Name = "barOutputVol";
            this.barOutputVol.Size = new System.Drawing.Size(141, 45);
            this.barOutputVol.TabIndex = 6;
            this.barOutputVol.TickFrequency = 20;
            this.barOutputVol.Value = 100;
            this.barOutputVol.Scroll += new System.EventHandler(this.barOutputVvol_Scroll);
            // 
            // barInputVol
            // 
            this.barInputVol.Enabled = false;
            this.barInputVol.LargeChange = 10;
            this.barInputVol.Location = new System.Drawing.Point(164, 93);
            this.barInputVol.Maximum = 100;
            this.barInputVol.Name = "barInputVol";
            this.barInputVol.Size = new System.Drawing.Size(141, 45);
            this.barInputVol.TabIndex = 5;
            this.barInputVol.TickFrequency = 20;
            this.barInputVol.Value = 100;
            this.barInputVol.Scroll += new System.EventHandler(this.barInputVol_Scroll);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label8.Location = new System.Drawing.Point(23, 99);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(135, 18);
            this.label8.TabIndex = 20;
            this.label8.Text = "Default Input Volume:";
            // 
            // checkSound
            // 
            this.checkSound.AutoSize = true;
            this.checkSound.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.checkSound.Location = new System.Drawing.Point(164, 52);
            this.checkSound.Name = "checkSound";
            this.checkSound.Size = new System.Drawing.Size(72, 22);
            this.checkSound.TabIndex = 4;
            this.checkSound.Text = "Enabled";
            this.checkSound.UseVisualStyleBackColor = true;
            this.checkSound.CheckedChanged += new System.EventHandler(this.checkSound_CheckedChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label7.Location = new System.Drawing.Point(29, 56);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(129, 18);
            this.label7.TabIndex = 18;
            this.label7.Text = "Microphone Support:";
            // 
            // tabVideo
            // 
            this.tabVideo.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.tabVideo.Controls.Add(this.label12);
            this.tabVideo.Controls.Add(this.lblCaptureTime);
            this.tabVideo.Controls.Add(this.barCaptureTime);
            this.tabVideo.Controls.Add(this.label10);
            this.tabVideo.Controls.Add(this.checkCamera);
            this.tabVideo.Controls.Add(this.label11);
            this.tabVideo.Location = new System.Drawing.Point(4, 22);
            this.tabVideo.Name = "tabVideo";
            this.tabVideo.Size = new System.Drawing.Size(422, 299);
            this.tabVideo.TabIndex = 3;
            this.tabVideo.Text = "Video";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label12.Location = new System.Drawing.Point(342, 106);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(25, 18);
            this.label12.TabIndex = 25;
            this.label12.Text = "ms";
            // 
            // lblCaptureTime
            // 
            this.lblCaptureTime.AutoSize = true;
            this.lblCaptureTime.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.lblCaptureTime.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.lblCaptureTime.Location = new System.Drawing.Point(312, 104);
            this.lblCaptureTime.Name = "lblCaptureTime";
            this.lblCaptureTime.Size = new System.Drawing.Size(24, 20);
            this.lblCaptureTime.TabIndex = 20;
            this.lblCaptureTime.Text = "20";
            // 
            // barCaptureTime
            // 
            this.barCaptureTime.Enabled = false;
            this.barCaptureTime.Location = new System.Drawing.Point(155, 104);
            this.barCaptureTime.Maximum = 60;
            this.barCaptureTime.Minimum = 20;
            this.barCaptureTime.Name = "barCaptureTime";
            this.barCaptureTime.Size = new System.Drawing.Size(141, 45);
            this.barCaptureTime.SmallChange = 2;
            this.barCaptureTime.TabIndex = 8;
            this.barCaptureTime.TickFrequency = 10;
            this.barCaptureTime.Value = 20;
            this.barCaptureTime.Scroll += new System.EventHandler(this.barCaptureTime_Scroll);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label10.Location = new System.Drawing.Point(13, 106);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(140, 18);
            this.label10.TabIndex = 24;
            this.label10.Text = "Image Capture Period:";
            // 
            // checkCamera
            // 
            this.checkCamera.AutoSize = true;
            this.checkCamera.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.checkCamera.Location = new System.Drawing.Point(165, 52);
            this.checkCamera.Name = "checkCamera";
            this.checkCamera.Size = new System.Drawing.Size(72, 22);
            this.checkCamera.TabIndex = 7;
            this.checkCamera.Text = "Enabled";
            this.checkCamera.UseVisualStyleBackColor = true;
            this.checkCamera.CheckedChanged += new System.EventHandler(this.checkCamera_CheckedChanged);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label11.Location = new System.Drawing.Point(46, 53);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(107, 18);
            this.label11.TabIndex = 23;
            this.label11.Text = "Camera Support:";
            // 
            // tabGeneral
            // 
            this.tabGeneral.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.tabGeneral.Controls.Add(this.label14);
            this.tabGeneral.Controls.Add(this.lblLastConn);
            this.tabGeneral.Controls.Add(this.barLastConn);
            this.tabGeneral.Controls.Add(this.label13);
            this.tabGeneral.Location = new System.Drawing.Point(4, 22);
            this.tabGeneral.Name = "tabGeneral";
            this.tabGeneral.Padding = new System.Windows.Forms.Padding(3);
            this.tabGeneral.Size = new System.Drawing.Size(422, 299);
            this.tabGeneral.TabIndex = 4;
            this.tabGeneral.Text = "General";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label14.Location = new System.Drawing.Point(361, 49);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(41, 18);
            this.label14.TabIndex = 28;
            this.label14.Text = "items";
            // 
            // lblLastConn
            // 
            this.lblLastConn.AutoSize = true;
            this.lblLastConn.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.lblLastConn.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.lblLastConn.Location = new System.Drawing.Point(331, 47);
            this.lblLastConn.Name = "lblLastConn";
            this.lblLastConn.Size = new System.Drawing.Size(24, 20);
            this.lblLastConn.TabIndex = 27;
            this.lblLastConn.Text = "10";
            // 
            // barLastConn
            // 
            this.barLastConn.Location = new System.Drawing.Point(180, 47);
            this.barLastConn.Maximum = 20;
            this.barLastConn.Name = "barLastConn";
            this.barLastConn.Size = new System.Drawing.Size(135, 45);
            this.barLastConn.TabIndex = 26;
            this.barLastConn.TickFrequency = 5;
            this.barLastConn.Value = 10;
            this.barLastConn.Scroll += new System.EventHandler(this.barLastConn_Scroll);
            // 
            // label13
            // 
            this.label13.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label13.Location = new System.Drawing.Point(24, 49);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(150, 59);
            this.label13.TabIndex = 25;
            this.label13.Text = "Maximum Items in Last Connected Servers:";
            // 
            // butOK
            // 
            this.butOK.Location = new System.Drawing.Point(211, 347);
            this.butOK.Name = "butOK";
            this.butOK.Size = new System.Drawing.Size(73, 26);
            this.butOK.TabIndex = 1;
            this.butOK.Text = "&OK";
            this.butOK.UseVisualStyleBackColor = true;
            this.butOK.Click += new System.EventHandler(this.butOK_Click);
            // 
            // butCancel
            // 
            this.butCancel.Location = new System.Drawing.Point(290, 348);
            this.butCancel.Name = "butCancel";
            this.butCancel.Size = new System.Drawing.Size(73, 25);
            this.butCancel.TabIndex = 2;
            this.butCancel.Text = "&Cancel";
            this.butCancel.UseVisualStyleBackColor = true;
            this.butCancel.Click += new System.EventHandler(this.butCancel_Click);
            // 
            // butApply
            // 
            this.butApply.Enabled = false;
            this.butApply.Location = new System.Drawing.Point(369, 347);
            this.butApply.Name = "butApply";
            this.butApply.Size = new System.Drawing.Size(73, 25);
            this.butApply.TabIndex = 3;
            this.butApply.Text = "&Apply";
            this.butApply.UseVisualStyleBackColor = true;
            this.butApply.Click += new System.EventHandler(this.butApply_Click);
            // 
            // prefWindow
            // 
            this.AcceptButton = this.butOK;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(454, 385);
            this.Controls.Add(this.butApply);
            this.Controls.Add(this.butCancel);
            this.Controls.Add(this.butOK);
            this.Controls.Add(this.tabContainer);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "prefWindow";
            this.Text = "Preferences";
            this.Load += new System.EventHandler(this.prefWindow_Load);
            this.tabContainer.ResumeLayout(false);
            this.tabUser.ResumeLayout(false);
            this.tabUser.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.tabConnection.ResumeLayout(false);
            this.tabConnection.PerformLayout();
            this.tabAudio.ResumeLayout(false);
            this.tabAudio.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.barOutputVol)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.barInputVol)).EndInit();
            this.tabVideo.ResumeLayout(false);
            this.tabVideo.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.barCaptureTime)).EndInit();
            this.tabGeneral.ResumeLayout(false);
            this.tabGeneral.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.barLastConn)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabContainer;
        private System.Windows.Forms.TabPage tabUser;
        private System.Windows.Forms.TabPage tabConnection;
        private System.Windows.Forms.TabPage tabAudio;
        private System.Windows.Forms.TabPage tabVideo;
        private System.Windows.Forms.TabPage tabGeneral;
        private System.Windows.Forms.Button butOK;
        private System.Windows.Forms.Button butCancel;
        private System.Windows.Forms.Button butApply;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox boxUser;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button butDefault;
        private System.Windows.Forms.Button butUpdate;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ComboBox boxMaxConnection;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.CheckBox checkSound;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TrackBar barInputVol;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TrackBar barOutputVol;
        private System.Windows.Forms.TrackBar barCaptureTime;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.CheckBox checkCamera;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label lblCaptureTime;
        private System.Windows.Forms.Label lblOutputVol;
        private System.Windows.Forms.Label lblInputVol;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label lblLastConn;
        private System.Windows.Forms.TrackBar barLastConn;
    }
}