# ボール

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tdpc/tasks/tdpc_ball

入力は以下の形式で標準入力から与えられる。

> $ N $ $ x_1\ ...\ x_N $

 答えを一行に出力せよ。絶対誤差が $ 10^{-6} $ 以下のとき正当と判定される。 ```

2
0 2
```

```

4.500000000
```

```

5
1 3 4 2 5
```

```

8.986111111
```

## 说明/提示

### Constraints

 $ N $ 個のものがある。$ i $ 番目のものは座標 $ x_i $ におかれている。すぬけ君が、座標 $ x $ の点を目指してボールを投げると $ x-1,\ x,\ x+1 $ のうちのいずれかに 1/3 ずつの確率で飛んでいき、そこに物がおいてあった場合は倒れる。最適な戦略でボールを投げたとき、すべての物を倒すのに必要なボールを投げる回数の期待値を求めよ。   
 追記 : **ボールを投げる場所は、前に投げたボールの飛んだ場所を見た後に決めることができる。**

- - - - - -

- $ 1\ <\ =\ N\ <\ =\ 16 $
- $ 0\ <\ =\ x_i\ <\ =\ 15 $
- $ x_i $ are pairwise distinct.

# 题解

## 作者：ttttalk (赞：8)

## [ボール](https://www.luogu.com.cn/problem/AT_tdpc_ball)

前置知识：状压 dp，数学期望。

## Solution

数学期望，通常用 $E$ 表示。很显然 $E_0$ 的场合不需要任何操作，即为 $0$。

考虑一个。

扔一次，就有 $1$ 的初始值。只有 $\dfrac{1}{3}$ 的概率击中这一个，$\dfrac{1}{3}$的击中左边，$\dfrac{1}{3}$ 击中右边。

有：

$$E_1=1+\dfrac{1}{3}E_0+\dfrac{2}{3}E_1$$

移项，带入 $E_0$ 可以求出 $E_1=3$。

---

考虑两个。当两个紧挨着放的时候，记为 $E_{11}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/m8oqdnhg.png)

假设瞄准左边的，有初始值 $1$。这一发有 $\dfrac{1}{3}$ 的概率击中左边的白，状态不变，所以贡献为 $\dfrac{1}{3}E_{11}$；有 $\dfrac{1}{3}$ 的概率击中左边的黑，状态变为 $01$，贡献为 $\dfrac{1}{3}E_{01}$；有 $\dfrac{1}{3}$ 的概率击中右边的黑，状态变为 $10$。

很显然瞄准右边是一样的。

得到公式：

$$E_{11}=1+\dfrac{1}{3}E{11}+\dfrac{1}{3}E_{01}+\dfrac{1}{3}E_{10}$$

$01$ 和 $10$ 的状态就是单独一个 $1$。故带入 $E_{1}$ 解方程可以得出 $E_{11}=4.5$。

---

当两个中间空一格排列时，记为 $E_{101}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/gpoazk0i.png)

如果在最优策略下，很显然瞄准是要对着中间的白，因为它有 $\dfrac{2}{3}$ 的概率提供贡献，但是打其它地方只有 $\dfrac{1}{3}$ 乃至更小的概率。

分析可得

$$E_{101}=1+\dfrac{1}{3}E_{001}+\dfrac{1}{3}E_{101}+\dfrac{1}{3}E_{100}$$

解得 $E_{101}=4.5$。

---

求解中，发现有 $10000$ 和 $00001$ 的状态，尽管它们代表的状态是一样的，但是数值上不相等，也不好处理，所以采用记忆化搜索，直接递归到 $0$ 返回 $1$。

采用 $01$ 串记录状态，每次遍历从每一个点瞄准，然后取最小值（最优策略）。

考虑如何实现移项解方程。很显然这一枪如果打空了，那么状态应该是不变的。这种情况不能直接加上求自己，也不能继续搜索，否则会死循环。所以记录一下有几个状态不变，和 $3$ 做一下比，然后再乘倒数就行了。

