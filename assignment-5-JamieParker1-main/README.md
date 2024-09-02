### Compilation Instructions

Ensure you have `g++` installed and accessible from your command line. This project uses `g++` from MSYS2.

To compile the project, navigate to the project directory in your terminal and run the following command:

```bash
g++ -fdiagnostics-color=always -g "Lepton.cpp" "FourMomentum.cpp" "Electron.cpp" "Muon.cpp" "Tau.cpp" "Neutrino.cpp" "assignment-5.cpp"  -o "a5"
```

After compilation, you can run the program on Windows by navigating to the output directory and executing:
```bash
.\a5
```
Or, on Unix-like systems:
```bash
./a5
```
Make sure to adjust the file paths in the compilation command if you're placing project files in a different directory. These instructions assume that the terminal's current working directory is the same as where the source files are located.