# [ABC364F] Range Connect MST

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc364/tasks/abc364_f

$ N\ +\ Q $ 頂点のグラフがあり、頂点には $ 1,\ 2,\ \ldots,\ N\ +\ Q $ の番号がついています。グラフにははじめ辺がありません。

このグラフに対して $ i\ =\ 1,\ 2,\ \ldots,\ Q $ の順に以下の操作を行います。

- $ L_i\ \leq\ j\ \leq\ R_i $ を満たす各整数 $ j $ について頂点 $ N\ +\ i $ と頂点 $ j $ の間にコスト $ C_i $ の無向辺を追加する
 
すべての操作を終えた後グラフは連結であるか判定し、連結である場合はこのグラフの最小全域木のコストを求めてください。

ただし、最小全域木とはコストが最小の全域木のことを指し、全域木のコストとは全域木に使われた辺のコストの和のことを指します。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ N $
- $ 1\ \leq\ C_i\ \leq\ 10^9 $
- 入力される値はすべて整数
 
### Sample Explanation 1

以下の辺からなる全域木が最小全域木のひとつとなります。 - 頂点 $ 1 $ と $ 5 $ を結ぶコスト $ 2 $ の辺 - 頂点 $ 2 $ と $ 5 $ を結ぶコスト $ 2 $ の辺 - 頂点 $ 1 $ と $ 6 $ を結ぶコスト $ 4 $ の辺 - 頂点 $ 3 $ と $ 6 $ を結ぶコスト $ 4 $ の辺 - 頂点 $ 3 $ と $ 7 $ を結ぶコスト $ 5 $ の辺 - 頂点 $ 4 $ と $ 7 $ を結ぶコスト $ 5 $ の辺 $ 2\ +\ 2\ +\ 4\ +\ 4\ +\ 5\ +\ 5\ =\ 22 $ であるため、$ 22 $ を出力します。

### Sample Explanation 2

グラフは非連結です。

## 样例 #1

### 输入

```
4 3
1 2 2
1 3 4
2 4 5```

### 输出

```
22```

## 样例 #2

### 输入

```
6 2
1 2 10
4 6 10```

### 输出

```
-1```

## 样例 #3

### 输入

```
200000 4
1 200000 1000000000
1 200000 998244353
1 200000 999999999
1 200000 999999999```

### 输出

```
199651870599998```

# 题解

## 作者：Milthm (赞：9)

不要什么题都用线段树啊喂！

______

我们遇到这种求 MST 的题目，首先考虑模拟 kruscal 算法求 MST 的过程，然后优化求解，所以我们有这样一个思路：

1. 将 $q$ 组边按照 $c_i$ 排序。

2. 按照顺序遍历 $q$ 组边，能连就连，累计答案。

3. 判断是否联通，输出答案。

看上去是对的，只是这会使你 TLE，所以考虑优化算法，看到这种连通性的判断，我们想到了并查集，于是有了新的算法思路：

1. 将 $q$ 组边按照 $c_i$ 排序。

2. 按照顺序遍历 $q$ 组边，枚举 $[l_i,r_i]$ 区间里所有未连边的点所在的集合，累计答案，并把它们合并到一个集合里。

3. 判断是否都在一个集合里，如果是输出答案，否则输出 $-1$。

因为每个集合连边一次就会被合并，所以总时间复杂度为 $O(n\log n)$，这里视 $n,q$ 同阶。


```cpp
#include<bits/stdc++.h>
#define ti tuple<int,int,int>
#define int long long
#define N 200005
using namespace std;
int n,q,f[N],l,r,c,ans;
ti a[N];
int Find(int x){
	return f[x]==x?x:f[x]=Find(f[x]);
}
signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;++i)f[i]=i;
	for(int i=1;i<=q;++i){
		cin>>l>>r>>c;a[i]=ti{c,l,r};
	}
	sort(a+1,a+q+1);
	for(int i=1;i<=q;++i){
		int w=get<0>(a[i]),l=get<1>(a[i]),r=get<2>(a[i]);
		ans+=w;
		while(Find(l)!=Find(r))ans+=w,f[Find(l)]=Find(l)+1;
	}
	if(Find(1)==Find(n))cout<<ans;
	else cout<<-1;
	return 0;
}

```

---

## 作者：Down_syndrome (赞：5)

**真的看不出哪里有错别字，微调了一些语言，望通过**
## 题意

给出一张有 $n+q$ 个点的无向加权图。一开始，图上没有边。接下来对于每个 $i\in[1,q]$ 给出 $l_i,r_i$ 和 $c_i$，表示对于所有 $j\in[l_i,r_i]$ 添加一条 $j$ 连向 $i+n$ 的边权为 $c_i$ 的边，最后求原图的最小生成树，或报告不连通。

