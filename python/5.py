import random
n = int(input())
a = []
for i in range(n):
    a.append([])
    for j in range(n):
        a[i].append(random.randint(-20,20)) 
for i in range(n):
    for j in range(n):
        print(a[i][j], end='  ')
    print()    
average = 0.0
average_k = 0
i = 1
j = 0
for i in range(n):
    for j in range(i-1):
        if a[i][j] < 0:
            average = average + a[i][j]
            average_k = average_k + 1
average = average / average_k
print('среднее ариф отриц элементов = ', average)
average_main=0.0
for i in range(n):
    average_main = average_main + a[i][i]
average_main = average_main / n
print('среднее ариф главной диагонали = ', average_main)
