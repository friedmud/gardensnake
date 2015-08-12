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

#ifndef FISSION_H
#define FISSION_H

#include "Kernel.h"

class Fission;

template<>
InputParameters validParams<Fission>();


class Fission : public Kernel
{
public:
  Fission(const InputParameters & parameters);
  virtual ~Fission();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const unsigned int _group;

  const MaterialProperty<std::vector<Real> > & _nu_sigma_f;

  // The values of all of the fluxes
  std::vector<VariableValue *> _vals;

  const PostprocessorValue & _k;
};


#endif /* FISSION_H */
