using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PictureHandler
{
    public partial class Form1 : Form
    {
        private List<Bitmap> pictureState = new List<Bitmap>();
        private string progName = "PixelManager";
        private Random random = new Random();
        public Form1()
        {
            InitializeComponent();
            Text = progName;
        }

        private async void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                menuStrip1.Enabled = trackBar1.Enabled = false;
                 pictureBox1.Image = null;
                if(pictureState != null && pictureState.Count > 0)  
                  pictureState.Clear();
                var picture = new Bitmap(openFileDialog1.FileName);
               await Task.Run(() => RunProcessing(picture));
                menuStrip1.Enabled = trackBar1.Enabled = true;
                Text = progName;
            }
        }

        private async void RunProcessing(Bitmap picture)
        {
            var pixelList = GetPixels(picture);
            var pixelsInStep = (picture.Width * picture.Height) / 100;
            var currentPixelsSet = new List<Pixel>(pixelList.Count - pixelsInStep);
            for (int i = 1; i  < trackBar1.Maximum; i++)
            {
                for(int j = 0; j < pixelsInStep; j++)
                {
                    var index = random.Next(pixelList.Count);
                    currentPixelsSet.Add(pixelList[index]);
                    pixelList.RemoveAt(index);
                }
                var currentBitmap = new Bitmap(picture.Width, picture.Height);
                foreach(var pixel in currentPixelsSet)
                {
                    currentBitmap.SetPixel(pixel.Point.X, pixel.Point.Y, pixel.Color);
                }
                pictureState.Add(currentBitmap);
                this.Invoke(new Action(() =>
                {
                    Text =  String.Format($" Processing : {i} %");
                }
                ));
            }
            pictureState.Add(picture);
        }

        private List<Pixel> GetPixels(Bitmap picture)
        {
            var pixels = new List<Pixel>(picture.Width * picture.Height);

            for(int y = 0; y < picture.Height; y++)
            {
                for(int x = 0; x < picture.Width; x++)
                {
                    pixels.Add(new Pixel() {
                        Color = picture.GetPixel(x, y),
                        Point = new Point() {X = x, Y = y }
                    });

                }
            }
            return pixels;
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            if (pictureState == null || pictureState.Count < 1) return;

            pictureBox1.Image = pictureState[trackBar1.Value - 1];
        }
    }
}
