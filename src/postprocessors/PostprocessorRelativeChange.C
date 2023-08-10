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

#include "PostprocessorRelativeChange.h"
#include "SubProblem.h"

registerMooseObject("GardensnakeApp", PostprocessorRelativeChange);

InputParameters
PostprocessorRelativeChange::validParams()
{
  InputParameters params = GeneralPostprocessor::validParams();

  params.addParam<PostprocessorName>("pp", "The Postprocessor to compute the relative change of.");

  return params;
}

PostprocessorRelativeChange::PostprocessorRelativeChange(const InputParameters & parameters)
  : GeneralPostprocessor(parameters),
    _pp(getPostprocessorValue("pp")),
    _pp_old(getPostprocessorValueOld("pp"))
{
}

Real
PostprocessorRelativeChange::getValue()
{
  return std::abs((_pp - _pp_old) / _pp);
}
