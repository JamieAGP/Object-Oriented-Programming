#include "Tau.h"
#include <iostream>
#include <utility>
#include <numeric>
 
// Constructor without label
Tau::Tau(std::unique_ptr<FourMomentum> four_momentum, DecayType decay_type, const std::vector<std::shared_ptr<Lepton>> &decay_products, bool is_antiparticle)
    : Lepton("tau", 0, std::move(four_momentum), is_antiparticle), decay_type(decay_type), decay_products(decay_products)
{
  if(!validate_decay_products(decay_products))
  {
    throw std::invalid_argument("Decay products do not conserve energy and momentum.");
  }
  this->decay_products = decay_products;
}

// Constructor with label
Tau::Tau(const std::string &label, std::unique_ptr<FourMomentum> four_momentum, DecayType decay_type, const std::vector<std::shared_ptr<Lepton>> &decay_products, bool is_antiparticle)
    : Lepton("tau", label, 0, std::move(four_momentum), is_antiparticle), decay_type(decay_type), decay_products(decay_products)
{
  if(!validate_decay_products(decay_products))
  {
    throw std::invalid_argument("Decay products do not conserve energy and momentum.");
  }
  this->decay_products = decay_products;
}

// Copy constructor
Tau::Tau(const Tau &other)
    : Lepton(other), decay_type(other.decay_type), decay_products(other.decay_products) {}

// Move constructor
Tau::Tau(Tau &&other) noexcept
    : Lepton(std::move(other)), decay_type(std::move(other.decay_type)), decay_products(std::move(other.decay_products)) {}

// Destructor
Tau::~Tau() {}

// Copy assignment operator
Tau &Tau::operator=(const Tau &other)
{
  if(this != &other)
  {
    Lepton::operator=(other);
    decay_type = other.decay_type;
    decay_products = other.decay_products;
  }
  return *this;
}

// Move assignment operator
Tau &Tau::operator=(Tau &&other) noexcept
{
  if(this != &other)
  {
    Lepton::operator=(std::move(other));
    decay_type = std::move(other.decay_type);
    decay_products = std::move(other.decay_products);
  }
  return *this;
}

// Getters and Setters implementations
void Tau::set_decay_type(DecayType decay_type)
{
  this->decay_type = decay_type;
}

void Tau::set_decay_products(const std::vector<std::shared_ptr<Lepton>> &decay_products)
{
  if(validate_decay_products(decay_products))
  {
    this->decay_products = decay_products;
  }
  else
  {
    std::cerr << "Decay products validation failed: Conservation of energy and momentum not satisfied." << std::endl;
  }
}

DecayType Tau::get_decay_type() const
{
  return decay_type;
}

std::vector<std::shared_ptr<Lepton>> Tau::get_decay_products() const
{
  return decay_products;
}

// Override the print function
void Tau::print() const
{
  Lepton::print(); // Print the base class attributes
  std::cout << "\033[1mTau Decay Type: \033[0m" << (decay_type == DecayType::Hadronic ? "Hadronic" : "Leptonic") << std::endl;

  if(decay_type == DecayType::Leptonic && !decay_products.empty())
  {
    int i = 1; // Start the counter at 1 for indexing
    for(const auto &product : decay_products)
    {
      std::cout << " - Decay Product " << i++ << ": \n";
      product->print();
    }
  }
  else
  {
    std::cout << "No specific decay products to display." << std::endl;
  }
}

// Method to validate the decay products four momentum matches with the tau's
bool Tau::validate_decay_products(const std::vector<std::shared_ptr<Lepton>> &decay_products) const
{
  double totalEnergy = 0.0;
  double totalPx = 0.0, totalPy = 0.0, totalPz = 0.0;

  for(const auto &product : decay_products)
  {
    const FourMomentum &mom = product->get_four_momentum();
    totalEnergy += mom.get_energy();
    totalPx += mom.get_Px();
    totalPy += mom.get_Py();
    totalPz += mom.get_Pz();
  }

  const FourMomentum &tauMom = this->get_four_momentum();
  return std::abs(totalEnergy - tauMom.get_energy()) < 1e-5 &&
         std::abs(totalPx - tauMom.get_Px()) < 1e-5 &&
         std::abs(totalPy - tauMom.get_Py()) < 1e-5 &&
         std::abs(totalPz - tauMom.get_Pz()) < 1e-5;
}