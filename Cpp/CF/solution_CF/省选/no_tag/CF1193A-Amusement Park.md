# Amusement Park

## 题目描述

你被请来设计一个游乐场，它将会使用一种全新科技：可以将游客从一个游乐设施送到另一个游乐设施的滑梯。

现在每条滑梯都已经确定了方向。然而，你发现这个方案存在问题。方案中同时存在从鬼屋通往过山车的滑梯，从过山车通往跳楼机的滑梯，以及从跳楼机通往鬼屋的滑梯。这显然是无法实现的——滑梯必须从高处通向低处，不然会违背物理规律。所以你需要反转一些滑梯的方向，以满足需求。

原始的方案由 $n$ 个游乐设施和 $m$ 条滑梯组成，你可以修改这个方案。

一个修改后的方案必须可以由原始方案反转若干条滑梯的方向得到，并且需要保证存在为每个游乐设施选择高度的方案使得不存在从低处往高处走的滑梯。它的代价为反转的滑梯数量。

你需要统计所有可能的方案的代价之和，对 $998244353$ 取模。

## 说明/提示

对于所有数据，$1\le n\le 18,0\le m\le \frac{n(n-1)}{2}$。不存在重边、自环。对于任意 $1\le u,v\le n$ 不同时存在边 $(u,v)$ 和 $(v,u)$。

子任务 $1$（$7$ 分）：$n\le 3$。

子任务 $2$（$12$ 分）：$n\le 6$。

子任务 $3$（$23$ 分）：$n\le 10$。

子任务 $4$（$21$ 分）：$n\le 15$。

子任务 $5$（$37$ 分）：无附加限制。

## 样例 #1

### 输入

```
2 1
1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 3
1 2
2 3
1 3
```

### 输出

```
9
```

# 题解

## 作者：封禁用户 (赞：8)

## 题意

对于一个有向图，翻转一些边使得其无环，问所有方案的总翻转边数对某个数取模后的结果。

## 分析

由题目，$m\le\dfrac{n(n-1)}{2}$。

对于前两个 $n\le6$ 的子任务，$m\le15$，所以可以枚举每条边是否翻转。

