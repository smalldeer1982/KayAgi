# [ABC298E] Unfair Sugoroku

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc298/tasks/abc298_e

高橋君と青木君がすごろくをします。  
 高橋君ははじめ地点 $ A $、青木君ははじめ地点 $ B $ にいて、交互にサイコロを振ります。  
 高橋君が振るサイコロは $ 1,\ 2,\ \ldots,\ P $ の出目が一様ランダムに出るサイコロで、青木君が振るサイコロは $ 1,\ 2,\ \ldots,\ Q $ の出目が一様ランダムに出るサイコロです。  
 地点 $ x $ にいるときに自分の振ったサイコロの出目が $ i $ であるとき、地点 $ \min(x\ +\ i,\ N) $ に進みます。  
 地点 $ N $ に先に着いた人をすごろくの勝者とします。  
 高橋君が先にサイコロを振るとき、高橋君が勝つ確率を $ \text{mod\ }998244353 $ で求めてください。

 確率 $ \text{mod\ }998244353 $ とは この問題で求める確率は必ず有理数になることが証明できます。また、この問題の制約下では、求める確率を既約分数 $ \frac{y}{x} $ で表したときに $ x $ が $ 998244353 $ で割り切れないことが保証されます。  
 このとき $ xz\ \equiv\ y\ \pmod\ {998244353} $ を満たすような $ 0 $ 以上 $ 998244352 $ 以下の整数 $ z $ が一意に定まります。この $ z $ を答えてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ A,\ B\ <\ N $
- $ 1\ \leq\ P,\ Q\ \leq\ 10 $
- 入力はすべて整数
 
### Sample Explanation 1

高橋君が最初の手番で $ 2 $ あるいは $ 3 $ の出目を出すと、高橋君は地点 $ 4 $ に進んで高橋君が勝利します。 高橋君が最初の手番で $ 1 $ の出目を出すと、高橋君は地点 $ 3 $ に進み、青木君は次の手番で必ず地点 $ 4 $ に進んで青木君が勝利します。 よって、高橋君が勝つ確率は $ \frac{2}{3} $ です。

### Sample Explanation 2

サイコロの出目は常に $ 1 $ です。 このとき高橋君が地点 $ 5 $ に進み、次いで青木君が地点 $ 3 $ に進み、次いで高橋君が地点 $ 6 $ に進むので、高橋君は必ず勝ちます。

## 样例 #1

### 输入

```
4 2 3 3 2```

### 输出

```
665496236```

## 样例 #2

### 输入

```
6 4 2 1 1```

### 输出

```
1```

## 样例 #3

### 输入

```
100 1 1 10 10```

### 输出

```
264077814```

# 题解

## 作者：liangbowen (赞：10)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc298_e)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17342621.html)

题解区的代码都好丑啊，嘲讽。

## 思路

对于这种概率题，正常人都能反应到这是 dp。

所以：$dp_{t, i, j}$ 表示：当前是第 $t$ 回合，Tak 在 $i$ 位置，Aok 在 $j$ 位置，概率。

如果这样设状态的话，转移方程就会非常一眼（刷表）：

$$dp_{t, \min(i + \texttt{sti}, n), \min(j + \texttt{stj}, n)} \gets \dfrac{dp_{t - 1, i, j}}{pq}$$

其中 $\texttt{sti} \in \{1, 2, \cdots, p\}$，$\texttt{stj} \in \{1, 2, \cdots q\}$，表示两人的步数。

答案就是 $\sum\limits_{t=1}^n\sum\limits_{j=b}^n dp_{t, n, j}$，表示某一回合内 Tak 走到 $n$ 了，那必然算入答案内。

初始化 $dp_{0, a, b} = 1$。更多细节参考代码，注意分数用逆元实现。

## 闲话

时间复杂度 $O(n^2pq)$。

题解区写得没我好看的原因是，他们的复杂度是 $O(n^2(p+q))$ 吧，好像跑得比我快多了。

但是正常机子跑常数极小的 $10^8$ 级别运算，还是能轻松胜任的（？）所以就过了。不信的话，你拿样例三跑一跑！

