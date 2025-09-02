# ARRPRM - Prime is fun

## 题目描述

给定一个长为 $n$ 的序列 $a$，从 $a$ 中选出若干个互不相连的长度均为质数的连续段，使这些连续段中的数的和最大。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T \leq 100$，$1 \leq n \leq 2 \times 10^3$，$1 \leq a_i \leq 10^6$。

# 题解

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
这道题若使用贪心，则无法处理后效性。  
考虑动态规划做法，区间 dp 可以保证正确性，但是时间复杂度绝对爆炸。$n$ 的范围让我们想到单次询问的时间复杂度应该接近 $O(n^2)$，我们可以从这方面考虑。
## 2. 题目做法
首先，肯定得先写一个质数筛，把 $2100$ 以内的质数全筛出来，多筛一点避免出事，这里用什么筛法都可以。  
然后我们再求一个序列的前缀和，方便我们快速求序列中一段区间和。  
那么根据区间 dp 的那个思路，一个大区间的连续段最大值一定是从其间两个小区间合并而成。但对于这道题，我们可以直接递推求出 $1$ 到 $x$ 区间中的连续段最大值，枚举其中的质数长度的子区间即可，那么我们不必再将每个长度再依次枚举，时间复杂度大大缩小。  
根据上面的思路，我们只需要在求每个 $1$ 到 $x$ 区间的最大值时枚举它们的中间点即可。时间复杂度完全可以通过此题。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2110;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
		c=='-'?f=-1:1,c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x*f;
}
bool st[N];
int prime[N/7],cnt;
void ol(int x)
{
	for(int i=2;i<=x;i++)
	{
		if(!st[i])
			prime[++cnt]=i;
		for(int j=1;prime[j]<=x/i;j++)
		{
			st[prime[j]*i]=1;
			if(!(i%prime[j]))
				break;
		}
	}
}
int T,n;
int a[N],s[N];
int f[N];
int main()
{
	T=read();
	ol(2100);
	while(T--)
	{
		n=read();
		for(int i=1;i<=n;i++)
			a[i]=read(),s[i]=s[i-1]+a[i];
		for(int i=1;i<=n;i++)
			f[i]=0;
		for(int i=1;prime[i]<=n;i++)
			f[prime[i]]=s[i];
		for(int i=1;i<=n;i++)
		{
			f[i]=max(f[i],f[i-1]);
			for(int j=1;prime[j]<=i;j++)
				f[i]=max(f[i],f[i-prime[j]-1]+s[i]-s[i-prime[j]]);
		}
		printf("%d\n",f[n]);
	}
	return 0;
}
```

---

## 作者：Micnation_AFO (赞：1)

前置知识：埃氏筛 + 前缀和 + 简单 dp。

yinhee 的题解好像有点复杂，所以来写一篇简单的题解。

令 $f_i$ 表示以 $i$ 结尾的最大答案是多少。那么若 $j \le i$ 且 $j$ 是一个质数，则 $f_{i - j - 1}$（注意不是 $f_{i - j}$，因为题目要求不能相邻）一定可以转移到 $f_i$。

所以可以得到方程：

$$
f_i =\max(f_i, f_{i - j - 1} + sum_i - sum_{i - j})
$$

可以先用埃氏筛求出 $n$ 以内的所有质数，然后每次找到一个最大的 $j$ 满足 $j \le i$，再用前缀和即可转移。

注意细节和一些边界，如记得特判 $i - j - 1 < 0$ 的情况，同时多测要清空。

代码非常好写，dp 的部分只有不到 $10$ 行。

完整代码：
```cpp
#include <iostream>
#include <cstring>

using namespace std;

const int N = 2010;

int T, n;
int a[N], sum[N]; 
int cnt, prime[N];
bool vis[N];
int f[N];

void init() {
	cnt = 0;
	memset(prime, 0, sizeof(prime));
	memset(vis, false, sizeof(vis));
	memset(f, 0, sizeof(f));
	for (int i = 2; i <= n; i++) {
		if (vis[i]) continue;
		prime[++cnt] = i;
		for (int j = i; j <= n / i; j++) vis[i * j] = true;
	}
}

void read() {
	cin >> n; memset(sum, 0, sizeof(sum));
	for (int i = 1; i <= n; i++) cin >> a[i], sum[i] = sum[i - 1] + a[i];
}

