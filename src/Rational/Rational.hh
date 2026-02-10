/**
 * @file Rational.hh
 * @author Martin
 * @brief File containing the class representing a rational number
*/
#ifndef RATIONAL_H
#define RATIONAL_H

#include <string>
#include <stdexcept>
#include <regex>
#include <numeric>
#include <cstdlib>
#include <cstdint>
#include <cmath>

#define FLOAT_CONVERSION_PRECISION 1000000

/** Rational Number, a signed fraction of two real numbers */
class Rational {

    private:
	/** The numerator of the Rational */
	uint32_t m_a;
	/** The denominator of the Rational */
	uint32_t m_b;
	/** Whether the number is negative */
	bool m_negative;

	/** Utility member function to simplify the fraction */
	void simplify(void) {
	    /* Simplify terms */
	    uint32_t gcd = std::gcd(m_a, m_b);
	    if(gcd > 1) {
		m_a /= gcd;
		m_b /= gcd;
	    }
	    /* Remove sign if zero to ensure unsigned zero */
	    if(m_a == 0 && m_negative)
		m_negative = false;
	}

	/** Static member function that creates a rational instance from a floating point number */
	static Rational fromFloat(float number) {
	    /* Getting unsigned integer representation of float, up to specific precision */
	    uint32_t a = static_cast<uint32_t>(std::abs(number) * FLOAT_CONVERSION_PRECISION);
	    uint32_t b = FLOAT_CONVERSION_PRECISION;
	    bool negative = (number < 0.0f);
	    /* Creating new Rational instance with the given parameters */
	    return Rational {a, b, negative};
	}

	/** Static member function that creates a rational instance from a std::string. 
	  * Accepted string formats are either a decimal number or a fraction of integers separated with a slash.
	  */
	static Rational fromString(std::string number) {
	    /* Checking if string is valid */
	    std::smatch matches;
	    if(std::regex_match(number, matches, std::regex("[-+]?\\d+(\\.\\d+)?"))) {
		/* String is a valid decimal number */
		return Rational::fromFloat(std::stof(number));

	    } else if(std::regex_match(number, matches, std::regex("([-+]?)(\\d+)/(\\d+)"))) {
		/* String is a valid fraction format */
		uint32_t a = std::stoi(matches[2].str());
		uint32_t b = std::stoi(matches[3].str());
		bool negative = (matches[1].str() == "-");
		return Rational {a, b, negative};

	    } else {
		/* String is invalid */
		throw std::runtime_error {"Rational Error: Invalid string format specified!"};
	    }
	}

    public:
	/** Constructor creating a Rational instance from the numerator a, denominator b and sign boolean */
	Rational(uint32_t a, uint32_t b, bool negative = false) : m_a{a}, m_b{b}, m_negative{negative} {
	    if(m_b == 0)
		throw std::runtime_error {"Rational Error: Denominator can't be zero!"};
	    this->simplify();
	}
	/** Constructor creating a Rational instance from an integer */
	Rational(int number) : Rational{static_cast<uint32_t>(number), 1, (number < 0)} {}
	/** Constructor creating a Rational instance from a floating point number */
	Rational(float number) {
	    *this = Rational::fromFloat(number);
	}
	/** Constructor creating a Rational instance from a string, either containing a decimal number or a fraction of integers separated with a slash */
	Rational(std::string number) {
	    *this = Rational::fromString(number);
	}
	/** Constructor creating a Rational instance from a C string */
	Rational(char const * number) {
	    *this = Rational::fromString(number);
	}
	/** Copy constructor */
	Rational(const Rational& other) {
	    *this = other;
	}
	/** Constructor creating a Rational instance set to zero by default */
	Rational(void) {
	    m_a = 0;
	    m_b = 1;
	    m_negative = false;
	}

	/** Returns the numerator of the Rational instance */
	uint32_t getNumerator(void) {
	    return m_a;
	}
	/** Returns the denominator of the Rational instance */
	uint32_t getDenominator(void) {
	    return m_b;
	}
	/** Returns whether the Rational instance is negative */
	bool isNegative(void) {
	    return m_negative;
	}

	/** Switches the sign of the Rational instance */
	Rational& negate(void) {
	    m_negative = !m_negative;
	    return *this;
	}
	/** Inverts the numerator and denominator of the Rational instance */
	Rational& invert(void) {
	    /* Check that the inversion won't result in a zero-division */
	    if(m_a == 0) {
		throw std::runtime_error {"Rational Error: Zero has no inverse element"};
	    }
	    /* Invert a and b */
	    uint32_t oldA = m_a;
	    m_a = m_b;
	    m_b = oldA;
	    return *this;
	}

