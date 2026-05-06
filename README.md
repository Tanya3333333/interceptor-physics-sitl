Release date: Jan 2026

# About the repo: 

## kernel: runs the repo
## px4_interface: Contains the physics of the UAV and communication linkage with PX4_SITL. 
## visulizer: sending FDM states of the UAV to the renderer



# Architecture: 

|
    .venv                                       -> (activate before running any code and then install the python, numpy, pymavlink, and any other libraries)
    pyproject.toml                              -> (allow importing from files to files without any "path.insert.." use in the script)
    sim 
        |
        px4_interface
                    |
                    
                    interface                   -> (the models for plant and px4 interface)
                    kernel                      -> (run the models and interfaces)
                    samples                     -> (code examples to use for those implementing new add-ons)
        visualizer
                 |
                 interface
                         |
                         client.py              -> (connect to the PC with visualization tools)
        kernel
             |
             analysis  -> (to analyse step delays and any function that is time sensative)
             scheduler
                     |
                      scheduler_busy_wait.py    -> the scheduler that runs the repo (aka main file)
                      draft_other_schedulers    -> folder contains other scheduler logics



# Requirment:

Python3.12



# Getting started: 

1) Clone the repo: 

    cd <path you want the folder to be>
    git clone https://github.com/Tanya3333333/interceptor-physics-sitl.git
    cd interceptor-physics-sitl.git
    code .

2) Make a virtual environment and activate it:

. For win: 

        py -3 -m venv .venv
        .\.venv\Scripts\Activate.ps1

. For Ubuntu (recommended): 

        python3 -m venv .venv
        source .venv/bin/activate

3) Install pip:
sudo apt update
sudo apt install python3-pip -y

4) Install dependecies for this repo (such as packages, libraries, etc):
pip install -r requirements.txt

5) source the Python:
echo 'alias python=python3' >> ~/.bashrc
source ~/.bashrc



# How to run the pipeline:

1) Run px4_sitl:
make px4_sitl none_iris

2) Run the repo:
python -m sim.kernel.scheduler.scheduler_busy_wait