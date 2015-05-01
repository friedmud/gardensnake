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

template<>
InputParameters validParams<KEigenvalue>()
{
  InputParameters params = validParams<GeneralPostprocessor>();

  params.addParam<PostprocessorName>("fission_rate", "The Postprocessor that is computing the integrated fission rate");

  return params;
}

KEigenvalue::KEigenvalue(const std::string & name, InputParameters parameters) :
    GeneralPostprocessor(name, parameters),
    _fission_rate(getPostprocessorValue("fission_rate")),
    _fission_rate_old(getPostprocessorValueOld("fission_rate")),
    _old_eigenvalue(getPostprocessorValueOldByName(name))
{}

Real
KEigenvalue::getValue()
{
  std::cout<<"Computing Eigenvalue!"<<std::endl;

  if (_t_step == 0)
    return 1.0;

  std::cout<<"_fission_rate_old "<<_fission_rate_old<<std::endl;

  return (_fission_rate / _fission_rate_old) * _old_eigenvalue;
}
