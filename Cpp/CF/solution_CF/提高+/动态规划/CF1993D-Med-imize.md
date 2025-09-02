# Med-imize

## 题目描述

Given two positive integers $ n $ and $ k $ , and another array $ a $ of $ n $ integers.

In one operation, you can select any subarray of size $ k $ of $ a $ , then remove it from the array without changing the order of other elements. More formally, let $ (l, r) $ be an operation on subarray $ a_l, a_{l+1}, \ldots, a_r $ such that $ r-l+1=k $ , then performing this operation means replacing $ a $ with $ [a_1, \ldots, a_{l-1}, a_{r+1}, \ldots, a_n] $ .

For example, if $ a=[1,2,3,4,5] $ and we perform operation $ (3,5) $ on this array, it will become $ a=[1,2] $ . Moreover, operation $ (2, 4) $ results in $ a=[1,5] $ , and operation $ (1,3) $ results in $ a=[4,5] $ .

You have to repeat the operation while the length of $ a $ is greater than $ k $ (which means $ |a| \gt k $ ). What is the largest possible median $ ^\dagger $ of all remaining elements of the array $ a $ after the process?

 $ ^\dagger $ The median of an array of length $ n $ is the element whose index is $ \left \lfloor (n+1)/2 \right \rfloor $ after we sort the elements in non-decreasing order. For example: $ median([2,1,5,4,3]) = 3 $ , $ median([5]) = 5 $ , and $ median([6,8,2,4]) = 4 $ .

## 说明/提示

In the first test case, you can select a subarray $ (l, r) $ which can be either $ (1, 3) $ or $ (2, 4) $ . Thus, two obtainable final arrays are $ [3] $ and $ [2] $ . The former one has the larger median ( $ 3 > 2 $ ) so the answer is $ 3 $ .

In the second test case, three obtainable final arrays are $ [6, 4] $ , $ [3, 4] $ , and $ [3, 2] $ . Their medians are $ 4 $ , $ 3 $ , and $ 2 $ respectively. The answer is $ 4 $ .

In the third test case, only one element is left in the final array and it can be any element of the initial array. The largest one among them is $ 9 $ , so the answer is $ 9 $ .

## 样例 #1

### 输入

```
5
4 3
3 9 9 2
5 3
3 2 5 6 4
7 1
5 9 2 6 5 4 6
8 2
7 1 2 6 8 3 4 5
4 5
3 4 5 6```

### 输出

```
3
4
9
6
4```

# 题解

## 作者：Register_int (赞：18)

一眼二分答案，将序列中 $<x$ 的数设为 $-1$，$\ge x$ 的数设为 $1$。问题转化为：从序列中删掉 $\lfloor\frac{n-1}m\rfloor$ 个长度为 $m$ 的连续段，最大化剩下的值之和。

有个显然的 $dp_{i,j}$ 表示前 $i$ 个数删了 $j$ 段的最优解，但是状态数 $O(n^2)$ 无法接受。但发现 $j$ 必须要 $\ge\lfloor\frac{i-1}m\rfloor$，同时它又 $\le\lfloor\frac im\rfloor$。也就是说，对于每个 $i$，有用的 $j$ 只有两个。

修改状态 $dp_{i,j=0/1}$ 表示前 $i$ 格分了 $\lfloor\frac{i-1}m\rfloor+j$ 段的最优解，记忆化搜索转移，时间复杂度 $O(n\log V)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;

int T, n, m, a[MAXN], b[MAXN], dp[MAXN][2]; bool vis[MAXN][2];

int dfs(int x, int k) {
	if (x < 0 || k < 0 || m * k > x) return -1e9;
	if (!x) return 0; int t = k - (x - 1) / m;
	if (vis[x][t]) return dp[x][t]; vis[x][t] = 1;
	return dp[x][t] = max(dfs(x - 1, k) + b[x], dfs(x - m, k - 1));
}

inline 
bool check(int x) {
	for (int i = 1; i <= n; i++) b[i] = (a[i] >= x ? 1 : -1);
	for (int i = 1; i <= n; i++) vis[i][0] = vis[i][1] = 0;
	return dfs(n, (n - 1) / m) > 0;
}

int l, r, mid;

