# Abnormal Permutation Pairs (hard version)

## 题目描述

This is the hard version of the problem. The only difference between the easy version and the hard version is the constraints on $ n $ . You can only make hacks if both versions are solved.

A permutation of $ 1, 2, \ldots, n $ is a sequence of $ n $ integers, where each integer from $ 1 $ to $ n $ appears exactly once. For example, $ [2,3,1,4] $ is a permutation of $ 1, 2, 3, 4 $ , but $ [1,4,2,2] $ isn't because $ 2 $ appears twice in it.

Recall that the number of inversions in a permutation $ a_1, a_2, \ldots, a_n $ is the number of pairs of indices $ (i, j) $ such that $ i < j $ and $ a_i > a_j $ .

Let $ p $ and $ q $ be two permutations of $ 1, 2, \ldots, n $ . Find the number of permutation pairs $ (p,q) $ that satisfy the following conditions:

- $ p $ is lexicographically smaller than $ q $ .
- the number of inversions in $ p $ is greater than the number of inversions in $ q $ .

Print the number of such pairs modulo $ mod $ . Note that $ mod $ may not be a prime.

## 说明/提示

The following are all valid pairs $ (p,q) $ when $ n=4 $ .

- $ p=[1,3,4,2] $ , $ q=[2,1,3,4] $ ,
- $ p=[1,4,2,3] $ , $ q=[2,1,3,4] $ ,
- $ p=[1,4,3,2] $ , $ q=[2,1,3,4] $ ,
- $ p=[1,4,3,2] $ , $ q=[2,1,4,3] $ ,
- $ p=[1,4,3,2] $ , $ q=[2,3,1,4] $ ,
- $ p=[1,4,3,2] $ , $ q=[3,1,2,4] $ ,
- $ p=[2,3,4,1] $ , $ q=[3,1,2,4] $ ,
- $ p=[2,4,1,3] $ , $ q=[3,1,2,4] $ ,
- $ p=[2,4,3,1] $ , $ q=[3,1,2,4] $ ,
- $ p=[2,4,3,1] $ , $ q=[3,1,4,2] $ ,
- $ p=[2,4,3,1] $ , $ q=[3,2,1,4] $ ,
- $ p=[2,4,3,1] $ , $ q=[4,1,2,3] $ ,
- $ p=[3,2,4,1] $ , $ q=[4,1,2,3] $ ,
- $ p=[3,4,1,2] $ , $ q=[4,1,2,3] $ ,
- $ p=[3,4,2,1] $ , $ q=[4,1,2,3] $ ,
- $ p=[3,4,2,1] $ , $ q=[4,1,3,2] $ ,
- $ p=[3,4,2,1] $ , $ q=[4,2,1,3] $ .

## 样例 #1

### 输入

```
4 403458273```

### 输出

```
17```

# 题解

## 作者：Froggy (赞：38)

来一个非常暴力的做法。

~~地理学考的时候想的~~

---

看见排列还有字典序，一个显然的想法就是枚举排列 $p$ 和 $q$ 的最长公共前缀。

假设最长公共前缀是 $i$，那么再枚举 $p_{i+1}$ 和 $q_{i+1}$ 的值，满足 $p_{i+1}<q_{i+1}$，那么后面的就可以随便填了，后面可以看成是长度为 $n-i-1$ 的排列。

分别设 $p_{i+1}$ 和 $q_{i+1}$ 在最后 $n-i$ 个数的排名（从小到大排）是 $a$ 和 $b$；分别设 $p$ 和 $q$ 最后 $n-i-1$ 个数的逆序对数是 $t_p$ 和 $t_q$。

由于 $p$ 和 $q$ 前 $i$ 个数全一样，所以显然需要满足 $a+t_p>b+t_q$，即 $t_p-t_q\geq b-a+1$。

那么现在的问题就变成了求有多少对长度为 $n-i-1$ 的排列满足两个排列的逆序对的差为 $j$ $\ (j\in [1,n-i+1])$ 的方案数。

从小到大一个一个插到排列里，直接暴力 dp 是 $\mathcal{O}(n^4)$ 或者 $\mathcal{O}(n^5)$ 的。不妨考虑把生成函数写出来。

插入 $i$ 的生成函数显然是：

$$\begin{aligned}
&\left(\sum\limits_{j=0}^{i-1}x^j\right)\left(\sum\limits_{j=0}^{i-1}x^{-j}\right) \\
=& \frac{x^i-1}{x-1}\cdot\frac{x^{-i}-1}{x^{-1}-1} \\
=& \frac{x^{i+1}+x^{-i+1}-2x}{(x-1)^2}
\end{aligned}$$

暴力乘上分子，然后除以 $(x-1)^2$ 就相当于做两次回退背包。

时间复杂度：$\mathcal{O}(n^3)$。

