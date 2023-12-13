#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct Point
{
    int x;
    int y;
};

struct PartNumber
{
    Point startIndex;
    Point endIndex;
    int value;
};

int main()
{
    fstream file;
    file.open("../inputTest2.txt", ios::in);

    int total = 0;

    vector<PartNumber> partNumbers;
    vector<Point> symbols;

    if (file.is_open())
    {
        string current;
        string number;

        int lineNumber = 0;

        while (getline(file, current))
        {
            Point start;
            start.x = -1;
            start.y = -1;

            Point end;
            end.x = -1;
            end.y = -1;

            Point symbol;

            for (int i = 0; i < current.length(); i++)
            {
                int asciiValue = int(char(current[i]));

                if (asciiValue >= 0x30 && asciiValue <= 0x39)
                {
                    if (start.x == -1)
                    {
                        start.x = i;
                        start.y = lineNumber;
                    }

                    number += char(asciiValue);
                }
                else if (((asciiValue < 0x30 || asciiValue > 0x39) || i == (current.length() - 1)) && !number.empty())
                {

                    end.x = i;
                    end.y = lineNumber;

                    PartNumber partNumber;

                    partNumber.startIndex = start;
                    partNumber.endIndex = end;
                    partNumber.value = stoi(number);

                    partNumbers.push_back(partNumber);

                    number = "";
                    start.x = -1;
                    start.y = -1;
                    end.x = -1;
                    end.y = -1;
                }
                else if (asciiValue != 0x2E)
                {
                    //  we have a symbol
                    symbol.x = i;
                    symbol.y = lineNumber;

                    symbols.push_back(symbol);
                }
            }

            lineNumber++;
        }
    }

    // for (PartNumber x : partNumbers)
    // {
    //     cout << x.value << " start: (" << x.startIndex.x << ", " << x.startIndex.y << ") end: (" << x.endIndex.x << ", " << x.endIndex.y << ")" << endl;
    // }

    // for (Point symbol : symbols)
    // {
    //     cout << "(" << symbol.x << " , " << symbol.y << ")" << endl;
    // }

    // iterate through symbols
    for (Point symbol : symbols)
    {
        int adjacentCount = 0;
        int gearRatio = 1;

        //  iterate through parts
        for (PartNumber partNumber : partNumbers)
        {
            // is part within vertical bounds
            if (partNumber.startIndex.y <= symbol.y + 1 && partNumber.startIndex.y >= symbol.y - 1)
            {
                //  is part within horizontal bounds

                if (symbol.x >= partNumber.startIndex.x - 1 && symbol.x <= partNumber.endIndex.x)
                {
                    cout << partNumber.value << " " << adjacentCount << endl;

                    gearRatio = gearRatio * partNumber.value;
                    adjacentCount += 1;
                }
            }
        }

        if (adjacentCount == 2)
        {
            total += gearRatio;
        }
    }

    file.close();

    std::cout << total << endl;

    return 0;
}
