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

#include "Absorption.h"

InputParameters
Absorption::validParams()
{
  InputParameters params = Kernel::validParams();

  return params;
}

Absorption::Absorption(const InputParameters & parameters)
  : Kernel(parameters),
    _group(_var.number()),
    _sigma_a(getMaterialProperty<std::vector<Real>>("sigma_a"))
{
}

Absorption::~Absorption() {}

Real
Absorption::computeQpResidual()
{
  // This is positive because it's always a loss
  return _sigma_a[_qp][_group] * _u[_qp];
}

Real
Absorption::computeQpJacobian()
{
  // This is positive because it's always a loss
  return _sigma_a[_qp][_group];
}
