﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace IPCClient_CSharp
{
    public partial class frmMain : Form
    {
        [DllImport("user32.dll")]
        private static extern int SendMessage(IntPtr hwnd, uint wMsg, int wParam, IntPtr lParam);

        [DllImport("user32.dll")]
        private static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        private const uint WM_APP = 0x8000;
        enum WIMMessage : uint
        {
            WM_IPC_MSG = WM_APP + 1,
        }

        enum Msg_Cmd
        {
            Cmd_Test,
            Cmd_SM_CString,

        };

        public frmMain()
        {
            InitializeComponent();
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            
        }

        private void btnSendMsg_Click(object sender, EventArgs e)
        {
            IntPtr hwnd = FindWindow("CIPCdemoDlg", null);
            if (hwnd == IntPtr.Zero)
                return;
            SendMessage(hwnd, (uint)WIMMessage.WM_IPC_MSG, (int)Msg_Cmd.Cmd_Test, new IntPtr(10));
        }

        protected override void WndProc(ref Message m)
        {
            if (m.Msg == (uint)WIMMessage.WM_IPC_MSG)
            {
                lsDebugString.Items.Add(m.LParam.ToString());
                lsDebugString.SelectedIndex = lsDebugString.Items.Count - 1;
            }
            base.WndProc(ref m);
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            lsDebugString.Items.Clear();
            lsSharedMemory.Items.Clear();
            lsSocket.Items.Clear();
        }

        private void btnSharedMemory_Click(object sender, EventArgs e)
        {
            try
            {
                using (MemoryMappedFile mmf = MemoryMappedFile.OpenExisting("Global\\SM_IPC"))
                {
                    //Mutex mutex = Mutex.OpenExisting("DarkthreadSharedMem");
                    //mutex.WaitOne();                    
                    //using (MemoryMappedViewStream stream = mmf.CreateViewStream(0, 0))
                    //{
                    //    using (var br = new BinaryReader(stream))
                    //    {
                    //        //先讀取長度，再讀取内容
                    //        var len = br.ReadInt32();
                    //        var word = Encoding.UTF8.GetString(br.ReadBytes(len), 0, len);
                    //    }
                    //}
                    using (MemoryMappedViewStream stream = mmf.CreateViewStream(0, 1024))
                    {
                        using (var bw = new BinaryWriter(stream))
                        {
                            if (txtSharedMemory.Text.Length == 0)
                                return;

                            IntPtr hwnd = FindWindow("CIPCdemoDlg", null);
                            if (hwnd == IntPtr.Zero)
                                return;
                            
                            var msg = Encoding.UTF8.GetBytes(txtSharedMemory.Text);
                            bw.Write(msg.Length);
                            bw.Write(msg);
                            
                            SendMessage(hwnd, (uint)WIMMessage.WM_IPC_MSG, (int)Msg_Cmd.Cmd_SM_CString, new IntPtr(msg.Length));
                        }
                    }
                    //mutex.ReleaseMutex();
                }
            }
            catch (FileNotFoundException ex)
            {
                MessageBox.Show("Memory-mapped file does not exist.");
            }
        }

        private void btnSocketSend_Click(object sender, EventArgs e)
        {

        }

        private void btnConnect_Click(object sender, EventArgs e)
        {

        }
    }
}
