using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace relation_visualizer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //下記のPythonスクリプトへのファイルパスを記述する
            string myPythonApp = textBox1.Text;

/*            int x = 2;
            int y = 5;
*/
            
            var myProcess = new Process
            {
                StartInfo = new ProcessStartInfo("python3.exe")
                {
                    UseShellExecute = false,
                    RedirectStandardOutput = true,
                    Arguments = myPythonApp
//                    Arguments = myPythonApp + " " + x + " " + y
                }
            };

            myProcess.Start();
//            StreamReader myStreamReader = myProcess.StandardOutput;
//            string myString = myStreamReader.ReadLine();
//            myProcess.WaitForExit();
//            myProcess.Close();

//            Console.WriteLine("Value received from script: " +myString);


        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string openFileName;

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                openFileName = openFileDialog1.FileName;
            }
            else
            {
                return;
            }

            textBox1.Clear();
            textBox1.Text = openFileName;

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
