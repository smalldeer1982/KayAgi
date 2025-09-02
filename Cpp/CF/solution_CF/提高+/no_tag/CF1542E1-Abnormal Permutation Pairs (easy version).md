# Abnormal Permutation Pairs (easy version)

## 题目描述

This is the easy version of the problem. The only difference between the easy version and the hard version is the constraints on $ n $ . You can only make hacks if both versions are solved.

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

## 作者：zhongpeilin (赞：13)

# CF1542E
## 题目大意：
给你一个 $n$ 和 $mod$，现在让你选择两个长度为 $n$ 的排列 $p$ 和 $q$，使得：  
1. $p$ 的字典序小于 $q$。
2. $p$ 的逆序对个数大于 $q$。

求方案数，模 $mod$。
## 解题思路：
首先看到题后我们不难想到先枚举 $p$ 和 $q$ 的最长相同前缀长度，再枚举第一个不相同的数在 $p$ 和 $q$ 分别是什么，然后我们在通过 dp 来预处理出有 $i$ 个数且有 $j$ 个逆序对的排列数，最后进行优化即可。  
所以我们先设 $dp_{i, j}$ 表示有多少个长度为 $i$ 的排列，且它的逆序对个数为 $j$。于是我们考虑第 $i$ 个数会增加多少逆序对，就有了方程：
$$dp_{i, j} = \sum_{k = 0}^{i - 1} dp_{i - 1, j - k}$$
这个可以前缀和优化，设 
$$f_{i, j} = \sum_{k = 0}^{j} dp_{i, k}$$
那么就有：
$$dp_{i, j} = f_{i - 1, j} - f_{i - 1, j - i}$$
预处理完了，我们接下来开始算答案，由于 $p$ 和 $q$ 的最长前缀的逆序对数量 $p$，$q$ 都有，所以直接不考虑。只需枚举相同前缀长度，相同前缀的后一位，以及 $p$，$q$ 后面的逆序对个数即可。  
$$\sum_{i = 0}^{n-1} A_{n}^{i} \times \sum_{x=1}^{n-i}\sum_{y=x+1}^{n-i}\sum_{j=0}^{C_{n-i-1}^{2}}\sum_{k=0}^{C_{n-i-1}^{2}} [j+x-1>k+y-1] \times dp_{n-i-1, j} \times dp_{n-i-1,k}$$
$A_{n}^{i}$ 是因为先从 $n$ 个数里选出 $i$ 个数，然后将他们任意排列不影响逆序对个数。  
然后你将判断条件改为 $k$ 的范围，就变成了：
$$\sum_{i = 0}^{n-1} A_{n}^{i} \times \sum_{x=1}^{n-i}\sum_{y=x+1}^{n-i}\sum_{j=0}^{C_{n-i-1}^{2}}\sum_{k=0}^{j+x-y-1} dp_{n-i-1, j} \times dp_{n-i-1,k}$$
接下来，因为相乘不好优化，但我们发现 $dp_{n-i-1, j}$ 和 $k$ 无关，将他提到外面去：
$$\sum_{i = 0}^{n-1} A_{n}^{i} \times \sum_{x=1}^{n-i}\sum_{y=x+1}^{n-i}\sum_{j=0}^{C_{n-i-1}^{2}}dp_{n-i-1, j} \times \sum_{k=0}^{j+x-y-1} dp_{n-i-1,k}$$
于是我们发现后面可以前缀和优化，正好是我们前面所设的 $f$ 能优化的，就变成了：
$$\sum_{i = 0}^{n-1} A_{n}^{i} \times \sum_{x=1}^{n-i}\sum_{y=x+1}^{n-i}\sum_{j=0}^{C_{n-i-1}^{2}}dp_{n-i-1, j} \times f_{n - i - 1, j + x - y -1}$$
接下来就是 E1 和 E2 的差距了：
## E1：
我们发现对于 $x$ 和 $y$，后面关心的只有 $y-x$ 的值而已，所以设 $z$ 表示 $y-x$，那么有：
$$\sum_{i = 0}^{n-1} A_{n}^{i} \times \sum_{z=1}^{n-i-1}\sum_{j=0}^{C_{n-i-1}^{2}}dp_{n-i-1, j} \times f_{n - i - 1, j - z -1} \times (n-i-z)$$
时间复杂度 $O(n^4)$，可以通过 E1，但是变成 $O(n^3)$ 就不太好优化了。  
## E2：
我们不可以枚举差值，但是优化之前的柿子不太好直接优化，怎么办？  
其实我们可以尝试一下：将 $j$ 在 $x$ 和 $y$ 值前枚举，这样有个好处，就是不用算乘法了。 
$$\sum_{i = 0}^{n-1} A_{n}^{i} \times \sum_{j=0}^{C_{n-i-1}^{2}}dp_{n-i-1, j} \times \sum_{x=1}^{n-i}\sum_{y=x+1}^{n-i}f_{n - i - 1, j + x - y -1}$$
接下来，我们发现，后面的 $f$ 的下标是连续的，是 $j+x-(n-i)-1 \sim j-2$ 这一段，还可以用前缀和优化。设
$$g_{i, j} = \sum_{k=0}^{j}f_{i, k}$$
那么转移式子又变成了
$$\sum_{i = 0}^{n-1}\sum_{j=0}^{C_{n-i-1}^{2}}dp_{n-i-1, j} \times \sum_{x=1}^{n-i}g_{n-i-1,j-2}-g_{n-i-1,j+x-n+i-2}$$
有了这个柿子之后，发现 $g_{n-i-1, j-2}$ 和 $x$ 无关，那么可以提到外面，变成：
$$\sum_{i = 0}^{n-1} A_{n}^{i} \times \sum_{j=0}^{C_{n-i-1}^{2}}dp_{n-i-1, j} \times (g_{n-i-1,j-2} \times (n-i) - \sum_{x=1}^{n-i}g_{n-i-1,j+x-n+i-2})$$
然后呢？其实你看一眼后面就又是一个可以前缀和优化的东西 QWQ！设
$$h_{i, j} = \sum_{k=0}^{j}g_{i, k}$$
则前缀和要算的区间是 $j-1-n+i \sim j-2$，最后，柿子变成了：
$$\sum_{i = 0}^{n-1} A_{n}^{i} \times \sum_{j=0}^{C_{n-i-1}^{2}}dp_{n-i-1, j} \times (g_{n-i-1,j-2} \times (n-i) - (h_{n-i-1, j-2} - h_{n-i-1, j-n+i-2}))$$
时间复杂度 $O(n^3)$，可以通过 E2，不过要注意一下空间，除了 $dp$ 数组预处理外， $f,g,h$ 都要是一维的，否则空间受不了，还有这个 E2 还要卡常。  
最后记得处理一下前缀和边界。  
## AC CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 505, M = 500 * 499 / 2 + 2;
int n, mod, dp[N][M];
long long f[M], g[M], h[M];
long long C[N][N], jie[N];
int main(){
	cin >> n >> mod;
	for(int i = 0; i <= n; i++){
		C[i][0] = 1;
		for(int j = 1; j <= i; j++){
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}
	}
	jie[0] = 1;
	for(int i = 1; i <= n; i++) jie[i] = (jie[i - 1] * i) % mod;
	
	dp[0][0] = 1;//这里也要 
	for(int i = 0; i <= n * (n - 1) / 2; i++) f[i] = 1; //记得改 
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= n * (n - 1) / 2; j++){ //dp要开二维，因为后面要用n-i-1的dp 
			if(j - i + 1 <= 0) dp[i][j] = f[j];  
			else dp[i][j] = (f[j] - f[j - i] + mod) % mod;
		}
		f[0] = dp[i][0];
		for(int j = 1; j <= n * (n - 1) / 2; j++) {
			f[j] = (f[j - 1] + dp[i][j]) % mod;
		}
	}
	
	long long ans = 0, val = 1;
	for(int i = 0; i < n; i++){
		f[0] = g[0] = h[0] = dp[n - i - 1][0];
		for(int j = 1; j <= n * (n - 1) / 2; j++) { //现推，不然空间受不了 
			f[j] = (f[j - 1] + dp[n - i - 1][j]) % mod;
			g[j] = (g[j - 1] + f[j]) % mod;
			h[j] = (h[j - 1] + g[j]) % mod;
		}
		
		val = C[n][i] * jie[i] % mod;
		for(int j = 2; j <= (n - i - 1) * (n - i - 2) / 2; j++){ //这里从2开始就行，因为如果j<2那么j-2和j+i-n-2肯定都是负数下标，然后上界不能为C[n-i-1][2]，因为mod不一定大于N，但E1卡了，E2没卡。 
			ans = (ans + (g[j - 2] * (n - i) % mod - h[j - 2] + (j + i >= n + 2 ? h[j + i - n - 2] : 0) + mod) * dp[n - i - 1][j] % mod * val) % mod;
			//套狮子 
		}
		//val = val * (n - i) % mod; 这句话可以让你不算组合数和阶乘，因为 C[n][i] * i! = A[n][i] 
	}
	cout << ans << endl;
	return 0;
}
```
创作不易，点个赞吧 QWQ！

---

## 作者：Pengzt (赞：7)

[CF1542E1](https://www.luogu.com.cn/problem/CF1542E1)

首先时间复杂度肯定是 $\mathcal{O}(n^3)$ 的。

容易想到先枚举最长公共前缀，然后枚举 $p_{len+1}$ 和 $q_{len+1}$，再枚举逆序对数进行统计。

令 $f_{i,j}$ 表示有 $j$ 个逆序对的 $i$ 阶排列的个数。

易得转移 $f_{i,j}=\sum\limits_{k=j-i+1}^{j}f_{i-1,k}$，使用前缀和可以做到 $\mathcal{O}(n^3)$。

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

时间复杂度降至 $\mathcal{O}(n^4)$。

已经可以通过 E1.

时间复杂度：$\mathcal{O}(n^4)$。

空间复杂度：$\mathcal{O}(n^3)$。

[评测记录](https://codeforces.com/contest/1542/submission/220146595)

---

## 作者：tzc_wk (赞：5)

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

## 作者：JiaY19 (赞：1)

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

## 作者：shuangmu (赞：1)

# CF1542E1 Abnormal Permutation Pairs (easy version) 题解

~~不会 Hard version~~

对于第一个限制字典序，我们可以考虑枚举前 $i$ 位相同，然后考虑后 $n-i$ 位。我们只需要保证 $p_{i+1} < q_{i+1}$ 即可。

我们设 $len = n - i$。由于前 $i$ 位完全相同，所以前 $i$ 位内部的逆序对个数以及前 $i$ 位与后 $len$ 位之间产生的逆序对个数也是相同的，因此对于第二个条件，我们只需要满足 $p$ 后 $len$ 位的逆序对个数严格大于 $q$ 的后 $len$ 位的即可。

因为逆序对仅与相对大小有关，所以后 $len$ 位可以抽象成一个 $1$ 到 $len$ 的排列。我们设 $f_{len, j, k}$ 表示长度为 $len$ 的排列，第一位是 $j$，有 $k$ 个逆序对的方案数。则长度每增加一位，只用考虑新加入的 $len$ 作为开头以及其他数作为开头的转移。有：
$$
\begin{aligned}
f_{len, len, k} = \sum_{j = 1}^{len-1} f_{len-1, j, k-(len-1)}  \\
f_{len, j, k} = \sum_{t = 0}^{len-2} f_{len-1, j, k-t}  (1 \leq j<len)
\end{aligned}
$$
对于第一种转移，我们只需把上一层所有数作为开头的方案加起来；对于第二种转移，我们考虑 $len$ 插入到除了开头以外的其他位置产生的新的逆序对即可。

其中第二个转移是 $O(n^5)$ 的，我们发现枚举的 $t$ 是一个区间内的答案，所以可以前缀和优化可以到 $O(n^4)$。

然后我们来考虑统计答案。我们设逆序对个数上界 $mx = \frac{len \times (len-1)}{2}$，$sp$、$sq$ 分别为 $p$ 和 $q$ 中后 $len$ 位的逆序对个数，一个朴素的答案式子如下：
$$
\sum_{len = 1}^{n} {n \choose len} (n-len)! \sum_{j = 1}^{len} \sum_{sp = 1}^{mx} \sum_{k = j+1}^{len} \sum_{sq = 0}^{sp-1} f_{len, j, sp} \times f_{len, k, sq}
$$
我们从 $n$ 中选取 $len$ 个数作为后缀，则剩下的 $n-len$ 个数做前缀。前缀要求完全相同，但可以随意排列顺序。后半部分就是通过枚举来满足第一和第二个限制。

显然是一个 $O(n^7)$ 的式子。我们调整一下这个式子：
$$
\sum_{len = 1}^{n} {n \choose len} (n-len)! \sum_{j = 1}^{len} \sum_{sp = 1}^{mx} f_{len, j, sp} \times (\sum_{k = j+1}^{len} \sum_{sq = 0}^{sp-1}  f_{len, k, sq})
$$
会发现后半部分是个矩形内的和，可以用二维前缀和优化到 $O(1)$ 求出。前半部分枚举是 $O(n^4)$ 的。

简单版就做完了，复杂度 $O(n^4)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 54;
int mod;

void add(int &a, int b) {
	a = (a+b)%mod;
}
int f[N][N][N*N];
int n;
int fac[N];
int sum1[N][N][N*N];//第一个前缀和（可以滚动数组优化）
int sum2[N][N][N*N];//第二个前缀和（也可以滚动数组）
int C[N][N];

void prework() {
	fac[0] = 1;
	for(int i = 1; i<=n; ++i) {
		fac[i] = 1ll*fac[i-1]*i%mod;
	}
	C[0][0] = 1;
	for(int i = 1; i<=n; ++i) {
		C[i][0] = 1;
		for(int j = 1; j<=i; ++j) {
			C[i][j] = (C[i-1][j] + C[i-1][j-1])%mod;
		}
	}//预处理阶乘和组合数
}
int main() {
	scanf("%d%d", &n, &mod);
	prework();
	f[1][1][0] = 1;
	for(int i = 2; i<=n; ++i) {
		for(int j = 1; j<i; ++j) {
			for(int k = i-1; k<=(i*(i-1)/2); ++k) {
				add(f[i][i][k], f[i-1][j][k-(i-1)]);
			}	
		}//新加入一个最大的数，让它作为开头

		for(int j = 1; j<i; ++j) {
			sum1[i-1][j][0] = f[i-1][j][0];
			for(int o = 1; o<=(i*(i-1)/2); ++o) {
				sum1[i-1][j][o] = f[i-1][j][o];
				add(sum1[i-1][j][o], sum1[i-1][j][o-1]);
			}//计算需要的前缀和
			for(int o = 0; o<=(i*(i-1)/2); ++o) {
				if(o > i-2) {
					add(f[i][j][o], (sum1[i-1][j][o] - sum1[i-1][j][o-(i-2)-1])%mod);
					if(f[i][j][o] < 0) f[i][j][o]+=mod;
				} else f[i][j][o] = sum1[i-1][j][o];
			}
		}//对于其他数作为开头的情况
	}
	int ans = 0;
	for(int i = 0; i<n-1; ++i) {
		int ret = 1ll*fac[i]*C[n][i]%mod;
		int len = n-i;
		int sum = 0;
		for(int j = 1; j<=len; ++j) {
			sum2[len][j][0] = f[len][j][0];
			add(sum2[len][j][0], sum2[len][j-1][0]);
			for(int k = 1; k<=(len*(len-1)/2); ++k){
				sum2[len][j][k] = f[len][j][k];
				add(sum2[len][j][k], (1ll * sum2[len][j][k-1] + 1ll * sum2[len][j-1][k] + 1ll * mod - 1ll*sum2[len][j-1][k-1])%mod);
			}
		}//预处理二维前缀和。

		for(int j = 1; j<=len; ++j) {
			for(int oa = 1; oa<=(len*(len-1)/2) ;++oa) {
				add(sum, 1ll*f[len][j][oa] * (1ll*sum2[len][len][oa-1] - sum2[len][j][oa-1])%mod);
			}
		}
		add(ans, 1ll*ret*sum%mod);
	}
	if(ans<0) ans+=mod;
	printf("%d\n", ans);
	return 0;
}
```



