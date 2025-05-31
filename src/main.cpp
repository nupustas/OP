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
    ofstream urlOutput("urls.txt");

    if (!input.is_open() || !output.is_open() || !urlOutput.is_open()) {
        cout << "Nepavyko atidaryti failų!" << endl;
        return 1;
    }

    regex frontUnwanted(R"(^[\"'„“°.,:;!?()\[\]{}<>]+)");
    regex backUnwanted(R"([\"'„“°.,:;!?()\[\]{}<>]+$)");
    regex insideUnwanted(R"([\\/.|:*+=@!?#$%^&~`<>\",;\[\]])");
    regex urlRegex(R"((https?://[^\s\"'<>]+)|(www\.[^\s\"'<>]+)|([a-zA-Z0-9.-]+\.[a-zA-Z]{2,}))");

    map<string, int> wordCount;
    map<string, set<int>> wordLines;
    set<string> foundUrls;

    string line;
    int lineNumber = 1;
    while (getline(input, line)) {

        auto urlsBegin = sregex_iterator(line.begin(), line.end(), urlRegex);
        auto urlsEnd = sregex_iterator();

        for (auto it = urlsBegin; it != urlsEnd; ++it) {
            string url = it->str();

            while (!url.empty() && (url.back() == '.' || url.back() == ',' || url.back() == ';' || url.back() == '!')) {
                url.pop_back();
            }

            foundUrls.insert(url);
        }

      
        istringstream iss(line);
        string word;

        while (iss >> word) {
            // pasalina , . - simbolius is priekio ir galo
            word = regex_replace(word, frontUnwanted, "");
            word = regex_replace(word, backUnwanted, "");

            // skip zodzius su simboliais
            if (regex_search(word, insideUnwanted)) {
                continue;
            }

            // paverciam zodi mazosiomis raidemis
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            // skip tuscius, per trumpus zodzius ir simbolius
            if (word.empty() || word.length() <= 1 || !any_of(word.begin(), word.end(), ::isalpha)) {
                continue;
            }

            wordCount[word]++;
            wordLines[word].insert(lineNumber);
        }
        ++lineNumber;
    }

    // Output zodzius
    for (const auto& [w, count] : wordCount) {
        if (count > 1) {
            output<< w << ": " << count << "       lines: ";
            const auto& lines = wordLines[w];
            for (auto it = lines.begin(); it != lines.end(); ++it) {
                output << *it;
                if (next(it) != lines.end()) output << ", ";
            }
            output << "\n";
        }
    }

    // Output URLs
    for (const string& url : foundUrls) {
        urlOutput << url << "\n";
    }

    cout << "Žodžiai, pasikartoję daugiau nei 1 kartą, išrašyti į output.txt su jų eilutėmis\n";
    cout << "Nuorodos išrašytos į urls.txt\n";
    return 0;
}
