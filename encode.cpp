#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<pair<char, int>> sorted;

struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};

Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

struct comp
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};

bool cmp(pair<char, int>& a, pair<char, int>& b)
{
    return a.second < b.second;
}
  
void sort(unordered_map<char, int>& freq)
{ 
    for (auto& it : freq) 
    {
        sorted.push_back(it);
    }

    //sort(sorted.begin(), sorted.end(), cmp);

	cout << sorted[0].first;
	for (int i = 1; i < sorted.size(); ++i)
	{
		cout << ' ' << sorted[i].first;
	}

	cout << '\n';

	cout << sorted[0].second;
	for (int i = 1; i < sorted.size(); ++i)
	{
		cout << ' ' << sorted[i].second;	
	}
}

void bits(string &text, string &str)
{
	cout << "Total Bits (Original):" << 8 * text.length() << '\n';
	cout << "Total Bits (Coded):" << str.length();
}

void encode(Node* root, string str,
			unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;

	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int &index, string str)
{
	if (root == nullptr) {
		return;
	}

	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] =='0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

void buildHuffmanTree(string text)
{
	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	priority_queue<Node*, vector<Node*>, comp> pq;

	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)
	{
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();

		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	Node* root = pq.top();

	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	//Printing...
	
	sort(freq);

	string str = "";

	for (char ch: text)
	{
		str += huffmanCode[ch];
	}

	cout << '\n' << str << '\n';
	
	bits(text, str);
}

int main()
{
	string phrase;

    getline(cin, phrase);

	buildHuffmanTree(phrase);

	return 0;
}