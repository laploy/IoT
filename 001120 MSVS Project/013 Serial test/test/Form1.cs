using System;
using System.Windows.Forms;

namespace test
{ 
    public partial class Form1 : Form
    {
        private Timer myTimer = new Timer();

        public Form1()
        {
            InitializeComponent();
            myTimer.Interval = 500;
            myTimer.Enabled = false;
            myTimer.Tick += MyTimer_Tick;
            loySerialPortUc1.OnDataReceived += LoySerialPortUc1_OnDataReceived;
        }

        private void MyTimer_Tick(object sender, EventArgs e)
        {
            loySerialPortUc1.Write("A");
            textBox1.AppendText("A");
        }

        private void LoySerialPortUc1_OnDataReceived(string recieveString)
        {
            textBox1.Invoke(new Action(() =>
            { textBox1.AppendText(recieveString); }));
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            myTimer.Enabled = true;
        }
    }
}
