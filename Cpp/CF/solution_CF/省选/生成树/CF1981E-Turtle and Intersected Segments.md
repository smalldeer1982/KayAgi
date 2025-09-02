# Turtle and Intersected Segments

## 题目描述

Turtle 给你 $n$ 条线段和一个序列 $a_1,a_2,\cdots,a_n$，第 $i$ 条线段是 $[l_i,r_i]$。

Turtle 将按如下方式建图：对于任意的 $i,j$，若 $a_i,a_j$ 相交，则 $i,j$ 之间连一条边权为 $|a_i-a_j|$ 的边。相交的定义为 $\max(l_1,l_2)\le\min(r_1,r_2)$。

Turtle 想知道最小生成树的边权和是多少。


保证所有子数据 $n$ 的和不超过 $5\cdot10^5$。

## 样例 #1

### 输入

```
4
5
1 7 3
2 4 6
3 5 5
6 7 9
3 4 4
5
2 7 3
1 3 6
4 5 5
6 7 9
1 1 4
4
1 4 3
1 2 1
3 4 5
1 4 4
3
1 3 1
2 3 3
4 5 8```

### 输出

```
9
13
4
-1```

# 题解

## 作者：EuphoricStar (赞：12)

发现对于三条两两相交的线段 $(l_1, r_1, a_1), (l_2, r_2, a_2), (l_3, r_3, a_3)$（不妨设 $a_1 \le a_2 \le a_3$），只用保留 $(1, 2), (2, 3)$ 之间的边，因为 $a_3 - a_1 = a_2 - a_1 + a_3 - a_2$，而且对于一个图的每个环，其中边权最大的边一定不会出现在最小生成树上。

由此，考虑这样的一个扫描线流程：每条线段在 $l$ 处加入，在 $r$ 处删除；加入一条线段时找到它按 $a$ 排序后的前驱后继连边。实际上是维护每个时刻存在的所有线段按 $a$ 排序后连成的一条链。

容易发现做完扫描线后边数缩减到了 $O(n)$，那么直接求最小生成树就行了。

时间复杂度：每个测试用例 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<int, int> pii;

const int maxn = 1000100;

int n, lsh[maxn], tot, fa[maxn];
pii b[maxn];

struct node {
	int l, r, x;
} a[maxn];

struct edg {
	int u, v, d;
	edg(int a = 0, int b = 0, int c = 0) : u(a), v(b), d(c) {}
} E[maxn];

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

inline bool merge(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		fa[x] = y;
		return 1;
	} else {
		return 0;
	}
}

void solve() {
	tot = 0;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i].l >> a[i].r >> a[i].x;
		lsh[++tot] = a[i].l;
		lsh[++tot] = (++a[i].r);
	}
	int m = 0;
	sort(lsh + 1, lsh + tot + 1);
	tot = unique(lsh + 1, lsh + tot + 1) - lsh - 1;
	for (int i = 1; i <= n; ++i) {
		a[i].l = lower_bound(lsh + 1, lsh + tot + 1, a[i].l) - lsh;
		a[i].r = lower_bound(lsh + 1, lsh + tot + 1, a[i].r) - lsh;
		b[++m] = mkp(a[i].l, i);
		b[++m] = mkp(a[i].r, -i);
	}
	set<pii> S;
	sort(b + 1, b + m + 1);
	int tt = 0;
	for (int i = 1; i <= m; ++i) {
		int j = b[i].scd;
		if (j > 0) {
			auto it = S.insert(mkp(a[j].x, j)).fst;
			if (it != S.begin()) {
				int k = prev(it)->scd;
				E[++tt] = edg(j, k, abs(a[j].x - a[k].x));
			}
			if (next(it) != S.end()) {
				int k = next(it)->scd;
				E[++tt] = edg(j, k, abs(a[j].x - a[k].x));
			}
		} else {
			j = -j;
			S.erase(mkp(a[j].x, j));
		}
	}
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
	}
	sort(E + 1, E + tt + 1, [&](const edg &a, const edg &b) {
		return a.d < b.d;
	});
	ll ans = 0, cnt = 0;
	for (int i = 1; i <= tt; ++i) {
		if (merge(E[i].u, E[i].v)) {
			++cnt;
			ans += E[i].d;
		}
	}
	cout << (cnt == n - 1 ? ans : -1) << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T = 1;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：Inui_Sana (赞：3)

