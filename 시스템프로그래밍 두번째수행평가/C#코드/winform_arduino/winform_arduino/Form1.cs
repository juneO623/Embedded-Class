using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO.Ports;

namespace winform_arduino
{
    public partial class Form1 : Form
    {

        private SerialPort mySerial = new SerialPort();

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        public Form1()
        {
            InitializeComponent();

            mySerial.PortName = "COM5";
            mySerial.BaudRate = 9600;
            mySerial.Open();
            //mySerial.DataBits = 8;
            //mySerial.StopBits = StopBits.One;
            //mySerial.Parity = Parity.None;

            //button1.Enabled = true;
            //button3.Enabled = true;
            //button5.Enabled = true;
            //button7.Enabled = false;
            //button8.Enabled = false;
            //button9.Enabled = true;
        }

        private void LED_1_ON(object sender, EventArgs e)   // button1
        {
            mySerial.Write("1");

            //button1.Enabled = false;
            //button3.Enabled = true;
        }

        private void LED_2_ON(object sender, EventArgs e)   // button7
        {
            mySerial.Write("2");

            //button7.Enabled = false;
            //button8.Enabled = true;
        }
        private void LED_1_OFF(object sender, EventArgs e)   // button3
        {
            mySerial.Write("3");

            //button3.Enabled = false;
            //button1.Enabled = true;
        }

        private void LED_2_OFF(object sender, EventArgs e)   // button8
        {
            mySerial.Write("4");

            //button8.Enabled = false;
            //button7.Enabled = true;x666666666666666666666666666666666666666666666666666666666666666666666
        }

        private void SERVO_LEFT(object sender, EventArgs e)   // button5
        {
            mySerial.Write("5");

            //button5.Enabled = false;
            //button9.Enabled = true;
        }

        private void SERVO_RIGHT(object sender, EventArgs e)   // button9
        {
            mySerial.Write("6");

            //button9.Enabled = false;
            //button5.Enabled = true;
        }
    }
}
