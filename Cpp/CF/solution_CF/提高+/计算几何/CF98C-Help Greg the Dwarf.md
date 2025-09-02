# Help Greg the Dwarf

## 题目描述

一个很不寻常的市民住在一个遥远的国度——他是矮人格库拉。然而，他不寻常的名字不是最奇怪的事情（而且，过去的每个人都习惯了只是叫他矮人格雷格），还有一些关于矮人格雷格的一些特殊的事实——他已经活了两百多年，而且，他住在一个废弃墓地的墓穴中，没人见他在白天出来过。此外，也没人见过他给自己买食物。这就是为什么在恶龙悲剧地死亡、牛持续从田野中消失后没人感到特别惊讶。邻里的人们非常确信无害的龙对消失的牛没有责任（考虑到恶龙一直对他的素食主义观点很诚挚）。但是甚至那也不是整个故事的最坏的部分。

最坏的部分是仅仅几分钟前，矮人格雷格用某些难以理解的方式进入了你的房子，并且让你帮他解决一个问题。关键是在很短的一段时间以前，格雷格决定订一口新的棺材（知道他怪异的性格，你一点也不会感到奇怪）。但问题是：一段非常长的双向的L形走廊通向格雷格的墓穴，无法拖着任何一口棺材通过那个走廊，这就是为什么他来寻求你的帮助。

你已经将任务抽象化到了一个这样的平面上：让走廊在转弯前和转弯后的宽度为 $a$ 和 $b$ （如图）。两端走廊相交成一个直角，棺材是一个边长分别为 $l$ 和 $w$ $(l\ge w)$ 的矩形。矮人格雷格已经决定了棺材的长$(l)$，这取决于他的身高；你的任务是决定棺材的最大可能的宽$(w)$，以这样的长和宽棺材可以被带到墓穴里。而且，由于棺材的质量很大（纯大理石！），棺材配备了轮子，因此它不能被抬离地面，但是可以在平面内平移和旋转。在进入走廊之前，你可以任意旋转棺材。

格雷格保证如果你帮助他，他就会奖励你永生（我想知道怎么实现？）。而且如果你不帮助他，嗯……相信我，你不想知道会发生什么的。

一句话题意：给出一个有直角拐角的L形走廊和一个长确定、宽不确定（宽不大于长）的矩形，矩形可以任意平移、旋转，要求求出能够通过拐角的矩形的最大的宽。

## 说明/提示

在第一个样例里答案被棺材的长度限制（请记住——棺材的宽不能大于长）

在第二个样例里，棺材由于用于旋转的轮子可以被运送通过走廊：首先，从一端拖着棺材，直到有墙阻止继续前进，然后垂直于初始移动方向将其向前移到相邻的一侧。（请记住——棺材可以任意平移、旋转）

## 样例 #1

### 输入

```
2 2 1
```

### 输出

```
1.0000000
```

## 样例 #2

### 输入

```
2 2 2
```

### 输出

```
2.0000000```

## 样例 #3

### 输入

```
2 2 3
```

### 输出

```
1.3284271
```

## 样例 #4

### 输入

```
2 2 6
```

### 输出

```
My poor head =(
```

# 题解

## 作者：Thomas0218 (赞：2)

~~水题~~

