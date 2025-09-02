# Counting Graphs

## 题目描述

Given a tree consisting of $ n $ vertices. A tree is a connected undirected graph without cycles. Each edge of the tree has its weight, $ w_i $ .

Your task is to count the number of different graphs that satisfy all four conditions:

1. The graph does not have self-loops and multiple edges.
2. The weights on the edges of the graph are integers and do not exceed $ S $ .
3. The graph has exactly one [minimum spanning tree](http://tiny.cc/30g9vz).
4. The minimum spanning tree of the graph is the given tree.

Two graphs are considered different if their sets of edges are different, taking into account the weights of the edges.

The answer can be large, output it modulo $ 998244353 $ .

## 说明/提示

In the first sample, there is only one graph, which is the given tree.

In the second samle, the given tree looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1857G/ab436917e6d0d4d72cf47ac14814448742495cf6.png)  All possible graphs for the second sample are shown below, the minimum spanning tree is highlighted in red: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1857G/9737432c0bacf448b6d65d0d9cf4c5fd9e2081b3.png)

## 样例 #1

### 输入

```
4
2 5
1 2 4
4 5
1 2 2
2 3 4
3 4 3
5 6
1 2 3
1 3 2
3 4 6
3 5 1
10 200
1 2 3
2 3 33
3 4 200
1 5 132
5 6 1
5 7 29
7 8 187
7 9 20
7 10 4```

### 输出

```
1
8
80
650867886```

# 题解

## 作者：Wf_yjqd (赞：16)

考场没写出来啊。

Div.3 都 AK 不了，我真的菜。

------------

考虑将给出的树边排序，模拟从头构建最小生成树。

在 kruskal 过程中，每次合并两个连通块，则完全图中浪费了两个连通块大小乘积 $-1$ 条边。

每条边可选的权值为最大权值 $-$ 当前枚举这条边的权值 $+1$。

快速幂维护每条边可行边权方案数的乘积。

总的答案即为每条边导致的废边个数乘积。

------------

