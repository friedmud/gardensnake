#ifndef GARDENSNAKEAPP_H
#define GARDENSNAKEAPP_H

#include "MooseApp.h"

class GardensnakeApp;

template<>
InputParameters validParams<GardensnakeApp>();

class GardensnakeApp : public MooseApp
{
public:
  GardensnakeApp(const std::string & name, InputParameters parameters);
  virtual ~GardensnakeApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* GARDENSNAKEAPP_H */
