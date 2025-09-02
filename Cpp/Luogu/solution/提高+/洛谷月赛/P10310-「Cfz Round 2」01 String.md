# 「Cfz Round 2」01 String

## 题目描述

定义一个 $\tt{01}$ 串是合法的，当且仅当它的首字符为 $\tt 0$ 而尾字符为 $\tt 1$。我们继而定义一个 $\tt{01}$ 串 $T$ 的权值 $f(T)$ 为，将 $T$ 划分若干个连续的合法子串的方案数。

例如 $f(\tt{001}) = \text{1}$，因为它仅可以被分割为 $[\tt 001]$；$f(\tt{0101101}) = \text{4}$，因为它可以被分割为 $[\tt 0101101][01, 01101][01011, 01][01, 011, 01]$ 共四种不同的方案；而 $f(\tt{1001010101}) = \text{0}$。

给定一个长度为 $n$ 的 $\tt{01}$ 串 $S$。定义 $f_k(l, r) = \begin{cases} f(S_{l\dots r}) & k = 0 \\ \displaystyle\sum_{l\leq l' \leq r' \leq r} f_{k-1}(l', r') & k \gt 0\end{cases}$，你需要求出 $f_k(1, n)$ 的值。

由于答案可能很大，所以你只需要输出答案对 $10^9+7$ 取模的结果。

## 说明/提示

#### 「样例解释 #1」

对于第 $1$ 组数据，用表格的交叉点表示 $f_k(l, r)$ 的值：

| $\bm{k = 0}$ | $r = 1$ | $2$ | $3$ |
| -----------: | :-----: | :-: | :-: |
| $l = 1$ | $0$ | $0$ | $1$ |
| $2$ | / | $0$ | $1$ |
| $3$ | / | / | $0$ |

| $\bm{k = 1}$ | $r = 1$ | $2$ | $3$ |
| -----------: | :-----: | :-: | :-: |
| $l = 1$ | $0$ | $0$ | $2$ |
| $2$ | / | $0$ | $1$ |
| $3$ | / | / | $0$ |

其中：

- $f_1(2, 3)= f_0(2, 2) + f_0(2, 3) + f_0(3, 3)= 0 + 1 + 0 = 1$；
- $f_1(1, 3) = f_0(1, 1) + f_0(1, 2) + f_0(1, 3) + f_0(2, 2) + f_0(2, 3) + f_0(3, 3) = 0 + 0 + 1 + 0 + 1 + 0 = 2$；

所以答案为 $2$。
 
#### 「数据范围」

设 $\sum n$ 表示单个测试点中 $n$ 的和。

对于所有数据，$1 \leq T \leq 100$，$1 \leq n \leq 2\times 10^5$，$0 \leq k \leq 10^{18}$，$\sum n \leq 6\times 10^5$，保证 $S$ 中只包含 $\tt{0}$ 和 $\tt{1}$。

**只有你通过本题的所有测试点，你才能获得本题的分数。**

## 样例 #1

### 输入

```
4
3 1
001
5 2
00101
30 10
010100110101001010010010011101
10 1000000000000
0010110101```

### 输出

```
2
19
926292963
340558843```

# 题解

## 作者：_maojun_ (赞：12)

不同于官方题解的维护方法。

---

首先 $f(S_{l\dots r})$ 给 $f_k(1,n)$ 的贡献为 ${l-1+k-1\choose k-1}{n-r+k-1\choose k-1}$，具体可以考虑这 $k$ 次是怎么从 $[1,n]$ 取子区间取到 $[l,r]$ 的。

记 $C_i={i+k-1\choose k-1}$，则 $C_0=1,C_i=\frac{i+k-1}iC_{i-1}$，可 $O(n)$ 递推出。

于是 $\mathrm{ans}=\sum\limits_{l=1}^n\sum\limits_{r=l}^nf(S_{l\dots r})C_{l-1}C_{n-r}=\sum\limits_{l=1}^nC_{l-1}\sum\limits_{r=l}^nf(S_{l\dots r})C_{n-r}$。

