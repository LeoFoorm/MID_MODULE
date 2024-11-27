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
G4double generated_photons_A = 0.0;
G4double generated_photons_B = 0.0;

const DetectorConstruction *detectorconstruction = static_cast < const DetectorConstruction* > (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
 
const std::vector<G4LogicalVolume*>& scoringVolumesA = detectorconstruction->GetScoringVolumesA();
const std::vector<G4LogicalVolume*>& scoringVolumesB = detectorconstruction->GetScoringVolumesB();
   
 G4LogicalVolume *touchedVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
 G4double stepLength = step->GetStepLength();
 G4ParticleDefinition* particle = step->GetTrack()->GetDefinition();

 


if(particle->GetParticleName()== "mu+"){
   G4double dEdxStep_A = 0.0; 
   G4double dEdxStep_B = 0.0;
   //for (size_t a = 0; a < scoringVolumesA.size(); ++a)
   //{
       //if (touchedVolume == scoringVolumesA[a])
       //{ 
         //auto it = std::find(scoringVolumesA.begin(),scoringVolumesA.end(), touchedVolume);
         //if(it != scoringVolumesA.end())
         if (std::find(scoringVolumesA.begin(), scoringVolumesA.end(), touchedVolume) != scoringVolumesA.end())
        {
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
                                              std::find(scoringVolumesA.begin(), scoringVolumesA.end(), touchedVolume));
            
            fEventAction->AddPhotonG_UsingEdep_A(a, generated_photons_A);
            fEventAction->AddEdepA(a, edep_A);
            fEventAction->AccumulatedEdx_A(a, dEdxStep_A);     
         }}
       //}
         
   //}  
    // Energy deposition for the second bar (bottom bar)
   //for (size_t b = 0; b < scoringVolumesB.size(); ++b)
   //{
       //if (touchedVolume == scoringVolumesB[b])
       //{
         if (std::find(scoringVolumesB.begin(), scoringVolumesB.end(), touchedVolume) != scoringVolumesB.end())
        {
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
                                              std::find(scoringVolumesB.begin(), scoringVolumesB.end(), touchedVolume));
            
            fEventAction->AddPhotonG_UsingEdep_B(b, generated_photons_B); 
            fEventAction->AddEdepB(b, edep_B);
            fEventAction->AccumulatedEdx_B(b, dEdxStep_B);  
         }}
    
}

}


