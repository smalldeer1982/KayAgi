# Okabe and City

## 题目描述

Okabe likes to be able to walk through his city on a path lit by street lamps. That way, he doesn't get beaten up by schoolchildren.

Okabe's city is represented by a 2D grid of cells. Rows are numbered from $ 1 $ to $ n $ from top to bottom, and columns are numbered $ 1 $ to $ m $ from left to right. Exactly $ k $ cells in the city are lit by a street lamp. It's guaranteed that the top-left cell is lit.

Okabe starts his walk from the top-left cell, and wants to reach the bottom-right cell. Of course, Okabe will only walk on lit cells, and he can only move to adjacent cells in the up, down, left, and right directions. However, Okabe can also temporarily light all the cells in any single row or column at a time if he pays $ 1 $ coin, allowing him to walk through some cells not lit initially.

Note that Okabe can only light a single row or column at a time, and has to pay a coin every time he lights a new row or column. To change the row or column that is temporarily lit, he must stand at a cell that is lit initially. Also, once he removes his temporary light from a row or column, all cells in that row/column not initially lit are now not lit.

Help Okabe find the minimum number of coins he needs to pay to complete his walk!

## 说明/提示

In the first sample test, Okabe can take the path ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821D/889fb52cd8e59d84c301f0f8e944c8435ec73245.png), paying only when moving to $ (2,3) $ and $ (4,4) $ .

In the fourth sample, Okabe can take the path ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821D/43c065d86f3862fdd168fa32390c7090f0f90d51.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821D/9437e98f5dfee3b86205c3722d844f74591a1a9d.png), paying when moving to $ (1,2) $ , $ (3,4) $ , and $ (5,4) $ .

## 样例 #1

### 输入

```
4 4 5
1 1
2 1
2 3
3 3
4 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 5 4
1 1
2 1
3 1
3 2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
2 2 4
1 1
1 2
2 1
2 2
```

### 输出

```
0
```

## 样例 #4

### 输入

```
5 5 4
1 1
2 2
3 3
4 4
```

### 输出

```
3
```

# 题解

## 作者：Dr_Gears (赞：4)

 首先，此题要开long long；


------------

 其次，k的范围是10000，不是104，可能是因为没处理好排版；
 

------------
~~然后，我不是在水~~


------------
# 进入主题。
题目说的不太清楚，简单来说，就是有k个点，你可以通过自己的能力，利用这  些点从起点到终点。
而能力也很简单，花费1s（~~翻译是真的皮~~）建一条边连接2个点，这两个点的横纵坐标差不能都超过2，也就是说中间最多插一行或一列。所以我们将满足上述条件的点对之间建一条边权为1的边，就没了。
###### 当然
还有相邻的点之间的边，边权为0；
###### 至于那些不满足上述两种条件的点对，之间的边边权为inf
使用spfa，从起点出发，边搜边建边。
# 代码
```c
#include<bits/stdc++.h>
const int inf=0x3f3f3f3f;
const int maxn=1e5+10;
using namespace std;
long long n,m,k,cnt;
long long dis[maxn],vis[maxn],nx[10010],ny[10010];
bool flag;
void spfa(int s)
{
    fill(dis+1,dis+(maxn-20)+1,inf);
    fill(vis+1,vis+(maxn-20)+1,0);
    queue<int> que;
    que.push(s);
    dis[s]=0; 
    vis[s]=1;
    while(!que.empty())
    {
        int x=que.front(); 
        que.pop();
        vis[x]=0;
        for(int i=1;i<=k;i++)
        {
            long long tmp;
            int dx=abs(nx[i]-nx[x]);
            int dy=abs(ny[i]-ny[x]);
            if(dx+dy==1) 
            tmp=0;
            else if(dx<=2||dy<=2) 
            tmp=1;
            else 
			tmp=inf;   
            if(dis[i]>dis[x]+tmp)
            {
                dis[i]=dis[x]+tmp;
                if(!vis[i])
                vis[i]=1;
                que.push(i);
            }
        }
    }
    printf("deep ♂dark♂fantasy\n"); 
}
main()
{
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=k;i++)
    {
    	scanf("%lld%lld",&nx[i],&ny[i]);
    	if(nx[i]==n&&ny[i]==m)
    	flag=true;
    }
    if(!flag)
    {
    k++;
    nx[k]=n+1;
    ny[k]=m+1;
    }
    spfa(1);
    if(dis[k]!=inf)
    printf("%lld",dis[k]);
    else
    printf("-1");
    return 0;
}
```
```
我绝不是哲学家。
```

