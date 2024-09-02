## Release Summary: Particle Catalogue System

The Particle Catalogue project, developed at The University of Manchester by James Parker, efficiently stores and manipulates data related to Standard Model particles using advanced C++ programming techniques. This system utilizes C++ features such as templates, Standard Template Library (STL) containers, and exception handling to create a robust particle data management system.

### Key Features:
- **Flexible Data Handling:** Utilizes templates for generic programming, reducing redundancy and enhancing type safety.
- **Efficient Data Storage:** Employs STL containers like `std::map` and `std::set` for optimized data retrieval and sorting.
- **Advanced Error Management:** Systematic exception handling ensures robustness, particularly in user interactions.
- **Object-Oriented Design:** Leverages inheritance and polymorphism for a clear hierarchical organization of particle classes, which represents various particle types such as leptons, bosons, and quarks.
- **Interactive User Interface:** A comprehensive UI allows users to add, manage, and analyze particle data without needing to interact directly with the underlying codebase.
- **Physical Accuracy and Validation:** Implements a physically accurate representation of particles, ensuring that all properties like mass and decay behaviors are consistent with theoretical expectations.

This project not only meets its functional objectives but also provides an educational tool for those interested in particle physics, demonstrating the application of theoretical concepts in a practical, software-oriented context.

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

