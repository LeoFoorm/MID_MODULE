//  DETECTOR CONSTRCTION SOURCE


#include "DetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>
#include "G4UserLimits.hh"  

#include "FieldSetUp.hh"

#include "G4AutoDelete.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
//#include "G4VisAttributes.hh"

using namespace std;

//: fVisAttributes()
DetectorConstruction::DetectorConstruction()
{
  fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");
  fMessenger->DeclareProperty("MID_Module", MID_Module, "Construct MID module detector");
  fMessenger->DeclareProperty("distance_modules", distance_modules, "The distance between both modules");
  
  DefineMaterials();

  env_sizeX = 2*m;
  env_sizeY = 3.5*m;
  env_sizeZ = 2*m;

  distance_modules = 20*cm + 1.04*cm;

  MID_Module = true; 
}


DetectorConstruction::~DetectorConstruction()
{/*for (auto visAttributes: fVisAttributes)
  {
    delete visAttributes;
  }*/}


void DetectorConstruction::DefineMaterials()
{
  
  std::vector<G4double> wavelength = {499.83,496.62,491.92,487.22,482.51,477.81,473.10,468.40,463.69,458.99,454.28,449.58,445.30,441.45,438.03,434.18,429.69,425.20,417.03,415.36,414.08,413.22,412.53,411.60,410.66,409.80, 408.53,405.80,402.75,400.18,399.32,397.27,396.33,395.48,394.62,394.28,392.91,392.27,391.41,390.34,389.70,388.42,386.63,384.57,381.58,380.31};
  std::vector<G4double> lightOutput = {2.55,2.56,2.97,3.59,4.40,5.49,6.93,8.52,10.68,13.38,17.07,21.41,26.21,31.27,36.04,40.53,45.23,49.04,53.41,58.78,63.62,68.61,73.05,78.28,83.01,88.07,92.45,96.07,99.46,96.00,91.32,86.66,80.18,73.98,69.53,64.76,58.40,50.56,44.59,38.14,33.28,29.14,23.55,17.68,12.13,6.27,4.06};
  std::vector<G4double> energy;
  std::vector<G4double> RI;
  std::vector<G4double> fraction;
  std::vector<G4double> absSC;
  std::vector<G4double> rindexWorld;
  std::vector<G4double> reflectivity;
  std::vector<G4double> rindexmylar;

  G4double RefIndex=1.58;
  G4double AbsSC = 160.*cm;
  G4double RIWorld = 1.0;
  G4double Reflectivity = 0.9999;
  G4double Rindexmylar = 1.655;


  for (size_t i = 0; i < wavelength.size(); ++i) {

    G4double Energy = 1.239841939 * eV / (wavelength[i] / 1000);

    G4double normalizedLightOutput = lightOutput[i] / 100;

    energy.push_back(Energy);

    fraction.push_back(normalizedLightOutput);

    RI.push_back(RefIndex);

    absSC.push_back(AbsSC);

    rindexWorld.push_back(RIWorld);

    reflectivity.push_back(Reflectivity);

    rindexmylar.push_back(Rindexmylar);
    }
  
  G4int numberOfEntries = energy.size();

 // ======= REQUIRED DATA FOR WLS =======
std::vector<G4double> energy_test = {
    2.00 * eV, 2.03 * eV, 2.06 * eV, 2.09 * eV, 2.12 * eV, 2.15 * eV, 2.18 * eV,
    2.21 * eV, 2.24 * eV, 2.27 * eV, 2.30 * eV, 2.33 * eV, 2.36 * eV, 2.39 * eV,
    2.42 * eV, 2.45 * eV, 2.48 * eV, 2.51 * eV, 2.54 * eV, 2.57 * eV, 2.60 * eV,
    2.63 * eV, 2.66 * eV, 2.69 * eV, 2.72 * eV, 2.75 * eV, 2.78 * eV, 2.81 * eV,
    2.84 * eV, 2.87 * eV, 2.90 * eV, 2.93 * eV, 2.96 * eV, 2.99 * eV, 3.02 * eV,
    3.05 * eV, 3.08 * eV, 3.11 * eV, 3.14 * eV, 3.17 * eV, 3.20 * eV, 3.23 * eV,
    3.26 * eV, 3.29 * eV, 3.32 * eV, 3.35 * eV, 3.38 * eV, 3.41 * eV, 3.44 * eV,
    3.47 * eV};

  std::vector<G4double> energySmall = { 2.0 * eV, 3.47 * eV };

   std::vector<G4double> RIndexFiber = { 1.60, 1.60 };

  std::vector<G4double> AbsFiber = {
    5.40 * m, 5.40 * m, 5.40 * m, 5.40 * m, 5.40 * m, 4.60 * m, 4.60 * m,
    4.60 * m, 4.60 * m, 4.60 * m, 4.60 * m, 4.60 * m, 4.60 * m, 4.60 * m,
    4.00 * m, 4.00 * m, 4.00 * m, 3.60 * m, 3.60 * m, 3.60 * m, 3.60 * m,
    3.60 * m, 3.51 * m, 3.51 * m, 3.51 * m, 3.51 * m, 1.00 * m, 1.00 * m,   //This gives low number of photons
    1.00 * m, 1.00 * m, 1.00 * m, 1.00 * m, 1.00 * m, 1.00 * m, 1.00 * m,
    1.00 * m, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm,
    1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm, 1. * mm,
    1. * mm};

  std::vector<G4double> EmissionFiber = {
    0.05, 0.10, 0.30, 0.50, 0.75, 1.00, 1.50, 1.85, 2.30, 2.75,
    3.25, 3.80, 4.50, 5.20, 6.00, 7.00, 13.50, 14.70, 15.1, 17.00,
    16.9, 16.0, 7.8, 6.3, 4.1, 3.0, 2.0, 1.0, 1.0, 0.9,
    0.1, 1.00, 1.50, 1.00, 0.05, 0.00, 0.00, 0.00, 0.00, 0.00,
    0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};


 G4OpticalParameters::Instance()->SetScintFiniteRiseTime(true); 
 G4NistManager *nist = G4NistManager::Instance();

//======== cladding ======================
  G4String name,symbol;
  G4double z;

  C = new G4Element(name="Carbon" ,symbol="C" , z= 6., 12.01*g/mole);

  O = new G4Element(name="Oxygen" ,symbol="O" , z= 8., 16.00*g/mole);

  H = new G4Element(name="Hydrogen",symbol="H" , z= 1., 1.01*g/mole);

  cladding = new G4Material("PMMA", 1.19*g/cm3, 3);
  cladding->AddElement(C,5);
  cladding->AddElement(O,2);
  cladding->AddElement(H,8);

  //I will use this PhotonEnergy
   vector<G4double> RIndexCladding = {1.49, 1.49};
  std::vector<G4double> absClad = { 20.0 * m, 20.0 * m };


//===========================================

 worldMaterial = nist->FindOrBuildMaterial("G4_AIR");
 plastic = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
 mylarMaterial = nist->FindOrBuildMaterial("G4_MYLAR");
 steel = nist->FindOrBuildMaterial("G4_Fe");
 fiber_core = nist->FindOrBuildMaterial("G4_POLYSTYRENE");

 mirrorsurface = new G4OpticalSurface("mirrorsurface");
 mirrorsurface->SetType(dielectric_dielectric);
 mirrorsurface->SetFinish(polishedfrontpainted);
 mirrorsurface->SetModel(unified);

 G4MaterialPropertiesTable *mirror=new G4MaterialPropertiesTable();
 G4MaterialPropertiesTable *prop=new G4MaterialPropertiesTable();
 G4MaterialPropertiesTable *propworld=new G4MaterialPropertiesTable();
 G4MaterialPropertiesTable *propmylar=new G4MaterialPropertiesTable();
 G4MaterialPropertiesTable *propfiber=new G4MaterialPropertiesTable();
 G4MaterialPropertiesTable *propcladding=new G4MaterialPropertiesTable();

 

 propworld->AddProperty("RINDEX",energy, rindexWorld,numberOfEntries);
 prop->AddProperty("RINDEX",energy, RI,numberOfEntries);
 prop->AddProperty("SCINTILLATIONCOMPONENT1",energy,fraction,numberOfEntries);
 prop->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1.8*ns);
 prop->AddConstProperty("SCINTILLATIONRISETIME1", 0.7*ns); //decay time of the scintillator
 prop->AddConstProperty("SCINTILLATIONYIELD", 10.666666/keV);//amount of photons per (in this case) KeV        
 prop->AddConstProperty("RESOLUTIONSCALE", 1.);
 prop->AddProperty("ABSLENGTH",energy,absSC,numberOfEntries);
 mirror->AddProperty("REFLECTIVITY", energy, reflectivity);
 propmylar->AddProperty("RINDEX",energy, rindexmylar,numberOfEntries);

 propfiber->AddProperty("RINDEX", energySmall, RIndexFiber);
 propfiber->AddProperty("WLSABSLENGTH", energy_test, AbsFiber);
 propfiber->AddProperty("WLSCOMPONENT", energy_test, EmissionFiber );
 propfiber->AddConstProperty("WLSTIMECONSTANT", 0.5*ns);
 propcladding->AddProperty("RINDEX", energySmall, RIndexCladding);
 propcladding->AddProperty("ABSLENGTH", energySmall, absClad);


 G4double density = steel->GetDensity(); // Densidad en unidades de Geant4
        std::cout << "Material: " << steel->GetName() << std::endl;
        std::cout << "Densidad: " << density/ (kg/m3)  << " kg/m^3" << std::endl;


 worldMaterial->SetMaterialPropertiesTable(propworld);
 plastic->SetMaterialPropertiesTable(prop);
 mirrorsurface->SetMaterialPropertiesTable(mirror);
 mylarMaterial->SetMaterialPropertiesTable(propmylar);
 fiber_core->SetMaterialPropertiesTable(propfiber);
 cladding->SetMaterialPropertiesTable(propcladding);

}


