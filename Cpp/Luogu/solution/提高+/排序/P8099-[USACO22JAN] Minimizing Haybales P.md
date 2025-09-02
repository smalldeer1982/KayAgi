# [USACO22JAN] Minimizing Haybales P

## 题目描述

Bessie 感到无聊，于是又在 Farmer John 的牛棚里制造麻烦。FJ 有 $N$（$1 \le N \le 10^5$）堆草堆。对于每个 $i \in [1,N]$，第 $i$ 堆草堆有 $h_i$（$1 \le h_i \le 10^9$）的草。Bessie 不想让任何的草倒下来，所以她唯一可以执行的操作为：

- 如果两个相邻的草堆的高度相差不超过 $K$（$1 \le K \le 10^9$），她可以交换这两堆草堆。

Bessie 在一系列这样的操作之后可以得到的的字典序最小的高度序列是什么？

## 说明/提示

【样例解释】

一种 Bessie 可以交换草堆的方式如下：

```plain
   7 7 3 6 2
-> 7 7 6 3 2
-> 7 7 6 2 3
-> 7 6 7 2 3
-> 6 7 7 2 3
```

【数据范围】

- 所有测试点的 $10\%$ 满足 $N \le 100$。
- 所有测试点的另外 $20\%$ 满足 $N \le 5000$。
- 其余 $70\%$ 的测试点没有额外限制。

供题：Daniel Zhang，Benjamin Qi

## 样例 #1

### 输入

```
5 3
7
7
3
6
2```

### 输出

```
6
7
7
2
3```

# 题解

## 作者：ETHANK (赞：31)

题意：给一个长度为 $N$ 的数组 $a$ ，若相邻两数之差的绝对值不超过 $K$ 则可以交换，问能得到的所有 $a$ 中字典序最小的一个。 

数据范围：$1\le N,K\le 10^5,1\le a_i\le 10^9$

发现 $|a_i-a_j| > K$ 的数无法交换，于是这两个数的相对位置是固定的。换言之，不妨设 $i<j$ ，那么 $a_i$ 始终会在 $a_j$ 前面。对于所有这样的 $(i,j)$ ，我们将 $i$ 向 $j$ 连一条有向边，按照题目要求做拓扑排序即可。

如何做？正常最小拓扑序是把所有入度为 $0$ 的点放入优先队列中，然后每次取堆顶的点并将其连出的边删除。时间复杂度为 $O(NK)$ ，瓶颈为图中可能的边数。

思考一下如何优化，首先可以对原数组离散化，用一个线段树来维护当前可能的最小位置，每次取出作为答案并更新与其有连边的点的入度即可。具体地，若当前点的权值为 $u$ ，则 $[1,m]\setminus[u-K+1,u+K-1]$ 中的所有权值对应的点的入度 $-1$ 。需要一个带懒标记线段树做区间更新。

时间复杂度：$O(N\log N)$

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define pii pair<int,int>
#define vi vector<int>
#define fi first
#define se second
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define ALL(x) x.begin(),x.end()
#define sz(x) int(x.size())
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const int N=2e5+5;
int n,K,a[N],val[N],deg[N];
unordered_map <int,int> vis;
#define ls (p<<1)
#define rs (ls|1)
#define mid ((L+R)>>1)
pii t[N<<2];
int tag[N<<2];
inline pii Min(const pii a,const pii b){
    if(a.se == b.se)return make_pair(min(a.fi,b.fi),a.se);
    return a.se < b.se ? a : b;
}
void build(int p,int L,int R){
    if(L == R){
        t[p] = make_pair(L,deg[L]);
        return;
    }
    build(ls,L,mid),build(rs,mid+1,R);
    t[p] = Min(t[ls],t[rs]);
}
void push(int p,int v){tag[p] += v,t[p].se += v;}
void down(int p){
    if(!tag[p])return;
    push(ls,tag[p]),push(rs,tag[p]);
    tag[p] = 0;
}
void upd(int p,int L,int R,int l,int r,int v){
    if(l > R || r < L)return;
    if(l <= L && R <= r){
        push(p,v);
        return;
    }
    down(p);
    upd(ls,L,mid,l,r,v),upd(rs,mid+1,R,l,r,v);
    t[p] = Min(t[ls],t[rs]);
}
int T[N];
void add(int x){for(;x <= n;x += x & -x)T[x]++;}
int Q(int x){
    int res = 0;
    for(;x;x -= x & -x)res += T[x];
    return res;
} 
int main(){
    n = read(),K = read();
    rep(i,1,n)a[i] = read(),val[i] = a[i];
    sort(val+1,val+n+1);
    rep(i,1,n){
        vis[a[i]]++;
        a[i] = lower_bound(val+1,val+n+1,a[i]) - val + vis[a[i]] - 1;
    }
    //calculating in-degree
    rep(i,1,n){
        int x = lower_bound(val+1,val+n+1,val[a[i]]-K) - val - 1;
        int y = lower_bound(val+1,val+n+1,val[a[i]]+K+1) - val - 1;
        deg[a[i]] = (i-1) + Q(x) - Q(y);
        add(a[i]);
    }
    build(1,1,n);
    rep(i,1,n){
        int u = t[1].fi;
        cout << val[u] << '\n';
        int x = lower_bound(val+1,val+n+1,val[u]-K) - val - 1;
        //cout << 1 << ' ' << x << '\n';
        int y = lower_bound(val+1,val+n+1,val[u]+K+1) - val - 1;
        //cout << y+1 << ' ' << n << '\n';
        //cout << u << ' ' << u << '\n';
        upd(1,1,n,1,x,-1);
        upd(1,1,n,y+1,n,-1);
        upd(1,1,n,u,u,n);
    }
    return 0;
}
```

---

## 作者：panyf (赞：11)

考虑从前到后遍历每一个草堆，设当前要加入第 $i$ 个草堆，前 $i-1$ 个草堆已经满足字典序最小，位置 $x$ 是原来的第 $p_x$ 个草堆。

若可以将 $i$ 插到位置 $x$ 后面，则需要满足 $h_{p_{x+1}},h_{p_{x+2}}\cdots h_{p_{i-1}}\in[h_i-k,h_i+k]$。找到最小的满足这个性质的 $x$。容易发现插到位置 $x,x+1\cdots i-1$ 后面都是可行的。

考虑插到哪个位置最优。若 $h_j>h_i$，则将 $i$ 插到 $j$ 的前面，字典序会变小。找到最小的 $y$ 满足 $h_{y+1}>h_i$，将 $i$ 插到 $y$ 后面即可。

考虑平衡树维护。每个结点维护子树 $size$，$h$ 的最大值和最小值。需要支持合并，按 $size$ 分裂，两种平衡树上二分（分别找 $x,y$）。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
mt19937 rd(time(0));
struct T{
	int l,r,d,mn,mx,s,h;
}s[100009];
int n,k,h,r;
void up(int x){//更新size，最大值，最小值
	s[x].mn=min(s[x].h,min(s[s[x].l].mn,s[s[x].r].mn));
	s[x].mx=max(s[x].h,max(s[s[x].l].mx,s[s[x].r].mx));
	s[x].s=s[s[x].l].s+s[s[x].r].s+1;
}
void sp(int x,int k,int&p,int&q){//分裂
	if(!x){p=q=0;return;}
	if(s[s[x].l].s<k)p=x,sp(s[x].r,k-s[s[x].l].s-1,s[x].r,q);else q=x,sp(s[x].l,k,p,s[x].l);
	up(x);
}
int mg(int x,int y){//合并
	if(!x||!y)return x|y;
	if(s[x].d<s[y].d)return s[x].r=mg(s[x].r,y),up(x),x;
	return s[y].l=mg(x,s[y].l),up(y),y;
}
int e1(int x){//求最小的w满足x子树内第w+1~sizex个元素属于[h-k,h+k]
	int w=0;
	while(x)if(min(s[x].h,s[s[x].r].mn)<h-k||max(s[x].h,s[s[x].r].mx)>h+k)w+=s[s[x].l].s+1,x=s[x].r;else x=s[x].l;
	return w;
}
int e2(int x){//求最小的w满足x子树内第w+1个元素大于h
	int w=0;
	while(x)if(max(s[s[x].l].mx,s[x].h)>h)x=s[x].l;else w+=s[s[x].l].s+1,x=s[x].r;
	return w;
}
void dfs(int x){if(x)dfs(s[x].l),cout<<s[x].h<<'\n',dfs(s[x].r);}//中序遍历
int main(){ios::sync_with_stdio(0),cin.tie(0);
	int i,x,y;
	for(cin>>n>>k,s[0].mn=2e9,s[0].mx=0,i=1;i<=n;++i){
		cin>>h,s[i]={0,0,(int)rd(),h,h,1,h};
		sp(r,e1(r),x,r),sp(r,e2(r),y,r),r=mg(mg(x,y),mg(i,r));
	}
	dfs(r);
}
```


