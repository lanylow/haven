# haven [![License](https://img.shields.io/badge/License-GPL3.0-green.svg)](https://github.com/lanylow/haven/blob/main/LICENSE.md) ![OS](https://img.shields.io/badge/OS-Linux-green.svg) [![Chat](https://img.shields.io/badge/Chat-Discord-blue.svg)](https://discord.com/invite/zSDXQTc)  
Unofficial SCP: Containment Breach Multiplayer Mod server for linux. This is a "lite" server, which works by redirecting requests to the host player.

## Getting started

### Prerequisites

-   CMake 3.11.0+
-   g++ 10

Below are example commands for some distributions to install the required packages:
#### Ubuntu
    sudo apt-get install cmake g++-10
#### Manjaro
    sudo pacman -S cmake g++
    
### Downloading

Open your terminal and enter the following command:

    git clone https://github.com/lanylow/haven.git

`haven` folder should have been succesfully created, containing all the source files. Now you can enter this folder by typing:

    cd haven

### Configuring

At first, copy the sample config and name it `config.hpp`:

    cp config.sample.hpp config.hpp
    
Now open `config.hpp` with any text editor and choose your settings.

### Building

Execute the following commands in the main haven directory:

    sh build.sh
    
Output file will be placed in `out` directory. Run it by typing:

    ./out/haven
    
## FAQ

### I have a problem, where can I ask for help?
Join the official discord server and ping lanylow#2557 for help. Please, don't create issues on github asking for help.

### I found a bug, where can I report it?
Create an issue on github describing what the bug is and when does it happen.

### I would like to contribute to this project, what do I do?
If you have any significant change that you want to contribute, open a pull request.

## License

This project is licensed under the [GPL-3.0](https://opensource.org/licenses/GPL-3.0) - see the [LICENSE](LICENSE.md) file for details.

## Credits

[Ne4to](https://github.com/Ne4to-podobnoe) - author of the mod.
