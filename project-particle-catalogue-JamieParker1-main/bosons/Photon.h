#ifndef PHOTON_H
#define PHOTON_H

#include "Boson.h"
#include "../FourMomentum.h"

#include <utility>   
 
// Photon class 
class Photon : public Boson
{
public:
  // Constructors
  Photon(std::unique_ptr<FourMomentum> four_momentum);
  Photon(const std::string &label, std::unique_ptr<FourMomentum> four_momentum);
  // Default constructor
  Photon();

  // Special member functions
  Photon(const Photon &other);                // Copy constructor
  Photon(Photon &&other) noexcept;            // Move constructor
  ~Photon();                                    // Destructor
  Photon &operator=(const Photon &other);     // Copy assignment operator
  Photon &operator=(Photon &&other) noexcept; // Move assignment operator
};

#endif // PHOTON_H


