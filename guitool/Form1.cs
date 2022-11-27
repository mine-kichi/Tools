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

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        /// <summary>
        /// ボタン
        /// </summary>
        private void button1_Click(object sender, EventArgs e)
        {
         
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Process p = new Process();

            p.StartInfo.FileName = "Test.bat";
            p.StartInfo.Verb = "RunAs"; //管理者として実行する場合

            p.Start();


        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void ライセンスToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("テスト");
        }

        private void 終了ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();

        }
    }
}
