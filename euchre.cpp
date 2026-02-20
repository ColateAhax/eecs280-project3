#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <array>
#include "Player.hpp"
#include "Pack.hpp"
using namespace std;

class Game
{
  public:
    Game(bool shuffle_on, int points_to_win, std::istream& pack_input,
    vector<std::string> names_Players, vector<std::string> types_of_Players);
    
    void play();

  private:
    vector<Player *> players;
    Pack pack;

    bool shuffle_on;
    int points_to_win;

    void shuffle();
    void deal(/* ... */);
    void make_trump(/* ... */);
    void play_hand(/* ... */);
};

Game::Game(bool shuffle_on, int points_to_win, std::istream& pack_input,
vector<std::string> names_Players, vector<std::string> types_of_Players)

:pack(pack_input), shuffle_on(shuffle_on), points_to_win(points_to_win)

{
  if (names_Players.size() != types_of_Players.size())
  {
    cout << "Different Numbers of Players and Types" << endl;
    assert(false);
  }

  for (int i = 0; i < names_Players.size(); i++)
  {
    players.push_back(Player_factory(names_Players[i], types_of_Players[i]));
  }
}

void Game::shuffle()
{
  //
}

void Game::deal(/* ... */)
{
  //
}

void Game::make_trump(/* ... */)
{
  //
}

void Game::play_hand(/* ... */)
{
  //
}

void Game::play()
{
  //
}




//-------------------------------------------

//      READS THE ARGUEMENT AND FILE

//-------------------------------------------



int main(int argc, char* argv[])
{
  cout << "Hello World" << endl;
  //checks that it has the 12 arguements for sample 4 players
  if (argc != 12)
  {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
    << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
    << "NAME4 TYPE4" << endl;
    
    return 1;
  }

  //sets the fileIn name and attempts to open it
  std::string fileIn = argv[1];
  std::ifstream is(fileIn);
  if (!is.is_open()) 
  {
    // Assume pack_filename is a variable containing
    // the specified pack filename from argv
    cout << "Error opening " << fileIn << endl;
    return 1;
  }

  //determines if we are shuffling
  bool shuffle_on = true;
  std::string shuff = std::string(argv[2]);
  if ( shuff == "noshuffle") shuffle_on = false;
  else if (shuff != "shuffle")
  {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
    << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
    << "NAME4 TYPE4" << endl;

    return 1;
  }

  //sets the points to win the name
  int points_to_win_game = stoi(argv[3]);
  if(points_to_win_game <= 1 && points_to_win_game >= 100)
  {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
    << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
    << "NAME4 TYPE4" << endl;

    return 1;
  }

  //gets the names and types of players
  vector<std::string> names_Players;
  vector<std::string> types_of_Players;

  for(int i = 4; i < 12; i++)
  {
    std::string str = std::string(argv[i]);

    //if its even its a name
    if(i % 2 == 0) names_Players.push_back(str);

    //if its odd its a type
    else
    {
      if(str != "Human" && str != "Simple")
      {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;

        return 1;
      }
      types_of_Players.push_back(str);
    }
  }

  Game game(shuffle_on, points_to_win_game, is, names_Players, types_of_Players);
}
