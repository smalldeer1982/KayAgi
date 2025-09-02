# [ABC234G] Divide a Sequence

## 题目描述

给定一个长度为 $N$ 的数列 $A$。

将 $A$ 切分为若干个非空、**连续的**子序列 $B_1,B_2,\ldots,B_k$ 的方法共有 $2^{N-1}$ 种。对于每一种切分方式，计算如下的值，并将所有切分方式下的结果求和后对 $998244353$ 取模输出：

- $\prod_{i=1}^{k}\ (\max(B_i)-\min(B_i))$

这里，对于某个子序列 $B_i=(B_{i,1},B_{i,2},\ldots,B_{i,j})$，$\max(B_i)$ 表示 $B_i$ 中元素的最大值，$\min(B_i)$ 表示 $B_i$ 中元素的最小值。

## 说明/提示

### 数据范围

- $1\leq N\leq 3\times 10^5$
- $1\leq A_i\leq 10^9$
- 输入均为整数

### 样例解释 1

将 $A=(1,2,3)$ 切分为非空连续子序列的方法共有 $4$ 种：

- $(1)$ 和 $(2)$ 和 $(3)$
- $(1)$ 和 $(2,3)$
- $(1,2)$ 和 $(3)$
- $(1,2,3)$

对于每种切分方式，$\prod_{i=1}^{k}\ (\max(B_i)-\min(B_i))$ 分别为 $0$、$0$、$0$、$2$，因此总和为 $2$，输出 $2$。

### 样例解释 3

请注意，输出时需要对 $998244353$ 取模。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
4
1 10 1 10```

### 输出

```
90```

## 样例 #3

### 输入

```
10
699498050 759726383 769395239 707559733 72435093 537050110 880264078 699299140 418322627 134917794```

### 输出

```
877646588```

# 题解

## 作者：OIer_Eternity (赞：16)

[更好的阅读体验 - My Blog](https://blog.csdn.net/OIer_Cosmos/article/details/139956926)

# 题目来源

- [ABC234G](https://atcoder.jp/contests/abc234/tasks/abc234_g)

- [洛谷](https://www.luogu.com.cn/problem/AT_abc234_g)

# Description

给定长度为 $n$ 的序列 $\{a_n\}$。定义一种将 $\{a_n\}$ 划分为若干段的方案的价值为每段的最大值减去最小值的差的乘积。求所有划分方案的价值的总和并对 $998244353$ 取模。

- $1\le n\le3\times10^5,1\le a_i\le10^9$。

# Solution

由于要求所有划分方案的总和，并且难以存储划分的具体方案，因此我们可以通过动态规划来避免对具体方案进行讨论。

同时，我们可以将求乘积的和转化为将之前求出的和乘上同一个数。

具体而言，若设 $f_i$ 表示 $a_{1\cdots i}$ 的划分方案价值之和，则：

$$f_i=\sum_{j=1}^{i-1}\Bigg(f_j\times\Big(\max_{k=j+1}^{i}\{a_k\}-\min_{k=j+1}^i\{a_k\}\Big)\Bigg)$$

但这么做效率显然不优，而我们又可以将 $\max$ 和 $\min$ 分为两个独立的问题进行处理，于是我们应考虑分别计算 $\text{Maxsum}_i=\sum\limits_{j=1}^{i-1}\Big(f_j\times\max\limits_{k=j+1}^{i}\{a_k\}\Big)$ 以及 $\text{Minsum}_i=\sum\limits_{j=1}^{i-1}\Big(f_j\times\min\limits_{k=j+1}^{i}\{a_k\}\Big)$，则 $f_i=\text{Maxsum}_i-\text{Minsum}_i$。

由于 $\max$ 和 $\min$ 的计算类似，接下来以 $\max$ 的相关计算为例。

可以观察到，若将 $i$ 从 $1$ 枚举到 $n$，每次 $f_j\times\max\limits_{k=j+1}^{i}\{a_k\}$ 的变化是有限的。即 $\max\limits_{k=j+1}^{i}\{a_k\}$ 只有一段会存在变化，而这一段一定是一个区间 $[x,i)$，其中 $x=\max\limits_{t<i,a_t>a_i}t$，可结合下图理解（只有黑色矩形所在的下标可能成为最大值，且其是最大值的区间在其前一个黑色矩形所在下标到它前一个下标之间，如红色区间所示）。

![](https://cdn.luogu.com.cn/upload/image_hosting/5jmvwtmr.png)

那么我们可以看出来这需要运用到单调栈，栈中储存的是黑色矩形所在下标，用于求出图片上面定义的 $x$ 的值。而在同一个红色区间内，最大值不变，只需对 $f_i$ 进行求和。因此，若设 $\text{fsum}$ 是 $f$ 的前缀和函数，我们可以得到 $\text{Maxsum}_i=\text{Maxsum}_x+(\text{fsum}_{i-1}-\text{fsum}_{x-1})\times a_i$，那么 $\max$ 就可以在 $O(n)$ 求出，$\min$ 同理，单调栈的具体过程可参考代码。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int p=998244353;
int n,a[300005],Max[300005],top,Maxsum[300005],Min[300005],top2,Minsum[300005],f[300005],fsum[300005];
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	f[0]=fsum[0]=1;
	for (int i=1;i<=n;i++){
		while (top&&a[i]>=a[Max[top]]) top--;
		while (top2&&a[i]<=a[Min[top2]]) top2--;
		if (top) Maxsum[i]=(Maxsum[Max[top]]+1ll*(fsum[i-1]-fsum[Max[top]-1]+p)%p*a[i]%p)%p;
		else Maxsum[i]=1ll*fsum[i-1]*a[i]%p;
		if (top2) Minsum[i]=(Minsum[Min[top2]]+1ll*(fsum[i-1]-fsum[Min[top2]-1]+p)%p*a[i]%p)%p;
		else Minsum[i]=1ll*fsum[i-1]*a[i]%p;
		f[i]=(Maxsum[i]-Minsum[i]+p)%p,fsum[i]=(fsum[i-1]+f[i])%p;
		Max[++top]=i,Min[++top2]=i;
	}
	printf("%d\n",f[n]);
	return 0;
}
```

