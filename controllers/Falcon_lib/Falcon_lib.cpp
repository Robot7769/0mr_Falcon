// File:          Falcon_lib.cpp
// Date:
// Description: Falcon lib
// Authors: Jan Škrabal, Veronika Jirmusová

#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/PositionSensor.hpp>
#include <webots/Keyboard.hpp>
#include <webots/VacuumGripper.hpp>
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
  Keyboard *keyboard = new Keyboard();
  keyboard->enable(timeStep);

  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  DistanceSensor *ds = robot->getDistanceSensor("distance sensor");
  ds->enable(timeStep);
  Motor *m0 = robot->getMotor("mR");
  Motor *m1 = robot->getMotor("mL");
  Motor *ram0 = robot->getMotor("ram0");
  ram0->setVelocity(0.1);
  Motor *ram1 = robot->getMotor("ram1");
  ram1->setVelocity(0.3);
  Motor *ram2 = robot->getMotor("ram2");
  ram2->setVelocity(0.3);
  //VacuumGripper *gripper = robot->getVacuumGripper("gripper");

  PositionSensor *pos0 = m0->getPositionSensor();
  pos0->enable(timeStep);
  PositionSensor *pos1 = m1->getPositionSensor();
  pos1->enable(timeStep);

  PositionSensor *ram0_pos = ram0->getPositionSensor();
  ram0_pos->enable(timeStep);
  PositionSensor *ram1_pos = ram1->getPositionSensor();
  ram1_pos->enable(timeStep);
  PositionSensor *ram2_pos = ram2->getPositionSensor();
  ram2_pos->enable(timeStep);

  ram0->setPosition(0);
  ram1->setPosition(-1.3);
  ram2->setPosition(-1.2);
  double ramStep = 0.01;


  double max_speed = 5.5;
  bool manual = false;

  double pos0_val = pos0->getValue();
  double pos1_val = pos1->getValue();
  m0->setVelocity(10);
  m1->setVelocity(10);
  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while (robot->step(timeStep) != -1) {
    int key = keyboard->getKey();
    if (key == 77) { //M
      manual = true;
    }
    if (manual) {
      m0->setPosition(1000000);
      m1->setPosition(1000000);

      switch(key) {
        case 87: //W
          m0->setVelocity(max_speed);
          m1->setVelocity(max_speed);
          break;
        case 68: //D
          m0->setPosition(-1000000);
          m1->setVelocity(max_speed*0.7);
          m0->setVelocity(max_speed*0.7);
          break;
        case 65: //A
          m1->setPosition(-1000000);
          m0->setVelocity(max_speed*0.7);
          m1->setVelocity(max_speed*0.7);
          break;
        case 83: //S
          m0->setPosition(-1000000);
          m1->setPosition(-1000000);
          m0->setVelocity(max_speed);
          m1->setVelocity(max_speed);
          break;
        case 48: //0
          ram0->setPosition(ram0_pos->getValue() - ramStep);
          break;
        case 49: //1
          ram0->setPosition(ram0_pos->getValue() + ramStep);
          break;
        case 50: //2
          ram1->setPosition(ram1_pos->getValue() - ramStep);
          break;
        case 51: //3
          ram1->setPosition(ram1_pos->getValue() + ramStep);
          break;
        case 52: //4
          ram2->setPosition(ram2_pos->getValue() - ramStep);
          break;
        case 53: //5
          ram2->setPosition(ram2_pos->getValue() + ramStep);
          break;
        default: 
          m0->setVelocity(0);
          m1->setVelocity(0);
          break;
      }
    } else {
      double time = robot->getTime();
      int tmp = 0;
      if (time < 2) {
        m0->setPosition(0.0);
        m1->setPosition(0.0);
      } else if (time < 6) {
        m0->setPosition(19);
        m1->setPosition(0.0);
      } else if (time < 6.04) {
        if (tmp == 0) {
          pos0_val = pos0->getValue() + 20;
          pos1_val = pos1->getValue() + 20;
          tmp = 1;
        }
      } else if (time < 12) {
        tmp = 1;
        m0->setPosition(pos0_val);
        m1->setPosition(pos1_val);
      } /*else if (time < 20.04) {
        if (tmp == 1) {
          pos0_val = pos0->getValue() - 20;
          pos1_val = pos1->getValue() - 20;
          tmp = 2;
        }
      }*/ else if (time < 25) {
        m0->setPosition(16);
        m1->setPosition(-3);
      } else {
        manual = true;
      }
      
    }
    // Debug
    cout << " pos0: " << pos0->getValue() << " pos1: " << pos1->getValue()  << endl;
    cout << "ram0: " << ram0_pos->getValue() << " ram1: " << ram1_pos->getValue() << " ram2: " << ram2_pos->getValue() << endl;
    cout << "time: " << robot->getTime() << endl;
  };


  delete robot;
  return 0;
}
