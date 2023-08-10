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

#include "KEigenvalue.h"
#include "SubProblem.h"

registerMooseObject("GardensnakeApp", KEigenvalue);

InputParameters
KEigenvalue::validParams()
{
  InputParameters params = GeneralPostprocessor::validParams();

  params.addParam<PostprocessorName>(
      "fission_rate", "The Postprocessor that is computing the integrated fission rate");
  params.addParam<PostprocessorName>(
      "fission_rate_old",
      "The Postprocessor that is computing the integrated fission rate with the old flux");

  return params;
}

KEigenvalue::KEigenvalue(const InputParameters & parameters)
  : GeneralPostprocessor(parameters),
    _fission_rate(getPostprocessorValue("fission_rate")),
    _fission_rate_old(getPostprocessorValue("fission_rate_old")),
    _old_eigenvalue(getPostprocessorValueOldByName(name()))
{
}

Real
KEigenvalue::getValue()
{
  std::cout << "Computing Eigenvalue!" << std::endl;

  if (_t_step == 0)
    return 1.0;

  std::cout << "_fission_rate " << _fission_rate << std::endl;
  std::cout << "_fission_rate_old " << _fission_rate_old << std::endl;
  std::cout << "_old_eigenvalue " << _old_eigenvalue << std::endl;

  std::cout << "new eigen " << (_fission_rate / _fission_rate_old) * _old_eigenvalue << std::endl;

  return (_fission_rate / _fission_rate_old) * _old_eigenvalue;
}
