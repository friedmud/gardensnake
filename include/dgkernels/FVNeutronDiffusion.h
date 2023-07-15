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
// #ifndef FVNEUTRONDIFFUSION_H
// #define FVNEUTRONDIFFUSION_H

#include "DGKernel.h"


// For AD DG Kernel:
// #include "ADDGKernel.h"
/**
 * DG kernel for diffusion
 *
 * General DG kernel that this class can handle is:
 * \f$ { \nabla u * n_e} [v] + epsilon { \nabla v * n_e } [u] + (sigma / |e| * [u][v]) \f$
 *
 * \f$ [a] = [ a_1 - a_2 ] \f$
 * \f$ {a} = 0.5 * (a_1 + a_2) \f$
 *
 */ /* The previous is taken from Zapdos app, and could be related to AD DG kernels only, or for specific physics simualted there. Not checked! */


// Forward Declarations
// class FVNeutronDiffusion;

class FVNeutronDiffusion : public DGKernel
{
public:
  static InputParameters validParams();

  FVNeutronDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type); // Not needed in AD DG kernels.

  const unsigned int _group;

  // Related to the diffusion coefficient
  const MaterialProperty<std::vector<Real>> & _diffusivity;
  const MaterialProperty<std::vector<Real>> & _diffusivity_neighbor;
};

// #endif
