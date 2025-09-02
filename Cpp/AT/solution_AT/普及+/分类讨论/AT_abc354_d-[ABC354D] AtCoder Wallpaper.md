# [ABC354D] AtCoder Wallpaper

## 题目描述

将 AtCoder 社的壁纸图案表示在 $xy$ 平面上，如下所示。

- 该平面被以下 $3$ 类直线分割：
  - $x = n$（$n$ 为整数）
  - $y = n$（$n$ 为偶数）
  - $x + y = n$（$n$ 为偶数）
- 每个区域被涂成黑色或白色。任意一条直线相邻的两个区域颜色不同。
- 包含点 $(0.5, 0.5)$ 的区域被涂成黑色。

下图展示了该图案的一部分。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc354_d/1813abe2f2a9c36459abd56b5463d1fab3634991.png)

给定整数 $A, B, C, D$。考虑一个各边与 $x$、$y$ 轴平行、左下顶点为 $(A, B)$、右上顶点为 $(C, D)$ 的矩形。请计算该矩形内部被涂成黑色的区域的面积，并输出其 $2$ 倍的值。

可以证明，输出的值一定为整数。

## 说明/提示

## 限制条件

- $-10^9 \leq A, B, C, D \leq 10^9$
- $A < C$ 且 $B < D$
- 输入均为整数

## 样例解释 1

