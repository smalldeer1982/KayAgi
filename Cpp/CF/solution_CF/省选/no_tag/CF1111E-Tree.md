# Tree

## 题目描述

给定一棵有 $n$ 个节点的树，以及 $q$ 个询问。

每个询问以三个整数 $k$、$m$ 和 $r$ 开头，接着是树上的 $k$ 个节点 $a_1, a_2, \ldots, a_k$。对于每个询问，假设树以 $r$ 为根。我们需要将给定的 $k$ 个节点分成最多 $m$ 个组，满足以下条件：

- 每个节点恰好属于一个组，每个组至少有一个节点。
- 在任意一个组内，不能存在两个不同的节点，使得其中一个节点是另一个节点的祖先（无论是直接还是间接的祖先）。

你需要输出每个询问的方案数，对 $10^9+7$ 取模。

## 说明/提示

考虑第一个样例。

在第一个询问中，需要将给定的三个节点（$7$、$4$ 和 $3$）分成最多三个组，假设树以 $2$ 为根。当树以 $2$ 为根时，$4$ 是 $3$ 和 $7$ 的祖先。因此不能将所有节点放在同一个组。只有 $1$ 种方式将节点分成两个组，即 $[4]$ 和 $[3, 7]$。也只有一种方式将节点分成三个组，即 $[7]$、$[4]$ 和 $[3]$。所以总共有 $2$ 种分组方式。

在第二个询问中，当树以 $4$ 为根时，$6$ 是 $2$ 的祖先，$2$ 又是 $1$ 的祖先。因此不能将所有给定节点放在同一个组。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7 2
5 4
2 6
5 3
1 2
7 5
4 6
3 3 2 7 4 3
3 1 4 6 2 1
```

### 输出

```
2
0
```

## 样例 #2

### 输入

```
7 2
4 7
2 5
4 1
5 1
5 6
4 3
3 3 2 7 1 4
2 1 6 3 2
```

### 输出

```
1
1
```

## 样例 #3

### 输入

```
5 2
3 5
4 5
4 2
1 4
2 2 3 1 2
2 2 4 5 4
```

### 输出

```
2
1
```

# 题解

## 作者：GKxx (赞：20)

比赛的时候满脑子虚树 就死掉了

看来真的不能先入为主

这种询问点集的，首先考虑建虚树，然后按套路设$dp(x,i)$表示将以$x$为根的子树中的关键点分成$i$组的方案数，那么你很快就会发现这玩意根本不能转移，因为它不是正常的背包。

换一个思路，如果我们考虑将关键点按$\text{dfs}$序排序，那么对于一个点$\text{node}_i$，所有不能跟它放在同一组里的点（也就是它到根的路径上的点）都会排在它前面。不妨设点$x$到根的路径上的关键点为$f(x)$，设$dp(i,j)$表示前$i$个点分成$j$组的方案数，那么就有一个类似于第二类斯特林数的转移：

$$dp(i,j)=\max\{j-f(\text{node}_i),0\}\cdot dp(i-1,j)+dp(i-1,j-1)$$

$f(x)$的处理非常简单：先把每个点在树上做个标记，然后查询$x$到根$r$的路径上有多少个标记就行了（不要忘了减去自己），树剖+树状数组即可解决。

处理完询问不要忘了清空

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

template <typename T> inline void read(T& x) {
    int f = 0, c = getchar(); x = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - 48, c = getchar();
    if (f) x = -x;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x); read(args...); 
}
template <typename T> void write(T x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> inline void writeln(T x) { write(x); puts(""); }
template <typename T> inline bool chkmin(T& x, const T& y) { return y < x ? (x = y, true) : false; }
template <typename T> inline bool chkmax(T& x, const T& y) { return x < y ? (x = y, true) : false; }

const int maxn = 1e5 + 207;
const int maxm = 307;
const int mod = 1e9 + 7;

int v[maxn << 1], head[maxn], next[maxn << 1], tot;
int dep[maxn], size[maxn], top[maxn], son[maxn], fa[maxn], dfn[maxn], xys;
int n, q;

inline void ae(int x, int y) {
    v[++tot] = y; next[tot] = head[x]; head[x] = tot;
    v[++tot] = x; next[tot] = head[y]; head[y] = tot;
}
void dfs(int x) {
    size[x] = 1; dep[x] = dep[fa[x]] + 1;
    for (int i = head[x]; i; i = next[i])
        if (v[i] != fa[x]) {
            fa[v[i]] = x;
            dfs(v[i]);
            size[x] += size[v[i]];
            if (size[v[i]] > size[son[x]]) son[x] = v[i];
        }
}
void dfs(int x, int t) {
    top[x] = t; dfn[x] = ++xys;
    if (son[x]) dfs(son[x], t);
    for (int i = head[x]; i; i = next[i])
        if (v[i] != son[x] && v[i] != fa[x])
            dfs(v[i], v[i]);
}

int s[maxn];
inline void add(int x, int val) { for (; x <= n; x += x & -x) s[x] += val; }
inline int sum(int l, int r) {
    int ans = 0;
    for (; r; r -= r & -r) ans += s[r];
    for (--l; l; l -= l & -l) ans -= s[l];
    return ans;
}

inline void mark(int x) { add(dfn[x], 1); }
inline void del(int x) { add(dfn[x], -1); }
inline int query(int x, int y) {
    int ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
        ans += sum(dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    return ans + (dep[x] < dep[y] ? sum(dfn[x], dfn[y]) : sum(dfn[y], dfn[x]));
}

int dp[maxn][maxm];
int f[maxn];
int node[maxn], K, m, r;

inline void clear() {
    for (int i = 1; i <= K; ++i)
        for (int j = 1, _end = std::min(i, m); j <= _end; ++j)
            dp[i][j] = 0;
    for (int i = 1; i <= K; ++i) {
        f[node[i]] = 0;
        del(node[i]);
    }
}

int main() {
    read(n, q);
    for (int i = 1, x, y; i < n; ++i)
        read(x, y), ae(x, y);
    dfs(1); dfs(1, 1);
    while (q--) {
        read(K, m, r);
        for (int i = 1; i <= K; ++i) {
            read(node[i]);
            mark(node[i]);
        }
        for (int i = 1; i <= K; ++i)
            f[node[i]] = query(node[i], r) - 1;
        std::sort(node + 1, node + K + 1, [](int a, int b) -> bool { return f[a] < f[b]; });
        dp[1][1] = 1;
        for (int i = 2; i <= K; ++i)
            for (int j = 1, _end = std::min(i, m); j <= _end; ++j)
                if (j - f[node[i]] >= 0)
                    dp[i][j] = (1ll * dp[i - 1][j] * (j - f[node[i]]) % mod + dp[i - 1][j - 1]) % mod;
                else
                    dp[i][j] = dp[i - 1][j - 1];
        int ans = 0;
        for (int i = 1; i <= m; ++i)
            if ((ans += dp[K][i]) >= mod) ans -= mod;
        writeln(ans);
        clear();
    }
    return 0;
}
```


---

## 作者：封禁用户 (赞：7)

