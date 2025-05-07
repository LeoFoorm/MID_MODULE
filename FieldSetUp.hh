
//   i) user class that creates the field           ( Current choice )
//  ii) a field manager that creates/updates field

#ifndef F01FieldSetup_h
#define F01FieldSetup_h 1

#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"
//#include "FieldMessenger.hh"

class G4FieldManager;
class G4ChordFinder;
class G4Mag_UsualEqRhs;
class G4MagIntegratorStepper;
class G4VIntegrationDriver;
class FieldMessenger;

class F01FieldSetup
{
public:
  F01FieldSetup(G4ThreeVector fieldVector);             //  The value of the field    

  F01FieldSetup();               //  A zero field
  F01FieldSetup( F01FieldSetup&) = delete;
  virtual ~F01FieldSetup();

  // ----------------------------
  void SetFieldValue(G4ThreeVector fieldVector);
  G4ThreeVector GetConstantFieldValue();


   void SetStepper();


  // ----------------------------
  void SetMinStep(G4double s) { fMinStep = s; }

  void InitialiseAll();    //  Set parameters and call method below

   // Original method
  void CreateStepperAndChordFinder();


  // Parameters for integration accuracy : get / control
  // -------------------------------------------------------
  G4double GetEpsilonMin(){ return fDesiredEpsilonMin; }
  G4double GetEpsilonMax(){ return fDesiredEpsilonMax; }

  void   SetEpsilonMin(G4double val){ fDesiredEpsilonMin= val; }
  void   SetEpsilonMax(G4double val){ fDesiredEpsilonMax= val; }

  void   SetDeltaOneStep(G4double val){ fDeltaOneStep= val; }


public:
  G4MagneticField* GetMagneticField() { return fMagneticField; }

   G4FieldManager* GetLocalFieldManager() { return fFieldManager; }


public:

  G4FieldManager*          fFieldManager = nullptr;
  G4ChordFinder*           fChordFinder = nullptr;
  G4Mag_UsualEqRhs*        fEquation = nullptr;
  G4MagneticField*         fMagneticField = nullptr;
  G4MagIntegratorStepper*  fStepper = nullptr;
  //FieldMessenger*       fFieldMessenger = nullptr;

  // Parameters / Invariant during tracking loop
  G4double fMinStep     = -1.0;
  G4double fDeltaOneStep= -1.0;
  G4double fDesiredEpsilonMin = 1.0e-05; // tight: 1.0e-8  std: 1.0e-5 to 1.e-6  loose: 1.0e-4
  G4double fDesiredEpsilonMax = 0.005;   // tight: 1.0e-5  std: 1.0e-4 to 5.e-3  loose: 1.0e-3+
};

#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


