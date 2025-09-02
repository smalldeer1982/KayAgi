# [IOI 2025] 羊驼的坎坷之旅（obstacles）

## 题目描述

一只羊驼想要穿越安第斯高原。它有一张高原的地图，为 $N \times M$ 个方形单元格组成的网格。地图的行从上到下以 $0$ 到 $N-1$ 编号，列从左到右以 $0$ 到 $M-1$ 编号。地图中第 $i$ 行第 $j$ 列的单元格（$0 \leq i < N$，$0 \leq j < M$）记为 $(i, j)$。

这只羊驼研究了高原的气候，发现地图中每行的所有单元格具有相同的**温度**（temperature），每列的所有单元格具有相同的**湿度**（humidity）。它给了你两个长度分别为 $N$ 和 $M$ 的整数数组 $T$ 和 $H$。这里，$T[i]$（$0 \leq i < N$）表示第 $i$ 行所有单元格的温度，$H[j]$（$0 \leq j < M$）表示第 $j$ 列所有单元格的湿度。

羊驼还研究了高原的植被情况，注意到一个单元格 $(i, j)$ **无植被**的充要条件是其温度大于湿度，形式化为 $T[i] > H[j]$。

羊驼只能通过**合法路径**在高原上移动。合法路径定义为满足以下条件的单元格序列：
* 路径中每对连续单元格之间共享一条边。
* 路径中所有单元格均为无植被的单元格。

你的任务是回答 $Q$ 次询问。对于每次询问，你将获得四个整数：$L$，$R$，$S$ 和 $D$。你需要判断是否存在一条合法路径，使得：
* 路径起点是单元格 $(0, S)$，终点是单元格 $(0, D)$。
* 路径中的所有单元格位于列 $L$ 到 $R$ 之间。

保证 $(0, S)$ 和 $(0, D)$ 均为无植被的单元格。

### 实现细节

你需要实现的第一个函数为：

```
void initialize(std::vector<int> T, std::vector<int> H)
```
 * $T$：长度为 $N$ 的数组，表示每行的温度。
 * $H$：长度为 $M$ 的数组，表示每列的湿度。
 * 对每个测试用例，该函数恰好被调用一次。该函数在 `can_reach` 之前调用。

你需要实现的第二个函数为：

```
bool can_reach(int L, int R, int S, int D)
```
* $L, R, S, D$：描述询问的四个整数。
* 对每个测试用例，该函数会被调用 $Q$ 次。

当且仅当存在一条从单元格 $(0, S)$ 到单元格 $(0, D)$ 的合法路径，使得路径中的所有单元格位于列 $L$ 到 $R$ 之间时，该函数返回 `true`。

## 说明/提示

### 例子

考虑以下调用。

```
initialize([2, 1, 3], [0, 1, 2, 0])
```

这对应于如下地图，其中白色单元格无植被：

