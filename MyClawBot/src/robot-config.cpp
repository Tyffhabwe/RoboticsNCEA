#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LeftMotor = motor(PORT6, ratio18_1, false);
motor RightMotor = motor(PORT7, ratio18_1, true);
bumper RearBumper = bumper(Brain.ThreeWirePort.H);
motor RightIntake = motor(PORT16, ratio18_1, false);
motor LeftIntake = motor(PORT17, ratio18_1, true);
motor RightLift = motor(PORT1, ratio18_1, false);
motor LeftLift = motor(PORT2, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}