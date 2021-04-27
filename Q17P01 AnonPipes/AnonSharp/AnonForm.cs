using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace AnonSharp
{
    public partial class AnonForm : Form
    {
        [DllImport("AnonDll.dll", CharSet = CharSet.Ansi)]
        private static extern void Send(StringBuilder Str);
        public AnonForm()
        {
            InitializeComponent();
        }

        private void CloseButton_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void SendButton_Click(object sender, EventArgs e)
        {
            var sb = new StringBuilder(textBox.Text);
            Send(sb);
            textBox.Text = "";
        }
    }
}
