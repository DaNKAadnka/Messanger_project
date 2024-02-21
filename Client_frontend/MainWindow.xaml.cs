using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


using System.Net.Sockets;
using System.Threading;
using System.Net.Http;
using System.Collections.ObjectModel;
using static System.Net.Mime.MediaTypeNames;
using System.Runtime.Remoting.Contexts;

namespace WpfApp1
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        public static ObservableCollection<string> messages = new ObservableCollection<string>();

        public MainWindow()
        {
            InitializeComponent();
            messagesPanel.ItemsSource = messages;
        }

        protected override void OnContentRendered (EventArgs e)
        {
            base.OnContentRendered(e);
            NetworkModule.instance = new NetworkModule();
        }

        //public async Task<string> RecieveAsync ()
        //{
        //    return await Task.Run(() => Recieve());
        //}

        public void OnSendMessage(object sender, RoutedEventArgs eventArgs)
        {
            string message = clientText.Text;
            if (message != null && NetworkModule.instance.isLogin)
            {
                string send_message = "Command:Send Message\n" +
                                      "Status:Check\n" +
                                      "Data:\n" +
                                      "Sender:" + NetworkModule.instance.login + "\n" +
                                      "Reciever:" + "@All\n" +
                                      "Message:" + message;
                NetworkModule.instance.SendMessage(send_message);
            }

            clientText.Text = "";
        }

        public void Register (object sender, RoutedEventArgs eventArgs)
        {
            RegisterWindows r = new RegisterWindows();
            r.Show();
        }

        public void OnAutho (object sender, RoutedEventArgs eventArgs)
        {
            AuthoWindow authoWindow = new AuthoWindow();
            authoWindow.Show();
        }
        
        public void OnLogOut(object sender, RoutedEventArgs eventArgs)
        {
            NetworkModule.instance.LogOut();
            Dispatcher.BeginInvoke(new Action(() =>
            {
                messages.Clear();
            }));
        }

        public void OnMyAccount(object sender, RoutedEventArgs eventArgs)
        {
            if (NetworkModule.instance.isLogin)
            {
                string account_message = "Hello, " + NetworkModule.instance.login + "!";

                MessageBox.Show(account_message);
            }
            else
            {
                MessageBox.Show("Please, log in to view messages:)");
            }
        }
    }
}
