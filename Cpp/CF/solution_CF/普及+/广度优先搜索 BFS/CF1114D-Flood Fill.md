# Flood Fill

## 题目描述

You are given a line of $ n $ colored squares in a row, numbered from $ 1 $ to $ n $ from left to right. The $ i $ -th square initially has the color $ c_i $ .

Let's say, that two squares $ i $ and $ j $ belong to the same connected component if $ c_i = c_j $ , and $ c_i = c_k $ for all $ k $ satisfying $ i < k < j $ . In other words, all squares on the segment from $ i $ to $ j $ should have the same color.

For example, the line $ [3, 3, 3] $ has $ 1 $ connected component, while the line $ [5, 2, 4, 4] $ has $ 3 $ connected components.

The game "flood fill" is played on the given line as follows:

- At the start of the game you pick any starting square (this is not counted as a turn).
- Then, in each game turn, change the color of the connected component containing the starting square to any other color.

Find the minimum number of turns needed for the entire line to be changed into a single color.

## 说明/提示

In the first example, a possible way to achieve an optimal answer is to pick square with index $ 2 $ as the starting square and then play as follows:

- $ [5, 2, 2, 1] $
- $ [5, 5, 5, 1] $
- $ [1, 1, 1, 1] $

In the second example, a possible way to achieve an optimal answer is to pick square with index $ 5 $ as the starting square and then perform recoloring into colors $ 2, 3, 5, 4 $ in that order.

In the third example, the line already consists of one color only.

## 样例 #1

### 输入

```
4
5 2 2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
8
4 5 2 2 1 3 5 5
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1
4
```

### 输出

```
0
```

# 题解

## 作者：lzpclxf (赞：22)

### 每日一唠：

这道题难度良心真的评的有点高

是一个区间DP并没有什么很难想的地方