## AC Code

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
const int inf=0x3f3f3f3f;
int n,s;
double e[1<<16];
double dp(int s)
{
	if (!s) return e[0]=0;
	if (e[s]!=inf) return e[s];
	for (int i=1;i<=16;i++)
	{
		int a=s&~(1<<i-1),b=s&~(1<<i),c=s&~(1<<i+1),cnt=3;//    cnt/3*e[s]
		if (a==s) cnt--;
		if (b==s) cnt--;
		if (c==s) cnt--;
		e[s]=min(e[s],(1+(s!=a?dp(a)/3.0:0)+(s!=b?dp(b)/3.0:0)+(s!=c?dp(c)/3.0:0))*3.0/cnt);
	}
	return e[s];
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		int a;scanf("%d",&a);
		s|=(1<<a);
	}
	for (int i=0;i<=1<<16;i++) e[i]=inf;
	printf("%.10lf",dp(s));
	return 0;
}
```

---

## 作者：PeterBei (赞：4)

已知 $x_i \leq 15$，因此可以对于球的状态进行二进制状态压缩，$1$ 表示有物品，$0$ 表示没有物品或者物品已被打倒。

设 $s$ 为压缩后的数字，$E_s$ 为对应状态的期望，易知 $E_0=0$。

接下来推转移方程：设场上仅有一个物品，则可以将球投至这个物品的左边，这个物品上和这个物品的右边。三种投掷方式击中物品的概率均为 $\dfrac{1}{3}$。若是击中物品，则状态会从 $1$ 变为 $0$，否则状态将不会改变。由此可知，$E_1=E_1\times \dfrac{2}{3}+E_0\times \dfrac{1}{3}$，$E_1$ 可以通过解一元一次方程得到。

依此类推，可以看出若在投球后物品状态没有改变，则会给 $E_s$ 贡献 $E_s\times \dfrac{1}{3}$，否则设状态改变为 $s2$，则会贡献 $E_{s2}\times\dfrac{1}{3}$。

可以使用递归来枚举状态。

```
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
int read() {
	char c = getchar(); int f = 1, a = 0;
	while(c != '-' && (c > '9' || c < '0'))
		c = getchar();
	if(c == '-')
		f = -1, c = getchar();
	while(c >= '0' && c <= '9')
		a = a * 10 + (c - '0'), c = getchar();
	return f * a;
}
const int N = 65540;
double E[N];
double dfs(int s){
	if(E[s] < 100000000)
		return E[s];
	bool flag = 0;
	for(int i = 0; i <= 15; i++){
		int w = (s >> (15 - i)) & 1;
		if(w == 1) flag = 1;
		if(flag){
			double now = 1, ji = 0;
			for(int j = -1; j <= 1; j++){
				w = (s >> (15 - i + j)) & 1;
				if(w == 0) ji++;
				else now += dfs(s - (1 << (15 - i + j))) / 3.0;
			}
			if(ji != 3){
				E[s] = min(E[s], now / (3.0 - ji) * 3.0);
			}
		}
	}
	return E[s];
}
int main() {
	for(int i = 0; i <= (1 << 16); i++){
		E[i] = 100000000;
	}
	int n = read(), s = 0;
	for(int i = 1; i <= n; i++){
		int z = read();
		s += (1 << (15 - z));
	}
	E[0] = 0;
	dfs(s);
	printf("%.10lf", E[s]);
	return 0;
}
```

---

## 作者：lalaji2010 (赞：2)

# AT_tdpc_ball

## 题目链接

[AT_tdpc_ball](https://www.luogu.com.cn/problem/AT_tdpc_ball)

## 分析

看到 $N \leq 16$ 首先想到状态压缩dp。

那么很显然，这题是一道与**数学期望**有关的**状压dp**。

于是我们考虑三个因素：

### Ⅰ.设状态

令二进制串 $bit$ 表示物品的分布情况，二进制下为 $1$ 的位置上有物品，为 $0$ 的位置上无物品。

那么，我们设 $dp_{bit}$ 表示 $bit$ 变成 $0$ 的需要的次数的数学期望，即从当前物品的分布到物品全部被球击中的需要的次数的数学期望。

### Ⅱ.设边界

显然，有 $dp_{0}=0$。

### Ⅲ.列状态转移方程

首先，我们对于任意串 $mask$，可以打的位置共有 $16$ 个。所以，$dp_{mask}$ 可以由打这 $16$ 个位置中数学期望值最小的位置转移而来。

那么我们考虑最暴力的做法，**抓住数据的弱点**即每次打击只会有 $3$ 种情况，依次枚举打的位置，对于每次打击瞄准的位置计算其数学期望。

假设我们成功计算出了 $dp_{mask}$ 的值，那么它会对谁有贡献呢？

很显然，是一个能够通过击打一次变为 $mask$ 的串，而对于任意一个非 $0$ 串的一次任意位置的击打，总共会分出 $3$ 个串。

不难得到，这道题的递推过程类似于一棵三叉树的dfs，考虑使用记忆化搜索。

接下来讨论对于任意一个串的任意一个位置进行打击的数学期望的状态转移即可。

我们不妨击打 $mask$ 的右数第 $i$ 个位置。因为我们首先要击打一次，所以数学期望初值先设为 $1$。

我们就可能击中 $i-1$，$i$ 或 $i+1$。各有 $\frac{1}{3}$ 的概率。

设该三个位置里有 $k$ 个有物品。那么对于有物品的位置，当前的数学期望应加上击打后的串的数学期望的 $\frac{1}{3}$。而击打的位置里有 $3-k$ 个位置是空的，所以平均击打到一个有物品的位置需要 $\frac{3}{k}$ 次，所以当前击打 $i$ 位置的数学期望应在最后乘上 $\frac{3}{k}$。

那么 $dp_{mask}$ 就等于击打 $mask$ 各个位置的数学期望的最小值。而且我们能够发现，最优决策一定不需要击打 $0$ 或 $15$。

根据上述分析，其实最终的递归过程类似于一棵二叉树的 dfs 中套了一个 $14$ 次的循环，时间复杂度近似于 $O(N \times 2^N)$，可以通过此题。

记忆化搜索求解即可。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[24];
int bit;
double dp[(1<<16)+5];
double dfs(int mask){
	if(dp[mask]<0x3f3f3f3f/2) return dp[mask];
	if(mask==0) return dp[mask]=0;
	for(int i=1;i<15;i++){
		int l=~(1<<i-1)&mask,m=~(1<<i)&mask,r=~(1<<i+1)&mask;
		double exp=(3.0)/((double)(1.0*(int)(l!=mask))+(int)(m!=mask)+(int)(r!=mask));
		double p=(3.0)/((double)(1.0*(int)(l!=mask))+(int)(m!=mask)+(int)(r!=mask));
		if(l!=mask){
			exp+=dfs(l)/3.0*p;
		}
		if(m!=mask){
			exp+=dfs(m)/3.0*p;
		}
		if(r!=mask){
			exp+=dfs(r)/3.0*p;
		}
		dp[mask]=min(dp[mask],exp);
	}
	return dp[mask];
}
int main(){
	cin>>n;
	for(int i=0;i<(1<<16)+1;i++) dp[i]=0x3f3f3f3f;
	for(int i=1;i<=n;i++){
		cin>>x[i];
		bit=bit|(1<<x[i]);
	}
	printf("%.7lf\n",dfs(bit));
	return 0; 
}
```