## 思路
先考虑 Kruskal。把每一组边按照边权从小到大排序，然后按顺序加边。容易发现，在任意时刻，对于所有编号在 $n$ 内的点形成的联通块编号是连续的。而且当考虑到第 $i$ 组边时，所有有节点在 $[l_i,r_i]$ 内的联通块都会向 $i+n$ 连刚好一条边。所以我们只要统计 $[l_i,r_i]$ 内有多少个联通块就行了。对于区间问题，可以考虑线段树。考虑用线段树维护每个点目前所属联通块的编号，并记下每个连通块的左端点和右端点。然后每次遍历 $[l_i,r_i]$ 内的所有联通块，并把它们合并，区间修改它们的联通块编号和左右端点。假设区间内共有 $cnt$ 个联通块，那第 $i$ 组就会选 $cnt$ 条边，给答案加上 $cnt\times c_i$ 即可。

## code
赛时代码，很多地方写的很唐，仅供参考。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;
const int N=2e5+5;
int n,q,sum,ans,num;
struct edge{
	int l,r,c;
}d[N];
struct node{
	int l,r,bel,lp,rp,tag[3];
}t[N<<2];
bool cmp(edge x,edge y){
	return x.c<y.c;
}
void build(int k,int l,int r){
	t[k].l=l;
	t[k].r=r;
	if(l==r){
		t[k].bel=t[k].lp=t[k].rp=l;
		return;
	}
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void push_down(int k){
	if(t[k].tag[0]){
		t[ls].bel=t[ls].tag[0]=t[k].tag[0];
		t[rs].bel=t[rs].tag[0]=t[k].tag[0];
		t[k].tag[0]=0;
	}
	if(t[k].tag[1]){
		t[ls].lp=t[ls].tag[1]=t[k].tag[1];
		t[rs].lp=t[rs].tag[1]=t[k].tag[1];
		t[k].tag[1]=0;
	}
	if(t[k].tag[2]){
		t[ls].rp=t[ls].tag[2]=t[k].tag[2];
		t[rs].rp=t[rs].tag[2]=t[k].tag[2];
		t[k].tag[2]=0;
	}
}
void modify_bel(int k,int l,int r,int x){
	if(r<t[k].l||t[k].r<l) return;
	if(l<=t[k].l&&t[k].r<=r){
		t[k].bel=t[k].tag[0]=x;
		return;
	}
	push_down(k);
	modify_bel(ls,l,r,x);
	modify_bel(rs,l,r,x);
}
void modify_lp(int k,int l,int r,int x){
	if(r<t[k].l||t[k].r<l) return;
	if(l<=t[k].l&&t[k].r<=r){
		t[k].lp=t[k].tag[1]=x;
		return;
	}
	push_down(k);
	modify_lp(ls,l,r,x);
	modify_lp(rs,l,r,x);
}
void modify_rp(int k,int l,int r,int x){
	if(r<t[k].l||t[k].r<l) return;
	if(l<=t[k].l&&t[k].r<=r){
		t[k].rp=t[k].tag[2]=x;
		return;
	}
	push_down(k);
	modify_rp(ls,l,r,x);
	modify_rp(rs,l,r,x);
}
int query_bel(int k,int x){
	if(x<t[k].l||t[k].r<x) return 0;
	if(t[k].l==t[k].r) return t[k].bel;
	push_down(k);
	return query_bel(ls,x)+query_bel(rs,x);
}
int query_lp(int k,int x){
	if(x<t[k].l||t[k].r<x) return 0;
	if(t[k].l==t[k].r) return t[k].lp;
	push_down(k);
	return query_lp(ls,x)+query_lp(rs,x);
}
int query_rp(int k,int x){
	if(x<t[k].l||t[k].r<x) return 0;
	if(t[k].l==t[k].r) return t[k].rp;
	push_down(k);
	return query_rp(ls,x)+query_rp(rs,x);
}
signed main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=q;i++) scanf("%lld%lld%lld",&d[i].l,&d[i].r,&d[i].c);
	sort(d+1,d+q+1,cmp);
	build(1,1,n);
	for(int i=1;i<=q;i++){
		sum=0;
		int L=query_lp(1,d[i].l),R,id=query_bel(1,i);
		for(int j=L;j<=d[i].r;j=R+1){
			sum++;
			R=query_rp(1,j);
		}
		modify_bel(1,L,R,id);
		modify_lp(1,L,R,L);
		modify_rp(1,L,R,R);
		ans+=sum*d[i].c;
		num+=sum;
	}
	if(num!=n+q-1) printf("-1");
	else printf("%lld",ans);
	return 0;
}
```

---

## 作者：DengStar (赞：3)

[在博客园中查看](https://www.cnblogs.com/dengstar/p/18329016) | [题目链接](https://atcoder.jp/contests/abc364/tasks/abc364_f)

看到要求最小生成树，首先想到 Kruskal。先回忆一下 Kruskal 的流程：

1. 将所有边按边权从小到大排序。
2. 依次遍历所有边。对于每条边，如果它连接的两点不在同一连通块中，则把这条边加入 MST。

对于本题来说，难点在于第二步：边数最多可以达到 $NQ$，不可能真的遍历每条边。然而，我们真的必须遍历每条边吗？

首先，编号大于 $N$ 的节点是不重要的，下面我们只关心编号小于 $N$ 的节点。注意到题目中加边的形式：每次加边都会将 $[L_i, R_i]$ 中的点练成一个连通块。也就是说，如果任意的两点 $A$，$B$ 联通，那么所有满足 $A \le x \le B$ 的点 $x$ 都和 $A$，$B$ 在同一连通块中。

以样例 1 为例，用不同颜色代表不同连通块：

初始时，所有节点互不连通。
$$
{\Huge{\color{red}\Box}{\color{green}{\Box}}{\color{blue}\Box}{\color{brown}{\Box}}}
$$
第一次操作，把 $1$，$2$ 号节点连通：
$$
{\Huge[{\color{green}{\Box\Box}}]{\color{blue}\Box}{\color{brown}{\Box}}}
$$
第二次操作，把 $1$，$2$，$3$ 号节点**所在的连通块**连通：
$$
{\Huge[{\color{blue}{\Box\Box\Box}}]{\color{brown}{\Box}}}
$$
第三次操作，把 $2$，$3$，$4$ 号节点所在的连通块连通：
$$
{\Huge{\color{brown}\Box}[{\color{brown}\Box\Box\Box}]}
$$
于是可以想到，把边权排序后，对于每次加边操作，从 $L_i$ 开始，不断跳到当前点所在连通块最右边的（即编号最大）节点（不妨称这个节点的编号为 $x$），然后在 $x$ 和 $x+1$ 之间连边，直到跳出加边的区间。每次加边的时候，统计一下答案即可。（可以根据上面的图示理解。）以及，别忘了每次操作时，我们还要从编号大于 $N$ 的节点向编号小于 $N$ 的节点连一条边（否则不连通），统计答案时记得加上。

连通性显然可以用并查集维护。为了方便快速找到当前连通块最右边的节点，可以直接用最右边的节点作为这个连通块的代表元，这需要在 `merge` 的时候注意一下参数的顺序（详见代码）。

[参考代码]()

PS：[ABC352E](https://atcoder.jp/contests/abc352/tasks/abc352_e) 也是一道相似的用 Kruskal 求最小生成树的题，可以去尝试一下。

---

## 作者：luanyanjia (赞：2)

区间连边先想到线段树优化建图，但显然的是这样建图求 MST 根本没法做。需要另想他法。

前两天刚做了[弹跳](https://www.luogu.com.cn/problem/P5471)，此题并没有直接建图，而是**模拟**了 Dijkstra 来跑最短路。同理，此题我们也可以不直接建图，而是通过模拟 Kruskal 来求 MST。

将边按照权值从小到大排序，注意到连完边后 $[l,r]$ 的每一个点都会进入到同一个连通块中，用 set 维护连通块（也就是珂朵莉树），这样连边就转化为了合并和 $[l,r]$ 有交的每一个连通块，假如第 $i$ 次将 $k$ 个连通块合并，那代价就是 $c_i \times k$。

原来 $n$ 个点分属于 $n$ 个连通块，最多合并 $n-1$ 次，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define mkp make_pair
using namespace std;
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
	char ch=getchar();
	T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x*=f;rd(args...);
}
const int N=2e5+5;
int n,m;
struct node{int l,r;long long c;}q[N];
set<pii> s;
long long ans;
signed main(){
	rd(n,m);
	for(int i=1;i<=n;i++)s.insert({i,i});
	for(int i=1;i<=m;i++)
		rd(q[i].l,q[i].r,q[i].c);
	sort(q+1,q+m+1,[](node a,node b){return a.c<b.c;});
	for(int i=1;i<=m;i++){
		auto st=--s.upper_bound({q[i].l,n}),ed=s.upper_bound({q[i].r,n});
		for(auto it=st;it!=ed;it++)ans+=q[i].c;
		pii nw=mkp(st->first,prev(ed)->second);
		s.erase(st,ed);
		s.insert(nw);
	}
	if(s.size()>1)printf("-1\n");
	else printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Hadtsti (赞：2)

### 题意简述

$n+q$ 个节点，给出 $q$ 个条件表示编号为 $n+1,n+2,\cdots,n+q$ 的节点分别向编号在 $1\sim n$ 中的一段区间内的节点连有一条无向有权边，求这个图的最小生成树。

$1\le n,q\le 2\times 10^5$。

### 题目分析

裸的解题方式就是暴力连边建图跑 Kruskal，复杂度 $O(nq\log (nq))$，显然会 T。

考虑优化此过程。我们分析 Kruskal 在此题的图中到底干了什么。由于每个条件中连的边边权相等，在 Kruskal 过程中也是连续处理的，故我们将条件按边权排序再按顺序处理。Kruskal 过程用并查集维护，判断一条边的两个节点原本是否连通，对于本题就是对每个条件数一下区间中的点原先来自于多少个不同的连通块，把这个个数乘上边权加到答案里就好了。

为了维护这一过程，我们可以使用颜色段均摊的思想。对每个条件将区间内原有的小区间扫一遍统计答案，再把它们合并即可。实现细节看代码。

分析一下复杂度。每个条件至多增加 $2$ 个小区间，再加上 set 的 $\log$，若视 $n,q$ 同级，则总复杂度为 $O(q\log q)$。

### 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,fa[200010];
long long ans;
struct ED
{
	int x,l,r;
	friend bool operator <(ED a,ED b)
	{
		return a.x<b.x;
	}
}a[200010];
struct node
{
	int l,r,v;
	friend bool operator <(node a,node b)
	{
		return a.l<b.l;
	}
};
set<node>S;
auto split(int x)
{
	if(x>n)
		return S.end();
	auto it=--S.upper_bound(node{x,0,0});
	int l=it->l,r=it->r,v=it->v;
	if(l==x)
		return it;
	S.erase(it);
	S.insert(node{l,x-1,v});
	return S.insert(node{x,r,v}).first;
}
void assign(int l,int r,int v)
{
	auto rit=split(r+1),lit=split(l);
	S.erase(lit,rit);
	S.insert(node{l,r,v});
}
int getf(int x)
{
	return x==fa[x]?x:fa[x]=getf(fa[x]);
}
int main()
{
	scanf("%d%d",&n,&q);
	S.insert({1,n,0});
	for(int i=1;i<=q;i++)
	{
		fa[i]=i;
		scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].x);
		assign(a[i].l,a[i].r,a[i].x);
	}
	for(auto i:S)
		if(!i.v)
		{
			printf("-1");
			return 0;
		}
	S.clear();
	S.insert({1,n,0});
	sort(a+1,a+q+1);
	for(int i=1;i<=q;i++)
	{
		auto rit=split(a[i].r+1),lit=split(a[i].l);
		for(auto j=lit;j!=rit;j++)
		{
			if(j->v)
			{
				if(getf(i)!=getf(j->v))
				{
					ans+=a[i].x;
					fa[getf(j->v)]=getf(i);
				}
			}
			else
				ans+=1ll*(j->r-j->l+1)*a[i].x;
		}
		assign(a[i].l,a[i].r,i);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：fzark (赞：1)

看了一圈题解都是并查集、颜色段合并，还有线段树的做法，这里介绍一个优先队列和集合差分的做法，并且这里推导出的结论可以省去并查集（因为是第一次自己想出集合差分的做法，所以会讲的非常详细！）。

## 题意
[原题链接](https://www.luogu.com.cn/problem/AT_abc364_f)。

给定一个 $n + q$ 个顶点的图，初始时每个顶点都没有边，现在给定 $q$ 个操作，每个操作 $q_j$ 包含 $L,R$，含义为：对于每个 $L \le i \le R$ 的节点，连接 $i$ 和 $n+j$。求完成所以操作后的最小生成树。

## 思路
首先观察操作，可以发现操作的节点是一段区间。所以可以理解为对 $[l,r]$ 区间进行添加一个数。如果我们暴力在线添加，显然会超时。这里考虑**集合差分**，即对于一次操作，我们维护一个差分集合，每个集合存储操作的 $id$。然后最后再用一个前缀集合跑一次前缀即可（对于正确性，下面有证明）。

考虑到某个区间会有多个叠加的边权，如何才能选出最小边权呢？很明显，我们可以用一个优先队列维护前缀集合即可。并且为了保证时间复杂度，对于我们采取**懒更新**，即对于当前点，当前缀集合跑完之后我们再进行更新。

现在考虑单个点 $x$ 的策略（稍后给出这些策略的证明），设想一下有很多点连接了 $x$，那么对于这些点，必然有如下分类：

- 这些点是之前没有遇到过的。
- 这些点是之前遇到过的。

对于情况 $1$，我们采取的策略是：直接将这些点的边最小生成树中。

对于情况 $2$，我们采取的策略是：选取一条代价最小的边进行连接（用我们维护的优先队列去取）。

当跑完差分的时候，判断加的边是否小于 $n+q-1$，如果不是，则不能构成最小生成树，显然无解。否则我们输出总代价即可。现在给出证明。

## 证明

- 这里集合差分的正确性怎么保证呢？

可以观察到很重要的一点，即：对于每一个操作，都具有**唯一性**，所以我们可以利用这个唯一性，结合异或运算的性质（当出现偶数次的时候，进行抵消）。所以这里的集合差分的逆运算为：**当再次遇到一个相同 $id$ 的时候，则视为一段区间结束**，满足可差分性，得证。

- 这两个策略的正确性怎么证明呢？

首先对于策略 $1$。考虑任何一个点（这里钦定的点都属于点集 $q$），它并入连通块的代价明显是它的边权。一个很显然的结论是：它一定是在某一时刻，用它的出边中**至少一条边**进行连接连通块。在策略 $1$，中。我们对于这些点，选择在第一次遇见的时刻就将**这条边**并入生成树中，并且保证后续不会对**这条边**进行重复计算。情况 $1$ 的策略得证。

最后对于策略 $2$。考虑属于点集 $n$ 中的点，这些点的特征是：只会被属于点集 $q$ 的点进行连边。考虑这些点中的任意一点 $x$。当 $x$ 进行了策略 $1$ 的操作后，形成了一个连通块。但是，对于那些之前已经出现过的连接它的边，很明显它需要选择一条最小代价的边，将当前所属连通块并入到之前的连通块。然后将这一情况可以推广到通用情况，得证。

*证毕。*

## 代码

```python
import heapq