同样发布于我的[$\tt CSDN$](https://blog.csdn.net/qq_42101694/article/details/108212827)博客。

# 题目
[传送门 to luogu](https://www.luogu.com.cn/problem/CF1111E)

# 思路
显然是虚树。根据套路，定义状态 $f(x,i)$ 为 $x$ 子树内的所有点放进至多 $i$ 个盒子。

发现不是很好转移。考虑让状态更严格，这样我们知道的信息更多。用 $f(x,i)$ 表示，$x$ 子树内的所有点放进 __恰好__ $i$ 个 __不同的__ 盒子。也就是说，盒子有编号。那么就可以轻松得到转移

$$f(x,i)=\prod_{y\in son(x)}f(y,i)$$

为何是这个式子？因为不同子树内的点可以放入一个盒子，所以直接将对应编号的盒子合并即可。举栗子：

左边子树准备放 $[1],[2]$（注意，这和 $[2],[1]$ 不同），而右边子树放 $[],[3,4]$ ，合并起来就是 $[1],[2,3,4]$ 了。

如果 $x$ 自身是个特殊点呢？显然只能自己放一个盒子。所以最后进行转移

$$f'(x,i)=i\cdot f(x,i-1)$$

就是枚举 $x$ 在哪个盒子中，因为盒子是不同的，所以这 $i$ 个类别是不重复的。

最后输出答案的时候就有问题了，因为实际上，盒子是没有区别的。我们得想办法除以一个阶乘。__非空盒子数的阶乘__。

怎么算恰好有 $j$ 个非空盒子的情况？答案是 __容斥__。记其为 $g(j)$ ，则

$$g(j)=\sum_{i=0}^{j}(-1)^{i}{j\choose i}f(x,j-i)$$

就是枚举有 $i$ 个盒子是空的。这个复杂度是 $\mathcal O(m^2)$ 的。

总复杂度是多少呢？是 $\sum m_i^2\le\max_m\sum m_i\le\max_m\sum k_i$ 的，也就是 $\mathcal O(mk)$ 的，恰好和 $\tt dp$ 复杂度一样。

# 代码
```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long int_;
inline int readint(){
	int a = 0; char c = getchar(), f = 1;
	for(; c<'0'||c>'9'; c=getchar())
		if(c == '-') f = -f;
	for(; '0'<=c&&c<='9'; c=getchar())
		a = (a<<3)+(a<<1)+(c^48);
	return a*f;
}

const int MaxN = 100005;
int n, m;

struct Edge{
	int to, nxt; Edge(){ }
	Edge(int T,int N){
		to = T, nxt = N;
	}
};
Edge e[MaxN<<1];
int cntEdge, head[MaxN];
void addEdge(int a,int b){
	e[cntEdge] = Edge(b,head[a]);
	head[a] = cntEdge ++;
}

int fa[MaxN][20], dep[MaxN];
int dfn[MaxN], dfsClock;
void buildTree(int x,int pre = 0){
	dfn[x] = ++ dfsClock;
	fa[x][0] = pre;
	dep[x] = dep[pre]+1;
	for(int j=0; j+1<20; ++j){
		if(fa[x][j] == 0) break;
		fa[x][j+1] = fa[fa[x][j]][j];
	}
	for(int i=head[x]; ~i; i=e[i].nxt)
		if(e[i].to != pre)
			buildTree(e[i].to,x);
}
int getLca(int a,int b){
	if(dep[a] < dep[b]) swap(a,b);
	for(int j=19; ~j; --j)
		if((dep[a]-dep[b])>>j&1)
			a = fa[a][j];
	if(a == b) return a;
	for(int j=19; ~j; --j)
		if(fa[a][j] != fa[b][j]){
			a = fa[a][j];
			b = fa[b][j];
		}
	return fa[a][0];
}

int rt, all[MaxN];
bool val[MaxN]; // 是否为特殊点
vector< int > v;
bool cmp(const int &a,const int &b){
	return dfn[a] < dfn[b];
}
void build(){
	int k = readint()+1;
	m = readint(), rt = readint();
	for(int i=1; i<k; ++i){
		all[i] = readint();
		val[all[i]] = true;
	}
	all[k] = rt; // matter as well
	sort(all+1,all+k+1,cmp);
	k = unique(all+1,all+k+1)-all-1;
	v.resize(1), v[0] = all[1];
	cntEdge = 0; // head 必须手动赋值
	for(int i=2; i<=k; ++i){
		head[all[i]] = -1;
		head[getLca(all[i-1],all[i])] = -1;
	}
	head[all[1]] = -1; // 别漏了
	for(int i=2; i<=k; ++i){
		int lca = getLca(all[i-1],all[i]);
		while(!v.empty()){
			int x = v.back();
			if(dep[x] <= dep[lca])
				break; // 不需要再弹了
			v.pop_back(); int y = lca;
			if(!v.empty())
			if(dep[v.back()] > dep[lca])
				y = v.back();
			addEdge(x,y), addEdge(y,x);
		}
		if(v.empty() || v.back() != lca)
			v.push_back(lca);
		v.push_back(all[i]);
	}
	while(!v.empty()){
		int x = v.back(); v.pop_back();
		if(v.empty()) break;
		addEdge(v.back(),x);
		addEdge(x,v.back());
	}
}

const int Mod = 1e9+7;
int dp[MaxN][301];
void dfs(int x,int pre){
	for(int j=0; j<=m; ++j)
		dp[x][j] = 1; // nothing
	for(int i=head[x]; ~i; i=e[i].nxt){
		if(e[i].to == pre) continue;
		dfs(e[i].to,x);
		for(int j=0; j<=m; ++j)
			dp[x][j] = 1ll*dp[x][j]*dp[e[i].to][j]%Mod;
	}
	if(val[x]){
		for(int j=m; j; --j)
			dp[x][j] = 1ll*dp[x][j-1]*j%Mod;
		dp[x][0] = 0; // 不可能了
		val[x] = false; // 顺便清空
	}
}

int jc[301]; // 预处理的阶乘
int inv[301]; // 预处理的阶乘的逆元
void prepare(){
	for(int i=jc[0]=1; i<=300; ++i)
		jc[i] = 1ll*jc[i-1]*i%Mod;
	inv[0] = inv[1] = 1;
	for(int i=2; i<=300; ++i)
		inv[i] = 1ll*(Mod-Mod/i)*inv[Mod%i]%Mod;
	for(int i=2; i<=300; ++i)
		inv[i] = 1ll*inv[i]*inv[i-1]%Mod;
}
void solve(int x){
	int ans = 0;
	for(int i=1; i<=m; ++i){
		int res = 0, now;
		for(int j=0; j<=i; ++j){
			now = 1ll*jc[i]*inv[j]%Mod;
			now = 1ll*now*inv[i-j]%Mod;
			if(j&1) now = Mod-now;
			res += 1ll*now*dp[x][i-j]%Mod;
			res %= Mod;
		}
		res = 1ll*res*inv[i]%Mod;
		ans = (ans+res)%Mod;
	}
	printf("%d\n",ans);
}

int main(){
	prepare();
	n = readint(); int q = readint();
	for(int i=1; i<=n; ++i)
		head[i] = -1;
	for(int i=1,a,b; i<n; ++i){
		a = readint(), b = readint();
		addEdge(a,b), addEdge(b,a);
	}
	buildTree(1); // whatever
	while(q --)
		build(), dfs(rt,-1), solve(rt);
	return 0;
}
```


---

## 作者：do_while_true (赞：5)

一个比价劣的根号做法......

首先考虑求出 $num_x$ 表示 $x$ 在 $r$ 为根的树中有多少个祖先是关键点，那么答案就可以 $\mathcal{O}(k\log k+km)$ dp 出。

具体就是先给 $num$ 排个序保证祖先比子孙先被计算到 dp 状态里，然后就是令 $dp_{i,j}$ 表示前 $i$ 个点分 $j$ 组，那么即有转移 $dp_{i,j}=dp_{i-1,j-1}+dp_{i-1,j}\times \max(j-num_i,0)$．

然后根号分治，考虑 $k>\sqrt{10^5}$ 直接暴力 dfs 统计，$k\leq \sqrt{10^5}$ 利用 $\mathcal{O}(n\log n)-\mathcal{O}(1)$ LCA（ST 表）可以做到 $\mathcal{O}(k^2)$ 暴力统计（用 $dis(x,y)+dis(y,z)=dis(x,z)$ 来判断 $y$ 是否在 $x\to z$ 上）。

那么复杂度就可以做到 $\mathcal{O}(n\sqrt n+\sum km)$（假设 $n,q,\sum k$ 同阶）．

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=1000000007;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
const int N=100010;
const int B=350;
int n,q,r;
vi eg[N];
int fac[N],inv[N];
int d[B+10][B+10],in[B+10],f[B+10];
vi tr[B+10];
int g[N],vis[N];
int dp[N][310];
int lg[N<<1],dep[N],dfn[N],rk[N<<1],tot;
int st[20][N<<1];
int cmpd(int x,int y){
	return dep[x]<dep[y]?x:y;
}
int LCA(int x,int y){
	int l=dfn[x],r=dfn[y];
	if(l>r)swap(l,r);
	int k=lg[r-l+1];
	return cmpd(st[k][l],st[k][r-(1<<k)+1]);
}
int dis(int x,int y){
	return dep[x]+dep[y]-2*dep[LCA(x,y)];
}
void dfs1(int x,int fa){
	rk[dfn[x]=++tot]=x;dep[x]=dep[fa]+1;
	for(auto v:eg[x])if(v!=fa){
		dfs1(v,x);
		rk[++tot]=x;
	}
}
void dfs2(int x,int fa,int h){
	g[x]=h;
	for(auto v:eg[x])if(v!=fa)dfs2(v,x,h+vis[x]);
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n,q);
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
	inv[n]=qpow(fac[n],mod-2);for(int i=n-1;~i;--i)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	for(int i=1,u,v;i<n;i++){
		read(u,v);
		eg[u].pb(v);eg[v].pb(u);
	}
	dfs1(1,0);
	for(int i=1;i<=tot;i++)st[0][i]=rk[i];
	for(int i=2;i<=tot;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<20;i++)
		for(int j=1;j+(1<<i)-1<=tot;j++)
			st[i][j]=cmpd(st[i-1][j],st[i-1][j+(1<<(i-1))]);
	while(q--){
		int k,m,r;
		read(k,m,r);
		vi vec;
		for(int i=1,x;i<=k;i++)read(x),vec.pb(x);
		if(k<=B){
			int fl=0,rt=0;
			for(int i=0;i<k;i++)if(vec[i]==r)fl=1,rt=i;
			if(!fl)vec.pb(r),rt=k++;
			for(int i=0;i<k;i++)vi().swap(tr[i]),in[i]=f[i]=0;
			for(int i=0;i<k;i++)
				for(int j=i+1;j<k;j++)
					d[i][j]=d[j][i]=dis(vec[i],vec[j]);
			for(int i=0;i<k;i++)
				for(int j=0;j<k;j++)
					if(i!=j && d[rt][i]+d[i][j]==d[rt][j])
						tr[i].pb(j),++in[j];
			queue<int>q;q.push(rt);
			while(!q.empty()){
				int x=q.front();q.pop();
				for(auto v:tr[x]){
					--in[v];
					if(!in[v]){
						f[v]=f[x]+1;
						q.push(v);
					}
				}
			}
			if(!fl){
				--k;
				for(int i=0;i<k;i++)--f[i];
			}
		}
		else{
			for(auto x:vec)vis[x]=1;
			dfs2(r,0,0);
			for(int i=0;i<k;i++)f[i]=g[vec[i]],vis[vec[i]]=0;
		}
		for(int i=0;i<=k;i++)
			for(int j=0;j<=i;j++)
				dp[i][j]=0;
		dp[0][0]=1;
		sort(f,f+k);
		for(int i=1;i<=k;i++)
			for(int j=0;j<=min(i,m);j++){
				dp[i][j]=j?dp[i-1][j-1]:0;
				if(j>f[i-1])cadd(dp[i][j],1ll*dp[i-1][j]*(j-f[i-1])%mod);
			}
		int ans=0;
		for(int i=0;i<=m;i++)cadd(ans,dp[k][i]);
		cout << ans << '\n';
	}
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：ywy_c_asm (赞：5)

其实这题对换根的处理直接用个LCT无脑处理即可……并不用什么线段树……

首先我看到这题的第一想法就是，这不建个虚树，然后在子树里跑个树形背包不就行了吗？但是这个合并两棵子树并不是一般的卷积的$a+b=c$的形式而是$a+b>=c$的形式，这样复杂度就爆炸了……

这题的最重要的性质就是自己不能和祖先在同一组里，显然，他的祖先们也分属不同的组，然后我们看这个k个点分成m组和第二类斯特林数很像，所以我们可以考虑不在树上dp，而是把这些点提出来用一个类似$dp[i][j]=j*dp[i-1][j]+dp[i-1][j-1]$去搞，即考虑新的一个点是否新建一个组还是放到已经有的j组中的一个去。

那么就可以这样做：我们令每个点的顺序必须排在他祖先之后，然后$i$点有$cnt$个祖先在询问点内，就相当于前面有$cnt$组分别包含了1个祖先，i不能放到那里面去，所以就是$dp[i][j]$为前i个分了j组的方案，$dp[i][j]=(j-cnt)dp[i-1][j]+dp[i-1][j-1]$。

关于换根的问题这个并不用非得求出dfs序搞，我们就是想求出这个点有多少个被标记过的祖先，以及让这个点排在祖先之后，可以用个LCT进行单点加链上求和，然后每个点deep可以通过splay的size判断，就按deep排序就行了。

另外我开始在排序上犯了个错就是我在cmp的时候判断了一下a是否为b的祖先，这个可以用splay上二分判定，但是如果没有祖先关系的话就没法比较了，这个排序在正确性上就是不稳定的，~~还多个log~~

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define p 1000000007
#define isroot(_o) (_o!=ch[fa[_o]][0]&&_o!=ch[fa[_o]][1])
#define opp(_o) (_o==ch[fa[_o]][1])
using namespace std;
namespace ywy{
	inline int get(){
		int n=0;char c;while((c=getchar())||23333){
			if(c>='0'&&c<='9')break;if(c=='-')goto s;
		}n=c-'0';while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10+c-'0';else return(n);
		}s:while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10-c+'0';else return(n);
		}
	}
	int ch[100001][2],fa[100001],val[100001],data[100001],stk[100001],size[100001];
	unsigned char bj[100001];
	inline void up(int tree){
		size[tree]=1+size[ch[tree][0]]+size[ch[tree][1]];
		data[tree]=val[tree]+data[ch[tree][0]]+data[ch[tree][1]];
	}
	int dp[100001][301];
	int ints[100001],deep[100001];
	inline void down(int tree){
		if(!bj[tree])return;bj[tree]=0;
		swap(ch[tree][0],ch[tree][1]);
		bj[ch[tree][0]]^=1;bj[ch[tree][1]]^=1;
	}
	inline void xuan(int me){
		int tree=fa[me],cjr=fa[tree];
		down(cjr);down(tree);down(me);
		int op=opp(me),ls=ch[me][op^1];
		ch[me][op^1]=tree;ch[tree][op]=ls;
		fa[ls]=tree;
		if(!isroot(tree))ch[cjr][opp(tree)]=me;
		fa[me]=cjr;fa[tree]=me;
		up(tree);up(me);
	}
	inline void splay(int tree){
		if(isroot(tree)){down(tree);return;}
		int sp=0,tmp=tree;
		while(!isroot(tmp))stk[sp]=tmp,sp++,tmp=fa[tmp];
		down(tmp);
		while(sp)sp--,down(stk[sp]);
		while(!isroot(tree)){
			int cjr=fa[tree];if(!isroot(cjr))xuan((opp(cjr)==opp(tree))?cjr:tree);xuan(tree);
		}
		up(tree);
	}
	inline void access(int tree){
		splay(tree);down(tree);
		ch[tree][1]=0;up(tree);
		while(fa[tree]){
			int cjr=fa[tree];splay(cjr);down(cjr);
			ch[cjr][1]=tree;up(cjr);splay(tree);
		}
		up(tree);
	}
	inline void makeroot(int tree){
		access(tree);splay(tree);bj[tree]^=1;
	}
	inline void link(int a,int b){
		makeroot(a);makeroot(b);fa[b]=a;
	}
	int rankof(int tree,int rk){
		if(rk<=size[ch[tree][0]])return(rankof(ch[tree][0],rk));
		rk-=size[ch[tree][0]];
		if(rk==1)return(tree);rk--;
		return(rankof(ch[tree][1],rk));
	}
	inline int cmp(const int &a,const int &b){
		return(deep[a]<deep[b]);
	}
	inline void add(int a,int num){
		splay(a);val[a]+=num;data[a]+=num;
	}
	void print(int num){
		if(num>=10)print(num/10);putchar(num%10+'0');
	}
	void ywymain(){
		int n=get(),q=get();
		for(register int i=1;i<=n;i++)size[i]=1;
		for(register int i=1;i<n;i++){
			int s=get(),t=get();link(s,t);
		}
		while(q){
			q--;
			int k=get(),m=get(),rt=get();
			makeroot(rt);
			for(register int i=1;i<=k;i++){
				add(ints[i]=get(),1);access(ints[i]);splay(ints[i]);deep[ints[i]]=size[ch[ints[i]][0]]+1;
			}
			sort(ints+1,ints+1+k,cmp);
			dp[0][0]=1;
			for(register int i=1;i<=k;i++){
				access(ints[i]);splay(ints[i]);
				int cnt=data[ints[i]]-1; 
				for(register int j=max(1,cnt+1);j<=i&&j<=m;j++){
					dp[i][j]=((ll)dp[i-1][j]*(ll)(j-cnt)+dp[i-1][j-1])%p;
				}
			}
			ll ans=0;
			for(register int i=1;i<=m;i++)ans=(ans+dp[k][i])%p
			;print(ans);putchar('\n');
			for(register int i=1;i<=k;i++){
				add(ints[i],-1);for(register int j=1;j<=i&&j<=m;j++)dp[i][j]=0;
			}
		}
	}
}
int main(){
	ywy::ywymain();return(0);
}
```

---

## 作者：luogubot (赞：4)

给定一棵 $n$ 个结点的树，回答 $q$ 次询问，每次询问给定 $k,m,r$ 以及 $k$ 个结点编号，求出以 $r$ 为根的情况下，把 $k$ 个给定点分为至多 $m$ 组点，同组点之间不存在祖先后代关系的方案数。

$n,q,\sum k,r\leq 10^5$，$m\leq 300$。

希望找到单次 $O(mk)$ 的 dp。

考虑一次 $r=1,k=n$ 的询问，在树上 dfs 时转移，设 $f_{i,j}$ 表示考虑了前 $i$ 个访问的点，分了 $j$ 组的方案数。容易转移 $f_{i,j}=(j-dep_{id_i})f_{i-1,j}+f_{i-1,j-1}$，要求 $j\ge dep_i$，其中 $dep_{rt}=0$，$dep_i$ 表示 $i$ 的祖先（不含自己）的个数。相当于始终对一个连通子树添加叶子。这里相当于是按照 dfn 为顺序进行转移。

考虑扩展到 $r=1,k\neq n$ 的情况，依然按照 dfn 序转移，$f_{i,j}=(j-g_{id_i})f_{i-1,j}+f_{i-1,j-1}$，其中 $g_u$ 表示 $u$ 的祖先中关键点的个数。发现“树”的结构被弱化了，做的更像是固定了某个转移顺序的序列 dp。这个顺序仅有一个要求：一个点被加入做 dp 时它的祖先已经完成了转移，即转移式本质只规避了“和祖先放在同一组”的情况，而规避”和子孙放在同一组“的情况由转移顺序来处理。

考虑扩展到 $r\neq 1$ 的情况，失去了"dfn"这个信息，而根据上面的分析，只需要找到一个转移顺序，满足一个点被加入时，其祖先都被加入了。不妨沿用 $g$ 的定义，发现祖先的 $g$ 一定严格小于自己的，则按照 $g$ 从小往大加入做上述 dp。

最后要处理的问题就是怎么算 $g$，即单点加，链求和，可以用 dfn+BIT+LCA 1log 完成。

$O(\sum k(m+\log n))$。[Submission](https://codeforces.com/contest/1111/submission/179007748)。

---

## 作者：chenxinyang2006 (赞：3)

题解里貌似都是二维 DP，但其实可以一维 DP。

分组方案数稍微有点难算，因为 $\{\{1\},\{2\}\}$ 和 $\{\{2\},\{1\}\}$ 是一种分组方案。不妨考虑算出所有 $f_i$ 表示将所有关键点染上颜色 $[1,i]$（每种都被使用），使得不存在一对祖先与后代颜色相同的方案数。

那么答案就是 $\sum\limits_{i=0}^m \dfrac{f_i}{i!}$。

但这样仍然不太好算，不妨继续放宽限制，改为算出 $g_i$ 表示将所有关键点染上 $[1,i]$ 的颜色，不要求每种都被使用的方案数。

$g_p$ 相对是好求的。把根转成 $r$ 后，我们从浅到深考虑每个关键点，只需要让每个点被考虑时，与其祖先颜色都不相同即可满足限制。假设 $i$ 到根有 $t$ 个点（不包含 $i$）。那么根据限制，这 $t$ 个点颜色互不相同，而无论它们怎么染色，$i$ 点总是有 $(p-t)$ 种与它们不同的方案。

故可以得出 $g_p = \prod\limits_{v \in S} (p-t_v)$，$S$ 是给定的点集。

求出所有 $g$ 后，可以通过容斥得到 $f$。具体而言，$f_i = g_i - \sum\limits_{j=0}^{i-1} \dbinom{i}{j} f_j$，$i$ 从 $0 \sim m$ 遍历即可推出所有 $f$。

在算 $g$ 的时候，显然 $t$ 相同的点可以压缩到一起算。于是可以 $O(m^2 \log m)$ 求出所有 $g$。

算 $t$ 是经典的单点修改，链求和。用 dfs 序 + 树状数组可以简单 1log 解决。

于是总复杂度 $O(n + (\sum k) \log n + \sum m^2 \log m)$。

虽然看着多了个 $\log$ 比较劣，但你稍微分析一下就会发现复杂度其实不高于 $\sum km$。

可能可以用多项式科技做到 $m \log^? m$，但我不懂这方面，于是摆烂了。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define mod 1000000007
using namespace std;
int n,q;

int cnt;
int head[100005];
struct eg{
	int to,nxt;
}edge[200005];

void make(int u,int v){
	edge[++cnt].to = v;
	edge[cnt].nxt = head[u];
	head[u] = cnt;
}
int to[20][100005],dep[100005],siz[100005],dfn[100005];

void dfs1(int u,int f){
	to[0][u] = f;
	dep[u] = dep[f] + 1;
	dfn[u] = ++cnt;
	siz[u] = 1;
	for(int i = head[u];i;i = edge[i].nxt){
		int v = edge[i].to;
		if(v == f) continue;
		dfs1(v,u);
		siz[u] += siz[v];
	}
}

int LCA(int u,int v){
	if(dep[u] < dep[v]) swap(u,v);
	for(int i = 17;i >= 0;i--) if(dep[to[i][u]] >= dep[v]) u = to[i][u];
	if(u == v) return u;
	for(int i = 17;i >= 0;i--){
		if(to[i][u] != to[i][v]){
			u = to[i][u];
			v = to[i][v];
		}
	}
	return to[0][u];
}
int tree[100005];

#define lowbit(x) (x & (-x))

void add(int id,int v){
	while(id <= n){
		tree[id] += v;
		id += lowbit(id);
	}
}

int qry(int id){
	int res = 0;
	while(id >= 1){
		res += tree[id];
		id -= lowbit(id);
	}
	return res;
}

int tag[100005];

void modify(int u){//翻转点 u 的状态
	if(tag[u]){
		add(dfn[u],-1);
		add(dfn[u] + siz[u],1);
	}else{
		add(dfn[u],1);
		add(dfn[u] + siz[u],-1);
	}
	tag[u] ^= 1;
}

int query(int u,int v){
	int d = LCA(u,v);
	//printf("LCA of %d and %d=%d\n",u,v,d);
	return qry(dfn[u]) + qry(dfn[v]) - 2 * qry(dfn[d]) + tag[d];
}
int S[100005],tmp[100005],rec[305];//到 r 路径上有 i 个点的有 rec[i] 个点
ll C[305][305],fact[305],ifac[305],f[305];//f[i] 分为 i 组的方案数

ll power(ll p,int k){
	ll ans = 1;
	while(k){
		if(k % 2 == 1) ans = ans * p % mod;
		p = p * p % mod;
		k /= 2;
	}
	return ans;
}

void calc(int m){
	int p;//rec[i] \neq 0 的最大 i
	for(int i = 0;i <= m;i++) if(rec[i]) p = i;
	for(int i = 0;i <= m;i++) f[i] = 0;

	for(int i = p + 1;i <= m;i++){
		f[i] = 1;
		for(int j = 0;j <= p;j++) f[i] = f[i] * power(i - j,rec[j]) % mod;
	}
	//printf("array f:\n");
	//for(int i = 0;i <= m;i++) printf("%lld ",f[i]);
	//printf("\n");
	ll ans = 0;
	for(int i = 0;i <= m;i++){
		for(int j = i + 1;j <= m;j++){
			f[j] -= f[i] * C[j][i] % mod;
			f[j] %= mod;
		}
		ans = (ans + f[i] * ifac[i]) % mod;
	}
	//for(int i = 0;i <= m;i++) printf("%lld ",f[i]);
	//printf("\n");
	ans = (ans + mod) % mod;
	printf("%lld\n",ans);
}

int main(){
	fact[0] = ifac[0] = 1;
	for(int i = 1;i <= 300;i++) fact[i] = fact[i - 1] * i % mod;
	for(int i = 1;i <= 300;i++) ifac[i] = power(fact[i],mod - 2);
	for(int i = 1;i <= 300;i++){
		C[i][0] = C[i][i] = 1;
		for(int j = 1;j < i;j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	}
	scanf("%d%d",&n,&q);
	for(int i = 1;i < n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		make(u,v);make(v,u);
	}
	cnt = 0;
	dfs1(1,0);
	//for(int i = 1;i <= n;i++) printf("node %d siz %d fa %d dep %d dfn %d\n",i,siz[i],to[0][i],dep[i],dfn[i]);
	//printf("\n");

	for(int i = 1;i <= 17;i++){
		for(int j = 1;j <= n;j++){
			to[i][j] = to[i - 1][to[i - 1][j]];
		}
	}
	int k,m,r;
	for(int i = 1;i <= q;i++){
		scanf("%d%d%d",&k,&m,&r);
		for(int j = 1;j <= k;j++) scanf("%d",&S[j]);
		for(int j = 1;j <= k;j++) modify(S[j]);
		for(int j = 1;j <= k;j++) tmp[j] = query(S[j],r);
		for(int j = 1;j <= k;j++) modify(S[j]);
		//for(int j = 1;j <= k;j++) printf("%d ",tmp[j]);
		//printf("\n");

		for(int j = 1;j <= k;j++) rec[tmp[j] - 1]++;
		calc(m);
		for(int j = 1;j <= k;j++) rec[tmp[j] - 1]--;
	}
	return 0;
}
```


