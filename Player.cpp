#include "Player.hpp"
#include <cassert>
#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

class SimplePlayer : public Player 
{
  public:
    SimplePlayer(const std::string name);

    const std::string & get_name() const override;

    void add_card(const Card &c) override;

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
  if (round == 1)
  {
    //seeing if hand has upcard
    int count = 0;
    Suit trump = upcard.get_suit();
    for (int i = 0; i < hand.size(); i++) 
    {
      if((hand[i].is_trump(trump)) && (hand[i].is_face_or_ace()
          || hand[i].is_left_bower(trump)
          || hand[i].is_right_bower(trump)))
      {
        count++;
      }
    }
    if (count >= 2)
    {
      order_up_suit = upcard.get_suit();
      return true;
    }
  }
  else
  {
    if(is_dealer)
    {
      order_up_suit = Suit_next(upcard.get_suit());
      return true;
    }
    //sneaky little change used to be 1
    //for (int i = 1; i < hand.size(); i++) 
    for (int i = 0; i < hand.size(); i++) 
    {
      if((hand[i].get_suit() == Suit_next(upcard.get_suit())) && (hand[i].is_face_or_ace()
          || hand[i].is_left_bower(upcard.get_suit())
          || hand[i].is_right_bower(upcard.get_suit())))
      {
        order_up_suit = Suit_next(upcard.get_suit());
        return true;
      }
    }
  }
  return false;
}


//REQUIRES  has at least one card
//EFFECTS   adds one card to hand and removes one card from hand.
void SimplePlayer::add_and_discard(const Card &upcard)
{
  hand.push_back(upcard);

  int comparing = 0;
  for(int i = 1; i < hand.size(); i++)
  {
    if(Card_less(hand[i], hand[comparing], upcard.get_suit()))
    {
      comparing = i;
    }
  }
  hand.erase(hand.begin() + comparing);
}

//REQUIRES  has at least one card
//EFFECTS  Leads one Card from 's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
Card SimplePlayer::lead_card(Suit trump)
{
  bool has_all_trumps = true;
  vector<int> index_non_trump;
  Card c;

  //checking if all of them are trump cards
  for(int i = 0; i < hand.size(); i++)
  {
    if(!(hand[i].is_trump(trump)))
    {
      has_all_trumps = false;
      index_non_trump.push_back(i);
    }
  }

  if (has_all_trumps)
  {
    c = hand[0];
    int indexBest = 0;
    //cycles through the deck
    for (int i = 1; i < hand.size(); i++)
    {
      Card current_card = hand[i];

      //checks if the best card is less in value than the current
      if (Card_less(c, current_card, trump))
      {
        c = current_card;
        indexBest = i;
      }
    }

    //deletes the best card from hand then returns it
    hand.erase(hand.begin() + indexBest);
  }

  else
  {
    c = hand[index_non_trump[0]];
    int indexBest = index_non_trump[0];
    //cycles through the deck
    for (int i = 1; i < hand.size(); i++)
    {
      //checks that current index is a non trump
      if (hand[i].is_trump(trump)) continue;

      Card current_card = hand[i];

      //checks if the best card is less in value than the current
      if (Card_less(c, current_card, trump))
      {
        c = current_card;
        indexBest = i;
      }
    }

    //deletes the best card from hand then returns it
    hand.erase(hand.begin() + indexBest);
  }
  return c;
}


//REQUIRES  has at least one card
//EFFECTS  Plays one Card from 's hand according to their strategy.
//  The card is removed from the player's hand.
Card SimplePlayer::play_card(const Card &led_card, Suit trump)
{
  //checks if it can follow suit
  bool follow_suit = false;
  Suit suit_led_card = led_card.get_suit(trump);
  for (int i = 0; i < hand.size(); i++)
  {
    //automatically breaks it because you can follow suit
    if(hand[i].get_suit(trump) == suit_led_card)
    {
      follow_suit = true;
      break;
    }
  }

  //if it can follow suit goes for best card
  if (follow_suit)
  {
    int indexBest = 0;

    //finds the first card that follows suit
    for (int i = 0; i < hand.size(); i++)
    {
      if (hand[i].get_suit(trump) == suit_led_card)
      {
        indexBest = i;
        break;
      }
    }
    Card best_Card = hand[indexBest];

    //cycles through the deck
    //sneaky little one before
    for (int i = 1; i < hand.size(); i++)
    //for (int i = 0; i < hand.size(); i++)
    {
      Card current_card = hand[i];

      //makes sure its in the suit of the led card
      if (hand[i].get_suit(trump) != suit_led_card) continue;
      //checks if the best card is less in value than the current
      if (Card_less(best_Card, current_card, led_card, trump))
      {
        best_Card = current_card;
        indexBest = i;
      }
    }

    //deletes the best card from hand then returns it
    hand.erase(hand.begin() + indexBest);
    return best_Card;
  }

  //it cannot follow suit
  else
  {
    Card worst_Card = hand[0];
    int indexWorst = 0;

    //cycles through the deck
    for (int i = 1; i < hand.size(); i++)
    {
      Card current_card = hand[i];

      //checks if the current card is less in value than worst
      if (Card_less(current_card, worst_Card, led_card, trump))
      {
        worst_Card = current_card;
        indexWorst = i;
      }
    }

    //deletes the best card from hand then returns it
    hand.erase(hand.begin() + indexWorst);
    return worst_Card;
  }
}