我是在做完[她](https://www.luogu.org/problem/P4170)之后学长推荐才过来的

建议大家也做一下~~可能泥萌早就做完了~~

### 正文：
区间DP正常思路即可

然后开数组一定要看数据范围！

~~为什么？这还用问吗？我MLE一气之下就变成了RE~~

```cpp
	for (int i = 1; i <= n; i++) {
		int x;
		scanf ("%d", &x);
		if (x != fre) a[++num] = x;
		fre = x;
	}
```


这一个地方我是借鉴了一下别人题解的思路Orz， 处理的很巧妙， 在输入的同时就把重复的颜色相同但是长短不一的连通块全都处理成一块， 因为他们颜色都一样所以这样处理完全没问题啊

然后dp
```cpp
	for (int l = 1; l <= num; l++)
		for (int i = 1; i + l <= num; i++) 
        	int j = i + l;
```
第一层循环枚举区间长度， 第二层循环枚举可行的左区间， j是算出的右区间， 注意不同题目不同分析，有的题目必须给f赋一个很大的初值再更新之类的，而此题可以不用这样。

```cpp
			if (a[i] == a[j]) f[i][j] = f[i + 1][j - 1] + 1;
			else f[i][j] = min (f[i + 1][j], f[i][j - 1]) + 1;
```
分两种情况的dp

1.两边的颜色相同那就是中间的长度再加上1（因为是合并）

2.两边颜色不同那就在两边分别取最小即可 。

The Last：

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 10101;
int num, n, a[N], fre, f[N][N];
int main () {
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x;
		scanf ("%d", &x);
		if (x != fre) a[++num] = x;
		fre = x;
	}
	for (int l = 1; l <= num; l++)
		for (int i = 1; i + l <= num; i++) {
			int j = i + l;
			if (a[i] == a[j]) f[i][j] = f[i + 1][j - 1] + 1;
			else f[i][j] = min (f[i + 1][j], f[i][j - 1]) + 1;
		}
	printf ("%d\n", f[1][num]);
	return 0;
}
```
谢谢收看， 祝身体健康！



---

## 作者：rui_er (赞：13)

又是一道小清新 dp 题。

题意简述：有 $n$ 个位置，初始颜色已知。每一次可以将与一个格子相邻的所有颜色相同的格子的颜色更改为任意数。要在尽可能少的步数内将所有格子染成同一个颜色，求这个步数。

---

思路：

我最开始的思路和原题官方题解的解法 $1$ 比较相似。

首先设计状态，像这种区间进行染色的问题容易想到设 $dp_{i,j}$ 表示将 $i\sim j$ 格子全部染成相同颜色所需的步数。但是这里比较特殊，需要添加一个维度，表示染成最左侧的颜色还是最右侧的颜色。

为什么只考虑左右两种颜色呢？我们的每次合并都在上次的基础上添加了一个数，由于上次的区间是合并好了的，因此除了新添加的数以外，其他的数的颜色均相同。只有这两种颜色，还恰好位于两侧，就只考虑这两种情况即可。

最终设计好的状态：$dp_{i,j,bit}$，表示 $i\sim j$ 全部染成同一种颜色（$bit=0$ 表示最左侧的颜色，否则是最右侧的颜色）所需的最少步数。

根据这个定义，我们得到初始值：对于 $i\ne j$，$dp_{i,j,0}=dp_{i,j,1}=\inf$；否则 $dp_{i,j,0}=dp_{i,j,1}=1$。

状态的转移：我们枚举当前区间的右端点，从右端点向左枚举左端点，得到当前区间 $\left[l,r\right]$，使用当前区间向左或向右更新两侧 $dp$ 的值。

设当前颜色为 $col$（根据 $dp$ 的 $bit$ 值获取左侧或右侧），初始颜色数组为 $a_{1,2,\cdots n}$，则转移方程为：

$$
\begin{aligned}
dp_{i-1,j,0}=&\min(dp_{i-1,j,0},dp_{i,j,bit}+(a_{i-1}\ne col))\\
dp_{i,j+1,1}=&\min(dp_{i,j+1,1},dp_{i,j,bit}+(a_{j+1}\ne col))
\end{aligned}
$$

最终的结果就是 $\min(dp_{1,n,0},dp_{1,n,1})$ 的值。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;
const int N = 5005, inf = 0x3f3f3f3f;

int n, a[N];
int dp[N][N][2];

void initDP() {
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			dp[i][j][0] = dp[i][j][1] = (i == j ? 0 : inf);
		}
	}
}
void updDP(int &a, int b) {a = min(a, b);}

int main() {
	scanf("%d", &n);
	for(int i=1;i<=n;i++) scanf("%d", &a[i]);
	initDP(); 
	for(int j=1;j<=n;j++) {
		for(int i=j;i>=1;i--) {
			for(int bit=0;bit<=1;bit++) {
				int col = bit ? a[j] : a[i];
				if(i > 1) updDP(dp[i-1][j][0], dp[i][j][bit] + (col != a[i-1]));
				if(j < n) updDP(dp[i][j+1][1], dp[i][j][bit] + (col != a[j+1]));
			}
		}
	}
	printf("%d\n", min(dp[1][n][0], dp[1][n][1]));
	return 0;
}
```

---

## 作者：Trimsteanima (赞：10)

### Solution
一看就是很水的区间DP

