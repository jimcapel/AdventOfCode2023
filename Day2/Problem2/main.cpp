
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Cube conondrum?! - Part 2
// 56322

int main()
{
    fstream file;
    file.open("../input.txt", ios::in);

    // sets multiplied together
    int total = 0;

    if (file.is_open()) {
        string tp;

        string colours[3] = { "red", "green", "blue" };

        while (getline(file, tp)) {
            int gameStringIndex = tp.find(":");

            if (gameStringIndex == -1) {
                continue;
            }

            // remove gameID from game string
            string gameString = tp.substr(gameStringIndex + 2) + ';';

            int last = 0;
            int next = 0;

            bool isAllowed = true;

            int green = -1;
            int blue = -1;
            int red = -1;

            while ((next = gameString.find(";", last)) != -1) {

                string subSetGame = gameString.substr(last, next - last) + ',';
                last = next + 1;

                int subLast = 0;
                int subNext = 0;

                while ((subNext = subSetGame.find(",", subLast)) != -1) {

                    string colour = subSetGame.substr(subLast, subNext - subLast);
                    subLast = subNext + 1;

                    int firstWhitespace = colour.find(" ");

                    if (firstWhitespace == 0) {
                        colour = colour.substr(1);
                    }

                    int numberIndex = colour.find(" ");

                    if (numberIndex == -1) {
                        continue;
                    }

                    string number = colour.substr(0, numberIndex);

                    int colourIndex = 0;

                    for (int i = 0; i < 3; i++) {
                        int position = colour.find(colours[i]);

                        if (position != -1) {
                            colourIndex = i;
                            break;
                        }
                    }

                    int n = stoi(number);

                    if (colourIndex == 0 && n > red) {
                        red = n;
                    } else if (colourIndex == 1 && n > green) {
                        green = n;
                    } else if (colourIndex == 2 && n > blue) {
                        blue = n;
                    }
                }
            }

            total += green * red * blue;
        }
    }

    file.close();

    std::cout << total << endl;

    return 0;
}