---

## 作者：Proxima_Centauri (赞：1)

[雅虎曰：原题传送门](https://www.luogu.com.cn/problem/AT_tdpc_ball)
# 题意
很明显清楚的题意：在一条坐标轴上有 $n$ 个东西，每次扔一个球，瞄准一个位置，那么会**等概率**地打到它和它两侧的三个位置，求使用**最优策略**时，打完这些物体的次数的**数学期望**。
# 分析过程
看到数据范围这么小，很容易想到了**状态压缩 DP**。

那就开整！首先定义状态：在 $x$ 的第 $i$ 位是 $0$ 时，表明该位置上不本来就没有东西或者东西被打掉了。那么 $f_i$ 就表示达成这种状态的期望步数。

数学期望倒着求，这都是老套路了。所以 $f_0 = 0$，其余都是无穷大；如果设初始状态为 $fmax$，最终答案便是 $f_{fmax}$。

接下来就是重头戏：状态转移！蒟蒻做这个题的时候没想那么多，只想到了**分类讨论**，于是枚举了许多可能的情况，形成了如下暴力的解法，具体解释看代码：
```
for (int i = 1; i <= fmax; i++)
{
	if ((i | fmax) != fmax) continue; // 首先判断状态是否合法，不合法就别求了
	int minnx = 0, maxnx = 0;
	for (int t = 0; t < 16; t++) if ((i | (1 << t)) == i) minnx = min(minnx, t), maxnx = max(maxnx, t);
	for (int j = minnx; j <= maxnx; j++) // 枚举瞄准哪个点，这里有一个小贪心，如果当前状态最左边和最右边的东西分别在 minnx 和 maxnx 上，那么最优解肯定不会瞄准 minnx 左边或者 maxnx 右边 
		if (j == minnx) // 特判左端点
			if (i & (1 << minnx + 1)) f[i] = min(f[i], 0.5 * f[i - (1 << minnx + 1)] + 0.5 * f[i - (1 << minnx)] + 1.5);
			else f[i] = min(f[i], f[i - (1 << minnx)] + 3);
		else if (j == maxnx) // 特判右端点
			if (i & (1 << maxnx - 1)) f[i] = min(f[i], 0.5 * f[i - (1 << maxnx - 1)] + 0.5 * f[i - (1 << maxnx)] + 1.5);
			else f[i] = min(f[i], f[i - (1 << maxnx)] + 3);
		else // 又臭又长的分类讨论环节，具体转移的解释见下文
			if (i & (1 << j))
				if (i & (1 << j - 1))
					if (i & (1 << j + 1))
						f[i] = min(f[i], 1.0 / 3 * f[i - (1 << j - 1)] + 1.0 / 3 * f[i - (1 << j)] + 1.0 / 3 * f[i - (1 << j + 1)] + 1);
					else f[i] = min(f[i], 0.5 * f[i - (1 << j - 1)] + 0.5 * f[i - (1 << j)] + 1.5);
				else 
					if (i & (1 << j + 1))
						f[i] = min(f[i], 0.5 * f[i - (1 << j)] + 0.5 * f[i - (1 << j + 1)] + 1.5);
					else f[i] = min(f[i], f[i - (1 << j)] + 3);
			else
				if (i & (1 << j - 1))
					if (i & (1 << j + 1))
						f[i] = min(f[i], 0.5 * f[i - (1 << j - 1)] + 0.5 * f[i - (1 << j + 1)] + 1.5);
					else f[i] = min(f[i], f[i - (1 << j - 1)] + 3);
				else 
					if (i & (1 << j + 1))
						f[i] = min(f[i], f[i - (1 << j + 1)] + 3);
}
```
中间的转移，总体来讲就是三大种情况：

1. 能打到的三个点中，只有一个有东西

设有东西的点是 $j$，那么基于数学期望的定义会有如下式子：
$$f_i = 1 + \frac{1}{3} \cdot f_{i - 2 ^ j} + \frac{2}{3} \cdot f_i$$
其中 $i - 2 ^ j$ 表示的就是打掉 $j$ 位置后的状态。之后稍加化简就可以得到：
$$f_i = f_{i - 2 ^ j} + 3$$
注意这个 $3$，不要手误打成 $1$，别问我怎么知道的。（逃

2. 能打到的三个点中，有两个有东西

设有东西的点是 $j, k$，同理得到：
$$f_i = 1 + \frac{1}{3} \cdot f_{i - 2 ^ j} + \frac{1}{3} \cdot f_{i - 2 ^ k} + \frac{1}{3} \cdot f_i$$
化简：
$$f_i = 1.5 + 0.5 \cdot f_{i - 2 ^ j} + 0.5 \cdot f_{i - 2 ^ k}$$
3. 能打到的三个点都有东西

那三个点就是 $j - 1, j, j + 1$，得到式子：
$$f_i = 1 + \frac{1}{3} \cdot f_{i - 2 ^ {j - 1}} + \frac{1}{3} \cdot f_{i - 2 ^ j} + \frac{1}{3} \cdot f_{i - 2 ^ {j + 1}}$$
不必化简。

------------
当然还有另一种情况：能打到的没有东西，但这种怎么可能会是最优情况呢？

所以，把上面代码中枚举的**能打到的东西的位置**带入刚刚推的式子即可。
# AC code
大部分都贴过了。
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int x[20];
double f[(1 << 16) + 10];
int main()
{
	int n;
	scanf("%d", &n);
	int fmax = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", x + i);
		fmax += 1 << x[i]; 
	}
	for (int i = 1; i <= fmax; i++) f[i] = 1e9;
	// 刚刚贴的 
	printf("%.6lf\n", f[fmax]);
	return 0;
 }
