# texas-poker-calc
Fast and efficient poker hand evaluator and simulator in C++ using bit twiddling

## How it Works

The program simulates a large number of poker hands, dealing random cards to the player and opponents. It then evaluates the hands using a fast hand evaluation algorithm to determine the winner. By repeating this process many times, it estimates the probability of the player winning the hand.

### Speed and Efficiency

The program is optimized for speed in several ways:

- **Efficient Hand Evaluation:** The hand evaluation algorithm uses bitwise operations and lookup tables to quickly determine the rank of a hand.
- **Fast Shuffling:** The deck shuffling algorithm is trivial, due to how cards are removed and dealt.
- **Monte Carlo Simulation:** By simulating a large number of hands, the program can provide accurate probability estimates in a reasonable amount of time.

### Performance

On Google Colab, the program can simulate over **1 million hands per second**.
