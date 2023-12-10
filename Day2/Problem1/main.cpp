#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Cube conondrum?! - Part 1
// 2447

int main()
{
    fstream file;
    file.open("../input.txt", ios::in);

    int total = 0;

    if (file.is_open())
    {
        string tp;
        int gamedID = 1;

        string colours[3] = {"red", "green", "blue"};

        while (getline(file, tp))
        {
            int gameStringIndex = tp.find(":");

            if (gameStringIndex == -1)
            {
                continue;
            }

            // remove gameID from game string
            string gameString = tp.substr(gameStringIndex + 2) + ';';

            int last = 0;
            int next = 0;

            bool isAllowed = true;

            while ((next = gameString.find(";", last)) != -1)
            {

                string subSetGame = gameString.substr(last, next - last) + ',';
                last = next + 1;

                int subLast = 0;
                int subNext = 0;

                int green = 0;
                int blue = 0;
                int red = 0;

                while ((subNext = subSetGame.find(",", subLast)) != -1)
                {

                    string colour = subSetGame.substr(subLast, subNext - subLast);
                    subLast = subNext + 1;

                    int firstWhitespace = colour.find(" ");

                    if (firstWhitespace == 0)
                    {
                        colour = colour.substr(1);
                    }

                    int numberIndex = colour.find(" ");

                    if (numberIndex == -1)
                    {
                        continue;
                    }

                    string number = colour.substr(0, numberIndex);

                    int colourIndex = 0;

                    for (int i = 0; i < 3; i++)
                    {
                        int position = colour.find(colours[i]);

                        if (position != -1)
                        {
                            colourIndex = i;
                            break;
                        }
                    }

                    if (colourIndex == 0)
                    {
                        red += stoi(number);
                    }
                    else if (colourIndex == 1)
                    {
                        green += stoi(number);
                    }
                    else if (colourIndex == 2)
                    {
                        blue += stoi(number);
                    }
                }

                if (!(red <= 12 && green <= 13 && blue <= 14))
                {
                    isAllowed = false;
                    break;
                }
            }

            if (isAllowed)
            {
                total += gamedID;
            }

            // incerment gameID at end of while loop;
            gamedID++;
        }
    }

    file.close();

    std::cout << total << endl;

    return 0;
}
