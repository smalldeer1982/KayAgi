# Rainbow Balls

## 题目描述

You have a bag of balls of $ n $ different colors. You have $ a_{i} $ balls of the $ i $ -th color.

While there are at least two different colored balls in the bag, perform the following steps:

- Take out two random balls without replacement one by one. These balls might be the same color.
- Color the second ball to the color of the first ball. You are not allowed to switch the order of the balls in this step.
- Place both balls back in the bag.
- All these actions take exactly one second.

Let $ M=10^{9}+7 $ . It can be proven that the expected amount of time needed before you stop can be represented as a rational number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850F/2c40be71c60fe708ee9e4e80e2cd7a26163f3bd6.png), where $ P $ and $ Q $ are coprime integers and where $ Q $ is not divisible by $ M $ . Return the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850F/a816c54f8859ee12f4e38a2cc4dba0d6f8dd5c0b.png).

## 说明/提示

In the first sample, no matter what happens, the balls will become the same color after one step.

For the second sample, we have 6 balls. Let’s label the balls from 1 to 6, and without loss of generality, let’s say balls 1,2,3 are initially color 1, balls 4,5 are color 2, and ball 6 are color 3.

Here is an example of how these steps can go:

- We choose ball 5 and ball 6. Ball 6 then becomes color 2.
- We choose ball 4 and ball 5. Ball 5 remains the same color (color 2).
- We choose ball 1 and ball 5. Ball 5 becomes color 1.
- We choose ball 6 and ball 5. Ball 5 becomes color 2.
- We choose ball 3 and ball 4. Ball 4 becomes color 1.
- We choose ball 4 and ball 6. Ball 6 becomes color 1.
- We choose ball 2 and ball 5. Ball 5 becomes color 1.

 At this point, the game ends since all the balls are the same color. This particular sequence took 7 seconds.It can be shown that the answer to this case is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850F/9f76609d2f8aa0999ab074d70f32e2692cee15a9.png).

## 样例 #1

### 输入

```
2
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
750000026
```

# 题解

## 作者：DeaphetS (赞：27)

貌似没看到有人用条件概率做这道题的，来整一个

[可能更好的阅读体验](https://www.cnblogs.com/DeaphetS/p/17168309.html)

题目链接：[F - Rainbow Balls](https://codeforces.com/contest/850/problem/F)

题目大意：一开始有 $n$ 种不同颜色的球，第 $i$ 种颜色有 $a_i$ 个。每次操作随机**先后**选取两个球，并将后取出来的球颜色染成前者的颜色。问期望进行多少次操作后所有球的颜色均相同。

### 符号约定与解释

$P(x)$：事件 $x$ 发生的概率

$P(x,y)$：事件 $x,y$ 同时发生的概率

$P(x|y)$：在事件 $y$ 发生的条件下，事件 $x$ 发生的概率。显然有 $P(x|y)=\frac{P(x,y)}{P(y)}$

$P_{i,j}$：某时刻某颜色的个数为 $i$，且下一时刻个数为 $j$ 的概率。显然只有 $j=i-1,i,i+1$ 是有效的

$N_i$：某颜色的球个数为 $i$

$x_k$：第 $k$ 时刻某颜色的个数

$F_i$：最终局面为所有球都变为第 $i$ 种颜色这一事件，我们也称为第 $i$ 种颜色获胜

$E(N_i|F_j)$：当前颜色为 $j$ 的球的个数为 $i$，在事件 $F_j$ 发生的条件下，期望的操作次数

$P_{i,j}|F_k$：在事件 $F_k$ 发生的条件下，发生颜色个数从 $i$ 到 $j$ 转移的概率

可以得出，最终答案即为 $\sum_{i=1}^{n} E(N_{a_i}|F_i)\times P(F_i)$。

### 弱化版本 

先来考虑这么一个弱化版本的问题：若一开始每种颜色的球都恰好有一个怎么做？

此时，根据对称性质，$P(F_i)$ 固定为 $\frac{1}{n}$，于是此时答案就为 $\sum_{i=1}^{n} E(N_1|F_i)\times \frac{1}{n}=E(N_1|F_1)$ 。

而对任意 $i\in [1,n)$，有：

$$E(N_i|F_1)=1+E(N_{i-1}|F_1)\times P_{i,i-1}|F_1+E(N_{i}|F_1)\times P_{i,i}|F_1+E(N_{i+1}|F_1)\times P_{i,i+1}|F_1 \tag{1}$$ 

这里需要注意的是，$P_{1,0}|F_1$ 必然是为 $0$ 的，这是因为我们已经制定了 $F_1$ 这一前提条件，所以对应颜色的球个数是不可能为零的。

于是这题的瓶颈就变成了求 $P_{i,j}|F_1$，以求 $P_{i,i-1}|F_1$ 为例，我们首先可以将其改写成 $P(x_{k+1}=i-1|x_k=i,F_1)$，现在我们开始求对应的值。
$$
\begin{aligned}
P(x_{k+1}=i-1|x_k=i,F_1)& = \frac{P(x_{k+1}=i-1,x_k=i,F_1)}{P(x_k=i,F_1)}\\
& = \frac{P(x_{k+1}=i-1,F_1|x_k=i)\times P(x_k=i)}{P(F_1|x_k=i)\times (x_k=i)}\\
& = \frac{P(F_1|x_{k+1}=i-1,x_{k}=i)\times P(x_{k+1}=i-1|x_{k}=i)}{P(F_1|x_k=i)}\\
& = \frac{\frac{i-1}{n}\times \frac{i(n-i)}{n(n-1)}}{\frac{i}{n}}\\
& = \frac{(n-i)\times (i-1)}{n(n-1)}
\end{aligned}
$$
过程中化简的思路大致就是把公共项提出来，然后变成计算 $P(F_1|x_k=i)$，即某时刻颜色 $1$ 的个数为 $i$ 时，其获胜的概率。对应值的计算也很简单，因为 $n$ 个颜色不同的球每个球的获胜概率均为 $\frac{1}{n}$，那么此情况下可以看做有其中 $i$ 个颜色被当作颜色 $1$，于是 $P(F_1|x_k=i)=\frac{i}{n}$。

采用类似的计算思路，最终我们可以得出：

$$P_{i,i-1}|F_1=\frac{(n-i)\times (i-1)}{n(n-1)},P_{i,i+1}|F_1=\frac{(n-i)\times (i+1)}{n(n-1)},P_{i,i}|F_1=1-\frac{(n-i)\times 2i}{n(n-1)}$$

那么令 $f_i=E(N_i|F_1)$，将结果代入式 $(1)$，可以得到如下结果：

$$f_i=1+\frac{(n-i)\times (i-1)}{n(n-1)}f_{i-1}+\frac{(n-i)\times (i+1)}{n(n-1)}f_{i+1}+(1-\frac{(n-i)\times 2i}{n(n-1)})f_i$$

$$\frac{(n-i)\times 2i}{n(n-1)}f_i=1+\frac{(n-i)\times (i-1)}{n(n-1)}f_{i-1}+\frac{(n-i)\times (i+1)}{n(n-1)}f_{i+1}$$

$$2i(n-i)f_i=n(n-1)+(n-i)(i-1)f_{i-1}+(n-i)(i+1)f_{i+1} \tag{2}$$

根据初始条件 $f_n=0$，我们最终可以推出 $f_1=(n-1)^2$，具体过程放在最后。

### 回到本题

令 $m=\sum_{i=1}^{n}a_i$ ，那么可以得出 $P(F_i)=\frac{a_i}{m}$。而根据对称性，$E(N_{a_i}|F_i)=E(N_{a_i}|F_1)$。于是我们就可以得到 $ans=\sum_{i=1}^{n} f_{a_i}\times \frac{a_i}{m}$，而 $f_i$ 的值可以直接根据 $(2)$ 式递推求出，最终我们就能以 $O(\max(a_i)\cdot \log M)$ 的时间复杂度解决此题。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100010
#define LL long long
#define MOD 1000000007
int n,m,x,c[N],f[N],ans;
LL qow(LL x,LL y){return y?(y&1?x*qow(x,y-1)%MOD:qow(x*x%MOD,y/2)):1;}
int main()
{
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&x);
		c[x]++;
		n+=x;
	}
	f[1]=1ll*(n-1)*(n-1)%MOD;
	for(int i=1;i<N-5;i++){
		LL tot=2ll*i*(n-i)%MOD*f[i]%MOD;
		tot=(tot+MOD-1ll*(i-1)*(n-i)%MOD*f[i-1]%MOD)%MOD;
		tot=(tot+MOD-1ll*n*(n-1)%MOD)%MOD;
		tot=tot*qow(i+1,MOD-2)%MOD*qow(n-i,MOD-2)%MOD;
		f[i+1]=tot;
		ans=(ans+qow(n,MOD-2)*i%MOD*f[i]%MOD*c[i])%MOD;
	}
	printf("%d\n",ans);
}
```

### 推出 $f_1$ 的过程

$2i(n-i)f_i=n(n-1)+(n-i)(i-1)f_{i-1}+(n-i)(i+1)f_{i+1}$

$2i\cdot f_i=\frac{n(n-1)}{n-i}+(i-1)f_{i-1}+(i+1)f_{i+1}$

令 $t_i=i\cdot f_i$，对 $i\in [1,n)$ 就有 $2t_i=\frac{n(n-1)}{n-i}+t_{i-1}+t_{i+1}$，且 $t_0=t_n=0$

那么设 $t_{i}=a_i\cdot t_{i-1}+b_i$，借由 $t_n=0$ 可以推出 $a_{n-1}=\frac{1}{2},b_{n-1}=\frac{n(n-1)}{2}$。考虑找到 $a_i,b_i$ 的递推式从而推出 $a_2,b_2$ 的值，与 $i=1$ 的情况 $2t_1=n+t_2$ 联立求解

$2t_i=\frac{n(n-1)}{n-i}+t_{i-1}+t_{i+1}=\frac{n(n-1)}{n-i}+t_{i-1}+a_{i+1}\cdot t_i+b_{i+1}$

$a_i=\frac{1}{2-a_{i+1}},b_i=\frac{1}{2-a_{i+1}}(b_{i+1}+\frac{n(n-1)}{n-i})$

手推几项不难瞪眼看出 $a_i=\frac{n-i}{n-i+1},b_i=\frac{n-i}{n-i+1}\cdot n(n-1)$，于是就有

$$ \left\{\begin{matrix}2t_1 =n+t_2\\t_2 = \frac{n-2}{n-1}t_1+n(n-2) \end{matrix}\right.$$

最后解得 $f_1=t_1=(n-1)^2$



---

## 作者：樱雪喵 (赞：27)

考虑钦定最后所有球的颜色为 $x$。设 $f_i$ 表示已有 $i$ 个球为给定颜色。

设 $p$ 为选出两个球，第一个颜色为 $x$，第二个颜色不为 $x$ 的概率。则：
$$p=\frac{i(s-i)}{s(s-1)}$$
$$f_i=f_{i-1}p+f_{i+1}p+f_i(1-2p)+v$$
其中 $v$ 为此步对答案的贡献，即**在当前局面下 $x$ 成为留到最后颜色的概率**。

设 $g_i$ 为有 $i$ 个 $x$ 时留到最后的概率。则有
$$g_0=0,g_s=1$$
$$g_i=g_{i-1}p+g_{i+1}p+(1-2p)g_i$$
$$g_i-g_{i-1}=g_{i+1}-g_i$$
解得
$$g_i=v=\frac{i}{s}$$
$$f_i=f_{i-1}p+f_{i+1}p+f_i(1-2p)+\frac{i}{s}$$
移项，得
$$f_i-f_{i+1}=f_{i-1}-f_i+\frac{s-1}{s-i}$$
$$f_{i+1}=2f_i-f_{i-1}-\frac{s-1}{s-i}$$
考虑边界，当 $i=1$ 时不存在 $f_0$，代入上式得
$$f_2=2f_1-1$$
显然 $f_s=0$。

那么
$$f_1=f_1-f_s=\sum\limits_{i=2}^s f_i-f_{i-1}$$
$$=(s-1)(f_1-f_2)+(s-2)(s-1)$$
将 $f_2=2f_1-1$ 代入，得
$$f_1=\frac{(s-1)^2}{s}$$
至此，已知 $f_1$，$f_2$，根据 $f_{i+1}=2f_i-f_{i-1}-\frac{s-1}{s-i}$ 递推即可。

答案即为 $\sum\limits_{i=1}^nf_{a_i}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=1e5+5;
int n,a[N],f[N],s,mx;
int qpow(int n,int k)
{
	int res=1;
	for(;k;n=n*n%mod,k>>=1)
		if(k&1) res=res*n%mod;
	return res;
}
int inv(int x) {return qpow(x,mod-2);}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) 
	{
		scanf("%lld",&a[i]);
		s+=a[i],mx=max(mx,a[i]);
	}
	f[1]=(s-1)*(s-1)%mod*inv(s);
	f[2]=2*f[1]-1;
	for(int i=2;i<mx;i++) 
	{
		f[i+1]=(2*f[i]%mod-f[i-1]-(s-1)*inv(s-i)%mod)%mod;
		f[i+1]=(f[i+1]+mod)%mod;
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans=(ans+f[a[i]])%mod;
	printf("%lld\n",ans);
	return 0;
}	
```

