# Strange Radiation

## 题目描述

 $ n $ people are standing on a coordinate axis in points with positive integer coordinates strictly less than $ 10^{6} $ . For each person we know in which direction (left or right) he is facing, and his maximum speed.

You can put a bomb in some point with non-negative integer coordinate, and blow it up. At this moment all people will start running with their maximum speed in the direction they are facing. Also, two strange rays will start propagating from the bomb with speed $ s $ : one to the right, and one to the left. Of course, the speed $ s $ is strictly greater than people's maximum speed.

The rays are strange because if at any moment the position and the direction of movement of some ray and some person coincide, then the speed of the person immediately increases by the speed of the ray.

You need to place the bomb is such a point that the minimum time moment in which there is a person that has run through point $ 0 $ , and there is a person that has run through point $ 10^{6} $ , is as small as possible. In other words, find the minimum time moment $ t $ such that there is a point you can place the bomb to so that at time moment $ t $ some person has run through $ 0 $ , and some person has run through point $ 10^{6} $ .

## 说明/提示

In the first example, it is optimal to place the bomb at a point with a coordinate of $ 400000 $ . Then at time $ 0 $ , the speed of the first person becomes $ 1000 $ and he reaches the point $ 10^{6} $ at the time $ 600 $ . The bomb will not affect on the second person, and he will reach the $ 0 $ point at the time $ 500000 $ .

In the second example, it is optimal to place the bomb at the point $ 500000 $ . The rays will catch up with both people at the time $ 200 $ . At this time moment, the first is at the point with a coordinate of $ 300000 $ , and the second is at the point with a coordinate of $ 700000 $ . Their speed will become $ 1500 $ and at the time $ 400 $ they will simultaneously run through points $ 0 $ and $ 10^{6} $ .

## 样例 #1

### 输入

```
2 999
400000 1 2
500000 1 1
```

### 输出

```
500000.000000000000000000000000000000
```

## 样例 #2

### 输入

```
2 1000
400000 500 1
600000 500 2
```

### 输出

```
400.000000000000000000000000000000
```

# 题解

## 作者：EasonLiang (赞：4)

