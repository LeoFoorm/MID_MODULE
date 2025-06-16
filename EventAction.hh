//   EVENT ACTION HEADER

#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "RunAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include <cmath>
#include <vector>

using namespace std;

class EventAction : public G4UserEventAction
{
public:

 EventAction(RunAction*);
 ~EventAction();

 
 virtual void BeginOfEventAction(const G4Event*);
 virtual void EndOfEventAction(const G4Event*);



void Add_DetectedPhotons_event_A_SiPMs (G4int sipmID_a)
{
    if (sipmID_a >= 0 && sipmID_a < 20 )
    {
        photonHits_event_A[sipmID_a]++;
    }
}
std::vector<G4int> GetPhotonHits_A() const{return photonHits_event_A;}


void Add_DetectedPhotons_event_B_SiPMs (G4int sipmID_b)
{
    if (sipmID_b >= 0 && sipmID_b < 20 )
    {
        photonHits_event_B[sipmID_b]++;
    }
}
std::vector<G4int> GetPhotonHits_B() const{return photonHits_event_B;}
//---------------------------------------------------------
//void AddLocalTime(G4int sipmID, G4double ltime) 
//{
 //   if (sipmID >= 0 && sipmID < 40) 
  //  {
  //      localTimes[sipmID] += ltime;
  //  }
//}
// std::vector<G4double> GetLocalTimes() const {return localTimes;
//---------------------------------------------------------


void AddEdepA(G4int E_A, G4double edep_A)
{ 
    if (E_A >= 0 && E_A < fEdepA.size()) 
    {
        fEdepA[E_A] += edep_A;
    }
}
std::vector<G4double> GetEdepA() const { return fEdepA; }


void AddEdepB(G4int E_B, G4double edep_B)
{ 
    if (E_B >= 0 && E_B < fEdepB.size()) 
    {
        fEdepB[E_B] += edep_B;
    }
}
std::vector<G4double> GetEdepB() const { return fEdepB; }


//---------------------------------------------------------


void AccumulatedEdx_A(G4int dEdx_a, G4double dEdxStep_A) 
{
    if (dEdx_a >= 0 && dEdx_a < fTotaldEdx_A.size() )
    {
         fTotaldEdx_A[dEdx_a] += dEdxStep_A;
    }
}
std::vector<G4double> GetdEdx_A() const { return fTotaldEdx_A; }


void AccumulatedEdx_B(G4int dEdx_b, G4double dEdxStep_B) 
{
    if (dEdx_b >= 0 && dEdx_b < fTotaldEdx_B.size() )
    {
         fTotaldEdx_B[dEdx_b] += dEdxStep_B;
    }
}
std::vector<G4double> GetdEdx_B() const { return fTotaldEdx_B; }


//---------------------------------------------------------

void AddPhotonG_UsingEdep_A(G4int PhotonGen_a, G4double generated_photons_A) 
 {
    if (PhotonGen_a >= 0 && PhotonGen_a < fGenerated_photons_A.size())
    {
        fGenerated_photons_A[PhotonGen_a] += generated_photons_A;
    }
 }
 std::vector<G4int> GetPhotonCount_Edep_A() const { return fGenerated_photons_A; }


void AddPhotonG_UsingEdep_B(G4int PhotonGen_b, G4double generated_photons_B)
 {
    if (PhotonGen_b >= 0 && PhotonGen_b <fGenerated_photons_B.size())
    {
        fGenerated_photons_B[PhotonGen_b] += generated_photons_B;
    }
 }
 std::vector<G4int> GetPhotonCount_Edep_B() const { return fGenerated_photons_B; }

//---------------------------------------------------------

void AddTraversedBar_A (G4int barA){

        if (std::find(traversed_Bars_A.begin(), traversed_Bars_A.end(), barA) == traversed_Bars_A.end()) {  
          traversed_Bars_A.push_back(barA);
        }
}
std::vector<G4int> GetTraversedBars_A() const {return traversed_Bars_A;}


void AddTraversedBar_B (G4int barB){
    
        if (std::find(traversed_Bars_B.begin(), traversed_Bars_B.end(), barB) == traversed_Bars_B.end()) {
           traversed_Bars_B.push_back(barB);
        }
}
std::vector<G4int> GetTraversedBars_B() const {return traversed_Bars_B;}

//---------------------------------------------------------
void Particle_Name_Pierced_Layer_A(G4String name_a){
    particles_names_A.push_back(name_a);
}

vector<G4String> Get_particle_names_A() const {return particles_names_A;}



void Particle_Name_Pierced_Layer_B(G4String name_b){
    particles_names_B.push_back(name_b);
}

vector<G4String> Get_particle_names_B() const {return particles_names_B;}


//-------------------- LAYER A --------------------------
void Add_Positions_Layer_A_x(G4double pos_xa){
    pos_layer_A_x.push_back(pos_xa);
}
vector<G4double> Get_pos_x_a() const {return pos_layer_A_x;}


void Add_Positions_Layer_A_y(G4double pos_ya){
    pos_layer_A_y.push_back(pos_ya);
}
vector<G4double> Get_pos_y_a() const {return pos_layer_A_y;}


void Add_Positions_Layer_A_z(G4double pos_za){
    pos_layer_A_z.push_back(pos_za);
}
vector<G4double> Get_pos_z_a() const {return pos_layer_A_z;}


//-------------------- LAYER B --------------------------
void Add_Positions_Layer_B_x(G4double pos_xb){
    pos_layer_B_x.push_back(pos_xb);
}
vector<G4double> Get_pos_x_b() const {return pos_layer_B_x;}


void Add_Positions_Layer_B_y(G4double pos_yb){
    pos_layer_B_y.push_back(pos_yb);
}
vector<G4double> Get_pos_y_b() const {return pos_layer_B_y;}


void Add_Positions_Layer_B_z(G4double pos_zb){
    pos_layer_B_z.push_back(pos_zb);
}
vector<G4double> Get_pos_z_b() const {return pos_layer_B_z;}

//---------------------------------------------------------


private:

std::vector<G4int> photonHits_event_A;
std::vector<G4int> photonHits_event_B;
std::vector<G4double> localTimes;
 
std::vector<G4double> fEdepA;
std::vector<G4double> fEdepB;

std::vector<G4double> fTotaldEdx_A;
std::vector<G4double> fTotaldEdx_B;

std::vector<G4int> fGenerated_photons_A;
std::vector<G4int> fGenerated_photons_B;

std::vector<G4int> traversed_Bars_A; 
std::vector<G4int> traversed_Bars_B; 

vector<G4String> particles_names_A;
vector<G4String> particles_names_B;

G4double TOTAL_Edep;
G4double TOTAL_dEdx;

G4int TOTAL_Detected_photons;
G4double TOTAL_Generated_photons;

G4double total_edep_A;
G4double total_edep_B;

vector<G4double> pos_layer_A_x;
vector<G4double> pos_layer_A_y;
vector<G4double> pos_layer_A_z;

vector<G4double> pos_layer_B_x;
vector<G4double> pos_layer_B_y;
vector<G4double> pos_layer_B_z;
 

 G4int muonCount;

 G4bool Hit_particle_passed_two_layers = false;
 

 G4int Sumcopies;



};

#endif



