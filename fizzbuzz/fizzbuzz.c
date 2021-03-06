#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEFAULT_FIZZBUZZ_COUNT  100

#define FL_DIV_NONE     0
#define FL_DIV_BY_THREE (1 << 0)
#define FL_DIV_BY_FIVE  (1 << 1)

#define STR_DIV_THREE_MSG   "Fizz"
#define STR_DIV_FIVE_MSG    "Buzz"

#define STR_DIV_SPACE   1

#ifndef TRUE
#   define TRUE 1
#endif

#ifndef FALSE
#   define FALSE 0
#endif

#define IVN_STATE_SIGN        0
#define IVN_STATE_DIGIT       1
#define IVN_STATE_EXIT        2

int is_valid_number(const char* str)
{
    const char* pStr = str;

    int result = 
        str && *str != '\0' ? TRUE : FALSE;

    int state = IVN_STATE_SIGN;

    int numDigits = 0;

    if (result)
    {
        while (state != IVN_STATE_EXIT && 
            *pStr != '\0')
        {
            switch (state)
            {
                case IVN_STATE_SIGN:
                    if (*pStr == '-' || 
                        *pStr == '+' ||
                        isdigit(*pStr))
                    {
                        state = IVN_STATE_DIGIT;

                        if (isdigit(*pStr))
                            pStr--;
                    }
                    else
                    {
                        result = FALSE;
                        state = IVN_STATE_EXIT;
                    }
                break;
                case IVN_STATE_DIGIT:
                    if (!isdigit(*pStr))
                    {
                        result = FALSE;
                        state = IVN_STATE_EXIT;
                    }
                    else
                    {
                        numDigits++;
                    }
                break;
            }

            pStr++;
        }

        if (numDigits < 1)
            result = FALSE;
    }

    return result;
}

int main(int argc, const char** argv)
{
    int fzCount = DEFAULT_FIZZBUZZ_COUNT;
    int fzFlags = FL_DIV_NONE;

    int result = 0;

    int i, ai;

    if (argc > 1)
    {
        for (ai = 1; ai < argc; ai++)
        {
            if (is_valid_number(argv[ai]))
            {
                fzCount = strtol(argv[ai], NULL, 10);
            }
            else
            {
                fprintf(stderr, "Invalid argument: '%s'\n", argv[ai]);
                result = 1;
            }
        }
    }

    if (fzCount < 1)
    {
        fprintf(stderr, "Number to count up to must be greater than or equal to one.\n");
        result = 1;
    }

    if (result == 0)
    {
        printf("Counting up to %i:\n", fzCount);

        for (i = 1; i <= fzCount; i++)
        {
            if (!(i % 3))
                fzFlags |= FL_DIV_BY_THREE;
            
            if (!(i % 5))
                fzFlags |= FL_DIV_BY_FIVE;

            if (fzFlags)
            {
                if (fzFlags & FL_DIV_BY_THREE)
                    printf(STR_DIV_THREE_MSG);

#if STR_DIV_SPACE
                if ((fzFlags & FL_DIV_BY_THREE) &&
                    (fzFlags & FL_DIV_BY_FIVE))
                    printf(" ");
#endif

                if (fzFlags & FL_DIV_BY_FIVE)
                    printf(STR_DIV_FIVE_MSG);
            }
            else
            {
                printf("%i", i);
            }

            printf("\n");

            fzFlags = FL_DIV_NONE;
        }
    }

    return result;
}