判断一个有向图是否存在环，可以使用[拓扑排序](https://oi-wiki.org/graph/topo/)，若原图为有向无环图 （DAG），则就能 push 进去所有的点，则 $sum=n$。

时间复杂度 $O(n\times2^n)$。

## Code（19ppt）

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 998244353
#define N 22
#define M 400 
ll ans = 0;
vector<int> g[N];
int x[M],y[M],deg[N],n,m;
int main()
{
    //freopen("park.in","r",stdin);
    //freopen("park.out","w",stdout);
    scanf("%d%d",&n,&m);
    if(!m)
	{
		putchar('1');
		return 0;	
	} 
    for(int i = 0;i < m;++i)
    {
        scanf("%d%d",&x[i],&y[i]);  
        g[x[i]].push_back(y[i]);
        g[y[i]].push_back(x[i]);
    }
    for(int t = 0;t < 1<<m;++t)
    {
        int cnt = 0,sum = 0;
        for(int i = 1;i <= n;++i) g[i].clear();
        for(int i = 1;i <= n;++i) deg[i] = 0;
        for(int i = 0;i < m;++i)
        {
            if(t & (1<<i))
            {
                ++cnt;  
                g[y[i]].push_back(x[i]);
                ++deg[x[i]];
            }   
            else
            {
                g[x[i]].push_back(y[i]);
                ++deg[y[i]];
            }
        }
        queue<int> q;
        for(int i = 1;i <= n;++i)
            if(!deg[i])
                q.push(i);
        while(q.size())
        {
            ++sum;
            int u = q.front();
            q.pop();
            for(auto v:g[u])
                if(--deg[v] == 0)
                    q.push(v);      
        } 
        if(sum == n) ans = (ans + cnt) % mod;
    }
    printf("%lld",ans);
    return 0;
}
```

## 推导结论

先前置一个结论：**对于一个有向无环图 （DAG），翻转所有边后仍是有向无环图 （DAG）**。

简单地证明一下：对于有向图中的一个环，翻转所有边，肯定是一个环，只是方向反了一下。所以一个有向图中的一个环也必然要由一个环翻转过来。

所以原图存在环是反图存在环的充分必要条件。

所以一个有向无环图 （DAG） 翻转后不可能存在环，即还是有向无环图 （DAG）。

有了这个结论，就可以进行优化了。

## 优化

对于一个有向图，如果翻转 $p$ 条边是一个有向无环图 （DAG），那么其反图，翻转 $m-p$ 条边也必然是一个有向无环图 （DAG）。

这两种情况，平均翻转了 $\frac{m}{2}$ 条边。

所以题目就转化成了：翻转一些边，求出成为有向无环图 （DAG） 的方案个数乘上 $\frac{m}{2}$ 对某个数取模的结果。

## 思路

这样就可以进行状态压缩 DP 了。

设 $dp_i$ 为状态 $i$ 成为有向无环图 （DAG） 的方案数量。

枚举 $i$ 的子集 $j$ 进行转移，**显然 $j$ 必定为独立集**（老生常谈了）
。

但是这样有个严重的问题：会算重。

所以我们使用容斥原理，根据集合的大小进行容斥。大小为奇数则加，大小为偶数则减。

![容斥原理](https://imgconvert.csdnimg.cn/aHR0cDovL3d3dy5jcHBibG9nLmNvbS9pbWFnZXMvY3BwYmxvZ19jb20vdmljaS8wMDAucG5n?x-oss-process=image/format,png)

原因比较套路，这里不详细讲容斥原理了，具体可以简单地查看[这个帖子](https://www.luogu.com.cn/discuss/451465)。

最终代码的时间复杂度为 $O(3^n+m\times2^n)$。

注意在最后答案的计算中使用**逆元**，不然可能会答案错误。
## AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 998244353
#define maxn 262145
#define N 22
#define M 400 
bitset<maxn> p;
ll dp[maxn];
int n,m,cnt[maxn],x[M],y[M];
int main()
{
	//freopen("park.in","r",stdin);
	//freopen("park.out","w",stdout);
	scanf("%d%d",&n,&m);
	if(!m)
	{
		putchar('1');
		return 0;
	}
	int k = 1<<n;
	for(int i = 1;i <= m;++i) scanf("%d%d",&x[i],&y[i]);
	for(int i = 0;i < k;++i)
	{
		int sum = 0;
		for(int j = i;j;j&=(j-1)) ++sum;
		if(sum & 1) cnt[i] = 1;
		else cnt[i] = -1;//确定容斥系数
		for(int j = 1;j <= m;++j)
			if(i&(1<<x[j]-1)&&i&(1<<y[j]-1))
			{
				p[i] = 1;
				break;		
			}	//判断独立集
	}
	dp[0] = 1ll;
	for(int i = 1;i < k;++i)
		for(int j = i;j;j = i&(j-1))
			if(!p[j])
				dp[i] = (dp[i] + dp[i^j] * cnt[j] + mod) % mod;
	printf("%lld",dp[k-1]*(mod+1)/2%mod*m%mod);//注意使用逆元
	return 0;
}
```

---

## 作者：Arghariza (赞：5)

Luogu 最优解。（2023/9/27）

详细讲一下容斥系数是怎么配的，还有 $O(n^22^n)$ 的优化。

发现一个 DAG 所有边反转后仍然是 DAG，所以一个反转了 $c$ 次的反转方案唯一对应了一个反转了 $m-c$ 次的方案。两种方贡献案之和为 $m$，所以设 $s$ 为给无向图定向成为 DAG 的方案数，答案就是 $\frac{s\times m}{2}$。

于是问题转化为求给一张无向图边定向，使得定向后成为 DAG 的方案数。考虑状压 dp，令 $f_S$ 为给点集 $S$ 的导出子图定向后为 DAG 的方案数。

考虑 DAG 中一定有出度为 $0$ 的独立集，同时删去这个集合后图仍为 DAG，所以枚举独立集 $T$，钦定其出度为 $0$：

$$f_S=\sum\limits_{T\subset S,T\neq \varnothing}f_{S\setminus T}\cdot g(|T|)[T\in \text{independent set}]$$

$g(n)$ 为容斥系数，因为会算重。由于一个大小为 $n$ 的点集 $T$ 会被它的每个非空子集计算一次，而我们要求 $T$ 的贡献恰好为 $1$：

$$1=\sum\limits_{i=1}^n\dbinom{n}{i}g(i)$$

大眼观察得：$g(1)=1,g(2)=-1,g(3)=1,\cdots$。我们猜测 $g(n)=(-1)^{n_+1}$：

$$\begin{aligned}\sum\limits_{i=1}^m\dbinom{n}{i}(-1)^{i+1}&=-\left(\sum\limits_{i=0}^{n}\dbinom{n}{i}(-1)^i-1\right)\\&=-\left((-1+1)^n-1\right)=1\end{aligned}$$

所以取 $g(n)=(-1)^{n+1}$ 即可：

$$f_S=\sum\limits_{T\subset S,T\neq \varnothing}(-1)^{|T|+1}f_{S\setminus T}[T\in \text{independent set}]$$

暴力算是 $O(3^n)$ 的，在线做子集卷积即可达到 $O(n^22^n)$。

```cpp
// Problem: Amusement Park
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1193A
// Memory Limit: 1000 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Med;

const int N = 20;
const int T = (1 << 18) + 5;
const int P = 998244353;
const int i2 = (P + 1) / 2;

int n, m, S, a[N][N];
int f[N][T], g[N][T], pc[T];

void Add(int &x, int y) { x += y, (x >= P) && (x -= P); }
void FWT(int *f, int op) {
	Add(op, P);
	for (int o = 2, k = 1; o <= S + 1; o <<= 1, k <<= 1)
		for (int i = 0; i <= S; i += o)
			for (int j = 0; j < k; j++)
				Add(f[i + j + k], 1ll * op * f[i + j] % P);
}

void solve() {
	cin >> n >> m, S = (1 << n) - 1;
	for (int i = 1, u, v; i <= m; i++) 
		cin >> u >> v, u--, v--, a[u][v] = a[v][u] = 1;
	for (int i = 1; i <= S; i++) pc[i] = pc[i >> 1] + (i & 1);
	for (int i = 1; i <= S; i++) {
		int fl = 1;
		for (int u = 0; u < n; u++) 
			for (int v = 0; v < u; v++) 
				if (((i >> u) & 1) && ((i >> v) & 1) && a[u][v]) { fl = 0; break; }
		if (!fl) continue;
		g[pc[i]][i] = (pc[i] & 1) ? 1 : P - 1;
	}
	for (int i = 1; i <= n; i++) FWT(g[i], 1);
	f[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		FWT(f[i - 1], 1);
		for (int j = 0; j < i; j++)
			for (int k = 0; k <= S; k++)
				Add(f[i][k], 1ll * f[j][k] * g[i - j][k] % P);
		FWT(f[i], -1);
		for (int j = 0; j <= S; j++)
			if (pc[j] != i) f[i][j] = 0;
	}
	cout << 1ll * f[n][S] * i2 % P * m % P;
}

bool Mbe;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Med - &Mbe) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：傅思维666 (赞：3)

## 题解：

作为本题第一个提交翻译的人（也不知道现在过没过）和第二个AC的人，先抢着发一下第一篇题解。

乍一看题面（因为是我翻译的）感觉题目爆难（事实上的确挺难的）。但是实际上我们不需要确定这张图的海拔高度到底是多少。我们只需要保证这张图没有环即可（由样例说明可以得出，环是绝对不合法的）。同理，我们可以证明，只要这个图不包含环，那么这个图就绝对是合法的。

那么题意就变成了：一张有向图，随便改边的方向，最终的答案是使图无环的贡献之和。

~~但是蒟蒻太弱了，自己只YY到了上面的步骤...~~

我们可以这样去想，对于一张图，我们可以把它拆成若干个DAG（有向无环图），这些DAG以点集的形式出现。确定一个DAG为初始集合。那么我们可以这样考虑：我们把剩下的DAG点集分批次加入到这个初始集合中，但是，DAG+DAG不一定还是DAG，所以我们在加入的时候进行判断。显然，假如我们新加入的点的出度或入度全部为0，那么这个加入后的原始集合就会依然合法。

注意这个关系是**或**！为什么呢？以为我们只要保证这些点的出度或者入度都为0，我们就可以保证：我们在链接的时候只连它们中度为0的那些，而那些度不为0的就无论如何也不会和原图构成环。

所以我们考虑采用DP来解决方案数的问题：设DP[a]为集合a为DAG的方案总数。

但是我们会出现：一个合法的小集合，我们既可以把它分多次依次加入，也可以把它一次性加入。

所以我们还需要利用容斥原理。

思路及代码借鉴自@zryabc's blog。



```cpp
#include<bits/stdc++.h>
#define ll long long
#define check(x,y) (((x)>>((y)-1))&1)
using namespace std;
const int mod=998244353;
const int maxn=1<<18|5;
int n,m;
int u[405],v[405];
ll dp[maxn];
int cnt[maxn];
bool mark[maxn];
void add(ll &x,ll y)
{
    x+=y;
    if(x>=mod)
        x-=mod;
    if(x<0)
        x+=mod;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&u[i],&v[i]);
    cnt[0]=-1;dp[0]=1;
    for(int i=1;i<1<<n;i++)
        cnt[i]=-cnt[i&(i-1)];
    for(int i=1;i<1<<n;i++)
        for(int j=1;j<=m;j++)
            if(check(i,u[j]) && check(i,v[j]))
            {
                mark[i]=1;
                break;
            }
    for(int i=1;i<1<<n;i++)
        for(int j=i;j>=1;j=(j-1)&i)
            if(!mark[j])
                add(dp[i],dp[i^j]*cnt[j]);
    printf("%lld\n",dp[(1<<n)-1]*m%mod*499122177%mod);
    return 0;
}
```


---

## 作者：AxB_Thomas (赞：2)

## 一.题意：
你有一个有向图，你可以选择翻转一些边的方向使其变成一个DAG，求所有翻转方案的总翻转边的数量对$998244353$取模
## 二.思路：
一个很显然的暴力做法是枚举每条边是否翻转，并且通过拓扑排序判断是否存在环，复杂度为 $O(n\times 2^m)$ 可以通过19pts的部分分。

**正解**：
手搓几组样例，我们发现翻转的方案是成对出现的：若每次选了 $x$ 条边翻转可以得到一个DAG，那么回到原来的图上，翻转剩余的 $m-x$ 条边也依旧是一个DAG。

那这个猜想的正确性或者说本质是什么呢？其实是下面的定理：**如果一个有向图是一个DAG，那么翻转其所有边之后，其依旧是一个DAG。** 这个定理是显然成立的，那么上面的猜想其实就是因为我们先翻转了 $x$ 条边之后变成了一个DAG，然后翻转整个图也是DAG才成立的，因为你翻转了两次，所以一开始翻转的 $x$ 条边就被翻回到原来的状态了。所以你发现这两种情况翻转的数量加起来的和是定值 $m$ ，所以每一次的平均贡献就是 $\frac{m}{2}$。

所以现在这一个问题就转化成了：给你一个无向图，需要给这个无向图定向，使其最终成为一个DAG的方案数然后答案乘上 $\frac{m}{2}$。

看到$n$的范围这么小，又是求方案数，我们就考虑状态压缩dp:定义状态 $f(S)$ 表示给点集 $S$ 的导出无向子图定向后为DAG的方案数。考虑转移：$S$中必定存在出度为$0$的独立集，说白了就是可以找出$S$的子集，使得其中的点互相没有约束（连边）。思考为什么，其实是因为一个DAG必定可以进行拓扑排序，他们是充要的，如果我们回忆拓扑排序的过程，你就会发现上面的结论是显然的。所以转移就从 $S$ 中互相没有约束的子点集转移过来，形式化的：
$$f(S)=\sum_{T\subseteq S,T\neq\varnothing}f(S\setminus T)\cdot G(|T|)$$
需要注意的是这里的$T$必须是一个独立集，并且$G(|T|)$是我们的容斥系数。那么现在的问题就是如何配容斥系数了。

**Q**:为什么会算重？

**A**:因为对于每一个独立集，我们可以选择一次全部加到集合 $S$ 中，或者，分多次加到 $S$ 中。

我们需要所有子集对于答案的最终贡献都是$1$，但是在上述计算中，$T$的每一个子集都会出现，也就是我们需要:
$$\sum_{i=1}^{|T|}\dbinom{|T|}{i}G(i)=1$$
可以证明的是：$G(i)=(-1)^{i+1}$。因为：
$$\sum_{i=1}^{|T|}(-1)^{i+1}\dbinom{|T|}{i}=-\left(\sum_{i=0}^{|T|}(-1)^{i}\dbinom{|T|}{i}-1\right)=-\left((-1+1)^{|T|}-1\right)=1$$

所以最终答案就可以彻底用程序去计算了。

现在我们来分析复杂度的问题，最终计算的时候我们通过子集枚举的方式来转移dp，此部分的复杂度为 $O(3^n)$ ，而一开始的预处理独立集的复杂度是 $O(m\cdot2^n)$ 所以综上，总复杂度就为 $O(3^n+m\cdot2^n)$。此外，有的大佬题解中还包含子集卷积优化的内容，本人水平不足，就不班门弄斧了。

## 三.code:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(ch > '9' || ch < '0'){if(ch == '-'){f = -1;}ch = getchar();}
	while(ch >= '0'&&ch <= '9'){x = x * 10 + ch - 48; ch = getchar();}
	return x * f;
} 

const int MOD = 998244353;
const int MAX_S = (1 << 18) + 5,MAX_E = 400 + 5;
int f[MAX_S],n,m,u[MAX_E],v[MAX_E],inv_2 = 499122177;
bool mark[MAX_S]; 

void add(int &x,int y)
{
	x += y;
	if(x >= MOD) x -= MOD;
	if(x < 0) x += MOD;
}
	
signed main()
{
	n = read();m = read();
	for(int i = 1;i <= m;++i)
	{
		u[i] = read();
		--u[i];
		v[i] = read();
		--v[i];
	}
	int up_lim = 1 << n;

	for(int i = 1;i < up_lim;++i)
	{
		for(int j = 1;j <= m;++j)
		{
			if(((i >> u[j]) & 1) && ((i >> v[j]) & 1))
			{
				mark[i] = true;
				break;
			}
		}
	}
	
	f[0] = 1;
	for(int i = 1;i < up_lim;++i)
	{
		for(int j = i; j;j = (j - 1) & i)
		{
			if(!mark[j])
			{
				if(__builtin_popcount(j) & 1) add(f[i],f[i ^ j]);
				else add(f[i],-f[i ^ j]);
			}
		}
	}
	int ans = f[up_lim - 1] * m % MOD * inv_2 % MOD;
	std::cout << ans;
	return 0;	
} 
```

