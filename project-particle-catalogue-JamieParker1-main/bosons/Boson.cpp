// Boson.cpp
#include "Boson.h"

// Default constructor
Boson::Boson() : Particle("boson", "General Boson", 0, 0, 0,  std::vector<DecayType>{DecayType::None}) {}
 
// Protected constructor without label with four momentum
Boson::Boson(std::string type, int charge, double rest_mass, int spin, std::unique_ptr<FourMomentum> four_momentum, std::vector<DecayType> possible_decay_types)
    : Particle(type, charge, spin, rest_mass, std::move(four_momentum), possible_decay_types) {}

// Protected constructor with label with four momentum
Boson::Boson(std::string type, const std::string &label, int charge,  double rest_mass, int spin, std::unique_ptr<FourMomentum> four_momentum, std::vector<DecayType> possible_decay_types)
    : Particle(type, label, charge, spin, rest_mass, std::move(four_momentum), possible_decay_types) {}

// Constructor without label without four momentum
Boson::Boson(std::string type, int charge, double rest_mass, int spin,  std::vector<DecayType> possible_decay_types)
    : Particle(type, charge, spin, rest_mass, possible_decay_types) {}

// Constructor with label without four momentum
Boson::Boson(std::string type, const std::string &label, int charge, double rest_mass, int spin, std::vector<DecayType> possible_decay_types)
    : Particle(type, label, charge, spin, rest_mass, possible_decay_types) {}

// Copy constructor
Boson::Boson(const Boson &other)
    : Particle(other){}

// Move constructor
Boson::Boson(Boson &&other) noexcept
    : Particle(std::move(other)) {} 

// Virtual destructor
Boson::~Boson() {}

// Copy assignment operator
Boson &Boson::operator=(const Boson &other)
{
  if(this != &other)
  {
    Particle::operator=(other); 
  }
  return *this;
}

// Move assignment operator
Boson &Boson::operator=(Boson &&other) noexcept
{
  if(this != &other)
  {
    Particle::operator=(std::move(other)); 
  }
  return *this;
}