def solve():
    n, q = map(int, input().split())
    # 重点：维护一个集合差分
    diff = [set() for i in range(n + 2)]
    hs = [0] * (q + 1)
    g = []
    for i in range(q):
        l, r, c = map(int, input().split())
        g.append([l, r, c, i])
        hs[i] = c
        # 因为id是唯一的，其逆运算类似于异或的性质。因为该逆运算满足可差分性，所以可以差分
        diff[l].add(i)
        diff[r + 1].add(i)
    # cnt 是连边计数
    ans = cnt = 0
    h = []
    # 前缀集合
    pre = set()
    vis = set()
    for i in range(len(diff)):
        # 对于某个点，还需要维护一个懒加入的集合，用来找没加入新点之前的最优边权
        lazy = set()
        for j in diff[i]:
            # 集合差分逆运算
            if j in pre:
                pre.remove(j)
            else:
                pre.add(j)
                if j not in vis:
                    lazy.add(j)
        # 懒删除：当堆顶的元素不在前缀集合中，很明显需要丢弃
        while h and h[0][1] not in pre: heapq.heappop(h)
        last_batter = -1
        # 找出没加入之前的最小代价边
        if h :last_batter = h[0][1]
        # 懒加入
        while lazy:
            cur = lazy.pop()
            heapq.heappush(h,[hs[cur],cur])
            vis.add(cur)
            ans += hs[cur]
            cnt += 1
        if h and last_batter != -1:
            # 需要连一条边到之前的连通块
            ans += hs[last_batter]
            cnt += 1
    if cnt < n + q - 1:return -1
    return ans

