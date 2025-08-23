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


//-------------------- DETECTED PHOTONS --------------------

//--------------------- JUST MUONS/PIONS --------------------------------

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



//--------------------- ALL --------------------------------

/*void Add_DetectedPhotons_event_A_SiPMs_all (G4int sipmID_a_all)
{
    if (sipmID_a_all >= 0 && sipmID_a_all < 20 )
    {
        photonHits_event_A_all[sipmID_a_all]++;
    }
}
std::vector<G4int> GetPhotonHits_A_all() const{return photonHits_event_A_all;}


void Add_DetectedPhotons_event_B_SiPMs_all (G4int sipmID_b_all)
{
    if (sipmID_b_all >= 0 && sipmID_b_all < 20 )
    {
        photonHits_event_B_all[sipmID_b_all]++;
    }
}
std::vector<G4int> GetPhotonHits_B_all() const{return photonHits_event_B_all;}
*/


//--------------------- JUST SECONDARIES --------------------------------

void Add_DetectedPhotons_event_A_SiPMs_s (G4int sipmID_a_s)
{
    if (sipmID_a_s >= 0 && sipmID_a_s < 20 )
    {
        photonHits_event_A_s[sipmID_a_s]++;
    }
}
std::vector<G4int> GetPhotonHits_A_s() const{return photonHits_event_A_s;}


void Add_DetectedPhotons_event_B_SiPMs_s (G4int sipmID_b_s)
{
    if (sipmID_b_s >= 0 && sipmID_b_s < 20 )
    {
        photonHits_event_B_s[sipmID_b_s]++;
    }
}
std::vector<G4int> GetPhotonHits_B_s() const{return photonHits_event_B_s;}


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



//-------------------- TOTAL EDEP  --------------------

//---------- JUST MUONS/PIONS ---------------

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


//-----------------------------------------------------------
void AddEdepAbs(G4double edep_abs){fEdep_abs += edep_abs;}
//-----------------------------------------------------------

//---------- ALL PARTICLES ---------------
/*
void AddEdepA_all(G4int E_A_all, G4double edep_A_all)
{ 
    if (E_A_all >= 0 && E_A_all < fEdepA_all.size()) 
    {
        fEdepA_all[E_A_all] += edep_A_all;
    }
}
std::vector<G4double> GetEdepA_all() const { return fEdepA_all; }


void AddEdepB_all(G4int E_B_all, G4double edep_B_all)
{ 
    if (E_B_all >= 0 && E_B_all < fEdepB_all.size()) 
    {
        fEdepB_all[E_B_all] += edep_B_all;
    }
}
std::vector<G4double> GetEdepB_all() const { return fEdepB_all; }
*/


//---------- JUST SECONDARIES ---------------

void AddEdepA_s(G4int E_A_s, G4double edep_A_s)
{ 
    if (E_A_s >= 0 && E_A_s < fEdepA_s.size()) 
    {
        fEdepA_s[E_A_s] += edep_A_s;
    }
}
std::vector<G4double> GetEdepA_s() const { return fEdepA_s; }


void AddEdepB_s(G4int E_B_s, G4double edep_B_s)
{ 
    if (E_B_s >= 0 && E_B_s < fEdepB_s.size()) 
    {
        fEdepB_s[E_B_s] += edep_B_s;
    }
}
std::vector<G4double> GetEdepB_s() const { return fEdepB_s; }





//----------------------- dE/dx ---------------------------------


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



//void AdddEdx_abs(G4double dedx_abs){fdEdx_abs += dedx_abs;}




//------------------------- GENERATED PHOTONS --------------------------------

//------------------- JUST MUONS/PIONS -----------------------------------------------------
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



//------------------- ALL -----------------------------------------------------
/*void AddPhotonG_UsingEdep_A_all(G4int PhotonGen_a_all, G4double generated_photons_A_all) 
 {
    if (PhotonGen_a_all >= 0 && PhotonGen_a_all < fGenerated_photons_A_all.size())
    {
        fGenerated_photons_A_all[PhotonGen_a_all] += generated_photons_A_all;
    }
 }
 std::vector<G4int> GetPhotonCount_Edep_A_all() const { return fGenerated_photons_A_all; }


void AddPhotonG_UsingEdep_B_all(G4int PhotonGen_b_all, G4double generated_photons_B_all)
 {
    if (PhotonGen_b_all >= 0 && PhotonGen_b_all <fGenerated_photons_B_all.size())
    {
        fGenerated_photons_B_all[PhotonGen_b_all] += generated_photons_B_all;
    }
 }
 std::vector<G4int> GetPhotonCount_Edep_B_all() const { return fGenerated_photons_B_all; }*/



 //------------------- JUST SECONDARIES -----------------------------------------------------
