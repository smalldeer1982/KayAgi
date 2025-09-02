# Building Forest Trails

## 题目描述

There are $ n $ villages lying equidistant on a circle in the middle of a thick, impassable forest. From ancient times, it was impossible to move from one village to another, but technical progress has changed a lot. Now, there is a technology to build passable trails in the forest.

The building process consists of $ m $ events. Each event is either building a trail or querying if two villages are connected. Trails are built as straight lines connecting two villages. After a trail is built, anybody can walk along the trail from one village to another.

Moreover, if two trails cross, anybody can turn at the intersection, and if other trails leave a village you have just reached, they can also be used to walk along. So, for example, if villages are numbered $ 1 $ to $ 6 $ in the order around the circle, and there are trails $ 1 $ to $ 3 $ , $ 2 $ to $ 4 $ , and $ 4 $ to $ 6 $ , then all villages, except the $ 5 $ -th, are reachable from the $ 1 $ -st village.

Given a list of $ m $ events, for each query, find if two given villages are reachable from each other at that moment.

## 样例 #1

### 输入

```
6 9
1 1 3
1 4 6
2 3 4
1 2 4
2 1 2
2 1 3
2 1 4
2 6 1
2 5 3```

### 输出

```
011110```

## 样例 #2

### 输入

```
2 5
2 1 2
2 2 1
1 1 2
2 1 2
2 2 1```

### 输出

```
0011```

# 题解

## 作者：Yu_Jie (赞：9)

CF 官方题解做法。

不难发现一个连通块内部的连边情况不重要，我们可以将其视为一个多边形，即每个点连向下一个同连通块内的点。

断环成链，形成如下结构：

