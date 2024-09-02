#include "Tau.h"

// Constructor without label
Tau::Tau(std::unique_ptr<FourMomentum> four_momentum, std::vector<std::unique_ptr<Particle>> decay_products, int lepton_number)
    : Lepton("tau", (lepton_number == 1) ? -1 : 1, Mass::tau, std::move(four_momentum), lepton_number, std::vector<DecayType>{DecayType::Weak}) {}

// Constructor with label
Tau::Tau(const std::string &label, std::unique_ptr<FourMomentum> four_momentum, std::vector<std::unique_ptr<Particle>> decay_products, int lepton_number)
    : Lepton("tau", label, (lepton_number == 1) ? -1 : 1, Mass::tau, std::move(four_momentum), lepton_number, std::vector<DecayType>{DecayType::Weak}) {}

// Default constructor
Tau::Tau(int lepton_number) : Lepton("tau", (lepton_number == 1) ? -1 : 1, Mass::tau, lepton_number, std::vector<DecayType>{DecayType::Weak}) {}

// Copy constructor
Tau::Tau(const Tau &other)
    : Lepton(other) {}

// Move constructor
Tau::Tau(Tau &&other) noexcept
    : Lepton(std::move(other)) {}

// Destructor
Tau::~Tau() {}

// Copy assignment operator
Tau &Tau::operator=(const Tau &other)
{
  if (this != &other)
  {
    Lepton::operator=(other);
  }
  return *this;
}

// Move assignment operator
Tau &Tau::operator=(Tau &&other) noexcept
{
  if (this != &other)
  {
    Lepton::operator=(std::move(other));
  }
  return *this;
}

// Override the print function
void Tau::print() const
{
  Lepton::print(); // Print the base class attributes
  std::cout << "\033[1m\033[4mTau-Specific Properties:\033[0m\n";
  if (!this->get_decay_products().empty())
  {
    std::cout << "\033[1mDecay Products:\033[0m" << std::endl;
    for (const auto &product : this->get_decay_products())
    {
      std::ostringstream oss;
      std::streambuf *coutBuf = std::cout.rdbuf();
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
