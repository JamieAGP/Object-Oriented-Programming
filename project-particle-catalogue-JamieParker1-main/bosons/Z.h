#ifndef Z_H
#define Z_H

#include "Boson.h"
#include "../FourMomentum.h"
#include "../helper_functions.h"

#include <utility>   // For std::move


 
// Z class 
class Z : public Boson
{
public:
  // Constructors
  Z(std::unique_ptr<FourMomentum> four_momentum);
  Z(const std::string &label, std::unique_ptr<FourMomentum> four_momentum);
  // Default constructor
  Z();

  // Special member functions
  Z(const Z &other);                // Copy constructor
  Z(Z &&other) noexcept;            // Move constructor
  ~Z();                                 // Destructor
  Z &operator=(const Z &other);     // Copy assignment operator
  Z &operator=(Z &&other) noexcept; // Move assignment operator

  // Virtual function overrides
  virtual void print() const override;
};

#endif // Z_H
