#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
//EFFECTS returns the Rank corresponding to str, for example "Two" -> TWO
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
//EFFECTS returns the Suit corresponding to str, for example "Clubs" -> CLUBS
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}


/////////////// Write your implementation for Card below ///////////////

Card::Card()
  : rank(TWO), suit (SPADES)
{}

Card::Card(Rank rank_in, Suit suit_in)
  : rank(rank_in), suit(suit_in)
{}

Rank Card::get_rank() const   {return rank;}

Suit Card::get_suit() const   {return suit;}

Suit Card::get_suit(Suit trump) const
{
  if (is_left_bower(trump)) return trump;
  
  return suit;
}

bool Card::is_trump(Suit trump) const
{
  if(suit == trump || is_left_bower(trump)) return true;
  return false;
}

bool Card::is_face_or_ace() const   {return (rank >= 9 && rank <= 12);}

bool Card::is_right_bower(Suit trump) const{ return (suit == trump && rank == JACK);}


bool Card::is_left_bower(Suit trump) const///
{
  if (rank == JACK)
  {
    if (suit == Suit_next(trump)){
      return true;
    }
}
return false;
}

//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.

bool Card_less(const Card &a, const Card &b, Suit trump) 
//Finished this check if its right when ur free @nick
{
  if(a.is_trump(trump) && !b.is_trump(trump))
  {
    return false;
  } 
  else if (b.is_trump(trump) && !a.is_trump(trump))
  {
    return true;
  } 
  else 
  { //if both trump or both not

    //most valuable bower
    if(a.is_right_bower(trump))   return false;
    else if (b.is_right_bower(trump))   return true;

    //second most valuable bower
    else if (a.is_left_bower(trump))   return false;
    else if (b.is_left_bower(trump))   return true;

    //ranks are the same --> tiebreaking with suit
    if (a.get_rank() == b.get_rank())
    {
      return (a.get_suit() < b.get_suit());
    }
    //checking rank
    return (a.get_rank() < b.get_rank());

  } 
}

//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump)
{
  //checks with the led card
  Suit led = led_card.get_suit();

  //checks that a is in accordandce to the led or trump
  if (a.get_suit() == led || a.is_trump(trump))
  {
    if (b.get_suit() == led || b.is_trump(trump))
    //then both a and b are accordance to led and trump then its normal
    {
      return Card_less(a, b, trump);
    }

    //then b is not the led or trump card but a is in accordance
    //so a should win it leading to a false
    else return false;
  }

  else //a is not in accordance
  {
    //then b is in accordance to led and trump but a is not
    //so automatically a is less
    if (b.get_suit() == led || b.is_trump(trump)) return true;
    
    //neither a or b are in accordance to led or trump
    //so its a normal Card_less
    else return Card_less(a, b, trump);
  }
}

Suit Suit_next(Suit suit)
{
  Suit result;

  if (suit == SPADES) result = CLUBS;
  else if (suit == CLUBS) result = SPADES;
  else if (suit == HEARTS) result = DIAMONDS;
  else result = HEARTS;

  return result;
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=


//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator == (const Card &card_left, const Card &card_right)
{
  // //checks if both are trump or both are not
  // if (card_left.is_trump(card_left.get_suit()) != 
  //     card_right.is_trump(card_right.get_suit())) return false;

  // //checks if its the same num
  // if (card_left.get_rank() != card_right.get_rank()) return false;

  // return true;

  bool rank = card_left.get_rank() == card_right.get_rank();
  bool suit = card_left.get_suit() == card_right.get_suit();

  if (rank && suit) return true;
  else return false;
}

bool operator != (const Card &card_left, const Card &card_right)
{
  return !(card_left == card_right);
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator > (const Card &card_left, const Card &card_right)
{
  // //makes sure they not equal to each other
  // if (card_left == card_right) return false;

  // //checks if one of them is the right bower
  // if (card_left.is_right_bower(card_left.get_suit())) return true;
  // if (card_right.is_right_bower(card_right.get_suit())) return false;

  // //checks if one of them is left boew
  // if (card_left.is_left_bower(card_left.get_suit())) return true;
  // if (card_right.is_left_bower(card_right.get_suit())) return false;

  // //checks if left card if trump and right isnt
  // if (card_left.is_trump(card_left.get_suit()) && 
  //     !card_right.is_trump(card_right.get_suit())) return true;
      
  // //checks if right card if trump and left isnt
  // if (card_left.is_trump(card_left.get_suit()) && 
  //     !card_right.is_trump(card_right.get_suit())) return false;

  // return (card_left.get_rank() > card_right.get_rank());

  if (card_left.get_rank() > card_right.get_rank()) return true;
  else return false;
}

bool operator < (const Card &card_left, const Card &card_right)
{//GENUIUS
  // return !(card_left > card_right) && card_left != card_right;
  if (card_left.get_rank() < card_right.get_rank()) return true;
  else return false;
}

bool operator <= (const Card &card_left, const Card &card_right)
{//so stylish
  return card_left < card_right || card_left.get_rank() == card_right.get_rank();
}

bool operator >= (const Card &card_left, const Card &card_right)
{
  return (card_left > card_right || card_left.get_rank() == card_right.get_rank());
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card)
{
  os << card.get_rank() << " of " << card.get_suit();
  return os;
}

//EFFECTS Reads a Card from a stream in the format "Two of Spades"
//NOTE The Card class declares this operator>> "friend" function,
//     which means it is allowed to access card.rank and card.suit.
std::istream & operator>>(std::istream &is, Card &card)
{
  std::string str;
  is >> card.rank >> str >> card.suit;
  return is;
}