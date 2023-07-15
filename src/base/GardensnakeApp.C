//* This file is part of GardenSnake, an open-source
//* application for the simulation of plasmas
//* https://github.com/friedmud/gardensnake
//*
//* GardenSnake is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "GardensnakeApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

// Kernels
// #include "Absorption.h"
// #include "Scattering.h"
// #include "Fission.h"

// BCs
// #include "FVVacuumBC.h"
// #include "PenaltyBC.h"

// Materials
// #include "XSMaterial.h"

// AuxKernels
// #include "ZoneAux.h"

// DGKernels
// #include "FVNeutronDiffusion.h"

// Postprocessors
// #include "FissionSourceRMSFractionalChange.h"
// #include "IntegratedFissionRatePostprocessor.h"
// #include "KEigenvalue.h"
// #include "PeakFissionSource.h"
// #include "PostprocessorRelativeChange.h"
// #include "TotalFluxRMSFractionalChange.h"


// UserObjects
// #include "SolutionNormalizer.h"

InputParameters
GardensnakeApp::validParams()
{
  InputParameters params = MooseApp::validParams();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

// When using the new Registry system, this line is required so that
// dependent apps know about the ZapdosApp label.
registerKnownLabel("GardensnakeApp");

GardensnakeApp::GardensnakeApp(InputParameters parameters) : MooseApp(parameters)
{
 srand(processor_id());
 GardensnakeApp::registerAll(_factory, _action_factory, _syntax);
}

GardensnakeApp::~GardensnakeApp() {}

void
GardensnakeApp::registerApps()
{
  registerApp(GardensnakeApp);
}

void
GardensnakeApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
//   ModulesApp::registerAllObjects<GardensnakeApp>(f, af, s);
  ModulesApp::registerAll(f, af, s);
  Registry::registerObjectsTo(f, {"GardensnakeApp"});
  Registry::registerActionsTo(af, {"GardensnakeApp"});

//   registerKernel(Absorption);
//   registerKernel(Scattering);
//   registerKernel(Fission);

//   registerBoundaryCondition(FVVacuumBC);
//   registerBoundaryCondition(PenaltyBC);

//   registerMaterial(XSMaterial);

//   registerAux(ZoneAux);

//   registerDGKernel(FVNeutronDiffusion);

//   registerPostprocessor(IntegratedFissionRatePostprocessor);
//   registerPostprocessor(KEigenvalue);
//   registerPostprocessor(PostprocessorRelativeChange);
//   registerPostprocessor(FissionSourceRMSFractionalChange);
//   registerPostprocessor(TotalFluxRMSFractionalChange);
//   registerPostprocessor(PeakFissionSource);

//   registerUserObject(SolutionNormalizer);



  /* register objects from dependent applications */
//   SquirrelApp::registerAll(f, af, s);
//   CraneApp::registerAll(f, af, s);

  /* register custom execute flags, action syntax, etc. here */
//   s.registerActionSyntax("AddPeriodicControllers", "PeriodicControllers/*");
//   s.registerActionSyntax("AddDriftDiffusionAction", "DriftDiffusionAction/*");
//   s.registerActionSyntax("AddPeriodicRelativeNodalDifference", "PeriodicRelativeNodalDifference/*");
}




// void
// GardensnakeApp::registerObjects(Factory & factory)
// {

// }


// void
// GardensnakeApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
// {
// //   HeatConductionApp::registerAll(f, af, syntax);
// //   NavierStokesApp::registerAll(f, af, syntax);
// //   MiscApp::registerAll(f, af, syntax);
//   Registry::registerObjectsTo(f, {"GardensnakeApp"});
//   Registry::registerActionsTo(af, {"GardensnakeApp"});

//   registerKernel(Absorption);
//   registerKernel(Scattering);
//   registerKernel(Fission);

//   registerBoundaryCondition(FVVacuumBC);
//   registerBoundaryCondition(PenaltyBC);

//   registerMaterial(XSMaterial);

//   registerAux(ZoneAux);

//   registerDGKernel(FVNeutronDiffusion);

//   registerPostprocessor(IntegratedFissionRatePostprocessor);
//   registerPostprocessor(KEigenvalue);
//   registerPostprocessor(PostprocessorRelativeChange);
//   registerPostprocessor(FissionSourceRMSFractionalChange);
//   registerPostprocessor(TotalFluxRMSFractionalChange);
//   registerPostprocessor(PeakFissionSource);

//   registerUserObject(SolutionNormalizer);

//   /* register custom execute flags, action syntax, etc. here */
// }

// extern "C" void
// GardensnakeApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
// {
//   GardensnakeApp::registerAll(f, af, s);
// }

// void
// GardensnakeApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
// {
// }

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
GardensnakeApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  GardensnakeApp::registerAll(f, af, s);
}

extern "C" void
GardensnakeApp__registerApps()
{
  GardensnakeApp::registerApps();
}


// extern "C" void
// GardensnakeApp__registerApps()
// {
//   GardensnakeApp::registerApps();
// }
