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

#include "FVVacuumBC.h"

template<>
InputParameters validParams<FVVacuumBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  return params;
}

FVVacuumBC::FVVacuumBC(const std::string & name, InputParameters parameters) :
    IntegratedBC(name, parameters),
    _group(_var.number()),
    _diffusivity(getMaterialProperty<std::vector<Real> >("diffusivity"))
{}

Real
FVVacuumBC::computeQpResidual()
{
  Real delta_x = _current_elem->hmax();

  return ((2.0*_diffusivity[_qp][_group]) / delta_x) * ( 1.0 / ( 1.0 + (4.0*_diffusivity[_qp][_group] / delta_x) ) ) * _u[_qp];
}

Real
FVVacuumBC::computeQpJacobian()
{
  Real delta_x = _current_elem->hmax();

  return ((2.0*_diffusivity[_qp][_group]) / delta_x) * ( 1.0 / ( 1.0 + (4.0*_diffusivity[_qp][_group] / delta_x) ) );
}
