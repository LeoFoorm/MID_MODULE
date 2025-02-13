//Author:   Carlos Leonardo Fernandez Luna

//Project:  Construction of detector (.cc)

//THIS IS THE    main 


#include <iostream>
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "DetectorConstruction.hh"
#include "Physics.hh"
#include "ActionInitialization.hh"
#include "G4OpticalPhysics.hh"
#include "Randomize.hh"


//argc and argv are parameters used to process command-line arguments. argc argument count and
// argv argument vector.



int main(int argc,char** argv)
{
    long seeds[2];
    seeds[0] = time(NULL);
    seeds[1] = 0;
    CLHEP::HepRandom::setTheSeeds(seeds);
    
    #ifdef G4MULTITHREADED
        G4MTRunManager *runManager = new G4MTRunManager();
    #else
    
        G4RunManager *runManager = new G4RunManager();
    #endif
    
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new ActionInitialization());
    
    //runManager->Initialize();
    
    G4UIExecutive *ui = 0;
    if(argc==1)
    {
        ui = new G4UIExecutive(argc,argv);
    }
    G4VisManager * visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();

   UImanager->ApplyCommand("/run/verbose 2");
    UImanager->ApplyCommand("/control/verbose 2");
    UImanager->ApplyCommand("/process/had/verbose 0");

    if(ui)
    {
    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/ViewpointVector 1 1 1");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");//update everytime it creates a new event
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");//to show the particle
    UImanager->ApplyCommand("/vis/scene/endofEventAction accumulate");//to show the particle
    UImanager->ApplyCommand("/vis/set/volumeForField"); //MAGNETIC FIELD
    UImanager->ApplyCommand("/vis/scene/add/magneticField"); // MAGNETIC FIELD
    UImanager->ApplyCommand("/vis/scene/add/axes 0 0 0 2.8 m");
    UImanager->ApplyCommand("/vis/scene/add/hits");
    UImanager->ApplyCommand("/vis/scene/add/eventID");
    UImanager->ApplyCommand("/vis/scene/add/date");
    UImanager->ApplyCommand("/vis/scene/");

    ui->SessionStart();
    }

    else
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }

 // Limpieza explícita de recursos
    delete visManager;   // Eliminar el administrador de visualización
    delete ui;           // Eliminar el UI Executive (si existe)
    delete runManager;   // Eliminar el RunManager
    G4cout << "Simulation finished successfully." << G4endl;


    return 0;
}

