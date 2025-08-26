//   EVENT ACTION SOURCE

#include "EventAction.hh" 
using namespace std;


EventAction::EventAction(RunAction*) : photonHits_event_A(20, 0), photonHits_event_B(20, 0), photonHits_event_A_s(20, 0), photonHits_event_B_s(20, 0) 
{
fEdepA.resize(20, 0.0); 
fEdepB.resize(20, 0.0); 


fEdepA_s.resize(20, 0.0);
fEdepB_s.resize(20, 0.0);


fTotaldEdx_A.resize(20, 0.0);
fTotaldEdx_B.resize(20, 0.0);


fGenerated_photons_A.resize(20, 0.0);
fGenerated_photons_B.resize(20, 0.0);

fGenerated_photons_A_s.resize(20, 0.0);
fGenerated_photons_B_s.resize(20, 0.0);


 muonCount = 0;


    traversed_Bars_A.clear();
    traversed_Bars_B.clear();


    traversed_Bars_A_s.clear();
    traversed_Bars_B_s.clear();


    Hit_particle_passed_two_layers = false;
    Sumcopies = 0;

    TOTAL_Edep = 0.0;
    TOTAL_dEdx = 0.0;
    TOTAL_Detected_photons = 0.0;
    TOTAL_Generated_photons = 0.0;
    total_edep_A = 0.0;
    total_edep_B = 0.0;

    TOTAL_Edep_s = 0.0;
    TOTAL_Detected_photons_s = 0.0;
    TOTAL_Generated_photons_s = 0.0;;


    particles_names_A.clear();
    particles_names_B.clear();
    particles_names_A_s.clear();
    particles_names_B_s.clear();



    pos_layer_A_x.clear();
    pos_layer_A_y.clear();
    pos_layer_A_z.clear();

    pos_layer_B_x.clear();
    pos_layer_B_y.clear();
    pos_layer_B_z.clear();


    pos_layer_A_x_s.clear();
    pos_layer_A_y_s.clear();
    pos_layer_A_z_s.clear();

    pos_layer_B_x_s.clear();
    pos_layer_B_y_s.clear();
    pos_layer_B_z_s.clear();


    fEdep_abs = 0;
    fdEdx_abs = 0;

TOTAL_Detected_photons_others = 0;  //<---- NEW
    photons_detected_others_A = 0;  //<---- NEW 
    photons_detected_others_B = 0;  //<---- NEW

    particle_tracks_A.clear();  //<---- NEW 
    particle_tracks_B.clear();  //<---- NEW

    particle_tracks_A_s.clear();    //<---- NEW
    particle_tracks_B_s.clear();    //<---- NEW

    particle_name_tracks_A.clear();  //<---- NEW 
    particle_name_tracks_B.clear();  //<---- NEW

    particle_name_tracks_A_s.clear();    //<---- NEW
    particle_name_tracks_B_s.clear();    //<---- NEW

}


EventAction::~EventAction()
{}



