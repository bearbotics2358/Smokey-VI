#ifndef _PREFS_H_
#define _PREFS_H_

//Port 1 on io board seems to be broken, do not use for the time being

//Driver Joystick Port
#define DRIVE_STICK_PORT 1

#define SHOOTER_STICK_PORT 2

#define SHOOTER_SPEED_UP 5

#define SHOOTER_SPEED_DOWN 4

#define SHOOTER_RUN 1

#define SHOOTER_RESET 2

#define FEEDER_BUTTON 1
#define FEEDER_RETRACT_BUTTON 4

#define HANGER_BUTTON 11
#define HANGER_RETRACT_BUTTON 12

//Driving Motor Jaguar IDs
#define LB_DRIVE_ID 1
#define LF_DRIVE_ID 4
#define RB_DRIVE_ID 8
#define RF_DRIVE_ID 5

//Steering Motor Jaguar IDs
#define LB_SWERVE_ID 3
#define LF_SWERVE_ID 2 
#define RB_SWERVE_ID 7
#define RF_SWERVE_ID 6

//Steering Motor Encoder Port #'s
#define LB_SWERVE_ENC 5
#define LF_SWERVE_ENC 4
#define RB_SWERVE_ENC 2
#define RF_SWERVE_ENC 3

//Shooting Motor Victor IDs
#define SHOOTER1_PORT 9
#define SHOOTER2_PORT 10

//Gyro Port #
#define GYRO_PORT 1

//Compressor Relay Port # (the spike)
#define COMPRESSOR_RELAY_PORT 1

//Compressor Switch Port #
#define COMPRESSOR_SWITCH_PORT 1
 
//Solenoid Port #'s for the feeder
#define FEEDER_EXTEND_PORT 1
#define FEEDER_RETRACT_PORT 2

//Solenoid Port #'s for the hanger
#define HANGER_EXTEND_PORT 3
#define HANGER_RETRACT_PORT 4
// Limit Switch Port #'s
#define HANGER_LIMIT_SWITCH1_PORT 8
#define HANGER_LIMIT_SWITCH2_PORT 9
#endif //_PREFS_H_
