#ifndef MANAGER_H
#define MANAGER_H
#include <string>

using namespace std;

class manager
{
private:
  vector<particle> defined_particles; // List of predefined and user-created particles
  vector<detector> defined_detectors; // List of predefined and user-created detectors

public:
  void add_particle_type(string type, double rest_mass, int charge); // Non interactive creation of a particle

  void add_detector_type(string type, map<string, double> particle_efficiencies); // Non interactive creation of a detector
  void add_detector_type_interface();                                             // Interactive creation of a detector

  void edit_particle_type(string type); // Edit properties of an existing particle
  void edit_detector_type(string type); // Edit properties of an existing detector

  void delete_particle_type(string type); // Delete a particle type
  void delete_detector_type(string type); // Delete a detector type

  void update_detectors_for_new_particle_type(const particle &particle); // Updates all detectors with a default efficiency for a new particle type

  // Getters
  vector<particle>& get_defined_particles() {return this->defined_particles; } 
  vector<detector> get_defined_detectors() const { return defined_detectors; }
};
#endif


