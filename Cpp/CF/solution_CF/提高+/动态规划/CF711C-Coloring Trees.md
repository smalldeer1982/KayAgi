# Coloring Trees

## 题目描述

ZS the Coder and Chris the Baboon has arrived at Udayland! They walked in the park where $ n $ trees grow. They decided to be naughty and color the trees in the park. The trees are numbered with integers from $ 1 $ to $ n $ from left to right.

Initially, tree $ i $ has color $ c_{i} $ . ZS the Coder and Chris the Baboon recognizes only $ m $ different colors, so $ 0<=c_{i}<=m $ , where $ c_{i}=0 $ means that tree $ i $ is uncolored.

ZS the Coder and Chris the Baboon decides to color only the uncolored trees, i.e. the trees with $ c_{i}=0 $ . They can color each of them them in any of the $ m $ colors from $ 1 $ to $ m $ . Coloring the $ i $ -th tree with color $ j $ requires exactly $ p_{i,j} $ litres of paint.

The two friends define the beauty of a coloring of the trees as the minimum number of contiguous groups (each group contains some subsegment of trees) you can split all the $ n $ trees into so that each group contains trees of the same color. For example, if the colors of the trees from left to right are $ 2,1,1,1,3,2,2,3,1,3 $ , the beauty of the coloring is $ 7 $ , since we can partition the trees into $ 7 $ contiguous groups of the same color : $ {2},{1,1,1},{3},{2,2},{3},{1},{3} $ .

ZS the Coder and Chris the Baboon wants to color all uncolored trees so that the beauty of the coloring is exactly $ k $ . They need your help to determine the minimum amount of paint (in litres) needed to finish the job.

Please note that the friends can't color the trees that are already colored.

## 说明/提示

In the first sample case, coloring the trees with colors $ 2,1,1 $ minimizes the amount of paint used, which equals to $ 2+3+5=10 $ . Note that $ 1,1,1 $ would not be valid because the beauty of such coloring equals to $ 1 $ ( $ {1,1,1} $ is a way to group the trees into a single group of the same color).

In the second sample case, all the trees are colored, but the beauty of the coloring is $ 3 $ , so there is no valid coloring, and the answer is $ -1 $ .

In the last sample case, all the trees are colored and the beauty of the coloring matches $ k $ , so no paint is used and the answer is $ 0 $ .

## 样例 #1

### 输入

```
3 2 2
0 0 0
1 2
3 4
5 6
```

### 输出

```
10```

## 样例 #2

### 输入

```
3 2 2
2 1 2
1 3
2 4
3 5
```

### 输出

```
-1```

## 样例 #3

### 输入

```
3 2 2
2 0 0
1 3
2 4
3 5
```

### 输出

```
5```

## 样例 #4

### 输入

```
3 2 3
2 1 2
1 3
2 4
3 5
```

### 输出

```
0```

# 题解

