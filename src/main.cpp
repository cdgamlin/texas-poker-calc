#include <iostream>
#include <string>
#include <algorithm>
// #include <bitset> // only used for debugging
#include "deck.hpp"
#include "handconverter.hpp"
#include "handevaluator.hpp"

int main(int argc, char* argv[]) {
    Deck deck;
    HandConverter handConverter;
    HandEvaluator handEvaluator;

    // Concatenate all arguments into a single string
    std::string commandLineArgs;
    for (int i = 1; i < argc; ++i) {
        commandLineArgs += argv[i];
    }

    // Remove whitespace and convert to uppercase
    commandLineArgs.erase(std::remove_if(commandLineArgs.begin(), commandLineArgs.end(), ::isspace), commandLineArgs.end());
    std::transform(commandLineArgs.begin(), commandLineArgs.end(), commandLineArgs.begin(), ::toupper);

    // Extract number of opponentCount from input
    int opponentCount = commandLineArgs[commandLineArgs.length() - 1] - '0';
    if (opponentCount < 1 || opponentCount > 9) {
        throw std::runtime_error("Invalid number of opponentCount");
    }

    // Extract cards from input
    if (commandLineArgs.length() < 5) {
        throw std::runtime_error("Not enough player cards: Need 2 cards");
    }
    uint64_t playerCards = handConverter.stringToHand(commandLineArgs.substr(0, 4));
    uint64_t communityCards = handConverter.stringToHand(commandLineArgs.substr(4, commandLineArgs.length()-5));
    int CommunityCardsNeeded = 5 - (commandLineArgs.length()-5)/2;
    if (CommunityCardsNeeded < 0) {
        throw std::runtime_error("Too many community cards: 5 cards max");
    }

    deck.remove(playerCards + communityCards);

    // // Show what the player can see
    // std::cout << handConverter.handToString(playerCards, true) << std::endl;
    // std::cout << handConverter.handToString(communityCards, true) << std::endl;

    // // Some useful stuff for debugging the hand evaluator
    // uint64_t score = handEvaluator.evaluate(playerCards + communityCards);
    // std::cout << std::bitset<64>(playerCards + communityCards) << std::endl;
    // std::cout << "------------AAAAKKKKQQQQJJJJTTTT99998888777766665555444433332222" << std::endl;
    // std::cout << std::bitset<64>(score) << std::endl;
    // std::cout << "----76543210AKQJT98765432AKQJT98765432AKQJT98765432AKQJT98765432" << std::endl;
    // std::cout << (score>>52) << std::endl;

    // Run the simulation
    int winCount = 0;
    int numberOfSimulations = 1000000;
    for (int sim = 0; sim < numberOfSimulations ; ++sim) {
        deck.shuffle();
        uint64_t currentCommunityCards = communityCards + deck.deal(CommunityCardsNeeded);
        uint64_t playerHandScore = handEvaluator.evaluate(playerCards + currentCommunityCards);
        int playerWon = 1;
        for (int opponent = 0; opponent < opponentCount; ++opponent) {
            uint64_t opponentCards = deck.deal(2);
            uint64_t opponentCountcore = handEvaluator.evaluate(opponentCards + currentCommunityCards);
            // Draw is treated as a win, as it winCount a split pot
            if (opponentCountcore > playerHandScore ) {
                playerWon = 0;
                break;
            }
        }
        winCount += playerWon;
    }

    // Output results
    std::cout << winCount << "/" << numberOfSimulations << std::endl;

	return 0;
}
