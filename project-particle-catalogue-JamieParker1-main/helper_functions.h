#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "FourMomentum.h"
#include "Particle.h"
#include "ParticleCatalogue.h"

#include "showcase.h"
#include "user_interface.h"

#include "leptons/Lepton.h"
#include "leptons/Electron.h"
#include "leptons/Muon.h"
#include "leptons/Tau.h"
#include "leptons/Neutrino.h"

#include "bosons/Boson.h"
#include "bosons/Photon.h"
#include "bosons/Gluon.h"
#include "bosons/Z.h"
#include "bosons/W.h"
#include "bosons/Higgs.h"

#include "quarks/Quark.h"
#include "quarks/QuarkTemplate.h"
#include "quarks/IndividualQuarks.h"

#include <vector>
#include <thread> 
#include <chrono> 
#include <iostream>
#include <string>
#include <typeindex>

// Convert enum types to string
std::string to_string(Colour colour);
std::string to_string(DecayType decay_type);

// Checks if a colour is an anticolour
bool is_anti_colour(Colour colour);
// Gets the anti colour of a colour
Colour get_anti_colour(Colour colour);
// Check if group of colours is colour neutral
bool is_colour_neutral(Colour colour1, Colour colour2, Colour colour3 = Colour::None);
bool is_colour_neutral(std::vector<Colour> colour_charges);
// Checks if a decay type is in a vector
bool contains_decay_type(const std::vector<DecayType> &decay_types, DecayType type_to_find);
// Calculates the total energy of two particles from their momentum
double energy_sum(double momentum, double product1_rest_mass, double product2_rest_mass);
// Finds the momentum of decay products for two bodies
double find_momentum_of_products(double product1_rest_mass, double product2_rest_mass, double decay_particle_rest_mass, double tolerance = 1e-6);
// Calculates the total energy of three particles from their momentum
double energy_sum_three_body(double p1x, double p2x, double p2y, double m1, double m2, double m3);
// Finds the momentum of decay products for three bodies
std::vector<double> find_momentum_of_products_three_body(double product1_rest_mass, double product2_rest_mass, double product3_rest_mass, double decay_particle_rest_mass, double tolerance = 1e-5);

// Clears the output screen
void clear_screen();
// Clears input buffer
void clear_input_buffer();
// Prints a string with elipses for a certain tie
void print_loading_string(const std::string &input_string, int seconds, bool new_new_line = false, bool elipses = true);
// Pauses program until user hits enter
void wait_for_enter(const std::string &prompt = "");

// Fill catalogue classes
void fill_leptons(ParticleCatalogue<Particle> &catalogue);
void fill_anti_leptons(ParticleCatalogue<Particle> &catalogue);
void fill_bosons(ParticleCatalogue<Particle> &catalogue);
void fill_quarks(ParticleCatalogue<Particle> &catalogue);
void fill_anti_quarks(ParticleCatalogue<Particle> &catalogue);
void fill_particles(ParticleCatalogue<Particle> &catalogue);
void fill_anti_particles(ParticleCatalogue<Particle> &catalogue);
void fill_catalogue(ParticleCatalogue<Particle> &catalogue);

// Sort catalogue classes by a property, only for a catalogue of Particle type
void sort_by_rest_mass(ParticleCatalogue<Particle> &catalogue);
void sort_by_charge(ParticleCatalogue<Particle> &catalogue);
void sort_by_spin(ParticleCatalogue<Particle> &catalogue);
void sort_by_energy(ParticleCatalogue<Particle> &catalogue);
void sort_by_momentum(ParticleCatalogue<Particle> &catalogue);
void sort_by_velocity(ParticleCatalogue<Particle> &catalogue);

#endif // HELPER_FUNCTIONS_