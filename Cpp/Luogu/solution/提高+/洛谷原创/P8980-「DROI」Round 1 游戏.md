# 「DROI」Round 1 游戏

## 题目背景

人生，又何尝不是一场游戏呢？

## 题目描述

你将和一名小朋友进行 $T$ 次游戏，每一次游戏的规则如下：

1. 首先，你需要在 $[1,n]$ 中选择一个正整数 $x$。

2. 接下来，小朋友会有 $Q$ 次询问，对于每次询问，他会给出一个 $a_i$（保证 $a_i \in [1,n]$），你需要回答他 $\gcd(x,a_i)$ 的值。

3. 当某一轮小朋友得到答案后，如果他能唯一确定你选择的数，那么本次游戏结束。

现在**你提前知道了**小朋友每次询问的 $a_i$，你需要找到一个 $x$，使得游戏持续的轮数最长。

## 说明/提示

#### 样例解释#1

选取 $11$ 作为 $x$，显然小朋友到游戏结束也无法唯一确定。

------------

#### 样例解释#2

对于第一组数据：选取 $1$ 作为 $x$，小朋友在第五轮结束后可以唯一确定 $x$，可以证明不存在更优的 $x$。

对于第二组数据：同理，选取 $1$ 作为 $x$ 即可。

------------

#### 数据范围

**「本题采用捆绑测试」** 

- $\operatorname{Subtask} 1(20\%)$：$n,Q\leq 500$。

- $\operatorname{Subtask} 2(20\%)$：$n,Q \leq 5 \times 10^4$。

- $\operatorname{Subtask} 3(30\%)$：$Q \leq 10^5$。

- $\operatorname{Subtask} 4(30\%)$：无特殊限制。

对于 $100\%$ 的数据：$T \leq 10$，$1 \leq a_i \leq n \leq 10^{18}$，$1 \leq Q \leq 2\times 10^{6}$，$\sum Q \leq 6\times 10^{6}$。

**本题输入量较大，请用较快的输入方法。**

## 样例 #1

### 输入

```
1
11 3
8 9 5```

### 输出

```
game won't stop```

## 样例 #2

### 输入

```
2
8 5
8 2 3 5 7 
24 16
3 17 18 5 19 4 16 23 7 11 13 18 6 21 22 2
```

### 输出

```
5
11
```

# 题解

## 作者：Demeanor_Roy (赞：7)

- 出题人题解。

-----------

首先发觉 $n$ 的范围过大导致无论从哪个方向攻破都难有进展，不难想到缩小 $n$ 的范围。

令 $\pi(n)$ 表示小于等于 $n$ 的质数个数，则有结论：若 $\pi(n) > Q$，小朋友必败。让我们考虑证明这个结论。 

- 考虑质数 $p$ ，令 $k$ 是使 $p^k \leq n$ 的最大正整数，显然若所选 $x$ 中 $p$ 的指数为 $k$ ，则必须存在一个 $a_i$ 使得 $a_i$ 中 $p$ 的指数等于 $k$ 才能唯一确定 $x$ 中 $p$ 的指数。所以若存在一个质数 $p$，使得所有 $a_i$ 中 $p$ 指数的最大值小于 $k$ ，那么我们就可以选择 $p^k$ 作为 $x$ ，小朋友必败。

- 而对于任意两个不同质数 $p$，$q$，显然都有 $p^{k1} \times q^{k2} > n$，所以一个 $a_i$ 最多能使小朋友确定 $x$ 中一个质数的指数。据此可知，$Q$ 次提问最多能确定 $Q$ 个质数的指数。显然当 $\pi(n) > Q$时，小朋友必然无法猜出 $x$ 的值，直接输出`game won't stop`即可。

于是我们接下来只需要考虑 $\pi(n) \leq Q$ 的情况。

先给出结论：当且仅当对于所有质数 $p \in [1,n]$，都有 $p^k$ 或其倍数在 $a_i$ 中出现过时，小朋友能唯一确定 $x$。给出证明：

- 充分性：根据以上条件，小朋友一定能确定每个质数在 $x$ 中的指数，故能唯一确定 $x$。

- 必要性：设质数 $p$ 不满足上述条件，不妨令 $x=p^k$，则小朋友无法唯一确定 $x$。

于是对于所有质数 $p \in [1,n]$ 求出 $p^k$ 或其倍数首次出现的位置，取 max 即为答案。线性筛预处理出一些信息，实现精细单次询问时间复杂度可做到 $O(Q)$。我写代码时偷懒有一个小常数，但无伤大雅。

这里顺便阐明一下部分分依据：

1. 第一档部分分是给 $n^2Q$ 暴力的，只要稍加思考过这档不难。

2. 第二档部分分是给没有推出缩小 $n$ 的范围但发掘了一些其他性质的。

3. 第三档部分分是给所有性质都推出来，但不会线性筛或者常数实在太大的人。

至此本题解决完毕。下附代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N=3.3e7+10,M=2e6+10;
LL n,A[M];
int T,m,id,v[N],sum[N],prime[M<<1];
bool ispk[N],check[N];
inline LL read()
{
	LL x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}