print(solve())
```
## 时间复杂度

$O(n \log n)$。

---

## 作者：Cosine_Func (赞：1)

比较板子的 MST 经典题。

考虑贪心，以 $c$ 为关键字对各操作排序，然后枚举区间内所有未连边的点所属的集合，计入答案并合并。时间复杂度 $O(Q\times\log Q +N)$。

[参考代码](https://atcoder.jp/contests/abc364/submissions/59784312)

---

## 作者：AK_400 (赞：1)

考虑模拟 Kruskal 的过程。

首先按边权排序，然后把不连通的连上。

观察一下，发现就是把这个区间内每个连通块中选一个点连向新加入的点，然后把这个区间合并成一个连通块。

用 set 模拟这个过程即可。（具体细节见代码）


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,q;
int l[200005],r[200005],c[200005],id[200005];
int ans=0;
bool cmp(int x,int y){
    return c[x]<c[y];
}
struct seg{
    int l, r;
};
bool operator<(seg x,seg y){
    return x.l<y.l;
}
set<seg>s;
void slv(int l,int r,int c){
    auto it=s.lower_bound({l,r});
    if(it==s.end()||it->l>l)it--;
    int l1=it->l;
    auto itl=it,itr=itl;
    while(it!=s.end()&&it->l<=r){
        ans+=c;
        itr=it;
        it++;
    }
    int r1=itr->r;
    itr++;
    s.erase(itl,itr);
    s.insert({l1,r1});

}
void slv(){
    cin>>n>>q;
    for(int i=1;i<=q;i++)cin>>l[i]>>r[i]>>c[i],id[i]=i;
    sort(id+1,id+1+q,cmp);
    for(int i=1;i<=n;i++)s.insert({i,i});
    for(int i=1;i<=q;i++){
        slv(l[id[i]],r[id[i]],c[id[i]]);
    }
    if(s.size()==1)
    cout<<ans<<endl;
    else cout<<-1<<endl;
}
signed main(){
    slv();
    return 0;
}
```

