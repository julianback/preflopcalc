
#include <card.h>      // card class
#include <carddeck.h>  // deck class
#include <hand.h>      // hand class
#include <getwinner.h>
/* #include <string> */
/* #include <algorithm> */
/* #include <unordered_map> */

/* enum Rank */
/* { */
/*   HighCard, */
/*   OnePair, */
/*   TwoPairs, */
/*   ThreeOfAKind, */
/*   Straight, */
/*   Flush, */
/*   FullHouse, */
/*   FourOfAKind, */
/*   StraightFlush, */
/*   RoyalFlush */
/* }; */

/* enum Result */
/* { */
/*   Player1, */
/*   Player2, */
/*   Tie */
/* }; */

/* std::ostream&    operator <<            (std::ostream& out, const Rank value); */
/* bool             InputValid             (const std::string& faceIn, */
/*                                          const std::string& suitIn); */
/* FaceType         String2Face            (const std::string& faceIn); */
/* SuitType         String2Suit            (const std::string& suitIn); */
/* Result           GetWinner              (const Hand& hand1, const Hand& hand2); */
/* Rank             GetRank                (const Hand& hand); */
/* Result           GetWinnerHighCard      (const Hand& hand1, const Hand& hand2); */
/* Result           GetWinnerOnePair       (const Hand& hand1, const Hand& hand2); */
/* Result           GetWinnerTwoPairs      (const Hand& hand1, const Hand& hand2); */
/* Result           GetWinnerThreeOfAKind  (const Hand& hand1, const Hand& hand2); */
/* Result           GetWinnerStraight      (const Hand& hand1, const Hand& hand2); */
/* Result           GetWinnerFlush         (const Hand& hand1, const Hand& hand2); */
/* Result           GetWinnerFullHouse     (const Hand& hand1, const Hand& hand2); */
/* Result           GetWinnerFourOfAKind   (const Hand& hand1, const Hand& hand2); */
/* Result           GetWinnerStraightFlush (const Hand& hand1, const Hand& hand2); */
/* Result           GetWinnerRoyalFlush    (const Hand& hand1, const Hand& hand2); */
/* std::vector<int> HandCount              (const Hand& hand); */
/* bool             IsRoyalFlush           (const Hand& hand); */
/* bool             IsStraightFlush        (const Hand& hand); */
/* bool             IsFourOfAKind          (const Hand& hand); */
/* bool             IsFullHouse            (const Hand& hand); */
/* bool             IsFlush                (const Hand& hand); */
/* bool             IsStraight             (const Hand& hand); */
/* bool             IsThreeOfAKind         (const Hand& hand); */
/* bool             IsTwoPairs             (const Hand& hand); */
/* bool             IsOnePair              (const Hand& hand); */
/* bool             IsHighCard             (const Hand& hand); */

int main()
{
  int num = 0;
  std::cout << "Number of simulations: ";
  std::cin >> num;
  int numP1 = 0;
  int numP2 = 0;
  int numT = 0;

  CardDeck deck;
  deck.InitalizeDeck();
  std::vector<Card> player1CardVec(2);           // card input
  std::vector<Card> player2CardVec(2);           // card input
  Hand player1;         // hero
  Hand player2;      // villain
  std::string faceInString;
  std::string suitInString;
  Result winner;

  // choose cards 
  for (size_t i = 0; i < 2; ++i) // two players
  {
    for (size_t j = 0; j < 2; ++j) // two cards
    {
      std::cout << "Enter Player " << i + 1 << ", card " << j + 1 << ": ";
      std::cin >> faceInString >> suitInString;
      FaceType faceIn = String2Face(faceInString);
      SuitType suitIn = String2Suit(suitInString);
      if (i == 0)
      {
        player1CardVec[j].SetFace(faceIn);
        player1CardVec[j].SetSuit(suitIn);
      }
      else
      {
        player2CardVec[j].SetFace(faceIn);
        player2CardVec[j].SetSuit(suitIn);
      }
    }
  }

  std::cout << "Please enter the flop, or b to begin simulation: ";
  int count = 0;
  Card card;
  
  while (count != 3)
  {
    std::cin >> faceInString;
    if (faceInString == "b")
      break;
    std::cin >> suitInString;
    FaceType faceIn = String2Face(faceInString);
    SuitType suitIn = String2Suit(suitInString);
    card.SetFace(faceIn);
    card.SetSuit(suitIn);
    /* player1.Receive(deck.Draw(card)); */
    /* player2.Receive(card); */
    player1CardVec.push_back(card);
    player2CardVec.push_back(card);

    ++count;
  }






  for (int i = 0; i < num; ++i)
  {
    /* std::cout << ii << '\n'; */
    deck.Shuffle();

    // deal chosen cards (removing from the deck)
    for (size_t j = 0; j < player1CardVec.size(); ++j)
    {
      player1.Receive(deck.Draw(player1CardVec[j]));
      player2.Receive(deck.Draw(player2CardVec[j]));
    }

    // flop turn river
    /* Card card; */
    for (size_t j = 0; j < 7 - player1CardVec.size(); ++j)
    {
      card = deck.Draw();  // draw a card
      player1.Receive(deck.Draw(card));
      player2.Receive(deck.Draw(card));
    }

    player1.SortHand();  // sort the hands
    player2.SortHand();

    winner = GetWinner(player1, player2);
    if (winner == Player1)
    {
      ++numP1;
    }
    else if (winner == Player2)
    {
      ++numP2;
    }
    else
    {
      ++numT;
    }
    player1.Reset();
    player2.Reset();
    deck.ReinitalizeDeck();
  }

  std::cout << "Player 1 wins " << (float) numP1*100/num << "%\n";
  std::cout << "Player 2 wins " << (float) numP2*100/num << "%\n";
  std::cout << "There is a tie " << (float) numT*100/num << "%\n";
  return 0;
}


/* std::ostream& operator << (std::ostream& out, const Rank value) */
/* { */
/*   switch(value) */
/*   { */
/*     case 0: out << "High Card"; */
/*             break; */
/*     case 1: out << "One Pair"; */
/*             break; */
/*     case 2: out << "Two Pair"; */
/*             break; */
/*     case 3: out << "Set"; */
/*             break; */
/*     case 4: out << "Straight"; */
/*             break; */
/*     case 5: out << "Flush"; */
/*             break; */
/*     case 6: out << "Full House"; */
/*             break; */
/*     case 7: out << "Quads"; */
/*             break; */
/*     case 8: out << "Straight Flush"; */
/*             break; */
/*     case 9: out << "Royal Flush"; */
/*             break; */
/*   } */
/*   return out; */
/* } */

