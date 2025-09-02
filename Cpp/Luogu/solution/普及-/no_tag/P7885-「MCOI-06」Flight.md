# 「MCOI-06」Flight

## 题目描述

书虫需要移动他的[盾构机](https://www.luogu.com.cn/problem/P7569)。

书虫将 MC 空间抽象为二维平面。他的盾构机现在在 $(a,b)$，而书虫想把盾构机移动到 $(c,d)$。

书虫每一步可以将盾构机向东南西北任何方向行动。但是这盾构机有一个限制：相邻两步不能向同一个方向走！

给定 $(a,b)$ 和 $(c,d)$，请计算书虫最少需要几步将盾构机移动到终点。

求书虫的最少步数。可以证明，他永远可以到达终点。



## 说明/提示

#### 样例 1 解释

 - 对于第一组，最优策略为 $(-2,0)\rarr(-2,1)$。
 - 对于第二组，最优策略为 $(0,1)\rarr(1,1)\rarr(1,2)\rarr(2,2)\rarr(2,3)\rarr(3,3)$。
 - 对于第三组，最优策略之一为 $(-1,1)\rarr (0,1)\rarr(0,0)\rarr(1,0)\rarr(1,1)$。

#### 数据规模与约定

**本题采用捆绑测试。**

 - Subtask 1（29 pts）：$0\le a,b,c,d\le 3$。
 - Subtask 2（29 pts）：$a=c$。
 - Subtask 3（42 pts）：无特殊限制。

对于所有数据，$1\le T\le 10^5$，$|a|,|b|,|c|,|d|\le10^{18}$。

## 样例 #1

### 输入

```
3
-2 0 -2 1
0 1 3 3
-1 1 1 1```

### 输出

```
1
5
4```

# 题解

## 作者：persimmon2008 (赞：21)

# 前言
这不就是一个最最最简单的**找规律**吗!?
# 思路
### 我们先来看一下这两种特殊情况：
###  case1:

![](https://cdn.luogu.com.cn/upload/image_hosting/ili4anw9.png)

即 $ |a-c|=|b-d| $

因为相邻两边方向不相同，所以有最小代价如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/0cqmb7xp.png)

即最小代价 $ =|a-c| + |b-d| $


### case2:
![](https://cdn.luogu.com.cn/upload/image_hosting/bjvo48nt.png)

即 $ a==c \parallel b==d $

相邻两边方向不相同,只能以 $ →↑→↓→↑→↓ $ 的方向移动，如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/nm59784i.png)

此时的最小距离分为两类：(假设b $ = $ d)

直线距离为偶数时：距离为 $ |a-c| \div 2 \ast 4 $ 

直线距离为奇数时：距离为 $ |a-c| \div 2 \ast 4 + 1 $

$ |a-c| \div 2 \ast 4 $ 可以约成 $ |a-c| \ast 2 $

而在$ |a-c| \div 2 $中，向下取整后会把多出的一步加在后面，便不能约了。

# Code

容易想到，任何两点都可以由上述两种情况构成的，如:

![](https://cdn.luogu.com.cn/upload/image_hosting/8zrbwkuy.png)

所以，我写出了如下代码，仅供参考。
```
#include<iostream>
#include<cstdio>
#include<cmath>
#define int long long
using namespace std;
inline int read() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return s*w;
}
inline void write(int x) {
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
signed main() {
	int n=read();
	while(n--){
		int a=read(),b=read();
		int c=read(),d=read();
		int x=abs(a-c),y=abs(b-d);
		if(x>y)swap(x,y);
		int ans=0;
		ans+=x*2;
		if(abs(x-y)%2)ans+=abs(x-y)/2*4+1;
		else ans+=abs(x-y)*2;
		write(ans);
		putchar('\n');
	}
}
```
# 完结撒花，不点个赞再走吗。

---

## 作者：苏联小渣 (赞：5)

## 题目大意

坐标系中从 $(a,b)$ 到 $(c,d)$，相邻两步不能走同一个方向，问至少要走多少步。

## 思路分析

本场比赛的签到题之一，简单思维题。

首先我们记 $ \Delta x= |a-c|$ , $\Delta y = |b-d|$。

假设起点在左下角，终点在右上角（其他情况同理，可以证明起点终点的相对位置不影响结果）

从起点到终点，最好的情况就是 $\Delta x = \Delta y$，方案为向右、向上、向右、向上……直到到达终点。所需步数为 $\Delta x + \Delta y$。

如果$\Delta x \neq \Delta y$，我们可以考虑贪心，先走一个正方形。所需步数为 $min(\Delta x,\Delta y) \times2$。此时我们所在的点和终点是在同一直线上的，距离为 $max(\Delta x,\Delta y)-min(\Delta x,\Delta y)$。此时我们就要讨论上式的奇偶性。

![](https://cdn.luogu.com.cn/upload/image_hosting/z1uxrvwo.png)

可以得到：还需要走的步数为：$(max(\Delta x,\Delta y)-min(\Delta x,\Delta y)) \times2 - (max(\Delta x,\Delta y)-min(\Delta x,\Delta y)) \% 2$

所以我们就得到了一个公式，从起点到终点，所需走的步数为：$min(\Delta x,\Delta y) \times2+(max(\Delta x,\Delta y)-min(\Delta x,\Delta y)) \times2 - (max(\Delta x,\Delta y)-min(\Delta x,\Delta y)) \% 2$

举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/97zexef8.png)

从 $(0,0)$ 到 $(4,8)$，先从 $(0,0)$ 到 $(4,4)$，再从 $(4,4)$ 到 $(4,8)$。

故一共需要 16 步。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, a, b, c, d;
signed main(){
	scanf ("%lld", &t);
	while (t --){
		scanf ("%lld%lld%lld%lld", &a, &b, &c, &d);
		int dx = abs(a-c), dy = abs(b-d);
		int mx = max(dx, dy), nx = min(dx, dy);
		printf ("%lld\n", nx * 2 + (mx - nx) * 2 - (mx - nx) % 2);
	}
	return 0;
}
```


---

## 作者：雨伞CKY (赞：3)

# 题意简述
- 书虫需要把盾构机从 $(a,b)$ 移至 $(c,d)$。
- 书虫每步可向任何方向移动 $1$ 个单位长度，但相邻两步不能向同一方向。求移动最少步数。
- 包含多组数据。$1\leq T\leq 10^{5},\lvert a\rvert,\lvert b\rvert,\lvert c\rvert,\lvert d\rvert\leq 10^{18}$。

# 题目分析
## 说明
1. 由平移可知：从 $(a,b)$ 移动至 $(c,d)$ 的最少步数等于从 $(0,0)$ 移动至 $(c-a,d-b)$ 的最少步数。
2. 由对称可知：从 $(0,0)$ 移动至 $(c-a,d-b)$ 的最少步数等于从 $(0,0)$ 移动至 $(\lvert c-a\rvert ,\lvert d-b\rvert )$ 的最少步数。

## 两点在同一列（行）
当 $a=c$ 时，两点在同一列。经过枚举，把盾构机从 $(0,0)$ 移至 $(0,k_{2})$ 所需的最少步数与 $k_{2}$ 的关系的如下表所示。其中，$k_{2}$ 为正整数。

| $k_{2}=$ | 可以达到最少步数的方案 | 所需最少步数 |
| :----------: | :----------: | :----------: |
| $1$ | $(0,0)\rightarrow (0,1)$ | $1$ |
| $2$ | $(0,0)\rightarrow (1,0)\rightarrow (1,1)\rightarrow (0,1)\rightarrow (0,2)$ | $4$ |
| $3$ | $(0,0)\rightarrow (0,1)\rightarrow (1,1)\rightarrow (1,2)\rightarrow (0,2)\rightarrow (0,3)$ | $5$ |
| $4$ | $(0,0)\rightarrow (1,0)\rightarrow (1,1)\rightarrow (0,1)\rightarrow (0,2)\rightarrow (1,2)\rightarrow (1,3)\rightarrow (0,3)\rightarrow(0,4)$ | $8$ |
| $5$ | $(0,0)\rightarrow (0,1)\rightarrow (1,1)\rightarrow (1,2)\rightarrow (0,2)\rightarrow (0,3)\rightarrow (1,3)\rightarrow (1,4)\rightarrow (0,4)\rightarrow (0,5)$ | $9$ |
| $\dotsc$ | $\dotsc$ | $\dotsc$ |

不难发现：当 $k_{2}\equiv 0\pmod 2$ 时，所需最少步数为 $2k_{2}$；否则，所需最少步数为 $2k_{2}-1$。

同理可得：当 $b=d$（两点在同一行）时，此规则仍成立。

## 两点不在同一列（行）
如果两点不在同一列（行）时，我们可以把盾构机移动至目标点所在列（行）。我们要把盾构机从 $(0,0)$ 移至 $(k_{1},k_{1})$，其中 $k_{1}=\min (\lvert c-a\rvert ,\lvert d-b\rvert )$。完成此操作的所需步数为 $2k_{1}$。之后，盾构机的位置与目标位置在同一列（行）。

## 总结
如果盾构机 $(0,0)$ 与目标点 $(\lvert c-a\rvert ,\lvert d-b\rvert )$ 不在同一列（行）时，先将盾构机移动至目标点所在列（行）。操作后，盾构机所在位置为 $(k_{1},k_{1})$，移动 $2k_{1}$ 步，其中 $k_{1}=\min (\lvert c-a\rvert ,\lvert d-b\rvert )$。

接着，把盾构机从 $(k_{1},k_{1})$ 移动至目标点 $(\lvert c-a\rvert ,\lvert d-b\rvert )$。当 $k_{2}\equiv 0\pmod 2$ 时，所需最少步数为 $2k_{2}$；否则，所需最少步数为 $2k_{2}-1$。其中，$k_{2}=\lvert \lvert c-a\rvert -\lvert d-b\rvert \rvert$。即可完成移动。

## 计算公式
所以，需要移动的次数 $K$ 的表达式如下：

$$
K=
\begin{cases}
   \min (t_{1},t_{2})+2\lvert t_{1}-t_{2} \rvert & \text{if } t_{1}\equiv t_{2}\pmod 2 \\
   \min (t_{1},t_{2})+2\lvert t_{1}-t_{2} \rvert-1 & \text{if } t_{1}\not \equiv t_{2}\pmod 2
\end{cases}
$$

其中，
$t_{1}=\lvert c-a\rvert ,t_{2}=\lvert d-b\rvert $。

化简得：

$$
K=
\begin{cases}
   2\max (t1,t2) & \text{if } t_{1}\equiv t_{2}\pmod 2 \\
   2\max (t1,t2)-1 & \text{if } t_{1}\not \equiv t_{2}\pmod 2
\end{cases}
$$

其中，
$t_{1}=\lvert c-a\rvert ,t_{2}=\lvert d-b\rvert $。

# 代码
```cpp
#include <iostream>
using namespace std;

int T;
long long int a,b,c,d,t1,t2;

int main(){
    cin >> T;
    for (int i = 1;i <= T;i++){
        cin >> a >> b >> c >> d;
        t1 = abs(a - c),t2 = abs(b - d);
        if (t1 > t2) swap(t1,t2);// 保证 t1 < t2
        if ((t2 - t1) % 2 == 0) cout << 2 * t2 << endl;
        else cout << 2 * t2 - 1 << endl;
    }
    return 0;
}
```

---

## 作者：小之森夏音 (赞：2)

## 题目分析
设 $dx=|a-c|$ ， $dy=|b-d|$ ， $dxy=|dx-dy|$ ，点 $A(a,b)$ ，点 $B(c,d)$ 。

当 $dx≠dy$ 时，不妨设 $dx>dy$ ， $a<c$ ， $b<d$ （若不然，可将原图形旋转、翻转），点 $C(e,d)$ ， $e=a+dy+1$ 。由观察可得图中红色路径为一种符合题意的最短路径（图中 $dxy$ 为奇数）。

![](https://cdn.luogu.com.cn/upload/image_hosting/s6ndb36v.png)

则图中由点 $A$ 到点 $C$ 的路径长为 $e-a+dy=2dy+1$ 。

若 $dxy$ 为奇数（即图中所示情况），则 $dxy-1$ 为偶数。故图中由点 $C$ 到点 $B$ 的路径长为 $\dfrac{dxy-1}{2}\times4=2dxy-2$ 。

所以图中由点 $A$ 到点 $B$ 的路径长为 $2dy+1+2dxy-2=2dy+dx-dy+dxy-1=dx+dy+dxy-1$ 。又 $dxy$ 为奇数，故原式可写为 $dx+dy+2\lfloor\dfrac{dxy}{2}\rfloor$ 。

若 $dxy$ 为偶数，考虑当线段 $BC=dxy$ 时，由点 $A$ 到点 $B$ 的最短路径长为 $2dy+1+2(dxy+1)-2=dx+dy+dxy+1$ 。

而线段 $BC=dxy-1$ ，所以可以少走最后一步。故此时的最短路径长为 $dx+dy+dxy=dx+dy+2\lfloor\dfrac{dxy}{2}\rfloor$ 。

当 $dx=dy$ 时，由点 $A$ 到点 $B$ 的水平方向、由点 $A$ 到点 $B$ 的竖直方向交错走即可。此时最短路径长为 $dx+dy$ 。又 $dxy=0$ ，故原式可写为 $dx+dy+2\lfloor\dfrac{dxy}{2}\rfloor$ 。

综上所述，最短路径长（即最少步数）为 $dx+dy+2\lfloor\dfrac{dxy}{2}\rfloor$ 。

## 代码

```cpp
#include <stdio.h>
#include <stdlib.h>
#define ll long long

inline ll read() {
  char ch = getchar();
  ll x = 0, f = 1;
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while ('0' <= ch && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
int main() {
  ll T = read();
  while (T--) {
    ll a = read(), b = read(), c = read(), d = read();
    ll dx = abs(a - c), dy = abs(b - d);
    ll dxy = abs(dx - dy);
    printf("%lld\n", dx + dy + dxy / 2 * 2);
  }
  return 0;
}
```

---

## 作者：C_S_L (赞：1)

为了方便，令 $x=\left\vert a-c\right\vert$ ，$y=\left\vert b-d\right\vert$ 。

进行分类讨论：

当 $\left\vert x-y\right\vert\leqslant1$ 时，答案即为 $x+y$，即 $(a,b)$ 和 $(c,d)$ 的曼哈顿距离。

当 $\left\vert x-y\right\vert\geqslant2$ 时，我们先假设他们走了 $(a,b)$ 和 $(c,d)$ 的曼哈顿距离，然后计算它少走了几步。

画图进行分析：

![分析](https://cdn.luogu.com.cn/upload/image_hosting/vm4uxp7u.png)

将 $(a,b)$ 转换到 $(a+k,b+k)$（$k$为整数） 使其与 $(c,d)$ 在同一行或同一列上，然后发现 $(a+k,b+k)$ 到 $(c,d)$ 的距离即为 $\left\vert x-y\right\vert$ 。

观察后，我们发现少走了 $\left\lfloor\dfrac{\left\vert x-y\right\vert}{2}\right\rfloor$ 次，每次少走 $3$ 步，多走 $1$ 步，故每次共少走 $2$ 步。所以，一共少走了 $2\left\lfloor\dfrac{\left\vert x-y\right\vert}{2}\right\rfloor$ 步。

故最终答案为 $x+y+2\left\lfloor\dfrac{\left\vert x-y\right\vert}{2}\right\rfloor$ 。

综上，答案为 $\begin{cases}x+y&\left\vert x-y\right\vert\leqslant1\\x+y+2\left\lfloor\dfrac{\left\vert x-y\right\vert}{2}\right\rfloor&\left\vert x-y\right\vert\geqslant2\end{cases}$ 。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
ll a,b,c,d,x,y;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
		x=abs(a-c),y=abs(b-d);
		if(abs(x-y)<=1){
			printf("%lld\n",x+y);
		}
		else{
			ll now=abs(x-y);
			printf("%lld\n",x+y+now/2*2);
		}
	}
	return 0;
}
```


---

## 作者：一只书虫仔 (赞：0)

#### Description

> 要从 $(a,b)$ 走向 $(c,d)$，要求不能有连续两步走同一方向，求至少需要多少步。

#### Solution

考虑简化模型，不难发现能把 $(a,b) \to (c,d)$ 转化为 $(0,0) \to (|a-c|,|b-d|)$。

而我们可以考虑如下构造（设 $A=|a-c|$，$B=|b-d|$）：

- 先用向左向上的路径走到最上面；
- 然后向上，向右，向下，向右，向上，向右，向下 …… 如此前进走到终点。

那么最终答案即为：

- 走到最上面要用 $A+B$ 的长度；
- 走到终点要用 $|A-B|-|A-B| \bmod 2$ 的长度，这个 $|A-B|\bmod 2$ 是因为有些情况最后一步是向右，有些情况最后一步是向下。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int main () {
	int t;
	scanf("%d", &t);
	while (t--) {
		long long a, b, c, d;
		scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
		a = abs(a - c), b = abs(b - d);
		if (a > b) swap(a, b);
		printf("%lld\n", 2 * b - (b - a) % 2);
	}
	return 0;
}
```

---

