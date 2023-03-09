#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "word_list.cpp"
#include "game.cpp"

using namespace std;

int num_tries = 12;

int main() {
  Game new_game;
  new_game.tries_remaining = num_tries;
  new_game.set_word();
  new_game.set_progress();
  new_game.play_intro();
  while (!new_game.is_won && !new_game.is_lost) {
    new_game.play_game();
    new_game.check_win();
    new_game.check_loss();
  }
  return 0;
};