## 作者：qian_shang (赞：10)

 [题目传送门](https://www.luogu.org/problem/CF711C)

 **题目大意**：有 n 棵树， m 种颜料，要求现在要给这些树涂上颜料
>> 最后涂成 k 段（连续颜色相同划为一段如 2 , 1 , 1 , 1 , 3 , 2 , 2 , 3 , 1 , 3 是7段）
>> 有些树已经涂了，则不涂了只能涂一次，输入n个数（每个数为0~m），0表示还没有涂，1~m表示已经涂了哪种颜料。
>> 接下来输入 n 行 m 列，表示每棵树涂成每种颜色所要的颜料量。
>> 现在要把所有树都涂上颜料涂成 k 段，求最少要用的颜料量。

 数据范围：n , m <=100

 首先，根据范围我们很容易想到这是一道三维DP

 那么$dp[i][j][k]$的含义就是
> 前$i$个点
> 分成$j$段
> 最后一段颜色是$k$的最小代价

 状态方程很~~容易~~就推出来了

 要注意本身就有颜色的情况

 细节详见代码注释：


```c++
#include<bits/stdc++.h>
#define N 105
#define R register
#define LL long long 
#define inf 0x7f7f7f7f7f7f//inf不能开小了，不然会WA
using namespace std;
inline LL read(){
	LL f=1,x=0; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}//快读，但好像没用
inline LL maxx(LL x,LL y){return x>y?x:y;}
inline LL minn(LL x,LL y){return x<y?x:y;}//自定义min函数（稍微快一点）
LL n,m,k,ans=inf,co[N],w[N][N],dp[N][N][N];
int main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	for (LL i=1;i<=n;i++) scanf("%lld",&co[i]);
	for (LL i=1;i<=n;i++)
		for (LL j=1;j<=m;j++) scanf("%lld",&w[i][j]);
	memset(dp,inf,sizeof(dp));//先初始化为极大值
	if (co[1]) dp[1][1][co[1]]=0;//如果第一个点有颜色就没有代价
	else for (LL i=1;i<=m;i++) dp[1][1][i]=w[1][i];//否则赋代价
	for (LL i=2;i<=n;i++)
	for (LL j=1;j<=k&&j<=i;j++){
		if (co[i]){//有颜色（无代价）
			for (LL l=1;l<=m;l++){
				if (co[i]==l) dp[i][j][l]=minn(dp[i][j][l],dp[i-1][j][l]);//一样就作为连续一段
				else dp[i][j][co[i]]=minn(dp[i][j][co[i]],dp[i-1][j-1][l]);//不一样就新开一段
			}
		}else{//没颜色（有代价）
			for (LL l=1;l<=m;l++)
			for (LL p=1;p<=m;p++)
				if (l==p) dp[i][j][l]=minn(dp[i][j][l],dp[i-1][j][p]+w[i][l]);//一样是连续一段
				else dp[i][j][l]=minn(dp[i][j][l],dp[i-1][j-1][p]+w[i][l]);//不一样新开一段
		}
	}
	if (co[n]) ans=dp[n][k][co[n]];//最后一个有颜色就只能以那种颜色结尾
	else for (LL i=1;i<=m;i++) ans=minn(ans,dp[n][k][i]);//否则全部枚举一遍
	printf("%lld",(ans<inf)?ans:-1);//记得要判断无解
    return 0;
}
```

 还有疑问私信我QWQ

---

## 作者：nomonick (赞：1)

[CF711C Coloring Trees](https://www.luogu.com.cn/problem/CF711C)

原题网址：[Codeforces Round #369 (Div. 2)C. Coloring Trees](https://codeforces.com/problemset/problem/711/C)

这道题的题意很好理解，所以直奔主题

先设置一个 $DP$ 函数 ：

$$
dp[iterator][colour][k]
$$

这个函数意义为，在第 $i$ 棵树，染为第 $colour$ 的颜色，分成了 $k$ 段的最小花费。

之后分类讨论

- 这棵树原本被染色了

所以这棵树颜色不变，状态直接从前一棵树继承。

$$
dp[i][colour[i]][tmp] = min(dp[i][colour[i]][tmp],dp[i-1][last][tmp - (last == colour[i] ? 0 : 1)]);
$$

- 这棵树原本没被染色

这棵树可以染成任何的颜色，所以在继承的基础上加上染色花费

$$
dp[i][j][tmp] = min(dp[i][j][tmp],dp[i-1][last][tmp - (last == j ? 0 : 1)] + cost[i][j]);
$$

对第一棵树进行操作，初始化 $DP$ 数组（预先设为正无限），之后从第二课树开始进行 $DP$ 。

# code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int SIZE = 150;

inline int read()
{
	int x = 0,f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return f * x;
}

int n,m,k;
int num[SIZE];
int cost[SIZE][SIZE],dp[SIZE][SIZE][SIZE];

signed main()
{
	memset(dp,0x3f,sizeof(dp));
	n = read();m = read();k = read();
	for (int i = 1; i <= n; ++i)
	{
		num[i] = read();
	}
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			cost[i][j] = read();
		}
	}
	if (num[1]) dp[1][num[1]][1] = 0;
	else 
	{
		for (int i = 1; i <= m; ++i)
		{
			dp[1][i][1] = cost[1][i];
		}
	}
	for (int i = 2; i <= n; ++i)
	{
		if (num[i] != 0)
		{
			for (int tmp = 1; tmp <= k; ++tmp)
			{
				for (int last = 1; last <= m; ++last)
				{
					dp[i][num[i]][tmp] = min(dp[i][num[i]][tmp],dp[i-1][last][tmp - (last == num[i] ? 0 : 1)]);
				}
			}
			continue;
		}
		for (int j = 1; j <= m; ++j)
		{
			for (int tmp = 1; tmp <= k; ++tmp)
			{
				for (int last = 1; last <= m; ++last)
				{
					dp[i][j][tmp] = min(dp[i][j][tmp],dp[i-1][last][tmp - (last == j ? 0 : 1)] + cost[i][j]);
				}
			}
		}
	}
	int ans = 0x7f7f7f7f7f7f;
	for (int i = 1; i <= m; ++i)
	{
		ans = min(ans,dp[n][i][k]);
	}
	if (ans >= 0x7f7f7f7f7f7f) printf("-1\n"); // 记得判无解
	else printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：GK0328 (赞：1)

# $DP$

$a[i]$表示第$i$棵树的颜色

$col[i][j]$表示第$i$棵树涂成颜色$j$所需要的颜料量

很容易想到$DP$的做法

$f[i][j][k]$表示涂完前$i$棵树，涂成$j$段，第$i$棵树涂成颜色$k$时，最少需要的颜料量

分为两种情况讨论：

### $1.$第$i$棵树已被涂色

$$ f[i][j][a[i]]=\max\begin{cases}
f[i-1][j][a[i]]  \\
\max\limits_{1≤t≤m,t≠a[i]}f[i-1][j-1][t] 
\end{cases}
$$

### $2.$第$i$棵树未被涂色

$$ f[i][j][l]=\max\begin{cases}

f[i-1][j][l]+col[i][l]  \\

\max\limits_{1≤t≤m,t≠l} \{f[i-1][j-1][t]+col[i][l]\} 

\end{cases}
$$

时间复杂度：$O(nkm^2)$

空间复杂度：$O(nkm)$

实际上已经可以$AC$了

但是我们考虑优化

## 空间优化：

常规操作，我们观察到$f[i][…][…]$只与$f[i-1][…][…]$有关，我们可以用滚动数组，从而优化空间复杂度

## 时间优化：

我们发现，第二种情况的时间复杂度较大，尝试优化这种情况

观察一下这个式子：

$$ f[i][j][l]=\max\begin{cases}

f[i-1][j][l]+col[i][l]  \\

\max\limits_{1≤t≤m,t≠l} \{f[i-1][j-1][t]+col[i][l]\} 

\end{cases}
$$

转化为：

$$ f[i][j][l]=col[i][l]+\max\begin{cases}

f[i-1][j][l]  \\

\max\limits_{1≤t≤m,t≠l} \{f[i-1][j-1][t]\} 

\end{cases}
$$

$\max\limits_{1≤t≤m,t≠l} \{f[i-1][j-1][t]\}$如何计算

$RMQ?$

没错，我们可以用$ST$表进行处理，然后将$[1,l-1],[l+1,m]$两段区间的最大值直接从$ST$表中取出就好了！

优化后：

时间复杂度：$O(nkm·logm)$

空间复杂度：$O(km)$

$C$++ $Code:$

```cpp
#include<bits/stdc++.h>
#define N 105
using namespace std;
int n,m,s,a[N],col[N][N],lg2[N],r1,r2,r3;
long long dp[2][N][N];
long long st[N][N];
inline int read()
{
	int s=0;
	char c=getchar();
	while (c<'0'||c>'9')
		c=getchar();
	while ('0'<=c&&c<='9')
		s=s*10+c-'0',c=getchar();
	return s;
}
inline long long gm(int s,int t)
{
	if (s>t)
		return 12345678987654321;
	int k=lg2[t-s+1];
	return min(st[s][k],st[t-(1 << k)+1][k]);
}
int main() 
{
	n=read(),m=read(),s=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			col[i][j]=read();
	for (int i=0;i<2;i++)
		for (int j=0;j<=s;j++)
			for (int k=0;k<=m;k++)
				dp[i][j][k]=12345678987654321;
	lg2[0]=-1;
	for (int i=1;i<=m;i++)
		lg2[i]=lg2[i/2]+1;
	if (a[1])
		dp[1][1][a[1]]=0; else
		{
			for (int k=1;k<=m;k++)
				dp[1][1][k]=col[1][k];
		}
	for (int pre=1,now=0,i=2;i<=n;pre=i&1,i++,now=i&1)
	{
		for (int j=0;j<=s;j++)
			for (int k=0;k<=m;k++)
				dp[now][j][k]=12345678987654321;
		r1=min(i,s);
		for (int j=1;j<=r1;j++)
		{
			if (a[i])//第一种情况
			{
				for (int k=1;k<=m;k++)
					if (a[i]^k)
						dp[now][j][a[i]]=min(dp[now][j][a[i]],dp[pre][j-1][k]); else
						dp[now][j][a[i]]=min(dp[now][j][a[i]],dp[pre][j][k]);
			} else//第二种情况
			{ //建立ST表
				for (int k=1;k<=m;k++)
					st[k][0]=dp[pre][j-1][k];
				for (int k=1;k<=lg2[m];k++)
					for (int l=1;l<=m-(1 << k)+1;l++)
						st[l][k]=min(st[l][k-1],st[l+(1 << (k-1))][k-1]);
				for (int k=1;k<=m;k++)
					dp[now][j][k]=min(dp[now][j][k],min(dp[pre][j][k],min(gm(1,k-1),gm(k+1,m)))+col[i][k]);
			}
		}
	}
	long long ans=12345678987654321;
	for (int i=1,now=n&1;i<=m;i++)
		ans=min(ans,dp[now][s][i]);
	if (ans==12345678987654321)
		ans=-1;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：James_Brady (赞：1)

终极n^4DP来也！

first,n,m<=100，一看就特别暴力

然后，我们定义```dp[i][j][k]```为**涂到第i棵树，一共有j段颜色，上一个颜色是k的最小花费**

转移时我们枚举上一个颜色和这一个颜色（如果已涂则不用枚举）

如果当前的颜色=上一个颜色，则将```dp[i-1][j][k]```转移到```dp[i][j][k]```

否则，则将```dp[i-1][j-1][k]```转移到```dp[i][j][l]```

code:
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
ll dp[110][110][110],a[110][110];
int n,m,p,col[110];
int main()
{
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1;i<=n;i++)
	scanf("%d",&col[i]);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	scanf("%lld",&a[i][j]);
	for(int i=0;i<=n;i++)
	for(int j=0;j<=p;j++)
	for(int k=1;k<=m;k++)
	dp[i][j][k]=1e17;//初始化
	for(int i=1;i<=m;i++)
	dp[0][0][i]=dp[0][1][i]=0;//这个初始化很重要
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i&&j<=p;j++)
		{
			if(col[i])//特判是否已有颜色
			{
				if(col[i-1])//同理
				{
					if(col[i]==col[i-1])
					dp[i][j][col[i]]=min(dp[i][j][col[i]],dp[i-1][j][col[i-1]]);
					else
					dp[i][j][col[i]]=min(dp[i][j][col[i]],dp[i-1][j-1][col[i-1]]);
				}
				else
				{
					for(int l=1;l<=m;l++)
					{
						if(l==col[i])
						dp[i][j][col[i]]=min(dp[i][j][col[i]],dp[i-1][j][l]);
						else
						dp[i][j][col[i]]=min(dp[i][j][col[i]],dp[i-1][j-1][l]);
					}
				}
			}
			else
			{
				for(int k=1;k<=m;k++)
				{
					if(col[i-1])
					{
						if(k==col[i-1])
						dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][col[i-1]]+a[i][k]);
						else
						dp[i][j][k]=min(dp[i][j][k],dp[i-1][j-1][col[i-1]]+a[i][k]);
					}
					else
					{
						for(int l=1;l<=m;l++)
						{
							if(l==k)
							dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][l]+a[i][k]);
							else
							dp[i][j][k]=min(dp[i][j][k],dp[i-1][j-1][l]+a[i][k]);
						}
					}
				}
			}
		}
	}
	ll ans=1e17;
	if(col[n])
	ans=dp[n][p][col[n]];
	else
	{
		for(int i=1;i<=m;i++)
		ans=min(ans,dp[n][p][i]);
	}
	if(ans>=1e17)
	ans=-1;
	printf("%lld",ans);
}
```


---

## 作者：orz_z (赞：0)

记 $f_{i,j,k}$ 表示前 $i$ 个点，第 $i$ 个点染为 $j$，分成 $k$ 段的最小花费。

转移方程：

* 第 $i$ 个点已被染色：$f_{i,col_i,k}=\min(f_{i,col_i,k},f_{i-1,lst,k-[lst \ne col_i]})$。
* 第 $i$ 个点未被染色：$f_{i,j,k}=\min(f_{i,j,k},f_{i-1,lst,k-[lst\ne j]}+cost_{i,j})$。

时间复杂度 $\mathcal O(nkm^2)$，可用 `st` 表优化到 $\mathcal O(nkm\log m)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x * f;
}

#define inf 0x7f7f7f7f7f7f

const int _ = 208;

int n, m, k, ans = inf, col[_], cost[_][_], dp[_][_][_];

signed main()
{
	n = read(), m = read(), k = read();
	for(int i = 1; i <= n; ++i) col[i] = read();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) cost[i][j] = read();
	memset(dp, inf, sizeof dp);
	if(col[1]) dp[1][col[1]][1] = 0;
	else for(int i = 1; i <= m; ++i) dp[1][i][1] = cost[1][i];
	for(int i = 2; i <= n; ++i)
		for(int j = 1; j <= k && j <= i; ++j)
			if(col[i])
			{
				for(int l = 1; l <= m; ++l)
					dp[i][col[i]][j] = min(dp[i][col[i]][j], dp[i - 1][l][j - (col[i] == l ? 0 : 1)]);
			}
			else
			{
				for(int l = 1; l <= m; ++l)
					for(int p = 1; p <= m; ++p)
						dp[i][l][j] = min(dp[i][l][j], dp[i - 1][p][j - (l == p ? 0 : 1)] + cost[i][l]);
			}
	if(col[n]) ans = dp[n][col[n]][k];
	else for(int i = 1; i <= m; ++i) ans = min(ans, dp[n][i][k]);
	printf("%lld", (ans < inf) ? ans : -1);
	return 0;
}
```

---

## 作者：Tyyyyyy (赞：0)

## 经典分类巨多无比的dp
题目大意这里不再赘述，没看过的看[题面](https://www.luogu.com.cn/problem/CF711C)
。

状态很好确定：用$dp(i,j,k)$表示前$i$棵树，染色染成$j$段，最后一段颜色为$k$时的最小颜料值。

问题就在于分类：首先很容易想到分为当前树木染过和没染过两种情况（已经染好的不能再染）。

如果树木没有被染过色，那么染到这里的最小代价就与它的前一棵树的染色有关。

用$k$表示当前染色，$l$表示前一棵树的染色，则：

$if(k==l):$
$dp(i,j,k)=min(dp(i,j,k),dp(i-1,j,l)+c(i,k))$

$if(k!=l):$
$dp(i,j,k)=min(dp(i,j,k),dp(i-1,j-1,l)+c(i,k))$

这里用$c$数组来表示涂每一棵树所需的颜料量，其他应该就很好理解了。

如果当前树木已经被染过色了，那么就不用枚举当前树木的颜色（即$dp(i,j,k)$中的$k$项）。

此时用$k$枚举前一棵树的颜色，$t(i)$表示当前树木的颜色，则有：

$dp(i,j,t(i))=min(dp(i,j,t(i)),dp(i-1,j-(k==t(i)),k))$

应该也很好理解，不多叙述（其中的$k==t(i)$表判断）。

最后的答案同样分两种情况：如果最后一棵树是染好色的，那答案就固定为$dp(n,p,t(n))$（p是题中要求最后涂成的段数）；如果最后一棵树没有染色，则答案是$min(dp(n,p,i))(1<=i<=m)$。

最后注意，本题的数据范围是$1<=c(i,j)<=10^9$，所以需要开$long long$。

完整的$AC$代码如下：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,p,t[105],c[105][105],dp[105][105][105],ans;
int main()
{
	scanf("%lld%lld%lld",&n,&m,&p);
	for(ll i=1;i<=n;i++)scanf("%lld",&t[i]);
	for(ll i=1;i<=n;i++)
	{
		for(ll j=1;j<=m;j++)
		{
			scanf("%lld",&c[i][j]);
		}
	}
	for(ll i=0;i<=n;i++)
	{
		for(ll j=0;j<=p;j++)
		{
			for(ll k=0;k<=m;k++)dp[i][j][k]=1e18;//注意初始化！
		}
	}
	for(ll k=0;k<=m;k++)dp[0][0][k]=dp[0][1][k]=0;
	for(ll i=1;i<=n;i++)
	{
		for(ll j=1;j<=i&&j<=p;j++)
		{
			if(t[i]==0)
			{
				for(ll k=1;k<=m;k++)
				{
					for(ll l=1;l<=m;l++)
					{
						if(k==l)dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][l]+c[i][k]);
						else dp[i][j][k]=min(dp[i][j][k],dp[i-1][j-1][l]+c[i][k]);
					}
				}
			}
			else
			{
				for(ll k=1;k<=m;k++)
				{
					if(k==t[i])dp[i][j][t[i]]=min(dp[i][j][t[i]],dp[i-1][j][k]);
					else dp[i][j][t[i]]=min(dp[i][j][t[i]],dp[i-1][j-1][k]);
				}
			}
		}
	}
	ans=1e18;
	if(t[n])ans=dp[n][p][t[n]];
	else for(ll i=1;i<=m;i++)ans=min(ans,dp[n][p][i]);
	if(ans==1e18)printf("-1");
	else printf("%lld",ans);
	return 0;
}
```

