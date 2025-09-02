# [ABC275E] Sugoroku 4

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc275/tasks/abc275_e

高橋君は双六で遊んでいます。

この双六には $ 0 $ から $ N $ の番号がついた $ N+1 $ 個のマスがあります。 高橋君はマス $ 0 $ からスタートし、マス $ N $ を目指します。

この双六では、$ 1 $ から $ M $ までの $ M $ 種類の目が等確率で出るルーレットを使います。 高橋君はルーレットを回して出た目の数だけ進みます。もし、マス $ N $ を超えて進むことになる場合、マス $ N $ を超えた分だけ引き返します。

例えば、 $ N=4 $ で高橋君がマス $ 3 $ にいるとき、ルーレットを回して出た目が $ 4 $ の場合は、マス $ 4 $ を $ 3+4-4=3 $ マス超えてしまいます。そのため、 $ 3 $ マスだけマス $ 4 $ から引き返し、マス $ 1 $ に移動します。

高橋君がマス $ N $ に到達するとゴールとなり、双六を終了します。

高橋君がルーレットを $ K $ 回まで回す時、ゴールできる確率を $ \text{mod\ }\ 998244353 $ で求めてください。

 確率 $ \text{mod\ }\ 998244353 $ の定義この問題で求める確率は必ず有理数になることが証明できます。 また、この問題の制約下では、求める確率を既約分数 $ \frac{y}{x} $ で表したときに $ x $ が $ 998244353 $ で割り切れないことが保証されます。

このとき $ xz\ \equiv\ y\ \pmod{998244353} $ を満たすような $ 0 $ 以上 $ 998244352 $ 以下の整数 $ z $ が一意に定まります。この $ z $ を答えてください。

## 说明/提示

### 制約

- $ M\ \leq\ N\ \leq\ 1000 $
- $ 1\ \leq\ M\ \leq\ 10 $
- $ 1\ \leq\ K\ \leq\ 1000 $
- 入力は全て整数

### Sample Explanation 1

$ 1 $ 回ルーレットを回してゴールできるのは、ルーレットで $ 2 $ が出るときです。よってゴールできる確率は $ \frac{1}{2} $ です。 このとき、$ 2\times\ 499122177\ \equiv\ 1\ \pmod{998244353} $ が成り立つので、答えとして $ 499122177 $ を出力してください。

## 样例 #1

### 输入

```
2 2 1```

### 输出

```
499122177```

## 样例 #2

### 输入

```
10 5 6```

### 输出

```
184124175```

## 样例 #3

### 输入

```
100 1 99```

### 输出

```
0```

# 题解

## 作者：_dijkstra_ (赞：7)

某人曾经说过，如果 ABC 的 E 或者 F 题考概率或期望，那么 $100\%$ 是 DP。

## 思路

设 $dp_{i, x}$ 表示当前是第 $i$ 次操作，当前所在的节点是 $x$，到达的概率。

发现填表法较为困难，于是考虑刷表法。对于当前点 $x$ 来说，假设步数是 $step$，那么走完后的 $dx$ 就有两种情况：

1. 如果 $x + step \le n$， 那么 $dx = x + step$。
2. 否则说明它会有一个回头的动作。所以 $dx = 2 \times n - x - step$，原因见下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/vh0q1kyg.png)
    
所以 $dp_{i - 1, dx} = \dfrac{dp_{i, j}}{m}$（每一个 $step$ 刚好抽到的概率都是 $\dfrac{1}{m}$）。答案就是所有 $dp_{i, n}$ 的和。

## 代码

