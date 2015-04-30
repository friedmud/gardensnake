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

#ifndef FVNEUTRONDIFFUSION_H
#define FVNEUTRONDIFFUSION_H

#include "DGKernel.h"

//Forward Declarations
class FVNeutronDiffusion;

template<>
InputParameters validParams<FVNeutronDiffusion>();

class FVNeutronDiffusion : public DGKernel
{
public:
  FVNeutronDiffusion(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);

  MaterialProperty<Real> & _diffusivity;
  MaterialProperty<Real> & _diffusivity_neighbor;
};

#endif
