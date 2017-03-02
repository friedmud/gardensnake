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

#ifndef SCATTERING_H
#define SCATTERING_H

#include "Kernel.h"

class Scattering;

template<>
InputParameters validParams<Scattering>();


class Scattering : public Kernel
{
public:
  Scattering(const InputParameters & parameters);
  virtual ~Scattering();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const unsigned int _group;

  const MaterialProperty<std::vector<std::vector<Real> > > & _sigma_s;

  // The values of all of the fluxes
  std::vector<const VariableValue *> _vals;
};


#endif /* SCATTERING_H */
