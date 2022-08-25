using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Threading;

namespace ConsoleApp2
{
    class Program
    {
        static int count = 0;

        //static byte[] num_byte = new byte[2] { 0x23, 0x37 };
        // unsigned char num_byte[2] = {0x23, 0x37}; // c언어
        static byte[] num_byte = new byte[8] { 0x00, 0x38, 0x44, 0x04, 0x08, 0x10, 0x20, 0x7c };

        // 2차원이여서 [,]
        // 3차원은 [,,], 4차원은 [,,,]
        static byte[,] num_byte_2 = new byte[2, 8]
        {
            {0x00,0x38,0x44,0x04,0x08,0x10,0x20,0x7c },
            { 0x00,0x38,0x44,0x04,0x18,0x04,0x44,0x38 },
        };

        static byte[,] num_byte_3 = new byte[10, 8] {
                { 0x00,0x38,0x44,0x4c,0x54,0x64,0x44,0x38},
                { 0x00,0x10,0x30,0x50,0x10,0x10,0x10,0x7c},
                { 0x00,0x38,0x44,0x04,0x08,0x10,0x20,0x7c},
                { 0x00,0x38,0x44,0x04,0x18,0x04,0x44,0x38},
                { 0x00,0x08,0x18,0x28,0x48,0x7c,0x08,0x08},
                { 0x00,0x7c,0x40,0x78,0x04,0x04,0x44,0x38},
                { 0x00,0x38,0x40,0x40,0x78,0x44,0x44,0x38},
                { 0x00,0x7c,0x04,0x08,0x10,0x20,0x20,0x20},
                { 0x00,0x38,0x44,0x44,0x38,0x44,0x44,0x38},
                { 0x00,0x38,0x44,0x44,0x3c,0x04,0x44,0x38},
            };

        // static byte[]
        //static byte num_byte

        static void Main(string[] args)
        {
            byte num = 0x23;
            // --*- --**

            byte num1 = 0x37;
            // --**-***

            Console.WriteLine("Hello World");
            Thread.Sleep(1000);
            Console.Clear();
            
            Console.WriteLine("Hi !!!");
            Thread.Sleep(1000);
            Console.Clear();

            while (true)
            {
                for (int m=0; m<10; m++)
                {
                    for (int k=0; k<10; k++)
                    {
                        for (int j=0; j<8; j++)
                        {
                            for (int i=0; i<8; i++)
                            {
                                if ((num_byte_3[m, j] & (0x80 >> i)) > 0)
                                {
                                    Console.Write("*");
                                }
                                else
                                {
                                    Console.Write(" ");
                                }
                            }
                            for (int i=0; i<8; i++)
                            {
                                if ((num_byte_3[k, j] & (0x80 >> i)) > 0)
                                {
                                    Console.Write("*");
                                }
                                else
                                {
                                    Console.Write(" ");
                                }
                            }
                            Console.WriteLine();
                        }

                        Thread.Sleep(1000);
                        Console.Clear();
                    }
                }
            }
                //for (int j = 0; j < 8; j++)
                //{
                //    for (int i = 0; i < 8; i++)
                //    {
                //        if ((num_byte_2[1, j] & (0x80 >> i)) > 0)
                //        {
                //            Console.Write("*");
                //        }
                //        else
                //        {
                //            Console.Write("-");
                //        }
                //    }
                //    Console.WriteLine();
                //}

                //Thread.Sleep(1000);
                //Console.Clear();


            //for (int i = 0; i < 8; i++)
            //{
            //    if ((num1 & (0x80 >> i)) > 0)
            //    {
            //        Console.Write("*");
            //    }
            //    else
            //    {
            //        Console.Write("-");
            //    }
            //}





            //while (true)
            //{

            //    Console.WriteLine(count);

            //    count++;

            //    Thread.Sleep(1000);
            //    Console.Clear();
            //}

            Console.ReadLine();
        }
    }
}
