#include "Electron.h"

// Constructor without label with validity check
Electron::Electron(std::unique_ptr<FourMomentum> four_momentum, const std::vector<double> &energy_deposited_in_layers, int lepton_number)
    : Lepton("electron", (lepton_number == 1) ? -1 : 1, Mass::electron, std::move(four_momentum), lepton_number)
{
  set_energy_deposited_in_layers(energy_deposited_in_layers);
}

// Constructor with label with validity check
Electron::Electron(const std::string &label, std::unique_ptr<FourMomentum> four_momentum, const std::vector<double> &energy_deposited_in_layers, int lepton_number)
    : Lepton("electron", label, (lepton_number == 1) ? -1 : 1, Mass::electron, std::move(four_momentum), lepton_number)
{
  set_energy_deposited_in_layers(energy_deposited_in_layers);
}

// Default constructor
Electron::Electron(int lepton_number) : Lepton("electron", (lepton_number == 1) ? -1 : 1, Mass::electron, lepton_number), energy_deposited_in_layers(std::vector<double>{0.12775, 0.12775, 0.12775, 0.12775}) {}

// Copy constructor
Electron::Electron(const Electron &other)
    : Lepton(other), energy_deposited_in_layers(other.energy_deposited_in_layers) {}

// Move constructor
Electron::Electron(Electron &&other) noexcept
    : Lepton(std::move(other)), energy_deposited_in_layers(std::move(other.energy_deposited_in_layers)) {}

// Destructor
Electron::~Electron() {}

// Copy assignment operator
Electron &Electron::operator=(const Electron &other)
{
  if (this != &other)
  {
    Lepton::operator=(other);
    energy_deposited_in_layers = other.energy_deposited_in_layers;
  }
  return *this;
}

// Move assignment operator
Electron &Electron::operator=(Electron &&other) noexcept
{
  if (this != &other)
  {
    Lepton::operator=(std::move(other));
    energy_deposited_in_layers = std::move(other.energy_deposited_in_layers);
  }
  return *this;
}

// Getter and Setter implementations
void Electron::set_energy_deposited_in_layers(const std::vector<double> &energies)
{
  if (is_valid_energy_deposit(energies))
  {
    this->energy_deposited_in_layers = energies;
  }
  else
  {
    throw std::invalid_argument("Error: Sum of energy deposited in layers does not match the four-momentum energy");
  }
}

const std::vector<double> &Electron::get_energy_deposited_in_layers() const
{
  return energy_deposited_in_layers;
}

void Electron::set_four_momentum(std::unique_ptr<FourMomentum> four_momentum)
{
  if (four_momentum->get_energy() <= 0)
  {
    throw std::invalid_argument("FourMomentum energy must be greater than 0.");
  }
  else if (Particle::is_invariant_mass_valid(four_momentum->invariant_mass()))
  {
    this->four_momentum = std::move(four_momentum);
    double equal_energy_split = this->four_momentum->get_energy() / 4;
    set_energy_deposited_in_layers(std::vector<double>{equal_energy_split, equal_energy_split, equal_energy_split, equal_energy_split});
  }
  else
  {
    throw std::invalid_argument("Rest mass does not match the invariant mass of the provided FourMomentum.");
  }
}

// Override the print function
void Electron::print() const
{
  Lepton::print(); // Print general particle properties

  std::cout << "\033[1m\033[4mElectron-Specific Properties:\033[0m\n";
  std::cout << "\033[1mEnergy Deposited in Layers (MeV): \033[0m";

  for (const auto &energy : energy_deposited_in_layers)
  {
    std::cout << energy << " ";
  }
  std::cout << std::endl;
}

// Utility function to check energy validity
bool Electron::is_valid_energy_deposit(const std::vector<double> &energy_deposited_in_layers) const
{
  if (four_momentum)
  {
    long double sum_of_energy = std::accumulate(energy_deposited_in_layers.begin(), energy_deposited_in_layers.end(), 0.0);
    long double four_momentum_energy = four_momentum->get_energy();
    if (std::abs(sum_of_energy - four_momentum_energy) < 1e-5)
    {
      return true;
    }
    else return false;
  }
  else
  {
    throw std::runtime_error("Error: No four momentum initialised");
  }
}
