# [USACO21FEB] Modern Art 3 G

## 题目描述

厌倦了常规的二维画作（同时也由于作品被他人抄袭而感到失落），伟大的奶牛艺术家牛加索决定转变为更为极简主义的一维风格。她的最新画作可以用一个长为 $N$（$1 \leq N \leq 300$）的一维数组来描述，其中每种颜色用 $1\ldots N$ 中的一个整数表示。

令牛加索感到沮丧的是，尽管这样，她的竞争对手哞奈似乎已经发现了如何抄袭她的这些一维画作！哞奈会用一种颜色涂在一个区间上，等待颜料干了再涂另一个区间，以此类推。哞奈可以使用 $N$ 中颜色中的每一种任意多次（也可以不用）。

请计算哞奈抄袭牛加索的最新一维画作所需要的涂色的次数。

## 说明/提示

#### 样例 1 解释：


在这个样例中，哞奈可以按下列方式进行涂色。我们用 $0$ 表示一个未涂色的方格。

 - 初始时，整个数组均未被涂色：`0 0 0 0 0 0 0 0 0 0`
 - 哞奈将前九个方格涂上颜色 $1$：`1 1 1 1 1 1 1 1 1 0`
 - 哞奈在一个区间上涂上颜色 $2$：`1 2 2 2 2 2 2 2 1 0`
 - 哞奈在一个区间上涂上颜色 $3$：`1 2 3 3 3 3 3 2 1 0`
 - 哞奈在一个区间上涂上颜色 $4$：`1 2 3 4 4 4 3 2 1 0`
 - 哞奈在一个方格上涂上颜色 $1$：`1 2 3 4 1 4 3 2 1 0`
 - 哞奈在最后一个方格上涂上颜色 $6$：`1 2 3 4 1 4 3 2 1 6 `

注意在第一次涂色时，哞奈可以同时在前九个方格之外将第十个方格也同时涂上颜色 $1$，这并不会影响最后的结果。

#### 测试点性质：

 - 对于另外 $15\%$ 的数据，画作中仅出现颜色 $1$ 和 $2$。
 - 对于另外 $30\%$ 的数据，对于每一个 $1\le i\le N$，第 $i$ 个方格的颜色在范围 $\left[12\left\lfloor\frac{i-1}{12}\right\rfloor+1,12\left\lfloor\frac{i-1}{12}\right\rfloor+12\right]$ 之内。
 - 对于另外 $50\%$ 的数据，没有额外限制。

供题：Brian Dean，Benjamin Qi

## 样例 #1

### 输入

```
10
1 2 3 4 1 4 3 2 1 6```

### 输出

```
6```

# 题解

## 作者：Unordered_OIer (赞：18)

# P7414 题解
~~不是，USACO 恶意撞题怎么回事啊/yiw~~

## Description
有一个长度为 $n$ 的初始值均为 $0$ 的序列 $a$，每次操作可以将其中一个子段统一改成任意值。

现给定一个长度为 $n$ 的目标序列 $b$，求最少操作几次可以达到这个目标序列。

## Solution
$dp$ 显然。

考虑设 $f[i][j]$ 表示刷完区间 $[i,j]$ 至少需要多少次。

假设当前决策到 $i,j$，分类讨论：  
- $b_i \neq b_j$，则考虑枚举一个分段点 $k$，依次转移即可，即：  
$$f[i][j]=\min\limits_{k=i}^{j-1}f[i][k]+f[k+1][j]$$

- $b_i=b_j$，则容易得到 $f[i][j] \geq f[i+1][j]$，并且观察到 $f[i+1][j]$ 的任意一种方案都会适合 $f[i][j]$，延申一个底盘即可，因此 $f[i][j] \leq f[i+1][j]$。  
综上，得到 $f[i][j]=f[i+1][j]$，但是因为左右延申都是可以的，所以 $f[i][j]=\min(f[i+1][j],f[i][j-1])$，即：  
$$f[i][j]=\min(f[i+1][j],f[i][j-1])$$