int main() {
	for (scanf("%d", &T); T--;) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (l = 1, r = 1e9; l < r; check(mid = l + r + 1 >> 1) ? l = mid : r = mid - 1);
		printf("%d\n", l);
	}
}
```

---

## 作者：Alex_Wei (赞：14)

### [CF1993D Med-imize](https://www.luogu.com.cn/problem/CF1993D)

第一个被留下的位置之前删去的长度是 $k$ 的倍数，所以第一个被留下的位置的下标模 $k$ 余 $1$。类似可知第 $i$ 个被留下的位置的下标模 $k$ 和 $i$ 同余。

已知总共会留下不超过 $r = ((n - 1) \bmod k) + 1$，二分答案 $mid$，则总共要留下至少 $c$ 个不小于 $mid$ 的数，满足 $2c - 1 \geq \min(r, n)$。设 $f_i$ 表示保留 $i$ 个数时 $c$ 的最大值，对当前 $a_j$，设 $t = ((j - 1) \bmod k) + 1$，则 $f_t \gets \max(f_t, f_{t - 1} + [a_j\geq mid])$。检查是否有 $2f_r - 1\geq \min(n, r)$ 即可。

时间复杂度 $\mathcal{O}(n\log V)$。[代码](https://codeforces.com/contest/1993/submission/275027585)。

---

## 作者：FLY_lai (赞：6)

## 题意

有一个 $n$ 长度的序列，一次操作定义为删去序列中一个长度为 $k$ 的子段，然后让剩下的数按顺序拼合在一起。

现在给定 $n,k$ 和初始序列。让你重复进行操作，直到序列长度 $\le k$。问最终序列的中位数最大是多少。

## 题解

一般涉及到中位数的题，很多都可以尝试二分来解。这题也是一样。因为越大越好，越小越可行，也就是答案的可行性是单调的。

于是二分 $x$ 作为答案，问题转化为判断最终中位数是否可以 $\ge x$。

因为我们只关心 $\ge x,<x$ 的个数，不关心它们具体是多少，可以尝试最小化 $<x$ 的数的个数。

$dp[i]$ 表示前 $i$ 个数组成的序列，一直删到个数 $\le k$ 之后（**不允许删空**），余下 $<x$ 的数的个数最少是多少。

可以列出 DP 方程：如果删第 $i$ 个，$dp[i]=dp[i-k]$；否则 $dp[i]=dp[i-1]+[a_i<x]$。

所以 $dp[i]=\min(dp[i-k],dp[i-1]+[a_i<x])$

初值设定：$dp[1\sim k]$ 都作为初值，$dp[i]$ 设定为 $a_1\sim a_i$ 里 $<x$ 的数的个数。

每次判定做一次 $O(n)$ 的 DP，然后判断 $dp[n]$ 的大小。

就行了吗？如果这么写连样例都过不去。

研究发现，这是因为如果 $dp[i]$ 选择不删 $i$，那 $a_1\sim a_{i-1}$ 其实删空了也没问题。

于是引入 $dp2[i]$，定义就是 $dp[i]$ 的允许删空版本。（当然不允许把长度删成负数）

$dp[i]=\min(dp2[i-k],dp2[i-1]+[a_i<x])$。

初值：$dp2$ 是允许删空的，所以初值是 $dp2[0\sim k-1]$，也是前 $i$ 个 $<x$ 的数的个数。

先递推完 $dp2$，然后 $dp$ 的转移方程改为 $dp[i]=\min(dp[i-k],dp2[i-1]+[a_i<x])$ 即可。

## Code

```
#include <bits/stdc++.h>

using namespace std;
const int N = 5e5 + 5;
typedef long long ll;

int n, k;
ll a[N];
int dp[N]; //dp[i]表示前i个至少有多少个<x的，要求非空 
int dp2[N]; //允许空 

int rem(int a, int b) {
	if (a % b == 0)
		return b;
	return a % b;
}

bool chk(int x) { //判断最终中位数>=x是否可行 
	for (int i = 0; i <= n; i++)
		dp[i] = 0;
	for (int i = 1; i <= k; i++)
		dp[i] = dp[i - 1] + (a[i] < x);
	for (int i = 1; i <= k - 1; i++)
		dp2[i] = dp2[i - 1] + (a[i] < x);
	for (int i = k; i <= n; i++) {
		dp2[i] = dp2[i - 1] + (a[i] < x);
		dp2[i] = min(dp2[i], dp2[i - k]);
	}
	for (int i = k + 1; i <= n; i++) {
		dp[i] = dp2[i - 1] + (a[i] < x);
		dp[i] = min(dp[i], dp[i - k]);
	}
	//dp[n]个<x的，rem(n,k)-dp[n]个>=x的 
	return (rem(n, k) + 1) / 2 > dp[n];
}
void slv() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	
	if (k >= n) {
		sort(a + 1, a + n + 1);
		cout << a[(n + 1) / 2] << endl;
		return ;
	}
	
	int l = 1, r = 1000000001;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (chk(mid))
			l = mid;
		else
			r = mid;
	}
	cout << l << endl;
}

