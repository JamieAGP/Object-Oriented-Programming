Features:
- Four-Momentum Handling: Simulates the energy and three-dimensional momentum of leptons, providing a foundation for particle physics studies.
- Dynamic Memory Use: Efficiently manages memory for particle properties using dynamic allocation.
- Operator Overloading: Simplifies simulations with intuitive operations for adding momenta and calculating dot products.
- Support for Multiple Lepton Types: Includes electrons, muons, and their antiparticles, enabling diverse simulations.

### Compilation Instructions

Ensure you have `g++` installed and accessible from your command line. This project uses `g++` from MSYS2.

To compile the project, navigate to the project directory in your terminal and run the following command:

```bash
g++ -fdiagnostics-color=always -g "Lepton.cpp" "assignment-4.cpp" -o "a4"
```

After compilation, you can run the program on Windows by navigating to the output directory and executing:
```bash
.\a4
```
Or, on Unix-like systems:
```bash
./a4
```
Make sure to adjust the file paths in the compilation command if you're placing project files in a different directory. These instructions assume that the terminal's current working directory is the same as where the source files are located.