//-----------------------------------------------------

//Human Player Class

//-----------------------------------------------------



//for human player
class HumanPlayer : public Player 
{
  public:
    HumanPlayer(const std::string name);

    const std::string & get_name() const override;

    void add_card(const Card &c) override;
    bool make_trump(const Card &upcard, bool is_dealer,
                              int round, Suit &order_up_suit) const override;
    void add_and_discard(const Card &upcard) override;
    Card lead_card(Suit trump) override;
    Card play_card(const Card &led_card, Suit trump) override;
    string decision() const;
  private:
    void print_hand() const;
    std::string name;
    vector<Card> hand;
};

HumanPlayer::HumanPlayer(const std::string name)
:name(name){};

void HumanPlayer::print_hand() const 
{
  for (size_t i=0; i < hand.size(); ++i)
    cout << "Human player " << name << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
}


string HumanPlayer::decision() const
{
  string str;
  cin >> str;
  return str;
}

const std::string & HumanPlayer::get_name() const
{
  return name;
}

//REQUIRES player has less than MAX_HAND_SIZE cards
///EFFECTS  adds Card c to 's hand
void HumanPlayer::add_card(const Card &c)
{
  hand.push_back(c);
}

//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If  wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If  wishes to pass, then do
//  not modify order_up_suit and return false.
bool HumanPlayer::make_trump(const Card &upcard, bool is_dealer,
                        int round, Suit &order_up_suit) const
{
  print_hand();
  cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
  string input = decision();
  if (input == "pass") return false;
  order_up_suit = string_to_suit(input);
  return true;
}

//REQUIRES  has at least one card
//EFFECTS   adds one card to hand and removes one card from hand.
void HumanPlayer::add_and_discard(const Card &upcard)
{
  cout << "Upcard: " << upcard << endl;
  std::sort(hand.begin(), hand.end());
  print_hand();
  cout << "Discard upcard: [-1]\n";
  int input = stoi(decision());
  if (input == -1) return;
  cout << "Human player " << name << ", please select a card to discard:\n";
  hand.erase(hand.begin() + input);
  hand.push_back(upcard);
}

//REQUIRES  has at least one card
//EFFECTS  Leads one Card from 's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
Card HumanPlayer::lead_card(Suit trump)
{
  std::sort(hand.begin(), hand.end());
  print_hand();
  cout << "Human player " << name << ", please select a card:\n";
  int input = stoi(decision());
  Card selected = hand[input];
  hand.erase(hand.begin() + input);
  return selected;
}

//REQUIRES  has at least one card
//EFFECTS  Plays one Card from 's hand according to their strategy.
//  The card is removed from the player's hand.
Card HumanPlayer::play_card(const Card &led_card, Suit trump)
{
  std::sort(hand.begin(), hand.end());
  print_hand();
  cout << "Human player " << name << ", please select a card:\n";
  int input = stoi(decision());
  Card selected = hand[input];
  hand.erase(hand.begin() + input);
  return selected;
}


//-----------------------------------------------------

//Vanilla Functions

//-----------------------------------------------------



//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each * after the game is over
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
  // Repeat for each other type of Player 
  if (strategy == "Human") 
  {
    // The "new" keyword dynamically allocates an object.
    return new HumanPlayer(name);
  }
  //Invalid strategy if we get here
  assert(false);
  return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player&p) 
{
  os << p.get_name();
  return os;
}
