#ifndef PARTICLE_H
#define PARTICLE_H

#include "constants.h"
#include <stdexcept> // Include this for std::invalid_argument
using namespace std;

//int speed_of_light = 299792458; // m/s

class particle
{
private:
  string type;      // Type of the particle (e.g., electron, muon)
  int charge;       // Charge of the particle
  double rest_mass; // Rest mass of the particle in MeV
public:
  // Default constructor
  particle() : type(""), rest_mass(0), charge(0){}

  // Paramaterised constructor
  particle(string type, double rest_mass, int charge)
      : type(type), rest_mass(rest_mass), charge(charge){}

  // Destructor
  ~particle() {}

  // Getter functions
  string get_type() const { return type; }
  double get_rest_mass() const { return rest_mass; }
  int get_charge() const { return charge; }

  //
  void print_info();
};

class particle_instance : public particle
{
private:
  double velocity; // Velocity of the particle instance
  double beta;     // Velocity as a fraction of the speed of light

public:
  // Constructor that takes an existing particle object and the velocity
  particle_instance(const particle &p, double v) : particle(p), velocity(v)
  {
    if (v > speed_of_light)
    {
      throw std::invalid_argument("Velocity cannot exceed the speed of light.");
    }
    beta = v / speed_of_light;
  }

  ~particle_instance() {}

  // Getter for velocity
  double get_velocity() const { return velocity; }

  // Getter for beta
  double get_beta() const { return beta; }

  // Print out all particle info
  void print_info();

};
#endif //PARTICLE_H