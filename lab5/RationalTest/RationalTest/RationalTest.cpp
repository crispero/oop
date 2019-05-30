#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "lab5/Rational/CRational.h"
#include <catch2/catch.hpp>

TEST_CASE("Methods")
{
	SECTION("Check init")
	{
		CRational rational1(3, 5);
		CHECK(rational1.GetNumerator() == 3);
		CHECK(rational1.GetDenominator() == 5);

		CRational rational2(0, 1);
		CHECK(rational2.GetNumerator() == 0);
		CHECK(rational2.GetDenominator() == 1);

		CHECK_THROWS_AS(CRational(3, 0), std::invalid_argument);

		CRational rational4(-1, 2);
		CHECK(rational4.GetNumerator() == -1);
		CHECK(rational4.GetDenominator() == 2);

		CRational rational5(1, -2);
		CHECK(rational5.GetNumerator() == -1);
		CHECK(rational5.GetDenominator() == 2);

		CRational rational6(-1, -2);
		CHECK(rational6.GetNumerator() == 1);
		CHECK(rational6.GetDenominator() == 2);

		CRational rational7(5, 3);
		CHECK(rational7.GetNumerator() == 5);
		CHECK(rational7.GetDenominator() == 3);

		CRational rational8(6, 3);
		CHECK(rational8.GetNumerator() == 2);
		CHECK(rational8.GetDenominator() == 1);

		CRational rational9(34, 68);
		CHECK(rational9.GetNumerator() == 1);
		CHECK(rational9.GetDenominator() == 2);

		CRational rational10(450, 3000);
		CHECK(rational10.GetNumerator() == 3);
		CHECK(rational10.GetDenominator() == 20);

		CRational rational11(6);
		CHECK(rational11.GetNumerator() == 6);
		CHECK(rational11.GetDenominator() == 1);

		CHECK(CRational().GetNumerator() == 0);
		CHECK(CRational().GetDenominator() == 1);
	}

	SECTION("To double")
	{
		CRational rational(1, 2);
		CHECK(rational.ToDouble() == 0.5);

		CRational rational1(3, 5);
		CHECK(rational1.ToDouble() == 0.6);

		CRational rational2(10, 10);
		CHECK(rational2.ToDouble() == 1);

		CRational rational3(21, 3);
		CHECK(rational3.ToDouble() == 7);
	}

	SECTION("GreatestCommonDenominator")
	{
		CHECK(GreatestCommonDenominator(3, 6) == 3);
		CHECK(GreatestCommonDenominator(3, 2) == 1);
		CHECK(GreatestCommonDenominator(5, 3) == 1);
		CHECK(GreatestCommonDenominator(49, 7) == 7);
		CHECK(GreatestCommonDenominator(22, 11) == 11);
		CHECK(GreatestCommonDenominator(50, 5) == 5);
		CHECK(GreatestCommonDenominator(-1, 2) == 1);
		CHECK(GreatestCommonDenominator(1, -2) == 1);
	}
}

