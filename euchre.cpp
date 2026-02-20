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
    void deletePlayers();

  private:
    vector<Player *> players;
    Pack pack;
    Suit trump;

    bool shuffle_on;
    int points_to_win;

    int dealer = 0;
    int team_1_score = 0;
    int team_2_score = 0;

    void shuffle();
    void deal();
    void deal(Player *);
    void make_trump(Suit &order_up_suit, Card &upcard);
    void play_hand();
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
  pack.shuffle();
}

void Game::deal(/*player, */)
{
  //deal 3-2-3-2 cards then 2-3-2-3 cards, for a total of 5 cards
  
  //frst pattern: deal 3-2-3-2 cards
  for (int i = 0; i < 4; i++)
  {
    //even turn deals 3
    if (i % 2 == 0)
    {
      players[i]->add_card(pack.deal_one());
      players[i]->add_card(pack.deal_one());
      players[i]->add_card(pack.deal_one());
    }

    //odd turn deals 2
    else
    {
      players[i]->add_card(pack.deal_one());
      players[i]->add_card(pack.deal_one());
    }
  }

  //second pattern: deals 2-3-2-3 cards
  for (int i = 0; i < 4; i++)
  {
    //even turn deals 2
    if (i % 2 == 0)
    {
      players[i]->add_card(pack.deal_one());
      players[i]->add_card(pack.deal_one());
    }

    //odd turn deals 3
    else
    {
      players[i]->add_card(pack.deal_one());
      players[i]->add_card(pack.deal_one());
      players[i]->add_card(pack.deal_one());
    }
  }
}

void Game::deal(Player * player)
{
  player->add_card(pack.deal_one());
}

void Game::make_trump(Suit &order_up_suit, Card &upcard)
{ 
 //round 1 
  int dealer_number = 0;
  int round_number = 0;
  
  Card upcard = pack.deal_one();

  // Player * eldest_hand = players[dealer_number - 1];
  // Player * dealer = players[dealer_number]; 
  bool is_dealer = true;
  
  for(int i = players.size() - 1; i >= 0; i--)
  {
    if (dealer_number == i)
    {
      is_dealer = true;
    }
    if(players[i]->make_trump(upcard, is_dealer, round_number, order_up_suit)) return;

    is_dealer = false;
  }
  is_dealer = false;

  //round 2
  //int eldest_hand_num = players.size() - 1; //eldest hand
  round_number = 2;
  if (round_number == 2)
  {
    for(int i = players.size(); i >= 0; i--)
    {
      if (dealer_number == i)
      {
        is_dealer = true;
        players[dealer_number]->make_trump(upcard, is_dealer, round_number, order_up_suit);
        return;
      }

      if(players[i]->make_trump(upcard, is_dealer, round_number, order_up_suit)) return;

      is_dealer = false;
    }
    
    is_dealer = false;  
  }
}

void Game::play_hand()
{
  Card led_card = players[dealer]->lead_card(trump);

  for (int i = 0; i < players.size(); i++)
  {
    if (i == dealer) continue;
    players[i]->play_card(led_card, trump);
  }
}

void Game::play()
{
  while (team_1_score < points_to_win &&
         team_2_score < points_to_win)
  {
    deal();
    Card upcard = pack.deal_one();
    Suit suit_order_up;
    make_trump(suit_order_up, upcard);
    play_hand();
    dealer++;
  }
}

void Game::deletePlayers()
{
  for (int i = 0; i < players.size(); i++)
  {
    delete players[i];
  }
}


//-------------------------------------------

//      READS THE ARGUEMENT AND FILE

//-------------------------------------------



int main(int argc, char* argv[])
{
  cout << "Hello World" << endl;
  //checks that it has the 12 arguements for sample 4 players
  // if (argc != 12)
  // {
  //   cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
  //   << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
  //   << "NAME4 TYPE4" << endl;
    
  //   return 1;
  // }

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
  game.deletePlayers();
}
