Author: Tanya Hajipour
Release date: Oct 2025

About the "sim/px4-interface" folder: 

- "sim/px4-interface/interface" folder includes the core models including: 
    . The main SITL model to communicate with PX4 Autopilot, initia
    
    te FDM and Sensor models, unpack commands from PX4 and pack data back to PX4 
    . Plant models (FDM and Sensor Models) of different aircrafts in different programming languages (the plant wrappers are being used to translate different languages to the main SITL model)

- "sim/px4-interface/kernel" folder manages the simulation - including: 
    . "scheduler" folder steps the FDM, and send massages all with specific frequencies. 
    . To run this simulator, use this command line: python -m kernel.scheduler.scheduler_busy_wait 
            (scheduler_busy_wait is the optimal scheduler to use for more determinisitc reactions. However the remaining schedulers also work, but with more jitter and was developed for RT evaluation of SITL testing) 
    . TO run logger: ~/home/0101-UVicCfAR_SimulationTools/sim/px4_interface/analysis/logger$ --(run command)--> python3 -m logger_module_test
        --> only scheduler_initial_test.py and scheduler_ext_log.py uses the logger module

-  "sim/px4-interface/samples" include:
    . Example of a simple client/server model (for networking communication)
    . The simulink model used for the current plant model. 
        To access the whole model, run this command in MATLAB Command Window and go to the UAV_Dynamics block for FDM and sensors models: openExample('px4/PX4StockAutopilotHITLUAVDynamicsExample')
        For more info, follow this website: https://www.mathworks.com/help/uav/px4/ref/px4-stock-hitl-simulink-example.html

-  "sim/px4-interface/analysis" include:
    . logger module that needs to run before running the scheduler (if the scheduler is using multiprocess loggin -> scheduler_ext_log.py)
    . jitter-analysis has a script to analyse the files (to run use command: python analysis/jitter-analysis/scheduler_timestamp-analysis.py)
        To use this, make sure to edit the files paths and "pip install" the scipy and the matplotlib libraries.

How to use any Plant model (FDM Model and sensor models) within Simulator framework: 

Section 1. If the plant model is available in MATLAB-Simulink: 
    Recommendation: to minimize the editing work and debugging process, download the Simulink model in "sample_practice/plant_model" and edit that Simulink Model for the new Dynamics. 

    i. Generate a C code from the MATLAB side (choose the compressed version)
    ii. Insert a folder in "plant/plant_model" with the files that has been genrated in C
    iii. Edit the libPlant.c to match the:
        . Include head files 
        . Name of the new I/O variables that need to equal to "global variables" (see the list within the libPlant file). 
            If more variables are available, add them - but also need to add it to the "plant_wrapper/c_wrapper model". 
        . Number of arrays for each variable 
        . Function names: make sure to have "UAV_Dynamics_initialize();" and "UAV_Dynamics_step();" fucntions in your plant model 
        . chekc the name/number of the PWM inputs that are an input to the FDM

    iv. Re-generate object file and .so/.dll (Depending on the OS: if window -> .dll if linux -> .so)
        note: since PX4 runs in Linux, if the environment has to be in window, create a TCP/IP connection from the window to the Ubuntu that is running the PX4_SITL to send and receive info from PX4. But for sanity checks to see if FDM integrated and steps properly, this model can still work as long as "fake/any" input data drives the FDM model.
        . make sure to change the path of the "FDM_DIR := ../quadcopter_plant_model" to the correct address of the new plant model (should be same name as as what you selected in step ii)
        . To re-generate:
            Go to path: cd ~/0101-UVicCfAR_SimulationTools/sim/px4_interface/interface/plant/plant_shared_lib
            if the OS in use is window, make sure the "x86_64-w64-mingw32" is installed in the system
            on terminal type: clean make 
            on terminal type: make

    v. (only if new variables added to the sample plant model or number of motors changed) Do a final code check in "plant_wrapper/c_wrapper.py" to make sure motor_num and the I/O structure matches the new FDM 

Section 2. If the plant model is available in C:
    i. Follow the steps in Section 1 from ii -> v 

Section 3. If the plant model is available in Python:
    i. Create a folder in "plant/plant_model" 
    ii. Follow the TODO comments in "plant/plant_wrapper/python_wrapper.py" 
    iii. Change the import path in "interface/px4_interface_sitl.py" to use the python_wrapper since the default wrapper is c_wrapper.py