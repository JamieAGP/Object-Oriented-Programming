#ifndef QUARK_H
#define QUARK_H

#include <memory> // For std::unique_ptr
#include <vector> // For std::vector
#include <string> // For std::string

#include "../Particle.h"

class Quark : public Particle
{
private:
  Colour colour_charge;
  double baryon_number;
  std::string flavour;
  bool is_valid_colour_charge(Colour colour_charge);

protected:
  // Constructor without label
  Quark(std::string flavour, double charge, double rest_mass, std::unique_ptr<FourMomentum> fourMomentum, double baryon_number, Colour colour_charge);
  // Constructor with label
  Quark(std::string flavour, const std::string &label, double charge, double rest_mass, std::unique_ptr<FourMomentum> fourMomentum, double baryon_number, Colour colour_charge);

public:
  // Default constructor
  Quark(double baryon_number = 1.0/3.0, Colour colour_charge = Colour::Red,  std::string flavour = "none");

  // Parameterized constructors
  // Constructor without label
  Quark(std::string flavour, double charge, double rest_mass, double baryon_number, Colour colour_charge);
  // Constructor with label
  Quark(std::string flavour, const std::string &label, double charge, double rest_mass, double baryon_number, Colour colour_charge);

  // Copy constructor
  Quark(const Quark &other);

  // Move constructor
  Quark(Quark &&other) noexcept;

  // Virtual destructor
  virtual ~Quark();

  // Copy assignment operator
  Quark &operator=(const Quark &other);

  // Move assignment operator
  Quark &operator=(Quark &&other) noexcept;

  // Setters
  //void set_baryon_number(double baryon_number);
  void set_colour_charge(Colour colour_charge);

  // Getters
  double get_baryon_number() const override {return baryon_number;}
  std::string get_flavour() const override {return flavour;}
  Colour get_colour_charge() const override {return colour_charge;}
  
  // Virtual print function
  virtual void print() const override;
};

#endif // QUARK_H