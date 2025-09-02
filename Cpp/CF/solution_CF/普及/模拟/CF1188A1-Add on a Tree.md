# Add on a Tree

## 题目描述

Note that this is the first problem of the two similar problems. You can hack this problem only if you solve both problems.

You are given a tree with $ n $ nodes. In the beginning, $ 0 $ is written on all edges. In one operation, you can choose any $ 2 $ distinct leaves $ u $ , $ v $ and any real number $ x $ and add $ x $ to values written on all edges on the simple path between $ u $ and $ v $ .

For example, on the picture below you can see the result of applying two operations to the graph: adding $ 2 $ on the path from $ 7 $ to $ 6 $ , and then adding $ -0.5 $ on the path from $ 4 $ to $ 5 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/4514fbf35a3201a7ca3b335f667bd3e11a688c5b.png)Is it true that for any configuration of real numbers written on edges, we can achieve it with a finite number of operations?

Leaf is a node of a tree of degree $ 1 $ . Simple path is a path that doesn't contain any node twice.

## 说明/提示

In the first example, we can add any real $ x $ to the value written on the only edge $ (1, 2) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/25d412324353a5cacb63d72803d1f9b15e742633.png)In the second example, one of configurations that we can't reach is $ 0 $ written on $ (1, 2) $ and $ 1 $ written on $ (2, 3) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/e16117f5a283e54a35e77dfddddf18a8df81966b.png)Below you can see graphs from examples $ 3 $ , $ 4 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/1d0c41f73ee7e0beb3f827a01577bfa07941d15e.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/91469666c4af6f377da3f6104280ec7d6081a3a0.png)

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
YES```

## 样例 #2

### 输入

```
3
1 2
2 3
```

### 输出

```
NO```

## 样例 #3

### 输入

```
5
1 2
1 3
1 4
2 5
```

### 输出

```
NO```

## 样例 #4

### 输入

```
6
1 2
1 3
1 4
2 5
2 6
```

### 输出

```
YES```

# 题解

## 作者：Priori_Incantatem (赞：10)

**Update: 2020/1/15 ，稍微修改了一下格式和一些小细节**

这题看起来很难，其实是一道结论题

题目要求求出初始边权为 $0$，能否通过操作变为边权为任意值的任何组合  
如果可以，那么我们可以形象的把它当成 先把所有边权变为 $0$，再把边权变为任意值的操作

具体操作如下：

令点 $x$ 的度数为 $d[x]$

若 $d[x]=1$，无限制随便加减，因为只有一条边

若 $d[x]=2$，两条边只能同加同减。虽然可以都变为 $0$，但不能变为任意组合值

若 $d[x]=3$，分两种情况考虑：  
设连接点$x$的三条边权为 $i,j,k$

若 $i+j \le k$：将 $i$ 和 $k$ 同时减去 $i$，再将 $j$和 $k$ 同时减去 $j$，这时 $i=j=0,k=k-i-j$  
我们将剩下的 $k$ 平均分给 $i$ 和 $j$，这时 $k=0,i=j=-\frac{k}{2}$，最后把 $i$ 和 $j$ 同时加上 $\frac{k}{2}$，则 $i=j=k=0$，全部为0后就可以加任意值了

若 $i+j>k$：将 $i,j,k$ 同时减去 $min(i,j)$，我们假设 $j<i$，那么这时 $i=i-j,j=0,k=k-j$  
再把 $i$ 和 $k$ 同时减去 $i$，这时除了 $k$ 其他都为 $0$，最后就跟上面一样的平均分来处理就可以全部为 $0$ 了

若 $d[x]>3$ ，与 $d[x]=3$ 同理  
首先可以三个三个分为一组，每组都不需要其他组的帮助就可以都变为$0$。最后只能剩下两个或一个（若没有剩下说明已经全部为$0$）。这时，我们可以借助已经化为 $0$ 的边来凑成三条边，再用上面的方法继续处理

当边权全部为 $0$ 时，达到任意组合的方法与上同理

代码就很简单啦，直接判断有没有度数为 $2$ 的节点就可以了

```cpp
#include<cstdio>
#include<iostream>
const int Maxn=100000+20,inf=0x3f3f3f3f;
int d[Maxn],n;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
bool check()
{
	for(int i=1;i<=n;++i)
	if(d[i]==2)return 0;
	return 1;
}
int main()
{
	//freopen("in.txt","r",stdin);
	n=read();
	for(int i=1;i<n;++i)
	{
		int x=read(),y=read();
		d[x]++,d[y]++;
	}
	if(check())puts("YES");
	else puts("NO");
	return 0;
}
```

---

## 作者：OIerWu_829 (赞：5)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1188A1) / [Codeforces 传送门](https://codeforces.com/contest/1188/problem/A1)

我们先构造出树的邻接表，然后开始搜索，把每个节点的度数存储在 $d$ 数组，然后遍历所有节点，如果发现有的节点度数为 $2$，就说明无法通过题目给定的操作实现边权的任意组合，输出 `NO` 结束程序，如果没有度数为 $2$ 的节点则输出 `YES`。

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5 + 5;

int d[N];
vector<int> G[N];

void dfs(int u, int fa)
{
	d[u] = G[u].size();
	for (int v : G[u])
		if (v != fa) dfs(v, u);
}

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, -1);
	for (int i = 1; i <= n; i++)
		if (d[i] == 2)
		{
			cout << "NO\n";
			return 0;
		}
	cout << "YES\n";
    return 0;
}
```

---

## 作者：Bai_R_X (赞：4)

## 思路
题意我们可以视为判断是否能将边权变为任意值。（如果边权非零则用下述情况中加换成减归零再按下述方法）

于是，我们可以试一下枚举每个点的度（连接的点数）所对应的情况。

对于度为 $1$ ，只有一条边，目标为将边设为 $a$ ，我们只要让边权 $+a$ 就可以。

对于度为 $2$ ，有两条边，目标为将边设为 $a$ 和 $b$ ( $a\ne b$ )，让边权 $+a$ ，第二条边达到不了 $b$ ；于是我们让边权 $-a$ 再 $+b$ ，第一条边又达到不了 $a$ 。

对于度为 $3$ ，有三条边，目标为将边设为 $a$ 、 $b$ 和 $c$ （为简单，我们将目标对应的边叫做 $A,B,C$ ）。我们让 $A$ 和 $B$ 加上 $\frac{b-c+a}{2}$ ， $B$ 和 $C$ 加上 $\frac{b-a+c}{2}$ ， $A$ 和 $C$ 加上 $\frac{a-b+c}{2}$ 。

度如果大于 $3$ ，与度为 $3$ 时同理。

所以，只有度为 $2$ 时不行，如果树内有度为 $2$ 的点则不能让边权任意。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int head[100005],cnt,n,i;
signed main()
{
    cin>>n;
    for(i=1;i<n;i++)
    {
    	int x,y;
    	cin>>x>>y;
    	head[x]++;
    	head[y]++;
	}
	for(i=1;i<=n;i++)
	{
		if(head[i]==2)
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
    return 0;
}
```

---

