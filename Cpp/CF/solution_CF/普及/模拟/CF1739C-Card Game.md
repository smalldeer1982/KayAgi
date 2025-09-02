# Card Game

## 题目描述

Consider a game with $ n $ cards ( $ n $ is even). Each card has a number written on it, between $ 1 $ and $ n $ . All numbers on the cards are different. We say that a card with number $ x $ is stronger than a card with number $ y $ if $ x > y $ .

Two players, Alex and Boris, play this game. In the beginning, each of them receives exactly $ \frac{n}{2} $ cards, so each card belongs to exactly one player. Then, they take turns. Alex goes first, then Boris, then Alex again, and so on.

On a player's turn, he must play exactly one of his cards. Then, if the opponent doesn't have any cards stronger than the card played, the opponent loses, and the game ends. Otherwise, the opponent has to play a stronger card (exactly one card as well). These two cards are removed from the game, and the turn ends. If there are no cards left, the game ends in a draw; otherwise it's the opponent's turn.

Consider all possible ways to distribute the cards between two players, so that each of them receives exactly half of the cards. You have to calculate three numbers:

- the number of ways to distribute the cards so that Alex wins;
- the number of ways to distribute the cards so that Boris wins;
- the number of ways to distribute the cards so that the game ends in a draw.

You may assume that both players play optimally (i. e. if a player can win no matter how his opponent plays, he wins). Two ways to distribute the cards are different if there is at least one card such that, in one of these ways, it is given to Alex, and in the other way, it is given to Boris.

For example, suppose $ n = 4 $ , Alex receives the cards $ [2, 3] $ , and Boris receives the cards $ [1, 4] $ . Then the game may go as follows:

- if Alex plays the card $ 2 $ , then Boris has to respond with the card $ 4 $ . Then, Alex's turn ends, and Boris' turn starts. Boris has only one card left, which is $ 1 $ ; he plays it, and Alex responds with the card $ 3 $ . So, the game ends in a draw;
- if Alex plays the card $ 3 $ , then Boris has to respond with the card $ 4 $ . Then, Alex's turn ends, and Boris' turn starts. Boris has only one card left, which is $ 1 $ ; he plays it, and Alex responds with the card $ 2 $ . So, the game ends in a draw.

So, in this case, the game ends in a draw.

## 说明/提示

In the first test case, Alex wins if he receives the card $ 2 $ (he plays it, and Boris cannot respond). If Alex receives the card $ 1 $ , the game ends in a draw.

In the second test case:

- Alex wins if he receives the cards $ [3, 4] $ , $ [2, 4] $ or $ [1, 4] $ ;
- Boris wins if Alex receives the cards $ [1, 2] $ or $ [1, 3] $ ;
- the game ends in a draw if Alex receives the cards $ [2, 3] $ .

## 样例 #1

### 输入

```
5
2
4
6
8
60```

### 输出

```
1 0 1
3 2 1
12 7 1
42 27 1
341102826 248150916 1```

# 题解

## 作者：Sycamore_Ma (赞：13)