所以通过讨论我们得到了转移方程：

$$f[i][j]=\begin{cases}\min\limits_{k=i}^{j-1}f[i][k]+f[k+1][j]&b_i \neq b_j\\\min(f[i+1][j],f[i][j-1])&b_i=b_j\end{cases}$$

初始化即为 $f[i][j]=\begin{cases}∞&i \neq j\\1&i=j\end{cases}$。

转移即可，复杂度 $\mathcal O(n^3)$。

---

## 作者：_zy_ (赞：18)

## [题目传送门](https://www.luogu.com.cn/problem/P7414)

今天我们来学区间$Dp$呀!

区间$DP$也属于线性$Dp$的一种，它以“区间长度”作为$Dp$的“阶段”，使用两个坐标（区间的左、右端点）描述每个维度。在区间$Dp$中，一个状态由若干个比它更小且包含于它的区间所代表的状态转移而来，因此区间$Dp$的决策往往就是划分区间的方法。区间$Dp$的初态一般就由长度为$1$的“元区间”构成。（参照《算法经典进阶指南》）

一般来说：

时间复杂度：O$_{(n^3)}$

$for$枚举区间长度$len$

$for$再枚举左端点$l$

$r=l+len$	推出右端点$r$

for枚举中间点$k$

递推$zzz$


------
关于此题：

状态：$l，r$

初态:

$f[i][i]=1$

$f[i][j]=INF$

状态转移方程：

考虑两端一样的情况

- 将两个子序列结合在一起，直接将两个$f$相加很显然比最优多$1$，因为可以确定，若一个一个刷会有$len$个，而直接从$[l,r]$刷满先刷一次然后刷剩下的$len-2$次，那么就是$len-1$次了呀!!

- 剩下的就是两个区间相加了。

- 我以上说的都是取给$f[l][r]$最小值.

结果：

$f[1][n]$。

