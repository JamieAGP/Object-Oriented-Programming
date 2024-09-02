#ifndef QUARK_NAME_H
#define QUARK_NAME_H

template<std::size_t N>
struct QuarkName {
    static constexpr char name[N] = {};
};

#endif // QUARK_NAME_H