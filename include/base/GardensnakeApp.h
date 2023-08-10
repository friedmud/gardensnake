//* This file is part of GardenSnake, an open-source
//* application for the simulation of plasmas
//* https://github.com/friedmud/gardensnake
//*
//* GardenSnake is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "MooseApp.h"

class GardensnakeApp : public MooseApp
{
public:
  static InputParameters validParams();

  GardensnakeApp(InputParameters parameters);

  virtual ~GardensnakeApp();

  static void registerApps();
  static void registerAll(Factory & f, ActionFactory & af, Syntax & s);

};