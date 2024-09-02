#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <set>
#include <sstream>
#include <iomanip>

#include "Particle.h"
#include "Detector.h"
#include "Simulation.h"
#include "Manager.h"
#include "constants.h"

using namespace std;

const double electron_rest_mass = 0.511; // MeV - ish
const double muon_rest_mass = 105.7;     // MeV - ish

// Displays all defined detector types
void output_defined_detectors(manager system)
{
  cout << "Defined Detector Types:\n";
  auto detectors = system.get_defined_detectors();
  for (auto it = detectors.begin(); it != detectors.end(); ++it)
  {
    cout << distance(detectors.begin(), it) << ". " << it->get_type() << endl;
  }
};

// Displays all defined particle types
void output_defined_particles(manager system)
{
  cout << "Defined Particle Types:\n";
  auto particles = system.get_defined_particles();
  for (auto it = particles.begin(); it != particles.end(); ++it)
  {
    cout << distance(particles.begin(), it) << ". " << it->get_type() << endl;
  }
};

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

// Finds and returns particle object reference from given type
particle &get_particle_type_obj(const std::string &type, manager &system)
{
  auto &particles = system.get_defined_particles(); // Get a reference to the particles
  for (auto &p : particles)
  {
    if (p.get_type() == type)
    {
      return p;
    }
  }
  // If no match is found
  throw std::runtime_error("Particle of type '" + type + "' not found.");
}

// Finds and returns detector object reference from given type
detector get_detector_type_obj(string type, manager system)
{
  for (const auto &det : system.get_defined_detectors())
  {
    if (det.get_type() == type)
    {
      return det;
    }
  }
  // If no match is found
  throw runtime_error("Detector of type '" + type + "' not found.");
}

// Adds a new particle type to the system, if it doesn't already exist
void manager::add_particle_type(string type, double rest_mass, int charge)
{
  // Check if the particle type already exists
  for (const auto &particle : defined_particles)
  {
    if (particle.get_type() == type)
    {
      cout << "A particle type with the name '" << type << "' already exists. No new particle added." << endl;
      return; // Exit the function to prevent adding a duplicate particle
    }
  }

  // If the particle type does not exist, create a new particle instance
  particle new_particle(type, rest_mass, charge);
  defined_particles.push_back(new_particle);
  cout << "New particle type '" << type << "' added successfully.\n"
       << endl;
}

// Adds a new detector type to the system, if it doesn't already exist
void manager::add_detector_type(string type, map<string, double> particle_efficiencies)
{
  // Check if the detector type already exists
  for (const auto &detector : defined_detectors)
  {
    if (detector.get_type() == type)
    {
      cout << "A detector type with the name '" << type << "' already exists. No new detector added." << endl;
      return; // Exit the function to prevent adding a duplicate detector
    }
  }

  // If the detector type does not exist, create a new particle instance
  detector new_detector(type, particle_efficiencies);
  defined_detectors.push_back(new_detector);
  cout << "New detector type '" << type << "' added successfully.\n"
       << endl;
}

// Prints all information about a particle type
void particle::print_info()
{
  cout << "Particle Type Info:" << endl;
  cout << "Type: " << get_type() << endl;
  cout << "Charge (e): " << get_charge() << endl;
  cout << "Rest Mass (MeV): " << get_rest_mass() << endl;
}

// Prints all information about a specific particle instance
void particle_instance::print_info()
{
  cout << "Particle Instance Info:" << endl;
  cout << "Type: " << get_type() << endl;
  cout << "Charge (e): " << get_charge() << endl;
  cout << "Rest Mass (MeV): " << get_rest_mass() << endl;
  cout << "Velocity (m/s): " << get_velocity() << endl;
  cout << "Beta (v/c): " << get_beta() << endl;
}

// Prints all information about a detector type
void detector::print_info()
{
  cout << "Detector Type Info:" << endl;
  cout << "Type: " << get_type() << endl;
  cout << "Particle Efficiencies(0-1):\n";
  for (const auto &pair : get_particle_efficiencies())
  {
    cout << pair.first << ": " << pair.second << endl;
  }
}

