# Coloring Rectangles

## 题目描述

David was given a red checkered rectangle of size $ n \times m $ . But he doesn't like it. So David cuts the original or any other rectangle piece obtained during the cutting into two new pieces along the grid lines. He can do this operation as many times as he wants.

As a result, he will get a set of rectangles. Rectangles $ 1 \times 1 $ are forbidden.

David also knows how to paint the cells blue. He wants each rectangle from the resulting set of pieces to be colored such that any pair of adjacent cells by side (from the same piece) have different colors.

What is the minimum number of cells David will have to paint?

## 说明/提示

The following pictures show how the initial rectangle can be split and cells colored blue.

In the first test case:

 ![](https://espresso.codeforces.com/d4181663ab2adbfb9f518c9f09390152197a7da9.png)In the second test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1584B/031877f8fff4a791933910251c89a32c8e77053c.png)In the third test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1584B/56c02ce81081236d5a7f494f32a723cf9e1c4a6e.png)In the fourth test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1584B/13bf05e608fac4f3bd0b4c9984699891f97a32fe.png)

## 样例 #1

### 输入

```
4
1 3
2 2
2 5
3 5```

### 输出

```
1
2
4
5```

# 题解

## 作者：让风忽悠你 (赞：3)

[原题](https://www.luogu.com.cn/problem/CF1584B)

题意比较直接，这里就不赘述了，直接讲做法。

首先从最简单的部分开始想，即只有一行或者一列的棋盘。要将其分为多个小长方形且每个小长方形中相邻方格的颜色都不同，不难想到每个棋盘都可以分为若干个长度为 3 或 2 的小长方形，此时每个小长方形只需要涂一次，而长度为 3 的小长方形越多显然是结果就更优。

进而推广到多行多列的棋盘，可以将这样的棋盘看做单行的棋盘，那就可以转化为上面的问题。

接着讲一下将单行棋盘分为长度非 3 即 2 的小长方形的做法，假设长度为 $T$，首先可以无脑的拆成长度为 3 的小长方形，拆到最后的剩下的长度只能为 0,1,2，如果是 0 就没有再拆下去的必要，如果为 2 便可以直接算为长度为 2 的长方形。如果是 1，退一步长度即为 4，就可以拆作两个长度为 2 的长方形。那么最后的结果即为 $\frac{(T+2)}{3}$。

最后给下代码（虽然好像没什么必要）

```cpp
#include<cstdio>
#include<algorithm>

using namespace std;

int T,n,m;

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		printf("%d\n",(n*m+2)/3);
	}
	return 0;
}
```


---

## 作者：_Haoomff_ (赞：2)

给你一个 $n\times m$ 棋盘，让你求出最少涂色次数。

看说明可以发现，是用 $1\times3$ 和 $1\times2$ 的两种小长方形来涂色的。为了使涂色次数最少，那么我们就要尽可能地多用  $1\times3$ 的小长方形，~~这点学过小学数学的应该都知道~~。

接下来，分类讨论：
1. 如果 $n$ 和 $m$ 中有 $3$ 的倍数，那么直接除以 $3$，因为任何数都可以整除 $1$；
2. 如何除以 $3$ 的余数是 $1$，那么就拆一个  $1\times3$，以此来凑出两个 $1\times2$；
3. 如何除以 $3$ 的余数是 $2$，那么就直接用一个 $1\times2$ 的小长方形来涂。

可得：最后的答案就是```(n*m+2)/3```。

#### 代码：
这么简单的代码本来不想放的，后来想了想，还是放一下吧。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t; 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(;t--;){
		int n,m;
		cin>>n>>m;
		cout<<(n*m+2)/3<<"\n";
	}
	return 0;
}
```


---

## 作者：luguangxing (赞：1)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1584B/56c02ce81081236d5a7f494f32a723cf9e1c4a6e.png)

我们来看这张图片。看出他把棋盘分成了两种格式，一种是 $1 \times 2$ 另一种是 $1 \times 3$ 的样式。我们把他当博弈论来想，每次我们都取最大的 $1 \times 3$ 此时有 $3$ 种情况：

+ 第一种是刚好取完就是 $0$。

- 第二种是还剩 $1$ 此时我们取什么都不好使于是就要舍去一个 $3$ 来换成两个 $1 \times 2$。  

+ 第三种是还剩 $2$ 此时就只需要再取一个 $1 \times 2$ 就满足了。

根据这 $3$ 种情况我们可以分类讨论，以下面这张图片为例，这个情况的公式就是 $n \times m \div 3$，那么我们再加 $1$ 个格子，这就是情况 $2$ 此时我们先填 $1 \times 3$ 进去，然后我们填进去了一个，但还有一个格子我们再把他拿出来，再填两个 $1 \times 2$ 进去此时公式就出来了是 $n \times m \div 3+1$ 情况 $3$ 的公式是跟情况 $2$ 一样的至此我们就推完了。

![](https://espresso.codeforces.com/d4181663ab2adbfb9f518c9f09390152197a7da9.png)


这里有两份代码有详有略请读者根据自己需要阅读。

详细代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,m;
		cin>>n>>m;
		if(n*m%3==0)
		cout<<n*m/3<<endl;
		else if(n*m%3==1)
		cout<<n*m/3+1<<endl;
		else if(n*m%3==2)
		cout<<n*m/3+1<<endl;
	}
	return 0;
}
```

稍简略代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,m;
		cin>>n>>m;
		if(n*m%3==0)
		cout<<n*m/3<<endl;
		else
		cout<<n*m/3+1<<endl;
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 思路
读题可以发现，图形会被分成 $1\times3$ 或者 $1\times2$ 两种长方形，因为的长方形面积大，所以要尽可能分出 $1\times3$ 的长方形。
## 方法
设长度是 $C$，然后疯狂的分出 $1\times3$ 的长方形，分到最后肯定剩下除 $3$ 的余数 $0$ 或 $1$ 或 $2$。如果是 $0$ 就不用管了，是 $2$ 就分出一个 $1\times2$ 的长方形，如果是 $1$ 就拆一个 $1\times3$ 的做两个 $1\times2$ 的长方形。最后得出结果 $(C+2)\div3$。
## 代码
```cpp
#include<iostream>
using namespace std;
int main(){
	int t,n,m;//定义
	cin>>t;//输入
	for(int i=1;i<=t;i++){//t组数据
		cin>>n>>m;//输入
		cout<<(n*m+2)/3<<endl;//直接套式子
	}
	return 0;
}
```

---

## 作者：Terry2011 (赞：0)

# 题目分析

题目非常良心，给了图片。不难发现，它把棋盘分成了两种形状：
 $1\times2$ 和 $1\times3$。
已知长度是 $n+m$，所以：
 
- 如果 $n$，$m$ 中有 $3$ 的倍数的，直接除以 $3$ 即可。
- 如果剩下的长度为 $1$，它便可以分成两个 $1\times2$。
- 否则，即剩下长度为 $2$，它就只有一个 $1\times2$。

综上所述，结果是`(n*m+2)/3`。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
int t,n,m;
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		cout<<(n*m+2)/3<<endl; 
	}
	return 0;
}
```

---

## 作者：felixshu (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/CF1584B)

## 分析

通过观察图示，发现把棋盘分成了两种形状。

- $1\times2$

- $1\times3$

通过计算，我们知道使用 $1\times3$ 是最好的，只有在无法使 $1\times3$ 时再去考虑使用 $1\times2$。

设总长度为 $x=m\times n$ 剩下的长度为只能为 $0,1,2$。

- 剩下的长度为 $0$ 时，直接输出 $x\div3$。

- 剩下长度为 $1$，舍弃一个 $1\times3$ 剩下长度为 $4$ 可以分成 $2$ 个 $1\times2$。

- 剩下长度为 $2$ 时，可以分成一个 $1\times2$。

最后的结果是 $(x+2)\div3$。

## 下面是 AC 代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
int t,n,m;
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		cout<<(n*m+2)/3<<endl; 
	}
	return 0;
}

```







