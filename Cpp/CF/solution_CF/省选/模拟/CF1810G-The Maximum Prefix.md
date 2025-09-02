# The Maximum Prefix

## 题目描述

You're going to generate an array $ a $ with a length of at most $ n $ , where each $ a_{i} $ equals either $ 1 $ or $ -1 $ .

You generate this array in the following way.

- First, you choose some integer $ k $ ( $ 1\le k \le n $ ), which decides the length of $ a $ .
- Then, for each $ i $ ( $ 1\le i \le k $ ), you set $ a_{i} = 1 $ with probability $ p_{i} $ , otherwise set $ a_{i} = -1 $ (with probability $ 1 - p_{i} $ ).

After the array is generated, you calculate $ s_{i} = a_{1} + a_{2} + a_{3}+ \ldots + a_{i} $ . Specially, $ s_{0} = 0 $ . Then you let $ S $ equal to $ \displaystyle \max_{i=0}^{k}{s_{i}} $ . That is, $ S $ is the maximum prefix sum of the array $ a $ .

You are given $ n+1 $ integers $ h_{0} , h_{1}, \ldots ,h_{n} $ . The score of an array $ a $ with maximum prefix sum $ S $ is $ h_{S} $ . Now, for each $ k $ , you want to know the expected score for an array of length $ k $ modulo $ 10^9+7 $ .

## 说明/提示

In the first test case, if we choose $ k=1 $ , there are $ 2 $ possible arrays with equal probabilities: $ [1] $ and $ [-1] $ . The $ S $ values for them are $ 1 $ and $ 0 $ . So the expected score is $ \frac{1}{2}h_{0} + \frac{1}{2}h_{1} = \frac{3}{2} $ . If we choose $ k=2 $ , there are $ 4 $ possible arrays with equal probabilities: $ [1,1] $ , $ [1,-1] $ , $ [-1,1] $ , $ [-1,-1] $ , and the $ S $ values for them are $ 2,1,0,0 $ . So the expected score is $ \frac{1}{2}h_{0} + \frac{1}{4}h_{1} + \frac{1}{4}h_{2} = \frac{7}{4} $ .

In the second test case, no matter what the $ S $ value is, the score is always $ 1 $ , so the expected score is always $ 1 $ .

## 样例 #1

### 输入

```
4
2
1 2
1 2
1 2 3
3
1 3
1 4
5 5
1 1 1 1
3
2 5
4 6
0 2
4 3 2 1
5
5 6
5 7
1 6
1 3
4 7
9 0 4 5 2 4```

### 输出

```
500000005 750000007 
1 1 1 
200000005 333333339 333333339 
500000005 880952391 801587311 781746041 789304620```

# 题解

## 作者：EuphoricStar (赞：31)

感觉是比较 educational 的题。

拿到题目应该有一个大致思路，就是考虑最大前缀和的求法，再把它扔到状态里面。

最大前缀和有两种求法：

- 从前往后求，需要维护当前前缀和 $s$，当前最大前缀和 $mx$，需要记录两个变量，无法承受。
- 从后往前求，只需记录当前最大前缀和 $mx$，从 $[i + 1, n]$ 的最大前缀和转移到 $[i, n]$ 的最大前缀和时，我们贪心地判断 $a_i$ 是否属于最大前缀和，即 $mx \gets \max(mx + a_i, 0)$。

于是我们有一个初步的 dp 思路：设 $f_{i, j}$ 为当前考虑了 $[i, n]$，其最大前缀和为 $j$。有转移：

$$\begin{cases} p_i f_{i + 1, j} \to f_{i, j + 1} \\ (1 - p_i) f_{i + 1, j} \to f_{i, \max(j - 1, 0)} \end{cases}$$

初值为 $f_{n + 1, 0} = 1$，最终 $ans = \sum\limits_{i = 0}^n h_i f_{1, i}$。

我们算的只是长度为 $n$ 的答案，我们希望对于每个长度 $l$ 都求出答案，但是直接做是 $O(n^3)$ 的。