***code：***

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 505
typedef long long ll;
const int B=251*501;
int n,mod,dp[2][N*N],ans,A[N];
int main(){
	n=read(),mod=read();
	A[0]=1;
	for(int i=1;i<=n;++i){
		A[i]=1LL*A[i-1]*(n-i+1)%mod;
	}
	dp[0][B]=1;
	#define update(x,y) x=(x+y)%mod
	for(int i=1;i<n;++i){
		memset(dp[i&1],0,sizeof(dp[i&1]));
		int C=(i+1)*(i+1)/2;
		for(int j=B-C;j<=B+C;++j){
			int w=dp[(i-1)&1][j];
			if(w){
				update(dp[i&1][j+i+1],w);
				update(dp[i&1][j-i+1],w);
				update(dp[i&1][j+1],1LL*(mod-2)*w);
			}
		}
		int zyk=2;
		while(zyk--){
			for(int j=B+C;j>=B-C;--j){
				update(dp[i&1][j],dp[i&1][j+1]);
			}
			for(int j=B-C;j<=B+C;++j)dp[i&1][j]=dp[i&1][j+1];
		}
		static int suf[N*N];
		for(int j=C;j>=0;--j){
			suf[j]=(suf[j+1]+dp[i&1][B+j])%mod;
		}
		for(int a=0;a<=i;++a){
			for(int b=a+1;b<=i;++b){
				update(ans,1LL*A[n-i-1]*suf[b-a+1]);		
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Alex_Wei (赞：26)

- Update on 2022.11.25：重写题解，原题解见 [剪贴板](https://www.luogu.com.cn/paste/g0t6nrny)

[CF1542E2 Abnormal Permutation Pairs (hard version)](https://www.luogu.com.cn/problem/CF1542E2)

考虑字典序的限制，枚举相同前缀长度 $L$，则 $p_{L + 1} < q_{L + 1}$。注意到 $p, q$ 前缀内部和对后缀的贡献相等，且我们不关心前缀的形态。所以最终方案数为 $p_{L + 1} < q_{L + 1}$ 且 $p_{L + 1}\sim p_n$ 和 $q_{L + 1} \sim q_n$ 均为 $n - L$ 阶排列的方案数，乘以安排 $p_1\sim p_L$ 的方案数 $\dbinom n L L!$。

因此，我们将问题转化为对每个 $m$，求 $m$ 阶排列对 $(p, q)$ 的数量，使得 $p_1 < q_1$ 且 $p$ 的逆序对数 $\pi(p)$ 严格大于 $q$ 的逆序对数 $\pi(q)$。

考虑 DP，设 $f_{i, j}$ 表示 $i$ 阶排列对 $(p, q)$ 的数量，使得 $\pi(p) - \pi(q) = j$。转移考虑将 $p_1$ 和 $q_1$ 分别插入到 $i - 1$ 阶排列的开头，$p_1$ 对 $\pi(p)$ 产生 $p_1 - 1$ 贡献，$q_1$ 对 $\pi(q)$ 产生 $q_1 - 1$ 贡献，得到转移式
$$
f_{i, j} = \sum\limits_{p_1 = 1} ^ {i} \sum\limits_{q_1 = 1} ^ i f_{i - 1, j - p_1 + q_1}
$$
此外，需要对所有 $j > 0$ 求出
$$
\sum\limits_{p_1 = 1} ^ i \sum\limits_{q_1 = p_1 + 1} ^ i f_{i - 1, j - p_1 + q_1}
$$
之和，再乘以 $\dbinom n {n - i} (n - i)!$ 贡献至答案。

考虑优化转移。注意到我们只关心 $p_1 - q_1$，所以直接枚举 $d = p_1 - q_1$，则
$$
f_{i, j} = \sum\limits_{|d| < i} f_{i - 1, j - d} (i - |d|)
$$
对 $d < 0$ 和 $d\geq 0$ 分类讨论，并将 $d < 0$ 的 $d$ 取反，有
$$
f_{i, j} = \sum\limits_{d = 1} ^ {i} f_{i - 1, j + d} (i - d) + \sum\limits_{d = 0} ^ {i - 1} f_{i - 1, j - d} (i - d)
$$
考虑加号前面的部分，它刚好需要贡献至答案，我们来推一遍式子。对于加号后的部分可类似推导。
$$
\begin{aligned}
& \sum\limits_{d = 1} ^ {i} i f_{i - 1, j + d} - \sum\limits_{d = 1} ^ {i} d f_{i - 1, j + d} \\
& \sum\limits_{d = 1} ^ {i} (i + j) f_{i - 1, j + d} - \sum\limits_{d = 1} ^ {i} (j + d) f_{i - 1, j + d}
\end{aligned}
$$
直接维护 $f_{i, j}$ 和 $jf_{i, j}$ 关于 $j$ 的前缀和即可，时间复杂度 $\mathcal{O}(n ^ 3)$。[代码](https://codeforces.com/contest/1542/submission/182436782)。

---

## 作者：I_am_Accepted (赞：15)

什么？你不会题解区的生成函数？

什么？你不会题解区的 DP 大优化？

看这里——

由于某些特殊的原因，此题被本蒟蒻优雅地解决了。

### 题目分析

为方便，满足如下条件的 $p.q$ 称为**逆序排列对**：

* $p$ 的字典序小于 $q$。

* $p$ 的逆序对个数 严格大于 $q$。

而单个排列内部的数的逆序对称为**逆序数对**。

显然，总共的排列有 $500!=1.22\times 10^{1136}$，所以不可能枚举 $(500!)^2$ 算逆序排列对。

由于明显的 $O(n^3)$，直接想到 DP。

我们先小数据打表（以下为长度为 $4$ 的排列按字典序排序）：

![](https://cdn.luogu.com.cn/upload/image_hosting/38q7aggz.png)

发现她们的逆序数对数量的图为同样的波形复制 $4$ 份然后逐个 $+1$。

我们称每一个同样的波形为**块**。

其实这很好理解：

设当前排列长度为 $k$。

* 当排列的首项为 $1$ 时，逆序数对数量就是剩下 $k-1$ 个数的逆序数对数量

* 当排列的首项为 $2$ 时，逆序数对数量就是剩下 $k-1$ 个数的逆序数对数量加上首项的 $2$ 与后面的 $1$ 构成的 $1$ 个逆序对。

* 当排列的首项为 $3$ 时，逆序数对数量就是剩下 $k-1$ 个数的逆序数对数量加上首项的 $3$ 与后面的 $1$ 和 $2$ 构成的 $2$ 个逆序对。

* ……

* 当排列的首项为 $k$ 时，逆序数对数量就是剩下 $k-1$ 个数的逆序数对数量加上首项的 $k$ 与后面的 $1$ 到 $(k-1)$ 构成的 $k-1$ 个逆序对。

有了这个结论，剩下的就很好想了。

假设当前要求长度为 $n$ 的排列的全体的逆序排列对（写成函数 `work(n)`）。

先调用 `work(n-1)`，即求单个块内的逆序排列对数量，将这个数乘 $n$，就得到了所有块内的逆序排列对数量。

然后只剩下块与块之间的逆序排列对要统计了。

考虑到此时块内的顺序已经不重要了，可将单个块内的逆序数对数量开一个**桶**，由于这 $n$ 个块的桶相似（只是有偏移量），我们只存第一个块的桶（即当前长度为 $n$ 的排列的首项为 $1$ 的那些），记为 $a_i$，表示逆序数对数量为 $i$ 的排列有几个。

考虑怎样求块与块之间的逆序排列对的数量。若有一对排列分别在第 $i,j\quad (1\leqslant i<j\leqslant n)$ 块中，则她们是逆序排列对的充要条件是（（前面的排列）的（逆序数对数量））大于（（后面的排列）的（逆序数对数量））

然而她们之间有 $j-i$ 的偏移量，所以总共的块与块之间的逆序排列对数量为：

$$\sum\limits_{1\leqslant i<j\leqslant n}{\sum\limits^{C_n^2}_{k=0}\left(a_k\times\sum\limits^{k-1-(j-i)}_{kk=0}a_{kk}\right)}$$

别说你被这公式吓到了……（后面有例子）

然后各种前后缀优化即可在 $O(n^2)$ 内算出答案（具体看代码）。

然后考虑如何转移至 `work(n+1)`，即如何更新 $\{a\}$。

由于：

逆序数对数量为 $x$ 的会在第 $1$ 块中逆序数对数量为 $x$。

逆序数对数量为 $x-1$ 的会在第 $2$ 块中逆序数对数量为 $x$。

逆序数对数量为 $x-2$ 的会在第 $3$ 块中逆序数对数量为 $x$。

……

逆序数对数量为 $x-n+1$ 的会在第 $n$ 块中逆序数对数量为 $x$。

所以：

$$new\_a_i=\sum\limits^{i}_{j=i-n+1}a_j$$

可以前缀和优化至 $O(n^2)$

总共 $O(n^2)$ 乘上 $O(n)$ 的递归，为 $O(n^3)$。

### Detail

注意边界条件，谢谢。

还有数组要开够（本人 $250000$ 的数组开了 $25000$ 硬是没查出来 qwq）。

### Code

[超级超级短的代码](https://codeforces.com/contest/1542/submission/136031085)（主体 $21$ 行）

### Example

当前 `work(4)`。

先 `work(3)`，答案为 $0$，乘 $4$ 后加入 $res$。同时传来 $\{a\}$：

![](https://cdn.luogu.com.cn/upload/image_hosting/bomntz2q.png)

再把这张图拿来：

![](https://cdn.luogu.com.cn/upload/image_hosting/38q7aggz.png)

枚举字典序小的排列的逆序数对对数：

以下跨度指两个所在块的编号之差。

若是 $a_0$（注意是 $a_0$ 而不指 $0$，下同）：

枚举跨度，发现都没有 qwq。

若是 $a_1$：

枚举跨度，发现都没有 qwq。

若是 $a_2$：

枚举跨度，发现跨度为 $1$ 时左边的 $a_2$ 和右边的 $a_0$ 满足，将 $3\times a_2 \times a_0=6$ 加入 $res$。

若是 $a_3$：

枚举跨度，发现跨度为 $2$ 时左边的 $a_3$ 和右边的 $a_0$ 满足，将 $2\times a_3 \times a_0=2$ 加入 $res$。发现跨度为 $1$ 时左边的 $a_3$ 和右边的 $a_0$ 或 $a_1$ 满足，将 $3\times a_3 \times (a_0+a_1)=9$ 加入 $res$。

总共 $res=17$ 为 $n=4$ 的答案。

最后更新 $\{a\}$（建议看图）：

$new\_a_0=1(1+0+0+0)$ 只有第 $1$ 块有 $1$ 个。

$new\_a_1=3(2+1+0+0)$ 第 $1$ 块有 $2$ 个、第 $2$ 块有 $1$ 个。

$new\_a_2=5(2+2+1+0)$ 第 $1$ 块有 $2$ 个、第 $2$ 块有 $2$ 个、第 $3$ 块有 $1$ 个。

$new\_a_3=6(1+2+2+1)$

$new\_a_4=5(0+1+2+2)$

$new\_a_5=3(0+0+1+2)$

$new\_a_6=1(0+0+0+1)$

还不懂的私信我！！！我就不信了 qwq。

---

## 作者：Crab_Dave (赞：13)

upd on 2022/11/19：修正若干细节，祝阅读愉快。

# CF1542E 题解

+ ### 题意

  给出 $n$ 和 $mod$，求有多少个排列 $p,q$ 满足：

  1. $p$ 的字典序比 $q$ 小
  2. $p$ 的逆序对个数比 $q$ 大

  $n \le 500$，答案对 $mod$ 取模

+ ### 闲扯

  建议改为 【模板】前缀和优化dp（

  这篇题解的做法没有用到任何性质和找规律，将一个 $O(n^7)$ 的dp优化到了 $O(n^3)$

  ~~然而神yhp和zxjk写得又短又简单吊打这个sb思路~~

  感谢 yijan 和 yhp 给予关键的两次提示

+ ### 题解

  首先看到 $O(n^3)$ 和逆序对联想到一个很经典的trick：

  我们设 $dp[i][j]$ 表示$1-i$ 的排列中逆序对个数为 $j$ 的方案数 

  然后 $dp[i][j]$ 从 $\sum\limits_{k=j-(i-1)}^{j} dp[i-1][k]$ 转移过来

  这是一段连续的区间，前缀和优化掉即可 $O(n^3)$ 解决

  那么长为 $n$ 以 $i$ 开头的逆序对个数为 $j$ 的排列有 $dp[n-1][j-(i-1)]$ 个

  我们首先枚举 $p$ 的首位和 $q$ 的首位，然后再枚举 $p$ 的逆序对个数和 $q$ 的逆序对个数，然后让长为 $N$ 的答案加上长为 $N-1$ 的答案（把 $N$ 这个数插到 $p,q$ 首端），这样可以得到一个 $O(n^7)$ 的dp：

  ```cpp
  rep(N,4,n){
  	rep(i,1,N)rep(p,i+1,N)
  		rep(j,i-1,N*(N-1)/2)rep(q,0,j-p)
  			ans[N]=(ans[N]+1ll*dp[N-1][j-(i-1)]*dp[N-1][q]%mod)%mod;
  	ans[N]=(ans[N]+ans[N-1]*N%mod)%mod;
  }
  ```

  考虑优化这个dp。

  首先 $dp[N-1][q]$ 是一段连续的区间，可以前缀和优化，我们记 $g[i]$ 表示 $dp[N-1][i]$ 的前缀和然后优化掉这一维。$->O(n^5)$

  ```cpp
  rep(N,4,n){
  	rep(i,1,N)rep(p,i+1,N)
  		rep(j,i-1,N*(N-1)/2)
  			if(j>=p)ans[N]=(ans[N]+1ll*dp[N-1][j-(i-1)]*g[j-p]%mod)%mod;
  	ans[N]=(ans[N]+ans[N-1]*N%mod)%mod;
  }
  ```

  到这里卡了一下壳：我们到底是把 $j$ 这一维优化掉呢，还是把 $i,p$ 这两维优化掉呢？

  我们选择优化后者。

  为什么？

  ~~因为尝试优化 $j$ 失败了~~

  因为 $g[i]$ 的定义域是 $n^2$ 级别的，我们再维护其他前缀和也要是 $n^2$ 级别才方便前缀和相套，那么显然 $j$ 这一维非留不可。

  现在决定优化 $p$ 这一维，于是我们把 $p$ 这一维循环的枚举放到里面：

  ```cpp
  rep(N,4,n){
  	rep(i,1,N)rep(j,i+1,N*(N-1)/2)
          rep(p,i+1,min(j,N))
  			ans[N]=(ans[N]+1ll*dp[N-1][j-(i-1)]*g[j-p]%mod)%mod;
  	ans[N]=(ans[N]+ans[N-1]*N%mod)%mod;
  }
  ```

  不难看出 $p$ 的枚举是 $[i+1,min(j,N)]$ 的一段连续区间。

  对 $g[i]$ 维护前缀和 $w[i]$，我们即可去掉 $p$ 这一维：

  ```cpp
  rep(N,4,n){
  	rep(i,1,N)rep(j,i+1,N*(N-1)/2)
  		ans[N]=(ans[N]+1ll*dp[N-1][j-(i-1)]*(w[j-(i+1)]-(j>N?w[j-N-1]:0)+mod)%mod)%mod;
  	ans[N]=(ans[N]+1ll*ans[N-1]*N%mod)%mod;
  }
  ```

  我们尝试效仿刚才的做法，将 $i$ 这一维换到里面：

  ```cpp
  rep(N,4,n){
  	rep(j,2,N*(N-1)/2)rep(i,1,min(N,j-1))
  		ans[N]=(ans[N]+1ll*dp[N-1][j-(i-1)]*(w[j-(i+1)]-(j>N?w[j-N-1]:0)+mod)%mod)%mod;
  	ans[N]=(ans[N]+1ll*ans[N-1]*N%mod)%mod;
  }
  ```

  这里我们发现了一点小问题，这个式子里有两项和 $j-i$ 有关系可以一起处理，可是剩一项只和 $j$ 有关系，我们无法把它们丢到同一个前缀和预处理里。

  其实是思维僵化了。

  我们记那串三目运算符为 $h(j)$，然后把式子写成求和形式：
  $$
  \sum\limits_{j=2}^{N*(N-1)/2} \sum\limits_{i=1}^{min(N,j-1)} dp[N-1][j-(i-1)]*(w[j-(i+1)]-h(j))
  $$
  然后脑筋急转弯，把括号拆开（感觉智商被侮辱了：
  $$
  \sum\limits_{j=2}^{N*(N-1)/2} \sum\limits_{i=1}^{min(N,j-1)} dp[N-1][j-(i-1)]*w[j-(i+1)]-dp[N-1][j-(i-1)]*h(j)
  $$
  不难发现 $h(j)$ 这个东西完全可以提到两个 $\sum$ 中间，那我们维护 $o[i]=dp[N-1][i]*w[i-2]$ 即可。

  还有一件事：**前缀和的枚举到 $N*(N-1)/2$ 而非 $(N-1)*(N-2)/2$，不然你考虑定义域**。

  ```cpp
  rep(N,4,n){
  	g[0]=dp[N-1][0];rep(i,1,N*(N-1)/2)g[i]=(g[i-1]+dp[N-1][i])%mod;
  	w[0]=g[0];rep(i,1,N*(N-1)/2)w[i]=(w[i-1]+g[i])%mod;
  	o[0]=o[1]=0;rep(i,2,N*(N-1)/2)o[i]=(o[i-1]+1ll*dp[N-1][i]*w[i-2]%mod)%mod;
  	rep(j,2,N*(N-1)/2)ans[N]=(ans[N]+(o[j]-(j>N?o[j-N]:0)+mod)%mod)%mod;
  	rep(j,2,N*(N-1)/2){
  		int sum=(g[j]-(j>N?g[j-N]:g[1])+mod)%mod;
  		ans[N]=(ans[N]+1ll*sum*(-(j>N?w[j-N-1]:0)+mod)%mod)%mod;
  	}
  	ans[N]=(ans[N]+1ll*ans[N-1]*N%mod)%mod;
  }
  ```

+ ### 完整代码

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  
  #define rep(x,l,r) for(int x=(l);x<=(r);++x)
  #define per(x,r,l) for(int x=(r);x>=(l);--x)
  const int maxn=505;
  int n,mod,dp[maxn][maxn*maxn/2],sum[maxn*maxn/2],g[maxn*maxn/2],w[maxn*maxn/2],o[maxn*maxn/2],ans[maxn];
  //dp[i][j]表示1-i的排列中逆序对个数为j的方案数 
  //以i开头的逆序对个数为j的排列有 dp[n-1][j-(i-1)] 个 
  
  int read(){
  	int res=0,f=1;char ch;
  	do{ch=getchar();if(ch=='-')f=-1;}while(!isdigit(ch));
  	do{res=res*10+ch-'0';ch=getchar();}while(isdigit(ch));
  	return res*f;
  }
  
  signed main(){
  	n=read();mod=read();sum[0]=1;
  	rep(i,1,n){
  		rep(j,0,i*(i-1)/2){
  //			rep(k,0,i-1)dp[i][j]=(dp[i][j]+dp[i-1][j-k])%mod;
  			if(j-i>=0)dp[i][j]=(sum[j]-sum[j-i]+mod)%mod;
  			else dp[i][j]=sum[j];
  		}
  		sum[0]=dp[i][0];
  		rep(j,1,i*(i+1)/2)sum[j]=(sum[j-1]+dp[i][j])%mod;
  	}
  //	rep(N,4,n){
  //		rep(i,1,N)rep(p,i+1,N)
  //			rep(j,i-1,N*(N-1)/2)rep(q,0,j-p)
  //				ans[N]=(ans[N]+1ll*dp[N-1][j-(i-1)]*dp[N-1][q]%mod)%mod;
  //		ans[N]=(ans[N]+ans[N-1]*N%mod)%mod;
  //	}
  	rep(N,4,n){
  		g[0]=dp[N-1][0];rep(i,1,N*(N-1)/2)g[i]=(g[i-1]+dp[N-1][i])%mod;
  		w[0]=g[0];rep(i,1,N*(N-1)/2)w[i]=(w[i-1]+g[i])%mod;
  		o[0]=o[1]=0;rep(i,2,N*(N-1)/2)o[i]=(o[i-1]+1ll*dp[N-1][i]*w[i-2]%mod)%mod;
  		rep(j,2,N*(N-1)/2){
  			ans[N]=(ans[N]+(o[j]-(j>N?o[j-N]:0)+mod)%mod)%mod;
  //			per(i,min(N,j-1),1)ans[N]=(ans[N]+1ll*dp[N-1][j-(i-1)]*w[j-(i+1)]%mod)%mod;
  		}
  		rep(j,2,N*(N-1)/2){
  			int sum=(g[j]-(j>N?g[j-N]:g[1])+mod)%mod;
  //			sum=0;
  //			per(i,min(N,j-1),1)sum=(sum+dp[N-1][j-(i-1)])%mod;
  			ans[N]=(ans[N]+1ll*sum*(-(j>N?w[j-N-1]:0)+mod)%mod)%mod;
  		}
  		ans[N]=(ans[N]+1ll*ans[N-1]*N%mod)%mod;
  	}
  	printf("%d\n",ans[n]);
  }
  ```

  

---

## 作者：Pengzt (赞：7)

[CF1542E2](https://www.luogu.com.cn/problem/CF1542E2)

首先时间复杂度肯定是 $\mathcal{O}(n^3)$ 的。

容易想到先枚举最长公共前缀，然后枚举 $p_{len+1}$ 和 $q_{len+1}$，再枚举逆序对数进行统计。

令 $f_{i,j}$ 表示有 $j$ 个逆序对的 $i$ 阶排列的个数。

易得转移 $f_{i,j}=\sum\limits_{k=\max(j-i+1,0)}^{j}f_{i-1,k}$，使用前缀和可以做到 $\mathcal{O}(n^3)$。

此时第一个数为 $i$ 且逆序对数为 $j$ 的 $n$ 阶排列的个数显然为 $f_{n-1,j-i+1}$。

则答案可表示为

$$\sum\limits_{len=4}^{n}\dfrac{n!}{(n-len)!}(\sum\limits_{x=1}^{len-1}\sum\limits_{y=x+1}^{len}\sum\limits_{i=x+1}^{x+1+(len-1)(len-2)/2}\sum\limits_{j=y-1}^{i-1}f_{len-1,i-x+1}\times f_{len-1,j-y+1})$$

默认 $0!=1$，这是 $\mathcal{O}(n^7)$ 的。

将式子稍微转化一下：

$$\sum\limits_{len=4}^{n}\dfrac{n!}{(n-len)!}(\sum\limits_{x=1}^{len-1}\sum\limits_{y=x+1}^{len}\sum\limits_{i=x+1}^{x+1+(len-1)(len-2)/2}f_{len-1,i-x+1}\times (\sum\limits_{j=0}^{i-y}f_{len-1,j}))$$

用前缀和可优化至 $\mathcal{O}(n^5)$。

令 $g_{i,j}=\sum\limits_{k=0}^{j}f_{i,k}$。

用 $g$ 替代：

$$\sum\limits_{len=4}^{n}\dfrac{n!}{(n-len)!}(\sum\limits_{x=1}^{len-1}\sum\limits_{y=x+1}^{len}\sum\limits_{i=y}^{x+1-(len-1)(len-2)/2}f_{len-1,i-x+1}\times g_{len-1,i-y})$$

直接看是不能再优化了，考虑交换一下后两个 $\Sigma$ 的位置，并提出 $f_{len-1,i-x+1}$，变为：

$$\sum\limits_{len=4}^{n}\dfrac{n!}{(n-len)!}(\sum\limits_{x=1}^{len-1}\sum\limits_{i=x+1}^{x+1+(len-1)(len-2)/2}f_{len-1,i-x+1}\times(\sum\limits_{y=x+1}^{\min(i,n)}g_{len-1,i-y})$$

发现可以继续使用前缀和优化。

再变一下：

$$\sum\limits_{len=4}^{n}\dfrac{n!}{(n-len)!}(\sum\limits_{x=1}^{len-1}\sum\limits_{i=x+1}^{x+1+(len-1)(len-2)/2}f_{len-1,i-x+1}\times\sum\limits_{y=i-min(i,n)}^{i-x-1}g_{len-1,y})$$

令 $h_{i,j}=\sum\limits_{k=0}^{j}g_{i,k}$，带入原式：

$$\sum\limits_{len=4}^{n}\dfrac{n!}{(n-len)!}(\sum\limits_{x=1}^{len-1}\sum\limits_{i=x+1}^{x+1+(len-1)(len-2)/2}f_{len-1,i-x+1}\times (h_{len-1,i-x-1}-h_{len-1,i-len-1}\times[i>len]))$$

时间复杂度降至 $\mathcal{O}(n^4)$，此时已可通过 E1。

参考上一个方法，交换 $x,i$ 的 $\Sigma$，先不看前面 $len$ 的枚举，同时改变一下 $i$ 的上限方便转化，变为

$$\sum\limits_{x=1}^{n-1}\sum\limits_{i=x+1}^{len(len+1)/2}f_{len-1,i-x+1}\times (h_{len-1,i-x-1}-h_{len-1,i-len-1}[i>len])$$

交换 $i,x$

$$\sum\limits_{i=2}^{len(len+1)/2}\sum\limits_{x=1}^{\min(i,len)-1}f_{len-1,i-x+1}\times (h_{len-1,i-x-1}-h_{len-1,i-len-1}[i>len])$$

但这次好像没什么用，不妨先将后面与 $h$ 有关的判断用函数 $H(i,j)$ 替代。

$$\sum\limits_{i=2}^{len(len+1)/2}\sum\limits_{x=1}^{\min(i-1,len)}f_{len-1,i-x+1}\times(h_{len-1,i-x-1}-H(len-1,i))$$

拆开括号

$$\sum\limits_{i=2}^{len(len+1)/2}\sum\limits_{x=1}^{\min(i-1,len)}f_{len-1,i-x+1}\times h_{len-1,i-x-1}-f_{len-1,i-x+1}\times H(len-1,i)$$

提出 $H$

$$\sum\limits_{i=2}^{len(len+1)/2}\sum\limits_{x=1}^{\min(i-1,len)}f_{len-1,i-x+1}\times h_{len-1,i-x-1}-H(len-1,i)\times\sum\limits_{x=1}^{\min(i-1,len)}f_{len-1,i-x+1}$$

发现 $f,h$ 的第二维只相差 $2$，可以直接处理出来，后面的 $f$ 可以用 $g$ 来替代。

定义 $s_{i,j}=\left\{
\begin{aligned}
0 (j<2)\\
\sum\limits_{k=2}^{j}h_{i,k-2}\times f_{i,k}(j\ge 2)
\end{aligned}
\right.
$

故最终式子为

$$\sum\limits_{i=2}^{len(len+1)/2}s_{len-1,i}-s_{len-1,i-len}[i\ge len]-H(len-1,i)\times(g_{len-1,i}-g_1[i\le len]-g_{len-1,i-len}[i>len])$$

显然这里的时间复杂度为 $\mathcal{O}(n^2)$。

空间若全开 $\mathcal{O}(n^3)$ 是不能过的，可以只将 $f$ 开为三维，当然也可以使用滚动数组降为 $\mathcal{O}(n^2)$。

时间复杂度：$\mathcal{O}(n^3)$。

空间复杂度：$\mathcal{O}(n^2)$。


---

## 作者：lzytag (赞：7)

# 题解
良心题解求过QWQ。

[题目链接](https://www.luogu.com.cn/problem/CF1542E2)

首先，我们看数据范围，$n\le500$。

所以很显然，算法是$O(n^3)$的。

看到$O(n^3)$和逆序对，我们不禁想到了一个十分经典的问题。

$d_{i,j}$表示在$i$个数的排列中，有$j$个逆序对的排序个数。

很显然，枚举排序的第一位$k$，可以得到状态转移方程：

$d_{i,j} = \sum_{k = 1}^n d_{i-1,j-k-1}$

状态为$O(n^3)$，转移为$O(n)$，总复杂度为$O(n^4)$。

而这个动规可以优化到$O(n^3)$。

我们设$ds_{i}$为$d_i$的前缀和数组（一维前缀和）。

上述方程可以简化为：

- $j>=i$ 时 $d_{i,j} = ds_{i-1,j} - ds_{i-1,j-i}$
- $j<i$ 时$d_{i,j} = ds_{i-1,j}$

以上就是本题的预处理内容，而接下来的推导，才是本题的精髓。

## $O(n^7)$

我们可以想到用递推的方式解决这道题。

首先，我们设$dp_i$为本题长度为$i$时的方案数。

从$dp_{n-1}$到$dp_n$有两种情况。

当$p_n=q_n$ 有$dp_{n-1}*n$种情况。

当$p_n<q_n$ 先枚举$p_n$，再枚举$q_n$ ,再枚举$p$的逆序对数$nump$，再枚举$q$的逆序对数$numq$，得到如下多种情况：

$\sum_{a=1}^n\sum_{b=a+1}^n\sum_{nump=a-1}^{a-1+(n-2)*(n-1)/2}\sum_{numq=b-1}^{nump-1}d_{n-1,nump-(a-1)}*d_{n-1,numq-(b-1)}$

这个式子中$a$即$p_n$，$b$即$q_n$,在以后的式子中我也会如此代替。

这个$O(n^7)$的做法显然无法通过，但他是我们以后所有推导的基础。

## $O(n^5)$

我们发现，在以上的式子中，他的最后一个求和可以利用前缀和优化掉。

所以我们得到了$O(n^5)$的方法：

$\sum_{a=1}^n\sum_{b=a+1}^n\sum_{nump=b}^{a-1+(n-2)*(n-1)/2}d_{n-1,nump-(a-1)}*ds_{n-1,nump-b}$

注意，由于$q_n=b$时$q_n$就产生了$b-1$个逆序对，所以$nump$最小取b。

## $O(n^4)$

我们再仔细观察一下前面的式子，我们要再继续优化，我们要把它从$O(n^5)$优化到$O(n^3)$要么优化掉$a$和$b$，要么优化掉$nump$，$nump$在式子中出现了很多次，不好优化，考虑优化$a$和$b$。

先优化b，首先把b提到最内层：

$\sum_{a=1}^n\sum_{nump=a+1}^{a-1+(n-2)*(n-1)/2}\sum_{b=a+1}^{min(nump,n)}d_{n-1,nump-(a-1)}*ds_{n-1,nump-b}$

我们突然间发现最后一项$ds_{n-1,nump-b}$也可以用前缀和优化!

设$dss_i$为$ds_i$的前缀和（也是一维）。

~~禁止套娃~~。

于是式子就变成了这副样子：

$\sum_{a=1}^n\sum_{nump=a+1}^{a-1+(n-2)*(n-1)/2}F(a)$

其中：

$$
F(a)=
\begin{cases}
d_{n-1,nump-(a-1)}*dss_{n-1,nump-a-1}, & nump \le n\\[2ex]
d_{n-1,nump-(a-1)}*(dss_{n-1,nump-a-1}-dss_{n-1,nump-n}),&nump>n
\end{cases}
$$

## $O(n^3)$

~~(啊我真的吐了优化到$O(n^4)$的式子长得就够奇特了还要让我把他优化到$O(n^3)$)~~

本步优化是本方法最难想到的一步了。

首先观察$F(a)$的两种情况，他们的第一项长得一样，而且有一个非常有意思的特点，都形如：

$d_{n-1,k+2}*dss_{n-1,k}$

其中$k=nump-a$。

我们设$f_{n-1,k} = d_{n-1,k+2}*dss_{n-1,k}$。

那$fs_i$就为$f_i$的前缀和 ~~（还来）~~。

而第二种情况的第二项，我们发现他们的一个乘数是一样的，另一个乘数也可以用前缀和求和。

所以我们提取公因数，就能把他算出来了。

最后，让我们先把$a$提到最内层循环。

原式变成：

$\sum_{nump=2}^{n*(n-1)/2}\sum_{a=1}^{min(sum-1,n)}F(a)$

再变形成：

$\sum_{nump=2}^{n*(n-1)/2}G(a)$

其中

$$
G(a) = 
\begin{cases}
fs_{n-1,nump-2}, & nump<=n\\[2ex]
fs_{n-1,nump-2}-fs_{n-1,nump-n-1}-dss_{n-1,nump-n-1}*(ds_{n-1,nump}-ds_{n-1,nump-i-1}),&nump>n
\end{cases}
$$

## 最后一个小问题
这样开可能会MLE。

这时，我们发现，所有$d$,$ds$,$dss$,$fs$的第一个下标均为$n-1$。

既然这样，那我们就可以隐藏这四个数组的第一维，随着$dp$的更新重新计算他们的值。

上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pii pair<int,int>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define vec vector
#define que queue
#define deq deque
#define prq priority_queue
#define sta stack
#define fuck return
#define ccf 0
#define CodeForces 0
#define mkp make_pair
#define fir first
#define sec second
#define bslow lower_bound
#define bsup upper_bound
#define mst memset
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define For(i,j,k) for(int (i)=(j);(i)<=(k);(i)++)
#define DFor(i,j,k) for(int (i)=(k);(i)>=(j);(i)--)
#define pb push_back
int read()
{
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)) f|=ch=='-',ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
ll lread()
{
	ll x=0,f=0;char ch=getchar();
	while(!isdigit(ch)) f|=ch=='-',ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
//file head over
#define MaxN 505
#define MaxC 125005
int d[MaxC],dp[MaxN],n,Mod;
int ds[MaxC],dss[MaxC],fs[MaxC];
int fun(int x)//代表n个数的排列最多fun(n)个nxd 
{
	return x*(x-1)/2;
}
int work(int k)
{
	return 1ll*dss[k]*d[k+2]%Mod;
}
int main()
{
	n = read();
	Mod = read();
	For(i,1,n)
	{
		if(i>=4)//当i<=3时 dp[i] = 0(手算可得)
		{
			//upd dp[i]
			/*For(j,0,fun(i)) cout<<d[j]<<' ';
			cout<<endl;
			For(j,0,fun(i)) cout<<ds[j]<<' ';
			cout<<endl;
			For(j,0,fun(i)) cout<<dss[j]<<' ';
			cout<<endl;
			For(j,0,fun(i)) cout<<fs[j]<<' ';
			cout<<endl;*/
			dp[i] = 1ll*dp[i-1]*i%Mod;//p[i] = q[i]
			For(num,2,fun(i))//num:p总nxd个数
			{
				if(num<=i) dp[i] = (dp[i] + fs[num-2])%Mod;
				else dp[i] = (dp[i] + (fs[num-2] - fs[num-i-1]+Mod)%Mod + 1ll*dss[num-i-1]*((ds[num-i+1] - ds[num]+Mod)%Mod)%Mod)%Mod;
				//cout<<num<<' '<<dp[i]<<endl;
				//又见到了究极屎山代码 
			}
		}
		//upd d & ds & dss & fs
		if(i==n) continue;
		d[0] = 1;
		For(j,1,fun(i))
		{
			if(j >= i) d[j] = (ds[j] - ds[j-i] + Mod)%Mod;
			else d[j] = ds[j];
		}
	    dss[0] = ds[0] = d[0];
		For(j,1,fun(i+1)) ds[j] = (ds[j-1] + d[j])%Mod;
		For(j,1,fun(i+1)) dss[j] = (dss[j-1] + ds[j])%Mod;
		fs[0] = work(0);
		For(j,1,fun(i+1)) fs[j] = (fs[j-1] + work(j))%Mod;
	}
	cout<<dp[n]<<endl;
	return 0;
}
```


---

## 作者：chenxia25 (赞：6)

首先复杂度肯定是三方对吧。

先对付字典序的限制。那就枚举相等前缀的长度呗。然后下一位 $p$ 要比 $q$ 小。

然后考虑逆序对。发现相等前缀内部的逆序对，以及相等前缀与后面的后缀产生的逆序对，$p$ 和 $q$ 是相等的！于是就看后面了啊。以及前面和后面完完全全是独立的，就是说你完全可以把前面和后面看作两个独立的排列，然后以组合数方案数合并起来的每一种情况都是等价的（这大概是各种排列题的套路想法之一吧）。同时前缀是什么样根本不重要，于是需要考虑后缀的排列，设前缀长度为 $x$（之后抛弃这个假设），方案数乘上 $\mathrm A_n^x$（模数不是质数，不能用逆元。我是预处理组合数，然后 $\mathrm A_n^x=\dbinom nxx!$）累到答案里。

考虑对长度为 $x=1\sim n$ 后缀怎么操作呢。容易想到枚举 $p$ 和 $q$ 在第一位的值（那么第一位与后面产生的逆序对数就定下来了），然后设长度为 $n-1$ 的逆序对数为 $i$ 的排列数量为 $f_i$，那么贡献就是需要枚举 $p$ 和 $q$ 后 $n-1$ 位分别的逆序对数使得总逆序对是 $p$ 比 $q$ 大的，乘起来累起来（此处又用到了将排列劈成两半（此处是 $1$ 和 $2\sim n$）之后独立开来的想法）。

那么对于每个 $x$，这个 $f$ 数组显然可以从左往右 D 一 DP。具体就是 $dp_{i,j}$ 表示长度为 $i$ 的逆序对数为 $j$ 的排列数量，枚举最后一位然后把前面 $i-1$ 位独立开来显然有 $dp_{i,j}=\sum\limits_{k=1}^idp_{i-1,j-(i-k)}$。$i$ 是线性的，然而 $j$ 是平方，暴力转移是四方的，前缀和优化一下即可。

**下面重点来了：**知道了 $f$ 数组怎么求对某个 $x$ 的贡献呢（根据直觉 $x$ 们是不可能合起来计算的）。列出式子 
$$
ans=\sum\limits_{p=1}^x\sum\limits_{q=p+1}^x\sum\limits_{i=q-p+1}^{x^2}f_i\sum\limits_{j=0}^{i-(q-p+1)}f_j
$$
注意到后面两个 $\sum$ 只跟 $q-p+1$ 有关，所以我们可以线性枚举这玩意 instead of 平方枚举 $p,q$。以及最后一个 $\sum$ 可以写成前缀和（前缀和可以预处理呀）。
$$
ans=\sum\limits_{d=2}^x(x-d+1)\sum\limits_{i=d}^{x^2}f_iF_{i-d}
$$
现在直接算是三方的，加上枚举 $x$ 总复杂度是四方的，不行。想办法把计算这个和式优化到两方。先固定第一个 $\sum$，看右边的那个东西能不能线性或者均摊线性算出来。然后仔细一看就傻眼了……这个就是把 $F$ 倒过来的卷积呀……$500^3$ 根本不允许再带一个 log~~，况且我也不会 FFT~~。那就没办法了，只能让第一个 $\sum$ 参与优化，交换和式：
$$
ans=\sum_{i=2}^{x^2}f_i\sum_{d=2}^{\min(x,i)}(x-d+1)F_{i-d}
$$
考虑的是把后面这个 $\sum$ 优化到常数或均摊常数。$x+1$ 以及 $d$ 前面的负号先去掉，因为这肯定不能成为难度的瓶颈。于是要求 $\sum\limits_{d=2}^{\min(x,i)}dF_{i-d}$。你可能会说这不还是卷积嘛！但是这个卷积的左元 $d$ 是个很简单的东西，可化解的。考虑递推，你考虑将 $i=i_0-1$ 和 $i=i_0$ 时候的这个和式做差，将 $F$ 下标相同的项对齐，系数减出来恰好都为 $1$ 好吧！也就是说按 $i$ 从小到大的顺序，只需要再预处理一个 $F$ 的前缀和（$\mathcal F$ 或者 $\mathbb F$，滑稽），就可以实现 $\mathrm O(1)$ 的递推了（一些边角就也常数处理一下吧，挺烦）。

总复杂度三方。顺带说一嘴，DP 数组如果开三方数组的话会 MLE，那只能滚动，这样就只能即时贡献答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=510;
int n,mod;
int fact[N],comb[N][N];
int dp[2][N*N],Dp[2][N*N];
int FF[N*N];
int ans;
int A(int x,int y){return 1ll*comb[x][y]*fact[y]%mod;}
int rmd(int x){
	x>=mod&&(x-=mod);
	x<=-mod&&(x+=mod);
	return x;
}
void mol(int &x){
	x>=mod&&(x-=mod);
	x<=-mod&&(x+=mod);
}
void deal(int x){
	#define f dp[n-x-1&1]
	#define F Dp[n-x-1&1]
	for(int i=0;i<=n*(n-1)/2;i++)FF[i]=rmd((i?FF[i-1]:0)+F[i]);
	int now=0,sum=0;
	for(int i=2;i<=n*(n-1)/2;i++){
		if(i==2)now=1ll*(n-x-i+0+1)*F[0]%mod;
		else{
			if(i-n+x>0)mol(now-=1ll*(n-x-(i-1)+(i-1-n+x)+1)*F[i-1-n+x]%mod);
			mol(now+=1ll*(n-x-i+(i-2)+1)*F[i-2]%mod);
			int l=max(0,i-n+x),r=i-3;
			if(l<=r)mol(now-=rmd(FF[r]-(l?FF[l-1]:0)));
		}
		mol(sum+=1ll*f[i]*now%mod);
	}
	mol(ans+=1ll*sum*A(n,x)%mod);
}
int main(){
	cin>>n>>mod;
	fact[0]=1;for(int i=1;i<=n;i++)fact[i]=1ll*fact[i-1]*i%mod;
	comb[0][0]=1;for(int i=1;i<=n;i++)for(int j=0;j<=i;j++)comb[i][j]=((j?comb[i-1][j-1]:0)+comb[i-1][j])%mod;
	dp[0][0]=1;
	for(int i=0;i<=n*(n-1)/2;i++)Dp[0][i]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n*(n-1)/2;j++){
			int l=max(0,j-(i-1)),r=j;
			dp[i&1][j]=rmd(Dp[i-1&1][r]-(l?Dp[i-1&1][l-1]:0));
			Dp[i&1][j]=rmd((j?Dp[i&1][j-1]:0)+dp[i&1][j]);
		}
		if(i<n)deal(n-1-i);
	}
	cout<<(ans+mod)%mod;
	return 0;
}
```

---

## 作者：zztqwq (赞：4)

设 $f(n,m)$ 表示长度为 $n$ 的排列逆序对数为 $m$ 的方案数，这是个经典的前缀和优化 dp，不难 $\mathcal O(n^3)$ 求出。

假设 $p,q$ 前 $i$ 位相等，枚举它们第 $i+1$ 位的数 $x,y$，然后枚举后 $n-i-1$ 位的逆序对数 $s,t$，那么答案就是：

$$
\sum_{i=0}^{n-1}\binom ni\sum_{x=1}^{n-i}\sum_{y=x+1}^{n-i}\sum_{s=0}^{\binom{n-i}2}\sum_{t=0}^{\binom{n-i}{2}}[s+x-1>t+y-1]f(n-i-1,s)f(n-i-1,t)
$$

初步处理可得：

$$
\sum_{i=0}^{n-1}\binom ni\sum_{x=1}^{n-i}\sum_{y=x+1}^{n-i}\sum_{s=0}^{\binom{n-i}2}\sum_{t=0}^{s-(y-x)-1}f(n-i-1,s)f(n-i-1,t)
$$

后面只和 $y-x$ 有关，另 $z=y-x$，合并两个 $\Sigma$：

$$
\sum_{i=0}^{n-1}\binom ni\sum_{z=1}^{n-i-1}(n-i-z)\sum_{s=0}^{\binom{n-i}2}\sum_{t=0}^{s-z-1}f(n-i-1,s)f(n-i-1,t)
$$

考虑把 $s,t$ 的 $\Sigma$ 防到前面：

$$
\sum_{i=0}^{n-1}\binom ni\sum_{s=0}^{\binom{n-i}2}\sum_{t=0}^{s-1}f(n-i-1,s)f(n-i-1,t)\sum_{z=1}^{\min\{n-i-1,s-t-1\}}n-i-z
$$

问题其实就是求：

$$
\sum_{z=1}^{\min\{n-i-1,s-t-1\}} z
$$

也就是：

$$\frac{(\min\{n-i,s-t\})(\min\{n-i,s-t\}-1)}{2}
$$

假设 $s-t\le n-i$（如果大于的话加一些东西即可，是容易的），那么后面那个东西可以拆成 $(s^2-s-2st+t^2+t)/2$，处理一些前缀和，枚举 $s$ 即可做到 $\mathcal O(n^3)$。

还有一个问题是模数不是质数，可能没有 $2$ 的逆元。一种可能的解决方案是把上面的东西改成 $(s(s-1)-2st+t(t+1))/2$，这样每一项都是偶数，就可以直接除 $2$ 了。

可能需要一些丧心病狂的卡常。

```cpp
// LUOGU_RID: 102071465
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
const int N=501;
int f[N][N*N],sum[N*N],mod;
void Sub(int &x,int y){x-=y;if(x<0)x+=mod;}
void Add(int &x,int y){x+=y;if(x>=mod)x-=mod;}
int c[N][N],sum1[N*N],sum2[N*N],sum3[N*N];
int main()
{
	int n=read();mod=read();
	for(int i=0;i<=n;i++)
	{
		c[i][0]=c[i][i]=1;
		for(int j=1;j<i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	f[0][0]=f[1][0]=1;
	for(int i=2;i<=n;i++)
	{
		memset(sum,0,sizeof(sum));
		sum[0]=f[i-1][0];
		for(int j=1;j<=n*n;j++)sum[j]=(sum[j-1]+f[i-1][j]>=mod?sum[j-1]+f[i-1][j]-mod:sum[j-1]+f[i-1][j]);
		int llim=i*(i-1)/2;
		for(int j=0;j<=llim;j++)
		{
			f[i][j]=sum[j];
			if(j-min(i-1,j)>0)Add(f[i][j],mod-sum[j-min(i-1,j)-1]);
		}
	}
	int mul=1,Ans=0;
	__int128 tmp;int tp;
	for(int i=0;i<n;i++)
	{
		memset(sum1,0,sizeof(sum1));
		memset(sum2,0,sizeof(sum2));
		memset(sum3,0,sizeof(sum3));
		sum1[0]=f[n-i-1][0];
		sum2[0]=sum3[0]=0;
		int zzt=1ll*mul*c[n][i]%mod;
		int ans=0;
		int lim=(n-i)*(n-i-1)/2;
		for(int s=1;s<=lim;s++)
		{
			if(s-n+i<=0)
			{
				tmp=(__int128)f[n-i-1][s]*(n-i)*s*sum1[s-1];
				tmp-=(__int128)f[n-i-1][s]*(n-i)*sum2[s-1];
				tmp-=(__int128)f[n-i-1][s]*(n-i)*sum1[s-1];
				tmp-=(__int128)s*(s-1)/2*f[n-i-1][s]*sum1[s-1];
				tmp+=(__int128)s*f[n-i-1][s]*sum2[s-1];
				tmp-=(__int128)f[n-i-1][s]*sum3[s-1];
				tmp%=mod;tp=tmp;Add(tp,mod);Add(ans,tp);
			}
			else
			{
				tmp=(__int128)f[n-i-1][s]*(n-i)*s*sum1[s-1];
				tmp-=(__int128)f[n-i-1][s]*(n-i)*sum2[s-1];
				tmp-=(__int128)f[n-i-1][s]*(n-i)*sum1[s-1];
				tmp-=(__int128)s*(s-1)/2*f[n-i-1][s]*sum1[s-1];
				tmp+=(__int128)s*f[n-i-1][s]*sum2[s-1];
				tmp-=(__int128)f[n-i-1][s]*sum3[s-1];
				tmp%=mod;tp=tmp;Add(tp,mod);Add(ans,tp);
				int t=s-n+i;tmp=0;
				tmp-=(__int128)f[n-i-1][s]*(n-i)*s*sum1[t-1];
				tmp+=(__int128)f[n-i-1][s]*(n-i)*sum2[t-1];
				tmp+=(__int128)f[n-i-1][s]*(n-i)*sum1[t-1];
				tmp+=(__int128)s*(s-1)/2*f[n-i-1][s]*sum1[t-1];
				tmp-=(__int128)s*f[n-i-1][s]*sum2[t-1];
				tmp+=(__int128)f[n-i-1][s]*sum3[t-1];
				tmp+=(__int128)f[n-i-1][s]*sum1[t-1]*(n-i-1)*(n-i);
				tmp-=(__int128)(n-i)*(n-i-1)/2*f[n-i-1][s]*sum1[t-1];
				tmp%=mod;tp=tmp;Add(tp,mod);Add(ans,tp);
			}
			sum1[s]=sum1[s-1],sum2[s]=sum2[s-1],sum3[s]=sum3[s-1];
			Add(sum1[s],f[n-i-1][s]),Add(sum2[s],1ll*s*f[n-i-1][s]%mod),Add(sum3[s],(1ll*s*(s+1)/2)%mod*f[n-i-1][s]%mod);
		}
		Add(Ans,1ll*ans*zzt%mod);
		mul=1ll*mul*(i+1)%mod;
	}
	printf("%d\n",Ans);
}
```

---

## 作者：Cry_For_theMoon (赞：4)

[弱化版](codeforces.com/contest/1542/problem/E1)

[原版](codeforces.com/contest/1542/problem/E2)

二合一豪华版题解。

虽然最后写起来并不难（指 E1 + E2 一共debug了约5h）。但是其思考过程还是很妙的。

~~似乎这场 题全都带 math标签？mathforces 实锤~~

##### 题意：

计算 $n$ 排列二元组 $(p,q)$ 个数使得 $p$ 字典序小于 $q$ 且 $p$ 逆序对数目大于 $q$ 逆序对数目.

弱化版：$n \le 50$.

原版：$n \le 500$.

##### 分析：

极小的数据范围，4s 的时限，排列计数，逆序对，一看就是个毒瘤题。

但是它同时也是很套路的。字典序和逆序对两个条件，显然会去先满足字典序。考虑枚举 $(p,q)$ 前 $i$ 位相同，第 $i+1$ 位强制不同，$i+2$ 到 $n$ 位不做要求，满足这些条件的二元组的个数。

显然 $i+1$ 把两个排列分别分成两部分：$A=1...i$，$B=i+1...n$. 逆序对则由三部分组成：$A$ 内的，$B$ 内的，$AB$ 间的。考虑到 $p,q$ 此时形如：
$$
p=AB,q=AB'
$$
注意到 $B$ 和 $B'$ 是相同元素集合的排列。所以$p,q$ 的逆序对数量关系取决于 $B$ 和 $B'$ 的逆序对数量关系。与 $A$ 无关。所以我们的 $A$ 可以任意选择。方案数为 $i!\dbinom{n}{i}$ . 只需要求出长度为 $n-i$ 的排列二元组 $(B,B')$ ，满足 $B_1<B'_1$ 且 $inverse(B)>inverse(B')$ 的方案数。$inverse(X)$ 是排列 $X$ 的逆序对数。

注意到重头戏在后半部分，那就不从前往后枚举，从后往前枚举 $i$，代表从后往前数的第 $i$ 位是 $p,q$ 第一次不同的地方。

然后我们就会有很多大力 dp 的乱搞做法。

显然我们枚举 $B$ 的第一个元素 $x$ 和 $B'$ 的第一个元素 $y$ 满足 $x<y$. 那么现在 $B$ 比 $B'$ 少 $y-x$ 个逆序对。也就是说后面长度为 $i-1$ 的排列中 $inverse(B_2....)$ 要比 $inverse(B'_2...)$ 至少多 $y-x+1$ 个。这样才能让最后 $inverse(B)>inverse(B')$.

那就考虑设 $f(i,j)$ 是长度为 $i$ 的排列二元组 $(p,q)$ 满足 $inverse(p)-inverse(q)=j$ 的方案数，注意字典序的限制已经被枚举 $x,y$ 满足了所以我们抛弃这个限制，只剩下逆序对就比较可做。但直接求发现求不出来，毕竟二元组摆在那里。那么一个显然的想法是我们枚举 $inverse(p)=a$ 的个数，则乘上 $inverse(q)=a-j$ 的个数即可。因此，设 $g(i,j)$ 为 $i$ 排列有 $j$ 个逆序对的个数。则
$$
f(i,j) \sum_{k}g(i,k)\,\cdot g(i,k-j)
$$
这部分应该是 $O(n^5)$ 的，发现能莽过 E1，所以先保留它。考虑计算 $g$. 实际上这是个用前缀和优化的[经典原题](https://www.luogu.com.cn/problem/P2513). 并不难在 $O(n^3)$ 的时间内解决，本身是黄题难度。因此就不再多说。

继续设 $sum(i,j)$ 是 $i$ 排列二元组 $(p,q)$ 满足 $inverse(p)-inverse(q)\ge j$ 的方案数，显然求出 $f$ 以后这东西也就 $O(n^3)$ 计算。然后我们枚举 $x<y$ 后，$sum(i,y-x+1)$ 就是此时的方案个数。容易发现这部分也是 $O(n^3)$ 的。

到这里，你就草过了 E1 大暴力。

到这里我们已经可以猜到 E2 就是 $O(n^5)$ dp 优化到 $O(n^3)$ 罢了。发现瓶颈在 $f$ 的计算。从转移状态角度考虑并没有发现什么规律，不管 $g$ 算得多快（事实上 $O(n^3)$ 也够用），$f$ 的转移不可避免需要 $O(n^5)$. 也就是说算 $g$ 再算 $f$ 是不合法的。思考一会能否把 $g$ 直接和 $sum$ 关联起来，看看式子也没有什么数量关系。

所以我们考虑**直接**计算 $f(i,j)$. 不难列出转移式子：
$$
f(i,j)=\sum_{k=-(i-1)}^{(i-1)}(i-|k|)\,\cdot\,f(i-1,j-k)
$$
你发现我们直接转移都已经 $O(n^4)$ 了qwq，所以经典原题误我 TAT.

那么考虑继续优化。一个方向是，这个东西是个卷积，我们 FFT 做多项式乘法，$O(n^3 \log n)$ 就可以切掉它，看上去非常 nb，div2 闯入多项式。

出题人：”which we hope can't pass E2"

写多项式和暴力一个分，衷心感谢出题人给我锻炼 dp 技巧。

显然我们只能从 dp 的转移上考虑了，比较特殊的其实是系数 $(i-|k|)$. 你发现把所有系数拿出来其实形如：
$$
1,2,...,(i-1),...,2,1
$$
这是个先递增再递减的单峰数列！

然后再看第二项 $f(i-1,j-k)$. 我们发现 $f(i)$ 都是从 $f(i-1)$ 转移过来只不过存在系数差异，显然考虑做差，如果我们把展开后的 $f(i,j)$ 和 $f(i,j-1)$ 做差就会发现可以前缀和优化达到 $O(n^3)$. 举个例子：
$$
f(3,0)=3\,\times f(2,0)+2\,\times f(2,1)+1\,\times f(2,2)+2\,\times f(2,-1)+1\,\times f(2,-2) \\
f(3,1)=3\,\times f(2,1)+2\,\times (2,2)+1\,\times f(2,3)+2\,\times f(2,0)+1\,\times f(2,-1)
$$
下式减上式后发现 $f(3,1)$ 相比 $f(3,0)$ 只不过多了 $f(2,1)+f(2,2)+f(2,3)$ 少了 $f(2,0)+f(2,-1)+f(2,-2)$. 因此前缀和一下，就可以用 $f(i,j-1)$ $O(1)$ 推出 $f(i,j)$.

然后就解决了复杂度最大的瓶颈。

记得滚动数组。

记得下标有负数。

希望各位一遍 AC 不要像某些 E2 调了半天的屑最后发现是 $f(i)$ 的前缀和用到计算 $f(i,j)$ 里了。

E2 代码：

```C++
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=510,MAXM=510*510,ADD=501*501/2+1;
ll n,mod;
ll f[2][MAXM],sum[2][MAXM],fact[MAXN],c[MAXN][MAXN],g[MAXN],ans[MAXN],s[MAXM];
int main(){
	cin>>n>>mod;
	fact[0]=1;
	rep(i,1,n){
		fact[i]=fact[i-1]*i%mod;
	}
	c[0][0]=1;
	rep(i,1,n){
		c[i][0]=1;
		rep(j,1,i)c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
	}
	//f[i][j]是长度为i的排列对，逆序对差为j的数量 
	f[1&1][0+ADD]=1;rep(j,0,n*(n-1)/2)sum[1&1][j+ADD]=1;
	rep(i,2,n){
		memset(sum[i&1],0,sizeof sum[i&1]);
		rep(k,0,i-1){
			f[i&1][-i*(i-1)/2+ADD]=((ll)f[i&1][-i*(i-1)/2+ADD]+(i-k)*f[(i-1)&1][-i*(i-1)/2+k+ADD])%mod;
		}
		rep(j,-(i*(i-1)/2)+1,i*(i-1)/2){
			f[i&1][j+ADD]=((ll)f[i&1][j-1+ADD]+sum[(i-1)&1][Min(j+i-1,n*(n-1)/2)+ADD]-sum[(i-1)&1][j-1+ADD]-
			sum[(i-1)&1][j-1+ADD]+sum[(i-1)&1][Max(j-i-1,-n*(n-1)/2)+ADD]+mod)%mod;
		}
		rep(j,-n*(n-1)/2,n*(n-1)/2)sum[i&1][j+ADD]=(sum[i&1][j-1+ADD]+f[i&1][j+ADD])%mod;
		memset(s,0,sizeof s);
		s[i*(i-1)/2+ADD]=f[i&1][i*(i-1)/2+ADD];
		per(j,i*(i-1)/2-1,-n*(n-1)/2){
			s[j+ADD]=(s[j+1+ADD]+f[i&1][j+ADD])%mod;
		}
		rep(x,1,i+1){
			rep(y,x+1,i+1){
				//分别为x,y方案数
				ll diff=y-x;
				g[i+1]=(g[i+1]+s[diff+1+ADD])%mod;
			}
		}
	}
	rep(i,2,n){
		ans[i]=((ll)ans[i-1]*i+g[i])%mod;
	}
	cout<<ans[n];
	return 0;
}
```









---

## 作者：JiaY19 (赞：2)

怎么会有这么离谱的题目啊。

【模板】前缀和优化 dp。

### 思路

考虑一个基本的东西。

由于要求字典序的限制。

我们可以枚举最长公共前缀计算。

考虑如何求长度为 $i$ 的排列有 $j$ 个逆序对的数量。

设 $dp_{i,j}$。

$$dp_{i,j}=\sum_{k=0}^{i-1}dp_{i-1,j-k}$$

就是枚举新的数放在那里。

不难看出可以前缀和优化。

$$dp_{i,j}=g_{i-1,j-k}-g_{i-1,j-i}$$

就可以 $O(n^3)$ 计算。

到这里都是比较简单的。

考虑如何算答案。

首先列出较为朴素的 $\text{dp}$。

枚举最长公共前缀长度 $i$，第 $i+1$ 位两个排列分别放 $x,y$，后面 $n-i-1$ 位分别会有 $s,t$ 个逆序对。

$$\sum_{i=0}^{n-1}\binom{n}{i}i!\sum_{x=1}^n\sum_{y=x+1}^{n-i}\sum_{s=0}^{\binom{n-i+1}{2}}\sum_{t=0}^{\binom{n-i+1}{2}}[s+x-1>t+y-1] dp_{n-i-1,s}\times dp_{n-i-1,t}$$

稍微整理一下。

$$\sum_{i=0}^{n-1}\binom{n}{i}i!\sum_{x=1}^n\sum_{y=x+1}^{n-i}\sum_{s=0}^{\binom{n-i+1}{2}}\sum_{t=0}^{s+x-y-1}dp_{n-i-1,s}\times dp_{n-i-1,t}$$

$$\sum_{i=0}^{n-1}\binom{n}{i}i!\sum_{x=1}^n\sum_{y=x+1}^{n-i}\sum_{s=0}^{\binom{n-i+1}{2}}dp_{n-i-1,s}\sum_{t=0}^{s+x-y-1}dp_{n-i-1,t}$$

发现又可以前缀和优化。

设 $g_{i,j}=\sum_{k=0}^j dp_{i,j}$。

$$\sum_{i=0}^{n-1}\binom{n}{i}i!\sum_{x=1}^n\sum_{y=x+1}^{n-i}\sum_{s=0}^{\binom{n-i+1}{2}}dp_{n-i-1,s}\times g_{n-i-1,s+x-y-1}$$

$$\sum_{i=0}^{n-1}\binom{n}{i}i!\sum_{s=0}^{\binom{n-i+1}{2}}dp_{n-i-1,s}\sum_{x=1}^n\sum_{y=x+1}^{n-i}g_{n-i-1,s+x-y-1}$$

这个时候，我发现了后面只与 $x-y$ 有关，那么可以枚举 $x-y=j$。

$$\sum_{i=0}^{n-1}\binom{n}{i}i!\sum_{s=0}^{\binom{n-i+1}{2}}dp_{n-i-1,s}\sum_{j=1}^{n-i-1}(n-i-j)\times g_{n-i-1,s+x-y-1}$$

这个式子已经可以 $O(n^4)$ 算了，可以通关简单版本。

但如何把它优化成 $O(n^3)$，我确实没有想到，如果有大佬会，可以教教我。

然后就发现我们走了很没有前途的一步，我也在这里卡了很久。

那么我们不得不往回退一步。

$$\sum_{i=0}^{n-1}\binom{n}{i}i!\sum_{s=0}^{\binom{n-i+1}{2}}dp_{n-i-1,s}\sum_{x=1}^{n-i}\sum_{y=x+1}^{n-i}g_{n-i-1,s+x-y-1}$$

我们考虑继续前缀和优化。

设 $h_{i,j}=\sum_{k=0}^jg_{i,k}$。

$$\sum_{i=0}^{n-1}\binom{n}{i}i!\sum_{s=0}^{\binom{n-i+1}{2}}dp_{n-i-1,s}\sum_{x=1}^{n-i}h_{n-i-1,s-2}-h_{n-i-1,s+x-n+i-1}$$

发现这玩意还可以前缀和优化。

$$\sum_{i=0}^{n-1}\binom{n}{i}i!\sum_{s=0}^{\binom{n-i+1}{2}}dp_{n-i-1,s}((n-i)\times h_{n-i-1,s-2}-\sum_{x=1}^{n-i}h_{n-i-1,s+x-n+i-1})$$

设 $f_{i,j}=\sum_{k=0}^jh_{i,k}$。

设 $l=s+i-n-1,r=s-2$。

$$\sum_{i=0}^{n-1}\binom{n}{i}i!\sum_{s=0}^{\binom{n-i+1}{2}}dp_{n-i-1,s}((n-i)\times h_{n-i-1,s-2}-(f_{n-i-1,r}-f_{n-i-1,l-1}))$$

然后就做完了。

可能有一些边界情况需要来判断。

### Code

```cpp
/**
 * @file 1542E1.cpp
 * @author mfeitveer
 * @date 2023-11-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define mp(x, y) make_pair(x, y)
#define fro(i, x, y) for(int i = (x);i <= (y);i++)
#define pre(i, x, y) for(int i = (x);i >= (y);i--)
#define dbg cerr << "Line " << __LINE__ << ": "
#define EVAL(x) #x " = " << (x)

typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef pair<int, int> PII;

bool ed;

const int N = 510;
const int M = 124760;

int n, m, mod, c[N][N], vis[N][N], g[M], h[M], f[M], dp[N][M];

inline int add(int x, int y)
	{ return x + y + (x + y >= mod ? -mod : 0); }
inline void init(int now)
{
	fro(j, 0, 124750) g[j] = dp[now][j];
	fro(j, 1, 124750) g[j] = add(g[j], g[j - 1]);
	fro(j, 0, 124750) h[j] = g[j];
	fro(j, 1, 124750) h[j] = add(h[j], h[j - 1]);
	fro(j, 0, 124750) f[j] = h[j];
	fro(j, 1, 124750) f[j] = add(f[j], f[j - 1]);
}
inline int C(int x, int y)
{
	if(x < y) return 0;
	if(y == 0 || x == y) return 1;
	if(vis[x][y]) return c[x][y]; vis[x][y] = 1;
	return c[x][y] = (C(x - 1, y - 1) + C(x - 1, y)) % mod;
}
inline int ask(int l, int r)
{
	if(l - 1 < 0) return g[r];
	return (g[r] - g[l - 1] + mod) % mod;
}
inline void init()
{
	dp[0][0] = 1;
	fro(i, 1, 500)
	{
		init(i - 1);
		fro(j, 0, 124750) dp[i][j] = ask(j - i + 1, j);
	}
}
inline void solve()
{
	i64 ans = 0, num = 1;
	fro(i, 0, n - 1)
	{
		i64 res = 0; init(n - i - 1);
			fro(s, 2, (n - i - 1) * (n - i - 2) / 2)
			{
				i64 res1 = 1ll * h[s - 2] * (n - i) % mod;
				int ls = s + i - n - 1;
				i64 res2 = f[s - 2] - (ls <= 0 ? 0 : f[ls - 1]);
				res2 = (res2 % mod + mod) % mod;
				(res += (res1 - res2 + mod) * dp[n - i - 1][s]) %= mod;
		}
		(ans += res * num) %= mod, num = num * (n - i) % mod;
	}
	cout << ans << endl;
}

bool st;

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	double Mib = fabs((&ed-&st)/1048576.), Lim = 1024;
	assert(Mib<=Lim), cerr << " Memory: " << Mib << "\n";
	cin >> n >> mod;
	init(), solve();
	return 0;
}

```

---

## 作者：tzc_wk (赞：2)

upd on 2021.7.7：修了个 typo

[Codeforces 题目传送门](https://codeforces.com/contest/1542/problem/E2) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1542E2)

[在 cnblogs 中查看](https://www.cnblogs.com/ET2006/p/codeforces-1542E2.html)

这里将 E1、E2 的题解一并写上。

首先考虑怎样处理”字典序小“这个问题，按照字典序比大小的套路，我们可以枚举第一位 $p_x\ne q_x$ 的位置 $x$，那么必然有 $p_x<q_x$，为了避免后面计算中出现太多形如 $n-x$ 之类的东西，我们不枚举 $x$，instead 我们枚举 $i=n-x$，那么真正的 $x$ 等于 $n$ 减去你枚举的 $i$。

接下来考虑 $p$ 逆序对个数大于 $q$ 逆序对个数这个东西怎么处理，显然 $p,q$ 的前 $n-i-1$ 位是相同的，它们内部的逆序对个数是相同的，而由于 $p,q$ 第 $n-i$ 位到第 $n$ 位中数组成相同，$p,q$ 前 $n-i-1$ 位与后 $i+1$ 位之间的逆序对个数也相同，因此 $p$ 逆序对个数大于 $q$ 逆序对个数即意味着 $p$ 后 $i+1$ 位逆序对个数 $>$ $q$ 后 $i+1$ 位逆序对个数。

我们假设 $p$ 后 $i$ 位逆序对个数为 $u$，$q$ 后 $i$ 位逆序对个数为 $v$，那么不难发现，加入 $p_{n-i}$ 后逆序对个数的变化只与 $p_{n-i}$ 在后 $i+1$ 个数中排第几有关——我们假设 $p_{n-i}$ 是 $p$ 后 $i+1$ 位中的第 $s$ 小，$q_{n-i}$ 是 $q$ 后 $n-i+1$ 位中的第 $t$ 小，那么后 $i+1$ 位中 $p$ 的逆序对数即为 $u+s-1$，$q$ 的逆序对数即为 $v+t-1$。

我们考虑枚举 $u,v$，那么根据 $u+s-1>v+t-1$ 可知 $t-s<u-v$，又显然 $t>s$，故 $0<t-s<u-v$，根据 $t,s\in[1,i+1]$ 可知，满足 $t-s=x(x\in[1,i])$ 的 $t,s$ 共有 $i+1-x$ 组，把它们累加起来可得 $\sum\limits_{x=1}^{u-v-1}i+1-x=\dfrac{i(i+1)}{2}-\dfrac{(i+1-(u-v))(i+2-(u-v))}{2}$，我们记 $f(i,x)=\dfrac{i(i+1)}{2}-\max(\dfrac{(i+1-x)(i+2-x)}{2},0)$，那么这东西就是 $f(i,u-v)$。

接下来考虑怎样计算答案，首先我们设 $dp_{i,j}$ 表示有多少个长度为 $i$ 的排列有 $j$ 个逆序对，那么显然有转移方程式 $dp_{i,j}=\sum\limits_{k=0}^{i-1}dp_{i-1,j-k}$，前缀和优化即可实现 $\mathcal O(1)$ 转移。那么我们枚举 $i,u,v$，那么根据之前的推论填好 $p,q$ 后 $i+1$ 位的相对大小关系的方案数为 $\sum\limits_{u=0}^{i(i-1)/2}\sum\limits_{v=0}^{u-1}dp_{i,u}dp_{i,v}f(i,u-v)$，再乘上确定 $p,q$ 前 $n-i-1$ 位的方案数——选出 $n-i-1$ 个数的方案数为 $\dbinom{n}{n-i-1}$，将它们排列好的方案数为 $(n-i-1)!$，因此总方案数就是 $\sum\limits_{i=0}^{n-1}\dbinom{n}{n-i-1}(n-i-1)!\sum\limits_{u=0}^{i(i-1)/2}\sum\limits_{v=0}^{u-1}dp_{i,u}dp_{i,v}f(i,u-v)$，暴力计算是 $\mathcal O(n^5)$，无法通过 E2，可以通过 E1。如果稍微观察一下可知若 $v<u-i$，$f(i,u-v)=\dfrac{i(i+1)}{2}$ 为定值，可以直接一波前缀和带走，时间复杂度可以降到 $n^4$，但是还是无法通过 E2。

附：E1 $\mathcal O(n^4)$ 的做法，注意，由于模数不是质数，不能预处理阶乘及其逆元来求组合数，需手动递推。

```cpp
const int MAXN=50;
const int MAXM=1225;
int n,mod,ans=0,dp[MAXN+5][MAXM+5],sum[MAXN+5][MAXM+5];
int c[MAXN+5][MAXN+5],fac[MAXN+5];
int main(){
	scanf("%d%d",&n,&mod);dp[1][0]=1;
	for(int i=0;i<=MAXM;i++) sum[1][i]=1;
	for(int i=2;i<=n;i++){
		for(int j=0;j<=i*(i-1)/2;j++){
			dp[i][j]=sum[i-1][j];
			if(j-i>=0) dp[i][j]=(dp[i][j]-sum[i-1][j-i]+mod)%mod;
//			printf("%d %d %d\n",i,j,dp[i][j]);
		} sum[i][0]=dp[i][0];
		for(int j=1;j<=MAXM;j++) sum[i][j]=(sum[i][j-1]+dp[i][j])%mod;
	}
	for(int i=(fac[0]=1)-1;i<=MAXN;i++){
		c[i][0]=1;if(i) fac[i]=1ll*fac[i-1]*i%mod;
		for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	for(int i=0;i<n;i++){
		int lim=i*(i+1)/2,s=0;
		for(int j=0;j<=i*(i-1)/2;j++){
			s=(s+1ll*lim*sum[i][j-1]%mod*dp[i][j])%mod;
			for(int k=max(0,j-i);k<j;k++){
				s=(s-1ll*(i-j+k+1)*(i-j+k+2)/2*dp[i][k]%mod*dp[i][j]%mod+mod)%mod;
			}
		} //printf("%d\n",s);
		ans=(ans+1ll*s*c[n][n-i-1]%mod*fac[n-i-1])%mod;
	}
	printf("%d\n",ans);
	return 0;
}
```

接下来考虑优化这个做法，考虑后面这个式子 $\sum\limits_{u=0}^{i(i-1)/2}\sum\limits_{v=0}^{u-1}dp_{i,u}dp_{i,v}f(i,u-v)$，我们不妨固定住 $u$，考虑后面的东西怎么快速计算，我们不妨将 $f$ 展开，可以得到：
$$
\begin{aligned}
&\sum\limits_{u=0}^{i(i-1)/2}\sum\limits_{v=0}^{u-1}dp_{i,u}dp_{i,v}f(i,u-v)\\
=&\sum\limits_{u=0}^{i(i-1)/2}dp_{i,u}·\sum\limits_{v=0}^{u-1}dp_{i,v}(\dfrac{i(i+1)}{2}-\max(\dfrac{(i+1-(u-v))(i+2-(u-v))}{2},0))\\
=&\sum\limits_{u=0}^{i(i-1)/2}dp_{i,u}·\sum\limits_{v=0}^{u-1}dp_{i,v}\dfrac{i(i+1)}{2}-dp_{i,u}·\sum\limits_{v=0}^{u-1}dp_{i,v}\max(\dfrac{(i+1-(u-v))(i+2-(u-v))}{2},0)
\end{aligned}
$$
前面的东西显然一波前缀和带走，对于后面的部分，如果 $v<u-i$ 那显然是 $0$，否则我们可以将 $\max$ 展开，继续化为 $\sum\limits_{v=0}^{u-1}dp_{i,v}·\dfrac{(i+1-u+v)(i+2-u+v)}{2}$，记 $T=i+1+v$，那么原式 $=\sum\limits_{v=0}^{u-1}dp_{i,v}·\dfrac{(T+v)(T+1+v)}{2}$，这里有一个稍微有些棘手的地方，就是 $2$ 不一定有逆元，因此不能直接拆成 $v$ 的平方项、$v$ 的一次项和常数项分别求和再乘上 $2$ 的逆元，因此我们采用这样一个方法：$\dfrac{(T+v)(T+1+v)}{2}=\dfrac{T(T+1)}{2}+Tv+\dfrac{v(v+1)}{2}$，这样三项都是整数，就可以直接求和了，维护 $dp_{i,v},v·dp_{i,v},\dfrac{v(v+1)}{2}·dp_{i,v}$ 的前缀和即可 $\mathcal O(1)$ 计算上式。

时间复杂度 $n^3$，代码不算难写。

```cpp
const int MAXN=500;
const int MAXM=500*499/2;
int n,mod,ans=0,dp[MAXN+5][MAXM+5];
int sum[MAXM+5],_sum[MAXM+5],__sum[MAXM+5];
int c[MAXN+5][MAXN+5],fac[MAXN+5];
int sum0(int l,int r){if(l>r) return 0;return (sum[r]-((!l)?0:sum[l-1])+mod)%mod;}
int sum1(int l,int r){if(l>r) return 0;return (_sum[r]-((!l)?0:_sum[l-1])+mod)%mod;}
int sum2(int l,int r){if(l>r) return 0;return (__sum[r]-((!l)?0:__sum[l-1])+mod)%mod;}
int main(){
	scanf("%d%d",&n,&mod);dp[1][0]=1;
	for(int i=0;i<=MAXM;i++) sum[i]=1;
	for(int i=2;i<=n;i++){
		for(int j=0;j<=i*(i-1)/2;j++){
			dp[i][j]=sum[j];
			if(j-i>=0) dp[i][j]=(dp[i][j]-sum[j-i]+mod)%mod;
//			printf("%d %d %d\n",i,j,dp[i][j]);
		} memset(sum,0,sizeof(sum));sum[0]=dp[i][0];
		for(int j=1;j<=MAXM;j++) sum[j]=(sum[j-1]+dp[i][j])%mod;
	}
	for(int i=(fac[0]=1)-1;i<=MAXN;i++){
		c[i][0]=1;if(i) fac[i]=1ll*fac[i-1]*i%mod;
		for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	for(int i=0;i<n;i++){
		int lim=i*(i+1)/2,s=0;
		memset(sum,0,sizeof(sum));
		memset(_sum,0,sizeof(_sum));
		memset(__sum,0,sizeof(__sum));
		sum[0]=dp[i][0];
		for(int j=1;j<=i*(i-1)/2;j++){
			sum[j]=(sum[j-1]+dp[i][j])%mod;
			_sum[j]=(_sum[j-1]+1ll*j*dp[i][j])%mod;
			__sum[j]=(__sum[j-1]+1ll*j*(j+1)/2*dp[i][j])%mod;
		}
		for(int j=0;j<=i*(i-1)/2;j++){
			s=(s+1ll*lim*sum[j-1]%mod*dp[i][j])%mod;
			int T=i-j+1;
			int A=(1ll*T*(T+1)/2%mod+mod)%mod;
			int B=(T+mod)%mod;
			int minus=(1ll*A*sum0(max(0,j-i),j-1)%mod
					  +1ll*B*sum1(max(0,j-i),j-1)%mod
					  +sum2(max(0,j-i),j-1))%mod;
			s=(s-1ll*minus*dp[i][j]%mod+mod)%mod;
		} //printf("%d\n",s);
		ans=(ans+1ll*s*c[n][n-i-1]%mod*fac[n-i-1])%mod;
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Jerrywang09 (赞：1)

有一个很典的 DP：求长度为 $i$、逆序对数为 $j$ 的排列个数。设其为 $f(i,j)$。枚举最后一位添加了几个逆序对，则有转移：

$$
f(i, j)=\sum_{k=0}^{\min(i-1, j)} f(i-1, j-k)
$$

令 $g(i, j)=\sum_{k=0}^j f(i, k)$ 可以前缀和优化转移。

本题的难点在于统计答案。比较字典序，首先考虑枚举 $p,q$ 的最长公共前缀 $i$，然后把 $p[i+1,n],q[i+1,n]$ 抽出来并离散化，得到两个长度为 $n-i$ 的排列 $p',q'$。

枚举 $x=p'[1],y=q'[1],x<y$，以及 $p'[2,n-i],q'[2,n-i]$ 的逆序对个数 $a,b$。则 $p',q'$ 的逆序对个数为 $x-1+a,y-1+b$。由于 $p[1,i]=q[1,i]$，因此题目中的条件等价于 $x-1+a>y-1+b$，也就是 $x+a-y>b$。

因此可以得到答案的计算式：

$$
\begin{align*}
ans&=\sum_{i=0}^{n-1}\text{P}_n^i\sum_{x=1}^{n-i}\sum_{y=x+1}^{n-i}\sum_{a=0}^{\binom {n-i-1} 2}\sum_{b=0}^{x+a-y-1} f(n-i-1, a)\cdot f(n-i-1, b)\\
&=\sum_{i=0}^{n-1}\text{P}_n^i\sum_{x=1}^{n-i}\sum_{y=x+1}^{n-i}\sum_{a=0}^{\binom {n-i-1} 2} f(n-i-1, a) \sum_{b=0}^{x+a-y-1} f(n-i-1, b)\\
&=\sum_{i=0}^{n-1}\text{P}_n^i\sum_{x=1}^{n-i}\sum_{y=x+1}^{n-i}\sum_{a=0}^{\binom {n-i-1} 2} f(n-i-1, a)\cdot g(n-i-1, x+a-y-1)\\
&=\sum_{i=0}^{n-1}\text{P}_n^i\sum_{a=0}^{\binom {n-i-1} 2} f(n-i-1, a)\sum_{x=1}^{n-i}\sum_{y=x+1}^{n-i}g(n-i-1, x+a-y-1)
\end{align*}
$$

考虑继续前缀和优化。令 $s(i, j)=\sum_{k=0}^j g(i, k)$，则
$$
\begin{align*}
ans&=\sum_{i=0}^{n-1}\text{P}_n^i\sum_{a=0}^{\binom {n-i-1} 2} f(n-i-1, a)\sum_{x=1}^{n-i}s(n-i-1,a-2)-s(n-i-1,x+a-n+i-2)\\
&=\sum_{i=0}^{n-1}\text{P}_n^i\sum_{a=0}^{\binom {n-i-1} 2} f(n-i-1, a)((n-i)s(n-i-1,a-2)-\sum_{x=1}^{n-i}s(n-i-1,x+a-n+i-2))\\
\end{align*}
$$

令 $t(i, j)=\sum_{k=0}^j s(i, k)$，则
$$
\begin{align*}
ans=\sum_{i=0}^{n-1}\text{P}_n^i\sum_{a=0}^{\binom {n-i-1} 2} f(n-i-1, a)\cdot ((n-i)s(n-i-1,a-2)-(t(n-i-1,a-2)-t(n-i-1,a-n+i-2))
\end{align*}
$$

```cpp
// Title:  Abnormal Permutation Pairs (hard version)
// Source: CF1542E2
// Author: Jerrywang
#include <cstdio>
#include <iostream>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=505, M=N*N;
using namespace std;

int n, m, mod, f[N][M]; ll g[M], s[M], t[M], ans;
inline int C(int n) {return n*(n-1)>>1;}
inline ll query(ll a[], int r, int l)
{
    ll x=(r>=0?a[r]:0);
    ll y=(l>=0?a[l]:0);
    return (x-y+mod)%mod;
}
int main()
{
    scanf("%d%d", &n, &mod), m=C(n);
    f[1][0]=1;
    rep(i, 0, m) g[i]=1;
    rep(i, 2, n)
    {
        rep(j, 0, C(i))
            f[i][j]=query(g, j, j-(i-1)-1);
        g[0]=f[i][0];
        rep(j, 1, m) g[j]=(g[j-1]+f[i][j])%mod;
    }
    ll P=1;
    rep(i, 0, n-1)
    {
        int ii=n-i-1;
        g[0]=f[ii][0];
        rep(j, 1, C(ii)) g[j]=(g[j-1]+f[ii][j])%mod;
        s[0]=g[0];
        rep(j, 1, C(ii)) s[j]=(s[j-1]+g[j])%mod;
        t[0]=s[0];
        rep(j, 1, C(ii)) t[j]=(t[j-1]+s[j])%mod;
        rep(a, 0, C(ii))
        {
            ll tmp=(n-i)*(a-2>=0?s[a-2]:0)%mod;
            tmp=(tmp-query(t, a-2, a-n+i-2)+mod)%mod;
            ans=(ans+P*f[ii][a]%mod*tmp%mod)%mod;
        }
        P=P*(n-i)%mod;
    }
    printf("%lld", ans);

    return 0;
}
```

---

## 作者：_SeeleVollerei_ (赞：1)

感觉做完后很自然但是做的过程并不顺利的一道题。

对于排列计数很自然的一个想法就是从小到大塞数进去。

最暴力的一个做法就是 $f_{i,j,k,0/1}$ 表示 $[1,i]$，其中前 $j$ 位相同，然后 $p$ 比 $q$ 多 $k$ 个逆序对，谁大谁小。

转移是复杂的，但是可以比较轻松的 $O(n^5)$，能过 E1。

第一反应肯定是降维，因为这个状态数都很大。发现其他维都比较重要，但是第二维的转移非常复杂，而且我们实际上并不关心中途有多少位相同，所以考虑直接枚举对于最终的排列，前多少位相同。因为前面全都是相同的，所以前面对后面以及前面自己内部的逆序对贡献是完全一致的，于是我们只需要考虑后 $n-j$ 位。

那么现在相当于要处理一个 $n-j$ 的排列，且强制 $p$ 的第一位比 $q$ 小。考虑枚举第 $j+1$ 位两个排列分别填多少，并且能直接统计这一位对后面的逆序对贡献，假设 $p$ 这一位的贡献比 $q$ 少 $k$，那么相当于要求我们求对于 $n-j-1$ 的排列，$p$ 比 $q$ 逆序对多至少 $k+1$ 个的方案数。

光是上面的部分就需要 $O(n^2)$ 或 $O(n^3)$ 了，但是剩下的地方似乎独立出来了，我们完全可以预处理一个 $f_{i,j}$ 表示 $[1,i]$ 的排列，$p$ 比 $q$ 多恰好 $j$ 个逆序对的方案数。

考虑转移，思考一下 $f_{i,j}$ 在 $f_{i+1}$ 的贡献.

这里假设 $k\ge 0$，由 $f_{i,j}$ 向 $f_{i+1,j+k}$ 转移，那么显然会有一个系数，大概是要考虑两个排列塞的位置要刚好差 $k$，然后一共有 $i+1$ 个空，所以系数为 $i+1-k$。$k\le 0$ 同理。

这样状态数是 $O(n^3)$，每次转移是 $O(n)$ 的，所以还要优化。

我们把所有的系数列出来，发现是这样的形式：

$$1,2,3,\dots,i+1,i,i-1,i-2,\dots,1,0,0$$

发现是一个阶梯的形式？这意味着差分后将会有一大段是相同的。

$$1,1,1,\dots,1,-1,-1,\dots,-1,-1,0$$

有一大段是相同的，这是不是一个类似区间加的操作？对于区间加，通常考虑差分。所以我们对这个差分再差分一下。

$$1,0,0,\dots,0,-2,0,\dots,0,0,1$$

这样每次转移就变成了一个单点加了，然后两次差分对应回来就是求两次前缀和即可。

这部分的复杂度是 $O(n^3)$ 的，然后就做完了。

https://codeforces.com/contest/1542/submission/172253455

---

## 作者：xuantianhao (赞：0)

# [Abnormal Permutation Pairs (hard version)](https://www.luogu.com.cn/problem/CF1542E2)

两个限制：字典序小、逆序对大，一个显然的想法就是确保一对关系，统计另一对关系。

确保哪一对呢？我们想了想，决定确保字典序小，因为字典序是可以贪心的。

具体而言，我们考虑两个排列自第 $i$ 位开始出现了不同。这样子，我们便将两个排列各自划成两段，即 $[1,i-1]$ 与 $[i,n]$。则两排列的第一段是相同的。

考虑借鉴 CDQ 分治的思想，将逆序对分为三类，即首段中、末段中、两段间。因为两排列首段相同，所以首段中的逆序对数相等；因为两排列中每一段的组成元素相同，所以两段间的逆序对数亦相等；有区别的只有末端中的逆序对数。

于是，我们考虑枚举这个 $i$，则前 $i-1$ 位就有 $n^{\underline{i-1}}$ 种取值方案。

我们还剩下 $n-i+1$ 个互不相同的数。因为逆序对仅与大小关系相关，所以我们完全可以将其映射作一个长度为 $n-i+1$ 的排列而不改变逆序对数。

现在考虑枚举第 $i$ 位两个排列分别填了什么。设排列 $p$ 填了 $j$（实际上是剩余数中第 $j$ 小的数），$q$ 填了 $k$（同理，实质是第 $k$ 小的数），则要满足字典序限制则应有 $j<k$。$j$ 对后面元素贡献了 $j-1$ 个逆序对，$k$ 对后面元素贡献了 $k-1$ 个逆序对，则现在 $p$ 比 $q$ 少了 $k-j$ 个逆序对。

因为后 $n-i$ 位以后就可以随便填了，所以我们就设一个 $f_{i,j}$ 表示长度为 $i$ 的排列出现 $j$ 个逆序对的方案数。枚举数字 $i$ 填哪里就可以做到 $n^4$，用前缀和/差分优化就能做到 $n^3$，过于基础不再赘述。

现在回到 $p$ 填 $j$、$q$ 填 $k$ 的情形。则，$p$ 要保证后 $n-i$ 位中逆序对数至少比 $q$ 多 $k-j+1$ 个才能满足逆序对的限制。

考虑枚举 $i,j,k$ 以及 $p,q$ 在后 $n-i$ 位中逆序对数分别是 $J,K$，可以做到垃圾的 $n^7$ 复杂度；

但注意到我们对于同样的 $J-K$ 只关心 $k-j+1$，于是我们仅枚举 $J,K$，再预处理出此时合法的 $j,k$ 对数，就能做到 $n^5$；

假如再观察到 $j-k+1$ 最大只到 $n-i$，这样 $J-K$ 在大于 $n-i$ 后，对于再之前的所有 $K$ 来说合法的 $j,k$ 对数便会一直相等，这样枚举 $K$ 时就只用枚举 $J$ 之前的 $n-i$ 个位置，之前的用一个前缀和就能解决，这样就能做到 $n^4$；

优化到正解 $n^3$ 的做法是考虑 $J$ 增加时，对于不同的 $K$ 来说 $j-k$ 数对的增量是什么；然后发现这一增量在 $J-K=2$ 时是 $n-i,J-K=3$ 时是 $n-i-1,J-K=k$ 时是 $n-i-k+2$。放到平面直角坐标系上就是一个三角形的形式，可以通过预处理 $f_{i,j}$ 数组的前缀和以及 $j\times f_{i,j}$ 的前缀和来 $O(1)$ 求出。

细节很多，详见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=510;
const int M=125100;
int n,mod,res;
int com[N],f[M],fac[N],s[M],t[M],C[N][N],d[N];
signed main(){
    cin>>n>>mod;
    for(int i=1;i<=n;i++) com[i]=i*(i-1)/2;
    fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    for(int i=0;i<=n;i++) C[i][0]=1;
    for(int i=1;i<=n;i++) for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
    f[0]=1;
    for(int i=0;i<n;i++){
        for(int j=1;j<=com[i];j++) (f[j]+=f[j-1])%=mod;
		f[com[i]+1]=0;
        for(int j=0;j<=i;j++) d[j]=0;
        for(int J=0;J<=i;J++) for(int K=J+1;K<=i;K++) d[K-J]++;
        for(int j=1;j<=i;j++) d[j]+=d[j-1];
        for(int j=0;j<=com[i];j++){
			s[j]=f[j];
			t[j]=1ll*f[j]*j%mod;
		}
        for(int j=1;j<=com[i];j++){
			(s[j]+=s[j-1])%=mod;
			(t[j]+=t[j-1])%=mod;
		}
        for(int j=2,k=0;j<=com[i];j++){
            if(j>i){
				(res+=1ll*d[i]*fac[n-i-1]%mod*C[n][n-i-1]%mod*f[j]%mod*s[j-i-1]%mod)%=mod;
				(k+=mod-1ll*f[j-i-1]*d[i]%mod)%=mod;
			}
            (k+=(0ll+t[j-2]+mod-1ll*(j-i-2)*s[j-2]%mod)%mod)%=mod;
            if(j-1>i) (k+=(2ll*mod-t[j-i-2]+1ll*(j-i-2)*s[j-i-2]%mod)%mod)%=mod;
            (res+=1ll*C[n][n-i-1]*fac[n-i-1]%mod*f[j]%mod*k%mod)%=mod;
        }
        for(int j=com[i];j>=0;j--) (f[j+i+1]+=mod-f[j])%=mod;
    }
    cout<<res;
    return 0;
}
```


---

## 作者：masterhuang (赞：0)

关于题解：我唯一看懂的是[这篇](https://www.luogu.com.cn/user/310317)。

**但是**，这篇错误有点多，于是我重新推一推，但还是要感谢这篇题解，让我看懂了。

----
首先，考虑枚举其中一个的逆序对数，这里绕不开的问题就是求 $I_{i,j}$ 表示 $1-i$ 的排列中逆序对个数为 $j$ 的排列数，不妨把这里逆序对变成顺序对（为了方便描述，显然是等价的）。

有个很显然的trick：把所有数按 $1-n$ 顺序插入。然后当插入第 $i$ 个数时，枚举它前面有 $k$ 个数，则顺序对会增加 $k$ 个。于是 $I_{i,j}\leftarrow\sum\limits_{k=0}^{i-1} I_{i-1,j-k}$。

复杂度： $n\times n^2\times n$，是 $O(n^4)$ 的。

前缀和优化一下，记 $SI_{i,j}=\sum\limits_{k=0}^j I_{i,j}$，那么 $I_{i,j}\leftarrow SI_{i-1,j}-SI_{i-1,j-i+1}$，就可以 $O(n^3)$ 了。

# 最初：$O(n^7)$
考虑这题，用递推（我也不知道是怎么想到的）。

记 $f_i$ 表示本题长度为 $i$ 时的答案。

考虑枚举两个排列的最后一位，分别为 $p,q$。

若 $p=q$，则 $f_i\leftarrow i\times f_{i-1}$。

否则，枚举 $p,q$ 和直接第一、二个排列**之前**的逆序对数 $j,k$。

则 $f_i\leftarrow \sum\limits_{p=1}^i\sum\limits_{q=p+1}^i\sum\limits_{j=p-1}^{p-1+(i-2)\times(i-2)/2}\sum\limits_{k=q-1}^{j-1} I_{i-1,j-(p-1)}\times I_{i-1,k-(q-1)}$。

两个加起来即可，复杂度是 $O(n^7)$ 的，~~非常优秀，能过样例~~，显然会超时。

# 优化：$O(n^5)$

$\sum\limits_{p=1}^i\sum\limits_{q=p+1}^i\sum\limits_{j=p-1}^{p-1+(i-2)\times(i-2)/2}\sum\limits_{k=q-1}^{j-1} I_{i-1,j-(p-1)}\times I_{i-1,k-(q-1)}=\sum\limits_{p=1}^i\sum\limits_{q=p+1}^i\sum\limits_{j=p-1}^{p-1+(i-2)\times(i-2)/2} I_{i-1,j-(p-1)}\sum\limits_{k=q-1}^{j-1} I_{i-1,k-(q-1)}$

$=\sum\limits_{p=1}^i\sum\limits_{q=p+1}^i\sum\limits_{j=p-1}^{p-1+(i-2)\times(i-2)/2} I_{i-1,j-(p-1)}SI_{i-1,j-q}$

有个细节，就是 $j-q$ 要 $\ge0$，所以 $j$ 要从 $q$ 开始枚举 $(q\ge p-1)$。

于是变成 $\sum\limits_{p=1}^i\sum\limits_{q=p+1}^i\sum\limits_{j=q}^{p-1+(i-2)\times(i-2)/2} I_{i-1,j-(p-1)}SI_{i-1,j-q}$

搞掉了一个 $n^2$ ，于是变成了 $O(n^5)$。

# 类似优化：$O(n^4)$

$\sum\limits_{p=1}^i\sum\limits_{q=p+1}^i\sum\limits_{j=q}^{p-1+(i-2)\times(i-2)/2} I_{i-1,j-(p-1)}SI_{i-1,j-q}$ 之前推到了这个式子。

下面优化 $q$。考虑 $\sum\limits_{q=p+1}^i\sum\limits_{j=q}^{p-1+(i-2)\times(i-2)/2}$，这等价于 $\sum\limits_{j=p+1}^{p-1+(i-2)\times(i-2)/2}\sum\limits_{q=p+1}^{\min(j,i)}$。

于是 $\sum\limits_{p=1}^i\sum\limits_{q=p+1}^i\sum\limits_{j=q}^{p-1+(i-2)\times(i-2)/2} I_{i-1,j-(p-1)}SI_{i-1,j-q}=\sum\limits_{p=1}^i\sum\limits_{j=p+1}^{p-1+(i-2)\times(i-2)/2} I_{i-1,j-(p-1)}\sum\limits_{q=p+1}^{\min(j,i)}SI_{i-1,j-q}$。

记 $SSI$ 为 $SI$ 的前缀和，则这个式子变成 $\sum\limits_{p=1}^i\sum\limits_{j=p+1}^{p-1+(i-2)\times(i-2)/2} I_{i-1,j-(p-1)}\times T$。

其中 $T=\begin{cases}SSI_{j-p-1}(j\le i)\\SSI_{j-p-1}-SSI_{j-i-1}(j>i)\end{cases}$(那篇题解这里就错了)。

# 终极优化：$O(n^3)$

都优化到这个份上了，相信大家能想到这个变成三次方的优化。

类似的 $\sum\limits_{p=1}^i\sum\limits_{j=p+1}^{p-1+(i-2)\times(i-2)/2}I_{i-1,j-(p-1)}\times T=\sum\limits_{j=2}^{p-1+(i-2)\times(i-2)/2}\sum\limits_{p=1}^{\min(i,j-1)}I_{i-1,j-(p-1)}\times T$。

显然是把 $I_{i-1,j-(p-1)}\times T$ 这整个去前缀和。

记 $S$ 为 $I_{k+2}\times SSI_k$ 的前缀和，这个式子就变成了：$\sum\limits_{j=2}^{i\times(i-1)/2} T$。

其中 $T=\begin{cases}S_{j-2}(j\le i)\\S_{j-2}-S_{j-i-1}-SSI_{j-i-1}\times(SI_{j}-SI_{j+i-1}) \end{cases}$ 。

这样就是 $O(n^3)$ 啦！

---
注意到三次方空间会爆，于是把枚举 $i$ 的那一维想办法优化一下就行了。

代码：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=505;
int n,mod,I[N*N>>1],SI[N*N>>1],SSI[N*N>>1],S[N*N>>1],f[N];
inline int AD(int x,int y){x+=y;return x>=mod?x-mod:x;}
inline void ad(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
int main()
{
	scanf("%d%d",&n,&mod);I[0]=SI[0]=SSI[0]=1;f[0]=0;
	for(int i=1;i<=n;i++)
	{
		f[i]=1ll*f[i-1]*i%mod;
		for(int j=2;j<=i*(i-1)/2;j++)
		{
			if(j<=i) ad(f[i],S[j-2]);
			else ad(f[i],AD(S[j-2],mod-AD(S[j-i-1],1ll*SSI[j-i-1]*AD(SI[j],mod-SI[j-i+1])%mod)));
		}
		for(int j=0;j<=i*(i-1)/2;j++)
		{
			if(j>=i) I[j]=AD(SI[j],mod-SI[j-i]);
			else I[j]=SI[j];
		}
		SI[0]=SSI[0]=I[0];S[0]=1ll*I[2]*SSI[0]%mod;
		for(int j=1;j<=i*(i+1)/2;j++) SI[j]=AD(SI[j-1],I[j]),SSI[j]=AD(SSI[j-1],SI[j]),S[j]=AD(S[j-1],1ll*I[j+2]*SSI[j]%mod);
	}
	printf("%d",f[n]);
	return 0;
}
```
个人感觉实现的比较优秀，从七次方优化到三次方的 $dp$ 还是很精妙的。

---

## 作者：pigstd (赞：0)

### CF1542E [E1](https://codeforces.com/contest/1542/problem/E1) [E2](https://codeforces.com/contest/1542/problem/E2)

蒟蒻不会做数数。

令 $f_x$ 表示排列长度为 $x$ 的时候的答案，那么所求的就是 $f_n$。

尝试递推出 $f$。对于一个新的 $n$，可以对第一位进行分类讨论：

- 第一位相同，那么这位对于后面的序列的逆序对的贡献也是相同的，所以 $p_{1\dots n}$ 的逆序对数大于 $q_{1 \dots n}$ 的逆序对数等价于 $p_{2\dots n}$ 的逆序对数大于 $q_{2 \dots n}$ 的逆序对数，字典序大小同理，这又相当于转化成了 $n-1$ 的时候的情况。第一位有 $n$ 个选择，那么有 $f_n = n \times f_{n-1}$。
- 第一位不同，那么可以尝试枚举 $p_1$ 和 $q_1$，显然有 $p_1<q_1$，这意味着无论后面的排列是什么，**字典序的条件已经满足了**，而排列 $p$ 的逆序对数又可以分为 $p_{2 \dots n}$ 的逆序对和 $p_1$ 的贡献，后者显然是 $p_1-1$，所以可以枚举 $p_{2 \dots n}$ 的逆序对数 $x$ 和 $q_{2 \dots n}$ 的逆序对数 $y$（$x+p_1-1>y+p_2-1$），然后算出 $n-1$ 的排列中有多少个逆序对数为 $x,y$ 的，然后乘起来就好。

后者可以先使用一个 dp 解决：$dp_{i,j}$ 表示长度为 $i$，逆序对数为 $j$ 的排列数，转移的时候枚举第一个数然后计算贡献即可。具体的，$\displaystyle dp_{i,j}=\sum_{k=1}^ndp_{i-1,j-k+1}$，直接算是 $\mathcal{O}(n^4)$ 的。

然而直接这么做的话时间复杂度是 $\mathcal{O}(n^7)$ 的根本过不去，注意到枚举了 $x$ 后 $y$ 只能为 $1 \dots (x+p1-p2-1)$，可以计算一下 $dp_{i,j}$ 的前缀和 $sum_{i,j}$ 表示长度为 $i$，逆序对数 $\le j$ 的排列数，然后就可以优化至 $\mathcal{O}(n^5)$，足以通过 E1。[code](https://codeforces.com/contest/1542/submission/121245585)。

~~比赛的时候想到了这里结果没写完 `\fn`~~。

考虑优化。发现这份代码可以分成两部分：求出 $dp_{i,j}$ 的部分和求出 $f$ 的部分。前者直接使用前缀和优化，一遍算 dp 一遍算前缀和就可优化至 $\mathcal{O}(n^3)$。

对于后者，有一个比较好想到的优化就是发现一对 $(p_1,q_1)$ 对 $f_n$ 产生的贡献只与 $q_1-p_1$ 有关，枚举 $q_1-p_1$ 然后乘上一个系数就可以把这部分优化为 $\mathcal{O}(n^4)$。[这部分的代码](https://codeforces.com/contest/1542/submission/121357579)。

观察一下剩下的这个东西，我们需要把这个东西优化至 $\mathcal{O}(n^3)$。

```cpp
for (int j=1;j<=i-1;j++)
	for (int p1=j+1;p1<=C2(i-1);p1++)
		f[i]=(f[i]+dp1[i-1][p1]*sum[i-1][p1-j-1]%Mod*(i-j))%Mod;
```

考虑**交换枚举顺序**，先枚举 $p1$（即上文中的 $x$）再枚举 $j$（即上文中的 $q_1-p_1$）。那么对于每个 $p1$，对于 $f_n$ 的贡献就是：

$\displaystyle dp_{i-1,p1}\times \sum_{j=1}^{i-1}sum_{i-1,p1-j-1}\times(i-j)=dp_{i-1,p1}\times (i\times \sum_{j=1}^{i-1}sum_{i-1,p1-j-1}-\sum_{j=1}^{i-1}j\times sum_{i-1,p1-j-1})$

$\displaystyle\sum_{j=1}^{i-1}sum_{i-1,p1-j-1}$ 这个东西可以通过对 $sum_i$ 再做一个前缀和 $\displaystyle sum2_{i,j}=\sum_{k=0}^jsum_{i,k}$ 从而快速算出，接下来要做的是快速求出 $\displaystyle \sum_{j=1}^{i-1}j\times sum_{i-1,p1-j-1}$。

考虑对这个东西进行“递推”。令 $b_{p1}=\displaystyle \sum_{j=1}^{i-1}j\times sum_{i-1,p1-j-1}$，那么经过一些推导后可以发现 $\displaystyle b_{p1+1}=b_{p1}+\sum_{j=1}^{i-1}sum_{i-1,p1-j}-(i-1)\times sum_{i-1,p1-i}$，又和 $sum2$ 有关系，都可以快速求出。综合一下就可以完成整个算法，其中空间不够需要滚动数组，时间复杂度 $\mathcal{O}(n^3)$，空间复杂度 $\mathcal{O}(n^2)$。

[code](https://codeforces.com/contest/1542/submission/121361994)。



---

## 作者：7KByte (赞：0)

数数好题。

求二元组 $(p,q)$ 的数量使得 $p,q$ 是长度为 $n$ 排列，其中 $p$ 的字典序更小，逆序对更多。

需要比字典序，我们枚举第一个不相同的的位置 $i$ 。那么 $i$ 前面的方案是 $i!\binom{n}{i}$。

我们枚举第 $i$ 位上 $p,q$ 分别填的数是 $l,r$ ，那么记对应后面的方案位 $F_{n-i,r-l+1}$ 。

不难发现，我们要求的 $F_{i,j}$ 就是二元组 $(u,v)$ 的数量，使得 $u,v$ 是长度为 $i$ 的排列，其中 $u$ 的逆序对数比 $v$ 的多 $j$ 个。

这玩意看起来就比较阴间，我们转化为求 $f_{i,j}$ 表示逆序对恰好多 $j$ 个。

我们可以直接计算 $g_{i,j}$ 表示长度为 $i$，逆序对数为 $j$ 的排列数，然后利用 $g$ 来计算 $f$，这样做时间复杂度是 $\mathcal{O}(N^5)$，前缀和优化以下可以做到 $\mathcal{O}(N^4)$ ，并且我手算了以下发现再计算一次前缀和并用卷积优化可以做到 $\mathcal{O}(N^3\log N)$ 。

以上的复杂度仍然不足以通过。

由于计算 $g$ 的复杂度已经到了极限，我们考虑直接计算 $f$ ，不难发现枚举第 $i$ 位上填的两个数，我们关心的只有这两个数的差。直接作差可以优化一维，时间复杂度是 $\mathcal{O}(N^4)$，直接卷积可以做到 $\mathcal{O}(N^3\log N)$ 。

再观察一下，发现我们求得大致是形如 $f_{i,j}=\sum |j-k|\times f_{i-1,k}$ ，拆掉绝对值后，可以将贡献拆为 $\sum\limits_{j} f_{i,j}$ 和 $\sum \limits_{j}j\times f_{i,j}$ 两部分（篇幅原因省略了系数），这两部分都可以通过前缀和求出来，所以直接前缀和优化可以做到 $\mathcal{O}(N^3)$ 。

直接开空间开不下，需要滚动数组优化。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 1005
using namespace std;
int n,P,f[N * N * 2],g[N * N * 2],p[N * N * 2],c[N][N],fac[N],ss,ans;
inline void ad(int &x,int y){x=(x+y)%P;if(x<0)x+=P;}
void maintain(int lim){
	g[ss - lim] = f[ss - lim];
	p[ss - lim] = - lim * f[0] % P + P;
	rep(j,-lim + 1,lim)
		p[j + ss] = (p[j - 1 + ss] + 1LL * f[j + ss] * j % P + P) % P,
		g[j + ss] = (g[j - 1 + ss] + f[j + ss]) % P;
}
int get(int *u,int l,int r){
	if(l > r)return 0;
	return (u[r + ss] - u[l - 1 + ss] + P) % P;
}
void calc(){
	f[ss] = 1;maintain(0);
	rep(i, 1, n - 1){
		int cur =  i * (i - 1) / 2;
		rep(k, -cur , cur){
			int L = max(k - i + 1, -cur);
			int R = min(k + i - 1, cur);
			f[k + ss] = 1LL * i * get(g, L, R) % P; 
			ad(f[k + ss], (1LL * get(g, k + 1, R) * k - get(p, k + 1, R)) % P);
			ad(f[k + ss], (get(p, L, k) - 1LL * get(g, L, k) * k % P) % P);
		}
		maintain(i * (i + 1) / 2);
		int w = n - i;
		int sum = n - w + 1;
		int ins = 1LL * c[n][w - 1] * fac[w - 1] % P;
		rep(l, 1, sum)rep(r, l + 1, sum){
			int k = r - l + 1;
			ans = (ans + 1LL * ins * get(g, k, cur)) % P;
		}
	}
}
signed main(){
	scanf("%d%d",&n,&P);ss = n * (n - 1)/2;
	fac[0] =1;rep(i,1,n)fac[i]=1LL*fac[i-1]*i%P;
	rep(i,0,n){
		c[i][0]=1;
		rep(j,1,i)c[i][j] = (c[i - 1][j - 1] + c[i - 1][j])%P;
	}
	calc();printf("%d\n",ans);
	return 0;
}
```

---