void EventAction::BeginOfEventAction(const G4Event*) 
{
    photonHits_event_A.assign(20, 0);
    photonHits_event_B.assign(20, 0);

    photonHits_event_A_s.assign(20, 0); 
    photonHits_event_B_s.assign(20, 0); 
    
    fEdepA.assign(20, 0.0); // Initialize with 20 bars, all values set to 0
    fEdepB.assign(20, 0.0);

    fEdepA_s.assign(20, 0.0);
    fEdepB_s.assign(20, 0.0);


    fTotaldEdx_A.assign(20, 0.0);
    fTotaldEdx_B.assign(20, 0.0);


    fGenerated_photons_A.assign(20, 0.0);
    fGenerated_photons_B.assign(20, 0.0);


    fGenerated_photons_A_s.assign(20, 0.0);
    fGenerated_photons_B_s.assign(20, 0.0);


 muonCount++;
 G4cout << "ID EVENT: "  << muonCount <<  G4endl;
 G4cout << "" << G4endl;

    
    traversed_Bars_A.clear();
    traversed_Bars_B.clear();

    
    traversed_Bars_A_s.clear();
    traversed_Bars_B_s.clear();


    Sumcopies = 0;  
    Hit_particle_passed_two_layers = false;
    

    TOTAL_Edep = 0.0;
    TOTAL_dEdx = 0.0;
    TOTAL_Detected_photons = 0.0;
    TOTAL_Generated_photons = 0.0;
    total_edep_A = 0.0;
    total_edep_B = 0.0;


    TOTAL_Edep_s = 0.0;
    TOTAL_Detected_photons_s = 0.0;
    TOTAL_Generated_photons_s = 0.0;


    particles_names_A.clear();
    particles_names_B.clear();

    particles_names_A_s.clear();
    particles_names_B_s.clear();

    particle_tracks_A.clear();  //<---- NEW 
    particle_tracks_B.clear();  //<---- NEW

    particle_tracks_A_s.clear();    //<---- NEW
    particle_tracks_B_s.clear();    //<---- NEW

    particle_name_tracks_A.clear();  //<---- NEW 
    particle_name_tracks_B.clear();  //<---- NEW

    particle_name_tracks_A_s.clear();    //<---- NEW
    particle_name_tracks_B_s.clear();    //<---- NEW




    pos_layer_A_x.clear();
    pos_layer_A_y.clear();
    pos_layer_A_z.clear();

    pos_layer_B_x.clear();
    pos_layer_B_y.clear();
    pos_layer_B_z.clear();


    pos_layer_A_x_s.clear();
    pos_layer_A_y_s.clear();
    pos_layer_A_z_s.clear();

    pos_layer_B_x_s.clear();
    pos_layer_B_y_s.clear();
    pos_layer_B_z_s.clear();


    fEdep_abs = 0;
    fdEdx_abs = 0;

    TOTAL_Detected_photons_others = 0;  //<---- NEW
    photons_detected_others_A = 0;  //<---- NEW
    photons_detected_others_B = 0;  //<---- NEW



}



