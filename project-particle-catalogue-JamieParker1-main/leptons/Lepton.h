#ifndef LEPTON_H
#define LEPTON_H

#include "../Particle.h"
#include "../FourMomentum.h" 

#include <memory> 
#include <vector> 
#include <string> 
#include <iostream> 
#include <stdexcept>
#include <iomanip>

class Lepton : public Particle
{
private:
  int lepton_number;
  
protected:
  // Constructor without label
  Lepton(std::string type, int charge, double rest_mass, std::unique_ptr<FourMomentum> fourMomentum, int lepton_number, std::vector<DecayType> possible_decay_types = {DecayType::None});
  // Constructor with label
  Lepton(std::string type, const std::string &label, int charge, double rest_mass, std::unique_ptr<FourMomentum> fourMomentum, int lepton_number, std::vector<DecayType> possible_decay_types = {DecayType::None});

public:
  // Default constructor
  Lepton(int lepton_number = 1);

  // Parameterized constructors
  // Constructor without label
  Lepton(std::string type, int charge, double rest_mass, int lepton_number, std::vector<DecayType> possible_decay_types = {DecayType::None});
  // Constructor with label
  Lepton(std::string type, const std::string &label, int charge, double rest_mass, int lepton_number, std::vector<DecayType> possible_decay_types = {DecayType::None});

  // Copy constructor
  Lepton(const Lepton &other);

  // Move constructor
  Lepton(Lepton &&other) noexcept;

  // Virtual destructor
  virtual ~Lepton();

  // Copy assignment operator
  Lepton &operator=(const Lepton &other);

  // Move assignment operator
  Lepton &operator=(Lepton &&other) noexcept;

  // Getters
  int get_lepton_number() const override {return lepton_number;}

  // Virtual print function
  virtual void print() const override;
};

#endif // LEPTON_H