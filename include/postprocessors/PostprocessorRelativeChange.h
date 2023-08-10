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

// #ifndef POSTPROCESSORRELATIVECHANGE_H
// #define POSTPROCESSORRELATIVECHANGE_H

#include "GeneralPostprocessor.h"

// Forward Declarations
// class PostprocessorRelativeChange;

// template<>
// InputParameters validParams<PostprocessorRelativeChange>();

class PostprocessorRelativeChange : public GeneralPostprocessor
{
public:
  static InputParameters validParams();

  PostprocessorRelativeChange(const InputParameters & parameters);

  virtual void initialize() {}
  virtual void execute() {}

  virtual Real getValue();

protected:
  const PostprocessorValue & _pp;
  const PostprocessorValue & _pp_old;
};

// #endif // POSTPROCESSORRELATIVECHANGE_H
