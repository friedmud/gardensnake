[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 300
  ny = 10
  xmax = 300
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
    initial_condition = 1 # 0.0912871
  [../]
[]

[AuxVariables]
  [./zone]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Kernels]
  active = 'scatter_0 scatter_1 fission_0 absorption_0 absorption_1'
  [./absorption_0]
    type = Absorption
    variable = group_0
  [../]
  [./fission_0]
    type = Fission
    variable = group_0
    fluxes = 'group_0 group_1'
    k = k
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

[AuxKernels]
  [./zone]
    type = ZoneAux
    variable = zone
    zones = '4 3 2 3 4'
    zone_edges = '0 25 40 260 275 300'
    execute_on = 'initial'
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
  [./xs_mat]
    type = XSMaterial
    block = 0
    a1 = '0.0605 0.0741 0.0862 0.0852 0.0200 0.1300 0.0286'
    a0 = '0.0079 0.0084 0.0089 0.0088 0.0025 0.0054 0.0010'
    nf1 = '0.0711 0.1000 0.1000 0.1249 0.0000 0.0000 0.0000'
    nf0 = '0.0034 0.0054 0.0054 0.0062 0.0000 0.0000 0.0000'
    s0_1 = '0.0195 0.0185 0.0178 0.0188 0.0294 0.0009 0.0450'
    d0 = '1.4300 1.4300 1.4300 1.4300 1.2600 1.0000 1.5500'
    d1 = '0.3700 0.3700 0.3700 0.3700 0.2700 0.3400 0.2700'
    zone = zone
    zones = '4 3 2 3 4'
    zone_edges = '0 25 40 260 275 300'
  [../]
[]

[Postprocessors]
  [./fission_rate]
    type = IntegratedFissionRatePostprocessor
    execute_on = 'TIMESTEP_END initial'
    new = true
    fluxes = 'group_0 group_1'
    zone =  zone
    active_zones = '0 1 2 3'
  [../]
  [./k]
    type = KEigenvalue
    execute_on = 'TIMESTEP_END initial'
    fission_rate = fission_rate
    fission_rate_old = fission_rate_old
  [../]
  [./fission_rate_old]
    type = IntegratedFissionRatePostprocessor
    new = false
    fluxes = 'group_0 group_1'
    zone =  zone
    active_zones = '0 1 2 3'
  [../]
  [./fission_change]
    type = FissionSourceRMSFractionalChange
    variable = group_0 # have to pick one
    fluxes = 'group_0 group_1'
    zone =  zone
    active_zones = '0 1 2 3'
  [../]
  [./flux_change]
    type = TotalFluxRMSFractionalChange
    variable = group_0 # Have to pick one
    fluxes = 'group_0 group_1'
  [../]
  [./peak]
    type = PeakFissionSource
    active_zones = '0 1 2 3'
    zone = zone
    report = NORMALIZED_VALUE
    fluxes = 'group_0 group_1'
    center = 150
  [../]
  [./peak_position]
    type = PeakFissionSource
    active_zones = '0 1 2 3'
    zone = zone
    report = position
    fluxes = 'group_0 group_1'
    center = 150
  [../]
[]

[UserObjects]
  [./normalizer]
    type = SolutionNormalizer
    execute_on = 'timestep_end initial'
    k = k
  [../]
  [./terminator]
    type = Terminator
    expression = '(fission_change < 1e-7) & (flux_change < 1e-5)'
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 1000
  solve_type = NEWTON
  petsc_options_iname = -pc_type
  petsc_options_value = lu
  l_tol = 1e-9
  line_search = none
  nl_abs_tol = 1e-14
[]

[Outputs]
  exodus = true
[]
