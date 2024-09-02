// PHYS 30762 Programming in C++
// Assignment 5
// Author: James Parker
/*
This C++ program demonstrates programming concepts in C++,
focusing on inheritance, smart pointers, and polymorphism.

It defines a hierarchy of lepton classes (Electron, Muon, Neutrino, Tau) inheriting from a base Lepton class,
showcasing polymorphism and dynamic memory management through smart pointers.

Features include creating particles, manipulating their properties, and calculating physical properties
like four-momentum sums and dot products. 

The program is designed to handle input validation. The use of C++ features (e.g., std::unique_ptr, std::shared_ptr, std::make_unique) 
is emphasized for resource management and code clarity. Additionally, utility functions like clear_screen and loading animations are 
used to improve user interaction.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::chrono::seconds

#include <memory>    // For std::make_unique and std::shared_ptr
#include <algorithm> // For std::find_if
#include <limits>    // For std::numeric_limits
#include <iomanip>   // For std::setprecision and std::fixed
#include <numeric>

#include "Lepton.h"
#include "FourMomentum.h"
#include "Electron.h"
#include "Muon.h"
#include "Neutrino.h"
#include "Tau.h"

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

// Gets a valid number from user
void get_valid_number(const std::string &prompt, const std::string &error_message, double &number, double min_val = -std::numeric_limits<double>::infinity(), double max_val = std::numeric_limits<double>::infinity())
{
  std::string input;
  while(true)
  {
    std::cout << prompt;
    std::getline(std::cin, input); // Read the whole line into a string

    std::stringstream ss(input);
    ss >> number;

    // Check if the entire input string was numeric and no characters are left after parsing the number
    // Also check if the extracted number falls within the specified range
    if(ss.fail() || !ss.eof() || number <= 0 || number <= min_val || number >= max_val)
    {
      std::cout << error_message << std::endl;
    }
    else
    {
      break; // Valid number entered; exit the loop
    }
  }
}

// Gets a valid integer from user
void get_valid_integer(const std::string &prompt, const std::string &error_message, int &number, int min_val = std::numeric_limits<int>::min(), int max_val = std::numeric_limits<int>::max())
{
  std::string input;
  while(true)
  {
    std::cout << prompt;
    std::getline(std::cin, input); // Read the whole line into a string

    std::stringstream ss(input);
    ss >> number;

    // Check if the entire input string was numeric, no characters are left after parsing the number,
    // and the extracted number falls within the specified range (inclusive of minVal and maxVal)
    if(ss.fail() || !ss.eof() || number < min_val || number > max_val)
    {
      std::cout << error_message << std::endl;
    }
    else
    {
      break; // Valid integer entered; exit the loop
    }
  }
}

// Prints a string followed by dots
void print_loading_string(const std::string &input_string, int seconds, bool new_new_line = false)
{
  std::cout << input_string;
  for(int i = 0; i < seconds; ++i)
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << ".";
  }
  std::cout << std::endl; // Move to a new line after printing all dots
  if(new_new_line)
  {
    std::cout << std::endl;
  }
}

// Test implementation
void test_implementation()
{
  std::vector<std::unique_ptr<Lepton>> test_particles;

  // Creating an Electrons
  test_particles.push_back(std::make_unique<Electron>(
      "Electron 1", std::make_unique<FourMomentum>(1, 2, 3, 0.511), std::vector<double>{0.2, 0.3, 0.4, 0.1}));
  test_particles.push_back(std::make_unique<Electron>(
      "Electron 2", std::make_unique<FourMomentum>(1, 5, 6, 0.511), std::vector<double>{0.6, 0.1, 0.1, 0.2}));
  // Creating muons
  test_particles.push_back(std::make_unique<Muon>(
      "Muon 1", std::make_unique<FourMomentum>(4, 5, 6, 0.511), 1));
  test_particles.push_back(std::make_unique<Muon>(
      "Muon 2", std::make_unique<FourMomentum>(4, 5, 6, 0.511), 1));
  test_particles.push_back(std::make_unique<Muon>(
      "Muon 3", std::make_unique<FourMomentum>(4, 5, 6, 0.511), 1));
  test_particles.push_back(std::make_unique<Muon>(
      "Muon 4", std::make_unique<FourMomentum>(4, 5, 6, 0.511), 1));
  // Creating anti-electron
  test_particles.push_back(std::make_unique<Electron>(
      "Anti-electron 1", std::make_unique<FourMomentum>(1, 2, 3, 0.511), std::vector<double>{0.2, 0.3, 0.4, 0.1}, true));
  // Creating anti-muon
  test_particles.push_back(std::make_unique<Muon>(
      "Anti-muon 1", std::make_unique<FourMomentum>(1, 2, 3, 0.511), 0, true));
  // Creating muon-neutrino
  test_particles.push_back(std::make_unique<Neutrino>(
      "Muon-neutrino 1", std::make_unique<FourMomentum>(1, 2, 3, 0.511), "muon", 0));
  // Creating electron-neutrino
  test_particles.push_back(std::make_unique<Neutrino>(
      "Electron-neutrino 1", std::make_unique<FourMomentum>(1, 2, 3, 0.511), "electron", 0));

  // Instantiate decay products for first tau
  auto muon = std::make_shared<Muon>("Decay Muon", std::make_unique<FourMomentum>(3, 3, 3, 3), 0);
  auto antimuon_neutrino = std::make_shared<Neutrino>("Decay Neutrino", std::make_unique<FourMomentum>(1, 1, 1, 1), "muon", 1, true);
  auto tau_neutrino = std::make_shared<Neutrino>("Decay Neutrino", std::make_unique<FourMomentum>(1, 1, 1, 1), "tau", 1);
  // Group the decay products in a vector
  std::vector<std::shared_ptr<Lepton>> decay_products1{muon, antimuon_neutrino, tau_neutrino};
  test_particles.push_back(std::make_unique<Tau>(
      "Tau 1", std::make_unique<FourMomentum>(5, 5, 5, 5), DecayType::Leptonic, decay_products1));

  // Instantiate decay products for antitau
  auto antielectron = std::make_shared<Electron>("Decay Electron", std::make_unique<FourMomentum>(3, 3, 3, 3), std::vector<double>{1, 1, 0.5, 0.5}, true);
  auto electron_neutrino = std::make_shared<Neutrino>("Decay Neutrino", std::make_unique<FourMomentum>(1, 1, 1, 1), "electron", 1);
  auto antitau_neutrino = std::make_shared<Neutrino>("Decay Neutrino", std::make_unique<FourMomentum>(1, 1, 1, 1), "tau", 1, true);
  // Group the decay products in a vector
  std::vector<std::shared_ptr<Lepton>> decay_products2{antielectron, electron_neutrino, antitau_neutrino};
  test_particles.push_back(std::make_unique<Tau>(
      "AntitTau 1", std::make_unique<FourMomentum>(5, 5, 5, 5), DecayType::Leptonic, decay_products2, true));

  // Loop through the particles
  print_loading_string("\033[4mLooping through particles\033[0m", 4);
  int i = 1;
  for(const auto &particle : test_particles)
  {
    std::cout << "\nParticle " << i++ << ": \n";
    std::cout << particle->get_type() << std::endl;
    std::cout << "--------------------------\n";
    particle->print(); // Polymorphic call to print
  }

  print_loading_string("\n\033[4mSumming the four momentum of the electrons:\033[0m", 4, true);
  FourMomentum summed_momentum = sum_four_momentum(*test_particles[0], *test_particles[1]);
  std::cout << summed_momentum << " [MeV]\n";

  print_loading_string("\n\033[4mTaking the dot product of the antielectron and antimuons four momentum:\033[0m", 4, true);
  double dot_product = dot_product_four_momentum(*test_particles[6], *test_particles[7]);
  std::cout << dot_product << " [MeV]\n";

  print_loading_string("\n\033[4mCreating a new Electron outside the original vector:\033[0m", 4, true);
  auto new_electron = std::make_unique<Electron>(
      "New Electron", std::make_unique<FourMomentum>(1, 3, 4, 0.511), std::vector<double>{0.3, 0.2, 0.1, 0.4});

  std::cout << "New Electron created: \n\n";
  new_electron->print();
  // Move the data to the first Electron in the test_particles vector
  std::cout << "\nMoving new Electron's data to the first Electron in the vector...\n";
  // Moving new_electron to the target Electron
  *dynamic_cast<Electron *>(test_particles[0].get()) = std::move(*new_electron);
  std::cout << "First Electron's after moving: \n\n";
  test_particles[0]->print();

  print_loading_string("\n\033[4mCreating a shared pointer to a Tau to be owned by multiple variables:\033[0m", 4, true);
  // Create a shared_ptr to a Tau lepton
  std::shared_ptr<Tau> tau_ptr_1 = std::make_shared<Tau>(
      std::make_unique<FourMomentum>(5, 5, 5, 5), DecayType::Leptonic, decay_products2);

  // Share the Tau lepton with another shared_ptr variable
  std::shared_ptr<Tau> tau_ptr_2 = tau_ptr_1;
  // and with another
  std::shared_ptr<Tau> tau_ptr_3 = tau_ptr_1;
  std::cout << "Number of owners = " << tau_ptr_1.use_count() << std::endl;
  std::cout << "Owner 1:\n--------------------------\n";
  tau_ptr_1->print();
  std::cout << "Owner 2:\n--------------------------\n";
  tau_ptr_2->print();
  std::cout << "\nOwner 3:\n--------------------------\n";
  tau_ptr_3->print();
}

// Function to output what the program does
void help()
{
  std::cout << "The test implementation  demonstrates the following features:\n\n";

  std::cout << "1. Creation of a variety of lepton objects, including electrons, muons, neutrinos, and taus. "
            << "This showcases how inheritance is used.\n\n";

  std::cout << "2. Use of smart pointers for managing particle objects. "
            << "This includes demonstrating the use of unique and shared pointers for ownership and reference management of particle instances.\n\n";

  std::cout << "3. Adding these particle objects to a vector and iterating over it to call their print functions. "
            << "This shows polymorphism in the code, particles of different types respond to the same function call in ways unique to their type.\n\n";

  std::cout << "4. Utilization of friend functions to perform operations on particle properties that are otherwise inaccessible. "
            << "This includes summing the four-vectors of two electrons and calculating the dot product of an antielectron and antimuon's four-vectors.\n\n";

  std::cout << "5. The function also demonstrates the creation and manipulation of particles using smart pointers, "
            << "such as creating a new electron with a unique pointer and transferring ownership with std::move, "
            << "and managing a tau lepton with a shared pointer to show shared ownership between multiple variables.\n\n";
}

int main()
{
  double choice;  // Variable to store initial choice input
  int int_choice; // Variable to cast to

  clear_screen();
  while(true)
  {
    std::cout << "\033[1mPlease select an option:\033[0m\n";
    std::cout << "1. Default Test Implementation\n";
    std::cout << "2. Help\n";
    std::cout << "3. End program\n";
    std::cout << "Enter your choice (1, 2, or 3): ";

    while(true)
    {
      std::cin >> choice;

      // Convert double to int for comparison and check if the input is a whole number
      int_choice = static_cast<int>(choice);

      if(std::cin.fail() || choice < 1 || choice > 3 || choice != floor(choice))
      {
        std::cout << "Invalid input, please enter 1, 2 or 3: ";
        std::cin.clear();                                                   // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to the next newline
      }
      else
      {
        break; // Exit loop if input is valid
      }
    }

    switch(int_choice)
    {
    case 1:
      print_loading_string("Selected test implementation", 4);
      clear_screen();
      test_implementation();
      std::cout << std::endl;
      break;
    case 2:
      print_loading_string("Selected Help", 4);
      clear_screen();
      help();
      break;
    case 3:
      return 0;
    default:
      std::cout << "An error occurred.\n";
    }
  }

  return 0;
}
