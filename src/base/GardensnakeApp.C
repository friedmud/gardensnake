#include "GardensnakeApp.h"
#include "Moose.h"
#include "AppFactory.h"

// Kernels
#include "Absorption.h"
#include "Scattering.h"
#include "Fission.h"

// BCs
#include "FVVacuumBC.h"
#include "PenaltyBC.h"

// Materials
#include "XSMaterial.h"

// AuxKernels
#include "ZoneAux.h"

// DGKernels
#include "FVNeutronDiffusion.h"

// Postprocessors
#include "IntegratedFissionRatePostprocessor.h"
#include "KEigenvalue.h"
#include "PostprocessorRelativeChange.h"
#include "FissionSourceRMSFractionalChange.h"
#include "TotalFluxRMSFractionalChange.h"
#include "PeakFissionSource.h"

// UserObjects
#include "SolutionNormalizer.h"

template<>
InputParameters validParams<GardensnakeApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

GardensnakeApp::GardensnakeApp(InputParameters parameters) :
    MooseApp(parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
  GardensnakeApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
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
  registerBoundaryCondition(PenaltyBC);

  registerMaterial(XSMaterial);

  registerAux(ZoneAux);

  registerDGKernel(FVNeutronDiffusion);

  registerPostprocessor(IntegratedFissionRatePostprocessor);
  registerPostprocessor(KEigenvalue);
  registerPostprocessor(PostprocessorRelativeChange);
  registerPostprocessor(FissionSourceRMSFractionalChange);
  registerPostprocessor(TotalFluxRMSFractionalChange);
  registerPostprocessor(PeakFissionSource);

  registerUserObject(SolutionNormalizer);
}

void
GardensnakeApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
