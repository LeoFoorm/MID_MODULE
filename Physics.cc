//		PHYSICS LIST SOURCE

#include "Physics.hh"


PhysicsList::PhysicsList()
{

	//RegisterPhysics(new FTFP_BERT_HP()); ---? 

	RegisterPhysics (new G4EmStandardPhysics());

	RegisterPhysics( new G4EmExtraPhysics() );

	RegisterPhysics (new G4DecayPhysics());

	RegisterPhysics( new G4HadronElasticPhysicsHP() );

	//RegisterPhysics( new HadronPhysicsFTFP_BERT_HP() );

	RegisterPhysics( new G4StoppingPhysics() );

	RegisterPhysics( new G4IonPhysics() );


    G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
	RegisterPhysics(opticalPhysics);

	
	//RegisterPhysics (new G4RadioactiveDecayPhysics());

	
	RegisterPhysics(new G4HadronPhysicsQGSP_BERT()); //<------



	

}

PhysicsList::~PhysicsList()
{}
