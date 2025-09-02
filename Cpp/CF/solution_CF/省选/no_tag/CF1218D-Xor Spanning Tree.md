# Xor Spanning Tree

## 题目描述

在遥远的银河系中，有一个古老的星际共和国 Bubbleland，由 $N$ 个行星组成。它们之间有 $M$ 条双向虫洞，每条虫洞连接一对行星。Bubbleland 是一个高度集中的共和国，拥有一个首都行星 Whiteplanet，从首都可以通过这些虫洞到达任何其他行星。保证没有虫洞连接自身，也没有两条不同的虫洞连接同一对行星。

我们称一条从某个行星出发，访问其他行星且每个行星最多访问一次，最后回到起点的路径为一次巡游。星际安全条例保证每个行星最多属于一次巡游，并且最多有 $42$ 次巡游。

经过无数年代的使用，虫洞需要修复，每条虫洞的修复费用为 $W_{i}$。不幸的是，Bubbleland 的参议院预算紧张。因此，他们决定只修复必要的虫洞，以保证所有行星都能从首都到达，并且修复费用尽可能少。然而，参议院计算费用的方式不同。修复费用集合的总费用是每条虫洞修复费用的二进制异或和。也就是说，如果修复的虫洞费用为 $A_{1},A_{2},...,A_{k}$，则总费用为 $A_{1} \oplus A_{2} \oplus ... \oplus A_{k}$。

现在，参议院想知道他们最少需要支付多少费用，以及有多少种不同的修复方案可以达到这个费用，答案对 $1000000007$ 取模。

## 说明/提示

我们可以修复虫洞 $1$、$2$、$3$、$5$ 和 $6$，支付的费用为 $5 \oplus 1 \oplus 2 \oplus 3 \oplus 4 = 1$，可以验证这是所有行星连通且费用最小的修复方案，并且只有这一种方案达到该费用。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 6
4 1 5
5 2 1
6 3 2
1 2 6
1 3 3
2 3 4
```

### 输出

```
1 1```

# 题解

## 作者：1saunoya (赞：1)

## 题意:
给出一个仙人掌，最多 **42** 个环，在图中选取一些边，使得只留下这些边时，整张图仍联通，且所有选取的边的边权的异或值最小。求最小值&方案数。


看到方案数，一定会想到一个东西叫做多项式（

我们发现仙人掌有一个很显然的性质，环的任意一条边只会出现在一个环里，那么说明了你每个环，最多删掉一条边，才能使它连通，所以枚举断边，然后对所有的环暴力 FWT 即可。

```cpp
#include <bits/stdc++.h>

const int maxn = 1e5 + 51;
const int mod1 = 1e9 + 7;
const int mod2 = 1e9 + 9;
std::vector <std::pair<int, int>> g[maxn];

int dfn[maxn], idx = 0;
int f[maxn], fw[maxn];
int xr;
std::vector<std::vector<int>> V;

void dfs(int u, int fa) {
	dfn[u] = ++idx;
	for(auto x: g[u]) {
		int v = x.first, w = x.second;
		if(v == fa) continue;
		if(!dfn[v]) {
			f[v] = u, fw[v] = w;
			dfs(v, u);
		}
		else if(dfn[v] > dfn[u]) {
			std::vector <int> vec;
			int cur = w;
			for(int now = v; now ^ u; now = f[now])
				cur ^= fw[now];
			vec.push_back(cur ^ w);
			for(int now = v; now ^ u; now = f[now])
				vec.push_back(cur ^ fw[now]);
			xr ^= cur;
			V.push_back(vec);
		}
	}
}

int add(int x, int y, const int&mod) { x += y; return (x >= mod) ? x - mod: x; }
int dec(int x, int y, const int&mod) { x -= y; return (x < 0) ? x + mod: x; }

