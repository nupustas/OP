#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <regex>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    if (!input.is_open() || !output.is_open()) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return 1;
    }

    // Regexes to clean words
    regex frontUnwanted(R"(^[\"'„“°.,:;!?()\[\]{}<>]+)");
    regex backUnwanted(R"([\"'„“°.,:;!?()\[\]{}<>]+$)");
    regex insideUnwanted(R"([\\/.|:*+=@!?#$%^&~`<>\",;\[\]])");

    map<string, int> wordCount;
    string line;
    while (getline(input, line)) {
        istringstream iss(line);
        string word;

        while (iss >> word) {
            // Remove unwanted punctuation at start and end
            word = regex_replace(word, frontUnwanted, "");
            word = regex_replace(word, backUnwanted, "");

            // Skip words containing unwanted chars inside
            if (regex_search(word, insideUnwanted)) {
                continue;
            }

            // Convert to lowercase
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            // Skip empty, very short, or non-alphabetic words
            if (word.empty() || word.length() <= 1 || !any_of(word.begin(), word.end(), ::isalpha)) {
                continue;
            }

            wordCount[word]++;
        }
    }

    for (const auto& [w, count] : wordCount) {
        if (count > 1) {
            output << w << ": " << count << "\n";
        }
    }

    cout << "Žodžiai, pasikartoję daugiau nei 1 kartą, išrašyti į output.txt\n";
    return 0;
}
