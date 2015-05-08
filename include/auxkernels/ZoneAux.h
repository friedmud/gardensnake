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

#ifndef ZONEAUX_H
#define ZONEAUX_H

#include "AuxKernel.h"


//Forward Declarations
class ZoneAux;

template<>
InputParameters validParams<ZoneAux>();

/**
 * Constant auxiliary value
 */
class ZoneAux : public AuxKernel
{
public:

  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  ZoneAux(const std::string & name, InputParameters parameters);

  virtual ~ZoneAux() {}

protected:
  virtual Real computeValue();

  /// Edges of each zone
  const std::vector<Real> & _zone_edges;

  /// Each zone that goes with the zone_edges
  const std::vector<Real> & _zone_numbers;
};

#endif //ZONEAUX_H
