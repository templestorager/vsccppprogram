// A classical user-defined arithmetic type of "complex" 
class complex {
    double re, im;
public:
    complex(double r, double i) : re(r), im(i){}
    complex(double r ) : re(r), im{0}{}
    complex():re{0}, im{0} {}
    double real() const { return re; }
    void real( double d ) { re = d; }
    double image() const { return im; }
    void image( double i ) { im = i; }
    complex& operator+= (complex z) { re+=z.re, im+=z.im; return *this; }
    complex& operator-= ( complex z) { re-=z.re, im-=z.im; return *this; }
    complex& operator*= ( complex );
    complex& operator/= (complex);

};