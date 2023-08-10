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
// #ifndef PEAKFISSIONSOURCE_H
// #define PEAKFISSIONSOURCE_H

#include "ZoneElementAverageValue.h"

// Forward Declarations
// class PeakFissionSource;


class PeakFissionSource : public ZoneElementAverageValue
{
public:
static InputParameters validParams();

  PeakFissionSource(const InputParameters & parameters);

  virtual void initialize();
  virtual Real getValue();
  virtual void threadJoin(const UserObject & y);

protected:
  virtual Real computeQpIntegral();

  const unsigned int _report;

  const Real & _center;

  const MaterialProperty<std::vector<Real>> & _nu_sigma_f;

  // The values of all of the fluxes
  std::vector<const VariableValue *> _fluxes;
  std::vector<const VariableValue *> _fluxes_old;

  /// The maximum value of the fission rate
  Real _max_fission_rate;

  /// The x coordinate from the center of the domain of the maximum fission rate
  Real _max_position;
};

// #endif
