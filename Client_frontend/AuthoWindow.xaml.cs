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
using System.Windows.Shapes;

namespace WpfApp1
{
    /// <summary>
    /// Логика взаимодействия для AuthoWindow.xaml
    /// </summary>
    public partial class AuthoWindow : Window
    {
        public AuthoWindow()
        {
            InitializeComponent();
        }

        public void OnAutho(object sender, EventArgs e)
        {
            if (loginField.Text != null && passwordField != null)
            {
                // Отправляется сообщение по протоколу
                // Command:Register
                // Status:Check
                // Data:
                // Login:###
                // Password:##

                string send_message = "Command:Authorize\n" +
                                      "Status:Check\n" +
                                      "Data:\n" +
                                      "Login:" + loginField.Text + "\n" +
                                      "Password:" + passwordField.Text;


                NetworkModule.instance.SendMessage(send_message);

                MessageBox.Show(send_message);
            }
        }
    }
}