---

## 作者：Blunt_Feeling (赞：9)

## P8099 [USACO22JAN] Minimizing Haybales P 题解

既然给了 4s 时限，那就放心想 $\mathcal{O}(n\log^{2}n)$ 的解法。

一个显然的性质是，对于每个数 $a_i$，它的最大活动空间 $[l,r]$ 满足 $\forall j\in [l,r], \lvert a_i-a_j \rvert \le k$。根据贪心的思想，当 $a_i$ 通过交换活动到最小的 $pos$ 前，且 $pos$ 满足 $pos\in [l,i-1],a_{pos}>a_i$ 时一定最优。只考虑往左活动，因为往右不一定更优。

不离散化，直接使用普通的线段数维护区间最小、最大值。从前往后每次新加进来一个 $a_i$，二分一个左端点 $p$，在线段数内查询 $[p,i-1]$ 的最值是否符合条件，找到向左的最大活动空间为 $[p,i-1]$。接着再二分一个最小的 $pos$，找到最小的 $>a_i$ 的位置。如果存在这样的 $pos$，把 $a_i$ 丢到 $pos$ 对应的一个容器里，我使用的是 `multiset`，同时在线段数上更新 $pos$ 所在位置的最小值；否则就把 $a_i$ 作为一个新的值加入线段数。

最后按顺序把每个 `multiset` 里的值取出来即可。总时间复杂度 $\mathcal{O}(n\log^{2}n)$，不开 O2 最慢点 611ms，开 O2 后快到飞起。

### Code
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read() {
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x; return x;
}
const int maxn=100050;
int n,m,a[maxn],tree[maxn<<2][2];
void push_up(int rt) {
    tree[rt][0]=min(tree[rt<<1][0],tree[rt<<1|1][0]);
	tree[rt][1]=max(tree[rt<<1][1],tree[rt<<1|1][1]);
}
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
void update(int p,int x0,int x1,int l,int r,int rt)
{
	if(l==r) tree[rt][0]=x0,tree[rt][1]=x1;
	else
	{
		int mid=(l+r)>>1;
		if(p<=mid) update(p,x0,x1,lson);
		else update(p,x0,x1,rson);
		push_up(rt);
	}
}
typedef pair<int,int> P;
P query(int L,int R,int l,int r,int rt)
{
	if(L<=l&&r<=R) return make_pair(tree[rt][0],tree[rt][1]);
	int mid=(l+r)>>1,Max=0,Min=1e9;
	if(L<=mid)
    {
        P ls=query(L,R,lson);
        Max=max(Max,ls.second);
        Min=min(Min,ls.first);
    }
	if(R>mid)
    {
        P rs=query(L,R,rson);
        Max=max(Max,rs.second);
        Min=min(Min,rs.first);
    }
	return make_pair(Min,Max);
}
multiset<int> st[maxn];
int main()
{
    n=read(); m=read();
    a[1]=read();
    update(1,a[1],a[1],1,n,1);
    st[1].insert(a[1]);
    int now=1;
    For(i,2,n)
    {
        a[i]=read();
        int p=now+1,L=1,R=now;
        while(L<=R) //找活动空间为 [p,i-1]
        {
            int mid=L+R>>1;
            P res=query(mid,now,1,n,1);
            if(res.first<a[i]-m||res.second>a[i]+m) L=mid+1;
            else p=min(p,mid),R=mid-1;
        }
        if(p==now+1)
        {
            now++;
            update(now,a[i],a[i],1,n,1);
            st[now].insert(a[i]);
            continue;
        }
        int pos=now+1;
        L=p,R=now;
        while(L<=R) //找最左的 >a[i] 的位置 pos
        {
            int mid=L+R>>1;
            P res=query(p,mid,1,n,1);
            if(res.second>a[i]) pos=min(pos,mid),R=mid-1;
            else L=mid+1;
        }
        if(pos==now+1)
        {
            now++;
            update(now,a[i],a[i],1,n,1);
            st[now].insert(a[i]);
            continue;
        }
        st[pos].insert(a[i]);
        int Min=*st[pos].begin(),Max=*st[pos].rbegin();
        if(a[i]==Min) update(pos,a[i],Max,1,n,1);
    }
    For(i,1,now) for(int x:st[i]) printf("%d\n",x);
    return 0;
}
```

---

## 作者：xglight (赞：5)

## 前置

1. 拓扑排序

2. 可持久化权值线段树（主席树）

## 解法

观察题面，我们希望高度小的尽可能在前面。

但不难发现，对于两个草堆 $i,j$，若 $i<j$ 且 $|h_i-h_j|>k$，则 $i$ 一定在 $j$ 前面。

联系 [P8100](https://www.luogu.com.cn/problem/P8100)，不妨从 $i$ 向 $j$ 连边，这样就确定了每个草堆的先后次序。

连出来的图一定是 DAG，跑一遍拓扑排序即可。

拓扑的注意事项：每次要优先取**原来就有的点**（草堆的点）。

不过还有一个问题，$N$ 是 $10^5$ 级别，边数太多，可能会 MLE+TLE。

我选择的是主席树优化连边，不会的可以看[P3834 【模板】可持久化线段树](https://www.luogu.com.cn/problem/P3834)。

具体来说，将草堆以高度为关键字从小到大排序。

遍历所有草堆，每次先二分查找前面所有满足 $|h_i-h_j|>k$ 的草堆，可分两段查询（$(h_i-h_j)>k$ 和 $(h_j-h_i)>k$），将这两段区间向草堆编号连边。

再将新草堆插入主席树，注意要将旧树向新树连边。

这样你就能收获 $O(n \log n)$ 的飞快解法。

```cpp
#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 1e5 + 5;
int n, k;
int h[N];
struct edge {
    int to, nt;
} e[N << 6];
int hd[N << 5], in[N << 5], tot;
inline void add(int u, int v) { e[++tot] = {v, hd[u]}, in[v]++, hd[u] = tot; }
void uadd(int u, int v) { add(u, v), add(v, u); }
int cnt; // 主席树节点数量
struct seg_node {
    int ls, rs, siz; //左儿子，右儿子，子树大小
};
struct segtree {
    int rt[N];
    seg_node tr[N << 5]; //32倍空间
    void push_up(int x) {
        int ls = tr[x].ls, rs = tr[x].rs;
        if (tr[ls].siz) add(ls, x);
        if (tr[rs].siz) add(rs, x);
        tr[x].siz |= tr[ls].siz, tr[x].siz |= tr[rs].siz;
    }
    void build_tree(int &x, int l, int r) {
        if (!x) x = ++cnt; //用了动态开点
        if (l == r) return;
        int mid = (l + r) >> 1;
        build_tree(tr[x].ls, l, mid), build_tree(tr[x].rs, mid + 1, r);
        push_up(x);
    }
    void insert(int &x, int y, int l, int r, int p, int id) {
        if (!x) x = ++cnt;
        if (l == r) {
            add(id, x), tr[x].siz = 1;
            return;
        }
        tr[x] = tr[y];
        int mid = (l + r) >> 1;
        if (p <= mid) {
            tr[x].ls = 0;
            insert(tr[x].ls, tr[y].ls, l, mid, p, id);
            if (tr[tr[y].ls].siz) add(tr[y].ls, tr[x].ls); //要由旧树向新树连边
        } else {
            tr[x].rs = 0;
            insert(tr[x].rs, tr[y].rs, mid + 1, r, p, id);
            if (tr[tr[y].rs].siz) add(tr[y].rs, tr[x].rs);
        }
        push_up(x);
    }
    void link(int x, int l, int r, int L, int R, int p) {
        if ((!x) || (!tr[x].siz) || (L > R)) return;
        if (L <= l && r <= R) {
            add(x, p); //区间向点连边
            return;
        }
        int mid = (l + r) >> 1;
        if (L <= mid) link(tr[x].ls, l, mid, L, R, p);
        if (R > mid) link(tr[x].rs, mid + 1, r, L, R, p);
    }
};
segtree tree;
int tmp[N], len;

