# Dynamic Color Problem

## 题目描述

你在和 AI 下『连子棋』！你们有黑白两个颜色的棋子。

这盘棋的规则是：双方轮流下棋，棋子放满整个棋盘后，再来统计分数。如果每有一整行或一整列颜色 **不完全相同**，那么你就获得 $1$ 分。如果每有一整行或一整列颜色 **完全相同**，那么 AI 就获得 $1$ 分。当你的分数为奇数且 AI 的分数为偶数时，那么你就胜利了！否则，AI 胜利。

你和 AI 对弈了 $T$ 局，第 $i$ 局的棋盘大小为 $n\times m $。双方每一回合都可以选择下黑或者下白，下棋的位置不能和之前重复。那么请计算棋盘最终形态的方案数使得你能获胜。

两种下棋方式不同，当且仅当最终棋盘的形态不同，即棋盘上存在一个位置，使得两种棋盘在此位置的颜色不同。答案可能很大，请对 $998244353$ 取模。


## 说明/提示

**【样例解释 $\mathbf 1$】**

对于第 $2$ 局棋盘大小 $2\times 3$ 有下列两种棋盘形式（总共 $32$ 种棋盘形式，不一一列出）：

![](https://cdn.luogu.com.cn/upload/image_hosting/3dt0b498.png)

上面两种情况，你获得 $3$ 分，AI 获得 $2$ 分，故你获胜。

---

**【数据规模与约定】**


**本题开启子任务捆绑测试**。本题自动开启 O2 优化。
* Subtask 1（15 pts）：$2\leq n,m\leq 4$。
* Subtask 2（15 pts）：$2\leq n,m\leq 6$。
* Subtask 3（8 pts）：$2\leq n,m\leq 20$。
* Subtask 4（8 pts）：$2\leq n,m\leq 100$。
* Subtask 5（10 pts）：$2\leq n,m\leq 1000$。
* Subtask 6（44 pts）：$2\leq n,m\leq 10^6$。


对于所有测试点满足 $1\leq T\leq 5$，$2\leq n,m\leq 10^6$。


## 样例 #1

### 输入

```
5
2 2
2 3
2 5
4 3
4 5```

### 输出

```
0
32
512
2240
608864```

## 样例 #2

### 输入

```
4
1000 999
1000000 999999
999999 1000000
677777 66778
```

### 输出

```
163503730
154415889
154415889
127032970```

# 题解

## 作者：Kingna (赞：8)

## Subtask 1

可以直接 $2^{nm}$ 暴力求解，实现的好的话其实可以拿 $30$ 分。

## Subtask 3~4

留给一些奇怪的做法。但其实没有人刻意去拿这档分。

## Subtask 5

可以发现你获得的分数和 AI 获得的分数相加等于 $n+m$。则 $n+m$ 为偶数时，一定不存在合法解。又因为当 $n+m$ 为奇数时，若你获得的分数是偶数，那么 AI 一定是奇数，反之亦然。故两者一一对应，只需要求出其中一种方案数就是答案。

一整行或一整列颜色不完全相同的情况难以处理，所以考虑处理一整行或一整列颜色完全相同的情况。即现在需要解决这个问题：一整行或一整列颜色完全相同的数量是偶数的方案数。再反过来，先考虑为奇数的方案，再用总方案去减。

根据惯用做法，直接容斥/二项式反演。先考虑容斥系数的求解：对于答案至少有 $i$ 个产生贡献的情况，恰好是 $i$ 是最后一次计算。

* 当答案至少有 $0$ 个产生贡献时：容斥系数为 $0$。
* 当答案至少有 $1$ 个产生贡献时：之前产生 $\binom{1}{0}\times 0=0$ 的贡献，所以此时容斥系数为 $1$。
* 当答案至少有 $2$ 个产生贡献时：之前产生 $\binom{2}{0}\times 0+\binom{2}{1}\times 1=2$ 的贡献，所以此时容斥系数为 $-2$。
* 当答案至少有 $3$ 个产生贡献时：之前产生 $\binom{3}{0}\times 0+\binom{3}{1}\times 1+\binom{3}{2}\times -2=-3$ 的贡献，所以此时容斥系数为 $4$。
* 当答案至少有 $4$ 个产生贡献时：之前产生 $\binom{4}{0}\times 0+\binom{4}{1}\times 1+\binom{4}{2}\times -2+\binom{4}{3}\times 4=8$ 的贡献，所以此时容斥系数为 $-8$。

因此可以得到答案至少为 $x$ 时，容斥系数为 $(-2)^{x-1}$。

接下来计算答案：


* 只有行产生贡献：$\sum_{i=1}^n (-2)^{i-1}\binom{n}{i}2^i2^{(n-i)m}$。具体含义为从 $n$ 行中选择 $i$ 列颜色相同，他们颜色方案数为 $2^i$。其余位置方案数为 $2^{(n-i)m}$。
* 只有列产生贡献：$\sum_{i=1}^m (-2)^{i-1}\binom{m}{i}2^i2^{(m-i)n}$。同理可得。
* 都产生贡献：枚举行列分别产生 $i$ 和 $j$ 的贡献：$\sum_{i=1}^n\sum_{j=1}^m (-2)^{i+j-1}\binom{n}{i}\binom{m}{j}2\times 2^{(m-j)(n-i)}$​。如果列的颜色相同，行的颜色也相同，那么总的颜色只有全黑和全白两种。

复杂度 $\mathcal O(nm)$。期望得分 $56$ 分。

## Subtask 6

考虑 $100$ 分的算法：

优化上面部分的第三个式子：

$$
\begin{align*}
f(n,m) &= \sum_{i=1}^n\sum_{j=1}^m (-2)^{i+j - 1}\binom{n}{i}\binom{m}{j}2\times 2^{(m - j)(n - i)} \\
&= \sum_{i=1}^n2 (-2)^{i - 1}\binom{n}{i}\sum_{j=1}^m (-2)^{j}\binom{m}{j}2^{(m - j)(n - i)} \\
&= \sum_{i=1}^n2 (-2)^{i - 1}\binom{n}{i}\sum_{j=1}^m \binom{m}{j}(-2)^{j}(2^{n - i})^{m - j} \\
&= \sum_{i=1}^n2 (-2)^{i - 1}\binom{n}{i} [(-2 + 2^{n - i})^m - 2^{(n - i)m}] \
\end{align*}
$$

因此复杂度可以做到 $O(T(n+m)\log n)$。可以预处理二的次幂来减小常数，但是始终需要快速幂。期望得分 $100$。

---

## 作者：dAniel_lele (赞：2)

首先我们注意到要求的即为所有方案数中，$(-1)^s$ 之和，其中 $s$ 为同色的行或列。然后算出答案是容易的。

考虑容斥，钦定一些行列同色。

先考虑钦定 $x$ 行/列的容斥系数 $c_x$，$c_x=(-1)^x-\sum_{i=0}^{x-1}c_i\binom{x}{i}$。

我们声称 $c_i=(-2)^i$，以下是归纳证明：

$$c_x=(-1)^x-\sum_{i=0}^{x-1}(-2)^i\binom{x}{i}$$
$$=(-1)^x-\sum_{i=0}^{x}(-2)^i\binom{x}{i}+(-2)^x$$
$$=(-1)^x-(-2+1)^x+(-2)^x$$
$$=(-2)^x$$

设钦定了 $x_1$ 行 $x_2$ 列，分以下三类讨论：

* $x_1=x_2=0$ 时，显然为 $2^{nm}$。
* $x_1=0$ 时（$x_2=0$ 同理），答案为 $\binom{n}{x_1}2^{x_1}2^{m(n-x_1)}$，直接计算即可，即选出钦定行，分别选出钦定颜色，然后剩下的任意。
* 否则，答案为 $2\binom{n}{x_1}\binom{m}{x_2}2^{(n-x_1)(m-x_2)}$（注意到钦定的颜色必须相同）。这是无法暴力计算的。

考虑如何计算 $\sum_{x_1=1}^n\sum_{x_2=1}^m2\binom{n}{x_1}\binom{m}{x_2}2^{(n-x_1)(m-x_2)}(-2)^{x_1+x_2}$。暴力枚举 $x_1$，提出无关项，对剩下部分推式子：

$$\sum_{x_2=1}^m\binom{m}{x_2}2^{(n-x_1)(m-x_2)}(-\frac{1}{2})^{m-x_2}$$
$$=\sum_{x_2=1}^m\binom{m}{x_2}(-2^{n-x_1-1})^{m-x_2}$$
$$=\sum_{x_2=0}^m\binom{m}{x_2}(-2^{n-x_1-1})^{m-x_2}-(-2^{n-x_1-1})^m$$
$$=(-2^{n-x_1-1}+1)^{m-x_2}-(-2^{n-x_1-1})^m$$

然后就可以计算了。总复杂度 $O(T\max(n,m)\log p)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
const int mod=998244353,inv2=(mod+1)/2;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int fac[2000005],inv[2000005];
void init(){
	fac[0]=1; for(int i=1;i<=2000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[2000000]=qp(fac[2000000],mod-2); for(int i=1999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[j]%mod*inv[i-j]%mod;
}
int pw2[2000005],pw2m[2000005];
int tpw[2000005];
void solve(){
	int n,m; cin>>n>>m;
	if(!((n+m)&1)){
		cout<<0<<"\n";
		return ;
	}
	int ans=qp(2,n*m);
	tpw[0]=1; for(int i=1;i<=n;i++) tpw[i]=tpw[i-1]*pw2[m]%mod;
	for(int i=1;i<=n;i++) (ans+=C(n,i)*pw2[i]%mod*tpw[n-i]%mod*pw2m[i])%=mod;
	tpw[0]=1; for(int j=1;j<=m;j++) tpw[j]=tpw[j-1]*pw2[n]%mod;
	for(int j=1;j<=m;j++) (ans+=C(m,j)*pw2[j]%mod*tpw[m-j]%mod*pw2m[j])%=mod;
	for(int i=1;i<=n;i++){
		if(i!=n) (ans+=2*C(n,i)*pw2m[m+i]%mod*(qp(mod+1-pw2[n-i-1],m)+mod-qp(mod-pw2[n-i-1],m)))%=mod;
		else (ans+=2*C(n,i)*pw2m[m+i]%mod*(qp(mod+1-inv2,m)+mod-qp(mod-inv2,m)))%=mod;
	}
	cout<<(ans+qp(2,n*m))*inv2%mod<<"\n";
}
signed main(){
	init();
	pw2[0]=1; for(int i=1;i<=2000000;i++) pw2[i]=pw2[i-1]*2%mod;
	pw2m[0]=1; for(int i=1;i<=2000000;i++) pw2m[i]=pw2m[i-1]*(mod-2)%mod;
	int t; cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：happybob (赞：0)

$2 \mid n+m$ 时无解。

有一个显然的二项式反演。记 $f_i$ 为恰有 $i$ 行列完全相同的方案数，$g_i = \sum \limits_{j \geq i} f_j \dbinom{j}{i}$，$g_i$ 容易计算，枚举 $a+b=i$ 表示 $a$ 行 $b$ 列全相同，若 $a, b>0$ 则式子大概是 $2\dbinom{n}{a}\dbinom{m}{b}2^{(n-a)(m-b)}$，$a=0$ 或 $b=0$ 需要特殊考虑，但也是容易的。

求出 $g$ 后对 $f$ 二项式反演即可得到一个平方做法。

把式子具体写出来，大概是 $\sum \limits_{2 \mid x} \sum \limits_{y \geq x} (-1)^{y-x}\dbinom{y}{x}g_y$。$y$ 固定时有 $\sum \limits_{x\leq y,2|x} (-1)^{y-x}\dbinom{y}{x} = -((-2)^{y-1})$。如果直接枚举 $y$，发现 $g_y$ 并不容易快速算，但是可以枚举 $a$，对于 $b$ 来说可以发现是一个二项式展开的形式，最终大概是  $-\sum \limits_{a} \dbinom{n}{a}(-2)^{a-1}(-2+2^{n-a})^m$ 直接计算即可，对于 $a=0$ 或 $b=0$ 需要特殊计算，复杂度 $O(Tn\log n)$。

---