不解释
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 310 
using namespace std;
int n;
int a[N],f[N][N];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)	f[i][i]=1;	//初始化 
	for(int i=1;i<=n;i++)			//区间长度 
	for(int l=1;l+i<=n;l++) {		//左端点 
		int r=l+i;					//右端点 
		for(int k=l;k<=r;k++)		//中间值 
			if(a[l]==a[r]) f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]-1);		//递推 
			else f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]);
	}
	cout<<f[1][n]<<endl;			//结果 
	return 0;
}
```

如果不妥，请不要吝啬您的建议。

-------
[双倍经验](https://www.luogu.com.cn/problem/P4170)

---

## 作者：一只书虫仔 (赞：8)

#### Description

> 定义涂色操作为将一区间改为同一个数，求将全为 $0$ 的序列最少需要多少涂色操作才能变为长度为 $n$ 的序列 $a_i$。

#### Solution

区间 dp，定义 $dp_{i,j}$ 为区间 $[i,j]$ 至少需要多少次涂色操作，分类讨论：

- $i=j$，$dp_{i,j}=1$。
- $a_i=a_j$，$i \ne j$，区间 $[i,j-1]$ 并到 $j$ 或区间 $[i+1,j]$ 并到 $i$，$dp_{i,j}=\min\{dp_{i,j-1},dp_{i+1,j}\}$。
- $a_i \ne a_j$，$i \ne j$，合并区间 $[i,k]$ 和 $[k+1,j]$，$dp_{i,j}=\min\limits_{k=i}^{j-1} \{dp_{i,k}+dp_{k+1,j}\}$。

#### Code

```cpp
for (int i = 1; i <= n; i++) dp[i][i] = 1;
for (int len = 1; len <= n; len++)
	for (int i = 1; i <= n; i++) {
	int j = i + len;
	if (a[i] == a[j]) dp[i][j] = min(dp[i][j - 1], dp[i + 1][j]);
	else 
		for (int k = i; k < j; k++)
			dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
}
```

---

## 作者：frzFRZ (赞：3)

## Question Description

有一个长度为 $n$ 的初始值均为 0 的序列 $a$，每次操作可以将其中任意一个子段中所有值改为一个任意值。

现给定一个长度为 $n$ 的目标序列 $b$，求最少操作次数。\
[P7414 \[USACO21FEB\] Modern Art 3 G](https://www.luogu.com.cn/problem/P7414)

## Solution

此题为区间 DP ，做法类似于石子合并。

### 设计 DP 数组

$f_{i,j}$ 表示画 (抄) 完 $[i , j]$ 这一段区间的最小染色次数。\
显然 $f_{1,n}$ 即为答案。

### 初始化

显然初始化为

$$
f_{i,j} = \begin{cases}
1 & i = j \\
∞ & i \neq j \\
\end{cases}
$$

### 动态转移

1. 先枚举长度与左端点，计算右端点，再枚举中间节点 $k$。

2. 如果 $color_l = color_r$\
   那么 $f_{l,r} = \operatorname{min}( f_{l,r} , f_{l,k} + f_{k + 1,r} - 1 )$\
   否则 $f_{l,r} = \operatorname{min}( f_{l,r} , f_{l,k} + f_{k + 1,r} )$

综上转移方程为

$$
f_{l,r} = \begin{cases}
\operatorname{min}( f_{l + 1,r} , f_{l,r - 1} ) & color_l = color_r \\
\operatorname{min}_{k = l}^{j - 1} f_{l,k} + f_{k + 1,r} & color_l \neq color_r\\
\end{cases}
$$

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300+10;
int f[N][N];
int n,color[N];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>color[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) f[i][j]=1e8;
	for(int i=1;i<=n;i++) f[i][i]=1;
	for(int len=2;len<=n;len++)
	{
		for(int l=1;l+len-1<=n;l++)
		{
			int r=l+len-1;
			for(int k=l;k<r;k++)
			{
				if(color[l]==color[r]) f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]-1);
				else f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]);
			}
		}
	}
	cout<<f[1][n]<<endl;
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：2)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15376113.html)

**完 全 一 样.jpg**

# 题目大意

有一个长度为 $N$ 的序列，初始时序列均为 $0$。

可以对其进行区间赋值，求你至少需要几次操作能将该序列变为目标序列？

# 题目大意

一道原题，详见 $\rm P4170$.

显然是一道区间 $\rm DP$。

令 $dp[i][j]$ 表示把区间 $[i,j]$ 内的数涂成目标颜色所需要的最少次数。

属性：$\min$。

目标：$dp[1][n]$。

令目标序列的第 $i$ 个数为 $a_i$，我们枚举区间左右边界 $l,r$，不难得出方程：

当 $a_l=a_r$ 时，$dp[l][r]=\min\{dp[l+1][r],dp[l][r-1]\}$。

意思是：我们可以认为 $l$ 是涂区间 $[l+1,r]$ 的时候顺便涂上的，或者 $j$ 是涂 $[l,r-1]$ 的时候顺便涂上的。

否则，即当 $a_l\neq a_r$ 时，$dp[l][r]=\{dp[i][k]+dp[k+1][r]\}(l\leq k<r)$。

# 代码

```cpp
const int ma=305;

int a[ma];

int dp[ma][ma];
//dp[i][j]:把区间 [i,j] 涂上目标颜色所需要的最少次数 

int sum; 

