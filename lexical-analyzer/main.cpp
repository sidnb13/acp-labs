#include <iostream>
#include <string>

#include <sstream>
#include <vector>

using namespace std;

// returns count of non-overlapping occurrences of 'sub' in 'str'

int countSubstring(const string& str, const string& sub) {
    if (sub.length() == 0) return 0;
    int count = 0;
    for (int offset = str.find(sub); offset != string::npos; offset = str.find(sub, offset + sub.length())) {
        ++count;
    }
    return count;
}

// this function takes in either a . or \\s whitespace as a delimiter,
// eliminating the need for 2 separate functions for sentence/word count (so total function count is 5 not 6)

int countInString(const string& source, char delimiter=' ') {
    int count = 0;
    stringstream stream(source);
    string t;
    while (getline(stream, t, delimiter))
        count++;
    return count;
}

int avgWordsInSentence(const string& source) {
    int len = countInString(source);
    int sentNum = countInString(source, '.');
    return len/sentNum;
}

int uniqueWords(const string& source) {
    stringstream stream(source);
    string t;
    vector<string> words;
    while (getline(stream, t, ' ')) {
        if (std::count(words.begin(), words.end(), t) == 0)
            words.push_back(t);
    }

    /*for (const string& word : words)
        cout << word << endl;*/

    return words.size();
}

double lexicalDensity(const string& source) {
    int uniqueWordCount = uniqueWords(source);
    int totalWords = countInString(source);

    return ((double)uniqueWordCount/(double)totalWords) * 100.0;
}

int main() {
    string source = "I was born in Lousiana down on the ol bayou raised on shrimps and catfish mamas good gumbo. "
                    "I got the ramblin fever. Said goodbye to ma and pa. Crossed that ol red river and this is what I saw. "
                    "I saw miles and miles of Texas 1000 stars up in the sky. "
                    "I saw miles and miles of Texas gonna live here till I die.";

    cout << "substring count: " << countSubstring(source, "is") << endl;
    cout << "words in source text: " << countInString(source) << endl;
    cout << "sentences in source text: " << countInString(source, '.') << endl;

    cout << "avg. number of words per sentence: " << avgWordsInSentence(source) << endl;
    cout << "lexical density: " << lexicalDensity(source) << endl;
}