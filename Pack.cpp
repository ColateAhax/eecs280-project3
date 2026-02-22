#include "Pack.hpp"
#include <cassert>
#include <iostream>
#include <array>

using namespace std;

// EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on. 
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  // NOTE: The pack is initially full, with no cards dealt.
Pack::Pack()
:next(0)
{
    int card_index = 0;
    for(int s = 0; s < 4; s++)
    {
        Suit suit = static_cast<Suit>(s);
        //going thru suit
        for(int r = NINE; r <= ACE; r++)
        {
            //going through 
            
            //enum can be auto casted to int
            //int cannot be auto casted enum
            Rank rank = static_cast<Rank>(r);
            Card newCard(rank, suit);
            
            cards[card_index++] = newCard;
        }
    }
}

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  // NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(std::istream& pack_input)
{//good job employee
    next = 0;
    for (int i = 0; i < PACK_SIZE; i++)
    {
        std::string str;
        Rank r;
        Suit s;
        //is the card array already filled with cards should we edit 
        // existing values or create new card objects
        pack_input >> r >> str >> s;

        Card newCard(r, s);
        cards[i] = newCard;
    }
}

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one()
{
    return cards[next++];
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset()
{
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle()
{
    for (int count = 0; count < 7; count++)
    {
        Card temp[PACK_SIZE];

        for (int i = 0; i < PACK_SIZE / 2; i++)
        {
            // Bottom half goes to odd positions
            temp[2 * i + 1] = cards[i];
            // Top half goes to even positions
            temp[2 * i] = cards[i + PACK_SIZE / 2];
        }

        for (int c = 0; c < PACK_SIZE; c++)
        {
            cards[c] = temp[c];
        }
    }

    next = 0;

}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const
{
    if (next == PACK_SIZE) return true;

    return false;
}