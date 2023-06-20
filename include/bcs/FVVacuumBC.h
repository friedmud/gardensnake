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
#pragma once

#ifndef FVVACUUMBC_H
#define FVVACUUMBC_H

#include "IntegratedBC.h"

// Forward Declarations
class FVVacuumBC;

/**
 * Applies a DirichletBC using integral(penalty*(u - value))
 */
class FVVacuumBC : public IntegratedBC
{
public:
  static InputParameters validParams();

  FVVacuumBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const unsigned int _group;

  const MaterialProperty<std::vector<Real>> & _diffusivity;
};

#endif // FVVACUUMBC_H
