#ifndef PCG_HPP
#define PCG_HPP

#include <cstdint>
#include <ctime>

/*
    Provides a pseudorandom number generator (PRNG).

    This class implements a PCG (Permutation Congruential Generator) 
    for quickly generating high-quality pseudorandom numbers. It's used 
    for drawing cards randomly from the deck.
 */

class PCG {
private:
    uint64_t state;

public:
    PCG(uint64_t seed = time(0)); // Constructor, initializes with a seed
    uint32_t nextUInt32(); // Generates the next pseudorandom 32-bit unsigned integer
};

#endif // PCG_HPP
