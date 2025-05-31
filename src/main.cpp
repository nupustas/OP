#include "global.h"

int main() {
    ifstream input("tekstas.txt");
    ofstream output("zodziai.txt");
    ofstream OutUrls("nuorodos.txt");

    if (!input.is_open() || !output.is_open() || !OutUrls.is_open()) {
        cout << "Nepavyko atidaryti failų!" << endl;
        return 1;
    }

    map<string, int> wordCount;
    map<string, set<int>> wordLines;
    set<string> urls;

    string line;
    int lineNumber = 1;

    while (getline(input, line)) {
        istringstream iss(line);
        string word;

        while (iss >> word) {
            string cleaned = trimPunctuation(word);

            if (isURL(cleaned)) {
                urls.insert(cleaned);
                continue;
            }

            if (containsUnwantedCharacters(cleaned)) continue;

            string lowered = toLower(cleaned);
            if (lowered.empty() || lowered.length() <= 1 || !any_of(lowered.begin(), lowered.end(), ::isalpha)) {
                continue;
            }

            wordCount[lowered]++;
            wordLines[lowered].insert(lineNumber);
        }

        ++lineNumber;
    }

    for (const auto& [word, count] : wordCount) {
        if (count > 1) {
            output << word <<" "<<count <<"       lines: ";
            const auto& lines = wordLines[word];
            for (auto it = lines.begin(); it != lines.end(); ++it) {
                output << *it;
                if (next(it) != lines.end()) output << ", ";
            }
            output << endl;
        }
    }

    for (const auto& url : urls) {
        OutUrls << url << '\n';
    }

    cout << "Zodziu analize baigta. Rezultatai:\n";
    cout << "Pasikartojantys zodziai: zodziai.txt\n";
    cout << "Nuorodos: nuorodos.txt\n";

    return 0;
}