## 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int mod = 998244353;
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
int dp[105][105][105]; //dp[t][i][j] : 第t回合，Tak在i位置，Aok在j位置，概率 
int main()
{
	int n, a, b, p, q, ans = 0;
	cin >> n >> a >> b >> p >> q;
	int inv = 1ll * qpow(p) * qpow(q) % mod;
	
	dp[0][a][b] = 1;
	for (int t = 1; t <= n; t++)
		for (int i = a; i < n; i++)
			for (int j = b; j < n; j++)
				for (int sti = 1; sti <= p; sti++)
					for (int stj = 1; stj <= q; stj++)
						dp[t][min(n, i + sti)][min(n, j + stj)] = (dp[t][min(n, i + sti)][min(n, j + stj)] + 1ll * inv * dp[t - 1][i][j] % mod) % mod;
	for (int t = 1; t <= n; t++)
			for (int j = b; j <= n; j++)
				ans = (ans + dp[t][n][j]) % mod;
	cout << ans;
	return 0;
}
```

希望能帮助到大家！

---

## 作者：_Ad_Astra_ (赞：9)

概率 $\text{dp}$。

考虑 $dp_{i,j}$ 表示第一个人到达 $i$，第二个人到达 $j$ 的概率。容易得知 $dp_{a,b} = 1$。那么更新的转移式也非常简单。我们可以枚举两个人掷骰子分别掷出的 $x$ 和 $y$，那么易得转移式 $dp_{\min\{n,i+x\},\min\{n,j+y\}}=dp_{\min\{n,i+x\},\min\{n,j+y\}}+dp_{i,j}\times\frac{1}{pq}$。

时间复杂度为 $O(n^2pq)$，可以通过此题。最后，转移一定要写成更新写法，否则会推的非常痛苦，并且容易 WA。

code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int n,a,b,p,q,dp[110][110],ans;
int quickpow(int x,int p)
{
    int base=x;
    int ans=1;
    while(p)
    {
        if(p&1)ans=ans*base%mod;
        p>>=1;
        base=base*base%mod;
    }
    return ans%mod;
}
signed main()
{
	cin>>n>>a>>b>>p>>q;
	dp[a][b]=1;
	for(int i=a;i<n;i++)
		for(int j=b;j<n;j++)
			for(int l1=1;l1<=p;l1++)
				for(int l2=1;l2<=q;l2++)
					dp[min(i+l1,n)][min(j+l2,n)]=(dp[min(i+l1,n)][min(j+l2,n)]+dp[i][j]*quickpow(p,mod-2)%mod*quickpow(q,mod-2)%mod)%mod;
	for(int i=1;i<=n;i++)ans=(ans+dp[n][i])%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：ForgotDream_CHN (赞：2)

# ATABC298E Unfair Sugoroku

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17322563.html)

![](https://s1.ax1x.com/2023/04/16/p993rtg.png)

（笑）

## 题意

有一个长为 $N$ 行的棋盘，两枚棋子初始时分别位于 $A$，$B$ 两个位置，分别记为 $a$ 与 $b$。两枚棋子分别对应两枚骰子，分别可以等概率的投掷出 $1 \sim P$ 与 $1 \sim Q$ 的点数，并将其对应的棋子移动到 $\min(N, i + X)$ 的位置上，其中 $i$ 是这枚棋子当前的位置，$X$ 是掷出的点数。率先到达 $N$ 的棋子获胜。

现在轮流移动这两枚棋子（$a$ 先动），问 $PA \bmod 998244353$ 的值是多少，其中 $PA$ 是 $a$ 获胜的概率。

$N \le 100; A, B \le N; P, Q \le 10$。

## 思路

我们先不考虑计算，直接写个搜索的框架来模拟游戏过程吧。

```cpp
void dfs(int dep = 1, int apos = a, int bpos = b) {
  if (dep & 1) {
    for (int i = 1; i <= p; i++) {
      if (apos + i >= n) {
        ...
      } else {
        dfs(dep + 1, apos + i, bpos);
      }
    }
  } else {
    for (int i = 1; i <= q; i++) {
      if (bpos + i >= n) {
        ...
      } else {
        dfs(dep + 1, apos, bpos + i);
      }
    }
  }

  return;
}
```

根据题意，这个搜索是很好写的。然后我们再来考虑计算。

题目中说对于搜索树中的每一个决策，也就是骰子掷出的点数，是等概率的，那么对于 $a$，投出每一个点数的概率就是 $\dfrac{1}{P}$，对于 $b$ 是同理的，为 $\dfrac{1}{Q}$。那么对于状态三元组 $(dep, cura, curb)$，其中 $dep$ 表示搜索树深度，$cura$ 表示 $a$ 当前位置，$curb$ 表示 $b$ 当前位置，我们很容易就可以写出一个式子：

$$
P(dep, cura, curb) = 
\begin{cases}
1 & cura \ge N \\
0 & curb \ge N \\
\sum_{i = 1}^{P}{\frac{P(dep + 1, cura + i, curb)}{P}} & dep \bmod2 = 1 \\
\sum_{i = 1}^{Q}{\frac{P(dep + 1, cura, curb + i)}{Q}} & dep \bmod 2 = 0
\end{cases}
$$

其中 $P(dep, cura, curb)$ 记为当前状态获胜的概率。

那么我们就可以在上边那个搜索框架的基础上，添加计算的部分。

```cpp
i64 dfs(int dep = 1, int apos = a, int bpos = b) {
  static const i64 MOD = 998244353;
  static const i64 invp = inv(p, MOD), invq = inv(q, MOD);
  
  i64 res = 0;

  if (dep & 1) {
    for (int i = 1; i <= p; i++) {
      if (apos + i >= n) {
        (res += invp) %= MOD;
      } else {
        (res += invp * dfs(dep + 1, apos + i, bpos) % MOD) %= MOD;
      }
    }
  } else {
    for (int i = 1; i <= q; i++) {
      if (bpos + i >= n) {
        continue;
      } else {
        (res += invq * dfs(dep + 1, apos, bpos + i) % MOD) %= MOD;
      }
    }
  }

  return res;
}
```

这样就做完了吗？当然没有，单纯地像这样爆搜的话，时间复杂度明显是指数级的，我们需要优化搜索的部分。

我们发现，上述搜索过程显然是满足无后效性的，因此我们可以通过记忆化来优化时间复杂度。

于是就有了下边的代码：

```cpp
i64 dfs(int dep = 1, int apos = a, int bpos = b) {
  static const i64 MOD = 998244353;
  static const i64 invp = inv(p, MOD), invq = inv(q, MOD);
  if (f[apos][bpos] != -1) {
    return f[apos][bpos];
  }
  
  i64 res = 0;

  ... // 省略搜索过程

  f[apos][bpos] = res;
  
  return res;
}
```

然后兴致冲冲地测第三个样例，发现错了。

难道是不能记忆化？当然不是，问题出在没有考虑好状态。我们发现，对于一个状态 $(cura, curb)$ ，其实是存在两种可能的，一种是当前为 $a$ 的回合，另一种是当前为 $b$ 的回合，所以记忆化数组还要多加一维，用于表示当前是谁先手，才可以避免状态混乱。

```cpp
i64 dfs(int dep = 1, int apos = a, int bpos = b) {
  static const i64 MOD = 998244353;
  static const i64 invp = inv(p, MOD), invq = inv(q, MOD);
  if (f[apos][bpos][dep & 1] != -1) {
    return f[apos][bpos][dep & 1];
  }
  
  i64 res = 0;

  ... // 省略搜索过程

  f[apos][bpos][dep & 1] = res;
  
  return res;
}
```

## 代码

```cpp
#include <bits/stdc++.h>