int main() {
	int T;
	cin >> T;
	while (T--)
		slv();
	return 0;
}
```

---

## 作者：小木虫 (赞：6)

### Preface  
无内鬼，来点搞笑解法。  
### Problem  

给定两个正整数 $n$ 和 $k$ 以及一个由 $n$ 个整数组成的数组 $a$。

在一次操作中，可以选择 $a$ 的任意一个大小为 $k$ 的子数组，然后在不改变其他元素的顺序的情况下，将其从数组中删除。更正式地说，假设正整数对 $(l, r)$ 满足 $r-l+1=k$ ，那么执行此操作意味着用 $[a_1, \ldots, a_{l-1}, a_{r+1}, \ldots, a_n]$ 替换 $a$。

例如，如果 $a=[1,2,3,4,5]$，选择正整数对 $(3,5)$，它就会变成 $a=[1,2]$ 。此外，选择正整数对 $(3,5)$ 的结果是 $a=[1,5]$，选择正整数对 $(1,3)$ 的结果是 $a=[4,5]$。

当 $a$ 的长度大于 $k$ （即 $|a| \gt k$ ）时，你必须重复操作。处理后，数组 $a$ 中所有剩余元素的最大中位数 $^\dagger$ 是多少？

$^\dagger$ 长度为 $n$ 的数组的中位数是对元素进行非递减排序后排名为 $\left \lfloor \frac{n+1}{2}\right \rfloor$ 的元素。例如 $\text{median}([2,1,5,4,3]) = 3$，$\text{median}([5]) = 5$ 和 $\text{median}([6,8,2,4]) = 4$。

多组数据，$1 \le t \le 10^4$，$1 \le n, k \le 5 \cdot 10^5$，$1 \le a_i \le 10^9$，$\sum n  \le 5 \cdot 10^5$。
### Solution  
首先我们可以通过二分中位数的方式来将 $a$ 变为一个只有 $1,-1$ 两种元素的数组，最后留下的所有元素之和应大于 $0$ 才合法。  
然后你注意到分步操作是没有用的，题目限制等价于选择若干个不交的区间删除。  
那么现在的问题是如何求出最大的留下元素之和。  
注意到操作次数是恒定的，为 $\dfrac{n-1}{k}$ 次，但是我们肯定不能记录操作次数来 dp，那样太蠢了。  

经过观察后发现对于一个局面，设 $f(x)$ 为操作 $x$ 次之后的最大元素之和，则 $f(x)$ 是一个凸函数。  
那这个就非常 Amazing 啊！我们直接通过 wqs 二分来限制住操作次数就可以了，复杂度 $O(n\log^2 n)$。  

（CF 的 i3-8100 老爷机也太慢了，这都要跑 1900ms。）  

```cpp
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define int long long
#define mp make_pair
#define fir first
#define sec second
using namespace std;
int read() {
  int x = 0, w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') { 
    if (ch == '-') w = -1;     
    ch = getchar();            
  }
  while (ch >= '0' && ch <= '9') {  
    x = x * 10 + (ch - '0');  
    ch = getchar();
  }
  return x * w;
}
void write(int x) {
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) putchar(sta[--top] + 48);
}
const int N=5e5+10;
int T,n,k,a[N],b[N],c[N],sum[N];
pair <int,int> f[N];
pair <int,int> calc(int x){
	f[0]=mp(0,0);
	for(int i=1;i<=n;i++)f[i]=mp(-1e18,0);
	for(int i=0;i<n;i++){
		f[i+1]=max(f[i+1],mp(f[i].fir+b[i+1],f[i].sec));
		if(i+k<=n){
			f[i+k]=max(f[i+k],mp(f[i].fir+x,f[i].sec+1));
		}
	}return f[n];
}
bool check(int x){
	for(int i=1;i<=n;i++)
		if(a[i]>=x)b[i]=1;
		else b[i]=-1;
	int l=-k,r=k;
	while(l<r){
		int mid=(l+r+1)>>1;
		if(calc(mid).sec>(n-1)/k)r=mid-1;
		else l=mid;
	}
	pair <int,int> ans=calc(l);
	return ans.fir-l*ans.sec>0;
}
int num[N];
void solve(){
	n=read();k=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),num[i]=a[i];
	int l=1,r=n;
	sort(num+1,num+1+n);
	while(l<r){
		int mid=(l+r+1)>>1;
		if(check(num[mid]))l=mid;
		else r=mid-1;
	}
	write(num[l]);putchar('\n');
}
signed main(){
	//ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	T=read();
	while(T--)solve();
	//cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
	return 0;
}
```

---

## 作者：SamHJD (赞：4)

> 给出一个长为 $n$ 的序列 $a$，每次操作可以一个长为 $k$ 的子段删除，并将剩余部分拼接。当 $n\le k$ 时停止。问最终序列的中位数最大可能是多少。

首先，最终序列的长度 $m=(|a|-1) \bmod k+1$，设这 $m$ 个数在原序列中的位置为 $p_1\dots p_m$，有结论：$p_i\equiv i\pmod k$。

考虑证明，对于 $p_i$，$[1,p_i]$ 中有 $p_i-i$ 个位置被删除，且一定为 $k$ 的倍数，有 $i$ 个位置没有被删除，显然 $p_i\equiv i\pmod k$ 成立。

二分中位数 $x$，将 $a$ 中小于 $x$ 的数设为 $-1$，其余的数设为 $1$，记 $f_i$ 为 $[1,i]$ 的答案，根据上述性质，模 $k$ 下等于 $1$ 的位置一定作为最终序列的第一个位置或被删除，可列出转移：
$$
f_i=
\begin{cases}
\max\{f_{i-k},a_i\}\qquad\qquad i\equiv 1\pmod k\\
\max\{f_{i-1}+a_i,f_{i-k}\}\quad \text{otherwise}
\end{cases}
$$

时间复杂度 $O(n\log V)$，其中 $V$ 为值域。

```cpp
#include "bits/stdc++.h"
#define rep(i,s,t) for(int i=s;i<=t;++i)
#define per(i,t,s) for(int i=t;i>=s;--i)
using namespace std;
template<typename T>
inline void read(T &x) {
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	x*=f;
}
const int N=5e5+10;
int T,n,k,a[N],tmp[N],f[N];
bool ck(int mid){
	rep(i,1,n) if(a[i]<mid) tmp[i]=-1;else tmp[i]=1;
	f[1]=tmp[1];
	rep(i,2,n){
		if((i-1)%k==0) f[i]=max(tmp[i],f[i-k]);
		else{
			f[i]=f[i-1]+tmp[i];
			if(i-k>1) f[i]=max(f[i],f[i-k]);
		}
	}
	return f[n]>0;
}
void solve(){
	read(n);read(k);
	int l=1,r=0;
	rep(i,1,n) read(a[i]),r=max(r,a[i]);
	while(l<=r){
		int mid=(l+r)>>1;
		if(ck(mid)) l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",r);
}
int main(){
	read(T);while(T--) solve();
	return 0;
}
```

---

## 作者：Engulf (赞：4)

很有趣的题。

先考虑 $k \le n$，即不用删除的情况，有没有不用排序求出中位数的方法？

注意本题的中位数定义不太一样，是排序后 $[a_1, a_2, \cdots, a_n]$ 中的 $a_{\left\lceil \frac{n}{2} \right\rceil}$。有个 trick，考虑 $x$ 能否成为数组的中位数，也就是 $a$ 中，$\ge x$ 的数的个数要大于 $<x$ 的数的个数。

定义数组 $b$，其中

$$b_i = \left\{\begin{matrix}
1 & a_i \ge x \\ -1 & a_i < x
\end{matrix}\right.$$

对 $b$ 求和，记 $s = \sum\limits_{i=1}^n b_i$。
- 若 $s > 0$，即 $\ge x$ 的数的个数要大于 $<x$ 的数的个数，那么数组的中位数是 $\ge x$ 的。这是因为 $s=1$ 时，中位数是 $x$，而 $s > 1$ 时，$\ge x$ 的数过多，中位数一定会变大。
- 若 $s \le 0$，中位数 $<x$。

就这样证明了中位数是单调的，直接二分即可求出 $a$ 的中位数，时间复杂度 $O(n \log V)$，其中 $V = \max\limits_{i=1}^{n}a_i - \min\limits_{i=1}^{n}a_i$。

现在来考虑 $k > n$，即需要删除的情况。
**从此处开始，为了求余的方便，数组下标从 $0$ 开始。**

记 $a'$ 是 $a$ 按题目要求删除后的数组，$|a'| = n \bmod k + [n \equiv 0(\bmod k)]$（不能删得啥都不剩），记 $m = |a'|$。

性质：设 $a'_0, a'_1, \cdots, a'_{m-1}$ 在原数组分别是 $a_{i_0}, a_{i_1}, \cdots, a_{i_{m-1}}$，那么 $\forall j \in [1, m], i_j \equiv j(\bmod k)$。

证明也很简单，删除 $a_l, a_{l+1},\cdots, a_{r}$ 相当于将 $a_{r + 1}, a_{r + 2}, \cdots a_n$ 下标全部减 $k$，这是不影响模 $k$ 的余数的，而且仍然连续。

为了让中位数尽量大，二分 check 的时候要尽量让 $s = \sum\limits_{i=0}^{m-1}b'_i$ 尽量大。如何让 $s$ 最大。

考虑动态规划，设 $f_i$ 是 $b$ 中前 $i$ 个数删除长度为 $k$ 的子段的最大值。

- 若 $i = 0$，$f_i = b_i$。
- 否则若 $i \equiv 0(\bmod k)$，可以把前面全删了从这里起一段，也可以删掉 $[i - k + 1, i]$ 这一段，所以此时 $f_i = \max(f_{i-k}, b_i)$。
- 否则，同样地，可以取 $i$，$f_i = f_{i-1} + b_i$，如果 $i > k$，也就是前面已经存在一个下标与 $i$ 模 $k$ 同余的了，可以删掉 $i$，此时取最大值即可。$f_i = \max({f_i, f_{i - k}})$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        int l = *min_element(a.begin(), a.end()), r = *max_element(a.begin(), a.end()), res = -1;
        while (l <= r) {
            int mid = l + r >> 1;
            if ([=]() {
                vector<int> b(n);
                for (int i = 0; i < n; i++)
                    b[i] = a[i] >= mid ? 1 : -1;
                vector<int> f(n);
                f[0] = b[0];
                for (int i = 1; i < n; i++)
                    if (i % k == 0) f[i] = max(b[i], f[i - k]);
                    else {
                        f[i] = f[i - 1] + b[i];
                        if (i - k > 0) f[i] = max(f[i], f[i - k]);
                    }
                return f[n - 1] > 0;
            }()) res = mid, l = mid + 1;
            else r = mid - 1;
        }

        cout << res << "\n";
    }
    return 0;
}
```

---

## 作者：zhm080507 (赞：2)

# [CF1993D Med-imize](https://codeforces.com/contest/1993/problem/D)

### 题目大意

将一个序列删除若干连续长度为 $k$ 的子串，使其长度小于等于 $k$，问操作结束后剩余序列中位数最大是多少。

### 算法分析

首先看到使中位数最大，因为可行性是单调的，容易想到二分答案，问题转化为判定一个答案是否可行。

经过思考后发现，不需要考虑其余数具体值是多少，只需要记录小于或大于 $mid$ 的个数就行。

首先想到令 $f_i$ 表示统计到 $i$ 时剩余的小于 $mid$ 的个数，转移为：$f_i=\min(f_{i-k},f_{i-1}+[a_i<mid])$。但发现这样转移在 $n \equiv 0 \pmod k$ 时，会直接选择删空。

所以考虑引入第二种状态 $g_i$ 表示统计到 $i$ 时**不能删空**的最小值，转移为：$g_i=\min(g_{i-k},f_{i-1}+[a_i<mid])$。

最后答案就是 $g_n$，复杂度 $O(n\log n)$。

想明白代码就很好写了，还有一些细节具体参照代码。

### [code](https://codeforces.com/contest/1993/submission/289778186)

```c++
#include<bits/stdc++.h>
using namespace std;

const int N=512345;
int T,n,k,a[N];
int f[N],g[N];

bool check(int x){
	int s=n%k;
	if(s==0) s=k;
	s=(s+1)/2;
	f[0]=0;
	for(int i=1;i<=n;i++){
		f[i]=f[i-1];
		if(a[i]<x) f[i]++;
		if(i>=k){
			f[i]=min(f[i],f[i-k]);
		}
		g[i]=f[i-1];
		if(a[i]<x) g[i]++;
		if(i>k){//注意这里的边界！！和f不一样 
			g[i]=min(g[i],g[i-k]);
		}
	}
	
	if(s>g[n]) return 1;
	else return 0;
}

void sol(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int l=0,r=1e9+10;
	while(l+1<r){
		int mid=(l+r)>>1;
		if(check(mid))
			l=mid;
		else r=mid;
	}
	cout<<l<<"\n";
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>T;
	while(T--){
		sol();
	}
	return 0;
}
```

---

## 作者：superl61 (赞：2)

[题目传送门](https://codeforces.com/contest/1993/problem/D) 

 [更好的阅读体验](https://www.cnblogs.com/superl61/p/18525524) 

二分套动态规划。

本题的中位数定义是 $a_{\lceil\frac{n}{2}\rceil}$，有个 trick，$x$ 可能成为中位数，当且仅当**比 $x$ 大的数多于比 $x$ 小的数**。

我们现在只需要关心每个数和 $x$ 的相对大小关系，我们给 $\ge x$ 的数赋权 $1$，$\lt x$ 的数赋权 $-1$。

容易发现 $x$ 越大，序列中 $-1$ 越多，总和越小，具有单调性。因此 **$x$ 具有可二分性**。

问题转化为：对于一个中位数 $x$ 得到的序列，能否通过删掉若干个长度为 $k$ 的子段，使剩下的序列总和 $sum \gt 0$。

即我们要考虑怎么删才能**最大化** $sum$。发现一段区间删不删，不是很好直接贪（跟每个数所处的位置有关系），考虑动态规划。

记 $f[i]$ 表示 $0 \sim i$，删到长度 $\le k$，总和最大值。（下标从 $0$ 开始，方便下文性质）

怎么判断分段呢？发现一个性质：若 $a[i]$ 被留下来了，最后下标一定是 $a[i \mod k]$。原因很好想，因为你只能 $k$ 个 $k$ 个删， $i$ 对于 $k$ 的余数肯定不变。

因此转移可分三类：
$$
f[i] =\begin{cases}f[i - 1] + b[i] \qquad & i \lt k \\\max(f[i], f[i - k]) \qquad & i \ge k \cap i\mod k \ne 0 \\\max(f[i - k], b[i]) \qquad & i \ge k \cap i\mod k = 0\end{cases}
$$
最后判断 $f[n] > 0$ 即可。时间复杂度 $O(nlogn)$。

---

## 作者：mango2011 (赞：2)

场切之。事实上，这个题目其实不怎么难。

显然，我们可以二分答案 $mid$，可以认为：

对于 $<mid$ 的 $a_i$，贡献都是 $0$；对于 $\ge mid$ 的 $a_i$，贡献都是 $1$，将 $a_i$ 的贡献记为 $b_i$。

可以观察到我们选择的区间可以都是相离的。我们考虑 $dp_{i,j}$ 表示前 $i$ 个数，取了 $j$ 段，那么 $dp_{i,j}=\max(dp_{i-1,j}+b_i,dp_{i-j,j-1})$。观察到对于每一个 $i$，它对应的 $j$ 是确定的，因此可以 $O(n)$ 实现转移。需要注意 $i\equiv1\pmod k$ 的情形，这种情况下需要特殊注意只留下 $i$ 的情况（前面的取光了）。

最后，我们只需要检查 $dp_{n}$ 是否 $>\lfloor\frac{len}{2}\rfloor$，其中 $len$ 表示最后应该留下的总长度。

于是，我们就在总复杂度 $O(n\log V)$ 的时间复杂度内解决了问题。

[评测记录](https://codeforces.com/contest/1993/submission/275321837)

---

## 作者：IKUN314 (赞：2)

## Problem

给定正整数序列 $\langle a_i\rangle_{i=1}^n$，一次操作定义为选择一个长度为 $k$ 的子段并将其删除并拼接两端元素。当 $|a|>k$ 时必须继续进行操作，求剩余元素的中位数$^†$最大为多少。 

$^†$中位数：序列 $a$ 的中位数为 $a$ 中第 $\left\lfloor\dfrac{|a|+1}{2}\right\rfloor$ 小的元素。与传统数学定义的不同在于若 $2\mid |a|$ 只取中间两数较小者而非均值。
## Solution

下称原序列以某种顺序或方式尽可能进行操作得到的最终序列为**剩余序列** $\langle a'\rangle_{i=1}^m$，其中「不小于 $x$ 的数的个数」与「小于 $x$ 的数的个数」的差值记为 $d_{a'}(x)$。

不难发现，当 $mid$ 增大时，**一个 *合法* 的剩余序列 $\mathbf{a'}$ 中** $d_{a'}(mid)$ 无论由何种删除方式得到都只减不增，因此 $\exists a',d_{a'}(mid)>0$ 就意味着存在 $\ge mid$ 的中位数答案，**反之则说明不存在**。因此答案具有单调性。

我们知道 
$$\exists a',d_{a'}(mid)>0\iff \max_{a'}\{d_{a'}(mid)\}>0.$$
那么有二分：$check(mid)=[\max_{a'}{\{d_{a'}(mid)\}}>0]$ 表示是否存在不小于 $mid$ 的答案，最终答案为 $\max\{mid\mid check(mid)=1\}$。

