// do not include this file

inline double cfl::MultiFunction::operator()(const std::valarray<double> &rX) const
{
  return (*m_pF)(rX);
}

inline bool cfl::MultiFunction::belongs(const std::valarray<double> &rX) const
{
  return m_pF->belongs(rX);
}

inline unsigned cfl::MultiFunction::dim() const
{
  return m_pF->dim();
}

// global inline functions

inline cfl::MultiFunction cfl::operator-(const cfl::MultiFunction &rF)
{
  return apply(rF, [](double dX)
               { return -dX; });
}

inline cfl::MultiFunction cfl::abs(const cfl::MultiFunction &rF)
{
  return apply(rF, [](double dX)
               { return std::abs(dX); });
}

inline cfl::MultiFunction cfl::exp(const cfl::MultiFunction &rF)
{
  return apply(rF, [](double dX)
               { return std::exp(dX); });
}

inline cfl::MultiFunction cfl::log(const cfl::MultiFunction &rF)
{
  return apply(rF, [](double dX)
               { return std::log(dX); });
}

inline cfl::MultiFunction cfl::sqrt(const cfl::MultiFunction &rF)
{
  return apply(rF, [](double dX)
               { return std::sqrt(dX); });
}

inline cfl::MultiFunction cfl::operator*(const cfl::MultiFunction &rF, const cfl::MultiFunction &rG)
{
  return apply(rF, rG, std::multiplies<double>());
}

inline cfl::MultiFunction cfl::operator*(double dX, const cfl::MultiFunction &rF)
{
  return apply(rF, [dX](double dY)
               { return dX * dY; });
}

inline cfl::MultiFunction cfl::operator*(const cfl::MultiFunction &rF, double dX)
{
  return dX * rF;
}

inline cfl::MultiFunction cfl::operator+(const cfl::MultiFunction &rF, const cfl::MultiFunction &rG)
{
  return apply(rF, rG, std::plus<double>());
}

inline cfl::MultiFunction cfl::operator+(double dX, const cfl::MultiFunction &rF)
{
  return apply(rF, [dX](double dY)
               { return dX + dY; });
}

inline cfl::MultiFunction cfl::operator+(const cfl::MultiFunction &rF, double dX)
{
  return dX + rF;
}

inline cfl::MultiFunction cfl::operator-(const cfl::MultiFunction &rF, const cfl::MultiFunction &rG)
{
  return apply(rF, rG, std::minus<double>());
}

inline cfl::MultiFunction cfl::operator-(double dX, const cfl::MultiFunction &rF)
{
  return apply(rF, [dX](double dY)
               { return dX - dY; });
}

inline cfl::MultiFunction cfl::operator-(const cfl::MultiFunction &rF, double dX)
{
  return apply(rF, [dX](double dY)
               { return dY - dX; });
}

inline cfl::MultiFunction cfl::operator/(const cfl::MultiFunction &rF, const cfl::MultiFunction &rG)
{
  return apply(rF, rG, std::divides<double>());
}

inline cfl::MultiFunction cfl::operator/(double dX, const cfl::MultiFunction &rF)
{
  return apply(rF, [dX](double dY)
               { return dX / dY; });
}

inline cfl::MultiFunction cfl::operator/(const cfl::MultiFunction &rF, double dX)
{
  return apply(rF, [dX](double dY)
               { return dY / dX; });
}

inline cfl::MultiFunction cfl::pow(const cfl::MultiFunction &rF, double dX)
{
  return apply(rF, [dX](double dY)
               { return std::pow(dY, dX); });
}
