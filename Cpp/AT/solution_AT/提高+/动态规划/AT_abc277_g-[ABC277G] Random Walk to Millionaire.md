# [ABC277G] Random Walk to Millionaire

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc277/tasks/abc277_g

$ N $ 個の頂点と $ M $ 本の辺からなる連結かつ単純な無向グラフが与えられます。  
$ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結んでいます。

高橋君は、はじめ**レベル**が $ 0 $ の状態で頂点 $ 1 $ におり、下記の行動をちょうど $ K $ 回行います。

- まず、いまいる頂点に隣接する頂点の中から、$ 1 $ つを等確率でランダムに選択し、その頂点に移動する。
- その後、移動後の頂点 $ v $ に応じて、下記のイベントが発生します。
  - $ C_v\ =\ 0 $ のとき : 高橋君のレベルが $ 1 $ だけ増加する。
  - $ C_v\ =\ 1 $ のとき : 高橋君のいまのレベルを $ X $ とする。高橋君は $ X^2 $ 円のお金を獲得する。

上記の $ K $ 回の行動の過程で高橋君が獲得するお金の合計金額の期待値を $ \mathrm{mod}\,\ 998244353 $ で出力してください（注記参照）。

## 说明/提示

### 注記

求める期待値は必ず有理数となることが証明できます。またこの問題の制約下では、その値を互いに素な $ 2 $ つの整数 $ P $, $ Q $ を用いて $ \frac{P}{Q} $ と表したとき、$ R\ \times\ Q\ \equiv\ P\pmod{998244353} $ かつ $ 0\ \leq\ R\ \lt\ 998244353 $ を満たす整数 $ R $ がただ一つ存在することが証明できます。この $ R $ を求めてください。

### 制約

- $ 2\ \leq\ N\ \leq\ 3000 $
- $ N-1\ \leq\ M\ \leq\ \min\lbrace\ N(N-1)/2,\ 3000\rbrace $
- $ 1\ \leq\ K\ \leq\ 3000 $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- $ u_i\ \neq\ v_i $
- $ i\ \neq\ j\ \implies\ \lbrace\ u_i,\ v_i\rbrace\ \neq\ \lbrace\ u_j,\ v_j\ \rbrace $
- 与えられるグラフは連結
- $ C_i\ \in\ \lbrace\ 0,\ 1\rbrace $
- 入力はすべて整数

### Sample Explanation 1

高橋君の移動経路として考えられるものは複数ありますが、ここでは例として、高橋君が頂点 $ 1 $ を始点として、$ 1\ \rightarrow\ 2\ \rightarrow\ 4\ \rightarrow\ 5\ \rightarrow\ 4\ \rightarrow\ 2\ \rightarrow\ 1\ \rightarrow\ 2\ \rightarrow\ 3 $ と移動する場合に獲得するお金の合計金額を計算します。 1. 高橋君は $ 1 $ 回目の行動で、いまいる頂点 $ 1 $ に隣接する頂点 $ 2 $ に移動します。$ C_2\ =\ 0 $ であるため、その後高橋君のレベルが $ 1 $ に上がります。 2. 高橋君は $ 2 $ 回目の行動で、いまいる頂点 $ 2 $ に隣接する頂点 $ 4 $ に移動します。$ C_4\ =\ 1 $ であるため、その後高橋君は $ 1^2\ =\ 1 $ 円を獲得します。 3. 高橋君は $ 3 $ 回目の行動で、いまいる頂点 $ 4 $ に隣接する頂点 $ 5 $ に移動します。$ C_5\ =\ 0 $ であるため、その後高橋君のレベルが $ 2 $ に上がります。 4. 高橋君は $ 4 $ 回目の行動で、いまいる頂点 $ 5 $ に隣接する頂点 $ 4 $ に移動します。$ C_4\ =\ 1 $ であるため、その後高橋君は $ 2^2\ =\ 4 $ 円を獲得します。 5. 高橋君は $ 5 $ 回目の行動で、いまいる頂点 $ 4 $ に隣接する頂点 $ 2 $ に移動します。$ C_2\ =\ 0 $ であるため、その後高橋君のレベルが $ 3 $ に上がります。 6. 高橋君は $ 6 $ 回目の行動で、いまいる頂点 $ 2 $ に隣接する頂点 $ 1 $ に移動します。$ C_1\ =\ 0 $ であるため、その後高橋君のレベルが $ 4 $ に上がります。 7. 高橋君は $ 7 $ 回目の行動で、いまいる頂点 $ 1 $ に隣接する頂点 $ 2 $ に移動します。$ C_2\ =\ 0 $ であるため、その後高橋君のレベルが $ 5 $ に上がります。 8. 高橋君は $ 8 $ 回目の行動で、いまいる頂点 $ 2 $ に隣接する頂点 $ 3 $ に移動します。$ C_3\ =\ 1 $ であるため、その後高橋君は $ 5^2\ =\ 25 $ 円を獲得します。 よって、高橋君が獲得するお金の合計金額は、$ 1\ +\ 4\ +\ 25\ =\ 30 $ 円です。

