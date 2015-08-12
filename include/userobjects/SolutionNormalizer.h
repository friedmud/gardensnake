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


#ifndef SOLUTIONNORMALIZER_H
#define SOLUTIONNORMALIZER_H

// Moose
#include "GeneralUserObject.h"
#include "MooseMesh.h"

//Forward Declarations
class RandomHitUserObject;
class SolutionNormalizer;

template<>
InputParameters validParams<SolutionNormalizer>();

class SolutionNormalizer :
  public GeneralUserObject
{
public:
  SolutionNormalizer(const InputParameters & parameters);

  virtual ~SolutionNormalizer() {}
  virtual void initialize(){}
  virtual void execute();
  virtual void finalize(){}
};

#endif
