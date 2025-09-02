# [ABC144D] Water Bottle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc144/tasks/abc144_d

高橋君は、底面が $ 1 $ 辺 $ a~\mathrm{cm} $ の正方形であり、高さが $ b~\mathrm{cm} $ であるような直方体型の水筒を持っています。(水筒の厚みは無視できます。)

この水筒の中に体積 $ x~\mathrm{cm}^3 $ の水を入れ、底面の正方形の $ 1 $ 辺を軸として、この水筒を徐々に傾けます。

水を溢れさせずに水筒を傾けることができる最大の角度を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ <\ =\ a\ \leq\ 100 $
- $ 1\ <\ =\ b\ \leq\ 100 $
- $ 1\ <\ =\ x\ <\ =\ a^2b $

### Sample Explanation 1

水筒は立方体であり、水は半分まで入っています。この水筒を $ 45 $° より大きく傾けると水が溢れます。

### Sample Explanation 2

水筒はほぼ空であり、水が溢れるときにはほぼ水平になっています。

### Sample Explanation 3

水筒はほぼ満杯であり、ほぼ垂直の状態で水が溢れます。

## 样例 #1

### 输入

```
2 2 4```

### 输出

```
45.0000000000```

## 样例 #2

### 输入

```
12 21 10```

### 输出

```
89.7834636934```

## 样例 #3

### 输入

```
3 1 8```

### 输出

```
4.2363947991```

# 题解

## 作者：f_hxr_ (赞：3)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc144_d) & [AT传送门](AT_abc144_d)

题意就不说了吧，直接开始分析。

## 1. 分析

从侧面看，水与玻璃侧面接触的部分（下文简称水）是一个平面图形。

我们用它的面积，乘以容器的底边宽度，就是水的体积。

这就把一个三维问题转化成二维问题，只需要用夹角和长宽表示出面积即可。

## 2.两种情况

根据水的多少，我们可以发现有两种情况，让我们逐一分析。

下文称要求的夹角为 $\theta$。

### 1.水的体积 $\ge$ 杯子容积

其情况如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/hdqjq25a.png)

我们设梯形面积为 $S$。它可以有大长方形减去白色三角形的面积得到。

由物理知识可得，$\angle \alpha = \angle \theta$。

因为 $\tan \alpha =  f/a$，所以 $f = a \tan \alpha$。

所以白色三角形的面积为 $\frac{a^2 \tan \alpha}{2}$。

所以蓝色梯形的面积为 $ab - \frac{a^2 \tan \alpha}{2}$。

又因为水的体积 $x = aS$，所以 $x = a^2b - \frac{a^3 \tan \alpha}{2}$。

移项得到 $\tan \alpha = \frac{2(a^2b-x)}{a^3}$。

将 $\angle \alpha = \angle \theta$ 代入，最后得到 $\theta = \arctan(\frac{2(a^2b-x)}{a^3})$。

### 1.水的体积 $\le$ 杯子容积

如图

