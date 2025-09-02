# [ABC130E] Common Subsequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc130/tasks/abc130_e

$ 1 $ 以上 $ 10^5 $ 以下の整数から成る、長さ $ N $ の整数列 $ S $ と 長さ $ M $ の整数列 $ T $ が与えられます。

$ S $ の部分列と $ T $ の部分列の組であって、整数列として等しいような組は何通りあるでしょうか。

ただし、整数列 $ A $ の部分列とは、$ A $ の要素を $ 0 $ 個以上いくつか選んで削除し、残ったものを元の順序を保って並べた整数列を表します。

また、$ S,\ T $ それぞれの部分列は、整数列として等しい場合でも、削除した要素の添字の集合が異なる場合には異なる部分列として区別してください。

答えは非常に大きくなることがあるので、$ 10^9+7 $ で割った余りを出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ M\ \leq\ 2\ \times\ 10^3 $
- $ S $ の長さは $ N $ である
- $ T $ の長さは $ M $ である
- $ 1\ \leq\ S_i,\ T_i\ \leq\ 10^5 $
- 入力は全て整数である

### Sample Explanation 1

$ S $ の部分列としては $ (),\ (1),\ (3),\ (1,\ 3) $ が考えられます。 $ T $ の部分列としては $ (),\ (3),\ (1),\ (3,\ 1) $ が考えられます。 共に部分列が $ () $ である組は $ 1\ \times\ 1 $ 通り、共に部分列が $ (1) $ である組は $ 1\ \times\ 1 $ 通り、共に部分列が $ (3) $ である組は $ 1\ \times\ 1 $ 通り考えられるので、合計 $ 3 $ 通りの組が存在します。

### Sample Explanation 2

$ S $ の部分列としては $ (),\ (1),\ (1),\ (1,\ 1) $ が考えられます。 $ T $ の部分列としては $ (),\ (1),\ (1),\ (1,\ 1) $ が考えられます。 共に部分列が $ () $ である組は $ 1\ \times\ 1 $ 通り、共に部分列が $ (1) $ である組は $ 2\ \times\ 2 $ 通り、共に部分列が $ (1,\ 1) $ である組は $ 1\ \times\ 1 $ 通り考えられるので、合計 $ 6 $ 通りの組が存在します。 部分列において削除する要素の添字の集合が異なるものを区別することに注意してください。

### Sample Explanation 5

個数を $ 10^9+7 $ で割った余りを出力することに注意してください。

## 样例 #1

### 输入

```
2 2
1 3
3 1```

### 输出

```
3```

## 样例 #2

### 输入

```
2 2
1 1
1 1```

### 输出

```
6```

## 样例 #3

### 输入

```
4 4
3 4 5 6
3 4 5 6```

### 输出

```
16```

## 样例 #4

### 输入

```
10 9
9 6 5 7 5 9 8 5 6 7
8 6 8 5 5 7 9 9 7```

### 输出

```
191```

## 样例 #5

### 输入

```
20 20
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1```

### 输出

```
846527861```

# 题解

## 作者：HanPi (赞：12)

**[AT4729 [ABC130E] Common Subsequence](https://www.luogu.com.cn/problem/AT4729)**

~~趁没什么人做这道题,水一发题解~~

f[i][j] 表示 在S的前i项 和 T的前j项 中有多少对不相同的公共子序列。

**分析**

1. $f[i - 1][j]$ , $f[i][j - 1]$ , $f[i - 1][j - 1]$ 所包含的子序列, $f[i][j]$ 都会包含.
2. $f[i - 1][j]$ 和 $f[i][j - 1]$ 都会包含 $f[i - 1][j - 1]$ 所包含的子序列,需要减去重复.

因此 $f[i][j]$ 应该等于 $f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1]$ .

3. 当 $S[i]==T[j]$ 时,相当于 $f[i - 1][j - 1]$ 中的每一个子序列都可以增加这个值,也就是说 $f[i][j]$ 会多出 $f[i - 1][j - 1]$ 个子序列.

所以 最终写成
```
// 注 : f[...][0] 和 f[0][...] 也要赋值1,空串也算子序列!
f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
if(a[i]==b[j])f[i][j]+=f[i-1][j-1];
```
**要注意的几点**

- 要开long long ~~(如果你直接存模后的数当我没说)~~
- 模和取余是不一样的,要用%来计算mod的话就要用这样的公式：a mod b = (a % b + b) % b；

