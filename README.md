## Yahtzee Game

This C++ program simulates the classic Yahtzee game, allowing players to roll dice and score points based on various combinations. It's a text-based implementation designed to be simple and easy to understand.

### Features
- **Dice Rolling:** The game allows players to roll a set of dice and keep selected dice for rerolls.
- **Scoring Combinations:** Players can choose from various scoring combinations such as ones, twos, full house, etc., and score points accordingly.
- **Modular Code Structure:** Functions are used to manage game logic, enhancing readability and maintainability.
- **Seed-based Randomization:** The game uses seed-based randomization to ensure reproducibility of dice rolls for testing.

### Scoring Combinations
The game supports the following scoring combinations:
1. **Ones to Sixes:** Score the sum of all dice showing the corresponding number.
2. **Three of a Kind:** Score the sum of all dice if at least three show the same number.
3. **Four of a Kind:** Score the sum of all dice if at least four show the same number.
4. **Full House:** Score 25 points if there are three of one number and two of another.
5. **Small Straight:** Score 30 points if there are four sequential numbers.
6. **Large Straight:** Score 40 points if there are five sequential numbers.
7. **Chance:** Score the sum of all dice regardless of the combination.
8. **Yahtzee:** Score 50 points if all five dice show the same number.

### Compilation/Execution
1. Ensure that your system has a C++ compiler installed.
2. Compile the code using the following command: `g++ yahtzee.cpp -o yahtzee`
3. Run the program: `./yahtzee`

### Gameplay
1. **Start the game:** The game initializes with the first roll of the dice.
2. **Commands:**
   - Enter `s` to stop rolling the dice.
   - Select a combination to play by entering its corresponding number.
3. **Winning the Game:** The game ends after all combinations have been played. Aim to score as high as possible!

### Future Enhancements
- **Interactive User Interface:** Implement a graphical user interface for a more engaging experience.
- **Multiplayer Support:** Allow multiple players to compete against each other.
- **Saving Game State:** Add the ability to save and load game progress.

### Contributing
Contributions to the project are welcome. Please ensure to follow the existing coding style and add comments where necessary. For major changes, please open an issue first to discuss what you would like to change.
