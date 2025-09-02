# [ARC114C] Sequence Scores

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc114/tasks/arc114_c

$ 1 $ 以上 $ M $ 以下の整数から成る長さ $ N $ の数列 $ A $ に対して， $ f(A) $ を以下のように定義します．

- 長さ $ N $ の数列 $ X $ があり，初め全ての要素は $ 0 $ である．$ f(A) $ を，次の操作を繰り返して $ X $ を $ A $ に等しくするための最小の操作回数とする．
  - $ 1\ \leq\ l\ \leq\ r\ \leq\ N $ と $ 1\ \leq\ v\ \leq\ M $ を指定する．$ l\ \leq\ i\ \leq\ r $ に対して $ X_i $ を $ \max(X_i,\ v) $ で置き換える．

$ A $ として考えられる数列は $ M^N $ 通りあります．これら全ての数列に対する $ f(A) $ の和を $ 998244353 $ で割った余りを求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ M\ \leq\ 5000 $
- 入力は全て整数

### Sample Explanation 1

$ 3\ ^\ 2\ =\ 9 $ 通りの数列と，それに対する $ f $ の値は以下の通りです． - $ A\ =\ (1,\ 1) $ のとき，$ (l\ =\ 1,\ r\ =\ 2,\ v\ =\ 1) $ として $ 1 $ 回の操作で可能なので，$ f(A)\ =\ 1 $ です． - $ A\ =\ (1,\ 2) $ のとき，$ (l\ =\ 1,\ r\ =\ 2,\ v\ =\ 1) $ , $ (l\ =\ 2,\ r\ =\ 2,\ v\ =\ 2) $ として $ 2 $ 回の操作で可能なので，$ f(A)\ =\ 2 $ です． - $ A\ =\ (1,\ 3) $ のとき，$ (l\ =\ 1,\ r\ =\ 2,\ v\ =\ 1) $ , $ (l\ =\ 2,\ r\ =\ 2,\ v\ =\ 3) $ として $ 2 $ 回の操作で可能なので，$ f(A)\ =\ 2 $ です． - $ A\ =\ (2,\ 1) $ のとき，$ (l\ =\ 1,\ r\ =\ 2,\ v\ =\ 1) $ , $ (l\ =\ 1,\ r\ =\ 1,\ v\ =\ 2) $ として $ 2 $ 回の操作で可能なので，$ f(A)\ =\ 2 $ です． - $ A\ =\ (2,\ 2) $ のとき，$ (l\ =\ 1,\ r\ =\ 2,\ v\ =\ 2) $ として $ 1 $ 回の操作で可能なので，$ f(A)\ =\ 1 $ です． - $ A\ =\ (2,\ 3) $ のとき，$ (l\ =\ 1,\ r\ =\ 2,\ v\ =\ 2) $ , $ (l\ =\ 2,\ r\ =\ 2,\ v\ =\ 3) $ として $ 2 $ 回の操作で可能なので，$ f(A)\ =\ 2 $ です． - $ A\ =\ (3,\ 1) $ のとき，$ (l\ =\ 1,\ r\ =\ 2,\ v\ =\ 1) $ , $ (l\ =\ 1,\ r\ =\ 1,\ v\ =\ 3) $ として $ 2 $ 回の操作で可能なので，$ f(A)\ =\ 2 $ です． - $ A\ =\ (3,\ 2) $ のとき，$ (l\ =\ 1,\ r\ =\ 2,\ v\ =\ 2) $ , $ (l\ =\ 1,\ r\ =\ 1,\ v\ =\ 3) $ として $ 2 $ 回の操作で可能なので，$ f(A)\ =\ 2 $ です． - $ A\ =\ (3,\ 3) $ のとき，$ (l\ =\ 1,\ r\ =\ 2,\ v\ =\ 3) $ として $ 1 $ 回の操作で可能なので，$ f(A)\ =\ 1 $ です． これらの和は $ 3\ \times\ 1\ +\ 6\ \times\ 2\ =\ 15 $ です．

## 样例 #1

### 输入

```
2 3```

### 输出

```
15```

## 样例 #2

### 输入

```
3 2```

### 输出

```
15```

## 样例 #3

### 输入

```
34 56```

### 输出

```
649717324```

# 题解

## 作者：小超手123 (赞：8)

### 题意：

有一个长度为 $n$ 的序列 $A$，值域在 $[1,m]$。

记 $f(A)$ 表示一个初始为 $0$ 的序列 $X$ 变成 $A$ 的最小操作数。

定义一次操作 $[l,r,v]$ 为 $X_{i}=\max(X_{i},v)$，其中 $l \le i \le r$。

$n,m \le 5 \times 10^3$。

### 分析：

考虑序列 $A$ 的末尾加上一个数 $x$，记此时在 $A$ 的位置为 $i$。不难发现最小操作数会有以下变化：

- $x$ 在序列 $A$ 中第一次出现，最小操作数 $+1$。
- 对于任意 $a[p]$（ 其中 $p \in [lst_{i}+1,i-1]$）都有 $a_{p} > x$，最小操作数不变。
- 存在一个 $a[p]$（ 其中 $p \in [lst_{i}+1,i-1]$）$a_{p} < x$，最小操作数 $+1$。

其中 $lst_{i}$ 表示 $x$ 在序列 $A$ 中上一个出现的位置。

于是可以记 $f_{i,x}$ 表示在序列 $A$ 的第 $i$ 个位置插入 $x$ 对答案带来的贡献。显然有：
$$
f_{i,x} = m^{i-1}-\sum_{k=1}^{i-1}(m-x)^{i-k-1} \times m^{k-1}
$$
利用前缀和可以快速计算 $f$。

