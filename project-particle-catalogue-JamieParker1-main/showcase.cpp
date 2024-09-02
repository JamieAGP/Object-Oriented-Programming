#include "FourMomentum.h"
#include "Particle.h"
#include "ParticleCatalogue.h"
#include "helper_functions.h"

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

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>

// Showcase the basic class hierarchy of particles
// Demonstrates the attributes of the base classes: Particle, Lepton, Quark, and Boson
void showcase_basic_class_hierarchy()
{
  Particle *general_particle = new Particle();
  Lepton *general_lepton = new Lepton();
  Quark *general_quark = new Quark();
  Boson *general_boson = new Boson();

  ParticleCatalogue<Particle> hierarchy_catalogue;
  hierarchy_catalogue.add_particle(general_particle);
  hierarchy_catalogue.add_particle(general_lepton);
  hierarchy_catalogue.add_particle(general_boson);
  hierarchy_catalogue.add_particle(general_quark);

  std::cout << "==== Class Hierarchy Showcase ====\n";
  print_loading_string("Now outputting different class attributes for particle base classes", 4, true);
  print_loading_string("General Particle Attributes", 4, true);
  hierarchy_catalogue.print_info_by_exact_type<Particle>();

  print_loading_string("\nGeneral Lepton Attributes", 4, true);
  hierarchy_catalogue.print_info_by_exact_type<Lepton>();

  print_loading_string("\nGeneral Quark Attributes", 4, true);
  hierarchy_catalogue.print_info_by_exact_type<Quark>();

  print_loading_string("\nGeneral Boson Attributes", 4, true);
  hierarchy_catalogue.print_info_by_exact_type<Boson>();

  wait_for_enter("\n\x1b[33mHit Enter to go back to the menu:\x1b[0m");
}

// Showcase specific particle attributes
// Demonstrates the unique attributes of Electron, Muon, and Neutrino objects
void showcase_particle_attributes()
{
  std::cout << "==== Particle Attribute Showcase ====\n";
  print_loading_string("Specific particles have extra attributes", 4, true);

  // Creating Electron object
  print_loading_string("Creating Electron object", 4, true);
  Electron electron;
  std::unique_ptr<FourMomentum> electron_fm = std::make_unique<FourMomentum>(Mass::electron, 0.2, 0.3, 0.4, true);
  electron.set_four_momentum(std::move(electron_fm));
  electron.set_label("Electron 1");
  electron.print();

  print_loading_string("\nNow attempting to change energy deposits", 4, true);
  std::vector<double> electron_energy_deposit = {2.5, 3.7, 1.2, 0.8};
  std::cout << "New Energy Deposits: " << electron_energy_deposit[0] << ", " << electron_energy_deposit[1] << ", " << electron_energy_deposit[2] << ", " << electron_energy_deposit[3] << std::endl;
  try
  {
    electron.set_energy_deposited_in_layers(electron_energy_deposit);
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << "\nException caught -" << e.what() << std::endl;
  }
  print_loading_string("\nElectron energy deposits remains unchanged", 4, true);
  std::cout << electron.get_energy_deposited_in_layers()[0] << ", " << electron.get_energy_deposited_in_layers()[1] << ", " << electron.get_energy_deposited_in_layers()[2] << ", " << electron.get_energy_deposited_in_layers()[3] << std::endl;

  // Creating Muon object
  print_loading_string("\nCreating Muon object", 4, true);
  std::unique_ptr<FourMomentum> muon_fm = std::make_unique<FourMomentum>(Mass::muon, 1.2, 2.3, 3.4, true);
  Muon muon("Muon1", std::move(muon_fm), true, 1);
  muon.print();

  // Accessing Muon's isolation status
  print_loading_string("\nAccessing Muon's isolation status", 4, true);
  bool is_isolated = muon.get_is_isolated();
  std::cout << "Is Muon isolated? " << (is_isolated ? "Yes" : "No") << std::endl;

  // Creating Neutrino object
  print_loading_string("\nCreating Electron Neutrino object", 4, true);
  std::unique_ptr<FourMomentum> neutrino_fm = std::make_unique<FourMomentum>(1.1e-6, 0.5, 0.6, 0.7, true);
  Neutrino neutrino("Neutrino1", std::move(neutrino_fm), "electron", true, 1);
  neutrino.print();

  // Accessing Neutrino's interaction status
  print_loading_string("\nAccessing Neutrino's interaction status:", 4, true);
  bool has_interacted = neutrino.get_has_interacted();
  std::cout << "Has Neutrino interacted? " << (has_interacted ? "Yes" : "No") << std::endl;

  wait_for_enter("\n\x1b[33mHit Enter to go back to the menu:\x1b[0m");
}