## 样例 #1

### 输入

```
5 4 8
4 5
2 3
2 4
1 2
0 0 1 1 0```

### 输出

```
89349064```

## 样例 #2

### 输入

```
8 12 20
7 6
2 6
6 4
2 1
8 5
7 2
7 5
3 7
3 5
1 8
6 3
1 4
0 0 1 1 0 0 0 0```

### 输出

```
139119094```

# 题解

## 作者：_SeeleVollerei_ (赞：10)

专门开个博客投个题解罢了。

考虑暴力是 $f_{i,j,k}$ 表示第 $i$ 步走到点 $j$，且当前等级为 $k$ 的概率。复杂度 $O(nmk)$。

考虑把 $k$ 压入 dp 值，发现 $k+1$ 的时候，平方的值会变成 $(k+1)^2=k^2+2k+1$，所以令 $f_{i,j,0/1/2}$ 表示第 $i$ 步走到 $j$ 时当前等级的 0/1/2 次方的期望值即可，然后暴力转移。

复杂度 $O((n+m)k)$。

https://atcoder.jp/contests/abc277/submissions/36436795

---

## 作者：Sharpsmile (赞：5)

# [ABC277G] 题解

## Random Walk to Millionaire

### 题目大意

给定一张 $n$ 个点，$m$ 条边的有向图，每个点有两种类型：经验池和副本。有一个人一开始在 $1$ 号节点，等级为 $0$ 。现在他进行恰好 $k$ 次随机游走操作，一次随机游走操作定义为：从所在点的所有出边中等概率选择一条出边走出去。如果目标点是经验池，则等级 $+1$ ，否则若当前等级为 $X$ ，获得 $X^2$ 个金币。求最后的金币期望值。$n,m,k \leq3000$。

### 题目解析

观察数据范围，感觉大概是一个 $O(n^2)$ 的做法。挺套路的一个题。不过这里可不能使用求所有的和，再除方案的方式，因为每一种走法的概率不是平均的。

看一下题目中的金币获取方式，是一个平方，感觉不好处理，不难想到类似于 `OSU!` 这种题，我们拆贡献。

具体的，我们从后向前考虑，假设我们已经知道了这 $k$ 次随机游走的具体方案，每次考虑经过一个经验池升级之后带来的影响。设我们在经过这个点之后经过的所有副本点和不考虑这个点和之前的所有经验点所的等级构成的有序对 $(x,l)$ 构成的集合为 $S=\{(x_1,l_1),(x_2,l_2),\cdots,(x_t,l_t)\}$，在不考虑当前经过这个经验池的时候，这些副本点得到的金币总和为：$\sum\limits_{i\in[1,t]} l_i^2$ ，而将这个点的等级加上之后得到的金币总和为 $\sum\limits_{i\in[1,t]} (l_i+1)^2=\sum\limits_{i\in[1,t]} l_i^2+\sum\limits_{i\in[1,t]} 2l_i+t$ ，所以我们对于一种方案只需要知道每一步的 $\sum\limits_{i\in[1,t]} l_i^2,\sum\limits_{i\in[1,t]}l_i,t$ 即可，由于这里使用的是加和，所以期望也可以直接这么求。所以我们需要知道的是三件：每个点出去走 $k$ 步的期望金币数量，期望副本等级和，期望副本数量即可。

