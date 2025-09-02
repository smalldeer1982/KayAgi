# Centroid Probabilities

## 题目描述

Consider every tree (connected undirected acyclic graph) with $ n $ vertices ( $ n $ is odd, vertices numbered from $ 1 $ to $ n $ ), and for each $ 2 \le i \le n $ the $ i $ -th vertex is adjacent to exactly one vertex with a smaller index.

For each $ i $ ( $ 1 \le i \le n $ ) calculate the number of trees for which the $ i $ -th vertex will be the centroid. The answer can be huge, output it modulo $ 998\,244\,353 $ .

A vertex is called a centroid if its removal splits the tree into subtrees with at most $ (n-1)/2 $ vertices each.

## 说明/提示

Example $ 1 $ : there are two possible trees: with edges $ (1-2) $ , and $ (1-3) $ — here the centroid is $ 1 $ ; and with edges $ (1-2) $ , and $ (2-3) $ — here the centroid is $ 2 $ . So the answer is $ 1, 1, 0 $ .

Example $ 2 $ : there are $ 24 $ possible trees, for example with edges $ (1-2) $ , $ (2-3) $ , $ (3-4) $ , and $ (4-5) $ . Here the centroid is $ 3 $ .

## 样例 #1

### 输入

```
3```

### 输出

```
1 1 0```

## 样例 #2

### 输入

```
5```

### 输出

```
10 10 4 0 0```

## 样例 #3

### 输入

```
7```

### 输出

```
276 276 132 36 0 0 0```

# 题解

## 作者：meyi (赞：12)