---

## 作者：liuyanxi2 (赞：0)

## 这道题的主要解法就是三维DPdp[i][j][k]表示在第i个树之前分为了j组，且上一组的颜色是k

#### 但是这道题不好做的地方在于它要分很多种情况，现在我们就一一分析一下：

## 一：此时树已经被染色了：

那么显然，此时k就确定了，即此时的颜色，我们所考虑的就是j，前面分了多少组，这可以在最外层的for循环中直接枚举。

所以很多人就觉得dp[i][j][k]=dp[i-1][j-1][k]了。但是我们要考虑上一组的颜色与当前颜色相同与否。那么我们就还要来一个for循环枚举

```
for(long long k=1;k<=m;k++)
{
	if(k==num[i])
	dp[i][j][num[i]]=min(dp[i][j][num[i]],dp[i-1][j][k]);
	else
	dp[i][j][num[i]]=min(dp[i][j][num[i]],dp[i-1][j-1][k]);
}
```

## 二：此时树还没有被染色：

此时k不确定了，那么我们还是用for循环解决，每个都枚举一次。上面上一组的颜色与当前颜色相同与否的问题仍然存在，那么我们还要用一个for循环枚举

```
for(long long k=1;k<=m;k++)
for(long long q=1;q<=m;q++)
if(k==q)
dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][q]+hua[i][k]);
else
dp[i][j][k]=min(dp[i][j][k],dp[i-1][j-1][q]+hua[i][k]);

```

