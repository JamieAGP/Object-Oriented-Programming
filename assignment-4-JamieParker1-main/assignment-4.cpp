// PHYS 30762 Programming in C++
// Assignment 4

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

#include "Lepton.h"

// Clears console screen based on operating system
void clear_screen()
{
// Clears terminal window
#ifdef _WIN32 // check if program is compiled on Windows
  system("cls");
#else
  // if not windows, clear screen using ANSI escape code
  std::cout << "\033[2J\033[1;1H";
#endif
}

int main()
{
  clear_screen();
  std::vector<Lepton> test_particles;
  test_particles.reserve(7); // Reserve space for at least 8 particles

  // For 7 'emblace_back' calls, construct objects in-place in
  // 'test_particles' without  requiring reallocations

  cout << "\033[1mCreating 7 particles in-place in vector\033[0m\n";
  test_particles.emplace_back(511, 1, 2, 3, 0.511, -1, "Electron");
  test_particles.emplace_back(511, 4, 5, 6, 0.511, -1, "Electron");

  test_particles.emplace_back(511, 7, 8, 9, 105.66, -1, "Muon");
  test_particles.emplace_back(511, 10, 11, 12, 105.66, -1, "Muon");
  test_particles.emplace_back(511, 13, 14, 15, 105.66, -1, "Muon");
  test_particles.emplace_back(511, 16, 17, 18, 105.66, -1, "Muon");

  test_particles.emplace_back(511, 1, 0, 0, 105.66, 1, "Antimuon");
  

  // Add new particle so vector exceeds reserved capacity
  cout << "\n\033[1mAdding 8th particle, to showcase vector reallocating existing objects to new storage using move, and destructor destroying previous object out of scope.The new object is constructed directly in the new storage location.\033[0m\n";
  test_particles.emplace_back(511, 1, 0, 0, 0.511, 1, "Antielectron");

  // Addition
  cout << "\n\033[1mShowcasing Four-momentum addition\033[0m\n";
  cout << "\033[1m-First Electron\033[0m:\n" << test_particles[0];
  cout << "\033[1m-Second Electron\033[0m:\n" << test_particles[1];
  // Sum the four-momenta of the two electrons
  Lepton sum_of_electrons = test_particles[0] + test_particles[1];
  cout << "\033[1m-Sum of Electrons Four momentum\033[0m:\n" << sum_of_electrons << endl;
  

  // Dot product
  cout << "\n\033[1mShowcasing Four-momentum dot products using 'E1*E2 - (px1*px2 + py1*py2 + pz1*pz2)'\033[0m\n";
  cout << "\033[1m-First Muon:\033[0m \n" << test_particles[2];
  cout << "\033[1m-Second Muon:\033[0m \n" << test_particles[3];
  // Dot product of the first two muons
  double dot_product_muons = test_particles[2].dot_product(test_particles[3]);
  cout << "\033[1m-Dot Product of the first two Muons' Four-Momenta: \033[0m" << dot_product_muons << "(MeV)^2" << endl << endl;

  // Assignment operator of an electron to a new electron
  
  Lepton new_electron = test_particles[0]; // Copy assignment
  cout << "\033[1mNew Electron Created by Assignment to first Electron:\033[0m \n" << new_electron << endl;

  // Copy constructor of the first muon to a new muon
  Lepton copied_muon(test_particles[2]);
  cout << "\033[1mNew Muon Created by Copy Constructor:\033[0m \n" << copied_muon << endl;

  // Move the antielectron into another antielectron
  Lepton moved_antielectron(move(test_particles[7]));
  cout << "\033[1mAntielectron Moved:\033[0m \n" << moved_antielectron << endl;

  // Assign the antimuon to another antimuon
  Lepton another_antimuon = move(test_particles[6]);
  cout << "\033[1mAntimuon Moved by Assignment:\033[0m \n" << another_antimuon << endl;

  cout << "\033[1mEnding program\n\033[0m";

  return 0;
}