// Showcase the decay product functionality
// Demonstrates the decay processes of Higgs boson and the conservation of four-momentum in decays
void showcase_decay_product_functionality()
{
  std::cout << "==== Decay Product Functionality Showcase ====\n";

  print_loading_string("In this program, the Higgs, W and Z bosons, along with the Tau lepton, can all decay", 4);
  // Creating Higgs object
  print_loading_string("\nCreating Higgs object", 4, true);
  Higgs higgs;
  std::unique_ptr<FourMomentum> higgs_fm = std::make_unique<FourMomentum>(Mass::higgs, 0, 0, 0, true);
  higgs.set_four_momentum(std::move(higgs_fm));
  higgs.print();

  // Basic decay: Higgs -> b + anti-b
  print_loading_string("\nBasic decay: Higgs -> b + anti-b", 4, true);
  std::unique_ptr<Bottom> b_decay_1 = std::make_unique<Bottom>();
  std::unique_ptr<Bottom> anti_b_decay_2 = std::make_unique<Bottom>(true);
  std::vector<std::unique_ptr<Particle>> higgs_real_decay_products;
  higgs_real_decay_products.push_back(std::move(b_decay_1));
  higgs_real_decay_products.push_back(std::move(anti_b_decay_2));
  higgs.auto_set_decay_products(std::move(higgs_real_decay_products), DecayType::Weak);
  higgs.print();

  // Showcasing momentum conservation
  print_loading_string("\nWe can see that Four Momentum has been conserved", 4, true);
  std::cout << "Higgs Four Momentum: " << higgs.get_four_momentum() << std::endl;
  std::cout << "Sum of products Four Momentum: " << higgs.get_decay_products()[0]->get_four_momentum() + higgs.get_decay_products()[1]->get_four_momentum() << std::endl;

  // Virtual decay: Higgs -> Z + Z (virtual)
  print_loading_string("\nVirtual decay: Higgs -> Z + Z (virtual)", 4, true);
  std::unique_ptr<Z> z_decay_1 = std::make_unique<Z>();
  std::unique_ptr<Z> z_decay_2 = std::make_unique<Z>();
  z_decay_1->set_is_virtual(true);
  z_decay_2->set_is_virtual(true);
  z_decay_1->set_label("Z1");
  z_decay_2->set_label("Z2");
  std::vector<std::unique_ptr<Particle>> higgs_virtual_decay_products;
  higgs_virtual_decay_products.push_back(std::move(z_decay_1));
  higgs_virtual_decay_products.push_back(std::move(z_decay_2));
  higgs.auto_set_decay_products(std::move(higgs_virtual_decay_products), DecayType::Weak);
  higgs.print();

  // Showcasing momentum conservation
  print_loading_string("\nFour Momentum has still been conserved", 4, true);
  std::cout << "Higgs Four Momentum: " << higgs.get_four_momentum() << std::endl;
  std::cout << "Sum of products Four Momentum: " << higgs.get_decay_products()[0]->get_four_momentum() + higgs.get_decay_products()[1]->get_four_momentum() << std::endl;
  print_loading_string("\nBut the invariant mass of the products is not consistent with their known rest mass", 4, true);
  std::cout << higgs.get_decay_products()[0]->get_label() << ": Rest Mass (MeV) = " << higgs.get_decay_products()[0]->get_rest_mass() << ", Invariant Mass (MeV) = " << higgs.get_decay_products()[0]->get_four_momentum().invariant_mass() << std::endl;
  std::cout << higgs.get_decay_products()[1]->get_label() << ": Rest Mass (MeV) = " << higgs.get_decay_products()[1]->get_rest_mass() << ", Invariant Mass (MeV) = " << higgs.get_decay_products()[1]->get_four_momentum().invariant_mass() << std::endl;

  // Decay chain: Higgs -> Z + Z (virtual), Z -> e + e-
  print_loading_string("\nWe can set decay products for decay products", 4);
  print_loading_string("\nDecay chain: Higgs -> Z + Z (virtual), Z -> e + e-", 4, true);
  std::unique_ptr<Electron> electron = std::make_unique<Electron>();
  std::unique_ptr<Electron> anti_electron = std::make_unique<Electron>(-1);
  electron->set_label("Z1 decay electron");
  anti_electron->set_label("Z1 decay anti-electron");

  std::vector<std::unique_ptr<Particle>> z_decay_1_decay_products;
  z_decay_1_decay_products.push_back(std::move(electron));
  z_decay_1_decay_products.push_back(std::move(anti_electron));
  higgs.get_decay_products()[0]->auto_set_decay_products(std::move(z_decay_1_decay_products), DecayType::Weak);
  higgs.print();

  // Updating Higgs four-momentum and observing the effect on decay products
  print_loading_string("\nIf we update the Higgs four-momentum", 4, true);
  higgs.set_four_momentum(std::make_unique<FourMomentum>(Mass::higgs, 10, 100, 2, true));
  print_loading_string("The Decay products will update to conserve the new four momentum", 4, true);
  higgs.print();

  // Showcasing momentum conservation
  print_loading_string("\nFour Momentum has still been conserved", 4, true);
  std::cout << "Higgs Four Momentum: " << higgs.get_four_momentum() << std::endl;
  std::cout << "Sum of Higgs products Four Momentum: " << higgs.get_decay_products()[0]->get_four_momentum() + higgs.get_decay_products()[1]->get_four_momentum() << std::endl;
  print_loading_string("\nIncluding down the decay chain", 4, true);
  std::cout << higgs.get_decay_products()[0]->get_label() << " Four Momentum: " << higgs.get_decay_products()[0]->get_four_momentum() << std::endl;
  std::cout << "Sum of " << higgs.get_decay_products()[0]->get_label() << " products Four Momentum: " << higgs.get_decay_products()[0]->get_decay_products()[0]->get_four_momentum() + higgs.get_decay_products()[0]->get_decay_products()[1]->get_four_momentum() << std::endl;

  wait_for_enter("\n\x1b[33mHit Enter to go back to the menu:\x1b[0m");
}

