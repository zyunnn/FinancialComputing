#include <random>
#include "cfl/Macros.hpp"
#include "test/Output.hpp"
#include "test/Print.hpp"

using namespace std;
using namespace cfl;

// accessor functions

std::valarray<double> test::getArg(double dL, double dR, unsigned iN)
{
  PRECONDITION(iN > 0);

  std::valarray<double> uResult(iN);
  double dH = (dR - dL) / (iN - 1);
  double dX = dL;
  for (unsigned iI = 0; iI < iN; iI++)
  {
    uResult[iI] = dX;
    dX += dH;
  }
  uResult[uResult.size() - 1] = dR;
  return uResult;
}

std::vector<double> test::getTimes(double dInitialTime, double dMaturity, unsigned iN)
{
  std::valarray<double> uArg = getArg(dInitialTime, dMaturity, iN + 1);
  std::vector<double> uTimes(std::begin(uArg) + 1, std::end(uArg));
  return uTimes;
}

std::valarray<double> test::getRandArg(double dL, double dR, unsigned iN)
{
  PRECONDITION(iN > 0);

  std::valarray<double> uResult(iN);
  std::minstd_rand uGen(1);
  std::uniform_real_distribution<double> uRand(dL, dR);
  for (unsigned iI = 0; iI < iN; iI++)
  {
    uResult[iI] = uRand(uGen);
  }
  std::sort(begin(uResult), end(uResult));
  POSTCONDITION((dL < uResult[0]) && (uResult[uResult.size() - 1] < dR));
  return uResult;
}

std::valarray<double> test::
    getValues(const Function &rF, const std::valarray<double> &rArg)
{
  std::valarray<double> uResult(rArg.size());
  std::transform(begin(rArg), end(rArg), begin(uResult), [&rF](double dX)
                 { return rF(dX); });
  return uResult;
}

// print functions

void test::compare(const std::valarray<double> &rExact,
                   const std::valarray<double> &rNum,
                   const std::string &rTitle, unsigned iColumn,
                   unsigned iSpace, unsigned iMaxRows)
{
  PRECONDITION(rExact.size() == rNum.size());

  std::vector<std::valarray<double>>
      uResults = {rExact, rNum, std::abs(rExact - rNum)};
  std::vector<std::string> uHeads = {"exact", "numeric", "error"};
  printTable(uResults, uHeads, rTitle, iColumn, iSpace, iMaxRows);
}

void test::print(double dValue, const std::string &sMessage, bool bExtraLine)
{
  std::string sM(sMessage);
  sM += std::string(" = ");
  std::cout << sM.c_str() << dValue << endl;
  if (bExtraLine)
  {
    std::cout << endl;
  }
}

void test::print(const std::string &sMessage, bool bExtraLine)
{
  std::cout << sMessage.c_str() << endl;
  if (bExtraLine)
  {
    std::cout << endl;
  }
}

void test::printValues(const cfl::Function &rF, const std::valarray<double> &rArg, const std::string &rTitle)
{
  std::valarray<double> uValues = getValues(rF, rArg);
  print(begin(uValues), end(uValues), rTitle);
}

void test::printTable(const std::vector<std::valarray<double>> &rValues,
                      const std::vector<std::string> &rNames,
                      const std::string &sMessage, unsigned iColumn,
                      unsigned iSpace, unsigned iMaxRows)
{
  PRECONDITION(rValues.size() == rNames.size());

  print(sMessage);
  for (unsigned i = 0; i < rValues.size(); i++)
  {
    std::cout << std::setw(iColumn) << rNames[i].c_str() << std::setw(iSpace) << "";
  }
  std::cout << endl;

  unsigned iSize = rValues.front().size();
  unsigned iRows = std::min(iSize, iMaxRows);
  unsigned iStart = (iSize - iRows) / 2;
  unsigned iEnd = (iSize + iRows) / 2;
  iEnd = min(iEnd, iSize);

  for (unsigned j = iStart; j < iEnd; j++)
  {
    for (unsigned i = 0; i < rValues.size(); i++)
    {
      ASSERT(rValues[i].size() == iSize);
      std::cout << std::setw(iColumn) << rValues[i][j] << std::setw(iSpace) << "";
    }
    std::cout << endl;
  }
  std::cout << std::endl;
}