![](https://cdn.luogu.com.cn/upload/image_hosting/q6zsb78m.png)

于是令 ```f(x) = a*cos(x)+b*sin(x)-l*cos(x)*sin(x)```

枚举求出 $x\in [0,\frac{\pi}{2}]$ 内 $f(x)$ 的最小值即是 $w$

循环时每次增加 $10^{-7}$ 即可。注意特判。

```cpp
#include <bits/stdc++.h>
using namespace std;
const double pi = 3.1415926, eps = 1e-7, inf = 1e12;
int a, b, l; double ans = inf;
double calc(double theta) {
    double _sin = sin(theta), _cos = cos(theta);
    return a * _cos + b * _sin - l * _sin * _cos;
}
int main() {
    scanf("%d%d%d", &a, &b, &l);
    if(l <= a) { printf("%.8lf\n", (double)min(l, b)); return 0; }
    if(l <= b) { printf("%.8lf\n", (double)min(l, a)); return 0; }
    for(double theta = 0; theta <= pi / 2; theta += eps)
        ans = min(ans, calc(theta));
    if(ans < eps) printf("My poor head =(\n");
    else printf("%.8lf\n", ans);
    return 0;
}
```

---

## 作者：Jeefy (赞：1)

# CF98C Help Greg the Dwarf 题解

~~为什么不三分~~？

首先我们考虑如何求出答案。

如图，考虑设夹角为 $\theta$，那么可以得到表达式：

$$
[\frac a {\tan \theta} - (l \cos \theta - b)] \sin \theta
$$

![](https://cdn.luogu.com.cn/upload/image_hosting/46r61tjp.png)

整理可得：

$$
a \times \cos\theta + b \times \sin\theta - l \times \sin \theta \cos \theta
$$

于是可以考虑观察这个函数的单调性：

![](https://cdn.luogu.com.cn/upload/image_hosting/8msrjjuo.png)

明显这是个单峰函数。

考虑合法的大小即是此函数的最小值。

特判掉 $l \le b$ 或者 $l \le a$ 的情况：

- $l \le b \implies w = \min(a, l)$

- $l \le a \implies w = \min(b, l)$

所以考虑三分答案求最小即可。

不过需要判断无解的情况！

> 注意一下 CF 上似乎不能使用 `long double`……亦或是我写法的问题 QwQ

```cpp
#include <stdio.h>
#include <math.h>
#define ldb double

int a, b, l;
ldb calc(ldb theta) {
    ldb c = cos(theta), s = sin(theta);
    return a * s - l * c * s + b * c;
}

int main() {
    scanf("%d %d %d", &a, &b, &l);

    if (l <= b) {
        printf("%.10lf\n", (ldb)(a < l ? a : l));
        return 0;
    }

    if (l <= a) {
        printf("%.10lf\n", (ldb)(b < l ? b : l));
        return 0;
    }

    ldb L = 0, R = acos(-1) / 2;
    const ldb eps = 1e-10;
    while (L + eps < R) {
        ldb ml = (L + L + R) / 3, mr = (L + R + R) / 3;
        ldb vl = calc(ml), vr = calc(mr);
        
        if (vl < vr) R = mr;
        else L = ml;
    }

    ldb ans = calc(L);

    if (l < ans) ans = l;

    if (ans < eps) puts("My poor head =(");
    else printf("%.10lf\n", ans);

    return 0;
}
```




---

## 作者：STDquantum (赞：1)

观察这道题，可以发现是求能够通过拐角的最大的长方形宽。

可以先特判掉一些特殊情况，比如

![](https://gitee.com/stdquantum/STDquantumImages/raw/master/images/1.png)
![](https://gitee.com/stdquantum/STDquantumImages/raw/master/images/2.png)

这种不用旋转就完全能通过的方式。

然后我们再考虑如果一个矩形能够通过，那么一定会倾斜（除去特判掉的情况）。

抽象出这个矩形，如下图

![](https://gitee.com/stdquantum/STDquantumImages/raw/master/images/4.png)

我们考虑如何求出这个矩形的宽（先不用考虑最大）。

我们注意到图中有很多相似三角形，所以可以通过求出$JN$线段的长度来求$JL=JN\sin\alpha$。而$JN$的长度是$ON-OJ=MN\cos\alpha-JI\cos\alpha$，而$MN$的长度可以通过从$A$做$ON$、$OM$的平行线，被走廊截得的线段长度就是$a$和$b$，所以$MN=\frac{a}{\sin\alpha}+\frac{b}{\cos\alpha}$。

一通计算猛如虎啊，这个宽就是$a\cos\alpha+b\sin\alpha-l\sin\alpha\cos\alpha$。

好的求出了一堆奇奇怪怪的带着三角函数的东西，这东西有什么用呢？

我们来看一个样例

```
2 2 3
```

```
1.3284271
```

首先这个函数长这个样子，点是一些最值，两条最粗的线是$x=0$和$x=\frac\pi2$。

因为$\alpha$的取值是$[0,\frac\pi2]$，所以之后我们只关心这个区间内的值。

![](https://gitee.com/stdquantum/STDquantumImages/raw/master/images/5.png)

我们会发现$D$点的位置是最低点，再一查询它的纵坐标，$y=1.33$。GeoGebra保留了两位小数，这不就是答案吗？

再来看一个样例

```
2 2 6
```

```
My poor head =(
```

![](https://gitee.com/stdquantum/STDquantumImages/raw/master/images/6.png)

最低点换了个名字不过这无所谓，会发现它的纵坐标是小于零的，而这个输入也确实无解。这是巧合吗？

肯定不是的。我们求出这个函数，必然有它的意义。我们可以发现，这段区间内对应的函数值就是每个$w$可能的宽度，而函数值最小的时候，正好就是可以取的$w$值最大的时候。因为如果矩形的宽度再小一点，就一定能连边也不蹭地随便通过了。

而观察那些特判的矩形，如这个样例

```
2 2 1
```

```
1.0000000
```

![](https://gitee.com/stdquantum/STDquantumImages/raw/master/images/7.png)

这所有的可能的函数值都不符合条件（不大于$l$，至少得不大于$a$吧）。所以基本可以判定在矩形不旋转就能通过的地方没必要算这个函数了。

于是我们现在的目标变成了求解这个函数的最小值，这玩意要是直接二分，我也不会，所以我们要用一种小学二年级就学了的知识（毕导粉轻喷qwq）——[导数](https://baike.baidu.com/item/导数)。

其实就把这东西理解为 把每一点函数的斜率都求出来，包装成另一个函数 就行。这玩意常用来求什么单调性啊、什么函数最值啊。单调性不解释，用不上；这个最值就可以理解为前面的斜率都是负的，这一点是零，后面的斜率都是正的，这个点就是这个函数的局部最小值，最大值同理。

![](https://gitee.com/stdquantum/STDquantumImages/raw/master/images/8.png)

可以发现在图中（样例为`2 2 3`），导函数为$0$的地方对应了上面函数的最小值。

至于导函数的求法，上面的导数链接里面很全了。

所以就这样特判一下，求一下，再与$l$取$\min$，这题就做完了。

放上完整的AC代码

```cpp
#include <bits/stdc++.h>
#define LOCAL // 为了让本地输入输出文件一直用一套qwq
using namespace std;

namespace STDquantum { // 就是一种防止命名冲突的写法

int a, b, l;
double ans, tmp1, tmp2;
inline double f(double x) { // 原函数
    return -sin(x) * cos(x) * l + cos(x) * a + sin(x) * b;
}
inline double g(double x) { // 导函数
    return sin(x) * sin(x) * l - cos(x) * cos(x) * l +
           cos(x) * b - sin(x) * a;
}
inline void main() {
    scanf("%d%d%d", &a, &b, &l);
    if (a > b) swap(a, b); // 取min方便
    ans = tmp1 = tmp2 = -100; // 防止取min失败
    if (l <= b) { tmp1 = min(a, l); } // 特判
    double L = 0, R = acos(-1) / 2, mid; // acos(-1)就是π
    while (R - L > 1e-7) { // 精度范围内二分导函数零点
        mid = (R + L) / 2;
        if (g(mid) < 0) {
            L = mid;
        } else {
            R = mid;
        }
    }
    tmp2 = f(L); // 对应原函数上的最小的函数值
    ans = max(tmp1, tmp2);
    ans = min(1.0 * l, ans); // 不能超过l
    if (ans < 1e-7) {
        puts("My poor head =(");
    } else {
        printf("%.7lf", ans);
    }
}

}  // namespace STDquantum

int main() {
#ifndef ONLINE_JUDGE
#ifdef LOCAL
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
#ifndef LOCAL
    freopen("CF98C_Help_Greg_the_Dwarf.in", "R", stdin);
    freopen("CF98C_Help_Greg_the_Dwarf.out", "w", stdout);
#endif
#endif
    STDquantum::main();
    return 0;
}
```

感谢GeoGebra和vscode的大力支持。

---

## 作者：梦应归于何处 (赞：0)

### 思路

~~这道题非常的恶心。~~

看到这道题我们可以去画一张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/fwu429dc.png)

图中我们现在要去求 $w$ 那我们想，我们应该怎么求 $w$ 呢？

我们设 $AC$ 长度为 $ac$。

然后我们根据相似三角形的性质就能推出来图中的 $w=\frac{ac\sqrt{l^2-x^2} }{l}$。

我们设 $OA=x$。

然后我们去求 $ac$。可以得到 $ac=b+\frac{ax}{\sqrt{l^2-x^2}}-x$。

最后，经验证，这个函数是一个单峰函数，所以我们去三分。

### 代码

~~~cpp
#include <bits/stdc++.h>
#define db double
#define ll long long
#define ex exit(0)
#define endl "\n"
#define inl inline
#define null NULL
#define mkp(a,b) make_pair(a,b)
using namespace std;
double a, b, l;
double getw(double x) {
	double t = sqrt(l * l - x * x);
	double ac = b + (a * x / t) - x;
	double w = ac * t / l;
	return w;
}
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin >> a >> b >> l;
	if (l <= b) {
		printf("%.10lf\n", (double)(a < l ? a : l));
		return 0;
	}
	if (l <= a) {
		printf("%.10lf\n", (double)(b < l ? b : l));
		return 0;
	}
	double le = 0, ri = l;
	while (fabs(ri - le) >= 0.000000001) {
		double mid1 = le + (ri - le) / 3.0, mid2 = le + (ri - le) / 3.0 * 2.0;
		if (getw(mid1) >= getw(mid2)) {
			le = mid1;
		} else {
			ri = mid2;
		}
	}
	if (getw(le) <= 0.0000000001) {
		cout << "My poor head =(";
		return 0;
	}
	printf("%.10lf", getw(le));
	return 0;
}
~~~

---

