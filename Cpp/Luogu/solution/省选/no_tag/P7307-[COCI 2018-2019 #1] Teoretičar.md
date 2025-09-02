# [COCI 2018/2019 #1] Teoretičar

## 题目描述

Alan 为了避免感到无聊，便让 Goran 给他出一道有趣的题目。由于他忙于准备考试，Goran 的回忆里只有一个巨大的二分图。他把二分图递给 Alan，让他用尽可能少的颜色涂满所有边，使得同种颜色的边没有公共点。

Goran 看到 Alan 的复杂方法后，决定大发慈悲，给定了一个简化版本：令 $C$ 为上述问题的答案，$X$ 为不小于 $C$ 的最小的 $2$ 的正整数次幂。仅需给出一种方案，使得颜色个数不超过 $X$。

请帮助 Alan 解决该题。

注：二分图是一种能够被分成两个集合的图，使得每条边连接的两个点都属于不同集合。

## 说明/提示

#### 样例 2 解释

使用颜色最少个数为 $3$。然而，使用 $4$ 种颜色也是可行的。因为 $4$ 是不小于 $3$ 的最小的 $2$ 的正整数次幂。

#### 数据规模与约定

对于 $20\%$ 的数据，$L,R \le 100$。

对于另外 $20\%$ 的数据，$L,R \le 5000$。

对于 $100\%$ 的数据，$1 \le L,R \le 10^5$，$1 \le M \le 5 \times 10^5$，$1 \le a_i \le L$，$1 \le b_i \le R$。

#### 说明

**这里只选取其中具有梯度的 $10$ 个测试点进行评测，因此满分由 $130$ 调整为 $100$。**

**题目译自 [COCI2018-2019](https://hsin.hr/coci/archive/2018_2019/) [CONTEST #1](https://hsin.hr/coci/archive/2018_2019/contest1_tasks.pdf)  _T5 Teoretičar_。**

## 样例 #1

### 输入

```
3 3 5
1 1
1 2
2 2
2 3
3 3```

### 输出

```
2
1
2
1
2
1```

## 样例 #2

### 输入

```
2 4 4
1 1
1 2
1 3
2 4```

### 输出

```
4
1
2
3
4```

# 题解

## 作者：EXODUS (赞：2)

# Part 1：前言
神仙构造题。

下文中，我们用小写代替原文中的大写，用 $col_i$ 代表原文的 $c_i$。
# Part 2：正文

首先可以猜测到最小的颜色数为度数最大的点的度数，不会证也没关系，有一点是显然的，就是最终答案 $c$ 不小于度数最大的点的度数 $d_max$。

注意到题目给了一个非常奇怪的范围：$x$ 为不小于 $c$ 的最小的 $2$ 的正整数次幂。换言之，$x=2^{\left\lceil{\log_2 c}\right\rceil}\ge2^{\left\lceil{\log_2 d_{max}}\right\rceil}$，对于这种范围，一般可以想到是分治构造了。

考虑对边集进行划分，每次我们都试图将原来的边集划分为两个边集，每个边集中度数最大的点都是原来边集中最大的点的度数的一半。当我们把边集划分后点的度数最大是 $1$ 时，就把这个边集内所有的边染成同色的。这样做最多会分治 $\left\lceil{\log_2 d_{max}}\right\rceil$ 轮，每轮合并答案都会让颜色种类数乘 $2$，答案不会超过 $2^{\left\lceil{\log_2 d_{max}}\right\rceil}$。

接下来考虑如何划分。我们新建两个虚点 $x',y'$ 分属于二分图两侧。把一侧度数为奇数的点向另一侧的虚点连边，这样每个点的度数都是偶数，一定存在一条欧拉回路。我们将欧拉回路上的边交替染色，同色的边属于一个边集，这样就能使得每个点点度数大小减半（感性理解，对于每个点，出现在欧拉回路中度数除二上取整次，每次涉及到两条边且被染成不同颜色）。

时间复杂度 $O(n\log n)$（这里视 $n,m$ 同阶）。

# Part 3：代码
```cpp
#define u first
#define v second
#define pb push_back
const int N=2e5+7,M=1e6+7;
int l,r,m,n;
vector<np>e,ne;
vector<int>to[N];
int tim[N],deg[N],_clock=0;
int col[M];
int vis[M];

void reset(int x,vector<int>&V){
	tim[x]=_clock;
	to[x].clear();
	deg[x]=0;V.pb(x);
}

int c=0;

void dfs(int u){
	for(;!to[u].empty();){
		int id=to[u].back();
		to[u].pop_back();
		if(vis[id]==_clock)continue;
		
		col[id]=(c^=1);
		vis[id]=_clock;
		dfs(ne[id].u+ne[id].v-u);
	}
}

vector<int>solve(vector<np>E){
	if(!E.size())return {};
	++_clock;
	ne=E;
	vector<int>V;
	bool flag=0;
	int siz=E.size(),nsiz=ne.size();
	for(int i=0;i<siz;i++){
		np edge=E[i];
		int u=edge.u,v=edge.v;
		if(tim[u]!=_clock)reset(u,V);
		if(tim[v]!=_clock)reset(v,V);
		deg[u]++,deg[v]++;
		if(deg[u]>1||deg[v]>1)flag=1;
		to[u].pb(i),to[v].pb(i);
	}
	if(!flag){
		vector<int>res(E.size(),1);
		return res;
	}
	deg[n+1]=0;
	for(int i:V){
		if(deg[i]&1){
			if(i<=l||i==n+1){
				deg[n+2]++,deg[i]++;
				to[n+2].pb(nsiz),to[i].pb(nsiz),ne.pb({i,n+2});
				nsiz++;
			}else{
				deg[n+1]++,deg[i]++;
				to[n+1].pb(nsiz),to[i].pb(nsiz),ne.pb({i,n+1});
				nsiz++;
			}
		}
	}
	if(deg[n+1]&1){
		deg[n+2]++,deg[n+1]++;
		to[n+2].pb(nsiz),to[n+1].pb(nsiz),ne.pb({n+1,n+2});
		nsiz++;
	}
	for(int i:V){dfs(i);}
	vector<np>el,er;
	vector<int>cl;
	for(int i=0;i<siz;i++){
		if(col[i])er.pb(E[i]);
		else el.pb(E[i]);
		cl.pb(col[i]);
	}
	vector<int>rl=solve(el);
	vector<int>rr=solve(er);
	int ansl=0;
	for(int i:rl)ansl=max(ansl,i);
	vector<int>res;
	int tmpl=0,tmpr=0;
	for(int i=0;i<siz;i++){
		if(cl[i])res.pb(ansl+rr[tmpr++]);
		else res.pb(rl[tmpl++]);
	}
	return res;
}

int main(){
	l=read(),r=read(),m=read();n=l+r;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e.pb(mp(u,v+l)); 
	}
	vector<int>ans=solve(e);
	int res=0;
	for(int i:ans)res=max(res,i);
	cout<<res<<endl;
	for(int i:ans)printf("%d\n",i);
	return 0;
}
```

---

## 作者：xiaoxiaoxia (赞：1)

## 题目大意
有一个二分图，构造一种对边的染色方案，使得没有两个颜色相同的边共顶点。

假设对于给定二分图的答案是 $C$，记 $X$ 是大于等于 $C$ 的最小的 $2$ 的整次幂，你只需要给出一个方案，使得颜色数量不多于 $X$.。
## 思路概述
设度数最大的点的度数为 $D$，那么显然的，如果答案 $C>D$，也就是说我们只要构造出一种颜色数量不超过  $2^{\left \lfloor log_2D \right \rfloor}$ 的方案数。假设我们有一个边集 $e$，如果每个点的度数都 $\leq 1$，那么显然此时答案为 $1$，否则我们可以考虑把这个边集划分为两个边集 $e_1,e_2$ 使得每一个点的度数都尽量平分。重复这样的操作就可以。其他的细节就是可以用欧拉回路割边。时间复杂度 $O(m \log n)$。
## 代码部分

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
const int N=2e5+5;
const int M=5e5+5;
int L,R,m,U[M],V[M],du[N],st[N];
int fa[M],val[M],tag[M],res[M];
vector<int>v;
int find(int x)
{
	if(fa[x]==x)
		return x;
	int tmp=fa[x];
	fa[x]=find(fa[x]);
	val[x]^=val[tmp];
	return fa[x];
}
void upd(int x)
{
	find(x);
	if(!(val[x]^tag[fa[x]]))
	{
		tag[fa[x]]^=1;
	}
}
void unionset(int x,int y)
{
	int u=find(x),v=find(y);
	if(u!=v)
	{
		val[u]=val[x]^val[y]^1;
		fa[u]=v;
	}
}
void solve(vector<int>&v,int cur)
{
	if(v.size()==0)
		return;
	for(auto e:v)
	{
		fa[e]=e;
		val[e]=0;
		tag[e]=0;
		st[U[e]]=st[V[e]]=0;
	}
	int f=0;
	for(auto e:v)
	{
		int x=U[e],y=V[e];
		if(st[x]||st[y])f=1;
		if(!st[x]&&!st[y])
		{
			st[x]=st[y]=e;
		}
		else if(!st[x])
		{
			upd(st[y]);
			unionset(e,st[y]);
			st[x]=e;
			st[y]=0;
		}
		else if(!st[y])
		{
			upd(st[x]);
			unionset(e,st[x]);
			st[y]=e;
			st[x]=0;
		}
		else
		{
			upd(st[x]);
			upd(st[y]);
			unionset(e,st[x]);
			unionset(e,st[y]);
			st[x]=st[y]=0;
		}
	}
	if(f==0)
	{
		for(auto e:v)
			res[e]=1;
	}
	else
	{
		vector<int>vl,vr;
		for(auto e:v)
		{
			find(e);
			if(val[e]^tag[fa[e]])
			{
				vr.push_back(e);
			}
			else
			{
				vl.push_back(e);
			}
		}
		solve(vl,cur>>1);
		solve(vr,cur>>1);
		for(auto e:vr)
			res[e]+=cur>>1;
	}
}
int main()
{
	cin>>L>>R>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>U[i]>>V[i];
		V[i]+=L;
		du[U[i]]++;
		du[V[i]]++;
		v.push_back(i);
	}
	int dmax=0;
	for(int i=1;i<=L+R;i++)
		dmax=max(dmax,du[i]);
	int x=2;
	while(x<dmax)
		x<<=1;
	solve(v,x);
	cout<<x<<endl;
	for(int i=1;i<=m;i++)
		cout<<res[i]<<endl;
}
```

---

## 作者：Unnamed114514 (赞：0)

为什么要求是 $2$ 的次方呢？

由[这道题](https://www.luogu.com.cn/problem/P9731)启发，考虑分治。

颜色数只有两种的时候，你会发现，其实就是和上面那道题一样，建个超级源点连上所有度数为奇数的边，然后跑欧拉回路定向。对于本题，左到右颜色为 $1$，右到左颜色为 $2$。

因此考虑分治，我们有 $2^k$ 种颜色，在跑完欧拉回路之后，只需要将前 $2^{k-1}$ 种颜色分配给左到右的边，后 $2^{k-1}$ 种颜色分配给右到左的边然后对两种边分别分治直到 $l=r$。

要注意欧拉回路实现的精细。

给几种遇到的错误的欧拉回路实现方式：

- 只给边打标记，对点不打标记。(TLE 70)

来个菊花就 $O(m^2)$ 了，因为菊花的中心每条边都会跑一次。

- 给点打标记，每个点只访问一次。（WA 0）

唐，欧拉回路要求是每条路径访问一次，点可以访问多次，这样写过不了第二个样例。

- 给点打标记，每次搜的起点都保证没打标记。(TLE 90)

仍然是可以被菊花卡掉，要保证菊花的中心度数为奇数，这样每个点都会连向超级源点，这样的话你从菊花中心出去，到一个点，然后又到超级源点，然后又会从头开始遍历。

正确的写法是，写个当前弧优化，定义 $now_u$ 表示 $u$ 出去的前 $now_u-1$ 条边都被遍历过，这个时候遍历第 $now_u$ 条边，遍历前先让 $now_u\gets now_u+1$，这样就不会存在访问过的边重复访问的问题了。

---

