// Problem Description

#include <iostream>
#include <vector>
#include <string> 
#include <unordered_map>
#include <unordered_set>

using namespace std;

string mostCommonWord(string paragraph, vector<string>& banned) {
    unordered_map<string, int> m;
    unordered_set<string> s(banned.begin(),banned.end());
    string word; 
    int freq = INT_MIN;
    bool Inword = false;
    for ( int i = 0; i < paragraph.size(); i++ )
    {
        if ( isalpha(paragraph[i]) ) 
        {
            if ( Inword == false )
                Inword = true;
            word.append(1,tolower(paragraph[i]));
        }
        else if ( Inword )
        {
            m[word]++;
            word.clear();
            Inword = false;
        }
    }
    
    if ( isalpha(paragraph.back()) )
    {
        m[word]++;
        word.clear();
    }
    
    for ( auto it : m )
    {
        if ( !s.count(it.first) && it.second > freq )
        {
            freq = it.second;
            word = it.first;
        }
    }
    
    return word;
}

int main()
{
    string paragraph = "Bob. hIt, baLl";
    vector<string> banned = {"bob","hit"};
    string res = mostCommonWord( paragraph, banned );
    cout << "most common word is " << res << endl;
}