// Prints all information about a specific detector instance
void detector_instance::print_info()
{
  cout << "Detector Instance Info:" << endl;
  cout << "Type: " << get_type() << endl;
  cout << "Status: " << (get_status() ? "On" : "Off") << endl;
  cout << "Tracked Particles: " << get_particles_tracked().size() << endl;
  cout << "Particle Efficiencies(0-1):\n";
  for (const auto &pair : get_particle_efficiencies())
  {
    cout << pair.first << ": " << pair.second << endl;
  }
}

// Runs a simulation, displaying included detectors and particles,
// and shows which detectors detected which particles
void simulation::run_simulation()
{
  cout << "\033[1mRunning simulation\033[0m\n"
       << "Detectors included:\n";
  for (size_t i = 0; i < detectors.size(); ++i)
  {
    cout << i + 1 << ". " << detectors[i].get_type() << endl;
  }
  cout << std::endl
       << "Particles included:\n";
  for (size_t i = 0; i < particles.size(); ++i)
  {
    cout << i + 1 << ". " << particles[i].get_type() << endl;
  }
  cout << std::endl;

  srand(static_cast<unsigned int>(time(nullptr)));

  // Iterate over each particle in the simulation
  for (size_t i = 0; i < particles.size(); ++i)
  {
    vector<detector_instance *> detected_by, not_detected_by; // Track which detectors detected the particle

    // Iterate over each detector
    for (auto &detector : detectors)
    {
      map<string, double> efficiencies = detector.get_particle_efficiencies();
      auto it = efficiencies.find(particles[i].get_type());

      if (detector.get_status() == 0)
      {
        not_detected_by.push_back(&detector);
      }
      else if (it != efficiencies.end())
      {
        double randValue = static_cast<double>(rand()) / RAND_MAX;
        if (randValue < it->second)
        { // Particle is detected
          detector.track_particle(&particles[i]);
          detected_by.push_back(&detector);
        }
        else
        {
          not_detected_by.push_back(&detector);
        }
      }
    }

    // Output results for each particle
    cout << "Particle " << i + 1 << ": " << particles[i].get_type() << " (" << particles[i].get_velocity() << " m/s  - " << fixed << setprecision(3) << particles[i].get_beta() <<"c)";
    if (!detected_by.empty())
    {
      cout << ", detected by ";
      for (auto it = detected_by.begin(); it != detected_by.end();)
      {
        cout << (*it)->get_type();
        if (++it != detected_by.end())
          cout << ", ";
      }
    }

    if (!not_detected_by.empty())
    {
      cout << ", not detected by ";
      for (auto it = not_detected_by.begin(); it != not_detected_by.end();)
      {
        cout << (*it)->get_type();
        if (++it != not_detected_by.end())
          cout << ", ";
      }
    }
    cout << "." << endl;
  }

  // Output the results for each detector_instance
  for (size_t i = 0; i < detectors.size(); ++i)
  {
    cout << "Detector " << i + 1 << ". " << detectors[i].get_type() << " - detected " << detectors[i].get_particles_tracked().size() << " particles.\n";
  }
  cout << endl;
}

