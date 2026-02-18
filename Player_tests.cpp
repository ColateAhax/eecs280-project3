#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) 
{
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}
// Add more tests here



//-------------------------------------------------
//SIMPLE PLAYER TESTS
//-------------------------------------------------


// //EFFECTS returns player's name
// virtual const std::string & get_name() const = 0;
TEST(test_simple_player_get_name)
{
    Player * simple_Player = Player_factory("Simple Play", "Simple");
    ASSERT_EQUAL("Simple Play", simple_Player->get_name());

    delete simple_Player;
}

// //REQUIRES player has less than MAX_HAND_SIZE cards
// //EFFECTS  adds Card c to Player's hand
// virtual void add_card(const Card &c) = 0;
TEST(test_simple_player_add_card)
{
    Player * simple_Player = Player_factory("Simple Play", "Simple");
    Card card1(JACK, HEARTS);
    Card card2(QUEEN, HEARTS);

    simple_Player->add_card(card1);
    simple_Player->add_card(card2);

    //in this case card 2 is best card to play
    Card temp(TEN, SPADES);
    ASSERT_TRUE(card2 == simple_Player->play_card(temp, HEARTS));

    delete simple_Player;
}

// //REQUIRES round is 1 or 2
// //MODIFIES order_up_suit
// //EFFECTS If Player wishes to order up a trump suit then return true and
// //  change order_up_suit to desired suit.  If Player wishes to pass, then do
// //  not modify order_up_suit and return false.
// virtual bool make_trump(const Card &upcard, bool is_dealer,
//                         int round, Suit &order_up_suit) const = 0;
TEST(test_simple_player_make_trump)
{
    Player * simple_Player = Player_factory("Simple Play", "Simple");

    delete simple_Player;
}

// //REQUIRES Player has at least one card
// //EFFECTS  Player adds one card to hand and removes one card from hand.
// virtual void add_and_discard(const Card &upcard) = 0;
TEST(test_simple_player_add_and_discard)
{
    Card upCard(QUEEN, SPADES);

    Player * simple_Player = Player_factory("Simple Play", "Simple");

    simple_Player->add_card(Card(ACE, CLUBS));
    simple_Player->add_card(Card(KING, CLUBS));
    simple_Player->add_card(Card(QUEEN, CLUBS));
    simple_Player->add_card(Card(JACK, CLUBS));
    simple_Player->add_card(Card(TEN, CLUBS)); //worst card

    simple_Player->add_and_discard(upCard);
    //led card returns lowest non trump card in deck
    //so it should not return ten of clubs
    ASSERT_FALSE(simple_Player->lead_card(DIAMONDS) == Card(TEN, CLUBS));

    Card upCard2 (NINE, SPADES);

    Player * simple_Player2 = Player_factory("Simple Play", "Simple");
    simple_Player2->add_card(Card(ACE, CLUBS)); //right bower
    simple_Player2->add_card(Card(KING, CLUBS)); //left bower
    simple_Player2->add_card(Card(QUEEN, CLUBS)); //trump
    simple_Player2->add_card(Card(JACK, CLUBS)); //trump
    simple_Player2->add_card(Card(TEN, CLUBS)); //trump

    simple_Player2->add_and_discard(upCard2);
    //led card returns lowest non trump card in deck
    //so it should discard the upcard as if it hadnt picked it up
    ASSERT_FALSE(simple_Player2->lead_card(DIAMONDS) == Card(NINE, SPADES));

    delete simple_Player2;
}