![](https://cdn.luogu.com.cn/upload/image_hosting/vzey3e58.png)

由于任意两个连通块不会相交，我们令 $h_i$ 表示点 $i$ **上方**的边的数量。如图中 $h_2=0,h_3=1,h_5=1$。显然 $\forall i\in [1,n),|h_i-h_{i+1}|\le 1$。这是一个很好的性质。

来看连边操作。设连接 $x,y$，$x<y$ 且 $x,y$ 不在同一连通块内。分两种情况：

* $h_x\neq h_y$。不妨设 $h_x>h_y$。找到 $x$ 右边第一个满足 $h_p<h_x$ 的点 $p$，则 $x$ 的连通块必“包含”于 $p$ 的连通块中（如上图 $E$ 与 $H$ 的关系）。由于 $p\le y$，所以可以将 $x$ 与 $p$ 的连通块合并。

* $h_x=h_y$。依旧找到 $p$，若 $p<y$，则依旧合并；否则说明此时 $x,y$ 的连边不会与其他边有交，直接合并 $x,y$ 即可。

重复上述过程，直至 $x$ 与 $y$ 在同一连通块内。由于总合并次数为 $O(n)$，所以我们只需实现一个并查集，与一个能快速找到 $p$ 的数据结构，并支持合并的数据结构即可。

注意到相邻点的 $h$ 之差不超过 $1$，于是可以用线段树维护区间最小值，查询时线段树二分。

合并又分两种情况。用 $l_i$ 表示 $i$ 所在连通块的最左边的点，$r_i$ 同理。若 $r_x<l_y$，则两连通块没有包含关系，要加一条边，$h$ 区间 $+1$；否则有包含关系，要删一条边，加两条边，区间 $-1$。可以用线段树维护。

于是此题得解。复杂度 $O(n\log n)$。常数很小，实测 $498\text{ms}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,m;
struct dsu {
    int fa[N],l[N],r[N];
    void init() {for(int i=1;i<=n;i++) fa[i]=l[i]=r[i]=i;}
    int get(int x) {return fa[x]==x?x:fa[x]=get(fa[x]);}
    void merge(int x,int y) {
        x=get(x); y=get(y);
        if(x==y) return ;
        fa[x]=y; l[y]=min(l[x],l[y]); r[y]=max(r[x],r[y]);
    }
} s;
struct sgt {
    int mn[4*N],add[4*N];
    void pushval(int p,int v) {mn[p]+=v; add[p]+=v;}
    void pushdown(int p) {
        if(!add[p]) return ;
        pushval(p<<1,add[p]); pushval(p<<1|1,add[p]);
        add[p]=0;
    }
    void modify(int L,int R,int v,int p=1,int l=1,int r=n) {
        if(L>R) return ;
        if(L<=l&&r<=R) {pushval(p,v); return ;}
        int mid=l+r>>1; pushdown(p);
        if(L<=mid) modify(L,R,v,p<<1,l,mid);
        if(R>mid) modify(L,R,v,p<<1|1,mid+1,r);
        mn[p]=min(mn[p<<1],mn[p<<1|1]);
    }
    int query(int x,int p=1,int l=1,int r=n) {
        if(l==r) return mn[p];
        int mid=l+r>>1; pushdown(p);
        if(x<=mid) return query(x,p<<1,l,mid);
        return query(x,p<<1|1,mid+1,r);
    }
    int binaryl(int x,int v,int p=1,int l=1,int r=n) {
        if(r<=x) {
            if(mn[p]>=v) return 0;
            if(l==r) return l;
            int mid=l+r>>1; pushdown(p);
            if(mn[p<<1|1]<v) return binaryl(x,v,p<<1|1,mid+1,r);
            return binaryl(x,v,p<<1,l,mid);
        }
        int mid=l+r>>1,res=0; pushdown(p);
        if(mid+1<=x) res=binaryl(x,v,p<<1|1,mid+1,r);
        if(!res) res=binaryl(x,v,p<<1,l,mid);
        return res;
    }
    int binaryr(int x,int v,int p=1,int l=1,int r=n) {
        if(x<=l) {
            if(mn[p]>=v) return n+1;
            if(l==r) return l;
            int mid=l+r>>1; pushdown(p);
            if(mn[p<<1]<v) return binaryr(x,v,p<<1,l,mid);
            return binaryr(x,v,p<<1|1,mid+1,r);
        }
        int mid=l+r>>1,res=n+1; pushdown(p);
        if(x<=mid) res=binaryr(x,v,p<<1,l,mid);
        if(res==n+1) res=binaryr(x,v,p<<1|1,mid+1,r);
        return res;
    }
} t;
void merge(int x,int y) {
    x=s.get(x); y=s.get(y);
    if(s.r[x]<s.l[y]) t.modify(s.r[x]+1,s.l[y]-1,1);
    else t.modify(max(s.l[x],s.l[y]),min(s.r[x],s.r[y]),-1);
    s.merge(x,y);
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>m;
    s.init();
    while(m--) {
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1) {
            if(x>y) swap(x,y);
            int vx=t.query(x),vy=t.query(y);
            while(s.get(x)!=s.get(y)) {
                if(vx>vy) {merge(x,t.binaryr(x,vx)); vx--;}
                else if(vx<vy) {merge(t.binaryl(y,vy),y); vy--;}
                else {
                    int p=t.binaryr(x,vx);
                    if(p<y) {merge(x,p); vx--;}
                    else merge(x,y);
                }
            }
        }
        else cout<<(s.get(x)==s.get(y));
    }
    return 0;
}
```

---

## 作者：MoYuFang (赞：9)

本文起笔于```2021.12.07```。

[CF1578B Building Forest Trails](https://www.luogu.com.cn/problem/CF1578B)

（内容哪里无意义了？难道 LuoGu 上 UKE 就代表我算法错了？CF上通过了喂！求管理员大大给通过审核，或者指出哪里无意义，我去修改）

难度应该在紫，但很考码力，难点都在代码实现方面了，然鹅写完题后发现题解比题更难写。

知识点：并查集 + $\text{FHQ Treap}$。

不难想到用并查集来回答查询，所以问题的关键转化为每次连边时要将哪些集合合并。

具体一点，给定一条将要连的边 $(l,r)$ 不妨设 $l<r$，我们需要快速知道 $(l,r)$ 穿过哪些集合，然后将这些集合合并起来，这样就能保证时间复杂度正确。

若要判断边 $(l,r)$ 是否穿过一个集合 $S$，则需判断在使得 $S$ 连通的那组边中，是否存在一条与 $(l,r)$ 相交的边 $(tl,tr)$ （端点相交也算相交），而判断两条边是否相交则相当于判断两条边对应的区间是否有重叠的部分（在端点处重叠也算相交）。 

容易注意到，我们并不需要关心是哪些边使这个集合连通起来，因为若 $(l,r)$ 穿过集合 $S$，则不管是哪组边将 $S$ 连通起来的，$(l,r)$ 肯定会与这组边的其中之一相交。

为了方便我们求解问题，我们可以为每个集合选取一组代表边，比如对于集合 $S=\{1,4,5,8,12\}$，我们选取 $(1,4),(4,5),(5,8),(8,12)$ 作为代表边，即选取首尾相接的边，这样选取的优点是这些边只在端点处相交，省去了很多麻烦。

下一步就有点难说明了，只能上图，意思是在仅连代表边时，集合们之间的关系可以构成一颗树，相信从图中不难看出这颗树是如何构建出来的。

下图中是连边后代表边集为 $(1,10),(10,20)\ ||\ (2,9)\ ||\ (3,5)\ ||\ (6,8)\ ||\ (11,20)\ ||\ (13,18)$ 的结果，其中分划线分开了不同的集合。

建议先在草稿纸上画围成圈的 20 个点，连上边后再对照下图（我不会高级的作图工具，只能将就将就了/xk），根节点是一个为了方便代码实现而设的虚节点。

![1](https://cdn.luogu.com.cn/upload/image_hosting/jrcm9vcf.png)

我们暂且称这颗树为区间段树，树上的每一个点都代表一个连通的集合 $S$，每一个点都存有这个集合的跨度，即这个集合包含的最小节点编号 $le$ 以及最大节点编号 $ri$，称 $[le,ri]$ 为 $S$ 对应的区间， 以下用集合对应的区间指代这个集合，图中节点上的区间代表了对应集合的跨度。

这颗树之所以可以建出来，是因为集合们对应区间之间的关系要么是包含要么是相离。

然后我们用 $son(S)$ 表示集合 $S$ 在区间段树上对应的儿子们，$son(S)$ 可以用 $\text{FHQ Treap}$ 维护（注意 $\text{FHQ Treap}$ 维护的是某个集合的儿子集，不是维护区间段树，所以区间段树上每个节点都对应了一颗 $\text{FHQ Treap}$）。

现在我们思考连边会对这颗树造成什么影响？

#### 情况一

![2](https://cdn.luogu.com.cn/upload/image_hosting/ya8otthv.png)

连边 $(10,13)$，边的两端点所在集合分别为 $[1:20]$ 和 $[13:18]$，这种情况下，这两个集合在区间段树上的路径是一条从上往下的链。

此时链上的每个集合就是要合并的集合，所有集合合并到 $\text{LCA}$（$[1:20]$），而且所有集合的儿子们都要成为 $\text{LCA}$ 的儿子（要合并儿子集）。

合并后区间段树变为

![3](https://cdn.luogu.com.cn/upload/image_hosting/5dyv9a65.png)

代表边集变为 $(1,10),(10,13),(13,18),(18,20)\ ||\ (2,9)\ ||\ (3,5)\ ||\ (6,8)$。

#### 情况二

![4](https://cdn.luogu.com.cn/upload/image_hosting/sgpisufi.png)

连边 $(7,13)$，边的两端点所对应的集合分别为 $[7:7]$ 和 $[13:18]$，这种情况下，这两个集合在区间段树上的 $\text{LCA}$（$[1:20]$）不是两个集合的其中之一，且最靠近 $\text{LCA}$ 的两个集合 $S_u=[2:9],S_v=[11:20]$ 之间有空隙（$10$ 不存在）。

此时链上的每个集合都要合并到 $\text{LCA}$，而且所有集合的儿子们都要成为 $\text{LCA}$ 的儿子。

合并后区间段树变为

![5](https://cdn.luogu.com.cn/upload/image_hosting/4t4xw44h.png)

代表边集变为 $(1,2),(2,6),(6,7),(7,8),(8,9),(9,10),(10,13),(13,18),(18,20)\ ||\ (3,5)$。

#### 情况三

![6](https://cdn.luogu.com.cn/upload/image_hosting/jr0na23q.png)

连边 $(14,17)$，边的两端点所对应的集合分别为 $[14:14]$ 和 $[17:17]$，这种情况下，这两个集合在区间段树上的 $\text{LCA}$（$[13:18]$）不是两个集合的其中之一，且最靠近 $\text{LCA}$ 的两个集合 $S_u=[14:14],S_v=[17:17]$ 之间没有空隙（$15,16$ 都存在）。

此时链上的每个集合除 $\text{LCA}$ 外都要合并到一起，成为一个新的集合，而且所有参与合并的集合（不包括 $\text{LCA}$）的儿子们都要成为新集合的儿子，而且 $S_u$ 与 $S_v$ 中间连续的那一段（$[15:15],[16:16]$）也要成为新集合的儿子，最后这个新集合成为 $\text{LCA}$ 的儿子。

合并后区间线段树变为

![7](https://cdn.luogu.com.cn/upload/image_hosting/dg8jnl79.png)

代表边集变为 $(1,10),(10,20)\ ||\ (2,9)\ ||\ (3,5)\ ||\ (6,8)\ ||\ (11,20)\ ||\ (13,18)\ ||\ (14,17)$。

#### 情况四

连边 $(10,20)$，边的两端的对应的集合为同一个，即 $[1:20]$，这种情况相当于什么事都没干，区间线段树的结构也不会改变，忽略即可。

#### 代码实现

算法的描述完成了，代码实现才是最难的，好像更难讲了，这里只能简略谈一下核心思想。

每个集合的儿子集是一颗 $\text{FHQ Treap}$，因为每次在区间段树上将儿子集合合并，都是从下往上合并的，于是这可以用 $\text{FHQ Treap}$ 的分裂及合并操作以单次合并 $O(\log n)$ 完成。

对于在区间段树上求 $\text{LCA}$ 及 $S_u,S_v$，则可通过暴力跳父亲的方式求出，所以需要在每颗 $\text{FHQ Treap}$ 的根节点处记录这颗 $\text{FHQ Treap}$ 是哪个集合的儿子集合。并且在每个集合 $S$ 在其父亲的儿子集中有一个 $\text{FHQ Treap}$ 节点 $nd(S)$，我们也需要在 $S$ 上记录 $nd(S)$（之所以不直接记录这个集合 $S$ 在区间段树上的父亲是谁，是因为在修改操作中对区间段树结构的修改会改变很多父子关系）。

然后在 $\text{FHQ Treap}$ 从 $nd(S)$ 往上跳，跳到根节点，再通过根节点上记录的信息得知这颗 $\text{FHQ Treap}$ 是谁的儿子集，也就知道到了在区间段树上 $S$ 的父亲是谁，在区间段树上找某个集合的父亲以单次 $O(\log n)$ 完成。

至于如何区分情况二和情况三，即如何得知 $S_u$ 与 $S_v$ 之间是否连续，则需要在 $\text{FHQ Treap}$ 上多维护一个标记 $tag$，代表这个$\text{FHQ Treap}$ 里是否连续，于是可在 $S_u$ 与 $S_v$ 的 $\text{LCA}$ 的儿子集合中先分裂出包含 $S_u$ 和 $S_v$ 的那一颗 $\text{FHQ Treap}$，然后通过根节点的 $tag$ 快速判断，这一步也是单次 $O(\log n)$。

因为集合们最多合并 $n-1$ 次，每次合并中上述三个 $O(\log n)$ 的操作会各进行 $O(1)$ 次，所以总时间复杂度为 $O(n\log n)$。

当然，这颗 $\text{FHQ Treap}$ 实在太复杂了， 常数也会有点大，时限开 $3s$ 并不过分。

CF 上提交 $AC$ 了，但在洛谷上提交 $UKE$ 了，不知道为什么。

![](https://cdn.luogu.com.cn/upload/image_hosting/9e1znt9n.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/0wy2ce1d.png)

```6k```代码如下

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <assert.h>
#include <random> 
using namespace std;

#define re register
#define sf scanf
#define pf printf
#define nl() putchar('\n')
#define ms(x, val) memset(x, val, sizeof(x))
#define ll long long
#define _for(i, a, b) for(re int (i) = (a); (i) < (b); ++(i))
#define _rfor(i, a, b) for(re int (i) = (a); (i) <= (b); ++(i))
#define _fev(p, u) for(re int (p) = head[(u)]; (p); (p) = nex[(p)])
#define inf 0x7fffffffffffffffll
#define maxn 200005
#define maxnn (4*maxn)

template <class T>
void print(string name, T arr[], int n, int flag = 1){
	cout<<name<<":";
	_for(i, 0, n)cout<<" "<<arr[i+flag];
	cout<<endl;
}

int rdnt(){
	re int x = 0, sign = 1;
	re char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') sign = -1; c = getchar(); }
	while (c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (c ^ 48), c = getchar();
	return x * sign;
}

mt19937 engine(315);
uniform_int_distribution<ll> dstr(0, inf);
ll randnt(){ return dstr(engine); }

int pcnt = 0, pool[maxnn];
struct Union{ int nd, uf, le, ri, rt; } union_[maxn];
struct Treap{ int bl, fa, vl, sz, lc, rc, L, R; bool tag; ll pri; } treap[maxnn];
#define nd(x) union_[x].nd
#define uf(x) union_[x].uf
#define le(x) union_[x].le
#define ri(x) union_[x].ri
#define rt(x) union_[x].rt
#define bl(x) treap[x].bl
#define fa(x) treap[x].fa
#define vl(x) treap[x].vl
#define sz(x) treap[x].sz
#define lc(x) treap[x].lc
#define rc(x) treap[x].rc
#define tag(x) treap[x].tag
#define R(x) treap[x].R
#define L(x) treap[x].L
#define pri(x) treap[x].pri
int new_node(re int nn){ re int x = pool[pcnt--]; treap[x] = treap[nn]; pri(x) = randnt(); return x; }
void del_node(re int x){ pool[++pcnt] = x; }

int stk[maxn];
int find(re int u){
	re int top = 0;
	while(uf(u) > 0) stk[top++] = u, u = uf(u);
	while(top) uf(stk[--top]) = u;
	return u;
}

//void print(int x, int dep = 0){
//	_for(i, 0, dep) pf("\t");
//	if (x == 0){ pf("none\n"); return; }
//	pf("bl:%d vl:%d sz:%d tag:%d L:%d R:%d\n", bl(x), vl(x), sz(x), tag(x), L(x), R(x));
//	print(lc(x), dep+1);
//	print(rc(x), dep+1);
//}
//
//void dfs(int x, vector<int> &vec){
//	if (!x) return;
//	dfs(lc(x), vec);
//	vec.push_back(vl(x));
//	dfs(rc(x), vec);
//}

bool cmp(re int v1, re int v2){ return le(v1) < le(v2); }

void ud(re int x){
	sz(x) = 1; tag(x) = true;
	if (lc(x)){
		tag(x) &= tag(lc(x)) && R(lc(x))+1 == le(vl(x));
		sz(x) += sz(lc(x));
		L(x) = L(lc(x));
		fa(lc(x)) = x;
		bl(lc(x)) = -1;
	}
	else L(x) = le(vl(x));
	if (rc(x)){
		tag(x) &= tag(rc(x)) && ri(vl(x))+1 == L(rc(x));
		sz(x) += sz(rc(x));
		R(x) = R(rc(x));
		fa(rc(x)) = x;
		bl(rc(x)) = -1;
	}
	else R(x) = ri(vl(x));
	fa(x) = 0;
}

void split(int x, int v, int &ltr, int &rtr, bool fg){
	if (!x){ ltr = rtr = 0; return; }
	bool judge = (fg?vl(x)==v:false) || cmp(vl(x), v);
	if (judge){
		ltr = x;
		split(rc(x), v, rc(ltr), rtr, fg);
		ud(ltr);
	}
	else{
		rtr = x;
		split(lc(x), v, ltr, lc(rtr), fg);
		ud(rtr);
	}
}

int merge(int x, int y){
	if (!x || !y){ if (x+y != 0) ud(x+y); return x+y; }
	if (pri(x) <= pri(y)){
		rc(x) = merge(rc(x), y); ud(x);
		return x;
	}
	else{
		lc(y) = merge(x, lc(y)); ud(y);
		return y;
	}
}

void ins(int &x, int v){
	re int ltr = 0, rtr = 0, d = new_node(0);
	sz(d) = 1; vl(nd(v) = d) = v; tag(d) = true; L(d) = le(v); R(d) = ri(v);
	split(x, v, ltr, rtr, false);
	x = merge(merge(ltr, d), rtr);
}

void del(re int &rt, re int v){
	if (!rt) return;
	re int ltr = 0, mtr = 0, rtr = 0;
	split(rt, v, ltr, mtr, false);
	split(mtr, v, mtr, rtr, true);
	rt = merge(ltr, rtr);
	nd(v) = 0;
	if (mtr) del_node(mtr);
}

bool unite(re int u, re int v){
	uf(u) += uf(v);
	uf(v) = u;
	nd(v) = le(v) = ri(v) = 0;
	return true;
}

void ud_bl(re int x){
	if (rt(x)) bl(rt(x)) = x;
}

int get_uf_fa(re int x){
	x = nd(x);
	while(fa(x)) x = fa(x);
	return bl(x);
}

void go_up(re int x, re int v){
	while(x != v){
		re int pa = get_uf_fa(x), ltr = 0, mtr = 0, rtr = 0;
		split(rt(pa), vl(x), ltr, mtr, false);
		split(mtr, vl(x), mtr, rtr, true);
		del_node(mtr);
		rt(pa) = merge(merge(ltr, rt(x)), rtr);
		ud_bl(pa); unite(pa, x); rt(x) = 0;
		x = pa;
	}
}

//void print_tree(int x, int dep = 0){
//	_for(i, 0, dep) pf("\t");
//	pf("x:%d le:%d ri:%d fa:%d\n", x, le(x), ri(x), x==0?-1:get_uf_fa(x)); 
//	vector<int> vec;
//	dfs(rt(x), vec);
//	for(auto i : vec) print_tree(i, dep+1);
//}

int main(){
//	#ifndef ONLINE_JUDGE
//	freopen("sample.in", "r", stdin);
//	freopen("sample.out", "w", stdout);
//	#endif
	
	uf(0) = -1;
	_for(i, 1, maxnn) pool[++pcnt] = maxnn-i; 
	bl(0) = fa(0) = -1; sz(0) = vl(0) = lc(0) = rc(0) = tag(0) = L(0) = R(0) = 0;
	
	re int n = rdnt(), m = rdnt();
	le(0) = 0; ri(0) = n+1;
	_rfor(i, 1, n){
		uf(i) = -1, le(i) = ri(i) = i, rt(i) = 0;
		ins(rt(0), i);
	}
	ud_bl(0);
	
	_rfor(i, 1, m){
		re int opt = rdnt(), l = rdnt(), r = rdnt();
		if (opt == 2) pf("%d", find(l) == find(r));
		else if (opt == 1){
			if (l > r) swap(l, r);
			re int u = find(l), v = find(r), tu, tv, lca, tar, tmp = u;
			if (u == v) continue;
			
			while(!(l >= le(tmp) && r <= ri(tmp))) tmp = get_uf_fa(tmp);
			if (tmp == u || tmp == v){
				lca = tar = tmp;
				go_up(u, lca); go_up(v, lca);
			}
			else{
				re int ltr = 0, mtr = 0, rtr = 0;
				lca = tmp; tu = u; tv = v;
				while((tmp = get_uf_fa(tu)) != lca) tu = tmp;
				while((tmp = get_uf_fa(tv)) != lca) tv = tmp;
				split(rt(lca), tu, ltr, mtr, false);
				split(mtr, tv, mtr, rtr, true);
				if (tag(mtr)){
					ri(tu) = ri(tv);
					del(mtr, tu); del(mtr, tv);
					ud_bl(tu); ud_bl(tv);
					go_up(u, tu); go_up(v, tv);
					rt(tu) = merge(merge(rt(tu), mtr), rt(tv));
					rt(tv) = 0;
					unite(tu, tv); ud_bl(tu);
					re int d = new_node(0);
					sz(d) = 1; vl(nd(tu) = d) = tu; tag(d) = true; L(d) = le(tu); R(d) = ri(tu);
					rt(lca) = merge(merge(ltr, d), rtr);
				}
				else{
					tar = lca;
					rt(lca) = merge(merge(ltr, mtr), rtr);
					go_up(u, lca); go_up(v, lca);
				}
			}
			ud_bl(lca);
		}
	}

	return 0;
}

```



