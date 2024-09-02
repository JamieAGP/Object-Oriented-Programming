// Lepton.cpp
#include "Lepton.h"
#include "FourMomentum.h" 
#include <iostream>  // For std::cout
#include <stdexcept> // For std::invalid_argument

// Default constructor
Lepton::Lepton() : charge(0), four_momentum(nullptr) {}

// Protected constructor without label with validity check
Lepton::Lepton(std::string type, int charge, std::unique_ptr<FourMomentum> fourMomentum, bool is_antiparticle)
    : type(type), charge(charge), four_momentum(std::move(fourMomentum))
{
  if(this->four_momentum->get_energy() <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
  if(is_antiparticle)
  {
    this->type = "anti-" + this->type;
    this->charge = -this->charge;
  }
}

// Protected constructor with label with validity check
Lepton::Lepton(std::string type, const std::string &label, int charge, std::unique_ptr<FourMomentum> fourMomentum, bool is_antiparticle)
    : type(type), label(label), charge(charge), four_momentum(std::move(fourMomentum))
{
  if(this->four_momentum->get_energy() <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
  if(is_antiparticle)
  {
    this->type = "anti-" + this->type;
    this->charge = -this->charge;
  }
}

// Constructor without label with validity check
Lepton::Lepton(std::string type, int charge, bool is_antiparticle)
    : type(type), charge(charge), four_momentum(std::make_unique<FourMomentum>())
{
  if(this->four_momentum->get_energy() <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
}

// Constructor with label with validity check
Lepton::Lepton(std::string type, const std::string &label, int charge, bool is_antiparticle)
    : type(type), label(label), charge(charge), four_momentum(std::make_unique<FourMomentum>())
{
  if(this->four_momentum->get_energy() <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
}

// Copy constructor
Lepton::Lepton(const Lepton &other)
    : label(other.label), charge(other.charge),
      four_momentum(other.four_momentum ? std::make_unique<FourMomentum>(*other.four_momentum) : nullptr) {}

// Move constructor
Lepton::Lepton(Lepton &&other) noexcept
    : label(std::move(other.label)), charge(other.charge), four_momentum(std::move(other.four_momentum)) {}

// Virtual destructor
Lepton::~Lepton() {}

// Copy assignment operator
Lepton &Lepton::operator=(const Lepton &other)
{
  if(this != &other)
  {
    label = other.label;
    charge = other.charge;
    four_momentum = other.four_momentum ? std::make_unique<FourMomentum>(*other.four_momentum) : nullptr;
  }
  return *this;
}

// Move assignment operator
Lepton &Lepton::operator=(Lepton &&other) noexcept
{
  if(this != &other)
  {
    label = std::move(other.label);
    charge = other.charge;
    four_momentum = std::move(other.four_momentum);
  }
  return *this;
}

// Setters
void Lepton::set_label(const std::string &label)
{
  this->label = label;
}

void Lepton::set_charge(int charge)
{
  this->charge = charge;
}

void Lepton::set_four_momentum(std::unique_ptr<FourMomentum> fourMomentum)
{
  this->four_momentum = std::move(fourMomentum);
}

// Getters
std::string Lepton::get_label() const
{
  return label;
}

int Lepton::get_charge() const
{
  return charge;
}

std::string Lepton::get_type() const
{
  return type;
}

const FourMomentum &Lepton::get_four_momentum() const
{
  if(!four_momentum)
  {
    throw std::runtime_error("FourMomentum is not initialized.");
  }
  return *four_momentum;
}

FourMomentum sum_four_momentum(const Lepton &a, const Lepton &b)
{
  // Direct access to FourMomentum through Lepton's unique_ptr
  FourMomentum result(
      a.four_momentum->get_energy() + b.four_momentum->get_energy(),
      a.four_momentum->get_Px() + b.four_momentum->get_Px(),
      a.four_momentum->get_Py() + b.four_momentum->get_Py(),
      a.four_momentum->get_Pz() + b.four_momentum->get_Pz());
  return result;
}

double dot_product_four_momentum(const Lepton &a, const Lepton &b)
{
  // Directly utilize FourMomentum's members via Lepton's unique_ptr
  return a.four_momentum->get_energy() * b.four_momentum->get_energy() -
         (a.four_momentum->get_Px() * b.four_momentum->get_Px() +
          a.four_momentum->get_Py() * b.four_momentum->get_Py() +
          a.four_momentum->get_Pz() * b.four_momentum->get_Pz());
}

// Virtual print function
void Lepton::print() const
{
  std::cout << "\033[1mType:\033[0m " << type << ", \033[1mLabel:\033[0m " << label << ", \033[1mCharge (e):\033[0m " << charge << ", \033[1mFour Momentum (MeV): \033[0m[" << *four_momentum << "]" << std::endl;
}