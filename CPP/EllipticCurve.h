#ifndef ELLIPTICCURVE_H_INCLUDED
#define ELLIPTICCURVE_H_INCLUDED

#include "Point.h"

template<size_t N>
class EllipticCurve
{
private:
    Integer<N> a;
    Integer<N> b;
    Integer<N> p;
    Integer<N> n;
    Integer<N> h;
    Point<N> G;
public:
    EllipticCurve(Integer<N> a, Integer<N> b, Integer<N> p, Integer<N> n, Integer<N> h, Point<N> G): a(a), b(b), p(p), n(n), h(h), G(G){};
    bool isOnCurve(Point<N> const& P)
    {
        if(P.getInfinity())
            return true;
        else
        {
            return (P.getY()*P.getY()).reduced(p) == ((P.getX()*P.getX()*P.getX()) + a*P.getX() + b).reduced(p);
        }
    }

};
#endif // ELLIPTICCURVE_H_INCLUDED
