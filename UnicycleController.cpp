/*
 * uni.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Austin
 */

#include <DifferentialMotorCommand.hpp>
#include "UnicycleController.hpp"
#include "VelocityVector.hpp"
#include <math.h>

UnicycleController::UnicycleController(Pose2D* pose)
{
	robotPose = pose;
	_maxOmega = 3.14159;
	_wheelBase=24.0;
	_wheelRadius=2.0;
	_transformL = .1;
}

 VelocityVector UnicycleController::Tracker(double x,double y)
 {
 	VelocityVector output;



 	return output;
 };

 VelocityVector UnicycleController::Tracker(double phi)
 {
	VelocityVector output;
	output.v=0.0;

	output.w = phi/_maxOmega;

	return output;
 }

 VelocityVector UnicycleController::Transform(double x,double y)

 {
 	VelocityVector output;

 	double theta = atan(y/x);

 	double l = _transformL;

 	output.v = x*cos(theta)+y*sin(theta);
 	output.w = y*cos(theta)/l-x*sin(theta)/l;

 	return output;
 }

 VelocityVector UnicycleController::Transform(double phi )
 {
 	VelocityVector output;
 	output.v=0.0;

 	output.w = phi/_maxOmega;

 	return output;
 }

 DifferentialMotorCommand UnicycleController::DifferentialOutput(VelocityVector input)
{

	DifferentialMotorCommand command;
	command.VR=(2*input.v+input.w)/2;
    command.VL=(2*input.v-input.w)/2;
	return command;
}

 DifferentialMotorCommand UnicycleController::GetDifferentialMotorCommand(double x,double y)
 {

	return DifferentialOutput(Transform(x,y));

 }
 DifferentialMotorCommand UnicycleController::GetDifferentialMotorCommand(double phi)
 {
	 double p = atan2(sin(phi), cos(phi));
	 return DifferentialOutput(Transform(p));
 }

