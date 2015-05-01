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

#include "IntegratedFissionRatePostprocessor.h"

template<>
InputParameters validParams<IntegratedFissionRatePostprocessor>()
{
  InputParameters params = validParams<ElementIntegralPostprocessor>();

  params.addRequiredCoupledVar("fluxes", "All of the fluxes");

  return params;
}

IntegratedFissionRatePostprocessor::IntegratedFissionRatePostprocessor(const std::string & name, InputParameters parameters) :
    ElementIntegralPostprocessor(name, parameters),
    _nu_sigma_f(getMaterialProperty<std::vector<Real> >("nu_sigma_f"))
{
  unsigned int n = coupledComponents("fluxes");

  _vals.resize(n);

  for (unsigned int i=0; i<_vals.size(); ++i)
    _vals[i] = &coupledValue("fluxes", i);
}

Real
IntegratedFissionRatePostprocessor::computeQpIntegral()
{
  Real r = 0;

  for (unsigned int i=0; i<_vals.size(); i++)
    r += _nu_sigma_f[_qp][i] * (*_vals[i])[_qp];

  return r;
}
