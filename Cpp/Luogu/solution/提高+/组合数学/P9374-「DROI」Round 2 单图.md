# 「DROI」Round 2 单图

## 题目背景

与其编写苍白无力的背景，不如出更有质量的题。

## 题目描述

我们称[简单有向图](https://www.luogu.com.cn/paste/4oz6fep2) $G,H$ **本质相同**，当且仅当：

- 对于任意点对 $(u,v)$，若在图 $G$ 中从 $u$ 出发能走到 $v$，则在图 $H$ 中从 $u$ 出发能走到 $v$。反之若在图 $H$ 中从 $u$ 出发能走到 $v$，则在图 $G$ 中从 $u$ 出发也能走到 $v$。

若对于简单有向图 $G$，不存在其他简单有向图 $H$ 与其本质相同，则我们称图 $G$ 为 **单图**。

$T$ 次询问，每次询问给定一个正整数 $n$，请你回答 $n$ 个点的**有标号**单图数。

## 说明/提示

#### 数据范围

**「本题采用捆绑测试」** 

- $\operatorname{Subtask} 1(30\%)$：$T = 1$，$n \leq 5$。

- $\operatorname{Subtask} 2(50\%)$：$T \leq 10$。

- $\operatorname{Subtask} 3(20\%)$：无特殊限制。

对于 $100\%$ 的数据满足：$1 \leq T,n \leq 1000$，$1\leq mod \leq 10^9$。


#### 说明提示

这里给出一些例子来帮助理解单图的含义：

------------

![](https://cdn.luogu.com.cn/upload/image_hosting/kykl8fg8.png)[](https://www.luogu.com.cn/paste/0tbbkesd)

这是一张单图，可以证明不存在其他图与其本质相同。

------------

![](https://cdn.luogu.com.cn/upload/image_hosting/5appj8pr.png)

这不是一张单图，因为我们可以添加边 $(5,2)$ 构造出与其本质相同的图。

------------

![](https://cdn.luogu.com.cn/upload/image_hosting/wtsep329.png)

这不是一张单图，因为我们可以删去边 $(1,3)$ 构造出与其本质相同的图。



## 样例 #1

### 输入

```
5 998244353
1
3
5
12
888```

### 输出

```
1
16
986
328006912
535268381```

# 题解

## 作者：Demeanor_Roy (赞：9)

- 出题人题解。

------------

第一档考虑手玩或爆搜，接下来从第二档讲起。

考虑图 $G$ 上若存在三点 $x,y,z$，若满足 $x \rightarrow y$ 有边，且 $y \rightarrow z$ 有边，那么我们只需改变 $x \rightarrow z$ 的有无边情况，即有边就删无边就加，就能构造出与 $G$ 本质相同的图。那么我们似乎可以得出，图 $G$ 是单图当且仅当其所有点入度为 $0$ 或出度为 $0$。

可这是有问题的，因为存在一个反例，即两点环。不难发现若图中一两点环与外界不联通，显然也无法据此构造出与其本质相同的图。所以需分两种情况讨论。

思考如何计数，对于一个 $n$ 个点的图。令 $f(x)$ 表示 $x$ 个点的单图数，$g(x)$ 表示 $x$ 个点不考虑两点环的单图数，$t(x)$ 表示 $x$ 个点只考虑两点环的单图数。显然有：

$$f(x)=\sum_{2i \leq x}{x \choose 2i}t(2i)g(x-2i)$$

先思考 $t(2x)$ 的求解。因为 $t(2x)$ 表示的是 $2x$ 个点划分成 $x$ 对两点环的方案数，我们不妨考虑一对一对选取，那么方案数就是 $\prod\limits_{i=1}^x\dbinom{2x-2(i-1)}{2}$。但这样做会算重，因为其实是与顺序无关的，所以再除以一个 $x!$ 即可。化简后可得 $t(x)=\prod\limits_{2i \leq n}(2i+1)$。

那么 $g(x)$ 怎么求呢？由于所有点要么无入度，要么无出度。考虑这样一种刻画：我们将所有点分为有入度和无入度两类，若前者有 $y$ 个点，则对于前者可能有 $x-y$ 条边，其中一条边都没有是非法的，故有 $(2^{x-y}-1)$ 种方案，将所有点的方案合并，故此时方案数为 $(2^{(x-y)}-1)^y$。所以可得：

$$g(x)=\sum_{i=0}^{x}{x \choose i}{(2^{x-i}-1)^i}$$

故暴力求解可做到 $O(Tn^2 \log n)$。预处理 $g$ 即可做到 $O(n^2 \log n + nT)$。

显然可以优化到 $O(n^2 \log n + T \log n)$。~~不过并不美丽也无甚价值~~ 。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N=1010;
 
int T,n,mod,fct[N],ans[N],C[N][N];
inline int pwr(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1) res=(LL)res*x%mod;
		x=(LL)x*x%mod;y>>=1;
	}
	return res;
}
inline void init()
{
	ans[0]=C[0][0]=C[1][0]=C[2][0]=fct[1]=1;
	for(int i=3;i<N;i++) C[i][0]=1,fct[i]=(i&1?(LL)fct[i-2]*i%mod:0);
	for(int i=1;i<N;i++)
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	for(int i=1;i<N;i++)
		for(int j=0;j<i;j++)
			ans[i]=(ans[i]+(LL)C[i][j]*pwr(pwr(2,i-j)-1,j)%mod)%mod;				
}

inline void solve()
{
	scanf("%d",&n);
	int res=ans[n];
	for(int i=2;i<=n;i+=2) res=(res+(LL)C[n][i]*fct[i-1]%mod*ans[n-i]%mod)%mod;
	printf("%d\n",res);
}
int main()
{
	scanf("%d%d",&T,&mod);
	init();
	while(T--) solve();
	return 0;
}
```


---

## 作者：0000pnc (赞：7)

题意：求点数为 $n$ 的简单有向图数量，使得没有另一个简单有向图，其可达性矩阵和原图相同。

我们考虑图里出现以下结构时会发生什么。

![](https://cdn.luogu.com.cn/upload/image_hosting/dduf3qxf.png)

显然，如果点 $1$ 没有连向点 $3$ 的边，那么连接后其可达性不变。同样地，如果这条边存在，那么把它删去依然没有影响。 

![](https://cdn.luogu.com.cn/upload/image_hosting/30x0quat.png)

所以，一个点不能既有出度又有入度。但是有一个特例：

![](https://cdn.luogu.com.cn/upload/image_hosting/oon1vqj2.png)  

这种情况下，虽然点 $1$ 和 $2$ 都有出度和入度，但依然符合要求。但是这要求点 $1$ 和 $2$ 必须是孤立的（即这两个点不能再有连边）。  

想清楚了，我们就可以开始推式子了。不考虑两点环的特殊情况，那么就可以把所有点根据出度的有无分成两个集合，即：有出度的点，设为点集 $\text{A}$，和没有出度的点，设为点集 $\text{B}$。显然，所有边都只能是从 $\text{A}$ 中的点连向 $\text{B}$ 中的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/e6nfai3o.png)  
这个图中，点 $1,2,3$ 有出度，$4,5,6,7$ 没有出度。

如果设 $|\text{A}|=a$，$|\text{B}|=b$，那么每个 $\text{A}$ 中的点都有 $2^{b}-1$ 种方法向 $\text{B}$ 中的点连边（减掉 $1$ 是因为不能不连）。$\text{A}$ 中有 $a$ 个点，那么方案数就是 $(2^{b}-1)^{a}$。

接下来计算总的方案数。在 $n$ 个点中，可以选择 $0,1,2,\cdots n-1$ 个有出度的点（不能全部都有出度）。对每种点数分别计算即可。这种情况的答案是

$$
f(n)=\sum_{i=0}^{n-1}\displaystyle \large(\small C_{n}^{i} \cdot (2^{n-i}-1)^{i}\large)
$$
。

对于两点环的情况，可以考虑在上述情况的基础上加几对两点环。从 $n$ 个点中划分出若干对两点环后，剩下的点依然符合上述条件即可。自然，最多可以选取 $\lfloor \dfrac{n}{2} \rfloor$ 对两点环。

![](https://cdn.luogu.com.cn/upload/image_hosting/7hiq8cf9.png)

设两点环的个数为 $k$。先选出所有 $2k$ 个在两点环里的点，再进行配对即可。最小标号的有 $2k-1$ 个能配对的点，剔除这对后最小标号的有 $2k-3$ 个能配对的点，以此类推，最后方案个数就是 $(2k-1)(2k-3)\cdots \kern{2pt}\cdot 3\cdot 1$。

所以，还是对于每种可能的两点环个数进行讨论就行。这种情况的方案数为

$$
\sum_{i=1}^{\lfloor \frac{n}{2} \rfloor}\large(\small\displaystyle C_{n}^{2i} \cdot \prod_{j=1}^{i}(2j-1)\large\cdot \small f(n-2i)\large)
$$
。

整合起来，得到

$$
\text{ans}_n=\sum_{i=0}^{\lfloor \frac{n}{2} \rfloor}\Large(\small \displaystyle C_{n}^{2i}\large\cdot \small\large(\small\prod_{j=1}^{i}(2j-1)\large)\cdot (\small\sum_{j=0}^{n-2i-1}\large(\small\displaystyle C_{n-2i}^{j} \large\cdot\small(2^{n-2i-j}-1)^j\large))\Large)
$$
。（这是通项式）

用倒数第二个柿子 $O(n^2)$ 递推预处理即可。注意要预处理组合数。

```cpp
#include <bits/stdc++.h>
using namespace std;

long long T, n, mod;
long long ans;

long long C[1005][1005], f[1005], ff[1005];

long long qpow(long long x, long long cnt) {
	long long ret = 1, bas = x, c = cnt;
	while (c) {
		if (c & 1) ret = ret * bas % mod;
		bas = bas * bas % mod;
		c >>= 1;
	}
	return ret;
}

void init() {
	for (int i = 0; i <= 1000; i++) {
		C[i][0] = C[i][i] = 1;
	}
	for (int i = 2; i <= 1000; i++) {
		for (int j = 1; j < i; j++) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
		}
	}
	f[0] = 1;
	f[1] = 1, f[2] = 3;
	ff[1] = 1, ff[2] = 4;
	for (n = 3; n <= 1000; n++) {
		ans = 0;
		for (int i = 0; i < n; i++) {
			ans += qpow(qpow(2, n - i) - 1, i) * C[n][i] % mod;
			ans %= mod;
		}
		f[n] = ans;
		long long res = 1, cur = 1;
		for (int i = 1; i <= n / 2; i++, cur += 2) {
			res *= cur; res %= mod;
			ans += C[n][(i << 1)] * res % mod * f[n - (i << 1)] % mod;
			ans %= mod;
		}
		ff[n] = ans;
	}
}

int main() {
	cin >> T >> mod; init();
	while (T--) {
		ans = 0;
		cin >> n;
		cout << ff[n] << endl;
	}
}
```

----

评价：一道思维难度稍大的计数题。

---

## 作者：听取MLE声一片 (赞：5)

简单计数题。

根据题目中的定义，发现一个图是单图当且仅当没有传递闭包。

没有传递闭包，很容易想到分成两类点，分别是只有出度的点和没有出度的点。

但是，二元环同样也不存在传递闭包却不在上述描述之中，所以要额外计算。

称二元环上的点为“双点”，考虑先处理出双点的方案数。

如果有 $n$ 个双点，那么第一个点有 $n-1$ 种选择，这样删去了两个点，第二个点有 $n-3$ 种选择，以此类推，那么方案数即为 $(n-1)!!$。

然后考虑非双点的情况。设非双点总数为 $n$，只有出度的点有 $x$ 个，没有出度的点有 $y$ 个，$x+y=n$。对于每个只有出度的点，都可以和若干没有出度的点连边，但必须连至少一条边，就是总个数减去不连边，即为 $2^y-1$。每个只有出度的点是独立的，所以方案数即为 $(2^y-1)^x$。因为是要 $n$ 个点选出 $x$ 个点为只有出度的点，要乘一个组合数 $\binom n x$。

$n$ 个非双点的答案即为枚举所有的 $x,y$，把上边的结果相加即可。

对于有 $n$ 个点的一般情况，枚举双点的个数 $x$，非双点个数即为 $n-x$。分别求出双点的 $x$ 和双点 $n-y$ 的方案数，因为要 $n$ 个选 $x$ 个所以还有组合数 $\binom n x$，把这三个乘起来就是 $x$ 对应的方案数，再把每个方案数加起来即可。

因为模数不一定是素数，所以处理组合数需要用到杨辉三角。

双点和非双点的答案可以先预处理出来，时间复杂度即为 $O(n^2\log \mathit{mod}+Tn)$。

如果预处理快速幂可以做到 $O(n^2+Tn)$，不过没有必要。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=1010;
int T,mod;
int n,a[N],C[N][N],f[N],g[N];
int ksm(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
signed main()
{
	//freopen("t1.in","r",stdin);
	//freopen("t1.out","w",stdout);
	T=read(),mod=read();
	C[0][0]=1;
	for(int i=1;i<N;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	f[0]=g[0]=1;
	for(int i=2;i<N;i+=2)
		g[i]=g[i-2]*(i-1)%mod;
	for(int i=1;i<N;i++){
		for(int j=0;j<=i;j++){
			int x=j,y=i-j;
			f[i]=(f[i]+C[i][j]*(ksm(ksm(2,y)-1,x)))%mod;
		}
	}
	while(T--){
		n=read();
		int res=0;
		for(int i=0;i<=n;i+=2){
			int x=n-i,y=i;
			res+=C[n][x]*f[x]%mod*g[y]%mod;
			res%=mod;
		}
		cout<<res<<'\n';
	}
	return 0;
}
```

---

## 作者：Leasier (赞：3)

首先考虑什么样的图可能成为“单图”，显然有：

- 若 $\exists x \to y \to z, x \neq z, \not\exists x \to z$，则加边 $x \to z$ 不影响结果。

进而可以得到：若 $G$ 为“单图”，则对于其每一个弱连通块必须满足如下两个条件之一：

- $|V| = |E| = 2$，即构成了一个大小为 $2$ 的环。
- 每个点要么入度为 $0$，要么出度为 $0$。

现在考虑计算 $n$ 对应的答案 $f_n$。枚举 $1$ 所在连通块大小 $i$，则：

- 第一种情况不难处理。
- 对于第二种情况，考虑钦定当前连通块中至少有 $j$ 个入度为 $0$ 的点，则我们为钦定点选择对面的点的非空子集作为其出边指向的点，方案数为 $C_i^j (2^{i - j} - 1)^j$。但这样算出的方案可能使得该图不弱连通，容斥即可。

时间复杂度为 $O(T + N^2)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int N = 1e3;
int c[N + 7][N + 7];
ll power[N + 7][N + 7], f[N + 7], g[N + 7], h[N + 7];

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(int mod){
	c[0][0] = 1;
	for (int i = 1; i <= N; i++){
		c[i][0] = 1;
		for (int j = 1; j <= i; j++){
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}
	power[0][1] = 1;
	for (int i = 1; i <= N; i++){
		power[i][1] = power[i - 1][1] * 2 % mod;
	}
	for (int i = 0; i <= N; i++){
		power[i][0] = 1;
		power[i][1] = ((power[i][1] - 1) % mod + mod) % mod;
		for (int j = 2; j <= N; j++){
			power[i][j] = power[i][j - 1] * power[i][1] % mod;
		}
	}
	f[0] = g[0] = h[0] = 1;
	for (int i = 1; i <= N; i++){
		f[i] = f[i - 1];
		for (int j = 0; j < i; j++){
			g[i] = (g[i] + c[i][j] * power[i - j][j] % mod) % mod;
		}
		h[i] = g[i];
		for (int j = 1; j < i; j++){
			h[i] = ((h[i] - c[i - 1][j - 1] * h[j] % mod * g[i - j] % mod) % mod + mod) % mod;
		}
		if (i >= 2){
			f[i] = (f[i] + 3 * (i - 1) % mod * f[i - 2] % mod) % mod;
			for (int j = 3; j <= i; j++){
				f[i] = (f[i] + f[i - j] * c[i - 1][j - 1] % mod * h[j] % mod) % mod;
			}
		}
	}
}

int main(){
	int t, mod;
	scanf("%d %d", &t, &mod);
	init(mod);
	for (int i = 1; i <= t; i++){
		int n;
		scanf("%d", &n);
		printf("%lld\n", f[n]);
	}
	return 0;
}
```

---

## 作者：August_Light (赞：2)

# P9374 「DROI」Round 2 单图 题解

[题目传送门](https://www.luogu.com.cn/problem/P9374)

## 题意简述

定义：

一张 $n$ 个节点的有向简单图如果满足不存在一张有向简单图使得这两张图的传递闭包相同，那么这张图被称为一张单图。

定义 $f(n)$ 为 $n$ 个节点的单图个数。

给定模数 $mod$，$T$ 次询问，给定 $n$，求 $f(n)$。

$1 \le T,n \le 10^3, 1 \le mod \le 10^9$。

## 解法

~~为什么 OEIS 上没有这个数列？~~

暴力：枚举邻接矩阵之后做 Floyd，时间复杂度 $\mathcal O(n^3 2^{n^2})$，虽然复杂度很糟糕，但是足以打表获得第一档部分分。

观察性质：

如果三个**不同**节点 $u,v,w$ 满足存在以下边 $u \to v, v \to w$，那么显然添加 $u \to w$ 这条边不会改变原图的传递闭包。

也就是说，不能有一个点又有出度又有入度，除非它和另一个点组成了一个两点环（两点环一定是孤立的，反证法易证）。

原图中的点被分为四类：只有入度的点（以下称为**入点**）、只有出度的点（以下称为**出点**）、入度出度都没有的点（以下称为**孤立点**）、在一个两点环内的点。

接下来看到 $n \le 10^3$，考虑复杂度可能比较高的组合计数。

### 组合做法

设 $g(n)$ 为 $n$ 个节点的不存在两点环的单图个数，$h(n)$ 为 $n$ 个节点的只存在两点环的单图个数。

既然 $n \le 10^3$，那就不用怕复杂度高了，直接枚举两点环的个数 $i$。

$$f(n) = \sum\limits_{2i \le n} \dbinom n {2i} g(n-2i) h(2i)$$

#### 求 $g(n)$

入点、出点、孤立点有三类，不方便枚举，不妨把孤立点作为出度为 $0$ 的入点考虑。

尝试枚举出点个数 $i$：

每个出点都会指向入点的一个子集（不能为空，否则就是孤立点了），所以选择数为 $2^{n-i}-1$。

$$g(n) = \sum\limits_{i=0}^n \dbinom n i (2^{n-i}-1)^i$$

#### 求 $h(n)$

$$h(2x) = \dfrac {\prod\limits_{2i \le 2x} \dbinom {2i} 2} {x!} = \dfrac {\dbinom {2x} 2} x h(2x-2) = (2x-1)h(2x-2)$$

其中递归边界情况为 $h(0)=1$。

## 代码

递推预处理可以将复杂度变为 $\mathcal O(n^2 \log n) - \mathcal O(1)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 1000 + 5;
int MOD;

// 省略快读快写的实现

// 省略快速幂 qpow 的实现

LL C[MAXN][MAXN], f[MAXN], g[MAXN], h[MAXN];
void init() {
    // 预处理组合数
    for (int i = 0; i <= 1e3; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
    }

    // 预处理 g
    for (int n = 0; n <= 1e3; n++)
        for (int i = 0; i <= n; i++)
            (g[n] += C[n][i] * qpow(qpow(2, n-i) - 1, i) % MOD) %= MOD;

    // 预处理 h
    h[0] = 1;
    for (int n = 1; 2*n <= 1e3; n++)
        h[2*n] = ((2*n-1) * h[2*n-2]) % MOD;

    // 预处理 f
    for (int n = 1; n <= 1e3; n++)
        for (int i = 0; 2*i <= n; i++)
            (f[n] += C[n][2*i] * g[n-2*i] % MOD * h[2*i] % MOD) %= MOD;
}

int main() {
    int t = read();
    MOD = read();
    init();
    while (t--) {
        int n = read();
        write(f[n], '\n');
    }
    return 0;
}
```


---

## 作者：Warriors_Cat (赞：2)

[洛谷题面传送门](https://www.luogu.com.cn/problem/P9374)。

题意：

* 求 $n$ 个定点有标号简单有向图 $G$ 的个数，其中 $G$ 要求无论怎么删边加边都不改变每个顶点的可达顶点集。

下午要上 MO 课没时间看比赛，晚上随便看了下发现第二题是个数学题，很快就推出来，写篇题解记录一下。

---

Solution：

手玩几个小样例不难发现一个事实：

> $\text{Property}$：若图 $G$ 中存在边 $x\rightarrow y$ 和 $y\rightarrow z$，则 $G$ 不为单图。

证明：可以发现 $x\rightarrow z$ 这条边的存在与否并没有影响，因此改变边 $x\rightarrow z$ 的有无状态即得到另一个图 $H$，因此 $G$ 不为单图。

有了这个性质我们不难发现：对 $G$ 中的每个点，要么它的入度为 $0$ 或出度为 $0$，要么它位于一个仅有两个点的双向边连通分支中。

枚举双向边的个数，从而我们仅需考虑每个点入度为 $0$ 或出度为 $0$ 的情况，此时我们可以用容斥原理得到结果。

具体地讲，我们设 $ans_k$ 为单图个数，$g_k$ 为每个点出度为 $0$ 或入度为 $0$ 的方案数，$f_k$ 为**有一些点出度为 $0$，另一些点入度为 $0$ 的方案数**，这里**不考虑**某个点的出度和入度均为 $0$，很显然：

$$f_k = \sum_{i=0}^k\binom{k}{i}2^{i(k-i)}$$

然后由容斥原理我们可以得到：

$$g_k =\sum_{i=0}^k(-1)^i\binom{k}{i}f_{k-i}$$

所以：

$$ans_k = \sum_{2\mid i}\binom{k}{i}\dfrac{i!}{2^{\frac{i}{2}}(\frac{i}{2})!}g_{k-i}=\sum_{2\mid i}\binom{k}{i}(i-1)!!g_{k-i}$$

$f_k, g_k, ans_k$ 都可以预处理。

over，时间复杂度为 $\mathcal O(n^2 + T)$。

---

Code：

```cpp
#include <cstdio>
using namespace std;
#define rep(i, x, y) for(int i = x; i <= y; ++i)
inline int read(){
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
    return x * f;
}
const int N = 1010;
int n, mod, pw[N * N], a[N], c[N][N], f[N], g[N], ans[N];
int main(){
	int qwq = read(), mod = read();
	pw[0] = 1;
	rep(i, 1, 1000000) pw[i] = pw[i - 1] * 2 % mod;
	c[0][0] = 1;
	rep(i, 1, 1000){
		c[i][0] = 1;
		rep(j, 1, i) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
	}
	a[0] = 1; rep(i, 1, 500) a[i] = 1ll * a[i - 1] * (2 * i - 1) % mod;
	rep(k, 0, 1000) rep(i, 0, k) f[k] = (f[k] + 1ll * c[k][i] * pw[i * (k - i)] % mod) % mod;
	rep(k, 0, 1000) rep(i, 0, k){
		if(i & 1) g[k] = ((g[k] - 1ll * c[k][k - i] * f[k - i] % mod) + mod) % mod;
		else g[k] = (g[k] + 1ll * c[k][k - i] * f[k - i] % mod) % mod;
	}
	rep(k, 0, 1000) rep(i, 0, k / 2) ans[k] = (ans[k] + 1ll * c[k][i * 2] * a[i] % mod * g[k - 2 * i] % mod) % mod;
	while(qwq--){
		int n = read();
		printf("%d\n", ans[n]);
	}
	return 0;
}
```


---

## 作者：Mine_King (赞：2)

## Problem

[P9374 「DROI」Round 2 单图](https://www.luogu.com.cn/problem/P9374)

## Solution

容易发现单图中不能存在三个点按顺序连在一起的情况：

![](https://s2.loli.net/2023/06/02/dEcblg1aHJ7Y83V.png)

但是我们发现二元环是合法的：

![](https://s2.loli.net/2023/06/02/pSWx5IuRbqF7wKs.png)

于是我们可以得到：单图的每一个连通块都是一个单独的点或一个二元环或一个有向二分图（即一部分点向另一部分点连边，且每部分内部无连边）。

考虑分开来统计这些东西。

二元环是好统计的，我们设 $f_i$ 表示 $i$ 个点组成的二元环的方案数，显然有：
$$
f _ i = \left\{
\begin{array}{ll}
f _ {i - 2} \cdot (i - 1) & i \equiv 0 \pmod{2} \\
0 & i \equiv 1 \pmod{2}
\end{array}
\right.
$$
剩下的就是单独的点和二分图，我们把这两个放在一起统计。

首先有一个很显然的想法就是钦定一部分点在左侧，另一部分在右侧，然后连边。设 $g_i$ 表示 $i$ 个点的方案数，则有：
$$
g _ i = \sum\limits _ {j = 0} ^ i \binom{i}{j} \cdot 2 ^ {j (i - j)}
$$
但是这样显然不对，因为单独的点放在左侧和右侧的方案本质上是相同的。

于是我们考虑容斥，设 $h_i$ 为实际答案，则有：
$$
h _ i = \sum\limits _ {j = 0} ^ i \binom{i}{j} \cdot g _ {i - j} \cdot (-1) ^ j
$$
最后统计答案时，直接枚举二元环的点数即可。即，$n$ 的答案为：
$$
\sum\limits _ {i = 0} ^ n \binom{n}{i} \cdot f _ i \cdot h _ {n - i}
$$
总时间复杂度为 $O(n ^ 2 + Tn)$。

## Code

```cpp
// Think twice, code once.
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int T, mod, n, dp[1005], C[1005][1005], pw[1000005], sum[1005], res[1005];

int calc(int x) {return (pw[x] - 1 + mod) % mod;}

int main() {
	scanf("%d%d", &T, &mod);
	for (int i = 0; i <= 1000; i++)
		for (int j = 0; j <= 1000; j++)
			if (j == 0 || j == i) C[i][j] = 1;
			else C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	pw[0] = 1;
	for (int i = 1; i <= 1000000; i++) pw[i] = pw[i - 1] * 2 % mod;
	dp[0] = 1;
	for (int i = 2; i <= 1000; i += 2)
		dp[i] = (long long)dp[i - 2] * (i - 1) % mod;
	for (int i = 0; i <= 1000; i++)
		for (int j = 0; j <= i; j++)
			sum[i] = (sum[i] + (long long)C[i][j] * pw[j * (i - j)] % mod) % mod;
	for (int i = 0; i <= 1000; i++)
		for (int j = 0; j <= i; j++)
			if (j % 2 == 0) res[i] = (res[i] + (long long)C[i][j] * sum[i - j] % mod) % mod;
			else res[i] = (res[i] - (long long)C[i][j] * sum[i - j] % mod + mod) % mod;
	while (T--) {
		scanf("%d", &n);
		int ans = 0;
		for (int i = 0; i <= n; i += 2)
			ans = (ans + (long long)C[n][i] * dp[i] % mod * res[n - i] % mod) % mod;
		printf("%d\n", ans);
	}
	return 0;
}
```



---

## 作者：Y2y7m (赞：1)

upd on 2023 6 19: 已将之前的错误更新。

第一眼直接看出不能有长大于等于 $2$ 的链。

于是我们在排除两个点互相连的情况（我称之为二元环）下可以将所有点分成两种类型：一种有出度，一种有入度（既没有出度也没有入度的我们把其当作有入度的那类）。

定义当前状态为有 $i$ 个点，$j$ 个点有出度，于是答案为 $C^i_n \times (2^{i-j}-1)^j$。

我们设 $f_i$ 为总共有 $i$ 个点时无二元环的答案是多少。

用快速幂做即可。

现在考虑有二元环的。

假设当前有 $k$ 个点组成一个个二元环（容易知道如果组成二元环了，就不能往其他点连边了），总共有 $n$ 个点，我们可以先从 $n$ 个点中选出 $k$ 个，然后每次从这 $k$ 个点中选出最小的然后从剩余点中选一个与其匹配，于是可以知道答案为 $k\times(k-2)\times(k-4)......$

这东西我们可以预处理，我们设 $g_i=i\times(i-2)\times(i-4)......$

于是答案为 $C^k_n\times g_k \times f_{n-k}$

于是这道题就做出来了。

```cpp
//
//  main.cpp
//  「DROI」Round 2 构造与取模
//
//  Created by Y2y7m on 2023/5/28.
//  Copyright © 2023年 Slip. All rights reserved.
//

#include <iostream>
#define int long long
using namespace std;
const int maxn=1010;
int mod;
int c[maxn][maxn];
int f[maxn],g[maxn];
void init()
{
    for(int i=0;i<=1000;i++)
        for(int j=0;j<=i;j++)
        {
            if(j==0) c[i][j]=1;
            else c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
        }
    return ;
}
int q_pow(int a,int b)
{
    int ans=1;
    while(b)
    {
        if(b%2==1) ans*=a,ans%=mod;
        a*=a,a%=mod;
        b/=2;
    }
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false);
    int T;
    cin>>T>>mod;
    init();
    f[0]=1;
    for(int i=1;i<=1000;i++)
    {
        for(int j=0;j<=i;j++)
        {
            int k=i-j;
            f[i]=(f[i]+q_pow((q_pow(2,k)-1),j)*c[i][j]%mod)%mod;
        }
    }
    g[0]=1;
    for(int i=2;i<=1000;i+=2)
    {
        g[i]=1;
        for(int j=i-1;j>=1;j-=2) g[i]=g[i]*j%mod;
    }
    int x;
    while(T--)
    {
        cin>>x;
        int ans=0;
        for(int i=0;i<=x;i+=2) ans=(ans+g[i]*c[x][i]%mod*f[x-i]%mod)%mod;
        cout<<ans<<endl;
    }
    return 0;
}
```


---

## 作者：Llx2022 (赞：1)

# **题目解析**

本题要求计算给定节点数量的有标号单图的数量。
- 首先需要理解什么是单图。

- 单图是指不存在其他简单有向图与其本质相同的图。
- 两个图本质相同，当且仅当对于**任意**点对 $(u, v)$，在图 $G$ 中从 $u$ 出发能走到 $v$ 的情况下，在图    $H$ 中从 $u$ 出发也能走到 $v$，反之亦然。


___
# **思路**
考虑一个 $n$ 个节点的图，我们从节点数量为 $0$ 的情况开始递推。首先，对于只有 $1$ 个节点的情况，显然只有一个单图，即这个节点本身。接下来，我们逐个节点地将单图扩展为 $n$ 个节点的单图。

当我们添加一个新的节点 $i$ 到图中时，我们可以选择在已有的节点集合中**添加一些边**以满足单图的条件。

假设我们添加了 $k$ 个边，那么我们可以得出如下关系：

$$
ans_i = \sum_{j = 0}^{i - 1} {C_{i}^{j} \times (2^{i - j} - 1)^j}
$$

**其中 $ans_i$ 表示 $i$ 个节点的单图数量。**


**分析以上式子：**


考虑从一个有 $i-1$ 个节点的单图 $G$ 扩展到一个有 $i$ 个节点的单图 $H$，我们可以考虑在 $G$ 中添加节点 $i$，然后在 $i$ 与 $G$ 中的节点之间添加若干条边，使得 $H$ 仍然是一个单图。

我们假设在节点 $i$ 与 $G$ 中的节点之间添加了 $j$ 条边，那么 $H$ 中的边数就是 $side_{i-1}+j$，其中      $side$ 表示 $i-1$ 个节点时边的个数。


其中，$i$ 是 $H$ 中新添加的结点，$j$ 是 $i$ 与 $G$ 中的节点之间的边数。由于 $G$ 是 $H$ 的子图，因此 $G$ 中的结点和边在 $H$ 中也存在。我们需要在 $H$ 中添加若干条边，使得 $i$ 与 $G$ 中的节点之间恰好有 $j$ 条边，且添加的边不会破坏 $H$ 的单图性质。


### 我们需要满足以下条件：

$H$ 中的边数不能超过 $\sum_{k=1}^{i-1}k = \frac{i(i-1)}{2}$，否则 $H$ 不是一个简单图。$H$ 中不能包含 $G$ 中任意一条边，否则 $H$ 与 $G$ 本质相同。

**证明**：假设 $H$ 中有 $i-1$ 个结点不在 $G$ 中，我们需要在这 $i-1$个结点和 $i$ 之间添加若干条边，来满足上述要求。由于我们需要保证 $H$ 仍然是一个单图，因此在 $i-1$ 个节点和 $i$ 之间最多只能添加 $i-2$ 条边。因此，我们需要考虑添加 $0, 1, 2, \cdots, i-2$ 条边的所有可能性。

**对于每种添加边的数量的情况**，我们可以使用二进制数的方式来表示。例如，假设我们要在 $H$ 中添加 $k$ 条边，其中 $k < i-1$，我们可以用一个 $i-1$ 位的二进制数来表示，其中第 $j$ 位为 $1$ 表示第 $j$ 个节点与 $i$ 之间添加了一条边，为 $0$ 则表示没有添加。由于 $i$ 与 $G$ 中的节点之间需要恰好有 $j$ 条边，因此我们需要在这个二进制数中选择 $j$ 个位置，将它们的值改为 $1$。因此，我们需要在 $i-1$ 个位置中选择 $j$ 个位置，来添加边。这个选择的过程可以用组合数 $\binom{i-1}{j}$ 来表示。因此，对于给定的 $i$ 和 $j$，满足要求的连通性的数量为 $\binom{i-1}{j}(2^{i-j}-1)^j$。

**其中**，$\binom{i-1}{j}$ 表示选择 $j$ 个位置的方案数，$2^{i-j}-1$ 表示 $i$ 与 $H$ 中的 $i-1$ 个节点之间可以选择的边的方案数，$j$ 表示在这些边中选择 $j$ 条边的方案数。

**因此**，$(2^{i-j}-1)^j$ 表示在 $i$ 与 $H$ 中的 $i-1$ 个节点之间添加边的情况下，其中 $i$ 与 $G$ 中的节点之间需要恰好有 $j$ 条边。这个式子反映了在给定的限制条件下，我们可以通过选择不同的添加边的数量和位置，来得到不同的满足要求的连通性的方案数。


**最后**，我们需要从 $i-1$ 个节点的单图中选取 $j$ 个节点与 $i$ 连边，因此方案数为 $C_{i-1}^{j}$。因此，得到了上述的递推式：

$$
ans_i = \sum_{j = 0}^{i - 1} {C_{i}^{j} \times (2^{i - j} - 1)^j}
$$

**优化**：我们可以预处理所有组合数 $C_{i}^{j}$ 和 $ans_i$ 的值。
___

# **处理答案**

对于一个给定的 $n$，**又因为每个点有标号**，我们可以通过以下方式计算单图的数量：

1. 初始化结果 $res$ 为 $ans_n$。
2. 对于所有的偶数 $i$（$2$ $\leq$ $i$ $\leq$ $n$)，将 $res$ 更新为：
    $$
    res = (res + C_{n}^i \times fact_{i-1} \times ans_{n-i}) \bmod mod 
    $$

最后输出结果 $res$ 即可。

___
# **复杂度分析**

**时间复杂度**：预处理的时间复杂度为 $O(N^2)$，每次查询的时间复杂度为 $O(N)$，共有 $T$ 次查询，总时间复杂度为 $O(N^2 + TN)$。

**空间复杂度**：预处理所需的空间复杂度为 $O(N^2)$，所以总空间复杂度为 $O(N^2)$。



---

