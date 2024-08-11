#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

struct HuffmanNode
{
    char data;
    int frequency;
    HuffmanNode *left;
    HuffmanNode *right;
    HuffmanNode(char data, int frequency) : data(data),
                                            frequency(frequency), left(nullptr), right(nullptr) {}
};

struct CompareNodes
{
    bool operator()(HuffmanNode *lhs, HuffmanNode *rhs)
    {
        return lhs->frequency > rhs->frequency;
    }
};

HuffmanNode *buildHuffmanTree(const map<char, int> &frequencies)
{

    priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> pq;
    for (const auto &pair : frequencies)
    {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1)
    {

        HuffmanNode *left = pq.top();
        pq.pop();
        HuffmanNode *right = pq.top();
        pq.pop();

        cout << left->data << " " << left->frequency << "\n";
        cout << right->data << " " << right->frequency << "\n";

        HuffmanNode *newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

void generateHuffmanCodes(HuffmanNode *root, string code,
                          map<char, string> &huffmanCodes)
{
    if (root == nullptr)
    {
        return;
    }

    if (!root->left && !root->right)
    {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);

    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}
int main()
{
    string input;
    cout << "Enter string :- ";
    cin >> input;
    map<char, int> frequencies = {{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};

    HuffmanNode *root = buildHuffmanTree(frequencies);

    map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    cout << "Huffman Codes:" << endl;
    for (const auto &pair : huffmanCodes)
    {
        cout << pair.first << " : " << pair.second << endl;
    }
    return 0;
}