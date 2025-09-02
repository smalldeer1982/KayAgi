# [SDOI/SXOI2022] 小 N 的独立集

## 题目描述

小 N 喜欢出最大权独立集问题。

有一天，他接到了一系列的出题任务，于是他顺手出了一系列最大权独立集问题。

为了同时给这一系列题目造数据，小 N 生成了一个 $n$ 个点的树，并选定了一个正整数 $k$。这样每生成一组数据时，他只需要对于每个点，随机生成一个在 $1 \sim k$ 之间的整数点权，就可以生成一个新的最大独立集问题。

小 N 把这些题给了他的好朋友，小 Ω。小 Ω 表示，这些题太多太乱了，他打算把所有的 $k^n$ 道题归类处理。一个自然的想法就是按答案（也就是最大权独立集中的点的权值之和）分类，显然这些最大权独立集问题的答案一定在 $1 \sim nk$ 之间，所以小 Ω 只需要将所有题目按照答案分成 $nk$ 类进行管理就行了。

在小 N 正式开始出题之前，小 Ω 先要算出每一类题目具体有多少道。稍加估计之后小 Ω 很快意识到自己并没有《诗云》中描述的那种存储器，于是断然拒绝了小 N 关于“先把所有可能的题目造好再慢慢分类统计数量”的建议，然后悲剧地意识到自己并不会计算这些数字。

他想叫你帮他解决这个问题，还说如果你成功解决了这个问题，那么在小 N 出那些最大权独立集问题的时候，他会帮你提交一份标程代码。

## 说明/提示

**【样例解释】**

符合题意的最大权独立集题目一共有 $2^4=16$ 道。

可以证明，当点 $1$, $3$, $4$ 的权值均为 $1$ 时，最大权独立集为 $3$ ，这样的题目共有 $2$ 道；点 $1$, $3$, $4$ 的权值恰有一个为 $2$ 时，最大权独立集为 $4$ ，这样的题目共有 $6$ 道；对于最大权独立集为 $5$ 或 $6$ 的情况也是类似的。

**【数据范围】**

对于 $15 \%$ 的数据， $n \leq 8$；  
对于 $30 \%$ 的数据， $n \leq 30$；  
对于 $50 \%$ 的数据， $n \leq 100$；  
对于另外 $10 \%$ 的数据， $k=1$；  
对于另外 $15 \%$ 的数据， $k=2$；  
对于 $100 \%$ 的数据， $n \leq 1000$，$k \leq 5$，$u_{i}, v_{i} \leq n$。

**【提示】**

最大权独立集问题是指：选择一个点集，使得任意两个被选择的点都没有边直接相连，并且使得所有被选择的点的点权之和最大。


## 样例 #1

### 输入

```
4 2
1 2
2 3
2 4```

### 输出

```
0
0
2
6
6
2
0
0```

# 题解

## 作者：Un1quAIoid (赞：28)

