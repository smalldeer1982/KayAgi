# [AGC053C] Random Card Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc053/tasks/agc053_c

$ 2N $ 枚のカードがあり、それぞれには $ 1 $ から $ 2N $ までの番号が付いています。 このカードを用いて行う、次のゲームを考えます。

まず、ディーラーはそれぞれの山が $ N $ 枚のカードからなるように、カードを $ 2 $ つの山にランダムに分けます。 このとき、ディーラーは各山におけるカードの順序もランダムに定めます。 その後プレイヤーは、一方の山が空になるまで次の操作を繰り返し行い、最終的な操作回数がこのゲームのスコアとなります。

- ある正の整数 $ k $ を選び、一方の山の上から $ k $ 枚目のカードと、もう一方の山の上から $ k $ 枚目のカードを比較する。（ただし、$ k $ は各山のカード枚数を超えてはいけない。）そして、番号が小さい方のカードをそのカードを含む山から取り除く。

このゲームを *チーター* がプレイするとします。 つまり、各山の各カードの番号を常に把握できるプレイヤーがプレイするとします。 このプレイヤーがスコアを最小化するよう最適にプレイしたときの、スコアの期待値を $ \bmod\ 10^9+7 $ で求めてください（注記参照）。

## 说明/提示

### 注記

- 求める期待値は有理数となります。期待値を分数 $ \frac{y}{x} $（$ x $ と $ y $ は互いに素な正の整数）で表したとき、$ x $ は $ P=10^9+7 $ と互いに素になるので、 $ xz\ \equiv\ y\ \pmod\ P $ なる $ 0 $ 以上 $ P-1 $ 以下の唯一の整数 $ z $ を出力してください。

### 制約

- $ 1\ \leq\ N\ \leq\ 10^6 $

## 样例 #1

### 输入

```
1```

### 输出

```
1```

## 样例 #2

### 输入

```
3```

### 输出

```
486111118```

# 题解

## 作者：joke3579 (赞：5)

## $\text{Statement}$

给定 $2n$ 张卡牌，顺次编号为 $1$ 至 $2n$。考虑如下的游戏：

首先，庄家随机地将卡牌分成两堆，每堆 $n$ 张。每堆内牌的顺序也是随机的。随后，玩家会重复以下操作直到其中一堆为空：   
选择一个正整数 $k$，比较两堆中从上到下第 $k$ 张卡牌（$k$ 必须不大于牌堆的大小）。随后，移除两张牌中编号更小的牌。   
操作次数即为玩家的得分。

假设玩家是一名**作弊者**，能看到两堆牌中每张牌的编号。玩家将采用最优策略最小化得分，请输出玩家的期望得分在模 $10^9 + 7$ 意义下的值。

本题中的期望得分是一个分数。假设我们将答案表示为最简分数 $\frac xy$，你需要输出的值即为满足 $yz \equiv x\pmod {10^9 + 7}$ 的值 $z$。

$n\le 10^6$。

## $\text{Solution}$

我们设两堆牌分别为 $A$ 堆和 $B$ 堆，每堆中从下到上分别编号为 $1$ 至 $n$，编号为 $i$ 的牌分别记作 $A_i$ 和 $B_i$。不妨令编号为 $2n$ 的牌出现在 $B$ 堆中。由此假设，确定了最终空堆仅有可能是 $A$ 堆。

讨论玩家采用最优策略的情况下最少需要多少次取完 $A$ 堆中的牌。  
对于每张 $A$ 堆中的牌 $A_i$，假设 $p_i$ 为最小的满足 $A_i < B_{p_i}$ 的值。令 $d$ 为 $\max\{p_i - i\}$，则玩家需要 $n + d$ 次取完 $A$ 堆中的牌。   
首先玩家操作的次数不可能小于 $n + d$，因为对于满足 $p_i - i = d$ 的 $i$，我们至少需要 $d$ 次操作取空 $p_i$ 和 $i$ 间的牌，随后才能取出 $i$。其次，我们可以构造一种方案使得玩家操作次数恰好为 $d$。在这种方案中，我们每次操作，要么可以将 $d$ 的值减一，要么可以取出一张 $A$ 堆中的牌。若当前 $d$ 大于 $0$，则指定 $k$ 为满足 $p_i - i > 0$ 的最小的 $i$；反之指定 $k$ 为满足 $p_i - i = 0$ 的最大的 $i$ 即可完成构造。   
这样我们就证明了最小取牌次数为 $n + d$。

