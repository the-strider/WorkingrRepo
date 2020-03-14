'''input
6 13
4 5 0 2 3 1 
4 5 2 0 3 1 
4 5 2 3 0 1 
4 5 2 3 1 0 
5 2 3 4 0 1 
5 2 3 4 1 0 
5 2 4 0 3 1 
5 2 4 3 0 1 
5 2 4 3 1 0 
5 4 0 2 3 1 
5 4 2 0 3 1 
5 4 2 3 0 1 
5 4 2 3 1 0 
'''

l = list(map(int, input().strip().split()))
n, m = l[0], l[1]
print(n, m)
for i in range(m):
	l = list(map(int, input().strip().split()))
	l = [x + 1 for x in l]
	print(*l)