---

## 作者：Cyhlnj (赞：17)

首先可以枚举**最后的球都是什么颜色**的

设 $f_i$ 表示当前有 $i$ 个钦定的颜色的球，把所有球都变成这种颜色的期望时间

显然 $f_0$ 不存在

设 $s=\sum_{i=1}^{n}a_i$ 那么 $f_s=0$

对于 $0<i<s$ 可以得到一个 $DP$ 方程

$$f_i=(f_{i-1}+f_{i+1})p+(1-2p)f_i+v$$

其中 $p$ 表示选出两个球不同色的概率 $\frac{i(s-i)}{s(s-1)}$，$v$ 表示贡献的期望时间

**注意不是 $1$!!!**

结论就是 $v=\frac{i}{s}$

**考虑 $v$ 是个什么东西**~~下面纯属瞎bb~~

由于不能到 $0$ 这个状态，所以 $i$ 只能算到达那些走到 $s$ 的贡献

那么 $v$ 相当于走到 $s$ 的概率，也就是走一步的期望

也就是数轴上一个点 $x$ 每次等概率向左或者向右走，求走到 $0$ 之前到达 $s$ 的概率

这个是个经典问题

设 $g_i$ 表示 $i$ 到 $s$ 的概率，那么 $g_0=0,g_s=1$

$g_i=pg_{i-1}+pg_{i+1}+(1-2p)g_i$

那么 $g_i-g_{i-1}=g_{i+1}-g_i$

可以得到概率为 $\frac{i}{s}$

~~瞎bb完了~~

那么现在有一个方程

$$f_i=(f_{i-1}+f_{i+1})p+(1-2p)f_i+\frac{i}{s} \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ (1)$$

由于 $f_0$ 不存在那么

$$f_1=f_2p+(1-2p)f_1+\frac{1}{s}$$

即 $f_2=2f_1-1$

由 $(1)$ 可以得到

$$f_i-f_{i+1}=f_{i-1}-f_i+\frac{s-1}{s-i} \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ (2)$$

所以

$$f_1=f_1-f_s=\sum_{i=2}^{s}f_{i-1}-f_i=(s-1)(f_1-f_2)+\sum_{i=2}^{s-1}\frac{s-1}{s-i}(s-i)$$

代入 $f_2=2f_1-1$ 得到

$$f_1=\frac{(s-1)^2}{s}$$

那么求出 $f_2$ 之后，根据 $(2)$ 就可以推出所有的 $f$ 了

**最后**答案就是 $\sum_{i=1}^{n}f_{a_i}$

```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod(1e9 + 7);
const int maxn(1e5 + 5);

int mx = 1e5, n, cnt[maxn], sum, f[maxn], ans;

inline void Inc(int &x, int y) {
	if ((x += y) >= mod) x -= mod;
}

inline int Pow(ll x, int y) {
	register ll ret = 1;
	for (; y; y >>= 1, x = x * x % mod)
		if (y & 1) ret = ret * x % mod;
	return ret;
}

int main() {
	scanf("%d", &n);
	register int i;
	for (i = 1; i <= n; ++i) scanf("%d", &cnt[i]), sum += cnt[i];
	f[1] = 1LL * (sum - 1) * (sum - 1) % mod * Pow(sum, mod - 2) % mod;
	f[2] = (2 * f[1] % mod + mod - 1) % mod;
	for (i = 2; i < mx; ++i)
		f[i + 1] = ((2 * f[i] % mod - f[i - 1] + mod) % mod - 1LL * (sum - 1) * Pow(sum - i, mod - 2) % mod + mod) % mod;
	for (i = 1; i <= n; ++i) Inc(ans, f[cnt[i]]);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：zhoukangyang (赞：12)

考虑最后变成哪一种颜色。

设  $s = \sum\limits_{i=1}^n a_i$

设现在有 $k$ 种当前颜色, 需要全部变成该种颜色, 期望步数为 $f_k$。

考虑状态转移。设 $p$ 为取出两个球颜色不同的概率。

$f_i = (f_{i+1} + f_{i-1})p + (1 - 2p)f_i + v_i$

考虑 $v_i$。由于我们考虑的 $dp$ 是要求最后颜色是一定的，所以不能算上答案不是该颜色的答案。所以 $v_i$ 就是最终颜色为这种颜色的概率。

如果颜色变动了，而让另一种颜色变成该颜色和该颜色变成另一种颜色的概率是一样的，所以 $v_i = \frac{1}{2}(v_{i-1} + v_{i+1})$

所以 $2v_i = v_{i-1} + v_{i+1}$, $v_{i+1} - v_i = v_i - v_{i-1} (= t)$

又 $v_0 = 1, v_s = 1$

$$1 = v_s - v_0 = \sum\limits_{i=1}^s v_i - v_{i-1} = st$$

所以 $t = \frac{1}{s}$, $v_i = \frac{i}{s}$

所以$f_i = (f_{i+1} + f_{i-1})p + (1 - 2p)f_i + \frac{i}{s}$

$$2pf_i = (f_{i+1} + f_{i-1})p + \frac{i}{s}$$

$$2f_i = f_{i+1} + f_{i-1} + \frac{\frac{i}{s}}{p}$$

又 $p = \frac{i(s-i)}{s(s-1)}$

$$2f_i = f_{i+1} + f_{i-1} + \frac{\frac{i}{s}}{\frac{i(s-i)}{s(s-1)}}$$

$$2f_i = f_{i+1} + f_{i-1} + \frac{s-1}{s-i}$$

当 $i=1$ 时，不需要考虑 $f_0$。$2f_1 = f_2 -1$

显然的，$f_s = 0$

$$2f_i = f_{i+1} + f_{i-1} + \frac{s-1}{s-i}$$

$$f_i -  f_{i+1} = f_{i-1} - f_i  + \frac{s-1}{s-i}$$

$$f_{i+1} - f_i = f_i - f_{i-1} - \frac{s-1}{s-i}$$

而 $f_1 = f_1 - f_s = \sum\limits_{i=2}^s f_i - f_{i-1}$

$$=\sum\limits_{i=2}^s (f_1 - f_2) + \sum\limits_{j=2}^{i-1} \frac{s-1}{s-j}$$ 

$$= (s-1)(f_1-f_2) + \sum\limits_{i=2}^s\sum\limits_{j=2}^{i-1} \frac{s-1}{s-j}$$

$$=(s-1)(f_1-f_2) + \sum\limits_{j=2}^{s-1} \frac{s-1}{s-j} * (s-j)$$

$$=(s-1)(f_1-f_2) + \sum\limits_{j=2}^{s-1} (s-1)$$

$$=(s-1)(f_1-f_2) + (s-2)(s-1)$$

而$f_1 - f_2 = f_1 - (2 f_1 - 1)  = 1 - f_1$

$$f_1 = (s-1)(f_1-f_2) + (s-2)(s-1)$$

$$f_1 = (s-1)(1-f_1) + (s-2)(s-1)$$

$$f_1 = s-1 + (s-1)f_1 + (s-2)(s-1)$$

$$sf_1 = (s-1)^2$$

$$f_1 = \frac{(s-1)^2}{s}$$

答案为 $\sum\limits_{i=1}^n f_{a_i}$

推到 $max(a_i)$ 即可。

```cpp
#include<bits/stdc++.h>
#define N 2510
#define M 100010
#define mod 1000000007
using namespace std;
int qpow(int x, int y) {
    if(x == 0) return 0;
    int res = 1;
    for(; y; x = 1ll * x * x % mod, y >>= 1) if(y & 1) res = 1ll * res * x % mod;
    return res;
}
int n, s, qny, a[N], dp[M], cc, ans, maxn;
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]), s = (a[i] + s) % mod, maxn = max(maxn, a[i]);
    dp[1] = 1ll * qpow(s, mod - 2) * (s - 1) % mod * (s - 1) % mod;
    cc = (dp[1] - 1) % mod;
    for(int i = 2; i <= maxn; i++) {
        dp[i] = (cc + dp[i - 1]) % mod;
        cc = (cc - 1ll * qpow((s - i + mod) % mod, mod - 2) * (s - 1) % mod + mod) % mod;
    }
    for(int i = 1; i <= n; i++) ans = (ans + dp[a[i]]) % mod;
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：zhylj (赞：10)

这篇题解大概讲的是本题势能函数做法的合法性。