struct node {
    int id;
    bool operator<(const node x) const {
        if (id > n || x.id > n) return id <= n; //优先选择原来就有的节点
        return h[id] > h[x.id];
    };
};
priority_queue<node> q;
void topsort() {
    for (int i = 1; i <= n; i++)
        if (in[i] == 0) q.push({i});
    while (!q.empty()) {
        int u = q.top().id;
        q.pop();
        if (u <= n) printf("%d\n", h[u]);
        for (int i = hd[u]; i; i = e[i].nt) {
            int v = e[i].to;
            if (--in[v] == 0) q.push({v});
        }
    }
}
int main() {
    scanf("%d%d", &n, &k), cnt = n;
    for (int i = 1; i <= n; i++)
        scanf("%d", &h[i]), tmp[++tmp[0]] = h[i];
    sort(tmp + 1, tmp + 1 + tmp[0]);
    len = unique(tmp + 1, tmp + 1 + tmp[0]) - tmp - 1; // 离散化去重，len为离散化后数组的长度
    tree.build_tree(tree.rt[0], 1, len);               // 建树
    int id = lower_bound(tmp + 1, tmp + 1 + len, h[1]) - tmp;
    tree.insert(tree.rt[1], tree.rt[0], 1, len, id, 1);
    for (int i = 2; i <= n; i++) {
        int l = lower_bound(tmp + 1, tmp + 1 + len, h[i] - k) - tmp - 1;
        int r = upper_bound(tmp + 1, tmp + 1 + len, h[i] + k) - tmp;                              //查找区间
        tree.link(tree.rt[i - 1], 1, len, 1, l, i), tree.link(tree.rt[i - 1], 1, len, r, len, i); //由区间向点连边
        id = lower_bound(tmp + 1, tmp + 1 + len, h[i]) - tmp;
        tree.insert(tree.rt[i], tree.rt[i - 1], 1, len, id, i); // 插入草堆
    }
    topsort(); // 拓扑
    return 0;
}
```

---

## 作者：寻逍遥2006 (赞：5)

既然这道题 $N\leqslant10^5$ ，为什么没有人写分块呢？

首先考虑在最终数列中在第一个的数，假设它原来在第 $i$ 位，也就是 $h_i$ ，那么它必然要和 $h_1,h_2\dots h_{i-1}$ 交换，也就是说 $h_1,h_2\dots h_{I-1}\in[h_i-K,h_i+K]$ 。

这时候贪心的思路就出来了：考虑所有还没有被选的数，找到里面最小的 $h_i$ ，使得所有的 $h_1,h_2\dots h_{I-1}\in[h_i-K,h_i+K]$ ，将这个数放在当前的最前面一位，从原序列中剔除这个数，然后递归这个过程，这样我们获得了 $O(N^2)$ 的做法。

接着，我们会发现，对于 $i<j$ ，如果 $h_i\notin[h_j-K,h_j+K]$ 那么 $h_i$ 必然在 $h_j$ 前面，找到所有这样的偏序关系，我们就可以得到一个 DAG ，只需要在上面找字典序最小拓扑排序即可。

但是考虑到它的边数会达到 $O(N^2)$ ，仍然会被卡，所以考虑分块暴力维护每一次贪心的选择，下面记块数为 $B$ 。

对于块内的数，暴力维护，找到所有没有被块内其他数限制的所有数，以 $h_i$ 为第一关键字，以 $i$ 为第二关键字排序，单次复杂度为 $O\left(\dfrac{n}{B}\log(\dfrac{n}{B})\right)$ 。

每一次找答案，从第一个还有数字没选的块开始，找到当前的最小值以及块内所有值中的最大值 $maxn$ 和最小值 $minn$ 。接下来的每一个块，找到所有的在 $[max-K,min+K]$ （这个区间可能为空）中的最小值，取所有这些值中的最小值为答案，这个过程复杂度为 $O\left(B\log(\dfrac{N}{B})\right)$ 。每一次找到贪心值之后，暴力重做一遍贪心值所在块即可。

所以总体复杂度为 $O\left(N\times \dfrac{N}{B}\log(\dfrac{N}{B})+N\times (B\log(\dfrac{N}{B})+\dfrac{N}{B}\log(\dfrac{N}{B}))\right)$ 。复杂度在 $B=\sqrt{N}$ 时取最优，为 $O(N\sqrt{N}\log N)$ 。开 O2 能过，而且线性空间。

```cpp
#include <bits/stdc++.h>
using namespace std;
int Qread()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return x; 
}
typedef pair<int,int> pr;
typedef pair<int,bool> ps;
int n,k,i,bel,a;
int B,Bnum;
bool vis[100010];
int ans[100010];
vector<pr> abl[1010];//able num in block
vector<ps> num[1010];//number in each block
pr qz[1010],gjz;//[maxn,minn] of each block
int las[1010];//last number cnt in each block
void Bsolv(int id)//solv in B
{
	int lim=num[id].size();
	qz[id]=make_pair(-1,-1);bool hv=false;
	abl[id].clear();
	for(int i=0;i<lim;i++)
	{
		if(num[id][i].second) continue;
		if(!hv) abl[id].push_back(make_pair(num[id][i].first,i)),qz[id].first=qz[id].second=num[id][i].first,hv=true;
		else
		{
			if(num[id][i].first-k<=qz[id].first&&qz[id].second<=num[id][i].first+k) abl[id].push_back(make_pair(num[id][i].first,i));
			qz[id].first=min(qz[id].first,num[id][i].first);
			qz[id].second=max(qz[id].second,num[id][i].first);
		}
	}
	sort(abl[id].begin(),abl[id].end());
	lim=abl[id].size();
	return;
}
int solve()
{
	int Bid=0,inBid=0,ret=20070610,d;
	pr lim;bool hv=false;
	for(int i=1;i<=Bnum;i++)
	{
		if(las[i]==0) continue;
		if(!hv)
		{
			Bid=i,inBid=0;
			ret=abl[i][0].first;
			lim=qz[i];hv=true;
		}
		else
		{
			if(lim.second-lim.first>2*k) break;
			gjz=make_pair(lim.second-k,-1);
			d=upper_bound(abl[i].begin(),abl[i].end(),gjz)-abl[i].begin();
			if(d!=(int)abl[i].size()&&abl[i][d].first<=lim.first+k&&ret>abl[i][d].first) Bid=i,inBid=d,ret=abl[i][d].first;
			lim.first=min(lim.first,qz[i].first);
			lim.second=max(lim.second,qz[i].second);
		}
	} 
	num[Bid][abl[Bid][inBid].second].second=true;las[Bid]--;
	Bsolv(Bid);
	return ret;
}
int main()
{
	n=Qread(),k=Qread();
	B=sqrt(n);
	for(i=1;i<=n;i++)
	{
		bel=(i-1)/B+1;
		a=Qread();
		num[bel].push_back(make_pair(a,false));
		las[bel]++;
	}
	Bnum=(n-1)/B+1;
	for(i=1;i<=Bnum;i++)
		Bsolv(i);
	for(i=1;i<=n;i++)
		ans[i]=solve();
	for(i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
 } 
```


---

## 作者：Odalys (赞：5)

由 `[AGC001F] Wide Swap` 可知一个结论，若 $i < j,|h_i-h_j|> k$ 则无论怎么交换，$h_i,h_j$ 的相对位置不会改变。

据此，我们暴力连边，每条边表示 $h_i$ 必须得在 $h_j$，然后用一个堆拓扑一遍即可得出最小字典序

考虑使用数据结构优化这个建图方式

考虑使用建一棵权值主席树，上面全是虚点，每次加入新的 $h_i$ 我们在叶子上将 $i$ 连上这个权值，再一路向祖先连；每次连所有满足 $i < j,|h_i-h_j|> k$  的边只需在权值主席树上将对应的区间连一下即可。

最后还是用一个堆来拓扑，有一个细节是，优先将堆（即当前入度为 $0$ 的点）中虚点拿出来处理。

注意，主席树新建点时应当把旧的点向新的点连边，否则会被

```
9 5
2
1
6
2
2
10
6
10
3
```

这组数据 hack ，原因是主席树上新建一连串虚点的同时，原来的限制可能丢失，~~然鹅这题数据过水所以练习赛时我没有考虑到这个问题也A了~~。


```cpp
/* ==============================
 *  Author : Odalys 
 *
 *  Blog : Odalys.xyz
 *
 *  Mail : minyuenu@gmail.com
 * =============================== */
#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void read(T &a){
    T w = 1; a = 0;
    char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') w = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) a = (a * 10) + (ch - '0');
    a *= w;
}
template <typename T> inline void ckmax(T &a, T b){a = a > b ? a : b;}
template <typename T> inline void ckmin(T &a, T b){a = a < b ? a : b;}
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define mii map<int, int> 
#define pii pair<int, int> 
#define vi vector<int>
#define si set<int> 
#define ins insert
#define era erase
#define Debug(x) cout << #x << " = " << x << endl
#define For(i,l,r) for (int i = l; i <= r; ++i) 
#define foR(i,l,r) for (int i = l; i >= r; --i)
const int N = 1e5 + 10;
vi to[N * 40];
int du[N * 40];
struct SGT {
	int l, r, siz;
} tr[N * 30];
#define ls tr[x].l
#define rs tr[x].r

