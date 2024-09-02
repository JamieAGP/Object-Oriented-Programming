#include "helper_functions.h"

// Functions to convert to string
std::string to_string(Colour colour)
{
  switch (colour)
  {
  case Colour::Red:
    return "Red";
  case Colour::Green:
    return "Green";
  case Colour::Blue:
    return "Blue";
  case Colour::AntiRed:
    return "AntiRed";
  case Colour::AntiGreen:
    return "AntiGreen";
  case Colour::AntiBlue:
    return "AntiBlue";
  case Colour::None:
    return "None";
  default:
    return "Unknown Colour";
  }
}
std::string to_string(DecayType decay_type)
{
  switch (decay_type)
  {
  case DecayType::Electromagnetic:
    return "Electromagnetic";
  case DecayType::Weak:
    return "Weak";
  case DecayType::Strong:
    return "Strong";
  case DecayType::None:
    return "None";
  default:
    return "Unknown Decay type";
  }
}

// Functions to assist enum classes
bool is_anti_colour(Colour colour)
{
  switch (colour)
  {
  case Colour::Red:
    return false;
  case Colour::Green:
    return false;
  case Colour::Blue:
    return false;
  case Colour::AntiRed:
    return true;
  case Colour::AntiGreen:
    return true;
  case Colour::AntiBlue:
    return true;
  case Colour::None:
    throw std::invalid_argument("Error: Cannot have AntiNone Colour");
  default:
    throw std::invalid_argument("Error: Unrecognised Colour");
  }
}
Colour get_anti_colour(Colour colour)
{
  switch (colour)
  {
  case Colour::Red:
    return Colour::AntiRed;
  case Colour::Green:
    return Colour::AntiGreen;
  case Colour::Blue:
    return Colour::AntiBlue;
  case Colour::AntiRed:
    return Colour::Red;
  case Colour::AntiGreen:
    return Colour::Green;
  case Colour::AntiBlue:
    return Colour::Blue;
  case Colour::None:
    return Colour::None;
  default:
    throw std::invalid_argument("Error: Unrecognised Colour");
  }
}
bool is_colour_neutral(Colour colour1, Colour colour2, Colour colour3)
{
  int red_count = 0;
  int blue_count = 0;
  int green_count = 0;

  if (!(colour3 == Colour::None))
  {
    for (Colour &colour : std::vector<Colour>{colour1, colour2, colour3})
    {
      switch (colour)
      {
      case Colour::Red:
        red_count++;
        break;
      case Colour::Green:
        green_count++;
        break;
      case Colour::Blue:
        blue_count++;
        break;
      case Colour::AntiRed:
        red_count--;
        break;
      case Colour::AntiGreen:
        green_count--;
        break;
      case Colour::AntiBlue:
        blue_count--;
        break;
      case Colour::None:
        break;
      default:
        throw std::invalid_argument("Error: Unrecognised Colour");
      }
    }
    if ((red_count == blue_count && blue_count == green_count))
    {
      return true;
    }
    else
      return false;
  }
  else
  {
    if (colour1 == get_anti_colour(colour2))
    {
      return true;
    }
    else
      return false;
  }
}
bool is_colour_neutral(std::vector<Colour> colour_charges)
{
  int red_count = 0;
  int blue_count = 0;
  int green_count = 0;

  if (!(colour_charges.size() == 2))
  {
    for (Colour &colour : colour_charges)
    {
      switch (colour)
      {
      case Colour::Red:
        red_count++;
        break;
      case Colour::Green:
        green_count++;
        break;
      case Colour::Blue:
        blue_count++;
        break;
      case Colour::AntiRed:
        red_count--;
        break;
      case Colour::AntiGreen:
        green_count--;
        break;
      case Colour::AntiBlue:
        blue_count--;
        break;
      case Colour::None:
        break;
      default:
        throw std::invalid_argument("Error: Unrecognised Colour");
      }
    }
    if ((red_count == blue_count && blue_count == green_count))
    {
      return true;
    }
    else
      return false;
  }
  else
  {
    if (colour_charges[0] == get_anti_colour(colour_charges[1]))
    {
      return true;
    }
    else
      return false;
  }
}

