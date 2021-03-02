using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;

namespace BubbleSort
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
                    "Nothing to sort.");

            bool sorted = false;

            do
            {
                sorted = false;

                for (int i = 0; i < Numbers.Length - 1; i++)
                {
                    if (Numbers[i + 1] < Numbers[i])
                    {
                        // XOR swap algorithm.
                        // I think this would not be practical to use in real world applications
                        // but it is just too cool not to demonstrate in this particular case.
                        Numbers[i] = Numbers[i] ^ Numbers[i + 1];
                        Numbers[i + 1] = Numbers[i + 1] ^ Numbers[i];
                        Numbers[i] = Numbers[i] ^ Numbers[i + 1];

                        sorted = true;
                    }
                }
            } while (sorted);

            Array.ForEach(Numbers, (n) => Console.WriteLine(n.ToString()));

            return 0;
        }
    }
}