可以记 $G_{i,x}=\sum_{k=1}^{i-1}(m-x)^{i-k-1} \times m^{k-1}$，那么：
$$
G_{i,x} = G_{i-1,x} \times m + (m-x) ^ {i-2}
$$
答案如何算呢？

由于 $f_{i,x}$ 会和先前的所有情况组合算进总答案里，不妨记个 $ans_{i}$。
$$
ans_{i} = \sum_{x=1}^{m} ans_{i-1}+f_{i,x}
$$
答案便是 $ans_{n}$。

时间复杂度 $O(nm \log n)$ 或 $O(nm)$。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 5010
#define mod 998244353
using namespace std;
int n, m;
int G[N][N], h[N], ans[N], z[N][N];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 0; i <= m; i++) {
		z[i][0] = 1;
		for(int j = 1; j <= n; j++) z[i][j] = z[i][j - 1] * i % mod;   
	}
	h[0] = 1;
	for(int i = 1; i <= n; i++) h[i] = h[i - 1] * m % mod;
	for(int i = 2; i <= n; i++)
	for(int j = 1; j <= m; j++) G[i][j] = (G[i - 1][j] * m % mod + z[m - j][i - 2]) % mod;
	for(int i = 1; i <= n; i++) {
		for(int x = 1; x <= m; x++)
			ans[i] = (ans[i] + ans[i - 1] + h[i - 1] - G[i][x] + mod) % mod;
	}
	cout << ans[n];
	return 0;
}
```



---

## 作者：_LiWenX_ (赞：8)

模拟赛中见到了此题，做出了一种很神奇的做法。

我们要处理的是 $\sum\limits_A f(A)$。所以我们当然是从 $f$ 下手。

考虑到一个 $f$ 可能会对应种操作方案（即使都是最小的方案但依然有很多种）。所以我们的第一步是统一操作方案，这样才能方便处理。

不妨这样规定一个形如 $(l,r,k)$ 的操作，它对于序列 $A$ 被执行当且仅当:

- $l=1$ 或 $A_{l-1}<\min\limits_{i=l}^r A_i$
- $r=n$ 或 $A_{r+1}<\min\limits_{i=l}^r A_i$
- $k=\min\limits_{i=l}^r A_i$

为什么要这样做呢，显然对于这样的定义 $(l,r,k)$ 都是极大的，也就是说你不能再在此基础上拓展 $k$ 的值或 $[l,r]$ 的范围。并且我们对于一个序列 $A$，我们有一个确定的方案来操作得到它，而且也是最小的操作步数，符合 $f$ 的定义。

计 $g(l,r,k)$ 为在所有的 $A$ 的操作中，操作 $(l,r,k)$ 被执行的次数。

显然有 $\sum\limits_A f(A)=\sum\limits_{1\le l\le r\le n,1\le k\le m}g(l,r,k)$。

这样的好处就是，我们把求一个抽象函数的值的过程，变为了计数，而计数恰好是我们擅长的事。

虽然 $g$ 有 $O(n^2m)$ 种，但我们还是考虑计算它的值，之后再进行优化。

我们要对 $g$ 分类，因为根据操作 $(l,r,k)$ 的定义，处理边界是十分困难的，而分类方法便是根据 $l,r$ 的定义有关的，分类如下：

- $l=1,r=n$，显然只用使得 $\min\limits_{i=l}^r A_i=k$ 即可。计数方法简单，只要用 $\min\limits_{i=l}^r A_i\ge k$ 的方案减去 $\min\limits_{i=l}^r A_i>k$ 的方案即可，$g(l,r,k)=(m-k+1)^{r-l+1}-(m-k)^{r-l+1}$。

- $l=1,r\not = n$，在满足刚刚情况的条件下，还要满足 $A_{r+1}<k$，那么 $A_{r+1}$ 只有 $k-1$ 种选法，而 $[l,r+1]$ 外的数可以随便选，$g(l,r,k)=(k-1)((m-k+1)^{r-l+1}-(m-k)^{r-l+1})m^{n-r+l-2}$。

- $1\not =1,r=n$，和上一种情况类似，$g(l,r,k)=(k-1)((m-k+1)^{r-l+1}-(m-k)^{r-l+1})m^{n-r+l-2}$。

- $1\not =1,r\not = n$，最一般的情况，但有了刚刚的分析后依旧十分简单，不过是情况 $2$ 与情况 $3$ 合在一起而已，$g(l,r,k)=(k-1)^2((m-k+1)^{r-l+1}-(m-k)^{r-l+1})m^{n-r+l-3}$。

在预处理出所有 $x^y(1\le x\le n,1\le y\le m)$ 后可以 $O(n^2m)$ 计算，这依然不够。

前三种情况加起来也就只有 $O(nm)$ 种，考虑优化最后一种情况，发现这种情况只与 $r-l+1$ 的值有关，枚举这个值即可。

时间复杂度 $O(nm)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int P[5001][5001];
int quickpow(int a,int b){
	if(b<1) return 1;
	return P[a][b];
}
int n,m;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=max(n,m);i++){
		P[i][0]=1;
		for(int j=1;j<=max(n,m);j++){
			P[i][j]=P[i][j-1]*i%mod; 
		}
	}
	int ans=0;
	for(int len=1;len<n;len++){
		for(int k=1;k<=m;k++){
			ans+=(k-1)*(k-1)%mod*(quickpow(m-k+1,len)-quickpow(m-k,len)+mod)%mod*quickpow(m,n-len-2)%mod*(n-len-1)%mod;
			ans%=mod;
		}
	}
	for(int r=1;r<n;r++){
		int l=1;
		for(int k=1;k<=m;k++){
			ans+=(k-1)*(quickpow(m-k+1,r-l+1)-quickpow(m-k,r-l+1)+mod)%mod*quickpow(m,n-r+l-2)%mod;
			ans%=mod;
		}
	}
	for(int l=2;l<=n;l++){
		int r=n;
		for(int k=1;k<=m;k++){
			ans+=(k-1)*(quickpow(m-k+1,r-l+1)-quickpow(m-k,r-l+1)+mod)%mod*quickpow(m,n-r+l-2)%mod;
			ans%=mod;
		}
	}
	for(int k=1;k<=m;k++){
		int l=1,r=n; 
		ans+=(quickpow(m-k+1,r-l+1)-quickpow(m-k,r-l+1)+mod);
		ans%=mod;
	}
	cout<<ans;
}
```