---

## 作者：_fairytale_ (赞：1)

设 $f[S]$ 表示给 $S$ 中点的生成子图中的边定向形成 DAG 的方案数，转移的时候，枚举 $S$ 的一个非空子集 $T$ 并钦定其度数为 $0$，从 $f[S \setminus T]$ 转移到 $f[S]$。

因为计算 $f[S]$ 会重，考虑在钦定 $A$ 的非空子集度数为 $0$ 时，算上了钦定 $A$ 度数为 $0$ 的方案数，所以设计容斥系数 $g$，使
$$\sum_{B\subseteq A}g(B)=1$$

不难发现 $g(B)=(-1)^{|B|-1}$。

证明的话，考虑枚举 $|B|$,
$$\sum_{B\subseteq A}g(B)=\sum_{i=1}^{|A|}{|A|\choose i}(-1)^{i-1}$$

根据杨辉三角可得上面那个为 $1$。

求出给边定向形成 DAG 的方案数之后，我们考虑，如果从原图反转了 $k$ 条边形成一个 DAG，那么反转其余的 $(m-k)$ 条边也必然形成一个 DAG，因此我们求出的这些 DAG 可以两两配对，每一对都翻转了 $m$ 条边，所以答案即为 $\dfrac{f[U]}{2}\times m$。

