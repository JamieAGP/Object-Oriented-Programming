#ifndef MUON_H
#define MUON_H

#include "Lepton.h"
#include "../FourMomentum.h"

#include <memory>
#include <string>
#include <iostream> 

class Muon : public Lepton
{
private:
  bool is_isolated; // 0 for false 1 for true

public:
  // Constructors
  Muon(std::unique_ptr<FourMomentum> four_momentum, bool is_isolated, int lepton_number = 1);
  Muon(const std::string &label, std::unique_ptr<FourMomentum> four_momentum, bool is_isolated, int lepton_number = 1);
  // Default constructor
  Muon(int lepton_number = 1);

  // Copy constructor
  Muon(const Muon &other);

  // Move constructor
  Muon(Muon &&other) noexcept;

  // Destructor
  virtual ~Muon();

  // Copy assignment operator
  Muon &operator=(const Muon &other);

  // Move assignment operator
  Muon &operator=(Muon &&other) noexcept;

  // Getter and Setter for isIsolated
  void set_is_isolated(bool is_isolated);
  bool get_is_isolated() const;

  // Override the print function to include muon-specific information
  virtual void print() const override;
};

#endif // MUON_H
