#-----------------------------------
#BASIC CONFIGURATION
 
cmake_minimum_required(VERSION 3.22.0)

project(MID_MODULE_ME)

#-----------------------------------
#FIND AND CONFIGURE GEANT4

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#-------------------------------------
#CONFIGURE THE PROJECT TO USE GEANT4

#To automatically configure CMake to use additional CMake modules supplied
#by Geant4. Here, sets to the path to this module when Geant4 is located by 
#by find_package. 

include(${Geant4_USE_FILE})

#include_directories(${PROJECT_SOURCE_DIR}/include)

#the line above adds the PROJECT header directory to the compiler's header search path.
#The things after include are calling CMake variables. The above variable points to the 
#top level directory of the project and is set by the earlier call to the "project" command.

#------------------------------------
#LIST THE SOURCES TO BUILD THE APPLICATION

#In order to compile every src and header file. 

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

#################################################
file(GLOB MACRO_FILES
 "*.mac"
)
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})
################################################

#NOTA PARA AUTOR: NO OLVIDES PONER LOS ARCHIVOS EN DIRECTORIOS src y include
#como file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
#y tambien file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#--------------------------------------
#DEFINE THE EXECUTABLE

#The creation of the executable; we will tell CMake the name of the executable (a file with .cc).
#target link command links the executable with the Geant4 libraries. 

add_executable(MID_MODULE_ME MID_MODULE_ME.cc ${sources} ${headers})  
target_link_libraries(MID_MODULE_ME ${Geant4_LIBRARIES})

#--------------------------------------
#CUSTOM TARGETS
#For internal Geant4 use - but has no effect if you build this

#add_custom_target(MID_MODULE_ME DEPENDS MID_MODULE_ME)
