// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

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

using namespace std;

string wordladder(string file, string &word1, string &word2);
HashSet <string> neighbors(string word, HashSet<string> &dict);
string promptFile();
string findWordladder(HashSet<string> &dict, string &word1, string &word2);
bool isNeighbor(string word, string word2);

/*
 * Runs and prints wordladder. Prompts the reader for replaying.
 */
int main() {
    cout << "Welcome to CS 106B/X Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the" << endl;
    cout << "first into the second by modifying one letter at a time." << endl << endl;
    string file = promptFile();
    while (true) {
        string word1;
        string word2;
        string wLadder = wordladder(file, word1, word2);
        if (wLadder.compare("done") == 0) {
            break;
        }
        else {
            cout << endl << "A ladder from " << word2 << " back to " << word1 << ": " << endl << wLadder << endl << endl;
        }
    }
    cout << "Have a nice day." << endl;
    return 0;
}

/*
 * Prompts user for two words. Checks if they are the same size or equal.
 * Prompts user for dictionary, checks for existence. Loads it. Runs
 * and returns findWorldLadder.
 * args: string file (name of file)
 * return: string (wordladder)
 */
string wordladder(string file, string &word1, string &word2) {
    do {
        cout << endl;
        word1 = toLowerCase(getLine("Word 1 (or Enter to quit): "));
        if (word1.compare("") == 0) {
            return "done";
        }
        word2 = toLowerCase(getLine("Word 2 (or Enter to quit): "));
        if (word2.compare("") == 0) {
            return "done";
        }
        if (word2.compare(word1) == 0) {
            cout << "Two words must be different." << endl;
        }
        if (word1.length() != word2.length()) {
            cout << "Words must be the same length" << endl;
        }
    } while (word1.length() != word2.length() || word2.compare(word1) == 0);
    ifstream dictionary;
    dictionary.open(file);
    HashSet <string> dict;
    string word;
    while (dictionary >> word) { // Creates dictionary.
        dict.add(word);
    }
    return findWordladder(dict, word1, word2);
}

/*
 * Uses dictionary to find neighbors of word inputed. Returns a HashSet with neighbors.
 * args: string (word), HashSet <string> (dictionary)
 * return: HashSet <string> (neighbors)
 */
HashSet <string> neighbors(string word, HashSet <string> &dict) {
    HashSet <string> wordNeighbors;
    for (int letter = 0; letter < word.length(); letter++) {
        string temp = word;
        for (int alpha = 0; alpha < 26; alpha++){
            temp[letter] = 'a' + alpha;
            if (dict.contains(temp)) {
                wordNeighbors.add(temp);
            }
        }

    }
    return wordNeighbors;
}

/*
 * Prompts user for file. Checks for existence. Repeats until receives valid input.
 * return: string (name of the file)
 */
string promptFile() {
    string file;
    do {
        file = getLine("Dictionary file name:  ");
        if (!fileExists(file)){
            cout << "File not found." << endl;
        }
    } while(!fileExists(file));
    return file;
}

/*
 * Uses dictionary to find neighbors of word inputed. Returns a HashSet with neighbors.
 * args: HashSet <string> (dictionary), string (Word 1), string (Word 2)
 * return: string (wordladder)
 */
string findWordladder(HashSet <string> &dict, string &word1, string &word2) {
    Stack <string> stack1 = {word1};
    string defFinal = "";
    Queue <Stack <string>> queue = {stack1};
    HashSet <string> words = {word1};
    if (isNeighbor(word1, word2)) {
        stack1.add(word2);
        words.add(word2);
        for (string final : stack1) {
            final += " " + defFinal;
            defFinal = final;
        }
    }
    else {
        while (!words.contains(word2) && !queue.isEmpty()) {
            Stack <string> stack;
            stack = queue.dequeue();
            HashSet <string> neighbor = neighbors(stack.peek(), dict);
            for (string similar : neighbor) {
                if (!words.contains(similar)) {
                    Stack <string> temporaryStack = stack;
                    temporaryStack.add(similar);
                    queue.enqueue(temporaryStack);
                    words.add(similar);
                    // testing
                    if (isNeighbor(similar, word2)) {
                        temporaryStack.add(word2);
                        words.add(word2);
                        cout << temporaryStack; //jjjjjjjjjjjjjjjjj
                        for (string final : temporaryStack) {
                            final += " " + defFinal;
                            defFinal = final;
                        }
                        break;
                    }
                }
            }
        }
    }
    if (queue.isEmpty()) {
        defFinal = "Couldn't find a path.";
    }
    return defFinal;
}

/*
 * Check if two words are neighbors. Returns true if they are,
 * false if they aren't.
 * args: string word, string word2
 * return: boolean
 */
bool isNeighbor(string word, string word2) {
    HashSet <string> dict;
    dict.add(word2);
    return !neighbors(word, dict).isEmpty();
}
