//      PRIMARY GENERATOR ACTION SOURCE FILE

#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()  
{

 fParticleGun = new G4ParticleGun(1); //argument is particle per event

 G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
 G4ParticleDefinition *particle = particleTable->FindParticle("mu+"); 
 fParticleGun->SetParticleDefinition(particle);

}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
 delete fParticleGun;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
 G4double minMomentum = 0;                                                  
 G4double maxMomentum = 10; 
 G4double randomNumber = G4UniformRand(); //random number between 0 and 1
 G4double momentumParticle = minMomentum + ( maxMomentum - minMomentum )*randomNumber;
 G4double momentum_onMeV = momentumParticle*1000;


   
    G4ThreeVector position(0, 2.8*m, 0); 
   

    G4double thetaMin = 0. * deg;
    G4double thetaMax = 10.125 * deg;
    G4double phiMin = 0. * deg;
    G4double phiMax = 360. * deg;
    G4double theta = thetaMin + (thetaMax - thetaMin) * G4UniformRand();
    G4double phi = phiMin + (phiMax - phiMin) * G4UniformRand();
    G4double xDir = std::sin(theta) * std::cos(phi);
    G4double yDir = -1* std::cos(theta);
    G4double zDir = std::sin(theta) * std::sin(phi);

    G4double angle = theta*(180.0/(CLHEP::pi));
    //G4double angle = (std::acos(-1.0*yDir))*(180.0/2.0*CLHEP::pi);


    G4ThreeVector momentumDirection(xDir,yDir,zDir);  
    fParticleGun->SetParticleMomentumDirection(momentumDirection);
     fParticleGun->SetParticleMomentum(momentumParticle*GeV);
     fParticleGun->SetParticlePosition(position);
     fParticleGun->GeneratePrimaryVertex(anEvent);
    

G4cout << "" << G4endl;                                                            
G4cout << "------------------------------------------------------------" << G4endl;
 G4cout << "MOMENTUM FOR THIS EVENT: " << momentumParticle << " GeV/c \n" << G4endl;                                                            
G4cout << "PARTICLE ANGLE : " <<angle << "° \n"<<  G4endl;   

G4AnalysisManager *man = G4AnalysisManager::Instance(); 
 man->FillNtupleDColumn(1, 160, momentum_onMeV); 
 man->FillNtupleDColumn(1, 161, momentumParticle);
 man->FillNtupleDColumn(1,162,angle);
 

}

