# Lazy Student

## 题目描述

给定 $n, m, a _ {1, \cdots, m}, b _ {1, \cdots, m}$，构造一个无重边自环的 $n$ 个点 $m$ 条边的无向连通图，满足第 $i$ 条边边权为 $a _ i$，且所有 $b _ i = 1$ 的边 $i$ 组成了该图的一棵最小生成树。

$2 \le n \le 10 ^ 5, n - 1 \le m \le \min(\frac{n(n - 1)}{2}, 10 ^ 5)$。

## 样例 #1

### 输入

```
4 5
2 1
3 1
4 0
1 1
5 0
```

### 输出

```
2 4
1 4
3 4
3 1
3 2
```

## 样例 #2

### 输入

```
3 3
1 0
2 1
3 1
```

### 输出

```
-1
```

# 题解

## 作者：Leap_Frog (赞：2)

### Description.
略

### Solution.
考虑倒着思考 Kruskal 算法。  
按边权从小到大排序。  
每次插入一条边。  
如果是树边，那就新开节点。  
否则在当前节点内任意连边。  
这样构造，每次非树边插入都比当前两端小。  
所以必然正确。  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}/*}}}*/
struct node{int w,id,fr,tw;char fg;}a[100005];int n,m,l=2,r=3,id=1;
int main()
{
	read(n),read(m);for(int i=1;i<=m;i++) read(a[i].w),read(a[i].fg),a[i].id=i;
	sort(a+1,a+m+1,[](node a,node b){return a.w<b.w||(a.w==b.w&&a.fg>b.fg);});
	for(int i=1;i<=m;i++)
	{
		if(a[i].fg) {a[i].fr=1,a[i].tw=++id;continue;}
		if(r>id) return puts("-1"),0;
		a[i].fr=l++,a[i].tw=r;if(l==r) r++,l=2;
	}sort(a+1,a+m+1,[](node a,node b){return a.id<b.id;});
	for(int i=1;i<=m;i++) printf("%d %d\n",a[i].fr,a[i].tw);
	return 0;
}
```

---

## 作者：Aisaka_Taiga (赞：2)

## 翻译

给你 $n$ 个点，$m$ 条边，给你 $m$ 条边的权值和是否为最小生成树的树边，求一个合法的图，无解则输出 $-1$。

## 构造

我们可以想到直接以 $1$ 为中心点来构造一个菊花图，在构造的过程中，我们首先是要按边权大小给边排个序的，另外的如果边权相等树边优先在前，为什么后面讲。

我们对于树边，可以直接开一个计数器 $cnt$ 表示当前已经添加到了第 $cnt$ 个点，只要遇见一条最小生成树的边就直接将其与 $1$ 相连，这样在遇到后面非树边的边就可以直接在这 $cnt$ 个点里面乱连了，因为最小生成树已经确定了，后面怎么加边都不会影响，而如果要是当前已经加进去的点边都连满了但是又有了非树边，这时候是无解的。

code:

```cpp
#include<bits/stdc++.h>
#define N 1000100
#define endl '\n'
using namespace std;
int n,m,cnt=1,u=2,v=3,flag=1;
struct sb{int u,v,w,id,flag;}e[N];
inline int cmp1(sb a,sb b){if(a.w==b.w)return a.flag>b.flag;return a.w<b.w;}
inline int cmp2(sb a,sb b){return a.id<b.id;}
inline int read(){int x=0,f=1;char ch=getchar();while(!isdigit(ch)){f=ch!='-';ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return f?x:-x;}
signed main()
{
	n=read();m=read();
	for(int i=1;i<=m;i++)e[i].w=read(),e[i].flag=read(),e[i].id=i;
	sort(e+1,e+m+1,cmp1);
	for(int i=1;i<=m;i++)
	{
		if(e[i].flag)e[i].u=1,e[i].v=++cnt;
		else
		{
			if(v>cnt){flag=0;break;}
			e[i].u=u++;e[i].v=v;
			if(u==v)v++,u=2;
		}
	}
	if(!flag){cout<<"-1"<<endl;return 0;}
	sort(e+1,e+m+1,cmp2);
	for(int i=1;i<=m;i++)cout<<e[i].u<<" "<<e[i].v<<endl;
	return 0;
}
```

---

## 作者：osfly (赞：2)

算是对 [Leap_Frog大佬的补充吧qwq](https://www.luogu.com.cn/blog/daniu/solution-cf605b)。

%%% Leap_Frog.

我们来看一下大佬的这段话：

	考虑倒着思考 Kruskal 算法。
	按边权从小到大排序。
	每次插入一条边。
	如果是树边，那就新开节点。
	否则在当前节点内任意连边。
	这样构造，每次非树边插入都比当前两端小。
	所以必然正确。

对于“如果是树边，那就新开节点。”这句话，可以理解成我们构造一个以 $1$ 号点为中心的菊花图（所有点都连向 $1$ 号点）。对于第 $i$ 条树边，建一条从 $1$ 连向 $i+1$ 的边。

就是这样子：

![](https://img1.imgtp.com/2022/08/10/h9SbRIrD.png)

对于“否则在当前节点内任意连边。”这句话，我们插入非树边的时候为了不能重复（题目有要求两点之间不能有多条边），设我们目前已经处理了 $i$ 条树边（即目前我们已经开了 $i+1$ 个点），现在要插的边是从 $u$ 连向 $v$，那么我们 $u$ 可以从 $j$ 开始 $(3\le j\le i+1)$，$v$ 从 $2$ 开始建边。每建完一条边，$v$ 就加 $1$，如果 $u=v$，那么 $u$ 加 $1$，$v$ 回退到 $2$ 重新开始为下一次的建边做准备。

$-1$ 的情况就是我们目前开的点不够用（即 $u=i+1,v=i$)。

放几张图理解一下吧qwq：

![](https://img1.imgtp.com/2022/08/10/pdxXyB0L.png)

这样子代码是不是好理解一点啦qwq.

没有压行的代码（Leap_Frog大佬压行的代码感觉不太好读TaT）：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m;
struct edge
{
	int u;
	int v;
	int w;
	int id;
	int yes;
}e[100010];
int tot=1;//目前已开的点的数量，我们要设为1，因为我们得先开好1号节点
bool cmp1(edge a,edge b)
{
	if(a.w==b.w) return a.yes>b.yes;
	return a.w<b.w;
}
bool cmp2(edge a,edge b)
{
	return a.id<b.id;
}
int u=2,v=3;//记得初始化
bool flag=1;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&e[i].w,&e[i].yes);
		e[i].id=i;
	}
	sort(e+1,e+1+m,cmp1);
	for(int i=1;i<=m;i++)
	{
		if(e[i].yes) e[i].u=1,e[i].v=++tot;//如果是树边
		else//如果是非树边
		{
			if(v>tot)//无解
			{
				flag=0;
				break;
			}
			e[i].u=u++;
			e[i].v=v;
			if(u==v) v++,u=2;
		}
	}
	if(!flag) printf("-1");
	else
	{
		sort(e+1,e+1+m,cmp2);//最后要记得按一开始的输入顺序排序
		for(int i=1;i<=m;i++) printf("%d %d\n",e[i].u,e[i].v);
	}
	return 0;
}
```

完结撒花~

---

## 作者：SJH__qwq (赞：0)

考虑把所有的边按照 $a_i$ 从小到大排序，**$a_i$ 相同的按照 $b_i$ 从 $1$ 到 $0$ 排序**。

然后按照排完序之后边的顺序贪心，以 $1$ 为新的树的根，最小生成树上的边形成一个菊花树，非最小生成树上的边任意连边即可。

---

## 作者：LG_ljc2022 (赞：0)

## 题目大意

给定一个图中所有边的权值以及该边是否属于最小生成树，现要求构造一个图，使得图的最小生成树满足题目给定的性质。

## Solution

题目较为明确，只是有一个地方……

```cpp
no loops and multiple edges.
``````

再看样例，结合题目，明显有环！

~~（不然还跑最小生成树干嘛）~~

学过 Kruskal 的人解此题会比较容易。不难想到可以将 Kruskal 的执行过程反过来，先将所有的边安照权值为第一关键字，归属为第二关键字进行排序。基于贪心，权值小的排前面；树上的边排前面（这样之后无论怎么加边最小生成树都不会受到影响）。接下来枚举所有边构造即可。

构造有两种方式：链或菊花图。这里用菊花图更好，链式相对麻烦一些。从小到大枚举所有边，如果是树上的边，则新建一个节点并将这个节点与根节点（$1$ 号）相连。

如果不是树上的边，则在当前节点内进行任意连边即可。可以这样构造：设定主节点 $v$，从 $3$ 开始，以及移动节点 $u$，从 $2$ 开始。$u$ 依次增大遍历完所有除了根节点以外编号小于 $v$ 的节点。每连一条非树上的边则 $u + 1$。如果 $v$ 前的编号已经全部用完（即 $u = v$）则 $v$ 加一移动到下一个节点，$u$ 则重新回归 $2$ 进行连边，如此循环往复即可。此时 $-1$ 的情况即为节点数量不够（设当前建了 $cnt$ 条树上的边，$-1$ 情况即为 $v > cnt$）。

代码中加入了一个小优化：输入时记录了每个节点的编号，在构造完成后可以省去一次排序。

**特别注意：**

 - 排序时一定要按照双关键字排序
 
 - 连接非树上的边时，不能把上述方法反过来，即设定 $u$ 为主节点，$v$ 为移动节点从 $u + 1$ 遍历到当前的 $cnt$。因为后续还可能增加树上的边，而增加一个节点 $u$ 曾经取到的所有的节点都会多出新的连边可能，直接把 $u$ 加一会导致情况考虑的缺失。
 
## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
struct node //存储输入
{
	int w, inct, idx;
}a[N];
struct edge //存储答案
{
	int l, r;
}ans[N];
int n, m, u = 2, v = 3, Node = 1;
bool cmp (node a, node b) //双关键字
{
	if (a.w == b.w) return a.inct > b.inct;
	return a.w < b.w;
}
int main()
{
	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &a[i].w, &a[i].inct);
		a[i].idx = i; //优化：记录编号，省去输出时的排序
	}
	sort(a + 1, a + m + 1, cmp);
	for (int i = 1; i <= m; i++)
	{
		if (a[i].inct == 1) //树上的边，直接构造菊花图
		{
			Node++;
			ans[a[i].idx] = {1, Node};
		}
		else
		{
//			if (u >= Node - 1)     //错误写法，不能正序枚举
//			{
//				printf("-1");
//				return 0;
//			}
//			if (v >= Node)
//			{
//				u++;
//				v = u + 1;
//			}
//			else v++;
//			ans[a[i].idx].l = u, ans[a[i].idx].r = v;

			if (v > Node) //节点数量不够
			{
				printf("-1");
				return 0;
			}
			ans[a[i].idx].l = u++, ans[a[i].idx].r = v; //记录连接边
			if (u == v) //当前v所有可用的节点已用完，v后移，u回归2重新开始
			{
				v++;
				u = 2;
			}
		}
	}
	for (int i = 1; i <= m; i++) printf("%d %d\n", ans[i].l, ans[i].r);
	
	return 0;
}
``````

---

