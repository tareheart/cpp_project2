#include <string>
#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <iomanip>
using namespace std;


class Dice{
  private:
    int value;
  public:
    void roll(){
      int initial_num = rand() % 6;
      value = initial_num + 1;
    }
    int reveal() {return value;}
    void setValue(int value) {this->value = value;}
};

const int HAND_SIZE = 5;
class Hand {
  public:
    void show() {
      cout << "Hand: ";
      for (int i = 0; i < HAND_SIZE; i++) {
        cout << my_dice[i].reveal() << " ";
      }
      cout << endl;
    }

    void play() {
      for (int i = 0; i < HAND_SIZE; i++) {
        if (chosen[i] == false) { 
          my_dice[i].roll();
        }
      }
    }

    Dice* getDice(int diceNum) {
      return &my_dice[diceNum];
    }

    void setSelection(string selection) {
      for (int i = 0; i < HAND_SIZE; i++) {
        chosen[i] = false;
      }
      for (int i = 0; i < selection.size(); ++i) {
        char ch = selection[i];
        int index = ch - '1';
        if (index >= 0 && index < HAND_SIZE) {
          chosen[index] = true;
        }
      }
    }

    Hand() {
      for (int i = 0; i < HAND_SIZE; i++) {
        my_dice[i].roll();
      }
    }
  private:
    Dice my_dice[HAND_SIZE];
    bool chosen[HAND_SIZE] = {false};
};


const int ONES = 0;
const int TWOS = 1;
const int THREES = 2;
const int FOURS = 3;
const int FIVES = 4;
const int SIXES = 5;
const int THREE_OF_KIND = 6;
const int FOUR_OF_KIND = 7;
const int FULL_HOUSE = 8;
const int SMALL_STRAIGHT = 9;
const int LARGE_STRAIGHT = 10;
const int CHANCE = 11;
const int YAHTZEE = 12;
const int BOARD_SIZE=13; 

class Game {
  public:
    Game() {
      for (int i = 0; i < BOARD_SIZE; i++) {
        scores[i] = -1;
      }
    }

    int calcScore(Hand* hand, int row) {
      int d_counts[7];
      for(int i = 0; i < 7; i++) {
        d_counts[i] = 0;
      }
      int score = 0;
      for(int i = 0; i < HAND_SIZE; i++) {
        Dice* currentDice = hand ->getDice(i);
        int index = currentDice -> reveal();
        d_counts[index]++;
      } 
      switch (row) {
        case ONES:
        case TWOS:
        case THREES:
        case FOURS:
        case FIVES:
        case SIXES:
          score = d_counts[row + 1] * (row + 1);
          break;
        case THREE_OF_KIND:
        case FOUR_OF_KIND: {
          int min_count;
          if (row == THREE_OF_KIND) {
            min_count = 3;
          } else {
            min_count = 4;
          }
          bool found = false; 
          for (int i = 1; i <= 6; i++) {
            if (d_counts[i] >= min_count) {
              found = true;
              for (int j = 0; j < HAND_SIZE; j++) {
                Dice* dice_now = hand->getDice(j);
                score += dice_now -> reveal();
              }
              break;
            }
          }
          if (!found) {
            score = 0; 
          }
          break;
        }
        case FULL_HOUSE: {
          bool two_found = false;
          bool three_found = false;
          for (int i = 1; i <= 6 && (!two_found || !three_found); i++) {
            if (d_counts[i] == 2) {
              two_found = true;
            } else if (d_counts[i] == 3) {
              three_found= true;
            }
          }
          if (two_found && three_found) {
            score = 25;
          }
          break;
        }
        case SMALL_STRAIGHT:
        case LARGE_STRAIGHT: { 
          int required_num;
          int scoreValue;
          if (row == 9) {
            required_num = 4;
            scoreValue = 30;
          } else {
            required_num = 5;
            scoreValue = 40;
          }
          int current_consq = 0;
          for (int i = 1; i <= 6; i++) {
            if (d_counts[i] > 0) {
              current_consq++;
              if (current_consq >= required_num) {
                score = scoreValue;
                break;
              }
            } else {
              current_consq = 0;
            }
          }
          break;
        }
        case CHANCE: { 
          int total = 0;
          for (int i = 0; i < HAND_SIZE; i++) {
            Dice* temp_dice = hand->getDice(i);
            total += temp_dice ->reveal();
          }
          score = total;
          break;
        }
        case YAHTZEE: {
          for (int i = 1; i <= 6; i++) {
            if (d_counts[i] == 5) {
              score = 50;
              break;
            }
          }
          break;
        }
      }
      return score;
    }