int main(void)
{
//	freopen("Art.in","r",stdin);
//	
//	freopen("Art.out","w",stdout);
	
	int n;
	
	scanf("%d",&n);
	
	memset(dp,0x3f,sizeof(dp));
	
	for(register int i=1;i<=n;i++)
	{
		scanf("%d",a+i);
		
		dp[i][i]=1;
	}
	
	for(register int len=2;len<=n;len++)
	{
		for(register int l=1;l<=n;l++)
		{
			int r=l+len-1;
			
			if(r>n)
			{
				break;
			}
			
			if(a[l]==a[r])
			{
				dp[l][r]=min(dp[l+1][r],dp[l][r-1]);
			}
			
			else
			{
				
				for(register int k=l;k<r;k++)
				{
					dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);
				}
			}
		}
	}
	
	printf("%d\n",dp[1][n]);
	
	return 0; 
}
```

---

## 作者：船医 (赞：2)

和[P4170](https://www.luogu.com.cn/problem/P4170)不能说很像，只能说一模一样。

**dp[i][j]:**

	从i到j需要的涂色次数
    
**方程：**
dp[i][j]=min(dp[i][k]+dp[k+1][j],dp[i][j])
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[10005],dp[10005][10005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		dp[i][i]=1;
	}
	for(int len=2;len<=n;len++){
		for(int i=1;i<=n-len+1;i++)
		{
			int j=i+len-1;
			dp[i][j]=1e+9;
			if(a[i]==a[j])
			{
				dp[i][j]=dp[i][j-1];
			}
				for(int k=i;k<j;k++)
				{
					dp[i][j]=min(dp[i][k]+dp[k+1][j],dp[i][j]);
				}
		}
	}
	cout<<dp[1][n]; 
}
```


---

## 作者：Constant (赞：1)

## 题意归纳：

给定一个长度为 $N$ 且数字只会为 $1$ 到 $N$ 的数列，每次可以选取一个子区

间，将其变为任意的数字，数列初始状态为全零，求变为目标状态的最少次数。

## Solution：

先分析一下，需要求的是最小变换次数，每次选择变换区间时，有许多不同的选择

方式，这提示我们要用区间 $DP$ 。

按照一般的区间题的套路，设 $f[i][j]$ 为将区间 $[i,j]$ 变换至目标区间的最

小变换次数，那么最后的答案就是 $f[1][n]$ 了，考虑如何转移。

注意到，如何变换肯定与序列中的数字是有关的，具体地，与区间两端点的数字是有关的，那么我们可以写出如下方程。

设区间两断点值是 $a,b$ 。

当 $a=b$ 时，$f[i][j]=min(f[i+1][j],f[i][j-1])$ ，也就是在第一次整体变换

时把其中一个端点一起变换了，显然是不影响次数的，于是二者取最优即可。

当 $a≠b$ 时，$f[i][j]=min(f[i][k]+f[k+1][j])$ ，枚举一个断点 $k$ ，前面

