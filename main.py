import matplotlib.pyplot as plt
import pandas as pd
from tinyec.ec import SubGroup, Curve

def generate_curve(a, b, p):
    curve = {
        'X' : [],
        'Y' : []
    }
    for x in range(p):
        for y in range(p):
            if (( y**2 - (x**3 + a*x + b) ) % p) == 0:
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
