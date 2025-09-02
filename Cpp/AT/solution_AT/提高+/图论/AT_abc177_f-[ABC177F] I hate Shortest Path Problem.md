# [ABC177F] I hate Shortest Path Problem

## 题目描述

### 题目大意

有一个 $(H+1)$ 行 $W$ 列的矩阵，你每步可以在矩阵中向右或向下移动一个格子。其中，在第 $i\,(1 \le i \le H)$ 行中，你无法从左至右第 $A_i$ 至 $B_i$ 个格子向下走。对于每一个 $k\,(1 \le k \le H)$，求出你从第 $1$ 行的任意一个格子出发移动到第 $(k+1)$ 行的最少步数，若无法移动到则输出 `-1`。

数据范围：$1 \le H,W \le 2\times 10^5$，$1 \le A_i \le B_i \le W$。

## 样例 #1

### 输入

```
4 4
2 4
1 1
2 3
2 4```

### 输出

```
1
3
6
-1```

# 题解

## 作者：rizynvu (赞：4)

[我的博客](https://www.cnblogs.com/rizynvu/p/18292750)。

考虑按题目所述的进行 DP。  
设计状态 $f_{i, j}$ 代表强制要求 $(i, j)$ 要走向 $(i + 1, j)$ 最小的横坐标之差，这是因为对应的纵坐标之差是确定的。

对于转移，考虑到对于 $j\not \in [a_i, b_i]$，直接从上面转移下来即可，即 $f_{i, j}\leftarrow f_{i - 1, j}$。  
对于 $j\in [a_i, b_i]$，不能往下走，就只能考虑往右走到到 $b_i + 1$ 处，即 $f_{i, b_{i} + 1}\leftarrow f_{i - 1, j} + b_{i} + 1 - j$，同时 $f_{i, j}$ 因为不能走就变为 $+\infty$。

需要用个数据结构优化一下。  
考虑用一个 *map* 存在当前 $f_{i, j}\not = +\infty$ 的 $j$ 和 $f_{i, j}$。  
那么对于第一种转移什么都不会发生，对于第二种转移，直接暴力删除区间内的点向 $f_{i, b_i + 1}$ 更新即可。  
同时需要一个 *multiset* 存下不为 $+ \infty$ 的 $f_{i, j}$ 以查找最小值。

时间复杂度分析考虑均摊，最多删去 $H + W$ 个点，复杂度 $\mathcal{O}((H + W)\log W)$。

```cpp
#include<bits/stdc++.h>
int main() {
   int H, W;
   scanf("%d%d", &H, &W);
   std::map<int, int> S;
   std::multiset<int> D;
   for (int i = 1; i <= W; i++) S[i] = 0, D.insert(0);
   for (int i = 1; i <= H; i++) {
      int a, b; scanf("%d%d", &a, &b);
      auto it = S.lower_bound(a);
      int mn = 1e9, w;
      while (it != S.end() && (w = (*it).first) <= b) {
         mn = std::min(mn, b + 1 - w + (*it).second);
         D.erase(D.find((*it).second)), S.erase(it++);
      }
      if (b < W && mn < (int)1e9) {
         if (S.find(b + 1) != S.end()) {
            D.erase(D.find(S[b + 1]));
            D.insert(S[b + 1] = std::min(S[b + 1], mn));
         } else {
            D.insert(S[b + 1] = mn);
         }
      }
      printf("%d\n", D.empty() ? -1 : ((*D.begin()) + i));
   } 
   return 0;
}
```

---

## 作者：tyr_04 (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_abc177_f)

纯线段树做法，五发场切。~~但三发离场（悲~~ 

## 题意

你在一个 $h$ 行，$w$ 列的矩阵中，每次可以向右或向下走一格，其中第 $h$ 行的第 $a_{i}$ 到 $b_{i}$ 列不能向下走（即只能向右走），问从第一行的任意列出发走到 $2$ 到 $h+1$ 行的最小步数。

## 思路

首先有个显然的贪心，不管你从哪一列出发，如果能向下走一定优先向下走，这样走到每行的步数一定最小，且能到达的行一定最多。

那么从每一列出发一定优先向下，如果遇到了不能向下走的情况，则向右走直到能向下走。

设当前为第 $i$ 行，$now_{j}$ 目前到达第 $j$ 列的最小步数，对于 $a_{i}$ 和 $b_{i}$，明显有 $now_{b_{i}+1} = \min^{b_{i}+1}_{k=a_{i}} now_{k}+b_{i}-k+1$，且 $now_{a_{i} \dots b_{i}}$ 均赋为极大值。

考虑用线段树快速维护最小值，由于每个位置的步数和列数都对最小值有影响，线段树中除了维护步数的最小值外还要维护步数与当前列走第到 $w$ 列的步数和的最小值。

定义 $minn$ 和 $minx$ 表示这一行中到达任意列的最小值与任意列中向右走到 $w$ 列时的最小值。

对于每一行的限制 $a_{i}$ 与 $b_{i}$，仅需查询区间 $a_{i}$ 到 $b_{i}$ 最小的 $minx$ 记为 $p$；再修改区间 $a_{i}$ 到 $b_{i}$ 的 $minn$ 和 $minx$ 赋为极大值；然后单点修改 $b_{i}+1$ 的 $minn=\min(p-(w-b_{i}-1),minn)$，$minx=minn+(w-b_{i})$；最后输出根节点的 $minn$ 就行了；如果根节点的 $minn$ 为极大值，则从此行往下的所有行均输出 $-1$。

其中，第 $i$ 列的初始 $minn$ 为 $0$，第 $i$ 列的初始 $minx$ 为 $(w-i)$。

时间复杂度：$O((h+w) \log_{2} w)$

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int h,w,ans=0;
struct node
{
	int a,b;
}s[800005];
struct nide
{
	int l,r,tag,minn,minx;
}t[3200005];
void pushup(int x)
{
	t[x].minn=min(t[x*2].minn,t[x*2+1].minn);
	t[x].minx=min(t[x*2].minx,t[x*2+1].minx);
	return;
}
void pushdown(int x)
{
	t[x*2].tag+=t[x].tag;
	t[x*2].minn+=t[x].tag;
	t[x*2].minx+=t[x].tag;
	t[x*2+1].tag+=t[x].tag;
	t[x*2+1].minn+=t[x].tag;
	t[x*2+1].minx+=t[x].tag;
	t[x].tag=0;
	return;
}
void build(int x,int l,int r)
{
	if(l==r)
	{
		t[x].minn=0;
		t[x].minx=(w-l);
		t[x].tag=0;
		t[x].l=l;
		t[x].r=r;
		return;
	}
	int mid=(l+r)/2;
	t[x].l=l;
	t[x].r=r;
	build(x*2,l,mid);
	build(x*2+1,mid+1,r);
	pushup(x);
	return;
}
void become1(int x,int l,int r,int kl,int kr,int k)
{
	pushdown(x);
	if(kl<=l&&r<=kr)
	{
		t[x].tag+=k;
		t[x].minn+=k;
		t[x].minx+=k;
		return;
	}
	else if(l>kr||r<kl)
	{
		return;
	}
	else
	{
		int mid=(l+r)/2;
		become1(x*2,l,mid,kl,kr,k);
		become1(x*2+1,mid+1,r,kl,kr,k);
	}
	pushup(x);
	return;
}
void become2(int x,int l,int r,int k,int wz)
{
	pushdown(x);
	if(l>wz||r<wz)
	{
		return;
	}
	if(l==r)
	{
		t[x].minn=min(t[x].minn,k);
		t[x].minx=t[x].minn+(w-l);
		return;
	}
	else
	{
		int mid=(l+r)/2;
		become2(x*2,l,mid,k,wz);
		become2(x*2+1,mid+1,r,k,wz);
	}
	pushup(x);
	return;
}
int ask(int x,int l,int r,int kl,int kr)
{
	pushdown(x);
	if(kl<=l&&r<=kr)
	{
		return t[x].minx;
	}
	else if(l>kr||r<kl)
	{
		return 1e15;
	}
	else
	{
		int mid=(l+r)/2;
		return min(ask(x*2,l,mid,kl,kr),ask(x*2+1,mid+1,r,kl,kr));
	}
}
signed main()
{
	cin>>h>>w;
	for(int i=1;i<=h;i++)
	{
		cin>>s[i].a>>s[i].b;
	}
	build(1,1,w);
	bool z=0;
	for(int i=1;i<=h;i++)
	{
		if(z==1)
		{
			cout<<-1<<'\n';
			continue;
		}
		int nmin=ask(1,1,w,s[i].a,s[i].b);
		become1(1,1,w,s[i].a,s[i].b,h*w+1);
		if(s[i].b+1<=w)
		{
			become2(1,1,w,nmin-(w-s[i].b-1),s[i].b+1);
		}
		if(t[1].minn>h*w)
		{
			z=1;
			cout<<-1<<'\n';
		}
		else if(t[1].minn<=h*w)
		{
			cout<<t[1].minn+i<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：CarroT1212 (赞：2)

笑死，寒假写了这题的翻译，现在才切掉。

### 解法分析

先从直接设 $dp_{i,j}$ 为走到第 $i$ 行第 $j$ 列时的最小步数开始，则显然有 $j\in[A_{i-1},B_{i-1}]$ 时 $dp_{i,j}=dp_{i,j-1}$，否则 $dp_{i,j}=\min(dp_{i-1,j},dp_{i,j-1})$。

然后你欣喜地发现这玩意压根没法优化，考虑回炉重造。

注意到题目仅要求第 $i$ 行的 $\min\{dp_{i,j}\}$。这个向右走的情况极为烦人，但是仔细一想，都向右走了，那走完之后这个步数还能影响到 $\min\{dp_{i,j}\}$ 吗？也就是说，如果走的时候某一行取到了最小值，那么上一步一定是向下走的。在能向下走的情况下，向下一定比向右更容易影响到答案，而仅仅在遇到不能向下走的 $[A_i,B_i]$ 时，才需要向右走出这个区间再立即往下走。

所以限制 $dp_{i,j}$ 一定是向下走时取到的，则有

$$
dp_{i,j}=\begin{cases} \min\{dp_{i-1,k}+B_{i-1}+2-k\},k\in[A_{i-1},B_{i-1}+1]&j=B_{i-1}+1\\dp_{i-1,j}+1&j\notin [A_{i-1},B_{i-1}+1]\\+∞&j\in[A_{i-1},B_{i-1}]\end{cases}
$$

线段树维护 $dp_{i,j}$ 和 $dp_{i,j}-j$ 的最小值即可解决。

### 代码

```cpp
ll h,w,a[N],b[N],t[N<<3][2],tg[N<<3];
void pdn(ll p,ll l,ll r,ll mid) {
	if (tg[p]) {
		t[p<<1][0]+=tg[p],t[p<<1][1]+=tg[p];
		t[p<<1|1][0]+=tg[p],t[p<<1|1][1]+=tg[p];
		tg[p<<1]+=tg[p],tg[p<<1|1]+=tg[p],tg[p]=0;
	}
}
void pup(ll p) {
	t[p][0]=min(t[p<<1][0],t[p<<1|1][0]);
	t[p][1]=min(t[p<<1][1],t[p<<1|1][1]);
}
void bui(ll p,ll l,ll r) {
	if (l==r) return t[p][0]=-l,t[p][1]=0,vo;
	ll mid=l+r>>1;
	bui(p<<1,l,mid),bui(p<<1|1,mid+1,r);
	pup(p);
}
void add(ll p,ll l,ll r,ll x,ll y,ll z) {
	if (x>y) return;
	if (x<=l&&r<=y) return t[p][0]+=z,t[p][1]+=z,tg[p]+=z,vo;
	ll mid=l+r>>1;
	pdn(p,l,r,mid);
	if (x<=mid) add(p<<1,l,mid,x,y,z);
	if (y>mid) add(p<<1|1,mid+1,r,x,y,z);
	pup(p);
}
void chg(ll p,ll l,ll r,ll x,ll y) {
	if (x>w) return;
	if (l==r) return t[p][0]=min(t[p][0],y-l),t[p][1]=min(t[p][1],y),vo;
	ll mid=l+r>>1;
	pdn(p,l,r,mid);
	if (x<=mid) chg(p<<1,l,mid,x,y);
	else chg(p<<1|1,mid+1,r,x,y);
	pup(p);
}
ll que(ll p,ll l,ll r,ll x,ll y) {
	if (x<=l&&r<=y) return t[p][0];
	ll mid=l+r>>1,ret=1e18;
	pdn(p,l,r,mid);
	if (x<=mid) ret=min(ret,que(p<<1,l,mid,x,y));
	if (y>mid) ret=min(ret,que(p<<1|1,mid+1,r,x,y));
	return ret;
}
int main() {
	memset(t,63,sizeof(t));
	scanf("%d%d",&h,&w);
	bui(1,1,w);
	for (int i=1;i<=h;i++) {
		scanf("%d%d",&a[i],&b[i]);
		add(1,1,w,1,a[i]-1,1),add(1,1,w,b[i]+1,w,1);
		chg(1,1,w,b[i]+1,que(1,1,w,a[i],b[i])+b[i]+2);
		add(1,1,w,a[i],b[i],1e13);
		printf("%lld\n",t[1][1]>1e12?-1:t[1][1]);
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：1)

设 $f_{i,j}$ 为从第 $1$ 行到 $(i + 1, j)$ 的最短路。

因为我们并不关心最后到达的是哪一个格子，于是强制 $f_{i,j}$ 为必须从 $(i, j)$ 往下走一格到 $(i + 1, j)$ 的最短路。

有转移：

$$f_{i,r+1} \gets f_{i-1,j} + r + 2 - j, j \in [l, r]$$

$$f_{i,j} \gets f_{i-1,j} + 1, j \notin [l, r]$$

$[l, r]$ 表示第 $i$ 行被 ban 掉的区间。

这个东西显然能用线段树优化。具体地，枚举到第 $i$ 行，线段树每个叶子结点 $[j,j]$ 存 $f_{i,j} - j$ 的最小值。对于第一种转移，区间查最小值，单点修；对于第二种转移，区间加 $1$。注意到 $j \in [l,r], f_{i,j}$ 不合法，把它们加上一个 $+\infty$ 即可。

时间复杂度线性对数。

[code](https://atcoder.jp/contests/abc177/submissions/41307830)

---

## 作者：myster1ous (赞：0)

## Statement

给定一个 $n + 1$ 行 $m$ 列的网格图，你在网格上可以向下走或者向右走，第 $i (1 \leq i \leq n)$ 行的第 $a_i$ 到 $b_i$ 列不能向下走。

求你从第一行的任何一个格子走到第 $k (2 \leq k \leq n + 1)$ 行任何一个格子最少需要多少步？

网格图的长宽可达 $10^5$，所以我们必须用 $\mathcal{O}(n \log n)$ 复杂度（或更低）的算法。

## Solution

首先，不难发现如果只能从 $(1, 1)$ 开始的话，那么就只需要模拟一下，不断执行下面两个步骤：

- 如果能向下走，则向下，记录此时的步数即为答案。
- 否则，不断向右走直到能向下走。 

这个模拟的步骤可以做到 $\mathcal{O}(n)$ 求出所有答案。

但是本题可以从第一行的任何一个格子开始，并且不能对于每一个格子都算一遍这样是 $\mathcal{O}(n^2)$，所以我们可以考虑同时模拟 $m$ 组。

我们定义 $f_{i, j}$ 表示走到第 $i$ 行第 $j$ 列最少需要的步数，首先可以把第一维度压掉变成 $f_j$，然后再定义 $s$ 表示目前最左边还能走到的格子，初始 $s = 1$。

然后判断当前不能向下走的区间：
- 如果当前不能向下走的区间包含 $s$, 那么 $s$ 就被赋值为区间的右端点加一（对应上面那个模拟的向右走的步骤），然后将剩下的 $f_j$ 分别自增（对应上面那个向下走的步骤）。
- 如果当前不能向下走的区间在 $s$ 左边，那么这完全不会限制任何行动因为 $s$ 左边的点都是不可达的，所以直接将 $f_j$ 自增即可。
- 如果当前不能向下走的区间在 $s$ 右边，那么在这个区间的左、右边的点不会被限制，$f_j$ 自增即可，在区间内的点由于不能直接下来需要从 $a_i - 1$ 点下来然后再向右走，所以将 $f_{a_i}$ 到 $f_{b_i}$ 设置为以 $f_{a_i - 1}$，公差为 $1$ 的等差数列即可。

形式化的讲：
- 如果 $s \in [a_i, b_i]$，那么 $s \gets b_i + 1, (s \leq j \leq m)f_j \gets f_j + 1$。
- 如果 $b_i < s$，那么 $(s \leq j \leq m)f_j \gets f_j + 1$。
- 如果 $a_i > s$，那么 $(a_i \leq j \leq b_i)f_j \gets f_{a_i - 1} + j - a_i + 1,(\text{other }j)f_j \gets f_j + 1$

那么如果要 $\mathcal{O}(n \log n)$ 完成上面这些操作，不难想到线段树，对于每个节点维护两个懒标记，`addtag` 和 `settag`，注意如果有 `settag` 的话就没有 `addtag`，反之亦然，然后就没有什么细节了，代码如下：

## Code

```cpp
// LUOGU_RID: 194743384
#include <iostream>
#define int long long

struct sequence {
	int frontx, distan;
	sequence(int a=0, int b=0): frontx(a), distan(b) {}
	bool operator==(const sequence& oth) const& {
		if (frontx != oth.frontx) return false;
		return distan == oth.distan;
	}	
	bool operator!=(const sequence& oth) const& {
		if (frontx != oth.frontx) return true;
		return distan != oth.distan;
	}	
};

const int maxn = 200010;
const int infinity = 1145141919810ll;
const sequence notag(infinity, infinity); 

int n, m;
int a[maxn], b[maxn];

struct segmentree {
	segmentree *son[2];
	int l, r, mid, val, addtag;
	sequence settag; 

	segmentree(int L, int R) {
		l = L, r = R, mid = (l + r) / 2;
		son[0] = son[1] = NULL;
		val = addtag = 0;
		settag = notag;
		if (l != r) {
			son[0] = new segmentree(L, mid);
			son[1] = new segmentree(mid + 1, R);
		}
	}

	void doadd(int add) {
		if (settag == notag) addtag += add;
		else settag.frontx += add;
		val += add;
	}

	void doset(sequence seq) {
		addtag = 0;
		settag = seq;
		val = std::min(seq.frontx, seq.frontx + seq.distan * (r - l));
	}

	void pushdown() {
		if (addtag) {
			son[0]->doadd(addtag);
			son[1]->doadd(addtag);
			addtag = 0;
		} else if (settag != notag) {
			son[0]->doset(settag);
			son[1]->doset(sequence(settag.frontx + settag.distan * (mid - l + 1), settag.distan));
			settag = notag;
		}
	}

	int query(int L, int R) {
		if (L <= l && r <= R) {
			return val; 
		} else {
			int ans = infinity;
			pushdown();
			if (L <= mid) ans = std::min(ans, son[0]->query(L, R));
			if (mid < R ) ans = std::min(ans, son[1]->query(L, R));
			return ans;
		}
	}

	void modify(int L, int R, int V) {
		if (L > R) return;
		// std::cout << "Modify " << l << ", "	<< r << ": " << L << ", " << R << ", " << V << std::endl; 
		if (L <= l && r <= R) {
			doadd(V);
		} else {
			pushdown();
			if (L <= mid) son[0]->modify(L, R, V);
			if (mid < R ) son[1]->modify(L, R, V);
			val = std::min(son[0]->val, son[1]->val); 
		}
	}

	void setsequence(int L, int R, sequence S) {
		if (L > R) return;
		// std::cout << "Set Sequence " << L << ", " << R << ", (" << S.frontx << " " << S.distan << ")" << std::endl; 
		if (L <= l && r <= R) {
			doset(sequence(S.frontx + S.distan * (l - L), S.distan));
		} else {
			pushdown();
			if (L <= mid) son[0]->setsequence(L, R, S);
			if (mid < R ) son[1]->setsequence(L, R, S);
			val = std::min(son[0]->val, son[1]->val); 
		}
	}

	void printout(std::string tab = "") {
		std::cout << tab << "Segmentree(" << l << ", " << r << ", " << addtag << ", " << val;
		if (settag != notag && l != r) std::cout << ", [" << settag.frontx << ", " << settag.distan << "]";
		std::cout << ")" << std::endl;
		if (son[0]) son[0]->printout(tab + "  ");
		if (son[1]) son[1]->printout(tab + "  ");
	}
} *tree;

signed main() {
	// freopen("input.in", "r", stdin);
	// freopen("output.out", "w", stdout);
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) 
		std::cin >> a[i] >> b[i];
	tree = new segmentree(1, m);
	int start = 1;
	for (int i = 1; i <= n; i++) {
		if (start > m) {
			std::cout << "-1\n";
			continue;
		}
		// std::cout << "Aliving blocks: [" << start << ", " << m << "]\n";
		// std::cout << "[" << a[i] << " " << b[i] << "] are blocked in this layer\n";
		// tree->printout();
		if (a[i] <= start && start <= b[i]) {
			start = b[i] + 1;
			tree->modify(start, m, 1);
		} else if (a[i] > start) {
			tree->modify(b[i] + 1, m, 1);
			tree->modify(start, a[i] - 1, 1);
			tree->setsequence(a[i], b[i], sequence(tree->query(a[i] - 1, a[i] - 1) + 1, 1));
		} else tree->modify(start, m, 1);
		if (start > m) std::cout << "-1\n";
		else std::cout << tree->query(start, m) << "\n";
	}
	return 0;
} 
```

---

