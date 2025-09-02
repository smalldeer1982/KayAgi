# Four Coloring

## 题目描述

给定一个$H \times W$的网格，试给其中所有格子染`RYGB`四种颜色之一，使得网格上任意一对曼哈顿距离为$d$的格子颜色不同。

## 样例 #1

### 输入

```
2 2 1```

### 输出

```
RY
GR```

## 样例 #2

### 输入

```
2 3 2```

### 输出

```
RYB
RGB```

# 题解

## 作者：Heartlessly (赞：21)

## Description

给定一个 $h \times w$ 的网格，试给其中所有格子染 `RYGB` 四种颜色之一，使得网格上任意一对曼哈顿距离为 $d$ 的格子颜色不同。

$(2 \leq h,w \leq 500, 1\leq d \leq h + w - 2)$

## Solution

曼哈顿距离并不方便处理，我们考虑把它转化为切比雪夫距离。（详见 **[常用距离算法详解](https://www.luogu.org/blog/xuxing/Distance-Algorithm)**）

举个例子，当 $d = 3$ 时，我们把曼哈顿坐标系（网格）旋转 $45^\circ$（即 $(i,j) \Rightarrow (i+j,i - j)$ ），得到切比雪夫坐标系。

其中蓝点是到红点距离为 $3$ 的点，切比雪夫坐标系中的点到周围 $8$ 个点的距离都是 $1$ 。

![VOZvLT.png](https://s2.ax1x.com/2019/06/19/VOZvLT.png)

考虑把切比雪夫坐标系分成多个网格，每个网格的大小是 $d \times d$ 。如果我们给同一网格中的点染相同的颜色（中心网格的所有点对的切比雪夫距离都 $< d$），那么对于任意一个网格，它周围 $8$ 个网格的颜色都应该与它不同，因为周围网格存在到中心网格距离为 $d$ 的点。

![VOAVa9.png](https://s2.ax1x.com/2019/06/19/VOAVa9.png)

怎么给网格染色呢？

我们会发现对于任意一个网格，它左上，右上，左下，右下网格的横坐标与纵坐标的奇偶性是相同的，上下网格的奇偶性也是相同的，左右网格的奇偶性也是相同的，但周围 $8$ 个网格都与中心网格的奇偶性不同。

所以一种有效的方式是按网格横坐标，纵坐标的奇偶性分成 $4$ 种颜色。对于坐标 $(x,y)$，其所在的网格为 $(\left \lfloor \frac{x}{d} \right \rfloor,\left \lfloor \frac{y}{d} \right \rfloor)$ 。若设奇数为 $1$，偶数为 $0$，则 $4$ 种颜色分别对应 $(0,0),(0,1),(1,0),(1,1)$ 。时间复杂度为 $O(hw)$ 。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

int h, w, d;
char s[4] = { 'R', 'Y', 'G', 'B' };//四种颜色 

int main() {
    read(h), read(w), read(d);
    for (int i = 1; i <= h; ++i, putchar('\n'))
        for (int j = 1; j <= w; ++j) {
            int x = i + j + w, y = i - j + w;
            //转成切比雪夫坐标系，+w 是因为防止坐标出现负数，方便得出奇偶性 
            putchar(s[((x / d) & 1) * 2 + ((y / d) & 1)]);
        }
    return 0;
}
```



---

## 作者：μηδσ (赞：2)

## Description

_~~老样子，三步走~~_

题目给出了$N$,$M$,$D$，问是否可以把一个$N\times M$的网格染成四种颜色，使得任意两个曼哈顿距离为$D$的点颜色两两不同

## Solution

在做这道题之前，先了解一下在平面内几个著名的“距离”

### 欧几里得距离

二维空间中两点的直接距离（这个应该是我们生活中最最常用的

公式：$d=\sqrt{|x_1-x_2|^2+|y_1-y_2|^2}$

~~其实和这道提没啥关系，主要是他太有名了~~

### 曼哈顿距离

这个其实就没有上面的那么常用了

起源据说是因为在美国的曼哈顿，所有的房子（或者是一块房子）都事矩形的，所有的马路都是横平竖直的，如果你要从一个点走向另外一个点，只要依靠曼哈顿距离了（~~你总不能从房子上方飞过去吧~~

公式：$d=|x_1-x_2|+|y_1-y_2|$

### 切比雪夫距离

如果不是某次有幸了解到了这个，我还真不知道有这个东西

公式：$d=max\{|x_1-x_2|,|y_1-y_2|\}$

### “进入正题”

满大度的距离实在不是很好求，于是把曼哈顿距离转换成切比雪夫距离，就是把坐标通过旋转转成$(x+y,x-y)$
，这样队友每一个点，周围的某一全的点都不能和他同色

然后就变得简单堕落

把每一个$D\times D$的格则堪称一个大格子这样之哟保证一个大格子的在周围一圈没有相同颜色的大格子就可以了。

这样就把问题转化成了每个大个子的上下左右都不能有相同的颜色了，然后就可以这么染:

$$12121212...\ \ \ \ \ \ \ \ \ 12341234...$$

$$34343434...\ \ \ \ \ \ \ \ \ 34123412...$$

$$12121212...\ \ \ \ \ \ \ \ \ 12341234...$$

$$34343434...\ \ \ \ \ \ \ \ \ 34123412...$$

$$...\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ ...$$

大概这两类的染色显然符合要求

ps:其实我觉得这道题的本质就是四色定理

思路结束，看代码吧。

## Code

~~~cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

#define re register
#define rep(a, b, c) for(re long long a = b;a <= c;a++)
#define per(a, b, c) for(re long long a = b;a >= c;a--)


template <typename T>
inline void read(T &x){
	x = 0;
	char c = 0;
	T w = 0;
	while(!isdigit(c))
		w |= c == '-', c = getchar();
	while(isdigit(c)) x = x * 10 + (c ^ 48), c = getchar();
	if(w)
		x = -x;
}

int h, w, d;
int mp[2005][2005];

void init(){
	rep(i, 0, 2000)
		rep(j, 0, 2000)
			mp[i][j] = ((i / d) % 2) * 2 + (j / d) % 2;
}

int main(){
	read(h); read(w); read(d);				//输入H，W，D 
    init();
    rep(i, 1, h){
    	rep(j, 1, w){						//将曼哈顿坐标系转换成切比雪夫坐标系 
    		int x = i + j + 500;			//+500是为了防止出现负数 
    		int y = i - j + 500;
            if(mp[x][y] == 0)				//判断一下到底应该是什么颜色 
				putchar('R');
            else if(mp[x][y] == 1)
				putchar('Y');
            else if(mp[x][y] == 2)
				putchar('G');
            else 
				putchar('B');
		}
		puts("");
	}
    return 0;
}
~~~

---

## 作者：cqbzlzm (赞：1)

摘抄自[我的博客](https://www.luogu.com.cn/article/ur9n70t7)

首先把曼哈顿距离转换成切比雪夫距离，然后把新坐标系的整点按照 $d\times d$ 的矩形进行分割，得到的图形按如图进行涂色：

![](https://pic.imgdb.cn/item/65db5cbe9f345e8d0381178e.png)

所以代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n, m, d;
    scanf("%d%d%d", &n, &m, &d);
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            int x = i + j + 114514, y = i - j + 114514;
            if (((x / d) % 2) * 2 + (y / d) % 2 == 0) putchar('R');
            if (((x / d) % 2) * 2 + (y / d) % 2 == 1) putchar('Y');
            if (((x / d) % 2) * 2 + (y / d) % 2 == 2) putchar('G');
            if (((x / d) % 2) * 2 + (y / d) % 2 == 3) putchar('B');
        }
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：tommymio (赞：1)

染色问题一般先想到奇偶染色，但是这题似乎没有很好的切入点。我们来一步一步转化问题。

曼哈顿距离可以转化成切比雪夫距离，通过变换坐标系，这是一个套路。为什么要转化呢？我们发现与点 $x$ 曼哈顿距离为 $d$ 的点构成了一个正方形，并且是斜着的，这不是很好处理。

变换过后，自然可以想到将变换后的坐标系分成 $d\times d$ 的块，块内的点显然不会有切比雪夫距离为 $d$ 的情况存在，所以只需考虑块间了。我们发现对于一个块 $x$，它的上面，下面，左边，右边的块中都有可能含有与块 $x$ 中某个点切比雪夫距离为 $d$ 的点，因此块 $x$ 必须与其上下左右的块颜色都不相同。

而我们自然又有一个贪心的策略，如果一些块可以染相同的颜色，就直接染。块 $x$ 上面的块和块 $x$ 下面的块就算颜色相同也不要紧，因为这两个块之间不可能存在切比雪夫距离为 $d$ 的点。块 $x$ 右边与块 $x$ 左边的点同理。进一步观察，发现这两对块的奇偶性各自相同，即块 $x$ 左右的块奇偶性相同，块 $x$ 上下的块奇偶性相同，但是这两对块之间的奇偶性却一定不相同。

想到了什么？是不是可以直接按行的奇偶性和列的奇偶性染色？正好 $4$ 种颜色，我们发现这样做的正确性根据上述结论是可以轻易证明出来的。

时间复杂度 $O(nm)$。

```cpp
#include<cstdio>
int main() {
	int n,m,d; scanf("%d%d%d",&n,&m,&d);
	for(register int i=1;i<=n;++i) {
		for(register int j=1;j<=m;++j) {
			int x=((i+j+m)/d)%2,y=((i-j+m)/d)%2;//平移整个变换后的坐标系，为了避免出现负数干扰判断奇偶性
			if(x==0&&y==0) putchar('R');
			if(x==0&&y==1) putchar('Y');
			if(x==1&&y==0) putchar('G');
			if(x==1&&y==1) putchar('B');
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：wwwwwza (赞：0)

### 前置知识：

- 在二维平面中，点 $(x_1,y_1)$ 与 $(x_2,y_2)$ 之间的曼哈顿距离为 $\left | x_1-x_2 \right | + \left | y_1-y_2 \right | $。

- 在二维平面中，点 $(x_1,y_1)$ 与 $(x_2,y_2)$ 之间的切比雪夫距离为 $\max(\left | x_1-x_2 \right | , \left | y_1-y_2 \right | )$。

- 将点 $(x,y)$ 变换成 $(x+y,x-y)$，原坐标系中的曼哈顿距离等于新坐标系中的切比雪夫距离。

- 将点 $(x,y)$ 变换成 $(\frac{x+y}{2},\frac{x-y}{2})$，原坐标系中的切比雪夫距离等于新坐标系中的曼哈顿距离。

### 本题做法：

将题目所属的曼哈顿距离转化成切比雪夫距离。

将网格按 $d\times d$ 分割，只要相邻的块的颜色不相同就满足条件，可以按 $\left \lfloor \frac{x}{d} \right \rfloor $ 和 $\left \lfloor \frac{y}{d} \right \rfloor $ 的奇偶性分配颜色。

### 本题代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,d,inf=1e5;
char ch[2][2]={{'R','Y'},{'G','B'}};
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin >>n>>m>>d;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)cout <<ch[((i+j+inf)/d)&1][((i-j+inf)/d)&1];
		cout <<"\n";
	}
	return 0;
}

```

---

## 作者：WorldMachine (赞：0)

首先，曼哈顿距离下的“圆”（距离一个点距离相等的点集）是一个斜放的正方形，非常地不好维护。

又注意到切比雪夫距离下的“圆”是一个正放的正方形，非常地好维护。

然后考虑转化坐标系，将点 $(x,y)$ 转化为 $(x+y,x-y)$​，这样就把曼哈顿距离转化成了切比雪夫距离。

> 证明：
>
> 我们有 $|a|+|b|=\max(|a+b|,|a-b|)$（考虑 $a,b$ 的符号异同即得）。因此：
> $$
> |x_1-x_2|+|y_1-y_2|=\max(|(x_1-x_2)+(y_1-y_2)|,|(x_1-x_2)-(y_1-y_2)|)
> $$
> 重新配对得：
> $$
> |x_1-x_2|+|y_1-y_2|=\max(|(x_1+y_1)-(x_2+y_2)|,|(x_1-y_1)-(x_2-y_2)|)
> $$

再把坐标系分成一个个 $d\times d$ 的小矩形，每个矩形染一种颜色，按照分割后的网格坐标奇偶性来涂色即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const char c[] = "RYGB";
int n, m, d;
int main() {
	scanf("%d%d%d", &n, &m, &d);
	for (int i = 1, x, y; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			x = i + j + 1e5, y = i - j + 1e5;
			putchar(c[(x / d & 1) * 2 + (y / d & 1)]);
		}
		putchar('\n');
	}
}
```

---

## 作者：Azazеl (赞：0)

$~~~~$ 对于所有点 $(x,y)$ ，将其坐标变换到 $(x+y,x-y)$ 后，原先两点之间的**曼哈顿距离**等于转换后对应点之间的**切比雪夫距离**。

$~~~~$ 下面给出证明：

$~~~~$ 设：点 $A_1(x_1,y_1),A_2(x_2,y_2)$

$~~~~$ 则 $A_1A_2$ 的曼哈顿距离为：$|x_1-x_2|+|y_1-y_2|$ 。

$~~~~$ 由于绝对值的本质是取正数，即正、负数之间较大一个，因此上式也可以写成：
$$\max\{x_1-x_2+y_1-y_2 \ \ ,\ \  x_1-x_2-y_1+y_2 \ \ ,\ \  x_2-x_1+y_1-y_2 \ \ ,\ \ x_2-x_1+y_2-y_1\}$$

$$=\max\{|(x_1+y_1)-(x_2+y_2)|\ \ ,\ \ |(x_1-y_1)-(x_2-y_2)|\}$$
$~~~~$ 而任意两点之间的切比雪夫距离即横纵坐标差的最大值，故上式表示的即为 $A_1'(x_1+y_1,x_1-y_1)$与 $A_2'(x_2+y_2,x_2-y_2)$ 之间的距离。

$~~~~$ 这样转换的好处是把距离某个点曼哈顿距离相等的点构成的斜着的正方形变为了正着的正方形~~（改斜归正）~~ ，那么转换后每个点不能与之颜色相同的点就会正向围在旁边。

$~~~~$ 此时可得一个构造方案：将整个坐标系分成若干个 $d\times d$ 的正方形，同一个正方形内的点的颜色相同。显然在这样划分时，每一个小点和与之不能染成相同颜色的点在两个不同的大正方形内，因此该题相当于转化为对大正方形染色。而此时的染色方案仅要求每个大正方形的颜色与周围八个方向的不同，可以简单构造出来如下图的方案：

![](https://cdn.luogu.com.cn/upload/image_hosting/wytsjg2l.png)

---

## 作者：qinyubo (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_code_festival_2017_quala_d)

题目大意：给定一个 $H\times W$ 的网格，试给其中所有格子染 `RYGB` 四种颜色之一，使得网格上任意一对曼哈顿距离为 $d$ 的格子颜色不同。

$1\le H,W\le500$

可爱的构造题。

想到曼哈顿距离意义下的圆是一个倾斜 $45^\circ$ 的菱形，可以想到如下的构造：

![](https://cdn.luogu.com.cn/upload/image_hosting/6rvhvziv.png)

其中每个颜色块是一个对角线长为 $d$ 的菱形，这样每两个同一块内的点距离一定不超过 $d-1$，每两个不在同一块内的同色点距离至少是 $d+2$。

但是除非斜着的菱形很好处理，否则它们一定不太好处理。故考虑把曼哈顿距离转成切比雪夫距离，这样染色就变成了这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/ohqmyga0.png)

然后点 $(i,j)$ 的颜色就可以很方便地表示出：$[\left\lfloor\frac id\right\rfloor\text{ is odd}]\times2+[\left\lfloor\frac jd\right\rfloor\text{ is odd}]$。

为了避免负数除法造成的奇怪错误，我给 $i$ 和 $j$ 做了偏移。

代码还是很短的。

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
namespace QYB {
    int main() {
        int n, m, d;
        scanf("%d%d%d", &n, &m, &d);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%c", "RBGY"[((((i + j + 114514) / d) & 1) << 1) | (((i - j + 1919810) / d) & 1)]);
            } printf("\n");
        } return 0;
    }
} int main() {
    return QYB::main();
}
```

---

