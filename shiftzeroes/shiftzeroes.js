#!/usr/bin/env node

process.exitCode = (function (args) {
    let result = 0;
    let arrayToShift = [];

    const writeOut = (str) => process.stdout.write(str);
    const writeErr = (str) => process.stderr.write(str);

    if (args !== null && args.length > 0)
    {
        for (let i = 0; i < args.length; i++)
        {
            if (isNaN(args[i]))
            {
                writeErr("Argument is not a number: '" + args[i] + "'\n");
                result = 1;
            }
            else
            {
                arrayToShift.push(args[i]);
            }
        }
    }

    if (result == 0 && arrayToShift.length < 1)
    {
        writeErr("Nothing to shift.\n");
        result = 1;
    }

    if (result === 0)
    {
        let src_index = 0;
        let dst_index = 0;

        for (src_index = 0; src_index < arrayToShift.length; src_index++)
        {
            if (arrayToShift[src_index] == 0)
            {
                for (let i = src_index; i > dst_index; i--)
                {
                    arrayToShift[i] = arrayToShift[i - 1];
                }

                arrayToShift[dst_index++] = 0;
            }
        }

        arrayToShift.forEach(
            (value) => writeOut(value + "\n"));
    }

    return result;
})(process.argv.slice(2));