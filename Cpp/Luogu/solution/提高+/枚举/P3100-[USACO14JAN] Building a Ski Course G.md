# [USACO14JAN] Building a Ski Course G

## 题目描述

Farmer John is helping to turn his large field into a ski course for the upcoming winter Moolympics.  The field has dimensions M x N (1 <= M,N <= 100), and its intended final composition is described by an M x N grid of characters like this:

RSRSSS
RSRSSS
RSRSSS
Each character describes how the snow in a unit square of the field should be groomed: either 'R' for 'rough' or 'S' for 'smooth' (the Moolympics organizers think that a course is more interesting if it has a mixture of rough and smooth patches).

To build the desired course, Farmer John plans to modify his tractor so that it can stamp any B x B patch of the field (B <= M, B <= N) with either entirely smooth snow or entirely rough snow.  Since it takes a long time to reset the tractor between each of these stamps, FJ wants to make B as large as possible.  With B = 1, he can clearly create the desired ski course by stamping each individual square with either R or S, as intended.  However, for larger values of B, it may no longer be possible to create the desired course design.  Every unit square of the course must at some point be stamped by FJ's tractor; it cannot be left in its default state.

Please help FJ determine the largest possible value of B he can successfully use.

滑雪场的设计图是一个M\*NM x N (1 <= M,N <= 100)的矩阵，每个格子里用一个字母R（表示粗糙）或者S（表示平整）。


比如：


RSRSSS

RSRSSS

RSRSSS

农民约翰的拖拉机每次可以将一块B\*B (B <= M, B <= N)的区域全部标记B\*B (B <= M, B <= N)的R或者S，他希望B能够尽量地大。一个格子可以被多次标记，下一次标记能够覆盖前一次标记，每个格子可以都至少被标记一次。


## 说明/提示

FJ can stamp a rough patch spanning columns 1-3, followed by a smooth patch spanning columns 2-4, then a rough patch spanning columns 3-5, and finally a smooth patch spanning columns 4-6.


## 样例 #1

### 输入

```
3 6 
RSRSSS 
RSRSSS 
RSRSSS 
```

### 输出

```
3 
```

# 题解

## 作者：姬小路秋子 (赞：5)

一道好（考智商）题。

看到求最大，我们不难想到用二分。如果你是这样想的话，那么**恭喜你！**

这样行不通。

我们不妨换种思路想（很难想到，对于我来说）。假设答案是k，那么读入数据（也就是最终矩阵）中必然有一个边长至少为k的全由同一种颜色组成的正方形，不然你最后一次进行标记时这个k*k的正方形应该在哪里。

然后我们把这个正方形中的所有点标记为任意颜色（即把它看做R，S通用）。为什么呢？这样做我们相当于撤销了当前的最后一次操作，而之前的操作又不确定这个位置标记的到底是哪种颜色。

当然，为了确保答案最优，这个正方形应该是最大的。

我们继续进行撤销操作（也就是逆推），然后继续求当前的最大正方形，直到没有点还有某种确定的颜色（意思是所有点都被标记了）。对于每一次求得的正方形边长取个min就是答案。

当然，最坏情况是每次找到的正方形边长都很小（甚至都为1），那么我们就要加个“可行性”剪枝了————在找了很多次正方形后带着当前得到的答案直接退出（事实证明你至少需要找不到2000一点的次数）

**PS：**一个点不能同时作为两个正方形的起始点（我用的是右下角）

上代码：

```c
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,sum,cnt,now,ans,l,r,f[101][101],g[101][101],mp[101][101],a[101][101];
char s[1010];
int main(){
	scanf("%d%d",&n,&m);
	ans=min(n,m);
	for(i=1;i<=n;i++){
		scanf("%s",s+1);
		for(j=1;j<=m;j++)
		 if(s[j]=='R')a[i][j]=1;
		  else a[i][j]=2;
	}
	now=n*m;
	while(now){
		sum=0;
		for(i=1;i<=n;i++)
		 for(j=1;j<=m;j++){
		 	f[i][j]=min(f[i-1][j],min(f[i][j-1],f[i-1][j-1]))+1;
		 	g[i][j]=min(g[i-1][j],min(g[i][j-1],g[i-1][j-1]))+1;
		 	if(a[i][j]==1)g[i][j]=0;
		 	if(a[i][j]==2)f[i][j]=0;
		 	if(!mp[i][j]&&max(f[i][j],g[i][j])>sum){
		 		sum=max(f[i][j],g[i][j]);
		 		l=i;r=j;
		 	}
		 }
		mp[l][r]=1;
		ans=min(ans,sum);
		for(i=l-sum+1;i<=l;i++) 
		 for(j=r-sum+1;j<=r;j++){
		 	if(a[i][j])now--;
		 	a[i][j]=0;
		 }
		cnt++;
		if(cnt>5000)break; 
	}
	printf("%d",ans);
}
```

---

## 作者：ccjjxx (赞：1)

# 题目翻译

### 题目描述

现有一个 $N\times M$ 的空矩阵，初始没有任何东西。

你初始可以选定一个 $B\times B$ 的正方形，把它全部涂成字母 `R` 或者 `S`，每次填涂会覆盖之前的字母，并且以后都必须以 $B$ 为边长填涂。

给定一个目标矩阵，问 $B$ 最大不超过多少可以使得这个空矩阵变成目标矩阵？

### 输入格式

第 $1$ 行两个正整数 $N,M$；

第 $2$ 行到第 $N+1$ 行，每行 $M$ 个字符表示目标矩阵。

### 输出格式

一行。一个正整数 $B$ 表示答案。

### 提示

$N,M\le 100$。


# Solution

既然这个矩阵是类似于栈一样地一层一层叠起来，那么我们不妨按照从栈顶到栈底的顺序逆序把涂层一层层揭开。

对于每次操作，我们可以记录当前最大的同字母正方形，注意如果一个点之前已经被揭开，那么它现在应该没有颜色，可以随意使用。

因为一个大正方形可以从许多个 $B\times B$ 填得，因此答案就是每次查询到的最大边长的最小值。

网上有人说要卡时间卡循环次数，我感觉不用，随随便便就过了？

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[101][101];
int f[101][101],g[101][101];
inline int min(int x,int y,int z)
{
	return min(x,min(y,z));
}char s[101];
bitset<101>vis[101];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>(s+1);
		for(int j=1;j<=m;j++)if(s[j]=='R') a[i][j]=1;
	}
	int ccnt=n*m;
	int ans=0;
	while(ccnt)
	{
		int mx=0;int l=0,r=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				f[i][j]=min(f[i-1][j],f[i][j-1],f[i-1][j-1])+1;
				g[i][j]=min(g[i-1][j],g[i][j-1],g[i-1][j-1])+1;
				if(a[i][j]==0)f[i][j]=0;
				if(a[i][j]==1)g[i][j]=0;
				if(!vis[i][j]&&max(f[i][j],g[i][j])>mx)
					mx=max(f[i][j],g[i][j]),l=i,r=j;
			}
		}
		vis[l][r]=1;
		ans=min(ans,mx);
		for(int i=l-mx+1;i<=l;i++)
		{
			for(int j=r-mx+1;j<=r;j++)
			{
				if(a[i][j]>-1)--ccnt;
				a[i][j]=-1;
			}
		}
	}cout<<ans;
}
```

---

