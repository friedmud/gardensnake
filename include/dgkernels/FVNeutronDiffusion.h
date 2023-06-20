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
#ifndef FVNEUTRONDIFFUSION_H
#define FVNEUTRONDIFFUSION_H

#include "DGKernel.h"

// Forward Declarations
class FVNeutronDiffusion;

class FVNeutronDiffusion : public DGKernel
{
public:
  static InputParameters validParams();

  FVNeutronDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);

  const unsigned int _group;

  const MaterialProperty<std::vector<Real>> & _diffusivity;
  const MaterialProperty<std::vector<Real>> & _diffusivity_neighbor;
};

#endif
