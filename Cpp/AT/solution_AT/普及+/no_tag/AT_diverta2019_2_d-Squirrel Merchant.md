# Squirrel Merchant

## 题目描述

松鼠直大君有 $N$ 个橡子。一天，为了获得更多的橡子，他决定去几家贵金属交易所做几笔交易。

他计划这么做：

1. 拿着 $N$ 个橡子离开巢穴；
2. 到交易所 $A$ 做几笔交易；
3. 到交易所 $B$ 做几笔交易；
4. 再到交易所 $A$ 做几笔交易；
5. 回巢穴。

在交易所 $X$ $(X\ =\ A,\ B)$，他可以以任意顺序完成任意整数笔（可能为零）如下的交易：

- 花费 $g_{X}$ 个橡子买来 $1$ 克金；
- 花费 $1$ 克金买来 $g_{X}$ 个橡子；
- 花费 $s_{X}$ 个橡子买来 $1$ 克银；
- 花费 $1$ 克银买来 $s_{X}$ 个橡子；
- 花费 $b_{X}$ 个橡子买来 $1$ 克铜；
- 花费 $1$ 克铜买来 $b_{X}$ 个橡子。

当然，他不能在橡子不够时购买金、银或铜；也不能在金、银或铜不够时购买橡子。

请求出他最多能带多少橡子回巢穴。注意，金、银或铜即使被带回巢穴也是无意义的，因为他只是一只松鼠。

## 说明/提示

- $1\ \leq\ N\ \leq\ 5000$
- $1\ \leq\ g_{X}\ \leq\ 5000$
- $1\ \leq\ s_{X}\ \leq\ 5000$
- $1\ \leq\ b_{X}\ \leq\ 5000$
- 所有输入的值都是整数。

### 样例 #1 解释

他可以拿 $46$ 个橡子回巢穴：

- 在交易所 $A$，用 $23$ 个橡子买 $23$ 克金。{ 橡子，金，银，铜 }={ $0,23,0,0$ }
- 在交易所 $B$，用 $23$ 克金买 $46$ 个橡子。{ 橡子，金，银，铜 }={ $46,0,0,0$ }
- 在交易所 $A$，不做任何交易。{ 橡子，金，银，铜 }={ $46,0,0,0$ }

他不能得到 $47$ 个或更多橡子，因此答案是 $46$。

## 样例 #1

### 输入

```
23
1 1 1
2 1 1```

### 输出

```
46```

# 题解

## 作者：Lvlinxi2010 (赞：0)

考虑动态规划。

第一次动态规划：
1. 状态：$f_i$ 表示 $i$ 个橡子在 $B$ 交易所时能拿到的最大橡子数。
2. 转移方程 $f_i\leftarrow\max(f_i,f_{i-a_{j,l}}+a_{j,r})$
3. 初始值：$f_i\leftarrow i$

第二次将 $n$ 设为 $f_n$。
1. 状态：$dp_i$ 表示 $i$ 个橡子在 $A$ 交易所时能拿到的最大橡子数。
2. 转移方程 $dp_i \leftarrow \max(dp_i,dp_{i-a_{j,r}}+a_{j,l})$
3. 初始值：$dp_i\leftarrow i$

最后输出 $dp_n$ 即可。

注意数组至少开到 $2 × 10^7$ 大小，不然会 RE。

附代码：
```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(int i=(a);i<=(b);i++)
#define FR(i,a,b) for(int i=(a);i>=(b);i--)
#define int long long
using namespace std;
const int MAXN = 2e7 + 10;
int f[MAXN],dp[MAXN];
struct node{
	int l,r;
}a[10];
signed main(){
	int n;
	scanf("%lld",&n);
	FL(i,1,3) scanf("%lld",&a[i].l);
	FL(i,1,3) scanf("%lld",&a[i].r);
	FL(i,0,n){
		f[i]=i;
		FL(j,1,3) if(i>=a[j].l) f[i]=max(f[i],f[i-a[j].l]+a[j].r);
	}
	n=f[n];
	FL(i,0,n){
		dp[i]=i;
		FL(j,1,3) if(i>=a[j].r) dp[i]=max(dp[i],dp[i-a[j].r]+a[j].l);
	}
	printf("%lld\n",dp[n]);
	return 0;
}
```

---

## 作者：cosf (赞：0)

## [Squirrel Merchant](https://www.luogu.com.cn/problem/AT_diverta2019_2_d)

暴力可过。当然不是原始的暴力。复杂度中当作 $n, a, b$ 同阶。

显然，这道题其实就是两个一模一样的问题叠加在一起：从 $A$ 到 $B$，然后再从 $B$ 到 $A$。现在只考虑从 $A$ 到 $B$

不管它什么金银铜，假设有用的就是 $(a_1, b_1), \dots, (a_m, b_m)$。即可以通过 $a_i$ 卖出，$b_i$ 买入，$a_i \lt b_i$ 的有用的买卖。

如果 $m$ 等于 $1$，显然尽量买就行了。复杂度 $O(1)$，$n$ 变成 $O(n^2)$。

