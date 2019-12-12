#include <stdio.h>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Item
{
	public:
		Item(string word);
		Item *nextItem;
		string word;
		int counter;
};

class TextAnalyzer {
	private:
		vector<Item*> table;
		int calculateHash(string);
		int calculateInternalHash(string);
		function<int(string)> lambda;

	public:
		TextAnalyzer();
		TextAnalyzer(int size, function<int(string)> lambdap);
		void PrintHashEntries();
		void Insert(string);
		int GetCount(string);
};

