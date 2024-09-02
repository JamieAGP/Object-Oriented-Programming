#ifndef MUON_H
#define MUON_H

#include "Lepton.h"
#include "FourMomentum.h"
#include <memory>
#include <string>

class Muon : public Lepton
{
private:
  bool is_isolated;

public:
  // Constructors
  Muon(std::unique_ptr<FourMomentum> four_momentum, bool is_isolated, bool is_antiparticle = false);
  Muon(const std::string &label, std::unique_ptr<FourMomentum> four_momentum, bool is_isolated, bool is_antiparticle = false);

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
