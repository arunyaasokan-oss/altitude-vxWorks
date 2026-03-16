# VxWorks Local build and Simulator

Follow the steps below to setup VxWorks environment.

## Basic setup

#### Clone the reference repository

`git clone https://github.com/aromalpj/vxBuild.git`

#### Install and Setup the dependencies

Install the dependencies using the command`./install.sh`
This script will do the following:

- Download the VxWorks SDK
- Extract the SDK
- Install dependencies such as `Qemu`,`ftpserver`, `toolchains` etc...

#### Setup the build environment

Setup the build environment using the command `./setenv.sh`. This command needs to be run everytime when new instances are used for development.

#### Compile the source code

`make`

#### Run the Emulator

To start the simulator environment for VxWorks run the command `./qemu.sh`
This script will do the following:

- Start the FTP server for VxWorks environment which maps the custom executables.
- Starts the QEMU with `VxWorks 7` environment.

