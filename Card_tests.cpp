#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor_provided) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here

//EFFECTS Initializes Card to the Two of Spades//rhea
//Card();
TEST(test_default_initializing)//tbl
{
    Card newCard;
    ASSERT_EQUAL(newCard.get_rank(), TWO);
    ASSERT_EQUAL(newCard.get_suit(), SPADES);
}

//EFFECTS Initializes Card to specified rank and suit
// Card(Rank rank_in, Suit suit_in);
TEST(test_overriden_initializing)//tbl
{
    Rank r = ACE;
    Suit s = HEARTS;

    Card newCard(r, s);

    ASSERT_EQUAL(newCard.get_rank(), r);
    ASSERT_EQUAL(newCard.get_suit(), s);
}

TEST(test_get_rank) //rhea
{
   
    Card newCard(ACE, HEARTS);

    ASSERT_EQUAL(newCard.get_rank(), ACE);
}

TEST(test_get_suit) //rhea
{
     Card newCard(ACE, HEARTS);

    ASSERT_EQUAL(newCard.get_suit(), HEARTS);
}

//EFFECTS Returns the suit
  //HINT: the left bower is the trump suit!
  //Suit get_suit(Suit trump) const;
TEST(test_get_suit_with_trump) //rhea
{
    //checking if the left bower changes suits
    Card newCard(JACK, HEARTS);
    Suit trump = DIAMONDS;
    ASSERT_EQUAL(newCard.get_suit(trump), trump);

    //checking that only the jack is the one
    //that changes
    Card Card2(TEN, HEARTS);
    trump = DIAMONDS;
    ASSERT_EQUAL(Card2.get_suit(trump), HEARTS);
}

 //EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
//   bool is_face_or_ace() const;
TEST(test_is_face_or_ace)//tbl
{
    Rank r = ACE;
    Suit s = HEARTS;
    Card card1(r, s);
    ASSERT_TRUE(card1.is_face_or_ace());

    r = TEN;
    s = CLUBS;
    Card card2(r, s);
    ASSERT_TRUE(!card2.is_face_or_ace());
}

  //EFFECTS Returns true if card is the Jack of the trump suit
//   bool is_right_bower(Suit trump) const;
TEST(test_is_right_bower)//tbl
{
    //not a jack so always false
    Card card1(TEN, HEARTS);
    ASSERT_FALSE(card1.is_right_bower(DIAMONDS));

    //this is left bowe
    Card card2(JACK, HEARTS);
    ASSERT_FALSE(card2.is_right_bower(DIAMONDS));

    //this is right bower
    Card card3(JACK, DIAMONDS);
    ASSERT_TRUE(card3.is_right_bower(DIAMONDS));
}

  //EFFECTS Returns true if card is the Jack of the next suit
//   bool is_left_bower(Suit trump) const;
TEST(test_is_left_bower)//tbl
{
    //not a jack so always false
    Card card1(TEN, HEARTS);
    ASSERT_FALSE(card1.is_left_bower(DIAMONDS));

    //this is left bower
    Card card2(JACK, HEARTS);
    ASSERT_TRUE(card2.is_left_bower(DIAMONDS));

    //this is rigtht bower
    Card card3(JACK, DIAMONDS);
    ASSERT_FALSE(card3.is_left_bower(DIAMONDS));
}

  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
//   bool is_trump(Suit trump) const;
TEST(test_is_trump_suit)//rhea
{
    //checking a trump card
    Suit trump = HEARTS;
    Card Card1(EIGHT, trump);
    ASSERT_TRUE(Card1.is_trump(trump));

    //checking left bower
    Card Card2(JACK, Suit_next(trump));
    ASSERT_TRUE(Card2.is_trump(trump));
    
    //checking a non trump card
    Card Card3(EIGHT, SPADES);
    ASSERT_FALSE(Card3.is_trump(trump));
    
}

// //EFFECTS Prints Card to stream, for example "Two of Spades"
// std::ostream & operator<<(std::ostream &os, const Card &card);
TEST(test_ostream_operator)
{
    Card newCard(TEN, HEARTS);
    
    std::ostringstream expected;
    expected << "Ten of Hearts";

    std::ostringstream actual;
    actual << newCard;

    ASSERT_EQUAL(expected.str(), actual.str());
}

// //EFFECTS Reads a Card from a stream in the format "Two of Spades"
// //NOTE The Card class declares this operator>> "friend" function,
// //     which means it is allowed to access card.rank and card.suit.
// std::istream & operator>>(std::istream &is, Card &card);
TEST(test_istream_operator)
{
    Card newCard;

    std::istringstream is("Ten of Hearts");

    is >> newCard;

    ASSERT_EQUAL(newCard.get_rank(), TEN);
    ASSERT_EQUAL(newCard.get_suit(), HEARTS);
}