2022/7/23 UPD: 感谢 [$\text{\color{black}S\color{red}yadouHayami}$](https://www.luogu.com.cn/user/184977) 指出一处 typo。

首先以 $1$ 为根，那么每个点的父亲的编号一定比自己小。

令 $m=\frac{n+1}{2}$，那么题意可以转化为求 $i$ 号点的子树大小 $\ge m$ 且其他点的子树大小 $<m$ 的方案数。

令 $f_i$ 表示 $i$ 号点的子树大小 $\ge m$ 的方案数。显然有 $f_1=(n-1)!$。设 $i$ 号点的子树大小为 $j$，则有 $m\le j\le n-i+1$，故 $n-i+1<m$ 时 $f_i=0$。

先给出结论：$i>1$ 时，$f_i=\sum\limits_{j=m}^{n-i+1}\binom{n-i}{j-1}(n-j-1)!(i-1)(j-1)!$。证明如下：

从 $n-i$ 个点中取出 $j-1$ 个点放在 $i$ 的子树内，有 $\binom{n-i}{j-1}$ 种方案。

不在子树内的 $n-j$ 个点，编号第 $k$ 大的点的父亲有 $n-j-k$ 种选取方案，故总方案数为 $(n-j-1)!$。

第 $i$ 个点可以任意选取一个编号比自己小的点作为父亲，方案数为 $i-1$。

在子树内的 $j-1$ 个点，编号第 $k$ 大的点的父亲有 $j-k$ 种选取方案，故总方案数为 $(j-1)!$。

接下来就是推柿子环节。。。

$$\sum\limits_{j=m}^{n-i+1}\binom{n-i}{j-1}(n-j-1)!(i-1)(j-1)!$$
$$=\sum\limits_{j=m}^{n-i+1}\frac{(n-i)!(n-j-1)!(i-1)(j-1)!}{(j-1)!(n-i-j+1)!}$$
$$=(n-i)!(i-1)\sum\limits_{j=m}^{n-i+1}\frac{(n-j-1)!}{(n-i-j+1)!}$$
$$=(n-i)!(i-1)!\sum\limits_{j=m}^{n-i+1}\binom{n-j-1}{n-i-j+1}$$
$$=(n-i)!(i-1)!\binom{n-m}{n-i-m+1}$$
$$=\frac{(n-i)!(n-m)!}{(n-i-m+1)!}$$

于是可以 $O(1)$ 求出 $f_i$。

考虑 $ans_i$ 是 $f_i$ 删去 $i$ 子树内存在某个点 $j$ 为重心的方案数，而 $j$ 是重心且在 $i$ 子树内的概率为 $\frac{1}{i}$，故 $ans_i=f_i-\frac{\sum\limits_{j=i+1}^n ans_j}{i}$。

因此可以在 $O(n)$ 复杂度内解决本题。

代码：

```cpp
#include<cstdio>
const int maxn=2e5+10,mod=998244353;
int ans[maxn],fac[maxn],ifac[maxn],inv[maxn],m,n,sum;
int main(){
	scanf("%d",&n);
	fac[0]=fac[1]=ifac[0]=ifac[1]=inv[1]=1;
	for(int i=2;i<=n;++i){
		fac[i]=1ll*fac[i-1]*i%mod;
		ifac[i]=1ll*ifac[i-1]*(inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod)%mod;
	}
	m=n+1>>1;
	for(int i=n-m+1;i;--i){
		if((ans[i]=(1ll*fac[n-i]*fac[n-m]%mod*ifac[n-i-m+1]-1ll*inv[i]*sum)%mod)<0)ans[i]+=mod;
		if((sum+=ans[i])>=mod)sum-=mod;
	}
	for(int i=1;i<=n;++i)printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：EuphoricStar (赞：8)

首先需要了解重心的三种定义：

1. 删掉一个点后剩下子树大小 $\le \frac{n}{2}$ 的点
2. $\sum\limits_{i = 1}^n \text{dis}(u, i)$ 最小的点
3. 最深的 $sz_u \ge \left\lceil\frac{n}{2}\right\rceil$ 的点

这道题我们使用第三种定义，也就是要统计 $i$ 为最深的 $sz_i \ge \left\lceil\frac{n}{2}\right\rceil$ 的点。

首先设 $m = \left\lceil\frac{n}{2}\right\rceil$。那么我们先计算 $sz_i \ge m$ 的方案数 $f_i$。

枚举 $sz_i = j$，选点方案为 $\binom{n - i}{j - 1}$；子树内的点和子树外的点选父亲的方案数分别为 $(j - 1)!$ 和 $(n - j - 1)!$，$i$ 号点选父亲的方案为 $i - 1$。

所以：

$$f_i = \sum\limits_{j = m}^{n - i + 1} \binom{n - i}{j - 1} (j - 1)! (n - j - 1)! (i - 1)$$

考虑化成能快速算的形式。首先把和 $i$ 有关的项提出来，消掉 $(j - 1)!$，分母补一个 $(i - 2)!$，有：

$$f_i = (n - i)! (i - 1)! \sum\limits_{j = m}^{n - i + 1} \binom{n - j - 1}{i - 2}$$

这不是组合数上指标求和吗。众所周知 $\sum\limits_{i = m}^n \binom{i}{m} = \binom{n + 1}{m + 1}$，所以：

$$f_i = (n - i)! (i - 1)! \binom{n - m}{i - 1}$$

现在 $f_i$ 已经被化成能 $O(1)$ 算的形式了。考虑再容斥计算答案。设 $g_i$ 为 $i$ 为最深的 $sz_i \ge \left\lceil\frac{n}{2}\right\rceil$ 的点的方案数。枚举 $i$ 子树内最深的 $sz_i \ge \left\lceil\frac{n}{2}\right\rceil$ 的点为 $j$，我们有：

$$g_i = f_i - \frac{\sum\limits_{j = i + 1}^n g_j}{i}$$

$\frac{1}{i}$ 是 $j$ 在 $i$ 子树内的概率。考虑 $j$ 不断跳父亲，跳到的第一个编号 $\le i$ 的点在 $[1, i]$ 是等概率的。

所以维护一个后缀和就可以算 $g_i$。时间复杂度 $O(n)$。

[code](https://codeforces.com/contest/1667/submission/243206340)

---

## 作者：1kri (赞：5)

考虑枚举每个点 $i$，记 $f_i$ 为子树 $i$ 大小 $\geq \frac{n+1}{2}$ 的方案数。

先考虑子树 $i$ 的大小为 $j$ 的方案数，首先要在 $i+1$ 到 $n$ 号点中选 $j-1$ 个放入子树 $i$，这部分方案数为 $\binom{n-i}{j-1}$ 。然后给子树 $i$ 中的点钦定父子关系，方案数为 $(j-1)!$ 。对子树 $i$ 以外的点钦定父子关系，方案数为 $(n-j-1)!$ 。还要考虑 $i$ 的父亲，方案数为 $(i-1)$。

综上，子树 $i$ 的大小为 $j$ 的方案数为：

$$\binom{n-i}{j-1} (j-1)! (n-j-1)! (i-1)$$ 

注意，这个式子在 $i=1$ 时显然不成立，简单特判即可。

发现上面的式子还可以拆阶乘变成：

$$(n-i)!(i-1)!\binom{n-1-j}{i-2}$$

我们枚举 $j$ 的范围为 $[\frac{n+1}{2},n]$，令 $k=n-1-j$，则 $k$ 的范围为 $[0,\frac{n-3}{2}]$。由经典的组合恒等式可知，$\sum\limits_{k=0}^{\frac{n-3}{2}}\binom{k}{i-2}=\binom{\frac{n-1}{2}}{i-1}$。

这样，我们就可以在线性复杂度内得到所有的 $f_i$。

但 $f_i$ 不等于 $i$ 为重心的方案数，我们还要容斥掉重心在 $i$ 子树内的情况。

重心在 $i$ 子树内等价于 $i$ 有某个子节点 $v$，满足 $v$ 的子树大小 $\geq \frac{n+1}{2}$，且显然这样的 $v$ 最多只有一个。

考虑对于每个 $i$，枚举所有 $v>i$，计算有多少种方案使 $v$ 子树大小 $\geq \frac{n+1}{2}$ 且 $v$ 为 $i$ 的子节点。

容易发现，当 $v$ 的子树大小固定时，$v$ 的父节点为任意可能点的方案数都是一样的。那么刚刚我们要容斥掉的东西可以直接按 $\frac{f_v}{v-1}$ 来算。

这样，$ans_i=f_i-\sum\limits_{v>i}\frac{f_v}{v-1}$，求完 $f$ 后做一遍后缀和就行了。

时间复杂度：$O(n)$。

完全不能理解这题是怎么放到 1E 的位置上的，没开真是亏大了（


---

## 作者：Lynkcat (赞：4)

我们把一个点作为重心的条件稍微转化一下，一个点是重心当且仅当其子树大小 $>\frac{n-1}{2}$ 并且其儿子的子树大小均 $\leq \frac{n-1}{2}$。

设 $f_i$ 为点 $i$ 子树大小 $>\frac{n-1}{2}$ 的方案数，然后枚举编号比 $i$ 大的点不在其子树内的点有 $j$ 个，那么首先判一下子树大小符不符合条件，然后在 $n-i$ 个点中选择 $j$ 个点，树被划分成了两部分，一部分是子树内的点，一部分是子树外的点。首先对于子树外的 $i-1+j$ 个点，每个点都可以连向比它小的一个点，所以方案数是 $(i+j-2)!$。而第 $i$ 个点只能连向前 $i-1$ 个点，所以方案数是 $i-1$，剩下 $n-i-j$ 个点的方案数同理，每个点都可以连向 $i$ 或者子树内比它小的点，所以方案数为 $(n-i-j)!$。所以最后的贡献是 $\frac{(n-i)!(i+j-2)!(n-i-j)!\times(i-1)}{j!(n-i-j)!}$，消去 $(n-i-j)!$ 变成 $\frac{(n-i)!\times(i-1)(i+j-2)!}{j!}$。发现这个柿子是一个上升幂的前缀和的形式，上升幂求前缀和可以先转成组合数，然后变成组合数上一列求和，可以发现是 $k$ 次前缀和之后的结果所以可以原式与 $i$ 无关的部分可以化为 $\sum_{j=0}^{j=S} \frac{(i+j-2)!}{j!}=(i-2)!\sum_{j=0}^{j=S}\tbinom{i+j-2}{j}=(i-2)!\tbinom{i+S-1}{S}$。

接着我们设 $g_i$ 为第 $i$ 个点作为重心的方案数，首先 $f_i$ 对 $g_i$ 的贡献系数是 $1$，然后再考虑 $i$ 前面的点 $j$，$f_i$ 对 $g_j$ 的贡献系数是 $f_i$ 中满足 $j$ 是 $i$ 的父亲的方案数在 $f_i$ 中的比例，相当于第 $i$ 个点的父亲不需要在 $i-1$ 个点中选了已经确定是 $j$ 了，即 $f_i$ 对 $g_j$ 的贡献系数是 $\frac{1}{i-1}$。直接从后往前边做边加贡献就行了。

时间复杂度 $O(n)$。

---

## 作者：Conan15 (赞：3)

挺巧妙的题，来理一下思路。

令 $m = \lceil \frac{n}{2} \rceil$。\
考虑节点 $u$ 是树的重心的一种判定方法：$u$ 子树大小 $\geq m$，而其他子树大小都 $\lt m$。

设 $f_u$ 表示 $sz_u \geq m$ 的方案数，$g_u$ 表示 $u$ 是重心的方案数。\
$f$ 是好求的，考虑枚举 $j=sz_i$：

$$f_i = \sum\limits_{j=m}^{n-i+1} \binom{n-i}{j-1} \times (j-1)! \times (n-j-1)! \times (i-1)$$

四项分别表示：

1. $\binom{n-i}{j-1}$ 表示 $n-i$ 个点选择 $j-1$ 个把他们放在 $i$ 子树内。
2. $(j-1)!$ 表示选中的点有多少种放置方法。设这个点是第 $p$ 个被放入的，那么它可以选择连接到之前放入的以及 $i$ 这些点共 $(j-1)-p+1+1=j-p+1$ 个点中，根据乘法原理总共有 $(j-1)!$ 种方法。
3. $(n-j-1)!$ 和前者同理，只不过是在子树外排列。
4. $(i-1)$ 表示从 $[1,i)$ 中选择一个点作为 $i$ 的父亲，方案数为 $i-1$。

这个东西看上去就很抽象，所以试着化简一下看看会变成什么：

$$f_i = \sum\limits_{j=m}^{n-i+1} \binom{n-i}{j-1} \times (j-1)! \times (n-j-1)! \times (i-1)$$

展开组合数，提出与 $i$ 相关项：

$$f_i = (n-i)! \times (i-1) \times \sum\limits_{j=m}^{n-i+1} \frac{(n-j-1)!}{(n-i-j-1)!}$$

右边是一个阶乘除以阶乘的形式，考虑把它补全成一个组合数，即除以 $(i-2)!$

$$f_i = (n-i)! \times (i-1) \times (i-2)! \times \sum\limits_{j=m}^{n-i+1} \frac{(n-j-1)!}{(n-i-j-1)!(i-2)!}$$

$$f_i = (n-i)! \times (i-1)! \times \sum\limits_{j=m}^{n-i+1} \binom{n-j-1}{i-2}$$

发现右边成了一个组合数求和的形式。

> 引理：$\sum\limits_{i=m}^{n} \binom{i}{m} = \binom{n+1}{m+1}$。

证明较为简单，大致就是手画一个杨辉三角，发现等号左边是一个竖着的长条求和，等号右边是长条最下面点的右下方。\
根据组合数递推公式显然该引理成立。

于是原式化为：

$$f_i = (n-i)! \times (i-1)! \times \binom{n-m}{i-1}$$

$$\frac{f_i = (n-i)! \times (n-m)!}{(n-m-i+1)!}$$

现在可以 $O(1)$ 地求出 $f_i$ 了！\
然后考虑如何求 $g_i$，$i$ 是重心当且仅当 $sz_i \geq m$ 且子树内不存在重心。\
那么 $g_i = f_i - \frac{\sum\limits_{j=i+1}^n g_j}{i}$，即子树内仅存在 $j$ 这一个重心的方案数乘上 $j$ 在 $i$ 子树的概率。\
为什么概率是 $\frac{1}{i}$？$j$ 不断往上跳，显然因为最后到达 $[1,i]$ 中每个点的概率是相等的。

于是我们只要倒着求 $g$ 数组并维护后缀和即可。

---

## 作者：DaiRuiChen007 (赞：3)

# CF1667E 题解

[Problem Link](https://www.luogu.com.cn/problem/CF1667E)

**题目大意**

> 对每个 $u$ 求出：在所有大小为 $n$ 且满足 $fa_i<i$ 的树中，重心为 $u$ 的有多少个。
>
> 数据范围：$n\le 3\times 10^5,2\nmid n$。

**思路分析**

首先我们要求 $siz_i\ge \dfrac{n+1}2$，记方案数为 $f_i$，枚举子树大小 $j$ 得到：
$$
\begin{aligned}
f_i
&=\sum_{j=(n+1)/2}^{n-i+1}\binom{n-i}{j-1}(n-j-1)!\times (j-1)!\times (i-1)
\end{aligned}
$$
其中 $(n-j-1)!$ 是子树外，$(j-1)!$ 是子树内，$i-1$ 是 $fa_i$。
$$
\begin{aligned}
f_i
&=\sum_{j=(n+1)/2}^{n-i+1}\binom{n-i}{j-1}(n-j-1)!\times (j-1)!\times (i-1)\\
&=\sum_{j=(n+1)/2}^{n-i+1}(n-i)!(i-1)\times(i-2)!\times\binom{n-j-1}{i-2}\\
&=(n-i)!(i-1)!\binom{(n-1)/2}{i-1}
\end{aligned}
$$
然后考虑 $i$ 为重心的答案 $g_i$，只要容斥掉重心在 $i$ 的子树 $j$ 中的方案数，容易发现 $j$ 的第一个 $\le i$ 祖先是均匀分布于 $[1,i]$ 中的，因此只要减去 $\dfrac {g_j}i$ 即可，维护后缀和即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+5,MOD=998244353;
int fac[MAXN],inv[MAXN],f[MAXN];
inline int ksm(int a,int b=MOD-2,int p=MOD) {
	int ret=1;
	while(b) ret=(b&1?ret*a%p:ret),a=a*a%p,b=b>>1;
	return ret;
}
inline int binom(int n,int m) {
	if(n<0||m<0||m>n) return 0;
	return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
}
signed main() {
	int n;
	scanf("%lld",&n);
	for(int i=fac[0]=1;i<=n;++i) fac[i]=fac[i-1]*i%MOD;
	inv[n]=ksm(fac[n]);
	for(int i=n;i>=1;--i) inv[i-1]=inv[i]*i%MOD;
	for(int i=n,sum=0;i>=1;--i) {
		f[i]=(fac[n-i]*fac[i-1]%MOD*binom((n-1)/2,i-1)%MOD+MOD-sum*ksm(i)%MOD)%MOD;
		sum=(sum+f[i])%MOD;
	}
	for(int i=1;i<=n;++i) printf("%lld ",f[i]);
	puts("");
	return 0;
}
```



---

## 作者：sgweo8ys (赞：3)

### 题目描述

给定奇数 $n$，对于每个 $i$ 求满足如下条件的树的个数

1. 有 $n$ 个点

2. 重心为 $i$

3. 对于所有的 $i \ge 2$，与 $i$ 相邻的点中有且仅有一个点编号比 $i$ 小

### 分析

首先说明一下重心的性质：

设将点 $i$ 作为根，$i$ 的最大子树大小是 $t_i$，则 $i$ 为重心等价于 $t_i$ 是序列 $t$ 中最小的数。

还有一个等价定义，即 $t_i \le \frac{n}{2}$ 。

重心要么有一个，要么有两个。

有两个重心时，这棵树节点个数一定是偶数，并且两个重心之间有边相连。

这些性质证明较为平凡，这里不再给出。

这道题的树有一个看起来很奇怪的性质：对于所有的 $i \ge 2$，与 $i$ 相邻的点中有且仅有一个点编号比 $i$ 小。

如果你有造过树的数据，看到这个描述应该会马上反应过来，它等价于：

**一棵以 $1$ 为根的树，每个点的父节点编号均比自己小**

所以对于一个节点 $i$，如果以 $i$ 为根，那么 $1$ ~ $i - 1$ 的所有节点全部在同一棵子树内。

这也就说明了为什么 $i > \frac{n + 1}{2}$ 时答案都是 $0$ 。

所以如果 $i$ 要是重心，那么树以 $1$ 为根时 $i$ 子树大小至少应该是 $\frac{n + 1}{2}$。

设满足 $i$ 子树大小至少是 $\frac{n + 1}{2}$ 的树的个数为 $f_i$，考虑计算 $f$。

设 $s = \frac{n + 1}{2}$ 我们有：

$$
f_i = 
\left\{ 
    \begin{array}{lc}
        (n - 1)! & i = 1 \\
        (i - 1)\sum\limits_{j = s - 1}^{n - i} \binom{n - i}{j} j! (n - j - 2)! & 2 \le i \le s \\
        0 & i \ge s + 1 \\
    \end{array}
\right.
$$

对于 $2\le i \le s$ 的情况，我们枚举 $i$ 子树的大小 （也就是 $j + 1$），将 $j$ 个点安插在 $i$ 子树上的方案是 $j!$ （因为第 $k$ 个点安放时 $i$ 子树已经有 $k$ 个节点了，所以父亲就有 $k$ 种可能）。

剩下 $n - i - j$ 个点放在子树外面方案就是 $(i - 1)^{\overline{n - i - j}}$ （组合解释与上面类似），最后乘上组合数，简单化简得到上式。

显然，满足上面条件的树不一定以 $i$ 为重心，他的重心还有可能在 $i$ 子树中。

我们不妨假设整棵树以 $i$ 为重心的方案数为 $a_i$。

那么当 $i$ 满足 $i$ 子树大小至少是 $s$ 但是重心是 $j(j>i)$ 时，这样的情况有 $\frac{a_j}{i}$ 种。

因为放第 $j$ 个点时，它到 $1$ 的路径上经过 $i$ 的概率是 $\frac{i}{1}$ （这个结论对 $j$ 用数学归纳法容易得到，这里不再证明）。

所以，我们有递推式：

$$
a_i = f_i - \sum_{j = i + 1}^{n} a_j
$$

如果我们从后往前枚举 $i$，后面的和式就可以用后缀和计算。

考虑如何计算 $f_i$，显然我们主要考虑 $2 \le i \le s$ 的部分，即

$$

\begin{aligned}

f_i &= (i - 1)\sum_{j = s - 1}^{n - i} \binom{n - i}{j} j! (n - j - 2)! \\
&= (n - i)!(i - 1)\sum_{j = s - 1}^{n - i} \frac{(n - j - 2)!}{(n - i - j)!}\\
&= (n - i)!(i - 1)! \sum_{j = s - 1}^{n - i} \binom{n - j - 2}{i - 2}\\
&= (n - 1)!(i - 1)! \sum_{j = i - 2}^{n - s - 1} \binom{j}{i - 2}\\
&= (n - 1)!(i - 1)!\binom{n - s}{i - 1}\\

\end{aligned}

$$

预处理阶乘及其逆元，暴力递推即可做到 $O(n)$。

有点搞不懂 std 为什么要用 NTT。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 200010;
const LL p = 998244353;

LL n, s, tmp, f[N], ans[N], fac[N], inv[N];

LL ksm(LL v, LL tms)
{
    LL res = 1;
    for(; tms; tms >>= 1, v = v * v % p) if(tms & 1) res = res * v % p;
    return res;
}

void pre(int mx)
{
    fac[0] = inv[0] = 1;
    for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % p;
    inv[mx] = ksm(fac[mx], p - 2);
    for(int i = mx - 1; i; i--) inv[i] = inv[i + 1] * (i + 1) % p;
}

LL c(LL n, LL m)
{
    if(n < m || m < 0) return 0;
    return fac[n] * inv[m] % p * inv[n - m] % p;
}

LL getinv(int x) { return inv[x] * fac[x - 1] % p; }

int main()
{
    cin >> n, s = (n + 1) >> 1;
    pre(n + 1);
    f[1] = fac[n - 1];
    for(int i = s + 1; i <= n; i++) f[i] = 0;
    for(int i = 2; i <= s; i++)
        f[i] = fac[n - i] * fac[i - 1] % p * c(n - s, i - 1) % p;

    for(int i = n; i >= 1; i--){
        ans[i] = (f[i] - tmp * getinv(i) % p + p) % p;
        tmp = (tmp + ans[i]) % p;
    }
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    puts("");
    return 0;
}
```

---

## 作者：OIerBoy (赞：2)

# Sol
首先我们需要处理一下如何去满足好树的条件。很容易想到，当我们定点 $1$ 为根节点时，每次让结点编号小的当结点编号大的父亲。这样我们就可以保证得到的树是一颗好树，同时能够证明这是不重不漏的。

然后我们考虑如何去判断点 $i$ 是重心。但这样很难，我们不妨把重心这个条件转换一下，变为点 $i$ 的子树大小 $\ge \dfrac{n+1}{2}$ 的方案数。这样转变有什么好处呢，好就是处由于小的结点是大的结点的父亲，我们确定了好树的重心是在点 $i$ 的子树内的，这样我们只需要容斥一下就可以得到答案了。

我们记 $f_i$ 表示以 $i$ 为根结点的子树大小 $\ge \dfrac{n+1}{2}$ 的方案数。然后我们就可以得到一个比较暴力的转移式：
$$f_i=\begin{cases}(n-1)! & i=1\\ \sum\limits_{j=\frac{n+1}{2}}^{n-i+1}C_{n-i}^{j-1}(n-j-1)!(j-1)!(i-1) & 1<i\le \frac{n+1}{2}\\0 & \frac{n+1}{2}< i\le n\end{cases}$$

主要解释一下当 $1<i\le \frac{n+1}{2}$ 时的情况，我们设当前子树内包括 $i$ 共有 $j$ 个结点，则子树外部就有 $n-j$ 个结点。对于子树中除了点 $i$ 的 $j-1$ 个结点可以在所有大于 $i$ 的点中选择，方案为 $C_{n-i}^{j-1}$。再考虑每一个结点连边的方案：

- 对于点 $i$ 可以连向点 $1\sim i-1$；

- 对于子树内的 $j-1$ 个点，编号第 $k$ 大的点就有 $j-k$ 个点可以连，总方案数就是 $(j-1)!$；

- 对于子树之外的 $n-j$ 个点，编号第 $k$ 大的点就有 $n-j-k$ 个点可以选择，总方案数为 $(n-j-1)!$。

这样合起来就是：
$$f_i=\sum\limits_{j=\frac{n+1}{2}}^{n-i+1}C_{n-i}^{j-1}(n-j-1)!(j-1)!(i-1)$$

对于 $i=1$ 和 $\dfrac{n+1}{2}<i\le n$ 的情况我们都可以 $O(1)$ 得到，但是对于 $1<i\le \frac{n+1}{2}$ 情况的时间复杂度是 $O(n)$ 的，我们接受不了，需要化简一下。

$$\begin{aligned}f_i= & \sum\limits_{j=\frac{n+1}{2}}^{n-i+1}C_{n-i}^{j-1}(n-j-1)!(j-1)!(i-1)\\= & \sum\limits_{j=\frac{n+1}{2}}^{n-i+1}\dfrac{(n-i)!(n-j-1)!(j-1)!(i-1)}{(j-1)!(n-i-j+1)!}\\= & \sum\limits_{j=\frac{n+1}{2}}^{n-i+1}\dfrac{(n-i)!(n-j-1)!(i-1)}{(n-i-j+1)!}\\= & \sum\limits_{j=\frac{n+1}{2}}^{n-i+1}\dfrac{(n-j-1)!(i-2)!(i-1)}{(n-i-j+1)!(i-2)!}(n-i)!\\= & \sum\limits_{j=\frac{n+1}{2}}^{n-i+1}\dfrac{(n-j-1)!}{(n-j-i+1)!(i+2)!}(n-i)!(i-1)!\\= & (n-i)!(i-1)!\sum\limits_{j=\frac{n+1}{2}}^{n-i+1}C_{n-j-1}^{n-i-j+1}\\= & C_{n-\frac{n+1}{2}}^{n-\frac{n+1}{2}-i+1}(n-i)!(i-1)!\end{aligned}$$

这样我们就可以 $O(1)$ 解决了 $f_i$。

然后考虑得到答案，即将 $f_i$ 中重心不为 $i$ 的点容斥掉。在这里的处理我对于其他的题解有少许的疑惑，但仔细的想了想发现是对的。

我们知道在 $i$ 的子树中的 $j$ 这个结点是一定对 $f_i$ 有贡献的，但其实这里的 $j$ 个结点是从 $n-i$ 个结点中随机挑选出来的，所以对于重心的祖先结点是均匀分布在 $[1,i]$ 之中的，对于 $f_i$ 的贡献是 $\dfrac{1}{i}$ 的。即 $ans_i=\dfrac{1}{i}f_i\sum\limits_{j=i+1}^nans_j$。简单的后缀和即可解决。

时间复杂度 $O(n)$。

# Code
```cpp
#include<bits/stdc++.h>
#define db double
#define inf LONG_LONG_MAX
#define fir first
#define sec second
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
#define Pr(i,j) pair<i,j>
#define PB(i) push_back(i)
#define MP(i,j) make_pair(i,j)
#define Fo(i,j) for(auto i:j)
#define mem(i,j) memset(i,j,sizeof(i))
#define FO(i,j,k) for(int i=j;i;i=k)
#define FFF(i,j,k) for(auto i=j;i!=k;++i)
#define For(i,j,k) for(int i=j;i<=k;++i)
#define FoR(i,j,k) for(int i=j;i^k;++i)
#define FOR(i,j,k) for(int i=j;i>=k;--i)
using namespace std;
template <typename _Tp>void read(_Tp& first) {
    _Tp x = 0, f = 1; char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ '0'), c = getchar();
    first = x * f;
}inline void write(int x){
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
#define N 200005
#define Mod 998244353
#define int long long
int n,m,sum;
int f[N],ans[N];
int fac[N],inv[N];
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%Mod;
		a=a*a%Mod;
		b>>=1;
	}return res;
}
void init(int n){
	fac[0]=1;
	For(i,1,n)fac[i]=fac[i-1]*i%Mod;
	inv[n]=ksm(fac[n],Mod-2);
	FOR(i,n,1)inv[i-1]=inv[i]*i%Mod;
}
signed main(){
	read(n);init(n+1);m=(n+1)>>1;f[1]=fac[n-1];
	For(i,2,m)f[i]=fac[n-i]*fac[n-m]%Mod*inv[n-i-m+1]%Mod;
	FOR(i,n,1){
		ans[i]=(f[i]-sum*ksm(i,Mod-2)%Mod+Mod)%Mod;
		sum+=ans[i];sum%=Mod;
	}
	For(i,1,n)write(ans[i]),putchar(' ');
	return 0;
}

