# [ABC172E] NEQ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc172/tasks/abc172_e

$ 1 $ 以上 $ M $ 以下の整数からなる長さ $ N $ の数列 $ A_1,A_2,\cdots,\ A_{N} $ と $ B_1,B_2,\cdots,\ B_{N} $ の組であって、以下の条件をすべて満たすものの個数を求めてください。

- $ 1\leq\ i\leq\ N $ なる任意の $ i $ について $ A_i\ \neq\ B_i $
- $ 1\leq\ i\ <\ j\leq\ N $ なる任意の $ (i,j) $ について $ A_i\ \neq\ A_j $ かつ $ B_i\ \neq\ B_j $

ただし、答えは非常に大きくなる可能性があるので、$ (10^9+7) $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ M\ \leq\ 5\times10^5 $
- 入力はすべて整数

### Sample Explanation 1

$ A_1=1,A_2=2,B_1=2,B_2=1 $ のときと $ A_1=2,A_2=1,B_1=1,B_2=2 $ のとき条件が満たされます。

## 样例 #1

### 输入

```
2 2```

### 输出

```
2```

## 样例 #2

### 输入

```
2 3```

### 输出

```
18```

## 样例 #3

### 输入

```
141421 356237```

### 输出

```
881613484```

# 题解

## 作者：UKE_Automation (赞：8)

## [ABC172E] NEQ 题解

### Problem

求出满足以下要求的序列 $A,B$ 个数，对 $10^9+7$ 取模：

1. 长度为 $N$；
2. 每个元素的范围是 $[1,M]$；
3. 每个位置上 $A,B$ 不相等；
4. $A,B$ 中元素互不相同。

### Solution

我们先考虑基本的错排问题：

错排问题指的是有 $n$ 个元素，若一个序列的所有数都不在他原来的位置上，就说这是原序列的一个错排。

这是一个递推问题。将 $n$ 个数的错排个数记作 $D(n)$，然后分步分类讨论。

第一步，考虑放下第 $n$ 个元素，则有 $n-1$ 种方法。设当前放下的位置是 $k$。

第二步，考虑放下第 $k$ 个元素，有两种情况：

1. 将它放在 $n$ 位置，此时剩下的 $n-1$ 个元素有 $D(n-2)$ 种方法。
2. 将它不放在 $n$ 位置，这时对于除 $n$ 外的 $n-1$ 个元素有 $D(n-1)$ 种方法。

综上，$D(n)=(n-1)\times(D(n-2)+D(n-1))$。

边界为 $D(0)=1,D(1)=0$，注意在这里我们人为定义 $0$ 个元素的错排有一种情况。

接下来，这道题目与错排十分相似，我们借鉴上面的做法。

首先，确定序列 $A$ 的个数，显然应该是 $A_M^N$。

接下来我们考虑对于一个固定的 $A$，如何求出合法的 $B$。

我们继续沿用 $D(n)$ 的定义。不考虑多余元素的情况下，公式仍然是 $D(n)=(n-1)\times(D(n-2)+D(n-1))$。

然而，由于我们此时的选数范围不只局限在 $[1,N]$，而是扩大到了 $[1,M]$。所以我们再次看一下放置第 $n$ 个元素的方案。

在放入第 $n$ 个元素时，我们可以选 $A$ 数列中没有出现的元素（如果这个元素被当前元素之前的元素选过了，那我们就选这个元素本身对应的 $A$ 数列的元素，其效果是相同的），总共 $(M-N)$ 个。（题目保证了 $N\le M$，所以是对的）

所以再根据加法原理，答案应该是 $D(n)=(M-N)\times D(n-1)+(n-1)\times(D(n-2)+D(n-1))$，注意这里区分是题目中给出的大 $N,M$ 和枚举时的小 $n$。

递推求解即可，此时边界条件是 $D(0)=1,D(1)=M-N$。

最后结果就是 $A_M^N\times D(N)$。

### Code

注意 `long long`。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

typedef long long LL;
const int Maxn = 2e6 + 5;
const int Mod = 1e9 + 7;

int n, m;
int d[Maxn];
int ans;

int A(int n, int m) {
	int res = 1;
	for(int i = n; i >= n - m + 1; i--) {
		res = (res * i) % Mod;
	}
	return res;
}

signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> m;
	d[0] = 1, d[1] = m - n;
	ans = A(m, n);
	for(int i = 2; i <= n; i++) {
		d[i] = ((m - n) * d[i - 1] % Mod + (i - 1) * (d[i - 2] + d[i - 1]) % Mod) % Mod;
	} 
	ans = (ans * d[n]) % Mod;
	cout << ans; 
	return 0;
}
```

---

## 作者：刘辰雨 (赞：5)

# 修改日志：

一审：不通过。`原因是 「公式/英文/数字/汉字」与中文标点符号之间不应添加多余空格；审核管理员：Wilson_Inversion，对审核结果有疑问请私信交流。`

一次修改：删除`「公式/英文/数字/汉字」与中文标点符号之间`的多余空格。

二审：不通过。`原因是 「公式/英文/数字/汉字」与中文标点符号之间不应添加多余空格；审核管理员：Wilson_Inversion，对审核结果有疑问请私信交流。`

二次修改：删除`「公式/英文/数字/汉字」与中文标点符号之间`的多余空格。

三审：不通过。`原因是 滥用标题（「没错，这就是答案了！」等应使用加粗而非三级标题）；排列记号的解释中有错误（「表示从 k_2 个元素中选择 k_2 个元素」）；建议统一使用括号或不使用括号（「它表示从 (m-k) 个数中找出 n-k 个不同的数」）；建议列表中的每一项末尾有句号或分号（题目描述中的三个条件）；审核管理员：Rainy_chen，对审核结果有疑问请私信交流。 。`

三次修改：修改`滥用标题`部分；更改`排列记号的解释中`的错误；对于`统一使用括号或不使用括号`，统一使用括号；对`题目描述中的三个条件`添加中文分号和中文句号。

---
被这题考场 $\text{AK}$ 了，教练请了数学竞赛老师来讲，赛后一遍 $\text{AC}$ 了，于是写篇题解纪念一下。

[更好的观看体验](https://xjcwliucy.github.io/2023/04/25/abc-172-e/)

# 前置芝士：

**请确保您掌握集合的基础知识。**

定义 $|A|$ 表示集合 $A$ 的大小，$|B|$ 表示集合 $B$ 的大小，以此类推。
则有：
$$|A\cup B|=|A|+|B|-|A\cap B|$$ 
如果您感到困难，画个图理解一下。我们继续：
$$|A\cup B\cup C|=(|A|+|B|+|C|)-(|A\cap B|+|B\cap C|+|A\cap C|)+(|A\cap B\cap C|)$$ 
这次更建议您画图理解。接下来经过**科学论证法**，我们可以获得**推广公式**：
$$|A_1\cup A_2\cup \dots \cup A_n|=(\sum^{n}_{i=1}|A_i|)-(\sum^{n}_{i=1}\sum^{n}_{j=1 ,j\neq i}|A_i\cap A_j|)+\dots \pm|A_1\cap A_2\cap\dots \cap A_n|$$ 
最后一个 $\pm$ 符号视 $n$ 奇偶性而定，$n$ 为奇数则加；$n$ 为偶数则减。

**请确保您可以理解**。我们开始分析题目。

# 题目描述：

对于两个大小为 $n$ 集合 $E,F$，需要满足：

- 条件一：$\forall i\in [1,n],E_i\neq F_i$；

- 条件二：$\forall i\in [1,n],E_i\in [1,m]$；

- 条件三：$\forall i\in [1,n],F_i\in [1,m]$。

求可能的方案。

# 题目分析：

首先我们确定 $E$ 集合，毫无疑问可以获得 $\text{A}^{n}_{m}$ 个方案。（此处 $\text{A}^{k_1}_{k_2}$ 是排列组合的用法，表示从 $k_2$ 个元素中选择 $k_1$ 个元素并考虑顺序的方案数。）

接下来我们尝试确定 $F$ 集合。如果不考虑条件一，那么显然也有 $\text{A}^{n}_{m}$ 个方案，与 $E$ 集合的相同。在此基础上考虑条件一，我们显然要**剔除一些方案**。 参见下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/tr282inv.png)

该图列举出了**所有的不合法方案**，对于集合 $T_i$，它的元素是**一些排列**，是不同的 $F$ 集合，不过需要满足 $F_i=E_i$。

值得强调的是，$E_i=F_i$ **并不意味着一定是 $E$ 集合的第 $i$ 个等于 $F$ 集合的第 $i$ 个，而是表示保证有一个位置上 $E$ 和 $F$ 相同。画出 $T_1\dots T_n$ 则强调对于每一个集合 $T_i$，该位置均不相同**。

**请务必理解这一点！**

接下来我们继续：

那么是不是直接用 $\text{A}^{n}_{m}$ 减去 $(|T_1|+|T_2|+\dots |T_n|)$ 就可以了呢？当然不是这样，因为 $T_1,T_2,\dots ,T_n$ 之间也有重复的部分，所以我们要减去的是 $|T_1\cup T_2\cup \dots \cup T_n|$，接下来，您果然熟练运用了我们的前置芝士，写出如下等式：

$$|T_1\cup T_2\cup \dots \cup T_n|=(\sum^{n}_{i=1}|T_i|)-(\sum^{n}_{i=1}\sum^{n}_{j=1 ,j\neq i}|T_i\cap T_j|)+\dots \pm|T_1\cap T_2\cap\dots \cap T_n|$$

最后，您甚至避免了歧义，说道：“**最后一个 $\pm$ 符号视 $n$ 奇偶性而定，$n$ 为奇数则加；$n$ 为偶数则减**。”

**感谢您做出的贡献**！但是接下来怎么办呢？

让我们回到最开始的图，会发现，尽管求 $|T_1\cup T_2\cup\dots\cup T_n|$ 是很困难的，但是求 $|T_1\cap T_2\cap\dots\cap T_n|$ 却要容易得多，因为**取集合间的交集可以保留单个集合的性质，即 $E_i=F_i$**。

详细地说，$k$ 个 $T$ 类集合的交集的大小即为：对于 $F$ 集合，固定住 $k$ 个数的方案数。

因为这 $k$ 个数位置不定，**所以我们用 $\text{C}^{k}_{n}$ 表示**，即从 $n$ 个位置中找到 $k$ 个位置的方案，这是排列组合的内容。

而除了这 $k$ 个位置，其余的数要求大小在 $[1,m]$ 之间且互不相同。

幸运的是，我们依然可以用排列组合的公式来表示**这 $(n-k)$ 个位置的方案数，即 $\text{A}^{n-k}_{m-k}$**。它表示从 $(m-k)$ 个数中找出 $(n-k)$ 个不同的数并考虑顺序的方案数。

最后我们把这两种方案数乘起来，就是 **$k$ 个 $T$ 类集合的交集的大小**：

$$\text{C}^{k}_{n} \cdot \text{A}^{n-k}_{m-k}$$

**真是巨大的进步**！接下来让我们看到您推出的公式，发现我们需要处理 $1$ 到 $n$ 个集合的交集，那么枚举 $k$ 并加起来！这次又是您更先整理出式子了：

$$|T_1\cup T_2\cup \dots \cup T_n|=\sum^{n}_{k=1}[\text{C}^{k}_{n} \cdot \text{A}^{n-k}_{m-k}\cdot (-1)^k]$$

**这是计算机可以计算出的式子了！**

我们再来看看它跟答案有什么关系吧！您一定还记得，我们是要用 $\text{A}^{n}_{m}$ 减去这个式子来求出 $F$ 的方案数吧，也就是说，$F$ 集合的方案数就是：

$$\text{A}^{n}_{m}-\sum^{n}_{k=1}[\text{C}^{k}_{n} \cdot \text{A}^{n-k}_{m-k}\cdot (-1)^k]$$

**离答案只有一步之遥了！**

您果然立刻就想起来我们还有 $\text{A}^{n}_{m}$ 个 $E$ 集合的可能方案数吧！最后的答案应该是 $E$ 集合的方案数乘上 $F$ 的方案数。您又抢先一步写出式子了:

$$\text{A}^{n}_{m}\times \{\text{A}^{n}_{m}-\sum^{n}_{k=1}[\text{C}^{k}_{n} \cdot \text{A}^{n-k}_{m-k}\cdot (-1)^k]\}$$

**没错，这就是答案了！**

快脱离复杂的数学运算，用这个简洁明快的式子去写出您的 $\text{AC}$ 代码吧！

我先放出我的代码啦！

```cpp

