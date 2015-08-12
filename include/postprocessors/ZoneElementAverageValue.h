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

#ifndef ZONEELEMENTAVERAGEVALUE_H
#define ZONEELEMENTAVERAGEVALUE_H

#include "ZoneElementIntegralPostprocessor.h"

//Forward Declarations
class ZoneElementAverageValue;

template<>
InputParameters validParams<ZoneElementAverageValue>();

class ZoneElementAverageValue : public ZoneElementIntegralPostprocessor
{
public:
  ZoneElementAverageValue(const InputParameters & parameters);

  virtual void initialize();
  virtual void execute();
  virtual Real getValue();
  virtual void threadJoin(const UserObject & y);

protected:
  Real _volume;
};

#endif
