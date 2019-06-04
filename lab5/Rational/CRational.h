#pragma once
#include <sstream>

class CRational
{
public:
	CRational(int numerator, int denominator);
	CRational(int value);
	CRational();
	
	~CRational();
	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;

	CRational const operator+() const;
	CRational const operator-() const;

	CRational& operator+=(CRational const& value);
	CRational& operator-=(CRational const& value);
	CRational& operator*=(CRational const& value);
	CRational& operator/=(CRational const& value);

private:
	void Normalize();
	int m_numerator;
	int m_denominator;

};

CRational operator+(CRational const& rational1, CRational const& rational2);
CRational operator-(CRational const& rational1, CRational const& rational2);
CRational operator*(CRational const& rational1, CRational const& rational2);
CRational operator/(CRational const& rational1, CRational const& rational2);
bool operator==(CRational const& rational1, CRational const& rational2);
bool operator!=(CRational const& rational1, CRational const& rational2);
bool const operator<(CRational const& rational1, CRational const& rational2);
bool const operator>(CRational const& rational1, CRational const& rational2);
bool const operator<=(CRational const& rational1, CRational const& rational2);
bool const operator>=(CRational const& rational1, CRational const& rational2);
std::ostream& operator<<(std::ostream& stream, CRational const& rational);
std::istream& operator>>(std::istream& stream, CRational& rational);
unsigned GreatestCommonDenominator(unsigned a, unsigned b);