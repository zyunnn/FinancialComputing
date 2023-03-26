#include "test/Main.hpp"
#include "test/Data.hpp"
#include "test/Print.hpp"
#include "home3/Output.hpp"
#include "home3/home3.hpp"

using namespace test;
using namespace cfl;
using namespace std;
using namespace test::Data;

void testInterp(const cfl::Interp &rInterp, const std::string &sInterp)
{
  print(sInterp.c_str());
  std::string sInterpNodes("Comparison at the nodes of interpolation");
  std::string sRandNodes("Comparison at the random arguments");
  double dL = 0;
  double dR = 1;
  unsigned iN = 8;
  unsigned iColumn = 10;
  unsigned iWidth = 8;
  std::valarray<double> uX = getArg(dL, dR, iN);
  std::valarray<double> uY = getRandArg(dL, dR, iN);
  Function uArg([](double dX)
                { return dX; });
  double dC = 1;
  double dT = 2;

  std::vector<std::string> uNames = {"exact", "numeric", "error"};
  std::vector<Function> uF(3);

  std::valarray<double> uV(dC, uX.size());
  cout << "Interpolation  of cubic function: f(x) = "
       << dC << " + 0.5 + x^2 + " << dT << "x^3" << endl
       << endl;
  uV = dC + 0.5 + uX * uX + dT * uX * uX * uX;
  uF[0] = dC + 0.5 + uArg * uArg + dT * uArg * uArg * uArg;
  uF[1] = rInterp.interpolate(begin(uX), end(uX), begin(uV));
  uF[2] = cfl::abs(uF[1] - uF[0]);
  printTable(uF, uNames, uX, sInterpNodes, iColumn, iWidth);
  printTable(uF, uNames, uY, sRandNodes, iColumn, iWidth);

  print("Interpolation of exponential function: f(x) = exp(x)");
  uV = exp(uX);
  uF[0] = exp(uArg);
  uF[1] = rInterp.interpolate(begin(uX), end(uX), begin(uV));
  uF[2] = cfl::abs(uF[1] - uF[0]);
  printTable(uF, uNames, uX, sInterpNodes, iColumn, iWidth);
  printTable(uF, uNames, uY, sRandNodes, iColumn, iWidth);

  print("Interpolation of itself. Should get zero errors everywhere.");
  uV = getValues(uF.front(), uX);
  uF[0] = uF[1];
  uF[1] = rInterp.interpolate(begin(uX), end(uX), begin(uV));
  uF[2] = cfl::abs(uF[1] - uF[0]);
  printTable(uF, uNames, uX, sInterpNodes, iColumn, iWidth);
  printTable(uF, uNames, uY, sRandNodes, iColumn, iWidth);
};

void cspline()
{
  Interp uSpline = prb::cspline();
  testInterp(uSpline, "CUBIC SPLINE INTERPOLATION WITH GSL");
}

void akima()
{
  Interp uSpline = prb::akima();
  testInterp(uSpline, "AKIMA INTERPOLATION WITH GSL");
}

void steffen()
{
  Interp uSpline = prb::steffen();
  testInterp(uSpline, "STEFFEN INTERPOLATION WITH GSL");
}

void forwardCarryInterp()
{
  test::print("FORWARD PRICES BY INTERPOLATION OF COST-OF-CARRY RATES");

  double dSpot = 100;
  double dInitialTime = 1.;

  auto uF = test::Data::getForward(dSpot, dInitialTime);

  double dInitialCarryRate =
      std::log(uF.second.front() / dSpot) / (uF.first.front() - dInitialTime);
  print(dInitialCarryRate, "initial carry rate", true);

  Function uResult =
      prb::forwardCarryInterp(dSpot, uF.first, uF.second,
                              dInitialCarryRate, dInitialTime,
                              cfl::NInterp::linear());
  print("Linear interpolation:");

  double dInterval = uF.first.back() - dInitialTime;
  test::Data::print(uResult, dInitialTime, dInterval);
}

void forwardCarrySteffenInterp()
{
  test::print("FORWARD PRICES  BY STEFFEN INTERPOLATION OF COST-OF-CARRY RATES");

  double dSpot = 100;
  double dInitialTime = 1.;

  auto uF = test::Data::getForward(dSpot, dInitialTime);

  Function uResult = prb::forwardCarrySteffenInterp(dSpot, uF.first,
                                                    uF.second, dInitialTime);

  double dInterval = uF.first.back() - dInitialTime;
  test::Data::print(uResult, dInitialTime, dInterval);
}

void volatilityVarInterp()
{
  test::print("VOLATILITY CURVE BY INTERPOLATION OF VARIANCE CURVE");

  double dInitialTime = 1.;
  auto uV = test::Data::getVol(dInitialTime);

  Function uResult = prb::volatilityVarInterp(uV.first, uV.second,
                                              dInitialTime, cfl::NInterp::linear());
  print("Linear interpolation:");

  double dInterval = uV.first.back() - dInitialTime;
  test::Data::print(uResult, dInitialTime, dInterval);
}


std::function<void()> test_home3()
{
  return []()
  {
    print("ONE-DIMENSIONAL INTERPOLATION");

    cspline();
    steffen();
    akima();
    forwardCarryInterp();
    forwardCarrySteffenInterp();
    volatilityVarInterp();
  };
}

int main()
{
  project(test_home3(), PROJECT_NAME, PROJECT_NAME,
          "Homework 3");
}
