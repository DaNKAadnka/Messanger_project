using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;

namespace WpfApp1
{
    public class NetworkModule
    {

        // Singleton
        public static NetworkModule instance;
        public static MainWindow mainWindow;

        private TcpClient client;
        //private NetworkStream stream;

        private byte[] buffer = new byte[4096];


        public NetworkModule()
        {
            client = new TcpClient();

            var server = "127.0.0.1";
            try
            {
                client.Connect(server, 1234);

                client.GetStream().BeginRead(buffer, 0, buffer.Length, MessageReceived, null);
            }
            catch
            {
                MessageBox.Show("Connection denied. Please, check your server!");
                Environment.Exit(0);
            }
        }

        public void SendMessage(string message)
        {

            // конвертируем данные в массив байтов
            byte[] requestData = Encoding.UTF8.GetBytes(message);
            // отправляем данные серверу
            client.GetStream().Write(requestData, 0, requestData.Length);


        }

        private void MessageReceived(IAsyncResult e)
        {
            if (e.IsCompleted)
            {

                int bytes = client.GetStream().EndRead(e);
                if (bytes > 0)
                {

                    byte[] temp = new byte[bytes];
                    Array.Copy(buffer, 0, temp, 0, bytes);
                    string str = Encoding.ASCII.GetString(temp);

                    Action action = () =>
                    {
                        MainWindow.messages.Add(str);

                    };

                    Application.Current.Dispatcher.Invoke(action);
                    
                    //messages.Add(str);
                }

                
                Array.Clear(buffer, 0, buffer.Length);
                client.GetStream().BeginRead(buffer, 0, buffer.Length, MessageReceived, null);
            }
        }
    }
}
