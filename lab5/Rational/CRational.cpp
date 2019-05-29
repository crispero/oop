#include "CRational.h"

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{
}

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{
}

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	if (denominator < 0)
	{
		m_numerator = -numerator;
		m_denominator = -denominator;
	}
	Normalize();
}

CRational::~CRational()
{
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

void CRational::Normalize()
{
	const auto gcd = GreatestCommonDenominator(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

unsigned GreatestCommonDenominator(unsigned a, unsigned b)
{
	return b ? GreatestCommonDenominator(b, a % b) : a;
}

double CRational::ToDouble() const
{
	return double(m_numerator) / double(m_denominator);
}

CRational const CRational::operator+() const
{
	return *this;
}

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational operator+(CRational const& rational1, CRational const& rational2)
{
	return (CRational((rational1.GetNumerator() * rational2.GetDenominator())
			+ (rational2.GetNumerator() * rational1.GetDenominator()),
		rational1.GetDenominator() * rational2.GetDenominator()));
}

CRational operator-(CRational const& rational1, CRational const& rational2)
{
	return rational1 + -rational2;
}

CRational& CRational::operator+=(CRational const& rational2)
{
	*this = *this + rational2;
	return *this;
}

CRational& CRational::operator-=(CRational const& rational2)
{
	*this = *this - rational2;
	return *this;
}

CRational operator*(CRational const& rational1, CRational const& rational2)
{
	return { rational1.GetNumerator() * rational2.GetNumerator(),
		rational1.GetDenominator() * rational2.GetDenominator() };
}

CRational operator/(CRational const& rational1, CRational const& rational2)
{
	return { rational1.GetNumerator() * rational2.GetDenominator(),
		rational2.GetNumerator() * rational1.GetDenominator() };
}

CRational& CRational::operator*=(CRational const& rational2)
{
	m_numerator *= rational2.GetNumerator();
	m_denominator *= rational2.GetDenominator();
	Normalize();
	return *this;
}

CRational& CRational::operator/=(CRational const& rational2)
{
	m_numerator *= rational2.GetDenominator();
	m_denominator *= rational2.GetNumerator();
	Normalize();
	return *this;
}

bool operator==(CRational const& rational1, CRational const& rational2)
{
	return rational1.GetNumerator() == rational2.GetNumerator() && rational2.GetDenominator() == rational2.GetDenominator();
}

bool operator!=(CRational const& rational1, CRational const& rational2)
{
	return rational1.GetNumerator() != rational2.GetNumerator() || rational2.GetDenominator() != rational2.GetDenominator();
}

bool const operator<(CRational const& rational1, CRational const& rational2)
{
	return rational1.GetNumerator() * rational2.GetDenominator() < rational2.GetNumerator() * rational1.GetDenominator();
}

bool const operator>(CRational const& rational1, CRational const& rational2)
{
	return rational1.GetNumerator() * rational2.GetDenominator() > rational2.GetNumerator() * rational1.GetDenominator();
}

bool const operator<=(CRational const& rational1, CRational const& rational2)
{
	return rational1 == rational2 || rational1 < rational2;
}

bool const operator>=(CRational const& rational1, CRational const& rational2)
{
	return rational1 == rational2 || rational1 > rational2;
}

std::ostream& operator<<(std::ostream stream, CRational const& rational)
{
	stream << rational.GetNumerator() << '/' << rational.GetDenominator();
	return stream;
}

std::istream& operator>>(std::istream stream, CRational& rational)
{
	int numerator;
	int denominator;

	if ((stream >> numerator) && (stream.get() == '/') && (stream >> denominator))
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		throw std::invalid_argument("error");
	}
	return stream;
}
