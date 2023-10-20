import matplotlib.pyplot as plt
import pandas as pd
from tinyec.ec import SubGroup, Curve
import Elliptic_Curve as EC


def generate_curve(a, b, p):
    curve = {
        'X': [],
        'Y': []
    }
    for x in range(p):
        for y in range(p):
            if ((y ** 2 - (x ** 3 + a * x + b)) % p) == 0:
                curve['X'].append(x)
                curve['Y'].append(y)
    return curve


if __name__ == '__main__':
    df = pd.DataFrame(generate_curve(0, 7, 17))
    plt.scatter(df['X'], df['Y'])
    plt.grid()
    plt.show()

    field = SubGroup(p=17, g=(15, 13), n=18, h=1)
    curve = Curve(a=0, b=7, field=field, name='p1707')
    print('curve:', curve)

    for k in range(0, 25):
        p = k * curve.g
        print(f"{k} * G = ({p.x}, {p.y})")

    p = 26959946667150639794667015087019630673557916260026308143510066298881
    a = -3
    b = 18958286285566608000408668544493926415504680968679321075787234672564

    Gx = 19277929113566293071110308034699488026831934219452440156649784352033
    Gy = 19926808758034470970197974370888749184205991990603949537637343198772
    G = (Gx, Gy)
    n = 26959946667150639794667015087019625940457807714424391721682722368061
    h = 1
    P224 = EC.EllipticCurve(a, b, p, G, n, h)
    # as specified in https://doi.org/10.6028/NIST.SP.800-186
    print("\n-------------------------------------------\n")
    print(P224.is_point_on_curve(Gx, Gy))# Verify G in curve

    Q = P224.multiply(1, G)# Verify 1*G in curve
    print(Q == G)

    Q = P224.multiply(n - 1, G)# Verify (n-1)G in curve
    print(Q)
    print(P224.is_point_on_curve(Q[0], Q[1]))

    Q = P224.multiply(n, G)# Verify nG is Infinity point
    print(Q == EC.INFINITY)