// //REQUIRES Player has at least one card
// //EFFECTS  Leads one Card from Player's hand according to their strategy
// //  "Lead" means to play the first Card in a trick.  The card
// //  is removed the player's hand.
// virtual Card lead_card(Suit trump) = 0;
TEST(test_simple_player_lead_card)
{
    Player * simple_Player = Player_factory("Simple Play", "Simple");
    Suit trump = HEARTS;

    simple_Player->add_card(Card(JACK, trump)); //right bower
    simple_Player->add_card(Card(JACK, DIAMONDS)); //left bower
    simple_Player->add_card(Card(TEN, trump)); //trump
    simple_Player->add_card(Card(NINE, DIAMONDS)); //non trump
    simple_Player->add_card(Card(QUEEN, CLUBS)); //non trump

    //since it returns highest non trump card then it should return queen of clubs
    ASSERT_TRUE(simple_Player->lead_card(trump) == Card(QUEEN, CLUBS));
    delete simple_Player;


    Player * simple_Player2 = Player_factory("Simple Play", "Simple");

    simple_Player2->add_card(Card(JACK, trump)); //right bower
    simple_Player2->add_card(Card(JACK, DIAMONDS)); //left bower
    simple_Player2->add_card(Card(TEN, trump)); //trump
    simple_Player2->add_card(Card(NINE, trump)); //trump
    simple_Player2->add_card(Card(QUEEN, trump)); //trump
    //since player has all trumps it should return right bower
    ASSERT_TRUE(simple_Player2->lead_card(trump) == Card(JACK, trump));
    delete simple_Player2;
}

// //REQUIRES Player has at least one card
// //EFFECTS  Plays one Card from Player's hand according to their strategy.
// //  The card is removed from the player's hand.
// virtual Card play_card(const Card &led_card, Suit trump) = 0;
TEST(test_simple_player_play_card)
{
    Player * simple_Player = Player_factory("Simple Play", "Simple");
    Suit trump = HEARTS;
    Card led_card(TEN, SPADES);

    simple_Player->add_card(Card(JACK, trump)); //right bower
    simple_Player->add_card(Card(JACK, DIAMONDS)); //left bower
    simple_Player->add_card(Card(QUEEN, SPADES)); //led suit
    simple_Player->add_card(Card(NINE, SPADES)); //led suit
    simple_Player->add_card(Card(QUEEN, CLUBS)); //random

    //since player can follow suit
    //it should return Queen of Spades
    ASSERT_TRUE(simple_Player->play_card(led_card, trump) == Card(QUEEN, SPADES));
    delete simple_Player;


    Player * simple_Player2 = Player_factory("Simple Play", "Simple");

    simple_Player2->add_card(Card(JACK, trump)); //right bower
    simple_Player2->add_card(Card(JACK, DIAMONDS)); //left bower
    simple_Player2->add_card(Card(TEN, trump)); //trump
    simple_Player2->add_card(Card(NINE, trump)); //trump
    simple_Player2->add_card(Card(QUEEN, trump)); //trump
    //since player cannot follow suit it plays worst hand
    //which is a Nine of Hearts
    ASSERT_TRUE(simple_Player2->play_card(led_card, trump) == Card(NINE, trump));
    delete simple_Player2;
}



//-------------------------------------------------
//HUMAN PLAYER TESTS
//-------------------------------------------------

// //EFFECTS returns player's name
// virtual const std::string & get_name() const = 0;
TEST(test_human_player_get_name)
{
    //
}

// //REQUIRES player has less than MAX_HAND_SIZE cards
// //EFFECTS  adds Card c to Player's hand
// virtual void add_card(const Card &c) = 0;
TEST(test_human_player_add_card)
{
    //
}

// //REQUIRES round is 1 or 2
// //MODIFIES order_up_suit
// //EFFECTS If Player wishes to order up a trump suit then return true and
// //  change order_up_suit to desired suit.  If Player wishes to pass, then do
// //  not modify order_up_suit and return false.
// virtual bool make_trump(const Card &upcard, bool is_dealer,
//                         int round, Suit &order_up_suit) const = 0;
TEST(test_human_player_make_trump)
{
    //
}

// //REQUIRES Player has at least one card
// //EFFECTS  Player adds one card to hand and removes one card from hand.
// virtual void add_and_discard(const Card &upcard) = 0;
TEST(test_human_player_add_and_discard)
{
    //
}

// //REQUIRES Player has at least one card
// //EFFECTS  Leads one Card from Player's hand according to their strategy
// //  "Lead" means to play the first Card in a trick.  The card
// //  is removed the player's hand.
// virtual Card lead_card(Suit trump) = 0;
TEST(test_human_player_lead_card)
{
    //
}

// //REQUIRES Player has at least one card
// //EFFECTS  Plays one Card from Player's hand according to their strategy.
// //  The card is removed from the player's hand.
// virtual Card play_card(const Card &led_card, Suit trump) = 0;
TEST(test_human_player_play_card)
{
    //
}

TEST_MAIN()
