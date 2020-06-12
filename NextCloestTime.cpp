#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;


class Solution {
public:
    string nextClosestTime(string time) {
        unordered_set<int> digits;
        int min_elapsed = 24 * 60;
        int h_res, m_res;
        int delimiter_pos = time.find(":");
        int cur_time = stoi(time.substr(0,delimiter_pos)) * 60 + stoi(time.substr(delimiter_pos+1));
        h_res = stoi(time.substr(0,delimiter_pos));     // hande the case 00:00
        m_res = stoi(time.substr(delimiter_pos+1));     // hande the case 00:00
        string res;
        for ( auto c : time )
        {
            if ( c != ':' )
                digits.insert(c-'0');      // at most four digits 
        }
        
        for ( auto h1 : digits )
            for ( auto h2 : digits )
            {
                int hour = h1 * 10 + h2;
                if ( hour < 24 )
                {
                    for ( auto m1 : digits ) 
                        for ( auto m2 : digits )
                        {
                            int minute = m1 * 10 + m2;
                            if ( minute < 60 )
                            {
                                int candi_elapsed = hour * 60 + minute - cur_time;
                                if ( candi_elapsed < 0 )
                                    candi_elapsed += 24 * 60;
                                if ( candi_elapsed > 0 && candi_elapsed < min_elapsed )
                                {
                                    min_elapsed = candi_elapsed;
                                    h_res = hour;
                                    m_res = minute;
                                }
                            }
                        }
                }
            }
        
        res += h_res >= 10 ? to_string(h_res) : ("0"+to_string(h_res));
        res += ":";
        res += m_res >= 10 ? to_string(m_res) : ("0" + to_string(m_res));
        return res;
    }

};

int main()
{
    string time = "19:34";
    string next = nextClosestTime(time);
    cout << "time is " << time << " Next time is " << next << endl;
}