#ifndef HIGGS_H
#define HIGGS_H

#include "Boson.h"
#include "../FourMomentum.h"
#include "../helper_functions.h"

#include <utility> 
#include <iomanip>

// Higgs class 
class Higgs : public Boson
{
public:
  // Constructors
  Higgs(std::unique_ptr<FourMomentum> four_momentum);
  Higgs(const std::string &label, std::unique_ptr<FourMomentum> four_momentum);
  
  // Default constructor
  Higgs();

  // Special member functions
  Higgs(const Higgs &other);                // Copy constructor
  Higgs(Higgs &&other) noexcept;            // Move constructor
  ~Higgs();                                 // Destructor
  Higgs &operator=(const Higgs &other);     // Copy assignment operator
  Higgs &operator=(Higgs &&other) noexcept; // Move assignment operator

  // Virtual function overrides
  virtual void print() const override;
};

#endif // Z_H
