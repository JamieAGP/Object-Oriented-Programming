### Compilation Instructions

Ensure you have `g++` installed and accessible from your command line. This project uses `g++` from MSYS2.

To compile the project, navigate to the project directory in your terminal and run the following command:

```bash
C:\\msys64\\ucrt64\\bin\\g++.exe -fdiagnostics-color=always -g "leptons/Muon.cpp" "leptons/Electron.cpp" "leptons/Lepton.cpp" "leptons/Tau.cpp" "leptons/Neutrino.cpp" "bosons/Boson.cpp" "bosons/Gluon.cpp" "bosons/Photon.cpp" "bosons/Z.cpp" "bosons/W.cpp" "bosons/Higgs.cpp" "quarks/Quark.cpp" "FourMomentum.cpp" "Particle.cpp" "helper_functions.cpp" "showcase.cpp" "user_interface.cpp" "project.cpp" -o "project"
```

If on the **lab computer**:

```bash
g++.exe -fdiagnostics-color=always -g "leptons/Muon.cpp" "leptons/Electron.cpp" "leptons/Lepton.cpp" "leptons/Tau.cpp" "leptons/Neutrino.cpp" "bosons/Boson.cpp" "bosons/Gluon.cpp" "bosons/Photon.cpp" "bosons/Z.cpp" "bosons/W.cpp" "bosons/Higgs.cpp" "quarks/Quark.cpp" "FourMomentum.cpp" "Particle.cpp" "helper_functions.cpp" "showcase.cpp" "user_interface.cpp" "project.cpp" -o "project"
```

After compilation, you can run the program on Windows by navigating to the output directory and executing:
```bash
.\project
```
Or, on Unix-like systems:
```bash
./project
```
Make sure to adjust the file paths in the compilation command if you're placing project files in a different directory. These instructions assume that the terminal's current working directory is the same as where the source files are located.