$dp[i][j]$表示区间$[l,r]$都涂成同色的代价。
$dp[i][j] = min( dp[i][j],  dp[i][k] + dp[k][j] + 1)$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, x, a[5010], f[5010][5010], y, cnt;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++) {
		scanf("%d", &x);
		if (x != y) a[++ cnt] = x;
		y = x;
	}
	for (int i = 1; i <= cnt; i ++)
		for (int j = 1; j + i <= cnt; j ++)
			if (a[j] == a[j + i])
				f[j][j + i] = f[j + 1][j + i - 1] + 1;
			else f[j][j + i] = std::min(f[j + 1][j + i], f[j][j + i - 1]) + 1;
	return printf("%d\n", f[1][cnt]), 0;
}
```


---

## 作者：MY（一名蒟蒻） (赞：4)

[CF1114D Flood Fill](https://www.luogu.com.cn/problem/CF1114D)

这题是我在学搜索的时候找到的。仔细一看发现是个区间DP。

~~极具迷惑性的Flood Fill~~。

---

顺带复习一下区间DP。

区间DP的状态转移方程一般有两种。
1. 枚举两端和断点合并；
2. 插入队头队尾分类讨论；

DP以 $len$ 为阶段，第一重循环枚举区间长度。通过公式和枚举的 $i$ 搞出 $j$ 然后再做DP。

有时设计的状态不太可做，要考虑给状态加限制或使状态表示的信息少一些。

第一种的经典题是[P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)。

本题采用的是第二种。

解释一下为什么外层循环要枚举长度。因为合并一定是由小的区间推到大的，于是区间的长度要从小到大枚举。

## 状态设计

一种非常好想的设计是：设 $f_{i,j}$ 表示合并 $i$ 到 $j$ 这段区间的最小花费。

考虑向两端转移，我们面临一个问题，就是如果转移的这个点和我们现在这个区间的颜色是一样的，没有花费。

但是我们不知道这个区间的颜色是啥。

**如果DP有个东西不知道，就把它放进下标里面。**

于是状态设计变成：设 $f_{i,j,0/1}$ 表示合并 $i$ 到 $j$ 这段区间的最小花费，且此时区间是左（右）边的颜色。

## 状态转移方程

很好搞了，如果一样没花费，否则花费加一，考虑从左边还是右边转移，转移到左边还是右边。

## 正确性

因为区间DP区间的规模从小到大，而且最后是哪种颜色无所谓，故正确性得证。

## Code

题解区有很多大佬缩了区间长度，由于我太弱了，所以直接无脑上了一个。基本都是在复读，非常容易理解。

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int N=5e3+10;
int n,a[N],f[N][N][2]; 

int main()
{
//	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++) f[i][i][0]=0;//一个就行，因为区间长度为1哪边都一样
	for(int len=1,j;len<=n;len++)
	{
		for(int i=1;i+len-1<=n;i++)
		{
			j=i+len-1;
        //从f[i][j]转移到左边i-1
        //从i转移
			if(a[i] == a[i-1]) f[i-1][j][0]=min(f[i-1][j][0],f[i][j][0]);
			else f[i-1][j][0]=min(f[i-1][j][0],f[i][j][0]+1);
        //从j转移
			if(a[j] == a[i-1]) f[i-1][j][0]=min(f[i-1][j][0],f[i][j][1]);
			else f[i-1][j][0]=min(f[i-1][j][0],f[i][j][1]+1);
			//从f[i][j]转移到右边j+1
        //从j转移
			if(a[j] == a[j+1]) f[i][j+1][1]=min(f[i][j+1][1],f[i][j][1]);
			else f[i][j+1][1]=min(f[i][j+1][1],f[i][j][1]+1);
        //从i转移
			if(a[i] == a[j+1]) f[i][j+1][1]=min(f[i][j+1][1],f[i][j][0]);
			else f[i][j+1][1]=min(f[i][j+1][1],f[i][j][0]+1);
		}
	}
	printf("%d",min(f[1][n][0],f[1][n][1]));//取min即可
//	fclose(stdin); fclose(stdout);
	return 0;
}
```
希望这篇题解对您学习OI有帮助！

## $Thank\ you\ for\ your\ reading!$

---

## 作者：lgswdn_SA (赞：3)

一道清新的简单 DP 题。

我们发现其实初始给定的颜色连通块没什么用，因为每一个颜色连通块抽象成一个点也不会有问题（即 unique 一下）。

设 $f(l,r)$ 代表 $[l,r]$ 的最少操作数。直接枚举涂哪个点会爆炸。我们考虑优化。