---

## 作者：2022liaojianxiang (赞：1)

图中的操作是对多个区间连边到一个全新的点，而这些全新的点都是不同的。那么我们挖掘一下性质，可以发现如果对于两个区间的重复部分，都会连向两个不同的点。那么这就会使得两个不同的点可能重复连边，我们思考如何优化这个过程。

我们可以先对所连区间的权值排序作克鲁斯卡尔算法。我们发现对于区间的重复部分，我们只需要在前面的区间上找出任意一个点连向新的那个不同的点即可，这样我们就既可以保证时间复杂度（连边的数量不超过 $n+q$ 条），也可以满足最小生成树的性质。

那么我们就对于每个区间当作一团（也可以等同于记录在并查集中），记录一下这个团中的最后一个位置，然后每次取出当前团的最后一个位置进行连边并更新即可。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const long long N=2000009;
long long fa[N],n,q,ans=0;
struct node{long long l,r,c;}a[N];
bool cmp(node x,node y){return x.c<y.c;}
long long getfa(long long x)
{
	if(fa[x]==x) return fa[x];
	return fa[x]=getfa(fa[x]);
}
int main()
{
	scanf("%lld%lld",&n,&q);
	for(long long i=1;i<=q;i++)
		scanf("%lld%lld%lld",&a[i].l,&a[i].r,&a[i].c);
	sort(a+1,a+q+1,cmp);
	for(long long i=1;i<=q+n;i++) fa[i]=i;
	for(long long i=1;i<=q;i++)
		for(long long j=a[i].l+q;j<=a[i].r+q;j=getfa(j)+1)
			fa[getfa(i)]=getfa(j),ans=ans+a[i].c;
	for(long long i=q+1;i<=q+n;i++)
		if(getfa(i)!=q+n)
			return !printf("-1");
	printf("%lld",ans);
	return 0;
}

