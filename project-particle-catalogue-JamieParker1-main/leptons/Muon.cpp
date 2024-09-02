#include "Muon.h"

// Constructor for Muon without label
Muon::Muon(std::unique_ptr<FourMomentum> four_momentum, bool is_isolated, int lepton_number)
    : Lepton("muon", (lepton_number == 1) ? -1 : 1, Mass::muon, std::move(four_momentum), lepton_number), is_isolated(is_isolated) {} // Muons have a charge of -1

// Constructor for Muon with label
Muon::Muon(const std::string &label, std::unique_ptr<FourMomentum> four_momentum, bool is_isolated, int lepton_number)
    : Lepton("muon", label, (lepton_number == 1) ? -1 : 1, Mass::muon, std::move(four_momentum), lepton_number), is_isolated(is_isolated) {} // Muons have a charge of -1

// Default constructor for MUon
Muon::Muon(int lepton_number) : Lepton("muon", (lepton_number == 1) ? -1 : 1, Mass::muon, lepton_number), is_isolated(true) {}


// Copy constructor
Muon::Muon(const Muon &other) : Lepton(other), is_isolated(other.is_isolated) {}
 
// Move constructor
Muon::Muon(Muon &&other) noexcept : Lepton(std::move(other)), is_isolated(other.is_isolated)
{
  other.is_isolated = false; 
}

// Destructor
Muon::~Muon() {}

// Copy assignment operator
Muon &Muon::operator=(const Muon &other)
{
  if(this != &other)
  {
    Lepton::operator=(other); // Call the base class copy assignment operator
    is_isolated = other.is_isolated;
  }
  return *this;
}

// Move assignment operator
Muon &Muon::operator=(Muon &&other) noexcept
{
  if(this != &other)
  {
    Lepton::operator=(std::move(other)); // Call the base class move assignment operator
    is_isolated = other.is_isolated;
    other.is_isolated = false; 
  }
  return *this;
}

// Setter for isIsolated
void Muon::set_is_isolated(bool is_isolated)
{
  this->is_isolated = is_isolated;
}

// Getter for isIsolated
bool Muon::get_is_isolated() const
{
  return is_isolated;
}

// Override the print function
void Muon::print() const
{
  Lepton::print(); // Call the base class print function
  std::cout << "\033[1m\033[4mMuon-Specific Properties:\033[0m\n";
  std::cout << "\033[1mIs Isolated: \033[0m" << (is_isolated ? "Yes" : "No") << std::endl;
}
