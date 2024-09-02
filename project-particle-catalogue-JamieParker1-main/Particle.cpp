// Lepton.cpp
#include "Particle.h"
#include "FourMomentum.h"
#include "helper_functions.h"
#include <iostream>  // For std::cout
#include <stdexcept> // For std::invalid_argument
#include <iomanip>

namespace Mass
{
  double string_to_mass(const std::string &particle)
  {
    static const std::map<std::string, double> mass_map = {
        {"electron", electron},
        {"muon", muon},
        {"tau", tau},
        {"electron_neutrino", electron_neutrino},
        {"muon_neutrino", muon_neutrino},
        {"tau_neutrino", tau_neutrino},
        {"neutrino", neutrino},
        {"w", w},
        {"z", z},
        {"higgs", higgs},
        {"up", up},
        {"down", down},
        {"charm", charm},
        {"bottom", bottom},
        {"top", top},
        {"strange", strange},
        {"gluon", gluon},
        {"photon", photon}};

    auto it = mass_map.find(particle);
    if (it != mass_map.end())
    {
      return it->second;
    }
    else
    {
      throw std::invalid_argument("Unknown particle");
    }
  }
}

// Default constructor
Particle::Particle() : type("particle"), label("General Particle"), charge(0), rest_mass(1), four_momentum(std::make_unique<FourMomentum>(1, 0, 0, 0, true)), possible_decay_types(std::vector<DecayType>{DecayType::None}) {}