我们分别设其为 $dpsq_{u,k},dps_{u,k},dpc_{u,k}$。对于经验点，我们有：

$dpsq_{u,k}=\frac{\sum \limits_{v\in Son_u} dpsq_{v,k-1}+2\times dps_{v,k-1}+dpc_{v,k-1}}{|Son_u|}$

$dps_{u,k}=\frac{\sum \limits_{v\in Son_u} dps_{v,k-1}+dpc_{v,k-1}}{|Son_u|}$

$dpc_{u,k}=\frac{\sum \limits_{v\in Son_u} dpc_{v,k-1}}{|Son_u|}$


而对于副本点，我们有：

$dpsq_{u,k}=\frac{\sum \limits_{v\in Son_u} dpsq_{v,k-1}}{|Son_u|}$

$dps_{u,k}=\frac{\sum \limits_{v\in Son_u} dps_{v,k-1}}{|Son_u|}$

$dpc_{u,k}=\frac{\sum \limits_{v\in Son_u} (dpc_{v,k-1}+1)}{|Son_u|}$


最后的答案就是 $dpsq_{1,k}$ ，但是需要注意的是，如果第一个点是经验池，他并不会升级，因为升级和打副本只发生在随机走出边之后。这部分可以考虑把第一个点在 **刚开始的时候** 视为一个副本，反正是零级不会影响答案。不过后面的时候再经过要正常升级了。

### CODE

太难看了，而且定义写的很诡异，不贴了。感觉讲的还是不模糊的。



---

## 作者：liangbowen (赞：5)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc277_g)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17464231.html)

好题，记录一手拆贡献的 trick。

## 思路

我们需要维护一个 $x^2$ 的期望 $f(x^2)$，支持 $f(x^2) \to f\Big((x+1)^2\Big)$。

想到 P1654 的 trick，$(x+1)^2 = x^2 + 2x + 1$，只需维护 $x^2$、$x^1$、$x^0$ 的转移即可。

大力 DP 即可。设 $p0_{i,u}$，$p1_{i,u}$，$p2_{i,u}$ 分别是 $x^0$，$x^1$，$x^2$，走了 $i$ 步，现在在 $u$ 的期望值。

转移方程：$p_{i,u} = \sum\limits_{u\to v} \frac1{\text{degree}_v} \cdot p_{i-1,v}$（三个数组都是这样子）。

+ 当 $a_u = 0$ 时，$p2_{i,u} \gets 2 \cdot p1_{i,u} + p0_{i,u}$，$p1_{i,u} \gets p0_{i,u}$。
+ 当 $a_u = 1$ 时，答案即 $p2_{i,u}$。

统计所有 $a_u=1$ 时的答案即可。

