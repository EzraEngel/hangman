#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "word_list.cpp"
#include "game.cpp"

using namespace std;

int num_strikes = 12;

int main() {
  Game new_game;
  new_game.set_strikes(num_strikes);
  new_game.set_word();
  new_game.play_intro();
  new_game.set_progress();
  while (!new_game.is_over()) {
    new_game.play_game();
    new_game.check_win();
    new_game.check_loss();
  }
  return 0;
};