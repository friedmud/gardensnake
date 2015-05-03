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

#ifndef TOTALFLUXRMSFRACTIONALCHANGE_H
#define TOTALFLUXRMSFRACTIONALCHANGE_H

#include "ElementAverageValue.h"

//Forward Declarations
class TotalFluxRMSFractionalChange;

template<>
InputParameters validParams<TotalFluxRMSFractionalChange>();

class TotalFluxRMSFractionalChange : public ElementAverageValue
{
public:
  TotalFluxRMSFractionalChange(const std::string & name, InputParameters parameters);
  virtual Real getValue();

protected:
  virtual Real computeQpIntegral();

  std::vector<VariableValue *> _fluxes;
  std::vector<VariableValue *> _fluxes_old;
};

#endif