---

## 作者：Helloworldwuyuze (赞：2)

# Tree (CF1111E)

## Des

给定一棵树和若干次询问。每次询问有若干个数，前三个为 $k,m,r$ 分别表示节点数量，分组数量和根节点。即选中树上的 $k$ 个节点，在 $r$ 为根的情况下至多分成 $m$ 组有多少种分法，要求每个组内不能出现祖先关系。

其中 $\sum k\le 10^5, m\le 300$。

## Sol

是不是一眼虚树，但其实完全没必要。考虑动态规划。我们发现一个点能分到哪几个组里只与它有多少个关键节点祖先有关。因此，我们可以假设我们已经知道了它有多少个祖先，并且都做完了这些祖先的动态规划，然后试着转移当前节点。

因为 $m$ 很小，所以我们完全可以设成二维的状态 $f_{i,j}$ 表示前 $i$ 个点分成 $j$ 组的方案数。那么一个点可以分到原来的组里面，也可以自己一个组。而它不能分到祖先在的组里面。因此，我们设 $s(u)$ 表示 $u$ 有多少个关键节点祖先，那么很容易得到转移方程：

$$f_{i,j} = \max\{ j - s(i), 0\}\times f_{i-1, j} + f_{i-1, j-1}$$

然后就可以考虑如何先计算祖先。我们发现可以提前把点按照 $dfn$ 排序，这样就一定能够保证祖先在 $u$ 之前就被处理到。但是每一次的根节点不一样，因此我们可以考虑先计算出 $s(u)$，这样 $s(u)$ 小的一定是大的的祖先。那么 $s(u)$ 使用树剖求 $(r, u)$ 路径上的关键节点数量即可。复杂度 $O(n\log^2n +nm)$。

