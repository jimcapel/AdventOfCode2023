#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Trebuchet?! - Part 2
// 52974

int main()
{
    string numbers[18] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "one", "two", "three",
                          "four", "five", "six", "seven", "eight", "nine"};

    fstream file;
    file.open("../input.txt", ios::in);

    int total = 0;

    if (file.is_open())
    {
        string tp;
        while (getline(file, tp))
        {
            int first = -1;
            int firstIndex = 1000;

            int last = -1;
            int lastIndex = -1;

            for (int i = 0; i < 18; i++)
            {
                // searching forward to find first number
                int indexOfString = tp.find(numbers[i]);
                if (indexOfString != -1 && indexOfString < firstIndex)
                {
                    firstIndex = indexOfString;
                    first = (i % 9) + 1;
                }

                // searching backward to find last number
                int indexOfStringReverse = tp.rfind(numbers[i]);

                if (indexOfStringReverse != -1 && indexOfStringReverse > lastIndex)
                {
                    lastIndex = indexOfStringReverse;
                    last = (i % 9) + 1;
                }
            }

            if (first == -1)
            {
                break;
            }

            string n;

            n += to_string(first);

            cout << n << endl;

            if (last != -1)
            {
                n += to_string(last);
            }
            else
            {
                n += to_string(first);
            }

            total += stoi(n);
        }
    }

    file.close();

    cout << total << endl;

    return 0;
}
