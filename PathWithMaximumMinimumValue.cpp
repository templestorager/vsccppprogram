// Problem Description 
/*
 
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
int maximumMinimumPath(vector<vector<int>>& A);

int main()
{
//    vector<vector<int> > path{{5,4,5},{1,2,6},{7,4,6}};
    vector<vector<int> > path{{2,2,1,2,2,2},{1,2,2,2,1,2}};
    cout << "Maximum Minimum Value is " << maximumMinimumPath(path) << endl;
}

int maximumMinimumPath(vector<vector<int>>& A) 
{
    int GlobalMin = A[0][0];
    priority_queue<pair<int,pair<int,int>>> neighbors;
    int r = A.size(), c = A[0].size();
    vector<vector<bool> > visited(r,vector<bool>(c,false));
    vector<vector<int> > direction{{-1,0},{1,0},{0,1},{0,-1}};
    neighbors.push({A[0][0],{0,0}});
    visited[0][0] = true;
    while(!neighbors.empty())
    {
        auto pos = neighbors.top();
        neighbors.pop();
        GlobalMin = min(pos.first,GlobalMin);
        if ( pos.second.first == r - 1 && pos.second.second == c-1 )
        {
            return GlobalMin;
        }
        for ( int dir = 0; dir < direction.size(); dir++ )
        {
            int new_x = pos.second.first + direction[dir][0];
            int new_y = pos.second.second + direction[dir][1];
            if ( new_x >= 0 && new_x < r && new_y >= 0 && new_y < c && !visited[new_x][new_y] )
            {
                neighbors.push({A[new_x][new_y],{new_x,new_y}});
                visited[new_x][new_y] = true;
            }
        }
    }
    
    return -1;
}