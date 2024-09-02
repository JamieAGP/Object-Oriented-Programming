#ifndef TAU_H
#define TAU_H

#include "Lepton.h"
#include "../FourMomentum.h"

#include <memory>
#include <string>
#include <iostream>
#include <utility>
#include <numeric>
#include <cmath>
#include <vector>
#include <iomanip>


// Tau class
class Tau : public Lepton
{
public:
  // Constructors
  Tau(std::unique_ptr<FourMomentum> four_momentum, std::vector<std::unique_ptr<Particle>> decay_products, int lepton_number = 1);
  Tau(const std::string &label, std::unique_ptr<FourMomentum> four_momentum, std::vector<std::unique_ptr<Particle>> decay_products, int lepton_number = 1);
  // Default constructor
  Tau(int lepton_number = 1);

  // Special member functions
  Tau(const Tau &other);
  Tau(Tau &&other) noexcept;
  ~Tau();
  Tau &operator=(const Tau &other);
  Tau &operator=(Tau &&other) noexcept;

  // Virtual function overrides
  virtual void print() const override;
};

#endif // TAU_H
