#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Trebuchet?! - Part 1
// 52974

int main()
{
    fstream file;
    file.open("../input.txt", ios::in);

    int total = 0;

    if (file.is_open()) {
        string tp;
        while (getline(file, tp)) {
            int first = -1;
            int last = -1;

            for (char ch : tp) {

                int a = ch;

                if (a >= 0x30 && a <= 0x39) {
                    if (first == -1) {
                        first = a;
                    } else {
                        last = a;
                    }
                }
            }

            if (first == -1) {
                break;
            }

            string n;

            n += char(first);

            if (last != -1) {
                n += char(last);
            } else {
                n += char(first);
            }

            total += stoi(n);
        }
    }

    file.close();

    cout << total << endl;

    return 0;
}