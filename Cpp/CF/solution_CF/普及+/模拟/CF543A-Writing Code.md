# Writing Code

## 题目描述

有 $n$ 个程序员，每个程序员都可以写任意行代码，总共要编写 $m$ 行代码，这 $m$ 行代码可以由多个程序员来编写。但是第 $i$ 个程序员在一行代码中会出现 $a_i$ 个 bug。现在希望知道有多少种方案能使得这 $m$ 行代码中的 bug 的数量不超过 $b$ 个。  
两个方案不同当且仅当某个程序员编写的代码量（行数）不同。

## 说明/提示

$1 \le n,m \le 500,0 \le b \le 500;1 \le mod \le 10^9+7;0 \le a_i \le 500$

Translated by @Mine_King

## 样例 #1

### 输入

```
3 3 3 100
1 1 1
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3 6 5 1000000007
1 2 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3 5 6 11
1 2 1
```

### 输出

```
0
```

# 题解

## 作者：打表大蒟蒻 (赞：12)

做完题后，照例看了一下题解，感觉讲的都不是太清楚，我来补一发。


------------
这是一道二维费用背包+完全背包求方案数的题，我们为了解题方便，将它翻译成背包问题的语言：

现在有一个体积为$b$的背包，有$n$个物品，第$i$个物品的体积为$a_i$，个数有无限个。要求在这$n$个物品中取恰好$m$个物品，且背包能装下的方案有多少种，答案模上$mod$。

1.**设计状态**：分析题目，很显然有两个限制，那就是二维费用背包，得用至少两个维度表示花费。但这题又是一个完全背包，所以可以设计一个三维dp，$dp[i][j][t]$表示目前枚举到第$i$个物品，取恰好$j$个物品，此时取到的总体积为$t$的方案数。

2.**状态转移**：这道题的状态转移方程很好推，就是完全背包的状态转移加上二维费用背包的状态转移：
$dp[i][j][t] = dp[i][j][t] + dp[i][j - 1][t - a[i]]$。

这样转移的空间复杂度和时间复杂度都是$O(nmb)$,

3.**状态压缩**：这道题的状态设计成三维的明显较大，容易被hack掉，所以我们要考虑如何降低空间复杂度。我们可以从完全背包的降维~~打击~~方法中寻求思路：对于目前查找到的$i$来说，$dp[i-1][j][t]$就等同于目前尚未更新的$dp[j][t]$，所以可以状态压缩。

4.上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e2 + 50;
int n, m, b, mod, a[maxn], dp[maxn][maxn], ans = 0;
int main () {
	cin >> n >> m >> b >> mod;
	for(int i = 1; i <= n; i++)
		cin >> a[i];   //标准读入 
	
	dp[0][0] = 1; //初始化数组，避免永远输出0
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			for(int t = a[i]; t <= b; t++) {
				dp[j][t] = (dp[j][t] + dp[j - 1][t - a[i]]) % mod;  //状态转移
			}
		}
	}
	
	for(int i = 0; i <= b; i++)
		ans = (dp[m][i] + ans) % mod;   //取最大值
	cout << ans << '\n';
	return 0;
}
```


---

## 作者：MeowScore (赞：8)

## 题意
已经挺明确了，应该能看出是个完全背包求方案数问题。那我们把它说得更像背包一些，但得把程序猿们降格成“物品”了。

改编：已知有 $n$ 个物品，其中第 $i$ 个物品的体积为 $a_{i}$ ，从中选取恰好 $m$ 个物品，使其总体积不超过 $b$ ，求方案总数。


------------
## 解决方案
完全背包求方案数，我们设 $f_{i,j,k}$ 是前 $i$ 个物品，选取了 $j$ 个，体积恰好为 $k$ 的方案数，转移方程如下:

$$f_{i,j,k}=\sum_{p=0}^{\frac{k}{a_i}}f_{i-1,j-p,k-a_i \times p}$$ 

贴一下代码，由于会超空间，数组没开大（感觉四重循环麻烦了，欢迎大佬指正！）

```
#include<bits/stdc++.h>
using namespace std;
int  v[210];
int f[210][210][210];
int main(){
	int n,m,b,Mod;
	cin>>n>>m>>b;
	cin>>Mod;
	for(int i=1;i<=n;i++)
		cin>>v[i];
	for(int i=0;i<=n;i++)
		f[i][0][0]=1;
	for(int i=1;i<=n;i++)//物品
		for(int j=1;j<=m;j++)//总共选了几个
			for(int k=0;k<=b;k++)//体积
				for(int t=0;t<=max(j,k/v[i]);t++)//枚举第i个物品选几个
					f[i][j][k]=(f[i][j][k]+f[i-1][j-t][k-v[i]*t])%Mod;
	int ans=0;
	for(int i=0;i<=b;i++)
		ans=(ans+f[n][m][i])%Mod;
	cout<<ans;
	return 0;
}
```

这样显然不行，需要降维~~打击~~！

还记得完全背包的那个优化吗？这次我们设 $f_{j,k}$ 为选了 $i$ 个物品， 总体积恰好为 $k$ 的方案数，数组滚动起来。如果掌握了完全背包，代码应该好理解。我们最终要求的结果是体积不超过 $b$ 的方案数。而 $f_{j,k}$ 的定义为选了 $i$ 个物品， 总体积**恰好**为 $k$ 的方案数，所以最终结果应该是 
$$\sum_{i=0}^{b}f_{m,i}$$ 


------------
## AC 代码
```
#include<bits/stdc++.h>
using namespace std;
int  v[510];
int f[510][510];
int main(){
	int n,m,b,Mod;
	cin>>n>>m>>b;
	cin>>Mod;
	for(int i=1;i<=n;i++)
		cin>>v[i];
	f[0][0]=1;
	for(int i=1;i<=n;i++)//物品
		for(int j=1;j<=m;j++)//选了几个
			for(int k=v[i];k<=b;k++)//体积
				f[j][k]=(f[j][k]+f[j-1][k-v[i]])%Mod;
	int ans=0;
	for(int i=0;i<=b;i++)
		ans=(ans+f[m][i])%Mod;
	cout<<ans;
	return 0;
}
```

~~完结撒花~~

---

## 作者：谦谦君子 (赞：4)

这不就是一个完全背包的板子吗（逃）

其实我觉得还是比叫水的，不知道怎么评到了蓝题，打顶了也就黄题吧
废话不多说（已经说了很多了）

## 题意：
#### 有n个程序，这n个程序运作产生m行代码，但是每个程序产生的BUG总和不能超过b，给出每个程序产生的代码，每行会产生ai个BUG，问在总BUG不超过b的情况下，我们有几种选择方法#### 

#### 完全背包：

```
我们令F[i,v]代表将前i种物品放入容量为v的背包中所能得到的最大价值。根据第i件物品放入的数量，可以得到如下的 状态转移函数：
F[i,v]=max{F[i−1,V−kCi]+kWi|0≤kCi≤v}
F[i,v]=max{F[i−1,V−kCi]+kWi|0≤kCi≤v}
每个物品可以放的上限为⌊v/Ci⌋⌊v/Ci⌋，为了得到F[i,v]需要遍历所有的 k ∈ (1…n) ，找出所有k值下F[ i , v ]的最大值。
伪代码如下：
    F [0..V] ←0
        for i ← 1 to N
            for v ← Ci to V
                for k ← 0 to V/Ci
                    F [i,v] ← max(F[i-1,v-kCi] + kWi)！

