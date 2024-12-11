//   EVENT ACTION SOURCE

#include "EventAction.hh" 


EventAction::EventAction(RunAction*) : photonHits_event_A(20, 0), photonHits_event_B(20, 0) 
{
fEdepA.resize(20, 0.0); // Initialize with 20 bars, all values set to 0
fEdepB.resize(20, 0.0); // Initialize with 20 bars, all values set to 0

fTotaldEdx_A.resize(20, 0.0);
fTotaldEdx_B.resize(20, 0.0);

fGenerated_photons_A.resize(20, 0.0);
fGenerated_photons_B.resize(20, 0.0);

 muonCount = 0;

    traversed_Bars_A.clear();
    traversed_Bars_B.clear();
     Hit_particle_passed_two_layers = false;
    Sumcopies = 0;

    TOTAL_Edep = 0.0;
    TOTAL_dEdx = 0.0;
    TOTAL_Detected_photons = 0.0;
    TOTAL_Generated_photons = 0.0;

}


EventAction::~EventAction()
{}



void EventAction::BeginOfEventAction(const G4Event*) 
{
    photonHits_event_A.assign(20, 0);
    photonHits_event_B.assign(20, 0);
    
    fEdepA.assign(20, 0.0); // Initialize with 20 bars, all values set to 0
    fEdepB.assign(20, 0.0);

    fTotaldEdx_A.assign(20, 0.0);
    fTotaldEdx_B.assign(20, 0.0);

    fGenerated_photons_A.assign(20, 0.0);
    fGenerated_photons_B.assign(20, 0.0);

 muonCount++;
 G4cout << "# # # ID EVENT: "  << muonCount << G4endl;
    
    traversed_Bars_A.clear();
    traversed_Bars_B.clear();
    Sumcopies = 0;  

    TOTAL_Edep = 0.0;
    TOTAL_dEdx = 0.0;
    TOTAL_Detected_photons = 0.0;
    TOTAL_Generated_photons = 0.0;


}