## 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 3005, mod = 998244353;
struct Edge {int now, nxt;} e[N << 1];
int in[N], inv[N], head[N], cur;
void add(int u, int v)
{
	in[u]++;
	e[++cur].now = v, e[cur].nxt = head[u];
	head[u] = cur;
}
int a[N]; long long p0[N][N], p1[N][N], p2[N][N];
int qpow(int x, int y = mod - 2)
{
	int ans = 1;
	while (y)
	{
		if (y & 1) ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod;
		y >>= 1;
	}
	return ans;
}
int main()
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	while (m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), inv[i] = qpow(in[i]);
	
	int ans = 0;
	p0[0][1] = 1;
	for (int i = 1; i <= k; i++)
		for (int u = 1; u <= n; u++)
		{
			for (int _ = head[u]; _; _ = e[_].nxt)
			{
				int v = e[_].now;
				(p0[i][u] += p0[i - 1][v] * inv[v]) %= mod;
				(p1[i][u] += p1[i - 1][v] * inv[v]) %= mod;
				(p2[i][u] += p2[i - 1][v] * inv[v]) %= mod;
			}
			if (a[u]) ans = (ans + p2[i][u]) % mod;
			else
				(p2[i][u] += 2 * p1[i][u] + p0[i][u]) %= mod,
				(p1[i][u] += p0[i][u]) %= mod;
		}
	cout << ans;
	return 0;
}
```

希望能帮助到大家！

---

## 作者：DengDuck (赞：2)

拆贡献期望 DP 题，做法来自月落落落老师。

首先你要知道这题的这个平方不是可以直接算的，你考虑当前的期望等级相当于包含转移到它的许多状态，直接开方，这些状态会两两相乘，这是错的。

所以需要算期望“等级的平方值”（注意我的断句）。

首先为了方便统计总期望，我们把状态维护的期望设为概率乘上期望，然后把贡献下放到每一个状态，这样就可以直接加一个状态的贡献得到总期望。

我们设：

- $f_{i,j,0}$ 表示走了 $i$ 步，目前在 $j$ 这个点上的概率。
- $f_{i,j,1}$ 表示走了 $i$ 步，目前在 $j$ 这个点上的期望等级。
- $f_{i,j,2}$ 表示走了 $i$ 步，目前在 $j$ 这个点上的期望等级的平方。

转移可以利用公式 $(x+y)^2=x^2+2xy+y^2$，算出每一个状态给下一个状态的贡献，对于 $c_j=1$ 把贡献加入总答案即可。

时间复杂度为 $\mathcal O((n+m)k)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pb push_back
#define pLL pair<LL,LL>
#define fir first
#define sec second
using namespace std;
const LL N=3005;
const LL K=3;
const LL mod=998244353;
LL n,m,k,f[N][N][K],du[N],c[N],x[N*2],y[N*2],inv[N],ans;
LL ksm(LL x,LL y)
{
    LL ans=1;
    while(y)
    {
        if(y&1)ans=ans*x%mod;
        x=x*x%mod,y>>=1;
    }
    return ans;
}
void Add(LL &x,LL y)
{
    x=(x+y+mod)%mod;
}
vector<LL>v[N];
int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)
    {
        cin>>x[i]>>y[i];
        x[i+m]=y[i],y[i+m]=x[i];
        du[x[i]]++,du[y[i]]++;
    }
    for(int i=1;i<=m;i++)inv[i]=ksm(i,mod-2);
    for(int i=1;i<=n;i++)cin>>c[i];
    f[0][1][0]=1;
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=2*m;j++)
        {
            LL u=x[j],v=y[j];
            LL k=inv[du[u]];
            if(c[v]==0)
            {
                Add(f[i][v][0],f[i-1][u][0]*k%mod);
                Add(f[i][v][1],(f[i-1][u][0]+f[i-1][u][1])%mod*k%mod);
                Add(f[i][v][2],(f[i-1][u][0]+2*f[i-1][u][1]+f[i-1][u][2])%mod*k%mod);
            }
            if(c[v]==1)
            {
                Add(f[i][v][0],f[i-1][u][0]*k%mod);
                Add(f[i][v][1],f[i-1][u][1]*k%mod);
                Add(f[i][v][2],f[i-1][u][2]*k%mod);
            }
        }
        for(int u=1;u<=n;u++)
        {
            if(c[u])Add(ans,f[i][u][2]);
        }
    }
    printf("%lld",ans);
}
//RP++
```

---

## 作者：lfxxx (赞：2)

考虑倒着转移。

我们记录 $dp_{i,j,0/1/2}$ 分别表示从点 $i$ 出发走 $j$ 步，经过经过所有 $c_i = 1$ 的点时的 $X^2,X,1$ 的和的期望，加入一个新的 $c_i = 0$ 的点就按照 $\Delta X^2 = 2 \times X + 1$ 的方式更新即可。

