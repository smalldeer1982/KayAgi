# [USACO22JAN] Drought G

## 题目描述

Farmer John 的草地里的草在一场大旱中都干死了。经过数小时的绝望和沉思，FJ 想到了一个绝妙的主意，购买玉米来喂养他宝贵的奶牛。

FJ 的 $N$ 头奶牛（$1 \leq N \leq 100$）排成一行，队伍中的第 $i$ 头奶牛的饥饿度为一个非负整数 $h_i$。由于 FJ 的奶牛是社会性动物，她们坚持一起进食，FJ 降低奶牛饥饿度的唯一方法是选择两头相邻的奶牛 $i$ 和 $i+1$ 并分别喂她们一袋玉米，令她们的饥饿度各减少 1。

FJ 想将他的奶牛喂至所有的奶牛都具有相同的非负饥饿度。尽管他不知道他的奶牛们具体的饥饿度，他知道每一头奶牛的饥饿度上界；具体地说，第 $i$ 头奶牛的饥饿度 $h_i$ 至多为 $H_i$（$0\le H_i\le 1000$）。

你的工作是计算符合上述上界的 $N$ 元组 $[h_1,h_2,\ldots,h_N]$ 的数量，使得 FJ 有可能达到他的目标，答案对 $10^9+7$ 取模。


## 说明/提示

【样例解释】

共有 $(9+1)\cdot (11+1)\cdot (7+1)$ 个 $3$ 元组 $h$ 与 $H$ 相符合。

$h=[8,10,5]$ 是其中一个元组。在这个情况中，有可能使得所有的奶牛具有相同的饥饿度：给奶牛 $2$ 和 $3$ 各两袋玉米，然后给奶牛 $1$ 和 $2$ 各五袋玉米，可以使得所有奶牛的饥饿度均为 $3$。

$h=[0,1,0]$ 是另一个元组。在这个情况中，不可能使得奶牛们的饥饿度相等。

【数据范围】


- 编号为偶数的测试点中的 $N$ 均为偶数，编号为奇数的测试点中的 $N$ 均为奇数。

- 测试点 3-4 满足 $N\le 6$ 以及 $H_i \le 10$。

- 测试点 5-10 满足 $N\le 50$ 以及 $H_i \le 100$。

- 测试点 11-20 没有额外限制。


## 样例 #1

### 输入

```
3
9 11 7```

### 输出

```
241```

## 样例 #2

### 输入

```
4
6 8 5 9```

### 输出

```
137```

# 题解

## 作者：耶梦加得 (赞：18)

~~由于按了 Command+Q 导致没能晋级的选手报到~~

大眼观察，$H_i$ 这么小，复杂度很可能和 $H_i$ 有关，然后 $N$ 也很小，所以复杂度很可能是 $O(HN),O(HN^2),O(H^2N)$ 之类的。又是有限制的，“答案可能很大”的计数，八成是 DP 没跑了。

显然我们有一个状态是“当前处理到第 $i$ 头牛”。考虑从 $i$ 到 $i+1$ 的转移过程，容易发现此时 $[1,i-1]$ 的牛应当都处于同一饥饿值，否则无论如何对 $i + 1$ 操作都无法满足条件。

也就是说，还有两个状态分别是牛 $i$ 的饥饿值 $j$，以及牛 $[1,i-1]$ 的饥饿值 $k$。空间 $O(NH^2)$，爆炸。

仔细考虑，容易发现其实我们只关心这两个值的差值。对于整个 DP 过程而言 $k$ 的值一旦确定就无法改变。我们可以将 DP 分若干次次进行，每一次人为规定每一头奶牛最终的饥饿值为 $k$。设 $\min\{H_i\} = M$，易知 $k \le M$。对于每一次 DP，先把所有 $H_i$ 都减去 $k$。

那么规定 $dp[i][j]$ 表示前 $i$ 头牛使得：

1. 前 $i - 1$ 头牛饥饿值为 0（注意：在减去 $k$ 的意义下）;
2. 第 $i$ 头牛饥饿值为 $j$。