众所周知，除法用逆元代替。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 1005, mod = 998244353;
int qpow(int x, int y = mod - 2)
{
    int ans = 1;
    while (y)
    {
        if (y & 1) ans = (1ll * ans * x) % mod;
        x = (1ll * x * x) % mod;
        y >>= 1;
    }
    return ans;
}
int dp[N][N]; //dp[i][x] : 前i轮，当前节点为x，概率
int main()
{
    int n, m, k;
    cin >> n >> m >> k; int inv = qpow(m);

    dp[0][0] = 1;
    for (int i = 1; i <= k; i++)
        for (int x = 0, dx; x < n; x++) //注意只能枚举到n-1
            for (int step = 1; step <= m; step++)
            {
                if (x + step <= n) dx = x + step; else dx = 2 * n - x - step;
                dp[i][dx] = (dp[i][dx] + 1ll * inv * dp[i - 1][x]) % mod;
            }
    int ans = 0;
    for (int i = 1; i <= k; i++) ans = (ans + dp[i][n]) % mod;
    cout << ans;
    return 0;
}
```

---

## 作者：FFTotoro (赞：6)

## 前言

这题生动地展现了飞行棋最后几步的经典画面，赛时瞎搞居然搞出来了。~~同学严重怀疑出题人飞行棋输多了才想到的这一题~~

## 解法

本题需要使用动态规划算法。

我们令 $f_{i,j}$ 为第 $i$ 轮转转盘的时候，走到格子 $j$ 的概率（易得边界条件 $f_{0,0}=1$）；令 $s(x,y)$ 为从 $x$ 格子开始，转盘转到了 $y$ 后走到的格子，根据游戏规则有：

$s(x,y)=\begin{cases}2n-x-y&x+y>n\\x+y &\operatorname{otherwise}\end{cases}$

因为转盘转到 $1$ 至 $M$ 的概率相同，所以易得：

$f_{i,s(j,r)}(0\le j<N,1\le r\le M)$ 就可以由 $f_{i-1,j}$ 推导而来，根据**两个独立事件同时发生的概率为两个事件发生的概率的乘积**，前者的值就是若干个 $\frac{f_{i-1,j}}{M}$ 的值的和。具体地，我们枚举每一个 $j$ 和 $r$ 即可解决问题。

除法时用乘法逆元求解即可，最终答案即为 $\sum\limits_{i=1}^Kf_{i,N}$。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p=998244353;
int n,f[1001][1001];
int qpow(int a,int b){
  int r=1;
  while(b){
    if(b&1)r=r%p*a%p;
    a=a%p*a%p; b>>=1;
  }
  return r;
}
int inv(int a,int b){
  return a*qpow(b,p-2)%p;
} // 逆元
int s(int x,int y){
  return x+y>n?(n<<1ll)-x-y:x+y;
} // 判断 x 走 y 步后会到哪
main(){
  ios::sync_with_stdio(false);
  int m,k,c=0; cin>>n>>m>>k; f[0][0]=1; // 初始化
  for(int i=1;i<=k;i++){
    for(int j=0;j<n;j++)
      for(int r=1;r<=m;r++)
        (f[i][s(j,r)]+=inv(f[i-1][j],m))%=p; // 状态转移
    (c+=f[i][n])%=p; // 求和
  }
  cout<<c<<endl;
  return 0;
}
```

---

## 作者：wnsyou (赞：1)

