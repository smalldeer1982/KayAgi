# Broken Tree

## 题目描述

题面：

给定一棵有n个节点的树，其中一号点是根。每条边有重量和强度。如果一条边的强度小于这条边深度较大的点的子树内所有边重量和，则这条边会断裂。你可以降低一些边的重量，且被降低重量的边会损失等量的强度。每条边的最终重量必须为正整数，强度必须为非负整数。询问至少要降低多少重量，或者输出-1表示这棵树无论如何都会断裂。本题配有SPJ

## 样例 #1

### 输入

```
3
1 3 5 7
3 2 4 3
```

### 输出

```
3
1 3 5 7
3 2 4 3
```

## 样例 #2

### 输入

```
4
1 3 2 3
3 4 5 1
3 2 3 3
```

### 输出

```
-1```

## 样例 #3

### 输入

```
5
1 2 2 4
2 4 1 9
4 5 5 6
4 3 4 8
```

### 输出

```
5
1 2 2 4
2 4 1 9
4 5 1 2
4 3 2 6
```

## 样例 #4

### 输入

```
7
1 2 5 2
2 3 4 3
1 4 3 7
4 5 4 1
4 6 3 2
6 7 1 6
```

### 输出

```
7
1 2 5 2
2 3 2 1
1 4 3 7
4 5 3 0
4 6 3 2
6 7 1 6
```

# 题解

## 作者：xtx1092515503 (赞：5)

# [Portal](https://www.luogu.com.cn/problem/CF758E)

这里介绍一种 $O(n)$ 的贪心做法。

首先，我们第一遍dfs，求出 $mnw_x$ 数组，表示以 $x$ 为根的子树中最小能有多大的重力。这个就直接贪心地把每条边剥削到最低（重力为 $1$/强度为该儿子的 $mnw$，看两个哪个最先发生）即可。假如发现就算把某棵子树剥削到最低，某条边也撑不住，则直接跳无解即可。

此部分代码（我的代码实现可能比较奇怪，$e$ 数组存的是边的信息，然后 ```vector``` $v$ 存的是某个点相邻的所有边的编号；边的两个端点异或起来，再异或上自己 ，就能得到边的另一边的编号）：

```cpp
void dfs1(int x,int fa){
	for(auto i:v[x]){
		int y=e[i].x^e[i].y^x;
		if(y==fa)continue;
		dfs1(y,x);
		if(mnw[y]>e[i].str){puts("-1");exit(0);}
		mnw[x]+=mnw[y]+e[i].wei-min(e[i].str-mnw[y],e[i].wei-1ll);
	}
}
```

然后第二遍dfs，求出 $f_x$ 数组，表示以 $x$ 为根的子树的最优状况。假如发现当前边的强度不足以支撑 $f_x$，这次我们就来剥削 $f_x$（~~翻 身 做 主 人~~）。因为之前已经证明必定有解，故我们必能在 $x$ 中找到某条边剥削。因为我们不知道要剥削哪条边，所以我们在 $x$ 处打个tag叫 $rec_x$，表示其子树中要剥削这么多（~~发 展 指 标~~）。

此部分代码：

```cpp
void dfs2(int x,int fa){
	for(auto i:v[x]){
		int y=e[i].x^e[i].y^x;
		if(y==fa)continue;
		dfs2(y,x);
		if(f[y]>e[i].str)rec[y]=f[y]-e[i].str;
		f[x]+=f[y]-rec[y]+e[i].wei;
	}
}
```

然后第三遍dfs，求解。我们首先将 $rec_x$ 下传到某个儿子，让那个儿子帮忙剥削。假如儿子剥削不完（~~家 族 企 业~~），就传回父亲，父亲先尝试在与儿子的连边处剥削，然后再传给下一个儿子。

此部分代码：

```cpp
int dfs3(int x,int fa){
	f[x]-=rec[x];
	for(auto i:v[x]){
		int y=e[i].x^e[i].y^x;
		if(y==fa)continue;
		ll ass=min(rec[x],f[y]-mnw[y]-rec[y]);
		rec[y]+=ass,rec[x]-=ass;
		rec[x]+=dfs3(y,x);
		ll delta=min({e[i].str-f[y],rec[x],e[i].wei-1ll});
		e[i].wei-=delta,e[i].str-=delta;
		rec[x]-=delta;
	}
	return rec[x];
}
```
最终输出即可。代码就把上面的拼一起即可。

---

## 作者：米奇 (赞：1)

### 题解

首先一个很显然的贪心，每次肯定先修改深度大的边。

然后就可以用堆维护子树内可以被修改的边。如果一条边不满足条件，那么就从堆中每次找深度最大的边来修改。

这时你会发现一条边被修改后，会使它的祖先边能被修改的范围发生变化，这个是很难维护的。

但是由于每次肯定先修改深度大的边，所以一条边如果要被修改，那么它子树内的边一定已经被修改过了。我们提前把它子树内的边被修改后对它产生的影响求出即可。

维护堆的方法很套路，启发式合并堆即可。

时间复杂度:$O(n  log ^2n)$

### 代码

