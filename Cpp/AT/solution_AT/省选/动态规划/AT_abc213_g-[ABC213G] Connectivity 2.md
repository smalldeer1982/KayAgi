# [ABC213G] Connectivity 2

## 题目描述

#### 题目大意

给一张 $N$ 个点 $M$ 条边的简单无向图 $G$。考虑删去 $0$ 条及以上的边构成一张新图。对于每个点 $k(2\leq k\leq N)$，求有多少张新图满足点 $k$ 与点 $1$ 连通（模 $998244353$）。

## 样例 #1

### 输入

```
3 2
1 2
2 3```

### 输出

```
2
1```

## 样例 #2

### 输入

```
5 6
1 2
1 4
1 5
2 3
2 5
3 4```

### 输出

```
43
31
37
41```

## 样例 #3

### 输入

```
2 0```

### 输出

```
0```

# 题解

## 作者：fjy666 (赞：15)

一道玄妙的状态压缩 dp。  
设 $F=\{1,2,3,\cdots,n\}$， $S$ 为 $F$ 的一个子集。  
设 $g(S)$ 为 $G$ 的**子图**中点集为 $S$ 的图的个数，$f(S)$ 为 $G$ 的**联通子图**中点集为 $S$ 的图的个数。  
则我们所求的答案 $\rm ans_{2,3,\cdots,n}$ 可以表示为
$$\mathrm{ans_k}=\sum_{\{1,k\}\subset S\subset F}f(S)\times g(\mathrm{C}_FS)$$

（$\mathrm{C}_FS$ 代表以 $F$ 为全集求 $S$ 的补集）

这可以在 $\Theta(n2^n)$ 内完成。
- 计算 $g(S)$  
求出满足两个端点 $\in S$ 的边的个数 $cnt$，则 $g(S)=2^{cnt}$，可以在 $\Theta(2^nm)$ 内完成、

- 计算 $f(S)$  
根据容斥原理，$f(S)=$ 所有点集为 $S$ 的子图个数 $-$ 所有点集为 $S$ 的不连通子图个数。  
前面那部分 $=g(S)$  
后面那部分的话……钦定一个点 $v\in S$，把不连通子图分成两部分：包含 $v$ 的连通块，不包含 $v$ 的其他部分。  
则可以列出式子 
$$f(S)=g(S)-\sum_{v\in T\subsetneqq S}f(T)\times g(\mathrm{C}_ST)$$  
由于枚举所有子集的子集是 $\Theta(3^n)$ 的，所以这部分也是 $\Theta(3^n)$ 的。  
总时间复杂度为 $\Theta(3^n+n2^n+m2^n)$。

---

## 作者：Tsawke (赞：7)

# [[ABC213G] Connectivity 2](https://www.luogu.com.cn/problem/AT_abc213_g) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC213G)

## 题面

给定 $ n $ 个点 $ m $ 条边的简单无向图，考虑删去其中大于 $ 0 $ 条边构成新图，显然共有 $ 2^m $ 张新图。求对于每个点 $ k \in [2, n] $ 有多少张新图满足 $ k $ 点和 $ 1 $ 点连通。对 $ 998244353 $ 取模。

## Solution

