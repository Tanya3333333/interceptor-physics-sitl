// FDM C Wrapper to be compiled into a shared library (libfdm.so)

#include "UAV_Dynamics.h"
#include <stdio.h>

// --- i/o structure for fdm ---

typedef struct {
    float motor_commands[4]; // 4 rotors 1, 2, 3, 4 normalized
    float delta_time;        // Time step for the FDM integration
} FDM_Input;

typedef struct {
    
    // - state quaternion -
    double position_ned[3];    // x, y, z (unit: meters)
    double velocity_ned[3];    // Vx, Vy, Vz (unit: m/s)
    float attitude_quaternion[4]; // w, x, y, z
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

} FDM_Output;

// Entry points and globals
extern void UAV_Dynamics_initialize(void);
extern void UAV_Dynamics_step(void);
extern ExtU_UAV_Dynamics_T UAV_Dynamics_U;
extern ExtY_UAV_Dynamics_T UAV_Dynamics_Y;


//calls the Simulink-generated init function
void fdm_initialize(void) 
{
    printf ("[libfdm] fdm_initialize() called\n");
    // setting it to zero if its not already zero
    memset(&UAV_Dynamics_U, 0, sizeof(UAV_Dynamics_U));
    memset(&UAV_Dynamics_Y, 0, sizeof(UAV_Dynamics_Y));

    UAV_Dynamics_initialize();
}

// transfer simulink i/o (UAV_DYNAMICS_U/Y) to FDM_Input/Output)
void fdm_step(const FDM_Input* in, FDM_Output* out)
{
    // Inputs → model
    for (int i = 0; i < 4; ++i) {
        float u = in->motor_commands[i];
        if (u < 0.f) u = 0.f;
        if (u > 1.f) u = 1.f;
        UAV_Dynamics_U.PWMInputs[i] = (double)u; // real_T/double in codegen
    }

    // advance one tick
    UAV_Dynamics_step();

    // Outputs ← model
    out->velocity_ned[0] = UAV_Dynamics_Y.Velocity[0];
    out->velocity_ned[1] = UAV_Dynamics_Y.Velocity[1];
    out->velocity_ned[2] = UAV_Dynamics_Y.Velocity[2];

    out->angular_velocity[0] = (float)UAV_Dynamics_Y.Gyro[0];
    out->angular_velocity[1] = (float)UAV_Dynamics_Y.Gyro[1];
    out->angular_velocity[2] = (float)UAV_Dynamics_Y.Gyro[2];

    // placeholders (no attitude/NED pos in outputs yet)
    out->attitude_quaternion[0] = 1.f;  // w
    out->attitude_quaternion[1] = 0.f;  // x
    out->attitude_quaternion[2] = 0.f;  // y
    out->attitude_quaternion[3] = 0.f;  // z

    out->position_ned[0] = 0.0;
    out->position_ned[1] = 0.0;
    out->position_ned[2] = 0.0;

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
}