## 题目链接
Educational Codeforces Round 136 (Rated for Div. 2), Problem C
[1739C Card Game](https://codeforces.com/problemset/problem/1739/C)

## 题目大意
游戏牌堆中含偶数 $n$ 张牌，每张牌上的数字不同，且大小在 $1$ 到 $n$ 之间（即给定 **$1$ 到 $n$ 的全排列牌**，又称 **permutation**）。两名玩家 A、B 都会在开局分得牌堆中的 $\frac{n}{2}$ 张牌，手牌互异，点数随机。
首先玩家 A 出牌，对手 B 应牌（对手**应牌点数需比出牌者大**，且丢弃），然后玩家 B 出牌，对手 A 应牌，依次轮转，直至**一人无法应牌判定其为输**（无更大牌可应），或**双方手牌为空判定平局**（双方皆空手无牌可出）。
给定牌的张数 $n$，求能使 A 获胜的发牌方式数、能使 B 获胜的发牌方式数、能使双方平局的发牌方式数。

---
## 解法

### *定义*
 - $a_i$：总牌数为 $i$ 时玩家 A 获胜的发牌方式数；
 - $b_i$：总牌数为 $i$ 时玩家 B 获胜的发牌方式数；
 - $t_i$：总牌数为 $i$ 时双方平局的发牌方式数。

### _初始状态_
$a_2 = 1, b_2 = 0, t_2 = 1$.

### _状态转移_
由于 $i$ 张牌互异，发牌方式共有组合数 $\tbinom{i}{\frac{i}{2}}$ 种。

- 从样例不难发现， $t_i\equiv1$.

> $t_i\equiv1$，证明采用演绎法，假设有 $n$ 张牌：
> - 若 A 拿到点数为 $n^\#$ 的牌，且首张打出该手牌，则 A 必胜，**为保证平局**，**B 需拿到点数为 $n^\#$ 的牌**；
> - 若 B 同时拿到点数为 $(n-1)^\#$ 的牌，B 打出该牌 A 将无 $n^\#$ 可应，则 B 必胜，**为保证平局**，**A 需拿到点数为 $(n-1)^\#$ 的牌**；
> - 若 B 同时拿到 $(n-2)^\#$，A 无论首次走出什么牌，B 在应牌后都能保证在下一轮持有场上最大牌，**为保证平局**，**A 需拿到 $(n-2)^\#$**；
> - 依此演绎，**B 需拿到 $(n-3)^\#$、$(n-4)^\#$**，**A 需拿到 $(n-5)^\#$、$(n-6)^\#$**；
> - ...
> 
> 此演绎可确定 $n$ 仅对应唯一一种可导致平局的发牌方式

- 考虑总牌数从 $i-2$ 到 $i$ 的每轮转移，牌堆都会增加两张牌 $(i-1)^\#, i^\#$，**$a_i$ 的转移前驱共含三种类型贡献**：
	- 若 A 分得最大牌 $i^\#$ 和次大牌 $(i-1)^\#$，A 立即打出最大牌必胜，贡献数为 $\tbinom{i-2}{\frac{i}{2}-2}$，即 A 从剩余的 $i-2$ 中抽取 $\frac{i}{2}-2$ 张牌的种类数；
	- 若 A 分得最大牌 $i^\#$，B 分得次大牌 $(i-1)^\#$，A 立即打出最大牌必胜，贡献数为 $\tbinom{i-2}{\frac{i-2}{2}}$，即 A 从剩余的 $i-2$ 中抽取 $\frac{i-2}{2}$ 张牌的种类数；
	- 若 A 分得次大牌 $(i-1)^\#$，B 分得最大牌 $i^\#$，A 立即打出次大牌逼 B 以最大牌应手，此时轮转到 B 出牌，**总牌数为 $i$ 时 A 的必胜态数问题，转变为总牌数为 $i-2$ 时后手的必胜态数问题**，贡献数为 $b_{i-2}$；
	- ~~若 B 分得最大牌和次大牌，A 必败，贡献为零。~~ 
    
> 即 $a_i = \tbinom{i-2}{\frac{i}{2}-2} + \tbinom{i-2}{\frac{i-2}{2}} + b_{i-2}$.

- 考虑到 A 胜态数 $a_i$、B 胜态数 $b_i$ 以及平局态数 $t_i$ 共同组成了发牌种数 $\tbinom{i}{\frac{i}{2}}$，做差值即可得 B 胜态数：

> 即 $b_i = \tbinom{i}{\frac{i}{2}} - a_i - t_i$，又可写成 $b_i = \tbinom{i}{\frac{i}{2}} - a_i - 1$.

一些实例：

```cpp
a[2] = 1;   b[2] = 0;   t[2] = 1;
a[4] = 3;   b[4] = 2;   t[4] = 1;
a[6] = 12;  b[6] = 7;   t[6] = 1;
a[8] = 42;  b[8] = 27;  t[8] = 1;
```

---
## 代码

> 组合数递推公式：$C_n^m = C_{n-1}^{m-1} + C_{n-1}^{m}$，又或写成 $\tbinom{n}{m} = \tbinom{n-1}{m-1} + \tbinom{n-1}{m}$.

创建组合数数组 `c[maxn][maxn]` 并打表，并按上节状态转移方法递推，输出 $n$ 张牌时的 A 胜种数 `a[n]`、B胜种数 `b[n]` 和平局种数 `t[n]`，代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MOD 998244353

const int maxn = 100 + 10;
long long int a[maxn];
long long int b[maxn];
long long int t[maxn];
long long int c[maxn][maxn];

void table(){
    for (int i = 0; i <= 60; i ++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j ++) {
            c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
        }
    }
    
    a[2] = 1;   b[2] = 0;   t[2] = 1;
    for (int i = 4; i <= 60; i += 2){
        t[i] = 1;
        a[i] = c[i-2][(i/2)-2] + c[i-2][(i-2)/2] + b[i-2];
        a[i] %= MOD;
        b[i] = MOD + MOD + c[i][i/2] - a[i] - 1;
        b[i] %= MOD;
    }
}

