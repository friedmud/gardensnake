#include "GardensnakeApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

// BCs
#include "FVVacuumBC.h"

// DGKernels
#include "FVNeutronDiffusion.h"


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
  registerBoundaryCondition(FVVacuumBC);

  registerDGKernel(FVNeutronDiffusion);
}

void
GardensnakeApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
