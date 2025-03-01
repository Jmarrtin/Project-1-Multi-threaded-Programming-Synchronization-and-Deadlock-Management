# Project-1-Multi-threaded-Programming-Synchronization-and-Deadlock-Management
This repository contains the complete source code for the "Multi-Threaded Car Simulation and IPC" project developed for CS 3502: Project 1. The project demonstrates key operating system concepts, including multi-threading and inter-process communication (IPC), using a car-themed simulation in C++.

## Project Overview
The project is divided into two main components:

- **Project A: Multi-Threaded Car Simulation**  
  This component simulates a fleet of cars performing various operations concurrently. It is structured into four phases:
  - **Phase 1:** Basic thread operations where multiple car threads are created and simulate starting and driving.
  - **Phase 2:** Resource protection using a mutex to simulate a shared gas station where cars refuel.
  - **Phase 3:** A deadlock creation scenario where cars try to cross two bridges by locking shared resources in different orders.
  - **Phase 4:** Deadlock resolution using `std::lock` and adopt-lock mechanisms to safely allow cars to cross both bridges.

- **Project B: Inter-Process Communication (IPC)**  
  This component demonstrates IPC by creating a pipe between a parent and a child process. The parent process sends car data (e.g., car IDs and speeds) to the child process, which then reads and displays the data.

## Repository Contents
- `projectA.cpp` – Source code for the multi-threaded car simulation.
- `projectB.cpp` – Source code for the IPC demonstration.
- `README.md` – This file.
- Additional documentation and resources (e.g., LaTeX report, demonstration video) as needed.

## Dependencies and Installation

### Dependencies
- **Operating System:** A Linux-based environment (e.g., Ubuntu) or Windows Subsystem for Linux (WSL).
- **Compiler:** `g++` with C++11 support.
- **Libraries:** Uses only standard C++ libraries.
- **Additional Tools:** Basic Linux tools for monitoring (e.g., `top`, `ps`, `kill`).

### Installation Instructions
1. **Set Up the Environment:**  
   - Install a Linux distribution (e.g., Ubuntu) or set up WSL on your Windows machine.
   - Ensure that `g++` is installed. On Ubuntu, you can install it with:
     ```bash
     sudo apt update
     sudo apt install build-essential
     ```
2. **Clone the Repository:**  
   Clone the repository to your local machine:
   ```bash
   git clone https://github.com/yourusername/MultiThreadedCarSimulation.git
   cd MultiThreadedCarSimulation
