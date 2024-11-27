//   STEPPING ACTION HEADER

#ifndef STEPPING_HH 
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4OpticalPhoton.hh"
#include "G4RandomTools.hh"
#include "G4Poisson.hh"
#include "G4LogicalVolume.hh"


class SteppingAction : public G4UserSteppingAction
{
    
public: 

 SteppingAction( EventAction *eventaction);
 ~SteppingAction();
 
 virtual void UserSteppingAction(const G4Step*);


private:

 EventAction *fEventAction;
 
 G4double generated_photons_A;
 G4double generated_photons_B;


};

#endif