#include <iostream>
#include <cstdio>
#define MOD 1000000007
using namespace std;
typedef long long i64;

i64 fast_pow(i64 a, i64 p) {
	i64 r = 1;
	while(p) {
		if(p & 1) r = r*a%MOD;
		a = a*a%MOD;
		p >>= 1;
	}
	return r%MOD;
}
i64 n, m;
i64 j[500005], inv[500005];

i64 A(i64 a, i64 b) {
	return j[b]*inv[m-n]%MOD;
}
i64 C(i64 a, i64 b) {
	return j[b]*inv[a]%MOD*inv[b-a]%MOD;
}

int main() {
	scanf("%lld%lld", &n, &m);
	j[1] = j[0] = 1;
	for(i64 i = 2 ; i<= 500000 ; i++) {
		j[i] = i*j[i-1]%MOD;
	}
	inv[1] = inv[0] = 1;
	for(i64 i = 2 ; i<= 500000 ; i++) {
		inv[i] = inv[i-1]*fast_pow(i, MOD-2)%MOD;
	}
	i64 sum = 0;
	for(i64 i = 1 ; i<= n ; i++) {
		i64 v = C(i, n)*A(n-i, m-i)%MOD;
		if(i%2 == 1) v = (v*(-1)+MOD)%MOD;
		sum = (sum+v)%MOD;
	}
	sum = (sum+A(n, m))%MOD;
	sum = sum*(A(n, m))%MOD;
	printf("%lld\n", sum%MOD);
	return 0;
}

```

### 期待与您的下一次合作！祝您好运~

---

## 作者：Tx_Lcy (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc172_e)

## 思路

这是一道很简单的容斥题。

首先分析一下第二个条件，$a_i$ 和 $b_i$ 分别均互不相同，这个条件等同于告诉你每个 $1$ 到 $m$ 的数只能用一次，别的没用。

然后分析一下第一个条件，$a_i$ 和 $b_i$ 对于每个 $i$ 均互不相同，于是我们可以简单容斥，钦定 $j$ 个数的 $a_i=b_i$，于是此时的答案就是 $(_{j}^{n}) \times A(m,j) \times A(m-j,n-j) \times A(m-j,n-j)$。

于是如此计算即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=5e5+10;
int const mod=1e9+7;
int fac[N];
inline int qpow(int a,int b){int ans=1;while (b){if (b&1) ans*=a,ans%=mod;a*=a,a%=mod,b>>=1;}return ans;}
#define inv(x) (qpow(x,mod-2))
inline int C(int n,int m){return fac[n]*inv(fac[m])%mod*inv(fac[n-m])%mod;}
inline int A(int n,int m){return fac[n]*inv(fac[n-m])%mod;}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m;cin>>n>>m;
	fac[0]=1;
	for (int i=1;i<=m;++i) fac[i]=fac[i-1]*i%mod;
	int ans=0;
	for (int i=0;i<=n;++i){
		int x=C(n,i)*A(m,i)%mod*A(m-i,n-i)%mod*A(m-i,n-i)%mod;
		ans+=x*((i&1)?-1:1);ans%=mod;
		ans+=mod;ans%=mod;
	}
	cout<<ans<<'\n';
	return 0;
}
```


---

## 作者：_zuoqingyuan (赞：2)

今天也是学会容斥，成功到达小学数学素养了。

# 思路分析

不难想到主要思路是先确定一个序列，再确定另一个序列。我们设第一个确定的序列为序列 $A$，第二个为序列 $B$。

对于序列 $A$，就是在 $[1,m]$ 中任选 $n$ 个数组成的一个排列，合法方案数即为 $A_{m}^n$。

对于序列 $B$，我们可以逆向思考，求解出和序列 $A$ **至少有一个位置相同**的序列个数，记为 $S$，则序列 $B$ 的合法方案数即为 $A_{m}^n-S$。显而易见，对于任意序列 $A$，因为计算方法一样，所以其对应的序列 $B$ 的合法方案数也一定。最终的答案即为 $A_{m}^n\times(A_{m}^n-S)$。