// //EFFECTS Returns true if lhs is lower value than rhs.
// //  Does not consider trump.
// bool operator<(const Card &lhs, const Card &rhs);
TEST(test_less_than_operator)//tbl
{
    Card card1(TEN, HEARTS);
    Card card2(ACE, HEARTS);
    Card card3(ACE, SPADES);

    //card 1 should be less than card 2
    ASSERT_TRUE(card1 < card2);

    //card 2 and 3 should be equal so it returns false
    ASSERT_FALSE(card2 < card3)
}

// //EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
// //  Does not consider trump.
// bool operator<=(const Card &lhs, const Card &rhs);
TEST(test_less_than_or_equal_operator)//tbl
{
    Card card1(TEN, HEARTS);
    Card card2(ACE, HEARTS);
    Card card3(ACE, SPADES);

    //card 1 should be less than card 2
    ASSERT_TRUE(card1 <= card2);

    //card 2 and 3 should be equal so it returns true
    ASSERT_TRUE(card2 <= card3)
}

// //EFFECTS Returns true if lhs is higher value than rhs.
// //  Does not consider trump.
// bool operator>(const Card &lhs, const Card &rhs);
TEST(test_more_than_operator)//tbl
{
    Card card1(TEN, HEARTS);
    Card card2(ACE, HEARTS);
    Card card3(ACE, SPADES);

    //card 2 should be more than card 1
    ASSERT_TRUE(card2 > card1);

    //card 2 and 3 should be equal so it returns false
    ASSERT_FALSE(card2 > card3)
}

// //EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
// //  Does not consider trump.
// bool operator>=(const Card &lhs, const Card &rhs);
TEST(test_more_than_or_equal_operator)//tbl
{
    Card card1(TEN, HEARTS);
    Card card2(ACE, HEARTS);
    Card card3(ACE, SPADES);

    //card 2 should be more than card 1
    ASSERT_TRUE(card2 >= card1);

    //card 2 and 3 should be equal so it returns true
    ASSERT_TRUE(card2 >= card3)
}

// //EFFECTS Returns true if lhs is same card as rhs.
// //  Does not consider trump.
// bool operator==(const Card &lhs, const Card &rhs);
TEST(test_equal_operator)
{
    Card card1(TEN, HEARTS);
    Card card2(TEN, HEARTS);

    ASSERT_TRUE(card2 == card1);

    Card card3(NINE, HEARTS);
    Card card4(TEN, HEARTS);

    ASSERT_FALSE(card3 == card4);

}

// //EFFECTS Returns true if lhs is not the same card as rhs.
// //  Does not consider trump.
// bool operator!=(const Card &lhs, const Card &rhs);
TEST(test_not_equal_operator)
{
    Card card1(TEN, HEARTS);
    Card card2(NINE, HEARTS);

    ASSERT_TRUE(card2 != card1);

    Card card3(TEN, HEARTS);
    Card card4(TEN, HEARTS);
    
    ASSERT_FALSE(card3 != card4);
}

// //EFFECTS returns the next suit, which is the suit of the same color
// Suit Suit_next(Suit suit);
TEST(test_next_suit)//tbl
{
    Suit spades(SPADES);
    //next suit of spades is clubs
    ASSERT_EQUAL(Suit_next(spades), CLUBS);

    Suit clubs(CLUBS);
    //next suit of clubs is spades
    ASSERT_EQUAL(Suit_next(clubs), SPADES);

    Suit hearts(HEARTS);
    //next suit of hearts is diamonds
    ASSERT_EQUAL(Suit_next(hearts), DIAMONDS);

    Suit diamonds(DIAMONDS);
    //next suit of diamonds is hearts
    ASSERT_EQUAL(Suit_next(diamonds), HEARTS);

    // //the following should be false
    // ASSERT_FALSE(Suit_next(diamonds), SPADES);
    // ASSERT_FALSE(Suit_next(clubs), HEARTS);
}

// //EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// // order, as described in the spec.
// bool Card_less(const Card &a, const Card &b, Suit trump);
TEST(test_less_card_basic)//rhea
{   
    //normal rank comparison
    Card cardB(TEN, HEARTS);
    Card cardA(ACE, HEARTS);
   
    ASSERT_TRUE(Card_less(cardB, cardA, SPADES));

    //false
    //normal rank comparison
   
    ASSERT_FALSE(Card_less(cardA, cardB, SPADES));
    
    //suit comparison
    Card cardC(TEN, SPADES);
    Card cardD(TEN, HEARTS);
   
    ASSERT_TRUE(Card_less(cardC, cardD, CLUBS));

    //left and right bower
    Suit trump = CLUBS;
    Card cardLeft(JACK, Suit_next(CLUBS));
    Card cardRight(JACK, trump);
   
    ASSERT_TRUE(Card_less(cardLeft, cardRight, trump));



}

// //EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
// //  and the suit led to determine order, as described in the spec.
// bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump);
TEST(test_less_card_with_suit)
{
    //
}

TEST_MAIN()
