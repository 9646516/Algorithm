def mul(a,b):
    return a[0]*b[1]-b[0]*a[1]
ct=1
n=int(input())
while n:
    a=[list(map(int,input().split())) for i in range (n) ]
    a.append(a[0])
    sz=len(a)
    S=x=y=0.0
    for i in range(sz-1):
        m=mul(a[i],a[i+1])
        S+=m
        x+=(a[i][0]+a[i+1][0])/3.0*m
        y+=(a[i][1]+a[i+1][1])/3.0*m
    print("Stage #%d: %f %f" %(ct,x/S,y/S))
    ct+=1
    n=int(input())