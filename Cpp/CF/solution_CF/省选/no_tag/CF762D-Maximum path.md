# Maximum path

## 题目描述

你被给了一个3*n的矩形表格。每个小格含有一个整数。如果两个格子有共享的边，你可以从一个格子移到另一个格子。
找到如下从左上角的格子到右下角的格子的路径，这条路径不能重复参观同一个格子，并且路径中的格子中的数字的和应该是可能的最大值。

------------

## 样例 #1

### 输入

```
3
1 1 1
1 -1 1
1 1 1
```

### 输出

```
7
```

## 样例 #2

### 输入

```
5
10 10 10 -1 -1
-1 10 10 10 10
-1 10 10 10 10
```

### 输出

```
110
```

# 题解

## 作者：Alan_Zhao (赞：13)

**[在我的 cnblogs 中查看](https://www.cnblogs.com/alan-zhao-2007/p/cf762d-sol.html)**

## 一种不一样的做法

首先，因为是 $(1,1)\to (3,n)$ 的简单路径上的点权之和的最大值，所以显然只会在第 $2$ 行进行“向左”的操作。

可以发现，每次向左一定会取到一个 $3$ 行 $x$ 列的子矩阵中的所有数，其中 $x$ 是向左的次数。

![](https://cdn.luogu.com.cn/upload/image_hosting/svg3dc7h.png)

如图，向左的次数是 $6$，所以它取到了一个 $3\times 6$ 的子矩阵中的数。

设 $f_{i,j}$ 为 $(1,1)\to (i,j)$ 的简单路径上的点权之和的最大值，所以我们可以把只能往上、下、右走的做法，添加上两种转移：

$$\begin{aligned}
f_{1,x}+a_{3,y}+\sum_{j=1}^3\sum_{k=x+1}^{y-1} a_{j,k}&\to f_{3,y},\forall x,y\in [1,n],x<y
\\
f_{3,x}+a_{1,y}+\sum_{j=1}^3\sum_{k=x+1}^{y-1} a_{j,k}&\to f_{1,y},\forall x,y\in [1,n],x<y
\end{aligned}$$

其中 $\to$ 指取 $\max$，即可得到此题的做法。前缀和优化后，时间复杂度为 $\mathcal{O}(n)$。

## 代码

```cpp
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
template<typename T> void Read(T &_x){
	_x=0;int _f=1;
	char ch=getchar();
	while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();
	while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();
	_x*=_f;
}
template<typename T,typename... Args> void Read(T &_x,Args& ...others){
	Read(_x);Read(others...);
}
typedef long long ll;
const int N=1e5+5;
const ll Inf=0x3f3f3f3f3f3f3f3fLL;
int n;ll a[4][N],f[4][N];
int main(){
	// freopen("CF762D.in","r",stdin);
	// freopen("CF762D.out","w",stdout);
	Read(n);
	For(i,1,3){
		For(j,1,n) Read(a[i][j]);
	}
	ll now=a[1][1]+a[2][1]+a[3][1],now1=-Inf;
	f[1][1]=a[1][1],f[2][1]=a[1][1]+a[2][1],f[3][1]=a[1][1]+a[2][1]+a[3][1];
	For(i,2,n){
		f[1][i]=max({f[1][i-1],f[2][i-1]+a[2][i],f[3][i-1]+a[3][i]+a[2][i]})+a[1][i];
		f[2][i]=max({f[1][i-1]+a[1][i],f[2][i-1],f[3][i-1]+a[3][i]})+a[2][i];
		f[3][i]=max({f[1][i-1]+a[1][i]+a[2][i],f[2][i-1]+a[2][i],f[3][i-1]})+a[3][i];
		now1=max(now1,f[3][i-1])+a[1][i]+a[2][i]+a[3][i];
		now=max(now,f[1][i-1])+a[1][i]+a[2][i]+a[3][i];
		f[1][i]=max(f[1][i],now1);
		f[3][i]=max(f[3][i],now);
	}
	printf("%lld\n",f[3][n]);
	return 0;
}
```

---

## 作者：TLE_Automat (赞：10)

**题目**：[CF762D](https://www.luogu.com.cn/problem/CF762D) 。

**题意**：给定一个 $3\times n$ 的网格，每个格内有一个 $[-10^9 , 10^9]$ 的整数权值，问从 $(1,1)$ 到 $(3,n)$ 的不重复经过同一格子的权值最大的路径的权值是多少。

**题解**：

看到这个题，立刻想到了 [CSP-J 2020 T4](https://www.luogu.com.cn/problem/P7074) 。但与 $\text{CSP-J}$ 这道题区别最大的是，此题可以一直向左走，只要不重复经过同一个点就可以，这也成为了此题最大的难点。

如果没有一直向左走这个条件，很容易想到一个 $O(nm)$ 的 dp ，在此题中也就是 $O(3n)$ 。那么考虑能否把这个 dp 魔改一下，改成支持向左走呢，经过尝试发现显然不行，因为不管怎么设计状态，这个 dp 永远存在环。

这时候发现这道题直接做很难，甚至是直接不可做，那么我们就该考虑一下此题有什么可以帮助做题的性质。

我们已经注意到一直向左走是 dp 中最大的难点了，那我们可以从这方面考虑一下，看能否通过一些性质化解一直向左走这个问题。

仔细考虑一下不难发现，我们只有可能在三行的中间那一行向左走（否则就回不来了），并且在上面或下面任意一行选择进入，另一行选择返回，考虑当返回的格子超过 $1$ 个时：

- 当返回格子数为偶数个时，一定可以通过上下盘曲而替代。如下图：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/sj0ymtsm.png)

- 当返回格子数为奇数个时，一定可以通过先返回 $1$ 格再上下盘曲而替代。如下图：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/034p5ifb.png)

所以，一直向左走其实是可以被代替的，换句话说，一定存在一种最优的走法，使得每次向左走不超过 $1$ 格。

根据这个性质，就可以像第二篇题解说的那样进行 dp 了，此篇题解主要解释了为什么那么 dp 是对的。

还有就是，目前的 [第一篇题解](https://www.luogu.com.cn/blog/YanYou/solution-cf762d) 是错的，直接交会 WA on test 3 ，望管理撤下。





---

## 作者：Moyou (赞：7)

> Update 2024.11.12 修正了回头走一格的歧义，改为了不会连续回头走大于等于二格。

# [CF762D] Maximum path 题解

## 想法

首先考虑问题的弱化版，如果不能往左走，能取到的最大值是多少。

这个问题可以用一个显然的 DP 解决，$f_{i,j}$ 表示走到第 $i$ 列，第 $j$ 行，并且不会再访问这一列其它的方格，能取到的最大值。

转移可以从三个方向考虑，以 $f_{i,1}$ 为例，黑色是当前状态，红黄蓝是可能的三个转移方向，每一个状态可以取到箭头经过的点的权值。$f_{i,2}, f_{i,3}$ 同理。

![](https://cdn.luogu.com.cn/upload/image_hosting/wq27j0m1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

## 思路

但是原题中人是可以往左回头走的，这样这个单纯的转移就不成立了，因为回头走会出现后效性。

既然如此，可以想一下有没有什么性质尚未被观察到。

根据人类的直觉，小人应该是不会回头走太多步的，这个直觉是正确的，小人最多 **连续地** 回头走 $1$ 格。

![](https://cdn.luogu.com.cn/upload/image_hosting/9sckc0t1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图，黑色的路径和红色路径得到的权值是相等的。

猜测 **所有的回头路径都有一个修正的路径对应**。

回头走的真谛是在遍历蓝色小人到黑色小人每一行的格子，如果能找到一条最多回头一次的路径也能遍历这些格子，就可以证明上面的引理。

观察到这种走法可以让要遍历的格子列数减去 2，而行位置不变。

![](https://cdn.luogu.com.cn/upload/image_hosting/jqaorob6.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

那么如果要遍历的列数是奇数，可以直接一直走上图走法，剩余遍历列数是 1 时，直接往上走到目标点。

如果列数是偶数，则在剩余遍历列数是 2 时，走一次下图走法，回头一次走到目标点：

![](https://cdn.luogu.com.cn/upload/image_hosting/v4expx7u.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以证明了对于任意一个最优解，都有一个最多只需要 **连续地** 回头一次的路径得到的权值与其相等，而不会 **连续地** 走大于等于两次。

所以这样就好做了，我们只需要在弱化版的 DP 转移里面加上回头一次的情况。

$f_{i, 2}$ 的转移不会出现回头的情况，而 $f_{i,1}, f_{i, 3}$ 加上回头转移的即可，以 $f_{i, 1}$ 为例，转移绿色路径：

![](https://cdn.luogu.com.cn/upload/image_hosting/esk1m5tx.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

问题得到了解决。

## 代码实现

时间复杂度：$O(n)$。

```cpp
// Problem: Maximum path
// Author: Moyou
// Copyright (c) 2023 Moyou All rights reserved.
// Date: 2023-09-29 19:36:59

#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int n;
long long a[3][N], f[N][3];

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 0; i < 3; i ++) {
        for(int j = 1; j <= n; j ++) {
            cin >> a[i][j];
        }
    }
    memset(f, -0x3f, sizeof f);
    f[0][0] = 0;
    for(int i = 1; i <= n; i ++) {
        long long sum = 0;
        for(int j = 0; j < 3; j ++) {
            sum += a[j][i] + a[j][i - 1];
        }
        f[i][1] = max({f[i - 1][0] + a[0][i], f[i - 1][1], f[i - 1][2] + a[2][i]}) + a[1][i];
        f[i][0] = max({f[i - 1][0], f[i - 1][1] + a[1][i], f[i - 1][2] + a[2][i] + a[1][i]}) + a[0][i];
        f[i][2] = max({f[i - 1][2], f[i - 1][1] + a[1][i], f[i - 1][0] + a[0][i] + a[1][i]}) + a[2][i];
        if(i > 1) {
            f[i][0] = max(f[i][0], f[i - 2][2] + sum);
            f[i][2] = max(f[i][2], f[i - 2][0] + sum);
        }
    }
    cout << f[n][2] << '\n';
    return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：5)

大意了，没交闪。                

我们一眼大致可以看出来一个很显的性质：行数只有 $3$ ，考虑在这上面做文章。                

先套一个插头 dp 的雏形上去，感觉巨大特别多状态不说，其中还有很多冗杂状态，于是考虑去除冗杂状态：              

观察这个 dp ，我们尝试把一列给压缩。我们发现这么做的话没有必要记录列与列之间的状态，这样就可以把我们中间格子和上下两个格子去掉两个插头，每个格子只需要两个插头即可。            


但是这个状态还不够优秀，我们考虑一下再利用只有三行这个性质：如果我们要往回走那么必然只能从第二行回来从两边出去。可以用笔画一下，如果不从中间往回走的话必将把路径走封闭，导致这个路径不合法。                 

两层优化下来状态数就很少了，对于每列考虑这几个状态：               

1. 状态 $0$：当前在该列的第 $1$ 行格子并且我们想往下一列的第 $1$ 行格子走；          

2. 状态 $1$：当前在该列的第 $2$ 行格子并且我们想往下一列的第 $2$ 行格子走；      

3. 状态 $2$：当前在该列的第 $3$ 行格子并且我们想往下一列的第 $3$ 行格子走；      

4. 状态 $3$：当前在该列的第 $1$ 行格子并且要走回路，从第 $1$ 行出第 $2$ 行回第 $3$ 行再出；         

5. 状态 $4$：当前在该列的第 $3$ 行格子并且要走回路，从第 $1$ 行出第 $2$ 行回第 $1$ 行再出；              

然后我们暴力枚举一下这几个状态可以从上一列的哪些状态转移过来即可，时间复杂度 $O(5n)$ 。                  


---

## 作者：edward1346 (赞：3)

## 一种神奇的做法

[题目传送门](https://www.luogu.com.cn/problem/CF762D)

### 分析过程

先来想想这道题为什么是一道紫题？

没错，就是因为它**可以向左走**，就是因为这个原因，才使这道题目的难度大大提高。

我们先对它的合法行走方式做一个分类：

一种是不含左走的；另一种是含左走的（也就是“蛇皮走位”）。

### 转移方程的推导

**我们可以先思考不含左走的。**

令 $f(i,j)$ 表示走到第 $i$ 行第 $j$ 列的最大点权和，那**不涵盖向左走的**转移方程也就自然而然地出来了：

$f(1,j) = \max \begin{cases} f(1,j-1)+a(1,j) \\ f(2,j-1)+a(2,j)+a(1,j) \\ f(3,j-1)+a(3,j)+a(2,j)+a(1,j) \end{cases}$

$f(2,j) = \max \begin{cases} f(1,j-1)+a(1,j)+a(2,j) \\ f(2,j-1)+a(2,j) \\ f(3,j-1)+a(3,j)+a(2,j) \end{cases}$

$f(3,j) = \max \begin{cases} f(1,j-1)+a(1,j)+a(2,j)+a(3,j) \\ f(2,j-1)+a(2,j)+a(3,j) \\ f(3,j-1)+a(3,j) \end{cases}$

不含左走的转移我们很简单就推导出来了，接下来让我们来想**含左走**的情况（也就是“蛇皮走位”）。

令 $g(i,j)$ 表示存在“蛇皮走位”操作地走到第 $i$ 行第 $j$ 列的最大点权和。

本蒟蒻通过不断地画图，发现：**第二行是不存在“蛇皮走位”的情况，因为向左走只能发生在第二行，否则将无法到达终点。**

所以，我们只需要考虑第一行的“蛇皮走位”和第三行的“蛇皮走位”。

我们先以第三行的“蛇皮走位”的情况为例子，来画个图：

![1](https://cdn.luogu.com.cn/upload/image_hosting/3nq4wbls.png)

我们现在要求的是 $g(3,j)$，需要通过 $g(3,j-1)$ 转移。怎么转移？

很简单，我们只需要把原来红色的路线扩展一下（如蓝色路径所示），就可以求出 $g(3,j)$ 的值了。

转移方程如下：

$g(3,j) = \max(g(3,j),g(3,j-1)+a(1,j)+a(2,j)+a(3,j))$

当然，这只是一种情况，还有第二种情况。

如图所示：

![2](https://cdn.luogu.com.cn/upload/image_hosting/pkz1m3tc.png)

我们现在要求的是 $g(3,j)$，需要通过 $f(1,j-1)$ 转移。怎么转移？

同样很简单，从上面直接走下来就行了（如蓝色路径所示），转移方程如下：

$ g(3,j) = \max (g(3,j),f(1,j-1)+a(1,j)+a(2,j)+a(3,j)) $

### 关于 $g(i,j)$ 转移方程推导的补充

（就拿上面的例子来说）本蒟蒻想到的两种转移：

$g(3,j) = \max \begin{cases} g(3,j-1)+a(1,j)+a(2,j)+a(3,j) & ① \\ f(1,j-1)+a(1,j)+a(2,j)+a(3,j) & ② \end{cases}$ 

对于第 $①$ 个转移，它涵盖了向左走次数大于等于 $1$ 次的情况；

对于第 $②$ 个转移，它涵盖了向左走次数 ~~（大于）~~ 等于 $0$ 的情况；

所以这两个转移就会不遗漏地涵盖所有情况（虽然可能有重合的情况，但是我们求的是最大值，不影响），保证了这种方法的正确性。

同理，$g(1,j)$ 的推导和 $g(3,j)$ 思路都十分相似（基本一样），这里直接给出转移方程：

$g(1,j) = \max \begin{cases} g(1,j-1)+a(1,j)+a(2,j)+a(3,j) \\ f(3,j-1)+a(1,j)+a(2,j)+a(3,j) \end{cases}$ 

**注意：**

因为这里的 $f(i,j)$ 表示的是走到第 $i$ 行第 $j$ 列的最大点权和，从定义上看那肯定是**要包含向左走的情况**的，所以：

当 $i = 1$ 或 $i = 3$ 时，$f(i,j) = \max(f(i,j),g(i,j))$。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int a[4][100001];
int f[4][100001];
int g[4][100001];
main()
{
	cin>>n;
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%lld",&a[i][j]);
		}
	}
	for(int i=0;i<=3;i++)
	{
		for(int j=0;j<=n;j++)
		{
			f[i][j]=-1e16;
			g[i][j]=-1e16;
		}
	}
	f[1][0]=0;
	for(int j=1;j<=n;j++)
	{
		for(int i=1;i<=3;i++)
		{
			if(i==1)
			{
				f[1][j]=max(f[1][j-1],max(f[2][j-1]+a[2][j],f[3][j-1]+a[3][j]+a[2][j]))+a[1][j];
				g[1][j]=max(g[1][j-1],f[3][j-1])+a[1][j]+a[2][j]+a[3][j];
				f[1][j]=max(f[1][j],g[1][j]);
			}
			if(i==2)
			{
				f[2][j]=max(f[1][j-1]+a[1][j],max(f[2][j-1],f[3][j-1]+a[3][j]))+a[2][j];
			}
			if(i==3)
			{
				f[3][j]=max(f[3][j-1],max(f[2][j-1]+a[2][j],f[1][j-1]+a[1][j]+a[2][j]))+a[3][j];
				g[3][j]=max(g[3][j-1],f[1][j-1])+a[1][j]+a[2][j]+a[3][j];
				f[3][j]=max(f[3][j],g[3][j]);
			}
		}
	}
	cout<<f[3][n];
	return 0;
	
}
```

---

## 作者：UperFicial (赞：2)

[CF762D Maxinum Path](https://www.luogu.com.cn/problem/CF762D)

参考了 Editor 的第二个 hint 才做出来。

首先可以发现，向左走的操作只会在第二行使用。

DP 过程中暴力枚举走了多少步进行转移是 $O(n^2)$ 的，但是你感性考虑一下，来回走的这一趟会形成一个矩形，这个矩形肯定会被一种等价形式形式表示出来，而且不用向左走很多步。

具体的，比如考虑如下这张图，向左走了奇数步。

[![pS6AVXT.md.png](https://s1.ax1x.com/2023/02/05/pS6AVXT.md.png)](https://imgse.com/i/pS6AVXT)

它的等价形式可以写成：

[![pS6AmBF.md.png](https://s1.ax1x.com/2023/02/05/pS6AmBF.md.png)](https://imgse.com/i/pS6AmBF)

或者是：

[![pS6An74.md.png](https://s1.ax1x.com/2023/02/05/pS6An74.md.png)](https://imgse.com/i/pS6An74)

都可以归结为向左走的步数不超过 $1$。

---

那如果我们向左走的步数为偶数步呢？

[![pS6AMN9.md.png](https://s1.ax1x.com/2023/02/05/pS6AMN9.md.png)](https://imgse.com/i/pS6AMN9)

也是一样，随便画一下图就行了：

[![pS6AQhR.md.png](https://s1.ax1x.com/2023/02/05/pS6AQhR.md.png)](https://imgse.com/i/pS6AQhR)

这个甚至都没有往左走。

---

上面几幅图主要说明的性质就是，向左走的步数不会超过 $1$，否则都可以变成向左走不超过 $1$ 的等价形式。

这样就好办多了啊！

设 $f_{i,j}$ 表示，考虑了前 $j$ 列，最后处于 $(i,j)$ 的最大价值。

既然我们不会处理向左走的操作，那么我们就不考虑它，而是直接将向左走的操作放到一个 $3\times 3$ 的矩形中去考虑，**直接计算贡献，不参与转移**，毕竟只向左走一步。

[![pS6AtBD.md.png](https://s1.ax1x.com/2023/02/05/pS6AtBD.md.png)](https://imgse.com/i/pS6AtBD)

比如要从左上角走到右下角，只考虑 $i-1$ 和 $i$ 这一列，且向左走一步，那么我们就只能这么走：

[![pS6AcDS.md.png](https://s1.ax1x.com/2023/02/05/pS6AcDS.md.png)](https://imgse.com/i/pS6AcDS)

实际上是，从 $(1,i-2)$ 出发，然后取遍 $i-1$ 和 $i$ 这两列的所有元素，所以得出：$f_{3,i}\leftarrow f_{1,i-2}+S_{i-1}+S_{i}$。

当然，从左下角走到右上角也是同理的，也很简单：

[![pS6AIg0.md.png](https://s1.ax1x.com/2023/02/05/pS6AIg0.md.png)](https://imgse.com/i/pS6AIg0)

同样是取遍第 $i-1$ 和 $i$ 列的所有元素，那么我们可以得出：$f_{1,i}\leftarrow f_{3,i-2}+S_{i-1}+S_i$。

这样的话向左走的情况就处理好了，只需要考虑向右，向下，以及向上的操作，这个就非常好处理。

由于我们是一列一列的考虑，所以就只需要考虑 $(1,i),(2,i),(3,i)$ 这三个元素怎么走。以 $(2,i)$ 为例，他只可能是 $(2,i-1)$ 向右走一个单位长度，或者是 $(1,i-1)$ 向右然后向下，或者是 $(3,i-1)$ 向右然后向上走。其余就都一样了。

时间复杂度 $O(n)$，可以通过。

---

## 作者：滑大稽 (赞：1)

这题看到那个 $n\le 3$ 就立马想到插头DP了。。。

先翻转一下序列，方便DP。

首先考虑括号表示法，我们设：$0$为无插头，$1$ 为路径的左端，$2$ 为路径右端，$3$ 为独立插头（该路径只在轮廓线上有一次贡献）。然后初始状态就是给 $(1,1)$ 处安上一个 $3$ 插头。在最后一格处接受 $3+0/0+3$ 插头的贡献来更新答案。然后中间大力分讨转移即可。唯一注意的就是一个格子可以不选，在 $0+0$ 插头转移的时候稍微注意一下。

还是写了哈希表压状态，随手一交就是rank4。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define ll long long
const int N=1e5+5,M=555,mod=101;
const ll inf=1e18;
using namespace std;
struct node{
	int x,y;
	ll v;
}q[2][M];
int k[mod],su[2];
int a[N][5];
int now,pre,n,m;
inline char gc()
{
	static char buf[1<<16],*S,*T;
	if(S==T)
	{
		T=(S=buf)+fread(buf,1,1<<16,stdin);
		if(S==T)return EOF;
	}
	return *(S++);
}
#define getchar gc
inline int read()
{
	char h=getchar();
	int y=0,q=1;
	while(h<'0'||h>'9'){if(h=='-')q=-1;h=getchar();}
	while(h>='0'&&h<='9')y=y*10+h-'0',h=getchar();
	return y*q;
}
inline void insert(int x,ll v)
{
	int w=x%mod;
	for(int i=k[w];i;i=q[now][i].x)
	if(q[now][i].y==x)
	{
		q[now][i].v=max(q[now][i].v,v);
		return;
	}
	q[now][++su[now]]=(node){k[w],x,v};
	k[w]=su[now];
}
inline int findl(int x,int w)
{
	int cnt=0;
	for(int z=w;z<=m;z++)
	{
		if(((x>>(z<<1))&3)==2)cnt++;
		else if(((x>>(z<<1))&3)==1)cnt--;
		if(cnt==0)
		{
			return (1<<(z<<1));
		}
	}
	return 1145141919;
}
inline int findr(int x,int w)
{
	int cnt=0;
	for(int z=w;~z;z--)
	{
		if(((x>>(z<<1))&3)==1)cnt++;
		else if(((x>>(z<<1))&3)==2)cnt--;
		if(cnt==0)
		{
			return (1<<(z<<1));
		}
	}
	return 1145141919;
}

signed main()
{
	n=read(),m=3;
	for(int j=1;j<=m;j++)
	for(int i=1;i<=n;i++)a[i][j]=read();
	now=1;insert(3<<(m<<1),0);
	ll ans=-inf;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=su[now];j++)q[now][j].y>>=2;
		for(int j=1;j<=m;j++)
		{
			swap(now,pre);
			su[now]=0;
			memset(k,0,sizeof k);
			for(int _=1;_<=su[pre];_++)
			{
				int x=q[pre][_].y;ll v=q[pre][_].v;
				int p1=(x>>((m-j)<<1))&3,p2=(x>>((m-j+1)<<1))&3,w1=1<<((m-j)<<1),w2=1<<((m-j+1)<<1);
				if(p1==0&&p2==0)
				{
					if(i!=n&&j!=m)insert(x+2*w1+w2,v+a[i][j]);
					insert(x,v);
				}
				else if(p1==1&&p2==0)
				{
					if(j!=m)insert(x,v+a[i][j]);
					if(i!=n)insert(x-w1+w2,v+a[i][j]);
				}
				else if(p1==2&&p2==0)
				{
					if(j!=m)insert(x,v+a[i][j]);
					if(i!=n)insert(x-2*w1+2*w2,v+a[i][j]);
				}
				else if(p1==3&&p2==0)
				{
					if(j!=m)insert(x,v+a[i][j]);
					if(i!=n)insert(x-3*w1+3*w2,v+a[i][j]);
					if(i==n&&j==m)ans=max(ans,v+a[i][j]);
				}
				else if(p1==0&&p2==1)
				{
					if(i!=n)insert(x,v+a[i][j]);
					if(j!=m)insert(v-w2+w1,v+a[i][j]);
				}
				else if(p1==1&&p2==1)
				{
					insert(x-p1*w1-p2*w2-findr(x,m-j),v+a[i][j]);
				}
				else if(p1==2&&p2==1)
				{
					insert(x-p1*w1-p2*w2,v+a[i][j]);
				}
				else if(p1==3&&p2==1)
				{
					insert(x-p1*w1-p2*w2+2*findr(x,m-j+1),v+a[i][j]);
				}
				else if(p1==0&&p2==2)
				{
					if(i!=n)insert(x,v+a[i][j]);
					if(j!=m)insert(x-2*w2+2*w1,v+a[i][j]);
				}
				else if(p1==1&&p2==2)
				{
					insert(x-w1-2*w2,v+a[i][j]);
				}
				else if(p1==2&&p2==2)
				{
					insert(x-p1*w1-p2*w2+findl(x,m-j+1),v+a[i][j]);
				}
				else if(p1==3&&p2==2)
				{
					insert(x-p1*w1-p2*w2+2*findl(x,m-j+1),v+a[i][j]);
				}
				else if(p1==0&&p2==3)
				{
					if(i!=n)insert(x,v+a[i][j]);
					if(j!=m)insert(x-3*w2+3*w1,v+a[i][j]);
					if(i==n&&j==m)ans=max(ans,v+a[i][j]);
				}
				else if(p1==1&&p2==3)
				{
					insert(x-p1*w1-p2*w2+findr(x,m-j),v+a[i][j]);
				}
				else if(p1==2&&p2==3)
				{
					insert(x-p1*w1-p2*w2+2*findl(x,m-j),v+a[i][j]);
				}
				else if(p1==3&&p2==3)
				{
					insert(x-p1*w1-p2*w2,v+a[i][j]);
				}
			}
		}
	}
	cout<<ans<<"\n";
}
```

---

## 作者：夏菡德佑 (赞：1)

看到这题没有题解，我便本着为大洛谷做些贡献的心理~~实则是想混点咕值~~，写下了这篇题解。


------------
## 分析
看到题目是3*n的矩形表格，这显然就是一题典型的状压dp题。
但是状压的方法就不那么经典了 ~~至少我的状压不经典~~。


------------

## 状态定义:
经过我深思熟虑，我发现自己没能想出像寻常的状压dp那样 状压格子 ，于是，我就改变了思路，决定状压边上的状态，通过边上的状态来推出路径，从而得到经过的格子。所谓的边，就是两列格子中间的线。

我设计的dp方程为：dp[i][s]，表示第i列的第s种状态能走过的最大值。

可以发现，通过某一条边的路径总共有以下5种状态。


------------

![](https://cdn.luogu.com.cn/upload/image_hosting/1h63k5hr.png)
图中箭头表示路径的方向，没有箭头的地方代表没有路径经过，第3、4号状态中绿色的箭头表示路径的出端

这样讲可能有点抽象，那么下面是我对样例的解释，以便加深理解


------------
![](https://cdn.luogu.com.cn/upload/image_hosting/lqq0u6e3.png)

图中每一条边上的黑色的数字代表这一条边的标号，红色的数字代表这一条边的状态。

应该算是挺清楚了，如果还是不懂，可以先放着，等到后面用代码辅助理解。


------------
## 状态转移
状态转移其实还挺好理解，主要就是想对于每一种状态，有哪些状态可以放在可以放在它的前一列（也就是说，如果能够用笔画出一条路径同时满足这种状态组合，那么则说明这种组合是可行的）。这个其实很好推，只需要稍微花一点时间动一动笔。下面是我的状态转移，可以参考一下。

x(a,b,....)表示括号中的状态可以作为x状态的前一个状态
-  0(0,1,2,4)
-  1(0,1,2)
-  2(0,1,2,3)
-  3(0,3)
-  4(2,4)


------------

## 初始化
由于第一列不太好判断，所以我选择直接预处理第一列的状态，值得注意的是，由于是从左上角开始走，所以不可能存在路径使得第一列呈现出四号状态，所以dp[1][4]赋值为负无穷（可以自己简单证明一下）。其他的dp数组不需要初始化，因为转移都是直接赋值


------------

## 答案
由于n列格子只有n-1条边，所以答案为第n-1列的五种状态加上各个状态在第n列上走过的路径，要注意，四号状态也无法出现在第n-1行，因为最终要走到右下角


------------
## 下面就是本人的代码，可供各位看官借鉴一二
```cpp
#include<cstdio>
using namespace std;
#define LL long long
#define N 100005
#define OO 0x3f3f3f3f3f3f3f3f
LL dp[N][5],mp[4][N];
inline LL MAX(LL a,LL b) {return a>b?a:b;}
inline LL MAX4(LL a,LL b,LL c,LL d) {return MAX(MAX(a,b),MAX(c,d));}
inline LL S(LL i,LL a,LL b,LL c) {return mp[a][i]+mp[b][i]+mp[c][i];}
int main() {
	LL n,ans;
   	scanf("%lld",&n);
   	for(int i=1;i<=3;i++)
   		for(int j=1;j<=n;j++)
   			scanf("%lld",&mp[i][j]);
   	if(n==1) {
   		printf("%lld\n",mp[1][1]+mp[2][1]+mp[3][1]);
   		return 0;
   	}
   	dp[1][0]=S(1,1,0,0);
   	dp[1][1]=S(1,1,2,0);
   	dp[1][2]=dp[1][3]=S(1,1,2,3);
   	dp[1][4]=-OO;
   	for(int i=2;i<n;i++) {
   		dp[i][0]=MAX4(dp[i-1][0]+S(i,1,0,0),dp[i-1][1]+S(i,1,2,0),dp[i-1][2]+S(i,1,2,3),dp[i-1][4]+S(i,1,2,3));
   		dp[i][1]=MAX4(dp[i-1][0]+S(i,1,2,0),dp[i-1][1]+S(i,2,0,0),dp[i-1][2]+S(i,2,3,0),-OO);
   		dp[i][2]=MAX4(dp[i-1][0]+S(i,1,2,3),dp[i-1][1]+S(i,2,3,0),dp[i-1][2]+S(i,3,0,0),dp[i-1][3]+S(i,1,2,3));
   		dp[i][3]=MAX(dp[i-1][0]+S(i,1,2,3),dp[i-1][3]+S(i,1,2,3));
   		dp[i][4]=MAX(dp[i-1][2]+S(i,1,2,3),dp[i-1][4]+S(i,1,2,3));
   	}
   	ans=MAX4(dp[n-1][0]+S(n,1,2,3),dp[n-1][1]+S(n,2,3,0),dp[n-1][2]+S(n,3,0,0),dp[n-1][3]+S(n,1,2,3));
   	printf("%lld\n",ans);
   	return 0;
}
```


---

## 作者：YanYou (赞：0)

奇奇怪怪的$DP$~~(大雾)~~

大概是说：

1.  因为只有三行，所以如果左边一列全选，那么只能从第一行或第三行出来；同理，全选也只能从第一或三行转移。

2. 在相邻列间向右移动后上下移动，向右移动也可以取两列。

~~有些玄乎，实在云里雾里。~~

 ```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
long long a[4][100005],f[100005][4];

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=3;++i)for(int j=1;j<=n;++j){
		cin>>a[i][j];
		a[i][j]+=a[i-1][j];
		f[j][i]=f[j][0]=-1e15;
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=3;++j)
			for(int k=1;k<=3;++k)f[i][j]=max(f[i][j],f[i-1][k]+a[max(j,k)][i]-a[min(j,k)-1][i]);
		f[i][1]=max(f[i][1],f[i-1][0]+a[3][i]);
		f[i][3]=max(f[i][3],f[i-1][0]+a[3][i]);
		f[i][0]=max(f[i][0],max(f[i-1][1],f[i-1][3])+a[3][i]);
	}
	cout<<f[n][3]<<"\n";
	return 0;
} 
```

---

