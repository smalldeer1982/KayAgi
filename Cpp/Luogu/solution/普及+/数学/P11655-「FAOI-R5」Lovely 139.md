# 「FAOI-R5」Lovely 139

## 题目背景


$\text{Height}\leq139$。

## 题目描述

对于一个 $\tt 01$ 串 $S$（下标从 $1$ 开始），我们定义它的一个区间 $[l,r]$ 是**极长颜色段**，当且仅当它**同时**满足以下条件：
- 如果 $l\neq 1$，$S_{l-1}\neq S_l$；
- 如果 $r\neq \lvert S\rvert$，$S_{r+1}\neq S_r$；
- $\forall i\in[l,r),S_i=S_{i+1}$。

定义 $g(S)$ 为 $S$ 的**不同**极长颜色段数。比如 $g(00)=1$，$g(1110)=2$，$g(001011)=4$。

定义 $f(n,m)$ 的值为所有**恰好包含 $\boldsymbol n$ 个 $\tt 0$ 和 $\boldsymbol m$ 个 $\tt 1$** 的 $\tt 01$ 串 $S$ 的 $g(S)$ 之和。

你需要回答 $T$ 个问题，每次给出 $n,m$ 的值，求 $f(n,m)$ 的值对 $10^9+7$ 取模后的结果。

## 说明/提示

### 样例 1 解释

对于第一组数据 $n=2,m=2$，一共有六个本质不同的 $S$，答案为 $g(0011)+g(0101)+g(0110)+g(1001)+g(1010)+g(1100)=2+4+3+3+4+2=18$。

### 数据规模与约定

**本题采用捆绑测试**。

- Subtask 1（15 pts）：$0 \le n+m \le 20$，$1 \le T \le 10$。
- Subtask 2（25 pts）：$0 \le n+m \le 4 \times 10^3$。
- Subtask 3（20 pts）：$1 \le T \le 10$。
- Subtask 4（40 pts）：无特殊限制。

对于所有数据，保证 $1 \leq T \leq 10^6$，$0 \leq n+m\leq 2 \times 10^6$，$0\le n,m\le 2\times10^6$。

## 样例 #1

### 输入

```
3
2 2
4 6
7 8
```

### 输出

```
18
1218
54483
```

## 样例 #2

### 输入

```
3
845 826
672 826
618 925```

### 输出

```
789284214
588160420
730993180```

## 样例 #3

### 输入

```
1
1 46```

### 输出

```
139```

# 题解

## 作者：喵仔牛奶 (赞：22)

## Solution

考虑如何对 $S$ 计算 $g(S)$，一种计算方式是 $g(S)$ 等于满足 $S_{i-1}\neq S_i$ 的位置 $i$ 数量再加上 $1$。

先考虑那个 $+1$，一共有 $\binom{n+m}{n}$ 个 $\tt 01$ 串 $S$，这部分贡献为 $\binom{n+m}{n}$。

接着考虑对于位置 $i$，$S_i\neq S_{i-1}$ 的方案数。$S_{i-1}S_i$ 可能是 $\tt 01$ 或 $\tt 10$，然后其它 $\lvert S\rvert-2$ 的个位置随便排，这部分贡献为 $\binom{n+m-2}{n-1}\times 2$。可以发现对于所有 $i$ 贡献都一样，所以乘上 $n+m-1$。

因此答案为
$$\binom{n+m}{n}+(n+m-1)\times\binom{n+m-2}{n-1}\times 2$$

---

## 作者：yedalong (赞：6)

## 前言

这是一道数学题，涉及到了乘法逆元以及组合数学。

## 思路

