#ifndef LEPTON_H
#define LEPTON_H

#include <memory> // For std::unique_ptr
#include <vector> // For std::vector
#include <string> // For std::string

#include "FourMomentum.h"

class Lepton
{
private:
  std::string type;             // Type of particle e.g 'electron', 'muon' ...
  std::string label = "None";   // Optional label of particle
  int charge;                   // Charge of the particle
  bool is_antiparticle = false; //

protected:
  // Protected attribute so that derived classes can access four momentum object
  std::unique_ptr<FourMomentum> four_momentum;
  // Constructor without label
  Lepton(std::string type, int charge, std::unique_ptr<FourMomentum> fourMomentum, bool is_antiparticle = false);
  // Constructor with label
  Lepton(std::string type, const std::string &label, int charge, std::unique_ptr<FourMomentum> fourMomentum, bool is_antiparticle = false);

public:
  // Default constructor
  Lepton();

  // Parameterized constructors
  // Constructor without label
  Lepton(std::string type, int charge, bool is_antiparticle = false);
  // Constructor with label
  Lepton(std::string type, const std::string &label, int charge, bool is_antiparticle = false);

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

  // Setters and getters
  void set_label(const std::string &label);
  std::string get_label() const;

  void set_charge(int charge);
  int get_charge() const;

  std::string get_type() const;

  void set_four_momentum(std::unique_ptr<FourMomentum> fourMomentum);
  const FourMomentum &get_four_momentum() const;

  // Friend functions
  friend FourMomentum sum_four_momentum(const Lepton &a, const Lepton &b);
  friend double dot_product_four_momentum(const Lepton &a, const Lepton &b);

  // Virtual print function
  virtual void print() const;
};

#endif // LEPTON_H