/* bool InputValid (const std::string& faceIn, const std::string& suitIn) */
/* { */
/*   if ((faceIn != "2") && */
/*       (faceIn != "3") && */
/*       (faceIn != "4") && */
/*       (faceIn != "5") && */
/*       (faceIn != "6") && */
/*       (faceIn != "7") && */
/*       (faceIn != "8") && */
/*       (faceIn != "9") && */
/*       (faceIn != "T") && */
/*       (faceIn != "J") && */
/*       (faceIn != "Q") && */
/*       (faceIn != "K") && */
/*       (faceIn != "A")) */
/*   { */
/*     std::cout << "Options: 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A" << '\n'; */
/*     return false; */
/*   } */

/*   if ((suitIn != "C") && */
/*       (suitIn != "D") && */
/*       (suitIn != "H") && */
/*       (suitIn != "S")) */
/*   { */
/*     std::cout << "Options: C (club), D (diamond, H (heart), S (spade)" << '\n'; */
/*     return false; */
/*   } */
/*   return true; */
/* } */

/* FaceType String2Face (const std::string& faceIn) */
/* { */
/*   if (faceIn == "2") */
/*     return Two; */
/*   else if (faceIn == "3") */
/*     return Three; */
/*   else if (faceIn == "4") */
/*     return Four; */
/*   else if (faceIn == "5") */
/*     return Five; */
/*   else if (faceIn == "6") */
/*     return Six; */
/*   else if (faceIn == "7") */
/*     return Seven; */
/*   else if (faceIn == "8") */
/*     return Eight; */
/*   else if (faceIn == "9") */
/*     return Nine; */
/*   else if (faceIn == "T") */
/*     return Ten; */
/*   else if (faceIn == "J") */
/*     return Jack; */
/*   else if (faceIn == "Q") */
/*     return Queen; */
/*   else if (faceIn == "K") */
/*     return King; */
/*   else if (faceIn == "A") */
/*     return Ace; */
/*   else  // invalid input somehow */
/*   { */
/*     std::cerr << "ERROR *** INVALID INPUT" << '\n'; */
/*     return Two; */
/*   } */
/* } */

/* SuitType String2Suit (const std::string& suitIn) */
/* { */
/*   if (suitIn == "C") */
/*     return Club; */
/*   else if (suitIn == "D") */
/*     return Diamond; */
/*   else if (suitIn == "H") */
/*     return Heart; */
/*   else if (suitIn == "S") */
/*     return Spade; */
/*   else  // invalid input somehow */
/*   { */
/*     std::cerr << "ERROR *** INVALID INPUT" << '\n'; */
/*     return Spade; */
/*   } */
/* } */

/* // https://github.com/HaochenLiu/My-Project-Euler/blob/master/054.cpp */
/* Result GetWinner (const Hand& hand1, const Hand& hand2) */
/* { */
/*   Rank rank1 = GetRank(hand1); */
/*   Rank rank2 = GetRank(hand2); */

/*   /1* std::cout << "Player 1 has a " << rank1 << '\n'; *1/ */
/*   /1* std::cout << "Player 2 has a " << rank2 << '\n'; *1/ */

/*   if (rank1 > rank2)      // player 1 wins */
/*     return Player1; */
/*   else if (rank2 > rank1) // player 2 wins */
/*     return Player2; */
/*   else                    // same hand rank (rank1 == rank 2) */
/*   { */
/*     if (rank1 == RoyalFlush)         return GetWinnerRoyalFlush(hand1, hand2); */
/*     else if (rank1 == StraightFlush) return GetWinnerStraightFlush(hand1, hand2); */
/*     else if (rank1 == FourOfAKind)   return GetWinnerFourOfAKind(hand1, hand2); */
/*     else if (rank1 == FullHouse)     return GetWinnerFullHouse(hand1, hand2); */
/*     else if (rank1 == Flush)         return GetWinnerFlush(hand1, hand2); */
/*     else if (rank1 == Straight)      return GetWinnerStraight(hand1, hand2); */
/*     else if (rank1 == ThreeOfAKind)  return GetWinnerThreeOfAKind(hand1, hand2); */
/*     else if (rank1 == TwoPairs)      return GetWinnerTwoPairs(hand1, hand2); */
/*     else if (rank1 == OnePair)       return GetWinnerOnePair(hand1, hand2); */
/*     else // (rank1 == HighCard) */
/*       return GetWinnerHighCard(hand1, hand2); */
/*   } */

/*   std::cerr << "ERROR *** NO WINNER" << '\n';  // we shouldn't get here */
/*   return Tie; */
/* } */

/* Rank GetRank(const Hand& hand) */
/* { */
/*   if (IsRoyalFlush(hand))    return RoyalFlush; */
/*   if (IsStraightFlush(hand)) return StraightFlush; */
/*   if (IsFourOfAKind(hand))   return FourOfAKind; */
/*   if (IsFullHouse(hand))     return FullHouse; */
/*   if (IsFlush(hand))         return Flush; */
/*   if (IsStraight(hand))      return Straight; */
/*   if (IsThreeOfAKind(hand))  return ThreeOfAKind; */
/*   if (IsTwoPairs(hand))      return TwoPairs; */
/*   if (IsOnePair(hand))       return OnePair; */
/*   /1* if (IsHighCard(hand))      return HighCard; *1/ */
/*   return HighCard;  // if nothing else */
/* } */

/* std::vector<int> HandCount (const Hand& hand) */
/* { */
/*   std::unordered_map<int, int> map; */
/*   /1* size_t n = hand.GetHand().size(); *1/ */
/*   size_t n = hand.Size(); */
/*   for (size_t i = 0; i < n; ++i) */
/*     ++map[hand.GetHand()[i].GetFace()]; */
/*   std::unordered_map<int, int>::iterator mapIter; */
/*   std::vector<int> count; */
/*   for (mapIter = map.begin(); mapIter != map.end(); ++mapIter) */
/*     count.push_back(mapIter->second); */
/*   sort(count.begin(), count.end()); */
/*   return count; */
/* } */

/* bool IsRoyalFlush (const Hand& hand) */
/* { */
/*   size_t n = hand.Size(); */
/*   std::vector<int> suitVec(4); */

