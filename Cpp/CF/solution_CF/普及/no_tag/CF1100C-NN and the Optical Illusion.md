# NN and the Optical Illusion

## 题目描述

有一个圆，在其周围摆一圈圆，如图所示： 
![](https://cdn.luogu.org/upload/vjudge_pic/CF1100C/a0c9f6bd15b532673873e8a75fb88103ad5b8775.png)  
现已知**内圆半径**$r$，和**外圆个数**$n$，你要求出**外圆半径**$R$。  

假设你输出的答案是$a$，标准答案为$b$；若$\frac{|a-b|}{\max(1,|b|)}\le10^{-6}$，你的答案被算作正确。

## 说明/提示

$3\le n\le100,n\in\mathbb{Z}$   
$1\le r\le 100$

## 样例 #1

### 输入

```
3 1
```

### 输出

```
6.4641016
```

## 样例 #2

### 输入

```
6 1
```

### 输出

```
1.0000000
```

## 样例 #3

### 输入

```
100 100
```

### 输出

```
3.2429391
```

# 题解

## 作者：HanPi (赞：6)

$\huge update$

* 删除了亿些废话

如图,这是一个当 $n=8$ 时的图,我们将 $8$ 个圆心分别标 $B \sim I$,
连接 $AB,BC,AC$ 构造出 $\triangle ABC$ .
![](https://cdn.luogu.com.cn/upload/image_hosting/qodxunke.png)

由题可知,$AB=AC=r+R , BC=2R , \angle BAC=\frac{360^\circ}{n}$ 

单独看这个三角形,我们做它在 $BC$ 边上的高 $AJ$.
![](https://cdn.luogu.com.cn/upload/image_hosting/qiuud3wf.png)

于是我们可以得到 $Rt\triangle ABJ$ , 且 $\angle BAJ=\frac{180^\circ}{n} , BJ=\frac{BC}{2}=R$

接下来你可以使用 正弦,余弦...各种方式求R,我这里讲我觉得比较简单的正弦做法.

![](https://bkimg.cdn.bcebos.com/pic/7a899e510fb30f2470e16cb2c895d143ad4b0303?x-bce-process=image/resize,m_lfit,w_220,h_220,limit_1)

正弦是直角三角形的对边与斜边之比
如图，斜边为 $r$，对边为 $y$ ，邻边为 $a$ 。斜边 $r$ 与邻边 $a$ 夹角 $\angle A$ 的正弦即为 $sinA=\frac{y}{r}$.

~~摘自百度百科~~

那么可以得到 $\sin \angle BAJ=\frac{AJ}{AB}$
即 $\sin \frac{180^\circ}{n}=\frac{R}{r+R}$,我们只需解方程即可.

**解:**

$(r+R)\times\sin\frac{180^\circ}{n}=R$

$r\times\sin\frac{180^\circ}{n}+R\times\sin\frac{180^\circ}{n}=R$

$r\times\sin\frac{180^\circ}{n}=R-R\times\sin\frac{180^\circ}{n}$

$r\times\sin\frac{180^\circ}{n}=R\times(1-\sin\frac{180^\circ}{n})$

$R=\huge\frac{r\times \sin \frac{180^\circ}{n}}{1-\sin \frac{180^\circ}{n}}$

**代码:**
* 需要注意,C语言的sin函数需要传递的是弧度, 弧度=角度 $\times\pi\div 180^\circ$

```
#include <stdio.h>
#include <math.h>
const double PI =3.141592653589793238462643383279;

double n,r,ans,s;
int main()
{
	scanf("%lf%lf",&n,&r);
	s=sin((180/(double)n)*(PI/180));
	ans=(s*r)/(1-s);
	printf("%.12lf",ans);
	return 0;
}
```


------------
好像不支持 `$$` ,排版可能有点丑 ~~(逃)~~

---

## 作者：ezuyz (赞：4)

本题是道纯数学题，代码很简单。

示意图:

![](https://cdn.luogu.com.cn/upload/image_hosting/5tfnphub.png)

如图所示：

线段 $BD$ 与 $\bigcirc A  \bigcirc C$ 相切，设 $R$ 为大圆的半径，$r$ 为小圆的半径，$n$ 为小圆个数，则 $\angle \alpha = (360 \div n \div 2)^\circ$ ，转化为**弧度制**即为：

$$\pi \cdot 2 \div n \div 2=\frac{\pi}{n}$$ 

由此则可在 $Rt\vartriangle BDC$ 设出 $k=\sin \angle \alpha$，即可得出方程:

$$r=(r+R)\cdot k$$

化简：

$$r=r \cdot k+R \cdot k$$
$$r-r \cdot k=R \cdot k$$
$$r(1-k)=R \cdot k$$

即

$$r=\frac{R \cdot k}{1-k}$$

代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
int main()
{
	double n,r;
	double pi=3.14159265358979323846;
	cin>>n>>r;
	double k=sinf(pi/n);
	printf("%.7lf",r*k/(1-k));
}
```

轻松解决~~

    

---

## 作者：moongazer (赞：3)

写一份比较详细的题解吧

不懂三角函数的先看[这里](https://www.luogu.org/blog/chtholly-willem/san-jiao-han-shuo-ru-men)
## 题意
- 一个半径为$r$的圆，与$n$个半径为$R$的圆相切且这$n$个圆分别和左右的两个圆相切
- 已知$n, r$,求$R$

## 思路
将外圈圆的圆心相连, 围成一个正$n$边形
![不见图，请刷新](https://i.loli.net/2019/01/15/5c3d7322b988e.png)
- 从多边形截出一个$\triangle BGA$
![不见图，请刷新](https://i.loli.net/2019/01/15/5c3d7341e205d.png)
- $\angle BGA=\frac{\angle BGF}{2}=\frac{180^{\circ}-\frac{360^{\circ}}{n}}{2}$
- 做$\triangle BGA \space BG$边上的高$AH$
- 得到$Rt\triangle GHA,GH=R,GA=R+r$
- $\frac{GA}{GH}=\frac{R+r}{R}=\sec\angle BGA$
- $R\cdot \sec\angle BGA=R+r$
- $R\cdot(\sec\angle BGA-1)=r$
- $R=\frac{r}{\sec\angle BGA-1}=\frac{r}{\sec(\frac{180^{\circ}-\frac{360^{\circ}}{n}}{2})-1}$

## 注意事项
1. cmath里没有$\sec$，可以用$\cos$的倒数嘛
2. cmath里面的所有三角函数都是弧度制，要将角度$\times\pi\div180$

## 备注
绘图工具:GeoGebra Geometry
## 代码(C++)
```cpp
int n;
double r;
read(n);
cin>>r;
double degree=180-(360.0/n);
degree/=2;
degree=degree/180*PI;
double ans=r/(1/cos(degree)-1);
cout.precision(7);
cout<<fixed<<ans<<endl;
```


---

## 作者：_bruh_ (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/CF1100C)

## 题目描述
	
有 $ n $ 个半径为 $ R $ 的圆与一个半径为 $ r $ 的圆相切。

且 $ n $ 个圆两两相切。

现给出 $ n $ 与 $ r $ ，求 $ R $ 的值。


------------
## 分析
### 我们看看图
![题目白嫖的图](https://cdn.luogu.org/upload/vjudge_pic/CF1100C/a0c9f6bd15b532673873e8a75fb88103ad5b8775.png)

可以发现，两个外圆的圆心与内圆的圆心可以连成一个**三角形**。

#### 所以我们可以在图中截取一小部分来观察：

![](https://img1.imgtp.com/2022/08/07/soCn061R.png)

首先，我们可以构造这个三角形的高。

不难求出，该三角形的高与斜边的夹角为： 
$ \frac{ 360 \div 2 }{ n } $

转为弧度就是： 
$ \frac{ \pi }{ n } $

我们将数值标上观察。

![](https://img1.imgtp.com/2022/08/07/po3Knhbk.png)

可以发现，我们能够使用~~伟大的~~三角函数来得出其斜边比去对边的值也就是 $ \frac{\text{R}}{\text{R+r}} $ 的值。

然后我们通过变式发现： 

$ \ R $ = $  r \cdot \frac{ R }{ R + r } \div \frac{ ( R + r ) - r }{ R + r } $ = $ \ r \cdot sin(\frac{\pi}{ n }) \div (1-sin(\frac{\pi}{ n })) $ 

接下来奉上极为简短代码：

```cpp
#include<cstdio>
#include<cmath>
int main(){double n,r;scanf("%lf%lf",&n,&r);printf("%.7f",(r*sin((3.1415926535)/n)/(1-sin((3.1415926535)/n))));}
```

~~我不信有比我更短的了。~~

---

## 作者：qiuzijin2026 (赞：1)

# NN and the Optical Illusion

## [题面](https://www.luogu.com.cn/problem/CF1100C)

## 思路

本题数学题。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/fnzuhkcr.png)

由三角函数可知：
 
$$ \because \frac{R}{r+R}=\sin(\alpha) $$ 

$$ \therefore R=(r+R) \times\operatorname{sin}(\alpha)$$ 

$$ \therefore R=r\times\operatorname{sin}(\alpha)+R\times\operatorname{sin}(\alpha)$$ 

$$ \therefore r\times\operatorname{sin}(\alpha)=R\times(1-\operatorname{sin}(\alpha))$$ 

$$ \therefore R=\frac{r\times\operatorname{sin}(\alpha)}{1-\operatorname{sin}(\alpha)}$$ 

而我们知道：

$$ \alpha=360^{\circ}\div(n\times2) $$ 

我们就可以算出 $R$ 了。

注意：STL中 $\operatorname{sin}$ 函数需要传的是弧度, 而弧度=角度 $ \times\pi\div 180^{\circ}$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long double p=3.141592653589793238462643383279;
long double n,r;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%Lf%Lf",&n,&r);
	printf("%.7Lf",sin(360.0/(n*2.0)*(p/180.0))*r*1.0/(1.0-sin(360.0/(n*2.0)*(p/180.0))));
	return 0;
}
```

---

## 作者：rpdg (赞：1)

一道数学题。

我们以 $n=6$ 为例，拿出内圆和两个外圆

![](https://cdn.luogu.com.cn/upload/image_hosting/0qjr3quq.png)

外圆半径就是图中的 $IH$ 或 $FD$。

我们发现，$\angle HAD$ 可以算出来，而它在三角形 $IFA$ 中所对的边是 $IF$，即 $2IH$。

然后我们知道 $IFA$ 一定是一个等腰三角形（因为 $AH=AD$，$DF=IH$，所以 $IA=AF$ ），所以我们可以把 $\angle AIF$ 算出来。

$\angle AIF$ 所对的边是 $IA$，即 $AH+IH$，我们设 $\angle HAD =\alpha ,\angle AIF =\beta ,IH=r,AH=R$，根据正弦定理（不知道的可以看[这里](https://baike.baidu.com/item/%E6%AD%A3%E5%BC%A6%E5%AE%9A%E7%90%86/2657575)）不难列出一个方程

$$
\frac{2r}{sin \alpha}=\frac{R+r}{sin \beta}
$$

解得

$$
r=\frac{R\sin \alpha}{2\sin \beta - \sin \alpha}
$$

至于 $\alpha,\beta$ 怎么算

~~其实我知道大家都知道但我还是要水字数~~

我们把外圆的过它们互相相切的点的半径连起来，就形成了一个正 $n$ 边形。

$\alpha$ 其实就是这个正 $n$ 边形的外接圆的圆心角，$n$ 个这样的角就是一个周角，所以 $\alpha =\frac{2\pi }{n}$，$\beta$ 可以由 $\alpha$ 求得，即 $\frac{\pi - \alpha}{2}$

代码贴一下


```cpp
#include<bits/stdc++.h>
#define pi acos(-1)
using namespace std;
int main() {
    int n,r;
    cin>>n>>r;
    double alpha=2.0*pi/(1.0*n),beta=(pi-alpha)/2.0;
    printf("%.6f",r*1.0*sin(alpha)/(2*sin(beta)-sin(alpha)));
    return 0;
}
```

---

## 作者：天南星魔芋 (赞：1)

~~此题是一道水题。~~


------------
我们先看题：

有一个圆，在其周围摆一圈圆，现已知内圆半径 $r$ ，和外圆个数 $n$ ，你要求出外圆半径 $R$ 。


链接中心圆和两个小圆的圆心，我们发现构成了一个三角形，如图：

![](https://i.loli.net/2020/11/14/jNcJbCSOoLs4ID2.png)


可知 $AJ=AI=r$ , $JE=IC=\frac{EC}{2}=R$ 。

因为大圆外有 $n$ 个小圆，故一个小圆站大圆的圆心角为 $∠EAC$  ，

故 $∠EAC=360°/n$ 。

因为 $K$ 平分 $EC$ 且 $AE=AC(AE=AJ+JE=AI+IC=AC)$ ，

所以 $AK$ 平分 $∠EAC$  $(等腰三角形三线合一)$  。

故 $∠EAK=\frac{∠EAC}{2}=\frac{360}{2n}$  。

因为 $sin∠EAK=\frac{EK}{EJ+AJ}$ ，

所以 $\frac{1}{sin∠EAK}=\frac{EJ+AJ}{EK}=\frac{AJ}{EJ}+1$ ,  $\frac{1}{sin∠EAK}-1=\frac{AJ}{EJ}$

故 $R=EJ=\frac{AJ}{\frac{1}{sin∠EAK}-1}$ $=$ $\frac{r}{\frac{1}{sin(\frac{360}{2×n})}-1}$ 。

但还有个坑，电脑中的 $sin$  用的是 $弧度$ 。

也就是 $\frac{∠EAC}{180}×π=\frac{π×2}{n}$ 。

接下来就上代码吧：



```cpp

/*
建议 C++17
*/
#include<bits/stdc++.h>
using namespace std;
long double n,r;
long double a;
int main(){
	cin>>n>>r;//π 精确到14位
	a=3.14159265358979*2/n;//∠EAC对应的弧度
	a/=2;//∠EACK应的弧度
	a=sinf(a);//sin 值 sinf 可以更精确
	a=1/a;//注意：
	a=a-1;//是先乘后减。
	a=r/a;
	printf("%.8Lf",a);// %.8Lf 精确小数点后八位
}
```



这篇题解就到这里了，如有不足请大家多多指教。



---

## 作者：da32s1da (赞：1)

考虑中间的圆和外面相邻的两个圆。

连接外面相邻两个圆的圆心$O_1O_2$，连接中间的圆和外面的一个圆的圆心$OO_1$。作$O_1O_2$的中点$P$，连接$OP$。由三角函数的有关知识得到$\sin \angle O_1OP=\frac{r+Ans}{Ans}$。而$\angle O_1OP=\frac{\pi}{n}$。

所以答案为$$Ans=\frac{\sin\frac{\pi}{n}\cdot R}{1-\sin\frac{\pi}{n}}$$

```
#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
typedef double D;
const D pai=3.141592653589793238462643383279;
D n,r,ans;
int main(){
	scanf("%lf%lf",&n,&r);
	ans=sin(pai/n);
	printf("%.12f\n",ans*r/(1.0-ans));
}
```

---

## 作者：decoqwq (赞：1)

余弦定理

大圆和任意两个相切的小圆得三个圆心组成一个三角形，设大圆半径为$R$，小圆半径为$r$，有$k$个外切圆

那么由余弦定理，得到$2r=\sqrt{2(r+R)^2-2(R+r)^2cos(360/k)}$

解方程即可

不给代码啦

---

## 作者：封禁用户 (赞：0)

# CF1100C NN and the Optical Illusion 题解

[题面](https://www.luogu.com.cn/problem/CF1100C)

## 思路

此题数学题

如图（盗的）：

![](https://cdn.luogu.com.cn/upload/image_hosting/fnzuhkcr.png)

需要用到三角函数，不懂自己 bdfs 。

$
\because \frac{ R }{ R + r } = \sin ( \alpha )
$

$
\therefore R = ( R + r ) \times \sin ( \alpha )
$

$
\therefore R = r \times \sin ( \alpha ) + R \times \sin ( \alpha )
$

$
\therefore r \times \sin ( \alpha ) = R \times (1 - \sin ( \alpha ) )
$

$
\therefore R = \frac { r \times \sin ( \alpha ) } { 1 - \sin ( \alpha ) }
$

因为我们知道：$ \alpha = \frac { 360 ^ \circ } { 2 \times n } $

所以我们就可以算出答案了。

## 注意

STL 中的 $\sin$ 函数需要传的是弧度，弧度 $=$ 角度 $\times \ \pi \  \div \  180 ^ \circ$ 所以还需要再定义一个 pi 取到 3.141592653589793238462643383279 就可以了。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
//#define double long double
#define il inline
#define endl '\n'
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
#define abs(x) (x<0?-x:x)
#define fast_io ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

const long double p=3.1415926535897932384626433832795028841971;
long double n,r;

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%Lf%Lf",&n,&r);
	printf("%.7Lf\n",sin(360.0/(n*2.0)*(p/180.0))*r*1.0/(1.0-sin(360.0/(n*2.0)*(p/180.0))));
	return 0;
}
```


---

## 作者：nxd_oxm (赞：0)

~~水社贡ing~~
# 题意
数学题啊，没啥好说的。
# 思路
看下示意图吧。

![](https://cdn.luogu.com.cn/upload/image_hosting/velljxsf.png?x-oss-process=image/resize,m_lfit,h_340,w_450)


小学二年级我们学过的三角函数可以解啊：

$$\because \dfrac{R}{R+r} = \sin ( \alpha )$$

$$\therefore R = \sin ( \alpha ) \times (R+r)  $$


$$\therefore R = r \times \sin ( \alpha) + R \times\sin (\alpha)$$

$$\therefore r \times \sin(\alpha) = R \times (1-\sin(\alpha))$$

$$\therefore R = \dfrac {r \times \sin (\alpha)}{1-\sin(\alpha)}$$

而我们由图可得，

$$\alpha =  360 \div (n \times 2)$$ 

那 $R$ 就可以算出来啦~

注意：$\sin$ 函数是弧度，并不是角度哦。

要转一下。

（弧度=角度 $\times \pi \div 180$）

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const long double pi=3.141592653589793238462643383279;
long double n,r;
signed main(){
	scanf("%Lf%Lf",&n,&r);
	printf("%.7Lf",sin(360.0*(pi/180.0)/(n*2.0))*r*1.0/(1.0-sin(360.0*(pi/180.0)/(n*2.0))));
	return 0;
}
```

---

## 作者：FiraCode (赞：0)

## 题解思路：
图就是一个内接圆，外面有一圈外接圆。

外接圆有 $n$ 个。

我们就设内接圆的半径为 $r$ 外接圆的半径为 $R$

如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/pudihqr8.png)

然后我们随便挑两个圆来看，首先我们先把圆心连起来，因为这 $n$ 个圆是相等的，所以他是等腰三角形，用两个外接圆的重合的那个点和内接圆的圆心连起来就是和外接圆的圆心连起来的边是垂直的，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/7qpld3vu.png)

而在圆心里的哪个角我们能求出来，因为 $n$ 个这样的角组成了一个圆，所以他的角度为：$\frac{2\pi}{n}$。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ipyq9exy.png)

那么这个角的一半就是： $\frac{\pi}{n}$。

那么 $\frac{R}{R + r} = \sin \frac{\pi}{n} \longrightarrow R = \frac{r \sin\frac{\pi}{n}}{1 - \sin \frac{\pi}{n}}$。

公式好了，就可以写代码了！

## AC CODE:
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const double PI = 3.1415926;
double n , r;
int main() {
    cin >> n >> r;
    printf ("%.7lf\n" , (double)(r * sin (PI / n)) / (1.0 - sin (PI / n)));//直接套用公式即可
    return 0;
}
```
码字不易，求赞！

---

## 作者：Erusel (赞：0)

我们可以画个图

从图中我们可以取出一个直角三角形

![2333](https://cdn.luogu.com.cn/upload/pic/65128.png)

可以发现这个直角三角形的两条直角边分别为$R+r$和$r$

因此，我们只要求出中间的夹角

$R+r$和$r$之间的夹角为正$n$边形内角和$/n$的一半

所以$\frac{r}{R+r}=cos\alpha$

$r=R*cos\alpha*(1-cos\alpha)$

代码：

```
#include<bits/stdc++.h>

#define rd(x) x=read()

#define PI acos(-1.0)

using namespace std;

double n,r;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

int main()
{
	cin>>n>>r;
	double t=PI*(n-2)/n;//计算角度
	printf("%.8lf\n",r*cos(t/2)/(1-cos(t/2)));//求答案
	
    return 0;
}


```

---

