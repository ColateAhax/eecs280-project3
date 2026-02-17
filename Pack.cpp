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
{
    //good job boss
//boss ts the easiest func
int card_index;
    for(int s = 0; s < 4; s++)
    {
        Suit suit = static_cast<Suit>(s);
        //going thru suit
        for(int r = TWO; r <= ACE; r++){//going through rank
            Rank rank = static_cast<Rank>(r);
            Card newCard(rank, suit);//nick help i need to input parameters that are Rank and Suit objects idk how to
            cards[card_index] = newCard;
            card_index++;
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
    for (int i = 0; i < 24; i++)
    {
        std::string str;
        Rank r;
        Suit s;
        //is the card array already filled with cards should we edit existing values or create new card objects
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

    //calcualting the number of elements by getting total array byte size and
    //dividing it by size of one element
    int totalCards = sizeof(cards) / sizeof(cards[0]);
    
    Card temp[totalCards];
    int count = 0;
    while (count < 7)
    //going through each element in the array 
    for(int i = 0; i < totalCards; i++){
        //in shuffle formula
        int newPos = (2i + 1) %(totalCards + 1);

        if newPos == totalCards{ //making sure it doesnt go out of bounds
            newPos -= 1;
        }
        temp[newPos] = cards[i];
    
    }

    for(int c = 0; c < totalCards; c++){
        cards[c] = temp[c];
    }
    
    count++;
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const
{
    if (next == 24) return true;

    return false;
}