/*   for (size_t i = 0; i < 4; ++i)  // loop over suits */
/*   { */
/*     for (size_t j = 0; j < n; ++j) */
/*     { */
/*       if (hand.GetHand()[j].GetSuit() == i) */
/*         ++suitVec[hand.GetHand()[j].GetSuit()]; */
/*     } */
/*   } */

/*   // find max element */
/*   std::vector<int>::iterator suitIter = std::max_element (suitVec.begin(), */
/*                                                           suitVec.end()); */
/*   int isFlush = *suitIter; */
/*   if (isFlush < 5)  // check if we have a flush */
/*     return false; */

/*   // position of max element */
/*   int suit = std::distance(suitVec.begin(), suitIter); */

/*   suitVec.clear(); */
/*   for (size_t i = 0; i < n; ++i) */
/*   { */
/*     if (hand.GetHand()[i].GetSuit() == suit) */
/*       suitVec.push_back(hand.GetHand()[i].GetFace()); */
/*   } */
/*   sort(suitVec.begin(), suitVec.end()); */
/*   reverse(suitVec.begin(), suitVec.end());  // reverse so alg is like IsStraight */

/*   // now suitVec contains all the faces of the flush suit. now we can check if */
/*   // there is a royal straight */

/*   if (std::find(suitVec.begin(), suitVec.end(), 14) != suitVec.end() && */
/*       std::find(suitVec.begin(), suitVec.end(), 13) != suitVec.end() && */
/*       std::find(suitVec.begin(), suitVec.end(), 12) != suitVec.end() && */
/*       std::find(suitVec.begin(), suitVec.end(), 11) != suitVec.end() && */
/*       std::find(suitVec.begin(), suitVec.end(), 10) != suitVec.end()) */
/*     return true; */
/*   return false; */
/* } */

/* bool IsStraightFlush (const Hand& hand) */
/* { */
/*   size_t n = hand.Size(); */
/*   std::vector<int> suitVec(4); */

/*   for (size_t i = 0; i < 4; ++i)  // loop over suits */
/*   { */
/*     for (size_t j = 0; j < n; ++j) */
/*     { */
/*       if (hand.GetHand()[j].GetSuit() == i) */
/*         ++suitVec[hand.GetHand()[j].GetSuit()]; */
/*     } */
/*   } */

/*   // find max element */
/*   std::vector<int>::iterator suitIter = std::max_element (suitVec.begin(), */
/*                                                           suitVec.end()); */
  
/*   int isFlush = *suitIter; */
/*   if (isFlush < 5)  // check if we have a flush */
/*     return false; */

/*   // position of max element */
/*   int suit = std::distance(suitVec.begin(), suitIter); */

/*   suitVec.clear(); */
/*   for (size_t i = 0; i < n; ++i) */
/*   { */
/*     if (hand.GetHand()[i].GetSuit() == suit) */
/*       suitVec.push_back(hand.GetHand()[i].GetFace()); */
/*   } */
/*   sort(suitVec.begin(), suitVec.end()); */
/*   reverse(suitVec.begin(), suitVec.end());  // reverse so alg is like IsStraight */

/*   // now suitVec contains all the faces of the flush suit. now we can check if */
/*   // there is a straight */

/*   // suitVec has at least 5 cards, as we know there is a flush, but could have */
/*   // 6 or 7 cards. so we have 1 to 3 sets of cards to check */
/*   n = suitVec.size() - 4; */
/*   int card = 0; */
/*   for (size_t i = 0; i < n; ++i) */
/*   { */
/*     card = hand.GetHand()[i].GetFace(); */
/*     if (std::find(suitVec.begin(), suitVec.end(), */
/*           card - 1) != suitVec.end() && */
/*         std::find(suitVec.begin(), suitVec.end(), */
/*           card - 2) != suitVec.end() && */
/*         std::find(suitVec.begin(), suitVec.end(), */
/*           card - 3) != suitVec.end() && */
/*         std::find(suitVec.begin(), suitVec.end(), */
/*           card - 4) != suitVec.end()) */
/*       return true; */
/*   } */

/*   // lastly we need to check for the A2345 straight */
/*   if (std::find(suitVec.begin(), suitVec.end(), 14) != suitVec.end() && */
/*       std::find(suitVec.begin(), suitVec.end(), 2) != suitVec.end() && */
/*       std::find(suitVec.begin(), suitVec.end(), 3) != suitVec.end() && */
/*       std::find(suitVec.begin(), suitVec.end(), 4) != suitVec.end() && */
/*       std::find(suitVec.begin(), suitVec.end(), 5) != suitVec.end()) */
/*     return true; */
/*   return false; */
/* } */

/* bool IsFourOfAKind (const Hand& hand) */
/* { */
/*   return (HandCount(hand).back() == 4); */
/* } */

/* /1* bool IsFourOfAKind (Hand hand) *1/ */
/* /1* { *1/ */
/* /1*   // we have to check every combination of five cards from the seven *1/ */
/* /1*   lexicographical_combination_generator gen(7, 5); *1/ */
/* /1*   std::vector<Card> handComb; *1/ */
/* /1*   do *1/ */
/* /1*   { *1/ */
/* /1*     // make a combination vector *1/ */
/* /1*     for (size_t i = 0; i < gen.get_combination_size(); ++i) *1/ */
/* /1*     { *1/ */
/* /1*       auto iter = alphabet.begin(); *1/ */
/* /1*       std::advance(iter, gen.get_combination_index(i)); *1/ */
/* /1*       handComb.pushback(*iter); *1/ */
/* /1*     } *1/ */
/* /1*     // now we have handComb, and can do stuff with it *1/ */

/* /1*     // check for four of a kind *1/ */

/* /1*     handComb.clear(); // clear the hand for the next combination *1/ */
/* /1*   } while (gen.increment()); *1/ */
/* /1*   return false; *1/ */
/* /1* } *1/ */

/* bool IsFullHouse (const Hand& hand) */
/* { */
/*   std::vector<int> count = HandCount(hand); */
/*   if (count.back() == 3 && count[count.size() - 2] == 2) */
/*     return true; */
/*   if (count.back() == 3 && count[count.size() - 2] == 3) */
/*     return true; */
/*   return false; */
/* } */

