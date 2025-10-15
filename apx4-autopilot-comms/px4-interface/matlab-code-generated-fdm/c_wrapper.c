
/*
 * FDM C Wrapper: fdm_wrapper.c
 *
 * This file provides a C-compatible interface for your Python script (using ctypes)
 * to interact with the Simulink-generated FDM (UAV_Dynamics).
 *
 * It will be compiled into a shared library (e.g., libfdm.so or fdm.dll), which is
 * the "outside" component.
 */

#include "UAV_Dynamics.h"
#include <stdio.h>

/* --- Simplified C Structures for Python (ctypes) Interoperability --- */

// Input structure mirroring MAVLink ACTUATOR_CONTROLS (e.g., 4 rotor commands)
typedef struct {
    float motor_commands[4]; // Rotor 1, 2, 3, 4 normalized [0, 1]
    float delta_time;        // Time step for the FDM integration
} FDM_Input;

// Output structure containing the necessary state for MAVLink HIL_STATE_QUATERNION
typedef struct {
    double position_ned[3];    // x, y, z (meters, North-East-Down)
    double velocity_ned[3];    // Vx, Vy, Vz (m/s, North-East-Down)
    float attitude_quaternion[4]; // w, x, y, z (quaternion, WXYZ order is assumed for FDM internal)
    float angular_velocity[3];  // P, Q, R (rad/s, body frame)
} FDM_Output;


/* --- Global FDM Data --- */
// Get pointers to the model data structures defined in UAV_Dynamics.c
// NOTE: These lines are crucial for connecting the wrapper to the generated code.
RT_MODEL_UAV_Dynamics_T *const UAV_Dynamics_M = UAV_Dynamics();
ExtU_UAV_Dynamics_T *UAV_Dynamics_U = UAV_Dynamics_M->ExternalInputs;
ExtY_UAV_Dynamics_T *UAV_Dynamics_Y = UAV_Dynamics_M->ExternalOutputs;


/*
 * Function: fdm_initialize
 * ------------------------
 * Initializes the FDM (calls the Simulink-generated init function).
 */
void fdm_initialize() {
    if (UAV_Dynamics_M != NULL) {
        printf("FDM: Initializing UAV_Dynamics model...\n");
        UAV_Dynamics_initialize();
    } else {
        printf("FDM ERROR: UAV_Dynamics model structure is NULL. Check compilation.\n");
    }
}

/*
 * Function: fdm_step
 * ------------------
 * Main FDM function to be called from Python.
 * 1. Copies input data from Python (FDM_Input) into the Simulink input structure (UAV_Dynamics_U).
 * 2. Runs the Simulink step function.
 * 3. Copies output data from the Simulink output structure (UAV_Dynamics_Y) to the Python output structure (FDM_Output).
 */
void fdm_step(const FDM_Input *input, FDM_Output *output) {
    // 1. Map Python input to FDM internal inputs (UAV_Dynamics_U)
    // Assuming UAV_Dynamics_U->RotorSpeedCommands is the input array of 4 floats:
    for (int i = 0; i < 4; i++) {
        UAV_Dynamics_U->RotorSpeedCommands[i] = input->motor_commands[i];
    }
    // Note: The input struct FDM_Input does not contain delta_time, as the Simulink step function
    // implicitly uses the model's fixed step size. We will rely on the main loop frequency in Python.


    // 2. Run the FDM step
    UAV_Dynamics_step();


    // 3. Map FDM internal outputs (UAV_Dynamics_Y) to Python output structure (FDM_Output)
    // NOTE: These field names (Position_NED, Attitude_Quat, etc.) are ASSUMED based on common Simulink exports.
    // You MUST verify these against the actual ExtY_UAV_Dynamics_T definition in your UAV_Dynamics.h file.

    // Position (m)
    output->position_ned[0] = UAV_Dynamics_Y->Position_NED[0];
    output->position_ned[1] = UAV_Dynamics_Y->Position_NED[1];
    output->position_ned[2] = UAV_Dynamics_Y->Position_NED[2];

    // Velocity (m/s)
    output->velocity_ned[0] = UAV_Dynamics_Y->Velocity_NED[0];
    output->velocity_ned[1] = UAV_Dynamics_Y->Velocity_NED[1];
    output->velocity_ned[2] = UAV_Dynamics_Y->Velocity_NED[2];

    // Attitude (Quaternion w, x, y, z)
    output->attitude_quaternion[0] = UAV_Dynamics_Y->Attitude_Quat[0];
    output->attitude_quaternion[1] = UAV_Dynamics_Y->Attitude_Quat[1];
    output->attitude_quaternion[2] = UAV_Dynamics_Y->Attitude_Quat[2];
    output->attitude_quaternion[3] = UAV_Dynamics_Y->Attitude_Quat[3];

    // Angular Velocity (rad/s)
    output->angular_velocity[0] = UAV_Dynamics_Y->AngularVelocity_Body[0];
    output->angular_velocity[1] = UAV_Dynamics_Y->AngularVelocity_Body[1];
    output->angular_velocity[2] = UAV_Dynamics_Y->AngularVelocity_Body[2];
}
