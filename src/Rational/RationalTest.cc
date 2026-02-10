/**
 * @file RationalTest.cc
 * @author Martin
 * @brief File containing test case implementations for the Rational class
*/

#include "RationalTest.hh"

namespace {

void constructorTest(void) {

    /* A/B/Negative Constructor */
    Rational ar1 {1, 2};
    Rational ar2 {3, 4};
    Rational ar3 {1, 2, true};
    Rational ar4 {6, 4};
    Rational ar5 {51, 6, true};

    assert(ar1.getNumerator() == 1 && ar1.getDenominator() == 2 && ar1.isNegative() == false);
    assert(ar2.getNumerator() == 3 && ar2.getDenominator() == 4 && ar2.isNegative() == false);
    assert(ar3.getNumerator() == 1 && ar3.getDenominator() == 2 && ar3.isNegative() == true);
    /* ar4 should be simplified to 3/2 */
    assert(ar4.getNumerator() == 3 && ar4.getDenominator() == 2 && ar4.isNegative() == false);
    /* ar5 should be simplified to 17/2 */
    assert(ar5.getNumerator() == 17 && ar5.getDenominator() == 2 && ar5.isNegative() == true);

    /* Float Constructor */
    Rational fr1 {0.5f};
    Rational fr2 {-0.1f};
    Rational fr3 {0.33f};
    Rational fr4 {0.111111f};
    Rational fr5 {-12.7f};

    assert(fr1.getNumerator() == 1 && fr1.getDenominator() == 2 && fr1.isNegative() == false);
    assert(fr2.getNumerator() == 1 && fr2.getDenominator() == 10 && fr2.isNegative() == true);
    assert(fr3.getNumerator() == 33 && fr3.getDenominator() == 100 && fr3.isNegative() == false);
    assert(fr4.getNumerator() == 111111 && fr4.getDenominator() == 1000000 && fr4.isNegative() == false);
    assert(fr5.getNumerator() == 127 && fr5.getDenominator() == 10 && fr5.isNegative() == true);

    /* Int Constructor */
    Rational ir1 {5};
    Rational ir2 {-325};

    assert(ir1.getNumerator() == 5 && ir1.getDenominator() == 1 && ir1.isNegative() == false);
    assert(ir2.getNumerator() == 325 && ir2.getDenominator() == 1 && ir2.isNegative() == true);

    /* String Constructor */
    Rational sr1 {"1/2"};
    Rational sr2 {"-5/7"};
    Rational sr3 {"9/12"};
    Rational sr4 {"0.5"};
    Rational sr5 {"-0.2"};
    
    assert(sr1.getNumerator() == 1 && sr1.getDenominator() == 2 && sr1.isNegative() == false);
    assert(sr2.getNumerator() == 5 && sr2.getDenominator() == 7 && sr2.isNegative() == true);
    assert(sr3.getNumerator() == 3 && sr3.getDenominator() == 4 && sr3.isNegative() == false);
    assert(sr4.getNumerator() == 1 && sr4.getDenominator() == 2 && sr4.isNegative() == false);
    assert(sr5.getNumerator() == 1 && sr5.getDenominator() == 5 && sr5.isNegative() == true);

    bool caught = false;
    try {
	Rational sr6 {"5This is not valid!4"};
    } catch(const std::exception& e) {
	caught = true;
    }
    assert(caught);

    /* Void Constructor */
    Rational vr1;

    assert(vr1.getNumerator() == 0 && vr1.getDenominator() == 1 && vr1.isNegative() == false);

    /* Special Case 1: Simplifying to zero */
    Rational cr1 {0, 45, true};

    assert(cr1.getNumerator() == 0 && cr1.getDenominator() == 1 && cr1.isNegative() == false);

}

void modifyTest(void) {

    /* Testing negate() */
    Rational n1 {3, 4, false};
    Rational n2 {5, 6, true};

    n1.negate();
    n2.negate();

    assert(n1.getNumerator() == 3 && n1.getDenominator() == 4 && n1.isNegative() == true);
    assert(n2.getNumerator() == 5 && n2.getDenominator() == 6 && n2.isNegative() == false);

    /* Testing invert() */
    Rational i1 {1, 2, false};
    Rational i2 {3, 4, true};

    i1.invert();
    i2.invert();

    assert(i1.getNumerator() == 2 && i1.getDenominator() == 1 && i1.isNegative() == false);
    assert(i2.getNumerator() == 4 && i2.getDenominator() == 3 && i2.isNegative() == true);

    /* Special Case 1: Zero has no inverse element */
    Rational i3;

    bool caught = false;
    try {
	i3.invert();
    } catch(std::exception& e) {
	caught = true;
    }

    assert(caught);
}

void conversionTest(void) {

    Rational r1 {1, 2};
    Rational r2 {1, 3};
    Rational r3 {4, 9, true};
    Rational r4;
    Rational r5 {0, 1, true};
    Rational r6 {1, 1};
    Rational r7 {36, 9};
    Rational r8 {5, 1, true};

    /* Testing conversion to float */
    assert(r1.toFloat() - 0.5f < 1.0f/FLOAT_CONVERSION_PRECISION);
    assert(r2.toFloat() - 0.3333333f < 1.0f/FLOAT_CONVERSION_PRECISION);
    assert(r3.toFloat() - -0.4444444f < 1.0f/FLOAT_CONVERSION_PRECISION);
    assert(r4.toFloat() == 0.0f);
    assert(r5.toFloat() == 0.0f);
    assert(r6.toFloat() == 1.0f);
    assert(r7.toFloat() == 4.0f);
    assert(r8.toFloat() == -5.0f);

    /* Testing conversion to string */
    assert(r1.toString() == "1/2");
    assert(r2.toString() == "1/3");
    assert(r3.toString() == "-4/9");
    assert(r4.toString() == "0");
    assert(r5.toString() == "0");
    assert(r6.toString() == "1");
    assert(r7.toString() == "4");
    assert(r8.toString() == "-5");

}

void assignmentTest(void) {

    Rational r1 {1, 2};
    Rational r2 {3, 4, true};
    Rational r3 = r1;

    /* Testing that instances created as expected */
    assert(r1.getNumerator() == 1 && r1.getDenominator() == 2 && r1.isNegative() == false);
    assert(r2.getNumerator() == 3 && r2.getDenominator() == 4 && r2.isNegative() == true);
    assert(r3.getNumerator() == 1 && r3.getDenominator() == 2 && r3.isNegative() == false);

    /* Testing reassignment behavior */
    r1 = r2;

    assert(r1.getNumerator() == 3 && r1.getDenominator() == 4 && r1.isNegative() == true);
    assert(r3.getNumerator() == 1 && r3.getDenominator() == 2 && r3.isNegative() == false);

    /* Testing that assignment copies rather than reassigns reference */
    r1.invert();
    r1.negate();

    assert(r1.getNumerator() == 4 && r1.getDenominator() == 3 && r1.isNegative() == false);
    assert(r2.getNumerator() == 3 && r2.getDenominator() == 4 && r2.isNegative() == true);
}

void comparisonTest(void) {

    Rational r1 {1, 2};
    Rational r2 {1, 2, true};
    Rational r3 {4, 2};
    Rational r4 {1, 1};

    /* Testing equality */
    assert(r1 == r1);
    assert(r2 == r2);
    assert(r3 == r3);
    assert(r4 == r4);

    r2.negate();
    assert(r1 == r2);

    assert(!(r1 == r3));
    assert(!(r1 == r4));
    assert(!(r3 == r4));

    /* Testing not equal */
    assert(r1 != r3);
    assert(r1 != r4);
    assert(r3 != r4);
    assert(!(r1 != r2));

    /* Testing greater/greater-equal/less/less-equal operators */
    assert(r1 <= r2);
    assert(r1 >= r2);
    assert(!(r1 < r2));
    assert(!(r1 > r2));

    r2.negate();
    assert(r2 < r1);
    assert(r4 > r1);
    assert(r3 > r4);
    assert(r3 > r2);
    assert(r4 > r2);
}

void arithmeticTestEq(void) {

    Rational r1 {1, 2};
    Rational r2 {5, 6};
    Rational r3 {8, 9, true};
    Rational r4 {3, 4, true};

    /* += test */
    r1 += r2;
    assert(r1.getNumerator() == 4 && r1.getDenominator() == 3 && r1.isNegative() == false);
    assert(r2.getNumerator() == 5 && r2.getDenominator() == 6 && r2.isNegative() == false);

    r2 += r3;
    assert(r2.getNumerator() == 1 && r2.getDenominator() == 18 && r2.isNegative() == true);
    assert(r3.getNumerator() == 8 && r3.getDenominator() == 9 && r3.isNegative() == true);

    r4 += r3;
    assert(r4.getNumerator() == 59 && r4.getDenominator() == 36 && r4.isNegative() == true);
    assert(r3.getNumerator() == 8 && r3.getDenominator() == 9 && r3.isNegative() == true);

    /* -= test */
    r4 -= r3;
    assert(r4.getNumerator() == 3 && r4.getDenominator() == 4 && r4.isNegative() == true);
    assert(r3.getNumerator() == 8 && r3.getDenominator() == 9 && r3.isNegative() == true);

    r2 -= r3;
    assert(r2.getNumerator() == 5 && r2.getDenominator() == 6 && r2.isNegative() == false);
    assert(r3.getNumerator() == 8 && r3.getDenominator() == 9 && r3.isNegative() == true);

    r1 -= r2;
    assert(r1.getNumerator() == 1 && r1.getDenominator() == 2 && r1.isNegative() == false);
    assert(r2.getNumerator() == 5 && r2.getDenominator() == 6 && r2.isNegative() == false);

    /* *= test */
    r1 *= r2;
    assert(r1.getNumerator() == 5 && r1.getDenominator() == 12 && r1.isNegative() == false);
    assert(r2.getNumerator() == 5 && r2.getDenominator() == 6 && r2.isNegative() == false);

    r2 *= r3;
    assert(r2.getNumerator() == 20 && r2.getDenominator() == 27 && r2.isNegative() == true);
    assert(r3.getNumerator() == 8 && r3.getDenominator() == 9 && r3.isNegative() == true);

    r4 *= r3;
    assert(r4.getNumerator() == 2 && r4.getDenominator() == 3 && r4.isNegative() == false);
    assert(r3.getNumerator() == 8 && r3.getDenominator() == 9 && r3.isNegative() == true);

    /* /= test */
    r4 /= r3;
    assert(r4.getNumerator() == 3 && r4.getDenominator() == 4 && r4.isNegative() == true);
    assert(r3.getNumerator() == 8 && r3.getDenominator() == 9 && r3.isNegative() == true);
    
    r2 /= r3;
    assert(r2.getNumerator() == 5 && r2.getDenominator() == 6 && r2.isNegative() == false);
    assert(r3.getNumerator() == 8 && r3.getDenominator() == 9 && r3.isNegative() == true);

    r1 /= r2;
    assert(r1.getNumerator() == 1 && r1.getDenominator() == 2 && r1.isNegative() == false);
    assert(r2.getNumerator() == 5 && r2.getDenominator() == 6 && r2.isNegative() == false);

    /* Checking to make sure division by zero impossible */
    Rational r0;
    bool caught = false;
    try {
	r1 /= r0;
    } catch(std::exception& e) {
	caught = true;
    }
    assert(caught);
}

void arithmeticTest(void) {

    Rational r1 {3, 4};
    Rational r2 {5, 6};
    Rational r3 {1, 3, true};

    /* Addition test */
    Rational r4;
    r4 = r1 + r2;
    assert(r4.getNumerator() == 19 && r4.getDenominator() == 12 && r4.isNegative() == false);
    assert(r1.getNumerator() == 3 && r1.getDenominator() == 4 && r1.isNegative() == false);
    assert(r2.getNumerator() == 5 && r2.getDenominator() == 6 && r2.isNegative() == false);

    Rational r5 = r1 + r3;
    assert(r5.getNumerator() == 5 && r5.getDenominator() == 12 && r5.isNegative() == false);
    assert(r1.getNumerator() == 3 && r1.getDenominator() == 4 && r1.isNegative() == false);
    assert(r3.getNumerator() == 1 && r3.getDenominator() == 3 && r3.isNegative() == true);

    /* Subtraction test */
    r4 = r1 - r2;
    assert(r4.getNumerator() == 1 && r4.getDenominator() == 12 && r4.isNegative() == true);
    assert(r1.getNumerator() == 3 && r1.getDenominator() == 4 && r1.isNegative() == false);
    assert(r2.getNumerator() == 5 && r2.getDenominator() == 6 && r2.isNegative() == false);

    r5 = r1 - r3;
    assert(r5.getNumerator() == 13 && r5.getDenominator() == 12 && r5.isNegative() == false);
    assert(r1.getNumerator() == 3 && r1.getDenominator() == 4 && r1.isNegative() == false);
    assert(r3.getNumerator() == 1 && r3.getDenominator() == 3 && r3.isNegative() == true);   

    /* Multiplication test */
    r4 = r1 * r2;
    assert(r4.getNumerator() == 5 && r4.getDenominator() == 8 && r4.isNegative() == false);
    assert(r1.getNumerator() == 3 && r1.getDenominator() == 4 && r1.isNegative() == false);
    assert(r2.getNumerator() == 5 && r2.getDenominator() == 6 && r2.isNegative() == false);

    r5 = r1 * r3;
    assert(r5.getNumerator() == 1 && r5.getDenominator() == 4 && r5.isNegative() == true);
    assert(r1.getNumerator() == 3 && r1.getDenominator() == 4 && r1.isNegative() == false);
    assert(r3.getNumerator() == 1 && r3.getDenominator() == 3 && r3.isNegative() == true);   
   
    /* Division test */
    r4 = r1 / r2;
    assert(r4.getNumerator() == 9 && r4.getDenominator() == 10 && r4.isNegative() == false);
    assert(r1.getNumerator() == 3 && r1.getDenominator() == 4 && r1.isNegative() == false);
    assert(r2.getNumerator() == 5 && r2.getDenominator() == 6 && r2.isNegative() == false);

    r5 = r1 / r3;
    assert(r5.getNumerator() == 9 && r5.getDenominator() == 4 && r5.isNegative() == true);
    assert(r1.getNumerator() == 3 && r1.getDenominator() == 4 && r1.isNegative() == false);
    assert(r3.getNumerator() == 1 && r3.getDenominator() == 3 && r3.isNegative() == true);   

    /* Zero division test */
    Rational r0;
    bool caught = false;
    try {
	r4 = r1 / r0;
    } catch(std::exception& e) {
	caught = true;
    }
    assert(caught);
}

void arithmeticTestNum(void) {

    Rational r1 {1, 2};
    Rational r2 {5, 6};
    Rational r3;
    Rational r4;
    Rational r5;

    /* Addition test */
    r2 += 0.5f;
    r2 += 1;
    r2 += "2/3";
    r3 = r1 + 0.5f;
    r4 = r1 + 1;
    r5 = r1 + "-5/4";

    assert(r1.getNumerator() == 1 && r1.getDenominator() == 2 && r1.isNegative() == false);
    assert(r2.getNumerator() == 3 && r2.getDenominator() == 1 && r2.isNegative() == false);
    assert(r3.getNumerator() == 1 && r3.getDenominator() == 1 && r3.isNegative() == false);
    assert(r4.getNumerator() == 3 && r4.getDenominator() == 2 && r4.isNegative() == false);
    assert(r5.getNumerator() == 3 && r5.getDenominator() == 4 && r5.isNegative() == true);

    /* Subtraction test */
    r2 -= 0.5f;
    r2 -= 1;
    r2 -= "2/3";
    r3 = r1 - 1.5f;
    r4 = r1 - 1;
    r5 = r1 - "-7/4";

    assert(r1.getNumerator() == 1 && r1.getDenominator() == 2 && r1.isNegative() == false);
    assert(r2.getNumerator() == 5 && r2.getDenominator() == 6 && r2.isNegative() == false);
    assert(r3.getNumerator() == 1 && r3.getDenominator() == 1 && r3.isNegative() == true);
    assert(r4.getNumerator() == 1 && r4.getDenominator() == 2 && r4.isNegative() == true);
    assert(r5.getNumerator() == 9 && r5.getDenominator() == 4 && r5.isNegative() == false);

    /* Multiplication test */
    r2 *= 0.5f;
    r2 *= 2;
    r2 *= "4/3";
    r3 = r1 * 2.5f;
    r4 = r1 * 3;
    r5 = r1 * "-7/8";

    assert(r1.getNumerator() == 1 && r1.getDenominator() == 2 && r1.isNegative() == false);
    assert(r2.getNumerator() == 10 && r2.getDenominator() == 9 && r2.isNegative() == false);
    assert(r3.getNumerator() == 5 && r3.getDenominator() == 4 && r3.isNegative() == false);
    assert(r4.getNumerator() == 3 && r4.getDenominator() == 2 && r4.isNegative() == false);
    assert(r5.getNumerator() == 7 && r5.getDenominator() == 16 && r5.isNegative() == true);

    /* Division test */
    r2 /= 0.5f;
    r2 /= 2;
    r2 /= "4/3";
    r3 = r1 / 0.3f;
    r4 = r1 / 4;
    r5 = r1 / "-3/7";

    assert(r1.getNumerator() == 1 && r1.getDenominator() == 2 && r1.isNegative() == false);
    assert(r2.getNumerator() == 5 && r2.getDenominator() == 6 && r2.isNegative() == false);
    assert(r3.getNumerator() == 5 && r3.getDenominator() == 3 && r3.isNegative() == false);
    assert(r4.getNumerator() == 1 && r4.getDenominator() == 8 && r4.isNegative() == false);
    assert(r5.getNumerator() == 7 && r5.getDenominator() == 6 && r5.isNegative() == true);

    /* Zero division test */
    Rational r0;
    int caught = 0;
    /* Float conversion */
    try {
	r3 = r1 / 0.0f;
    } catch(std::exception& e) {
	++caught;
    }
    /* Int conversion */
    try {
	r3 = r1 / 0;
    } catch(std::exception& e) {
	++caught;
    }
    /* String conversion */
    try {
	r3 = r1 / "0/2";
    } catch(std::exception& e) {
	++caught;
    }
    assert(caught == 3);
}

} /* anonymous */

void rationalTest(void) {

    std::puts("--- Rational TC Running ---");
    constructorTest();
    std::puts("-> Passed constructorTest()");
    modifyTest();
    std::puts("-> Passed modifyTest()");
    conversionTest();
    std::puts("-> Passed conversionTest()");
    assignmentTest();
    std::puts("-> Passed assignmentTest()");
    comparisonTest();
    std::puts("-> Passed comparisonTest()");
    arithmeticTestEq();
    std::puts("-> Passed arithmeticTestEq()");
    arithmeticTest();
    std::puts("-> Passed arithmeticTest()");
    arithmeticTestNum();
    std::puts("-> Passed arithmeticTestNum()");

    std::puts("--- Rational Tests Passed ---");
}