inline void Euler()
{
	v[1]=ispk[1]=true;
	for(int i=2;i<N;i++)
	{
		if(!v[i]) v[i]=i,prime[++id]=i,ispk[i]=true;
		for(int j=1;j<=id;j++)
		{
			if(i*prime[j]>=N||v[i]<prime[j]) break;
			v[i*prime[j]]=prime[j];
			ispk[i*prime[j]]=(ispk[i]&&(v[i]==prime[j]));
		}
		sum[i]=sum[i-1]+(v[i]==i);
	}
}
inline void solve()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++)	A[i]=read();
	if(prime[m+1]<=n) return printf("game won't stop\n"),void();
	for(int i=1;i<=m;i++)	check[prime[i]]=false;
	int now=0;
	for(int i=1;i<=m;i++)
	{
		while(A[i]*A[i]>n&&!ispk[A[i]]) 	A[i]/=v[A[i]];
		if(A[i]*v[A[i]]>n) 
		{
			now+=!check[v[A[i]]];
			check[v[A[i]]]=true;
		}
		if(now==sum[n])	
		{
			printf("%d\n",i);
			break;
		}
		else if(m-i+now<sum[n]) 
		{
			printf("game won't stop\n");	
			break;
		}
	}
}
int main()
{	
	Euler();
	scanf("%d",&T);
	while(T--)	solve();
	return 0;	
} 
```

---

## 作者：Super_Builder (赞：1)

## 思路

我们考虑先取出**小于等于 $n$ 的所有质数** $p_i$，假设我们已经选出了 $x$，唯一分解 $x$ 得：
$x = p_{1}^{e_{1}} \times p_{2}^{e_{2}} \times p_{2}^{e_{3}} \times...$，
若小朋友猜了一个数 $y = p_{1}^{l_{1}} \times p_{2}^{l_{2}} \times p_{2}^{l_{3}} \times...$，那么 $\gcd(x, y) = p_{1}^{\min(e_{1},l_{1})} \times p_{2}^{\min(e_{2},l_{2})} \times p_{2}^{\min(e_{3},l_{3})} \times...$。

如果小朋友猜的 $y$ 中，不存在一个因子 $p^f \le n$ 使得 $p^{f + 1} > n$，那么这次询问是无效的。

因为如果不含有 $p^f$ 使得 $p^f \le n$ 且 $p^{f + 1} > n$，那么假设含有 $p^{f'}$，$f' < f$，只要将 $x$ 中 $p$ 的次数设为 $f$，那么小朋友永远猜不到 $x$ 中 $p$ 的次数。

所以只有含有至少一个 $p^f$ 的询问才有效。只需要查询小于等于 $n$ 的每一个质数 $p$，查询 $p^f \le n$ 和 $p^{f + 1} > n$ 在 $a_i$ 中出现的最早位置，取最大值就是答案。如果有一个质数没有出现过，那么答案是 `game won't stop`。

至此可以获得 40 分。我们会发现 $n$ 太大了，所以当你拿出所有小于等于 $n$ 的质数时，时间和空间都会炸。

从上面的推论中可以发现一条结论，在小朋友的每次有效询问中，最多只能确定一个质数在 $x$ 中的次数。即不存在两个质数 $p$、$q$，使得 $p^f \le n$ 和 $p^{f + 1} > n$、$q^l \le n$ 和 $q^{l + 1} > n$ 且满足 $p^{f} \times q^{l} \le n$。由于 $a_i \le n$，所以有此结论。

所以在 $Q$ 次询问中最多确定 $Q$ 个质数的次数，如果第 $Q + 1$ 个质数仍然小于等于 $n$ 的话，那么 $Q$ 次询问就不能确定所有质数。$Q$ 最大 $2 \times 10^6$，第 $2 \times 10^6 + 1$ 个质数在 $3.25 \times 10^7$ 以下。所以如果 $Q > 3.25 \times 10^7$，那么输出 `game won't stop`。

### 提示

- 在枚举询问时，对每个 $a_i$ 判断能否含有一种 $p^f$，可以在线性筛的时候筛出最小质因子，然后每次除以最小质因子来判断。由于每次至少除以 2，所以这一步是 $O(\log n)$ 的。

总复杂度 $O(T \times (Q \log n + n))$。
## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define gc pa == pb && (pb = (pa = buf) + fread(buf, 1, 100000, stdin), pa == pb) ? EOF : *pa++
static char buf[100000], *pa(buf), *pb(buf);
inline int read()
{
    int x = 0;
    char c = gc;
    while (c < '0' || c > '9')
        c = gc;
    for (; c >= '0' && c <= '9'; c = gc)
        x = x * 10 + (c & 15);
    return x;
}
const int M = 32500000;
int m, n, a[2000005], cnt, pri[M], minp[M];
bool ck[M], p[M];
signed main()
{
    for (int i = 2; i <= M; i++)
    {
        if (!p[i])
            pri[++cnt] = i, minp[i] = i;
        for (int j = 1; i * pri[j] <= M && j <= cnt; j++)
        {
            p[i * pri[j]] = 1;
            minp[i * pri[j]] = pri[j];
            if (i % pri[j] == 0)
                break;
        }
    }
    int T = read();
    while (T--)
    {
        m = read(), n = read();
        for (int i = 1; i <= n; i++)
        {
            a[i] = read();
        }
        if (m >= M)
        {
            puts("game won't stop");
            continue;
        }
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            while (a[i] != 1)
            {
                int x = minp[a[i]], res = 1;
                while (a[i] % x == 0)
                    a[i] /= x, res *= x;
                if (1ll * res * x > m && !ck[x])
                    ans = i, ck[x] = 1;
            }
        }
        for (int i = 2; i <= m; ck[i] = 0, i++)
            if (!p[i] && !ck[i])
                ans = n + 1;
        if (ans <= n)
            printf("%d\n", ans);
        else
            puts("game won't stop");
    }
    return 0;
}
```

---

