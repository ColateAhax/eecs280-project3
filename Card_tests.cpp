#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here

//EFFECTS Initializes Card to the Two of Spades//rhea
//Card();
TEST(test_default_initializing)
{
    //
}

//EFFECTS Initializes Card to specified rank and suit
// Card(Rank rank_in, Suit suit_in);
TEST(test_overriden_initializing)
{
    //
}

TEST(test_get_rank) //rhea
{
    //
}

TEST(test_get_suit) //rhea
{
    //
}

//EFFECTS Returns the suit
  //HINT: the left bower is the trump suit!
  //Suit get_suit(Suit trump) const;
TEST(test_get_rank_with_suit) //rhea
{
    //
}

 //EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
//   bool is_face_or_ace() const;
TEST(test_is_face_or_ace)
{
    //
}

  //EFFECTS Returns true if card is the Jack of the trump suit
//   bool is_right_bower(Suit trump) const;
TEST(test_is_right_bower)
{

}

  //EFFECTS Returns true if card is the Jack of the next suit
//   bool is_left_bower(Suit trump) const;
TEST(test_is_left_bower)
{
    //
}

  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
//   bool is_trump(Suit trump) const;
TEST(test_is_trump_suit)
{
    //
}

// //EFFECTS Prints Card to stream, for example "Two of Spades"
// std::ostream & operator<<(std::ostream &os, const Card &card);
TEST(test_ostram_operator)
{
    //
}

// //EFFECTS Reads a Card from a stream in the format "Two of Spades"
// //NOTE The Card class declares this operator>> "friend" function,
// //     which means it is allowed to access card.rank and card.suit.
// std::istream & operator>>(std::istream &is, Card &card);
TEST(test_istream_operator)
{
    //
}

// //EFFECTS Returns true if lhs is lower value than rhs.
// //  Does not consider trump.
// bool operator<(const Card &lhs, const Card &rhs);
TEST(test_less_than_operator)
{
    //
}

// //EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
// //  Does not consider trump.
// bool operator<=(const Card &lhs, const Card &rhs);
TEST(test_less_than_or_equal_operator)
{
    //
}

// //EFFECTS Returns true if lhs is higher value than rhs.
// //  Does not consider trump.
// bool operator>(const Card &lhs, const Card &rhs);
TEST(test_more_than_operator)
{
    //
}

// //EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
// //  Does not consider trump.
// bool operator>=(const Card &lhs, const Card &rhs);
TEST(test_more_than_or_equal_operator)
{
    //
}

// //EFFECTS Returns true if lhs is same card as rhs.
// //  Does not consider trump.
// bool operator==(const Card &lhs, const Card &rhs);
TEST(test_equal_operator)
{
    //
}

// //EFFECTS Returns true if lhs is not the same card as rhs.
// //  Does not consider trump.
// bool operator!=(const Card &lhs, const Card &rhs);
TEST(test_not_equal_operator)
{
    //
}

// //EFFECTS returns the next suit, which is the suit of the same color
// Suit Suit_next(Suit suit);
TEST(test_next_suit)
{
    //
}

// //EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// // order, as described in the spec.
// bool Card_less(const Card &a, const Card &b, Suit trump);
TEST(test_less_card_basic)
{
    //
}

// //EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
// //  and the suit led to determine order, as described in the spec.
// bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump);
TEST(test_less_card_with_suit)
{
    //
}

TEST_MAIN()