随后计算期望。对于任意 $0 \le d <n$，设 $P(d)$ 为最小取牌次数小于等于 $n+d$ 的概率，并令 $\forall i < 0, P(i) = 0$。由于 $P(n -1) = 1$，我们有答案即为
$$\begin{aligned}

&\sum_{i=0}^{n-1} \left(P(i) - P(i - 1)\right) (n + i)
\\ = \ & n\left(\sum_{i=0}^{n-1} P(i) - P(i - 1)\right) + \sum_{i=0}^{n-1} i\times P(i) -  \sum_{i=0}^{n-1} i\times P(i - 1)
\\ = \ & n\times P(n - 1) + \sum_{i=0}^{n-1} i\times P(i) - \sum_{i=0}^{n-2} (i + 1)\times P(i)
\\ = \ & n + \sum_{i=0}^{n-1} i\times P(i) - \sum_{i=0}^{n-2} (i + 1)\times P(i)
\\ = \ & n + \sum_{i=0}^{n-1} i\times P(i) - \sum_{i=0}^{n-2} i\times P(i) - \sum_{i=0}^{n-2} P(i)
\\ = \ & 2n - 1 - \sum_{i=0}^{n-2} P(i)
\\ = \ & 2n - \sum_{i=0}^{n-1} P(i)

\end{aligned}$$

现在的目的是快速求得每个 $P(i)$。  

我们固定一组 $A,B$。仍然假设 $2n$ 位于 $B$ 堆中，则答案小于 $n + d$ 当且仅当对于任何 $i \ge 1$，$B_1,B_2,\cdots,B_{\min\{i + d, n\}}$ 中存在一个值大于 $A_i$。
分开统计概率，我们有
$$P(d) = 2\times \prod_{i=1}^{n - d}\frac{2i + d - 1}{2i + d}\times \prod_{i=n-d+1}^n\frac{n + i - 1}{n + i} = \prod_{i=1}^{n - d}\frac{2i + d - 1}{2i + d}\times \frac{2n - d}{n} $$

可以通过预处理奇偶数的前缀积并作商的形式得到 $\prod_{i=1}^{n - d}\frac{2i + d - 1}{2i + d}\times (2n - d)$。最后乘入 $n$ 的逆元即可得到答案。

总时间复杂度 $O(n)$。

$\text{code : }$
```cpp
#include <bits/stdc++.h>
using namespace std; 
#define rep(i,s,t) for (register int i = (s), i##_ = (t) + 1; i < i##_; ++ i)
const int mod = 1e9 + 7, N = 2e6 + 10;
int n, ans, invn, fac[N], inv[N], ifac[N];
int sub(int a, int b) { return (a -= b) < 0 ? a + mod : a; }
int mul(int a, int b) { return 1ll * a * b % mod; } template <typename ...Args> int mul(int a, Args ...b) { return mul(a, mul(b...)); }
template <typename T1, typename T2> T1 qp(T1 a, T2 b) { T1 ret = 1; for (; b > 0; a = mul(a, a), b >>= 1) if (b & 1) ret = mul(ret, a); return ret; } 
int calc(int d) { return mul(fac[(n << 1) - 1 - d], d ? ifac[d - 1] : 1, fac[d], ifac[(n << 1) - d - 2]); }
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0); 
	cin >> n;
	fac[0] = fac[1] = inv[0] = inv[1] = ifac[0] = ifac[1] = 1;
	rep(i, 2, n << 1) inv[i] = mul(mod - mod / i, inv[mod % i]), fac[i] = mul(i, fac[i - 2]);
	rep(i, 2, n << 1) ifac[i] = mul(inv[i], ifac[i - 2]);
	int ans = (n << 1); invn = qp(n, mod - 2);
	rep(i,0,n-1) ans = sub(ans, mul(calc(i), invn));
	cout << ans << '\n';
}
```

