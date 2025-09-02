# Minimizing the Sum

## 题目描述

You are given an integer array $ a $ of length $ n $ .

You can perform the following operation: choose an element of the array and replace it with any of its neighbor's value.

For example, if $ a=[3, 1, 2] $ , you can get one of the arrays $ [3, 3, 2] $ , $ [3, 2, 2] $ and $ [1, 1, 2] $ using one operation, but not $ [2, 1, 2 $ \] or $ [3, 4, 2] $ .

Your task is to calculate the minimum possible total sum of the array if you can perform the aforementioned operation at most $ k $ times.

## 说明/提示

In the first example, one of the possible sequences of operations is the following: $ [3, 1, 2] \rightarrow [1, 1, 2 $ \].

In the second example, you do not need to apply the operation.

In the third example, one of the possible sequences of operations is the following: $ [2, 2, 1, 3] \rightarrow [2, 1, 1, 3] \rightarrow [2, 1, 1, 1] $ .

In the fourth example, one of the possible sequences of operations is the following: $ [4, 1, 2, 2, 4, 3] \rightarrow [1, 1, 2, 2, 4, 3] \rightarrow [1, 1, 1, 2, 4, 3] \rightarrow [1, 1, 1, 2, 2, 3] $ .

## 样例 #1

### 输入

```
4
3 1
3 1 2
1 3
5
4 2
2 2 1 3
6 3
4 1 2 2 4 3```

### 输出

```
4
5
5
10```

# 题解

## 作者：Herman526 (赞：11)

**本题需要设计 dp 状态，还要有一定的贪心技巧。**

由于本题是要求修改后和的最小值，我们可以很自然地想到 dp。注意到 $k$ 的值（即修改次数）很小，因此可以这样定义 dp 状态：设 $f_{i,j}$ 为对 $a$ 的前 $i$ 项进行 $j$ 轮操作后，$∑\limits_{p=1}^ia_p$ 的最小值。然而，在定义时，容易发现，我们不好判断在 $j$ 次操作中，$a_i$ 是否曾被改为 $a_{i+1}$。为了方便，我设计的状态中，**不能出现此情况**。

那么，如何进行递推呢？我们先考虑可以对一个长为 $m$ 的数列 $b$ 进行任意次操作的答案。采用贪心的思想，显然，我们可以用至多 $(m-1)$ 次操作将 $b$ 全部变为 $\min\{b_i\}$：设 $\min\{b_i\}=b_k$，则我们可以对 $k$ 至 $2$ 的每一个 $i$，依次令 $b_{i-1}←b_i$，并对 $k$ 至 $m-1$ 的每一个 $i$，依次令 $b_{i+1}←b_i$。此时，答案为 $m\min\{b_i\}$。而用 $(m-2)$ 次及以下的操作，则在最坏情况下无法令所有 $b_i$ 都变为 $\min\{b_i\}$。

由此，我们就可以推出 $f_{i,j}$ 的状态转移方程了。因为 $t$ 次操作在最坏情况下可以让 $(t+1)$ 个数变得一样，因此可以枚举 $t$，并让 $a_{i-t}∼a_i$ 变为 $\min\limits_{i-t⩽p⩽i}\{a_p\}$，再加上前 $(i-t-1)$ 个数的 dp 值 **（但操作次数要减 $t$）**。写成式子，即是：
$$f_{i,j}=\min\limits_{0⩽t⩽j}\{f_{i-t-1,j-t}+(t+1)\min\limits_{i-t⩽p⩽i}\{a_p\}\}(j<i)$$
这样，这道题的思路就完了。如果暴力算 $\min\limits_{i-t⩽p⩽i}\{a_p\}$ 的话，时间复杂度为 $O(∑nk^3)$，可能无法通过。但当 $t$ 增加 $1$ 时，我们可以将 $\min\limits_{i-t+1⩽p⩽i}\{a_p\}$ 再与 $a_{i-t}$ 取最小值，将原本 $O(k)$ 的时间优化到 $O(1)$。由此，我们得到了一个时间复杂度 $O(∑nk^2)$，空间复杂度 $O(\max\{nk\})$ 的做法。
```c++
//此代码中有多处用 i^j 代替 i!=j，且有部分变量名与题解不同
#import<ios>
int t,n,k,a[300000],x;long long f[300000][11],g,w,*m;
main(){
	scanf("%d",&t);
	do{
		scanf("%d%d",&n,&k);
		for(int i=0;i^n;++i){
			scanf("%d",a+i),g=a[i],m=f[i];//g 即为记录的最小值
			for(int j=k;~j;m[j--]=1e15);
			for(int j=0;j<=k&&j<=i;g=std::min(g,(long long)a[i-++j])){//一定要记得开 long long
				if(w=g*(j+1),i==j)m[i]=w;
				//此处要进行特判，因为当 i 与 j 相等时，
				//i-j-1 为 -1，会导致数组越界
				for(int p=i^j?j:i+1;p<=k&&p<=i;++p)m[p]=std::min(m[p],f[i-j-1][p-j]+w);
			}
		}
		m=f[n-1],w=1e15;
		for(int i=k;~i;w=std::min(w,m[i--]));
		printf("%lld\n",w);
	}while(--t);
}
```
其实这段代码还可以优化。利用滚动数组，可以将空间复杂度优化到 $O(\max\{k^2\})$（至少要记录前 $(k+1)$ 个状态）。但是，这样的实现较为麻烦，容易写错，且在本题没有必要。因此，我选择了相对好写的，空间复杂度 $O(\max\{nk\})$ 的做法。

