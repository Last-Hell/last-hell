
# Last Hell - Source Code for Last Chaos MMO

Welcome to the **Last Hell** repository, a project focused on the development and enhancement of the MMORPG *Last Chaos*. This repository contains the full source code needed to set up, run, and modify the game servers and clients for *Last Chaos*. Below is a guide to understanding and working with the source code in this project.

## Table of Contents

1. [Project Overview](#project-overview)
2. [Repository Structure](#repository-structure)
3. [Installation](#installation)
4. [Building the Client and Server](#building-the-client-and-server)
5. [Usage Instructions](#usage-instructions)
6. [Contributing](#contributing)
7. [License](#license)

## Project Overview

The **Last Hell** project aims to create a customizable version of the MMO *Last Chaos*. This source code gives developers the ability to:
- Set up a custom game server
- Modify gameplay mechanics
- Develop and run a game client
- Enable a wide range of potential expansions and mods to the game

*Last Chaos* is a popular MMORPG that offers players extensive PvE and PvP gameplay, crafting systems, and guild warfare.

## Repository Structure

The code base is primarily written in **C++**, with additional components written in **C**, **JavaScript**, and other supporting languages.

Key directories:
- `client/`: Contains the client-side source code for running the game.
- `server/`: Contains the server-side source code to host the game world.
- `scripts/`: JavaScript and other auxiliary scripts for server management.
- `data/`: Game assets and configurations.
- `docs/`: Documentation for the project setup and development guidelines.

Key files:
- `README.md`: This file, containing information about the project.
- `Dockerfile`: Instructions to build the Docker container for easy setup.
- `Makefile`: Automates the build process for both client and server code.

## Installation

To install and run the project, follow these steps:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/Last-Hell/last-hell.git
   ```

2. **Set Up Environment**:
   Ensure that you have the necessary dependencies installed, such as `CMake`, `GCC`, and other development tools. If you're running the project in a Docker container, the environment will be automatically configured for you.

3. **Build the Project**:
   ```bash
   cd last-hell
   mkdir build && cd build
   cmake ..
   make
   ```

4. **Run the Server**:
   ```bash
   ./server/bin/last-chaos-server
   ```

## Building the Client and Server

### Server
To build the server, navigate to the `server` directory and run:
```bash
cd server
make
```

### Client
To build the client application:
```bash
cd client
make
```

Both of these commands will generate the binaries necessary to run the client and server.

## Usage Instructions

Once the server is running, you can configure various gameplay mechanics by editing the configuration files found in the `data/` folder. Modify these files to control game parameters such as:
- Player experience rates
- Guild features
- In-game events

After configuring, start the server and connect the client using the appropriate IP address and port.

## Contributing

We welcome contributions! Please follow these guidelines:
- Fork the repository.
- Create a feature branch for any new developments.
- Submit a pull request with a clear explanation of changes.

Please check out the `CONTRIBUTING.md` file for detailed instructions.

## License

This project is licensed under the [MIT License](LICENSE), which means you are free to use, modify, and distribute the software as long as you provide proper attribution.