---

## 作者：2022dyx (赞：0)

我们显然可以忽略掉串前面的相同字符，只需在最后的答案前面乘点系数，这样字典序就等价于排列的首位。长度、首位、逆序对个数均相同的排列显然是本质相同的，由于 $n$ 非常小，所以枚举 $O(n^4)$ 的本质不同的排列数算答案是可以接受的。设 $dp_{i,j,k}$  表示长度为 $i$，首位为 $j$，逆序对有 $k$ 个的排列数，有转移 $dp_{i,j,k}=\sum_l dp_{i,l,k-(j-1)}$，前缀和优化一下就是 $O(1)$ 转移。再看答案，有：
$$ans=\sum_{i=1}^n\binom{n}{i}(n-i)!\sum_j\sum_kdp_{i,j,k}\sum_{j'}\sum_{k'}[j>j'][k<k']dp_{i,j',k'}$$
直接做是 $O(n^7)$ 的，但是把后面两个求和用二维前后缀和优化一下就能到 $O(n^4)$，可以通过。

下面是代码：
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define file(x) freopen(#x ".in", "r", stdin); freopen(#x ".out", "w", stdout);
#define add(x, y) (x = x + (y), x = x >= mod ? x - mod : x)
#define For for (int i = 1; i <= n; ++i) for (int j = 1; j <= i; ++j) for (int k = m; k >= j - 1; --k)
void DEBUG(int x, ...) { va_list y; va_start(y, x); while(x--) cout << va_arg(y, int) << ' '; va_end(y); cout << '\n'; }
constexpr int N = 5e1 + 5;
int n, m, mod, fac[N], C[N][N], dp[N][N][N * N], sum[N][N * N], pre[N][N][N * N], ans;
signed main() {
    cin.tie(0) -> sync_with_stdio(false); 
    cin >> n >> mod, m = n * (n - 1) / 2;
    sum[0][0] = fac[0] = 1;
    For add(dp[i][j][k], sum[i - 1][k - j + 1]), add(sum[i][k], dp[i][j][k]);
    For pre[i][j][k] = dp[i][j][k];
    For add(pre[i][j][k], pre[i][j][k + 1]);
    For add(pre[i][j][k], pre[i][j - 1][k]);
    for (int i = 0; i <= n; ++i) C[i][0] = 1;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= i; ++j) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
    For add(ans, dp[i][j][k] * pre[i][j - 1][k + 1] % mod * C[n][i] % mod * fac[n - i] % mod);
    cout << ans;
}
```

---

## 作者：Jerrywang09 (赞：0)

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

我们知道，设 $y-x=d$，则 $1\le x,y\le n$ 的 $(x,y)$ 对共有 $n-d$ 个。枚举这个 $d$，最终的答案式为：

$$
\begin{align*}
ans&=\sum_{i=0}^{n-1}\text{P}_n^i\sum_{a=0}^{\binom {n-i-1} 2} f(n-i-1, a)\sum_{d=1}^{n-i} (n-i-d)\cdot g(n-i-1, a-d-1)
\end{align*}
$$

扩展阅读：本题的加强版[题解](/article/dh8cqkoy)。

```cpp
// Title:  Abnormal Permutation Pairs (easy version)
// Source: CF1542E1
// Author: Jerrywang
#include <cstdio>
#include <iostream>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=55;
using namespace std;

