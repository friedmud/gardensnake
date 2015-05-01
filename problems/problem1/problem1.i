[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 5
  ny = 10
  xmax = 10
[]

[Variables]
  [./group_0]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 1
  [../]
  [./group_1]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 1
  [../]
[]

[Kernels]
  [./absorption_0]
    type = Absorption
    variable = group_0
  [../]
  [./fission_0]
    type = Fission
    variable = group_0
    fluxes = 'group_0 group_1'
  [../]
  [./scatter_0]
    type = Scattering
    variable = group_0
    fluxes = 'group_0 group_1'
  [../]
  [./absorption_1]
    type = Absorption
    variable = group_1
  [../]
  [./scatter_1]
    type = Scattering
    variable = group_1
    fluxes = 'group_0 group_1'
  [../]
  [./source_0]
    type = BodyForce
    variable = group_0
    value = 1
  [../]
  [./source_1]
    type = BodyForce
    variable = group_1
    value = 1
  [../]
[]

[DGKernels]
  [./neutron_diff_0]
    type = FVNeutronDiffusion
    variable = group_0
  [../]
  [./neutron_diff_1]
    type = FVNeutronDiffusion
    variable = group_1
  [../]
[]

[BCs]
  [./right_0]
    type = FVVacuumBC
    variable = group_0
    boundary = right
  [../]
  [./left_0]
    type = FVVacuumBC
    variable = group_0
    boundary = left
  [../]
  [./left_1]
    type = FVVacuumBC
    variable = group_1
    boundary = left
  [../]
  [./right_1]
    type = FVVacuumBC
    variable = group_1
    boundary = right
  [../]
[]

[Materials]
  [./constant_mat]
    type = XSMaterial
    block = 0
    d0 = '1.4300 1.4300 1.4300 1.4300 1.2600 1.0000 1.5500'
    d1 = '0.3700 0.3700 0.3700 0.3700 0.2700 0.3400 0.2700'
    a0 = '0.0079 0.0084 0.0089 0.0088 0.0025 0.0054 0.0010'
    a1 = '0.0605 0.0741 0.0862 0.0852 0.0200 0.1300 0.0286'
    s0_1 = '0.0195 0.0185 0.0178 0.0188 0.0294 0.0009 0.0450'
    nf0 = '0.0034 0.0054 0.0054 0.0062 0.0000 0.0000 0.0000'
    nf1 = '0.0711 0.1000 0.1000 0.1249 0.0000 0.0000 0.0000'
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  l_tol = 1e-9
[]

[Outputs]
  output_initial = true
  exodus = true
  print_linear_residuals = true
  print_perf_log = true
[]

