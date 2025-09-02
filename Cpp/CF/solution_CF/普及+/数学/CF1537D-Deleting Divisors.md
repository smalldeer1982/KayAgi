# Deleting Divisors

## 题目描述

Alice and Bob are playing a game.

They start with a positive integer $ n $ and take alternating turns doing operations on it. Each turn a player can subtract from $ n $ one of its divisors that isn't $ 1 $ or $ n $ . The player who cannot make a move on his/her turn loses. Alice always moves first.

Note that they subtract a divisor of the current number in each turn.

You are asked to find out who will win the game if both players play optimally.

## 说明/提示

In the first test case, the game ends immediately because Alice cannot make a move.

In the second test case, Alice can subtract $ 2 $ making $ n = 2 $ , then Bob cannot make a move so Alice wins.

In the third test case, Alice can subtract $ 3 $ so that $ n = 9 $ . Bob's only move is to subtract $ 3 $ and make $ n = 6 $ . Now, Alice can subtract $ 3 $ again and $ n = 3 $ . Then Bob cannot make a move, so Alice wins.

## 样例 #1

### 输入

```
4
1
4
12
69```

### 输出

```
Bob
Alice
Alice
Bob```

# 题解

## 作者：liangbowen (赞：34)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1537D)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17000850.html)

遇到这种博弈论的题目，当然是要**打表找规律**了！

## 思路

