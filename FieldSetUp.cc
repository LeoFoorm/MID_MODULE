//   User Field setup class implementation.
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "FieldSetUp.hh"

//#include "F01FieldMessenger.hh"

#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"

#include "G4FieldManager.hh"

#include "G4TransportationManager.hh"

#include "G4Mag_UsualEqRhs.hh"

#include "G4MagIntegratorStepper.hh"

#include "G4ChordFinder.hh"

#include "G4ExplicitEuler.hh"
#include "G4ImplicitEuler.hh"

#include "G4SimpleRunge.hh"
//#include "G4SimpleHeum.hh"

#include "G4ClassicalRK4.hh"

#include "G4HelixExplicitEuler.hh"
#include "G4HelixImplicitEuler.hh"
#include "G4HelixSimpleRunge.hh"

/*
#include "G4CashKarpRKF45.hh"
#include "G4RKG3_Stepper.hh"
#include "G4ConstRK4.hh"*/
#include "G4NystromRK4.hh"
#include "G4HelixMixedStepper.hh"
#include "G4ExactHelixStepper.hh"

//#include "G4BogackiShampine23.hh"
//#include "G4BogackiShampine45.hh"

#include "G4DormandPrince745.hh"

#include "G4DormandPrinceRK56.hh"
#include "G4DormandPrinceRK78.hh"
#include "G4TsitourasRK45.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

enum EStepperNumber { kDormandPrince45 = 17, kClassicalRK4 = 4,
                     kDormandPrince56 = 56, 
                     kDormandPrince78 = 78 
                    } ;

//  Constructors:


