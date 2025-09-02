# [ABC244Ex] Linear Maximization

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc244/tasks/abc244_h

$ 2 $ 次元平面上の点の集合 $ S $ があります。$ S $ ははじめ空です。

$ i\ =\ 1,\ 2,\ \dots,\ Q $ の順に、以下のクエリを処理してください。

- 整数 $ X_i,\ Y_i,\ A_i,\ B_i $ が与えられる。$ S $ に点 $ (X_i,\ Y_i) $ を追加した後、$ \displaystyle\ \max_{(x,y)\ \in\ S}\left\{A_ix\ +\ B_iy\right\} $ を求める。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ <\ =Q\ <\ =2\ \times\ 10^5 $
- $ |X_i|,\ |Y_i|,\ |A_i|,\ |B_i|\ <\ =10^9 $
- $ i\ ≠\ j $ ならば $ (X_i,\ Y_i)≠(X_j,\ Y_j) $

### Sample Explanation 1

\- $ i\ =\ 1 $ のとき : $ S $ に点 $ (1,\ 0) $ を追加し、$ S\ =\ \{(1,\ 0)\} $ とします。$ (x,\ y)\ =\ (1,\ 0) $ のとき $ -x\ -\ y\ =\ -1 $ となり、これが最大値を取ります。 - $ i\ =\ 2 $ のとき : $ S $ に点 $ (0,\ 1) $ を追加し、$ S\ =\ \{(0,\ 1),\ (1,\ 0)\} $ とします。$ (x,\ y)\ =\ (1,\ 0) $ のとき $ 2x\ =\ 2 $ となり、これが最大値を取ります。 - $ i\ =\ 3 $ のとき : $ S $ に点 $ (-1,\ 0) $ を追加し、$ S\ =\ \{(-1,\ 0),\ (0,\ 1),\ (1,\ 0)\} $ とします。$ (x,\ y)\ =\ (1,\ 0) $ または $ (x,\ y)\ =\ (0,\ 1) $ のとき $ x\ +\ y\ =\ 1 $ となり、これが最大値を取ります。 - $ i\ =\ 4 $ のとき : $ S $ に点 $ (0,\ -1) $ を追加し、$ S\ =\ \{(-1,\ 0),\ (0,\ -1),\ (0,\ 1),\ (1,\ 0)\} $ とします。$ (x,\ y)\ =\ (0,\ -1) $ のとき $ x\ -\ 2y\ =\ 2 $ となり、これが最大値を取ります。

## 样例 #1

### 输入

```
4
1 0 -1 -1
0 1 2 0
-1 0 1 1
0 -1 1 -2```

### 输出

```
-1
2
1
2```

## 样例 #2

### 输入

```
9
-1 4 -8 -2
9 -9 -7 7
4 1 6 7
-4 -1 -4 -5
-9 3 -2 -6
-1 0 -8 5
-8 -5 0 0
8 3 0 -4
2 -5 2 5```

### 输出

```
0
35
31
21
36
87
0
36
31```

# 题解

## 作者：Leasier (赞：5)

### 法一：维护凸包
考虑将 $ax + by$ 看成 $(a, b) \cdot (x, y)$，则可以发现可能成为最优解的 $(x, y)$ 必然在其所构成的凸包上。

平衡树维护凸包，查询时在凸包上三分即可。时间复杂度为 $O(q \log^2 q)$。
### 法二：维护直线
不妨设 $b \neq 0$，考虑将 $ax + by$ 转化为 $b(x \frac{a}{b} + y)$。

此时我们可以将其看成一次函数最值乘上常数，将 $\frac{a}{b}$ 离散化后用李超线段树维护即可。时间复杂度为 $O(q \log q)$。

注意特判所有 $b$ 均为 $0$ 的情况，此时我们不应建出李超线段树。

法二代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;