// Showcase the FourMomentum class
// Demonstrates the usage and functionality of the FourMomentum class
void showcase_four_momentum_class()
{
  std::cout << "==== FourMomentum Class Showcase ====\n";

  // Creating FourMomentum objects
  print_loading_string("Creating FourMomentum objects", 4, true);
  FourMomentum fm1(10.0, 2.0, 3.0, 4.0);
  FourMomentum fm2(5.0, 1.0, 2.0, 3.0);
  std::cout << "FourMomentum 1: " << fm1 << std::endl;
  std::cout << "FourMomentum 2: " << fm2 << std::endl;

  // Accessing individual components
  print_loading_string("\nAccessing individual components", 4, true);
  std::cout << "Energy of FourMomentum 1: " << fm1.get_energy() << std::endl;
  std::cout << "Px of FourMomentum 2: " << fm2.get_Px() << std::endl;

  // Performing arithmetic operations
  print_loading_string("\nPerforming arithmetic operations", 4, true);
  FourMomentum fm_sum = fm1 + fm2;
  FourMomentum fm_diff = fm1 - fm2;
  double dot_product = fm1 * fm2;
  std::cout << "Sum of FourMomentum 1 and 2: " << fm_sum << std::endl;
  std::cout << "Difference of FourMomentum 1 and 2: " << fm_diff << std::endl;
  std::cout << "Dot product of FourMomentum 1 and 2: " << dot_product << std::endl;

  // Creating FourMomentum objects from rest-mass
  print_loading_string("\nCreating Four Momentum Objects for a particle of rest mass 10(MeV) with a momentum of 2(MeV)", 4, true);
  FourMomentum particle_fm(10, 2, 0, 0, true);
  std::cout << "Particle's FourMomentum: " << particle_fm << std::endl;

  // Calculating invariant mass
  print_loading_string("\nCalculating invariant mass from this FourMomentum", 4, true);
  double mass = particle_fm.invariant_mass();
  std::cout << "Invariant mass of Particle's FourMomentum: " << mass << std::endl;

  // Calculating velocity components
  print_loading_string("\nCalculating velocity components", 4, true);
  std::cout << "Velocity magnitude of Particle's FourMomentum: " << particle_fm.get_velocity_magnitude() << std::endl;
  std::cout << "Velocity x-component of Particle's FourMomentum: " << particle_fm.get_velocity_x() << std::endl;
  std::cout << "Velocity y-component of Particle's FourMomentum: " << particle_fm.get_velocity_y() << std::endl;
  std::cout << "Velocity z-component of Particle's FourMomentum: " << particle_fm.get_velocity_z() << std::endl;

  // Performing Lorentz boost
  print_loading_string("\nPerforming Lorentz boost to Particles rest frame using these velocity values", 4, true);
  std::vector<long double> v_xyz = particle_fm.get_velocity_vector();
  particle_fm.lorentz_boost(v_xyz);
  std::cout << "Particle's FourMomentum after Lorentz boost: " << particle_fm << std::endl;

  print_loading_string("\nPerforming Lorentz boost using same velocity values", 4, true);
  particle_fm.lorentz_boost(v_xyz);
  std::cout << "Particle's FourMomentum after second identical Lorentz boost: " << particle_fm << std::endl;

  wait_for_enter("\n\x1b[33mHit Enter to go back to the menu:\x1b[0m");
}

