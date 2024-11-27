//		PHYSICS LIST SOURCE

#include "Physics.hh"


PhysicsList::PhysicsList()
{

	RegisterPhysics (new G4EmStandardPhysics());


	// Register optical physics and configure scintillation properties				In order to set the G4Scintillation
    G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
	RegisterPhysics(opticalPhysics);

	//G4Scintillation *scintillation_process = opticalPhysics->GetScintillationProcess();
	//if(scintillation_process)
	//{
    //scintillation_process->SetScintillationYieldFactor(1.0); 								// Scales the light yield
    //scintillation_process->SetScintillationByParticleType(true); 							// Different yields for different particles
	//}

	//RegisterPhysics (new G4OpticalPhysics()); 
	RegisterPhysics (new G4DecayPhysics());
	RegisterPhysics (new G4RadioactiveDecayPhysics());

}

PhysicsList::~PhysicsList()
{}
