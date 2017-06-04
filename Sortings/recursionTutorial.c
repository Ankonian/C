/*
 * This is a simple tutorial and introduction to recursive
 * functions and how to use the getopt interface to
 * accept command line arguments in C.
 *
 * A recursive function is simply a function which calls itself
 * to compute something. They are extremely useful in programming
 * and sometimes make the code much easier to understand than
 * their iterative (loop) variants.
 *
 * We will be using the fibonacci series to demonstrate
 * recursion because the fibonacci series is the quintessential
 * algorithm for recursion and it suits a recursive function perfectly.
 *
 * Some small review of fibonacci series
 *  0 1 1 2 3 5 8 13 ...
 *
 * fibonacci(n) ==
 *  1. 0 or 1 if n is 0 or 1
 *  2. fibonacci(n-1) + fibonacci(n-2) if n >= 2
 *
 * TODO: Compile Using
 *  cc -Wall -Wextra -Wpedantic -Werror -std=c99 -o recursionTest recursionTutorial.c
 *
 * TODO: 1. Execute Using
 *  ./recursionTest
 *
 * TODO: 2. Execute Using
 *  ./recursionTest -h
 *
 * TODO: 3. Execute Using
 *  ./recursionTest -n 10
 *
 * TODO: 4. Execute Using
 *  ./recursionTest -c
 */
# include <stdio.h>     // Used for printf
# include <stdlib.h>    // Used for atoi
# include <getopt.h>    // Used for getopt, optarg, optopt, opterr

/* This is the default number of fibonacci numbers to be printed */
# define DEFAULT_MAX_NUMBER         (15)

/**
 * This is a recursive function which calculates the nth
 * fibonacci number. As this is a recursive function, we include
 * a base case and if the base case is not matched, a smaller
 * recursive call to the function is made. This step is repeating
 * until the function is called with the base case in which case
 * the function returns with the given value.
 *
 * @param number The nth fibonacci number to be found
 * @return The nth fibonacci number
 */
unsigned int
fibonacci(unsigned int number)
{
    /*
     * If the number passed is 0 or 1 (which are the first two fibonacci numbers),
     * then we return the number itself. This makes sense because we can't go any
     * smaller than these numbers in the fibonacci sequence.
     */
    if (number == 0 || number == 1) {
        return number;
    }

    /*
     * In this case, we know fibonacci(n) = fibonacci(n-1) + fibonacci(n-2) and
     * this is exactlty what we return. This makes a recursive call to the
     * function albeit with a smaller n. As this keeps getting repeated, the function
     * is eventually called with n == 0 and n == 1 at which point it returns those
     * values and they join up together until the original point when the first
     * recursive call was made.
     */
    return fibonacci(number - 1) + fibonacci(number - 2);
}

/**
 * Prints a helpful message to the user which shows the user
 * how to use the program.
 */
void
printUsage()
{
    printf("Usage: ./recursionTest OR ./recursionTest -h OR ./recursionTest -n N {N=integer}\n");
}

/**
 * The main function collects the arguments for the program
 * and it uses the getopt interface to make parsing command
 * line arguments very simple.
 *
 * In Unix, the command line arguments work by telling us the
 * number of arguments and the value of each argument stored
 * as a string in a 2D array.
 *
 * @param argc The number of command line arguments
 * @param argv The value of each command line argument
 * @return Zero or Error
 */
