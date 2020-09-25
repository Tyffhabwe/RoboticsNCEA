/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\vhabw                                            */
/*    Created:      Wed Jul 29 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftMotor            motor         6               
// RightMotor           motor         7               
// RearBumper           bumper        H               
// RightIntake          motor         16              
// LeftIntake           motor         17              
// RightLift            motor         1               
// LeftLift             motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

//Intake speed variables
#define mainIntakeSpeed 500
#define mainOutTakeSpeed 500


bool armBool = true; //Allows robot to figure out if it needs to pull arm up or down

//Drop the arm
void drop(int liftSpeed, int liftTime){
  RightLift.spin(directionType::rev, liftSpeed,velocityUnits::rpm); 
  LeftLift.spin(directionType::fwd, liftSpeed, velocityUnits::rpm);

  wait(liftSpeed, msec);
}
//Intake function to be called
void intake(int intakeSpeed) {
  RightIntake.spin(directionType::rev, intakeSpeed, velocityUnits::rpm); 
  LeftIntake.spin(directionType::rev, intakeSpeed, velocityUnits::rpm);
}
//Outtake function to be called
void outtake(int intakeSpeed){
  RightIntake.spin(directionType::fwd, intakeSpeed, velocityUnits::rpm); 
  LeftIntake.spin(directionType::fwd, intakeSpeed, velocityUnits::rpm);
}
//Lift function to be called
void lift(int liftSpeed, int liftTime){
  RightLift.spin(directionType::fwd, liftSpeed, velocityUnits::rpm);
  LeftLift.spin(directionType::rev, liftSpeed, velocityUnits::rpm);

  wait(liftTime, msec);

}
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(1){

    //Tank Drive because it's easier to control
    LeftMotor.spin(vex::directionType::fwd, Controller1.Axis3.value()/2, vex::velocityUnits::pct); //(Axis3+Axis4)/2
    RightMotor.spin(vex::directionType::fwd, Controller1.Axis2.value()/2, vex::velocityUnits::pct);//(Axis3-Axis4)/2

    //Press L2 to take the balls in
    if(Controller1.ButtonL2.pressing()){
      intake(mainIntakeSpeed);
    }
    //Press L1 to push balls out
    else if(Controller1.ButtonL1.pressing()){
      outtake(mainOutTakeSpeed);
    }
    //Lift mechanism that allows alternating between up and down
    else if(Controller1.ButtonR1.pressing()){
      if(armBool == true){ //Lift the arm 
        Controller1.Screen.print(armBool);
        armBool = false;
        RightLift.spin(directionType::fwd, 50, velocityUnits::rpm);
        LeftLift.spin(directionType::rev, 50, velocityUnits::rpm);
        wait(2000, msec);//Controls the distance the arm goes up
        RightLift.stop(brakeType::hold);
        LeftLift.stop(brakeType::hold);
      }
      else if(armBool == false){ //Drop the arm
        Controller1.Screen.print(armBool);
        armBool = true;
        RightLift.spin(directionType::rev, 50, velocityUnits::rpm);
        LeftLift.spin(directionType::fwd, 50, velocityUnits::rpm);
        wait(2000, msec); //Controls the distance the arm goes up
        RightLift.stop(brakeType::hold);
        LeftLift.stop(brakeType::hold);
      }
      else{
        Controller1.Screen.print("Something's wrong");
      }
    }
    //Catch statement to ensure that motors don't run indefinitely by stopping them
    else{
      RightIntake.stop();
      LeftIntake.stop();
    }
  }

}

