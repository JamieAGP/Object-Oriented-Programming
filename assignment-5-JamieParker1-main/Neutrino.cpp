#include "Neutrino.h"
#include <iostream>

// Constructor without label
Neutrino::Neutrino(std::unique_ptr<FourMomentum> four_momentum, std::string flavour, bool has_interacted, bool is_antiparticle)
    : Lepton("neutrino", 0, std::move(four_momentum), is_antiparticle), flavour(std::move(flavour)), has_interacted(has_interacted) {}

// Constructor with label
Neutrino::Neutrino(const std::string &label, std::unique_ptr<FourMomentum> four_momentum, std::string flavour, bool has_interacted, bool is_antiparticle)
    : Lepton("neutrino", label, 0, std::move(four_momentum), is_antiparticle), flavour(std::move(flavour)), has_interacted(has_interacted) {}

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
  if(this != &other)
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
  if(this != &other)
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
  this->flavour = std::move(flavour);
}

// Getters
std::string Neutrino::get_flavour() const
{
  return flavour;
}
 
bool Neutrino::get_hasInteracted() const
{
  return has_interacted;
}

// Virtual function overrides
void Neutrino::print() const
{
  // Call to Lepton's print to display common properties
  Lepton::print();
  std::cout << "\033[1mNeutrino Flavour: \033[0m" << flavour << ", \033[1mHas Interacted: \033[0m" << (has_interacted ? "Yes" : "No") << std::endl;
}
 