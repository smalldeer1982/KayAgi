# Two Rooted Trees

## 题目描述

你有两棵有根树，每棵树都有 $n$ 个结点。不妨将这两棵树上的点都用 $1$ 到 $n$ 之间的整数编号。每棵树的根结点都是 $1$。第一棵树上的边都是**蓝色**，第二课树上的边都是**红色**。我们也称第一棵树是**蓝色的**，第二棵树是**红色的**。

对于一条边 $(p, q)$，当以下条件满足时，我们认为 $(x, y)$ 是一条坏边：

- 边 $(x, y)$ 的颜色与 $(p, q)$ 的颜色不同。
- 考虑与 $(p, q)$ 颜色相同的那棵树。在 $x$ 和 $y$ 中**有且仅有**其中一个点**同时**位于 $p$ 和 $q$ 的子树。（注意这里的 $x, y$ 和上面的 $(x, y)$ 不在同一棵树上）

在本题中，你的任务是模拟下述过程。该过程包含几个阶段：

- 在每个阶段，**有且仅有**一种颜色的边可以被删除。
- 在第 $1$ 个阶段，**有且仅有**一条**蓝色**的边被删除。
- 假设在第 $i$ 个阶段我们删除了 $(u_1, v_1), (u_2, v_2), ..., (u_k, v_k)$。在第 $i+1$ 个阶段，我们会先删除所有对于 $(u_1, v_1)$ 的没有删除的坏边，然后删除所有对于 $(u_2, v_2)$ 的没有删除的坏边，然后一直进行下去，直到 $(u_k, v_k)$ 结束。

对于每一个阶段，输出哪些边会被删除。注意，对于一条边的坏边的定义，我们总是只考虑初始的那两棵树。

## 样例 #1

### 输入

```
5
1 1 1 1
4 2 1 1
3
```

### 输出

```
Blue
3
Red
1 3
Blue
1 2
Red
2
```

# 题解

## 作者：Lynkcat (赞：5)

这里给出一个不需要树剖的做法。

对于第一棵树中的一条边 $(u,v)$ 设 $v$ 是 $u$ 的儿子。我们设每个点在第一棵树上的 dfs 序为 $a_i$，第二棵树中为 $b_i$。显然在第二棵树中需要删掉的边 $(x,y)$ 满足 $x,y$ 其中一个的 dfs 序在 $v$ 子树中另一个不在。那么相当于平面上的两个矩形，直接开两个线段树维护即可。

具体维护方法有很多种，我的方法是把这个点在每个覆盖它的区间都插入一遍，然后区间查询取出的时候判断一下是否已经取出过即可，时间复杂度和空间复杂度 $O(n \log n)$。

还有一种做法是直接把所有点插入到叶子上，然后线段树上维护是否子树内元素都被取完的标记，每次查询如果没取完就暴力递归，时间复杂度 $O(n\log n)$ 空间复杂度 $O(n)$。

