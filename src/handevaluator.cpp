#include "handevaluator.hpp"

HandEvaluator::HandEvaluator() {
    // Create bit count lookup table
    // Returns how many bits are set in a number
    for (int i = 0; i < 16; ++i) {
        int count = 0;
        int temp = i;
        for (int j = 0; j < 4; ++j) {
            count += (temp & 1); // Check if the last bit is set and increment count
            temp >>= 1; // Right shift to check the next bit
        }
        bitCountTable[i] = count;
    }

    // Initialize hand rank scores
    handRankValues [0] = 0;
    handRankValues [1] = 1;
    handRankValues [2] = 8;
    handRankValues [3] = 32;
    handRankValues [4] = 128;
}

uint64_t HandEvaluator::removeLowestCards(uint64_t hand, int numberOfCards ) const {
    for (int i = 0; i < numberOfCards ; ++i) {
        hand &= hand - 1; // Clears the least significant bit set to 1
    }
    return hand;
}

uint64_t HandEvaluator::shiftCards(uint64_t hand, int posFrom, int posTo) const {
    // Extract bits from posFrom using bitwise AND and right shift
    // (hand >> (posFrom * 13)) shifts the bits to the right by posFrom * 13
    // & 0x1FFF masks the bits to extract only the desired ones
    uint64_t bits = (hand >> (posFrom * 13)) & 0x1FFF;
    hand ^= (bits << (posFrom * 13)); // Clear bits at posFrom
    hand |= (bits << (posTo * 13)); // Set bits at posTo
    return hand;
}

uint64_t HandEvaluator::shiftLowestCard(uint64_t hand, int posFrom, int posTo) const {
    // Extract bits from posFrom using bitwise AND and right shift
    // (hand >> (posFrom * 13)) shifts the bits to the right by posFrom * 13
    // & 0x1FFF masks the bits to extract only the desired ones
    uint64_t bits = (hand >> (posFrom * 13)) & 0x1FFF;
    // Isolate the least significant bit set to 1 using bitwise AND and negation
    // bits &= -bits; sets all bits to 0 except the least significant bit set to 1
    bits &= -bits;
    hand ^= (bits << (posFrom * 13)); // Clear the isolated bit at posFrom
    hand |= (bits << (posTo * 13)); // Set the isolated bit at posTo
    return hand;
}

uint64_t HandEvaluator::evaluate(uint64_t cards) const {
    // This is the inner loop of the simulation
    // so must be written as efficiently as possible

    // Algorithm tests hands from strongest to weakest hand types
    // which allows for early exiting of strong hands

    // Returns hand score:
    // Top 12 bits are used to indicate hand type
    // Bottom 52 bits represent ranking within hand type

        uint64_t cardRank = 0;
        int handType = 0;

        // Check: Straight-Flush
        {
            uint64_t cardMask = 0x11111;
            for (int i = 35; i >= 0; --i) {
                // Check if 5 consecutive ranks are present using bitwise AND and comparison
                if (((cards >> i) & cardMask) == cardMask) {
                    // Highest hand type
                    handType = 255;
                    // std::cout << "Straight-Flush" << std::endl;
                    return (static_cast<uint64_t>(handType ) << 52) | (i/4);
                }
            }
        }

        // Fast stats for hand types other than Straights and Flushes
        {
            int bits = 0;
            for (int rank = 0; rank < 13; ++rank) {
                // Get the 4 bits for the currently assessed rank
                bits = (cards >> (rank*4)) & 0xF;
                // Look up the number of cards in the rank
                bits = bitCountTable[bits];
                // Accumulate hand rank values based on card counts
                handType += handRankValues [bits];
                if (bits != 0) {
                    bits -= 1;
                    cardRank += static_cast<uint64_t>(1) << (13 * bits + rank);
                }
            }
        }

        // Check: 4-of-Kind and Full-House
        switch (handType ) {
            case 131: // 4-of-Kind
                cardRank = removeLowestCards(cardRank, 2);
                // std::cout << "4-of-Kind" << std::endl;
                break;
            case 137: // 4-of-Kind (Quad + Pair)
                handType = 131;
                cardRank = shiftCards(cardRank, 1, 0);
                cardRank = removeLowestCards(cardRank, 1);
                // std::cout << "4-of-Kind" << std::endl;
                break;
            case 160: // 4-of-Kind (Quad + Trips)
                handType = 131;
                cardRank = shiftCards(cardRank, 2, 0);
                // std::cout << "4-of-Kind" << std::endl;
                break;
            case 42: // Full-House
                cardRank = removeLowestCards(cardRank, 2);
                // std::cout << "Full-House" << std::endl;
                break;
            case 48: // Full-House (Trip + 2 Pairs)
                handType = 42;
                cardRank = removeLowestCards(cardRank, 1);
                // std::cout << "Full-House" << std::endl;
                break;
            case 65: // Full-House (2 Trips)
                handType = 42;
                cardRank = removeLowestCards(cardRank, 1);
                cardRank = shiftLowestCard(cardRank, 2, 1);
                // std::cout << "Full-House" << std::endl;
                break;
        }
        // Early return for 4-of-Kind and Full-House
        if (handType >= 42) {
            return (static_cast<uint64_t>(handType ) << 52) | cardRank;
        }

        // Check: Flush
        {
        int suitCounts = cards >> 52;
            for (int suit = 0; suit < 4; ++suit) {
                int suitCount = ((suitCounts >> (suit*3)) & 0x7);
                if (suitCount >= 5){
                    // Remove cards that arent flush suit
                    handType = 41;
                    uint64_t cardMask = 0x1111111111111;
                    cardMask <<= suit;
                    cards = cards & cardMask;
                    // Remove any excess cards
                    cards = removeLowestCards(cards, suitCount - 5);
                    // std::cout << "Flush" << std::endl;
                    return (static_cast<uint64_t>(handType ) << 52) | (cards >> suit);
                }
            }
        }

        // Check: Straight
        {
            // Determine what card ranks are in hand
            int cardsPresent = 0;
            for (int i = 0; i < 4; ++i) {
                cardsPresent |= (cardRank >> (i * 13));
            }
            // Scan to detect a Straight
            uint64_t cardMask = 0x1F;
            for (int i = 8; i >= 0; --i) {
                if (((cardsPresent >> i) & cardMask) == cardMask) {
                    handType = 39;
                    // std::cout << "Straight" << std::endl;
                    return (static_cast<uint64_t>(handType ) << 52) | i;
                }
            }
        }

        // Process all remaining hand types
        switch (handType ) {
            case 36: // Trips
                cardRank = removeLowestCards(cardRank, 2);
                // std::cout << "Trips" << std::endl;
                break;
            case 19: // 2 Pair
                cardRank = removeLowestCards(cardRank, 2);
                // std::cout << "2 Pair" << std::endl;
                break;
            case 25: // 2 Pair (3 Pairs)
                handType = 19;
                cardRank = shiftLowestCard(cardRank, 1, 0);
                cardRank = removeLowestCards(cardRank, 1);
                // std::cout << "2 Pair" << std::endl;
                break;
            case 13: // Pair
                cardRank = removeLowestCards(cardRank, 2);
                // std::cout << "Pair" << std::endl;
                break;
            case 7: // High card
                cardRank = removeLowestCards(cardRank, 2);
                // std::cout << "High card" << std::endl;
                break;
        }

        return (static_cast<uint64_t>(handType ) << 52) | cardRank;
    }