# [Sugoroku 4](https://www.luogu.com.cn/problem/AT_abc275_e)
[前排兜售我的博客园。](https://www.cnblogs.com/lw0-blog/p/17446532.html)
## 题意
有一行格子，编号为 $0, 1, \cdots n$，你站在 $0$ 号格子上。

你手上有一个转盘，转盘上写有数字 $1 \sim m$，每次转转盘后显示的数值是等概率出现的。

假设某次转转盘后转盘显示的数值为 $x$，你会行走 $x$ 步，当你走到第 $n + 1$ 个格子时，你会回头行走剩余步数，**形同飞行棋的最后几步。**

当你在某次走完后恰好停在第 $n + 1$ 个格子上时游戏结束，你最多转 $k$ 次转盘，问胜利的概率对 $998244353$ 取模的结果。

## 思路
一个明显的概率 dp。

提到等概率和取模，不难想到[费马小定理](https://baike.baidu.com/item/%E8%B4%B9%E9%A9%AC%E5%B0%8F%E5%AE%9A%E7%90%86/4776158)，转盘上显示某个数的概率为 $\frac{1}{m}$，根据费马小定理可得 $\frac{1}{m} \equiv \frac{1}{m} \times m ^ {998244353 - 1} \equiv m ^ {998244353 - 2} \equiv m ^{998244351} \pmod{998244353}$，可以用快速幂求，下面用 $qp$ 表示。

定义 $F_{i,j}$ 表示 $i$ 是否可以转一次转盘走到 $j$，如果是则为 $1$，否则为 $0$。

- 状态：$dp_{i, j}$ 表示转了 $i$ 次转盘走到编号为 $j$ 的格子的概率。
- 转移：$dp_{i, j} = \sum\limits_{0 \leqslant k < n} F_{k, i} \times dp_{i - 1, k} \times qp$，你也可以思考一下扩散性转移。
- 初始状态：$dp_{0, 0} = 1$。
- 目标状态：$\sum\limits_{1 \leqslant i \leqslant k} dp_{i, n}$。

注意取模和乘法爆 int 的细节即可。
### 复杂度

- 时间：$O(n \times m \times k)$。
- 空间：$O(n \times k)$。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int mod = 998244353, N = 1e3 + 10;

int n, m, k;
ll qp, dp[N][N], ans;

ll qmod (ll a, int b) { // 快速幂求 qp
  ll ans = 1;
  while (b) {
    if (b & 1) {
      ans = (ans * a) % mod;
    }
    a = (a * a) % mod, b >>= 1;
  }
  return ans;
}

int Q (int x, int t) { // 求按规则从 x 往后走 t 步会走到的格子的编号
  if (x + t <= n) { // 不用回头
    return x + t;
  }
  return 2 * n - t - x; // 回头
}

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> k;
  qp = qmod(m, mod - 2), dp[0][0] = 1;
  for (int i = 0; i < k; i++) { // 扩散形转移好写
    for (int j = 0; j < n; j++) {
      for (int l = 1; l <= m; l++) { // 枚举走多少步
        dp[i + 1][Q(j, l)] = (dp[i + 1][Q(j, l)] + dp[i][j] * qp) % mod; // 取模!
      }
    }
  }
  for (int i = 1; i <= k; i++) {
    ans = (ans + dp[i][n]) % mod;
  }
  cout << ans;
  return 0;
}
```

---

## 作者：allenchoi (赞：1)

### 科技：  
逆元，概率 DP 
### 思路：  
设 $dp_{i,j}$ 为在第 $j$ 步走到 $i$ 号格子的概率。  
考虑转移：  
走到一个格子有两种可能，一是从后面直接走过来，二是走到 $n$ 后后退。  
走到 $n$ 再倒退到 $i$ 的格子可以在 $[n-(m-(n-i)),n-1]$  
所以：  
$dp_{i,j}=\sum_{k=i-m}^{k-1}\frac{1}{m}dp_{k,j-1}+\sum_{k=2n-m-i}^{n-1}\frac{1}{m}dp_{k,j}$  
注意处理一下边界。  
### 代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int n,m,K,inv,s,dp[1010][1010];
int ksm(int x,int y)
{
	int ret = 1;
	while(y)
	{
		if(y & 1) ret = 1LL * ret * x % mod;
		x = 1LL * x * x % mod;
		y >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%d%d%d",&n,&m,&K);
	dp[0][0] = 1,inv = ksm(m,mod - 2);
	for(int j = 1;j <= K;j++)
	{
		for(int i = 0;i < n;i++)
		{
			for(int t = max(0,i - m);t < i;t++) dp[i][j] = (dp[i][j] + 1LL * dp[t][j - 1] * inv % mod) % mod;
			for(int t = n - 1;t >= 2 * n - m - i;t--) dp[i][j] = (dp[i][j] + 1LL * dp[t][j - 1] * inv % mod) % mod;
		}
		for(int t = max(0,n - m);t <= n - 1;t++) dp[n][j] = (dp[n][j] + 1LL * dp[t][j - 1] * inv % mod) % mod;
		s = (s + dp[n][j]) % mod;
	}
	printf("%d\n",s);
	return 0;
}
```

---

