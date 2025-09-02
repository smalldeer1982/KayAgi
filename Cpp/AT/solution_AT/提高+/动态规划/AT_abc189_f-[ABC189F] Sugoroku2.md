# [ABC189F] Sugoroku2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc189/tasks/abc189_f

高橋君は双六で遊んでいます。

この双六には $ 0 $ から $ N $ の番号がついた $ N+1 $ 個のマスがあります。 高橋君はマス $ 0 $ からスタートし、マス $ N $ を目指します。

この双六では、$ 1 $ から $ M $ までの $ M $ 種類の目が等確率で出るルーレットを使います。 各手番で、高橋君はルーレットを回して出た目の数だけ進みます。この結果マス $ N $ に到達するか、マス $ N $ を越えて進むことになる場合、ゴールとなります。

また、いくつかのマスは「振り出しに戻る」であり、それらのマスに止まると、マス $ 0 $ まで戻されます。 そのようなマスは $ K $ 個あり、マス $ A_1,\ldots,A_K $ です。

高橋君がゴールするまでにルーレットを回す回数の期待値を答えてください。 ゴールすることが不可能な場合は、かわりに `-1` を出力してください。

## 说明/提示

### 制約

- 入力はすべて整数
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 0\ \leq\ K\ \leq\ 10 $
- $ 0\ <\ A_1\ <\ \ldots\ <\ A_K\ <\ N $

### Sample Explanation 1

$ 1 $ 回目のルーレットで $ 1 $ を出した場合は $ 2 $ 回、$ 2 $ を出した場合は $ 1 $ 回でゴールできるので、ルーレットを回す回数の期待値は $ 1.5 $ です。

### Sample Explanation 2

ルーレットで $ 1 $ を出すとマス $ 1 $ に移動しますが、このマスは「振り出しに戻る」なのでマス $ 0 $ に戻されます。 従って、$ 2 $ が出るまでルーレットを回し続け、$ 2 $ が初めて出た時点でゴールすることになります。 $ i $ 回目に初めて $ 2 $ が出る確率は $ \frac{1}{2^i} $ ですから、ルーレットを回す回数の期待値は $ \sum_{i\ =\ 1}^{\infty}\ (i\ \times\ \frac{1}{2^i})\ =\ 2 $ となります。

## 样例 #1

### 输入

```
2 2 0```

### 输出

```
1.5000```

## 样例 #2

### 输入

```
2 2 1
1```

### 输出

```
2.0000```

## 样例 #3

### 输入

```
100 6 10
11 12 13 14 15 16 17 18 19 20```

### 输出

```
-1```

## 样例 #4

### 输入

```
100000 2 2
2997 92458```

### 输出

```
201932.2222```

# 题解

## 作者：allenchoi (赞：3)

