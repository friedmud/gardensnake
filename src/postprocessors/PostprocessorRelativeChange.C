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

template<>
InputParameters validParams<PostprocessorRelativeChange>()
{
  InputParameters params = validParams<GeneralPostprocessor>();

  params.addParam<PostprocessorName>("pp", "The Postprocessor to compute the relative change of.");

  return params;
}

PostprocessorRelativeChange::PostprocessorRelativeChange(const std::string & name, InputParameters parameters) :
    GeneralPostprocessor(name, parameters),
    _pp(getPostprocessorValue("pp")),
    _pp_old(getPostprocessorValueOld("pp"))
{}

Real
PostprocessorRelativeChange::getValue()
{
  return std::abs((_pp - _pp_old)/_pp);
}
