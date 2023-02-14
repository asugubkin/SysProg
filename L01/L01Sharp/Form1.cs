using Microsoft.VisualBasic.ApplicationServices;
using System.Diagnostics;
using System.Text;

namespace L01Sharp
{
    public partial class Form1 : Form
    {
        Process childProcess = null;
        EventWaitHandle eventStart = new EventWaitHandle(false, EventResetMode.AutoReset, "StartEvent");
        EventWaitHandle eventConfirm = new EventWaitHandle(false, EventResetMode.AutoReset, "ConfirmEvent");
        public Form1()
        {
            InitializeComponent();
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            if(childProcess==null || childProcess.HasExited)
            {
                childProcess = Process.Start("L01.exe");
            }
            else
            {
                eventStart.Set();
                eventConfirm.WaitOne();
            }
        }
    }
}