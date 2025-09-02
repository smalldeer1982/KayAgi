# [BalticOI 2000] Honeycomb Problem

## 题目描述

如下图，是一个边长为 $3$ 的蜂窝图，每个点有点权：

![](https://cdn.luogu.com.cn/upload/image_hosting/71c4lcqk.png)

现在要从上面一行的某一点到最下面的一行某一点，每次只可以到达左下角的点和右下角的点，您最多可以交换选定的一行中的两个点的数值。

求通过交换，从上面一行的某一点到最下面的一行某一点的点权之和的最大值是多少。

## 说明/提示

#### 样例说明

对于样例 $1$，交换第四行的 $5$ 和 $1$，然后我们就可以得到一条点权之和最大的路径：

$$3 \to 2 \to 8 \to 5 \to 4$$

最大值为 $22$。

#### 数据规模与约定

对于 $100\%$ 的数据，$1 \le n \le 99$，$0 \le $ 蜂窝图中的每个图 $\le 99$。

#### 说明

翻译自 [BalticOI 2000 Day1 A Honeycomb Problem](https://boi.cses.fi/files/boi2000_day1.pdf)。

## 样例 #1

### 输入

```
3
1 2 3
3 2 2 1
4 2 8 0 3
5 3 1 2
3 1 4```

### 输出

```
22```

# 题解

## 作者：卷王 (赞：11)

## 题目大意

[略。](https://www.luogu.com.cn/problem/P7266)

## 思路
这题挺难的！

观察数据范围，发现 $O(n^3)$ 最适合，于是选择暴力 dp。

设 $dp_{i,j,0/1}$ 表示当前走到了第 $i$ 行，第 $j$ 列没交换/交换数字的最大权值和。

我们发现蜂窝图的行和列都是 $2 × n - 1$，所以得开 $dp[200][200][2]$。有点烦人的是输入，但是找一下规律其实也没那么难。主要是先输入上半部分，再输入下半部分：

```cpp
for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n + i - 1; j++) {
			cin >> a[i][j];
		}
	for(int i = 1; i <= n - 1; i++)
		for(int j = 1; j <= 2 * n - i - 1; j++) {
			cin >> a[i + n][j];
		}
```

然后我们来讨论一下状态转移方程。

转移方程主要分成两种情况（为了方便，数组就不用 $\LaTeX$ 了）：

* 从第 $1$ 行到第 $n$ 行（列数递增），易得转移方程：$dp[i][j][0] = \max(dp[i-1][j][0],dp[i-1][j-1][0])+a[i][j]$，$dp[i][j][1] = \max(\max(dp[i-1][j][1],dp[i-1][j-1][1])+a[i][j]),\max(dp[i-1][j][0],dp[i-1][j-1][0])+rowmax[i])$。

* 从第 $n + 1$ 行到第 $2 × n - 1$ 行（列数递减），状态转移方程跟上面的没啥两样，建议自己想，实在想不出来看[这](https://www.luogu.com.cn/paste/kosfvxgr)。

这里面的 $rowmax_i$ 表示第 $i$ 行最大的值。我们用贪心，如果这一行要换值，那么就把值换成最大的。

最后取 $dp_{n×2-1,i,1}$ 的最大值即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, ans = 0;
int row[207];
int a[207][207];
int dp[207][207][2];
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n + i - 1; j++) {
			cin >> a[i][j];
			row[i] = max(row[i], a[i][j]);
		}
	for(int i = 1; i <= n - 1; i++)
		for(int j = 1; j <= 2 * n - i - 1; j++) {
			cin >> a[i + n][j];
			row[i + n] = max(row[i + n], a[i + n][j]);
		}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n + i - 1; j++) {
			dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j - 1][0]) + a[i][j];
			dp[i][j][1] = max(max(dp[i - 1][j][1], dp[i - 1][j - 1][1]) + a[i][j], max(dp[i - 1][j][0], dp[i - 1][j - 1][0]) + row[i]);
		}
	for(int i = 1; i <= n - 1; i++)
		for(int j = 1; j <= 2 * n - i - 1; j++) {
			int w = i + n;
			dp[w][j][0] = max(dp[w - 1][j][0], dp[w - 1][j + 1][0]) + a[w][j];
			dp[w][j][1] = max(max(dp[w - 1][j][1], dp[w - 1][j + 1][1]) + a[w][j], max(dp[w - 1][j][0], dp[w - 1][j + 1][0]) + row[w]);
		}
	for(int i = 1; i <= n; i++)
		ans = max(ans, dp[n * 2 - 1][i][1]);
	cout << ans;
	return 0;
}
```

---

## 作者：一只书虫仔 (赞：6)

#### Description

> 给定一个边长为 $n$ 的蜂窝图，求一条路径使得和最大。      
> 可以选择任意一行的两个数交换。         
> $1 \le n \le 99$，$0 \le $ 蜂窝图的每个数 $\le 99$

#### Solution

类似过河卒的暴力 dp，只不过套了一层可以交换和蜂窝图的衣服，本质一样。

首先一个很简单的结论，如果要交换，那么一定选择这一行的最大数进行交换。

定义到第 $i$ 行第 $j$ 列的最大和为 $dp[i][j]$，因为有交换和不交换，因此暴力升维：

- $dp[i][j][1]$ 为经过交换后到第 $i$ 行第 $j$ 列的最大值。
- $dp[i][j][0]$ 为不经过交换后到第 $i$ 行第 $j$ 列的最大值。
- $a[i][j]$ 为第 $i$ 行第 $j$ 列的数。

转移方程很容易得到：

- $dp[i][j][0]$ 从 $dp[i][j][0]$ 的左上角和右上角转移过来。
- $dp[i][j][1]$ 从 $dp[i][j][1]$ 的左上角，右上角，或者左上角，右上角的 $dp[i][j][0]$ 的值的最大值加上 $\max\{a[i][j]\}$。

但是输入有点恶心，边长为 $n$ 的蜂窝图有 $2 \times n-1$ 行，前 $n$ 行是正着的，后 $n$ 行是倒着的，前 $n$ 行和后 $n$ 行不一样，左上角和右上角的表示方式也不一样，自己模拟一下即可。

---

## 作者：Exber (赞：4)

## 做法
三维的暴力 DP。

首先考虑一下怎么存蜂窝图。其实很简单，把它拍扁在墙上就行了。原来宽度为 3 的蜂窝图
拍扁之后就长这样：
```
***
****
*****
****
***
```
拍扁了就可以用二维数组存了。

显然，要交换的话只有把当前行最大的那个数字弄过来才是最优的。那么就需要预处理一个数组 $maxn$，用 $maxn_i$ 表示第 $i$ 行最大的数字。

可以定义 $dp_{0,i,j}$ 表示走到第 $i$ 行第 $j$ 列并**没交换过数字**的最大权值和， $dp_{1,i,j}$ 表示走到第 $i$ 行第 $j$ 列并**交换过数字**的最大权值和。那么状态转移方程也很好想，上半边就是:

$dp_{0,i,j}=\max(dp_{0,i-1,j},dp_{0,i-1,j-1})+a_{i,j}$

$dp_{1,i,j}=\max(\max(dp_{1,i-1,j},dp_{1,i-1,j-1})+a_{i,j},\max(dp_{0,i-1,j},dp_{0,i-1,j-1})+maxn_i)$

下半边就是:

$dp_{0,i,j}=\max(dp_{0,i-1,j},dp_{0,i-1,j+1})+a_{i,j}$

$dp_{1,i,j}=\max(\max(dp_{1,i-1,j},dp_{1,i-1,j+1})+a_{i,j},\max(dp_{0,i-1,j},dp_{0,i-1,j+1})+maxn_i)$

其实由于每一行的状态都是由上一行转移过来的，所以 $dp$ 数组可以降维，但由于本题不卡空间这里就不降了。

最后对第 $n\times2-1$ 行取一个最大值就行了。

## AC 代码
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int n,a[205][205],maxn[205],dp[2][205][205]; // 注意空间要开两倍 

int main()
{
	scanf("%d",&n);
	// 分成上下两半读入 
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n+i-1;j++)
		{
			scanf("%d",&a[i][j]);
			maxn[i]=max(maxn[i],a[i][j]);
		}
	}
	for(int i=1;i<=n-1;i++)
	{
		for(int j=1;j<=n+n-1-i;j++)
		{
			int t=i+n;
			scanf("%d",&a[t][j]);
			maxn[t]=max(maxn[t],a[t][j]);
		}
	}
	// 分成上下两半 DP 
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n+i-1;j++)
		{
			dp[0][i][j]=max(dp[0][i-1][j],dp[0][i-1][j-1])+a[i][j];
			dp[1][i][j]=
			max(
			max(dp[1][i-1][j],dp[1][i-1][j-1])+a[i][j],
			max(dp[0][i-1][j],dp[0][i-1][j-1])+maxn[i]
			);
		}
	}
	for(int i=1;i<=n-1;i++)
	{
		for(int j=1;j<=n+n-1-i;j++)
		{
			int t=i+n;
			dp[0][t][j]=max(dp[0][t-1][j],dp[0][t-1][j+1])+a[t][j];
			dp[1][t][j]=
			max(
			max(dp[1][t-1][j],dp[1][t-1][j+1])+a[t][j],
			max(dp[0][t-1][j],dp[0][t-1][j+1])+maxn[t]
			);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,dp[1][n*2-1][i]); // 求最大值 
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：翼德天尊 (赞：1)

这是一道非常典型的 $\text{dp}$ 题目。

有几个较为不容易思考的点：

1. 如何储存蜂窝图？

2. 状态转移方程如何推？（存在一次交换数值的机会）


------------

###  先来说第一点吧，如何储存蜂窝图？

我们其实就可以考虑采用样例呈现的方式存图。用一个二维数组，第一行的下标为 $(1,1)-(1,n)$，第二行的下标为 $(2,1)-(2,n+1)$，以此类推。那么一个问题就来了，**如何在循环中表示某一行的列数呢？**

我们采用分类讨论的方式（假设行用 $i$ 表示，列用 $j$ 表示）：

1. 对于前 $n$ 行：我们会发现列数会随着行数的增大而增大，故关系式为 $j=n+i-1$。

2. 对于后 $n-2$ 行：我们会发现列数会随着行数的增大而减小，且行列之和恒为 $3\times n-1$（第 $n+i$ 行会有 $2\times n-1-i$ 列），故关系式为 $j=3\times n-i-1$。

至此，一座大山已经被我们翻过了！


------------

### 最重要的问题来了，状态转移方程怎么推？

如果先不考虑转移点的问题，那么我们可以轻松的知道，**到某个点截止的最大值一定与该点上面的两个点有关**。所以状态转移方程为——

不对，上半层图和下半层图是不一样的，上半层图点 $(i,j)$ 的上面两个点为点 $(i-1,j-1)$ 和点 $(i-1,j)$，下半层图为点 $(i-1,j)$ 和点 $(i-1,j+1)$。

所以状态转移方程为：（$t$ 数组为输入的图）

上半层：$dp_{i,j}=max\left\{dp_{i-1,j-1},dp_{i-1,j}\right\}+t_{i,j}$

下半层：$dp_{i,j}=max\left\{dp_{i-1,j},dp_{i-1,j+1}\right\}+t_{i,j}$

已经思考到这里了，那么加上转移点也就简单了——我们可以再将 $\text{dp}$ 数组加一维，表示到该点为止是否转移过点，再用一个 $\text{maxn}$ 数组记录每一行的最大值，转移方程如下。

上半层：

$$dp_{i,j,0}=max\left\{dp_{i-1,j-1,0},dp_{i-1,j,0}\right\}+t_{i,j}$$
$$dp_{i,j,1}=max\left\{max\left\{dp_{i-1,j-1,1},dp_{i-1,j,1}\right\}+t_{i,j},max\left\{dp_{i-1,j-1,0},dp_{i-1,j,0}\right\}+maxn_i\right\}$$

下半层的就以此类推啦！

最后将最后一排的 $\text{dp 1}$ 值取最大值输出就行啦（因为交换过的值肯定大于等于未交换过的）

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 205
int n,t[N][N],dp[N][N][2],maxn[N];
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c<='9'&&c>='0'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
int main(){
	n=read();
	for (int i=1;i<=n;i++){
		for (int j=1;j<n+i;j++){
			t[i][j]=read();
			maxn[i]=max(maxn[i],t[i][j]);
		}
	}
	for (int i=n+1;i<2*n;i++){
		for (int j=1;j<3*n-i;j++){
			t[i][j]=read();
			maxn[i]=max(maxn[i],t[i][j]);
		}
	}
	for (int i=1;i<=n;i++){//第一排特别处理一下
		dp[1][i][0]=t[1][i];
		dp[1][i][1]=maxn[1];
	}
	for (int i=2;i<=n;i++){
		for (int j=1;j<n+i;j++){
			dp[i][j][0]+=max(dp[i-1][j-1][0],dp[i-1][j][0])+t[i][j];
			dp[i][j][1]=max(max(dp[i-1][j-1][1],dp[i-1][j][1])+t[i][j],
							max(dp[i-1][j-1][0],dp[i-1][j][0])+maxn[i]);
		}
	}
	for (int i=n+1;i<2*n;i++){
		for (int j=1;j<3*n-i;j++){
			dp[i][j][0]+=max(dp[i-1][j][0],dp[i-1][j+1][0])+t[i][j];
			dp[i][j][1]=max(max(dp[i-1][j][1],dp[i-1][j+1][1])+t[i][j],
							max(dp[i-1][j][0],dp[i-1][j+1][0])+maxn[i]);							
		}
	}
	int ans=0;
	for (int i=1;i<=n;i++){
		ans=max(ans,dp[2*n-1][i][1]);
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Tomle (赞：0)

# P7266 题解

一眼 dp，但是可以交换位置，所以加一维。

先说循环读入，设 $len_i$ 表示第 $i$ 行的数字个数。$i \le n$ 时，$len_i= n + i - 1$；$i > n$ 时，$len_i = 3n - i - 1$。很简单，不做证明。

## 状态：

- $f_{i, j, 0}$ 表示走到了 $(i, j)$ 并且没有交换过位置时的最大值。
- $f_{i, j, 1}$ 表示走到了 $(i, j)$ 并且交换过位置时的最大值，不一定在第 $i$ 行交换了位置，也可能之前交换了位置。

## 状态转移：

首先，不同的行状态转移不一样。$i \le n$ 时 $f_{i, j}$ 由 $f_{i - 1, j}$ 和 $f_{i - 1, j - 1}$ 转移；$i > n$ 时 $f_{i, j}$ 由 $f_{i - 1, j}$ 和 $f_{i - 1, j + 1}$ 转移。

如果交换位置，一定是和这一行最大的数交换。设 $maxn_i = \max\limits_{j \le len_i}\{a_{i, j}\}$。

知道这个就好推了：

$$
f_{i, j, 0} = \begin{cases}
a_{i,j} & i = 1 \\
\max\{f_{i - 1, j, 0}, f_{i - 1, j - 1, 0}\} + a_{i,j} & i \le n \\
\max\{f_{i - 1, j, 0}, f_{i - 1, j + 1, 0}\} + a_{i, j} & i > n
\end{cases}
\\
f_{i, j, 1} = \begin{cases}
maxn_i & i = 1 \\
\max\{\max\{f_{i - 1, j, 1}, f_{i - 1, j - 1, 1}\} + a_{i, j}, \max\{f_{i - 1, j, 0}, f_{i - 1, j - 1, 0}\} + maxn_i\} & i \le n \\
\max\{\max\{f_{i - 1, j, 1}, f_{i - 1, j + 1, 1}\} + a_{i, j}, \max\{f_{i - 1, j, 0}, f_{i - 1, j + 1, 0}\} + maxn_i\} & i > n
\end{cases}
$$

code:
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, a[205][205], f[205][205][2], maxn[205];

int main() {
	memset(f, 0xc0, sizeof(f));
	memset(maxn, 0xc0, sizeof(maxn));
	cin >> n;
	for (int i = 1; i < 2 * n; i++) {
		if (i <= n) for (int j = 1; j < n + i; j++) {
			cin >> a[i][j];
			maxn[i] = max(maxn[i], a[i][j]);
		} else for (int j = 1; j < 3 * n - i; j++) {
			cin >> a[i][j];
			maxn[i] = max(maxn[i], a[i][j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		f[1][i][0] = a[1][i];
		f[1][i][1] = maxn[1];
	}
	for (int i = 2; i < 2 * n; i++) {
		int len = i <= n ? n + i - 1 : 3 * n - i - 1;
		if (i <= n) for (int j = 1; j <= len; j++) {
			f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j - 1][0]) + a[i][j];
			f[i][j][1] = max(max(f[i - 1][j][1], f[i - 1][j - 1][1]) + a[i][j], max(f[i - 1][j][0], f[i - 1][j - 1][0]) + maxn[i]);
		} else for (int j = 1; j <= len; j++) {
			f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j + 1][0]) + a[i][j];
			f[i][j][1] = max(max(f[i - 1][j][1], f[i - 1][j + 1][1]) + a[i][j], max(f[i - 1][j][0], f[i - 1][j + 1][0]) + maxn[i]);
		}
	}
	int ans = INT_MIN;
	for (int i = 1; i <= n; i++) {
		ans = max(ans, max(f[n * 2 - 1][i][0], f[n * 2 - 1][i][1]));
	}
	cout << ans;
	return 0;
}

```

