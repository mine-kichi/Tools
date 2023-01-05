using System;
using System.IO;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Diagnostics;

namespace summary_extractor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 日々書き込んでいくファイル作成関数。
        /// フォルダ指定機能作成予定
        /// ファイル名も日付にする予定
        /// </summary>
        private void makeFileBtn(object sender, EventArgs e)
        {

            // 日付取得
            DateTime dt = DateTime.Now;
            Console.WriteLine(dt.ToString("yyyy/MM/dd"));
            string path = dt.ToString("yyyyMMdd") + ".md";
            // FileInfoのインスタンスを生成する
            FileInfo fileInfo = new FileInfo(path);
            if (File.Exists(path))
            {
                MessageBox.Show("日付ファイルはすでに存在します");
            }
            else {
                // ファイルを作成する
                FileStream fileStream = fileInfo.Create();
            }

            // ToDo
            path = "ToDo.md";
            // FileInfoのインスタンスを生成する
            fileInfo = new FileInfo(path);
            if (File.Exists(path))
            {
                MessageBox.Show("ToDoファイルはすでに存在します");
            }
            else
            {
                // ファイルを作成する
                FileStream fileStream = fileInfo.Create();
            }

            // QA
            path = "QA.md";
            // FileInfoのインスタンスを生成する
            fileInfo = new FileInfo(path);
            if (File.Exists(path))
            {
                MessageBox.Show("QAファイルはすでに存在します");
            }
            else
            {
                // ファイルを作成する
                FileStream fileStream = fileInfo.Create();
            }

            // other
            path = "other.md";
            // FileInfoのインスタンスを生成する
            fileInfo = new FileInfo(path);
            if (File.Exists(path))
            {
                MessageBox.Show("otherファイルはすでに存在します");
            }
            else
            {
                // ファイルを作成する
                FileStream fileStream = fileInfo.Create();
            }


        }

        /// <summary>
        /// 抽出ボタン実行部
        /// </summary>
        private void extractBtn(object sender, EventArgs e)
        {
            int flg = 0;
            int type = 0;
            List<string> list = new List<string>();
            // ファイルを一行ずつ読み込み
            foreach (string line in System.IO.File.ReadLines(@"./20230104.md"))
            {
                if( flg == 0)
                {
                    //<Todo/>開始
                    //</Todo>終わり
                    if (line == "<Todo/>")
                    {
                        type = 1;
                        flg = 1;
                    }else if(line == "<QA/>"){
                        type = 2;
                        flg = 1;
                    }else if(line == "<other/>"){
                        type = 3;
                        flg = 1;
                    }

                }
                else
                {
                    if (line == "</Todo>" || line == "</QA>" || line == "</other>")
                    {
                        additionSentence(flg, list);
                        //初期化
                        type = 0;
                        flg = 0;
                        list = new List<string>(); 
                    }

                    list.Add(line);

                }

            }

        }

        /// <summary>
        /// ファイルに抽出事項を追記する関数
        /// </summary>
        private void additionSentence(int flg, List<string> S)
        {
            string path;
            // ファイルオープン
            if(flg == 1)
            {
                path = @"ToDo.md";
            }
            else if( flg == 2)
            {
                path = @"QA.md";

            }
            else
            {
                path = @"other.md";
            }

            // 追記
            foreach (string s in S)
            {

                File.AppendAllText(path, s+Environment.NewLine);
            }

        }


        /// <summary>
        /// 
        /// </summary>
        private void closeBtn(object sender, EventArgs e)
        {
            this.Close();
        }

        /// <summary>
        /// close
        /// </summary>
        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
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

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            ProcessStartInfo pInfo = new ProcessStartInfo();
            pInfo.FileName = "notepad";
            pInfo.Arguments = textBox1.Text;

            Process.Start(pInfo);
        }
    }
}
