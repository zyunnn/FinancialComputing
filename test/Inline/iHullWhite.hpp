// do not include this file
inline cfl::Data::Swap test::HullWhite::swapParameters()
{
  cfl::Data::Swap uSwap;
  uSwap.notional = c_dNotional;
  uSwap.rate = c_dYield;
  uSwap.period = c_dPeriod;
  uSwap.numberOfPayments = c_iNumberOfPeriods;
  uSwap.payFloat = true;
  return uSwap;
}

inline std::vector<double> test::HullWhite::exerciseTimes()
{
  unsigned iExerciseTimes = 12;
  return test::getTimes(c_dInitialTime, c_dMaturity, iExerciseTimes);
}

inline std::vector<double> test::HullWhite::barrierTimes()
{
  unsigned iBarrierTimes = 10;
  double dBarrierMaturity = c_dMaturity - 0.1;
  return test::getTimes(c_dInitialTime, dBarrierMaturity, iBarrierTimes);
}