---

## 作者：_ICEY_ (赞：7)

[传送门](https://codeforces.com/contest/1578/problem/B)
 
这里提供一个不需要平衡树也不需要启发式合并~~但跑的比这两个都慢~~的 $O(n\log n)$ 做法。

考虑一个连通块内部的边：  
容易发现可以等效成 这个连通块中的所有点构成的凸多边形 的边。  
那么考虑连通两个点会使得若干个连通块合并。  
发现合并次数和维护凸多边形所需的边的变化次数都是 $O(n)$ 的。
那么来康康怎么维护这个东西：  
将环展开为链，对每个点维护 $pre1_i$ 为这个点所在凸多边形上的编号小于这个点的前驱（若没有则 $pre1_i=i$）。  
若这个点的后继为凸多边形上编号最小的点，那么将 $pre2_i$ 设为其后继，否则 $pre2_i=i$。  
对称地维护 $suf_1$ 和 $suf_2$。

![image](https://cdn.luogu.com.cn/upload/image_hosting/81nqz2eu.png)

事实上就是想维护出展开后的结果啦。  
然后发现添加一条边可能跨过若干条当前维护的边。  
将所有涉及到的边的端点拎出来单独处理。  
发现将这些点单独排序后相邻点在新多边形上一定有边（除了 $(最小的点, 最大的点)$ 这条边）。  
那么利用这些边更新涉及到的点的前驱后继，特判一下最小的点和最大的点之间是否有边即可。  
要怎么找到新添加的边 $(u, v)(u<v)$ 跨过的边呢？  
发现就是 $\{(i, pre1/2_i)\mid i\in[u, v]\land pre1/2_i\leqslant u\}$ 和 $\{(i, suf1/2_i)\mid i\in[u, v]\land suf1/2_i\geqslant v\}$。  
那么用一棵线段树在这个区间上若满足条件就向下递归即可。  
因为每跨过一条边就会导致两个连通块的合并，所以取出的总点数是 $O(n)$ 的。  
所以最终复杂度是 $O(n\log n)$ 的，但是带了若干常数，可能需要比较精细的实现。  
笔者通过将线段树的单点修改部分改为非递归实现通过了本题。  

另附两组方便调试的 hack 数据：

```
8 6
1 6 4
1 6 8
1 7 2
1 4 2
1 5 3
2 5 6
```
```
10 6
1 5 10
1 3 7
1 6 9
1 8 1
1 2 4
2 2 8
```

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define N 200010
#define ll long long
//#define int long long

char buf[1<<21], *p1=buf, *p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf, 1, 1<<21, stdin)), p1==p2?EOF:*p1++)
inline int read() {
	int ans=0, f=1; char c=getchar();
	while (!isdigit(c)) {if (c=='-') f=-f; c=getchar();}
	while (isdigit(c)) {ans=(ans<<3)+(ans<<1)+(c^48); c=getchar();}
	return ans*f;
}

