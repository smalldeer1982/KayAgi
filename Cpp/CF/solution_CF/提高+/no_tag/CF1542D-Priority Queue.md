# Priority Queue

## 题目描述

You are given a sequence $ A $ , where its elements are either in the form + x or -, where $ x $ is an integer.

For such a sequence $ S $ where its elements are either in the form + x or -, define $ f(S) $ as follows:

- iterate through $ S $ 's elements from the first one to the last one, and maintain a multiset $ T $ as you iterate through it.
- for each element, if it's in the form + x, add $ x $ to $ T $ ; otherwise, erase the smallest element from $ T $ (if $ T $ is empty, do nothing).
- after iterating through all $ S $ 's elements, compute the sum of all elements in $ T $ . $ f(S) $ is defined as the sum.

The sequence $ b $ is a subsequence of the sequence $ a $ if $ b $ can be derived from $ a $ by removing zero or more elements without changing the order of the remaining elements. For all $ A $ 's subsequences $ B $ , compute the sum of $ f(B) $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the following are all possible pairs of $ B $ and $ f(B) $ :

- $ B= $ {}, $ f(B)=0 $ .
- $ B= $ {-}, $ f(B)=0 $ .
- $ B= $ {+ 1, -}, $ f(B)=0 $ .
- $ B= $ {-, + 1, -}, $ f(B)=0 $ .
- $ B= $ {+ 2, -}, $ f(B)=0 $ .
- $ B= $ {-, + 2, -}, $ f(B)=0 $ .
- $ B= $ {-}, $ f(B)=0 $ .
- $ B= $ {-, -}, $ f(B)=0 $ .
- $ B= $ {+ 1, + 2}, $ f(B)=3 $ .
- $ B= $ {+ 1, + 2, -}, $ f(B)=2 $ .
- $ B= $ {-, + 1, + 2}, $ f(B)=3 $ .
- $ B= $ {-, + 1, + 2, -}, $ f(B)=2 $ .
- $ B= $ {-, + 1}, $ f(B)=1 $ .
- $ B= $ {+ 1}, $ f(B)=1 $ .
- $ B= $ {-, + 2}, $ f(B)=2 $ .
- $ B= $ {+ 2}, $ f(B)=2 $ .

The sum of these values is $ 16 $ .

## 样例 #1

### 输入

```
4
-
+ 1
+ 2
-```

### 输出

```
16```

## 样例 #2

### 输入

```
15
+ 2432543
-
+ 4567886
+ 65638788
-
+ 578943
-
-
+ 62356680
-
+ 711111
-
+ 998244352
-
-```

### 输出

```
750759115```

# 题解

## 作者：岸芷汀兰 (赞：21)

# 一、题目：

