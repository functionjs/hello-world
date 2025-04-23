#https://basecamp.eolymp.com/en/problems/3728
#The undirected graph is given. Two types of operations are performed on graph in the given order:
#cut — cut a graph, or delete an edge from a graph;
#ask — check, whether two given vertices lie in the same connected component.

#It is known that after performing all types of cut operations there is no edges left in the graph. Give the result for each ask operation.

# Input
# The first line contains three integers — the number of vertices n in a graph, 
#  the number of edges m and the number of operations k 
#  (1≤n≤50000,0≤m≤10^5,m≤k≤150000).



# Examples
# Input #1
# 3 3 7
# 1 2
# 2 3
# 3 1
# ask 3 3
# cut 1 2
# ask 1 2
# cut 1 3
# ask 2 1
# cut 2 3
# ask 3 1
# Answer #1
# YES
# YES
# NO
# NO
import sys
# DSU mem and fun
parent=[]
def dsuinit(n):
    parent[:] = list(range(n + 1))

def find(v):
    if parent[v] == v:
        return v
    parent[v] = find(parent[v])
    return parent[v]

def union(v1, v2):
    p1 = find(v1)
    p2 = find(v2)
    if p1 != p2:
        parent[p2] = p1

#input data
n, m, k = map(int, input().split())
[input() for _ in range(m)] #dummy input m lines
queries=[0]*k;
L=0;
for i in range(0,k):
  line=input().split()
  queries[i]=[line[0], int(line[1]), int(line[2])]
  if line[0][0]=="a" : L += 1
#process queries from last to first
dsuinit(n)
ans = [""]*L
l=L-1;
for i in range(k - 1, -1, -1):
    u = queries[i][1]
    v = queries[i][2]
    if queries[i][0][0] == "c": union(u,v)
    else:
        p1 = find(u)
        p2 = find(v)
        ans[l]= (p1 == p2)
        l-=1
#ans normal output
for i in range(0,L):
    if ans[i]: print("YES")     
    else:      print("NO")   