最开始，我们把一整个字符串认定为极长颜色段，那最开始的极长颜色段数量就为字符串的数量，而我们可以根据题目得出，字符串的数量为 $\binom{n+m}{n}$。接着我们考虑位置 $i$，若 $S_i\neq S_{i-1}$，那么位置 $i$ 就能做出贡献。关键是贡献多少呢？那我们就要算这种情况下的方案数。我们固定死 $i$ 和 $i-1$ 两个位置，剩下的字符随便排能有 $\binom{n+m-2}{n-1}$ 种可能，而 $i$ 和 $i-1$ 这两个位置能有 `01` 和 `10` 两种可能，再乘上二即可。而在整个字符串内，我们能够找到 $n+m-1$ 个这样的 $i$，因此答案就为 $\binom{n+m}{n}+(n+m-1)\times2\times\binom{n+m-2}{n-1}$。此外，在计算组合函数时要用到乘法逆元，不懂的同学可以参考[这篇文章](https://www.luogu.com.cn/article/2ooix0rj)，这里就不多说了。

## AC code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int T,n,m,jc[2000006],inv[2000005];//jc表示阶乘，inv表示逆元
int qpow(int a,int b){//快速幂
    int ans=1;
    while(b){
        if(b&1) ans=ans*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return ans;
}
int c(int n,int m){return jc[n]*inv[n-m]%mod*inv[m]%mod;}//求组合的函数
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    jc[0]=1;
    for(int i = 1;i<=2000000;i++) jc[i]=jc[i-1]*i%mod;//求阶乘
    inv[2000000]=qpow(jc[2000000],mod-2);//费马小定理
    for(int i = 1999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;//这里用到了线性求逆元
    while(T--){
        cin>>n>>m;
        if(!n&&!m){
            cout<<"1\n";
            continue;
        }
        cout<<(c(n+m,n)+(n+m-1)*c(n+m-2,n-1)%mod*2%mod)%mod<<'\n';//记得多加几个mod
    }
    return 0;
}
```

---

## 作者：zhoumurui (赞：5)

### 题面展示

对于一个 $01$ 串 $S$（下标从 $1$ 开始），我们定义它的一个区间 $[l,r]$ 是**极长颜色段**，当且仅当它**同时**满足以下条件：
- 如果 $l\neq 1$，$S_{l-1}\neq S_l$；
- 如果 $r\neq \lvert S\rvert$，$S_{r+1}\neq S_r$；
- $\forall i\in[l,r),S_i=S_{i+1}$。

定义 $g(S)$ 为 $S$ 的**不同**极长颜色段数。比如 $g(\tt00)=1$，$g(\tt1110)=2$，$g(\tt001011)=4$。

定义 $f(n,m)$ 的值为所有恰好包含 $n$ 个 0 和 $m$ 个 1 的 01 串 $S$ 的 $g(S)$ 之和。

多测，求 $f(n,m)$ 的值对 $10^9+7$ 取模后的结果。

### 解题思路

前置知识：动态规划、模意义下的乘法逆元。

#### 40 分

我们考虑 DP。令 $F[i][j]$ 表示恰好包含 $i$ 个 0 和 $j$ 个 1，且末尾为 0 的 01 串 $S$ 的 $g(S)$ 之和；$G[i][j]$ 表示恰好包含 $i$ 个 0 和 $j$ 个 1，且末尾为 1 的 01 串 $S$ 的 $g(S)$ 之和。

状态转移方程为：

$$F[i][j]=F[i-1][j]+G[i-1][j]+\displaystyle\binom{i-1}{i+j-2}$$

$$G[i][j]=F[i][j-1]+G[i][j-1]+\displaystyle\binom{i-1}{i+j-2}$$

以 $F[i][j]$ 为例。$G[i][j]$ 类似。

1. 倒数第二位是 0。添加一个 0 后，极长颜色段数量不变，答案为 $F[i-1][j]$。

2. 倒数第二位是 1。添加一个 1 后，极长颜色段数量加一，答案为 $G[i-1][j]+\displaystyle\binom{i-1}{i+j-2}$。这个组合数的含义是前 $i+j-2$ 位的组合方案数。

令 $H[i][j] = F[i][j]+G[i][j]$，它就是答案。合并一下转移方程：

$$H[i][j]=H[i-1][j]+H[i][j-1]+2\displaystyle\binom{i-1}{i+j-2}$$

初始状态为 $H[0][i]=H[i][0]=1$。由于数据原因，特判 $H[0][0]=1$，获得 $40$ 分。

#### 100 分

推式子环节。

---

**定理 1**

$$ H[i][j]=\frac{(i+j-1)! \times (2\times i\times j+i+j)}{i!\times j!}$$

赛时我是通过把每一行的式子通过解方程组的形式推出来再找规律得出的结论。这里只给出式子的证明。

**证明** 用数学归纳法。

当 $i=0$ 时，$H[0][j]=\displaystyle \frac{(j-1)! \times j}{j!} = 1$。当 $j=0$ 时类似得 $H[j][0]=1$。

假设 $i=p-1,j=q$ 及 $i=p,j=q-1$ 时等式成立，那么：

$H[p][q]=H[p-1][q]+H[p][q-1]+2\displaystyle\binom{p-1}{p+q-2}$

$= \displaystyle \frac{(p+q-2)! \times (2\times (p-1)\times q+p+q-1)}{(p-1)!\times q!}+\frac{(p+q-2)! \times (2\times p\times (q-1)+p+q-1)}{p!\times (q-1)!} + \frac{(p+q-2)!}{(p-1)!\times (q-1)!}$

$= \displaystyle \frac{p\times(p+q-2)! \times (2\times p\times q+p-q-1)}{p!\times q!}+\frac{q \times (p+q-2)! \times (2\times p\times q-p+q-1)}{p!\times q!} + \frac{p \times q \times (p+q-2)!}{p!\times q!}$

$\displaystyle=  \frac{(p+q-2)!}{p!\times q!} \times (p \times (2\times p\times q+p-q-1)+q \times (2\times p\times q-p+q-1) + p \times q)$

$\displaystyle=  \frac{(p+q-2)!}{p!\times q!} \times ( (2p^2q+p^2-pq-p)+ (2p q^2-p q+q^2-q) + p  q)$

$\displaystyle=  \frac{(p+q-2)!}{p!\times q!} \times ( 2p^2q+2pq^2+p^2-pq+q^2-p-q)$

$\displaystyle=  \frac{(p+q-2)!}{p!\times q!} \times (p+q-1)( 2pq+p+q)$

$\displaystyle=  \frac{(p+q-1)!}{p!\times q!} \times ( 2pq+p+q)$

那么 $i=p,j=q$ 时等式也成立。

综上，由数学归纳法，定理成立。

---

按照公式计算答案在模 $10^9+7$ 下的结果即可。分母使用[模意义下的乘法逆元](https://www.luogu.com.cn/problem/solution/P3811)来处理。

由于数据原因，特判 $H[0][0]=1$。

### 核心代码展示
```cpp
int ksm(int a,int b){
    if (b==0)return 1;
    if (b&1)return ksm(a,b^1)*a%M;
    int k=ksm(a,b>>1);
    return k*k%M;
}
signed main(){
    cin>>t;
    fc[0]=inv[0]=1;
    for (int i=1;i<=2000000;i++){
        fc[i]=fc[i-1]*i%M;
        inv[i]=ksm(fc[i],M-2);
    }
    while (t--){
        cin>>n>>m;
        if (n==0&&m==0)cout<<"1\n";
        else cout<<fc[n+m-1]*inv[n]%M*inv[m]%M*((2*n*m%M+n+m)%M)%M<<"\n";
    }
    return 0;
}
```

---

## 作者：ANDER_ (赞：4)

#### 考察：组合数、计数。

## 题意

对于一个 $\tt 01$ 字符串 $S$，我们定义它的一个区间 $[l,r]$ 是**极长颜色段**，当且仅当它**同时**满足以下条件：
- 如果 $l\neq 1$，$S_{l-1}\neq S_l$；
- 如果 $r\neq \lvert S\rvert$，$S_{r+1}\neq S_r$；
- $\forall i\in[l,r),S_i=S_{i+1}$。

定义 $g(S)$ 为 $S$ 的**不同**极长颜色段数。

定义 $f(n,m)$ 的值为所有**恰好包含 $\boldsymbol n$ 个 $\tt 0$ 和 $\boldsymbol m$ 个 $\tt 1$** 的 $\tt 01$ 串 $S$ 的 $g(S)$ 之和。

回答 $T$ 个问题，每次给出 $n,m$，求 $f(n,m) \text{ mod } 10^9 + 7$。

## 思路

首先可以自然地得出满足条件的字符串数量的个数为：

$$\binom{n + m}{m}$$

钦定满足条件的字符串集合为 $T$。可以发现答案就是集合 $T$ 中所有字符串 $\tt01$ 变化的次数加上 $|T|$。那么我们就可以单独地分析每一位对答案的贡献。$\forall s \isin T$ 的某一位置 $i$ 满足 $1 < i \le n + m$，则对于 $s_i$ 为 $\tt1$ 且 $s_{i - 1}$ 为 $\tt0$ 的字符串个数为：

$$\binom{n + m - 2}{n - 1}$$

对于 $s_i$ 为 $\tt0$ 且 $s_{i - 1}$ 为 $\tt1$ 的字符串个数为：

$$\binom{n + m - 2}{m - 1}$$

所以 $s_i$ 的总变化次数为：

$$\binom{n + m - 2}{n - 1} + \binom{n + m - 2}{m - 1} = \binom{n + m - 1}{n}$$

所以有：

$$f(n,m) = \binom{n + m}{m} + (n + m - 1)\binom{n + m - 1}{n}$$

现在我们找到了较为一般的情况，然而特殊地，若 $nm = 0$，显然特判 $f(n,m) = 1$。所以我们得出：

$$f(n,m) = \begin{cases}
1 &\text{if }nm = 0\\
\binom{n + m}{m} + (n + m - 1)\binom{n + m - 1}{m - 1}&\text{otherwise}
\end{cases}
$$

根据公式计算即可，注意预处理阶乘、逆元和逆阶乘数组，以快速计算组合数。时间复杂度 $\mathcal{O}(n + m + T)$。
## 代码

```cpp
// Problem: T561025 「FAOI-R5」Lovely 139
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T561025?contestId=220507
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<bits/stdc++.h>

#define int long long
//#define long long ll
#define endl "\n"
#define MSOD
#define RANDOM
#define IOS

using namespace __gnu_pbds;
using namespace std;

const int N = 2e6 + 5, M = 1e6 + 5, MOD1 = 1e9 + 7ll, MOD2 = 998424353ll;

#ifdef RANDOM
	mt19937 ran(0x9f4a7c15ll);
	uniform_int_distribution<int>ran_int(1, 1e18);
	uniform_real_distribution<long double> ran_real(1, 1e9);
#endif

inline int lowbit(int x) {return x & (-x);}
inline int quick_pow(int a, int b) {int res = 1;while(b) {if(b & 1) {res *= a;}a *= a, b >>= 1;}return res;}
inline int quick_pow_mod(int a, int b, int m) {int res = 1;while(b) {if(b & 1) {res = res * a % m;}a = a * a % m, b >>= 1;}return res;}

int n, m, fac[N], inv[N];
inline int get(int x, int y) {
	if(x >= y && x >= 0 && y >= 0) {
		return inv[y] * fac[x] % MOD1 * inv[x - y] % MOD1;
	} else {
		return 0;
	}
}
inline void init() {
	fac[0] = 1;
	for(int i = 1 ; i < N ; i ++) {
		fac[i] = fac[i - 1] * i % MOD1;
	}
	inv[N - 1] = quick_pow_mod(fac[N - 1], MOD1 - 2, MOD1);
	for(int i = N - 2 ; i >= 0 ; i --) {
		inv[i] = inv[i + 1] * (i + 1) % MOD1;
	}
	return;
}
inline void solve() {
	cin>>n>>m;
	if(n == 0 || m == 0) {
		cout<<1<<endl;
	} else {
		int tmp1 = get(n + m, n), k1 = get(n + m - 2, n - 1);
		int tmp2 = ((n + m - 1) << 1) % MOD1;
		tmp2 = tmp2 * k1 % MOD1;
		cout<<(tmp1 + tmp2) % MOD1<<endl;
	}
	return;
}

signed main() {
	init();
#ifdef IOS
	ios::sync_with_stdio(false), cout.tie(0), cin.tie(0);
#endif
	int T = 1;
#ifdef MSOD
	cin>>T;
#endif
	while(T --) {solve();}
	return 0;
}

```

---

## 作者：getchar_unlocked (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P11655)

### 思路

**组合数**问题。

对于一个 $\texttt{01}$ 串 $S$，具有 $C_{n+m}^n$ 种组合方案。然后若两个相邻的字符不同，颜色段段数需增加 $1$。去掉这一位后剩余 $C_{n+m-2}^{n-1}$ 种组合方案。最后乘上两个字符相同情况 $n+m-1$ 即可。

预处理阶乘和逆元，将单次询问的复杂度降为 $\mathcal{O}(\log(n+m))$。最终时间复杂度为 $\mathcal{O}(n+m+T\log(n+m))$。

**注意事项**

- 不开 `long long` 见祖宗。
- 随时取模。

---

## 作者：_Deer_Peach_ (赞：3)

题意：

转换一下，定义一个字符串的价值为这个字符串中又多少个子串是连续的 $1$ 或 $0$，求所有由 $n$ 个 $0$ 和 $m$ 个 $0$ 的字符串的价值之和。

思路：

在场上的思路是枚举不同价值出现的字符串的数量，字符串的价值最小为 $2$，最大为 $\min(n,m) \times 2 + 1$（$n$ 或 $m$ 为 $0$ 时特判输出 $1$）。那么一个价值的数量怎么算？

首先，两种子串的数量相差最多为 $1$，因为子串是相互分割的，不可能相差超过 $1$，接着这里分类讨论一下：
1. 价值为偶数时，连续为 $1$ 的子串数量一定等于连续为 $0$ 的数量；
2. 价值为奇数时，一种子串可能出现在整个字符串的两端和中间，也有可能都在中间（这里的中间指被另一种子串包住，不出现在字符串的最前或最后）。

设价值为 $i$ 且 $m \le n$，把字符串理解为在一个长度为 $n$ 的全部为 $1$ 的字符串中插入 $\frac{i}{2}$ 个且这些子串的长度之和为 $0$ 的子串。用插板法就可以算出这些方案数。

第一种情况比较好算。其中有一个子串肯定在整个字符串的头或尾，所以就是在 $n-1$ 个空隙中插入 $\frac{i}{2}$ 个子串，因为还有一个子串可以放在头或尾，所以再乘以 $2$，再求出和为 $m$ 分成 $\frac{i}{2}$ 份有多少方案，也就是在 $m-1$ 个空隙中插入 $\frac{i}{2}-1$ 个板子的方案数，这时价值为 $i$ 的字符串数量就是 $\binom{n-1}{\frac{i}{2}-1} \times \binom{m-1}{\frac{i}{2}-1}\times 2$。

第二种情况还要分两类。一类是插入的子串都在内部，这时插入的子串数量会更少，子串数量为 $\frac{i-1}{2}$，就是在 $n-1$ 个空隙中插入 $\frac{i-1}{2}$ 个子串，在 $m-1$ 个空隙中插入 $\frac{i-1}{2}-1$ 个板子；另一类是插入的子串有两个在头和尾，这时插入的子串数会更多，子串数量为 $\frac{i+1}{2}$，就是在 $n-1$ 个空隙中插入 $\frac{i+1}{2}-2$ 个子串，在 $m-1$ 个空隙中插入 $\frac{i+1}{2}-3$ 个板子，这时价值为 $i$ 的字符串数量就是 $\binom{n-1}{\frac{i-1}{2}} \times \binom{m-1}{\frac{i-1}{2}-1} + \binom{n-1}{\frac{i+1}{2}-2} \times \binom{m-1}{\frac{i+1}{2}-1}$。

得到的答案乘以 $i$ 再累加就可以算出答案了。
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int Mod=1e9+7,N=2e6;
int t,n,m,ans,a[N+1],b[N+1];
int C(int x,int y){
	return a[x]*b[y]%Mod*b[x-y]%Mod;
}int Pow(int x,int y){
	int res=1;while(y){
		if(y&1)(res*=x)%=Mod;
		y>>=1;(x*=x)%=Mod;
	}return res%Mod;
}signed main(){
	a[0]=1;for(int i=1;i<=N;i++)a[i]=(a[i-1]*i)%Mod;
	b[N]=Pow(a[N],Mod-2);
	for(int i=N-1;i>=0;i--)b[i]=(b[i+1]*(i+1))%Mod;//预处理，注意逆元
	cin>>t;while(t--){
		ans=0;scanf("%lld %lld",&n,&m);
		if(n==0||m==0){printf("%lld\n",1ll);continue;}//特判
		if(n<m)swap(n,m);//把0和1的数量换一下并不会影响结果，这并不难想
        int cnt,x,y;
		for(int i=2;i<=2*m+(n!=m);i++){//枚举字符串价值
			if(i%2==0){//价值为偶数
				x=i/2;
				cnt=C(n-1,x-1)*C(m-1,x-1)*2%Mod;
				//cout<<i<<" "<<cnt<<endl;
			}else{//价值为奇数
				x=i/2,y=i-x;
				cnt=C(n-1,x)*C(m-1,x-1)%Mod+C(n-1,y-2)*C(m-1,y-1)%Mod;
				cnt%=Mod;
				//cout<<i<<" "<<cnt<<endl;
			}(ans+=cnt*i%Mod)%=Mod;
		}printf("%lld\n",ans%Mod);
	}return 0;
}
```
但是时间复杂度较高，只有 $35$ 分（作者太菜了，只想出这种方法）。

以下是赛后的思路，也许更加简单：

$n$ 个 $1$ 和 $m$ 个 $0$ 可以组成 $\binom{n+m}{n}$ 个字符串，对于每一个字符 $S_i$ 都有一个对字符串价值的贡献，当一个字符它相邻的字符不同时，就贡献了一个价值。去掉两个相邻不同的字符，剩余 $n-1$ 和 $m-1$ 个字符组成 $\binom{n+m-2}{n-1}$ 个字符串，有 $n+m-1$ 个位置相邻不同，又因为 $0$ 和 $1$ 可以相反，加上最前面去掉的两个字符，答案就是 $\binom{n+m}{n} + \binom{n+m-2}{n-1} \times (n+m-1) \times 2$。

代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int Mod=1e9+7,N=2e6;
int t,n,m,ans,a[N+1],b[N+1];
int C(int x,int y){
	return a[x]*b[y]%Mod*b[x-y]%Mod;
}int Pow(int x,int y){
	int res=1;while(y){
		if(y&1)(res*=x)%=Mod;
		y>>=1;(x*=x)%=Mod;
	}return res%Mod;
}signed main(){
	a[0]=1;for(int i=1;i<=N;i++)a[i]=(a[i-1]*i)%Mod;
	b[N]=Pow(a[N],Mod-2);
	for(int i=N-1;i>=0;i--)b[i]=(b[i+1]*(i+1))%Mod;
	cin>>t;while(t--){
		ans=0;scanf("%lld %lld",&n,&m);
		printf("%lld\n",(C(n+m,n)+(n+m-1)*C(n+m-2,n-1)*2%Mod)%Mod);
	}return 0;
}
```
感谢 ANDER_ 提出在 LaTex 上的错误。

---

## 作者：M1__ (赞：2)

# 题解：P11655 「FAOI-R5」Lovely 139
[题目传送门](https://www.luogu.com.cn/problem/P11655)
### 前置知识
- [加法原理、乘法原理、组合数学](https://www.luogu.com.cn/training/217#information)
- [乘法逆元](https://oi-wiki.org/math/number-theory/inverse/#__tabbed_3_1)
## 题目思路

> 对于一个 $\tt 01$ 串 $S$（下标从 $1$ 开始），我们定义它的一个区间 $[l,r]$ 是**极长颜色段**，当且仅当它**同时**满足以下条件：
>  - 如果 $l\neq 1$，$S_{l-1}\neq S_l$；
>   - 如果 $r\neq \lvert S\rvert$，$S_{r+1}\neq S_r$；
>   - $\forall i\in[l,r),S_i=S_{i+1}$。

观察上述条件，不难发现一个性质，即对于一个字符串 $S$，两个相邻的字符不同的数量加上 $1$ 就是 $S$ 的不同极长颜色段数。即：
$$g(s)=(\sum_{i=1}^n i(S_i \neq S_{i+1}))+1$$
所以，问题就分为了两个部分：
- 计算所有满足条件的相邻两个字符之和。
- 以及这些字符串的总数。（即通过排列组合生成的所有字符串所加的 $1$ 之和）。
### 计算字符串的总数
显然，这是一个排列组合问题，结果即为 $C_{m+n}^n$ 或 $C_{m+n}^m$，实际上两者的结果都是一样的，读者可以自己赋特殊值进行证明。所以通过排列组合生成的所有字符串所加的 $1$ 之和也就是 $C_{m+n}^n$ 或 $C_{m+n}^m$ 了。
### 计算所有满足条件的相邻两个字符之和
对于每一组 $S_i,S_{i+1}(S_i \neq S_{i+1})$，则还有 $n-1$ 个 $0$，$m-1$ 个 $1$，$n+m-2$ 个 $0$ 和 $1$。则对于其他子串的排列方案为 $C_{m+n-2}^{n-1}$ 或 $C_{m+n-2}^{m-1}$。同理，两者结果仍相同。又因为对于每一组 $S_i,S_{i+1}(S_i \neq S_{i+1})$，有 $\tt 01$ 和 $\tt 10$ 两种情况，并且 $S$ 中有 $n+m-1$ 组这样的数，所以所有满足条件的相邻两个字符之和为：
$$2 \times (n-m+1) \times C_{m+n-2}^{n-1}$$
所以：
$$f(n,m)=2 \times (n-m+1) \times C_{m+n-2}^{n-1}+C_{m+n}^n $$
## 代码实现
### 0pts Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod=1e9+7;
ll jc(ll a){
	ll sum=1;
	for(int i=1;i<=a;i++){
		sum=sum*i;
	}
	return sum;
}

ll zh(ll a,ll b){return jc(b)/(jc(a)*jc(b-a));}

int main(){
	ll T,n,m;
	cin>>T;
	while(T--){
		cin>>n>>m;
		cout<<(zh(n,n+m)+2*(n+m-1)*zh(n-1,n+m-2))%mod<<"\n";
	}
	return 0;
}
```

一开始推得规律后，就直接写了个阶乘和组合函数，但显然不行，还要处理对 $10^{9}+7$ 取模的问题。再到后来甚至想使用高精乘，但仍无法处理对 $10^{9}+7$ 取模的问题。            
于是想到了[P3811 【模板】模意义下的乘法逆元](https://www.luogu.com.cn/problem/P3811)和[B3717 组合数问题](https://www.luogu.com.cn/problem/B3717)，知道是乘法逆元，于是套上了板子。
### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod=1e9+7;
const ll MAXN=2e6+10;
ll f[MAXN],inv[MAXN];

inline ll read() { 
    ll x = 0, f = 1; char ch = getchar();
    while(ch>'9'||ch<'0') { if(ch=='-') f=-f;ch=getchar(); }
    while(ch>='0'&&ch<='9') { x=x*10+ch-'0';ch=getchar(); }
    return x*f;
}
ll zh(ll n,ll m){
	return f[n]*inv[m]%mod*inv[n-m]%mod;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	ll T,n,m;
	T=read();
	f[1]=f[0]=inv[1]=inv[0]=1;
	for(ll i=2;i<=MAXN;i++){
      f[i]=f[i-1]*i%mod;
      inv[i]=(mod-mod/i)*inv[mod%i]%mod;
  } 
	for(ll i=1;i<=MAXN;i++)  inv[i]=inv[i-1]*inv[i]%mod;
	for(ll i=1;i<=T;i++){
		n=read(),m=read();
		if(n==0&&m==0) cout<<1<<"\n";
		else if(n==0||m==0) cout<<1<<"\n";
		else{
			cout<<((n+m-1)*2*(zh(n+m-2,n-1)%mod)%mod+(zh(n+m,n)%mod))%mod<<"\n";
		}
	} 
	return 0;
}
```

---

## 作者：K_J_M (赞：2)

# 「FAOI-R5」Lovely 139
## 题目描述
对于一个 $\tt 01$ 串 $S$（下标从 $1$ 开始），我们定义它的一个区间 $[l,r]$ 是**极长颜色段**，当且仅当它**同时**满足以下条件：
- 如果 $l\neq 1$，$S_{l-1}\neq S_l$；
- 如果 $r\neq \lvert S\rvert$，$S_{r+1}\neq S_r$；
- $\forall i\in[l,r),S_i=S_{i+1}$。

定义 $g(S)$ 为 $S$ 的**不同**极长颜色段数。

定义 $f(n,m)$ 的值为所有**恰好包含 $\boldsymbol n$ 个 $\tt 0$ 和 $\boldsymbol m$ 个 $\tt 1$** 的 $\tt 01$ 串 $S$ 的 $g(S)$ 之和。

你需要回答 $T$ 个问题，每次给出 $n,m$ 的值，求 $f(n,m)$ 的值对 $10^9+7$ 取模后的结果。
## Solution
排列组合好题！

赛时想到一个 35pts 的做法，这里讲一下。

我们考虑固定 $g(S)$ 的答案来计数。

举例来说，$g(S)$ 的取值为 $[1,2\times \min(n,m)+[n≠m]]$，具体请读者自证。然后我们对于 $i∈[1,2\times \min(n,m)+[n≠m]]$，求出 $g(S)=i$ 的 $S$ 的数量。

不妨设 $2\times \min(n,m)+[n≠m]=k$，现在求 $g(S)=i$ 的 $S$ 的数量。我们可以想象每一段极长的字段看作 $0,1$，那么 $S$ 就变成了 $0101\dots 010$。这里需要分情况讨论一下。

如果 $2\ |\ i$，那么我们的 $S$ 肯定为 $0101\dots 0101$ 或者 $1010\dots 1010$，这样我们 $1$ 的个数有 $\frac{i}{2}$ 个。不妨记每一个 $1$ 中包含了 $x_j$ 个 $1$，每一个 $0$ 中包含了 $y_j$ 个 $0$，那么则满足 
$$\sum_{j=1}^{\frac{i}{2}}x_j=n$$
$$\sum_{j=1}^{\frac{i}{2}}y_j=m$$
注意，$x_j,y_j∈\N_{+}$。这样就转化为了求解上面两个不定方程的正整数解的个数了。通过很简单的组合数学知识可以得到第一个方程的解的个数为
$${n-1 \choose \frac{i}{2}-1}$$
同理，第二个方程解的个数为
$${m-1 \choose \frac{i}{2}-1}$$
所以当 $2 \ | \ i$ 的时候，总共的满足 $g(S)=i$ 的个数为 
$${n-1 \choose \frac{i}{2}-1} \times {m-1 \choose \frac{i}{2}-1}$$
当然这只是数量，我们还要乘上贡献 $i$。

同理可以得到当 $i$ 为奇数时的答案，因此我们的总答案为
$$\sum_{i=1}^{k}[i \bmod 2=1]\times {n-1 \choose \lfloor \frac{i-1}{2} \rfloor} \times {m-1 \choose {\lfloor \frac{i}{2} \rfloor-1} } \times i+[i \bmod 2 =0]\times {n-1 \choose \lfloor \frac{i-1}{2} \rfloor}\times {m-1 \choose \lfloor \frac{i}{2} \rfloor-1} \times i+\sum_{i=1}^{k}[i \bmod 2=1]\times {m-1 \choose \lfloor \frac{i-1}{2} \rfloor} \times {n-1 \choose {\lfloor \frac{i}{2} \rfloor-1} }\times i+[i \bmod 2 =0]\times {n-1 \choose \lfloor \frac{i-1}{2} \rfloor}\times {m-1 \choose \lfloor \frac{i}{2} \rfloor-1} \times i$$
式子可能有点丑，而且也只能拿到 35pts。~~下面开始讲正解~~

知周所众，排列组合最讲究的就是计算贡献。这里我们考虑贡献的来源是什么。

我们 $g(S)$ 是由存在相邻的两个不相等的数字的来的，那我们不妨假设 $S$ 的某一个位置上为 $01$，那么显然，它会对答案贡献 $+1$。也就是说，对于其他 $n+m-2$ 个位置来说，它们随便怎么排都可以，因为我已经固定了这两个位置，它们是一定会产生贡献的。所以，其它 $n+m-2$ 个位置排列 $n-1$ 个 $1$ 的方案数有 ${n+m-2 \choose n-1}$，但是对于 $n+m-1$ 个这样的相邻的一对来说，我们的贡献需要乘上 $n+m-1$，而且 $01$ 和 $10$ 也是不同的，所以我们的总贡献为 
$${n+m-2 \choose n-1}\times (n+m-1) \times 2$$
但是有一点需要注意，我们在考虑完 $x$ 对这样的 $01$ 时，会产生 $x+1$ 的答案，例如 $S=0110011101$ 中有 $5$ 对这样的 $01$，但是 $g(S)=6$，所以我们的总答案还要加上 $n$ 个 $1$，$m$ 个 $0$ 能组成的 $S$ 的个数，这样的个数有 ${n+m \choose n}$ 个。

所以，我们的答案为
$${n+m \choose n}+{n+m-2 \choose n-1}\times (n+m-1) \times 2$$
[Ac Code](https://www.luogu.com.cn/paste/4d3gn1xy)

---

## 作者：CrazyEagle (赞：2)

### $40$ 分：递推

记 $f_{i,j,0}$ 表示由 $i$ 个 $0$ 与 $j$ 个 $1$ 组成的所有以 $0$ 结尾的字符串中的极长颜色段数，$f_{i,j,1}$ 同理。$g_{i,j}$表示由 $i$ 个 $0$ 与 $j$ 个 $1$ 组成的不同的字符串个数。可得：

$$
g_{i,j}={i+j\choose i}
$$

那么有：

$$
f_{i,j,0}=f_{i-1,j,0}+f_{i-1,j,1}+g_{i-1,j-1}\\
f_{i,j,1}=f_{i,j-1,0}+g_{i-1,j-1}+f_{i,j-1,1}
$$

把 $f_{i,j,0}$ 与 $f_{i,j,1}$ 合并起来，就有：

$$f_{i,j}=f_{i-1,j}+f_{i,j-1}+2\times g_{i-1,j-1}$$

边界当 $i=0$ 或 $j=0$ 时取 $1$。
代码很简单，不展示了。

### 满分：

我是直接用上面的代码打表找规律的（那叫一个折磨），所以只能讲一讲自己找的大致过程。

首先我钦定 $i=1$，那么答案就是关于 $j$ 的一个函数。不难发现，$f_{1,j}=3\times j+1$

然后钦定 $i=2$，对着数据凑就有：$f_{2,j}=\frac{(5\times j+2)(j+1)}{2}$

再用已知的 $f_{3,1}=10$ 去凑在 $i=3$ 时的表达式。观察上面，由于在递推时用到了二项式系数，猜测分母为 $3!=6$，然后……编不下去了，纯猜，得出：$f_{3,j}=\frac{(7\times j+3)(j+2)(j+1)}{6}$

不难想，$f_{4,j}=\frac{(9\times j+4)(j+3)(j+2)(j+1)}{24}$

最后观察一下得出规律并整理出通式：
$$
f_{i,j}=(i+2\times i\times j+j)\times\frac{(i+j-1)!}{i!\times j!}
$$

预处理后即可 $O(1)$ 回答。


```cpp
#include<iostream>
#define int long long
using namespace std;
const int mod=1e9+7;
int F[2000006],G[2000006];//阶乘与逆元 
int fpow(int a,int b)//快速幂 
{
	int ret=1;
	a%=mod;
	for(;b;b>>=1)
	{
		if(b&1)ret=ret*a%mod;
		a=a*a%mod;
	}
	return ret;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	F[0]=F[1]=1;
	G[0]=1;
	for(int i=2;i<2000006;++i)F[i]=F[i-1]*i%mod;//阶乘 
	G[2000005]=fpow(F[2000005],mod-2);//费马小定理 
	for(int i=2000004;i>0;--i)G[i]=G[i+1]*(i+1)%mod;//逆元 
	int n;
	cin>>n;
	while(n--)
	{
		int a,b;
		cin>>a>>b;
		if(a==0&&b==0)//注意特判 
		{
			cout<<"1\n";
			continue;
		}
		cout<<((2*a%mod+1)%mod*b%mod+a)%mod*F[b+a-1]%mod*G[a]%mod*G[b]%mod<<'\n';//凑出来的公式 
	}
}
```

---

## 作者：_O_v_O_ (赞：1)

我们注意到 $n$ 个 $0$ 和 $m$ 个 $1$ 可以组成 ${n+m\choose n}$ 个本质不同的 01 串。因为我们可以视为在 $n+m$ 个空中填入 $n$ 个 $0$

又因为每个字符串至少都有 $1$ 个极长颜色段，那么我们先考虑这部分。

然后我们又要如何计算剩下的答案呢？

我们注意到，上面算到的贡献不妨就视为计算到了一个字符串中第一个极长颜色段。接下来每个极长连续段中设开头为 $s_i$，那么 $s_{i-1}s_i$ 肯定为 $\texttt{01}$ 或 $\texttt{10}$ 之一，剩下的随便填。此部分贡献为 $2\times {n+m-2\choose n-1}$，又因为贡献对于每个位置都有效，那么此部分总贡献为 $(n+m-1)\times 2\times {n+m-2\choose n-1}$。

那么答案为：

$${{n+m\choose n}+(n+m-1)\times 2\times {n+m-2\choose n-1}}$$

直接逆元求组合即可。

记得不要把模数写成 $998244353$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=2e6+5,mod=1e9+7;
int fac[N],inv[N],n,m,T;

int exp(int x,int y){
	int ans=1;
	while(y){
		if(y&1) (ans*=x)%=mod;
		(x*=x)%=mod;
		y>>=1;
	}
	return ans;
}

int calc(int x,int y){
	return fac[x]*inv[y]%mod*inv[x-y]%mod;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	fac[0]=1;
	for(int i=1;i<=N-5;i++) fac[i]=fac[i-1]*i%mod;
	for(int i=0;i<=N-5;i++) inv[i]=exp(fac[i],mod-2);
	cin>>T;while(T--){
		cin>>n>>m;
		if(n==0||m==0){
			cout<<1<<endl;
			continue;
		}
		cout<<(calc(n+m,n)+2*(n+m-1)*calc(n+m-2,n-1)%mod)%mod<<endl;
	}
	return 0;
}
```

---

## 作者：yezicong1104 (赞：1)

### 题目描述

对于一个 $01$ 串 $S$（下标从 $1$ 开始），我们定义它的一个区间 $[l,r]$ 是**极长颜色段**，当且仅当它**同时**满足以下条件：

- 若 $l \ne 1$，$S_{l-1} \ne S_l$；
- 若 $r \ne \lvert S \rvert$，$S_{r+1} \ne S_r$；
- $\forall i \in [l,r),S_i=S_{i+1}$。

定义 $g(S)$ 为 $S$ 的**不同**极长颜色段数。

定义 $f(n,m)$ 的值为所有**恰好包含 $n$ 个 $0$ 和 $m$ 个 $1$** 的 $01$ 串 $S$ 的 $g(S)$ 之和。

回答 $T$ 个问题，每次给出 $n,m$ 的值，求 $f(n,m) \bmod (10^9+7)$ 的值。

#### 样例
**输入**
```
3
2 2
4 6
7 8
```
**输出**
```
18
1218
54483
```

----------

### 算法
#### (组合计数、逆元)

易得 $g(S)=1+\sum_{i=1}^{n+m-1}[S_i \ne S_{i+1}]$。

先考虑 $1$，由于有 $C_{n+m}^n$ 个 $01$ 串 $S$，所以一共加了 $C_{n+m}^n$ 个 $1$。

在 $S$ 中，对于 $\forall i \in [1,n+m)$，若 $S_i \ne S_{i+1}$，对答案的贡献为 $1$。$S_i$ 和 $S_{i+1}$ 有 $01$ 和 $10$ 两种可能，其余的 $n+m-2$ 个数字随便排列，有 $C_{n+m-2}^{n-1}$ 中排列。
所以对于 $\forall i$，所有 $[S_i \ne S_{i+1}]$ 的和对答案的贡献为 $2 \times C_{n+m-2}^{n-1}$，
由于一共有 $n+m-1$ 个 $i$，所以所有 $\sum_{i=1}^{n+m-1}[S_i \ne S_{i+1}]$ 的和对答案的贡献为 $2 \times C_{n+m-2}^{n-1} \times (n+m-1)$。

综上所述，答案为
$$C_{n+m}^n+2 \times C_{n+m-2}^{n-1} \times (n+m-1)$$

预处理 $fac$ 数组存储阶乘，$inv$ 数组存储逆元，$facinv$ 数组存储阶乘的逆元，可得 $C_a^b=\frac{a!}{b!(a-b)!}=fac_a \times facinv_b \times facinv_{a-b}$。

#### 时间复杂度 $O(T)$

#### C++ 代码

```cpp
#include <iostream>
using namespace std;

typedef long long LL;
const int N = 2000010, MOD = 1e9 + 7;

int fac[N], inv[N], facinv[N];

LL C(int n, int m) { //计算组合数
	return (LL)fac[m] * facinv[m - n] % MOD * facinv[n] % MOD;
}

int main() {
	fac[0] = facinv[0] = inv[1] = 1; //初始化
	for (int i = 1; i < N; i++) //计算阶乘数组
		fac[i] = (LL)fac[i - 1] * i % MOD;
	for (int i = 2; i < N; i++) //计算逆元数组
		inv[i] = MOD - (LL)inv[MOD % i] * (MOD / i) % MOD;
	for (int i = 1; i < N; i++) //计算阶乘的逆元数组
		facinv[i] = (LL)facinv[i - 1] * (LL)inv[i] % MOD; //逆元的地推公式
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m;
		scanf("%d%d", &n, &m);
		int ans = 0;
		if (!n || !m) { //特判
			puts("1");
			continue;
		}
        //计算答案
		ans = (2ll * (n + m - 1) * C(n - 1, m + n - 2) % MOD + C(n, n + m)) % MOD;
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：wangkaiwei (赞：1)

首先理解一下极长颜色段：连续的 $0$ 或 $1$。~~题目里说的那么高深。~~  

学过排列组合的的朋友们都知道，$n$ 个 $0$ 和 $m$ 个 $1$ 可以组成 $\binom{n}{n+m} $ 个字符串。易得这部分的贡献为 $\binom{n}{n+m} $。  

接着考虑相邻两个字符不同时，分两种情况。去掉这两个字符之后，剩下的 $n+m-2$ 个字符又可以随便排，即 $\binom{n-1}{n+m-2} $。相邻两个字符不同的情况最多有 $n+m-1$ 种，所以这部分的贡献为 $2\times(n+m-1)\times\binom{n-1}{n+m-2}$。

所以最终答案为 $2\times(n+m-1)\times\binom{n-1}{n+m-2}+\binom{n}{n+m}$。

实现方面可以用逆元求组合数。记得特判。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+5,MOD=1e9+7;
int fact[N],infact[N];
int qmi(int a,int k){
    int res=1;
    while(k){
        if(k&1)res=res*a%MOD;
        k>>=1;
        a=a*a%MOD;
    }
    return res;
}
int c(int n,int m){return (fact[n]*infact[n-m]%MOD*infact[m]%MOD)%MOD;}
signed main(){
    fact[0]=infact[0]=1;
    for(int i=1;i<N;++i){
        fact[i]=fact[i-1]*i%MOD;
        infact[i]=infact[i-1]*qmi(i,MOD-2)%MOD;
    }
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        if(n==0&&m==0) cout<<1<<endl;
        else cout<<(2*(n+m-1)%MOD*c(n+m-2,n-1)%MOD+c(n+m,n)%MOD)%MOD<<endl;
    }
    return 0;
}

```

---

## 作者：Wind_love (赞：1)

好久没做组合数学了，正好做了个月赛题，写个题解。   
### 解法
我们注意到，题目中所求的 $g(S)$ 其实是字符串 $S$ 中 $01$ 变化的次数加一。    
于是我们想到排列组合来求解，分为两部分，先处理后面的加一，发现一共有 $C(n+m,n)$ 中排列情况，每种排列加一，所以直接在答案上加 $C(n+m,n)$，这第一个部分就处理完了。   
接下来看变化次数对答案的贡献。不难发现，对于每一组不同且相邻的位置，可以将剩下的字符任意排列，所以对答案贡献为 $C(n+m-2,n-1)\times2$，又因为共有 $n+m-1$ 对相邻对，所以这部分对答案的最终贡献为 $C(n+m-2,n-1)\times2\times(n+m-1)$。   
注意到这里需要取模，又因为组合数需要除法，所以记得处理逆元，阶乘只要预处理出来就好。    
最终答案为 $C(n+m,n)+C(n+m-2,n-1)\times2\times(n+m-1)$。
### 代码如下
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int T,n,m;
int fac[2000005];
int qpow(int a,int b){
	int fac=1%mod;
	while(b){
		if(b&1)fac*=a,fac%=mod;
		a*=a,a%=mod;
		b>>=1;
	}
	return fac;
}
void pre(){
	fac[0]=1;
	for(int i=1;i<=2e6;i++)fac[i]=(fac[i-1]*i)%mod;
	return;
}
int C(int n,int m){
	return (fac[n]*qpow(fac[m],mod-2)%mod*qpow(fac[n-m],mod-2))%mod;
}
signed main(){
	pre();
	cin>>T;
	while(T--){
		cin>>n>>m;
		if(n==0&&m==0)cout<<1<<"\n";
		else{
			int ans=0;
			ans+=C(n+m,n);
			ans=(ans+2*C(n+m-2,n-1)%mod*(n+m-1)%mod)%mod;
			cout<<ans<<"\n";
		}
	}
	return 0;
}

---

## 作者：nightwatch.ryan (赞：1)

## Analysis
### Step 1
下设所有字符串的下标从 $1$ 开始。

对 $S$ 计算 $g(S)$。

根据题目中对 $g(S)$ 的定义，容易得出一种计算 $g(S)$ 的方式：$\sum_{i = 2}^{|S|} [S_{i - 1} \neq S_{i}] + 1$。
### Step 2
对于题目中所描述的 $\tt 01$ 串，即由 $n$ 个 $0$ 和 $m$ 个 $1$ 组成的 $\tt 01$ 串， 显然有 $\binom{n + m}{n}$ 个不同的 $\tt 01$ 串 $S$。

考虑对每个 $S$ 计算 $g(S)$。先计算式子中 $+1$ 部分，这部分对答案的贡献为 $\binom{n + m}{n}$。

接下来，我们这样考虑：对于 $S_i$（$i \neq |S|$），我们假设 $S_i \neq S_{i + 1}$，即 $S_i$ 和 $S_{i + 1}$ 一个为 $\tt 0$，一个为 $\tt 1$。我们从 $n + m$ 个位置先去掉两端的位置，还剩下 $n + m - 2$ 个位置，从这其中选择 $n - 1$ 个位置放 $0$，或者 $m - 1$ 个位置放 $1$，方案数为 $\binom{n + m - 2}{n - 1} = \binom{n + m - 2}{m - 1}$，因为 $S_i$ 和 $S_{i + 1}$ 可以交换，所以这部分的贡献为 $\binom{n + m - 2}{n - 1} \times 2$。

接下来，注意到对于每一个 $i$，都有上述考虑，故这部分的贡献为 $\binom{n + m - 2}{n - 1} \times 2 \times (n + m - 1)$。
### Step 3
最后答案即为 $\binom{n + m}{n} + (n + m - 1) \times \binom{n + m - 2}{n - 1} \times 2$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int N = 2e6 + 5;
using ll = long long;
char buf[100000], *pa(buf), *pb(buf);
char obuf[1000000], *p3 = obuf;
#define gc pa == pb && (pb = (pa = buf) + fread(buf, 1, 100000, stdin), pa == pb) ? EOF : *pa ++
#define pc(x) (p3 - obuf < 1000000) ? (*p3 ++ = x) : (fwrite(obuf, p3 - obuf, 1, stdout), p3 = obuf, *p3 ++ = x)
ll read(){
    ll t = 1,x = 0;
    char c = gc;
    while(c < '0' || c > '9') c = gc;
    while(c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48),c = gc;
    return x * t;
} 
char o[12];
void write(ll x){
    int len = 0;
    while(x) o[len ++] = x % 10 + 48, x /= 10;
    while(len --) pc(o[len]);
}
ll fac[N], inv[N];
ll qpow(){
    ll ans = 1, x = fac[N - 1], y = mod - 2;
    while(y){
        if(y & 1) ans = (ans * x) % mod;
        x = (x * x) % mod, y >>= 1;
    }
    return ans;
}
ll C(ll n, ll m){
    if(m == 0) return 1;
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int main(){
    cin.tie(0) -> sync_with_stdio(0);
    fac[0] = 1;
    for(int i = 1; i < N; i ++)
     fac[i] = fac[i - 1] * i % mod;
    inv[N - 1] = qpow();
    for(int i = N - 2; i >= 0; i --)
     inv[i] = inv[i + 1] * (i + 1) % mod;
    int T = read();
    while(T --){
        ll n = read(), m = read();
        ll ans = (n + m - 1) * C(n + m - 2, n - 1) % mod * 2 % mod;
        ans = (ans + C(n + m, n)) % mod;
        write(ans); pc('\n');
    }
    fwrite(obuf, p3-obuf, 1, stdout);
}
```

---

## 作者：FurippuWRY (赞：0)

由题意可得，极长颜色段（下面简称颜色段）是一串连续相同字符的字符串，且段数即为字符的变化次数（即子串 $\tt 01$ 与 $\tt 10$ 的出现次数）加一。由基本的组合数学知识可得，恰好包含 $n$ 个 $\tt 0$ 与 $m$ 个 $\tt 1$ 的字符串数为 $\mathrm C ^ n _ {n + m}$。由于所有字符串是等概率出现的，那么所有字符串的颜色段数总和等于每个字符串颜色段数的期望乘以总字符串数。

接下来开始计算期望。显然字符串的长度为 $n + m$，对于任意一对相邻字符，第一位可以是 $\tt 0$ 或 $\tt 1$，第二位也可以是 $\tt 0$ 或 $\tt 1$，那么第一位有 $n + m$ 种选择，第二位有 $n + m - 1$ 种选择，总选择方案数即为 $(n + m)(n + m - 1)$。然后考虑变化的相邻字符对数，从 $n$ 个 $\tt 0$ 中选一个，$m$ 个 $\tt 1$ 中选一个，两种排列方式，那么总方案为 $2mn$，变化相邻字符的出现概率为 $\dfrac{2mn}{(n + m)(n + m - 1)}$，再乘上相邻字符数 $n + m - 1$，可以得到变化相邻字符的期望为 $\dfrac{2mn}{n + m}$，因为求的是颜色段数的期望，所以还要加上一，为 $\dfrac{2mn}{n + m} + 1$。

最后，所有字符串的颜色段数总和即为：

$$\mathrm C ^ n _ {n + m} \times (\dfrac{2mn}{n + m} + 1)$$

由于涉及组合数取模，而且是多测，考虑预处理，先计算 $i! \bmod (10 ^ 9 + 7)$ 和 $(i!) ^ {-1} \bmod (10 ^ 9 + 7)$，询问时再用快速幂计算 $(n + m) ^ {-1}$，调用预处理的结果计算即可。

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 4e6 + 7, mod = 1e9 + 7;

int t, m, n;
int f[N], inv[N];

inline
int fpm(int a, int b, int m) {
	a %= m;
	int x = 1;
	while (b) {
		if (b & 1) x = x * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return x;
}

inline
int g() {
	return fpm(n + m, mod - 2, mod) * (2 * m * n % mod) + 1;
}

inline
int h() {
	return f[n + m] * inv[n] % mod * inv[m] % mod;
}

signed main() {
	
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	f[0] = f[1] = inv[0] = inv[1] = 1;
    for (int i = 2; i < N; ++i) {
    	f[i] = f[i - 1] * i % mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	}
    for (int i = 2; i < N; ++i) {
    	inv[i] = inv[i] * inv[i - 1] % mod;
	}
	cin >> t;
	while (t--) {
		cin >> n >> m;
		if (!m && !n) cout << "1\n";
		else {
			cout << g() % mod * h() % mod << '\n';
		}
	}
	
	return 0;
}
```

---

