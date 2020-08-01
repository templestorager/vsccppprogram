#include <iostream>
struct Entry{
    std::string name;
    int age;
};

ostream& operator<< (ostream& os, const Entry &e )
{
    return os << "{\"" << e.name << "\"," << e.age << "}";
}

istream& operator>>(istream& is, Entry &e )
{
    char c, c2;
    if ( is >> c && c == '{' && is >> c2 && c2 == '"' ) {
        string name;
        while ( is.getc(c) && c != '"' )
            name += c;
    
        if ( is >> c && c == ',' ) {
            int number = 0;
            if ( is >> name >> c && c == '}' ) {
                e = {name, number};
                return is;
            }
        }
    }

    is.setf(ios_base::failbit);
    return is;
}