#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Node
{
    string left;
    string right;
};

int main()
{
    fstream file;
    file.open("../input.txt", ios::in);

    string instructionString = "";

    // vector<Node> nodes;

    map<string, Node> nodes;

    string initialNode = "AAA";

    if (file.is_open())
    {
        string current;

        bool lineBreak = false;

        while (getline(file, current))
        {
            if (current.empty())
            {
                lineBreak = true;
                continue;
            }

            if (!lineBreak)
            {
                instructionString += current;
            }
            else
            {
                string self = current.substr(0, 3);
                string left = current.substr(7, 3);
                string right = current.substr(12, 3);

                Node node;
                node.left = left;
                node.right = right;

                nodes[self] = node;
            }
        }
    }

    int counter = 0;

    for (int i = 0; initialNode != "ZZZ"; i++)
    {
        int y = i % (instructionString.length());

        counter++;

        if (instructionString[y] == 'R')
        {
            initialNode = nodes[initialNode].right;
        }
        else
        {
            initialNode = nodes[initialNode].left;
        }
    }

    cout << counter << endl;

    file.close();

    return 0;
}