void solve() {
	for (int i = 1; i <= n; i++) {
		int num = cnt;
		while (prime[num] > i) num--;
		for (int j = prime[num]; ~num; j = prime[--num])
			f[i] = max(f[i], f[max(i - j - 1, 0)] + sum[i] - sum[i - j]);
	}
	cout << f[n] << endl;
}

int main() {
	cin >> T;
	while (T--) {
		read();
		init();
		solve();
	}
	return 0;	
}
 
 ```

---

## 作者：封禁用户 (赞：0)

解题思路： 线性筛 $+$ 动态规划 dp $+$ 前缀和。

用线筛筛出这个序列中的所有质数，我不想多说。

代码如下：

```

int prime_shai()
{
    cnt = 0;
    p[0] = p[1] = 1;
    for (register int i = 2; i < N; i++){
        if (!p[i]) prime[++cnt] = i;
        for (register int j = 1; j <= cnt && i * prime[j] < N; j++){
            p[i * prime[j]] =1;
            if (i % prime[j] == 0) break;
        }
    }
    return cnt;
} 

```
 $dp$ 是负责动态规划的数组。
 
我们可以使用动态规划来求解最大值。$dp_i$ 表示以第 $i$ 个数字结尾的数组中的不相邻数字和的最大值。

然后，我们可以选择将其加入到前面某个不相邻的数字中，或者不加入任何数字，即取前一个数字$dp_{j-1}$ 或者不相邻的元素和 $sum_j - sum_t + dp_{\max(t-1,0)}$（选择不相邻数字的最大之和）的最大值（ $t$ 是在当前位置 $j$ 的前 $t$ 个位置内选择一个不相邻的数字，并将其作为与当前位置 $j$ 相邻的数字）

动态规划:

```
	for (int i = 1; i <= t; i++)
	{
		ans = 0;//清零。 
		scanf("%d", &n);
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &a[j]);
			sum[j] = sum[j - 1] + a[j];//前缀和。 
		}
	    for (int j = 1; j <= n; j++)
		{
			dp[j] = dp[j-1];//防止发生在在当前位置的前 t 个位置内不存在满足条件的质数 t
			for (int k = 1; k <= cnt && prime[k] <= j; k++)
			{
				int t = j - prime[k];
				dp[j] = max(dp[j], sum[j] - sum[t] +dp[max(t-1,0)]);//动态规划。 
			}
		dp[j] = max(dp[j],dp[j-1]); //最大不相邻数字和。
			ans = max(ans, dp[j]);//最大答案
			}//取最大值。 
		printf("%d\n", ans);
	}
```

前缀和：如果你不知道的话，请看[这个](https://blog.csdn.net/xp_957/article/details/121549337)。

代码就是这上面代码的模板。

---

## 作者：Inui_Sana (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP30394)

解题思路：线性筛+dp

对于每一个位置，分两种情况讨论：它是一个被选中的连续段的结尾，或是不选。对于前者，枚举段长再进行状态转移即可，用前缀和维护区间和，线性筛预处理区间可能长度（即质数）。对于后者，将 $dp_i$ 和 $dp_{i-1}$ 取 $\max$ 即可。

没啥好说的，上代码：

```cpp
int n,m,ans,e[maxn],sum[maxn],pm[maxn],dp[maxn];
bool bk[maxn];
void solve(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&e[i]),sum[i]=sum[i-1]+e[i];
	ans=0;
	for(int i=2;i<=n;i++){
		dp[i]=0;
		for(int j=ub(pm+1,pm+m+1,i)-pm-1;j;j--){
			int len=pm[j];
			if(len==i)dp[i]=max(dp[i],sum[i]);
			else dp[i]=max(dp[i],dp[i-len-1]+sum[i]-sum[i-pm[j]]);
		}
		dp[i]=max(dp[i],dp[i-1]);
		ans=max(ans,dp[i]);
	}
	printf("%lld\n",ans);
}
signed main(){
	const int mxn=2e3;
	for(int i=2;i<=mxn;i++){
		if(!bk[i])pm[++m]=i;
		for(int j=1;j<=m&&pm[j]<=mxn/i;j++){
			bk[i*pm[j]]=true;
			if(i%pm[j]==0)break;
		}
	}
	int t=1;
	scanf("%lld",&t);
	while(t--)solve();
}
```

---

