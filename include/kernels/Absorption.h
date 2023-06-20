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
#ifndef ABSORPTION_H
#define ABSORPTION_H

#include "Kernel.h"

class Absorption;

class Absorption : public Kernel
{
public:
  static InputParameters validParams();

  Absorption(const InputParameters & parameters);

  virtual ~Absorption();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const unsigned int _group;

  const MaterialProperty<std::vector<Real>> & _sigma_a;
};

#endif /* ABSORPTION_H */
