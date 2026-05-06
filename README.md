Release date: Jan 2026

# About the repo: 

#### kernel: runs the repo
#### px4_interface: Contains the physics of the UAV and communication linkage with PX4_SITL. 
#### visulizer: sending FDM states of the UAV to the renderer



# Architecture 
 
`.venv`   
Activate before running any code, then install required libraries such as: 
 
- `numpy` 
- `pymavlink` 
- and any additional dependencies 
 
--- 
 
`pyproject.toml`   
Allows importing between files/modules without needing manual `sys.path.insert(...)` usage. 
 
--- 
 
```text 
sim/ 
├── px4_interface/ 
│   ├── interface/ 
│   │   └── Models for the plant dynamics and PX4 interface 
│   │ 
│   ├── kernel/ 
│   │   └── Runs the models and interfaces 
│   │ 
│   └── samples/ 
│       └── Example code for implementing new add-ons 
│ 
├── visualizer/ 
│   └── interface/ 
│       └── client.py 
│           └── Connects to the visualization PC/tools 
│ 
└── kernel/ 
   ├── analysis/ 
   │   └── Analyze step delays and timing-sensitive functions 
   │ 
   └── scheduler/ 
       ├── scheduler_busy_wait.py 
       │   └── Main scheduler that runs the repository 
       │ 
       └── draft_other_schedulers/ 
           └── Contains alternative scheduler implementations 
``` 


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