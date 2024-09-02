// Lepton.cpp - Implementation file
#include "Lepton.h"
#include <cmath>



// Updated constructor with parameters for type, rest_mass, and charge
Lepton::Lepton(double E, double px, double py, double pz, double mass, double q, std::string particleType)
    : P(new std::vector<double>(4)), rest_mass(mass), charge(q), type(particleType)
{
  std::cout << "Calling Paramaterised Constructor" << std::endl;
  // Validate and set the energy component with input checking
  if (E < 0.0)
  {
    std::cerr << "Error: Energy cannot be negative." << std::endl;
    exit(1); // Exit program with error code
  }

  set_E(E);
  set_Px(px);
  set_Py(py);
  set_Pz(pz);
}

// Copy constructor
Lepton::Lepton(const Lepton &other)
    : P(new std::vector<double>(*(other.P))),
      rest_mass(other.rest_mass),
      charge(other.charge),
      type(other.type)
{
  std::cout << "Calling Copy Constructor" << std::endl;
  // Deep copy is handled in the initializer list
}

// Move contructor
Lepton::Lepton(Lepton &&other) noexcept
    : P(other.P),
      rest_mass(other.rest_mass),
      charge(other.charge),
      type(std::move(other.type))
{
  std::cout << "Calling Move Constructor" << std::endl;
  other.P = nullptr; // Transfer ownership and avoid double free
}

// Destructor
Lepton::~Lepton()
{
  std::cout << "Calling Destructor" << std::endl;
  delete P; // Free dynamically allocated memory
}

// Copy assignment operator
Lepton &Lepton::operator=(const Lepton &other)
{
  std::cout << "Calling Copy Assignment Operator" << std::endl;
  if (this != &other)
  { // Protection against self-assignment
    deep_copy(other);

  }
  return *this;
}

// Move assignment operator
Lepton &Lepton::operator=(Lepton &&other) noexcept
{
  std::cout << "Calling Move Assignment Operator" << std::endl;
  if (this != &other)
  {
    delete P;          // Free existing resource
    P = other.P;       // Transfer ownership
    other.P = nullptr; // Ensure the temporary object doesn't delete the resource
  }
  return *this;
}

// Four momentum addition operator
Lepton Lepton::operator+(const Lepton &other) const
{// Purpose of this is to only add four momentum - not to consider what happens when combining rest masses / charge etc
  double newE = this->get_E() + other.get_E();
  double newPx = this->get_Px() + other.get_Px();
  double newPy = this->get_Py() + other.get_Py();
  double newPz = this->get_Pz() + other.get_Pz();

  std::string combinedType = "Combined " + this->type + " and " + other.type;
  if(this->get_type() == other.get_type())
  {
    return Lepton(newE, newPx, newPy, newPz, this->rest_mass, this->charge, combinedType);
  }
  else
  {
    double combinedMass = std::numeric_limits<double>::quiet_NaN(); // This is a placeholder.
    double combinedCharge = std::numeric_limits<double>::quiet_NaN();     // This is a placeholder.
    return Lepton(newE, newPx, newPy, newPz, combinedMass, combinedCharge, combinedType);
  }
}

// Four momentum dot product method
double Lepton::dot_product(const Lepton &other) const
{
  // This results in the dot product being: E1*E2 - (px1*px2 + py1*py2 + pz1*pz2)

  double dotProduct = (*P)[0] * (*other.P)[0]; // E1*E2
  // Subtract the product of the spatial components
  for (int i = 1; i <= 3; ++i)
  {
    dotProduct -= (*P)[i] * (*other.P)[i]; 
  }
  return dotProduct;
}

// Deep copy method
void Lepton::deep_copy(const Lepton &source) {
    // Copy the four-momentum vector
    if (!source.P) {
        // Handle the null source vector if necessary
        return;
    }
    // Allocate new memory for P if it does not exist or is of a different size
    if (P == nullptr || P->size() != source.P->size()) {
        delete P; // Free existing memory
        P = new std::vector<double>(source.P->size());
    }
    // Copy each element from source.P to P
    std::copy(source.P->begin(), source.P->end(), P->begin());
    
    // Copy the rest of the attributes
    rest_mass = source.rest_mass;
    charge = source.charge;
    type = source.type;
}

// Setters
void Lepton::set_E(double E)
{
  if (E < 0.0)
  {
    std::cerr << "Error: Energy cannot be negative." << std::endl;
    exit(1);
  }
  (*P)[0] = E;
}

void Lepton::set_Px(double px)
{
  (*P)[1] = px;
}

void Lepton::set_Py(double py)
{
  (*P)[2] = py;
}

void Lepton::set_Pz(double pz)
{
  (*P)[3] = pz;
}

std::ostream& operator<<(std::ostream& os, const Lepton& lepton) {
    os << "Type=" << lepton.get_type() << std::endl
       << "Charge=" << lepton.get_charge() << "e\n"
       << "Rest Mass=" << lepton.get_rest_mass() << "MeV\n"
       << "Four momentum -\n"
       << "E=" << lepton.get_E() << " MeV\n"
       << "Px=" << lepton.get_Px() << " MeV\n"
       << "Py=" << lepton.get_Py() << " MeV\n"
       << "Pz=" << lepton.get_Pz() << " MeV\n";
    return os;
}