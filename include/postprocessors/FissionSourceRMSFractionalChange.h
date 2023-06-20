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
#ifndef FISSIONSOURCERMSFRACTIONALCHANGE_H
#define FISSIONSOURCERMSFRACTIONALCHANGE_H

#include "ZoneElementAverageValue.h"

// Forward Declarations
class FissionSourceRMSFractionalChange;

class FissionSourceRMSFractionalChange : public ZoneElementAverageValue
{
public:
  static InputParameters validParams();

  FissionSourceRMSFractionalChange(const InputParameters & parameters);

  virtual Real getValue();

protected:
  virtual Real computeQpIntegral();

  const MaterialProperty<std::vector<Real>> & _nu_sigma_f;

  // The values of all of the fluxes
  std::vector<const VariableValue *> _fluxes;
  std::vector<const VariableValue *> _fluxes_old;
};

#endif