现在考虑如何 $check$。删除与决策有关，而且很显然具有最优子结构，因此考虑 DP。固定 $mid$，令 $f_i$ 表示原序列为前 $i$ 个元素时，所有合法的最终剩余序列中 $d(mid)$ 的最大值。则 $check(mid)=[f_n>0]$。

转移和边界呢？这实际上是在问：**什么样的剩余序列是 *合法* 的？** 倒过来思考，一个剩余序列合法当且仅当它能被扩充为原序列。注意到剩余序列中的元素下标 $i\equiv i\pmod k$（废话），而这个余数在删除长度恰好为 $k$ 的子段时完全不会改变。题目说明停止操作的条件是 $|a|\le k$，则可得 $m=(n-1)\bmod k+1$。于是如果第 $i$ 个剩余元素映射到原序列中的「原下标」$I_i$ 满足
$${\forall i\in[1,m=(n-1)\bmod k+1],I_i\equiv i^\pmod k}$$
则剩余序列一定能被扩充到长度为 $n$ 的原序列；而如果不满足，则这种剩余序列无论原序列怎么删都无法得到，因为总存在剩余序列中两个相邻元素（或首元素与 $a_0$，尾元素与 $a_{n+1}$）在原序列中的下标之差减一（这就是它们之间要删除的元素个数）不为 $k$ 的倍数。

