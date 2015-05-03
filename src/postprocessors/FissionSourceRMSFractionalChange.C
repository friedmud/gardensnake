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

#include "FissionSourceRMSFractionalChange.h"

template<>
InputParameters validParams<FissionSourceRMSFractionalChange>()
{
  InputParameters params = validParams<ElementAverageValue>();

  params.addRequiredCoupledVar("fluxes", "The fluxes");

  return params;
}

FissionSourceRMSFractionalChange::FissionSourceRMSFractionalChange(const std::string & name, InputParameters parameters) :
    ElementAverageValue(name, parameters),
    _nu_sigma_f(getMaterialProperty<std::vector<Real> >("nu_sigma_f"))
{
  unsigned int n = coupledComponents("fluxes");

  _fluxes.resize(n);
  _fluxes_old.resize(n);

  for (unsigned int i=0; i<_fluxes.size(); ++i)
  {
    _fluxes[i] = &coupledValue("fluxes", i);
    _fluxes_old[i] = &coupledValueOld("fluxes", i);
  }
}

Real
FissionSourceRMSFractionalChange::computeQpIntegral()
{
  Real fission_rate = 0;
  Real fission_rate_old = 0;

  for (unsigned int i=0; i<_fluxes.size(); i++)
  {
    fission_rate += _nu_sigma_f[_qp][i] * (*_fluxes[i])[_qp];
    fission_rate_old += _nu_sigma_f[_qp][i] * (*_fluxes_old[i])[_qp];
  }

  Real change = (fission_rate - fission_rate_old) / fission_rate;

  if (isnan(change))
    return 0;

  return change*change;
}

Real
FissionSourceRMSFractionalChange::getValue()
{
  Real mean = ElementAverageValue::getValue();

  return std::sqrt(mean);
}