用一个区间 DP 的没啥意思的常见技巧，更换计算顺序，先枚举长度再枚举左端点，那么转移可以想象成一个动态扩张的过程。如果两端的颜色相同，那么直接合并中间的即可。如果颜色不同，那么取 max。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5009;

int n,c[N],f[N][N];

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	n=unique(c+1,c+n+1)-c-1;
	for(int i=1;i<=n;i++) f[i][i]=0;
	for(int len=2;len<=n;len++)
		for(int l=1;l<=n-len+1;l++) {
			int r=l+len-1;
			f[l][r]=(c[l]==c[r] ? f[l+1][r-1]+1 : min(f[l][r-1],f[l+1][r])+1);
		}
	printf("%d",f[1][n]);
	return 0;
}
```

---

## 作者：一只书虫仔 (赞：2)

这个数据是不是有点水，我 dp 执行的时候不小心把去重后的 cnt 写成了去重前的 $n$ 还过了。。

#### Description

> 给定一个长为 $n$ 的序列 $a_i$，每次可以将一个数相同的区间改为同一个数，求至少需要多少步能使得这 $n$ 个数相等。

#### Solution

定义 $dp_{l,r}$ 为区间 $[l,r]$ 满足要求的最小步数，考虑区间 dp，对于两个数 $i,j$（$i<j$）有：

- 如果 $a_i=a_j$，那么可以先让区间 $[i+1,j-1]$ 满足要求再转移过来，从 $dp_{i+1,j-1}+1$ 转移过来。
- 如果 $a_i \ne a_j$，那么一种情况是让区间 $[i,j-1]$ 满足要求再让 $j$ 跟他们统一，另一种是让区间 $[i+1,j]$ 满足要求再让 $i$ 跟他们统一，从 $\min\{dp_{i,j-1},dp_{i+1,j}\}+1$ 转移过来。

为了方便计算，考虑去重，即将一个区间缩为一个点，方式简单，不多赘述。

（但好像不去重也能过？没试）

#### Code

```cpp
for (int i = 1; i <= n; i++)
	if (a[i] != a[i - 1]) {
		cnt++;
		c[cnt] = a[i];
	}
for (int len = 1; len < cnt; len++)
	for (int i = 1; i + len <= cnt; i++) {
		int j = i + len;
		if (c[i] == c[j]) dp[i][j] = dp[i + 1][j - 1] + 1;
		else dp[i][j] = min(dp[i][j - 1], dp[i + 1][j]) + 1;
	}
```

---

## 作者：Need_No_Name (赞：1)

# Solution for CF114D

## Step1：分析题意

题意：给定一个 $int$ 类型的序列，可以一次由 $i$ 到 $j$ 一次变换成一种数字。现在问至少要多少次操作，使得序列变成一种数字。

## Step2：思路

Hmm...看看题，是从 $i$ 到 $j$ 能进行批次变化，那么这...应该是...区间 dp 吧！这样子，除了区间 dp 还有什么呢？

## Step3：转移方程

既然选择了 $dp$ ，那么就来搞一下转移方程吧！

先贴为敬：

```
dp[i][j]=dp[i+1][j-1]+1;//当a[i]与a[j]相等的时候
dp[i][j]=min(dp[i+1][j],dp[i][j-1])+1;//其他情况
```
那么，屏幕前 ~~帅气的~~ 做过一些区间dp的小盆友就会问了：啊，为什么不先从 $i$ 到 $k$ ，再从 $k+1$ 到 $j$ 这么不断将大区间变成小区间这么枚举呢？比如说典型的石子合并呢？

枚举分割点的做法一定是对的，但是没有必要的。我们可以发现，将相同的序列合并成为`1`个之后，也就是剩下的序列中每一个元素都是相同的时候，我们就可以发现方案数只用一个个加`1`就行了。也便没有必要去将 $O(n^2)$ 变成 $O(n^3)$ 了。

## Step4：话不多说上代码

```cpp
//区间dp模板题目 
//dp[i][j]表示使i到j的颜色都一样的次数 
#include<bits/stdc++.h>
using namespace std;
const int N=5050;
int a[N]={0};
int dp[N][N];
int ans=0;
int n;
signed main()
{
	cin>>n;
	int cnt=0;
	int x;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		if(a[cnt]==x)
		{
			continue;
		}
		a[++cnt]=x;
	}
	//上面的循环是剔除那些完全相等的方块 ，至于为什么，那就看下面的转移方程。 
	for(int i=cnt;i>=1;i--)//去枚举停止的点 
	{
		for(int j=i+1;j<=cnt;j++)//枚举起始点 
		{
			if(a[i]==a[j])//如果发现有两个相同 
			{
				dp[i][j]=dp[i+1][j-1]+1;//那么就将从i+1，j-1继续转移。这里解答一个问题；为什么不从i~k,k+1~j这么枚举。因为其中在上面的循环里面剔除了连续相同的项，所以就不用将大区间分成两个小区间
				 
			}
			else
			{
				dp[i][j]=min(dp[i+1][j],dp[i][j-1])+1;//其他就不用说了，就是在从i+1~j的方案和i~j-1之间取min值再+1 
			}
		}
	}
	cout<<dp[1][cnt]<<endl;//输出 
}
//感谢seantheone(ZSH)给予的思路 