考虑对于每个左端点 $S_l=\texttt0$ 一遍 dp 求出 $\sum\limits_{r=l}^nf(S_{l\dots r})C_{n-r}$。

则对于一个 $S_r=\texttt1$，其方案数为所有 $S_i=\texttt1,S_{i+1}=\texttt0$ 的“合法点”$i$ 的方案数之和。

记一个 $dp$ 表示前缀合法点的方案数之和，$sum$ 表示所有 $S_r=\texttt1$ 点的方案数乘上系数之和。

则若 $S_r=\texttt1$，$sum\gets sum+dp\times C_{n-r}$，若还有 $S_{r+1}=\texttt0$，$dp\gets dp+dp$。

最后 $\mathrm{ans}\gets\mathrm{ans}+sum\times C_{l-1}$，这样得到了一个 $O(n^2)$ 的做法。

```cpp
for(int i=1;i<=n;i++)if(s[i]=='0'){
  int dp=1,sum=0;
  for(int j=i+1;j<=n;j++)if(s[j]=='1'){
    sum=(sum+dp*C[n-j])%MOD;
    if(s[j+1]=='0')dp=dp*2%MOD;
  }
  res=(res+sum*C[i-1])%MOD;
}
```

注意到对于每个 $r$ 关于 $dp$ 和 $s$ 的转移是固定的，而且正好符合加乘矩阵的逻辑，考虑矩乘。

举个例子，若 $S_i=\texttt1$ 且 $S_{i+1}=\texttt0$，则有这样的转移。

$$\begin{bmatrix}s'\\dp'\end{bmatrix}=\begin{bmatrix}s\\dp\end{bmatrix}\begin{bmatrix}1&C_{n-i}\\0&2\end{bmatrix}$$

初始时 $\begin{bmatrix}s\\dp\end{bmatrix}=\begin{bmatrix}0\\1\end{bmatrix}$，维护一个转移矩阵的后缀和即可，复杂度 $O(n\omega^3)$，其中 $\omega=2$。

```cpp
void solve(){
	scanf("%d%lld%s",&n,&k,s+1);k%=MOD;
	C[0]=1;for(int i=1;i<=n;i++)C[i]=C[i-1]*(i+k-1)%MOD*inv[i]%MOD;
	ll res=0;mtx A,M,T;
	A[0][1]=M[0][0]=M[1][1]=1;	// A 为初始矩阵，M 为后缀积，初始为单位矩阵
	for(int i=n;i;i--)
		if(s[i]=='0')res=(res+(A*M)[0][0]*C[i-1])%MOD;
		else{
			T[0][0]=1;T[1][0]=C[n-i];
			T[1][1]=1+(s[i+1]=='0');
			M=T*M;				// 注意顺序，先转移 i 的再转移 i 之后的
		}
	printf("%lld\n",res);
}
```

---

## 作者：irris (赞：5)

考虑计算 $k = 0$ 即 $f_0(1, n)$，容易发现若 $S_1$ 不为 $\tt 0$ 或 $S_n$ 不为 $\tt 1$ 则无解，因为这两个位置显然应为最开头和最末尾的一个划分出的子串的开头或末尾。

否则，我们尝试找到合法的划分位置，也就是说将一个合法串划分成两个合法串的可能位置，容易证明的是这个位置形如 $\tt 1\color{red}|\color{black}0$。由于每个划分位置是独立的（因为划分前后都是合法串），所以在原串合法的情况下，答案为 $2^{\texttt{10} \text{ 子串个数}}$。

那么考虑计算 $k \gt 0$，首先很显然的是直接根据定义式 dp，暴力是 $\mathcal O(n^4k)$ 的，前缀和优化后可以变成 $\mathcal O(n^3k)$，不过没有什么作用。

