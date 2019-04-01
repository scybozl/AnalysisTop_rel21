
# Declare the name of this package:
atlas_subdir( TopMass_13TeV_PseudoExp None )

# This package depends on other packages:
atlas_depends_on_subdirs( PUBLIC )

# This package uses ROOT:
find_package( ROOT REQUIRED COMPONENTS Core Gpad Tree Hist RIO MathCore Graf Minuit )

# Generate a CINT dictionary source file:
atlas_add_root_dictionary( TopMass_13TeV_PseudoExp _cintDictSource
                           ROOT_HEADERS Root/LinkDef.h
                           EXTERNAL_PACKAGES ROOT )

# Build a library that other components can link against:
atlas_add_library( TopMass_13TeV_PseudoExp Root/*.cxx Root/*.h Root/*.icc
                   TopMass_13TeV_PseudoExp/*.h TopMass_13TeV_PseudoExp/*.icc TopMass_13TeV_PseudoExp/*/*.h
                   TopMass_13TeV_PseudoExp/*/*.icc ${_cintDictSource} 
                   PUBLIC_HEADERS TopMass_13TeV_PseudoExp
                   LINK_LIBRARIES AsgTools
		                  TopMass_13TeV_Parameterization   
                                  ${ROOT_LIBRARIES}
                   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} )

# Install data files from the package:
atlas_install_data( DIRECTORY share/* )

atlas_add_executable( RunPseudoExp
                      util/RunPseudoExp.cxx
                      LINK_LIBRARIES TopMass_13TeV_PseudoExp
                      ${ROOT_LIBRARIES}
                      )

atlas_add_executable( MakeClosureTests
                      util/MakeClosureTests.cxx
                      LINK_LIBRARIES TopMass_13TeV_PseudoExp
                      ${ROOT_LIBRARIES}
                      )

