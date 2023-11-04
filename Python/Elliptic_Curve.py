INFINITY = None


class EllipticCurve:
    def __init__(self, a, b, p, G, n, h):
        self.a = a
        self.b = b
        self.p = p
        self.G = G
        self.n = n
        self.h = h

    def add(self, P, Q):
        if P == INFINITY:
            return Q
        if Q == INFINITY:
            return P

        (x1, y1) = P
        (x2, y2) = Q

        # If we add points symmetrical with respect to Y-axis
        if self.equal_modp(x1, x2) and self.equal_modp(y1, -y2):
            return INFINITY

        # Calculation slope for:
        # Point doubling
        if self.equal_modp(x1, x2) and self.equal_modp(y1, y2):
            u = self.reduce_modp((3 * x1 * x1 + self.a) * self.inverse_modp(2 * y1))
        # Point addition
        else:
            u = self.reduce_modp((y1 - y2) * self.inverse_modp(x1 - x2))

        v = self.reduce_modp(y1 - u * x1)
        x3 = self.reduce_modp(u * u - x1 - x2)
        y3 = self.reduce_modp(-u * x3 - s)
        return x3, y3

    def multiply(self, k, P):
        # Double and add algorithm from least significant bit to most significant bit
        Q = INFINITY
        while k != 0:
            if k & 1 != 0:
                Q = self.add(Q, P)
            P = self.add(P, P)
            k >>= 1
        return Q

    def reduce_modp(self, x):
        return x % self.p

    def equal_modp(self, x, y):
        return self.reduce_modp(x - y) == 0

    def inverse_modp(self, x):
        if self.reduce_modp(x) == 0:
            return None
        return pow(x, self.p - 2, self.p)#From Fermat's therorem supposing p is prime

    def is_point_on_curve(self, x, y):
        return self.equal_modp(y * y, x * x * x + self.a * x + self.b)