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

// #ifndef ZONEELEMENTINTEGRALPOSTPROCESSOR_H
// #define ZONEELEMENTINTEGRALPOSTPROCESSOR_H

#include "ElementPostprocessor.h"

//Forward Declarations
// class ZoneElementIntegralPostprocessor;


class ZoneElementIntegralPostprocessor : public ElementPostprocessor
{
public:
static InputParameters validParams();

  ZoneElementIntegralPostprocessor(const InputParameters & parameters);

  virtual void initialize();
  virtual void execute();
  virtual void threadJoin(const UserObject & y);
  virtual Real getValue();

protected:
  virtual Real computeQpIntegral() = 0;
  virtual Real computeIntegral();

  unsigned int _qp;

  Real _integral_value;

  const VariableValue & _zone;
  const std::vector<unsigned int> & _active_zones;
};

// #endif
