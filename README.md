**WiFi Communication Simulation**
Object-Oriented Programming and Design - Monsoon 2024

This project is a simulation of WiFi communication protocols to measure the throughput, latency, and maximum latency under varying number of users . The simulation focuses on three WiFi standards:

WiFi 4 (CSMA/CA): Implements Carrier Sense Multiple Access with Collision Avoidance.
WiFi 5 (MU-MIMO): Models Multi-User Multiple-Input and Multiple-Output communication.
WiFi 6 (OFDMA): Simulates Orthogonal Frequency-Division Multiple Access.


Building the Project using Makefile:
The Makefile is used to compile, build, and manage a WiFi simulation project. 

Targets in the Makefile
all:
This is the default target and will:
Compile individual source files into object files (.o files).
Commands:
g++ -c WiFi.cpp -o WiFi.o compiles WiFi.cpp into WiFi.o without linking.
Similar commands exist for other source files like WiFi4.cpp, WiFi5.cpp, etc.
Create a static library (libwifi_simulation.a) from the compiled object files.
Command:
ar rcs libwifi_simulation.a WiFi.o WiFi4.o WiFi5.o WiFi6.o AccessPoint.o Report.o FrequencyChannel.o Packet.o User.o creates a static library using the ar (archive) tool.
Link the static library with simulation.cpp to produce executable files:
Command for a standard build:
g++ simulation.cpp -L. -lwifi_simulation -o wifi_simulation creates the main executable (wifi_simulation) by linking the static library (-lwifi_simulation) located in the current directory (-L.).
Debug build
Produces a version of the program with debugging symbols enabled (useful for debugging with tools like gdb).
Command:
g++ -g simulation.cpp -L. -lwifi_simulation -o wifi_simulation_debug
Optimized build
Produces a highly optimized version of the program for performance.
Command:
g++ -O3 simulation.cpp -L. -lwifi_simulation -o wifi_simulation_optimized
-O3 enables aggressive optimization options in the compiler.
clean:
Removes all compiled files, the static library, and executables, ensuring a clean build environment.
Command:
rm -f *.o libwifi_simulation.a wifi_simulation wifi_simulation_debug wifi_simulation_optimized



Input: There is no input file for running the program.It takes user input.

Added Functionality : Added feature have been added to make a report of metrics for all transmission and also maintain the logs of accesspoint.


**I have taken help from chatgpt to do this project.**