时间复杂度 $O((n+m) \times k)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int maxn = 3114;
int dp[maxn][4];//x^2 x cnt
int f[maxn][4];
int type[maxn];
int d[maxn],n,m,k;
vector<int> E[maxn];
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
signed main(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    for(int i=1;i<=n;i++) cin>>type[i];
    for(int i=1;i<=n;i++) d[i]=qpow(E[i].size(),mod-2);
    for(int i=1;i<=k;i++){
        for(int u=1;u<=n;u++){
            for(int v:E[u]){
                if(type[v]==0){
                    f[u][1]=(f[u][1]+(dp[v][1]+2*dp[v][2]%mod+dp[v][3])%mod*d[u]%mod)%mod;
                    f[u][2]=(f[u][2]+(dp[v][2]+dp[v][3])%mod*d[u]%mod)%mod;
                    f[u][3]=(f[u][3]+dp[v][3]*d[u]%mod)%mod;
                }else{
                    f[u][1]=(f[u][1]+dp[v][1]*d[u]%mod)%mod;
                    f[u][2]=(f[u][2]+dp[v][2]*d[u]%mod)%mod;
                    f[u][3]=(f[u][3]+(dp[v][3]+1)*d[u]%mod)%mod;
                }
            }
        }
        for(int u=1;u<=n;u++){
            dp[u][1]=f[u][1],dp[u][2]=f[u][2],dp[u][3]=f[u][3];
            f[u][1]=f[u][2]=f[u][3]=0;
        }
    }
    cout<<dp[1][1]<<'\n';
    return 0;
}
```

---

## 作者：Qiaoqia (赞：2)

[可能更好的阅读体验](https://atcoder-for-chinese-developers.github.io/atcoder-for-chinese/index.html?page=Sabc277.abc277_g.twttwt)

一个显然的 $\Theta(n^3)$ 做法是对所有 $i, j, k$ 求走了 $i$ 次到达 $j$ 等级为 $k$ 的概率。状态数 $n^3$ 不行，考虑怎么把 $k$ 这一维去掉。 

设某个时刻到达某个点的等级为 $1$ 的概率为 $a$，等级为 $2$ 的概率为 $b$，以此类推，那么这个时刻这个点的贡献是 $a + 4b + 9c + \dots$，如果遇上了一个让其等级提升的点，则贡献变成了 $4 a + 9b + 16c + \dots$，再加上这个时刻走到这个点等级为 $0$ 的概率。  

贡献增加了 $3a + 5b + 7c + \dots$（因为 $(i + 1)^2 - i^2 = 2i + 1$），如果能维护这个东西就能维护贡献了。  

接着考虑等级提升时这个东西怎么变化，即增加了 $2(a + b + c + \dots)$。  
那么维护 $a + b + c + \dots, a + 3b + 5c + \dots, a + 4b + 9c + \dots$ 的值就行了。

```cpp
void main() {
    std::cin >> n >> m >> k;
    for (int i = 1, x, y; i <= m; i++) {
        std::cin >> x >> y;
        g[x].push_back(y), g[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) std::cin >> c[i];
    zro[0][1] = 1;
    for (int i = 1; i <= n; i++) ind[i] = Pow(g[i].size(), P - 2);
    for (int i = 1; i <= k; i++) 
        for (int u = 1; u <= n; u++)
            for (int v : g[u]) 
                if (c[u] || (i == 1 && u == 1)) 
                    add(zro[i][v], 1ll * zro[i - 1][u] * ind[u] % P);
    for (int i = 1; i <= k; i++) {
        for (int u = 1; u <= n; u++)
            for (int v : g[u]) {
                add(sm[i][v], 1ll * sm[i - 1][u] * ind[u] % P);
                add(ts[i][v], 1ll * ts[i - 1][u] * ind[u] % P);
                add(sq[i][v], 1ll * sq[i - 1][u] * ind[u] % P);
            }
        for (int j = 1; j <= n; j++)
            if (c[j]) add(ans, 1ll * sq[i][j] % P);
            else {
                add(ts[i][j], 2ll * sm[i][j] % P);
                add(ts[i][j], zro[i][j]);
                add(sq[i][j], ts[i][j]);
                add(sm[i][j], zro[i][j]);
            }
    }
    std::cout << ans;
}
```

---

## 作者：翼德天尊 (赞：0)

破防了破防了，彻底破防了，被自己弱智错误的多样性整的破大防。

周日模拟赛打过相似思路的题目。考虑倒序 dp，设 $dp_{i,j}$ 为**进行了第 $k-j+1$ 到第 $k$ 次行动**，且当前在节点 $i$ 时的答案期望。思考两种操作分别对于当前答案的贡献。

对于操作 $1$，我们会让之前的若干个 $x^2$ 变成 $(x+1)^2$，直接转移期望不好转移，由于 $(x+1)^2=x^2+2x+1$，于是考虑维护 $f_{i,j}$ 表示当前一次项的期望，$g_{i,j}$ 表示当前零次项的期望，依次转移，有转移方程：
$$dp_{u,i}=\frac{1}{deg_u}\sum_{v}(dp_{v,i-1}+2\times f_{v,i-1}+g_{v,i-1})$$
$$f_{u,i}=\frac{1}{deg_u}\sum_{v}f_{v,i-1}+g_{v,i-1}$$
$$g_{u,i}=\frac{1}{deg_u}\sum_{v}g_{v,i-1}$$
对于操作 $2$，我们相当于增加了一下 $0$ 次项，所以将 $0$ 次项加 $1$ 之后算期望即可。

初始对于每个节点 $i$ 将 $g_{i,1}=1$，时间复杂度 $O(nk)$。感觉类似这种【带有一个影响后续贡献计算的属性】的 dp 大多都可以倒序做，会简单许多。

赛后脑残用前缀积预处理优化求 inv 的过程，忘记将前缀积差分了，并且一点异常都没有发现，于是调了四五个小时+重构代码一次，彻底破防orz

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
const int N=3005;
const int M=6005;
const int mod=998244353;
int n,m,k,a[N],dp[N][N],dp2[N][N],in[N],jc[N],inv[N],dp3[N][N];
struct node{
	int to[M],next[M],tot,head[N];
	void adde(int u,int v){
		to[++tot]=v,next[tot]=head[u],head[u]=tot;
	}
}S;
ll read(){
	ll w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
int ksm(int x,int y){
	int ans=1;
	while (y){
		if (y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
void init(){
	inv[0]=jc[0]=1;
	for (int i=1;i<=n;i++) jc[i]=jc[i-1]*i%mod;
	inv[n]=ksm(jc[n],mod-2);
	for (int i=n-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
	for (int i=1;i<=n;i++)
		inv[i]=inv[i]*jc[i-1]%mod;
}
signed main(){
	n=read(),m=read(),k=read();
	init();
	for (int i=1;i<=m;i++){
		int u=read(),v=read();
		S.adde(u,v),S.adde(v,u);
		in[u]++,in[v]++;
	}
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1;i<=n;i++)
		if (a[i]==1) dp3[i][1]=1;
	for (int p=2;p<=k;p++){
		for (int u=1;u<=n;u++){
			for (int i=S.head[u];i;i=S.next[i]){
				int v=S.to[i];
				if (a[u]==1){
					dp[u][p]=(dp[u][p]+dp[v][p-1])%mod;	
					dp2[u][p]=(dp2[u][p]+dp2[v][p-1])%mod;	
					dp3[u][p]=(dp3[u][p]+dp3[v][p-1]+1)%mod;
				}else{			
					dp[u][p]=(dp[u][p]+dp[v][p-1]+2ll*dp2[v][p-1]+dp3[v][p-1])%mod;
					dp2[u][p]=(dp2[u][p]+dp2[v][p-1]+dp3[v][p-1])%mod;
					dp3[u][p]=(dp3[u][p]+dp3[v][p-1])%mod;
				}
			}
			dp[u][p]=dp[u][p]*inv[in[u]]%mod;
			dp2[u][p]=dp2[u][p]*inv[in[u]]%mod;
			dp3[u][p]=dp3[u][p]*inv[in[u]]%mod;
		}
	}
	int ans=0;
	for (int i=S.head[1];i;i=S.next[i]){
		int v=S.to[i];
		ans=(ans+dp[v][k])%mod;
	}
	cout<<ans*inv[in[1]]%mod<<'\n';
	return 0;
}
```

---

## 作者：tony0530 (赞：0)

发现 $N, M, K\le 3000$ 考虑动态规划。

先考虑暴力设 $f_{i,j,k}$ 为 $i$ 步走到 $j$ 等级为 $k$ 的概率。

发现时间复杂度为 $O(n^3)$ 显然不行，就可以考虑把 $k$ 这一维压缩掉。

发现 $(k + 1)^2 = k^2+2k+1$ ，所以可以把 $(k + 1)^2$ 拆成 $k^2 + 2 \times k ^1 + 1 \times k^0$ 完成转移。 

所以，我们设 $f_{i,j,0/1/2}$ 为 $i$ 步走到 $j$ 等级的 $0/1/2$ 次方期望，再用以上方法转移即可。

时间复杂度明显能过。

代码就不给予展示了，还蛮好写的。

---