为一段，后面为一段分开变换即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1005],f[1005][1005]; 
int main()
{
    scanf("%d",&n);
    memset(f,127/3,sizeof(f));
    for(int i=1;i<=n;i++)
    {
    	scanf("%d",&a[i]);
    	f[i][i]=1;
	}
	for(int l=2;l<=n;l++)
	{
		for(int i=1;i+l-1<=n;i++)
		{
			int j=i+l-1;
			if(a[i]==a[j])
			{
				f[i][j]=min(f[i+1][j],f[i][j-1]);
			} 
			else
			{
				for(int k=i;k<=j-1;k++)
				{
					f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
				}
			}
		}
	}
	cout<<f[1][n];
    return 0;
}
```




---

## 作者：BMTXLRC (赞：1)

听到一位神犇[_Enthalpy](https://www.luogu.com.cn/user/42156)说跟 [[CQOI2007]涂色](https://www.luogu.com.cn/problem/P4170) 完全一致，要求的东西都一样，我这个蒟蒻马上就来了。

$\texttt{Upd 2021/07/15}$ 修改了部分公式

------------

### 思路：

首先看其是否有无后效性，我第 $i$ 次的涂色很显然不会影响第 $j$ 次涂色，因此可以考虑用 DP。

其次问题跟区间有关，于是我们采用区间 DP。

以 $f_{i,j}$ 表示从 $a_i$ 到 $a_j$ 的最少染色次数。（注：$f$ 数组是 DP 数组，$a$ 数组是输入数组。

如果 $i=j$ ，很显然要染一次，如果不是且 $a_i=a_j$ ，上一次染色时多染一格就行。

那如果 $a_i\neq a_j$，考虑一个断点 $k$，以这个为界分开左右两部分就行。

**于是就可以得到状态转移方程：**

$\begin{cases}f_{i,j}=1&(i=j)\\f_{i,j}=\min(f_{i-1,j},f_{i,j-1})&(i\neq j,a_i=a_j)\\f_{i,j}=\min(f_{i,j},f_{i,k}+f_{k+1,j})&(i\neq j,a_i\neq a_j)\end{cases}$

又因为 $f_{1,n}$ 表示 $1$ 到 $n$ 的最少染色次数，我们最后输出 $f_{1,n}$ 即可。
 
**记得把你 P4170 的代码数组开大一点（（**

------------

### P7414代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[305][305],n,a[305];
int main(){
	cin>>n;
	for(register int i=1;i<=n;i++) cin>>a[i];
	memset(f,0x7F,sizeof(f));
	for(register int i=1;i<=n;++i) f[i][i]=1;
	for(register int l=1;l<n;++l){
		for(register int i=1,j=1+l;j<=n;++i,++j) {
			if(a[i]==a[j]) f[i][j]=min(f[i+1][j],f[i][j-1]);
			else for(int k=i;k<j;++k) f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
		}
	}
	printf("%d",f[1][n]);
}
```

### P4170 代码（顺便放送.jpg）：

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[52];
int f[52][52],n;
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	memset(f,0x7F,sizeof(f));
	for(register int i=1;i<=n;++i) f[i][i]=1;
	for(register int l=1;l<n;++l){
		for(register int i=1,j=1+l;j<=n;++i,++j) {
			if(s[i]==s[j]) f[i][j]=min(f[i+1][j],f[i][j-1]);
			else for(register int k=i;k<j;++k) f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
		}
	}
	printf("%d",f[1][n]);
}
```

~~是不是很简单（（（~~

---

## 作者：wenjunyi (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/)
## 大意

有一个长度为 $n$ 的初始值均为 $0$ 的序列 $a$，每次操作可以将其中一个子串统一改成任意值。

现给定一个长度为 $n$ 的目标序列 $arr$，求最少操作几次可以把 $a$ 变为 $b$。

## 思路

一道区间 dp 的模板题。

我们第一层循环遍历长度 $l$，第二层循环遍历开头 $i$，就可以算出结尾 $j$，第二层循环遍历中间的每一个点 $k$。

状态转移方程：

如果 $a_i \ne a_j$，那么 $dp[i][j] = \min(dp[i][k]+dp[k+1][j],dp[i][j])$。

如果 $a_i = a_j$，那么 $dp[i][j] = \min(dp[i][j-1],dp[i-1][j])$。

---


## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,dp[305][305],arr[305];
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>arr[i];
	}
	memset(dp,0x3f,sizeof(dp));//初始化
	for(int i=1;i<=n;i++){
		dp[i][i]=1;
	}
	for(int l=2;l<=n;l++){
		for(int j=l;j<=n;j++){
			int i=j-l+1;
			for(int k=i;k<j;k++){
				dp[i][j]=min(dp[i][k]+dp[k+1][j],dp[i][j]);
			}
			if(arr[i]==arr[j]){
				dp[i][j]=min(dp[i][j-1],dp[i-1][j]);
			}
		}
	}
	cout<<dp[1][n];
	return 0;
}
```

---

## 作者：Kalium (赞：0)

# P7414 [USACO21FEB] Modern Art 3 G题解

## 前言：

没写过区间 dp 的题解，唯一写过的还是二维的模板题，特此来发一篇留作纪念。

## 题意：

