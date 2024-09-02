#include "FourMomentum.h"

// Constructor
FourMomentum::FourMomentum(long double energy_or_rest_mass, long double px, long double py, long double pz, bool energy_is_rest_mass)
    : px(px), py(py), pz(pz)
{
  if (energy_is_rest_mass)
  {
    long double spatial_momentum_magnitude_squared = px * px + py * py + pz * pz;
    long double energy_squared = spatial_momentum_magnitude_squared + pow(energy_or_rest_mass, 2);
    this->energy = std::sqrt(energy_squared);
  }
  else
  {
    this->energy = energy_or_rest_mass; // Treat as energy directly
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
    // Optionally, reset the moved-from object's state if needed
  }
  return *this;
}

// Destructor
FourMomentum::~FourMomentum() {}

// Setters
void FourMomentum::set_energy(double energy)
{
  this->energy = energy;
}
void FourMomentum::set_momentum(double px, double py, double pz)
{
  this->px = px;
  this->py = py;
  this->pz = pz;
}

// Getters
long double FourMomentum::get_energy() const
{
  return energy;
}
long double FourMomentum::get_Px() const
{
  return px;
}
long double FourMomentum::get_Py() const
{
  return py;
}
long double FourMomentum::get_Pz() const
{
  return pz;
}
long double FourMomentum::get_P_magnitude() const
{
  return std::sqrt(px*px + py*py + pz*pz);
}

// Calculates velocity from four momentum in units of c
long double FourMomentum::get_velocity_magnitude() const
{
  long double velocity = get_P_magnitude() / energy;
  return velocity;
}
long double FourMomentum::get_velocity_x() const
{
  return px/energy;
}
long double FourMomentum::get_velocity_y() const
{
  return py/energy;
}
long double FourMomentum::get_velocity_z() const
{
  return pz/energy;
}
std::vector<long double> FourMomentum::get_velocity_vector(bool positive) const
{
  if (positive)
  {
    return std::vector<long double>{this->get_velocity_x(), this->get_velocity_y(), this->get_velocity_z()};
  }
  else
  {
    return std::vector<long double>{-this->get_velocity_x(), -this->get_velocity_y(), -this->get_velocity_z()};
  }
}

// Function to calculate the invariant mass of the four momentum
double FourMomentum::invariant_mass() const
{
  // std::amax to prevent sqrt of a negative
  long double zero = 0;
  return sqrt(std::max(zero, energy * energy - (px * px + py * py + pz * pz)));
}

// Function to perform a lorentz boost to four momentum
void FourMomentum::lorentz_boost(long double v_x, long double v_y, long double v_z)
{// Velocity in units of c
  // long double v_magnitude_2 = std::pow(v_x, 2) + std::pow(v_y, 2) +std::pow(v_z, 2);
  long double v_magnitude_2 = v_x*v_x + v_y*v_y + v_z*v_z;
  if (v_magnitude_2 >= 1)
  {
    std::cerr << "Error: Velocity exceeds speed of light. Four momentum not boosted.\n";
    return;
  }
  else if (v_magnitude_2 == 0)
  {
    return; //No boost needed
  }
  long double gamma = 1 / std::sqrt(1-v_magnitude_2);
  long double beta_dot_momentum = v_x*px + v_y*py + v_z*pz; //beta is just velocity in units of c in natural units

  // Calculate new energy component
  long double new_energy = gamma * (energy - beta_dot_momentum);
  // Calculate new momentum components
  long double factor = (gamma - 1) * beta_dot_momentum / v_magnitude_2;
  long double new_px = px + factor * v_x - gamma * energy * v_x;
  long double new_py = py + factor * v_y - gamma * energy * v_y;
  long double new_pz = pz + factor * v_z - gamma * energy * v_z;

  energy = new_energy;
  px = new_px;
  py = new_py;
  pz = new_pz;
}
void FourMomentum::lorentz_boost(std::vector<long double> v_xyz)
{// Velocity in units of c
  if (v_xyz.size() != 3)
  {
    std::cerr << "Velocity vector incorrect length. Four momentum not boosted.\n";
    return;
  }
  lorentz_boost(v_xyz[0], v_xyz[1], v_xyz[2]);
}

// Overloaded operator+ for addition
FourMomentum FourMomentum::operator+(const FourMomentum &rhs) const
{
  return FourMomentum(energy + rhs.energy, px + rhs.px, py + rhs.py, pz + rhs.pz);
}

// Overloaded operator- for subtraction
FourMomentum FourMomentum::operator-(const FourMomentum &rhs) const
{
  return FourMomentum(energy - rhs.energy, px - rhs.px, py - rhs.py, pz - rhs.pz);
}

// Overloaded operator* for dot product
double FourMomentum::operator*(const FourMomentum &rhs) const
{
  return energy * rhs.energy - (px * rhs.px + py * rhs.py + pz * rhs.pz);
}

// Overloaded << operator for printing
std::ostream &operator<<(std::ostream &os, const FourMomentum &fm)
{
  os << "Energy: " << fm.get_energy() << ", Px: " << fm.get_Px() << ", Py: " << fm.get_Py() << ", Pz: " << fm.get_Pz();
  return os;
}