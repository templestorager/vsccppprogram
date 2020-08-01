#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<string>::iterator digit_logs = std::stable_partition(logs.begin(), logs.end(),
                                                                    [](const string log) { return isalpha(log.back());});
        sort(logs.begin(),digit_logs,LogCmp);
        return logs;
        
    }
    
    static bool LogCmp(const string first, const string second)
    {
        size_t spacepos1 = first.find(' ');
        size_t spacepos2 = second.find(' ');
        string word1 = first.substr( spacepos1 );
        string word2 = second.substr( spacepos2 );
        string identifier1 = first.substr(0,spacepos1);
        string identifier2 = second.substr(0,spacepos2);
        if ( word1 < word2 ) 
            return true;
        else if ( word1 == word2 ) {
            if ( identifier1 < identifier2 ) 
                return true;
            else 
                return false;
        }
        else {
            return false;
        }
    }
};

template <typename T >
T Maxof( T a, T b )
{
    return (a > b ? a : b);
}

int main()
{
    vector<int> data = { 2,3,4,5,72,21};
    stable_partition( data.begin(), data.end(), [](int n ) { return n % 2 == 0; } ); // put all even numbers before odd numbers 
    const char str[] = "abcd";
    string hello = "Hello World!";
    cout << "strlen(str) is " << strlen(str) << " sizeof(str) is " << sizeof(str) << endl;
    cout << "strlen(str) is " << strlen(hello.c_str()) << " hello.size() is " << hello.size() << endl;
    for ( auto n : data )
        cout << n << " ";
    cout << endl;

    Solution s;

    vector<string> logs = {"dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"};
    vector<string> res = s.reorderLogFiles(logs);

    for ( auto s : res )
        cout << s << endl;
    
}