现在的主要问题是如何求解 $S$，根据定义，一种可行的方案是，枚举序列 $A$ 中的一个元素 $A_i$，令 $B_i=A_i$，然后让 $B$ 的剩余元素随意排列，即方案数为 $n\times A_{m-1}^{n-1}$（$m-1$ 是因为 $A_i$ 已经使用过了，$n-1$ 是 $B$ 中剩余的元素）。

但同一种排列可能会重复计算，假定序列 $A$ 为 `1 2 3 4 5`，则序列 $B$ 为 `1 2 5 3 4`。我们希望这种方案在 $S$ 中出现一次，但是在枚举到 $A_1,A_2$ 时，这种方案都计算了一次，共计算了两次，所以我们要将其减掉，即减去 $C_{n}^{2}\times A_{m-2}^{n-2}$。

不过我们又发现，对于 $A$ 和 $B$ 中有三个位置相同的方案，又少算了一次，所以要加上，依次类推，可以得到 $S$ 的表达式。

$$S=(-1)\sum_{i=1}^n(-1)^iC_{n}^{i}\times A_{m-i}^{n-i}$$

这用到了**容斥原理**的思想，通过这种思想，可以快速求出 $S$，结合预处理，可以在 $O(n\log n)$ 的时间复杂度内求解。

# Code

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N=5e5+10,mod=1e9+7;
ll fac[N],n,m,sum;
void prep(){
	fac[0]=1;
	for(ll i=1;i<=5e5;i++)fac[i]=(fac[i-1]*i)%mod;
	return;
}
ll ksm(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1)ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
ll A(ll n,ll m){
	return (fac[n]*ksm(fac[n-m],mod-2))%mod;
}
ll C(ll n,ll m){
	return (fac[n]*ksm(fac[n-m]*fac[m]%mod,mod-2))%mod;
} 
int main(){
	scanf("%lld %lld",&n,&m);
	prep();
	sum=A(m,n);
	for(int i=1;i<=n;i++){
		ll val=C(n,i)*A(m-i,n-i)%mod;
		if(i&1)sum=((sum-val)%mod+mod)%mod;
		else sum=(sum+val)%mod;
	}
	printf("%lld\n",sum*A(m,n)%mod);
	return 0;
}
```

如有错误，请指出。

---

## 作者：rickyxrc (赞：2)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

## 题面大意

给定 $n,m$，需要构造长度为 $n$ 的整数序列 $A,B$，使得 $A,B$ 中元素两两互异，并且使得 $A,B$ 两序列相同位置的元素值不同，求方案数模上 $10^9+7$ 的值。

## 解法

肯定是一道数学题。

我们首先考虑方案的计算，正难则反，可以用总情况数减去所有不合法情况数。

什么情况是不合法的呢？

- 数列内元素不互异。
- 数列 $A$ 和 $B$ 在相同位置的元素值相等。

第一种情况，可以通过排列组合排除掉，下文的数列均满足数列中数两两互异。

对于第二种情况，我们可以定义 $T_i$ 为**在数列 $A$ 确定的情况下**第 $i$ 位与 $A_i$ 相同的数列构成的集合。

那么容易得出 $|T_i| = A^{n-1}_m$（因为相等的那一位已经确定了，其他位只需要满足互异即可） 。

我们可以直接求出 $\sum^n_{i=1}|T_i|$ 作为不合法情况数吗？显然不行，因为会有重复情况（例如第 $2$，$3$ 位相等的数列既在 $T_2$ 又在 $T_3$ 中）。

那么实际上我们应该求出的不合法情况数是 $\left|\bigcup_{i=1}^nT_i\right|$。

这个式子怎么求呢？我们来考虑下容斥定理。

### 容斥定理

这一部分是知识铺垫，上文所有的假设和定义均不适用，已经了解这是什么可以跳过。

首先考虑 $A,B$ 两个集合，那么显然当 $A\bigcap B \neq \emptyset$ 时，$|A|+|B| \neq |A\bigcup B|$。

所以要减去其中重复的部分，即 $\left| A\bigcup B\right| =\left| A\right| +\left| B\right| -\left| A\bigcap B\right|$。

那么如果推广到三个集合呢？此时我们发现 $|A\bigcap B\bigcap C|$ 被多减了一次，所以要加回来，即 $|A\bigcup B\bigcup C|=|A|+|B|+|C|-|A\bigcap B|-|B\bigcap C|+|A\bigcap B\bigcap C|$。

将其推广到任意集合，我们发现如下定理：

> $n$ 个集合的并的元素数量等于它们的数量和减去其中任意两个集合的交的数量和加上其中任意三个集合的交的数量和减去其中任意四个集合的交的数量和，以此类推。

好，讲完了，现在我们来看看上面的不合法情况数怎么处理。

那么 $\left|\bigcup_{i=1}^nT_i\right|$ 和这个式子等价：
$$\bigcup_{i=1}^n|T_i| =\sum_{i<j,i\in[1,n],j\in[1,n]}^n|T_i\bigcap T_j| - \sum_{i<j<k,i\in[1,n],j\in[1,n],k\in[1,n]}^n|T_i\bigcap T_j\bigcap T_k| + \cdots$$

但是交集也不好算，我们需要再次转化。

想一想，这些集合的交集代表什么？应该代表的是符合这些集合共同特征的数列构成的集合，即上面公式中 $n$ 个集合的交就是有且仅有 $n$ 位与 $A$ 数列相等的数列构成的集合。

我们再做如下定义：定义 $F_i$ 为有且仅有 $i$ 位与 $A$ 相等的序列构成的集合。

现在只要推出 $F_i$，问题就解决了。

那么因为我们需要 $i$ 位相等，那么需要选出 $i$ 位（无顺序要求）来和 $A$ 的每一位匹配，有 $C^i_n$ 种，剩下的位置不能是 $A_i$ 且两两互异，所以有 $A_{m-i}^{n-i}$ 种类。

根据乘法原理可得 $|F_i| = C_n^i \times A_{m-i}^{n-i}$。

这里不要忘记上面的所有公式前提都是在 $A$ 已经确定的情况下推出的，所以答案要乘上 $A^n_m$。

因为我们计算的是不合法方案数，所以我们要用 $A^n_m$ 减去合法方案数。

现在我们整理一下公式：

$$ans = A^n_m(A^n_m-\text{invalid})$$

$$ans = A^n_m(A^n_m-T_1+T_2-T_3+T_4-\cdots)$$
$$ans = A^n_m(A^n_m+\sum_{i=1}^nT_i\times(-1)^i)$$
$$ans = A^n_m(A^n_m+\sum_{i=1}^nC^i_nA^{n-i}_{m-i}\times(-1)^i)$$
由于要取模，记得计算乘法逆元。

可以看这里：[乘法逆元 - OI Wiki (oi-wiki.com)](http://oi-wiki.com/math/number-theory/inverse/)。

这里只需要知道 $a\times inv(b,p) \equiv a/b\space\text{(mod p)}$，因为 $p$ 是质数，所以我们使用费马小定理求逆元。

代码注意点有一个，就是负数取模一定要 `(x%p+p)%p` 才能取到最小正整数。

代码如下：

```cpp
#include <stdio.h>
#include <ctype.h>
#define mod 1000000007
#define int long long
int pow(int x, int p)
{
  int res = 1;
  while (p)
  {
    if (p & 1)
      res = res * x % mod;
    x = x * x % mod;
    p >>= 1;
  }
  return res;
}

