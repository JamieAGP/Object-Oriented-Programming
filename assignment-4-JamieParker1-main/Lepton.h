// Lepton.h - Interface file
#include <vector>
#include <iostream>
#include <string>

class Lepton {
private:
    std::vector<double>* P; // Dynamically allocated four-momentum (E, Px, Py, Pz)
    double rest_mass;
    double charge;
    std::string type;

    void deep_copy(const Lepton &source);

public:
    Lepton(double E, double px, double py, double pz, double mass, double q, std::string particleType);
    Lepton(const Lepton& other);
    Lepton(Lepton&& other) noexcept;
    ~Lepton();

    Lepton& operator=(const Lepton& other);
    Lepton& operator=(Lepton&& other) noexcept;

    void set_E(double E);
    void set_Px(double px);
    void set_Py(double py);
    void set_Pz(double pz);

    double get_E() const { return (*P)[0]; }
    double get_Px() const { return (*P)[1]; }
    double get_Py() const { return (*P)[2]; }
    double get_Pz() const { return (*P)[3]; }

    std::string get_type() const { return type; }
    double get_charge() const { return charge; }
    double get_rest_mass() const { return rest_mass; }

    Lepton operator+(const Lepton& other) const;
    double dot_product(const Lepton& other) const;
};

std::ostream& operator<<(std::ostream& os, const Lepton& lepton);