---

## 作者：As_Snow (赞：9)

[可能更好的阅读体验](https://www.cnblogs.com/As-Snow/articles/17742330.html)

## Solution
$f_i$ 表示前 $i$ 个分成若干段的价值之和。

易得状态转移方程为 $f_i=\sum_{j=1}^{i-1} f_j\times( \max\limits_{k=j+1}^{i}{a_k}-\min\limits_{k=j+1}^{i}{a_k} )$。

考虑拆成两个子问题，求 $\max\limits_{k=j+1}^{i}{a_k}$ 和 $\min\limits_{k=j+1}^{i}{a_k}$。其实就是求以 $i$ 为右端点的区间最大值之和与最小值之和。 用单调栈求即可。

由于在出栈过程中计算贡献比较麻烦，这里记录一下 $\max$ 和 $\min$ 的贡献。

时间复杂度 $\mathcal O(n)$。

----
[**Code**](https://atcoder.jp/contests/abc234/submissions/46206702)

---

## 作者：WaterSun (赞：5)

# 思路

定义 $dp_i$ 表示将前 $i$ 个分为若干段的价值总和。容易得到状态转移方程：

$$
dp_i = \sum_{j = 1}^{i - 1}{dp_j \times (\max_{k = j + 1}^{i}\{a_k\} - \min_{k = j + 1}^{i}\{a_k\})}
$$

于是考虑将其拆成 $\max_{k = j + 1}^{i}\{a_k\}$ 与 $\min_{k = j + 1}^{i}\{a_k\}$ 两个子问题。

在这里我们先讨论 $\max_{k = j + 1}^{i}\{a_k\}$ 这一子问题。

令 $x$ 表示在 $i$ 左边第一个大于 $a_i$ 的位置。那么，一定有 $\max_{k = x + 1}^{i}\{a_k\} = a_i$；$\max_{k = 1}^{x}\{a_k\} > a_i$。

所以，$a_i$ 能对答案产生贡献当且仅当 $j > x$。$x$ 是很好求的，直接用单调栈维护即可。

那么我们现在的问题就变为了如何求 $j \leq x$ 所能产生的贡献。

考虑用一个数组 $mx_i$ 表示 $\sum_{j = 1}^{i - 1}{dp_j \times \max_{k = j + 1}^{i}\{a_k\}}$。

那么显然有：

$$
mx_i = mx_x + (\sum_{k = x}^{i - 1}dp_k) \times a_i
$$

然后用前缀和优化一下即可做到 $\Theta(n)$ 时间复杂度解决。

对于 $\min_{k = j + 1}^{i}\{a_k\}$ 的子问题同理可用一个 $mn$ 数组解决。

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 3e5 + 10,mod = 998244353;
int n;
int arr[N];
int tp1,st1[N];
int tp2,st2[N];
int Max[N],Min[N],dp[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int Add(int a,int b){
	return (a + b) % mod;
}

inline int Sub(int a,int b){
	return ((a - b) % mod + mod) % mod;
}

inline int Mul(int a,int b){
	return a * b % mod;
}

signed main(){
	dp[0] = 1;
	n = read();
	for (re int i = 1;i <= n;i++) arr[i] = read();
	for (re int i = 1;i <= n;i++){
		while (tp1 && arr[st1[tp1]] <= arr[i]) tp1--;
		while (tp2 && arr[st2[tp2]] >= arr[i]) tp2--;
		if (tp1) Max[i] = Add(Max[st1[tp1]],Mul(Sub(dp[i - 1],dp[st1[tp1] - 1]),arr[i]));
		else Max[i] = Mul(dp[i - 1],arr[i]);//当 tp1 和 tp2 为 0 时需要特殊处理，避免越界 
		if (tp2) Min[i] = Add(Min[st2[tp2]],Mul(Sub(dp[i - 1],dp[st2[tp2] - 1]),arr[i]));
		else Min[i] = Mul(dp[i - 1],arr[i]);
		dp[i] = Add(dp[i - 1],Sub(Max[i],Min[i]));
		st1[++tp1] = st2[++tp2] = i;
	}
	printf("%lld",Sub(dp[n],dp[n - 1]));
	return 0;
}
```

---

## 作者：Union_Find (赞：2)

设 $f_i$ 表示前 $i$ 个数的价值和，所以就可以很容易推得 $f_i = \sum_{j = 1}^{i - 1}f_j \times (\max_{k=j+1}^{i} - \min_{k=j+1}^{i})$。

其实可以拆成两个问题，分别求 $\max_{k=j+1}^{i}$ 和 $\min_{k=j+1}^{i}$。而通过 [P5788 单调栈](https://www.luogu.com.cn/problem/P5788) 可得，我们能使用单调栈求出前面第一个比他大的或小的。拿 $\max_{k=j+1}^{i}$ 举例，我们直接先使用单调栈，然后分析一下。设前面第一个比他大的数下标是 $x$，问题中的 $\max_{k=x+1}^{i}$ 就是 $a_i$。所以以上式子就是 $\sum_{j = 1}^{i - 1}f_j \times a_i$。用以上方法，就可以轻松过掉这题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll n, a[300005], f[300005], v1[300005], v2[300005];
ll s1[300005], s2[300005], t1, t2, P = 998244353;
int main(){
	scanf ("%lld", &n);
	for (int i = 1; i <= n; i++) scanf ("%lld", &a[i]);
	f[0] = 1;
	for (int i = 1; i <= n; i++){
		while (t1 && a[s1[t1]]<= a[i]) t1--;
		while (t2 && a[s2[t2]] >= a[i]) t2--;
		if (t1) v1[i] = (v1[s1[t1]] + (f[i - 1] - f[s1[t1] - 1] + P) % P * a[i] % P) % P;
		else v1[i] = f[i - 1] * a[i] % P;
		if (t2) v2[i] = (v2[s2[t2]] + (f[i - 1] - f[s2[t2] - 1] + P) % P * a[i] % P) % P;
		else v2[i] = f[i - 1] * a[i] % P;
		f[i] = (f[i - 1] + v1[i] - v2[i] + P) % P;
		s1[++t1] = s2[++t2] = i;
	}
	printf("%lld", (f[n] - f[n - 1] + P) % P);
	return 0;
}

```

---

## 作者：Saint_ying_xtf (赞：2)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

转了一圈题解都不太清晰。来一篇详细的题解。

又是统计方案数，肯定是 Dp 啦！

设 $dp_i$ 为前 $i$ 个数分成若干段的价值。

那么转移方程就是 $dp_i = \sum_{j=1}^{i-1} dp_j \times (\max_{k=j+1}^i a_k-\min_{k=j+1}^i a_k)$。

也就是：$\sum_{j=1}^{i-1} dp_j \times \max_{k=j+1}^i a_k - \sum_{j=1}^{i-1}dp_j \times\min_{k=j+1}^i a_k$

此时的时间复杂度 $O(n^2)$ 显然过不了。也就是说，必须把 $ \sum_{j=1}^{i-1} dp_j \times \max_{k=j+1}^i a_k - \sum_{j=1}^{i-1}dp_j \times\min_{k=j+1}^i a_k$ 这个式子控制在常数级以内。才可以通过此题。

所以考虑如何处理 $\max_{k=j+1}^i a_k\sum_{j=1}^{i-1} dp_j \times \max_{k=j+1}^i a_k$ 和$ \sum_{j=1}^{i-1} dp_j \times \max_{k=j+1}^i a_k$。这两个子问题，很显然可以线段树，但是看了一圈题解区，好像没有那么~~愚蠢~~的做法。

引用教练灵魂画图：

![](https://cdn.luogu.com.cn/upload/image_hosting/yr9pmpt2.png)

此时遍历到 $i$。上一段的末尾是 $j$。

我们设 $x$ 表示的是 $i$ 左边的点第一个大于 $a_i$ 的位置，很显然我们可以得到两个式子：$\max_{k=x+1}^i a_k  = a_i$ 和 $\max_{k=1}^x a_k > a_i$。

先看取最大值：

那么我们可以对 $j$ 进行分类讨论处理。

- 如果 $j > x$，那么意味着 $j$ 到 $i$ 之前都是比 $a_i$ 都小。所以最大值也就是 $a_i$。而此时当且仅当 $j > x$，$a_i$ 才是答案的贡献，而 $x$ 是很好求的，单调栈维护即可。

- 如果 $j \le x$。问题就转换成如何求 $j \le x$ 所能产生的贡献。这种情况我么可以设一个数组 $f_i$ 表示 $\sum_{j=1}^{i-1} dp_j \times \max_{k=j+1}^i    a_k$。所以又有 $f_i = f_x + (\sum_{k=x}^{i-1}dp_k) \times a_i$。

对此，我们可以用单调栈维护 $(\sum_{k=x}^{i-1}dp_k)$ 的值，进而可以维护 $f_i = f_x + (\sum_{k=x}^{i-1}dp_k) \times a_i$ 的值。可以直接在单调栈中做加法和减法，所以不需要开一个数组，只需要变量即可。

注：最小值的方式也是类似的，只是单调栈的时候符号不一样，代码中最小值的变量是 $g$。

代码中的注释：

- （1）式为 $f_i = f_x + (\sum_{k=x}^{i-1}dp_k) \times a_i$。
- （2）式为 $g_i = g_x + (\sum_{k=x}^{i-1}dp_k) \times a_i$。
- （3）式为 $dp_i =  \sum_{j=1}^{i-1} dp_j \times \max_{k=j+1}^i a_k - \sum_{j=1}^{i-1}dp_j \times\min_{k=j+1}^i a_k$。也就是 $dp_i = f-g$。

[link](https://atcoder.jp/contests/abc234/submissions/49207240)。


```cpp
int n,a[N],f,g,dp[N],mx[N],mn[N];
stack<int> stmx,stmn;
void solve(){
	cin>>n;for(int i=1;i<=n;i++)cin>>a[i];
	dp[0]=mx[0]=mn[0]=1;//因为要做乘法
	for(int i=1;i<=n;i++){
		//对max部分处理
		mx[i]=dp[i-1];//长度为1的贡献肯定是ai
		while(!stmx.empty()&&a[stmx.top()]<a[i]){//找比ai小的数
			int x=stmx.top();stmx.pop();
			mx[i]=(mx[i]+mx[x])%mod;//修改累积的和。
			f-=mx[x]*a[x]%mod;f=(f%mod+mod)%mod;
		}stmx.push(i);
		f=((f+mx[i]*a[i])%mod+mod)%mod;//(1)式
		//对min部分处理	（跟max同理）
		mn[i]=dp[i-1];
		while(!stmn.empty()&&a[stmn.top()]>a[i]){//找比ai小的数
			int x=stmn.top();stmn.pop();
			mn[i]=(mn[i]+mn[x])%mod;
			g-=mn[x]*a[x]%mod;g=(g%mod+mod)%mod;
		}stmn.push(i);
		g=((g+mn[i]*a[i])%mod+mod)%mod;//(2)式
		//合算答案。
		dp[i]=((f-g)%mod+mod)%mod;//(3)式
	}cout<<dp[n];
}
```


---

## 作者：woshishabi11451444 (赞：1)

读完题，考虑设计状态，$dp_i$ 表示以 $i$ 结尾的序列的答案，转移如下：

$$dp_i = \sum _{j = 0} ^ {i - 1} \max _{j + 1 \le k \le i}{a_j} \times dp_j - \sum _{j = 0} ^ {i - 1} \min _{j + 1 \le k \le i}{a_j} \times dp_j$$ 

初始状态 $dp_0 = 1$。

不优化的时间复杂度：$O(n^2)$。

现在为我们需要一种 $O(1)$ 的方式快速求解 $\sum _{j = 0} ^ {i - 1} \max _{j + 1 \le k \le i}{a_j} \times dp_j$ 和 $\sum _{j = 0} ^ {i - 1} \min _{j + 1 \le k \le i}{a_j} \times dp_j$。

而单调栈刚好可以快速地求解最大值和最小值，现在再用乘法原理把 $\max _{j + 1 \le k \le i}{a_j} $ 和 $\min _{j + 1 \le k \le i}{a_j}$ 相同的同时处理。

然后前缀数组相同的最大值和最小值是连续的，所以使用前缀和。

所以每次维护新加进来的 $a_i$，并维护 $\sum _{j = 0} ^ {i - 1} \max _{j + 1 \le k \le i}{a_j} \times dp_j$ 和 $\sum _{j = 0} ^ {i - 1} \min _{j + 1 \le k \le i}{a_j} \times dp_j$ 的值。

---

## 作者：yukimianyan (赞：1)

## problem
长为 $n$ 的序列 $a$，将其划分成若干个连续的子串 $B=\{b_1,b_2,\cdots,b_k\}$

令 $f(B)=\prod_i(\max b_i-\min b_i)$，求 $\sum_B f(B)$，$n\leq 10^5$。

## solution
考虑 DP。令 $f_i$ 表示 $[1,i]$ 中所有 $B$ 的价值之和。

转移枚举 $j$ 表示上一次从哪里来，乘法分配律：

$$f_i=\sum_j f_j\left(\max([j+1,i])-\min([j+1,i])\right).$$

优化这个转移，以 $\max$ 为例，这类似于是后缀最大值和 $f$ 的相应位相乘之和。于是用单调栈维护后缀最大值，相同的后缀最大值压成一个区间，用乘法分配律，动态维护下一个 $f$ 值。

## code
```cpp
#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;
#define l first
#define r second
typedef long long LL;
const int P=998244353;
int n,a[300010];
LL f[300010],sum[300010];
template<int N,int D> struct crxakioi{
	int top;LL ans;
	pair<int,int> stk[N+10];
	crxakioi():top(0),ans(0){stk[0]={0,0};}
	void insert(int x){
		while(top&&a[stk[top].r]*D<=a[x]*D){
			ans-=(sum[stk[top].r-1]-sum[stk[top].l-2]+P)*a[stk[top].r]%P*(D+P)%P;
			ans=(ans%P+P)%P;
			top--;
		}
		top++,stk[top]={stk[top-1].r+1,x};
		ans+=(sum[stk[top].r-1]-sum[stk[top].l-2]+P)*a[stk[top].r]%P*(D+P)%P;
        //减一是因为原式 j+1
		ans%=P;
	}
};
crxakioi<300010,1> crx1;
crxakioi<300010,-1> crx2;
int main(){
//	#ifdef LOCAL
//	 	freopen("input.in","r",stdin);
//	#endif
	a[0]=1e9+7;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	f[0]=sum[0]=1;
	for(int i=1;i<=n;i++){
//		for(int j=0;j<i;j++){
//			f[i]=(f[i]+f[j]*(t1.query(j+1,i)+t2.query(j+1,i))%P);
//		}
		crx1.insert(i),crx2.insert(i);
		sum[i]=(sum[i-1]+(f[i]=(crx1.ans+crx2.ans)%P))%P;
	}
	printf("%lld\n",f[n]);
	return 0;
}

```


---

## 作者：wangzeqin2008 (赞：0)

# 题面

给长度为 $n$ 的序列 $a_{1\sim n}$。         

定义将 $a_{1\sim n}$ 划分为若干段的权值为：每一段的最大值减最小值的差的乘积。     

求所有划分方案的权值和。
  
$n\le 3\times 10^5$
  
# solution

计数类型一眼 dp。    
序列上 dp，常见套路是设 $f_i$ 表示处理到第 $i$ 位。    

设 $f_i$ 表示前 $i$ 个数的每种划分方案的权值和。 

如果 $1\sim i$ 作为一段，这种情况下权值为 $\max\limits_{k=1}^ia_k-\min\limits_{k=1}^ia_k$。    
如果不是整个作为一段，那么枚举上一个段的结尾 $j$，这种情况下的权值为 $f_j\times (\max\limits_{k=j+1}^ia_k-\min\limits_{k=j+1}^ia_k)$。

综合起来，有：

$$f_i=(\max\limits_{k=1}^ia_k-\min\limits_{k=1}^ia_k)+\sum\limits_{j=1}^{i-1}f_j\times (\max\limits_{k=j+1}^ia_k-\min\limits_{k=j+1}^ia_k)$$

瓶颈在于 $\sum\limits_{j=1}^{i-1}f_j\times (\max\limits_{k=j+1}^ia_k-\min\limits_{k=j+1}^ia_k)$。

$$\begin{aligned} &\sum\limits_{j=1}^{i-1}f_j\times (\max\limits_{k=j+1}^ia_k-\min\limits_{k=j+1}^ia_k)\\=&\sum\limits_{j=1}^{i-1}f_j\times \max\limits_{k=j+1}^ia_k-\sum\limits_{j=1}^{i-1}f_j\times \min\limits_{k=j+1}^ia_k \end{aligned}$$

这两个是同质问题。    
这里分析 $\sum\limits_{j=1}^{i-1}f_j\times \max\limits_{k=j+1}^ia_k$ 为例。

想着用数据结构实时维护这个值。    

这种 $f_j$ 不变，乘上一个变系数，可以用线段树实现。

$tr_i$ 维护两个东西，$sumf$ 和 $sumv$，分别表示区间 $f$ 的和，区间 $f\times \max a$ 的和。

每次遇到一个 $i$，需要考虑把那些 $\max a$ 改变的位置的 $tr_i$ 修改。    
即，要找出新产生的以 $a_i$ 为 $\max a$ 的区间。    
修改的时候，由于这个区间的 $\max$ 相同（都是 $a_i$），所以 $sumv=sumf\times a_i$。    
懒标记就维护这个系数就行。

这题就结束了。

线段树具体细节见代码。

# code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef long long ll;
typedef pair<int,int> PII;

int read() {
	int n=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9') {
		n=(n<<1)+(n<<3)+ch-'0';
		ch=getchar();
	}
	return f==1?n:-n;
}

void write(int x) {
	if(x<0) {
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar((x%10)+'0');
}

//========================================================//

const int N=3e5+7,K=20;
const ll MOD=998244353;

int n;
ll a[N];
ll f[N];

//========================================================//

struct Segment_Tree{
	
	struct Tr{
		ll sumf,sumv;
		ll lazy;
	}tr[N<<2];
	
	void pushup(int u) {
		Tr &f=tr[u],&ls=tr[u<<1],&rs=tr[u<<1|1];
		f.sumf=(ls.sumf+rs.sumf)%MOD;
		f.sumv=(ls.sumv+rs.sumv)%MOD;
	}
	
	void pushdown(int u) {
		Tr &f=tr[u],&ls=tr[u<<1],&rs=tr[u<<1|1];
		if(f.lazy) {
			ls.sumv=ls.sumf*f.lazy%MOD;
			rs.sumv=rs.sumf*f.lazy%MOD;
			ls.lazy=f.lazy; rs.lazy=f.lazy;
			f.lazy=0;
		}
	}
	
	void build(int u,int l,int r) {
		tr[u].sumf=tr[u].sumv=0;
		tr[u].lazy=0;
		if(l==r) return;
		int mid=(l+r)>>1;
		build(u<<1,l,mid); build(u<<1|1,mid+1,r);
	}
	
	void set(int u,int l,int r,int k,ll v) {
		if(l==r) {
			tr[u].sumf=v;
			if(tr[u].lazy) tr[u].sumv=v*tr[u].lazy%MOD;
			else tr[u].sumv=v;
			return;
		}
		pushdown(u);
		int mid=(l+r)>>1;
		if(k<=mid) set(u<<1,l,mid,k,v);
		else set(u<<1|1,mid+1,r,k,v);
		pushup(u);
	}
	
	void modify(int u,int l,int r,int ql,int qr,ll v) {
		if(ql<=l && qr>=r) {
			tr[u].lazy=v;
			tr[u].sumv=tr[u].sumf*v%MOD;
			return;
		}
		pushdown(u);
		int mid=(l+r)>>1;
		if(ql<=mid) modify(u<<1,l,mid,ql,qr,v);
		if(qr>mid) modify(u<<1|1,mid+1,r,ql,qr,v);
		pushup(u);
	}
	
	ll query(int u,int l,int r,int ql,int qr) {
		if(ql<=l && qr>=r) {
			return tr[u].sumv;
		}
		pushdown(u);
		int mid=(l+r)>>1;
		if(qr<=mid) return query(u<<1,l,mid,ql,qr);
		if(ql>mid) return query(u<<1|1,mid+1,r,ql,qr);
		return (
			query(u<<1,l,mid,ql,qr)+
			query(u<<1|1,mid+1,r,ql,qr)
		)%MOD;
	}
	
}tr1,tr2;

//========================================================//

int q1[N],h1,t1;
int q2[N],h2,t2;

//========================================================//

void input() {
	n=read();
	for(int i=1;i<=n;i++) 
		a[i]=read();
}

void work() {
	tr1.build(1,1,n);
	tr2.build(1,1,n);
	h1=0,t1=-1;
	h2=0,t2=-1;
	for(int i=1;i<=n;i++) {
		while(h1<=t1 && a[q1[t1]]<a[i]) t1--;
		if(h1<=t1) {
			if(q1[t1]<=i-1) tr1.modify(1,1,n,q1[t1],i-1,a[i]);
		}else{
			if(1<=i-1) tr1.modify(1,1,n,1,i-1,a[i]);
		}
		q1[++t1]=i;
		while(h2<=t2 && a[q2[t2]]>a[i]) t2--;
		if(h2<=t2) {
			if(q2[t2]<=i-1) tr2.modify(1,1,n,q2[t2],i-1,a[i]);
		}else{
			if(1<=i-1) tr2.modify(1,1,n,1,i-1,a[i]);
		}
		q2[++t2]=i;
		f[i]=(a[q1[h1]]-a[q2[h2]]+MOD)%MOD;
		if(1<=i-1) 
			f[i]=(f[i]+tr1.query(1,1,n,1,i-1)-tr2.query(1,1,n,1,i-1)+MOD)%MOD;
		tr1.set(1,1,n,i,f[i]);
		tr2.set(1,1,n,i,f[i]);
	}
	write(f[n]);
}

int main() {
	input();
	work();
	return 0;
}

```

---

## 作者：P7GAB (赞：0)

### 分析

题意十分简单，不难推出式子：

$ f_i = \sum_{j=1}^{i-1} f_j \times (\max_{k=j+1}^i a_k - \min_{k=j+1}^i a_k) $

但我们考虑这个 $O(n^2)$ 的东西显然是冲不过去的，所以必须优化转移。

式子后面两块都是极值，这启发我们用单调栈解决。

由于 $\max_{k=j+1}^i$ 与 $\min_{k=j+1}^i$ 是类似的，所以仅以前者为例，我们不妨设 $x$ 为前面第一个比当前大的数的下标，那么可得如下式子:

 $f_i = f_x + a_i \times \sum_{k=x}^{i-1} dp_k$

最小值同理，然后再用前缀和优化一下即可。

#### code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=3e5+10;
const int mod=998244353;
int n,a[maxn];
int s[maxn],f[maxn],g[maxn];
int stk1[maxn],stk2[maxn],top1,top2;
signed main() {
	cin>>n;
	for(int i=1; i<=n; i++)
		cin>>a[i];
	s[0]=1;//希望你没有因为忘记它而在【数据删除】中怒挂100pts 
	for(int i=1; i<=n; i++) {
		while (top1>0 && a[stk1[top1]]<=a[i]) top1--;
		while (top2>0 && a[stk2[top2]]>=a[i]) top2--;
		if (top1) f[i]=(f[stk1[top1]]+(s[i-1]-s[stk1[top1]-1]+mod)%mod*a[i]%mod)%mod;
		else f[i]=s[i-1]*a[i]%mod;
		if (top2) g[i]=(g[stk2[top2]]+(s[i-1]-s[stk2[top2]-1]+mod)%mod*a[i]%mod)%mod;
		else g[i]=s[i-1]*a[i]%mod;
		s[i]=(s[i-1]+f[i]-g[i]+mod)%mod;
		stk1[++top1]=i,stk2[++top2]=i;
	}
	cout<<(s[n]-s[n-1]+mod)%mod<<'\n';
	return 0;
}
```

---

## 作者：KazamaRuri (赞：0)

[题面](https://www.luogu.com.cn/problem/AT_abc234_g).

题意简明,不再赘述.

## 分析

一眼可以得到朴素 dp 方程:
$$$
dp_i=\sum_{j<i} dp_{j} (\max[j+1:i]-\min[j+1:i])
$$$
后面括号内非常难维护,考虑拆开,这样会分别得到两个极值状物,记
$$$
f_{i}=\sum_{j<i} dp_{j}\max\ ,\ g_{i}=\sum_{j<i} dp_j\min \\
dp_{i}=f_{i}-g_{i} \\
$$$
考虑如何转移 $f,g$,下文仅讨论 $f$ 的转移,$g$ 的转移类似.

根据极值的单调性,转移时我们重点在求 $\max = a_i$ 的区间.设 $a_j$ 为$i$ 左边第一个比 $a_i$ 大的数,可以得到如下转移方程:
$$$
f_i=f_j + a_i \cdot \sum_{k=j}^{i-1} dp_k
$$$
$j$ 可以单调栈线性求出,$\sum dp_k$ 可以用前缀和做到线性,这样我们可以在线性时间内转移 $f,g$.

## 代码

时空复杂度均为 $O(n)$.


```cpp
#include <bits/stdc++.h>
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
using namespace std;
using ll =long long;
const int N=3e5+5,mod=998244353;
int n,st[N],top,t0[N],t1[N]; ll a[N],f[N],g[N],s[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",a+i);
	for(int i=n;i;i--){
		for(;top&&a[st[top]]<a[i];t0[st[top--]]=i); st[++top]=i;
	} for(;top;t0[st[top--]]=0);
	for(int i=n;i;i--){
		for(;top&&a[st[top]]>a[i];t1[st[top--]]=i); st[++top]=i;
	} for(;top;t1[st[top--]]=0);
	s[0]=1;
	for(int i=1;i<=n;i++)
		f[i]=(f[t0[i]]+a[i]*(s[i-1]-s[t0[i]?t0[i]-1:n+1]+mod)%mod)%mod,
		g[i]=(g[t1[i]]+a[i]*(s[i-1]-s[t1[i]?t1[i]-1:n+1]+mod)%mod)%mod,
		s[i]=(s[i-1]+(f[i]-g[i]+mod)%mod)%mod;
	return printf("%lld\n",(f[n]-g[n]+mod)%mod)&0;
}
```

---

## 作者：AlicX (赞：0)

## Solution 

首先，这是由经典的序列分段变形而来的问题。所以可以很轻松地想出 $O(n^2)$ 的暴力：$f_i=\sum\limits_{j=1}^{i-1}f_j \times (\max\limits_{j \leq k \leq i-1} a_k-\min\limits_{j \leq k \leq i-1} a_k)$，用前缀维护即可。

将原式化简、打表或者稍加思考都可发现对于一个值 $a_i$，假设右端点为 $i$，以它为最大值的区间为 $j \sim k$，条件是 $a_j>a_i$，然后就顺水推舟地想到用单调维护区间最大值，那么假设右端点为 $i$，他作为最大值的贡献即为 $f_i=a_i \times (s_{i-1}-s_{j})$，$s$ 为前缀和数组。如果没有比 $a_i$ 大的数，$f_i=s_{i-1} \times a_i$。求最小值同理。


---

