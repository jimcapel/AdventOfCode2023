#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    fstream file;
    file.open("../input.txt", ios::in);

    vector<int> time;
    vector<int> distance;

    int total = 1;

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

                if ((asciiValue == 0x20 || i == (current.length() - 1)))
                {
                    if (!number.empty())
                    {
                        if (lineIndex == 0)
                        {
                            time.push_back(stoi(number));
                        }
                        else
                        {
                            distance.push_back(stoi(number));
                        }
                    }

                    number = "";
                }
            }

            lineIndex++;
        }

        file.close();
    }

    for (int i = 0; i < time.size(); i++)
    {
        int couldWin = 0;

        for (int x = 1; x < time[i]; x++)
        {
            if (((time[i] - x) * x) > distance[i])
            {
                couldWin++;
            }
        }

        if (couldWin)
        {
            total = total * couldWin;
        }
    }

    cout << total << endl;

    return 0;
}