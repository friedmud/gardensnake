#include "GardensnakeApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

// Kernels
#include "Absorption.h"
#include "Scattering.h"
#include "Fission.h"

// BCs
#include "FVVacuumBC.h"

// Materials
#include "XSMaterial.h"

// DGKernels
#include "FVNeutronDiffusion.h"

// Postprocessors
#include "IntegratedFissionRatePostprocessor.h"
#include "KEigenvalue.h"

// UserObjects
#include "SolutionNormalizer.h"

template<>
InputParameters validParams<GardensnakeApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

GardensnakeApp::GardensnakeApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  GardensnakeApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  GardensnakeApp::associateSyntax(_syntax, _action_factory);
}

GardensnakeApp::~GardensnakeApp()
{
}

extern "C" void GardensnakeApp__registerApps() { GardensnakeApp::registerApps(); }
void
GardensnakeApp::registerApps()
{
  registerApp(GardensnakeApp);
}

void
GardensnakeApp::registerObjects(Factory & factory)
{
  registerKernel(Absorption);
  registerKernel(Scattering);
  registerKernel(Fission);

  registerBoundaryCondition(FVVacuumBC);

  registerMaterial(XSMaterial);

  registerDGKernel(FVNeutronDiffusion);

  registerPostprocessor(IntegratedFissionRatePostprocessor);
  registerPostprocessor(KEigenvalue);

  registerUserObject(SolutionNormalizer);
}

void
GardensnakeApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