```cpp
#include<bits/stdc++.h>
#define rep(x,qwq,qaq) for(int (x)=(qwq);(x)<=(qaq);++(x))
using namespace std;
#define mod 998244353
#define inv 499122177
int n,m,u,v;
bool can[(1<<18)];
int f[(1<<18)],g[(1<<18)];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	memset(can,1,sizeof can);
	f[0]=1,g[0]=-1;
	cin>>n>>m;
	rep(S,0,(1<<n)-1)g[S]=g[S>>1]*(S&1?-1:1);
	rep(i,1,m) {
		cin>>u>>v;
		rep(S,0,(1<<n)-1)if(((S>>(u-1))&1)&&((S>>(v-1))&1))can[S]=0;
	}
    rep(S,0,(1<<n)-1)for(int T=S;T;T=(T-1)&S)if(can[T])f[S]=(f[S]+g[T]*f[S^T])%mod;
    cout<<1ll*f[(1<<n)-1]*inv%mod*m%mod;
	return 0;
}
```

---

## 作者：伟大的王夫子 (赞：1)

首先，我们将原题转化为求最后形成一个 DAG 的方案数。我们假设我们翻转了 $x$ 条边，那么我们翻转剩下 $m - x$ 条边，相当于是把原 DAG 所有得边方向反一下，显然还是个 DAG。于是答案就是方案数乘上 $\dfrac{m}{2}$。原问题便转化为：给定一个无向图，现在要将其中的每条边定一个方向，要求最终形成的有向图没有环，请问有多少种方案？

