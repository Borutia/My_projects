data = []
sum = 0
with open('1.dat') as f:
    for line in f:
        for x in line.split():
            data.append(int(x))
n = len(data)
print(data)
for i in data:
    if i > n:
        sum = sum + i
print('sum = ' + str(sum))