```

---

## 作者：MatrixCascade (赞：2)

其实是 Centroid Probabilities。

题解区全是线性做法，菜鸡带 log 做法还推了很久 /kk

先考虑让题目简单点，一棵 $k$ 个点的树，根是 $1$，求 $1$ 的子树都不大于 $\frac n 2$ 的方案数。

想了想觉得直接算很麻烦，于是考虑容斥。答案显然是 $(n-1)!$ 减去有一棵子树大于 $\frac n 2$ 的方案数。

首先枚举超出的子树 $siz$ 大小($siz\in [\frac n 2 +1,k]$)，把这棵子树称作超重子树，然后选择在那棵子树上的点，这一部分方案数是 $\binom{k-1}{siz}$，接着考虑选出一部分点后别的点连边的方案数（这个我一开始以为要 dp 啥的，然后想了想发现很容易）。

先考虑超重子树，在超重子树内有 $siz$ 个点，其中编号最小的点必须强制连 $1$，剩下 $siz-1$ 个点，若他是第 $j$ 小的，可以连向超重子树中的第 $[1,j-1]$ 小的点，因此方案数是 $j-1$。合并起来就是 $(siz-1)!$ 种方案。

超重子树外有 $n-1-siz$ 个点。每个点可以连向一个超重子树外的一个比他小的点**或者** $1$，一起考虑就是 $(n-siz-1)!$ 种方案。

然后把这一部分整合起来，设 $f_k$ 为 $k$ 个点的树每棵子树 $siz$ 都不大于 $\frac n 2$ 的方案数，就是 $(k-1)!-\sum\limits_{j=\frac n 2+1}^{k-1}\binom{k-1}{j}\times(k-j-1)!\times(j-1)!$

~~貌似可以 ntt 求出每一项~~，展开柿子，$(k-1)!-\sum\limits_{j=\frac k 2+1}^{k-1}\frac{(k-1)!(j-1)!(k-j-1)!}{(j!)(k-j-1)!}$，能约分的全部约掉，得到 $f_k=(k-1)!-\sum\limits_{j=\frac n 2+1}^{k-1} \frac{(k-1)!}{j}=(k-1)!(1-\sum\limits_{j=\frac n 2+1}^{k-1} \frac{1}{j})$

你惊奇的发现，这玩意显然是可以线性或者$n\log$算的！然后考虑进一步去求每个点的答案。

设 $g_i$ 表示 $i$ 点是重心的方案数，首先这个点的 $siz$ 必须大于 $\frac n 2$，那么枚举 $siz$，再考虑他子树里面的店，显然是 $\binom{n-i}{siz-1}$ 种选法，然后考虑子树内的连边必须满足不存在超重子树，那就是 $f_i$ 种方案，然后类似的分析 $i$ 子树外的点仍然一样，$(n-siz-1)!$ 种选法，最后就是 $i$ 有 $(i-1)$ 种连边。

得出柿子：$g_i=\sum_{j=\frac n 2 +1}^{n-i+1} \binom{n-i}{j-1}  \times(i-1) \times (n-j-1)! \times f_j$，展开 $g_i=(i-1)\times\sum_{j=\frac n 2 +1}^{n-i+1} \frac{(n-i)!(n-j-1)!f_j}{(j-1)!(n-i-j+1)!}=(i-1)\times (n-i)!\times \sum_{j=\frac n 2 +1}^{n-i+1}\frac{(n-j-1)f_j}{(j-1)!(n-i-j+1)!}$ （不知道为什么莫名其妙用不了 `\limits`）

这个内部显然是一个卷积形式，ntt 即可。需要注意其中一个卷积数组下标并不是从 $0$ 开始的。

[代码](https://codeforces.com/contest/1667/submission/157651220)，用了自己恩塔塔板子就只放链接了。

---

## 作者：Purslane (赞：0)

# Solution

没有脑子的小朋友只能写 NTT 了。

显然一棵树是好树等价于能整理为一棵以 $1$ 为根的、指向编号较小节点的有根树。

$u$ 是重心的必要条件为，它的子树大小 $\ge \dfrac{n+1}{2}$。因此尝试计算这样的答案。不妨设这是 $i$ 号节点。（不妨设 $i \neq 1$）

答案为：

$$
\sum_{k=\frac{n-1}{2}}^{n-i} \binom{n-i}{k} \times k! \times (n-k-2)! \times (i-1)
$$

含义是：先钦定子树内的节点集合；然后子树内连边；再将整棵子树剥离，剩下的节点连边；最后将整棵子树挂在编号 $<i$ 的节点上。

展开发现这个显然可以写成卷积的形式，用 NTT 卷一下。因此设这个式子的结果是 $f_i$。

然后容斥，要减去有一棵子树的大小 $\ge \dfrac{n+1}{2}$。发现实际上就是

$$
f_i - \sum_{j>i} \dfrac{f_j}{j-1}
$$

做一遍后缀和即可。

复杂度 $O(n \log n)$。好想好调试。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=6e5+10,MOD=998244353;
int n,rev[MAXN],frac[MAXN],inv[MAXN],o[MAXN],f[MAXN],g[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
void ntt(int *f,int k,int op) {
	ffor(i,0,k-1) rev[i]=(rev[i>>1]>>1)|((i&1)*(k>>1));
	ffor(i,0,k-1) if(i<rev[i]) swap(f[i],f[rev[i]]);
	int lst=1,len=1;
	while(len<k) {
		lst=len,len<<=1;
		int omega=qpow(3,(MOD-1)/len);
		if(op==-1) omega=qpow(omega,MOD-2);
		ffor(i,0,k/len-1) {
			int l=i*len,r=l+len-1,tmp=1;
			ffor(j,l,l+lst-1) {
				int x=f[j],y=f[j+lst];
				f[j]=(x+tmp*y)%MOD,f[j+lst]=(x-tmp*y)%MOD,tmp=tmp*omega%MOD;	
			}
		}
	}
	if(op==-1) {
		int inv=qpow(k,MOD-2);
		ffor(i,0,k-1) f[i]=f[i]*inv%MOD;	
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n,frac[0]=1;
	ffor(i,1,n) frac[i]=frac[i-1]*i%MOD;
	inv[n]=qpow(frac[n],MOD-2);
	roff(i,n-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	ffor(k,(n-1)/2,n-2) f[k]=frac[n-k-2];
	ffor(i,0,n) g[i]=inv[i];
	ntt(f,1<<19,1),ntt(g,1<<19,1);
	ffor(i,0,(1<<19)-1) f[i]=f[i]*g[i]%MOD;
	ntt(f,1<<19,-1);
	o[1]=frac[n-1];
	ffor(i,2,n) o[i]=f[n-i]*frac[n-i]%MOD*(i-1)%MOD;
	int pre=0;
	roff(i,n,1) o[i]=(o[i]-pre)%MOD,pre=(pre+f[n-i]*frac[n-i])%MOD;
	ffor(i,1,n) cout<<(o[i]%MOD+MOD)%MOD<<' ';
	return 0;
}
```