![](https://cdn.luogu.com.cn/upload/image_hosting/99d0tson.png)

对第一次询问，考虑以下调用：

```
can_reach(0, 3, 1, 3)
```

这对应如下场景，其中竖直粗线表示列范围 $L = 0$ 到 $R = 3$，黑色圆点表示起点和终点：

![](https://cdn.luogu.com.cn/upload/image_hosting/ze89ex77.png)

在这种情况下，羊驼可以通过以下合法路径从单元格 $(0,1)$ 移动到 $(0,3)$：
$$(0,1), (0,0), (1,0), (2,0), (2,1), (2,2), (2,3), (1,3), (0,3)$$
因此，该调用应返回 `true`。

对第二次询问，考虑以下调用：

```
can_reach(1, 3, 1, 3)
```

其对应如下场景：

![](https://cdn.luogu.com.cn/upload/image_hosting/ci9ill1r.png)

在这种情况下，不存在从单元格 $(0, 1)$ 到 $(0, 3)$ 的合法路径，使得路径中的所有单元格位于列 $1$ 到 $3$ 之间。因此，该调用应返回 `false`。


### 约束条件

* $1 \leq N, M, Q \leq 200\,000$
* 对每个满足 $0 \leq i < N$ 的 $i$，都有 $0 \leq T[i] \leq 10^9$。
* 对每个满足 $0 \leq i < M$ 的 $j$，都有 $0 \leq H[j] \leq 10^9$。
* $0 \leq L \leq R < M$
* $L \leq S \leq R$
* $L  \leq D \leq R$
* $(0, S)$ 和 $(0, D)$ 均为无植被的单元格。

### 子任务

| 子任务 | 分数  | 额外的约束条件 |
| :-----: | :----: | ---------------------- |
| 1       | $10$   | 对每次询问，都有 $L = 0$, $R = M - 1$。$N = 1$。 |
| 2       | $14$   | 对每次询问，都有 $L = 0$, $R = M - 1$。对每个满足  $1 \leq i < N$ 的 $i$，都有$T[i-1] \leq T[i]$。 |
| 3       | $13$   | 对每次询问，都有 $L = 0$, $R = M - 1$。$N = 3$ 和 $T = [2, 1, 3]$。 |
| 4       | $21$   | 对每次询问，都有 $L = 0$, $R = M - 1$。$Q \leq 10$。 |
| 5       | $25$   | 对每次询问，都有 $L = 0$, $R = M - 1$。|
| 6       | $17$   | 没有额外的约束条件。 |

## 样例 #1

### 输入

```
```

### 输出

```
```

# 题解

## 作者：IvanZhang2009 (赞：8)

题外话：我做出来了？我做出来了？我做出来了？中国队只过了一个人的题我做出来了？？？

其实我觉得 $83\rightarrow 100$ 非常简单啊。

我们考虑这个东西简直就是双序列拓展。回忆一下这个题的题意，就是一样的网格，问你能不能从左上走到右下。做这个题的时候我就回忆了一下双序列拓展的几个做法，用热门做法做这个题好像是死路一条，后来想起来我补题的第一个做法是[这个](https://www.luogu.com.cn/article/di5ogaa0)，突然就大有思路！

我们先考虑 $l=0,r=m-1$ 的特殊性质。

首先一句转化就是两个点不可达当且仅当存在一个割，也就是一条不合法的从中间穿过去的路径。可以得到如下几种形式的割（显然要从两个点中间出发；以及忽略对称的情况）：

![](https://cdn.luogu.com.cn/upload/image_hosting/ljc7ev60.png)

注意此处上面的不一定都是直线，只是表达可达性。

我们给左右两边和下面都加一层不可达的点，这样前两种都可以归为第三种（走边路回到第一行）。假设我们能预处理处每一对点 $(i,j)$ 之间是否可以形成割，那两个点 $(s,d)$ 是连通的当且仅当对于任意有割的 $(i,j)$ 都满足，$[i<s<j]=[i<d<j]$。这里容易想到 xor hashing，我们给每一对 $(i,j)$ 赋随机权值，给区间里的异或随机权值，这样就是判断两个点的权值是否相同。

考虑 $(i,j)$ 之间的割。上面说了不一定是直线。但是真的不一定是直线吗？手玩一下可以证明，如果一条路径从 $(0,i)$ 出发到 $(0,j)$ 结束，那必然存在一个 $k$ 使得 $(0,i)$ 到 $(k,i)$ 到 $(k,j)$ 到 $(0,j)$ 的三条直线段都是不合法点。说人话就是那个圈是三条直线。

举一个手玩的例子。称最后的三条线和顶边形成了一个“矩形”。如下图，如果在右下角折了一下，那固定矩形左上角不变，右下角一定可以是折线右下角小矩形四个点之一，否则不合法点之间不满足行列互相包含。对于其它情况，如凸凹状，也可以类似反证。当然严谨证明我还是不会的。

![](https://cdn.luogu.com.cn/upload/image_hosting/s0zt39w3.png)

还有一个观察是如果取出了一个矩形，中间有一列也是全部不合法的，那这个矩形可以选择不要，因为中间一列把它分成了两个小矩形，可以代替它。

所以我们可以限制找的 $(i,j)$ 必须满足 $\max(b_{i+1,\dots,j-1})<\min(b_i,b_j)$，否则中间更大的这一列比两边更容易不合法。那很容易看出来这样的 $(i,j)$ 只有 $O(n)$ 对了。具体来说就是 $i$ 是 $j$ 左边第一个 $b_i\ge b_j$ 的或者相反一定符合一个。

枚举 $(i,j)$，然后需要问是否存在一个 $k$ 使得 $\min(b_i,b_j)\ge \max_{l=0}^k a_l$ 以及 $\min_{t=i}^j b_t\ge a_k$。对于第一个限制，$l$ 是一段前缀，可以二分出来。然后对于第二个限制，求一下前缀内的最优 $a_k$ 即可。

这样特殊性质就做完了，时间复杂度 $O(n+m\log m+q)$。[代码](https://qoj.ac/submission/1199465)。

然后你考虑加上 $[l,r]$ 的限制，那这就等价于我们在两边加的边框收缩了。首先本来就不可达的肯定还是不可达。现在其实只加了一个限制，相当于最开始三种割的第二个（从两个点之间到了两边）。这个同理是两段直线，我们枚举割的起点，很容易二分求出这个横着的直线最远到哪里。然后回答询问的时候 rmq 求出中间最长的横线即可。时间复杂度 $O(n+m\log m+q)$。

笑点解析是我懒得写 rmq 交上去 $O(mq)$ 的时候直接通过了后三个包（ioi 赛制拼包情况下就是直接过了），[提交记录](https://qoj.ac/submission/1199509)。

[通过代码](https://qoj.ac/submission/1199528)。

---

## 作者：min_inf (赞：6)

比较答辩但是很人类的做法！！

注意到起点终点都在第一行，这个看上去很有性质。我们猜测路径一定形如一堆 $(0,a)\to(x,a)\to(x,b)\to(0,b)$。设一列中第一个空的位置是 $fi_i$，前缀连续空的长度是 $cn_i$，$a\to b$ 之间的 $\max H$ 位置为 $c$，那能这么走就相当于 $fi_c\le\min(cn_a,cn_b)$。

这启发我们建出 $H$ 的笛卡尔树。如果我们现在在一个子树 $x$，如果我们能到达 $fi_x$，那去子树内 $cn$ 最大的点肯定是不劣的，然后如果 $\max cn\ge fi_{fa_x}$ 那就可以走到 $x$ 的父亲，询问的时候只要看能跳到最高的位置是否相等即可。倍增做就可以获得 $83$ 分。

对于最后一个 subtask，我们考虑区间笛卡尔树：先一直倍增到子树包含了端点，此时当前节点 $x$ 一定是 $[l,x]$ 或者 $[x,r]$ 的 $\max$。如果两者都是那 $x$ 就是根；如果 $x$ 是 $[l,x]$ 的 $\max$ 那父亲一定是 $R_x=\min\limits_{y>x}H_y>H_x$，左儿子是 $[l,x-1]$，右儿子就是在笛卡尔树上的右儿子。如果右儿子的 $\max cn$ 已经满足要求那直接跳就行，否则需要 $l \le\max\limits_{i<x,cn_i\ge fi_{R_x}}i$，倍增跳 $R$ 的时候维护所有点这个 $\max i$ 的 $\min$ 即可。$x$ 是 $[x,r]$ 的 $\max$ 的情况就是反过来。

时间复杂度 $O(n+m\log nm+q\log m)$。[code](https://qoj.ac/submission/1199459)

---

## 作者：_lmh_ (赞：4)

我们发现，设第 $i$ 列的可行集合为 $P_i$，那么对于任意 $i,j$，如果 $H_i\ge H_j$，则 $P_i\subseteq P_j$。

同理，设第 $i$ 行可行集合为 $C_i$，那么对于任意 $i,j$，如果 $T_i\le T_j$，则 $C_i\subseteq C_j$。

首先考虑 $T_{i-1}\le T_i$ 的部分分，此时可以从起点开始贪心向下走（走到编号更大的一行），然后走到终点所在列，最后往上走。如果中间被挡住，那么无解。

容易验证这个策略的可行性：每一行的可行列的集合都比上一行更大。

现在把 $T$ 中所有前缀最大值找出来，设其为 $A_0\sim A_k$。找出这 $k+1$ 行中所有横向的连续段。

此时的最优策略一定是：

首先，找出最小的 $p$ 使得 $S,D$ 在第 $A_p$ 行中同属一个连续段——若不存在则无解。

然后，让两个点分别从 $(0,S)$ 和 $(0,D)$ 出发尝试走到第 $A_p$ 行，然后让它们相遇。

这样就只需要考虑一个点尝试从 $A_x$ 行的一个连续段走到 $A_{x+1}$ 行的一个连续段的情况。

找出这两行中间 $T$ 最小的行 $r$，显然如果存在一条路径，那么路径上一定有一列 $c$ 满足 $H_c<T_r$。此时，我们发现，只使用第 $c$ 列就足以完成。

现在找出所有满足条件的 $c$，显然只要从 $A_x$ 行走到任意一个 $c$ 就可以走到 $A_{x+1}$ 行。

在 $[L,R]$ 的限制下，需要考虑最小和最大的 $c$。如果 $[L,R]$ 在最小值和最大值中间，那么此时那两个点已经同属一个连续段，可以让它们相遇了。

维护一个可能的位置集合。一开始将所有 $H_i<T_0$ 的位置放入集合，然后对 $x$ 做扫描线。每当集合中有一个位置不合法，就将其永久移除，之后也不用把它加回来。利用“如果 $H_i\ge H_j$，则 $P_i\subseteq P_j$”的性质可以证明其正确性。

用线段树维护每个位置要走到当前行的前提下 $[L,R]$ 的限制，每次修改的时候重构当前整个段。合并两个段的时候可以使用链表，也可以启发式合并。

这样把询问离线下来扫描线就做完了。但是题目中强制在线，所以需要用可持久化线段树维护 $[L,R]$ 的限制。

时间复杂度 $O((n+m)\log m+q)$。

```cpp
#include"obstacles.h"
#include<bits/stdc++.h>
using namespace std;
#define ll int
const ll N=200007;
ll n,m,h[N],lim[N],a[N],x[N],d[N],root[N],fa[N],L[N],R[N],bg[N],ed[N],nxt[N],pre[N];//a < h,lim
vector<int> add[N],del[N];
pair<ll,ll> operator +(const pair<ll,ll>& a,const pair<ll,ll>& b){return make_pair(min(a.first,b.first),max(a.second,b.second));}
ll getfa(ll x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
namespace P1{
#define lson (u<<1)
#define rson (u<<1|1)
	ll val[N<<2];
	void build(int u,int l,int r){
		if (l==r){val[u]=x[l];return;}
		int mid=l+r>>1;
		build(lson,l,mid);build(rson,mid+1,r);
		val[u]=max(val[lson],val[rson]);
	}
	ll query(int u,int l,int r,int L,int R){
		if (L<=l&&r<=R) return val[u];
		int mid=l+r>>1;
		if (R<=mid) return query(lson,l,mid,L,R);
		if (L>mid) return query(rson,mid+1,r,L,R);
		return max(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
	}
#undef lson
#undef rson
}
namespace SGT{
	const ll N=20000007;
	ll nV,lson[N],rson[N],mn[N],mx[N];
	void build(int& u,int l,int r){
		u=++nV;mn[u]=n+1;mx[u]=0;
		if (l==r){mn[u]=mx[u]=l;return;}
		int mid=l+r>>1;
		build(lson[u],l,mid);build(rson[u],mid+1,r);
	}
	void modify(int& u,int l,int r,int L,int R,int vl,int vr){
		int U=++nV;
		lson[U]=lson[u];rson[U]=rson[u];mn[U]=mn[u];mx[U]=mx[u];
		u=U;
		if (L<=l&&r<=R){mn[u]=min(mn[u],vl);mx[u]=max(mx[u],vr);return;}
		int mid=l+r>>1;
		if (L<=mid) modify(lson[u],l,mid,L,R,vl,vr);
		if (R>mid) modify(rson[u],mid+1,r,L,R,vl,vr);
	}
	pair<ll,ll> query(int u,int l,int r,int x){
		if (l==r) return make_pair(mn[u],mx[u]);
		int mid=l+r>>1;
		if (x<=mid) return make_pair(mn[u],mx[u])+query(lson[u],l,mid,x);
		return make_pair(mn[u],mx[u])+query(rson[u],mid+1,r,x);
	}
}
void merge(int u,int v){
	u=getfa(u);v=getfa(v);
	if (u==v) return;
	if (u>v) swap(u,v);fa[v]=u;
	R[u]=R[v];
	if (ed[u]&&bg[v]!=n+1){
		nxt[ed[u]]=bg[v];
		pre[bg[v]]=ed[u];
	}
	if (ed[v]) ed[u]=ed[v];
	if (bg[u]==n+1) bg[u]=bg[v];
}
void initialize(std::vector<int> T,std::vector<int> H){
	n=H.size();
	for (int i=1;i<=n;++i) a[i]=H[i-1];
	h[m=1]=0;
	for (int i=1;i<T.size();++i) if (T[i]>T[h[m]]) h[++m]=i;
	lim[0]=1e9;
	for (int i=1;i<m;++i){
		lim[i]=lim[i-1];
		for (int j=h[i];j<h[i+1];++j) lim[i]=min(lim[i],T[j]);
	}
	for (int i=1;i<=m;++i) h[i]=T[h[i]];
//	for (int i=1;i<=m;++i) cout<<h[i]<<' ';cout<<endl;
//	for (int i=1;i<=m;++i) cout<<lim[i]<<' ';cout<<endl;
	for (int i=1;i<=n;++i){
		L[i]=R[i]=fa[i]=i;bg[i]=n+1;ed[i]=0;
		x[i]=upper_bound(h+1,h+1+m,a[i])-h;
		if (x[i]==1){
			int l=1,r=m-1,p=m;
			while(l<=r){
				int mid=l+r>>1;
				if (lim[mid]<=a[i]) p=mid,r=mid-1;
				else l=mid+1;
			}
			d[i]=p;
			del[d[i]+1].emplace_back(i);
			bg[i]=ed[i]=i;
		}
		else add[x[i]].emplace_back(i);
	}
	P1::build(1,1,n);
	SGT::build(root[1],1,n);
	for (int i=2;i<=n;++i) if (x[i]==1&&x[i-1]==1) merge(i-1,i);
//	for (int i=1;i<=n;++i) cout<<x[i];cout<<endl;
//	for (int i=1;i<=n;++i) cout<<d[i];cout<<endl;
	for (int i=2;i<=m;++i){
//		cout<<i<<endl;
		root[i]=root[i-1];
		for (auto x:del[i]){
//			cout<<"del "<<x<<endl;
			int p=getfa(x);
			if (nxt[x]&&pre[x]){pre[nxt[x]]=pre[x];nxt[pre[x]]=nxt[x];continue;}
//			cout<<"bad"<<endl;
			if (pre[x]==0&&nxt[x]==0){
				bg[p]=n+1;ed[p]=0;
				SGT::modify(root[i],1,n,L[p],R[p],ed[p],bg[p]);
				continue;
			}
			if (nxt[x]==0) ed[p]=pre[x];
			else pre[nxt[x]]=pre[x];
			if (pre[x]==0) bg[p]=nxt[x];
			else nxt[pre[x]]=nxt[x];
			SGT::modify(root[i],1,n,L[p],R[p],ed[p],bg[p]);
		}
		for (auto p:add[i]){
			if (p!=1&&x[p-1]<=x[p]) merge(p-1,p);
			if (p!=n&&x[p+1]<=x[p]) merge(p,p+1);
		}
	}
}
bool can_reach(int L,int R,int S,int D){
	++L;++R;++S;++D;
	if (x[S]>1||x[D]>1) return 0;
	if (S>D) swap(S,D);
	ll k=P1::query(1,1,n,S,D);
	if (k>m) return 0;
	auto p=SGT::query(root[k],1,n,S)+SGT::query(root[k],1,n,D);
	return L<=p.first&&p.second<=R;
}
```

---

## 作者：_Ch1F4N_ (赞：3)

下面是 vp 时的做法，由于一些原因可能做复杂了。

首先看上去非常的奇怪，我们关注一下限制最松的一部分，也就是 $h$ 最小的若干列 $p_1,p_2,\dots,p_k$。

考虑对这些列做分治，也就是将区间 $[l,r]$ 分为 $[l,p_1),(p_1,p_2),\dots,(p_k,r]$，然后去递归这些区间内部的连边，然后再考虑区间之间的连边。

考虑区间之间的连边，注意到区间 $(p_i,p_{i+1})$ 想连边出去必须先抵达抵达列 $p_i+1$ 或者列 $p_{i+1}-1$，不妨记能抵达这些列的连通块集合为 $L,R$。

注意到区间 $(p_i,p_{i+1})$ 中的限制严格强于 $p_i,p_{i+1}$，所以如果从区间 $(p_i,p_{i+1})$ 中走出来可以走到第 $p_i,p_{i+1}$ 列的第 $j$ 行，那么必定可以从 $(p_i,0),(p_{i+1},0)$ 直接走到 $(p_i,j),(p_{i+1},j)$。

所以我们会把集合 $L,R$ 中的连通块分别与 $(p_i,0),(p_{i+1},0)$ 代表的连通块合并。

再考虑 $p_i,p_k$ 之间的连边，预处理出 $(p_i,0)$ 可以抵达的前缀中最大行 $q$，那么 $(p_i,0),(p_k,0)$ 如果满足 $\max_{j=i}^k h_j < t_p$ 就将其合并。

当递归完 $[l,r]$ 返回时，再以 $[l,p_1),(p_k,r]$ 最左边和最右边的连通块集合作为 $L,R$ 返回。 

写一发，交上去发现过不了。

你发现漏掉了 $p_1,p_k$ 分别抵达 $l,r$ 的情形，更进一步地，如果其可以抵达区间端点并且区间端点不是 $0,m-1$，那么其一定会与 $[l,p_1),(p_k,r]$ 中可以抵达区间端点的连通块在某个时刻合并，所以不妨直接在返回 $L,R$ 时直接将其中所有连通块合并一同返回。

到这里可以过掉最后一个子任务之前的所有子任务。

考虑正解，不妨把合并过程建树，然后把每个点在合并过程中**强制拐弯**的位置刻画出来。

所谓强制拐弯，就是如果 $(p_i,p_{i+1})$ 返回了两个不同的连通块 $L,R$，那么当把 $L$ 合并到 $p_i$ 上时，你发现 $L$ 内的点出来后不管向左或者向右都要经过 $p_i$，这就要给 $L$ 设置一个虚拟父亲并打上 $p_i$ 的强制拐弯标记，对于 $R$ 同理。

在处理递归完返回的 $L,R$ 时也需要类似地打标记。

查询就在由合并建立的树上在链查询标记 $\max,\min$ 即可，容易倍增做到 $O(q \log n)$。

细节比较多，可以看[代码。](http://qoj.ac/submission/1201123)

事实上，因为我的做法建出的是广义笛卡尔树所以有较多的分类讨论，但注意到相同值并不需要特殊处理，所以可以直接建一般笛卡尔树（也就是每次随意取出一个最小值位置去分治）减少很多细节。

下面贴出一般笛卡尔树写法的代码：

```cpp
#include<bits/stdc++.h>
#include "obstacles.h"
#define fir first
#define sec second
using namespace std;
const int maxn = 6e5+114;
int t[maxn],h[maxn],n,m;
int fa[maxn];
int mx[maxn<<2];
pair<int,int> mi[maxn<<2];
void build(int cur,int lt,int rt){
    if(lt==rt){
        mi[cur]=make_pair(h[lt],lt);
        mx[cur]=h[lt];
        return ;
    }
    int mid=(lt+rt)>>1;
    build(cur<<1,lt,mid),build(cur<<1|1,mid+1,rt);
    mi[cur]=min(mi[cur<<1],mi[cur<<1|1]);
    mx[cur]=max(mx[cur<<1],mx[cur<<1|1]);
}
pair<int,int> askmi(int cur,int lt,int rt,int l,int r){
    if(rt<l||r<lt) return make_pair(1e9+114,-1);
    if(l<=lt&&rt<=r) return mi[cur];
    int mid=(lt+rt)>>1;
    return min(askmi(cur<<1,lt,mid,l,r),askmi(cur<<1|1,mid+1,rt,l,r));
}
int askmx(int cur,int lt,int rt,int l,int r){
    if(rt<l|r<lt) return -1;
    if(l<=lt&&rt<=r) return mx[cur];
    int mid=(lt+rt)>>1;
    return max(askmx(cur<<1,lt,mid,l,r),askmx(cur<<1|1,mid+1,rt,l,r));
}
int find(int u){
    return fa[u]=(fa[u]==u?u:find(fa[u]));
}
int premi[maxn],premx[maxn];
vector<int> E[maxn<<1];
int val[maxn<<1];
int jump[maxn][20],Mx[maxn][20],Mi[maxn][20];
int dep[maxn],lg[maxn];
int tot;
void dfs(int u,int lst){
    if(lst==-1) dep[u]=1;
    else dep[u]=dep[lst]+1;
    jump[u][0]=lst;
    Mx[u][0]=(val[u]==-1?-1e9:val[u]);
    Mi[u][0]=(val[u]==-1?1e9:val[u]);
    for(int i=1;i<20;i++){
        if(jump[u][i-1]==-1){
            jump[u][i]=-1;
            Mx[u][i]=Mx[u][i-1];
            Mi[u][i-1]=Mi[u][i-1];
        }
        else{
            jump[u][i]=jump[jump[u][i-1]][i-1];
            Mx[u][i]=max(Mx[u][i-1],Mx[jump[u][i-1]][i-1]);
            Mi[u][i]=min(Mi[u][i-1],Mi[jump[u][i-1]][i-1]);
        }
    }
    for(int nxt:E[u]){
        dfs(nxt,u);
    }
}
pair<int,int> solve(int l,int r){
    //返回可以靠到最左边/右边的连通块
    int pos=askmi(1,0,m-1,l,r).sec;
    int v=h[pos];
    if(v>=t[0]) return make_pair(-1,-1);
    pair<int,int> res=make_pair(-1,-1);
    if(pos!=l){
        pair<int,int> son=solve(l,pos-1);
        bool flag=false;
        if(son.fir!=-1&&son.sec!=-1&&find(son.fir)==find(son.sec)) flag=true;
        if(son.fir!=-1) res.fir=find(son.fir);
        if(son.sec!=-1){
            if(find(son.sec)!=find(pos)){
                if(flag==false){
                    tot++;
                    E[tot].push_back(find(son.sec));
                    E[find(pos)].push_back(tot);
                    fa[find(son.sec)]=fa[tot]=find(pos);  
                    val[tot]=pos;
                }else{
                    tot++;
                    E[tot].push_back(find(son.sec));
                    E[tot].push_back(find(pos));
                    fa[find(son.sec)]=fa[find(pos)]=fa[tot]=tot;
                    val[tot]=-1;
                }
            }
        }
    }else res.fir=find(pos);
    if(pos!=r){
        pair<int,int> son=solve(pos+1,r);
        bool flag=false;
        if(son.fir!=-1&&son.sec!=-1&&find(son.fir)==find(son.sec)) flag=true;
        if(son.fir!=-1){
            if(find(son.fir)!=find(pos)){
                if(flag==false){
                    tot++;
                    E[tot].push_back(find(son.fir));
                    E[find(pos)].push_back(tot);
                    fa[find(son.fir)]=fa[tot]=find(pos);   
                    val[tot]=pos;                 
                }else{
                    tot++;
                    E[tot].push_back(find(son.fir));
                    E[tot].push_back(find(pos));
                    fa[find(son.fir)]=fa[find(pos)]=fa[tot]=tot;
                    val[tot]=-1;
                }
            }
        }
        if(son.sec!=-1) res.sec=find(son.sec);
    }else res.sec=find(pos);
    int L=0,R=n;
    while(L+1<R){
        int mid=(L+R)>>1;
        if(premi[mid]>v) L=mid;
        else R=mid;
    }
    int edge=premx[L];
    if(askmx(1,0,m-1,l,pos)<edge){
        if(res.fir==-1) res.fir=find(pos);
        else if(l!=0){
            if(find(res.fir)!=find(pos)){
                tot++;
                E[tot].push_back(find(res.fir));
                val[tot]=l-1;
                tot++;
                E[tot].push_back(tot-1);
                E[tot].push_back(find(pos));
                fa[find(res.fir)]=fa[tot-1]=fa[find(pos)]=fa[tot]=tot;
                val[tot]=-1;
            }
        }
    }
    if(askmx(1,0,m-1,pos,r)<edge){
        if(res.sec==-1) res.sec=find(pos);
        else if(r!=m-1){
            if(find(res.sec)!=find(pos)){
                tot++;
                E[tot].push_back(find(res.sec));
                val[tot]=r+1;
                tot++;
                E[tot].push_back(tot-1);
                E[tot].push_back(find(pos));
                fa[find(res.sec)]=fa[tot-1]=fa[find(pos)]=fa[tot]=tot;
                val[tot]=-1;
            }
        }
    }
    return res;
}
void initialize(std::vector<int> T, std::vector<int> H){
    n=T.size(),m=H.size();
    for(int i=0;i<n;i++) t[i]=T[i];
    for(int i=0;i<m;i++) h[i]=H[i];
    for(int i=0;i<m;i++) fa[i]=i;
    build(1,0,m-1);
    for(int i=0;i<m;i++) val[i]=i;
    tot=m-1;
    premi[0]=premx[0]=t[0];
    for(int i=1;i<n;i++){
        premi[i]=min(premi[i-1],t[i]);
        premx[i]=max(premx[i-1],t[i]);
    }
    lg[1]=0;
    for(int i=2;i<maxn;i++) lg[i]=lg[i>>1]+1;
    solve(0,m-1);
    for(int i=0;i<=tot;i++){
        if(find(i)==i) dfs(i,-1);
    }    
}
bool can_reach(int L, int R, int S, int D){
    if(find(S)!=find(D)) return false;
    int mx=-1e9,mi=1e9;
    if(dep[S]<dep[D]) swap(S,D);
    while(dep[S]>dep[D]){
        mx=max(mx,Mx[S][lg[dep[S]-dep[D]]]);
        mi=min(mi,Mi[S][lg[dep[S]-dep[D]]]);
        S=jump[S][lg[dep[S]-dep[D]]];
    }
    if(S!=D){
        for(int i=19;i>=0;i--){
            if(jump[S][i]!=jump[D][i]){
                mx=max(mx,max(Mx[S][i],Mx[D][i]));
                mi=min(mi,min(Mi[S][i],Mi[D][i]));
                S=jump[S][i],D=jump[D][i];
            }
        }
        mx=max(mx,max(Mx[S][0],Mx[D][0]));
        mi=min(mi,min(Mi[S][0],Mi[D][0]));
        S=jump[S][0],D=jump[D][0];
    }
    mx=max(mx,Mx[S][0]);
    mi=min(mi,Mi[S][0]);
    if(mx>R||mi<L) return false;
    return true;
}
```

---