空间复杂度O(VN)
时间复杂度为O(VN ∑N i=1 V/Ci) 
```

## 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[501][501];
int main()
{
    int n,m,b,mod;
    cin>>n>>m>>b>>mod;
    f[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        for(int j=1;j<=m;j++)
        {
            for(int k=x;k<=b;k++)
            {
                (f[j][k]+=f[j-1][k-x])%=mod;
            }
        }
    }
    int ans=0;
    for(int i=0;i<=b;i++)
    {
        (ans+=f[m][i])%=mod;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：SIXIANG32 (赞：3)

连我这种蒟蒻都能轻松爆切的一道水题。  
闲话少说，切入正题。  

---
这道题显然是个计数类的 dp，而且这个 dp 有点类似于背包。  
背包的老套路了，$f_{i,j}$ 为当前写到了第 $i$ 行，bug 数量为 $j$ 的方案数。  
显然，这个只能由 $f_{i-1,j-a_p}$ 转移而来，也就是上一行，没有增加这么第 $p$ 号程序员所出的 bug 的方案数。  
那么状态转移方程也就出来了：  
$f_{i,j}=(f_{i,j}+f_{i-1,j-a_p})\mod Mod$  

---
可是答案让我们统计的是小于 $b$ 的方案数啊？$f_{m,b}$ 是最后一行出现 $b$ 次的方案数，不是答案，怎么办？  
很简单，从 $0$ 到 $b$ 累加 $f_{m,p}$ 的和就好了。  
还有一个问题，怎么初始化？  
初始化就是 $f_{0,0}=1$，也就是不编写不出现 bug，也是一种方案数。  

---
分析完了，上代码！  
```cpp
#include<iostream>
using namespace std;
int a[510],f[510][510];
int main()
{
	int n,m,b,mod,ans=0;
	cin>>n>>m>>b>>mod;
	for(int p=1;p<=n;p++)
		cin>>a[p];
	f[0][0]=1;//初始化
	for(int p=1;p<=n;p++)//dp
		for(int i=1;i<=m;i++)
			for(int j=a[p];j<=b;j++)
				f[i][j]=(f[i][j]+f[i-1][j-a[p]])%mod;
	for(int p=0;p<=b;p++)//统计答案
		ans=(ans+f[m][p])%mod;
	cout<<ans<<endl;
}
```

---

## 作者：周子衡 (赞：3)

思路：动态规划

设$dp[i][j][k]$表示前$i$个人写$j$行代码恰有$k$个bug的方案总数。易得

$dp[i][j][k]=\sum_{t=1}^{max(j,[\frac{k}{a[i]}])}dp[i-1][j-t][k-a[i]\times t]$

（其中$a[i]$意义见输入）

再压维即可，记得取模

代码：

```cpp
#include<cstdio>

