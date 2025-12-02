This is an active branch!

Author: Tanya Hajipour
Release date: Oct 2025

---- About the sim/px4-interface folder: 

- interface folder includes the actual model for the simulator to interact with PX4 (aka: PX4 plugin/interface) as well as the libfdm (C wrapper) which is a way to connect the fdm that is written in C to the PX4 plugin model. The C wrapper mostly focus on the structure of the input and output of the FDM (coming from the MATLAB code generated) as well as simulation steps

- Within the MATLAB code generated folder there exist UAV Dynamics model and its extensions which are a C code generated from an example within SIMULINK Docs: https://www.mathworks.com/help/uav/px4/ref/px4-stock-hitl-simulink-example.html

- io-port folder is not directly used in the PX4 plugin model, but this folder will later be used to make models inherit from these sockets for their initiation of communication.

- test folder is for the purpose of compiling interface and matlab-code-generated folders to verify PX4 and C wrapper models in the unittest, 
