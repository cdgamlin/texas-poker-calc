#ifndef DECK_HPP
    #define DECK_HPP

    #include <cstdint>   // For fixed-size integer types (uint64_t)
    #include <vector>    // For dynamic arrays
    #include <algorithm> // For std::swap
    #include <random>    // For random number generation

/*
    Represents a standard deck of 52 playing cards.

    This class provides functionality to create, shuffle, remove, and deal cards
    from a deck. It uses a uint64_t array to represent the cards and bitwise
    operations for efficient card manipulation.
 */

    class Deck {
    private:
        uint64_t deck[52]; // Array representing the cards in the deck.
        int deckSize; // Maximum number of cards in the deck.
        int cardsLeft ; // Number of cards remaining in the deck.

    public:
        Deck(); // Constructor to initialize the deck.
        void shuffle(); // Shuffles the deck.
        void remove(uint64_t cards); // Removes specific cards from the deck.
        uint64_t deal(int numberOfCards ); // Deals a specified number of cards.

        // Methods for debugging (commented out):
        // int getcardsLeft () const;
        // uint64_t listCards();
    };

    #endif // DECK_HPP