---

## 作者：破壁人罗辑 (赞：4)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/CF1969C)/[Codeforces](https://codeforces.com/problemset/problem/1969/D)

## 题意简述

给出一个长度为 $n$ 的数组 $a$，每次可以选择两个数字 $i,j$，其中 $|i-j|=1$ 将 $a_j$ 的值变为 $a_i$，问在最多进行 $k$ 次操作的情况下 $\sum_{i=1}^na_i$ 的最小值。

数据范围：$1\leq n\leq3\times10^5,0\leq k\leq 10$。

## 解题思路

容易想到区间 dp。

设 $ans_{i,j}$ 表示区间 $[0,i]$ 经过 $j$ 次操作后的最小值，$val_{i,j}$ 表示区间 $[i,i+j]$ 经过 $j$ 次操作后的最小值，则可以得到如下状态转移方程：
$$ans_{i,j}=\begin{cases}
0&,i=0\\
\min_{h\leq\min(i-1,j)}(ans_{i-h-1,j-h}+val_{i-h,h})&,i>0
\end{cases}$$
最终得到的 $\min_{i\leq k}ans_{n,i}$ 即为所求答案。

预处理 $val_{i,j}$ 和动态规划求解 $ans_{i,j}$ 的时间复杂度都为 $O(nk^2)$，预处理的过程可以优化成 $O(nk)$，总时间复杂度 $O(nk^2)$，可以通过。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300001];long long p[300001][11],ans[300001][11];
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n,k;scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++){scanf("%d",a+i);p[i][0]=a[i];}
		for(int j=1;j<=k;j++)for(int i=1;i+j<=n;i++)p[i][j]=min(p[i][j-1],(long long)a[i+j]);
		for(int j=1;j<=k;j++)for(int i=1;i+j<=n;i++)p[i][j]*=(j+1);
		for(int i=1;i<=n;i++){
			ans[i][0]=ans[i-1][0]+a[i];
			for(int j=1;j<=k;j++){
				ans[i][j]=min(ans[i-1][j]+a[i],ans[i][j-1]);
				for(int h=0;h<i&&h<=j;h++)ans[i][j]=min(ans[i][j],ans[i-h-1][j-h]+p[i-h][h]);
			}
		}
		printf("%lld\n",ans[n][k]);
	}
	return 0;
}
```

---

## 作者：Jerrycyx (赞：2)

首先，每次操作的时候一定是用小的来替换大的，这时数组总和会减少一个值（就是这两个数的差）。

设 $f_{i,j}$ 表示前 $i$ 个元素执行 $j$ 次操作后**可以减去的最大值**，最后的答案就是 $sum_n - f_{n,k}$。

**每次操作可以将一段连续子串替换为其中的最小值**。设操作次数为 $l$，则可以这样处理长度为 $(l+1)$ 的一段区间。所消去的值为区间总和减去 $(l+1)$ 乘区间最小值，即：

$$\sum_{j=i-l}^{i} a_j - \min_{j=i-l}^{i} a_j$$

（上面的 $i$ 表示区间右端点）

枚举操作次数 $i$ 和 数列末尾 $j$，通过枚举操作次数 $l$ ，就可以用上面的式子就可以求出所有 $f_{j,i}$ 的值。

$$f_{j,i} = \max\left\{ f_{j-l-1,i-l} + sum\{a_{j-l} \sim a_{j}\} - \min\{a_{j-l} \sim a_j\} \times (l+1) \right\} $$

上面的式子中，等号右边表示：当后面连续操作 $l$ 次时得到可消去的最大值，等于前 $(j-l-1)$ 个数执行 $(i-l)$ 次操作所能消去的最大值，加上将后面的 $(l+1)$ 个数合并替换为区间最小值所能消去的值。

注意操作次数 $i$ 需要从 $0$ 开始枚举，枚举 $l$ 的时候需要排除负数下标（排除不可能的情况）。

时间复杂度 $O(nk^2)$，在数据范围是 $1 \le n \le 3 \times 10^5,0 \le k \le 10$ 的情况下可以接受（实际上只需 $359$ ms 即可）。

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

const int N=3e5+5,K=15;
int n,k,a[N];
long long sum[N],f[N][K];
long long getsum(int l,int r){return sum[r]-sum[l-1];}

int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			sum[i]=sum[i-1]+a[i];
		}
		for(int i=0;i<=k;i++)
			for(int j=1;j<=n;j++)
			{
				long long mina=a[j];
				for(int l=1;j-l>=1&&i-l>=0;l++) //l operations: [j-l,j](len=l+1)
				{
					mina=min(mina,(long long)a[j-l]);
					f[j][i]=max(f[j][i],f[j-l-1][i-l]+getsum(j-l,j)-mina*(l+1));
				}
				f[j][i]=max(f[j-1][i],f[j][i]);
			}
		printf("%lld\n",sum[n]-f[n][k]);
		
		for(int i=0;i<=k;i++)
			for(int j=1;j<=n;j++)
				f[j][i]=0;
		for(int i=1;i<=n;i++)
			a[i]=sum[i]=0;
	}
	return 0;
}
```

