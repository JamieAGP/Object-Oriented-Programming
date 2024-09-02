#include "FourMomentum.h"

// Constructor
FourMomentum::FourMomentum(double energy, double px, double py, double pz)
    : energy(energy), px(px), py(py), pz(pz)
{
  if (energy <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
}

// Copy constructor
FourMomentum::FourMomentum(const FourMomentum &other)
    : energy(other.energy), px(other.px), py(other.py), pz(other.pz) {}

// Move constructor
FourMomentum::FourMomentum(FourMomentum &&other) noexcept
    : energy(std::move(other.energy)), px(std::move(other.px)), py(std::move(other.py)), pz(std::move(other.pz)) {}

// Copy assignment operator
FourMomentum &FourMomentum::operator=(const FourMomentum &other)
{
  if (this != &other)
  { // Protect against self-assignment
    energy = other.energy;
    px = other.px;
    py = other.py;
    pz = other.pz;
  }
  return *this;
}

// Move assignment operator
FourMomentum &FourMomentum::operator=(FourMomentum &&other) noexcept
{
  if (this != &other)
  {
    energy = std::move(other.energy);
    px = std::move(other.px);
    py = std::move(other.py);
    pz = std::move(other.pz);
  }
  return *this;
}

// Destructor
FourMomentum::~FourMomentum(){}

// Setters
void FourMomentum::set_energy(double energy)
{
  if (energy > 0)
    this->energy = energy;
  else
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
}

void FourMomentum::set_momentum(double px, double py, double pz)
{
  this->px = px;
  this->py = py;
  this->pz = pz;
}

// Getters
double FourMomentum::get_energy() const
{
  return energy;
}

double FourMomentum::get_Px() const
{
  return px;
}

double FourMomentum::get_Py() const
{
  return py;
}

double FourMomentum::get_Pz() const
{
  return pz;
}

// Function to calculate the invariant mass
double FourMomentum::invariant_mass() const
{
  return sqrt(std::max(0.0, energy * energy - (px * px + py * py + pz * pz)));
}

// Function to sum four momentum objects
FourMomentum sum_four_momentum(const FourMomentum &a, const FourMomentum &b)
{
  // Directly accessing private members due to 'friend' status
  double summedEnergy = a.energy + b.energy;
  double summedPx = a.px + b.px;
  double summedPy = a.py + b.py;
  double summedPz = a.pz + b.pz;
  return FourMomentum(summedEnergy, summedPx, summedPy, summedPz);
}

double dot_product_four_momentum(const FourMomentum &a, const FourMomentum &b)
{
  // Directly accessing private members, utilizing the 'friend' functionality
  return a.energy * b.energy - (a.px * b.px + a.py * b.py + a.pz * b.pz);
}

// Overloaded << operator
std::ostream &operator<<(std::ostream &os, const FourMomentum &fm)
{
  os << "Energy: " << fm.get_energy() << ", Px: " << fm.get_Px() << ", Py: " << fm.get_Py() << ", Pz: " << fm.get_Pz();
  return os;
}