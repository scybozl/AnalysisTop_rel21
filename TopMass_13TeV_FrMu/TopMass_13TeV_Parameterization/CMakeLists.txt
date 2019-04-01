# Auto-generated on: 2017-11-24 15:14:15.262411

# Declare the name of this package:
atlas_subdir( TopMass_13TeV_Parameterization None )

# This package depends on other packages:
atlas_depends_on_subdirs( PUBLIC
                          TopDataPreparation
                          AsgTools )

# This package uses ROOT:
find_package( ROOT REQUIRED COMPONENTS Core Gpad Tree Hist RIO MathCore Graf Matrix Physics Minuit )

# Generate a CINT dictionary source file:
atlas_add_root_dictionary( TopMass_13TeV_Parameterization _cintDictSource
                           ROOT_HEADERS Root/LinkDef.h
                           EXTERNAL_PACKAGES ROOT )

# Build a library that other components can link against:
atlas_add_library( TopMass_13TeV_Parameterization Root/*.cxx Root/*.h Root/*.icc
                   TopMass_13TeV_Parameterization/*.h TopMass_13TeV_Parameterization/*.icc TopMass_13TeV_Parameterization/*/*.h
                   TopMass_13TeV_Parameterization/*/*.icc ${_cintDictSource} 
                   PUBLIC_HEADERS TopMass_13TeV_Parameterization
                   LINK_LIBRARIES TopDataPreparation
                                  AsgTools
                                  ${ROOT_LIBRARIES}
                   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} )

# Install data files from the package:
atlas_install_data( DIRECTORY data/* )

atlas_add_executable( RunCombFitPar
		      util/RunCombFitPar.cxx 
		      LINK_LIBRARIES TopMass_13TeV_Parameterization
		      ${ROOT_LIBRARIES}
		      )

atlas_add_executable( RunSepFitPar
                      util/RunSepFitPar.cxx
                      LINK_LIBRARIES TopMass_13TeV_Parameterization
                      ${ROOT_LIBRARIES}
                      )