---

## 作者：ztntonny (赞：0)

## 思路

本题我的第一想法是 $\mathcal{O(n^3)}$ 做法：枚举要改变的那一行，并对应的考虑最大值，最后考虑改变每一行对应的最大值。

## 解法

对于要改变的每一行：

- 遍历每一行，运用朴实的背包。
- 在遇到要改变的那一行的时候，跳过。
- 在遇到要改变的那一行的下一行的时候，考虑其上上行可能传下来的三个位置，更新答案。

最后考虑最后一行的最大值，加上对应行的最大值，更新最终答案。

最后输出即可。

PS. 我貌似输入是题解中最简短的，建议借鉴我的的（doge。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n , m , p[305][305] , f[305][305] , ans;
int main()
{
	cin >> n;
	for ( int i = 1; i < 2 * n; i++ )	for ( int j = 1; j <= 2 * n - 1 - abs( i - n ); j++ )	cin >> p[i][j];
	for ( int l = 1; l < 2 * n; l++ )
	{
		for ( int i = 0; i <= 2 * n + 2; i++ )	for ( int j = 0; j <= 2 * n - 1 - abs( i - n ) + 2; j++ )	f[i][j] = 0;
		ll pls = 0 , s = 0;
		for ( int i = 1; i <= 2 * n - 1 - abs( l - n ); i++ )	pls = max( pls , p[l][i] );
		for ( int i = 1; i <= n; i++ )
			for ( int j = 1; j <= i + n - 1; j++ )
			{
				if ( i == l )	continue;
				if ( i == l + 1 && i >= 2 )
				{
					f[i][j] = max( f[i - 2][j] , f[i - 2][j - 1] );
					if ( j - 2 >= 0 ) f[i][j] = max( f[i - 2][j - 2] , f[i][j] );
					f[i][j] += p[i][j];
					continue;
				}
				f[i][j] = max( f[i - 1][j - 1] , f[i - 1][j] );
				f[i][j] += p[i][j];
			}
		for ( int i = n + 1; i < 2 * n; i++ )
			for ( int j = 1; j <= 3 * n - i - 1; j++ )
			{
				if ( i == l )	continue;
				if ( i == l + 1 && i >= 2 )
				{
					f[i][j] = max( f[i - 2][j] , f[i - 2][j + 1] );
					if ( i > n + 1 )	f[i][j] = max( f[i - 2][j + 2] , f[i][j] );
					else	f[i][j] = max( f[i - 2][j - 1] , f[i][j] );//这里很重要，因为在n+1行处，上上行对应的本行的可传下来的位置不同于n+2行以下的
					f[i][j] += p[i][j];
					continue;
				}
				f[i][j] = max( f[i - 1][j + 1] , f[i - 1][j] );
				f[i][j] += p[i][j];
			}
		if ( l < 2 * n - 1 )	for ( int i = 1; i <= n; i++ )	s = max( s , f[2 * n - 1][i] );
		else	for ( int i = 1; i <= n; i++ )	s = max( s , f[2 * n - 2][i] );//这里虽然不影响AC，但是需要考虑当我们改变最后一行且其中含有最优解的时候，最后一行是全都是0的，需要考虑前一行
		s += pls;
		ans = max( ans , s );
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：technopolis_2085 (赞：0)

## P7266 [BalticOI 2000] Honeycomb Problem 题解

分析：

题解区里看到了很多用 $O(n^2)$ 的三维 dp 过了这道题，我给大家分享一个更易懂，复杂度为 $O(n^3)$ 的方法。

首先，我们枚举一个 $k$，表示我们交换第 $k$ 行的两个数的值。

可以理解为交换后这一行的所有数都变成了这一行的最大值。

然后再 dp 就好了。

时间复杂度 $O(n^3)$。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=220;
int a[maxn][maxn];
int dp[maxn][maxn];
int len[maxn];
int mx[maxn];

int main(){
	int n;
	scanf("%d",&n);
	
	len[0]=n-1;
	for (int i=1;i<2*n;i++){
		if (i<=n) len[i]=len[i-1]+1;
		else len[i]=len[i-1]-1;
		
		for (int j=1;j<=len[i];j++) scanf("%d",&a[i][j]),mx[i]=max(mx[i],a[i][j]);
	}
	
	int ans=0;
	for (int k=1;k<2*n;k++){
		memset(dp,0,sizeof(dp));
		for (int i=1;i<=n;i++){
			for (int j=1;j<=len[i];j++){
				if (i==k) dp[i][j]=max(dp[i-1][j],dp[i-1][j-1])+mx[i];
				else dp[i][j]=max(dp[i-1][j],dp[i-1][j-1])+a[i][j];
			}
		}
		
		for (int i=n+1;i<2*n;i++){
			for (int j=1;j<=len[i];j++){
				if (i==k) dp[i][j]=max(dp[i-1][j],dp[i-1][j+1])+mx[i];
				else dp[i][j]=max(dp[i-1][j],dp[i-1][j+1])+a[i][j]; 
			}
		}
		
		
		for (int i=1;i<=n;i++) ans=max(ans,dp[2*n-1][i]);
	}
	
	printf("%d",ans);
	return 0;
}
```


---

## 作者：_edge_ (赞：0)

个人认为这题目难度大概在 pj T2~T3 的样子。

明显有一个无后效性，也就可以考虑 DP。

对于每一个节点来讲它无非就几种可能性到达。

1. 从他左边过来。

1. 从他右边过来。

对于操作来讲，显然得到换最大值是最优的 (不过这里枚举一下应该也不会 T)。

定义状态 $f_{i,j,k}$ 表示到第 $i$ 行，第 $j$ 列，有无进行过操作产生的最大值。

上半段方程：

$k$ 的情况讨论一下就可以了。

$f_{i,j}=\max(f_{i-1,j-1},f_{i-1,j})+a_{i,j}$ 。

下半段方程：

$f_{i,j}=\max(f_{i-1,j+1},f_{i-1,j})+a_{i,j}$ 。

注意这边操作可以用在之前。

时间复杂度 $O(n^2)$。

注意这里要分上下两段讨论。

代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=205;
int n,a[INF][INF],sum[INF],f[INF][INF][3],ans;
signed main()
{
        scanf("%d",&n); int jj=n,fl=1;
        for (int i=1; i<=2*n-1; i++) {
                // cout<<jj<<"\n";
                for (int j=1; j<=jj; j++) {
                        scanf("%d",&a[i][j]);
                        sum[i]=max(sum[i],a[i][j]);
                }
                jj+=fl;
                if (jj>=2*n) jj-=2,fl=-1;
        }
        jj=n; fl=1;
        for (int i=1; i<=n; i++) {
                for (int j=1; j<=jj; j++) {
                        int xx=max(f[i-1][j][0],f[i-1][j-1][0]);
                        f[i][j][0]=xx+a[i][j];
                        int yy=max(f[i-1][j][1],f[i-1][j-1][1])+a[i][j];
                        // if (i==5 && j==3) cout<<yy<<"\n";
                        xx+=sum[i];
                        f[i][j][1]=max(xx,yy);
                        // cout<<f[i][j][0]<<" "<<f[i][j][1]<<" "<<i<<" "<<j<<"\n";
                }
                jj+=fl;
                if (jj>=2*n) jj-=2,fl=-1;
        }
        for (int i=n+1; i<=2*n-1; i++) {
                for (int j=1; j<=jj; j++) {
                        int xx=max(f[i-1][j][0],f[i-1][j+1][0]);
                        f[i][j][0]=xx+a[i][j];
                        int yy=max(f[i-1][j][1],f[i-1][j+1][1])+a[i][j];
                        // if (i==5 && j==3) cout<<yy<<"\n";
                        xx+=sum[i];
                        f[i][j][1]=max(xx,yy);
                        if (i==2*n-1) ans=max(ans,max(f[i][j][0],f[i][j][1]));
                        // cout<<f[i][j][0]<<" "<<f[i][j][1]<<" "<<i<<" "<<j<<"\n";
                }
                jj+=fl;
                if (jj>=2*n) jj-=2,fl=-1;
        }
        cout<<ans<<"\n";
        return 0;
}

```

这题目还可以用滚动数组将空间压成 $O(n)$。

~~然后可以愉快地卡空间了！~~

数据范围可以出到 $n \le 2000$。

目前我尽力只能做到这里。

**谢谢**



---

## 作者：Error_Eric (赞：0)

### 前言

首A!

### 正文

建议看[这道题](https://www.luogu.com.cn/problem/P1004)学习什么是动态规划。

这道题是动态规划水题，然后我用了三分钟A了它。

首先，根据小学目视法可知，第 $i$ 行有 $2n-|i-n|-1$ 个数字。

其次，根据小学目视法可知，对于一个蜂窝 $a_{i,j}$：如果 $i\le n$,那么这个蜂窝的左上角和右上角分别是 $a_{i-1,j}$ 和 $a_{i-1,j-1}$ 不然，则是 $a_{i-1,j+1}$ 和 $a_{i-1,j}$ 。

在其次，根据小学目视法可知，如果进行交换，一定是将这一行最大的那个数交换过来。

我们令 $m_i$ 表示第 $i$ 行蜂窝最大值。

我们令 $f_{i,j}$ 表示没有进行交换，到达这个蜂窝时可以获得的总和的最大值。

我们令 $g_{i,j}$ 表示有进行交换，到达这个蜂窝时可以获得的总和的最大值。

转移方程显然：

$ f_{i,j}=\max(f_{\texttt{左上角}}+a_{\texttt{左上角}},f_{\texttt{右上角}}+a_{\texttt{右上角}}) $ 。
分别对应左上角转移来，右上角转移来两种决策。

$g_{i,j}=\max(\max(f_{\texttt{左上角}},f_{\texttt{右上角}})+m_i,g_{\texttt{左上角}}+a_{\texttt{左上角}},g_{\texttt{右上角}}+a_{\texttt{右上角}})$

代码显然:

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
#define l (n+n-abs(i-n)-1)
const int size=99*2-1+5;
const int inf=1000000;
int n,ans=-inf;
int a[size][size],f[size][size],g[size][size],m[size];
int main(){
	scanf("%d",&n);
	for(int i=0;i<=2*n-1;i++)
		for(int j=0;j<=2*n-1;j++)
			a[i][j]=f[i][j]=g[i][j]=-inf;
	for(int j=1;j<=2*n-1;j++)a[0][j]=f[0][j]=g[0][j]=0;
	for(int i=1;i<=2*n-1;i++)
		for(int j=1;j<=l;j++)
			scanf("%d",&a[i][j]),m[i]=max(a[i][j],m[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=l;j++)
			f[i][j]=max(f[i-1][j]+a[i-1][j],f[i-1][j-1]+a[i-1][j-1]),
			g[i][j]=max(max(f[i-1][j],f[i-1][j-1])+m[i-1],max(g[i-1][j]+a[i-1][j],g[i-1][j-1]+a[i-1][j-1]));
	for(int i=n+1;i<=2*n-1;i++)
		for(int j=1;j<=l;j++)
			f[i][j]=max(f[i-1][j]+a[i-1][j],f[i-1][j+1]+a[i-1][j+1]),
			g[i][j]=max(max(f[i-1][j],f[i-1][j+1])+m[i-1],max(g[i-1][j]+a[i-1][j],g[i-1][j+1]+a[i-1][j+1]));
	for(int j=1;j<=2*n-1;j++)
		ans=max(ans,max(f[2*n-1][j],g[2*n-1][j])+a[2*n-1][j]);
	return printf("%d\n",ans),0;
}
```

时空复杂度 $\Theta(n^2)$，绰绰有余。

当然这道题可以用滚动数组卡空间，有兴趣的人可以思考一下。

---