int main()
{
    int tt;
    cin >> tt;
    table();
    while (tt --){
        int n;
        cin >> n;
        cout << a[n] << " " << b[n] << " " << t[n] << endl;
    }
    return 0;
}
```

---
## 官方题解
[BledDest](https://codeforces.com/profile/BledDest) 借助了一些串上位 DP 的思想，并可采用 Java、Python 长整数递推。
[Tutorial](https://codeforces.com/blog/entry/107461)

---

## 作者：Hedgehog_210508 (赞：8)

**题目传送门**：[here](https://www.luogu.com.cn/problem/CF1739C)

**思路**：

对于平局的情况，每轮后手都有比先手大的牌，手牌固定，只有一种；

显然，如果 Alice 有 $n$ 这个数，第一轮就获胜，其他数任意取；

若 Bob 有 $n$，则无论 Alice 出什么数，情况转换为 $n-2$ 时的 Alice 后手情况（大小关系之间不影响，去掉第一轮 Alice 和 Bob 出的牌，其他可以平移，试做 $1$ 至 $n-2$）。

组合数使用快速幂和逆元处理。

**代码**：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define M 998244353
ll t,f[109],g[109],p[109];
ll qp(ll a,ll b){
	if(b==1) return a;
	if(b==0) return 1;
	ll ans=1;
	if(b%2) b--,ans*=a;
	ll tmp=qp(a,b/2);
	ans*=tmp%M*tmp%M;
	return ans%M;
}
ll c(ll a,ll b){
	return p[a]%M*qp(p[b],M-2)%M*qp(p[a-b],M-2)%M; 
}
int main(){
	std::ios::sync_with_stdio(false);
	cin>>t;
	f[2]=1,p[1]=1;
	for(ll i=2;i<=100;i++) p[i]=p[i-1]*i%M;
	for(ll i=4;i<=100;i+=2){
		f[i]=g[i-2];
		f[i]+=(c(i-1,i/2-1))%M;
		f[i]%=M;
		g[i]=(c(i,i/2)%M-f[i]+M-1)%M;
	}
	while(t--){
		ll n;
		cin>>n;
		cout<<f[n]<<' '<<g[n]<<' '<<1<<endl;
	}
	return 0;
}

```


---

## 作者：XenonWZH (赞：2)

