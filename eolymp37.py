#
#https://basecamp.eolymp.com/en/problems/37
#Mail of Sponsor
#
#Input
#First line contains three integers — the number of post offices n (1≤n≤10^5),
# the number of post office the sponsor uses s (1≤s≤n) 
# and the number of links between the pairs of offices k (0≤k≤10^5).
#
#Each of the next k lines contains two numbers: a and b — the numbers of post offices, 
# between which the mail transportation exists 
#  (a and b are different numbers from interval [1;n]). 
#   All the pairs (a,b) are different.
#
#Output
#Print one number — the minimum possible number of new connections to be created, 
# so that the mail can be delivered from s to any other post office.
#
#Examples
#Input #1
#5 1 4
#1 2
#2 3
#1 3
#4 5
#Answer #1
#1
#

import sys
stack=[];

def dfs(node):
    stack.append(node) 
    while(len(stack)!=0):
       top=len(stack)-1 
       node=stack[top]
       if visited[node]:
          stack.pop()
       else: 
         visited[node] = True
         for neighbor in adj[node]:
             if not visited[neighbor]:
                stack.append(neighbor)  


n, s, k = map(int, input().split())

adj = [[] for _ in range(n + 1)]
visited = [False] * (n + 1)

for _ in range(k):
    a, b = map(int, input().split())
    adj[a].append(b)
    adj[b].append(a)

c = 0
for node in range(1, n + 1):
    if not visited[node]:
        c += 1
        dfs(node)

print(c - 1)