## Code

```cpp
#define int long long
const int INF = 0x3f3f3f3f;
typedef pair<int,int> PII;
typedef pair<int,PII> PIII;
const int N = 1e5 + 10;
const int M = 3e2 + 10;
const int MOD = 1e9 + 7;

int n,q,m,k,r;
int a[N], s[N], f[N][M];
vector<int> g[N];

namespace BIT{
	int b[N];
	#define lowbit(x) (x&-x)
	void update(int x,int k){ for(int i=x;i<=n;i+=lowbit(i))	b[i]+=k;}
	int query(int x){ int ans=0; for(int i=x;i;i-=lowbit(i))	ans+=b[i]; return ans;}
	#undef lowbit
}

namespace cut{
	int dfn[N], rk[N], top[N], siz[N], son[N], dep[N], fa[N], idx;
	void dfs1(int x,int fat){
		fa[x] = fat, siz[x] = 1, dep[x] = dep[fat]+1;
		for(int y:g[x]){
			if(y==fat)	continue;
			dfs1(y,x);
			siz[x]+=siz[y];
			if(siz[y]>siz[son[x]])	son[x]=y;
		}
	}
	void dfs2(int x,int tp){
		top[x] = tp, dfn[x] = ++idx, rk[idx] = x;
		if(son[x])	dfs2(son[x], tp);
		for(int y:g[x])
			if(y!=son[x] && y!=fa[x])	dfs2(y, y);
	}
	int query(int x,int y){
		int ans = 0;
		while(top[x] != top[y]){
			if(dep[top[x]]<dep[top[y]])	swap(x,y);
			// cout<<x<<" "<<y<<" "<<top[x]<<endl;
			ans += BIT::query(dfn[x]) - BIT::query(dfn[top[x]]-1);
			x = fa[top[x]];
		}
		if(dep[x]<dep[y])	swap(x,y);
		// cout<<x<<" "<<y<<endl;
		return ans + BIT::query(dfn[x]) - BIT::query(dfn[y]-1);
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n>>q;
	for(int i=2, x, y; i<=n; ++i)	cin>>x>>y, g[x].pb(y), g[y].pb(x);
	cut::dfs1(1, 0), cut::dfs2(1, 1);
	while(q--){
		cin>>k>>m>>r;
		for(int i=1;i<=k;++i)	cin>>a[i], BIT::update(cut::dfn[a[i]], 1);
		for(int i=1;i<=k;++i)	s[i] = cut::query(a[i], r) - 1;
		// for(int i=1;i<=k;++i)	cout<<s[i]<<" ";
		// cout<<endl;
		sort(s+1, s+1+k);
		f[1][1] = 1;
		for(int i = 2; i<=k; ++i)
			for(int j = 1, _end = min(i, m); j<=_end; ++j)
				f[i][j] = (max(j-s[i], 0ll) * f[i-1][j] % MOD + f[i-1][j-1]) % MOD;
		int ans = 0;
		for(int i=1;i<=m;++i)	ans = (ans + f[k][i]) % MOD;
		cout<<ans<<endl;
		for(int i=1;i<=k;++i)	BIT::update(cut::dfn[a[i]], -1);
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

考虑一个到根上有 $p$ 个点的时候他有多少种符合要求的选择方案。不难发现是 $m-p$。于是感觉答案就是所有点这玩意的乘积。

然而其实这个做法有问题，考虑一个分成 $m-1$ 个集合的方案，这种方案会被重复计算 $m$ 次（空集可能在 $1\sim m$）位置。于是可以考虑容斥。钦定有 $t$ 个集合，计算答案。

注意集合是无序的，要在最后乘上 $t!$，$t$ 为集合个数。

关于如何计算一个点到给定根 $r$ 路径上点的个数，这个先转化成每个点子树加，给定根子树加是经典题。

复杂度是单次询问 $O(m^2+k\log n+mk)$，分析一下可得总复杂度 $\sum k(m+\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1; 
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1; 
	}
	return ans;
}
vector<int> vc[100005];
int a[100005],b[100005],dep[100005],ind[100005],outd[100005],cnt,f[100005][18];
int fac[100005],inv[100005];
void dfs1(int now,int fa){
	f[now][0]=fa;
	for(int i=1;i<=17;i++) f[now][i]=f[f[now][i-1]][i-1];
	dep[now]=dep[fa]+1;
	ind[now]=++cnt;
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs1(v,now);
	}
	outd[now]=cnt;
}
int lca(int u,int v){
	if(dep[u]>dep[v]) swap(u,v);
	for(int i=17;i>=0;i--) if(dep[f[v][i]]>=dep[u]) v=f[v][i];
	if(u==v) return u;
	for(int i=17;i>=0;i--) if(f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
	return f[u][0];
}
int gup(int u,int v){
	if(dep[u]>dep[v]) swap(u,v);
//	cout<<u<<" "<<v<<"  ";
	for(int i=17;i>=0;i--) if(dep[f[v][i]]>dep[u]) v=f[v][i];
	return v;
}
struct sgt{
	int f[1000005],lzt[1000005];
	void pushdown(int i,int l,int r){
		f[i*2]+=lzt[i]*(mid-l+1);
		f[i*2+1]+=lzt[i]*(r-mid);
		lzt[i*2]+=lzt[i];
		lzt[i*2+1]+=lzt[i];
		lzt[i]=0;
	}
	void build(int i,int l,int r){
		if(l==r){
			f[i]=b[l];
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		f[i]=f[i*2]+f[i*2+1];
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			f[i]+=cg*(r-l+1);
			lzt[i]+=cg;
			return ;
		}
		pushdown(i,l,r);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
		f[i]=f[i*2]+f[i*2+1];
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		if(ql>r||qr<l) return 0;
		pushdown(i,l,r);
		return qry(i*2,l,mid,ql,qr)+qry(i*2+1,mid+1,r,ql,qr);
	}
}tree;
int C(int i,int j){
	if(i<j||i<0||j<0) return 0;
	return fac[i]*inv[j]%mod*inv[i-j]%mod;
}
signed main(){
    ios::sync_with_stdio(false);
	fac[0]=1; for(int i=1;i<=100000;i++) fac[i]=fac[i-1]*i%mod;
	inv[100000]=qp(fac[100000],mod-2); for(int i=99999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
    ios::sync_with_stdio(false);
	int n,q; cin>>n>>q;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	dfs1(1,0);
	tree.build(1,1,n);
	while(q--){
		int k,m,rt; cin>>k>>m>>rt;
		vector<int> vc;
		for(int i=1;i<=k;i++){
			int v; cin>>v; vc.push_back(v);
		}
		int f[m+1],tot=0;
		for(auto v:vc){
			if(v==rt) tree.change(1,1,n,1,n,1);
			else if(ind[v]<=ind[rt]&&ind[rt]<=outd[v]) tree.change(1,1,n,1,n,1),tree.change(1,1,n,ind[gup(rt,v)],outd[gup(rt,v)],-1);
			else tree.change(1,1,n,ind[v],outd[v],1);
		}
		vector<int> vcc;
		for(auto v:vc){
			vcc.push_back(tree.qry(1,1,n,ind[v],ind[v]));
		}
		for(auto v:vc){
			if(v==rt) tree.change(1,1,n,1,n,-1);
			else if(ind[v]<=ind[rt]&&ind[rt]<=outd[v]) tree.change(1,1,n,1,n,-1),tree.change(1,1,n,ind[gup(rt,v)],outd[gup(rt,v)],1);
			else tree.change(1,1,n,ind[v],outd[v],-1);
		}
		for(int p=1;p<=m;p++){
			int ans=1;
			for(auto v:vcc){
				(ans*=(p-v+1))%=mod;
			}
			f[p]=ans;
			for(int l=1;l<p;l++){
				(f[p]+=mod-f[l]*C(p,l)%mod)%=mod;
			}
			(tot+=f[p]*inv[p])%=mod;
		}
		cout<<tot<<"\n";
	}
	return 0;
}
```