```c++
#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define N 200005
#define pa pair<int,int>
using namespace std;
ll read()
{
	ll x=0,fh=1;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') fh=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return fh*x;
}
void write(ll x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar('0'+x%10);
}
void writeln(ll x)
{
	write(x);
	putchar('\n');
}
void writesp(ll x)
{
	write(x);
	putchar(' ');
}
int st;
int n;
vector<int>S;
int sm;
vector<pair<int,pa>>Wt[2];
int vis[2][N];
struct CWT_Mei_Ma
{
	int num,cnt;
	vector<int>G[N];
	int Dfn;
	int ldfn[N],rdfn[N],dfn[N];
	vector<pa>tr[N<<2];
	int Ltr[N<<2],Rtr[N<<2];
	pa E[N];
	inline init()
	{
		memset(Rtr,-1,sizeof(Rtr));
	}
	inline void ad(int x,int y)
	{
		++cnt;
		E[cnt].fi=x,E[cnt].se=y;
		G[x].push_back(y);
	}
	void dfs(int k,int fa)
	{
		++Dfn;
		ldfn[k]=dfn[k]=Dfn;
		for (auto u:G[k])
		{
			dfs(u,k);
		}
		rdfn[k]=Dfn;
	}
	void update(int k,int l,int r,int x,int y,int i)
	{
		if (l==r)
		{
			tr[k].push_back({y,i});
			Rtr[k]=tr[k].size()-1;
			cnt=max(cnt,k);
			return;
		}
		tr[k].push_back({y,i});
		Rtr[k]=tr[k].size()-1;
		int mid=l+(r-l)/2;
		if (x<=mid) update(k<<1,l,mid,x,y,i);
		else update(k<<1|1,mid+1,r,x,y,i);
	}
	vector<int>query(int k,int l,int r,int L,int R,int val,int fh)
	{
		if (tr[k].empty()) return vector<int>();
		if (L<=l&&r<=R)
		{
			vector<int>g;
			if (fh==0)
			{
				while (Ltr[k]<=Rtr[k])
				{
					if (tr[k][Rtr[k]].fi<val) break;
					if (!vis[num^1][tr[k][Rtr[k]].se])
					{
						vis[num^1][tr[k][Rtr[k]].se]=1;
						g.push_back(tr[k][Rtr[k]].se);
					}
					Rtr[k]--;
				}
			} else
			{
				while (Ltr[k]<=Rtr[k])
				{
					if (tr[k][Ltr[k]].fi>val) break;
					if (!vis[num^1][tr[k][Ltr[k]].se])
					{
						vis[num^1][tr[k][Ltr[k]].se]=1;
						g.push_back(tr[k][Ltr[k]].se);
					}
					Ltr[k]++;
				}
			}
			return g;
		}
		int mid=l+(r-l)/2;
		if (R<=mid) return query(k<<1,l,mid,L,R,val,fh);
		if (L>mid) return query(k<<1|1,mid+1,r,L,R,val,fh);
		auto X=query(k<<1,l,mid,L,R,val,fh);
		auto Y=query(k<<1|1,mid+1,r,L,R,val,fh);
		for (auto u:Y) X.push_back(u);
		return X;
	}
}T[2];
signed main()
{
	n=read();
	for (int i=2;i<=n;i++)
	{
		int x=read();
		T[0].ad(x,i);
	}
	for (int i=2;i<=n;i++)
	{
		int x=read();
		T[1].ad(x,i);
	}
	T[0].dfs(1,0);
	T[1].dfs(1,0);
	T[0].init();
	T[1].init();
	T[0].num=0;
	T[1].num=1;
	st=read();
	S.push_back(st);
	for (int now=0;now<=1;now++)
	{
		for (int i=1;i<n;i++)
		{
			if (now==0&&i==st) continue;
			int x=T[now^1].dfn[T[now].E[i].fi],y=T[now^1].dfn[T[now].E[i].se];
			Wt[now^1].push_back({y,{x,i}});
			Wt[now^1].push_back({x,{y,i}});
		}
	}
	for (int now=0;now<=1;now++) 
		sort(Wt[now].begin(),Wt[now].end());
	for (auto u:Wt[0])
	{
		T[0].update(1,1,n,u.se.fi,u.fi,u.se.se);
	}
	for (auto u:Wt[1])
	{
		T[1].update(1,1,n,u.se.fi,u.fi,u.se.se);
	}	
	puts("Blue");
	writeln(st);
	int now=0;
	while (!S.empty())
	{
		vector<int>G;
		for (auto u:S)
		{
			vector<int>g=T[now].query(1,1,n,T[now].ldfn[T[now].E[u].se],T[now].rdfn[T[now].E[u].se],T[now].rdfn[T[now].E[u].se]+1,0);
			for (auto i:g)
			{
				G.push_back(i);
			}
			g=T[now].query(1,1,n,T[now].ldfn[T[now].E[u].se],T[now].rdfn[T[now].E[u].se],T[now].ldfn[T[now].E[u].se]-1,1);
			for (auto i:g)
			{
				G.push_back(i);
			}
		}
		S.swap(G);
		if (S.empty()) break;
		if (now==0) puts("Red");
		else puts("Blue"); 
		sort(S.begin(),S.end());
		for (auto u:S) writesp(u);
		puts("");
		now^=1;
	}
}
```


---

## 作者：DeepSeaSpray (赞：1)

# CF403E Two Rooted Trees

略去题面。

因为 $(x,y)$ 只有一个点在 $(p,q)$ 的公共子树上（定义同题面），若 $q$ 为儿子，我们只要保证 $(x,y)$ 只有一个在 $q$ 的子树中即可。对于 DFS 序而言，因为子树的 DFS 序是连续的，所以我们转化为 $(x,y)$（对于 DFS 序而言，下同）有一个在该区间内，另一个不在即可。

为了解决这个问题，我们定义 $x < y$ ，接着问题进一步转换成 $x \in [p,q]$ 以及 $x<p,y \in [p,q]$ 的问题，考虑使用线段树。

## DFS 序