要求的是下图正方形包围的区域内被涂成黑色的区域面积。![](https://img.atcoder.jp/abc354/d_img2_zzwqsaaewub.png) 该面积为 $5$，因此输出 $2$ 倍后的 $10$。

## 样例解释 2

面积为 $5.5$，虽然是小数，但应输出的值为整数。

## 样例解释 3

这是矩形取最大范围的情况，但输出仍在 64 位有符号整数范围内。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
0 0 3 3```

### 输出

```
10```

## 样例 #2

### 输入

```
-1 -2 1 3```

### 输出

```
11```

## 样例 #3

### 输入

```
-1000000000 -1000000000 1000000000 1000000000```

### 输出

```
4000000000000000000```

# 题解

## 作者：泥土笨笨 (赞：21)

# 题意简述

题目中给我们一个无限大的地面，在地面上有图中样式的花纹。然后题目当中给我们一个矩形，矩形的左下角的坐标是 $(A,B)$，右上角的坐标是 $(C,D)$，让我们计算这个矩形内部黑色部分的面积的二倍。题目中让我们求的答案是黑色部分面积的二倍，这样可以保证这个数字一定是整数。

# 思路

## 平移到第一象限内部

首先我们发现这道题目当中的情况非常的多，如果我们要列举的话会非常的复杂。所以我们的第一步想法应该是先进行一个化归，把各种各样的情况统一成一种，这样我们后面好处理。

比如说题目当中给我们的矩形，它的左下角可能在各个象限内部。如果我们对每一种情况都去列举的话，那可能情况就太多了，所以我们想能不能把这个矩形在图片内部进行一个平移，只要平移的过程当中答案不变，我们就可以把它挪到任何一个位置，最好把整个矩形都挪到第一象限去，这样的话我们计算就只有一种情况了。

仔细观察题目中给我们的图片，我们会发现可以把它看成是 $4 \times 4$ 的小正方形无限的拼接，所以其实我们可以认为如果平移的长度是四的倍数的话，那在平移过程当中整个矩形内部黑色的面积是不变的。

比如在下面这张图片当中，我们要求的是红色部分的矩形的面积，我们可以把它平移到黄色的部分，沿着 $X$ 轴的正方向移动八个单位，沿着 $Y$ 轴的正方向移动四个单位，因为 $X$ 轴和 $Y$ 轴移动的长度都是四的倍数，所以它图形内部的形状是不变的，黑色部分的面积自然也是不变的。

![](https://cdn.luogu.com.cn/upload/image_hosting/di4m37e4.png)

题目中给我们的数据范围是在正负 $10^9$ 之间，所以我们可以输入之后把所有的坐标都加一个 $10^9$，这样我们就可以保证这个正方形一定会被平移到第一象限范围之内，因为 $10^9$ 是四的倍数，所以我们这样做平移可以让我们的答案不变，而我们的计算过程就简化了很多，只要考虑矩形在第一象限内部的情况就行了。

## 转化成左下角是原点的情况

现在我们的矩形一定在第一象限内部了，但是我们的计算还是很复杂，因为如果我们认为每一个 $4 \times 4$ 的方块是一个图案的话，我们的矩形的左下角可能在图案的任何一个位置，右上角也可能在图案的任何一个位置。所以我们要考虑进一步简化这个问题，看下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/hkah1nyc.png)

我们要求的是图当中红色的矩形内部的答案，我们可以把它变成四个矩形来拼凑。首先是我们用一个黄色的矩形内部的答案，减去浅蓝色矩形内部的答案，再减去棕色矩形内部的答案。这个时候我们发现我们减重复了一块，所以我们要把浅蓝色和棕色中重复的那一部分内部的答案再加回来，这样就可以得到我们想要的红色举行内部的答案。

这个时候我们发现我们要求的所有矩形的答案都是以原点作为左下角的，只是右上角不同而已，所以问题得到了进一步的简化，我们现在只需要想办法求出任何一个以原点为左下角，$(x,y)$ 为右上角的矩形内部的答案，把它写成一个函数，然后调用这个函数四遍，加加减减拼凑一下就可以得到我们想要的任何一个第一象限矩形内部的答案。

## 写一个辅助计算函数

![](https://cdn.luogu.com.cn/upload/image_hosting/b7dqjo1u.png)

如上图，我们现在想计算这个矩形内部的答案，我们可以把它分成几部分，首先是它内部有很多个完整的 $4 \times 4$ 的方块，这部分的答案我们可以数出他在 $X$ 方向有多少个完整的方块，记做 $xCnt$。在 $Y$ 方向有多少个完整的方块，记做 $yCnt$。然后把它们乘在一起再乘以每个方块内部的答案就可以了，这里面的每个方块的边长都是四。除此之外，在横着的方向竖着的方向还各有一个长条，这里面的答案我们要计算。最后在右上角还有一个小块，它是一个不够 $4 \times 4$ 的小块，它内部的答案我们要计算。

为了方便计算，我们可以事先打一个表，这个表的内部是当 $X$ 和 $Y$，都在四以内的时候我们的答案。那么这样的话，上面的那一个长条，它的答案就应该等于横着方向完整方块的个数乘以长条内部的一个方块内的面积。竖着的方向的长条的计算也是同理。最后右上角的小矩形的答案，可以直接从这个表格当中拿到。

当我们这个辅助函数写完之后，我们这道题就几乎做完了，最后是代码时间。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;

// 计算第一象限中(x,y)点，与原点围成的矩形范围内的答案
// 预先打出来(x,y) 在 4*4 的小正方形内部的答案
ll table[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 2, 3, 5, 6},
        {0, 3, 6, 9, 12},
        {0, 3, 7, 10, 14},
        {0, 4, 8, 12, 16}
};

//计算第一象限中(x,y)点，与原点围成的矩形范围内的答案
ll cal(ll x, ll y) {
    //计算x方向和y方向有多少个完整的4*4方格
    ll xCnt = x / 4;
    ll yCnt = y / 4;
    //完整的部分答案先计算出来
    ll ans = xCnt * yCnt * table[4][4];
    x = x % 4;
    y = y % 4;
    ans += xCnt * table[4][y];
    ans += yCnt * table[x][4];
    ans += table[x][y];
    return ans;
}

int main() {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    //先平移到第一象限去
    a += 1e9, b += 1e9, c += 1e9, d += 1e9;
    ll ans = cal(c, d) - cal(a, d) - cal(c, b) + cal(a, b);
    cout << ans << endl;
    return 0;
}
```

---

## 作者：233L (赞：5)

分讨题尽量不分讨。首先注意到这个图案在横坐标的周期是 $4$，纵坐标的周期是 $2$，于是我们可以把矩形平移到第一象限。（横坐标向右平移 $4x$，纵坐标向上平移 $2y$）接着把矩形差分，记 $f(x,y)$ 表示原点到 $(x,y)$ 这个矩形的答案，那么我们要求的就是 $f(B,D)-f(A,D)-f(B,C)+f(A,C)$。

于是现在只要考虑如何求 $f(X,Y)$。若 $X$ 是 $4$ 的倍数，$Y$ 是 $2$ 的倍数，那么答案就是 $8 \frac X 4 \frac Y 2$。所以我们对 $X \bmod 4,Y \bmod 2$ 分讨。

若 $Y\bmod 2=1$，我们先把最上面一行（下图中标绿部分）算出来，然后再求 $f(X,Y-1)$。（下图每个格子的数字代表对答案的贡献，粗线矩形代表 $(0,0),(X,Y)$ 这个矩形）

![image-20240521175833442.png](https://img2.imgtp.com/2024/05/21/jODSSMVP.png)

至于最上面一行怎么算：

```cpp
int s1(int x){
    int a[4]={0,2,3,3};
    return 4*(x/4)+a[x&3];
}
```

每 $4$ 格的和为 $4$，余数单独处理。

接着算下图这一部分，和上面的方法类似。最后一部分的答案就是最简单的 $8 \frac X 4 \frac Y 2$。

![image-20240521180223337.png](https://img2.imgtp.com/2024/05/21/89i32OND.png)

[submission](https://atcoder.jp/contests/abc354/submissions/53612511)

---

## 作者：LuukLuuk (赞：4)

# 题解：AT_abc354_d [ABC354D] AtCoder Wallpaper

题目大意
------------------------------------------
有一个如下图的表格：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc354_d/1813abe2f2a9c36459abd56b5463d1fab3634991.png)
给你一组 $A,B,C,D$，求表格中的 $(A,B)$ 到 $(C,D)$ 所框出的矩形的阴影面积乘以二的值。

解题思路
--------------------------------------
在下文中，为了方便，我们姑且设我们每一步求出来的面积都默认乘以了 $2$。

因为有负数的情况，我们首先给所有数加上 $10^9$（数据范围是 $-10^9 \le A,B,C,D \le 10^9$）使他们变成正数。由观察上图可知，上图会以一个 $4 \times 2$ 的矩阵重复，如下图：![](https://cdn.luogu.com.cn/upload/image_hosting/lt4jnshq.png)

因此因为 $10^9 \bmod 4 = 0$ 且 $10^9 \bmod 2 = 0$，所以加上 $10^9$ 后坐标轴的 $(0,0)$ 点显示的图案和上图还是一样的。并且，我们可以发现每一个矩阵的阴影为其本身的面积 $8$。

因此我们可以想到前缀和求解，设 $S(i,j)$ 表示从原点到 $(i,j)$ 的面积，例如 $A=5,B=3,C=10,D=7$ 时：
![](https://cdn.luogu.com.cn/upload/image_hosting/2dbd3d5o.png)
$ANS=S(10,7)-S(5,7)-S(10,3)+S(5,3)$

接下来，主要问题就落在了如何求解 $S(i,j)$ 上。
我们可以尝试分类讨论：（设此时 $x=i \bmod 2, y = j \bmod 4$）

>1. 有偶数行，此时 $x = 0$：
>>1. $y = 0$：我们可以很容易地发现，此时图由数个完整的矩阵拼成，$S(i,j) = i \times j$（上文说过，当有完整矩阵时，这些完整矩阵的阴影面积为其本身的面积）。如下图：
>>>![](https://cdn.luogu.com.cn/upload/image_hosting/2oqim555.png)
>>2. $y = 1$：我们可以运用(1)的结论，则前 $i-1$ 行的阴影面积为 $(i-1) \times j$，又因为我们是从 $(0,0)$ 开始的，所以剩下的必然是 $y \div 2$ 个阴影面积为 $3$ 的小方格：
>>>![](https://cdn.luogu.com.cn/upload/image_hosting/wl5t17l3.png)
>>
>>所以，此时 $S(i,j)=(i-1) \times j + 3 \times j \div 2$。
>>
>>3. $y = 2$：同理，$S(i,j) = (i - 2) \times j + 6 \times j \div 2$。
>>>![](https://cdn.luogu.com.cn/upload/image_hosting/bdxvqf4s.png)
>>4. $y = 3$：一样的，$S(i,j) = (i - 3) \times j + 7 \times y \div 2$。
>>>![](https://cdn.luogu.com.cn/upload/image_hosting/e4nlyvcz.png)
>2. 有奇数行，此时 $x = 1$：
>>1. $y = 0$：在算完所有的完整矩阵后，我们可以发现剩下了半个完整矩阵，例如下图：
>>>![](https://cdn.luogu.com.cn/upload/image_hosting/4vo684bs.png)
>>>
>>因为我们从 $(0,0)$ 开始，所以只用考虑上述情况（当然，无论是小矩阵的第一行还是第二行，它们的面积都是 $4$），所以 $S(i,j) = i \times j$。
>>
>>2. $y=1$，此时我们剩了一行一列，我们可以套用前面的结论减少复杂度，因为 $x=i\bmod 2=1$，所以 $(x-1)=i\bmod 2-1=0$，下图红框加绿框等于 $S(i-1,j)$，即 $x=0,y=1$ 的情况，接下来我们可以用 $x=1,y=0$ 的情况处理黄框，其面积为 $j-1$，而因为我们是从 $(0,0)$ 开始的，所以蓝框只能是下图蓝框的情况，即 $2$。因此，$S(i,j)=S(i-1,j)+(x-1)+2=S(i-1,j)+x+1$。
>>>![](https://cdn.luogu.com.cn/upload/image_hosting/ipmqd5ig.png)
>>3. $y=2$，同理，蓝框剩了 $3$，$S(i,j)=S(i-1,j)+(x-2)+3=S(i-1,j)+x+1$。
>>>![](https://cdn.luogu.com.cn/upload/image_hosting/57cr8558.png)
>>4. $y=3$，蓝框还是剩了 $3$， $S(i,j)=S(i-1,j)+(x-3)+3=S(i-1,j)+x$。
>>>![](https://cdn.luogu.com.cn/upload/image_hosting/dc9ruhkf.png)

以上就是分类讨论的所有情况，讨论完后我们便就可以用最初的前缀和来完成这道题了：（要开 `long long` ）
```c
#include <cstdio>
using namespace std;

long long a, b, c, d;

long long get_sum(long long x, long long y) {
	long long ans;
	long long a1 = x % 4, b1 = y % 2;//这里的a1就是上文的x，b1就是上文的y
	if (x == 0 || y == 0)	return 0;
	if (b1 == 0) {
		if (a1 == 0) {
			return x * y;
		}
		if (a1 == 1) {
			return (x - 1) * y + y / 2 * 3; 
		}
		if (a1 == 2) {
			return (x - 2) * y + y / 2 * 6;
		}
		if (a1 == 3) {
			return (x - 3) * y + y / 2 * 7;
		}
	}
	if (b1 == 1) {
		if (a1 == 0) {
			return x * y;
		}
		if (a1 == 1) {
			return get_sum(x, y - 1) + x + 1;
		}
		if (a1 == 2) {
			return get_sum(x, y - 1) + x + 1; 
		}
		if (a1 == 3) {
			return get_sum(x, y - 1) + x;
		}
	}
}

int main() {
	scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
	a += 1000000000, b += 1000000000, c += 1000000000, d += 1000000000;
	printf("%lld", get_sum(c, d) - get_sum(a, d) - get_sum(c, b) + get_sum(a, b));
	return 0;
}
```

---

## 作者：FallingFYC_ (赞：2)

[原题](https://www.luogu.com.cn/problem/AT_abc354_d)

在学校推了一午休~（题解区最复杂的思路）

---
### 思路

分讨，但我的思路更粗暴一点。

经过观察，可以发现图像的第 $x$ 行与第 $(x+2)$ 行相同，第 $y$ 列与第 $(y+4)$ 列相同。

我的思路是以 $(a,b)$ 为原点将每个 $2 \times 2$ 的部分组成互不重合的“大格子”，在一个图中最多会有两种这样的大格子。先根据如上规律先计算出一行的阴影面积，再乘上大格子的列数，当 $c-a$ 或 $d-b$ 为奇数时，会出现多出来一行或一列的情况，此时单独处理，最终得到总阴影面积再乘二。

如下图，红框与篮框代表两种大格子：

![qwq](https://cdn.luogu.com.cn/upload/image_hosting/uuq1e1ws.png)

~~难道你第一眼看到这图不觉得是这样排列的吗？~~

首先分讨两种大格子的外形，共分八种情况，当 $b$ 为奇数或偶数时各再分 $a \bmod 4=0,1,2,3$ 四种情况，其中需要记录的八个数值：$S_1,S_2,S_3,S_4,S_5,S_6,S_7,S_8$，其关系如下图所示：

![awa](https://cdn.luogu.com.cn/upload/image_hosting/zg01to5m.png)

之后对多出来的一行进行处理，定义 $la=c-a,lb=d-b,sx=\lfloor \frac{lx}{2} \rfloor,sy=\lfloor \frac{ly}{2} \rfloor,S_l,S_阴$，其中 $la,lb$ 代表查询矩形的长和宽，$sx,sy$ 代表长和宽分别能放几个大格子，$S_l$ 代表一行大格子阴影部分的面积，$S_阴$ 代表总阴影面积。

先处理右边多出一列的情况，分讨如果 $lx$ 是偶数，$S_l=\lceil \frac{sx}{2}\rceil\times S_1+\lfloor \frac{sx}{2}\rfloor\times S_5$，反之，在其基础上再加上多出来一列的阴影面积（这里可能用到 $S_2,S_3,S_6,S_7$）。

然后令 $S_阴=S_l\times sy$。

再处理顶部多处一行的情况，分讨如果 $ly$ 是偶数，不变，反之定义 $S_{tl}$ 为顶部多处一行的阴影面积，如果 $lx$ 是偶数 $S_{tl}=\lceil \frac{sx}{2}\rceil\times (S_3+S_4)+\lfloor \frac{sx}{2}\rfloor\times (S_7+S_8)$，反之，在其基础上再加上右上角剩余的一个格子的阴影面积（这里可能用到 $S_3,S_4,S_7,S_8$），最后将 $S_{tl}$ 加到 $S_阴$ 里。

最后输出 $S_阴 \times 2$。

**注意：记得开 `long double`**（至少我在此处挂了很多次）。

---
### [代码](https://atcoder.jp/contests/abc354/submissions/53745509)

---

## 作者：tder (赞：2)

[ABC354 场记](https://tder6.github.io/articles/ABC354A%20to%20ABC354E%20%E5%9C%BA%E8%AE%B0.html) 食用效果更佳。 

---

**【题意】**

给定如图所示的网格图，求指定的矩形 $ABCD$ 中所包含的黑色部分面积的二倍。

**【思路】**

下文用形如「矩形是 $x\times y$ 的」语句表示这个矩形的横向长度为 $x$，而纵向长度为 $y$。

观察得到：

> 结论：任意横向连续 $4$ 个单位正方形中黑白各半。
>
> 证明：显然的。可找规律验证，如下图所示。
> 
> ![](https://cdn.luogu.com.cn/upload/image_hosting/ankeyfhh.png)

利用这个结论，我们不妨将原来的四边形分为两部分：横向长为 $4$ 的倍数的一部分，以及其余部分。

即对于如下图所示的 $10\times8$ 的矩形，可以分为右边 $8\times8$ 的矩形和左边是 $2\times8$ 的矩形：

![](https://cdn.luogu.com.cn/upload/image_hosting/kyhz3241.png)

因此，右边的贡献为 $2\times\dfrac{8\times8}2=64$。

不妨推广到一般，即 $A(a,b)$ 和 $C(c,d)$：

> 结论：右边的贡献为 $(d-b)\cdot\left(\left\lfloor\dfrac{(c-a)}4\right\rfloor\cdot4\right)$。
> 
> 证明：原矩形是 $(c-a)\times(d-b)$ 的。为使横向长度为 $4$ 的倍数，最大为 $h=\left\lfloor\dfrac{(c-a)}4\right\rfloor\cdot4$，故贡献为 $2\times\dfrac{(d-b)\cdot h}2=(d-b)\cdot h$。得证。

此后左边部分的右上点 $C'$ 的横坐标即为 $c'=c-\left\lfloor\dfrac{(c-a)}4\right\rfloor\cdot4$。故此，其是 $\left(c'-a\right)\times(d-b)$ 的。

那么考虑如何求出左边的贡献，此时便需要分类讨论四种不同的列。如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/lr3zn6qw.png)

下面用列或单位正方形的左下角坐标表示其坐标。

先看红色的列，即 $x\bmod4=0$ 时，每连续两个单位正方形的贡献为 $3$。对于单个偶数单位正方形，即 $y\bmod2=0$ 时，其贡献为 $2$。反之同理，单个奇数单位正方形的贡献为 $1$。

依次类推，用 $p_k$ 表示对于所有 $x\bmod 4=k$ 的列，其每连续两个单位正方形的贡献。而 $q_{f,k}$ 表示该列中，单个满足 $y\bmod2=f$ 的单位正方形的贡献。

容易得到：

| $k$ | $0$ | $1$ | $2$ | $3$ |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $p_k$ | $3$ | $3$ | $1$ | $1$ |
| $q_{0,k}$ | $2$ | $1$ | $0$ | $1$ |
| $q_{1,k}$ | $1$ | $2$ | $1$ | $0$ |

不妨用 $p'_{k}$ 表示 $p_{(k\bmod4)}$ 且 $q'_{f,k}$ 表示 $q_{(f\bmod2),(k\bmod4)}$。

综上，则有：

> 结论：左边的贡献为 $\displaystyle\left(\sum_{x=a}^{c'}\left(\left\lfloor\dfrac{d-b}2\right\rfloor\cdot p'_x\right)\right)+[(d-b)\bmod2=1]\cdot\left(\sum_{x=a}^{c'}q'_{b,x}\right)$。
> 
> 证明：对于每个 $x$ 都能分成 $\left\lfloor\dfrac{d-b}2\right\rfloor$ 个连续两个单位正方形。特别的，当 $d-b$ 为奇数时会多出一个单独的单位正方形，此时需要加上 $q'_{b,x}$ 的贡献。得证。

另附赛时草稿：

![](https://cdn.luogu.com.cn/upload/image_hosting/eqm9z1js.png)

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e5 + 5, INF = 1e18;
int a, b, c, d, ans;
const int p[4] = {3, 3, 1, 1};
const int q[2][4] = {
	{2, 1, 0, 1},
	{1, 2, 1, 0}
};
signed main() {
	cin>>a>>b>>c>>d;
	ans = (d - b) * ((c - a) / 4 * 4);
	c -= ((c - a) / 4 * 4);
	// cout<<ans<<" "<<c<<endl;
	for(int i = a; i < c; i++) ans += ((d - b) / 2) * p[(i + INF) % 4];
	if((d - b) % 2) for(int i = a; i < c; i++) ans += q[(b + INF) % 2][(i + INF) % 4];
	cout<<ans<<endl;
}
```

---

## 作者：Heldivis (赞：1)

# ABC354D

考虑如果分类讨论，就很麻烦。

很好算出来每一个矩形内，和矩形左下角相同方格个数：

```cpp
int Calc(int a, int b, int c, int d) {
  return (c <= a || d <= b) ? 0 : ((c - a - 1) / 4 + 1) * ((d - b - 1) / 2 + 1);
}
```

预处理以点 $(i,j)$ 左下角单位方格的权值 $w_{i,j}$。

枚举左下角的位置（一共八种），乘上矩形内和左下角相同方格的数量。

将这八种情况累加起来，即为最后答案。

*Code:*

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int read() {...}
int Calc(int a, int b, int c, int d) {
  return (c <= a || d <= b) ? 0 : ((c - a - 1) / 4 + 1) * ((d - b - 1) / 2 + 1);
}
int w[10][10];
signed main() {
  w[0][0] = 2; w[1][0] = 1; w[2][0] = 0; w[3][0] = 1;
  w[0][1] = 1; w[1][1] = 2; w[2][1] = 1; w[3][1] = 0;
  int a = read() + 2000000000, b = read() + 2000000000,
      c = read() + 2000000000, d = read() + 2000000000;
  int res = 0;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 2; j++)
        res += Calc(a+i, b+j, c, d) * w[(a+i)%4][(b+j)%2];
  printf("%lld", res);
  return 0;
}
```

---

## 作者：Dtw_ (赞：0)

[at](https://atcoder.jp/contests/abc354/tasks/abc354_d)
# 前言
文中的括号均表示点的坐标。

这题跟以前的 [D 题](https://atcoder.jp/contests/abc331/tasks/abc331_d) 很像。
# 思路
观察图片，我们发现，每 $4 \times 2$ 的一个小矩形为一个循环。

![](https://cdn.luogu.com.cn/upload/image_hosting/6gvq6jj4.png)

那么我们就考虑二维前缀和来计算一个区间的值。

定义一个函数 $f(x,y)$ 为 $(0,0)$ 到 $(x,y)$ 的阴影部分面积。我们可以用一个前缀和来求出那个小矩形的面积，然后考虑如何求这个大的。

首先我们肯定知道他并不是完整的一些小矩形拼来的，但是在我们要求的区间里一定会存在一下几种矩形。

1. 完整的小矩形
2. 长完整但宽不完整的矩形
3. 宽完整但长不完整的矩形
4. 长宽都不完整的矩形

画个图吧。

![](https://cdn.luogu.com.cn/upload/image_hosting/1uhdkqp6.png)

那么我们就可以算出任意 $f(x,y)$ 然后根据二维前缀和来计算最终的答案。即：

$$f(c,d)-f(c,b)-f(a,d)+f(a,b)$$

然后大致思路就是这样。

# 实现
本题最重要的部分在于 $f(x,y)$ 这。

首先我们要求小矩形的前缀和，但发现有非整数的面积，但是都是 $0.5$ 我们可以在这里就先 $S\times 2$ 这样后面就不用再算了。

然后考虑到有负数的情况，所以我们加一个偏移量，设 $T =10^9$ 我们每次计算 $f(x,y)$ 的时候都将 $x,y$ 统一加上 $T$ 即可。那么我们现在计算的就是 $(-10^9,-10^9)$ 到当前位置的值。

关于各部分的计算：

无坑的就不说了。

当我们在求上图中 $2$ 的部分的面积时发现，此时我们求了竖着剩下的长度，即 $x \bmod 2$ 但是发现他可能为 $1$ 而此时我们要求的是第二行的和，可我们访问的是第一行的前缀和，所以我们有手动改一下存的顺序。代码中我用的 `o[i][j]` 存的修改顺序后的前缀和。

还有我们计算的是从 $(-10^9,-10^9)$ 到当前位置的值，所以我们的前缀和应从 $(1,2)$ 开始计算直到 $(1,4)$ 为止。

反正细节挺多的。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define fi first
#define se second

#define IN(o) insert(o)

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int T = 1e9;

const int P = 998244353;

const int N = 1e6 + 10;

int a[10][10];

int s[10][10], o[10][10];

// 注意本题不需要开 __int128

int calc(int x, int y)
{
	int h = x / 4;
	int l = y / 2;
	int sum1 = h * l * o[2][4];
	int sum2 = l * o[2][x % 4];
	int sum3 = h * o[y % 2][4];
	int sum4 = o[y % 2][x % 4];
	int sum = sum1 + sum2 + sum3 + sum4;
//	cout << sum1 << " " << sum2 << " " << sum3 << " " << sum4 << " " << sum << endl;
	return sum;
}

signed main()
{
	a[1][1] = a[2][2] = a[1][3] = a[2][4] = 1;
	a[2][1] = a[1][2] = 2; // 提前乘2
	int p = 1, q = 1; // 现在要存 o[p][q]
	for(int i=2; i>=1; i--)
	{
		for(int j=1; j<=4; j++)
		{
			s[i][j] = s[i][j-1] + s[i+1][j] - s[i+1][j-1] + a[i][j]; // 前缀和正常算
			o[p][q] = s[i][j];
			q++;
		}
		p++;
		q = 1;
	}
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	int res = calc(c + T, d + T) - calc(c + T, b + T) - calc(a + T, d + T) + calc(a + T, b + T);
	cout << res;
	return 0;
}




```

---

## 作者：whx2009 (赞：0)

## 本题思路：
这是一道经典的规律题，我们可以发现在 $x$ 轴上以四为一个周期，只要是在一个周期的黑色一定占了总量的一半，这样我们就可以很容易的想到把这个正方形的两个控制 $x$ 轴坐标的移到几个周期拼起来的情况。

这操作还是很简单的，我们只用分类讨论即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	int a,b,c,d,ans=0;
	cin>>a>>b>>c>>d;
		int x1=a,x2=c,y1=b,y2=d;
		while(x1<x2 && x1%4!=0){
			if((x1-1)%4==0){
				int u=y1,v=y2;
				if(abs(u)%2==1) u++,ans+=2;
				if(abs(v)%2==1) v--,ans+=1;
				if(u<v)ans+=3*((v-u)/2);
			}
			if((x1-2)%4==0){
				int u=y1,v=y2;
				if(abs(u)%2==1) u++,ans+=1;
				if(abs(v)%2==1) v--;
				if(u<v)ans+=((v-u)/2);				
			}
			if((x1-3)%4==0){
				int u=y1,v=y2;
				if(abs(u)%2==1) u++;
				if(abs(v)%2==1) v--,ans+=1;
				if(u<v)ans+=((v-u)/2);		
			}
			x1++;
		}
		while(x2>x1 && x2%4!=0){
			if((x2+2)%4==0){
				int u=y1,v=y2;
				if(abs(u)%2==1) u++,ans+=2;
				if(abs(v)%2==1) v--,ans+=1;
				if(u<v)ans+=3*(((v-u)/2));
			}
			if((x2+1)%4==0){
				int u=y1,v=y2;
				if(abs(u)%2==1) u++,ans+=1;
				if(abs(v)%2==1) v--;
				if(u<v)ans+=((v-u)/2);			
			}
			if((x2+3)%4==0){
				int u=y1,v=y2;
				if(abs(u)%2==1) u++,ans+=1;
				if(abs(v)%2==1) v--,ans+=2;
				if(u<v)ans+=3*((v-u)/2);
			}		
			x2--;
		}
		ans+=(x2-x1)*(y2-y1);
	cout<<ans;
	return 0;
}

```

---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题解
不难发现横排 $4$ 个为一周期，竖排 $2$ 个为一周期，贡献分别是：

- $A_1={2,1,2,1,2,...}$
- $A_2={1,2,1,2,1,...}$
- $A_3={1,0,1,0,1,...}$
- $A_4={0,1,0,1,0,...}$

我们可以通过先预处理出在 $[a,c]$ 中 $[b,d]$ 这个区间的价值，不难发现没 $4$ 个为一周期，再算有几个循环，剩余的求一个前缀和就行。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d,p,ans,tmp,x[10];
int main()
{
	cin>>a>>b>>c>>d,p=a;
	while(tmp<4&&a<=c)
	{
		a++;
	    tmp++;
	    x[tmp]+=x[tmp-1];
		if((a%4+4)%4==1)
		{
			x[tmp]+=3*((d-b)/2);
			if((d-b)%2==1)
			{
				if(((d%2)+2)%2==1)x[tmp]+=2;
				else x[tmp]+=1;
			}
		}
		if((a%4+4)%4==2)
		{
			x[tmp]+=3*((d-b)/2);
			if((d-b)%2==1)
			{
				if(((d%2)+2)%2==1)x[tmp]+=1;
				else x[tmp]+=2;
			}
		}
		if((a%4+4)%4==3)
		{
			x[tmp]+=(d-b)/2;
			if((d-b)%2==1)
			{
				if(((d%2)+2)%2==1)x[tmp]+=0;
				else x[tmp]+=1;
			}
		}
		if((a%4+4)%4==0)
		{
			x[tmp]+=(d-b)/2;
			if((d-b)%2==1)
			{
				if(((d%2)+2)%2==1)x[tmp]+=1;
				else x[tmp]+=0;
			}
		}
	}
	cout<<x[4]*((c-p)/4)+x[(c-p)%4];
} 
```

---

## 作者：forever_nope (赞：0)

容易发现（~~观察图像~~），

$$
x\gets x+4\\
y\gets y+2
$$

对答案没有任何影响，因此考虑将最复杂的负数坐标全部转化，

即给定的两个点的坐标，全部加上 $10^9+4$。

这里这么做保证了所有坐标为正数，因此可以直接差分，

考虑二维差分，我们计算 $(0,0)(x,y)$ 的答案，

那么对于 $(a,b)(c,d)$ 的答案，我们用 $A$ 表示，

$$
A(a,b,c,d)=A(c,d)-A(a,d)-A(c,b)+A(a,b)
$$

然后考虑这个后面的函数如何实现，

重复一遍需求：计算 $(0,0)(x,y)$ 的答案。

容易发现，一个 $4\times2$ 的矩阵是重复的。

而且对于这个重复的部分，其上下两个 $4\times1$ 的矩阵是等价的。

而对于不属于这个部分的地方，才会有上下两个 $4\times1$ 的矩阵是不同的。

对于下面的情况，容易发现其上下两个 $x\times2(0<x<4)$ 又是等价的。

据此，可以直接 $\mathcal O(1)$ 的计算。

因为我们多计算了很多的区域，答案可能很大，注意开 `longlong`。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

using ll = long long;

ll solev(ll a, ll b) {
    ll xgroup = a / 4;
    ll xleft = a % 4;
    ll ygroup = b / 2;
    ll yleft = b % 2;
    ll ans = xgroup * b * 4;
    if (xleft >= 1) {
        ans += ygroup * 3;
        ans += yleft * 2;
    }
    if (xleft >= 2) {
        ans += ygroup * 3;
        ans += yleft;
    }
    if (xleft >= 3) {
        ans += ygroup;
    }
    if (xleft >= 4) {
        ans += ygroup;
        ans += yleft;
    }
    return ans;
}

constexpr int add = 1e9 + 4;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    ll a, b, c, d; cin >> a >> b >> c >> d;
    a += add, b += add, c += add, d += add;
    cout << solev(c, d) - solev(a, d) - solev(c, b) + solev(a, b) << endl;
    return 0;
}
```

---

## 作者：Merge_all (赞：0)

## 思路：
### 通过观察图像可以发现：
- 从左到右有规律性。
- 每一行连续的 4 个格子阴影部分相加得 4，因此可以先处理这一部分，再处理模 4 后的剩余部分即可。

## 代码：
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll solve1(ll x1,ll y1,ll x2,ll y2){
	ll ans=0;
	ll y3=y1,y4=y2;
	while(y3%2)y3++;
	while(y4%2)y4--;
	for(ll i=x1;i<x2;i++){
		if((i%4+4)%4==0){
			ans+=(y4-y3)/2*3;
			if(y3!=y1)ans++;
			if(y4!=y2)ans+=2;
		}
		else if((i%4+4)%4==1){
			ans+=(y4-y3)/2*3;
			if(y3!=y1)ans+=2;
			if(y4!=y2)ans++;
		}
		else if((i%4+4)%4==2){
			ans+=(y4-y3)/2;
			if(y3!=y1)ans++;
		}
		else{
			ans+=(y4-y3)/2;
			if(y4!=y2)ans++;
		}
	}
	return ans;
}
ll solve(ll x1,ll y1,ll x2,ll y2){
	ll ans=0;
	ll x3=x1,x4=x2;
	while(x3%4)x3++;
	while(x4%4)x4--;
	if(x3>x4){
		return solve1(x1,y1,x2,y2);
	}
	return 1LL*(x4-x3)*(y2-y1)+solve1(x1,y1,x3,y2)+solve1(x4,y1,x2,y2);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int x,y,xx,yy;
	cin>>x>>y>>xx>>yy;
	cout<<solve(x,y,xx,yy);
	return 0;
}
```

---

## 作者：Mortidesperatslav (赞：0)

分讨题。

我们会发现，每行的图形都一样，但每列的图形不一样。所以要按照列来进行分类讨论。

我们考虑到每四个一循环，所以我们把 $A$ 右移，处理移动的这一段，再把 $C$ 左移，处理移动的这一段，当 $A$ 和 $C$ 相等或者 $A$ 和 $C$ 都是 $4$ 的倍数时停止移动。

移完之后很简单，中间一块就是 $\dfrac{(D-B)(C-A) \times 2}{4} \times 2=(D-B)(C-A)$。

那么如何处理移动的这一段呢？判断一下移动时的余数然后判断 $B$ 和 $D$ 的奇偶性就行了。

我的代码非常长，如果你能读懂，就不需要注释了，如果你读不懂，注释也没有用了。而且都是运算符的运算，注释恐怕作用确实也不大。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a, b, c, d;
unsigned long long ans;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> a >> b >> c >> d;
	int m1 = (a % 4 + 4) % 4, m2 = (c % 4 + 4) % 4;
//	cout << m1 << " " << m2 << "\n"; 
	for (; m1 != 0 && m1 != 4 && a < c; m1++, a++){
		if (m1 == 0){
			if ((d - b) % 2 == 0)
				ans += (d - b) / 2 * 3;
			else{
				ans += (d - b) / 2 * 3;
				if ((d % 2 + 2) % 2 == 1)
					ans += 2;
				else
					ans++;
			}
		}else if (m1 == 1){
			if ((d - b) % 2 == 0)
				ans += (d - b) / 2 * 3;
			else{
				ans += (d - b) / 2 * 3;
				if ((d % 2 + 2) % 2 == 1)
					ans++;
				else
					ans += 2;
			}
		}else if (m1 == 2){
			if ((d - b) % 2 == 0)
				ans += (d - b) / 2;
			else{
				ans += (d - b) / 2;
				if ((d % 2 + 2) % 2 == 0)
					ans++;
			}
		}else if (m1 == 3){
			if ((d - b) % 2 == 0)
				ans += (d - b) / 2;
			else{
				ans += (d - b) / 2;
				if ((d % 2 + 2) % 2 == 1)
					ans++;
			}
		}
	}
//	cout << ans << "\n";
	m1 = m2;
	for (; m1 != 0 && m1 != 4 && c > a; m1--, c--){
	//	cout << m1 << " " << (c / abs(c) - (c / abs(c) == 1)) << "\n";
		if (m1 == 1){
			if ((d - b) % 2 == 0)
				ans += (d - b) / 2 * 3;
			else{
				ans += (d - b) / 2 * 3;
				if ((d % 2 + 2) % 2 == 1)
					ans += 2;
				else
					ans++;
			}
		}else if (m1 == 2){
			if ((d - b) % 2 == 0)
				ans += (d - b) / 2 * 3;
			else{
				ans += (d - b) / 2 * 3;
				if ((d % 2 + 2) % 2 == 1)
					ans++;
				else
					ans += 2;
			}
		}else if (m1 == 3){
			if ((d - b) % 2 == 0)
				ans += (d - b) / 2;
			else{
				ans += (d - b) / 2;
				if ((d % 2 + 2) % 2 == 0)
					ans++;
			}
		}else if (m1 == 4){
			if ((d - b) % 2 == 0)
				ans += (d - b) / 2;
			else{
				ans += (d - b) / 2;
				if ((d % 2 + 2) % 2 == 1)
					ans++;
			}
		}
	}
//	cout << a << " " << c << "\n";
	ans += (d - b) * (c - a);
	cout << ans;
}
```

---

## 作者：kkxacj (赞：0)

#### 思路

一眼分讨题。

首先观察下题目给出的图：
![](https://cdn.luogu.com.cn/upload/image_hosting/c0na9yo4.png)

只看正半轴，发现奇数行图像是一样的，偶数行图像是一样的，每一行每四个格子一个循环，发现这些规律后分讨就可以了。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
int x,y,x2,y2,l,l1,ans,sum,sum1,bj[20],bj1[20];
signed main()
{
	read(x),read(y),read(x2),read(y2);
	x += 1e9,y += 1e9,x2 += 1e9,y2 += 1e9;
	bj[1] = 2,bj[2] = 3,bj[3] = 3; bj[4] = 4;
	bj1[1] = 1,bj1[2] = 3,bj1[3] = 4,bj1[4] = 4;
	l = x % 4;
	l1 = y % 2;
	if(l && x + (4-l) <= x2)
	{
		sum += (bj[4] - bj[l]);
		sum1 += (bj1[4] - bj1[l]);
		x += (4-l);
	}
	sum += (x2 - x) / 4 * 4 + bj[(x2 - x) % 4];
	sum1 += (x2 - x) / 4 * 4 + bj1[(x2 - x) % 4];
	if(l1 == 0)//先sum在sum1 
	{
		ans = (sum + sum1) * ((y2 - y)/2) + sum * ((y2 - y) % 2);
	}
	else
	{
		ans = (sum + sum1) * ((y2 - y)/2) + sum1 * ((y2 - y) % 2);
	}
	printf("%lld",ans);
	return 0;
}
```

---

