How to use any Plant model (FDM Model and sensor models) within sim framework: 

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