### 题意：  
有一个人想从 $0$ 号格子走到 $n$ 号格子，每次会从 $[1,m]$ 中随机选一个整数 $x$ ，往前走 $x$ 步（超过了 $n$ 就回到 $n$）。有 $k$ 个特殊的格子，如果在这些格子停下，会自动传送回 $0$ 。求期望步数。  
### 科技：  
期望 DP  
### 思路：  
设第 $i$ 个格子到第 $n$ 个格子的期望步数为 $f_i$ 。  
但是我们会发现，有些点的转移要依靠 $f_0$ ，而我们是从后往前转移的，所以有问题。  
咋搞捏？  
设 $f_i = dp1_i\times f_0+dp2_i$    
考虑转移  
若 $i$ 号格子为特殊格子，那么 $dp1_i=1,dp2_i=0$  
若 $i$ 号格子不是特殊格子：  
下一步可以走到 $i+1$ 号到 $i+m$ 号格子，所以：   
$dp1_i=\frac{1}{m}\sum_{j=i+1}^{i+m}dp1_j$   
$dp2_i=\frac{1}{m}\sum_{j=i+1}^{i+m}dp2_j$  
求和那一坨可以用后缀和。  
最后得到：  
$f_0=dp1_0\times f_0+dp2_0$  
移项得：  
$(1-dp1_0)\times f_0=dp2_0$  
$f_0=\frac{dp2_0}{1-dp1_0}$  
但是要注意，如果 $f_0$ 最后求出来小于 $1$ ，那么就是无解的情况（走到 $n$ 至少一步）  
### 代码：  
```cpp
#include <cstdio>
using namespace std;
int n,m,k,t,a[100010];
double dp1[100010],dp2[100010],h1[100010],h2[100010];
bool flag[100010];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i <= k;i++)
	{
		scanf("%d",&t);
		flag[t] = true;
	}
	dp1[n] = dp2[n] = 0;
	for(int i = n - 1;i >= 0;i--)
	{
		if(flag[i])
		{
			dp1[i] = 1;
			dp2[i] = 0;
		}
		else
		{
			dp1[i] = (h1[i + 1] - h1[i + m + 1]) * (1.0 / (m * 1.0));
			dp2[i] = (h2[i + 1] - h2[i + m + 1]) * (1.0 / (m * 1.0)) + 1;
		}
		h1[i] = h1[i + 1] + dp1[i];
		h2[i] = h2[i + 1] + dp2[i];
	}
	if(dp1[0] == 1) printf("-1\n");
	else
	{
		double ans = dp2[0] / (1.0 - dp1[0]);
		if(ans < 1) printf("-1\n");
		else printf("%.10lf\n",ans);
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

我们可以很容易写出这题的 dp 式子，令 $dp_i$ 表示从 $i$ 走到 $n$ 的期望步数，那么：

$$dp_i=\begin{cases}
0 & i\ge n\\
dp_0 & i \in A\\
\frac{\sum_{j=1}^mdp_{i+j}}{m}+1& \text{otherwise}\\
\end{cases}$$

但是由于 $dp_0$ 未知，所以不妨令 $dp_i=a_i\times dp_0+b_i$，此时我们可以很轻松地维护 $a,b$ 并得到关于 $dp_0$ 的方程：$dp_0=a_0\times dp_0+b_0$，则当 $a_0=1$ 时方程无解，输出 `-1`；否则输出 $\frac {b_0} {1-a_0}$。

注意卡精度。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ld long double
const ld eps=1e-10;
ld a[200010],b[200010];
int vis[200010];
ld ldabs(ld x)
{
	return x>0?x:-x;
}
int main()
{
	int n,m,k;
	cin>>n>>m>>k;
	while(k--)
	{
		int x;
		cin>>x;
		vis[x]=1;
	}
	ld suma=0,sumb=0;
	for(int i=n-1;~i;i--)
	{
		if(vis[i]) a[i]=1;
		else a[i]=suma/m,b[i]=sumb/m+1;
		suma+=a[i]-a[i+m];
		sumb+=b[i]-b[i+m];
	}
	if(ldabs(a[0]-1)<eps) cout<<-1;
	else cout<<fixed<<setprecision(4)<<(-b[0]/(a[0]-1));
}

---

## 作者：cosf (赞：0)

如果我们写一个朴素的方程：

$$
dp_i = \begin{cases}
1 + \frac{1}{M} \times \sum_{j=1}^Mdp_{i + j} & i \not\in A\\
dp_0 & i \in A\\
0 & i \ge N
\end{cases}
$$

显然可以通过 $O(n^3)$ 来消元。~~当然过不了。~~

不过由于我们只用求 $dp_0$，可以借助一些消元的 trick，即将所有的 $dp_i$ 表示为 $U_idp_0 + V_i$ 的形式。

对于所有的 $i \ge N$，有 $U_i = V_i = 0$。对于所有的 $i \in A$，有 $U_i = 1, V_i = 0$。对于其他的，则有：

$$
\begin{aligned}
dp_i &= 1 + \frac{1}{M}\times \sum_{j = 1}^{M}dp_{i + j}\\
&= \left(\frac{1}{M}\sum_{j=1}^MU_{i + j}\right)dp_0 + \left(1 + \frac{1}{M}\sum_{j=1}^MV_{i = j}\right)
\end{aligned}
$$

可见其也能表示为 $U_i \times dp_0 + V_i$ 的形式。递推到 $0$ 之后，如果 $U_i = 1$，则无解，否则为 $\frac{V_i}{1 - U_i}$。

注意精度问题。

[AC 记录](https://atcoder.jp/contests/abc189/submissions/59925816)

---

## 作者：封禁用户 (赞：0)

期望 dp。

使用动态规划来计算从起点到终点的期望轮数。由于涉及到回到起点的特殊情况，需要考虑两种状态：

- `dp_a[i]`：从位置 $i$ 开始，确定到达终点的期望轮数。

- `dp_b[i]`：从位置 $i$ 开始，不确定到达终点的期望轮数。

dp 状态转移方程：

1. 确定到达终点的期望轮数：\
A. 如果位置 $i$ 是回到起点的，则 `dp_a[i] = 0`。\
B. 否则，`dp_a[i] = 1 + (sum_decided / M)`，其中：
	- $1$ 代表当前一步。
	- `sum_a` 是从位置 $i + 1$ 到 $i + M$ 所有位置的 `dp_a` 之和。
	- $M$ 是骰子的最大值，表示从 $i$ 可以走到 $i + 1$ 到 $i + M$ 中的任意一个位置。

2. 不确定到达终点的期望轮数：\
A. 如果位置 $i$ 是回到起点的，则 `dp_b[i] = 1`，因为需要再走一次才能回到起点。\
B. 否则，`dp_b[i] = sum_b / M`，其中：
	- `sum_b` 是从位置 $i + 1$ 到 $i + M$ 所有位置的 `dp_b` 之和。
	- $M$ 是骰子的最大值，表示从 $i$ 可以走到 $i + 1$ 到 $i + M$ 中的任意一个位置。

如果还不理解，看注释。

```cpp
#include <stdio.h>
#include <vector>
using namespace std;

