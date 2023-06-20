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

#include "PeakFissionSource.h"

InputParameters
PeakFissionSource::validParams()
{
  InputParameters params = ZoneElementAverageValue::validParams();

  params.addRequiredCoupledVar("fluxes", "The fluxes");

  MooseEnum report("NORMALIZED_VALUE POSITION");

  params.addRequiredParam<MooseEnum>("report", report, "The type of value to report");

  params.addRequiredParam<Real>("center", "The x coordinate of the center of the domain");

  return params;
}

PeakFissionSource::PeakFissionSource(const InputParameters & parameters)
  : ZoneElementAverageValue(parameters),
    _report(getParam<MooseEnum>("report")),
    _center(getParam<Real>("center")),
    _nu_sigma_f(getMaterialProperty<std::vector<Real>>("nu_sigma_f"))
{
  unsigned int n = coupledComponents("fluxes");

  _fluxes.resize(n);

  for (unsigned int i = 0; i < _fluxes.size(); ++i)
    _fluxes[i] = &coupledValue("fluxes", i);
}

void
PeakFissionSource::initialize()
{
  ZoneElementAverageValue::initialize();
  _max_fission_rate = -std::numeric_limits<Real>::max();
  _max_position = -std::numeric_limits<Real>::max();
}

Real
PeakFissionSource::computeQpIntegral()
{
  Real fission_rate = 0;

  for (unsigned int i = 0; i < _fluxes.size(); i++)
    fission_rate += _nu_sigma_f[_qp][i] * (*_fluxes[i])[_qp];

  if (fission_rate > _max_fission_rate)
  {
    _max_fission_rate = fission_rate;
    _max_position = _q_point[_qp](0) - _center;
  }

  return fission_rate;
}

Real
PeakFissionSource::getValue()
{
  Real average = ZoneElementAverageValue::getValue();

  gatherProxyValueMax(_max_fission_rate, _max_position);

  switch (_report)
  {
    case 0:
      return _max_fission_rate / average;
    case 1:
      return _max_position;
    default:
      mooseError("Shouldn't happen!");
  }
}

void
PeakFissionSource::threadJoin(const UserObject & y)
{
  ZoneElementAverageValue::threadJoin(y);

  const PeakFissionSource & pps = static_cast<const PeakFissionSource &>(y);

  if (pps._max_fission_rate > _max_fission_rate)
  {
    _max_fission_rate = pps._max_fission_rate;
    _max_position = pps._max_position;
  }
}