// Showcase the ParticleCatalogue class
// Demonstrates the usage and functionality of the ParticleCatalogue class
void showcase_particle_catalogue()
{
  std::cout << "==== Particle Catalogue Showcase ====\n";

  // Creating a particle catalogue
  print_loading_string("Creating a particle catalogue", 4, true);
  ParticleCatalogue<Particle> catalogue;

  // Adding particles to the catalogue
  print_loading_string("Adding only quarks and leptons to the catalogue for demonstration purposes", 4, true);
  fill_leptons(catalogue);
  fill_quarks(catalogue);
  //fill_catalogue(catalogue);

  // Printing all particles in the catalogue
  print_loading_string("Printing all particles in the catalogue", 4, true);
  catalogue.print_all();

  wait_for_enter("\n\x1b[33mHit Enter to go to next step:\x1b[0m");

  // Getting the total number of particles in the catalogue
  print_loading_string("\nGetting the total number of particles in the catalogue", 4, true);
  size_t total_particles = catalogue.get_number_of_particles();
  std::cout << "Total number of particles: " << total_particles << std::endl;

  // Getting the number of particles of each type
  print_loading_string("\nGetting the number of particles of each type", 4, true);
  std::map<std::string, int> particle_counts = catalogue.get_particle_count_by_type();
  for (const auto &pair : particle_counts)
  {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }

  // Summing the four-momenta of all particles
  print_loading_string("\nSumming the four-momenta of all particles", 4, true);
  FourMomentum total_four_momentum = catalogue.sum_four_momenta();
  std::cout << "Total four-momentum: " << total_four_momentum << std::endl;

  // Getting a sub-container of particles of the same kind
  print_loading_string("\nGetting a sub-container of particles of the same kind", 4, true);
  std::vector<Lepton *> leptons = catalogue.get_vector_of_subtype<Lepton>();
  std::cout << "Number of leptons: " << leptons.size() << std::endl;

  wait_for_enter("\n\x1b[33mHit Enter to go to next step:\x1b[0m");

  // Printing information about particles of a specific type
  print_loading_string("\nPrinting information about particles of a specific type", 4, true);
  std::cout << "Leptons:\n";
  catalogue.print_info_by_type<Lepton>();

  wait_for_enter("\n\x1b[33mHit Enter to go to next step:\x1b[0m");

  // Printing information about particles of an exact type
  print_loading_string("\nPrinting information about particles of an exact type", 4, true);
  std::cout << "Electrons:\n";
  catalogue.print_info_by_exact_type<Electron>();

  wait_for_enter("\n\x1b[33mHit Enter to go to next step:\x1b[0m");

  // Sorting particles by rest mass
  print_loading_string("\nSorting particles by rest mass", 4, true);
  sort_by_rest_mass(catalogue);
  std::cout << "Particles sorted by rest mass:\n";
  catalogue.print_all();

  wait_for_enter("\n\x1b[33mHit Enter to go to next step:\x1b[0m");

  // Removing a particle by label
  print_loading_string("\nRemoving a particle by index (can also remove by label and by direct pointer)", 4, true);
  size_t remove_index = 0;
  catalogue.remove_particle(remove_index);
  std::cout << "Particle at index 0 removed.\n";
  catalogue.print_all();

  wait_for_enter("\n\x1b[33mHit Enter to go to next step:\x1b[0m");

  // Applying a function to all particles
  print_loading_string("\nApplying a function to all particles - setting the label to 'random label'", 4, true);
  catalogue.apply_function_to_particles<Particle>(&Particle::set_label, "random label");
  catalogue.print_all();

  wait_for_enter("\n\x1b[33mHit Enter to go back to the menu:\x1b[0m");
}