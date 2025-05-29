#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

bool isURL(const std::string& word);

using namespace std;
int main()
{
  map<string, int> words;
  map<string, int> url;


 ifstream fd ("input.txt");
    if (!fd)
    {
        cerr << "Nepavyko atidaryti failo" << endl;
        return 1;
    }

string line;
    while(getline(fd,line))
    {
        istringstream iss(line);
        string word;

        while(iss >> word)
        {
            if (isURL(word)) {
                url[word]++;
            } else {
                words[word]++;
            }
        }

    }

    ofstream out("output.txt");
    

};
bool isURL(const std::string& word) {
    return word.find("http") != std::string::npos ||
           word.find("www.") != std::string::npos ||
           word.find(".lt") != std::string::npos;
}