给长度为 n 的序列染色，一开始没颜色，可以选择用一种颜色连续染色一段长度（不可断开），给定目标序列，求染色几次。

## 思路：

这题吧，看一眼就裸的区间 dp。

我们可以设 $dp_{l, r}$ 为在 $[l, r]$ 间涂成目标序列的最少次数。

接下来就是喜闻乐见的推方程了。

很模板，我们放 4 个情况讨论：

1. 当 $a_l = a_{l + 1}$ 时，即左端点的颜色等于左端点后一个颜色。

那么我们可以知道，此时的最少次数就是在 $[l, r]$ 与 $[l + 1, r]$ 之间选取，那么方程即为 $dp_{l, r} = \min(dp_{l, r}, dp_{l + 1, r})$。

2. 当 $a_r = a_{r - 1}$ 时，即右端点的颜色等于右端点前面一个的颜色。

和上面类似，这个时候最少次数在 $[l, r]$ 和 $[l, r - 1]$ 里面选，方程即为  $dp_{l, r} = \min(dp_{l, r}, dp_{l, r - 1})$。

3. 当 $a_l = a_r$ 时，即左右两端点颜色相同。

这个时候，我们所选区间明显是在 $[l + 1, r]$ 和 $[l, r - 1]$ 之间了，方程即为 $dp_{l, r} = \min(dp_{l + 1, r}, dp_{l, r - 1})$。

4. 一般情况。

除去上面三种特殊情况外，剩下的就是正常的了，那么很明显，这个时候方程就是板子：$dp_{l, r} = \min(dp_{l, r}, dp_{l, k} + dp_{k + 1, r})$。

不过要记得，因为初始的时候无颜色，所以说初始化 $dp_{i, i} = 1$。

## 代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

#define inf 0x3f3f3f3f

using namespace std;

int n;

int a[307];

int dp[307][307];

inline int mina(int a, int b) {
	if (a < b)
		return a;
	return b;
}

int main() {
	memset(dp, inf, sizeof(dp));
	
	scanf("%d", &n);
	
	for (int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	
	for (int i = 1; i <= n; i ++)
		dp[i][i] = 1;
	
	for (int i = 1; i <= n; i ++) {
		for (int l = 1; l <= n - i + 1; l ++) {
			int r = l + i - 1;
			
			for (int k = l; k < r; k ++) {
				if (a[l] == a[l + 1])
					dp[l][r] = mina(dp[l][r], dp[l + 1][r]);	
				else if (a[r] == a[r - 1])
					dp[l][r] = mina(dp[l][r - 1], dp[l][r]);	
				else if (a[l] == a[r])
					dp[l][r] = mina(dp[l + 1][r], dp[l][r - 1]);
				else
					dp[l][r] = mina(dp[l][r], dp[l][k] + dp[k + 1][r]);
			}
		}
	}
	
	printf("%d\n", dp[1][n]);
	
	return 0;
}
```

$Atlantis$.

---

## 作者：StayAlone (赞：0)

### 题意

要将一段长度为 $n$ 初值为 $0$ 的序列变成给定的序列，每一次可以将一个区间全部更改为同一个数值，求最少操作次数。  

### 思路

区间 dp，令 $f_{i, j}$ 表示将区间 $[i, j]$ 更改成给定的序列所需最少操作次数。


有递推式如下：

$$
f_{i, j} = \begin {cases}
\min(f_{i + 1, j}, f_{i, j - 1}) &s_i = s_j\\
\min\limits_{i\leqslant k < j}\{f_{i, k} + f_{k + 1, j}\} &others
\end{cases}
$$  

- 当 $s_i = s_j$ 时，在让 $s_j$ 合法的同时一定可以让 $s_i$ 合法；同理，让 $s_i$ 合法的同时一定能让 $s_j$ 合法，所以取两种情况的最小值。

- 其它情况下，枚举一个 $k$，先操作 $[i, k]$，再操作 $[k + 1, j]$，取所有 $f_{i, k} + f_{k + 1, j}$ 的最小值。  

同时易得边界：

 $\forall i \in [1, n]$，都有 $f_{i, i} = 1$。


[AC code记录](https://www.luogu.com.cn/record/54129455)

```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (int i = j; i <= int(n); ++i)
#define rep2(i, j, n) for (int i = j; i >= int(n); --i)
#define il inline
#define ld long double
#define ll long long
#define ull unsigned long long
#define pyq priority_queue
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define end return 0
using namespace std;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int MAXN = 3e2 + 10, inf = ~0U >> 2;
template <typename T>
il void read(T &x)
{
	x = 0; T f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1; ch = getchar();}
	while (isdigit(ch)) {x = (x << 1) + (x << 3) + (ch & 15); ch = getchar();} x *= f;
}

