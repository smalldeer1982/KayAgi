# [ARC055B] せんべい

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc055/tasks/arc055_b



# 题解

## 作者：tobie (赞：0)

直接思考最优策略有点困难。但是你发现，如果现在送来的饼**不是**前缀最大值，那么 AtCoDeer 一定不会吃它。

那如果送来的是前缀最大值呢？那你可以选择吃，也可以选择不吃。但是如果你要吃掉 $n$ 号饼，那就得保证你在送来最后一张饼后已经吃掉了全局的最大值。

所以考虑如下 dp：$dp_{i,j,0/1}$ 表示当前考虑到第 $i$ 张饼，已经吃掉了 $j$ 张饼，有没有吃掉当前的前缀最大值，在最优策略下吃掉 $n$ 号饼的概率。

然后你发现，第 $i+1$ 张饼是前 $i+1$ 张饼的前缀最大值的概率恒为 $\frac 1 {i+1}$，所以就可以列出转移式：

$$dp_{i,j,t}\leftarrow \frac 1 {i+1} \max(dp_{i+1,j+1,1},dp_{i+1,j,0})+\frac {i} {i+1} dp_{i+1,j,t}$$

直接转移即可，最后枚举第一张饼吃不吃，取个最大值就可以得到最终答案了。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1009;
double dp[N][N][2];
int n,k;
signed main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++) dp[n][i][1]=1;
	for(int i=n-1;i>=1;i--)
	for(int j=0;j<=k;j++)
	for(int t=0;t<=1;t++)
	dp[i][j][t]=1.0*(max(dp[i+1][j][0],dp[i+1][j+1][1])+1.0*i*dp[i+1][j][t])/(i+1);
	printf("%0.12lf\n",max(dp[1][1][1],dp[1][0][0]));
}
```

时间复杂度 $O(nk)$。

打个表你会发现，当 $1000\le n\le 10^5$，$k\ge 30$ 时最终答案与 $1$ 的差距会减小到 $10^{-6}$ 以下，所以对这一部分特判可以解决 $n,k\le 10^5$ 的问题。

---