---

## 作者：MikukuOvO (赞：1)

看着好像一道虚树题。。。

还是考虑题目的性质，假设我们已经将虚树建出来，那么该怎么做。

我们将虚树中的每个点按照$dfn$序排序，那么如果一个点是另一个点的祖先，那么就一定排在前面。

我们定义$f[i][j]$表示考虑前$i$个点，分成$j$组的方案数。

$f[i][j]+=f[i-1][j-1]+f[i-1][j] \times (j-cnt[i])$

其中$cnt[i]$表示$i$的祖先个数。

但是由于题目中的换根操作的存在，直接建虚树有一些困难。

考虑到本题虚树的价值在于求出一个点到根节点路径的关键点的数目，根节点不固定则变成两点间关键点的数目，发现可以用树剖处理。

复杂度$nlogn+n \times m$

```cpp
const int N=1e5+5;
const int M=305;
const ll mod=1e9+7;

int n,q,cnt,idx;
int head[N],dep[N],anc[N],siz[N],son[N],top[N],s[N],id[N],dfn[N];
ll t[N],f[N][M];
struct edge
{
    int to,nxt;
};
edge e[N<<1];

void add(int x,int y)
{
    e[++cnt].to=y;
    e[cnt].nxt=head[x];
    head[x]=cnt;
}
void link(int x,int y)
{
    add(x,y),add(y,x);
}
void dfs1(int x,int fa,int d)
{
    dep[x]=d,anc[x]=fa,siz[x]=1;
    int maxson=0;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==fa) continue;
        dfs1(v,x,d+1);
        siz[x]+=siz[v];
        if(siz[v]>maxson) maxson=siz[v],son[x]=v;
    }
}
void dfs2(int x,int topf)
{
    top[x]=topf,id[x]=++idx;
    if(son[x]) dfs2(son[x],topf);
    for(int i=head[x];i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==anc[x]||v==son[x]) continue;
        dfs2(v,v);
    }
}
int lowbit(int x)
{
    return x&-x;
}
void modify(int x,int z)
{
    while(x<=n) t[x]+=z,x+=lowbit(x);
}
int query(int x)
{
    int res=0;
    while(x) res+=t[x],x-=lowbit(x);
    return res;
}
int calc(int x,int y)
{
    int res=0;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        res+=query(id[x])-query(id[top[x]]-1);
        x=anc[top[x]];
    }
    if(dep[x]<dep[y]) swap(x,y);
    res+=query(id[x])-query(id[y]-1);
    return res;
}
int main()
{
    fio();
    gi(n,q);
    for(int i=1,x,y;i<=n-1;++i) gi(x,y),link(x,y);
    dfs1(1,0,1),dfs2(1,1);
    while(q--)
    {
        int k,m,r;
        gi(k,m,r);
        for(int i=1;i<=k;++i) gi(s[i]),modify(id[s[i]],1);
        for(int i=1;i<=k;++i) dfn[s[i]]=calc(s[i],r)-1;
        sort(s+1,s+k+1,[](int x,int y){
            return dfn[x]<dfn[y];
        });
        f[0][0]=1;
        for(int i=1;i<=k;++i)
        {
            for(int j=1;j<=min(i,m);++j)
            {
                if(j<dfn[s[i]]) f[i][j]=f[i-1][j-1];
                else f[i][j]=(f[i-1][j-1]+f[i-1][j]*(j-dfn[s[i]])%mod)%mod;
            }
        }
        ll ans=0;
        for(int i=1;i<=m;++i) ans=(ans+f[k][i])%mod;
        print(ans),pc(10);

        for(int i=1;i<=k;++i) modify(id[s[i]],-1);
        for(int i=1;i<=k;++i) for(int j=1;j<=min(i,m);++j) f[i][j]=0;
    }
    end();
}
```