考虑转移，由于考虑 $dp[i + 1][j]$ 的时候我们要把第 $i$ 头牛也喂饱，也就是对于 $dp[i][j']$，要先对 $i, i+1$ 两头牛投喂 $j'$ 次，因此 $j' + j \le H_{i + 1}$。容易得到转移方程：

$dp[i + 1][j] = \sum{dp[i][j']}(0 \le j \le \min(H_i,H_{i+1}-j)$ 

边界为 $dp[1][j] = 1$，要求 $dp[N][0]$。

可以通过处理前缀和的方式 $O(1)$ 转移，DP 复杂度 $O(NH)$，总复杂度 $O(NH^2)$，空间上可以通过滚动数组进一步优化（代码没有用滚动数组）。

~~最后输出 $dp[N][0]$ 的总和然后发现样例都过不去，交一发 WA50。~~

对于样例 $2$ 输出 $dp$ 数组，发现我们第一次 DP 就得出了 $dp[N][0] = 137$。

冷静分析题目，发现题目问的是有多少种初始情况，而不是有多少种方案。当 $N$ 为偶数时，$k$ 为多少不重要（可以通过 $N/2$ 次操作变成 $k-1$），因此我们对于这种情况进行一次 DP 后直接输出 $dp[N][0]$ 即可。

```cpp
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
inline int mmin(register int x, register int y) {
    return x > y ? y : x;
}
const long long mod = 1000000007;
int n;
int a[107], mn = 1000;
long long ans, g[107][1007];
signed main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        mn = mmin(mn, a[i]);
    }
    for(int i = 0; i <= a[1]; ++i) g[1][i] = i + 1; //这里省略了求和
    if(n % 2 == 0)mn = 0;
    for(int d = 0; d <= mn; ++d) {
        for(int i = 2; i <= n; ++i) {
            g[i][0] = g[i - 1][mmin(a[i], a[i - 1]) - d];
            for(int j = 1; j <= a[i] - d; ++j) {
                g[i][j] = g[i][j - 1] + g[i - 1][mmin(a[i] - j, a[i - 1]) - d];
                if(g[i][j] >= mod) g[i][j] -= mod;
            }
        }
        ans += g[n][0]; if(ans >= mod) ans -= mod;
    }
    printf("%lld\n", ans);
    return 0;
}

```





---

## 作者：duyi (赞：8)

[更好的阅读体验](https://www.cnblogs.com/dysyn1314/p/P8096.html)

# 洛谷P8096 [USACO22JAN] Drought G

## 题目大意

[题目链接](https://www.luogu.com.cn/problem/P8096)

对于某个整数序列 $h_1, h_2, \dots, h_n$，定义一种操作：选取一个位置 $i$，满足 $1\leq i < n$ 且 $h_i, h_{i + 1}\geq 1$，令 $h_i$ 和 $h_{i + 1}$ 同时减 $1$。

称一个序列是合法的，当且仅当能通过若干次操作，使它所有位置上的值相等。

现在给出 $n$ 和每个位置上 $h_{i}$ 的上界 $H_{i}$（即 $0\leq h_i\leq H_{i}$），问有多少个合法的 $h$ 序列。

数据范围：$1\leq n\leq 100$，$0\leq H_i \leq 1000$。

## 本题题解

要想计数，我们需要先搞清楚一个序列合法的充分必要条件。

因为只能对**相邻位置**操作，一个经典的套路是**把所有位置按下标的奇偶性分类**。这样的好处是，每次操作恰好会碰到两类位置各 $1$ 个。

设序列的前 $i$ 个位置里，奇数位置上数的和为 $o_i$，偶数位置上数的和为 $e_i$。考虑某个 $i$，不妨假设 $i$ 是奇数，那么 $h$ 序列合法的一个必要条件是：$o_i \geq e_i$。理由如下：最终的序列，显然满足 $o_i\geq e_i$（所有位置上数都相等，但奇数位置比偶数位置多一个）。任意一次操作 $(p, p + 1)$，若 $p < i$，那么不会改变 $o_i - e_i$ 的值；若 $p = i$，反而会使 $o_i - e_i$ 变得更小（$o_i$ 减 $1$，$e_i$ 不变）。所以只有初始时 $o_i\geq e_i$，最终才能 $o_i\geq e_i$。同理，若 $i$ 是偶数，则需要满足 $e_i\geq o_i$。

为了方便，我们定义一个 $d_i$：若 $i$ 是奇数，$d_i = o_i - e_i$；若 $i$ 是偶数，$d_i = e_i - o_i$。不难发现：$d_i = h_i - d_{i - 1}$。根据刚刚的分析，序列合法的一个必要条件是 $\forall i: d_i\geq 0$。任意一次操作 $(p, p + 1)$ 对 $d$ 序列的影响是：让 $d_p$ 减 $1$，其他值均不变。

考虑最终的 $d$ 序列是什么样。不妨设最终的 $h$ 序列上所有值均为 $k$。那么 $d_1 = d_3 = d_5 = \dots = k$，$d_2 = d_4 = d_6 = \dots = 0$。我们的目标就是要把 $d$ 序列变成这个样子。我们的工具是，可以通过一次操作，使任何一个 $p < n$ 的位置的 $d_p$ 减 $1$。除此之外，我们没有任何限制！换言之，原来那个对 $h$ 序列进行操作的问题，彻底被我们转化为了对 $d$ 序列进行操作的问题。而且 $d$ 序列的操作比 $h$ 简洁得多。另外，$d$ 和 $h$ 序列显然是一一对应的（知道 $h$ 可以构造出 $d$，知道 $d$ 可以构造出 $h$），所以接下来我们只要求合法的 $d$ 的数量即可。

不同于 $h$，$d$ 合法的充分必要条件是很显然的。具体来说，若 $n$ 是偶数，我们需要 $\forall i < n: d_i \geq 0$，且 $d_n = 0$ 即可；若 $n$ 是奇数，我们需要 $\forall i < n \text{ and }i\text{ is odd}: d_i \geq k$，$\forall i < n \text{ and } i \text{ is even}: d_i \geq 0$，且 $d_n = k$ 即可（这里假设 $k$ 是我们已枚举的一个常数）。为了求这样的序列数量，可以做 DP。设 $\mathrm{dp}(i, j)$ 表示考虑了前 $i$ 个位置，$d_i = j$ 的方案数。则有转移：
$$
\mathrm{dp}(i, j) = \sum_{h_i = j}^{H_i} \mathrm{dp}(i - 1, h_i - j)
$$
若 $n$ 是偶数，最终答案就是 $\mathrm{dp}(n, 0)$。若 $n$ 是奇数，定义状态时要加上一个条件：当 $i$ 是奇数时 $j\geq k$。最终答案是所有 $k$ 对应的 $\mathrm{dp}(n, k)$ 之和。

直接 DP 的时间复杂度是 $\mathcal{O}(nH^2)$。用前缀和可以优化到 $\mathcal{O}(nH)$。当 $n$ 是奇数时还需要在外层枚举 $k$，所以此时的总时间复杂度是 $\mathcal{O}(nH^2)$。

## 参考代码

```cpp
// problem: P8096
#include <bits/stdc++.h>
using namespace std;

#define mk make_pair
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 100, MAXH = 1000;
const int MOD = 1e9 + 7;
int n, H[MAXN + 5], dp[MAXN + 5][MAXH + 5], sum[MAXH + 5];

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> H[i];
	}
	
	if (n % 2 == 0) {
		// n 是偶数
		dp[0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= H[i]; ++j) { // d[i]
				for (int h = j; h <= H[i]; ++h) { // d[i] = h - d[i - 1]
					dp[i][j] = (dp[i][j] + dp[i - 1][h - j]) % MOD;
				}
			}
		}
		cout << dp[n][0] << endl;
	} else {
		int ans = 0, lim = MAXH;
		for (int i = 1; i <= n; i += 2) {
			// 对所有奇数位置：k <= d[i] <= h[i] <= H[i]
			// 所以 k 的上限是这些 H[i] 的 min
			ckmin(lim, H[i]);
		}
		for (int k = 0; k <= lim; ++k) {
			dp[0][0] = 1;
			for (int i = 1; i <= n; ++i)
				for (int j = 0; j <= MAXH; ++j)
					dp[i][j] = 0; // 清空
			for (int i = 1; i <= n; ++i) {
				sum[0] = dp[i - 1][0];
				for (int j = 1; j <= MAXH; ++j) {
					sum[j] = (sum[j - 1] + dp[i - 1][j]) % MOD;
				}
				for (int j = (i % 2 == 0 ? 0 : k); j <= H[i]; ++j) { // d[i]
					/*
					for (int h = j; h <= H[i]; ++h) { // d[i] = h - d[i - 1]
						dp[i][j] = (dp[i][j] + dp[i - 1][h - j]) % MOD;
					}
					*/
					dp[i][j] = sum[H[i] - j];
				}
			}
			ans = (ans + dp[n][k]) % MOD;
		}
		cout << ans << endl;
	}
	
	return 0;
}
```



---

## 作者：AutiFancers (赞：6)

## 前言
谨以此篇，献给帮助我 $4$ 个小时去理解此题，写出此题，并优化此题的机房大佬 [wangmaocheng](https://www.luogu.com.cn/user/553849)。

## 题意
先抽象该题意，有一个长为 $n$ 的序列 $a$，在进行若干次操作后使 $a$ 的每一个数都相等。其中，一次操作的意思是将 $a$ 任意两相邻的数减一，求存在多少种方案使之成立。

其中：$1 \leq n \leq 100$，$0\le a_i \le 1000$。

## 思路
本部分主要完整呈现本蒟蒻写此题的心路历程。

看到 $n$ 和 $a_i$ 的范围较小，且答案为计数性质，想到 DP。

讨论到 DP，就需要想到状态表示和状态计算。

### 暴力

我的第一版状态表示是定义 $f(i,j)$ 表示前 $i$ 头牛，最后的序列每个数均为 $j$ 的方案的集合。但因为无法想出状态转移方程，不得不放弃。接下来考虑暴力在优化，定义 $f(i,j,k)$ 表示前 $i$ 头牛，总共吃了 $j$ 份饲料，且与前一头牛共同吃的饲料份数为 $k$。在统计答案时，需要分类讨论 $n$，是奇数还是偶数。

为了表述方便，最后情况序列都相同的数记为 $m$。

1. 当 $n$ 为偶数时，存在永远存在一种方式使序列中的每个数变为 $0$。那么说明，此种情况一定包括 $m$ 可以取到的所有值，那么在最后统计答案的时候就可以直接统计最后序列每个数为 $0$ 的情况即可。
2. 当 $n$ 为奇数时，是不一定存在一种方式使序列中的每个数变为 $0$ 的。那么，在每次统计答案时，需要将序列里每个数的值都减一，直到有一个数变为 $0$，才真正能统计出答案。

#### 时间复杂度 
对于偶数，复杂度为 $O(NH^3)$，对于奇数，复杂度为 $O(NH^4)$，是一定会超时的。

#### 代码
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=110,mod=1e9+7;
int n,mn=0x3f3f3f3f,ans;
int a[N]; 
int f[N][N][N]; 

int main() {
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        mn=min(a[i],mn);
    }
    
    for(int y=0;y<=mn;y++) {
        memset(f,0,sizeof f);
        f[0][0][0]=1;
        for(int i=1;i<=n;i++)
            for(int j=0;j<=a[i];j++)
                for(int k=0;k<=j;k++)
                    for(int u=k;u<=a[i-1];u++)
                        f[i][j][k]=(f[i][j][k]+f[i-1][u][u-k])%mod;
        for(int i=0;i<=a[n];i++) ans=(ans+f[n][i][i])%mod;
        for(int i=1;i<=n;i++) a[i]--;
        if(!(n%2)) {
            cout<<ans<<'\n';
            return 0;
        }
    }

    
    cout<<ans<<'\n';    
    return 0;
}
```
喜提 45 分。

### 正解

考虑降维，有个小技巧，先将原状态转移方程的 $j$ 和 $k$ 调换一下位置，在对于如何统计 $f(i,k)$ 表示出来，得到：
``` cpp
f[i][k][k+0]=f[i-1][k+0-(a[i-1]-1)][a[i-1]-1]+f[i-1][k+0-(a[i-1]-2)][a[i-1]-2]+...+f[i-1][0][k]
f[i][k][k+1]=f[i-1][k+1-(a[i-1]-1)][a[i-1]-1]+f[i-1][k+1-(a[i-1]-2)][a[i-1]-2]+...+f[i-1][1][k]
f[i][k][k+2]=f[i-1][k+2-(a[i-1]-1)][a[i-1]-1]+f[i-1][k+2-(a[i-1]-2)][a[i-1]-2]+...+f[i-1][2][k]
f[i][k][k+t]=f[i-1][k+t-(a[i-1]-1)][a[i-1]-1]+f[i-1][k+t-(a[i-1]-2)][a[i-1]-2]+...+f[i-1][t][k]
```
找规律，很容易发现（~~其实并不容易，本蒟蒻其实花了 30 分钟才看出来~~)：
```cpp
f[i][k]=f[i-1][a[i-1]]+f[i-1][a[i-1]-1]+...+f[i-1][a[i-1]-k]
```
降维成功！！！
#### 时间复杂度 
对于偶数，复杂度为 $O(NH^2)$，对于奇数，复杂度为 $O(NH^3)$，有点危险，实测只有 $75pts$。

再优化，如何去优化奇数的情况呢，前缀和就可以了。

**注意**：本代码和上面的状态表示有些许不同。本代码的 $f(i,j)$ 表示第 $i$ 头牛与后一头牛共享了 $j$ 份草料。

#### 代码
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=110,mod=1e9+7;
int n,mn=0x3f3f3f3f;
int a[N]; 
int f[N][N*10],sum[N][N*10],ans; 

int main() {
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        mn=min(a[i],mn);
        a[i]++;
    }
    
    for(int y=0;y<=mn;y++) {
        memset(f,0,sizeof f);
        memset(sum,0,sizeof sum);
        f[0][0]=1;
        sum[0][0]=1;
        for(int i=1;i<=n;i++) a[i]--;
        for(int i=1;i<=n;i++)
            for(int k=0;k<=a[i];k++) {
                if(sum[i-1][a[i]-k]) f[i][k]=sum[i-1][a[i]-k];
                else f[i][k]=sum[i-1][a[i-1]];
                sum[i][k]=f[i][k];
                if(k) sum[i][k]=(sum[i][k]+sum[i][k-1])%mod; 
            }

        
        int tmp=0;
        tmp=f[n][0]%mod;
        if(!(n%2)) {
            cout<<tmp<<'\n';
            return 0;
        }
        ans=(ans+tmp)%mod;
    }
    
    cout<<ans<<'\n';    
    return 0;
}
```

---

## 作者：vicissitudes (赞：3)

# 思路

看到 $h_i$ 比较小，考虑枚举最后的饥饿度 $m$。

首先 $m$ 的上界应该是 $\min\ h_i$，因为最后的饥饿度不可能增加。

感觉倒着做好做点，也就是从全为 $m$ 开始，给相邻两个数加。每个数不能超过上界 $h_i$。

这里只能加。

我们先算出每个位置最多可以加多少次，记为 $cnt_i$。

由于一个位置可以和前面的和后面的加，所以我们设 $f_{i, j}$ 表示第 $i$ 位还剩下 $j$ 次可以加的方案数。

转移时，可以枚举前一个数还剩下多少次数，记为 $pre$。再枚举当前数和前一个数加多少次，记为 $now$。手动模拟一下样例发现，有 $now \le \min(pre, h_i)$。

即 
$$f_{i, cnt_i - now} += f_{i - 1, pre}\ (now \le \min(pre, h_i))$$

枚举 $m$ 为 $O(m)$，$pre$ 为 $O(m)$，$now$ 为 $O(m)$，$i$ 为 $O(n)$。时间  $O(nm^3)$ 不优。

考虑优化转移，发现转移的本质是给一段区间加上同一个数。

差分，前缀和好像都可以，前缀和熟悉点。

时间为 $O(nm^2)$。

比较有意思的是，如果是偶数就不用枚举 $m$，否则答案会算重。

为什么，因为 $\lbrace 0, 0, 0, 0\rbrace$ 会计算到 $\lbrace 1, 1, 1, 1\rbrace$。导致多算。

# 正确性证明

鉴于机房同学提出了一个有意义的问题，在这里给个证明。

>问题：既然偶数会算重，为什么奇数不会算重？

例如，$\lbrace 0, 0, 0\rbrace$ 虽然无法到达 $\lbrace 8, 8, 8\rbrace$，但是有没有可能到达同一种答案呢？

>记 $\lbrace 8, 8, 8\rbrace$ 能够到达的一种状态为 $\lbrace a_1, a_2, a_3\rbrace$。由于第 $1$ 个数只能和第 $2$ 个数相加，则每个数怎么加都已经确定。

>则$\lbrace 8, 8, 8\rbrace$ 到 $\lbrace a_1, a_2, a_3\rbrace$ 的方法是：
>$(1, 2)$ $a_1 - 8$ 次，$(2, 3)$ $a_2 - 8 - (a_1 - 8)$ 次，最后满足 $a_2 - 8 - (a_1 - 8) = a_3 - 8$。
>
> 即 $a_2 - a_1 = a_3 - 8$

>$\lbrace 0, 0, 0\rbrace$ 到 $\lbrace a_1, a_2, a_3\rbrace$ 的方法是：
>$(1, 2)$ $a_1 - 0$ 次，$(2, 3)$ $a_2 - 0 - (a_1 - 0)$ 次，最后满足 $a_2 - 0 - (a_1 - 0) = a_3 - 0$。
>
> 即 $a_2 - a_1 = a_3$

相矛盾，故不存在奇数算重的情况。

又鉴于机房同学让我写**一般点**，那就写一般点吧。

设 $\lbrace a, a, a, \cdots, a\rbrace$ 与 $\lbrace b, b, b, \cdots, b\rbrace$ 是两种不同初始状态。即 $n$ 为奇数，$a \neq b$。

设 $\lbrace c_1, c_2, c_3, \cdots,c_n\rbrace$ 为目标状态。

从 $a$ 到 $c$ 有 $(c_{n - 1} - a - (c_{n - 2} - a- \cdots)  )= c_n - a$。

看常数项，右边有 $n - 1$ 项，每一项的 $a$ 都要变号，所以常数项为 $0$。

容易发现下标为偶数的系数为 $1$，反之为 $-1$。

所以有 $\sum_{i = 1}^{n - 1} (-1)^i \times c_i = c_n - a$。

同理有 $\sum_{i = 1}^{n - 1} (-1)^i \times c_i = c_n - b$。

因为 $a \neq b$，所以上式矛盾。故不可能存在这种状态。

# 实现
放一个丑陋的实现。暴力也在里面。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10, mod = 1e9 + 7;
typedef long long ll;
int n;
ll f[110][N], h[N], m = 1001, cnt[N];

int main() {
	freopen("drought.in","r",stdin);
	freopen("drought.out","w",stdout);
	cin >> n;
	for(int i = 1; i <= n; i ++) {
		cin >> h[i];
		m = min(m, h[i]);
	}
	ll ans = 0;
	if(n % 2 == 0) m = 0; 
	for(int i = 0; i <= m; i ++) {
		for(int j = 1; j <= n; j ++) cnt[j] = h[j] - i;
		memset(f, 0, sizeof f);
		f[1][cnt[1]] = 1;
		for(int j = 2; j <= n; j ++) {
			ll sum = 0;
			for(int pre = 0; pre <= cnt[j - 1]; pre ++) {
//				for(int now = 0; now <= min(pre, cnt[j]); now ++) {
//					f[j][cnt[j] - now] = (f[j][cnt[j] - now] + f[j - 1][pre]) % mod;
//				}
				sum = (sum + f[j - 1][pre]) % mod;
			}
			for(int now = 0; now <= cnt[j]; now ++) {
				f[j][cnt[j] - now] = (f[j][cnt[j] - now] + sum) % mod;
				sum -= f[j - 1][now];
				sum = (sum + mod) % mod;
				if(!sum) break;
			}
//			for(int now = 0; now <= cnt[j]; now ++) cout << f[j][now] << " ";
//			puts("");
		}
		for(int j = 0; j <= cnt[n]; j ++) 
		ans = (ans + f[n][j]) % mod;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：ttcwws (赞：3)

#### 我这里提供一种我考场上不同的思路：基于差分来考虑。


------------
首先，我们发现，题目中一次操作可以将 $h_i$ 和 $h_{i+1}$ 分别减去 $1$，那么我们就可以考虑差分数组 $b$，那么一次操作就是 $b_i\rightarrow b_i-1,\,b_{i+2}\rightarrow b_{i+2}+1$（下文称之为在第 $i$ 位上的操作），可以发现改变的两个数奇偶性相同，然后我们考虑按照奇数位和偶数位划分，思考什么样的差分数组满足条件。

首先，我们发现，我们的要达到的最终状态是原数组每一位都相等，对应到差分上就是除了 $b_1$ 以外的数都等于 $0$。

因为奇数和偶数互不影响，所以可以定义 $pre_i=\sum\limits_{0\leqslant j\leqslant i\ \land
\ j\equiv i(\bmod2\,)}$，也就是 $pre_1=b_1,\ pre_2=b_2,\ pre_3=b_1+b_3,\ pre_4=b_2+b_4,\ \dots$\
然后可以发现，一次在第$i$位上的操作相当于 $pre_i\rightarrow pre_i-1,\,pre_{i+2}$ 是不变的，因此 $pre$ 只减不加。这样我们就把一次操作影响的两位变成了一位，方便很多。因为奇偶位互不影响，所以可以分开考虑。

下文中标有撇号的数组，例如 $pre'$，代表操作完了之后，所有 $h_i$ 相等时的对应数组，以防混淆。对于 $pre$ 数组也就是 $pre'_1=pre'_2=\dots pre'_n=$ 最终相等的的 $h'_i$。其它同理。


------------


#### 接下来分情况讨论
如果 $n$ 是偶数，那么由于我们最终的合法的条件是差分数组在偶数位上每一位都等于 $0$，这个等价于 $\forall i\leqslant n$ 是偶数，$pre'_i=0$，然而由于 $pre$ 只减不增，开始时我们一定要满足 $pre_i\geqslant0$ 才可以。加之，因为要满足最后 $pre'_n=0$，那么开始时 $pre_n$ 只能等于 $0$，因为题目规定我们不能在第 $n$ 位，也就是最后一个偶数位上操作，使得 $pre_n$ 从一个 $>0$ 的数减为 $0$。反之，只要上面两个条件满足，一定可以构造一组解使得最终所有偶数位都等于 $0$。

那么 $i$ 是奇数呢？与偶数位的不同在于，最终 $b'_1=pre'_1$ 无需等于 $0$，然后因为其它的 $b'_i=0$，所以 $\forall i\neq 1$ 且是奇数，$pre'_i=pre'_1$，因此和上面相似（$pre$ 只增不减），推出开始时 $pre_i\geqslant pre'_1$。并且因为在最后一个奇数位，也就是第 $n-1$ 位上操作是合法的，所以也就没了 $i$ 是偶数时的第二个限制。而且无论 $pre_1$ 开始时是多少，我们可以先直接对第 $1$ 位操作，使 $pre_1$ 减为 $pre'_1=0$，这样我们就有和上面一样的 $pre_i\geqslant0$ 了。

之后我们可以就开始 $dp$ 了。

根据前面的推导，自然地设计状态 $f_{i,j}$ 表示前 $i$ 位，$pre_i=j$ 时的方案数，之后考虑决策。但我们推到这里发现，我们并不知道 $pre_i$ 的上界是多少，况且我们还有一个 $H_i$ 的限制没有用呢。$H_i$ 是限制原数组的 $h_i$ 的，所以我们把 $pre_i$ 用 $h$ 数组表示。

那么有 $pre_i=\sum\limits_{k=1}^i(-1)^{i-k}h_k$，也就是 $pre_1=h_1,\ pre_2=h_2-h_1,\ pre_3=h_3-h_2+h_1,\ \dots$，推导直接根据定义带值就可以了。

然后，因为相邻的两项的和式有很多项都之差一个符号，我们就有一个振奋人心的发现，$pre_i+pre_{i-1}=h_i$！那么，因为 $h_i\leqslant H_i$，前面推了 $pre_{i-1}\geqslant0$，我们就有 $pre_i=h_i-pre_{i-1}\leqslant H_i$！。

现在考虑决策就方便了。

我们枚举 $k=pre_{i-1}$，由于 $pre_i+pre_{i-1}=j+k=h_i\leqslant H_i$，有 $f_{i,j}=\sum\limits_{k=0}^{H_i-j}f_{i-1,k}$，最终答案就是 $f_{n,0}$，因为上文说了，$pre_n=0$，初态 $f_{0,0}=1$。因为这个柿子右侧访问的是 $f_{i-1}$ 的一段连续的区间，所以可以前缀和优化。复杂度 $O(\sum H_i)$，其实不优化 $O(\sum H_i^2)$ 也能过。


------------


其实 $n$ 是奇数的情况和偶数差不太多。

在偶数位上的情况和上面相似，只是我们现在可以在最后一个偶数位，也就是第 $n-1$ 位上操作了，所以只需满足 $pre_i\geqslant0$ 即可。

奇数位略有不同，推导过程和 $n$ 是偶数时一样，只是在最后一个奇数位，第 $n$ 位上操作变得不合法了，所以类似地，开始时 $pre_n$ 只能等于最终的 $pre'_1$。这样的话因为 $pre_n$ 改变不了，如果像上面一样将 $pre'_1$ 减为0，就漏掉了 $pre_n>pre'_1>0$ 的情况，所以只好初始时所有的 $pre_i\geqslant pre'_1$（除了 $pre_n=pre'_1$）。这个条件下，我们发现原来的 $dp$ 不太好控制，原因是 $dp$ 时我们不好枚举 $j$ 使它 $\geqslant pre'_1$。

所以我们可以多枚举一个 $0\leqslant l=pre'_1=pre_n\leqslant H_1$，然后在 $i$ 是奇数时，枚举 $j$ 时从 $l$ 开始，也就是 $f_{i,j}=\sum\limits_{k=l}^{H_i-j}f_{i-1,k}$，初态 $f_{1,j}=1(j\geqslant l)$，然后记录一个 $ans$，每次 $ans\leftarrow ans+f_{n,l}$，最后的答案就是 $ans$。

这时加了一层循环，就必须要用前缀和优化了，时间复杂度 $O(H_1\sum H_i)$。

------------


可能写得比较复杂，代码其实不复杂，具体细节看代码就好了（不要抄哦）。



------------
考场代码：
```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define ll long long
#define N 103
#define MX 1005
#define MOD 1000000007
int h[N], f[N][MX], sum[N][MX];
int read()
{
	int x = 0;
	char c, f = 1;
	while (!isdigit(c = getchar()) && c != '-');
	if (c == '-')c = getchar(), f = -1;
	while (isdigit(c))
	{
		x = x * 10 + (c ^ '0');
		c = getchar();
	}
	return x * f;
}
int main()
{
	int n = read();
	std::generate(h + 1, h + n + 1, read);
	f[0][0] = 1;
	if (n & 1)
	{
		int ans = 0;
		std::fill(f[1], f[1] + h[1] + 1, 1);
		for (int l = 0; l <= h[n]; ++l)
		{
			if (l)f[1][l - 1] = 0;
			for (int i = 2; i <= n; ++i)
			{
				sum[i - 1][0] = f[i - 1][0];
				for (int j = 1; j <= h[i]; ++j)
					sum[i - 1][j] = (sum[i - 1][j - 1] + f[i - 1][j]) % MOD;
				for (int j = (i & 1) ? l : 0; j <= h[i]; ++j)
					f[i][j] = sum[i - 1][h[i] - j];
			}
			ans = (ans + f[n][l]) % MOD;
			for (int i = 2; i <= n; ++i)
				std::fill(f[i], f[i] + h[i] + 1, 0);
		}
		printf("%d", ans);
	}
	else
	{
		for (int i = 1; i <= n; ++i)
			for (int j = h[i]; j >= 0; --j)
				f[i][j] = (f[i][j + 1] + f[i - 1][h[i] - j]) % MOD;
		printf("%d", f[n][0]);
	}
}
```



---

## 作者：Alex_Wei (赞：3)

upd on 2022.3.16：修改一处事实性表述错误。

> **[P8096 [USACO22JAN] Drought G](https://www.luogu.com.cn/problem/P8096)*

带限制的计数题首先考虑满足条件的序列具有什么性质。

将所有位置按奇偶分类（经典套路），一次操作将 $\sum h_{2k}$ 和 $\sum h_{2k + 1}$ 各减少 $1$。考虑一段前缀 $h_1\sim h_i$，当 $i$ 是奇数时，如果不满足奇数位置上 $h$ 的和（设为 $o_i$） **不小于** 偶数位置上 $h$ 的和（设为 $e_i$），即 $o_i < e_i$，那么无解：不妨设一次操作 $h_j$ 和 $h_{j + 1}$，当 $j \neq i$ 时，并不改变 $o_i$ 和 $e_i$ 的大小关系。当 $j = i$ 时，甚至还会让 $o_i - e_i$ 变小，因为 $o_i\gets o_i - 1$，$e_i$ 不变。又因为最终目标的 **必要条件** 是 $o_i - e_i \geq 0$，故无解。当 $i$ 是偶数时同理，若 $e_i < o_i$ 则无解。

对于任意前缀均满足上述条件是序列合法的 **必要条件**，这是 **大前提**。因此，不妨设 $d_i$，当 $i$ 为奇数时 $d_i = o_i - e_i$，当 $i$ 为偶数时 $d_i = e_i - o_i$，不难发现 $d_i = h_i - d_{i - 1}$， 且一次 $j = i$ 的操作会令 $d_i$ 减去 $1$。 

考虑最终序列 $h_1' = h_2' = \cdots = h_n' = k$，有  $d_1' = d_3' = \cdots = k$，且 $d_2' = d_4' = \cdots = 0$。因此，当 $n$ 是偶数时，我们能够令整个序列同时减去 $1$，故直接令 $k = 0$。当 $i$ 是奇数时，还需枚举 $k$，此时 $h$ **唯一对应** $h'$。

设计状态 $f_{i, j}$ 表示考虑到第 $i$ 位，且 $d_i = j$ 的序列数量。转移根据 $d_i = h_i - d_{i - 1}$，枚举 $h_i$：
$$
f_{i, j} = \sum_{h_i = j} ^ {H_i} f_{i, h_i - j}
$$
注意当 $i$ 是奇数时还有 $j \geq k$ 的限制。当 $n$ 是奇数时方案数为 $f_{n, k}$，对每个 $k$ 求和。当 $n$ 是偶数时 $k = 0$，方案数为 $f_{n, 0}$。使用前缀和优化以及滚动数组，时间复杂度 $\mathcal{O}(nH ^ 2)$，可以通过。获得了最优解（2022.2.4）。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5, mod = 1e9 + 7;
int n, h[N], mn = N, ans, f[2][N];
void add(int &x, int y) {x += y, x >= mod && (x -= mod);}
int calc(int v) {
	memset(f[0], 0, sizeof(f[0])), f[0][0] = 1;
	for(int i = 1, p = 1, q = 0; i <= n; i++, swap(p, q)) {
		for(int j = 1; j <= h[i]; j++) add(f[q][j], f[q][j - 1]);
		memset(f[p], 0, sizeof(f[p]));
		for(int j = i & 1 ? v : 0; j <= h[i]; j++) f[p][j] = f[q][h[i] - j];
	} return f[n & 1][v];
}
int main() {
	cin >> n; for(int i = 1; i <= n; i++) cin >> h[i], mn = min(mn, h[i]);
	if(n & 1) for(int i = 0; i <= mn; i++) add(ans, calc(i)); else ans = calc(0);
	return cout << ans << endl, 0;
}
```

---

## 作者：zhiyangfan (赞：2)

> 给出一个长为 $n$ 的序列 $h$，求出有多少个长为 $a$ 的序列满足以下条件：
> - $0\le a_i\le h_i$。
> - 能通过每次选择一个 $i(1\le i<n)$，把 $a_i,a_{i+1}$ 同时减去 $1$，进行若干次来使整个序列变成同一个非负整数。
> 
> 答案对 $10^9+7$ 取模。($1\le n\le100,1\le h_i\le10^3$)

这种题一看不像什么推式子的题，就可以考虑计数 $\rm dp$ 了。考虑设 $f_{i,j,k}(j\ge k)$ 表示对于前 $i$ 个数，第 $i$ 个数最后会变为 $j$，其他的数最后会变为 $k$ 的方案数。则注意到我们在转移时动 $k$ 并不是一个明智的选择，毕竟这牵扯到的数太多了，所以如果要从 $f_{i,j,k}$ 转移到 $f_{i+1,x,k}$，我们的目标应该是把第 $i$ 个数从 $j$ 变为 $k$。即要对 $i$ 操作恰好 $j-k$ 次，这样的话，第 $i+1$ 个数最初的值应该是 $x+j-k$，由于有条件 $1$ 的限制，所以我们有转移时 $x$ 的取值范围：
$$k\le x\le h_{i+1}-j+k$$
所以把 $\rm dp$ 方程写出来就是：
$$f_{i,j,k}=\sum_{l=0}^{h_i-j}f_{i-1,k+l,k},f_{1,j,k}=[j\le h_1]$$
随便做个前缀和就可以做到 $\mathcal{O}(nh_i^2)$ 的转移了。

接下来就是答案统计的问题了，显然最后我们要所有的数都一样，看起来答案应该是：
$$\sum_{k=0}^{\min \{h_i\}}f_{n,k,k}$$
在 $n$ 是奇数的时候，这样统计确实没错。但当 $n$ 是偶数的时候，我们是能够通过题目中所给的操作给全部的数减去某个非负整数的，所以本质上所有 $f_{n,k,k}$ 都被 $f_{n,0,0}$ 包含，此时答案即为 $f_{n,0,0}$。

这样直接实现可能有点麻烦，这里参考了 USACO 官方的实现方法。考虑我们刚刚关心的只是 $j,k$ 的差，所以我们新设一个状态 $f_{i,l}$ 表示前 $i$ 个，$j-k=l$ 的方案数。这样把第一维滚动掉后，实现就非常简洁了。我们需要对每个 $k$ 都做一次，注意 $0\le k\le \min\{h_i\}$，每次做的时候只需要令 $h_i$ 为 $h_i-k$ 就可以方便实现边界赋值和转移条件。时间复杂度依然是 $\mathcal{O}(nh_i^2)$，但空间省掉不少。
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N = 110, M = 1100, mod = 1e9 + 7; int f[M], pre[M], h[N];
int main()
{
	int n, mn = M, ans = 0; scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &h[i]), mn = std::min(mn, h[i]);
	do
	{
		for (int i = 0; i <= h[1]; ++i) pre[i] = i + 1;
		for (int i = h[1] + 1; i <= 1000; ++i) pre[i] = h[1] + 1;
		for (int i = 2; i <= n; ++i)
		{
			memset(f, 0, sizeof (f));
			for (int j = 0; j <= h[i]; ++j) f[j] = pre[h[i] - j];
			pre[0] = f[0];
			for (int j = 1; j <= 1000; ++j) pre[j] = (pre[j - 1] + f[j]) % mod;
		}
		(ans += pre[0]) %= mod;
		for (int i = 1; i <= n; ++i) --h[i];
	}while ((n & 1) && mn--);
	printf("%d\n", ans); return 0;
}
```

---

## 作者：pengyule (赞：1)

一道难度小于提高 T2 的简单 dp 优化题。

一个显然的性质是：对于一个确定的 $h$ 数组，如果有解，那么按照“先操作 $(n-1,n)$ 若干次把 $h_n$ 变成 $0$、再操作 $(n-2,n-1)$ 若干次把 $h_{n-1}$ 变成 $0$……”一定最后可以都变成 $0$（当然不一定是 $0$，这里只是举个例子）。

一个最初的想法是枚举公共高度 $\mathfrak U$，那么把 $H_1,H_2,...,H_n$ 都减去 $\mathfrak U$，再进行如下的暴力 DP：  
设 $\mathfrak{F}(i,j)$ 表示前 $i$ 个数，第 $i$ 个数已经被 $i+1$ 操作了 $j$ 次的情况下，$i$ 元组 $(h_1,h_2,...,h_i)$ 有几种合法方案。转移显然：$\mathfrak{F}(i,j)=\sum_{k=j}^{H_i}\mathfrak{F}(i-1,k-j)$。边界是 $\mathfrak F(1,0)=\mathfrak F(1,1)=...=\mathfrak F(1,H_1)=1$。复杂度 $O(nH^2)$。

直觉告诉我们这个公共高度的枚举十分多余，转而我们就发现对于 $n$ 为偶数的情况，每一种有解情况我们钦定都变成 $0$ 亦有解，因为当你把它都变成同一高度 $\mathfrak U$ 时，将 $(1,2),(3,4),...,(n-1,n)$ 再各操作 $\mathfrak U$ 次就都变成 $0$ 了。这样一来，对于 $n$ 为偶数的情况，直接做上面的 DP 并取 $\mathfrak F(n,0)$ 即为答案。

对于奇数的情况我们似乎感到没有进一步优化空间，转而看到转移可以表示为 $\mathfrak{F}(i,j)=\sum_{k=0}^{H_i-j}\mathfrak{F}(i-1,k)$，我们便自然地想到前缀和优化，也就是说 DP 可以做到 $O(nH)$。这样一来我们完全可以枚举 $\mathfrak U$ 了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,mnh=mod,H[105],f[105][1005];
inline void add(int &x,int y){(x+=y)>=mod&&(x-=mod);}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&H[i]),mnh=min(mnh,H[i]);
	for(int i=0;i<=H[1];i++)f[1][i]=1;for(int i=1;i<=1000;i++)add(f[1][i],f[1][i-1]);
	for(int i=2;i<=n;i++){
		for(int j=0;j<=H[i];j++)f[i][j]=f[i-1][H[i]-j];
		for(int j=1;j<=1000;j++)add(f[i][j],f[i][j-1]);
	}
	if(n&1){
		int sum=0;
		for(int i=0;i<=mnh;i++){
			memset(f,0,sizeof f);
			for(int i=0;i<=H[1];i++)f[1][i]=1;for(int i=1;i<=1000;i++)add(f[1][i],f[1][i-1]);
			for(int i=2;i<=n;i++){
				for(int j=0;j<=H[i];j++)f[i][j]=f[i-1][H[i]-j];
				for(int j=1;j<=1000;j++)add(f[i][j],f[i][j-1]);
			}
			add(sum,f[n][0]);
			for(int j=1;j<=n;j++)H[j]--;
		}
		cout<<sum;
	}
	else cout<<f[n][0];
}
```

---

## 作者：_Diu_ (赞：1)

提供一个不一样的 dp 做法。

## dp

我们可以先不管全都相同的限制，要求把所有奶牛都喂饱。

我们发现，$1$ 号奶牛一定要和  $2$ 号奶牛一起被喂。所以要求 $h_1\le h_2$，然后同时投喂 $h_1$ 给个玉米，此时 $2$ 号奶牛还需要吃 $h_2-h_1$。

此时 $1$ 号奶牛被喂饱，要喂 $2$ 号奶牛，就只能和 $3$ 号奶牛一起喂，所以要求 $h_2-h_1\le h_3$，然后同是投喂 $h_2-h_1$，$3$ 号奶牛还需要吃 $h_3-h_2+h_1$。

$\dots$

最后如果喂完第 $n-1$ 只奶牛都合法，并且此时刚好吧第 $n$ 只奶牛也喂饱了，这个方案就合法。

形式化地，如果 `FJ` 能把所有奶牛喂饱，需要满足一下条件：

- $\forall i\in (1,n],h_i\ge\sum_{j=1}^{i-1}(-1)^{i-j+1}h_i$

- $\sum_{j=1}^n(-1)^{n-j+1}h_i=0$

我们设 $s_i$ 表示 `FJ` 需要投喂 $(i,i+1)$ 这对奶牛多少次。

则有 $s_0=0,s_i=h_i-s_{i-1}$。

判断条件也可以用 $s$ 来表示。

- $\forall i\in [1,n],s_i\ge 0$

- $s_n=0$

发现一个如果规定一个数组 $s$，我们可以唯一确定一个数组 $h$，

所以我们考虑把 $h$ 加到 $s$ 的判断条件里。

- $\forall i\in [1,n]s_i+s_{i-1}=h_i$

表示每只奶牛需要被投喂多少次。

我们发现这个条件非常好判断，可以很愉快的 `dp`。

设 $f_{i,j}$ 表示前 $i$ 个 $s$，其中 $s_i=j$ 的合法方案数。

转移显然：

$$
f_{i,j}=\sum_{k=0}^{\min(h_{i-1},h_i-j)}f_{i-1,k}
$$

答案就是 $f_{n,0}$。

显然可以前缀和优化，做到 $O(nh)$。

```cpp
int dp(){
	f[0][0]=s[0][0]=1;
	for(int i=1;i<=n;i++){
		up[i]=min(h[i],h[i+1]);
		for(int j=0;j<=up[i];j++){
			f[i][j]=s[i-1][min(up[i-1],h[i]-j)];
			s[i][j]=(s[i][j-1]+f[i][j])%p;
		}
	}
	return f[n][0];
}
```

回到题目，题目只要保持所有奶牛剩余投喂量相同就行了，

如果有偶数只奶牛，我们可以把着拆成两两投喂，只需要统计全部喂完的情况，不重不漏。

如果有奇数只奶牛，我们发现所有奶牛的 $h_i$ 相同时，不存在合法投喂方案，这些情况中时不会有重复的，我们只要枚举每一种保留投喂的数量，暴力算出所对应的 $f_{n,0}$，全部加起来即可。

## code

~~代码里的输出答案被隔壁家小孩偷走了。~~

```cpp
#include<bits/stdc++.h>//odd: O(n^2h)  even: O(nh)
#define int long long
using namespace std;
const int N=110,M=1010,p=1e9+7;
int n,h[N],up[N],f[N][M],s[N][M];
int dp(){
	f[0][0]=s[0][0]=1;
	for(int i=1;i<=n;i++){
		up[i]=min(h[i],h[i+1]);
		for(int j=0;j<=up[i];j++){
			f[i][j]=s[i-1][min(up[i-1],h[i]-j)];
			s[i][j]=(s[i][j-1]+f[i][j])%p;
		}
	}
	return f[n][0];
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&h[i]);
	int ans=dp();
	if(n&1){
		int mn=h[1];
		for(int i=2;i<=n;i++)mn=min(mn,h[i]);
		for(;mn--;){
			for(int i=1;i<=n;i++)--h[i];
			ans=(ans+dp())%p;
		}
	}
}
```

---

## 作者：djh0314 (赞：0)

### [传送门](https://www.luogu.com.cn/problem/P8096)

### 题意
对于 $n$ 头牛，给予每头牛的最大值 $H_i$，问一共有多少种方法可以满足下面的要求。

每次将两个相邻的值 -1，   
使最后的值全部相同。

### 分析 
首先分析我们在如何情况下可以满足我们的要求，     
显然我们可以从左边开始，将当前位与其右边的位一起下降，      
直至当前位的值与我们最终的值相同，倘若出现负数则不可行，倘若最后一位无法清 0，不可行。

可以解决前 4 个点。
### 优化
我们先枚举最终的值，然后我们发现最终的方案数只与我们前一位所遗留下来的数有关，显然我们可以用 dp 解决此题。     
转移：
~~~cpp
for(int j=3; j<=n; ++j) {
	for(int k=0; k<=a[j-1]; ++k) {
		for(int q=k; q<=a[j]; ++q) {
			f[j][q-k]+=f[j-1][k];
			f[j][q-k]%=MOD;
		}
	}
}
~~~
对于每一个最终值，
时间复杂度 $O(n\times H^2)$。      
但是此时我们可以发现，我们枚举每一个终值并不能愉快的拿到我们的部分分，甚过不了样例。

可以发现，当我们的数字数量为偶数时，我们相同的一种排列，最终可以到达好多种最终值，因此我们在偶数时只用判断 0。

### 正解 
就是简单化一下式子可以得到，$f_{j,k}=\sum_{q=0}^{a[j]-k} f_{j-1,q}$。     

很明显，我们可以用前缀和解决该问题。

[Code](https://www.luogu.com.cn/paste/3oq0xupr)。

---

## 作者：StillEmpty (赞：0)

目标进度：第（2/100）篇USACO金组题解。

初步分析，设操作后都为 $k$（显然 $0 \le k \le \min{h_i}$），则第一、二个被减去 $h_1 - k$，第二、三个被减去 $h_2 - h_1$，第三、四个被减去 $h_3 - h_2 + h_1 - k$，第四、五个被减去 $h_4 - h_3 + h_2 - h_1$，以此类推。

所以若 $n$ 为奇数，
$$
k = \sum_{i = 1}^n (-1)^{i-1} h_i
$$
是能全部操作成 $k$ 必要条件。之所以不是充分必要条件，是因为 还需要保证 $h_1 -k, h_2 - h_1, h_3 - h_2 + h_1 - k, \cdots \ge 0$。这告诉我们，当 $n$ 为奇数时，若存在 $k$，也只会存在一个，所以我们可以枚举 $k$ 再算出操作后全是 $k$ 的方案数。

若 $n$ 为偶数，
$$
\sum_{i = 1}^n (-1)^{i-1} h_i = 0
$$
时能操作成一个数。也就是说，如果 $n$ 为偶数，$k$ 可能若干取值。这其实可以直观简单的理解：当 $n$ 为偶数时，我们可以将所有数减去同样的值（一、二操作，三、四操作……），所以若 可以全变成 $k$，也可以全变成 $k-1$，以此类推。所以全变成 $0$ 的方案数就是总的方案数。

这就变成了一个可以用dp解决的问题：确定操作后全变成 $k$，总共有多少种方案。考虑到一个数只会被覆盖它的两个减法操作改变，且减法操作影响，我们可以设计dp状态 $f_{i, j}$ 表示 $(i,i+1)$ 被减去 $j$ 的情况下前 $i$ 个数的方案数。

易得动态转移式：
$$
f_{i,j} = \sum_{\Delta = 0}^{h_i-k-j} f_{i-1, \Delta}
$$

显然这个和式可以用前缀和维护，总时间复杂度降至 $O(n(\max{h_i})^2)$：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100, H = 1000, MOD = 1e9+7;
int n, h[N+1], minh = 1001, ans;
int f[N+1][H+1];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> h[i]; minh = min(minh, h[i]);
    }
    for(int same = 0; same <= minh; ++same) {
        memset(f, 0, sizeof(f));
        for(int i = same; i <= h[1]; ++i) f[1][i-same] = 1;
        for(int i = 2; i <= n; ++i) {
            for(int j = 1; j <= H; ++j) f[i-1][j] = (f[i-1][j]+f[i-1][j-1])%MOD;
            for(int j = 0; j <= h[i]-same; ++j) {
                f[i][j] = f[i-1][h[i]-same-j];
            }
        }
        ans = (ans+f[n][0])%MOD;
        if(n%2 == 0) break;
    }
    cout << ans << endl;
    return 0;
}
```

---