由此得出，上式为剩余序列合法的充分必要条件。另外，该式有一种特殊情形：$I_{m}\equiv n$，待会会用到。

那么，边界就是 $\equiv 1$ 的点了$^{(*)}$，因为它们是剩余序列的开头。不过因为它们都能作为开头，所以其中一个点要与之前的 $\equiv 1$ 的点取 $\max$，这里用前缀最小值可优化。

$$\forall i\equiv1,f_i\gets \begin{cases}1,&\text{if }a_i\ge mid\\-1.&\text{otherwise}\end{cases}$$
$$\forall i\equiv 1\land i>1,f_i\overset{\max}{\gets}f_{i-k}$$

接下来考虑转移。为得到合法的剩余序列，对 $f_i$ 的转移需要考虑两种情况：
1. 不用 $a_i$ 作为剩余序列中下标 $\equiv i$ 的元素，这种转移合法当且仅当 $i>k$。因为该状态中原序列长度为 $i$，所以剩余序列末尾元素的原下标必须满足 $I_m\equiv i$，则不用 $a_i$ 也要用原序列中之前下标 $\equiv i$ 的元素代替。结合第二种情况的设置，涵盖这种情况所有可能性的状态只有 $f_{i-k}$。
2. 使 $a_i$ 作为剩余序列中下标 $\equiv i$ 的元素。由上文的讨论，此时若 $f_i$ 不是边界，则必须从满足「**剩余序列**长度 $\equiv i-1$」的状态转移过来。这种情况的所有决策可能性恰好涵盖在了 $f_{i-1}$ 中，因此选之作为子结构即可。

