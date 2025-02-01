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
 G4cout << "ID EVENT: "  << muonCount <<  G4endl;
 G4cout << "" << G4endl;


    
    traversed_Bars_A.clear();
    traversed_Bars_B.clear();
    Sumcopies = 0;  
     Hit_particle_passed_two_layers = false;
    

    TOTAL_Edep = 0.0;
    TOTAL_dEdx = 0.0;
    TOTAL_Detected_photons = 0.0;
    TOTAL_Generated_photons = 0.0;
}



void EventAction::EndOfEventAction(const G4Event*)
{
G4AnalysisManager *man = G4AnalysisManager::Instance();  


//------------------------------------------------------------------------------------------
G4cout << "------------------------------------------------------------\n" << G4endl;

G4cout << "ENERGY DEPOSITION ON BARS (MeV):   \n" << G4endl;
for (size_t i = 0; i < fEdepA.size(); i++){
    if(fEdepA[i]>0){
    G4cout << "BAR A | " << "ID: "<< i << " |  Edep:  " << fEdepA[i] << "  MeV" << G4endl;
      } 
     man->FillNtupleDColumn(1, i, fEdepA[i]);  
}

for (size_t j = 0; j < fEdepA.size(); j++){
    if(fEdepB[j]>0){
       G4cout << "BAR B | "<<"ID: "<< j + 20  << " |  Edep:  " << fEdepB[j] << "  MeV" << G4endl; 
    }
    man->FillNtupleDColumn(1, j + fEdepA.size(), fEdepB[j] );
    
}

G4cout << "" << G4endl;
if (fEdepA.size() != fEdepB.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden (EDEP)." << G4endl;
    return;
}

for (size_t i = 0; i < fEdepA.size(); ++i) {
       TOTAL_Edep += fEdepA[i] + fEdepB[i];

    }

    G4cout << "TOTAL EDEP:  " << TOTAL_Edep << G4endl;

    man->FillNtupleDColumn(1, 166, TOTAL_Edep);
  
//------------------------------------------------------------------------------------------
G4cout << "" << G4endl;
G4cout << "dE/dx (MeV/dx):   " << G4endl;

for (size_t k = 0; k < fTotaldEdx_A.size(); k++){
    if(fTotaldEdx_A[k]>0){
      G4cout << "BAR A | " << "ID: "<< k  << " |  dE/dx:  " << fTotaldEdx_A[k] << "  MeV/mm" << G4endl; 
    }
     man->FillNtupleDColumn(1, k + fEdepB.size() + fEdepA.size() , fTotaldEdx_A[k] );
}
   

for (size_t l = 0; l < fTotaldEdx_B.size(); l++){
    if(fTotaldEdx_B[l]>0){
       G4cout << "BAR B | " << "ID: "<<  l + 20  <<" |  dE/dx:  " << fTotaldEdx_B[l] << "  MeV/mm" << G4endl; 
    }
     man->FillNtupleDColumn(1, l + fTotaldEdx_A.size() + fEdepA.size() + fEdepB.size(), fTotaldEdx_B[l] );
}

G4cout << "" << G4endl;
if (fTotaldEdx_A.size() != fTotaldEdx_A.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden (dEdx)." << G4endl;
    return;
}

    for (size_t i = 0; i < fTotaldEdx_A.size(); ++i) {
        TOTAL_dEdx += fTotaldEdx_A[i] + fTotaldEdx_B[i];
    }
     G4cout << "total dE/dx:  " << TOTAL_dEdx <<"\n"<< G4endl;


    
    man->FillNtupleDColumn(1, 167, TOTAL_dEdx);

//------------------------------------------------------------------------------------------
G4cout << "\n------------------------------------------------------------" << G4endl;
G4cout << "" << G4endl;
G4cout << "DETECTED PHOTONS ON SiPM's:   " << G4endl;
for (size_t m = 0; m < photonHits_event_A.size(); m++){
    if(photonHits_event_A[m]>0){
        G4cout << "SiPM A | " <<"ID: "<<  m  << " |  Detected photons:  " << photonHits_event_A[m] << "  photons" << G4endl;   
    }
    man->FillNtupleDColumn(1, m + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,  photonHits_event_A[m] ); 
}

for (size_t n = 0; n < photonHits_event_B.size(); n++){
    if(photonHits_event_B[n]>0){
        G4cout << "SiPM B | " <<"ID: "<< n + 20 << " |  Detected photons:  " << photonHits_event_B[n] << "  photons" << G4endl; 
       }
     man->FillNtupleDColumn(1, n + photonHits_event_A.size() + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,  photonHits_event_B[n] );
}

//............................................................................................
if (photonHits_event_A.size() != photonHits_event_B.size() ) {
    G4cout << "Error: los tamaños de las listas no coinciden (Detected Photons)." << G4endl;
    return;
}

//             TO GET THE RIGHT NUMBER OF DETECTED PHOTONS 

G4int photons_detected_real_A = 0.0;

G4int photons_detected_real_B = 0.0;

    for (auto bar : traversed_Bars_A) {
        if(bar >=0 && bar <20){
            photons_detected_real_A += photonHits_event_A[bar];
        } else{
            G4cerr << " ERROR: índice inválido en traversed_Bars_A: " << bar << G4endl;
        }   
    }
    
    for (auto bar : traversed_Bars_B) {
        if(bar >=20 && bar <40){
            photons_detected_real_B += photonHits_event_B[bar-20];
        } else {
            G4cerr << "ERROR: índice inválido en traversed_Bars_B: " << bar << G4endl;
        }
    }

    if(photons_detected_real_A > 0 && photons_detected_real_B > 0){
    TOTAL_Detected_photons = photons_detected_real_A + photons_detected_real_B;
    }

    G4cout << "\n" << G4endl;
    G4cout <<"TOTAL DETECTED PHOTONS: "<< TOTAL_Detected_photons << " photons \n"<< G4endl;       
            
    man->FillNtupleIColumn(1, 168, TOTAL_Detected_photons);
  

// INSIDE THE VECTORS
/*
G4cout << "traversed_Bars_A: ";
for (auto bar : traversed_Bars_A) G4cout << bar << " ";
G4cout << G4endl;

G4cout << "traversed_Bars_B: ";
for (auto bar : traversed_Bars_B) G4cout << bar << " ";
G4cout << G4endl;

G4cout << "photonHits_event_A: ";
for (auto photons : photonHits_event_A) G4cout << photons << " ";
G4cout << G4endl;

G4cout << "photonHits_event_B: ";
for (auto photons : photonHits_event_B) G4cout << photons << " ";
G4cout << G4endl;
*/


//------------------------------------------------------------------------------------------
G4cout << "\n" << G4endl;
G4cout << "GENERATED PHOTONS:   " << G4endl;
for (size_t u = 0; u < fGenerated_photons_A.size(); ++u){
    if(fGenerated_photons_A[u]>0){
         G4cout << "BAR A | " <<"ID: "<<  u  << " |  Generated photons:  " << fGenerated_photons_A[u] << "  photons" << G4endl;   
       }
    man->FillNtupleDColumn(1, u + photonHits_event_B.size() + photonHits_event_A.size() + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,   fGenerated_photons_A[u] );   
}

for (size_t v = 0; v < fGenerated_photons_B.size(); v++){
    if(fGenerated_photons_B[v]>0){
         G4cout << "BAR B | " <<"ID: "<<  v + 20  << " |  Generated photons:  " << fGenerated_photons_B[v] << "  photons" << G4endl; 
        }
    man->FillNtupleDColumn(1, v + fGenerated_photons_A.size() + photonHits_event_B.size() + photonHits_event_A.size() + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,   fGenerated_photons_B[v] ); 
}


G4cout << "\n" << G4endl;

if (fGenerated_photons_A.size() != fGenerated_photons_B.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden (Generated Photons)." << G4endl;
    return;
}

for (size_t i = 0; i < fGenerated_photons_A.size(); ++i) {
        TOTAL_Generated_photons += fGenerated_photons_A[i] + fGenerated_photons_B[i];
    }

    G4cout << "TOTAL GENERATED PHOTONS:  " << TOTAL_Generated_photons <<" photons "<< G4endl;

      man->FillNtupleDColumn(1, 169, TOTAL_Generated_photons);


G4cout << "\n------------------------------------------------------------" << G4endl;

//------------------------------------------------------------------------------------------
//              GET THE COPY NUMBER OF THE BARS AND DEFINE THE HIT

G4cout << "" << G4endl;
G4cout << "HIT STATUS: " << G4endl;
G4cout << "" << G4endl;

G4cout << "BAR A | ID: ";
if (traversed_Bars_A.empty()) {
    G4cout << "-1 ";
    man->FillNtupleDColumn(1, 163, -1);
} else {
    for (auto bar : traversed_Bars_A) {
        G4cout << bar << " ";
        man->FillNtupleDColumn(1,163,bar);
    }
}
 G4cout << G4endl;


    G4cout << "BAR B | ID: ";
    if(traversed_Bars_B.empty()){
        G4cout<< "non (0)";
        man->FillNtupleDColumn(1,164,0);
    }else{
    for (auto bar : traversed_Bars_B) {
        G4cout << bar << " ";
        
        man->FillNtupleDColumn(1,164,bar);
    }
    }
    G4cout << G4endl;


    for(size_t i = 0; i < traversed_Bars_A.size(); ++i){
        if(traversed_Bars_A[i]>=0 && traversed_Bars_A[i]<20){
            if(traversed_Bars_B[i]>=20 && traversed_Bars_B[i]<40){
                Hit_particle_passed_two_layers = true;
             
            }
        } else {
            Hit_particle_passed_two_layers = false;
        }  
    }


    G4int hit_just_two_layers_crossed = static_cast<G4int>(Hit_particle_passed_two_layers);

    man->FillNtupleIColumn(1, 165, hit_just_two_layers_crossed);

    G4cout << "" << G4endl;
    G4cout << "HIT:  " << Hit_particle_passed_two_layers << "  (1 yes.  0 no.)" << G4endl;
    G4cout << "\n" << G4endl;


 //-------------------------------------------------------------------------------------------


man->AddNtupleRow(1);


}



