#ifndef QUARK_TEMPLATE_H
#define QUARK_TEMPLATE_H

#include "Quark.h"
#include "../FourMomentum.h"
#include "../helper_functions.h"
#include "QuarkName.h"
#include <cstdint>

template<typename Derived, typename Name, std::intmax_t charge_integer, std::intmax_t charge_denominator, std::intmax_t mass_integer, std::intmax_t mass_denominator>
class QuarkTemplate : public Quark
{
public:
  // Constructors
  using Quark::Quark;

  // Constructors
  QuarkTemplate(bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
      : Quark(Name::name, (anti) ? -static_cast<double>(charge_integer) / static_cast<double>(charge_denominator) : static_cast<double>(charge_integer) / static_cast<double>(charge_denominator), static_cast<double>(mass_integer) / static_cast<double>(mass_denominator), std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

  QuarkTemplate(const std::string &label, bool anti, Colour colour_charge, std::unique_ptr<FourMomentum> four_momentum)
      : Quark(Name::name, label, (anti) ? -static_cast<double>(charge_integer) / static_cast<double>(charge_denominator) : static_cast<double>(charge_integer) / static_cast<double>(charge_denominator), static_cast<double>(mass_integer) / static_cast<double>(mass_denominator), std::move(four_momentum), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}

  QuarkTemplate(bool anti = false)
      : Quark(Name::name, (anti) ? -static_cast<double>(charge_integer) / static_cast<double>(charge_denominator) : static_cast<double>(charge_integer) / static_cast<double>(charge_denominator), static_cast<double>(mass_integer) / static_cast<double>(mass_denominator), (anti) ? -1.0/3.0 : 1.0/3.0, (anti) ? Colour::AntiRed : Colour::Red) {}

  QuarkTemplate(Colour colour_charge, bool anti = false)
      : Quark(Name::name, (anti) ? -static_cast<double>(charge_integer) / static_cast<double>(charge_denominator) : static_cast<double>(charge_integer) / static_cast<double>(charge_denominator), static_cast<double>(mass_integer) / static_cast<double>(mass_denominator), (anti) ? -1.0/3.0 : 1.0/3.0, colour_charge) {}
  // Special member functions
  QuarkTemplate(const Derived &other) : Quark(other) {}
  QuarkTemplate(Derived &&other) noexcept : Quark(std::move(other)) {}
  ~QuarkTemplate() {}
  Derived &operator=(const Derived &other)
  {
    if (this != &other)
      Quark::operator=(other);
    return static_cast<Derived&>(*this);
  }
  Derived &operator=(Derived &&other) noexcept
  {
    if (this != &other)
      Quark::operator=(std::move(other));
    return static_cast<Derived&>(*this);
  }
};

#endif // QUARK_TEMPLATE_H