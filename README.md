Release date: Jan 2026

About the "0101-UVicCfAR_SimulationTools/sim" folder: 

- The simulator has 2 parts:
    . px4_interface: Containing the physics of the UAV and main communication with PX4. 
    . visulizer: sending FDM states to the visualizer renderer as well as creating the behavoiur of the target UAV that would be in POV of the Interceptor


Getting started: 
    In your terminal type the following: 
        cd <path you want the folder to be>
        git clone https://github.com/UVicCfAR/0101-UVicCfAR_SimulationTools.git
        cd 0101-UVicCfAR_SimulationTools.git
        code .
    
    follow the README in path "sim/px4_interface" to get info about each folder and their functionalities 


Architecture: 

.venv                     -> (activate before running any code and then install the python, numpy, pymavlink, and any other libraries)
pyproject.toml            -> (allow importing from files to files without any "path.insert.." use in the script)
sim 
    |
    px4_interface
                |
                analysis  -> (to analyse step delays and any function that is time sensative)
                interface -> (the models for plant and px4 interface)
                kernel    -> (run the models and interfaces)
                samples   -> (code examples to use for those implementing new add-ons)
    visualizer
             |
             interface
                      |
                      client
                      server 
                        
