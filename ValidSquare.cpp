/*
 This test program implements several utilities. 
 First, it tests when given four points can form a square. 
 Second, then it extends to find the number of squares can be formulated by a set of n > 4 given points. 

*/

#include <iostream> 
#include <vector>
#include <set>
#include <map>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <unordered_set>

using namespace std;

#define TEST_TIMES 10000

#define DEBUG 0

static bool print_out = 0;

// This function generates n points in the planar plane, which has (x-coordinate, y-coordinate) in integer
void GeneratePoints( vector<vector<int>> &points, int n )
{
    vector<int> tmp; 
    srand(time(nullptr));
    while (n--)
    {
        tmp.push_back( rand() % 10 );
        tmp.push_back( rand() % 10 );
        points.push_back( tmp );
        tmp.clear();
    }
}

// Print out the points 
void PrintPoints( const vector<vector<int>> points )
{
    if ( print_out )
    {
        for ( int i = 0;  i < points.size(); i++ )
        {
            if ( i != 0 && i % 10 == 0 )
                cout << endl;
            cout << "[" << points[i][0] << "," << points[i][1] << "] ";
        }
        cout << endl;
    }
}

// This utility function calculates the distance between two points 
long CalculatePointDistance( const vector<int> &p1, const vector<int> &p2 )
{
    return pow(p2[0]-p1[0],2) + pow(p2[1]-p1[1],2);
}

// This function checks whether four points forms a square. 
// This sufficient and necessary condition for four points to form a square is: 
// 1. All four sids are congruent  
// 2. The two diagonals are the same in length 
// we put all six distance formuated by the 4 points in a set and then check it has only two length sizes 
bool IsFourPointsSquareCheckDistance ( const vector<vector<int>> &points )
{
    assert( points.size() == 4 );
    set<long> pointdist;
    for ( int i = 0; i < points.size() - 1; i++ )
        for ( int j = i + 1; j < points.size(); j++ )
        {
            pointdist.insert(CalculatePointDistance(points[i],points[j]));
        }
    if ( pointdist.size() != 2 )
        return false;
    for ( auto it = pointdist.begin(); it != pointdist.end(); it++ )
        if ( *it == 0 )
            return false;
    return true;
}

bool Compare( const vector<int> &p1, const vector<int>& p2 )
{
    if ( p1[0] < p2[0] )
        return true;
    else if ( p1[0] == p2[0] && p1[1] < p2[1] )
        return true;
    return false;
}

// We sort the points by the x-coordinate and by y-coordinate in case of a tie, say order then is p0p1p2p3. 
// then the four sides are p0p1, p1p3, p3p2, p2p0 and the two diagnoals are p0p3, p1p2.
bool IsFourPointsSquareCheckSortedDistance( vector<vector<int>> &points )
{
    sort( points.begin(), points.end(), Compare );
    return CalculatePointDistance( points[0],points[1] ) > 0 &&
           CalculatePointDistance( points[0], points[1] ) == CalculatePointDistance( points[1], points[3] ) && 
           CalculatePointDistance( points[1], points[3] ) == CalculatePointDistance( points[3], points[2] ) && 
           CalculatePointDistance( points[3], points[2] ) == CalculatePointDistance( points[2], points[0] );
}

// This solution uses the quartic complexity (n^4)
// We first eleminate the duplicate points to avoid checking duplicate points tuples 
int GetSquareFromPointsNQuartic( const vector<vector<int> > &points )
{
    vector<vector<int>> uniquepoints;
    set<vector<int>> pointset;
    int squares = 0;
    if ( points.size () < 4 )
        return 0;
    
    if ( print_out )
        cout << "points size is " << points.size() << " in function " << __LINE__ << endl;
    for ( auto p : points )
    {
        pointset.insert( p );
    }
    uniquepoints = vector<vector<int> > (pointset.begin(),pointset.end());

    // brute force searching 
    for( int p0 = 0; p0 < uniquepoints.size(); p0++ )
        for ( int p1 = p0+1; p1 < uniquepoints.size(); p1++ )
            for ( int p2 = p1+1; p2 < uniquepoints.size(); p2++ )
                for( int p3 = p2+1; p3 < uniquepoints.size(); p3++ )
                {
                    vector<vector<int> > FourPoints;
                    FourPoints.push_back( uniquepoints[p0] );
                    FourPoints.push_back( uniquepoints[p1] );
                    FourPoints.push_back( uniquepoints[p2] );
                    FourPoints.push_back( uniquepoints[p3] );
                    if ( IsFourPointsSquareCheckDistance( FourPoints ) )
                    {
                        PrintPoints( FourPoints );
                        squares++;
                    }
                }
    return squares;
}