void test::printTable(const std::vector<std::vector<double>> &rValues,
                      const std::vector<std::string> &rNames,
                      const std::string &sMessage, unsigned iColumn,
                      unsigned iSpace, unsigned iMaxRows)
{
  unsigned iSize = rValues.front().size();
  std::vector<std::valarray<double>> uV(rValues.size(), std::valarray<double>(iSize));
  for (unsigned i = 0; i < rValues.size(); i++)
  {
    std::copy(rValues[i].begin(), rValues[i].end(), begin(uV[i]));
  }
  printTable(uV, rNames, sMessage, iColumn, iSpace, iMaxRows);
}

void test::printTable(const std::vector<cfl::Function> &rF, const std::vector<std::string> &rNames,
                      const std::valarray<double> &rArg, const std::string &sMessage,
                      unsigned iColumn, unsigned iSpace, const std::string &sArg)
{
  PRECONDITION(rF.size() == rNames.size());

  std::vector<std::string> uNames(rNames.size() + 1);
  uNames.front() = sArg;
  std::copy(rNames.begin(), rNames.end(), uNames.begin() + 1);
  std::vector<std::valarray<double>>
      uValues(rF.size() + 1, std::valarray<double>(rArg.size()));
  uValues.front() = rArg;
  for (unsigned i = 0; i < rF.size(); i++)
  {
    uValues[i + 1] = getValues(rF[i], rArg);
  }
  printTable(uValues, uNames, sMessage, iColumn, iSpace, uValues.front().size());
}

double chi2(const cfl::Function &rErr, const std::valarray<double> &rArg)
{
  std::valarray<double> uErr = test::getValues(rErr, rArg);
  double dChi2 = std::inner_product(begin(uErr), end(uErr), begin(uErr), 0.);
  return dChi2;
}

void test::printChi2(const cfl::Function &rEstErr, const cfl::Function &rActErr,
                     const std::valarray<double> &rArg)
{
  print(chi2(rEstErr, rArg), "sum of squares of estimated errors");
  print(chi2(rActErr, rArg), "sum of squares of actual errors", true);
}

void test::printRisk(const cfl::Function &rOption, double dShift)
{
  print("RISK REPORT: ");
  double dCenter = 0.;
  double dL = -dShift;
  double dR = dShift;
  double dPrice = rOption(dCenter);
  cout << "price = " << dPrice << endl;
  if (rOption.belongs(dR) && rOption.belongs(dL))
  {
    double dValueLeft = rOption(dL);
    double dValueRight = rOption(dR);
    double dDelta = (dValueRight - dValueLeft) / (2. * dShift);
    double dGamma = 0.01 * (dValueRight - 2. * dPrice + dValueLeft) / (dShift * dShift);
    print(dDelta, "delta");
    print(dGamma, "one percent gamma", true);
  }
}

namespace testPrint
{
  void print(const cfl::Data::CashFlow &rCashFlow, const std::string &rName)
  {
    std::string sM(rName);
    sM += std::string(":");
    test::print(sM, false);
    test::print(rCashFlow.notional, "notional");
    test::print(rCashFlow.period, "period between payments");
    test::print(rCashFlow.numberOfPayments, "number of payments");
    test::print(rCashFlow.rate, "rate");
  }
} // namespace testPrint

void test::printCashFlow(const cfl::Data::CashFlow &rCashFlow, const std::string &rName)
{
  testPrint::print(rCashFlow, rName);
  cout << endl;
}

void test::printSwap(const cfl::Data::Swap &rSwap, const std::string &rName)
{
  testPrint::print(cfl::Data::CashFlow(rSwap), rName);
  if (rSwap.payFloat)
  {
    print("we pay float and receive fixed");
  }
  else
  {
    print("we pay fixed and receive float");
  }
}
