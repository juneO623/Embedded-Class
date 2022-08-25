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

        static byte[,] background = new byte[22, 12]
        {
            {1,1,1,1,1,1,1,1,1,1,1,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,0,0,0,0,0,0,0,0,0,0,1 },
            {1,1,1,1,1,1,1,1,1,1,1,1 },
        };

        //static byte[,] block_L = new byte[4, 4] {
        //                                {0,0,0,0},
        //                                {0,1,0,0},
        //                                {0,1,1,1},
        //                                {0,0,0,0}};

        static byte[,,] block_L = new byte[4, 4, 4]
        {
            {
                {0,0,0,0},
                {0,1,0,0},
                {0,1,1,1},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,0,0},
                {0,1,0,0}
            },
            {
                {0,0,0,0},
                {0,1,1,1},
                {0,0,0,1},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,0,1,0},
                {0,0,1,0},
                {0,1,1,0}
            },
        };

        static int x = 3;
        static int y = 3;

        static int rotate = 0;


        static void Main(string[] args)
        {
            ConsoleKeyInfo key_value;
            String ch;


            make_background();
            
            make_block();

            while (true)
            {
                if (Console.KeyAvailable)
                {

                    key_value = Console.ReadKey(true);
                    ch = key_value.Key.ToString();

                    if (ch == "A")
                    {
                        if (overlab_check(-1, 0) == 0)
                        {
                            delete_block();
                            x--;
                            make_block();
                            //Console.WriteLine("a");
                        }
                    }
                    else if (ch == "D")
                    {
                        if (overlab_check(1, 0) == 0)
                        {
                            delete_block();
                            x++;
                            make_block();
                            //Console.WriteLine("d");
                        }
                    }
                    else if (ch == "S")
                    {
                        if (overlab_check(0, 1) == 0)
                        {
                            delete_block();
                            y++;
                            make_block();
                            //Console.WriteLine("s");
                        }
                    }
                    else if (ch == "R")
                    {
                        if (overlab_check_rotate() == 0)
                        {
                            delete_block();
                            rotate++;
                            if (rotate > 3) rotate = 0;
                            make_block();
                        }
                        //Console.WriteLine("haha");
                    }
                }

                if (count >= 100)
                {
                    count = 0;
                    if (overlab_check(0, 1) == 0)
                    {
                        delete_block();
                        y++;
                        make_block();
                    }

                }
                Thread.Sleep(10);
                count++;
            }
        }



        static void make_background()
        {
            int x_pos = 0;
            int y_pos = 0;
            for (int j = 0; j < 22; j++)
            {
                for (int i = 0; i < 12; i++)
                {
                    if (background[j, i] == 1)
                    {
                        Console.SetCursorPosition(i + x_pos, j + y_pos);
                        Console.Write("*");
                    }
                    else
                    {
                        Console.SetCursorPosition(i + x_pos, j + y_pos);
                        Console.Write("-");
                    }
                }
                Console.WriteLine();
            }
        }


        static void make_block()
        {
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (block_L[rotate, j, i] == 1)
                    {
                        Console.SetCursorPosition(i + x, j + y);
                        Console.Write("*");
                    }
                    else
                    {
                        Console.SetCursorPosition(i + x, j + y);
                        Console.Write("-");
                    }
                }
                Console.WriteLine();
            }
        }


        static void delete_block()
        {
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (block_L[rotate, j, i] == 1)
                    {
                        Console.SetCursorPosition(i + x, j + y);
                        Console.Write("-");
                    }
                }
                Console.WriteLine();
            }
        }


        static int overlab_check(int tmp_x, int tmp_y)
        {
            int overlap_count = 0;
            for (int j=0; j<4; j++)
            {
                for (int i=0; i<4; i++)
                {
                    if (block_L[rotate, j, i] == 1 && background[j + y + tmp_y, i + x + tmp_x] == 1)
                    {
                        overlap_count++;
                    }
                }
            }
            return overlap_count;
        }

        static int overlab_check_rotate()
        {
            int overlap_count = 0;
            int tmp_rotate = rotate;

            tmp_rotate++;
            if (tmp_rotate > 3) tmp_rotate = 0;

            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (block_L[tmp_rotate, j, i] == 1 && background[j + y, i + x] == 1)
                    {
                        overlap_count++;
                    }
                }
            }
            return overlap_count;
        }

    }
}