/* bool IsFlush (const Hand& hand) */
/* { */
/*   // similar to HandCount but counts suit instead of faces */
/*   std::unordered_map<int, int> map; */
/*   size_t n = hand.GetHand().size(); */
/*   for (size_t i = 0; i < n; ++i) */
/*     ++map[hand.GetHand()[i].GetSuit()]; */
/*   std::unordered_map<int, int>::iterator mapIter; */
/*   std::vector<int> count; */
/*   for (mapIter = map.begin(); mapIter != map.end(); ++mapIter) */
/*     count.push_back(mapIter->second); */
/*   sort(count.begin(), count.end()); */
/*   return (count.back() >= 5); */
/* } */

/* bool IsStraight (const Hand& hand) */
/* { */
/*   std::vector<int> handVec; */
/*   bool isStraight = false; */

/*   for (size_t i = 0; i < hand.Size(); ++i) */
/*     handVec.push_back(hand.GetHand()[i].GetFace()); */

/*   // check cards 1-5, 2-6, and 3-7 (3 sets). rememeber that handVec is sorted */
/*   int card; */
/*   for (size_t i = 0; i < 3; ++i) */
/*   { */
/*   card = handVec[i]; */
/*     if (std::find(handVec.begin(), handVec.end(), card - 1) != handVec.end() && */
/*         std::find(handVec.begin(), handVec.end(), card - 2) != handVec.end() && */
/*         std::find(handVec.begin(), handVec.end(), card - 3) != handVec.end() && */
/*         std::find(handVec.begin(), handVec.end(), card - 4) != handVec.end()) */
/*       isStraight = true; */

/*     if (isStraight) return isStraight; */
/*   } */

/*   /1* // check cards 2 - 6 *1/ */
/*   /1* int card2 = hand.GetHand()[1].GetFace(); *1/ */
/*   /1* if (std::find(handVec.begin(), handVec.end(), *1/ */
/*   /1*       card2 - 1) != handVec.end() && *1/ */
/*   /1*     std::find(handVec.begin(), handVec.end(), *1/ */
/*   /1*       card2 - 2) != handVec.end() && *1/ */
/*   /1*     std::find(handVec.begin(), handVec.end(), *1/ */
/*   /1*       card2 - 3) != handVec.end() && *1/ */
/*   /1*     std::find(handVec.begin(), handVec.end(), *1/ */
/*   /1*       card2 - 4) != handVec.end()) *1/ */
/*   /1*   isStraight = true; *1/ */

/*   /1* if (isStraight) return isStraight; *1/ */

/*   /1* // check cards 3 - 7 *1/ */
/*   /1* int card3 = hand.GetHand()[2].GetFace(); *1/ */
/*   /1* if (std::find(handVec.begin(), handVec.end(), *1/ */
/*   /1*       card3 - 1) != handVec.end() && *1/ */
/*   /1*     std::find(handVec.begin(), handVec.end(), *1/ */
/*   /1*       card3 - 2) != handVec.end() && *1/ */
/*   /1*     std::find(handVec.begin(), handVec.end(), *1/ */
/*   /1*       card3 - 3) != handVec.end() && *1/ */
/*   /1*     std::find(handVec.begin(), handVec.end(), *1/ */
/*   /1*       card3 - 4) != handVec.end()) *1/ */
/*   /1*   isStraight = true; *1/ */

/*   return isStraight; */

/*   /1* // this isn't correct *1/ */
/*   /1* // *1/ */
/*   /1* // we could have pairs or sets *1/ */
/*   /1* // *1/ */
/*   /1* // *1/ */
/*   /1* bool straight = true; *1/ */
/*   /1* // check for A2345 *1/ */
  
  
/*   /1* // check cards 1 - 5 *1/ */
/*   /1* straight = true; *1/ */
/*   /1* for (size_t i = 0; i < 4; ++i) *1/ */
/*   /1* { *1/ */
/*   /1*   if (hand.GetHand()[i].GetFace() != hand.GetHand()[i+1].GetFace()) *1/ */
/*   /1*     straight = false; *1/ */
/*   /1* } *1/ */
/*   /1* if (straight == true) *1/ */
/*   /1*   return straight; *1/ */

/*   /1* // check cards 2 - 6 *1/ */
/*   /1* straight = true; *1/ */
/*   /1* for (size_t i = 1; i < 5; ++i) *1/ */
/*   /1* { *1/ */
/*   /1*   if (hand.GetHand()[i].GetFace() != hand.GetHand()[i+1].GetFace()) *1/ */
/*   /1*     straight = false; *1/ */
/*   /1* } *1/ */
/*   /1* if (straight == true) *1/ */
/*   /1*   return straight; *1/ */

/*   /1* // check cards 3 - 7 *1/ */
/*   /1* straight = true; *1/ */
/*   /1* for (size_t i = 2; i < 6; ++i) *1/ */
/*   /1* { *1/ */
/*   /1*   if (hand.GetHand()[i].GetFace() != hand.GetHand()[i+1].GetFace()) *1/ */
/*   /1*     straight = false; *1/ */
/*   /1* } *1/ */
/*   /1* return straight; *1/ */
/* } */

/* bool IsThreeOfAKind (const Hand& hand) */
/* { */
/*   std::vector<int> count = HandCount(hand); */
/*   return (count.back() == 3 && count.size() == 5); */
/* } */

/* bool IsTwoPairs (const Hand& hand) */
/* { */
/*   std::vector<int> count = HandCount(hand); */
/*   return (count.back() == 2 && count[count.size() - 2] == 2); */
/* } */

/* bool IsOnePair (const Hand& hand) */
/* { */
/*   std::vector<int> count = HandCount(hand); */
/*   return (count.back() == 2 && count.size() == 6); */
/* } */

/* bool IsHighCard (Hand hand) */
/* { */
/*   return (GetRank(hand) == HighCard); */
/* } */

/* Result GetWinnerHighCard (const Hand& hand1, const Hand& hand2) */
/* { */
/*   size_t n = hand1.Size(); */
/*   for (size_t i = 0; i < n; ++i) */
/*   { */
/*     if (hand1.GetHand()[i].GetFace() > hand2.GetHand()[i].GetFace()) */
/*       return Player1; */
/*     else if (hand1.GetHand()[i].GetFace() < hand2.GetHand()[i].GetFace()) */
/*       return Player2; */
/*   } */
/*   return Tie; */
/* } */

/* Result GetWinnerOnePair (const Hand& hand1, const Hand& hand2) */
/* { */
/*   std::vector<int> existHand1(13,0); */
/*   std::vector<int> existHand2(13,0); */
/*   size_t n = hand1.Size(); */