![](https://cdn.luogu.com.cn/upload/image_hosting/f47xe3ne.png)

此时我们只需求出蓝色三角形的面积即可。

还是由物理知识可得，$\angle \alpha = \angle \theta$。~~这不废话吗~~

因为 $\tan \alpha =  b/f$，所以 $f = b / \tan \alpha$。

所以蓝色三角形的面积为 $\frac{b^2 }{2 \tan \alpha}$。

又因为水的体积 $x = aS$，所以 $x = \frac{ab^2 }{2 \tan \alpha}$。

移项得到 $\tan \alpha = \frac{ab^2 }{2x}$。

将 $\angle \alpha = \angle \theta$ 代入，最后得到 $\theta = \arctan(\frac{ab^2 }{2x})$。

至此，问题解决。

### 3.代码

```cpp
#include<bits/stdc++.h>//	   2(a^2·b-x)                 a b^2  
using namespace std;//tanθ= --------------(x>=a^2 b) or ---------- (x<a^2 b) 
typedef long double LD;//          a^3                       2x
const LD PI=3.1415926535897932384626433832795028841971693993751058209749445;
LD A,B,X,ans;
int main(){
	cin>>A>>B>>X;
	if(A*A*B==X){cout<<"0";return 0;}
	if(X>=(A*A*B)/2.0) ans=atan(2*(A*A*B-X)/(A*A*A))*180.0/PI;
	else ans=atan((A*B*B)/(2*X))*180.0/PI;
	cout<<fixed<<setprecision(10)<<ans<<endl;
	return 0;
}
```


## [附：在Desmos做的模拟图](https://www.desmos.com/geometry/rqnhdqhuqh?lang=zh-CN)

---

## 作者：Keids (赞：3)

# [ABC144D] Water Bottle

原题链接：[D - Water Bottle](https://atcoder.jp/contests/abc144/tasks/abc144_d)

洛谷链接：[[ABC144D\] Water Bottle](https://www.luogu.com.cn/problem/AT_abc144_d)

题意已经很清晰了，就不过多复述。

这里给出数学做法。

首先我们要搞懂，要让水倒不出来的情况有什么。

自己动手画图可以发现只存在两种情况。

这里给出两张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rkad38zn.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如上图，我们当水未过瓶子的一半时，它成一个三棱柱。

而我们需要求的角为红色标出的角。

求角度，我们需要借用一个函数：atan。即反正切函数。

直接调用 cmath 函数库即可，作用是求出该正切值对应的弧度。

那么我们只需要求出两边即可。

有一条边我们已知为 $b$，另一条边可以快速求出为：$x\times2 \div a\div b $。

那么我们要求的角的正切值就是：$a\times b\times b\div 2\div x$。

![](https://cdn.luogu.com.cn/upload/image_hosting/k2pkg704.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

对于另一种情况同理，但是因为水超过一半，我们就可以通过平行的关系把要求的角转移。

如上图所示。(其实直接爆算也行)

那么我们的两条边就变成了：$a$ 和 $(b-2\times x+a\times a\times b)\div (a\times a)$。

那么答案就是：$(b-(2\times x-a\times a\times b)\div (a\times a))\div a$。

代码很短，如下：

```c++
#include<cstdio>
#include<cmath>
#define PI 3.14159265
using namespace std;
double x,a,b;
int main(){
	scanf("%lf%lf%lf",&a,&b,&x);
	if(2*x>a*a*b)printf("%.10lf",atan((b-(2.0*x-a*a*b)/(a*a))/a)*180.0/PI);
	else printf("%.10lf",atan(a*b*b/2/x)*180.0/PI);
    \\    *180/PI是因为要把弧度转化成角度。
	return 0;
}

```



---

## 作者：FurippuWRY (赞：2)

### 题意如下
![正立](https://cdn.luogu.com.cn/upload/image_hosting/z2q00nh4.png)

其中 $a$ 是底边长，$b$ 是容器的高，$x$ 是水的体积。  
现在要把它倾斜，有三种情况。
#### 图 1  
![倾斜1](https://cdn.luogu.com.cn/upload/image_hosting/y4ktg3dm.png)
#### 图 2  
![倾斜2](https://cdn.luogu.com.cn/upload/image_hosting/oa8rmb4i.png)
#### 图 3  
![倾斜3](https://cdn.luogu.com.cn/upload/image_hosting/pos8kezb.png)

------------

### 前置知识
做这题你首先要知道三角函数、反三角函数、弧度制等知识。

三角函数中常用的有正弦函数、余弦函数、正切函数等。本题只用正切函数就可以 AC，正切函数的定义如下： 
![](https://cdn.luogu.com.cn/upload/image_hosting/xk0le0y0.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/p2j89y6w.png)  
三角函数还有一个在平面直角坐标系里的定义，在这里不讲。

那么什么是反三角函数？反三角函数是三角函数的反函数。
反函数即定义域（函数自变量的取值范围）和值域（函数因变量的集合，即 $y$ 值的集合）互换的函数。

我们利用反三角函数来求出一个三角函数值对应的角的大小。

要表示一个三角函数的反函数，用 $\operatorname{arc}+$ 函数名或在三角函数与自变量中间加上上标“$-1$”即可。
如正切函数，用 $\arctan a$ 或 $\tan^{-1}a$ 来表示反正切函数（$a$ 是一个常数）。

在 C++ 的 `cmath` 库里，有一个函数 `atan()`，可以用它来计算一个数的反正切函数，结果是一个弧度数，（弧度制是表示角的大小的方法之一）但输出结果要求是角度，这时我们就要把弧度转换为角度。  
角度与弧度的换算如下（$\operatorname{rad}$ 为弧度单位）：
![jiaoduhudu](https://cdn.luogu.com.cn/upload/image_hosting/n5qhq5vp.png)  
也就是说，要把弧度数转换为角度，只要把这个弧度数乘 $\dfrac{180}{\pi}$ 即可。

------------
### 回归正题
先定义几个要用的变量：  
容积 $v=a^2b$；  
角度 $ang$；  
$m=$ 图 1 中的 $AP$；  
$h=$ 图 2、图 3 中的 $CP$。  

------------

先看第一种情况.。

![倾斜1](https://cdn.luogu.com.cn/upload/image_hosting/y4ktg3dm.png)  
这种情况下，$x>\dfrac{v}{2}$，$PD\parallel EF$，$BC\parallel AD$。

由“两直线平行，同位角相等”可得 $\angle BCE=\angle ADP$。

也就是说，$\tan\angle BCE=\tan\angle ADP=\dfrac{AP}{AD}=\dfrac{m}{a}$。

我们只要求出 $\arctan \dfrac{m}{a}$ 再转换为角度即可。

求 $m$，可以先把剩余体积（即 $v-x$）乘 $2$，当作一个正方体，因为正方体的体积为边长的三次方，所以将剩余体积除容器底面积（$a^2$）就可得到 $m$。

即 $m=\dfrac {2(v-x)}{a^2}$。

因为这个容器是个长方体，所以 $AD=BC=a$，所以 $\arctan \dfrac{m}{a}=\arctan \dfrac{2(v-x)}{a^3}$，$ang=\dfrac{180}{\pi}\times\arctan \dfrac{2(v-x)}{a^3}$。  

------------

第二、三种情况。

由于这两种情况本质上是一样的，所以放在一起讲。  
![倾斜2](https://cdn.luogu.com.cn/upload/image_hosting/oa8rmb4i.png)
![倾斜3](https://cdn.luogu.com.cn/upload/image_hosting/pos8kezb.png)
这种情况下，$x\le\dfrac{v}{2}$。

这里要求出 $\tan \angle BCE$ 和第一种情况类似，$PD\parallel EF$，由“两直线平行，内错角相等”可得 $\angle BCE=\angle DPC$。

即 $\tan\angle BCE=\tan\angle DPC=\dfrac{DC}{PC}=\dfrac{b}{h}$。

求 $h$，先求 $2x$，得到一个长方体。

长方体的体积 $=$ 长 $\times$ 宽 $\times$ 高，这里的高就是 $h$，所以长 $\times$ 宽 $=ab$，即 $h=\dfrac{2x}{ab}$。

所以 $\arctan\dfrac{b}{h}=\arctan\dfrac{ab^2}{2x}$，$ang=\dfrac{180}{\pi}\times\arctan\dfrac{ab^2}{2x}$。  
综上所述，

$$ang=\begin{cases}\dfrac{180}{\pi}\times\arctan \dfrac{2(v-x)}{a^3},x>\dfrac{v}{2}\\\dfrac{180}{\pi}\times\arctan\dfrac{ab^2}{2x},x\le\dfrac{v}{2}\end{cases}$$

------------

# AC code
```cpp
#include <bits/stdc++.h>

using namespace std;

double a, b, x, ang, v, m, h; //ang 为角度，v 为容积，m 为 AP，h 为 CP 

const double pi = 3.14159265358979;

int main() {
	
	cin >> a >> b >> x;
	v = a * a * b;
	if (x > v / 2){//第一种情况
		m = (v - x) * 2 / (a * a);
		ang = atan(m / a) * (180 / pi);//求出反正切函数的值，弧度化为角度
	}
	else {//第二、三种情况
		h = 2 * x / b / a;
		ang = atan(b / h) * (180 / pi);
	}
	printf("%.10lf",ang);//要输出 10 位小数
	return 0;
}
```
#### 化简：
```cpp
#include <bits/stdc++.h>

using namespace std;

double a, b, x, v, pi = 3.14159265358979;

int main() {
	cin >> a >> b >> x;
	v = a * a * b;
	if (x > v / 2) {
		printf("%.10lf", atan((v - x) * 2 / (a * a * a)) * (180 / pi));
	}
	else {
		printf("%.10lf",atan(a * b * b / 2 / x) * (180 / pi));
	}
	return 0;
}
```

---

## 作者：OIerBoy (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc144_d)
## 翻译
有一个底是正方形的长方体水瓶,这个水瓶的底的边长为 $a$，高为 $b$ (忽略瓶子的厚度)。

倒入 $x \, cm^3$ 的水，且沿底面倾斜瓶子。瓶子最多能倾斜多少度时水不会溢出？

## 预备知识
注：会三角函数的 dalao 可以跳过。

我们在做这道题目之前，需要先了解一下三角函数是什么。

![](https://cdn.luogu.com.cn/upload/image_hosting/0wfnl6gc.png)

这里，我们有如下的定义：

- 正切函数：$\sin A = \tfrac{a}{c}$。

- 余弦函数：$\cos A = \tfrac{b}{c}$。

- 正切函数：$\tan A = \tfrac{a}{b}$。

而在 C++ 中求 $ \angle A$ 的度数可以用一下几个函数：

```cpp
A_1=asin(a/c)/(2*M_PI)*360
A_2=acos(b/c)/(2*M_PI)*360
A_3=atan(a/b)/(2*M_PI)*360
//注意这里的反函数求出的是弧度，所以要/(2*M_PI)*360
```

## 解析
首先，我们这道题我们要进行一下分类讨论，分以下两种情况：

1.当 $x \ge \tfrac{a^2b}{2}$ 时：

![](https://cdn.luogu.com.cn/upload/image_hosting/d52l5kof.png)

我们要想求桌面与杯子的倾角 $\angle 1$ 求出 $\angle 3$ 即可。

所以我们只需要求出 $AB$ 与 $AP$ 然后用函数 $\tan$ 求出角度。

这里，$AB=a$，$AP=\tfrac{2(a^2b-x)}{a^2}$。

2.当 $x < \tfrac{a^2b}{2}$ 时：

![](https://cdn.luogu.com.cn/upload/image_hosting/r620sfu1.png)

我们要想求桌面与杯子的倾角 $\angle 1$ 求出 $\angle 2$ 即可。

所以我们只需要求出 $BC$ 与 $CQ$ 然后用函数 $\tan$ 求出角度。

这里，$BC=a$，$CQ=\tfrac{2x}{ab}$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
double a,b,x,k,n,m;
int main(){
	cin>>a>>b>>x;
	if(x>=a*a*b*1.0/2){
		n=a,m=(a*a*b-x)*2.0/(a*a);
		printf("%.10lf",atan((double)(m*1.0/n))/(2*M_PI)*360);
	}else{
		n=b,m=2.0*x/(a*b);
		printf("%.10lf",atan((double)(n*1.0/m))/(2*M_PI)*360);
	}
	return 0;
}
```

---

## 作者：liyixi09 (赞：1)

**前言** 

~~一眼式子，万年debug。~~

------------

# 题目大意

有一个长方体瓶子，底面为边长为 $a$ 厘米的正方形，高为 $b$ 厘米。现倒入 $x$ 立方厘米的水，求最多倾斜多少度，使水不会漏出来？

------------

# 思路

由于是向一侧倾斜，所以倾斜后水的形状一定是棱柱。

则棱柱高为 $a$。

求得底面积 $d = x \div a$。

先将这个问题转化为平面问题。

讨论倾斜后为三角形时：

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/wm7ge6ig.png)

是长方体瓶子，所以图中蓝色三角形为直角三角形。

已经求出底面积 $d$ （即图中蓝色直角三角形的面积），则 $a_1 = d \times 2 \div b $。利用反正切函数 $\operatorname{arctan(\frac{a_1}{b})}$ 用对边与邻边之比求出 $\angle 2$。得出倾斜度 $\angle 1 = 90^\circ - \angle 2$。

还有倾斜后为直角梯形的情况：

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/i92z3xn8.png)

设 $PM$ 长度为 $x$。

可以列出方程：

$$ax + \frac{a(b-x)}{2}=d$$

解得 $x = \frac{2d}{a}-b$。

则 $NQ$ 长为 $b-x=b-\frac{2d}{a}+b=2b-\frac{2d}{a}$。

利用反正切函数 $\operatorname{arctan(\frac{a}{NQ})}$ 用对边与邻边之比求出 $\angle 2$。得出倾斜度为 $ 90^\circ - \angle 2$。


------------

# code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
double a,b,x,a1,d;
signed main(){
	cin>>a>>b>>x;
	
	if(a*a*b==x)
	printf("%.10lf\n",0.0);
	else{
	if(a*a*b/2.0<=x)
	{
		a1=2.0*x/a/a-b;
		printf("%.10lf\n",90.0-(atan((a)/(b-a1))/acos(-1))*180.0);
	}
	else
	{
		a1=x/a*2.0/b;
	printf("%.10lf\n",90.0-(atan(a1/b)/acos(-1))*180.0);
	}

	}
		return 0;
}
```

注意输出的小数位数。


---

## 作者：Sun_wtup (赞：0)

# [ABC144D] Water Bottle 题解

[题目传送](https://www.luogu.com.cn/problem/AT_abc144_d)

## 题意

有一个水杯，给出它的底的边长 $a$（底是正方形），然后给出他的高 $b$，向水杯中注入一些水，水的体积是 $x~\mathrm{cm}^3$。现在将水杯倾斜，问水杯最多倾斜多少度，水不会溢出。

## 分析

这是一道~~简单~~的数学题。首先我们要从侧面看这个水杯，先用水的体积除以底边边长，就得到了从侧面看水的面积，再判断这个图形是梯形还是三角形，最后运用三角函数的知识即可解决。

![](https://cdn.luogu.com.cn/upload/image_hosting/lnx20zvr.png)

我们令侧面积为 $S~\mathrm{cm}^2$，$S = \dfrac{x}{a}$。

接下来判断这个侧面积是梯形还是三角形。不难想到当梯形的上底不为正数时，它就成为了一个三角形，我们设上底为 $y$，有：

$$
\begin{aligned}
S &= \dfrac{(y+b)a}{2}\\
y &= \dfrac{2S}{a}-b
\end{aligned}
$$

1. 若是三角形，我们求一下在水杯底边上的那条直角边，很明显这条边的长度是 $\dfrac{2S}{b}$。接下来运用三角函数来求角度。

    ![](https://cdn.luogu.com.cn/upload/image_hosting/x5xswymh.png)

    对于上面的这个直角三角形，有：

    $$
    \sin \theta = \dfrac{z}{y}
    $$

    $$
    \cos \theta = \dfrac{x}{y}
    $$
    
    $$
    \tan \theta = \dfrac{z}{x}
    $$

    在已知 $x$ 和 $z$ 的情况下，使用 $\arctan(\dfrac{z}{x})$（其中 $\arctan$ 是反正切函数，`cmath` 头文件中有该函数 `atan()`）即可得到 $\theta$（在代码实现的过程中注意 `atan()` 这个函数返回弧度值，需要将该值 $\times \dfrac{180}{\pi}$ 才可得到真正的 $\theta$）。最终答案是 $90^{\circ} - \theta$。

2. 若是梯形，只要在梯形中做一个直角三角形即可，如图所示：

    ![](https://cdn.luogu.com.cn/upload/image_hosting/owiykeb0.png)

    这个三角形的一个直角边是 $a$, 另一个是 $b-y$, 这样梯形的问题就转化成了三角形，再进行三角函数处理（和上文基本一样）即可得到 $\theta$。

答案需要保留十位小数。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define debug(x) std::cerr<<#x<<'='<<x<<std::endl

int main()
{
    ios::sync_with_stdio(false);
    double PI=acos(-1);
    double a,b,x,st; // a是底边，b是高 
    cin>>a>>b>>x;
    x/=a; // 求面积
    st=x*2/a-b; // 上底
    if(st>0) { // 梯形 
        printf("%.10lf",90.0-atan(a/(b-st))*180.0/PI);
    }
    else {//三角形 
        a=2*x/b;
        printf("%.10lf",90.0-atan(a/b)*180.0/PI);
    }
    return 0;
}
```

---

