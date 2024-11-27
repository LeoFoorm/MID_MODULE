#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::Build() const
{
    PrimaryGeneratorAction *generator = new PrimaryGeneratorAction();
    SetUserAction(generator);

    RunAction *runaction = new RunAction();
    SetUserAction(runaction);

    EventAction *eventaction = new EventAction(runaction); 
    SetUserAction(eventaction);

    SteppingAction *steppingaction = new SteppingAction(eventaction);
    SetUserAction(steppingaction);
}