	/** Returns the floating point representation of the rational number */
	float toFloat(void) {
	    return (m_negative ? -1.0f : 1.0f)*(static_cast<float>(m_a) / static_cast<float>(m_b));
	}

	/** Returns the string representation of the rational number, in the form of "A/B" */
	std::string toString(void) {
	    return (m_negative ? "-" : "") + std::to_string(m_a) + (m_b != 1 ? "/" + std::to_string(m_b) : "");
	}

	/* --- Operators --- */

	Rational& operator=(const Rational& other) {
	    /* Guard self-assignment */
	    if(this == &other) {
		return *this;
	    }

	    /* Copy values and return self */
	    this->m_a = other.m_a;
	    this->m_b = other.m_b;
	    this->m_negative = other.m_negative;
	    return *this;
	}

	/* --- Comparison Operators --- */

	friend bool operator==(const Rational& lhs, const Rational& rhs) {
	    return (lhs.m_a == rhs.m_a && lhs.m_b == rhs.m_b && lhs.m_negative == rhs.m_negative);
	}

	friend bool operator!=(const Rational& lhs, const Rational& rhs) {
	    return !(lhs == rhs);
	}

	friend bool operator<(const Rational& lhs, const Rational& rhs) {
	    /* If the sign is different, return based on sign */
	    if(lhs.m_negative != rhs.m_negative) {
		return lhs.m_negative;
	    }
	    /* If the sign is the same, convert to the same denominator and compare numerators */
	    return (lhs.m_a * rhs.m_b < rhs.m_a * lhs.m_b);
	}

	friend bool operator>(const Rational& lhs, const Rational& rhs) {
	    return (rhs < lhs);
	}

	friend bool operator<=(const Rational& lhs, const Rational& rhs) {
	    return !(rhs < lhs);
	}

	friend bool operator>=(const Rational& lhs, const Rational& rhs) {
	    return !(lhs < rhs);
	}

	/* --- Arithmetic Operators --- */
	Rational& operator+=(const Rational& rhs) {
	    int64_t result = 0;
	    if(this->m_b == rhs.m_b) {
		/* Add sign-corrected numerators if denominators equal */
		result = (this->m_negative ? -1 : 1)*static_cast<int64_t>(this->m_a) + (rhs.m_negative ? -1 : 1)*static_cast<int64_t>(rhs.m_a);
	    } else {
		/* Add sign-corrected denominator-corrected numerators */
		result = (this->m_negative ? -1 : 1)*static_cast<int64_t>(this->m_a * rhs.m_b) + (rhs.m_negative ? -1 : 1)*static_cast<int64_t>(rhs.m_a * this->m_b);
		this->m_b *= rhs.m_b;
	    }
	    /* Set the corresponding a and negative bool */
	    this->m_a = static_cast<uint32_t>(std::abs(result));
	    this->m_negative = (result < 0);
	    /* Simplify the fraction and return reference */
	    this->simplify();
	    return *this;
	}

	Rational& operator*=(const Rational& rhs) {
	    /* Multiply a and b of both sides */
	    this->m_a *= rhs.m_a;
	    this->m_b *= rhs.m_b;
	    /* Logical XOR for the sign */
	    this->m_negative = this->m_negative != rhs.m_negative;
	    /* Simplify the fraction and return reference */
	    this->simplify();
	    return *this;
	}

	Rational& operator-=(const Rational& rhs) {
	    Rational negated = rhs;
	    *this += negated.negate();
	    return *this;
	}

	Rational& operator/=(const Rational& rhs) {
	    Rational inverted = rhs;
	    *this *= inverted.invert();
	    return *this;
	}

	friend Rational operator+(Rational lhs, const Rational& rhs) {
	    lhs += rhs;
	    return lhs;
	}

	friend Rational operator-(Rational lhs, const Rational& rhs) {
	    lhs -= rhs;
	    return lhs;
	}

	friend Rational operator*(Rational lhs, const Rational& rhs) {
	    lhs *= rhs;
	    return lhs;
	}

	friend Rational operator/(Rational lhs, const Rational& rhs) {
	    lhs /= rhs;
	    return lhs;
	}

};

#endif /* RATIONAL_H */
