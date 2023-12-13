#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

int main()
{
    fstream file;
    file.open("../input.txt", ios::in);

    vector<long long> numbers;
    vector<long long> numbersThatHaveBeenConverted;

    vector<long long> converted;

    long long destinationStart = -1;
    long long sourceStart = -1;
    long long range = -1;

    if (file.is_open())
    {
        string current;
        int lineIndex = 0;

        bool lineBreak = false;

        while (getline(file, current))
        {
            string number;

            destinationStart = -1;
            sourceStart = -1;
            range = -1;

            if (current.empty())
            {
                lineIndex++;
                lineBreak = true;
                continue;
            }

            if (lineBreak)
            {

                if (!numbers.empty())
                {

                    for (long long x : numbers)
                    {
                        if (std::find(numbersThatHaveBeenConverted.begin(), numbersThatHaveBeenConverted.end(), x) == numbersThatHaveBeenConverted.end())
                        {
                            converted.push_back(x);
                        }
                    }

                    numbers = converted;
                    converted = {};
                    numbersThatHaveBeenConverted = {};
                }
                lineIndex++;
                lineBreak = false;
                continue;
            }

            for (int i = 0; i < current.length(); i++)
            {

                int asciiValue = int(char(current[i]));

                //  get the numbers to convert and store them in a vec

                if (asciiValue >= 0x30 && asciiValue <= 0x39)
                {
                    number += char(asciiValue);
                }

                if ((asciiValue == 0x20 || i == (current.length() - 1)) && !number.empty())
                {
                    if (lineIndex == 0)
                    {
                        numbers.push_back(stoll(number));
                    }
                    else
                    {
                        if (destinationStart == -1)
                        {
                            destinationStart = stoll(number);
                        }
                        else if (sourceStart == -1)
                        {
                            sourceStart = stoll(number);
                        }
                        else
                        {
                            range = stoll(number);
                        }
                    }

                    number = "";
                }
            }

            if (lineIndex == 0)
            {
                lineIndex++;
                continue;
            }

            long long destinationEnd = destinationStart + range - 1;
            long long sourceEnd = sourceStart + range - 1;

            for (long long x : numbers)
            {
                if (x >= sourceStart && x <= sourceEnd)
                {
                    long long difference = sourceEnd - x;
                    converted.push_back(destinationEnd - difference);
                    numbersThatHaveBeenConverted.push_back(x);
                }
            }

            lineIndex++;
        }
    }

    long long destinationEnd = destinationStart + range - 1;
    long long sourceEnd = sourceStart + range - 1;

    for (long long x : numbers)
    {
        if (x >= sourceStart && x <= sourceEnd)
        {
            long long difference = sourceEnd - x;
            converted.push_back(destinationEnd - difference);
            numbersThatHaveBeenConverted.push_back(x);
        }
    }

    for (long long x : numbers)
    {
        if (std::find(numbersThatHaveBeenConverted.begin(), numbersThatHaveBeenConverted.end(), x) == numbersThatHaveBeenConverted.end())
        {
            converted.push_back(x);
        }
    }

    numbers = converted;

    long long min = std::numeric_limits<long long int>::max();

    for (long long x : numbers)
    {
        if (x < min)
        {
            min = x;
        }
    }

    cout << min << endl;

    file.close();

    return 0;
}
