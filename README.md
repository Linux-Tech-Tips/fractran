# FRACTRAN Interpreter

This project is a small interpreter written in C++ using a custom Rational number class for the FRACTRAN esolang,
invented by John Conway in 1972.

More details on FRACTRAN can be found on its [wikipedia article](https://en.wikipedia.org/wiki/FRACTRAN).

## Sample Programs

With the project, 3 sample programs are provided:

- PRIMEGAME.txt ... contains the fractions of Conway's original PRIMEGAME program
- add.txt ......... number addition
- multiply.txt .... number multiplication

## Interpreter Functionality

The 'fractran.elf' output program provides the following functionality:

**Running a program:**

Given a filename and input number as the first 2 arguments, and optionally an iteration limit as the third,
the interpreter processes the input number through the fractions listed in the text file, as per FRACTRAN rules.

The filename is expected to be a list of fractions, each on a separate line, using the '/' symbol to separate the numerator and denominator.

If the environment variable `DEBUG=true` is set, the program prints each step as it interprets the fractions to the console.

**Getting a prime factorisation:**

The argument 'decompose' followed by a number calculates and prints out the prime factorisation of the given number.

This can be used to obtain the FRACTRAN output values given the numeric result of running a FRACTRAN program.

**Getting a FRACTRAN input from prime powers:**

The argument 'vars' followed by a list of numbers calculates and prints the input number for a FRACTRAN program,
setting the implicit 'variables' to the given numbers.

In essence, given a list of numbers `n_1, n_2, n_3, ... n_N` it generates a number that is
the product of the first N primes, exponentiated to the given `n_k`.

## Limits

The program is meant for educational purposes and as a learning experience, and therefore is very limited.

It uses a 64-bit unsigned integer type, meaning any multiplication that leads to a number greater or equal to `2^64` causes an error.
