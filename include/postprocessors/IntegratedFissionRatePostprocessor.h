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
// #ifndef INTEGRATEDFISSIONRATEPOSTPROCESSOR_H
// #define INTEGRATEDFISSIONRATEPOSTPROCESSOR_H

#include "ZoneElementIntegralPostprocessor.h"

// Forward Declarations
// class IntegratedFissionRatePostprocessor;

/**
 * This postprocessor computes the volume of a specified block.
 */
class IntegratedFissionRatePostprocessor : public ZoneElementIntegralPostprocessor
{
public:
  static InputParameters validParams();

  IntegratedFissionRatePostprocessor(const InputParameters & parameters);

protected:
  virtual Real computeQpIntegral();

  bool _new;

  const MaterialProperty<std::vector<Real>> & _nu_sigma_f;

  // The values of all of the fluxes
  std::vector<const VariableValue *> _vals;
};

// #endif
