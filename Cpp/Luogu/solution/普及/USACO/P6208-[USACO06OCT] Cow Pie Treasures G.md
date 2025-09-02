# [USACO06OCT] Cow Pie Treasures G

## 题目描述

奶牛们制作了一些藏有金币的馅饼，并把它们排成了一个 $r$ 行 $c$ 列的矩阵。现在，你需要从坐标为 $(1,1)$ 的馅饼旁移动到坐标为 $(r,c)$ 的馅饼旁。对于每次移动，你必须向右移动一列，并且行数的变动不能超过 $1$。即如果你处于坐标为 $(x,y)$ 的馅饼旁，你只能移动到坐标为 $(x-1,y+1)$，$(x,y+1)$ 或 $(x+1,y+1)$ 的馅饼旁。在一个馅饼旁停留时，你可以拿走其中所有的金币。当然，你一定不愿意中途离开矩阵而放弃这些金币。

奶牛们把标有矩阵中每一块馅饼所藏金币数的表格交给了你。你想知道按照以上规则，自己最多能拿到多少金币。

## 说明/提示

**【数据范围】**

对于 $100\%$ 的数据，$1\le r,c\le 100$，$1\le t\le 25$。

------------

**【样例说明】**

![](https://cdn.luogu.com.cn/upload/image_hosting/pgw19uqm.png)

样例给出的矩阵如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/hwhzq9oy.png)

这是一种合法的移动方式。你可以拿到 $47$ 枚金币。

