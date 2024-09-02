#include "Neutrino.h"

// Constructor without label
Neutrino::Neutrino(std::unique_ptr<FourMomentum> four_momentum, std::string flavour, bool has_interacted, int lepton_number)
    : Lepton("neutrino", 0, determine_neutrino_mass(flavour), std::move(four_momentum), lepton_number), flavour(std::move(flavour)), has_interacted(has_interacted) {}

// Constructor with label
Neutrino::Neutrino(const std::string &label, std::unique_ptr<FourMomentum> four_momentum, std::string flavour, bool has_interacted, int lepton_number)
    : Lepton("neutrino", label, 0, determine_neutrino_mass(flavour), std::move(four_momentum), lepton_number), flavour(std::move(flavour)), has_interacted(has_interacted) {}

// Default constructor
Neutrino::Neutrino(std::string flavour, int lepton_number) : Lepton("neutrino", 0, determine_neutrino_mass(flavour), lepton_number), flavour(flavour), has_interacted(false) {}

// Copy constructor
Neutrino::Neutrino(const Neutrino &other)
    : Lepton(other), flavour(other.flavour), has_interacted(other.has_interacted) {}

// Move constructor
Neutrino::Neutrino(Neutrino &&other) noexcept
    : Lepton(std::move(other)), flavour(std::move(other.flavour)), has_interacted(other.has_interacted) {}

// Destructor
Neutrino::~Neutrino() {}

// Copy assignment operator
Neutrino &Neutrino::operator=(const Neutrino &other)
{
  if (this != &other)
  {
    Lepton::operator=(other);
    flavour = other.flavour;
    has_interacted = other.has_interacted;
  }
  return *this;
}

// Move assignment operator
Neutrino &Neutrino::operator=(Neutrino &&other) noexcept
{
  if (this != &other)
  {
    Lepton::operator=(std::move(other));
    flavour = std::move(other.flavour);
    has_interacted = other.has_interacted;
  }
  return *this;
}

// Setters
void Neutrino::set_has_interacted(bool has_interacted)
{
  this->has_interacted = has_interacted;
}

void Neutrino::set_flavour(std::string flavour)
{
  this->rest_mass = determine_neutrino_mass(flavour);
  this->flavour = std::move(flavour);
}

double Neutrino::determine_neutrino_mass(std::string flavour)
{
  if (flavour == "electron")
  {
    return Mass::electron_neutrino;
  }
  else if (flavour == "muon")
  {
    return Mass::muon_neutrino;
  }
  else if (flavour == "tau")
  {
    return Mass::tau_neutrino;
  }
  else if (flavour == "none")
  {
    return 1.1e-6;
  }
  else
  {
   throw std::invalid_argument("Error: Unknown neutrino flavour");
  }
}

// Virtual function overrides
void Neutrino::print() const
{

  const int columnWidth = 29; // Set the width for each column
  std::cout << std::left;     // Align output to the left

  // Call to Lepton's print to display common properties
  Lepton::print();
  std::cout << "\033[1m\033[4mNeutrino-Specific Properties:\033[0m\n";

  std::cout << std::setw(columnWidth) << "\033[1mNeutrino Flavour:\033[0m" << flavour << std::endl;
  std::cout << std::setw(columnWidth) << "\033[1mHas Interacted:\033[0m" << (has_interacted ? "Yes" : "No") << std::endl;
}