typedef struct Segment_tag {
	int id;
	int k;
	int b;
	
	Segment_tag(){}
	
	Segment_tag(int id_, int k_, int b_){
		id = id_;
		k = k_;
		b = b_;
	}
	
	inline double calc(double x){
		return k * x + b;
	}
} Segment;

typedef struct {
	int l;
	int r;
	Segment min;
	Segment max;
} Node;

int x[200007], y[200007], a[200007], b[200007];
ll ans[200007];
double val[200007];
Node tree[800007];

void build(int x, int l, int r){
	tree[x].l = l;
	tree[x].r = r;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
}

void insert1(int x, Segment seg){
	int mid = (tree[x].l + tree[x].r) >> 1;
	if (tree[x].min.id == 0 || tree[x].min.calc(val[mid]) > seg.calc(val[mid])) swap(tree[x].min, seg);
	if (seg.id == 0 || tree[x].l == tree[x].r) return;
	if (tree[x].min.calc(val[tree[x].l]) > seg.calc(val[tree[x].l])) insert1(x * 2, seg);
	if (tree[x].min.calc(val[tree[x].r]) > seg.calc(val[tree[x].r])) insert1(x * 2 + 1, seg);
}

void insert2(int x, Segment seg){
	int mid = (tree[x].l + tree[x].r) >> 1;
	if (tree[x].max.id == 0 || tree[x].max.calc(val[mid]) < seg.calc(val[mid])) swap(tree[x].max, seg);
	if (seg.id == 0 || tree[x].l == tree[x].r) return;
	if (tree[x].max.calc(val[tree[x].l]) < seg.calc(val[tree[x].l])) insert2(x * 2, seg);
	if (tree[x].max.calc(val[tree[x].r]) < seg.calc(val[tree[x].r])) insert2(x * 2 + 1, seg);
}

void query1(int x, int pos, Segment &ans){
	if (tree[x].min.id == 0) return;
	if (ans.id == 0 || ans.calc(val[pos]) > tree[x].min.calc(val[pos])) ans = tree[x].min;
	if (tree[x].l == tree[x].r) return;
	if (pos <= ((tree[x].l + tree[x].r) >> 1)){
		query1(x * 2, pos, ans);
	} else {
		query1(x * 2 + 1, pos, ans);
	}
}

void query2(int x, int pos, Segment &ans){
	if (tree[x].max.id == 0) return;
	if (ans.id == 0 || ans.calc(val[pos]) < tree[x].max.calc(val[pos])) ans = tree[x].max;
	if (tree[x].l == tree[x].r) return;
	if (pos <= ((tree[x].l + tree[x].r) >> 1)){
		query2(x * 2, pos, ans);
	} else {
		query2(x * 2 + 1, pos, ans);
	}
}