int n, m;
int dsu[N], sta[N*8], top;
inline int find(int p) {return dsu[p]==p?p:dsu[p]=find(dsu[p]);}

struct seg1{
	#define tl(p) tl[p]
	#define tr(p) tr[p]
	int tl[N<<2], tr[N<<2], minn[N<<2], mini[N<<2], pos[N];
	inline void pushup(int p) {
		minn[p]=min(minn[p<<1], minn[p<<1|1]);
		mini[p]=minn[p]==minn[p<<1]?mini[p<<1]:mini[p<<1|1];
	}
	void build(int p, int l, int r) {
		tl(p)=l; tr(p)=r;
		if (l==r) {minn[p]=mini[p]=l; pos[l]=p; return ;}
		int mid=(l+r)>>1;
		build(p<<1, l, mid);
		build(p<<1|1, mid+1, r);
		pushup(p);
	}
	void upd(int t, int p, int val) {for (minn[p=pos[p]]=val,p>>=1; p; p>>=1) pushup(p);}
	void chkmin(int t, int p, int val) {for (p=pos[p],minn[p]=min(minn[p], val),p>>=1; p; p>>=1) pushup(p);}
	void query(int p, int l, int r, int lim) {
		if (minn[p]>lim) return ;
		if (tl(p)==tr(p)) {sta[++top]=minn[p]; sta[++top]=tl(p); return ;}
		int mid=(tl(p)+tr(p))>>1;
		if (l<=mid) query(p<<1, l, r, lim);
		if (r>mid) query(p<<1|1, l, r, lim);
	}
}pre1, pre2;

