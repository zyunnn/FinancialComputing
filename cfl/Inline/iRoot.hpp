// do not include this file

inline double cfl::Root::find(const cfl::Function &rF, double dL, double dR) const
{
  return m_uP->find(rF, dL, dR);
}
