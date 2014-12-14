namespace WindowsFormsApplication1
{
    partial class Server
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Server));
            this.txtMessage = new System.Windows.Forms.TextBox();
            this.butSend = new System.Windows.Forms.Button();
            this.txtLog = new System.Windows.Forms.TextBox();
            this.butCamera = new System.Windows.Forms.Button();
            this.camBox = new System.Windows.Forms.PictureBox();
            this.camBox0 = new System.Windows.Forms.PictureBox();
            this.camBox4 = new System.Windows.Forms.PictureBox();
            this.camBox1 = new System.Windows.Forms.PictureBox();
            this.camBox2 = new System.Windows.Forms.PictureBox();
            this.camBox3 = new System.Windows.Forms.PictureBox();
            this.butSound = new System.Windows.Forms.Button();
            this.gameArea = new AxShockwaveFlashObjects.AxShockwaveFlash();
            this.barInput = new System.Windows.Forms.TrackBar();
            this.barOutput = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.preferencesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuUser = new System.Windows.Forms.ToolStripMenuItem();
            this.menuAudio = new System.Windows.Forms.ToolStripMenuItem();
            this.menuVideo = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.menuGeneral = new System.Windows.Forms.ToolStripMenuItem();
            this.seçenekleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuPlay = new System.Windows.Forms.ToolStripMenuItem();
            this.yardımToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.içindekilerToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.searchToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.aboutUsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutAddonsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label7 = new System.Windows.Forms.Label();
            this.listUsers = new System.Windows.Forms.ListBox();
            this.butEndGame = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.camBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.camBox0)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.camBox4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.camBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.camBox2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.camBox3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gameArea)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.barInput)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.barOutput)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // txtMessage
            // 
            this.txtMessage.Location = new System.Drawing.Point(691, 611);
            this.txtMessage.Multiline = true;
            this.txtMessage.Name = "txtMessage";
            this.txtMessage.Size = new System.Drawing.Size(231, 41);
            this.txtMessage.TabIndex = 0;
            // 
            // butSend
            // 
            this.butSend.Location = new System.Drawing.Point(928, 611);
            this.butSend.Name = "butSend";
            this.butSend.Size = new System.Drawing.Size(52, 26);
            this.butSend.TabIndex = 1;
            this.butSend.Text = "send";
            this.butSend.UseVisualStyleBackColor = true;
            this.butSend.Click += new System.EventHandler(this.butSend_Click);
            // 
            // txtLog
            // 
            this.txtLog.Font = new System.Drawing.Font("Trebuchet MS", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.txtLog.Location = new System.Drawing.Point(691, 447);
            this.txtLog.Multiline = true;
            this.txtLog.Name = "txtLog";
            this.txtLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtLog.Size = new System.Drawing.Size(289, 158);
            this.txtLog.TabIndex = 12;
            this.txtLog.TabStop = false;
            // 
            // butCamera
            // 
            this.butCamera.Location = new System.Drawing.Point(156, 564);
            this.butCamera.Name = "butCamera";
            this.butCamera.Size = new System.Drawing.Size(74, 36);
            this.butCamera.TabIndex = 2;
            this.butCamera.Text = "Start Camera";
            this.butCamera.UseVisualStyleBackColor = true;
            this.butCamera.Click += new System.EventHandler(this.butCamera_Click);
            // 
            // camBox
            // 
            this.camBox.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.camBox.Location = new System.Drawing.Point(236, 532);
            this.camBox.Name = "camBox";
            this.camBox.Size = new System.Drawing.Size(218, 176);
            this.camBox.TabIndex = 16;
            this.camBox.TabStop = false;
            // 
            // camBox0
            // 
            this.camBox0.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.camBox0.Location = new System.Drawing.Point(12, 251);
            this.camBox0.Name = "camBox0";
            this.camBox0.Size = new System.Drawing.Size(218, 176);
            this.camBox0.TabIndex = 20;
            this.camBox0.TabStop = false;
            // 
            // camBox4
            // 
            this.camBox4.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.camBox4.Location = new System.Drawing.Point(691, 251);
            this.camBox4.Name = "camBox4";
            this.camBox4.Size = new System.Drawing.Size(218, 176);
            this.camBox4.TabIndex = 21;
            this.camBox4.TabStop = false;
            // 
            // camBox1
            // 
            this.camBox1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.camBox1.Location = new System.Drawing.Point(236, 27);
            this.camBox1.Name = "camBox1";
            this.camBox1.Size = new System.Drawing.Size(218, 176);
            this.camBox1.TabIndex = 22;
            this.camBox1.TabStop = false;
            // 
            // camBox2
            // 
            this.camBox2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.camBox2.Location = new System.Drawing.Point(467, 27);
            this.camBox2.Name = "camBox2";
            this.camBox2.Size = new System.Drawing.Size(218, 176);
            this.camBox2.TabIndex = 23;
            this.camBox2.TabStop = false;
            // 
            // camBox3
            // 
            this.camBox3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.camBox3.Location = new System.Drawing.Point(467, 532);
            this.camBox3.Name = "camBox3";
            this.camBox3.Size = new System.Drawing.Size(218, 176);
            this.camBox3.TabIndex = 24;
            this.camBox3.TabStop = false;
            // 
            // butSound
            // 
            this.butSound.Location = new System.Drawing.Point(156, 606);
            this.butSound.Name = "butSound";
            this.butSound.Size = new System.Drawing.Size(74, 36);
            this.butSound.TabIndex = 25;
            this.butSound.Text = "Start Microphone";
            this.butSound.UseVisualStyleBackColor = true;
            this.butSound.Click += new System.EventHandler(this.butSound_Click);
            // 
            // gameArea
            // 
            this.gameArea.Enabled = true;
            this.gameArea.Location = new System.Drawing.Point(236, 209);
            this.gameArea.Name = "gameArea";
            this.gameArea.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("gameArea.OcxState")));
            this.gameArea.Size = new System.Drawing.Size(449, 317);
            this.gameArea.TabIndex = 26;
            this.gameArea.Visible = false;
            // 
            // barInput
            // 
            this.barInput.LargeChange = 10;
            this.barInput.Location = new System.Drawing.Point(28, 564);
            this.barInput.Maximum = 100;
            this.barInput.Name = "barInput";
            this.barInput.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.barInput.Size = new System.Drawing.Size(45, 115);
            this.barInput.TabIndex = 27;
            this.barInput.TickFrequency = 20;
            this.barInput.Scroll += new System.EventHandler(this.barInput_Scroll);
            // 
            // barOutput
            // 
            this.barOutput.LargeChange = 10;
            this.barOutput.Location = new System.Drawing.Point(79, 564);
            this.barOutput.Maximum = 100;
            this.barOutput.Name = "barOutput";
            this.barOutput.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.barOutput.Size = new System.Drawing.Size(45, 115);
            this.barOutput.TabIndex = 28;
            this.barOutput.TickFrequency = 20;
            this.barOutput.Scroll += new System.EventHandler(this.barOutput_Scroll);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(34, 548);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(16, 13);
            this.label1.TabIndex = 29;
            this.label1.Text = "In";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(85, 548);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(24, 13);
            this.label2.TabIndex = 30;
            this.label2.Text = "Out";
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.preferencesToolStripMenuItem,
            this.seçenekleToolStripMenuItem,
            this.yardımToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(992, 24);
            this.menuStrip1.TabIndex = 31;
            this.menuStrip1.Text = "menuStrip";
            // 
            // preferencesToolStripMenuItem
            // 
            this.preferencesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuUser,
            this.menuAudio,
            this.menuVideo,
            this.toolStripSeparator4,
            this.menuGeneral});
            this.preferencesToolStripMenuItem.Name = "preferencesToolStripMenuItem";
            this.preferencesToolStripMenuItem.Size = new System.Drawing.Size(77, 20);
            this.preferencesToolStripMenuItem.Text = "&Preferences";
            // 
            // menuUser
            // 
            this.menuUser.Name = "menuUser";
            this.menuUser.Size = new System.Drawing.Size(140, 22);
            this.menuUser.Text = "&User Profile";
            this.menuUser.Click += new System.EventHandler(this.menuUser_Click);
            // 
            // menuAudio
            // 
            this.menuAudio.Name = "menuAudio";
            this.menuAudio.Size = new System.Drawing.Size(140, 22);
            this.menuAudio.Text = "&Audio";
            this.menuAudio.Click += new System.EventHandler(this.menuAudio_Click);
            // 
            // menuVideo
            // 
            this.menuVideo.Name = "menuVideo";
            this.menuVideo.Size = new System.Drawing.Size(140, 22);
            this.menuVideo.Text = "&Video";
            this.menuVideo.Click += new System.EventHandler(this.menuVideo_Click);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(137, 6);
            // 
            // menuGeneral
            // 
            this.menuGeneral.Name = "menuGeneral";
            this.menuGeneral.Size = new System.Drawing.Size(140, 22);
            this.menuGeneral.Text = "&General";
            this.menuGeneral.Click += new System.EventHandler(this.menuGeneral_Click);
            // 
            // seçenekleToolStripMenuItem
            // 
            this.seçenekleToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuPlay});
            this.seçenekleToolStripMenuItem.Name = "seçenekleToolStripMenuItem";
            this.seçenekleToolStripMenuItem.Size = new System.Drawing.Size(51, 20);
            this.seçenekleToolStripMenuItem.Text = "&Games";
            // 
            // menuPlay
            // 
            this.menuPlay.Name = "menuPlay";
            this.menuPlay.Size = new System.Drawing.Size(105, 22);
            this.menuPlay.Text = "&Play";
            this.menuPlay.Click += new System.EventHandler(this.menuPlay_Click);
            // 
            // yardımToolStripMenuItem
            // 
            this.yardımToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.içindekilerToolStripMenuItem,
            this.searchToolStripMenuItem,
            this.toolStripSeparator1,
            this.aboutUsToolStripMenuItem,
            this.aboutAddonsToolStripMenuItem});
            this.yardımToolStripMenuItem.Name = "yardımToolStripMenuItem";
            this.yardımToolStripMenuItem.Size = new System.Drawing.Size(40, 20);
            this.yardımToolStripMenuItem.Text = "&Help";
            // 
            // içindekilerToolStripMenuItem
            // 
            this.içindekilerToolStripMenuItem.Name = "içindekilerToolStripMenuItem";
            this.içindekilerToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.içindekilerToolStripMenuItem.Text = "&Index";
            // 
            // searchToolStripMenuItem
            // 
            this.searchToolStripMenuItem.Name = "searchToolStripMenuItem";
            this.searchToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.searchToolStripMenuItem.Text = "&Search";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(146, 6);
            // 
            // aboutUsToolStripMenuItem
            // 
            this.aboutUsToolStripMenuItem.Name = "aboutUsToolStripMenuItem";
            this.aboutUsToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.aboutUsToolStripMenuItem.Text = "&About Us";
            // 
            // aboutAddonsToolStripMenuItem
            // 
            this.aboutAddonsToolStripMenuItem.Name = "aboutAddonsToolStripMenuItem";
            this.aboutAddonsToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.aboutAddonsToolStripMenuItem.Text = "About &Games";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label7.ForeColor = System.Drawing.Color.Blue;
            this.label7.Location = new System.Drawing.Point(698, 42);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(92, 18);
            this.label7.TabIndex = 32;
            this.label7.Text = "Who is Inside?";
            // 
            // listUsers
            // 
            this.listUsers.Font = new System.Drawing.Font("Trebuchet MS", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.listUsers.FormattingEnabled = true;
            this.listUsers.ItemHeight = 18;
            this.listUsers.Location = new System.Drawing.Point(701, 73);
            this.listUsers.MultiColumn = true;
            this.listUsers.Name = "listUsers";
            this.listUsers.Size = new System.Drawing.Size(263, 130);
            this.listUsers.TabIndex = 33;
            // 
            // butEndGame
            // 
            this.butEndGame.Location = new System.Drawing.Point(156, 648);
            this.butEndGame.Name = "butEndGame";
            this.butEndGame.Size = new System.Drawing.Size(75, 35);
            this.butEndGame.TabIndex = 34;
            this.butEndGame.Text = "&End Game";
            this.butEndGame.UseVisualStyleBackColor = true;
            this.butEndGame.Visible = false;
            this.butEndGame.Click += new System.EventHandler(this.butEndGame_Click);
            // 
            // Server
            // 
            this.AcceptButton = this.butSend;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(992, 720);
            this.Controls.Add(this.butEndGame);
            this.Controls.Add(this.listUsers);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.barOutput);
            this.Controls.Add(this.barInput);
            this.Controls.Add(this.gameArea);
            this.Controls.Add(this.butSound);
            this.Controls.Add(this.camBox3);
            this.Controls.Add(this.camBox2);
            this.Controls.Add(this.camBox1);
            this.Controls.Add(this.camBox4);
            this.Controls.Add(this.camBox0);
            this.Controls.Add(this.camBox);
            this.Controls.Add(this.butCamera);
            this.Controls.Add(this.txtLog);
            this.Controls.Add(this.butSend);
            this.Controls.Add(this.txtMessage);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Server";
            this.Text = "Hosting Remote Users";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form_Closed);
            this.Load += new System.EventHandler(this.Form2_Load);
            ((System.ComponentModel.ISupportInitialize)(this.camBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.camBox0)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.camBox4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.camBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.camBox2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.camBox3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gameArea)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.barInput)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.barOutput)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtMessage;
        private System.Windows.Forms.Button butSend;
        private System.Windows.Forms.TextBox txtLog;
        private System.Windows.Forms.Button butCamera;
        private System.Windows.Forms.PictureBox camBox;
        private System.Windows.Forms.PictureBox camBox0;
        private System.Windows.Forms.PictureBox camBox4;
        private System.Windows.Forms.PictureBox camBox1;
        private System.Windows.Forms.PictureBox camBox2;
        private System.Windows.Forms.PictureBox camBox3;
        private System.Windows.Forms.Button butSound;
        private AxShockwaveFlashObjects.AxShockwaveFlash gameArea;
        private System.Windows.Forms.TrackBar barInput;
        private System.Windows.Forms.TrackBar barOutput;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem preferencesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuUser;
        private System.Windows.Forms.ToolStripMenuItem menuAudio;
        private System.Windows.Forms.ToolStripMenuItem menuVideo;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripMenuItem menuGeneral;
        private System.Windows.Forms.ToolStripMenuItem seçenekleToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem yardımToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem içindekilerToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem searchToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem aboutUsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutAddonsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuPlay;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ListBox listUsers;
        private System.Windows.Forms.Button butEndGame;


    }
}