/*   for (size_t i = 0; i < n; ++i) */
/*   { */
/*     ++existHand1[hand1.GetHand()[i].GetFace() - 2];  // -2 offset as Ace = 14 */
/*     ++existHand2[hand2.GetHand()[i].GetFace() - 2];  //  and Two = 2. */
/*   } */

/*   int hand1PairCard = 0; */
/*   int hand2PairCard = 0; */
/*   int hand1HighCard1 = 0; */
/*   int hand2HighCard1 = 0; */
/*   int hand1HighCard2 = 0; */
/*   int hand2HighCard2 = 0; */
/*   int hand1HighCard3 = 0; */
/*   int hand2HighCard3 = 0; */
/*   int hand1HighCard4 = 0; */
/*   int hand2HighCard4 = 0; */
/*   int hand1HighCard5 = 0; */
/*   int hand2HighCard5 = 0; */

/*   for (size_t i = 0; i < 13; ++i) */
/*   { */
/*     if (existHand1[i] == 2) hand1PairCard = i + 2;  // add back the offset so we */
/*     if (existHand2[i] == 2) hand2PairCard = i + 2;  // don't have problems with */
/*     if (existHand1[i] == 1)                         // i = 0 */
/*     { */
/*       if      (hand1HighCard1 == 0) hand1HighCard1 = i + 2; */
/*       else if (hand1HighCard2 == 0) hand1HighCard2 = i + 2; */
/*       else if (hand1HighCard3 == 0) hand1HighCard3 = i + 2; */
/*       else if (hand1HighCard4 == 0) hand1HighCard4 = i + 2; */
/*       else    hand1HighCard5 = i + 2; */
/*     } */
/*     if (existHand2[i] == 1) */
/*     { */
/*       if      (hand2HighCard1 == 0) hand2HighCard1 = i + 2; */
/*       else if (hand2HighCard2 == 0) hand2HighCard2 = i + 2; */
/*       else if (hand2HighCard3 == 0) hand2HighCard3 = i + 2; */
/*       else if (hand2HighCard4 == 0) hand2HighCard4 = i + 2; */
/*       else    hand2HighCard5 = i + 2; */
/*     } */
/*   } */

/*   if      (hand1PairCard > hand2PairCard)   return Player1; */
/*   else if (hand1PairCard < hand2PairCard)   return Player2; */
/*   else if (hand1HighCard5 > hand2HighCard5) return Player1; */
/*   else if (hand1HighCard5 < hand2HighCard5) return Player2; */
/*   else if (hand1HighCard4 > hand2HighCard4) return Player1; */
/*   else if (hand1HighCard4 < hand2HighCard4) return Player2; */
/*   else if (hand1HighCard3 > hand2HighCard3) return Player1; */
/*   else if (hand1HighCard3 < hand2HighCard3) return Player2; */
/*   /1* else if (hand1HighCard2 > hand2HighCard2) return Player1; *1/ */
/*   /1* else if (hand1HighCard2 < hand2HighCard2) return Player2; *1/ */
/*   /1* else if (hand1HighCard1 > hand2HighCard1) return Player1; *1/ */
/*   /1* else if (hand1HighCard1 < hand2HighCard1) return Player2; *1/ */
/*   else    return Tie; */
/* } */

/* Result GetWinnerTwoPairs (const Hand& hand1, const Hand& hand2) */
/* { */
/*   std::vector<int> existHand1(13,0); */
/*   std::vector<int> existHand2(13,0); */
/*   size_t n = hand1.Size(); */

/*   for (size_t i = 0; i < n; ++i) */
/*   { */
/*     ++existHand1[hand1.GetHand()[i].GetFace() - 2];  // -2 offset as Ace = 14 */
/*     ++existHand2[hand2.GetHand()[i].GetFace() - 2];  //  and Two = 2. */
/*   } */

/*   int hand1PairCard1 = 0;  // we could have up to three pairs */
/*   int hand1PairCard2 = 0; */
/*   int hand1PairCard3 = 0; */
/*   int hand1HighCard1 = 0;  // we could have up to three high cards */
/*   int hand1HighCard2 = 0; */
/*   int hand1HighCard3 = 0; */
/*   int hand2PairCard1 = 0;  // hand2 */
/*   int hand2PairCard2 = 0; */
/*   int hand2PairCard3 = 0; */
/*   int hand2HighCard1 = 0; */
/*   int hand2HighCard2 = 0; */
/*   int hand2HighCard3 = 0; */

/*   for (size_t i = 0; i < 13; ++i) */
/*   { */
/*     // hand 1: pairs */
/*     if (existHand1[i] == 2) */
/*     { */
/*       if      (hand1PairCard1 == 0) hand1PairCard1 = i + 2; */
/*       else if (hand1PairCard2 == 0) hand1PairCard2 = i + 2; */
/*       else    hand1PairCard3 = i + 2; */
/*     } */
/*     // hand1: high cards */
/*     if (existHand1[i] == 1) */
/*     { */
/*       if      (hand1HighCard1 == 0) hand1HighCard1 = i + 2; */
/*       else if (hand1HighCard2 == 0) hand1HighCard2 = i + 2; */
/*       else    hand1HighCard3 = i + 2; */
/*     } */

/*     // hand 2: pairs */
/*     if (existHand2[i] == 2) */
/*     { */
/*       if      (hand2PairCard1 == 0) hand2PairCard1 = i + 2; */
/*       else if (hand2PairCard2 == 0) hand2PairCard2 = i + 2; */
/*       else    hand2PairCard3 = i + 2; */
/*     } */
/*     // hand 2: high cards */
/*     if (existHand1[i] == 1) */
/*     { */
/*       if      (hand2HighCard1 == 0) hand2HighCard1 = i + 2; */
/*       else if (hand2HighCard2 == 0) hand2HighCard2 = i + 2; */
/*       else    hand2HighCard3 = i + 2; */
/*     } */
/*   } */

/*   /1* if (std::max(hand1PairCard2, hand1PairCard3) > *1/ */
/*   /1*     std::max(hand2PairCard2, hand2PairCard3)) *1/ */
/*   /1*   return Player1; *1/ */
/*   /1* else if (std::max(hand1PairCard2, hand1PairCard3) < *1/ */
/*   /1*          std::max(hand2PairCard2, hand2PairCard3)) *1/ */
/*   /1*   return Player2; *1/ */
/*   /1* // else the top pair of each hand are equal, so we check the second pair *1/ */

