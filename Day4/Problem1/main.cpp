#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    fstream file;
    file.open("../input.txt", ios::in);

    int total = 0;

    if (file.is_open())
    {
        string current;

        while (getline(file, current))
        {

            int cardTotal = 0;

            string number;

            vector<int> winningNumbers;
            vector<int> elfsNumbers;

            bool gameString = false;
            bool elfString = false;

            for (int i = 0; i < current.length(); i++)
            {
                if (current[i - 1] == 0x3A)
                {
                    gameString = true;
                }

                if (!gameString)
                {
                    continue;
                }

                int asciiValue = int(char(current[i]));

                if (asciiValue >= 0x30 && asciiValue <= 0x39)
                {
                    number += char(asciiValue);
                }

                if ((asciiValue == 0x20 || i == (current.length() - 1)) && !number.empty())
                {
                    if (!elfString)
                    {
                        winningNumbers.push_back(stoi(number));
                    }
                    else
                    {
                        elfsNumbers.push_back(stoi(number));
                    }

                    number = "";
                }

                if (asciiValue == 0x7C)
                {
                    elfString = true;
                }
            }

            for (int x : elfsNumbers)
            {
                if (std::count(winningNumbers.begin(), winningNumbers.end(), x))
                {
                    cardTotal = cardTotal == 0 ? 1 : cardTotal * 2;
                }
            }

            total += cardTotal;
        }
    }

    file.close();

    std::cout << total << endl;

    return 0;
}