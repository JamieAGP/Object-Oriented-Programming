#include "Quark.h"
#include "../FourMomentum.h" 
#include"../helper_functions.h"
#include <iostream>  // For std::cout
#include <stdexcept> // For std::invalid_argument
#include <iomanip>

// Default constructor
Quark::Quark(double baryon_number, Colour colour_charge,  std::string flavour) : Particle("quark", "General Quark", 0, 0.5, 1, std::vector<DecayType>{DecayType::None}), baryon_number(baryon_number), flavour(flavour)
{
  set_colour_charge(colour_charge);
}

// Protected constructor without label with four momentum
Quark::Quark(std::string flavour, double charge, double rest_mass, std::unique_ptr<FourMomentum> four_momentum, double baryon_number, Colour colour_charge)
    : Particle((baryon_number > 0) ? "quark" : "antiquark", charge, 0.5, rest_mass, std::move(four_momentum), std::vector<DecayType>{DecayType::None}), baryon_number(baryon_number), flavour(flavour)
{
  set_colour_charge(colour_charge);
}


// Protected constructor with label with four momentum
Quark::Quark(std::string flavour, const std::string &label, double charge,  double rest_mass, std::unique_ptr<FourMomentum> four_momentum, double baryon_number, Colour colour_charge)
    : Particle((baryon_number > 0) ? "quark" : "antiquark", label, charge, 0.5, rest_mass, std::move(four_momentum), std::vector<DecayType>{DecayType::None}), baryon_number(baryon_number), flavour(flavour)
{
  set_colour_charge(colour_charge);
}


// Constructor without label without four momentum
Quark::Quark(std::string flavour, double charge, double rest_mass, double baryon_number, Colour colour_charge)
    : Particle((baryon_number > 0) ? "quark" : "antiquark", charge, 0.5, rest_mass, std::vector<DecayType>{DecayType::None}), baryon_number(baryon_number), flavour(flavour)
{
  set_colour_charge(colour_charge);
}

// Constructor with label without four momentum
Quark::Quark(std::string flavour, const std::string &label, double charge, double rest_mass, double baryon_number, Colour colour_charge)
    : Particle((baryon_number > 0) ? "quark" : "antiquark", label, charge, 0.5, rest_mass, std::vector<DecayType>{DecayType::None}), baryon_number(baryon_number), flavour(flavour)
{
  set_colour_charge(colour_charge);
}

// Copy constructor
Quark::Quark(const Quark &other)
    : Particle(other), baryon_number(other.baryon_number), colour_charge(other.colour_charge) {}

// Move constructor
Quark::Quark(Quark &&other) noexcept
    : Particle(std::move(other)), baryon_number(other.baryon_number), colour_charge(other.colour_charge) {} 

// Virtual destructor
Quark::~Quark() {}

// Copy assignment operator
Quark &Quark::operator=(const Quark &other)
{
  if(this != &other)
  {
    Particle::operator=(other); // Call the base class copy assignment operator
    baryon_number = other.baryon_number;
    colour_charge = other.colour_charge;
  }
  return *this;
}

// Move assignment operator
Quark &Quark::operator=(Quark &&other) noexcept
{
  if(this != &other)
  {
    Particle::operator=(std::move(other)); // Call the base class move assignment operator
    baryon_number = other.baryon_number;   
    colour_charge = other.colour_charge;
  }
  return *this;
}

bool Quark::is_valid_colour_charge(Colour colour_charge)
{

  if(baryon_number < 0 && is_anti_colour(colour_charge))
  {
    return true;
  }
  else if (baryon_number > 0 && !is_anti_colour(colour_charge))
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Setters

void Quark::set_colour_charge(Colour colour_charge)
{
  if(is_valid_colour_charge(colour_charge))
  {
    this->colour_charge = colour_charge;
  }
  else
  {
    throw std::invalid_argument("Error: Colour type must match quark type.");
  } 
}

// Virtual print function
void Quark::print() const {
    const int columnWidth = 29;  // Set the width for each column
    std::cout << std::left;  // Align output to the left
    Particle::print();  // Print general particle properties

    std::cout << "\n\033[1m\033[4mQuark-Specific Properties:\033[0m\n";
    // Print Particle and Quark attributes side by side
    std::cout << std::setw(columnWidth) << "\033[1mFlavour:\033[0m " << flavour << std::endl;
    std::cout << std::setw(columnWidth) << "\033[1mBaryon Number:\033[0m " << baryon_number << std::endl;
    std::cout << std::setw(columnWidth) << "\033[1mColour Charge:\033[0m " << to_string(colour_charge) << std::endl;
}