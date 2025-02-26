//    RUN ACTION SOURCE

#include "RunAction.hh"

RunAction::RunAction(): photonHits(40, 0)
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();


 man->CreateNtuple("Photons","information about the Photons generated by scintillation");
 man->CreateNtupleIColumn("fEvent");
 man->FinishNtuple(0);



  man->CreateNtuple("Edep","Data from each event");

  for (G4int i = 0; i < 40; i++) {
        std::stringstream columnName;
        columnName << "Energy_Deposition_MeV_On_Bar_" << i;
        man->CreateNtupleDColumn(columnName.str());
    }

  for (G4int j = 0; j < 40; j++){
      std::stringstream columnName;
      columnName << "dEdx_MeVmm_On_Bar_" << j;
      man->CreateNtupleDColumn(columnName.str());
  }

  for (G4int k = 0; k < 40; k++){
      std::stringstream columnName;
      columnName << "Photons_Detected_perEvent_by_SiPM_" << k;
      man->CreateNtupleDColumn(columnName.str());
  }

   for (G4int l = 0; l < 40; l++){
      std::stringstream columnName;
      columnName << "Photons_Generated_perEvent_on_Bar_" << l;
      man->CreateNtupleDColumn(columnName.str());
  }
  man->CreateNtupleDColumn("Particle_Momentum_MeV");
  man->CreateNtupleDColumn("Particle_Momentum_GeV");
  man->CreateNtupleDColumn("angle");  //162
  man->CreateNtupleDColumn("Copy_num_Bar_Traversed_A"); //163
  man->CreateNtupleDColumn("Copy_num_Bar_Traversed_B"); //164
  man->CreateNtupleIColumn("HIT_particle_passed_both_layers");  // 165

  man->CreateNtupleDColumn("Total_Energy_Deposition");  //166
  man->CreateNtupleDColumn("Total_dEdx");  //167
  man->CreateNtupleIColumn("Total_Photons_Detected");  //168
  man->CreateNtupleDColumn("Total_Photons_Generated");  //169

  man->CreateNtupleSColumn("PARTICLE_NAME_ON_A"); //170
  man->CreateNtupleSColumn("PARTICLE_NAME_ON_B"); //171

  man->CreateNtupleDColumn("total_edep_on_A"); //172
  man->CreateNtupleDColumn("total_edep_on_B"); //173

  man->FinishNtuple(1);


 
}

RunAction::~RunAction()
{}


void RunAction:: BeginOfRunAction(const G4Run* run)
{
 G4AnalysisManager *man = G4AnalysisManager::Instance(); 

 photonHits.assign(40, 0);  


 G4int runID = run->GetRunID();

 std::stringstream strRunID;
 strRunID << runID;

 man->OpenFile("Output"+strRunID.str()+".root");

 //photonHits = 0; 
}


void RunAction::EndOfRunAction(const G4Run*)
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();

 
  //G4cout << "NUMBER OF PHOTONS DETECTED: " << photonHits << G4endl; 

  //man->FillNtupleDColumn(1,0,photonHits); //total
 
 man->Write();
 man->CloseFile();
}