```
# 总结
暴力出奇迹！！！

再提醒：**位运算的优先级比加减法和比较运算符都低！**

---

## 作者：fa_555 (赞：1)

under 题解 [AT687](https://www.luogu.com.cn/problem/AT687)

同步发布于[个人博客](https://fa555.github.io/2020/某At的dp场/#J-ボール)

### problem

有 $N \ (1 \le N \le 16)$ 个物品，其中第 $i$ 个在 $x_i \ (0 \le x_i \le 15)$ 坐标处。向坐标 $x$ 扔球时，分别有 $\frac{1}{3}$ 的概率击中坐标 $x - 1, x, x + 1$ 中的一个；如果打中的坐标上有物品，将其打倒。求出在最优策略下期望扔球多少次将所有物品打倒。保证 $x_i$ 两两不同。

赛时补充：**每次扔球时可以先看到上一次扔球击中的位置再决定向哪里扔球。**

### solution

看到这个数据范围，盲猜状压。

设 $E(S)$ 为状态 $S$ 时的期望次数。考虑如何转移。一般这种题需要列出一个关于 $E(S)$ 的方程，把它反解出来。

考虑向 $x$ 扔球的情况，能列出这样的一个方程：

$$
E(S) = 1 + \sum{(P(u) \times E(T))} + (1 - \sum{P(u)}) \times E(S)
$$

其中 $P(x) = \frac{1}{3}$ 表示击中坐标 $x$ 的概率，$u \in \{x - 1, x, x + 1 \}$，`T = S & ~u`。化简可得

$$
E(S) = \frac{1 + \sum{(P(u) \times E(T))}}{\sum P(u)}
$$

就可以枚举 $x$ 进行转移了。

显然可以记忆化一下。设 $f_S = E(S)$，初始状态 $f_0 = 0$。

答案即为 $E(S)$。总复杂度 $O(N \times 2^N)$。

### code

代码可能换了一些奇怪的写法，但是跟上面式子是等价的（

``` cpp
double f[1<<16|1];

