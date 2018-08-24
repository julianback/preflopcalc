

#include <card.h>
#include <vector>
#include <algorithm>

#ifndef _HAND_H
#define _HAND_H

class Hand
{
  public:
    std::vector<Card>    GetHand();
    std::vector<Card>    GetHand() const;
    void                 SortHand();
    void                 SetSize(int size);
    size_t               Size();
    size_t               Size() const;
    void                 Receive(Card card);
    void                 Reset();
  private:
    std::vector<Card>    _hand;

};

std::vector<Card> Hand::GetHand()
{
  return _hand;
}

std::vector<Card> Hand::GetHand() const
{
  return _hand;
}

void Hand::SortHand()
{
  sort (_hand.begin(), _hand.end());
  reverse (_hand.begin(), _hand.end());
}

void Hand::SetSize(int size)
{
  _hand.resize(size);
}

size_t Hand::Size()
{
  return _hand.size();
}

size_t Hand::Size() const
{
  return _hand.size();
}

void Hand::Receive(Card card)
{
  _hand.push_back(card);
}

void Hand::Reset()
{
  _hand.clear();
}

#endif

