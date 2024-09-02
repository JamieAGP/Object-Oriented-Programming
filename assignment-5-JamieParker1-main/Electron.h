#ifndef ELECTRON_H
#define ELECTRON_H

#include "Lepton.h"
#include "FourMomentum.h"
#include <vector>
#include <string>
 
// Electron class
class Electron : public Lepton
{
private:
  std::vector<double> energy_deposited_in_layers; // Specific to electrons
  bool is_valid_energy_deposit() const;

public:
  // Constructors
  Electron(std::unique_ptr<FourMomentum> four_momentum, const std::vector<double> &energy_deposited_in_layers, bool is_antiparticle = false);
  Electron(const std::string &label, std::unique_ptr<FourMomentum> four_momentum, const std::vector<double> &energy_deposited_in_layers, bool is_antiparticle = false);

  // Special member functions
  Electron(const Electron &other);                // Copy constructor
  Electron(Electron &&other) noexcept;            // Move constructor
  ~Electron();                                    // Destructor
  Electron &operator=(const Electron &other);     // Copy assignment operator
  Electron &operator=(Electron &&other) noexcept; // Move assignment operator

  // Getters and Setters
  void set_energy_deposited_in_layers(const std::vector<double> &energies);
  const std::vector<double> &get_energy_deposited_in_layers() const;

  // Virtual function overrides
  virtual void print() const override;
};

#endif // ELECTRON_H