### 这就是dp的主体内容了，如果大家还有不懂的就结合代码理解哈

```
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,n,m,x,dp[101][101][101],num[101],hua[101][101],ans=1e17;             //dp[i][j][k]表示前i个树涂成j段，最后一段颜色是k; 
int main ( )
{
	scanf("%lld%lld%lld",&n,&m,&x);
	for(long long i=1;i<=n;i++)
	scanf("%lld",&num[i]);
	for(long long i=1;i<=n;i++)
	for(long long j=1;j<=m;j++)
	scanf("%lld",&hua[i][j]);
	for(long long i=0;i<=n;i++)
	for(long long j=0;j<=x;j++)
	for(long long k=1;k<=m;k++)
	dp[i][j][k]=1e17;
	for(long long i=1;i<=m;i++)
	dp[0][0][i]=dp[0][1][i]=0;
	for(long long i=1;i<=n;i++)
	for(long long j=1;j<=i&&j<=x;j++)               //已有j段
	{
		if(num[i]==0)
		{
			for(long long k=1;k<=m;k++)
			for(long long q=1;q<=m;q++)
			if(k==q)
			dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][q]+hua[i][k]);
			else
			dp[i][j][k]=min(dp[i][j][k],dp[i-1][j-1][q]+hua[i][k]);
		}
		else
		{
			for(long long k=1;k<=m;k++)
			{
				if(k==num[i])
				dp[i][j][num[i]]=min(dp[i][j][num[i]],dp[i-1][j][k]);
				else
				dp[i][j][num[i]]=min(dp[i][j][num[i]],dp[i-1][j-1][k]);
			}
		}
	}
	if(num[n]!=0)
	ans=dp[n][x][num[n]];
	else
	for(long long i=1;i<=m;i++)
	ans=min(ans,dp[n][x][i]);
	if(ans>=1e17)
	cout<<-1;
	else
	cout<<ans;
	return 0 ;
}
```

Thanks for reading

---