```
#include<bits/stdc++.h>
using namespace std;
#define next Nxt
#define last Lst
#define gc getchar
#define int long long
const int N=1e6+5;
int n,m,sum[N],sum_can[N],a[N],b[N],can[N],X[N],Y[N];
struct node{
	int dep,id;
};
bool operator < (node a,node b)
{
	return a.dep<b.dep;
}
priority_queue<node>q[N];
vector<int>g[N];
//char buf[1<<21],*p1=buf,*p2=buf;
//inline int gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
inline int read()
{
    int ret=0,f=0;char c=gc();
    while(!isdigit(c)){if(c=='-')f=1;c=gc();}
    while(isdigit(c)){ret=ret*10+c-48;c=gc();}
    if(f)return -ret;return ret;
}
void dfs(int u,int dep)
{
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		dfs(v,dep+1);
		sum[u]+=sum[v]+a[v];
		sum_can[u]+=sum_can[v];
		if(q[v].size()>q[u].size())swap(q[u],q[v]);
		while(!q[v].empty())
		{
			q[u].push(q[v].top());
			q[v].pop();
		}
	}
	if(u==1)return;
	while(b[u]<sum[u])
	{
		if(q[u].empty())
		{
			puts("-1");
			exit(0);
		}
		node x=q[u].top();q[u].pop();
		int mi=min(sum[u]-b[u],can[x.id]);
		a[x.id]-=mi;
		b[x.id]-=mi;
		can[x.id]-=mi;
		sum[u]-=mi;
		sum_can[u]-=mi;
		if(can[x.id]>0)q[u].push(x);
	}
	if(b[u]<sum[u])
	{
		puts("-1");
		exit(0);
	}
	q[u].push((node){dep,u});
	can[u]=min(a[u]-1,b[u]-sum[u]+sum_can[u]);
	sum_can[u]+=can[u];
}
signed main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		X[i]=read();Y[i]=read();
		g[X[i]].push_back(Y[i]);
		a[Y[i]]=read();b[Y[i]]=read();
	}
	dfs(1,0);
	cout<<n<<endl;
	for(int i=1;i<n;i++)
		printf("%lld %lld %lld %lld\n",X[i],Y[i],a[Y[i]],b[Y[i]]);
	return 0;
}
```

---

## 作者：5ab_juruo (赞：0)

一个显然的性质是，一个子树内能形成的重量是一个区间。

感性理解一下是先形成最大的重量，然后从下到上遍历着减重，一定不会互相冲突。

然后每个子树维护能形成的最大和最小就是个简单的树形 dp 了。如果最小重量之和大于承重就寄了。

输入的边是有序的，输出的边顺序是不能换的/tuu。

代码写得极其丑陋，甚至于写了两个 dfs。

```cpp
/* name: CF758E
 * author: 5ab
 * created at: 22-04-14 22:14
 */
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;
const int max_n = 200000;

int hd[max_n], des[max_n], w[max_n], pr[max_n], nxt[max_n], fr[max_n], e_cnt = 0;
ll l[max_n], r[max_n];

void add(int s, int t, int a, int b)
{
	fr[e_cnt] = s, des[e_cnt] = t, w[e_cnt] = a, pr[e_cnt] = b;
	nxt[e_cnt] = hd[s], hd[s] = e_cnt++;
}

inline ll my_min(ll a, ll b) { return (a < b)? a:b; }
inline ll my_max(ll a, ll b) { return (a > b)? a:b; }
bool dfs(int id, int wc, ll pc)
{
	ll curl = 0, curr = 0;
	for (int p = hd[id]; p != -1; p = nxt[p])
	{
		if (!dfs(des[p], w[p], pr[p]))
			return false;
		curl += l[des[p]], curr += r[des[p]];
	}
	if (curl > pc)
		return false;
	l[id] = curl + my_max(1, wc - pc + curl), r[id] = my_min(curr, pc) + wc;
	return true;
}

void dfs2(int id, int fa, int p, ll cur)
{
	for (int p = hd[id]; p != -1; p = nxt[p])
		if (des[p] != fa)
			cur -= l[des[p]];
	if (cur > w[p])
		cur -= w[p];
	else
	{
		pr[p] = pr[p] - w[p] + cur, w[p] = cur;
		cur = 0;
	}
	
	for (int p = hd[id]; p != -1; p = nxt[p])
	{
		if (cur + l[des[p]] >= r[des[p]])
		{
			cur -= r[des[p]] - l[des[p]];
			dfs2(des[p], id, p, r[des[p]]);
		}
		else
		{
			dfs2(des[p], id, p, l[des[p]] + cur);
			cur = 0;
		}
	}
}

signed main()
{
	memset(hd, -1, sizeof hd);
	
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	
	cin >> n;
	for (int i = 1, x, y, c1, c2; i < n; i++)
	{
		cin >> x >> y >> c1 >> c2;
		add(x-1, y-1, c1, c2);
	}
	if (!dfs(0, 0, 0x3f3f3f3f3f3f3f3fll))
	{
		cout << "-1" << endl;
		return 0;
	}
	
	w[n-1] = pr[n-1] = 0;
	dfs2(0, -1, n - 1, r[0]);
	
	cout << n << endl;
	for (int i = 0; i < n - 1; i++)
		cout << fr[i] + 1 << " " << des[i] + 1 << " " << w[i] << " " << pr[i] << endl;
	
	return 0;
}
```

---

