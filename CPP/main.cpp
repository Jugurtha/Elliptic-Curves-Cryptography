#include <iostream>
#include "Integer.h"
#include "EllipticCurve.h"

using namespace std;





int main()
{
    const size_t N = 16;
    Integer<N> n(1);
    for(int i = 0; i<25; i++)
        cout << n << " + " << i << " = " << n + i << endl;
    cout << "\n";

    for(Integer<N> v(0); v< Integer<N>(25); v++)
        cout <<"v = " << v << endl;
    cout << "\n";

    for(int i = 0; i<5; i++)
        cout << n << " - " << i << " = " << n - i << endl;
    cout << "\n";

    Integer<N> k(2);
    cout << k << " * " << Integer<N>(-3) << " = " << k * Integer<N>(-3) << endl;
    cout << "\n";

    for(Integer<N> i(0); i<5; i++)
        cout << k << " * " << i << " = " << k * i << endl;
    cout << "\n";

    Integer<N> j(120);
    for(Integer<N> i(1); i<6; i++)
        cout << j << " / " << i << " = " << j / i << endl;
    cout << "\n";

    Integer<N> l(10);
    for(Integer<N> i(1); i<6; i++)
        cout << l << " % " << i << " = " << l % i << endl;
    cout << "\n";

    Integer<N> a(3), b(-2);
    for(Integer<N> i(1); i<6; i++)
        cout << i << " * " << b << " = " << i * b << endl;
    cout << "\n";

    cout << " - " << a << " = " << -a << endl;
    cout << "\n";

    Integer<N> p(13);
    for(Integer<N> i(1); i<13; i++)
        cout << i << " inverse mod " << p << " = " << i.inverseModP(p) << endl;
    cout << "\n";

    p = 5;
    for(Integer<N> i(1); i<13; i++)
        cout << i << " reduced mod " << p << " = " << i.reduced(p) << endl;
    cout << "\n";

    cout << Integer<N>(-14) << " reduced mod " << p << " = " << Integer<N>(-14).reduced(p) << endl;
    cout << "\n";

    int ix(0), iy(0);
    Integer<N> x(ix), y(iy);

    cout << ix << " = " << x << endl;
    cout << iy << " = " << y << endl;

    if(x < y)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    if(x <= y)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    if(x > y)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    if(x >= y)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    //cout << bitset<N>(0)[N-1];

    Point<N> P(15, 13,0,17);
    Point<N> Q(15, 13,0,17);
    cout << P << " + " << Q << " = " << P + Q<< endl;
    Point<N> S(2,10,0,17);
    cout << P << " + " << S << " = " << P + S<< endl;

    Point<N> G(15, 13,0,17);
    for(int i(0); i<25; i++)
        cout << i << " * " << G << " = " << Integer<N>(i)*G << endl;
    cout << "\n\n";

    Point<N> G1(15, 13,0,17);
    EllipticCurve<N> E(0, 7, 17, 25, 10, G1);
    cout <<  "E.isOnCurve(G1) = " <<  E.isOnCurve(G1) << endl;

    Point<N> G2(string("0xf"), string("0xd"),0,string("0x11"));
    EllipticCurve<N> E1(0, string("0x7"), string("0x11"), 25, 10, G1);
    cout << "E1.isOnCurve(G2) = " <<  E1.isOnCurve(G2) << endl;

    cout << "\n\n";

    const size_t M = 224 *4;
    Point<M> G0(
                string("0x0 b70e0cbd 6bb4bf7f 321390b9 4a03c1d3 56c21122 343280d6 115c1d21"),
                string("0x0 bd376388 b5f723fb 4c22dfe6 cd4375a0 5a074764 44d58199 85007e34"),
               string("0xf  ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff fffffffd"),
               string("0x0  ffffffff ffffffff ffffffff ffffffff 00000000 00000000 00000001"));
    cout << "G0 = " << G0 << endl;
    cout << "\n\n";
    EllipticCurve<M> P224(
                            string("0xf  ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff fffffffd"),
                            string("0x0  b4050a85 0c04b3ab f5413256 5044b0b7 d7bfd8ba 270b3943 2355ffb4"),
                            string("0x0  ffffffff ffffffff ffffffff ffffffff 00000000 00000000 00000001"),
                            string("0x0  ffffffff ffffffff ffffffff ffff16a2 e0b8f03e 13dd2945 5c5c2a3d"),
                            1,
                            G0);
    cout <<  "P224.isOnCurve(G0) = " <<  P224.isOnCurve(G0) << endl;
/*
    for(int i(0); i<25; i++)
        cout << i << " * " << G0 << " = " << Integer<M>(i)*G0 << endl;
    cout << "\n";
//*/
    cout <<  "1  * G0  ==  G0 : "; cout << ((Integer<M>(1)*G0) == G0) << endl;

/*
    auto F = ((Integer<M>(string("0x0  ffffffff ffffffff ffffffff ffff16a2 e0b8f03e 13dd2945 5c5c2a3d")) - 1)*G0);
    cout <<  "(n - 1)  * G0  ==  G0 : "; cout << F << endl;
    cout <<  "P224.isOnCurve(F) = " <<  P224.isOnCurve(F) << endl;
//*/
    return 0;
}
