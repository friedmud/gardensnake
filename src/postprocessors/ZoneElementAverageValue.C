/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "ZoneElementAverageValue.h"

template<>
InputParameters validParams<ZoneElementAverageValue>()
{
  InputParameters params = validParams<ZoneElementIntegralPostprocessor>();
  return params;
}

ZoneElementAverageValue::ZoneElementAverageValue(const InputParameters & parameters) :
    ZoneElementIntegralPostprocessor(parameters),
    _volume(0)
{}

void
ZoneElementAverageValue::initialize()
{
  ZoneElementIntegralPostprocessor::initialize();
  _volume = 0;
}

void
ZoneElementAverageValue::execute()
{
  // The zero is here because each element only falls in one zone - so it's sufficient to do this check for the first qp
  if (std::find(_active_zones.begin(), _active_zones.end(), (unsigned int)_zone[0]) != _active_zones.end())
  {
    ZoneElementIntegralPostprocessor::execute();
    _volume += _current_elem_volume;
  }
}

Real
ZoneElementAverageValue::getValue()
{
  Real integral = ZoneElementIntegralPostprocessor::getValue();

  gatherSum(_volume);

  return integral / _volume;
}

void
ZoneElementAverageValue::threadJoin(const UserObject & y)
{
  ZoneElementIntegralPostprocessor::threadJoin(y);
  const ZoneElementAverageValue & pps = static_cast<const ZoneElementAverageValue &>(y);
  _volume += pps._volume;
}
