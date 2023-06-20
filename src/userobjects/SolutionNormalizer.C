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

#include "SolutionNormalizer.h"
#include "FEProblem.h"
#include "NonlinearSystem.h"

// template <>
registerMooseObject("GardensnakeApp", SolutionNormalizer);

InputParameters
SolutionNormalizer::validParams()
{

  InputParameters params = GeneralUserObject::validParams();

  params.addParam<PostprocessorName>("k",
                                     "This is here to inject a dependency to insure tha this runs "
                                     "after the eigenvalue computation");

  return params;
}

SolutionNormalizer::SolutionNormalizer(const InputParameters & parameters)
  : GeneralUserObject(parameters)
{
  // We don't actually need to store it.... just try to get it to create the dependency.
  getPostprocessorValue("k");
}

void
SolutionNormalizer::execute()
{
  std::cout << "Normalizing Solution!" << std::endl;

  Real norm = _fe_problem.getNonlinearSystem().solution().l2_norm();

  std::cout << "Norm: " << norm << std::endl;

  _fe_problem.getNonlinearSystem().solution() /= norm;

  _fe_problem.getNonlinearSystem().sys().update();
}
