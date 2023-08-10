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

#include "Fission.h"

registerMooseObject("GardensnakeApp", Fission);

InputParameters
Fission::validParams()
{
  InputParameters params = Kernel::validParams();

  params.addRequiredCoupledVar("fluxes", "All of the fluxes");
  params.addRequiredParam<PostprocessorName>("k", "The eigenvalue for the 1/k");

  return params;
}

Fission::Fission(const InputParameters & parameters)
  : Kernel(parameters),
    _group(_var.number()),
    _nu_sigma_f(getMaterialProperty<std::vector<Real>>("nu_sigma_f")),
    _k(getPostprocessorValue("k"))
{
  unsigned int n = coupledComponents("fluxes");

  _vals.resize(n);

  for (unsigned int i = 0; i < _vals.size(); ++i)
    _vals[i] = &coupledValueOld("fluxes", i);
}

// Fission::~Fission() {}

Real
Fission::computeQpResidual()
{
  Real r = 0;

  for (unsigned int i = 0; i < _vals.size(); i++)
    r += _nu_sigma_f[_qp][i] * (*_vals[i])[_qp];

  return -(1.0 / _k) * r;
}

Real
Fission::computeQpJacobian()
{
  return 0;
}

Real
Fission::computeQpOffDiagJacobian(unsigned int jvar)
{
  return 0;
}
