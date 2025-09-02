# [ABC178D] Redistribution

## 题目描述

给定整数 $ S $。请求出有几个序列，所有项都是 $ 3 $ 以上的整数，其总和是 $ S $。因为答案可能会非常大，所以请输出除以$ 1e9+7 $ 后的余数。

## 样例 #1

### 输入

```
7```

### 输出

```
3```

## 样例 #2

### 输入

```
2```

### 输出

```
0```

## 样例 #3

### 输入

```
1729```

### 输出

```
294867501```

# 题解

## 作者：Tang_poetry_syndrome (赞：4)

## [ABC178D] Redistribution
[洛谷题面](https://www.luogu.com.cn/problem/AT_abc178_d) [Atcoder题面](https://atcoder.jp/contests/abc178/tasks/abc178_d)
### 思路
一道很基础的动态规划题。
设 $dp_i$ 为总和为 $i$ 的序列数。  
因为分解为多个大于等于 $3$ 的整数，所以数列中的元素必定在 $[3,S-3]$ 的范围内，则 $dp_i=\sum\limits_{j=3}^{i-3}dp_j$，结果即为 $dp_n$。时间复杂度为 $O(S^2)$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
const int N=2e3+5,Mod=1e9+7;
int n;
ll f[N];
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=3;i<=n;i++)
	{
		f[i]=1;
		for(int j=3;j<=i-3;j++)
			f[i]=(f[i]+f[j])%Mod;
	}
	cout<<f[n]<<endl;
	return 0;
} 
```
[提交记录](https://atcoder.jp/contests/abc178/submissions/45458332)

---

## 作者：So_noSlack (赞：2)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc178_d)&[Atcoder 链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc178_d)

本篇题解为此题较**简单做法**及**较少码量**，并且码风优良，请放心阅读。

## 题目简述

给定一个正整数 $S$，问有多少个数满足以下条件：

- 序列中必须为 $\ge 3$ 的正整数。
- 序列中的和必须为 $S$。

## 思路

首先想到组合数学，本题可通过组合数学**插板法**解决。

引入：例题，求 $n$ 个苹果分为 $k$ 组的**方案数**，**每组苹果个数仅需** $\ge 1$。

那么这道题就可**转化**为：

![SonoSlack](https://cdn.luogu.com.cn/upload/image_hosting/addsiyos.png)

如图，共有 $n$ 个苹果用 $k-1$ 个**隔板**隔开 $k$ 组，即**从 $n-1$ 个空中选 $k-1$ 个空插隔板**，所以答案即为 $C_{n-1}^{k-1}$。

**注意：隔板不能重合也不能在两边，因为每组苹果个数需** $\ge 1$。

现在再来看此题，发现**每组需** $\ge 3$ 且**组数不确定**，所以需要枚举组数 $i$ 从 $1$ 到 $n/3$，并且**空格数即可插板的位置数也会发生变化**：

$$n-1 \to n-2 \times i-1$$

隔板数依然不变，是 $i-1$。所以对于此题，方案数即为 $C_{n-2 \times i-1}^{i-1}$。

接下来就需要解决组合数的计算了，因为此题的**数据范围不大**，所以就可以用**杨辉三角预处理组合数**。学过组合数的同学应该都学过，这里直接说结论：**杨辉三角的第 $n$ 行的第 $i$ 个数即为 $C_n^i$ 的值**。

预处理如下（预处理过程中也要模 $1000000007$）：

```cpp
for(int i = 0; i <= n; i ++) {
		C[i][0] = C[i][j] = 1;
		for(int j = 1; j < i; j ++) 
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
	}
```

经过以上分析及部分代码讲解，基本的**代码框架**就很清晰了，下面是**具体代码实现**：

```cpp
#include<iostream>
using namespace std;
#define MOD 1000000007

int S, C[2005][2005]; // 组合数数组
long long ans = 0; // 记录答案，可不开 long long

