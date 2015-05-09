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

#include "ZoneElementIntegralPostprocessor.h"

template<>
InputParameters validParams<ZoneElementIntegralPostprocessor>()
{
  InputParameters params = validParams<ElementPostprocessor>();

  params.addRequiredCoupledVar("zone", "The zone");

  params.addRequiredParam<std::vector<unsigned int> >("active_zones", "The zones where this postprocessor should be active");

  return params;
}

ZoneElementIntegralPostprocessor::ZoneElementIntegralPostprocessor(const std::string & name, InputParameters parameters) :
    ElementPostprocessor(name, parameters),
    _qp(0),
    _integral_value(0),
    _zone(coupledValue("zone")),
    _active_zones(getParam<std::vector<unsigned int> >("active_zones"))
{}

void
ZoneElementIntegralPostprocessor::initialize()
{
  _integral_value = 0;
}

void
ZoneElementIntegralPostprocessor::execute()
{
  // The zero is here because each element only falls in one zone - so it's sufficient to do this check for the first qp
  if (std::find(_active_zones.begin(), _active_zones.end(), (unsigned int)_zone[0]) != _active_zones.end())
    _integral_value += computeIntegral();
}

Real
ZoneElementIntegralPostprocessor::getValue()
{
  gatherSum(_integral_value);
  return _integral_value;
}

void
ZoneElementIntegralPostprocessor::threadJoin(const UserObject & y)
{
  const ZoneElementIntegralPostprocessor & pps = static_cast<const ZoneElementIntegralPostprocessor &>(y);
  _integral_value += pps._integral_value;
}

Real
ZoneElementIntegralPostprocessor::computeIntegral()
{
  Real sum = 0;

  for (_qp=0; _qp<_qrule->n_points(); _qp++)
      sum += _JxW[_qp]*_coord[_qp]*computeQpIntegral();

  return sum;
}