struct seg2{
	#define tl(p) tl[p]
	#define tr(p) tr[p]
	int tl[N<<2], tr[N<<2], maxn[N<<2], maxi[N<<2], pos[N];
	inline void pushup(int p) {
		maxn[p]=max(maxn[p<<1], maxn[p<<1|1]);
		maxi[p]=maxn[p]==maxn[p<<1]?maxi[p<<1]:maxi[p<<1|1];
	}
	void build(int p, int l, int r) {
		tl(p)=l; tr(p)=r;
		if (l==r) {maxn[p]=maxi[p]=l; pos[l]=p; return ;}
		int mid=(l+r)>>1;
		build(p<<1, l, mid);
		build(p<<1|1, mid+1, r);
		pushup(p);
	}
	void upd(int t, int p, int val) {for (maxn[p=pos[p]]=val,p>>=1; p; p>>=1) pushup(p);}
	void chkmax(int t, int p, int val) {for (p=pos[p],maxn[p]=max(maxn[p], val),p>>=1; p; p>>=1) pushup(p);}
	void query(int p, int l, int r, int lim) {
		if (maxn[p]<lim) return ;
		if (tl(p)==tr(p)) {sta[++top]=maxn[p]; sta[++top]=tl(p); return ;}
		int mid=(tl(p)+tr(p))>>1;
		if (l<=mid) query(p<<1, l, r, lim);
		if (r>mid) query(p<<1|1, l, r, lim);
	}
}suf1, suf2;