    void show(){ 
      const string categoryNames[BOARD_SIZE] = {
        "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", 
        "Three of a kind", "Four of a kind", "Full house", 
        "Small straight", "Large straight", "Chance", "Yahtzee"
      };
      cout << "Upper Section:" << endl;
      int upperSum = 0;
      for (int i = 0; i < 6; i++) {
        cout << i + 1 << "." << categoryNames[i] << ": ";
        if (scores[i] == -1) {
          cout << "-" << endl;
        } else {
          cout << scores[i] << endl;
          upperSum += scores[i];
        }
      }
      cout << "   Sum: " << upperSum << endl;
      int bonus = (upperSum > 62) ? 35 : 0;
      cout << "   Bonus: " << bonus << endl;
      cout << "Lower Section:" << endl;
      for (int i = 6; i < BOARD_SIZE; i++) {
        cout << i + 1 << "." << categoryNames[i] << ": ";
        if (scores[i] == -1) {
          cout << "-" << endl;
        } else {
          cout << scores[i] << endl;
        }
      }
      int total = upperSum + bonus;
      for (int i = 6; i < BOARD_SIZE; i++) {
        if (scores[i] != -1) {
          total += scores[i];
        }
      }
      cout << "Total: " << total << endl;
    }

    int getUpperScore() { 
      int upperScore = 0;
      int i = 0;
      while (i < 6) {
        if (scores[i] != -1) {
          upperScore += scores[i];
        }
        i++;
      }
      return upperScore;
    }

    int getLowerScore() {
      int lowerScore = 0;
      int i = 6;
      while (i < BOARD_SIZE) {
        if (scores[i] != -1) {
          lowerScore += scores[i];
        }
        i++;
      }
      return lowerScore;
    }

    int getBonusScore() { 
      if (getUpperScore() > 62) {
        return 35;
      }
      return 0;
    }

    int getTotalScore(){
      return getUpperScore() + getLowerScore() + getBonusScore();
    }

    void play(Hand* hand, int row){
      scores[row] = calcScore(hand, row);
    }

    bool isPlayed(int row){
      if (scores[row] != -1) {
        return true;
      } else {
        return false;
      }
    }

    bool isFinished() { 
      for (char score : scores) {
        if (score == -1) {
          return false;
        }
      }
      return true;
    }
  private:
    int scores[BOARD_SIZE];
};


void run() {
  srand(static_cast<unsigned int>(time(0)));
  Game game; 
  for (int i = 1; i <= BOARD_SIZE; i++) {
    Hand hand;
    string keep;
    bool no_roll = false;
    int rolls = 0;
    while (rolls <= 2 && no_roll == false) { 
      game.show();
      hand.show();
      if (rolls <= 1) {
        cout << "Keep Dice(s to stop rolling):";
        getline(cin, keep);
        no_roll = (keep == "s") ? true : false;
        if (no_roll == false) {
          hand.setSelection(keep); 
          hand.play();
        }
      }
      rolls++;
    }
    int combination;
    do {
      cout << "Select a combination to play: ";
      cin >> combination;
      if (combination <= 0 || combination > BOARD_SIZE || game.isPlayed(combination - 1)) {
        cout << "This combination has been played or is not valid.";
      }
    } while (combination <= 0 || combination > BOARD_SIZE || game.isPlayed(combination - 1));
    while (cin.get() != '\n') {
      continue;
    }
    game.play(&hand, combination - 1);  
  }
}


int main() {
  run();
}