/*   std::vector<int> hand1PairVec(3); */
/*   std::vector<int> hand2PairVec(3); */
/*   hand1PairVec.push_back(hand1PairCard1); */
/*   hand1PairVec.push_back(hand1PairCard2); */
/*   hand1PairVec.push_back(hand1PairCard3); */
/*   hand2PairVec.push_back(hand2PairCard1); */
/*   hand2PairVec.push_back(hand2PairCard2); */
/*   hand2PairVec.push_back(hand2PairCard3); */

/*   sort(hand1PairVec.begin(), hand1PairVec.end()); */
/*   reverse(hand1PairVec.begin(), hand1PairVec.end()); */
/*   sort(hand2PairVec.begin(), hand2PairVec.end()); */
/*   reverse(hand2PairVec.begin(), hand2PairVec.end()); */

/*   if      (hand1PairVec[0] > hand2PairVec[0]) return Player1; // check top pairs */
/*   else if (hand1PairVec[0] < hand2PairVec[0]) return Player2; */
/*   else if (hand1PairVec[1] > hand2PairVec[1]) return Player1; // check next pair */
/*   else if (hand1PairVec[1] < hand2PairVec[1]) return Player2; */

/*   // the two pairs are equal, so we check the high cards */
/*   std::vector<int> hand1HighVec(4); */
/*   std::vector<int> hand2HighVec(4); */
/*   hand1HighVec.push_back(hand1PairVec[2]);  // push left over pair (if any) */
/*   hand2HighVec.push_back(hand2PairVec[2]); */
/*   hand1HighVec.push_back(hand1HighCard1); */
/*   hand1HighVec.push_back(hand1HighCard2); */
/*   hand1HighVec.push_back(hand1HighCard3); */
/*   hand2HighVec.push_back(hand2HighCard1); */
/*   hand2HighVec.push_back(hand2HighCard2); */
/*   hand2HighVec.push_back(hand2HighCard3); */

/*   sort(hand1HighVec.begin(), hand1HighVec.end()); */
/*   reverse(hand1HighVec.begin(), hand1HighVec.end()); */
/*   sort(hand2HighVec.begin(), hand2HighVec.end()); */
/*   reverse(hand2HighVec.begin(), hand2HighVec.end()); */

/*   if      (hand1HighVec[0] > hand2HighVec[0]) return Player1; */
/*   else if (hand1HighVec[0] < hand2HighVec[0]) return Player2; */
/*   else    return Tie; */
/* } */

/* Result GetWinnerThreeOfAKind (const Hand& hand1, const Hand& hand2) */
/* { */
/*   std::vector<int> existHand1(13,0); */
/*   std::vector<int> existHand2(13,0); */
/*   size_t n = hand1.Size(); */

/*   for (size_t i = 0; i < n; ++i) */
/*   { */
/*     ++existHand1[hand1.GetHand()[i].GetFace() - 2];  // -2 offset as Ace = 14 */
/*     ++existHand2[hand2.GetHand()[i].GetFace() - 2];  //  and Two = 2. */
/*   } */

/*   int hand1SetCard = 0; */
/*   int hand2SetCard = 0; */
/*   int hand1HighCard1 = 0; */
/*   int hand2HighCard1 = 0; */
/*   int hand1HighCard2 = 0; */
/*   int hand2HighCard2 = 0; */
/*   int hand1HighCard3 = 0; */
/*   int hand2HighCard3 = 0; */
/*   int hand1HighCard4 = 0; */
/*   int hand2HighCard4 = 0; */

/*   for (size_t i = 0; i < 13; ++i) */
/*   { */
/*     if (existHand1[i] == 3) hand1SetCard = i + 2;  // add back the offset so we */
/*     if (existHand2[i] == 3) hand2SetCard = i + 2;  // don't have problems with */
/*     if (existHand1[i] == 1)                        // i = 0 */
/*     { */
/*       if      (hand1HighCard1 == 0) hand1HighCard1 = i + 2; */
/*       else if (hand1HighCard2 == 0) hand1HighCard2 = i + 2; */
/*       else if (hand1HighCard3 == 0) hand1HighCard3 = i + 2; */
/*       else    hand1HighCard4 = i + 2; */
/*     } */
/*     if (existHand2[i] == 1) */
/*     { */
/*       if      (hand2HighCard1 == 0) hand2HighCard1 = i + 2; */
/*       else if (hand2HighCard2 == 0) hand2HighCard2 = i + 2; */
/*       else if (hand2HighCard3 == 0) hand2HighCard3 = i + 2; */
/*       else    hand2HighCard4 = i + 2; */
/*     } */
/*   } */

/*   if      (hand1SetCard > hand2SetCard)     return Player1; */
/*   else if (hand1SetCard < hand2SetCard)     return Player2; */
/*   else if (hand1HighCard4 > hand2HighCard4) return Player1; */
/*   else if (hand1HighCard4 < hand2HighCard4) return Player2; */
/*   else if (hand1HighCard3 > hand2HighCard3) return Player1; */
/*   else if (hand1HighCard3 < hand2HighCard3) return Player2; */
/*   /1* else if (hand1HighCard2 > hand2HighCard2) return Player1; *1/ */
/*   /1* else if (hand1HighCard2 < hand2HighCard2) return Player2; *1/ */
/*   /1* else if (hand1HighCard1 > hand2HighCard1) return Player1; *1/ */
/*   /1* else if (hand1HighCard1 < hand2HighCard1) return Player2; *1/ */
/*   else    return Tie; */
/* } */

/* Result GetWinnerStraight (const Hand& hand1, const Hand& hand2) */
/* { */
/*   int hand1Highest = 0; */
/*   int hand2Highest = 0; */
/*   std::vector<int> hand1Vec; */
/*   std::vector<int> hand2Vec; */

/*   for (size_t i = 0; i < hand1.Size(); ++i) */
/*   { */
/*     hand1Vec.push_back(hand1.GetHand()[i].GetFace()); */
/*     hand2Vec.push_back(hand2.GetHand()[i].GetFace()); */
/*   } */

/*   // hand 1 */
/*   // check cards 1 - 5 */
/*   int card1 = hand1.GetHand()[0].GetFace(); */
/*   if (std::find(hand1Vec.begin(), hand1Vec.end(), */
/*         card1 - 1) != hand1Vec.end() && */
/*       std::find(hand1Vec.begin(), hand1Vec.end(), */
/*         card1 - 2) != hand1Vec.end() && */
/*       std::find(hand1Vec.begin(), hand1Vec.end(), */
/*         card1 - 3) != hand1Vec.end() && */
/*       std::find(hand1Vec.begin(), hand1Vec.end(), */
/*         card1 - 4) != hand1Vec.end()) */
/*     hand1Highest = card1; */