如果 $m$ 等于 $2$，枚举通过 $a_1$ 卖出了多少松果，然后和 $m=1$ 一样算 $a_2$ 即可。复杂度 $O(n)$，$n$ 变成 $O(n^2)$。

如果 $m$ 等于 $3$，就枚举 $a_1, a_2$ 就可以了。复杂度 $O(n^2)$，$n$ 变成 $O(n^2)$。

---

这样为什么是对的呢？（以下函数用法可能不太标准）

注意到，正反的 $m_1, m_2$ 的和一定 $\le 3$。假设它们的和就是 $3$。

如果 $m_1 = 0$ 或 $m_2 = 0$，则复杂度为单次的复杂度，即 $O(n^2)$，可过。

如果 $m_1 = 1$，则第一次复杂度为 $O(1)$，$n$ 变为 $n' = O(n^2)$，第二次的复杂度为 $O(n') = O(n^2)$，可过。

如果 $m_1 = 2$，则第一次复杂度为 $O(n^2)$，第二次是 $O(1)$，总的就是 $O(n^2)$，可过。

所以复杂度是正确的。

## 代码

```cpp
#include <iostream>
using namespace std;

#define int long long

int a[3];
int b[3];
int c[4];
int d[4];

int n;

signed main()
{
    cin >> n;
    for (int i = 0; i < 3; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < 3; i++)
    {
        cin >> b[i];
    }
    int up = 0; // up 表示有用的个数，即文中的 m
    for (int i = 0; i < 3; i++)
    {
        if (b[i] > a[i])
        {
            c[++up] = a[i];
            d[up] = b[i];
        }
    }
    if (up == 1)
    {
        int bs = n / c[1];
        n -= c[1] * bs;
        n += d[1] * bs;
    }
    else if (up == 2)
    {
        int rn = 0;
        for (int i = 0; i * c[1] <= n; i++)
        {
            int cn = n - c[1] * i;
            int bs = cn / c[2];
            rn = max(rn, cn - c[2] * bs + d[2] * bs + i * d[1]);
        }
        n = rn;
    }
    else if (up == 3)
    {
        int rn = 0;
        for (int i = 0; i * c[1] <= n; i++)
        {
            int cn = n - c[1] * i;
            for (int j = 0; j * c[2] <= cn; j++)
            {
                int dn = cn - c[2] * j;
                int bs = dn / c[3];
                rn = max(rn, dn - c[3] * bs + i * d[1] + j * d[2] + bs * d[3]);
            }
        }
        n = rn;
    }
    up = 0; // 反过来再做一次
    for (int i = 0; i < 3; i++)
    {
        if (b[i] < a[i])
        {
            c[++up] = b[i];
            d[up] = a[i];
        }
    }
    if (up == 1)
    {
        int bs = n / c[1];
        n -= c[1] * bs;
        n += d[1] * bs;
    }
    else if (up == 2)
    {
        int rn = 0;
        for (int i = 0; i * c[1] <= n; i++)
        {
            int cn = n - c[1] * i;
            int bs = cn / c[2];
            rn = max(rn, cn - c[2] * bs + d[2] * bs + i * d[1]);
        }
        n = rn;
    }
    else if (up == 3)
    {
        int rn = 0;
        for (int i = 0; i * c[1] <= n; i++)
        {
            int cn = n - c[1] * i;
            for (int j = 0; j * c[2] <= cn; j++)
            {
                int dn = cn - c[2] * j;
                int bs = dn / c[3];
                rn = max(rn, dn - c[3] * bs + i * d[1] + j * d[2] + bs * d[3]);
            }
        }
        n = rn;
    }
    cout << n << endl;
    return 0;
}
```

---

## 作者：Acheron_RBM (赞：0)

很明显的动态规划。

状态转移方程分两种情况讨论。

遍历数组：

- 如果 $a_{0,j} \le i$，那么 $dp_i=\max(dp_i,dp_{i-a_{0,j}}+a_{1,j})$。

将 $n$ 设为 第一次的结果 $dp_n$：

- 如果 $a_{1,j} \le i$，那么 $dp_i=\max(dp_i,dp_{i-a_{1,j}}+a_{0,j})$。

```cpp
signed main() 
{
	cin>>n;
	for(int i=0;i<2;i++) 
	{
		for(int j=0;j<3;j++) 
		{
			cin>>a[i][j];
		}
	}
	dp.assign(n+1,0);
	for(int i=0;i<=n;i++) 
	{
		dp[i]=i;
		for (int j=0;j<3;j++) 
		{
			if(i>=a[0][j]) 
			{
				dp[i]=max(dp[i],dp[i-a[0][j]]+a[1][j]);
			}
		}
	}
	n=dp[n];
	dp.assign(n+1,0);
	for(int i=0;i<=n;i++) 
	{
		dp[i]=i;
		for(int j=0;j<3;j++) 
		{
			if(i>=a[1][j]) 
			{
				dp[i]=max(dp[i],dp[i-a[1][j]]+a[0][j]);
			}
		}
	}
	cout<<dp[n];
	return 0;
}
```

---

