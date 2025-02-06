//    RUN ACION HEADER

#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"		//ya no es g4root.hh, ahora es este que puse.
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"


class RunAction : public G4UserRunAction
{
 public:
  RunAction();
  ~RunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);


  void Add_DetectedPhotons_run_all_SiPMs(G4int sipmID) 
  {
    if (sipmID >= 0 && sipmID < 40) 
    {
        photonHits[sipmID]++;
    }
}
std::vector<G4int> GetPhotonHits() const 
{
    return photonHits;
}


private:
 
 std::vector<G4int> photonHits;
 
};

#endif


