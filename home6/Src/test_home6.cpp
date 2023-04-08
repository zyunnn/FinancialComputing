#include "test/Main.hpp"
#include "test/Data.hpp"
#include "test/Print.hpp"
#include "home6/Output.hpp"
#include "home6/home6.hpp"
#include <cmath>
#include <string>
#include <iomanip>

using namespace test;
using namespace cfl;
using namespace std;
using namespace prb;
using namespace test::Data;

namespace test_GaussRollback
{
	/*
	class Chain : public IGaussRollback
	{
	public:
		Chain(const std::string &sFast, unsigned iSize = 0, double dH = 0, double dVar = 0)
			: m_sFast(sFast)
		{
			PRECONDITION((sFast == "crankNicolson") || (sFast == "fft2") || (sFast == "fft"));
			if (iSize > 0)
			{
				ASSERT((dVar > 0) && (dH > 0));
				unsigned iExpl, iImpl;
				if (m_sFast == "crankNicolson")
				{
					iExpl = 2 * (std::ceil(dVar / dH) + 1);
					iImpl = iExpl / 2;
					m_uRollback = prb::chain(iExpl, crankNicolson(), iImpl);
				}
				// FFT
				iExpl = 2 * std::ceil(std::log2(iSize)) + 10;
				iImpl = iExpl / 2;
				if (m_sFast == "fft2")
				{
					m_uRollback = prb::chain(iExpl, fft2(), iImpl);
				}
				if (m_sFast == "fft")
				{
					m_uRollback = prb::chain(iExpl, fft(), iImpl);
				}
				m_uRollback.assign(iSize, dH, dVar);
			}
		}

		IGaussRollback *
		newObject(unsigned iSize, double dH, double dVar) const
		{
			return new Chain(m_sFast, iSize, dH, dVar);
		}

		void rollback(std::valarray<double> &rValues) const
		{
			m_uRollback.rollback(rValues);
		}

	private:
		std::string m_sFast;
		GaussRollback m_uRollback;
	};

	cfl::GaussRollback chain(const char *sFast)
	{
		return GaussRollback(new Chain(sFast));
	}*/
}


using namespace test_GaussRollback;

void printRollback(const std::vector<std::valarray<double>> &rRes,
				   const std::string &sMes, const std::valarray<double> &rState)
{
	std::vector<std::string> uNames =
		{"state", "value", "delta", "gamma", "vega"};
	auto uRes(rRes);
	uRes.insert(uRes.begin(), rState);

	unsigned iPoints = 11; // points to print
	unsigned iColumns = 12;
	unsigned iSpace = 3;

	test::printTable(uRes, uNames, sMes, iColumns, iSpace, iPoints);
}

void testGaussRollback(const cfl::GaussRollback &rRollback,
					   const std::string &sMethod, bool bRadix2)
{
	print(sMethod);

	double dVar = 0.36;
	int iStandardDev = 8;
	double dInterval = iStandardDev * ::sqrt(dVar);

	double dH = 0.01;
	unsigned iSize = std::exp2(std::round(std::log2(2 * ::ceil(dInterval / dH))));
	if (bRadix2 == false)
	{
		iSize /= 2;
		iSize *= 3;
	}
	print(iSize, "size");
	print(dVar, "var", true);

	unsigned iNames = 4;
	std::vector<std::valarray<double>> uRes(iNames, std::valarray<double>(iSize));
	GaussRollback uRollback(rRollback);
	uRollback.assign(iSize, dH, dVar);

	std::valarray<double> uState(0., iSize);
	uState[0] = -dH * (iSize - 1) / 2;
	std::transform(begin(uState), end(uState) - 1, begin(uState) + 1,
				   [dH](double dX)
				   { return dX + dH; });
	std::string sMes;

	sMes = "Rollback of function f(x) = xe^x. ";
	uRes[0] = uState * exp(uState);
	uRollback.rollback(uRes[0], uRes[1], uRes[2]);
	uRes[3] = uRes[2];
	uRollback.vega(uRes[3]);
	printRollback(uRes, sMes, uState);
}

void gaussRollback()
{
	bool bRadix2 = false;
	std::string sMethod = "Explicit scheme with default parameters";
	testGaussRollback(prb::expl(), sMethod, bRadix2);

	sMethod = "Implicit scheme with default parameters";
	testGaussRollback(prb::impl(), sMethod, bRadix2);

	// sMethod = "Crank-Nicolson scheme with default parameters";
	// testGaussRollback(prb::crankNicolson(), sMethod, bRadix2);

	// sMethod = "3-layer scheme with Crank Nicolson";
	// testGaussRollback(chain("crankNicolson"), sMethod, bRadix2);

	// sMethod = "Fast Fourier Transform: general form";
	// testGaussRollback(prb::fft(), sMethod, bRadix2);

	// sMethod = "3-layer scheme with FFT general radix";
	// testGaussRollback(chain("fft"), sMethod, bRadix2);

	// bRadix2 = true;
	// sMethod = "Fast Fourier Transform: radix-2";
	// testGaussRollback(prb::fft2(), sMethod, bRadix2);

	// sMethod = "3-layer scheme with FFT radix-2";
	// testGaussRollback(chain("fft2"), sMethod, bRadix2);
};

std::function<void()> test_home6()
{
	return []()
	{
		print("GAUSS ROLLBACK");

		gaussRollback();
	};
}

int main()
{
	project(test_home6(), PROJECT_NAME, PROJECT_NAME,
			"Homework 6");
}
