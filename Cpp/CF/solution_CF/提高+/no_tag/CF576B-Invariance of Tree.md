# Invariance of Tree

## 题目描述

A tree of size $ n $ is an undirected connected graph consisting of $ n $ vertices without cycles.

Consider some tree with $ n $ vertices. We call a tree invariant relative to permutation $ p=p_{1}p_{2}...\ p_{n} $ , if for any two vertices of the tree $ u $ and $ v $ the condition holds: "vertices $ u $ and $ v $ are connected by an edge if and only if vertices $ p_{u} $ and $ p_{v} $ are connected by an edge".

You are given permutation $ p $ of size $ n $ . Find some tree size $ n $ , invariant relative to the given permutation.

## 说明/提示

In the first sample test a permutation transforms edge (4, 1) into edge (1, 4), edge (4, 2) into edge (1, 3) and edge (1, 3) into edge (4, 2). These edges all appear in the resulting tree.

It can be shown that in the second sample test no tree satisfies the given condition.

## 样例 #1

### 输入

```
4
4 3 2 1
```

### 输出

```
YES
4 1
4 2
1 3
```

## 样例 #2

### 输入

```
3
3 1 2
```

### 输出

```
NO
```

# 题解

## 作者：alnumb (赞：3)

构造题。

对于每一个 $i$, 连一条 $i \to p_i$ 的边，容易发现这样构成很多个环。

设有 $k$ 个环，那这样会有两种情况:

1. 环内连边:

记环上的点数量有 $n$ 个。
首先，当 $n = 1, n = 2$ 时，显然是没有问题的。

当 $n\ge 3$ 时，分奇偶性讨论:

当 $n$ 为奇数时，显然将环上任意两个点连边，最后都会有 $n$ 条边，根据题意，一棵有 $n$ 个点的树有 $n-1$ 条边，显然不符合要求。

当 $n$ 为偶数时，将环上任意两个点连边，最后会有 $\dfrac{n}{2}$ 条边，重复两次，至少就会有 $n$ 条边，同样也不符合要求。

2. 环间连边

现在考虑将两个环如何才能合并。

不妨设一个环的大小为 $a$，另外一个大小为 $b$ $(a \le b)$。

手动模拟容易得到, 在两个环中分别选两个点，会连 $\operatorname{lcm}(a, b)$ 条边，又因为 $a + b - 1 < 2b$，可以得出 $\operatorname{lcm}(a, b) = b$。

也就是说如果只考虑环之间连边的话,最多只能够连一次，否则就不会形成一棵树。


现在就只剩下环内连边了，这是还剩下 $a + b - 1 - b = a - 1$ 条边需要连，又因为当 $a \ge 3$ 时环内连边无解，所以 $a$ 只能等于 $1$ 或 $2$。

综上，有解情况有两种：

1. 存在 $p_i = i$ 

2. 存在 $p_{p_{_i}} = i$ （也就是存在点数为 $2$ 的环）并且这 $k$ 个环中任意一个环，环上的点的数量为偶数。

其余情况无解。

代码：

```cpp
int a[N];
int n;
void solve(int x)
{
	printf("YES\n");
	for(int i = 1; i <= n; i ++)
	{
		if(x == i)continue;
		printf("%d %d\n", x, i);
	}
	return; 
}
bool vis[N];
void Solve(int x, int y)
{
	printf("YES\n");
	printf("%d %d\n", x, y);
	int op = 0;
	for(int i = 1; i <= n; i ++)
	{
		if(vis[i] == 1)continue;
		int p = i;
		while(vis[p] == 0)
		{
			vis[p] = 1;
			if(op == 0)printf("%d %d\n", x, p);
			else printf("%d %d\n", y, p);
			op = op ^ 1;
			p = a[p];
		}
	}
}
void check(int x, int y)
{
	for(int i = 1; i <= n; i ++)
	{
		if(vis[i] == 1)continue;
		int p = i;
		int cnt = 0;
		while(vis[p] == 0)
		{
			vis[p] = 1;
			p = a[p];
			cnt ++;
		}
		if(cnt % 2 == 1)
		{
			printf("NO\n");
			exit(0);
		}
	}
	memset(vis, 0, sizeof(vis));
	vis[x] = vis[y] = 1;
	Solve(x, y);
}
int main()
{
	n = read();
	for(int i = 1; i <= n; i ++)
	{
		a[i] = read();
		if(a[i] == i)
		{
			solve(i);
			return 0;
		}
	}
	for(int i = 1; i <= n; i ++)
	{
		if(a[a[i]] == i)
		{
			vis[i] = vis[a[i]] = 1;
			check(i, a[i]);
			return 0;
		}
	}
	printf("NO\n");
	return 0;	
} 
```


