#   File:       GetPMFeatures.make
#   Target:     GetPMFeatures
#   Created:    Sunday, August 26, 2018 12:47:59 PM


MAKEFILE        = GetPMFeatures.make
•MondoBuild•    = {MAKEFILE}  # Make blank to avoid rebuilds when makefile is modified

ObjDir          = :
Includes        = 

Sym-PPC         = -sym off

PPCCOptions     = {Includes} {Sym-PPC} 


### Source Files ###

SrcFiles        =  ∂
				  GetPMFeatures.c


### Object Files ###

ObjFiles-PPC    =  ∂
				  "{ObjDir}GetPMFeatures.c.x"


### Libraries ###

LibFiles-PPC    =  ∂
				  "{PPCLibraries}PPCSIOW.o" ∂
				  "{SharedLibraries}InterfaceLib" ∂
				  "{SharedLibraries}StdCLib" ∂
				  "{SharedLibraries}MathLib" ∂
				  "{PPCLibraries}StdCRuntime.o" ∂
				  "{PPCLibraries}PPCCRuntime.o" ∂
				  "{PPCLibraries}PPCToolLibs.o"


### Default Rules ###

.c.x  ƒ  .c  {•MondoBuild•}
	{PPCC} {depDir}{default}.c -o {targDir}{default}.c.x {PPCCOptions}


### Build Rules ###

GetPMFeatures  ƒƒ  {ObjFiles-PPC} {LibFiles-PPC} {•MondoBuild•}
	PPCLink ∂
		-o {Targ} ∂
		{ObjFiles-PPC} ∂
		{LibFiles-PPC} ∂
		{Sym-PPC} ∂
		-mf -d ∂
		-t 'APPL' ∂
		-c 'siow'


GetPMFeatures  ƒƒ  "{RIncludes}"SIOW.r {•MondoBuild•}
	Rez "{RIncludes}"SIOW.r -o {Targ} -append


### Required Dependencies ###

"{ObjDir}GetPMFeatures.c.x"  ƒ  GetPMFeatures.c


### Optional Dependencies ###
### Build this target to generate "include file" dependencies. ###

Dependencies  ƒ  $OutOfDate
	MakeDepend ∂
		-append {MAKEFILE} ∂
		-ignore "{CIncludes}" ∂
		-objdir "{ObjDir}" ∂
		-objext .x ∂
		{Includes} ∂
		{SrcFiles}