**代码:**
```c
// AT4729 [ABC130E] Common Subsequence
#include <stdio.h>
int n,m;
int a[2010],b[2010];
long long f[2010][2010];
#define MOD 1000000007
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)scanf("%d",&b[i]);
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			if(i==0||j==0)
			{
				f[i][j]=1;
				continue;
			}
			f[i][j]=(f[i-1][j]+f[i][j-1]-f[i-1][j-1])%MOD;
			if(a[i]==b[j])f[i][j]=(f[i][j]+f[i-1][j-1])%MOD;
		}
	}
	printf("%lld",(f[n][m]%MOD+MOD)%MOD);
	return 0;
}
```


---

## 作者：Tx_Lcy (赞：2)

## 思路
这是一个较简单的 $\verb!DP!$。

我们设状态 $f_{i,j}$ 为 $S$ 序列前 $i$ 个数和 $T$ 序列前 $j$ 个数所能组成的相同子序列种数。

边界条件 $f_{0,i}=f_{j,0}=1\ \ (0 \le i \le len_T,0 \le j \le len_S)$。

状态转移方程也非常简单，我们只要直接容斥一下即可，$f_{i,j}=f_{i-1,j}+f_{i,j-1}-f_{i-1,j-1}$。

这里需要注意，如果 $s_i=t_j$，他们可以组成一对相同子序列，所以 $f_{i,j}$ 还要加上 $f_{i-1,j-1}$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
int const N=2e3+10;
int f[N][N],a[N],b[N];
int const mod=1e9+7;
signed main(){
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    for (rint i=1;i<=n;++i) cin>>a[i],f[i][0]=1;
    for (rint i=1;i<=m;++i) cin>>b[i],f[0][i]=1;
    f[0][0]=1;
    for (rint i=1;i<=n;++i)
        for (rint j=1;j<=m;++j){
            f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
            if (a[i]==b[j]) f[i][j]+=f[i-1][j-1];
            f[i][j]%=mod;f[i][j]+=mod,f[i][j]%=mod;
        }
    cout<<f[n][m]<<'\n';
    return 0;
}

```


---

## 作者：bigsmart21 (赞：2)

# 题解


[题目传送门](https://www.luogu.com.cn/problem/AT_abc130_e)


## 题目大意

给定两个长度为 $N$ 和 $M$ 的整数序列 $S$ 和 $T$，求两个序列中公共子序列的个数。

## 题目分析

这是一道经典 DP 求公共子序列的题目。

~~学过 DP 的都知道:~~

求公共子序列，$dp_{i,j}$ 和 $dp_{i-1,j}$，$dp_{i,j-1}$，$dp_{i-1,j-1}$ 有联系。

题目要求统计公共子序列个数（包括空串），所以我们可以基本归纳为：

* $dp_{i,j} = dp_{i-1,j} + dp_{i,j-1}$

**But**

若 $s_i \neq t_i$，重复计算了 $dp_{i-1,j-1}$，根据容斥原理，需要排除。

最终得到这题的状态转移方程：
* 若 $s_i = t_i$ ，$dp_{i,j} = dp_{i-1,j} + dp_{i,j-1}$
* 否则 $dp_{i,j} = dp_{i-1,j} + dp_{i,j-1} - dp_{i-1,j-1}$


还要记得取模，不然会爆。

##  代码
```cpp
#include<iostream>
using namespace std;
int a[10010],b[10010],dp[10010][10010];
int MOD=1000000007;
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
	}
	dp[0][0]=1;
	for(int i=1;i<=n;i++)dp[i][0]=1;
	for(int j=1;j<=m;j++)dp[0][j]=1;//初始化 子串可以是空串 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i]==b[j]){
				dp[i][j]=(dp[i-1][j]+dp[i][j-1])%MOD;
			}
			else{
				dp[i][j]=(dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1])%MOD;//状态转移方程，记得取模 
			}
		}
	}
	cout<<(dp[n][m]%MOD+MOD)%MOD;//有可能出现负数 
	return 0;
} 
```

---

## 作者：bigclever (赞：1)

题意：给定两个序列，求有多少个不同的公共子序列。
## 思路：
求不同的公共子序列的个数当然是用**动态规划**啦。

定义状态：$dp_{i,j}$ 表示序列 $S$ 的前 $i$ 项和序列 $T$ 的前 $j$ 项有多少个不同的公共子序列。

状态转移方程：简单推出 $dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}$，但是如果 $s_i ≠ t_j$ 的话， $dp_{i-1,j-1}$ 会被算两次，所以还要减掉一次。最终得：

若 $s_i = t_j$，则 $dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}$。

否则  $dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}-dp_{i-1,j-1}$。

注意：在计算过程中要**边加边模**，防止溢出。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+10,inf=1e9+7;
int n,m,s[N],t[N],dp[N][N];
int main(){
    cin>>n>>m;
    for(int i=0;i<=max(n,m);i++)dp[i][0]=dp[0][i]=1;//初始化，由于空串也算，所以全部赋为1
    for(int i=1;i<=n;i++)cin>>s[i];
    for(int i=1;i<=m;i++)cin>>t[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            //状态转移方程，记得取模
            if(s[i]==t[j])dp[i][j]=(dp[i-1][j]+dp[i][j-1])%inf;
            else dp[i][j]=((dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1])%inf+inf)%inf;
    }
	cout<<dp[n][m]%inf<<endl; 
	return 0;
}
```