---

## 作者：Graphcity (赞：1)

小清新构造结论题。考虑由边 $i\to p_i$ 构成的置换环，结论如下：

若合法的构造方案存在，当且仅当：

1. 存在一个自环（$p_i=i$）。
2. 存在一个双元环（$p_i=j,p_j=i$），且所有置换环的大小为偶数。

先证明这两种情况可以构造出合法的解。

1. 存在自环 $p_i=i$ 时，那么就将 $i$ 连向其它所有点，形成一个菊花图，这样显然是合法的。

2. 存在双元环 $p_i=j,p_j=i$ 时，若所有置换环的大小为偶数，则对置换环进行黑白染色，一条边连接的两个点颜色不同，那么就将所有的 $i$ 连向黑点，所有的 $j$ 连向白点即可。最后连接 $i,j$。这样当然也是合法的。

接下来证明其它的情况不合法。

在一个置换环内，考虑环内合并。设环的大小为 $siz\ (siz>2)$，每个点连向它后面 $k$ 个点。

- 当 $k \mid siz$ 时，连边后会形成 $\dfrac{siz}{k}$ 个环，不合法。
- 当 $k \nmid siz$ 时，连边后会形成恰好一个整环，不合法。

所以环内合并的方法是行不通的。

接下来只能考虑不同环之间的合并。

设你要合并环 $a$ 和环 $b$，环 $a$ 的大小为 $s_1$，环 $b$ 的大小为 $s_2$，若有 $s_1>s_2> 2$，分类讨论：

- $\gcd(s_1,s_2)=1$ 时，你就会在 $s_1+s_2$ 个点之间连接 $s_1s_2$ 条边。显然这个时候边数会超过点数，矛盾。
- $\gcd(s_1,s_2)>1$ 且 $s_2\nmid s_1$ 时，它会形成许多不相交的环，不合法。
- $s_2\mid s_1$ 时，每个 $b$ 环上的点都会连接不同的 $\dfrac{s_1}{s_2}$ 个 $a$ 环上的点，这个时候 $a$ 环和 $b$ 环就可以合并了。

看起来这样可能可行。但要注意到一个问题，多环合并之后还需要进行至少一次环内合并，所以这依然是不可行的。

代码很简单。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,tmp,p[Maxn+5],col[Maxn+5],siz[Maxn+5];
vector<int> v[Maxn+5];

inline void Run1(int x)
{
    int num=v[x][0];
    For(i,1,tmp) if(i!=x)
        for(auto j:v[i]) printf("%d %d\n",num,j);
}
inline int Check()
{
    For(i,1,tmp) if(siz[i]&1) return 0;
    return 1;
}
inline void Run2(int x)
{
    int num1=v[x][0],num2=v[x][1];
    printf("%d %d\n",num1,num2);
    For(i,1,tmp) if(i!=x)
    {
        int len=siz[i]-1;
        For(j,0,len)
        {
            int y=v[i][j];
            if(j&1) printf("%d %d\n",num2,y);
            else printf("%d %d\n",num1,y);
        }
    }
}

int main()
{
    n=read();
    For(i,1,n) p[i]=read();
    For(i,1,n) if(!col[i])
    {
        int now=i; ++tmp;
        while(!col[now]) col[now]=tmp,v[tmp].push_back(now),
                         siz[tmp]++,now=p[now];
    }
    For(i,1,n) if(siz[i]==1)
    {
        printf("YES\n");
        Run1(i);
        return 0;
    }
    For(i,1,n) if(siz[i]==2)
    {
        if(Check())
        {
            printf("YES\n");
            Run2(i);
            return 0;
        }
        else
        {
            printf("NO\n");
            return 0;
        }
    }
    printf("NO\n");
    return 0;
}
```

---

