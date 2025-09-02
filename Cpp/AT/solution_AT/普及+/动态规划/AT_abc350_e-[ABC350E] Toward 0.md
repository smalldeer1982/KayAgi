# [ABC350E] Toward 0

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc350/tasks/abc350_e

整数 $ N $ が与えられます。あなたは次の $ 2 $ 種類の操作を行うことができます。

- $ X $ 円払う。$ N $ を $ \displaystyle\left\lfloor\frac{N}{A}\right\rfloor $ に置き換える。
- $ Y $ 円払う。$ 1 $ 以上 $ 6 $ 以下の整数が等確率で出るサイコロを振る。その出目を $ b $ としたとき、$ N $ を $ \displaystyle\left\lfloor\frac{N}{b}\right\rfloor $ に置き換える。
 
ここで $ \lfloor\ s\ \rfloor $ は $ s $ 以下の最大の整数を表します。例えば $ \lfloor\ 3\ \rfloor=3 $、$ \lfloor\ 2.5\ \rfloor=2 $ です。

適切に操作を選択したとき、$ N $ を $ 0 $ にするまでに払う必要がある金額の期待値の最小値を求めてください。  
 なお、サイコロの出目は操作ごとに独立であり、操作の選択はそれまでの操作の結果を確認してから行うことができます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{18} $
- $ 2\ \leq\ A\ \leq\ 6 $
- $ 1\ \leq\ X,Y\ \leq\ 10^9 $
- 入力は全て整数である
 
### Sample Explanation 1

行える操作は 次の $ 2 $ 種類です。 - $ 10 $ 円払う。$ N $ を $ \displaystyle\left\lfloor\frac{N}{2}\right\rfloor $ に置き換える。 - $ 20 $ 円払う。$ 1 $ 以上 $ 6 $ 以下の整数が等確率で出るサイコロを振る。その出目を $ b $ としたとき、$ N $ を $ \displaystyle\left\lfloor\frac{N}{b}\right\rfloor $ に置き換える。 前者の操作を $ 2 $ 回行うのが最適です。

### Sample Explanation 2

行える操作は 次の $ 2 $ 種類です。 - $ 20 $ 円払う。$ N $ を $ \displaystyle\left\lfloor\frac{N}{2}\right\rfloor $ に置き換える。 - $ 20 $ 円払う。$ 1 $ 以上 $ 6 $ 以下の整数が等確率で出るサイコロを振る。その出目を $ b $ としたとき、$ N $ を $ \displaystyle\left\lfloor\frac{N}{b}\right\rfloor $ に置き換える。 最適な操作は以下のようになります。 - まず後者の操作でサイコロを振ります。 - $ 4 $ 以上が出た場合 $ N=0 $ となります。 - $ 2 $ または $ 3 $ が出た場合 $ N=1 $ となります。続けて前者の操作を行うことで $ N=0 $ となります。 - $ 1 $ が出た場合最初からやり直します。

## 样例 #1

### 输入

```
3 2 10 20```

### 输出

```
20.000000000000000```

## 样例 #2

### 输入

```
3 2 20 20```

### 输出

```
32.000000000000000```

## 样例 #3

### 输入

```
314159265358979323 4 223606797 173205080```

### 输出

```
6418410657.7408381```

# 题解

## 作者：fcy20180201 (赞：5)

~~由于某种未知原因~~我又回来写题解了。