---

## 作者：CYZZ (赞：1)

# [Common Subsequence](https://www.luogu.com.cn/problem/AT_abc130_e)
这是一道水的很的 DP 题。
# 题意简明
题面已经说得很清楚了，这里就简单说一下子序列吧。

$A$ 的子序列是指通过从 $A$ 删除零个或多个元素而不改变顺序而获得的序列。简单点说，就是在 $A$ 中选一些元素，可以跳着选，但不能倒着选。

此题中，对于序列 $S,T$ 而言。只有 $S,T$ 的某两个子序列中的每个元素的**值**和**位置**对应相同，才称它们拥有一对相同的子序列。求 $S,T$ 中相同子序列的个数。
# 思路分析
直接开始推状态转移方程，设 $dp_{i,j}$ 为 $S_{1,i}$ 与 $T_{1,j}$ 中相同子序列的对数。显然 $dp_{i-1,j}$ 和 $dp_{i,j-1}$ 中包含的相同子序列 $dp_{i,j}$ 都包含。但是 $dp_{i-1,j}$ 和 $dp_{i,j-1}$ 都包含 $dp_{i-1,j-1}$ 中的相同子序列。所以，根据容斥原理可得：
$$dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}-dp_{i-1,j-1}$$
但是，这样就结束了吗？

我们发现，当 $S_i = T_j$ 时，$S_{1,i-1}$ 与 $T_{1,j-1}$ 中包含的相同子序列同时加上 $S_i,T_j$ 会构成 $dp_{i-1,j-1}$ 个新的相同子序列。所以，当 $S_i = T_j$ 时：
$$dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}$$
到此，方程算是推完了，最后答案为 $dp_{n,m}$。
# 注意事项
- 空集与任何序列的相同子序列数都是 $1$，所以初始化 $dp_{i,0}=1,dp_{0,j}=1,dp_{0,0}=1$。
- 最终答案要先取模再加 $1000000007$ 再取模，否则有可能出现负数答案。
# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
#define mod 1000000007
int n,m,a[2005],b[2005],dp[2005][2005];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		dp[i][0]=1;//初始值 
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&b[i]);
		dp[0][i]=1;
	}
	dp[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			dp[i][j]=(dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1])%mod;//方程 
			if(a[i]==b[j])
				dp[i][j]=(dp[i][j]+dp[i-1][j-1])%mod;//特判 
		}
	}
	printf("%d",(dp[n][m]%mod+mod)%mod);//注意取模 
	return 0;
}
```
希望本篇题解可以帮到大家！！！

---

## 作者：AbsMatt (赞：1)

## [题目传送器](https://www.luogu.com.cn/problem/AT4729)

# 分析

首先，这就是一道 DP 模板题（~~水题~~）。

$dp_{i,j}$ 也就是记录从 $S_1\sim S_i$ 与 $T_1\sim T_j$ 的子序列个数。

我们就能~~简单地~~推出：

$dp_{i,j}$ 就等于 $dp_{i-1,j}+dp_{i,j-1}$，但还会有重复的部分，所以还要减去 $dp_{i-1,j-1}$。

也就是 $dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}-dp_{i-1,j-1}$。

但如果 $S_i=T_j$： $dp_{i,j}$ 就为 $dp_{i-1,j}+dp_{i,j-1}+1$。

也就是 $dp_{i,j}=dp_{i-1,j}+dp_{i,j-1} + 1$。

最后别忘了空串也符合条件，所以结果要加 $1$，每步也要取模。

# 代码

```cpp
#include<bits/stdc++.h>// 开始了
using namespace std;
long long n,m,a[2001],b[2001],s[2001][2001];
const long long mod=1e9+7;
int main(){
    cin>>n>>m// 输入
    for(int i=1;i<=n;i++)   cin>>a[i];
    for(int i=1;i<=m;i++)   cin>>b[i];
    for(int x=1,y=1;y<=m;x++){
        if(x>n) x=1,y++;
        s[x][y]=(s[x-1][y]%mod+s[x][y-1]%mod-s[x-1][y-1]%mod+mod)%mod;//每步都要取模
        if(a[x]==b[y])  s[x][y]+=(s[x-1][y-1]%mod+1);
        s[x][y]%=mod;
    }
    cout<<(s[n][m]+1)%mod;//结果要加1
}
```


---

## 作者：让风忽悠你 (赞：1)

定义 $dp_{i,j}$ 为 $S$ 的前 $i$ 个元素和 $T$ 的前 $j$ 个元素的公共子序列数。

不难发现 $dp_{i,j}$ 只能由 $dp_{i-1,j},dp_{i,j-1},dp_{i-1,j-1}$ 转移来。

当 $S_i=T_j$ 时，$dp_{i,j}=dp_{i+1,j}+dp_{i,j+1}$。

否则 $dp_{i,j}=dp_{i+1,j}+dp_{i,j+1}-dp_{i-1,j-1}$。

```cpp
#include<cstdio>
#include<algorithm>
#define N 2005
#define mod 1000000007

