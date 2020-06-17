#include <iostream>
#include <vector>
using namespace std;

string convertUnit( int num );

string numberToWords(int num) {
    string res = convertUnit( num % 1000 );
    vector<string> highunits = { "Thousand", "Million", "Billion"};
    int i = 0; 
    while ( num /= 1000 ) {
        res = num % 1000 ? convertUnit(num % 1000) + " " + highunits[i] + " " + res: res; 
        i++;
    }
    
    while ( res.back() == ' ' ) 
        res.pop_back();
    return res.empty() ? "Zero" : res;
}

// Handle a group of at most three digits
string convertUnit( int num ) {
    vector<string> lessthan20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    vector<string> morethan20lessthanhundred = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    string res; 
    int hundreds = num / 100, tens = num % 100, ones = num % 10; 
    res = tens < 20 ? lessthan20[tens] : morethan20lessthanhundred[tens/10] + ( ones ? " " + lessthan20[ones] : "");
    if ( hundreds > 0 ) {
        res = lessthan20[hundreds] + " Hundred" + ( tens ? " " + res : "");
        return res;
    }
    
    return res;
}

int main()
{
    int num = 1234534;
    string res = numberToWords(num);
    cout << "Number " << num << " is read as " << res << endl;
}