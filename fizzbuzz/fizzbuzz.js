#!/usr/bin/env node

const FL_DIVIDE_NONE = 0;
const FL_DIVIDE_BY_THREE = 1;
const FL_DIVIDE_BY_FIVE = 2;

const MSG_DIVIDE_BY_THREE = "Fizz";
const MSG_DIVIDE_BY_FIVE = "Buzz";
const MSG_DIVIDE_SPACE = " ";

const DEFAULT_FIZZBUZZ_COUNT = 100;

process.exitCode = (function (args) {
    let result = 0;
    let fizzBuzzCount = DEFAULT_FIZZBUZZ_COUNT;

    const writeOut = (str) => process.stdout.write(str);
    const writeErr = (str) => process.stderr.write(str);

    if (args !== null && args.length > 0)
    {
        for (let i = 0; i < args.length; i++)
        {
            if (isNaN(args[i]))
            {
                writeErr("Invalid argument: '" + args[i] + "'\n");
                result = 1;
            }
            else
            {
                fizzBuzzCount = args[i];
            }
        }
    }

    if (fizzBuzzCount < 1)
    {
        writeErr("Number to count up to must be greater than or equal to one.\n");
        result = 1;
    }

    if (result === 0)
    {
        writeOut("Counting up to " + fizzBuzzCount + ":\n");

        for (let i = 1; i <= fizzBuzzCount; i++)
        {
            let fzFlag = FL_DIVIDE_NONE;

            if ((i % 3) == 0)
                fzFlag |= FL_DIVIDE_BY_THREE;
            
            if ((i % 5) == 0)
                fzFlag |= FL_DIVIDE_BY_FIVE;
            
            if (fzFlag != FL_DIVIDE_NONE)
            {
                if ((fzFlag & FL_DIVIDE_BY_THREE) != 0)
                    writeOut(MSG_DIVIDE_BY_THREE);

                if ((fzFlag & (FL_DIVIDE_BY_THREE)) != 0 &&
                    (fzFlag & (FL_DIVIDE_BY_FIVE)) != 0)
                    writeOut(MSG_DIVIDE_SPACE);
                
                if ((fzFlag & FL_DIVIDE_BY_FIVE) != 0)
                    writeOut(MSG_DIVIDE_BY_FIVE);

                writeOut("\n");
            }
            else
            {
                writeOut(i + "\n");
            }
        }
    }

    return result;
})(process.argv.slice(2));