对于 FZT（子集计数）的更具体说明可以参考 [FZT - 子集计数学习笔记](http://blog.tsawke.com?t=FZT)。

考虑 FZT，显然令 $ S $ 为二进制状态，表示某个点是否钦定。

令 $ F(S) $ 表示点集为 $ S $ 中的点互相连通的方案数。令 $ G(S) $ 表示点集为 $ S $ 可以产生的子图数量。

不难想到，若 $ cnt_S $ 表示点集为 $ S $ 中的点之间有多少条边，则 $ G(S) = 2^{cnt_S} $，不难想到这个的预处理复杂度为 $ O(m2^n) $，可以接受。

考虑如何转移 $ F $，不难想到（错误的）转移为：
$$
F(S) = G(S) - \sum_{T \subsetneq S}F(T) \times G(S \oplus T)
$$
可以尝试理解一下这个转移，我们要保证 $ S $ 连通，那么可以考虑在所有的方案数 $ G(S) $ 中枚举减去不合法的，为了不漏，不难想到枚举每个 $ S $ 的真子集 $ T $，然后让 $ T $ 和 $ S $ 中除去 $ T $ 以外的部分之间不连通。为了不重，所以我们要钦定 $ T $ 连通，此时 $ S $ 里 $ T $ 的补集，也就是 $ S \oplus T $，其中的边是否存在都可以，也就是 $ G(S \oplus T) $。将两者乘起来即可，此时即保证了不漏。枚举子集及其子集的复杂度和一般枚举子集复杂度相同，为 $ O(3^n) $，可以接受。

然后发现，**这个东西是假的**。不难想到，假设我们考虑一个将 $ S $ 分为几个连通块的方案，如果按照我们刚才的方案的话，钦定一个连通块之后，枚举剩下的所有方案时一定会包含了钦定其它连通块，会重复。考虑如何去重，不难想到我们只需要钦定一个点在枚举子集的时候必须被选中，这样对于多个连通块的情况就等于是我们钦定只选择该点所在区间为必须连通的，这样即可保证不重。当然这个点的选择是任意的，可以直接钦定为 $ 1 $。

于是转移优化为：
$$
F(S) = G(S) - \sum_{1 \in T \subsetneq S}F(T) \times G(S \oplus T)
$$
然后因为我们要保证 $ 1 $ 一定存在，所以可以不枚举第一位，复杂度可以少一个 $ 3 $。也可以正常枚举，然后计算答案的时候去掉所有 $ 1 $ 对应的状态为 $ 0 $ 的即可。这样的复杂度也是 $ 1e8 $ 级别，可以接受，且更易于实现。

同时不难对于初始值，存在 $ F(0) = G(0) = 1 $，也就是所有点都不选的时候认为所有边都不选也是一种方案。

然后考虑答案，不难想到，对于点 $ i $ 的答案 $ ans_i $，令 $ S = 2^n - 1 $，也就是全集，显然有：
$$
ans_i = \sum_{T \subseteq S}F(T) \times G(S \oplus T) \times [T \land 2^{i - 1}] \times [T \land 1]
$$
然后这个求解的复杂度为 $ O(n2^n) $。

最终复杂度为 $ O((m + n)2^n + 3^n) $，卡的比较满，但是有三秒，显然可以通过。

Tips：对于枚举子集的过程应该不用多说，令 $ Smx $ 为全集，一般为 $ Smx = 2^{n} - 1 $，然后枚举的过程就是 `for(int S = Smx; S; S = (S - 1) & Smx)`，具体证明这里不再赘述，可以网上直接搜一下。

Tips：然后关于前面说的枚举子集和子集的子集的复杂度，这个东西用组合数写一下不难证明，总之枚举 $ 2^n $ 状态的子集是 $ O(3^n) $ 的，枚举子集套娃的复杂度可以证明枚举 $ k $ 次子集的复杂度是 $ (k + 1)^n $，本题即为 $ O(3^n) $。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MOD (ll)(998244353ll)
#define MAX_STATUS (150000)
#define EXIST(x) (S & (1 << ((x) - 1)))

template < typename T = int >
inline T read(void);

int N, M;
struct Edge{
    Edge* nxt;
    int to;
    OPNEW;
}ed[2100];
ROPNEW(ed);
Edge* head[20];
ll F[MAX_STATUS], G[MAX_STATUS];
ll pow2[500];
ll ans[20];

int main(){
    pow2[0] = 1;
    for(int i = 1; i <= 300; ++i)pow2[i] = pow2[i - 1] * 2 % MOD;
    N = read(), M = read();
    const int Smx = (1 << N) - 1;
    for(int i = 1; i <= M; ++i){
        int s = read(), t = read();
        head[s] = new Edge{head[s], t};
    }F[0] = G[0] = 1;
    for(int S = Smx; S; S = (S - 1) & Smx){
        int cnt(0);
        for(int p = 1; p <= N; ++p)
            if(EXIST(p))
                for(auto i = head[p]; i; i = i->nxt)
                    if(EXIST(SON))++cnt;
        G[S] = pow2[cnt];
    }
    for(int S = 1; S <= Smx; ++S){
        for(int T = (S - 1) & S; T; T = (T - 1) & S)
            if(T & 1)
                (F[S] += F[T] * G[S ^ T] % MOD) %= MOD;
        F[S] = (G[S] - F[S] + MOD) % MOD;
    }
    for(int i = 2; i <= N; ++i)
        for(int S = Smx; S; S = (S - 1) & Smx)
            if(EXIST(i) && EXIST(1))(ans[i] += F[S] * G[S ^ Smx] % MOD) %= MOD;
    for(int i = 2; i <= N; ++i)printf("%lld\n", ans[i]);
    // for(int S = Smx; S; S = (S - 1) & Smx)
    //     cout << "G[" << bitset < 6 >(S) << "] = " << G[S] << ", F = " << F[S] << endl;
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_05 初稿

---

## 作者：MSqwq (赞：5)

模拟赛时非常接近正解的一道题了，没有调出来，有点可惜。  
首先就是状压，很显然只能状压点，然后选点考虑连通块。  
那么没选到的点肯定随便连，比如没有选到的点之间的边有 $x$ 条，那么最后肯定要乘个 $2^x$，乘法原理嘛。  
然你你可以预处理 $2^n$ 个状态的时候的连边情况，这个很小，直接暴力枚举就行，记作 $g_x$，$x$ 是一个二进制状态，我本人喜欢从左往右标号，可能不太符合很多人习惯吧，但是不重要，$1$ 表示在联通块里面，$0$ 表示不在，然后你暴力枚举任意两个 $1$ 去看有无边，然后加起来算就行。  
设 $f_s$ 表示让 $s$ 状是个连通块，有多少个图。分为两类边啊，一类是 $s$ 内的边，记作 $a$，一类是 $s$ 与 $s$ 补集之间的边，就是 $s$ 连出去的边，记作 $b$。  
考虑转移，就是有一个很深刻的概念就是删边比加边难，一般逆着处理，那么就是一个很典型的容斥了。那么 $s$ 外的我们前面已经说过了，就不多赘述，考虑 $s$ 内的，要形成连通块，那么就要联通，一共有 $g_s$ 种连边状态（不一定联通，只是所有的状态），然后就减去不连通的状态嘛，在 $s$ 内存在一个独立的子图，那么就一定不连通，方案数就是 $f_t\times g_{s/t}$，$s/t$ 就是 $t$ 在 $s$ 内的补图。然后就做完了啊，最后算一下每个状态对于每个点的贡献，就完事了。  
顺便提一下，因为问的是与 $1$ 的连通性，而且要考虑不重复算，所以规定 $s$ 和 $t$ 都必须有 $1$。当然 $t$ 规定其他的点也无所谓，但是不需要有。还有 $s$ 不能等于 $t$。    
顺手一下方程式吧 $f_s=\sum\limits_{1\in t\in s}f_t\times g_{s/t}$。  
然后放一下代码，因为我的状压可能异于常人，所以谨慎观看吧。。。  
```
#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
#define INF 0x3f3f3f3f
using namespace std;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}
const int N=20,M=2e5+10;
int e[N][N];
ll g[M],f[M],fac[M];
int main()
{
	int n=read(),m=read();
	fac[0]=1;for(int i=1;i<=m;i++)fac[i]=fac[i-1]*2%mod;
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		e[x][y]=1,e[y][x]=1;
	}
	for(int i=0;i<=(1<<n)-1;i++)
	{
		vector<int>v;int x=i,now=n;
		while(x)
		{
			if(x&1)v.push_back(now);
			x>>=1,now--;
		}
		for(int p=0;p<v.size();p++)
			for(int q=p+1;q<v.size();q++)g[i]+=e[v[p]][v[q]];
		g[i]=fac[g[i]];
	}
	for(int i=1<<(n-1);i<=(1<<n)-1;i++)
	{
		f[i]=g[i];
		for(int j=i;j>=(1<<(n-1));j=i&(j-1))
		{
			if(j==i)continue;
			if((j&(1<<(n-1)))==0)continue;
			f[i]=(f[i]-f[j]*g[i^j]%mod+mod)%mod;
		}
	}
	for(int i=2;i<=n;i++)
	{
		ans=0;
		for(int j=1<<(n-1);j<=(1<<n)-1;j++)
			if(j&(1<<(n-i)))ans=(ans+f[j]*g[((1<<n)-1)^j]%mod)%mod;
		cout<<ans<<endl;
	}
	return 0;
}

```


---

## 作者：daniEl_lElE (赞：3)

比较经典的好题。

## 思路

首先先转化问题，先考虑计算出一个子图连通的方案数。

比较难算，我们考虑使用容斥的方法计算。先计算出对于子集 $i$，$f_i$ 表示只有 $i$ 子集内有边的方案数，也就是 $2$ 的两端都在该子集内的边数次方。

考虑容斥，记一个 $ans_i$ 数组（即刚才所述的答案）。我们考虑目前已经计算出对于 $i$ 的所有子集 $j$ 的 $ans_j$，我们尝试去计算 $ans_i$。首先采用添加一个维度的方式计算（也就是对于 $1\sim n$ 分别计算子集所有元素在 $1\sim i$ 的答案），钦定他必须包含 $i$，从原来的 $ans_x$ 中扣减所有子集 $j$ 的 $ans_{j|(1<<(i-1)}\times dp_{x\oplus j}$。

在此之后，我们得到了 $ans$ 数组。接下来，只需要针对每一个包含 $1$ 的子集 $i$，计算出符合要求的任意选边数（即两个端点均不被 $i$ 包含的边），在子集内点上计算贡献即可。

总复杂度是 $O(3^n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int unsigned long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=998244353;
int dp[1000005];
int dp2[1000005];
vector<int> vc[18];
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
int ans[18];
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	int n,m;
	cin>>n>>m;
	int u[m+1],v[m+1];
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
		vc[max(u[i],v[i])].push_back(min(u[i],v[i]));
	}
	for(int i=0;i<(1<<n);i++){
		int cnt=0;
		for(int j=1;j<=m;j++){
			cnt+=(((i>>(u[j]-1))&1)&((i>>(v[j]-1))&1));
		}
		dp[i]=qp(2,cnt);
//		cout<<dp[i]<<endl;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<(1<<(i-1));j++){
			dp2[j|(1<<(i-1))]=dp[j|(1<<i-1)];
			for(int k=j;k;k=(k-1)&j){
				(dp2[j|(1<<(i-1))]+=mod-(dp2[(k^j)|(1<<(i-1))]*dp[k]%mod))%=mod; 
			}
		}
	}
//	for(int i=0;i<(1<<n);i++){
//		cout<<dp2[i]<<endl;
//	}
	for(int i=0;i<(1<<n);i++){
		if(!(i&1)) continue;
		int cntm=0;
		for(int j=1;j<=m;j++){
			if(((i>>(u[j]-1))&1)|((i>>(v[j]-1))&1)) cntm++;
		}
		cntm=m-cntm;
		for(int j=1;j<=n;j++){
			if((i>>(j-1))&1){
				(ans[j]+=qp(2,cntm)*dp2[i])%=mod;
			}
		}
	}
	for(int i=2;i<=n;i++){
		cout<<ans[i]<<endl;
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

老年人复健第一题，先挂[题链](https://www.luogu.com.cn/problem/AT_abc213_g)。

[更好的阅读体验QwQ](https://www.cnblogs.com/MinCat/articles/17459582.html)

### 题目大意：

给你一个无向图，枚举每个点求出其有多少种删边的方案满足 $1$ 能到 $k$。

设 $1$ 要到达点 $k$ 所经过的点集为 $s$。状态设为 $f_{s}$ 表示从 $1$ 走过 $s$ 这个点集的方案数。

边界：$f_0 \leftarrow 1$。

记 $get_s$ 为在忽略限制条件时保留边的方案数，有 $get_s = 2^s$，预处理即可。

设不合法方案为 $s$ 的一个子集 $u$。则 $s \setminus u$ 中的边任意，贡献 $get_{s-u}$。但是 $s \setminus u$ 与点集 $u$ 之间却无边相连，贡献 $f_u$。

上容斥！转移方程如下：

$f_s = get_s - \sum_{u \in s} f_u \times get_{s-u}$。

怎么枚举一个集合的子集？手摸试试看吧！

$s$：``1101``

$u_1$：``1100``

$u_2$：``1001``

$u_3$：``1000``

$u_4$：``0101``

$u_5$：``0100``

$u_6$：``0001``

诶！我们发现 $u$ 可以用 ``for(int u = s - lowbit(s); u; u = (u-1) & s)`` 的方式枚举，具体含义就是在倒着枚举的时候对 $s$ 做与运算保证是它的子集。

统计答案就枚举 $s$ 保留的点的那一块的贡献乘上被割掉的边。 

还有一件事！开 ``long long``，取模可悠着点。

### Code：

```
/*[ABC213G] Connectivity 2*/
//拜托了给一个赞吧。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int M = 21;
const int mod = 998244353;
int n,m;
int Graph[M][M];
int Get[1 << M];
int f[1 << M];
int ans[M];
int lim;

int lowbit(int s) {
	return s & -s;
}//lowbit可爱

void read() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i = 1,x,y; i<=m; ++i) {
		cin>>x>>y;
		Graph[x - 1][y - 1] = 1;
		Graph[y - 1][x - 1] = 1;
	}//这里为了方便dp把点的编号从0开始qwq
}

void init() {
	lim = 1<<n;
	for(int s = 0; s <= lim - 1; ++s) {
		Get[s] = 1;
		for(int i = 0; i<n; ++i) {
			for(int j = i + 1; j<n; ++j) {
				if(
				    (s & (1 << i)) &&	//i在点集
				    (s & (1 << j)) &&	//j在点集
				    (Graph[i][j])		//有连边
				)
					Get[s] = (Get[s] << 1) % mod;

			}
		}
	}
}
//qwq
void DP() {
	f[0] = 1;
	for(int s = 1; s <= lim - 1; ++s) {
		if(s & 1) {
			f[s] = Get[s];
		}
		for(int u = s - lowbit(s); u; u = (u-1) & s) {
			f[s] = (f[s] - f[u] * Get[s - u]) % mod;
		}
	}
	for(int s = 0; s <=  lim - 1; ++s) {
		for(int i = 1; i<= n - 1; ++i) {
			if(s & (1 << i)) {
				ans[i] = (ans[i] + f[s] * Get[(1 << n) - 1 - s]) % mod;
				// s 保留的乘上被割掉的边。 
			}
		}
	}
}

void print() {
	for(int i = 1; i<= n - 1; i++) {
		cout<<(ans[i] + mod) % mod<<'\n';
	}
}

void solve() {
	read();
	init();
	DP();
	print();
}



signed main() {
	solve();
	return 0;
}
```

---

