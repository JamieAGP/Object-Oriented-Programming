#include "Gluon.h"

// Constructor without label with validity check
Gluon::Gluon(std::unique_ptr<FourMomentum> four_momentum, std::vector<Colour> colour_charges)
    : Boson("gluon", 0, Mass::gluon, 1, std::move(four_momentum))
{
  set_colour_charges(colour_charges);
}

// Constructor with label with validity check
Gluon::Gluon(const std::string &label, std::unique_ptr<FourMomentum> four_momentum, std::vector<Colour> colour_charges)
    : Boson("gluon", label, 0, Mass::gluon, 1, std::move(four_momentum))
{
  set_colour_charges(colour_charges);
}

// Default constructor
Gluon::Gluon() : Boson("gluon", 0, Mass::gluon, 1), colour_charges(std::vector<Colour>{Colour::Red, Colour::AntiRed}) {}

// Copy constructor
Gluon::Gluon(const Gluon &other)
    : Boson(other), colour_charges(other.colour_charges) {}

// Move constructor
Gluon::Gluon(Gluon &&other) noexcept
    : Boson(std::move(other)), colour_charges(std::move(other.colour_charges)) {}

// Destructor
Gluon::~Gluon() {}

// Copy assignment operator
Gluon &Gluon::operator=(const Gluon &other)
{
  if (this != &other)
  {
    Boson::operator=(other);
    colour_charges = other.colour_charges;
  }
  return *this;
}

// Move assignment operator
Gluon &Gluon::operator=(Gluon &&other) noexcept
{
  if (this != &other)
  {
    Boson::operator=(std::move(other));
    colour_charges = other.colour_charges;
  }
  return *this;
}

// Override the print function
void Gluon::print() const
{
  Boson::print();
  std::cout << "\033[1mColour Charges: \033[0m" << to_string(colour_charges[0]) << ", " << to_string(colour_charges[1]) << std::endl;
}

void Gluon::set_colour_charges(std::vector<Colour> colour_charges)
{
  if (is_valid_colour_charges(colour_charges))
  {
    this->colour_charges = colour_charges;
  }
  else
  {
    std::cerr << "Error: Not colourless gluon.\n";
  }
}

std::vector<Colour> Gluon::get_colour_charges() const
{
  return colour_charges;
}

// Validate gluon is colourless
bool Gluon::is_valid_colour_charges(std::vector<Colour> &colour_charges) const
{
  int net_red = 0;
  int net_green = 0;
  int net_blue = 0;

  for (const Colour &colour : colour_charges)
  {
    switch (colour)
    {
    case Colour::Red:
      net_red++;
      break;
    case Colour::AntiRed:
      net_red--;
      break;
    case Colour::Green:
      net_green++;
      break;
    case Colour::AntiGreen:
      net_green--;
      break;
    case Colour::Blue:
      net_blue++;
      break;
    case Colour::AntiBlue:
      net_blue--;
      break;
    case Colour::None:
      break;
    }
  }

  return net_red == 0 && net_green == 0 && net_blue == 0;
}

