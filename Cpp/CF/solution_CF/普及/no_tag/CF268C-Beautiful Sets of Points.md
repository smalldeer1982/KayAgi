# Beautiful Sets of Points

## 题目描述

Manao has invented a new mathematical term — a beautiful set of points. He calls a set of points on a plane beautiful if it meets the following conditions:

1. The coordinates of each point in the set are integers.
2. For any two points from the set, the distance between them is a non-integer.

Consider all points $ (x,y) $ which satisfy the inequations: $ 0<=x<=n $ ; $ 0<=y<=m $ ; $ x+y&gt;0 $ . Choose their subset of maximum size such that it is also a beautiful set of points.

## 说明/提示

Consider the first sample. The distance between points (0, 1) and (1, 2) equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF268C/2826342a15affce70e459206e8466cd2b66552a3.png), between (0, 1) and (2, 0) — ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF268C/29e9747d937919d5f8da56e63d91085e91605151.png), between (1, 2) and (2, 0) — ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF268C/29e9747d937919d5f8da56e63d91085e91605151.png). Thus, these points form a beautiful set. You cannot form a beautiful set with more than three points out of the given points. Note that this is not the only solution.

## 样例 #1

### 输入

```
2 2
```

### 输出

```
3
0 1
1 2
2 0
```

## 样例 #2

### 输入

```
4 3
```

### 输出

```
4
0 3
2 1
3 0
4 2
```

# 题解

## 作者：LRL65 (赞：7)

比较简单的一道题。我们来分析一下：

题目定义：

给出一组好点的定义：

1. 所有的好点都属于整点

1. 每对好点的距离都不是整数

1. 所有好点的坐标$(x,y)(x,y)$满足有$x\in [0,n],y\in [0,m]x∈[0,n],y∈[0,m]$

1. $(0,0)(0,0)$不是好点

第一点是说坐标是整数，很好处理。第三点是说 $x$ 为 $1$ ~ $x$ 间，$y$ 为 $1$ ~ $m$ 间，就是循环的起始与结尾，也没啥难的。第四点现在也看不出啥来。

那主要的就是第2点，他说不是整数，那么选完某个点后，就不能再选和他同一列或者同一行的点了，如：选了$(1,1)(1,1)$，就不能选第一行的点和第一列的点了。好动了这个，那么稍加思考一下，就能发现好点最多为 $min(n,m)+1$。

那怎么放好点呢呢，最简单的，肯定是一条斜线了了。但是由于第四点（0，0）不是好点，所以我们必须选择这一条对角线（图1）。如图，这是一个$4*5$（ $n$ 为 $3$，$m$ 为 $4$ ）的格子，好点形成一条斜线，1为好点，0不是好点。




| 0|0  | 0 | 1 | 0 |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| 0 | 0 | 1 | 0| 0 |
| 0 | 1 | 0 | 0 |  0|
| 1 | 0 | 0 | 0 | 0 |
图1

那么每两个好点的距离应为：$\sqrt{1^2+1^2}=\sqrt{2}$，所以不是整数，符合要求。

那我们来看看坐标，这些点的坐标为（注意，$x$ 和 $y$ 都是从0开始）：

$(0,3)(1,2)(2,1)(3,0)$

