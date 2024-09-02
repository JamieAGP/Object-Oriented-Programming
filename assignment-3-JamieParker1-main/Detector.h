#ifndef DETECTOR_H
#define DETECTOR_H

using namespace std;
class detector
{
private:
  string type;                               // Type of the detector (e.g., tracker, calorimeter)
  map<string, double> particle_efficiencies; // Efficiencies for detecting each particle type
public:
  // Default constructor
  detector() : type(""), particle_efficiencies({}) {}

  // Paramaterised constructor
  detector(string type, map<string, double> particle_efficiencies)
      : type(type), particle_efficiencies(particle_efficiencies) {}

  // Destructor
  ~detector() {}

  // Getter functions
  string get_type() const {return type; }
  map<string, double> get_particle_efficiencies() const { return particle_efficiencies; }

  // 
  void print_info();
};

class detector_instance : public detector {
private:
    bool status;   // Status of the detector (true for on, false for off)
    vector<particle_instance*> particles_tracked; // Particles tracked by the detector

public:
    // Constructor that takes an existing detector object, status, and optionally a list of particles tracked
    detector_instance(const detector& d, bool status, const vector<particle_instance*>& particles_tracked = {}) 
        : detector(d), status(status), particles_tracked(particles_tracked) {}

    // Destructor - handle the deletion of particle_instance pointers if ownership is transferred
    ~detector_instance() {}

    // Getter for status
    bool get_status() const { return status; }

    // Getter for particles tracked
    const vector<particle_instance*>& get_particles_tracked() const { return particles_tracked; }

    // Function to add a particle instance to the tracking list
    void track_particle(particle_instance* particle) {particles_tracked.push_back(particle); }

    // Function to change the detector's status
    void set_status(bool new_status) {status = new_status; }

    // Function to print out all detector info
    void print_info();

    
};
#endif