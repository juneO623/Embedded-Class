
namespace winform_arduino
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.button9 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(167, 89);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(101, 58);
            this.button1.TabIndex = 0;
            this.button1.Text = "LED 1 ON";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.LED_1_ON);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(167, 200);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(101, 58);
            this.button3.TabIndex = 2;
            this.button3.Text = "LED 1 OFF";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.LED_1_OFF);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(167, 299);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(101, 58);
            this.button5.TabIndex = 4;
            this.button5.Text = "SERVO LEFT";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.SERVO_LEFT);
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(368, 89);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(101, 58);
            this.button7.TabIndex = 0;
            this.button7.Text = "LED 2 ON";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.LED_2_ON);
            // 
            // button8
            // 
            this.button8.Location = new System.Drawing.Point(368, 200);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(101, 58);
            this.button8.TabIndex = 2;
            this.button8.Text = "LED 2 OFF";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Click += new System.EventHandler(this.LED_2_OFF);
            // 
            // button9
            // 
            this.button9.Location = new System.Drawing.Point(368, 299);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(101, 58);
            this.button9.TabIndex = 4;
            this.button9.Text = "SERVO RIGHT";
            this.button9.UseVisualStyleBackColor = true;
            this.button9.Click += new System.EventHandler(this.SERVO_RIGHT);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.button9);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button8);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button button9;
    }
}