int rt[N];
int total;
int Id () { return ++total; }
inline void pushup (int x) {
	if (tr[ls].siz) to[ls].pb(x), du[x]++;
	if (tr[rs].siz) to[rs].pb(x), du[x]++; 
	tr[x].siz |= tr[ls].siz; 
	tr[x].siz |= tr[rs].siz;
}
void Build (int &x, int l, int r) {
	if (!x) x = Id(); 
//	Debug(x); cout << l << " " << r << endl; 
	if (l == r) return;
	int mid = l + r >> 1;
	Build(ls, l, mid), Build(rs, mid + 1, r);
	pushup(x); 
}
void Insert (int &x, int y, int l, int r, int p, int id) {
	if (!x) x = Id(); 
	if (l == r) return (du[x]++, to[id].pb(x), tr[x].siz = 1), void();
	tr[x] = tr[y];
	int mid = l + r >> 1;
	if (p <= mid) {
		ls = 0, Insert(ls, tr[y].l, l, mid, p, id);
		if (tr[tr[y].l].siz) to[tr[y].l].pb(tr[x].l), du[tr[x].l]++;
	}
	else {
		rs = 0, Insert(rs, tr[y].r, mid + 1, r, p, id);
		if (tr[tr[y].r].siz) to[tr[y].r].pb(tr[x].r), du[tr[x].r]++;	
	}
	pushup(x);
} 

void Link (int x, int l, int r, int ll, int rr, int p) {
	if (!x) return ;
	if (!tr[x].siz) return ;
	if (ll > rr) return ;
	if (ll <= l && r <= rr) return (du[p]++, to[x].pb(p)), void();
	int mid = l + r >> 1;
	if (ll <= mid) Link(ls, l, mid, ll, rr, p);
	if (rr > mid) Link(rs, mid + 1, r, ll, rr, p);
}

int a[N];
int lsh[N], lshc;
inline void Init () {
	sort (lsh + 1, lsh + lshc + 1);
	lshc = unique (lsh + 1, lsh + lshc + 1) - lsh - 1;
}
int GetId (int x) { return lower_bound(lsh + 1, lsh + lshc + 1, x) - lsh; }
int Get (int x, bool op) {
	if (!op) 
		return lower_bound(lsh + 1, lsh + lshc + 1, x) - lsh - 1;
	return upper_bound(lsh + 1, lsh + lshc + 1, x) - lsh; 
}
int n, k; 
namespace Topu {
	struct Node {
		int id;	
		Node (int Id = 0) { id = Id; }
		bool operator < (const Node x) const{ 
			if (id > n || x.id > n) {
				return !(id > n);
			}
			return a[id] > a[x.id]; 
	
		}
	};
	priority_queue < Node > q;

	inline void main() {
		For (i, 1, n) if (!du[i]) q.push(Node(i));
		while (!q.empty()) {
			int u = q.top().id; q.pop();
			if (u <= n) 
				printf ("%d\n", a[u]);
			for (auto v : to[u]) {
				du[v]--;
				if (!du[v]) q.push(Node(v)); 
			}
		}
	}
}

int main() {
//	freopen ("prod1.in", "r", stdin);
//	freopen ("prod1.out", "w", stdout);
	read(n), read(k);
	For (i, 1, n) read(a[i]), lsh[++lshc] = a[i];
	Init(); 
	total = n;
	Build(rt[0], 1, lshc);
	Insert(rt[1], rt[0], 1, lshc, GetId(a[1]), 1); 
	For (i, 2, n) {
		int l = Get(a[i] - k, 0), r = Get(a[i] + k, 1);
		//if (i == n) cout << r << " " << lshc << endl;
		Link(rt[i - 1], 1, lshc, r, lshc, i);
		Link(rt[i - 1], 1, lshc, 1, l, i);
		Insert(rt[i], rt[i - 1], 1, lshc, GetId(a[i]), i);
	}	
	Topu :: main();
	return 0;
}
```


---

## 作者：ForgotDream_CHN (赞：3)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17607726.html)

> $n$ 个草垛排成一排，第 $i$ 个的高度为 $h_i$，两个草垛 $i, j$ 之间能够交换当且仅当 $|h_i - h_j| \le k$，求交换任意次后字典序最小的草垛排列。  
$n, k \le 10^5, h_i \le 10 ^ 9$。

一道古老的湖北省内测试题。

我们注意到对于任意 $i, j$，如果 $|h_i - h_j| > k$ 的话，那么 $i, j$ 的相对次序是不会改变的，那么一个很好想的暴力就是找出所有满足 $i < j, |h_i - h_j| > k$ 的 $i, j$，然后在 $i, j$ 间连边表示拓扑顺序，然后用一个优先队列来维护拓扑排序即可构造出字典序最小的序列。时间复杂度为 $\mathcal{O}(n^2 \log n)$，可以拿 $30$ 分。

考虑正解。从左向右遍历每一个草垛，假设当前已经到了第 $i$ 个草垛，且前边的 $i - 1$ 个草垛已经是字典序最小的了。我们考虑将 $i$ 插到哪里会使字典序最小。一个很显然的事实是，草垛 $i$ 能插入的位置 $j$ 一定满足对于任意的 $j \le l < i$，都有 $|h_i - h_l| \le k$。那么首先要找到一个最小的 $j$，样 $i$ 就只能插入到 $[j, i)$ 中。

再考虑插到哪里会让字典序变小。贪心地，我们找到一个最小的 $p \in [j, i)$ 并且满足 $h_p > h_i$，将 $i$ 插入到 $p$ 的前边即可。

上述过程不难用 FHQ Treap 实现，具体而言，需要支持按秩合并与分裂，两种平衡树上二分（用于求出 $j$ 与 $p$）即可。总体时间复杂度 $\mathcal{O}(n \log n)$。

```cpp
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e5 + 50;
int n, k, h[N];
template<int N = 300050>
struct FHQTreap {
  std::mt19937 rnd;
  std::random_device rd;
  struct Node {
    int lc = 0, rc = 0;
    int max = 0, min = 0, val = 0, siz = 0, prm;
  } t[N];
  int cnt = 0, rt = 0;
  FHQTreap() { rnd = std::mt19937(rd()), t[rt].min = 2e9, t[rt].max = 0; }
  int &lc(int u) { return t[u].lc; }
  int &rc(int u) { return t[u].rc; }
  void pushup(int u) {
    t[u].siz = t[lc(u)].siz + t[rc(u)].siz + 1;
    t[u].max = std::max({t[u].val, t[lc(u)].max, t[rc(u)].max});
    t[u].min = std::min({t[u].val, t[lc(u)].min, t[rc(u)].min});
  }
  int init(int val) {
    cnt++;
    t[cnt].val = t[cnt].max = t[cnt].min = val;
    t[cnt].prm = rnd(), t[cnt].siz = 1;
    return cnt;
  }
  void split(int u, int val, int &l, int &r) {
    if (!u) return void(l = r = 0);
    if (t[lc(u)].siz < val) l = u, split(rc(u), val - t[lc(u)].siz - 1, rc(u), r);
    else r = u, split(lc(u), val, l, lc(u));
    pushup(u);
  }
  int merge(int l, int r) {
    if (!l || !r) return l + r;
    if (t[l].prm > t[r].prm) return rc(l) = merge(rc(l), r), pushup(l), l;
    else return lc(r) = merge(l, lc(r)), pushup(r), r;
  }
  int find1(int u, int val) {
    int res = 0;
    while (u) {
      if (std::min(t[u].val, t[rc(u)].min) < val - k || 
          std::max(t[u].val, t[rc(u)].max) > val + k) {
        res += t[lc(u)].siz + 1, u = rc(u);
      } else {
        u = lc(u);
      }
    }
    return res;
  }
  int find2(int u, int val) {
    int res = 0;
    while (u) {
      if (std::max(t[u].val, t[lc(u)].max) > val) u = lc(u);
      else res += t[lc(u)].siz + 1, u = rc(u);
    }
    return res;
  }
  void traverse(int u) {
    if (!u) return;
    traverse(lc(u));
    std::cout << t[u].val << "\n";
    traverse(rc(u));
  }
};
FHQTreap fhq;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> h[i];
  for (int i = 1, l, r, p; i <= n; i++) {
    fhq.split(fhq.rt, fhq.find1(fhq.rt, h[i]), l, r);
    fhq.split(r, fhq.find2(r, h[i]), r, p);
    fhq.rt = fhq.merge(fhq.merge(l, r), fhq.merge(fhq.init(h[i]), p));
  }
  fhq.traverse(fhq.rt);
  return 0;
}

