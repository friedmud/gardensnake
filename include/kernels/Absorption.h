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

#ifndef ABSORPTION_H
#define ABSORPTION_H

#include "Kernel.h"

class Absorption;

template<>
InputParameters validParams<Absorption>();


class Absorption : public Kernel
{
public:
  Absorption(const std::string & name, InputParameters parameters);
  virtual ~Absorption();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const unsigned int _group;

  MaterialProperty<std::vector<Real> > & _sigma_a;
};


#endif /* ABSORPTION_H */