int n, m;
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
		xr ^= w;
	}
	dfs(1, 0);
	static int a[1 << 17 | 3], b[1 << 17 | 3];
	
	auto fwt = [&](int*f, int lim, const int&inv, const int&mod) {
		for(int len = 1; len < lim; len <<= 1) {
			for(int i = 0; i < lim; i += len << 1) {
				for(int j = 0; j < len; j++) {
					int x = f[i + j], y = f[i + j + len];
					f[i + j] = add(x, y, mod);
					f[i + j + len] = dec(x, y, mod);
					if(inv > 1) f[i + j] = 1ll * f[i + j] * inv % mod, f[i + j + len] = 1ll * f[i + j + len] * inv % mod;
				}
			}
		}
	};
	
	a[xr] = 1, b[xr] = 1;
	
	fwt(a, 1 << 17, 1, mod1);
	fwt(b, 1 << 17, 1, mod2);
	
	static int c[1 << 17 | 3], d[1 << 17 | 3];
	for(auto v: V) {
		memset(c, 0, sizeof(c));
		memset(d, 0, sizeof(d));
		for(auto x : v) c[x]++, d[x]++;
		fwt(c, 1 << 17, 1, mod1);
		fwt(d, 1 << 17, 1, mod2);
		for(int i = 0; i < (1 << 17); i++) {
			a[i] = 1ll * a[i] * c[i] % mod1;
			b[i] = 1ll * b[i] * d[i] % mod2;
		}
	}
	
	fwt(a, 1 << 17, (mod1 + 1) >> 1, mod1);
	fwt(b, 1 << 17, (mod2 + 1) >> 1, mod2);
	
	for(int i = 0; i < (1 << 17); i++)
		if(a[i] || b[i]) {
			std::cout << i << ' ' << a[i] << '\n';
			return 0;
		}
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
接触多项式后第一道想到多项式的题？

