#Primes
#https://basecamp.eolymp.com/en/problems/3843
#Execution time limit is 10 seconds
#
#Runtime memory usage limit is 256 megabytes
#Let m and n (2<=m<n<=10^7) be two integers. 
#
#Consider the following set:
#Prime(m,n) = { p | p prime and m<=p<=n }.
#
#Find the cardinality of the set Prime(m,n).
#
#Input
#Consists of several tests. 
#The input of each test is represented on a single line. 
#Any two consecutive tests are separated by an empty line. 
#For each test, the values for m and n are given on the same line, 
#separated by exactly one space.
#
#Output
#For each test, the result will be written on a different line 
#(the tests will have the same order as in the input). 
#The results of any two consecutive tests will be separated by an empty line. 
#For each test, the result will be the cardinal of the set Prime (m,n).
#
'''
Examples
Input1
4 12

70 110

5 150
Answer1
3

10

33
'''
import time
import sys
import math

Max = 10**7
notP = [False for _ in range(Max + 1)] # not Prime: default notP[x]=False :  all x are primes by default
M = [False for _ in range(Max + 1)]  # Memorized: default M[x]=False
prefixSum = [0 for _ in range(Max + 1)]


def initBySieveOfEratosthenes():
    notP[0] = True
    M[0] = True
    notP[1] = True
    M[1] = True
    
    notP[2] = False
    M[2] = True
    for i in range(2*2, Max+1, 2):
        notP[i] = True
        M[i] = True
    q = int(math.sqrt(Max))
    for x in range(3, q+1, 2):
        if M[x]: continue
        M[x] = True
        for i in range(x*x, Max + 1, 2*x):
            notP[i] = True
            M[i] = True

def evaluatePrefixSum():
    for x in range(2, Max + 1):
        prefixSum[x] = prefixSum[x - 1] + (not notP[x])


def cardinalityOfPrimes(m, n):
    c = not notP[m]
    c += prefixSum[n] - prefixSum[m]
    return c    

def oldcardinalityOfPrimes(m, n):
    c = 0
    for x in range(m,n+1):
       c += not notP[x]
    return c        

t0 =  time.perf_counter()
initBySieveOfEratosthenes()
#t1 = time.perf_counter()
#evaluatePrefixSum()
#t2 = time.perf_counter()
#print("initBySieveOfEratosthenes() time=", (t1 - t0), "s\n")
#print("evaluatePrefixSum() time=", (t2 - t1), "s\n")

data = sys.stdin.read()
lines = data.split("\n")
for l in lines:
    if len(l)==0 : continue
    m, n = map(int, l.split())
    print(oldcardinalityOfPrimes(m, n),"\n")

t1 = time.perf_counter()
print("Time: ", (t1 - t0), "s\n")     

