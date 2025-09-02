# Small Operations

## 题目描述

给你两个正整数 $x,k$。进行以下两种变换之一称为一次操作：
- 选择一个满足 $1 \le a \le k$ 的正整数 $a$，使 $x$ 变为 $x\cdot a$；
- 选择一个满足 $1 \le a \le k$ 的正整数 $a$，使 $x$ 变为 $\frac{x}{a}$，要求操作完后 $x$ 值是整数。

你需要找出使 $x$ 变为给定正整数 $y$ 的最小操作次数，或判断无解。

## 说明/提示

对于第一组测试数据，我们可以选择 $a=2$，将 $x$ 除以 $2$，然后选择 $a=3$，将 $x$ 乘上 $3$，此时 $x$ 将变为 $6$，等于 $y$。

对于第二组测试数据，可以证明其不可能。

对于第七组测试数据，我们可以分别选择 $a=7,9,10,10,12,13$，连续做 $6$ 次乘法。可以证明没有比这更少的操作次数了。

## 样例 #1

### 输入

```
8
4 6 3
4 5 3
4 6 2
10 45 3
780 23 42
11 270 23
1 982800 13
1 6 2```

### 输出

```
2
-1
-1
3
3
3
6
-1```

# 题解

## 作者：Imerance1018 (赞：4)

## Description

[传送门](https://codeforces.com/problemset/problem/2114/F)

## Solution

令 $a \gets x/ \gcd(x,y)$，$b \gets y/ \gcd(x,y)$。由于 $a \perp b$，我们要将 $a$ 不断除以它不超过 $k$ 的某个因数，一直到 $1$，然后再累乘到 $b$，显然累乘与累除等价。

尝试寻找策略，发现并没有结果。

但是，我们发现如果已知某个数的最小操作数，那么可以用它扩展到它所有不超过 $k$ 倍的倍数，即此题满足最优子结构性质，考虑 dp。

定义 $dp_i$ 为累乘到 $i$ 的最小代价，则有 $dp_{i \times j} \gets dp_i+1 [2 \le j \le k]$。

为了方便分析时间复杂度，定义 $n \gets \max(a,b)$。

刷表法单组数据时间复杂度是 $O(n \ln n)$ 的，（虽然比填表法的 $O(n \sqrt{n})$ 好）面对 $10^8$ 肯定要 T 掉。

发现不是 $n$ 的因数的状态都没有必要，那么使用记忆化搜索（填表法）剪去大量无用状态，复杂度能大大降低，单组数据为 $O(\sqrt{n})$，可以通过。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve()
{
	int x,y,k;
	cin>>x>>y>>k;
	int g=__gcd(x,y);
	x/=g;
	y/=g;
	int n=max(x,y);
	vector<int>dp(n+1,1e18);
	auto dfs=[&](auto &dfs,int u)->int
	{
//	cout<<u<<endl; 
		if(dp[u]!=1e18)return dp[u];
		if(u==1)return dp[u]=0;
		if(u<=k)return dp[u]=1;
		for(int i=2;i*i<=u&&min(i,u/i)<=k;i++)
		{
			if(u%i!=0)continue;
			if(i<=k)	
				dp[u]=min(dp[u],dfs(dfs,u/i)+1);	
			if(u/i<=k)
				dp[u]=min(dp[u],dfs(dfs,i)+1);
		}
		return dp[u];
	}; 
	dfs(dfs,x),dfs(dfs,y);
	if(dp[x]==1e18||dp[y]==1e18)cout<<"-1\n";
	else cout<<dp[x]+dp[y]<<"\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}
``````
``````

---

## 作者：封禁用户 (赞：3)

第一次场切 Div.3 F，写篇题解。

题意是给你三个数 $x,y,k$，问通过多次乘或除以一个不大于 $k$ 的正整数的操作（结果必须为整数）使 $x$ 变为 $y$ 的最小次数，如果不可能，输出 $-1$。

### 思路

首先，判断什么时候无解。很明显当 $x$ 和 $y$ 含有的大于 $k$ 的质因子的次数有不同的时候肯定无解，因为此时需要乘或除以大于 $k$ 的数才能把 $x$ 变成 $y$。否则一定有解。

考虑如何最小化操作次数。很明显先用除法把 $x$ 变成 $x$ 和 $y$ 的最大公约数再用乘法变成 $y$ 最优。如果把 $x$ 和 $y$ 都除以它们的最大公约数，那么问题就等价于求每次只能除以一个不大于 $k$ 的正整数，从 $x$ 和 $y$ 变为 $1$ 的次数和。

刚开始想的是贪心每次选最大可以做除数的数，但是会 WA 在第七组样例。考虑搜索。普通 DFS 时间复杂度肯定会上天，于是尝试记忆化搜索。

记搜板子打出来了，但是 [TLE on #6](https://codeforces.com/contest/2114/submission/321489067)。仔细想想，发现有一个剪枝，就是如果当前的数小于或等于 $k$，那就说明可以只用一次操作变成 $1$，直接返回 $1$ 即可。AC 了，最后系统测试跑了 $546$ 毫秒。

[代码 & AC 记录](https://codeforces.com/contest/2114/submission/321494248)

---

## 作者：the_Short_Path (赞：1)

## 形式化题意
给定 $x,y,k$，每次可以将 $x$ 乘或除以一个 $\le k$ 的正整数数，问需要多少次才能把 $x$ 变为 $y$，若不能则输出 $-1$。

显然当 $x$ 和 $y$ 含有的大于 $k$ 的质因子的次数不同时无解，因为此时需要乘或除以大于 $k$ 的数才能把 $x$ 变成 $y$。反之则一定有解。

用除法将 $x$ 变为 $\gcd(x,y)$，再用乘法将 $x$ 变为 $y$，这样最优。

如果将 $x$ 和 $y$ 都除以 $\gcd(x,y)$，那么就转化为了每次可以将 $x$ 除以一个 $\le k$ 的正整数数，问需要多少次才能把 $x$ 和 $y$ 变为 $1$。

记忆化搜索 + 剪枝即可通过本题。
# 正解
```cpp
#include <bits/stdc++.h>
using namespace std;
int x, y, k, dp[1000005]; // dp 为答案
int solve(int n, int k) { // 求是否有大于 k 的因子
    for (int i = 2; i * i <= n && i <= k; i++) while (n % i == 0) n /= i;
    return (n > k ? n : 1);
}
int dfs(int x) {
	if (x == 1) return 0; // 剪枝 1
	if (dp[x]) return dp[x]; // 剪枝 2
	if (x <= k) return dp[x] = 1; // 记忆化搜索
	dp[x] = 1e9;
	for (int i = k; i > 1; i--) { // 记得从大到小枚举
		if (x % i == 0) dp[x] = min(dp[x], dfs(x / i) + 1);
	}
	return dp[x];
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        memset(dp, 0, sizeof(dp)); // 多测清空
        int x, y, ans = 0;
        cin >> x >> y >> k;
        int p = solve(x, k);
        if (p != solve(y, k)) { // 特判无解
            puts("-1");
            continue;
        }
        int g = __gcd(x,y); // 优化
        x /= g, y /= g;
        cout << dfs(x) + dfs(y) << "\n";
    }
}
```

---