int
main(int argc, char *argv[])
{
    int option;
    int maxNumber;
    int numberFlag = 0;

    /*
     * The getopt interface is used to ease the process of collecting
     * command line arguments. Command line arguments are the arguments
     * passed to the program when the program is called from the terminal.
     *
     * We use the function 'getopt' (found in getopt.h) which parses the
     * arguments we are given from the command line. It returns the character
     * which comes next in the argument list or -1 if there are no more
     * arguments.
     *
     * Hence, we setup a loop where we keep calling this function until
     * we get a -1 and then we exit the loop.
     *
     * NOTE: Command line arguments are given a preceding minus sign {-n, -c, etc.}
     */

    /*
     * The 'getopt.h' header file defines a few global variables for us
     * which we can use.
     *
     * optopt
     *  This variable gets set to the argument we have last read.
     *
     * optarg
     *  In case we want are command line option (like -n) too accept a value,
     *  then getopt stores that value in optarg and we can use it.
     *
     * opterr
     *  This variable allows use to manage and handle errors made by the
     *  user when passing in arguments. If we set this variable to 0, then
     *  we suppress the error message printed by the getopt interface.
     */
    opterr = 0;     // We want to suppress the getopt errors

    /*
     * The getopt function takes in the number of arguments (argc), an array
     * of C-style strings (argv), and a format string which specifies our
     * parsing options ("hn:")
     *
     * The "hn:" string tells getopt that 'h' and 'n' are flags and the colon after
     * 'n' tells getopt that 'n' accepts a value from the user.
     * Eg:
     *  option = getopt(argc, argv, "abc:d:");
     *  This function call means that getopt should look for the options
     *  {-a, -b, -c, -d} and that '-c' and '-d' should have a value associated
     *  with them after the option.
     *
     * In case getopt sees a '-c' or a '-d', it will store the parameter which
     * follows those options in the global variabe 'optarg' which we can then
     * use to set our variables however we like.
     *
     * So in our case, we tell getopt that we only accept the '-n' and the '-h'
     * option and that there should be a value associated with the 'n' flag. For us,
     * '-n' is used to specify how many fibonacci numbers we want to print and -h
     * is to print a help message.
     */
    while ((option = getopt(argc, argv, "hn:")) != -1)
    {
        /*
         * Here we setup a switch...case construct and go through what getopt
         * returned. If it returns a 'n', that means that the user wants to set
         * the max number of fibonacci numbers we want to print.
         *
         * Because we specified the ":" after the 'n' in our getopt format string
         * getopt sets the optarg variable to be equal to what comes after the
         * '-n' option and we set that as our maxNumber then.
         */
        switch (option)
        {
            case 'n':
            {
                /*
                 * Confirm in case this flag was already set and the user decided to
                 * set the flag again.
                 */
                if (numberFlag)
                {
                    fprintf(stderr, "[ARGUMENT ERROR] Value for option already set {-n: %d}\n", maxNumber);
                    return 3;
                }

                /*
                 * The 'atoi' function (found in stdlib.h) converts a string to an integer
                 * and returns its value.
                 *
                 * Remember, all command line arguments (stored in argv) are strings and
                 * hence, if we need to take in an int, we need to convert the argument
                 * from a string to an integer.
                 */
                maxNumber = atoi(optarg);
                if (maxNumber == 0)
                {
                    numberFlag = 0;
                }
                else
                {
                    numberFlag = 1;
                }

                /*
                 * As this is a switch...case construct, we need to break after each
                 * case so that we don't fall through to the other cases.
                 */
                break;
            }
            case 'h':
            {
                /*
                 * Print a helpful message on how to use the program and then
                 * exit the program.
                 */
                printUsage();
                return 0;
            }
            case '?':
            {
                /*
                 * In case getopt did not recognize an option in the command line
                 * parameters, it returns a '?'.
                 *
                 * Over here we can check if 'optopt' is 'n' and that means that a value
                 * was not supplied to '-n' option and hence, we print a message.
                 *
                 * In case 'optopt' is not 'n', then it means some unknown argument
                 * was provided to the program by the user.
                 *
                 * In either case we have an error and hence we return from the main
                 * function.
                 */
                if (optopt == 'n')
                {
                    if (numberFlag) {
                        fprintf(stderr, "[ARGUMENT ERROR] Value for option already set {-n: %d}\n\n", maxNumber);
                    }
                    else
                    {
                        fprintf(stderr, "[ARGUMENT ERROR] Value for option not supplied {-n}\n\n");
                    }
                }
                else
                {
                    fprintf(stderr, "[ARGUMENT ERROR] Unknown option supplied {-%c}\n\n", optopt);
                }
                printUsage();

                /*
                 * As we return and exit the main function right here, we don't need to
                 * add the break statement here.
                 */
                return 1;
            }
            default:
            {
                /*
                 * This case should never be encountered, but it is still there
                 * in case something screws up real bad.
                 */
                fprintf(stderr, "[UNKNOWN ERROR] Something very bad happened\n");
                return 2;
            }
        }
    }

    /*
     * In case the maxNumber was not changed by an argument, we use
     * the default value, which is DEFAULT_MAX_NUMBER {15}.
     */
    if (numberFlag)
    {
        printf("[MAX NUMBER] Displaying the first %d Fibonacci Numbers\n", maxNumber);
    }
    else
    {
        maxNumber = DEFAULT_MAX_NUMBER;
        printf("Default Value of maxNumber {%d} being used\n", DEFAULT_MAX_NUMBER);
    }

    /*
     * Now, we simply go through in a for loop and print the
     * first maxNumber number of fibonacci numbers using the
     * recursive fibonacci call we wrote earlier.
     */
    for (int i = 0; i < maxNumber; i++)
    {
        printf("%u ", fibonacci(i));
    }
    printf("\n");

    return 0;
}
