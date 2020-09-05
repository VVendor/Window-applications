using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Notepad
{
    public partial class Form1 : Form
    {
        string filepath;
        public Form1()
        {
            InitializeComponent();
        }

        private void textBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            filepath = string.Empty;
            textBox.Clear();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog ofd = new OpenFileDialog() { Filter = "Text Documents|*.txt",
                ValidateNames = true, Multiselect = false})
            {
                if(ofd.ShowDialog() == DialogResult.OK)
                {
                    try
                    {
                        using (StreamReader reader = new StreamReader(ofd.FileName))
                        {
                            filepath = ofd.FileName;
                            Task<string> text = reader.ReadToEndAsync();
                            textBox.Text = text.Result;
                        }
                    }
                    catch (Exception exception)
                    {
                        MessageBox.Show(exception.Message, "Message", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }
        }

        private async void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(string.IsNullOrEmpty(filepath))
            {
                using (SaveFileDialog sfd = new SaveFileDialog() {Filter = "Text Documents|*.txt",
                    ValidateNames = true })
                {
                    if(sfd.ShowDialog() == DialogResult.OK)
                    {
                        filepath = sfd.FileName;
                    }
                }
            }

            try
            {
                using (StreamWriter writer = new StreamWriter(filepath))
                {
                    await writer.WriteLineAsync(textBox.Text);
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Message", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private async void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (SaveFileDialog sfd = new SaveFileDialog()
            {
                Filter = "Text Documents|*.txt",
                ValidateNames = true
            })
            {
                if (sfd.ShowDialog() == DialogResult.OK)
                {
                    try
                    {
                        using (StreamWriter writer = new StreamWriter(sfd.FileName))
                        {
                            await writer.WriteLineAsync(textBox.Text);
                        }
                    }
                    catch(Exception exception)
                    {
                        MessageBox.Show(exception.Message, "Message", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (aboutBox aboutForm = new aboutBox())
            {
                aboutForm.ShowDialog();
            }
        }
    }
}