那也就是$(i,min(n,m)-i)$

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main() {
    cin>>n>>m;//输入
    n=min(n,m);
    cout<<n+1<<endl;//输出最多数量
    for(int i=0;i<=n;i++)cout<<i<<" "<<n-i<<endl;//输出坐标
}
```

大佬们点个赞再走吧！

---

## 作者：boluo2014 (赞：2)

这题是神奇的大水绿！
### 思路
由于如果两个点在同一行或者同一列，那么它们的距离一定是一个整数，距离的那条线段相等于一条和 $x$ 轴或 $y$ 轴平行的一条线段。

于是，我们用组合数学中的最值问题的解题方法证明。

第一步，最大的可能数：由于不同行，不同列，因为是对称的，我们要在这个矩阵上“放”好点。我们假设 $n \le m$，在这 $n$ 行中，每行为了满足要求只能放 $1$ 个，$n$ 行最多放 $1 \times n=n$ 个。

第二部：构造，对角线啊！这个证明比较简单，写一下：

由于 $(x,y)$ 到 $(x+1,y+1)$ 的距离是 $\sqrt{2}$，那么 $(x,y)$ 到 $(x+p),(y+p)$ 的距离是 $p \sqrt{2}$，由于 $p$ 为整数，所以距离一定不是整数。

所以输出对角线坐标即可。

### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    int n,m;
    cin>>n>>m;
    n=min(n,m);
    cout<<n+1<<endl;
    int i;
    for(i=0;i<=n;i++){
        cout<<i<<' '<<n-i<<endl;
    }
    return 0;
}

```

---

## 作者：wanyiheng (赞：1)

# 思路
这是一道简单的构造题，因为不能让任意两点在同一横坐标或纵坐标上。因此想到为对角线。总数是 $\min(n,m)$ 因为从 $0$ 开始。
# Code：

```cpp
#include <bits/stdc++.h>

using namespace std;

int n,m;

int main(){
	scanf("%d%d", &n, &m);
	
	printf("%d\n", min(n,m)+1);
	
	for(int i=0;i<=min(n,m);i++)printf("%d %d\n", i, min(n,m)-i);

	return 0;
}

```

---

## 作者：szh_AK_all (赞：1)

## 题意
根据题目中好点的定义，要求我们尽可能多地构造好点。

## 分析
首先考虑好点的第一个定义和第三个定义，可以得出：每对好点的横坐标为 $0\sim n$ 中的整数，纵坐标为 $0\sim m$ 中的整数。

接着考虑第二个、第四个定义及题目要求，可得：假设平面中有一个 $(n+1)\times (m+1)$ 的矩形（因为矩形的长为 $0\sim n$，宽为 $0\sim m$），则所求好点应在这个矩形的对角线上，原因如下：
1. 由于每对好点的距离都不是整数，所以每队好点既不能同行也不能同列，所以好点的数量最多为 $\min(n,m)+1$，而对角线的长度也为 $\min(n,m)+1$；
2. 对角线中每对好点间的距离都是 $\sqrt2$ 的倍数，因为有理数乘无理数还得无理数，所以符合第二个定义；
3. 需要注意的是，由于 $(0,0)$ 不是好点，所以对角线的开端与末端应分别是 $(0,m),(\min(n,m),0)$。

由此，本题便易解了，对角线的每个点分别是 $(0,m),(1,m-1),(2,m-2)\dots$ 而总点数为 $\min(n,m)+1$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	int nm=min(n,m)+1;
	cout<<nm<<endl;
	int l=0,r=m;
	for(int i=1;i<=nm;i++)
	{
		cout<<l<<" "<<r<<endl;
		l++;
		r--;
	}
}
```
点赞吧！

---

## 作者：ModestCoder_ (赞：1)

令$x=min(n,m)+1$

可以发现最多能放$(x+1)$个点

因为每行最多放一个

如何构造达到最大值？放一条斜线就好了

比如$(0,x)(1,x-1)...(x,0)$

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	int x = min(n, m);
	printf("%d\n", x + 1);
	for (int i = 0; i <= x; ++i) printf("%d %d\n", i, x - i);
	return 0;
}
```


---

## 作者：songtaoran (赞：0)