---

## 作者：mklzc (赞：5)

## 题意简述

一个长度为 $N$ 的序列 $A$，$\forall i\in [1,n], A_i\in [1, M]$ 。

定义 $f(A)$ 为：将一个初始全部为 $0$ 的序列 $X$ 变为 $A$ 的最少操作数。

一次操作是指：选择一个区间 $[l,r], 1\le l\le r\le N$ 和一个值 $v,v\in [1,M]$ ，然后用 $\max(X_i, v)$ 替代每个 $X_i, i\in [l,r]$ 。

对于所有 $M^N$ 种序列 $A$，求 $f(A)$ 的和。

## 思路

统计贡献。设 $R(i,v)$ 表示在位置 $i$，值为 $v$ 且该位置为某个操作的左端点所产生的贡献。

正难则反，考虑计算不合法的方案数（即 $i$ 不可能为某个操作的左端点）。可以发现 $i$ 不存在的充要条件为：存在 $j\le i, A_j=A_i$ 且 $j\sim i$ 之间没有比 $v$ 的小的数。 

$R(i,v)=M^{N-1}-\sum\limits_{1\le j\le i-1}{M^{N-i}M^{j-1}(M-v)^{i-j-1}}$

如上等式中，

$M^{N-1}$ 是可能的序列总数；

$M^{N-i}, M^{j-1}$ 是后 $N-i$、前 $j-1$ 个数的值任取；

$(M-v)^{i-j-1}$ 是限制 $j\sim i$ 之间的数大于等于 $v$ 。

每次从 $R(i-1,v)$ 递推求 $R(i,v)$ 即可。

时间复杂度 $O(NM)$

```cpp
#include <bits/stdc++.h>
using LL = long long;
const int Maxn = 5010, mod = 998244353;
int n, m;
LL powm[Maxn], R[Maxn][Maxn];
int main()
{
    scanf("%d %d", &n, &m);
    powm[0] = 1;
    for (int i = 1; i <= n; i++)
        powm[i] = powm[i - 1] * m % mod;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= m; j++)
            R[i][j] = (R[i - 1][j] * (m - j) + powm[i - 2]) % mod;
    LL ans = 0, sav = powm[n - 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans = (ans + sav - R[i][j] * powm[n - i]) % mod;
    printf("%lld\n", (ans % mod + mod) % mod);
    return 0;
}
```

---

## 作者：DengDuck (赞：4)

一个找对方向很重要的题，我就找错方向了。

首先这种题的普遍做法是先探究已知 $A$ 的策略：

- 一种是考虑每次将最大值的区间删掉，然后你可以得到一个 $\mathcal O(n^3)$ 的动态规划做法，不太能优化的样子。
- 一种是考虑建图。

建图？是的，我们发现这题在序列已知的情况下，也可以这么做，对于两个相等的点，中间的点值都比这两个大，那么我们处理的时候肯定可以一次把两个点都染色，所以我们就连边，最后统计连通块即可，这样也显然是对的。

显然，我们只需要与最近的点相连就可以达到联通的效果。

那这题咋做的，我们统计时显然考虑只把连通块最左边的点算贡献，所以我们先假设所有点都有贡献，然后减去一个点在多少中情况下没贡献即可。

所有点有贡献：$n\times m^n$。

$x$ 与前面的点 $y$ 相连：$(\sum\limits_{i=1}^{m}(m-i)^{x-y-1})m^{n-(x-y)-1}$，这里的 $i$ 枚举的是 $x,y$ 是啥，然后其他点可以随便选，记得算上。


然后机甲合体就行了，式子是：

$$
n\times m^n-\sum_{i=1}^n\sum_{j=i+1}^n(\sum\limits_{x=1}^{m}(m-x)^{j-i-1})m^{n-(j-i)-1}
$$

注意到对于同样的 $j-i$ 值总是相等，所以事实上只需要枚举 $j-i$ 和 $x$ 就行了。