[洛谷原题](https://www.luogu.com.cn/problem/CF1542D)

[codeforces原题](https://codeforces.com/problemset/problem/1542/D)

# 二、思路：

这道题很明显是一道 DP 题。

考虑计算某个 `+ x` 对答案的贡献。也就是说，我们的目标是对于每个 `+ x`，求出有多少个子序列满足经过一番操作之后，这个 $x$ 会被统计到答案中。

对于固定的、处于位置 $p$ 的一个 `+ x`，考虑 DP。设 $dp[i,j]$ 表示考虑了前 $i$ 位，有 $j$ 个比 $x$ 小的方案数。

1. 若第 $i$ 位是 `-`，则 $dp[i,j]=dp[i-1,j]+dp[i-1,j+1]$。

   这里需要着重强调，如果 $i<p$ 且 $j=0$，那么 $dp[i,0]$ 还要再加上 $dp[i-1,0]$。原因是这样的，如果 $i<p$，那么根据题目的约定，如果此时 $T$ 是空的，那么我们什么也不做，所以，此时选上 `-` 号不会使得 $j$ 变小。如果此时 $T$ 中还有比 $x$ 大的数，那 `-` 号也只会消去比 $x$ 大的数，同样对 $j$ 没有影响。

2. 若第 $i$ 位是正数而且比 $x$ 大，则 $dp[i,j]=dp[i-1,j]\times 2$。选和不选都不会使得 $j$ 改变。

3. 若第 $i$ 位是正数而且比 $x$ 小，则
   $$
   dp[i,j]=
   \begin{cases}
   dp[i-1,j] &j=0\\
   dp[i-1,j]+dp[i-1,j-1] &j>0
   \end{cases}
   $$

细心的同学可能会发现，那第 $i$ 位如果和 $x$ 相等怎么办？

我的处理方法是这样的，为了避免重复计算，强制规定，如果 $i<p$，那么就把它归到第 3 种情况中；如果 $i>p$，那么就把它归到第 2 种情况中。

# 三、代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
#define FILEIN(s) freopen(s, "r", stdin)
#define FILEOUT(s) freopen(s, "w", stdout)
#define mem(s, v) memset(s, v, sizeof s)

inline int read(void) {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return f * x;
}

const int MAXN = 505, MOD = 998244353;

int n, a[MAXN];
long long dp[MAXN][MAXN];

int main() {
    n = read();
    for (int i = 1; i <= n; ++ i) {
        char op[3]; scanf("%s", op);
        if (*op == '-')
            a[i] = -1;
        else
            a[i] = read();
    }
    long long ans = 0;
    for (int p = 1; p <= n; ++ p) {
        if (a[p] < 0) continue;
        int x = a[p];
        mem(dp, 0); dp[0][0] = 1;
        for (int i = 1; i <= n; ++ i) {
            if (i == p) {
                memcpy(dp[i], dp[i - 1], sizeof dp[i]);
                continue;
            }
            for (int j = 0; j <= n; ++ j) {
                if (a[i] < 0) {
                    dp[i][j] = (dp[i - 1][j] + dp[i - 1][j + 1]) % MOD;
                    if (j == 0 && i < p) (dp[i][j] += dp[i - 1][j]) %= MOD;
                }
                else if (a[i] < x || (a[i] == x && i < p)){
                    dp[i][j] = dp[i - 1][j];
                    if (j > 0) (dp[i][j] += dp[i - 1][j - 1]) %= MOD;
                }
                else
                    dp[i][j] = 2 * dp[i - 1][j] % MOD;
            }
        }

        long long sum = 0;
        for (int j = 0; j <= n; ++ j)
            (sum += dp[n][j]) %= MOD;
        (ans += sum * x % MOD) %= MOD;
    }
    printf("%lld\n", ans);
    return 0;
}
```



---

## 作者：MatrixCascade (赞：14)

套路题。

我们考虑对每一个“+”的位置去计算贡献，也就是使这个位置的数到最后还存在的方案数。

假设我们算的是 $p$ 位置的贡献，于是可以设 $dp_{i,j}$ 表示当前枚举到 $i$ 位置，目前集合中有 $j$ 个比 $val_{p}$ 小的数，然后分情况讨论。

- $i<p$ 的情况：

若当前这一位是“-”号，那么就有 $dp_{i,j}=dp_{i-1,j}+dp_{i-1,j+1}$，另外特别注意一下 $dp_{i,0}$ 需要再次 + $dp_{i-1,0}$（不选这个“-”号，不变，选了这个“-”号并且 $j$ **本来就已经是 0 了**，也是不变，因此 $$dp_{i-1,0}$要算两遍）

如果是“+”号，并且当前的 $val_{j}>val_{p}$，那么选不选都无所谓，就有 $dp_{i,j}=dp_{i-1,j}*2$；否则的话，如果选，$j$ 就增加 $1$，否则不变，就有$dp_{i,j}=dp_{i-1,j}+dp_{i-1,j-1}$

- $i=p$ 的情况：

必须选，所以只需 $dp_{i,j}=dp_{i-1,j}$

- $i>p$ 的情况：

和 $i<p$ 有两点不同：

1. 如果当前是 “-” 号，$dp_{i,0}$ 只需加一遍 $dp_{i-1,0}$（如果已经是 0 了就不能再删了，不然 p 就要被删了）
1. 如果当前是 “+” 号，改为 $val_{j}\geq val_{p}$ 的情况下无所谓选不选（不然在有重复数的情况下方案算重，会 WA on 3）。  

可以试试  
```
4
-
+ 1
+ 1
-
```

这组数据，输出为 10


```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define int long long
#define up(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define down(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
using namespace std;
int n, m, k;
int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}
const int mod=998244353;
const int maxn=555;
int opt[maxn],val[maxn];
int dp[maxn][maxn];
signed main()
{
	n=read();
	int sum=0;
	up(i,1,n)
	{
		
		char c;
		cin>>c;
		if(c=='+')
		{
			opt[i]=1;
			val[i]=read();
		}
	}
	up(i,1,n)
	{
		if(opt[i]==1)
		{	
			memset(dp,0,sizeof(dp));
			int v=val[i];
			int p=i;
			dp[0][0]=1;
			up(j,1,i-1)
			{
				if(opt[j]==0)
				{
					up(k,0,n)
					{
						dp[j][k]+=dp[j-1][k];
						dp[j][k]%=mod;
					}
					up(k,0,n)
					{
						dp[j][k]+=dp[j-1][k+1];
						dp[j][k]%=mod;
					}
					dp[j][0]=(dp[j][0]+dp[j-1][0])%mod;
				}
				else
				{
					if(val[j]>v)
					{
						up(k,0,n)
						{
							dp[j][k]+=dp[j-1][k]*2%mod;
							dp[j][k]%=mod;
						}
					}
					else
					{
						up(k,0,n)
						{
							dp[j][k]+=dp[j-1][k]%mod;
							dp[j][k]%=mod;
						}
						up(k,1,n)
						{
							dp[j][k]+=dp[j-1][k-1]%mod;
							dp[j][k]%=mod;
						}
					}
				}
			}
			up(j,0,n)
			{
				dp[i][j]=dp[i-1][j];
			}
			up(j,i+1,n)
			{
				if(opt[j]==0)
				{
					up(k,0,n)
					{
						dp[j][k]+=dp[j-1][k];
						dp[j][k]%=mod;
					}
					up(k,0,n)
					{
						dp[j][k]+=dp[j-1][k+1];
						dp[j][k]%=mod;
					}
					//dp[j][0]=(dp[j][0]+dp[j-1][0])%mod;
				}
				else
				{
					if(val[j]>=v)
					{
						up(k,0,n)
						{
							dp[j][k]+=dp[j-1][k]*2%mod;
							dp[j][k]%=mod;
						}
					}
					else
					{
						up(k,0,n)
						{
							dp[j][k]+=dp[j-1][k]%mod;
							dp[j][k]%=mod;
						}
						up(k,1,n)
						{
							dp[j][k]+=dp[j-1][k-1]%mod;
							dp[j][k]%=mod;
						}
					}
				}
			}
			int ans=0;
			up(j,0,n)
			{
				ans+=dp[n][j]*val[i]%mod;
				ans%=mod;
			}
			sum+=ans;
			sum%=mod;
		}
		
	}
	cout<<sum;
}

```


---

## 作者：Acfboy (赞：6)

就这伞兵题我居然赛场上写挂了。

首先一个简单的想法是分开考虑每一个 $a_i$ 出现了多少次，因为考虑很多个数非常的困难，而只考虑一个数是否出现在最终的可重集中就方便得多了。  
一个数出现在最后的充要条件是对于后面出现第 $k$ 个 `-` 时，都有至少 $k$ 个数比当前的数小。

那么就只需要考虑对于每一个数，满足以上充要条件的方案数有多少个就可以了。由于数据范围是 $500$, 所以求这个方案数的时间复杂度必须要在 $n^2$ 以内。

赛场上我想到 $f_i$ 表示到 $i$ 个 `-` 的合法方案有多少个，可是这样得枚举上一个转移来的位置 $j$, 但中间取多少个又不知道，还得枚举取了多少个。这样时间就变成了 $n^3$ 了，总时间复杂度 $n^4$, 无法通过。~~然后被一个错误的性质误导以为自己成功优化，最后噼里啪啦写完发现样例都过不了。~~

那么想想怎么优化这个 dp，我们真的需要关心两个 `-` 之间出现了多少个小于当前选的数的数吗？  
其实不然，要知道的只是在出现 $x$ 个 `-` 后比当前小的是不是多于 $x$ 个。而且在背包问题中，并不需要枚举上一个选择的是哪里，只需要管当前这个取不取就可以了。  
所以首先把状态改成 $f_{i,j}$ 表示取到 $i$，有 $j$ 个比当前选中的数小的方案数。然后模仿背包的时候，从前一个转移过来就可以了。

但实际上这个 $i$ 在处理到当前选的数之前的转移和之后的是不同的，因为之前的只需要选到 $j$ 个就行，而之后的必须保证满足上面的充要条件（不然当前这个就被仍了啊）。

具体地，选中枚举到的第 $i$ 个对于当前位置之前的转移:

- 若是 `+` 操作，那么 `add(f[j][k + (a[j] <= a[i])], f[j-1][k]);`。
- 对于 `-` 操作 `add(f[j][std::max(k-1, 0ll)], f[j-1][k]);`

（因为代码里枚举当前数用了 $i$ 所以这里只能用 $j,k$ 了）

而对于之后的转移：

- 若是 `+` 操作，那么 `add(f[j][k + (a[j] < a[i])], f[j-1][k])`。（有变化，`<=` 改 `<` 了，因为不能把这个给删了）
- 对于 `-` 操作 `if (k) add(f[j][k-1], f[j-1][k]);`（有变化，必须要满足条件才能加）

而若当前的不选，两边都是 `add(f[j][k], f[j-1][k]);`

最后把方案数和当前数的值乘起来求和就可以了。

完整代码。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
const int N = 505, P = 998244353;
int n, a[N], x, f[N][N], ans;
char opt[5];
void add(int &x, int y) { x = (x + y) % P; }
signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", opt);
        if (opt[0] == '-') a[i] = -1;
        else scanf("%lld", &x), a[i] = x;
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] == -1) continue;
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        for (int j = 1; j < i; j++)
            for (int k = 0; k <= j; k++) {
                if (a[j] > 0) add(f[j][k + (a[j] <= a[i])], f[j-1][k]);
                else add(f[j][std::max(k-1, 0ll)], f[j-1][k]);
                add(f[j][k], f[j-1][k]);
            }
        for (int j = 0; j <= i; j++) f[i][j] = f[i-1][j];
        for (int j = i+1; j <= n; j++)
            for (int k = 0; k <= j; k++) {
                if (a[j] > 0) add(f[j][k + (a[j] < a[i])], f[j-1][k]);
                else if (k) add(f[j][k-1], f[j-1][k]);
                add(f[j][k], f[j-1][k]);
            }
        for (int j = 0; j <= n; j++) add(ans, f[n][j] * a[i] % P);
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：cmll02 (赞：5)

巨大多细节 dp。

考虑 $n^3$ 的做法。

对每个 `+ x` 分别考虑贡献。

设 $dp_{i,j}$ 表示到 $i$ 位置，集合里有 $j$ 个 $\le a_c$ 的数（$c$ 是当前正在计算贡献的位置）的方案数。

可以列出转移方程。


对于每个 $c$ 算一遍就行了。

具体：如果 $i$ 是 `+ x` 且 $x>a_i$ 则 $dp_{i,j}=2dp_{i-1,j}$（选不选两种都可）；

如果 $x<a_i$（为了防止算重用了双关键字比较），那么 $dp_{i,j}=dp_{i-1,j-1}+dp_{i-1,j}$。

如果是 $i=c$ 就强制选。

遇到 `-` 号类似转移。

然后稍微判断一下边界（$dp_{i,0}$）的问题。

注意如果 $i>c$ 那么要把 $dp_{i,0}$ 设置为 $0$，因为这个数已经被删了。
```cpp
// Problem: D. Priority Queue
// Contest: Codeforces - Codeforces Round #729 (Div. 2)
// URL: https://codeforces.com/contest/1542/problem/D
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//lost in rain
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <stdio.h>
#include <string.h> 
#include <algorithm>
#define oldl(x) printf("%lld\n",x)
#define rg(x) for(int i=1;i<=(x);i++){
#define rg_(i,x) for(int i=1;i<=(x);i++){
#define gr }
#define int long long
inline int read()
{
	int num=0,f=1;char c=getchar();
	while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
	while(c>47&&c<58)num=num*10+(c^48),c=getchar();
	return num*f;
}
inline int re1d()
{
	char c=getchar();
	while(c!='+'&&c!='-')c=getchar();
	return c=='+';
}
inline int min(int a,int b){return a>b?b:a;}
inline int max(int a,int b){return a<b?b:a;}
int a[505],b[505],dp[505][505];
signed main()
{
	int n=read();
	rg(n)int op=re1d();
	if(op)a[i]=1,b[i]=read();gr
	int ans=0;
	const int mod=998244353;
	rg(n)
		if(a[i]==0)continue;
		memset(dp,0,sizeof(dp));
		dp[0][0]=1;
		rg_(j,n)
			if(j==i)
			{
				rg(n)dp[j][i]=dp[j-1][i-1];gr
				continue;
			gr
			if(a[j])
			{
				if(b[j]<b[i]||(b[j]==b[i]&&j<i))
				{
					rg_(k,j)dp[j][k]=dp[j-1][k]+dp[j-1][k-1];
					dp[j][k]%=mod;
					gr
					dp[j][0]=dp[j-1][0];
				gr
				else rg_(k,n+1)dp[j][k-1]=dp[j-1][k-1]*2;dp[j][k-1]%=mod;gr
			gr
			else 
			{
				rg_(k,j)dp[j][k]=dp[j-1][k]+dp[j-1][k+1];dp[j][k]%=mod;gr
				dp[j][0]=dp[j-1][0]*2+dp[j-1][1];dp[j][0]%=mod;
			gr
			if(j>i)dp[j][0]=0;
	//		rg_(k,n+1)odb(dp[j][k-1]);gr puts("");
		gr //puts("");
		int q=0;
		rg_(j,n)q+=dp[n][j];q%=mod;gr
		ans=(ans+q*b[i])%mod;
	//	odb(q);
	gr
	oldl(ans);
	return 0;
}
```

---

## 作者：cyh_toby (赞：4)

[题目](https://www.luogu.com.cn/problem/CF1542D)

没做出来所以纪念一下（（（

此篇详细介绍了如何想到最后的 DP 状态。

首先容易想到分别对每个数计算贡献，那么就是要对每个数计算有多少个子序列最终会包含它。

假定现在考虑计算第 $s$ 个数的贡献，那先把 $s$ 从序列当中抽出来，不在 DP 中考虑它。一开始，我考虑设 $f_{i,j}$ 表示前 $i$ 个数中 「**小于** $a_s$ 的数 $-$ 选择的 `-` 的个数」为 $j$ 时，有多少种子序列。但显然这有一些问题：

- 原序列中可能有相等的数，但删除只任意删除一个；

- 在 $s$ 之前并且大于 $a_s$ 的数其实也可以起到「抵消 `-` 的作用」，但是在 $s$ 之后，这些数就不能使用了（因为会 `-` 会先删去 $a_s$）。

对于第一点，我们可以人为规定对于相等的数，优先删除靠前的，这显然不会影响答案。对于后一点，它启发我们这个 DP 应当分 $s$ 之前和 $s$ 之后两部分考虑。

然后会考虑设 $f_{i,j,k}$ 表示前 $i$ 个数，被 `-` 抵消后还剩 $j$ 个小于等于 $a_s$ 的数，$k$ 个大于 $a_s$ 的数，有多少种子序列。但这样会是 $O(n^3)$ 的 DP, 总复杂度 $O(n^4)$，过不了……吗？但是我看见有大佬这么过了所以可能此处分析的不对，望大佬们指点迷津orz。

这时候发现其实可以继承最开始定义的状态，只把小于改成小于等于。那么在 $s$ 之前有

$$f_{i,j}=\begin{cases}f_{i-1,j}+f_{i-1,j+1} + [j=0]f_{i-1,j} & (a_i=-) \\ f_{i-1,j} + f_{i-1,j-1} & (a_i \le a_s) \\ f_{i-1,j}+f_{i-1,j} & (a_i > a_s)\end{cases}$$

在 $s$ 之后，有

$$f_{i,j}=\begin{cases}f_{i-1,j}+f_{i-1,j+1} & (a_i=-) \\ f_{i-1,j}+f_{i-1,j-1} & (a_i < a_s) \\ f_{i-1,j}+f_{i-1,j} & (a_i > a_s)\end{cases}$$

为什么？可以这么说，比 $a_s$ 大的数具体选了多少个并不重要，它不会影响到之后的选择方法（被归入了第一组方程的第一个式子的第三项中），只会影响子序列的数量。不理解可以手动模拟一下。

对每个 $s$ 做一次 DP，然后求 $a_s \times \sum_{i=0}^nf_{n,i}$ 的和就是答案。

总时间复杂度 $O(n^3)$。

```cpp
const int N = 505, D = 501, mod = 998244353;
typedef long long ll;

int n;
int a[N];
char str[3];
ll f[2][N], ans;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", str + 1);
		if (str[1] == '+') scanf("%d", &a[i]);
		else a[i] = -1;
	}
	for (int s = 1; s <= n; s++) {
		if (a[s] == -1) continue;
		for (int i = 0; i <= n; i++) f[0][i] = 0;
		f[0][0] = 1;
		for (int i = 1; i < s; i++) {
			for (int j = 0; j <= n; j++) {
				if (a[i] != -1) {
					if (a[i] <= a[s]) f[1][j] = (f[0][j] + (j > 0 ? f[0][j-1] : 0)) % mod;
					else f[1][j] = (f[0][j] + f[0][j]) % mod;
				}
				else {
					f[1][j] = (f[0][j] + (j < n ? f[0][j+1] : 0)) % mod;
					if (j == 0) f[1][j] = (f[1][j] + f[0][j]) % mod; 
				}
			}
			for (int j = 0; j <= n; j++) f[0][j] = f[1][j];
		}
		for (int i = s + 1; i <= n; i++) {
			for (int j = 0; j <= n; j++) {
				if (a[i] != -1) {
					if (a[i] < a[s]) f[1][j] = (f[0][j] + (j > 0 ? f[0][j-1] : 0)) % mod;
					else f[1][j] = (f[0][j] + f[0][j]) % mod;
				}
				else f[1][j] = (f[0][j] + (j < n ? f[0][j+1] : 0)) % mod;
			}
			for (int j = 0; j <= n; j++) f[0][j] = f[1][j];
		}
		ll sum = 0;
		for (int i = 0; i <= n; i++) sum = (sum + f[0][i]) % mod;
		ans = (ans + 1ll * a[s] * sum % mod) % mod;
	}
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：YCS_GG (赞：2)

因为子序列有 $2^n$ 个所以基本只能考虑每个元素带来的贡献

也就是每个元素在所有子序列操作的最终结果里出现的次数，思考一下这个东西似乎没办法组合计数，因为限制条件极多

所以考虑 DP 来算方案，假设我们现在钦定 $x$ 出现在最终序列里

设 $dp_{i,j}$ 表示考虑到第 $i$ 个，目前的 $T$ 中有 $j$ 个 **小于等于** $x$ 的数字

每次 $-$ 操作会消耗一个 $j$ , 加入新的小于 $x$ 的数字会增加

最终统计一下 $\sum\limits_{j=1}^ndp_{n,j}$ 就是方案数

注意如果现在的 $i$ 已经超过了 $x$ 的位置，$dp_{i,0}$ 恒为零，因为我们要保证 $x$ 不被排出去

复杂度 $O(n^3)$ 

应该还有复杂度更优的做法，不过这个做法比较好想

[Code](https://pasteme.cn/134522)

---

## 作者：do_while_true (赞：1)

考虑一个数对答案的贡献，我们想要的是有替当前这个数 pop 的替死鬼，那么可以设计一个 dp：设 $f_{i,j}$ 为当前考虑 $a_x$ 在原序列选到 $i$，共有 $j$ 个替死鬼。注意到由于可以是非连续的子序列，所以每个 $f_{i,j}$ 转移可以从 $<i$ 的所有 $k$，所有的 $f_{k,j'}$ 转移而来。$j'$ 是固定的，具体选哪个我们后面再说。这样子一次 $f_{i,j}$ 就可以通过处理出对于每个 $j$，预处理出所有 $f_{k,j}$ 的前缀和，做到 $\mathcal{O}(1)$ 转移。

那么如何选择 $j'$ ？注意到如果当前 $a_i=a_x$，没有定义谁先 pop，所以钦定遇到此类情况，且 $i<x$ 的时候 $a_i$ 才能当 $a_x$ 的替死鬼。由于相等时弹出的数之间是没有区分的，但只有一种弹出的方案，所以给他加上区分仍然只有一种弹出方案，这样钦定是正确的。

综上所述，可以简单地设出一个 $f_{i,j}$ 的 dp，来得到 $a_x$ 对答案贡献了多少次，一共枚举 $\mathcal{O}(n)$ 个 $x$，一次 dp $\mathcal{O}(n^2)$，复杂度为 $\mathcal{O}(n^3)$。

> 简单来讲，我们做的是考虑一个数对答案贡献的次数，基于“替死鬼”的贪心设计一个 dp。

详细 dp 方程见代码。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
typedef long long ll;
const ll mod = 998244353;
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T> T Add(T x, T y) { return (x + y >= mod) ? (x + y - mod) : (x + y); }
template <typename T> T Mul(T x, T y) { return x * y % mod; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = (r << 3) + (r <<1) + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
ll qpow(ll x, ll y) {
	ll sumq = 1;
	while(y) {
		if(y&1) sumq = sumq * x % mod;
		x = x * x % mod;
		y >>= 1;
	} return sumq;
}
const int N = 510;
int n, a[N];
ll s[N], f[N][N], ans;
void dp(int p) {
	s[0] = 1;
	for(int i = 1; i <= n; ++i) {
		if(i == p) continue ;
		for(int j = 0; j <= i; ++j) {
			if(a[i] == 1 && !j) { f[i][j] = 0; continue ; }
			if(a[i] != -1) {
				if(a[i] < a[p] || (a[i] == a[p] && i < p)) f[i][j] = s[j-1];
				else f[i][j] = s[j] % mod;
			}
			else f[i][j] = Add(s[j+1], (j==0 && i < p) ? s[0] : 0ll);
		}
		for(int j = 0; j <= i; ++j) s[j] = Add(s[j], f[i][j]);
	}
}
signed main() {
	read(n);
	for(int i = 1; i <= n; ++i) {
		char ch; std::cin >> ch;
		if(ch == '+') read(a[i]);
		else a[i] = -1;
	}
	for(int i = 1; i <= n; ++i)
		if(a[i] != -1) {
			for(int j = 1; j <= n; ++j) s[j] = 0;
			dp(i);
			ll sum = 0;
			for(int i = 0; i <= n; ++i) sum = Add(sum, s[i]);
			ans = Add(ans, sum * a[i] % mod);
		}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2200}$
---
### 解题思路：

考虑对于每一个位置单独计算贡献。那么也就是要求出有多少种方案能使得这个位置能够产生贡献。

数据范围较小，可以对每一个位置进行动态规划，设 $f_{i,j}$ 表示考虑到 $i$ 个位置，当前存在 $j$ 个比要考虑的数（不妨设为 $a_t$，位置为 $t$）小的数。

当 $i<t$ 的时候。若当前位置为减号，可以不取，此时 $f_{i,j}$ 可以由 $f_{i-1,j}$ 转移过来，如果要取，则 $f_{i,j}$ 可以由 $f_{i-1,j+1}$ 转移过来。特殊地，当 $j$ 等于 $0$ 时，也可以继续取减号，此时 $f_{i,0}$ 可以由 $f_{i-1,0}$ 转移过来。如果是数字，再分为三种种情况考虑，如果 $a_i>a_t$ 则取和不取不会对 $j$ 造成改变，只会额外多一种方案，有 $f_{i,j}$ 可以由 $f_{i-1,j}$ 转移两次。$a_i<a_t$ 则不取时有 $f_{i,j}$ 可以由 $f_{i-1,j-1}$ 转移过来。特殊地，当 $a_i=a_t$ 的时候，可以强制让先入的先出，也就是用和 $a_i<a_t$ 一样的方式转移，而在之后的阶段里（$i\ge t$）用前一种转移方式。

恰好处在 $t$ 位置的时候，一定要取，没有任何操作。

当 $i>t$ 的时候，有类似的转移方式，不过此时 $j=0$ 时意味着 $a_t$ 就是最小的数，不能取走。还需要结合之前说的恰好等于的情况。

最后将方案数乘以权值加到答案里去，因为不涉及除法或其他较为特殊的运算，所以完全可以一边做一边取模。


---
### 代码：

```cpp
#include<cstdio>
using namespace std;
#define int long long
const int MOD=998244353;
int n,num[505],f[505][505],ans;
char get(){
	char c=getchar();
	while(c=='\n'||c=='\r'||c==' ')c=getchar();
	return c;
}
int read(){
	int num=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())num=num*10+c-'0';
	return num;
}
signed main(){
	scanf("%I64d",&n);
	for(int i=1;i<=n;i++){
		if(get()=='+')num[i]=read();
		else num[i]=-1;
	}
	for(int t=1;t<=n;t++){
		if(num[t]==-1)continue;
		for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)f[i][j]=0;
		f[0][0]=1;
		for(int i=1;i<t;i++)
		for(int j=0;j<=n;j++){
			f[i][j]=(f[i][j]+f[i-1][j])%MOD;
			if(num[i]==-1){
				f[i][j]=(f[i][j]+f[i-1][j+1])%MOD;
				if(j==0)f[i][j]=(f[i][j]+f[i-1][j])%MOD;
				continue;
			}
			if(num[i]>num[t])f[i][j]=(f[i][j]+f[i-1][j])%MOD;
			if(num[i]<=num[t]&&j>=1)f[i][j]=(f[i][j]+f[i-1][j-1])%MOD;
		}
		
		for(int j=0;j<=n;j++)f[t][j]=(f[t][j]+f[t-1][j])%MOD;
		
		for(int i=t+1;i<=n;i++)
		for(int j=0;j<=n;j++){
			f[i][j]=(f[i][j]+f[i-1][j])%MOD;
			if(num[i]==-1){f[i][j]=(f[i][j]+f[i-1][j+1])%MOD;continue;}
			if(num[i]>=num[t])f[i][j]=(f[i][j]+f[i-1][j])%MOD;
			if(num[i]<num[t]&&j>=1)f[i][j]=(f[i][j]+f[i-1][j-1])%MOD;
		}
		
		for(int i=0;i<=n;i++)
		ans=(ans+(num[t]*f[n][i])%MOD)%MOD;
		
	}
	printf("%I64d\n",ans);
	return 0;
}
```


---

## 作者：Exber (赞：0)

## 做法

计数 dp。

刚开始一直在想用状态记录答案之类的做法，结果看了题解才发现是数数题/kk

首先我们**定义 $opt_i$ 表示第 $i$ 个操作的类型，$x_i$ 表示第 $i$ 个操作的 $x$（如果有）**。

考虑**计算插入操作 $pos$ 对答案的贡献**。**设 $dp_{i,j}$ 表示考虑了 $[1,i]$，当前集合中比 $x_{pos}$ 小的数有 $j$ 个的子序列数**。

显然有 $dp_{0,0}=1$，接下来分情况讨论转移：

- 若 $i<pos$，那么：

1. 若 $opt_i=\texttt{-}$，那么：

	1. 对于所有满足 $j\ge 1$ 的 $j$，$dp_{i,j}=dp_{i-1,j}+dp_{i-1,j+1}$，因为不选 $i$ 的情况是 $dp_{i-1,j}$，选 $i$ 则会删除一个数，是 $dp_{i-1,j+1}$。
    
   2. $dp_{i,0}=2\cdot dp_{i-1,0}+dp_{i-1,1}$，因为选 $i$ 但没有比 $x_{pos}$ 小的数（$j=0$）时，比 $x_{pos}$ 小的数的个数并不会改变，还是 $0$。

2. 若 $opt_i=\texttt{+}$，那么:

	1. 若 $x_i<x_{pos}$，那么:
    
		1. 对于所有满足 $j\ge 1$ 的 $j$，$dp_{i,j}=dp_{i-1,j}+dp_{i-1,j-1}$，因为不选 $i$ 的情况是 $dp_{i-1,j}$，选 $i$ 则会多一个比 $x_{pos}$ 小的数，是 $dp_{i-1,j-1}$。
       
		2. $dp_{i,0}=dp_{i-1,0}$，因为 $j=0$ 时不能选 $i$。

	2. 若 $x_i\ge x_{pos}$，那么对于所有满足 $j\ge 0$ 的 $j$，$dp_{i,j}=2\cdot dp_{i-1,j}$，因为选不选 $i$ 没有影响。

- 若 $i=pos$，那么对于所有满足 $j\ge 0$ 的 $j$，$dp_{i,j}=dp_{i-1,j}$，因为必须选 $i$。

- 若 $i>pos$，那么此时我们**需要令 $dp_{i,j}$ 表示考虑了 $[1,i]$，当前集合中小于等于 $x_{pos}$ 且位置不是 $pos$ 的数有 $j$ 个的子序列数，因为重复的 $x_{pos}$ 对答案会有影响**。则有：

1. 若 $opt_i=\texttt{-}$，那么：

	1. 对于所有满足 $j\ge 1$ 的 $j$，$dp_{i,j}=dp_{i-1,j}+dp_{i-1,j+1}$，因为不选 $i$ 的情况是 $dp_{i-1,j}$，选 $i$ 则会删除一个数，是 $dp_{i-1,j+1}$。
    
   2. $dp_{i,0}=dp_{i-1,0}+dp_{i-1,1}$，因为当没有小于等于 $x_{pos}$ 的数（$j=0$）时，不能选择 $i$，因为选择的话会删掉 $x_{pos}$。

2. 若 $opt_i=\texttt{+}$，那么:

	1. 若 $x_i\le x_{pos}$，那么:
    
		1. 对于所有满足 $j\ge 1$ 的 $j$，$dp_{i,j}=dp_{i-1,j}+dp_{i-1,j-1}$，因为不选 $i$ 的情况是 $dp_{i-1,j}$，选 $i$ 则会多一个小于等于 $x_{pos}$ 的数，是 $dp_{i-1,j-1}$。
       
		2. $dp_{i,0}=dp_{i-1,0}$，因为 $j=0$ 时不能选 $i$。

	2. 若 $x_i\ge x_{pos}$，那么对于所有满足 $j\ge 0$ 的 $j$，$dp_{i,j}=2\cdot dp_{i-1,j}$，因为选不选 $i$ 没有影响。

最后插入操作 $pos$ 对答案的贡献就是 $x_{pos}\cdot \sum\limits_{j=0}^n dp_{n,j}$。

时间复杂度 $O(n^3)$，可以通过本题。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int mod=998244353;

struct node
{
	char opt;
	int x;
}a[505];

int n;
int dp[505][505];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf(" %c",&a[i].opt);
		if(a[i].opt=='+')
		{
			scanf("%d",&a[i].x);
		}
	}
	int ans=0;
	for(int pos=1;pos<=n;pos++)
	{
		if(a[pos].opt=='-')
		{
			continue;
		}
		int x=a[pos].x;
		memset(dp,0,sizeof(dp));
		dp[0][0]=1;
		for(int i=1;i<=n;i++)
		{
			if(i<pos)
			{
				if(a[i].opt=='-')
				{
					for(int j=0;j<=n;j++)
					{
						dp[i][j]=(dp[i-1][j]+dp[i-1][j+1])%mod;
					}
					dp[i][0]=(dp[i][0]+dp[i-1][0])%mod;
				}
				else if(a[i].x<x)
				{
					dp[i][0]=dp[i-1][0];
					for(int j=1;j<=n;j++)
					{
						dp[i][j]=(dp[i-1][j]+dp[i-1][j-1])%mod;
					}
				}
				else
				{
					for(int j=0;j<=n;j++)
					{
						dp[i][j]=(dp[i-1][j]+dp[i-1][j])%mod;
					}
				}
			}
			else if(i==pos)
			{
				for(int j=0;j<=n;j++)
				{
					dp[i][j]=dp[i-1][j];
				}
			}
			else
			{
				if(a[i].opt=='-')
				{
					for(int j=0;j<n;j++)
					{
						dp[i][j]=(dp[i-1][j]+dp[i-1][j+1])%mod;
					}
				}
				else if(a[i].x<=x)
				{
					dp[i][0]=dp[i-1][0];
					for(int j=1;j<=n;j++)
					{
						dp[i][j]=(dp[i-1][j]+dp[i-1][j-1])%mod;
					}
				}
				else
				{
					for(int j=0;j<=n;j++)
					{
						dp[i][j]=(dp[i-1][j]+dp[i-1][j])%mod;
					}
				}
			}
		}
		for(int i=0;i<=n;i++)
		{
			ans=(ans+1ll*x*dp[n][i])%mod;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Tritons (赞：0)

题目本质上是在求对于每一个 $+x$ 对哪些子序列会有贡献，然后求和统计(因为子序列有 $2^n$ 个)。

这显然是一道DP题，假定找到了处于位置 $t$ 的一个 $+x$ ，设 $dp_{i,j}$ 表示到第 $i$ 位为止，集合 $T$ 中有 $j$ 个数 $\leq x$ 的方案数，操作序列是 $a$ 数组。我们的目的是要让我们选定的这个 $+x$ 到最后并对答案产生贡献，我们分成以下几种情况讨论:

- 当 $i < t$ 的时候

	1. 如果第 $i$ 位是 $-$ ，那么有 $dp_{i,j}=dp_{i-1,j}+dp_{i-1,j+1}$ 。特别的，当 $j=0$ 时，需要在前面式子的基础上再 $+dp_{i-1,0} $。
    
    	因为会有两种情况，一个是上一个状态中没有  $+x$ 了，读题知道这种情况是直接忽略掉 $-$ ，还有就是可能上一个状态中有 $>x$ 的数，这种就是删去了一个 $>x$ 的数，两种情况的状态都是 $dp_{i-1,j}$ ,因此要算两次。


	2. 如果第 $i$ 位是 $+x$ 并且 $x>a_t$ ，则选与不选都不会对 $j$ 产生影响， $dp_{i,j}=dp_{i-1,j}\times2$ 。
    
    3. 若 $x\geq a_t$ ，选了 $j$ 就要增加 $1$ ,否则 $j$ 不变。 
    
- 当 $i=t$ 的时候

	根据我们给的定义，这里是必选的 $dp_{i,j}=dp_{i-1,j}$ 。 
    
- 当 $i> t$ 的时候

	1. 如果第 $i$ 位是 $-$ ，则不存在 $i<t$ 时的特殊情况 ，因为这时侯 $a_t$ 已经在序列中了，再删就把 $a_t$ 给删了，所以只用算一次。
    
	2. 如果第 $i$ 位是 $+x$ ，若 $x\geq a_t$ ，则选与不选都不会对 $j$ 产生影响，$dp_{i,j}=dp_{i-1,j}\times2$ 。 
    
    3. 若 $x>a_t$ , 选了 $j$ 就要增加 $1$ , 否则 $j$ 不变。  

最后统计下答案。

$ans=\sum\limits_{t=1}^n\sum\limits_{i=1}^n dp_{n,i}\times a_t$。
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#define int long long
const int mod = 998244353, N = 505;
int n, m, dp[N][N], ans;
struct A{
	int x;
	bool plus; // 判断是哪种操作 
}a[N];
signed main() 
{
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		char ch; std::cin >> ch;
		if (ch == '+') {
			a[i].plus = true;
			scanf("%lld", &a[i].x);
		}
		else a[i].plus = false;
	}
	for (int t = 1; t <= n; t++) {
		if (a[t].plus) {	
			memset(dp, 0, sizeof(dp)); // 每一次dp都要清零 
			dp[0][0] = 1; // 初始状态 
			for (int i = 1; i < t; i++) { // i<t的情况 
				if (!a[i].plus) { // 如果第i位是- 
					for (int j = 0; j <= n; j++) 
						dp[i][j] += dp[i - 1][j + 1], dp[i][j] %= mod; // 累加选的方案
					for (int j = 0; j <= n; j++) 
						dp[i][j] += dp[i - 1][j], dp[i][j] %= mod; // 累加不选的方案 
					dp[i][0] = dp[i][0] + dp[i - 1][0]; dp[i][0] %= mod; // 特殊情况
				}
                else { // 如果第i位是+x 
                    if (a[i].x > a[t].x) // 并且x>a[t]
                        for (int j = 0; j <= n; j++) 
                            dp[i][j] += dp[i - 1][j] * 2 % mod, dp[i][j] %= mod; // 选与不选均不会对j有影响 
                    else { // 并且x>=a[t]
                        for (int j = 0; j <= n; j++)
                            dp[i][j] += dp[i - 1][j] % mod, dp[i][j] %= mod; // 不选
                        for (int j = 1; j <= n; j++) 
                            dp[i][j] += dp[i - 1][j - 1] % mod, dp[i][j] %= mod; // 选 
                    }
                }
			}
			for (int j = 0; j <= n; j++) // i=t的情况 
				dp[t][j] = dp[t - 1][j];
			for (int i = t + 1; i <= n; i++) { // i>t的情况 
				if (!a[i].plus) { // 第i位是-
					for (int j = 0; j <= n; j++) 
						dp[i][j] += dp[i - 1][j], dp[i][j] %= mod; // 不选 
					for (int j = 0; j <= n; j++) 
						dp[i][j] += dp[i - 1][j + 1], dp[i][j] %= mod; // 选 
				}
                else { // 第i位是+x
                    if (a[i].x >= a[t].x) // 如果x>=a[t]
                        for (int j = 0; j <= n; j++) 
                            dp[i][j] += dp[i - 1][j] * 2 % mod, dp[i][j] %= mod; // 同上一种情况
                    else {
                        for (int j = 0; j <= n; j++)
                            dp[i][j] += dp[i - 1][j] % mod, dp[i][j] %= mod; // 同上一种情况
                        for (int j = 1; j <= n; j++) 
                            dp[i][j] += dp[i - 1][j - 1] % mod, dp[i][j] %= mod;
                    }
                }
			}
			int tmp = 0;
			for (int i = 0; i <= n; i++)  // 计算总的贡献 
				tmp += (dp[n][i] * a[t].x) % mod, tmp %= mod;
			ans += tmp; ans %= mod;
		}
	}
	printf("%lld", ans);
    return 0;
}
```

---

## 作者：Skylmt (赞：0)

~~求管理放蒟蒻一马~~

------------

经过~~感性剖析~~，他显然是个 $dp$ 

假定我们找到了处于位置 $t$ 的一个 $+x$ 设 $dp[i][j]$ 表示到第 $i$ 位为止，集合中有 $j$ 个数 $<=x$ 的方案数。
操作序列是数组 $a$ ，我们的目的是要让我们选定的这个到最后并对答案产生贡献，我们分成以下几种情况讨论

当 $i<t$ 时

若这一位是 $-$ ,那么 $dp[i][j] = dp[i-1][j] + dp[i-1][j+1]$   如果不选，他就是上一位直接继承下来
但如果选，他就相当于删去了一个数，也就是说原来是 $j+1$

并且特别的，若 $ j=0 $ ,需要在上式的基础上再加 $ dp[i-1][0] $ 

当 $ i=t $ 时

根据我们给的定义，这里是必选的 $dp[i][j]=dp[i][j-1]$ 

当 $i>t$ 时

其实和 $i<t$ 差不多
若是 $-$ ,不存在特殊情况，因为此时我们找的那个 $x$ 已经在序列中了

若是 $+x$ 大于我们找的那个值
那么 $dp[i][j]=dp[i-1][j]*2$ 

如果小于把 $j+1$ 就行了

最后统计答案

code：
```cpp

#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
const int mod=998244353;
const int maxn=610;
struct node{
	int x;
	bool plus;//判断是哪种操作 
}a[maxn];
int dp[maxn][maxn];
signed main()
{
	cin>>n;
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		
		char ch;
		cin>>ch;
		if(ch=='+')
		{
			a[i].plus=true;
			cin>>a[i].x;
		}
		else a[i].plus=false;
	}
	for(int t=1;t<=n;t++)
	{
		if(a[t].plus)
		{	
			memset(dp,0,sizeof(dp));//每一次dp都要清零 
			int at=a[t].x;
			dp[0][0]=1;//初始状态 
			for(int i=1;i<t;i++)//i<t的情况 
			{
				if(!a[i].plus)//如果第i位是- 
				{
					for(int j=0;j<=n;j++)
					{
						dp[i][j]+=dp[i-1][j+1];//累加选的方案 
						dp[i][j]%=mod;
					}
					for(int j=0;j<=n;j++)
					{
						dp[i][j]+=dp[i-1][j];//累加不选的方案 
						dp[i][j]%=mod;
					}
					dp[i][0]=dp[i][0]+dp[i-1][0];//特殊情况
					dp[i][0]%=mod; 
/*
这是因为会有两种情况：

1. 根据题意，若没有 $+x$ ,就不管他

2. 若删去的数比 $x$ 大，也是 $dp[i-1][0]$

所以要多加一遍
*/
				}
				else//如果第i位是+x 
				{
					if(a[i].x>at)
					{
						for(int j=0;j<=n;j++)
						{
							dp[i][j]+=(dp[i-1][j]*2)%mod;//选与不选均不会对j有影响 
							dp[i][j]%=mod;
						}
					}
					else
					{
						for(int j=0;j<=n;j++)
						{
							dp[i][j]+=dp[i-1][j]%mod;//不选 
							dp[i][j]%=mod;
						}
						for(int j=1;j<=n;j++)
						{
							dp[i][j]+=dp[i-1][j-1]%mod;//选 
							dp[i][j]%=mod;
						}
					}
				}
			}
			for(int i=0;i<=n;i++)//i=t的情况 
			{
				dp[t][i]=dp[t-1][i];
			}
			for(int i=t+1;i<=n;i++)//i>t的情况 
			{
				if(!a[i].plus)
				{
					for(int j=0;j<=n;j++)
					{
						dp[i][j]+=dp[i-1][j];//不选 
						dp[i][j]%=mod;
					}
					for(int j=0;j<=n;j++)
					{
						dp[i][j]+=dp[i-1][j+1];//选 
						dp[i][j]%=mod;
					}
				}
				else
				{
					if(a[i].x>=at)
					{
						for(int j=0;j<=n;j++)
						{
							dp[i][j]+=dp[i-1][j]*2%mod;//同上一种情况 
							dp[i][j]%=mod;
						}
					}
					else
					{
						for(int j=0;j<=n;j++)
						{
							dp[i][j]+=dp[i-1][j]%mod;//同上一种情况 
							dp[i][j]%=mod;
						}
						for(int j=1;j<=n;j++)
						{
							dp[i][j]+=dp[i-1][j-1]%mod;
							dp[i][j]%=mod;
						}
					}
				}
			}
			int tmp=0;
			for(int i=0;i<=n;i++)//计算总的贡献 
			{
				tmp+=(dp[n][i]*a[t].x)%mod;
				tmp%=mod;
			}
			ans+=tmp;
			ans%=mod;
		}
		
	}
	cout<<ans;
}
```


---

