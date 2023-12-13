#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    fstream file;
    file.open("../input.txt", ios::in);

    long time;
    long distance;

    if (file.is_open())
    {
        string current;
        string number;

        int lineIndex = 0;

        while (getline(file, current))
        {
            for (int i = 0; i < current.length(); i++)
            {
                int asciiValue = int(char(current[i]));

                if (asciiValue >= 0x30 && asciiValue <= 0x39)
                {
                    number += char(asciiValue);
                }

                if ((i == (current.length() - 1)))
                {
                    if (!number.empty())
                    {
                        if (lineIndex == 0)
                        {
                            time = stol(number);
                        }
                        else
                        {
                            distance = stol(number);
                        }
                    }

                    number = "";
                }
            }

            lineIndex++;
        }

        file.close();
    }

    long couldWin = 0;

    for (long x = 1; x < time; x++)
    {
        //  this is a quadratic, can solve for x.
        if (((time - x) * x) > distance)
        {
            couldWin++;
        }
    }

    cout << couldWin << endl;

    return 0;
}
