#ifndef W_H
#define W_H

#include "Boson.h"
#include "../FourMomentum.h"

#include "../helper_functions.h"
#include <utility>

 
// W class 
class W : public Boson
{
private:
  int validate_charge(int charge);
public:
  // Constructors
  W(int charge, std::unique_ptr<FourMomentum> four_momentum);
  W(const std::string &label, int charge, std::unique_ptr<FourMomentum> four_momentum);
  // Default constructor
  W(int charge = 1);

  // Special member functions
  W(const W &other);                // Copy constructor
  W(W &&other) noexcept;            // Move constructor
  ~W();                                 // Destructor
  W &operator=(const W &other);     // Copy assignment operator
  W &operator=(W &&other) noexcept; // Move assignment operator

  // Virtual function overrides
  virtual void print() const override;
};

#endif // W_H
