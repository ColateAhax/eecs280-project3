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
    int made_trump = 0; //either team 1 or 2

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
      if (curr % 2 == 0) made_trump = 1;
      else made_trump = 2;
      trump = order_up_suit;
      players[dealer]->add_and_discard(upcard);
      cout << players[curr]->get_name() << " orders up " << trump << "\n" << endl;
      return;
    }
    cout << players[curr]->get_name() << " passes" << endl;
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
      if (curr % 2 == 0) made_trump = 1;
      else made_trump = 2;
      trump = order_up_suit;
      cout << players[curr]->get_name() << " orders up " << trump << "\n" << endl;
      return;
    }
    //cout << players[curr]->get_name() << " passes" << endl;
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
    cout << led_card << " led by " << players[leader]->get_name() << endl;

    //assumes the leader has the winning card and thus is the winner
    int winner = leader;
    Card win_card = led_card;

    //the rest play the cards
    for (int j = 1; j < 4; j++)
    {
      int curr = (leader + j) % 4;
      Card played = players[curr]->play_card(led_card, trump);

      cout << played << " played by " << players[curr]->get_name() << endl;
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
    cout << players[winner]->get_name() << " takes the trick\n" << endl;
    //if the index of winner is even its team 1
    if (winner % 2 == 0) team_1_tricks++;
    //if the index of winner is odd its team 2
    else team_2_tricks++;    
  }

  //checks who got the most tricks thus getting a point
  int finalWinner = 0;
  int WinnerTricksAmt = 0;
  int points = 0;
  bool march = false;
  bool euchered = false; //may change later cause idk wehre to output if thy ot a march oor not
  //bool ordered_up;
  
  if (team_1_tricks > team_2_tricks)
  {
    cout << players[0]->get_name() << " and " << players[2]->get_name() << " win the hand" << endl;
    finalWinner = 1;
    WinnerTricksAmt = team_1_tricks;
    //ordered_up = made_trump == 1;
  }
  else 
  {
    finalWinner = 2;
    WinnerTricksAmt = team_2_tricks;
    cout << players[1]->get_name() << " and " << players[3]->get_name() << " win the hand" << endl;
    //ordered_up = made_trump == 2;
  }

  //ordered_up = finalWinner == made_trump;
  //cout << ordered_up << endl;
  if (finalWinner == made_trump){
    if(WinnerTricksAmt > 4)
    {
      points = 2;
      march = true;
    }
    else if (WinnerTricksAmt > 2)
    {
      points = 1;
    
    }
  }else
  {
    //cout << "in else";
    euchered = true;
    points = 2;
  }
  
  if (finalWinner == 1)
  { 
    // cout << "rhea";
    // cout << team_1_score;
    // cout << points;
    team_1_score += points;
  }
  else 
  {
    team_2_score += points;
  }
  
  if (euchered) cout << "euchred!" << endl;
  else if (march) cout << "march!" << endl;
  //announces scores
  cout << players[0]->get_name() << " and " << players[2]->get_name() << " have " << team_1_score << " points" << endl;
  cout << players[1]->get_name() << " and " << players[3]->get_name() << " have " << team_2_score << " points\n" << endl;
}

void Game::play()
{
  int hand_num = 0;
  while (team_1_score < points_to_win &&
         team_2_score < points_to_win)
  {
    if (shuffle_on) pack.shuffle();
    cout << "Hand " << hand_num << endl;
    cout << players[dealer]->get_name() << " deals" << endl;
    deal();
    Card upcard = pack.deal_one();
    cout << upcard << " turned up" << endl;
    Suit suit_order_up;
    make_trump(suit_order_up, upcard);
    play_hand();
    //usually it would be dealer++
    //but it needs to wrap around the array
    dealer = (dealer + 1) % 4;
    hand_num++;
  }

  //announces winnners
  if (team_1_score > team_2_score)
  {
    cout << players[0]->get_name() << " and " << players[2]->get_name() << " win!" << endl;
  }
  else cout << players[1]->get_name() << " and " << players[3]->get_name() << " win!" << endl;
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
  //cout << "Hello World" << endl;
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
  game.play();
  game.deletePlayers();
}