using namespace std;

int n,m;
int s[N],t[N];
int dp[N][N];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&s[i]),dp[i][0]=1;
	for(int i=1;i<=m;i++)
		scanf("%d",&t[i]),dp[0][i]=1;
	dp[0][0]=1;
	// 注意初始化 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(s[i]==t[j]) dp[i][j]=(dp[i-1][j]+dp[i][j-1])%mod;
			else dp[i][j]=(dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1])%mod;
	// 状态转移 
	printf("%d",(dp[n][m]%mod+mod)%mod); // mod 
	return 0;
} 
```


---

## 作者：Coros_Trusds (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15246704.html)

## 题目大意

给出两个长度分别为 $N$ 和 $M$ 的整数序列 $\rm S$ 和 $\rm T$，它们均由 $1$ 到 $10^{5}$ (含) 之间的整数组成。

求在 $\rm S$ 子序列和 $\rm T$ 子序列中，有多少对两个子序列的内容相同。

子序列的说明:

$\rm A$ 的子序列是指通过从 $\rm A$ 删除零个或多个元素而不改变顺序而获得的序列。

对于 $\rm S$ 和 $\rm T$ 而言，如果子序列的内容相同，但是被删除元素的索引集(位置)不同，也当成两个不同的子序列。

输出答案 $\operatorname{mod}1e9+7$ 的结果。

## 题目分析

令 $dp[i][j]$ 表示在 $\rm S$ 的前 $i$ 项和 $\rm T$ 的前 $j$ 项中有多少对**相同**的公共子序列。

分析一波：

$dp[i][j]$ 当然是由 $dp[i-1][j]$、$dp[i][j-1]$ 和 $dp[i-1][j-1]$ 更新来的。

如果当前进行匹配的两个数字不相同的话，前两个显然会出现重合，于是接下来套路了，套一下容斥原理即可。

用 $S[i]$ 表示 $\rm S$ 的第 $i$ 位，$T[i]$ 表示 $\rm T$ 的第 $i$ 位。

当 $S[i]\not=T[j]$ 时，有

$$dp[i][j]=dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1]$$

否则有

$$dp[i][j]=dp[i-1][j]+d[i][j-1]$$

然后需要注意一下取模会出现负数和初始化即可。

## 代码

```cpp
//2021/9/8

//2021/9/9

#include <iostream>

#include <cstdio>

#include <string>

#define debug(c) cerr<<#c<<" = "<<c<<endl

using namespace std;

const int ma=2005;

const int mod=1e9+7;

int s[ma],t[ma];

long long dp[ma][ma];

int n,m;

int main(void)
{
	cin.tie(nullptr),cout.tie(nullptr);
	
	cin>>n>>m;
	
	dp[0][0]=1ll;//初始化
	
	for(register int i=1;i<=n;i++)
	{
		cin>>s[i];
		
		dp[i][0]=1ll;//初始化
	}
	
	for(register int i=1;i<=m;i++)
	{
		cin>>t[i];
		
		dp[0][i]=1ll;//初始化
	}
	
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=m;j++)
		{
			if(s[i]!=t[j])
			{
			    dp[i][j]=(dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1])%mod;
			}
			
			else
			{
			    dp[i][j]=(dp[i-1][j]+dp[i][j-1])%mod;
			}
		}
	}
	
	cout<<(dp[n][m]%mod+mod)%mod<<endl;
	
	return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc130_e)