int inv(int x)
{
  if (x == 0 || x == 1)
    return 1;
  return pow(x, mod - 2) % mod;
}

int n, m, jc[1000007];

int lm(int x)
{
  return (x % mod + mod) % mod;
}

int A(int m, int n)
{
    return lm(jc[n] * inv(jc[n - m]));
}

int C(int m, int n)
{
    return lm(lm(jc[n] * inv(jc[m])) * inv(jc[n - m]));
}

int anm, sum, tval, pv = -1;
signed main()
{
  scanf("%lld%lld", &n, &m);
  jc[0] = 1;
  for (int i = 1; i <= 1000000; i++)
    jc[i] = i * jc[i - 1] % mod;

  for (int i = 1; i <= n; i++)
  {
    tval = lm(lm(C(i, n) * A(n - i, m - i)) * pv);
    sum = lm(sum + tval);
    pv *= -1;
  }

  sum = lm(sum + A(n, m));
  sum = lm(sum * A(n, m));

  printf("%lld\n", sum);

  return 0;
}
```


---

## 作者：OIer_Automation (赞：1)

我们考虑总共的情况数：$A$ 序列有 $A_{m}^{n}$ 种选择，同样的，$B$ 序列有 $A_{m}^{n}$ 种选择，那么总共的情况数有 ${A_{m}^{n}}^{2}$ 种。

但是，很明显，这样得到的答案一定是不准确的，因为两个序列可能有重复的部分，我们尝试用总方案数减去所有不合法的序列（就是不合法情况的并）。

不合法情况指的就是与题意相违背的 $\exists i\in [1,n],A_{i}=B_{i}$。可以将其更加具体的划分为恰好有 $1$ 个相等，恰好有 $2$ 个相等，$\dots$，恰好有 $n$ 个相等，用总情况减去即可。（下用 $f_{i}$ 表示恰好有 $i$ 个相等）。

若要求出每一个 $f_{i}$，求出至少有 $i$ 个情况相等的情况数（下用 $g_{i}$ 表示至少有 $i$ 个相等），再依次减去每一个 $f_{j}(j>i)$ 才可以。时间复杂度为 $O(n^2)$。

> 明显的，对于每一个 $g_{i}$ 的求法，先在 $m$ 个数里找出 $i$ 个数，令他们作为两个序列中相等的数，再将其排列至 $n$ 个位置，可以证明，这样得到的相等位置一定不重复。剩下的 $n-i$ 个位置可以从剩下的 $m-i$ 个数里随意取，所以总共的方案数为 $C_{m}^{i}\times A_{n}^{i}\times A_{m-i}^{n-i}$。

考虑每一个 $g_{k+1}$ 的情况，一定在 $g_{k}$ 里出现了 $C_{k+1}^{k}$ 次，因此减去，即 $g_{k+1}$ 前的系数为 $-C_{k+1}^{k}$。但对于 $g_{k+2}$ 的情况，一定在 $g_{k+1}$ 里出现了 $C_{k+2}^{k+1}$ 次，要先减去，所以对于 $g_{k+2}$，系数应为 $-C_{k+2}^{k}+C_{k+1}^{k}\times C_{k+2}^{k+1}=C_{k+2}^{k}$ 。如此类推下去，可以得到，$g_{k+i}$ 对应的系数为 $(-1)^{k+i}\times C_{k+i}^{k}$。在原题中，因为求解的情况 $k=0$，所以可以看作 $(-1)^{k+i}$。

> 对于每一个 $g_{k+1}$，可以看作先挑选了 $k$ 个一定重复的数然后得到的结果，所以有：对于每一个 $g_{k+1}$ 的情况，一定在 $g_{k}$ 里出现了 $C_{k+1}^{k}$ 次。

得到了系数之后，用容斥原理处理即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int R=1e9+7;
int n,m;
ll f[500005],g[500005];

void init(){
	f[0]=g[0]=g[1]=1;
	for(int i=1;i<=500000;i++)f[i]=f[i-1]*i%R;
	for(int i=2;i<=500000;i++)g[i]=(R-R/i)*g[R%i]%R;
	for(int i=2;i<=500000;i++)g[i]=g[i]*g[i-1]%R;
}

ll calc(){
	ll res=0,sign=-1;
	for(int i=0;i<=n;i++){
		ll sum=(f[m]*g[m-i]%R*g[i]%R)*(f[n]*g[n-i]%R)%R*(f[m-i]*g[m-n]%R)%R*(f[m-i]*g[m-n]%R)%R;
		sign=-sign;
		res=((res+sum*sign)%R+R)%R;
	}
	return res;
}

int main(){
	init();
	scanf("%d%d",&n,&m);
	printf("%lld",calc());
}
```