感觉这题比榜反应出来的简单。

首先容易发现一个性质：如果有 $a_i<a_j,a_j<a_k$ 且 $i,j,k$ 两两连边，那么 $(i,k)$ 这条边是完全没用的，因为会直接被 $(i,j),(j,k)$ 代替。

这启发我们先按照 $a_i$ 升序排序。对于每个区间 $[l_i,r_i]$，我们先看之前有哪些区间 $[l_j,r_j]$ 和这段区间有交。根据上面的性质，我们只用考虑其中 $a_i$ 最大的。也就是说，如果一个区间 $[l_j,r_j]\cup[l_i,r_i]$ 被 $[l_k,r_k]\cup[l_i,r_i]$ 所包含且 $a_k>a_j$，则 $i$ 不会向 $k$ 连边。然后发现这就相当于每次区间覆盖，向区间内出现过的数连边。

根据颜色段均摊，这样的边数是 $O(n)$ 的。最后再跑一遍 Kruskal 即可。

code：

```cpp
int n,m;
struct node{
	int l,r,x;
}a[N],E[M];
struct CHTree{
	struct node{
		int l,r,k;
		node(int _l=0,int _r=0,int _k=0):l(_l),r(_r),k(_k){}
		il bool operator<(const node &rhs)const{
			return l<rhs.l;
		}
	};
	set<node> st;
	il void init(){
		st.clear();
		st.insert(node(1,n,0));
	}
	il auto split(int p){
		auto it=st.lower_bound(node(p));
		if(it!=st.end()&&it->l==p){
			return it;
		}
		node tmp=*--it;
		st.erase(it);
		st.emplace(tmp.l,p-1,tmp.k);
		return st.emplace(p,tmp.r,tmp.k).fi;
	}
	void assign(int l,int r,int k){
		auto itr=split(r+1),itl=split(l);
		for(auto it=itl;it!=itr;it++){
			if(!(it->k)){
				continue;
			}
			E[++m]=(::node){k,it->k,a[k].x-a[it->k].x};
		}
		st.erase(itl,itr);
		st.emplace(l,r,k);
	}
}T;
struct DSU{
	int fa[N];
	void init(){
		rep(i,1,n){
			fa[i]=i;
		}
	}
	int find(int x){
		return fa[x]==x?x:fa[x]=find(fa[x]);
	}
	il bool merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y){
			return 0;
		}
		fa[x]=y;
		return 1;
	}
}D;
il bool cmp(node x,node y){
	return x.x<y.x;
}
void Yorushika(){
	scanf("%d",&n),m=0;
	rep(i,1,n){
		scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].x);
	}
	sort(a+1,a+n+1,cmp);
	T.init();
	rep(i,1,n){
		T.assign(a[i].l,a[i].r,i);
	}
	sort(E+1,E+m+1,cmp);
	D.init();
	ll ans=0;int cnt=0;
	rep(i,1,m){
		int u=E[i].l,v=E[i].r;
		if(D.merge(u,v)){
			ans+=E[i].x;
			cnt++;
		}
	}
	printf("%lld\n",cnt<n-1?-1:ans);
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：Demeanor_Roy (赞：2)

- [原题链接](https://www.luogu.com.cn/problem/CF1981E)

------------

对于某条线段 $L$，我们考虑它与左端点不大于它的线段的连边，显然这些线段若与 $L$ 相交，必有一个交点是 $L$ 的左端点，故它们也两两相交。

考虑 kruskal 算法求最小生成树的过程，我们是优先考虑小边权边，待两个点联通后我们把他们当作整体考虑。故对于上述线段 $L$ 以及左端点不大于它且与它相交的线段，我们把它们按照 $a$ 值排序，则我们只用关心 $L$ 与其前驱后继的连边，因为当我们在 kruskal 算法中考虑到 $L$ 与其他线段的连边时， $L$ 一定已经与它的前驱后继联通，且它的前驱或后继与这些点的连边一定不劣于 $L$ 与这些点的连边。

而对于线段 $L$，左端点大于它且与它相交的线段我们会在考虑那条线段时枚举到 $L$，故我们可以得出结论：对于每条线段，拎出左端点不大于它且与它相交的线段中 $a$ 值与它相邻的至多两条线段连边，把这些边拿出来做 kruskal 即可。显然这样的边不超过 $2n$ 条。

具体实现上，我们从左往右扫，将线段在左端点处加入一个按 $a$ 值排序的 set，并在右端点处删除这条线段。同时我们在加入一条线段时得到它与此时 set 中前驱后继的连边即可。

时间复杂度 $O(n \log n)$。下附代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
const int N=5e5+10;
int T,n,m,fa[N];
vector<int> vec,ad[N<<1],de[N<<1];
struct node{int l,r,v;}s[N],E[N<<1]; 
inline int get(int x){return x==fa[x]?x:fa[x]=get(fa[x]);}
inline int find(int x){return lower_bound(vec.begin(),vec.end(),x)-vec.begin()+1;}
inline void solve()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) fa[i]=i,scanf("%d%d%d",&s[i].l,&s[i].r,&s[i].v);
	m=0;vec.clear();
	for(int i=1;i<=n;i++) vec.push_back(s[i].l),vec.push_back(s[i].r);
	sort(vec.begin(),vec.end());
	vec.erase(unique(vec.begin(),vec.end()),vec.end());
	for(int i=1;i<=(int)vec.size();i++) ad[i].clear(),de[i].clear();
	for(int i=1;i<=n;i++)
	{
		ad[find(s[i].l)].push_back(i);
		de[find(s[i].r)].push_back(i);
	}
	set<pii> S;
	for(int i=1;i<=(int)vec.size();i++)
	{
		for(auto x:ad[i])
		{
			pii tmp={s[x].v,x};
			auto it=S.lower_bound(tmp);
			if(it!=S.end()) E[++m]={it->second,x,it->first-s[x].v};
			if(it!=S.begin()) --it,E[++m]={it->second,x,s[x].v-it->first};
			S.insert(tmp);
		}
		for(auto x:de[i]) 
		{
			pii tmp={s[x].v,x};
			S.erase(S.find(tmp));
		}
	}
	int cnt=0;long long ans=0;
	sort(E+1,E+m+1,[](node a,node b){return a.v<b.v;});
	for(int i=1;i<=m;i++)
		if(get(E[i].l)!=get(E[i].r))
		{
			fa[get(E[i].l)]=get(E[i].r);
			++cnt;ans+=E[i].v;
		}
	printf("%lld\n",cnt==n-1?ans:-1);
}
int main()
{
	scanf("%d",&T);
	while(T--) solve();
	return 0;	
} 
```