一道二维线性 `dp` 题。

在 `dp` 之前，我们需要明确以下几个东西：

**状态的表示**，**状态转移方程**，**边界条件**跟**答案的表示**。

### 状态的表示

$\mathit{dp}_{i,j}$ 表示考虑序列 $S$ 的前 $i$ 个数字跟序列 $T$ 的前 $j$ 个数字有多少对两个子序列的内容相同。

### 状态转移方程

对于 $s_i$ 与 $t_j$，有以下两种情况。

$1.\space s_i=t_j$ 

那 $s_1 \thicksim s_i$ 跟 $t_1 \thicksim t_j$ 的公共子序列有包含 $s_i$ 跟 $t_j$，包含 $s_i$ 但不包含 $t_j$，不包含 $s_i$ 跟 $t_j$，不包含 $s_i$ 但包含 $t_j$ 这 $4$ 种可能。

$$\mathit{dp}_{i,j} = \mathit{dp}_{i-1,j} + \mathit{dp}_{i,j-1}$$

$2.\space s_i\ne t_j$

那 $s_1 \thicksim s_i$ 跟 $t_1 \thicksim t_j$ 的公共子序列有包含 $s_i$ 但不包含 $t_j$，不包含 $s_i$ 跟 $t_j$，不包含 $s_i$ 但包含 $t_j$ 这 $3$ 种可能。

$$\mathit{dp}_{i,j} = \mathit{dp}_{i-1,j} + \mathit{dp}_{i,j-1} - \mathit{dp}_{i-1,j-1}$$

### 边界条件

$$\mathit{dp}_{i,0}=0\;(0\le i\le n)$$

$$\mathit{dp}_{0,j}=0\space \space (\space 0\le j\le m)$$

### 答案的表示
$$\mathit{dp}_{n,m}$$

#### 最后贴上代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int n, m, s[2005], t[2005], dp[2005][2005];
signed main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0); // 优化
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= m; i++) cin >> t[i];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 or j == 0) dp[i][j] = 1; // 初始化
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i] == t[j]) dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % mod;
            else dp[i][j] = (dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1]) % mod; 
        }
        // 进行 dp
    }
    cout << (dp[n][m] % mod + mod) % mod; // 处理负数
    return 0;
}
```


---

## 作者：high_sky (赞：0)

### 思路
题目要求我们求最长公共子序列，那么这就是一个 `线性dp` 了。

我们不妨确定一个设数，如 $dp_{i,j}$ 表示在序列 $a$ 中前 $i$ 个数，与数列 $b$ 中前 $j$ 个数所组成的最长序列的长度。那就有以下 $2$ 种情况。
- 若 $a_i=b_i$，那么：$dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}$
- 若 $a_i\ne b_i$，那么：$dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}-dp_{i-1,j-1}$

你可能要问：**为什么要减去 $dp_{i-1,j-1}$ 呢？**

回答：根据容斥原理，多的部分是要减掉的

### 代码如下
```cpp
#include<iostream>
using namespace std;
int a[10010],b[10010],dp[10010][10010];
const int mod=1000000007;
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	dp[0][0]=1;
	for(int i=1;i<=n;i++)dp[i][0]=1;
	for(int j=1;j<=m;j++)dp[0][j]=1; 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i]==b[j]){
				dp[i][j]=(dp[i-1][j]+dp[i][j-1])%mod;
			}
			else{
				dp[i][j]=(dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1])%mod;
			}
		}
	}
	cout<<(dp[n][m]%mod+mod)%mod;
	return 0;
} 
```

---

## 作者：Xdl_rp (赞：0)

这题就是一道 `DP` 。

- 首先定义 $f$ 数组，$f_{i, j}$ 表示以 $a_i$ , $b_i$ 之前的有多少对两个子序列的内容相同的数量。
- 还有状态转移方程：$f_{i, j} = f_{i - 1, j} + f_{i, j - 1} - f_{i - 1, j - 1}$ ，如果 $a_i = b_i$ ，则 $f_{i, j} += f_{i - 1, j - 1}$ 最后还要 $\bmod \ 1000000007$ 。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2005],b[2005],dp[2005][2005];
int main(){
    int n,m;
    long long p=1000000007;
	cin>>n>>m;
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		dp[i][0]=1;
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
		dp[0][i]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			dp[i][j]=((dp[i-1][j]%p+dp[i][j-1]%p)%p+p-dp[i-1][j-1]%p)%p;
			if(a[i]==b[j]){
				dp[i][j]=(dp[i-1][j-1]%p+dp[i][j]%p)%p;
			}
		}
	}
	cout<<dp[n][m];
}
```


