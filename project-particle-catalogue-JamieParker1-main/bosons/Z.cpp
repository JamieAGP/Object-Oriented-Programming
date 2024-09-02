#include "Z.h"

// Constructor without label 
Z::Z(std::unique_ptr<FourMomentum> four_momentum)
    : Boson("z", 0, Mass::z, 1, std::move(four_momentum), std::vector<DecayType>{DecayType::Weak}) {}

// Constructor with label 
Z::Z(const std::string &label, std::unique_ptr<FourMomentum> four_momentum)
    : Boson("z", label, 0, Mass::z, 1, std::move(four_momentum), std::vector<DecayType>{DecayType::Weak}) {}

// Default constructor
Z::Z() : Boson("z", 0, Mass::z, 1, std::vector<DecayType>{DecayType::Weak}) {}

// Copy constructor
Z::Z(const Z &other)
    : Boson(other) {}

// Move constructor
Z::Z(Z &&other) noexcept
    : Boson(std::move(other)) {}

// Destructor
Z::~Z() {}

// Copy assignment operator
Z &Z::operator=(const Z &other)
{
  if (this != &other)
  {
    Boson::operator=(other);
  }
  return *this;
}

// Move assignment operator
Z &Z::operator=(Z &&other) noexcept
{
  if (this != &other)
  {
    Boson::operator=(std::move(other));
  }
  return *this;
}

// Override the print function
void Z::print() const
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

