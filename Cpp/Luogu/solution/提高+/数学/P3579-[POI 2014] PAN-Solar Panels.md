# [POI 2014] PAN-Solar Panels

## 题目描述

对于 $n$ 组询问，每组询问给定四个整数 $a,b,c,d$，从区间 $[a,b]$ 和 $[c,d]$ 中任意选取两个整数 $x$ 和 $y$，求 $\gcd(x,y)$ 的最大值是多少。

## 说明/提示

### 数据规模与约定

对于 $100\%$ 的数据，$1 \le n \le 1000$，$1 \le a \le b \le 10^9$，$1 \le c\le d \le 10^9$。

### 说明

Translated by @一只书虫仔。

## 样例 #1

### 输入

```
4
3 9 8 8
1 10 11 15
4 7 22 23
2 5 19 24
```

### 输出

```
8
7
2
5
```

# 题解

## 作者：TwoJie (赞：14)

一般的数论分块是求商相同的时候的区间贡献，然后就容易进入一种固定思维，就是我必须要统计完这个区间的所有信息，就会忽略一些题目本身的性质。

回到题目本身，首先可以发现一个性质（实际上这个性质是简化版的，我当时推出来的式子要复杂一点）：

如果区间 $(l,r]$ 存在 $x$ 的倍数，那么需要满足 $\lfloor \frac{l}{x} \rfloor < \lfloor \frac{r}{x} \rfloor$ 。

那么我们考虑枚举答案 $i$ ，对于答案 $i$ ，如果它满足上面的式子，那么这个 $i$ 就是合法的。

根据数论分块套路，我们可以改为枚举 $\frac{b}{i}$ 的商  $x$ ，那么这个 $x$ 必定对应着一个区间，而我们想要答案尽量大，就会想要取这个区间最大的那个，也就是 $x$ 尽量大。

代回上面那个约束条件，我们发现因为是枚举商，所以 $\lfloor \frac{r}{x} \rfloor$ 的值是不变的，我们再看左边的那个式子，发现 $x$ 越大， $\lfloor \frac{l}{x} \rfloor$ 越小，那么这个约束条件就越容易满足。

实际上这就是这道题隐藏的贪心性质，发现之后就简单了。

---

## 作者：panyf (赞：10)

不算困难的数学题，稍微推推式子就出来了，代码十分简短

考虑两个数x,y(x<=y)，任取一个数k满足k<=y，设t=y / k * k，则t即为不大于y的最大的k的倍数，若满足x<=t，则x,y之间存在k的倍数。

回到本题，设m=min(smax,wmax)，任取一个数k满足k<=m，设p=smax / k * k，q=wmax / k * k，若满足smin<=p且wmin<=q，则k为候选答案之一。

此时便形成思路：枚举不大于m的所有正整数，一一进行判断，输出符合要求的最大的数。

然而这样做时间复杂度O(nm)，明显需要继续优化，此时我们注意到对于一些连续的k，y/k的值可能相等，此时只需判断这些k中的最大值即可，时间复杂度降为O(n* sqrt(m))，能够通过本题。

只有2行的核心代码+注释：
```cpp
for(int i=1;i<=m;i++){
	i=min(b/(b/i),d/(d/i));//优化，只考虑b/i和d/i值都相等的数中最大的一个
	if(b/i*i>=a&&d/i*i>=c)s=i;//判断是否符合条件，更新答案
}
```


---

## 作者：一只书虫仔 (赞：8)

upd on 2020.6.12 修正了 Sol2 里的一处笔误，不是 $[l,r]$ 应该是 $(l,r]$

---

