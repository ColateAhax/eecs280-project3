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
    int curr = (dealer + 1 + i) % 4;

    //even turn deals 3
    if (i % 2 == 0)
    {
      players[curr]->add_card(pack.deal_one());
      players[curr]->add_card(pack.deal_one());
      players[curr]->add_card(pack.deal_one());
    }

    //odd turn deals 2
    else
    {
      players[curr]->add_card(pack.deal_one());
      players[curr]->add_card(pack.deal_one());
    }
  }

  //second pattern: deals 2-3-2-3 cards
  for (int i = 0; i < 4; i++)
  {
    int curr = (dealer + 1 + i) % 4;
    //even turn deals 2
    if (i % 2 == 0)
    {
      players[curr]->add_card(pack.deal_one());
      players[curr]->add_card(pack.deal_one());
    }

    //odd turn deals 3
    else
    {
      players[curr]->add_card(pack.deal_one());
      players[curr]->add_card(pack.deal_one());
      players[curr]->add_card(pack.deal_one());
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
  int round_number = 1;
  
  for(int i = 0; i < 4; i++)
  {
    int curr = (dealer + 1 + i) % 4;

    if(players[curr]->make_trump(upcard, dealer == curr,
       round_number, order_up_suit))
    {
      trump = order_up_suit;
      players[dealer]->add_and_discard(upcard);
      return;
    }

  }

  //round 2
  //int eldest_hand_num = players.size() - 1; //eldest hand
  round_number = 2;
  for(int i = 0; i < 4; i++)
  {
    int curr = (dealer + 1 + i) % 4;

    if(players[curr]->make_trump(upcard, dealer == curr,
       round_number, order_up_suit))
    {
      trump = order_up_suit;
      return;
    }
  }
}

void Game::play_hand()
{
  int leader = (dealer + 1) % 4;
  int team_1_tricks = 0;
  int team_2_tricks = 0;

  //there is 5 tricks
  for (int i = 0; i < 5; i++)
  {
    //determines lead card
    Card led_card = players[leader]->lead_card(trump);

    //assumes the leader has the winning card and thus is the winner
    int winner = leader;
    Card win_card = led_card;

    //the rest play the cards
    for (int j = 1; j < 5; j++)
    {
      int curr = (leader + i) % 4;
      Card played = players[curr]->play_card(led_card, trump);

      //checks and stores who is winning
      //if true it updates the variables
      if(Card_less(win_card, played, led_card, trump))
      {
        win_card = played;
        winner = curr;
      }
    }

    //the winner is gonna become leader next
    leader = winner;
    //if the index of winner is even its team 1
    if (winner % 2 == 0) team_1_tricks++;
    //if the index of winner is odd its team 2
    else team_2_tricks++;
  }

  //checks who got the most tricks thus getting a point
  if (team_1_tricks > team_2_tricks) team_1_score++;
  else team_2_score++;
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
    //usually it would be dealer++
    //but it needs to wrap around the array
    dealer = (dealer + 1) % 4;
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
