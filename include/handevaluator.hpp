#ifndef HANDEVALUATOR_HPP
#define HANDEVALUATOR_HPP

#include <cstdint>

/*
    Determines the rank of a poker hand.

    This class provides functionality to evaluate a texas poker hand 
    and determine its rank according to standard poker rules. It uses 
    efficient bitwise operations for hand comparison and ranking.
 */

class HandEvaluator {
private:
    int bitCountTable[16];
    int handRankValues[5];

public:
    HandEvaluator();
    uint64_t evaluate(uint64_t cards) const;
    uint64_t removeLowestCards(uint64_t hand, int numberOfCards) const;
    uint64_t shiftCards(uint64_t hand, int posFrom, int posTo) const;
    uint64_t shiftLowestCard(uint64_t hand, int posFrom, int posTo) const;
};

#endif // HANDEVALUATOR_HPP
