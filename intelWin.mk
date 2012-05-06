# Version 	: 0.0.1
# Date		: 26.01.2012
# Author 	: Cedric.Bilat@he-arc.ch
#
# Contrainte
#
#	Dans les d�finitions de variables ci-dessous, ne laisser jamais d'espace � la fin!!!
#

#########
#public #
#########

SRC_AUX+=../PRODUCTION/commonExt/include
SRC_AUX+=../PRODUCTION/commonExt/windows

#Option de compilation 
#Elles seront ensuite surcharg�es automatiquement (par exemple en fonction du type de la target)
#Compilation: (minimal conseill� : /MD)
CXXFLAGS:= /MD #pour linker cpptest
#CXXFLAGS:= /w 
CXXFLAGS+= /QxSSSE3
CXXFLAGS+= /fast /O3 /Qparallel /Qpar-threshold100  
CXXFLAGS+= /openmp
CXXFLAGS+= /EHsc

#Option de compilation Static Lib 
ARFLAGS:=

#Option de linkage
#Elles seront ensuite surcharg�es automatiquement (par exemple en fonction du type de la target)
#Version minimale : Ne rien metter laisser vierge!
LDFLAGS_AUX:=

#Injection de variable dans le code (same as #define XXX YYY)
CODE_DEFINE_VARIABLES:=

#Minimum: rien!
#true (ou n'importe quoi) pour activer!
IS_DEFAULT_SYS_LIBRARY_ENABLE:=
IS_ADVANCED_SYS_LIBRARY_ENABLE:=y#pour linker cpptest

#separateur est espace
EXCLUDE_LIBRARY_FILES:=
ADD_LIBRARY_FILES:=

#########
#Private#
#########

COMPILATEUR:=INTEL
OS:=Win
USER=${USERNAME}

ROOT_MAKEFILE_PRIVATE:=../PRODUCTION/MANAGER/makefile/private
-include dataProject.mk
-include $(ROOT_MAKEFILE_PRIVATE)/fileSet.mk
-include $(ROOT_MAKEFILE_PRIVATE)/flags_VisualIntel.mk
-include $(ROOT_MAKEFILE_PRIVATE)/makeFileCPP.mk
 
#########
#  End  #
#########