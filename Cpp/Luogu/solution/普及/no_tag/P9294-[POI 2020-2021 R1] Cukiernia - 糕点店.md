# [POI 2020/2021 R1] Cukiernia / 糕点店

## 题目背景

**题目译自 [XXVIII Olimpiada Informatyczna – I etap](https://sio2.mimuw.edu.pl/c/oi28-1/dashboard/) [Cukiernia](https://sio2.mimuw.edu.pl/c/oi28-1/p/cuk/)。**

## 题目描述

Bajtuś 面包店售卖蛋糕，甜甜圈和羊角面包三种食物。在面包店中，有 $n$ 个橱窗，在正常情况下，每个货架上只应该放置一种食物。但一天早上，面包店老板 Bajtazara 的儿子 Bajtuś 偷偷进入了面包店，将所有的食物摆放得乱七八糟。

面包店马上就要开门了，Bajtazara 急切地想要重新摆放食物，使得每个货架上只有一种食物（特别地，一个货架上没有食物也是允许的）。请你帮助他求出，至少需要移动多少次食物才能达成目标。

## 说明/提示

【样例解释#1】：

一种合法的移动方案如下：

1. 将一个甜甜圈从货架 $1$ 移动至货架 $3$，将一个羊角面包从货架 $1$ 移动至货架 $2$；
2. 将三个甜甜圈从货架 $2$ 移动至货架 $3$；
3. 将一个蛋糕从货架 $3$ 移动至货架 $1$，将三个羊角面包从货架 $3$ 移动至货架 $2$；

在此之后，货架 $1$ 只有蛋糕，货架 $2$ 只有羊角面包，货架 $3$ 只有甜甜圈，货架 $4$ 只有蛋糕，货架 $5$ 是空的。

【数据范围】：

所有测试点均满足：$3 \leq n \leq 3 \times 10^5$，$0 \leq d_i,p_i,r_i \leq 10^9$。

| 子任务编号 | $n \leq$        | 分值 |
| :----------: | :---------------: | :----: |
| $1$        | $10$            | $15$ |
| $2$        | $5 \times 10^3$ | $35$ |
| $3$        | $3 \times 10^5$ | $50$ |

## 样例 #1

### 输入

```
5
5 1 1
0 3 4
1 4 3
4 0 0
0 0 0```

### 输出

```
9```

## 样例 #2

### 输入

```
3
1 1 2
2 1 1
1 1 2```

### 输出

```
7```

## 样例 #3

### 输入

```
5
5 5 5
5 5 5
5 5 5
5 5 5
5 5 5```

### 输出

```
50```

# 题解

## 作者：lkjzyd20 (赞：11)

### 思路

很巧妙的 dp，~~但这题可以贪心（160 行）。~~

我们很容易思考出来一个贪心，就是把每个货架只留一个最多的面包，但是这样会出现有可能一排都没有可以放的面包。

我们可以通过上面的贪心发现，面包之间是可以互相影响的，所以考虑 dp。

定义 $f_{i,x}$ 表示前 $i$ 个货架已经整理完毕，且第 $i$ 个货架的状态为 $x$（用 $3$ 位二进制表示分别是否存放蛋糕、甜甜圈、羊角面包）。

则
+ 如果货架上有蛋糕，就移走甜甜圈和羊角面包。
+ 如果货架上有甜甜圈，就移走蛋糕和羊角面包。
+ 如果货架上有羊角面包，就移走甜甜圈和蛋糕。

### 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define per(i, r, l) for(int i = r; i >= l; -- i)
using namespace std;
const int N=300010;
int n, d[N], p[N], r[N];
int f[N][8];
int a,b,c;
main() 
{
    cin>>n;
	memset(f,0x3f,sizeof f);
    f[0][0] = 0;
    rep(i,1,n)
    {
    	cin>>d[i]>>p[i]>>r[i];
        if(d[i]) a=4;
        if(p[i]) b=2;
        if(r[i]) c=1;
    }
    rep(i,1,n)
    	rep(x,0,7)
        {
            f[i][x]=1e18;
            if(x&4) f[i][x]=min(f[i][x],min(f[i-1][x],f[i-1][x^4])+p[i]+r[i]);
            if(x&2) f[i][x]=min(f[i][x],min(f[i-1][x],f[i-1][x^2])+d[i]+r[i]);
            if(x&1) f[i][x]=min(f[i][x],min(f[i-1][x],f[i-1][x^1])+d[i]+p[i]);
        }
    cout<<f[n][a+b+c];
    return 0;
}
```

---

## 作者：honglan0301 (赞：4)

## 题目分析

容易想到贪心地把 $d_i,p_i,r_i$ 中较小的两个换掉，但这样存在问题，因为如果 $sum_d>0$，则至少要有一个店留着 $d$。

于是考虑用 dp 替代贪心，令 $f(i,0/1,0/1,0/1)$ 表示前 $i$ 家店是/否至少有一家留下了 $d_i,p_i,r_i$ 时的最小花费，最后输出 $f(n,0/1,0/1,0/1)$ 中最优合法状态的花费即可，转移简单。

## 代码

```cpp
/*
  author: PEKKA_l  
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
#define int long long

int n,a[300005],b[300005],c[300005],sa,sb,sc,dp[300005][8];

signed main()
{
	cin>>n; for(int i=1;i<=n;i++) cin>>a[i]>>b[i]>>c[i],sa+=a[i],sb+=b[i],sc+=c[i];
	for(int i=0;i<=n;i++) for(int j=0;j<=7;j++) dp[i][j]=1e18; dp[0][0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=7;j++)
		{
			if(j&1) dp[i][j]=min(dp[i][j],min(dp[i-1][j],dp[i-1][j^1])+b[i]+c[i]);
			if(j&2) dp[i][j]=min(dp[i][j],min(dp[i-1][j],dp[i-1][j^2])+a[i]+c[i]);
			if(j&4) dp[i][j]=min(dp[i][j],min(dp[i-1][j],dp[i-1][j^4])+a[i]+b[i]);
		}
	}
	sa=sa?0:1; sb=sb?0:1; sc=sc?0:1; int ans=1e18;
	for(int j=0;j<=7;j++) if((j|(sa)|(sb*2)|(sc*4))==7) ans=min(ans,dp[n][j]);
	cout<<ans<<endl;
}
```


---

## 作者：Firsry (赞：2)

# P9294 \[POI 2020] Cukiernia / 糕点店

每个货架上有多个货物，目标是通过移动让每个货架上只有一个，每一次移动可以改变一个糕点的位置。

货架上有没有某一种糕点非常重要，而这个不容易通过维护 $d,p,r$ 实现，因为上一个货架选择保留哪一种会影响到这一层要处理哪些糕点以及其个数。这个时候可以考虑用二进制的方法去处理**有或没有**的组合情况：一个二进制数的前三位分别表示是否有 $d,p,r$ 这样遍历 $[0,8)$ 就可以处理出所有可能的情况。

也就是说 $f_{i,j}$ 表示的是第 $i$ 个货架上，面对 $j$ 情况，将整理好的状态转移给下一状态的最小代价。然后思考如何转移。假设 $d,p,r$ 对应 $1,2,4$。

$j$ 的情况有些糕点可能是没有的，所以这个情况只有可能是其子情况推演过来。也就是说，如果 $i-1$ 层的状态 $j'$ 拥有 $j$ 没有的糕点并传递给了下一层 $i$，那么此时 $i$ 层的状态不可能是 $j$，所以就有如下的推导：

- 可以是上一层货架和这一层的情况是完全一致的。
- 可以是上一层货架比这一层少了某一个，其有无糕点的其情况是当前情况的子情况。

那么对于现在我有某一种（以 $1$ 为例），所以我想丢弃我现在拥有的 $2,4$，所以上一层的情况中，其他一样，仅仅是 $1$ 的存在性不同，则并不影响可行性，所以就在其中选择最优。

我们对于每一种情况都进行这样的讨论，就可以推出状态转移了，具体见代码。同时可以使用滚动数组进行空间优化。毕竟只依赖上一层，而且是交叉依赖，所以保留两层完整的数组就足够了。

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

const ll MAXN = 300005;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll n, d[MAXN], p[MAXN], r[MAXN];
ll type, f[2][8];

void in() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%lld%lld%lld", &d[i], &p[i], &r[i]);
	for (int i = 1; i <= n && type != 7; ++i) {
		if (d[i])	type |= 1;
		if (p[i])	type |= 2;
		if (r[i])	type |= 4;
	}
	return;
}
void dp() {
	for (int i = 0; i < 8; ++i)
		f[0][i] = f[1][i] = INF;
	f[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		ll cur = i % 2, pre = (i - 1) % 2, tot = d[i] + p[i] + r[i];
		for (int j = 0; j < 8; ++j) {
			f[cur][j] = INF;
			if (j & 1)
				f[cur][j] = min(f[cur][j], min(f[pre][j], f[pre][j ^ 1]) + tot - d[i]);
			if (j & 2)
				f[cur][j] = min(f[cur][j], min(f[pre][j], f[pre][j ^ 2]) + tot - p[i]);
			if (j & 4)
				f[cur][j] = min(f[cur][j], min(f[pre][j], f[pre][j ^ 4]) + tot - r[i]);
		}
	}
	return;
}

int main() {
	in();
	dp();
	cout << f[n % 2][type];
	return 0;
}
```

---