signed main()
{
	n=read(); m=read();
	pre1.build(1, 1, n); pre2.build(1, 1, n);
	suf1.build(1, 1, n); suf2.build(1, 1, n);
	for (int i=1; i<=n; ++i) dsu[i]=i;
	for (int i=1,u,v; i<=m; ++i) {
		// cout<<"i: "<<i<<endl;
		if (read()&1) {
			u=read(); v=read(); top=0;
			if (u>v) swap(u, v);
			if (find(u)==find(v)) continue;
			pre1.query(1, u, v, u); pre2.query(1, u, v, u);
			suf1.query(1, u, v, v); suf2.query(1, u, v, v);
			sort(sta+1, sta+top+1);
			top=unique(sta+1, sta+top+1)-sta-1;
			// cout<<"sta: "; for (int j=1; j<=top; ++j) cout<<sta[j]<<' '; cout<<endl;
			for (int j=1; j<top; ++j) dsu[find(sta[j])]=find(sta[j+1]);
			for (int j=1; j<top; ++j) pre1.upd(1, sta[j+1], sta[j]), pre2.upd(1, sta[j], sta[j]);
			for (int j=2; j<=top; ++j) suf1.upd(1, sta[j-1], sta[j]), suf2.upd(1, sta[j], sta[j]);
			pre2.chkmin(1, sta[top], sta[1]);
			suf2.chkmax(1, sta[1], sta[top]);
			// cout<<"pre1: "; for (int j=1; j<=n; ++j) cout<<pre1[j]<<' '; cout<<endl;
			// cout<<"pre2: "; for (int j=1; j<=n; ++j) cout<<pre2[j]<<' '; cout<<endl;
		}
		else printf("%d", find(read())==find(read()));
	}
	printf("\n");
	
	return 0;
}
```


---

## 作者：UKE_Automation (赞：0)

### CF1578B Building Forest Trails

[$\text{Link}$](https://codeforces.com/problemset/problem/1578/B)

首先我们先断环为链，此时两条弦相交等价于两条线段相交。破开环之后我们发现序列上的线段关系比较复杂，我们考虑一个经典套路，也就是只保留相交和包含两种关系中的一种。显然此时我们应该保留包含，因为环上连通块本身就具有这个性质，即只有包含关系。

那么我们就强制要求在同一个连通块内的点按照顺序依次连边，这样的话就可以满足要求。然后考虑如何新加入一条线段。我们设两个端点是 $x,y$，我们要知道此时这条线第一次会穿过哪一个连通块，也就是第一个包含 $x$ 的连通块。

此时会发现这样一件事：如果我们令 $h_i$ 表示 $i$ 点上方经过的线段个数（不含端点），那么 $x$ 右边第一个满足 $h_p<h_x$ 就是这个连通块中的点。那么每一次我们实际上只需要根据 $h_x,h_y$ 的关系，找出要移动的点，然后把两个连通块合并起来即可。特殊的情况是 $h_x=h_y$，此时我们任意移动一个点，然后判断一下，如果还没有超出要求的范围就合并，否则的话直接合并 $x,y$。

合并的时候分两种情况，即包含或者无交。这个用并查集维护一下左右端点即可判断。然后按照最开始的规则连接完边之后 $h$ 会改变，每一次会在一个区间上加一减一，用线段树维护即可。而上面查询 $p$ 的过程显然也可以用线段树二分完成。

显然我们只有在合并的时候会调用线段树，而总共只会有 $O(n)$ 次合并，所以总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = 2e5 + 5;
const int Inf = 2e9;
const int Mod = 1e9 + 7;
il int Add(int x, int y) {return x + y >= Mod ? x + y - Mod: x + y;} il void pls(int &x, int y) {x = Add(x, y);}
il int Del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;} il void sub(int &x, int y) {x = Del(x, y);}
il int qpow(int a, int b, int P = Mod) {int res = 1; for(; b; a = 1ll * a * a % P, b >>= 1) if(b & 1) res = 1ll * res * a % P; return res;}
il int Inv(int a) {return qpow(a, Mod - 2);}
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int n, m;
int fa[Maxn], l[Maxn], r[Maxn], siz[Maxn];

void init() {for(int i = 1; i <= n; i++) fa[i] = l[i] = r[i] = i, siz[i] = 1;}
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
void merge(int x, int y) {
	x = find(x), y = find(y);
	if(x == y) return ;
	if(siz[x] > siz[y]) swap(x, y);
	fa[x] = y; siz[y] += siz[x];
	l[y] = min(l[y], l[x]), r[y] = max(r[y], r[x]);
}

namespace SGT {
	struct node {
		int mn, tag;
	}t[Maxn << 2];
	#define ls(p) (p << 1)
	#define rs(p) (p << 1 | 1)
	void pushup(int p) {t[p].mn = min(t[ls(p)].mn, t[rs(p)].mn);}
	void pushtag(int p, int v) {t[p].mn += v, t[p].tag += v;}
	void pushdown(int p) {pushtag(ls(p), t[p].tag), pushtag(rs(p), t[p].tag); t[p].tag = 0;}
	void mdf(int p, int l, int r, int pl, int pr, int v) {
		if(pl > pr) return ;
		if(pl <= l && r <= pr) return pushtag(p, v);
		pushdown(p); int mid = (l + r) >> 1;
		if(pl <= mid) mdf(ls(p), l, mid, pl, pr, v);
		if(pr > mid) mdf(rs(p), mid + 1, r, pl, pr, v);
		pushup(p);
	}
	int query(int p, int l, int r, int x) {
		if(l == r) return t[p].mn;
		pushdown(p); int mid = (l + r) >> 1; 
		if(x <= mid) return query(ls(p), l, mid, x);
		else return query(rs(p), mid + 1, r, x);
	}
	int qr(int p, int l, int r, int x, int v) {
		if(t[p].mn >= v) return n + 1;
		if(l == r) return l;
		pushdown(p); int mid = (l + r) >> 1, res = n + 1;
		if(mid >= x) res = qr(ls(p), l, mid, x, v);
		if(res == n + 1) res = qr(rs(p), mid + 1, r, x, v);
		return res;
	}
	int ql(int p, int l, int r, int x, int v) {
		if(t[p].mn >= v) return 0;
		if(l == r) return l;
		pushdown(p); int mid = (l + r) >> 1, res = 0;
		if(mid < x) res = ql(rs(p), mid + 1, r, x, v);
		if(res == 0) res = ql(ls(p), l, mid, x, v);
		return res;
	}
}

void mg(int x, int y) {
	x = find(x), y = find(y);
	if(r[x] < l[y]) SGT::mdf(1, 1, n, r[x] + 1, l[y] - 1, 1);
	else SGT::mdf(1, 1, n, max(l[x], l[y]), min(r[x], r[y]), -1);
	merge(x, y);
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	cin >> n >> m;
	init();
    while(m--) {
    	int opt, x, y;
    	read(opt), read(x), read(y);
		if(x > y) swap(x, y);
		if(opt == 1) {
    		int hx = SGT::query(1, 1, n, x), hy = SGT::query(1, 1, n, y);
			while(find(x) != find(y)) {
    			if(hx > hy) {
    				int pos = SGT::qr(1, 1, n, x + 1, hx);
    				mg(x, pos); hx--;
				}
				else if(hx < hy) {
					int pos = SGT::ql(1, 1, n, y - 1, hy);
					mg(pos, y); hy--; 
				}
				else {
					int pos = SGT::qr(1, 1, n, x + 1, hx);
					if(pos < y) mg(x, pos), hx--;
					else mg(x, y);
				}
			}
		}
		else {
			putchar((find(x) == find(y)) + '0');
		}
	}
	Usd();
	return 0;
}
```

---

