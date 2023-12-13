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

// think can use chinese remainder theorem here, this only works if lcm works

int main()
{
    fstream file;
    file.open("../input.txt", ios::in);

    string instructionString = "";

    map<string, Node> nodes;

    vector<string> initialNodes;

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

                if (self[2] == 'A')
                {
                    initialNodes.push_back(self);
                }
            }
        }
    }

    for (int i = 0; i < initialNodes.size(); i++)
    {
        string node = initialNodes[i];
        int instructionIndex = 0;
        int counter = 1;

        while (true)
        {

            if (instructionString[instructionIndex] == 'R')
            {
                node = nodes[node].right;
            }
            else
            {
                node = nodes[node].left;
            }

            if (node[2] == 'Z')
            {
                // need to find lcm of counters
                cout << initialNodes[i] << ": " << node << " " << counter << endl;
                break;
            }

            counter++;
            instructionIndex = (instructionIndex + 1) % instructionString.length();
        }
    }

    file.close();

    return 0;
}
