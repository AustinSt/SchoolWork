using System;
using System.Linq;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;
namespace GridThread
{
    class Program
    {
        const int NR = 5 + 2;
        const int NC = 5 + 2;
        const int seed = 4;
        const int high = 14;
        const int gen = 10;
        
        
        static void Main(string[] args)
        {
            Stopwatch stopWatch = new Stopwatch();//timing
            stopWatch.Start();
            int[,] A = new int[NR, NC];
            int[,] B = new int[NR, NC];
            int count1 = 0;
            int[] TN = new int[11];
           
            A = fillGrid(A);//fills with 0's and numbers
            B = fillGrid(B);//same
            Barrier barrier = new Barrier(1);//for barrier
            Console.WriteLine("Gen {0}", count1);
            for (int i = 0; i < NR; i++)//first print
            {
                for (int k = 0; k < NC; k++)
                {
                    Console.Write(" {0,3} ", A[i, k]);
                }
                Console.WriteLine();
            }
            Console.WriteLine();
            Console.WriteLine();
            A = B;
            int number = 0;
            do
            {
                Parallel.For(1, NR-1, count =>//first parallel for 
                 {
                     Parallel.For(1, NC - 1, count2 =>//nested parallel for
                         {
                             B[count, count2] = checker(A, count, count2);//goes to function for changing grid
                         }
                     );
                     number = Process.GetCurrentProcess().Threads.Count;//grabs thread count
                 }
                );
                TN[count1] = number;//put into array for printing later
                
                barrier.SignalAndWait();//barrier
                Console.WriteLine("Gen {0}", count1+1);
                for (int i = 0; i < NR; i++)
                {
                    for (int k = 0; k < NC; k++)
                    {
                        Console.Write(" {0,3} ", B[i, k]);
                    }
                    Console.WriteLine();
                }
                Console.WriteLine();
                Console.WriteLine();
                A = B;//copy
                count1++;
                number = 0;
            } while (count1 < gen);
            stopWatch.Stop();
            TimeSpan ts = stopWatch.Elapsed;
            string elapsedTime = String.Format("{0:00}:{1:00}:{2:00}.{3:00}",
            ts.Hours, ts.Minutes, ts.Seconds,
            ts.Milliseconds / 10);
            Console.WriteLine("RunTime " + elapsedTime);//printing out time of program
            Console.WriteLine("--------------------------------");
            Console.WriteLine("Amount of Threads per run: ");
            for (int i = 0; i < gen; i++)
            {
                Console.WriteLine(" Gen: {0} -  {1} ", i+1, TN[i]);
            }
            
            Console.WriteLine("--------------------------------");
        }

        public static int[,] fillGrid(int[,] A)//fills with 0's then numbers
        {
            var rand = new Random(seed);
            for(int i = 0; i < NR; i++)
            {
                for(int k = 0; k < NC; k++)
                {
                    A[i, k] = 0;
                    
                }
                
            }
           
            for (int i = 1; i < NR-1; i++)
            {
                for (int k = 1; k < NC-1; k++)
                {
                    A[i, k] = rand.Next(high);
                   
                }
               
            }
            
            return A;
        }
        public static int checker(int[,] GridA, int i, int k)//algorithm for changing numbers in grid per generation
        {
            int initial = GridA[i, k];
            int left = GridA[i, k - 1];//left of number
            int right = GridA[i, k + 1];//right of number
            int up = GridA[i - 1, k];//above number in grid
            int down = GridA[i + 1, k];//below number in grid
            int leftUp = GridA[i - 1, k - 1];//top left
            int rightUp = GridA[i - 1, k + 1];//top right
            int leftDown = GridA[i + 1, k - 1];//bottom left
            int rightDown = GridA[i + 1, k + 1];//bottom right
            int addAll = initial + left + right + up + down + leftUp + rightUp + leftDown + rightDown;
            Thread.Sleep(100);//sleep in ms
            if (addAll % 10 == 0)
            {
                return 0;
            }
            if (addAll < 50)
            {
                return initial + 3;
            }
            if (addAll > 50 && addAll < 150)
            {
                initial = initial - 3;
                if (initial <= 0)
                {
                    return 0;
                }
                else
                {
                    return initial;
                }
            }
            if (initial > 150)
            {
                return 1;
            }
            
           
            return -1;
           
        }
        
    }
    
}
