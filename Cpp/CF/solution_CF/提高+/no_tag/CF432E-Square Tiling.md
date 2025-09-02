# Square Tiling

## 题目描述

You have an $ n×m $ rectangle table, its cells are not initially painted. Your task is to paint all cells of the table. The resulting picture should be a tiling of the table with squares. More formally:

- each cell must be painted some color (the colors are marked by uppercase Latin letters);
- we will assume that two cells of the table are connected if they are of the same color and share a side; each connected region of the table must form a square.

Given $ n $ and $ m $ , find lexicographically minimum coloring of the table that meets the described properties.

## 样例 #1

### 输入

```
1 3
```

### 输出

```
ABA
```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
AA
AA
```

## 样例 #3

### 输入

```
3 4
```

### 输出

```
AAAB
AAAC
AAAB
```

# 题解

## 作者：zplqwq (赞：2)

考虑 贪心 + 半个 dp

首先贪心策略

- 我们每次找到当前能放进去的边长最大的正方形，把它放进去，并使字典序尽量地小即可。

然后代码分三个部分。

第一个部分 `dfs` 

- 主要目的是以我们在后面的随机切入的点位顶点为顶点，向外扩张一个正方形。

```
int dfs(int x,int y)
{
	if(dp[x][y]) return dp[x][y];
	for(int i=1;i<=26;i++)
	{
		if(dp[x-1][y]!=i and dp[x][y-1]!=i and dp[x+1][y]!=i and dp[x][y+1]!=i) return i;
	}
}
```

第二个部分 `work`

- 主要的目的是找到一个点，得到这个点的最优解并标记答案。

```
void work(int l,int c)
{
	for(int i=1;i<=l;i++)
	{
		for(int j=1;j<=c;j++)
		{
			if(dp[i][j]) continue;
			int tmp;
			tmp=dfs(i,j);
			int qwq=0;
			while(dfs(i,j+qwq)==tmp and i+qwq<=l and j+qwq<=c) qwq++;
			for(int k=i;k<i+qwq;k++)
			{
				for(int o=j;o<j+qwq;o++)
				{
					dp[k][o]=tmp;
				}
			}
		}
	}
}
```

第三个部分 `output`

- 即输出整张地图。

```
void output(int l,int c)
{
	for(int i=1;i<=l;i++)
	{
		for(int j=1;j<=c;j++)
		{
			cout<<(char)(dp[i][j]+'A'-1);
		}
		cout<<endl;
	} 
}
```


---

## 作者：_ReClouds_ (赞：0)

最近没怎么认真复健，人变蠢了，看了几篇题解发现根本看不懂啊，那很有生活了。

自己搞懂之后来写一篇。

------

这题目要是往每次填一个正方形的方向想那感觉很难做出来，一大堆的分类讨论根本搞不完。

既然它要求字典序最小，我们不如直接往贪心的方向想。其实这样想就很简单了：我们按照顺序枚举每个位置，然后根据已有的限制尽可能地填入最小的字母，再根据这个字母去添加限制即可。

现在来考虑如何填一个字母。

首先，这个位置上下左右的字母组成的集合的 $\operatorname{mex}$ 是一定可以填的，如果这个位置不能填入更小的字母，那么我们直接填入这个集合的 $\operatorname{mex}$ 即可。

什么情况下这个位置能够填入更小的字母呢？我们考虑前一个位置的字母 $c$，如果 $c$ 小于上述 $\operatorname{mex}$，并且当前位置上方的字母不为 $c$，那么我们就可以考虑扩展前一个位置对应的正方形。如果能够扩展成功，当前位置填入 $c$ 就是最优的，同时我们也要把扩展后的正方形相对于原正方形新添的位置也填入相同的字母。

具体的实现可以看代码。

[代码实现。](https://codeforces.com/contest/432/submission/310362866)

---

## 作者：_Clown_ (赞：0)

## 概述
|题号|难度|$AC$时间及记录|
| :----: | :----: | :----: |
|$\texttt{CF432E}$|$\texttt{CF难度:2300}$|[$\texttt{On 2020/11/02}$](https://www.luogu.com.cn/record/41067349)|
## 解析
### 思路
这道题目，我们不难想到**贪心**

我们每次找到当前能放进去的边长**最大**的正方形，把它放进去

并使字典序尽量地小即可

### 代码实现时的具体步骤
- 找一个点切进去
- 看看它的最佳答案是多少
- 以它为顶点向外扩张成一个最大的正方形
- 标记好答案
- 输出整张答案地图$\texttt{(这里记得类型转换)}$
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int Line,Column;
int Dp[101][101]; 
inline int Dfs(int X,int Y)
{
	if(Dp[X][Y])
	{
		return Dp[X][Y];
	}
	register int i;
	for(i=1;i<=26;i++)
	{
		if(Dp[X-1][Y]!=i&&Dp[X][Y-1]!=i&&Dp[X+1][Y]!=i&&Dp[X][Y+1]!=i)
		{
			return i;
		}
	}
}
int main(void)
{
	register int i,j,k,l;
	cin>>Line>>Column;
	for(i=1;i<=Line;i++)
	{
		for(j=1;j<=Column;j++)
		{
			if(Dp[i][j])
			{
				continue;
			}
			register int Dfsed;
			Dfsed=Dfs(i,j);
			register int Tmp;
			Tmp=0;
			while(Dfs(i,j+Tmp)==Dfsed&&i+Tmp<=Line&&j+Tmp<=Column)
			{
				Tmp++;
			}
			for(k=i;k<i+Tmp;k++)
			{
				for(l=j;l<j+Tmp;l++)
				{
					Dp[k][l]=Dfsed;
				}
			}
		}
	}
	for(i=1;i<=Line;i++)
	{
		for(j=1;j<=Column;j++)
		{
			cout<<(char)(Dp[i][j]+'A'-1);
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Polaris_Dane (赞：0)

考虑贪心，每次将能够填的最小的填最大的正方形

然后pretest6啪啪打脸

我们发现更大的字母的作用是为了隔开较小的字母以便再次使用他们

我们贪心应该改成每次将能够填的最小的填到一个能填更小字母的位置

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<set>
#include<queue>
#define M 400100
#define N 500100
#define inf 2e9
#define LL long long
const int mod=998244353;
using namespace std;
inline int read(){
	int f=1,x=0;char s=getchar();
	while (!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while (isdigit(s)){x=(x<<1)+(x<<3)+(s^48),s=getchar();}
	return x*f;
}
int n,m,a[200][200];
inline int work(int x,int y){
	if (a[x][y]) return a[x][y];
	int now=1;
	for (;now<=26;now++) if (a[x-1][y]!=now&&a[x][y-1]!=now&&a[x+1][y]!=now&&a[x][y+1]!=now) return now;	
}
signed main(void){
	n=read(),m=read();
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			if (a[i][j]) continue;
			int col=work(i,j);
			int k=0;
			while (work(i,j+k)==col&&i+k<=n&&j+k<=m) k++;
			for (int pi=i;pi<i+k;pi++)
				for (int pj=j;pj<j+k;pj++)
					a[pi][pj]=col;
		}
	}
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++)
			printf("%c",a[i][j]-1+'A');
		puts("");
	}
	return 0;
}
```


---

