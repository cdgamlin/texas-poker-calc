#include "handconverter.hpp"
#include <stdexcept>
#include <algorithm>

uint64_t HandConverter::stringToHand(const std::string& cardsAsString) const {
    uint64_t hand = 0;
    for (size_t i = 0; i < cardsAsString.size(); i += 2) {
        // Get rank and suit values using lookup tables
        int rankIndex = rankLookup.at(cardsAsString[i]);
        int suitIndex = suitLookup.at(cardsAsString[i + 1]);

        // Add card type
        // Each card is represented by a unique bit in a 64-bit integer
        // rankIndex * 4 + suitIndex calculates the bit position for the card
        // (1) << (rankIndex * 4 + suitIndex) sets the bit for the card
        hand += static_cast<uint64_t>(1) << (rankIndex * 4 + suitIndex);

        // Add to suit counter
        // The upper 12 bits of the hand integer are used to store suit counts
        // suitIndex * 3 + 52 calculates the bit position for the suit counter
        // (1) << (suitIndex * 3 + 52) sets the bit for the suit counter
        hand += static_cast<uint64_t>(1) << (suitIndex * 3 + 52);
    }
    return hand;
}

std::string HandConverter::handToString(uint64_t cards, bool spaces) const {
    std::string cardsAsString = "";
    for (int rank = 12; rank >= 0; --rank) {
        for (int suit = 3; suit >= 0; --suit) {
            // Check if the bit for the current card is set
            // (cards >> (rank * 4 + suit)) & 1 isolates the bit for the card
            if ((cards >> (rank * 4 + suit)) & 1) {
                cardsAsString += rankChars[rank];
                cardsAsString += suitChars[suit];
                if (spaces) {
                    cardsAsString += " ";
                }
            }
        }
    }
    if (spaces && cardsAsString.length()) {
        cardsAsString.pop_back();
    }
    return cardsAsString;
}