注意到我们每次 dp 的转移都是固定的，只是初值不同（长度为 $l$ 时 dp 初值为 $f_{l + 1, 0} = 1$），因此 $f_{i, j}$ 对答案的贡献也是固定的。我们不妨使用**反推贡献系数**的 trick，设 $g_{i, j}$ 为 $f_{i, j}$ 对 $ans$ 的贡献系数，那么有转移：

$$g_{i + 1, j} = p_i g_{i, j + 1} + (1 - p_i) g_{i, \max(j - 1, 0)}$$

初值为 $g_{1, i} = h_i$。最终长度为 $l$ 的答案为 $g_{l + 1, 0}$。

时间复杂度降至 $O(n^2)$。

[code](https://codeforces.com/problemset/submission/1810/215315436)

---

## 作者：Ecrade_ (赞：26)

分享一种理解起来可能更为简单的思路。

假设我们钦定了 $a$ 数组的最大前缀和为 $x$，那么 $a$ 的前缀和数组 $s$ 需要满足：

1. $\forall\ 0\le i\le n$，$s_i\le x$。
2. $\exists\ 0\le i\le n$，$s_i=x$。

形象地，我们称这个钦定的最大前缀和 $x$ 为 “目标”。令 $f_{i,j,0/1}$ 表示仅考虑前 $i$ 个元素，当前前缀和 $s_i$ 离目标还差 $j$，之前达到过 / 未达到过目标的期望得分。则对于长度 $i$，其答案即为当前所有达到过目标的状态的期望得分之和。

初始化：$f_{0,i,[i=0]}=h_i$。

转移方程：$f_{i,j,o\ |\ [j=0]}=f_{i-1,j+1,o}\times p_i+f_{i-1,j-1,o}\times (1-p_i)$。

长度为 $k$ 时的答案：$\sum\limits_{i=0}^nf_{k,i,1}$。

注意处理边界问题，具体见代码。

时间复杂度为 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
int t,n,x,y,p[5009],f[5009][5009][2];
inline int read(){
	int s = 0,w = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0'){ if (ch == '-') w = -1; ch = getchar();}
	while (ch <= '9' && ch >= '0') s = (s << 1) + (s << 3) + (ch ^ 48),ch = getchar();
	return s * w;
}
inline void add(int &x,int y){x += y; if (x >= mod) x -= mod;}
int qp(int x,int y){
	int a = 1,b = x;
	while (y){
		if (y & 1) a = (ll) a * b % mod;
		b = (ll) b * b % mod,y >>= 1;
	}
	return a;
}
int main(){
	t = read();
	while (t --){
		n = read();
		for (int i = 1;i <= n;i += 1) x = read(),y = read(),p[i] = (ll) x * qp(y,mod - 2) % mod;
		for (int i = 0;i <= n;i += 1) f[0][i][!i] = read();
		for (int i = 1;i <= n;i += 1){
			int ans = 0;
			for (int j = 0;j <= n;j += 1){
				f[i][j][0] = f[i][j][1] = 0;
				for (int o = 0;o < 2;o += 1){
					if (j < n) add(f[i][j][o | (!j)],(ll) f[i - 1][j + 1][o] * p[i] % mod);
					if (j > 0) add(f[i][j][o | (!j)],(ll) f[i - 1][j - 1][o] * (mod + 1 - p[i]) % mod);
				}
				add(ans,f[i][j][1]);
			}
			printf("%d ",ans);
		}
		puts("");
	}
	return 0;
}
```


---

## 作者：Schi2oid (赞：9)

# CF1810G The Maximum Prefix 题解

典型的反转 dp，整理一下此类题思路。

[博客食用效果更佳](https://schi2oid.github.io/2023/04/05/CF1810G%20The%20Maximum%20Prefix%20%E9%A2%98%E8%A7%A3/)

## 题意简述

你现在要按照如下方式生成一个长度为 $k(k\in[1,n])$ 的数组：

- $\forall i\in[1,k]$，有 $p_i$ 的概率设 $a_i=1$，有 $1-p_i$ 的概率设 $a_i=-1$。

对于一个长度为 $k$ 的数组，计算 $s_i=a_1+a_2+a_3+...+a_i$。特别地，$s_0=0$。此时 $s$ 数组的最大前缀和 
 $ S=\displaystyle \max_{i=0}^{k}{s_{i}} $。现在给定 $n+1$ 个正整数 $h_0,h_1,...,h_n$。该数组最大前缀和为 $S$ 时，该数组的分数为 $h_s$。

要求对于所有 $k$，求出生成出的数组的期望分数对 $10^9+7$ 取模的结果。

$n\le 5000$。

## 思路分析

正向考虑困难，因为我们要加入一个新的前缀和，而这个前缀和的值与其前一位前缀和的值相关，所以需要同时存下最大的 $s$ 和当前的 $s$，复杂度升天，那么反向考虑。

此时容易发现，我们向一个序列的开头加入一个 $1$ 或 $-1$，会将之后的所有前缀和 $+1$ 或 $-1$，同时再加入一个新的前缀和。这是相对来说容易转移的。因此，对于某一个 $k$，我们有如下朴素 dp 过程，设 $f_{i,j}$ 表示数组 $[a_i,a_{i+1},…,a_k]$ 的 $S$ 值为 $j$ 时的期望分数：

$$
p_{i-1}f_{i,j}\rightarrow f_{i-1,j+1}\\
(1-p_{i-1})f_{i,j}\rightarrow f_{i-1,\max\{j-1,0\}}
$$

直接进行这个过程，由于需要枚举 $k$，复杂度是 $O(n^3)$ 的，不足以通过此题。

考虑状态所设两维难以压掉，尝试去除枚举 $k$ 所带来的复杂度。观察 dp 过程，我们共进行了 $O(n)$ 次 dp，而每次 dp 都指向同一组终止状态。因此考虑反转整个 dp 过程，我们从终止状态出发，进行反向转移，最终抵达初始状态。

刚才所设的是“已经”，那么我们可以设“还需要”。具体来说，我们设 $g_{i,j}$ 表示数组 $[a_{i+1},a_{i+2},…,a_{k}]$ 的 $S$ 值需要为 $j$ 的最终数组的期望分数，换句话来说，我们钦定了 $[a_{i+1},a_{i+2},…,a_{k}]$ 的 $S$ 值为 $j$，$g_{i,j}$ 表示在这样的限制条件下，$[a_1,a_2,…,a_k]$ 的期望分数。那么我们有 $g_{0,i}=h_i$，$k$ 的答案即为 $g_{k,0}$。有转移：

$$
g_{i,j}=p_ig_{i-1,j+1}+(1-p_i)g_{i-1,\max\{j-1,0\}}
$$

容易发现与之前的转移形式一致。

此时有可能会产生这样的疑惑：如果仅仅钦定了 $[a_i,a_{i+1},…,a_{k}]$ 的 $S$ 值为 $0$，那么有一部分填法中 $[a_{i+1},a_{i+2},…,a_{k}]$ 的 $S$ 值为 $0$，另一部分 $S$ 值为 $1$，那么为什么 $g_{i-1,0}$ 能够同时对 $g_{i,0}$ 和 $g_{i,1}$ 做等量的贡献？

这时，考虑 dp 定义。我们此时并不知道 $[a_i,a_{i+1},…,a_{k}]$ 的填法，我们只是要求这一数组的 $S$ 值为 $j$。那么，如果我们在 $a_i$ 处填了 $-1$，无论我们要求 $[a_{i+1},a_{i+2},…,a_{k}]$ 的 $S$ 值填为 $0$ 还是 $1$，都符合我们对 $[a_i,a_{i+1},…,a_{k}]$ 的要求，自然都应该进行转移。

## 启发

- 前缀和问题，正难则反。
- 多起点单终点问题，考虑反转 dp。
- 反转 dp 需要明确状态定义。

## 代码

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int p[50005],h[50005],dp[5005][5005];
int qkp(int x,int k){
	int ret=1;
	while(k){
		if(k&1) ret=ret*x%mod;
		k>>=1;
		x=x*x%mod;
	}
	return ret;
}
int ny(int x){return qkp(x,mod-2);}
signed main(){
	int t,n,x,y;
	cin>>t;
	while(t--){
		scanf("%lld",&n);
		for(int i=0;i<=n+1;i++)
			for(int j=0;j<=n+1;j++)
				dp[i][j]=0;
		for(int i=1;i<=n;i++){
			scanf("%lld%lld",&x,&y);
			p[i]=x*ny(y)%mod;
		}
		for(int i=0;i<=n;i++) scanf("%lld",&h[i]),dp[0][i]=h[i];
		for(int i=1;i<=n;i++){
			for(int j=0;j<=n;j++){
				dp[i][j]=(p[i]*dp[i-1][j+1]%mod+(1-p[i]+mod)*dp[i-1][max(j-1,0ll)]%mod)%mod;
			}
			printf("%lld ",dp[i][0]);
		}
		puts("");
	}
	return 0;
}
```



---

## 作者：EXODUS (赞：4)

# Part 1：前言
小清新计数题，有很大的启发意义，我上来就被干烂了/cf。

# Part 2：正文
小清新计数题，有很大的启发意义，我上来就被干烂了/cf。

首先考虑一个 naive 的 dp，设 $f_{i,j,k}$ 表示到达 $i$ 位置，最大前缀和为 $j$，当前前缀和为 $k$ 的期望答案，这样就是一个 $O(n^3)$ 的做法，但我们发现 $i,j,k$ 这三维好像没有一维是可以砍掉的，这为我们优化复杂度带来了困难。

考虑去改变我们求最大前缀和的方式。倒序考虑，我们惊讶的发现对于一段后缀，其于整个序列的最大前缀和有贡献的部分即为其最大前缀和！

证明是容易的，考虑到每在前面插入一个数实质上是增加一个前缀和并把所有已有的前缀和加上他的值。

至此我们可以设计出一个状态数是 $O(n^2)$ 的 dp：设 $f_{i,j}$ 表示把前 $i$ 个数填完，当前 $[i+1,n]$ 的最大后缀和为 $j$ 的期望答案。转移时我们考虑第 $i+1$ 个数填什么，如果 $a_{i+1}=1$，则可以以 $p_{i+1}$ 的系数转移到 $f_{i+1,\max(j-1,0)}$，否则以 $q_i$ 的系数转移到 $f_{i+1,j+1}$。

如何统计答案？我们发现，对于一段后缀，若其最大前缀和等于 $0$，则其于答案一定无贡献，则长度为 $i$ 的答案即为 $f_{i,0}$。

这个最大前缀和的转化感觉很有意思，对于一部分题目可以直接砍掉一些复杂度，很有启发意义。

# Part 3：代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
int read(){
	int ans=0,flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flg;
}
template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}
const int N=5e3+7,mod=1e9+7;
int T,n,f[N][N],p[N],q[N],scr[N];
int qp(int b,int m=mod-2){
	int res=1;
	for(;m;m>>=1,b=(ll)b*b%mod)if(m&1)res=(ll)res*b%mod;
	return res;
}
void add(int &x,int y){x+=y-mod,x+=x>>31&mod;}
void solve(){
	read(n);
	for(int i=1,x,y;i<=n;i++){
		read(x,y);
		p[i]=(ll)x*qp(y)%mod;
		add(q[i]=1,mod-p[i]);
	}
	for(int i=0;i<=n;i++)read(f[0][i]);
	for(int i=1;i<=n;i++)
		for(int j=0;j<=n;j++)
			add(f[i][j]=(ll)f[i-1][j+1]*p[i]%mod,(ll)f[i-1][max(j-1,0)]*q[i]%mod);
	for(int i=1;i<=n;i++)printf("%d ",f[i][0]);
	printf("\n");
}
int main(){
	read(T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：APJifengc (赞：1)

最大值并不好考虑，我们尝试拆贡献，求最大值小于等于 $k$ 的概率，然后将概率差分一下即可得到恰好等于 $k$ 的概率，而最大值小于等于 $k$ 的概率是很容易通过一个 $O(n^2)$ DP 求出来的，但是这样我们还需要再枚举一个 $k$，复杂度 $O(n^3)$，难以接受。

那么我们可以考虑不对概率进行差分，而是对权值进行差分，这样我们只需要将所有位置的和加起来就是答案了。而上述做法可以合并起来一起做，具体设 $f_{i, j}$ 表示考虑到第 $i$ 个数，现在距离上限还有 $j$，直接转移即可，复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5005, P = 1000000007;
int qpow(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % P;
        a = 1ll * a * a % P;
        b >>= 1;
    }
    return ans;
}
int T, n, p[MAXN], h[MAXN];
int f[MAXN][MAXN * 2];
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            int a, b; scanf("%d%d", &a, &b);
            p[i] = 1ll * a * qpow(b, P - 2) % P;
        }
        for (int i = 0; i <= n; i++) {
            scanf("%d", &h[i]);
        }
        for (int i = 0; i < n; i++) {
            h[i] = (h[i] - h[i + 1] + P) % P;
        }
        for (int i = 0; i <= n; i++) {
            f[0][i] = h[i];
        }
        for (int i = n + 1; i <= 2 * n; i++) f[0][i] = 0;
        for (int i = 1; i <= n; i++) {
            int ans = 0;
            for (int j = 0; j <= 2 * n; j++) {
                f[i][j] = 0;
                if (j != 2 * n) f[i][j] = (f[i][j] + 1ll * p[i] * f[i - 1][j + 1]) % P;
                if (j) f[i][j] = (f[i][j] + 1ll * (1 - p[i] + P) * f[i - 1][j - 1]) % P;
                ans = (ans + f[i][j]) % P;
            }
            printf("%d ", ans);
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：hgzxwzf (赞：1)

## [CF1810G](https://www.luogu.com.cn/problem/CF1810G)

设 $dp_{i,j,k}$ 表示考虑了前 $i$ 个位置，当前前缀和为 $j$，最大前缀和为 $k$ 的概率，时间复杂度 $O(n^3)$。

考虑计算位置 $i$ 作为最大前缀和的贡献。设长度为 $n$，满足 $a[1,i]$ 的任意后缀和 $> 0$、$a(i,n]$ 的任意前缀和 $\le 0$ 时 $i$ 才会对 $n$ 产生贡献，贡献为 $h_{s_i}\times P$，$P$ 指总概率。

$P$ 由两部分组成，设 $dp_{i,j}$ 表示从 $i$ 位置向前，初值为 $j$，填完 $i$ 到 $1$ 所有位置后的期望，$f_{i,n}$ 表示从 $i$ 位置向后，填完 $i$ 到 $n$ 满足任意前缀和 $\le 0$ 的概率，得到 $i$ 对 $n$ 的贡献为 $dp_{i,j}\times f_{i,n}$。

先考虑前缀。对于 $j=1\sim n$，有 $dp_{0,j}=h_j$。对于 $i\ge 1$，$dp_{i,j}=dp_{i-1,j+1}\times p_i+dp_{i-1,j-1}\times q_i$，从 $dp_{i-1,j-1}$ 转移需要满足 $j>1$，因为需要保证后缀和 $>0$。

$f_{i,n}$ 只能做到 $O(n^3)$，因为要从每个位置开始 dp，一次 dp 时间复杂度为 $O(n^2)$。考虑设 $g_{i,j}$ 表示从 $\le i$ 的一个位置 $k$ 开始填到 $i$、当前前缀和为 $-j$、任意前前缀和 $\le 0$ 的概率 $\times $ $dp_{k,0}$。$g_{i,j}=g_{i-1,j+1}\times p_i+g_{i-1,j-1}\times q_i$，从 $g_{i-1,j-1}$ 转移需要满足 $j>0$。最后还要加上从 $i$ 出发的贡献，$g_{i,0}\leftarrow g_{i,0}+dp_{i,0}$。

$ans_i=\sum_{j=0}^ng_{i,j}$。

[代码](https://codeforces.com/contest/1810/submission/208718107)。



---

## 作者：tzc_wk (赞：1)

挺小清新的一道计数题。

首先先分析下这个“最大前缀和”，按照最朴素的思路就是扫一遍每个前缀，然后记录一下当前的 $sum$ 与前面的 $mx$，但是如果你一直陷在这个思路上你就似了，因为按照这个思路做，你 DP 状态里需要记录 $sum$ 和 $mx$ 两个维度，算上下标一维总共是 $n^3$，并且没有任何办法省掉当中任何一个循环，所以哪怕解决 $k=n$ 的问题都至少需要 $O(n^3)$。

考虑换一个角度处理这个“最大前缀和”，我们倒着 DP，$f_i$ 表示 $[i,n]$ 后缀的最大前缀和，显然 $f_i=\max(f_{i+1}+a_i,0)$。这样的好处一目了然：我们倒着 DP 的时候，只用记录一个维度也就是当前位置的 $f_i$，于是 $k=n$ 的情况就迎刃而解了：$dp_{i,j}$ 表示考虑到 $i$，目前 $f_i=j$ 的概率。

但是还有一个问题，就是我们对 $k=1,2,3,\cdots,n$ 求答案，相当于每次在末尾加一个数，这就导致我们 DP 状态不得不重新计算，而每次重新计算复杂度又变成了三方。这个 bug 的修补方法也比较 trivial，倒着 DP 行不通，我们就再改回正着 DP 呗。**我们将 DP 状态改为：设 $dp_{i,j}$ 表示当前在 $i$，在已知 $f_{i+1}=j$ 的情况，随机填 $[1,i]$ 的前缀，得分的期望值。**考虑这样的转移：

- 如果 $j\ne 0$：
  - $dp_{i,j}·a_{i+1}\to dp_{i+1,j-1}$
  - $dp_{i,j}·(1-a_{i+1})\to dp_{i+1,j+1}$
- 如果 $j=0$：
  - $dp_{i,j}·(1-a_{i+1})\to dp_{i+1,0}$
  - $dp_{i,j}·(1-a_{i+1})\to dp_{i+1,1}$

初值 $dp_{0,i}=h_i$，最终所求即为 $dp_{i,0}$。

代码非常短：

```cpp
const int MAXN=5000;
const int MOD=1e9+7;
int qpow(int x,int e){int ret=1;for(;e;e>>=1,x=1ll*x*x%MOD)if(e&1)ret=1ll*ret*x%MOD;return ret;}
int n,a[MAXN+5],dp[MAXN+5][MAXN+5];
void solve(){
	scanf("%d",&n);
	for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)dp[i][j]=0;
	for(int i=1,x,y;i<=n;i++)scanf("%d%d",&x,&y),a[i]=1ll*x*qpow(y,MOD-2)%MOD; 
	for(int i=0;i<=n;i++)scanf("%d",&dp[0][i]);
	for(int i=0;i<n;i++)for(int j=0;j<=n;j++){
		if(j){
			dp[i+1][j-1]=(dp[i+1][j-1]+1ll*a[i+1]*dp[i][j])%MOD;
			if(j<n)dp[i+1][j+1]=(dp[i+1][j+1]+1ll*(1-a[i+1]+MOD)*dp[i][j]%MOD);
		}else{
			dp[i+1][0]=(dp[i+1][0]+1ll*(1-a[i+1]+MOD)*dp[i][j])%MOD;
			dp[i+1][1]=(dp[i+1][1]+1ll*(1-a[i+1]+MOD)*dp[i][j])%MOD;
		}
	}
	for(int i=1;i<=n;i++)printf("%d%c",dp[i][0]," \n"[i==n]);
}
int main(){
	int qu;scanf("%d",&qu);while(qu--)solve();
	return 0;
}
```



---

## 作者：IdnadRev (赞：1)

我们考察一个序列最大前缀和的第一次出现位置，我们可以考虑先 dp 出 $g_i$ 表示长度为 $i$ 的最大前缀和为自己的序列的期望分数。

一个和为非负，最大前缀和不是自己的序列一定存在一个和为 $0$ 的后缀，于是我们可以枚举这样的后缀进行容斥，使用整体 dp 可以将容斥复杂度降为 $O(n^2)$。

现在我们要用一个上述序列对应到原来的序列，也就是拼接一个最大前缀和非正的后缀，类似地使用整体 dp 解决即可。

复杂度 $O(n^2)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5005,mod=1000000007;
int T,n;
int p[maxn],h[maxn],f[maxn],g[maxn],g1[2][maxn+maxn],g2[2][maxn+maxn],g3[2][maxn+maxn];
int ksm(int a,int b) {
	int res=1;
	while(b) {
		if(b&1)
			res=1ll*res*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return res;
}
inline void inc(int &x,int y) {
	x+=y;
	if(x>=mod)
		x-=mod;
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(int i=1,x,y; i<=n; i++)
			scanf("%d%d",&x,&y),p[i]=1ll*x*ksm(y,mod-2)%mod;
		for(int i=0; i<=n; i++)
			scanf("%d",&h[i]);
		int now=0;
		for(int i=0; i<=n+n; i++)
			g1[0][i]=g1[1][i]=g2[0][i]=g2[1][i]=g3[0][i]=g3[1][i]=0;
		g1[0][n]=1,g2[0][n]=g3[0][n]=h[0];
		for(int i=1; i<=n; i++) {
			now^=1;
			for(int j=0; j<=n+n; j++)
				g1[now][j]=g2[now][j]=g3[now][j]=0;
			for(int j=-i; j<=i; j++) {
				if(g1[now^1][n+j]) {
					inc(g1[now][n+j+1],1ll*g1[now^1][n+j]*p[i]%mod);
					inc(g1[now][n+j-1],1ll*g1[now^1][n+j]*(1+mod-p[i])%mod);
				}
				if(g2[now^1][n+j]) {
					inc(g2[now][n+j+1],1ll*g2[now^1][n+j]*p[i]%mod);
					inc(g2[now][n+j-1],1ll*g2[now^1][n+j]*(1+mod-p[i])%mod);
				}
				if(j>0)
					continue;
				if(g3[now^1][n+j]) {
					inc(g3[now][n+j+1],1ll*g3[now^1][n+j]*p[i]%mod);
					inc(g3[now][n+j-1],1ll*g3[now^1][n+j]*(1+mod-p[i])%mod);
				}
			}
			g[i]=f[i]=0;
			for(int j=0; j<=i; j++)
				inc(g[i],1ll*g1[now][n+j]*h[j]%mod);
			inc(g[i],mod-g2[now][n]);
			inc(g2[now][n],g[i]),inc(g3[now][n],g[i]);
			for(int j=-i; j<=0; j++)
				inc(f[i],g3[now][n+j]);
		}
		for(int i=1; i<=n; i++)
			printf("%d%c",f[i],i==n? '\n':' ');
	}
	return 0;
}
```

---

## 作者：_lbw_ (赞：0)

原问题即为：

$\forall k$，求：
$$\forall i\in [1,k],a_i\in\{-1,1\},\sum f_{\max_{t=1}^k \sum\limits_{i=1}^ta_i}\prod\limits_{i=1}^k v_{a_i}$$

我们发现 max 不好算，考虑将 $f_a$ 拆成 $\sum\limits_{k\ge a}f_k-f_{k+1}=\sum\limits_{k\ge a}g_k$。

做 dp，设 $f_{i,j}$ 表示前 $i$ 个数，当前前缀和为 $j$ 的答案。

但这样要先枚举 $k$，时间复杂度 $n^3$。

我们把 dp 数组翻转，将 $\leq j$ 转化为 $\ge 0$，这样所有 $k$ 的限制就变得相同。

最后依据 $f$ 的转移是线性变换，将所有 $f$ 的初值叠加在一起做一遍 dp 即可。



---

