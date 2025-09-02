# ロボットアーム

## 题目描述

想象一只机器人手臂，将其看作是二维的一条线 $O-A-B-C$，其中 $O$ 这个点固定在原点 $(0,0)$。

如下图所示。

![](https://mujin-pc-2016.contest.atcoder.jp/img/other/mujin2016/arm_01.png)

现在，你可以改变 $\angle O,\ \angle A$ 和 $\angle B$ 的角度，但不可以改变任何线段的长度。

现在给定各条线段的长度，你需要计算 $C$ 能到达的范围总面积。

## 说明/提示

$1\le l_{OA},\ l_{AB},\ l_{BC}\le 100$

### 翻译贡献

@[hellolin](https://www.luogu.com.cn/user/751017) 译。

# 题解

## 作者：SunnyLi (赞：2)

## 思路

一道计算题，小学生都会做。

这道题其实就是计算圆环的面积，其表达式为 $\pi(R^2-r^2)$，其中 $R$ 为外圆的半径，$r$ 为内圆的半径。这里 $R$ 就是机械臂能伸到最远的距离，即 $a+b+c$。$r$ 需要分类讨论：

1. 如果 $a,b,c$ 可以构成三角形，即满足任意两边大于第三边，可以取到 $r=0$。

2. 如果无法构成三角形，则一定是 $\min(a-b-c,b-c-a,c-a-b)$，在这里表示三边中最大的一边减去较小的两边的值。

## AC 代码

```python
a,b,c = map(int,input().split(" "))
R = a+b+c
if(a+b>=c and a+c>=b and b+c>=a):   r = 0
else:   r = min(abs(a-b-c),abs(b-c-a),abs(c-a-b))
print(3.14159265358*(R*R-r*r))
```

---

## 作者：WA_sir (赞：1)

## [题目](https://atcoder.jp/contests/mujin-pc-2016/tasks/mujin_pc_2016_b)|[链接](https://www.luogu.com.cn/problem/AT_mujin_pc_2016_b)

### 题目分析

众所周知，圆周长上任意一点到圆心的距离均相等。也就说明，本题正是在求圆的面积。而因为三条机械臂长短不一，点 $C$ 可能还会有一个在大圆中的小圆所处的的面积接触不到。因此，本题的问题就简化成了求大圆减小圆，也就是圆环的面积。

圆环的面积公式为：

$$S\ =\ \pi\ (\ R^{2}-\ r^{2}\ )$$

这里只有 $R$ 和 $r$ 是变量，因此题意进一步简化为求 $R$ 和 $r$ 的值。

其中的 $R$ 很好求，就是机械臂能够的最远（伸直）的长度 $l_{OA}+l_{AB}+l_{BC}$。

但 $r$ 的长度应该是多少呢？我们分情况讨论。假设三条线段从短到长依次为 $a$，$b$，$c$：

- 如果 $a+b\geq c$，三条线段成为一个三角形或重叠。此时点 $C$ 能够碰到圆心。因此小圆不存在，$r$ 的值为 $0$。（算出负数要改成 $0$）

- 如果 $a+b<c$，则 $r$ 的值为 $c-(a+b)$。

对于第二种情况的处理有点长，因为我们并不知道最长的线段及第二长的线段是哪个。如果将其直接放在输出里会很长且很难纠错，写成函数又会有些复杂。因此先列式：

$$r=\max\{a,b,c\}-(a+b+c-\max\{a,b,c\})$$

拆括号得：

$$r=\max\{a,b,c\}-a-b-c+\max\{a,b,c\}$$

合并同类项，得：

$$r=\max\{a,b,c\}\times2-a-b-c$$

又因 $R=a+b+c$，得：

$$r=\max\{a,b,c\}\times2-R$$

便可以求出 $r$ 的值了。但由于我在程序中是直接输出的，所以省去了最后一步。

另外，还要注意一下本题的精度问题。$\pi$ 一定要越精确越好，例如保留小数点后 $10$ 位。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const double pi=3.14159265358979;
double a,b,c,ans;
int main()
{
	scanf("%lf%lf%lf",&a,&b,&c);
	printf("%.7lf",pi*(pow(a+b+c,2)-pow(max(max(max(a,b),c)*2-(a+b+c),0.0),2)));
	return 0;
}
```
感谢你的阅读！

---

## 作者：0x00AC3375 (赞：0)

# 1. 分析
简单的求圆环面积问题。

输入三根机械臂的长度 $a,b,c$，最长的半径显然就是它们的长度之和，也即 $a+b+c$，而最短的半径取决于三条长度是否能组成三角形。

设 $a$ 为最长，$c$ 为最短，如果 $a\le b+c$，那么 $C$ 能够够到原点，所求的面积就是 $\pi (a+b+c)^2$。若 $a>b+c$，则最短的半径就是 $a-b-c$。

汇总以上情况，需要输出的值就是 $\pi (a+b+c)^2-\pi(\max(a-b-c,0))^2$。

# 2. 代码
```
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const long double pi = 3.1415926535897932385l;
long double l[3];
int main()
{
	scanf("%Lf%Lf%Lf", &l[0], &l[1], &l[2]);
	sort(l, l + 3);
	printf("%.10Lf\n", l[0] + l[1] >= l[2] ? pi * powl(l[2]+l[1]+l[0], 2.0l) : pi * powl(l[2]+l[1]+l[0], 2.0l) - pi * powl(l[2] - l[1] - l[0], 2.0l));
}


```

# 3. 拓展
本题也可以推广到 $n$ 条机械臂的情况，解决方法也与之类似，关键点在于这些机械臂是否能构成一个 $n$ 边形。在上面的代码中增加 ```cin>>n``` 语句或者 ```scanf("%d",&n)```，排序后判断最长的一个是否大于其他之和即可。

---

## 作者：zxh923 (赞：0)

# AT_mujin_pc_2016_b ロボットアーム 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_mujin_pc_2016_b)

### 思路

这道题一开始看有点懵，再仔细一看，其实就是求一个圆或者圆环的面积，所以我们只需要求出它的半径或大圆减小圆的半径差即可。

最大半径很好求，把三根机械臂拉为一条线段即可。

最小半径需要想一想，其实就是最长的一根机械臂减去剩下两根机械臂的长度。但显然长度不可能是负数，所以我们要将它和 $0$ 取最大值。

又发现精度的要求，所以我们将圆周率取为 $3.14159265$ 即可。

###  代码

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a,b,c,maxx,midd,minn;
double maxs,mins,minlen;
double pi=3.14159265;//圆周率
int main(){
   //以下的三者表示三根机械臂
   cin>>a>>b>>c;
   maxs=pi*(a+b+c)*(a+b+c);//最大面积
   maxx=max(a,(max(b,c)));//三者之中最大长度
   minn=min(a,(min(b,c)));//三者之中最小长度
   midd=a+b+c-maxx-minn;//三者之中第二的长度
   minlen=max(0,maxx-minn-midd);//最小半径
   mins=pi*minlen*minlen;//最小面积
   //然后做差求出圆或圆环的面积
   cout<<fixed<<setprecision(7)<<maxs-mins<<'\n';//控制精度，7位就够了
   return 0;
} 
```

---

## 作者：caijiahuangya (赞：0)

# 一道很基础的数学题

我们可以预料，点 $C$ 的运动路径将会是一个圆环。

那又有一个问题：大半径 $R$ 和小半径 $r$ 呢？

很明显，大半径 $R$ 将会是三条线段的长度和。

那小半径呢？

很简单，将三条线段长度进行排序（建议用双精数组存入，可以直接排序)。
```cpp
sort(a,a+3);
```
小半径自然就是最长的半径减去另外两条半径之和了。
```cpp
double r2=a[2]-a[1]-a[0];
```
接下去就是圆环面积。

我们小学就学过一个公式 $\pi(R^2-r^2)$。

那么送去平方差公式处理一下可以得到 $\pi(R+r)(R-r)$（不知道的可以跳过，只是写着简单）。

但是别忘了一点，万一另外两条小的之和大于最大的一条，那也就意味着可以到达圆内的任意一个地方。

那只要计算圆的面积即可。

进行一个小小的特判。

上代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
const double PI=3.141592653;
double a[3];
int main(){
    scanf("%lf%lf%lf",&a[0],&a[1],&a[2]);
    sort(a,a+3);
    double r1=a[0]+a[1]+a[2];
    double r2=a[2]-a[1]-a[0];
    if(r2<=0) printf("%.10lf",PI*r1*r1);
    else printf("%.10lf",PI*(r1+r2)*(r1-r2));
    return 0;
}
```
蒟蒻的第二篇题解qwq。

---

## 作者：zhanghaosong (赞：0)

# AT_mujin_pc_2016_b ロボットアーム 题解

### 前置芝士

1. 圆的面积怎么算呢？

[Baidu First Search(BFS)](https://baike.baidu.com/item/%E5%9C%86%E9%9D%A2%E7%A7%AF%E5%85%AC%E5%BC%8F/3117177?fr=ge_ala)。

公式很简单：$S=\pi r^2$。

2. 圆环的面积怎么算呢？

[Baidu First Search(BFS)](https://baike.baidu.com/item/%E7%8E%AF%E5%BD%A2%E9%9D%A2%E7%A7%AF%E5%85%AC%E5%BC%8F/939414)。

公式也很简单，设两个圆的面积为 $x_1,x_2$，且 $x_1>x_2$。

$S=\pi (x_1^2-x_2^2)$。

### 思路

1. 面积最大的情况：

可以讲 $3$ 个机械臂全部伸直，圆的半径为 $l_1+l_2+l_3$，面积易得。

2. 面积最小的情况：

设 $l_1,l_2,l_3$ 中的最大值为 $maxx$，中值为 $mid$，最小值为 $minn$。

机械臂的最短臂展为 $\text{max}(0,maxx-mid-minn)$。

注意判断如果 $maxx-mid-minn<0$ 的情况。

### 代码

沿袭优良传统，不给代码。

---

## 作者：shenbairui (赞：0)

### 题目分析
题目大意：求一个圆环，要精确到十位小数，注意了 $\pi$ 要取到```
3.14159265359```。

#### [圆环面积公式。](https://baike.baidu.com/item/%E7%8E%AF%E5%BD%A2%E9%9D%A2%E7%A7%AF%E5%85%AC%E5%BC%8F/939414?fr=ge_ala)

我们就成功把第一步完成了，成功的转换成了一道小学奥数题，只需要得到大圆半径和小圆半径就可以了。


第二步：求 $r$ 的值，让我们思考一下，我们可以先将 $OA$ 和 $OB$和 $OC$  排序
，得到 $OA \geq OB \geq OC$，我们可以把最长的线段设为 $O-A$ ，发现任何线段作为 
 $O-A$ 对结果并不造成影响，我们就可以直接套公式了！

### 代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10];
double r1,r2;
const double pi=3.14159265359;
int main(){
	cin>>a[0]>>a[1]>>a[2];
	sort(a,a+3);//排序
	r2=a[0]+a[1]+a[2];//r2
	r1=a[2]-a[0]-a[1];//r1
	if(r1<0) r1=0;//特判 防止变负数
	cout<<fixed<<setprecision(10)<<pi*(r2*r2-r1*r1);//精度！
	return 0;//好习惯
}
```
下期见！

---

## 作者：Lemon_zqp (赞：0)

### 思路
思考了一下，先进行排序使得 $OA≥AB≥BC$，任何线段作为 $O-A$ 对结果并不造成影响，我们可以把最长的线段设为 $O-A$，求 $r$ 的值也就是轻轻松松的事了。圆形面积公式 $S=π(R^2 - r^2)$，这题 $π$ 取 ``3.14159265359``。

### 代码
```
#include<bits/stdc++.h>
using namespace std;

int a, b, c;
double r, R;//要用double

void cmp()
{
    if(a > b) 
	{
		int t = a;
		a = b;
		b = t;
	}
	if(b > c) 
	{
		int t = b;
		b = c;
		c = t;
	}
	if(a > b) 
	{
		int t = a;
		a = b;
		b = t;
	}
}

int main()
{
    double pai = 3.14159265359;
    cin >> a >> b >> c;
    cmp();//进行排序
    R = a + b + c;
    r = c - b - a;
    if(r < 0) 
    {
        r = 0;
    }
    printf("%.10lf\n", pai * (pow(R, 2) - pow(r, 2)));
    return 0;
}
```



---

## 作者：fish_love_cat (赞：0)

# 1 思路

题面上已经解释的很清楚了吧……

就是求一个圆环，需要注意要精确到 10 位小数，所以 $\pi$ 要取到 ```3.14159265359``` 。

[圆环面积公式，需要自取。](https://wenku.baidu.com/view/1da1823d1db91a37f111f18583d049649a660e64.html?_wkts_=1677291877982&bdQuery=%E5%9C%86%E7%8E%AF%E7%9A%84%E9%9D%A2%E7%A7%AF%E5%85%AC%E5%BC%8F)
~~（大佬请自动忽略。）~~

那么，这题就变成了一个数学题，只需要得到大圆半径和小圆半径，问题就迎刃而解了。

---

**求 $r$ 的值：**

从样例中绘制的图可以推导出，当 $O-A$ 是最长的线段时：

$r=$ 第一条线（样例图中的 $O-A$ 线）减第二条线（样例图中的 $A-B$ 线）减第三条线（样例图中的 $B-C$ 线）。

这里有一个细节，输入的数只是三个普通的线段，不是从 $O$ $-$ $A$ 线开始输。所以，判断哪一条线是 $O$ $-$ $A$ 至关重要。
~~我是这么理解的，有不同意见的别骂。~~

为了推导哪一条作为 $O-A$ 最优，我画了一张图：

![推导の图片](https://cdn.luogu.com.cn/upload/image_hosting/7uey1ztu.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

~~画太丑了。。。~~

线段 A 是深蓝色；线段 B 是浅蓝色；线段 C 是红褐色。

从图中可以看出，任何线段作为 $O-A$ 对结果并不造成影响。为了迎合上文中我们发现的公式，我们就可以将最长的线段设为 $O-A$，那么得出 $r$ 的值也就是轻而易举的事情了。

PS ：千万别把 $r$ 减到负数去！！

---

**求 $R$ 的值：**

这个部分其实没有什么思维难度，把三个线段伸直出去绕一圈，就是外圆了。而三个线段的长度和自然也就是 $R$ 了。

# 2 代码

综上，我们可以得到如下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[3];
double r1,r2;//r1=r r2=R
int main(){
    cin>>a[0]>>a[1]>>a[2];
    sort(a,a+3);
    r2=a[0]+a[1]+a[2];
    r1=a[2]-a[0]-a[1];
    if(r1<0) r1=0;
    printf("%.10lf\n",3.14159265359*(r2*r2-r1*r1));//精度！！！
    return 0;
}
```

[ Accepted.](https://www.luogu.com.cn/record/102694668)

---

## 作者：hellolin (赞：0)

[题面(洛谷)](https://www.luogu.com.cn/problem/AT_mujin_pc_2016_b)

[题面(AtCoder)](https://atcoder.jp/contests/mujin-pc-2016/tasks/mujin_pc_2016_b)

AtCoder Problems 评级难度：$\texttt{\color{#72ff72}{958}}$。

## 思路

由样例解释图易知，求解的部分是是一个圆环（当小圆半径 $r=0$ 时是一个整圆）。

首先需要会圆环的计算公式。~~（大概是小学内容）~~

$$S=\pi \cdot (R^2 - r^2)$$

大圆半径 $R$ 不必多说，把手臂伸最长就是。

$$R=l_{OA}+l_{AB}+l_{BC}$$

小圆半径 $r$ 求解如下：

由 $l_{OC}=l_{OA}+l_{AB}+l_{BC}$ 易知，即使改变这三条线段的顺序，$C$ 点的坐标和将会扫过的面积也不会改变。可将 $OA$ 段改为最长的那段，此时将 $OA$ 伸直，其余两段往回伸，扫一圈（见下图，手画画得丑见谅），小圆的半径就是 $r=l_{OA}-(l_{AB}+l_{BC})$ 了。

![](https://cdn.luogu.com.cn/upload/image_hosting/3conatgn.png)

整理如下（先进行排序使得 $OA\ge AB\ge BC$）：

$$S=\pi \cdot (R^2 - r^2)$$

$$R=l_{OA}+l_{AB}+l_{BC}$$

$$r=\left\{\begin{aligned}0\ (AB+BC\ge OA)\\OA-(AB+BC)\ (AB+BC< OA)\end{aligned}\right.$$

## 代码

``` cpp
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#define PI acos(-1)
int a[4];
double R, r;
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin>>a[1]>>a[2]>>a[3];

    std::sort(a+1,a+4); // 排序，此时 a[3] 最大

    R = a[1]+a[2]+a[3];
    r = a[3]-(a[1]+a[2]);
    r = r<0?0:r;

    std::cout<<std::fixed<<std::setprecision(10);
    std::cout<<(PI*(R*R-r*r))<<std::endl;
    return 0;
}
```

---