首先，手玩一下两个样例，可得最多有 $\min(n, m) + 1$ 个点。  
看一眼第一个样例，发现大概是一个对角线。  
即：第 $i$ 个点为 $(i, \min(n, m) - i)$。  
恭喜你，这道题你 AC 了！  
证明：第 $i$ 个点和第 $j$ 个点之间的距离为 $\sqrt{(i - j)^2 + (i - j)^2} = \sqrt{2} \times (i - j)$，永远都不是整数。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n, m;
int main(){
	cin >> n >> m;
	ll t = min(n, m);
	cout << t + 1 << endl;
	for(ll i = 0; i <= t; i++) printf("%lld %lld\n", i, t - i);
	return 0;
}
```
[提交记录 - $291280121$](https://codeforces.com/problemset/submission/268/291280121)

---

## 作者：OIer_Hhy (赞：0)

非常水的一道绿题，使我的通过率暴涨。

显然，手玩一下样例，就知道好点最多数量为 $\min(n,m)+1$。

由题意知，不能让两个好点距离为整数。

怎么构造呢？我灵光一闪，突然想到了——对角线！

设 $k=\min(n,m)$，任何点 $(x,y)$ 满足 $x+y=k$ 且 $x,y \in N$，它们都是好点！

于是——你 AC 了！

my code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main() {
    cin>>n>>m;
    n=min(n,m);
    cout<<n+1<<endl;
    for(int i=0;i<=n;i++) cout<<i<<" "<<n-i<<endl;
}
```

---

## 作者：ny_Dacong (赞：0)

# 思路

既然不能让任意两点距离为整数，那么就不能让任意两点在同一条横轴或纵轴上。因此容易想到，最优的方案是对角线。

那么总数的统计就很简单了。总数是 $\min (n+1,m+1)$（因为坐标从 0 开始）。然后输出一条对角线即可。

注意，题目要求不能选 $(0,0)$。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,tot = 0,a,b;
int main(){
	scanf("%d%d",&n,&m);
	printf("%d\n",min(m+1,n+1));
	a = n,b = 0;
	while(tot < min(m+1,n+1)){
		printf("%d %d\n",a,b);
		a--,b++;
		tot++;
	}
	return 0;
}
```

---

## 作者：Milthm (赞：0)

## CF268C题解

这题是一道简单的构造题。给了你四个要求，分别为：

- 所有的好点都属于整点
- 每对好点的距离都不是整数
- 所有好点的坐标 $(x,y)$ 满足有 $x\in [0,n],y\in [0,m]$。
- $(0,0)$ 不是好点

首先观察要求一和三，没有什么好说的，坐标必须是整点，在 $n,m$ 的矩阵内。最主要的是要求二，我们发现如果一对好点在同一排或同一列，那么它们的距离一定是整数，所以我们如果选了一个点，就不能选和它在同一排或同一列的点了。经过观察，我们可以选一个对角线，这样可以使好点的个数最多。但是因为 $(0,0)$ 不是好点，所以我们可以选另一条对角线 $(0,x),(1,x-1),……,(x,0)$，其中的 $x$ 代表 $\min(n,m)$ 的值。

### AC代码
```cpp
#include<iostream>
#define int long long
using namespace std;
int n,m;
signed main(){
    cin>>n>>m;
    cout<<min(n,m)+1<<endl;
    for(int i=min(n,m);i>=0;i--)cout<<i<<" "<<min(n,m)-i<<endl;
    return 0;
}
```





---

## 作者：da32s1da (赞：0)

一道比较简单的构造题。

首先答案一定不会超过$\min(n,m)+1$。

这是因为一行**最多放一个**，若放$2$个，则**距离就是整数**了，不符题意。

令$x=\min(n,m)$

比较容易想到$(0,0),(1,1)...(x,x)$为好点，但是题目中要求$(0,0)$不是好点，所以是不行的。

所以**换一条对角线**，即$(0,x),(1,x-1)...(x,0)$即可。

```
#include<cstdio>
int n,m,qwq;
inline int min(int u,int v){return u<v?u:v;}
int main(){
	scanf("%d%d",&n,&m);
	qwq=min(n,m);
	printf("%d\n",qwq+1);
	for(int i=qwq;i>=0;i--)printf("%d %d\n",i,qwq-i);
}
```

---