---

## 作者：CQ_Bob (赞：2)

## 分析

考虑 DP。

观察到 $k\le 10$，定义状态函数 $f_{i,j}$ 表示前 $i$ 个数改变了 $j$ 次的最小和。

对于 $i$，我们去枚举区间 $[l,r]$，使 $a_l \sim a_r$ 都改变为 $a_i$。则有：$f_{r,r-l+w}= \min(f_{r,r-l+w},f_{i-1,w}+(r-l+1)\times a_i)$。

时间复杂度差不多 $O(n k^3)$。~~赛时写的这个，不知道能不能过。~~

考虑优化，还是枚举 $l$，但钦定 $r=i$，则将区间 $[l,r]$ 赋成某个数时，最优的一定是区间的最小值。则：$f_{i,j} = \min(f_{i,j},f_{l-1,j-(i-l)}+m \times (i-l+1))$，其中 $m$ 是区间最小值。

复杂度 $O(nk^2)$。

---

## 作者：Day_Tao (赞：1)

### Sol

看到题目，我是先想到了贪心，对于每一次更新求出最大差分，再将那两项变成他们的最小值。

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 0x7fffffff;
const int mod = 998244353;
const int MAX = 3e5 + 5;
int T,n,a[MAX],p,k;
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]);
		for(int i=1;i<=k;i++)
		{
			int maxx=-1;
			for(int j=1;j<n;j++)
				if(abs(a[j]-a[j+1])>maxx)
					p=j,maxx=abs(a[j]-a[j+1]);
			if(maxx==-1)
				continue;
			a[p]=min(a[p],a[p+1]),a[p+1]=min(a[p],a[p+1]);
		}
		int sum=0;
		for(int i=1;i<=n;i++)
			sum+=a[i];
		printf("%lld\n",sum);
	}
	return 0;
}
```
但是 WA on test 2。

容易发现其实可以是一个小的数更新多个与之相邻的连续的数，这样的话贪心就假了。

再次读题，你也许就可以看出一些转移，即将操作了 $i-1$ 次的状态转移到操作了 $i$ 次，接着考虑怎么进行 DP。

我们设 $f_{i,j}$ 表示到了第 $i$ 个数，操作了 $j$ 次之后的 $\min\{\sum\limits _ {l=1} ^ {i} a_l\}$。先考虑一个数只能更新其后一个数的情况，这时状态转移方程就是 $f_{i,j}=min\{f_{i,j},f_{i-1,j-1}+min(a_i,a_{i-1})\}$。

由于一个数可以更新多个之相邻的连续的数，最终效果就是这一段的数都变成了这一段的最小值，而每段长度最大为 $k \le 10$。所以不妨枚举每个段，使之变为最小值，再进行转移。设 $l$ 为该段的长度，$mn$ 为该段最小值，这时的状态转移方程就是 $f_{i+l,j+l}=\min\{f_{i+l,j+l},f_{i-1,j}+(l+1)\times mn\}$。由于一次替换的操作是使得两个数变为它们的最小值，所以就是加上 $(l+1)\times mn$ 了。最后答案就是 $\min \limits _ {i=0} ^k \{f_{n,i}\}$。复杂度 $O(nk^2)$。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 0x7fffffff;
const int mod = 998244353;
const int MAX = 3e5 + 5;
int T,n,a[MAX],p,k,f[MAX][11];
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]);
		for(int i=0;i<=n;i++)
			for(int j=0;j<=k;j++)
				f[i][j]=INF;
		f[0][0]=0;
		for(int i=1;i<=n;i++)
			for(int j=0;j<=k;j++)
			{
				int minn=INF;
				for(int l=0;l+j<=k&&i+l<=n;l++)
				{
					minn=min(minn,a[i+l]);
					f[i+l][j+l]=min(f[i+l][j+l],f[i-1][j]+(l+1)*minn);
				}
			}
		int ans=INF;
		for(int i=0;i<=k;i++)
			ans=min(ans,f[n][i]);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

### END

---

## 作者：DYYqwq (赞：0)

首先看到这题，第一眼想到 dp。

设 $dp_{i,j}$ 表示，前 $i$ 个数，进行了 $j$ 次操作后能得到的总和最小值。然后我们钦定第 $i$ 个数不能对 $i + 1$ 做操作。

然后考虑到，一定是一段一段进行操作的，所以每次直接枚举一个转移开始的点，算一下就好了。

但是发现直接做时间爆炸，是 $O(nK^3)$ 的。于是列出式子仔细看一眼：

$dp_{i+k,j+k} = \min\limits_{0 \le k \le \min(K-j,n-i)} \{dp_{i-1,j}+(k+1) \times \min\limits_{i \le l \le i+k} a_l\}$

发现后面那一坨子取 $\min$ 的东西自然可以边转移边维护啊，自己循环一遍完全是没必要的。

结束了，时间复杂度是 $O(nK^2)$。

这东西极大值需要设特别大，我因为这个错了一发。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t , n , K , a[300010] , dp[300010][20];
void solve()
{
	scanf("%lld%lld" , &n , &K);
	for(int i = 0 ; i <= n ; i ++) for(int j = 0 ; j <= K ; j ++) dp[i][j] = 9e18;
	for(int i = 1 ; i <= n ; i ++) scanf("%lld" , &a[i]);
	dp[0][0] = 0;
	for(int i = 1 ; i <= n ; i ++) for(int j = 0 ; j <= K ; j ++) for(int k = 0 , mn = a[i + k] ; k <= min(K - j , n - i) ; k ++ , mn = min(mn , a[i + k])) dp[i + k][j + k] = min(dp[i + k][j + k] , dp[i - 1][j] + (k + 1) * mn);
	int ans = 9e18;
	for(int i = 0 ; i <= K ; i ++) ans = min(ans , dp[n][i]);
	printf("%lld\n" , ans);
}
signed main()
{
	scanf("%lld" , &t);
	while(t --) solve();
	return 0;
}
```

