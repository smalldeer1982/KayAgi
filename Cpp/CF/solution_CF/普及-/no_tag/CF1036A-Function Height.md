# Function Height

## 题目描述

You are given a set of $ 2n+1 $ integer points on a Cartesian plane. Points are numbered from $ 0 $ to $ 2n $ inclusive. Let $ P_i $ be the $ i $ -th point. The $ x $ -coordinate of the point $ P_i $ equals $ i $ . The $ y $ -coordinate of the point $ P_i $ equals zero (initially). Thus, initially $ P_i=(i,0) $ .

The given points are vertices of a plot of a piecewise function. The $ j $ -th piece of the function is the segment $ P_{j}P_{j + 1} $ .

In one move you can increase the $ y $ -coordinate of any point with odd $ x $ -coordinate (i.e. such points are $ P_1, P_3, \dots, P_{2n-1} $ ) by $ 1 $ . Note that the corresponding segments also change.

For example, the following plot shows a function for $ n=3 $ (i.e. number of points is $ 2\cdot3+1=7 $ ) in which we increased the $ y $ -coordinate of the point $ P_1 $ three times and $ y $ -coordinate of the point $ P_5 $ one time:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1036A/04a4a03c886e714b20b2d32a2aa307f64861219c.png)Let the area of the plot be the area below this plot and above the coordinate axis OX. For example, the area of the plot on the picture above is 4 (the light blue area on the picture above is the area of the plot drawn on it).

Let the height of the plot be the maximum $ y $ -coordinate among all initial points in the plot (i.e. points $ P_0, P_1, \dots, P_{2n} $ ). The height of the plot on the picture above is 3.

Your problem is to say which minimum possible height can have the plot consisting of $ 2n+1 $ vertices and having an area equal to $ k $ . Note that it is unnecessary to minimize the number of moves.

It is easy to see that any answer which can be obtained by performing moves described above always exists and is an integer number not exceeding $ 10^{18} $ .

## 说明/提示

One of the possible answers to the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1036A/9b7ffb43d6497943731f35d46eb19664771e1698.png)The area of this plot is 3, the height of this plot is 1.

There is only one possible answer to the second example:

 ![](/predownloaded/87/0e/870ecd0db34c7f6d9c82c27dbd8add2b8f3f537c.png)The area of this plot is 12, the height of this plot is 3.

## 样例 #1

### 输入

```
4 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 12
```

### 输出

```
3
```

## 样例 #3

### 输入

```
999999999999999999 999999999999999986
```

### 输出

```
1
```

# 题解

## 作者：きりと (赞：2)

**[题目传送门](https://www.luogu.com.cn/problem/CF1036A)**

### 题目大意

见中文翻译。

### 解题思路

此题使用贪心求解，我们要让所有三角形中最长的高的长度最小，由于每个三角形的底边长相等，所以三角形的高之和是确定的，也就是$S_总=S_1+S_2+...+S_n=\frac{2*(h_1+h_2+...+h_n)}{2}=h_1+h_2+...+h_n=k$

此时我们要使最大的$h_i$尽量小，而$\sum^n_{i=1}h[i]$不变，所以必须使$h[i]$尽量平均，答案即为$\frac{k}{n}$向上取整。

### 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	int x,y;
	cin>>x>>y;
	cout<<(y+x-1)/x<<endl;   //向上取整操作
	return 0;
}
```



---

## 作者：zhangyuhao9 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1036A)

题目大意
---
翻译讲得比较清楚了，结合题目给的这张图，我们要让所有这些底为 $2$ 三角形通过若干次操作使得三角形的面积之和为 $k$ ,求其中高最大的三角形高的最小。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1036A/04a4a03c886e714b20b2d32a2aa307f64861219c.png)

题目分析
---
分别设这些三角形面积是 $S _1$ ，$S _2$ ，$S _3$ ，$ \cdots$，$S _n$。

高为 $h _1$ ，$h_2$ ，$h _3$ ，$ \cdots$，$h_n$。

因为三角形的面积为底 * 高 $/$ 2。

因此我们推得：$S=S _1+S _2+ \cdots+S _n=h _1+h _2+ \cdots+h _n=k$。

此时我们要使最大的高 $h_i$ 尽量小，而 $\sum^n_{i=1}h[i]$ 不变，所以必须使 $h[i]$ 尽可能平均。

注意：数据范围 $k$ 小于 $10$ 的 $18$ 次方。

CODE
---
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a,b,ans;
int main(){
    cin>>a>>b;
    ans=(a+b-1)/a;
    cout<<ans<<endl;
    return 0;
}
```