时间复杂度为 $\mathcal O(nm)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
const LL N=5005;
//const LL M;
const LL mod=998244353;
//const LF eps;
//const LL P;
LL n,m,ans,pw[N][N];
int main()
{
	scanf("%lld%lld",&n,&m);
	pw[0][0]=1;
	for (LL i = 1; i <= m; i++)
	{
		pw[i][0] = 1;
		for (LL j = 1; j <= n; j++) pw[i][j] = pw[i][j - 1] * i % mod;
	}
	ans=n*pw[m][n]%mod;
	for(int i=1;i<=n-1;i++)
	{
		LL t=n-i,cnt=0;
		for(int j=1;j<=m;j++)cnt=(cnt+pw[m-j][i-1])%mod;
		ans=(ans-t*cnt%mod*pw[m][n-i-1]%mod+mod)%mod;
		//cout<<t<<' '<<cnt<<' '<<endl;
	}
	printf("%lld",ans);
	return 0;
}
//RP++
```

---

## 作者：违规用户名1425622 (赞：2)

### 1. 前言

你谷新人第二篇题解qwq。

### 2. 做法

根据其他题解可得 ~~（其实是因为我懒得再打一遍了）~~，答案显然，推一下柿子得：

$$
\sum_{i=1}^n \sum_{j=1}^m m^{n-i}(m^{i-1}-\sum_{k=1}^{i-1}m^{k-1}(m-j)^{i-k-1}) \\

=nm^n- \sum_{i=1}^n \sum_{j=1}^m \sum_{k=1}^{i-1} m^{n-i+k-1} (m-j)^{i-k-1} \\

=nm^n- \sum_{i=1}^n \sum_{k=1}^{i-1} m^{n-i+k-1} \sum_{j=0}^{m-1} j^{i-k-1} \\

=nm^n- \sum_{i=1}^{n-1} (n-i) m^{n-i+1} \sum_{j=0}^{m-1}j^{i-1} \\

=nm^n- m^{n-2} \sum_{j=0}^{m-1} \sum_{i=1}^{n-1} (\frac{j}{m})^{i-1} (n-i)
$$

直接做就可以 $O(nm)$ 了，但是其实可以再推一下。

设 $p=\frac{j}{m}$。

$$
\sum_{i=1}^{n-1} p^{i-1}(n-i) \\

=\sum_{i=1}^{n-1} p^{i-1} \sum_{j=1}^{n-i} 1 \\

=\sum_{j=1}^{n-1} \sum_{i=0}^{n-j-1} p^i \\

=\sum_{j=1}^{n-1} \frac{p^{n-j}-1}{p-1} \\

=\frac{\sum\limits_{j=1}^{n-1} p^j-(n-1)}{p-1} \\

=\frac{\frac{p^n-p}{p-1}-(n-1)}{p-1}
$$

那么我们就得到了 $O(n\log n)$ 的做法。

扔个代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define mod 998244353
int n,m;
int qmi(int a,int b=mod-2)
{
	int ans=1;
	while(b){
		if(b&1)ans=(LL)ans*a%mod;
		a=(LL)a*a%mod,b>>=1;
	}return ans;
}
int main()
{
	int i,ans=0;
	cin>>n>>m;
	if(n==1)return cout<<m,0;
	int t=qmi(m);
	for(i=0;i<m;i++){
		int x=(LL)i*t%mod,s=qmi(x+mod-1);
		ans=(ans+(LL)s*((LL)(qmi(x,n)+mod-x)*s%mod+mod-n+1))%mod;
	}
	ans=((LL)m*m%mod*n+mod-ans)%mod;
	cout<<(LL)ans*qmi(m,n-2)%mod;
}
```

可不可以做到 $O(n)$ 呢，答案是肯定的。

我们发现要在 $O(n)$ 复杂度内解决这个问题只需要快速求出 $(\frac{k}{m})^n$ 和 $(\frac{k}{m} -1)^{-1}$ 即可。

然后就不出意外的抢了 Atcoder 的最优解。

---

## 作者：kiritokazuto (赞：2)

# 简述题意
- 给你两个长为 $n$ 的可重数列，一个叫 $A$，另一个叫 $X$，$A$ 中的元素取值范围为 $1 \sim m$，$X$中的元素初始值都是 $0$。
- 每次你可以选择 $X$ 中的 $[l, r]$ 区间，让他和 $v$ 取 $max$，将这段区间里的数都变成这个最大值。
- 设 $X$ 最少经过 $f(A)$ 次操作可以变成 $A$，问对于所有的 $m ^ n$ 种 $A$ 的 $f(A)$ 之和。

# 思路
- 将问题转化成给 $A$ 里填数。
- 考虑每新来一个数 $p$ 对我 $f(A)$ 的影响。
	- $p$ 没有出现过，那么我的 $f(A)$ 应加一。
	- $p$ 出现过，记录之前出现的位置为 $lst$，那么如果对于 $\forall k \in [lst, i], val_k \ge p$，显然我可以通过对 $lst$ 操作来达到让这里变成 $p$ 的目的(因为中间的数不会被影响，区间取 $max$)，操作数不用加，反之则需要加一。
    
# 推式子

- 考虑如何求出每一个 $f(A)$，因为我们知道什么情况下是不需要加一的，所以直接用总情况数减去不需要加一的情况就行了。记 $g(i, x)$ 表示在 $i$ 的位置增加一个数 $x$ 的操作数。
$$ g(i, x) = m ^ {i - 1} - \sum\limits_{k = 1}^{i - 1} (m - x) ^ {i - k - 1} \cdot m ^ {k - 1}$$
- 其中 $k$ 枚举的是上一个 $x$ 出现的位置，$(m - x)$ 表示所有比 $x$ 大的数，他们可以在 $[k + 1, i - 1]$ 任意分布，对于其他的 $k - 1$ 个位置随便放就行了。

- 这里有一个细节，对于每一个 $x$ 这个式子是可以递推的，首先对于 $i$ 每增大 $1$ 我 $(m - x)$ 的次方就多一，所以应该先乘上 $(m - x)$ 其次我们可以把乘 $m ^ {k - 1}$ 单独拿出来，因为对于增大的 $i$ 上一个和式和现在的和式之间只差一个 $m ^ {k - 1}$ (抛去次方的变化来看)。

- 最后统计答案就只需要：
$$ans_i = \sum\limits_{x = 1} ^ {m} ans_{i - 1} + g(i, x)$$

# Code