void AddPhotonG_UsingEdep_A_s(G4int PhotonGen_a_s, G4double generated_photons_A_s) 
{
   if (PhotonGen_a_s >= 0 && PhotonGen_a_s < fGenerated_photons_A_s.size())
   {
       fGenerated_photons_A_s[PhotonGen_a_s] += generated_photons_A_s;
   }
}
std::vector<G4int> GetPhotonCount_Edep_A_s() const { return fGenerated_photons_A_s; }


void AddPhotonG_UsingEdep_B_s(G4int PhotonGen_b_s, G4double generated_photons_B_s)
{
   if (PhotonGen_b_s >= 0 && PhotonGen_b_s <fGenerated_photons_B_s.size())
   {
       fGenerated_photons_B_s[PhotonGen_b_s] += generated_photons_B_s;
   }
}
std::vector<G4int> GetPhotonCount_Edep_B_s() const { return fGenerated_photons_B_s; }




//-------------------------- BAR ID -----------------------------
//-------------- JUST MUONS/PION --------------------------------------------------------------------------------------------- 
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


//-------------- ALL ---------------------------------------------------------------------------------------------  
void AddTraversedBar_A_all (G4int barA_all){

    if (std::find(traversed_Bars_A_all.begin(), traversed_Bars_A_all.end(), barA_all) == traversed_Bars_A_all.end()) {  
      traversed_Bars_A_all.push_back(barA_all);
    }
}
std::vector<G4int> GetTraversedBars_A_all() const {return traversed_Bars_A_all;}


void AddTraversedBar_B_all (G4int barB_all){

    if (std::find(traversed_Bars_B_all.begin(), traversed_Bars_B_all.end(), barB_all) == traversed_Bars_B_all.end()) {
       traversed_Bars_B_all.push_back(barB_all);
    }
}
std::vector<G4int> GetTraversedBars_B_all() const {return traversed_Bars_B_all;}


//-------------- JUST SECONDARIES --------------------------------------------------------------------------------------------- 
void AddTraversedBar_A_s (G4int barA_s){

    if (std::find(traversed_Bars_A_s.begin(), traversed_Bars_A_s.end(), barA_s) == traversed_Bars_A_s.end()) {  
      traversed_Bars_A_s.push_back(barA_s);
    }
}
std::vector<G4int> GetTraversedBars_A_s() const {return traversed_Bars_A_s;}


void AddTraversedBar_B_s (G4int barB_s){

    if (std::find(traversed_Bars_B_s.begin(), traversed_Bars_B_s.end(), barB_s) == traversed_Bars_B_s.end()) {
       traversed_Bars_B_s.push_back(barB_s);
    }
}
std::vector<G4int> GetTraversedBars_B_s() const {return traversed_Bars_B_s;}





//---------------------------PARTICLE NAME ----------------------------


void Particle_Name_Pierced_Layer_A(G4String name_a){
    particles_names_A.push_back(name_a);
}

vector<G4String> Get_particle_names_A() const {return particles_names_A;}



void Particle_Name_Pierced_Layer_B(G4String name_b){
    particles_names_B.push_back(name_b);
}

vector<G4String> Get_particle_names_B() const {return particles_names_B;}


//--------------- JUST SECONDARIES ------------------------
void Particle_Name_Pierced_Layer_A_s(G4String name_a_s){
    particles_names_A_s.push_back(name_a_s);
}

vector<G4String> Get_particle_names_A_s() const {return particles_names_A_s;}



void Particle_Name_Pierced_Layer_B_s(G4String name_b_s){
    particles_names_B_s.push_back(name_b_s);
}

vector<G4String> Get_particle_names_B_s() const {return particles_names_B_s;}





//---------------------------------PARTICLE POSITION --------------------------------------------------

//-------------------- JUST MUONS/PIONS ---------------------------

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



//-------------------- ALL ---------------------------
//-------------------- LAYER A --------------------------
/*void Add_Positions_Layer_A_x_all(G4double pos_xa_all){
    pos_layer_A_x_all.push_back(pos_xa_all);
}
vector<G4double> Get_pos_x_a_all() const {return pos_layer_A_x_all;}


void Add_Positions_Layer_A_y_all(G4double pos_ya_all){
    pos_layer_A_y_all.push_back(pos_ya_all);
}
vector<G4double> Get_pos_y_a_all() const {return pos_layer_A_y_all;}


void Add_Positions_Layer_A_z_all(G4double pos_za_all){
    pos_layer_A_z_all.push_back(pos_za_all);
}
vector<G4double> Get_pos_z_a_all() const {return pos_layer_A_z_all;}



//-------------------- LAYER B --------------------------
void Add_Positions_Layer_B_x_all(G4double pos_xb_all){
    pos_layer_B_x_all.push_back(pos_xb_all);
}
vector<G4double> Get_pos_x_b_all() const {return pos_layer_B_x_all;}


void Add_Positions_Layer_B_y_all(G4double pos_yb_all){
    pos_layer_B_y_all.push_back(pos_yb_all);
}
vector<G4double> Get_pos_y_b_all() const {return pos_layer_B_y_all;}


void Add_Positions_Layer_B_z_all(G4double pos_zb_all){
    pos_layer_B_z_all.push_back(pos_zb_all);
}
vector<G4double> Get_pos_z_b_all() const {return pos_layer_B_z_all;}*/




