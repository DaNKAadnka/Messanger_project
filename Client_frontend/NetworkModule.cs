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

        public bool isLogin = false;
        public string login;
        public string password;

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

                    processData(str);
                    
                    //messages.Add(str);
                }

                
                Array.Clear(buffer, 0, buffer.Length);
                client.GetStream().BeginRead(buffer, 0, buffer.Length, MessageReceived, null);
            }
        }

        private void processData (string message)
        {

            string[] strings = message.Split('\n');

            string command = strings[0].Substring(8);
            string status = strings[1].Substring(7);
            if (command == "Authorize" && status == "Success")
            {
                isLogin = true;
                login = strings[3].Substring(6);
                string get_messages_command = "Command:Get Messages\n" +
                    "Status: Check";
                NetworkModule.instance.SendMessage(get_messages_command);
            }
            if (command == "Register" && status == "Success")
            {
                isLogin = true;
                login = strings[3].Substring(6);
                string get_messages_command = "Command:Get Messages\n" +
                    "Status: Check";
                NetworkModule.instance.SendMessage(get_messages_command);
            }
            if (command == "Get Messages" && status == "Success")
            {
                for (int i = 3; i < strings.Length; i += 3)
                {
                    if (i + 2 >= strings.Length) break;
                    string sender = strings[i];
                    string reciever = strings[i + 1];
                    string text = strings[i + 2];
                    Action action = () =>
                    {
                        MainWindow.messages.Add(sender + ": " + text);

                    };

                    Application.Current.Dispatcher.Invoke(action);
                }
            }
            if (command == "Send Message")
            {
                string str = strings[3];
                Action action = () =>
                {
                    MainWindow.messages.Add(login + ": " + str);

                };

                Application.Current.Dispatcher.Invoke(action);
            }
            //MessageBox.Show(String.Join(";", strings));
        }
    }
}