void DetectorConstruction::ConstructMIDModule()
{
  //                     BAR 
  G4double bar_X = 2.5*cm;
  G4double bar_Y = 0.5*cm;
  G4double bar_Z = 50*cm;
  
  Solidbar = new G4Box("Solidbar", bar_X, bar_Y, bar_Z );


//                        SiPM 
  G4double sipm_X = 0.3*cm;
  G4double sipm_Y = 0.3*cm;
  G4double sipm_Z = 0.005*cm;
  
  Solidsipm = new G4Box("Solidsipm", sipm_X, sipm_Y, sipm_Z );


//                      WINDOW
  G4double window_x = 0.05*cm;
  G4double window_y = 0.15*cm;
  G4double window_z = 0.0005*cm; 
  window = new G4Box("solid_Hole", window_x, window_y, window_z);

  //the position is relative to the first volume 
  G4double wind_pos_x = -2.496*cm; //<-- -2.5
  G4double wind_pos_y = 0*cm;
  G4double wind_pos_z = 50.0005*cm; //<--
  G4ThreeVector window_pos(wind_pos_x, wind_pos_y, wind_pos_z);



//                        MYLAR
  G4double mylar_x = 2.551*cm;
  G4double mylar_y = 0.52*cm;
  G4double mylar_z = 50.001*cm;
 Solidmylar = new G4Box("Solidmylar", mylar_x, mylar_y, mylar_z);
 SolidInnermylar = new G4Box("SolidInnermylar", mylar_x-0.001*cm, mylar_y-0.001*cm, mylar_z-0.001*cm);
 G4SubtractionSolid* hollowMylarBox = new G4SubtractionSolid("HollowMylarBox", Solidmylar, SolidInnermylar);
 G4SubtractionSolid* Mylar_With_Hole = new G4SubtractionSolid("Mylar_With_Hole", hollowMylarBox, window, 0, window_pos);

 //Logicmylar = new G4LogicalVolume(hollowMylarBox, mylarMaterial, "Logicmylar");
 Logicmylar = new G4LogicalVolume(Mylar_With_Hole, mylarMaterial, "Logicmylar");

 G4LogicalSkinSurface *skin= new G4LogicalSkinSurface("skin", Logicmylar, mirrorsurface); 


//                      FIBER
  G4double innerRadius = 0.*cm;
  G4double outerRadius = 0.049*cm; // 1 mm diameter, 0.5 mm radius. Core 0.098 cm half core 0.049 cm 
  G4double hz = 50.*cm;
  G4double startAngle = 0.*deg;
  G4double spanningAngle = 360.*deg;

 Solid_fiber = new G4Tubs("FIBER", innerRadius, outerRadius, hz, startAngle, spanningAngle);


//                      CLADDING
  G4double innerR_clad = 0.049*cm;
  G4double outerR_clad = 0.05*cm; //, 0.5 mm radius. Core 0.098 cm half core 0.049 cm. Cladding 0.02mm
  G4double hz_clad = 50.*cm;
  G4double startAngle_clad = 0.*deg;
  G4double spanningAngle_clad = 360.*deg;

 Solid_cladding = new G4Tubs("CLADDING", innerR_clad, outerR_clad, hz_clad, startAngle_clad, spanningAngle_clad);

// ==========  Optical surface  (CORE-CLADDING) ========== 
op_surface_core_clad = new G4OpticalSurface("CoreCladSurface");
op_surface_core_clad->SetType(dielectric_dielectric); 
op_surface_core_clad->SetFinish(polished);
op_surface_core_clad->SetModel(glisur);
//G4LogicalBorderSurface* border_clad_core_A = new G4LogicalBorderSurface( "Border_clad_core_A", Physical_cladding_A, Physical_Fiber_A, op_surface_core_clad);


// ==========  Optical surface (CLADDING-BAR) ========== 
 op_surface_bar_clad = new G4OpticalSurface("BarCladSurface"); 
 op_surface_bar_clad->SetType(dielectric_dielectric); 
 op_surface_bar_clad->SetFinish(polished);
 op_surface_bar_clad->SetModel(glisur);
 //G4LogicalBorderSurface* border_clad_bar_A = new G4LogicalBorderSurface( "Border_clad_bar_A", Physical_cladding_A, Physical_MID_A, op_surface_bar_clad);



//             20 SCINTILLATION BARS A 

  for (G4int i = 0; i <20; i++)
  {

  Logicbar_A = new G4LogicalVolume(Solidbar, plastic, "Logicbar_A_"+std::to_string(i));
  LogicBars_A.push_back(Logicbar_A);
  fScoringVolumes_A.push_back(Logicbar_A);


  Physical_MID_A = new  G4PVPlacement(0, G4ThreeVector(-48.418 * cm + (5.102*i) * cm, 0, 0),
                                    Logicbar_A, "Physical_MID_A", LogicWorld, false, i, true);
  }


//             20 SiPM A 

 for (G4int j = 0; j<20; j++)
 {
  Logicsipm_A= new G4LogicalVolume(Solidsipm, worldMaterial, "Logicsipm_A_"+std::to_string(j));
  LogicSiPMs_A.push_back(Logicsipm_A);

  Physical_SiPM_MID_A = new  G4PVPlacement(0, G4ThreeVector(-50.718 * cm + (5.102*j) * cm, 0, 50.006*cm),
                                    Logicsipm_A, "Physical_SiPM_MID_A", LogicWorld, false, j, true);
 }


//             20 MYLAR A 
  for(G4int k = 0; k<20; k++)
  {
  Physical_Mylar_MID_A = new  G4PVPlacement(0, G4ThreeVector(-48.468 * cm + (5.102*k) * cm, 0, 0),
                                    Logicmylar, "Physical_Mylar_MID_A", LogicWorld, false, k, true);
  }

//            60 FIBERS and CLADDING A 

for (G4int l = 0; l < 20; l++)
 {
  Logic_Fiber_A= new G4LogicalVolume(Solid_fiber, fiber_core, "Logic_fiber_A_"+std::to_string(l));
  Logic_Fibers_A.push_back(Logic_Fiber_A);

  Physical_Fiber_A = new  G4PVPlacement(0, G4ThreeVector(-50.968 * cm + (5.102*l) * cm, 0, 0),
                                   Logic_Fiber_A, "Physical_Fiber_A_middle", LogicWorld, false, l, true);
  
  Logic_cladding_A= new G4LogicalVolume(Solid_cladding, cladding, "Logic_cladding_A_"+std::to_string(l));
  Logic_claddings_A.push_back(Logic_cladding_A);
                                 
  Physical_cladding_A = new  G4PVPlacement(0, G4ThreeVector(-50.968 * cm + (5.102*l) * cm, 0, 0),
                                                                    Logic_cladding_A, "Physical_cladding_A_middle", LogicWorld, false, l, true);

  G4LogicalBorderSurface* border_clad_core_A = new G4LogicalBorderSurface( "Border_clad_core_A", Physical_cladding_A, Physical_Fiber_A, op_surface_core_clad);                       
 }

 for (G4int l = 0; l < 20; l++)
 {
  Logic_Fiber_A= new G4LogicalVolume(Solid_fiber, fiber_core, "Logic_fiber_A_"+std::to_string(l));
  Logic_Fibers_A.push_back(Logic_Fiber_A);

  Physical_Fiber_A = new  G4PVPlacement(0, G4ThreeVector(-50.968 * cm + (5.102*l) * cm, 0.1 * cm, 0),
                                   Logic_Fiber_A, "Physical_Fiber_A_up", LogicWorld, false, l, true);

  Logic_cladding_A= new G4LogicalVolume(Solid_cladding, cladding, "Logic_cladding_A_"+std::to_string(l));
  Logic_claddings_A.push_back(Logic_cladding_A);

  Physical_cladding_A = new  G4PVPlacement(0, G4ThreeVector(-50.968 * cm + (5.102*l) * cm, 0.1 * cm, 0),
                                 Logic_cladding_A, "Physical_cladding_A_up", LogicWorld, false, l, true);
  
  G4LogicalBorderSurface* border_clad_core_A_up = new G4LogicalBorderSurface( "Border_clad_core_A_up", Physical_cladding_A, Physical_Fiber_A, op_surface_core_clad);
 }

 for (G4int l = 0; l < 20; l++)
 {
  Logic_Fiber_A= new G4LogicalVolume(Solid_fiber, fiber_core, "Logic_fiber_A_"+std::to_string(l));
  Logic_Fibers_A.push_back(Logic_Fiber_A);

  Physical_Fiber_A = new  G4PVPlacement(0, G4ThreeVector(-50.968 * cm + (5.102*l) * cm, - 0.1 * cm, 0),
                                   Logic_Fiber_A, "Physical_Fiber_A_down", LogicWorld, false, l, true);

  Logic_cladding_A= new G4LogicalVolume(Solid_cladding, cladding, "Logic_cladding_A_"+std::to_string(l));
  Logic_claddings_A.push_back(Logic_cladding_A);

  Physical_cladding_A = new  G4PVPlacement(0, G4ThreeVector(-50.968* cm + (5.102*l) * cm, - 0.1 * cm, 0),
                                 Logic_cladding_A, "Physical_cladding_A_down", LogicWorld, false, l, true);

  G4LogicalBorderSurface* border_clad_core_A_down = new G4LogicalBorderSurface( "Border_clad_core_A_down", Physical_cladding_A, Physical_Fiber_A, op_surface_core_clad);
 }

 //          60 CLADDING A

 /*for (G4int l = 0; l < 20; l++)
 {
  Logic_cladding_A= new G4LogicalVolume(Solid_cladding, cladding, "Logic_cladding_A_"+std::to_string(l));
  Logic_claddings_A.push_back(Logic_cladding_A);

  Physical_cladding_A = new  G4PVPlacement(0, G4ThreeVector(-50.968 * cm + (5.102*l) * cm, 0, 0),
                                   Logic_cladding_A, "Physical_cladding_A_middle", LogicWorld, false, l, true);
 }*/
 /*for (G4int l = 0; l < 20; l++)
 {
  Logic_cladding_A= new G4LogicalVolume(Solid_cladding, cladding, "Logic_cladding_A_"+std::to_string(l));
  Logic_claddings_A.push_back(Logic_cladding_A);

  Physical_cladding_A = new  G4PVPlacement(0, G4ThreeVector(-50.968 * cm + (5.102*l) * cm, 0.1 * cm, 0),
                                   Logic_cladding_A, "Physical_cladding_A_up", LogicWorld, false, l, true);
 }*/
 /*for (G4int l = 0; l < 20; l++)
 {
  Logic_cladding_A= new G4LogicalVolume(Solid_cladding, cladding, "Logic_cladding_A_"+std::to_string(l));
  Logic_claddings_A.push_back(Logic_cladding_A);

  Physical_cladding_A = new  G4PVPlacement(0, G4ThreeVector(-50.968* cm + (5.102*l) * cm, - 0.1 * cm, 0),
                                   Logic_cladding_A, "Physical_cladding_A_down", LogicWorld, false, l, true);
 }*/





// ====================  STEP LIMITS FOR FIBERS A ===============================
G4double maxStep = 0.1 * mm;
G4UserLimits* fiberStepLimit = new G4UserLimits(maxStep);
for (auto& fiberLogic : Logic_Fibers_A) {
    fiberLogic->SetUserLimits(fiberStepLimit);
}
// =============================================================================



//---------------- 20 SCINTILLATION BARS B  -----------------------------
  G4RotationMatrix* rotationY = new G4RotationMatrix(); 
  rotationY->rotateY(90*deg);

  for (G4int l = 0; l <20; l++)
  {
  Logicbar_B = new G4LogicalVolume(Solidbar, plastic, "Logicbar_B_"+std::to_string(l));
  LogicBars_B.push_back(Logicbar_B);
  fScoringVolumes_B.push_back(Logicbar_B);

  Physical_MID_B = new  G4PVPlacement(rotationY, G4ThreeVector( 0, distance_modules, -48.418 * cm + (5.102*l) * cm),
                                    Logicbar_B, "Physical_MID_B", LogicWorld, false, l+20, true);
  }


//             20 SiPM B 
 for (G4int m = 0; m<20; m++)
 {
  Logicsipm_B= new G4LogicalVolume(Solidsipm, worldMaterial, "Logicsipm_B_"+std::to_string(m));
  LogicSiPMs_B.push_back(Logicsipm_B);
  
  Physical_SiPM_MID_B = new  G4PVPlacement(rotationY, G4ThreeVector(-50.006*cm, distance_modules,  -50.718 * cm + (5.102*m) * cm),
                                    Logicsipm_B, "Physical_SiPM_MID_B", LogicWorld, false, m+20, true);
 }


//             20 MYLAR B  
  for(G4int n = 0; n<20; n++)
  {
  Physical_Mylar_MID_B = new  G4PVPlacement(rotationY, G4ThreeVector(0, distance_modules,-48.468 * cm + (5.102*n) * cm),
                                    Logicmylar, "Physical_Mylar_MID_B", LogicWorld, false, n+20, true);
  }

//            60 FIBERS B 

for (G4int l = 0; l < 20; l++)
 {
  Logic_Fiber_B= new G4LogicalVolume(Solid_fiber, fiber_core, "Logic_fiber_B_"+std::to_string(l));
  Logic_Fibers_B.push_back(Logic_Fiber_B);

  Physical_Fiber_B = new  G4PVPlacement(rotationY, G4ThreeVector(0, distance_modules, -50.968 * cm + (5.102*l) * cm),
                                   Logic_Fiber_B, "Physical_Fiber_B_middle", LogicWorld, false, l+20, true);


  Logic_cladding_B= new G4LogicalVolume(Solid_cladding, cladding, "Logic_cladding_B_"+std::to_string(l));
  Logic_claddings_B.push_back(Logic_cladding_B);

  Physical_cladding_B = new  G4PVPlacement(rotationY, G4ThreeVector(0, distance_modules,  -50.968 * cm + (5.102*l) * cm),
                                 Logic_cladding_B, "Physical_cladding_B_middle", LogicWorld, false, l+20, true);

G4LogicalBorderSurface* border_clad_bar_B = new G4LogicalBorderSurface( "Border_clad_bar_B", Physical_cladding_B, Physical_MID_B, op_surface_bar_clad);

 }

 for (G4int l = 0; l < 20; l++)
 {
  Logic_Fiber_B= new G4LogicalVolume(Solid_fiber, fiber_core, "Logic_fiber_B_"+std::to_string(l));
  Logic_Fibers_B.push_back(Logic_Fiber_B);

  Physical_Fiber_B = new  G4PVPlacement(rotationY, G4ThreeVector(0, distance_modules + 0.1 * cm,  -50.968 * cm + (5.102*l) * cm),
                                   Logic_Fiber_B, "Physical_Fiber_B_up", LogicWorld, false, l+20, true);

          
  Logic_cladding_B= new G4LogicalVolume(Solid_cladding, cladding, "Logic_cladding_B_"+std::to_string(l));
  Logic_claddings_B.push_back(Logic_cladding_B);

  Physical_cladding_B = new  G4PVPlacement(rotationY, G4ThreeVector(0, distance_modules + 0.1 * cm,  -50.968 * cm + (5.102*l) * cm),
                                   Logic_cladding_B, "Physical_cladding_B_up", LogicWorld, false, l+20, true);
                                  
G4LogicalBorderSurface* border_clad_bar_B_up = new G4LogicalBorderSurface( "Border_clad_bar_B_up", Physical_cladding_B, Physical_MID_B, op_surface_bar_clad);
 }

 for (G4int l = 0; l < 20; l++)
 {
  Logic_Fiber_B= new G4LogicalVolume(Solid_fiber, fiber_core, "Logic_fiber_B_"+std::to_string(l));
  Logic_Fibers_B.push_back(Logic_Fiber_B);

  Physical_Fiber_B = new  G4PVPlacement(rotationY, G4ThreeVector(0 ,distance_modules - 0.1 * cm,  -50.968 * cm + (5.102*l) * cm),
                                   Logic_Fiber_B, "Physical_Fiber_B_down", LogicWorld, false, l+20, true);
  
                                   
  Logic_cladding_B= new G4LogicalVolume(Solid_cladding, cladding, "Logic_cladding_B_"+std::to_string(l));
  Logic_claddings_B.push_back(Logic_cladding_B);

  Physical_cladding_B = new  G4PVPlacement(rotationY, G4ThreeVector(0,distance_modules  - 0.1 * cm,  -50.968 * cm + (5.102*l) * cm),
                                 Logic_cladding_B, "Physical_cladding_B_down", LogicWorld, false, l+20, true);

G4LogicalBorderSurface* border_clad_bar_B_down = new G4LogicalBorderSurface( "Border_clad_bar_B_down", Physical_cladding_B, Physical_MID_B, op_surface_bar_clad);
 }

 //          60 CLADDING B

 /*for (G4int l = 0; l < 20; l++)
 {
  Logic_cladding_B= new G4LogicalVolume(Solid_cladding, cladding, "Logic_cladding_B_"+std::to_string(l));
  Logic_claddings_B.push_back(Logic_cladding_B);

  Physical_cladding_B = new  G4PVPlacement(rotationY, G4ThreeVector(0, distance_modules,  -50.968 * cm + (5.102*l) * cm),
                                   Logic_cladding_B, "Physical_cladding_B_middle", LogicWorld, false, l+20, true);
 }
 
 for (G4int l = 0; l < 20; l++)
 {
  Logic_cladding_B= new G4LogicalVolume(Solid_cladding, cladding, "Logic_cladding_B_"+std::to_string(l));
  Logic_claddings_B.push_back(Logic_cladding_B);

  Physical_cladding_B = new  G4PVPlacement(rotationY, G4ThreeVector(0, distance_modules + 0.1 * cm,  -50.968 * cm + (5.102*l) * cm),
                                   Logic_cladding_B, "Physical_cladding_B_up", LogicWorld, false, l+20, true);
 }
 for (G4int l = 0; l < 20; l++)
 {
  Logic_cladding_B= new G4LogicalVolume(Solid_cladding, cladding, "Logic_cladding_B_"+std::to_string(l));
  Logic_claddings_B.push_back(Logic_cladding_B);

  Physical_cladding_B = new  G4PVPlacement(rotationY, G4ThreeVector(0,distance_modules  - 0.1 * cm,  -50.968 * cm + (5.102*l) * cm),
                                   Logic_cladding_B, "Physical_cladding_B_down", LogicWorld, false, l+20, true);
 }*/

//G4LogicalBorderSurface* border_clad_bar_B = new G4LogicalBorderSurface( "Border_clad_bar_B", Physical_cladding_B, Physical_MID_B, op_surface_bar_clad);
//G4LogicalBorderSurface* border_clad_core_B = new G4LogicalBorderSurface( "Border_clad_core_B", Physical_cladding_B, Physical_Fiber_B, op_surface_core_clad);

for (auto& fiberLogic : Logic_Fibers_B) 
{
  fiberLogic->SetUserLimits(fiberStepLimit);
}




     
    
    // CLADDING–BAR A y B
   // for (size_t i = 0; i < LogicBars_A.size(); ++i) {
     // new G4LogicalBorderSurface("Surface_CladBar_A_" + std::to_string(i),
       //                          Physical_cladding_A[i], Physical_MID_A[i/3], op_surface_bar_clad); // Cada 3 fibras por barra
    //}
    /*for (size_t i = 0; i < Physical_claddings_B.size(); ++i) {
      new G4LogicalBorderSurface("Surface_CladBar_B_" + std::to_string(i),
                                 Physical_cladding_B[i], Physical_MID_B[i/3], op_surface_bar_clad);
    }
    
    // CLADDING–AIRE A y B
    for (size_t i = 0; i < Physical_claddings_A.size(); ++i) {
      new G4LogicalBorderSurface("Surface_CladAir_A_" + std::to_string(i),
                                 Physical_cladding_A[i], PhysicalWorld, op_surface_clad_air);
    }
    for (size_t i = 0; i < Physical_claddings_B.size(); ++i) {
      new G4LogicalBorderSurface("Surface_CladAir_B_" + std::to_string(i),
                                 Physical_cladding_B[i], PhysicalWorld, op_surface_clad_air);
    }
    
    // BAR–AIRE A y B
    for (size_t i = 0; i < Physical_MID_A.size(); ++i) {
      new G4LogicalBorderSurface("Surface_BarAir_A_" + std::to_string(i),
                                 Physical_MID_A[i], PhysicalWorld, op_surface_bar_air);
    }
    for (size_t i = 0; i < Physical_MID_B.size(); ++i) {
      new G4LogicalBorderSurface("Surface_BarAir_B_" + std::to_string(i),
                                 Physical_MID_B[i], PhysicalWorld, op_surface_bar_air);
    }*/


  //---------------  STEEL-ABSORBER  ---------------

 G4double SA_X = 50*cm;
  G4double SA_Y = 35*cm;
  G4double SA_Z =50*cm;

  G4ThreeVector  positionSA = G4ThreeVector(0, 66.56*cm, 0);

  SolidSA = new G4Box("SolidSA", SA_X, SA_Y, SA_Z );
 LogicalSA = new G4LogicalVolume(SolidSA, steel, "LogicSA");
 
fScoringVolume_Abs = LogicalSA;

 PhysicalSA = new G4PVPlacement(0, positionSA, LogicalSA, "PhysicalSA", LogicWorld, false, 0, true);



//              CUBE TO B FIELD
  /*G4double BcubeX = 1.4 * m;
  G4double BcubeY = 1 * m;
  G4double BcubeZ = 1.4 * m;

  G4ThreeVector positioncube = G4ThreeVector(0, 2.0156 * m, 0);
  SolidCube = new G4Box("SolidCube", BcubeX, BcubeY, BcubeZ);
  LogicCube = new G4LogicalVolume(SolidCube, worldMaterial, "LogicCube");
 PhysicalCube = new G4PVPlacement(0, positioncube, LogicCube, "PhysicalCube_forB", LogicWorld, false, 100, true);*/




/*
// world
auto visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
visAttributes->SetVisibility(false);
LogicWorld->SetVisAttributes(visAttributes);
fVisAttributes.push_back(visAttributes);

//cube to field, not available
visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
visAttributes->SetVisibility(false);
LogicCube->SetVisAttributes(visAttributes);
fVisAttributes.push_back(visAttributes);

//absorber
visAttributes = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.6));
visAttributes->SetVisibility(true);
visAttributes->SetForceSolid(false);
LogicalSA->SetVisAttributes(visAttributes);
fVisAttributes.push_back(visAttributes);

//mylar
visAttributes = new G4VisAttributes(G4Colour(0.7, 0.85, 1.0, 0.1));
visAttributes->SetVisibility(true);
visAttributes->SetForceSolid(true);
Logicmylar->SetVisAttributes(visAttributes);
fVisAttributes.push_back(visAttributes);

//scintillators
visAttributes = new G4VisAttributes(G4Colour(0.9, 0.9, 0.9, 0.8));
visAttributes->SetVisibility(true);
visAttributes->SetForceSolid(true);
Logicbar_A->SetVisAttributes(visAttributes);
fVisAttributes.push_back(visAttributes);

//scintillators
visAttributes = new G4VisAttributes(G4Colour(0.9, 0.9, 0.9, 0.8));
visAttributes->SetVisibility(true);
visAttributes->SetForceSolid(true);
Logicbar_B->SetVisAttributes(visAttributes);
fVisAttributes.push_back(visAttributes);

//fiber core
visAttributes = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.9));
visAttributes->SetVisibility(true);
Logic_Fiber_A->SetVisAttributes(visAttributes);
fVisAttributes.push_back(visAttributes);

//cladding
visAttributes = new G4VisAttributes(G4Colour(0.0,0.8,0.2,0.2));
visAttributes->SetVisibility(true);
Logic_cladding_A->SetVisAttributes(visAttributes);
fVisAttributes.push_back(visAttributes);

//SiPMs
visAttributes = new G4VisAttributes(G4Colour(0.3,0.3,1.0,0.3));
visAttributes->SetVisibility(true);
Logicsipm_A->SetVisAttributes(visAttributes);
fVisAttributes.push_back(visAttributes);
*/

}



