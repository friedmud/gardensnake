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

#include "FVNeutronDiffusion.h"

#include <cmath>

InputParameters
FVNeutronDiffusion::validParams()
{
  InputParameters params = DGKernel::validParams();
  return params;
}

FVNeutronDiffusion::FVNeutronDiffusion(const InputParameters & parameters)
  : DGKernel(parameters),
    _group(_var.number()),
    _diffusivity(getMaterialProperty<std::vector<Real>>("diffusivity")),
    _diffusivity_neighbor(getNeighborMaterialProperty<std::vector<Real>>("diffusivity"))
{
}

Real
FVNeutronDiffusion::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;

  const double delta_x = _current_elem->hmax();
  const double delta_x_neighbor = _neighbor_elem->hmax();

  Real weighted_D = ((_diffusivity_neighbor[_qp][_group] * _u_neighbor[_qp] +
                      _diffusivity[_qp][_group] * _u[_qp]) /
                     (_diffusivity_neighbor[_qp][_group] + _diffusivity[_qp][_group]));

  switch (type)
  {
    case Moose::Element:
    {
      RealVectorValue grad_u((weighted_D - _u[_qp]) / (delta_x / 2.0), 0, 0);

      r = -_diffusivity[_qp][_group] * (grad_u * _normals[_qp]);
      break;
    }
    case Moose::Neighbor:
    {
      RealVectorValue grad_u_neighbor(
          (weighted_D - _u_neighbor[_qp]) / (delta_x_neighbor / 2.0), 0, 0);

      r = _diffusivity_neighbor[_qp][_group] * (grad_u_neighbor * -_normals[_qp]);
      break;
    }
  }

  return r;
}

Real
FVNeutronDiffusion::computeQpJacobian(Moose::DGJacobianType type)
{
  Real r = 0;

  const double delta_x = _current_elem->hmax();
  const double delta_x_neighbor = _neighbor_elem->hmax();

  switch (type)
  {
    case Moose::ElementElement:
    {
      Real weighted_D = (-_diffusivity_neighbor[_qp][_group] /
                         (_diffusivity_neighbor[_qp][_group] + _diffusivity[_qp][_group]));
      RealVectorValue grad_u(weighted_D / (delta_x / 2.0), 0, 0);

      r = -_diffusivity[_qp][_group] * (grad_u * _normals[_qp]);

      break;
    }

    case Moose::ElementNeighbor:
    {
      Real weighted_D = (_diffusivity_neighbor[_qp][_group] /
                         (_diffusivity_neighbor[_qp][_group] + _diffusivity[_qp][_group]));
      RealVectorValue grad_u(weighted_D / (delta_x / 2.0), 0, 0);

      r = -_diffusivity[_qp][_group] * (grad_u * _normals[_qp]);
      break;
    }

    case Moose::NeighborElement:
    {

      Real weighted_D = (-_diffusivity[_qp][_group] /
                         (_diffusivity_neighbor[_qp][_group] + _diffusivity[_qp][_group]));
      RealVectorValue grad_u_neighbor(weighted_D / (delta_x_neighbor / 2.0), 0, 0);

      r = -_diffusivity_neighbor[_qp][_group] * (grad_u_neighbor * -_normals[_qp]);
      break;
    }

    case Moose::NeighborNeighbor:
    {
      Real weighted_D = (_diffusivity[_qp][_group] /
                         (_diffusivity_neighbor[_qp][_group] + _diffusivity[_qp][_group]));
      RealVectorValue grad_u_neighbor(weighted_D / (delta_x_neighbor / 2.0), 0, 0);

      r = -_diffusivity_neighbor[_qp][_group] * (grad_u_neighbor * -_normals[_qp]);
      break;
    }
  }

  return r;
}
