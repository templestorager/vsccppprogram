#include <unordered_map>
#include <vector>
using namespace std;

vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int,int> m;
    vector<int> res;
    unordered_map<int,int>::iterator it;
    
    for ( int i = 0; i < nums2.size(); i++ )
        m.insert(make_pair<int,int>(nums2[i],i));
    for ( int i = 0; i < nums1.size(); i++ )
    {
        it = m.find(nums1[i]);
        if ( it == m.end() )
        {
            res.push_back(-1);
        }
        else
        {
            if ( ++it == m.end() )
            {
                res.push_back(-1);
            }
            else 
            {
                res.push_back((*it).second);
            }
        }
    }
    
    return res;
}

int main()
{
    vector<int> nums1{4,1,2}, nums2{1,3,4,2};
    nextGreaterElement(nums1,nums2);
}