[题目链接](https://www.luogu.com.cn/problem/AT_abc350_e)

## 思路
先考虑朴素 DP。$dp_i$ 表示把 $i$ 变为 $0$ 需要的最少期望代价。$dp1$ 和 $dp2$ 分别表示最后一次进行操作 $1$ 和 $2$ 的答案。
$$dp1_i=dp_{\lfloor\frac{i}{A}\rfloor}+X$$
$$dp2_i=\frac{1}{6}(dp2_{\lfloor\frac{i}{1}\rfloor}+dp_{\lfloor\frac{i}{2}\rfloor}+dp_{\lfloor\frac{i}{3}\rfloor}+dp_{\lfloor\frac{i}{4}\rfloor}+dp_{\lfloor\frac{i}{5}\rfloor}+dp_{\lfloor\frac{i}{6}\rfloor})+Y$$

这时候我们发现 $dp2$ 的转移有后效性（因为这个转移方程的是建立在最后一次使用操作 $2$ 的基础上，所以使用 $dp2_{\lfloor\frac{i}{1}\rfloor}$ 转移而不是 $dp_{\lfloor\frac{i}{1}\rfloor}$），所以考虑移项（~~当然也可以写高斯消元~~）:
$$\frac{5}{6}dp2_i=\frac{1}{6}(dp_{\lfloor\frac{i}{2}\rfloor}+dp_{\lfloor\frac{i}{3}\rfloor}+dp_{\lfloor\frac{i}{4}\rfloor}+dp_{\lfloor\frac{i}{5}\rfloor}+dp_{\lfloor\frac{i}{6}\rfloor})+Y$$
两边同除以 $\frac{5}{6}$：
$$dp2_i=\frac{1}{5}(dp_{\lfloor\frac{i}{2}\rfloor}+dp_{\lfloor\frac{i}{3}\rfloor}+dp_{\lfloor\frac{i}{4}\rfloor}+dp_{\lfloor\frac{i}{5}\rfloor}+dp_{\lfloor\frac{i}{6}\rfloor})+\frac{6Y}{5}$$
于是就得到了一个无后效性的转移方程，显然 $dp_i=\min(dp1_i,dp2_i)$，答案是 $dp_N$。

但是 $N\le 10^{18}$，朴素 DP 直接爆炸。借鉴一下[这题](https://www.luogu.com.cn/problem/AT_abc188_f)的思路，使用 map 记搜，时间复杂度和空间复杂度都约为 $O(\log N)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
ll n,A;
double x,y;
map<ll,double>dp;
double dfs(ll i){//map 记搜
	if(!i)return 0;//初值 dp[0]=0
	if(dp.count(i))return dp[i];//如果算过就直接返回
	return dp[i]=min(dfs(i/A)+x,(dfs(i/2)+dfs(i/3)+dfs(i/4)+dfs(i/5)+dfs(i/6))/5+y*1.2);//转移
}
int main(){
	scanf("%lld%lld%lf%lf",&n,&A,&x,&y);
	printf("%.7lf\n",dfs(n));
	return 0;
}

```

---

## 作者：Crazyouth (赞：0)

## 分析

如果我们去计算每个选项带来的期望花费，取最小那个，其实是可能可以通过的，但为了保险起见，我加了个记忆化。第一个选项没什么好说的，主要讲讲第二个选项的处理。

记 $f(k)$ 表示把 $k$ 通过第二个操作变成 $0$ 的期望花费，由题意易得

$$f(k)=y+(\sum_{i=1}^6f(\frac{k}{i}))\times \frac{1}{6}$$

考虑到 $i=1$ 的时候还是要计算 $f(k)$ 不好处理，于是把 $f(k)$ 移项到左边，得

$$f(k)\times \frac{5}{6}=y+(\sum_{i=2}^6f(\frac{k}{i}))\times\frac{1}{6}$$

由此不难计算出 $f(k)$ 的值。最后判断一下它和第一操作谁更划算，然后输出 $n$ 的答案就过了。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long double
map<int,int> mp;
int n,a,x,y;
int dfs(int k)
{
	if(k==0) return 0;
	if(mp[k]) return mp[k];
	int ret=dfs(floor(k/a))+x;
	ret=min(ret,(y+(dfs(floor(k/2))+dfs(floor(k/3))+dfs(floor(k/4))+dfs(floor(k/5))+dfs(floor(k/6)))/6.000)*6.000/5.000);
	mp[k]=ret;
	return mp[k];
}
signed main()
{
	cin>>n>>a>>x>>y;
	cout<<fixed<<setprecision(7)<<dfs(n);
	return 0;
}

---

## 作者：UniGravity (赞：0)

## Solution AT_abc350_e [ABC350E] Toward 0
[传送门](https://www.luogu.com.cn/problem/AT_abc350_e)

充分发扬人类智慧，看到除法和下取整，直觉告诉我们虽然 $n$ 很大，但是**真正有效的状态很少**。

搜一发后发现不到 $10^4$，于是直接上记忆化搜索概率 dp 即可。

但此时还需要一个转化，因为我们发现 $\lfloor\frac{n}{1}\rfloor$ 还是 $n$。此时 dp 需要用到自己，~~上高斯消元就太不明智了~~。

于是我们干脆**修改随机操作的代价和范围**，从 1 到 6 变成 2 到 6。如果投出了 1，那么就需要继续投。投出别的进行下一步操作的概率是 $\frac{5}{6}$，那么期望做 $\frac{6}{5}$ 次，代价就不是 $y$ 而是 $y\times\frac{6}{5}$。

```cpp
int n, a, x; double y; // y 已经乘过 6/5 了
map< int, double > cost;

inline double dfs(rnt n) {
    if (n == 0) return 0;
    if (cost.count(n)) return cost[n];
    double c1 = dfs(n / a) + x;
    double c2 = dfs(n / 2) / 5 + dfs(n / 3) / 5 + dfs(n / 4) / 5 + dfs(n / 5) / 5 + dfs(n / 6) / 5 + y;
    cost[n] = min(c1, c2);
    return min(c1, c2);
}
```

---

## 作者：incra (赞：0)

### Solution
玄学记搜题。

设 $f_n$ 为 $n$ 变成 $0$ 所需的期望价钱。

不难得到第二种情况中 $f_n=\dfrac{1}{6}\displaystyle\sum_{i=1}^{6}f_{\lfloor\frac{n}{i}\rfloor}+y$，然后发现两边都有 $f_n$，移项可得 $f_n=\dfrac{1}{5}\displaystyle\sum_{i=2}^{6}f_{\lfloor\frac{n}{i}\rfloor}+\dfrac{6}{5}y$。

注意和第一种情况的价钱 $f_{\lfloor\frac{n}{a}\rfloor}+x$ 取最小值。

于是这题就做完了，加上记忆化即可。
### Code
[Link](https://atcoder.jp/contests/abc350/submissions/52587722)。

---

## 作者：Starrykiller (赞：0)

不要被 $N\le 10^{18}$ 吓到。经过打表可以发现，$N$ 经过操作后能够得到的数的最多在 $7000$ 左右。我们可以利用 dfs 将这些值找出来，离散化。

我们设 $f_i$ 为 $i\to 0$ 的期望最小代价。

根据题意，可以得到：

$$
f_i=\min\left(f_{\lfloor\frac{i}{A}\rfloor}+X,Y+\frac{1}{6}\sum_{j=1}^6f_{\lfloor\frac{i}{j}\rfloor}\right)
$$

注意到转移（可能）成环，我们把它提出来

$$f_i=Y+\frac{1}{6}f_{i}+\sum_{j=2}^6f_{\lfloor\frac{i}{j}\rfloor}$$

解得

$$f_i=\frac{6}{5}\left(Y+\sum_{j=2}^6f_{\lfloor\frac{i}{j}\rfloor}\right)$$

把解出来的 $f_i$ 与 $f_{\lfloor\frac{i}{A}\rfloor}+X$ 取个 $\min$ 即可。

[My implementation](https://atcoder.jp/contests/abc350/submissions/52606423).

---

