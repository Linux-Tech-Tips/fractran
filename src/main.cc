/* TODO Fractran make it work!! 
 * -> reads in a number
 * -> reads in fractions from a string cli input
 * -> runs the program either for N iterations or until end, then prints out state
 *
 * -> able to decompose number into prime factors, or build a number based on given variables
 *
 * -> CLI args: fractran with either file or stdin
 *              decompose num
 *              vars list of nums
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "PrimeUtil.hh"
#include "Rational/Rational.hh"

void printHelp() {
    std::puts("Command line arguments:");
    std::puts("decompose <num> .......... get prime factorisation");
    std::puts("vars <num1, num2, ...> ... get number input from variable values");
    std::puts("<filename> <number> ...... program to read in and execute with the given number input");
}

int main(int argc, char * argv[]) {

    if(argc < 2) {
	printHelp();
	return 1;
    }

    char * debugVar = std::getenv("DEBUG");
    bool debug = (debugVar != nullptr && std::strcmp(debugVar, "true") == 0);

    if(std::strcmp(argv[1], "decompose") == 0) {
	if(argc < 3) {
	    std::puts("Please supply number to decompose");
	    return 1;
	}
	auto result = primeutil::GetPrimeFactors(std::atoi(argv[2]));
	std::printf("Prime decomposition: ");
	for(auto f : result) {
	    std::printf("%d^%d ", f.first, f.second);
	}
	std::putchar('\n');
    } else if(std::strcmp(argv[1], "vars") == 0) {
	if(argc < 3) {
	    std::puts("Please supply at least one variable value");
	    return 1;
	}
	std::vector<uint32_t> powers;
	for(uint8_t i = 2; i < argc; ++i) {
	    powers.push_back(std::atoi(argv[i]));
	}
	uint64_t result = primeutil::GetNumber(powers);
	std::printf("The resulting number is %d\n", result);
    } else {
	if(argc < 3) {
	    std::puts("Please supply input number to program");
	}
	uint32_t number = static_cast<uint32_t>(std::atoi(argv[2]));
	std::vector<Rational> program;
	std::ifstream programFile(argv[1]);

	std::string fraction;
	while(std::getline(programFile, fraction)) {
	    program.push_back(fraction);
	}
	programFile.close();

	size_t idx = 0;
	while(idx < program.size()) {
	    Rational step = program[idx];
	    Rational result = step * Rational(static_cast<int>(number));
	    if(debug) {
		std::printf("DEBUG: idx = %d, %d/%d * %d = %d/%d\n", idx,
			    step.getNumerator(), step.getDenominator(), number,
			    result.getNumerator(), result.getDenominator());
	    }
	    if(result.getDenominator() == 1) {
		number = result.getNumerator();
		idx = 0;
	    } else {
		++idx;
	    }
	}

	std::printf("RESULT: %d\n", number);

	// TODO Implement factran interpreter
	// might actually need to use a larger/infinite precision data type or something idk
	// what to do here:
	// -> load file, read file lines into std::vector of Rational instances
	// go through all fractions and multiply, if result whole number, reset and replace current n with result, if not, move on to the next fraction
	// once end reached, end the loop
    }

    return 0;
}
