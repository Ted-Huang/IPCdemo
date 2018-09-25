namespace IPCClient_CSharp
{
    partial class frmMain
    {
        /// <summary>
        /// 設計工具所需的變數。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清除任何使用中的資源。
        /// </summary>
        /// <param name="disposing">如果應該處置 Managed 資源則為 true，否則為 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 設計工具產生的程式碼

        /// <summary>
        /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
        /// 這個方法的內容。
        /// </summary>
        private void InitializeComponent()
        {
            this.btnSendMsg = new System.Windows.Forms.Button();
            this.lsDebugString = new System.Windows.Forms.ListBox();
            this.btnClear = new System.Windows.Forms.Button();
            this.btnSharedMemory = new System.Windows.Forms.Button();
            this.txtSharedMemory = new System.Windows.Forms.TextBox();
            this.lsSharedMemory = new System.Windows.Forms.ListBox();
            this.btnConnect = new System.Windows.Forms.Button();
            this.txtIP = new System.Windows.Forms.TextBox();
            this.txtPort = new System.Windows.Forms.TextBox();
            this.lsSocket = new System.Windows.Forms.ListBox();
            this.btnSocketSend = new System.Windows.Forms.Button();
            this.txtSocketSend = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // btnSendMsg
            // 
            this.btnSendMsg.Location = new System.Drawing.Point(12, 23);
            this.btnSendMsg.Name = "btnSendMsg";
            this.btnSendMsg.Size = new System.Drawing.Size(91, 21);
            this.btnSendMsg.TabIndex = 0;
            this.btnSendMsg.Text = "SendMsg";
            this.btnSendMsg.UseVisualStyleBackColor = true;
            this.btnSendMsg.Click += new System.EventHandler(this.btnSendMsg_Click);
            // 
            // lsDebugString
            // 
            this.lsDebugString.FormattingEnabled = true;
            this.lsDebugString.ItemHeight = 12;
            this.lsDebugString.Location = new System.Drawing.Point(228, 23);
            this.lsDebugString.Name = "lsDebugString";
            this.lsDebugString.Size = new System.Drawing.Size(120, 52);
            this.lsDebugString.TabIndex = 1;
            // 
            // btnClear
            // 
            this.btnClear.Location = new System.Drawing.Point(12, 54);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(91, 21);
            this.btnClear.TabIndex = 2;
            this.btnClear.Text = "Clear";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // btnSharedMemory
            // 
            this.btnSharedMemory.Location = new System.Drawing.Point(12, 94);
            this.btnSharedMemory.Name = "btnSharedMemory";
            this.btnSharedMemory.Size = new System.Drawing.Size(91, 21);
            this.btnSharedMemory.TabIndex = 3;
            this.btnSharedMemory.Text = "Shared memory";
            this.btnSharedMemory.UseVisualStyleBackColor = true;
            this.btnSharedMemory.Click += new System.EventHandler(this.btnSharedMemory_Click);
            // 
            // txtSharedMemory
            // 
            this.txtSharedMemory.Location = new System.Drawing.Point(109, 93);
            this.txtSharedMemory.Name = "txtSharedMemory";
            this.txtSharedMemory.Size = new System.Drawing.Size(100, 22);
            this.txtSharedMemory.TabIndex = 4;
            // 
            // lsSharedMemory
            // 
            this.lsSharedMemory.FormattingEnabled = true;
            this.lsSharedMemory.ItemHeight = 12;
            this.lsSharedMemory.Location = new System.Drawing.Point(228, 94);
            this.lsSharedMemory.Name = "lsSharedMemory";
            this.lsSharedMemory.Size = new System.Drawing.Size(120, 52);
            this.lsSharedMemory.TabIndex = 5;
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(12, 164);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(91, 21);
            this.btnConnect.TabIndex = 6;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // txtIP
            // 
            this.txtIP.Location = new System.Drawing.Point(109, 165);
            this.txtIP.Name = "txtIP";
            this.txtIP.Size = new System.Drawing.Size(100, 22);
            this.txtIP.TabIndex = 7;
            // 
            // txtPort
            // 
            this.txtPort.Location = new System.Drawing.Point(109, 193);
            this.txtPort.Name = "txtPort";
            this.txtPort.Size = new System.Drawing.Size(100, 22);
            this.txtPort.TabIndex = 8;
            // 
            // lsSocket
            // 
            this.lsSocket.FormattingEnabled = true;
            this.lsSocket.ItemHeight = 12;
            this.lsSocket.Location = new System.Drawing.Point(228, 164);
            this.lsSocket.Name = "lsSocket";
            this.lsSocket.Size = new System.Drawing.Size(120, 52);
            this.lsSocket.TabIndex = 9;
            // 
            // btnSocketSend
            // 
            this.btnSocketSend.Location = new System.Drawing.Point(12, 225);
            this.btnSocketSend.Name = "btnSocketSend";
            this.btnSocketSend.Size = new System.Drawing.Size(91, 21);
            this.btnSocketSend.TabIndex = 10;
            this.btnSocketSend.Text = "SocketSend";
            this.btnSocketSend.UseVisualStyleBackColor = true;
            this.btnSocketSend.Click += new System.EventHandler(this.btnSocketSend_Click);
            // 
            // txtSocketSend
            // 
            this.txtSocketSend.Location = new System.Drawing.Point(109, 226);
            this.txtSocketSend.Name = "txtSocketSend";
            this.txtSocketSend.Size = new System.Drawing.Size(100, 22);
            this.txtSocketSend.TabIndex = 11;
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(414, 277);
            this.Controls.Add(this.txtSocketSend);
            this.Controls.Add(this.btnSocketSend);
            this.Controls.Add(this.lsSocket);
            this.Controls.Add(this.txtPort);
            this.Controls.Add(this.txtIP);
            this.Controls.Add(this.btnConnect);
            this.Controls.Add(this.lsSharedMemory);
            this.Controls.Add(this.txtSharedMemory);
            this.Controls.Add(this.btnSharedMemory);
            this.Controls.Add(this.btnClear);
            this.Controls.Add(this.lsDebugString);
            this.Controls.Add(this.btnSendMsg);
            this.Name = "frmMain";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.frmMain_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnSendMsg;
        private System.Windows.Forms.ListBox lsDebugString;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.Button btnSharedMemory;
        private System.Windows.Forms.TextBox txtSharedMemory;
        private System.Windows.Forms.ListBox lsSharedMemory;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.TextBox txtIP;
        private System.Windows.Forms.TextBox txtPort;
        private System.Windows.Forms.ListBox lsSocket;
        private System.Windows.Forms.Button btnSocketSend;
        private System.Windows.Forms.TextBox txtSocketSend;
    }
}

