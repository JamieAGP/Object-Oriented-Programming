#ifndef GLUON_H
#define GLUON_H

#include "Boson.h"
#include "../helper_functions.h"
#include "../FourMomentum.h"

#include <vector>
#include <string>
#include <iostream>
#include <utility>   
#include <numeric>   
#include <stdexcept> 
 
// Gluon class 
class Gluon : public Boson
{
private:
  std::vector<Colour> colour_charges;
  bool is_valid_colour_charges(std::vector<Colour>& colour_charges) const;
public:
  // Constructors
  Gluon(std::unique_ptr<FourMomentum> four_momentum, std::vector<Colour> colour_charges);
  Gluon(const std::string &label, std::unique_ptr<FourMomentum> four_momentum, std::vector<Colour> colour_charges);
  // Default constructor
  Gluon();

  // Special member functions
  Gluon(const Gluon &other);                // Copy constructor
  Gluon(Gluon &&other) noexcept;            // Move constructor
  ~Gluon();                                 // Destructor
  Gluon &operator=(const Gluon &other);     // Copy assignment operator
  Gluon &operator=(Gluon &&other) noexcept; // Move assignment operator

  // Setters and Getters
  void set_colour_charges(std::vector<Colour> colour_charges);
  std::vector<Colour> get_colour_charges() const;

  // Virtual function overrides
  virtual void print() const override;
};

#endif // GLUON_H
