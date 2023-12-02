#include "trigger.h"

using namespace std;

Trigger::Trigger(int state) : triggerState{state} {}

int Trigger::getState() { return triggerState; }