using i64 = long long;
using d80 = long double;

int n, a, b, p, q;
i64 all;
std::vector<std::vector<std::vector<i64>>> f;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  i64 d = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}

i64 inv(i64 num, i64 mod) {
  i64 x, y;
  exgcd(num, mod, x, y);
  return (x % mod + mod) % mod;
}

i64 dfs(int dep = 1, int apos = a, int bpos = b) {
  static const i64 MOD = 998244353;
  static const i64 invp = inv(p, MOD), invq = inv(q, MOD);
  if (f[apos][bpos][dep & 1] != -1) {
    return f[apos][bpos][dep & 1];
  }
  
  i64 res = 0;

  if (dep & 1) {
    for (int i = 1; i <= p; i++) {
      if (apos + i >= n) {
        (res += invp) %= MOD;
      } else {
        (res += invp * dfs(dep + 1, apos + i, bpos) % MOD) %= MOD;
      }
    }
  } else {
    for (int i = 1; i <= q; i++) {
      if (bpos + i >= n) {
        continue;
      } else {
        (res += invq * dfs(dep + 1, apos, bpos + i) % MOD) %= MOD;
      }
    }
  }

  f[apos][bpos][dep & 1] = res;
  
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  std::cin >> n >> a >> b >> p >> q;
  f.resize(n + 50, std::vector<std::vector<i64>>(n + 50, std::vector<i64>(2, -1)));

  std::cout << dfs() << "\n";

  return 0;
}
```

---

## 作者：六楼溜刘 (赞：2)

## 题意
- 小 A 和小 T 要玩一个骰子游戏，小 T 最初在 A 点，小 A 最初在 B 点。小 T 的骰子上每面的数字分别为 $1,2,3\dots P$，小 A 的骰子上每面的数字分别为 $1,2,3\dots Q$。
- 两人轮流扔骰子，我们认为骰子每一面等概率出现（冷知识，现实中骰子每面的概率不同），假如某人扔骰子前在 $x$ 点，扔骰子结果为 $i$ ，则移动到 $\min(x+i,N)$ 点，先到达点 $N$ 的获胜。
- 求先手小 T 获胜的概率。
- $2 \le N \le 100,1 \le A,B \le N,1 \le P,Q \le 10$

## 题解
概率/期望 DP 入门题，简单讲讲。

容易发现这个游戏不可能向后退，符合 DP 的“无后效性”原则。

设计 DP 状态，容易想到令 $dp_{i,j,1/0}$ 表示出现先手玩家在点 $i$，后手玩家在点 $j$，这一步轮到先手/后手走这种情况的概率。

接下来考虑转移方程（这里只说先手，后手一样的），显然，由于扔骰子的概率是一致的，故 $dp_{i,j,1}$ 可以等概率地转化到 $dp_{i+1,j,0},dp_{i+2,j,0}\dots dp_{i+P,j,0}$，使其的概率增加 $dp_{i,j,1}\times \frac{1}{p}$。

注意到题面中这句话：

> 移动到 $\min(x+i,N)$ 点。

所以这道题边界处理也非常简单，每次转移时将目标与 $N$ 取 $\min$ 就行了。

这道题初状态就更简单了，令 $dp_{A,B,1}$ 为 $1$ 即可。

答案即为 $\sum\limits_{i=b}^ndp_{n,i,0}$，由于先手胜前必定是先手走所以下一步（尽管这一步不存在）是后手走，故只用统计第三维为 $0$ 的情况

~~第一次赛时写出 E 结果 Unrated，QWQ。~~

## code
```cpp
#include<iostream>
#include<algorithm>
#include<string.h>
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#include<vector>
#define pbk(a) emplace_back(a) 
#define forup(i,s,e) for(ll i=(s);i<=(e);i++)
#define fordown(i,s,e) for(register ll i=(s);i>=(e);i--)
using namespace std;
#define gc getchar()
inline ll read(){//快读。
    ll x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const ll mod=998244353,N=105;
ll ksm(ll a,ll b){//快速幂用来算逆元。
    ll c=1;
    while(b){
        if(b&1) c=(c*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return c;
}
ll n,a,b,p,q;
ll dp[N][N][2];
signed main(){
    n=read();a=read();b=read();p=read();q=read();
    dp[a][b][1]=1;//初状态
    ll invp=ksm(p,mod-2),invq=ksm(q,mod-2);//提前算逆元只用算一次。
    forup(i,a,n-1){
        forup(j,b,n-1){
            forup(k,0,1){//枚举三维
                if(dp[i][j][k]==0) continue;
                if(k){
                    forup(num,1,p){
                        dp[min(i+num,n)][j][0]=(dp[min(i+num,n)][j][0]+dp[i][j][1]*invp%mod)%mod;
                    }
                }else{
                    forup(num,1,q){
                        dp[i][min(j+num,n)][1]=(dp[i][min(j+num,n)][1]+dp[i][j][0]*invq%mod)%mod;
                    }
                }//转移
            }
        }
    }
    int ans=0;
    forup(i,b,n){//注意统计答案要统计后手在所有可能点的情况。
        ans=(ans+dp[n][i][0])%mod;
  //由于先手赢必定是从先手走转移到后手走，只用统计不存在的下一步为后手走的情况。
    }
    printf("%lld",ans);
}
```


---

## 作者：yuhong056 (赞：1)

# 题解：AT_abc298_e [ABC298E] Unfair Sugoroku
怎么大家的时间复杂度都是 $O(n ^ 2 \times p \times q)$，那我就来一发源自官解的 $O(n ^ 2 \times (p + q))$ 时间复杂度的算法吧。
## 思路
一看到概率，我们就立刻想到概率 dp。而且这个数据范围也在故意暗示我们使用概率 dp。
## dp 状态
与其他题解不同，这里 $dp_{i, j, 0}$ 表示甲走到 $i$，乙走到 $j$，且接下来是甲走甲获胜的概率。

而 $dp_{i, j, 1}$ 表示甲走到 $i$，乙走到 $j$，且接下来是乙走甲获胜的概率。
## dp 初始化
很明显，当甲走到 $n$，乙只要没走到 $n$，就必然获胜。

因此，对于任意 $0 \le i < n$，$dp_{i, j, 0 / 1} = 1$。
## dp 转移
很明显，转移为：

$$dp_{i, j, 0} = \sum\limits_{st = 1} ^ p \frac{dp_{i + st, j, 1}}{p} = \frac{\sum\limits_{st = 1} ^ p dp_{i + st, j, 1}}{p}$$

$$dp_{i, j, 1} = \sum\limits_{st = 1} ^ q \frac{dp_{i, j + st, 0}}{q} = \frac{\sum\limits_{st = 1} ^ q dp_{i, j + st, 0}}{q}$$
## Code
```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MOD = 998244353, MAXN = 1e2 + 10;

ll dp[MAXN][MAXN][2];

ll qpow(ll a, int b = MOD - 2) { // 快速幂
	ll ans = 1;
	for(; b; b >>= 1) {
		if(b & 1)ans = ans * a % MOD;
		a = a * a % MOD;
	}
	return ans;
}

int n, a, b, p, q;

int main() {
	cin >> n >> a >> b >> p >> q;
	int pinv = qpow(p), qinv = qpow(q);
	for(int i = 0; i < n; i++){
		dp[n][i][0] = dp[n][i][1] = 1;
	}
	for(int i = n - 1; ~i; i--) {
		for(int j = n - 1; ~j; j--) {
			for(int st = 1; st <= p; st++) {
				(dp[i][j][0] += dp[min(n, i + st)][j][1]) %= MOD;
			}
			(dp[i][j][0] *= pinv) %= MOD;
			for(int st = 1; st <= q; st++) {
				(dp[i][j][1] += dp[i][min(n, j + st)][0]) %= MOD;
			}
			(dp[i][j][1] *= qinv) %= MOD;
		}
	}
	cout << dp[a][b][0] << '\n';
	return 0;
}

```

---

## 作者：a_small_penguin (赞：1)

概率 DP。

考虑扩散性 DP，定义 $f_{i,j,k}$ 为第一人到达 $i$，第二人到达 $j$，第 $k$ 个人走完。

那么明显，对于状态 $f_{i+r,j,1}(r \in \{x|1\le x \le p\})$ 一定能从状态 $f_{i,j,2}$ 以 $\frac{1}{p}$ 的概率走到。

同样的，对于状态 $f_{i,j + r,2}(r \in \{x|1\le x \le q\})$ 一定能从状态 $f_{i,j,1}$ 以 $\frac{1}{q}$ 的概率走到。

其中注意，因为位置是到 $\min(x + i, n)$，所以如果 $i + r\ge n$ 或 $j + r \ge n$ 那么就要将转移到 $f_{n,j,k}$ 或 $f_{i,n,k}$。

那么就可以以此写出 DP。

那么答案为 $\sum_{i = b}^{n - 1} f_{n,i,0}$。

code：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define mod 998244353

long long fast_pow(long long a, long long b, long long p) {
	long long ans = 1, base = a;
	while(b) {
		if(b & 1) 
			ans *= base, ans %= p;
		base *= base, base %= p, b >>= 1;
	}
	return ans;
}

int n, a, b, p, q;

long long dp[119][119][2];

int main() {

	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> a >> b >> p >> q;
	dp[a][b][1] = 1;
	for(int i = a; i < n; i++){
		for(int j = b; j < n; j++) {
			for(int k = 1; k <= p; k++)
				dp[min(i + k, n)][j][0] += dp[i][j][1] * fast_pow(p, mod - 2, mod), dp[min(i + k, n)][j][0] %= mod;
			for(int k = 1; k <= q; k++)
				dp[i][min(j + k, n)][1] += dp[i][j][0] * fast_pow(q, mod - 2, mod), dp[i][min(j + k, n)][1] %= mod;
		}
	}
	long long ans = 0;
	for(int i = b; i < n; i++) {
		ans += dp[n][i][0];
		ans %= mod;
	}
	cout << ans;

	return 0;

}
```

---

## 作者：JWRuixi (赞：1)

~~浪费时间，导致掉分……~~

- 题意

Takahashi 和 Aoki 在 $a$ 和 $b$ 点，两个人进行如下操作：
- 设 Takahashi 在 $x$，则她会随机在 $[1,P]$ 中选定一个 $i$，然后走到 $\min(x+i,n)$。
- 设 Aoki 在 $x$，则他会随机在 $[1,Q]$ 中选定一个 $i$，然后走到 $\min(x+i,n)$。

先到 $n$ 的人胜，问若 Takahashi 先手，Takahashi 赢的概率是多少？

- 分析

不好直接算，直接考虑 DP。

设 $f_{i,j}$ 表示 Takahashi 在第 $i$ 步恰好走到 $j$ 的概率是多少，$g_{i,j}$ 同理。转移很简单：
$$f_{i+1,j+k}\leftarrow \frac{f_{i,j}}{P},k\in[1,P]$$
$$g_{i+1,j+k}\leftarrow \frac{g_{i,j}}{Q},k\in[1,Q]$$

统计答案直接考虑枚举 Takahashi 在第 $i$ 步走到终点且在此前 Aoki 没走到的概率，形式化的 $\sum_{i=1}^nf_{i,n}\sum_{j=1}^{n-1}g_{i-1,j}$。每次至少走一步，所以最多走 $n$ 步，时间复杂度 $\mathcal O(n^2p)$。

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define LL long long
#define writesp(x) write(x), putchar(' ')
#define writeln(x) write(x), putchar('\n')
#define FileIO(ch) freopen(ch".in", "r", stdin), freopen(ch".out", "w", stdout)
using namespace std;

namespace IO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
#if ONLINE_JUDGE
#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
#else
#define gh() getchar()
#endif
    inline long long read() {
        char ch = gh();
        long long x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    template <typename _Tp>
    inline void write(_Tp x) {
    	static char stk[64], *top = stk;
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        do *top++ = x % 10, x /= 10;
        while (x);
        while (top != stk) putchar((*--top) | 48);  
    }
}

using IO::read;
using IO::write;

const int maxn(107), maxp(12), mod(998244353);
int n, p, q, a, b, ip, iq, f[maxn][maxn], g[maxn][maxn], ans;

inline int ksm (int b, int k) {
	int res = 1;
	for (; k; k >>= 1, b = (LL)b * b % mod) if (k & 1) res = (LL)res * b % mod;
	return res;
}

inline void add (int &x, const int &y) { x += y; x > mod && (x -= mod); }

int main() {
	n = read(), a = read(), b = read(), p = read(), q = read(), ip = ksm(p, mod - 2), iq = ksm(q, mod - 2);
	f[0][a] = 1, g[0][b] = 1;
	for (int i = 0; i <= n; i++) {
		for (int j = 1; j < n; j++)
			for (int k = 1; k <= p; k++)
				add(f[i + 1][min(j + k, n)], (LL)f[i][j] * ip % mod);
		for (int j = 1; j < n; j++)
			for (int k = 1; k <= q; k++)
				add(g[i + 1][min(j + k, n)], (LL)g[i][j] * iq % mod);
	}
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j < n; j++) 
			ans = (ans + (LL)f[i][n] * g[i - 1][j] % mod) % mod;
	write(ans);
}
// I love WHQ!
```

---

## 作者：Unnamed114514 (赞：1)

概率 dp。

设 `dfs(x,y)` 表示第一个人得分为 $x$，第二个人得分为 $y$ 的概率。

首先来考虑边界条件：若 $x=n$，则第一个人赢；若 $y=n$，则第二个人赢，注意第二个人比第一个人先操作。

那么此时我们枚举这两个人分别选了什么，我们假设他们选的 $a,b$，那么我们接下来变成的状态就是 `dfs(min(x+a,n),min(y+b,n))`，然后这个情况的概率，就是 $\dfrac{1}{pq}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,a,b,p,q,dp[105][105];
inline int qpow(int a,int b){
	int s=1;
	while(b){
		if(b&1)
			s=s*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return s;
}
int dfs(int x,int y){
	if(x==n)
		return 1;
	if(y==n)
		return 0;
	if(~dp[x][y])
		return dp[x][y];
	int res=0;
	for(int i=1;i<=p;++i)
		for(int j=1;j<=q;++j)
			res=(res+dfs(min(x+i,n),min(y+j,n))*qpow(p*q%mod,mod-2)%mod)%mod;
	return dp[x][y]=res;	
}
signed main(){
	cin>>n>>a>>b>>p>>q;
	memset(dp,-1,sizeof(dp));
	cout<<dfs(a,b)<<endl;
	return 0;
}
```

---

## 作者：ダ月 (赞：1)

### 题意概要：

两个人（分别记甲和乙）手上分别有初始值 $A$ 和 $B$。

甲有个骰子，等概率从 $1\sim P$ 中出现一个数，让甲当前值加上出现的数。乙同理，不过是等概率从 $1\sim Q$ 中出现一个数。

当前的数先大于等于 $n$ 的人胜利。甲先甩，甲乙轮流。问甲获胜的几率。答案对 $998244353$ 取模。

### 题目分析：

有个直观的感受，就是用动态规划。

由于有三个要记录的东西，分别为甲当前拥有的数，乙当前拥有的数，和当前是谁操作。所以记 $f_{i,j,k}$，分别对应，其中若 $k=0$，说明是甲操作；若是 $1$，说明是乙操作。

转移类似背包，可以得到以下转移：

$\begin{aligned}f_{i,j,0}=\frac{1}{P}\sum_{p=1}^Pf_{\min\{n,i+p\},j,1}\end{aligned}$

$\begin{aligned}f_{i,j,1}=\frac{1}{Q}\sum_{q=1}^Qf_{i,\min\{j+q\},0}\end{aligned}$

倒序转移。

其中为了让甲胜利，我们设置边界调节 $f_{n,i,1}=1,f_{n,i,0}=1(i\in[0,n))$。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;
ll QP(ll x,ll y,ll mod){ll ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ans=ans*x%mod;return ans;}
namespace IO{
	void WL(int x){Output(x);putchar('\n');}
}
ll f[110][110][2];
int n,a,b,p,q;
const int mod=998244353;
ll inv(ll x){return QP(x,mod-2,mod);}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>a>>b>>p>>q;
	for(int i=0;i<n;i++)
		f[n][i][0]=f[n][i][1]=1;
	for(int i=n-1;~i;i--)
		for(int j=n-1;~j;j--){
			for(int k=1;k<=p;k++)
				f[i][j][0]=(f[min(n,i+k)][j][1]+f[i][j][0])%mod;
			for(int k=1;k<=q;k++)
				f[i][j][1]=(f[i][min(n,j+k)][0]+f[i][j][1])%mod;
			f[i][j][0]=f[i][j][0]*inv(p)%mod;
			f[i][j][1]=f[i][j][1]*inv(q)%mod;
		}
	IO::WL(f[a][b][0]);
	return 0;
}






```


---

## 作者：mondayrain (赞：0)

# AT_abc298_e [ABC298E] Unfair Sugoroku 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc298_e)

考虑概率 dp。

### 1. 状态

$dp_{i , j , k}$ 表示第 $i$ 轮高桥走到第 $j$ 个格子，青木走到第 $k$ 个格子的概率。

### 2. 转移

这题其实扩散型 dp 更好写，先判断这轮是轮到谁了，再枚举那个人投到了多少，然后转移。

注意要乘以 $\frac{1}{p}$ 或 $\frac{1}{q}$，用逆元实现，也就是 $p ^ {(mod - 2)}$ 和 $q ^ {(mod - 2)}$。

### 3. 答案

最多可能有 $2n$ 轮，枚举所有高桥到 $n$ 且青木没到 $n$ 的所有状态，求和。

### 4. 初始化

刚开始高桥在 $a$，青木在 $b$，所以 $dp_{0 , a , b} = 1$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 998244353;
int n , p , q , a , b , dp[205][105][105];
int qpow(int a , int b , int mod)
{
	int ans = 1;
	while(b)
	{
		if(b & 1)
		{
			ans *= a;
			ans %= mod;
		}
		a *= a;
		a %= mod;
		b /= 2;
	}
	return ans;
}
int inv(int x , int y)
{
	return (x * qpow(y , mod - 2 , mod)) % mod;
}
signed main()
{
	cin >> n >> a >> b >> p >> q;
	dp[0][a][b] = 1;
	int qq , pp;
	qq = inv(1 , q);
	pp = inv(1 , p);
	for(int i = 0;i <= 2 * n;i ++)     //注意范围。
	{
		for(int j = a;j < n;j ++)
		{
			for(int k = b;k < n;k ++)
			{
				if(i % 2 == 0)
				{
					for(int u = 1;u <= p;u ++)
					{
						(dp[i + 1][min(j + u , n)][k] += dp[i][j][k] * pp % mod) %= mod;
					}
				}
				else
				{
					for(int u = 1;u <= q;u ++)
					{
						(dp[i + 1][j][min(k + u , n)] += dp[i][j][k] * qq % mod) %= mod;
					}
				}
			}
		}
	}
	int ans = 0;
	for(int i = 0;i <= 2 * n;i ++)
	{
		for(int j = 1;j < n;j ++)   //不能枚举到 n。
		{
			ans += dp[i][n][j];
			ans %= mod;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Ascnbeta (赞：0)

## [ABC298E] Unfair Sugoroku

因为两个人的数字不会在中途变得更少，无后效性，结合 $1\le N\le100$ 的数据范围，很容易想到概率 dp。

发现题解好像大多数都是顺推，即由当前状态推到其他状态，我就写一个从其他状态转移至当前状态的状态转移方程吧。

我们设 $f_{cnt,i,j}$ 为进行完第 $cnt$ 回合后，第一个人数字为 $i$，第二个人数字为 $j$ 的概率。

考虑如何转移而来，显然 $i,j$ 可以从 $i-p\sim i-1,j-q\sim j-1$  中每一个组合的概率推来，而两颗骰子扔出其中任意一个组合的概率为 $\dfrac{1}{pq}$，所以不考虑边界问题的话，状态转移方程方程可以写为：
$$
f_{cnt,i,j}\gets\dfrac{1}{pq}\sum_{k=1}^{p}\sum_{l=1}^{q}f_{cnt-1,i-k,j-l}
$$
相当于从上一轮可行的 $(i,j)$ 组合中转来，而这样也相当于指定了两颗骰子分别扔出什么数，自然这种情况的概率是 $\dfrac{1}{pq}$。

然而这样就做完了吗？当然不只是这么简单，只要第一个人的数字超过 $n$ 就可以算他赢，所以我们不能只把 $i,j$ 枚举到 $n$，而是把 $i$ 枚举到 $n+p-1$，把 $j$ 枚举到 $n+q-1$。因为在两个数都小于 $n$ 的情况下，下一轮扔出的数字肯定不会超过上述两个数。

但是注意我们在算 $i,j$ 有一个数超过 $n$ 时的概率时，注意游戏一旦有一方超过 $n$ 就结束了，所以上式中 $i-k,j-l$ 均不应当超过 $n$。

最终状态转移方程为：
$$
f_{cnt,i,j}\gets\dfrac{1}{pq}\sum_{k=i-p}^{\min(i-1,n)}\sum_{l=j-q}^{\min(j-1,n)}f_{cnt-1,k,l}
$$
初始化显然为 $f_{0,a,b}=1$，答案即为：
$$
ans=\sum_{cnt=1}^{n}\sum_{i=n}^{n+p-1}\sum_{j=1}^{n+q-1}f_{cnt,i,j}
$$
由于本题有取模，所以需要先用费马小算出 $pq$ 的逆元，在这里不再赘述。最终时间复杂度 $\mathcal{O(n^3pq)}$，本题数据范围下约为 $10^8$ 量级，可以通过。

## AC Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353;
inline int binpow(int base,int b) {
    int ret = 1;
    while (b) {
        if (b&1) ret = ret * base % mod;
        base = base * base % mod;
        b >>= 1;
    }
    return ret % mod;
}
int n,a,b,p,q,ans;

int f[160][150][150];
signed main() {
#ifdef LOCAL
    freopen("D:/codes/exe/a.in","r",stdin);
    freopen("D:/codes/exe/a.out","w",stdout);
#endif
    cin >> n >> a >> b >> p >> q;
    const int ni = binpow(p*q,mod-2);//求逆元
    f[0][a][b] = 1;
    for (int cnt = 1; cnt <= n; cnt++) {
        for (int i = a; i < n+p; i++) {
            for (int j = b; j < n+q; j++) {
                for (int k = 1; k <= min(i,p); k++) {//注意枚举上界
                    for (int l = 1; l <= min(j,q); l++) {
                        if (i-k < n && j-l < n) {//注意不要超过n
                            f[cnt][i][j] = (f[cnt][i][j]+f[cnt-1][i-k][j-l]*ni%mod)%mod;//这里的转移方程是后者与前者的结合，所以写成了这样
                        }
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = n; j < n+p; j++) {
            for (int k = 1; k < n+q; k++) ans = (ans+f[i][j][k])%mod;
        }
    }
    cout << (ans+mod)%mod << '\n';//防止出现负数
    return 0;

}
```

## Others

为什么可以统计 $i,j$ 都大于等于 $n$ 的答案呢？由于题面告诉我们保证第一个人先扔，在我们的状态转移方程下，如果 $i,j$ 都大于等于 $n$，则第一个人一定先大于等于 $n$，相当于是他赢了之后第二个人又扔了一次才也大于等于 $n$。

---

## 作者：CarroT5656 (赞：0)

**题目大意**

甲和乙分别有两个数 $A$ 和 $B$。

每次，甲可以将 $A$ 等概率增加 $1\sim p$ 中的每个数。乙可以将 $B$ 等概率增加 $1\sim q$ 中的每个数。

甲和乙轮流操作。甲先开始操作。

问 $A$ 先大于等于 $n$ 的概率。答案对 $998244353$ 取模。

**解题思路**

显然是个 dp，定义 dp 转移状态。

* $dp_{i,j,0/1}$ 表示 $A$ 现在的值为 $i$，$B$ 为 $j$，轮到甲/乙操作的概率。

* $dp_{i,j,0}=\frac{1}{p}\times \sum\limits_{k=1}^pdp_{i+k,j,1}$

* $dp_{i,j,1}=\frac{1}{q}\times \sum\limits_{k=1}^qdp_{i,j+k,0}$

可以预处理出 $\frac{1}{p}$ 和 $\frac{1}{q}$。

倒推该 dp 即可。答案为 $dp_{a,b,0}$。

时间复杂度 $O(n^2pq)$ 可以通过。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 998244353
#define N 155
ll n,a,b,p,q,f[N],dp[N][N][2];
ll qpow(ll a,ll b){
	ll ans=1,base=a;
	while(b){
		if(b&1) ans=(ans*base)%mod;
		base=(base*base)%mod;
		b>>=1;
	}
	return ans;
}
int main(){
	scanf("%lld%lld%lld%lld%lld",&n,&a,&b,&p,&q);
	for(ll i=1;i<=p+q;i++) f[i]=qpow(i,mod-2);
	for(ll i=n;i<=n+p-1;i++) for(ll j=1;j<n;j++) dp[i][j][0]=dp[i][j][1]=1;
	for(ll i=n;i<=n+q-1;i++) for(ll j=1;j<n;j++) dp[j][i][0]=dp[j][i][1]=0;
	for(ll i=n-1;i>0;i--) for(ll j=n-1;j>0;j--){
		for(ll k=1;k<=p;k++) dp[i][j][0]+=dp[i+k][j][1];
		for(ll l=1;l<=q;l++) dp[i][j][1]+=dp[i][j+l][0];
		dp[i][j][1]=dp[i][j][1]*f[q]%mod,dp[i][j][0]=dp[i][j][0]*f[p]%mod;
	}
	printf("%lld\n",dp[a][b][0]);
	return 0;
}
```

---

## 作者：2huk (赞：0)

## 前置

本题考察 [概率 $\text {dp}$](https://oi-wiki.org/dp/probability/)。

## 状态和答案

有两个人，且当前谁要下棋都是为止的，所以我们设三维状态 $f_{i, j, 0/1}$，表示当前先手在 $i$ 点，后手在 $j$ 点，且下一步该先手/后手走的先手获胜概率。

显然我们要倒着推出所有的值。因此答案为 $f_{A, B, 1}$，表示先手在 $A$ 点，后手在 $B$ 点，且下一步（也就是第一步）要先手走的获胜概率。

## 边界

如果当前先手在 $N$ 点，且下一步要后手走，那么显然此时先手已经赢了。所以 $f_{N, i, 1} = 1, \in [1, N]$。

如果当前先手在 $N$ 点，且下一步要先手走，那么显然这样的情况是不存在的。所以 $f_{N, i, 0} = 0, \in [1, N]$。

## 转移

先手走或后手走的转移类似，这里讨论先手的转移过程，也就是 $f_{i, j, 0}$。

题目中规定走的步数的概率是相同的，也就是 $\dfrac 1P$，那么我们可以考虑当前点 $i$ 是从那些点转移过来的。

![p9kuC5D.png](https://s1.ax1x.com/2023/04/20/p9kuC5D.png)

如图，假设当前棋子在 $i$ 点，那么它下一步可以跳到 $i+1,\ i+2\ \dots\ i+P$ 点上。由于概率相同，每一个点的概率都要乘 $\dfrac 1P$。而先手走完这一点后该后手走，所以得到动态转移方程：

$$
f_{i, j, 1} = \dfrac{\sum_{k=1}^P f_{\min(i + P, N), j, 0}}P
$$

按照同样的思路，后手的动态转移方程为：

$$
f_{i, j, 0} = \dfrac{\sum_{k=1}^Q f_{i, \min(j+Q, N), 1}}Q
$$

## 代码

```cpp
#include <iostream>

using namespace std;

#define int long long

const int N = 110, P = 998244353;

int n, a, b, p, q;
int f[N][N][2];		// f[..][..][0] 表示下一步 Takahashi 走，f[..][..][1] 表示下一步 Aoki 走 

int add(int a, int b)			// (a + b) % P 的值 
{
	return ((a % P) + (b % P)) % P;
}

int mul(int a, int b)			// (a * b) % P 的值 
{
	return ((a % P) * (b % P)) % P;
}

int fpm(int a, int b)		// 求逆元用到了快速幂 
{
	int res = 1;
	while (b)
	{
		if (b & 1) res = mul(res, a);
		b >>= 1, a = mul(a, a);
	}
	return res;
}

signed main()
{
	// 读入 
	cin >> n >> a >> b >> p >> q;
	
	// 边界 
	for (int i = 1; i <= n; i ++ ) f[n][i][1] = 1;
	
	for (int i = n - 1; i >= a; i -- )		// 倒序 
		for (int j = n - 1; j >= b; j -- )	// 倒序 
		{
			// 转移 
			for (int k = 1; k <= p; k ++ )
				f[i][j][0] = add(f[i][j][0], f[min(n, i + k)][j][1]);
			
			for (int k = 1; k <= q; k ++ )
				f[i][j][1] = add(f[i][j][1], f[i][min(n, j + k)][0]);
			
			f[i][j][0] = mul(f[i][j][0], fpm(p, P - 2));		// 除以 P 
			f[i][j][1] = mul(f[i][j][1], fpm(q, P - 2));		// 除以 q 
		}
	
	// 答案为先手在 A 点，后手在 B 点，且下一步（也就是第一步）要先手走的获胜概率
	cout << f[a][b][0];
	
	return 0;
}
```


---