```cpp
#include <bits/stdc++.h>
#define Re register int
#define LL long long
#define fr(x, y, z) for(Re x = y; x <= z; x ++)
#define fp(x, y, z) for(Re x = y; x >= z; x --)
#define fuc(x, y) inline x y
#define WMX aiaiaiai~~
using namespace std;
namespace kiritokazuto {
	fuc(char, getc)(){
		static char buf[1 << 18], *p1, *p2;
		if(p1 == p2){
			p1 = buf, p2 = buf + fread(buf, 1, 1 << 18, stdin);
			if(p1 == p2)return EOF;
		}
		return *p1++;
	}
	fuc(LL, read)() {
		LL x = 0, f = 1;char c = getc();
		while(!isdigit(c)){if(c == '-')f = -1; c = getc();}
		while(isdigit(c)){x = (x << 1) + (x << 3) + (c ^ 48); c = getc();}
		return x * f;
	}
	template <typename T> fuc(void, write)(T x){
		if(x < 0)putchar('-'), x = -x;
		if(x > 9)write(x / 10);putchar(x % 10 | '0');
	}
} 
using namespace kiritokazuto;
const int maxn = 1e5 + 1000, Inf = 2147483647, Mod = 998244353, lim = 2e5 ;
LL sum[5010];
LL lst, ans;
LL pows[5010];
int n, m;
signed main() {	
	n = read(), m = read();
	pows[0]  = 1;
	int lim = max(n, m);
	fr(i, 1, lim)pows[i] = pows[i - 1] * m % Mod, sum[i] = 1;
	lst = m;
	ans = 0;
	fr(j, 1, m)ans = (ans + (lst + (pows[1] - sum[j] + Mod) % Mod) % Mod) % Mod;
	fr(i, 3, n) {
		lst = ans, ans = 0;
		fr(j, 1, m)sum[j] = (sum[j] * (m - j) % Mod + pows[i - 2]) % Mod;
		fr(j, 1, m)ans = (ans + (lst + (pows[i - 1] - sum[j] + Mod) % Mod) % Mod) % Mod;
	}
	write(ans);
	return 0;
}

```

---

## 作者：shinkuu (赞：1)

提供一个更臭一点的 $O(n)$ 做法。

首先分析，如果现在已知 $A$，怎么求 $f(A)$。首先贪心地想，设依次操作 $v_i$，若 $v_{i+1}<v_i$，那么换成先操作 $v_i$ 再 $v_{i+1}$ 一定不劣，因为可能的结果后者包含前者。于是一定是按 $v$ 从小到大操作。

然后发现，对于一个 $a_i=a_j=x$，若 $\exists k\in(i,j),a_k<x$，则无法用一次操作同时使 $a_i,a_j$ 满足要求，否则会影响中间已经确定的数。同时，若 $a_i$ 这个数是第一次出现，显然也要一次操作。

然后拆开算贡献。对于第一种情况，考虑枚举 $a_i=k$ 上一次出现的位置为 $j$，则 $(i,j,k)$ 产生贡献的要求有：$(i,j)$ 中没有 $k$ 且 $\exists p\in(i,j),a_p<k$。计算方案数，考虑算没有 $k$ 的方案减去全 $>k$ 的方案，为 $((m-1)^{i-j-1}-(m-k)^{i-j-1})m^{n-i+j-1}$，后面的 $m$ 是其他位置任取的方案数。于是方案数为：

$$\sum\limits_{i=1}^n\sum\limits_{k=1}^m\sum\limits_{j=1}^{i-1}((m-1)^{i-j-1}-(m-k)^{i-j-1})m^{(n-(i-j+1))}$$

然后推式子。发现只和 $i-j$ 有关：

$$=\sum\limits_{i=1}^{n-1}\sum\limits_{k=1}^m((m-1)^{i-1}-(m-k)^{i-1})(n-i)m^{n-i-1}$$

改变枚举顺序。

$$=\sum\limits_{k=1}^m\sum\limits_{i=1}^{n-1}((m-1)^{i-1}(n-i)m^{n-i-1}-(m-k)^{i-1}(n-i)m^{n-i-1})$$

对于 $x^iy^{n-i}$ 状物，有个 trick 是提出来 $y^n$ 变成 $y^n(\frac xy)^i$。

$$=m^{n-2}\sum\limits_{k=1}^m\sum\limits_{i=1}^{n-1}((\frac{m-1}{m})^{i-1}(n-i)-(\frac{m-k}{m})^{i-1}(n-i))$$

$$=m^{n-2}(n\sum\limits_{k=1}^m\sum\limits_{i=1}^{n-1}((\frac{m-1}{m})^{i-1}-(\frac{m-k}{m})^{i-1})-\sum\limits_{k=1}^m\sum\limits_{i=1}^{n-1}(i(\frac{m-1}{m})^{i-1}-i(\frac{m-k}{m})^{i-1}))$$

发现前半部分是等比数列形式，可以 $O(1)$ 算。后半形似 $\sum (i+1)x^i$，对于这种的处理，令 $A=\sum\limits_{i=0}^n (i+1)x^i,xA=\sum\limits_{i=1}^{n+1} ix^i$，相减得 $(x-1)A=(n+1)x^{n+1}-\sum\limits_{i=0}^nx^i$，结合等比数列也是 $O(1)$。

于是 令 $f(x,n)=\sum\limits_{i=0}^nx^i=\frac{x^{n+1}-1}{x-1},g(x,n)=\sum\limits_{i=0}^{n}(i+1)x^i=\frac{(n+1)x^{n+1}-f(x,n)}{x-1}$，则有：

$$=m^{n-2}(n\sum\limits_{k=1}^m(f(\frac{m-1}{m},n-2)-f(\frac{m-k}{m},n-2))-\sum\limits_{k=1}^m(g(\frac{m-1}{m},n-2)-g(\frac{m-k}{m},m-2)))$$