F01FieldSetup::F01FieldSetup(G4ThreeVector fieldVector,
                             G4int         stepperNum,
                             G4bool        useFSALstepper )                         
 : fMagneticField(new G4UniformMagField(fieldVector)),
    fUseFSALstepper(useFSALstepper),
   fStepperType(5)
{
  G4cout << " F01FieldSetup: magnetic field set to Uniform( "
         << fieldVector << " ) " << G4endl;     // Prints the B Field 


  if( stepperNum == -1000 )
  {
     fUseFSALstepper = useFSALstepper;
     if( !useFSALstepper )
        fStepperType=   5;   // Use Dormand Prince (7) 4/5 as default stepper
     else
        fStepperType = 101;
  }
  

  InitialiseAll();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

F01FieldSetup::F01FieldSetup()
 : fMagneticField(new G4UniformMagField(G4ThreeVector())),
   fUseFSALstepper(false),
   fStepperType(17)   // Use Dormand Prince (7) 4/5 as default stepper
{
  G4cout << " F01FieldSetup: magnetic field set to Uniform( 0.0, 0, 0 ) "
         << G4endl;
  InitialiseAll();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void F01FieldSetup::InitialiseAll()
{
  //fFieldMessenger = new F01FieldMessenger(this);

  fEquation = new G4Mag_UsualEqRhs(fMagneticField); // Change for a relativistic? 

  fMinStep      = 3.0e-3*mm;
  // minimal step of 1 um is default ==> accept any error for smallersteps!
  fDeltaOneStep = 1.0e-5*mm;
  // Errors of this size in an integration sub-step are acceptable
  //   except limited by the relative integration error limits (epsilon_min/max)
  //  Notes: - their initial values are set in the header.
  //         - both this and the eps min/max can be changed using Set methods.


  //fFieldManager = G4TransportationManager::GetTransportationManager()
                    //->GetFieldManager();

    // Create LOCAL field manager instead of getting global one
    fFieldManager = new G4FieldManager();            

  if( fUseFSALstepper ) {
    CreateFSALStepperAndChordFinder();
  }
  else
  {
    CreateStepperAndChordFinder();
    // To try the symplectic method (Boris Scheme/Driver) replace the line above
    // with the one below:
    // CreateAndSetupBorisDriver();
  }

  G4cout  << "   4/5. Updating eps_min and eps_max in Field Manager."  << G4endl;
  fFieldManager->SetChordFinder( fChordFinder );
  fFieldManager->SetDetectorField(fMagneticField );

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

F01FieldSetup::~F01FieldSetup()
{
  delete fMagneticField;
  delete fChordFinder;
  delete fStepper;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void F01FieldSetup::CreateStepperAndChordFinder()
{
  delete fChordFinder;
  fChordFinder= nullptr;

  // Update field
  G4cout << " F01FieldSetup::CreateStepperAndChordFinder() called. " << G4endl
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

  switch ( fStepperType )
  {
     //  The new default in G4 and here ( since G4 10.4 Dec 2017 )
    case 17:
    case 457:
    case 745:
      fStepper = new G4DormandPrince745( fEquation );
      G4cout<<"G4DormandPrince745 Stepper is chosen"<<G4endl;
      break;

    case 0:
      fStepper = new G4ExplicitEuler( fEquation );
      G4cout<<"G4ExplicitEuler is chosen."<<G4endl;
      break;
    case 1:
      fStepper = new G4ImplicitEuler( fEquation );
      G4cout<<"G4ImplicitEuler is chosen"<<G4endl;
      break;
      
    case 2:
      fStepper = new G4SimpleRunge( fEquation );
      G4cout<<"G4SimpleRunge is chosen"<<G4endl;
      break;
    
    case 4:
      fStepper = new G4ClassicalRK4( fEquation );
      G4cout<<"G4ClassicalRK4 (default) is chosen"<<G4endl;
      break;
    case 5:
      fStepper = new G4HelixExplicitEuler( fEquation );
      G4cout<<"G4HelixExplicitEuler is chosen *"<<G4endl;
      break;
    case 6:
      fStepper = new G4HelixImplicitEuler( fEquation );
      G4cout<<"G4HelixImplicitEuler is chosen"<<G4endl;
      break;
    case 7:
      fStepper = new G4HelixSimpleRunge( fEquation );
      G4cout<<"G4HelixSimpleRunge is chosen"<<G4endl;
      break; 
    
    case 10:
       fStepper = new G4ExactHelixStepper( fEquation );
       G4cout<<"G4ExactHelixStepper is chosen"<<G4endl;
       break;
    case 11:
       fStepper = new G4HelixMixedStepper( fEquation );
       G4cout<<"G4HelixMixedStepper is chosen"<<G4endl;
       break;
    case 13:
    case 40:
      fStepper = new G4NystromRK4( fEquation );
      G4cout<<" G4NystromRK4 Stepper is chosen"<<G4endl;
      break;
    

      // Higher order embedded steppers - for very smooth fields
    case 56:
      fStepper = new G4DormandPrinceRK56( fEquation );
      G4cout<<"G4DormandPrinceRK56 Stepper is chosen"<<G4endl;
      break;
    case 78:
      fStepper = new G4DormandPrinceRK78( fEquation );
      G4cout<<"G4DormandPrinceRK78 Stepper is chosen"<<G4endl;
      break;

    default:
      // fStepper = new G4ClassicalRK4( fEquation );
      // G4cout<<"G4ClassicalRK4 Stepper (default) is chosen"<<G4endl;
      fStepper = new G4DormandPrince745( fEquation );
      G4cout<<"G4DormandPrince745 (default) Stepper is chosen"<<G4endl;
      break;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4VIntegrationDriver.hh"
#include "G4FSALIntegrationDriver.hh"
#include "G4RK547FEq1.hh"
#include "G4RK547FEq2.hh"
#include "G4RK547FEq3.hh"

G4VIntegrationDriver*
F01FieldSetup::CreateFSALStepperAndDriver()
{
   // using FsalStepperType = G4RK547FEq1;
  const char *methodName= "F01FieldSetup::CreateFSALStepperAndDriver()";
  delete fStepper;
  fStepper = nullptr;

  G4cout << " F01FieldSetup::CreateFSALStepperAndDriver() called. " << G4endl;
  G4cout << "   1. Creating Stepper."  << G4endl;
  // auto fsalStepper = new FsalStepperType( fEquation );
  G4RK547FEq1* stepper1 = nullptr;
  G4RK547FEq2* stepper2 = nullptr;
  G4RK547FEq3* stepper3 = nullptr;

  G4cout << "   2. Creating FSAL Driver."  << G4endl;
  G4VIntegrationDriver* fsalDriver = nullptr;
  switch ( fStepperType )
  {
    case   1:
    case 101:
       stepper1 = new G4RK547FEq1( fEquation );
       fsalDriver = new G4FSALIntegrationDriver<G4RK547FEq1>( fMinStep, stepper1 );
       G4cout  << " Stepper type '1' is G4RK547FEq1 stepper (in FSAL mode) with FSAL driver. "
               << G4endl;
       fStepper = stepper1;
       stepper1 = nullptr;
       break;

    case   2:
    case 102:
       stepper2= new G4RK547FEq2( fEquation );
       fsalDriver = new G4FSALIntegrationDriver<G4RK547FEq2>( fMinStep, stepper2 );
       G4cout  << " Stepper type '2' is G4RK547FEq2 stepper (in FSAL mode) with FSAL driver. "
               << G4endl;
       fStepper = stepper2;
       stepper2 = nullptr;
       break;

    case   3:
    case 103:
       stepper3 = new G4RK547FEq3( fEquation );
       fsalDriver = new G4FSALIntegrationDriver<G4RK547FEq3>( fMinStep, stepper3 );
       G4cout  << " Stepper type '3' is G4RK547FEq3 stepper (in FSAL mode) with FSAL driver. "
               << G4endl;
       fStepper = stepper3;
       stepper3 = nullptr;
       break;

    default:
       G4cout << " Warning from " << methodName << " :  stepperType (= "
              << fStepperType << " ) is unknown. " << G4endl
              << " Using value '1' instead - i.e. G4RK547FEq1 stepper. "
              << G4endl;
       stepper1 = new G4RK547FEq1( fEquation );
       fsalDriver = new G4FSALIntegrationDriver<G4RK547FEq1>( fMinStep, stepper1 );
       fStepper = stepper1;
       stepper1 = nullptr;
       break;
  }

  delete stepper1;    stepper1 = nullptr;
  delete stepper2;    stepper2 = nullptr;
  delete stepper3;    stepper3 = nullptr;

  if( fsalDriver )
     fStepper = fsalDriver->GetStepper();

  return fsalDriver;
}

void F01FieldSetup::CreateFSALStepperAndChordFinder()
{
  // using FsalStepperType = G4DormandPrince745; // eventually ?
  delete fChordFinder;
  fChordFinder= nullptr;

  G4cout << " F01FieldSetup::CreateFSALStepperAndChordFinder() called. " << G4endl;

  auto FSALdriver= CreateFSALStepperAndDriver();
  fDriver = FSALdriver;
  G4cout<<"The minimal step is equal to "<<fMinStep/mm<<" mm"<<G4endl;

  G4cout << "    3. Creating ChordFinder."  << G4endl;
  fChordFinder = new G4ChordFinder( FSALdriver );  // ( fMagneticField, fMinStep, fStepper );
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void F01FieldSetup::SetFieldValue(G4ThreeVector fieldVector)
{
  // Set the value of the Global Field

  /*delete fMagneticField;

#ifdef G4VERBOSE
     G4cout << "Setting Field strength to "
            << fieldVector / gauss  << " Gauss." << G4endl;
#endif

  if (fieldVector != G4ThreeVector(0.,0.,0.))
  {
    fMagneticField = new G4UniformMagField(fieldVector);
  }
  else
  {
#ifdef G4VERBOSE
     G4cout << " Magnetic field pointer is null." << G4endl;
#endif
    // If the new field's value is Zero, signal it as below
    // so that it is not used for propagation.
    fMagneticField = nullptr;
  }

  // Set this as the field of the global Field Manager
  GetGlobalFieldManager()->SetDetectorField(fMagneticField);

  // Now notify equation of new field
  fEquation->SetFieldObj( fMagneticField );
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4BorisScheme.hh"
#include"G4BorisDriver.hh"

void
F01FieldSetup::CreateAndSetupBorisDriver()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

