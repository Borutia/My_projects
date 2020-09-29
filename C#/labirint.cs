using System;
using System.Collections.Generic;
using System.ComponentModel.Design;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Threading;

namespace ConsoleApplication11
{
    class Program
    {
        static void CreateMap(ref int[,] maze)
        {
            Random rnd = new Random(DateTime.Now.Millisecond);
            int length = -1;
            var nextPreviousNull = new List<int>();
            var resultPreviousNull = new List<int>();
            int ChisloHodov = 25; 
            int shansTupika = 5; 
            int DimensionMatrix = maze.GetLength(0);
            for (int i = 0; i < DimensionMatrix; i++)
                for (int j = 0; j < DimensionMatrix; j++)
                    maze[i, j] = 1;
            for (int i = 0; i < DimensionMatrix; i++)
            {
                if (i == 0)
                {
                    maze[i, 1] = 0;
                    resultPreviousNull.Add(1);
                    continue;
                };
                if (i + 1 == DimensionMatrix)
                {
                    maze[i, resultPreviousNull[rnd.Next(0, resultPreviousNull.Count)]] = 0;
                    continue;
                };
                nextPreviousNull.Clear();
                for (int x = 0; x < resultPreviousNull.Count; x++)
                {
                    if (x + 1 != resultPreviousNull.Count && rnd.Next(0, shansTupika) == 0) continue;
                    maze[i, resultPreviousNull[x]] = 0;
                    nextPreviousNull.Add(resultPreviousNull[x]);
                    length = rnd.Next(0, resultPreviousNull[x]);
                    for (int j = resultPreviousNull[x] - 1; length != 0; j--)
                    {
                        if (maze[i - 1, j] != 0)
                        {
                            maze[i, j] = 0;
                            nextPreviousNull.Add(j);
                        }
                        else break;
                        length--;
                    };
                    length = rnd.Next(0, DimensionMatrix - 1 - resultPreviousNull[x]);
                    for (int j = resultPreviousNull[x] + 1; length != 0; j++)
                    {
                        if (maze[i - 1, j] != 0)
                        {
                            maze[i, j] = 0;
                            nextPreviousNull.Add(j);
                        }
                        else break;
                        length--;
                    };
                }
 
                resultPreviousNull.Clear();
                for (int k = 0; k < ChisloHodov; k++)
                    resultPreviousNull.Add(nextPreviousNull[rnd.Next(0, nextPreviousNull.Count)]);
                resultPreviousNull = resultPreviousNull.Distinct().ToList();
                for (int h = 0; h < resultPreviousNull.Count; h++)
                {
                    if (resultPreviousNull.Contains(resultPreviousNull[h] + 1))
                        resultPreviousNull.Remove(resultPreviousNull[h] + 1);
                    if (resultPreviousNull.Contains(resultPreviousNull[h] - 1))
                        resultPreviousNull.Remove(resultPreviousNull[h] - 1);
                };
            }
        }

        static void rules()
        {
            Console.WriteLine("Это игра лабиринт! Тебе нужно найти выход из лабиринта который находится в самом низу. " +
                              "Попробуй это сделать! Точки(.) на карте - это пространство где ты можешь ходить. " +
                              "Решетки(#) на карте - это стены, через них ты не можешь ходить.");
            Console.WriteLine("Нажмите любую клавишу");
            Console.ReadKey();
        }
        
        private static bool isRead;
        static void go_game()
        {
            isRead = true;
            Console.CursorVisible = false;
 
            
            int[,] maze = new int[10, 10]; 
            CreateMap(ref maze);  
 
            int x = 1, y = 1;
            while (true)
            {
                Console.Clear();
                for (int i = 0; i < maze.GetLength(0); i++)
                {
                    for (int j = 0; j < maze.GetLength(1); j++)
                    {
                        if (maze[i, j] == 0) Console.Write(".");
                        if (maze[i, j] == 1) Console.Write("#");
 
                    }
                    Console.WriteLine();
                }
                Console.CursorLeft = x;
                Console.CursorTop = y;
                Console.Write("@");
              
                ConsoleKeyInfo ki = Console.ReadKey(true);
                if (ki.Key == ConsoleKey.Escape) break;
                if (ki.Key == ConsoleKey.UpArrow && y == 0) continue;
                if (ki.Key == ConsoleKey.DownArrow && y == maze.GetLength(0) - 1)
                {
                    Console.WriteLine(string.Empty);
                    Console.WriteLine("Вы выиграли!");
                    isRead = false;
                    Console.ReadKey();
                    break;
                };
                if (ki.Key == ConsoleKey.LeftArrow && maze[y, x - 1] == 0) x--;
                if (ki.Key == ConsoleKey.RightArrow && maze[y, x + 1] == 0) x++;
                if (ki.Key == ConsoleKey.UpArrow && maze[y - 1, x] == 0) y--;
                if (ki.Key == ConsoleKey.DownArrow && maze[y + 1, x] == 0) y++;
            }
        }

        static void menu()
        {
            while (true)
            {
                Console.CursorVisible = true;
                Console.WriteLine("\nИгра Лабиринт\n");
                Console.WriteLine("Меню");
                Console.WriteLine("1)Показать правила");
                Console.WriteLine("2)Начать игру");
                Console.WriteLine("3)Выход");
                Console.WriteLine("Выберите пункт меню: ");
                int number;
                while (!int.TryParse(Console.ReadLine(), out number))
                {
                    Console.WriteLine("Ошибка ввода! Введите число из меню: ");
                }
                switch (number)
                {
                    case 1:
                    {
                        rules();
                        break;
                    }
                    case 2:
                    {
                        Thread th = new Thread(go_game);
                        th.Start();
                        Thread.Sleep(10000);
                        if (isRead)
                        {
                            th.Abort();
                            Console.Clear();
                            Console.WriteLine("\nВаше время для прохождения вышло!");
                        }
                        while(Console.KeyAvailable) 
                        {
                            Console.ReadKey(false);
                        }
                        break;
                    }
                    case 3:
                    {
                        Console.WriteLine("До свидания!");
                        System.Environment.Exit(0);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }

        static void Main(string[] args)
        {
            menu();
        }
    }
}