bool contains_decay_type(const std::vector<DecayType> &decay_types, DecayType type_to_find)
{
  // Iterate over the vector to check if the given type is present
  for (const auto &type : decay_types)
  {
    if (type == type_to_find)
    {
      return true;
    }
  }
  return false;
}

// Function to calculate the sum of energies of products 1 and 2 given a momentum
double energy_sum(double momentum, double product1_rest_mass, double product2_rest_mass)
{
  double E1 = sqrt(product1_rest_mass * product1_rest_mass + momentum * momentum);
  double E2 = sqrt(product2_rest_mass * product2_rest_mass + momentum * momentum);
  return E1 + E2;
}
// Function to perform the bisection method to find the momentum of two decay particles
double find_momentum_of_products(double product1_rest_mass, double product2_rest_mass, double decay_particle_rest_mass, double tolerance)
{
  double low = 0.0;
  double high = decay_particle_rest_mass;
  double mid;

  while (high - low > tolerance)
  {
    mid = (low + high) / 2;
    double total_product_energy = energy_sum(mid, product1_rest_mass, product2_rest_mass);

    if (total_product_energy > decay_particle_rest_mass)
      high = mid;
    else
      low = mid;
  }
  return (low + high) / 2;
}
// Function to calculate the sum of energies of products 1, 2, and 3 given a momentum
double energy_sum_three_body(double p1x, double p2x, double p2y, double m1, double m2, double m3)
{
  double p3x = -p1x - p2x;
  double p3y = -p2y;
  double E1 = std::sqrt(m1 * m1 + p1x * p1x);
  double E2 = std::sqrt(m2 * m2 + p2x * p2x + p2y * p2y);
  double E3 = std::sqrt(m3 * m3 + p3x * p3x + p3y * p3y);
  return E1 + E2 + E3;
}
// Function to calculate the momentum of products in a three body decay, utilising the bisection method for two body decay
std::vector<double> find_momentum_of_products_three_body(double product1_rest_mass, double product2_rest_mass, double product3_rest_mass, double decay_particle_rest_mass, double tolerance)
{
  double p1x = 0.0;
  double p2x = 0.0;
  double p2y = 0.0;
  double p3x = 0.0;
  double p3y = 0.0;

  double extra_energy = decay_particle_rest_mass - product1_rest_mass - product2_rest_mass - product3_rest_mass;
  double E1 = product1_rest_mass + extra_energy / 3;
  p1x = std::sqrt(E1 * E1 - product1_rest_mass * product1_rest_mass);

  double remaining_energy = decay_particle_rest_mass - E1;

  // Calculate the momentum magnitude of the second and third particles
  double p23_momentum = find_momentum_of_products(product2_rest_mass, product3_rest_mass, remaining_energy, tolerance);

  // Calculate the energies of the second and third particles
  double E2 = std::sqrt(product2_rest_mass * product2_rest_mass + p23_momentum * p23_momentum);
  double E3 = std::sqrt(product3_rest_mass * product3_rest_mass + p23_momentum * p23_momentum);

  // Check if the energies of the decay particles add up to the rest mass of the decaying particle
  if (std::abs(E1 + E2 + E3 - decay_particle_rest_mass) < tolerance)
  {
    p2x = -p1x / 2.0;
    p3x = p2x;
    double p23_y_component = std::sqrt(p23_momentum * p23_momentum - p2x * p2x);
    p2y = p23_y_component;
    p3y = -p23_y_component;
  }
  else
  {
    throw std::runtime_error("Error: Cannot determine 3 body decay problem momenta.");
  }
  // Return the momentum components
  return std::vector<double>{p1x, p2x, p2y, p3x, p3y};
}

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
// Function to clear input buffer
void clear_input_buffer()
{
  std::cin.clear();                                                   // Clear any error flags
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard any remaining characters in the input buffer
}
// Prints a string followed by dots
void print_loading_string(const std::string &input_string, int seconds, bool new_new_line, bool elipses)
{
  std::cout << input_string;
  for (int i = 0; i < seconds; ++i)
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (elipses)
    {
      std::cout << ".";
    }
  }
  std::cout << std::endl; // Move to a new line after printing all dots
  if (new_new_line)
  {
    std::cout << std::endl;
  }
}
// Function to pause program execution until user hits enter
void wait_for_enter(const std::string &prompt)
{
  if (prompt.empty())
  {
    std::cout << "Press Enter to continue:";
  }
  else
  {
    std::cout << prompt;
  }

  while (true)
  {
    std::string input;
    std::getline(std::cin, input); // Read a line of input

    // Check if the user pressed Enter
    if (input.empty())
    {
      break; // Exit the loop if Enter is pressed
    }
    else
    {
      break;
    }
  }
}

