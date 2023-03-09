#include <iostream>
#include <string>
#include <random>
#include <ctime>

class Game {
private:
  bool is_won = false;
  bool is_lost = false;
  int strikes_remaining;
  string word_progress;
  string guess_list = "                          ";
  string winning_word;

public:
  int play_game() {
    string player_guess = "";
    cout << endl;
    cout << "=========================================" << endl;
    cout << "           GUESS A LETTER!               " << endl;
    cout << "=========================================" << endl;
    cin >> player_guess;
    player_guess[0] = tolower(player_guess[0]);
    if (player_guess.length() != 1) {
      cout << "Guess is the wrong length.\n";
      return 0;
    }
    else if (!guess_allowed(player_guess)) {
      cout << "Guess not allowed!" << endl;
      return 0;
    }
    else if (repeat_guess(player_guess)) {
      cout << "You've already guessed that!" << endl;
      return 0;
    }
    else {
      bool good_guess = false;
      add_to_guess_list(player_guess);
      for (int i=0; i<winning_word.length(); i++) {
        if (player_guess[0] == winning_word[i]) {
          word_progress[i*2] = player_guess[0];
          good_guess = true;
        }
      }
      if (good_guess) {
        cout << word_progress << endl;
        cout << "Great guess!" << endl;
        cout << "Your guesses: ";
        print_guess_list();
      }
      else {
        strikes_remaining--;
        cout << word_progress << endl;
        cout << "Bad guess! You have " << strikes_remaining << " strikes remaining." << endl;
        cout << "Your guesses: ";
        print_guess_list();
      }
    }
    return 0;
  }

  void check_win() {
    string underscore = "_";
    bool blank_exists = false;
    for (int i=0; i<word_progress.length(); i++) {
      if (word_progress[i] == underscore[0]) {
        blank_exists = true;
      }
    }
    if (!blank_exists) {
      is_won = true;
      cout << endl;
      cout << "=======================================" << endl;
      cout << "               YOU WIN!                " << endl;
      cout << "=======================================" << endl;
    }
  }

  void check_loss() {
    if (strikes_remaining == 0) {
      is_lost = true;
      cout << endl;
      cout << "=======================================" << endl;
      cout << "              YOU LOSE!                " << endl;
      cout << "=======================================" << endl;
    }
  }

  void set_progress() {
    for (int i=0; i<winning_word.length(); i++) {
      word_progress.append("_ ");
    }
    cout << word_progress << endl;
  }

  bool guess_allowed(string player_guess) {
    bool guess_allowed = false;
    string allowed_chars = "abcdefghijklmnopqrstuvwxyz";
    for (int i=0; i<allowed_chars.length(); i++) {
      if (player_guess[0] == allowed_chars[i]) {
        guess_allowed = true;
        return guess_allowed;
      }
    }
    return guess_allowed;
  }

  bool repeat_guess(string player_guess) {
    bool repeat = false;
    for (int i=0; i<guess_list.length(); i++) {
      if (player_guess[0] == guess_list[i]) {
        repeat = true;
        break;
      }
    }
    return repeat;
  }

  int add_to_guess_list(string player_guess) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (int i=0; i<alphabet.length(); i++) {
      if (player_guess[0] == alphabet[i]) {
        guess_list[i] = player_guess[0];
        return 0;
      }
    }
    return 0;
  }

  void print_guess_list() {
    for (char c : guess_list) {
      if (c!=' ') {
      cout << c;
      }
    }
    cout << endl;
  }

  void set_word() {
    default_random_engine generator(time(nullptr));
    uniform_int_distribution<int> distribution(0, 1000);
    int random_index = distribution(generator);
    winning_word = word_list[random_index];
  }

  void play_intro() {
    cout << endl << "#############################################\n";
    cout << "           Welcome to HANGMAN!\n";
    cout << "#############################################\n";
    cout << "You have " << strikes_remaining << " strikes remaining.\n";
    cout << "The word has " << winning_word.length() << " letters.\n";
  }

  void set_strikes(int num_strikes) {
    strikes_remaining = num_strikes;
  }

  bool is_over() {
    return (is_won || is_lost);
  }
};