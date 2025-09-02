# More Reclamation

## 题目描述

In a far away land, there are two cities near a river. One day, the cities decide that they have too little space and would like to reclaim some of the river area into land.

The river area can be represented by a grid with $ r $ rows and exactly two columns — each cell represents a rectangular area. The rows are numbered $ 1 $ through $ r $ from top to bottom, while the columns are numbered $ 1 $ and $ 2 $ .

Initially, all of the cells are occupied by the river. The plan is to turn some of those cells into land one by one, with the cities alternately choosing a cell to reclaim, and continuing until no more cells can be reclaimed.

However, the river is also used as a major trade route. The cities need to make sure that ships will still be able to sail from one end of the river to the other. More formally, if a cell $ (r,c) $ has been reclaimed, it is not allowed to reclaim any of the cells $ (r-1,3-c) $ , $ (r,3-c) $ , or $ (r+1,3-c) $ .

The cities are not on friendly terms, and each city wants to be the last city to reclaim a cell (they don't care about how many cells they reclaim, just who reclaims a cell last). The cities have already reclaimed $ n $ cells. Your job is to determine which city will be the last to reclaim a cell, assuming both choose cells optimally from current moment.

## 说明/提示

In the first example, there are 3 possible cells for the first city to reclaim: $ (2,1) $ , $ (3,1) $ , or $ (3,2) $ . The first two possibilities both lose, as they leave exactly one cell for the other city.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF335C/9dcf00d73fa4874adb1a93b4ff0aff43602b2edb.png)However, reclaiming the cell at $ (3,2) $ leaves no more cells that can be reclaimed, and therefore the first city wins.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF335C/3534861a36cc5545c6ce50c4536d43f04309cbd9.png)In the third example, there are no cells that can be reclaimed.

## 样例 #1

### 输入

```
3 1
1 1
```

### 输出

```
WIN
```

## 样例 #2

### 输入

```
12 2
4 1
8 1
```

### 输出

```
WIN
```

## 样例 #3

### 输入

```
1 1
1 2
```

### 输出

```
LOSE
```

# 题解

## 作者：juju527 (赞：2)

### 前置知识
观察能力，一点sg函数基础

### $\texttt{Solution}$

考虑某个位置 $(u,v)$ 放了一个棋子后，

$(u,v\space xor \space1),(u-1,v\space xor \space1),(u+1,v\space xor \space1)$ 都不能再放棋子

我们能发现 1~u-1 行与 u+1~r 行将互不影响

由于这是个博弈问题，我们对**互不影响**非常敏感，因为这有可能能得到一组**组合游戏的和**

显然本质不同的状态只由行数，最上方状态，最下方状态

考虑sg函数 $f_{l,up,dw}$，其中 $up,dw\in[0,3]$

表示一个 $l$ 行的子问题，最上方的状态是 $up$，最下方的状态是 $dw$ 的sg值

考虑转移

$f_{l,up,dw}=\text{mex}_{i,s}\{f_{i,up,s}\space xor\space f_{l-i-1,s,dw}\}$

复杂度 $O(r^2)$

代码很好懂

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=105;
struct node{
	int u,v;
	bool operator <(node i)const{
		return u<i.u;
	}
}a[maxn];
int l[maxn];
int f[maxn][3][3];
int vis[maxn][3][3];
int read(){
    int x=0,y=1;
    char ch=getchar();
    while(ch<48||ch>57){if(ch==45)y=-1;ch=getchar();}
    while(ch>=48&&ch<=57)x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*y;
}
int main(){
    freopen("CF335C.in","r",stdin);
    freopen("CF335C.out","w",stdout);
    int r,n;
	r=read();n=read();
	for(int i=1;i<=n;i++){
		int u,v;
		u=read();v=read()-1;
		a[i].u=u;a[i].v=v;
		l[u]|=(1<<v);
		if(l[u]==3){puts("LOSE");return 0;}
	}
	for(int i=1;i<=r;i++){
		memset(vis,0,sizeof(vis));
		for(int s=0;s<=2;s++)
			for(int t=0;t<=2;t++)
				for(int j=0;j<i;j++)
					for(int k=1;k<=2;k++){
						if((j==0&&k!=s&&s)||(j==i-1&&k!=t&&t))continue;
//						cout<<"qaq\n";
						vis[f[j][s][k]^f[i-j-1][k][t]][s][t]=1;
					}
		for(int s=0;s<=2;s++){
			for(int t=0;t<=2;t++){
				int p=0;
				for(int j=0;j<=i;j++)if(!vis[j][s][t]){p=j;break;}
				f[i][s][t]=p;
//				cout<<i<<" "<<s<<" "<<t<<" "<<f[i][s][t]<<endl;
			}
		}
	}
	sort(a+1,a+n+1);
	a[0].u=0;
	a[n+1].u=r+1;
	int ans=0;
	for(int i=1;i<=n+1;i++)
		ans^=f[a[i].u-a[i-1].u-1][l[a[i-1].u]][l[a[i].u]];
//	cout<<a[n+1].u<<" "<<a[n].u<<endl;
//	cout<<ans<<endl;
	if(ans>0)puts("WIN");
	else puts("LOSE");
    return 0;
}

```

---

## 作者：Dehydration (赞：0)

### 前言：

翻译与题解同时交的，不知道哪个先过。

这题是一个博弈问题，显然啊，```WIN```和```LOSE```。

ps：[博客](https://www.luogu.com.cn/blog/661534/)，[题目](https://www.luogu.com.cn/problem/CF335C)。

### 思路：

一个很显然的 $sg$ 博弈问题。

我们设 $f[len][x][y]$ 表示有一个长度为 $len$ 的矩形，它的 $len\times2$ 个小正方形都在，最左边的一个小正方形只能按照 $x$ 的方式剪掉，最右边的一个小正方形只能按照 $ y$ 的方式剪掉，其中：$x=1$ 或者 $y=1$ 表示剪掉的是第一排的矩形，$x=2$ 或者 $y=2$ 表示剪掉的是第二排的矩形，$x=0$ 或者 $y=0$ 表示没有限制，即：可以剪掉第一排的也可以剪掉第二排的。

那么，当 $len=0$ 的时候，必然有 $f[0][x][y]=0$，其中 $0\le x\le 2, 0\le y\le 2$。

当 $len=1$ 的时候，必然有 $f[1][1][2]=f[1][2][1]=0$， $f[1][1][1]=f[1][2][2]=f[1][0][x]=f[1][x][0]=1$，其中  $0\le x\le 2$。

根据状态的定义，当前状态的下一个子状态也很好确定，先记忆化搜索将 $f$ 函数暴力出来。

然后，根据输入的矩形，将举行分解成若干个子矩形，每个子矩形都应该尽量大，这样，每个子矩形必然属于上面提到的的一个状态之一。

现在的游戏就变成了很多个游戏的和了，求出这些子游戏的 $sg$ 值的异或和 $sum$，如果 $sum\neq	0$，先手必胜，否则先手必败。

**思路应该讲的很清楚，代码就不放了。**

---

