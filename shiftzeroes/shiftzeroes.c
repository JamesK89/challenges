#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

#ifndef TRUE
#   define TRUE 1
#endif

#ifndef FALSE
#   define FALSE 0
#endif

#define RET_ERROR   INT_MAX

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

int get_numbers(int numValues, const char** values, int** numbers)
{
    int result = 0;
    int err = FALSE;
    int i, j;

    if (numbers)
        *numbers = NULL;

    if (values && numValues && numbers)
    {
        for (i = 0; i < numValues; i++)
        {
            if (is_valid_number(values[i]))
            {
                result++;
            }
            else
            {
                fprintf(stderr, "Argument is not a number: '%s'\n", values[i]);
                err = TRUE;
            }
        }

        if (!err && result)
        {
            *numbers = (int*)malloc(sizeof(int) * result);

            if (numbers)
            {
                j = 0;

                for (i = 0; i < numValues; i++)
                {
                    if (is_valid_number(values[i]))
                    {
                        (*numbers)[j++] = strtol(values[i], NULL, 10);
                    }
                }
            }
            else
            {
                result = RET_ERROR;
            }
        }
        else if (err)
        {
            result = RET_ERROR;
        }
    }

    return result;
}

int main(int argc, const char** argv)
{
    int result = 0;
    int* numbers = NULL;
    int numNumbers, i;
    int sorted = FALSE;
    int src_index, dst_index;

    numNumbers = get_numbers(argc - 1, &argv[1], &numbers);
    
    if (numNumbers == RET_ERROR)
    {
        result = 1;
    }
    else if (!numNumbers)
    {
        fprintf(stderr, "Nothing to sort.\n");
        result = 1;
    }
    else if (!numbers)
    {
        fprintf(stderr, "Failed to allocate memory.\n");
        result = 1;
    }

    if (result == 0)
    {
        src_index = numNumbers - 1;
        dst_index = numNumbers - 1;

        while (src_index >= 0)
        {
            if (numbers[src_index] != 0)
            {
                numbers[dst_index--] = numbers[src_index];
            }

            src_index--;
        }
        
        while (dst_index >= 0)
        {
            numbers[dst_index--] = 0;
        }

        for (i = 0; i < numNumbers; i++)
            printf("%i\n", numbers[i]);
    }

    if (numbers)
        free(numbers);

    return result;
}