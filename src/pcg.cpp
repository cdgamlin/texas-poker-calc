#include "pcg.hpp"
#include <ctime>

PCG::PCG(uint64_t seed) {
    state = seed;
}

// Generates the next pseudorandom 32-bit unsigned integer
uint32_t PCG::nextUInt32() {
    // Update the internal state using the linear congruent generator algorithm
    uint64_t oldstate = state;
    state = oldstate * 6364136223846793005ULL + 0xda3e39cb94b95bdbULL;
    // Apply XOR shift and rotation to generate the output
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}
