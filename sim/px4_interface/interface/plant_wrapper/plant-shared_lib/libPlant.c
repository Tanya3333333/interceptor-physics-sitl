// Plant (FDM + Sensor Models) C Wrapper to be compiled into a shared library (libPlant.so)
#include "UAV_Dynamics.h"
#include <stdio.h>

// paramters
#define MOTOR_COUNT (sizeof(UAV_Dynamics_U.PWMInputs) / sizeof(UAV_Dynamics_U.PWMInputs[0]))

// --- i/o structure for fdm ---
typedef struct {
    float motor_commands[MOTOR_COUNT]; // 4 rotors 1, 2, 3, 4 normalized
} FDM_Input;

typedef struct {
    // - state quaternion -
    double position_ned[3];    // x, y, z (unit: meters)
    double velocity_ned[3];    // Vx, Vy, Vz (unit: m/s)
    float attitude_quaternion[4]; // w, x, y, z -- in the fdm: q0-q1-q2-q3
    float angular_velocity[3];  // P, Q, R (unit: rad/s, body frame)

    // - imu/sensor -
    double acc[3];
    double gyro[3];
    double mag[3];

    // - baro -
    double pressure;
    double lla[3];   // lat, lon, alt
    
    // - gps -
    double gnd_speed;
    double course_deg;

    // FDM States
    double states_raw[21];

} PLANT_Output;

// Entry points and globals
extern void UAV_Dynamics_initialize(void);
extern void UAV_Dynamics_step(void);
extern ExtU_UAV_Dynamics_T UAV_Dynamics_U;
extern ExtY_UAV_Dynamics_T UAV_Dynamics_Y;
extern X_UAV_Dynamics_T UAV_Dynamics_X;

//calls the Simulink-generated init function
void plant_initialize(void) 
{
    printf ("[libplant] plant model initialized..\n");
    // setting it to zero if its not already zero
    memset(&UAV_Dynamics_U, 0, sizeof(UAV_Dynamics_U));
    memset(&UAV_Dynamics_Y, 0, sizeof(UAV_Dynamics_Y));

    UAV_Dynamics_initialize();
}

// transfer simulink i/o (UAV_DYNAMICS_U/Y) to planrt i/o structure
void fdm_step(const FDM_Input* in, PLANT_Output* out)
{
    // Inputs → model
    for (int i = 0; i < MOTOR_COUNT; ++i) {
        float u = in->motor_commands[i];
        if (u < 0.f) u = 0.f;
        if (u > 1.f) u = 1.f;
        UAV_Dynamics_U.PWMInputs[i] = (double)u;
    }

    // advance one tick
    UAV_Dynamics_step();

    // Outputs (check 6DOF block in simulink for finding the names of var)
    out->velocity_ned[0] = UAV_Dynamics_Y.Velocity[0];
    out->velocity_ned[1] = UAV_Dynamics_Y.Velocity[1];
    out->velocity_ned[2] = UAV_Dynamics_Y.Velocity[2];

    out->angular_velocity[0] = (float)UAV_Dynamics_Y.Gyro[0];
    out->angular_velocity[1] = (float)UAV_Dynamics_Y.Gyro[1];
    out->angular_velocity[2] = (float)UAV_Dynamics_Y.Gyro[2];

    out->attitude_quaternion[0] = UAV_Dynamics_Y.quat_raw[0];  // w - q0
    out->attitude_quaternion[1] = UAV_Dynamics_Y.quat_raw[1];  // x - q1
    out->attitude_quaternion[2] = UAV_Dynamics_Y.quat_raw[2];  // y - q2
    out->attitude_quaternion[3] = UAV_Dynamics_Y.quat_raw[3];  // z - q3

    out->position_ned[0] = UAV_Dynamics_Y.posi_raw[0];
    out->position_ned[1] = UAV_Dynamics_Y.posi_raw[1];
    out->position_ned[2] = UAV_Dynamics_Y.posi_raw[2];

    // placeholders for all the sensors (imu, baro, gps)
    for (int i = 0; i < 3; i++)
    {
        out->acc[i]  = UAV_Dynamics_Y.Acc[i];
        out->gyro[i] = UAV_Dynamics_Y.Gyro[i];
        out->mag[i]  = UAV_Dynamics_Y.Mag[i];
        out->lla[i]  = UAV_Dynamics_Y.LLA[i];
    }

    out->pressure   = UAV_Dynamics_Y.Pressure;
    out->gnd_speed  = UAV_Dynamics_Y.GndSpeed;
    out->course_deg = UAV_Dynamics_Y.Course;


    // FDM raw states
    for (int i = 0; i < 21; i++)
    {
        out->states_raw[i] = ((double*)&UAV_Dynamics_X)[i];
    }
}