using namespace std;

int a[501]={};
int dp[501][501]={};

int main()
{
    int n=0,m=0,b=0,mod=0;
    scanf("%d%d%d%d",&n,&m,&b,&mod);
    
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    dp[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            for(int k=a[i];k<=b;k++)
            {
                dp[j][k]=(dp[j][k]+dp[j-1][k-a[i]])%mod;
            }
        }
    }
    
    int ans=0;
    for(int i=0;i<=b;i++)
    {
        ans=(ans+dp[m][i])%mod;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：BFSDFS123 (赞：1)


比较简单的一道题，很好想，可以作为 dp 入门题

---

看到计数题，首先考虑 dp。

---

根据老套路，我们设 $dp_{i,j}$ 为在前 $i$ 行中出现了 $j$ 个 bug 的方案数。

然后我们运用一个背包的套路。我们发现，我们可以将一个程序员视为**一类**物品，它的体积是 $a_i$，有无限个。我们要求从这 $n$ 类物品中取出 $m$ 个，且体积之和不超过背包的大小 $b$。我们要求出所有满足条件的方案数对 $mod$ 取模。

然后这就变成了完全背包的计数。

我们用上完全背包的套路，可以得出 dp 公式：

$$dp_{j,k}=\sum dp_{j-1,k-a_i}$$

其中 $i$ 枚举的是程序员的编号（即物品的编号），$j$ 枚举的是已写完的行数，$k$ 枚举的是前 $j$ 出现了多少个 bug。

然后初始值是 $dp_{0,0}=1$，即没有写代码，没有出 bug 时候的方案数是 $1$。

代码：

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define LL_inf 1145141919810
//#define int long long
#define ull unsigned long long
#define ll long long
using namespace std;
int dp[510][510];
int Ar[510];
int n,m,b,mod;
int main()
{
	scanf("%d%d%d%d",&n,&m,&b,&mod);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&Ar[i]);
	}
	dp[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			for(int k=Ar[i];k<=b;k++)
			{
				dp[j][k]=(dp[j][k]+dp[j-1][k-Ar[i]])%mod;
			}
		}
	}
	int ans=0;
	for(int j=0;j<=b;j++)
	{
		ans=(ans+dp[m][j])%mod;
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：Daniel_7216 (赞：1)

看到求方案，显然应该考虑 DP。

看到题目中的约束条件有人数限制、代码行数规定以及 bug 数量的要求，所以可以想到用 $dp_{i, j, k}$ 表示用前 $i$ 个程序员编写 $j$ 行代码，正好产生了 $k$ 个 bug 的方案数。因为一个程序员可以写多行代码，所以三个变量都要正序枚举，并且显然第一维可以优化。于是有方程：

$dp_{j,k} = \sum\limits_{i=1}^n dp_{j - 1, k-a_i}$


最后的答案就是 $\sum\limits_{i=0}^b dp_{m,i}$

相对来说，这题比较简单，其实就是一个二位费用的完全背包。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, b, mod, a[501], dp[501][501], sum;
int main(){
	scanf("%d%d%d%d", &n, &m, &b, &mod);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			for (int k = a[i]; k <= b; k++){
				dp[j][k] += dp[j - 1][k - a[i]];
				dp[j][k] %= mod;
			}
		}
	}
	for (int i = 0; i <= b; i++){
		sum = (sum + dp[m][i]) % mod;
	}
	printf("%d", sum);
	return 0;
}
```

注：一般对于求方案的问题，不选也要算一种方案，即 $dp_{0,0}=1$！

---

## 作者：windrizzle (赞：1)

### 题意
如果任务的所有书面行最多包含b错误，那么让我们将计划称为好的。你的任务是确定有多少不同的好计划。由于计划的数量可能很大，打印其余的这个数字模给定正整数模。

### 解析

比较水的背包，将每一个程序员的代码都看成是不同的物品，求总质量。不过要记得初始化。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1001;
int n,m,b,mod;
int a[N],dp[N][N];
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m>>b>>mod;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=0;i<=b;i++) dp[0][i]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=a[i];k<=b;k++)
				dp[j][k]=(dp[j][k]+dp[j-1][k-a[i]])%mod;
	cout<<dp[m][b];
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

~~这是一道比较水的dp。~~

我们可以设dp(i,j,k)表示让前i个人完成j页文本并且问题不超过k的方案数。

于是，我们很容易想出状态转移方程：

dp(i,j,k)=dp(i-1,j,k)+dp(i-1,j-1,k-ai)

因为第一个维度只需要记录上一行，所以可以滚动数组优化。

代码并不复杂，也就十几行。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
int a[N],dp[N][N];
int main()
{
	int n,m,b,mod;
	scanf("%d%d%d%d",&n,&m,&b,&mod);
	for(int i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	for(int i=0;i<=b;i++) 
		dp[0][i]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=a[i];k<=b;k++) 
				dp[j][k]=(dp[j][k]+dp[j-1][k-a[i]])%mod;
	printf("%d\n",dp[m][b]);
	return 0;
}

```

---