---

## 作者：FFTotoro (赞：2)

赛时降智了写树套树结果没调完，赛后才发现扫描线 + 只查前驱后继直接用 `std::multiset` 即可。错失一个场切 $\color{Red}*2700$，寄。

暴力建图显然不可取，考虑使用限制减少边数。猜测对于某一条线段 $i$，它只需要向与它相交**且左端点不大于它**的线段 $j$ 中的（最多）两条线段连边：第一条为 $a_j\le a_i$ 且 $a_j$ 最大的线段，第二条为 $a_j>a_i$ 且 $a_j$ 最小的线段；最后在这个图上跑 MST 即可。证明可以考虑 Kruskal 算法的流程，如果两点已经连通那么边权更大的边就不需要也不可以加入最小生成树，对于三条两两相交的线段简单讨论即可。

现在问题在于如何找出上面的这（最多）两条线段。可以用一种比较麻烦的线段树套平衡树 + 二分进行维护；但是并不需要。参考官方题解做法，离散化后按照位置从左往右进行扫描线：对于每一条线段 $[l_i,r_i]$ 在扫到 $l_i$ 时往一个多重集合里面加入 $a_i$，在 $r_i$ 时删除 $a_i$；插入时查找集合中 $a_i$ 的前驱后继，建边即可。最后跑一遍 Kruskal。