摘自 [数数数](https://www.luogu.com.cn/training/627660)。
## 思路分析
首先生成树中的边有 $n-1$ 条，直接做最小异或生成树肯定是会炸飞的。

注意到这题的运算符号是异或，而异或也可以考虑用整体减掉局部。

具体的，就是我们不要直接考虑这 $n-1$ 条边的异或值，而是通过全部边的值异或上断掉的边的值。

因为环最多只有 $42$ 个，而每个环都恰好断掉一条边，所以断掉的边最多也只有 $42$ 条，而全部边的异或值也是固定的，所以考虑这 $42$ 个环断哪些边就可以了。

那现在我们的问题就变成了从 $43$ 个序列中恰好选出 $43$ 个数（每个序列恰好一个），使得异或值最小并求方案数（还有一个序列仅有一个值是全局所有边的异或值）。

我们考虑用 $f_i$ 表示异或值为 $i$ 的方案数。

那么我们对于一个环，也类似的处理一个 $g_i$ 表示异或值为 $i$ 的方案数。

那么把这个环并进来就是：
$$f'_{k}=\sum\limits_{i\bigoplus j=k}f_i\cdot g_j$$
这个式子就是真的板子了，直接上 FWT 就行了。

注意到这题是 $43$ 次 FWT，所以可以做完后再逆变换回来卡常。

不过出题人比较没素质所有有一些点的方案数对于 $10^9+7$ 取模后刚好是 $0$，记得双模判断下。
## 代码
实现上找环选择了先拉一棵树出来，然后从两端点往 LCA 跳。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=5e5+10,M=1e5+10,V=1<<17,p=13331,mod=1e9+7,md=998244353,INF=0x3f3f3f3f3f3f3f3f;
struct edge{int x,y,w;}g[N];
int n,m,q,tot,a[N],b[N],d[N],w[N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
struct DSU
{
    vector<int> h;
    void init(int n){h=vector<int>(n+10);for(int i=0;i<=n;i++) h[i]=i;}
    int find(int x){return h[x]==x?x:h[x]=find(h[x]);}
    void merge(int x,int y){x=find(x),y=find(y);h[x]=y;}
}f;
inline void FWT_xor(int a[],int n,int op,int mod)
{
	for(int i=1;i<n;i<<=1) for(int p=i<<1,j=0;j<n;j+=p)
		for(int k=0,x,y;k<i;k++)
		{
			x=a[j+k],y=a[i+j+k];a[j+k]=(x+y)%mod;a[i+j+k]=(x+mod-y)%mod;
			a[j+k]=a[j+k]*op%mod,a[i+j+k]=a[i+j+k]*op%mod;
		}
}
namespace tree_decomposition
{
    int fa[N],son[N],si[N],dep[N];int cnt;
    int top[N],id[N],dfn[N],c[N];vector<pair<int,int>>e[N];
    inline void add(int u,int v,int w){e[u].emplace_back(v,w),e[v].emplace_back(u,w);}
	inline void clear(int n)
	{
		memset(son,0,sizeof son);
		cnt=0;for(int i=1;i<=n;i++) e[i].clear();
	}
    inline void dfs1(int u,int ff)
    {
        fa[u]=ff,si[u]=1,dep[u]=dep[ff]+1;
        for(auto [v,w]:e[u])
        {
            if(v==ff) continue;c[v]=w;
            dfs1(v,u);si[u]+=si[v];
            if(si[son[u]]<si[v]) son[u]=v;
        }
    }
    inline void dfs2(int u,int topf)
    {
        top[u]=topf;dfn[u]=++cnt,id[cnt]=u;
        if(son[u]) dfs2(son[u],topf);
        for(auto [v,w]:e[u])
        {
            if(v==fa[u]||v==son[u]) continue;
            dfs2(v,v);
        }
    }
    inline int LCA(int x,int y)
    {
        while(top[x]!=top[y])
        {
            if(dep[top[x]]<dep[top[y]]) swap(x,y);
            x=fa[top[x]];
        }
        return dep[x]<dep[y]?x:y;
    }
}
using namespace tree_decomposition;
inline void solve()
{
	n=read(),m=read();f.init(n);
	for(int i=1,x,y,w;i<=m;i++)
	{
		x=read(),y=read(),w=read();q^=w;
		if(f.find(x)==f.find(y)){g[++tot]={x,y,w};continue;}
		f.merge(x,y);add(x,y,w);
	}dfs1(1,0);dfs2(1,1);a[q]=1;d[q]=1;FWT_xor(a,V,1,mod);FWT_xor(d,V,1,md);
	for(int i=1;i<=tot;i++)
	{
		memset(b,0,sizeof b);int x=g[i].x,y=g[i].y;
		b[g[i].w]++;int lca=LCA(g[i].x,g[i].y);
		while(x!=lca) b[c[x]]++,x=fa[x];
		while(y!=lca) b[c[y]]++,y=fa[y];
		memcpy(w,b,sizeof w);FWT_xor(b,V,1,mod);FWT_xor(w,V,1,md);
		for(int j=0;j<V;j++) a[j]=a[j]*b[j]%mod,d[j]=d[j]*w[j]%md;
	}FWT_xor(a,V,(mod+1)>>1,mod);FWT_xor(d,V,(md+1)>>1,md);
	for(int i=0;i<V;i++) if(a[i]||d[i])
		return print(i),put(' '),print(a[i]),put('\n');
}
signed main()
{
	int T=1;
	// T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：hhhqx (赞：0)

博客园：https://www.cnblogs.com/huangqixuan/articles/18608743#cf1218d---xor-spanning-tree

仙人掌定义：每条边最多在一个环上（温馨提示：这题没重边自环，所以环的大小至少为 $3$）。

仙人掌的生成树就是在每个环上选择删除一条边。42 次卷积就做完了。关于在仙人掌上找环，可以得出 dfs 树，然后判断多余的边。

注意可能方案数 $ \bmod 10^9 + 7 = 0$。可以双模数。

关于常数：

- 每个环都 6 次 FWT 肯定不行，需要使用 $D = A * B * C * \cdots \iff FWT(D) = FWT(A) \cdot FWT(B) \cdot FWT(C) \cdots$。
- 于是变为了每个环都 2 次 FWT。但是还是不太好过，可以把 FWT 函数中取模的数量减少到两次，就可以 1.7s 卡过了。

```cpp
#include <bits/stdc++.h>

using namespace std;
using PII = pair<int, int>;

const int MAXN = 1e5 + 3;
const int MAXV = (1ll << 17), V = 17; // 2^17 > 1e5
const int mod = 1e9 + 7, i2 = 5e8 + 4, _mod = 1e9 + 21, _i2 = 5e8 + 11;

int n, m, sum = 0;
int f[MAXV], g[MAXV], _f[MAXV], _g[MAXV];
vector<PII> eg[MAXN];

void FWT(int *A, int op, int MOD){
	for(int len = 1; len < MAXV; len <<= 1){
		for(int i = 0; i < MAXV; i += len + len){ 
			for(int j = i; j < i + len; j++){
				int tmp = A[j];
				A[j] = (A[j] + A[j + len]), A[j + len] = (tmp - A[j + len] + MOD);
				A[j] = 1ll * A[j] * op % MOD, A[j + len] = 1ll * A[j + len] * op % MOD;
			}
		}
	}
}

int dfn[MAXN], fw[MAXN], fa[MAXN], depth = 0;
void dfs(int x, int dad){
  dfn[x] = ++depth, fa[x] = dad;
  for(PII e : eg[x]){ int nxt = e.first;
    if(nxt == dad) continue;
    if(!dfn[nxt]){
      fw[nxt] = e.second, dfs(nxt, x);
    }else if(dfn[nxt] < dfn[x]){
      memset(g, 0, sizeof(g)), memset(_g, 0, sizeof(_g));
      g[e.second]++, _g[e.second]++;
      for(int p = x; p != nxt; p = fa[p]) g[fw[p]]++, _g[fw[p]]++;
      FWT(g, 1, mod), FWT(_g, 1, _mod);
      for(int i = 0; i < MAXV; i++) f[i] = 1ll * f[i] * g[i] % mod, _f[i] = 1ll * _f[i] * _g[i] % _mod;
    }
  }
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for(int i = 1, U, V, W; i <= m; i++){
		cin >> U >> V >> W, sum ^= W;
		eg[U].push_back({V, W}), eg[V].push_back({U, W});
	}
	f[sum] = _f[sum] = 1; 
  FWT(f, 1, mod), FWT(_f, 1, _mod);
	dfs(1, 0);
  FWT(f, i2, mod), FWT(_f, _i2, _mod);
	for(int x = 0; x < MAXV; x++) if(f[x] > 0 || _f[x] > 0){
	  cout << x << " " << f[x];
	  return 0;
	}
	return 0;
}
```

---

## 作者：rui_er (赞：0)

萌萌 FWT 题。

仙人掌满足任意一条边只在至多一个环上，因此要求生成树，只需要每个环断一条边即可。显然生成树上边权异或和等于所有边异或和再异或上所有断的边。

设所有边异或和为 $s$，第 $i$ 个环上有 $c_{i,j}$ 条边权为 $j$ 的边。

令 $F_0(z)=[z=s]$，$F_i(z)=c_{i,z}$。定义 $(F\stackrel{\operatorname{xor}}{*}G)(z)=\sum\limits_{i\operatorname{xor} j=z}F(i)G(j)$。

使用 FWT 计算出 $\prod\limits^{\operatorname{xor}}F_i$，其第 $z$ 项的值即为边权异或和为 $z$ 的生成树个数，从小到大枚举 $z$ 找出第一个可行解并输出即可。

需要注意的是，在第 $31$ 个测试点，最小异或生成树个数对 $10^9+7$ 取模恰好余 $0$，会使得我们漏掉最优解，因此需要双模数。

时间复杂度为 $O(kn\log n)$，其中 $k$ 为环数，值域视为与 $n$ 同阶。

```cpp
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

const ll N = 131072, mod1 = 1e9+7, mod2 = 1e9+9;

ll n, m, xsum, F[N], G[N], f[N], g[N], fa[N], val[N], dfn[N], tms;
vector<tuple<ll, ll>> e[N];
vector<vector<ll>> cyc;

template<ll mod, ll flg>
void FWT_xor(ll* a, ll n) {
	ll mul = flg == +1 ? 1 : (mod + 1) / 2;
	for(ll o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
		for(ll i = 0; i < n; i += o)
			rep(j, 0, k-1) {
				a[i+j] += a[i+j+k];
				a[i+j+k] = a[i+j] + 2 * (mod - a[i+j+k]);
				a[i+j] *= mul;
				a[i+j+k] *= mul;
				a[i+j] %= mod;
				a[i+j+k] %= mod;
			}
}

void dfs(ll u, ll f, ll w) {
	fa[u] = f;
	val[u] = w;
	dfn[u] = ++tms;
	for(auto& i : e[u]) {
		ll v = get<0>(i), w = get<1>(i);
		if(v != f) {
			if(!dfn[v]) dfs(v, u, w);
			else if(dfn[v] < dfn[u]) {
				cyc.push_back({});
				cyc.back().push_back(w);
				for(ll k = u; k != v; k = fa[k]) cyc.back().push_back(val[k]);
			}
		}
	}
}

int main() {
	scanf("%lld%lld", &n, &m);
	rep(i, 1, m) {
		ll u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		e[u].emplace_back(v, w);
		e[v].emplace_back(u, w);
		xsum ^= w;
	}
	F[xsum] = G[xsum] = 1;
	FWT_xor<mod1, +1>(F, N);
	FWT_xor<mod2, +1>(G, N);
	dfs(1, 0, 0);
	for(auto& c : cyc) {
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		for(ll i : c) ++f[i], ++g[i];
		FWT_xor<mod1, +1>(f, N);
		FWT_xor<mod2, +1>(g, N);
		rep(i, 0, N-1) {
			F[i] = F[i] * f[i] % mod1;
			G[i] = G[i] * g[i] % mod2;
		}
	}
	FWT_xor<mod1, -1>(F, N);
	FWT_xor<mod2, -1>(G, N);
	rep(i, 0, N-1) {
		if(F[i] || G[i]) {
			printf("%lld %lld\n", i, F[i]);
			break;
		}
	}
	return 0;
}
```

---

## 作者：Terac (赞：0)

这题很简单。

首先把每个环找出来，因为是仙人掌，所以每个环最多删一条边。问题变为从每个环中找出至多一条边，使剩下的边权异或和最小，即所有边权与选出的边权异或和最小，同时求其方案数。

显然可以用多项式计数，令 $f_{k,i}$ 表示第 $k$ 个环边权为 $i$ 的边数，并使 $f_{0,sum}=1$，$sum$ 为所有边异或和。发现最终异或和为 $i$ 的方案数就是所有的 $f$ 异或卷积后 $i$ 处的值，FWT 即可。

---

