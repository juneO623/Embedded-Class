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
            byte[] data = new byte[1024];
            
            UdpClient client = new UdpClient("192.168.132.48", 10004);

            data = Encoding.UTF8.GetBytes("led1on");
            client.Send(data, data.Length);

            client.Close();
            Console.WriteLine("Stopping clinet");
        }

        private void button3_Click(object sender, EventArgs e)  // LED2 ON
        {
            byte[] data = new byte[1024];

            UdpClient client = new UdpClient("192.168.132.48", 10004);

            data = Encoding.UTF8.GetBytes("led2on");
            client.Send(data, data.Length);

            client.Close();
            Console.WriteLine("Stopping clinet");
        }

        private void button4_Click(object sender, EventArgs e)  // LED1 OFF
        {
            byte[] data = new byte[1024];

            UdpClient client = new UdpClient("192.168.132.48", 10004);

            data = Encoding.UTF8.GetBytes("led1of");
            client.Send(data, data.Length);

            client.Close();
            Console.WriteLine("Stopping clinet");
        }

        private void button5_Click(object sender, EventArgs e)  // LED2 OFF
        {
            byte[] data = new byte[1024];

            UdpClient client = new UdpClient("192.168.132.48", 10004);

            data = Encoding.UTF8.GetBytes("led2of");
            client.Send(data, data.Length);

            client.Close();
            Console.WriteLine("Stopping clinet");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[1024];

            UdpClient client = new UdpClient("192.168.132.48", 10004);

            data = Encoding.UTF8.GetBytes("smolef");
            client.Send(data, data.Length);

            client.Close();
            Console.WriteLine("Stopping clinet");
        }

        private void button7_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[1024];

            UdpClient client = new UdpClient("192.168.132.48", 10004);

            data = Encoding.UTF8.GetBytes("smorit");
            client.Send(data, data.Length);

            client.Close();
            Console.WriteLine("Stopping clinet");
        }
    }
}