---

## 作者：knsg251 (赞：0)

## 题目意思
给了一个 $n\times m$ 的棋盘，问最小染色的个数。
## 题目分析
我们可以看一下题目下面的样例解释图，就能发现把棋盘分成了两种正方形。

*	$1\times 3$
*	$1\times 2$

**最优的时候**一定是 $1\times 3$ 的情况，只有在**迫不得已**的情况下才会使用 $1\times 2$ 的。所以先计算总数 $x=n\times m$。

把它对 $3$ 取模后，得到的只有 $0,1,2$。

*	当得到的为 $0$ 时，就直接输出 $x\div3$。
*	当得到的为 $1$ 时，可以拿出一组来和多的 $1$ 组队。也就是组成两个 $1\times 2$ 的。
*	当得到的为 $2$ 时，就直接变成一个 $1\times 2$ 的即可。

**所以综上，答案就可以变成 $(x + 2) / 3$**。

这样就减少了判断，非常的简单，接下来直接输出即可。
## 代码实现
```cpp
	cin>>t;
	while(t--){
		scanf("%d%d",&n,&m);
		printf("%d\n",(n * m + 2) / 3);
	}
```

---

## 作者：Supor__Shoep (赞：0)

看到大佬们的方法都比我简单，那么小人就阐述一下自己的思路吧。

通过计算，我们可以得到用 $1×3$ 的方式最优，所以我们要尽可能地多用。

其实有特殊情况，如果 $n,m$ 中至少有一个为 $3$ 的倍数就输出 $n×m÷3$

除此之外，我们要用比较法计算矩阵中个数为 $3$ 的倍数的最大子矩阵计算 $n×m÷3$ 的公式。

