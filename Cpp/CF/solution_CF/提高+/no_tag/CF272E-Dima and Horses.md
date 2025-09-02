# Dima and Horses

## 题目描述

Dima came to the horse land. There are $ n $ horses living in the land. Each horse in the horse land has several enemies (enmity is a symmetric relationship). The horse land isn't very hostile, so the number of enemies of each horse is at most 3.

Right now the horse land is going through an election campaign. So the horses trusted Dima to split them into two parts. At that the horses want the following condition to hold: a horse shouldn't have more than one enemy in its party.

Help Dima split the horses into parties. Note that one of the parties can turn out to be empty.

## 样例 #1

### 输入

```
3 3
1 2
3 2
3 1
```

### 输出

```
100
```

## 样例 #2

### 输入

```
2 1
2 1
```

### 输出

```
00
```

## 样例 #3

### 输入

```
10 6
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
0110000000
```

# 题解

## 作者：MatrixGroup (赞：3)

## 前言

Kevin 搬的模拟赛都是小清新思维题！就是我被创死了！非常好题目，爱来自瓷器。

## 题意

给定一个最大度不超过 $3$ 的图，求出一个 $2$-染色使得对于每个结点至多有一个与其相邻的结点颜色相同，或报告无解。

$n\le 3\cdot 10^5$。

## 题解

考虑调整法。一开始我们不妨让所有点颜色均为 $0$。可以发现假如有一个结点 $v$ 使得有不少于 $2$ 个与其相邻的结点与其颜色相同，则将其反色。这样一定可以调整到一组合法解。为什么？

称不符合条件的点为关键点，两端颜色相同的边为关键边。每一次修改，关键边的条数至少减少 $1$，因此一定可以到达一个没有关键点的局面。$\square$

考虑维护关键点集合。对于每次反色，暴力维护要反色的点与其邻居是否仍为关键点即可。因为最大度不超过 $3$，时间复杂度 $O(n\log n)$。（`std::set` 的时间）

---

## 作者：zhjzhmh (赞：2)

考虑一个点最多连 $3$ 条边，其中一个邻点可以分在同一部分，其他两个放另外一个部分，所以总是有解的。考虑每个点最多只有三条边，所以可以用邻接表存图，对于每个点进行一遍染色，如果发现它有 $2$ 个及以上的邻点与它在同一部分，则将其反色处理，然后遍历与它在同一部分的邻点进行更新检查，详见代码注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[300010][5],f[300010],x,y;
void work(int x)
{
	int cnt=0;for(int i=1;i<=a[x][0];i++) if(f[x]==f[a[x][i]]) cnt++;//找相同部分内的的邻点数量
	if(cnt>=2) {f[x]^=1;for(int i=1;i<=a[x][0];i++) if(f[x]==f[a[x][i]]) work(a[x][i]);}//邻点数量>=2，将这个点反色处理，进一步遍历
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++) scanf("%d%d",&x,&y),a[x][++a[x][0]]=y,a[y][++a[y][0]]=x;//存图
	for(int i=1;i<=n;i++) work(i);for(int i=1;i<=n;i++) cout<<f[i];
}
```

---

## 作者：RAND_MAX (赞：0)

# Dima and Horses 题解
## 前言
一道类似的题（可以说是双倍经验了QwQ）：[P7178](https://www.luogu.com.cn/problem/P7178)。

## Solution
题意很显然，这里不作赘述，下文以**染色**代替**分组**。

看到题**很难不想到**先令所有点同色，再进行调整。考虑如何调整一种不合法的染色方案。

注意到一个点不合法当且仅当有大于一个与它相邻的点与它同色，由于一个点度数最多为 3 ，那么在遇到一个不合法的点时，将它反色（黑变白，白变黑）后再对与其相邻的不合法点进行同样操作即可。

这样的做法看上去是 $O(n^2)$ 的，但是注意到一开始至多有 $\frac{3n}{2}$ 条边，对于每一次反色操作，端点同色的边**至少**减少一条，最终一定会有解且复杂度 $O(n)$。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define R read()
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-') 
		{
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9') 
	{
		x=(x<<1)+(x<<3)+c-48;
		c=getchar();
	}
	return x*f;
}
void write(int x)
{
	static int st[35],top=0;
	if(x<0)
	{
		x=-x;
		putchar('-');
	}
	do
	{
		st[top++]=x%10;
		x/=10;
	}while(x);
	while(top)
	{
		putchar(st[--top]+48);
	}
}
int n,m;
vector<int>g[300010];
bool col[300010];
void dfs(int x)
{
	int ans=0;
	for(int i:g[x])
	{
		if(col[x]==col[i])
		{
			ans++;
		}
	}
	if(ans>=2)
	{
		col[x]^=1;
		for(int i:g[x])
		{
			if(col[i]==col[x])
			{
				dfs(i);
			}
		}
	}
	return;
}
signed main()
{
//	freopen("horse.in","r",stdin);
//	freopen("horse.out","w",stdout);
	n=R,m=R;
	for(int i=1,x,y;i<=m;i++)
	{
		x=R,y=R;
		g[x].pb(y);
		g[y].pb(x);
	}
	for(int i=1;i<=n;i++)
	{
		dfs(i);
	}
	for(int i=1;i<=n;i++)
	{
		write(col[i]);
	}
	putchar('\n');
 	return 0;
}

```

---