int main()
{
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    vector<bool> a(N+1, false);
    for (int i = 0; i < K; i++)
	{
        int A;
        scanf("%d", &A);
        a[A] = true;
    }
    // 检查是否可以到达终点，如果任何长度为M的区间都被“回到起点”占据，则不可能到达终点
    if (K >= M)
	{
        for (int i = 1; i + M <= N; i++)
		{
            bool ok = false;
            for (unsigned j = i; j < i + M; j++)
			{
                if (!a[j])
				{
                    ok = true;
                    break;
                }
            }
            if (!ok)
			{
                printf("-1\n");
                return 0;
            }
        }
    }
    // dp_a[i]: 从 i 开始，确定到达终点的期望轮数
    // dp_b[i]: 从 i 开始，不确定到达终点的期望轮数
    vector<double> dp_a(N+1), dp_b(N+1);
    // 终点期望轮数为0
    dp_a[N] = dp_b[N] = 0.0;
    // sum_a: 从 i 开始，确定到达终点的期望轮数之和
    // sum_b: 从 i 开始，不确定到达终点的期望轮数之和
    double sum_a = 0.0, sum_b = 0.0;
    // 逆向递推
    for (int i = N-1; i >= 0; i--)
	{
        // 从 i+1 开始的期望轮数之和
        sum_a += dp_a[i+1];
        // 如果 i + M + 1 < N，则减去 i + M + 1 开始的期望轮数之和
        // 因为从 i 开始，可能直接走到 i + M + 1，不需要经过 i+1 到 i + M 的这些位置
        if (i + M + 1 < N) sum_a -= dp_a[i + M + 1];
        sum_b += dp_b[i+1];
        if (i + M + 1 < N) sum_b -= dp_b[i + M + 1];
        // 如果 i “回到起点”
        if (a[i])
		{
            dp_a[i] = 0.0; // 从 i 开始，确定到达终点的期望轮数为0，因为会回到起点
            dp_b[i] = 1.0; // 从 i 开始，不确定到达终点的期望轮数为1，因为需要再走一次
        }
		else
		{
            // 从 i 开始，确定到达终点的期望轮数为1 + 从 i+1 开始的期望轮数之和的平均值
            dp_a[i] = 1.0 + sum_a/M;
            dp_b[i] = sum_b/M;
        }
    }
    printf("%lf\n", dp_a[0]/(1.0 - dp_b[0]));
    return 0;
}
```

---

