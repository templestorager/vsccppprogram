/* 
    Given a complete binary tree with nodes of values of either 1 or 0, the following rules always hold:
    (1) a node's value is 1 if and only if all its subtree nodes' values are 1
    (2) a leaf node can have value either 1 or 0
    Implement the following 2 APIs:
    set_bit(offset, length), set the bits at range from offset to offset+length-1
    clear_bit(offset, length), clear the bits at range from offset to offset+length-1
    
    i.e. The tree is like:
                 0
              /     \
             0        1
           /  \      /  \
          1    0    1    1
         /\   / \   / 
        1  1 1   0 1
        Since it's complete binary tree, the nodes can be stored in an array:
        [0,0,1,1,0,1,1,1,1,1,0,1] 
        
*/

// We need to understand the following properties of a complete binary tree, stored in an array 
// 1. The left child and right child of node i are (2i+1) and (2i+2), respectively 
//    We define a utility function Buddy(int x) to find it's buddy (sibling)
// 2. The parent of node i is node (i+Buddy(i))/4.

// Step1: we set each requested node and recursively traverse down its desendents to set them to meet the first requirement
// Step2: we then recursively traverse up and set its parent as well if its' buddy is also set 

#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;

int GetBuddy( int x ) 
{
    if( x % 2 )
        return x + 1;
    else 
        return x - 1; // handle -1 case ? The root has no buddy 
}

int GetParent( int x )
{
    return (x+GetBuddy(x))/4;
}

// this function sets the indicated bit and traverses down 
void setbit_down( vector<int> &nodes, int pos )
{
    int n = nodes.size();
    if ( pos >= n || nodes[pos] )
        return;
    nodes[pos] = 1;
    int leftchild  = 2 * pos + 1; 
    int rightchild = 2 * pos + 2; 
    if ( leftchild < n && nodes[leftchild] == 0 )      // set left child 
    {
        setbit_down( nodes, 2*pos+1 );
    }
    if ( rightchild < n && nodes[rightchild] == 0 )
    {
        setbit_down( nodes, 2*pos+2 );
    }
}

// check if we need to set parent's 
void setbit_up( vector<int> &nodes, int pos ) 
{
    int n = nodes.size();
    int parent  = GetParent( pos );
    int sibling = GetBuddy( pos);
    if ( sibling < 0 || nodes[sibling] == 0 )      // the sibling of root (0) is -1 or sibling is not set, then we are done 
        return; 
    // we alread set pos before entering setbit_up, since we first set it down 
    nodes[parent] = 1;
    setbit_up( nodes, parent);
}

// When clearing a bit, we have several options regarding clearing its children without compromising the 
// said properties. We clear both, which will lead the whole subtree rooted at pos to be cleared. 
// Or we can always lear the left or the right, or randomize left or right. 
// In this implementation, I choose to clear always left 
void clearbit_down( vector<int> &nodes, int pos )
{
    int n = nodes.size();
    if ( nodes[pos] == 0 )
        return;
    nodes[pos] = 0;
    int left = 2 * pos + 1;
    while ( left < n ) 
    {
        nodes[left] = 0;
        left = left * 2 + 1;
    }
}

void clearbit_up( vector<int> &nodes, int pos )
{
    int parent;
    while ( pos > 0 )
    {
        parent = GetParent( pos );
        if ( nodes[parent] == 0 )
            break;
        nodes[parent] = 0;
        pos = parent;
    }
}

void set_bits( vector<int> &nodes, int offset, int len )
{
    for ( int i = offset; i < min((int)nodes.size(),(int)(offset+len)); i++ )
    {
        setbit_down( nodes, i );
        setbit_up( nodes, i );
    }
}

void clear_bits( vector<int> &nodes, int offset, int len )
{
    for ( int i = offset; i < min((int)nodes.size(),(int)(offset+len)); i++ )
    {
        clearbit_down( nodes, i );
        clearbit_up( nodes, i );
    }
}

void print_nodes( const vector<int> nodes )
{
    cout << "[";
    for( int i = 0; i < nodes.size() - 1; i++ )
        cout << nodes[i] <<",";
    cout << nodes[nodes.size()-1];
    cout << "]" << endl;
}

int main()
{
    const vector<int> nodes{0,0,1,1,0,1,1,1,1,1,0,1};
    vector<int> tmp;
    int offset, len; 
    srand(time(NULL));
    offset = rand() % (nodes.size());
    len    = rand() % (nodes.size() - offset);
    tmp = nodes;
    cout << "Complete binary tree is " << endl;
    print_nodes(tmp);
    cout << "After set bit from " << offset << " for " << len << " bits" << endl;
    set_bits( tmp, offset, len );
    print_nodes( tmp );
    tmp.clear();
    tmp = nodes; 
    print_nodes( tmp );
    cout << "After clear bit from " << offset << " for " << len << " bits" << endl;
    clear_bits( tmp, offset, len );
    print_nodes( tmp );
    cout << endl;
}