TEST_CASE("Operators")
{
	SECTION("Unary + ")
	{
		CRational rational(1, 2);
		CRational rationalResult = +rational;
		CHECK(rationalResult.GetNumerator() == 1);
		CHECK(rationalResult.GetDenominator() == 2);

		CRational rational1(46, 41);
		CRational rationalResult1 = +rational1;
		CHECK(rationalResult1.GetNumerator() == 46);
		CHECK(rationalResult1.GetDenominator() == 41);
	}

	SECTION("Unary - ")
	{
		CRational rational(1, 2);
		CRational rationalResult = -rational;
		CHECK(rationalResult.GetNumerator() == -1);
		CHECK(rationalResult.GetDenominator() == 2);

		CRational rational1(46, 41);
		CRational rationalResult1 = -rational1;
		CHECK(rationalResult1.GetNumerator() == -46);
		CHECK(rationalResult1.GetDenominator() == 41);

		CRational rational2(-1, 3);
		CRational rationalResult2 = -rational2;
		CHECK(rationalResult2.GetNumerator() == 1);
		CHECK(rationalResult2.GetDenominator() == 3);
	}

	SECTION("Binary + ")
	{
		CRational rational1(1, 3);
		CRational rational2(1, 3);
		CRational rationalResult = rational1 + rational2;
		CHECK(rationalResult.GetNumerator() == 2);
		CHECK(rationalResult.GetDenominator() == 3);

		CRational rational3(5, 4);
		CRational rational4(6, 5);
		CRational rationalResult2 = rational3 + rational4;
		CHECK(rationalResult2.GetNumerator() == 49);
		CHECK(rationalResult2.GetDenominator() == 20);

		CRational rational5(-1, 3);
		CRational rational6(6, 4);
		CRational rationalResult3 = rational5 + rational6;
		CHECK(rationalResult3.GetNumerator() == 7);
		CHECK(rationalResult3.GetDenominator() == 6);

		CRational rational7(6, 7);
		CRational rational8(6);
		CRational rationalResult4 = rational7 + rational8;
		CHECK(rationalResult4.GetNumerator() == 48);
		CHECK(rationalResult4.GetDenominator() == 7);

		CRational rationalResult5 = rational8 + rational7;
		CHECK(rationalResult5.GetNumerator() == 48);
		CHECK(rationalResult5.GetDenominator() == 7);

		
	}

	SECTION("Binary - ")
	{
		CRational rational1(1, 3);
		CRational rational2(1, 3);
		CRational rationalResult = rational1 - rational2;
		CHECK(rationalResult.GetNumerator() == 0);
		CHECK(rationalResult.GetDenominator() == 1);

		CRational rational3(5, 4);
		CRational rational4(6, 5);
		CRational rationalResult2 = rational3 - rational4;
		CHECK(rationalResult2.GetNumerator() == 1);
		CHECK(rationalResult2.GetDenominator() == 20);

		CRational rational5(-1, 3);
		CRational rational6(6, 4);
		CRational rationalResult3 = rational5 - rational6;
		CHECK(rationalResult3.GetNumerator() == -11);
		CHECK(rationalResult3.GetDenominator() == 6);

		CRational rational7(6, 7);
		CRational rational8(6);
		CRational rationalResult4 = rational7 - rational8;
		CHECK(rationalResult4.GetNumerator() == -36);
		CHECK(rationalResult4.GetDenominator() == 7);

		CRational rationalResult5 = rational8 - rational7;
		CHECK(rationalResult5.GetNumerator() == 36);
		CHECK(rationalResult5.GetDenominator() == 7);
	}

	SECTION("Operator +=")
	{
		CRational rational1(1, 2);
		CRational rational2(1, 6);
		rational1 += rational2;
		CHECK(rational1.GetNumerator() == 2);
		CHECK(rational1.GetDenominator() == 3);

		CRational rational3(1);
		CRational rational4(1, 2);
		rational4 += rational3;
		CHECK(rational4.GetNumerator() == 3);
		CHECK(rational4.GetDenominator() == 2);

		CRational rational5(4, 3);
		CRational rational6(5, 3);
		rational5 += rational6;
		CHECK(rational5.GetNumerator() == 3);
		CHECK(rational5.GetDenominator() == 1);

		CRational rational0(1, 2);
		CRational rational00(1, 2);
		rational0 -= rational00;
		CHECK(rational0.GetNumerator() == 0);
		CHECK(rational0.GetDenominator() == 1);
	}

	SECTION("Operator -=")
	{
		CRational rational1(1, 2);
		CRational rational2(1, 6);
		rational1 -= rational2;
		CHECK(rational1.GetNumerator() == 1);
		CHECK(rational1.GetDenominator() == 3);

		CRational rational3(1);
		CRational rational4(1, 2);
		rational4 -= rational3;
		CHECK(rational4.GetNumerator() == -1);
		CHECK(rational4.GetDenominator() == 2);
	}

	SECTION("Operator *")
	{
		CRational rational1(1, 2);
		CRational rational2(2, 3);
		CRational rationalResult = rational1 * rational2;
		CHECK(rationalResult.GetNumerator() == 1);
		CHECK(rationalResult.GetDenominator() == 3);

		CRational rational3(1, 2);
		CRational rational4(-3);
		CRational rationalResult1 = rational3 * rational4;
		CHECK(rationalResult1.GetNumerator() == -3);
		CHECK(rationalResult1.GetDenominator() == 2);

		CRational rational5(7);
		CRational rational6(2, 3);
		CRational rationalResult2 = rational5 * rational6;
		CHECK(rationalResult2.GetNumerator() == 14);
		CHECK(rationalResult2.GetDenominator() == 3);

		CRational rational9(4, 3);
		CRational rational10(3, 3);
		CRational rationalResult6 = rational9 * rational10;
		CHECK(rationalResult6.GetNumerator() == 4);
		CHECK(rationalResult6.GetDenominator() == 3);
	}

	SECTION("Operator /")
	{
		CRational rational1(1, 2);
		CRational rational2(2, 3);
		CRational rationalResult = rational1 / rational2;
		CHECK(rationalResult.GetNumerator() == 3);
		CHECK(rationalResult.GetDenominator() == 4);

		CRational rational3(1, 2);
		CRational rational4(5);
		CRational rationalResult1 = rational3 / rational4;
		CHECK(rationalResult1.GetNumerator() == 1);
		CHECK(rationalResult1.GetDenominator() == 10);

		CRational rational5(7);
		CRational rational6(2, 3);
		CRational rationalResult2 = rational5 / rational6;
		CHECK(rationalResult2.GetNumerator() == 21);
		CHECK(rationalResult2.GetDenominator() == 2);
	}

	SECTION("Operator *=")
	{
		CRational rational1(1, 2);
		CRational rational2(2, 3);
		rational1 *= rational2;
		CHECK(rational1.GetNumerator() == 1);
		CHECK(rational2.GetDenominator() == 3);

		CRational rational3(1, 2);
		CRational rational4(3);
		rational3 *= rational4;
		CHECK(rational3.GetNumerator() == 3);
		CHECK(rational3.GetDenominator() == 2);
	}

	SECTION("Operator /=")
	{
		CRational rational1(1, 2);
		CRational rational2(2, 3);
		rational1 /= rational2;
		CHECK(rational1.GetNumerator() == 3);
		CHECK(rational1.GetDenominator() == 4);

		CRational rational3(1, 2);
		CRational rational4(3);
		rational3 /= rational4;
		CHECK(rational3.GetNumerator() == 1);
		CHECK(rational3.GetDenominator() == 6);

		CRational rational5(3, 4);
		CRational rational6(3, 8);
		rational5 /= rational6;
		CHECK(rational5.GetNumerator() == 2);
		CHECK(rational5.GetDenominator() == 1);
	}

	SECTION("Operator ==")
	{
		CRational rational1(1, 2);
		CRational rational2(1, 2);
		bool result = (rational1 == rational2);
		CHECK(result == true);

		CRational rational3(1, 2);
		CRational rational4(2, 3);
		bool result1 = (rational3 == rational4);
		CHECK(result1 == false);

		CRational rational5(4, 1);
		CRational rational6(4);
		bool result2 = (rational5 == rational6);
		CHECK(result2 == true);

		CRational rational7(1, 2);
		CRational rational8(7);
		bool result3 = (rational7 == rational8);
		CHECK(result3 == false);

		CRational rational9(3);
		CRational rational10(3, 1);
		bool result4 = (rational9 == rational10);
		CHECK(result4 == true);

		CRational rational11(3);
		CRational rational12(2, 3);
		bool result5 = (rational11 == rational12);
		CHECK(result5 == false);
	}

	SECTION("Operator !=")
	{
		CRational rational1(1, 2);
		CRational rational2(1, 2);
		bool result = (rational1 != rational2);
		CHECK(result == false);

		CRational rational3(1, 2);
		CRational rational4(2, 3);
		bool result1 = (rational3 != rational4);
		CHECK(result1 == true);

		CRational rational5(4, 1);
		CRational rational6(4);
		bool result2 = (rational5 != rational6);
		CHECK(result2 == false);

		CRational rational7(1, 2);
		CRational rational8(7);
		bool result3 = (rational7 != rational8);
		CHECK(result3 == true);

		CRational rational9(3);
		CRational rational10(3, 1);
		bool result4 = (rational9 != rational10);
		CHECK(result4 == false);

		CRational rational11(3);
		CRational rational12(2, 3);
		bool result5 = (rational11 != rational12);
		CHECK(result5 == true);
	}

	SECTION("Operators <, <=, >, >=")
	{
		CRational rational1(1, 2);
		CRational rational2(1, 3);
		bool result = (rational1 >= rational2);
		CHECK(result == true);

		bool result1 = (rational1 <= rational2);
		CHECK(result1 == false);

		CRational rational3(3, 1);
		CRational rational4(2);
		bool result2 = (rational3 > rational4);
		CHECK(result2 == true);

		CRational rational5(7);
		bool result3 = (rational1 < rational5);
		CHECK(result3 == true);

		CRational rational6(3);
		CRational rational7(7, 2);
		bool result4 = (rational6 <= rational7);
		CHECK(result4 == true);

		CRational rational8(8, 2);
		bool result5 = (rational6 >= rational8);
		CHECK(result5 == false);
	}

	SECTION("Operator <<")
	{
		CRational rational1(7, 15);
		std::stringstream output1;
		output1 << rational1;
		CHECK(output1.str() == "7/15");

		CRational rational2(-7, 15);
		std::stringstream output2;
		output2 << rational2;
		CHECK(output2.str() == "-7/15");

		CRational rational3(7);
		std::stringstream output3;
		output3 << rational3;
		CHECK(output3.str() == "7/1");

		std::stringstream output4;
		output4 << CRational();
		CHECK(output4.str() == "0/1");
	}

	SECTION("Operator >>")
	{
		CRational rational1;
		std::stringstream input1("7/15");
		input1 >> rational1;

		CHECK(rational1.GetNumerator() == 7);
		CHECK(rational1.GetDenominator() == 15);

		CRational rational2;
		std::stringstream input2("-7/15");
		input2 >> rational2;
		CHECK(rational2.GetNumerator() == -7);
		CHECK(rational2.GetDenominator() == 15);

		CRational rational3;
		std::stringstream input3("test");
		CHECK_THROWS_AS(input3 >> rational3, std::invalid_argument);

		CRational rational4;
		std::stringstream input4("3/1");
		input4 >> rational4;
		CHECK(rational4.GetNumerator() == 3);
		CHECK(rational4.GetDenominator() == 1);
	}
}