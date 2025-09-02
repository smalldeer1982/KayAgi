# [JOI 2025 Final] 邮局 / Post Office

## 题目背景

译自 [第24回日本情報オリンピック 本選](https://contests.ioi-jp.org/joi-ho-2025/index.html) T5。


## 题目描述


有一张 $N$ 个节点 $N$ 条边的有向图，节点标号 $1\sim N$。

第 $i$ 条边从节点 $i$ 指向节点 $P_i$（注意，可能出现 $i=P_i$ 的情况），需要花 $1$ 单位时间经过它。

有 $M$ 个包裹，第 $j$（$1\le j\le M$）个包裹要从节点 $A_j$ 运到节点 $B_j$。这些包裹全部从 $0$ 时刻开始运送。

每条边一次只能运送一个包裹。节点可以存储无限多个包裹。

判断：是否能够将所有包裹都运到目的地。如果可以，还要求出到达时间最晚的包裹的最早到达时刻。

## 说明/提示


### 样例解释

#### 样例 $1$ 解释

该样例满足子任务 $2,3,4,6,7$ 的限制。


#### 样例 $2$ 解释
该样例满足子任务 $1,2,7$ 的限制。



#### 样例 $3$ 解释
该样例满足子任务 $2,4,6,7$ 的限制。

#### 样例 $4$ 解释
该样例满足子任务 $2,5,7$ 的限制。


#### 样例 $5$ 解释
该样例满足子任务 $2,6,7$ 的限制。



#### 样例 $6$ 解释
该样例满足子任务 $2,7$ 的限制。



### 数据范围

- $2\le N\le 2\times 10^5$。
- $1\le M\le 2\times 10^5$。
- $1\le P_i\le N$（$1\le i\le N$）。
- $1\le A_i,B_i\le N$（$1\le i\le M$）。
- $A_i\neq B_i$（$1\le i\le M$）。
- 输入的值全部是整数。

### 子任务

1. （3pts）$N\le 3,000$，$M=1$。
1. （9pts）$N\le 3,000$，$M\le 3,000$。
1. （13pts）$P=(1,1,2,\cdots,N-1)$，$\max(B_1,B_2,\cdots,B_M)\lt \min(A_1,A_2,\cdots,A_M)$。
1. （25pts）$P=(1,1,2,\cdots,N-1)$。
1. （11pts）$P=(N,1,2,\cdots,N-1)$。
1. （25pts）$P_1=1$，$P_i\lt i$（$2\le i\le N$）。
7. （14pts）无额外限制。

## 样例 #1

### 输入

```
5
1 1 2 3 4
3
3 2
3 1
3 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3
2 1 3
1
1 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
7
1 1 2 3 4 5 6
6
4 2
5 1
5 3
6 2
7 3
7 6```

### 输出

```
5```

## 样例 #4

### 输入

```
4
4 1 2 3
4
4 1
4 1
2 3
2 3```

### 输出

```
4```

## 样例 #5

### 输入

```
7
1 1 1 3 3 4 4
5
6 1
6 3
7 1
5 1
5 1```

### 输出

```
5```

## 样例 #6

### 输入

```
11
3 1 2 5 6 7 8 4 4 5 10
6
2 1
9 8
11 8
10 4
5 6
5 7```

### 输出

```
6```

# 题解

## 作者：DaiRuiChen007 (赞：11)

[Problem Link](https://www.luogu.com.cn/problem/P11666)

**题目大意**

> 给定 $n$ 个点的基环内向树森林，$m$ 条个棋子要从 $u\to v$，每个时刻可以把每个棋子移动到父亲，但同一个格子的棋子只能移动一个，求所有棋子到达的最小时间。
>
> 数据范围：$n,m\le 2\times 10^5$。

**思路分析**

首先我们每轮肯定有限移动距离远终点的点，这样可以得到一个朴素暴力。

但是这个做法无法优化，需要更好地刻画答案，考虑每条边对答案的贡献，即对于每条边 $u\to fa_u$，我们计算所有棋子都离开 $u$ 的最小时刻 $w_u$。

设所有经过这条边的棋子到 $u$ 的距离为 $d_1\sim d_k$（按离开顺序排列），考虑每个棋子离开这条边的时刻 $t_i$，那么有 $t_i\ge \max(d_i,t_{i-1})+1$。

此时 $w_u=\max d_{k-i+1}+i$，显然 $d$ 升序时取到最小。

我们能证明答案恰好能取到下界 $\max w_u$，观察 $w_u$ 的计算，相当于对于一些在 $u$ 的前驱处重合的棋子，我们钦定他们可以一起运动到 $u$ 再考虑重合的问题。

直观上来看这个做法是很对的，因为重合后这两个棋子已经没有本质区别，无论谁先到 $u$ 都是等价的。

即所有经过这条边的棋子的贡献可以正确计算，但有一些不经过 $u$ 的棋子，我们还要考虑他对答案的影响。

对于一条链 $x\to y\to u$，如果有一个棋子从 $x\to y$，那么他在 $x$ 处可能卡住其他到 $u$ 的径棋子

根据我们的朴素贪心，这显然是不可能的，因为经过 $u$ 的棋子剩余距离更大，因此 $x\to y$ 的棋子一定会在这些棋子离开 $x$ 之后再运动，所有这些棋子无影响。

所以我们能证明最优解中，最后一个棋子离开这条边的时刻恰好就是 $w_u$。

那么考虑树的情况，把过 $u$ 的路径用线段树合并，维护每条路径终点的深度，push up 时左边的最大答案加上右边的终点个数，这样就能维护 $w_u$ 了。

然后处理基环树，我们只要让覆盖每条边的棋子集合正确即可。

随便找一条边破环为链，然后把整棵基环树复制一遍接到末尾，如果过 $x\to y$ 路径过环边 $p\to fa_{p}$，就拆成 $x\to p$ 和 $x'\to y$，容易证明此时覆盖每条路径的棋子集合不变。

时间复杂度 $\mathcal O((n+m)\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=4e5+5;
struct SegmentTree {
	int tot,ls[MAXN*20],rs[MAXN*20],mx[MAXN*20],ct[MAXN*20];
	void psu(int p) {
		ct[p]=ct[ls[p]]+ct[rs[p]],mx[p]=max(mx[ls[p]]+ct[rs[p]],mx[rs[p]]);
	}
	void ins(int u,int op,int l,int r,int &p) {
		if(!p) p=++tot;
		if(l==r) return ct[p]+=op,mx[p]=(ct[p]?l+ct[p]:0),void();
		int mid=(l+r)>>1;
		u<=mid?ins(u,op,l,mid,ls[p]):ins(u,op,mid+1,r,rs[p]);
		psu(p);
	}
	void merge(int l,int r,int q,int &p) {
		if(!q||!p) return p|=q,void();
		if(l==r) return ct[p]+=ct[q],mx[p]=(ct[p]?l+ct[p]:0),void();
		int mid=(l+r)>>1;
		merge(l,mid,ls[q],ls[p]),merge(mid+1,r,rs[q],rs[p]);
		psu(p);
	}
}	T;
vector <int> G[MAXN],D[MAXN];
int n,m,fa[MAXN],dsu[MAXN],tp[MAXN];
int find(int x) { return x^dsu[x]?dsu[x]=find(dsu[x]):x; }
int dcnt,dfn[MAXN],rdn[MAXN],dep[MAXN];
void dfs1(int u) {
	dfn[u]=++dcnt;
	for(int v:G[u]) dep[v]=dep[u]+1,tp[v]=u?tp[u]:v,dfs1(v);
	rdn[u]=dcnt;
}
int op[MAXN],ans,rt[MAXN];
void ins(int x,int y) { ++op[y],D[x].push_back(dep[y]); }
void dfs2(int u) {
	for(int v:G[u]) dfs2(v),T.merge(0,2*n,rt[v],rt[u]);
	T.ins(dep[u],op[u],0,2*n,rt[u]);
	for(int i:D[u]) T.ins(i,-1,0,2*n,rt[u]);
	ans=max(ans,T.mx[rt[u]]-dep[u]);
}
signed main() {
	scanf("%d",&n),iota(dsu+1,dsu+n+1,1);
	for(int i=1;i<=n;++i) scanf("%d",&fa[i]),fa[i+n]=fa[i]+n,dsu[find(i)]=find(fa[i]);
	for(int i=1;i<=n;++i) if(dsu[i]==i) {
		int x=i;
		for(;dsu[x];x=fa[x]) dsu[x]=0;
		fa[x+n]=fa[x],fa[x]=0;
	}
	for(int i=1;i<=2*n;++i) G[fa[i]].push_back(i);
	dfs1(0),scanf("%d",&m);
	for(int x,y;m--;) {
		scanf("%d%d",&x,&y);
		if(dfn[y]<=dfn[x]&&dfn[x]<=rdn[y]) ins(y,x);
		else if(dfn[y]<=dfn[x+n]&&dfn[x+n]<=rdn[y]) ins(y,x+n),ins(tp[y],x);
		else return puts("-1"),0;
	}
	dfs2(0),printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Rain_chr (赞：7)

**题意**

有 $n$ 个点，每个点有一条 $(i,p_i)$ 的有向边。一共有 $m$ 个棋子，每个棋子要从 $a_i$ 去往 $b_i$。每一个时刻你可以选择一些节点 $i$，把上面的一个棋子移动到 $p_i$。求所有棋子都到达 $b_i$ 的最小时刻。

$n,m\le 2\times 10^5$

我们显然有一个贪心策略，每一轮移动每个点上剩余距离最长的棋子，于是就有一个 $O(nm\log m)$ 的做法。模拟已经不好优化了，这个时候就得发现一条非常厉害的性质了：

> 答案等价于每条边中最后一个经过这条边的点所花费的时间的最大值

这句话非常绕，具体来说就是你枚举每一条边，对于一种方案可以算出最后一个经过这条边的点他所需要的时间，然后答案就是每条边这个时间的最大值。

具体来说怎么证呢？这个性质需要的结论是每个点上的操作互相独立，互不影响。也就是说这一个点的策略，不影响除出边外的所有边最后一个经过的点所花费的时间。

考虑枚举两个点 $(x,y)$ 满足 $x$ 可以到达 $y$，根据贪心策略，如果 $x$ 上有棋子的路径经过 $y$，那么他出发的时间一定比其他不经过 $y$ 的棋子早，不影响 $y$ 的时间，所以每一条边的策略是互相独立的。

具此，我们也可以得到一个结论，每个要经过 $y$ 的棋子如果在去往 $y$ 的时候重叠了，我们可以视作没有重叠，最后在 $y$ 这个点重叠。因为如果两个棋子在去往 $y$ 的时候需要等待，这两个棋子一定都要经过 $y$。

假设要经过 $y$ 的棋子到 $y$ 的距离从小到大分别是 $\{a_1,a_2,\dots,a_k\}$，那么最后一个经过 $y$ 的棋子花费的时间是

$$\max \{a_1+k,a_2+k,\dots,a_k+1\}$$

所以对于出边形成内向树森林的情况，我们使用线段树合并，距离可以转化为深度，合并的同时维护上述式子的值即可做到 $O(m\log m)$。

更进一步，对于基环树森林的情况，我们可以把环展开，复制所有节点以及棋子的路径，然后规约到树上问题，这样所有的路径都可以被考虑了。

**注意：如果路径应该遵循以下方式复制**

1. 如果 $(a,b)$ 没有绕过环，加入 $(a,b),(a+n,b+n)$

2. 如果 $(a,b)$ 绕过环，加入 $(a,b+n),(a+n,root)$，root 是当前第二棵树的根。

为什么要加入 $(a+n,root)$，是因为虽然确实如果有一个棋子的复制的路径和(a+n,root)相交，那么这个棋子本来的路径就一定会和(a,b+n)在第一棵树相交，但是相交的部分是不一样的，两个相交的部分加起来才是总体相交的部分。

![](https://cdn.luogu.com.cn/upload/image_hosting/tt58xlzt.png)

就像上图所示，OP这条线段如果不加进去，[12,15]这一段就只有三条线段被考虑了


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;
int p[N];
struct dsu
{
	int fa[N];
	int find(int x)
	{
		if(fa[x]==x) return x;
		return fa[x]=find(fa[x]);
	}
	void merge(int x,int y){fa[find(x)]=find(y);}
}T; 
bool ring[N];
int in[N];
vector<int> a[N];
int dfn[N],siz[N],cnt,d[N];
int root[N];
void dfs(int x)
{
	dfn[x]=++cnt,siz[x]=1;
	for(int to:a[x]) d[to]=d[x]+1,root[to]=root[x],dfs(to),siz[x]+=siz[to];
}
int upd[N];
vector<int> del[N];
struct Segment_Tree
{
	struct node
	{
		int val,cnt;
		int lt,rt;
	}t[N<<5];
	Segment_Tree(){t[0].val=-1e9;}
	int root[N],cnt;
	void pushup(int x)
	{
		t[x].cnt=t[t[x].lt].cnt+t[t[x].rt].cnt;
		t[x].val=max(t[t[x].lt].val+t[t[x].rt].cnt,t[t[x].rt].val);
	}
	void upd(int &x,int l,int r,int pos,int v)
	{
		if(!x) x=++cnt,t[x].val=-1e9;
		if(l==r) 
		{
			t[x].cnt+=v;
			t[x].val=t[x].cnt?l+t[x].cnt:-1e9;
		}
		else
		{
			int mid=(l+r)>>1;
			if(pos<=mid) upd(t[x].lt,l,mid,pos,v);
			else upd(t[x].rt,mid+1,r,pos,v);
			pushup(x);
		}
	}
	void merge(int &x,int a,int b,int l,int r)
	{
		if(!a||!b) x=a+b;
		else 
		{
			x=a;
			if(l==r) 
			{
				t[a].cnt+=t[b].cnt;
				t[a].val=t[a].cnt?l+t[a].cnt:-1e9;
			}
			else
			{
				int mid=(l+r)>>1;
				merge(t[a].lt,t[a].lt,t[b].lt,l,mid);
				merge(t[a].rt,t[a].rt,t[b].rt,mid+1,r);
				pushup(a);
			}
		}
	}
	void print(int x,int l,int r,int v)
	{
		if(l==r) 
		{
			if(t[x].cnt) cout<<l-v<<' '<<t[x].cnt<<'\n';
		}
		else
		{
			int mid=(l+r)>>1;
			print(t[x].lt,l,mid,v);
			print(t[x].rt,mid+1,r,v); 
		}
	}
}S;
int ans;
int n;
void dfs2(int x)
{
	for(int to:a[x])
	{
		dfs2(to);
		S.merge(S.root[x],S.root[x],S.root[to],1,2*n);
	}
	S.upd(S.root[x],1,2*n,d[x],upd[x]);
	for(int i:del[x]) S.upd(S.root[x],1,2*n,i,-1);
	ans=max(ans,S.t[S.root[x]].val-d[x]);
}
void copy(int x)
{
	for(int to:a[x])
	{
		if(ring[to]) continue;
		a[x+n].push_back(to+n);
		copy(to);
	}
}
void add(int a,int b)
{
	upd[a]++;
	del[b].push_back(d[a]);
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) T.fa[i]=i;
	for(int i=1;i<=n;i++) 
	{
		cin>>p[i],T.merge(i,p[i]);
		a[p[i]].push_back(i),in[p[i]]++;
	}
	queue<int> q;
	for(int i=1;i<=n;i++) if(!in[i]) q.push(i);
	while(q.size())
	{
		int x=q.front();
		q.pop();
		in[p[x]]--;
		if(!in[p[x]]) q.push(p[x]);
	}
	vector<int> rt;
	for(int i=1;i<=n;i++)
	{
		if(!in[i]) continue;
		vector<int> vt;
		int now=i;
		while(in[now])vt.push_back(now),ring[now]=1,in[now]=0,now=p[now];
		int x=vt[0],y=vt.back();
		a[x].erase(find(a[x].begin(),a[x].end(),y));
		for(int i:vt) copy(i);
		for(int i=1;i<vt.size();i++) a[vt[i]+n].push_back(vt[i-1]+n);
		a[x+n].push_back(y);
		rt.push_back(y+n);
	}
	for(int i:rt) d[i]=1,root[i]=i,dfs(i);
	int m;
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		int a,b;
		cin>>a>>b;
		if(T.find(a)!=T.find(b)) {cout<<-1;return 0;}
		else if(dfn[b]<=dfn[a]&&dfn[a]<dfn[b]+siz[b]) add(a,b),add(a+n,b+n);
		else if(ring[b]) add(a,b+n),add(a+n,root[a]); 
		else {cout<<-1;return 0;}
	}
	for(int i:rt) dfs2(i);
	cout<<ans;
	return 0;
}
```

---

## 作者：qiuzx (赞：4)

一个直观的贪心就是每次有多个人需要走一条边时，选择距离目的地最远的一个人。这样做的依据是当两个人需要走同一条边时，他们后面的路径是完全一样的，直到其中一个人到达目的地。因此如果我们让一个距离更近的人先走，则将他们两个人交换一下，对于两个人路径的公共部分，相当于没有影响（在其他人看来，总是这两个时刻存在一个人走过去，只不过是具体谁走了的区别）。但此时距离更远者在脱离路径公共部分的时刻更小，从而只需要复制原来的决策就一定可以做到不劣于原来的时间到达。

但是直接维护这个贪心的过程是十分复杂的，因为在一个位置的交汇停留可能会导致后续更多的交汇，这些时间是无法在一开始就全部预知的。但注意到我们只关心最后一个到达的时刻，这意味着我们或许可以不用维护这个过程而从其它的角度得到答案。

答案其实就等于所有边被经过的时刻的最大值。先考虑一条边，计算在只考虑它时，最后一次经过它的时刻 $t_i$ 的最小值。我们取出所有经过这条边的路径，并钦定这些路径到达它的顺序，假设从这些路径的起点到当前边的距离依次为 $d_1,d_2,\cdots,d_k$，那么第 $i$ 个人实际到达这条边的时刻 $w_i$ 必然满足 $w_i\ge \max(d_i,w_{i-1}+1)$，因为不能存在两条边在同一时刻到达。可以说明一定存在一种方案使得等号能够取到，并且在 $w_i=\max(d_i,w_{i-1}+1)$ 时，按照 $d$ 从小到大的顺序进行排列可以使得 $w_k$ 最小，此时 $w_k=\max_i(d_i+k-i)$。

假如我们已经求出所有的 $t_i$，那么答案的一个下界就是 $\max t_i$，实际上这个下界是能够取到的。这是因为在计算 $t_i$ 的过程中，按照最开始的贪心策略进行决策可以达到 $t_i$ 的最小值。而在进行这个贪心的过程中，如果我们同时考虑其它不经过当前边的路径，则一条新的路径 $s_1\to e_1$ 可能会阻拦一条原来被考虑到的路径 $s_0\to e_0$ 以使得 $t_i$ 增大的情况只可能是 $e_1$ 是当前边之前的某个点（否则这两条路径汇聚之后 $s_1\to e_1$ 一定会经过当前边，矛盾）。然而根据我们贪心的原则，由于 $e_1$ 距离汇聚点比 $e_0$ 更近，所以会优先移动 $s_0\to e_0$，因此新的路径并不会影响答案。所以我们说明了按照这个贪心原则，最终每条边被经过的最大时刻就是其理论最小能够被经过的时刻 $t_i$。因此我们只需要对每条边计算 $t_i$ 即可。

先考虑链的情形，此时进行扫描线，使用权值线段树维护 $d_i+k-i$ 的最大值。在插入或删除一个 $d_i$ 时，会将一段前缀的值增大或减小 $1$，做区间修改即可。在将指针移动一位时会对所有的 $d_i$ 做平移，此时打一个整体的标记而不去修改线段树的值域，最后求答案的时候把标记加上即可，复杂度 $O(n\log n)$。

对于树的情况也是类似的，此时只需要做线段树合并或者启发式合并以合并两棵子树的权值线段树即可，复杂度 $O(n\log n)$ 或 $O(n\log^2n)$。

最后是原问题。考虑拆环成链，取断开的环上节点为根，然后把得到的树复制一份，将第二份的环头对应的节点与第一份环尾对应的节点连起来。我们现在只需要让经过第一棵树上的每条边（包括新加的这条代表被拆开的环边的这条边）的路径集合等于原问题中在基环树上经过它的路径集合即可。对于一条没有跨过拆掉的边的路径，直接将它看作树上对应的路径。否则这条路径 $s\to t$ 经过了拆开的边，那么把这条路径看作两条，一条从第一棵树的 $s$ 连向根，另一条从第二棵树的 $s$ 连向第一棵树的 $t$。这样加入路径之后按照树的方式做即可。值得注意的是，也可也不用复制这棵树，但此时在连第二种边时会有一个额外的代表原距离的 offset，可能需要特殊处理。如果按照复制树的方式处理就可以直接做。

[代码](https://www.luogu.com.cn/paste/cehdkqg3)（使用了 dsu on tree，复杂度 $O(n\log^2n)$，但是可以通过。也可使用线段树做到更好的复杂度）

---

## 作者：ty_mxzhn (赞：2)

很厉害的题。

## 算法 $1$

考虑每次动的时候贪心的动，能动就动，动离终点最远的棋子，显然是最优的。

期望得分 $12$ 分。

## 算法 $2$

考虑这个东西显然能拆，所有点走完的时间其实就是所有点走完所有该走的边的时间。

考虑某一条该走的边，走过这条边的路径有 $k$ 条。首先，所有和走过这条边的路径相交，但是没有走过这条边的路径，都和这条边的答案无关。这很好理解，因为你会先动距离终点最远的棋子。

考虑两条没有走到这条该走的边就相交的路径，不难理解的是，提前相交和在这条边相交的答案一致。于是我们可以把每条路径分离，这条边的答案只和这些路径的长度有关。

设每条路径的长度为 $a_1 \le a_2 \le a_3 \le ... \le a_k$。

注意到答案为 $\max(a_1+k,a_2+k-1,a_3+k-2,...,a_k+1)$。

1. 这是答案的下界。因为考虑一组相等的边，最倒霉的那条必须要等之后的所有边。
2. 这是答案的上界。因为可以构造方案。

直接做链或者环可以拿一些分。

## 算法 $3$

考虑树。刚才的路径的顺序可以使用线段树合并维护。

考虑环。注意到答案是取 $\max$ 的，直接断环成链则答案不会改变。

考虑基环树。发现其实就是直接断环成链。

时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,tot;
struct stu{
	int ch[2];
	int r[2];
	long long su,mx;
	int& operator [](int z){return ch[z];}
}tr[400007*50];
int rt[400007];
void pushup(int k){
	tr[k].su=tr[tr[k][0]].su+tr[tr[k][1]].su;
	tr[k].mx=max(tr[tr[k][0]].mx+tr[tr[k][1]].su,tr[tr[k][1]].mx);
}
void upd(int &k,int p,int op,int c,int lb=0,int ub=2*n){
	if(k==0) k=++tot;
	if(lb==ub){
		tr[k].r[op]+=c;
		tr[k].su=0;
		if(tr[k].r[0]>0) tr[k].su+=lb+1;
		if(tr[k].r[0]<0) tr[k].su+=-lb-1;
		if(tr[k].r[1]>0) tr[k].su+=lb;
		if(tr[k].r[1]<0) tr[k].su+=-lb;
		tr[k].su+=tr[k].r[1];
		tr[k].mx=max(0ll,tr[k].su);
		return;
	}
	int mid=(lb+ub)>>1;
	if(p<=mid) upd(tr[k][0],p,op,c,lb   ,mid);
	if(p> mid) upd(tr[k][1],p,op,c,mid+1,ub );
	pushup(k);
}
void merge(int &a,int b,int lb=0,int ub=2*n){
	if(a==0||b==0){
		a+=b;
		return;
	}
	if(lb==ub){
		tr[a].r[0]+=tr[b].r[0];
		tr[a].r[1]+=tr[b].r[1];
		tr[a].su=0;
		if(tr[a].r[0]>0) tr[a].su+=lb+1;
		if(tr[a].r[0]<0) tr[a].su+=-lb-1;
		if(tr[a].r[1]>0) tr[a].su+=lb;
		if(tr[a].r[1]<0) tr[a].su+=-lb;
		tr[a].su+=tr[a].r[1];
		tr[a].mx=max(0ll,tr[a].su);
		return;
	}
	int mid=(lb+ub)>>1;
	merge(tr[a][0],tr[b][0],lb   ,mid);
	merge(tr[a][1],tr[b][1],mid+1,ub );
	pushup(a);
}
int m,p[400007],vis[400007],dep[400007];
void dfs1(int u){
	vis[u]=-1;
	int v=p[u];
	if(!vis[v]) dfs1(v);
	else if(vis[v]==-1) p[u]=v+n,p[u+n]=0;
	vis[u]=1;
}
int f[20][400007];
void dfs2(int u){
	vis[u]=1;
	int v=p[u];
	if(!vis[v]) dfs2(v);
	dep[u]=dep[v]+1;
	f[0][u]=v;
}
void init(){
	for(int i=1;i<=n;i++) if(!vis[i]) dfs1(i);
	for(int i=1;i<=n;i++) vis[i]=0;
	vis[0]=1;
	for(int i=1;i<=n*2;i++) if(!vis[i]) dfs2(i);
	//for(int i=1;i<=n*2;i++) printf(" %d\n",dep[i]);
	for(int j=1;j<=19;j++){
		for(int i=1;i<=n*2;i++){
			f[j][i]=f[j-1][f[j-1][i]];
		}
	}
}
int chk(int a,int b){
	for(int i=19;i>=0;i--){
		if(dep[f[i][a]]>=dep[b]) a=f[i][a];
	}
	return a==b;
}
void addedge(int a,int b){
	if(chk(a,b)){
		//printf("111\n");
		upd(rt[a]  ,dep[a]    ,1,1);
		upd(rt[a]  ,dep[a]-1  ,0,-1);
		upd(rt[b]  ,dep[a]    ,1,-1);
		upd(rt[b]  ,dep[a]-1  ,0,1);
		upd(rt[a+n],dep[a+n]  ,1,1);
		upd(rt[a+n],dep[a+n]-1,0,-1);
		upd(rt[b+n],dep[a+n]  ,1,-1);
		upd(rt[b+n],dep[a+n]-1,0,1);
	}else{
		if(chk(a,b+n)){
			upd(rt[a]  ,dep[a]    ,1,1);
			upd(rt[a]  ,dep[a]-1  ,0,-1);
			upd(rt[b+n],dep[a]    ,1,-1);
			upd(rt[b+n],dep[a]-1  ,0,1);
			upd(rt[a+n],dep[a+n]  ,1,1);
			upd(rt[a+n],dep[a+n]-1,0,-1);
		}else{
			printf("-1\n");
			exit(0);
		}
	}
}
int d[400007];
queue<int> q;
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]),p[i+n]=p[i]+n;
	scanf("%d",&m);
	init();
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		addedge(a,b);
	}
	for(int i=1;i<=n*2;i++) d[p[i]]++;
	for(int i=1;i<=n*2;i++) if(d[i]==0) q.push(i);
	long long ans=0;
	while(!q.empty()){
		int u=q.front(),v=p[u];
		if(u==0) break;
		q.pop();
		ans=max(ans,tr[rt[u]].mx-dep[u]);
		d[v]--,merge(rt[v],rt[u]);
		if(d[v]==0) q.push(v);
	} 
	printf("%lld\n",ans);
	return 0;
} 
```

---

## 作者：Godzilla (赞：1)

先假设这个过程在树上进行。

考虑暴力，模拟这个过程，对一条边选择哪个点移动进行决策。发现一定是移动剩余距离最大的点，因为如果移动距离较小的点，调整一定不劣。

但是模拟这个过程无法优化，没有前途。调整思路，不关注时间，而关注每条边，答案显然等于所有边最后经过时间的最大值，如果能计算出每个点 $i$ 到 $x$ 的时间，那么 $(x,p_x)$ 最后经过时间可以通过上述贪心求出。因为每次移动剩余距离最大的点，我们只需要关心所有经过 $(x,p_x)$ 的路径的出发点 $a_i$。

考察特殊情况，如果只有 $1$ 条路径，那么显然到达 $x$ 的时间为 $d_{a_i}-d_{x}$，其中 $d_i$ 表示 $i$ 点的深度。

拓展到一般情况，发现会出现某个时刻，两个点在同一位置，造成堵塞的情况。这种情况不好考虑，不妨猜测不用考虑这种情况，直接另 $a_i$ 到 $x$ 的时间为 $d_{a_i}-d_{x}$ 而不影响答案。证明考虑如果 $u,v$ 两点 $t$ 时刻在 $z$ 点堵塞了，那么到达 $p_z$ 的时刻应为 $t+1,t+2$，但是观察到我们可以将堵塞时间延后，将 $(z,p_z)$ 边扩容，到达 $p_z$ 时刻变为 $t+1,t+1$，但是他们在 $p_z$ 仍会堵塞，那么得到一个结论：将 $(x,p_x)$ 子树内的边扩容为 $+\infty$，不影响 $(x,p_x)$ 答案的计算。

如果得到到达 $x$ 的时间集合 $T$，考虑如何计算 $(x,p_x)$ 的贡献。显然最后经过时刻具有单调性，考虑二分时间 $t$，判断能否再 $\le t$ 时间走完这条边。

考虑 hall 定理，相当于每个时刻 $t_i$ 可以连边 $(t_i,t]$，判断是否存在完美匹配。为了方便，平移一格匹配，也就是 $t_i$ 可以连边 $[t_i,t]$，将求出的时刻 $t$ 加一即可。只需要考虑所有后缀 $(i,t]$，是否都满足 $|N(S)|\ge |S|$，即 $t-i\ge s_{t}-s_{i}$，其中 $s_i$ 表示时刻小于等于 $i$ 的点的个数，条件等价于 $t-s_{t}\ge i-s_{i}$。

这个信息可以通过线段树合并维护区间 $\max\{i-s_i\}$，线段树上二分查询得到。

拓展到基环树上，考虑断环为链，就可以考虑到所有经过环上的路径了，注意到复制的环上的点会正确地考虑到所有信息。

注意到二分的位置需要包含所有子树中目前存在时刻，我先维护区间时刻出现次数和，求出但前最大时刻 $pos$，在 $[pos,+\infty)$ 上二分。

线段树合并需要进行区间修改，为了减少空间，我使用了标记永久化。

事实上观察到 $s_t$ 为定值，那么相当于 $i\ge j+s_{i}-s_{j}$，可以转化为单点修改，答案也是容易合并的。

代码写得很复杂，建议参考其他的题解。

```c++
#include <bits/stdc++.h>
#define file_in(x) (freopen(#x".in", "r", stdin))
#define file_out(x) (freopen(#x".out", "w", stdout))
#define vi vector
#define pr pair <int, int>
#define mk make_pair
#define pb push_back

using namespace std;

bool START;

const int N = 4e5 + 5, M = 100, inf = 1e9;

int n, m, p[N], a[N], b[N];
int stk[N], tot, vis[N];
int d[N], idx, dy[N];
int dfn[N], sz[N], tp[N], dep[N], mxd[N], cnt;
int v[N];
int fr[N], o;
int lim;

int rt[N], mx[N * M], ex[N * M], tag[N * M], ls[N * M], rs[N * M], num;
int ans;

vi <int> G[N], q, id[N];
vi <pr> vc[N];

bool END;

void add_e(int x, int y) {G[x].pb(y);}

void dfs(int x) {
  if (v[x]) {
    bool fl = 0;
    for (int i = 1; i <= tot; ++i) {
      if (stk[i] == x) fl = 1;
      if (fl) d[++idx] = stk[i];
    }
    return;
  }
  stk[++tot] = x, v[x] = 1, dfs(p[x]);
}

void dfs2(int x, int TP) {
  dfn[x] = ++cnt, sz[x] = 1, tp[x] = TP, fr[x] = o, q.pb(x);
  for (auto y : G[x]) if (!vis[y]) dep[y] = dep[x] + 1, dfs2(y, TP), sz[x] += sz[y];
}

void psu(int l, int r, int x) {
  int mid = (l + r) >> 1;
  mx[x] = max(ls[x] ? mx[ls[x]] : mid, rs[x] ? mx[rs[x]] : r) + tag[x];
  ex[x] = ex[ls[x]] + ex[rs[x]];
}

void work(int k, int p) {tag[p] -= k, mx[p] -= k;}

int nnd(int l, int r) {
  return num++, mx[num] = r, ls[num] = rs[num] = ex[num] = tag[num] = 0, num;
}

int mrg(int l, int r, int x, int y) {
  if (!x || !y) return x | y;
  tag[x] += tag[y];
  if (l == r)
    return mx[x] = r + tag[x], ex[x] += ex[y], x;
  int mid = (l + r) >> 1;
  ls[x] = mrg(l, mid, ls[x], ls[y]);
  rs[x] = mrg(mid + 1, r, rs[x], rs[y]);
  return psu(l, r, x), x;
}

void add(int l, int r, int L, int R, int k, int & p) {
  if (!p) p = nnd(l, r);
  if (l >= L && r <= R) return work(k, p);
  int mid = (l + r) >> 1;
  if (L <= mid) add(l, mid, L, R, k, ls[p]);
  if (R > mid) add(mid + 1, r, L, R, k, rs[p]);
  psu(l, r, p);
}

void addex(int l, int r, int ps, int k, int & p) {
  if (!p) p = nnd(l, r);
  if (l == r) return ex[p] += k, void();
  int mid = (l + r) >> 1;
  ps <= mid ? addex(l, mid, ps, k, ls[p]) : addex(mid + 1, r, ps, k, rs[p]);
  psu(l, r, p);
}

int getp(int l, int r, int p) {
  if (!ex[p]) return -1;
  if (l == r) return l;
  int mid = (l + r) >> 1;
  if (ex[rs[p]] > 0) return getp(mid + 1, r, rs[p]);
  return getp(l, mid, ls[p]);
}

int ask(int l, int r, int L, int R, int & premx, int k, int p) {
  int mid = (l + r) >> 1;
  if (!ls[p]) ls[p] = nnd(l, mid);
  if (!rs[p]) rs[p] = nnd(mid + 1, r);
  if (l >= L && r <= R) {
    if (l == r) {
      if (mx[p] + k >= premx) return l;
      return -1;
    }
    k += tag[p];
    if (mx[ls[p]] + k >= premx)
      return ask(l, mid, L, R, premx, k, ls[p]);
    else if (mx[rs[p]] + k >= (premx = max(premx, mx[ls[p]] + k)))
      return ask(mid + 1, r, L, R, premx, k, rs[p]);
    else premx = max(premx, mx[rs[p]] + k);
    return -1;
  }
  k += tag[p];
  if (L <= mid) {
    int t = ask(l, mid, L, R, premx, k, ls[p]);
    if (t != -1) return t;
  }
  premx = max(premx, mx[ls[p]] + k);
  return ask(mid + 1, r, L, R, premx, k, rs[p]);
}

void dfs3(int x) {
  mxd[x] = dep[x];
  for (auto y : G[x]) {
    if (x == d[1] + n && y == d[idx] + n) continue;
    if (x == d[1] && y == d[idx]) continue;
    dfs3(y);
    rt[x] = mrg(0, lim, rt[x], rt[y]), mxd[x] = max(mxd[x], mxd[y]);
  }
  for (auto [t, v] : vc[x]) {
    add(0, lim, t, lim, v, rt[x]);
    addex(0, lim, t, v, rt[x]);
  }
  int tmp = -inf, pos = getp(0, lim, rt[x]);
  if (pos != -1) {
    int tim = ask(0, lim, pos, lim, tmp, 0, rt[x]);
    ans = max(ans, tim - dep[x] + 1);
  }
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n; for (int i = 1; i <= n; ++i) cin >> p[i];
  cin >> m; for (int i = 1; i <= m; ++i) cin >> a[i] >> b[i], id[a[i]].pb(i);
  for (int i = 1; i <= n; ++i) if (!vis[i]) add_e(p[i], i), add_e(p[i] + n, i + n);
  lim = max(n, m) * 2 + 5;
  int fl = 1;
  for (int s = 1; s <= n; ++s) {
    if (v[s]) continue;
    idx = tot = cnt = num = 0, ++o, q.clear();
    dfs(s);
    for (int i = 1; i <= idx; ++i) {
      d[i + idx] = d[i] + n;
      dy[d[i]] = i, vis[d[i]] = 1;
      dy[d[i] + n] = i + idx, vis[d[i] + n] = 1;
    }
    add_e(d[idx + 1], d[idx]);
    for (int i = 1; i <= 2 * idx; ++i)
      dep[d[i]] = 2 * idx - i, dfs2(d[i], d[i]);

    for (int w : q) {
      for (auto i : id[w]) {
	if (fr[b[i]] != o) {fl = 0; break;}
	vc[a[i]].pb(mk(dep[a[i]], 1)), vc[a[i] + n].pb(mk(dep[a[i] + n], 1));
	if (vis[b[i]]) {
	  int l = dy[tp[a[i]]], r = dy[b[i]];
	  if (l <= r)
	    vc[b[i]].pb(mk(dep[a[i]], -1)), vc[b[i] + n].pb(mk(dep[a[i] + n], -1));
	  else vc[b[i] + n].pb(mk(dep[a[i]], -1));
	}
	else {
	  vc[b[i]].pb(mk(dep[a[i]], -1)), vc[b[i] + n].pb(mk(dep[a[i] + n], -1));
	  if (!(tp[a[i]] == tp[b[i]] && dfn[a[i]] >= dfn[b[i]] && dfn[a[i]] < dfn[b[i]] + sz[b[i]])) {
	    fl = 0; break;
	  }
	}
      }
    }
    if (!fl) return cout << -1 << endl, 0;
    dfs3(d[2 * idx]);
  }
  cout << ans << endl;
  return 0;
}

```

---

## 作者：lalaouye (赞：1)

首先根据直觉我们应该先移动离终点更远的点，但是这个东西难以加速。

我们希望对于每条边算贡献，发现显然不是可以通过加法刻画的，考虑对于每条边 $u\rightarrow fa_u$ 所有棋子经过这条边的最晚时间。

但是这看起来就很不可做，因为这样做貌似得基于每条边都是独立的才行，比如说像经典的移动棋子问题，每条边的贡献独立。反观这道题，一条边会受到若干条边决策的影响，但是仔细想想，每个人到达同一个点时，它们几乎是本质相同的，除了目的地不同以外。若我们在考虑 $u\rightarrow fa_u$ 这条边的贡献，那么我们是否可以钦定只在当前这条边考虑限制，也就是说让他们先都走到 $u$ 再考虑限制。考虑归纳证明其正确性，也就是说我们假定钦定他们先走到 $u$ 再考虑限制与原本情况等价。

首先考虑当前在结点 $u$，而他在 $t$ 时刻若有人往上走，当且仅当有人仍在点上。若 $son_u$ 存在 $x$ 个人需要往上走，在这 $x$ 个人提前满足限制的情况下，第一个人到达 $u$ 时使得在这一时刻 $t$，$u$ 上多了一个人，那么下一刻 $u$ 将离开一人，$son_u$ 又上去一个人......不难发现，这与在 $t$ 时刻 $u$ 点上直接增加 $x$ 的人效果是等价的。归纳即可得证。但是还存在一个问题，每个人的目的可能不同，距离较短的人是否会影响到距离较长的人呢？答案是不会的，因为决策时距离较长的人会先走，意味着会直接无视距离较短的人，那么这样正确性是有保证的。

那么对于每个点，若子树内有 $k$ 个人往上走会经过它，距离为 $d_1\sim d_k$，它的贡献为 $\max d_i+k-i+1$。这个信息我们可以直接线段树合并维护。

而对于基环树，我们考虑断掉一个环边。对于经过环边的人，我们希望使得每条边的贡献都能够存在保证。比如若断边为 $(u,v)$，那么对于 $(x,y)$ 的信息，首先我们要加入 $(x,u)$ 的信息满足前半部分。后半部分显然全部都在环上，为了满足距离，我们复制一棵根为 $u$ 的树接到 $v$，若这棵树的编号为原本的编号加 $n$，我们只需要加入 $(x+n,y)$ 的信息即可。

时间复杂度 $\mathcal{O}(n\log n)$。

---

