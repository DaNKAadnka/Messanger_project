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
    /// Логика взаимодействия для RegisterWindows.xaml
    /// </summary>
    public partial class RegisterWindows : Window
    {
        public string login;
        public string password;

        public RegisterWindows()
        {
            InitializeComponent();
        }

        public void OnRegistry(object sender, EventArgs e)
        {
            if (loginField.Text != null && passwordField != null && !NetworkModule.instance.isLogin)
            {
                // Отправляется сообщение по протоколу
                // Command:Register
                // Status:Check
                // Data:
                // Login:###
                // Password:##

                string send_message = "Command:Register\n" +
                                      "Status:Check\n" +
                                      "Data:\n" +
                                      "Login:" + loginField.Text + "\n" +
                                      "Password:" + passwordField.Text;


                NetworkModule.instance.SendMessage(send_message);
            }
        }
    }
}