---

## 作者：luxiaomao (赞：1)

## [AT_abc172_e](https://www.luogu.com.cn/problem/AT_abc172_e) 二项式反演解法

最近刚好在学二项式繁衍，所以就来个二项式繁衍解法。~~其实是我不会递推式。~~

### Problem

给出 $n$ 和 $m$。（$1 \le n \le m \le 5 \times 10^5$）

要求构造长为 $n$ 的序列 $A$ 和 $B$，满足：

- $1 \le A_i,B_i \le m$。

- $A$ 中的数两两不同，$B$ 中的数两两不同。

- $A_i \not= B_i$。

### Solution

首先，只考虑构造序列 $A$，答案为 $A_m^n$。

那么我们从这 $A_m^n$ 种 $A$ 序列中选出一种：$A = \{1,2,3,\dots,n\}$，然后要求构造序列 $B$ 时原来要求 $A_i \not= B_i$，就退化为 $B_i \not= i$ 了。这样就变成了一个比较经典的错排问题。

但相比传统的错排问题，这次我们多出了 $(m-n)$ 个额外的数可以选，我们记 $k = m-n$。

然后开始二项式反演！

- 记 $G_x$ 为 $B$ 的长为 $x$，多出来 $k$ 个数能选，同时满足 $B_i \not= i$ 的方案数。

- 记 $F_x$ 为 $B$ 的长为 $x$，多出来 $k$ 个数能选，同时不用管是否 $B_i \not= i$ 的方案数。

$F_x$ 很好求，显然 $F_x = A_{x+k}^x$。

同时我们可以通过枚举来求 $F_x$，即：

$$F_x = \sum\limits_{i = 0}^x \binom{x}{i}G_i$$

板子一样的反演：

$$G_x = \sum\limits_{i = 0}^x (-1)^{x-i}\binom{x}{i}F_i$$

代入 $F_i$，同时代入 $x = n$：

$$G_n = \sum\limits_{i = 0}^n (-1)^{n-i}\binom{n}{i}A_{i+k}^i$$

至此我们用 $O(n)$ 的时间复杂度求解出了 $G_n$，但别忘了求 $G_n$ 的前提是 $A_i = i$，所以：

$$ans = A_m^n \times G_n$$

解决了本题。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 500005
using namespace std;

