
#include <iostream>

#ifndef _CARD_H
#define _CARD_H

enum SuitType
{
  Club = 0,
  Diamond,
  Heart,
  Spade
};

enum FaceType
{
  Two = 2,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King,
  Ace
};

class Card;
std::ostream& operator << (std::ostream& out, const SuitType value);
std::ostream& operator << (std::ostream& out, const FaceType value);
bool operator < (const Card c1, const Card c2);
bool operator != (const Card c1, const Card c2);
bool operator == (const Card c1, const Card c2);

class Card
{
  public:
    Card ();                        // default constructor
    Card (FaceType f, SuitType s);  // parameterized constructor

    FaceType     GetFace   ();
    SuitType     GetSuit   ();
    FaceType     GetFace   () const;
    SuitType     GetSuit   () const;
    void         PrintShort     ();             // print card
    void         PrintLong     ();             // print card

    void         SetFace   (FaceType f);
    void         SetSuit   (SuitType s);
    Card&        operator= (const Card&); // assignment operator

  private:
    FaceType     _face;
    SuitType     _suit;
    
    /* void         SetFace   (char); */
    /* void         SetSuit   (std::string s); */
};

/* bool operator == (const Card c1, const Card c2); */
/* bool operator != (const Card c1, const Card c2); */
/* bool operator <  (const Card c1, const Card c2); */

Card::Card()
{}

Card::Card (FaceType f, SuitType s) : _face(f), _suit(s)
{}

FaceType Card::GetFace()
{
  return _face;
}

SuitType Card::GetSuit()
{
  return _suit;
}

FaceType Card::GetFace() const
{
  return _face;
}

SuitType Card::GetSuit() const
{
  return _suit;
}

void Card::SetSuit (SuitType s)
{
  _suit = s;
}

void Card::SetFace (FaceType f)
{
  _face = f;
}

void Card::PrintLong()
{
  std::cout << _face << " of " << _suit;// << '\n';
}

void Card::PrintShort()
{
  std::cout << _face << _suit;// << '\n';
}

Card& Card::operator= (const Card& c)
{
  if (this != &c) // check for self assignment
  {
    SetSuit(c.GetSuit());
    SetFace(c.GetFace());
  }
  return *this;
}

bool operator == (const Card c1, const Card c2)
{
  if ((c1.GetFace() == c2.GetFace()) && (c1.GetSuit() == c2.GetSuit()))
    return true;
  return false;
}

bool operator != (const Card c1, const Card c2)
{
  return !(c1 == c2);
}

bool operator < (const Card c1, const Card c2)
{
  return c1.GetFace() < c2.GetFace();
}

// https://stackoverflow.com/a/3342891
std::ostream& operator<< (std::ostream& out, const SuitType value)
{
  switch(value)
  {
    case 0: out << "C";
            break;
    case 1: out << "D";
            break;
    case 2: out << "H";
            break;
    case 3: out << "S";
            break;
  }
  return out;
}

std::ostream& operator<< (std::ostream& out, const FaceType value)
{
  switch(value)
  {
    case 2: out << "2";
            break;
    case 3: out << "3";
            break;
    case 4: out << "4";
            break;
    case 5: out << "5";
            break;
    case 6: out << "6";
            break;
    case 7: out << "7";
            break;
    case 8: out << "8";
            break;
    case 9: out << "9";
            break;
    case 10: out << "T";
            break;
    case 11: out << "J";
            break;
    case 12: out << "Q";
            break;
    case 13: out << "K";
            break;
    case 14: out << "A";
            break;
  }
  return out;
}

#endif