---

## 作者：EuphoricStar (赞：2)

## 题意

$n$ 行 $m$ 列的网格中有 $k$ 个点，你每次可以从一个点花费 $0$ 块钱到达另一个与它四连通的点。除此之外，你还可以花费 $1$ 块钱从 $(x_1,y_1)$ 到达 $(x_2,y_2)$（需满足 $|x_1-x_2| \le 1$ **或** $|y_1-y_2| \le 1$）。求 $(1,1)$ 到 $(n,m)$ 的最小花费。

## 思路

对于网格中的 $n$ 个行，$m$ 个列和 $k$ 个点在新图上建立一些一一对应的虚点。

那么不难想到建图方式：第 $i$ 个点向第 $r$ 行（$|x_i-r| \le 1$）和第 $c$ 列（$|y_i-c| \le 1$）分别连一条边权为 $1$ 的边，反过来第 $r$ 行和第 $c$ 列向第 $i$ 个点连一条边权为 $0$ 的边（因为点切换到行/列的需要花费 $1$，而从行/列切换到具体的点不需要花费），然后每个点再向与自己四连通的另外的点分别连一条边权为 $0$ 的边。跑最短路即可。

由于图上的边权全都为 $0/1$，因此可以用 01bfs 求最短路。

## 代码

[code](https://pastebin.ubuntu.com/p/PchkF6yBBv/)

---

## 作者：Nero_Claudius (赞：1)

其实，这道题不用long long也能AC。

------------

题意是给你一个矩阵，有一些格子被点亮有一些没有，每一次只能在被点亮的格子上面走。

然后你每一次都可以选择点亮一行或一排（非永久），现在问你最少点多少次可以走到终点？

------------

思路十分好想。

我们把相邻的格子边权设为0，把不相邻但只差一行的格子之间边权设为1。（其他情况都不能直接到达）

然后跑一下SPFA就可以了。

但是需要考虑一个特例：终点有没有被点亮。

如果点了的话那没关系，没点的话得把(n+1,m+1)设为点亮的点。（要不然我们走不到终点不是吗）

------------

AC代码如下：

`11149ms/192kb`

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
namespace StandardIO{
	template<typename T>inline void read(T &x){
		x=0;T f=1;char c=getchar();
		for(;c<'0'||c>'9';c=getchar())if(c=='-')f=-1;
		for(;c>='0'&&c<='9';c=getchar())x=x*10+c-'0';
		x*=f;
	}
	template<typename T>inline void write(T x){
		if(x<0)putchar('-'),x*=-1;
		if(x>=10)write(x/10);
		putchar(x%10+'0');
	}
}
using namespace StandardIO;
namespace Solve{
	const int N=10100;
	const int INF=0x3f3f3f3f;
	int n,m,k;
	struct node{
		int from,to;
	}edge[N];
	int dis[N],vis[N];
	inline int spfa(){
		for(register int i=1;i<=k;++i)dis[i]=INF;
		queue<int>q;q.push(1);
		vis[1]=1,dis[1]=0;
		while(!q.empty()){
			int to=q.front();q.pop();
			vis[to]=0;
			for(register int i=1;i<=k;++i){
				if(to==i)continue;
				int val=INF;
				int dx=abs(edge[to].from-edge[i].from),dy=abs(edge[to].to-edge[i].to);
				if(dx+dy==1)val=0;
				else if(dx<=2||dy<=2)val=1;
				if(dis[i]>dis[to]+val){
					dis[i]=dis[to]+val;
					if(!vis[i]){
						q.push(i),vis[i]=1;
					}
				}
			}
		}
		if(dis[k]!=INF)return dis[k];
		return -1;
	}
	inline void solve(){
		read(n),read(m),read(k);
		int flag=0;
		for(register int i=1;i<=k;++i){
			read(edge[i].from),read(edge[i].to);
			if(edge[i].from==n&&edge[i].to==m)flag=1;
		}
		if(!flag)edge[++k].from=n+1,edge[k].to=m+1;
		write(spfa());
	}
}
using namespace Solve;
int main(){
	solve();
}
```

---

