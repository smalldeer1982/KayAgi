# Odd Mineral Resource

## 题目描述

In Homer's country, there are $ n $ cities numbered $ 1 $ to $ n $ and they form a tree. That is, there are $ (n-1) $ undirected roads between these $ n $ cities and every two cities can reach each other through these roads.

Homer's country is an industrial country, and each of the $ n $ cities in it contains some mineral resource. The mineral resource of city $ i $ is labeled $ a_i $ .

Homer is given the plans of the country in the following $ q $ years. The plan of the $ i $ -th year is described by four parameters $ u_i, v_i, l_i $ and $ r_i $ , and he is asked to find any mineral resource $ c_i $ such that the following two conditions hold:

- mineral resource $ c_i $ appears an odd number of times between city $ u_i $ and city $ v_i $ ; and
- $ l_i \leq c_i \leq r_i $ .

As the best friend of Homer, he asks you for help. For every plan, find any such mineral resource $ c_i $ , or tell him that there doesn't exist one.

## 说明/提示

In the first three queries, there are four cities between city $ 3 $ and city $ 5 $ , which are city $ 1 $ , city $ 2 $ , city $ 3 $ and city $ 5 $ . The mineral resources appear in them are mineral resources $ 1 $ (appears in city $ 3 $ and city $ 5 $ ), $ 2 $ (appears in city $ 2 $ ) and $ 3 $ (appears in city $ 1 $ ). It is noted that

- The first query is only to check whether mineral source $ 1 $ appears an odd number of times between city $ 3 $ and city $ 5 $ . The answer is no, because mineral source $ 1 $ appears twice (an even number of times) between city $ 3 $ and city $ 5 $ .
- The second and the third queries are the same but they can choose different mineral resources. Both mineral resources $ 2 $ and $ 3 $ are available.

## 样例 #1

### 输入

```
6 8
3 2 1 3 1 3
1 2
1 3
2 4
2 5
4 6
3 5 1 1
3 5 1 3
3 5 1 3
1 1 2 2
1 1 3 3
1 4 1 5
1 6 1 3
1 6 1 3```

### 输出

```
-1
2
3
-1
3
2
2
3```

# 题解

## 作者：zhoukangyang (赞：27)

洛谷终于把 cf 爬上来了，水篇题解 qwq

