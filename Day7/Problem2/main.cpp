#include <fstream>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum handType
{
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    FullHouse,
    FourOfAKind,
    FiveOfAKind,
};

struct Card
{
    string hand;
    int bid;
    enum handType type;
};

int cardToIntValue(char card)
{
    switch (card)
    {
    case 'J':
        return 0;
    case '2':
        return 1;
    case '3':
        return 2;
    case '4':
        return 3;
    case '5':
        return 4;
    case '6':
        return 5;
    case '7':
        return 6;
    case '8':
        return 7;
    case '9':
        return 8;
    case 'T':
        return 9;
    case 'Q':
        return 10;
    case 'K':
        return 11;
    // if 'A'
    default:
        return 12;
    }
}

bool doesBeatCard(Card cardOne, Card cardTwo)
{
    if (cardOne.type > cardTwo.type)
    {
        return true;
    }

    if (cardOne.type < cardTwo.type)
    {
        return false;
    }

    for (int i = 0; i < cardOne.hand.length(); i++)
    {
        int a = cardToIntValue(cardOne.hand[i]);
        int b = cardToIntValue(cardTwo.hand[i]);

        if (a > b)
        {
            return true;
        }

        if (a < b)
        {
            return false;
        }
    }

    return true;
}

handType getType(string hand)
{
    int numberOfPairs = 0;
    int numberOfSoloCards = 0;
    bool threeMatching = false;

    vector<char> keys;

    map<char, int> cardCount;

    for (int i = 0; i < hand.length(); i++)
    {
        int n = std::count(hand.begin() + i, hand.end(), hand[i]);

        if (cardCount.count(hand[i]))
        {
            cardCount[hand[i]] += 1;
        }
        else
        {
            cardCount[hand[i]] = 1;

            if (hand[i] != 'J')
            {
                keys.push_back(hand[i]);
            }
        }

        // cout << n << ": " << hand[i] << endl;
    }

    int jokerCount = cardCount.count('J') ? cardCount['J'] : 0;

    for (int i = 0; i < keys.size(); i++)
    {

        int numberOfCards = cardCount[keys[i]];

        if (numberOfCards + jokerCount == 5)
        {
            return FiveOfAKind;
        }

        if (numberOfCards + jokerCount == 4)
        {
            return FourOfAKind;
        }

        if (numberOfCards + jokerCount == 3)
        {
            return FullHouse;
        }

        if (numberOfCards == 3)

            if (numberOfCards == 2)
            {

                numberOfPairs++;
            }

        if (numberOfCards == 1)
        {
            numberOfSoloCards++;
        }
    }

    if (threeMatching && numberOfPairs == 1)
    {
        return FullHouse;
    }

    if (threeMatching && numberOfPairs == 0)
    {
        return ThreeOfAKind;
    }

    if (numberOfPairs == 2)
    {
        return TwoPair;
    }

    if (numberOfPairs == 1)
    {
        return OnePair;
    }

    return HighCard;
}

int main()
{
    fstream file;
    file.open("../inputTest2.txt", ios::in);

    vector<Card> cards;

    if (file.is_open())
    {
        string current;

        while (getline(file, current))
        {
            int spaceIndex = current.find(" ");
            string currentHand = current.substr(0, spaceIndex);
            string currentRank = current.substr(spaceIndex + 1);

            Card card;

            card.hand = currentHand;
            card.bid = stoi(currentRank);
            card.type = getType(currentHand);

            if (cards.empty())
            {
                cards.push_back(card);
            }
            else
            {
                bool inserted = false;
                for (int i = 0; i < cards.size(); i++)
                {
                    if (!doesBeatCard(card, cards[i]))
                    {
                        cards.insert(cards.begin() + i, card);
                        inserted = true;
                        break;
                    }
                }

                if (!inserted)
                {
                    cards.push_back(card);
                }
            }
        }
    }

    file.close();

    int total = 0;

    for (int i = 0; i < cards.size(); i++)
    {
        // cout << c.hand << " " << c.bid << " " << c.type << endl;
        cout << cards[i].hand << " " << cards[i].bid << endl;
        total += (cards[i].bid * (i + 1));
    }

    cout << total << endl;

    return 0;
}
