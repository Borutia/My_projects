import timeit

reps = 10000
repslist = list(range(reps))

def forLoop():
    res = []
    for x in repslist:
        res.append(abs (x))
    return res

def listComp():
    return [abs(x) for x in repslist]

def mapCall():
    return list(map(abs, repslist))

def genExpr ():
    return list(abs(x) for x in repslist)

def genFunc () :
    def gen():
        for x in repslist:
            yield abs(x)
    return list (gen () )

print(min(timeit.repeat(stmt=mapCall, number=1000, repeat=5)))
