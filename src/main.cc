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
    std::puts("NOTE: set environment DEBUG=true to see how the input number is processed through a program");
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
	std::vector<uint64_t> powers;
	for(uint8_t i = 2; i < argc; ++i) {
	    powers.push_back(std::atoi(argv[i]));
	}
	uint64_t result = primeutil::GetNumber(powers);
	std::printf("The resulting number is %d\n", result);
    } else {
	if(argc < 3) {
	    std::puts("Please supply input number to program");
	}
	uint64_t number = static_cast<uint64_t>(std::atoi(argv[2]));
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
	    Rational result = step * Rational(static_cast<uint64_t>(number));
	    if(debug) {
		std::printf("DEBUG: idx = %llu, %llu/%llu * %llu = %llu/%llu\n", idx,
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

	std::printf("RESULT: %llu\n", number);
    }

    return 0;
}
