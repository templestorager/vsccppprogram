#include <vector>
#include <string>
#include <iostream>
#include <map>

using namespace std;

vector<string> fizzBuzz(int n) {
    vector<string> res;
    map<int,string> m = {
        {3,"Fizz"},
        {5,"Buzz"}
    };
    for ( int i = 1; i <= n; i++ )
    {
        string s;
        for ( auto iter = m.begin(); iter != m.end(); iter++ )
        {
            cout << "iter->first = " << iter->first << " iter->second" << iter->second << endl;
            if ( i % iter->first == 0 )
                s += iter->second;
        }
        if ( s == "" )
            s += to_string(i);
        res.push_back(s);
    }
    return res;
}
#if 1
int main()
{
    vector<string> res;
    int num = 15;
    res = fizzBuzz(num);
    for ( int i = 0; i < res.size(); i++ )
        cout << res[i] << endl;
    cout << endl;

}
#endif

#if 0
int main()
{
	std::unordered_map<int, std::string> m = 
	{
		{1, "one"},
		{2, "two"},
		{3, "three"}
	};

	for (auto iter = m.begin(); iter != m.end(); iter++ )
		std::cout << "{" << iter->first << " -> " << iter->second << "}\n";

	return 0;
}

#endif 
