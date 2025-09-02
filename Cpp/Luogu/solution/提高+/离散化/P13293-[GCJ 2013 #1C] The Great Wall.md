# [GCJ 2013 #1C] The Great Wall

## 题目描述

你正在研究中国长城的历史。长城是中国人为防御来自北方的军事入侵而修建的。为了简化问题，我们假设长城从东边的正无穷一直延伸到西边的负无穷。由于需要覆盖的距离太长，长城并不是一次性建成的。本题假设修建者采用了一种“被动应对”的策略：每当某段边境被成功攻破，长城就会在该段加高到足以抵御相同强度攻击的高度。

中国北部边境经常遭到游牧部落的进攻。为简化问题，我们假设每个部落在某个区间内以强度 $S$ 发起攻击。要抵御这次攻击，长城在该区间上必须处处高度不低于 $S$。只要有哪怕一小段低于 $S$，攻击就会在那里突破并成功。注意，即使攻击成功，也不会损坏长城。每次攻击结束后，所有被攻击且高度低于 $S$ 的长城段都会被加高到 $S$——也就是说，长城会以最小的方式加固到足以抵御本次攻击的高度。需要注意的是，如果在同一天有多次攻击，这些攻击都在当天结束后统一加固，且加固到能同时抵御所有当天攻击的最低高度。

由于游牧部落是游牧的，他们不一定只进攻一次。实际上，他们会不断东移或西移，并定期进攻长城。为简化问题，假设他们以恒定速度移动，并以恒定时间间隔发起攻击；此外，假设同一部落每次进攻的强度变化也是恒定的（可能因消耗而减弱，也可能因经验而增强）。

假设最初（公元前 250 年）长城尚未修建（即任意位置高度为 0），并给出所有游牧部落的完整攻击描述，请你求出有多少次攻击是成功的。


## 说明/提示

**样例说明**

在第一个样例中，第一个部落攻击三次：第0天攻击 $[0,2]$，强度为 $10$，第2天攻击 $[3,5]$，强度为 $8$，第4天攻击 $[6,8]$，强度为 $6$；这三次都成功。然后第二个部落攻击三次，每次强度为 $8$——第10天攻击 $[2,3]$（例如在 $2.5$ 处，长城高度仍为 $0$，所以成功），第17天攻击 $[4,5]$（失败，因为 $[3,5]$ 区间长城已经加高到 $8$），第24天攻击 $[6,7]$（成功，因为那里长城高度只有 $6$）。

在第二个样例中，有三个部落，攻击交错进行。顺序如下：

- 第0天，部落2攻击 $[0,1]$，高度 $7$，成功。
- 第1天，部落1攻击 $[0,5]$，高度 $10$，部落2攻击 $[2,3]$，高度 $9$。由于是同一天，这两次都成功（加固是在所有攻击结束后才进行的）。
- 第2天，部落2攻击 $[4,5]$，高度 $11$，成功（那里的长城高度原本为 $10$）。
- 第3天，部落1攻击 $[8,13]$，高度 $10$，成功。同时部落3攻击 $[0,5]$，高度 $1$，失败（该区间长城已有高度 $10$ 和 $11$）。
- 第4天，部落3攻击 $[4,9]$，高度 $1$，成功（$[5,8]$ 区间没有长城）。
- 第5天，部落3攻击 $[8,13]$，高度 $1$，失败（该区间长城高度为 $10$）。

**限制条件**

- $1 \leq T \leq 20$
- $0 \leq d_i$
- $1 \leq \text{delta\_d}_i \leq 676060$
- $d_i + (n_i - 1) \times \text{delta\_d}_i \leq 676060$
- $1 \leq s_i \leq 10^6$
- $-10^5 \leq \text{delta\_s}_i \leq 10^5$
- $s_i + (n_i - 1) \times \text{delta\_s}_i \geq 1$

**小数据集（9 分，测试集 1 - 可见）**

- $1 \leq N \leq 10$
- $1 \leq n_i \leq 10$
- $-100 \leq w_i < e_i \leq 100$
- $-10 \leq \text{delta\_p}_i \leq 10$

**大数据集（28 分，测试集 2 - 隐藏）**

- $1 \leq N \leq 1000$
- $1 \leq n_i \leq 1000$
- $-10^6 \leq w_i < e_i \leq 10^6$
- $-10^5 \leq \text{delta\_p}_i \leq 10^5$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
2
2
0 3 0 2 10 2 3 -2
10 3 2 3 8 7 2 0
3
1 2 0 5 10 2 8 0
0 3 0 1 7 1 2 2
3 3 0 5 1 1 4 0```

### 输出

```
Case #1: 5
Case #2: 6```

# 题解

## 作者：osfly (赞：1)

卧槽我这个退役老人还能写出这种题。

---

我很喜欢线段树，所以我使用了线段树通过了此题。

首先先对每一个城墙的位置作为下标开一棵线段树。

题目的 $w$ 和 $e$ 到了 $\pm 10^6$ 的范围，加上移动，值域干到了 $\pm 10^8$，四倍空间直接炸了。观察到最多只有 $10^6$ 次攻击，也就只有 $2\times10^6$ 个位置，先离散化喝杯茶冷静一下。

先看看他的操作，攻击成功与区间中最小值小于攻击值等价。

那么线段树只需要支持两个操作：

1. 查询区间最小值。

2. 将区间中小于 $x$ 的数改为 $x$。

第一个操作显然，第二个操作可以维护一下区间的最大最小值。如果区间最大值比 $x$ 小就整个覆盖，最小值比 $x$ 大就直接跳过。加个懒标记能剪掉挺多枝的。这种做法似乎能被卡掉，但好像咕噜咕噜没卡，人还挺好的。

？RE 了？哦，线段树建树的时候最大下标是离散化后的值而不是 $n$。

？样例过不了？哦，发现如果 $[1,2]$ 改了，$[3,4]$ 改了，但是 $[2,3]$ 之间的 $2.5$ 还是 $0$，致敬 $2023$ 省选 D1T1。直接所有坐标乘二，然后把 $x-1$ 和 $x+1$ 两个点也一起离散化。这样就能把坐标相邻的点隔开了。

？样例还是过不了？哦，$\text{delp}_i$ 也要乘二。

？样例还是过不了？哦，同一天的攻击要等到这一天结束再建墙。把时间也离散化，对每一天都开个 `vector`，然后一天一天看，先扫一遍统计成功攻击的数量，再扫一遍对线段树操作。

？样例还是过不了？哦，两个离散化的下标搞混了。

？样例还是过不了？哦，多组数据 `vector` 忘清了。

过了！

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N=6e6+10;
const ll INF=1e16;

int n;
struct tribe
{
	int d,cs;
	ll w,e;
	int s,deld,delp,dels;
}tr[N];

ll lsh[N];
int lshcnt;
int lshd[N];
int lshdcnt;

struct seg
{
	struct node
	{
		int l,r;
		ll minn,maxn;
		ll lz;
	}t[N<<2];
	#define ls (k<<1)
	#define rs (k<<1|1)
	#define L t[k].l
	#define R t[k].r
	#define mid ((L+R)>>1)
	void pushup(int k)
	{
		t[k].minn=min(t[ls].minn,t[rs].minn);
		t[k].maxn=max(t[ls].maxn,t[rs].maxn);
	}
	void mark(int k,ll x)
	{
		t[k].lz=t[k].maxn=t[k].minn=x;
	}
	void pushdown(int k)
	{
		if(!t[k].lz) return ;
		mark(ls,t[k].lz);
		mark(rs,t[k].lz);
		t[k].lz=0;
	}
	void build(int k,int l,int r)
	{
		L=l,R=r,t[k].lz=t[k].maxn=t[k].minn=0;
		if(L==R) return ;
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(k);
	}
	void update(int k,int l,int r,ll x)
	{
		if(L>r||R<l) return ;
		if(l<=L&&R<=r)
		{
			if(t[k].minn>=x) return ;
			if(t[k].maxn<x) return mark(k,x),void();
		}
		pushdown(k);
		update(ls,l,r,x),update(rs,l,r,x);
		pushup(k);
	}
	ll query(int k,int l,int r)
	{
		if(l<=L&&R<=r) return t[k].minn;
		pushdown(k);
		ll res=INF;
		if(l<=mid) res=min(res,query(ls,l,r));
		if(r>mid) res=min(res,query(rs,l,r));
		return res;
	}
	#undef ls
	#undef rs
	#undef L
	#undef R
	#undef mid
}tree;

struct attack
{
	int l,r,d;
	ll s;
};
vector<attack> v[N];

int ans;

inline void work(int cas)
{
	scanf("%d",&n);
	
	lshcnt=lshdcnt=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%lld%lld%d%d%d%d",&tr[i].d,&tr[i].cs,&tr[i].w,&tr[i].e,&tr[i].s,&tr[i].deld,&tr[i].delp,&tr[i].dels);
		tr[i].w<<=1,tr[i].e<<=1,tr[i].delp<<=1;
		ll al=tr[i].w,ar=tr[i].e;
		int ad=tr[i].d;
		for(int j=1;j<=tr[i].cs;j++)
		{
			lsh[++lshcnt]=al,lsh[++lshcnt]=al-1,lsh[++lshcnt]=al+1;
			lsh[++lshcnt]=ar,lsh[++lshcnt]=ar-1,lsh[++lshcnt]=ar+1;
			lshd[++lshdcnt]=ad;
			al+=tr[i].delp,ar+=tr[i].delp,ad+=tr[i].deld;
		}
	}
	sort(lsh+1,lsh+1+lshcnt);
	lshcnt=unique(lsh+1,lsh+1+lshcnt)-lsh-1;
	sort(lshd+1,lshd+1+lshdcnt);
	lshdcnt=unique(lshd+1,lshd+1+lshdcnt)-lshd-1;
	for(int i=1;i<=n;i++)
	{
		ll al=tr[i].w,ar=tr[i].e;
		int as=tr[i].s,ad=tr[i].d;
		for(int j=1;j<=tr[i].cs;j++)
		{
			int rel=lower_bound(lsh+1,lsh+1+lshcnt,al)-lsh,
				rer=lower_bound(lsh+1,lsh+1+lshcnt,ar)-lsh,
				red=lower_bound(lshd+1,lshd+1+lshdcnt,ad)-lshd;
			v[red].push_back(attack{rel,rer,ad,as});
			al+=tr[i].delp,ar+=tr[i].delp,as+=tr[i].dels,ad+=tr[i].deld;
		}
	}
	ans=0;
	tree.build(1,1,lshcnt);
	for(int i=1;i<=lshdcnt;i++)
	{
		for(auto cur:v[i]) 
			if(tree.query(1,cur.l,cur.r)<cur.s) ans++;
		for(auto cur:v[i])
			if(tree.query(1,cur.l,cur.r)<cur.s) tree.update(1,cur.l,cur.r,cur.s);
		v[i].clear();
	}
	printf("Case #%d: %d\n",cas,ans);
}

int main()
{
//	freopen("ts2_input.txt","r",stdin);
	int T;scanf("%d",&T);
	for(int i=1;i<=T;i++) work(i);
	return 0;
}
```

---