void EventAction::EndOfEventAction(const G4Event*)
{
G4AnalysisManager *man = G4AnalysisManager::Instance();  

//------------------------------------------------------------------------------------------
G4cout << "DEPOSITED ENERGY ON BARS:   " << G4endl;
for (size_t i = 0; i < fEdepA.size(); i++){
    if(fEdepA[i]>0){
        G4cout << "BAR ID A:    " << i << "     Edep:  " << fEdepA[i] << "  MeV" << G4endl;
    } 
     man->FillNtupleDColumn(1, i, fEdepA[i]);  
}

for (size_t j = 0; j < fEdepA.size(); j++){
    if(fEdepB[j]>0){
       G4cout << "BAR ID B:    " << j + 20  << "     Edep:  " << fEdepB[j] << "  MeV" << G4endl; 
    }
    man->FillNtupleDColumn(1, j + fEdepA.size(), fEdepB[j] );
    
}

    
//------------------------------------------------------------------------------------------
G4cout << "" << G4endl;
G4cout << "dE/dx ON BARS:   " << G4endl;

for (size_t k = 0; k < fTotaldEdx_A.size(); k++){
    if(fTotaldEdx_A[k]>0){
       G4cout << "BAR ID A:    " <<  k  << "     dE/dx:  " << fTotaldEdx_A[k] << "  MeV/mm" << G4endl; 
    }
     man->FillNtupleDColumn(1, k + fEdepB.size() + fEdepA.size() , fTotaldEdx_A[k] );
}
   

for (size_t l = 0; l < fTotaldEdx_B.size(); l++){
    if(fTotaldEdx_B[l]>0){
       G4cout << "BAR ID B:    " <<  l + 20  << "     dE/dx:  " << fTotaldEdx_B[l] << "  MeV/mm" << G4endl; 
    }
     man->FillNtupleDColumn(1, l + fTotaldEdx_A.size() + fEdepA.size() + fEdepB.size(), fTotaldEdx_B[l] );
}

//------------------------------------------------------------------------------------------
G4cout << "" << G4endl;
G4cout << "DETECTED PHOTONS ON SiPM's:   " << G4endl;
for (size_t m = 0; m < photonHits_event_A.size(); m++){
    if(photonHits_event_A[m]>0){
        G4cout << "SiPM ID A:    " <<  m  << "     Detected photons:  " << photonHits_event_A[m] << "  photons" << G4endl;   
    }
    man->FillNtupleDColumn(1, m + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,  photonHits_event_A[m] ); 
}

for (size_t n = 0; n < photonHits_event_B.size(); n++){
    if(photonHits_event_B[n]>0){
        G4cout << "SiPM ID B:    " <<  n +20   << "     Detected photons:  " << photonHits_event_B[n] << "  photons" << G4endl; 
        }
     man->FillNtupleDColumn(1, n + photonHits_event_A.size() + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,  photonHits_event_B[n] );
}

//------------------------------------------------------------------------------------------
G4cout << "" << G4endl;
G4cout << "GENERATED PHOTONS:   " << G4endl;
for (size_t u = 0; u < fGenerated_photons_A.size(); ++u){
    if(fGenerated_photons_A[u]>0){
        G4cout << "BAR ID A:    " <<  u  << "     Generated photons:  " << fGenerated_photons_A[u] << "  photons" << G4endl;   
        }
    man->FillNtupleDColumn(1, u + photonHits_event_B.size() + photonHits_event_A.size() + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,   fGenerated_photons_A[u] );   
}

for (size_t v = 0; v < fGenerated_photons_B.size(); v++){
    if(fGenerated_photons_B[v]>0){
        G4cout << "BAR ID B:    " <<  v + 20   << "     Generated photons:  " << fGenerated_photons_B[v] << "  photons" << G4endl; 
        }
    man->FillNtupleDColumn(1, v + fGenerated_photons_A.size() + photonHits_event_B.size() + photonHits_event_A.size() + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,   fGenerated_photons_B[v] ); 
}
G4cout << "" << G4endl;



//X TODO ESTO

    // Imprime las barras atravesadas
    G4cout << "Barras A atravesadas: ";
    for (auto bar : traversed_Bars_A) {
        G4cout << bar << " ";
        man->FillNtupleDColumn(1,163,bar);
    }
    G4cout << G4endl;

    G4cout << "Barras B atravesadas: ";
    for (auto bar : traversed_Bars_B) {
        G4cout << bar << " ";
        man->FillNtupleDColumn(1,164,bar);
    }
    G4cout << G4endl;

    for(size_t i = 0; i < traversed_Bars_A.size(); ++i){
        Sumcopies = traversed_Bars_A[i] + traversed_Bars_B[i];
    }
    G4cout << "SUMA DE COPIAS:  " << Sumcopies << G4endl;
    G4cout << G4endl;

    if (Sumcopies >= 20 && Sumcopies <= 58) {
        Hit_particle_passed_two_layers = true;
    } else {
        Hit_particle_passed_two_layers = false;
    }


 //-------------------------------------------------------------------------------------------


//------- THIS CALCULATES THE TOTAL OF EDEP, dE/dx, GENERATED AND DETECTED PHOTONS ----------------
//         first, It verifies if the size of the vectors are the same for both layers

if (fEdepA.size() != fEdepB.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden (EDEP)." << G4endl;
    return;
}

if (fTotaldEdx_A.size() != fTotaldEdx_A.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden (dEdx)." << G4endl;
    return;
}

if (photonHits_event_A.size() != photonHits_event_B.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden (Detected Photons)." << G4endl;
    return;
}

if (fGenerated_photons_A.size() != fGenerated_photons_B.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden (Generated Photons)." << G4endl;
    return;
}


   for (size_t i = 0; i < fEdepA.size(); ++i) {
       TOTAL_Edep += fEdepA[i] + fEdepB[i];

    }

     for (size_t i = 0; i < fTotaldEdx_A.size(); ++i) {
        TOTAL_dEdx += fTotaldEdx_A[i] + fTotaldEdx_B[i];
    }

    for (size_t i = 0; i < photonHits_event_A.size(); ++i) {
        TOTAL_Detected_photons += photonHits_event_A[i] + photonHits_event_B[i];
    }

   for (size_t i = 0; i < fGenerated_photons_A.size(); ++i) {
        TOTAL_Generated_photons += fGenerated_photons_A[i] + fGenerated_photons_B[i];
    }

    // Save the data 
    //man->FillNtupleDColumn(1, 162, TOTAL_Edep);
    //man->FillNtupleDColumn(1, 163, TOTAL_dEdx);
    //man->FillNtupleDColumn(1, 164, TOTAL_Detected_photons);
    //man->FillNtupleDColumn(1, 165, TOTAL_Generated_photons);

//--------------------------------------------------------------------------------------------------------



man->AddNtupleRow(1);


}