```

---

## 作者：__O_v_O__ (赞：1)

根据克鲁斯卡尔算法的思想，我们先把所有的 $c$ 从小到大排序，再依次处理每一次加边。

因为 $c$ 是从小到大的，所以每一次加边一定是能加就加。也就是说，从小到大枚举 $c$ 时，如果当前一条边两个端点不在一个连通块里，这条边一定在最小生成树里。

下面，难点来到了加边。如果我们对于 $l$ 到 $r$ 中的每个点都判断一次，一定会超时。我们需要优化。

考虑一个性质：如果一个点在之前被某个点连过，且存在一个点，满足它和这个点和当前点都连了边，则这个点在之后一定不会被连边。

所以，我们维护一个并查集，如果当前点被连了边，则把它的父亲设为下一个点。当对于区间 $[l,r]$ 加点时，从 $l$ 到 $r$ 枚举每个点，如果没被加过边则加边，再跳到当前点 `find` 的结果。

为什么这样复杂度正确？因为每个点最多会被加两次，后面就直接跳过了，复杂度是总点数。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct A{int l,r,c;}qr[200001];
int n,q,fa[200005],an;
int fi(int x){return fa[x]==x?x:fa[x]=fi(fa[x]);}
signed main(){
	ios::sync_with_stdio(0),cin>>n>>q;
	for(int i=1;i<=n+1;i++)fa[i]=i;
	for(int i=1;i<=q;i++)
		cin>>qr[i].l>>qr[i].r>>qr[i].c;
	sort(qr+1,qr+q+1,[](A x,A y){return x.c<y.c;});
	for(int i=1;i<=q;i++){
		for(int j=qr[i].l;j<=qr[i].r;++j){
			an+=qr[i].c,j=fi(j);
			if(j+1<=qr[i].r)fa[j]=j+1;
		}
	}for(int i=1;i<=n;i++)
		if(fi(i)!=n){cout<<-1;return 0;}
	cout<<an;
	return 0;
}
```

---

## 作者：liruixiong0101 (赞：0)

# at_abc364_f Range Connect MST
题目链接：<https://atcoder.jp/contests/abc364/tasks/abc364_f>

## 题意：
有一个 $N+Q$ 个点的无向图，其中的点 $N+i$ 会与 $j$ 连边，其中 $l_i\le j\le r_i$ 且 $j$ 为整数。求这个无向图的最小生成树。（$N,Q\le 2\times 10^5$）

