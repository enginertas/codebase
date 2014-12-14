namespace WindowsFormsApplication1
{
    partial class Games
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
            this.label3 = new System.Windows.Forms.Label();
            this.listGames = new System.Windows.Forms.ListBox();
            this.butPlay = new System.Windows.Forms.Button();
            this.butAdd = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.butCancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label3.ForeColor = System.Drawing.Color.Blue;
            this.label3.Location = new System.Drawing.Point(116, 56);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 18);
            this.label3.TabIndex = 18;
            this.label3.Text = "Type:";
            // 
            // listGames
            // 
            this.listGames.FormattingEnabled = true;
            this.listGames.Items.AddRange(new object[] {
            "Hımbıl\t\t[Java]"});
            this.listGames.Location = new System.Drawing.Point(21, 77);
            this.listGames.MultiColumn = true;
            this.listGames.Name = "listGames";
            this.listGames.Size = new System.Drawing.Size(193, 134);
            this.listGames.TabIndex = 19;
            // 
            // butPlay
            // 
            this.butPlay.Location = new System.Drawing.Point(233, 77);
            this.butPlay.Name = "butPlay";
            this.butPlay.Size = new System.Drawing.Size(91, 26);
            this.butPlay.TabIndex = 20;
            this.butPlay.Text = "&Play";
            this.butPlay.UseVisualStyleBackColor = true;
            this.butPlay.Click += new System.EventHandler(this.butPlay_Click);
            // 
            // butAdd
            // 
            this.butAdd.Location = new System.Drawing.Point(21, 217);
            this.butAdd.Name = "butAdd";
            this.butAdd.Size = new System.Drawing.Size(127, 28);
            this.butAdd.TabIndex = 22;
            this.butAdd.Text = "Download New Games";
            this.butAdd.UseVisualStyleBackColor = true;
            this.butAdd.Click += new System.EventHandler(this.butAdd_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label1.ForeColor = System.Drawing.Color.Blue;
            this.label1.Location = new System.Drawing.Point(18, 56);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 18);
            this.label1.TabIndex = 23;
            this.label1.Text = "Name:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Trebuchet MS", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label2.ForeColor = System.Drawing.Color.Black;
            this.label2.Location = new System.Drawing.Point(57, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(239, 18);
            this.label2.TabIndex = 24;
            this.label2.Text = "Select a game to Play or Add a New one";
            // 
            // butCancel
            // 
            this.butCancel.Location = new System.Drawing.Point(233, 109);
            this.butCancel.Name = "butCancel";
            this.butCancel.Size = new System.Drawing.Size(91, 26);
            this.butCancel.TabIndex = 25;
            this.butCancel.Text = "Cancel";
            this.butCancel.UseVisualStyleBackColor = true;
            this.butCancel.Click += new System.EventHandler(this.butCancel_Click);
            // 
            // Games
            // 
            this.AcceptButton = this.butPlay;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(350, 253);
            this.Controls.Add(this.butCancel);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.butAdd);
            this.Controls.Add(this.butPlay);
            this.Controls.Add(this.listGames);
            this.Controls.Add(this.label3);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Games";
            this.Text = "Games";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ListBox listGames;
        private System.Windows.Forms.Button butPlay;
        private System.Windows.Forms.Button butAdd;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button butCancel;
    }
}