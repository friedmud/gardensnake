/****************************************************************/
/*               Do NOT MODIFY THIS HEADER                      */
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

#include "TotalFluxRMSFractionalChange.h"

template<>
InputParameters validParams<TotalFluxRMSFractionalChange>()
{
  InputParameters params = validParams<ElementAverageValue>();

  params.addRequiredCoupledVar("fluxes", "The fluxes");

  return params;
}

TotalFluxRMSFractionalChange::TotalFluxRMSFractionalChange(const InputParameters & parameters) :
    ElementAverageValue(parameters)
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
TotalFluxRMSFractionalChange::computeQpIntegral()
{
  Real total_flux = 0;
  Real total_flux_old = 0;

  for (unsigned int i=0; i<_fluxes.size(); i++)
  {
    total_flux += (*_fluxes[i])[_qp];
    total_flux_old += (*_fluxes_old[i])[_qp];
  }

  Real change = (total_flux - total_flux_old) / total_flux;

  return change*change;
}

Real
TotalFluxRMSFractionalChange::getValue()
{
  Real mean = ElementAverageValue::getValue();

  return std::sqrt(mean);
}
