//  STEPPING ACTION SOURCE

#include "SteppingAction.hh"

SteppingAction::SteppingAction( EventAction *eventaction)
{
 fEventAction = eventaction;
}


SteppingAction::~SteppingAction()
{}


void SteppingAction::UserSteppingAction(const G4Step *step)
{

const DetectorConstruction *detectorconstruction = static_cast < const DetectorConstruction* > (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
 
const std::vector<G4LogicalVolume*>& scoringVolumesA = detectorconstruction->GetScoringVolumesA();
const std::vector<G4LogicalVolume*>& scoringVolumesB = detectorconstruction->GetScoringVolumesB();
   

G4TouchableHandle touchedbar = step->GetPreStepPoint()->GetTouchableHandle(); //
 G4LogicalVolume* barvolume = touchedbar->GetVolume()->GetLogicalVolume();


 G4double stepLength = step->GetStepLength();
 G4ParticleDefinition* particle = step->GetTrack()->GetDefinition();
 
 
 G4Track* track = step->GetTrack();

 
if(particle->GetParticleName()== "mu+"){
   G4double dEdxStep_A = 0.0; 
   G4double dEdxStep_B = 0.0;
   G4double generated_photons_A = 0.0;
   G4double generated_photons_B = 0.0;
   
         if (std::find(scoringVolumesA.begin(), scoringVolumesA.end(), barvolume) != scoringVolumesA.end())
        {

                G4int copyNumA = touchedbar->GetCopyNumber(); // Número de copia de la barra
                fEventAction->AddTraversedBar_A(copyNumA);
    
         G4double edep_A = step->GetTotalEnergyDeposit();
         if (edep_A > 0.&& stepLength > 0.)
         {
            G4double dEdxStep_A = edep_A / stepLength ;

            G4Material *plastic_scin = step->GetPreStepPoint()->GetMaterial(); 
            G4MaterialPropertiesTable *Yield = plastic_scin->GetMaterialPropertiesTable(); 
            G4double Scintillation_Yield = Yield->GetConstProperty("SCINTILLATIONYIELD");

            generated_photons_A = edep_A * Scintillation_Yield; 
            generated_photons_A = G4Poisson(generated_photons_A); 

            size_t a = std::distance(scoringVolumesA.begin(),
                                              std::find(scoringVolumesA.begin(), scoringVolumesA.end(), barvolume));
            
            fEventAction->AddPhotonG_UsingEdep_A(a, generated_photons_A);
            fEventAction->AddEdepA(a, edep_A);
            fEventAction->AccumulatedEdx_A(a, dEdxStep_A);    
         }}
      

         if (std::find(scoringVolumesB.begin(), scoringVolumesB.end(), barvolume) != scoringVolumesB.end())
        {

           
                G4int copyNumB = touchedbar->GetCopyNumber(); // Número de copia de la barra
                fEventAction->AddTraversedBar_B(copyNumB);
            

         G4double edep_B = step->GetTotalEnergyDeposit();
         if (edep_B > 0.&& stepLength > 0.)
         {
            G4double dEdxStep_B = edep_B  / stepLength ;

            G4Material *plastic_scin = step->GetPreStepPoint()->GetMaterial(); 
            G4MaterialPropertiesTable *Yield = plastic_scin->GetMaterialPropertiesTable(); 
            G4double Scintillation_Yield = Yield->GetConstProperty("SCINTILLATIONYIELD");

            generated_photons_B = edep_B * Scintillation_Yield; 
            generated_photons_B = G4Poisson(generated_photons_B); 
            
            size_t b = std::distance(scoringVolumesB.begin(),
                                              std::find(scoringVolumesB.begin(), scoringVolumesB.end(), barvolume));
            
            fEventAction->AddPhotonG_UsingEdep_B(b, generated_photons_B); 
            fEventAction->AddEdepB(b, edep_B);
            fEventAction->AccumulatedEdx_B(b, dEdxStep_B);  
        
         }
         }


       
        // Obtener el número de copia del volumen
        //G4int copynum = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
              //fEventAction->WorkingBars(copynum);  
}

}


//Para agregar información del numero de copia atravesada tuve que modificar  lo que esta con "//" y todo lo que tenia a "touchedVolume". 
//En eventAction todo lo respectivo a estos cambios hechos de prisa los señalaré con //X