# Forecast

## 题目描述

The Department of economic development of IT City created a model of city development till year 2100.

To prepare report about growth perspectives it is required to get growth estimates from the model.

To get the growth estimates it is required to solve a quadratic equation. Since the Department of economic development of IT City creates realistic models only, that quadratic equation has a solution, moreover there are exactly two different real roots.

The greater of these roots corresponds to the optimistic scenario, the smaller one corresponds to the pessimistic one. Help to get these estimates, first the optimistic, then the pessimistic one.

## 样例 #1

### 输入

```
1 30 200
```

### 输出

```
-10.000000000000000
-20.000000000000000```

# 题解

## 作者：Strelitzia_ (赞：3)

### 题目大意

给出 $a,b,c$，求一元二次方程 $ax^2+bx+c=0$ 的解。保证有两个不相等的实数根。

------------
### 解法

一元二次方程的判别式：设 $\Delta =\mathop{{b}}\nolimits^{{2}}-4ac$，那么：

$$\left\{\begin{matrix} 
  \Delta \gt 0 & \text{方程有两个不相等的实根} \\ 
  \Delta = 0 & \text{方程有两个相等的实根} \\ 
  \Delta \lt 0 & \text{方程没有实数解} 
\end{matrix}\right. $$

不过这道题保证了有两个不相等的实数根，就不用判断了。然后就是求根公式：

$$\begin{cases}
x_1=\dfrac{-b+\sqrt[]{\Delta} }{2a}  \\
x_2=\dfrac{-b-\sqrt[]{\Delta} }{2a}
\end{cases}$$

我们把所有变量开成 `double`，扔到公式里面计算即可。最后比较大小，先输出大的根。代码如下：

```cpp
double a,b,c,delta,sol1,sol2; 
signed main(){
	cin>>a>>b>>c;
	delta=sqrt(b*b-4*a*c);
	sol1=(-b+delta)/(2*a),sol2=(-b-delta)/(2*a);
	if(sol1<sol2) swap(sol1,sol2);//比较大小
	printf("%.12lf\n%.12lf\n",sol1,sol2);
	return 0;
}
```

---

## 作者：charleshe (赞：2)

解一元二次方程的模板题，一元二次方程求根公式[在这里](https://baike.baidu.com/item/%E4%B8%80%E5%85%83%E4%BA%8C%E6%AC%A1%E6%96%B9%E7%A8%8B%E6%B1%82%E6%A0%B9%E5%85%AC%E5%BC%8F/56066624)。求根公式代码注释里也有。

套入求根公式，这题就很简单了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    double a,b,c;
    cin>>a>>b>>c;
    double x1=(-b+sqrt(pow(b,2)-4*a*c))/(2*a);//利用求根公式求出两根。求根公式：有一ax²+bx+c=0的方程，其两根为：(-b±√(b²-4ac))/(2a)。由于数据保证存在两根，所以直接带入。
    double x2=(-b-sqrt(pow(b,2)-4*a*c))/(2*a);
    if(x1<x2) printf("%.10lf\n%.10lf",x2,x1);//比较大小后输出（貌似不比较也行欸）
    else printf("%.10lf\n%.10lf",x1,x2);
    return 0;
}
```


---

## 作者：Natori (赞：0)

~~初三菜鸡前来报到~~

最近学校数学学到第二章《一元二次方程》，刚从讨论区里发现这题，切掉之后索性来写篇题解，讲一下一元二次方程的相关内容，~~顺便复习一下whk~~。

~~如果不过审的话就当做中考复习资料了~~

## 一、一元二次方程的定义

一个整式方程**经过整理后**，如果只含 $1$ 个未知数，且未知数最高项的次数是 $2$，则称这个方程是**一元二次方程**。

其中，**整式方程**指的是等号两边都是关于**未知数的整式**的方程。

一般地，定义一元二次方程的**一般形式**为：

$$ax^2+bx+c=0(a \not= 0)$$

在上面的式子中，$a,b,c$ 分别被称作这个一元二次方程的**二次项系数、一次项系数和常数项**。

举几个反面教材：

- $ax^2+bx+c=0$ 不是一个一元二次方程

没有规定 $a \not= 0$（注意，$b,c$ 是可以等于 $0$ 的）。

- $2x^2+5x-1=(2x-1)(x+4)$ 不是一个一元二次方程

判断是否为一元二次方程应先整理原方程变为一般形式。

原方程的一般形式是 $-2x+3=0$，二次项系数为 $0$。

- $x^2 + \dfrac{1}{x}=0$ 不是一个一元二次方程

等号左边不是一个整式。

## 二、一元二次方程的解法

需要明确的是，一元二次方程可能**无实数根**（不是无解）。

### （一）配方法

前置知识：完全平方公式，即 $(a\pm b)^2=a^2 \pm 2ab +b^2$。

配方法用举例来理解比较好。

- 求解方程 $x^2-6x+3=0$

把常数项拆开，使原方程更容易配方：

$$x^2-6x+9-6=0$$

移项：

$$x^2-6x+9=6$$

把等式左边的式子配方：

$$(x-3)^2=6$$

直接开平方：

$$x-3= \pm \sqrt{6}$$

移项，得到原方程的解：

$$x_1=3+\sqrt{6},x_2=3-\sqrt{6}$$

在配方法中，将等号左边的式子配成完全平方式后，如果右边的数小于 $0$，那么就可以判定原方程无实数根。

原因很简单，直接开平方时会给等号右边套一层根号，开根号的值必须不小于 $0$。

### （二）公式法

公式法可以理解为从配方法加以总结得到的。

考虑从一元二次方程的一般形式下手：

- $ax^2+bx+c=0(a\not = 0)$

首先将原方程等号两边同除以 $a$，得：

$$x^2+\dfrac{b}{a}x+\dfrac{c}{a}=0$$

配方：

$$x^2+\dfrac{b}{a}x+(\dfrac{b}{2a})^2+\dfrac{c}{a}-(\dfrac{b}{2a})^2=0$$

$$(x+\dfrac{b}{2a})^2-\dfrac{b^2-4ac}{4a^2}=0$$

移项并开平方：

$$(x+\dfrac{b}{2a})^2=\dfrac{b^2-4ac}{4a^2}$$

$$x+\dfrac{b}{2a}=\pm \sqrt{\dfrac{b^2-4ac}{4a^2}}$$

$$x+\dfrac{b}{2a}=\pm \dfrac{\sqrt{b^2-4ac}}{2a}$$

移项，得到原方程的两根：

$$x=\dfrac{-b \pm \sqrt{b^2-4ac}}{2a}$$

不难发现原方程有实数根的充要条件是 $b^2-4ac \ge 0$，

于是，人们记 $\Delta=b^2-4ac$，并把 $\Delta$ 称为一元二次方程的**判别式**，用以判断方程是否有实数根。

所以，可以得到一元二次方程的**求根公式**：

$$x_1=\dfrac{-b+\sqrt{\Delta}}{2a},x_2=\dfrac{-b-\sqrt{\Delta}}{2a}$$

其中，$\Delta=b^2-4ac$。

一个一元二次方程有实数根，当且仅当 $\Delta=b^2-4ac\ge 0$。

由此，容易得到一元二次方程**实数根数量**的判断方法：

- 若 $\Delta<0$，则原方程**无实数根**；

- 若 $\Delta=0$，则原方程**有 $2$ 个相等的实数根**；

- 若 $\Delta>0$，则原方程**有 $2$ 个不相等的实数根**。

### （三）十字相乘法

前置知识：[因式分解](https://baike.baidu.com/item/%E5%9B%A0%E5%BC%8F%E5%88%86%E8%A7%A3/384402?fr=aladdin)

对于二次三项式 $mx^2+rx+n(m,n,r \in \text{N})$，若存在 $a,b,c,d \in \text{N}$，使得 $ad+bc=r$，则原式可以写作 $(ax+c)(bx+d)$。

举个例子：

$$\begin{aligned}& 2x^2-7x+5 \\ & = 2x \times x-2x-5x+(-5)\times(-1) \\ & = (x-1)(2x-5)\end{aligned}$$

注意，并不是每一个二次三项式都可以十字相乘。

回到正题，对于一元二次方程 $ax^2+bx+c=0(a \not= 0)$，若其可以因式分解为：
$$(mx+n)(rx+k)=0$$

因为若 $pq=0$，则 $p=0$ 或 $q=0$，所以容易得到原方程的两根：

$$x_1= - \dfrac{n}{m},x_2= -\dfrac{k}{r}$$

值得一提的是，如果原方程无实数解，那么它一定无法十字相乘。

## 关于本题

~~终于扯到正题上了~~

[再看一眼题](https://www.luogu.com.cn/problem/CF630N)，免得忘了要干啥。

题目中只给出了一元二次方程的三个系数，所以直接代求根公式即可。

平时解一元二次方程的时候要注意判无实数根，但本题中不需要，因为题面保证了方程有实数根。

记得开 ```double```，~~代码就不贴了罢~~

希望能帮到没学过一元二次方程的小朋友。

---

## 作者：zhang_kevin (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF630N)

[更好的阅读体验？](https://www.luogu.com.cn/blog/zyc-Kevin-Luogu-blog/Solution-CF630N)

# Solution

二次方程求解没有什么特别难的地方，但这有一个陷阱：你应该先输出较大的根（坑死我了$\verb!······!$）。

对于二次方程 $ax^{2}+bx+c=0$ $(a \ne 0)$，它的解为 $x = \dfrac{-b + \sqrt{b^{2}-4ac}}{2a} $ 或者 $ \dfrac{-b - \sqrt{b^{2}-4ac}}{2a}$。因此我们将题目给出的 $a,b,c$ 代入公式即可。

而 $a=0$ 时，$ax^{2}+bx+c=0$ 就变成了 $bx+c=0$，这个东西只有一个解，不符合题意，不需要考虑。

# Code

```cpp
#include<cmath>
#include<iomanip>
#include<iostream>
#include<algorithm>
using namespace std;
auto Solve = [](void) -> int{
	double a, b, c;
	cin >> a >> b >> c;
	double x_1 = ( ( -b ) + sqrt( b * b - 4 * a * c ) ) / ( 2 * a );
	double x_2 = ( ( -b ) - sqrt( b * b - 4 * a * c ) ) / ( 2 * a );
	cout << fixed << setprecision(15) << max(x_1, x_2) << endl << min(x_1, x_2) << endl;
    return 0;
}();
int main(){return Solve;}
```

---

## 作者：tommyfj (赞：0)

读完题目，我们知道它是要我们求关于 $x$ 的一元二次方程 $ax^2 + bx + c = 0$ 的根。

先来了解一下什么是一元二次方程：

定义：只含一个未知数，并且这个未知数的最高次数是 $2$ 的整式方程，叫做一元二次方程。

请注意，一元二次方程是有根的判别式以及求根公式的。

请看,

一般地，我们将式子 $b^2 - 4ac$ 叫做方程 $ax^2 + bx + c = 0(a \neq 0)$ 的根的判别式，通常用希腊字母 $\Delta$ 表示，即 $\Delta = b^2 - 4ac$。

根的情况与判别式的关系大致分别三种：

$$
    \left\{
        \begin{array}{ll}
            \Delta > 0 \\  
            \Delta = 0 \\
            \Delta < 0
            
        \end{array}
    \right.
$$

当 $\Delta > 0$ 时，方程 $ax^2 + bx + c = 0$ 有两个不相等的实数根，即 $x = \frac{-b\pm\sqrt{b^2-4ac}}{2a}$。（其实就是求根公式）

当 $\Delta = 0$ 时，方程 $ax^2 + bx + c = 0$ 有两个相等的实数根，即 $x_1 = x_2 = -\frac{b}{2a}$。

当 $\Delta < 0$ 时，方程 $ax^2 + bx + c = 0$ 没有实数根，但是有两个共轭复根，即 $x = \frac{-b\pm\sqrt{b^2-4ac}i}{2a}$。（由于涉及到复数部分，不细讲，感兴趣的同学，出门右转，[复数](https://baike.baidu.com/item/%E5%A4%8D%E6%95%B0/254365?fr=aladdin)）

了解了这么多，下面展示核心代码：
```cpp
    delta = b*b*1.0 - 4.0*a*c;//求Delta
    delta1 = sqrt(delta);//相当于 √b²-4ac
    maxn = max((-b*1.0-delta1)/2.0/a, (-b*1.0+delta1)/2.0/a);//找最大值
    minn = min((-b*1.0-delta1)/2.0/a, (-b*1.0+delta1)/2.0/a);//找最小值
}
```

---

## 作者：jimmyfj (赞：0)


先讲下一元二次方程根的[判别式](https://baike.baidu.com/item/%E5%88%A4%E5%88%AB%E5%BC%8F/10834494?fr=aladdin)

一般的 , 式子 $b^{2} - 4ac$ 叫做 $ax^{2}+bx+c=0(a\ne0)
$ 的根的判别式 , 通常用 $\Delta$ 表示 , 即 $\Delta = b^{2} - 4ac$ .

当方程系数为实数时

1. $\Delta > 0$ 时 , 方程有两个不相等的实数根 , 即 $x = \frac{-b\pm\sqrt{b^{2} - 4ac}}{2a}$ .

2. $\Delta = 0$ 时 , 方程有两个相等的实数根 , 即 $x_{1} = x_{2} = -\frac{b}{2a}$ .

3. $\Delta < 0$ 时 , 方程没有实数根 , 方程有两个共轭虚根.

接下来看一下题目 , 题目要我们求方程的解 , 且题目**保证方程有两个不相等的实数根** , 接下来就很好做了 , 只要根据上面根的判别式的第一条求出两个实数根 , 再比一下大小 , 就完事了 .

下面给出本题的参考代码 : 

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

double a, b, c, DT;

int main()
{
    scanf("%lf %lf %lf\n", &a, &b, &c);
    
	DT = b * b - 4.0 * a * c;
    
	DT = sqrt(DT);
    
	printf("%.15lf\n%.15lf", max((-b + DT) / 2.0 / a, (-b - DT) / 2.0 / a), min((-b + DT) / 2.0 / a, (-b - DT) / 2.0 / a));

    return 0;
}

```



---

## 作者：Jasper08 (赞：0)

### 【解题思路】

我们知道，对于一元二次方程 $ax^2+bx+c=0\;(a\ne 0)$，它的解是 $x=\dfrac{-b\pm \sqrt{b^2-4ac}}{2a}$。所以我们直接将题目给出的 $a,b,c$ 代入公式即可，注意题目要求 $x_1>x_2$，所以最后还要特判一下。

最后讨论 $a=0$ 的情况。当 $a=0$ 时，普通的求根公式不再适用（因为分母显然不能为 $0$），此时方程退化为一元一次方程 $bx+c=0$。但这个方程只有一个解，与题目中保证的“方程有两个不同的实数根”矛盾。所以这种情况可以排除。

### 【完整代码】

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

int main() {
	double a, b, c;
	cin >> a >> b >> c;
	double x1 = (-b+sqrt(b*b-4*a*c)) / (2*a);
	double x2 = (-b-sqrt(b*b-4*a*c)) / (2*a);
	if (x1 < x2)
	    swap(x1, x2);
	printf("%.15f\n%.15f\n", x1, x2);
	return 0; 
}
```

---

