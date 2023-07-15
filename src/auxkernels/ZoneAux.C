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

#include "ZoneAux.h"

registerMooseObject("GardensnakeApp", ZoneAux);

InputParameters
ZoneAux::validParams()
{
  // InputParameters params = validParams<AuxKernel>();
  InputParameters params = AuxKernel::validParams();

  params.addRequiredParam<std::vector<Real>>("zone_edges", "The beginning and ending of each zone");
  params.addRequiredParam<std::vector<Real>>("zones",
                                             "Each zone should go with with pair of zone_edges. ie "
                                             "there should be one more zone_edge than zones");

  return params;
}

ZoneAux::ZoneAux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _zone_edges(getParam<std::vector<Real>>("zone_edges")),
    _zone_numbers(getParam<std::vector<Real>>("zones"))
{
}

Real
ZoneAux::computeValue()
{
  // Snag the x position of the center of this element
  Real x = _current_elem->centroid()(0);

  // Find the zone we fall in:
  unsigned int zone_entry = 0;
  for (; zone_entry < _zone_edges.size() - 1; zone_entry++)
    if (_zone_edges[zone_entry] <= x && x <= _zone_edges[zone_entry + 1])
      break;

  return _zone_numbers[zone_entry];
}
