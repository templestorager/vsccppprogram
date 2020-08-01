template<typename T>
class Less_than {
    const T val;
public:
    Less_than( const T& v) : val(v){}
    bool operator()(const T& x) const { return x < val; }
};

// count the occurences having predicate P being true in the given container 
template<typename C, typename P>
int count(const C& c, P pred)
{
    int cnt = 0;
    for ( const auto& x : c )
        if ( pred(x) )
            ++cnt;
    return cnt;
}