首先，很容易想到[暴力递推](https://www.luogu.com.cn/paste/itqu247j)。

代码在上方的链接里。然后看几眼就能发现，在大部分情况下，如果 $n$ 是偶数那么 Alice 获胜，否则 Bob 获胜。

再多看几眼，会发现：有些地方 $n$ 是偶数，但是仍然是 Bob 获胜！

于是，我们再打表，单独看这些地方。然后就会发现：

![](https://cdn.luogu.com.cn/upload/image_hosting/60ia8l0j.png)

这些数有什么特点呢？很容易想到，$2 = 2^1$，$8 = 2^3$，$32 = 2^5$，$128 = 2^7$，以此类推。

换句话说，只要 $n = 2^{k}$（$k$ 是奇数），那么这种情况就是特例，是 Bob 获胜。

然后写成代码就行。

## 代码

代码内有一个 `map`，里面存储的是上述的特殊值。这个也是可以[打表](https://www.luogu.com.cn/paste/8hne279g)的。

```cpp
#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
map <int, bool> zlt;
bool solve()
{
	int n;
	scanf("%d", &n);
	if (zlt[n]) return false; //可以理解为特判
	return (n % 2 == 0); //奇数就是Bob，偶数就是Alice
}
int main()
{
	zlt[2] = zlt[8] = zlt[32] = zlt[128] = zlt[512] = zlt[2048] = zlt[8192] = zlt[32768] = zlt[131072] = zlt[524288] = zlt[2097152] = zlt[8388608] = zlt[33554432] = zlt[134217728] = zlt[536870912] = true;
	ios::sync_with_stdio(false);
	int T;
	scanf("%d", &T);
	while (T--)
		if (solve()) puts("Alice");
		else puts("Bob");
	return 0;
}
```

 希望能帮助到大家！

---

## 作者：Little09 (赞：15)

### 前言

挺有意思的结论题，虽然我是打表找规律的（比赛的时候确实打表找规律更好用）。

------------

### 题意

给定一个正整数 $n$，Alice 和 Bob 轮流操作，每次操作减去当前的数一个不是 $1$ 和它本身的约数。谁不能操作谁输。Alice 先操作，请问谁有必胜策略。

------------
### 分析

我们分下面 $3$ 种情况讨论：

1. 当前的数 $n$ 是个奇数；
2. 当前的数 $n$ 是偶数但不是 $2$ 的幂。
3. 当前的数 $n$ 是 $2$ 的幂。

- 第 $1$ 种情况：由于 $n$ 是奇数，那么选择的 $n$ 的约数 $k$ 肯定也是奇数，而且由于 $k|n$ 和 $k|k$，所以 $k|(n-k)$，所以 $n-k$ 一定不是 $2$ 的次幂（因为有约数 $k$），转化为第 $2$ 种情况。

- 第 $2$ 种情况：接下来我们要证明面对这种情况是必胜的。由于 $n$ 是偶数但不是 $2$ 的幂，那么一定存在一个奇数非 $1$ 约数 $k$，考虑让 $n$ 减掉这个 $k$，就转化为第 $1$ 种情况。而这样循环会在哪一步结束呢？很显然是在第 $1$ 种情况结束，因为第 $2$ 种情况的操作是无论 $n$ 为任意满足条件的值都可以进行的，而第 $1$ 种情况的会在面对质数的时候停止。

至此我们证明了第 $1$ 种情况必败，第 $2$ 种情况必胜。

- 第 $3$ 种情况：$n$ 是 $2$ 的幂时，我们可以减去 $\frac{n}{2}$ 使得 $n$ 仍然是第 $3$ 种情况，也可以减去一个其他数使得转化为第 $2$ 种情况。但是第 $2$ 种情况是必胜的，所以不应该转化为第 $2$ 种情况。于是唯一的选择就是对半减。所以 $n$ 是 $2$ 的奇数次幂时必败，$n$ 是 $2$ 的偶数次幂时必胜。



------------

### 核心代码

```cpp
int T=read();
while (T--)
{
	ll x=read();
	ll p=2;
	while (p<x) p*=4;
	if (p==x||x%2==1) cout << "Bob\n";
	else cout << "Alice\n";
}
```


---

## 作者：Aestas16 (赞：6)

[更好的阅读体验](https://wp.aestas16.top/archives/cf1537d/)

---

显然这种题我们可以打个表来帮助我们思考问题。

枚举 $i$ 的每一个非 $1$ 和 $i$ 的因数 $j$，判断 $i-j$ 是否为必败态，若是，则 $i$ 为必胜态；反之 $i$ 为必败态。

可以采用复杂度为 $\Theta(n\sqrt{n})$ 的代码进行打表：
```cpp
/*
    I will never forget it.
*/

// 392699

#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e3;

bool f[N + 10];

// f[i] 为 1 表示先手必胜
// f[i] 为 0 表示先手必败

struct OI {
    int RP, score;
} CSPS2021, NOIP2021;

signed main() {
    CSPS2021.RP++, CSPS2021.score++, NOIP2021.RP++, NOIP2021.score++, 392699;
    f[1] = 0, f[2] = 0, f[3] = 0, f[4] = 1;
    for (int i = 5; i <= N; i++) {
        for (int j = 2; j * j <= i; j++)
            if (i % j == 0 && (f[i - j] == 0 || f[i - i / j] == 0)) {
                f[i] = 1;
                break;
            }
    for (int i = 1; i <= N; i++)
        printf("f[%d] = %d\n", i, f[i]);
    return 0;
}
```
观察程序的输出可以发现当 $i$ 为奇数时先手必败，但是也有若干个偶数是先手必败的，为了使分析更加方便，我们修改代码使其只输出先手必败的偶数：
```cpp
/*
    I will never forget it.
*/

// 392699

#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e3;

bool f[N + 10];

// f[i] 为 1 表示先手必胜
// f[i] 为 0 表示先手必败

struct OI {
    int RP, score;
} CSPS2021, NOIP2021;

signed main() {
    CSPS2021.RP++, CSPS2021.score++, NOIP2021.RP++, NOIP2021.score++, 392699;
    f[1] = 0, f[2] = 0, f[3] = 0, f[4] = 1;
    for (int i = 5; i <= N; i++) {
        for (int j = 2; j * j <= i; j++)
            if (i % j == 0 && (f[i - j] == 0 || f[i - i / j] == 0)) {
                f[i] = 1;
                break;
            }
    for (int i = 1; i <= N; i++)
        if (f[i] == 0 && i % 2 == 0) printf("f[%d] = %d\n", i, f[i]);
    return 0;
}
```
观察输出发现，当 $i$ 为偶数时只有 $i \in \{2^{2k+1}, k \in \mathbb{N}\}$ 的时候是先手必败。

按照发现的规律进行判断即可，代码在[这里](https://codeforces.ml/contest/1537/submission/119933928)。


---

## 作者：pomelo_nene (赞：5)

是一个博弈问题。每次给定一个数 $n$，你可以令这个数减去它的非 $1$ 或本身的因子，不能操作的人失败。问先手是否必胜。

考虑证明几个简单结论：

1. $n=1$ 时，先手必败；   
2. $n$ 为素数时，先手必败；   

上面两个结论显然。

3. $n$ 为奇数时，$n$ 只能被变为偶数。

$n$ 为奇数意味着 $n$ 的质因数分解中没有 $2$。那么其所有因子都是奇数，因此 $n$ 只能被变为偶数。

4. $n$ 为偶数时，$n$ 可以被变为奇数。

显然。将 $n$ 除以 $2$ 即可。

将奇数、偶数与必败必胜勾连起来。除了 $n=2$ 的情况下，所有的已知必败态都是奇数，那么将奇数视作必败态，偶数视作必胜态即可。

5. $n$ 为 $2$ 的次幂时，先手不一定必胜。

如果我们不将 $n$ 变成 $\frac{n}{2}$，那么后手就一定必胜；因此只能每次除以 $2$。因此设 $n=2^x$（$x$ 为正整数），若 $x$ 为奇数，后手必胜；否则先手必胜。

代码由上述思路整理可得。


```cpp
#include<cstdio>
int t,n;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		if(n==1)
		{
			printf("Bob\n");
			continue;
		}
		int tmp=n,cnt=0;
		while(tmp%2==0)
		{
			tmp/=2;
			cnt++;
		}
		if(cnt==0)
		{
			printf("Bob\n");
			continue;
		}
		else
		{
			if(tmp==1)
			{
				if(cnt%2==0)	printf("Alice\n");
				else	printf("Bob\n");
			}
			else	printf("Alice\n");
		}
	}
	return 0;
 } 
```

---

## 作者：氧少Kevin (赞：1)

# CF1537D - Deleting Divisors

https://www.luogu.com.cn/problem/CF1537D

## 题意

开始时有一个整数 $n$，Alice 和 Bob 轮流行动，每次可以在当前的 $n$ 上减去**当前的** $n$ 的一个非 $1$ 非 $n$ 的因子。

若 Alice 先手，某一方无法进行操作则判输，假如他们都采用最佳策略，问谁赢。

## 思路

不难发现跟当前数字的奇偶有关。

如果某一方不能操作，那么当前的数字一定是质数，质数是奇数。

### 性质
#### 根据奇数和偶数的性质，不难发现：

- 奇数只能变成偶数。

- 对于偶数：
    - 如果当前偶数不是 $2$ 的幂次，那么它既可以变成奇数，也可以变成偶数。
    - 如果当前偶数是 $2$ 的幂次，那么它只能变成偶数。

### 情况
#### 如果一个人拿到了奇数，那么有以下两种情况：
- 当前奇数是质数，无法进行操作，此人输。
- 当前奇数不是质数，将此数字减为偶数后给对手。

#### 如果一个人拿到了偶数，那么有以下两种情况：
- 将当前偶数减为偶数，然后给对方。
- 将当前偶数减为奇数，然后给对方（如果当前数字不是 $2$ 的幂次）。

### 结论
#### 如果一个人拿到了偶数，并且当前数字可以减为奇数（不是 $2$ 的幂次）

那么将其减为奇数给对方是最好的选择，此时此人必胜（如果此时将当前偶数减为偶数，相当于把必胜态交给了对手，对手胜）。

*必胜态之一：此数字是非 $2$ 次幂的偶数。*


#### 如果一个人拿到了偶数，并且当前数字不可以减为奇数（是 $2$ 的幂次）

将其减去一个偶数因子后：
- 减去后的数字不是 $2$ 的幂次：将必胜态给了对手，对手胜。显然这不是好的策略。
- 将其减去 $\frac{n}{2}$，即 $2^k\rightarrow 2^{k-1}$，对手没有拿到必胜态。对于对手来说，再减去一半是最好的选择。因此，谁最后减到 $2^1$，谁赢。

*必胜态之二：此数字 $=2^k$，且 $k$ 是偶数。*

---

## 作者：Exiler (赞：1)

## 原题

[CF1537D Deleting Divisors](https://www.luogu.com.cn/problem/CF1537D)

---

## 思路概述

### 题意分析

一个博弈论游戏。给定一个整数 $n(n∈[1,10^9])$ ，Alice和Bob二人轮流从中减去当前 $n$ 的因子（Alice先手），最终无法操作的人失败。求两人中谁有必胜策略。

### 思路分析

最初笔者将题中“减去”操作误读为“除去”，误以为可以用分解质因数和巴什博奕。但本题是在当前 $n$ 中减去其因子，故不能按上述方法解决。

由于本题数据规模 $n∈[1,10^9]$ ，按一般博弈论题目DP打表的解法显然不可行，所以笔者推测本题是一道结论题。

关于思考方向，因为题目数据规模较大，因此算法思路应该从 $n$ 本身的性质出发。综上，笔者选择从奇偶性开始考虑问题性质。

---

## 算法实现

### 从最简单的必败态出发

由于题目中对必败态的定义“某一方无法进行操作则判输”，又因为每次减去的因子 $i$ 不能为 $1$ 或 $n$ ，所以可以大胆推测的是，当出现 $n=1$ 时，先手方无法操作，所以必然失败。

根据博弈论中胜负态的转移原则（必败态的所有前驱态必然都为必胜态，必胜态至少有一个后继态为必败态），我们可以推出一个如下的转移方程雏形。

### 状态转移推导

如上文所述，笔者认为本题思路方向应该放在 $n$ 的奇偶性考虑，又根据上文中状态转移的原则我们可以得到状态转移的基本思路。

首先，对于先手方面对 $\frac{n}{2}∈N^*$ （ $n$ 为偶数）的情况，必然存在因子 $p|n$ 有 $p$ 为奇数和偶数两种情况。根据小学数学基础我们可以知道的是，一个偶数减去一个偶数仍然为偶数，即状态不发生改变；一个偶数减去一个奇数结果为奇数，状态改变。在第二种情况中，若对方再将奇数转化为偶数，就又回到了当前状态。显然地，这种状态互相转化的过程必然以对方拿到 $n=1$ 的情况为结束，因此当 $n$ 为偶数时当前操作方处于必胜态。

特别地，当 $n=2^k(k∈N^*)$ 时，先手方始终可以取走 $n$ 的一半避免使对方拿到必胜态。但这种转移必定以某一方取到 $n=1$ 告终，而决定先手方是否失败的要素就是这种转移的次数 $k$ ，即 $k|2$ ，先手方必胜，反之必败。

对于 $\frac{n}{2}∉N^*$ （ $n$ 为奇数）的情况，其所有因子必然都是奇数，所以先手方的任何操作必然使 $n'$ 为偶数，即将必胜态送给对方，所以处于必败态。

由上文就得到了本题的判断函数（设函数值为 $1$ 则必胜，反之必败）如下：

$$f(x)=\begin{cases}1,2|i\text{ or }i=2^k(2|k)\\0,\text{otherwise} \end{cases}$$

---

## AC code
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<set>
#include<ctime>
#define RI register int
using namespace std;
int T,n,m;
inline int read();
inline void print(int x);
int main()
{
	for(T=read();T;--T)
	{
		n=read();
		if(n&1) puts("Bob");
		else
		{
			RI clc=log2(n*1.0);
			if(1<<clc==n && clc&1) puts("Bob");
			else puts("Alice");
		}
	}
	return 0;
}
inline int read(void)
{
	char putin;bool isneg=false;RI ret=0;
	putin=getchar();
	while((putin>'9' || putin<'0') && putin!='-')
		putin=getchar();
	if(putin=='-')
	{
		isneg=true;
		putin=getchar();
	}
	while(putin>='0' && putin<='9')
	{
		ret=(ret<<3)+(ret<<1)+(putin&15);
		putin=getchar();
	}
	return isneg?-ret:ret;
}
inline void print(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) print(x/10);
	putchar(x%10+'0');
	return;
}
```



---

## 作者：YuanZihan1225 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1537D)

# 思路分析

这显然是一道博弈论的题，我们考虑从以下三个方面来考虑：~~（不要问我怎么想到的）~~

1. 当 $n$ 为奇数时，它如果不是质数，就一定会有一个奇因子。又因 $k \mid n$ 且 $k \mid k$ ，所以 $k \mid (n - k)$ ，所以减掉后的数不会是 $2 ^ k$  ，就能变为第二种情况。

2. 当 $n$ 为偶数且不为 $2 ^ k$ 时，显然会存在一个奇数 $k \mid n$ ，减掉后又变为第一种情况，于是我们陷入了一个循环。那什么时候跳出呢？显然，在某一次由第二种情况变为第一种时， $n$ 会变为一个奇质数，而必是后手拿到它，所以此时先手必胜。而由此我们又能得出，在多循环一次的奇数情况下，后手必胜。

3. 当 $n$ 为 $2 ^ k$ 时，先手如果选择变为第二种情况，则后手必胜，所只能选择减掉 $\frac{n}{2}$ ，后手同理，则若 $k \mid 2$ ，则 $2 ^ 0$ 会去后手手中，先手必胜，否则后手必胜。

下面让我们来整理一下：

1. 当 $n$ 为奇数，后手必胜。

2. 当 $n$ 为偶数且不为 2 的整数次幂先手必胜。

3. 当 $n$ 为 2 的奇数次幂时后手必胜，为 2 的偶数次幂时先手必胜。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long//注意开long long
using namespace std;
inline int read()//卡个常
{
	int x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-')
			f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}
int t, n;
int main()
{
	t = read();
	while(t--)
	{
		n = read();
		int k = 2;//2 ^ 1
		while(k < n)//处理 2 的奇数次幂，所以指数每次加2
			k *= 4;
		if(k == n || (n & 1))//判断
			puts("Bob");
		else
			puts("Alice");
	}
	return 0;//完美的结束QWQ
}
```

---