---

## 作者：Bulyly (赞：0)

### 前言
感觉很多大佬对于一些细节没有过多的阐述，为了帮助像我一样巨的人们更好的理解，我就对细节再展开赘述。
### 解析
- 首先对于数组的定义：$f[i][j]$ 表示 $S$ 的前 $i$ 项 和 $T$ 的前 $j$ 项中有多少对不相同的公共子序列。

- 关于状态转移时的容斥：首先，先考虑 $S[i]$ 不等于 $T[j]$ 时，此时所以此时的公共子序列数应该为 $f[i-1][j]+f[i][j-1]$ 的子序列个数再减去这两项中的重复部分 $f[i-1][j-1]$。接着考虑 $S[i]$ 等于 $T[j]$ 的时候，此时重合部分 $f[i-1][j-1]$ 都加上 $S[i]$ 和 $T[j]$ 时就会组成 $f[i-1][j-1]$ 个新的公共子序列所以应在 $S[i]$ 不等于 $T[j]$ 的转移式上再加上 $f[i-1][j-1]$。

- 其次关于最后输出的取模处理：应为模的数是 $10^9+7$ 会爆 int 范围所以可能会是负数应该先模在加上模数再来模。

下附代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define rs register 
using namespace std;
const int mod=1e9+7,N=11055;
int n,m;
int a[N],b[N],f[N][N];
int main()
{
	
	scanf("%d%d",&n,&m);
	for(rs int i=1;i<=n;i++)  scanf("%d",&a[i]),f[i][0]=1;
	for(rs int i=1;i<=m;i++)  scanf("%d",&b[i]),f[0][i]=1;
	f[0][0]=1;
	for(rs int i=1;i<=n;i++)
	   for(rs int j=1;j<=m;j++)
	   {
	   	 if(a[i]==b[j])  f[i][j]=(f[i-1][j]+f[i][j-1])%mod;
	   	 else  f[i][j]=(f[i-1][j]+f[i][j-1]-f[i-1][j-1])%mod;
	   }
	   
	printf("%d\n",(f[n][m]%mod+mod)%mod);
	return 0;
}
```

完结撒花~

---

## 作者：_cmh (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT4729)

一道清新的 DP 题。

## $\texttt{Description}$

给定两个序列，求两个序列中有多少对子序列相同。

**注意：子序列可以为空串！**

## $\texttt{Solution}$

我们令 $dp_{i,j}$ 为 $a$ 序列的前 $i$ 位，$b$ 序列的前 $j$ 位有多少子序列相同。

他们的子序列可以为空串，空串相等，则初始化：

$$ dp_{i,0}=dp_{0,j}=1 $$

接下来是状态，分情况讨论：

- 当 $a_i\neq b_j$ 时：

$dp_{i,j}$ 可以从 $dp_{i-1,j}$ 和 $dp_{i,j-1}$ 两个状态转移。但是注意，这两个状态共同包含 $dp_{i-1,j-1}$ 这个状态，所以应减去重复的部分，即：

$$dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}-dp_{i-1,j-1}$$

- 当 $a_i=b_j$ 时：

$dp_{i,j}$ 也可以同上进行转移，但是因为有了新的相同的子序列，所以状态中可以加上 $dp_{i-1,j-1}$（因为新的数字可以与之前的每一位进行匹配）。

综上两种情况，对状态转移方程简化，得：

$$dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}-dp_{i-1,j-1}\times(a_i\ne b_j)$$

记得对 $10^9+7$ 取模，记得开 `long long`。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N=2e3;
int a[N],b[N];
long long dp[N][N];
int main(){
	int n,m; 
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		dp[i][0]=1;
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
		dp[0][i]=1;
	}
	dp[0][0]=1;
	for(int i=1;i<=n;i++)	
		for(int j=1;j<=m;j++)
			dp[i][j]=(dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1]*(a[i]!=b[j])+mod)%mod;
	cout<<(dp[n][m]+mod)%mod;
	return 0;
}
```


---

