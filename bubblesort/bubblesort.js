#!/usr/bin/env node

process.exitCode = (function (args) {
    let result = 0;
    let arrayToSort = [];

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
                arrayToSort.push(args[i]);
            }
        }
    }

    if (result == 0 && arrayToSort.length < 1)
    {
        writeErr("Nothing to sort.\n");
        result = 1;
    }

    if (result === 0)
    {
        let sorted = false;

        do
        {
            sorted = false;

            for (let i = 0; i < arrayToSort.length - 1; i++)
            {
                if (arrayToSort[i + 1] < arrayToSort[i])
                {
                    // XOR swap algorithm.
                    // I think this would not be practical to use in real world applications
                    // but it is just too cool not to demonstrate in this particular case.
                    arrayToSort[i] = arrayToSort[i] ^ arrayToSort[i + 1];
                    arrayToSort[i + 1] = arrayToSort[i + 1] ^ arrayToSort[i];
                    arrayToSort[i] = arrayToSort[i] ^ arrayToSort[i + 1];

                    sorted = true;
                }
            }
        } while (sorted);

        arrayToSort.forEach(
            (value) => writeOut(value + "\n"));
    }

    return result;
})(process.argv.slice(2));