#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include "Integer.h"

template<size_t N>
class Point
{
    private:
    Integer<N> x;
    Integer<N> y;
    const Integer<N> a;
    const Integer<N> p;
    bool infinity = false;

    public:
    Point(Integer<N> x, Integer<N> y, Integer<N> a, Integer<N> p):x(x), y(y), a(a), p(p){};
    string to_string()const;
    Integer<N> const& getX() const {return x;};
    Integer<N> const& getY() const {return y;};
    bool const& getInfinity() const {return infinity;};



    //Point Addition:
    Point<N> & operator+=( Point<N> const & rhs );
    template<size_t M>
    friend Point<M> operator+(Point<M> const& P, Point<M> const& O);

    //Point Multiplication:
    Point<N> & operator*=( Integer<N> rhs );
    template<size_t M>
    friend Point<M> operator*(Integer<M> const& n, Point<M> const& P);

    //Equality
    template<size_t M>
    friend bool operator==( Point<M> const & lhs, Point<M> const & rhs );

    //Inequality
    template<size_t M>
    friend bool operator!=( Point<M> const & lhs, Point<M> const & rhs );
};

//Point Addition:
template<size_t N>
Point<N> & Point<N>::operator+=( Point<N> const & rhs )
{
    //cout  << endl;
    if(infinity)
    {
        x = rhs.x;
        y = rhs.y;
        infinity = false;
        return *this;
    }
    if(rhs.infinity)
        return *this;

    auto x1 = x.reduced(p);
    auto y1 = y.reduced(p);
    auto x2 = rhs.x.reduced(p);
    auto y2 = rhs.y.reduced(p);

    if((x1 == x2) && (y1 == (-y2).reduced(p)))
    {
        infinity = true;
        return *this;
    }

    Integer<N> u(0), two(2), three(3);
    if( (x1 == x2) && (y1 == y2))
    {
        u = ((three * x1 * x1 + a) * (two * y1).inverseModP(p)).reduced(p);
    }
    else
    {
        u = ((y1 - y2) * (x1 - x2).inverseModP(p)).reduced(p);
    }



    auto v = (y1 - u * x1).reduced(p);

    x = (u * u - x1 - x2).reduced(p);

    y = (-u * x - v).reduced(p);

    return *this;

}
template<size_t M>
Point<M> operator+(Point<M> const& P, Point<M> const& O)
{
    auto tmp(P);
    tmp += O;
    return tmp;
}

//Point Multiplication:
template<size_t N>
Point<N> & Point<N>::operator*=( Integer<N> k )
{
    Point<N> Q(0,0,a,p);
    auto & P = *this;
    Q.infinity = true;
    Integer<N> zero(0), one(1);
    if(k == zero)
    {
        x = Q.x;
        y = Q.y;
        infinity = Q.infinity;
        return *this;
    }

    while(k != zero)
    {
        if((k & one) != zero)
        {
            Q += P;
        }
        P += P;
        k >>= 1;
    }

    x = Q.x;
    y = Q.y;
    infinity = Q.infinity;
    return *this;
}
template<size_t M>
Point<M> operator*(Integer<M> const& n, Point<M> const& P)
{
    auto tmp(P);
    tmp *= n;
    return tmp;
}
template<size_t M>
Point<M> operator*(Point<M> const& P, Integer<M> const& n)
{
    auto tmp(P);
    tmp *= n;
    return tmp;
}

//Equality
template<size_t M>
bool operator==( Point<M> const & lhs, Point<M> const & rhs )
{
    if(lhs.infinity || rhs.infinity)
        return lhs.infinity == rhs.infinity;

    return (lhs.a == rhs.a) && (lhs.p == rhs.p) && (lhs.x.reduced(lhs.p) == rhs.x.reduced(lhs.p)) && (lhs.y.reduced(lhs.p) == rhs.y.reduced(lhs.p));
}

//Inequality
template<size_t M>
bool operator!=( Point<M> const & lhs, Point<M> const & rhs )
{
    return ! (lhs == rhs);
}

template<size_t N>
string Point<N>::to_string()const
{
    if(infinity)
        return "Infinity";
    return "(" + (infinity?string("Infinity"):x.to_string())+", " +(infinity?string("Infinity"):y.to_string())+")";
};

template<size_t N>
std::ostream& operator<<(std::ostream& stream, const Point<N>& p)
{
    return stream << p.to_string();
}


#endif // POINT_H_INCLUDED
