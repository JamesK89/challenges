using System;
using System.Text;

namespace FizzBuzz
{
    public sealed class Program
    {
        public const int DefaultNumberOfFizzBuzz = 100;

        public const string DivideByThreeMessage = "Fizz";
        public const string DivideByFiveMessage = "Buzz";
        public const string DivideSpace = " ";

        [Flags]
        public enum FizzBuzzFlags
        {
            None = 0,
            DivisibleByThree = (1 << 0),
            DivisibleByFive = (1 << 1)
        }

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
                int count = 0;

                for (int i = 0; i < args.Length; i++)
                {
                    if (int.TryParse(args[i], out count))
                    {
                        NumberOfFizzBuzz = count;
                    }
                    else
                    {
                        invalidArguments.AppendLine($"Invalid argument: '{args[i]}'");
                    }
                }
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

        public int NumberOfFizzBuzz
        {
            get;
            private set;
        } = DefaultNumberOfFizzBuzz;

        private int Run()
        {
            if (NumberOfFizzBuzz < 1)
                throw new InvalidOperationException(
                    "Number to count up to must be greather than or equal to one.");

            FizzBuzzFlags fbFlags = FizzBuzzFlags.None;

            Console.WriteLine($"Counting up to {NumberOfFizzBuzz}:");

            for (int i = 1; i < NumberOfFizzBuzz; i++)
            {
                if ((i % 3) == 0)
                    fbFlags |= FizzBuzzFlags.DivisibleByThree;
                
                if ((i % 5) == 0)
                    fbFlags |= FizzBuzzFlags.DivisibleByFive;

                if (fbFlags != FizzBuzzFlags.None)
                {
                    if (fbFlags.HasFlag(FizzBuzzFlags.DivisibleByThree))
                        Console.Write(DivideByThreeMessage);
                    
                    if (fbFlags.HasFlag(
                            FizzBuzzFlags.DivisibleByThree |
                            FizzBuzzFlags.DivisibleByFive) )
                        Console.Write(DivideSpace);

                    if (fbFlags.HasFlag(FizzBuzzFlags.DivisibleByFive))
                        Console.Write(DivideByFiveMessage);

                    Console.WriteLine();
                }
                else
                {
                    Console.WriteLine(i.ToString());
                }

                fbFlags = FizzBuzzFlags.None;
            }

            return 0;
        }
    }
}