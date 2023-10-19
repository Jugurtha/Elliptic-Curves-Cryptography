import matplotlib.pyplot as plt
import pandas as pd

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
