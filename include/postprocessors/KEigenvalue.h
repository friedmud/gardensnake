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

#ifndef KEIGENVALUE_H
#define KEIGENVALUE_H

#include "GeneralPostprocessor.h"

// Forward Declarations
class KEigenvalue;

// template<>
// InputParameters validParams<KEigenvalue>();

class KEigenvalue : public GeneralPostprocessor
{
public:
  static InputParameters validParams();

  KEigenvalue(const InputParameters & parameters);

  virtual void initialize() {}
  virtual void execute() {}

  /**
   * This will return the degrees of freedom in the system.
   */
  virtual Real getValue();

protected:
  const PostprocessorValue & _fission_rate;
  const PostprocessorValue & _fission_rate_old;

  const PostprocessorValue & _old_eigenvalue;
};

#endif // KEIGENVALUE_H