/*   // check cards 2 - 6 */
/*   int card2 = hand1.GetHand()[1].GetFace(); */
/*   if (std::find(hand1Vec.begin(), hand1Vec.end(), */
/*         card2 - 1) != hand1Vec.end() && */
/*       std::find(hand1Vec.begin(), hand1Vec.end(), */
/*         card2 - 2) != hand1Vec.end() && */
/*       std::find(hand1Vec.begin(), hand1Vec.end(), */
/*         card2 - 3) != hand1Vec.end() && */
/*       std::find(hand1Vec.begin(), hand1Vec.end(), */
/*         card2 - 4) != hand1Vec.end()) */
/*     hand1Highest = card2; */

/*   // check cards 3 - 7 */
/*   int card3 = hand1.GetHand()[2].GetFace(); */
/*   if (std::find(hand1Vec.begin(), hand1Vec.end(), */
/*         card3 - 1) != hand1Vec.end() && */
/*       std::find(hand1Vec.begin(), hand1Vec.end(), */
/*         card3 - 2) != hand1Vec.end() && */
/*       std::find(hand1Vec.begin(), hand1Vec.end(), */
/*         card3 - 3) != hand1Vec.end() && */
/*       std::find(hand1Vec.begin(), hand1Vec.end(), */
/*         card3 - 4) != hand1Vec.end()) */
/*     hand1Highest = card3; */

/*   // hand 2 */
/*   // check cards 1 - 5 */
/*   card1 = hand2.GetHand()[0].GetFace(); */
/*   if (std::find(hand2Vec.begin(), hand2Vec.end(), */
/*         card1 - 1) != hand2Vec.end() && */
/*       std::find(hand2Vec.begin(), hand2Vec.end(), */
/*         card1 - 2) != hand2Vec.end() && */
/*       std::find(hand2Vec.begin(), hand2Vec.end(), */
/*         card1 - 3) != hand2Vec.end() && */
/*       std::find(hand2Vec.begin(), hand2Vec.end(), */
/*         card1 - 4) != hand2Vec.end()) */
/*     hand2Highest = card1; */

/*   // check cards 2 - 6 */
/*   card2 = hand2.GetHand()[1].GetFace(); */
/*   if (std::find(hand2Vec.begin(), hand2Vec.end(), */
/*         card2 - 1) != hand2Vec.end() && */
/*       std::find(hand2Vec.begin(), hand2Vec.end(), */
/*         card2 - 2) != hand2Vec.end() && */
/*       std::find(hand2Vec.begin(), hand2Vec.end(), */
/*         card2 - 3) != hand2Vec.end() && */
/*       std::find(hand2Vec.begin(), hand2Vec.end(), */
/*         card2 - 4) != hand2Vec.end()) */
/*     hand2Highest = card2; */

/*   // check cards 3 - 7 */
/*   card3 = hand2.GetHand()[2].GetFace(); */
/*   if (std::find(hand2Vec.begin(), hand2Vec.end(), */
/*         card3 - 1) != hand2Vec.end() && */
/*       std::find(hand2Vec.begin(), hand2Vec.end(), */
/*         card3 - 2) != hand2Vec.end() && */
/*       std::find(hand2Vec.begin(), hand2Vec.end(), */
/*         card3 - 3) != hand2Vec.end() && */
/*       std::find(hand2Vec.begin(), hand2Vec.end(), */
/*         card3 - 4) != hand2Vec.end()) */
/*     hand2Highest = card3; */

/*   if      (hand1Highest > hand2Highest) return Player1; */
/*   else if (hand1Highest < hand2Highest) return Player2; */
/*   else    return Tie; */
/* } */

/* Result GetWinnerFlush (const Hand& hand1, const Hand& hand2) */
/*   // i think this is wrong. double check */
/* { */
/*   size_t n = hand1.Size(); */
/*   std::vector<int> hand1SuitVec(4); */
/*   std::vector<int> hand2SuitVec(4); */

/*   for (size_t i = 0; i < 4; ++i)  // loop over suits */
/*   { */
/*     for (size_t j = 0; j < n; ++j) */
/*     { */
/*       ++hand1SuitVec[hand1.GetHand()[i].GetSuit()]; */
/*       ++hand2SuitVec[hand2.GetHand()[i].GetSuit()]; */
/*     } */
/*   } */

/*   // find the flush suit: */
/*   // first find the max element of the suit vectors */
/*   std::vector<int>::iterator suitIter1 = std::max_element (hand1SuitVec.begin(), */
/*                                                            hand1SuitVec.end()); */
/*   std::vector<int>::iterator suitIter2 = std::max_element (hand2SuitVec.begin(), */
/*                                                            hand2SuitVec.end()); */
/*   // we already know that these will contain a flush */
/*   // next, find the position of the max element. this is the flush suit of the */
/*   // corresponding hand. note that this will always be the same */
/*   int suitHand1 = std::distance(hand1SuitVec.begin(), suitIter1); */
/*   int suitHand2 = std::distance(hand2SuitVec.begin(), suitIter2); */

/*   hand1SuitVec.clear(); */
/*   hand2SuitVec.clear(); */
/*   for (size_t i = 0; i < n; ++i) */
/*   { */
/*     if (hand1.GetHand()[i].GetSuit() == suitHand1) */
/*       hand1SuitVec.push_back(hand1.GetHand()[i].GetFace()); */
/*     if (hand2.GetHand()[i].GetSuit() == suitHand2) */
/*       hand2SuitVec.push_back(hand2.GetHand()[i].GetFace()); */
/*   } */
/*   // sort and reverse to the largest elements are at the front */
/*   sort(hand1SuitVec.begin(), hand1SuitVec.end()); */
/*   sort(hand2SuitVec.begin(), hand2SuitVec.end()); */
/*   reverse(hand1SuitVec.begin(), hand1SuitVec.end()); */
/*   reverse(hand2SuitVec.begin(), hand2SuitVec.end()); */
/*   // now check the elements of this vector from largest (first) to smallest */
/*   // (last). */
/*   suitIter1 = hand1SuitVec.begin(); */
/*   suitIter2 = hand2SuitVec.begin(); */

