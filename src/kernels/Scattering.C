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

#include "Scattering.h"


template<>
InputParameters validParams<Scattering>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("fluxes", "All of the fluxes");

  return params;
}


Scattering::Scattering(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    _group(_var.number()),
    _sigma_s(getMaterialProperty<std::vector<std::vector<Real> > >("sigma_s"))
{
  unsigned int n = coupledComponents("fluxes");

  _vals.resize(n);

  for (unsigned int i=0; i<_vals.size(); ++i)
    _vals[i] = &coupledValue("fluxes", i);
}

Scattering::~Scattering()
{

}

Real
Scattering::computeQpResidual()
{
  Real r = 0;

  for (unsigned int i=0; i<_vals.size(); i++)
    r += _sigma_s[_qp][_group][i] * (*_vals[i])[_qp];

  return r;
}

Real
Scattering::computeQpJacobian()
{
  return _sigma_s[_qp][_group][_group];
}


Real
Scattering::computeQpOffDiagJacobian(unsigned int jvar)
{
  return _sigma_s[_qp][_group][jvar];
}
