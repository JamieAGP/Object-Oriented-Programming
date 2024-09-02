#include "W.h"


// Constructor without label
W::W(int charge, std::unique_ptr<FourMomentum> four_momentum)
    : Boson("w", validate_charge(charge), Mass::w, 1, std::move(four_momentum), std::vector<DecayType>{DecayType::Weak}) {}

// Constructor with label
W::W(const std::string &label, int charge, std::unique_ptr<FourMomentum> four_momentum)
    : Boson("w", label, validate_charge(charge), Mass::w, 1, std::move(four_momentum), std::vector<DecayType>{DecayType::Weak}) {}

// Default constructor
W::W(int charge) : Boson("w", validate_charge(charge), Mass::w, 1, std::vector<DecayType>{DecayType::Weak}) {}

// Copy constructor
W::W(const W &other)
    : Boson(other) {}

// Move constructor
W::W(W &&other) noexcept
    : Boson(std::move(other)) {}

// Destructor
W::~W() {}

// Copy assignment operator
W &W::operator=(const W &other)
{
  if (this != &other)
  {
    Boson::operator=(other);
  }
  return *this;
}

// Move assignment operator
W &W::operator=(W &&other) noexcept
{
  if (this != &other)
  {
    Boson::operator=(std::move(other));
  }
  return *this;
}

int W::validate_charge(int charge)
{
  if (charge != -1 && charge != 1)
  {
    throw std::invalid_argument("Error: Charge must be either -1 or +1");
  }
  return charge;
}

// Override the print function
void W::print() const
{
  Boson::print(); // Print the base class attributes
  if (!this->get_decay_products().empty())
  {
    std::cout << "\033[1mDecay Products:\033[0m" << std::endl;
    for (const auto &product : this->get_decay_products())
    {
      std::ostringstream oss;
      std::streambuf* coutBuf = std::cout.rdbuf();
      std::cout.rdbuf(oss.rdbuf());

      product->print();
      std::cout.rdbuf(coutBuf);

      std::istringstream iss(oss.str());
      std::string line;
      std::string indent(4, ' ');

      while (std::getline(iss, line))
      {
        std::cout << indent << line << std::endl;
      }
    }
  }
  else
  {
    std::cout << "\033[1mDecay Products: \033[0mNo Specific Decay Products To Display" << std::endl;
  }
}
