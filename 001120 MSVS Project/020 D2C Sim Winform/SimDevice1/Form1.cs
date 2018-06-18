/// <remarks>
/// Laploy V.Angkul
/// laploy@gmail.com
/// July ,2017
/// </remarks>


using System;
using System.Text;
using System.Windows.Forms;
using Microsoft.Azure.Devices.Client;
using Newtonsoft.Json;

namespace SimDevice1
{
    public partial class Form1 : Form
    {
        DeviceClient deviceClient;
        string myDevice = "d1";
        string iotHubUri = "loy2017bh1.azure-devices.net";
        string deviceKey = "K2JW/PI2qPxLC7qzu0kC2m9WB65tji3uEoPiqkfgDCA=";

        public Form1()
        {
            InitializeComponent();
            deviceClient = DeviceClient.Create(iotHubUri, new DeviceAuthenticationWithRegistrySymmetricKey(myDevice, deviceKey));
        }
        private async void SendDeviceToCloudMessagesAsync(string data)
        {
            string myLocation = "Ban";
            string myTime = DateTime.Now.ToShortTimeString();
            string myDate = DateTime.Now.ToShortDateString();
            var telemetryDataPoint = new
            {
                deviceId = myDevice,
                location = myLocation,
                date = myDate,
                time = myTime,
                Temperature = Convert.ToDouble(data)
            };
            var messageString = JsonConvert.SerializeObject(telemetryDataPoint);
            var message = new Microsoft.Azure.Devices.Client.Message(Encoding.ASCII.GetBytes(messageString));
            await deviceClient.SendEventAsync(message);
            textBoxCouldTX.Invoke(new MethodInvoker(delegate { textBoxCouldTX.AppendText(DateTime.Now + messageString + "\r\n"); }));
        }
        private void button1_Click(object sender, EventArgs e)
        {
            double temper = 10; // m/s
            Random rand = new Random();
            double currentTemper = temper + rand.NextDouble() * 4 - 3;
            string temperStr = currentTemper.ToString();
            textBoxCouldTX.AppendText(temperStr + "\r\n");
            SendDeviceToCloudMessagesAsync(temperStr);

        }
        private void button2_Click(object sender, EventArgs e)
        {
            textBoxCouldTX.Clear();
        }
    }
}