真的太可惜了这场。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=2e5+84,mod=998244353;
struct Edge{
    int u,v,w;
    inline void read(){
        scanf("%lld%lld%lld",&u,&v,&w);
        return ;
    }
    friend bool operator<(Edge xy,Edge zb){
        return xy.w<zb.w;
    }
}e[maxn];
ll T,n,s,fx,fy,ans,fa[maxn],sz[maxn];
inline ll Find(register ll x){
    return x==fa[x]?x:fa[x]=Find(fa[x]);
}
inline ll Pow(ll x,ll y){
    if(!y)
        return 1;
    if(y&1)
        return x*Pow(x,y-1)%mod;
    ll res=Pow(x,y>>1)%mod;
    return res*res%mod;
}
int main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld",&n,&s);
        for(int i=1;i<=n;i++){
            fa[i]=i;
            sz[i]=1;
        }
        for(int i=1;i<n;i++)
            e[i].read();
        sort(e+1,e+n);
        ans=1;
        for(int i=1;i<n;i++){
            fx=Find(e[i].u);
            fy=Find(e[i].v);
            ans=(ans*Pow(s-e[i].w+1,sz[fx]*sz[fy]-1))%mod;
            fa[fx]=fy;
            sz[fy]+=sz[fx];
        }
        printf("%lld\n",ans%mod);
    }
    return 0;
}
```


---

## 作者：rui_er (赞：4)

一个非常显然的事情是：总方案数即为每条边方案数之积。

树边已经确定，考察每条非树边 $(u,v)$ 可以怎么取。给定的树 $T$ 是唯一最小生成树，这意味着非树边 $(u,v)$ 要么不存在，要么权值大于 $T$ 上 $(u,v)$ 之间任意一条边的权值。设 $T$ 上 $(u,v)$ 间的最大边权为 $k$，则 $(u,v)$ 对答案的贡献为 $S-k+1$。

但我们无法枚举每条非树边计算贡献，因为复杂度为 $O(n^2)$。考虑将“一类”非树边放到一起计算。

考虑 Kruskal 算法的过程，每次取出权值最小的边 $(u,v,w)$ 加入最小生成树，并将两个连通块 $B_1,B_2$ 合并。当一条边 $(u,v,w)$ 加入最小生成树时，它就是跨越两个连通块 $B_1,B_2$ 的任意一对点间的最大权值。这就意味着对于每一对 $B_1\times B_2$ 中的点对（$\times$ 是集合直积，$(u,v)$ 除外），这条边要么不存在，要么权值大于 $w$。

我们用桶统计出对于每个 $w$，有多少条边的要求是“要么不存在，要么权值大于 $w$”，并用快速幂计算即可。

时间复杂度 $O(n\log n+n\log S)$。

```cpp
// Problem: G. Counting Graphs
// Contest: Codeforces - Codeforces Round 891 (Div. 3)
// URL: https://codeforces.com/contest/1857/problem/G
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
ll randint(ll L, ll R) {
    uniform_int_distribution<ll> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const ll N = 2e5+5, mod = 998244353;

ll T, n, S;

struct Edge {
    ll u, v, w;
}e[N];

struct Dsu {
    ll fa[N], sz[N];
    void init(ll x) {rep(i, 1, x) fa[i] = i, sz[i] = 1;}
    ll find(ll x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
    bool same(ll x, ll y) {return find(x) == find(y);}
    bool merge(ll x, ll y) {
        if(same(x, y)) return false;
        x = find(x); y = find(y);
        fa[x] = y;
        sz[y] += sz[x];
        return true;
    }
}dsu;

map<ll, ll> cnt;

ll qpow(ll x, ll y) {
    ll ans = 1;
    for(; y; y >>= 1, x = x * x % mod) if(y & 1) ans = ans * x % mod;
    return ans;
}

int main() {
    for(scanf("%lld", &T); T; T--) {
        map<ll, ll>().swap(cnt);
        scanf("%lld%lld", &n, &S);
        rep(i, 1, n-1) scanf("%lld%lld%lld", &e[i].u, &e[i].v, &e[i].w);
        sort(e+1, e+n, [](const Edge& a, const Edge& b) {return a.w < b.w;});
        dsu.init(n);
        rep(i, 1, n-1) {
            ll u = e[i].u, v = e[i].v, w = e[i].w;
            cnt[w] += dsu.sz[dsu.find(u)] * dsu.sz[dsu.find(v)] - 1;
            dsu.merge(u, v);
        }
        ll ans = 1;
        for(auto [key, val] : cnt) if(val) ans = ans * qpow(S-key+1, val) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：NBest (赞：4)

## 题意：
求有多少个有 $n$ 个节点的无向图，使其满足以下条件：

- 无重边自环。
- 有且只有一个最小生成树，且为给定树。
- 最大边权不大于 $S$。

对 $998244353$ 取模。
## 思路：
其实就是让我们在给定的树加边使得最小生成树不改变。

考虑到在整棵树上我们可以加大于最大边权的任意边使得满足条件，那显然我们断掉最大边后，在各个联通块内随意加大于连通块最大边的边也可以满足条件。

那么我们可以先按照边权将所有边排序，一条一条加入边将节点合并。现在我们先考虑对于两个大小分别为 $siz_x,siz_y$ 的连通块，用目前最大边 $w$ 合并，对答案的贡献。

因为 $x,y$ 内部的贡献已经算过了，所以合并之后显然我们最多只能在 $x,y$ 之间**新增** $siz_x\times siz_y-1$ 条边，按照上面的理论，每条选了的边可以选 $S-w$ 个边权，我们令 $siz_x\times siz_y-1=m$，那么贡献就为：
$$\binom{m}{0}(S-w)^0+\binom{m}{1}(S-w)^1+\dots+\binom{m}{m}(S-w)^{m}$$

这显然是一个二项式定理的形式，所以可以将其转化为 $(S-w+1)^m$。

最后将所有贡献相乘即可。
## $Code$
```cpp
struct edge{
    int u,v;ll w;
    inline bool operator <(const edge &o)const{return w<o.w;}
}F[200005];
int T,n,fa[200005];
ll fac[200005],ifac[200005],siz[200005],S;
inline int find(int x){return (x==fa[x]?x:(fa[x]=find(fa[x])));}
inline int merge(int x,int y){
    if((x=find(x))==(y=find(y)))return siz[x];
    if(siz[x]>siz[y])x^=y^=x^=y;
    siz[y]+=siz[x],siz[x]=0,fa[x]=y;
    return siz[y]; 
}
ll qpow(ll x,ll w){
    ll res=1;
    for(;w;w>>=1,x=x*x%mod)if(w&1)res=res*x%mod;
    return res;
}
int main(){
    for(T=read();T--;){
        n=read(),S=read();
        fa[n]=n,siz[n]=1;
        for(int i=1;i<n;i++){
            fa[i]=i,siz[i]=1;
            int u=read(),v=read(),w=read();
            F[i]={u,v,w};
        }
        sort(F+1,F+n);
        ll ans=1;
        for(int i=1;i<n;i++){
            int u=find(F[i].u),v=find(F[i].v);
            ll sume=siz[u]*siz[v]-1;//可以加入的边数
            ll sum=qpow(S-F[i].w+1,sume);//二项式定理
            ans=ans*sum%mod;
            merge(u,v);
        }
        printf("%lld\n",ans);
    }
}
```


---

## 作者：Z1qqurat (赞：4)

纪念一下这个场切了但是题解通过之后 FST 的 G 题。想一想，什么样的边是可以加的？

* 首先这条边肯定不能在 $T$ 中出现过。
* 我们考虑一个求最小生成树的过程。我们把 $T$ 中所有边排序，假设现在我们插入的是边权为 $w$ 的树边，因为 $T$ 是 MST，所以加入的边 $(u, v)$ 两节点肯定不在同一个连通块内，假设 $ru = root_u, rv = root_v$，那么将 $u$ 和 $v$ 所在连通块合并后，会有 $siz_{ru} \times siz_{rv} - 1$ 个不在 $T$ 边集中的点对从不连通到连通。那么这些点对一定可以连边权为 $[w + 1, s]$ 的边。我们发现如果将所有边权为 $w$ 的树边都连完，在过程中我们将这些点对数累加为 $cnt$，它们对答案的贡献为乘上 $cnt^{s - w + 1}$。$s - w + 1$ 是因为每个点对我们可以选择连接一条边权在 $[w + 1, s]$ 的边，也可以不连这条边。然后这题就做完了，给出赛时代码。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define mr make_pair
#define fi first
#define se second
using namespace std;
const int N = 2e5 + 5;
const ll P = 998244353;
int t, n, fa[N], siz[N];
ll s;
struct Ed{
    int u, v;
    ll w;
}ed[N];
vector <Ed> e[N];
vector <ll> ww;
map <ll, int> id;

int getroot(int x) {
    if(fa[x] == x) return x;
    return getroot(fa[x]);
}

ll merge(int x, int y) {
    x = getroot(x), y = getroot(y);
    if(siz[x] > siz[y]) swap(x, y);
    ll ret = (ll)siz[x] * siz[y];
    siz[y] += siz[x], fa[x] = y;
    return ret;
}

ll qpow(ll x, ll y) {
    ll ret = 1ll;
    for (; y; y >>= 1ll, x = x * x % P) {
        if(y & 1ll) ret = ret * x % P;
    }
    return ret;
}

ll Spanning() {
    int mx = ww.size();
    // ww.push_back(s);
    ll ret = 1;
    for (int i = 0; i < mx; ++i) {
        ll cnt = 0;
        for (int j = 0; j < e[i].size(); ++j) {
            Ed c = e[i][j];
            int u = c.u, v = c.v; ll w = c.w;
            cnt += merge(u, v);
        }
        cnt -= e[i].size();
        ll x = s - ww[i] + 1;
        //cout << x << ' ' << cnt << "\n";
        if(cnt > 0 && x > 0) {
        	x %= P;
            ret = ret * qpow(x, cnt) % P;
        }
    }
    return ret;
}

void solve() {
    cin >> n >> s;
    ww.clear();
    for (int i = 1; i <= n; ++i) {
        fa[i] = i, siz[i] = 1;
    }
    for (int i = 0; i <= n; ++i) {
        e[i].clear();
    }
    for (int i = 1; i < n; ++i) {
        int u, v; ll w;
        cin >> u >> v >> w;
        ed[i].u = u, ed[i].v = v, ed[i].w = w;
        ww.push_back(w);
    }
    sort(ww.begin(), ww.end());
    unique(ww.begin(), ww.end());
    for (int i = 0; i < ww.size(); ++i) {
        id[ww[i]] = i;
    }
    for (int i = 1; i < n; ++i) {
        e[id[ed[i].w]].push_back(ed[i]);
    }
    /*for (int i = 0; i < ww.size(); ++i) {
        cout << e[i][0].u << ' ' << e[i][0].v << "\n";
    }*/
    cout << Spanning() << "\n";
    return ;
}

int main() {
    cin >> t;
    while(t--) solve();
    return 0;
}
```



---

## 作者：ProzacPainkiller (赞：3)

看到最小生成树就想到了并查集。

按照 Kruskal 的思路从小到大添加树边，可以发现当添加了一条边权为 $w$ 的树边时，它的两个端点所在的集合的每一个点（两个端点之间除外）都可以互相连一条边权在 $w+1$ 和 $S$ 之间的非树边，同时也可以不连非树边。设树边权值为 $w$，两个端点所在的集合分别为 $S_u,S_v$，统计答案就每次把答案乘上 $(S-w+1)^{|S_u|\times|S_v|-1}$ 即可。

---

再证明这种方法的正确性。首先由于两个并查集之间连了一条边权为 $w$ 的边，而由于边权从小到大排序，那么非树边的边权刚好可以从 $w+1$ 一直取到 $S$。而又由于边权从小到大排序，在枚举到边权为 $w$ 的树边的时候，剩下的树边的权值要么大于 $w$ 要么等于 $w$，那么对于这条边两个端点的并查集，其他树边的权值要么大于等于 $w+1$，不能添加边权为 $w+1$ 的非树边，否则最小生成树将会不唯一（当然也不能添加边权更小的，那么最小生成树就不是数据给出的这一棵了）；要么等于 $w$ ，待会就会统计。于是就可以证明用上面给出的方法统计是可以不重不漏的。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
const ll P=998244353;
int fa[N];
ll siz[N];
struct edge
{
	int fr,ed;
	ll w;
}e[N];
bool cmp(const edge& x,const edge& y)
{
	return x.w<y.w;
}
int kf(int x)
{
	return fa[x]==x?x:(fa[x]=kf(fa[x]));
}
ll qpow(ll a,ll b)
{
	if(!b)	return 1;
	ll tem=qpow(a,b/2ll);
	if(b&1)	return tem*tem%P*a%P;
	return tem*tem%P;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		ll S;
		cin>>n>>S;
		for(int i=1;i<=n;++i)
		{
			fa[i]=i;
			siz[i]=1;
		}
		for(int i=1;i<n;++i)	cin>>e[i].fr>>e[i].ed>>e[i].w;
		sort(e+1,e+n,cmp);
		e[n]={0,0,S};
		ll ans=1;
		for(int i=1;i<n;++i)
		{
			int f1=kf(e[i].fr),f2=kf(e[i].ed);
			(ans*=qpow(S-e[i].w+1,siz[f1]*siz[f2]-1ll))%=P;
			fa[f1]=f2;
			siz[f2]+=siz[f1];
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：AllenKING_RED (赞：1)

## 题目大意

给定一颗树以及树上边的边权，在树上添加任意边权的任意条边（不能重边，且最大为 $S$），生成一个新图（或新树），保证有且仅有一个最小生成树，且最小生成树就是原树,求生成新图的方案数。

## 基本思路

我们先考虑不合法的做法，即破坏了原来的最小生成树。

看到这里，写过次小生成树算法的同学应该会感到熟悉，没错，如果添加一条边，假设其边权为 $x$，如果其连接的两个点在原树上的路径中最小的边权小于等于 $x$，就破坏了原来的最小生成树。

既然我们已经知道了什么情况下原树会被破坏，所以合法的方案就是原本的方案减去不合法的方案数。当两个点 $x$、$y$ 不直接相连时，可以连接所有边权大于其在树上路径的最大边权，小于 $S$ 的边。

那么怎么统计呢？

我们可以按边权从大到小考虑所有原树上的边，假设最大边权的边连接两点 $x$、$y$，权值为 $z$，则所有直接路径经过该边的两个点，可以连接的最小边权大于 $z$。接下来我们思考如何维护经过该边的点，显然的，由于树上每一条边都是割边，将这条边断开后两个连通块内的点就可以连符合上述条件的边。以此类推，我们可以继续断开剩余连通块中的边，直到无边可断，最终答案就是每一次断开后计算出的答案相乘。

不过，断开连边似乎不好维护连通块中点的数量。我们可以考虑正难则反，由所有的点不连通开始从小往大建边，每次建边时假设两个连通块中分别有 $a$、$b$ 个点，此时建边的边权为 $c$，则最多可以连 $(a \times b-1)$ 条边，因为直接相连的两个点不能重新连边。此外，所有的边可以取 $(S-c+1)$ 个值，因为选择不连接该边可以视为边权为无限大，此时单次连边的答案就是 $S-c+1$ 的 $a \times b-1$ 次方，最后统计即可。

## 最终代码

其实不长，以下为赛时代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,MOD=998244353;
int T;
int n,S,fa[N],siz[N],ans=1;
struct node{
	int x;
	int y;
	int z;
}a[N];
bool cmp(node a,node b)
{
	return a.z<b.z;
}
int find(int x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
int ksm(int x,int y)
{
	if(y==0)return 1;
	if(y==1)return x;
	int ans=ksm(x,y>>1)%MOD;
	ans*=ans;
	ans%=MOD;
	if(y%2==1)
		ans*=x;
	return ans%MOD;
} 
signed main(void)
{
	cin>>T;
	while(T--)
	{
		cin>>n>>S;
		for(int i=1;i<=n;i++)
			fa[i]=i,siz[i]=1;
		for(int i=1;i<=n-1;i++)
			cin>>a[i].x>>a[i].y>>a[i].z;
		sort(a+1,a+n,cmp);
		for(int i=1;i<=n-1;i++)
		{
			int x=a[i].x,y=a[i].y;
			find(x),find(y);
			if(siz[fa[x]]*siz[fa[y]]-1)
				ans*=ksm(S-a[i].z+1,siz[fa[x]]*siz[fa[y]]-1)%MOD;//快速幂
			ans%=MOD;
			siz[fa[y]]+=siz[fa[x]];
			fa[fa[x]]=fa[y];//连边和统计点数，注意不能打反了
		}
		cout<<ans<<endl;
		ans=1;
	}
	return 0;
}
```
## 特别鸣谢

感谢 @syksykCCC 赛时的帮助

---

## 作者：WrongAnswer_90 (赞：0)

这个题感觉和[走廊泼水节](https://www.acwing.com/problem/content/348/)这道题很像，只不过改成了求方案，代码稍微改改就能过了。

考虑模拟一个求 MST 的的过程，既将边按照边权从小到大排序，一开始 $n$ 个点分别属于各自的集合，然后加边可以看成是将两个集合合并。

考虑加了一条边的贡献，首先两个点所在肯定是在两个联通块内，记联通块大小为 $siz_u$ 和 $siz_v$，这条边的边权为 $z$。

两个联通块之间可以加 $siz_u \times siz_v-1$ 条边，由于题目要求最小生成树仍是原树，所以这些边要么不加，要么边权大于 $z$，所以一共有 $S-z+1$ 种选择，快速幂求解即可。

正确性：首先边权已经从小到大排序，所以当前边两个端点 $(u,v)$ 所在树的边权一定全部小于等于当前的边。按照题目要求，在树上 $(u,v)$ 两点间加边的权值必须大于树上 $u$ 到 $v$ 经过路线的边权的最大值，所以加边一定合法。而 $(u,v)$ 分别的树内可以加的边在合并更小的两个集合时已经考虑过了，所以一定会考虑所有的方案。

附上赛时代码

```cpp
int T,n,m,fa[200001],siz[200001],ans;
struct Node{int x,y,z;}e[200001];
bool cmp(Node nd1,Node nd2){return nd1.z<nd2.z;}
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline int power(int x,int y)
{
	int ans=1;
	for(;y;x=x*x%MOD,y>>=1)if(y&1)ans=ans*x%MOD;
	return ans;
}
signed main()
{
	read(T);
	while(T--)
	{
		read(n,m);
		for(int i=1;i<=n;++i)fa[i]=i,siz[i]=1;
		for(int i=1;i<n;++i)read(e[i].x,e[i].y,e[i].z);
		sort(e+1,e+n,cmp),ans=1;
		for(int i=1;i<n;++i)
		{
			int x=find(e[i].x),y=find(e[i].y);
			if(x==y)continue;
			ans=ans*power(m-e[i].z+1,siz[y]*siz[x]-1)%MOD;
			fa[x]=y,siz[y]=(siz[y]+siz[x])%MOD;
		}
		write(ans,'\n');
	}
}

```

---