![](https://cdn.luogu.com.cn/upload/image_hosting/sdyxlpv5.png)

在这个矩阵中你最多能拿到 $50$ 枚金币，路线如图所示。

## 样例 #1

### 输入

```
3 7
6 5 3 7 9 2 7
2 4 3 5 6 8 6
4 9 9 9 1 5 8```

### 输出

```
50```

# 题解

## 作者：WaltVBAlston (赞：19)

~~日常刷新题，维护自己在小伙伴们中的微信。~~

这道题的题意很明显，连动态转移方程都给你了：

```
dp[j][i]=max(dp[j-1][i-1],max(dp[j+1][i-1],dp[j][i-1]))+a[j][i];
```
感觉莫名很像一道叫做：红牌 的题目。

```
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n,m;
int dp[1001][1001];
int a[1001][1001];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	dp[1][1]=a[1][1];
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			dp[j][i]=max(dp[j-1][i-1],max(dp[j+1][i-1],dp[j][i-1]))+a[j][i];
		}
	} 
	printf("%d",dp[n][m]);
	return 0;
}
```
慢着，如果你直接把这份代码交上去等待着你的
（我相信你不会那么干的）那么等待着你的就是：WAWAWAWAWA。没错，五个点。

到底是为什么呢？

我们来分析一下：把这张地图看成一个四边形，那么我们可以发现，左上点（起点），到右下点（终点），它们练成的斜线以下的部分，是到达不了的（读题就很容易看出）。

所以我们在for的边界应该是这样的：

```
j<=i&&j<=n;
```
AC代码如下：

```
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n,m;
int dp[1001][1001];
int a[1001][1001];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	dp[1][1]=a[1][1];
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n&&j<=i;j++)
		{
			dp[j][i]=max(dp[j-1][i-1],max(dp[j+1][i-1],dp[j][i-1]))+a[j][i];
		}
	} 
	printf("%d",dp[n][m]);
	return 0;
}
```

记得一定要先枚举列，再枚举行！

（第一篇题解，大家多多资瓷）

---

## 作者：do_while_false (赞：3)

看到题目，很容易想到这是道DP。

【大概思路】

根据题意，$a_{i,j}$ 可以转移到 $a_{i-1,j+1},a_{i,j+1}$ 和 $a_{i+1,j+1}$

我们倒过来讨论，即可发现 $a_{i,j}$ 可以从 $a_{i-1,j-1},a_{i,j-1}$ 和 $a_{i+1,j-1}$ 转移而来。

我们只要另开一个 $f$ 数组，将 $f_{i-1,j-1},f_{i,j-1}$ 和 $f_{i+1,j-1}$ 中的最大值和 $a_{i,j}$ 一起加到 $f_{i,j}$ 即可。

状态转移方程即为:

$$f_{i,j}=\max\begin{cases}f_{i-1,j-1}\\f_{i,j-1}\\f_{i+1,j-1}\end{cases}+a_{i,j}$$

初始条件则为:

$$f_{1,1}\gets a_{1,1}$$

【具体代码】

```cpp
#include<bits/stdc++.h>
#define MAXN 100 + 10 
using namespace std;
int a[MAXN][MAXN],f[MAXN][MAXN],r,c;
inline int read() {//快读 
	int r=0;bool flag=true;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=false;ch=getchar();}
	while(ch>='0'&&ch<='9'){r=(r<<3)+(r<<1)+(ch^48);ch=getchar();}
	return flag==true?r:~r+1;
}
int main(void) {
	memset(f,-0x3f3f3f,sizeof(f)); 
	r=read();c=read();
	for(int i=1;i<=r;i++) 
		for(int j=1;j<=c;j++) 
			a[i][j]=read();//读入 
	f[1][1]=a[1][1];//初始化 
	for(int j=2;j<=c;j++)
        for(int i=1;i<=r;i++)
            f[i][j]=a[i][j]+max(f[i-1][j-1],max(f[i][j-1],f[i+1][j-1]));//DP的状态转移方程 
    printf("%d\n",f[r][c]);//输出 
	return 0;
}
```

---

## 作者：DreamFox (赞：3)

# 前言
虽然这是一道裸的$DP$，但由于我的水平过低，只能用记搜$AC$这道题。
# 本题思路
由于纯$DFS$的复杂度为$O(3^c)$，稳稳地$TLE$，所以我们要对此做些优化。

纯$DFS$会走很多不必要的路径，因此，我们可以用一个数组储存最大值，如果现有的值比这个最大值小，那么就停止搜索，否则就更新最大值，并继续搜索。

亲测最慢测试点小于$200ms$，可以稳稳地$AC$这道题。

$AC$ $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[101][101],h[101][101];
int n,m,maxx;
void dfs(int i,int j,int num)
{
	if(i>n)return;
	if(j>m)return;
	if(i<1)return;
	if(j<1)return;
	if(i==n&&j==m)
	{
		maxx=max(num,maxx);
		return;
	}
	if(h[i][j])
	{
		if(h[i][j]>num)
		return;
	}
	h[i][j]=num;
	dfs(i-1,j+1,num+dp[i-1][j+1]);
	dfs(i+1,j+1,num+dp[i+1][j+1]);
	dfs(i,j+1,num+dp[i][j+1]);
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	cin>>dp[i][j];
	dfs(1,1,dp[1][1]);
	cout<<maxx<<endl;
	return 0;
}
```


---

## 作者：monstersqwq (赞：2)

#### 题目大意

给出一个 $r \times c$ 的矩阵 $a$，选择一条路径从 $a_{1,1}$ 到达 $a_{r,c}$ 使得路径上的数字之和最大。

行走要求：从 $a_{i,j}$ 可以到达 $a_{i-1,j+1},a_{i,j+1},a_{i+1,j+1}$。

#### 思路：

一拿到这道题，有经验的 OIer 们马上就能反应出这是一道十分经典的 dp 裸题。（不懂dp的可以转弯去[这里](https://baike.baidu.com/item/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/529408?fr=aladdin)（仅仅是一个普及，有兴趣的可以去问老师或者教练））

看到从 $a_{i,j}$ 可以到达 $a_{i-1,j+1},a_{i,j+1},a_{i+1,j+1}$ 这个条件，我们就可反着推出 $a_{i,j}$ 只能由前一列，行距不超过一的格子到达，即 $a_{i-1,j-1},a_{i,j-1},a_{i+1,j-1}$。

拥有了这些条件，我们就可以得到状态转移方程：$dp_{i,j} \gets \max(dp_{i-1,j-1},dp_{i,j-1},dp_{i+1,j-1})+a_{i,j}$。（$dp_{i,j}$ 记录从 $a_{1,1}$ 到 $a_{i,j}$ 的所有路径中数字和最大的那条的数字和）

进行 dp 的起始条件：$dp_{1,1} \gets a_{1,1}$。

有了这些条件，就可以开始 dp 了。

tips：

1：dp 时要先枚举列再枚举行，不然会导致调用的东西还没有计算，然后错误。

2：可以直接从第二列开始枚举，因为第一列除了 $a_{1,1}$ 以外都不可能到达，而 $dp_{1,1}$ 已经初始化过了。（虽然不这么做也完全没有问题）

代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
int a[105][105],r,c,dp[105][105];
int main()
{
	cin>>r>>c;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			cin>>a[i][j];
	dp[1][1]=a[1][1];
	for(int j=2;j<=c;j++)
		for(int i=1;i<=r;i++)
			dp[i][j]=max(dp[i-1][j-1],max(dp[i][j-1],dp[i+1][j-1]))+a[i][j];
	cout<<dp[r][c]<<endl;
	return 0;
}
```

别急，还没结束，如果你把上面的代码交上去的话
就会看到5个鲜红的 WA [戳我](https://www.luogu.com.cn/record/31750245)。

为什么呢？因为在 $a_{1,1},a_{2,2} \dots a_{\min(r,c),\min(r,c)}$ 这条斜线以左侧的点，全部不可能达到（原理大家都应该很清楚，这里就不再赘述了），而如果把这些点也计算，最后计算正解的时候就会出现~~玄学~~错误，导致那五个 WA 的产生。

于是，对于 $j$ 列，我将行的循环条件从 $i \leq r$ 改为了 $i \leq r$ 且 $i \leq j$，这样就能不计算不能到达的点，从而 AC。

代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
int a[105][105],r,c,dp[105][105];
int main()
{
	cin>>r>>c;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			cin>>a[i][j];
	dp[1][1]=a[1][1];
	for(int j=2;j<=c;j++)
		for(int i=1;i<=j&&i<=r;i++)
			dp[i][j]=max(dp[i-1][j-1],max(dp[i][j-1],dp[i+1][j-1]))+a[i][j];
	cout<<dp[r][c]<<endl;
	return 0;
}
```


---

## 作者：LongDouble (赞：2)

一道 **移动类 DP** 入门题。

题目描述说，$(x,y)$ 可以移动到 $(x-1,y+1)$，$(x,y+1)$ 或 $(x+1,y+1)$。

换句话说，$(x,y)$ 只可能从 $(x-1,y-1)$，$(x,y-1)$ 或 $(x+1,y-1)$ 过来。

但是，我们希望金币越多越好。

所以，从 $(x-1,y-1)$，$(x,y-1)$ 和 $(x+1,y-1)$ 中找一个金币最多的就行。

得到状态转移方程：

$$dp(x,y)=\max(dp(x-1,y-1),dp(x,y-1),dp(x+1,y-1))+t(x,y)$$

在 $dp(x,y)$ 算出之前，$dp(x-1,y-1)$，$dp(x,y-1)$ 和 $dp(x+1,y-1)$ 肯定是要算好的。

所以要先枚举列，再枚举行。

另外要把 dp 数组初始化成一个很小的数。（就是这里让我调了很久。）

原因：比如说数据如下时：

```
3 4
1 1 1 1
1 1 1 1
1 25 1 1
```

如果 dp 数组初始值为 0，状态转移时 $dp(3,2)$ 就会变成 25，从而导致后面出错。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int r, c, t[110][110], dp[110][110];

int main()
{
	memset(dp, -0x3f, sizeof dp);
	scanf("%d%d", &r, &c);
	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++)
			scanf("%d", &t[i][j]);
	dp[1][1] = t[1][1];
	for (int j = 2; j <= c; j++)
		for (int i = 1; i <= r; i++)
			dp[i][j] = t[i][j] + max(dp[i - 1][j - 1], max(dp[i][j - 1], dp[i + 1][j - 1]));
	printf("%d\n", dp[r][c]);
	return 0;
}
```
其实也可以逆推，方法和顺推类似，可以试着做一下。

---

