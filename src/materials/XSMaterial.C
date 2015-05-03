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

#include "XSMaterial.h"

template<>
InputParameters validParams<XSMaterial>()
{
  InputParameters params = validParams<Material>();

  params.addRequiredParam<std::vector<Real> >("d0", "Diffusion coefficient for each Material for group 0");
  params.addRequiredParam<std::vector<Real> >("d1", "Diffusion coefficient for each Material for group 1");
  params.addRequiredParam<std::vector<Real> >("a0", "Absorption XS for each Material for group 0");
  params.addRequiredParam<std::vector<Real> >("a1", "Absorption XS for each Material for group 1");
  params.addRequiredParam<std::vector<Real> >("s0_1", "Downscatter XS for 0->1");
  params.addRequiredParam<std::vector<Real> >("nf0", "Fission XS for group 0");
  params.addRequiredParam<std::vector<Real> >("nf1", "Fission XS for group 1");

  params.addRequiredParam<std::vector<Real> >("zone_edges", "The beginning and ending of each zone");
  params.addRequiredParam<std::vector<Real> >("zones", "Each zone should go with with pair of zone_edges. ie there should be one more zone_edge than zones");

  return params;
}

XSMaterial::XSMaterial(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    _diffusivity(declareProperty<std::vector<Real> >("diffusivity")),
    _sigma_a(declareProperty<std::vector<Real> >("sigma_a")),
    _sigma_s(declareProperty<std::vector<std::vector<Real> > >("sigma_s")),
    _nu_sigma_f(declareProperty<std::vector<Real> >("nu_sigma_f")),
    _zone_edges(getParam<std::vector<Real> >("zone_edges")),
    _zone_numbers(getParam<std::vector<Real> >("zones"))
{
  const std::vector<Real> & d0 = getParam<std::vector<Real> >("d0");
  const std::vector<Real> & d1 = getParam<std::vector<Real> >("d1");
  const std::vector<Real> & a0 = getParam<std::vector<Real> >("a0");
  const std::vector<Real> & a1 = getParam<std::vector<Real> >("a1");
  const std::vector<Real> & s0_1 = getParam<std::vector<Real> >("s0_1");
  const std::vector<Real> & nf0 = getParam<std::vector<Real> >("nf0");
  const std::vector<Real> & nf1 = getParam<std::vector<Real> >("nf1");

  const unsigned int n_zones = d0.size();

  _zones.resize(n_zones);

  // Load up the Zones:

  for (unsigned int i=0; i < n_zones; i++)
  {
    Zone & _zone = _zones[i];

    _zone.diffusivity.resize(2);
    _zone.sigma_a.resize(2);
    _zone.nu_sigma_f.resize(2);

    _zone.sigma_s.resize(2);
    for (unsigned int j=0; j < 2; j++)
      _zone.sigma_s[j].resize(2);

    _zone.diffusivity[0] = d0[i];
    _zone.diffusivity[1] = d1[i];

    _zone.sigma_a[0] = a0[i];
    _zone.sigma_a[1] = a1[i];

    _zone.sigma_s[0][0] = -s0_1[i]; // Loss
    _zone.sigma_s[1][0] = s0_1[i]; // Gain

    _zone.nu_sigma_f[0] = nf0[i];
    _zone.nu_sigma_f[1] = nf1[i];
  }
}

void
XSMaterial::computeQpProperties()
{
  // Snag the x position of the center of this element
  Real x = _current_elem->centroid()(0);

  // Find the zone we fall in:
  unsigned int zone_entry = 0;
  for (; zone_entry<_zone_edges.size()-1; zone_entry++)
    if (_zone_edges[zone_entry] <= x && x <= _zone_edges[zone_entry+1])
      break;

  Zone & zone = _zones[_zone_numbers[zone_entry]];

  _diffusivity[_qp] = zone.diffusivity;
  _sigma_a[_qp] = zone.sigma_a;
  _sigma_s[_qp] = zone.sigma_s;
  _nu_sigma_f[_qp] = zone.nu_sigma_f;
}