// Tests the implementation by running simulations with predefined
// particle and detector instances.
void test_implementation(manager system)
{
  clear_screen();
  vector<particle_instance> test_particles_instances;
  // Add particles specified in assignment to simulation
  test_particles_instances.push_back(particle_instance(get_particle_type_obj("electron", system), 100));
  test_particles_instances.push_back(particle_instance(get_particle_type_obj("electron", system), 96));

  test_particles_instances.push_back(particle_instance(get_particle_type_obj("muon", system), 3));
  test_particles_instances.push_back(particle_instance(get_particle_type_obj("muon", system), 4));
  test_particles_instances.push_back(particle_instance(get_particle_type_obj("muon", system), 5));
  test_particles_instances.push_back(particle_instance(get_particle_type_obj("muon", system), 0));

  test_particles_instances.push_back(particle_instance(get_particle_type_obj("antielectron", system), 4));
  test_particles_instances.push_back(particle_instance(get_particle_type_obj("antimuon", system), 1000));

  // Create simulation for each type of detector
  simulation tracker_test_sim = simulation({detector_instance(get_detector_type_obj("tracker", system), 1)}, test_particles_instances);
  simulation calorimeter_test_sim = simulation({detector_instance(get_detector_type_obj("calorimeter", system), 1)}, test_particles_instances);
  simulation muon_chamber_test_sim = simulation({detector_instance(get_detector_type_obj("muon chamber", system), 1)}, test_particles_instances);

  // Create simulation including all detector types for showcase
  simulation all = simulation({detector_instance(get_detector_type_obj("tracker", system), 1),
                               detector_instance(get_detector_type_obj("tracker", system), 1),
                               detector_instance(get_detector_type_obj("muon chamber", system), 1)},
                              test_particles_instances);

  clear_screen();
  tracker_test_sim.run_simulation();
  calorimeter_test_sim.run_simulation();
  muon_chamber_test_sim.run_simulation();
  all.run_simulation();
};

// Prompts the user for a yes/no input and returns true for yes and
// false for no
bool get_yes_no_input(const string &prompt)
{
  string input;
  while (true)
  {
    cout << prompt << " (yes/y/no/n): ";
    getline(cin, input);
    if (input == "yes" || input == "y")
    {
      return true;
    }
    else if (input == "no" || input == "n")
    {
      return false;
    }
    else
    {
      cout << "Invalid input. Please enter 'yes', 'y', 'no', or 'n'." << endl;
    }
  }
}

// Prompts the user for an on/off input and returns true for on and
// false for off
bool get_on_off_input(const string &prompt)
{
  string input;
  while (true)
  {
    cout << prompt << " (on/off): ";
    getline(cin, input);
    if (input == "on")
    {
      return true;
    }
    else if (input == "off")
    {
      return false;
    }
    else
    {
      cout << "Invalid input. Please enter 'on' or 'off'." << endl;
    }
  }
}

// Ensures the user inputs a valid velocity within a specified range
// and returns it.
double get_valid_velocity()
{
  string input;
  double velocity;

  while (true)
  {
    cout << "Enter the velocity of the particle in m/s (positive, <= speed of light): ";
    getline(cin, input); // Get the entire line of input as a string

    stringstream stream(input);
    stream >> velocity;

    // Check if the input is numeric and less than the speed of light, and if there's anything left in the input stream after reading the number
    if (!stream.fail() && stream.eof() && velocity >= 0 && velocity <= speed_of_light)
    {
      return velocity;
    }
    else
    {
      // Clear the error flags and ignore the rest of the line if the input is invalid
      cin.clear();
      cout << "Invalid velocity. Please enter a positive number that is less than or equal to the speed of light (" << speed_of_light << " m/s)." << endl;
    }
  }
}

