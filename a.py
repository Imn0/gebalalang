#Bartek Łabuz
#pragma test in() out()
def plus_i_minus(u, v,  w) :

    for i in range(1, 100+1):
        u = u + i
        v = v - i
        s = i * i
        w[5] = i + w[5]
        w[5] = w[5] + s
    print(u)
    print(v)
    print(w[5])

if __name__ == "__main__":
    z = {}
    x = 456;
    y = 123;
    z[5] = 789
    plus_i_minus(x, y, z)