//		PHYSICS LIST HEADER

#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"

#include "G4OpticalPhysics.hh"

//#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
//#include "G4DecayPhysics.hh"
 
#include "G4Scintillation.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"  

#include "G4EmExtraPhysics.hh"
//#include "G4HadronElasticPhysicsHP.hh"

//#include "G4StoppingPhysics.hh"
//#include "G4IonPhysics.hh"

//#include "FTFP_BERT_HP.hh"

class PhysicsList : public G4VModularPhysicsList
{
	public:
		PhysicsList();
		~PhysicsList();
};

#endif