## 思路：
考虑 kruskal 是如何求最小生成树，首先将边按照边权从小到大排序，然后遍历每一条边，若该边的两个端点不在一个连通块中就在最小生成树中加上这条边。考虑本题，本题应该先遍历 $Q$ 点集的点，然后遍历 $[l_i,r_i]$，然后判断该不该加这条边，显然这样做会超时。我们可以发现任意两个区间最多相交一格，考虑建立 $N$ 点集的并查集，每次遍历区间的时候可以将 `j++` 替换为 `j = find(j)`，在循环内加上 `merge(j,j+1)`，这样就可以跳过一部分，时间复杂度为 $O(N+Q)$。（但是要注意一些细节，比如：$j$ 和 $j+1$ 合并时要判断 $j+1$ 是否小于等于 $n$）

## 代码：
<https://atcoder.jp/contests/abc364/submissions/56435514>

---

## 作者：2020kanade (赞：0)

由于 $Q$ 个额外点的存在，每个区间都需要至少选出一个点满足这个点已经在其他区间被选中。按这个思路手玩一下，发现这东西其实就是颜色段合并。因此，当且仅当所有给出的区间不能合并为一个颜色段时，本题无解。

考虑加入一个新的颜色段，如果它和其他的颜色段有重叠，在图的连通性意义上，重叠部分只需要由这个区间的额外点向这个部分的任意一点连边即可保证此时当前颜色段的连通性的合并。

因此，我们可以贪心地将所有区间按照代价从小到大排序并加入，每加入一个区间时，将其作为一个颜色段，合并所有与其相交的颜色段，其代价分为两部分：若一个点不属于任意颜色段，对应直接连接区间额外点和这个点之间的边，这样的点必须全部都连上；否则，对于已经存在的一个颜色段，选择其中任意一点进行连边即可。

使用 ```std::set``` 维护颜色段与其合并即可，具体实现见代码。


```cpp
//written by Amekawa_kanade
#include<bits/stdc++.h>
using namespace std;
void syncoff()//fuck you sync
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
#define endl '\n'
const int N=5e5+11;
using ll=long long;
using i128=__int128;
using ld=long double;
const ll JT=998244353;
const ll GEH=1e9+7;
const ll ZLH=1e9+9;
int t,n,k,m,q;
struct stt
{
	int lp,rp;ll cost;
	bool operator <(const stt& a) const
	{
		return cost<a.cost;
	} 
};
struct node
{
	ll l,r;
	node(ll l,ll r):l(l),r(r) {}
	bool operator <(const node& a) const
	{
		return l<a.l;
	} 
};
set<node> qaq;
using sit=set<node>::iterator;
ll assign(ll l,ll r,ll cost)
{
	ll cnt=cost*(r-l+1);
	ll pl=l,pr=r;
    sit lit=qaq.lower_bound(node(l,0)),lit2=lit,lp=qaq.end();
    if(lit!=qaq.begin()) --lit2;
    if(lit2!=lit&&(l<=(*lit2).r)) lp=lit2;
    else if(lit!=qaq.end()&&(*lit).l<=r) lp=lit;
    sit rit=qaq.upper_bound(node(r,0)),rp=qaq.end();
    if(rit!=qaq.begin()) --rit;
    if(rit!=qaq.end()&&(*rit).r>=l) rp=rit;
    sit rlim=rp;if(rlim!=qaq.end()) ++rlim;
    if(lp==qaq.end())
    {
    	qaq.insert(node(pl,pr));
	}
	else
	{
		for(auto it=lp;it!=rlim;++it)
	    {
	        cnt-=(min(1ll*r,(*it).r)-max(1ll*l,(*it).l)+1ll)*cost;
	        cnt+=cost;
	        pl=min(pl,(*it).l),pr=max(pr,(*it).r);
	    }
	    qaq.erase(lp,rlim);
	    qaq.insert(node(pl,pr));
	}
	return cnt;
}
stt atk[N];
void solve()
{
	cin>>n>>m;
	for(int i=1;i<=m;++i) cin>>atk[i].lp>>atk[i].rp>>atk[i].cost;
	sort(atk+1,atk+m+1);ll ans=0;
	for(int i=1;i<=m;++i) ans+=assign(atk[i].lp,atk[i].rp,atk[i].cost);
	if(qaq.size()>1) ans=-1;
	if((*qaq.begin()).r-(*qaq.begin()).l+1<n) ans=-1;
	cout<<ans<<endl;
}
int main()
{
 	t=1;
    //cin>>t;
    while(t--) solve();
    return 0;
}

```

时间复杂度 $\Theta(Q\log Q)$。

---

## 作者：IronMen (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc364_f)