部分节选自[我关于停时和鞅的学习笔记](http://zhylj.cc/index.php/archives/31/)

### 势能函数方法及其适用范围

对于随机事件序列 $\{A_0,A_1,\cdots,A_{\tau}\}$，$\tau$ 为其停时，终止状态为 $A_{\tau}$，而我们希望求得 $\mathbb E[\tau]$.

我们可以构造势能函数 $\Phi(A)$，满足：

- $\mathbb E[\Phi(A_{n+1})-\Phi(A_{n})\mid A_0,A_1,\cdots,A_n] = -1$.
- $\Phi(A_{\tau})$ 为常数，且 $\Phi(A) = \Phi(A_{\tau})$ 当且仅当 $A = A_{\tau}$.

设随机变量 $X_n = \Phi(A_n) + n$，则随机过程（即随机变量序列）$\{X_0,X_1,\cdots,X_{\tau}\}$ 是个离散时间鞅（即满足所有随机变量有限且 $\mathbb E[X_{n+1}\mid X_0,X_1,\cdots,X_n] = X_n$ 的随机过程）。

由 $\Phi(A) = \Phi(A_{\tau})$ 当且仅当 $A = A_{\tau}$ 我们可以推得 $\tau$ 也为 $\{X_0,X_1,\cdots,X_{\tau}\}$ 的停时。

而可选停时定理指出：对一个离散时间鞅 $\{X_0,X_1,\cdots,X_{\tau}\}$，其停时为 $\tau$，若满足 $X_n$ 一致有界，且 $\tau$ 几乎必然有限（事实上停时定理有三种条件，但似乎 OI 中最常用的是这种），则 $\mathbb E[X_{\tau}] = \mathbb E[X_0]$.

所以我们有：

$$
\mathbb E[X_{\tau}] =\mathbb E[X_0] \Rightarrow \mathbb E[\Phi(A_0)] - \Phi(A_{\tau}) = \mathbb E [\tau]
$$

### 回到本题

我们考虑类似地写出 $\Phi(A) = \sum f(a_i)$，$f(a)$ 需要满足的条件：

$$
\sum_i f(a_i) - 1
$$

应与下式相等：

$$
\sum_i \frac 1{m^{\underline 2}}((a_i^{\underline 2} + (m-a_i)^{\underline 2})f(a_i) + a_i(m-a_i)(f(a_i - 1) + f(a_i + 1)))
$$

把右边的 $f(a_i)$ 移过来，再展开一下式子可以得到：

$$
\sum_i \frac {a_i}{m^{\underline 2}}((a_i-m)2f(a_i) + (m-a_i)(f(a_i - 1) + f(a_i + 1))) = -1
$$

（我们有下降幂的完全平方公式 $(x-y)^{\underline 2} = x^{\underline 2} - 2xy + (-y)^{\underline 2}$）

$$
\sum_i \frac {a_i(m-a_i)}{m^{\underline 2}}(f(a_i - 1) - 2f(a_i) + f(a_i + 1)) = -1
$$

发现这个形式神似二维差分，于是我们设 $g(x) = f(x + 1) - f(x)$.

$$
\sum_i \frac {a_i(m-a_i)}{m^{\underline 2}}(g(a_i) - g(a_i - 1)) = -1
$$

经验表明，对于要将所有元素集中在一个集合的这类问题，我们可能可以以正比于某个集合的大小的期望减少这个集合的势能。

即：

$$
\frac {a(m-a)}{m^{\underline 2}}(g(a) - g(a - 1)) + \frac am = 0
$$

$$
g(a) - g(a - 1) = \frac{m-1}{a-m} < 0
$$

容易发现，这样设置总能满足 $\mathbb E[\Delta \Phi(A)] = -1$ 的条件，并且在本题中差分单调递减，又由于 $\sum a_i$ 不变，可以看作一个经典的背包模型，势能的最低点必然是把一个函数取完而其它不取。

于是我们证明了 $\Phi(A) = \Phi(A_{\tau})\Rightarrow A = A_{\tau}$.

不妨设 $f(0) = 0, g(0) = -\frac{m-1}{m}$（容易发现，我们几乎可以随意给 $g(0)$ 定一个值，只需要其满足 $\Phi(A) = \Phi(A_{\tau})\Rightarrow A = A_{\tau}$）

然后问题在于求 $f(m)$（$f(a_i)$ 可以直接递推求）：

$$
f(m) = \sum_{i=0}^{m-1}\sum_{j=0}^{i} \frac{m-1}{j-m} = \sum_{j=0}^{m-1}(m-j) \frac{m-1}{j-m} = -m(m-1)
$$

于是这道题就做完了。

时间复杂度 $\mathcal O(n + \max a_i)$.

### 代码

（我写的较丑，多了个 $\log$）

```cpp
const int kN = 5e5 + 5;
const ll kMod = 1e9 + 7;

ll QPow(ll a, ll b) {
	ll ret = 1, bas = a;
	for(; b; b >>= 1, bas = bas * bas % kMod)
		if(b & 1) ret = ret * bas % kMod;
	return ret;
}

int n, mx, a[kN]; ll f[kN], g[kN]; ll m, m_inv;
int main() { 
	rd(n);
	for(int i = 1; i <= n; ++i) {
		rd(a[i]);
		m = (m + a[i]) % kMod;
		mx = std::max(mx, a[i]);
	}
	g[0] = (kMod - QPow(m, kMod - 2) * (m - 1) % kMod) % kMod;
	for(int i = 1; i <= mx; ++i) {
		g[i] = g[i - 1] + QPow(i - m + kMod, kMod - 2) * (m - 1) % kMod;
		f[i] = f[i - 1] + g[i - 1];
	}
	ll bg = 0;
	for(int i = 1; i <= n; ++i)
		bg = (bg + f[a[i]]) % kMod;
	ll ed = (m - 1) * (kMod - m) % kMod;
	printf("%lld\n", (bg - ed + kMod) % kMod);
	return 0;
}
```

---

## 作者：luogubot (赞：10)

给定 $n$ 种颜色的球，第 $i$ 种颜色的球有 $a_i$ 个，每步进行如下操作：

- 依次不放回地选出两个球，把第一个球的颜色改为第二个球的颜色。

当所有球的颜色相同时，过程终止。求期望步数。

$1\leq n\leq 2500$，$1\leq a_i\leq 10^5$。

枚举每种颜色钦定它活到最后，每个情况就是独立的。令 $s=\sum a_i$。

设 $f_i$ 表示钦定的颜色有 $i$ 个球，目标是 $s$ 个球的期望步数，则答案是 $\sum f_{a_i}$。观察 $f$：

- $f_0$ 不存在，$f_s=0$。
- 要求的东西的本质是，在位置 $i$ 每步有 $p_i=\frac{i(s-i)}{s(s-1)}$ 的概率 $+1$ 或 $-1$，$1-2p_i$ 的概率不动，$f_i$ 表示从 $i$ 出发，不经过 $0$ 到达 $s$ 的期望步数。
- 对于 $i>1$，有转移 $f_i=(f_{i-1}+f_{i+1})p_i+(1-2p_i)f_i+{\color{red} 1}$，对于 $i=1$，有 $f_1=p_1f_2+(1-2p_1)f_1+{\color{red}1}$。

写出来发现不对，思考一下发现问题可能出在，对于“不能经过 $0$”这个限制，上述转移的处理仅仅是“因为 $f_0$ 不存在，所以把 $f_0$ 视作 $0$”，这样的处理是不合理的。实际上，转移时加上的权值需要再考虑。

另外求出一个 $P_i$ 表示当前在 $i$ 点，最终到达 $s$ 而不经过 $0$ 的**概率**，有 $P_0=0,P_s=1$，转移 $P_i=(P_{i-1}+P_{i+1})p_i+(1-2p_i)P_i$，带状矩阵手动消元/通过一些处理手段可以得到 $P_i=\frac{i}{s}$。

并且，$P_i$ 还可以理解为，从 $i$ 出发的所有路径（以 $0$ 终止或以 $s$ 终止）中，求出每条路径中每步概率的乘积作为权值，则等价于在这些路径中按照权值随机一条走，权值和为 1，其中能到达 $s$ 的路径权值和为 $P_i$。也就是说，把从 $i$ 开始走的这第一步，视作由随机出来的路径决定，则只有 $P_i$ 的概率选择了能到达 $s$ 的路径，这一步对期望步数的有效贡献就是 $1\times P_i$。

注意到此时转移中已经去掉了所有会到达 $0$ 的路径，$f_0$ 不应该再进一步参与实际转移，应该在转移中忽略掉 $f_0$，即视作 $f_0=0$。

接下来，可以对常规转移做一些处理，得到 $f_i-f_{i-1}=f_{i+1}-f_i+\frac{s-1}{s-i}$，则 $g_i=f_{i+1}-f_{i}=g_{i-1}-\frac{s-1}{s-i}$。则 $g_0=f_1-0=f_1$。对于 $i\ge1$，$g_i=f_1-\sum_{j=1}^i\frac{s-1}{s-j}$。

现在仍不可知的是 $f_1$，但已知的是方程 $f_s=0=f_1+\sum_{i=1}^{s-1}g_i$，对于后面那一坨，考虑 $-\frac{s-1}{s-j}$ 在 $i\in[j,s)$ 时均会被算到，共被算到 $s-j$ 次，故总贡献是 $-(s-1)$，同时有 $s-1$ 个这样的 $j$，则 $sf_1=(s-1)^2$，解得 $f_1=\frac{(s-1)^2}{s}$。

此时问题已经解决，因为 $g_0=f_1$ 已知，可以递推依次求得 $g_i,f_{i+1}$ 直到求得 $f_{\max\{a_i\}}$，复杂度瓶颈在于求逆元。每个逆元暴力算可以做到 $O(n+V\log p)$，线性求逆元可以做到 $O(n+V)$，其中 $V=\max\{a_i\}$。

---

## 作者：IceKylin (赞：4)

### CF850F Rainbow Balls 题解

*2800 期望题。

设 $\{A_n\}_{n\ge 0}$ 为一随机过程，令 $\tau$ 为其停时，我们希望构造势能函数 $\Phi$ 使得对于 $\forall k\in[0,\tau)$，都有 $E[\Phi(A_{k+1})-\Phi(A_k)]=1$，且 $\Phi(A_0)$ 值为常数，则 $E\tau=E\Phi(A_{\tau})-\Phi(A_0)$。

回到原题，考虑将势能进行拆分，不妨令 $\displaystyle\Phi(A_k)=\sum_{i}f(a_i)$，记 $s=\displaystyle\sum_{i}a_i$。

相邻两事件不同当且仅当取出了两个不同颜色的球，所以有：

$$E[\Phi(A_{k+1})-\Phi(A_k)]=\frac{1}{s(s-1)}\sum_{i\ne j}a_ia_j[f(a_i+1)+f(a_j-1)-f(a_i)-f(a_j)]=1$$

运用简单的有限微积分知识可以得到：

$$\frac{1}{s(s-1)}\sum_{i\ne j}a_ia_j[\Delta f(a_i)-\Delta f(a_j-1)]=1$$

化简得到：

$$\sum_ia_i(s-a_i)\Delta^2 f(a_i-1)=s(s-1)$$

解得 $\displaystyle\Delta^2f(x)=\frac{s-1}{s-x-1}$，定义边界条件为 $\displaystyle f(0)=0,f(1)=\frac{s-1}{s}$。这样递推即可得到所有的 $f(a_i)$，进而求和得到 $\Phi(A_0)$，而 $\Phi(A_{\tau})$ 则可以通过简单推式子得到值为 $s(s-1)$。

时间复杂度 $\Theta(\max a+n)$，代码参见 [link](https://codeforces.com/contest/850/submission/281055062)。

---

## 作者：Soulist (赞：4)


有 $n$ 个种颜色的球，第 $i$ 个颜色的球有 $a_i$ 个。当袋子有至少两个不同颜色的球时，执行以下操作：

1. 先后随机取出两个球，然后将第二个球涂成第一个球的颜色。（允许同色）

这些步骤均只需要 $1s$，输出无法操作的期望时间。

答案对 $10^9+7$ 取模。

$n\le 2500,a_i\le 10^5$

----

### Solution

~~看到你谷题解没有这个做法赶快过来复读一下~~

[$\textrm{更好的阅读体验}$](https://www.cnblogs.com/Soulist/p/13906776.html)

定义 $S_t$ 表示时间 $t$ 时的局面，定义 $\phi(S_t)$ 表示时间 $t$ 时的局面 $S_t$ 的势函数，我们希望选择合适的势函数，使得 $\phi(S_{end})$ 为一个常数，同时在期望意义下每次操作 $\phi$ 均会减少 $1$，那么这样 $\phi(S_{begin})-\phi(S_{end})$ 就是我们需要求的答案。

考虑定义 $f(a_i)$ 表示颜色 $i$ 有 $a_i$ 个球的势函数，定义 $F(S)=\sum f(a_i)$ 以表示局面的势函数，记 $m=\sum a_i$，那么有：

1. 我们有 $\frac{a_i(a_i-1)}{m(m-1)}$ 的概率选中两个 $i$ 类球
2. 我们有 $\frac{a_ia_j}{m(m-1)}$ 的概率将 $i$ 变成 $j$

于是有：

$$\begin{aligned}
    &\phi(S_{t+1})=\frac{1}{m(m-1)}\bigg(\sum_i a_i(a_i-1)\phi(S_t)+\sum_i\sum_{j\ne i} a_ia_j(\phi(S_t)+f(a_i+1)-f(a_i)+f(a_j-1)-f(a_j))\bigg)
    \\&=\frac{1}{m(m-1)}\bigg(\sum_i \Big(a_i(a_i-1)+a_i(m-a_i)\Big)\phi(S_t)+\sum_i a_i(m-a_i)(f(a_i+1)-2f(a_i)+f(a_i-1))\bigg)
    \\&=\frac{1}{m(m-1)}\bigg(\sum_i \Big( ma_i-a_i\Big)\phi(S_t)+\sum_i a_i(m-a_i)(f(a_i+1)-2f(a_i)+f(a_i-1))\bigg)
    \\&=\frac{1}{m(m-1)}\bigg(m(m-1)\phi(S_t)+\sum_i a_i(m-a_i)(f(a_i+1)-2f(a_i)+f(a_i-1))\bigg)
    \\&=\phi(S_t)+\frac{1}{m(m-1)}\sum_i a_i(m-a_i)(f(a_i+1)-2f(a_i)+f(a_i-1))
\end{aligned}$$

由于我们希望 $\phi(S_{t+1})-\phi(S_t)=-1$，于是有：

$$\begin{aligned}
    &-1=\frac{1}{m(m-1)}\sum_i a_i(m-a_i)(f(a_i+1)-2f(a_i)+f(a_i-1))
    \\&0=~m+\frac{1}{m-1}\sum_i a_i(m-a_i)(f(a_i+1)-2f(a_i)+f(a_i-1))
    \\&0=\sum_i a_i\bigg(1+\frac{m-a_i}{m-1}(f(a_i+1)-2f(a_i)+f(a_i-1))\bigg)
\end{aligned}$$

由于我们希望的是更一般的情况，于是这个式子对于任意的 $a_i$ 均成立，所以有：

$$1+\frac{m-x}{m-1}(f(x+1)+f(x-1)-2f(x))=0$$

恒成立。

故：

$$(f(x+1)+f(x-1)-2f(x))=-\frac{m-1}{m-x}$$

考虑定义 $g(x)=f(x)-f(x-1)$，那么 $g(x+1)-g(x)=-\frac{m-1}{m-x}$

接着我们认为 $g(0)$ 和 $f(0)$ 均为常数，那么有：

$$g(x)=g(0)+\sum_{j=0}^{x-1} \frac{1-m}{m-j}$$

$$\begin{aligned}
    &f(x)=f(0)+\sum_{j=1}^{x} g(j)
    \\&=f(0)+x\cdot g(0)-\sum_{j=0}^{x-1}\frac{(m-1)(x-j)}{m-j}
    \\&=f(0)+x\cdot g(0)-x(m-1)+\sum_{j=0}^{x-1}\frac{(m-1)(m-j-x+j)}{m-j}
    \\&=f(0)+x\cdot g(0)-x(m-1)+(m-1)(m-x)\sum_{j=0}^{x-1}\frac{1}{m-j}
\end{aligned}$$

方便起见，规定 $g(0)=m-1,f(0)=0$，那么就有：

$$f(m)=0$$

$$f(x)=(m-1)(m-x)\sum_{j=0}^{x-1}\frac{1}{m-j}$$

维护倒数和，递推至 $\max a_i$ 即可。

此时，$\phi(S_{end})=f(m)=0,\phi(S_{begin})=\sum f(a_i)$

如果写线性逆元的话，复杂度为 $\mathcal O(\max a+n)$

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int P = 1e9 + 7 ;  
const int N = 1e5 + 5 ; 
int fpow(int x, int k) {
	int ans = 1, base = x ;
	while(k) {
		if(k & 1) ans = 1ll * ans * base % P ;
		base = 1ll * base * base % P, k >>= 1 ;
	} return ans ;
}
int n, m, c, a[N], f[N], inv[N] ;  
signed main()
{
	n = gi() ; f[0] = 0 ; 
	rep( i, 1, n ) a[i] = gi(), c += a[i], m = max( m, a[i] ) ; 
	rep( i, 0, m ) inv[i] = fpow(c - i, P - 2) ; 
	rep( i, 1, m ) inv[i] = (inv[i - 1] + inv[i]) % P ; 
	rep( i, 1, m ) f[i] = (c - 1) * (c - i) % P * inv[i - 1] % P ; 
	int ans = 0 ;
	rep( i, 1, n ) ans = (ans + f[a[i]]) % P ; 
	cout << ans % P << endl ; 
	return 0 ;
}
```


---

## 作者：x7103 (赞：4)

## [蒟蒻的blog](https://blog.csdn.net/m0_46374167/article/details/116089985)
## 题目描述
给定 $n$ 种颜色的球，每种球有 $a_i$ 个，对这些球执行以下操作：
 - 有顺序地任意取两个球，将第二个球涂上第一个球的颜色，重复该操作至所有球颜色相同。

求期望操作次数，对 $10^9+7$ 取模。

**数据范围：**$n\le 2500$，$1\le a_i\le 10^5$。
## Solution
设 $f_i$ 表示当前有 $i$ 个球，将所有球变为该颜色的期望次数，$s$ 表示球的总数，$p$ 表示当前取出的两个球第一个与最终颜色相同，第二个与最终颜色不同的概率。

根据题意，有 
$$p=\frac{i\times(s-i)}{s\times(s-1)}$$
$$f_i=p\times f_{i-1}+p\times f_{i+1}+(1-2p)\times f_i+v$$
其中 $v$ 为这一步操作对最终答案的贡献，也就是该颜色成为最终颜色的概率。

设 $g_i$ 表示当前颜色成为最终颜色的概率，有 $g_0=0$，$g_1=1$，且 $g_{i}=p\times g_{i-1}+p\times g_{i+1}+(1-2p)\times g_i$。

转化可得 $g_i-g_{i-1}=g_{i+1}-g_{i}$，等差数列求和可得 $g_i=\frac{i}{s}$，即 $v=\frac{i}{s}$。

那么现在有
$$f_i=p\times f_{i-1}+p\times f_{i+1}+(1-2p)\times f_i+\frac{i}{s}$$

转化后有
$$f_{i}-f_{i+1}=f_{i-1}-f_{i}+\frac{s-1}{s-i}$$

考虑求 $f_1$ 和 $f_2$ 后线性递推，由于 $f_0$ 不存在，代入后有 $f_2=2f_1-1$

$$\begin{aligned}f_1&=f_1-f_s\\ &=\sum_{i=2}^{s}{f_{i-1}-f_{i}}\\ &=(s-1)\times(f_1-f_2)+\sum_{i=2}^{s-1}{\frac{s-1}{s-i}\times(s-i)}\\&=(s-1)\times(1-f_1)+(s-1)\times(s-2)\end{aligned}$$
所以 $f_1=\frac{(s-1)^2}{s}$。线性递推即可求解，答案为 $\sum_{i=1}^{n}{f_{a_{i}}}$。
## Code
```cpp
#include<cstdio>
using namespace std;
const int maxn=100010,MLY=1000000007;
int f[maxn],n,a[maxn],s,ans;
inline int power(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=1ll*ans*a%MLY;
		a=1ll*a*a%MLY;
		b>>=1;
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]),s+=a[i];
	f[1]=(s-1ll)*(s-1)%MLY*power(s,MLY-2)%MLY;
	f[2]=(2ll*f[1]-1+MLY)%MLY;
	for(int i=2;i<100000;++i)
		f[i+1]=((2ll*f[i]-f[i-1]-(s-1ll)*power(s-i,MLY-2))%MLY+MLY)%MLY;
	for(int i=1;i<=n;++i)ans=(ans+f[a[i]])%MLY;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Anoshag_Ruwan (赞：2)

就是来整理分享一下我做这题时的过程，相信很多大佬的第一感觉会是“有必要这么麻烦吗”，我也觉得跑得比较偏，不过这道个人评价还算不错的期望 dp，私以为这样殊途同归的思路还是值得记录的（qwq）。

先考虑一种暴力搞法：设 $m = \sum\limits_{i=1}^na_i$，令每个点对应一种将 $m$ 拆分成**任意个无标号**正整数的方案，对单次操作能转移到的所有方案连边（别忘了除 $\forall a_i = 1$ 外都要对自己连边）并计算出这种转移发生的概率，就转化成了一个经典的图上随机游走问题（比如[这道入门题](https://www.luogu.com.cn/problem/P6835)）。考虑指针指到 $i$ 后的第一步，设 $e_i$ 为第 $i$ 个点到终点期望步数，$nxt_i$为第 $i$ 个点的出边集合，则有 $e_i = \begin {cases} 0,&i=end\\ 1+\sum\limits_{v \in nxt_i} p_v e_{v.to},&i≠end \end {cases}$，比如这样（csacademy 显示不了自环，每个点的自环概率 $=1-$ 所有出边概率之和）：

![](https://cdn.luogu.com.cn/upload/image_hosting/aqgu5lsk.png)

然后问题是这玩意太暴力了，点数为 $m$ 的拆分数即 $P_m$ 个，这个经典数列的生成函数可用[五边形数定理](https://www.cnblogs.com/Eulring/articles/5101374.html)求得为 $\sum\limits_{i=-\infty}^{+\infty}(-1)^ix^{\frac{i(3i-1)}{2}}$，或者也可以把它当做 [P4389 付公主的背包](https://www.luogu.com.cn/problem/P4389) 的特殊情况来多项式 exp 处理，总之结果当 $m = 90$ 时就会超过 $5\times10^7$，而本题的 $m$ 可以达到 $10^9$ 量级，更吓人的是对于颜色数相等的点，内部连边复杂，需要 $O(n^3)$ 的高斯消元处理。。。emm。不过这时我们可以回过头来，注视一些的基本性质。

1.令 $E_i$ 表示如果某种颜色现有 $i$ 个，通过操作把所有其他小球“同化”掉（变成相同颜色）的期望步数，由随机变量的独立性得，无论其他小球是怎样的颜色分布，不会影响 $E_i$ 的数值（当然 $E_m=0$）。

2.设一种划分方案（图中一个点）的颜色集合为 $S_i$，由期望的对称性得，$e_i = \frac{1}{m} \sum\limits_{j \in S_i}E_j$，那么我们就把 $P_m$ 个未知量的方案期望步数转化为 $m$ 个未知量的颜色期望步数，只需要 $m$ 个转移方程，那就观察这条长为 $m$ 的链：

![](https://cdn.luogu.com.cn/upload/image_hosting/4gqto736.png)

对于主链上每个点，其期望都能表示为 $E_k+(m-k)E_1$，其中 $k \in (1,m]$.除起、终和第 $2$ 个、第 $m-1$ 个点外，每个点都能到达 $3$ 个点：（设操作的两种颜色依次为 $i$、$j$）。

1.$a_i=1\rightarrow 2,a_j=1\rightarrow 0$，概率为 $\frac{(m-k)(m-k-1)}{m(m-1)}$。

2.$a_i=1\rightarrow 2,a_j=k\rightarrow k-1$，概率为 $\frac{k(m-k)}{m(m-1)}$。

3.$a_i=k\rightarrow k+1,a_j=1\rightarrow 0$，概率同上。

4.自环（啥都没干），概率为 $\frac{k(k-1)}{m(m-1)}$。

然后一顿回代猛如虎，得到 $E_1=(m-1)^2$，(我不会告诉你我是通过最开始的暴力知道的），再由图上最下面的边，得出 $\frac{1}{m} (E_2 + (m-2)E_1) = E_1 - 1$，即 $E_2 = 2(m-1)^2-m$。有了 $E_1$ 和 $E_2$ 这转移方程中最重要的两个量，就能利用随机游走的转移方程，对任意 $E_k$ 求递推式了。

$(1-\frac{k(k-1)}{m(m-1)})(E_k+(n-k)E_1)=\frac{k(n-k)}{m(m-1)}(2(m-k-1)E_1+E_2+E_{k-1}+E_{k+1})+\frac{(m-k)(m-k-1)}{m(m-1)}(E_{k-1}+E_2+(m-k-1)E_1)$

~~2000 years later~~
 
 我们得到了递推式：$E_{k+1}=2E_k-E_{k-1}-\frac{m(m-1)}{m-i}$！我们令 $E_0=0$ 后，发现它对 $k=2$、$m-1$、$m$ 也是成立的。然后 $a_i$ 的范围只有 $10^5$,这意味着我们不需要推到 $m$，只需要推到 $\max(a_i)$ 即可，复杂度为 $O(\max(a_i) \log p)$(别忘了快速幂逆元产生的 $\log$)，而且它的代码量不到 1KB！
 
 ```cpp
#include<cstdio>
#include<cstring>
using namespace std;
long long a[2511],e[100011],p=1e9+7;
inline long long add(long long x,long long y){return x+y>=p?x+y-p:x+y;}
inline long long maxx(long long x,long long y){return x>y?x:y;}
inline long long rd(){
	long long i=0;char g=getchar();
	while(g>57||g<48)g=getchar();
	while(g>47&&g<58)i=(i<<3)+(i<<1)+g-48,g=getchar();
	return i;
}
inline long long ksm(long long x,long long y){
	long long k=1,l=x;while(x<=1||y==1)return x;
	while(y){if(y&1)k=k*1ll*l%p;l=l*1ll*l%p,y>>=1;}
	return k;
}
int main()
{
	long long i,h,m=0,s=0,n,k=0;scanf("%lld",&n);
	for(i=1;i<=n;i++)
		a[i]=rd(),m=maxx(m,a[i]),s=add(s,a[i]);
	e[1]=(s-1)*(s-1)%p;
	for(i=2;i<=m;i++)
		e[i]=add(add(e[i-1],e[i-1]),p-add(e[i-2],s*(s-1)%p*ksm(s-i+1,p-2)%p));
	for(i=1;i<=n;i++)k=add(k,e[a[i]]);
	printf("%lld\n",k*ksm(s,p-2)%p);
	return 0;
} 
```


---

## 作者：gxy001 (赞：2)

[鞅与停时定理学习笔记](https://www.luogu.com.cn/blog/gxy001/yang-yu-ting-shi-ding-li-xue-xi-bi-ji)

$m$ 表示球总数。

设 $a_{n,i}$ 为 $n$ 次操作后，第 $i$ 个颜色球的个数。

设 $f(x)$ 为有 $x$ 个球的颜色的势能函数，整个局面的势能函数为 $\Phi(A)=\sum f(a_{i})$。

注意到 $E(\Phi(A_{n+1})\mid A_0,A_1,\cdots,A_n)=E(\Phi(A_{n+1})\mid A_n)$，就等于


$$
\sum\limits_i\frac{a_{n,i}(a_{n,i}-1)}{m(m-1)}\sum\limits_{k}f(a_{n,k})+\sum\limits_i\sum\limits_{j\ne i}\frac{a_{n,i}a_{n,j}}{m(m-1)}\left(f(a_{n,i}+1)+f(a_{n,j}-1)+\sum\limits_{k\ne i,k\ne j}f(a_{n,k})\right)
$$


为满足 $E(\Phi(A_{n+1})-\Phi(A_n)\mid A_0,A_1,\cdots,A_n)=-1$，有


$$
\sum\limits_{k}f(a_{n,k})-1=\sum\limits_i\frac{a_{n,i}(a_{n,i}-1)}{m(m-1)}\sum\limits_{k}f(a_{n,k})+\sum\limits_i\sum\limits_{j\ne i}\frac{a_{n,i}a_{n,j}}{m(m-1)}\left(f(a_{n,i}+1)+f(a_{n,j}-1)+\sum\limits_{k\ne i,k\ne j}f(a_{n,k})\right)\\
\sum\limits_{k}f(a_{n,k})-1=\sum\limits_i\frac{a_{n,i}(a_{n,i}-1)}{m(m-1)}\sum\limits_{k}f(a_{n,k})+\sum\limits_i\sum\limits_{j\ne i}\frac{a_{n,i}a_{n,j}}{m(m-1)}\left(f(a_{n,i}+1)+f(a_{n,j}-1)+\sum\limits_{k\ne i,k\ne j}f(a_{n,k})\right)\\
\sum\limits_{k}f(a_{n,k})-1=\sum\limits_i\left(\frac{a_{n,i}(m-a_{n,i})}{m(m-1)}f(a_{n,i}+1)+\frac{a_{n,i}(m-a_{n,i})}{m(m-1)}f(a_{n,i}-1)+(1-\frac{2a_{n,i}(m-a_{n,i})}{m(m-1)})f(a_{n,i})\right)\\
f(x)-\frac{x}{m}=\frac{x(m-x)}{m(m-1)}f(x+1)+\frac{x(m-x)}{m(m-1)}f(x-1)+\frac{2x^2-2mx-m+m^2}{m(m-1)}f(x)\\
f(x+1)=2f(x)-f(x-1)-\frac{m-1}{m-x}
$$


这东西不太好处理，差分一下 $g(x)=f(x)-f(x-1)$。


$$
f(x+1)-2f(x)+f(x-1)=-\frac{m-1}{m-x}\\
g(x+1)-g(x)=-\frac{m-1}{m-x}\\
g(x+1)=g(x)-\frac{m-1}{m-x}\\
g(x)=g(0)-\sum\limits_{i=0}^{x-1}\frac{m-1}{m-i}\\
f(x)=f(0)+\sum\limits_{i=1}^xg(i)\\
f(x)=f(0)+\sum\limits_{i=1}^x(g(0)-\sum\limits_{j=0}^{i-1}\frac{m-1}{m-j})\\
f(x)=f(0)+xg(0)-\sum\limits_{i=1}^x\sum\limits_{j=0}^{i-1}\frac{m-1}{m-j}\\
f(x)=f(0)+xg(0)-\sum\limits_{j=0}^{x-1}(x-j)\frac{m-1}{m-j}\\
f(x)=f(0)+xg(0)-(m-1)\sum\limits_{j=0}^{x-1}(\frac{x-m}{m-j}-1)\\
f(x)=f(0)+xg(0)+(m-1)(m-x)\sum\limits_{j=0}^{x-1}\frac{1}{m-j}-x(m-1)\\
$$


取 $f(0)=0,g(0)=m-1$，则 $f(x)=(m-1)(m-x)\sum\limits_{i=0}^{x-1}\frac{1}{m-i}$。

设停时为 $t$，则 $\Phi(A_t)=f(m)+(n-1)f(0)=0$，为常数，所以 $E(t)=\Phi(A_0)-\Phi(A_t)$。

```cpp
#include<cstdio>
int const mod=1e9+7;
int n,a[2510],f[100010],m,ans;
int pow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=1ll*res*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",a+i),m+=a[i];
	f[0]=0;
	for(int i=1;i<=100000;i++)
		f[i]=(f[i-1]+pow(m-i+1,mod-2))%mod;
	for(int i=1;i<=100000;i++)
		f[i]=1ll*(m-1)*(m-i)%mod*f[i]%mod;
	for(int i=1;i<=n;i++)ans=(ans+f[a[i]])%mod;
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Leasier (赞：1)

赛时无人得分的模拟赛 T2。恐怖如斯。

------------

注意到若最终留下来的是第 $i$ 种颜色的球，则我们其实并不太关心其他球间发生了什么。

设 $sum = \displaystyle\sum_{i = 1}^n a_i$，则此时问题转化为了 $n' = 2, a' = [a_i, sum - a_i]$。于是我们只需要知道 $n = 2$ 怎么做。

考虑怎样表出一个状态：不难发现我们只需知道现在有几个目标颜色的球即可。

设 $f_x$ 表示现在有 $x$ 个目标颜色的球时，期望还有多少步才能将所有球涂成目标颜色。**需要注意的是这里我们将最终没有涂成目标颜色视作 $0$ 步。**

边界：$f_0 = f_{sum} = 0$。

递推式：

- 设现在在考虑 $f_x$，$p = \dfrac{x(sum - x)}{sum(sum - 1)}$。
- 则 $f_x = p([x > 1] f_{x - 1} + f_{x + 1}) + (1 - 2p) f_x + \ ?$，这里 $?$ 是从当前状态开始最终走到 $f_{sum}$ 的**概率**。
- 根据 [P5155 [USACO18DEC] Balance Beam P](https://www.luogu.com.cn/problem/P5155) 的经典结论，这个概率为 $\frac{x}{sum}$。

于是我们有了一个 $O((\sum a_i)^3)$ 的暴力高斯消元做法，但显然不能通过。

- **对于只与邻项相关且有边界的递推式，我们可以考虑主元法。**

考虑把上面那坨移个项，可得：

- $2pf_x = p([x > 1] f_{x - 1} + f_{x + 1}) + \frac{x}{sum}$。

注意到两边都有 $p$，除掉可得：

- $2f_x = [x > 1] f_{x - 1} + f_{x + 1} + \frac{sum - 1}{sum - x}$。

**我们尝试在未知的 $f_1$ 和已知的 $f_{sum}$ 之间建立联系。**

首先特判 $f_2 = 2 f_1 - 1$。

对于 $x > 1$，我们尝试移项以构造出**长得比较像的形式**，可以发现 $f_x - f_{x + 1} = f_{x - 1} - f_x + \frac{sum - 1}{sum - x}$。

考虑用上面的差分之和将 $f_1, f_{sum}$ 联系在一起，可得 $f_1 = f_1 - f_{sum} = (f_2 - f_1)(sum - 1) + \displaystyle\sum_{i = 2}^{sum - 1} \frac{sum - 1}{sum - i} \times (sum - i) = (sum - 1)(sum - f_1 - 1)$。

解方程可得 $f_1 = \frac{(sum - 1)^2}{sum}$。

于是不难递推出 $x \in [2, \displaystyle\max_{i = 1}^n a_i]$ 的 $f_x$，答案为 $\displaystyle\sum_{i = 1}^n f_{a_i}$。

时间复杂度视实现可能为 $O(n + \displaystyle\max_{i = 1}^n a_i)$ 或 $O(n + \displaystyle\max_{i = 1}^n a_i \log mod)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int mod = 1e9 + 7;
int a[2507];
ll f[100007];

inline int max(int a, int b){
	return a > b ? a : b;
}

inline ll sqr(int n){
	return (ll)n * n % mod;
}

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

int main(){
	int n, max_val = 0, sum = 0;
	ll ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		max_val = max(max_val, a[i]);
		sum += a[i];
	}
	f[1] = sqr(sum - 1) * quick_pow(sum, mod - 2, mod) % mod;
	f[2] = ((f[1] * 2 % mod - 1) % mod + mod) % mod;
	for (int i = 3; i <= max_val; i++){
		f[i] = ((f[i - 1] * 2 % mod - f[i - 2] - (sum - 1) * quick_pow(sum - i + 1, mod - 2, mod) % mod) % mod + mod) % mod;
	}
	for (int i = 1; i <= n; i++){
		ans = (ans + f[a[i]]) % mod;
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Laoshan_PLUS (赞：0)

这道题本质上和 [P5516](https://www.luogu.com.cn/problem/P5516) 是一样的。P5516 看似复杂，实际上由于题末不起眼的一条：
$$
\sum_{a=1}^n\sum_{b=1}^np_{a,b}=n^2
$$

于是便和此题一样了。实在佩服出题人。

---

### 题意

题意非常简单：给定 $n$ 个不同颜色的球，第 $i$ 种颜色的小球有 $a_i$ 个。每次随机选择两个小球，将后者颜色改为前者的颜色，求最终将所有小球变为相同颜色的期望次数。

### 骗分

有一个期望题屡试不爽的骗分方法~~但此题不适用~~，即模拟题意，输出多次随机数据下次数的平均值，这个值最后是一定收敛到我们要求的期望值的，应对最终要求输出粗略小数的期望题非常有用。在 P5516 中最终可以骗到 40pts，还是非常可观的。

### 正解

参考 @[wzw0611](https://www.luogu.com.cn/user/479167) 大佬提供的[这篇题解](https://gxyzoj.com/d/hzoj/p/3692/solution/6649dd43e9f28a76335d7c25)。

对于这种样本空间无限的期望题，我们**考虑从期望的本质入手**：
$$
E(i)=p_ix_i
$$

其中 $p_i$ 表示有 $i$ 个颜色为 $i$ 的元素时这个颜色成为最终所有球的颜色的概率，$x_i$ 表示有 $i$ 个颜色为 $i$ 的元素时 $i$ 这个颜色成为最终所有球颜色的期望步数。由于最终有可能成为任何一种颜色，所以答案即为 $\sum_{i=1}^n p_ix_i$。

先推 $p_i$，**牢记概率 DP 正推**。假设颜色 A 有 $i$ 个，那么接下来一次操作的 $n(n-1)$ 种情况中，有 $2i(n-i)$ 种可能会影响到颜色 A 的数量 $+1$ 或 $-1$，$+1$ 的情况转移到 $p_{i-1}$，$-1$ 的情况转移到 $p_{i+1}$，二者概率是等价的。

由此得出 $p_i$ 的式子，记 $k=\dfrac{2i(n-i)}{n(n-1)}$：
$$
p_i=kp_{i-1}+kp_{i+1}+(1-2k)p_i
$$

化简：
$$
p_i=\frac 12\left(p_{i-1}+p_{i+1}\right)\tag{1}
$$

这个 $(1)$ 式非常特别，我们可以由它推得 $p$ 是个等差数列。我们又易得 $p_0=0,p_n=1\implies p_i=\dfrac in$。这个性质留着，等会儿用。

然后推 $x_i$。改变颜色 A 的概率是 $k$，所以实现一次改动要改 $k$ 的倒数次，**转移概率由实现转移的概率作比得到**。
$$
x_i=\frac{p_{i-1}}{2p_i}x_{i-1}+\frac{p_{i+1}}{2p_i}x_{i+1}+\frac 1k\tag{2}
$$

这妥妥的高斯消元式子。此时有两种路，要么用优化的 $O(n)$ 高斯消元，要么按照本题解接下来的做法。

**我们要求的答案是 $\boldsymbol{\sum_{i\in\textbf{\textit{cnt}}}p_ix_i}$，$\textbf{\textit{cnt}}$ 是每种颜色球的数量。接下来我们就照着这个目标往下推。**

因为最终求的是 $p_ix_i$ 也就是二者乘积，所以考虑不单独求出 $x_i$，而是合起来看。

由 $(2)$ 式可得：
$$
p_ix_i=\frac12\left(p_{i-1}x_{i-1}+p_{i+1}x_{i+1}\right)+\frac{p_i}k
$$

因为我们最终求的也是二者乘积，所以我们令 $f_i=p_ix_i$，将式子转化为：
$$
f_i=\frac12\left(f_{i-1}+f_{i+1}\right)+\frac{p_i}k
$$

前面我们得出 $p_i=\dfrac in$，又因为 $k=\dfrac{2i(n-i)}{n(n-1)}$，代入得：
$$
f_i=\frac12\left(f_{i-1}+f_{i+1}\right)+\frac{n-1}{2(n-i)}
$$

和 $(1)$ 式很像，我们把它化成递推式：
$$
f_{i}=2f_{i-1}-f_{i-2}-\frac{n-1}{n-i+1}\tag{3}
$$

好的，现在我们有了递推式。想要推出整个数组，我们还需要首项，也就是 $f_1$。

令 $g_i=\left(f_i-f_{i-1}\right)-\left(f_{i+1}-f_i\right)$，$d_i=f_{i+1}-f_i$。由 $(3)$ 式推得，$g_i=\dfrac{n-1}{n-i}$，留着备用。下面开始暴力推。
$$
\begin{aligned}
f_i&=f_{i-1}+d_{i-1} \\
&=f_{i-2}+d_{i-2}+d_{i-1} \\
&\phantom=\vdots \\
&=f_0+d_0+d_1+\cdots+d_{i-1} \\
&=d_0+\left(d_0-g_1\right)+\left(d_0-g_1-g_2\right)+\cdots+\left(d_0-\sum_{j=1}^{i-1}g_j\right) \\
&=id_0-(i-1)g_1-\cdots-2g_{i-2}-g_{i-1} \\
&=if_1-(i-1)\frac{n-1}{n-1}-\cdots-2\times\frac{n-1}{n-i+2}-\frac{n-1}{n-i+1} \\
&=if_1-(n-1)\left(\frac{i-1}{n-1}+\frac{i-2}{n-2}+\cdots+\frac{1}{n-i+1}\right) \\
&=if_1-(n-1)\left(\sum_{j=1}^{i-1}\frac{i-j}{n-j}\right) \\
f_n&=nf_1-(n-1)(n-1)=0 \\
f_1&=\frac{(n-1)^2}{n}
\end{aligned}
$$

请不要只是看，一定要自己推一遍，并且是在自己脑子好使的时候。里面各种细节非常多，一不小心就会推错。

> 又是这种硬核推导。为了保持推导过程『一气呵成』的感觉，我没有在里面加入注释。下面简单说说推导过程中注意的一些点。
>
> 1. $d_i=d_{i-1}-g_i$，**看清楚各种 +1-1，不要搞混**。
> 2. **别忘了我们有边界条件：$f_0=f_n=0$**。在将 $f_i$ 推到极致时，令 $i=n$，就可以利用这个条件，接着往下推。

最终我们得出了我们要求的 $f_1$ 的值：
$$
f_1=\frac{(n-1)^2}n\tag{4}
$$

结合 $(3)(4)$ 两式，我们就能推出整个 $f$ 数组的值，最后即可求得答案。时间复杂度 $O(n)$。

### 实现

代码非常简短。

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 10005;
string s;
int n, cnt[26];
double f[MAXN], ans;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> s;
    n = s.size();
    for (auto x : s) cnt[x - 'A']++;
    f[1] = (double)(n - 1) * (n - 1) / n;
    for (int i = 2; i <= n; i++) f[i] = 2 * f[i - 1] - f[i - 2] - (double)(n - 1) / (n - i + 1);
    for (int i = 0; i < 26; i++) ans += f[cnt[i]];
    cout << fixed << setprecision(1) << ans << '\n';

    return 0;
}
```

### 后记

整个思路下来，有没有一气呵成的感觉？真的佩服考场上切掉此题的大佬们。

这道题的难度绝对在紫题及以上。如果按这个做法，那就是思维题。否则你需要会 $O(n)$ 高斯消元。

再顺一遍思路：

1. 样本空间无限，从期望的本质入手，分别推 $p_i$ 和 $x_i$。
2. 分别推出 $p_i$ 和 $x_i$ 的式子（**难点**），然后有两条路：要么高斯消元，要么继续推。
3. 推出 $f_i$ 的递推式和 $f_1$ 的值。（**重点**）
4. 递推出整个 $f$ 数组，求解出答案。

总的来说，这题是道综合题，考验读题、概率期望、推式子、高斯消元的综合运用。*难得用文化课的口吻来形容一道竞赛题，足见此题的价值。*

---

## 作者：Mashu77 (赞：0)

分别考虑每种颜色。那么设 
$f_
i$
 表示当前颜色的球有 
$i$
 个，到没有其他颜色的球时的期望秒数。
 
 设 $s=\sum\limits_{i=1}^n a_i$，则 $f_0=+\infty,f_s=0,\forall i \in (0,s),f_i=(f_{i-1}+f_{i+1})p_i+f_i(1-2p_i)+1$。其中 $p_i$ 为 $\frac{i(s-i)}{s(s-1)}$。
 
但因为有无穷，这是无法求的。我们需要避开 
$0$。因为一旦进入 
$0$
 就出不来，所以所有从 
$i$
 到 
$s$
 的合法路径都是不经过 
$0$
 的。那么我们设 
$g_
i$
 表示从 
$i$
 到 
$s$
 不经过 
$0$
 的概率，易得为 
$\frac{i}{
s}$。结合其实际意义，我们可以修改上式：$f_0=f_s=0$，$\forall i\in(0,s),f_i=(f_{i-1}+f_{i+1})p_i+f_i(1-2p_i)+\frac{i}{s}$。注意，此时 
$f_
0$
 没有实际意义，赋 
$0$
 仅为了运算方便。

此时若用高斯消元，复杂度为 $
O
(
n
^3
V
^3
)$，无法接受。将其化为更简单的形式：$f_{i+1}-f_i=f_i-f_{i-1}-\frac{s-1}{s-i}$。因为 $
f_0=
0$，我们只需求出 
$f_
1$
 即可。再结合 
$f_s=
0$，有 $f_1+\sum\limits_{i=1}^{s-1}f_{i+1}-f_i=sf_1-\sum\limits_{i=1}^{s-1}\frac{s-1}{s-i}s-i=sf_1-(s-1)^2=0$。则 
$f_1=\frac{(s-1)^2}{s}$。递推即可。复杂度 
$O
(
V\log
P
)$，瓶颈在求逆元。

此题关键在由 
$g$
 得出 
$f$
 的方程。非常巧妙地结合其实际意义。

---

## 作者：Zi_Gao (赞：0)

## 题意

有一袋 $n$ 个颜色球，第 $i$ 个颜色的球有 $a_i$ 个。

当袋子里至少有两个不同颜色的球时，执行以下步骤：

1. 一个接一个的按照顺序随机取出两个的球，这些球的颜色可能是一样的。
2. 把第二个球涂成第一个球的颜色，然后把两个球放回袋子里。

求期望操作次数。

$n\le 2500,1\le a_i \le 10^5$

## 题解

考虑计算最后颜色全是 $x$ 的情况，设 $f_i$ 表示已经有 $i$ 个 $x$ 颜色，把这所有都变成 $x$ 还需要的期望次数。先计算一下选出两个求，一个是 $x$，另一个不是的概率设为 $p$，并且记 $s$ 表示球总数：

$$
p=\frac{i(s-i)}{s(s-1)}
$$

然后列出转移方程，先考虑边界，$f_s=0$，$f_0$ 不存在，因为永远走不到。按照正常的套路是：

$$
f_i=pf_{i-1}+pf_{i+1}+(1-2p)f_i+1
$$

即表示走出去这一步，但是发现这样干会错，应为走出去这一步不一定就能走到 $f_n$ 了，可能直接走到 $f_0$，所以这一步不是所有情况都能贡献到。假设贡献为 $v$，可以知道 $v$ 就是能走到 $f_n$ 的概率。dp 计算一下，设 $g_i$ 表示有 $i$ 个为 $x$ 的球，到最后的概率所有球都变成 $x$ 的概率：

$$
\begin{align}
&g_0=0,g_s=1\\
&g_i=pg_{i-1}+pg_{i+1}+(1-2p)g_i\\
&g_{i+1}-g_{i}=g_i-g_{i-1}
\end{align}
$$

所以 $g$ 是等差数列，并且知道首项和尾项，可以解出：

$$
v=g_i=\frac{i}{s}
$$

带入列一下转移方程：

$$
\begin{align}
&f_i=pf_{i-1}+pf_{i+1}+(1-2p)f_i+\frac{i}{s}\\
&f_{i}-f_{i+1}=f_{i-1}-f_i+\frac{s-1}{s-i}\\
&f_{i+1}=2f_i-f_{i-1}-\frac{s-1}{s-i}
\end{align}
$$

由于没有 $f_0$，可得 $f_2=2f_1-1$，现在需要把 $f_1$ 解出来。根据 $f_{i}-f_{i+1}=f_{i-1}-f_i+\frac{s-1}{s-i}$ 可以把 $f_1$ 和 $f_s$ 用差分的方式列出来：

$$
f_1-0=f_1-f_s=\sum_{i=2}^s f_i-f_{i-1}
$$

考虑差分数列上相邻两项的差的贡献：

$$
\begin{align}
&\sum_{i=2}^s f_i-f_{i-1}\\
=&(s-1)(f_1-f_2)+\sum_{i=2}^{s-1} \frac{s-1}{s-i}(s-i)\\
=&(s-1)(f_1-f_2)+(s-2)(s-1)
\end{align}
$$

把 $f_2=2f_1-1$ 带入得 $f_1=\frac{(s-1)^2}{s}$。答案就是 $\sum_{i=1}^n f_{a_i}$

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
inline __attribute((always_inline)) INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

#define MODINT_TYPE long long
#define barK (64)

namespace MODINT{
	unsigned long long d;
    __uint128_t m;
    inline __attribute((always_inline)) void init(const long long &mod){
        m=(((__uint128_t)1)<<barK)/(d=mod);
        return;
    }

    inline __attribute((always_inline)) unsigned long long mod(const unsigned long long &x){
        register unsigned long long w=(m*x)>>barK;
        w=x-w*d;
        return w>=d?w-d:w;
    }

    MODINT_TYPE exgcd(MODINT_TYPE a,const MODINT_TYPE b,MODINT_TYPE &x,MODINT_TYPE &y){
        if(!b){
            x=1;
            y=0;
            return a;
        }
        MODINT_TYPE d=exgcd(b,a%b,y,x);
        y-=a/b*x;
        return d;
    }

    inline __attribute((always_inline)) MODINT_TYPE inv(const MODINT_TYPE &n,const MODINT_TYPE &p){
        MODINT_TYPE x,y;
        exgcd(n,p,x,y);
        x%=p;
        return x>=0?x:x+p;
    }

    struct MODNUM{
        MODINT_TYPE val;
        inline __attribute((always_inline)) MODNUM(const MODINT_TYPE &x){
            if(x<0){
                val=d-mod(-x);
                if(val>=d) val-=d;
            }else val=mod(x);
            return;
        }
        inline __attribute((always_inline)) MODNUM(){val=0;}
        inline __attribute((always_inline)) MODNUM operator + (const MODNUM& o) const{return (MODNUM){(val+o.val>=d)?(val+o.val-d):(val+o.val)};}
        inline __attribute((always_inline)) MODNUM operator + (const MODINT_TYPE& o) const{return *this+MODNUM(o);}
        friend inline __attribute((always_inline)) MODNUM operator + (const MODINT_TYPE &o,const MODNUM&a){return a+o;}
        inline __attribute((always_inline)) MODNUM operator - (const MODNUM& o) const{return (MODNUM){(val-o.val<0)?(val-o.val+d):(val-o.val)};}
        inline __attribute((always_inline)) MODNUM operator - (const MODINT_TYPE& o) const{return *this-MODNUM(o);}
        friend inline __attribute((always_inline)) MODNUM operator - (const MODINT_TYPE &o,const MODNUM&a){return MODNUM(o)-a;}
        inline __attribute((always_inline)) MODNUM operator * (const MODNUM& o) const{return (MODNUM){mod(val*o.val)};}
        inline __attribute((always_inline)) MODNUM operator * (const MODINT_TYPE& o) const{return *this*MODNUM(o);}
        friend inline __attribute((always_inline)) MODNUM operator * (const MODINT_TYPE &o,const MODNUM&a){return a*o;}
        inline __attribute((always_inline)) MODNUM operator / (const MODNUM& o) const{return (MODNUM){mod(val*inv(o.val,d))};}
        inline __attribute((always_inline)) MODNUM operator / (const MODINT_TYPE& o) const{return *this/MODNUM(o);}
        friend inline __attribute((always_inline)) MODNUM operator / (const MODINT_TYPE &o,const MODNUM&a){return MODNUM(o)/a;}

        inline __attribute((always_inline)) MODNUM operator ++(){
            ++val;
            if(val>=d) val-=d;
            return *this;
        }
        inline __attribute((always_inline)) MODNUM operator ++(const int){
            MODNUM tmp=*this;
            ++val;
            if(val>=d) val-=d;
            return tmp;
        }
        inline __attribute((always_inline)) MODNUM operator --(){
            --val;
            if(val<0) val+=d;
            return *this;
        }
        inline __attribute((always_inline)) MODNUM operator --(const int){
            MODNUM tmp=*this;
            --val;
            if(val<0) val+=d;
            return tmp;
        }

        inline __attribute((always_inline)) MODNUM& operator += (const MODNUM& o) {return *this=*this+o;}
        inline __attribute((always_inline)) MODNUM& operator += (const MODINT_TYPE& o) {return *this=*this+o;}
        inline __attribute((always_inline)) MODNUM& operator -= (const MODNUM& o) {return *this=*this-o;}
        inline __attribute((always_inline)) MODNUM& operator -= (const MODINT_TYPE& o) {return *this=*this-o;}
        inline __attribute((always_inline)) MODNUM& operator *= (const MODNUM& o) {return *this=*this*o;}
        inline __attribute((always_inline)) MODNUM& operator *= (const MODINT_TYPE& o) {return *this=*this*o;}
        inline __attribute((always_inline)) MODNUM& operator /= (const MODNUM& o) {return *this=*this/o;}
        inline __attribute((always_inline)) MODNUM& operator /= (const MODINT_TYPE& o) {return *this=*this/o;}

        inline __attribute((always_inline)) operator MODINT_TYPE(){return val;}
    };
}

#define mint MODINT::MODNUM

int arr[2510];
mint dp[100010];

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

	MODINT::init(1000'000'007);

	register int i,max=0,sum=0;
	register mint res=0;
	int n=read();

	for(i=0;i<n;++i) sum+=(arr[i]=read()),max=std::max(max,arr[i]);
	dp[1]=mint(sum-1)*(sum-1)/sum;
	dp[2]=dp[1]*2-1;

	for(i=2;i<max;++i)
		dp[i+1]=dp[i]*2-dp[i-1]-mint(sum-1)/(sum-i);

	for(i=0;i<n;++i) res+=dp[arr[i]];

	print(res);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

---

## 作者：Eznibuil (赞：0)

模拟赛狂砍 3.5h 获得高贵的零分。~~绝对是因为有人在玩巴西原神导致的。~~

---
首先考虑拆开贡献，分别算每种颜色留到最后的期望，然后乘上概率求和。

令 $s=\sum a_i$，手模后发现对于第 $i$ 种颜色留到最后的概率为 $\frac{a_i}s$。

现在只有两种颜色了：$i$ 和非 $i$。考虑 DP。

令 $dp_i$ 表示从 $i$ 个变为 $s$ 个的期望步数。有 $dp_i=\frac12(dp_{i-1}+dp_{i+1})+\frac{s(s-1)}{2i(s-i)}$

然后发现 $0$ 处存在严重的问题，**无法直接算期望**，因为 $0$ 是要被排除的。

于是模拟赛卡这里卡了 3h29min（大雾）。

不要紧，之前提到过 $i$ 个最后变成 $0$ 个的概率是 $1-\frac is$，变成 $s$ 个的概率是 $\frac is$，所以进行一个简单修改，令 $dp_i$ 表示变为 $s$ 个或者 $0$ 个的期望步数，但是变成 $0$ 时的贡献为 $0$，这样答案就是 $\sum dp_{a_i}$ 了：
$$dp_i=\frac12(dp_{i-1}+dp_{i+1})+\frac{s-1}{2(s-i)}$$

令 $dp_0=dp_s=0$，手模可以得到 $dp_1=\frac{(s-1)^2}s$，递推即可。

时间复杂度 $O(\max a\log\textit{mod}+n)$，对数来源于快速幂求逆。
```cpp
#include<iostream>
const int mod=1e9+7;
int a[10001],dp[1000001];
int Inv(int a)
{
	int s=1;
	for(int b=mod-2;b;a=1ll*a*a%mod,b>>=1)
		if(b&1)
			s=1ll*s*a%mod;
	return s;
}
int main()
{
	int n,m=0,s=0;
	std::cin>>n;
	for(int i=0;i<n;i++)
		std::cin>>a[i],m<a[i]?m=a[i]:0,s+=a[i];
	dp[1]=(s-1ll)*(s-1ll)%mod*Inv(s)%mod;
	for(int i=1;i<m;i++)
		dp[i+1]=((dp[i]<<1)-dp[i-1]-(s-1ll)*Inv(s-i)%mod+(mod<<1))%mod;
	int ans=0;
	for(int i=0;i<n;i++)
		ans=(ans+dp[a[i]])%mod;
	std::cout<<ans;
	return 0;
}
```

---

## 作者：Add_Catalyst (赞：0)

# [CF850F] Rainbow Balls 题解

---

## 题意分析

> 在一个袋子中，有 $n$ 种颜色的球，每种颜色分别有 $a_i$ 种。
>
> 接下来，每次操作中取两个不一样的球（颜色可以相同），将其中一个涂成另一个的颜色。
>
> 问：使所有球都变成一种颜色的操作次数的期望值为多少？
>
> 以有理数 $\frac{P}{Q}$ 模 $M = 10^9 + 7$ 的形式输出（其中 $\gcd{(P,Q)} = 1$），也就是 $P \cdot Q^{-1} \pmod{M}$。

这明显是一道期望 DP。

---

## 思路分析

### 状态定义

那我们该如何求解这一道期望 DP 呢？

从数据范围入手，$1 \le n \le 2.5\times 10^3$，而 $1 \le a_i \le 10^5,\forall i \in [1,n]$，那么我们可以联想到：

这应该是一道与 $a_i$ 的数据范围有关的题目，需要 $O(n\log{M})$ 或优于 $O(n\log{M})$ 的做法，那么 DP 应该是线性的，对于 DP 数组，也应是形如 $\{ f_i \}$ 的一维数组。

那么我们可以通过期望的离散型定义来看：

> 设离散型随机变量 $X$ 的分布律为 $P_{ X = x_k } = p_k,k \in N^* $，若级数 $\sum_{k=1}^{\infty} |x_k| \cdot p_k < +\infty$，记 $E_X = \sum_{k=1}^{\infty} x_k \cdot p_k$。则称 $E_X$ 为随机变量 $X$ 的数学期望。

其中，$E_X = \sum_{k=1}^{\infty} x_k \cdot p_k$，我们从这里切入。

我们可以把它分解成对于每个颜色的子问题，再把它加起来，那么状态可以为：

 $E_i$ 表示总共有 $i$ 个相同颜色的小球，把所有球都变成该颜色的期望次数；

 $P_i$ 表示总共有 $i$ 个相同颜色的小球，把所有球都变成该颜色的概率。

所以式子应改为 $E = \sum_{i=1}^{n} E_{a_i} \cdot P_{a_i}$。

### 求解公式

#### 对于 $\{ P_i \}$

初始状态为 $P_0 = 0 , P_{sum} = 1$（其中 $sum=\sum_{i=1}^{n}a_i$，下同）。

假设现在有 $x$ 个某颜色的球，那么总共选择方案有 $(sum-1)sum$ 种，变为 $x-1$ 个的方案有 $x(sum-x)$ 种，变为 $x+1$ 个的方案也是有 $x(sum-x)$ 种，因此从 $x$ 变为 $x-1$ 个与变为 $x+1$ 个的概率相同，故得到式子：
$$
\begin{aligned}
P_x & = \frac{P_{x+1}+P_{x-1}}{2}\\
P_{x+1} - P_x & =  P_x - P_{x-1}\\
\end{aligned}
$$
因此 $\{ P_i \}$ 是一个等差数列，通项公式为 $P_i = \frac{i}{sum}$。

#### 对于 $\{ E_i \}$

仍设现在有 $x$ 个某颜色的球，那么总共选择方案有 $(sum-1)sum$ 种，变为 $x-1$ 个的方案有 $x(sum-x)$ 种，变为 $x+1$ 个的方案也是有 $x(sum-x)$ 种，那么操作后 $x$ 会变化的概率是 $p = \frac{2x(sum-x)}{sum(sum-1)}$，因此操作后 $x$ 会变化的期望步数是 $\frac{1}{p} = \frac{sum(sum-1)}{2x(sum-x)}$（概率学知识，我不太懂）。

那么得到式子：
$$
\begin{aligned}
E_i & = \frac{P_{i-1}E_{i-1} + P_{i+1}E_{i+1}}{P_{i-1}+P_{i+1}} + \frac{sum(sum-1)}{2i(sum-i)} \\
E_i & = \frac{(i-1)E_{i-1} + (i+1)E_{i+1}}{2i} + \frac{sum(sum-1)}{2i(sum-i)} \\
\end{aligned}
$$

### 状态化简

我们求出 $\{ P_i \}$ 与 $\{ E_i \}$ 后，发现似乎不是很好求解，那么我们回到原式子：$E = \sum_{i=1}^{n} E_{a_i} \cdot P_{a_i}$。

经过我们的结果，此时式子可以化为：$E = \sum_{i=1}^{n} \frac{a_iE_{a_i}}{sum}$。

那么我们直接定义 $f_i = \frac{iE_{i}}{sum}$，进行转移。

它的初始状态也很容易得到：$f_0 = 0,f_{sum} = 0$（虽然 $f_0$ 无意义，但有几率会变为这个状态，同时也为了方便，在此设为 $0$）。

我们继续推导：
$$
\begin{aligned}
E_i & = \frac{(i-1)E_{i-1} + (i+1)E_{i+1}}{2i} + \frac{sum(sum-1)}{2i(sum-i)} \\
\frac{sumf_i}{i} & = \frac{sumf_{i-1} + sumf_{i+1}}{2i} + \frac{sum(sum-1)}{2i(sum-i)} \\
2f_i & = f_{i-1} + f_{i+1} + \frac{sum-1}{sum-i} \\
f_{i+1} & = 2f_i - f_{i-1} - \frac{sum-1}{sum-i} \\
f_{i} & = 2f_{i-1} - f_{i-2} - \frac{sum-1}{sum-i+1} \\
\end{aligned}
$$
这很明显可以用数学归纳法求解。

### 归纳法求解

在此我们直接求出 $f_1$ 的值，然后就可以递推求解。

将 $x=sum-1$ 代入式子中可得：
$$
\begin{aligned}
f_{sum} & = 2f_{sum-1} - f_{sum-2} - (sum-1) \\
2f_{sum-1} - f_{sum-2} - (sum-1) & = 0 \\
\end{aligned}
$$
构造函数 $h_x = (sum-x+1)f_{x} - (sum-x)f_{x-1} - (sum-x)(sum-1)$，其中已知 $h_{sum-1}=0$。

假设有 $h_x = c$，则将 $f_{x} = 2f_{x-1} - f_{x-2} - \frac{sum-1}{sum-i+1}$ 代入，得到：
$$
\begin{aligned}
h_x & = c \\
(sum-x+1)(2f_{x-1} - f_{x-2} - \frac{sum-1}{sum-x+1}) - (sum-x)f_{x-1} - (sum-x)(sum-1) & = c \\
(sum-x+1)(2f_{x-1} - f_{x-2}) - (sum-1) - (sum-x)f_{x-1} - (sum-x)(sum-1) & = c \\
(sum-x+2)f_{x-1} - (sum-x+1)f_{x-2} - (sum-x+1)(sum-1) & = c \\
h_{x-1} & = c \\
\end{aligned}
$$
故，$h_i = 0,\forall i \in [1,sum-1]$，其中，通过 $h_1 = 0$ 我们可以得到：
$$
\begin{aligned}
h_1 &= sumf_{1} - (sum-1)f_{0} - (sum-1)^2 \\
sumf_{1} - (sum-1)f_{0} - (sum-1)^2 &= 0 \\
f_1 &=\frac{(sum-1)^2}{sum} \\
\end{aligned}
$$
至此，得到 $f_1$，则 $\{ f_i \}$ 可以通过递推得到。

### 答案统计

设总期望为 $E$，则 $E = \sum_{i=1}^n f_{a_i}$。

---

## 代码实现

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define max(a,b) ((a)<(b)?(b):(a))
#define add(a,b) ((a)+(b)>=(MOD)?((a)+(b)-(MOD)):((a)+(b)<0?((a)+(b)+(MOD)):((a)+(b))))
#define mul(a,b) (1ll*(a)*(b)%(MOD))
#define tomax(a,b) ((a)=max((a),(b)))
#define toadd(a,b) ((a)=add((a),(b)))
#define tomul(a,b) ((a)=mul((a),(b)))
#define FOR(i,a,b) for(register int i=(a);i<=(b);++i)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
using namespace std;
const int N=25e2+10,M=1e5+10;
int n,mx,sum,ans;
int a[N],f[M];
inline int fpow(int a,int b) {
	int res=1;
	for(a%=MOD; b; b>>=1,tomul(a,a))if(b&1)tomul(res,a);
	return res;
}
inline int Inv(int x) {
	return fpow(x,MOD-2);
}
signed main() {
	cin>>n;
	FOR(i,1,n)cin>>a[i],sum+=a[i],tomax(mx,a[i]);
	f[1]=mul(mul(sum-1,sum-1),Inv(sum));
	FOR(i,2,mx)f[i]=add(add((ll)f[i-1]<<1,-f[i-2]),mul(1-sum,Inv(sum-i+1)));
	FOR(i,1,n)toadd(ans,f[a[i]]);
	cout<<ans<<endl;
	return 0;
}
```

***提示***：注意取模与逆元相关细节。

---

## 题外话

这题还有一个弱化版：[Color - BZOJ 2554 - Virtual Judge (vjudge.net)](https://vjudge.net/problem/BZOJ-2554)，可以拿来试试手。

如果你想要一个美丽的题面，可以看：[Rainbow Balls - CodeForces 850F - Virtual Judge (vjudge.net)](https://vjudge.net/problem/CodeForces-850F#author=plus_cat)。

---

---

