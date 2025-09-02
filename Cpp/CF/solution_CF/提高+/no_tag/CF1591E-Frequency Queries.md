# Frequency Queries

## 题目描述

Petya has a rooted tree with an integer written on each vertex. The vertex $ 1 $ is the root. You are to answer some questions about the tree.

A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. The parent of a node $ v $ is the next vertex on the shortest path from $ v $ to the root.

Each question is defined by three integers $ v $ , $ l $ , and $ k $ . To get the answer to the question, you need to perform the following steps:

- First, write down the sequence of all integers written on the shortest path from the vertex $ v $ to the root (including those written in the $ v $ and the root).
- Count the number of times each integer occurs. Remove all integers with less than $ l $ occurrences.
- Replace the sequence, removing all duplicates and ordering the elements by the number of occurrences in the original list in increasing order. In case of a tie, you can choose the order of these elements arbitrary.
- The answer to the question is the $ k $ -th number in the remaining sequence. Note that the answer is not always uniquely determined, because there could be several orderings. Also, it is possible that the length of the sequence on this step is less than $ k $ , in this case the answer is $ -1 $ .

For example, if the sequence of integers on the path from $ v $ to the root is $ [2, 2, 1, 7, 1, 1, 4, 4, 4, 4] $ , $ l = 2 $ and $ k = 2 $ , then the answer is $ 1 $ .

Please answer all questions about the tree.

## 样例 #1

### 输入

```
2
3 3
1 1 1
1 2
3 1 1
3 1 2
3 2 1
5 5
1 2 1 1 2
1 1 2 2
3 1 1
2 1 2
4 1 1
4 2 1
4 2 2```

### 输出

```
1 -1 1 
1 1 2 1 -1```

# 题解

## 作者：Tyyyyyy (赞：5)

# CF1591E

### 题意简述
有一棵 $n$ 个点的有根树，每个点有一个权值 $a_i$，且给出每个点的父节点 $p_i$。

有 $q$ 个询问如 `v l k` 所示。你需要进行如下操作来得到询问的答案：

1. 写下根节点到点 $v$ 路径上的所有点权（包括根节点和 $v$ 点）。
1. 去掉其中出现次数小于 $l$ 的数。
1. 按出现次数将剩下的数升序排序。
1. 答案为去重后的第 $k$ 个数。如果不足 $k$ 个数，答案为 `-1`。

如果有出现次数相同的数，你可以将它们按任意顺序排序。

本题有多组数据，在输入的第一行以 $t$ 给出。

数据范围：$1 \leq t,n,q,\sum n,\sum q \leq 10^6,1 \leq a_i,p_i,v,l,k \leq n$。

### 题目分析
在线明显不可做。考虑将询问离线，以一次从根节点出发的 dfs 依次处理。在以上做法的基础上给出三种算法供参考：

#### 算法 1：平衡树套平衡树
考虑用平衡树维护路径上出现过的点权。该平衡树需要以出现次数作为关键码维持形态。我们考虑增加一个域 $val$ 维护出现了该次数的数。因为 $val$ 域需要支持动态的插入和删除，可以使用 STL 库中的 $\operatorname{multiset}$ 来实现。

记数 $i$ 出现的次数为 $cnt_i$，每当我们访问到一个节点，该节点权值的出现次数自增 $1$，我们就把该节点的权值插入到 $cnt_{a_i}$ 这个节点中，同时把 $cnt_{a_i-1}$ 这个节点中的 $a_i$ 删除。返回时同理。

该平衡树还需要维护一个域表示子树内的**本质不同元素数量**，记为 $size_i$。当我们处理一个查询时，我们先以 $size$ 为标准找到**比 $l$ 小的本质不同元素个数** $rank$。于是需要查询的真正排名就是 $k+rank$，在平衡树上查询即可。

该算法的理论时间复杂度为 $O(n\operatorname{log}^2 n)$。考虑到实现难度和常数大小，不建议使用该算法。