排开刚才的最大 $3$ 倍数子矩阵，那么所剩下的子矩阵一定不是 $3$ 的倍数，我们又在这个子矩阵中找到剩下的最大 $3$ 倍数子子矩阵，又套用公式 $n×m÷3$ 。

刚才两次操作之后，剩下的子矩阵一定不是 $3$ 的倍数了，一定！！！！！

此时矩阵的 $n,m$  都小于等于 $2$ ，所以我们用他的 $n,m$ 最小值就可以了。

累加以上答案即可 AC。

然后我这复杂而晦涩的代码就是这个：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		long long n,m;
		cin>>n>>m;
		cout<<min(n/3*m+(m/3)*(n%3),m/3*n+(n/3)*(m%3))+min(n%3,m%3)<<endl;
	}
	return 0;
}
```

---

## 作者：CSP_Sept (赞：0)

**[Technocup 2022 - Elimination Round 2](http://codeforces.com/contest/1584)** [A](https://www.luogu.com.cn/blog/supervise/solution-cf1584a) / B / [C](https://www.luogu.com.cn/blog/supervise/solution-cf1584c) / [D](https://www.luogu.com.cn/blog/supervise/solution-cf1584d) / [E](https://www.luogu.com.cn/blog/supervise/solution-cf1584e) / [F](https://www.luogu.com.cn/blog/supervise/solution-cf1584f) / [G](https://www.luogu.com.cn/blog/supervise/solution-cf1584g)

如果以上链接所指链接不存在，就是作者咕了 /dk

### Description

给定一个 $n\times m$ 的矩形，你需要把它分成面积大于 $1\times 1$ 的小矩形，并对每个小矩形涂色，你需要保证在每一个小矩形中任意两个相邻格不同色。

求最小涂色次数。

### Soluition

考虑所有矩形里的最小涂色面积与总面积的比值，发现最小的是 $1\times3$ 的，比值为 $\dfrac13$。

于是我们尽量分割成 $1\times3$ 的矩形，考虑如下情况：

- $n\mid 3$ 或 $m\mid 3$：直接分。
- $n\equiv m\equiv2\pmod3$：剩下一个 $2\times 2$，加上 $2$ 次。
- $n\equiv m\equiv1\pmod3$：剩下一个 $1\times 4$，加上 $2$ 次。
- $\text{Otherwise}$：剩下一个 $1\times 2$，加上 $1$ 次。

按上述方法分讨即可，Code 可能比较繁琐。

### Code

[$\textit{135360795}$](http://codeforces.com/contest/1589/submission/135360795)

---

## 作者：hyman00 (赞：0)

# CF1584B题解

[链接](https://codeforces.ml/problemset/problem/1584/B)

## 题意

给定一个 $n\times m$ 的棋盘，你要将它沿格线切割成若干个小长方形（面积不为 1 ）。

你要将小长方形中一些 $1\times1$ 的格子（下文称作单位格）涂色，保证对于任意小长方形，任意两个相邻单位格不同色。

求最小涂色次数。

$$
1\le n,m\le 3\times10^4,nm\ge1
$$

## 解法

考虑涂色格子占的概率：

- 面积偶数： $\frac{1}{2}$
- 面积奇数： $\frac{\left\lfloor \frac{S}{2} \right\rfloor}{S}$

显然，面积奇数更优，面积越小越好，最小占比 $\frac{1}{3}$ 。

考虑构造：

- $n,m$ 中有 $3$ 的倍数的，直接分；
- 余数为 $1,1$ 或 $2,2$ 的，剩下一个 $S=4$ 的长方形，要涂 $2$ 个；
- 余数为 $1,2$ 的，剩下一个 $S=2$ 的长方形，要涂 $1$ 个。

综上，答案为 $\left\lceil \frac{nm}{3} \right\rceil$ 。

## 代码

```c++
void run(){
	int n,m;
	cin>>n>>m;
	cout<<(n*m+2)/3<<"\n";
}
```

---

## 作者：shengyeqi (赞：0)

## 题面

[题目传送门](https://www.luogu.com.cn/problem/CF1584B)

## 思路

通过观察图示可以发现，最后的图形只会剩下 $1 \times 2$ 和 $1 \times 3$ 两种长方形。

通过计算，我们把 $1 \times 3$ 认为是好的，因为只有在无法切成 $1 \times 3$ 的情况下在切 $1 \times 2$。

设总长为 $x=m \times n$,那剩下的长度为只能为 $0$,$1$,$2$。

当剩下的长度为 $0$ 时，直接输出 $x \div 3$。

当剩下的长度为 $1$ 时,就要舍弃一个 $1 \times 3$,剩下的长度就为 $4$ 可以分成两个 $1 \times 2$。

当剩下的长度为 $2$ 时，就正好可以分成一个 $1 \times 2$。

所以最后的结果是 $(x+2)\div3$。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
    scanf("%d",&t);
    while(t--)
    {
		int n,m;
        scanf("%d%d",&n,&m);
        printf("%d\n",(n*m+2)/3);
    }
    return 0;
}


```


---

