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

#ifndef FVVACUUMBC_H
#define FVVACUUMBC_H

#include "IntegratedBC.h"


//Forward Declarations
class FVVacuumBC;

template<>
InputParameters validParams<FVVacuumBC>();

/**
 * Applies a DirichletBC using integral(penalty*(u - value))
 */
class FVVacuumBC : public IntegratedBC
{
public:

  FVVacuumBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const unsigned int _group;

  const MaterialProperty<std::vector<Real> > & _diffusivity;
};

#endif //FVVACUUMBC_H
