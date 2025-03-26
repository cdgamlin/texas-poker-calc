#ifndef HANDCONVERTER_HPP
#define HANDCONVERTER_HPP

#include <cstdint>
#include <string>
#include <unordered_map>

class HandConverter {
private:
    // Lookup tables for ranks and suits
    const std::unordered_map<char, int> rankLookup = {
        {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3}, {'6', 4},
        {'7', 5}, {'8', 6}, {'9', 7}, {'T', 8}, {'J', 9},
        {'Q', 10}, {'K', 11}, {'A', 12}
    };

    const std::unordered_map<char, int> suitLookup = {
        {'C', 0}, {'D', 1}, {'H', 2}, {'S', 3}
    };

    const char rankChars[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    const char suitChars[4] = {'c', 'd', 'h', 's'};

public:
    uint64_t stringToHand(const std::string& cardsAsString) const;
    std::string handToString(uint64_t cards, bool spaces) const;
};

#endif // HANDCONVERTER_HPP