//-------------------- JUST SECONDARIES ---------------------------
//-------------------- LAYER A --------------------------
void Add_Positions_Layer_A_x_s(G4double pos_xa_s){
    pos_layer_A_x_s.push_back(pos_xa_s);
}
vector<G4double> Get_pos_x_a_s() const {return pos_layer_A_x_s;}


void Add_Positions_Layer_A_y_s(G4double pos_ya_s){
    pos_layer_A_y_s.push_back(pos_ya_s);
}
vector<G4double> Get_pos_y_a_s() const {return pos_layer_A_y_s;}


void Add_Positions_Layer_A_z_s(G4double pos_za_s){
    pos_layer_A_z_s.push_back(pos_za_s);
}
vector<G4double> Get_pos_z_a_s() const {return pos_layer_A_z_s;}





//-------------------- LAYER B --------------------------
void Add_Positions_Layer_B_x_s(G4double pos_xb_s){
    pos_layer_B_x_s.push_back(pos_xb_s);
}
vector<G4double> Get_pos_x_b_s() const {return pos_layer_B_x_s;}


void Add_Positions_Layer_B_y_s(G4double pos_yb_s){
    pos_layer_B_y_s.push_back(pos_yb_s);
}
vector<G4double> Get_pos_y_b_s() const {return pos_layer_B_y_s;}


void Add_Positions_Layer_B_z_s(G4double pos_zb_s){
    pos_layer_B_z_s.push_back(pos_zb_s);
}
vector<G4double> Get_pos_z_b_s() const {return pos_layer_B_z_s;}


//---------------------------------------------------------


private:


std::vector<G4int> photonHits_event_A;
std::vector<G4int> photonHits_event_B;

std::vector<G4int> photonHits_event_A_all;
std::vector<G4int> photonHits_event_B_all;

std::vector<G4int> photonHits_event_A_s;
std::vector<G4int> photonHits_event_B_s;


std::vector<G4double> localTimes;
 

std::vector<G4double> fEdepA;
std::vector<G4double> fEdepB;

std::vector<G4double> fEdepA_all;
std::vector<G4double> fEdepB_all;

std::vector<G4double> fEdepA_s;
std::vector<G4double> fEdepB_s;


std::vector<G4double> fTotaldEdx_A;
std::vector<G4double> fTotaldEdx_B;


std::vector<G4int> fGenerated_photons_A;
std::vector<G4int> fGenerated_photons_B;

std::vector<G4int> fGenerated_photons_A_all;
std::vector<G4int> fGenerated_photons_B_all;

std::vector<G4int> fGenerated_photons_A_s;
std::vector<G4int> fGenerated_photons_B_s;


std::vector<G4int> traversed_Bars_A; 
std::vector<G4int> traversed_Bars_B; 

std::vector<G4int> traversed_Bars_A_all;
std::vector<G4int> traversed_Bars_B_all;

std::vector<G4int> traversed_Bars_A_s;
std::vector<G4int> traversed_Bars_B_s;


vector<G4String> particles_names_A;
vector<G4String> particles_names_B;

vector<G4String> particles_names_A_s;
vector<G4String> particles_names_B_s;


G4double TOTAL_Edep;
G4double TOTAL_dEdx;

G4double fEdep_abs;
G4double fdEdx_abs;

G4int TOTAL_Detected_photons;
G4double TOTAL_Generated_photons;

G4double total_edep_A;
G4double total_edep_B;

G4double TOTAL_Edep_all;
G4double TOTAL_Edep_s;

G4int TOTAL_Detected_photons_all;
G4int TOTAL_Detected_photons_s;

G4double TOTAL_Generated_photons_all;
G4double TOTAL_Generated_photons_s;


vector<G4double> pos_layer_A_x;
vector<G4double> pos_layer_A_y;
vector<G4double> pos_layer_A_z;

vector<G4double> pos_layer_B_x;
vector<G4double> pos_layer_B_y;
vector<G4double> pos_layer_B_z;

vector<G4double> pos_layer_A_x_all;
vector<G4double> pos_layer_A_y_all;
vector<G4double> pos_layer_A_z_all;

vector<G4double> pos_layer_B_x_all;
vector<G4double> pos_layer_B_y_all;
vector<G4double> pos_layer_B_z_all;

vector<G4double> pos_layer_A_x_s;
vector<G4double> pos_layer_A_y_s;
vector<G4double> pos_layer_A_z_s;

vector<G4double> pos_layer_B_x_s;
vector<G4double> pos_layer_B_y_s;
vector<G4double> pos_layer_B_z_s;

 G4int muonCount;

 G4bool Hit_particle_passed_two_layers = false;
 

 G4int Sumcopies;



};

#endif