---

## 作者：Memory_of_winter (赞：1)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/10357755.html)

**题目大意：**给一棵$n(n\leqslant10^5)$个点的树，有$q(q\leqslant10^5)$次询问，每次询问给出$k,m,r$表示把一下$k$个点分成不超过$m$组，使得在以$r$为根的情况下，组内的任意两个结点不存在祖先关系。$\sum k\leqslant10^5,m\leqslant300$

**题解：**针对一次询问，可以想到一个$DP$，$f_{i,j}$表示处理到第$i$个点（假设为$u$），$u$的祖先都已经处理完，这$i$个点放到$j$组的方案数。$f_{i,j}=f_{i-1,j-1}+f_{i-1,j-father_u}$，$father_u$表示这$k$个点中$u$的祖先的个数。

现在考虑如何处理$DP$顺序，发现可以深度由浅到深处理，$dfs$序也是可以的。而后再考虑如何处理$father$，我想到了几种写法：

1. 用树状数组，给子树加，然后查询需要的点，这种写法因为换根需要分类讨论，复杂度$O(k\log_2n)$。
2. 树剖后单点加，询问需要的点到根的和（这种写法在写之前被我以为需要分类讨论），复杂度$O(k\log_2^2n)$。
3. 建虚树，直接$dfs$，复杂度$O(k\log_2k)$。

