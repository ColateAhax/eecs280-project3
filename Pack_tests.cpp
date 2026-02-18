#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

// // EFFECTS: Initializes the Pack to be in the following standard order:
// //          the cards of the lowest suit arranged from lowest rank to
// //          highest rank, followed by the cards of the next lowest suit
// //          in order from lowest to highest rank, and so on. 
// // NOTE: The standard order is the same as that in pack.in.
// // NOTE: Do NOT use pack.in in your implementation of this function
// // NOTE: The pack is initially full, with no cards dealt.
// Pack();
TEST(test_basic_pack_ctor)
{
    //
}

// // REQUIRES: pack_input contains a representation of a Pack in the
// //           format required by the project specification
// // MODIFIES: pack_input
// // EFFECTS: Initializes Pack by reading from pack_input.
// // NOTE: The pack is initially full, with no cards dealt.
// Pack(std::istream& pack_input);
TEST(test_parameters_pack_ctor)
{
    //
}

// // REQUIRES: cards remain in the Pack
// // EFFECTS: Returns the next card in the pack and increments the next index
// Card deal_one();
TEST(test_deal_one)
{
    //
}

// // EFFECTS: Resets next index to first card in the Pack
// void reset();
TEST(test_reset)
{
    //
}

// // EFFECTS: Shuffles the Pack and resets the next index. This
// //          performs an in shuffle seven times. See
// //          https://en.wikipedia.org/wiki/In_shuffle.
// void shuffle();
TEST(test_shuffle)
{
    //
}

// // EFFECTS: returns true if there are no more cards left in the pack
// bool empty() const;
TEST(test_empty)
{
    //
}

TEST_MAIN()