我们设 $A$ 树是蓝树，$B$ 树是红树。考虑处理上一次是蓝边的情况（红色正好相反。我们要先对 $A$ 求一个 DFS 序，其子树头和子树尾分别用 $din$，$dout$ 表示。然后将 $B$ 中的边加入，如下面代码。

```cpp
inline void Init(Tree &x,Tree &y)
{
	int iu,iv;
	Edge tmp;
	for(int i=0;i<x.et;i++)
	{
		tmp=x.e[i];
		iu=tmp.u,iv=tmp.v;
		if(y.din[iu]>y.din[iv]) swap(iu,iv);
		y.v0[y.din[iu]].push_back(Edge(y.din[iv],y.din[iu],tmp.v));
		y.v1[y.din[iv]].push_back(Edge(y.din[iu],y.din[iv],tmp.v));
	}
	for(int i=1;i<=y.dcnt;i++)
	{
		sort(y.v0[i].begin(),y.v0[i].end(),Cmp2);
		sort(y.v1[i].begin(),y.v1[i].end(),Cmp2);
	}
}
```

其中 $v0$，$v1$ 分别用以存储不同的两种情况，当然还有边的编号（这里使用儿子端点记录，因为编号等于端点减一）。最后要进行排序，下文会提到原因。

## 线段树

接着我们直接使用两棵线段树分别维护上文两种情况维护即可，在建树的过程中，对于元区间，我们直接赋值，对于父区间，我们只需要合并子区间的 vector。可以参考以下代码：

```cpp
void Build(int x,int l,int r,int re,vector<Edge> ve[])
{
    T[x].l=l,T[x].r=r;
    if(l==r)
    {
        T[x].v=ve[l];
        if(re) reverse(T[x].v.begin(),T[x].v.end());
    }
    else
    {
        int mid=(T[x].r-T[x].l)/2+T[x].l;
        Build(x<<1,l,mid,re,ve);
        Build(x<<1|1,mid+1,r,re,ve);
        int ng=1;
        if(re) ng=-1;
        int i=0,j=0;
        while(i<(int)T[x<<1].v.size()&&j<(int)T[x<<1|1].v.size())
        {
            if(T[x<<1].v[i].u*ng<T[x<<1|1].v[j].u*ng)
                T[x].v.push_back(T[x<<1].v[i]),i++;
            else T[x].v.push_back(T[x<<1|1].v[j]),j++;
        }
        for(;i<(int)T[x<<1].v.size();i++)
            T[x].v.push_back(T[x<<1].v[i]);
        for(;j<(int)T[x<<1|1].v.size();j++)
            T[x].v.push_back(T[x<<1|1].v[j]);
    }
}
```

其中我们需要注意维护单调性。分析其的时间复杂度，在同一层中，所有父区间不可能重复 vector 大小最多为 $n$，总共只有 $\log n$ 层所以时间，空间复杂度都为 $O(n \log n)$。

接下来就是查询操作，也是维护单调性的原因。我们像普通线段树一样查询即可，但是值得注意的是，对于一个被查询区间覆盖的线段，我们只需要从 vecotr 尾部取出答案并弹出即可，因为我们维护了单调性，所以如果尾部不合法，那么前面的也就不合法。还没完，因为取过的边不能再取，所以我们需要一个vis保存状态。因为其可能在子区间取过，虽然它不记录在子区间中，但可能在父区间中。如果我们找到了被取过的边，我们直接跳过即可。

你可能有疑问，为什么不能查询之后重新合并区间，因为这样会导致我们每一次查询都是 $O(n \log⁡ n)$ 这显然不行，然而通过标记，因为总共只有 $n \log n$ 个元素，每一个只可能被操作一次，所以总时间复杂度为 $O(n \log n)$。

```cpp
void Query(int x,int l,int r,int val,int ng,bool vi[])
{
    if(l<=T[x].l&&T[x].r<=r)
    {
        Edge tmp;
        while(!T[x].v.empty()&&T[x].v.back().u*ng<val*ng)
        {
            tmp=T[x].v.back();
            T[x].v.pop_back();
            if(vi[tmp.nxt]) continue;
            vi[tmp.nxt]=1;
            ans.push_back(tmp);
        }
    }
    else
    {
        int mid=(T[x].r-T[x].l)/2+T[x].l;
        if(l<=mid) Query(x<<1,l,r,val,ng,vi);
        if(mid<r) Query(x<<1|1,l,r,val,ng,vi);
    }
}
```

[完整代码](https://codeforces.com/contest/403/submission/228035646)

---