我们聚焦 $k = 1$，这里可以转化为 **每个子串的贡献**，那么可以整体扫描计算。具体地，我们从 $n \to 1$ 依次扫描 $L$，维护 $p$ 表示当前 $r \geq L$ 的贡献之和以及 $ans$ 表示 $L \leq l \leq r \leq n$ 的答案之和，那么根据上文的结论，可以如下维护：

+ 若 $S_L = \tt 1$：
	+ 若 $L \neq n$ 且 $S_{L + 1} = \tt 0$：$p \gets 2p$（$r \gt L$ 的所有贡献因为多了一个 $\tt 10$ 子串而 $\times\ 2$）；
	+ 然后，$p \gets p + 1$（加入 $r = L$ 的贡献）；
+ 若 $S_L = \tt 0$，那么 $ans \gets ans + p$（加入 $l = L$ 的答案）。

考虑 $k \gt 1$ 呢？我们不光需要计算每个子串本身的贡献，还要表示出它在 $f_k(1, n)$ 中，暴力拆开累加中的出现次数。

容易发现 $f_k(1, n)$ 其实相当于 $S$ 的「每个子串的每个子串......（共 $k$ 个『每个子串』）」，那么组合意义保平安，我们可以看做初始 $l = 1, r = n$，每次 $l, r$ 切换到 $l', r'$ 满足 $l \leq l' \leq r' \leq r$ 且最终 $l = L, r = R$ 的方案数。**由于始终 $l \leq r$，那么 $l, r$ 两维的方案数其实是独立的**，这样我们就转化成 $l = 1$ 在恰好 $k$ 次增加一个非负整数后变成 $L$ 的方案数，对差分序列插板法可以得到 $L + k - 1 \choose L$；$r$  也是同理的，所以只要在上述的扫描流程中乘上组合数系数即可。

由于 $L$ 很小而 $L + k - 1$ 很大，因此需要一些独特的方式预处理组合数，即转化为下降幂除阶乘的形式，这也是平凡的。

---

## 作者：_Cheems (赞：4)

拆贡献，考虑 $f(l,r)$ 会贡献几次，注意到 $f_k(1,n)\to f(l,r)$ 其实可以反过来视作 $[l,r]$ 区间逐渐扩大 $k$ 次，最终变成 $[1,n]$ 的过程。

于是我们计算这个东东就好了，左右端点互相独立，以计算左端点 $l$ 的拓展为例：记 $p_i$ 表示 $i$ 会被选为左端点几次，那么等价于计算 $0\le p_i$ 且 $\sum\limits_{i=1}^l p_i=k-1$ 的方案数。这里减一是因为必然有一个左端点为 $1$。

简单组合数学得知其方案数为 ${{k-1+l-1}\choose {l-1}}$，右端点同理。

考虑计算 $f(l,r)$，每个合法子串只关注其开头和结尾即可，形式为 $0\dots 10\dots 10\dots 1$ 这样子。注意开头结尾是固定的，而中间为相邻的 $10$，对它们计数即可。

记 $a_i=\sum\limits_{j=1}^{i} [c_i=0\wedge c_{i+1}=1]$，那么 $f(l,r)=2^{c_{r-2}-c_l}$。

不妨令 $k$ 先减去 $1$，那么：

$$ans=\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^{n} 2^{c_{j-2}-c_i} {{k+i-1}\choose {i-1}} {{k+n-j}\choose n-j}$$

但是 $k$ 很大，大到 $\rm lucas$ 定理都解决不了。注意到后面的组合数具有某种规律，可以递推计算。具体来说，令 $C_i={{k+i}\choose i}$，那么有 $C_i=\frac{(k+i)C_{i-1}}i$。

（下降幂是啥？蒟蒻不会。）

于是暴力枚举，得到了 $O(n^2)$ 做法~

进一步优化：

$$ans=\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^{n} 2^{c_{j-2}-c_i} C_{i-1}C_{n-j}$$

