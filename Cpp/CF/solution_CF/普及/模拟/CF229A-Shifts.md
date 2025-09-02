# Shifts

## 题目描述

You are given a table consisting of $ n $ rows and $ m $ columns. Each cell of the table contains a number, 0 or 1. In one move we can choose some row of the table and cyclically shift its values either one cell to the left, or one cell to the right.

To cyclically shift a table row one cell to the right means to move the value of each cell, except for the last one, to the right neighboring cell, and to move the value of the last cell to the first cell. A cyclical shift of a row to the left is performed similarly, but in the other direction. For example, if we cyclically shift a row "00110" one cell to the right, we get a row "00011", but if we shift a row "00110" one cell to the left, we get a row "01100".

Determine the minimum number of moves needed to make some table column consist only of numbers 1.

## 说明/提示

In the first sample one way to achieve the goal with the least number of moves is as follows: cyclically shift the second row to the right once, then shift the third row to the left twice. Then the table column before the last one will contain only 1s.

In the second sample one can't shift the rows to get a column containing only 1s.

## 样例 #1

### 输入

```
3 6
101010
000100
100000
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 3
111
000
```

### 输出

```
-1
```

# 题解

## 作者：zhouchuer (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF229A)
### 思路分析
首先读懂题意后就要思考，要使矩阵 $A$ 某一列的元素全部变为 $1$ 且操作次数最少，我们不知道这是哪一列，所以可以枚举矩阵的每一列。

对于枚举的每一列 $x$，设行为 $i$，如果 $A(i,x)=1$ 则无需处理，$A(i,x)=0$ 就要寻找每一行离这一列最近的 $1$ 与这一列的距离，最后累加得到这一列总共需要多少次操作。举例（如下图）：

![有解](https://cdn.luogu.com.cn/upload/image_hosting/cnrgqbxh.png)

假设寻找标黄一列所需最小操作次数，可以找到两个距离黄色列最近且值为 $1$ 的 $A(2,4)$ 和 $A(4,3)$ 两点。

按这样的方法枚举这个矩阵的每一列，用 $ans$ 记录移动次数的总和，在所有的 $ans$ 中取最小的输出即可通过。那么接下来处理无解的情况。

![无解](https://cdn.luogu.com.cn/upload/image_hosting/1j3gm4h8.png)

观察样例 $2$，发现第二行根本没有 $1$，自然无法使得任何一列的元素全部变成 $1$，因此这种情况无解，如上图。

本题的思维难度不大，主要是模拟代码较长，建议大家尝试自己写代码，可以较好地锻炼代码能力。

---

## 作者：__UrFnr__ (赞：2)

**题目思路**：

这道题我们可以枚举每一列，计算出最小代价。如何计算呢？可以算出每一行离这一列最近的 $1$ 距离这一列之和。

无解情况：某一行没有 $1$。

接着按照这样做，就能解决本题。

---

## 作者：素质玩家孙1超 (赞：2)

+ 题目意思：

给一个n*m的矩阵，里面有0或1

你可以向左或向右移动某一行（当向右移时，最后一个数会到最左，向左移同理）

问最少要多少步才可以使某一列全部是1

+ 解决方法：

枚举要变成1的列

对于每一行分别计算最近的1的距离

+ 注意：

由于是循环数组，所以要数组要复制两遍

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize(2)
const int Maxn=3e4+5;
const int Maxm=1e2+5;
const int inf=100000000;
int a[Maxm][Maxn],cnt[Maxm];
int n,m;
inline int R()
{
	char c;int res;
	while((c=getchar())>'9'||c<'0');res=c-'0';
	while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
	return res;
}
int fs(int k,int l,int r,int x)
{
	while(r>=l)
	{
		int mid=(l+r)>>1;
		if(a[k][mid]>=x) r=mid-1;
		else l=mid+1;
	}
	return a[k][r+1];
}
int fx(int k,int l,int r,int x)
{
	while(r>=l)
	{
		int mid=(l+r)>>1;
		if(a[k][mid]>x) r=mid-1;
		else l=mid+1;
	}
	return a[k][r];
}
int main()
{
	n=R();m=R();char c;
	for(int i=1;i<=n;i++)
	{
	for(int j=1;j<=m;j++)
	{
		while((c=getchar())!='0'&&c!='1');
		if(c=='1')
			a[i][++cnt[i]]=j;
	}
	int pp=cnt[i];
	for(int j=1;j<=pp;j++)
	a[i][++cnt[i]]=a[i][j]+m;
	for(int j=1;j<=pp;j++)
	a[i][++cnt[i]]=a[i][j]+m+m;
	}
	for(int i=1;i<=n;i++) if(cnt[i]==0) {puts("-1");return 0;};
	int s,ans=inf;
	for(int i=1;i<=m;i++)
	{
		s=0;
		for(int j=1;j<=n;j++)
			s+=min(fs(j,0,cnt[j],i+m)-i-m,i+m-fx(j,0,cnt[j],i+m));
		ans=min(ans,s);
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：_Deer_Peach_ (赞：0)

题意已经很清楚了所以不再赘述。

思路：

枚举使每一列都是 $1$ 的操作的次数，也就是计算每一行中到这一列最近的 $1$ 的距离的和，最后求最小值即可。当某一行没有 $1$ 就不可能完成，也就是无解情况。

---

## 作者：zhouzhengxuan (赞：0)

### 思路：  
因为不知道哪一列操作次数最小，所以枚举每一列的最小操作次数，加以比较，取最小值。  
具体如何枚举呢？可以一行一行地看，看每一行这一列的点，离它最近的 $1$ 离它有多远，将每一行的数值加起来，就是这一列的最小操作次数。

代码就不贴了，相信你们都懂，希望管理员大大给过 qwq。

---

