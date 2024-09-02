#ifndef INDIVIDUAL_QUARKS_H
#define INDIVIDUAL_QUARKS_H

#include "QuarkTemplate.h"

// Define specialized structs for each quark type with their respective names

template <>
struct QuarkName<7>
{
  static constexpr char name[7] = "bottom";
};

template <>
struct QuarkName<6>
{
  static constexpr char name[6] = "charm";
};

template <>
struct QuarkName<5>
{
  static constexpr char name[5] = "down";
};

template <>
struct QuarkName<3>
{
  static constexpr char name[3] = "up";
};

template <>
struct QuarkName<8>
{
  static constexpr char name[8] = "strange";
};

template <>
struct QuarkName<4>
{
  static constexpr char name[4] = "top";
};


// Create classes using the QuarkTemplate, specialising the rest mass and charge
// Utilise


class Up : public QuarkTemplate<Up, QuarkName<3>, 2, 3, 23, 10>
{
  using QuarkTemplate<Up, QuarkName<3>, 2, 3, 23, 10>::QuarkTemplate;
};
class Charm : public QuarkTemplate<Charm, QuarkName<6>, 2, 3, 1275, 1>
{
  using QuarkTemplate<Charm, QuarkName<6>, 2, 3, 1275, 1>::QuarkTemplate;
};
class Top : public QuarkTemplate<Top, QuarkName<4>, 2, 3, 173070, 1>
{
  using QuarkTemplate<Top, QuarkName<4>, 2, 3, 173070, 1>::QuarkTemplate;
};


class Down : public QuarkTemplate<Down, QuarkName<5>, -1, 3, 48, 10>
{
  using QuarkTemplate<Down, QuarkName<5>, -1, 3, 48, 10>::QuarkTemplate;
};
class Strange : public QuarkTemplate<Strange, QuarkName<8>, -1, 3, 95, 1>
{
  using QuarkTemplate<Strange, QuarkName<8>, -1, 3, 95, 1>::QuarkTemplate;
};
class Bottom : public QuarkTemplate<Bottom, QuarkName<7>, -1, 3, 4180, 1>
{
  using QuarkTemplate<Bottom, QuarkName<7>, -1, 3, 4180, 1>::QuarkTemplate;
};

#endif // INDIVIDUAL_QUARKS_H