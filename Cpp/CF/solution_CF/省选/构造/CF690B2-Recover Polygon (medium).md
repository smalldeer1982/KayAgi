# Recover Polygon (medium)

## 题目描述

Now that Heidi has made sure her Zombie Contamination level checker works, it's time to strike! This time, the zombie lair is a strictly convex polygon on the lattice. Each vertex of the polygon occupies a point on the lattice. For each cell of the lattice, Heidi knows the level of Zombie Contamination – the number of corners of the cell that are inside or on the border of the lair.

Given this information, Heidi wants to know the exact shape of the lair to rain destruction on the zombies. Help her!

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF690B2/2c935730d8a3e2a07073e9f21e778227fe9ea585.png)

## 说明/提示

It is guaranteed that the solution always exists and is unique. It is guaranteed that in the correct solution the coordinates of the polygon vertices are between $ 2 $ and $ N-2 $ . A vertex $ (x_{1},y_{1}) $ is lexicographically smaller than vertex $ (x_{2},y_{2}) $ if $ x_{1}<x_{2} $ or ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF690B2/d2bfbe49d551bf0cc9cbeba8f0c1469bad61d202.png).

## 样例 #1

### 输入

```
8
00000000
00000110
00012210
01234200
02444200
01223200
00001100
00000000
5
00000
01210
02420
01210
00000
7
0000000
0122100
0134200
0013200
0002200
0001100
0000000
0
```

### 输出

```
4
2 3
2 4
6 6
5 2
4
2 2
2 3
3 3
3 2
3
2 5
4 5
4 2
```

# 题解

## 作者：千早爱音 (赞：0)

因为给定的图形是一个凸多边形，所以会存在一些格点，周围的四个格子中至少有一个为 $ 1 $ 且没有格子为 $ 0 $。如果周围有格子为 $ 0 $，则说明这个点并不位于这个多边形上。如果周围格子都不为 $ 1 $，则说明这个点在这个多边形内部，忽略。剩下的这些格点都会位于多边形的边界或者顶点。

于是考虑找出所有这样的点之后求出凸包，判断这些点是位于顶点还是边界，之后按照题目要求输出即可。

时间复杂度：二维凸包的时间复杂度是 $ \mathcal{O}(n\log{n}) $ 的，求出所有这样点的复杂度是 $ \mathcal{O}(n^2) $ 的，所以总时间复杂度为 $ \mathcal{O}(n^2) $，可以通过。

代码：

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct node
{
    int x,y;
}p[500005],q[500005];
int n,m,a[505][505];
char s[505]; 
inline ll check(node a,node b,node c)
{
    return (ll)(a.x-b.x)*(ll)(c.y-b.y)-(ll)(a.y-b.y)*(ll)(c.x-b.x);
}
inline bool cmp(node a,node b)
{
    if(a.x!=b.x) 
    return a.x<b.x;
    return a.y<b.y;
}
int main()
{
    while(1)
    {
    	cin>>n;
        m=0;
    	if(!n) 
        return 0;
    	for(int i=n;i;i--)
        {
    		scanf("%s",s+1);
    		for(int j=1;j<=n;j++)
    			a[i][j]=s[j]-'0';
    	}
    	bool isok=0;
    	if(a[1][1]==4) 
        p[++m]=(node){0,0},a[1][1]--;
    	for(int i=1;i<=n;i++)
    		if(a[1][i]==4||a[1][i]==3)
            {
    			p[++m]=(node){0,i};
    			a[1][i]--;
    			a[1][i+1]--;
    		}
    	for(int i=1;i<=n;i++)
        {
    		int id=0;
    		for(int j=1;j<=n;j++)
    			if(a[i][j])
                {
                id=j;
                break;
                }
    	if(a[i][id]>1)
        {
    		p[++m].x=i;p[m].y=id-1;
    		a[i][id]--;
    	}
    	for(int j=id;j<=n;j++)
        {
    		if(!a[i][j]) 
            break;
    		p[++m].x=i,p[m].y=j;
    		a[i][j]--;a[i][j+1]--;
    		a[i+1][j]--;a[i+1][j+1]--;
    	}
    }
    for(int i=1;i<=m;i++) 
    swap(p[i].x,p[i].y);
    sort(p+1,p+m+1,cmp);
    int tot=0,t=1;
    q[1]=p[1],q[2]=p[2];
    tot=2;
    for(int i=3;i<=m;i++)
    {
    	while(tot>t&&check(q[tot-1],q[tot],p[i])<=0) 
        tot--;
    	q[++tot]=p[i]; 
    }
    t=tot;
    q[++tot]=p[m-1];
    for(int i=m-2;i;i--)
    {
    	while(tot>t&&check(q[tot-1],q[tot],p[i])<=0)
        tot--;
    	q[++tot]=p[i]; 
    }
    printf("%d\n",tot-1);
    for(int i=1;i<tot;i++) 
    printf("%d %d\n",q[i].x,q[i].y);
    }
}
```


---