void EventAction::EndOfEventAction(const G4Event*)
{

G4AnalysisManager *man = G4AnalysisManager::Instance();  



//------------------------------- EDEP -----------------------------------------------------------
G4cout << "===============================================================\n" << G4endl;

G4cout << "ENERGY DEPOSITION ON BARS (MeV):   \n" << G4endl;
for (size_t i = 0; i < fEdepA.size(); i++){
    if(fEdepA[i]>0){
    G4cout << "BAR A | " << "ID: "<< i << " |  Edep:  " << fEdepA[i] << "  MeV" << G4endl;
      } 
     man->FillNtupleDColumn(1, i, fEdepA[i]);  
}

for (size_t j = 0; j < fEdepB.size(); j++){
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

    G4cout << "TOTAL EDEP:  " << TOTAL_Edep << "MeV"<<G4endl;

    man->FillNtupleDColumn(1, 166, TOTAL_Edep);



//------------------ PER LAYER ------------------
for(size_t i = 0; i < fEdepA.size(); ++i){
    if(fEdepA[i] > 0){
        man->FillNtupleDColumn(1,172,fEdepA[i]);
    }
}

for(size_t i = 0; i < fEdepB.size(); ++i){
    if(fEdepB[i] > 0){
        man->FillNtupleDColumn(1,173,fEdepB[i]);
    }
}




//----------------------------------------------------------
G4cout << "\n**************************************************************" << G4endl;
G4cout << "EDEP TOTAL IN ABSORBER: " << fEdep_abs<<" MeV" << G4endl;
man->FillNtupleDColumn(1, 191, fEdep_abs);
G4cout << "************************************************************** \n" << G4endl;




G4cout << "----------------------------------------------------------------"<< G4endl;
G4cout << "" <<G4endl;
    G4cout << "(Edep) SECONDARIES  \n" << G4endl;

G4cout << "ENERGY DEPOSITION ON BARS (MeV):   \n" << G4endl;
for (size_t i = 0; i < fEdepA_s.size(); i++){
    if(fEdepA_s[i]>0){
    G4cout << "BAR A | " << "ID: "<< i << " |  Edep:  " << fEdepA_s[i] << "  MeV" << G4endl;
      }  
}

for (size_t j = 0; j < fEdepB_s.size(); j++){
    if(fEdepB_s[j]>0){
       G4cout << "BAR B | "<<"ID: "<< j + 20  << " |  Edep:  " << fEdepB_s[j] << "  MeV" << G4endl; 
    }
}


G4cout << "" << G4endl;
if (fEdepA_s.size() != fEdepB_s.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden (EDEP)." << G4endl;
    return;
}
for (size_t i = 0; i < fEdepA_s.size(); ++i) {
       TOTAL_Edep_s += fEdepA_s[i] + fEdepB_s[i];
    }
    G4cout << "TOTAL EDEP sec:  " << TOTAL_Edep_s << " MeV"<<G4endl;

    man->FillNtupleDColumn(1, 192, TOTAL_Edep_s); 



    for(size_t i = 0; i < fEdepA_s.size(); ++i){
        if(fEdepA_s[i] > 0){
            man->FillNtupleDColumn(1,193,fEdepA_s[i]);
        }
    }
    
    for(size_t i = 0; i < fEdepB_s.size(); ++i){
        if(fEdepB_s[i] > 0){
           man->FillNtupleDColumn(1,194,fEdepB_s[i]);
        }
    }
    



//-------------------------------------- dE/dx ----------------------------------------------------
G4cout << "\n===============================================================\n" << G4endl;
G4cout << "dE/dx (MeV/dx):   " << G4endl;
G4cout << "\n" <<G4endl;

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
     G4cout << "total dE/dx:  " << TOTAL_dEdx <<" MeV / mm\n"<< G4endl;


    
    man->FillNtupleDColumn(1, 167, TOTAL_dEdx);



//------------------ PER LAYER ----------------------

for(size_t i = 0; i < fTotaldEdx_A.size(); ++i){
    if(fTotaldEdx_A[i] > 0){
        man->FillNtupleDColumn(1,174,fTotaldEdx_A[i]);
    }
}

for(size_t i = 0; i < fTotaldEdx_B.size(); ++i){
    if(fTotaldEdx_B[i] > 0){
        man->FillNtupleDColumn(1,175,fTotaldEdx_B[i]);
    }
}
//---------------------------------------------------





//-------------------------------- DETECTED PHOTONS ---------------------------------------------------------
G4cout << "\n===============================================================" << G4endl;
G4cout << "" << G4endl;
G4cout << "DETECTED PHOTONS ON SiPM's:   " << G4endl;
G4cout << "\n" <<G4endl;

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

G4cout << "\n"<<G4endl;
G4cout << "(by mu+ and pi+)"<<G4endl;
G4cout << ""<<G4endl;
G4int photons_detected_real_A = 0.0;
G4int photons_detected_real_B = 0.0;




    for (auto bar : traversed_Bars_A) {
        if(bar >=0 && bar <20){
            photons_detected_real_A += photonHits_event_A[bar];
            G4cout <<"SiPM A | ID: "<< bar  <<G4endl;
            man->FillNtupleDColumn(1,176,photons_detected_real_A);

        } else{
            G4cerr << " ERROR: índice inválido en traversed_Bars_A: " << bar << G4endl;
        }   
    }
    
    for (auto bar : traversed_Bars_B) {
        if(bar >=20 && bar <40){
            photons_detected_real_B += photonHits_event_B[bar-20];
                G4cout <<"SiPM B | ID: "<< bar  <<G4endl;
            man->FillNtupleDColumn(1,177,photons_detected_real_B);

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



//-------------------------------- Secondaries ---------------------------------------------------------
G4cout << "\n-------------------------------------------------------------" << G4endl;
G4cout << "SECONDARIES  detected photons on SiPM's:   " << G4endl;
G4cout << "\n" <<G4endl;


G4cout << "(by secondaries)"<<G4endl;           //<---- NEW (until line 507)
G4cout << ""<<G4endl;
    // boolean vectors. True if the member of the vector was pierced by mu/pi.
    std::vector<G4bool> visitedA(20, false);
    std::vector<G4bool> visitedB(20, false);


    //filling the vector with True's.
    for (auto bar : traversed_Bars_A) {
        if (bar >= 0 && bar < 20) visitedA[bar] = true;
    }

    for (auto bar : traversed_Bars_B) {
        if (bar >= 20 && bar < 40) visitedB[bar - 20] = true;
    }



photons_detected_others_A = 0;
photons_detected_others_B = 0;

    for (int i = 0; i < 20; ++i) {
        if (!visitedA[i]){ 
            photons_detected_others_A += photonHits_event_A[i];
        if (photonHits_event_A[i] > 0){
            G4cout <<"SiPM A | ID: "<< i  <<G4endl;
            man->FillNtupleDColumn(1, 195, photons_detected_others_A);
        }
        }

        if (!visitedB[i]){ photons_detected_others_B += photonHits_event_B[i];
         if (photonHits_event_B[i] > 0){
            G4cout <<"SiPM B | ID: "<< i + 20  <<G4endl;
            man->FillNtupleDColumn(1, 196, photons_detected_others_B);
        }
        } 
    }

    TOTAL_Detected_photons_others = photons_detected_others_A + photons_detected_others_B;

    
    
    G4cout <<"TOTAL DETECTED PHOTONS BY SECONDARIES: "<<   TOTAL_Detected_photons_others << " photons \n"<< G4endl;       
    
    man->FillNtupleIColumn(1, 197, TOTAL_Detected_photons_others);
    
  G4cout << "\n===============================================================" << G4endl;




//----------------------------------------GENERATED PHOTONS-------------------------------------------------
G4cout << "" << G4endl;


G4cout << "GENERATED PHOTONS:   " << G4endl;
for (size_t u = 0; u < fGenerated_photons_A.size(); ++u){
    if(fGenerated_photons_A[u]>0.0000001){
         G4cout << "BAR A | " <<"ID: "<<  u  << " |  Generated photons:  " << fGenerated_photons_A[u] << "  photons" << G4endl;   
       }
    man->FillNtupleDColumn(1, u + photonHits_event_B.size() + photonHits_event_A.size() + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,   fGenerated_photons_A[u] );   
}

for (size_t v = 0; v < fGenerated_photons_B.size(); v++){
    if(fGenerated_photons_B[v]>0.0000001){
         G4cout << "BAR B | " <<"ID: "<<  v + 20  << " |  Generated photons:  " << fGenerated_photons_B[v] << "  photons" << G4endl; 
        }
    man->FillNtupleDColumn(1, v + fGenerated_photons_A.size() + photonHits_event_B.size() + photonHits_event_A.size() + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,   fGenerated_photons_B[v] ); 
}


G4cout << "\n" << G4endl;

if (fGenerated_photons_A.size() != fGenerated_photons_B.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden (Generated Photons)." << G4endl;
    return;
}


G4int photons_gen_A = 0.0;
G4int photons_gen_B = 0.0;
G4int photons_gen_A_s = 0.0;
G4int photons_gen_B_s = 0.0;


for (size_t i = 0; i < fGenerated_photons_A.size(); ++i) {
    photons_gen_A += fGenerated_photons_A[i];
}
for (size_t i = 0; i < fGenerated_photons_B.size(); ++i) {
    photons_gen_B += fGenerated_photons_B[i];
}
        TOTAL_Generated_photons += photons_gen_A + photons_gen_B;
    
    

    G4cout << "TOTAL GENERATED PHOTONS:  " << TOTAL_Generated_photons <<" photons "<< G4endl;

      man->FillNtupleDColumn(1, 169, TOTAL_Generated_photons);




//------------------ PER LAYER ----------------------
for(size_t i = 0; i < fGenerated_photons_A.size(); ++i){
    if(fGenerated_photons_A[i] > 0.0000001){
        man->FillNtupleDColumn(1,178,fGenerated_photons_A[i]);
    }
}

for(size_t i = 0; i < fGenerated_photons_B.size(); ++i){
    if(fGenerated_photons_B[i] > 0.0000001){
        man->FillNtupleDColumn(1,179,fGenerated_photons_B[i]);
    }
}
G4cout << "\n------------------------------------------------------------" << G4endl;



    //----------------------- Secondaries ----------------------------------
G4cout << "" << G4endl;
G4cout << "GENERATED PHOTONS BY SECONDARIES PARTICLES ON BARS:   \n" << G4endl;
for (size_t i = 0; i < fGenerated_photons_A_s.size(); i++){
    if(fGenerated_photons_A_s[i]>0.0000001){
    G4cout << "BAR A | " << "ID: "<< i << " |  Generated photons:  " << fGenerated_photons_A_s[i] << "  photons" << G4endl;
      } 
 
}

for (size_t j = 0; j < fGenerated_photons_B_s.size(); j++){
    if(fGenerated_photons_B_s[j]>0.0000001){
       G4cout << "BAR B | "<<"ID: "<< j + 20  << " |  Generated photons:  " << fGenerated_photons_B_s[j] << "  photons" << G4endl; 
    }

    
}

G4cout << "" << G4endl;
if (fGenerated_photons_A_s.size() != fGenerated_photons_B_s.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden." << G4endl;
    return;
}


for (size_t i = 0; i < fGenerated_photons_A_s.size(); ++i) {
    photons_gen_A_s += fGenerated_photons_A_s[i];
}
for (size_t i = 0; i < fGenerated_photons_B_s.size(); ++i) {
    photons_gen_B_s += fGenerated_photons_B_s[i];
}

    

    TOTAL_Generated_photons_s += photons_gen_A_s + photons_gen_B_s;


    G4cout << "TOTAL GENERATED PHOTONS BY SECONDARIES PARTICLES:  " << TOTAL_Generated_photons_s << " photons"<<G4endl;
    man->FillNtupleDColumn(1, 198, TOTAL_Generated_photons_s); 


//------------------ PER LAYER ----------------------
for(size_t i = 0; i < fGenerated_photons_A_s.size(); ++i){
    if(fGenerated_photons_A_s[i] > 0.0000001){
        man->FillNtupleDColumn(1, 199,fGenerated_photons_A_s[i]);
    }
}

for(size_t i = 0; i < fGenerated_photons_B_s.size(); ++i){
    if(fGenerated_photons_B_s[i] > 0.0000001){
       man->FillNtupleDColumn(1, 200,fGenerated_photons_B_s[i]);
    }
}

G4cout << "\n===============================================================" << G4endl;




//------------------------------------------------------------------------------------------
//              GET THE COPY NUMBER OF THE BARS AND DEFINE THE HIT

G4cout << "" << G4endl;
G4cout << "HIT STATUS: " << G4endl;
G4cout << "" << G4endl;

G4cout << "BAR A | ID: ";
if (traversed_Bars_A.empty()) {
    G4cout << "-1 | NO HIT ";
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
        G4cout<< "0 | NO HIT ";
        man->FillNtupleDColumn(1,164,0);
    }else{
    for (auto bar : traversed_Bars_B) {
        G4cout << bar << " ";
        
        man->FillNtupleDColumn(1,164,bar);
    }
    }
    G4cout << G4endl;


    for(size_t i = 0; i < traversed_Bars_A.size(); ++i){
        if(i < traversed_Bars_B.size()) { 
        if(traversed_Bars_A[i]>=0 && traversed_Bars_A[i]<20 &&
            traversed_Bars_B[i]>=20 && traversed_Bars_B[i]<40){
                Hit_particle_passed_two_layers = true;
             
            }else {
                Hit_particle_passed_two_layers = false;
            }  }
        } 
    


    G4int hit_just_two_layers_crossed = static_cast<G4int>(Hit_particle_passed_two_layers);

    man->FillNtupleIColumn(1, 165, hit_just_two_layers_crossed);

    G4cout << "" << G4endl;
    G4cout << "HIT:  " << Hit_particle_passed_two_layers << "  (1 | yes    0 | no)" << G4endl;
    G4cout << "\n" << G4endl;

 


        G4cout << "--------------------------------------------------------------------------------" << G4endl;
    G4cout <<"BARS ID SECONDARY \n"<<G4endl;
    G4cout << "BAR A | ID: ";
    if (traversed_Bars_A_s.empty()) {
        G4cout << "-1 | NO HIT ";
        man->FillNtupleDColumn(2, 0, -1);
    } else {
        for (auto bar : traversed_Bars_A_s) {
            G4cout << bar << " ";
           man->FillNtupleDColumn(2, 0,bar);
        }
    }
     G4cout << G4endl;
     G4cout << "BAR B | ID: ";
        if(traversed_Bars_B_s.empty()){
            G4cout<< "0 | NO HIT ";
            man->FillNtupleDColumn(2, 1, 0);
        }else{
        for (auto bar : traversed_Bars_B_s) {
            G4cout << bar << " ";
            
            man->FillNtupleDColumn(2, 1,bar);
        }
        }
        G4cout << G4endl;
    
        G4cout <<"\n"<<G4endl;







 //------------------------------------ PARTICLE NAMES-------------------------------------------------------

G4cout <<"==============================================================="<< G4endl;
G4cout <<"PARTICLES NAMES \n" <<G4endl;

G4cout << "Prymary \n"<<G4endl;

G4cout << "PARTICLES ON LAYER A: " <<  G4endl;

if (particles_names_A.empty()) {
    G4cout << "**No particles pierced Layer A in this event. \n" << G4endl;
} else {
    for (auto p_name : particles_names_A) {
        G4cout << p_name << ", \n";
        man->FillNtupleSColumn(1, 170, p_name);
    }}


G4cout << "PARTICLES ON LAYER B: " <<  G4endl;

if (particles_names_B.empty()) {
   G4cout << "**No particles pierced Layer B in this event. \n" << G4endl;
} else {
    for (auto p_name : particles_names_B) {
        G4cout << p_name << ", \n";
        man->FillNtupleSColumn(1, 171, p_name);
    }}


//------------------------------------------------------------------------------------------------
    G4cout << "\nSecondary \n"<<G4endl;
    //G4cout << G4endl;
    G4cout << "PARTICLES ON LAYER A: " <<  G4endl;
    
    if (particles_names_A_s.empty()) {
        G4cout << "**No particles pierced Layer A in this event. \n" << G4endl;
    } else {
        for (auto p_name : particles_names_A_s) {
            G4cout << p_name << ", \n";
          man->FillNtupleSColumn(2, 2, p_name);
        }}
    
    
    G4cout << "PARTICLES ON LAYER B: " <<  G4endl;
    
    if (particles_names_B_s.empty()) {
       G4cout << "**No particles pierced Layer B in this event. \n" << G4endl;
    } else {
        for (auto p_name : particles_names_B_s) {
            G4cout << p_name << ", \n";
            man->FillNtupleSColumn(2, 3, p_name);
        }}
    G4cout <<"\n" <<G4endl;
    



//========================= POSITIONS ============================
G4cout << "------------------------ POSITIONS ------------------------------------" << G4endl;

G4cout << "------------------------ MUONS/PIONS ------------------------------------" << G4endl;
G4cout << G4endl;

G4cout <<"LAYER A | POSITION X : " << G4endl;
for(const auto& pos_x_A :pos_layer_A_x){
        G4cout << pos_x_A << " cm, ";
        man->FillNtupleDColumn(1, 181, pos_x_A);

}
G4cout << "" << G4endl;
G4cout <<"LAYER A | POSITION Y: " << G4endl;
for(const auto& pos_y_A :pos_layer_A_y){
        G4cout << pos_y_A << " cm, ";
        man->FillNtupleDColumn(1, 182, pos_y_A);
}
G4cout << "" << G4endl;
G4cout <<"LAYER A | POSITION Z: " << G4endl;
for(const auto& pos_z_A :pos_layer_A_z){
        G4cout << pos_z_A << " cm, ";
        man->FillNtupleDColumn(1, 183, pos_z_A);
}
G4cout << "" << G4endl;
G4cout << "" << G4endl;

G4cout <<"LAYER B | POSITION X: "<< G4endl;
for(const auto& pos_x_B :pos_layer_B_x){
        G4cout << pos_x_B << " cm, ";
        man->FillNtupleDColumn(1, 184, pos_x_B);
}
G4cout << "" << G4endl;
G4cout <<"LAYER B | POSITION Y: " << G4endl;
for(const auto& pos_y_B :pos_layer_B_y){
        G4cout << pos_y_B << " cm, ";
        man->FillNtupleDColumn(1, 185, pos_y_B);
}
G4cout << "" << G4endl;
G4cout <<"LAYER B | POSITION Z: " << G4endl;
for(const auto& pos_z_B :pos_layer_B_z){
        G4cout << pos_z_B << " cm, ";
        man->FillNtupleDColumn(1, 186, pos_z_B);
}

G4cout << "\n" << G4endl;


G4cout << "------------------------ SECONDARY ------------------------------------" << G4endl;
G4cout << G4endl;

G4cout <<"LAYER A | POSITION X : " << G4endl;
for(const auto& pos_x_A :pos_layer_A_x_s){
        G4cout << pos_x_A << " cm, ";
        man->FillNtupleDColumn(2, 4, pos_x_A);

}
G4cout << "" << G4endl;
G4cout <<"LAYER A | POSITION Y: " << G4endl;
for(const auto& pos_y_A :pos_layer_A_y_s){
        G4cout << pos_y_A << " cm, ";
        man->FillNtupleDColumn(2, 5, pos_y_A);
}
G4cout << "" << G4endl;
G4cout <<"LAYER A | POSITION Z: " << G4endl;
for(const auto& pos_z_A :pos_layer_A_z_s){
        G4cout << pos_z_A << " cm, ";
        man->FillNtupleDColumn(2, 6, pos_z_A);
}
G4cout << "" << G4endl;
G4cout << "" << G4endl;

G4cout <<"LAYER B | POSITION X: "<< G4endl;
for(const auto& pos_x_B :pos_layer_B_x_s){
        G4cout << pos_x_B << " cm, ";
        man->FillNtupleDColumn(2, 7, pos_x_B);
}
G4cout << "" << G4endl;
G4cout <<"LAYER B | POSITION Y: " << G4endl;
for(const auto& pos_y_B :pos_layer_B_y_s){
        G4cout << pos_y_B << " cm, ";
        man->FillNtupleDColumn(2, 8, pos_y_B);
}
G4cout << "" << G4endl;
G4cout <<"LAYER B | POSITION Z: " << G4endl;
for(const auto& pos_z_B :pos_layer_B_z_s){
        G4cout << pos_z_B << " cm, ";
       man->FillNtupleDColumn(2, 9, pos_z_B);
}

G4cout << "\n" << G4endl;
G4cout <<"===============================================================" << G4endl;




//-----------------  ANGLE  -----------------
//if the particle just pass layer A

   G4ThreeVector pos_vertex  (2., 301.56, 2.);
G4cout <<"Vector Interaction point (V_p): (2, 305.56, 2) cm " << G4endl;
G4cout<< "" <<G4endl;


if (!pos_layer_A_x.empty() && !pos_layer_A_y.empty() && !pos_layer_A_z.empty()) {

        G4double first_pos_x_a = pos_layer_A_x.front();
        G4double first_pos_y_a = pos_layer_A_y.front();
        G4double first_pos_z_a = pos_layer_A_z.front();
     
        G4ThreeVector pos_on_A (first_pos_x_a, first_pos_y_a, first_pos_z_a);
        

        // Print the vector for debugging
        G4cout << "LAYER A | First position (V_r): ("
               << pos_on_A.x() << ", " << pos_on_A.y() << ", " << pos_on_A.z() << ") cm" << G4endl;
        
        G4cout <<""<<G4endl;
        

        G4ThreeVector sustraction_a =  pos_on_A - pos_vertex ;
        G4double Magnitude_sustraction_a = sustraction_a.mag();

        G4cout << "LAYER A | vector with the direction (V_r - V_p): ("
               << sustraction_a.x() << ", " << sustraction_a.y() << ", " << sustraction_a.z() << ") cm" << G4endl;
        
        G4cout <<""<<G4endl;


         G4ThreeVector unit_sust_a = sustraction_a.unit();
        G4cout << "LAYER A | UNIT (V_r - V_p) : ("
               << unit_sust_a.x() << ", " << unit_sust_a.y() << ", " << unit_sust_a.z() << ") cm" << G4endl;
        
         G4cout <<""<<G4endl;


        G4ThreeVector unit_y(0., -1., 0.);
        

         G4double angle_a = std::acos(sustraction_a.unit().dot(unit_y));
        //G4double angle_a = std::acos(first_pos_y_a/Magnitude_sustraction_a);
        G4double angle_a_d = angle_a * (180.0/ CLHEP::pi);


         G4cout <<""<<G4endl;
        G4cout <<"LAYER A | Magnitude (V_r - V_p): "<<Magnitude_sustraction_a <<G4endl;
        /*G4cout <<""<<G4endl;
        G4cout <<"LAYER A | Dispersion angle (radians) respect to y:: " << angle_a << " rad"<< G4endl;*/
        G4cout <<""<<G4endl;
        G4cout <<"LAYER A | Dispersion angle (degrees) respect to y: " << angle_a_d <<" °"<< G4endl;
        G4cout <<""<<G4endl;
       

        man->FillNtupleDColumn(1,189,angle_a);
        man->FillNtupleDColumn(1,187,angle_a_d);

    

    } else {
            G4cout << "No positions recorded in Layer A for this event." << G4endl;
   
    }
    G4cout << "\n" << G4endl;
   
//------------------------------------------------------------------------------------
G4cout <<"------------------------------------------------------------" << G4endl;

  if (!pos_layer_B_x.empty() && !pos_layer_B_y.empty() && !pos_layer_B_z.empty()) {

        G4double first_pos_x_b = pos_layer_B_x.front();
        G4double first_pos_y_b = pos_layer_B_y.front();
        G4double first_pos_z_b = pos_layer_B_z.front();
       
        G4ThreeVector pos_on_B (first_pos_x_b, first_pos_y_b, first_pos_z_b);


        // Print the vector for debugging
        G4cout << "LAYER B | First position (V_r) : ("
               << pos_on_B.x() << ", " << pos_on_B.y() << ", " << pos_on_B.z() << ") cm" << G4endl;

        G4cout <<""<<G4endl;
        

        G4ThreeVector sustraction_b =  pos_on_B - pos_vertex ;
        G4double Magnitude_sustraction_b = sustraction_b.mag();

        G4cout << "LAYER B | vector with the direction (V_r - V_p) : ("
               << sustraction_b.x() << ", " << sustraction_b.y() << ", " << sustraction_b.z() << ") cm" << G4endl;
        
        G4cout <<""<<G4endl;


        G4ThreeVector unit_sust_b = sustraction_b.unit();
        G4cout << "LAYER B | UNIT (V_r - V_p) : ("
               << unit_sust_b.x() << ", " << unit_sust_b.y() << ", " << unit_sust_b.z() << ") cm" << G4endl;
        
         G4cout <<""<<G4endl;


        G4ThreeVector unit_y(0., -1., 0.);
        

         G4double angle_b = std::acos(sustraction_b.unit().dot(unit_y));
        //G4double angle_a = std::acos(first_pos_y_a/Magnitude_sustraction_a);
        G4double angle_b_d = angle_b * (180.0/ CLHEP::pi);
        
         G4cout <<""<<G4endl;
        G4cout <<"LAYER B | Magnitude (V_r - V_p): "<<Magnitude_sustraction_b <<G4endl;

        /*G4cout <<""<<G4endl;
        G4cout << "LAYER B | Dispersion angle (radians): " << angle_b <<" rad"<< G4endl;*/

        G4cout <<""<<G4endl;
        G4cout << "LAYER B | Dispersion angle (degrees) respect to y: " << angle_b_d <<" °"<< G4endl;

        
        man->FillNtupleDColumn(1,190,angle_b);
        man->FillNtupleDColumn(1,188,angle_b_d);
        
    } else {
            G4cout << "No positions recorded in Layer B for this event." << G4endl;
   
    }  

G4cout<<"\n"<<G4endl;


man->AddNtupleRow(1);
man->AddNtupleRow(2);


}



