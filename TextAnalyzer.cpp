#include "TextAnalyzer.h"

using namespace std;

Item::Item(string word){
	this->word = word;
	this->counter = 1;
	this->nextItem = NULL;
}

TextAnalyzer::TextAnalyzer() : TextAnalyzer(27, NULL) {
}

TextAnalyzer::TextAnalyzer(int size, function<int(string)> lambdap) {
	for (int i = 0; i < size; i++)
		this->table.push_back(NULL);
	this->lambda = lambdap;
	cout << this->table.size() << endl;
}

// returns nothing and takes no arguments.
// It prints a word followed by its repetition count,
// each pair on a line. Here's a snippet from the included input text:
// was     15
// weeping 2
// would   10
void TextAnalyzer::PrintHashEntries() {
	for (int i = 0; i < this->table.size(); i++)
	{
		Item* item = this->table.at(i);
		while(item != NULL)
		{
			cout << item->word << " " << item->counter << endl;
			item = item->nextItem;
		}
	}
}

// It should insert the word into the hash table
// or increment the count of that word if it is
// already in the table.
void TextAnalyzer::Insert(string word) {
	if (word.size() == 0) {
		return;
	}
	int hash = this->calculateHash(word);
	if (hash >= this->table.size()) {
		cout << "Error: " << hash << " is greater than the vector size " << this->table.size() << endl;
		return;
	}
	Item* item = this->table.at(hash);
	if (item == NULL)
	{
		this->table.at(hash) = new Item(word);
		return;
	}
	while(item->word != word && item->nextItem != NULL)
		item = item->nextItem;
	
	if (item->word == word)
		item->counter++;
	else
		item->nextItem = new Item(word);
}

// returns the count of a word in the hash table and takes a single std::string &word argument
int TextAnalyzer::GetCount(string word) {
	if (word.size() == 0)
		return 0;
	int hash = this->calculateHash(word);
	if (hash >= this->table.size()) {
		cout << "Error: " << hash << " is greater than the vector size " << this->table.size() << endl;
		return 0;
	}
	Item* item = this->table.at(hash);
	if (item == NULL)
	{
		cout << "Item not found for hash " << hash << " and word " << word << endl;
		return 0;
	}
	while(item->word != word && item->nextItem != NULL)
		item = item->nextItem;
	if (item->word == word)
	{
		return item->counter;
	}

	cout << "Word not found: " << word << endl;
	return 0;
}

int TextAnalyzer::calculateHash(string word) {
	if (this->lambda == NULL)
		return this->calculateInternalHash(word);
	else
		return this->lambda(word);
}

// looks at only the first letter of the inserted word
// Any non-alphabetic characters hash to bucket zero
// words starting with 'A' or 'a' hash to bucket one,
// words starting with 'B' or 'b' hash to bucket two, etc.
int TextAnalyzer::calculateInternalHash(string word) {
	char firstCharacter = word.at(0);
	if (firstCharacter >= 'A' && firstCharacter <= 'Z')
		firstCharacter += ('a' - 'A');
	int index = firstCharacter - 'a';
	if (index < 0 || index > 25)
		return 0;
	return index + 1;
}

