/**
 * @file PrimeUtil.hh
 * @author Martin
 * @brief File containing utility functions for prime numbers
*/
#ifndef PRIMEUTIL_H
#define PRIMEUTIL_H

#include <vector>
#include <map>
#include <set>
#include <cstdint>

#define PRIME_REGEN_COEF 1.5f

namespace {

std::set<uint64_t> generatedNumbers;
uint64_t currentMax = 100;

std::vector<uint64_t> primes;

uint64_t primeIdx = 0;

uint64_t IntegerPower(uint64_t base, uint64_t exp) {
    /* Base cases */
    if(exp == 0)
	return 1;
    if(exp == 1)
	return base;

    /* Do black magic */
    uint64_t tmp = IntegerPower(base, exp/2);
    if(exp % 2 == 0)
	return tmp * tmp;
    return base * tmp * tmp;
}

void GeneratePrimes(uint64_t max) {
    /* Regenerate multiples of existing primes up to max */
    for(uint64_t prime : primes) {
	uint64_t n = prime, j = 1;
	while(n < max) {
	    generatedNumbers.insert(n);
	    n = prime * ++j;
	}
    }
    /* Loop through all the numbers in existence or something idk */
    for(uint64_t i = 2; i < max; ++i) {
        if(generatedNumbers.count(i) == 0) {
            primes.push_back(i);
            uint64_t n = i, j = 1;
            while(n < max) {
                generatedNumbers.insert(n);
                n = i * ++j;
            }
        }
    }
}

uint64_t GetNextPrime() {
    /* Get prime if exists */
    if(primeIdx < primes.size()) {
        return primes[primeIdx++];
    }
    /* Generate more primes if not enough found */
    GeneratePrimes(currentMax);
    currentMax *= PRIME_REGEN_COEF;
    return primes[primeIdx++];
}

} /* anonymous namespace */

namespace primeutil {

uint64_t GetNumber(std::vector<uint64_t> powers) {
    primeIdx = 0;
    uint64_t total = 1;
    for(uint64_t num : powers) {
	total *= IntegerPower(GetNextPrime(), static_cast<int64_t>(num));
    }
    return total;
}

std::map<uint64_t, uint64_t> GetPrimeFactors(uint64_t number) {
    std::map<uint64_t, uint64_t> result;
    primeIdx = 0;
    uint64_t currentPrime = GetNextPrime();
    while(number > 1) {
	if(number % currentPrime == 0) {
	    number /= currentPrime;
	    if(result.count(currentPrime) > 0) {
		++result[currentPrime];
	    } else {
		result[currentPrime] = 1;
	    }
	} else {
	    currentPrime = GetNextPrime();
	}
    }
    return result;
}

} /* namespace primeutil */

#endif /* PRIMEUTIL_H */
