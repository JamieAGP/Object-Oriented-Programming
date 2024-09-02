
#ifndef PARTICLE_CATALOGUE_H
#define PARTICLE_CATALOGUE_H

#include "Particle.h"
#include <vector>
#include <iostream>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <set>
#include <algorithm>
#include <numeric>

template <typename T>
class ParticleCatalogue
{
private:
  std::vector<T *> particles;
  std::set<T *> unique_particles;

public:
  // Default constructor. Initializes a new instance of the ParticleCatalogue class with no particles.
  ParticleCatalogue() = default;

  // Destructor. Frees memory for all particle pointers managed by the catalogue and clears the container of particles and unique particles.
  ~ParticleCatalogue()
  {
    for (auto &particle : particles)
    {
      delete particle;
    }
    particles.clear();
    unique_particles.clear();
  }

  // Adds a particle to the catalogue. If the particle is not already present (as determined by a set of unique pointers), it adds the particle to both the vector and the set. If the particle is a duplicate, it prints a warning.
  void add_particle(T *particle)
  {
    // Check if the particle pointer is already added
    if (unique_particles.find(particle) == unique_particles.end())
    {
      particles.push_back(particle);
      unique_particles.insert(particle); // Add to the set of unique pointers
    }
    else
    {
      std::cout << "Warning: Attempt to add a duplicate particle pointer.\n";
    }
  }

  //  Prints information for every particle in the catalogue using each particle's print method.
  void print_all() const
  {
    std::for_each(particles.begin(), particles.end(), [](const T *particle)
                  { particle->print(); });
  }

  //  Returns the total number of particles in the catalogue
  size_t get_number_of_particles() const
  {
    return particles.size();
  }

  // Returns a map where keys are particle type names and values are the counts of particles of each type.
  std::map<std::string, int> get_particle_count_by_type() const
  {
    std::map<std::string, int> counts;
    std::for_each(particles.begin(), particles.end(), [&counts](const T *particle)
                  {
      // Get the type name as a string
      std::string typeName = typeid(*particle).name();

      // Remove the prefix if it exists
      size_t pos = typeName.find_first_not_of("0123456789");
      if (pos != std::string::npos)
      {
        typeName = typeName.substr(pos);
      }

      // Increment the count for the type
      counts[typeName]++; });
    return counts;
  }

  // Calculates and returns the total four-momentum of all particles in the catalogue by summing their individual four-momenta.
  FourMomentum sum_four_momenta() const
  {
    return std::accumulate(particles.begin(), particles.end(), FourMomentum(), [](const FourMomentum &sum, const T *particle)
                           { return sum + particle->get_four_momentum(); });
  }

  // Returns a vector containing pointers to all particles in the catalogue that can be dynamically cast to a specified subtype.
  template <typename SubType>
  std::vector<SubType *> get_vector_of_subtype() const
  {
    std::vector<SubType *> sub_container;
    for (const auto &particle : particles)
    {
      SubType *casted = dynamic_cast<SubType *>(particle);
      if (casted != nullptr)
      {
        sub_container.push_back(casted);
      }
    }
    return sub_container;
  }

  // Returns a new ParticleCatalogue that contains all particles of a specified subtype.
  template <typename SubType>
  ParticleCatalogue<SubType> get_sub_container() const
  {
    ParticleCatalogue<SubType> sub_container;
    for (const auto &particle : particles)
    {
      if (const SubType *casted = dynamic_cast<const SubType *>(particle))
      {
        sub_container.add_particle(const_cast<SubType *>(casted));
      }
    }
    return sub_container;
  }

  // Similar to get_sub_container<SubType>(), but returns a new ParticleCatalogue containing particles of the same type as the specified subtype.
  template <typename SubType>
  ParticleCatalogue<T> get_sub_container_of_same_type() const
  {
    ParticleCatalogue<T> sub_container;
    for (const auto &particle : particles)
    {
      if (const SubType *casted = dynamic_cast<const SubType *>(particle))
      {
        sub_container.add_particle(const_cast<SubType *>(casted));
      }
    }
    return sub_container;
  }