对一个有向无环图而言，肯定存在一些节点入度为 0，而我们删除这些点后，剩下的图一定也是个 DAG。只要这些点是独立集（互相之间没有边相连，可以 $O(2 ^ n \times n^2)$ 预处理），那么就一定可以找到一种方式确定与这些点相连的边的方向，并且这种方案有且仅有一种。那我们可以枚举这些入度为 0 的点进行统计。但是，我们可以进行容斥。设这些入度为 0 的点数量为 $cnt$，那么容斥系数为 $(-1)^{cnt - 1}$。就相当于是加上除去这些入度为 0 的点的 DP 值，再乘上这个系数。具体的，我们采用枚举子集的方法，时间复杂度为 $O(3^n + 2^n \times n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int n, m, dp[1 << 18], a[20], g[1 << 18];
bool in_s[1 << 18];
int main() {
	cin >> n >> m;
	for (int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		--x, --y;
		a[x] |= 1 << y;
		a[y] |= 1 << x;
	}
	for (int s = 0; s < (1 << n); ++s)  {
		in_s[s] = 1;
		g[s] = __builtin_popcount(s) & 1 ? 1 : -1;
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j)
				if ((s >> i & 1) && (s >> j & 1) && (a[i] >> j & 1)) {
					in_s[s] = 0;
					break;
				}
	}
	dp[0] = 1;
	for (int s = 1; s < (1 << n); ++s)
		for (int i = s; i; i = (i - 1) & s)
			if (in_s[i]) {
				dp[s] += g[i] * dp[s ^ i];
				if (dp[s] < 0) dp[s] += mod;
				dp[s] %= mod;
			}
	cout << 1ll * dp[(1 << n) - 1] * (mod + 1 >> 1) % mod * m % mod << endl;
}
```

---

## 作者：lfxxx (赞：0)

任意合法定向方案，反转所有边后一定也合法，而且两种方案的贡献和是 $m$，因此答案就是定向方案数量乘上 $\frac{m}{2}$。

不妨 $dp_{S}$ 表示将 $S$ 中的点构成的导出子图定向为 DAG 的方案，考虑每次将 DAG 中所有零度点剥去以递归到子状态，但是你发现钦定剩下的点度数大于 $0$ 不太现实，考虑一个非常牛的容斥，枚举零度点的一个非空子集 $T$ 然后 $dp_{S} \gets dp_{S} + dp_{S - T} \times (-1)^{|T|+1}$，你发现对于所有的 DAG 其零度点的每个子集都对这个 DAG 产生了一次贡献，又因为带了容斥系数所以每个 DAG 刚好就被算了一遍，对于 $T$ 的限制是将给定的有向边视作无向边后其为一个独立集，可以在 $O(n \times 2^n)$ 的时间复杂度内预处理，而 dp 的复杂度是 $O(3^n)$ 的，因此总复杂度就是 $O(n \times 2^n + 3^n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int maxv = (1<<18);
int dp[maxv],pop[maxv];
int n,m;
int E[maxv];
int vis[maxv];
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
signed main(){
	cin>>n>>m;
	for(int i=1;i<(1<<n);i++) pop[i]=pop[i/2]+(i&1);
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		E[u-1]|=((1<<(v-1)));
		E[v-1]|=((1<<(u-1)));
	}
	vis[0]=1;
	for(int i=1;i<(1<<n);i++){
		for(int j=0;j<n;j++){
			if((1<<j)&i){
				if((E[j]&(i-(1<<j)))==0) vis[i]|=vis[i-(1<<j)];
			}
		}
	}
	dp[0]=1;
	for(int i=1;i<(1<<n);i++){
		for(int j=i;j;j=(j-1)&i){
			if(vis[j]==1) dp[i]=(dp[i]+dp[i-j]*(pop[j]%2==0?mod-1:1)%mod)%mod;
		}
	}
	cout<<dp[(1<<n)-1]*m%mod*((mod+1)/2)%mod<<'\n';
	return 0;
}
```