int main() {
	cin >> S;
	for(int i = 0; i <= S; i ++) {
		C[i][0] = C[i][j] = 1;
		for(int j = 1; j < i; j ++) 
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD; // 杨辉三角预处理组合数
	}
        // 枚举组数
	for(int i = 1; i <= S / 3; i ++) 
		ans = (ans + C[S - 2 * i - 1][i - 1]) % MOD; // 累计答案
        cout << ans << endl; // 输出答案，换行好习惯 
	return 0;
}
```

提交记录：

![提交记录](https://cdn.luogu.com.cn/upload/image_hosting/tjx6jfw1.png)

$$\text{The End!}$$

---

## 作者：AbsMatt (赞：2)

## [题目传送器](https://www.luogu.com.cn/problem/AT_abc178_d)
## [更爽的阅读体验](https://yaohaoyou.blog.luogu.org/solution-at-abc178-d)

## 题意

在 $n$ 个苹果间，插入 $i - 1$ 块板。将其分成 $i$ 组，每组的个数 $\ge 3$。学过插板法的同学们应该都知道当这个题每个个数 $\le 1$ 时就很简单了，所以我们可以把题目转化为，在 $n - 2 \times i$ 个苹果间，插入 $i - 1$ 块板，每组苹果数 $\le 1$。

现在就是一道很模板的插板法了，可以看看 [cyz2010](https://www.luogu.com.cn/user/631576) 的图自行理解。$ans=\sum^{m}_{i=1}{C_{n - i \times 2-1}^{i-1}}$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int _maojun_=1e9+7,maxn=2005;
int n,m,ans,C[maxn][maxn];
int main()
{
    scanf("%d",&n);
    m=n/3;
    for(int i=0;i<=n;i++)
    {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%_maojun_;
    }
    for(int i=1;i<=m;i++)
    {
        ans+=C[n-i*2-1][i-1];
        ans%=_maojun_;
    }
    printf("%d",ans);
}
```


---

## 作者：qinmingze (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc178_d)
## 题意

给定一个正整数 $S$，问有多少个数满足以下条件：

- 序列中**不能出现**小于 $3$ 的正整数。
- 序列中的和必须**等于**输入的 $S$。

## 思路

- 这是一道求方案数的题，因此我们需要先建一个数组，其中 $dp[i]$ 表示为序列总和为 $i$ 时的方案总数。
- 同时为保证序列中**不出现**小于 $3$ 的正整数，因此只能取 $dp[i-1]$ 和 $dp[i-3]$ 之和，所以转移方程为 $dp[i]=dp[i-1]+dp[i-3]$。

## 注意事项：

-  $dp[0]$ 的值要赋值为 $1$。
- 需要在运算过程中 $\bmod10^9+7$。
- 最后要输出回车。

# AC 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7, N = 2e3 + 10;

int dp[N];

int main(){
	int S;
	cin >> S;
	dp[0] = 1; dp[1] = 0; dp[2] = 0;
	for(int i = 3; i <= S; i++){
		dp[i] = (dp[i - 1] + dp[i - 3]) % MOD;//转移方程
	}
	cout << dp[S] << endl;//输出方案数
	return 0;
}
```

------------

### [AC记录](https://www.luogu.com.cn/record/99612781)

---

## 作者：冷却心 (赞：1)

## 题意

给定一个整数 $S$，问有多少个序列满足：

- 仅包含 大于等于 $3$ 的整数。

- 序列的所有数之和为 $S$。

## 解法

很容易想到这是一个计数 DP，设状态 $dp[i]$ 为 序列总和为 $i$ 的方法数，初始化 $dp[0] = 1$，转移方程为:

$$dp[i] = \sum_{j = 0}^{i-3}dp[j]$$

或者枚举最后一个数，最小为 $3$，最大为 $i$:

$$dp[i] = \sum_{j=3}^{i}dp[i-j]$$

最后输出 $dp[S]$ 即可。

别忘了要模 $10^9 + 7$。

时间复杂度 $O(S^2)$。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
#define Fcin\
	ios :: sync_with_stdio(0);\
	cin.tie(0); cout.tie(0)
using namespace std;
const LL MOD = 1e9 + 7;
const LL N = 2e3 + 10;
LL S, dp[N];
int main(){
    Fcin;
    cin >> S;
    dp[0] = 1;
    for (LL i = 3; i <= S; i ++){
    	for (LL j = 0; j <= i - 3; j ++){
    		dp[i] = (dp[i] + dp[j]) % MOD;
		}
	}
	cout << dp[S];
	return 0;
}
```


