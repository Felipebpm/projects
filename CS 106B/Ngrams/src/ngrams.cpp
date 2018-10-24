#include "simpio.h"
#include "hashset.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"
#include "map.h"
#include "random.h"
using namespace std;

string promptFile();
Map <Queue <string>, Vector <string>> ngram(int &n, string &file);
string writer(Map <Queue <string>, Vector <string>> &ngram, int &nWords);
int promptWordCount();

/*
 * Prompts the user for file name, gets degree of n-gram and number of words.
 * Outputs an n-sized random text for the user.
 * variables: file - name of file, number - N in N-Grams, wordCount - number of
 * words in story.
 */
int main() {
    cout << "Welcome to CS 106B/X Random Writer ('N-Grams')!" << endl;
    cout << "This program generates random text based on a document." << endl;
    cout << "Give me an input file and an 'N' value for groups" << endl;
    cout << "of words, and I'll create random text for you." << endl << endl;
    string file = promptFile();
    int number = getInteger("Value of N? ");
    int wordCount;
    while (true) {
        cout << endl;
        wordCount = promptWordCount();
        if (wordCount == 0) {
            cout << "Exiting." << endl;
            break;
        }
        Map <Queue <string>, Vector <string>> nGram = ngram(number, file);
        cout << " ... " << writer(nGram, wordCount) << " ... " << endl;
    }
    return 0;
}

/*
 * Creates a map of queues to vectors, where the queues are the (n - 1)-sized
 * phrases and each of the elements in the vector is what comes after.
 * args: n (number of words + 1), file (filename)
 * return: Map <Queue <string>, Vector <string>> (map stated above)
 */
Map <Queue <string>, Vector <string>> ngram(int &n, string &file) {
    Map <Queue <string>, Vector <string>> ngrams;
    ifstream story;
    story.open(file);
    Queue <string> phrase;
    string word;
    for (int i = 0; i < n - 1; i++){
        story >> word;
        phrase.enqueue(word);
    }
    Queue <string> temp = phrase;
    while(story >> word) {
        ngrams[phrase].add(word);
        phrase.dequeue();
        phrase.enqueue(word);
    }
    for (int j = 0; j < n - 1; j++){
        ngrams[phrase].add(temp.peek());
        phrase.dequeue();
        phrase.enqueue(temp.peek());
        temp.dequeue();
    }
    return ngrams;
}

/*
 * Uses Markov Chains to write stories.
 * args: nWords (number of words), ngram (dictionary)
 * return: string (final story)
 */
string writer(Map <Queue <string>, Vector <string>> &ngram, int &nWords) {
    Vector <Queue <string>> keys = ngram.keys();
    int counter = 0;
    string newStory = "";
    Queue <string> manyWords = keys[randomInteger(0, keys.size())];
    for (string word : manyWords) {
        newStory += (word + " ");
        counter++;
        if (counter == nWords) {
            break;
        }
    }
    while (counter != nWords) {
        string word = ngram[manyWords][randomInteger(0, ngram[manyWords].size() - 1)];
        newStory += word + " ";
        manyWords.dequeue();
        manyWords.enqueue(word);
        counter++;
    }
    return newStory;
}

/*
 * Prompts user for file. Checks for existence. Repeats until receives valid input.
 * return: string (name of the file)
 */
string promptFile() {
    string file;
    do {
        file = getLine("Input file name? ");
        if (!fileExists(file)){
            cout << "Unable to open that file.  Try again." << endl;
        }
    } while(!fileExists(file));
    return file;
}

/*
 * Prompts user for number of words. Checks if they're bigger than 4. Repeats until receives valid input.
 * return: int (number of words)
 */
int promptWordCount() {
    int wordCount;
    do {
        wordCount = getInteger("# of random words to generate (0 to quit)? ");
        if (wordCount == 0) {
            return wordCount;
        }
        else if (wordCount < 4) {
            cout << "Must be at least 4 words." << endl;
        }
    } while (wordCount == 0 || wordCount < 4);
    return wordCount;
}