我写的时候不想分类讨论，就选择了第$3$种，在我交的时候成功跑到$rank$倒一。写题解的时候突然发现这种写法似乎复杂度最优秀？~~自带大常数~~



**C++ Code：**

```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
#define maxn 100010
const int mod = 1e9 + 7;
inline void reduce(int &x) { x += x >> 31 & mod; }

int head[maxn], cnt;
struct Edge {
	int to, nxt;
} e[maxn << 1];
inline void addedge(int a, int b) {
	e[++cnt] = (Edge) { b, head[a] }; head[a] = cnt;
	e[++cnt] = (Edge) { a, head[b] }; head[b] = cnt;
}

namespace Tree {
	int sz[maxn], dep[maxn], fa[maxn];
	int dfn[maxn], out[maxn], top[maxn], idx;
#define f top
	int find(int x) { return x == f[x] ? x : (f[x] = find(f[x])); }
#undef f
	void dfs(int u) {
		int son = 0; top[u] = u;
		dfn[u] = ++idx, sz[u] = 1;
		for (int i = head[u], v; i; i = e[i].nxt) {
			v = e[i].to;
			if (v != fa[u]) {
				dep[v] = dep[u] + 1, fa[v] = u;
				dfs(v), sz[u] += sz[v];
				if (sz[v] > sz[son]) son = v;
			}
		}
		out[u] = idx; if (son) top[son] = u;
	}
	inline int LCA(int x, int y) {
		while (top[x] != top[y]) {
			if (dep[top[x]] > dep[top[y]]) x = fa[top[x]];
			else y = fa[top[y]];
		}
		return dep[x] < dep[y] ? x : y;
	}
}
using Tree::dfn;
using Tree::out;

int n, q, k, m, r;

int Mark[maxn], f[305], idx;
inline bool cmp(int x, int y) { return dfn[x] < dfn[y]; }

void dfs(int u, int fa = 0, int num = 0) {
	if (Mark[u]) {
		++idx;
		for (int i = std::min(m, idx); ~i; --i) {
			if (i > num) f[i] = (static_cast<long long> (i - num) * f[i] + f[i - 1]) % mod;
			else f[i] = 0;
		}
		++num;
	}
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].to;
		if (v != fa) dfs(v, u, num);
	}

	head[u] = Mark[u] = 0;
}

void solve() {
	static int List[maxn << 1], tot, S[maxn], top;
	std::cin >> k >> m >> r;
	for (int i = 0; i < k; ++i) {
		std::cin >> List[i];
		Mark[List[i]] = 1;
	}
	tot = k;
	if (!Mark[r]) List[tot++] = r;

	std::sort(List, List + tot, cmp);
	for (int i = tot - 1; i; --i) List[tot++] = Tree::LCA(List[i], List[i - 1]);
	tot = (std::sort(List, List + tot, cmp), std::unique(List, List + tot) - List);
	top = 0;
	for (int I = 0, i = *List; I < tot; i = List[++I]) {
		while (top && out[S[top]] < dfn[i]) --top;
		if (top) addedge(S[top], i);
		S[++top] = i;
	}

	f[idx = 0] = 1, dfs(r);
	int ans = 0;
	for (int i = 1; i <= m; ++i) reduce(ans += f[i] - mod);
	std::cout << ans << '\n';

	cnt = 0;
	__builtin_memset(f, 0, m + 1 << 2);
}

int main() {
	std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
	std::cin >> n >> q;
	for (int i = 1, a, b; i < n; ++i) {
		std::cin >> a >> b;
		addedge(a, b);
	}
	Tree::dfs(1);
	for (int i = 1; i <= n; ++i) Tree::find(i);
	__builtin_memset(head, 0, n + 1 << 2), cnt = 0;

	while (q --> 0) solve();
	return 0;
}

```