#### 算法 2：权值线段树配合平衡树
观察到 $1 \leq a_i \leq n$。类似于刚才的思路，我们在出现次数的值域上建立权值线段树，配合桶来记录元素出现的次数，可以做到查询出现次数比 $l$ 少的数的个数，和查询排名为 $x$ 的数。

因为还需要输出排名为 $k$ 的具体的元素，我们配合一个 $\operatorname{set}$ 即可。

该算法的时间复杂度为 $O(n\operatorname{log}n)$，在实际测试中需要 $\text{3.2s}$ 通过本题。

该算法的参考实现附在文末。

#### 算法 3：线性递推（官方题解做法）
考虑维护以下几个信息：
1. 元素 $i$ 出现的次数 $cnt_i$。
1. 以 $cnt_i$ 排序的排列 $p$，原本为 $1,2,\dots,n$。注意，排列中的数是元素本身，但将它们按出现次数排序。
1. 排列 $p$ 的逆排列 $p^{-1}$。
1. 对于每个 $x\in\{1,\dots,n\}$，满足 $cnt_{p_i}>x$ 的最小的 $i$。记作 $lb_i$。

当我们将 $cnt_x$ 自增 $1$ 时：
1. 把 $x$ 挪到出现次数为原来的 $cnt_x$ 的块的末尾。即交换 $p_{p_i^{-1}}$ 和 $p_{lb_{cnt_x+1}-1}$。
1. 根据 $p$ 的变化改变 $p^{-1}$。
1. 将 $lb_{cnt_x+1}$ 减少 $1$。
1. 将 $cnt_x$ 增加 $1$。

对于减少 $cnt_x$，做法类似。

对于询问，答案就是 $p_{lb_l+k-1}$。

时间复杂度 $O(n+q)$。


------------