**传送门：**[P8352 [SDOI/SXOI2022] 小 N 的独立集](https://www.luogu.com.cn/problem/P8352)


------------
### 题意
 给定 $n$ 个点的树的形态以及点的权值范围 $k$，对于任意 $i \in [1,kn]$，
求有多少种权值分配方案，使得树的最大权独立集大小为 $i$。


------------

**1. 经典 dp $(n \le 8)$：**

枚举所有权值分配方案，设 $f_{u,0/1}$ 表示 $u$ 子树中点 $u$ 不选/选的最大独立集然后做经典树上最大权独立集 dp 即可，复杂度 $O(nk^n)$。

**2. dp 套 dp $(n \le 100)$：**

经典 dp 和极小的值域 $(k \le 5)$ 启发我们可以**将 $f_{u,0/1}$ 的值设为状态**。

设 $g_{u,v0,v1}$ 为 $u$ 子树中 $f_{u,0},f_{u,1}$ 分别为 $v0,v1$ 时的方案数。转移时考虑将 $u$ 的一个儿子 $v$ 合并到 $u$ 中，枚举 $i,j,p,q$ 分别作为 $f_{u,0},f_{u,1},f_{v,0},f_{v,1}$，易得转移：

$$g'_{u,i+\max(p,q),j+p} \gets g'_{u,i+\max(p,q),j+p}+g_{u,i,j} \times g_{v,p,q}$$

套用树上背包的复杂度分析可得时间复杂度为 $O(n^4k^4)$，加上判0远远跑不满，能够通过 $n \le 100$。

因为状态转移时是将内层 $f$ 的转移结果作为外层 $g$ 的状态来转移的，所以称作 dp 套 dp。

**3. 状态优化 $(n \le 1000)$：**

上文的 dp 方法复杂度瓶颈在于状态数就已经到达了 $O(n^3k^2)$ 级别，此时可以考虑**简化内层 $f$ 的状态和转移**，考虑另一种树上最大权独立集的 dp 方法：重新定义 $f_{u,0/1}$ 表示 $u$ 子树内是(1)否(0)强制**不选**节点 $u$ 时的最大方案大小，转移显然，如此设便得到了一条重要性质：$0 \le f_{u,0}-f_{u,1} \le val_{u} \le k$（强制不选的答案肯定小于等于无限制的答案，且两者一定不会差出 $u$ 点的权值），此时自然得出 $g_{u,v1,d}$ 表示 $u$ 子树中 $f_{u,0},f_{u,1}$ 分别为 $v1+d,v1$ 时的方案数，依然枚举 $i,j,p,q$，有转移：

$$g'_{u,i+p+q,\max(i+j+p,i+p+q)-(i+p+q)} \gets g'_{u,i+p+q,\max(i+j+p,i+p+q)-(i+p+q)}+g_{u,i,j} \times g_{v,p,q}$$

时间复杂度$O(n^2k^4)$，加判0跑得很快

代码（代码中的 $f$ 数组即为 $g$）：

```cpp
//dp套dp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1001;
const int Mod = 1e9+7;

int n, k, siz[MAXN];
int f[MAXN][MAXN * 5][6], t[MAXN * 5][6];
int head[MAXN], edge_num;

struct edge {
    int nxt, to;
} T[MAXN * 2];

inline void add(int u, int v) {
    T[++edge_num] = (edge) {head[u], v};
    head[u] = edge_num;
}

inline void Add(int &a, int b) { a += b; if (a >= Mod) a -= Mod; }

void dfs(int x, int fa) {
    siz[x] = 1;
    for (int i = 1; i <= k; i++) f[x][0][i] = 1;
    for (int i = head[x]; i; i = T[i].nxt) {
        int son = T[i].to;
        if (son == fa) continue;
        dfs(son, x);
        memset(t, 0, sizeof(t));
        for (int i = 0; i <= k * siz[x]; i++)
            for (int j = 0; j <= k; j++) if (f[x][i][j])
                for (int p = 0; p <= k * siz[son]; p++)
                    for (int q = 0; q <= k; q++) if (f[son][p][q])
                        Add(t[i + p + q][max(i + j + p, i + p + q) - (i + p + q)], 1ll * f[x][i][j] * f[son][p][q] % Mod);
        memcpy(f[x], t, sizeof(t));
        siz[x] += siz[son];
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }

    dfs(1, 0);

    for (int i = 1; i <= k * n; i++) {
        int ans = 0;
        for (int d = 0; d <= min(i, k); d++) Add(ans, f[1][i - d][d]);
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：401rk8 (赞：9)

很好的签到题，为啥 SX 没人过呢？
 
本文中的 $m$ 是题目中的 $k$

### 考场做法
考虑 DP。设 $f[u,i,j]$ 为子树 $u$，选/不选 $u$ 的最大权独立集为 $i,j$ 的方案数。转移：$f'[u,i+l,j+\max(k,l)]\leftarrow f[u,i,j]\times f[v,k,l]$，注意顺序。

状态数 $O(n^{3}m^{2})$，但实际上远远达不到这个上界（有没有好哥哥教我怎么算复杂度啊/kel）。同时注意到 **$i\le j$ 时转移不需要用到 $i$，可以把这样的状态合并为 $ff[u,j]$**。赛时发现了状态数并不多但认为是二维 FFT 之类的东西就不管了

我使用了 `cc_hash_table` 保存状态，获得了 80pts

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std; using namespace __gnu_pbds; using namespace __gnu_cxx;
#define For(i,x,y,...) for(int i=(x),##__VA_ARGS__;i<=(y);++i)
#define rFor(i,x,y,...) for(int i=(x),##__VA_ARGS__;i>=(y);--i)
#define Rep(i,x,y,...) for(int i=(x),##__VA_ARGS__;i<(y);++i)
#define pb emplace_back
#define sz(a) int((a).size())
#define all(a) begin(a),end(a)
#define MT make_tuple
#define MP make_pair
#define fi first
#define se second
typedef long long LL; typedef unsigned uLL;
typedef vector<int> Vi; typedef pair<int,int> Pii;
template<typename X,typename Y>bool ckmin(X &x,Y y) { return y<x ? x=y,1 : 0; }
template<typename X,typename Y>bool ckmax(X &x,Y y) { return x<y ? x=y,1 : 0; }
sfmt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r) { return uniform_int_distribution<>(l,r)(mt); }
#define endl '\n'
namespace IO { const int L = 1<<22; char a[L],*l=a,*r=a,b[L],*p=b;
auto gc=[]() { if(l==r)r=(l=a)+fread(a,1,L,stdin);return l==r?EOF:*l++; };
auto pc=[](char x) { if(p-b==L)fwrite(b,1,L,stdout),p=b;*p++=x; };
struct IO {
	~IO() { fwrite(b,1,p-b,stdout); }
	template<typename T>IO& operator >> (T &x) {
		x=0;bool f=1;char c;while(!isdigit(c=gc()))if(c=='-')f=0;
		if(f)do x=x*10+c-48;while(isdigit(c=gc()));
		else do x=x*10-c+48;while(isdigit(c=gc()));
		return *this;
	}
	IO& operator >> (char *s) {
		while(!isgraph(*s=gc())); while(isgraph(*++s=gc()));
		return *s=0, *this;
	}
	IO& operator << (char x) { pc(x); return *this; }
	IO& operator << (char *s) { while(*s)pc(*s++); return *this; }
	IO& operator << (const char *s) { while(*s)pc(*s++); return *this; }
	template<typename T>IO& operator << (T x) {
		if(!x)pc(48);
		else{static char s[44];char *t=s;if(x<0)pc('-'),*t++=-(x%10),x=-(x/10);
		for(;x;x/=10)*t++=x%10;while(s!=t)pc(*--t|48);}
		return *this;
	}
} io; } using IO::io;
const int mod = 1e9+7;
template<typename T>T Mod(T x) { return x<0 ? x+mod : x<mod ? x : x-mod; }
template<typename X,typename Y>void ckadd(X &x,Y y)
	{ x = x+y<0 ? x+y+mod : x+y<mod ? x+y : x+y-mod; }
LL Pow(LL x,LL y=mod-2) { LL z=1;for(;y;y>>=1,x=x*x%mod)if(y&1)z=z*x%mod;return z; }

const int N = 1005;
int n,m;
LL ans[N*5];
Vi e[N];
struct Hash {
	size_t operator () (const Pii &x) const
		{ return x.fi * 131 + x.se; }
}; cc_hash_table<Pii,LL,Hash> f[N];
cc_hash_table<int,LL> ff[N];

void dfs(int u,int fa) {
	for(int v : e[u]) if( v != fa ) dfs(v,u);
	For(i,1,m) f[u][MP(i,0)] = 1;
	for(int v : e[u]) if( v != fa ) {
		auto g(f[u]); f[u].clear();
		for(auto i : g) {
			for(auto j : f[v])
				(f[u][MP(i.fi.fi+j.fi.se,i.fi.se+j.fi.fi)] +=
					i.se * j.se) %=mod;
			for(auto j : ff[v])
				(f[u][MP(i.fi.fi+j.fi,i.fi.se+j.fi)] += i.se * j.se) %=mod;
		}
	}
//	cerr<<u<<":\n";
//	for(auto i : f[u]) cerr<<i.fi.fi<<' '<<i.fi.se<<": "<<i.se<<endl;
	auto g(f[u]); f[u].clear();
	for(auto i : g)
		if( i.fi.fi <= i.fi.se ) ckadd(ff[u][i.fi.se],i.se);
		else f[u][i.fi] = i.se;
}

signed main() { freopen("nset.in","r",stdin); freopen("nset.out","w",stdout);
	io>>n>>m; Rep(i,1,n, x,y) io>>x>>y, e[x].pb(y), e[y].pb(x);
	dfs(1,0);
	for(auto i : f[1]) ckadd(ans[max(i.fi.fi,i.fi.se)],i.se);
	for(auto i : ff[1]) ckadd(ans[i.fi],i.se);
	For(i,1,n*m) io<<ans[i]<<endl;
//	int TM=0; For(i,1,n) TM += sz(f[i]); cerr<<TM<<endl;
	return 0;
}
```

### 正解
另一个观察是 **$j\ge i-m$（一个选 $u$ 的方案去掉 $u$ 就可以变为不选 $u$ 的方案）**。因此有用的状态只有 $O(nm^{2})$ 种：$i\le j$ 或 $1\le i-j\le m$。转移复杂度类似树上背包

[代码](https://www.luogu.com.cn/record/75939774)把上文中先转移到 $f[u]$ 再合并到 $ff[u]$ 改为直接转移到 $ff[u]$ 即可，不贴了

另一个能过的思路是发现全程只用到了 $j,\max(i,j)$，所以把这两个放进 DP 状态，敢写敢 AC

---

碎碎念：


一开始看错题了，以为 $O(n^{2}m)$ 随便做/kk。后面读对了也没细想，写完暴力就跑了，于是输麻了。几乎写出了正解还是白丢 20pts，完美体现了不带脑子做题，只能说不愧是我。

考场策略也很重要。花了大量时间做 T2，但一个包只有 2,3pts，以放弃思考 T1 T3 为代价其实是不值的

希望读者以我为鉴吧

---

## 作者：云浅知处 (赞：5)

容易想到设计 $f(u,x,y)$ 表示给以 $u$ 为根的子树填数，选 $u$ 时的最大权独立集大小为 $x$，不选 $u$ 时为 $y$ 的方案数。转移就直接写一下树上最大权独立集那个 DP，有

$$
f(u,x_1,y_1)\times f(v,x_2,y_2)\to f(u,x_1+y_2,y_1+\max(x_2,y_2))
$$

复杂度是 $O(n^3k^4)$。

然后发现，当 $x\le y$ 的时候记录 $x$ 没有意义，若 $x>y$，那么 $x-y\le k$。因此可以记录 $f(u,j,y)$ 表示以 $u$ 为根的子树填数，选 $u$ 时的最大权独立集大小为 $y+j$（$j>0$） 或者 $\le j$（$j=0$），不选 $u$ 时最大权独立集大小为 $y$ 的方案数。转移式类似：

$$
f(u,j_1,y_1)\times f(v,j_2,y_2)\to f(u,\max(0,j_1-j_2),y_1+y_2+j_2)
$$

复杂度 $O(n^2k^4)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=1e9+7;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
int randint(int l,int r){return rand()*rand()%(r-l+1)+l;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}

const int N=1005;
const int K=6;

int f[N][K][N*K],n,k,ans[N*K];
vector<int>G[N];

int tmp[K][N*K],sz[N];
void DP(int u,int fa){
	sz[u]=1;
	for(int i=1;i<=k;i++)f[u][i][0]=1;
	for(int v:G[u]){
		if(v==fa)continue;
		DP(v,u);
		for(int i=0;i<=k;i++)for(int j=0;j<=(sz[u]+sz[v])*k;j++)tmp[i][j]=0;
		for(int x=0;x<=k;x++)for(int i=0;i<=sz[u]*k;i++){
			if(!f[u][x][i])continue;
			for(int y=0;y<=k;y++)for(int j=0;j<=sz[v]*k;j++)if(f[v][y][j])add(tmp[max(0,x-y)][i+j+y],1ll*f[u][x][i]*f[v][y][j]%mod);
		}
		sz[u]+=sz[v];for(int i=0;i<=k;i++)for(int j=0;j<=sz[u]*k;j++)f[u][i][j]=tmp[i][j];
	}
}

signed main(void){

#ifdef YUNQIAN
	freopen("2.in","r",stdin);
	freopen("2.out","w",stdout);
#endif

	n=read(),k=read();
	for(int i=2;i<=n;i++){
		int u=read(),v=read();
		G[u].emplace_back(v),G[v].emplace_back(u);
	}
	DP(1,0);
	for(int i=0;i<=k;i++){
		for(int j=0;j<=n*k;j++)add(ans[i+j],f[1][i][j]);
	}
	for(int i=1;i<=n*k;i++)cout<<ans[i]<<endl;

	return 0;
}
```

---

## 作者：Anita_Hailey (赞：4)

## [SDOI2022] 小 N 的独立集

### 题意

给你一个 $N$ 个点的树，然后每个点的点权是 $1\sim K$，求这个树最大独立集是 $x$ 的方案数（对于 $x\in [1,N \times K]$ 求解。

$N\le 1000,1\le K\le 5$

###  题解

一眼就是 dp 套 dp。

> dp 的时候，我们一般会**设计**一个 dp 状态，然后让 dp 从某个状态向某个状态**转移**，最终统计某些状态最终的值。
>
> 而在 dp套dp 里面，我们就将内层 dp 的结果作为外层 dp 的状态进行 dp。

有一个经典的求解树上最大独立集的方法，设 $f[x][0/1]$ 表示选没选 $x$ 这个节点的最大值。

但是这种方法在这道题不是很适合，因为说，你考虑设 $dp[i][x][y]$ 表示做到了 $i$ 子树，然后 $f[i][0]=x，f[i][1] = y$ 的方案数，然后转移是考虑合并两个节点的话，首先你枚举 $x,y,x1,y1$，之后转移就好了，是平凡的。这种做法是 $O(N^4k^4)$ 的，十分的不太行。

考虑换一个状态 $f[x][0/1]$ 表示设是否强制不选 $x$ 的方案数量。然后就可以得到 $f[x][0]\le f[x][1] \le f[x][0] + K$。这是显然的，因为你强制不选了之后肯定会比原来小，但是不会小过一个 $K$。

然后定义状态 $g[i][p][q]$ 表示 $i$ 子树，然后 $f[i][1] = p,f[i][0] = p + q$ 的方案数，之后转移就是你枚举 $j,l,k,h$ 的话，$f[x][j][l] \times f[y][k][h]$ 可以转移到 $f[x][j + k + h][\max(0,l - h)]$ 这是因为如果强制不选 $x$ ，则可以选 $y$，对应的答案是 $j+k+h$；一种选择是不选 $y$，那么此时可以选 $x$ ，对应的答案是 $j + k + \max(h,l)$ 。

```cpp
// Siriqwq
#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::vector;
using std::copy;
using std::reverse;
using std::sort;
using std::get;
using std::unique;
using std::swap;
using std::array;
using std::cerr;
using std::function;
using std::map;
using std::set;
using std::pair;
using std::mt19937;
using std::make_pair;
using std::tuple;
using std::make_tuple;
using std::uniform_int_distribution;
using ll = long long;
namespace qwq {
	mt19937 eng;
	void init(int Seed) {return eng.seed(Seed);}
	int rnd(int l = 1, int r = 1000000000) {return uniform_int_distribution<int> (l, r)(eng);}
}
template<typename T>
inline void chkmin(T &x, T y) {if (x > y) x = y;}
template<typename T>
inline void chkmax(T &x, T y) {if (x < y) x = y;}
template<typename T>
inline T min(const T &x, const T &y) {return x < y ? x : y;}
template<typename T>
inline T max(const T &x, const T &y) {return x > y ? x : y;}
template<typename T>
inline void read(T &x) {
	x = 0;
	bool f = 0;
	char ch = getchar();
	while (!isdigit(ch)) f = ch == '-', ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	if (f) x = -x;
}
template<typename T, typename ...Arg>
inline void read(T &x, Arg &... y) {
	read(x);
	read(y...);
}
#define O(x) cerr << #x << " : " << x << '\n'
const double Pi = acos(-1);
const int MAXN = 1010, MOD = 1e9 + 7, inv2 = (MOD + 1) / 2, I32_INF = 0x3f3f3f3f;
const long long I64_INF = 0x3f3f3f3f3f3f3f3f;
auto Ksm = [] (int x, int y) -> int {
	if (y < 0) {
		y %= MOD - 1;
		y += MOD - 1;
	}
	int ret = 1;
	for (; y; y /= 2, x = (long long) x * x % MOD) if (y & 1) ret = (long long) ret * x % MOD;
	return ret;
};
auto Mod = [] (int x) -> int {
	if (x >= MOD) return x - MOD;
	else if (x < 0) return x + MOD;
	else return x;
};
template<const int N_num, const int M_num>
struct Graph {
	int H[N_num];
	struct Edge {int to, lac;} e[M_num];
	inline void add_edge(int x, int y) {e[*H] = {y, H[x]};H[x] = (*H)++;}
	inline void init() {memset(H, -1, sizeof H);*H = 0;}
};
#define go(x, y) for (int i = x.H[y], v; (v = x.e[i].to) && ~i; i = x.e[i].lac)
inline int ls(int k) {return k << 1;}
inline int rs(int k) {return k << 1 | 1;}
Graph<MAXN, MAXN * 2> tr;
int N, K, f[MAXN][MAXN * 5][6], sz[MAXN], g[MAXN * 5][6];
void dfs(int u, int fa) {
	for (int i = 1; i <= K; ++i) f[u][0][i] = 1;
	sz[u] = K;
	go(tr, u) {
		if (v == fa) continue;
		dfs(v, u);
		memset(g, 0, sizeof g);
		for (int j = 0; j <= sz[u]; ++j) for (int l = 0; l <= K; ++l) if (f[u][j][l]) {
			for (int k = 0; k <= sz[v]; ++k) for (int h = 0; h <= K; ++h) if (f[v][k][h]) {
				g[j + k + h][max(0, l - h)] = (g[j + k + h][max(0, l - h)] + (ll) f[u][j][l] * f[v][k][h]) % MOD;
			}	
		}
		memcpy(f[u], g, sizeof f[u]);
		sz[u] += sz[v];
	}
}
int main() {
	// std::ios::sync_with_stdio(0);
	// cout << std::fixed << std::setprecision(8);
	// cin.tie(0);
	// cout.tie(0);
	freopen("1.in", "r", stdin);
	qwq::init(20050112);
	read(N, K);
	tr.init();
	for (int i = 1, x, y; i < N; ++i) {
		read(x, y);
		tr.add_edge(x, y);
		tr.add_edge(y, x);
	}
	dfs(1, 0);
	for (int i = 1; i <= N * K; ++i) {
		ll ans = 0;
		for (int j = 0; j <= i && j <= K; ++j) ans += f[1][i - j][j];
		printf("%lld\n", ans % MOD);
	}
	// cout << (-3 / 2);
	cerr << ((double) clock() / CLOCKS_PER_SEC) << '\n';
	return (0-0);
}
```

---

## 作者：_Cheems (赞：2)

题解只有 $\rm dp$ 套 $\rm dp$ 做法？来补充下丑陋的 $\rm dp$ 套反悔贪心方法。

显然，定义 $f_{u,i}$ 表示 $u$ 子树、最大权独立集为 $i$ 的情况数。那么第二维怎么定义呢？

最大权独立集可以 $\rm dp$ 解决，尝试再套个 $\rm dp$ 解决。

但是 $\rm dp$ 是以顶部取不取为状态，但是“取不取”是**人为决定**的，而我们要求的是**不同树**的种类数，似乎不太好处理重复情况。

总之，蒟蒻太菜了，不会 $\rm dp$ 套 $\rm dp$，至此走上一条歪路。

众所周知，反悔贪心也能解决最大权独立集。具体来说，令 $g_i$ 表示由取 $i\to$ 不取 $i$ 的代价。然后对于 $u$，令 $res=\sum\limits_{v\in son_u} g_v$，若 $a_u\ge res$ 则取 $u$，$g_u=a_u-res$；反之不取 $u$，$g_u=0$。
 
显然不同树的 $g$ 是唯一确定的。同时 $g_u$ 只有 $\le a_u$ 才有意义，且 $g_u$ 不可能为 $0$，这是可以归纳验证的。总之 $0\le g\le a$。

注意到 $a_u\le k$，$k$ 非常小，所以以 $g$ 为第二维。定义 $f_{u,i,j}$ 表示 $u$ 子树、最大权独立集为 $i$、$g_u=j$ 时的情况数。

转移是容易的。可以先不考虑 $a_u$ 填什么，计算出 $f_{u,i,j}$。然后枚举 $a_u$，按照反悔贪心过程转移就好啦。

复杂度 $O(n^2k^4)$。

卡常注意事项：

1. 注意卡好循环上界；特判到 $0$ 直接跳过；

2. 可以稍微更改下 $f$ 定义，一开始就把 $a_u$ 考虑进来。

魔改完代码后发现和 $\rm dp$ 套 $\rm dp$ 做法极其相似！

看了看，发现另一种做法的状态优化思路和反悔贪心貌似有着异曲同工之妙。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ADD(a, b) a = (a + (b)) % mod
const int N = 1e3 + 5, K = 5, mod = 1e9 + 7;
int n, k, u, v;
int siz[N], f[N][N * K][K + 1], G[N][N * K][K + 1];
vector<int> to[N];

inline void dfs(int u, int fa){
	siz[u] = 1; 
	for(int uk = 1; uk <= k; ++uk) f[u][uk][uk] = 1;
	for(auto v : to[u])
		if(v ^ fa){ 
			dfs(v, u);
			for(int j = 0; j <= siz[u] * k; ++j) 
				for(int p = 0; p <= k; ++p) G[u][j][p] = f[u][j][p], f[u][j][p] = 0;
			for(int j = 0; j <= siz[v] * k; ++j)
				for(int p = 0; p <= k; ++p)
					if(f[v][j][p])
						for(int j2 = 0; j2 <= siz[u] * k; ++j2)
							for(int p2 = 0; p2 <= k; ++p2)
								ADD(f[u][j + j2 - min(p, p2)][max(0, p2 - p)], 1ll * f[v][j][p] * G[u][j2][p2] % mod);
			siz[u] += siz[v];
		}
}
signed main(){
	cin >> n >> k;
	for(int i = 1; i < n; ++i) scanf("%d%d", &u, &v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	for(int i = 1; i <= n * k; ++i){
		int res = 0;
		for(int p = 0; p <= min(i, k); ++p) ADD(res, f[1][i][p]);
		printf("%d\n", res);	
	}
	return 0;
}
```

---

## 作者：LinkyChristian (赞：2)

**年轻人的第一道 dp of dp**

虽然不是我的第一道 dp of dp。但是这题十分的经典，很符合我对 dp of dp 的想象。

考虑如果每个点的权值是固定的，这就是经典的 [没有上司的舞会](https://www.luogu.com.cn/problem/P1352) 。设 $f_{i,0/1}$ 分别表示在 $i$ 的子树中，强制 $i$ 不选 / 强制 $i$ 选的最大权值。

发现 $k<5$ ，因此 $f_{i,0/1}$ 的值是 $O(n)$ 级别的。我们考虑**将dp的值作为状态**，设 $g_{u,i,j}$ 表示 $f_{u,0}$ 和 $f_{u,1}$ 分别为 $i$ 和 $j$ 时的方案数。转移直接枚举 $u$ 和其儿子 $v$ 的状态转移即可。

发现这样光是状态数就已经是 $O(n^3)$ ，无法通过。

考虑优化内层 dp。我们重新设 $f_{i,0/1}$ 为强制 $i$ 不选 / **不强制** $i$ 选的方案个数。

发现强制 $i$ 不选最多比不强制 $i$ 选权值少 $k$ ，也就是 $i$ 本身的权值。因此我们做一个差分，设 $g_{u,i,d}$ 表示 $f_{u,0}$ 和 $f_{u,1}$ 分别为 $i$ 和 $i+d$ 时的方案数。这次我们的状态数降到了 $O(n^2k^2)$ 。接下来直接 dp 即可，可以通过。


---

## 作者：vectorwyx (赞：2)

时隔四个月回顾一下在场上给我带来不小阴影的这道题……

首先对于树上最大独立集有一个广为人知的 dp ：记 $F(i,0/1)$ 表示只考虑 $i$ 的子树，且 $i$ 本身选没选的最大独立集。转移 $F(i,0)=\sum_{i\to p} \max(F(p,0),F(p,1)),F(i,1)=\sum F(p,0)$。

现在问题反过来了，不难想到把上述 dp 的 $f(i,0)$ 与 $f(i,1)$ 包到状态里去，也就是 dp 套 dp。记 $f(x,i,j)$ 表示只考虑 $x$ 的子树有多少种方案使得 $F(x,0)=i,F(x,1)=j$，转移就
按照树形背包的方式直接枚举当前子结点 $p$ 的所有状态 $(i,j)$ 然后把 $f(p,i,j)$ 按照 $F$ 的转移接上去。复杂度是 $O(n^4k^2)$，过不去啊！接下来我们需要优化这个 dp。

而这题其实难点就在于选择一个正确的方向。熟悉相关套路的话应该知道 dp 套 dp 最常用的优化手段就是压缩内层 dp 的状态。然而当时我对 dp 套 dp 一无所知，看到外层转移感觉很像卷积，就走上了不归路。

正解只需要注意到 $F(x,0),F(x,1)$ 始终满足 $F(x,0)\ge F(x,1)-a_x\iff F(x,0)+a_x\ge F(x,1)$，其中 $a_x$ 为 $x$ 的点权。这个不等式是显然的，因为对于某个选了 $x$ 的决策我们只需要把 $x$ 从方案中去掉可以得到一个不选 $x$ 的决策。换句话说 $0\le\max(F(x,0),F(x,1))-F(x,0)\le a_x\le k$。

而内层 $F$ 的转移实际上只用到了 $F(p,0)$ 与 $\max(F(p,0),F(p,1))$，因此可以修改内层 dp 的状态：记 $f(x,i,j)$ 表示只考虑 $x$ 的子树有多少种方案使得 $F(x,0)=i,\max(F(x,0),F(x,1))=i+j$。由于 $j\le k$，所以状态数被压缩成了 $O(n^2k^2)$。

转移时先把当前的根节点放在一边不管它，只考虑合并子树。假设当前要把 $f(p,i,j)$ 合并进来，那么内层 dp 对应的转移是 $F(x,0)\to F(x,0)+i+j,F(x,1)\to F(x,1)+i$。
由于我们最终只关心 $F(x,0)$ 与 $\max(F(x,0),F(x,1))$ 的差，那么记 $\triangle=F(x,0)-F(x,1)$，内层转移相当于 $F(x,0)\to F(x,0)+i+j,\triangle\to\triangle+j$。而根节点的影响是 $F(x,1)\to F(x,1)+a_x$，所以如果 $\triangle\ge k$ 最终一定有 $F(x,0)>F(x,1)$，于是可以再做一个 dp：记 $g(i,j)$ 表示合并完某些子树后目前的 $F(x,0)=i,F(x,0)-F(x,1)=j$ 的方案数，$g$ 的转移是标准的树形背包。从 $g$ 推 $f$ 就再枚举一下 $a_x$ 的值，$g(i,j<a_x)$ 会贡献到 $f(x,i,a_x-j)$，$g(i,j\ge a_x)$ 会贡献到 $f(i,0)$。然后就做完了。复杂度 $O(n^2k^2)$。

代码如下：

```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned int
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
#define ptc putchar
#define emp emplace
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){int ch=getchar(),x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=1005,M=6,qlr=1e9+7;
int f[N][N*M][M],g[N*M][M],h[N*M][M],n,m,siz[N],V,ans[N*M];
vector<int> e[N];

#define add(x,y) (x=(x+y)%qlr)
#define amod(x,y) (x+=y,x=x>=qlr?x-qlr:x)
void dfs(int x,int fa){
	//printf("dfs(%d,%d)\n",x,fa);
	siz[x]=m;
	for(int i:e[x]) if(i!=fa){
		dfs(i,x);
		siz[x]+=siz[i];
	}
	int sum=0;
	fo(i,0,siz[x]) fo(j,0,m) g[i][j]=0;
	g[0][0]=1;
	for(int p:e[x]) if(p!=fa){
		fo(i,0,siz[x]) fo(j,0,m) h[i][j]=0;
		fo(i,0,sum)
			fo(j,0,m) if(g[i][j])
				fo(k,0,siz[p])
					fo(w,0,m) if(f[p][k][w])
						add(h[i+k+w][min(m,j+w)],(ll)g[i][j]*f[p][k][w]);
		sum+=siz[p];
		fo(i,0,siz[x]) fo(j,0,m) g[i][j]=h[i][j];
	}
	
	fo(w,1,m){
		fo(i,0,siz[x]){
			fo(j,0,w-1) amod(f[x][i][w-j],g[i][j]);
			fo(j,w,m) amod(f[x][i][0],g[i][j]);
		}
	}
	/*printf("%d:\n",x);
	//cout<<"g:"
	fo(i,0,siz[x]){
		fo(j,0,m) printf("(%d,%d)=%d ",i,j,f[x][i][j]);
		ptc('\n');
	}*/
}

signed main(){
	//freopen("2.in","r",stdin);freopen(".out","w",stdout);
	cin>>n>>m;V=n*m;
	fo(i,2,n){
		int x=read(),y=read();
		e[x].pb(y),e[y].pb(x);
	}
	dfs(1,0);
	fo(i,0,siz[1]) fo(j,0,m) amod(ans[i+j],f[1][i][j]);
	fo(i,1,siz[1]) cout<<ans[i]<<'\n';
	return 0;
}
/*
-------------------------------------------------
*/

```


---

## 作者：Hell0_W0rld (赞：1)

# [P8352 小 N 的独立集](https://www.luogu.com.cn/problem/P8352) 题解

## 0 题目大意
一个 $n$ 个点的树（随机的），每个点都被在 $[1,k]$ 之间赋随机权，求对于 $\forall i \in [1,nk]$，该树的最大独立集大小为 $i$ 的赋值方案数。

## 1 当 $n^k\leq 1000$ 时
不说了。暴力枚举每一种情况即可。

期望得分 $25$ pts。
## 2 当 $ n\leq 100$ 时，
首先传统的最大独立集是树形 DP：$f[u][0/1]$ 表示以 $u$ 为根的子树里，$u$ 选或不选的最优方案，答案为 $\max\{f[1][0],f[1][1]\}$。

这里要求的是使得答案为 $\max\{f[1][0],f[1][1]\}$ 的方案数，一个明显的 dp 套 dp：令 $g[u][f_0][f_1]$ 表示以 $u$ 为根的子树内，dp 值为 $f_0, f_1$ 的方案数。

容易得出转移方程：$g[u][f_0][f_1]=\sum\limits_{v\in S}\sum\limits_{v_0=0}^{nk}\sum\limits_{v_1=0}^{nk}g[v][v_0][v_1]\cdot g[u][f_0-\max\{v_0,v_1\}][f_1-v_0]$，其中 $S$ 表示 $u$ 的儿子编号集合。

至于转移方程怎么来的，~~请读者自证~~参考最大独立集的转移方程以及乘法原理即可。

而根据树形 dp 基础知识，我们知道可以把 push 改为 pull，时间复杂度会少一只 $O(n)$。

所以时间复杂度 $O(n^4 k^4)$。期望得分 $60$ pts。
## 3 当 $n\leq 1000, k\leq 5$ 时，
本蒟蒻认为较难的 Trick。

修改最大独立集的状态：$f[u][1]$ 表示以 $u$ 为根的子树里，$u$ **选或不选**（原来是必须选！）的最优方案。

此时我们有 $f[u][1]\geq f[u][0]$，同时修改 $g$ 数组的定义：$g[u][dp][de]$ 表示以 $u$ 为根的子树内，$f[u][0]=dp$，$f[u][1]=dp+de$ 的方案数。

则明显 $de\leq k$，再加上上面的转移类似修改，即可 AC 本题了。

$\color{#30BFA7}\Large\texttt{Talk is cheap, show my code.}$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rep(i,l,r) for(register ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(register ll i=(r);i>=(l);--i)
#define all(x) x.begin(),x.end()
using namespace std;
namespace IO{
	const int sz=1<<22;
	char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
	inline char gc(){
		return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
	}
	template<class T> void gi(T& x){
		x=0; char c=gc();
		for(;c<'0'||c>'9';c=gc());
		for(;c>='0'&&c<='9';c=gc())
			x=x*10+(c-'0');
	}
	inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
	inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
	template<class T> void pi(T x,char c='\n'){
		if(x<0) pc('-'),x=-x;
		if(x==0) pc('0'); int t=0;
		for(;x;x/=10) p[++t]=x%10+'0';
		for(;t;--t) pc(p[t]); pc(c);
	}
	struct F{~F(){flush();}}f;
}
using IO::gi;
using IO::pi;
const ll N=1009,MOD=1e9+7;
ll gu[N*5][7],g[N][N*5][7],cnt[N*5],sz[N],n,k;
vector<ll> to[N];
void dfs(ll u,ll fa){
	sz[u]=1;
	rep(du,1,k)g[u][0][du]=1;
	for(ll i=0;i<to[u].size();i++){
		ll v=to[u][i];
		if(v==fa)continue;
		dfs(v,u);
		memset(gu,0,sizeof(gu));
		rep(u0,0,k*sz[u])rep(du,0,k)if(g[u][u0][du])
			rep(v0,0,k*sz[v])rep(dv,0,k)if(g[v][v0][dv]){
				ll A=u0+v0+dv,B=u0+du+v0;
				gu[A][max(A,B)-A]=(gu[A][max(A,B)-A]+g[v][v0][dv]*g[u][u0][du]%MOD)%MOD;
			}
		memcpy(g[u],gu,sizeof(gu));
		sz[u]+=sz[v];
	}
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>n>>k;
	rep(i,2,n){
		ll u,v;
		cin>>u>>v;
		to[u].push_back(v);
		to[v].push_back(u);
	}
	dfs(1,0);
	rep(u0,0,k*n)rep(du,0,k){
		cnt[u0+du]+=g[1][u0][du];
//		rep(i,1,n)cout<<i<<" "<<u0<<" "<<du<<" "<<g[i][u0][du]<<endl;
	}
	rep(u0,1,k*n)cout<<cnt[u0]%MOD<<endl;
	return 0;
}
```

---

## 作者：Chy12321 (赞：1)

还是先打暴力，枚举 $k^n$ 种树的形态做树形 DP，时间复杂度 $\mathcal O(nk^n)$，拿下 $n \le 8$ 和 $k = 1$ 的 $25$ 分。

虽然很简单，还是交代下吧：设 $f(u, 0/1)$ 表示以 $u$ 为根的子树中是否选 $u$ 的最大权独立集，$f(u, 0) \gets w_u + \sum\limits_{v \in son_u} \max\{f(v, 0), f(v, 1)\}, f(u, 1) \gets \sum\limits_{v \in son_u} f(v, 0)$。答案是 $\max\{f(u, 0), f(u,1)\}$。

把相同的 $\mathcal O(n)$ DP 做 $k^n$ 次很笨蛋，考虑优化这个过程，上 DP 套 DP！

设 $F(u, i,j)$ 表示 $f(u, 0) = i, f(u, 1) = j$ 的方案数，转移时考虑逐个加入子结点 $v$，有：
$$
F'(u, i, j) \gets F'(u, i, j) + \sum_{p, q \le i} F(u, i - \max\{p, q\}, j - p) \times F(v, p, q)
$$
然后状态数 $\mathcal O(n^2k^3)$，时间复杂度 $\mathcal O(n^4k^4)$（单层时间复杂度 $\mathcal O(n^4k^4)$，树形 DP 时间复杂度 $\mathcal O(n)$，根据主定理，取大的单层时间复杂度），非常跑不满，但也不可能过，能有 $60$ 分吧？

不合法状态很多，且转移时用到的是 $\max\{i, j \}$，单独记个 $j$ 显得有些浪费，考虑优化。

有一个重要性质是 $\max\{f(u, 0), f(u, 1) \} \in [f(u, 0), f(u, 0) + k]$，证明是显然的：$f(u, 0) \ge f(u, 1) - w_u, w_u \in [1, k]$。

根据这个性质，设 $F(u, i, j)$ 表示 $f(u, 0) = i, \max\{f(u, 0), f(u, 1)\} = f(u, 0) + j$ 的方案数。

转移时同样是考虑逐个加入子结点 $v$，有：
$$
F'(u, i + p + q, \max\{j - q, 0\}) \gets F'(u, i + p + q, \max\{j - q, 0\}) + F(u, i, j) \times F(v, p, q)
$$
初值： $\forall u, f(u, 0, j) = 1(j \in [1, k])$。

答案： $ans_l = \sum\limits_{i + j = l} F(1, i, j)$。

跑自身 $\mathcal O(n)$ 树形 DP 的时候，每层的时间复杂度是 $\mathcal O(n^2k^4)$，根据主定理，取大的单层时间复杂度，总时间复杂度 $\mathcal O(n^2k^4)$。

实际实现时还可以在转移时对为 $0$ 的状态剪枝，飞快！

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

constexpr int N = 1e3 + 10, K = 5 + 1, MOD = 1e9 + 7;

int n, k, sz[N], f[N][N * K][K], fu[N * K][K];

vector<int> G[N];
inline void add(int u, int v) {G[u].emplace_back(v), G[v].emplace_back(u);}

void dfs(int u, int fa) {
    sz[u] = 1;
    for (int j = 1; j <= k; j++) f[u][0][j] = 1;
    for (int v : G[u]) if (v != fa) {
        int maxi = k * sz[u];
        dfs(v, u); sz[u] += sz[v];
        int maxp = k * sz[v];
        for (int i = 0; i <= maxi; i++) {
            for (int j = 0; j <= k; j++) if (f[u][i][j]) {
                for (int p = 0; p <= maxp; p++) {
                    for (int q = 0; q <= k; q++) if (f[v][p][q]) {
                        int x = i + p + q, y = max(j - q, 0);
                        fu[x][y] = (fu[x][y] + 1ll * f[u][i][j] * f[v][p][q]) % MOD;
                    }
                }
            }
        }
        maxi = k * sz[u];
        for (int i = 0; i <= maxi; i++) for (int j = 0; j <= k; j++) f[u][i][j] = fu[i][j], fu[i][j] = 0;
    }
}

int main() {
    // freopen("2.in", "r", stdin), freopen("a.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 1, u, v; i < n; i++) cin >> u >> v, add(u, v);
    dfs(1, 0); n *= k;
    for (int i = 1; i <= n; i++) {
        ll ans = 0;
        for (int j = max(i - k, 0); j <= i; j++) ans += f[1][j][i - j];
        cout << ans % MOD << '\n';
    }
    return 0;
}
```

---

## 作者：Fzrcy (赞：0)

当我们已知每个点的权值时，可以设 $f_{u,0/1}$ 表示在子树 $u$ 中 $u$ 不选/选的最大权独立集的权值和，$O(n)$ dp 计算最大权独立集。

回到原题，考虑将 $f_{u,0/1}$ 作为状态的一部分，设 $g_{u,f_{u,0},f_{u,1}}$ 表示子树 $u$ 中 $u$ 不选、选的最大权独立集的权值和分别为 $f_{u,0}$ 和 $f_{u,1}$ 时的方案数，转移方程为：
$$
g_{u,x+\max(p,q),y+p}=g_{u,x+\max(p,q),y+p}+g_{u,x,y}\times g_{v,p,q}
$$
时间复杂度为 $O(n^3k^2)$。

考虑优化状态数，将 $f_{u,0/1}$ 的定义修改为在子树 $u$ 中 $u$ 不选/**不强制选**的最大权独立集的权值和。可以发现 $f_{x,1}-f_{x,0}\le k$，所以 $g_{u,f_{u,0},f_{u,1}}$ 可以改为 $g_{u,f_{u,0},d}$，表示在子树 $u$ 中 $u$ 不选/**不强制选**的最大权独立集的权值和分别为 $f_{u,0}$ 和 $f_{u,0}+d$ 时的方案数。

则 $g_{u,f_{u,0},d}$ 的转移方程为：
$$
g_{u,i+x+y,\max(i+j+x,i+x+y)-(i+x+y)}=g_{u,i+x+y,\max(i+j+x,i+x+y)-(i+x+y)}+g_{u,i,j}\times g_{v,x,y}
$$
时间复杂度为 $O(n^2k^4)$。

```cpp
// qwq
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N=1009,mo=1e9+7;
int n,K,f[N][N*5][6],t[N*5][6],sz[N];
vector<int>e[N];
inline int suf(int x,int y){
    return x+=y,x>=mo?x-mo:x;
}
inline void dp(int u,int fa){
    sz[u]=1;for(int i=1;i<=K;i++)f[u][0][i]=1;
    for(int v:e[u])if(v^fa){
        dp(v,u);
        memset(t,0,sizeof t);
        for(int i=0;i<=sz[u]*K;i++)for(int j=0;j<=K;j++)if(f[u][i][j])
            for(int x=0;x<=sz[v]*K;x++)for(int y=0;y<=K;y++)if(f[v][x][y])
                t[i+x+y][max(i+j+x,i+x+y)-(i+x+y)]=
                    suf(t[i+x+y][max(i+j+x,i+x+y)-(i+x+y)],(ll)f[u][i][j]*f[v][x][y]%mo);
        memcpy(f[u],t,sizeof f[u]),sz[u]+=sz[v];
    }
}
int main(){
    cin>>n>>K;
    for(int i=1,x,y;i<n;i++)
        cin>>x>>y,e[x].push_back(y),
        e[y].push_back(x);
    dp(1,0);
    for(int i=1;i<=n*K;i++){
        int ans=0;
        for(int d=0;d<=min(i,K);d++)
            ans=suf(ans,f[1][i-d][d]);
        cout<<ans<<'\n';
    }
    return 0;
}
```



---

## 作者：Leasier (赞：0)

首先可以暴力枚举点权，然后树形 dp 求最大权独立集，但时间复杂度为 $O(n k^n)$，显然不能通过。

注意到最大权独立集 dp 的转移只依赖于当前点是否选择（即 $dp_{u, 0/1}$），且状态的值域 $nk = 5 \times 10^3$ 很小，考虑把这玩意压入状态，设 $dp_{u, i, j}$ 表示 $dp_{u, 0} = i, dp_{u, 1} = j$ 的方案数。

初值：$dp_{u, 0, i} = 1$，其中 $1 \leq i \leq k$。

转移：考虑在 $(u, i, j)$ 基础上加入一个子树 $(v, l, x)$，则 $dp_{u, i + \max(l, x), j + l} \leftarrow dp_{u, i + \max(l, x), j + l} + dp_{u, i, j} dp_{v, l, x}$。

答案：$ans_i = \displaystyle\sum_{\max(j, x) = i} dp_{1, j, x}$。

但此时状态都有 $O(n^3 k^2)$ 量级了，显然不能通过。

注意到我们在转移时并不关心 $j$ 的值，而只关心 $\max(i, j)$ 的值，考虑把 $j$ 换成 $\max(i, j)$ 放进状态。

此时注意到 $\max(i, j) \in [i, i + k]$（因为把 $j$ 中的 $u$ 点扔掉后方案一定合法），则我们转而记录 $dp_{u, i, \Delta}$ 表示 $\max(i, j) - i = \Delta$ 的方案数，转移是类似的。此时状态减少到了 $O(n^2 k^2)$ 量级。

树上背包即可。时间复杂度为 $O(n^2 k^4)$，空状态剪枝后跑得飞快。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

typedef struct {
	int nxt;
	int end;
} Edge;

const int mod = 1e9 + 7;
int cnt = 0;
int head[1007], size[1007];
ll dp[1007][5007][7], temp[5007][7], ans[5007];
Edge edge[2007];

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

inline int max(int a, int b){
	return a > b ? a : b;
}

void dfs(int u, int father, int k){
	size[u] = 1;
	for (int i = 1; i <= k; i++){
		dp[u][0][i] = 1;
	}
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != father){
			int up1 = size[u] * k, up2, up3;
			dfs(x, u, k);
			up2 = size[x] * k;
			size[u] += size[x];
			up3 = size[u] * k;
			for (int j = 0; j <= up1; j++){
				for (int y = 0; y <= k; y++){
					if (dp[u][j][y] != 0){
						for (int z = 0; z <= up2; z++){
							for (int w = 0; w <= k; w++){
								if (dp[x][z][w] != 0){
									int p = j + z + w, q = max(y - w, 0);
									temp[p][q] = (temp[p][q] + dp[u][j][y] * dp[x][z][w] % mod) % mod;
								}
							}
						}
					}
				}
			}
			for (int j = 0; j <= up3; j++){
				for (int x = 0; x <= k; x++){
					dp[u][j][x] = temp[j][x];
					temp[j][x] = 0;
				}
			}
		}
	}
}

int main(){
	int n, k, m;
	scanf("%d %d", &n, &k);
	m = n * k;
	for (int i = 1; i < n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs(1, 0, k);
	for (int i = 1; i <= m; i++){
		for (int j = 0; j <= k; j++){
			int t = i + j;
			ans[t] = (ans[t] + dp[1][i][j]) % mod;
		}
	}
	for (int i = 1; i <= m; i++){
		printf("%lld\n", ans[i]);
	}
	return 0;
}
```

---

## 作者：St_john (赞：0)

# [ P8352 [SDOI/SXOI2022] 小 N 的独立集 ](https://www.luogu.com.cn/problem/P8352)

首先，最大权独立集是一个经典问题：  
设 $f_{i,0/1}$ 表示 $i$ 这个点不选还是选时的答案。  

转移就是 ：
$$f_{i,0}=\sum_{son}\max(f_{son,0},f_{son,1})$$
$$f_{i,1}=\sum_{son}f_{son,0}+val_i$$

复杂度 $O(nk^n)$。  

观察题目给的提示：答案在 $1\sim nk$ 之间，$nk\leqslant 5000$。  
考虑能否把 $f_{i,0/1}$ 设为状态？？  

考虑 dp套dp。  

设 $g_{i,v_0,v_1}$ 表示 $f_{i,0}=v_0,f_{i,1}=v_1$ 的方案数。  
转移就是
$$g'_{i,j+\max(x,y),k+x}=g_{i,j,k}\times \sum_{son} g_{son,x,y}$$

这也很显然。  
复杂度 $O(n^5k^4)$。  
（加上一些优化应该能拿到不少部分分，$O()$ 是上界）  


我们发现上面的瓶颈在于需要枚举很大的值域。  
考虑卡卡值域。  

观察发现 $f_{i,0}+k\geqslant f_{i,1}$。  
分类讨论一下：
1.  $f_{i,0}\geqslant f_{i,1}$ 没什么好说的，平凡。  
1.  $f_{i,1}>f_{i,0}$。  
$f_{i,1}-val_i\leqslant f_{i,0}$ 这条性质很显然，又因为 $val_i\leqslant k$ 所以说成立。  

综上所述，我们可以设 $g_{i,v_0,d}$ 表示 $f_{i,0}=v_0,f_{i,1}=v_0+d$ 的方案数。  
转移显然：
$$g'_{i,j+x+y,\max((j+k+x)-(j+x+y),0)}=g_{i,j,k}\times \sum_{son} g_{son,x,y}$$

因为当 $d\leqslant 0$ 时，$f_{i,1}=f_{i,0}+d$ 是没用的。  

所以最终复杂度为 $O(n^3k^4)$。  
当然这只是个上界。  
具体来讲就是 $O(\text{能过})$。  

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
#define  il inline
#define pc putchar
#define Re register int
#define _for(i,a,b) for(register int i=(a);i<=(b);++i)
#define __for(i,a,b) for(register int i=(a);i>=(b);--i)
il int re(){
    int x=0;
    char ch=getchar();
    bool f=0;
    while(ch<'0'||ch>'9')
        f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return f?-x:x;
}
void pr(int x){
    if(x<0) x=-x,pc('-');
    if(x>9) pr(x/10);
    pc(x%10|48);
}
const int A=1e3+10,B=6,C=A*5,D=A<<1,mod=1e9+7;

il int max(int a,int b){
	return a>b?a:b;
}
int n,K;
int head[A],cnt;
struct Edge{
	int t,n;
}edge[D];
il void add_edge(int u,int v){
	edge[++cnt]={v,head[u]};head[u]=cnt;
	edge[++cnt]={u,head[v]};head[v]=cnt;
}
int siz[A];
int g[C][B];
int f[A][C][B];
il void calc1(int &x,int y){//取模优化
	x=(x+y>=mod?x+y-mod:x+y);
}

void dfs(int x,int fa){
	siz[x]=K;//统计值域 
	_for(i,1,K) f[x][0][i]=1;//初始化f_{x,1} 
	for(Re i=head[x],y;i;i=edge[i].n){
		y=edge[i].t;
		
		if(y!=fa){
			dfs(y,x);
			memset(g,0,sizeof(g));
			_for(i,0,siz[x])
				_for(j,0,K)
					if(f[x][i][j])
					_for(k,0,siz[y])
						_for(l,0,K)
							if(f[y][k][l])
								calc1(g[i+k+l][max(j-l,0)],(ll)f[x][i][j]*f[y][k][l]%mod);
			siz[x]+=siz[y];
			memcpy(f[x],g,sizeof(g));
		}
		
	}
}
signed main(){
	n=re(),K=re();
	_for(i,2,n)
		add_edge(re(),re());
	dfs(1,0);
	int ii=K*n;
	_for(i,1,ii){
		int ans=0;
		for(Re j=0;j<=i&&j<=K;++j)
			calc1(ans,f[1][i-j][j]);//满足i-j+j=i即可 
		pr(ans),pc('\n');
	}
    return 0;
}
```


---

## 作者：ListenSnow (赞：0)

[原题链接](https://www.luogu.com.cn/problem/P8352 "原题链接")

## 题意

给定一棵 $n$ 个点的树，每个点的权值在 $[1,k]$ 之间，对于 $\forall i \in [1,kn]$，求出有多少种权值分配方案，使得树的最大权独立集大小为 $i$。

$n \leq 1000,k \leq 5$。

## 思路

不难想到一种很暴力的方式，即枚举每个点的权值，然后树形 dp 求出最大权独立集。即，设 $f_{u,0/1}$ 表示在子树 $u$ 中不选/选 $u$ 时的最大权独立集。时间复杂度为 $O(nk^n)$。

在本题中，注意到点权的范围实际上很小，一种理想的状态是令 $g_{u,v}$ 为 $u$ 子树内最大权独立集大小为 $v$ 的方案数。而在转移中，由于需要对当前点 $u$ 是否被选取在独立集中分类讨论，那么可以进一步想到令 $g_{u,v_0,v_1}$ 表示在 $u$ 子树中不选择 $u$ 节点时最大权独立集大小为 $v_0$，选择 $u$ 节点时最大权独立集大小为 $v_1$ 的方案数。枚举当前儿子 $v$ 的时候，令 $p$ 和 $q$ 分别表示不选/选 $v$ 节点的最大权独立集大小，可以得到状态转移方程：

$$g_{u,v0+\max(p,q),v1+p}=\sum_{v \in son_u} g_{u,v0,v1} \times g_{v,p,q}$$

不难发现这里的 $v_0$ 和 $v_1$ 实质上就是之前提到的 $f_{u,0}$ 和 $f_{u,1}$。这种内层 dp 结果作为外层 dp 的状态的小 trick 就被称为 dp 套 dp。这样做的时间复杂度为 $O(n^3k^4)$。还需要考虑进一步优化。

注意到 $f_{u,0}$ 和 $f_{u,1}$ 的差值实际上不会很大，考虑把这个差值的范围确定下来。可以重新定义 $f_{v,0}$ 和 $f_{v,1}$ 的为是否强制**不选**择 $u$ 节点时的最大权独立集大小，那么可以得到不等式 $0 \leq f_{u,0}-f_{u,1} \leq a_u \leq k$。于是就可以重新定义 $g_{u,v_1,d}$ 表示 $f_{u,0}=v_1+d,f_{u,1}=v_1$ 时的方案数。

由于状态重新定义，转移方程也发生了一定的变化。在枚举 $f_{v,v_1,d}$ 时，同样令 $p=v_1,q=d$，那么可以得到 $v_1'=v_1+\max(p,p+q)=v_1+p+q$，$v_0'=\max(v_1+p+q,v_1+d+p)$，于是就有 $d'=v_0'-v_1'=\max(v_1+p+q,v_1+d+p)-v_1+p+q$，得到转移方程：

$$g_{u,v_1+p+q,d'}=\sum_{v \in son_u} g_{u,v1,d} \times g_{v,p,q}$$

此时的时间复杂度就降低到了 $O(n^2k^4)$，可以通过本题。

## code

```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1010,M=N*5,mod=1e9+7;
int tmp[M][6],f[N][M][6],siz[N],n,k,h[N],idx;
struct edge{int v,nex;}e[M];
void add(int u,int v){e[++idx]=edge{v,h[u]};h[u]=idx;}
void Add(int &a,int b){a+=b;if(a>=mod) a-=mod;}
void dfs(int u,int fa)
{
	siz[u]=1;
	for(int i=1;i<=k;i++) f[u][0][i]=1;
	for(int i=h[u];i;i=e[i].nex)
	{
		int v=e[i].v;if(v==fa) continue;dfs(v,u);memset(tmp,0,sizeof(tmp));
		for(int i=0;i<=k*siz[u];i++)
		    for(int j=0;j<=k;j++)
		    {
		    	if(!f[u][i][j]) continue;
		    	for(int p=0;p<=k*siz[v];p++)
		    	    for(int q=0;q<=k;q++)
		    	        Add(tmp[i+p+q][max(i+j+p,i+p+q)-(i+p+q)],1ll*f[u][i][j]*f[v][p][q]%mod);    
			}
		memcpy(f[u],tmp,sizeof(tmp));
		siz[u]+=siz[v];
	}
}
int main()
{
	scanf("%d%d",&n,&k);for(int u,v,i=1;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);dfs(1,0);
    for(int i=1;i<=k*n;i++)
	{
        int ans=0;
        for(int d=0;d<=min(i,k);d++) Add(ans,f[1][i-d][d]);
        printf("%d\n",ans);
    }
	return 0;
}
```

---

