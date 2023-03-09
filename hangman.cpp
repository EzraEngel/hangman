#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "word_list.cpp"

using namespace std;

int num_tries = 12;

int play_intro(int num_tries, string winning_word);
string set_progress(string winning_word);
int play_game(string winning_word, string& word_progress, int& tries_remaining, string& guess_list);
int check_win(string word_progress, bool& game_is_won);
int check_loss(int tries_remaining, bool& game_is_lost);
bool repeat_guess(string player_guess, string guess_list);
string set_word();
bool guess_allowed(string player_guess);
int add_to_guess_list(string player_guess, string& guess_list);
int print_guess_list(string guess_list);

int main() {
  string guess_list = "                          ";
  string winning_word = set_word();
  bool game_is_won = false;
  bool game_is_lost = false;
  int tries_remaining = num_tries;
  play_intro(num_tries, winning_word);
  string word_progress = set_progress(winning_word);
  while (!game_is_won && !game_is_lost) {
    play_game(winning_word, word_progress, tries_remaining, guess_list);
    check_win(word_progress, game_is_won);
    check_loss(tries_remaining, game_is_lost);
  }
  return 0;
};

int play_intro(int num_tries, string winning_word) {
  cout << endl << "#############################################\n";
  cout << "           Welcome to HANGMAN!\n";
  cout << "#############################################\n";
  cout << "You have " << num_tries << " strikes remaining.\n";
  cout << "The word has " << winning_word.length() << " letters.\n";
  return 0;
};

string set_progress(string winning_word) {
  string word_progress = "";
  for (int i=0; i<winning_word.length(); i++) {
  	word_progress.append("_ ");
  }
  cout << word_progress << endl;
  return word_progress;
}

int play_game(string winning_word, string& word_progress, int& tries_remaining, string& guess_list) {
  string player_guess = "";
  cout << endl;
  cout << "=========================================" << endl;
  cout << "           GUESS A LETTER!\n";
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
  else if (repeat_guess(player_guess, guess_list)) {
    cout << "You've already guessed that!" << endl;
    return 0;
  }
  else {
  	bool good_guess = false;
  	add_to_guess_list(player_guess, guess_list);
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
  	  print_guess_list(guess_list);
  	}
  	else {
  	  tries_remaining--;
  	  cout << word_progress << endl;
	  cout << "Bad guess! You have " << tries_remaining << " strikes remaining." << endl;
	  cout << "Your guesses: ";
  	  print_guess_list(guess_list);
  	}
  }
  return 0;
};

int check_win(string word_progress, bool& game_is_won) {
  string underscore = "_";
  bool blank_exists = false;
  for (int i=0; i<word_progress.length(); i++) {
    if (word_progress[i] == underscore[0]) {
      blank_exists = true;
    }
  }
  if (!blank_exists) {
  	game_is_won = true;
  	cout << endl;
  	cout << "=======================================" << endl;
  	cout << "               YOU WIN!                " << endl;
    cout << "=======================================" << endl;
  }
  return 0;
}

int check_loss(int tries_remaining, bool& game_is_lost) {
  if (tries_remaining == 0) {
  	game_is_lost = true;
  	cout << endl;
  	cout << "=======================================" << endl;
  	cout << "              YOU LOSE!                " << endl;
    cout << "=======================================" << endl;
  }
  return 0;
}

bool repeat_guess(string player_guess, string guess_list) {
  bool repeat = false;
  for (int i=0; i<guess_list.length(); i++) {
    if (player_guess[0] == guess_list[i]) {
  	  repeat = true;
  	  break;
  	}
  }
  return repeat;
}

string set_word() {
  default_random_engine generator(time(nullptr));
  uniform_int_distribution<int> distribution(0, 1000);
  int random_index = distribution(generator);
  return word_list[random_index];
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

int add_to_guess_list(string player_guess, string& guess_list) {
  string alphabet = "abcdefghijklmnopqrstuvwxyz";
  for (int i=0; i<alphabet.length(); i++) {
  	if (player_guess[0] == alphabet[i]) {
  	  guess_list[i] = player_guess[0];
  	  return 0;
  	}
  }
  return 0;
}

int print_guess_list(string guess_list) {
  for (char c : guess_list) {
  	if (c!=' ') {
  	cout << c;
    }
  }
  cout << endl;
  return 0;
}