算法 2 参考实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int T,n,Q,a[N];
struct Queries
{
	int l,k,ans,id;
};
vector<Queries>q[N];
int tot,h[N];
struct edge
{
	int v,nxt;
}e[N];
void add(int u,int v)
{
	e[++tot]=(edge){v,h[u]};
	h[u]=tot;
}
struct SegmentTree
{
	int sum[N<<2];
	void pushup(int rt){sum[rt]=sum[rt<<1]+sum[rt<<1|1];}
	void build(int rt,int l,int r)
	{
		if(l==r){sum[rt]=0;return;}
		int mid=(l+r)>>1;
		build(rt<<1,l,mid);build(rt<<1,mid+1,r);
		pushup(rt);
	}
	void upd(int rt,int l,int r,int p,int d)
	{
		if(l==p&&r==p){sum[rt]+=d;return;}
		int mid=(l+r)>>1;
		if(p<=mid)upd(rt<<1,l,mid,p,d);
		else upd(rt<<1|1,mid+1,r,p,d);
		pushup(rt);
	}
	int querysum(int rt,int l,int r,int L,int R)
	{
		if(L<=l&&r<=R)return sum[rt];
		int res=0,mid=(l+r)>>1;
		if(L<=mid)res+=querysum(rt<<1,l,mid,L,R);
		if(R>mid)res+=querysum(rt<<1|1,mid+1,r,L,R);
		return res;
	}
	int querynum(int rt,int l,int r,int rk)
	{
		if(l==r)return (rk<=sum[rt]?l:0);
		int mid=(l+r)>>1;
		if(sum[rt<<1]>=rk)return querynum(rt<<1,l,mid,rk);
		else return querynum(rt<<1|1,mid+1,r,rk-sum[rt<<1]);
	}
}segt;
set<int>S[N];
int cnt[N],out[N];
void dfs(int u,int fa)
{
	S[cnt[a[u]]+1].insert(a[u]);
	if(cnt[a[u]])
		S[cnt[a[u]]].erase(a[u]),segt.upd(1,1,n,cnt[a[u]],-1);
	cnt[a[u]]++;
	segt.upd(1,1,n,cnt[a[u]],1);
	for(int i=0;i<(int)q[u].size();i++)
	{
		int rk=(q[u][i].l>1?segt.querysum(1,1,n,1,q[u][i].l-1):0);
		int pos=segt.querynum(1,1,n,q[u][i].k+rk);
		out[q[u][i].id]=(S[pos].size()?*S[pos].begin():-1);
	}
	for(int i=h[u];i;i=e[i].nxt)
		if(e[i].v!=fa)dfs(e[i].v,u);
	if(cnt[a[u]]>1)
		S[cnt[a[u]]-1].insert(a[u]),segt.upd(1,1,n,cnt[a[u]]-1,1);
	S[cnt[a[u]]].erase(a[u]);segt.upd(1,1,n,cnt[a[u]],-1);
	cnt[a[u]]--;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&Q);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=2,p;i<=n;i++)scanf("%d",&p),add(p,i);
		for(int i=1,v,l,k;i<=Q;i++)
		{
			scanf("%d%d%d",&v,&l,&k);
			q[v].push_back((Queries){l,k,-1,i});
		}
		segt.build(1,1,n);
		dfs(1,0);
		for(int i=1;i<=Q;i++)printf("%d ",out[i]);
		puts("");
		for(int i=1;i<=n;i++)S[i].clear(),q[i].clear(),h[i]=0;
		tot=0;
	}
	return 0;
}
```

---

## 作者：peterwuyihong (赞：2)

又被 $\texttt{myee}$ 抓車了，滚来写题

题意：给一棵有点权的树，进行 $q$ 次询问 $v,l,k$，把根节点到 $v$ 的点权写下来，去掉其中出现次数小于 $l$ 的数，再去重后输出按值域排输出第 $k$ 大，如果不存在就输出 $-1$。

显然先离线挂在树上 dfs，然后问题就转化为动态给一个集合增加数或删除数，再询问。

你可以把那个东西转化为 记 $u$ 为多少个数出现次数小于 $l$，然后求第 $k+u$ 大，直接值域 ds 维护就行了，可以二分加树状数组，或者直接线段树上二分，可以少一只老哥。

感觉写拉了，讨论有一点小多。

```cpp
void solve(){
  int n,q;
  cin>>n>>q;
  vector<int>a(n);
  for(int&i:a)cin>>i;
  vector<vector<int> >g(n);
  rep(i,1,n-1){
    int x;cin>>x;
    g[x-1].push_back(i);
  }
  vector<vector<array<int,3> > >Q(n);
  vector<int>ans(q);
  rep(i,0,q-1){
    int v,l,k;
    cin>>v>>l>>k;v--;
    Q[v].push_back({l,k,i});
  }
  vector<int>sm(n*4+1);
  function<void(int,int,int,int,int)>
  insert=[&](int pos,int d,int l,int r,int x){
    sm[x]+=d;
    if(l==r)return;
    int mid=(l+r)>>1;
    if(pos<=mid)insert(pos,d,l,mid,x<<1);
    else insert(pos,d,mid+1,r,x<<1|1);
  };
  function<int(int,int,int,int)>
  ask=[&](int k,int l,int r,int x){
    if(k>sm[x])return -1;
    if(l==r)return l;
    int o=sm[x<<1],mid=(l+r)>>1;
    if(k>o)return ask(k-o,mid+1,r,x<<1|1);
    return ask(k,l,mid,x<<1);
  };
  vector<int>app(n+1);
  vector<int>c(n+1);
  auto ad=[&](int x,int y){
    for(;x<=n;x+=x&-x)c[x]+=y;
  };
  auto qry=[&](int x){
    int ans=0;
    for(;x;x-=x&-x)ans+=c[x];
    return ans;
  };
  vector<set<int> >G(n+1);
  function<void(int x)>dfs=[&](int x){
    if(app[a[x]]!=0){
      insert(app[a[x]],-1,1,n,1);
      ad(app[a[x]],-1);
      G[app[a[x]]].erase(a[x]);
    }
    insert(app[a[x]]+1,1,1,n,1);
    G[app[a[x]]+1].insert(a[x]);
    ad(++app[a[x]],1);
    for(auto[l,k,id]:Q[x]){
      int u=qry(l-1);
      k+=u;
      int tmp=ask(k,1,n,1);
      if(tmp==-1)ans[id]=-1;
      else ans[id]=*G[tmp].begin();
    }
    for(int y:g[x])
      dfs(y);
    app[a[x]]--;
    if(app[a[x]]!=0){
      insert(app[a[x]],1,1,n,1);
      ad(app[a[x]],1);
      G[app[a[x]]].insert(a[x]);
    }
    insert(app[a[x]]+1,-1,1,n,1);
    ad(app[a[x]]+1,-1);
    G[app[a[x]]+1].erase(a[x]);
  };
  dfs(0);
  for(int i:ans)cout<<i<<' ';
  cout<<endl;
}
```
希望能看到在线的解法。

以及这份代码在非 64 位环境下才能过，看不懂了，在洛谷上是自动 64 的，我用了[卡爬虫的办法](https://www.luogu.com.cn/record/72679711)得到了这题的 AC 记录

---

## 作者：IdnadRev (赞：1)

## 题意

给定一棵 $n$ 个点的带点权有根树，$q$ 次询问，给定 $v,l,k$，你需要将根结点 $1$ 到 $v$ 路径上所有出现次数大于等于 $l$ 的数按照出现次数升序排序，并求出第 $k$ 个数是什么。

$1\leqslant \sum n,\sum q\leqslant 10^6$。

## 分析

比较简单的一道题目。

考虑离线，把询问挂在 $v$ 上，然后再树上扫一遍。

对于每个询问，我们二分一下出现次数，那么只需要 check 这个出现次数对应的数字种类数量是否小于 $k$。

可以在树上遍历的同时维护当前位置到根的所有数字出现次数，以及出现次数对应的数字数量，那么 check 就只需要 $O(1)$ 了。

时间复杂度 $O((\sum n+\sum q)\log n)$。

## 代码

```
#include<stdio.h>
#include<vector>
#include<set>
using namespace std;
const int maxn=1000005;
int T,n,q;
int a[maxn],p[maxn],ans[maxn],ll[maxn],kk[maxn],cnt[maxn],cntcnt[maxn];
vector<int>v[maxn],g[maxn];
set<int>s[maxn];
void dfs(int x,int last) {
	if(cnt[a[x]]>0)
		s[cnt[a[x]]].erase(a[x]);
	cnt[a[x]]++,cntcnt[cnt[a[x]]]++,s[cnt[a[x]]].insert(a[x]);
	for(int i=0; i<v[x].size(); i++) {
		int q=v[x][i],L=ll[q],R=n+1;
		if(cntcnt[ll[q]]<kk[q]) {
			ans[q]=-1;
			continue;
		}
		while(L+1<R) {
			int mid=(L+R)>>1;
			if(cntcnt[ll[q]]-cntcnt[mid]<kk[q])
				L=mid;
			else R=mid;
		}
		ans[q]=*s[L].begin();
	}
	for(int i=0; i<g[x].size(); i++)
		dfs(g[x][i],x);
	s[cnt[a[x]]].erase(a[x]),cntcnt[cnt[a[x]]]--,cnt[a[x]]--;
	if(cnt[a[x]]>0)
		s[cnt[a[x]]].insert(a[x]);
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&q);
		for(int i=1; i<=n; i++)
			scanf("%d",&a[i]),g[i].clear(),v[i].clear();
		for(int i=2; i<=n; i++)
			scanf("%d",&p[i]),g[p[i]].push_back(i);
		for(int i=1,x; i<=q; i++)
			scanf("%d%d%d",&x,&ll[i],&kk[i]),v[x].push_back(i);
		dfs(1,0);
		for(int i=1; i<=q; i++)
			printf("%d%c",ans[i],i==q? '\n':' ');
	}
	return 0;
}
```

---

## 作者：KemononeRou (赞：1)

赛时最后 10s 网络爆炸，没交上去痛失 AK/fn

## 题意

- 给定一棵 $n$ 个结点的有根树，根为 $1$，每个点有一个颜色 $a_i$，$p_i$ 表示 $i+1$ 的父亲。
- 有 $q$ 次询问，每次询问给定三个正整数 $v,l,k$。
- 你需要统计出 $v$ 到根节点路径上的所有点中，每种颜色的出现次数，然后将出现次数小于 $l$ 的颜色删除。
- 求剩下的颜色中出现次数第 $k$ 少的颜色，若有多个输出任意一个，若剩下的颜色不足 $k$ 个输出 $-1$。
- $t$ 组测试，$\sum n,\sum q\leq 1e6$，$a_i,p_i,v,l,k\leq n$。

## 题解

思路比较简单，所以后面讲优化的部分可能比较多。

大致思路就是先将询问离线挂到对应节点上，然后跑一遍 dfs。

dfs 的时候维护当前结点到根的路径上每种颜色的出现次数，对于每个询问，在出现次数不小于 $l$ 的颜色中找第 $k$ 小。

每种颜色的出现次数可以开个桶直接维护，找区间第 $k$ 小可以用一些数据结构维护。

数据范围和四秒时限，容易想到大常数 $O(n\log{n})$ 或小常数 $O(n\log^2{n})$。

可以对每种出现次数开个 set 记录对应的颜色，每次修改一个颜色的出现次数时相当于将当前颜色在一个 set 中删除，丢进另一个对应的 set。

然后可以用平衡树找第 $k$ 小的出现次数，复杂度 $O(n\log{n})$。

或者可以用二分 + 权值树状数组找第 $k$ 小的出现次数，复杂度 $O(n\log^2{n})$。

现在已经足以通过本题了。但是我们发现它跑得飞慢！！1

这里给出一种小常数（？）$O(n\log{n})$ 的做法。目前在 CF 上是最优解。

实际上大概就是对上面所说的二分 + 权值树状数组的优化。

- set 是不必要的。

可以用队列/栈 + 懒删除代替。

- 二分 + 树状数组可以用树状数组上二分优化掉一只 $\log$。

容易发现出现次数不小于 $l$ 对应的总是一段后缀区间，考虑将它变成一段前缀区间。

容易想到，用 $n+1$ 减去每种颜色的出现次数，它就变成一段前缀区间了！

但是此时所求的就不是出现次数不小于 $l$ 的第 $k$ 小了。

假设之前有 $m$ 种出现次数不小于 $l$ 的颜色，那么我们转化后就变成了求第 $m-k+1$ 小。

其实刚刚我在翻提交记录的时候还看见了一种做法：

就是直接对整个树状数组查询第 $k+ \sum_{i=1}^n[tot_i<l]$ 小，其中 $tot_i$表示颜色 $i$ 的出现次数，但是还是要在树状数组上二分。

具体如何树状数组上二分和找第 $k$ 小可以参考 [P6619 冰火战士 题解](https://www.luogu.com.cn/problem/solution/P6619) 和 [这篇博客](https://www.cnblogs.com/zgmf_x20a/archive/2008/11/15/1334109.html)。

[我的代码](https://www.luogu.com.cn/paste/yjkzwzaw)是用 vector 代替了栈。

如果你被卡常了：

- 加上快读快输。

- vector 的 clear 是 $O(n)$ 的，换成 $O(1)$ 的 resize。

实测会快很多。

---