此时 $O(n\log n)$ 已经是简单的，至于 $O(n)$，容易发现需要快速幂的只有 $x^{n-1}$，线性筛预处理，再预处理一些逆元即可。

后面部分的式子比较简单，为 $\sum\limits_{i=1}^n\sum\limits_{k=1}^m(m-1)^{i-1}m^{n-i}$。容易发现与 $k$ 无关，于是动态维护后面两个东西即可。

code：

```cpp
int n,m,s,pm[N],pw[N],inv[N];
int ivm,ivmp;
bool vis[N];
il int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
il int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1){
			ret=1ll*ret*x%mod;
		}
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
il int F(int x){
	return mod-1ll*Mod(1ll*pw[x]*ivmp%mod,mod-1)*m%mod*inv[m-x]%mod;
}
il int G(int x){
	return mod-1ll*Mod(1ll*(n-1)*pw[x]%mod*ivmp%mod,mod-F(x))*m%mod*inv[m-x]%mod;
}
void Yorushika(){
	read(n,m);
	if(n==1){
		printf("%d\n",m);
		return;
	}
	pw[1]=inv[1]=1;
	rep(i,2,m){
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
		if(!vis[i]){
			pm[++s]=i;
			pw[i]=qpow(i,n-1);
		}
		rep(j,1,s){
			if(pm[j]>m/i){
				break;
			}
			vis[i*pm[j]]=1;
			pw[i*pm[j]]=1ll*pw[i]*pw[pm[j]]%mod;
			if(i%pm[j]==0){
				break;
			}
		}
	}
	ivm=qpow(m,mod-2),ivmp=qpow(ivm,n-1);
	int ans=0;
	rep(k,1,m){
		ans=Mod(ans,1ll*n*Mod(F(m-1),mod-F(m-k))%mod);
		ans=Mod(ans,mod-Mod(G(m-1),mod-G(m-k)));
	}
	ans=1ll*ans*qpow(m,n-2)%mod;
	int x=1,y=qpow(m,n-1);
	rep(i,1,n){
		ans=Mod(ans,1ll*x*y%mod*m%mod);
		x=1ll*x*(m-1)%mod,y=1ll*y*inv[m]%mod;
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

吐槽一下，这种题明明可以出到 $n=10^7$ 结果偏偏出了 $n=5000$，直接变成了zz题了……

---

## 作者：流水行船CCD (赞：1)

这题定大致方向很重要，如果按值从小到大的顺序去 DP（类似连续段 DP），根本优化不了。

这种每个元素贡献独立的题，肯定要拆开算贡献。若一个元素 $a_i$ 不能和它的前驱通过一次操作赋值或它没有前驱，$a_i$ 就会产生 $1$ 的贡献。

而 $a_i$ 能和它的前驱通过一次操作赋值，设 $a_i$ 的前驱为 $j$，当且仅当 $\forall k \in (j,i), a_k > a_i$，此时合法序列有 $m^{j-1+n-i}(m-a_i)^{i-j-1}$ 个，简单容斥一下就可以得到答案式子，下面给出推导。

$$\begin{aligned}
令 F(x) = \sum_{i=1}^{m} (m-i)^x
\\
Ans&=\sum_{i=1}^{n}\sum_{j=1}^{m}m^{n-1}-\sum_{k=1}^{i-1}m^{k-1+n-i}(m-j)^{i-k-1}
\\
&=nm^n-\sum_{i=1}^{n}\sum_{j=1}^{m}\sum_{k=1}^{i-1}m^{k-1+n-i}(m-j)^{i-k-1}
\\
&=nm^n-\sum_{i=1}^{n}\sum_{k=1}^{i-1}m^{k-1+n-i}\sum_{j=1}^{m}(m-j)^{i-k-1}
\\
&=nm^n-\sum_{i=1}^{n}\sum_{k=1}^{i-1}m^{k-1+n-i}F(i-k-1)
\\
&=nm^n-n\sum_{len=i-k+1=2}^{n}m^{n-len}F(len-2)
\end{aligned}$$

$O(n \log n)$ 递推即可。

code 太丑了，就不放了。

---

## 作者：cpchenpi (赞：1)

[官解](https://atcoder.jp/contests/arc114/editorial/918)已经告诉我们，答案是这样的一个式子：（具体思路及推导参考官解，这里不在赘述）
$$
N \times M^N - \sum_{i=1}^{N} \sum_{j=i+1} ^{N} (\sum_{x=1}^{M}(M-x)^{j-i-1}) \times M^{N-(j-i)-1}
$$
官解注意到内部的求和 $j-i$ 和 $x$ 有关，因此可以在 $O(NM)$ 的时间内求出答案。但其实还可以有更快的做法，交换顺序把 $x$ 作为求和的主元，那么求和项 $\sum_{i=1}^{N} \sum_{j=i+1} ^{N} (M-x)^{j-i-1} M^{N-(j-i)-1}$ 是有简洁的表达式的（我不会推这个式子，但是 [Wolfram|Alpha](https://www.wolframalpha.com/input?i2d=true&i=Sum%5BSum%5BPower%5Bm-x%2Cj-i-1%5DPower%5Bm%2Cn-%5C%2840%29j-i%2B1%5C%2841%29%5D%2C%7Bj%2Ci%2B1%2Cn%7D%5D%2C%7Bi%2C1%2Cn%7D%5D) 可以告诉我们）：
$$
\dfrac{-M^{N+1}+NxM^N+M(M-x)^N}{Mx^2}
$$

直接使用快速幂，就可以在 $O(m\log n)$ 的时间内求出答案。由于 $x$ 的取值范围固定，也可以预处理后线性时间内求得答案。

参考代码（使用 [ac-library](https://atcoder.github.io/ac-library/production/document_en/)）：
``` C++
#include <atcoder/modint>
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
using Z = atcoder::modint998244353;

