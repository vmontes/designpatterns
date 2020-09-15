#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Sentence
{
    vector<string> words;
    
    struct WordToken
    {
        bool capitalize;
    };

    vector<WordToken> tokens;

    Sentence(const string& text)
    {
        // todo
        istringstream f(text);
        string tmp;
        while (getline(f, tmp, ' '))
        {
            words.push_back(tmp);
            tokens.push_back({ false });
        };
    }

    WordToken& operator[](size_t index)
    {
        // todo
        return tokens[index];
    }

    string str() const
    {
        // todo
        string ret;
        for (int i = 0; i < words.size(); i++)
        {
            if (tokens[i].capitalize)
            {
                string s = words[i];
                transform(s.begin(), s.end(), s.begin(), ::toupper);
                ret += s;
            }
            else
            {
                ret += words[i];
            }
            ret += " ";
        }
        return ret;
    }
};

int main()
{
    Sentence s{ "alpha beta gamma" };
    s[0].capitalize = s[2].capitalize = false;
    s[1].capitalize = true;
    cout << s.str() << endl;
    return 0;
}