```

---

## 作者：Alex_Wei (赞：3)

> [P8099 [USACO22JAN] Minimizing Haybales P](https://www.luogu.com.cn/problem/P8099)

为使字典序尽量小，我们的大致思路是将小的数尽量往前移。具体一点，依次考虑每个位置 $i$，将 $h_i$ 移到从前往后第一个大于 $h_i$ 的 **合法** 位置 $p\ (p\leq i)$ 之前，合法即满足 $h_p\sim h_i$ 与 $h_i$ 相差不超过 $k$。

再往前移反而会让字典序变大：前面能够移到的位置上的数均不大于 $h_i$，不如不移。但我们还有一个顾虑：当前决策是否会影响到全局结果？即是否存在 $j > i$，使得 $h_j$ 很小且本来能移到很前面，但 $h_i$ 这样一挪，就办不到了呢？并不会，因为若 $h_j < h_i$，阻挡它的仅有可能是落在区间 $(h_j + k, h_i + k]$ 的数（对于小于 $h_j - k$ 的数，$h_i$ 本来也过不去），说明就算 $h_i$ 不移，$h_j$ 本来就只能待在这些数后面，不会比移动 $h_i$ 更优。$h_j > h_i$ 同理。

根据上述结论，我们首先二分找到最左边的合法位置，再二分找到最左边的第一个大于 $h_i$ 的合法位置 $p$，然后把 $h_i$ 挪到 $h_p$ 前面。若直接将二分和平衡树生硬地结合，时间复杂度线性对数平方，不开 O2 难以通过，甚至开了 O2 都荣膺最劣解（41.82s）。但若直接在平衡树上二分，时间复杂度降至线性对数，比 $\log ^ 2 n$ 快了将近 20 倍（2.21s）。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0; char s = getchar();
	while(!isdigit(s)) s = getchar();
	while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
	return x;
}
inline void print(int x) {
	if(x >= 10) print(x / 10);
	putchar(x % 10 + '0');
}

const int N = 1e5 + 5;
int ls[N], rs[N], mn[N], mx[N], val[N];
int n, k, R, node, rd[N], sz[N];
void push(int x) {
	mn[x] = min(min(mn[ls[x]], mn[rs[x]]), val[x]);
	mx[x] = max(max(mx[ls[x]], mx[rs[x]]), val[x]);
	sz[x] = sz[ls[x]] + sz[rs[x]] + 1;
}
int nnode(int v) {
	int x = ++node;
	val[x] = mn[x] = mx[x] = v, sz[x] = 1;
	return rd[x] = rand(), ls[x] = rs[x] = 0, x;
}
int merge(int x, int y) {
	if(!x || !y) return x | y;
	if(rd[x] > rd[y]) return rs[x] = merge(rs[x], y), push(x), x;
	return ls[y] = merge(x, ls[y]), push(y), y;
}
void split(int p, int &x, int &y, int k) {
	if(!p) return x = y = 0, void();
	if(k <= sz[ls[p]]) split(ls[p], x, ls[y = p], k);
	else split(rs[p], rs[x = p], y, k - sz[ls[p]] - 1);
	push(p);
}
void move(int i, int p) {
	int a, b, c, d; if(i == p) return;
	split(R, c, d, i), split(c, b, c, i - 1), split(b, a, b, p - 1);
	R = merge(a, merge(c, merge(b, d))); 
}
void dfs(int x) {
	if(!x) return;
	dfs(ls[x]), print(val[x]), putchar('\n'), dfs(rs[x]);
}

int main() {
	cin >> n >> k, mn[0] = 1e9;
	for(int i = 1; i <= n; i++) {
		int p, x, tot = 0, l, h = read();
		p = R = merge(R, nnode(h));
		while(p) {
			int r = rs[p];
			if(mx[r] - h > k || h - mn[r] > k) p = r;
			else if(val[p] - h > k || h - val[p] > k) {tot += sz[r]; break;}
			else p = ls[p], tot += sz[r] + 1;
		} if(tot == 1) continue;
		split(R, R, x, l = i - tot), tot = 0, p = x;
		if(mx[x] == h) {R = merge(R, x); continue;}
		while(p) {
			int l = ls[p];
			if(mx[l] > h) p = l;
			else if(val[p] > h) {tot += sz[l]; break;}
			else p = rs[p], tot += sz[l] + 1;
		} R = merge(R, x), move(i, l + tot + 1);
	} dfs(R);
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：2)

## 思路分析

类线段树优化建图。

最基础的，我们需要能够抽象出图论做法：如果 $|a_i-a_j|>m$，那么 $i,j$ 的相对顺序不会改变。因此，如果 $a_i$ 恒在 $a_j$ 前面，那么我们从 $i$ 向 $j$ 连一条边。最后再跑一下最小字典序 top 序即可。

HINT：按照这道题的时限，暴力卡常已经能过了。

但是不够优，我们想一下线段树优化建图优化建图的套路。

其实每减一个点，都会将后面的所有的满足要求的点的入度 $-1$。那也就是说，如果我们能快速的计算出入度 $=0$ 的序号最靠前的最小的点，则此题可解。

这个显然可以用线段树去维护，但是怎么只加后面的满足要求的点呢？

你但凡前面还有一个满足要求的点，你这个点都没法成为一个入度为 $0$ 的点。此题可解。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define sipt //signed-input
#define sopt //signed-output
struct IO {
#define mxsz (1 << 22)
	char buf[mxsz], * p1, * p2;
	char pbuf[mxsz], * pp;
	IO() : p1(buf), p2(buf), pp(pbuf) {}
	~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
	inline char gc() {
		if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, mxsz, stdin);
		return p1 == p2 ? ' ' : *p1++;
	}
#ifndef sipt
	inline int read() {
		int r = 0; char c = gc(); while (c < '0' || c>'9') c = gc();
		while (c >= '0' && c <= '9') r = r * 10 + (c ^ 48), c = gc();
		return r;
	}
#else
	inline int read() {
		int r = 0; char c = gc(); bool rev = 0;
		while (c < '0' || c>'9') rev |= (c == '-'), c = gc();
		while (c >= '0' && c <= '9') r = r * 10 + (c ^ 48), c = gc();
		return rev ? ~r + 1 : r;
	}
#endif
	inline void push(char c) {
		if (pp - pbuf == mxsz) fwrite(pbuf, 1, mxsz, stdout), pp = pbuf;
		*pp++ = c;
	}
	inline void write(int x) {
		static char sta[22]; int top = 0;
		do sta[top++] = x % 10, x /= 10; while (x);
		while (top) push(sta[--top] ^ 48);
	}
	inline void write(int x, char opc) {
#ifdef sopt
		if (x < 0) push('-'), x = ~x + 1;
#endif
		write(x), push(opc);
	}
} io;
int n, m, a[100005], v[100005], rd[100005];
unordered_map<int, int>apt;
struct tree_array {
	int v[100005];
	inline int lb(int v) { return v & ~v + 1; }
	inline void ins(int p, int t = 1) {
		do v[p] += t; while ((p += lb(p)) <= n);
	}
	inline int que(int p) {
		int ret = 0; do ret += v[p];
		while (p -= lb(p)); return ret;
	}
}ta;
struct seg_tree {
	struct node {
		int l, r, mv, mp, tg;
	}re[100005 << 2];
	inline void pup(int p) {
		if (re[p << 1].mv <= re[p << 1 | 1].mv)
			re[p].mv = re[p << 1].mv, re[p].mp = re[p << 1].mp;
		else re[p].mv = re[p << 1 | 1].mv, re[p].mp = re[p << 1 | 1].mp;
		//大小不同选最小，大小相同选最前
	}
	inline void pud(int p) {
		if (!re[p].tg) return;
		re[p << 1].tg += re[p].tg;
		re[p << 1].mv += re[p].tg;
		re[p << 1 | 1].tg += re[p].tg;
		re[p << 1 | 1].mv += re[p].tg;
		re[p].tg = 0; //区间加不影响区间内相对大小
	}
	inline void build(int l, int r, int p) {
		re[p].l = l; re[p].r = r;
		if (l == r) return re[p].mv = rd[l], re[p].mp = l, void();
		build((l + r >> 1) + 1, r, p << 1 | 1);
		build(l, (l + r >> 1), p << 1); pup(p);
	}
	inline void chg(int l, int r, int v, int p) {
		if (re[p].l >= l && re[p].r <= r)
			return re[p].mv += v, re[p].tg += v, void();
		pud(p);
		if (l <= re[p << 1].r) chg(l, r, v, p << 1);
		if (r > re[p << 1].r) chg(l, r, v, p << 1 | 1);
		pup(p);
	}
}sgt;
signed main() {
	ios::sync_with_stdio(0); n = io.read(); m = io.read();
	for (int i = 1;i <= n;++i) v[i] = a[i] = io.read();
	sort(v + 1, v + n + 1);
	for (int i = 1;i <= n;++i)
		a[i] = lower_bound(v + 1, v + n + 1, a[i]) - v + apt[a[i]], apt[v[a[i]]]++;
	//类离散化，但是如果每一个点的编号都不一样会更好处理。
	for (int i = 1;i <= n;++i) {
		int lp = lower_bound(v + 1, v + n + 1, v[a[i]] - m) - v - 1;
		int rp = upper_bound(v + 1, v + n + 1, v[a[i]] + m) - v - 1;
		rd[a[i]] = (i - 1) + ta.que(lp) - ta.que(rp); ta.ins(a[i]);
		//求入度。写成这样会更好理解一些：(i - 1) - (ta.que(rp) - ta.que(lp))
		//总的减去不合法的。
	}
	sgt.build(1, n, 1);
	for (int i = 1;i <= n;++i) {
		int ps = sgt.re[1].mp;
		io.write(v[ps], '\n');
		sgt.chg(1, n, -1, 1);
		int lp = lower_bound(v + 1, v + n + 1, v[ps] - m) - v;
		int rp = upper_bound(v + 1, v + n + 1, v[ps] + m) - v - 1;
		sgt.chg(lp, rp, 1, 1);
		//就是所有的不在 lp 到 rp 的都可以减。这些是可达的，即不满足要求的。
		sgt.chg(ps, ps, 1145141919810, 1);
		//一定要让这个点不能再被选到
	}
}
```