  // Prints information for all particles in the catalogue that are of a specified type or a derived type, using dynamic casting.
  template <typename SubType>
  void print_info_by_type() const
  {
    std::for_each(particles.begin(), particles.end(), [](const T *particle)
                  {
      const SubType *casted = dynamic_cast<const SubType *>(const_cast<T *>(particle));
      if (casted)
      {
        casted->print();
      } });
  }

  // Prints information for all particles in the catalogue that are of the exact specified type, using RTTI (Run-Time Type Information)
  template <typename SubType>
  void print_info_by_exact_type() const
  {
    std::for_each(particles.begin(), particles.end(), [](const T *particle)
                  {
          if (typeid(*particle) == typeid(SubType))
          {
              particle->print();
          } });
  }

  // Returns a vector of pointers to all particles that have a specific label.
  std::vector<Particle *> find_particles_by_label(const std::string &label) const
  {
    std::vector<Particle *> result;
    std::copy_if(particles.begin(), particles.end(), std::back_inserter(result), [&label](const T *particle)
                 { return particle->get_label() == label; });
    return result;
  }

  // Retrieves a vector containing the labels of all particles in the catalogue
  std::vector<std::string> get_all_labels() const
  {
    std::vector<std::string> labels;
    for (const auto &particle : particles)
    {
      labels.push_back(particle->get_label());
    }
    return labels;
  }

  // Overloaded functions to remove particles via label, pointer, index or type
  void remove_particle(const std::string &label)
  {
    particles.erase(std::remove_if(particles.begin(), particles.end(), [&label, this](const T *particle)
                                   {
        if (particle->get_label() == label) {
            unique_particles.erase(const_cast<T*>(particle));
            return true;
        }
        return false; }),
                    particles.end());
  }
  void remove_particle(const T *particle)
  {
    particles.erase(std::remove(particles.begin(), particles.end(), particle), particles.end());
    unique_particles.erase(const_cast<T *>(particle));
  }
  void remove_particle(size_t index)
  {
    if (index < particles.size())
    {
      unique_particles.erase(particles[index]);
      particles.erase(particles.begin() + index);
    }
  }
  template <typename SubType>
  void remove_particles_by_type()
  {
    auto it = std::remove_if(particles.begin(), particles.end(), [](const Particle *particle)
                             { return dynamic_cast<const SubType *>(particle) != nullptr; });
    for (auto ptr = it; ptr != particles.end(); ++ptr)
    {
      unique_particles.erase(*ptr);
      delete *ptr;
    }
    particles.erase(it, particles.end());
  }
  // Clears the catalogue of all particles, properly freeing memory and clearing the internal containers
  void clear_all_particles()
  {
    for (auto &particle : particles)
    {
      delete particle;
    }
    particles.clear();
    unique_particles.clear();
  }
  
  // Sorts the particles in the catalogue according to a specified comparator function. If reverse is true, the sort is in descending order.
  template <typename Compare>
  void sort_particles_by_property(Compare compare, bool reverse = false)
  {
    if (reverse)
    {
      std::sort(particles.rbegin(), particles.rend(), compare);
    }
    else
    {
      std::sort(particles.begin(), particles.end(), compare);
    }
  }

  // Applies a function to all particles or to particles with specified labels.
  template <typename Function, typename... Args>
  void apply_function_to_particles(Function function, Args &&...args, const std::vector<std::string> &labels = {})
  {
    if (labels.empty())
    {
      for (const auto &particle : particles)
      {
        (particle->*function)(std::forward<Args>(args)...);
      }
    }
    else
    {
      for (const auto &label : labels)
      {
        for (Particle *particle : find_particles_by_label(label))
        {
          (particle->*function)(std::forward<Args>(args)...);
        }
      }
    }
  }

  // Applies a function to all particles of a specified subtype.
  template <typename SubType, typename Function, typename... Args>
  void apply_function_to_particles(Function function, Args &&...args)
  {
    for (const auto &particle : particles)
    {
      SubType *casted = dynamic_cast<SubType *>(particle);
      if (casted)
      {
        (casted->*function)(std::forward<Args>(args)...);
      }
    }
  }
};

#endif
