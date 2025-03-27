# texas-poker-calc
Fast and efficient poker hand evaluator and simulator in C++ using bit twiddling

## How it Works

Given the players hole cards, any community cards, and number of opponents, the program simulates a large number of poker rounds, dealing random cards to the table and opponents. It then evaluates the hands using a fast hand evaluation algorithm to determine if the player wins (draws counting as wins, as you win a spilt pot). By repeating this a million times, it estimates the probability of the player winning at least part of the pot.

### Speed and Efficiency

The program is optimized for speed in several ways:

- **Efficient Hand Evaluation:** The hand evaluation algorithm uses bitwise operation tricks to quickly determine the rank of a hand.
- **Fast Shuffling:** The deck shuffling algorithm is trivial, due to how cards are removed and dealt.
- **PCG random number generator:** PCG is faster than rand(), with the bonus of better statistical properties.

On [Google Colab](https://colab.research.google.com/drive/1bMS6FuAO9-c2_RVsQWc0lSHAVigE6HHI?usp=sharing), the program can simulate over **1 million hands per second**.

## Usage

To use the program, compile it using the provided Makefile and then run it with the following command-line arguments:

./main `<player_cards>`  `<community_cards>` `<opponent_count>`

Where:

- `<player_cards>`: Your two hole cards, represented as a string of four characters (e.g., "AsKd" for Ace of Spades and King of Diamonds).
- `<community_cards>`: Any community cards, represented as a string of two-character pairs (e.g., "AhQdTc" for Ace of Hearts, Queen of Diamonds, and 10 of Clubs).
- `<opponent_count>`: The number of opponents in the hand.
- Whitespace is ignored and all cards are case insensitive, eg: Ace of Spades can be AS, aS, As, as

For example, to calculate the probability of winning with 2 of Spades and 2 of Diamonds against one opponent with no community cards, you would run the following command:

./main 2s 2d 1

The program will output the estimated win probability as a fraction (e.g., "512612/1000000").

## Building

To build the program, simply run the following command in the project directory:

make

This will compile the source code and create an executable file named `main`.

## Dependencies

The program has no external dependencies other than a standard C++ compiler.

## License

This program is licensed under the MIT License. See the LICENSE file for more information.