---

## 作者：__ycx2010__ (赞：0)

## Solution

若改变了 $k$ 条边能变为有向无环图，那么反转另外 $m-k$ 条边也一定能得到有向无环图，所以平均反转 $\frac{m}{2}$ 条边，转化为求有向无环图的个数。

设 $f_S$ 表示原图 $G$ 中包含点集 $S$ 的导出子图的方案数。

假设 $T$ 为拓扑图上的第一层点，也就是没有入边的点，那么这些点一定要满足 $T$ 为独立集，发现这样会有重复，所以用容斥得到

$$f_S = \sum _{T\subseteq S} (-1)^{|T|+1} f_{S\backslash T}$$

时间复杂度 $O(3^n)$。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 20, mod = 998244353;
int g[N][N], bit[1 << N], f[1 << N], ok[1 << N];

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		g[a][b] = g[b][a] = 1;
	}
	vector<int> v;
	for (int i = 1; i < (1 << n); i ++ ) {
		for (int j = 0; j < n; j ++ )
			if (i >> j & 1)
				bit[i] ++ ;
		ok[i] = 1;
		for (int j = 0; j < n; j ++ )
			if (i >> j & 1)
				for (int k = j + 1; k < n; k ++ )
					if ((i >> k & 1) && g[j + 1][k + 1])
						ok[i] = 0;
	}
	f[0] = 1;
	for (int i = 1; i < (1 << n); i ++ )
		for (int j = i; j; j = (j - 1) & i)
			if (ok[j])
				f[i] = (f[i] + ((bit[j] & 1) ? f[i ^ j] : 1ll * (mod - 1) * f[i ^ j] % mod)) % mod;
	printf("%d\n", 1ll * f[(1 << n) - 1] * m % mod * (mod + 1 >> 1) % mod);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

