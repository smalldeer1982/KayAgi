# 「MCOI-Zero / AC6-M15」 Chandelier

## 题目背景

「不，还没完……」

「什么！？」

「炮管打开了。   
　那个丑陋的东西开始通过炮管散热了！」

「它的关键区域就在炮管后面。」

「Talisman……   
　……我们可以信任你，对吗？」
 
$$_{{\frac{\large\text{ACE COMBAT }\Large6}{\tiny{\text{F i r e s\quad O f\quad L i b e r a t i o n}}}}}\\ \text{Mission 15} \\\Large\text{Chandelier}\\\tiny -\textit{ To All Things }
-$$

![](https://cdn.luogu.com.cn/upload/image_hosting/w6wqsh2b.png)

## 题目描述

Chandelier 的核心可以被描述为一个 $n\times m$ 的矩阵。初始时，矩阵中的每一个格子都是一个独立的空间。

如果在核心中存在两个空间使得它们在矩阵上的并是一个矩形，则这两个空间可以合并为一个空间，合并出的空间就是原先两个空间的并。

![](https://cdn.luogu.com.cn/upload/image_hosting/jkzu2t0u.png)

如果不存在任何两个空间的并是矩形，则我们称核心达到了稳定状态。

如果一个空间的长达到了 $n$ 或者宽达到了 $m$，那么核心将会短路，引发爆炸。**注意这里空间的长指的是和原矩阵的长为 $n$ 的边平行的边的长度，宽类似。也就是说如果平行于 原矩形的长为 $n$ 的边 的边长达到了 $m$ 且 $m<n$，那么这是合法的。**

核心达到了稳定状态后，你才能攻击并摧毁它，需要的攻击次数就是剩下的空间数。

你剩下的弹药不多了，所以只能攻击 $10$ 次。

你需要合理地控制空间的合并，使得核心在不短路的情况下达到稳定状态，且需要的攻击次数 $\leq 10$。

求出一种可能合并出来的形态。如果核心无法在不短路的情况下达到稳定或者无法合并为 $\leq 10$ 个空间，输出 $-1$。

## 说明/提示

- Subtask 1（20 pts）：$n,m\leq 2$。
- Subtask 2（40 pts）：$n,m\leq 4$。
- Subtask 3（40 pts）：无特殊限制。

对于 $100\%$ 的数据，满足 $1\leq n,m\leq 10^{3}$。

idea：Sol1，solution：Sol1，code：Sol1，data：Sol1

---

「我看见大炮终于完了……」

「全机注意，   
　战争结束了。」

……

「Talisman 看，太阳升起来了。」

「尽管黑夜是如此漫长，但终将迎来黎明的曙光。」

「我们失去的战友，都把他们的生命之火   
　献给了破晓之光。」

「我们尽最大努力存活——   
　就是对他们的最好悼念。」

「现在，来吧。」

「让我们回家吧。」



## 样例 #1

### 输入

```
5 6```

### 输出

```
10
1 9 9 9 9 10
1 2 3 4 4 10
1 2 3 5 5 5
1 2 6 6 6 8
7 7 7 7 7 8```

# 题解

## 作者：Sol1 (赞：8)

~~idea 来自讨论奇怪问题~~

给一种最好实现的构造方式：

$$\begin{matrix}1&1&1&\cdots&1&2\\3&5&5&\cdots&5&2\\3&5&5&\cdots&5&2\\\vdots&\vdots&\vdots&\ddots&\vdots&\vdots\\3&5&5&\cdots&5&2\\3&4&4&\cdots&4&4\end{matrix}$$

复杂度 $O(n^2)$。

---

## 作者：乐乐乐还在乐 (赞：6)

# P7784 题解

**[题目传送门](https://www.luogu.com.cn/problem/P7784)**

### 题目大意

- 将一个 $n*m$ 的矩形分成 $x$ 个空间 （$x\le10$），要求每个空间都是矩形，且任意两个矩形均不能合并成一个更大的矩形。

- 任意一个空间的长和宽不能达到 $n$ 和 $m$。

### 分析题目

这道题乍一看很难，实际上只需拿起草稿纸和笔想一想，就能发现这题就是水题一道。

### 思考算法

~~这题有算法吗？~~

首先，我们想到，可以用一块空间占据一个尽量大的地方。（但又不能太大）

于是，自然而然地就想到可以用一块大小为 $(n-1)*(m-1)$，再用四个空间围在它的旁边就行了。

**即：**

$1\ 1\ 1\ \cdots\ 1\ 1\ 2$

$3\ 5\ 5\ \cdots\ 5\ 5\ 2$

$3\ 5\ 5\ \cdots\ 5\ 5\ 2$

$\vdots\ \ \vdots\ \ \vdots\ \ddots\ \vdots\ \ \vdots\ \ \vdots$

$3\ 5\ 5\ \cdots\ 5\ 5\ 2\ $

$3\ 5\ 5\ \cdots\ 5\ 5\ 2\ $

$3\ 4\ 4\ \cdots\ 4\ 4\ 4\ $

**注意了：**

当 $n=2$ 或 $m=2$ 时，是不能达到题目目标的，需要特判。

## 附上AC代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n,m;

int main(){
	cin>>n>>m;
	
	if(n==2||m==2){
		printf("-1");
		return 0;
	}
	
	printf("5\n");
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(1<i&&i<n&&1<j&&j<m)printf("5 ");
			if(i==1&&j!=m)printf("1 ");
			if(j==m&&i!=n)printf("2 ");
			if(j==1&&i!=1)printf("3 ");
			if(i==n&&j!=1)printf("4 ");
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Eason_AC (赞：6)

## Content
你要把 $n\times m$ 的一个矩阵划分成若干个矩阵，使得对于每一个矩阵：

- 不存在两个矩阵合起来是一个矩阵。
- 划分的矩阵个数不超过 $10$。

请给出一个划分方案，或者报告不存在。

**数据范围：$1\leqslant n,m\leqslant 1000$。**
## Solution
ClCN 往第一题和最后一题放分别放了个签到题，真是别有用心啊（

回到正题，首先，显然如果 $n=2$ 或者 $m=2$，就不能够构造出一个方案满足上面的要求。

否则是可以构造的，下面给出一个划分的矩阵数为 $5$ 的一个构造方案。

首先对于一个格子 $(x,y)$，如果 $x\in[2,n-1]$ 且 $y\in[2,m-1]$，则所有满足要求的格子可以组成一个矩阵。然后对于在边界上的格子，从 $(1,1)$ 开始到 $(n-1,1)$ 的一段为一个矩阵，从 $(n,1)$ 开始到 $(n,m-1)$ 的一段为一个矩阵，从 $(n,m)$ 到 $(2,m)$ 的一段为一个矩阵，从 $(1,m)$ 到 $(1,2)$ 的一段为一个矩阵。这样就可以构造出一个划分的矩阵数为 $5$ 的满足要求的方案了。
## Code
```cpp
namespace Solution {
    int a[1007][1007] = {0};
	
	iv Main() {
    	int n = Rint, m = Rint;
		if(n <= 2 || m <= 2) puts("-1");
		else {
			int curx = 1, cury = 1, curcol = 1;
			while(curx < n) a[curx++][cury] = curcol;
			curcol++;
			while(cury < m) a[curx][cury++] = curcol;
			curcol++;
			while(curx > 1) a[curx--][cury] = curcol;
			curcol++;
			while(cury > 1) a[curx][cury--] = curcol;
			F(int, i, 2, n - 1) F(int, j, 2, m - 1) a[i][j] = 5;
			puts("5");
			F(int, i, 1, n) print_array1(a[i], m);
		}
        return;
    }
}
```

---

## 作者：狛枝风斗 (赞：2)

很久以前 ClCN 向 MCOI 提供过这题，只不过当时不缺题他就收回来了（

有趣的签到题。

#### Description

> 给定一个 $n \times m$ 的矩阵，求将其划分为 $1 \sim 10$ 个子空间使得这些子空间满足：
> - 不能与其他任何子空间合并成一个矩阵；
> - 不能有任何一条边长度为 $n$ 或 $m$。
>
> 求一种分配子空间的方式。

#### Solution

根据样例可以想到，我们需要构造一种所有空间都错开的情况。

不知道您们是怎么想的，反正我一想到空间错开就能想到一张图片：

![](https://cdn.luogu.com.cn/upload/image_hosting/inzltmah.png)

因此根据这张弦图就可以构造出来一种合法的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/yzley3na.png)

注意一些特判，当 $n \le 2$ 或 $m \le 2$ 时就不可能容下这些子空间了，需要判掉。

#### Code

自认为比较优美的写法（

```cpp
#include <bits/stdc++.h>

using namespace std;

int main () {
	int n, m;
	scanf("%d%d", &n, &m);
	if (n <= 2 || m <= 2) {
		puts("-1");
		return 0;
	}
	puts("5");
	for (int i = 1; i < m; i++) printf("1 ");
	puts("2");
	for (int i = 1; i < n - 1; i++) {
		printf("4 ");
		for (int j = 1; j < m - 1; j++) printf("3 ");
		puts("2");
	}
	printf("4 ");
	for (int i = 1; i < m; i++) printf("5 ");
	puts("");
	return 0;
}
```

---

## 作者：_ZhouYuHan_ (赞：2)

这道题我们分两种情况考虑

- 无解

因 $n\le2$ 时宽只能为 $1$，肯定可以合并，所以无解。

- 有解，如何构造此解？

我们以 $n=3,m=3$ 的情况为例：

可以如此构造：
```
1 1 4
3 5 4
3 2 2
```
很明显，四周长为 $n-1$，宽为 $1$ ，其他以 $5$ 填充。

据此，我们可写出代码的核心部分：
```
for(int i=1; i<m; i++)
		g[1][i]=1,g[n][i+1]=2;//上下两行
for(int i=2; i<=n; i++)
		g[i][1]=3,g[i-1][m]=4;//左右两列
printf("5\n");
for(int i=1; i<=n; i++) {
	for(int j=1; j<=m; j++)
		if(g[i][j]==0)
			printf("5 ");//如果没填，输出5
		else
			printf("%d ",g[i][j]);//如果填了，输出填的数
	printf("\n");
}
```
最后加上头尾即可：
```
#include<bits/stdc++.h>
using namespace std;
int n,m;
int g[1005][1005];
int main() {
	scanf("%d%d",&n,&m);
	if(n<=2||m<=2) { //特判无法构造
		printf("-1");
		return 0;
	}
	for(int i=1; i<m; i++)
		g[1][i]=1,g[n][i+1]=2;//上下两行
	for(int i=2; i<=n; i++)
		g[i][1]=3,g[i-1][m]=4;//左右两列
	printf("5\n");
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++)
			if(g[i][j]==0)
				printf("5 ");//如果没填，输出5
			else
				printf("%d ",g[i][j]);//如果填了，输出填的数
		printf("\n");
	}
	return 0;
}
```

---