由此轻松得出状态转移方程：
$$f_i=\max\begin{cases}
\begin{cases}f_{i-k},&\text{if }i>k\\-\infty.&\text{otherwise}\end{cases}\\
[i\not\equiv 1\pmod k]f_{i-1}+\begin{cases}1&\text{if }a_i\ge mid,\\-1&\text{otherwise.}\end{cases}.
\end{cases}$$

然后就做完了。时间复杂度 $O(n\log V)$。

--- 
$(*)$ 注：此处的同余判断在代码中必须严格按照同余的定义，即 $i\bmod k=1\bmod k$ 或 $k\mid (i-1)$，原因显然。
```diff
- i%k==1
+ (i-1)%k==0
```

---

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define LF putchar('\n')
#define def(X) constexpr int X= 
def(N) 5e5+10; 
template<typename T>inline void read(T& x){
    x=0;int f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=~f+1;ch=getchar();}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    x*=f;
}
template<typename T,typename... Args>inline void read(T& x,Args&... args){
    read(x);
    read(args...);
}
template<typename T>inline void write(T x){
    static int buf[40],top=0;
    if(x<0){putchar('-');x=~x+1;}
    while(x)buf[++top]=x%10,x/=10;
    if(top==0)buf[++top]=0;
    while (top) putchar(buf[top--]^48);
    putchar(' ');
}
template<typename T,typename... Args>inline void write(T x,Args... args){
    write(x);
    write(args...);
}
int T,n,k,a[N],f[N];
bool check(int mid){
    for(int i=1;i<=n;i++){
        if(i>k)f[i]=f[i-k];
        else f[i]=-N;
        f[i]=max(f[i],((i-1)%k!=0)*f[i-1]+(a[i]>=mid?1:-1));
    }
    return f[n]>0;
}
signed main(){
    int i,j;
    read(T);
    while(T--){
        read(n,k);
        int maxx=0;
        for(i=1;i<=n;++i){
            read(a[i]);
            maxx=max(maxx,a[i]);
        }
        int l=0,r=maxx+1,mid=0;
        while(l+1<r){
            mid=(l+r)>>1;
            if(check(mid))l=mid;
            else r=mid;
        }
        write(l),LF;
    }
    return 0;
}
```

---

## 作者：lfxxx (赞：1)

考虑二分中位数，然后我们需要判定序列中只剩下 $0,1$，能否进行一些操作使得剩下的数中 $1$ 的数量严格大于 $0$ 的数量。

不妨记 $dp_i$ 表示考虑序列前 $i$ 位，进行一些操作使得 $1$ 的数量减去 $0$ 的数量最大是多少，显然有 $dp_i = \max(dp_{i - l \times k - 1}) + val_i$，这表示你删除了一个长度为 $l \times k$ 的段，如果删除的段相交，则可以合并成一个大段，因此在这个 dp 中认为删除的段不交是没有问题的。

然后直接记录余数优化即可，但是这里仍然有一些问题，也就是剩下的段长度至多为 $k$ 这一限制没有被考虑，注意这里无需考虑长度非 $0$ 的限制，因为长度为 $0$ 的序列中 $1$ 的数量减去 $0$ 的数量等于 $0$ 并不满足条件，考虑怎么处理长度至多为 $k$ 的限制，也就是至多转移 $k$ 次的限制，我们观察到，第 $i$ 次转移的点的下标对 $k$ 取模后为 $i$，那么我们不让对 $k$ 取模后为 $0$ 的状态去转移其他状态即可，时间复杂度 $O(n \log V)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 5e5+114;
int dp[maxn],cnt[maxn],n,k;
int a[maxn];
const int top = 1e9+114;
bool check(int x){
    if(k>n){
        int c=0;
        for(int i=1;i<=n;i++) c+=(a[i]>=x?1:-1);
        return c>0;
    }
    for(int i=1;i<=n;i++) dp[i]=-INT_MAX;
    for(int i=0;i<k;i++) cnt[i]=-INT_MAX;
    cnt[0]=0;
    int g=-INT_MAX;
    for(int i=1;i<=n;i++){
        if(i%k!=0){
            dp[i]=cnt[i%k-1]+(a[i]>=x?1:-1);
        }else dp[i]=cnt[k-1]+(a[i]>=x?1:-1);
        if(i%k!=0) cnt[i%k]=max(cnt[i%k],dp[i]);
        if(i%k==0) g=max(g,dp[i]);
    }
    cnt[0]=max(cnt[0],g);
    return max(dp[n],(n+1)%k==0?cnt[k-1]:cnt[(n+1)%k-1])>0;
}
void work(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    int l=0,r=top;
    while(l+1<r){
        int mid=(l+r)>>1;
        if(check(mid)==true) l=mid;
        else r=mid;
    }
    cout<<l<<'\n';
    return ;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        work();
    }
    return 0;
}
/*
1
7 1
5 9 2 6 5 4 6
*/
```