```

鸣谢：感谢seantheone提供的初始思路

























-+



---

## 作者：pomelo_nene (赞：1)

$\ \ \ \ \ \ \ $[luogu](https://www.luogu.com.cn/problem/CF1114D)

$\ \ \ \ \ \ \ $实际上这是个模板。考虑枚举长度和长度区间，区间枚举划分点，这实际上是 $O(n^3)$ 的。只能优化区间划分点。每次加入的话，其实是不需要枚举划分点的。把序列 `unique` 掉，每次加入就不会有相同的影响了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,dp[5005][5005],a[5005],len;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)	scanf("%d",&a[i]);
	len=unique(a+1,a+1+n)-a-1;
	for(int i=1;i<=len;++i)
	{
		for(int l=1,r=i+1;r<=len;++l,++r)
		{
			if(a[l]==a[r])	dp[l][r]=dp[l+1][r-1]+1;
			else	dp[l][r]=min(dp[l+1][r],dp[l][r-1])+1;
		}
	}
	printf("%d",dp[1][len]);
	return 0;
}
```

---

## 作者：decoqwq (赞：1)

$D$

看到数据范围，考虑区间$dp$

两个区间合并的转移方程是$dp[l][r]=min(dp[l][r],dp[l][k]+dp[k][r]+1);$(两边不同)

但是这样是$O(n^3)$的，考虑优化

容易想到直接枚举长度，然后和左右合并即可

复杂度$O(n^2)$

其实这种区间$dp$很套路的...

