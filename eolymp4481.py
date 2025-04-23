
#https://basecamp.eolymp.com/en/problems/4481
#https://basecamp.eolymp.com/en/problems/4481#editorial
#In the Country of Unlearned Lessons
#Input
#The first line contains the number of elements n (1≤n≤10^5) in array. 
#The second line contains n integers — the elements a_i (1≤a_i≤10^9 )of array. 
#The third line gives the number of queries m (1≤m≤10^5).
#Each of the next m lines contains three integers q,l,r (1≤l≤r≤n).
#
#If q=1, find the GCD of elements on an interval [l,r];
#If q=2, change the element at position l to number r.
#
#Output
#For each query with number 1 print the answer on a separate line.
#
#Examples
#Input #1
#5
#2 4 6 10 8
#6
#1 1 5
#1 2 3
#2 5 15
#2 3 10
#1 3 5
#1 1 5
#Answer #1
#2
#2
#5
#1
#*/
import math
import sys

SegTree = []
H = 0

def buildTree(v, lpos, rpos):
    if v >= H // 2:
        return
    mid = (lpos + rpos) // 2
    buildTree(2 * v, lpos, mid)
    buildTree(2 * v + 1, mid + 1, rpos)
    SegTree[v] = math.gcd(SegTree[2 * v], SegTree[2 * v + 1])

def getGCD(v, lpos, rpos, left, right):
    if left > right:
        return 0
    if left == lpos and right == rpos:
        return SegTree[v]
    mid = (lpos + rpos) // 2
    return math.gcd(
        getGCD(2 * v, lpos, mid, left, min(right, mid)),
        getGCD(2 * v + 1, mid + 1, rpos, max(left, mid + 1), right)
    )

def QueryGCD(l, r):
    return getGCD(1, 1, H // 2, l, r)

def update(v, lpos, rpos, pos, val):
    if lpos == rpos:
        SegTree[v] = val
    else:
        mid = (lpos + rpos) // 2
        if pos <= mid:
            update(2 * v, lpos, mid, pos, val)
        else:
            update(2 * v + 1, mid + 1, rpos, pos, val)
        SegTree[v] = math.gcd(SegTree[2 * v], SegTree[2 * v + 1])

def changeValue(pos, new_val):
    update(1, 1, H // 2, pos, new_val)


#f=1;
#for i in range(1,101):
#    f *=i
#    print(f) 

data = sys.stdin.read().split()
#print(data)
i=0
n= int(data[i])
i+=1
#print (n)
h = int((math.ceil(math.log2(n))+1)); # segTree height
H = 2**h;                             #  segTree volume
neutral_element =0                    # neutral element for gcd
SegTree =[neutral_element]*H;
#print(SegTree) 
for k in range(n):
  SegTree[H//2+k]=int(data[i])
  i+=1 
#print(SegTree)   
buildTree(1, 1, H/2);       # build segTree upper nodes 
#print(SegTree) 

m = int(data[i])
i += 1

for _ in range(m):
    q = int(data[i])
    l = int(data[i + 1])
    r = int(data[i + 2])
    i += 3
    if q == 1:
        print(QueryGCD(l, r))
    else:
        changeValue(l, r)