# Balance Addicts

## 题目描述

Given an integer sequence $a_1, a_2, \dots, a_n$ of length $n$, your task is to compute the number, modulo $998244353$, of ways to partition it into several **non-empty** **continuous** subsequences such that the sums of elements in the subsequences form a **balanced** sequence.

A sequence $s_1, s_2, \dots, s_k$ of length $k$ is said to be balanced, if $s_{i} = s_{k-i+1}$ for every $1 \leq i \leq k$. For example, $[1, 2, 3, 2, 1]$ and $[1,3,3,1]$ are balanced, but $[1,5,15]$ is not.

Formally, every partition can be described by a sequence of indexes $i_1, i_2, \dots, i_k$ of length $k$ with $1 = i_1 < i_2 < \dots < i_k \leq n$ such that

1.  $k$ is the number of non-empty continuous subsequences in the partition;
2.  For every $1 \leq j \leq k$, the $j$\-th continuous subsequence starts with $a_{i_j}$, and ends exactly before $a_{i_{j+1}}$, where $i_{k+1} = n + 1$. That is, the $j$\-th subsequence is $a_{i_j}, a_{i_j+1}, \dots, a_{i_{j+1}-1}$.

There are $2^{n-1}$ different partitions in total.

Let $s_1, s_2, \dots, s_k$ denote the sums of elements in the subsequences with respect to the partition $i_1, i_2, \dots, i_k$. Formally, for every $1 \leq j \leq k$,

$$
s_j = \sum_{i=i_{j}}^{i_{j+1}-1} a_i = a_{i_j} + a_{i_j+1} + \dots + a_{i_{j+1}-1}. 
$$
 For example, the partition $[1\,|\,2,3\,|\,4,5,6]$ of sequence $[1,2,3,4,5,6]$ is described by the sequence $[1,2,4]$ of indexes, and the sums of elements in the subsequences with respect to the partition is $[1,5,15]$.

Two partitions $i_1, i_2, \dots, i_k$ and $i'_1, i'_2, \dots, i'_{k'}$ (described by sequences of indexes) are considered to be different, if at least one of the following holds.

-   $k \neq k'$,
-   $i_j \neq i'_j$ for some $1 \leq j \leq \min\left\{ k, k' \right\}$.


## 说明/提示

For the first test case, there is only one way to partition a sequence of length $ 1 $ , which is itself and is, of course, balanced.

For the second test case, there are $ 2 $ ways to partition it:

- The sequence $ [1, 1] $ itself, then $ s = [2] $ is balanced;
- Partition into two subsequences $ [1\,|\,1] $ , then $ s = [1, 1] $ is balanced.

For the third test case, there are $ 3 $ ways to partition it:

- The sequence $ [0, 0, 1, 0] $ itself, then $ s = [1] $ is balanced;
- $ [0 \,|\, 0, 1 \,|\, 0] $ , then $ s = [0, 1, 0] $ is balanced;
- $ [0, 0 \,|\, 1 \,|\, 0] $ , then $ s = [0, 1, 0] $ is balanced.

For the fourth test case, there are $ 4 $ ways to partition it:

- The sequence $ [1, 2, 3, 2, 1] $ itself, then $ s = [9] $ is balanced;
- $ [1, 2 \,|\, 3 \,|\, 2, 1] $ , then $ s = [3, 3, 3] $ is balanced;
- $ [1 \,|\, 2, 3, 2 \,|\, 1] $ , then $ s = [1, 7, 1] $ is balanced;
- $ [1 \,|\, 2 \,|\, 3 \,|\, 2 \,|\, 1] $ , then $ s = [1, 2, 3, 2, 1] $ is balanced.

For the fifth test case, there are $ 2 $ ways to partition it:

- The sequence $ [1, 3, 5, 7, 9] $ itself, then $ s = [25] $ is balanced;
- $ [1, 3, 5 \,|\, 7 \,|\, 9] $ , then $ s = [9, 7, 9] $ is balanced.