---

## 作者：hcng (赞：0)

提供一种和官方题解不一样的做法。

考虑二分答案，假设当前二分中点为 $x$。

我们知道在最后剩下的序列的长度 $m = (n - 1) \bmod k + 1$，那么如果 $x$ 合法，则存在一种删除方法使得剩下的序列中小于 $x$ 的数的数量不超过 $\lfloor {(m + 1) \div 2}\rfloor - 1$。另外，观察到其实题面描述的这种操作可以转化为删除掉原序列中若干不交且长度为 $k$ 的区间。考虑 dp，让 $dp_i$ 表示在前缀 $a_{1...i}$ 中删去若干个区间后，剩下的数小于 $x$ 的最少个数。转移为：

$$dp_i = \max(dp_{i - 1} + [a_i < x], dp_{i - k})$$

$dp_n \le \lfloor {(m + 1) \div 2}\rfloor - 1$ 时则 $x$ 合法。

我们不需要保证这个 dp 构造出来的方案会把原序列删到剩下 $m$ 个，因为如果 $dp_n \le \lfloor {(m + 1) \div 2}\rfloor - 1$，且我们还能继续删的话，我们只需要任意删除也能使得最终序列小于 $x$ 的个数不大于 $dp_n$。

有一个细节就是当 $n \bmod k = 0$ 的时候 dp 会直接删掉所有数，把 dp 再开一维，记录有没有保留过数就可以了。

配合离散化时间复杂度可以做到 $O(n\log n)$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, k, m;
int a[500010], b[500010];
int dp[500010][2];

bool check(int x) {
    dp[0][0] = 1e8;
    for (int i = 1; i <= n; i++) {
        int v = (a[i] >= x);
        if (v) {
            dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]);
        } else {
            dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]) + 1;
        }
        if (i >= k) {
            dp[i][1] = dp[i - k][1];
            dp[i][0] = min(dp[i][0], dp[i - k][0]);
        } else {
            dp[i][1] = 1e8;
        }
    }
    return (dp[n][0] <= m - 1);
}