---

## 作者：HomuraAkemi (赞：1)

> 摘自 杂题选做。



很牛的题目。

不妨设 $A,B$ 为两堆卡片，其中 $2n$ 在 $B$ 这一堆。

> $\textbf{Lemma 1.}$ 令 $p_i$ 为最小的 $j$ 满足 $B_j\gt A_i$。则最优操作次数为 $n+\max_{1\le i\le n}\{p_i-i\}$。
>
> $\textbf{Proof.}$ 显然这是答案的下界。考虑构造达到下界的操作。
> 
> 每次我们可以做两种操作：选择一个 $i$ 使得 $A_i\lt B_i$，吃掉 $A_i$；或者吃掉一个 $B_i$。前一种操作的次数之和是一定的，我们只需要最小化后面的操作的次数。
>
> 考虑如下策略：每次选择**最小的** $i$ 使得当前的 $A_i\gt B_i$，然后吃掉 $B_i$（如果不存在，就随便吃掉一个 $A_i$）。
> 
> 这么做之后，所有满足 $p_i\gt i$ 的 $p_i$ 都会减小 $1$。这样在 $\max_{1\le i\le n}\{p_i-i\}$ 次后就一定能吃掉所有的 $A_i$。故策略是正确的。$\square$

不妨记 $Y=\max_{1\le i\le n}\{p_i-i\}$。我们要求操作次数的期望值，也就是：

$$
\begin{aligned}
\mathbb{E}[X]&=n+\sum_{d=0}^{n-1} d\cdot \mathrm{Pr}\left(Y=d\right) \\
\mathbb{E}[X]&=n+\sum_{d=1}^{n} d\cdot \mathrm{Pr}\left(Y=d\right) \\
&=n+\sum_{d=1}^{n}  \mathrm{Pr}\left(Y\ge d\right) \\
&=n+\sum_{d=1}^{n} \left( 1-\mathrm{Pr}\left(Y\lt d\right)\right) \\
&=2n-\sum_{d=1}^{n} \mathrm{Pr}\left(Y\lt d\right) \\
&=2n-\sum_{d=0}^{n-1} \mathrm{Pr}\left(Y\le d\right) \\
\end{aligned}
$$

只需要求出 $\mathrm{Pr}(Y\le d)$ 即可。

$Y\le d\iff \forall 1\le i\le n,\exists j\in [1,\min(n,i+d)],\text{ s.t. } B_j\gt A_i$。

设事件 $D_i$：$\exists j\in [1,\min(n,i+d)],\text{ s.t. } B_j\gt A_i$ 成立。本质上，我们就是要求 $\mathrm{Pr}(D_1D_2\cdots D_n)$。

由概率乘积公式可得

$$\mathrm{Pr}(D_1D_2\cdots D_n)=\prod_{i=1}^n\mathrm{Pr}(D_i\vert D_1D_2\cdots D_{i-1})$$

$\mathrm{Pr}(D_i\vert D_1D_2\cdots D_{i-1})$ 不好算，正难则反，考虑它的对立事件，也就是：

$\overline{D_i}\vert D_1D_2\cdots D_{i-1}$：
- $\forall k\in [1,i-1]$，都 $\exists j\in [1,\min(n,k+d)],\text{ s.t. } B_j\gt A_k$ 成立。
- 对于 $i$，不存在 $j\in [1,\min(n,i+d)],\text{ s.t. } B_j\gt A_i$ 成立。

这意味着，$A_i$ 是 $B_1\sim B_{\min(n,i+d)},A_1\sim A_i$ 这 $[i+\min(n,i+d)]$ 个数中最小的。

