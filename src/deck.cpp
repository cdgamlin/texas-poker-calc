#include "deck.hpp"

Deck::Deck() {
        // Create deck
        deckSize = 52;
        int suitIndex ;
        for (int i = 0; i < deckSize ; ++i) {
            suitIndex = i % 4;
            // Card type in lower 52 bits
            deck[i] = static_cast<uint64_t>(1) << i;
            // Suit count in upper 12 bits (4 groups of 3 bits)
            deck[i] |= static_cast<uint64_t>(1) << (suitIndex * 3 + 52);
        }
        shuffle();
}

void Deck::shuffle() {
    // Fast shuffling - due to how cards are removed and dealt
    cardsLeft = deckSize;
}

void Deck::remove(uint64_t cards) {
    // Remove cards from deck
    // by placing them on the top of the permanent inactive pile
    // This helps to make the shuffling algorithm trivial

    // Remove suit count information using bitwise AND with a mask
    // to isolate the lower 52 bits representing card types.
    cards &= 0xFFFFFFFFFFFFF;

    // Keep looping though deck until all cards are removed
    while (cards) {
        for (int i = 0; i < deckSize; ++i) {
            if (deck[i] & cards) {
                // Remove cards from list of cards to be removed using bitwise AND
                // with the bitwise NOT of deck[i] to clear the corresponding bits.
                cards &= ~deck[i];
                // Swap card with top of permanent inactive pile
                std::swap(deck[i], deck[deckSize - 1]);
                deckSize--;
            }
            if (cards == 0) {
                break;
            }
        }
    }
    shuffle();
}

uint64_t Deck::deal(int numberOfCards ) {
    // Uses a swapping algorithm to make things fast
    // so deck needs no more processing after random card is selected
    // and the shuffling algorithm becomes trivial
    uint64_t cardsDealt = 0;
    for (int i = 0; i < numberOfCards ; ++i) {
        // Add random card to dealt pile using bitwise OR
        // to accumulate the bits representing the dealt cards.
        int cardIndex = rand() % cardsLeft ;
        cardsDealt |= deck[cardIndex];
        // Move card to top of temporary inactive pile
        std::swap(deck[cardIndex], deck[cardsLeft - 1]);
        cardsLeft --;
    }
    return cardsDealt ;
}

// // For debugging purposes only:
// // Return count of cards remaining in deck
// int Deck::getcardsLeft () const {
//     return cardsLeft ;
// }

// // For debugging purposes only:
// // List cards remaining in deck
// uint64_t Deck::listCards() {
//     uint64_t cards = 0;
//     for (int i = 0; i < cardsLeft ; ++i) {
//         cards |= deck[i];
//     }
//     return cards;
// }
