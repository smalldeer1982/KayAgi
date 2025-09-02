# [ABC197D] Opposite

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc197/tasks/abc197_d

$ \mathrm{x} $ 軸の正の向きを右、$ \mathrm{y} $ 軸の正の向きを上とする $ 2 $ 次元座標平面上に、$ p_0,\ p_1,\ p_2,\ \dots,\ p_{N\ -\ 1} $ の $ N $ 個の頂点からなる正 $ N $ 角形があります。  
 ここで $ N $ は偶数であることが保証され、頂点 $ p_0,\ p_1,\ p_2,\ \dots,\ p_{N\ -\ 1} $ はこの順に反時計回りに並んでいます。  
 $ p_i $ の座標を $ (x_i,\ y_i) $ とします。  
 $ x_0,\ y_0,\ x_{\frac{N}{2}},\ y_{\frac{N}{2}} $ が与えられるので、$ x_1,\ y_1 $ を求めてください。

## 说明/提示

### 制約

- $ 4\ \le\ N\ \le\ 100 $
- $ N $ は偶数
- $ 0\ \le\ x_0,\ y_0\ \le\ 100 $
- $ 0\ \le\ x_{\frac{N}{2}},\ y_{\frac{N}{2}}\ \le\ 100 $
- $ (x_0,\ y_0)\ \neq\ (x_{\frac{N}{2}},\ y_{\frac{N}{2}}) $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ p_0\ =\ (1,\ 1),\ p_2\ =\ (2,\ 2) $ という情報が与えられています。 $ p_0,\ p_1,\ p_2,\ p_3 $ が正方形をなし、反時計回りに並んでいるという情報から残りの頂点の座標は一意に定まり、以下のようになります。 - $ p_1\ =\ (2,\ 1) $ - $ p_3\ =\ (1,\ 2) $

## 样例 #1

### 输入

```
4
1 1
2 2```

### 输出

```
2.00000000000 1.00000000000```

## 样例 #2

### 输入

```
6
5 3
7 4```

### 输出

```
5.93301270189 2.38397459622```

# 题解

## 作者：ChuYilin2011 (赞：5)

# [AT_abc197_d](https://www.luogu.com.cn/problem/AT_abc197_d) 题解
## 前言
看到 dalao 们都用到向量，~~怕蒟蒻们看不懂，~~ 在此写一篇不带向量的题解，~~通俗易懂。~~

## 解题方法
### 前期知识
这是道计算几何题，不知道[三角函数](https://baike.baidu.com/item/%E4%B8%89%E8%A7%92%E5%87%BD%E6%95%B0/1652457?fr=ge_ala)相关知识，根本做不出来。

### 分析
知道这些后，因为是正多边形，所以我们可以画出它的外接圆。以正六边形为例，如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/p3arr73d.png)

其中点 $O$ 为圆心，也是正六边形的中心。$p_0$ 与 $p_{\frac{N}{2}}$ 如题目所述。

由于确保 $N$ 是偶数，则 $p_0$ 和 $p_{\frac{N}{2}}$ 的连线必定为该正多边形最长的对角线，即其外接圆的直径。