---

## 作者：newbiechd (赞：1)

# CF1111E Tree

[LG传送门](https://www.luogu.org/problemnew/show/CF1111E)

日常安利[博客](https://www.cnblogs.com/cj-chd/p/10352143.html)。

对于每个询问点$x$，设它的祖先即不能和它放在同一个集合中的点的个数为$f[x]$，设$dp[i][j]$表示前$i$个询问点放在$j$个非空集合中的方案数，注意这里“前$i$个”的意义，这表示会对第$i$个点造成影响的点都已被考虑过了，转移就是$dp[i][j] = dp[i - 1][j] * (j - f[j]) + dp[i -1][j - 1]$。

下面的问题就是怎么处理出$f$数组和找出DP的顺序。发现$f$数组可以直接树剖：先在线段树上把所有询问点更新一遍，然后再查询每个点到当前根的路径上询问点的个数，$f[x]$就是线段树上查询的值$- 1$（不算自己）。处理出$f$数组之后，发现祖先的$f$值一定比子孙的$f$值小，那么直接对$f$数组排一边序就可以DP了。

UPD:改正了DP转移的手误

```cpp
//written by newbiechd
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define R register
#define I inline
#define B 1000000
#define L long long
using namespace std;
const int N = 100003, yyb = 1e9 + 7;
char buf[B], *p1, *p2;
I char gc() { return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, B, stdin), p1 == p2) ? EOF : *p1++; }
I int rd() {
    R int f = 0;
    R char c = gc();
    while (c < 48 || c > 57)
        c = gc();
    while (c > 47 && c < 58)
        f = f * 10 + (c ^ 48), c = gc();
    return f;
}
int a[N], s[N], fa[N], dep[N], siz[N], son[N], dfn[N], top[N], f[N], v[N << 2], n, tim;
L dp[N], ans;
vector <int> g[N];
void dfs1(int x, int f) {
    fa[x] = f, dep[x] = dep[f] + 1, siz[x] = 1;
    for (R int i = 0, y, m = 0; i < s[x]; ++i)
        if ((y = g[x][i]) ^ f) {
            dfs1(y, x), siz[x] += siz[y];
            if (siz[y] > m)
                m = siz[y], son[x] = y;
        }
}
void dfs2(int x, int t) {
    dfn[x] = ++tim, top[x] = t;
    if (son[x])
        dfs2(son[x], t);
    for (R int i = 0, y; i < s[x]; ++i)
        if ((y = g[x][i]) ^ fa[x] && y ^ son[x])
            dfs2(y, y);
}
void modify(int k, int l, int r, int x, int y) {
    v[k] += y;
    if (l == r)
        return ;
    R int p = k << 1, q = p | 1, m = l + r >> 1;
    if (x <= m)
        modify(p, l, m, x, y);
    else
        modify(q, m + 1, r, x, y);
}
int tquery(int k, int l, int r, int x, int y) {
    if (x <= l && r <= y)
        return v[k];
    R int p = k << 1, q = p | 1, m = l + r >> 1, o = 0;
    if (x <= m)
        o += tquery(p, l, m, x, y);
    if (m < y)
        o += tquery(q, m + 1, r, x, y);
    return o;
}
int query(int x, int y) {
    R int o = 0;
    while (top[x] ^ top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        o += tquery(1, 1, n, dfn[top[x]], dfn[x]), x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    return o + tquery(1, 1, n, dfn[x], dfn[y]);
}
int main() {
    R int Q, k, m, rt, i, j, x, y, flag;
    n = rd(), Q = rd();
    for (i = 1; i < n; ++i)
        x = rd(), y = rd(), g[x].push_back(y), g[y].push_back(x);
    for (i = 1; i <= n; ++i)
        s[i] = g[i].size();
    dfs1(1, 0), dfs2(1, 1);
    while (Q--) {
        k = rd(), m = rd(), rt = rd(), ans = 0, flag = 0;
        for (i = 1; i <= k; ++i)
            a[i] = rd(), modify(1, 1, n, dfn[a[i]], 1);
        for (i = 1; i <= k; ++i) {
            f[i] = query(a[i], rt) - 1;
            if (f[i] >= m)
                flag = 1;
        }
        for (i = 1; i <= k; ++i)
            modify(1, 1, n, dfn[a[i]], -1), dp[i]  = 0;
        if (flag) {
            printf("0\n");
            continue;
        }
        sort(f + 1, f + k + 1), dp[0] = 1;
        for (i = 1; i <= k; ++i)
            for (j = min(i, m); ~j; --j) {
                if (j <= f[i])
                    dp[j] = 0;
                dp[j] = (dp[j] * (j - f[i]) + dp[j - 1]) % yyb;
            }
        for (j = 1; j <= k; ++j)
            ans = (ans + dp[j]) % yyb;
        printf("%I64d\n", ans);
    }
    return 0;
}

```

---