void solve() {
    int n, m;
    cin >> n >> m;
    if (m == 1) {
        cout << 1 << "\n";
        return;
    }
    Z ans = n * Z(m).pow(n);
    for (int x = 1; x <= m; x++) {
        ans -= (n * x * Z(m).pow(n) - Z(m).pow(n + 1) + m * Z(m - x).pow(n)) /
               m / x / x;
    }
    cout << ans.val() << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}

```

---

## 作者：Enoch006 (赞：0)

这题找对方向非常重要，想歪了就不容易做出来了，悼念我被硬控的五个小时。

考虑将一个序列的贡献**分到每一个下标**身上，于是我们来看贡献的变化量，设上一个等于 $x$ 的下标为 $lst$。

- 若 $(lst,i)$ 中的数全部大于 $x$，那么贡献不变。
- 若 $(lst,i)$ 中有数小于 $x$ 或之前没有相同的数，那么贡献加一。

现在对于每个下标看贡献，假设在下标 $i$ 填 $j$，那么他在所有序列中的贡献是：

$$m^{n-i}((m-1)^{i-1}+\sum_{lst=1}^{i-1}m^{lst-1}((m-1)^{i-lst-1}-(m-j)^{i-lst-1})))$$

因此答案为:

$$
\begin{aligned}
& \sum_{i=1}^{n}\sum_{j=1}^{m}m^{n-i}(m-1)^{i-1}+\sum_{lst=1}^{i-1}m^{n-(i-lst)-1}((m-1)^{i-lst-1}-(m-j)^{i-lst-1})\\
= & \sum_{i=1}^{n}\sum_{j=1}^{m}m^{n-i}(m-1)^{i-1}+\sum_{k=1}^{i-1}m^{n-k-1}((m-1)^{k-1}-(m-j)^{k-1})\\
= & \sum_{i=1}^{n}\left(m^{n-i+1}(m-1)^{i-1}+\sum_{k=1}^{i-1}m^{n-k}(m-1)^{k-1}-\sum_{j=1}^{m}\sum_{k=1}^{i-1}m^{n-k-1}(m-j)^{k-1}\right)\\
= & \sum_{i=1}^{n}\left(m^{n-i+1}(m-1)^{i-1}+\sum_{k=1}^{i-1}m^{n-k}(m-1)^{k-1}-\sum_{k=1}^{i-1}m^{n-k-1}\sum_{j=0}^{m-1}j^{k-1}\right)\\
\end{aligned}
$$

化简式子时需要换元，最后 $\sum_{j=0}^{m-1}j^{k-1}$，我们 $\mathcal{O}(n^2)$ 预处理 $d_{k-1}$ 就行了。

---

## 作者：_luanyi_ (赞：0)

集训统一 VP ARC 时遇到了这道题，发现我的做法还没有出现过，故写一篇题解~~纪念一道 ARC 的 C 调了一个小时~~。

首先我们要探究怎么对 $A$ 操作才能使方案数最小。通过手模可以发现，如果存在一段区间 $[l,r]$ 满足：

- $\min\limits_{i=l}^rA_i=x$；
- $l=1$ 或者 $a_{l-1}<x$；
- $r=n$ 或者 $a_{r+1}<x$；

则需要进行一次操作 $(l,r,x)$。

不难发现，这样操作正确性显然，最优性看起来就很对，因为这样可以把一个极长的 $\geqslant x$ 的段拆成若干个 $>x$ 的段，相当于把这一段的所有 $x$ 全部处理完了。

因此，我们可以枚举操作 $(l,r,x)$，再计算这个操作在所有 $M^N$ 的序列中会出现几次。

注意到这个操作若会被进行则上述三个条件一定会被满足，则可以用上述条件计算操作 $(l,r,x)$ 的出现次数。

枚举 $[l,r]$ 中最小的 $i$ 使得 $A_i=x$，则第一个条件可以转化为 $\forall j\in[l,i),a_j>x$ 以及 $\forall j\in(i,r],a_j\geqslant x$。

因此 $(l,r,x)$ 出现次数为 $m^{n-(r-l+1)-2}(x-1)^{[l\neq1]+[r\neq n]}\sum\limits_{i=l}^r(m-x)^{i-l}(m-x+1)^{r-i}$。

注意当 $r-l+1\geqslant n-1$ 时可能会出现一些问题，需要特判。

这样直接计算的复杂度是四次方的，过不了，考虑优化。

注意到区间长度相等的 $(l,r,x)$ 操作计算过程是相似的，可以一起算，这样就只需要枚举长度 $len$ 了。

同时我们观察枚举 $i$ 的部分，发现 $\sum\limits_{i=l}^r(m-x)^{i-l}(m-x+1)^{r-i}=\sum\limits_{i=1}^{len}(m-x)^{i-1}(m-x+1)^{len-i}=(m-x+1)^{len-1}\sum\limits_{i=0}^{len-1}(\frac{m-x}{m-x+1})^i$，是等比数列求和的形式，可以公式优化成 $O(1)$。

至此，复杂度已优化至平方级别，实现精细一些、注意少求逆元就可以通过。

```cpp
#define fq(i,a,b) for (int i = (a); i <= (b); i++)
#define elif else if
const int p = 998244353;
const int maxn = 5050;
int sum;
int n, m;
int po[maxn][maxn]; // po[i][j] = i**j
int qo[maxn], oq[maxn]; // qo[x] = (m - x) / (m - x + 1), oq[x] = 1 / (qo[x] - 1)
signed main () {
	cin >> n >> m;
	po[0][0] = 1;
	fq (i, 1, m) {
		po[i][0] = 1;
		fq (j, 1, n) po[i][j] = 1ll * po[i][j - 1] * i % p;
	}
	fq (x, 1, m) {
		qo[x] = 1ll * (m - x) * power (m - x + 1, p - 2, p) % p;
		oq[x] = power (qo[x] - 1, p - 2, p);
	}
	fq (x, 1, m) {
		int mulq = 1;
		fq (len, 1, n) {
			int val = 0;
			if (len <= n - 2)
				val = (1ll * (n - len - 1) * po[m][n - len - 2] % p * po[x - 1][2]
				+ 2ll * po[m][n - len - 1] % p * (x - 1)) % p;
			elif (len == n - 1) val = 2ll * po[m][n - len - 1] % p * (x - 1) % p;
			else val = 1;
			
			int vv = po[m - x + 1][len - 1];
			int k = qo[x];
			mulq = 1ll * mulq * k % p;
			vv = 1ll * (mulq - 1) * oq[x] % p * vv % p;
			
			sum = (sum + 1ll * val * vv) % p;
		}
	} cout << sum << endl;
	return 0;
}
```

---

## 作者：Miraik (赞：0)

我是暴力老哥，不会高妙简洁推法 /ll

先考虑一下我们的操作过程应该长什么样。

显然我们会按 $v$ 从小到大操作，这样一定是不劣的。

进一步的，我们对于 $x$ 的相邻出现位置，即 $a_i=a_j=x(i<j)$ 且 $\forall k \in [i+1,j-1] \space a_k \neq x$，如果 $\min\{a_i,\cdots,a_j\}<x$，则 $a_i,a_j$ 必须分两次操作赋值，对答案有 $1$ 的贡献。

记一个序列所有相邻出现位置统计得到的贡献为 $cnt_A$，所有数字的种类数为 $cnt_B$，那么答案即为 $cnt_A+cnt_B$。

$cnt_B$ 不难算，直接 dp（设 $f_{i,j}$ 表示序列长度为 $i$，有 $j$ 种不同数字的方案数） 或者容斥都不难做到 $O(nm)$。接下来考虑计数 $cnt_A$。

然后来设计一个暴力计数的方法：枚举左右端点 $L,R$ 以及值 $a_L=a_R=x$，我需要在中间放至少一个 $<x$ 的数以及若干 $>x$ 的数（注意不能 $=x$，因为我需要保证 $\forall k \in [L+1,R-1] \space a_k \neq x$），其他位置我们并不关心。容斥即可做到 $O(n^3m)$，推出来式子即：

$cnt_A=\sum_{L=1}^n \sum_{R=L+1}^n \sum_{x=1}^m \sum_{i=1}^{R-L-1} (-1)^{i-1} \times {R-L-1 \choose i} \times (x-1)^i \times (m-1)^{R-L-1-i} \times m^{n-(R-L+1)}$

其中 $i$ 为钦定 $<x$ 的数个数。

考虑优化这个式子，首先我们发现枚举 $L,R$ 的具体位置意义是不大的，在计算后面的式子时我们只关心 $R-L-1$ 的值。这样前面改成枚举 $len=R-L-1$，算出来的贡献再乘上 $n-len-1$（即对应左端点 $L$ 的取值个数），这样就是 $O(n^2m)$ 的了。

$\sum_{len=1}^{n-2} \sum_{i=1}^{len} \sum_{x=1}^m (-1)^{i-1} \times {len \choose i} \times (x-1)^i \times (m-1)^{len-i} \times m^{n-len-2}$

然后我们又发现式子里与 $x$ 唯一相关的项即为 $(x-1)^i$，那么对于相同的 $i$ 这个式子的总系数就是 $\sum_{x=1}^{m-1} x^i$，预处理一下即可去掉枚举 $x$ 的过程，总复杂度降至 $O(nm+n^2)$，可以通过本题。

我偷懒直接用了快速幂计算，复杂度为 $O(n^2 \log n)$，1995ms 极限通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
const int mod=998244353;
inline int read(){
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x*f;
}
int n,m,f[N][N],fac[N],ifac[N],sumpw[N],ans;
inline int qpow(int x,int y){
	int r=1;
	while(y){
		if(y&1) r=1ll*r*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return r;
}
inline int C(int n,int m){
	if(n<m || n<0) return 0;
	return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
inline void Init(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
	ifac[n]=qpow(fac[n],mod-2);
	for(int i=n-1;~i;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
int main(){
	n=read(),m=read(); Init(max(n,m)); f[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=min(i,m);j++)
			f[i][j]=(1ll*f[i-1][j]*j+f[i-1][j-1])%mod;
	for(int i=1;i<=min(n,m);i++) (ans+=1ll*C(m,i)%mod*fac[i]%mod*f[n][i]%mod*i%mod)%=mod;
	for(int i=1;i<=n;i++)
		for(int val=2;val<=m;val++)
			(sumpw[i]+=qpow(val-1,i))%=mod;
	for(int len=1;len<=n-2;len++){
		int ff=0;
		for(int i=1;i<=len;i++){
			int rr=1ll*C(len,i)*sumpw[i]%mod*qpow(m-1,len-i)%mod*qpow(m,n-2-len)%mod;
			if(i&1) (ff+=rr)%=mod;
			else (ff+=mod-rr)%=mod;
		}
		(ans+=1ll*(n-len-1)*ff%mod)%=mod;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