int n, mod; ll f[N][N*N], g[N][N*N], ans;

void upd(ll &x, ll y)
{
    x+=y;
    if(x<0) x+=mod;
    if(x>=mod) x-=mod;
}
ll C(int n) {return n*(n-1)>>1;}

int main()
{
#ifdef Jerrywang
    freopen("E:/OI/in.txt", "r", stdin); ios::sync_with_stdio(0);
#endif
    scanf("%d%d", &n, &mod);
    f[1][0]=1;
    rep(i, 0, C(n)) g[1][i]=1;
    rep(i, 2, n)
    {
        rep(j, 0, C(i))
        {
            f[i][j]=g[i-1][j];
            if(j-(i-1)-1>=0) upd(f[i][j], -g[i-1][j-(i-1)-1]);
        }
        g[i][0]=f[i][0];
        rep(j, 1, C(n))
        {
            g[i][j]=g[i][j-1]; upd(g[i][j], f[i][j]);
        }
    }
    ll P=1;
    rep(i, 0, n-1)
    {
        rep(a, 0, C(n-i-1))
        {
            ll tmp=0;
            rep(d, 1, n-i-1)
            {
                if(a-d-1>=0)
                    upd(tmp, (n-i-d)*g[n-i-1][a-d-1]%mod);
            }
            upd(ans, P*f[n-i-1][a]%mod*tmp%mod);
        }
        P=P*(n-i)%mod;
    }
    printf("%lld", ans);

    return 0;
}
```

---

