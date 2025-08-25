//  STEPPING ACTION SOURCE

#include "SteppingAction.hh"
#include <vector>

using namespace std;

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
G4LogicalVolume* scoringVolume_Absorber = detectorconstruction->GetScoringVolumeAbsorber();
   
//const vector<G4LogicalVolume*>& Logic_Fibers_A = detectorconstruction->GetFibersVolumesA();
//const vector<G4LogicalVolume*>& Logic_Fibers_B = detectorconstruction->GetFibersVolumesB();

G4TouchableHandle touchedbar = step->GetPreStepPoint()->GetTouchableHandle(); 
 G4LogicalVolume* barvolume = touchedbar->GetVolume()->GetLogicalVolume();


 G4double stepLength = step->GetStepLength();
 G4ParticleDefinition* particle = step->GetTrack()->GetDefinition();
 
 
 G4Track* track = step->GetTrack();


G4StepPoint *PreStep = step->GetPreStepPoint();
  
 
if(particle->GetParticleName()== "mu+" ||  particle->GetParticleName() == "pi+" ){

   G4double dEdxStep_A ; 
   G4double dEdxStep_B ;
   G4double generated_photons_A;
   G4double generated_photons_B ;


   if(barvolume == scoringVolume_Absorber){
      
	   G4double edep_abs ;
	   G4double dEdx_abs ;

	   edep_abs = step-> GetTotalEnergyDeposit();
	   if (edep_abs > 0. && stepLength > 0.){
		fEventAction->AddEdepAbs(edep_abs);
	   }
      
   }
   
         if (std::find(scoringVolumesA.begin(), scoringVolumesA.end(), barvolume) != scoringVolumesA.end())
        {

         G4int copyNumA = touchedbar->GetCopyNumber(); // Número de copia de la barra
         fEventAction->AddTraversedBar_A(copyNumA);
    

        G4ThreeVector position_A = step->GetPostStepPoint()->GetPosition();
       
        G4double A_pos_x = position_A.x()/(cm);
        G4double A_pos_y = position_A.y()/(cm);
        G4double A_pos_z = position_A.z()/(cm);
        
     
        fEventAction->Add_Positions_Layer_A_x(A_pos_x);
        fEventAction->Add_Positions_Layer_A_y(A_pos_y);
        fEventAction->Add_Positions_Layer_A_z(A_pos_z);
      

         G4double edep_A = step->GetTotalEnergyDeposit();

          G4double stepLength_New = step->GetStepLength(); //will be useful?
         
         if (edep_A > 0.&& stepLength > 0.)
         {

            G4String p_name = step->GetTrack()->GetDefinition()->GetParticleName();
            G4int trackID = step->GetTrack()->GetTrackID();       //<--- NEW
            fEventAction->Particle_Name_Pierced_Layer_A(p_name, trackID);

            dEdxStep_A = edep_A / stepLength ;

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
            
            G4ThreeVector position_B = step->GetPostStepPoint()->GetPosition();
       
            G4double B_pos_x = position_B.x()/(cm);
            G4double B_pos_y = position_B.y()/(cm);
            G4double B_pos_z = position_B.z()/(cm);
        
     
            fEventAction->Add_Positions_Layer_B_x(B_pos_x);
            fEventAction->Add_Positions_Layer_B_y(B_pos_y);
            fEventAction->Add_Positions_Layer_B_z(B_pos_z);


            G4double edep_B = step->GetTotalEnergyDeposit();

         if (edep_B > 0.&& stepLength > 0.)
         {

            G4String p_name = step->GetTrack()->GetDefinition()->GetParticleName();
            G4int trackID = step->GetTrack()->GetTrackID();         //<--- NEW
            fEventAction->Particle_Name_Pierced_Layer_B(p_name, trackID);   //<--- NEW

             dEdxStep_B = edep_B  / stepLength ;

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
} 

// ---------------------------------------------------------------------------------




//----------------------- DATA WITH SEOCNDARIES -------------------------------------------------------------------------------------------
 if (particle->GetParticleName()!= "opticalphoton" && particle->GetParticleName()!= "mu+" && particle->GetParticleName()!= "pi+" ){

   G4double edep_A_s  ;
   G4double edep_B_s;
   G4int generated_photons_A_s ;
   G4int generated_photons_B_s ;

 if (std::find(scoringVolumesA.begin(), scoringVolumesA.end(), barvolume) != scoringVolumesA.end())
        {

         G4int copyNumA_s = touchedbar->GetCopyNumber(); 
         fEventAction->AddTraversedBar_A_s(copyNumA_s);
                       

         G4ThreeVector position_A_s = step->GetPostStepPoint()->GetPosition();
       
         G4double A_pos_x_s = position_A_s.x()/(cm);
         G4double A_pos_y_s = position_A_s.y()/(cm);
         G4double A_pos_z_s = position_A_s.z()/(cm);
         
      
         fEventAction->Add_Positions_Layer_A_x_s(A_pos_x_s);
         fEventAction->Add_Positions_Layer_A_y_s(A_pos_y_s);
         fEventAction->Add_Positions_Layer_A_z_s(A_pos_z_s);
       
         
          edep_A_s = step->GetTotalEnergyDeposit();

         if (edep_A_s > 0.&& stepLength > 0.)
         {

            G4String p_name = step->GetTrack()->GetDefinition()->GetParticleName();
            G4int trackID = step->GetTrack()->GetTrackID();    //<--- NEW
            fEventAction->Particle_Name_Pierced_Layer_A_s(p_name, trackID);       //<--- NEW
            


            G4Material *plastic_scin = step->GetPreStepPoint()->GetMaterial(); 
            G4MaterialPropertiesTable *Yield = plastic_scin->GetMaterialPropertiesTable(); 
            G4double Scintillation_Yield = Yield->GetConstProperty("SCINTILLATIONYIELD");

            generated_photons_A_s = edep_A_s* Scintillation_Yield; 
            generated_photons_A_s = G4Poisson(generated_photons_A_s); 

            size_t a = std::distance(scoringVolumesA.begin(),
                                              std::find(scoringVolumesA.begin(), scoringVolumesA.end(), barvolume));
            
            fEventAction->AddPhotonG_UsingEdep_A_s(a, generated_photons_A_s);
            fEventAction->AddEdepA_s(a, edep_A_s);
            
         }}
      

 if (std::find(scoringVolumesB.begin(), scoringVolumesB.end(), barvolume) != scoringVolumesB.end())
        {

         G4int copyNumB_s = touchedbar->GetCopyNumber(); 
         fEventAction->AddTraversedBar_B_s(copyNumB_s); 


         G4ThreeVector position_B_s = step->GetPostStepPoint()->GetPosition();
       
         G4double B_pos_x_s = position_B_s.x()/(cm);
         G4double B_pos_y_s = position_B_s.y()/(cm);
         G4double B_pos_z_s = position_B_s.z()/(cm);
         
      
         fEventAction->Add_Positions_Layer_B_x_s(B_pos_x_s);
         fEventAction->Add_Positions_Layer_B_y_s(B_pos_y_s);
         fEventAction->Add_Positions_Layer_B_z_s(B_pos_z_s);

                
         G4double edep_B_s = step->GetTotalEnergyDeposit();
         
         if (edep_B_s > 0.&& stepLength > 0.)
         {

            G4String p_name = step->GetTrack()->GetDefinition()->GetParticleName();
            G4int trackID = step->GetTrack()->GetTrackID();        //<--- NEW
            fEventAction->Particle_Name_Pierced_Layer_B_s(p_name, trackID);   //<--- NEW
        

            G4Material *plastic_scin = step->GetPreStepPoint()->GetMaterial(); 
            G4MaterialPropertiesTable *Yield = plastic_scin->GetMaterialPropertiesTable(); 
            G4double Scintillation_Yield = Yield->GetConstProperty("SCINTILLATIONYIELD");

            generated_photons_B_s = edep_B_s * Scintillation_Yield; 
            generated_photons_B_s = G4Poisson(generated_photons_B_s); 

            size_t b = std::distance(scoringVolumesB.begin(),
                                              std::find(scoringVolumesB.begin(), scoringVolumesB.end(), barvolume));
            
            fEventAction->AddPhotonG_UsingEdep_B_s(b, generated_photons_B_s);
            fEventAction->AddEdepB_s(b, edep_B_s);
            
         }
         }
  }
}