/*   while (suitIter1 != hand1SuitVec.end() && suitIter2 != hand2SuitVec.end()) */
/*   { */
/*     if      (*suitIter1 > *suitIter2) return Player1; */
/*     else if (*suitIter1 < *suitIter2) return Player2; */
/*     ++suitIter1; */
/*     ++suitIter2; */
/*   } */
/*   return Tie; */
/* } */

/* Result GetWinnerFullHouse (const Hand& hand1, const Hand& hand2) */
/* { */
/*   std::vector<int> existHand1(13,0); */
/*   std::vector<int> existHand2(13,0); */
/*   size_t n = hand1.Size(); */

/*   for (size_t i = 0; i < n; ++i) */
/*   { */
/*     ++existHand1[hand1.GetHand()[i].GetFace() - 2];  // -2 offset as Ace = 14 */
/*     ++existHand2[hand2.GetHand()[i].GetFace() - 2];  // and Two = 2. */
/*   } */

/*   int hand1SetCard1 = 0;  // we could have two sets */
/*   int hand1SetCard2 = 0; */
/*   int hand2SetCard1 = 0; */
/*   int hand2SetCard2 = 0; */
/*   int hand1PairCard1 = 0;  // we coud have two pairs */
/*   int hand1PairCard2 = 0; */
/*   int hand2PairCard1 = 0; */
/*   int hand2PairCard2 = 0; */

/*   for (size_t i = 0; i < 13; ++i) */
/*   { */
/*     if (existHand1[i] == 3) */
/*     { */
/*       if   (hand1SetCard1 == 0) hand1SetCard1 = i + 2; */
/*       else hand1SetCard2 = i + 2; */
/*     } */
/*     if (existHand1[i] == 2) */
/*     { */
/*       if   (hand1PairCard1 == 0) hand1PairCard1 = i + 2; */
/*       else hand1PairCard2 = i + 2; */
/*     } */

/*     if (existHand2[i] == 3) */
/*     { */
/*       if   (hand2SetCard1 == 0) hand2SetCard1 = i + 2; */
/*       else hand2SetCard2 = i + 2; */
/*     } */
/*     if (existHand2[i] == 2) */
/*     { */
/*       if   (hand2PairCard1 == 0) hand2PairCard1 = i + 2; */
/*       else hand2PairCard2 = i + 2; */
/*     } */
/*   } */

/*   if (std::max(hand1SetCard1, hand1SetCard2) > */
/*       std::max(hand2SetCard1, hand2SetCard2)) */
/*     return Player1; */
/*   else if (std::max(hand1SetCard1, hand1SetCard2) < */
/*            std::max(hand2SetCard1, hand2SetCard2)) */
/*     return Player2; */
/*   // else the top set of both hands is equal and we check the pairs */

/*   // if there are two sets, get the small one (as the large ones are equal) */
/*   int minPairHand1Set = std::min(hand1SetCard1, hand1SetCard2); */
/*   int minPairHand2Set = std::min(hand2SetCard1, hand2SetCard2); */
/*   // if there are two pairs, get the largest */
/*   int maxPairHand1Pair = std::max(hand1PairCard1, hand1PairCard2); */
/*   int maxPairHand2Pair = std::max(hand2PairCard1, hand2PairCard2); */

/*   // now get the largest or these */
/*   if (std::max(minPairHand1Set, maxPairHand1Pair) > */
/*       std::max(minPairHand2Set, maxPairHand2Pair)) */
/*     return Player1; */
/*   else if (std::max(minPairHand1Set, maxPairHand1Pair) < */
/*            std::max(minPairHand2Set, maxPairHand2Pair)) */
/*     return Player2; */
/*   else */
/*     return Tie; */
/* } */

/* Result GetWinnerFourOfAKind (const Hand& hand1, const Hand& hand2) */
/* { */
/*   std::vector<int> existHand1(13,0); */
/*   std::vector<int> existHand2(13,0); */
/*   size_t n = hand1.Size(); */

/*   for (size_t i = 0; i < n; ++i) */
/*   { */
/*     ++existHand1[hand1.GetHand()[i].GetFace() - 2];  // -2 offset as Ace = 14 */
/*     ++existHand2[hand2.GetHand()[i].GetFace() - 2];  //  and Two = 2. */
/*   } */

/*   int hand1QuadCard = 0; */
/*   int hand2QuadCard = 0; */
/*   int hand1HighCard1 = 0; */
/*   int hand2HighCard1 = 0; */
/*   int hand1HighCard2 = 0; */
/*   int hand2HighCard2 = 0; */
/*   int hand1HighCard3 = 0; */
/*   int hand2HighCard3 = 0; */

/*   for (size_t i = 0; i < 13; ++i) */
/*   { */
/*     if (existHand1[i] == 4) hand1QuadCard = i + 2; */
/*     else if (existHand1[i] != 4 && existHand1[i] != 0) */
/*     { */
/*       if      (hand1HighCard1 == 0) hand1HighCard1 = i + 2; */
/*       else if (hand1HighCard2 == 0) hand1HighCard2 = i + 2; */
/*       else    hand1HighCard3 = i + 2; */
/*     } */

/*     if (existHand2[i] == 4) hand2QuadCard = i + 2; */
/*     else if (existHand2[i] != 4 && existHand2[i] != 0) */
/*     { */
/*       if      (hand2HighCard1 == 0) hand2HighCard1 = i + 2; */
/*       else if (hand2HighCard2 == 0) hand2HighCard2 = i + 2; */
/*       else    hand2HighCard3 = i + 2; */
/*     } */
/*   } */

/*   if      (hand1QuadCard > hand2QuadCard)   return Player1; */
/*   else if (hand1QuadCard < hand2QuadCard)   return Player2; */
/*   else if (hand1HighCard3 > hand2HighCard3) return Player1; */
/*   else if (hand1HighCard3 < hand2HighCard3) return Player2; */
/*   else    return Tie; */
/* } */

/* Result GetWinnerStraightFlush (const Hand& hand1, const Hand& hand2) */
/* { */
/*   // we already know the hands both has flushes, so we only need to check which */
/*   // has the highest straight */
/*   return GetWinnerStraight (hand1, hand2); */
/* } */

/* Result GetWinnerRoyalFlush (__attribute__((unused)) const Hand& hand1, */
/*                             __attribute__((unused)) const Hand& hand2) */
/* { */
/*   return Tie; */
/* } */

