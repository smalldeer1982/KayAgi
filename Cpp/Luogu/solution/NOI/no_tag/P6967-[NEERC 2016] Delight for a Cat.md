# [NEERC 2016] Delight for a Cat

## 题目描述

一只猫正在进行一次冒险。

每小时，猫可以选择睡觉或吃东西。猫不能在同一小时内同时进行这两种活动，并且猫在整小时内只能进行其中一种活动。

对于接下来的 $n$ 小时，已知猫在每小时内睡觉或吃东西所获得的快乐值。这些值在每小时内可能不同。

还知道一个整数时间段 $k$。在每 $k$ 个连续的小时中，至少有 $m_{s}$ 小时猫在睡觉，至少有 $m_{e}$ 小时猫在吃东西。因此，有正好 $n - k + 1$ 个 $k$ 小时的时间段需要满足这个条件。

求猫在接下来的 $n$ 小时内所能获得的最大总快乐值。

## 说明/提示

时间限制：2 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
10 4 1 2
1 2 3 4 5 6 7 8 9 10
10 9 8 7 6 5 4 3 2 1
```

### 输出

```
69
EEESESEESS
```

# 题解

## 作者：ix35 (赞：42)

这里转载一下我[博客](https://www.luogu.com.cn/blog/ix-35/noi-yi-lun-fu-xi-i-er-fen-tu-wang-lao-liu)中的一个片段，因为我发现本题的题解基本都是从线性规划的角度进行考虑的，这种方法**技巧性极强**，且需要一定的**数学观察**，不适合像我这种无脑选手，所以这里引出一种适用于这类题目的易于理解的费用流模型。

---

> 区间选择模型：
>
> 给定 $[1,m]$ 中的 $n$ 个区间 $[l_i,r_i]$，每个区间选择一次的代价为 $w_i$，最多可以选 $c_i$ 次，要求使得任意点 $j$ 被覆盖次数在 $[a_j,b_j]$ 间，求最小/最大代价。

将 $1$ 到 $m+1$ 连成一条链，尝试用 $i\to i+1$ 边的流量刻画 $i$ 被覆盖的次数。

对于一个区间，我们建立从 $l_i$ 到 $r_i+1$ 的一条边，称为区间边，如果区间边上流过一条流，就表示选择一次这个区间。

源流向 $1$，$m+1$ 流向汇，首先设确定总流量为 $X$，那么没有流经 $i\to i+1$ 这条边的流量就是选择了跨过 $i$ 的区间，所以 $i\to i+1$ 的流量为 $X-f_i$ 就表示 $i$ 被覆盖了 $f_i$ 次。

由此，如果我们要限定一个点被覆盖次数在一个区间中，只需要设定 $i\to i+1$ 的流量上下界为 $[X-b_i,X-a_i]$，然后将区间边费用设为区间代价，容量设为可选次数，最小/最大费用上下界最大流即为答案。

这里 $X$ 可以选取任意一个充分大的数（不小于最大的 $b_i$）。

---

>  例题 $31$：[网络流 24 题] 最长 $k$ 可重区间集问题
>
>  从给定的 $m$ 个开区间中选择尽量多的区间，使得每个位置被不超过 $k$ 个区间覆盖，且区间长度和最大。

模型中的 $w_i=1,\ c_i=1,\ a_j=0,\ b_j=k$，套用即可。

注意由于所有 $b_j$ 相等，所以令 $X=b_j$，就没有下界了，可以普通费用流。

---

> 例题 $32$：[NEERC 2016] Delight for a Cat
>
> 在 $n$ 小时中的每个小时，猫可以选择吃饭或睡觉，每个小时吃饭或睡觉都有一个愉悦度，但要求任意连续 $k$ 小时中至少有 $m_e$ 小时吃饭，至少 $m_s$ 小时睡觉，问最大总愉悦度。

首先做个小转化：强制每个小时都睡觉，然后可以选择一些小时改成吃饭，连续 $k$ 个小时中吃饭的数量要在 $[m_e,k-m_s]$ 之中。

再做个转换，将”第 $i$ 小时改吃饭“看成一个区间 $[i,i+k)$，那么上面的条件就等价于对于所有 $i\ge k$ 的点有 $i$ 被这些区间覆盖的次数在 $[m_e,k-m_s]$ 之中。

模型中的 $c_i=1,\ a_j=m_e,\ b_j=k-m_s$（对于 $i\ge k$ 的 $i\to i+1$ 边），套用即可。

所有 $b_j$ 相等，所以令 $X=b_j$，就没有下界了。

---

> 例题 $33$：[NOI 2008] 志愿者招募
>
> 有 $m$ 个可选操作，每个操作为将 $s_i$ 到 $t_i$ 中每个位置加 $1$，代价为 $c_i$，每个操作可以做无限次，要求最后位置 $i$ 上的数不小于 $a_i$，问最小代价。

模型中的 $w_i$ 是题中的 $c_i$，模型中的 $c_i=+\infty,\ b_j=+\infty$，套用即可。

所有 $b_j$ 相等，所以令 $X=b_j$，就没有下界了。

---

## 作者：GK0328 (赞：7)

### 单纯形法

太弱了，不会网络流，只好用**单纯形法**辗过去。

很容易发现，这是一个线性规划问题，我们可以设$n$个变量$x_1,x_2,\cdots,x_n$表示每个时刻猫的状态，$x_i=0$表示猫在$i$时刻进食，$x_i=1$表示猫在$i$时刻睡觉。

我们可以列出以下这些方程：

$$
\begin{cases}
0 \le x_1 \le 1 \\
0 \le x_2 \le 1 \\
\cdots\\
0 \le x_n \le 1 \\
\sum_{i=1}^k x_i \ge ms \\
k-\sum_{i=1}^k x_i \ge me\\
\cdots\\
\sum_{i=n-k+1}^n x_i \ge ms \\
k-\sum_{i=n-k+1}^n x_i \ge me\\
\end{cases}
$$

求：

$$
\max \sum_{i=1}^n s_i x_i + e_i (1-x_i)
$$

根据线性规划整数最优解的判定条件，可以证明整数解一定是本题中线性规划的最优解（~~伪证：因为本题可以费用流，所以单纯形法能够跑出整数解~~）。

把方程经过添加负号等变换，转化为标准形式，然后直接跑单纯形法。

提交一下，发现$TLE$了。

实际上，我们这里的单纯形法需要初始化，因为一开始的全$0$解是不合法的，这会消耗大量时间，引用一句话：

> 需要注意的一点是，大部分的OI试题得出的限制条件都有一定的性质，而执行初始化操作会破坏这些性质，造成运行时间的无谓增加。	——董克凡《浅谈线性规划与对偶问题》

因此我们可以考虑手动初始化，也就是找到一组合法解，实际上这很容易构造，我们让$me$个$E$,$k-me$个$S$不断循环得到一个长度为$n$的序列，容易发现，任意一个长度为$k$的子区间都含有$me$个$E$，$k-me$个$S$，显然合法。

我们把这个序列作为标准序列，把$x_i$重新定义，即$x_i=0$表示$i$时刻状态与标准序列中$i$时刻状态不同，$x_i=1$表示$i$时刻状态与标准序列中$i$时刻状态相同。

然后再跑单纯形法就可以通过本题了。

$Code:$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#define db double
using namespace std;
const db eps=1e-7;
int n,m,k,ms,me,s[1005],e[1005],id[4005];
db z,ans[4005],a[3005][1005];
bool r[1005];
void pivot(int l,int e)
{
    swap(id[n+l],id[e]);
    db t(a[l][e]);
    a[l][e]=1.0;
    for (int i=0;i<=n;++i)
        a[l][i]/=t;
    for (int i=0;i<=m;++i)
        if (i!=l && fabs(a[i][e])>eps)
        {
            db t(a[i][e]);
            a[i][e]=0.0;
            for (int j=0;j<=n;++j)
                a[i][j]-=t*a[l][j];
        }
}
void simplex()
{
    for (;;)
    {
        int e(0),l(0);
        db mx(eps);
        for (int i=1;i<=n;++i)
            if (a[0][i]>mx)
                mx=a[0][i],e=i;
        if (!e)
            return;
        db mn(1e18);
        for (int i=1;i<=m;++i)
            if (a[i][e]>eps && a[i][0]/a[i][e]<mn)
                mn=a[i][0]/a[i][e],l=i;
        pivot(l,e);
    }
}
int main()
{
    scanf("%d%d%d%d",&n,&k,&ms,&me);
    for (int i=1;i<=n;++i)
        scanf("%d",&s[i]);
    for (int i=1;i<=n;++i)
        scanf("%d",&e[i]);
    for (int i=1;i<=n;++i)
    {
        r[i]=((i-1)%k+1>me);
        if (r[i])
            z+=s[i],a[0][i]=e[i]-s[i]; else
            z+=e[i],a[0][i]=s[i]-e[i];
        a[i][0]=1.0,a[i][i]=1.0;
    }
    m=n;
    for (int i=1;i<=n-k+1;++i)
    {
        ++m,a[m][0]=-ms;
        for (int j=i;j<i+k;++j)
            a[m][j]=-1.0;
        ++m,a[m][0]=k-me;
        for (int j=i;j<i+k;++j)
            a[m][j]=1.0;
    }
    for (int i=1;i<=n;++i)
        if (r[i])
            for (int j=n+1;j<=m;++j)
                a[j][0]-=a[j][i],a[j][i]=-a[j][i];
    for (int i=1;i<=n;++i)
        id[i]=i;
    simplex();
    for (int i=1;i<=m;++i)
        ans[id[n+i]]=a[i][0];
    printf("%.lf\n",z-a[0][0]);
    for (int i=1;i<=n;++i)
        putchar(((fabs(ans[i])>eps) ^ r[i])?'S':'E');
    putchar('\n');
    return 0;
}
```

