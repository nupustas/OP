#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
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
    map<string, set<int>> wordLines;  // laiko zodziu eilutes nr

    string line;
    int lineNumber = 1;
    while (getline(input, line)) {
        istringstream iss(line);
        string word;

        while (iss >> word) {
            // pasalina simbolius is priekio ir galo
            word = regex_replace(word, frontUnwanted, "");
            word = regex_replace(word, backUnwanted, "");

            // skip zodzius kurie turi neleistinus simbolius
            if (regex_search(word, insideUnwanted)) {
                continue;
            }

            // Convert to lowercase
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            // Skip tuscius, per trumpus zodzius ir simbolius
            if (word.empty() || word.length() <= 1 || !any_of(word.begin(), word.end(), ::isalpha)) {
                continue;
            }

            wordCount[word]++;
            wordLines[word].insert(lineNumber);
        }
        ++lineNumber;
    }

    // Output words appearing more than once, with counts and line numbers
    for (const auto& [w, count] : wordCount) {
        if (count > 1) {
            output << w << ": " << count << "       lines: ";
            const auto& lines = wordLines[w];
            for (auto it = lines.begin(); it != lines.end(); ++it) {
                output << *it;
                if (next(it) != lines.end()) output << ", ";
            }
            output << "\n";
        }
    }

    cout << "Žodžiai, pasikartoję daugiau nei 1 kartą, išrašyti į output.txt su jų eilutėmis\n";
    return 0;
}
