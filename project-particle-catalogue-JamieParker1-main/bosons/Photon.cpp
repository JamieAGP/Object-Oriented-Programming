#include "Photon.h"

// Constructor without label with validity check
Photon::Photon(std::unique_ptr<FourMomentum> four_momentum)
    : Boson("photon", 0, Mass::photon, 0, std::move(four_momentum)) {}

// Constructor with label with validity check
Photon::Photon(const std::string &label, std::unique_ptr<FourMomentum> four_momentum)
    : Boson("photon", label, 0, Mass::photon, 0, std::move(four_momentum)) {}

//Default constructor
Photon::Photon() : Boson("photon", 0, Mass::photon, 0) {}

// Copy constructor
Photon::Photon(const Photon &other)
    : Boson(other) {}

// Move constructor 
Photon::Photon(Photon &&other) noexcept
    : Boson(std::move(other)) {}

// Destructor
Photon::~Photon() {}

// Copy assignment operator
Photon &Photon::operator=(const Photon &other)
{
  if(this != &other)
  {
    Boson::operator=(other);
  }
  return *this;
}

// Move assignment operator
Photon &Photon::operator=(Photon &&other) noexcept
{
  if(this != &other)
  {
    Boson::operator=(std::move(other));
  }
  return *this;
} 