[AtCoder链接](https://atcoder.jp/contests/abc364/tasks/abc364_f)

---
## 题目
有一个图，它有 $N+Q$ 个顶点，编号为 $1,2, \ldots ,N+Q$。最初，该图没有边。

对于这个图，请依次对 $i=1,2, \ldots ,Q$ 执行以下操作：
- 对于每个满足 $L_i \le j \le R_i$ 的整数 $j$，在顶点 $N+i$ 和 $j$ 之间添加一条代价为 $C_i$ 的无向边。

完成所有操作后，确定图形是否相连。如果相连，求该图的最小生成树的代价。

最小生成树是成本尽可能小的生成树，生成树的成本是生成树所用边的成本之和。

---
## 思路
考虑是否构成连通块，即这 $q$ 个线段是否构成一个大线段。再考虑最小生成树怎么求，即考虑前 $n$ 个点该和哪个操作点 $(n+i)$ 连边。

我们从代价小的操作开始，给 $L_i \le j \le R_i$ 中的每个点合并成一个连通块，每合并一次的代价是 $C_i$。最后看是否是同一个连通块即可。

连通块利用并查集维护，合并时总是以编号大的点为根，这样在上述从左到右合并时每次都从还未连通的点开始遍历即可。

---
### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5, mod = 1e9 + 7;
int fa[200010], rmax[200010], n, q, now, nxt;
long long ans;

struct node
{
	int l, r, c;
} a[200010];

bool cmp(node p, node q)
{
	return p.c < q.c;
}

int find(int x)
{
	if (fa[x] == x)
		return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	int fx = find(x), fy = find(y);
	if (fx != fy)
	{
		fa[fx] = fy;
		rmax[fy] = max(rmax[fx], rmax[fy]);
	}
}

int main()
{
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i ++ )
		fa[i] = rmax[i] = i;
	for (int i = 1; i <= q; i ++ )
		scanf("%d %d %d", &a[i].l, &a[i].r, &a[i].c);
	sort(a + 1, a + 1 + q, cmp);
	for (int i = 1; i <= q; i ++ )
	{
		now = a[i].l;
		while (1)
		{
			ans += 1ll * a[i].c;
			nxt = rmax[find(now)] + 1;
			if (nxt > a[i].r)
				break;
			else
			{
				merge(now, nxt);
				now = nxt;
			}
		}
	}
	if (rmax[find(1)] != n)
		puts("-1");
	else
		cout << ans << '\n';
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

## [ABC364F] Range Connect MST

仿照 Kruskal 重构树的加边方式，同样按权值排序加边。

同时使用并查集维护某个点最靠右的、和自己联通的点 $nxt_i$，每次加边的区间，根据最小生成树的定义可知，最有方案是使得整个区间联通，即 $nxt_l \ge r$。

注意即使不加边，第 $N+i$ 个点也要花费 $C_i$ 的代价与前 $N$ 个点联通。

细节看代码：

```cpp
n = read(), q = read();
for (int i = 1; i <= n; i++) fa[i] = i;
for (int i = 1; i <= q; i++)
  a[i].l = read(), a[i].r = read(), a[i].c = read();
sort(a + 1, a + 1 + q, [](Edge x, Edge y) { return x.c < y.c; });
for (int i = 1; i <= q; i++) {
  res += a[i].c;
  while (Get(a[i].l) < a[i].r) {
    res += a[i].c;
    Merge(a[i].l, Get(a[i].l) + 1);
    a[i].l = fa[a[i].l];
  }
}
printf("%lld", Get(1) == n ? res : -1);
```

---

## 作者：Merge_all (赞：0)

### 思路：
- 首先先写一遍 kruscal 算法求 MST。
1. 按照 $c_i$ 从小到大排序。
2. 若不在第 $i$ 个点不在最小生成树中，则联通。

**但是这样做会 TLE**。
- 考虑优化。
- 找到 $[L_i,R_i]$ 中的每个点，判断是否不在同一个集合内，若不在就放入新的集合中。顺便统计答案。
- 最后判断是否所有元素的祖宗节点是 $n$，不是就是 -1。
### code：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Max=2e5+10;
int n,q;
struct node {
	int l;
	int r;
	int c;
} a[Max];
bool cmp(node a,node b){
	return a.c<b.c;
}
bool vis[Max];
int fa[Max];
int get_fa(int x){
	if(x==fa[x]){
		return x;
	}
	return fa[x]=get_fa(fa[x]);
}
int res;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>n>>q;
	for(int i=1;i<=q;i++){
		cin>>a[i].l>>a[i].r>>a[i].c;
	}
	sort(a+1,a+q+1,cmp);
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=1;i<=q;i++){
		int cnt=1;
		for(int j=a[i].l;j<=a[i].r;){
			int r=get_fa(j);
			if(r>=a[i].r){
				break;
			}
			fa[r]=get_fa(r+1);
			cnt++;
			j=r+1;
		}
		res+=cnt*a[i].c;
	}
	for(int i=1;i<=n;i++){
		if(get_fa(i)!=n){
			cout<<-1;
			return 0;
		}
	}
	cout<<res;
	return 0;
}
```

---

