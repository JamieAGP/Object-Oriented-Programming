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

#include <sstream>


int main()
{
  ParticleCatalogue<Particle> user_catalogue;
  main_menu_navigation(user_catalogue);

  print_loading_string("Creating catalogue", 4, true);
  ParticleCatalogue<Particle> catalogue;

  print_loading_string("Instantiating all particles", 4, true);
  // Leptons
  Tau *tau = new Tau();
  tau->set_label("general tau");
  Electron *electron = new Electron();
  electron->set_label("general electron");
  Muon *muon = new Muon();
  muon->set_label("general muon");
  Neutrino *tau_neutrino = new Neutrino("tau");
  tau_neutrino->set_label("general tau neutrino");
  Neutrino *electron_neutrino = new Neutrino("electron");
  electron_neutrino->set_label("general electron neutrino");
  Neutrino *muon_neutrino = new Neutrino("muon");
  muon_neutrino->set_label("general muon neutrino");

  // Anti-leptons
  Tau *anti_tau = new Tau(-1);
  anti_tau->set_label("general anti-tau");
  Electron *anti_electron = new Electron(-1);
  anti_electron->set_label("general anti-electron");
  Muon *anti_muon = new Muon(-1);
  anti_muon->set_label("general anti-muon");
  Neutrino *anti_tau_neutrino = new Neutrino("tau", -1);
  anti_tau_neutrino->set_label("general anti-tau neutrino");
  Neutrino *anti_electron_neutrino = new Neutrino("electron", -1);
  anti_electron_neutrino->set_label("general anti-electron neutrino");
  Neutrino *anti_muon_neutrino = new Neutrino("muon", -1);
  anti_muon_neutrino->set_label("general anti-muon neutrino");

  // Bosons
  Photon *photon = new Photon();
  photon->set_label("general photon");
  Gluon *gluon = new Gluon();
  gluon->set_label("general gluon");
  Z *z = new Z();
  z->set_label("general z");
  W *w_plus = new W();
  w_plus->set_label("general w");
  W *w_minus = new W(-1);
  w_minus->set_label("general w");
  Higgs *higgs = new Higgs();
  higgs->set_label("general higgs");

  // Quarks
  Up *up = new Up();
  up->set_label("general up");
  Down *down = new Down();
  down->set_label("general down");
  Bottom *bottom = new Bottom();
  bottom->set_label("general bottom");
  Charm *charm = new Charm();
  charm->set_label("general charm");
  Top *top = new Top();
  top->set_label("general top");
  Strange *strange = new Strange();
  strange->set_label("general strange");

  // Anti-quarks
  Up *anti_up = new Up(true);
  anti_up->set_label("general anti-up");
  Down *anti_down = new Down(true);
  anti_down->set_label("general anti-down");
  Bottom *anti_bottom = new Bottom(true);
  anti_bottom->set_label("general anti-bottom");
  Charm *anti_charm = new Charm(true);
  anti_charm->set_label("general anti-charm");
  Top *anti_top = new Top(true);
  anti_top->set_label("general anti-top");
  Strange *anti_strange = new Strange(true);
  anti_strange->set_label("general anti-strange");

  print_loading_string("Adding particles to catalogue", 4, true);
  // Adding particles to catalogue
  catalogue.add_particle(tau);
  catalogue.add_particle(electron);
  catalogue.add_particle(muon);
  catalogue.add_particle(tau_neutrino);
  catalogue.add_particle(electron_neutrino);
  catalogue.add_particle(muon_neutrino);
  catalogue.add_particle(anti_tau);
  catalogue.add_particle(anti_electron);
  catalogue.add_particle(anti_muon);
  catalogue.add_particle(anti_tau_neutrino);
  catalogue.add_particle(anti_electron_neutrino);
  catalogue.add_particle(anti_muon_neutrino);
  catalogue.add_particle(photon);
  catalogue.add_particle(gluon);
  catalogue.add_particle(z);
  catalogue.add_particle(w_plus);
  catalogue.add_particle(w_minus);
  catalogue.add_particle(higgs);
  catalogue.add_particle(up);
  catalogue.add_particle(down);
  catalogue.add_particle(bottom);
  catalogue.add_particle(top);
  catalogue.add_particle(charm);
  catalogue.add_particle(strange);
  catalogue.add_particle(anti_up);
  catalogue.add_particle(anti_down);
  catalogue.add_particle(anti_bottom);
  catalogue.add_particle(anti_top);
  catalogue.add_particle(anti_charm);
  catalogue.add_particle(anti_strange);

  print_loading_string("Getting total number of particles", 4, true);
  std::cout << "Total number of particles: " << catalogue.get_number_of_particles();

  print_loading_string("\nGetting the number of particles of each type", 4, true);
  std::map<std::string, int> particle_counts = catalogue.get_particle_count_by_type();
  for (const auto &pair : particle_counts)
  {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }

  print_loading_string("\nPrinting all particle information", 4, true);
  catalogue.print_all();

  wait_for_enter("\nHit Enter to continue to next demonstration\n");
  print_loading_string("\nPrinting all lepton information", 4, true);
  catalogue.print_info_by_type<Lepton>();

  wait_for_enter("\nHit Enter to continue to next demonstration\n");

  print_loading_string("\nSorting particles by rest mass", 4, true);
  sort_by_rest_mass(catalogue);
  std::cout << "Particles sorted by rest mass:\n";
  catalogue.print_all();
  wait_for_enter("\nHit Enter to continue to next demonstration\n");

  print_loading_string("\nApplying a function to all particles - setting the label to 'random label'", 4, true);
  catalogue.apply_function_to_particles<Particle>(&Particle::set_label, "random label");
  catalogue.print_all();
  wait_for_enter("\nHit Enter to continue to next demonstration\n");

  print_loading_string("\nRemoving all particles with the label 'random label'", 4, true);
  catalogue.remove_particle("random label");
  wait_for_enter("\nHit Enter to continue to next demonstration\n");


  print_loading_string("\nCreating four momentum object for an Electron, with incorrect values", 4, true);
  std::unique_ptr<FourMomentum> wrong_four_momentum = std::make_unique<FourMomentum>(100, 0, 0, 0);
  std::cout <<"Wrong four momentum: " <<  *wrong_four_momentum << std::endl;

  Electron test_electron;
  print_loading_string("\nAttempting to set to Electron object", 4, true);
  try
  {
    test_electron.set_four_momentum(std::move(wrong_four_momentum));
  }
  catch(const std::exception& e)
  {
    std::cerr << "Caught error: " <<  e.what() << '\n';
  }

  print_loading_string("\nIf you want to set the four momentum of a particle, you can pass the rest mass to the Four Momentum constructor to make a four momentum with an invariant mass consistent with its invariant mass", 5, true);
  std::unique_ptr<FourMomentum> new_four_momentum = std::make_unique<FourMomentum>(Mass::electron, 100, 0, 0, true);
  std::cout << "New Four Momentum: " << *new_four_momentum << std::endl;
  test_electron.set_four_momentum(std::move(new_four_momentum));


  print_loading_string("\nIn this program, the Higgs, W and Z bosons, along with the Tau lepton, can all decay", 4);
  // Creating Higgs object
  print_loading_string("\nCreating Higgs object", 4, true);
  Higgs higgs_test;
  std::unique_ptr<FourMomentum> higgs_fm = std::make_unique<FourMomentum>(Mass::higgs, 0, 0, 0, true);
  higgs_test.set_four_momentum(std::move(higgs_fm));
  higgs_test.print();

  // Basic decay: Higgs -> b + anti-b
  print_loading_string("\nBasic decay: Higgs -> b + anti-b", 4, true);
  std::unique_ptr<Bottom> b_decay_1 = std::make_unique<Bottom>();
  std::unique_ptr<Bottom> anti_b_decay_2 = std::make_unique<Bottom>(true);
  std::vector<std::unique_ptr<Particle>> higgs_real_decay_products;
  higgs_real_decay_products.push_back(std::move(b_decay_1));
  higgs_real_decay_products.push_back(std::move(anti_b_decay_2));
  higgs_test.auto_set_decay_products(std::move(higgs_real_decay_products), DecayType::Weak);
  higgs_test.print();

  // Showcasing momentum conservation
  print_loading_string("\nWe can see that Four Momentum has been conserved", 4, true);
  std::cout << "Higgs Four Momentum: " << higgs_test.get_four_momentum() << std::endl;
  std::cout << "Sum of products Four Momentum: " << higgs_test.get_decay_products()[0]->get_four_momentum() + higgs_test.get_decay_products()[1]->get_four_momentum() << std::endl;

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
  higgs_test.auto_set_decay_products(std::move(higgs_virtual_decay_products), DecayType::Weak);
  higgs_test.print();

  // Showcasing momentum conservation
  print_loading_string("\nFour Momentum has still been conserved", 4, true);
  std::cout << "Higgs Four Momentum: " << higgs_test.get_four_momentum() << std::endl;
  std::cout << "Sum of products Four Momentum: " << higgs_test.get_decay_products()[0]->get_four_momentum() + higgs_test.get_decay_products()[1]->get_four_momentum() << std::endl;
  print_loading_string("\nBut the invariant mass of the products is not consistent with their known rest mass", 4, true);
  std::cout << higgs_test.get_decay_products()[0]->get_label() << ": Rest Mass (MeV) = " << higgs_test.get_decay_products()[0]->get_rest_mass() << ", Invariant Mass (MeV) = " << higgs_test.get_decay_products()[0]->get_four_momentum().invariant_mass() << std::endl;
  std::cout << higgs_test.get_decay_products()[1]->get_label() << ": Rest Mass (MeV) = " << higgs_test.get_decay_products()[1]->get_rest_mass() << ", Invariant Mass (MeV) = " << higgs_test.get_decay_products()[1]->get_four_momentum().invariant_mass() << std::endl;

  // Decay chain: Higgs -> Z + Z (virtual), Z -> e + e-
  print_loading_string("\nWe can set decay products for decay products", 4);
  print_loading_string("\nDecay chain: Higgs -> Z + Z (virtual), Z -> e + e-", 4, true);
  std::unique_ptr<Electron> electron_decay = std::make_unique<Electron>();
  std::unique_ptr<Electron> anti_electron_decay = std::make_unique<Electron>(-1);
  electron_decay->set_label("Z1 decay electron");
  anti_electron_decay->set_label("Z1 decay anti-electron");

  std::vector<std::unique_ptr<Particle>> z_decay_1_decay_products;
  z_decay_1_decay_products.push_back(std::move(electron_decay));
  z_decay_1_decay_products.push_back(std::move(anti_electron_decay));
  higgs_test.get_decay_products()[0]->auto_set_decay_products(std::move(z_decay_1_decay_products), DecayType::Weak);
  higgs_test.print();

  // Updating Higgs four-momentum and observing the effect on decay products
  print_loading_string("\nIf we update the Higgs four-momentum", 4, true);
  higgs_test.set_four_momentum(std::make_unique<FourMomentum>(Mass::higgs, 10, 100, 2, true));
  print_loading_string("The Decay products will update to conserve the new four momentum", 4, true);
  higgs_test.print();

  // Showcasing momentum conservation
  print_loading_string("\nFour Momentum has still been conserved", 4, true);
  std::cout << "Higgs Four Momentum: " << higgs_test.get_four_momentum() << std::endl;
  std::cout << "Sum of Higgs products Four Momentum: " << higgs_test.get_decay_products()[0]->get_four_momentum() + higgs_test.get_decay_products()[1]->get_four_momentum() << std::endl;
  print_loading_string("\nIncluding down the decay chain", 4, true);
  std::cout << higgs_test.get_decay_products()[0]->get_label() << " Four Momentum: " << higgs_test.get_decay_products()[0]->get_four_momentum() << std::endl;
  std::cout << "Sum of " << higgs_test.get_decay_products()[0]->get_label() << " products Four Momentum: " << higgs_test.get_decay_products()[0]->get_decay_products()[0]->get_four_momentum() + higgs_test.get_decay_products()[0]->get_decay_products()[1]->get_four_momentum() << std::endl;

  //Attempt to set incorrect decay products
  print_loading_string("Can attempt to set decay products that would violate conservation properties, Higgs -> Up + Up", 4 ,true);
  std::unique_ptr<Up> up_decay_1 = std::make_unique<Up>();
  std::unique_ptr<Up> up_decay_2 = std::make_unique<Up>();
  std::vector<std::unique_ptr<Particle>> higgs_wrong_decay_products;
  higgs_wrong_decay_products.push_back(std::move(up_decay_1));
  higgs_wrong_decay_products.push_back(std::move(up_decay_2));
  higgs_test.auto_set_decay_products(std::move(higgs_wrong_decay_products), DecayType::Weak);
  higgs_test.print();

  print_loading_string("Please re-run the program and go into the program showcase section of the user interface for more demonstrations of this project!", 1, false, false);
  return 0; 
}
