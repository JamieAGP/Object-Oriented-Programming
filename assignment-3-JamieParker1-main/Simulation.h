#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <vector>
#include <map>
#include <string>


class simulation
{
private:
  vector<detector_instance> detectors; // List of detector_instances in the simulation
  vector<particle_instance> particles; // List of particles to simulate

public:
  // Default constructor
  simulation() : detectors({}), particles({}) {}

  // Paramaterised constructor
  simulation(vector<detector_instance> detectors, vector<particle_instance> particles)
      : detectors(detectors), particles(particles) {}

  // Destructor
  ~simulation() {}

  // Adds detector to simulation
  void add_detector(const detector_instance &newDetector){detectors.push_back(newDetector);}

  // Adds particle to simulation
  void add_particle(const particle_instance &newParticle){particles.push_back(newParticle);}

  // Runs simulation
  void run_simulation(); 
};
#endif