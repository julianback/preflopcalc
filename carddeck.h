
#include <list>
#include <vector>
#include <algorithm>  // find
#include <random>     // mt19937 gen
#include <card.h>

#ifndef _CARDDECK_H
#define _CARDDECK_H

std::mt19937 gen (std::chrono::system_clock::now().time_since_epoch().count());

class CardDeck
{
  public:
          /* CardDeck         ();        // default constructor */

    void  InitalizeDeck    ();        // initalize deck
    void  ReinitalizeDeck  ();        // reinitalize deck
    void  Shuffle          ();        // shuffle deck
    Card  Draw             ();        // draw top card
    Card  Draw             (Card c);  // draw specific card
    int   GetDeckSize      ();        // return deck size
    void  PlaceTop         (Card c);  // place card on top of deck
    void  PrintDeck        ();        // print deck (could be better)
    bool  InDeck           (Card c);  // check if a card has been drawn yet

  private:
    std::list<Card> _deck;
    int             _deckSize = 52;
    // can this be better??
    SuitType        _suitArray[4]  = {Club, Diamond, Heart, Spade};
    FaceType        _faceArray[13] = {Two, Three, Four, Five, Six, Seven, Eight,
                                      Nine, Ten, Jack, Queen, King, Ace};
};

/* CardDeck::CardDeck() */
/* {} */

void CardDeck::InitalizeDeck()
{

  for (int i = 0; i < 13; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      Card temp(_faceArray[i], _suitArray[j]);
      _deck.push_front(temp);
    }
  }
}

void CardDeck::ReinitalizeDeck()
{
  _deck.clear();
  InitalizeDeck();
  _deckSize = 52;
}

void CardDeck::Shuffle()
{
   std::vector<Card> V(_deck.begin(), _deck.end());
   shuffle(V.begin(), V.end(), gen);
   _deck.assign(V.begin(), V.end());
}

Card CardDeck::Draw()
{
  if (_deckSize == 0)
  {
    std::cerr << "ERROR *** DECK EMPTY";
    Card temp;
    return temp;
  }
  --_deckSize;
  Card frontCard = _deck.front();
  _deck.pop_front();
  return frontCard;
}

Card CardDeck::Draw(Card c)
{
  PlaceTop(c);
  return Draw();
}

int CardDeck::GetDeckSize()
{
  return _deckSize;
}

void CardDeck::PlaceTop(Card c)
{
  _deck.remove(c);      // remove the card c from the deck
  _deck.push_front(c);  // put c on the top
}

void CardDeck::PrintDeck()
{
  std::list<Card>::iterator listIter = _deck.begin();
  while (listIter != _deck.end())
  {
    listIter->PrintShort();
    std::cout << '\n';
    ++listIter;
  }
}

// check if a card has been drawn yet
bool CardDeck::InDeck(Card c)
{
  std::list<Card>::iterator findIter = std::find(_deck.begin(), _deck.end(), c);
  if (findIter == _deck.end())
    return false;  // card not found, that is, already drawn
  return true;
}

#endif