// Allows the user to customize the simulation by selecting detectors
// and particles to include in the simulation.
void custom_usage(manager system)
{
  clear_screen();
  cout << "\n\033[1mChoose Defined Detectors to include in simulation\033[0m\n";
  output_defined_detectors(system);

  vector<detector_instance> selected_detector_instances;
  string detector_type;
  bool add_more = true;

  while (add_more)
  {
    cout << "Enter the type of the detector you want to add (e.g., tracker): ";
    cin >> ws;
    getline(cin, detector_type);

    // Attempt to find a detector by type
    bool found = false;
    for (const auto &det : system.get_defined_detectors())
    {
      if (det.get_type() == detector_type)
      {
        bool status = get_on_off_input("Enter the status of the detector");
        selected_detector_instances.push_back(detector_instance(det, status));
        found = true;
        break; // Exit loop after finding and adding the detector
      }
    }

    if (!found)
    {
      cout << "Detector type '" << detector_type << "' not found. Please try again.\n";
    }
    else
    {
      add_more = get_yes_no_input("Do you want to add more detectors?");
    }
  }

  cout << "\n\033[1mChoose Defined Particles to include in simulation\033[0m\n";
  output_defined_particles(system);

  vector<particle_instance> selected_particle_instances;
  string particle_type;
  add_more = true;

  while (add_more)
  {
    cout << "Enter the type of the particle you want to add (e.g., electron): ";
    cin >> ws;
    getline(cin, particle_type);

    // Attempt to find a particle by type
    bool found = false;
    for (const auto &p : system.get_defined_particles())
    {
      if (p.get_type() == particle_type)
      {
        double velocity = get_valid_velocity();
        selected_particle_instances.push_back(particle_instance(p, velocity));
        found = true;
        break; // Exit loop after finding and adding the particle
      }
    }

    if (!found)
    {
      cout << "Particle type '" << particle_type << "' not found. Please try again.\n";
    }
    else
    {
      add_more = get_yes_no_input("Do you want to add more particles?");
    }
  }

  // Proceed with the simulation once detectors and particle selected
  cout << endl;
  simulation sim(selected_detector_instances, selected_particle_instances);
  sim.run_simulation();
}

// Interface function for adding a new particle type, including input
// validation for the particle's charge and rest mass.
void add_particle_type_interface(manager &system)
{
  string type;
  string input;
  int charge;
  double rest_mass;

  cout << "\n\033[1mAdding new particle type\033[0m\n";
  cout << "Enter particle name: ";
  cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore any newline left in the input stream
  getline(cin, type);

  cout << "Enter particle charge (in integer units of e): ";
  while (true)
  {
    getline(cin, input);
    stringstream input_stream(input);
    double temp_charge;
    input_stream >> temp_charge;
    if (!input_stream.fail() && input_stream.eof() && temp_charge == floor(temp_charge))
    {
      charge = static_cast<int>(temp_charge);
      break;
    }
    else
    {
      cout << "Invalid input. Please enter a valid integer for charge: ";
    }
  }

  cout << "Enter particle rest mass (MeV): ";
  while (true)
  {
    getline(cin, input);
    stringstream input_stream(input);
    input_stream >> rest_mass;
    if (!input_stream.fail() && input_stream.eof() && rest_mass >= 0)
    {
      break;
    }
    else
    {
      cout << "Invalid input. Please enter a valid number for rest mass: ";
    }
  }

  system.add_particle_type(type, rest_mass, charge);
}

// Allows the user to view individual particle information or add a
// new particle type, and returns to the edit menu.
void edit_particles(manager &system)
{
  cout << endl;
  double choice;  // Variable to store initial choice input
  int int_choice; // Variable to cast to
  clear_screen();
  while (true)
  {
    cout << "\033[1mPlease select an option:\033[0m\n";
    cout << "1. View individual particle information\n";
    cout << "2. Add new particle type\n";
    cout << "3. Return to edit menu\n";
    cout << "Enter your choice (1, 2 or 3): ";

    while (true)
    {
      cin >> choice;

      // Convert double to int for comparison and check if the input is a whole number
      int_choice = static_cast<int>(choice);

      if (cin.fail() || choice < 1 || choice > 3 || choice != floor(choice))
      {
        cout << "Invalid input, please enter 1, 2 or 3: ";
        cin.clear();                                         // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip to the next newline
      }
      else
      {
        break; // Exit loop if input is valid
      }
    }

    switch (int_choice)
    {
    case 1:
      cout << "\n\033[1mDefined Particle Types:\033[0m\n";
      for (auto &particle : system.get_defined_particles())
      {
        particle.print_info();
        cout << "-----------------------\n";
      }
      cout << endl;
      break;
    case 2:
      add_particle_type_interface(system);
      break;
    case 3:
      clear_screen();
      return;
    default:
      std::cout << "An error occurred.\n";
    }
  }
  return;
}

