//   User Field setup class implementation.

#include "FieldSetUp.hh"
//#include "FieldMessenger.hh"
#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Mag_UsualEqRhs.hh"

//#include "G4MagIntegratorStepper.hh"

#include "G4ChordFinder.hh"
#include "G4ClassicalRK4.hh"
#include "G4DormandPrince745.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"



//  Constructors:
F01FieldSetup::F01FieldSetup(G4ThreeVector fieldVector)                        
 : fMagneticField(new G4UniformMagField(fieldVector))
{
  G4cout << " FIELD SETUP: magnetic field set to Uniform( "
         << fieldVector/tesla << " ) " << G4endl;     // Prints the B Field 

  InitialiseAll();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


F01FieldSetup::F01FieldSetup()
 : fMagneticField(new G4UniformMagField(G4ThreeVector()))
{
  G4cout << " || Field Setup: magnetic field set to Uniform( 0.0, 0, 0 ) || "
         << G4endl;
  InitialiseAll();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


F01FieldSetup::~F01FieldSetup()
{
  delete fMagneticField;
  delete fChordFinder;
  delete fStepper;
  //delete fFieldMessenger;

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void F01FieldSetup::InitialiseAll()
{
  //fFieldMessenger = new FieldMessenger(this);
  fEquation = new G4Mag_UsualEqRhs(fMagneticField); 
  // CREATELOCAL FIELD MANAGER instead of getting global one
  fFieldManager = new G4FieldManager();  

  CreateStepperAndChordFinder(); 

  fFieldManager->SetChordFinder( fChordFinder );
  fFieldManager->SetDetectorField(fMagneticField );
  //fFieldManager = G4TransportationManager::GetTransportationManager()   //  IT WAS DELETE TO JUST ADD THE FIELD 
                    //->GetFieldManager();                                //  ON A VOLUME AND NOT GENERALLY. 

  fMinStep      = 3.0e-3*mm;
  // minimal step of 1 um is default ==> accept any error for smallersteps!
  fDeltaOneStep = 1.0e-5*mm;
  // Errors of this size in an integration sub-step are acceptable
  //   except limited by the relative integration error limits (epsilon_min/max)
  //  Notes: - their initial values are set in the header.
  //         - both this and the eps min/max can be changed using Set methods

  G4cout  << "   4/5. Updating eps_min and eps_max in Field Manager."  << G4endl;


  // For controling the accurancy
  fFieldManager -> SetMinimumEpsilonStep( fDesiredEpsilonMin ) ;
  
  const G4double increaseFactor = 3.0 ;     // typical rangle  1.0 - 10.0
  //  maxEpsilon must not exceed a ceiling, ideally 0.001 -- above this integration is unreliable
   const G4double maxEpsilon = increaseFactor * fDesiredEpsilonMin;
   fFieldManager -> SetMaximumEpsilonStep( maxEpsilon );

  
  // To demonstrate that it is now possible to change the maximum accepted epsilon

  // Note: The values of both epsilon parameters must be between
  //    fMaxAcceptedEpsilon = 0.001
  //   to ensure robustness of integration (adequate accuracy of intermediate results)
  // and (much bigger than)
  //    fMinAcceptedEpsilon ~= 2.2e-13  ( 1000.0 * std::numeric_limits<G4double>::epsilon() )
  // which even the best integration methods would struggle greatly to achieve.

  G4cout << " Changed FieldManager epsilon values to  epsilon_min= "
         << fFieldManager -> GetMinimumEpsilonStep()
         <<  " and epsilon_max= "
         << fFieldManager -> GetMaximumEpsilonStep() << G4endl;

         G4cout << "\n" << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



void F01FieldSetup::CreateStepperAndChordFinder()
{
  delete fChordFinder;
  fChordFinder= nullptr;

  // Update field
  G4cout << " FIELD SETUP::CreateStepperAndChordFinder() called. " << G4endl
         << "   1. Creating Stepper."  << G4endl;

  SetStepper();
  G4cout<<"The minimal step is equal to "<<fMinStep/mm<<" mm"<<G4endl;


  G4cout << "   2. Creating ChordFinder."  << G4endl;
  fChordFinder = new G4ChordFinder( fMagneticField, fMinStep,fStepper );


  G4cout << "   3. Updating Field Manager (chord finder, field-ptr)."  << G4endl;
  fFieldManager->SetChordFinder( fChordFinder );
  fFieldManager->SetDetectorField(fMagneticField );
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void F01FieldSetup::SetStepper()
{
// Set stepper according to the stepper type

  delete fStepper;

       fStepper = new G4ClassicalRK4( fEquation );
       G4cout<<"G4ClassicalRK4 Stepper (default) is chosen"<<G4endl;

//fStepper = new G4DormandPrince745( fEquation );
//G4cout<<"G4DormandPrince745 (default) Stepper is chosen"<<G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void F01FieldSetup::SetFieldValue(G4ThreeVector fieldVector)
{
  // Set the value of the Global Field

  delete fMagneticField;

if (fieldVector != G4ThreeVector(0.,0.,0.)) {
    fMagneticField = new G4UniformMagField(fieldVector);
    G4cout << "Field updated to " << fieldVector/tesla << " Tesla" << G4endl;
  } else {
    fMagneticField = nullptr;
    G4cout << "Field set to zero" << G4endl;
  }

  fEquation->SetFieldObj(fMagneticField);
  fFieldManager->SetDetectorField(fMagneticField);

}


  G4ThreeVector F01FieldSetup::GetConstantFieldValue()
{
  if (fMagneticField) {
    return static_cast<G4UniformMagField*>(fMagneticField)->GetConstantFieldValue();
  }
  return G4ThreeVector(0.,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


