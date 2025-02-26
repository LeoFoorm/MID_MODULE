//		PHYSICS LIST SOURCE

#include "Physics.hh"

#include "G4EmStandardPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"

#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4DecayPhysics.hh" 
#include "G4OpticalParameters.hh"



PhysicsList::PhysicsList()
{

	//RegisterPhysics(new FTFP_BERT_HP());

	/*RegisterPhysics (new G4EmStandardPhysics());

	RegisterPhysics( new G4EmExtraPhysics() );

	RegisterPhysics (new G4DecayPhysics());

	RegisterPhysics( new G4HadronElasticPhysicsHP() );

	//RegisterPhysics( new HadronPhysicsFTFP_BERT_HP() );

	RegisterPhysics( new G4StoppingPhysics() );

	RegisterPhysics( new G4IonPhysics() );



	// Register optical physics and configure scintillation properties				In order to set the G4Scintillation
    G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
	RegisterPhysics(opticalPhysics);

	

	//RegisterPhysics (new G4OpticalPhysics()); 
	
	//RegisterPhysics (new G4RadioactiveDecayPhysics());

	
	RegisterPhysics(new G4HadronPhysicsQGSP_BERT()); //<------

*/

/*
// Register the FTFP_BERT_HP physics list
    RegisterPhysics(new FTFP_BERT_HP());

    // Register optical physics for scintillation and photon transport
    G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
    opticalPhysics->Configure(G4OpticalPhysics::Scintillation, true);  // Enable scintillation
    //opticalPhysics->Configure(G4OpticalPhysics::Cerenkov, false);      // Disable Cerenkov (optional)
    opticalPhysics->Configure(G4OpticalPhysics::OpAbsorption, true);   // Enable absorption
    opticalPhysics->Configure(G4OpticalPhysics::OpBoundaryProcess, true); // Enable boundary processes
    RegisterPhysics(opticalPhysics);
*/

  // Register standard electromagnetic physics
    RegisterPhysics(new G4EmStandardPhysics());

    // Register hadronic physics (FTFP_BERT_HP components)
    RegisterPhysics(new G4HadronPhysicsFTFP_BERT_HP());
    RegisterPhysics(new G4HadronElasticPhysicsHP());
    RegisterPhysics(new G4StoppingPhysics());
    RegisterPhysics(new G4IonPhysics());

    // Register decay physics
    RegisterPhysics(new G4DecayPhysics());

    // Register optical physics for scintillation
    G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
    RegisterPhysics(opticalPhysics);

    // Configure optical processes using G4OpticalParameters
    G4OpticalParameters* opticalParams = G4OpticalParameters::Instance();
     opticalParams->SetProcessActivation("Scintillation", true);    // Enable scintillation
    opticalParams->SetProcessActivation("OpAbsorption", true);    // Enable absorption
    opticalParams->SetProcessActivation("OpBoundary", true);      // Enable boundary processes
    //opticalParams->SetProcessActivation("Cerenkov", false);       // Disable Cerenkov (optional)
}

PhysicsList::~PhysicsList()
{}