template <typename T>
il void write(T x)
{
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
int n, s[MAXN], f[MAXN][MAXN];

int main()
{
	read(n);
	rep1(i, 1, n) read(s[i]);
	rep1(i, 1, n) rep1(j, 1, n) f[i][j] = inf;
	rep1(i, 1, n) f[i][i] = 1;
	rep1(l, 2, n)
		rep1(i, 1, n - l + 1)
		{
			int j = i + l - 1;
			if (s[i] == s[j]) f[i][j] = min(f[i + 1][j], f[i][j - 1]);
			else rep1(k, i, j - 1) f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
		}
	write(f[1][n]); end;
}
```

---

## 作者：龙潜月十五 (赞：0)

## 一、前言

本题算是 **区间dp** 的经典模型了，写篇题解讲讲这种套路。

## 二、题意

有一个长度为 $n$ 的初始序列，你每次可以将一段区间变为同一种颜色，后加的颜色会覆盖原先的颜色。问最少涂几次色能变成目标序列。

## 三、思路

首先很明显是 dp 了。一看 **题目所求**：最小值，是 dp 常见的题目类型（最优解）；二看 **数据范围**： $1 \leq n \leq 300$，非常适合 dp。再一看是在区间上操作，区间 dp 就呼之欲出了。

1. **状态**

	既然是区间 dp，那么状态显然是跟 **区间** 相关的，同时我们还要将状态表示成题目所求。设 $f_{i,j}$ 为变成区间 $i \sim j$ 最少要涂几次。
    
2. **转移**

	通过模拟样例我们容易发现，当出现两端颜色相同的情况时，比如说：
    
| $1$ | $2$ | $1$ |
| :----------: | :----------: | :----------: |

我们就不需要涂 $3$ 次，而只需要涂 $2$ 次。为什会这样呢？因为事实上，后面涂的颜色会覆盖原来的颜色，所以两边的颜色其实相当于是顺带的（可以理解为附赠品），并不需要刻意去涂。而由于大区间是由小区间转移而来，因此在中间找一个中转点。因此得到转移方程：

$$\left\{\begin{matrix}
f_{i,j}=\min(f_{i+1,j},f_{i,j-1}) \ (a_i=a_j)& \\ 
f_{i,j}=\min_{k=i}^{j-1}f_{i,k}+f_{k+1,j} (a_i \ne a_j)& 
\end{matrix}\right.$$

3. **初始化**

$$f_{i,i}=1$$

## 四、代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=307;
int n,a[N],f[N][N];

int main()
{
	memset(f,64,sizeof(f));
			
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),f[i][i]=1;
	
	for(int len=2;len<=n;len++)
		for(int i=1;i+len-1<=n;i++)
		{
			int j=i+len-1;
			if(a[i]==a[j])
				f[i][j]=min(f[i+1][j],f[i][j-1]);
			for(int k=i;k<j;k++)
				f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
		}
	
//	for(int i=1;i<=n;i++)
//		for(int j=1;j<=n;j++)
//			printf("%d %d %d\n",i,j,f[i][j]);
	printf("%d",f[1][n]);
	return 0;
}
```


---