![](https://cdn.luogu.com.cn/upload/image_hosting/5365e5ko.png)

因此，点 $O$ 就是线段 $p_0 p_{\frac{N}{2}}$ 的中点，于是就有：
$$O(\dfrac{x_0+x_{\frac{N}{2}}}{2},\dfrac{y_0+y_{\frac{N}{2}}}{2})$$

再将 $p_0$ 绕点 $O$ 逆时针旋转 $\dfrac{2\pi}{n}$ 角度，得到 $p_1$。剩下的问题就是怎样确定旋转后的点了。

![](https://cdn.luogu.com.cn/upload/image_hosting/kt605849.png)

又有公式
$$(x\cos{\theta}-y\sin{\theta},y\cos{\theta}+x\sin{\theta})$$
描述点 $(x,y)$ 绕**原点**逆时针旋转 $\theta$ 角度后得到的点。

（记记公式容易，但希望大家能尝试看看 [证明](https://www.luogu.com.cn/article/qg8bh6p6)。）

这时，就要将 $O$ 点先当作原点，确定旋转后的点之后，再“还原”。图示大概长这个样子（**仅在这幅图中** $O$ 指原点，$O^\prime$ 是旋转中心，$p$、$p^\prime$ 分别表示旋转前、旋转后的点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/l9e8sm6m.png)

描述 $p_1$ 的式子就是这样：
$$[(x_0-x_O)\cos{\theta}-(y_0-y_O)\sin{\theta}+x_O,\\(y_0-y_O)\cos{\theta}+(x_0-x_O)\sin{\theta}+y_O]$$

为了让~~可爱的~~读者明确什么叫“先当作原点”，什么叫“还原”，这里用 $\theta$ 表示旋转角度，用 $x_O$、$y_O$ 分别表示上文 $O$ 点的横、纵坐标。

## 代码
根据上式，就可以写出如下代码了：

```cpp
#include <stdio.h>
#include <math.h>
int n, X0, Y0, Xk, Yk;
double XO, YO, X1, Y1, theta;
//math.h 库中有 y0、y1 两个函数，全局变量不能用

int main()
{
	scanf("%d %d %d %d %d", &n, &X0, &Y0, &Xk, &Yk);

	XO = (X0+Xk)*0.5;
	YO = (Y0+Yk)*0.5;
	theta = 2*M_PI/n;
//M_PI 是 math.h 库中自带的圆周率常量

	X1 = (X0-XO)*cos(theta) - (Y0-YO)*sin(theta) + XO;
	Y1 = (Y0-YO)*cos(theta) + (X0-XO)*sin(theta) + YO;
	printf("%.11lf %.11lf", X1, Y1);
	return 0;
}
//该代码未使用作者真实码风写，请勿误解。
```

### P.s.
重要的事情说三遍！全局变量不要用 `y0` 和 `y1`！全局变量不要用 `y0` 和 `y1`！全局变量不要用 `y0` 和 `y1`！`math.h` 库里有这两个函数（定义局部变量就没事）！

#### Upd. 
- upd. 2024.04.05：根据用户 [2021Changqing60](https://www.luogu.com.cn/user/947380) 的建议修改部分内容。
- upd. 2024.04.07：修改了 $\LaTeX$。
- upd. 2024.04.09：加入旋转公式证明。
- upd. 2024.04.13：将旋转公式证明移至文章中。

## 总结
虽然写了题解，但本人也是查了一大堆资料才会做的，所以打提高组，与三角函数有关的知识真的很重要！大家一定要去多学学！

---

## 作者：superLouis (赞：1)

## 题解：AT_abc197_d [ABC197D] Opposite

看到一堆向量的题解，过来水一篇三角函数的。

----------
### 1. 题目理解

题目给定一个正 $N$ 边形（$N$ 为偶数），并且给出了两个顶点的坐标：$ p_0 = (x_0, y_0) $ 和 $ p_{\frac{N}{2}} = (x_{\frac{N}{2}}, y_{\frac{N}{2}}) $。要求我们求出下一个顶点 $ p_1 = (x_1, y_1) $ 的坐标。

----------
### 2. 解题思路

正 $N$ 边形的所有顶点均匀分布在以中心为圆心的圆上。因此，我们可以通过旋转的方式来求出其他顶点的坐标。给定一个点 $ (x, y) $，绕原点旋转角度 $ \theta $ 后的新坐标 $ (x', y') $ 可以通过以下公式计算：
   $$
   x' = x \cos \theta - y \sin \theta
   $$
   $$
   y' = x \sin \theta + y \cos \theta
   $$

由于正 $N$ 边形的中心是 $ p_0 $ 和 $ p_{\frac{N}{2}} $ 的中点，我们可以先求出中心点的坐标：
   $$
   \text{center}_x = \frac{x_0 + x_{\frac{N}{2}}}{2}
   $$
   $$
   \text{center}_y = \frac{y_0 + y_{\frac{N}{2}}}{2}
   $$

正 $ N $ 边形的每个顶点之间的旋转角度为 $ \theta = \frac{2\pi}{N} $。将 $ p_0 $ 绕中心点旋转 $ \theta $ 角度，得到 $ p_1 $ 的坐标，这道题就做完啦。

----------
### 3. 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    double x0, y0, xn2, yn2;
    cin >> n >> x0 >> y0 >> xn2 >> yn2;
    double cenx = (x0 + xn2) / 2.0;
    double ceny = (y0 + yn2) / 2.0;
    double theta = 2 * M_PI / n;
    double x = x0 - cenx;
    double y = y0 - ceny;
    double x1 = x * cos(theta) - y * sin(theta);
    double y1 = x * sin(theta) + y * cos(theta);
    x1 += cenx;
    y1 += ceny;
    cout << fixed << setprecision(11) << x1 << " " << y1 << "\n";
    return 0;
}
```

直接 $O(1)$ 水掉哦～

---

## 作者：loser_seele (赞：1)

计算几何题，虽然不难想，但是写起来很恶心。部分内容参考官方题解。

考虑题目给定的正多边形为偶数边形，且给定了一条对角线求顺时针的第二个顶点，那么可以这么计算：先算出对角线上的中点，然后计算出从第一个顶点到中点需要旋转的角度，再根据这个角度算出第一个顶点到第二个顶点需要旋转的角度，就可以直接用公式算出第二个顶点的坐标。

具体地，设 $ q $ 为中点，则先计算出 $ p_0 $ 到 $ q $ 的角度，然后逆时针旋转 $ \frac{2 \times \pi}{n} $ 角度，这样计算出的是第二个顶点到 $ q $ 的角度，最后就可以算出这个坐标。至于为什么这么做，因为原多边形是正多边形且边为偶数，则 $ p_0qp_1 = \frac{2 \times \pi}{n} $，然后就可以直接计算。

实现上可以直接套用自带的三角函数和复数，减少代码量。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
pair<double,double>rotate(double x,double y,int n) 
{
    complex<double>c(x, y),alpha(cos(2*M_PI/n),sin(2*M_PI/n));
    c*=alpha;
    return {c.real(),c.imag()};
}
int main() 
{
    int n; 
    cin>>n;
    double x0,y0,xn,yn; 
    cin>>x0>>y0>>xn>>yn;
    double xg=(x0+xn)/2,yg=(y0+yn)/2;
    auto [x1,y1]=rotate(x0-xg,y0-yg,n);
    printf("%.12lf %.12lf",x1+xg,y1+yg);
}
```


---

## 作者：Symbolize (赞：1)

# 思路
首先我们来画图分析，首先话外接圆，圆心坐标即为 $(\frac{x_0+x_{\frac{n}{2}}}{2},\frac{y_0+y_{\frac{n}{2}}}{2})$，又因为为正 $n$ 边形，所以中点即为外接圆圆心，连接中点与 $(x_1,y_1)$ 和中点与 $(x_0,y_0)$，显然圆周被正 $n$ 形 $n$ 等分，所以所连两线的夹角即为 $\frac{2 \pi}{n}$。

接着直接套用绕角公式。

绕角公式：
> 中点 $(x_c,y_c)$，从 $(x_0,y_0)$ 转 $\theta$ 度得到 $(x_1,y_1)$。

> $x_1=(x_0-x_c) \times \cos(\theta)-(y_0-y_c) \times \sin(\theta)+x_c$。

> $y_1=(x_0-x_c) \times \sin(\theta)+(y_0-y_c) \times \cos(\theta)+y_c$。

此题就结束了。

图：

![](https://cdn.luogu.com.cn/upload/image_hosting/hk1rr7n8.png)

# Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
#define debug() puts("----------")
const int N=1e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
const double pi=acos(-1);
using namespace std;
typedef complex<int> ci;
typedef complex<double> cd;
int n;
double x_0,y_0,x_1,y_1;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
signed main()
{
//	#ifndef ONLINE_JUDGE
//		freopen(".in","r",stdin);
//		freopen(".out","w",stdout);
//	#endif
	n=read()>>1;//稍微化简了一下，这里预先除2，之后计算角时就可以直接算π/n
	cin>>x_0>>y_0>>x_1>>y_1;
	double theta=pi/n;//角
    //可以直接把中点的计算代入转角公式
	printf("%.11lf %.11lf\n",
	(x_0-(x_0+x_1)/2)*cos(theta)-(y_0-(y_0+y_1)/2)*sin(theta)+(x_0+x_1)/2/*横坐标*/,
	(x_0-(x_0+x_1)/2)*sin(theta)+(y_0-(y_0+y_1)/2)*cos(theta)+(y_0+y_1)/2/*纵坐标*/);
	return 0;//收场
}
```

---

## 作者：ma_yu_chen_ (赞：0)

## 题目简述
这是一个几何问题，需要根据正多边形两个已知顶点求另一个顶点的坐标。
## 思路
画出这个正多边形的外接圆，再把 $p_0$ 和 $p_\frac{N}{2}$ 连接，这必定是这个正多边形最长的对角线（前提是 $N$ 为偶数），也是外接圆的直径。

然后再这条对角线上取它的中点 $O$ ，即圆心，例如下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/afo5k4e3.png)
于是，点 $O$ 的坐标就是

$$ \left(\frac{x_0 + x_{\frac{N}{2}}}{2}, \frac{y_0 + y_{\frac{N}{2}}}{2}\right) $$
再然后，需要以点 $p_0$ 为起点逆时针旋转 $\frac{2π}{N}$ 度到达下一个顶点。角度的公式如下：
$$(x \cos \theta - y \sin \theta, y \cos \theta + x \sin \theta)$$
于是点 $p_1$ 的坐标就是
$$\begin{bmatrix}
(x_0 - x_O) \cos \theta - (y_0 - y_O) \sin \theta + x_O, (y_0 - y_O) \cos \theta + (x_0 - x_O) \sin \theta + y_O
\end{bmatrix}$$
按照思路写出代码即可。
最后附上AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x00,y00,xx,yy;//这里要注意：math库中有y0、y1两个函数，不能当做变量名
double pi=3.141592653589793;
int main(){
	cin>>n>>x00>>y00>>xx>>yy;
	double xo=(x00+xx)/2.0,yo=(y00+yy)/2.0;
	double th=2*pi/n;
	cout<<(x00-xo)*cos(th)-(y00-yo)*sin(th)+xo<<' '<<(y00-yo)*cos(th)+(x00-xo)*sin(th)+yo;
	return 0;
}
```

---

## 作者：To_Carpe_Diem (赞：0)

## 题目简述
这是一个关于计算几何的问题，我们需要根据已知的顶点和条件来求解另外一个顶点的坐标。题目中给出了一个正多边形的若干个顶点的坐标，并且要求根据已知的两个顶点的坐标来求解另外一个顶点的坐标。

## 思路分析
根据题目描述，我们知道正多边形的顶点是按照逆时针方向依次给出的，现在我们已知 $p_0(x_0,y_0)$ 和 $p_{\frac{N}{2}}(x_{\frac{N}{2}}, y_{\frac{N}{2}})$，需要求解 $p_1(x_1, y_1)$。

我们可以利用已知的两个顶点坐标来求解剩余的顶点坐标，具体的做法是计算已知两个顶点的中点坐标 $(cx, cy)$。

根据已知两个顶点的坐标计算向量 $\overrightarrow{p_0p_{\frac{N}{2}}}$。根据正多边形的性质，我们可以通过旋转变换的方式求解 $\overrightarrow{p_0p_1}$，然后得到 $p_1$ 的坐标。

## 代码实现
```cpp
#include <iostream>
#include <cmath>
using namespace std;

int n, xx, yy, x2, y2;

int main() {
    cin >> n >> xx >> yy >> x2 >> y2;

    // 计算已知两个顶点的中点坐标
    double cx = (xx + x2) / 2.0;
    double cy = (yy + y2) / 2.0;
    // 计算向量p0pN/2
    double dx = xx - cx;
    double dy = yy - cy;
    // 计算旋转角度
    double a = 2 * M_PI / n;

    // 根据旋转变换的公式求解p1的坐标
    double x1 = cx + dx * cos(a) - dy * sin(a);
    double y1 = cy + dx * sin(a) + dy * cos(a);

    cout << fixed;
    cout.precision(10);
    cout << x1 << " " << y1 << endl;

    return 0;
}
```
## 复杂度分析
时间复杂度 $O(1)$，空间复杂度 $O(1)$。

---

## 作者：Kobe_BeanBryant (赞：0)

## 题目大意：
在 $ \mathrm{x} $ 轴的正方向为右，$ \mathrm{y} $ 轴的正方向为上的二维坐标平面上，设置了 $ p_0,p_1,p_2 \dots $，有一个由 $ p_{N - 1} $ 的 $ N $ 个顶点组成的正 $ N $ 边形。保证 $ N $ 是偶数，顶点 $ p_0,p_1,p_2 \dots p_{N - 1} $ 按这个顺序逆时针排列。

设 $ p_i $ 的坐标为 $ (x_i, y_i) $。$ x,y,x_{ \frac {n} {2}},y_{ \frac {n} {2}} $，求 $ x_1 $ 与 $ y_1 $。

## 大体思路：
1. 分别用 $ x $ 与 $ y $ 来存储题目所要求的值。

2. 找到所求值与 $ \pi $ 与 $ N $ 之间的规律。

## 规律：
**横坐标**：$ x + \cos(2 \times \pi \div N) \times ( x_1 - x ) - \sin(2 \times \pi \div N) \times ( y_1 - y ) $

**纵坐标**：$ y + \cos(2 \times \pi \div N) \times ( y_1 - y ) + \sin(2 \times \pi \div N) \times ( x_1 - x ) $
## AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
double PI=3.141592653589793;
	double N,x1,y1,x2,y2;//定义变量
	cin>>N>>x1>>y1>>x2>>y2;//按题目要求输入
	double x=(x1+x2)/2;//x的初始值
	double y=(y1+y2)/2;//y的初始值
	cout<<x+cos(2*PI/N)*(x1-x)-sin(2*PI/N)*(y1-y)<<" "<<y+cos(2*PI/N)*(y1-y)+sin(2*PI/N)*(x1-x);
    //当找到规律时（如上），将规律套入其中，求出最终的值
	return 0;
}
```

---