---

## 作者：hegm (赞：2)

一道好题，由于当初看第一篇题解被困扰了一段时间，因此特意在此解释说明。

首先，对于一个点对 $(i,j)$ （不妨假设 $i<j$），若 $|a_i-a_j|>K$，那就意味着两者永远无法交换顺序，这启示我们进行拓扑。

在不考虑复杂度的情况下，我们可以暴力的连边 $i\to j$ 表示在 $a_i$ 放入之前 $a_j$ 绝对无法填入。

考虑优化这个过程，首先我们不妨扫描线，求出每个节点的度数，即对于 $j$，$\text{deg}_j=\sum\limits_{i<j}[|a_i-a_j|>K]$。

扫描下标，数据结构维护权值即可。

现在考虑求解答案，显然每次对于当前的开头，我们需要找到一个 $\text{deg}_j=0$，将 $a_j$ 填入当前的开头。

如果将 $j$ 填入，我们就需要将所有的和 $j$ 有连边的 $j\to i$ 的 $\text{deg}_i\ -1$。

但是这是一个二维偏序的问题，不方便动态处理，但是第一篇题解直接选择使用朴素线段树维护，这是为什么呢？

考虑和 $j$ 有连边的节点的特性，即 $|a_i-a_j|>K$，同时根据 $i,j$ 之间的大小关系确定连边方向。

但是注意到，当 $j$ 被删除的时候，所有连向他的 $i$ 也一定被删除了，而剩余的 $|a_i-a_j|>K$ 的节点一定是 $j\to i$ 的关系。

因此我们直接朴素线段树维护即可，每次找出最小值，因为一定有解，所以最小值一定是 $0$。然后线段树更新区间。

### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define make make_pair
#define pii pair<int,int>
#define N 100005
#define lb(x) (x&(-x))
#define ls (now<<1)
#define rs (now<<1|1)
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,k,a[N],bit[N],w[N],tot,deg[N],lz[N*4],ct[N],pos[N];
pii tr[N*4];
void add(int x,int w)
{
	for(;x<=n;x+=lb(x))bit[x]+=w;
}
int que(int x)
{
	int ans=0;
	for(;x>=1;x-=lb(x))ans+=bit[x];
	return ans;
}
void build(int now,int l,int r)
{
	if(l==r)
	{
		tr[now]={deg[pos[l]],a[pos[l]]};
		return ;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	tr[now]=min(tr[ls],tr[rs]);
}
void push(int now,int w)
{
	lz[now]+=w;
	tr[now].fi+=w;
}
void down(int now)
{
	push(rs,lz[now]);
	push(ls,lz[now]);
	lz[now]=0;
}
void midy(int now,int l,int r,int ql,int qr,int w)
{
	if(ql>qr)return ;
	if(l>=ql&&r<=qr)
	{
		push(now,w);
		return ;
	}
	int mid=(l+r)>>1;down(now);
	if(mid>=ql)midy(ls,l,mid,ql,qr,w);
	if(mid<qr)midy(rs,mid+1,r,ql,qr,w);
	tr[now]=min(tr[ls],tr[rs]);
}
void del(int now,int l,int r)
{
	if(l==r)
	{
		tr[now].fi=n+1;
		return ;
	}
	int mid=(l+r)>>1;down(now);
	if(tr[ls]==tr[now])del(ls,l,mid);
	else del(rs,mid+1,r);
	tr[now]=min(tr[ls],tr[rs]);
}
signed main()
{
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read(),w[i]=a[i];
	sort(w+1,w+1+n);
	for(int i=1;i<=n;i++)
	{
		int l=lower_bound(w+1,w+1+n,a[i]-k)-w;
		int r=upper_bound(w+1,w+1+n,a[i]+k)-w-1;
		a[i]=lower_bound(w+1,w+1+n,a[i])-w;
		a[i]+=ct[a[i]];ct[a[i]]++;
		pos[a[i]]=i;
		deg[i]=(i-1)-que(r)+que(l-1);
		add(a[i],1);
	}
	build(1,1,n);
	for(int i=1,l,r;i<=n;i++)
	{
		int x=tr[1].se;
		cout<<w[x]<<"\n"; 
		l=lower_bound(w+1,w+1+n,w[x]-k)-w-1;
		r=lower_bound(w+1,w+1+n,w[x]+k+1)-w;
		del(1,1,n);
		midy(1,1,n,1,l,-1);
		midy(1,1,n,r,n,-1);
	}
	return 0;
}

```

---

## 作者：Anonymely (赞：2)

注意到 $|a_i - a_j| >k$ 的两个数相对位置不能改变，考虑增量，每次插入一个数维护答案。

在 $i$ 插入一个数时，设它最后换到 $j$，则需要满足 $p \in [j,i],|a_p - a_i| \le k$，符合条件的 $j$ 是一段后缀，由于需要字典序最小，故应该在这段符合条件的后缀中选择最靠前的 $a_t > a_i$ 插入，平衡树维护即可。

[submission](https://www.luogu.com.cn/record/176615089)

---

## 作者：ZnPdCo (赞：2)

容易发现如果两个草堆绝对值超过 $k$，它们无论如何都无法交换。

也就是说，对于 $x<y$，如果有 $|h[x]-h[y]| >k$，在答案里也必定有 $x<y$。

所以从 $x$ 向 $y$ 连边，一个合法的拓扑序也是一个合法的答案。

那么题目就是要求最小的拓扑序。

对于这种具有重复值的最小拓扑序似乎是不可做的，但是我们可以挖掘性质。

在这一题中，我们可以发现如果有 $h[x]=h[y],x<y$，那么 $y$ 的出边一定是 $x$ 出边的子集。也就是说，选择 $y$ 能去的点选择 $x$ 一定能去，选择 $x$ 能去的点选择 $y$ 不一定能去。所以选择 $x$ 会更优。

所以说，我们可以使用优先队列，以 $h$ 为第一关键字，在 $h$ 相同的情况下，优先选下标小的。

另外，发现这道题的点有点多，可以使用可持久化线段树优化建图。对于每一个 $i$ 建一个只有下标为 $(i,n]$ 这些点的线段树版本，然后每次连值域在 $[1,h-k)$ 与 $(h+k,\inf)$ 的边就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100010
ll n, k, tot, rt;
ll h[N], h2a[N];
struct node {
	ll val, Id;
	node(ll a=0,ll b=0):val(a), Id(b) {}
} a[N];
ll ls[N * 100], rs[N * 100];
ll head[N * 100], nxt[N * 100], to[N * 100], cnt, in[N * 100];
void addEdge(ll u, ll v) {
	cnt ++;
	to[cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
	
	in[v] ++;
}
void build(ll l, ll r, ll &pos) {
	pos = ++ tot;
	if(l == r) {
		addEdge(pos, a[l].Id);
		return;
	}
	ll mid = (l + r) >> 1;
	build(l, mid, ls[pos]);
	build(mid + 1, r, rs[pos]);
	addEdge(pos, ls[pos]);
	addEdge(pos, rs[pos]);
}
void update(ll x, ll l, ll r, ll &pos) {
	ls[++ tot] = ls[pos];
	rs[tot] = rs[pos];
	pos = tot;
	if(l == r) {
		return;
	}
	ll mid = (l + r) >> 1;
	if(x <= mid)
		update(x, l, mid, ls[pos]);
	if(mid < x)
		update(x, mid + 1, r, rs[pos]);
	addEdge(pos, ls[pos]);
	addEdge(pos, rs[pos]);
}
void link(ll x, ll nl, ll nr, ll l, ll r, ll pos) {
	if(nl <= l && r <= nr) {
		addEdge(x, pos);
		return;
	}
	ll mid = (l + r) >> 1;
	if(nl <= mid) {
		link(x, nl, nr, l, mid, ls[pos]);
	}
	if(mid < nr) {
		link(x, nl, nr, mid + 1, r, rs[pos]);
	}
}
auto cmp = [](const node &x, const node &y) {
	return x.val < y.val;
};
int main() {
	freopen("minimizing.in", "r", stdin);
	freopen("minimizing.out", "w", stdout);
	scanf("%lld %lld", &n, &k);
	for(ll i = 1; i <= n; i ++) {
		scanf("%lld", &h[i]);
		a[i].val = h[i];
		a[i].Id = i;
	}
	tot = n;
	sort(a + 1, a + 1 + n, cmp);
	build(1, n, rt);
	for(ll i = 1; i <= n; i ++) {
		h2a[a[i].Id] = i;
	}
	for(ll i = 1; i <= n; i ++) {
		update(h2a[i], 1, n, rt);
		ll L = lower_bound(a + 1, a + 1 + n, node(h[i] - k, 0), cmp) - a - 1,
		   R = lower_bound(a + 1, a + 1 + n, node(h[i] + k + 1, 0), cmp) - a;
		if(1 <= L) link(i, 1, L, 1, n, rt);
		if(R <= n) link(i, R, n, 1, n, rt);
		L = lower_bound(a + 1, a + 1 + n, node(h[i], 0), cmp) - a,
		R = upper_bound(a + 1, a + 1 + n, node(h[i], 0), cmp) - a - 1;
		link(i, L, R, 1, n, rt);
	}
	
	priority_queue<pair<ll, ll> > q;
	
	for(ll i = 1; i <= tot; i ++) {
		if(in[i] == 0) {
			if(i <= n) q.push(make_pair(- h[i], i));
			else q.push(make_pair(1e9, i));
		}
	}
	
	while(!q.empty()) {
		ll u = q.top().second;
//		printf("now: %lld\n", u);
		q.pop();
		if(u <= n) printf("%lld\n", h[u]);
		for(ll i = head[u]; i; i = nxt[i]) {
			ll v = to[i];
			in[v] --;
			if(in[v] == 0) {
				if(v <= n) q.push(make_pair(- h[v], v));
				else q.push(make_pair(1e9, v));
			}
		}
	}
}
```

---

## 作者：Little09 (赞：2)

提供一个无脑做法。是目前最劣解……

考虑两个草堆 $x,y$ 若满足 $x<y$ 且 $|h_x-h_y|>K$，那么显然无论怎么交换 $x$ 永远在 $y$ 前面。因此我们对于每一个这样的 $x,y$，从 $x$ 向 $y$ 连边。

答案应该是建出的图的最小字典序（权值是 $h$）的拓扑序。这样很明显是 $n^2$ 的算法，我们考虑优化建图。

考虑绝对值拆开。考虑按照 $h$ 的大小依次把每个点加入线段树，于是对于 $y$ 这个点加边的时候，只要考虑前面某棵线段树（满足所有 $h_i<h_y-K$）的区间 $[1,y]$ 加边就行了。可以用 lower_bound 找到这棵线段树。

这里我就写了主席树。当然由于绝对值，反过来也要跑一遍。于是建完图跑一下拓扑序就行了。

时间复杂度应当是 $O(n\log n)$ 的，但是常数似乎巨大。

---

## 作者：DYYqwq (赞：1)

模拟赛题，但是挂了 $80$ 分，气死我了。

考虑对于一个数 $a_i$ 的可能移动范围 $[l,r]$，需要满足 $\forall j \in [l,r],|a_i-a_j| \leq k$。我们一定是一直把 $a_i$ 往左移，而非右移，因为左移显然不劣。我们考虑应当让 $a_i$ 移动到哪里：这个点 $p$ 一定 $\in [l,i)$，并且 $a_p > a_i$，毕竟你要求字典序最小嘛！

于是我们考虑如何找到我们的左端点 $l$ 和 $p$ 呢？考虑使用线段树维护区间最大最小值，并且使用二分配合线段树查找。

我们每次对于一个新的 $i$ 找到它的 $p$ 以后，可以在 $p$ 那一位的答案中加入 $i$，这里存储答案的东西应该是 `multiset` 而非 `set`，这就是我挂分的原因。

分析复杂度发现是 $O(n \log^2 n)$。一秒内随便跑。

```cpp
#include<bits/stdc++.h>
#define lson(root) (root << 1)
#define rson(root) ((root << 1) | 1)
using namespace std;
struct node
{
	int mn , mx;
}tree[400010];
int n , k , h[100010];
multiset<int> ans[100010];
void pushup(int root)
{
	tree[root].mn = min(tree[lson(root)].mn , tree[rson(root)].mn);
	tree[root].mx = max(tree[lson(root)].mx , tree[rson(root)].mx);
}
void update(int root , int l , int r , int x , int mn , int mx)
{
	if(l == r)
	{
		tree[root].mn = mn , tree[root].mx = mx;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) update(lson(root) , l , mid , x , mn , mx);
	else update(rson(root) , mid + 1 , r , x , mn , mx);
	pushup(root);
}
int query_mn(int root , int l , int r , int L , int R)
{
	if(L <= l && R >= r) return tree[root].mn;
	int mid = (l + r) >> 1 , ans = INT_MAX;
	if(L <= mid) ans = min(ans , query_mn(lson(root) , l , mid , L , R));
	if(R > mid) ans = min(ans , query_mn(rson(root) , mid + 1 , r , L , R));
	return ans; 
}
int query_mx(int root , int l , int r , int L , int R)
{
	if(L <= l && R >= r) return tree[root].mx;
	int mid = (l + r) >> 1 , ans = INT_MIN;
	if(L <= mid) ans = max(ans , query_mx(lson(root) , l , mid , L , R));
	if(R > mid) ans = max(ans , query_mx(rson(root) , mid + 1 , r , L , R));
	return ans;
}
//void build(int root )
int main()
{
// 	freopen("hay.in" , "r" , stdin);
// 	freopen("hay.out" , "w" , stdout);
	scanf("%d%d" , &n , &k);
	int x;
	scanf("%d" , &x);
	update(1 , 1 , n , 1 , x , x);
	int pos = 1;
	ans[pos].insert(x);
	for(int i = 1 ; i < n ; i ++)
	{
		int x;
		scanf("%d" , &x);
		int lft = pos + 1 , l = 1 , r = pos;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			int mx = query_mx(1 , 1 , n , mid , pos) , mn = query_mn(1 , 1 , n , mid , pos);
			if(mn + k < x || mx - k > x) l = mid + 1;
			else lft = min(lft , mid) , r = mid - 1;
		}
		if(lft == pos + 1) // 这玩意没动 说明需要新的 pos 
		{
			pos ++;
			ans[pos].insert(x);
			update(1 , 1 , n , pos , x , x);
			continue; 
		}
		l = lft , r = pos;
		int lf = pos + 1;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			int mx = query_mx(1 , 1 , n , lft , mid);
			if(mx <= x) l = mid + 1;
			else lf = min(lf , mid) , r = mid - 1;
		}
		if(lf == pos + 1) // 完全同理 
		{
			pos ++;
			ans[pos].insert(x);
			update(1 , 1 , n , pos , x , x);
			continue;
		}
		ans[lf].insert(x);
//		auto it_mn = ans[lf].begin() , it_mx = ans[lf].end();
//		it_mx --;
//		int mn = *it_mn , mx = *it_mx;
		int mn = *ans[lf].begin() , mx = *ans[lf].rbegin(); // 这里不知道为什么需要这么写，不会 stl。
		if(x == mn) // 这东西恰好是最优解
			update(1 , 1 , n , lf , x , mx); // 最小是最小，最大是最大 
	}
	for(int i = 1 ; i <= pos ; i ++) for(int j : ans[i]) printf("%d\n" , j);
	return 0;
}
```

---

## 作者：Rain_chr (赞：1)

因为前几天考了 CF1895E，所以这是根据那题独立想出来的奇妙做法。

首先会有很显然的 $O(n^2)$ 做法，对于两个位置 $i,j$，若有 $i<j$ 且 $|a_i-a_j|>k$，那么 $i$ 就向 $j$ 连边，答案即为这个图的最小拓扑序。

考虑怎么优化，我们可以发现，越是极值越不容易入度为 $0$，也就是说，如果极值都入度为 $0$ 了，其他的数一定都入度为 $0$ 了。

所以，我们只用考虑每个位置前的最大值和最小值，如果的确交换不了，那就向当前位置连边。

本来这样就可以过了，但貌似有人 Hack 掉了。我看了看原因，上述思路是没有问题的，但是当前面的数都入度为 $0$ 时，后面的数可能会提前被更新到，因此会提前入队，导致出错。

所以只用再多连一条边：每个位置之前最后一个无法和当前位置交换的向当前位置连边。并且只用考虑大于当前位置的，因为如果全都是小于当前位置的，即使提前入队也不会被拿出来。

可能有更简单的做法，我还是用了线段树维护。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N];
vector<int> g[N];
int in[N];
int t[N<<5],lt[N<<5],rt[N<<5];
int cnt;
void update(int &x,int l,int r,int pos,int v)
{
    if(!x) x=++cnt;
    if(l==r) t[x]=v;
    else
    {
        int mid=(l+r)>>1;
        if(pos<=mid) update(lt[x],l,mid,pos,v);
        else update(rt[x],mid+1,r,pos,v);
        t[x]=max(t[lt[x]],t[rt[x]]);
    }
}
int query(int x,int l,int r,int L,int R)
{
    if(!x) return 0;
    if(L<=l&&r<=R) return t[x];
    else
    {
        int mid=(l+r)>>1,k=0;
        if(L<=mid) k=max(k,query(lt[x],l,mid,L,R));
        if(mid+1<=R) k=max(k,query(rt[x],mid+1,r,L,R));
        return k;
    }
}
int root;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    int p1=1,p2=1;
    update(root,1,1e9,a[1],1);
    for(int i=2;i<=n;i++)
    {
        if(a[i]-a[p1]>k) g[p1].push_back(i),in[i]++;
        if(a[p2]-a[i]>k) g[p2].push_back(i),in[i]++;
        int p=query(root,1,1e9,a[i]+k+1,1e9);
        if(p) g[p].push_back(i),in[i]++;
        if(a[i]<=a[p1]) p1=i;
        if(a[i]>=a[p2]) p2=i;
        update(root,1,1e9,a[i],i);
    }
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
    for(int i=1;i<=n;i++)
        if(!in[i])
            q.push(make_pair(a[i],i));
    while(q.size())
    {   
        int x=q.top().second;
        q.pop();
        cout<<a[x]<<'\n';
        for(int to:g[x])
        {
            in[to]--;
            if(!in[to]) q.push(make_pair(a[to],to));
        }
    }
    return 0;
}
```


---

## 作者：comcopy (赞：1)

很容易想到对于一个数 $a_i$，我们找到前面的第一个数 $a_j(\operatorname{abs}(a_i-a_j)>k)$，对于 $j\sim i$ 这段区间内 $a_i$ 是可以在任意位置的。

考虑贪心，即找到区间 $j\sim i$ 内最左边第一个大于 $a_i$ 的数，将 $a_i$ 插入在该数最前面可以使当前的序列字典序最小。

显然需要以下两个功能：

- 区间最值。
- 单点插入。

考虑使用分块来维护，对于每次插入一个点，从最右边的点暴力往左搜到第一个不可以交换的位置，在从这个位置开始暴力往左扫找到第一个大于当前点的位置，插入。

再定期重构防止爆块就行。

事实上就是模拟最上面的个暴力。


```cpp
#include<bits/stdc++.h>
//#define int long long
#define mi(...) <%__VA_ARGS__%>
using namespace std;
namespace Faster {
inline bool _u(char ch) { return ch >= '0' && ch <= '9'; }
//char buf[1 << 23], *p1 = buf, *p2 = buf;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++)
inline int read() {int x = 0, f = 1;char ch = getchar();for (; !_u(ch); ch = getchar())if (ch == '-')f = -f;for (; _u(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);return x * f;}
inline void write(int num) {static int sta[39], top = 0;if (num < 0)putchar('-'), num *= -1;do sta[++top] = num % 10, num /= 10;while (num);while (top) putchar(sta[top--] | 48);return;}
}using namespace Faster;
const int N=1e5+5;
int n,k,cnt,a[N],b[N],S,ma[N],mi[N];
vector<int> v[N];
inline void init(){
	int tot=0;
	for(int i=1;i<=cnt;++i){
		for(int j=0;j<v[i].size();++j)
			b[++tot]=v[i][j];
		v[i].clear();
	}
	memset(ma,-0x3f,sizeof ma);
	memset(mi,0x3f,sizeof mi);
	for(int i=1;i<=tot;++i){
		v[(i-1)/S+1].push_back(b[i]);
		ma[(i-1)/S+1]=max(ma[(i-1)/S+1],b[i]);
		mi[(i-1)/S+1]=min(mi[(i-1)/S+1],b[i]);
	}
	cnt=(tot-1)/S+1;
	return;
}
inline void add(int x,int c){
	for(int i=1;i<=cnt;++i){
		if(v[i].size()<x) x-=v[i].size();
		else{
			v[i].insert(v[i].begin()+x,c);
			ma[i]=max(ma[i],c);
			mi[i]=min(mi[i],c);
			break;
		}
	}
	return;
}
inline int fnd(int x,int c){
	for(int i=cnt;i>=1;--i){
		if(abs(ma[i]-c)>k||abs(mi[i]-c)>k)
			for(int j=v[i].size()-1;j>=0;j--)
				if(abs(v[i][j]-c)>k||abs(v[i][j]-c)>k)return x;
				else
				--x;
		x-=v[i].size();
	}
	return x;
}
inline int query1(int x,int c){
	int now=0;
	for(int i=1;i<=cnt;i++){
		if(now+v[i].size()>=x&&ma[i]>c){
			for(int j=0;j<v[i].size();j++){
				now++;
				if(now>=x&&v[i][j]>c)return now-1;
			}
			now-=v[i].size();
		}
		now+=v[i].size();
	}
	return now;
}
int main(){
	n=read(),k=read();
	S=sqrt(n);
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++){
		if((i-1)%S==0)init();
		int now=query1(fnd(i-1,a[i])+1,a[i]);
		add(now,a[i]);
	}
	for(int i=1;i<=n;++i)
		for(int j:v[i])
			write(j),puts("");
	return(0-0);
}
```

---