时间复杂度 $O(n\log n)$，略带常数（`std::multiset`）但时限 $5\mathrm{s}$ ，$n=5\times 10^5$ 轻松通过，甚至跑不到 $2\mathrm{s}$。

参考代码（GNU C++17）：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tpi;
namespace IAOI_lib{
  template<typename T> class dsu{
    private:
      vector<T> a;
      vector<int> s;
    public:
      dsu(){
        a.resize(200000),s.resize(200000,1);
        iota(a.begin(),a.end(),0);
      }
      dsu(int n){
        a.resize(n),s.resize(n,1);
        iota(a.begin(),a.end(),0);
      }
      T leader(T x){
        return a[x]==x?x:a[x]=leader(a[x]);
      }
      inline int size(T x){
        return s[leader(x)];
      }
      inline void merge(T x,T y){
        x=leader(x),y=leader(y);
        if(x==y)return;
        if(s[x]>s[y])swap(x,y);
        s[y]+=s[x],a[x]=y;
      }
      inline bool same(T x,T y){
        return leader(x)==leader(y);
      }
  };
} // 并查集模板
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t; cin>>t;
  while(t--){
    int n,c=0; long long mst=0; cin>>n;
    vector<tpi> a(n),e;
    vector<int> b;
    for(auto &[l,r,w]:a)
      cin>>l>>r>>w,b.emplace_back(l),b.emplace_back(r);
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    vector<vector<pii> > q1(n<<1),q2(n<<1);
    for(int i=0;i<n;i++){
      auto &[l,r,w]=a[i];
      l=lower_bound(b.begin(),b.end(),l)-b.begin();
      r=lower_bound(b.begin(),b.end(),r)-b.begin();
      // 离散化
      q1[l].emplace_back(w,i);
      q2[r].emplace_back(w,i);
    }
    multiset<pii> s;
    for(int t=0;t<n<<1;t++){ // 进行扫描线
      for(auto i:q1[t]){
        auto p=s.lower_bound(make_pair(i.first,0));
        if(p!=s.end())e.emplace_back(i.second,p->second,p->first-i.first);
        p=s.upper_bound(make_pair(i.first+1,0));
        if(p!=s.begin())e.emplace_back(i.second,prev(p)->second,i.first-prev(p)->first);
        s.emplace(i);
      } // 加入线段并查找前驱后继
      for(auto i:q2[t])
        s.erase(s.find(i)); // 删除线段
    }
    sort(e.begin(),e.end(),[](tpi x,tpi y){
      return get<2>(x)<get<2>(y);
    });
    IAOI_lib::dsu<int> d(n);
    for(auto [u,v,w]:e)
      if(!d.same(u,v))d.merge(u,v),c++,mst+=w;
    // 跑一遍 Kruskal
    cout<<(c==n-1?mst:-1)<<'\n';
  }
  return 0;
}
```

---

## 作者：Disjoint_cat (赞：2)

# [CF1981E](https://www.luogu.com.cn/problem/CF1981E)

众所周知一篇题解需要一张头图。

![](https://cdn.luogu.com.cn/upload/image_hosting/5sfso9km.png)

## 题意

给定 $n$ 个三元组 $(l_i,r_i,a_i)$。有一个 $n$ 个点的图，其中 $(i,j)$ 有边当且仅当 $[l_i,r_i]\cap[l_j,r_j]\ne\varnothing$，且如果有边则边权为 $|a_i-a_j|$。求该图的 MST 或报告图不连通。

Data range：$n\le5\times10^5$，$1\le l_i,r_i,a_i\le10^9$。

## 题解

本以为放在 E 的位置是什么 Boruvka 之类的高级玩意，结果发现是经典套路。

这种根据某些信息生成边数很多的图然后求 MST 的题，一种经典 trick 就是：绝大多数边对于 MST 都是没用的。

现考虑本题。

> Lemma：考虑图中的一个环，则其中权值最大的边对于 MST 是无用的。
>
> Proof：反证，如果 MST 中包含此边，考虑 Kruskal，则加到这条边时两个端点不连通，但环上其他边已经可以使这两点连通，矛盾。

那么，如果三条线段两两相交，设其权值为 $x\le y\le z$，则三条边权值显然 $z-x$ 最大，所以我们只需考虑 $(x,y)$ 和 $(y,z)$ 的边就行了。

更形象地，如果两条线段间隔着一条与它们都相交的线段，那么这两点之间的边是没用的。

扫描线，维护当前所有与扫描线相交的线段。

当加入一条线段时，则由引理，我们其实只需要考虑和它的 $a$ 值离得最近的上、下各一条线段，`set` 即可。

此时每条线段最多贡献两条边，于是边数降至 $\Theta(n)$，总时间复杂度 $\Theta(n\log n)$。

[赛时 submission](https://codeforces.com/contest/1981/submission/263491977)。

---

## 作者：SamHJD (赞：0)

将线段按 $a_i$ 排序，对于 $i<j<k$，若三条线段有公共点，则 $(i,k)$ 这条边是无用的，因为 $(i,j),(j,k)$ 两条边可以替换 $(i,k)$，且 $\max(|a_i-a_j|,|a_j-a_k|)<|a_i-a_k|$。

故使用 ODT 维护颜色段，每条线段连向其下方的每一条线段，然后覆盖上去，连边的数量是 $O(n)$ 的，正常跑 kruskal。

```cpp
#include <bits/stdc++.h>
#define ll long long
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
const int N=1e6+10;
int T,n,m;
set<pair<pair<int,int>,int> > s;
struct node{
    int u,v,w;
    bool operator <(const node b) const{
        return w<b.w;
    }
}e[N*2];
struct NODE{
    int l,r,a,id;
    bool operator <(const NODE b) const{
        return a<b.a;
    }
}a[N];
auto split(int x){
    auto it=s.lower_bound({{x,x},0});
    if(it!=s.end()&&it->first.first==x) return it;
    auto p=*--it;
    s.erase(it);
    s.insert({{p.first.first,x-1},p.second});
    return s.insert({{x,p.first.second},p.second}).first;
}
int f[N];
int getfa(int x){return f[x]==x?f[x]:f[x]=getfa(f[x]);}
void merge(int x,int y){f[getfa(x)]=getfa(y);}
void solve(){
    s.clear();
    read(n);m=0;
    s.insert({{1,n},0});
    rep(i,1,n) read(a[i].l,a[i].r,a[i].a),a[i].id=i;
    sort(a+1,a+n+1);
    rep(i,1,n){
        int l=a[i].l,r=a[i].r;
        auto itr=split(r+1),itl=split(l);
        for(auto it=itl;it!=itr;it++){
            if(!it->second) continue;
            e[++m]={a[i].id,a[it->second].id,abs(a[i].a-a[it->second].a)};
        }
        s.erase(itl,itr);
        s.insert({{l,r},i});
    }
    sort(e+1,e+m+1);
    rep(i,1,n) f[i]=i;
    int cnt=0;ll res=0;
    rep(i,1,m){
        int u=e[i].u,v=e[i].v,w=e[i].w;
        if(getfa(u)!=getfa(v)){
            merge(u,v);
            cnt++;res+=w;
        }
    }
    if(cnt!=n-1) printf("-1\n");
    else printf("%lld\n",res);
}
int main(){
    read(T);while(T--) solve();
    return 0;
}
```

---

## 作者：不知名用户 (赞：0)

### 题意

Turtle 给你 $n$ 条线段和一个序列 $a_1,a_2,\cdots,a_n$，第 $i$ 条线段是 $[l_i,r_i]$。

Turtle 将按如下方式建图：对于任意的 $i,j$，若 $a_i,a_j$ 相交，则 $i,j$ 之间连一条边权为 $|a_i-a_j|$ 的边。相交的定义为 $\max(l_1,l_2)\le\min(r_1,r_2)$。

Turtle 想知道最小生成树的边权和是多少。

### 做法

看到 $|a_i-a_j|$ 想到把线段按 $a$ 从小到大排序。观察发现如果一个线段覆盖了另一个线段，被覆盖的线段就没用了。用 `set` 维护颜色段。容易证明边数是 $O(n)$ 的。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e5 + 10;

struct xx{int l,r,a;}s[N],e[N*40];
int t[N*2], cur, f[N], ce;
int find(int x){return x == f[x] ? x : f[x] = find(f[x]);}
void lsh(int &x){x = lower_bound(&t[1],&t[cur]+1,x)-t;}
using piii = pair<pair<int,int>,int>;
#define L first.first
#define R first.second
#define C second
#define mkp(a,b,c) make_pair(make_pair(a,b),c)
set<piii>r;


int Main()
{
	int n, i;
	scanf("%lld", &n);
	cur = ce = 0;
	for(i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld", &s[i].l, &s[i].r, &s[i].a);
		t[++cur] = s[i].l, t[++cur] = s[i].r, f[i] = i;
	}
	sort(&t[1],&t[cur]+1);
	cur = unique(&t[1],&t[cur]+1) - t - 1;
	for(i=1;i<=n;i++) lsh(s[i].l), lsh(s[i].r);
	sort(&s[1],&s[n]+1,[](xx a,xx b){return a.a<b.a;});
	r.clear();
	for(i=1;i<=n;i++)
	{
//		printf("%d %d\n", s[i-1].l, s[i-1].r);
//		for(auto i:r) printf("%d %d %daa\n", i.L, i.R, i.C);
//		printf("------------------------\n");
		piii z = mkp(s[i].l,0,0);
		for(;;)
		{
			auto it = r.upper_bound(z);
			if(it==r.end()||it->R>s[i].r) break;
			e[++ce] = {it->C,i,s[i].a-s[it->C].a};
			r.erase(it);
		}
		auto it = r.upper_bound(z);
		if(it!=r.begin())
		{
			it--;
			if(it->L<=s[i].l&&it->R>=s[i].r)
			{
				piii v = *it;
				e[++ce] = {it->C,i,s[i].a-s[it->C].a};
				r.erase(it);
				if(v.L<s[i].l) r.insert(mkp(v.L,s[i].l-1,v.C));
				if(s[i].r<v.R) r.insert(mkp(s[i].r+1,v.R,v.C));
				r.insert(mkp(s[i].l,s[i].r,i));
				continue;
			}
		}
		it = r.upper_bound(z);
		if(it!=r.end()&&it->L<=s[i].r)
		{
			e[++ce] = {it->C,i,s[i].a-s[it->C].a};
			piii v = *it;
			r.erase(it), v.L = s[i].r + 1, r.insert(v);
		}
		it = r.upper_bound(z);
		if(it!=r.begin())
		{
			it--;
			if(it->R>=s[i].l)
			{
				e[++ce] = {it->C,i,s[i].a-s[it->C].a};
				piii v = *it;
				r.erase(it), v.R = s[i].l - 1, r.insert(v);
			}
		}
		r.insert(mkp(s[i].l,s[i].r,i));
	}
	int cc = 0, ans = 0;
	sort(&e[1],&e[ce]+1,[](xx a,xx b){return a.a<b.a;});
	for(i=1;i<=ce;i++)
	{
		int x = find(e[i].l), y = find(e[i].r);
		if(x!=y) cc++, f[y] = x, ans += e[i].a;
	}
	if(cc<n-1) ans = -1;
	printf("%lld\n", ans);
	return 0;
}
signed main(){int t;scanf("%lld", &t);while(t--)Main();return 0;}
```

