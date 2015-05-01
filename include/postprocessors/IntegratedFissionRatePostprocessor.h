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

#ifndef INTEGRATEDFISSIONRATEPOSTPROCESSOR_H
#define INTEGRATEDFISSIONRATEPOSTPROCESSOR_H

#include "ElementIntegralPostprocessor.h"

//Forward Declarations
class IntegratedFissionRatePostprocessor;

template<>
InputParameters validParams<IntegratedFissionRatePostprocessor>();

/**
 * This postprocessor computes the volume of a specified block.
 */
class IntegratedFissionRatePostprocessor : public ElementIntegralPostprocessor
{
public:
  IntegratedFissionRatePostprocessor(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpIntegral();

  MaterialProperty<std::vector<Real> > & _nu_sigma_f;

  // The values of all of the fluxes
  std::vector<VariableValue *> _vals;
};

#endif