// Given any two points as one of the diagonals, it uniquely defines a square. 
// This function returns the other two points forming the other diagonal of the square defined by the given diagnoal 
// The idea is: the other diagnal is perpendicular to the diagonal and intersects at the mid point of the given diagnal 
// The two end points of the other diagonal are thus the two points reached through rotating the vector starting 
// from the middle to either of the given points arount the middle point by 90 degree clockwise and unticlockwise, respectively.
// The result is returned in sorted order
vector<vector<int>> CalculateTheOtherdiagonal( const vector<vector<int>> &Diagonal )
{
    vector<vector<int>> res;
    assert( Diagonal.size() == 2 && Diagonal[0] != Diagonal[1] );
    vector<float> m_pos{((float)Diagonal[0][0] + (float)Diagonal[1][0])/2, ((float)Diagonal[0][1]+(float)Diagonal[1][1])/2};
    // Note that we swap x and y in the delta
    vector<float> delta({Diagonal[0][1] - m_pos[1], Diagonal[0][0] - m_pos[0]});

    // First point by negating delta_x 
    res.push_back(vector<int>{(int)(m_pos[0]-delta[0]),(int)(m_pos[1]+delta[1])});
    // Second point by negating delta_y
    res.push_back( vector<int>{(int)(m_pos[0]+delta[0]),(int)(m_pos[1]-delta[1])});

    sort( res.begin(), res.end(), Compare );
    return res;
}

// This function tests whether the given three points are the three points of a square, with the first point (smallest)
// being the left-bottom point. If so, it calculates the fourth point in @FourthPoint and returns true. Otherwise, it return false.Compare
// The procedure to check the valid three points is: 
// p0p1 is perependicular to p0p2 (dot product is zero) and line p0p1 is equal to line p0p2
// The procedure to calculate the coordinate of the fourth diagnal point based on the fact that p1p2 
// must be one diagonal since one p0p1p2 are in sorted order 
bool ValidThreePoints( const vector<vector<int>> &ThreePoints, vector<int> &FourthPoint )
{
    vector<int> p0p1_vec{ThreePoints[1][0] - ThreePoints[0][0], ThreePoints[1][1] - ThreePoints[0][1]};
    vector<int> p0p2_vec{ThreePoints[2][0] - ThreePoints[0][0], ThreePoints[2][1] - ThreePoints[0][1]};
    if ( p0p1_vec[0] * p0p2_vec[0] + p0p1_vec[1] * p0p2_vec[1] != 0 ) // dot product is not zero 
        return false;
    if ( CalculatePointDistance(ThreePoints[0],ThreePoints[1]) != CalculatePointDistance(ThreePoints[0],ThreePoints[2]) ) // adjcent sides are not equal 
        return false;

    vector<vector<int>> p1p2_diagonal{ThreePoints[1],ThreePoints[2]};
    vector<vector<int>> p0p3_diagonal;

    p0p3_diagonal = CalculateTheOtherdiagonal( p1p2_diagonal );

    for ( int i = 0; i < p0p3_diagonal.size(); i++ )
    {
        if ( p0p3_diagonal[i] != ThreePoints[0] )
        {
            FourthPoint = p0p3_diagonal[i];
            break;
        }
    }
    
    return true;
}

// Return the number of squares formed by the give set of points, using O(n^3) complexity 
// Algorithm: 
// 0. Remove duplicate points and store them in a map for convenient checking later 
// 1. sort the points according to x-coordinate and y-coordinate if it is a tie
// 2. Then select three points in sorted order and check whether they are three points of a square 
//    with the smallest point being the left-bottom point. And if so, we can calculate the right-up 
//    point using math. Note the three points (if they satisfy the conditions) can define a unique square 
// 3. check if the calculated fourth point exists in the points set. If so, then we have found a square 
int GetSquareFromPointsNCubic( const vector<vector<int>> &points )
{
    // To check the existence of a point in O(1), we use map. 
    // Even though we can use set to check the existence of a point, it's complexity is O(lgn), which would 
    // cause our complexity to be O(n^3lgn)
    // map<string,bool> pointmap; 
    set<vector<int>> pointset( points.begin(), points.end() );
    vector<vector<int>> uniquepoints( pointset.begin(), pointset.end() );
    sort( uniquepoints.begin(), uniquepoints.end(), Compare );
    map<vector<int>,bool> pointmap;
    if ( print_out )
        cout << "points size is " << points.size() << " in function " << __LINE__ << endl;
    int squares = 0;
    for ( auto p : uniquepoints )
    {
        pointmap[p] = true;
    }

    for ( int p0 = 0; p0 < uniquepoints.size(); p0++ )
        for ( int p1 = p0+1; p1 < uniquepoints.size(); p1++ )
            for ( int p2 = p1 + 1; p2 < uniquepoints.size(); p2++ )
            {
                vector<vector<int>> ThreePoints(3,vector<int>(2));
                vector<int> FourthPoint;
                ThreePoints[0] = uniquepoints[p0];
                ThreePoints[1] = uniquepoints[p1];
                ThreePoints[2] = uniquepoints[p2];
                // if the three points can form a square, then p1p2 must be a diagonal
                if ( ValidThreePoints(ThreePoints, FourthPoint ) && pointmap[FourthPoint] )
                {
                    ThreePoints.push_back(FourthPoint);
                    PrintPoints( ThreePoints );
                    squares++;
                }
            }
    return squares;
}