const int mod = 1000000007;
int n,m,k;
int fac[N],inv[N];
int qpow(int a,int b)
{
	int ret = 1;
	while(b)
	{
		if(b&1)ret = ret * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ret;
}
void init()
{
	fac[0] = 1;
	for(int i = 1;i <= 500000;i++)fac[i] = fac[i-1] * i % mod;
	inv[500000] = qpow(fac[500000],mod-2);
	for(int i = 499999;i+1;i--)inv[i] = inv[i+1] * (i+1) % mod;
}
int A(int n,int m){return fac[n] * inv[n-m] % mod;}
int C(int n,int m){return fac[n] * inv[m] % mod * inv[n-m] % mod;}

signed main()
{
	init();
	scanf("%lld%lld",&n,&m);k = m-n;
	int ans = 0;
	for(int i = 0;i <= n;i++)
	{
		ans += ((n-i)%2?-1:1) * C(n,i) % mod * A(i+k,i) % mod;
		ans = (ans%mod+mod)%mod;
	}
	return printf("%lld\n",ans*A(m,n)%mod),0;
}
```

感谢阅读。

---

## 作者：ccjjxx (赞：1)

# AT_abc172_e [ABC172E] NEQ 题解

### 排列数+错排。

考虑序列 $A$ 的个数，显然是 $A_{m}^{n}$ 种。

那么题目上说要求 $\forall A_i \neq B_i,A_j \neq A_i,B_i\neq B_j$，

显然，B 序列是 A 的错排。在通常的定义中，错排 $D(n)=(n-1)\times (D(n-1)+D(n-2))$ 是针对于有 $n$ 个可选数，且序列长度为 $n$ 的。

但是这里是**有** $m$ **个可选数，且序列长度为** $n$，并有 $m\ge n$。

可以考虑**加法原理**，即 $B$ 序列的选择数一定是 $D(n)+f(n)$ 的形式，这里可以找个例子来理解一下：

若 $n=3,m=4$，则 $A$ 序列的个数为 $A_{m}^{n}=A_{4}^{3}=24$。

对于一个 $A=1,2,3$，$B$ 的全部合法序列为：

$$
\begin{aligned}
2,3,4 \\
2,4,1 \\
2,3,1 \\
3,4,1 \\
3,2,4 \\
3,4,2 \\
3,1,2 \\
3,1,4 \\
4,3,1 \\
4,1,2 \\
4,3,2 \\
\end{aligned}
$$
总共 $11$ 种。可以看出，除过与 $A$ 序列元素相同的排法，在第 $N$ 位上，会有 $m-n$ 个 $A$ 序列中没有的元素，在本例中即是数字 $4$。而对于剩下 $n-1$ 位，有 $D(n-1)$ 种排法。

所以这道题的答案是错排公式是改编版，其中 $M,N$ 代表题中给出数据。
$$
D(n)=
\begin{cases}
1 &,n=0\\
M-N&,n=1 \\
(M-N)\times D(n-1)+(n-1)\times(D(n-2)+D(n-1))&,otherwise
\end{cases}
$$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int mx=5e5+5;
int f[mx+5],g[mx+5],d[mx+5];
int ppow(int a,int b)//快速幂 
{
	int res=1;
	while(b)
	{
		if(b&1) res=(res*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return res;
}
void init()
{
	f[0]=g[0]=1;
	for(int i=1;i<=mx;i++)
	{
		f[i]=(f[i-1]*i)%mod;
		g[i]=(g[i-1]*ppow(i,mod-2))%mod;//费马小定理求逆元 
	}
}
inline int a(int n,int m)
{
	return (f[n]*g[n-m]%mod+mod)%mod;
}
signed main()
{
	int n,m;
	cin>>n>>m;
	d[1]=m-n;d[0]=1;//边界 
	init();//初始化f[n]g[n]数组 
	for(register int i=2;i<=n;++i)//计算D(n) 
	{
		d[i]=(m-n)*d[i-1]+(i-1)*(d[i-1]+d[i-2]);
		d[i]%=mod;
	}
	int ans=a(m,n)%mod;
	int t=d[n]%mod;
	ans=(ans*t)%mod;
	cout<<ans%mod;//结论 
}
```


---

## 作者：Erica_N_Contina (赞：1)

## 大意

构造两个 $1\sim M$ 的不完全排列（即可能会有数字空缺），使得 $\forall i$，$A_i\neq B_i$，求方案数。

## 前置知识

组合数。

本题解尽量不使用排列数里的相关运算，而是写出阶乘的形式。对于文章中的 $C$ 定义为：

> 从 $n$ 个不同元素中，任取 $m(m≤n) $ 个元素并成一组，叫做从 $n $ 个不同元素中取出 $m $ 个元素的一个组合；从 $n $ 个不同元素中取出 $m(m≤n) $ 个元素的所有组合的个数，叫做 $n$ 个不同元素中取出 $m$ 个元素的组合数。用符号 $C(n,m) $ 表示。

## 思路



很明显是一个组合数学的问题，我们求出总方案数，然后减去不满足的即可。注意这里需要容斥一下。

总方案数：对于 $A$，第一个位置有 $M$ 种方案，第二个位置有 $M-1$ 种，以此类推，方案总数为 $\prod\limits_{i=0}^{N-1}M-i $，即 $\frac{ M!}{(M-N)!}$。

对于 $B$ 也是一样的，所以总方案数为 $[\frac{M!}{(M-N)!}]^2$。

我们现在来考虑不满足要求的。先考虑**至少**有一个位置相同的，即存在一个 $i$ 使得 $A_i=B_i$。注意我们没有办法计算出恰好只要一个位置相同的，所以我们只能去其次求至少的。
那么我们把位置 $i$ 从 $A,B$ 中剔除，先加上位置 $i$ 的 $M$ 种情况，剩下的 $A',B'$ 的长度均为 $N-1$，那么 $A',B'$ 方案数量为 $[\frac{(M-1)!}{(M-N+1)!}]^2$，总情况数为 $M\times [\frac{(M-1)!}{(M-N+1)!}]^2$，注意这里不能写成 $[\frac{(M)!}{(M-N+1)!}]^2\times (M-N+1)$。

还没完，我们还需要考虑相同的位置在哪里，比如是 $A_1=B_1$ 还是 $A_2=B_2\dots$，所以就相当于我们在 $N$ 个位置中挑选一个位置，方案为 $C(N,1)$。

这下我们终于得到了**至少**有一个位置相同的情况数，为 $C(N,1)\times M\times [\frac{(M-1)!}{(M-N+1)!}]^2$。



再考虑至少有 $2$ 个位置相同的，情况数为 $C(N,2)\times M\times(M-1)\times  [\frac{(M-2)!}{(M-N+2)!}]^2$。

$\dots$

总结一下，当有 $i$ 个位置相同时，情况数为 $C(N,i)\times \frac{(M)!}{(M-i)!}\times [\frac{(M-i)!}{(M-N+i)!}]^2$。

根据容斥原理，奇减偶加，答案即为 $\sum\limits_{i=0}^N (-1)^i\times C(N,i)\times  \frac{(M)!}{(M-i)!}\times [\frac{(M-i)!}{(M-N+i)!}]^2$。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>

//数据类型
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
//命名空间
using namespace std;
//常量
const int N=5e5+5;
const int M=1e3;
const int MOD=1e9+7;
const int INF=1e9;
//变量
int n,m,a,b,c,x[N],y[N],ans,res,tmp,cnt,web[M][M],fac[N];

int ksm(int c,int k,int p) {	//c^k %p
	int res=1;
	while(k) {
		if(k&1) {
			res=res*c%p;	//注意只有1句在里面！
		}
		k>>=1;	//不要写反了！
		c=c*c%p;
	}
	return res;
}

int inv(int x){
    return ksm(x,MOD-2,MOD);
} 

int C(int n,int m){return fac[n]*inv(fac[m])%MOD*inv(fac[n-m])%MOD;}

int A(int n,int m){return fac[n]*inv(fac[n-m])%MOD;}

signed main(){
    cin>>n>>m;
	fac[0]=1;
	for (int i=1;i<=m;++i) fac[i]=fac[i-1]*i%MOD;

	for (int i=0;i<=n;++i){
		int x=C(n,i)*A(m,i)%MOD*A(m-i,n-i)%MOD*A(m-i,n-i)%MOD;
		if(i&1)ans-=x;
        else ans+=x;
        ans=(ans%MOD+MOD)%MOD;
	}
    printf("%lld\n",ans);
#ifdef PAUSE_ON_EXIT
    system("pause");
#endif
    return 0;
}

```


## Upd.

23.10.3 修改数学性错误。



---

## 作者：_Kenma_ (赞：0)

# abc172_e 解题报告

## 前言

终于能独立做容斥题了！

## 思路分析

首先这是一个错排问题。

我们都知道错排问题是经典容斥问题。

仿照正常错排问题的思路，我们可以这样容斥：总数 - 有一个位置正确 + 有两个位置正确 - 有三个位置正确……

对于有 $i$ 个位置正确的问题，我们可以按照这个思路计算组合数：先选出这 $i$ 个正确的数，给它们分配位置，再让剩下的数随意选择位置。

所以，答案为：

$$ans=\sum_{i=0}^{n} (-1)^i\cdot \binom{m}{i} \cdot A(n,i) \cdot A(m-i,n-i)^2$$

这个柿子的组合意义就是上面所说的。

预处理阶乘和逆元，可以做到 $O(n)$。

我偷懒写快速幂就是 $O(n \log v)$ 了。

## 代码实现

计算上面的和柿即可。

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,op,ans,fac[500005];
int binpow(int a,int b){
	if(b==0) return 1;
	int res=binpow(a,b/2);
	if(b&1) return res*res%mod*a%mod;
	else return res*res%mod;
}
int C(int a,int b){
	return fac[a]*binpow(fac[a-b],mod-2)%mod*binpow(fac[b],mod-2)%mod;
}
int A(int a,int b){
	return fac[a]*binpow(fac[a-b],mod-2)%mod;
}
signed main(){
	cin>>n>>m;
	fac[0]=1;
	for(int i=1;i<=m;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	for(int i=0;i<=n;i++){
		if(i&1) op=-1;
		else op=1;
		ans=(ans+op*C(m,i)*A(n,i)%mod*binpow(A(m-i,n-i),2)%mod+mod)%mod;
	}
	cout<<ans;
}

```

## 后记

应该算是比较基础的容斥了。

难的我也不会啊。

---

## 作者：DESCENDANTSOFDRAGON (赞：0)

首先，我们来看一个基础内容 **错排问题**

即： $n$ 封不同的信，与 $n$ 个不同的信封，将 $n$ 封信都装错信封的方案个数

设 $D[n]$ 表示 $n$ 个元素的错排

则有

$$
D(n)=(n-1)(D(n-1)+D(n-2))
(D(1)=0,D(2)=1)
$$

通过这个递推可推出下面这个公式

$$
D(n)=n!(\frac{(-1)^0}{0!}+\frac{(-1)^1}{1!}+\dots+\frac{(-1)^n}{n!})=n!\sum_{k=0}^{n}\frac{(-1)^k}{k!}
$$

错排问题中，对于每一个 $k$ 不与 $i$ 相当，将 $i$ 放在位置 $k$，有以下两种情况：

- $k$ 放在位置 $i$ 上，则相当于不管 $i$ 和 $k$，然后剩下的 $i-2$ 个数字错排，共有 $dp[i-2]$ 种情况。
- $k$ 没有放在位置 $i$ 上，因为 $k$ 不能放在位置 $i$ 上，所以就相当于不包括数字 $i$ 的错排，共有 $dp[i-1]$ 种情况。

而这道题其实就是一个错排的变式。

在这道题中，我们首先固定序列 $A$，选出 $n$ 个数字，共有 $A_{m}^{n}$ 种方案。

“假错排”就是在上述情况中再加上一种情况：

- 对于第 $i$ 次加入数字，将任意一个数字 $k(k\in[1,m],k\notin\{b_1,b_2\cdots b_{i-1}\},k\notin\{i+1,n\})$ 填入位置 $n$，则可选择 $m-n$ 种数字。

从而本题的状态转移方程为：

$$
dp[i]=(m-n)dp[i-1]+(i-1)(dp[i-1]+dp[i-2])
$$

代码如下：

```
#include<bits/stdc++.h>
#include<cstdlib>
using namespace std;
const int maxn=1e6+5;
const int MOD=1e9+7;
typedef long long ll;
ll n,m;
ll dp[maxn];
int main (){
	cin>>n>>m;
	dp[0]=1;
	dp[1]=m-n;
	for(int i=2;i<=n;i++)
		dp[i]=((m-n)*dp[i-1]%MOD+(i-1)*(dp[i-1]+dp[i-2])%MOD)%MOD;
	ll ans=dp[n];
	for(int i=m;i>=m-n+1;i--)
		ans=(ans*i)%MOD;
	cout<<ans<<endl;
	return 0;
}
```


---