---

## 作者：optimize_2 (赞：5)

这本来应该是一篇日报，但是日报审核咕了一年了，我先投成这题题解再说。

# 单纯形法简介

## -1. 前置知识

初中数学。

## 0. 问题引入

某天我做到了 [P6967 \[NEERC2016\] Delight for a Cat](https://www.luogu.com.cn/problem/P6967)，是一道可爱的建图费用流题。结果我看题解出现了一个名词单纯形法，我就去学了一下。但是因为网上好多文章是面向学数学的大学生而不是学算法竞赛的高中生的，我花了点精力看懂了之后打算写一点东西。

先介绍一下题意：

有一只猫猫要在接下来的 $n$ 个小时内，每个小时选择吃饭或者睡觉。第 $i$ 个小时吃饭可以获得 $e_i$ 的快乐值，睡觉可以获得 $s_i$ 的快乐值。对于每段连续的 $k$ 小时，必须至少有 $E$ 个小时在吃饭，$S$ 个小时在睡觉。给定 $n, s_i, e_i, S, E, k$，求可能获得的最大快乐值。$n, k \leq 1000$，时间限制 2s。

接下来讲一下思路：

设第 $i$ 小时的状态为 $x_i \in \{0, 1\}$，$0$ 代表吃饭了，$1$ 代表睡觉了。

从 $d$ 小时开始的连续 $k$ 小时的连续段就有 $sleep = \sum_{i = d}^{d + k - 1} x_i$ 小时在睡觉，有 $eat = k - sleep$ 小时在吃饭。

那么连续 $k$ 小时必须至少有 $E$ 小时吃饭，$S$ 小时睡觉的限制就可以写成 

$$\forall d \in [1, n - k + 1], \sum_{i = d}^{d + k - 1} x_i \in [S, k - E]$$

我们发现，限制有很多种，有 $\in {0, 1}$ 这种二值的，也有 $\in [S, k - E]$ 这种属于一个区间的，我们想个办法把限制用一种统一的格式写起来。

考虑一个简单的不等式

$$0 \leq x_1 \leq b_1$$
$$b_2 \leq x_2$$

其中 $x_1, x_2$ 是变量，$b_1, b_2$ 是常量。可以再添加两个未知数 $x_3, x_4$ 来把不等式转换成等式。

$$x_1 + x_3 = b_1$$

$$x_2 - x_4 = b_2$$

另外在单纯形法中，我们规定对于所有 $i$ 都有 $x_i \geq 0$。

另外，对于一个没有限制的 $x$，可以把它拆成 $x_5 - x_6$，其中 $x_5, x_6 \geq 0$。


同时，答案（我们要最大化或者最小化的目标）也应该被写成一个关于所有未知数的线性函数：

$$ans = \sum_{j = 1}^{n} c_jx_j$$

如果要最小化答案，可以把 $a_i$ 都取相反数然后最大化。

那么我们就得到了线性规划问题的一般形式：

有关于 $n$ 个 $\geq 0$ 的未知数的 $m$ 个线性方程组（线性就是一次的），要最大化一个关于这 $n$ 个未知数的线性函数 $z$。

用符号表达就是

$$
\max \ z = \sum_{j = 1}^{n}c_jx_j
$$


$$
s.t.
\begin{cases}  
\displaystyle a_{1,1}x_1 + a_{1,1}x_2+ ... + a_{1,n}x_n = b_1, \\ 
\displaystyle a_{2,1}x_1 + a_{2,2}x_2+ ... + a_{2,n}x_n = b_2, \\ 
...\\
\displaystyle a_{m,1}x_1 + a_{m,2}x_2+ ... + a_{m,n}x_n = b_m, \\ 
x_j \geq 0 , j \in \{1,2,\dots,n\}  \\
n \leq m
\end{cases}
$$

$s.t.$ 就是受限制于的意思，就是说你的 $x$ 得满足这些性质，而你需要最大化 $z$。

有人可能会问：这道题的前 $n$ 个 $x_i$（之所以说前 $n$ 个是因为我们后面添加了一些用来把不等式转成等式的未知数，只有前 $n$ 个表示了吃饭睡觉的状态）不是只能是 $0$ 或者 $1$ 吗，转换成线性规划怎么变成 $0 \leq x_i \leq 1$ 了？

因为这道题可以费用流（如果把每个点的流量式子列出来，会发现费用流解决的也是线性规划问题），所以最优解一定在整数点上。

感觉有点牵强，算了，本文章也没有打算证明，各位只要能看懂就行了，做题的时候能用就更好了，你大学数学要重新学一遍的，是你老师的事。

## 1. 一些解决问题的尝试

首先，你可以把 $x_i$ 叫做未知数，也可以叫做变量。

（可以想象一下我们在搓仪表盘，上面有很多滑块，每个都代表一个变量，有的东西大了就会带动别的东西变大变小。）

根据初中数学知识，通常情况下（不退化或者说方程组之间线性无关，如果你听不懂这些就当没看到这个括号里的内容），$n$ 个 $n$ 元一次方程有一组唯一解。

好我们解决了 $n = m$ 的情况，就是直接解出所有解然后算出答案，没法最小化最大化，因为就这一个解了，爱要不要。

遗憾的，如果 $n$ 大于 $m$ 怎么办？

我们可以在 $n$ 个变量中挑选出 $m$ 个变量作为幸运变量。这里假定是 $x_1, x_2, ..., x_m$ 这 $m$ 个。

唉，如果未知数是 $m$ 个就好了。

假设我们知道了剩下 $n - m$ 个没被选中的不幸运的变量的取值，未知数就真的变成 $m$ 个了。

所以如果我们知道了所有不幸运变量的取值，可以解出幸运变量的取值，也可以表示出答案。

现在我们把幸运变量叫做基变量，不幸运变量叫非基变量。

## 2. 重要结论

**非基变量都取 $0$ 是最优解的必要条件**。

这里给一个感性理解。非基变量都是 $0$ 代表卡到了某种边界。

举一个例子（懒得画图所以图和例子都来自 [OI-wiki](http://oi-wiki.com/math/simplex/)）

$$
\max \ z = x_1 + x_2
$$

$$
s.t \begin{cases}  
2x_1 + x_2 + x_3 = 12 \\ 
x_1 + 2x_2 + x_4 = 9  \\
x_1, x_2, x_3, x_4 \geq 0
\end{cases}
$$

选择 $x_1$，$x_2$ 作为基变量，那么只要确定了 $x3, x3$ 的值，$x_1$, $x_2$ 就能被确定，从而进一步确定答案。

先画出一个平面直角坐标系，横轴代表 $x_1$，纵轴代表 $x_2$

![](https://cdn.luogu.com.cn/upload/image_hosting/0dc1varb.png)

可以看到，所有合法的 $(x_1, x_2)$ 的集合是阴影部分。

我们来考察一下，非基变量等于 $0$ 究竟有什么意义。

令 $x_3, x_4 = 0$，限制变为
$$
\begin{cases}  
2x_1 + x_2 = 12 \\ 
x_1 + 2x_2 = 9  \\
x_1, x_2 \geq 0
\end{cases}
$$

第一条限制规定了 $(x_1, x_2)$ 必须在 $2x_1+x_2=12$ 的直线上（就是图里比较陡峭的那条），第二条限制规定了 $(x_1, x_2)$ 必须在 $x_1 + 2x_2 = 9$ 的直线上（就是图里另一条）

所以当 $x_3, x_4 = 0$ 时，$(x_1, x_2)$ 落在了两条直线的交点，也是解集的边缘。

现在我们大胆猜测一下，当非基变量都为 $0$ 时，我们得到的解一定在解集的边缘。

感性理解：每条限制规定了基变量解位于基变量空间中的某一半上（比如这个例子中，有两个基量时基变量空间是平面，限制规定基变量一定在直线的一侧也就是半个平面），而非基变量等于 $0$ 则限制了一定在规定的这部分空间的边缘上（这里是在直线上），所有限制取交集，那基变量的解就位于解集的边缘。

我再举个例子，如果有 $3$ 个基变量，那就有 $3$ 条限制，同时基变量空间是三维的，每条限制给出了基变量都位于一个平面上，而在通常情况下（限制之间线性无关），三条平面有且仅有一个交点，这个点就是非基变量为 $0$ 时基变量的解，也是解集的边缘。

那么为什么解集的边缘一定是最优解的充分条件呢？

还是考虑这个例子，我们要最大化 $z = x_1 + x_2$，或者你也可以写成 $z = x_1 + x_2 + 0x_3 + 0x_4$，取 $x_1, x_2$ 作为基变量，在图里画出来 $C = x_1 + x_2$ 这条直线。（$C$ 是某个可以变化的量。）

发现如果这条直线和解集有交，那么交集里的点对应的 $(x_1, x_2)$ 就能取到 $z = C$。

那么我们把直线往上移动一点（增大 $C$）直到直线与解集只有一个交点，由于解集是凸的，这个点就能取到最大的 $z$，同时这个点也是解集的边缘点。所以令非基变量等于 $0$ 是 $z$ 最大的充分条件。

- 什么是“凸的”？

  你可以理解为解集这个图画出来是凸的，没有凹下去的地方。
  
  或者说，如果 $(x_1, x_2, ..., x_m)$ 是一组解，$(y_1, y_2, ..., y_m)$ 也是一组解，那么 $(\frac{x_1 + y_1}{2}, \frac{x_2 + y_2}{2}, ..., \frac{x_m + y_m}{2})$ 也应该是一组解。

- 为什么解集是凸的？

  感性理解：还是上面的思路，对于一个平面来说每条限制给出了一条直线并且规定解集一定在直线的同一侧，所以解集的每条边都是某个限制对应的直线的一部分。如果解集中真的出现了凹陷，那么对于连接凹陷点的两条边，解集同时出现在了他们所对应的直线的两侧，这不符合事实。

每次选择一些非基变量置 $0$，几何意义就是在解集边缘上移动来寻找最优解。

这里放一张来自知乎的图以便于理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/45ofxlxx.png)

## 3. 重要结论引发的思路

非基变量取 $0$ 是 $z$ 取最大值的必要条件。

遗憾的，你不能随便取 $m$ 个作为基变量，然后让剩下作为非基变量，并且让他们都变成 $0$ 就说我取到最大值了。

所以为了找到最优的基变量选取方案，我们要从一组初始基变量开始调整。

在此之前，我们可以先使用和高斯消元一样的方法，让每个方程都只包含一个非基变量，并且系数为 $1$。
  
  举例：（基变量是 $x_1, x_2$）
  
  $$
\begin{cases}  
2x_1 + x_2 + x_3 + 0x_4 = 12 \\ 
x_1 + 2x_2 + 0x_3 + x_4 = 9  \\
x_1, x_2, x_3, x_4 \geq 0
\end{cases}
  $$
  
我们可以对于每个限制都选一个基变量，并且在别的限制中消去这个变量，即通过方程组的加减让这个变量系数为 $0$。这里第一条限制选择 $x_1$，第二条限制选择 $x_2$。
  
  $$
\begin{cases}  
2x_1 + 0x_2 + \frac{4}{3}x_3 + 0x_4 = 10 \\ 
0x_1 + \frac{3}{2}x_2 - \frac{1}{2}x_3 + x_4 = 3  \\
\end{cases}
  $$
  
  然后把基变量的系数都变成 $1$。
  
  $$
\begin{cases}  
1x_1 + 0x_2 + \frac{2}{3}x_3 + 0x_4 = 5 \\ 
0x_1 +1 x_2 - \frac{1}{3}x_3 + \frac{2}{3} x_4 = 2  \\
\end{cases}
  $$


## 4. 单纯形法

单纯形法的核心流程就是从一组初始选定的基变量开始，不断修改选取的基变量来达到最大值。

那么每次调整基变量，我们就要选择一个非基变量替换掉一个基变量，同时再进行一下方程组的加减来让每个基变量都在一条限制中系数为 $1$，其余限制中系数为 $0$。

接下来考虑调整基变量，那就要回答三个问题：

1. 如何判断当前是不是最优解？

  前面提到，当确定了非基变量（这里假设是 $x_1, x_2, ..., x_m$ 是基变量，$x_{m + 1}, x_{m + 2}, ..., x_n$ 是非基变量），那就能确定基变量从而进一步确定 $z$。由于这都是线性方程组，所以基变量和非基变量的关系是线性的，那么 $z$ 和非基变量的关系也是线性的，也就是说 $z$ 一定形如：
  
  $$z = C + \sum_{i = 1}^{m} \sigma_ix_{n + i} $$

  由于最优解的非基变量都是 $0$，所以如果当前情况是最优解，那么非基变量不取 $0$（比 $0$ 大）一定会使得 $z$ 变小。也就是说存在一个非基变量的系数 $\sigma_i > 0$。
  
  那么我们对于一组基变量的选取方案，算出每个非基变量的 $\sigma$，如果都 $\leq 0$ 就说明是最优解了，不然还得改动。

2. 如果不是最优解，如何找到新的基变量？（这又被称为进基变量）

  取最大的那个 $\sigma$。

3. 找到了一个新的基变量，得替换掉现有方案中的一个，替换哪个？（这又被称为出基变量）
  
  由于我们选择了进基变量，而且这个变量的 $\sigma$（对答案的贡献系数）是正的，这意味着这个变量越大越好。
  
  而非基变量都是 $0$，所以限制这个新的变量变大的只会是基变量。我们要选择一个对新变量限制最大的基变量踢掉，让它成为出基变量。
  
  为了做到这一点，就得算出基变量对非基变量的限制。
  
  这时候就体现出我们之前让每条限制只含有一个基变量的作用了。
  
  首先我们找到所有包含进基变量的限制（系数不等于 $0$，系数等于 $0$ 的限制和进基变量无关即对进基变量无约束，不用考虑了）。
  
  假设我们选中的进基变量是 $x_{m + i}$，目前选择的基变量是 $x_1, x_2, ..., x_m$，那么包含基变量 $x_j$ 的一条限制形如
  
  $$0x_1 + 0x_2 + ... + 1x_j + ... + 0x_m + k_1x_{m + 1} + k_2x_{m + 2} + ... + k_ix_{m+i}+...+k{n - m}x_n = b$$

  由于非基变量都是 $0$（除了我们选定的进基变量 $x_{m + i}$），实际上这个方程只有两个变量
  
  $$x_j + k_ix_{m+i} = b$$
  
  由于 $x_j$ 即将变成非基变量，他的取值也会变成 $0$，所以这个方程能让 $x_{m+i}$ 最大取到 $\frac{b}{k_i}$。
  
  有个问题：如果有 $\frac{b}{k_i} < 0$ 怎么办？由于你的 $x_{m+i} \geq 0$，这意味着如果你要把 $x_j$ 从基变量里踢出（让它等于 $0$）的话，就无解了，所以 $\frac{b}{k_i} < 0$ 的限制也不用考虑。那我们选择所有限制的常数项除以进基变量系数大于 $0$ 的限制里最小的那条限制的基变量踢掉就好了。

现在我们确定了进出基变量，再把方程组加加减减让进基变量在出基变量那条限制中系数为 $1$，在其他限制中系数为 $0$ 就解决了。

## 5. 单纯形表

单纯形表实际上是把单纯形法的流程一般化。

其实到这里，如果你看懂了前面的内容，就已经理解了单纯形法的原理，可以直接写个代码冲例题了。

所以你不如去看 [OI-wiki](http://oi-wiki.com/math/simplex/)。

## 参考资料

1. http://oi-wiki.com/math/simplex/
2. https://zhuanlan.zhihu.com/p/623374447
3. https://zhuanlan.zhihu.com/p/622997038
4. https://www.bilibili.com/video/BV1824y137JU （这个对于单纯形表流程的讲解很详细，可以看看）

---

## 作者：Morpheuse (赞：4)

看到大佬们都用线性规划费用流，我太弱了只好用暴力一点的方法来建模.

# Solution

我们先假设所有时间都在睡觉，那么我们的快乐值为 $\sum\limits^n_{i = 1}\ S_i$.

但是我们有一些时间要吃饭.

对于每 $k$ 个小时，吃饭的时间区间为 $[me , k - ms]$.

设总流量为 $Flw$.

对于所有的 $i$ 连边 $i\to i + 1$ ，每个单位流量意义为被睡觉覆盖一次.

流量为 $[Flw - k + ms , Flw - me]$ ，表示这一天最少被睡觉覆盖 $Flw - k + ms$ 次，最多被覆盖 $Flw - me$ 次.

边权为 $0$ ，因为我们先前已经计算了睡觉的贡献.

对于所有的 $i$ 连边 $i\to i + k$ ，每个单位流量意义为被吃饭覆盖一次.

流量为 $1$ 表示这个小时只能吃一次饭.

边权为 $E_i - S_i$ ，表示这个小时不选择睡觉而选择吃饭.

令 $Flw$ 为 $k - ms$ ，即可使下界为 $0$.

然后跑最大费用最大流即可.

---

我们来考虑为什么这样是对的.

因为总流量 $Flw$ 是不变的，

但是对于 $i\to i + 1$ 的边流量只有 $Flw - me$，所以就必定有 $me$ 的流量从别的地方去到 $i + 1$ 或者更远的地方.

这个流量的来源就是 $i\to i + k$ 的边.

---

代码有一些细节方面的内容需要自己考虑.

实在想不明白再参考我的代码吧（主要是太丑了）.

```cpp
	scanf("%lld%lld%lld%lld", &n,&k,&ms,&me);
	//所有时间都在睡觉.
	//吃饭的时间区间为 [me , k - ms].
	//流经上面的边 也就是吃饭的区间为 [me , k - ms].
	//总流量为 Flw.
	//流经下面的边的区间就是 [Flw - k + ms , Flw - me].
	Flw = k - ms;
	s = 0 , t = n + 1;
	add(s , 1 , Flw , 0);
	int ans = 0;
	for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &S[i]) , ans += S[i];
	for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &E[i]);
	for(int i = 1 ; i < k ; ++ i) add(i , i + 1 , Flw , 0);
	for(int i = k ; i <= n ; ++ i) add(i , i + 1 , Flw - me , 0);
	for(int i = 1 ; i <= n ; ++ i) add(i , min(i + k , t) , 1 , S[i] - E[i]);
	dinic();
	printf("%lld\n", ans - cot);
	for(int x = 1 ; x <= n ; ++ x)
	{
		int flag = 0;
		for(int i = hea[x] ; i ; i = e[i].nex)
		{
			if(e[i].dat == S[x] - E[x])
			{ 
				flag = e[i].flw;
				break;
			}
		}
		if(flag)
			printf("S");
		else
			printf("E");
	}
```

---

## 作者：JoshAlMan (赞：3)

## Description

你要构造一个长度为 $n$ 的 $01$ 序列，每个位置选 $0/1$ 的权值给定。

要求在任意 $k$ 连续段的 $0$ 的数量大于 $m_s$，$1$ 的数量大于 $m_e$，在这种状态下最大的总权值。

还要输出一种方案。

## Solution

这题和 [NOI2008 志愿者招募](https://www.cnblogs.com/dmoransky/p/13592442.html) 挺像的。

看起来很像 DP，但 DP 要记录每个点选的啥才能保证满足限制，因此不能用 DP。

发现要满足的限制是一个带变量的不等式，我们需要在限制内，选择一种变量的方案，使答案最大化。

可以考虑设置一些变量，变不等式为等式，利用网络流的流量守恒，使每个点等于一个等式，我们只需要将等式变换让每个变量最多出现在一个等式的左侧和另一个等式的右侧（或者只出现一次）：

* 若出现两次，让右侧的等式点指向左侧的等式点连一条边。
* 若出现一次，若右侧则让这个等式点指向网络流虚拟汇点连一条边。

对于等式中的常量，左右侧连和源汇点连边，考虑到费用流首先保证最大流，因此一定会让它充满。

这条边的流量就映射着这个变量的选择，因此变量的形式应该是 $0 \le x \le a$。（$x$ 为变量，$a$ 为常量），这样可以保证每个变量在所有等式中是同一个值。

因为睡觉和吃是补集关系，我们不妨只考虑在那些位置吃饭。设最初我们都选择睡觉，然后考虑每个点的权值为 $e_i - s_i$，即从睡觉到吃变换的权值。

设 $x_i \in \{ 1, 0\}$ 为第 $i$ 天是否选择吃饭，那么需要满足对于任意 $K \le i \le n$， $m_e \le \displaystyle \sum_{j=i-k+1}^i x_j \le k - m_s$。

化不等式为等式，设 $t_i$ 为这个等式的一个阙值，满足 $0 \le t_i \le k - m_s - m_e$，这样上面那个式子就等价变成了：

$$\displaystyle \sum_{j=i-k+1}^i x_j + t_i = k - m_s$$

但是呢现在每个变量出现在了多个等式中，考虑把等式进行等价变换，保留 $i = k$ 的等式，$i > k$ 的等式做一个差分，等价变成 $i$ 减去 $i - 1$ 的等式，如此，我们得到了 $n - k + 1$ 个等式：

* $i = k$：$\displaystyle \sum_{j=i-k+1}^i x_j + t_i = k - m_s$
* $i > k$：$t_i + x_i = t_{i-1} + x_{i-k}$

然后我们发现变量就最多出现在两个式子中了，因此跑最大费用最大流就好了。

还要输出方案，根据实际意义在网络流里看对应边有没有流满就好了。

网络点边数都是 $n$ 级别的。由于网络流不容易卡满，因此可以跑过。

---

## 作者：drowsylve (赞：2)

### 本题解尝试对费用流做法再进行一些更加完备的解释说明。

这题在 sd 二轮省集出过，不过当时没题号，而且不等关系建模真的没听懂，错过了一个好题。做了志愿者招募以后发现这题很牛，时隔三个月回来带走猫猫。

### 题解

非常建议先熟练志愿者招募的建模思路。但显然这题并没有志愿者招募中比较裸的区间限制，所以先进行一些转化。

类似其他题解的，先把钦定所有时刻都睡觉，然后考虑把部分时刻改为吃饭。

先套路的把区间用 $i \to i+k$ 这条边描述出来，称为区间边。然后你发现直接考虑把 $[i,i+k)$ 这个区间的吃饭睡觉次数限制，对应放到某条边上，事实上~~我认为~~是不好确定该对应在哪里的。

所以我们先从 $i \to i+1$ 这条边考虑。首先 $S \to 1$ 和 $n \to T$ 这两条边要流满，先设为 $R$。类似志愿者招募的理解，我们要在 $i \to i+1$ 的边上卡一个流量的上限，使得有一部分流量会被强行分流到 $i \to i+k$ 上。显然这个限制是由吃饭睡觉的次数决定的，不难发现吃饭次数要求在 $[m_e,k-m_s]$ 之间。

接下来考虑如果在 $i \to i+1$ 卡上了限制以后最大流会如何决策。区间边长度显然都为 $k$，相当于一定会有一些流从 $(i-k,i]$ 中的某处流进了区间边，然后直接跨过了 $i \to i+1$ 这条边。如果认为流量流经区间边 $i \to i+k$ 是在起点时刻 $i$ 处吃饭，那显然区间边的流量限制是 $1$，也就恰好满足了每一个长为 $k$ 的区间的需求。

至此不难发现，区间 $[i,i+k)$ 的需求是由边 $i+k-1 \to i+k$ 这条边的流量限制来保证的。

这样建图思路就很自然了，对于 $i < k$ 的边 $i \to i+1$ 显然不会有区间需要它来做限制，因此流量 $R$，费用 $0$。其他的 $i \to i+1$ 边需要来保证每个长度为 $k$ 的区间的睡觉吃饭限制，因此流量 $[R-(k-m_s),R-m_e]$，费用为睡觉改吃饭的负贡献。

令 $R=k-m_s$，就没有流量下界了，可以直接胡上费用流。最小化改变带来的负贡献，等价于最大化答案。

代码基本就是板子没有啥特别重要的点，具体细节可以参考其他题解。

###### 猫猫也想有成为网络流带师的一天。

---

## 作者：Nuisdete (赞：0)

考虑先每小时都吃饭，再改睡觉。

发现一个点可以贡献 $k$ 个限制，因此直接把所有的限制先拆个点限制一下再串成一串。

然后直接用每个点连向前面最远的限制，费用为睡觉和吃饭的差值，形成一个闭环就完事了。

跑无源汇上下界最大费用可行流。

但是我们发现这玩意好像出正环了，于是再套上一个上下界就行了。

```cpp
# include <cstdio>
# include <cstring>
# include <utility>
# include <algorithm>

# define int long long

constexpr int MAXN = 2e3 + 5, MAXM = 1e6 + 5, INF = 0x3f3f3f3f3f3f3f3f;

int n, k, A, B;

int s = 0, t = MAXN;

int head[MAXN << 1], cur[MAXN << 1], numE = 1;

struct Edge {
	int nxt, to, cap, val;
	
	Edge() {}
	Edge(int N, int T, int C, int V) {
		nxt = N, to = T, cap = C, val = V;
	}
} edge[MAXM << 1];

void addE2(int x, int y, int C, int V) {
	edge[++numE] = Edge(head[x], y, C, V), head[x] = numE;
	edge[++numE] = Edge(head[y], x, 0, -V), head[y] = numE;
}

int que[MAXN << 1], *tl, *hd;

int dis[MAXN << 1];

bool vis[MAXN << 1];

bool spfa() {
	hd = tl = que;
	memcpy(cur, head, sizeof cur);
	memset(vis, false, sizeof vis);
	for (int i = 0; i < MAXN << 1; ++i) dis[i] = -INF;
	*tl ++ = s, dis[s] = 0, vis[s] = true;
	while (hd != tl) {
		int u = *hd ++; if (hd - que > MAXN) hd = que;
		vis[u] = false;
		for (int i = head[u]; i; i = edge[i].nxt) {
			int k = edge[i].to;
			if (dis[k] < dis[u] + edge[i].val && edge[i].cap) {
				dis[k] = dis[u] + edge[i].val;
				if (!vis[k]) {
					*tl ++ = k; if (tl - que > MAXN) tl = que;
					vis[k] = true;
				}
			}
		}
	}
	return dis[t] != -INF;
}

int cost;

int dfs(int u, int flw) {
	if (u == t) return flw;
	int tot = 0; vis[u] = true;
	for (int& i = cur[u]; i; i = edge[i].nxt) {
		int k = edge[i].to;
		if (dis[k] == dis[u] + edge[i].val && edge[i].cap && !vis[k]) {
			int add = dfs(k, std::min(flw, edge[i].cap));
			if (!add) dis[k] = -INF;
			edge[i].cap -= add, edge[i ^ 1].cap += add;
			flw -= add, tot += add, cost += add * edge[i].val;
			if (!flw) break;
		}
	}
	return vis[u] = false, tot;
}

void dinic() {
	while (spfa()) {
		memset(vis, false, sizeof vis);
		while (dfs(s, INF));
	}	
}

int a[MAXN << 1], b[MAXN << 1];

int deg[MAXN << 1], Deg[MAXN << 1];

signed main() {
	
	std::vector<std::pair<int, int> > ans;
	scanf("%lld %lld %lld %lld", &n, &k, &A, &B);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]), cost += a[i];
	for (int i = 1; i <= n; ++i) scanf("%lld", &b[i]);
	for (int i = 1; i <= n; ++i) {
		if (i < n) addE2(i + n, i + 1, INF, 0);
		if (i + k - 1 <= n) {
			deg[i + n] += B, deg[i] -= B;
			addE2(i, i + n, k - A - B, 0);
		}
		else addE2(i, i + n, INF, 0);
		if (b[i] > a[i]) {
			cost += b[i] - a[i];
			addE2(std::max(1LL, i - k + 1), i + n, 1, a[i] - b[i]), ans.emplace_back(numE, 0);
			++Deg[std::max(1LL, i - k + 1)], --Deg[i + n];
		}
		else addE2(i + n, std::max(1LL, i - k + 1), 1, b[i] - a[i]), ans.emplace_back(numE, 1);
	}
	for (int i = 1; i <= 2 * n; ++i) {
		if (deg[i] > 0) addE2(s, i, deg[i], 0);
		if (deg[i] < 0) addE2(i, t, -deg[i], 0);
	}
	std::vector<int> vec;
	addE2(t, s, INF, 0); vec.push_back(numE);
	s = MAXN + 1, t = MAXN + 2;
	for (int i = 0; i <= 2 * n + 1; ++i) {
		if (i == 2 * n + 1) i = MAXN;
		if (Deg[i] > 0) addE2(s, i, Deg[i], 0), vec.push_back(numE);
		if (Deg[i] < 0) addE2(i, t, -Deg[i], 0), vec.push_back(numE);
	}
	dinic();
	s = 0, t = MAXN;
	for (int k : vec) edge[k].cap = edge[k ^ 1].cap = 0;
	dinic();
	printf("%lld\n", cost);
	for (auto k : ans) putchar(edge[k.first].cap ^ k.second ? 'S' : 'E'); putchar('\n');
	
	return 0;
}
```

---

## 作者：Akwamaryna (赞：0)

[安利一下我的 blog ~](https://www.cnblogs.com/Remained-Apple/p/15700517.html)

第一眼：这个是 dp ？

第二眼：神马 dp 神仙题啊，太弱了诶

第三眼：一发上网络流建模！

于是就有了这篇题解。

这里给出一个线性规划理解的最大流做法。

假设猫睡了 $n$ 天，则有收益 $\sum_{i=1}^n s_i$ ，然后所做的事情就是把某些天的睡觉改成吃饭。

设 $x_i\in\{0, 1\}$ 表示第 $i$ 天干的事情。 $x_i=0$ 表示睡觉， $x_i=1$ 表示吃饭。

依题意得

$\forall i\in[1,n-k+1],
me\leqslant\sum_{j=i}^{i+k-1}x_j\leqslant k-ms$

$\forall i\in[1,n]\cap\mathbb{Z},x_i\in\{0,1\}$ 

$\text{maximize}\{\sum_{i=1}^n (e_i-s_i)x_i\}$

再设变量 $y$ 和 $z$ 。得：

$x_1+x_2+...+x_k=me+y_1$

$x_1+x_2+...+x_k=k-ms-z_1$

$x_2+x_3+...+x_{k+1}=me+y_2$

$x_2+x_3+...+x_{k+1}+z_2=k-ms-z_2 $

$...$

$x_{n-k+1}+x_{n-k+2}+...+x_{n-1}+x_n=me+y_{n-k+1}$

$x_{n-k+1}+x_{n-k+2}+...+x_{n-1}+x_n=k-ms-z_{n-k+1}$

增加恒等式 $0=0$ ，并且设常数 $C=k-ms-me$ 。得：

$x_1+x_2+...+x_k=me+y_1 $

$y_1+z_1=C $

$x_{k+1}+C=x_1+y_2+z_1 $

$y_2+z_2=C $

$... $

$x_n+C=x_{n-k}+y_{n-k+1}+z_{n-k} $

$y_{n-k+1}+z_{n-k+1}=C$

$k-ms=x_{n-k+1}+x_{n-k+2}+...+x_n+z_{n-k+1} $

所有未知量和满足“流入=流出”，每一个式子也可以看作“流入=流出”，所以使用网络流算法。

为什么不用单纯型？因为不容易输出方案。~~其实是本人不会~~

因为有容量，还有费用 $e_i-s_i$ （仅限于表示 $x_i$ 的边），所以使用**最大费用最大流**来求解。

答案为 $\sum s_i + \text{MCMF}$ 。

如何判断方案？找出所有表示 $x_i$ 的边，满流就是吃饭，空流就是睡觉。

由于本人使用EK算法，所以是 $\Theta(nm^2)$ 。

# 代码时光到~

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f 
using namespace std;
int n,k,ms,me,_s[1010],_e[1010],sum;
bool vis[50010];int id[1010];
int front,rear,q[10000010];
int cnt=-1,head[50010],d[50010];
int s,t,p1[50010],p2[50010];
int pre[100010],ver[100010],cap[100010],cost[100010];
void adde(int u,int v,int f,int w){
	pre[++cnt]=head[u];ver[cnt]=v;cap[cnt]=f;cost[cnt]=w;head[u]=cnt;
	pre[++cnt]=head[v];ver[cnt]=u;cap[cnt]=0;cost[cnt]=-w;head[v]=cnt;
}
bool SPFA(int src,int &fs,int &cs){
	front=1,rear=1;
	memset(d,0x3f,sizeof(d));
	memset(p1,-1,sizeof(p1));
	memset(p2,-1,sizeof(p2));
	memset(vis,false,sizeof(vis));
	q[++rear]=src;vis[src]=true;d[src]=0;
	while(front<rear){
		int u=q[++front];vis[u]=false;
		for(int i=head[u];i!=-1;i=pre[i]){
			int v=ver[i];
			if(cap[i]<=0)continue;
			if(d[v]>d[u]+cost[i]){
				d[v]=d[u]+cost[i];
				p1[v]=u;p2[v]=i;
				if(!vis[v])vis[v]=true,q[++rear]=v;
			}
		}
	}
	if(p1[t]==-1)return false;
	int k=t;fs=0x3f3f3f3f3f3f3f3f;
	while(k!=s&&p1[k]!=-1)fs=min(fs,cap[p2[k]]),k=p1[k];
	if(fs<=0||k!=s)return false;
	k=t;cs=0;
	while(k!=s){
		cs=cs+cost[p2[k]];
		cap[p2[k]]-=fs;
		cap[p2[k]^1]+=fs;
		k=p1[k];
	}
	cs=cs*fs;return true;
}
void mincost_flow(int &fsum,int &csum){
	int ff,cc;
	fsum=0,csum=0;
	while(SPFA(s,ff,cc)){
		fsum=fsum+ff;
		csum=csum+cc;
	}
}
signed main(){
	memset(head,-1,sizeof(head));
	scanf("%lld%lld%lld%lld",&n,&k,&ms,&me);
	for(int i=1;i<=n;i++)scanf("%lld",&_s[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&_e[i]);
	for(int i=1;i<=n;i++)sum+=_s[i],_e[i]-=_s[i];
	s=0,t=(n-k+1<<1|1)+1;
	for(int i=1;i<=n-k+1;i++)adde(i<<1|1,i<<1,inf,0);//zi
	for(int i=1;i<=n-k+1;i++)adde((i-1)<<1|1,i<<1,inf,0);//yi
	for(int i=1;i<=n-k;i++)adde(s,i<<1|1,k-ms-me,0);//C
	for(int i=1;i<=n-k+1;i++)adde(i<<1,t,k-ms-me,0);//C
	for(int i=1;i<=k;i++){id[i]=cnt+1;
		adde(min(i<<1|1,t-1),1,1,-_e[i]);
	}
	for(int i=1;i<=n-k;i++){id[i+k]=cnt+1;
		adde(min((i+k)<<1|1,t-1),i<<1|1,1,-_e[k+i]);
	}
	adde(1,t,me,0);adde(s,t-1,k-ms,0);
	int tmpf=0,tmps=0;mincost_flow(tmpf,tmps);sum-=tmps;
	printf("%lld\n",sum);
	for(int i=1;i<=n;i++)printf(cap[id[i]]?"S":"E");
	putchar('\n');
	return 0;
}
```


---