---

## 作者：SDqwq (赞：0)

首先转化题意中的树为一棵以 $1$ 为根的，且每个点的父亲编号都比自己小的树。

由重心的定义可得，$siz_u\ge n-\frac{n-1}{2}=\frac{n+1}{2}$。后者是前者的必要条件。

考虑先满足这个必要条件。

设 $F(i,j)$ 表示 $siz_i=j$ 的方案数，可得：

$$
F(i,j)=\binom{n-i}{j-1}(j-1)!(n-j-1)!(i-1)
$$

每一项分别表示：$i$ 的子树里面有哪些点、$i$ 子树里的点选父亲的方案数、$i$ 子树外的点选父亲的方案数、$i$ 选父亲的方案数。

注意当 $i=1$ 时需要特殊考虑。

设 $f_i$ 表示$i$ 的子树大小 $\ge\frac{n+1}{2}$ 的方案数，则当 $i=1$ 时，$f_i=(n-1)!$，当 $i>1$ 时，有：

$$
\begin{aligned}
f_i&=\sum_{j=\frac{n+1}{2}}^nF(i,j)\\
&=\sum_{j=\frac{n+1}{2}}^n\frac{(n-i)!}{(j-1)!(n-i-j+1)!}(j-1)!(n-j-1)!(i-1)\\
&=\sum_{j=\frac{n+1}{2}}^n\frac{(n-j-1)!}{(n-i-j+1)!(i-2)!}(n-i)!(i-1)!\\
&=\sum_{j=\frac{n+1}{2}}^n\binom{n-j-1}{i-2}(n-i)!(i-1)!\\
&=(n-i)!(i-1)!\sum_{j=0}^{\frac{n-3}{2}}\binom{j}{i-2}\\
&=(n-i)!(i-1)!\binom{\frac{n-1}{2}}{i-1}
\end{aligned}
$$