int main(){
	int q, minx = 0x7fffffff, maxx = 0x80000000, cnt = 0;
	scanf("%d", &q);
	for (register int i = 1; i <= q; i++){
		scanf("%d %d %d %d", &x[i], &y[i], &a[i], &b[i]);
		minx = min(minx, x[i]);
		maxx = max(maxx, x[i]);
		if (b[i] == 0){
			ans[i] = max((ll)a[i] * minx, (ll)a[i] * maxx);
		} else {
			val[++cnt] = 1.0 * a[i] / b[i];
		}
	}
	if (cnt > 0){
		sort(val + 1, val + cnt + 1);
		cnt = unique(val + 1, val + cnt + 1) - val - 1;
		build(1, 1, cnt);
		for (register int i = 1; i <= q; i++){
			Segment cur(i, x[i], y[i]);
			insert1(1, cur);
			insert2(1, cur);
			if (b[i] != 0){
				Segment seg(0, 0, 0);
				if (b[i] < 0){
					query1(1, lower_bound(val + 1, val + cnt + 1, 1.0 * a[i] / b[i]) - val, seg);
				} else {
					query2(1, lower_bound(val + 1, val + cnt + 1, 1.0 * a[i] / b[i]) - val, seg);
				}
				ans[i] = (ll)a[i] * seg.k + (ll)b[i] * seg.b;
			}
		}
	}
	for (register int i = 1; i <= q; i++){
		cout << ans[i] << endl;
	}
	return 0;
}
```

---

## 作者：qczrz6v4nhp6u (赞：2)

平衡树，不会！李超树，不会！

来个二进制分组的做法。

### Solution

首先 $ax+by=b\times (\frac{a}{b}\cdot x+y)$，转化成维护若干条直线，查给定横坐标的 $\min$ 或者 $\max$。

不难发现这就是维护两个凸壳。观察到只有加入操作，且很难支持在线加入，考虑二进制分组。具体地，维护 $\log_2 n$ 个集合，第 $i$ 个集合维护 $2^i$ 条直线的凸壳。加入一条直线就从 $0$ 开始扫，直到当前集合为空，然后将前面扫过的所有集合都合并进当前集合中，暴力重构凸壳即可。

不难发现上述过程类似于做二进制加法。因为每条直线只会被重构 $\log n$ 次，所以总复杂度是有保证的。

时间复杂度 $O(n\log^2 n)$，应该可以精细实现做到 $O(n\log n)$。

### Code

非常好写！

```cpp
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=2e5+5;
int n;
struct line{
	ll k,b;
	line(){k=b=0;}
	line(ll _k,ll _b){k=_k,b=_b;}
	inline bool operator <(const line &_)const{return k!=_.k?k<_.k:b<_.b;}
};
inline double calc(const line &u,const line &v){
	return 1.0*(u.b-v.b)/(v.k-u.k);
}
inline bool check(const line &u,const line &v,const line &w){
	return calc(v,w)<=calc(u,v);
}
inline void convex(vector<line> &s){
	static vector<line> a;a=s,s.clear();
	sort(a.begin(),a.end());
	for(const auto &o:a){
		while((s.size()&&s.back().k==o.k)||((int)s.size()>1&&check(s[(int)s.size()-2],s[(int)s.size()-1],o)))
			s.pop_back();
		s.emplace_back(o);
	}
}
vector<line> h[2][20];
inline void ins(line u){
	for(int op=0;op<2;op++){
		auto &s=h[op];
		int pos=0;
		while(s[pos].size())pos++;
		for(int i=0;i<pos;i++){
			for(const auto &o:s[i])s[pos].emplace_back(o);
			s[i].clear();
		}
		s[pos].emplace_back(u);
		convex(s[pos]);
		u.k*=-1,u.b*=-1;
	}
}
inline ll query(ll u,ll v){
	ll ans=-4e18;double tar=1.0*u/v;
	for(int op=0;op<2;op++){
		for(int i=0;i<20;i++){
			auto &s=h[op][i];
			if(!s.size())continue;
			int l=0,r=(int)s.size()-1,mid;
			while(l<r){
				mid=(l+r)>>1;
				if(calc(s[mid],s[mid+1])<tar)l=mid+1;
				else r=mid;
			}
			ans=max(ans,(!op?1:-1)*(s[r].k*u+s[r].b*v));
		}
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	while(n--){
		ll u,v,a,b;
		cin>>u>>v>>a>>b;
		ins(line(u,v));
		cout<<query(a,b)<<'\n';
	}
	return 0;
}
```

---

## 作者：qnqfff (赞：1)

### 思路

首先 $ax+by$ 可以变成 $b(\frac{a}{b}x+y)$，显然若 $b>0$ 则后者取最大值，否则取最小值，$b=0$ 要特判。

现在问题变成求 $\frac{a}{b}x+y$ 的最值，显然这是个一次函数，李超线段树即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){char c=getchar();int p=0,flg=1;while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,ans[200010];double a[200010];struct Line{int k,b;}p[200010];struct Info{int x,y,a,b;}q[200010];struct seg{int l,r,mi,mx;}t[800010];
double calc(int u,double x){return p[u].k*x+p[u].b;}
#define lson now<<1
#define rson now<<1|1
void build(int now,int l,int r){
	t[now]={l,r};if(l==r) return ;
	int mid=(l+r)>>1;build(lson,l,mid);build(rson,mid+1,r);
}
void upd(int now,int u){
	if(!t[now].mx){t[now].mx=u;return ;}if(t[now].l==t[now].r) return ;int mid=(t[now].l+t[now].r)>>1;
	if(calc(u,a[mid])>calc(t[now].mx,a[mid])) swap(u,t[now].mx);if(calc(u,a[t[now].l])>calc(t[now].mx,a[t[now].l])) upd(lson,u);if(calc(u,a[t[now].r])>calc(t[now].mx,a[t[now].r])) upd(rson,u);
}
void _upd(int now,int u){
	if(!t[now].mi){t[now].mi=u;return ;}if(t[now].l==t[now].r) return ;int mid=(t[now].l+t[now].r)>>1;
	if(calc(u,a[mid])<calc(t[now].mi,a[mid])) swap(u,t[now].mi);if(calc(u,a[t[now].l])<calc(t[now].mi,a[t[now].l])) _upd(lson,u);if(calc(u,a[t[now].r])<calc(t[now].mi,a[t[now].r])) _upd(rson,u);
}
int _max(int u,int v,double x){if(!v) return u;if(!u) return v;return calc(u,x)>calc(v,x)?u:v;}
int _min(int u,int v,double x){if(!v) return u;if(!u) return v;return calc(u,x)<calc(v,x)?u:v;}
int query(int now,int x){
	if(t[now].l==t[now].r) return t[now].mx;
	int mid=(t[now].l+t[now].r)>>1;if(x<=mid) return _max(t[now].mx,query(lson,x),a[x]);else return _max(t[now].mx,query(rson,x),a[x]);
}
int _query(int now,int x){
	if(t[now].l==t[now].r) return t[now].mi;
	int mid=(t[now].l+t[now].r)>>1;if(x<=mid) return _min(t[now].mi,_query(lson,x),a[x]);else return _min(t[now].mi,_query(rson,x),a[x]);
}
signed main(){
	n=read();int cnt=0;for(int i=1,mx=-1e18,mi=1e18;i<=n;i++){q[i]={read(),read(),read(),read()};mx=max(mx,q[i].x);mi=min(mi,q[i].x);if(!q[i].b) ans[i]=max(q[i].a*mx,q[i].a*mi);else a[++cnt]=1.*q[i].a/q[i].b;}
	if(!cnt) goto out;sort(a+1,a+1+cnt);cnt=unique(a+1,a+1+cnt)-a-1;build(1,1,cnt);
	for(int i=1,tot=0;i<=n;i++){
		p[++tot]={q[i].x,q[i].y};upd(1,tot);_upd(1,tot);if(!q[i].b) continue;
		if(q[i].b>0){int pos=query(1,lower_bound(a+1,a+1+cnt,1.*q[i].a/q[i].b)-a);ans[i]=q[i].a*p[pos].k+q[i].b*p[pos].b;}
		else{int pos=_query(1,lower_bound(a+1,a+1+cnt,1.*q[i].a/q[i].b)-a);ans[i]=q[i].a*p[pos].k+q[i].b*p[pos].b;}
	}out:;for(int i=1;i<=n;i++) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：江户川·萝卜 (赞：1)

$ax+by=b(\frac{a}{b}x+y)$，括号里面是直线的形式，启示我们使用李超线段树。

但是 $x$ 坐标求的一直是 $\frac{a}{b}$ 这种分数形式，李超只能维护整数域。但是考虑到总共询问的就 $n$ 个分数，所以可以离线下来，将分数离散化至 $1\sim n$。

记得对于 $b$ 分讨，若 $b=0$ 存下当前 $x$ 的最小值与最大值进行计算，若 $b<0$ 则求的是 $kx+y$ 的最小值，否则就是最大值。

时间复杂度 $O(q\log q)$。

```cpp
// LUOGU_RID: 156714149
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
#define mp make_pair
typedef pair<ll,ll> pll;
constexpr int maxn=2e5+5;
pll v[maxn];ll a[maxn],b[maxn],x[maxn],y[maxn];int q,id[maxn],pd[maxn];
inline long double f(int i,int j){return a[i]*x[j]*1.0/b[i]+y[j];}
#define ls p<<1
#define rs p<<1|1
ll ans;
struct sb{
    int t[maxn<<2];
    inline ll cmp(int l,int r,int d){return l&&(!r||f(d,l)>f(d,r));}
    void modify(int p,int l,int r,int k){
        int mid=l+r>>1;
        if(cmp(k,t[p],mid)) swap(t[p],k);
        if(l==r) return;
        if(cmp(k,t[p],l)) modify(ls,l,mid,k);
        if(cmp(k,t[p],r)) modify(rs,mid+1,r,k);
    }
    void query(int p,int l,int r,int k){
        if(t[p])ans=max(ans,a[k]*x[t[p]]+b[k]*y[t[p]]);
        if(l==r) return;
        int mid=l+r>>1;
        if(k<=mid) query(ls,l,mid,k);else query(rs,mid+1,r,k);
    }
}A;
struct sbw{
    int t[maxn<<2];
    inline ll cmp(int l,int r,int d){return l&&(!r||f(d,l)<f(d,r));}
    void modify(int p,int l,int r,int k){
        int mid=l+r>>1;
        if(cmp(k,t[p],mid)) swap(t[p],k);
        if(l==r) return;
        if(cmp(k,t[p],l)) modify(ls,l,mid,k);
        if(cmp(k,t[p],r)) modify(rs,mid+1,r,k);
    }
    void query(int p,int l,int r,int k){
        if(t[p])ans=max(ans,a[k]*x[t[p]]+b[k]*y[t[p]]);
        if(l==r) return;
        int mid=l+r>>1;
        if(k<=mid) query(ls,l,mid,k);else query(rs,mid+1,r,k);
    }
}B;
int main(){
    // string name="A";freopen((name+".in").c_str(),"r",stdin);freopen((name+".out").c_str(),"w",stdout);
    std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>q;for(int i=1;i<=q;i++) cin>>x[i]>>y[i]>>v[i].fi>>v[i].se,id[i]=i;
    sort(id+1,id+q+1,[&](auto x,auto y){
        if(v[x].se==0&&v[y].se==0) return x<y;
        if(v[x].se==0) return false;
        if(v[y].se==0) return true;
        if(v[x].fi*v[y].se==v[y].fi*v[x].se) return x<y;
        if((v[x].se<0)^(v[y].se<0)) return v[x].fi*v[y].se>v[y].fi*v[x].se;
        else return v[x].fi*v[y].se<v[y].fi*v[x].se;
    });
    for(int i=1;i<=q;i++) a[i]=v[id[i]].fi,b[i]=v[id[i]].se,pd[id[i]]=i;
    // for(int i=1;i<=q;i++)cout<<id[i]<<' '<<pd[i]<<' '<<a[i]<<' '<<b[i]<<'\n';
    int Q=q;
    while(q&&!b[q]) q--;
    ll mx=-1e18,Sb=1e18;
    for(int i=1;i<=Q;i++){
        if(q)A.modify(1,1,q,i),B.modify(1,1,q,i);
        mx=max(mx,x[i]);Sb=min(Sb,x[i]);
        if(!v[i].se){
            // cout<<mx<<' '<<Sb<<'\n';
            cout<<v[i].fi*(v[i].fi>0?mx:Sb)<<'\n';
        }
        else if(v[i].se>0){
            ans=-3e18;
            A.query(1,1,q,pd[i]);
            cout<<ans<<'\n';
        }else{
            ans=-3e18;
            B.query(1,1,q,pd[i]);
            cout<<ans<<'\n';
        }
    }
}
```

---