> $\textbf{Proof.}$ 如果 $A_i$ 不是 $A_1\sim A_i$ 中最小的，设 $j\lt i$ 使得 $A_j\gt A_i$。由第一个条件，得知：存在 $k\in [1,\min(n,j+d)] \subset [1,\min(n,i+d)]$，使得 $B_k\gt A_j$ 成立，显然此时也有 $B_k\gt A_i$，矛盾。
> 
> 否则，与条件 $2$ 矛盾。$\square$

而这个事件满足的概率是很容易计算的——就是 $\displaystyle \frac{1}{i+\min(n,i+d)}$！把它代回原式，我们得到了

$$\mathrm{Pr}(Y\le d)=\prod_{i=1}^{n-d}\frac{2i+d-1}{2i+d}\prod_{i=n-d+1}^{n}\frac{n+i-1}{n+i}$$

预处理双阶乘即可快速计算，从而我们解决了本题。

时间复杂度为 $\Theta(N)$，当然如果懒得写线性预处理，$\Theta(N\log N)$ 也可以轻松通过。

鸣谢：Appleblue17。

---

## 作者：carefree_Zhuang (赞：0)

## Solution

前面部分略，相信别的题解写得很详细。

本题解集中解释 $p(d)$ 的计算。

$p(d)$ 表示对于 $\forall A_i, B_1\cdots B_{i+d}$ 中有比它大的数。

那么这么考虑，已经加入 $A_1 \cdots A_{i-1}$。对于 $A_i$ ，如果大于 $\min(A_1 \cdots A_{i-1},B_1 \cdots B_{\min(i+d,n)})$ 会有解。

那么就逐个加入 $A_i$ 计算贡献的概率，而且定好了 $A_i$ 之后，剩下的值可以简单地视作排列，而且同时新加入的 $B_{i+d}$ 不影响，因为和 $i-1$ 的子情况无关。这是概率统计的“排列下降技巧”。对于一个排列，取出一些元素，递归到子问题。

