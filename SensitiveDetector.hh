//      SENSITIVE DETECTOR HEADER 

#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh" 
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "RunAction.hh"
#include "EventAction.hh"

class SensitiveDetector : public G4VSensitiveDetector
{
 public:
  SensitiveDetector(G4String);
  ~SensitiveDetector();
 
 private:
  virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *);
};
#endif

