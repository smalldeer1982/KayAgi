# 「chaynOI R1 T3」镍铬合金机器人

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/wv3r15c6.png)


## 题目描述

给定一个长为 $n$ 的序列 $bot$。

有 $q$ 次询问，每次给出三个数 $l,x,y$，请你求出有多少个以 $l$ 为左端点的区间 $[l,r]$（$l\le r$）使得 $\text{mex}(\{bot_l,bot_{l+1},\cdots,bot_r\})\in[x,y]$。

注：一个可重集合 $S$ 的 $\text{mex}$ 函数 $\text{mex}(S)$ 指的是**最小**的没有在 $S$ 中出现过的**非负整数**，如 $\text{mex}(\{0,1,1,3\}) = 2$。 

## 说明/提示

对于 $100\%$ 的数据，$1\le n,q \le 3\times 10^5$，$0\le bot_i < n$，$0\le x \le y \le n$，$1 \le l\le n$。

**本题采用捆绑测试。**

+ Subtask 1(10pts)：$n,q\le 300$。
+ Subtask 2(15pts)：$n,q\le 2000$。
+ Subtask 3(15pts)：$bot_i \le 1$。
+ Subtask 4(20pts)：$x=y$。
+ Subtask 5(40pts)：无特殊限制。

## 样例 #1

### 输入

```
4 2
0 1 3 2
1 2 2
2 1 4```

### 输出

```
2
0```

## 样例 #2

### 输入

```
10 10
0 0 1 1 1 0 0 1 0 1
1 0 0
2 0 1
3 1 2
4 0 1
5 0 2
6 0 1
7 1 1
8 2 2
9 0 0
10 1 2
```

### 输出

```
0
1
5
2
6
2
1
2
0
0
```

# 题解

## 作者：_Yonder_ (赞：6)

简单题。

考虑对 $l$ 从大到小扫描线，维护一个数组 $a$，每次把 $a_{bot_i}$ 修改为 $i$。

注意到从 $l$ 开始一直到 $n$，$\text{mex}$ 是单调递增的，那么我们只需要求出第一次 $\text{mex}\ge x$ 和第一次 $\text{mex}>y$，显然分别为 $\displaystyle\max_{0\le i<x}a_i,\displaystyle\max_{0\le i\le y}a_i$。

用线段树维护 $a$ 数组即可。

---

## 作者：grape_king (赞：2)

## 前言
菜鸟只会比较简单的双 $\log$ 写法，单 $\log$ 暂时不会，用的是整体二分加主席树查询区间 $\operatorname{mex}$ 的方法。

## 题意
给你一个长度为 $n$ 的数组 $a$，每次询问给你三个整数 $l,x,y$，问你以 $l$ 为左端点，找到有多少个 $r$ 能够满足区间 $[l,r]$ 的 $\operatorname{mex}$ 在 $x$ 和 $y$ 之间。

其中区间 $\operatorname{mex}$ 可以通过主席树来实现或者用离散化线段树来实现，另外怎么求解这个满足要求的 $r$ 的数目呢？可以发现如果左端点 $l$ 固定，当区间的右端点 $r$ 不断变大，就会使得 $\operatorname{mex}$ 的值也越来越大，具有递增的单调性，很明显可以通过二分实现这一部分，但是我加上二分就超时了，估计是用的主席树来查询的，常数大些，如果用离散化加线段树，应该是可以直接二分过的，不过我们可以通过整体二分的方法来对整个查询进行整体处理，这样就会优化些常数，时间复杂度为 $O(n\log n+q\log^2 n)$，可能这个双 $\log$ 常数会更少些。