G4VPhysicalVolume *DetectorConstruction::Construct()
{
  // Solid world
  SolidWorld = new G4Box("SolidWorld", env_sizeX, env_sizeY, env_sizeZ);
  
  //logical
  LogicWorld = new G4LogicalVolume(SolidWorld, worldMaterial, "LogicWorld");

  //Physical
  PhysicalWorld = new G4PVPlacement(0, G4ThreeVector(), LogicWorld, "PhysicalWorld", 0, false, 0, true);


  if (MID_Module)
   ConstructMIDModule(); 

  return PhysicalWorld; 

  // ==========  Optical surface (CLADDING - AIR for A & B) ========== 
 op_surface_clad_air = new G4OpticalSurface("CladAirSurface");
 op_surface_clad_air->SetType(dielectric_dielectric); 
 op_surface_clad_air->SetFinish(ground);
 op_surface_clad_air->SetModel(glisur);
 G4LogicalBorderSurface* border_clad_air_A = new G4LogicalBorderSurface( "Border_clad_air_A", Physical_cladding_A, PhysicalWorld, op_surface_clad_air);
 G4LogicalBorderSurface* border_clad_air_B = new G4LogicalBorderSurface( "Border_clad_air_A", Physical_cladding_B, PhysicalWorld, op_surface_clad_air);

// ==========  Optical surface (BAR - AIR for A & B) ========== 
 op_surface_bar_air = new G4OpticalSurface("BarAirSurface");
 op_surface_bar_air->SetType(dielectric_dielectric); 
 op_surface_bar_air->SetFinish(ground);
 op_surface_bar_air->SetModel(glisur);
 G4LogicalBorderSurface* border_bar_air_A = new G4LogicalBorderSurface( "Border_bar_air_A", Physical_MID_A, PhysicalWorld, op_surface_bar_air);
 G4LogicalBorderSurface* border_bar_air_B = new G4LogicalBorderSurface( "Border_bar_air_A", Physical_MID_B, PhysicalWorld, op_surface_bar_air);

}


