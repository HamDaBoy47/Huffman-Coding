#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<pair<char, int>> sorted;
vector<int> frequencies;

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

void buildHuffmanTree(string characters, string str)
{
	vector<pair<char, int>> freq;

	for (int i = 0; i <= characters.length(); i += 2) {
        freq.push_back({characters[i], frequencies[i]});
	}

	priority_queue<Node*, vector<Node*>, comp> pq;

	for (auto &pair: freq) {
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
	//encode(root, "", huffmanCode);

	//Printing...

    int index = -1;
	
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
}

void freqsorter(string &characters)
{
	int x;
	int length;	

	if (characters.length() % 2 == 0){
		length = characters.length() / 2;
	}
	else{
		length = (characters.length() / 2) + 1;
	}
    
	for(int i = 0; i < length; ++i)
	{
		cin >> x;
		frequencies.push_back(x);
		//frequencies.push_back(0);
	}
}

int main()
{
	string characters;
    string encoded;
	string rubbish;
	string junk;

    getline(cin, characters);
	freqsorter(characters);
    getline(cin >> ws, encoded);
	getline(cin, rubbish);
	getline(cin, junk);

	buildHuffmanTree(characters, encoded);

	return 0;
}