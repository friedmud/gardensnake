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

#include "PenaltyBC.h"

template<>
InputParameters validParams<PenaltyBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addParam<Real>("value", 0.0, "The value of the gradient on the boundary.");
  params.addParam<Real>("penalty", 1e10, "Penalty used for penalty*(u-value).");
  return params;
}

PenaltyBC::PenaltyBC(const std::string & name, InputParameters parameters) :
  IntegratedBC(name, parameters),
  _value(getParam<Real>("value")),
  _penalty(getParam<Real>("penalty"))
{}

Real
PenaltyBC::computeQpResidual()
{
  return _penalty*(_u[_qp]-_value);
}

Real
PenaltyBC::computeQpJacobian()
{
  return _penalty;
}