inline void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    if (n % k != 0) m = (n % k + 1) / 2;
    else m = (k + 1) / 2;
    sort(b + 1, b + 1 + n);
    int L = 1, R = n;
    while (L < R) {
        int M = (L + R + 1) >> 1;
        if (check(b[M])) L = M;
        else R = M - 1;
    }
    cout << b[L] << endl;
    cerr << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t; cin >> t;
    while (t--) solve();
    
    return 0;
}
```

---

## 作者：UniGravity (赞：0)

## Solution CF1993D Med-imize

考虑如何判断中位数，可以想到使用二分 $mid$。记数组中大于等于 $mid$ 的数的数量为 $cnt_{\ge}$，小于的数量记为 $cnt_<$。若 $cnt_{\ge}>cnt_<$，则中位数一定大于等于 $mid$。

设新的 $b$ 数组为若 $a_i\ge mid$ 为 $1$ 否则为 $-1$。问题变为在 $b$ 数组上删去长度为 $k$ 的区间，问最后可能的最大 $\sum b$ 是否大于 $0$。

采用 dp 的方式。设 $f_i$ 表示进行到 $i$ 的最大和。

注意到一个性质，最后的数组元素（下标为 $now$）在原来 $b$ 中的下标 $old$ 有 $(old-1)\bmod k+1=now$。这是因为每次删去的区间长度都是固定的 $k$。

初始化所有的 $f_i=\max(f_{i-k},b_i)\ ((i-1)\bmod k=0)$。代表最后序列的第一个元素为 $i$。

对于其他的 $i$，有 $f_i=\max(f_{i-k},f_{i-1}+b_i)$。即分为删区间和不删两种可能。

[code](https://codeforces.com/contest/1993/submission/274491814)

---

## 作者：EricWan (赞：0)

一个很有意思的题。

看见中位数，直接把二分糊上去。

考虑 DP。但是状态太多了。

先向暴力 DP，定义 $dp_{i,j}$ 为前 $i-1$ 个元素的状态已定，已经删掉 $j$ 个长度为 $k$ 的段的最大的比当前二分 $mid$ 大的元素个数。

这样是 $n^2\log V$ 的，你会获得 TLE on #18 的好成绩！（别问我怎么知道的。）

考虑优化，发现对于每一个 $i$，真正有用的 $j$ 数量不多，经过~~乱试~~计算，发现 $j\in[\max\{0,\frac i k-2\},\min\{\frac{n - 1}k,\frac i k\}]$，于是，我们就可以开始快乐的 DP 了。

小 trick：现在的 DP 空间较大，可以在存储时将 $j$ 减去一个值来缩小值域。

代码：

```cpp
#include <bits/stdc++.h>
#define MAXN 1000005
#define getmin(i) ((i) / k - 2)
using namespace std;
int n, k, maxn, b[MAXN], dp[MAXN][5], a[MAXN];
int check(int mid) {
	int nowb = 0, cnt = 0;
	for (int i = 1; i <= n; i++) {
		dp[i][0] = dp[i][1] = dp[i][2] = dp[i][3] = dp[i][4] = 2 * n;
		nowb += ((a[i] >= mid) ? 1 : 0);
		cnt += ((a[i] >= mid) ? 1 : 0);
		if (i >= k - 1) {
			b[i - k + 1] = nowb;
			nowb -= ((a[i - k + 1] >= mid) ? 1 : 0);
		}
	}
	dp[n + 1][0] = dp[n + 1][1] = dp[n + 1][2] = dp[n + 1][3] = dp[n + 1][4] = 2 * n;
	dp[1][0 - getmin(1)] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = max(0, i / k - 2); j <= min((n - 1) / k, i / k); j++){
			dp[i + 1][j - getmin(i + 1)] = min(dp[i + 1][j - getmin(i + 1)], dp[i][j - getmin(i)]);
			dp[i + k][j - getmin(i + k) + 1] = min(dp[i + k][j - getmin(i + k) + 1], dp[i][j - getmin(i)] + b[i]);
		}
	}
	return cnt - dp[n + 1][(n - 1) / k - getmin(n + 1)];
}
signed main()
{
	int T = 1;
	cin >> T;
	while (T--) {
		maxn = 0;
		cin >> n >> k;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			maxn = max(maxn, a[i]);
		}
		int l = 0, r = maxn;
		while (l < r) {
			int mid = (l + r + 1) / 2;
			if (check(mid) >= ((n - 1) % k + 3) / 2)
				l = mid;
			else
				r = mid - 1;
		}
		cout << l << endl;
	}
	return 0;
}
```

---

## 作者：StarLbright40 (赞：0)

考虑按照 $(i-1)\bmod k+1$ 将序列 $\{ a_i\}$ 分为 $k$ 组，由于每次删除**连续的** $k$ 个元素直至 $\operatorname{size}(\{ a_i\})\le k$，所以每次删除都是在每组中恰删除一个元素，直至前 $(n-1)\bmod k+1$ 组恰有一个元素而其他组没有元素。

动态维护中位数是困难的，考虑二分答案，按照 $a_i\ge mid$ 是否成立将 $a_i$ 转化为 $1$ 或 $-1$，则原子序列中位数 $\ge mid$ 等价于新子序列和为正。

根据删除操作可知，最后保留的相邻两数在原序列中对应位置之间的数的个数一定为 $k$ 的非负整数倍，也即它们的组号 $(i-1)\bmod k+1$ 是相邻的。也就是说，最后保留的数位置越靠后，组号也一定越靠后。

设 $f_i$ 表示按如上规律在前 $i$ 组各保留一个数所得新子序列和的最大值，由于每个数的组号和位置都是确定的，依次更新即可，若 $f_{(n-1)\bmod k+1}>0$ 则当前的 $mid$ 可能成为答案。

时间复杂度 $\mathcal O(n\log V)$，在离散化的 $a$ 数组上二分答案可以做到 $\mathcal O(n\log n)$。

注意本题没有对 $\sum k$ 的范围做出限制，在初始化 dp 数组时小心超时。

[code](https://codeforces.com/contest/1993/submission/274462509)

---