定理：DAG 的每条边翻转后仍然为 DAG。

证明：考虑把 DAG 抽象成分层图，原来所有的边都是前面层向后面层连，现在所有的边都是后面层向前面层连，这样是不可能有环的。

于是原问题转化为给每条边定向，求 DAG 数量。最后乘 $\frac{m}{2}$ 即可。

考虑 $dp_S$ 表示 $S$ 子集形成 DAG 的方案数。钦定一个子集 $T$ 入度为 $0$，考虑容斥：

* $|T|$ 为奇数时：$dp_S\leftarrow dp_{S\oplus T}$；
* $|T|$ 为偶数时：$dp_S\leftarrow -dp_{S\oplus T}$。

预处理出每个子集是否合法（两两无边）。显然可以 $O(3^n)$ 枚举子集。已经可以通过。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define int long long
#define double long double
#define mid ((l+r)>>1)
#define add(i,j) ((i+j>=mod)?(i+j-mod):(i+j))
using namespace std;
const int mod=998244353;
int nr[19][19],pre[262144][19],ok[262144];
int dp1[262144];
signed main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b; cin>>a>>b;
		nr[a][b]=nr[b][a]=1;
		for(int j=0;j<(1<<n);j++){
			if((j>>(a-1))&1){
				pre[j][b]++;
			}
		}
	}
	for(int i=0;i<(1<<n);i++){
		ok[i]=1;
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				if((i>>(j-1))&1){
					if((i>>(k-1))&1){
						if(nr[j][k]) ok[i]=0;
					}
				}
			}
		}
	}
	dp1[0]=1;
	int all=(1<<n)-1;
	for(int i=1;i<(1<<n);i++){
		for(int j=i;j;j=(j-1)&i){
			if(!ok[j]) continue;
			if(__builtin_popcount(j)&1) dp1[i]+=dp1[i^j];
			else dp1[i]-=dp1[i^j];
		}
		dp1[i]%=mod;
	} 
	cout<<((dp1[all]%mod+mod)*((mod+1)/2)%mod*m)%mod;
	return 0;
}
```

本题仍可优化，考虑这个转移，所有 $|T|$ 为奇数的系数均为 $1$，偶数均为 $-1$。故可以使用子集卷积优化。复杂度 $O(2^nn^2)$。

---

