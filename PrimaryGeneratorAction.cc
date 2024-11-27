//      PRIMARY GENERATOR ACTION SOURCE FILE

#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()   //:fConfigName("MID_oneD") 
{
   
 // fMessenger_config = new G4GenericMessenger(this, "/INT1/", "Primary generator setup");
 // fMessenger_config->DeclareProperty("SetConfiguration", fConfigName).SetGuidance("Set primary generation configuration").SetParameterName("config", false).SetDefaultValue("MID_oneD");    //This allows you to change the value of fConfigName by issuing a command such as /INT1/SetConfiguration one in your macro file or command line.
 
 fParticleGun = new G4ParticleGun(1); //argument is particle per event

 G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
 G4ParticleDefinition *particle = particleTable->FindParticle("mu+"); 
 fParticleGun->SetParticleDefinition(particle);

}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
 delete fParticleGun;
 //delete fMessenger_config;
}


// void PrimaryGeneratorAction::SetConfiguration(G4String configName)
//{
  //  fConfigName = configName;
//}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
 G4double minMomentum = 0;                                                    // THE ASESOR WANTS 0 TO 10 GEV 
 G4double maxMomentum = 10; 
 G4double randomNumber = G4UniformRand(); //random number between 0 and 1
 G4double momentumParticle = minMomentum + ( maxMomentum - minMomentum )*randomNumber;
 G4double momentum_onMeV = momentumParticle*1000;


    //if(fConfigName == "MID_oneD")
    //{
    //G4ThreeVector position(2.52*cm, 1*m, 2.52*cm); 
    //fParticleGun->SetParticlePosition(position);

    // G4ThreeVector momentum(0.,-1.,0.);  
    // fParticleGun->SetParticleMomentumDirection(momentum);
    //}
    //else if (fConfigName == "two")
    //{
     //G4double min_Direction = -0.50;
     //G4double max_Direction = +0.50;
    //G4double randomNumber = G4UniformRand(); //random number between 0 and 1
     //G4double randomNumber_2 = G4UniformRand(); //random number between 0 and 1
    // G4double Z_dir = min_Direction + ( max_Direction - min_Direction )*randomNumber;
    // G4double X_dir = min_Direction + ( max_Direction - min_Direction )*randomNumber_2;
    //G4ThreeVector position(X_dir*m, 0.21*m, Z_dir*m); 
    

     //G4ThreeVector momentum(0.,-1.,0.);  

      //fParticleGun->SetParticleMomentum(momentumParticle*GeV);
      //fParticleGun->SetParticlePosition(position);
     //fParticleGun->SetParticleMomentumDirection(momentum);
      //fParticleGun->GeneratePrimaryVertex(anEvent);
    // } 
   // else if (fConfigName == "one")
    // {
    // G4ThreeVector position(0, 1*m, 0); 
    // fParticleGun->SetParticlePosition(position);
    // G4ThreeVector momentum(0.,-1.,0.);  
    // fParticleGun->SetParticleMomentumDirection(momentum);
    // } 
    // else if (fConfigName == "solid_angle")
    // {
    G4ThreeVector position(0, 2.8*m, 0); 
    //fParticleGun->SetParticlePosition(position);

    G4double thetaMin = 0. * deg;
    G4double thetaMax = 10.125 * deg;
    G4double phiMin = 0. * deg;
    G4double phiMax = 360. * deg;
    G4double theta = thetaMin + (thetaMax - thetaMin) * G4UniformRand();
    G4double phi = phiMin + (phiMax - phiMin) * G4UniformRand();
    G4double xDir = std::sin(theta) * std::cos(phi);
    G4double yDir = -1* std::cos(theta);
    G4double zDir = std::sin(theta) * std::sin(phi);


    G4ThreeVector momentumDirection(xDir,yDir,zDir);  
    fParticleGun->SetParticleMomentumDirection(momentumDirection);
     fParticleGun->SetParticleMomentum(momentumParticle*GeV);
     fParticleGun->SetParticlePosition(position);
     fParticleGun->GeneratePrimaryVertex(anEvent);
    //} 

G4cout << "" << G4endl;                                                            

 G4cout << "MOMENTUM FOR THIS EVENT: " << momentumParticle << " GeV/c" << G4endl;                                                            


G4AnalysisManager *man = G4AnalysisManager::Instance();  
 //man->FillNtupleDColumn(2,1,momentumParticle);
 //man->FillNtupleDColumn(2,3,momentum_onMeV);

}