// Fill catalogue with leptons
void fill_leptons(ParticleCatalogue<Particle> &catalogue)
{
  Tau *tau = new Tau();
  tau->set_label("general tau");
  Electron *electron = new Electron();
  electron->set_label("general electron");
  Muon *muon = new Muon();
  muon->set_label("general muon");
  Neutrino *tau_neutrino = new Neutrino("tau");
  tau_neutrino->set_label("general tau neutrino");
  Neutrino *electron_neutrino = new Neutrino("electron");
  electron_neutrino->set_label("general electron neutrino");
  Neutrino *muon_neutrino = new Neutrino("muon");
  muon_neutrino->set_label("general muon neutrino");
  catalogue.add_particle(tau);
  catalogue.add_particle(electron);
  catalogue.add_particle(muon);
  catalogue.add_particle(tau_neutrino);
  catalogue.add_particle(electron_neutrino);
  catalogue.add_particle(muon_neutrino);
}
// Fill catalogue with antileptons
void fill_anti_leptons(ParticleCatalogue<Particle> &catalogue)
{
  Tau *anti_tau = new Tau(-1);
  anti_tau->set_label("general anti-tau");
  Electron *anti_electron = new Electron(-1);
  anti_electron->set_label("general anti-electron");
  Muon *anti_muon = new Muon(-1);
  anti_muon->set_label("general anti-muon");
  Neutrino *anti_tau_neutrino = new Neutrino("tau", -1);
  anti_tau_neutrino->set_label("general anti-tau neutrino");
  Neutrino *anti_electron_neutrino = new Neutrino("electron", -1);
  anti_electron_neutrino->set_label("general anti-electron neutrino");
  Neutrino *anti_muon_neutrino = new Neutrino("muon", -1);
  anti_muon_neutrino->set_label("general anti-muon neutrino");
  catalogue.add_particle(anti_tau);
  catalogue.add_particle(anti_electron);
  catalogue.add_particle(anti_muon);
  catalogue.add_particle(anti_tau_neutrino);
  catalogue.add_particle(anti_electron_neutrino);
  catalogue.add_particle(anti_muon_neutrino);
}
// Fill catalogue with bosons
void fill_bosons(ParticleCatalogue<Particle> &catalogue)
{
  Photon *photon = new Photon();
  photon->set_label("general photon");
  Gluon *gluon = new Gluon();
  gluon->set_label("general gluon");
  Z *z = new Z();
  z->set_label("general z");
  W *w_plus = new W();
  w_plus->set_label("general w");
  W *w_minus = new W(-1);
  w_minus->set_label("general w");
  Higgs *higgs = new Higgs();
  higgs->set_label("general higgs");
  catalogue.add_particle(photon);
  catalogue.add_particle(gluon);
  catalogue.add_particle(z);
  catalogue.add_particle(w_plus);
  catalogue.add_particle(w_minus);
  catalogue.add_particle(higgs);
}
// Fill catalogue with quarks
void fill_quarks(ParticleCatalogue<Particle> &catalogue)
{
  Up *up = new Up();
  up->set_label("general up");
  Down *down = new Down();
  down->set_label("general down");
  Bottom *bottom = new Bottom();
  bottom->set_label("general bottom");
  Charm *charm = new Charm();
  charm->set_label("general charm");
  Top *top = new Top();
  top->set_label("general top");
  Strange *strange = new Strange();
  strange->set_label("general strange");
  catalogue.add_particle(up);
  catalogue.add_particle(down);
  catalogue.add_particle(bottom);
  catalogue.add_particle(top);
  catalogue.add_particle(charm);
  catalogue.add_particle(strange);
}
// Fill catalogue with antiquarks
void fill_anti_quarks(ParticleCatalogue<Particle> &catalogue)
{
  Up *anti_up = new Up(true);
  anti_up->set_label("general anti-up");
  Down *anti_down = new Down(true);
  anti_down->set_label("general anti-down");
  Bottom *anti_bottom = new Bottom(true);
  anti_bottom->set_label("general anti-bottom");
  Charm *anti_charm = new Charm(true);
  anti_charm->set_label("general anti-charm");
  Top *anti_top = new Top(true);
  anti_top->set_label("general anti-top");
  Strange *anti_strange = new Strange(true);
  anti_strange->set_label("general anti-strange");
  catalogue.add_particle(anti_up);
  catalogue.add_particle(anti_down);
  catalogue.add_particle(anti_bottom);
  catalogue.add_particle(anti_top);
  catalogue.add_particle(anti_charm);
  catalogue.add_particle(anti_strange);
}
// Fill catalogue with particles
void fill_particles(ParticleCatalogue<Particle> &catalogue)
{
  fill_leptons(catalogue);
  fill_bosons(catalogue);
  fill_quarks(catalogue);
}
// Fill catalogue with antiparticles
void fill_anti_particles(ParticleCatalogue<Particle> &catalogue)
{
  fill_anti_leptons(catalogue);
  fill_bosons(catalogue);
  fill_anti_quarks(catalogue);
}
// Fill catalogue with all particles
void fill_catalogue(ParticleCatalogue<Particle> &catalogue)
{
  fill_particles(catalogue);
  fill_anti_leptons(catalogue);
  fill_anti_quarks(catalogue);
}

