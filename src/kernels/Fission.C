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


template<>
InputParameters validParams<Fission>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("fluxes", "All of the fluxes");

  return params;
}


Fission::Fission(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    _group(_var.number()),
    _nu_sigma_f(getMaterialProperty<std::vector<Real> >("nu_sigma_f"))
{
  unsigned int n = coupledComponents("fluxes");

  _vals.resize(n);

  for (unsigned int i=0; i<_vals.size(); ++i)
    _vals[i] = &coupledValue("fluxes", i);
}

Fission::~Fission()
{

}

Real
Fission::computeQpResidual()
{
  Real r = 0;

  for (unsigned int i=0; i<_vals.size(); i++)
    r += _nu_sigma_f[_qp][i] * (*_vals[i])[_qp];

  return r;
}

Real
Fission::computeQpJacobian()
{
  return -_nu_sigma_f[_qp][_group];
}


Real
Fission::computeQpOffDiagJacobian(unsigned int jvar)
{
  return -_nu_sigma_f[_qp][jvar];
}