double dfs(int S) {
  if (f[S] >= 0.) return f[S];

  double ans = 1 << 16, E;
  for (int x = 0, c; x < 16; ++x) {
    int T[] = {
      S & ~((1 << x) << 1),
      S & ~(1 << x),
      S & ~((1 << x) >> 1)
    };
    c = 0, E = 1.;

    for (int i = 0; i < 3; ++i)
      if (S != T[i])
        E += dfs(T[i]) / 3., ++c;
    ans = std::min(ans, 3 * E / c);
  }
  return f[S] = ans;
}

double solve() {
  int N, S = 0;
  scanf("%d", &N);
  std::fill(f + 1, f + (1 << 16), -1);
  for (int t; N; --N) {
    scanf("%d", &t);
    S |= 1 << t;
  }
  return dfs(S);
}

```

---

## 作者：SnowFlavour (赞：0)

首先考虑只有一个瓶子的情况。在这个时候。我们显然可以直接冲着那个瓶子砸，狂砸 $3$ 次就理论上可以干掉这个球。这个 $3$ 就是只有一个球的期望。

再考虑多个球的情况。我们枚举在每一个位置扔球，则数学期望就是砸倒以后的三种情况的期望的平均值再加上 $1$。那如果没砸到怎么办？那这样就相当于是一个解方程了，我们只要分类讨论即可。

设当前的状态为 $x$，砸到三个位置的位置是 $l$，$m$，$r$，

这是方程：

$$f_x=\frac{f_l+f_m+f_r}{3}+1$$

当无论砸到哪里都不会砸到瓶子的时候，这个操作是无意义的。


当有一个状态和原状态不同的时候，这个方程就变成这样（以 $r$ 为例）：

$$f_x=\frac{2 \times f_x+f_r}{3}+1$$

移项，得：

$$f[x]=f_r+3$$

另外的情况也可以由对称性得到。

当由两个状态和原状态不同的时候，这个方程就变成这样（以 $m$，$r$ 为例）：

$$f_x=\frac{f_x+f_m+f_r}{3}+1$$

整理，得：

$$f_x=\frac{f_m+f_r+3}{2}$$

另外的情况也可以由对称性得到。

当所有状态都和原状态不同得时候，直接带入原方程即可。

这是 AC Code：
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=20;
double f[1<<N];
int x[N];
int main(){
    int n,zt=0,mx=0;
    cin>>n;
    memset(f,0x42,sizeof(f));
    for(int i=1;i<=n;i++){
        cin>>x[i];
        zt+=1<<x[i];
        mx=max(mx,x[i]);
    }
    for(int i=0;i<=mx;i++)f[1<<i]=3;
    for(int i=1;i<(1<<(mx+1));i++){
        if(__builtin_popcount(i)==1)continue;
        // cout<<endl<<i<<endl;
        for(int k=1;k<=mx;k++){
            int dal=i&(~(1<<(k+1)));
            int dam=i&(~(1<<k));
            int dar=i&(~(1<<(k-1)));
            int cnt=0;
            bool l=0,m=0,r=0;
            if(dal==i)cnt++,l=1;
            if(dam==i)cnt++,m=1;
            if(dar==i)cnt++,r=1;
            if(cnt==3)continue;
            else{
                // cout<<k<<endl;
                // cout<<dal<<" "<<dam<<" "<<dar<<endl;
                if(cnt==1){
                    // cout<<111<<endl;
                    if(l)f[i]=min(f[i],(f[dam]+f[dar]+3)/2);
                    if(m)f[i]=min(f[i],(f[dal]+f[dar]+3)/2);
                    if(r)f[i]=min(f[i],(f[dam]+f[dal]+3)/2);
                }
                if(cnt==2){
                    if(l&&m)f[i]=min(f[i],f[dar]+3);
                    if(l&&r)f[i]=min(f[i],f[dam]+3);
                    if(r&&m)f[i]=min(f[i],f[dal]+3);
                }
                if(cnt==0)f[i]=min(f[i],(f[dal]+f[dar]+f[dam]+3)/3);
            }
        }
        // cout<<f[i]<<endl;
    }
    // cout<<zt<<endl;
    printf("%.15f",f[zt]);
}
```

---

