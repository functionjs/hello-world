N, D = map(int, input().split())
A, B = map(int, input().split())
M = [int(x) for x in input().split()]


M.sort()
extra = M[:N - A]
del M[:N - A]

profit = 0
entered = False

for i in range(D):
    if max(M) - min(M) <= 1 or (max(M) - (sum(M) - max(M))/(A - B)) < (D - i):
        entered = True
        currentMilk = sum(M)
        additionalMilk = (D - i) * (A - B)
        totalMilk = currentMilk + additionalMilk
        numOfLargerBottles = totalMilk % A
        numOfSmallerBottles = A - numOfLargerBottles
        profit = numOfSmallerBottles * (totalMilk // A)**2 + numOfLargerBottles * ((totalMilk // A) + i)**2
        break
    for j in range(A - B):
     M[j] += 1
    M.sort()

MOD = 10**9 + 7
for i in range(N - A):
    profit += extra[i]**2
    profit %= MOD
if not entered:
    for i in range(A):
        profit += M[i]**2
        profit %= MOD

print(profit)

'''
5 4
4 2
4 10 8 10 10
---
546
---
10 5
5 1
1 2 3 4 5 6 7 8 9 10
---
777
---
5 1000000000
3 1
0 1 2 3 4
---
10
'''