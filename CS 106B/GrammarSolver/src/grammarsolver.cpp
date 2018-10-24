// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "grammarsolver.h"
#include <hashmap.h>
#include <string>
#include "strlib.h"
#include "simpio.h"
#include <iostream>
#include "random.h"

using namespace std;

string engrammer (HashMap <string, Vector<Vector<string>>> &grammar, string &symbol, string &gramGen);

/* accepts a reference to an input file representing a language grammar,
 * along with a symbol to randomly generate and the number of times to generate it.
 * Generates the given number of random expansions of the given symbol and return
 * them as a Vector of strings.
 * args: ifstream input (language grammar),
 * int times (number of times to genereate),
 * string symbol (symbol)
 * return: Vector <string> returnVector (Vector with times strings generated)
 */
Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    HashMap <string, Vector<Vector<string>>> grammar;
    string line;
    while (getline(input, line)) {
        //loads grammar into a HashMap.
        Vector<string> split = stringSplit(line, "::=");
        for (string s : stringSplit(split[1], "|")) {
            Vector<string> tokens = stringSplit(trim(s), " ");
            if (!tokens.isEmpty()) {
                grammar[split[0]] += tokens;
            }
        }
    }
    Vector <string> returnVector;
    // loads string into vector for return.
    for (int i = 0; i < times; i++) {
        string gramGen = "";
        returnVector.add(engrammer(grammar, symbol, gramGen));
    }
    return returnVector;
}

/* recursively
 * args: HashMap <string, Vector<Vector<string>>> &grammar (map from
 * tokens to other tokens or terminals), string gramGen (string to be built),
 * string symbol (symbol)
 * return: string gramGen (phrase being built)
 */
string engrammer (HashMap <string, Vector<Vector<string>>> &grammar, string &symbol, string &gramGen) {
    if (grammar[symbol].isEmpty()){
        // base case.
        gramGen += symbol + " ";
        return gramGen;
    }
    else {
        for (string rules : grammar[symbol][randomInteger(0, grammar[symbol].size() - 1)]) {
            // parses through the elements picked at random from dictionary.
            // recursively changes gramGen until reaches base case.
            gramGen = engrammer(grammar, rules, gramGen);
        }
    }
    return gramGen;
}