// Protected constructor without label with four-momentum
Particle::Particle(std::string type, double charge, double spin, double rest_mass, std::unique_ptr<FourMomentum> four_momentum, std::vector<DecayType> possible_decay_types)
    : type(type), charge(charge), spin(spin), rest_mass(rest_mass), four_momentum(std::move(four_momentum)), possible_decay_types(possible_decay_types)
{
  if (four_momentum->get_energy() <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
  else if (is_invariant_mass_valid(four_momentum->invariant_mass()))
  {
    this->four_momentum = std::move(four_momentum);
  }
  else
  {
    throw std::invalid_argument("Rest mass does not match the invariant mass of the provided FourMomentum.");
  }
}

// Protected constructor with label with four-momentum
Particle::Particle(std::string type, const std::string &label, double charge, double spin, double rest_mass, std::unique_ptr<FourMomentum> four_momentum, std::vector<DecayType> possible_decay_types)
    : type(type), label(label), spin(spin), charge(charge), rest_mass(rest_mass), possible_decay_types(possible_decay_types)
{
  if (four_momentum->get_energy() <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
  else if (is_invariant_mass_valid(four_momentum->invariant_mass()))
  {
    this->four_momentum = std::move(four_momentum);
  }
  else
  {
    throw std::invalid_argument("Rest mass does not match the invariant mass of the provided FourMomentum.");
  }
}
// Constructor without label without four-momentum
Particle::Particle(std::string type, double charge, double spin, double rest_mass, std::vector<DecayType> possible_decay_types)
    : type(type), charge(charge), spin(spin), rest_mass(rest_mass), four_momentum((rest_mass > 0) ? std::make_unique<FourMomentum>(rest_mass, 0, 0, 0, true) : std::make_unique<FourMomentum>(1, 0, 0, 1)), possible_decay_types(possible_decay_types) {}

// Constructor with label without four-momentum
Particle::Particle(std::string type, const std::string &label, double charge, double spin, double rest_mass, std::vector<DecayType> possible_decay_types)
    : type(type), label(label), charge(charge), spin(spin), rest_mass(rest_mass), four_momentum((rest_mass > 0) ? std::make_unique<FourMomentum>(rest_mass, 0, 0, 0, true) : std::make_unique<FourMomentum>(1, 0, 0, 1)), possible_decay_types(possible_decay_types) {}

// Copy constructor
Particle::Particle(const Particle &other)
    : label(other.label), charge(other.charge), spin(other.spin),
      four_momentum(other.four_momentum ? std::make_unique<FourMomentum>(*other.four_momentum) : nullptr)
{
  decay_products.reserve(other.decay_products.size());
  for (const auto &particle : other.decay_products)
  {
    decay_products.push_back(particle ? std::make_unique<Particle>(*particle) : nullptr);
  }
}

// Move constructor
Particle::Particle(Particle &&other) noexcept
    : label(std::move(other.label)), charge(other.charge), spin(other.spin), four_momentum(std::move(other.four_momentum)), decay_products(std::move(other.decay_products)) {}

// Virtual destructor
Particle::~Particle() {}

// Copy assignment operator
Particle &Particle::operator=(const Particle &other)
{
  if (this != &other)
  {
    label = other.label;
    charge = other.charge;
    spin = other.spin;
    rest_mass = other.rest_mass;
    type = other.type;
    four_momentum = other.four_momentum ? std::make_unique<FourMomentum>(*other.four_momentum) : nullptr;
    decay_products.clear();
    decay_products.reserve(other.decay_products.size());
    for (const auto &particle : other.decay_products)
    {
      decay_products.push_back(particle ? std::make_unique<Particle>(*particle) : nullptr);
    }
  }
  return *this;
}

// Move assignment operator
Particle &Particle::operator=(Particle &&other) noexcept
{
  if (this != &other)
  {
    label = std::move(other.label);
    charge = other.charge;
    spin = other.spin;
    rest_mass = other.rest_mass;
    type = other.type;
    four_momentum = std::move(other.four_momentum);
    decay_products = std::move(other.decay_products);
  }
  return *this;
}

// Setters
void Particle::set_label(const std::string &label)
{
  this->label = label;
}

void Particle::set_four_momentum(std::unique_ptr<FourMomentum> four_momentum)
{
  if (four_momentum->get_energy() <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
  else if (is_invariant_mass_valid(four_momentum->invariant_mass()))
  {
    this->four_momentum = std::move(four_momentum);
    if (!decay_products.empty())
    {
      auto_set_decay_products(std::move(decay_products), current_decay_type);
    }
  }
  else
  {
    throw std::invalid_argument("Rest mass does not match the invariant mass of the provided FourMomentum.");
  }
}

void Particle::set_decay_products(std::vector<std::unique_ptr<Particle>> decay_products, DecayType decay_type)
{
  if (!contains_decay_type(possible_decay_types, decay_type))
  {
    std::cerr << "Error: Particle cannot decay via that path\n";
  }
  else if (validate_decay_products(decay_products, decay_type))
  {
    this->current_decay_type = decay_type;
    this->decay_products = std::move(decay_products);
  }
  else
  {
    std::cerr << "Decay products validation failed." << std::endl;
  }
}

void Particle::auto_set_decay_products(std::vector<std::unique_ptr<Particle>> decay_products, DecayType decay_type)
{
  if (decay_type == DecayType::None)
  {
    return;
  }
  if (!contains_decay_type(possible_decay_types, decay_type))
  {
    std::cerr << "Error: Particle cannot decay via that path\n";
    return;
  }

  if (decay_products.size() == 2)
  {
    // Work in decaying particle's rest frame
    // Only energy in system is decaying particle's rest mass
    if (!(rest_mass > (decay_products[0]->get_rest_mass() + decay_products[1]->get_rest_mass())))
    {
      if (decay_products[0]->get_is_virtual() && decay_products[1]->get_is_virtual())
      {
        auto_set_decay_products_virtual(std::move(decay_products), decay_type);
        return;
      }
      else
      {
        throw std::invalid_argument("Error: Rest masses of decay particles exceeds decaying particle's. Decay products must be virtual.");
      }
    }

    // Arbitrarily choose, in rest frame, decaying particles move along x axis
    // E1^2 = P1^2 + M1^2, E2^2 = P2^2 + M2^2 (P1^2 = P2^2 = P^2, E1+E2=M_particle)
    // sqrt(P^2 + M1^2) + sqrt(P^2 + M2^2) = M_particle
    double product1_rest_mass = decay_products[0]->get_rest_mass();
    double product2_rest_mass = decay_products[1]->get_rest_mass();

    // Calculate magnitude of momentum for decay products
    double product_px_magnitude;
    if (is_virtual)
    {
      product_px_magnitude = find_momentum_of_products(product1_rest_mass, product2_rest_mass, four_momentum->invariant_mass());
    }
    else
    {
      product_px_magnitude = find_momentum_of_products(product1_rest_mass, product2_rest_mass, rest_mass);
    }
    // double product_px_magnitude = find_momentum_of_products(product1_rest_mass, product2_rest_mass, four_momentum->get_energy());
    double product1_energy = std::sqrt(product1_rest_mass * product1_rest_mass + product_px_magnitude * product_px_magnitude);
    double product2_energy = std::sqrt(product2_rest_mass * product2_rest_mass + product_px_magnitude * product_px_magnitude);

    // Have first particle move +ve along x axis
    std::unique_ptr<FourMomentum> product1_fm = std::make_unique<FourMomentum>(product1_energy, product_px_magnitude, 0, 0);
    // Have second particle move -ve along x axis
    std::unique_ptr<FourMomentum> product2_fm = std::make_unique<FourMomentum>(product2_energy, -product_px_magnitude, 0, 0);

    // Find velocity of decaying particle to perform lorentz boost
    std::vector<long double> negative_decaying_particle_velocity = four_momentum->get_velocity_vector(false);

    // Perform lorentz boost on rest-frame four momentums by performing lorentz boost by substracting
    // the decaying particles velocity, back to lab frame
    product1_fm->lorentz_boost(negative_decaying_particle_velocity);
    product2_fm->lorentz_boost(negative_decaying_particle_velocity);
    // Give decay particles their four momenta
    decay_products[0]->set_four_momentum(std::move(product1_fm));
    decay_products[1]->set_four_momentum(std::move(product2_fm));
    // Validate these auto products
    if (validate_decay_products(decay_products, decay_type))
    {
      this->current_decay_type = decay_type;
      this->decay_products = std::move(decay_products);
    }
    else
    {
      std::cerr << "Error: Auto-set decay products failed. A value is not conserved.\n";
      return;
    }
  }
  else if (decay_products.size() == 3)
  {
    // Work in decaying particle's rest frame
    // Only energy in system is decaying particle's rest mass
    if (!(rest_mass > (decay_products[0]->get_rest_mass() + decay_products[1]->get_rest_mass() + decay_products[2]->get_rest_mass())))
    {
      if (decay_products[0]->get_is_virtual() && decay_products[1]->get_is_virtual() && decay_products[2]->get_is_virtual())
      {
        auto_set_decay_products_virtual(std::move(decay_products), decay_type);
        return;
      }
      else
      {
        throw std::invalid_argument("Error: Rest masses of decay particles exceeds decaying particle's. Decay products must be virtual.");
      }
    }

    // Arbitrarily choose, in rest frame, first decaying particle moves along x axis
    // Other two move 120 degrees away from x axis in x-y plane
    // E1^2 = P1X^2 + M1^2
    // E2^2 = P2X^2 + P2Y^2 + M2^2
    // E3^2 = P3X^2 + P3Y^2 + M3^2
    // E1 + E2 + E3 = M_particle
    // E1 >= M1, E2 >= M2, E3 >= M3,
    // P2X + P3X = -P1X
    // P2Y = - P3Y
    // sqrt(P1X^2 + M1^2) + sqrt(P2X^2 + P2Y^2 + M2^2) + sqrt(P3X^2 + P3Y^2 + M3^2) = M_particle

    double product1_rest_mass = decay_products[0]->get_rest_mass();
    double product2_rest_mass = decay_products[1]->get_rest_mass();
    double product3_rest_mass = decay_products[2]->get_rest_mass();

    // Calculate magnitude of momentum for decay products
    std::vector<double> momenta;
    if (is_virtual)
    {
      momenta = find_momentum_of_products_three_body(product1_rest_mass, product2_rest_mass, product3_rest_mass, four_momentum->invariant_mass());
    }
    else
    {
      momenta = find_momentum_of_products_three_body(product1_rest_mass, product2_rest_mass, product3_rest_mass, rest_mass);
    }
    // Find momenta of decay particles in x-y plane: p1x, p2x, p2y, p3x, p3y
    // Access the momentum components
    double p1x = momenta[0];
    double p2x = momenta[1];
    double p2y = momenta[2];
    double p3x = momenta[3];
    double p3y = momenta[4];

    double product1_energy = std::sqrt(product1_rest_mass * product1_rest_mass + p1x * p1x);
    double product2_energy = std::sqrt(product2_rest_mass * product2_rest_mass + p2x * p2x + p2y * p2y);
    double product3_energy = std::sqrt(product3_rest_mass * product3_rest_mass + p3x * p3x + p3y * p3y);

    std::unique_ptr<FourMomentum> product1_fm = std::make_unique<FourMomentum>(product1_energy, p1x, 0, 0);
    std::unique_ptr<FourMomentum> product2_fm = std::make_unique<FourMomentum>(product2_energy, p2x, p2y, 0);
    std::unique_ptr<FourMomentum> product3_fm = std::make_unique<FourMomentum>(product3_energy, p3x, p3y, 0);

    std::vector<long double> negative_decaying_particle_velocity = four_momentum->get_velocity_vector(false);
    product1_fm->lorentz_boost(negative_decaying_particle_velocity);
    product2_fm->lorentz_boost(negative_decaying_particle_velocity);
    product3_fm->lorentz_boost(negative_decaying_particle_velocity);

    decay_products[0]->set_four_momentum(std::move(product1_fm));
    decay_products[1]->set_four_momentum(std::move(product2_fm));
    decay_products[2]->set_four_momentum(std::move(product3_fm));

    // Validate these auto products
    if (validate_decay_products(decay_products, decay_type))
    {
      this->current_decay_type = decay_type;
      this->decay_products = std::move(decay_products);
    }
    else
    {
      std::cerr << "Error: Auto-set decay products failed. A value is not conserved.\n";
      return;
    }
  }
  return;
}

void Particle::auto_set_decay_products_virtual(std::vector<std::unique_ptr<Particle>> decay_products, DecayType decay_type)
{

  if (decay_products.size() == 2)
  {
    // Get the energy and momentum of the decaying particle in the lab frame
    double decaying_particle_energy = four_momentum->get_energy();
    double decaying_particle_px = four_momentum->get_Px();
    double decaying_particle_py = four_momentum->get_Py();
    double decaying_particle_pz = four_momentum->get_Pz();

    // Split the energy and momentum equally between the two decay products
    double product1_energy = decaying_particle_energy / 2;
    double product1_px = decaying_particle_px / 2;
    double product1_py = decaying_particle_py / 2;
    double product1_pz = decaying_particle_pz / 2;

    double product2_energy = decaying_particle_energy / 2;
    double product2_px = decaying_particle_px / 2;
    double product2_py = decaying_particle_py / 2;
    double product2_pz = decaying_particle_pz / 2;

    // Create the four-momenta for the decay products in the lab frame
    std::unique_ptr<FourMomentum> product1_fm = std::make_unique<FourMomentum>(product1_energy, product1_px, product1_py, product1_pz);
    std::unique_ptr<FourMomentum> product2_fm = std::make_unique<FourMomentum>(product2_energy, product2_px, product2_py, product2_pz);

    // Give decay particles their four-momenta
    decay_products[0]->set_four_momentum(std::move(product1_fm));
    decay_products[1]->set_four_momentum(std::move(product2_fm));

    // Validate these auto products
    if (validate_decay_products(decay_products, decay_type))
    {
      this->current_decay_type = decay_type;
      this->decay_products = std::move(decay_products);
    }
    else
    {
      std::cerr << "Error: Auto-set decay products failed. A value is not conserved.\n";
      return;
    }
  }
  else if (decay_products.size() == 3)
  {
    // Get the energy and momentum of the decaying particle in the lab frame
    double decaying_particle_energy = four_momentum->get_energy();
    double decaying_particle_px = four_momentum->get_Px();
    double decaying_particle_py = four_momentum->get_Py();
    double decaying_particle_pz = four_momentum->get_Pz();

    // Split the energy and momentum equally between the two decay products
    double product1_energy = decaying_particle_energy / 2;
    double product1_px = decaying_particle_px / 3;
    double product1_py = decaying_particle_py / 3;
    double product1_pz = decaying_particle_pz / 3;

    double product2_energy = decaying_particle_energy / 3;
    double product2_px = decaying_particle_px / 3;
    double product2_py = decaying_particle_py / 3;
    double product2_pz = decaying_particle_pz / 3;

    double product3_energy = decaying_particle_energy / 3;
    double product3_px = decaying_particle_px / 3;
    double product3_py = decaying_particle_py / 3;
    double product3_pz = decaying_particle_pz / 3;

    // Create the four-momenta for the decay products in the lab frame
    std::unique_ptr<FourMomentum> product1_fm = std::make_unique<FourMomentum>(product1_energy, product1_px, product1_py, product1_pz);
    std::unique_ptr<FourMomentum> product2_fm = std::make_unique<FourMomentum>(product2_energy, product2_px, product2_py, product2_pz);
    std::unique_ptr<FourMomentum> product3_fm = std::make_unique<FourMomentum>(product3_energy, product3_px, product3_py, product3_pz);

    // Give decay particles their four-momenta
    decay_products[0]->set_four_momentum(std::move(product1_fm));
    decay_products[1]->set_four_momentum(std::move(product2_fm));
    decay_products[2]->set_four_momentum(std::move(product3_fm));

    // Validate these auto products
    if (validate_decay_products(decay_products, decay_type))
    {
      this->current_decay_type = decay_type;
      this->decay_products = std::move(decay_products);
    }
    else
    {
      std::cerr << "Error: Auto-set decay products failed. A value is not conserved.\n";
      return;
    }
  }
}

void Particle::set_is_virtual(bool is_virtual)
{
  this->is_virtual = is_virtual;
}

// Getters
std::string Particle::get_label() const
{
  return label;
}

double Particle::get_charge() const
{
  return charge;
}

double Particle::get_spin() const
{
  return spin;
}

double Particle::get_rest_mass() const
{
  return rest_mass;
}

std::string Particle::get_type() const
{
  return type;
}

const FourMomentum &Particle::get_four_momentum() const
{
  if (four_momentum->get_energy() == 0 && four_momentum->get_Px() == 0 && four_momentum->get_Py() == 0 && four_momentum->get_Pz() == 0)
  {
    throw std::runtime_error("FourMomentum has not been intitialised.");
  }
  else
  {
    return *four_momentum;
  }
}

const std::vector<std::unique_ptr<Particle>> &Particle::get_decay_products() const
{
  return decay_products;
}

bool Particle::get_is_virtual()
{
  return is_virtual;
}

// Friend functions
FourMomentum sum_four_momentum(const Particle &a, const Particle &b)
{
  // Direct access to FourMomentum through Lepton's unique_ptr
  FourMomentum result(
      a.four_momentum->get_energy() + b.four_momentum->get_energy(),
      a.four_momentum->get_Px() + b.four_momentum->get_Px(),
      a.four_momentum->get_Py() + b.four_momentum->get_Py(),
      a.four_momentum->get_Pz() + b.four_momentum->get_Pz());
  return result;
}

double dot_product_four_momentum(const Particle &a, const Particle &b)
{
  // Directly utilize FourMomentum's members via Particles's unique_ptr
  return a.four_momentum->get_energy() * b.four_momentum->get_energy() -
         (a.four_momentum->get_Px() * b.four_momentum->get_Px() +
          a.four_momentum->get_Py() * b.four_momentum->get_Py() +
          a.four_momentum->get_Pz() * b.four_momentum->get_Pz());
}

// Lorentz boost functions
void Particle::lorentz_boost(long double v_x, long double v_y, long double v_z)
{
  four_momentum->lorentz_boost(v_x, v_y, v_z);
}

void Particle::lorentz_boost(std::vector<long double> v_xyz)
{
  four_momentum->lorentz_boost(v_xyz);
}

// Virtual print function
void Particle::print() const
{
  const int column_width = 29; // Set the width for each column

  // Print table header
  std::cout << std::left;
  std::cout << std::endl;
  std::cout << std::setw(column_width) << "\033[1m\033[4m\x1b[34mParticle Details:\033[0m\x1b[0m" << std::endl;
  std::cout << std::setw(column_width) << "\033[1mAttribute\033[0m"
            << "\033[1mValue\033[0m" << std::endl;

  // Print separator line
  std::cout << std::setfill('-') << std::setw(2 * column_width) << "-" << std::endl;
  std::cout << std::setfill(' ');
  std::cout << "\033[1m\033[4mParticle Properties:\033[0m\n";

  // Print each attribute and value in a row
  std::cout << std::setw(column_width) << "\033[1mType:\033[0m" << (is_virtual ? "virtual " + type : type) << std::endl;
  std::cout << std::setw(column_width) << "\033[1mLabel:\033[0m" << label << std::endl;
  std::cout << std::setw(column_width) << "\033[1mCharge (e):\033[0m" << charge << std::endl;
  std::cout << std::setw(column_width) << "\033[1mSpin:\033[0m" << spin << std::endl;
  std::cout << std::setw(column_width) << "\033[1mRest Mass (MeV):\033[0m" << rest_mass << std::endl;
  std::cout << std::setw(column_width) << "\033[1mFour Momentum (MeV):\033[0m"
            << "[" << *four_momentum << "]" << std::endl;
}

// Implement the validity check method
bool Particle::is_invariant_mass_valid(double invariant_mass) const
{
  if (is_virtual)
  {
    return true; // Skip the invariant mass check for virtual particles
  }
  if (std::abs(invariant_mass - rest_mass) > 1e-5)
  { // 1e-5 tolerance
    return false;
  }
  return true;
}

// Decay product validity checker
bool Particle::validate_decay_products(const std::vector<std::unique_ptr<Particle>> &decay_products, DecayType decay_type) const
{
  // Checking four momentum conservation
  //////// NEED TO ADD SOME MORE CHECKS BUT CAN COME LATER ////////
  FourMomentum product_total_momentum;
  double product_total_charge = 0;
  int product_total_lepton_number = 0;
  double product_total_baryon_number = 0;

  // Counters for lepton and quark flavors
  int electron_count = 0;
  int muon_count = 0;
  int tau_count = 0;
  int up_count = 0;
  int down_count = 0;
  int charm_count = 0;
  int strange_count = 0;
  int top_count = 0;
  int bottom_count = 0;

  std::vector<Colour> colour_charges;

  for (const auto &product : decay_products)
  {
    product_total_momentum = product_total_momentum + product->get_four_momentum();
    product_total_charge = product_total_charge + product->get_charge();
    product_total_lepton_number = product_total_lepton_number + product->get_lepton_number();
    product_total_baryon_number = product_total_baryon_number + product->get_baryon_number();
    if (product->get_colour_charge() != Colour::None)
    {
      colour_charges.push_back(product->get_colour_charge());
    }
    // Check lepton flavors
    if (dynamic_cast<const Electron *>(product.get()) || (dynamic_cast<const Neutrino *>(product.get()) && dynamic_cast<const Neutrino *>(product.get())->get_flavour() == "electron"))
    {
      if (product->get_lepton_number() == 1)
      {
        electron_count++;
      }
      else if (product->get_lepton_number() == -1)
      {
        electron_count--;
      }
    }
    else if (dynamic_cast<const Muon *>(product.get()) || (dynamic_cast<const Neutrino *>(product.get()) && dynamic_cast<const Neutrino *>(product.get())->get_flavour() == "muon"))
    {
      if (product->get_lepton_number() == 1)
      {
        muon_count++;
      }
      else if (product->get_lepton_number() == -1)
      {
        muon_count--;
      }
    }
    else if (dynamic_cast<const Tau *>(product.get()) || (dynamic_cast<const Neutrino *>(product.get()) && dynamic_cast<const Neutrino *>(product.get())->get_flavour() == "tau"))
    {
      if (product->get_lepton_number() == 1)
      {
        tau_count++;
      }
      else if (product->get_lepton_number() == -1)
      {
        tau_count--;
      }
    }
    // Check quark flavours
    if (dynamic_cast<const Up *>(product.get()))
    {
      if (product->get_baryon_number() > 0)
      {
        up_count++;
      }
      else if (product->get_baryon_number() < 0)
      {
        up_count--;
      }
    }
    else if (dynamic_cast<const Down *>(product.get()))
    {
      if (product->get_baryon_number() > 0)
      {
        down_count++;
      }
      else if (product->get_baryon_number() < 0)
      {
        down_count--;
      }
    }
    else if (dynamic_cast<const Charm *>(product.get()))
    {
      if (product->get_baryon_number() > 0)
      {
        charm_count++;
      }
      else if (product->get_baryon_number() < 0)
      {
        charm_count--;
      }
    }
    else if (dynamic_cast<const Strange *>(product.get()))
    {
      if (product->get_baryon_number() > 0)
      {
        strange_count++;
      }
      else if (product->get_baryon_number() < 0)
      {
        strange_count--;
      }
    }
    else if (dynamic_cast<const Top *>(product.get()))
    {
      if (product->get_baryon_number() > 0)
      {
        top_count++;
      }
      else if (product->get_baryon_number() < 0)
      {
        top_count--;
      }
    }
    else if (dynamic_cast<const Bottom *>(product.get()))
    {
      if (product->get_baryon_number() > 0)
      {
        bottom_count++;
      }
      else if (product->get_baryon_number() < 0)
      {
        bottom_count--;
      }
    }
  }
  FourMomentum diff = product_total_momentum - *four_momentum;
  // Check if the difference in each component is within an acceptable range
  bool four_momentum_conserved = std::abs(diff.get_energy()) < 1e-5 &&
                                 std::abs(diff.get_Px()) < 1e-5 &&
                                 std::abs(diff.get_Py()) < 1e-5 &&
                                 std::abs(diff.get_Pz()) < 1e-5;
  bool charge_conserved = (std::abs(charge - product_total_charge) < 0.01);
  bool lepton_number_conserved = (this->get_lepton_number() == product_total_lepton_number);
  bool baryon_number_conserved = (this->get_baryon_number() == product_total_baryon_number);
  bool colour_charge_conserved = is_colour_neutral(colour_charges);

  // Check lepton flavor conservation
  bool lepton_flavor_conserved = true;
  if (dynamic_cast<const Electron *>(this) || (dynamic_cast<const Neutrino *>(this) && dynamic_cast<const Neutrino *>(this)->get_flavour() == "electron"))
  {
    lepton_flavor_conserved = (electron_count == this->get_lepton_number());
  }
  else if (dynamic_cast<const Muon *>(this) || (dynamic_cast<const Neutrino *>(this) && dynamic_cast<const Neutrino *>(this)->get_flavour() == "muon"))
  {
    lepton_flavor_conserved = (muon_count == this->get_lepton_number());
  }
  else if (dynamic_cast<const Tau *>(this) || (dynamic_cast<const Neutrino *>(this) && dynamic_cast<const Neutrino *>(this)->get_flavour() == "tau"))
  {
    lepton_flavor_conserved = (tau_count == this->get_lepton_number());
  }

  // Check quark flavor conservation
  bool quark_flavor_conserved = true;
  if (dynamic_cast<const Up *>(this))
  {
    quark_flavor_conserved = (up_count == static_cast<int>(this->get_baryon_number() * 3));
  }
  else if (dynamic_cast<const Down *>(this))
  {
    quark_flavor_conserved = (down_count == static_cast<int>(this->get_baryon_number() * 3));
  }
  else if (dynamic_cast<const Charm *>(this))
  {
    quark_flavor_conserved = (charm_count == static_cast<int>(this->get_baryon_number() * 3));
  }
  else if (dynamic_cast<const Strange *>(this))
  {
    quark_flavor_conserved = (strange_count == static_cast<int>(this->get_baryon_number() * 3));
  }
  else if (dynamic_cast<const Top *>(this))
  {
    quark_flavor_conserved = (top_count == static_cast<int>(this->get_baryon_number() * 3));
  }
  else if (dynamic_cast<const Bottom *>(this))
  {
    quark_flavor_conserved = (bottom_count == static_cast<int>(this->get_baryon_number() * 3));
  }
  if (decay_type == DecayType::Weak)
  {
    return (four_momentum_conserved && charge_conserved && lepton_number_conserved && baryon_number_conserved && lepton_flavor_conserved && colour_charge_conserved);
  }
  else
  {
    return (four_momentum_conserved && charge_conserved && lepton_number_conserved && baryon_number_conserved && lepton_flavor_conserved && quark_flavor_conserved && colour_charge_conserved);
  }
}
