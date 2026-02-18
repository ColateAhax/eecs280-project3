#include "Player.hpp"
#include <cassert>
#include <iostream>
#include <array>
using namespace std;

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each * after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) 
{
  //
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player&p) 
{
  //
}

class SimplePlayer : public Player 
{
  public:
    SimplePlayer(const std::string name);

    const std::string & get_name() const override;

    void add_card(const Card &c) override{hand.push_back(c);}

    bool make_trump(const Card &upcard, bool is_dealer,
                              int round, Suit &order_up_suit)const override;

    void add_and_discard(const Card &upcard) override;

    Card lead_card(Suit trump) override;

    Card play_card(const Card &led_card, Suit trump) override;
  private:
    std::string name;
    vector<Card> hand;
};

//for simple player
SimplePlayer::SimplePlayer(const std::string name)
:name(name){};

const std::string & SimplePlayer::get_name() const
{
  return name;
}

//REQUIRES player has less than MAX_HAND_SIZE cards
///EFFECTS  adds Card c to 's hand
void SimplePlayer::add_card(const Card &c)
{
  hand.push_back(c);
}

//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If  wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If  wishes to pass, then do
//  not modify order_up_suit and return false.
bool SimplePlayer::make_trump(const Card &upcard, bool is_dealer,
                        int round, Suit &order_up_suit) const
{
  //
}

//REQUIRES  has at least one card
//EFFECTS   adds one card to hand and removes one card from hand.
void SimplePlayer::add_and_discard(const Card &upcard)
{
  //
}

//REQUIRES  has at least one card
//EFFECTS  Leads one Card from 's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
Card SimplePlayer::lead_card(Suit trump)
{
  //
}

//REQUIRES  has at least one card
//EFFECTS  Plays one Card from 's hand according to their strategy.
//  The card is removed from the player's hand.
Card SimplePlayer::play_card(const Card &led_card, Suit trump)
{
  //
}











//for human player
class HumanPlayer : public Player 
{
  public:
    HumanPlayer(const std::string name) :name(name){};

    const std::string & get_name() const override;

    void add_card(const Card &c) override;
    bool make_trump(const Card &upcard, bool is_dealer,
                              int round, Suit &order_up_suit) const override;
    void add_and_discard(const Card &upcard) override;
    Card lead_card(Suit trump) override;
    Card play_card(const Card &led_card, Suit trump) override;
  private:
    std::string name;
};

HumanPlayer::HumanPlayer(const std::string name)
:name(name){};

const std::string & HumanPlayer::get_name() const
{
  return name;
}

//REQUIRES player has less than MAX_HAND_SIZE cards
///EFFECTS  adds Card c to 's hand
void HumanPlayer::add_card(const Card &c)
{
  //
}

//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If  wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If  wishes to pass, then do
//  not modify order_up_suit and return false.
bool HumanPlayer::make_trump(const Card &upcard, bool is_dealer,
                        int round, Suit &order_up_suit) const
{
  //
}

//REQUIRES  has at least one card
//EFFECTS   adds one card to hand and removes one card from hand.
void HumanPlayer::add_and_discard(const Card &upcard)
{
  //
}

//REQUIRES  has at least one card
//EFFECTS  Leads one Card from 's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
Card HumanPlayer::lead_card(Suit trump)
{
  //
}

//REQUIRES  has at least one card
//EFFECTS  Plays one Card from 's hand according to their strategy.
//  The card is removed from the player's hand.
Card HumanPlayer::play_card(const Card &led_card, Suit trump)
{
  //
}








Player * Player_factory(const std::string &name, 
                        const std::string &strategy) 
{
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") 
  {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  // Repeat for each other type of 
  if (strategy == "Human") 
  {
    // The "new" keyword dynamically allocates an object.
    return new HumanPlayer(name);
  }
  // Invalid strategy if we get here
  return nullptr;
}
