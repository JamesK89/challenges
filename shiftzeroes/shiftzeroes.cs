using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;

namespace ShiftZeroes
{
    public sealed class Program
    {
        [STAThread]
        private static int Main(string[] args)
        {
            int result = 0;

            try
            {
                result = (new Program(args)).Run();
            }
            catch (System.Exception ex)
            {
                result = 1;
                Console.Error.WriteLine(ex.ToString());
            }

            return result;
        }

        private Program(string[] args)
        {
            Instance = this;

            StringBuilder invalidArguments = new StringBuilder();

            if (args != null)
            {
                int number;
                List<int> numbers = new List<int>();

                for (int i = 0; i < args.Length; i++)
                {
                    if (int.TryParse(args[i], out number))
                    {
                        numbers.Add(number);
                    }
                    else
                    {
                        invalidArguments.AppendLine($"Argument is not a number: '{args[i]}'");
                    }
                }

                Numbers = numbers.ToArray();
            }

            if (invalidArguments.Length > 0)
            {
                throw new Exception(invalidArguments.ToString());
            }
        }

        public static Program Instance
        {
            get;
            private set;
        }

        public int[] Numbers
        {
            get;
            private set;
        } = new int[0];

        private int Run()
        {
            if (Numbers == null || Numbers.Length < 1)
                throw new InvalidOperationException(
                    "Nothing to shift.");

            int src_index = Numbers.Length - 1;
            int dst_index = Numbers.Length - 1;

            while (src_index >= 0)
            {
                if (Numbers[src_index] != 0)
                {
                    Numbers[dst_index--] = Numbers[src_index];
                }

                src_index--;
            }

            while (dst_index >= 0)
            {
                Numbers[dst_index--] = 0;
            }

            Array.ForEach(Numbers, (n) => Console.WriteLine(n.ToString()));

            return 0;
        }
    }
}