![pic](https://ooo.0x0.ooo/2025/02/16/OGd9Vb.png)

[CODE](https://atcoder.jp/contests/agc053/submissions/62832200)

---

## 作者：zifanwang (赞：0)

首先容易发现含有 $2n$ 的那一堆不会被删掉，记其为 $a$，另一堆为 $b$。记 $p_i$ 表示最小的 $j$ 满足 $j\ge i\land a_j>b_i$，那么至少要在 $a$ 堆中删除 $\max\{p_i-i,0\}$ 个数才能删除 $b_i$，那么答案就是 $n+\max\{p_i-i\}$。

记 $f(x)$ 表示操作次数 $\le x+n$ 的概率，那么期望操作次数就是 $2n-\sum_{i=0}^{n-1}f(i)$，容易得到：

$$f(x)=\prod_{i=1}^n \left(1-\frac{1}{i+\min\{i+x,n\}}\right)$$

分奇偶处理前/后缀逆元积即可，时间复杂度 $\mathcal O(n+\log B)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 2000003
#define md 1000000007
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rept(i,a,b) for(int i=(a);i<(b);++i)
#define drep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int n;
ll ans,inv[mxn],d[mxn],d1[mxn],d2[mxn],d3[mxn],d4[mxn];
ll power(ll x,int y){
	ll ans=1;
	for(;y;y>>=1){
		if(y&1)ans=ans*x%md;
		x=x*x%md;
	}
	return ans;
}
ll solve(int k){
	ll ans=d[n*2-k+1];
	if(k&1)ans=ans*d1[n*2-k]%md*d3[k+1]%md;
	else ans=ans*d2[n*2-k]%md*d4[k+1]%md;
	return ans;
}
signed main(){
	cin>>n,ans=n;
	inv[1]=1;
	rep(i,2,n<<1)inv[i]=inv[md%i]*(md-md/i)%md;
	d[(n<<1)+1]=1;
	drep(i,(n<<1),1)d[i]=d[i+1]*(1-inv[i])%md;
	d1[1]=1;
	rep(i,2,(n<<1)){
		if(i&1)d1[i]=d1[i-1]*(1-inv[i])%md;
		else d1[i]=d1[i-1];
	}
	d3[n<<1]=power(d1[n<<1],md-2);
	drep(i,n<<1,2){
		if(i&1)d3[i-1]=d3[i]*(1-inv[i])%md;
		else d3[i-1]=d3[i];
	}
	d2[1]=1;
	rep(i,2,(n<<1)){
		if(!(i&1))d2[i]=d2[i-1]*(1-inv[i])%md;
		else d2[i]=d2[i-1];
	}
	d4[n<<1]=power(d2[n<<1],md-2);
	drep(i,n<<1,1){
		if(!(i&1))d4[i-1]=d4[i]*(1-inv[i])%md;
		else d4[i-1]=d4[i];
	}
	rept(i,0,n)ans=(ans-solve(i))%md;
	cout<<(ans*2%md+md)%md;
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc053_c)

**题目大意**

> 给定 $a_1\sim a_n,b_1\sim b_n$，所有元素是 $1\sim 2n$ 的一个随机排列，每次操作选定一个 $k$，比较 $a_k,b_k$ 的大小：
>
> - 如果 $a_k<b_k$ 那么删除 $a_k$ 并把 $a_{k+1}\sim a_n$ 平移到 $a_k\sim a_{n-1}$。
> - 否则删除 $b_k$ 并做相同操作。
>
> 求清空其中一个序列的最小操作次数的期望。
>
> 数据范围：$n\le 10^6$。

**思路分析**

先考虑如何刻画最小操作次数，不妨设 $2n$ 在 $a$ 中，那么一定要清空 $b$。

考虑每个 $b_i$ 被删除至少要删掉几个 $a$，设 $p_i$ 为最小的 $a_{p_i}>b_i$ 的点，那么至少需要 $\max(0,p_i-i)$ 次操作才能删掉 $b_i$。

因此答案有下界 $n+\max\{p_i-i\}$，下面给出构造：如果存在 $a_i>b_i$，那么直接操作 $i$ 删除一个 $b$ 中元素。

否则找到第一个 $p_i>i$ 的 $i$ 并操作，此时所有 $p_i>i$ 的 $p_i$ 都会 $-1$。

因此答案就是 $n+\max\{p_i-i\}$，不难把答案转成统计每个 $\max\{p_i-i\}\le k$ 的概率。

考虑什么时候 $\max\{p_i-i\}\le k$，那么只要求出第一个 $p_i-i>k$ 的概率，此时 $b_i$ 大于 $a_1\sim a_{\min(n,i+k)}$。

并且对于 $b_1\sim b_{i-1}$，由于 $i$ 是第一个非法位置，因此 $b_1\sim b_{i-1}$ 都要小于 $a_1\sim a_{\min(n,i+k)}$。

因此 $i$ 是第一个非法位置的概率就是 $\dfrac1{i+\min(i+k,n)}$，总概率就是 $\prod\limits_{i=1}^n\left(1- \dfrac{1}{i+\min(i+k,n)}\right)$，预处理前后缀积即可。

概率最终要 $\times 2$ 因为可以交换 $a,b$。

时间复杂度 $\mathcal O(n\log P)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e6+5,MOD=1e9+7;
ll ksm(ll a,ll b=MOD-2) { ll s=1; for(;b;a=a*a%MOD,b>>=1) if(b&1) s=s*a%MOD; return s; }
int n;
ll fac[MAXN],ifac[MAXN];
signed main() {
	scanf("%d",&n);
	fac[0]=ifac[0]=fac[1]=ifac[1]=1;
	for(int i=2;i<MAXN;++i) ifac[i]=ksm(fac[i]=i*fac[i-2]%MOD);
	ll ans=2*n;
	for(int k=0;k<n;++k) {
		//prod 1-1/min(i+k,n)+i
		//i=1~n-k: 2i+k-1/2i+k, else n+i-1/n+i
		ll w=(2*n-k)*ksm(2*n)%MOD*fac[2*n-k-1]%MOD*ifac[2*n-k]%MOD;
		if(k) w=w*ifac[k-1]%MOD*fac[k]%MOD;
		ans=(ans+2*(MOD-w))%MOD;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

