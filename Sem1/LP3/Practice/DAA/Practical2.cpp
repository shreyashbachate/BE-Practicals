#include <bits/stdc++.h>
using namespace std;

struct HuffmanNode
{
    char data;
    int freq;
    HuffmanNode *left, *right;
    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

struct CompareNodes
{
    bool operator()(HuffmanNode *left, HuffmanNode *right)
    {
        return left->freq > right->freq;
    }
};

void printCode(HuffmanNode *root, string s)
{
    if (!root)
        return;

    if (root->data != '$')
        cout << root->data << ": " << s << "\n";

    printCode(root->left, s + "0");
    printCode(root->right, s += "1");
}

void HuffmanCode(vector<char> &data, vector<int> &freq, int n)
{
    HuffmanNode *left, *right, *top;

    priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> pq;

    for (int i = 0; i < n; i++)
    {
        pq.push(new HuffmanNode(data[i], freq[i]));
    }

    while (pq.size() != 1)
    {
        left = pq.top();
        pq.pop();
        right = pq.top();
        pq.pop();

        top = new HuffmanNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        pq.push(top);
    }
    printCode(pq.top(), "");
}

int main()
{
    cout << "\nEnter no of characters :- ";
    int n;
    cin >> n;

    vector<char> data(n);
    vector<int> freq(n);

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter character and its frequency of char " << i + 1 << ":- ";
        cin >> data[i] >> freq[i];
    }

    HuffmanCode(data, freq, n);
}