#ifndef TAU_H
#define TAU_H

#include "Lepton.h"
#include "FourMomentum.h"
#include <memory>
#include <string>

enum class DecayType
{
  Hadronic,
  Leptonic
};

// Tau class
class Tau : public Lepton
{
private:
  DecayType decay_type;
  std::vector<std::shared_ptr<Lepton>> decay_products; // For leptonic decays

  bool validate_decay_products(const std::vector<std::shared_ptr<Lepton>> &decay_products) const;

public:
  // Constructors
  Tau(std::unique_ptr<FourMomentum> four_momentum, DecayType decay_type, const std::vector<std::shared_ptr<Lepton>> &decay_products, bool is_antiparticle = false);
  Tau(const std::string &label, std::unique_ptr<FourMomentum> four_momentum, DecayType decay_type, const std::vector<std::shared_ptr<Lepton>> &decay_products, bool is_antiparticle = false);

  // Special member functions
  Tau(const Tau &other);
  Tau(Tau &&other) noexcept;
  ~Tau();
  Tau &operator=(const Tau &other);
  Tau &operator=(Tau &&other) noexcept;

  // Getters and Setters
  void set_decay_type(DecayType decay_type);
  void set_decay_products(const std::vector<std::shared_ptr<Lepton>> &decay_products);
  DecayType get_decay_type() const;
  std::vector<std::shared_ptr<Lepton>> get_decay_products() const;

  // Virtual function overrides
  virtual void print() const override;
};

#endif // TAU_H