现在再考虑 $i$ 的某一个儿子 $j$，当 $siz_j\ge\frac{n+1}{2}$ 时，$i$ 显然不是重心。且这样的 $j$ 最多只有 $1$ 个。

那么直接容斥。设 $g_i$ 表示 $i$ 为重心的方案数，则：

$$
g_i=f_i-\sum_{j=i+1}^n\frac{f_j}{j-1}
$$

其中 $\frac{1}{j-1}$ 表示 $i$ 是 $j$ 的父亲的概率。

维护 $\frac{f_i}{i-1}$ 的后缀和即可。时间复杂度 $\mathcal{O}(n)$。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 2e5 + 5;
const int mod = 998244353;

int ksm(int a, int k, int p) {
	int res = 1; a %= p;
	while (k) {
		if (k & 1) res = 1ll * res * a % p;
		a = 1ll * a * a % p, k >>= 1;
	}
	return res;
}
int inv(int a, int p) {return ksm(a, p - 2, p);}

int iv[N], fac[N], ifac[N];
int getC(int n, int m) {
	if (n < 0 || m < 0 || n < m) return 0;
	return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int f[N], sum[N];

int main() {
	int n;
	scanf("%d", &n);
	iv[1] = 1; for (int i = 2; i <= n; i++) iv[i] = 1ll * iv[mod % i] * (mod - mod / i) % mod;
	fac[0] = 1; for (int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n], mod); for (int i = n - 1; i >= 0; i--) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
	f[1] = fac[n - 1]; for (int i = 2; i <= n; i++) f[i] = 1ll * fac[n - i] * fac[i - 1] % mod * getC(n - 1 >> 1, i - 1) % mod;
	for (int i = n; i > 1; i--) sum[i] = (sum[i + 1] + 1ll * f[i] * iv[i - 1]) % mod;
	for (int i = 1; i <= n; i++) printf("%d ", (f[i] - sum[i + 1] + mod) % mod);
	return 0;
}
```

---

