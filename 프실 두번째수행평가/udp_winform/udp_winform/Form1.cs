using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace udp_winform
{
    public partial class Form1 : Form
    {

        char[] MyIp = new char[13];

        private SerialPort mySerial = new SerialPort();

        public Form1()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[1024];
            //"10.80.163.244"
            UdpClient client = new UdpClient("192.168.139.128", 10004);

            data = Encoding.UTF8.GetBytes("haha");
            client.Send(data, data.Length);

            client.Close();
            Console.WriteLine("Stopping clinet");
        }

        private void button1_Click(object sender, EventArgs e)  // LED1 ON
        {

        }

        private void button3_Click(object sender, EventArgs e)  // LED2 ON
        {

        }

        private void button4_Click(object sender, EventArgs e)  // LED1 OFF
        {

        }

        private void button5_Click(object sender, EventArgs e)  // LED2 OFF
        {

        }
    }
}