[cnblogs 里来看](https://www.cnblogs.com/zkyJuruo/p/14392030.html#cf1479d-odd-mineral-resource)

## 题面

> [CF1479D Odd Mineral Resource](https://www.luogu.com.cn/problem/CF1479D)

> 给定一颗有 $n$ 个节点的树，每一个节点有一种颜色 $a_i$。$q$ 次询问，每次询问点 $x$ 到点 $y$ 的最短路径上是否有一种编号在 $[l, r]$ 的颜色，满足其出现次数为奇数。如果有，输出任意一个；否则输出 `-1`。

> 数据范围：$1 \le n, q \le 3 \times 10^5$，$1 \le l \le r \le n$，$1 \le a_i, x, y \le n$。

## 题解

介绍两种方法。

### 法 1

这是一个有关树上数颜色的问题，用树上莫队。

对颜色编号进行分块，块内维护可能成为答案的颜色。

修改时，如果此颜色的出现次数是奇数，那么就认为这种颜色可能成为答案。

查询的时候，对于整块扫描可能成为答案的颜色。对于一个扫到的数 $x$，如果出现次数确实是奇数就停，否则就把 $x$ 从可能成为答案的数中删除。散块暴力即可。

时间复杂度 $\Theta(n \sqrt m)$

喜提最劣解。

[aclink](https://codeforces.com/contest/1479/submission/106944471)

### 法 2

出现奇数次可以用异或来处理。

如果对于每一个元素，进行随机赋值。我们查询树上 $u$ 到 $v$ 上，编号在 $l$ 到 $r$ 的权值异或和，如果是 $0$ 那么我们就认为答案是 `-1`。

然后我们进行二分答案，查询一下 $[l, mid]$，如果异或和不是 $0$ 就在 $[l, mid]$ 往下做，否则 $[mid + 1, r]$ 的异或和一定不是 $0$，在 $[mid + 1, r]$ 往下做。

这个可以主席树维护。由于主席树的优良性质，我们可以直接在主席树上二分。时间复杂度 $\Theta((n + m) \log n)$

喜提最优解。

[aclink](https://codeforces.com/contest/1479/submission/106944375)

---

## 作者：wsyhb (赞：8)

## 目录

- 题意简述
- 思路一
	- 大常数 $O(n\sqrt{q}\log{n}+q\log{n})$ 算法
    - 小常数 $O(n\sqrt{q}\log{n}+q\log{n})$ 算法
    	- 代码
    - 正解 $O(n\sqrt{q}+q\sqrt{n})$
    	- 代码
- 思路二
	- 分析 + 题解
	- 代码
    - 有关 $X$ 的随机生成

## 题意简述

给定一棵 $n$ 个节点的树，$i$ 号节点的权值为 $a_i$。

有 $q$ 次询问，每次询问给定 $u,v,l,r$，表示询问是否存在 $c$ 满足 $l \le c \le r$ 且 $u,v$ 两点路径上恰好有**奇数个**权值为 $c$ 的节点。若存在，输出任意一个满足条件的 $c$，否则输出 `-1`。

**数据范围**：$n,q \le 3 \times 10^5$，$1 \le a_i \le n$，$1 \le l \le r \le n$。

## 思路一

看完题面，很容易想到**树上莫队**，用以维护当前每种权值出现的奇偶性，但是如何求得区间 $[l,r]$ 中某个出现奇数次的值呢？

### 大常数 $O(n\sqrt{q}\log{n}+q\log{n})$ 算法

我们可以将新增的出现奇数次的权值放进 **set** 里，将新增的出现偶数次的权值从 **set** 中删除，查询时**二分查找**即可。单次修改和单次查询都是**大常数** $O(\log{n})$ 的，**不足以通过此题**。

### 小常数 $O(n\sqrt{q}\log{n}+q\log{n})$ 算法

我们也可以在**树状数组**上将新增的出现奇数次和偶数次的权值对应位置 `+1` 和 `-1`，单次修改是**小常数** $O(\log{n})$ 的；查询时**在树状数组上二分**即可，时间复杂度为 $O(\log^2{n})$ 或 $O(\log{n})$（如果不会 $O(\log{n})$ 的做法，可以点[此处](https://blog.csdn.net/Defener/article/details/106926034)学习）。

由于 $q\log^2{n}<n\sqrt{q}\log{n}$（即瓶颈为前半部分），加之常数问题，理论上来说跑得会比前一种快一些，但**依然会 `Time limit exceeded on test 7`**。

#### 代码

由于是赛时写的，写得丑请见谅。（结构体变量 `l,r,L,R` 和局部变量 `L,R,ll,rr` 不要弄混了，本人因为弄混在赛时获得了 `Wrong answer on pretest 1` 的好成绩——当然这里已经修正）

``` cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	const int buffer_size=1e5+5;
	char buf[buffer_size],*S,*T;
	bool flag_EOF;
	inline char read_char()
	{
	    if(S==T)
			T=(S=buf)+fread(buf,1,buffer_size,stdin);
	    return S!=T?*(S++):EOF;
	}
	inline int read_int()
	{
	    int flag=1;
	    char c=read_char();
	    while(c<'0'||c>'9')
	    {
	        if(c==EOF)
	        {
	            flag_EOF=true;
	            return 0;
	        }
	        flag=(c=='-'?-1:1);
	        c=read_char();
	    }
	    int x=0;
	    while(c>='0'&&c<='9')
	    {
	        x=x*10+(c^48);
	        c=read_char();
	    }
	    return x*flag;
	}
	char st[13];
	int _top;
	inline void Write(int x)
	{
		if(!x)
		{
			putchar('0');
			return;
		}
		if(x<0)
		{
			putchar('-');
			x=-x;
		}
		while(x)
		{
			st[++_top]=x%10+'0';
			x/=10;
		}
		while(_top>0)
			putchar(st[_top--]);
	}
}
int n,m;
const int max_n=3e5+5;
vector<int> edge[max_n];
int id[max_n<<1],Time,dfn[max_n][2];
void dfs(int x,int fa)
{
	dfn[x][0]=++Time;
	id[Time]=x;
	for(int i=0;i<int(edge[x].size());++i)
	{
		int y=edge[x][i];
		if(y!=fa)
			dfs(y,x);
	}
	dfn[x][1]=++Time;
	id[Time]=x;
}
int dep[max_n],sz[max_n],son[max_n],fath[max_n];
void dfs1(int x,int fa)
{
	dep[x]=dep[fa]+1;
	sz[x]=1;
	son[x]=-1;
	fath[x]=fa;
	int max_sz=0;
	for(int i=0;i<int(edge[x].size());++i)
	{
		int y=edge[x][i];
		if(y!=fa)
		{
			dfs1(y,x);
			sz[x]+=sz[y];
			if(sz[y]>max_sz)
			{
				max_sz=sz[y];
				son[x]=y;
			}
		}
	}
}
int _top[max_n];
void dfs2(int x,int top_now)
{
	_top[x]=top_now;
	if(son[x]!=-1)
		dfs2(son[x],top_now);
	for(int i=0;i<int(edge[x].size());++i)
	{
		int y=edge[x][i];
		if(y!=fath[x]&&y!=son[x])
			dfs2(y,y);
	}
}
inline int get_LCA(int x,int y)
{
	while(_top[x]!=_top[y])
	{
		if(dep[_top[x]]<dep[_top[y]])
			swap(x,y);
		x=fath[_top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
namespace BIT
{
	int c[max_n];
	inline void modify(int k,int v)
	{
		for(int i=k;i<=n;i+=i&(-i))
			c[i]+=v;
	}
	inline int query(int k)
	{
		int res=0;
		for(int i=k;i>0;i-=i&(-i))
			res+=c[i];
		return res;
	}
}
const int max_m=3e5+5;
int ans[max_m];
struct Query
{
	int l,blo,r,lca,L,R,id;
}q[max_m];
inline bool cmp(const Query &a,const Query &b)
{
	return a.blo!=b.blo?a.blo<b.blo:a.r<b.r;
}
int a[max_n];
bool odd[max_n];
inline void work(int x)
{
	if(odd[a[x]])
	{
		BIT::modify(a[x],-1);
		odd[a[x]]=false;
	}
	else
	{
		BIT::modify(a[x],1);
		odd[a[x]]=true;
	}
}
int main()
{
	n=IO::read_int(),m=IO::read_int();
	for(int i=1;i<=n;++i)
		a[i]=IO::read_int();
	for(int i=1;i<=n-1;++i)
	{
		int x=IO::read_int(),y=IO::read_int();
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	dfs(1,0);
	dfs1(1,0);
	dfs2(1,1);
	int s=int(2*n/sqrt(m));
	for(int i=1;i<=m;++i)
	{
		int u=IO::read_int(),v=IO::read_int(),l=IO::read_int(),r=IO::read_int();
		if(dfn[u][0]>dfn[v][0])
			swap(u,v);
		int p=get_LCA(u,v);
		if(p==u)
			q[i].l=dfn[u][0],q[i].r=dfn[v][0];
		else
			q[i].l=dfn[u][1],q[i].r=dfn[v][0],q[i].lca=p;
		q[i].L=l,q[i].R=r,q[i].id=i;
		q[i].blo=(q[i].l-1)/s+1;
	}
	sort(q+1,q+m+1,cmp);
	int L=1,R=0;
	for(int i=1;i<=m;++i)
	{
		while(L<q[i].l)
			work(id[L++]);
		while(L>q[i].l)
			work(id[--L]);
		while(R<q[i].r)
			work(id[++R]);
		while(R>q[i].r)
			work(id[R--]);
		if(q[i].lca)
			work(q[i].lca);
		int v1=BIT::query(q[i].L-1);
		int v2=BIT::query(q[i].R);
		if(v1==v2)
			ans[q[i].id]=-1;
		else
		{
			int ll=q[i].L,rr=q[i].R,mid,res=q[i].R;
			while(ll<=rr)
			{
				mid=(ll+rr)>>1;
				if(BIT::query(mid)>=v1+1)
					res=mid,rr=mid-1;
				else
					ll=mid+1;
			}
			ans[q[i].id]=res;
		}
		if(q[i].lca)
			work(q[i].lca);
	}
	for(int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}
```

### 正解 $O(n\sqrt{q}+q\sqrt{n})$

注意到时间复杂度的瓶颈在于修改，即要求单次修改 $O(1)$，单次询问不超过 $O(\sqrt{n})$，使用分块即可。

具体来说，用一个 `bool` 数组记录每种权值是否出现奇数次，再用一个 `int` 数组记录每一块有多少个出现奇数次的权值。修改时把当前这种权值及其所在块修改；查询时暴力扫描左右两端的部分，中间块若出现个数 $>0$ 则扫描。

#### 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
const int max_n=3e5+5;
vector<int> edge[max_n];
int id[max_n<<1],Time,dfn[max_n][2];
void dfs(int x,int fa)
{
	dfn[x][0]=++Time;
	id[Time]=x;
	for(int i=0;i<int(edge[x].size());++i)
	{
		int y=edge[x][i];
		if(y!=fa)
			dfs(y,x);
	}
	dfn[x][1]=++Time;
	id[Time]=x;
}
int dep[max_n],sz[max_n],son[max_n],fath[max_n];
void dfs1(int x,int fa)
{
	dep[x]=dep[fa]+1;
	sz[x]=1;
	son[x]=-1;
	fath[x]=fa;
	int max_sz=0;
	for(int i=0;i<int(edge[x].size());++i)
	{
		int y=edge[x][i];
		if(y!=fa)
		{
			dfs1(y,x);
			sz[x]+=sz[y];
			if(sz[y]>max_sz)
			{
				max_sz=sz[y];
				son[x]=y;
			}
		}
	}
}
int _top[max_n];
void dfs2(int x,int top_now)
{
	_top[x]=top_now;
	if(son[x]!=-1)
		dfs2(son[x],top_now);
	for(int i=0;i<int(edge[x].size());++i)
	{
		int y=edge[x][i];
		if(y!=fath[x]&&y!=son[x])
			dfs2(y,y);
	}
}
inline int get_LCA(int x,int y)
{
	while(_top[x]!=_top[y])
	{
		if(dep[_top[x]]<dep[_top[y]])
			swap(x,y);
		x=fath[_top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
const int max_m=3e5+5;
int ans[max_m];
struct Query
{
	int l,blo,r,lca,L,R,id;
}q[max_m];
inline bool cmp(const Query &a,const Query &b)
{
	return a.blo!=b.blo?a.blo<b.blo:a.r<b.r;
}
int a[max_n];
bool odd[max_n];
int sn;
const int max_sqrt_n=548+5;
int cnt[max_sqrt_n];
inline void work(int x)
{
	if(odd[a[x]])
	{
		--cnt[(a[x]-1)/sn+1];
		odd[a[x]]=false;
	}
	else
	{
		++cnt[(a[x]-1)/sn+1];
		odd[a[x]]=true;
	}
}
inline int query(int l,int r)
{
	int id_l=(l-1)/sn+1,id_r=(r-1)/sn+1;
	if(id_l==id_r)
	{
		for(int i=l;i<=r;++i)
		{
			if(odd[i])
				return i;
		}
		return -1;
	}
	for(int i=l;i<=id_l*sn;++i)
	{
		if(odd[i])
			return i;
	}
	for(int i=(id_r-1)*sn+1;i<=r;++i)
	{
		if(odd[i])
			return i;
	}
	for(int i=id_l+1;i<=id_r-1;++i)
	{
		if(cnt[i])
		{
			for(int j=(i-1)*sn+1;j<=i*sn;++j)
			{
				if(odd[j])
					return j;
			}
		}
	}
	return -1;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	for(int i=1;i<=n-1;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	dfs(1,0);
	dfs1(1,0);
	dfs2(1,1);
	sn=int(sqrt(n));
	int s=int(2*n/sqrt(m));
	for(int i=1;i<=m;++i)
	{
		int u,v,l,r;
		scanf("%d%d%d%d",&u,&v,&l,&r);
		if(dfn[u][0]>dfn[v][0])
			swap(u,v);
		int p=get_LCA(u,v);
		if(p==u)
			q[i].l=dfn[u][0],q[i].r=dfn[v][0];
		else
			q[i].l=dfn[u][1],q[i].r=dfn[v][0],q[i].lca=p;
		q[i].L=l,q[i].R=r,q[i].id=i;
		q[i].blo=(q[i].l-1)/s+1;
	}
	sort(q+1,q+m+1,cmp);
	int L=1,R=0;
	for(int i=1;i<=m;++i)
	{
		while(L<q[i].l)
			work(id[L++]);
		while(L>q[i].l)
			work(id[--L]);
		while(R<q[i].r)
			work(id[++R]);
		while(R>q[i].r)
			work(id[R--]);
		if(q[i].lca)
			work(q[i].lca);
		ans[q[i].id]=query(q[i].L,q[i].R);
		if(q[i].lca)
			work(q[i].lca);
	}
	for(int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}
```

PS：出题人应该是想放这种解法过的，因为另外一种时间复杂度更优秀的正解只需 1s 左右，但时限是 5s，而这份代码最大用时 4742 ms。

## 思路二

### 分析 + 题解

题目的要求相当于“**奇数次算出现，偶数次算没出现**”，这跟**异或**的性质类似，考虑用异或值来刻画询问是否有解。

定义 $f(u,v,l,r)$ 表示 $u$ 到 $v$ 路径上权值 $\in [l,r]$ 的权值的异或和，则若无解，必有 $f(u,v,l,r) = 0$。进一步，若 $f(u,v,l,r) \neq 0$，必然有解。

但即使有解，$f(u,v,l,r)=0$ 仍然有很大概率成立（或者说很容易构造这样的例子）。为了解决这个问题，我们将原来的 $n$ 种权值映射到新的 $n$ 种权值，使得“$f(u,v,l,r)=0$ 等价于无解”**有足够大的概率成立**。

具体来说，设 $X$ 是一组大小为 $n$ 的**值域**为 $[0,2^{64})$ 的**随机变量**，将权值 $i$ 映射为权值 $X_i$ 即可使得：对于单次查询，上述式子成立的概率 $p \ge 1-2^{-64}$；对于 $q$ 次查询，上述式子均成立的概率为：

$$
\begin{aligned}
Pr\big[\bigwedge_{i=1}^{q}A_i\big]&=1-Pr\big[\bigvee_{i=1}^{q}\overline{A}_i\big]\\
&\ge 1-\sum_{i=1}^{q}Pr[\overline{A}_i]\\
&=1-\sum_{i=1}^{q}(1-Pr[A_i])\\
&\ge 1-\sum_{i=1}^{q}(1-(1-2^{-64}))\\
&=1-2^{-64}q
\end{aligned}
$$

当 $q \le 2^{20}$ 时，该概率不小于 $1-2^{-64}q \ge 1-2^{-44}$，近似于 $1$。

我们知道，原问题相当于求区间 $[l,r]$ 中的某个 $c$ 使得 $f(u,v,c,c) \neq 0$，那么如何维护 $f$ 值呢？

先来一个常用套路，一条路径拆成四条节点到根的链：

$$f(u,v,l,r)=f(1,u,l,r) \oplus f(1,v,l,r) \oplus f(1,lca(u,v),l,r) \oplus f(1,father(lca(u,v)),l,r)$$

因此只需维护 $f(1,x,l,r)$，使用**可持久化线段树**，**时间复杂度**为 $O(n\log{n}+q\log{n})$。（根据“$f(u,v,l,r)=0$ 等价于无解”这一性质，我们可以在线段树上二分求解，具体实现见代码）

PS：由于 $f(1,lca(u,v),l,r) \oplus f(1,father(lca(u,v)),l,r)=f(lca(u,v),lca(u,v),l,r)$，你也可以每个点额外再开一颗线段树，用于直接查询后两项。


### 代码

需要注意的是，查询时一旦找到答案，就不再继续求解，否则时间复杂度会变成 $O(n\log{n}+q\log^2{n})$。

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
const int max_n=3e5+5;
int End[max_n<<1],Last[max_n],Next[max_n<<1],e;
inline void add_edge(int x,int y)
{
	End[++e]=y;
	Next[e]=Last[x];
	Last[x]=e;
	End[++e]=x;
	Next[e]=Last[y];
	Last[y]=e;
}
int dep[max_n],fath[max_n],sz[max_n],son[max_n];
void dfs1(int x,int fa)
{
	dep[x]=dep[fa]+1;
	fath[x]=fa;
	sz[x]=1;
	son[x]=-1;
	int max_sz=0;
	for(int i=Last[x];i;i=Next[i])
	{
		int y=End[i];
		if(y!=fa)
		{
			dfs1(y,x);
			sz[x]+=sz[y];
			if(sz[y]>max_sz)
			{
				max_sz=sz[y];
				son[x]=y;
			}
		}
	}
}
int _top[max_n];
void dfs2(int x,int top_now)
{
	_top[x]=top_now;
	if(son[x]!=-1)
		dfs2(son[x],top_now);
	for(int i=Last[x];i;i=Next[i])
	{
		int y=End[i];
		if(y!=fath[x]&&y!=son[x])
			dfs2(y,y);
	}
}
inline int get_LCA(int x,int y)
{
	while(_top[x]!=_top[y])
	{
		if(dep[_top[x]]<dep[_top[y]])
			swap(x,y);
		x=fath[_top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int a[max_n];
unsigned long long X[max_n];
namespace SegmentTree
{
	const int max_sz=20*3e5+5;
	unsigned long long val[max_sz];
	int ls[max_sz],rs[max_sz],cnt_node;
	void modify(int old,int &p,int l,int r,int k,unsigned long long v)
	{
		p=++cnt_node;
		val[p]=val[old]^v,ls[p]=ls[old],rs[p]=rs[old];
		if(l<r)
		{
			int mid=(l+r)>>1;
			if(k<=mid)
				modify(ls[old],ls[p],l,mid,k,v);
			else
				modify(rs[old],rs[p],mid+1,r,k,v);
		}
	}
	int res;
	void query(int p1,int p2,int p3,int p4,int l,int r)
	{
		if(l==r)
		{ 
			res=l;
			return;
		}
		int mid=(l+r)>>1;
		if(val[ls[p1]]^val[ls[p2]]^val[ls[p3]]^val[ls[p4]])
			query(ls[p1],ls[p2],ls[p3],ls[p4],l,mid);
		else
			query(rs[p1],rs[p2],rs[p3],rs[p4],mid+1,r);
	}
	void query(int p1,int p2,int p3,int p4,int l,int r,int a,int b)
	{
		if(a<=l&&r<=b)
		{
			if(val[p1]^val[p2]^val[p3]^val[p4])
				query(p1,p2,p3,p4,l,r);
			return;
		}
		int mid=(l+r)>>1;
		if(a<=mid)
			query(ls[p1],ls[p2],ls[p3],ls[p4],l,mid,a,b);
		if(b>mid&&res==-1)
			query(rs[p1],rs[p2],rs[p3],rs[p4],mid+1,r,a,b);
	}
}
int root[max_n];
void dfs(int x,int fa)
{
	SegmentTree::modify(root[fa],root[x],1,n,a[x],X[a[x]]);
	for(int i=Last[x];i;i=Next[i])
	{
		int y=End[i];
		if(y!=fa)
			dfs(y,x);
	}
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	for(int i=1;i<=n-1;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add_edge(x,y);
	}
	dfs1(1,0);
	dfs2(1,1);
	srand(time(NULL));
	for(int i=1;i<=n;++i)
		X[i]=1ull*rand()<<60|1ull*rand()<<45|1ull*rand()<<30|1ull*rand()<<15|1ull*rand();
	dfs(1,0);
	while(q--)
	{
		int u,v,l,r;
		scanf("%d%d%d%d",&u,&v,&l,&r);
		int p=get_LCA(u,v);
		SegmentTree::res=-1;
		SegmentTree::query(root[u],root[v],root[p],root[fath[p]],1,n,l,r);
		printf("%d\n",SegmentTree::res);
	}
	return 0;
}
```

### 有关 $X$ 的随机生成

上述代码中使用的方法是，将 $5$ 个 `rand()` 函数通过移位进行叠加，即：

``` cpp
srand(time(NULL));
for(int i=1;i<=n;++i)
	X[i]=1ull*rand()<<60|1ull*rand()<<45|1ull*rand()<<30|1ull*rand()<<15|1ull*rand();
```

（在 Windows 下，`rand()` 的取值范围为 $[0,2^{15})$）

你也可以使用比较高级的随机数：

``` cpp
mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());
for(int i=1;i<=n;++i)
	X[i]=rd();
```

事实上，本人一开始使用的是下面这种方法，会被 test 7 的第 $164990$ 个询问卡掉，答案不为 `-1`，但代码输出 `-1`。

``` cpp
srand(time(NULL));
for(int i=1;i<=n;++i)
	for(int j=0;j<64;++j)
		X[i]=X[i]<<1|(rand()&1);
```

（即从高到低每一个二进制位均为 `rand()&1`，我试过其它种子，都会被同样卡掉）

个人理解是因为 `rand()` 的均匀随机性不高，容易出现循环——**这只是感性理解，如果你能给出更严谨的解答或构造这样的 Hack 数据，请务必私信告知我，我会将其添加至该篇文章，供大家学习。**

---

## 作者：Plozia (赞：3)

宣传博客 $\to$ [link](https://blog.csdn.net/BWzhuzehao/article/details/118999062)

本题有两种算法，一种是 $\log n$ 级别算法，一种是 $\sqrt{n}$ 级别算法，这里只讲根号算法。

这道题就是一个树上数颜色问题，只是颜色被限定在一个区间。

如果你做过 [P4396 [AHOI2013]作业](https://www.luogu.com.cn/problem/P4396)，我相信你能一眼看出这道题的做法。

数颜色问题的根号算法做法一般是莫队，而这道题是树上莫队。

如果你没学过莫队，看一下[我的算法总结](https://blog.csdn.net/BWzhuzehao/article/details/110889871)。

如果你没学过树上莫队但是学过莫队，可以看[我的算法总结](https://blog.csdn.net/BWzhuzehao/article/details/110940154)，也可以在代码后面看我写的简要描述。

好的下面默认你学会了树上莫队。

那么有一种方法就是我们在树上莫队的时候维护一棵线段树，对于加删操作而言我们在线段树对应位置修改，线段树中维护当前区间是否存在奇数个颜色，查询时直接查即可。

这个做法的复杂度是 $O(q \log n \sqrt{n}+q \log n)$ 的，会被 #7 卡 TLE。

发现修改操作复杂度 $q \log n \sqrt{n}$ 远大于查询操作复杂度 $q \log n$，因此我们需要考虑平衡一下这两者。

因此我们可以采用值域分块。

如果你没学过值域分块，建议先去学一下分块（[我的算法总结](https://blog.csdn.net/BWzhuzehao/article/details/111057797)），然后类比值域线段树，值域分块就是在值域上分块。

值域分块有一个好处是 $O(1)$ 修改 $O(\sqrt{n})$ 查询，而这可以平衡复杂度，使得修改操作和查询操作都是 $O(q\sqrt{n})$。

需要注意的是如果块长不当，可能会被 #7 卡掉，这里建议调成理论最优块长 $\dfrac{2n}{\sqrt{m}}$（$2n$ 是因为欧拉序长为 $2n$），如果还不过就在这附近调块长。

Code：[GitHub CodeBase-of-Plozia CF1479D Odd Mineral Resource.cpp](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/Codeforces%20%E5%88%B7%E9%A2%98%E5%90%88%E9%9B%86/CF1479D%20Odd%20Mineral%20Resource.cpp)

```cpp
/*
========= Plozia =========
	Author:Plozia
	Problem:CF1479D Odd Mineral Resource
	Date:2021/7/21
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 3e5 + 5;
int n, m, Head[MAXN], cnt_Edge = 1, cnt_n, Eular[MAXN << 1], a[MAXN], fa[MAXN][21], Block, Num_Block, dep[MAXN], ys[MAXN << 1], val[MAXN], sum[MAXN], fir[MAXN], las[MAXN], ans[MAXN], book[MAXN];
struct node { int to, Next; } Edge[MAXN << 1];
struct Query { int x, y, l, r, id, lca; } q[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10)+ (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }
bool cmp(const Query &fir, const Query &sec) { return (ys[fir.x] ^ ys[sec.x]) ? (fir.x < sec.x) : ((ys[fir.x] & 1) ? (fir.y < sec.y) : (fir.y > sec.y)); }

void dfs(int now, int father)
{
	Eular[++cnt_n] = now, fa[now][0] = father; fir[now] = cnt_n; dep[now] = dep[father] + 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].to;
		if (u == father) continue ;
		dfs(u, now);
	}
	Eular[++cnt_n] = now; las[now] = cnt_n;
}

void init()
{
	for (int j = 1; j <= 20; ++j)
		for (int i = 1; i <= n; ++i)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
}

int LCA(int x, int y)
{
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int i = 20; i >= 0; --i)
		if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if (x == y) return x;
	for (int i = 20; i >= 0; --i)
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

void Add(int x)
{
	++val[a[x]];
	if (val[a[x]] & 1) ++sum[(a[x] - 1) / Num_Block + 1];
	else --sum[(a[x] - 1) / Num_Block + 1];
}

void Del(int x)
{
	--val[a[x]];
	if (val[a[x]] & 1) ++sum[(a[x] - 1) / Num_Block + 1];
	else --sum[(a[x] - 1) / Num_Block + 1];
}

void Work(int x)
{
	book[x] ? Del(x) : Add(x);
	book[x] ^= 1;
}

int Ask(int l, int r)
{
	int yl = (l - 1) / Num_Block + 1, yr = (r - 1) / Num_Block + 1;
	if (yl == yr)
	{
		for (int i = l; i <= r; ++i)
			if (val[i] & 1) return i;
		return -1;
	}
	int el = yl * Num_Block, br = (yr - 1) * Num_Block + 1;
	for (int i = l; i <= el; ++i)
		if (val[i] & 1) return i;
	for (int i = br; i <= r; ++i)
		if (val[i] & 1) return i;
	for (int i = yl + 1; i <= yr - 1; ++i)
	{
		if (sum[i])
		{
			l = (i - 1) * Num_Block + 1, r = i * Num_Block;
			for (int j = l; j <= r; ++j)
				if (val[j] & 1) return j;
		}
	}
	return -1;
}

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= n; ++i) a[i] = Read();
	for (int i = 1; i < n; ++i) { int x = Read(), y = Read(); add_Edge(x, y); add_Edge(y, x); }
	dfs(1, 1); init(); Block = cnt_n / sqrt(m); Num_Block = sqrt(n);
	for (int i = 1; i <= cnt_n; ++i) ys[i] = (i - 1) / Block + 1;//cnt_n=2n
	for (int i = 1; i <= m; ++i)
	{
		q[i].x = Read(), q[i].y = Read(), q[i].l = Read(), q[i].r = Read(), q[i].id = i;
		q[i].lca = LCA(q[i].x, q[i].y);
		if (fir[q[i].x] > fir[q[i].y]) std::swap(q[i].x, q[i].y);
		if (q[i].x == q[i].lca) { q[i].x = fir[q[i].x]; q[i].y = fir[q[i].y]; q[i].lca = 0; }
		else { q[i].x = las[q[i].x]; q[i].y = fir[q[i].y]; }
	}
	std::sort(q + 1, q + m + 1, cmp);
	int l = 1, r = 0;
	for (int i = 1; i <= m; ++i)
	{
		while (l > q[i].x) Work(Eular[--l]);
		while (r < q[i].y) Work(Eular[++r]);
		while (l < q[i].x) Work(Eular[l++]);
		while (r > q[i].y) Work(Eular[r--]);
		if (q[i].lca) Work(q[i].lca);
		ans[q[i].id] = Ask(q[i].l, q[i].r);
		if (q[i].lca) Work(q[i].lca);
	}
	for(int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
	return 0;
}
```

树上莫队简介：

做树上莫队，你需要知道欧拉序。

欧拉序就是 DFS 序的升级版，在每一次遍历到这个节点的时候记录一次，离开这个节点的时候再记录一次。

一般采用 $fir_{x}$ 表示 $x$ 在欧拉序中第一个出现的位置，$las_{x}$ 表示 $x$ 在欧拉序中第二个（最后一个）出现的位置。

当一个询问询问路径 $x \to y$ 的时候，如果 $x,y$ 在一条链上，询问的区间就是 $[fir_x,fir_y]$，否则就是 $[las_x,fir_y]$，具体询问区间可以使用 LCA 判断。

需要注意的是当询问 $[las_x,fir_y]$ 的时候，不能忘记计算他们 LCA 的贡献。

> LCA：树上最近公共祖先。

由于一个点在欧拉序中会出现两次，因此树上莫队的修改采用奇增偶删原则，即若这个点是奇数次被修改就增加，偶数次被修改就减少。

写的有点少大致看看吧qwq

---

## 作者：dead_X (赞：3)

## 前言
场上没开这题！！1

A 被 hack 了！！1

掉分了！！1
## 思路
前置知识：CF1000F 的均摊复杂度分析。

考虑树上莫队，每次移动端点时，维护每个数的出现次数。

然后对每个点的权值值域分块。对于每个值域块，维护一个栈，当某个数被访问到且还没入栈的时候就将它加入对应值域块的栈。

于是我们保证了每次移动完端点后，**所有可能成为答案的数**都在栈中。

这样我们只要对整块的 $\sqrt n$ 个栈不断弹出直到找到答案或栈空时停止，再对两边散块直接查询出现次数即可。

移动端点单次复杂度 $O(1)$，每个询问查询单次复杂度 $O(\sqrt n+popcnt)$，$\sum popcnt=O(n\sqrt n)$，因此总复杂度 $O(n\sqrt n)$。
## 代码
$4991$ 毫秒，差点就最劣解了/shake
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while('0'<=ch && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
int n,m,qcnt,bl,Q;
int a[600003],cnt[300003];
int Ans[600003];
struct query
{
	int vl,vr,l,r,id,pl,qwq;
	bool operator<(const query&a) const { return (pl<a.pl)||(pl==a.pl&&r<a.r); }
}q[600003];
int nxt[600003],head[300003],to[600003],ecnt;
int IN[300003],OUT[300003],CNT;
int A[600003],d[300003],fa[300003][20];
bool flag[300003];
stack<int> s[603];
inline void ins(int x)
{
	if(flag[x]) --cnt[a[x]];
	else ++cnt[a[x]];
	if(cnt[a[x]]&1) s[a[x]>>10].push(a[x]);
	flag[x]^=1;
} 
inline void dfs(int x,int y)
{
	fa[x][0]=y,d[x]=d[y]+1;
	for(int i=1; i<=19; i++) fa[x][i]=fa[fa[x][i-1]][i-1];
	IN[x]=++CNT,A[CNT]=x;
	for(int i=head[x]; i; i=nxt[i]) if(to[i]!=y) dfs(to[i],x);
	OUT[x]=++CNT,A[CNT]=x;
}
inline int LCA(int x,int y)
{
	if(d[x]>d[y]) swap(x,y);
	for(int i=19; i>=0; i--) if(d[x]<=d[fa[y][i]]) y=fa[y][i];
	if(x==y) return x;
	for(int i=19; i>=0; i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
signed main()
{
	n=read(),Q=read(),bl=sqrt(n)*2+1;
	for(int i=1; i<=n; i++) a[i]=read();
	for(int i=1,u,v; i<n; i++) u=read(),v=read(),
	to[++ecnt]=v,nxt[ecnt]=head[u],head[u]=ecnt,
	to[++ecnt]=u,nxt[ecnt]=head[v],head[v]=ecnt;
	dfs(1,1);
	for(int i=1,x,y,l,r; i<=Q; i++) 
	{
		x=read(),y=read(),l=read(),r=read();
		if(IN[x]>IN[y]) swap(x,y);
		if(LCA(x,y)==x) q[++qcnt].l=IN[x],q[qcnt].r=IN[y];
		else q[++qcnt].l=OUT[x],q[qcnt].r=IN[y],q[qcnt].qwq=LCA(x,y);
		q[qcnt].pl=q[qcnt].l/bl,q[qcnt].id=qcnt,q[qcnt].vl=l,q[qcnt].vr=r;
	}
	sort(q+1,q+qcnt+1),memset(Ans,-1,sizeof(Ans));
	for(int i=1,l=1,r=0; i<=qcnt; i++)
	{
		while(l<q[i].l) ins(A[l++]);
		while(l>q[i].l) ins(A[--l]);
		while(r<q[i].r) ins(A[++r]);
		while(r>q[i].r) ins(A[r--]);
		if(q[i].qwq) ins(q[i].qwq);
		int L=q[i].vl,R=q[i].vr,pl=L>>10,pr=R>>10;
		if(pl==pr)
		{
			for(int j=L; j<=R; ++j) if(cnt[j]&1)
			{
				Ans[q[i].id]=j;
				break;
			 } 
		}
		else
		{
			for(int j=L,t=(pl+1)<<10; j<t; ++j) if(cnt[j]&1)
			{
				Ans[q[i].id]=j;
				break;
			} 
			if(Ans[q[i].id]==-1) for(int j=pr<<10; j<=R; ++j) if(cnt[j]&1)
			{
				Ans[q[i].id]=j;
				break;
			} 
			if(Ans[q[i].id]==-1) for(int j=pl+1; j<pr; ++j)
			{
				while(!s[j].empty())
				{
					if(cnt[s[j].top()]&1) 
					{
						Ans[q[i].id]=s[j].top();
						break;
					}
					else s[j].pop();
				}	
				if(Ans[q[i].id]!=-1) break;
			}
		}
		if(q[i].qwq) ins(q[i].qwq);
	} 
	for(int i=1; i<=qcnt; i++) printf("%d\n",Ans[i]);
	return 0;
}
```

---

## 作者：orz_z (赞：0)

### CF1479D Odd Mineral Resource

`CF1000F` 上树，考虑树上莫队。

同理，对值域分块，记 $sum_i$ 表示第 $i$ 块值域出现次数为奇数的数的个数，再开个桶记录一下每个数的出现次数就行了，单次修改 $\mathcal O(1)$。

对于询问，同块暴力，否则从左散块，中整块，右散块判断，找到就结束，单次询问 $\mathcal O(\sqrt n)$。

说下树上莫队的细节：

* 建括号序，有两种情况，有一种需特判 `LCA`（树剖维护）。
* 注意一些加加减减的细节问题，本人模拟赛因为这爆零。

综上，时间复杂度 $\mathcal O(n\sqrt n)$，空间复杂度 $\mathcal O(n)$，$n$ 与值域同阶。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define he putchar('\n')
#define ha putchar(' ')

typedef long long ll;

inline int read() {
	int x = 0;
	char c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x;
}

inline void write(int x) {
	if (x < 0) {
		x = -x;
		putchar('-');
	}
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}

const int _ = 7e5 + 10;

int n, m, cnt, a[_], L[_], R[_], fn[_], ans[_];

int sq, bel[_];

vector<int> d[_];

void dfs(int u, int fa) {
	fn[++cnt] = u, L[u] = cnt;
	for (int v : d[u]) {
		if (v == fa) continue;
		dfs(v, u);
	}
	fn[++cnt] = u, R[u] = cnt;
}

int siz[_], dep[_], fa[_], hson[_], top[_];

void dfs1(int u, int D = 1) {
	siz[u] = 1, dep[u] = D;
	for (int v : d[u])
		if (!siz[v]) {
		fa[v] = u;
		dfs1(v, D + 1);
		siz[u] += siz[v];
		if (siz[hson[u]] < siz[v]) hson[u] = v;
	}
}

void dfs2(int u, int tf) {
	top[u] = tf;
	if (hson[u]) dfs2(hson[u], tf);
	for (int v : d[u])
		if (!top[v]) dfs2(v, v);
}

int LCA(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] > dep[v] ? v : u;
}

struct Query {
	int l, r, L, R, id, dd;
} q[_];

bool cmp(Query x, Query y) {
	if (bel[x.L] != bel[y.L]) return x.L < y.L;
	if (bel[x.L] & 1) return x.R < y.R;
	return x.R > y.R;
}

int t[_], sum[_], lp[_], rp[_];

void upd(int x) {
	if (t[x] & 1) sum[bel[x]]--;
	else sum[bel[x]]++;
	t[x] ^= 1;
}

signed main() {
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i < n; ++i) {
		int x = read(), y = read();
		d[x].push_back(y), d[y].push_back(x);
	}
	dfs(1, 0);
	dfs1(1), dfs2(1, 1);
	sq = sqrt(cnt) * 1.2;
	for (int i = 1; i <= cnt; ++i) bel[i] = (i - 1) / sq + 1;
	for (int i = 1; i <= bel[cnt]; ++i) lp[i] = rp[i - 1] + 1, rp[i] = min(cnt, i * sq);
	for (int i = 1, u, v; i <= m; ++i) {
		u = read(), v = read();
		q[i].l = read(), q[i].r = read(), q[i].id = i;
		if (L[u] > L[v]) swap(u, v);
		if (R[u] < L[v]) q[i].L = R[u], q[i].R = L[v], q[i].dd = LCA(u, v);
		else q[i].L = L[u], q[i].R = L[v];
	}
	sort(q + 1, q + m + 1, cmp);
	int l = 0, r = 0;
	for (int i = 1; i <= m; ++i) {
		while (l > q[i].L) upd(a[fn[--l]]);
		while (r < q[i].R) upd(a[fn[++r]]);
		while (l < q[i].L) upd(a[fn[l++]]);
		while (r > q[i].R) upd(a[fn[r--]]);
		upd(a[fn[L[q[i].dd]]]);
		bool flg = 0;
		if (bel[q[i].l] == bel[q[i].r]) {
			for (int j = q[i].l; j <= q[i].r; ++j)
				if (t[j] & 1) {ans[q[i].id] = j, flg = 1;break;}
		} else {
			if (!flg) for (int j = q[i].l; j <= rp[bel[q[i].l]]; ++j) if (t[j] & 1) {ans[q[i].id] = j;flg = 1;break;}
			if (!flg) for (int j = bel[q[i].l] + 1; j <= bel[q[i].r] - 1; ++j) if (sum[j]) {
				for (int k = lp[j]; k <= rp[j]; ++k) if (t[k] & 1) {ans[q[i].id] = k;flg = 1;break;}
				if (flg) break;
			}
			if (!flg) for (int j = lp[bel[q[i].r]]; j <= q[i].r; ++j) if (t[j] & 1) {ans[q[i].id] = j;flg = 1;break;}
		}
		if (!flg) ans[q[i].id] = -1;
		upd(a[fn[L[q[i].dd]]]);
	}
	for (int i = 1; i <= m; ++i) write(ans[i]), he;
	return 0;
}
```



---

## 作者：xfrvq (赞：0)

树上奇怪问题，$n=3\times10^5$，直接考虑根号。

树上莫队，然后套上值域分块维护每个位置颜色的奇偶性，每个块奇颜色的个数。

卡常：

+ 树剖求 $\tt LCA$（你甚至可以写基于括号序、$\tt RMQ$ 的 $\mathcal O(1)$ 复杂度 $\tt LCA$，但是树剖就够了）
+ $\tt IO$ 优化（较为常规，用处不大）
+ $\texttt{inline,register}$（我觉得有点用）
+ 莫队块长 $\dfrac {2n}{\sqrt m}$（挺快，但是微调会更好）
+ 分块块长瞎调

模拟赛被卡常了，没过，遗憾。

```cpp
const int N = 3e5 + 5,SQ = 560;

int n,m,a[N],in[N],out[N],ans[N],path[N * 2];
vector<int> G[N];
struct qry{ int l,r,L,R,p,i; } Q[N];
int dep[N],siz[N],son[N],fa[N],top[N],tot;
int B,C,st[SQ],ed[SQ],bl[N],sum[SQ],cnt[N];

inline void dfs1(int u = 1,int ft = 0){
	dep[u] = dep[fa[u] = ft] + 1; siz[u] = 1;
	for(int v : G[u]) if(v != ft){
		dfs1(v,u);
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}

inline void dfs2(int u = 1,int tp = 1){
	top[u] = tp;
	path[in[u] = ++tot] = u;
	if(son[u]) dfs2(son[u],tp);
	for(int v : G[u]) if(!top[v]) dfs2(v,v);
	path[out[u] = ++tot] = u;
}

inline int lca(int u,int v){
	while(top[u] != top[v]){
		if(dep[top[u]] < dep[top[v]]) swap(u,v);
		u = fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
}

inline void init(){
	B = 600; C = (n - 1) / B + 1;
	rep(i,1,C){
		st[i] = ed[i] + 1;
		ed[i] = (i == C) ? n : i * B;
		rep(j,st[i],ed[i]) bl[j] = i;
	}
}

inline void Upd(int x){
	(cnt[x] ^= 1) ? ++sum[bl[x]] : --sum[bl[x]];
}

inline int Qry(int L,int R){
	if(bl[L] == bl[R]){
		rep(i,L,R) if(cnt[i]) return i;
		return -1;
	}
	rep(i,L,ed[bl[L]]) if(cnt[i]) return i;
	rep(i,bl[L] + 1,bl[R] - 1) if(sum[i])
		rep(j,st[i],ed[i]) if(cnt[i]) return i;
	rep(i,st[bl[R]],R) if(cnt[i]) return i;
	return -1;
}

int main(){
	n = read(),m = read(); init();
	rep(i,1,n) a[i] = read();
	rep(i,1,n - 1){
		int u = read(),v = read();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs1(); dfs2();
	rep(i,1,m){
		int u = read(),v = read(),p = lca(u,v);
		int L = read(),R = read();
		if(in[u] > in[v]) swap(u,v);
		if(p != u && p != v) Q[i] = (qry){out[u],in[v],L,R,p,i};
		else Q[i] = (qry){in[u],in[v],L,R,0,i};
	}
	int Bl = 2 * n / sqrt(m);
	sort(Q + 1,Q + m + 1,[Bl](qry x,qry y){
		return (x.l / Bl) ^ (y.l / Bl) ? x.l < y.l : (x.l / Bl) & 1 ? x.r < y.r : x.r > y.r;
	});
	int l = 1,r = 0;
	rep(i,1,m){
		while(r < Q[i].r) Upd(a[path[++r]]);
		while(l > Q[i].l) Upd(a[path[--l]]);
		while(r > Q[i].r) Upd(a[path[r--]]);
		while(l < Q[i].l) Upd(a[path[l++]]);
		if(Q[i].p) Upd(a[Q[i].p]);
		ans[Q[i].i] = Qry(Q[i].L,Q[i].R);
		if(Q[i].p) Upd(a[Q[i].p]);
	}
	rep(i,1,m) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：RyexAwl (赞：0)

考虑在序列上我们怎么做：

考虑莫队去维护一个值域分块，该值域分块每块维护出现次数为奇数的数的个数，对于每个整块查一下其出现次数为奇数的数的个数，如果不为 $0$ 则遍历该块内的元素，找到合法的 $x$ 直接输出。 并且这个值域分块我们可以做到 $O(1)$ 修改 $O(\sqrt{N})$ 查询，因此总的复杂度即 $O(M\sqrt{N} + N\sqrt{M})$。

直接将上面做法上树即可。

卡常小技巧（雾）：只离散化点权并在此基础上建立值域分块，每个询问二分对应区间。

```cpp
#include <bits/stdc++.h>
 
namespace wxy{
 
const int N = 3e5+5,Q = 3e5+5;
 
int head[N],edge[N<<1],fail[N<<1],tot;
 
int w[N],b[N<<2],a[N<<1],c[N<<2],n,m,q,dfn,S;
 
int ans[Q],f[25][N],d[N],st[N],ed[N],use[N<<2],bm[N],cnt[N<<2],cj[N];
 
bool vis[N];
 
struct node{int u,v,l,r,LCA,idx;}ask[Q],qa[Q];
 
inline int read(){
    int s=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)) s=s*10+ch-'0',ch=getchar();
    return s*f;
}
 
inline int get(int x){return std::lower_bound(b + 1,b + 1 + m,x) - b;}
 
inline bool cmp(node a,node b){return (a.v/1001)==(b.v/1001)?a.u<b.u:a.v<b.v;}
 
inline void ins(int x,int y){
    edge[++tot] = y;
    fail[tot] = head[x];
    head[x] = tot;
}
 
inline void dfs(int x){
    vis[x] = true; st[x] = ++dfn; a[dfn] = x;
    for (int i = 1; i <= 19; i++)
        f[i][x] = f[i-1][f[i-1][x]];
    for (int i = head[x]; i; i = fail[i]){
        int v = edge[i];
        if (vis[v]) continue;
        d[v] = d[x] + 1; f[0][v] = x;
        dfs(v);
    }
    ed[x] = ++dfn; a[dfn] = x;
}
 
inline int lca(int x,int y){
    if (d[x] < d[y]) std::swap(x,y);
    for (int i = 19; i >= 0; i--)
        if (d[f[i][x]] >= d[y]) x = f[i][x];
    if (x == y) return x;
    for (int i = 19; i >= 0; i--)
        if (f[i][x] != f[i][y]) {x = f[i][x]; y = f[i][y];}
    return f[0][x];
}
 
inline int getL(int idx){return (idx-1)*S+1;}
inline int getR(int idx){return std::min(idx*S,m);}
 
inline void init(){for (int i = 1; i <= m; i++) bm[i] = (i-1)/S+1;}
 
inline int bf(int l,int r){
    for (int i = l; i <= r; i++)
        if (cnt[i] % 2 == 1) return b[i];
    return -1;
}
 
inline int query(int l,int r){
    if (bm[l] == bm[r]) return bf(l,r);
    for (int i = l; i <= getR(bm[l]); i++){
        if (cnt[i] % 2 == 1) return b[i];
    }
    for (int i = getL(bm[r]); i <= r; i++){
        if (cnt[i] % 2 == 1) return b[i];
    }
    for (int i = bm[l] + 1; i < bm[r]; i++)
        if (cj[i] > 0) return bf(getL(i),getR(i));
    return -1;
}
 
inline void change(int x,int v){cnt[x] += v;cnt[x]%2==0?cj[bm[x]]--:cj[bm[x]]++;}
 
inline void add(int x){change(x,1);}
inline void del(int x){change(x,-1);}
 
inline void Add(int x){use[x] ? del(w[x]) : add(w[x]); use[x] ^= 1;}
 
inline void solve(){
    init();int l = 1,r = 0; //std::cout << q;
    for (int i = 1; i <= q; i++){
        int ql = qa[i].u,qr = qa[i].v;
        int qL = qa[i].l,qR = qa[i].r; 
        //std::cout << qL << " " << qR << std::endl;
        while (l < ql){Add(a[l]); l++;}
        while (l > ql){l--; Add(a[l]);}
        while (r < qr){r++; Add(a[r]);}
        while (r > qr){Add(a[r]); r--;}
        if (qa[i].l == qa[i].r && qa[i].l == 0) {ans[qa[i].idx] = -1; continue;}
        if (qa[i].LCA != -1) Add(qa[i].LCA);
        ans[qa[i].idx] = query(qL,qR);
        if (qa[i].LCA != -1) Add(qa[i].LCA);
    }
}
 
inline void fprint(){for (int i = 1; i <= q; i++) printf("%d\n",ans[i]);}
 
inline void initlr(){
    for (int i = 1; i <= q; i++){
        int l = ask[i].l,r = ask[i].r;
        int pl = get(l),pr = get(r);
        if (pr > m) pr--;
        if (pl > m) pl--;
        if (b[pl] > r) {ask[i].l = ask[i].r = 0; continue;}
        if (b[pr] > r) pr--;
        if (b[pr] < l) {ask[i].l = ask[i].r = 0; continue;}
        ask[i].l = pl; ask[i].r = pr;
    }
}

inline void main(){
    #ifndef ONLINE_JUDGE
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    dfn = m = tot = 0; memset(d,-1,sizeof d);
    n = read(); q = read(); S = 800;
    for (int i = 1; i <= n; i++) w[i] = read();
    for (int i = 1; i <= n; i++) c[i] = w[i]; int idx = n;
    std::sort(c + 1,c + 1 + idx);
    for (int i = 1; i <= idx; i++)
        if (i == 1 || c[i] != c[i-1]) b[++m] = c[i];
    for (int i = 1; i <= n; i++) w[i] = get(w[i]);
    for (int i = 1; i < n; i++){
        int a,b; a = read(); b = read();
        ins(a,b); ins(b,a);
    }
    d[1] = 0; dfs(1);
    for (int i = 1; i <= q; i++){
        ask[i].u = read(); ask[i].v = read(); 
        ask[i].l = read(); ask[i].r = read();
    }
    initlr();
    for (int i = 1; i <= q; i++){
        if (st[ask[i].u] > st[ask[i].v]) std::swap(ask[i].u,ask[i].v);
        int LCA = lca(ask[i].u,ask[i].v); //ask[i].l = get(ask[i].l); ask[i].r = get(ask[i].r);
        int x = ask[i].u,y = ask[i].v;
        if (LCA == x) {qa[i].u = st[x]; qa[i].v = st[y]; qa[i].LCA = -1;}
        else {qa[i].u = ed[x]; qa[i].v = st[y]; qa[i].LCA = LCA;}
        qa[i].idx = i; qa[i].l = ask[i].l; qa[i].r = ask[i].r;
    }
    std::sort(qa + 1,qa + 1 + q,cmp);
    solve(); fprint();
}
 
}signed main(){wxy::main(); return 0;}
```


---

## 作者：Warriors_Cat (赞：0)

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF1479D) & [CF 题面传送门](https://www.luogu.com.cn/problem/CF1479D)。

> 题意：给定 $n$ 个点的树和 $m$ 个操作，点有颜色，每次询问有没有一种颜色属于特定区间并在特定路径上出现奇数次。

>$n, m \le 3\times 10^5$。

~~又是一道 DS 神仙题，而且码量极大，debug 极久，不愧为 *2900 的题。~~

---

### $Solution:$

以下默认 $n, m$ 同阶

看到数颜色的题久想到用莫队，由于是树上的所以我们还要套一个树上莫队。

我们对颜色进行分块，对于每一个块，我们维护一个数组，当我们在莫队移动端点的时候就把没出现过的颜色全都丢进所在块的数组里。很显然，此时**数组内所有的元素不一定是答案，而所有可能的答案都一定会在这个数组里。**

那么，我们查询的时候，散点直接暴力查询即可，整块就一直找这个数组里有没有合法的，而且不合法的直接从这个数组中移除即可。

分析一下时间复杂度，首先树上莫队的复杂度是 $O(n\sqrt n)$ 的，由于移动次数是 $n\sqrt n$，故进入数组的次数是 $n\sqrt n$，总时间复杂度即为 $O(n\sqrt n)$。

这样就搞定了，只是树上莫队的板子可能有点长而已。

---
### $Code:$

代码可能有亿点长，请耐心食用。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define mpr make_pair
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
#define y0 y_csyakioi_0
#define y1 y_csyakioi_1
#define rep(i, x, y) for(int i = x; i <= y; ++i)
#define per(i, x, y) for(int i = x; i >= y; --i)
#define repg(i, u) for(int i = head[u]; i; i = e[i].nxt)
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 300010, M = 610;
struct edge{ int v, nxt; }e[N << 1];
int head[N], cnt, n, m, k, p, t, x, y, z, l, r, tot, maxx, c[N], dep[N], L[N], R[N], rev[N << 1], f[N][20], ans[N], pl[N], pr[N], pos[N], num[N], st[M][M], len[M]; bool vis[N];
struct ask{
	int idx, x, y, l, r, z;
	ask(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0, int f = 0){
		idx = a; x = b; y = c; l = d; r = e; z = f;
	}
	bool operator < (const ask&rhs)const{
		return (x - 1) / t + 1 ^ (rhs.x - 1) / t + 1 ? x < rhs.x : (x - 1) / t + 1 & 1 ? y < rhs.y : y > rhs.y;
	}
}q[N];
inline void change(int x){
	x = c[rev[x]]; num[x] ^= 1;
	if(num[x]){
		int y = pos[x];
		if(!vis[x]) st[y][++len[y]] = x, vis[x] = 1;
	}
}
inline void add(int u, int v){ e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt; }
inline void dfs(int u, int fa){
	dep[u] = dep[fa] + 1; f[u][0] = fa; L[u] = ++tot; rev[tot] = u;
	rep(i, 1, 18) f[u][i] = f[f[u][i - 1]][i - 1];
	repg(i, u) if(e[i].v != fa) dfs(e[i].v, u);
	R[u] = ++tot; rev[tot] = u;
}
inline int lca(int x, int y){
	if(dep[x] < dep[y]) swap(x, y); per(i, 18, 0) if(dep[f[x][i]] >= dep[y]) x = f[x][i];
	if(x == y) return x; per(i, 18, 0) if(f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}
inline void mian(){
	n = read(); m = read(); rep(i, 1, n) c[i] = read(), maxx = max(maxx, c[i]);
	k = sqrt(maxx); p = (maxx - 1) / k + 1; rep(i, 1, maxx) pos[i] = (i - 1) / k + 1;
	rep(i, 1, p) pl[i] = (i - 1) * k + 1, pr[i] = min(maxx, i * k);
	rep(i, 1, n - 1) x = read(), y = read(), add(x, y), add(y, x); dfs(1, 0);
	rep(i, 1, m){
		x = read(); y = read(); l = read(); r = read(); r = min(r, maxx);
		if(L[x] > L[y]) swap(x, y); z = lca(x, y);
		if(R[y] <= R[x]) q[i] = ask(i, L[x], L[y], l, r, 0);
		else q[i] = ask(i, R[x], L[y], l, r, z);
	}
	t = sqrt(tot); sort(q + 1, q + m + 1); int ql = 1, qr = 0;
	rep(i, 1, m){
		int idx = q[i].idx; x = q[i].x; y = q[i].y; z = q[i].z; l = q[i].l; r = q[i].r;
		if(l > r){ ans[idx] = -1; continue; }
		while(qr < y) change(++qr); while(ql > x) change(--ql);
		while(qr > y) change(qr--); while(ql < x) change(ql++);
		if(z) change(L[z]); int bl = pos[l], br = pos[r];
		if(bl == br){
			rep(i, l, r) if(num[i]){
				ans[idx] = i; break;
			}
		}
		else{
			rep(i, l, pr[bl]) if(num[i]){
				ans[idx] = i; break;
			}
			if(!ans[idx])
			rep(i, pl[br], r) if(num[i]){
				ans[idx] = i; break;
			}
			if(!ans[idx])
			rep(i, bl + 1, br - 1){
				while(len[i] && !num[st[i][len[i]]]) vis[st[i][len[i]]] = 0, --len[i];
				if(len[i]){
					ans[idx] = st[i][len[i]]; break;
				}
			}
		}
		if(!ans[idx]) ans[idx] = -1; if(z) change(L[z]);
	}
	rep(i, 1, m) printf("%d\n", ans[i]);
}
int main(){ int qwq = 1; while(qwq--) mian(); return 0; }
```


---