---

## 作者：CYZZ (赞：1)

# [Redistribution](https://www.luogu.com.cn/problem/AT_abc178_d)
用组合数中的插板法即可解决。
# 思路分析
如果序列长度固定为 $i$，并运用插板法的建模，则题目化为：

在 $n$ 个苹果间，插入 $i-1$ 块板。将其分成 $i$ 组，每组的个数 $\ge 3$。

如果我们默认每组中原本就有两个苹果，这样每组的苹果数只需 $\ge1$ 即可，题目化为：

在 $n-2\times i$ 个苹果间，插入 $i-1$ 块板，每组至少一个苹果。

![](https://cdn.luogu.com.cn/upload/image_hosting/firv7nhr.png)

在 $n-2\times i-1$ 个空中选 $i-1$ 个，方法数为 $C_{n-2\times i-1}^{i-1}$。组合数提前预处理好，序列长度 $i$ 从 $1$ 到 $n/3$ 枚举。

# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,ans,c[2005][2005],mod=1e9+7;
signed main()
{
	scanf("%lld",&n);
	m=n/3;
	for(int i=0;i<=n;i++)
	{
		c[i][0]=c[i][i]=1;
		for(int j=1;j<i;j++)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
	}
	for(int i=1;i<=m;i++)
	{
		ans=(ans+c[n-i*2-1][i-1])%mod;
	}
	printf("%lld",ans);
}
```


---

## 作者：Demons_Killer (赞：0)

# 思路：
很基础的一道动态规划。

 $f_{i}$ 表示总和为 $i$ 有几种情况，每个满足条件的 $i$ 都是一种情况，其余的情况就将与 $i$ 相差满足不超过限制的情况加起来，在按题目要求取余，就得出了我们最后的答案 $f_{n}$。
 
# code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2010,p=1e9+7;
int f[N];
int n;
signed main(){
	cin>>n;
	f[3]=1;
	for(int i=4;i<=n;i++){
		f[i]=1;
		for(int j=3;j<=i-3;j++){
			f[i]=(f[i]+f[j])%p;
		}
	}
	cout<<f[n];
	return 0;
}

```

---

## 作者：CQ_Bab (赞：0)

# 思路
我们可以用动态规划和前缀和来做，我们定义 $f_i$ 为合为 $i$ 时的方案数，那么初始化我们就可以想到对于 $i$ 等于 $3$ 时就是 $1$。

然后我们对于每一个 $f_i$ 都可以由 $3\sim i-3$ 的方案数相加因为我们只需要在原本的序列后面加上一个 $j-i$ 就行了（毕竟 $j+(i-j)$ 是等于 $i$ 的），那么就十分简单了，并且我们将 $i$ 从 $4$ 开始枚举然后 $j$ 从 $3\sim i-3$ 即可毕竟两个数都不能小于 $3$ 嘛。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define int long long
int n,f[2010];
const int mod=1e9+7;
signed main() {
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	f[3]=1;
	rep(i,4,n) {
		f[i]=1;
		rep(j,3,i-3) f[i]=(f[i]+f[j])%mod; 
	}
	cout<<f[n]<<endl;
	return false;
}
```


---

## 作者：highkj (赞：0)

# 思路
我们可以用动态规划来做，那么我们就可以定义 $f_i$ 为和为 $i$ 时的方案数，然后我们就可以想到对于每一个 $f_i$ 它都等于从 $i-3$ 到 $3$ 的方案数总和加一（因为它之前的数都能通过加上 $i-j$ 来变成它），最后输出 $f_n$ 即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define int long long
int n,f[2010];
const int mod=1e9+7;
signed main() {
	cin>>n;
	f[3]=1;
	rep(i,4,n) {
		f[i]=1;
		rep(j,3,i-3) f[i]=(f[i]+f[j])%mod;
	}
	cout<<f[n]<<endl;
	return 0;
}
```
这是蒟蒻的第一篇题解，请求审核大大通过！

---