另外区间 $\operatorname{mex}$ 模版题传送门为 [P4137](https://www.luogu.com.cn/problem/P4137)。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
typedef pair<int, int> pi;
typedef pair<i64, i64> PI;

struct node {
    int l, r;
    int mn;
    node(int l = 0, int r = 0, int mn = 0) : l(l), r(r), mn(mn) {}
};
int tot, n, q;
int a[300005], rt[300005], val[300005], ans[300005];
node tr[300005 * 20];
vector<int> g[300005];
vector<array<i64, 3>> mp[300005];

void push_up(int root) {
    auto l = tr[root].l, r = tr[root].r;
    tr[root].mn = min(tr[l].mn, tr[r].mn);
}

void ins(int &p, int bf, int l, int r, int k, int pos) {
    p = ++tot;
    tr[p] = tr[bf];
    int mid = l + r >> 1;
    if (l == r) {
        tr[p].mn = pos;
        return;
    }
    if (k <= mid) ins(tr[p].l, tr[bf].l, l, mid, k, pos);
    else ins(tr[p].r, tr[bf].r, mid + 1, r, k, pos);
    push_up(p);
}

int query(int p, int l, int r, int k) {
    int mid = l + r >> 1;
    if (l == r) {
        return l;
    }
    if (tr[tr[p].l].mn < k) {
        return query(tr[p].l, l, mid, k);
    } else {
        return query(tr[p].r, mid + 1, r, k);
    }
}

void sol(int idx, int L, int R, int l, int r) {// 整体二分
    if (l > r) return;
    int mid = L + R >> 1;
    int v = query(rt[mid], 0, n, idx);
    if (L == R) {
        for (int i = l; i <= r; i++) {
            int it = g[idx][i];
            if (v <= it) {
                val[it] = L;
            } else {
                val[it] = L - 1;
            }
        }
        return;
    }
    auto it = lower_bound(g[idx].begin() + l, g[idx].begin() + r + 1, v) - g[idx].begin() - 1;
    sol(idx, L, mid, l, it);
    sol(idx, mid + 1, R, it + 1, r);
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ins(rt[i], rt[i - 1], 0, n, a[i], i);
    }
    vector<array<int, 4>> st;
    for (int i = 1; i <= q; i++) {
        int l, x, y;
        cin >> l >> x >> y;
        st.push_back({l, x, y, i});
    }
    sort(st.begin(), st.end());
    for (auto [l, x, y, id] : st) {
        mp[l].push_back({x, y, id});
        g[l].push_back(x - 1);
        g[l].push_back(y);
    }
    for (int l = 1; l <= n; l++) {
        if (g[l].empty()) continue;
        sort(g[l].begin(), g[l].end());
        g[l].erase(unique(g[l].begin(), g[l].end()), g[l].end());
        int m = g[l].size();
        sol(l, l, n, 0, m - 1);
        for (auto &[x, y, id] : mp[l]) {
            ans[id] = max(0, val[y] - val[x - 1]);
        }
    }
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int _ = 1;
    // std::cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}
```

---

## 作者：Laisira (赞：2)

### 思路
首先求出以 $1$ 为 $l$ 的所有区间的 $\mathrm{mex}$，这个可以用 set 维护一下没有出现过的最小值，接下来把左端点右移，对全局的影响即在后一个相同数字之前的右端点的区间 $\mathrm{mex}$ 与其取最小值，线段树维护区间最小值即可。最后把询问离线下来，发现左端点相同每次移动右端点后面的答案一定是不减的（证明很简单，没有出现的数集不会新加进数），直接在线段树上二分即可，时间复杂度 $O(q\log n)$。

---

## 作者：CaiZi (赞：2)

定义 $\text{mex}^*(l,r)=\text{mex}(\{bot_l,\cdots,bot_r\})$，$\text{max}^*(l,r)=\text{max}(\{t_l,\cdots,t_r\})$，其中 $t$ 在后文出现。

首先我们发现，当 $l$ 固定时，将 $r$ 左移，此时进行 $\text{mex}$ 运算的数字减少一个，答案肯定变小或不变，将 $r$ 右移，此时进行 $\text{mex}$ 运算的数字增加一个，答案肯定变大或不变。所以 $\text{mex}^*(l,r)\in[x,y]$ 的 $r$ 是有单调性的，一定是在一个区间 $[p_1,p_2]$ 中。

于是我们问题变成了：给定 $l,x,y$，求最小的满足 $\text{mex}^*(l,p_1)\ge x$ 的 $p_1$，和最大的满足 $\text{mex}^*(l,p_2)\le y$ 的 $p_2$，答案就是 $p_2-p_1+1$。

考虑将询问离线，按照 $l$ 从大到小排序，记上个处理的 $l$ 为 $l'$，初始为 $n+1$。每次询问加入 $a_l\sim a_{l'-1}$，此时每次询问求的就是全部加入的数的 $p_1,p_2$。考虑使用权值线段树，$t_i$ 表示当前数字 $i$ 最早出现的位置，初始时 $t_i=n+1$。因为若想要 $\text{mex}^*(l,p_1)\ge x$，至少需要令 $0\sim x-1$ 各出现一次。所以最小的满足 $\text{mex}^*(l,p_1)\ge x$ 的 $p_1$ 为 $\max^*(0,x-1)$。最小的满足 $\text{mex}^*(l,p_3)\le y+1$ 的 $p_3$ 为 $\max^*(0,y)$，最大的满足 $\text{mex}^*(l,p_2)\le y$ 的 $p_2$ 为 $\max^*(0,y)-1$。

时间复杂度 $O(q\log n+n\log n)$。

代码展示：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int c,f,x,y;
}b[300001];
int n,m,k,a[300001],s[300001],t[1200001];
inline void update(int u,int v,int s=1,int l=0,int r=n-1){
	if(l==r){
		t[s]=v;
	}
	else{
		if(u<=(l+r>>1)){
			update(u,v,s<<1,l,(l+r>>1));
		}
		else{
			update(u,v,s<<1|1,(l+r>>1)+1,r);
		}
		t[s]=max(t[s<<1],t[s<<1|1]);
	}
}
inline int query(int u,int v,int s=1,int l=0,int r=n-1){
	if(u<=l&&r<=v){
		return t[s];
	}
	else{
		int w=-1;
		if(u<=(l+r>>1)){
			w=max(w,query(u,v,s<<1,l,(l+r>>1)));
		}
		if(v>(l+r>>1)){
			w=max(w,query(u,v,s<<1|1,(l+r>>1)+1,r));
		}
		return w;
	}
}
inline bool cmp(node u,node v){
	return u.f>v.f;
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>n>>m;
	k=n+1;
	for(int i=0;i<=n-1;i++){
		update(i,n+1);
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i].f>>b[i].x>>b[i].y;
		b[i].c=i;
	}
	sort(b+1,b+m+1,cmp);
	for(int i=1;i<=m;i++){
		while(k>b[i].f){
			k--;
			update(a[k],k);
		}
		if(b[i].x==0){
			s[b[i].c]=query(0,b[i].y)-b[i].f;
		}
		else{
			s[b[i].c]=query(0,b[i].y)-query(0,b[i].x-1);
		}
	}
	for(int i=1;i<=m;i++){
		cout<<s[i]<<'\n';
	}
	return 0;
}
```

---

## 作者：SamHJD (赞：1)

固定左端点为 $l$，右端点 $r$ 向右移动时，$\text{mex}$ 单调不降。因此对于一个询问，合法的 $r$ 一定对应一个区间，只需找出区间的左右端点，即 $\text{mex}$ 等于 $x$ 的第一个位置和 $\text{mex}$ 等于 $y$ 的最后一个位置。

对于询问 $(l,x,y)$，$\text{mex}$ 等于 $x$ 的第一个位置即为 $[0,x-1]$ 在 $[l,n]$ 中第一次出现位置的最大值，$\text{mex}$ 等于 $y$ 的最后一个位置即 $\text{mex}$ 等于 $y+1$ 的第一个位置减一。

维护一棵值域线段树，支持单点修改区间查询最大值，离线询问按 $l$ 升序处理，动态修改每个值在当前后缀区间的第一次出现的位置，$(l,x,y)$ 的答案即为线段树上 $[0,y]$ 的最大值减 $[0,x-1]$ 的最大值。

实现时未出现的数在线段树上的值可以赋成 $n+1$。

```cpp
#include <bits/stdc++.h>
#define rep(i,k,n) for(int i=k;i<=n;++i)
#define per(i,n,k) for(int i=n;i>=k;--i)
using namespace std;
template<typename T>
inline void read(T &x){
    x=0;int f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c-'0');
    x*=f;
}
template<typename T,typename ...Args>
inline void read(T &x,Args &...rest){read(x);read(rest...);}
const int N=3e5+10;
int n,q,a[N];
struct node{
    int l,x,y,id;
}ask[N];
bool cmp(node a,node b){return a.l<b.l;}
namespace SGT{
    #define ls p*2
    #define rs p*2+1
    int mx[N*4];
    void init(){memset(mx,0,sizeof(mx));}
    void upd(int p,int l,int r,int x,int k){
        if(l==r) return mx[p]=k,void();
        int mid=(l+r)>>1;
        if(x<=mid) upd(ls,l,mid,x,k);
        else upd(rs,mid+1,r,x,k);
        mx[p]=max(mx[ls],mx[rs]);
    }
    int query(int p,int l,int r,int nl,int nr){
        // printf("%d %d %d\n",p,l,r);
        if(nl<=l&&r<=nr) return mx[p];
        int res=0,mid=(l+r)>>1;
        if(nl<=mid) res=max(res,query(ls,l,mid,nl,nr));
        if(nr>mid) res=max(res,query(rs,mid+1,r,nl,nr));
        return res;
    }
}
vector<int> pos[N];
int now[N],ans[N];
void del(int x){
    now[a[x]]++;
    if(now[a[x]]==pos[a[x]].size()) SGT::upd(1,0,n,a[x],n+1);
    else SGT::upd(1,0,n,a[x],pos[a[x]][now[a[x]]]);
}
int main(){
    read(n,q);
    rep(i,1,n) read(a[i]),pos[a[i]].push_back(i);
    rep(i,1,q) read(ask[i].l,ask[i].x,ask[i].y),ask[i].id=i;
    sort(ask+1,ask+q+1,cmp);
    ask[0].l=1;
    rep(i,0,n){
        if(!pos[i].size()) SGT::upd(1,0,n,i,n+1);
        else SGT::upd(1,0,n,i,pos[i][0]); 
    }
    rep(i,1,q){
        rep(j,ask[i-1].l,ask[i].l-1) del(j);
        int x=ask[i].x,y=ask[i].y;
        int L=ask[i].l;if(x!=0) L=SGT::query(1,0,n,0,x-1);
        int R=SGT::query(1,0,n,0,y);
        ans[ask[i].id]=R-L;
    }
    rep(i,1,q) printf("%d\n",ans[i]);
    return 0;  
}
```

---

## 作者：_zuoqingyuan (赞：1)

感觉蛮有意思的，就切了。

# 思路分析

记 $\text{mex}(l,r)$ 表示 $\text{mex}\{bot_l,bot_{l+1},\dots,bot_{r-1},bot_r\}$。

容易发现，当左端点 $l$ 固定是，随着右端点 $r$ 的值增大，区间 $\text{mex}(l,r)$ 一定不减。

由上面的性质可得：记 $L$ 为第一个满足 $\text{mex}(l,L)\ge x$ 的位置，$R$ 为第一个满足 $\text{mex}(l,R)\ge y+1$ 的位置，则对于任意 $r\in [L,R)$，都满足 $\text{mex}(l,r)\in [x,y]$。

好的，我们现在要快速求解：如何找到第一个满足 $[l,p]\ge x$ 的位置 $p(p\ge l)$。根据定义，如果 $\text{mex}(l,r)\ge x$，则只需要对于任何 $i\in [0,x-1]$ 都在 $[l,r]$ 中出现过。

我们把询问离线，倒着跑一遍扫描线，假设当前扫到了第 $l$ 个位置，此时数组 $v_i$ 上维护的是 $i$ 在 $[l,n]$ 内第一次出现的下标（若没出现过则为 $\infty$）。则查询第一个 $[l,p]\ge x$ 的位置 $p$ 即等于 $\max_{i=0}^{x-1}v_i$。

整个扫描线的过程需要支持对 $v$ 数组的单点修改和前缀最大值，显然用树状数组就可以完成，但我还是脑抽写了线段树。注意处理一些特殊的情况（如左右边界为正无穷之类的）。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define ls (p<<1)
#define rs (p<<1|1)
using namespace std;
const int N=3e5+10,inf=1e9+7;
inline void read(int &x){
	x=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	x*=f;return; 
}
int a[N],n,ans[N],tot,m;
struct node{int x,y,id;};
vector<node>v[N];
struct sgt{
	int mx[N<<2];
	void push_up(int p){
		mx[p]=max(mx[ls],mx[rs]);
	}
	void init(int p,int l,int r){
		mx[p]=inf;if(l==r)return;
		int mid=(l+r)>>1;
		init(ls,l,mid),init(rs,mid+1,r);
	}
	void change(int p,int l,int r,int x,int v){
		if(l==r){mx[p]=v;return;}
		int mid=(l+r)>>1;
		if(x<=mid)change(ls,l,mid,x,v);
		if(x>mid)change(rs,mid+1,r,x,v);
		push_up(p);
	}
	int ask(int p,int l,int r,int L,int R){
		if(L<=l&&r<=R)return mx[p];
		int mid=(l+r)>>1,cnt=-inf;
		if(L<=mid)cnt=max(cnt,ask(ls,l,mid,L,R));
		if(R>mid)cnt=max(cnt,ask(rs,mid+1,r,L,R));
		return cnt;
	}
}tr;
int main(){
	read(n),read(m);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1,l,x,y;i<=m;i++){
		scanf("%d %d %d",&l,&x,&y);
		v[l].push_back(node{x,y,i});
	}
	tr.init(1,0,n);
	for(int i=n,pos=0,L,R;i>=1;i--){
		tr.change(1,0,n,a[i],i);
		for(auto p:v[i]){
			L=(p.x==0?i:tr.ask(1,0,n,0,p.x-1));
			R=min(tr.ask(1,0,n,0,p.y),n+1);
            if(L==inf)ans[p.id]=0;
            else ans[p.id]=R-L;//注意特判一些情况
		} 
	}
	for(int i=1;i<=m;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
} 
```

时间复杂度 $O((n+q)\log n)$。

如有错误，请指出。

---

## 作者：CuFeO4 (赞：1)

挺不错的扫描线题。

将所有询问离线挂到 $l$ 上，从大到小枚举 $l$ 做扫描线。

显然有 $\operatorname{mex}$ 是单调不降的，那么直接二分加上线段树求区间 $\operatorname{mex}$ 就是 $log^2n$ 的。

但是太 naive 了，能不能再给力一点呢？

由于 $\operatorname{mex}$ 是单调不降的，那么对于一个询问 $[l,x,y]$，只需要求出第一个 $\operatorname{mex}\le x$ 的位置 $p_1$ 和第一个 $\operatorname{mex} > y$ 的位置 $p_2$ 即可。

假设当前扫到了 $l$，记 $a_i$ 表示 $l\sim n$ 中，$i$ 第一次出现的位置，如果没有，记为 $n+1$，显然有 $p_1=\max\limits_{i=0}^{x-1}a_{i}$，$p_2=\max\limits_{i=0}^ya_{i}$，这个东西用线段树维护就行。答案就是 $p_2-p_1$。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t,p) for(int i = s;i <= t;i += p)
#define drep(i,s,t,p) for(int i = s;i >= t;i -= p)
#ifdef LOCAL
  auto I = freopen("in.in","r",stdin),O = freopen("out.out","w",stdout);
#else
  auto I = stdin,O = stdout;
#endif
using ll = long long;using ull = unsigned long long;
using db = double;using ldb = long double;
const int N = 3e5 + 10;
int n,m,a[N],ans[N];
struct Segment_Tree{
  int t[N<<2];
  void B(int k = 1,int l = 0,int r = n){
    t[k] = n + 1;
    if(l == r) return;
    int mid = (l + r) >> 1;
    B(k<<1,l,mid);B(k<<1|1,mid+1,r);P(k);
  }
  void P(int k){t[k] = max(t[k<<1],t[k<<1|1]);}
  void upd(int p,int v,int k = 1,int l = 0,int r = n){
    if(l == r) return t[k] = v,void();
    int mid = (l + r) >> 1;
    p <= mid?upd(p,v,k<<1,l,mid):upd(p,v,k<<1|1,mid+1,r);
    P(k);
  }
  int qry(int ql,int qr,int k = 1,int l = 0,int r = n){
    if(ql > qr) return n;
    if(ql <= l && r <= qr) return t[k];
    int mid = (l + r) >> 1,res = 0;
    if(ql <= mid) res = max(res,qry(ql,qr,k<<1,l,mid));
    if(qr > mid) res = max(res,qry(ql,qr,k<<1|1,mid+1,r));
    return res;
  }
}sgt;
struct node{int id,x,y;node(){};node(int I,int X,int Y):id(I),x(X),y(Y){};};
vector<node> q[N];
signed main(){
  cin.tie(nullptr)->sync_with_stdio(false);
  cin>>n>>m;rep(i,1,n,1) cin>>a[i];
  rep(i,1,m,1){int l,x,y;cin>>l>>x>>y;q[l].emplace_back(i,x,y);}
  sgt.B();
  drep(now,n,1,1){
    sgt.upd(a[now],now);
    for(auto &[id,x,y]:q[now])
      ans[id] = sgt.qry(0,y) - (x-1 >=0?sgt.qry(0,x-1):now);
  }
  rep(i,1,m,1) cout<<max(ans[i],0)<<'\n';
}
```

---

## 作者：luckyqwq (赞：1)

# 「chaynOI R1 T3」镍铬合金机器人 题解

### 大致思路：

建立一棵主席树，值域是 $[1,n+1]$。（所有键值默认 $+1$）。可以发现值 $> n$ 的，对最终答案不会有影响，因为前面 $1\sim n$ 没法铺满。于是倒着循环，建立权值线段树，每个点维护区间内最大出现时间 $maxn$，初始化为 $n+1$。

考虑 $\text{mex}$ 的变化，发现随着右端点增大，左端点不变，$\text{mex}$ 是单调不减的。设 $p1=$ 使得区间 $\text{mex}\ge y+1$ 的最小 $r$ 的值，$p2=$ 使得区间  $\text{mex}\ge x$ 的最小 $r$ 的值。于是答案为 $(p1-1)-p2+1$。要让 $[l,r]$ 的 $\text{mex}$ 至少到达 $k$，就是要求 $r$ 至少为 $[1,k-1]$ 出现时间的最大值。

这样这道题目就完成啦！！！

---

## 作者：zhangxy__hp (赞：0)

很巧的 trick。

首先离线。从大到小扫 $l$，维护数组 $p_i$ 表示当前出现 $i$ 的最小的位置。

显然当确定了左端点，从左到右的 $\operatorname{mex}$ 是单调不降的。因此我们要求的就是一段区间 $[l',r']$，满足 $\operatorname{mex}[l,l']\ge x$ 且 $l'$ 最小，$\operatorname{mex}[l,r']\le y$ 且 $r'$ 最大。（其中 $\operatorname{mex}[l,r]$ 表示区间 $[l,r]$ 的 $\operatorname{mex}$。）显然 $l'=\max_{0\le i<x}p_i$，$r'+1=\max_{0\le i\le y}p_i$。用线段树维护 $p$ 即可。时间复杂度 $O(n\log n)$。代码实现时要注意一些细节。
```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#define ll long long
#define il inline
#define pb push_back
#define lid id<<1
#define rid id<<1|1
using namespace std;
namespace asbt{
namespace cplx{bool begin;}
const int maxn=3e5+5;
int n,m,a[maxn],ans[maxn];
struct wen{
	int x,y,id;
};
vector<wen> wt[maxn];
int tr[maxn<<2];
il void pushup(int id){
	tr[id]=max(tr[lid],tr[rid]);
}
il void build(int id,int l,int r){
	tr[id]=n+1;
	if(l==r){
		return ;
	}
	int mid=(l+r)>>1;
	build(lid,l,mid);
	build(rid,mid+1,r);
}
il void upd(int id,int l,int r,int p,int v){
	if(l==r){
		tr[id]=v;
		return ;
	}
	int mid=(l+r)>>1;
	if(p<=mid){
		upd(lid,l,mid,p,v);
	}
	else{
		upd(rid,mid+1,r,p,v);
	}
	pushup(id);
}
il int query(int id,int L,int R,int l,int r){
	if(L>=l&&R<=r){
		return tr[id];
	}
	int mid=(L+R)>>1,res=0;
	if(l<=mid){
		res=max(res,query(lid,L,mid,l,r));
	}
	if(r>mid){
		res=max(res,query(rid,mid+1,R,l,r));
	}
	return res;
}
namespace cplx{
	bool end;
	il double usdmem(){return (&begin-&end)/1048576.0;}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1,l,x,y;i<=m;i++){
		cin>>l>>x>>y;
		wt[l].pb((wen){x,y,i});
	}
	build(1,0,n);
	for(int i=n;i;i--){
		upd(1,0,n,a[i],i);
		for(wen j:wt[i]){
			int id=j.id,x=j.x,y=j.y;
			ans[id]=query(1,0,n,0,y)-(x?query(1,0,n,0,x-1):i);
		}
	}
	for(int i=1;i<=m;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
}
int main(){return asbt::main();}
```

---

## 作者：mystic_qwq (赞：0)

我们建立权值线段树，值域是 $[1,n+1]$。可以发现值 $\ge n$ 的，对最终答案不会有影响，因为前面 $0\sim n-1$ 没法铺满。于是倒着建立权值线段树，每个值维护一个最晚（这里考虑按照遍历的时间来的）出现时间 $maxn$，初始化为 $n+1$。则要让 $[l,r]$ 的 $\text{mex}$ 至少到达 $k$，就是要求 $r$ 至少为 $[1,k-1]$ 出现时间的最大值（事实上是最早出现）。由此本题得解。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
struct
{
	int ls, rs, ma = N;
} t[N << 5];
int n, a[N], q, cnt, r[N];
#define mid (l + r >> 1)
#define lson t[h].ls, l, mid
#define rson t[h].rs, -~mid, r
void update(int x, int y, int p, int &h, int l = 1, int r = -~n)
{
	t[h = ++cnt] = t[p];
	if (l == r)
		return t[h].ma = y, void();
	if (x <= mid)
		update(x, y, t[p].ls, lson);
	else
		update(x, y, t[p].rs, rson);
	t[h].ma = max(t[t[h].ls].ma, t[t[h].rs].ma);
}
int query(int x, int y, int h, int l = 1, int r = -~n)
{
	if (x <= l && r <= y)
		return t[h].ma;
	int ret = 0;
	if (x <= mid)
		ret = max(ret, query(x, y, lson));
	if (y > mid)
		ret = max(ret, query(x, y, rson));
	return ret;
}
main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i)
		cin >> a[i], ++a[i];
	for (int i = n; i >= 1; --i)
	{
		if (a[i] > n)
		{
			r[i] = r[-~i];
			continue;
		}
		update(a[i], i, r[-~i], r[i]);
	}
	while (q--)
	{
		int l, x, y;
		cin >> l >> x >> y;
		int s1 = x ? query(1, x, r[l]) : l;
		int s2 = query(1, -~y, r[l]);
		if (s1 == N)
			s1 = -~n;
		if (s2 == N)
			s2 = -~n;
		cout << s2 - s1 << '\n';
	}
}
```

---

