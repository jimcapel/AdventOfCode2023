#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int getLineTotal(string *currentLine, string *previousLine, string *penultimateLine)
{
    int lineTotal = 0;
    string number;

    bool symbol;

    if (!(*previousLine).empty())
    {
        for (int i = 0; i < (*previousLine).length(); i++)
        {
            //  get ascii values for each char in all lines
            char currentChar = (*currentLine)[i];
            int currentCharAscii = int(currentChar);

            char previousChar = (*previousLine)[i];
            int previousCharAscii = int(previousChar);

            char penultimateChar = (*penultimateLine)[i];
            int penultimateCharAscii = int(penultimateChar);

            //  get vars for if chars are a certain type
            bool isPreviousCharNumber = previousCharAscii >= 0x30 && previousCharAscii <= 0x39;
            bool isPreviousCharSymbol = (previousCharAscii < 0x30 || previousCharAscii > 0x39) && previousCharAscii != 0x2E & previousCharAscii != 0;

            bool isCurrentCharSymbol = (currentCharAscii < 0x30 || currentCharAscii > 0x39) && currentCharAscii != 0x2E && currentCharAscii != 0;
            bool isPenultimateCharSymbol = (penultimateCharAscii < 0x30 || penultimateCharAscii > 0x39) && penultimateCharAscii != 0x2E && penultimateCharAscii != 0;

            bool symbolPresent = isPenultimateCharSymbol || isPreviousCharSymbol || isCurrentCharSymbol;

            if (isPreviousCharNumber)
            {
                number += previousChar;
            }

            if (symbolPresent)
            {
                symbol = true;
            }

            //  if we are at the end of a number, check if that number should be added to total
            if ((!isPreviousCharSymbol && !isPreviousCharNumber) || i == ((*currentLine).length() - 1) || isPreviousCharSymbol)
            {
                if (!number.empty() && symbol)
                {
                    std::cout << number << endl;
                    lineTotal += stoi(number);
                }

                symbol = false;
                number = "";
            }

            if (symbolPresent)
            {
                symbol = true;
            }
        }
    }

    *penultimateLine = *previousLine;
    *previousLine = *currentLine;

    return lineTotal;
}

int main()
{
    fstream file;
    file.open("./inputTest.txt", ios::in);

    int total = 0;

    if (file.is_open())
    {
        string current;
        string previous;
        string penultimate;

        while (getline(file, current))
        {
            int lineTotal = getLineTotal(&current, &previous, &penultimate);

            total += lineTotal;
        }

        current = "";

        if (!previous.empty())
        {
            int lastLineTotal = getLineTotal(&current, &previous, &penultimate);

            total += lastLineTotal;
        }
    }
    file.close();

    std::cout << total << endl;

    return 0;
}