void DetectorConstruction::ConstructSDandField()
{
 SensitiveDetector *sensDet = new SensitiveDetector("SensitiveDetector");
 // Assign sensitive detector to all SiPMs in Set A
    for (auto& logicSiPM_aasignment_a : LogicSiPMs_A) {
        logicSiPM_aasignment_a->SetSensitiveDetector(sensDet);
    }

    // Assign sensitive detector to all SiPMs in Set B
    for (auto& logicSiPM_aasignment_b : LogicSiPMs_B) {
        logicSiPM_aasignment_b->SetSensitiveDetector(sensDet);
    }
  
  // Construct the field creator - this will register the field it creates
  /*if (!fEmFieldSetup.Get()) {
    auto  fieldSetup
       = new F01FieldSetup(G4ThreeVector( 0.0, 0.0, 0.5*tesla ));
    G4AutoDelete::Register(fieldSetup); // Kernel will delete the F01FieldSetup
    fEmFieldSetup.Put(fieldSetup);

    // Get components from field setup
    G4MagneticField* magField = fieldSetup->GetMagneticField();
    G4FieldManager* fieldMgr = fieldSetup->GetLocalFieldManager();
    G4ChordFinder* chordFinder = fieldSetup->fChordFinder;
    
    // Configure field manager
    fieldMgr->SetDetectorField(magField);
    fieldMgr->SetChordFinder(chordFinder);
    
    // IMPORTANT: Assign only to LogicCube
    LogicCube->SetFieldManager(fieldMgr, true); // true = override existing
    
    // Explicitly remove field from world
    LogicWorld->SetFieldManager(nullptr, false);
    
    G4cout << "Created magnetic field confined to LogicCube volume" << G4endl;
  }


  // After field assignment:
G4cout << "Field manager assignments:" << G4endl;
G4cout << "  LogicCube has field: " 
       << (LogicCube->GetFieldManager() != nullptr) << G4endl;
G4cout << "  LogicWorld has field: "
       << (LogicWorld->GetFieldManager() != nullptr) << G4endl;*/

 
  /*
  G4MagneticField *magField;
  G4ThreeVector BField = G4ThreeVector(0., 0., 5.0 *kilogauss);
  magField = new G4UniformMagField(BField);

  G4FieldManager* FieldMngr = new G4FieldManager(magField);
  FieldMngr->SetDetectorField(magField);
  FieldMngr->CreateChordFinder(magField);
  LogicCube->SetFieldManager(FieldMngr,true); 
  */
}

