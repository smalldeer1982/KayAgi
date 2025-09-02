# [POI 2016 R3] 巡游 Parade

## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/5043)。

## 题目描述

**题目译自 [XXIII Olimpiada Informatyczna — III etap](https://sio2.mimuw.edu.pl/c/oi23-3/dashboard/) [Parada](https://szkopul.edu.pl/problemset/problem/1QaUWE_ePAmitZjgAszOVD1U/statement/)**

每年春天，拜托城都会举办盛大的拜托尼亚春季巡游，迎接新季的到来。今年，国王 Bajtazar XVI 亲临现场，为巡游增添光彩。拜托城的路网由 $n$ 个路口通过 $n-1$ 条双向街道连接而成，确保从任一路口可到达其他任意路口。

巡游的具体路线尚未确定，但已知它将从某路口出发，沿若干街道行进，最终在另一路口结束。为避免单调，巡游路线每条街道至多经过一次。

为确保巡游参与者的安全，需在巡游经过的路口（包括起点和终点）处，对未被巡游使用的街道入口设置路障。请计算最多可能需要多少路障。

## 说明/提示

**样例 1 解释**

![](https://cdn.luogu.com.cn/upload/image_hosting/nzhumxn8.png)

若巡游从路口 $2$ 出发，至路口 $7$ 结束，需设置 $5$ 处路障（路口 $2$ 的 $3$ 个入口各一处，路口 $5$ 和 $7$ 各一处）。

**附加样例**

1. $n=20$，路网为路径。  
2. $n=20$，路网为星形。  
3. $n=1000$，随机样例，第 $i$ 条街道（$i=1, \ldots, n-1$）连接路口 $i+1$ 与某编号更小的路口。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$    | $n \leq 20$              | $15$ |
| $2$    | $n \leq 300$             | $16$ |
| $3$    | $n \leq 3000$            | $22$ |
| $4$    | $n \leq 200000$          | $47$ |

## 样例 #1

### 输入

```
8
1 2
2 3
4 2
5 2
6 5
5 7
7 8
```

### 输出

```
5
```

# 题解

## 作者：leozhao123 (赞：1)

**[传送门](https://www.luogu.com.cn/problem/P12747) | [AC 记录](https://www.luogu.com.cn/record/221153782)**

**题意**：给定树，对于一条**起点与终点不同**的简单路径 $P$，称它的「权值」为满足 $u\in V_P$ 且 $v\notin V_P$ 的边 $(u,v)$ 的数量。求所有 $P$ 的权值的最大值。

先不考虑起点与终点是否相同。记 $f_u$ 为以节点 $u$ 为起点、$u$ 的子树中的节点（包括 $u$）为终点的所有路径的权值的最大值。

- 当 $u$ 的子树是菊花图时，即 $u$ 的所有儿子都是叶子，此时选择任意一个儿子作为终点的路径的权值都为 $|son_u|-1$，而选择 $u$ 本身作为终点则为 $|son_u|$ 更优，因此 $f_u=|son_u|$。
- 当 $u$ 的子树不是菊花图时，易得：
  $$
  f_u=\max_{v\in son_u}\set{f_v}+|son_u|-1
  $$

统计答案时用相同方法下传向上部分的 $f$ 值即可。

最后考虑起点与终点相同的情况。按照转移，当且仅当给定的树是菊花图时，求出的起点与终点同为树的中心。由于最少取 $2$ 个点，所以答案最大为 $n-2$，在输出时要将结果与 $n-2$ 取较小值。

---

时间复杂度 $\mathcal{O}(n)$。
```cpp
// -std=c++14 -O2
#include<vector>
#include<iostream>
using namespace std;
using ll=long long;
const ll N=2e5+3;
ll n,f[N],d[N],ans;
// d[u]=v 表示节点 u 继承了 f[v] (v\in son_u)
vector<ll>G[N];
void dfs1(ll u,ll fa) {// 求 f 和 d 数组
	for(auto v:G[u]) {
		if(v==fa) continue;
		dfs1(v,u);
		if(f[u]<f[v]) f[u]=f[v],d[u]=v;
	}
	fa=(u==1?0:1);// 注意 fa 的意义发生了改变，表示 u 有 / 没有父节点
	if(G[u].size()-fa>0) {
		if(f[u]) f[u]+=G[u].size()-fa-1;// 非菊花图情况
		else f[u]=G[u].size()-fa,d[u]=0;// 菊花图情况
	}
}
void dfs2(ll u,ll fa,ll g) {// g 为下传的向上部分的 f 值
	ans=max(ans,max(g,(u==1?0LL:1LL))+f[u]);
	for(auto v:G[u]) {
		if(v==fa) continue;
		if(d[u]!=v)
			 dfs2(v,u,max((ll)(g+G[u].size()-2),f[u]-1+(u==1?0:1)));
		else dfs2(v,u,max((ll)(g+G[u].size()-2),f[u]-f[v]+(u==1?0:1)));
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	ll u,v;
	cin>>n;
	for(ll i=1;i<=n-1;++i) {
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs1(1,0);
	dfs2(1,0,0);
	cout<<min(ans,n-2);
	return 0;
}
```

---

## 作者：mairuisheng (赞：1)

- 题目：[P12747 [POI 2016 R3] 巡游 Parade](https://www.luogu.com.cn/problem/P12747)

- 主要算法：树形 DP。

- 分析：

设 $f_u$ 是以节点 $u$ 为根的子树中，从 $u$ 向下延伸的最大路障数。

则分两种情况计算 $f_u$：

先计算 $u$ 的边数，用 $sz$ 表示，将 $f_u$ 初始化为 $sz$。

设 $u$ 的其中一个子节点为 $v$。

①以 $u$ 为起点的最大值：

![](https://cdn.luogu.com.cn/upload/image_hosting/qc6gebzy.png)

如图所示（红色路径为选择的路径）。

它的状态转移方程是：

$$f_u=\max(f_u,f_v-2+sz)$$

即 $u$ 的边数加子节点的路障数减去二（$u$ 到 $v$ 的路障和 $v$ 到 $u$ 的路障）。

②以 $u$ 为连接点（连接两个不同子节点路径）的最大值：

首先，如果 $u$ 的子节点不足两个，直接跳过；

否则，设 $w$ 是 $u$ 的另外一个子节点；设 $ft$ 是 $u$ 的最大子路障数；$sd$ 是 $u$ 的次大子路障数。

![](https://cdn.luogu.com.cn/upload/image_hosting/g2bf2l22.png)

如图所示（红色路径为选择的路径）。

它的状态转移方程是：

$$f_u=\max(f_u,sz+ft+sd-4)$$

即 $u$ 的边数加上最大子路障数与次大子路障数的和再减去四（$u$ 到 $v$ 的路障、$v$ 到 $u$ 的路障、$u$ 到 $w$ 的路障和 $w$ 到 $u$ 的路障）。

- 时间复杂度：$O(n)$，可以通过此题。

- 参考代码：

```cpp
//Author : mairuisheng
//#pragma GCC optimize(3)
#include<cstdio>
#include<vector>
using namespace std;
inline int read()
{
	int x=0,f=1;
	char s;
	s=getchar();
	while(s<48||s>57)
	{
		if(s=='-')f=-f;
		s=getchar();
	}
	while(s>47&&s<58)
	{
		x=(x<<3)+(x<<1)+s-48;
		s=getchar();
	}
	return x*f;
}
constexpr int N=2e5+1,MIN=-1e9;
int n;
vector<int> g[N];
int f[N];
int ans;
void dfs(int u,int fa)
{
	int sz=g[u].size(),ft=MIN,sd=MIN;
	f[u]=sz;
	for(auto v:g[u])
	{
		if(v==fa)continue;
		dfs(v,u);
		f[u]=max(f[u],f[v]-2+sz);
		if(f[v]>ft)
		{
			sd=ft;
			ft=f[v];
		}
		else if(f[v]>sd)sd=f[v];
	}
	ans=max(ans,f[u]);
	if(ft!=MIN&&sd!=MIN)ans=max(ans,ft+sd+sz-4);
}
int main()
{
	n=read();
	int i,u,v;
	for(i=1;i<n;++i)
	{
		u=read();
		v=read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	printf("%d",min(ans,n-2));
	return 0;
}
```

---

## 作者：a202401006 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P12747)

# 解析

## 题目大意

有一些点互相连通（连接两个点的边为无向边），需要规划出一条从某个点开始到某个点结束的路线，使得剩余没有处于路线上的点的总数量最大。

## 考察知识

本题考查树形 DP。

## 思路

我们不妨考虑一下每个在路线上的点的情况：作为根节点或者连接的节点。

设 $dotsum_i$ 表示点 $i$ 最大路障数量。设 $side$ 表示根节点连接的边的数量。设 $dotsum1$ 和 $dotsum2$ 表示某个点的所有子节点中所含有的最大路障数量和次大路障数量。

**第一种情况：u 为根节点**

![](https://cdn.luogu.com.cn/upload/image_hosting/ce30odup.png)如图，红色箭头表示路线。那么我们就可以得出路障的转移方程：点 $u$ 所连接的所有边的数量（即其周围的路障总数）加上点 $v$ 连接的路线的最大路障数量减去被算了两遍的把路障放在 $v$ 点的情况。

那么转移方程就得出来了。

$$dotsum_{u}= \max (dotsum_{u},dotsum_{v}-2+side)$$

**第二种情况：u 为连接节点**

![](https://cdn.luogu.com.cn/upload/image_hosting/rmb5r4lt.png)如图所示，红色箭头表示路线。那么我们就又能得出转移方程：点 $u$ 所连接的边的总数加上子节点中的最大和次大路障数（都要向上面的第一种情况那样减去 $2$）。

那么转移方程就得出来了。

$$dotsum_{u}= \max (output,dotsum1+dotsum2+side-4)$$

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,MINN=-1008610086;
int n,u,v,max_dotsum[N],output;
vector<int> ed[N];
void dfs(int u,int fa)
{
	int connectedside_sum=ed[u].size(),max_fromdot_dotsum=MINN,second_fromdot_dotsum=MINN;
	max_dotsum[u]=connectedside_sum;
	for(auto v:ed[u])
	{
		if(v==fa)
		{
			continue;
		}
		dfs(v,u);
		max_dotsum[u]=max(max_dotsum[u],max_dotsum[v]-2+connectedside_sum);
		if(max_dotsum[v]>max_fromdot_dotsum)
		{
			second_fromdot_dotsum=max_fromdot_dotsum;
			max_fromdot_dotsum=max_dotsum[v];
		}
		else if(max_dotsum[v]>second_fromdot_dotsum)
		{
			second_fromdot_dotsum=max_dotsum[v];
		}
	}
	output=max(output,max_dotsum[u]);
	if(max_fromdot_dotsum!=MINN&&second_fromdot_dotsum!=MINN)
	{
		output=max(output,max_fromdot_dotsum+second_fromdot_dotsum+connectedside_sum-4);
	}
}

int main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		cin>>u>>v;
		ed[u].push_back(v);
		ed[v].push_back(u);
	}
	dfs(1,0);
	cout<<min(output,n-2);
}
```

---