[P3579 [POI2014]PAN-Solar Panels](https://www.luogu.com.cn/problem/P3579)

### Description

给定 $l_1,r_1,l_2,r_2$，求在 $[l_1,r_1]$ 和 $[l_2,r_2]$ 中选择两个数 $i,j$ 他们的 $\gcd$ 的最大值。

### Solution 1

傻傻的我打了个暴力

```cpp
#include <bits/stdc++.h>

using namespace std;

int gcd (int a, int b) {return b == 0 ? a : gcd(b, a % b);}

int main () {
	int t;
	scanf("%d", &t);
	while (t--) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		int Max = -1;
		for (int i = a; i <= b; i++)
			for (int j = c; j <= d; j++)
				Max = max(gcd(i, j), Max);
		printf("%d", Max);
	} 
	return 0;
}
```

[Record](https://www.luogu.com.cn/record/34210233)，肯定全 T

期望得分：$0$ 分

### Solution 2

我从 GXZlegend 巨佬的博客 [Link](https://www.cnblogs.com/GXZlegend/p/7434565.html) 得知了一个结论

> 如果区间 $(l,r]$ 想出现 $k$ 的倍数，需要 $\left\lfloor\dfrac{l}{k}\right\rfloor<\left\lfloor\dfrac{r}{k}\right\rfloor$。

然后这就很简单了吧 ……   
直接枚举即可

```cpp
#include <bits/stdc++.h>

using namespace std;

int main () {
	int T;
	scanf("%d", &T);
	while (T--) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		int Max = -1, tmp = 0;
		for (int i = 1; i <= b && i <= d; i = min(b / (b / i), d / (d / i)) + 1)
			if (b / min(b / (b / i), d / (d / i))  > (a - 1) / min(b / (b / i), d / (d / i)) && d / min(b / (b / i), d / (d / i)) > (c - 1) / min(b / (b / i), d / (d / i))) 
				Max = min(b / (b / i), d / (d / i));
		printf("%d\n", Max);
	}
	return 0;
}

```

评测记录：[Link](https://www.luogu.com.cn/problem/P3579)   
期望得分：$80$ 分   
但是，我们开 $O2$ 就可以 [A 掉这道题](https://www.luogu.com.cn/record/34211556)   
~~不过这不行，这太野蛮了，我无法忍受你的行为~~

### Solution 3

方法：枚举 $[1,\min(b,d)]$ 的所有正整数 $i$，看看是否可以满足
$$a \le \dfrac{b}{i^2}\text{ and }c \le \dfrac{d}{i^2}$$
即可

所以代码就出来啦！

```cpp
#include <bits/stdc++.h>

using namespace std;

int main () {
	int T;
	scanf("%d", &T);
	while (T--) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		int Max = -1;
		for (int i = 1; i <= min(b, d); i++)
			if (a <= (b / i * i) && c <= (d / i * i))
				Max = i;
		printf("%d\n", Max); 
	}
	return 0;
}

```

评测记录：[Link](https://www.luogu.com.cn/record/34211829)   
期望得分：$10$ 分  
纳，纳尼？  
为啥才 $10$ 分捏 qwq  
因为这时间复杂度不行啊  
所以我们需要再次优化

### Solution 3.5

这里参考了 AK新手村 大佬的 [题解](https://www.luogu.com.cn/blog/221955/solution-p3579)

本来我也不知道的   
我看了 AK新手村 大佬的题解才知道   
需要的优化和 Solution 1 的几乎一毛一样   
即

> 只考虑 $\dfrac{b}{i}$ 和 $\dfrac{d}{i}$ 值都相等的数中最大的一个

代码在 AK新手村 大佬那里都有了   
去看就可以

期望得分：$100$ 分

---

参考资料：

- Solution 1：None
- Solution 2：[Link](https://www.cnblogs.com/GXZlegend/p/7434565.html)
- Solution 3 & 3.5：[Link](https://www.luogu.com.cn/blog/221955/solution-p3579)

---

## 作者：喵の耳 (赞：7)

来源：https://www.cnblogs.com/GXZlegend/p/7434565.html

作者：[GXZlegend](https://www.cnblogs.com/GXZlegend/)

我只是题解的搬运工QAQ



------------
数论

结论：区间(l,r]中出现n的倍数的充要条件是⌊r/n⌋>⌊l/n⌋。

于是可以枚举i，看是否在两段区间内都出现过。可以通过枚举商将时间复杂度将至O(n√a)。

注意在枚举商的时候要使用最后一个商与b/i和d/i相等的last值计算。



------------
code
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int main()
{
    int T , a , b , c , d , i , last , ans;
    scanf("%d" , &T);
    while(T -- )
    {
        scanf("%d%d%d%d" , &a , &b , &c , &d);
        for(i = 1 ; i <= b && i <= d ; i = last + 1)
        {
            last = min(b / (b / i) , d / (d / i));
            if(b / last > (a - 1) / last && d / last > (c - 1) / last) ans = last;
        }
        printf("%d\n" , ans);
    }
    return 0;
}
```


---

## 作者：HYdroKomide (赞：5)

看题解区的大佬们的题解都有些看不懂，所以补一发。希望大家都能看懂。参考题解区前三篇的思路。
### 题意：
求两区间内任意两个数 $x,y$ 的最小公倍数（$\gcd$）的最大值。

### 思路：
思路有一定难度，~~但绝对到不了紫题吧~~。

暴力模拟在 $a,b,c,d \le 10^9$ 的情况下必挂。所以考虑枚举一个可以同时整除 $x,y$ 的 $p$。

那么我们需要考虑怎样使枚举 $p$ 得出的 $x$ 和 $y$ 分别位于 $[a,b],[c,d]$ 这两个区间内。于是我们构造 $x,y$，使它们成为仅次于 $b,d$ 的 $p$ 的倍数，即 $x=p\lfloor \dfrac{b}{p} \rfloor$，$y=p\lfloor \dfrac{d}{p} \rfloor$。

构造好后我们判断 $x,y$ 是否在区间内即可。

但是直接暴力枚举还是过不了，我们只能试着减少循环次数。

我们发现当 $\lfloor \dfrac{b}{p} \rfloor=\lfloor \dfrac{b}{p+1} \rfloor$ 且 $\lfloor \dfrac{d}{p} \rfloor=\lfloor \dfrac{d}{p+1} \rfloor$ 时，无论 $p$ 取 $p$ 还是 $p+1$，原式都会成立，所以我们直接取最大值就行了。
### 关键程序如下：
```cpp
inline int solve(int a,int b,int c,int d){
	int ret;
	for(ri p=1;p<=min(b,d);p++){
		p=min(b/(b/p),d/(d/p));
		int x=b/p*p,y=d/p*p;
    	if(x>=a&&y>=c)ret=p;
	}
	return ret;
}
```

### THE END

---

## 作者：LittleMoMol (赞：2)

# P3579 题解
## 前言
感觉大部分题解讲的不是很清楚，在 $haosen$ 的讲解中，我才会了这道题……

[更差的阅读体验](https://www.cnblogs.com/LittleMoMol-kawayi/p/LuoGu_solution_P3579.html)

## 思路

看到数据范围，线性必然超时，那么复杂度一般就为 $O(\log n)$ 或者 $O(\sqrt{n})$，又看到这是一个数学题，心里应该有暗示，可能会用到整数分块。

不过第一件事总是：挖掘性质！

你会发现，对于任意一个数 $x$，如果 $a \sim b$ 中存在一个数是 $x$ 的倍数，且 $c \sim d$ 中存在一个数是 $x$ 的倍数，那么 $x$ 就为一个合法的答案，但可能不是最优的。这个比较简单，就不赘述了。

那就直接枚举答案 $x$，从 $1$ 到 $\min(b,d)$ 枚举，逐个判断 $x$ 合不合法，取最大值。

显然这样做是超时的。

其实如果 $x$ 是合法的，只需要满足：

$$
\begin{cases}
 \left\lfloor \dfrac{b}{x} \right\rfloor - \left\lfloor \dfrac{a-1}{x} \right\rfloor \ge 1 \\
 \left\lfloor \dfrac{d}{x} \right\rfloor - \left\lfloor \dfrac{c-1}{x} \right\rfloor \ge 1
\end{cases}
$$

为什么？我们就拿第一个不等式举例子：$\left\lfloor \dfrac{b}{x} \right\rfloor$ 表示 $1 \sim b$ 中有几个数是 $x$ 的倍数，同理，$\left\lfloor \dfrac{a-1}{x} \right\rfloor$ 表示 $1 \sim a-1$ 中有几个数是 $x$ 的倍数。两式相减，就得到了 $a \sim b$ 中有几个数是 $x$ 的倍数，只要有一个数是 $x$ 的倍数，就满足答案。第二个不等式同理。

我们还是拿第一个不等式为例，进行化简：

$\left\lfloor \dfrac{b}{x} \right\rfloor - \left\lfloor \dfrac{a-1}{x} \right\rfloor \ge 1 \Rightarrow \left\lfloor \dfrac{b}{x} \right\rfloor \ge 1 + \left\lfloor \dfrac{a-1}{x} \right\rfloor \Rightarrow \left\lfloor \dfrac{b}{x} \right\rfloor > \left\lfloor \dfrac{a-1}{x} \right\rfloor$

接下来，我认为是最难的一步，考虑 $\left\lfloor \dfrac{b}{x} \right\rfloor > \left\lfloor \dfrac{a-1}{x} \right\rfloor$ 还能怎么化简。

如果我们把除以 $x$ 得到的商相等的所有数都合并成一个块儿，并把每个块儿按顺序编号，那么这个式子就表示 $b$ 所在的块的编号要**严格大于** $a-1$ 所在的块。

式子就**可以**变成这样：$x\left\lfloor \dfrac{b}{x} \right\rfloor > a-1$ 

为啥要变成这样？方便整数分块！现在只需要对 $\left\lfloor \dfrac{b}{x} \right\rfloor$ 整数分块就行哩~

最后的最后，要满足的条件其实就变成了：

$$
\begin{cases}
 x\left\lfloor \dfrac{b}{x} \right\rfloor > a-1\\
 x\left\lfloor \dfrac{d}{x} \right\rfloor > c-1
\end{cases}
$$

## Code

```cpp
#include <iostream>

using namespace std;

int T; 
int a, b, c, d, ans;

int main()
{
	cin >> T;
	while (T -- )
	{
		cin >> a >> b >> c >> d;
		for (int L = 1, R = 1; L <= min(b, d); L = R + 1)
		{
			R = min(b / (b / L), d / (d / L));
			if (R * (b / R) > a - 1 && R * (d / R) > c - 1) ans = R;
		}
		cout << ans << endl;
	}
	return 0;
}
```

## 总结

先明确大方向，再进行分析，最后优化。

完结撒花！


---

## 作者：白简 (赞：1)


> 区间 $\left( l,r \right]$ 中存在 $n$ 的倍数的充要条件是 $\left\lfloor \frac{r}{n}\right\rfloor > \left\lfloor \frac{l}{n}\right\rfloor$。

**证明**：记有整数 $k$ 满足 $k \times n \in \left( l,r \right]$。

那么有

$$\displaystyle l < k \times n \leqslant r \Longleftrightarrow \dfrac{l}{n} < k \leqslant \dfrac{r}{n} \Longleftrightarrow \left\lfloor \frac{l}{n}\right\rfloor < \left\lfloor \frac{r}{n}\right\rfloor$$

证毕。

记 $\gcd(x,y)=k$，我们可以枚举 $k$，因为 $a \leqslant x \leqslant b$，所以我们可以枚举 $k$。

但暴力枚举 $k$ 肯定是会超时，那我们就用**整除分块**优化。

没学过整除分块可以看[这个](https://www.luogu.com.cn/blog/baijian0212/zheng-chu-fen-kuai-xue-xi-bi-ji)。
#### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
int a,b,c,d;
int last,ans;

int main() {
#ifdef ONLINE_JUDGE == 1
    freopen("melina.in","r",stdin);
    freopen("melina.out","w",stdout);
#endif
    cin >> n;
    for(int t = 1;t <= n; t++) {
        cin >> a >> b >> c >> d;

        for(int i = 1;i <= b && i <= d; i = last + 1) {
            last = min(d / (d / i),b / (b / i));
            // 整除分块的右端点，实际是范围内的最大值 
            if(b / last > (a - 1) / last && d / last > (c - 1) / last)
                ans = last;// 利用性质 
        }

        cout << ans << "\n";
    }
#ifdef ONLINE_JUDGE == 1
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
```

---

## 作者：User_Unauthorized (赞：1)

## 题意
给定两个区间 $\left[a, b\right],\left[c, d\right]$，求 $\max\limits_{x \in \left[a, b\right], y \in \left[c, d\right]} \gcd(x, y)$，多测。

（$1 \le n \le 1000, 1 \le a \le b \le 10^9, 1 \le c \le d \le 10^9$）

## 题解

首先考虑一个结论：$\exist kx \in \left(l, r\right] \Leftrightarrow \left\lfloor\dfrac{l}{x}\right\rfloor < \left\lfloor\dfrac{r}{x}\right\rfloor$。证明考虑转化左式

$$l < kx \leqslant r \Leftrightarrow \dfrac{l}{x} < k \leqslant \dfrac{r}{x}$$

因为有 $k \in \mathbb{Z} $，那么可以得出

$$\left\lfloor\dfrac{l}{x}\right\rfloor < k \leqslant \left\lfloor\dfrac{r}{x}\right\rfloor \Leftrightarrow \left\lfloor\dfrac{l}{x}\right\rfloor < \left\lfloor\dfrac{r}{x}\right\rfloor$$

那么我们可以考虑枚举 $\left\lfloor\dfrac{b}{x}\right\rfloor$ 和 $\left\lfloor\dfrac{d}{x}\right\rfloor$ 的值，根据整除分块的结论，可以得出值的总数是 $\sqrt{d}$ 数量级的，可以通过本题。考虑钦定  $\left\lfloor\dfrac{b}{x}\right\rfloor$ 和 $\left\lfloor\dfrac{d}{x}\right\rfloor$ 的值后，$x$ 的取值是一个区间，我们应当取这个区间的右端点，即最大值。证明可以考虑因为我们要做的是判定这个区间里是否存在 $x$，使得 $\left\lfloor\dfrac{l}{x}\right\rfloor < \left\lfloor\dfrac{r}{x}\right\rfloor$，且 $\left\lfloor\dfrac{r}{x}\right\rfloor$ 的值是钦定的，考虑最小化 $\left\lfloor\dfrac{l}{x}\right\rfloor$ 的值，即使 $x$ 取得最大值。换句话说，若区间存在满足条件的 $x$，那么区间右端点一定符合要求，若区间右端点不符合要求，那么整个区间一定都不符合要求，所有我们贪心地判定区间右端点即可。

## Code
```cpp
#include <bits/stdc++.h>

typedef int valueType;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType a, b, c, d;

        std::cin >> a >> b >> c >> d;

        --a;
        --c;

        valueType const end = std::min(b, d);
        valueType l = 1, r, ans = 1;

        while (l <= end) {
            r = std::min(b / (b / l), d / (d / l));

            if (b / r > a / r && d / r > c / r)
                ans = r;

            l = r + 1;
        }

        std::cout << ans << '\n';
    }

    std::cout << std::flush;
}
```

---

## 作者：AbsMatt (赞：1)

## [题目传送器](https://www.luogu.com.cn/problem/P3579)

# 分析

首先，这就是一道数学题（~~但我做了很久才做出来~~）

### 结论

先取三个数 $x$ 和 $y$ 和 $k$ ($x \le y$ 且 $k \le y$)，令 $a={y\div}k \times k $，则 $a$ 为小于等于 $y$ 中最大的 $k$ 的倍数，若满足 $a \ge x$，则 $x,y$之间存在 $k$ 的倍数。

回到本题，设两个数 $a$ 和 $b$，任取一个数 $k$ 满足 $k \le a$ 且 $k \le b$，设 $p={a\div} k \times k$，$q={b \div} k \times k$，若满足 $b \le p$ 且 $a \le q$，则 $k$ 为一种合法答案。

最后只要把一个个 $k$ 算出来再取最大值就行了，时间复杂度也就是 $O(n \times \sqrt m)$

# 代码

```cpp
#include<bits/stdc++.h>  // 开始了
using namespace std;
int q,a,b,c,d;
int main(){
	scanf("%d",&q); //输入
	while(q--){
		scanf("%d%d%d%d",&a,&b,&c,&d); //输入
		int ans=0,now=0;
		for(int i=1;i<=min(b,d);i=now+1){
			now=min(b/(b/i),d/(d/i));
			if((b/now)>(a-1)/now&&(d/now)>(c-1)/now)	ans=now;  // 结论
		}
		printf("%d\n",ans);  //结束
	}
    return 0;  //拜拜
}
```

---

## 作者：jijidawang (赞：0)

不难发现 $[l,r]$ 中存在 $d$ 的倍数当且仅当 $\lfloor\frac rd\rfloor\cdot d\ge l$，那么也就是 $\lfloor\frac rd\rfloor\ge\lceil\frac ld\rceil$。

从而对于 $[a,b],\ [c,d]$ 存在一对数的 GCD 是 $k$ 的倍数当且仅当：
$$\begin{cases}\lfloor\tfrac bk\rfloor\ge\lceil\tfrac ak\rceil\\\lfloor\tfrac ck\rfloor\ge\lceil\tfrac dk\rceil\end{cases}$$

对于 $k$ 来说，二元组 $(\lfloor\tfrac bk\rfloor,\lfloor\tfrac dk\rfloor)$ 只有 $O(\sqrt{\max\{b,d\}})$ 种取值，整除分块处理后判断是否满足不等式即可，时间复杂度 $O(\sqrt{\max\{b,d\}})$，可以通过。

核心代码：
```cpp
scanf("%d%d%d%d", &a, &b, &c, &d);
int ans = 0;
for (int l=1, r; l<=min(b, d); l=r+1)
{
	r = min(b/(b/l), d/(d/l));
	if ((b / r * r >= a) && (d / r * r >= c)) chkmax(ans, r);
}
printf("%d\n", ans);
```

---

## 作者：_Fontainebleau_ (赞：0)

### 题意

- 多组测试数据。
- 给定 $a,b,c,d$。$x,y$ 满足 $x\in[a,b],y\in[c,d]$，求 $\gcd(x,y)$ 的最大值。
- $1\le a\le b\le 10^9,1\le c\le d\le 10^9$。

### 做法

记 $\gcd(x,y)=k$。

枚举 $k$。因为 $a \le x\le b$，所以 $x$ 最多取到 $k\left\lfloor\frac bk\right\rfloor$，如果 $k\left\lfloor\frac bk\right\rfloor<a$ 就不行了。

如果你暴力枚举 $k$，时间复杂度是 $O(nm)$ 的，$\color{Midnightblue} \text{TLE}$ 无疑。怎么办？

**整除分块！**

我们发现因为是向下取整，所以必然会出现 $\left\lfloor \frac bk\right\rfloor=\left\lfloor\frac b{k+1}\right\rfloor$ 的情况。此时取 $k+1$ 显然都满足 $(k+1)\left\lfloor\frac b{k+1}\right\rfloor\le b$，并且更有可能 $\ge a$。又因题目里要求最大值，所以我们可以直接取到 $k+1$。

此时我们直接整除分块即可。复杂度是 $O(n\sqrt m)$ 的。

### 代码

给出关键部分

```c++
int a=read(),b=read(),c=read(),d=read(),res;
for(int i=min(b,d);i>=1;)
{
	int x=b/i*i,y=d/i*i;
	if(x>=a&&y>=c)
	{
		printf("%d\n",i);break;
	}
	i=max(b/(b/i+1),d/(d/i+1));
}
```





---

## 作者：RNTBW (赞：0)

### PART 0

考试题。

全机房没人做出来。

## PART 1

题意没什么好解释。

## PART 2

下文设小写的 $a$ 为 $\gcd$。

我们可以把式子化为如下形式：

$\begin{cases} A\le pa\le B \\ C\le qa\le D \end{cases}$

考虑对 $B$ 整除分块，枚举 $p$，得到 $a$ 的某个范围。

之后由于我们求得的是 $a$ 的某个范围，所以我们还要判断范围内是否存在一个 $a$ 满足 $C\le qa\le D$ 且 $A\le pa$。

考虑像 $B$ 一样再套一个整除分块，对于 $D$ 枚举 $q$，得到 $a$ 更细的某个范围。

贪心一下，每次选择范围内 $a$ 的最大值 $\max_a$。

判断 $\max_a$ 是否满足 $C\le qa,A\le pa$ 即可。如果 $\max_a$ 都不满足，那么范围里剩下其他更小的 $a$ 肯定也不满足。

注意边界判断。

## PART 3

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b,c,d,i,k,s,now,ans;
int get(int l,int r,int a,int b,int d,int c)
//dq>=c!!
//这里的c,d和讲解的不一样，注意一下qwq
{
	int p=a,q=0,ans=0;
	if(a>r)return 0;
	for(;q<b&&q<r;p=q+1)
	{
		q=min(b,r/(r/p));//此时r/p=上文讲解中的q，但是特判
		if(d*q<c)continue;//判断pa>=A
		if((r/p)*q>=l)ans=max(ans,q);//判断qa>=C
	}
	return ans;
}
int main()
{
	scanf("%d",&t);
	//k:左 s:右
	while(t--)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		k=1;ans=s=0;
		for(;s<b;k=s+1)//枚举a区间
		{
			s=b/(b/k);//此时b/k=上文讲解中的p
			ans=max(ans,get(c,d,k,s,b/k,a));
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：renhao (赞：0)

# Solar Panels

$ans=max(gcd(x,y))~~~~~~~\forall~x~\in [L1,R1]~y~\in~[L2,R2]$

#### 暴力
$\Theta((R1-L1)*(R2-L2))$

直接枚举

#### 怎么优化

似乎没有什么办法。
考虑一下 $ans$ 的取值
可以发现这等价于 

$(L1-1)/ans<(R1/ans)$
and
$(L2-1)/ans<(R2/ans)$

可以发现 ans 取一些连续的值的时候对于不等式两边没有影响。

确实

$\huge \lfloor \frac{a}{b} \rfloor$
的取值只有 $ \sqrt a $ 种，

因为在 $ b \le \sqrt a $的时候最多有 $\sqrt a$个$b$,所以最多有 $\sqrt a$个结果

在$b \ge \sqrt a$ 的时候 $\lfloor \frac{a}{b} \rfloor \le \sqrt a$
这显然也有 $\sqrt a$ 个结果

所以$\lfloor \frac{a}{b} \rfloor $最多能取 $2 \times \sqrt a$种值

#### ans 在 约束不等式 取值相同的时候有很多值，那该取哪个值保证合法且最优呢

显然对于一在不等式取值边界的 $ans$ 可以把它+1 ，它一定是合法的，并且+1 后答案会更优

所以只用枚举每个除出来的值，然后再反推边界，这些边界一定有最优答案。

```cpp
		for(int i=1;i<=max(max(max(A,B),C),D);i++){
			if((a-1)/i<b/i&&(c-1)/i<d/i) Max(ans,i);
			if(((a-1)/i)&&(a-1)/((a-1)/i)<b/((a-1)/i)&&(c-1)/((a-1)/i)<d/((a-1)/i)) Max(ans,(a-1)/i);
			if((b/i)&&(a-1)/(b/i)<b/(b/i)&&(c-1)/(b/i)<d/(b/i)) Max(ans,(b/i));
			if(((c-1)/i)&&(a-1)/((c-1)/i)<b/((c-1)/i)&&(c-1)/((c-1)/i)<d/((c-1)/i)) Max(ans,(c-1)/i);
			if((d/i)&&(a-1)/(d/i)<b/(d/i)&&(c-1)/(d/i)<d/(d/i)) Max(ans,(d/i));
		}
```

---

## 作者：夏色祭 (赞：0)

没人发题解吗。。。

首先可以想到如果存在gcd(x,y)=k，那么就一定要满足b/k>(a-1)/k&&d/k>(c-1)/k。

而n/k的k取法只有√n种，直接枚举即可。

具体代码见我的博客:http://www.cnblogs.com/zykykyk/p/8721568.html

---