// Sort catalogue by values
void sort_by_rest_mass(ParticleCatalogue<Particle> &catalogue)
{
  catalogue.sort_particles_by_property([](const Particle *p1, const Particle *p2)
                                       { return p1->get_rest_mass() < p2->get_rest_mass(); });
}
void sort_by_charge(ParticleCatalogue<Particle> &catalogue)
{
  catalogue.sort_particles_by_property([](const Particle *p1, const Particle *p2)
                                       { return p1->get_charge() < p2->get_charge(); });
}
void sort_by_spin(ParticleCatalogue<Particle> &catalogue)
{
  catalogue.sort_particles_by_property([](const Particle *p1, const Particle *p2)
                                       { return p1->get_spin() < p2->get_spin(); });
}
void sort_by_energy(ParticleCatalogue<Particle> &catalogue)
{
  catalogue.sort_particles_by_property([](const Particle *p1, const Particle *p2)
                                       { return p1->get_four_momentum().get_energy() < p2->get_four_momentum().get_energy(); });
}
void sort_by_momentum(ParticleCatalogue<Particle> &catalogue)
{
  catalogue.sort_particles_by_property([](const Particle *p1, const Particle *p2)
                                       { return p1->get_four_momentum().get_P_magnitude() < p2->get_four_momentum().get_P_magnitude(); });
}
void sort_by_velocity(ParticleCatalogue<Particle> &catalogue)
{
  catalogue.sort_particles_by_property([](const Particle *p1, const Particle *p2)
                                       { return p1->get_four_momentum().get_velocity_magnitude() < p2->get_four_momentum().get_velocity_magnitude(); });
}