```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[5005][5005],n,a[5005],tot,b[5005];
int main() 
{
	cin>>n;
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&a[i]);
		if(a[i]==a[i-1]) 
		{
			continue;
		}
		else 
		{
			b[++tot]=a[i];
		}
	} 
	n=tot;
	for(int len=1;len<n;len++) 
	{
		for(int l=1;l+len<=n;l++) 
		{
			int r=l+len;
			if(b[l]==b[r]) 
			{
				dp[l][r]=dp[l+1][r-1]+1;
			}
			else 
			{
				dp[l][r]=min(dp[l+1][r]+1,dp[l][r-1]+1);
			}
		}
	}
	cout<<dp[1][n];
}
```
[这一场cf的题解，打个广告](https://decorationqwq.com/archives/324/)

---

## 作者：Daniel_7216 (赞：0)

为什么 CF 有这么多板题啊，我十五分钟内轻松搞定，结果一看 dalao 写的题解竟然跟我写的这么像还比我简洁，我真的直接给大佬 orz 了，但是总觉得我做题时碰到的一些小障碍楼下好像并没有解释特别详细，所以我就再发一个题解让后来人能清楚一点吧（~~主要是来水题解~~）

### 一、预处理：

预处理的有无无疑是这个题 TLE 或 AC 的关键之一。判断与一个位置 $p$ 的颜色连通块的朴素方法显然是从左右分别向前走到第一个不同的颜色，但是复杂度极端情况就是 $O(N)$，简直就在 TLE 的边缘上疯狂试探啊。所以，我们可以在输入时把每个连通块都缩成一格，不仅可以为 $O(N^2)$ 的算法打基础，而且等状态转移的时候你就会直呼真香。

### 二、关于连通块
预处理过后是没有连通块的，即当且仅当区间 $[l,r]$ 有 $l = r$ 时是连通块。通过数学归纳法可以证明如下结论：

- 若 $c_l=c_r$，那么把 $[l,r]$ 涂色所需步数就是把 $[l+1,r-1]$ 涂色所需步数加一。

证：

设结论对 $l + k=r$ 成立。对于预处理之后的方块，当 $k = 2$ 时显然是成立的，即染成 $l+1$ 上的颜色。

同理，当 $k = 3$ 时，$[l,l+2]$ 已被证明是连通的，所以此时只用把 $l+3$ 染上色。

由此我们可以得出，$[l,l+k-1]$ 是连通的，只需要把 $l+k$ 染成相同色。

证毕。

- 若 $c_l≠c_r$，那么把 $[l,r]$ 涂色所需步数就是把 $[l+1,r]$ 涂色所需和 $[l,r-1]$ 涂色所需的最小值加一。

证明与上个结论相同，但是因为 $c_l≠c_r$，所以就会有两种染色决策。

### 三、初始化和目标
根据二的结论，初始化之后就满足合并的合法，所以不用像石子合并那道题一样分别初始化为 $0$ 和无穷。目标是把 $1$ 到 $N$ 合并，即：$d_{1,N}$。

### 四、代码
这是带注释版的，为了方便大家~~复制~~学习，这还有[无注释版](https://www.luogu.com.cn/paste/db8vhjap)
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int r, n, c[5001], idx = 0, a, d[5001][5001];
void DP(int l, int r){
	if (c[l] == c[r]){//因为已经有预处理和顺推，所以[l,r]的最大子区间[l+1,r-1]是颜色联通块(但是与c[l]和c[r]不同)，这时只需要染一次色。 
		d[l][r] = d[l + 1][r - 1] + 1; 
	}else{//如果不同，那么根据前面的推测，[l,r-1]和[l+1,r]也是颜色联通块，取最小代价再加一即可 
		d[l][r] = min(d[l][r - 1], d[l + 1][r]) + 1; 
	}
}
int main(){
	scanf("%d", &n);
	//预处理，因为判断颜色联通块在极端情况下是O(N)，所以提前把一个联通块缩成一个格 
	for (int i = 1; i <= n; i++){
		scanf("%d", &a);
		if (a != c[idx]){
			idx++;
			c[idx] = a;
		}
	}
	n = idx;
	//开始套路
	for (int i = 1; i < n; i++){ //枚举合并的跨度
		for (int l = 1; l <= n - i; l++){ //左端点 
			r = l + i;//右端点
			DP(l, r); 
		} 
	}
	printf("%d", d[1][n]);
	return 0;
}
```
题目不难，蒟蒻也没有什么创新，但是看在我写得~~这么多~~还算多份上管理员给过吧 QAQ

---

## 作者：_Dreamer_ (赞：0)


[传送门](https://www.luogu.com.cn/problem/CF1114D)

是一道比较清新的 区间 $DP$

可以很快速的糊出来 $ dp[\,i\,][\,j\,] = $ 把区间 $[\,i\,,\,j\,]$ 染成同一个颜色的最小步数

考虑转移
$$
\begin{cases}
dp[\,i\,][\,j\,]=dp[\,i+1\,][\,j-1\,]+1,&a[\,i\,]=a[\,j\,]\\
dp[\,i\,][\,j\,]=\max (dp[\,i+1\,][\,j\,],dp[\,i\,][\,j-1\,])+1,&a[\,i\,]\neq a[\,j\,]
\end{cases}
$$
 含义是

- 如果当前区间左右端点一致  直接涂一次就可以了
- 如果左右端点不一致  则需要涂两次

要注意 在读入时要把相同的缩到一起

```cpp

#include<bits/stdc++.h>
using namespace std;
int dp[5005][5005];
int n;
int a[5005];
int main()
{
	scanf("%d",&n);
	memset(dp,0x3f,sizeof dp);
	int last=-1;
	int tot=0;
	for(int i=1;i<=n;i++)
	{
		int x;scanf("%d",&x);
		if(x!=last)a[++tot]=x;
		last=x;
	}
	for(int i=1;i<=tot;i++)dp[i][i]=0;
	for(int len=2;len<=tot;len++)
	{
		for(int i=1;i+len-1<=tot;i++)
		{
			int j=i+len-1;
			if(a[i]==a[j])
				dp[i][j]=min(dp[i][j],dp[i+1][j-1]+1);
			else 
				dp[i][j]=min(dp[i+1][j],dp[i][j-1])+1;
		}
	}
	printf("%d",dp[1][tot]);
	return 0;
}

```

---

## 作者：E1_de5truct0r (赞：0)

## 题意

首先，定义一串数如果这串数字全部相同，那么这串数被称为“联通串”。现在给定一个串，每次可以把一个联通串中每一个数变成任意数字，求最少把整个串变成联通串的次数。

## 算法

首先这显然是在区间里面操作（~~搞事情~~），所以我们要使用区间DP解决此题。

定义 $dp[i][j]$ 表示从 $i$ 到 $j$ 变成联通串的最小刷的次数。那么分成两种情况：

- $a[i] = a[j]$：我们可以把 $[i + 1, j - 1]$ 的数刷成联通串，再刷一次。所以得到：$dp[i][j] = dp[i + 1][j - 1] + 1$。

- $a[i] \ne a[j]$：我们选择把 $[i, j - 1]$ 刷成联通串再刷一次 $a[j]$，或者把 $[i + 1, j]$ 刷成联通串，再刷一次 $a[i]$。

所以我们得到转移方程。

### 但是！

有可能会出现这种情况：```1 1 1 1 1```，这时我们-从 $dp[2][3]$ 转移到 $dp[1][4]$ 时其实是不需要 $+ 1$ 的，但是我们的程序不能做到。所以我们要把一开始的联通串变成一个数，这样就可以有效的避免这种情况。

那么我们就解决了这道题。代码不是很复杂，但是各种情况要考虑全。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[5005][5005],a[5005],tot; //tot记录非联通串的数字个数
signed main()
{
	int n; cin>>n>>a[++tot];
	for(int i=2;i<=n;i++)
	{
		int x; cin>>x;
		if(x==a[tot]) continue; //如果能和上一个数组成联通串那么不选
		else a[++tot]=x;
	}
	//普通区间DP
	for(int i=2;i<=tot;i++)
	{
		for(int l=1;l+i-1<=tot;l++)
		{
			int r=l+i-1;
			if(a[l]==a[r]) dp[l][r]=dp[l+1][r-1]+1;
			else dp[l][r]=min(dp[l+1][r],dp[l][r-1])+1;
		}
	}
	cout<<dp[1][tot]; //输出从 1 到 tot 的最小次数
	return 0;
}
```

---

## 作者：wrzSama (赞：0)

## 题意
给定一行 $n$ 个方块与它们的颜色，规定连续且颜色相同的方块属于一个连通分量，每次操作可以将一个连通分量内的方块改成同一颜色，问至少需要几次操作才能将所有方块改成同一颜色。
## 思路
由题意我们可知这道题我们只需要在输入时把每个连通分量的颜色记录下来，由短到长计算出依次计算出每个区间的最小更改次数，用区间DP即可。 $dp_{i,j}$ 表示从第 $i$ 个连通分量到第 $j$ 个连通分量改成同一颜色的最小更改数量。如果首尾的连通分量相同，即 $c_i = c_j$ ， $dp_{i,j}$ 就可以从 $dp_{i+1,j-1}$ 转移，为它的值加$1$。如果首尾两个连通分量颜色不相同，即 $c_i \ne c_j$ ，就需要从 $dp_{i+1,j}$ 或 $dp_{i,j-1}$ 来转移，为它们的较小值加$1$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c[5005],dp[5005][5005]; //dp[i][j]表示从第i个连通分量到第j个连通分量改成同一颜色的最小更改数量
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&c[i]);
		if(c[i]==c[i-1])
		{
			n--;
			i--; //把相同相连的方块记录在同一个连通分量里
		}
	}
	for(int len=1;len<n;len++) //枚举区间长度
	{
		for(int i=1;i+len<=n;i++)
		{
			int j=i+len;
			if(c[i]!=c[j]) dp[i][j]=min(dp[i+1][j],dp[i][j-1])+1; //若首尾连通分量不同,从dp[i+1][j]或dp[i][j-1]转移
			else dp[i][j]=dp[i+1][j-1]+1; //首尾相同,直接从dp[i+1][j-1]转移
		}
	}
	printf("%d",dp[1][n]); //输出全部改成一样颜色需要的代价
	return 0;
}
```

---

## 作者：Fa1thful (赞：0)

### 题意：
给定一些颜色的方块，可以一次从一个位置变颜色，问多少次能把这列方块变成一个颜色。
### 分析：
这道题中的表示都在疯狂暗示区间 `dp` ，所以我们考虑 $dp[i][j]$ 表示从 `i`到`j`变成相同的颜色的最小步数。那么分为两种情况：1.扩大的区间的两个颜色相同。2.不相同。继而我们又有了转移方程：
```cpp
if (a[i] == a[j]) dp[i][j] = dp[i + 1][j - 1] = 1;       //相同，那么就是将里面的全刷成a[i]的颜色 
dp[i][j] = min(dp[i + 1][j] + 1, min(dp[i][j - 1] + 1, dp[i][j]));       //不相同，那么将小区间都刷成a[i]或a[j]的颜色 
```
发现问题了！为什么这次不用像以前的合并石子一样枚举分割点，而是一次区间增加 `1` 呢？不仅仅是因为不支持 $O(n^3)$吧！

我们可以想一想，枚举分割点的做法一定是对的，因为这题正解的增长方式也是包含在分割点的一种情况里的，但是真的有必要吗？我们很容易发现只要序列的颜色各不相同，那么就一定可以每次增长`1`。所以我们前面判断颜色就起了另一个作用：把不能增长`1`的情况先解决了。
### 代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
const int NR = 5050;
int a[NR];
int dp[NR][NR];
int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		if (!i) continue;
		if (a[i] == a[i - 1])        //初始化a的情况 
		{
			i--;
			n--;
		}
	}
	memset(dp, 0x7f, sizeof(dp));       //取最小值 
	for (int i = 1; i <= n; i++) 
	{
		dp[i][i] = 0;      //如果i到i合并，就一个数字，一种颜色，方案数为0 
	}
	for (int len = 2; len <= n; len++)       //区间长度 
	{
		for (int i = 1; i + len - 1 <= n; i++)      //枚举起点 
		{
			int j = i + len - 1;     //终点 
			if (a[i] == a[j]) dp[i][j] = dp[i + 1][j - 1] + 1;
			dp[i][j] = min(dp[i + 1][j] + 1, min(dp[i][j - 1] + 1, dp[i][j]));  //转移 
		}
	}
	cout << dp[1][n] << endl;
	return 0;
}
```


---

