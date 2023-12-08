// Bounce.pde
// -*- mode: C++ -*-
//
// Make a single stepper bounce from one limit to another
//
// Copyright (C) 2012 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

#define Stepper1StepPin 27
#define Stepper1DirPin 26

// Define a stepper and the pins it will use
// AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

AccelStepper stepper (AccelStepper::DRIVER, Stepper1StepPin, Stepper1DirPin);

long dx = 0;

void setup()
{  
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(6000);
  stepper.setAcceleration(4000);
  // stepper.moveTo(6400);

  // 1mm per 200 pulses at 1/4-step
}

void loop()
{

    // If at the end of travel go to the other end
    if (stepper.distanceToGo() == 0){
      if(stepper.currentPosition() > 10){
        stepper.moveTo(0);
      }
      else{
        stepper.moveTo(dx+=200);
        // dx += 200;
        dx %= 4000;
      }
      delay(2000);
    }

    stepper.run();
}