// This function finds the number of squares that can be formed by the set of given points 
// The idea is as following: 
// 0. put all points in a map to facilitate O(1) checking 
// 1. select pairs of distinct points
// 2. use the selected pair as one diagonal and calculate the other diagnoal 
// 3. check if the other two points are also in the set. if so push the four points in the result
// 4. remove duplicate from the result

bool IsSamePoint( const vector<int> &p1, const vector<int> &p2 )
{
    assert( p1.size() == 2 && p2.size() == 2 ); 
    return p1[0] == p2[0] && p1[1] == p2[1];
}

int GetSquareFromPointsNSquared( const vector<vector<int>> &points )
{
    map<vector<int>,bool> pointmap;
    set<vector<int> > uniquepoints(points.begin(),points.end());
    vector<vector<int> > uniquepoint_vec( uniquepoints.begin(), uniquepoints.end() );
    vector<vector<vector<int>>> squares;        // each contains four points, can contain duplicate 
    set<vector<vector<int>>> uniquesquares;     // each contains four points, all are unique
    if ( points.size() < 4 ) 
        return 0;
    for ( auto p : uniquepoints )
    {
        pointmap[p] = true;
    }
    if ( print_out )
        cout << "total size " << points.size() << " map point size " << pointmap.size() << endl;
    // sort( uniquepoint_vec.begin(), uniquepoint_vec.end(), Compare );
    for ( int i = 0; i < uniquepoint_vec.size(); i++ )
        for ( int j = i+1; j < uniquepoint_vec.size(); j++ )
        {
            vector<vector<int>> theotherdiagnonal = CalculateTheOtherdiagonal( vector<vector<int>>{uniquepoint_vec[i],uniquepoint_vec[j]} );
            // Note: after we get the other diagonal, we need to confirm that the four points indeed can form a square, because when the 
            // calculated points may not be an integer and after rounded to integer they may happen to be in the point set.
            if ( pointmap[theotherdiagnonal[0]] && pointmap[theotherdiagnonal[1]] && IsFourPointsSquareCheckDistance({uniquepoint_vec[i],uniquepoint_vec[j],theotherdiagnonal[0],theotherdiagnonal[1]}) )
            {
                squares.push_back(vector<vector<int>>{uniquepoint_vec[i],uniquepoint_vec[j],theotherdiagnonal[0],theotherdiagnonal[1]});
            }
        }
    
    // squares may contain duplicates 
    for ( int i = 0; i < squares.size(); i++ )
    {
        sort( squares[i].begin(), squares[i].end(), Compare );
        uniquesquares.insert( squares[i] );
    }
    for ( auto &sq : uniquesquares )
        PrintPoints( sq );
    if ( print_out )
        cout << "sizeof of sqaures is " << squares.size() << " sizeof uniquesquares is " << uniquesquares.size() << endl;

    return uniquesquares.size();

}

int main()
{
    vector<vector<int>> points;
    // print_out = 0;
    points.push_back({0,4});
    points.push_back({2,2});
    points.push_back({2,6});
    points.push_back({4,0});
    points.push_back({4,4});
    points.push_back({6,2});
    
    points.push_back({1,1});
    points.push_back({1,4});
    points.push_back({4,1});
    points.push_back({7,1});
    points.push_back({4,4});
    points.push_back({7,4});

    points.push_back({4,8});
    points.push_back({6,6});
    points.push_back({8,4});
    points.push_back({10,6});
    points.push_back({8,8});
    points.push_back({6,10});
    
    int i = 0;
    while ( i++ < 10 )
    {
        GeneratePoints( points, 10 );
        cout << "There are " << GetSquareFromPointsNQuartic( points ) << " <n quartic> squares in the above set of points" << endl;
        cout << "There are " << GetSquareFromPointsNCubic( points ) << " <n cubic> squares in the above set of points" << endl;
        cout << "There are " << GetSquareFromPointsNSquared( points ) << " <n squared> squares in the set of points" << endl;
    }
    return 0;
}
