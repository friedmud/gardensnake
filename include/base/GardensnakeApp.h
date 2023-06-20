#pragma once

#ifndef GARDENSNAKEAPP_H
#define GARDENSNAKEAPP_H

#include "MooseApp.h"

class GardensnakeApp;

class GardensnakeApp : public MooseApp
{
public:
  static InputParameters validParams();

  GardensnakeApp(InputParameters parameters);

  virtual ~GardensnakeApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* GARDENSNAKEAPP_H */
