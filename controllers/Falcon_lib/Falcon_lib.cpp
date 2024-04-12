// File:          Falcon_lib.cpp
// Date:
// Description: Falcon lib
// Authors: Jan Škrabal, Veronika Jirmusová

#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/PositionSensor.hpp>
#include <stdio.h>

// All the webots classes are defined in the "webots" namespace
using namespace webots;
using namespace std;

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();

  // get the time step of the current world.
  int timeStep = (int)robot->getBasicTimeStep();

  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  DistanceSensor *ds = robot->getDistanceSensor("distance sensor");
  ds->enable(timeStep);
  Motor *m0 = robot->getMotor("mR");
  Motor *m1 = robot->getMotor("mL");
  PositionSensor *pos0 = m0->getPositionSensor();
  pos0->enable(timeStep);
  PositionSensor *pos1 = m1->getPositionSensor();
  pos1->enable(timeStep);

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while (robot->step(timeStep) != -1) {
    // Read the sensors:
    // Enter here functions to read sensor data, like:
    //  double val = ds->getValue();

    // Process sensor data here.

    // Enter here functions to send actuator commands, like:
    //  motor->setPosition(10.0);
    m0->setPosition(11.15);
    m1->setPosition(0.0);
    cout << "dis: " << ds->getValue() << " pos0: " << pos0->getValue() << " pos1: " << pos1->getValue()  << endl;
    
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}