[CF832C Strange Radiation](https://www.luogu.com.cn/problem/CF832C)

Duel 到的。题解区没人写李超树？

设炸弹位置为 $p$。

以往左走的人为例：设此人初始位置为 $x \le p$，初始速度为 $v$。

稍微推一下式子可以知道这个人到达 0 所需时间：

$$\min(\dfrac{sp - vx}{s^2 - v^2}, \dfrac xv) = \min(\dfrac{s}{s^2 - v^2} p - \dfrac{vx}{s^2 - v^2}, \dfrac xv)$$

这不就是 $kx + b$ 的形式嘛！

从小到大枚举 $p$，并实时将 $x \le p$ 的、往左走的人加入李超树。在李超树上查询，就可以得到炸弹放在位置 $p$ 时，往左走的人到达 0 所需最小时间 $f_p$。

往右走同理，用另一颗李超树计算出炸弹放在位置 $p$ 时，往右走的人到达 $10^6$ 所需最小时间 $g_p$。

答案即为 $\min\limits_{p=0}^{10^6} \max(f_p, g_p)$。[AC Code](https://codeforces.com/contest/832/submission/294210344)

---

## 作者：max67 (赞：2)

# 前言

~~没想到我也有写黑题题解的一天~~。

看了看 CF，这是 Div.2 的 C 题，但居然有 2500 分 。看看这个难度曲线，我感受到了当时打比赛的看到 C 题的绝望心情：

[![5rwKkd.png](https://z3.ax1x.com/2021/10/21/5rwKkd.png)](https://imgtu.com/i/5rwKkd)

（pass: D 题 1900 分，E 题 2600 分）

# 题面

## 题目描述

有 $n$ 个人站在数轴上。对于每个人，我们知道他的位置，最大速度以及前进方向（向左或向右）。这 $n$ 个人刚开始静止不动

其中这 $n$ 个人所在的位置 $x$ 均满足：$0<x<10^6$ 且 $x$ 为正整数。

你可以在数轴上任意一个非负整数上放置一个炸弹($0\le$ 炸弹位置 $\le 10^6$)。当你引爆他的时候，所有人都会开始用他的最大速度朝着对应的方向奔跑。另外，两条奇怪的光线将会从炸弹爆炸的位置处开始，朝着数轴两端（向左和向右）以最大速度 $s$ 传播。

**注意**：$s$ 严格大于所有人的速度。

当一个正在奔跑的人接触到了一条光线，且光线的方向与人的方向相同，那么他的速度为立刻增加 $s$。（只会增加一次）

请问，让你任意选择炸弹的位置，花最少的时间，使得至少有一个人穿过位置 $0$，至少有一个人穿过位置 $10^6$。并输出这个最小的时间。

## 输入格式

第一行包含两个数：$n$ 和 $s$，表示人数和光线的速度。

接下来有 $n$ 行，第 $i$ 行有三个数：$x_i$ ，$v_i$ 和 $t_i$。表示这个人所处的位置，最大速度以及方向。（$t_i=1$ 表示这个人向左，$t_i=2$表示这个人向右 ）

**注意** ：数据保证一定有解。

## 输出格式

输出满足条件的最小时间。设您的答案为 $a$，标准答案为 $b$。若他们满足以下条件：$\frac{|a-b|}{max(1,|b|)}\le 10^{-6}$，则认为您的答案正确

## 样例说明

在样例 $1$ 中，炸弹放在位置 $400000$ 上是最优的，此时在时间 $0$，第一个人的速度变为 $1000$,让他在时刻 $600$ 时到达位置 $10^6$。炸弹不会影响第二个人，他会在时刻 $500000$ 时到达 $0$ 点。

在样例 $2$ 中，炸弹放在位置 $500000$ 上是最优的，光线将在时刻 $200$ 时追上两个人，此时，第一个人位于位置 $300000$，第二个人位于位置 $700000$。他们的速度将变为 $1500$。当时刻 $400$ 时，他们讲同时到达 位置 $0$ 和 位置 $10^6$。

## 数据约定

$2\le n \le 10^5$，$2\le s \le 10^6$，$0\le$ 炸弹位置 $\le 10^6$

$0< x_i < 10^6$，$1 \le v_i \le s$，$1 \le t_i \le 2$

$n,s,x_i,v_i,t_i$，炸弹位置 $\in N^*$


# 题解

（需要简化题意的可以去 luogu 题面上康康。）

首先看到题目答案中有 "至少"，"最少" 的字眼，且题目限制比较多，第一时间考虑二分。

考虑答案是否有单调性质——这是显然的，若一个方案满足最小的时间，保持这个方案不变，那么时间增大仍然满足条件。

那么我们二分枚举最少时间，然后我们希望通过题目的限制条件来判定——有没有一种放炸弹的方案满足花费时间小于等于我们枚举的答案。

然而这样子二分不二分并没有什么区别。考虑我们需要判定可行性，那么就不需要精确求解，考虑有没有一些区间放炸弹满足条件即可。

那么分别考虑炸弹对每一个人的影响。为了方便说明，这里先探讨人向左的情况。

那么我们已知人到 $0$ 点的距离 $dis_1$，人的速度 $v$，人的方向（向左）以及限制时间 $t$。我们设炸弹距离 $0$ 点的距离为 $x$ ，人与光线接触时行走的距离为 $dis_2$，

若不加炸弹也能在限定时间内到达 $0$ 点，说明我们可以把炸弹放到任意一个点。

$$
\frac{dis_1}{v}\le t
$$

若即使把炸弹放在他那个位置，他依然不能到达，那么他不能对答案造成贡献。

$$
dis_1 - (v+s) \times t \ge 0
$$
否则，我们要开始愉快的推柿子了。

根据[追及问题](https://baike.baidu.com/item/%E8%BF%BD%E5%8F%8A%E9%97%AE%E9%A2%98/1039047?fr=aladdin)，我们可以推出 $dis_2$ 的值：

1.
$$
dis_2= \frac{(x-dis_1) \times v}{s-v}
$$

（时间等于路程除以速度，路程等于时间乘以速度）

那么根据题意，我们能列出以下限制条件：

2.
$$
\frac{dis_2}{v}+\frac{dis_1-dis_2}{s+v} \le t  
$$


（人与光线相遇的时间加上人相遇后到达 $0$ 点的时间，也就是到达 $0$ 点的时间必须小于限制时间）  

3.
$$
dis_1\le x
$$

（炸弹的位置必须在人的右边，否则起不了加速作用）

因为我们要限制炸弹位置 $x$，但第一个式子中没有 $x$，我们需要再来一个式子表示 $x$。

4.

$$
x = (dis_1-dis_2)+\frac{dis_2}{v} \times s
$$

(由追及问题可得当 $x$ 与光线相遇时，花费的时间为 $\frac{dis_2}{v} $，速度为 $s$，可以算出 $x$ 与 $dis_2$  之间的距离，再加上 $dis_2$ 离 $0$ 点的距离，就是 $x$ 与 $0$ 点的距离)

然后开始愉快的化式子后（过程在[云剪贴板](https://www.luogu.com.cn/paste/po5ye8m8)里）,我们得到了最终结果：

$$
dis_1 \le x \le \frac{t \times (s^2-v^2) +dis_1 \times v}{s}
$$

然后再考虑向右的情况（过程在[云剪贴板](https://www.luogu.com.cn/paste/ma0cqnsk)里，过程类似，定义相同）：

首先考虑能不能直接到达，若满足以下条件，则不用炸弹也能到达：

$$
dis_1 + v \times t \ge 10^6
$$

再考虑若炸弹放在他的位置依然不能到达，那么不能对答案造成贡献。

$$
dis_1 + (v+s) \times t \le 10^6
$$
否则，要满足以下条件：
$$
\frac{10^6 \times(s-v) + dis_1 \times v - t \times  (s^2-v^2)}{s} \le x \le dis_2
$$

那么对于一个方向相同的人，我们求出了使得他满足条件的炸弹的位置（令人高兴的是，他是一个连续的区间，使得我们可以用简单的差分维护），那么多个人方向相同呢？因为只需要 "至少"，所以我们只需要求区间并即可。

那么对于方向不同的人，我们需要求出一个炸弹位置，使得两个方向的人都满足——即求区间交。

那么整道题的思路就豁然开朗了。

那么就是写一个实数二分，每次求差分求两个区间并，判一下两个区间并有无交即可

# 代码实现
我之前代码求区间并使直接求左右端点的。显然这是错的，会被下面这种数据卡掉。

[![5ssags.png](https://z3.ax1x.com/2021/10/21/5ssags.png)](https://imgtu.com/i/5ssags)

但我居然 A 了，~~这就离谱~~。

那么下面具体讲讲几个要点：

* 判区间并与交要用前缀和

* 要特判一定满足，一定不满足以及区间的情况。

* double 和 int 不要搞混

* 注意炸弹位置必须是整数，要根据 $\le$ 和 $\ge$ 特殊判断。要满足取整后的区间是原区间的子集。（$\le$ 用 floor，$\ge$ 用 ceil）

具体详见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+1e3,inf=1e6;//数组下标必须是正数，所以要用 int
const double eps=1e-9;
struct People
{
    int dir;
    double x,v;//取 double 就不用 * 1.0
}p[N];
int n;
double s;
int suml[N],sumr[N];

bool check(double t)
{
    for(int i=0;i<=inf+10;i++)suml[i]=sumr[i]=0;
    for(int i=1;i<=n;i++)
    {
        if(p[i].dir==1)
        {
            if(p[i].x-(p[i].v+s)*t>0)continue;
            if(p[i].x-p[i].v*t<=0)
            {
                suml[0]++;suml[inf+1]--;continue;
            }
            double x=floor((t*(s*s-p[i].v*p[i].v)+p[i].x*p[i].v)/s);
            //x 用 int 可能会爆
            suml[(int)p[i].x]++;suml[(int)min(x+1,inf*1.0+1)]--;
        }
        else  
        {
            if(p[i].x+(p[i].v+s)*t<inf)continue;
            if(p[i].x+p[i].v*t>=inf)
            {
                sumr[0]++;sumr[inf+1]--;continue;
            }
            double x=ceil((1.0*inf*(s-p[i].v)-t*(s*s-p[i].v*p[i].v)+p[i].x*p[i].v)/s);
            sumr[(int)max(x,0.0)]++;sumr[(int)p[i].x+1]--;
        }
    }
    for(int i=1;i<=inf;i++)
    {
        suml[i]+=suml[i-1],sumr[i]+=sumr[i-1];
        if(suml[i]&&sumr[i])return 1;
    }
    return suml[0]&&sumr[0];//特判不用炸弹也能到的点
}
int main()
{
    scanf("%d%lf",&n,&s);
    for(int i=1;i<=n;i++)scanf("%lf%lf%d",&p[i].x,&p[i].v,&p[i].dir);
    double l=0,r=1e6,mid;
    while(r-l>=eps)//实数二分
    {
        mid=(l+r)/2;
        if(check(mid))r=mid;
        else l=mid;
    }
    printf("%.12lf\n",l);
    return 0;
}
```

# 后记

感觉这题最多评个蓝，不过 CF 评分 2500，可能是式子过于冗长（向我这样的老年选手就推的很慢），精度要求高的原因吧。

---

## 作者：流水行船CCD (赞：1)

这题思路还是比较启发的。

# 思路

对于这种时间最小化的问题，大多具有**单调性**，且本题在未确定最快到达时间的情况下变量很多，因此考虑实数二分时间，问题转化为：

> 在 $mid$ 时刻内，是否有一种炸弹的摆放使至少两个人到达 $0$ 和 $10^6$ 处。

考虑如何 check。
  
- 第一种思路是枚举炸弹放置在 $[0,10^6]$ 中的那个位置，快速求出人到边界的最短时间，但是这样会发现人花费的时间是一个追及问题，式子很复杂，无法快速求最值（也没有用上二分的性质）。

- 考虑换一个角度入手，枚举每一个人，发现对于每一个人，都有唯一确定的一个区间 $[l,r]$，使炸弹在这个区间内爆炸可以使它在 $mid$ 时间内到达边界。

  - 考虑如何快速求出这个区间（这里以人往左跑举例，向右跑同理），设当前人坐标为 $x$，向左跑速度为 $v$，二分出的最大到达边界时间为 $mid$，冲击波速度为 $F$。
    - 如果 $\frac{x}{v} \le mid$，无需炸弹加速，区间为 $[0,10^6]$。
    - 如果 $\frac{x}{v + F} > mid$，以最大速度奔跑仍不能满足条件，区间为空。
    - 否则，设冲击波与人相交的最晚时间（即人在此情况下在 $mid$ 时刻刚好到终点）为 $t$，则有方程：
      $$v \times t + (v + F) \times (mid - t) = x$$
    - 解得：$t = \frac{(v+F) \times mid - x}{F}$。因此，炸弹距离人起点最多相距 $\lfloor t \times (F - v) \rfloor$ 单位长度（更远冲击波追上人的时间就不合法了），合法区间为 $[x,\min (10^6,x + \lfloor t \times (F - v) \rfloor)]$。
  - 此时问题就转换为是否有一个炸弹满足同时在至少一个向左走的人合法区间和至少一个向右走的人合法区间内，只需要将向左的人区间求并，向右的人区间求并，再将这两个并集取交集，判断是否为空即可。
  - **差分**维护区间并集，注意清空即可。

- $O(V \log V)$ 可以通过。

# AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define REP(i, l, r) for (int i = l; i <= r; ++i)
#define PER(i, l, r) for (int i = l; i >= r; --i)
using namespace std;
namespace fast_IO{
...
}using namespace fast_IO;
#define int long long 
const int N = 1e5 + 7;
const int inf = 1e6 + 7;
namespace code {
	int n, F, d1[inf], d2[inf];
	struct per {int x, v, way;} c[N];
	inline bool chk(double time) {
		REP(i, 1, n) {
			int L = 0, R = 0;
			if (c[i].way == 1) {
				int diss = c[i].x;
				if (1.0 * diss / c[i].v <= time) L = 0, R = 1000000;
				else {
					double t0 = 1.0 * (1.0 * time * (c[i].v + F) - 1.0 * diss) / F;
					if (t0 < 0.0) continue;
					int d = floor(t0 * (F - c[i].v));
					L = c[i].x, R = min(1000000ll, c[i].x + d);	
				} ++d1[L], --d1[R + 1];
//				jyt << L << "~" << R << '\n'; 
			} else {
				int diss = 1000000ll - c[i].x;
				if (1.0 * diss / c[i].v <= time) L = 0, R = 1000000;
				else {
					double t0 = 1.0 * (1.0 * time * (c[i].v + F) - 1.0 * diss) / F;
					if (t0 < 0.0) continue;
					int d = floor(t0 * (F - c[i].v));
					L = max(0ll, c[i].x - d), R = c[i].x;	
				} ++d2[L], --d2[R + 1];
//				jyt << L << "~" << R << '\n'; 
			}
		}
		bool flag = false; int c1 = 0, c2 = 0;
		REP(i, 0, 1000000) {
			c1 += d1[i], c2 += d2[i];
//			if (i == 450000) jyt << c1 << "," << c2 << '\n';
			flag |= (c1 && c2);
			d1[i] = d2[i] = 0;
		}
		return flag;
	}
	signed main() {
		ld >> n >> F;	
		REP(i, 1, n) ld >> c[i].x >> c[i].v >> c[i].way;
		sort(c + 1, c + n + 1, [](per a, per b) {return a.way == b.way ? a.x < b.x : a.way < b.way;});
//		jyt << chk(1100) << '\n';
		double l = 0, r = 1000000, Res = 1000000;
		while (r - l > 10e-9) {
			double mid = (l + r) / 2.0;
			if (chk(mid)) r = mid, Res = mid;
			else l = mid;
		} printf("%.8lf", Res);
		return 0;
	}
}
signed main() {
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	code::main();
	return 0;
}
```

---

## 作者：泠小毒 (赞：1)

# Strange Radiation
你有一个炸弹，速度比人快。炸弹气流从爆炸位置以速度s向左右两边飞。

一维坐标。给你n个人的坐标x、走向dir、速度v。

当炸弹和人重叠且同向的时候，人的速度变为v+s，不考虑逆气流的影响。

让你在[0, 1e6]的范围内放置炸弹，花最少的时间使得至少有一个走到位置0，还有一个人走到位置1e6。求最少时间。
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190512/)
## 解法
将时间二分，check的时候对于每个点考虑炸弹可以放置的区间，求并集，最后左右区间如果有交集就是可行解，需要用到前缀和去维护

需要推一个计算每个点是否可行的公式，下面给出三个关于向左走是否可行的式子，请自行求解QAQ

设人离左边界距离为dis1，气流赶上人时人走了dis2，炸弹离左边界距离为x

人的速度v，气流速度s，二分出的时间t

dis2/v+(dis1-dis2)/(v+s)<=t

x>=dis1

x=(dis1-dis2)+dis2·x/v

至于向右走是否可行的式子，同理可自行推导，~~其实是我懒得写（大雾~~
## ac代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define eps (1e-8)
using namespace std;
struct node{int x,v,w;}a[1000010];
int n,s,suml[1000010],sumr[1000010];
double l=0,r=1000010;
bool judge(double t)
{
    memset(suml,0,sizeof(suml)),memset(sumr,0,sizeof(sumr));
    for(int i=1;i<=n;i++)if(a[i].w==1)
	{
		double d=a[i].x;
        if(d<t*(1.0*a[i].v)+eps){suml[0]++;continue;}
        ll dis=floor((t*(1.0*(a[i].v+s))-d)*(1.0*(s-a[i].v))/(1.0*s)+1.0*a[i].x);
        if(dis>=a[i].x)dis=min(dis,1000000ll),suml[a[i].x]++,suml[dis+1]--;
    }
	else
	{
	    double d=1000000-a[i].x;
	    if(d<t*(1.0*a[i].v)+eps){sumr[0]++;continue;}
	    ll dis=ceil(1.0*a[i].x-(t*(1.0*(a[i].v+s))-d)*(1.0*(s-a[i].v))/(1.0*s));
	    if(dis<=a[i].x)dis=max(dis, 0ll),sumr[dis]++,sumr[a[i].x+1]--;
	}
    for(int i=1;i<=1000000;i++)
		{suml[i]+=suml[i-1],sumr[i]+=sumr[i-1];if(suml[i]&&sumr[i])return 1;}
	return suml[0]&&sumr[0];
}
int main()
{
    scanf("%d%d",&n,&s);
    for(int i=1;i<=n;i++)scanf("%d%d%d",&a[i].x,&a[i].v,&a[i].w);
    while(r-l>eps){double mid=(l+r)/2;if(judge(mid))r=mid;else l=mid;}
    printf("%.6f\n",l);
}
```

---