$$ans=\sum\limits_{i=1}^{n-1} 2^{-c_i}C_{i-1}\sum\limits_{j=i+1}^{n} 2^{c_{j-2}} C_{n-j}$$

然后后缀和预处理后面的和式，就能 $O(n)$ 算出了。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e5 + 5, mod = 1e9 + 7;
int T, n, k, inv[N], a[N], ans, C[N];
int s[N];
char c[N];

inline int qstp(int a, int k) {int res = 1; for(; k > 0; a = a * a % mod, k >>= 1) if(k & 1) res = res * a % mod; return res;}
signed main(){
	for(int i = 1; i < N; ++i) inv[i] = qstp(i, mod - 2); 
	cin >> T;
	while(T--){
		ans = 0;
		scanf("%lld%lld %s", &n, &k, c + 1), --k;
		C[0] = 1;
		for(int i = 1; i <= n; ++i) C[i] = C[i - 1] * ((i + k) % mod) % mod * inv[i] % mod;
		for(int i = 1; i < n; ++i) a[i] = a[i - 1] + (c[i] == '1' && c[i + 1] == '0');
		s[n + 1] = 0; 
		for(int i = n; i >= 2; --i){
			s[i] = s[i + 1];
			if(c[i] == '1') s[i] = (s[i] + qstp(2, a[i - 2]) * C[n - i] % mod) % mod;
		}
		for(int i = 1; i < n; ++i){
			if(c[i] == '0'){
				//貌似有点边界问题，所以把j=i+1单独拿出来算
				if(c[i + 1] == '1') ans = (ans + C[i - 1] * C[n - i - 1] % mod) % mod;
				ans = (ans + qstp(inv[2], a[i]) * C[i - 1] % mod * (s[i + 2] + mod) % mod) % mod;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：_H17_ (赞：0)

## 前言

神秘组合数题！苦战组合数！

## 题目分析

首先考虑 $k=0$ 的情况：我们设 $s$ 中的子串 $\texttt{10}$ 数量为 $x$。如果 $s$ 的开头不是 $\texttt{0}$ 或者结尾不是 $\texttt{1}$，那结果是 $0$；否则结果是 $2^{x}$。

为什么是 $2^{x}$？考虑每一个 $\texttt{10}$ 串从中间断开都是合法的，每一个串有断开和不断开两种选择。

考虑 $k\ne 0$ 的情况：我们考虑每一个 $f_0(l,r)$ 的贡献。对于这样的一对 $(l,r)$ 左边可以选 $l_1,l_2,\dots,l_{k-1}$，右边选 $r_1,r_2,\dots,r_{k-1}$（显然 $l_0=l,r_0=r,l_k=1,r_k=n$）。

我们考虑这个“选数”的条件：你需要选择若干个**可以相同**的数，但是**没有顺序区分**（因为 $l_k\le l_{k-1}\le\dots\le l_1\le l_0$ 且 $r_k\ge r_{k-1}\ge\dots\ge r_1\ge r_0$）。

可以重复选相同的数让我们想到了小球问题中：有 $n$ 个小球，分成 $m$ 份，每一份可以（不可以）为空。

这个小球问题的实际内容就是 $n-1$ 个空隙，选择 $m-1$ 个位置放隔板，答案是 $C_{n-1}^{m-1}$。由于每一个空隙只能插入一个隔板，这时候每一份不能为空。

由于本题可以重复选数，我们使用可以为空的小球问题：强制给总球数加上 $m$ 个，然后不能为空。这样把所有情况中的每一堆的球数减去 $1$ 即可，即一共 $C_{n+m-1}^{m-1}$。

于是我们可以把这些位置当成空隙进行小球问题，$x$ 个数中没有顺序的选择 $m$ 个可以重复的数可以看做 $x$ 个空隙，插入 $m$ 个隔板，隔板可以放在一块。

隔板可以放在一块，那就说明每一份可以为空。那有多少小球呢？一种错误的想法是：$x$ 个空隙所以 $x+1$ 个小球。

为什么是错误的？不能为空的时候第 $1$ 个球前的空隙，第 $n$ 个球后的空隙都是不能选的，但是可以为空的时候你的板子可以放在最前边和最后边。所以这里的 $x$ 个空隙对应应该放 $x-1$ 个小球。

这样我们左边的情况是：有 $l$ 个空隙（对应 $1\sim l$ 的数），也就是有 $l-1$ 个球，然后我们需要插入 $k-1$ 个隔板，也就是分成 $k$ 份，一共 $C_{l+k-2}^{k-1}$。

右边的也同理，一共 $C_{n-r+k-1}^{k-1}$。

同时 $f_0(l,r)$ 可以前缀和求出，$sum_i$ 表示 $1\sim i$ 这里有多少 $\texttt{10}$。如果 $s_l=\texttt{0},s_r=\texttt{1}$，那么 $f_0(l,r)=2^{sum_r-sum_l}$。（注意不是 $sum_{l-1}$，因为 $sum_l$ 包含了 $[l-1,l]$ 这一段区间，不能要）。

考虑如何求组合数：这里拿 $l$ 举例子。$C_{l+k-2}^{k-1}=\frac{(l+k-2)!}{(k-1)!(l-1)!}$，考虑 $l\to l+1$，此时式子变为 $\frac{(l+k-1)!}{(k-1)!l!}$。此时组合数变成了原来组合数乘上 $\frac{l+k-1}{l}$，可以递推。

递推式子的第一项可以发现都是 $1$。$r$ 可以自己求一下，是乘 $\frac{n-r+k}{n-r+1}$。

这样我们有 $O(n^2\log n)$ 做法了（求逆元需要 $O(\log n)$）。

考虑把式子写出来：$\sum\limits_{l=1}^{n}\sum\limits_{r=l}^{n}2^{sum_r-sum_l}\times C_{l+k-2}^{k-1}\times C_{n-r+k-1}^{k-1}$。

继续把 $l,r$ 分离：$\sum\limits_{l=1}^{n}\sum\limits_{r=l}^{n}(2^{-sum_l}\times C_{l+k-2}^{k-1})( 2^{sum_r}\times C_{n-r+k-1}^{k-1})$。

考虑先处理 $r$，然后求后缀和，然后再算每一个 $l$ 的答案，时间复杂度 $O(n\log n)$（求逆元需要 $O(\log n)$）。

需要特判 $f_0(l,r)=0$ 的情况。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N=2e5+2,p=1e9+7;
int T,n,k,sum[N],suf[N],ans;
string s;
int qpow(int a,int b){
    int ret=1;
    a%=p;
    while(b){
        if(b&1)
            (ret*=a)%=p;
        (a*=a)%=p,b>>=1;
    }
    return ret;
}
int inv(int x){
    return qpow(x%p,p-2);
}
void Main(){
    ans=0;
    cin>>n>>k>>s;
    s=" "+s;
    for(int i=2;i<=n;i++){
        sum[i]=sum[i-1];
        if(s[i-1]=='1'&&s[i]=='0')
            sum[i]++;//前缀和求 f_0
    }
    suf[n+1]=0;
    for(int i=n,val=1;i>=1;i--){
    	suf[i]=suf[i+1];//后缀和求 r
    	if(s[i]=='1')
        	(suf[i]+=qpow(2,sum[i])*val%p)%=p;
        (val*=((n-i+k)%p)*inv(n-i+1)%p)%=p;//递推
    }
    for(int i=1,val=1;i<=n;i++){
    	if(s[i]=='0')
        	(ans+=(val*inv(qpow(2,sum[i]))%p)*suf[i]%p)%=p;//对 l 处理答案
        (val*=((i+k-1)%p)*inv(i)%p)%=p;//递推
    }
    cout<<ans<<'\n';
    return;
}
signed main(){
//    init();
    for(cin>>T;T;--T)
        Main();
    return 0;
}
```

---

