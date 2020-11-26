import math
x = [-0.98,-0.5,0.1,0.5,0.95]
eps = float(input('eps =' ))
i = 0
def toFixed(numObj, digits=0):
    return f"{numObj:.{digits}f}"
print('№        X        S(x)       K        F(x)       |S(x)-F(x)|')
while i < 5:
    s = (1.0/4.0)*x[i]
    k = 2.0
    zn = 1.0
    ch = 1.0
    good_s = 1 - (1/(math.pow(1+x[i],1/4)))
    while s > eps:
        zn = zn * 4.0 * k
        ch = ch * (4.0 * k - 3.0)
        if k % 2 != 0:
            s = s - (((ch)/(4.0*zn))*(math.pow(x[i],k)))
        else:
            s = s + (((ch)/(4.0*zn))*(math.pow(x[i],k)))
        k = k+1.0
    print(i+1,'   ',x[i],'   ',toFixed(s,2),'   ',k,'   ',toFixed(good_s,2),'   ',toFixed(math.fabs(s-good_s),2))
    i = i + 1