管理员求过。


---

## 作者：diqiuyi (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1036A)

**思路**

很显然，如果只能移动下标为奇数的点，那么这些三角形的底边的两个端点的下标就是相邻的偶数。也就是说，每条底边的长度都是 $2$。不妨设第 $i$ 个下标为奇数的点的横坐标为 $h_i$，由它组成的那个三角形 ~~也有可能是一条线段~~ 的面积为 $s_i$。显然，$\sum_{i=1}^ns_i=k$。又 $\because$ 每个三角形的底边长都为 $2$，$\therefore$ 对于每个 $i$，$s_i=\dfrac{2h_i}{2}=h_i$。也就是说，$\sum_{i=1}^nh_i=\sum_{i=1}^ns_i=k$。

于是，这个问题转化成了已知 $\sum_{i=1}^nh_i$，求最大的 $h_i$ 的最小值。众所皆知，这个问题的答案为 $\left\lceil\dfrac{k}{n}\right\rceil$，也就是 $\left\lfloor\dfrac{k+n-1}{n}\right\rfloor$。这里之所以要用第二个式子，是因为 C++ 会自动下取整。

**CODE**
```cpp
#include <bits/stdc++.h>
long long n,k;//不开 long long 见祖宗
int main(){
    scanf("%lld%lld",&n,&k);
    printf("%lld\n",(k+n-1ll)/n);
    return 0;
}
```
显然这又是一道数学题。

---

## 作者：_lgh_ (赞：1)

# 思路：
这一题其实就是思维题，因为给定面积和底，要求高最大的三角形的最小值，所以肯定要尽量平均，那么答案就是$ \lceil \frac k n \rceil $，这里来证明一下：

因为要尽量平均，不妨设这 $n$ 个高分别为 $ h_1, h_2 ......h_n$，则我们可以知道 $\sum\limits_{i=1}^nh_i=k$，那么根据尽量平均的思路，每一个都要尽量相等，于是，如果 $k|n$ ,最后结果就是 $\frac k n$ ，否则是 $\frac n k+1$ ，合在一起就写为 $\lceil \frac k n  \rceil$ 。

# 代码：
```cpp
#include<bits/stdc++.h>//万能头好东西
using namespace std;
int main()
{
    long long n,k;
    scanf("%lld%lld",&n,&k);
    printf("%lld\n",ceil(n/k));//向上取整函数ceil不知为何坏了
    return 0;
}
```


---

## 作者：makerlife (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF1036A) | [CF 原题传送门](https://codeforces.com/problemset/problem/1036/A)

~~本题难度严重低于橙题~~

## 思路

这道题思考时，不妨设第 $i$ 个三角形的高为 $h_i$，面积为 $S_i$，同时，题目还有已知条件底为 $2$。

根据三角形面积公式，我们可以得到：

$$
S=S_1+S_2+\cdots +S_n=\dfrac{(h_1+h_2+\cdots +h_n)\times 2}{2}=h_1+h_2+\cdots +h_n=k
$$
由于 $\sum_{i=1}^n h_i=k$ 不变，同时满足最大的 $h_i$ 最小，所以 $h$ 的值需要平均。

分析到这答案就出来了，即为 $\lceil \frac{k}{n}\rceil$，也就是 $\lfloor \frac{k+n-1}{n}\rfloor$。

## 代码

```cpp
#include<cstdio>
#define ll long long
ll n,k;
int main()
{
	scanf("%lld%lld",&n,&k);
	printf("%lld\n",(k+n-(ll)1)/n);
	return 0;
}
```

---

## 作者：Obviathy (赞：0)

## 前言
这道题，看似很复杂，又是什么笛卡尔坐标系，什么奇数点偶数点，其实简单的堪比A+B Problem！

## 解题思路
以为只对横坐标奇数的点进行操作，所以不难发现每一个三角形的底必为 $2$，所以根据面积公式，他的面积的数值和高相等！所以这个问题就转化成了 $n$ 个数字加起来是 $k$,问这 $n$ 个数字里最大值最小是多少。这不就是平均数吗？又因为都是整数，所以就是平均数向上去一下整罢了！

## Code
**（我这里用的 $a,b$，分别表示题目中的 $n,k$）**
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b;
int main(){
	cin >> a >> b;
	cout<<(b+a-1)/a;
	return 0;
}