---

## 作者：__Louis__ (赞：0)

## 题解：CF1969C Minimizing the Sum

### 题目大意

给你一个序列，定义一次操作是把一个数换成相邻两个数其中之一。现在你可以操作 $k$ 次，问最后整个序列和的最小值为多少。

### 思路

注意到 $k \le 10$，所以这可能是突破口。

首先意识到对于连续的几次操作，其效果相当于把一个区间赋值成其区间最小的数。

所以考虑 dp。

设 $dp[i][j]$ 表示 考虑前 $i$ 位，已经合并了 $j$ 次。

则有转移方程


$$ dp_{i,j}= \min_{d\le j}(dp_{i-d-1,j-d}+ find_{i-d,i}*(f+1) ) $$

其中 $find_{i,j}$ 表示区间 $[i,j]$ 中的最小值，用 st 表处理即可。

### code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=3e5+10;
int arr[maxn];
int dp[maxn][20];
int st[maxn][20];
void init(int n){
	for(int i=0;i<=n;i++){
		for(int j=0;j<20;j++){
			st[i][j]=0x3f3f3f3f3f3f3f3f;
			dp[i][j]=0x3f3f3f3f3f3f3f3f;
		}
	}
	for(int i=1;i<=n;i++){
		st[i][0]=arr[i];
	}
	for(int j=1;j<20;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
}
int find(int l,int r){
	int f=log2(r-l+1);
	return min(st[l][f],st[r-(1<<f)+1][f]);
}
signed main(){
	int T;
	scanf("%lld",&T);
	while(T--){
		int n,k;
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%lld",&arr[i]);
		}
		init(n);
		if(n<=k+1){
			printf("%lld\n",find(1,n)*n);
			continue;
		}
		dp[0][0]=0;
		for(int i=1;i<=n;i++){
			for(int j=0;j<=min(i-1,k);j++){
				for(int p=0;p<=j;p++){
					int f=j-p;
					dp[i][j]=min(dp[i-f-1][p]+find(i-f,i)*(f+1),dp[i][j]);
				}
			}
		}
		printf("%lld\n",dp[n][k]);
	}
}
```

---