[更好的阅读体验请点这](https://xenonwzh.github.io/cf-1739c/)

# 题意描述

[Codeforces 链接](https://codeforces.com/problemset/problem/1739/C)

Alice 和 Bob 玩游戏，游戏中有 $n$ 张标有 $1 \sim n$ 数字卡牌（$n$ 为偶数），开局时 Alice 和 Bob 均有 $\frac{n}{2}$ 张。在每一轮中，其中一人先打出自己一张卡牌，然后另一人再打出自己的一张卡牌。若后手无法打出比前一人打出卡牌数字大的卡牌，则后手输；否则进入下一轮。该轮的后手为下一轮的先手。若卡牌打完则平局。在这个游戏中，Alice 为第一轮的先手。假设双方均按最优策略出牌，求 Alice 赢、Bob 赢和平局的情况数。答案对 $998244353$ 取模。

# 解题思路

对于每一轮，我们显然可以得出：若先手有目前双方未打出的最大的牌，则先手打出这张牌必胜，否则后手可打出更大的牌结束该轮。于是我们只考虑最大的牌和次大的牌，分别分情况讨论：

1. 先手拥有最大的牌，则先手必胜；
2. 后手同时拥有最大的牌和次大的牌，则先手必输；
3. 先手拥有次大的牌，后手拥有最大的牌，此时的最优策略是先手打掉次大的牌，后手打掉最大的牌，进入下一轮。

对于每一种情况，我们用组合数学求出即可。我们存储 Alice 和 Bob 赢的情况，将 $n$ 从大到小两两一组讨论，假设最大牌为 $i$：

1. 对于情况 $1$，先手获胜情况数加 ${i - 1 \choose \frac{n}{2} - 1 - \frac{n - i}{2}}$，即先手的剩下的卡牌为在 $i - 1$ 个数中选择的情况数；
2. 对于情况 $2$，后手获胜情况数加 ${i - 2 \choose \frac{n}{2} - \frac{n - i}{2}}$，即后手的剩下的卡牌在 $i - 2$ 个数中选择的情况数。

每讨论完一组就换先手继续讨论。平局的情况数显然为 $1$，这样我们就可以得出获胜的情况数了。

# 代码演示

```cpp
#include <cstdio>
#include <iostream>

const int MAXN = 60;
const int MOD = 998244353;

long long fac[MAXN + 1], inv[MAXN + 1], facInv[MAXN + 1], f[MAXN + 1];

inline int C(const int n, const int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0) return 1;
    return fac[n] * facInv[k] % MOD * facInv[n - k] % MOD;
}

inline long long lucas(long long n, long long k) {
    if (!k) return 1;
    return C(n % MOD, k % MOD) * lucas(n / MOD, k / MOD) % MOD;
}

inline void prepare() {
    fac[0] = 1;
    for (int i = 1; i <= MAXN; i++) fac[i] = fac[i - 1] * i % MOD;

    inv[1] = 1;
    for (int i = 2; i <= MAXN; i++) inv[i] = ((-(MOD / i) * inv[MOD % i]) % MOD + MOD) % MOD;

    facInv[0] = 1;
    for (int i = 1; i <= MAXN; i++) facInv[i] = facInv[i - 1] * inv[i] % MOD;

    f[0] = 0, f[1] = 0, f[2] = 1;
    for (int i = 3; i <= MAXN; i++) {
        f[i] = (i - 1) * (f[i - 1] + f[i - 2]) % MOD;
    }
}

void solve() {
    int n;

    scanf("%d", &n);

    long long ans1 = 0, ans2 = 0;
    bool flag = true;
    for (int i = n; i >= 1; i -= 2) {
        if (flag) {
            ans1 = (ans1 + lucas(i - 1, n / 2 - 1 - (n - i) / 2)) % MOD;
            ans2 = (ans2 + lucas(i - 2, n / 2 - (n - i) / 2)) % MOD;
        } else {
            ans2 = (ans2 + lucas(i - 1, n / 2 - 1 - (n - i) / 2)) % MOD;
            ans1 = (ans1 + lucas(i - 2, n / 2 - (n - i) / 2)) % MOD;
        }
        flag ^= true;
    }

    printf("%lld %lld 1\n", ans1, ans2);
}

int main() {
    prepare();

    int t;

    scanf("%d", &t);

    while (t--) solve();

    return 0;
}
```


---