```


---

## 作者：Jerrlee✅ (赞：0)

~~这算考古吗~~
## 题意
给定笛卡尔坐标系（平面直角坐标系）$x$ 轴正方向上的一条线段 $OP_{2n}$（$O$ 为原点），长度为 $n$，每次操作定义为将这条线段上任意一个下标为奇数的点向上平移一个单位。经过若干次操作后会形成许多三角形。现给定正整数 $k$，要求通过若干次操作使得三角形的面积之和为 $k$，求其中高最大的三角形其高的最小值是多少。

翻译：@yfct
## 思路
很容易看出，该图的面积是该图中所有三角形的面积之和。每次移动都会将面积增加一倍。我们不能得到小于 $[\frac{k}{n}]$ 以下的答案，但我们总能得到这样的答案。
## 代码
（自己没写，给个看到的 `Python` 吧）
```python
n,k=map(int,input().split())
print((k+n-1)//n)
```
[Python3 AC记录（洛谷）](https://www.luogu.com.cn/record/59370508)

[Python3 AC记录（CF）](https://codeforces.com/contest/1036/submission/131026692)

---

## 作者：Eason_AC (赞：0)

## Content
给定一个坐标系，在它的 $x$ 轴上有 $2n+1$ 个点 $P_0,P_1,P_2,...,P_{2n}$，其中对于 $0\leqslant i\leqslant 2n$，有 $OP_i$ 的长度为 $i$。可以执行一些操作，每次操作可将一个下标为奇数的点向上移动 $1$ 个单位，这样进行若干次操作后会形成一些三角形。现在想让所有三角形的总面积为 $k$，试求出当中的所有三角形的高的最小值。

**数据范围：$1\leqslant n,k\leqslant 10^{18}$。**
## Solution
这题目确实题意比较难懂，建议去看下原题面给的图。

这样的话，将 $P_0P_2,P_2P_4,...,P_{2n-2}P_{2n}$ 顺次连接起来，就可以获得 $n$ 条长度为 $2$ 的线段，又因为想要面积为 $k$，所以，设所有三角形的高的总和为 $h$，则 $2\times h\times\dfrac{1}{2}=k$，解得 $h=k$。所以，我们就相当于将奇数下标的点往上移动 $k$ 次了。

由于又想让高度最小，所以我们考虑尽量平均地分配每个点上移的高度。

很显然，如果 $n\mid k$ 的话，那么我们正好将其均分给每一个三角形，那么答案就是 $\dfrac{k}{n}$，否则，总会有多的一些没分到，那么就再尽量平均地分给 $k\mod n$ 个三角形，所以答案就是 $\dfrac{k}{n}+1$。

综上，答案为 $\begin{cases}\frac{k}{n}&n\mid k\\\frac{k}{n}+1&n\nmid k\end{cases}$。
## Code
```cpp
ll n, m, ans;

int main() {
	getll(n), getll(m);
	ans = (!(m % n) ? m / n : m / n + 1);
	writell(ans);
	return 0;
}
```

---

## 作者：yfct (赞：0)

## 题意

给定笛卡尔坐标系（平面直角坐标系）x轴正方向上的一条线段$OP_{2n}$（O为原点），长度为$n$，每次操作定义为将这条线段上任意一个下标为奇数的点向上平移一个单位。经过若干次操作后会形成许多三角形。现给定正整数k，要求通过若干次操作使得三角形的面积之和为$k$，求其中高最大的三角形其高的最小值是多少、

## 解题思路

既然要让高度最大的高尽量小，那么我们就要考虑“平均主义”，即：让每个三角形分摊总面积。设有$n$个三角形，其高分别为$h_1,h_2,...,h_n$，由于每次操作是平移下标为奇数的点，而奇数点必然在两个下标为偶数的点之间，因此这些三角形的底都为2。由三角形面积=底*高÷2，得$2*(h_1+h_2+...+h_n)/2=k$，那么最大高的最小值就是$n/k$.

签到题，难度较为基础，花了大概七八分钟推出来了式子。

## 代码分享
注意n%k!=0的情况要特判。

```c++
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
typedef long long ll;
ll n,k,ans;
int main() {
	scanf("%lld%lld",&n,&k);
	ans=k/n;
	if(k%n) ans++;
	printf("%lld",ans);
	return 0;
}
```

---