---

## 作者：daniEl_lElE (赞：0)

考虑优化建图。

考虑将所有线段画到一个平面上。问题转化为画一些竖直的线段使得原来的线段两两相连。

考虑对于一个新画的线段，如果这条线段两端所在的原线段之间跨越了一条另外的线段，那么不妨把线段拆成两段（此时权值相同，可能连通的原线段 +1）。

接着，对于所有极小线段（即，不跨越任何原线段），不妨把这个线段移到连接的原线段某个线段的两端。

此时，我们发现，新的可能存在于 MST 上的线段只有 $O(n)$ 条，即，每条原线段左右端点与上方/下方的原线段的连线。

现在我们跑 Kruskal 的复杂度就是 $O(n\log n)$ 了。

考虑如何找到这些线段，可以使用 set 维护，加点/删点/查前驱后继。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
int l[1000005],r[1000005],a[1000005];
int lsh[1000005];
vector<pair<int,int>> vc[1000005];
vector<pair<pair<int,int>,int>> ed;
set<int> st;
map<int,int> mp;
bool cmp(pair<pair<int,int>,int> p1,pair<pair<int,int>,int> p2){
	return p1.second<p2.second;
}
int f[1000005],lp[1000005];
map<int,int> cnt;
int find(int i){
	return f[i]==i?f[i]:f[i]=find(f[i]);
}
void solve(){
	int n; cin>>n;
	mp.clear(),cnt.clear();
	for(int i=1;i<=n;i++){
		f[i]=i;
		cin>>l[i]>>r[i]>>a[i];
		lp[i]=a[i];
		lsh[i*2-1]=l[i];
		lsh[i*2]=r[i];
	}
	sort(lp+1,lp+n+1);
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(lp+1,lp+n+1,a[i])-lp;
		int tmp=a[i];
		a[i]+=cnt[tmp];
		mp[a[i]]=i;
		cnt[tmp]++;
	}
	sort(lsh+1,lsh+2*n+1); int m=unique(lsh+1,lsh+2*n+1)-lsh-1;
	for(int i=1;i<=m;i++) vc[i].clear();
	ed.clear();
	for(int i=1;i<=n;i++){
		l[i]=lower_bound(lsh+1,lsh+m+1,l[i])-lsh;
		r[i]=lower_bound(lsh+1,lsh+m+1,r[i])-lsh;
		vc[l[i]].push_back(make_pair(i,a[i]));
		vc[r[i]].push_back(make_pair(i,-a[i]));
//		cout<<l[i]<<" "<<r[i]<<" "<<a[i]<<"\n";
	}
	for(int i=1;i<=m;i++){
//		cout<<i<<"\n";
		for(auto v:vc[i]){
			if(v.second>0) st.insert(v.second);
		}
		for(auto v:vc[i]){
			int q=llabs(v.second);
			auto p=st.upper_bound(q);
			if(p!=st.end()){
//				cout<<q<<" "<<(*p)<<"\n";
				ed.push_back(make_pair(make_pair(v.first,mp[*p]),lp[(*p)]-lp[q]));
			}
			p=st.lower_bound(q);
			if(p!=st.begin()){
				p=prev(p);
//				cout<<q<<" "<<(*p)<<"\n";
				ed.push_back(make_pair(make_pair(v.first,mp[*p]),lp[q]-lp[(*p)]));
			}
		}
		for(auto v:vc[i]){
			if(v.second<0) st.erase(st.find(-v.second));
		}
	}
	sort(ed.begin(),ed.end(),cmp);
	int cnt=0,sum=0;
	for(auto v:ed){
		if(find(v.first.first)!=find(v.first.second)){
			f[find(v.first.first)]=find(v.first.second);
			cnt++,sum+=v.second;
		}
	}
	if(cnt==n-1){
		cout<<sum<<"\n";
	}
	else{
		cout<<-1<<"\n";
	}
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	int t; cin>>t;
	while(t--) solve();
	return 0;
}
```

---