// Interface function for adding a new detector type, initializing
// efficiencies for all defined particles to zero and updating based
// on user input.
void add_detector_type_interface(manager &system)
{
  string type;
  map<string, double> particle_efficiencies;
  string particle_name;
  double efficiency;
  char continueInput = 'y';

  // Initialize particle efficiencies to 0 for all defined particles
  auto defined_particles = system.get_defined_particles();
  for (const auto &p : defined_particles)
  {
    particle_efficiencies[p.get_type()] = 0.0;
  }

  cout << "\n\033[1mAdding new detector type\033[0m\n";
  cout << "Enter detector name: ";
  cin >> ws; // Clear any leading whitespace
  getline(cin, type);

  do
  {
    cout << "Enter particle name that new detector can detect: ";
    cin >> ws;
    getline(cin, particle_name);

    // Check if the particle exists in defined_particles
    if (particle_efficiencies.find(particle_name) == particle_efficiencies.end())
    {
      cout << "Warning: '" << particle_name << "' is not a defined particle. Efficiency set to 0." << endl;
      continue; // Continue with the next iteration
    }

    cout << "Enter detector's efficiency for " << particle_name << " (0.0 to 1.0): ";
    while (!(cin >> efficiency) || efficiency < 0.0 || efficiency > 1.0)
    {
      cout << "Invalid efficiency. Please enter a value between 0.0 and 1.0: ";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard input
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any remaining input

    // Update the efficiency for the specified particle
    particle_efficiencies[particle_name] = efficiency;

    cout << "Do you want to add another particle? (y/n): ";
    cin >> continueInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard newline character after y/n input

  } while (continueInput == 'y' || continueInput == 'Y');

  // Add the detector with updated efficiencies
  system.add_detector_type(type, particle_efficiencies);
}

// Allows the user to view individual detector information or add a new
// detector type, and returns to the edit menu
void edit_detectors(manager &system)
{
  cout << endl;
  double choice;  // Variable to store initial choice input
  int int_choice; // Variable to cast to
  clear_screen();
  while (true)
  {
    cout << "\033[1mPlease select an option:\033[0m\n";
    cout << "1. View individual detector information\n";
    cout << "2. Add new detector type\n";
    cout << "3. Return to edit menu\n";
    cout << "Enter your choice (1, 2 or 3): ";

    while (true)
    {
      cin >> choice;

      // Convert double to int for comparison and check if the input is a whole number
      int_choice = static_cast<int>(choice);

      if (cin.fail() || choice < 1 || choice > 3 || choice != floor(choice))
      {
        cout << "Invalid input, please enter 1, 2 or 3: ";
        cin.clear();                                         // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip to the next newline
      }
      else
      {
        break; // Exit loop if input is valid
      }
    }

    switch (int_choice)
    {
    case 1:
      cout << "\n\033[1mDefined Detector Types:\033[0m\n";
      for (auto &detector : system.get_defined_detectors())
      {
        detector.print_info();
        cout << "-----------------------\n";
      }
      break;
    case 2:
      add_detector_type_interface(system);
      break;
    case 3:
      clear_screen();
      return;
    default:
      std::cout << "An error occurred.\n";
    }
  }
  return;
}

// Presents an edit menu for the user to choose between viewing/editing
// defined particles or detectors, or returning to the main menu.
void edit_menu(manager &system)
{
  // Code to choose whether user wants to see test implementation or custom use
  double choice;  // Variable to store initial choice input
  int int_choice; // Variable to cast to
  clear_screen();
  while (true)
  {
    cout << "\033[1mPlease select an option:\033[0m\n";
    cout << "1. View/edit defined particles\n";
    cout << "2. View/edit defined detectors\n";
    cout << "3. Return to main menu\n";
    cout << "Enter your choice (1, 2 or 3): ";

    while (true)
    {
      cin >> choice;

      // Convert double to int for comparison and check if the input is a whole number
      int_choice = static_cast<int>(choice);

      if (cin.fail() || choice < 1 || choice > 3 || choice != floor(choice))
      {
        cout << "Invalid input, please enter 1, 2 or 3: ";
        cin.clear();                                         // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip to the next newline
      }
      else
      {
        break; // Exit loop if input is valid
      }
    }

    switch (int_choice)
    {
    case 1:
      edit_particles(system);
      break;
    case 2:
      edit_detectors(system);
      break;
    case 3:
      clear_screen();
      return;
    default:
      std::cout << "An error occurred.\n";
    }
  }
}

void display_help_text()
{
  cout << "\033[1mHELP SECTION: Program Description\033[0m\n\n"
       << "This simulation program is designed for testing particle detection systems. It includes three components, particles, detectors, and simulations. These work together to demonstrate how different detectors interact with various types of particles. The user can choose which particles and detectors take part in a given simulation.\n\n"
       << "\033[1mTest Implementation:\033[0m\n"
       << "- The test implementation runs predefined simulations using the set of particles and detectors, indicated in the project assignment,to demonstrate how the system functions. This mode automatically configures the simulation with specific particles and detectors to show how particles are detected or missed based on the detector’s efficiency and type.\n\n"
       << "\033[1mCustom Usage:\033[0m\n"
       << "- In the custom usage mode, users have the ability to define their own particles and detectors, including specifying the efficiency of detectors in detecting certain particles. Users can choose from predefined particle types or add new ones, specify their properties (like rest mass and charge), and do the same for detectors. The user can also specify the velocity of individual particles in this mode. This mode works with different simulation setups and shows the full capabilities of the program.\n\n"
       << "The program provides options for adding, editing, and viewing the properties of particles and detectors, allowing users to fully customize their simulation experience.\n\n"
       << "To navigate back to the main menu and start the simulation, select the appropriate option from the list provided in the main menu.\n\n";
}

int main()
{
  manager system = manager();
  // Predefine some particles
  system.add_particle_type("electron", electron_rest_mass, -1);
  system.add_particle_type("muon", muon_rest_mass, -1);
  system.add_particle_type("antielectron", electron_rest_mass, +1);
  system.add_particle_type("antimuon", muon_rest_mass, +1);
  // Predfine some detectors
  system.add_detector_type("tracker", {{"electron", 1}, {"muon", 1}, {"antielectron", 1}, {"antimuon", 1}});
  system.add_detector_type("calorimeter", {{"electron", 1}, {"muon", 0}, {"antielectron", 1}, {"antimuon", 0}});
  system.add_detector_type("muon chamber", {{"electron", 0}, {"muon", 1}, {"antielectron", 0}, {"antimuon", 1}});

  // Code to choose whether user wants to see test implementation or custom use
  double choice;  // Variable to store initial choice input
  int int_choice; // Variable to cast to
  clear_screen();
  while (true)
  {
    cout << "\033[1mPlease select an option:\033[0m\n";
    cout << "1. Default Test Implementation\n";
    cout << "2. Custom Usage\n";
    cout << "3. Edit defined detectors and particles\n";
    cout << "4. Help\n";
    cout << "5. End program\n";
    cout << "Enter your choice (1, 2, 3, 4 or 5): ";

    while (true)
    {
      cin >> choice;

      // Convert double to int for comparison and check if the input is a whole number
      int_choice = static_cast<int>(choice);

      if (cin.fail() || choice < 1 || choice > 5 || choice != floor(choice))
      {
        cout << "Invalid input, please enter 1, 2, 3, 4 or 5: ";
        cin.clear();                                         // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip to the next newline
      }
      else
      {
        break; // Exit loop if input is valid
      }
    }

    switch (int_choice)
    {
    case 1:
      test_implementation(system);
      break;
    case 2:
      custom_usage(system);
      break;
    case 3:
      edit_menu(system);
      break;
    case 4:
      clear_screen();
      display_help_text();
      break;
    case 5:
      return 0;
    default:
      std::cout << "An error occurred.\n";
    }
  }
}