For the sixth test case, every possible partition should be counted. So the answer is $ 2^{32-1} \equiv 150994942 \pmod {998244353} $ .

## 样例 #1

### 输入

```
6
1
1000000000
2
1 1
4
0 0 1 0
5
1 2 3 2 1
5
1 3 5 7 9
32
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0```

### 输出

```
1
2
3
4
2
150994942```

# 题解

## 作者：TKXZ133 (赞：6)

[Balance Addicts](https://www.luogu.com.cn/problem/CF1738E)

### 题目大意

给定序列 $a$，求有多少种合法的划分方案。

定义一种划分方案是合法的当且仅当划分出的各段序列的和构成回文序列。

### 思路分析

一种不太一样的做法。

我们先对 $a$ 做一遍前缀和，得到 $s$。

观察各段序列的和形式：

$$s_{p_1},s_{p_2} - s_{p_1},s_{p_3}-s_{p_2},...,s_{p_k}-s_{p_{k-1}}$$

其中，$p_i$ 是第 $i$ 段的结尾下标，$k$ 是划分出的段数。

因为这个序列构成回文序列，因此我们有：

$$\begin{cases}
s_{p_1}=s_{p_k}-s_{p_{k-1}}\\
s_{p_2}-s_{p_1}=s_{p_{k-1}}-s_{p_{k-2}}\\
...\\
s_{p_{m}}-s_{p_{m-1}} = s_{p_{k-m+1}} - s_{p_{k-m}}
\end{cases}$$

移项，得到以下等式：

$$s_{p_m}+s_{p_{k-m}}=s_{p_{m-1}}+s_{p_{k-m+1}}=...=s_{p_2}+s_{p_{k-2}}=s_{p_1}+s_{p_{k-1}}=s_{p_k}=s_n$$

也就是说，我们选出的序列是回文序列的**充要条件**是：

$$\boxed{s_{p_i}+s_{p_{k-i}}=s_n}$$

因为 $a_i\ge0$，所以 $s$ 单调不减，也就是说，**$s$ 中相同的值均相邻**。

那么我们对 $s$ 的每一段值分别考虑。我们可以发现，$s$ 的每一段值之间互不影响，也就是说，对于 $s$ 中的一种值我们计算且只计算一次答案。

对于一种值 $x$，设 $cnt(x)$ 表示 $x$ 在 $s$ 中的出现次数，那么它对答案的贡献就是：

$$\sum_{i=1}^{cnt(x)}{cnt(x)\choose i}{cnt(s_n-x)\choose i}$$

也就是枚举这种值放几个到回文序列中去，用乘法原理和加法原理组合出结果。这里默认 $cnt(x)\le cnt(s_n-x)$，不满足交换一下就可以了。

然后考虑范德蒙德卷积，也就是：

$$\sum_{i=1}^{cnt(x)}{cnt(x)\choose i}{cnt(s_n-x)\choose i}=\sum_{i=1}^{cnt(x)}{cnt(x)\choose cnt(x)-i}{cnt(s_n-x)\choose i}={cnt(x)+cnt(s_n-x)\choose cnt(x)}$$

（这里其实麻烦了，直接枚举也是可以的，因为 $\sum cnt(x)=n$。是我脑抽了。）

因此，我们可以得出答案的最终表达式为：

$$\prod_{x\in V} {cnt(x)+cnt(s_n-x)\choose cnt(x)}$$

其中，$V$ 表示 $s$ 的值域集合，注意 $x$ 和 $s_n-x$ 只能计算一次。

当 $s_n$ 是偶数时，会出现 $s_{p_i}=s_{p_{k-i}}=\dfrac{1}{2}s_n$ 这样的情况，因此这时需要额外乘上 $2^{cnt(\frac{1}{2}s_n)}$，也就是等于 $\dfrac{1}{2}s_n$ 的数可以随便选的方案数。

### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <map>

using namespace std;
const int N = 200200, L = 200000, mod = 998244353;
#define inf 0x3f3f3f3f
#define int long long

int n, ans = 1, T;
int a[N], sum[N], fac[N], inv[N];

map <int, int> mp;

int q_pow(int a, int b){
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int C(int n, int m){
    if (m > n) return 0;
    return fac[n] * inv[n - m] % mod * inv[m] % mod;  
}

signed main(){
    fac[0] = 1;
    for (int i = 1; i <= L; i ++) fac[i] = fac[i - 1] * i % mod;
    inv[L] = q_pow(fac[L], mod - 2);
    for (int i = L; i >= 1; i --) inv[i - 1] = inv[i] * i % mod;
    scanf("%lld", &T);
    while (T --) {
        mp.clear(); ans = 1;
        scanf("%lld", &n);
        for (int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
        for (int i = 1; i <= n; i ++) sum[i] = sum[i - 1] + a[i];
        for (int i = 1; i < n; i ++) mp[sum[i]] ++;
        int pos = 1;
        while (sum[pos] * 2 < sum[n]) {
            if (sum[pos] != sum[pos + 1]) 
                ans = ans * C(mp[sum[pos]] + mp[sum[n] - sum[pos]], mp[sum[pos]]) % mod;
            pos ++;
        }
        if (sum[n] % 2 == 0) ans = ans * q_pow(2, mp[sum[n] / 2]) % mod;
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：Alex_Wei (赞：5)

求出 $a$ 的前缀和 $pre_i = pre_{i - 1} + a_i$ 和后缀和 $suf_i = suf_{i + 1} + a_{i + 1}$，注意 $suf$ 的定义。

定义在 $i$ 处切分表示分割 $a_i$ 和 $a_{i + 1}$。

因为需要保证 $s$ 回文，所以从两端向中间一刀一刀切。考虑将一种切分方案双射至两个长度为 $k$ 的序列 $p$ 和 $q$，满足 $1\leq p_1 < p_2 < \cdots < p_k \leq q_k < q_{k - 1} < \cdots < q_1 < n$ 且 $pre_{p_i} = suf_{q_i}$。从 $p, q$ 出发，可以构造切分方案为在所有 $p_i$ 和 $q_i$ 处切分。从切分方案也可以构造出 $p, q$，令前 $\lceil \frac n 2 \rceil$ 个切分位置为 $p$，后 $\lceil \frac n 2\rceil$ 个切分位置为 $q$。易知若 $p_k = q_k$，则 $s$ 是偶回文，否则 $s$ 是奇回文。

因为 $a_i \geq 0$，所以 $pre$ 随着 $i$ 增大不减，$suf$ 随着 $i$ 减小不减。因此，对于所有极长的 $[l_l, l_r]$ 和 $[r_l, r_r]$ 表示 $pre_{l_l} = \cdots = pre_{l_r} = suf_{r_l} = \cdots = suf_{r_r}$，它们之间独立。将它们的方案数相乘即得最终方案数，而一对 $[l_l, l_r], [r_l, r_r]$ 的方案数可枚举切分数 $p$ 计算得 $\sum\limits \binom {l_r - l_l + 1} p \binom {r_r - r_l + 1} p$。

注意特判 $[l_l, l_r] = [r_l, r_r]$ 的情况，此时方案数为 $2 ^ {l_r - l_l + 1}$。

时间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1738/submission/174185702)。

---

## 作者：elbissoPtImaerD (赞：3)

# 简述题意
给定一个长度为 $n$ 的自然数序列 $a$，求以下划分方式的方案数：
1. 将整个序列分为连续的若干段。
2. 每一段的和按顺序排起来是一个回文序列。

# 解题报告
区间和自然想到前缀和，结合序列划分不难想到记录划分时的断点。  
我们记录一个序列 $x$，$x_i$ 表示 $a_{x_i}$ 是第 $i-1$ 段的右端点且 $a_{x_i+1}$ 是第 $i$ 段的左端点。  
区间和自然可以用两端点的缀和来表示。

考虑回文的约束条件：我们可以把回文序列从中间劈开，这样左右两边是对称的。  
将断点序列也从中劈开，则前一半的每个断点的前缀和，都会有一个在后一半的断点的后缀和与之对应。

考虑对于前缀和的每一个取值，如果对答案有贡献则必然有一个后缀和与之对应，找出相等取值的两个极大区间 $[l_1,r_1]$ 和 $[l_2,r_2]$，枚举从中能产生几个断点，做加法原理有 $\sum\limits_{m}^{\min\{r_1-l_1+1,r_2-l_2+1\}}\binom{r_1-l_1+1}{m}\binom{r_2-l_2+1}{m}$。

每个前缀和的不同取值之间做乘法原理就是最终答案。

需要注意的是，由于我们断点的定义，所以后缀和应做成 $suf_{i+1}=suf_i+a_{i+1}$ 的形式。

$Code$：

```cpp
il void Solve()
{
	rd(n),pre[0]=suf[n]=0,ans=1;
	for(re int i=1;i<=n;++i) rd(a[i]);
	for(re int i=1;i<=n;++i) pre[i]=pre[i-1]+a[i];
	for(re int i=n-1;~i;--i) suf[i]=suf[i+1]+a[i+1];
	for(re int l=1,r=n-1,x,y,len[2],s;l<=r;)
	{
		for(;pre[l]^suf[r]&&l<=r;)//找到 pre_l = suf_r 的一组值
		{
			if(pre[l]<suf[r])
			{
				++l;
				continue;
			}
			if(pre[l]>suf[r])
			{
				--r;
				continue;
			}
		}
		if(l>r) break;
		if(pre[l]==pre[r])
		{
			(ans*=b[r-l+1])%=p;
			break;
		}
		x=l,y=r,len[0]=len[1]=1,s=0;
		for(;pre[x+1]==pre[l];++x,++len[0]);
		for(;suf[y-1]==suf[r];--y,++len[1]);
     		//找出对应的区间 [l,x],[y,r]
		for(re int i=0;i<=std::min(len[0],len[1]);++i) (s+=C(len[0],i)*C(len[1],i)%p)%=p;
		(ans*=s)%=p,l=x+1,r=y-1;
	}
	prt(ans,'\n');
	return;
}
```

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1738/submission/196352848)

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1738E Balance Addicts](https://www.luogu.com.cn/problem/CF1738E)

# 解题思路

发现我们可以直接枚举左端点 $L$，那么此时显然右端点 $R$ 的取值范围也随之确定，那么此时 $L$ 能往右移当且仅当 $L + 1<R$ 与 $a_{L+1} = 0$，$R$ 能往左移当且仅当 $L<R - 1$ 与 $a_{R-1} = 0$。

那么 $L,R$ 的取值范围确定后，此时会有以下两种情况：

- $L,R$ 的取值范围不相交，此时显然枚举分的段数 $k$ 然后两端组合数部分相乘即可。

- $L,R$ 的取值部分相交，此时直接让两个取值范围一定，然后枚举分的段数 $k$，此时显然 $k$ 为偶数，依然组合数计算即可。

由于双指针，时间复杂度 $O(n)$。

# 参考代码

```cpp
ll n;
ll a[1000010];
ll L,R;
ll pre[1000010],suf[1000010];
ll ans;
ll l,r;
void solve()
{
    ans=1;
    cin>>n;
    forl(i,1,n)
        cin>>a[i];
    forl(i,1,n)
        pre[i]=pre[i-1]+a[i];
    suf[n+1]=0;
    forr(i,n,1)
        suf[i]=suf[i+1]+a[i];
    R=n;
    forL(L,1,n,L<R)
    {
        while(L<R-1 && suf[R]<pre[L])
            R--;
        if(pre[L]==suf[R])
        {
            l=L,r=R;
            while(L<R-1 && suf[R-1]==pre[L])
                R--;
            while(L+1<R && suf[R]==pre[L+1])
                L++;
            ll S=0;
            if(L==R-1 && pre[L]==suf[L+1])
            {
                forll(k,0,r-l+1,2)
                    S=(S+C(r-l+1,k))%mod;
                ans=(ans*S)%mod;
                continue;
            }
            forl(k,0,min(L-l+1,r-R+1))
                S=(S+C(L-l+1,k)*C(r-R+1,k)%mod)%mod;
            ans=(ans*S)%mod;
        }
    }
    cout<<ans<<endl;
}
```

---

## 作者：ifffer_2137 (赞：0)

### 题意
给定一个长度为 $n$ 的序列 $a_i$，求有多少种将它恰好分割为若干个子段的方式，使得分割成的子段分别求和后形成回文串。
### 分析
首先你发现你需要在序列的两边各取一段使得它们和相等。

再接着往里面取，你发现每一对前后分别断开来的点，到前一个的前缀和等于到后一个的后缀和。

于是你可以先对 $a_i$ 做一遍前缀和 $pre_i$ 以及后缀和 $suf_i$。然后 $a_i\ge 0$，所以两个数列都具有单调性，可以 two pointers 线性找出 $pre_i$ 中的相等连续段在 $suf_i$ 中出现在哪一段。不妨将这两段设为 $[l_p,r_p]$ 和 $[l_s,r_s]$。

现在有两种情况，一种是 $r_p<l_s$，一种是 $l_s\leq r_p \leq r_s$。对于前者，我们可以枚举在两侧同时选几个断点，方案数：
$$\sum_{i=0}\dbinom{r_p-l_p+1}{i}\dbinom{r_s-l_s+1}{i}$$
由于所有相等连续段总长 $O(n)$，所以预处理组合数，直接暴力枚举 $i$ 即可做到线性。

对于另一种情况，直接将两段并到一起考虑，在 $[l_p,r_s]$ 中选取偶数个断点，类似暴力枚举组合数求和即可。

所有贡献全部累乘即为总方案数，时间复杂度 $O(n)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define pdd pair<double,double>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1e5+5;
const int mod=998244353;
namespace Comb{
	int fac[maxn],inv[maxn];
	int pw(int a,int x){
		int s=1;
		while(x){
			if(x&1) s=s*a%mod;
			a=a*a%mod;
			x>>=1;
		}
		return s%mod;
	}
	void init(){
		fac[0]=1;
		for(int i=1;i<maxn;i++){
			fac[i]=fac[i-1]*i%mod;
		}
		inv[maxn-1]=pw(fac[maxn-1],mod-2);
		for(int i=maxn-2;i>=0;i--){
			inv[i]=inv[i+1]*(i+1)%mod;
		}
	}
	int C(int n,int m){
		if(n<m) return 0;
		return fac[n]*inv[m]%mod*inv[n-m]%mod;
	}
}
int T;
int n,ans;
int a[maxn];
int pre[maxn],suf[maxn];
signed main(){
	cin.tie(0),cout.tie(0);
	Comb::init();T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++) a[i]=read(),pre[i]=pre[i-1]+a[i];
		suf[n+1]=0; for(int i=n;i>=1;i--) suf[i]=suf[i+1]+a[i];
		ans=1;
		for(int i=1,j=n;i<=n&&i<j;i++){
			while(i<j-1&&suf[j]<pre[i]) j--;
			if(suf[j]==pre[i]){
				int ti=i,tj=j;
				while(i<j-1&&suf[j-1]==suf[j]) j--;
				while(i+1<j&&pre[i+1]==suf[j]) i++;
				int res=0;
				if(i+1==j&&pre[i+1]==suf[j]) for(int k=0;k<=tj-ti+1;k+=2) res=(res+Comb::C(tj-ti+1,k))%mod;
				else for(int k=0;k<=min(i-ti+1,tj-j+1);k++) res=(res+Comb::C(i-ti+1,k)%mod*Comb::C(tj-j+1,k)%mod)%mod;
				ans=ans*res%mod;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

