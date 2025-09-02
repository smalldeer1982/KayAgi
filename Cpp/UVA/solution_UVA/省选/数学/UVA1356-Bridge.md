# Bridge

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4102

[PDF](https://uva.onlinejudge.org/external/13/p1356.pdf)

# 题解

## 作者：jdsb (赞：8)

## 题意
有一条长度为 $B$ 的桥，要在桥上建若干高度为 $H$ 的电线杆，使得相邻两根电线杆之间的距离小于等于 $D$ 且相等，相邻两根电线杆有电线连接，电线的总长为 $L$，要求电线最低点与地面的距离。
## 分析
- 首先考虑贪心，电线杆建得越多，两根电线杆直接的电线长度就越短，与地面的距离就越远，所以我们要尽可能的少建电线杆，电线杆的最小数量 $n=\lceil \frac BD \rceil$，相邻电线杆的距离 $d=\frac {B}{n}$，电线长度 $l=\frac {L}{n}$。

- 电线就是一条抛物线，不妨设左端点为原点，并且将电线上翻，则这条抛物线的解析式 $f(x)=ax^2$ ，设它的顶点纵坐标为 $h$，因为总宽度为 $d$ ，所以顶点坐标为 $(\frac d2,h)$ ，带入可得 $a=\frac{4h}{d^2}$，因为高度 $h$ 具有单调性，所以我们可以二分高度，然后判断此时的电线长度是否小于等于 $l$ 即可。

- 接下来是数学分析，考虑如何求一个可导函数 $[a,b]$ 范围内的弧长，弧长公式为 
$$ \int_{a}^{b} \sqrt{1+f'(x)^2} \,dx $$
- 设函数上两点 $P$，$P'$，则这两点距离 $PP'=\sqrt{(\Delta x)^2+(\Delta y)^2}$，当 $PP'$ 的距离趋于无穷小(极限)时，有 $ds=\sqrt{(dx)^2+(dy)^2}$，根据 $ dy=f'(x)\times dx $，化简后可得上式。

- 所以弧长即为 $2\times \int_{0}^{\frac{d}2} \sqrt{1+4a^2x^2} \,dx$，用自适应辛普森法模拟即可。结合上面二分即可求出最大的 $h$，答案即为 $H-h$。
## 一些细节
- 本题多组数据，且输出要注意格式，详细可以参考我代码。
## 代码
```cpp
#include<iostream>
#include<math.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') { if(c=='-') f=-1;c=getchar(); }
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^'0'),c=getchar();
	return x*f;
}
double a;
inline double f(double x){
	return sqrt(1+4*a*a*x*x);
}
inline double simpson(double l,double r){
	double mid=((l+r)/2);
	return (f(l)+f(r)+4*f(mid))*(r-l)/6;
}
double asr(double l,double r,double eps,double res){
	double mid=((l+r)/2);
	double x=simpson(l,mid),y=simpson(mid,r);
	if(fabs(x+y-res)<=15*eps) return x+y+(x+y-res)/15;
	return asr(l,mid,eps/2,x)+asr(mid,r,eps/2,y);
}
const double eps=1e-9;
double D,H,B,L,W;
double check(double h){
	a=4*h/(W*W);
	return asr(0,W/2,eps,simpson(0,W/2))*2;
}
int main(){
	int T=read(),t=0;
	while(T--){
		D=read(),H=read(),B=read(),L=read();
		int n=(B-1)/D+1;
		W=B/n,L=L/n;
		double l=0,r=H;
		while(r-l>eps){
			double mid=(l+r)/2;
			if(check(mid)<=L) l=mid;
			else r=mid;
		}
		printf("Case %d:\n%.2lf\n",++t,H-l);
		if(T) puts("");
	}
	return 0;
}
```


---

## 作者：da32s1da (赞：2)

这里就讲一下为什么使用**Simpson**时，二分高度后调整$a=\frac{4h}{W^2}$，以及被积函数是$f(x)=\sqrt{1+4a^2x^2}$。

-----

- $a=\frac{4h}{W^2}$

假设抛物线在原点，有宽度$W$，高度$H$。故有点$(\frac{W}{2},H)$在抛物线上，带入$y=ax^2$，得到$a=\frac{4h}{W^2}$

-----

- $f(x)=\sqrt{1+4a^2x^2}$

把抛物线分成很多小段，长度$L=2\int_{0}^{\frac{W}{2}}\sqrt{(dx)^2+(dy)^2}$。

考虑$dy=y'\times dx$

$$L=2\int_{0}^{\frac{W}{2}}\sqrt{1+(y')^2}dx=2\int_{0}^{\frac{W}{2}}\sqrt{1+4a^2x^2}dx$$

~~式子不知道写的对不对~~

代码就不给啦qwq

---

## 作者：AlexandreLea (赞：1)

# 题意简述
有若干根高定值 $h$ 的电线杆，相邻两根距离不超过定值 $d$，在电线杆之间是全等的抛物线电线，总长为定值 $l$。电线杆之间的距离和为定值 $b$，求电线杆数目最小最下端离地的高度 $y$。

# 题目思路
很明显，如果电线杆数目最小，我们就要插 $n=\lceil\dfrac{b}{d}\rceil$ 根电线杆，于是每个间隔宽度即为 $d_0=\dfrac{b}{n}$ 而每节电线长度为 $l_0=\dfrac{l}{n}$。

现在，我们的任务是根据 $d_0$ 和 $l_0$ 计算 $y$ 然而这似乎行不通，因此我们考虑正难则反，计算高度为 $h$ 而间隔为 $w$ 的抛物线长度 $p(w,h)$，现在我们解方程 $p(d_0,x)=l_0$ 并计算 $y=h-x$。

在这里注意到 $x$ 上升时 $p(d_0,x)$ 单调递增，于是我们二分。最大的困难就在于 $p(w,h)$。

在微积分中弧长公式即为

$$\int_{a}^{b}{\sqrt{1+(f'(x))^2}\mathrm dx}$$

现在我们要搞出 $f(x)$ 以及其导函数 $f'(x)$。现在设抛物线的最低点交于 $(0,0)$ 而两侧最高点分别交于 $\left(-\dfrac{2}{w},h\right)$ 以及 $\left(\dfrac{2}{w},h\right)$。由于抛物线最低点为顶点，因此函数 $f(x)=ax^2$；根据前面两点，得出 $a=\dfrac{4h}{w^2}$。而后，我们即可带入：

$$=\int_{-w/2}^{w/2}\sqrt{1+4ax^2}\mathrm dx$$

由于对称性，我们既可以再次简化：

$$=2\int_{0}^{w/2}\sqrt{1+4ax^2}\mathrm dx$$

如何求上述积分？积分表里这样写道：

$$\int\sqrt{x^2+a^2}\mathrm dx=\dfrac{x\sqrt{x^2+a^2}+a^2\ln|x+\sqrt{x^2+a^2}|}{2}+C$$

于是我们再度简化上式

$$=4a\int_{0}^{w/2}\sqrt{\left(\dfrac{1}{2a}\right)^2+x^2}\mathrm dx$$

然后就不带入了。这里放出程序：

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
double F(double a,double x){
    double a2=a*a,x2=x*x;
    return (x*sqrt(x2+a2)+a2*log(x+sqrt(x2+a2)))/2.0;
}
double p(double w,double h){
    double a=4*h/(w*w),b=1.0/(2*a);
    return 4*a*(F(b,w/2)-F(b,0));
}
int main(){
    int t,_=0;
    cin>>t;
    while(t--){
        double d,h,b,l,d1,l1,x,y;
        cin>>d>>h>>b>>l;
        int n=(b+d-1)/d;
        d1=b/n,l1=l/n,x=0,y=h;
        while(y-x>1e-7){
            double m=(x+y)/2;
            if(p(d1,m)<l1) x=m;
            else y=m;
        }
        if(_!=0) cout<<endl;
        cout<<"Case "<<(++_)<<":"<<endl<<fixed<<setprecision(2)<<h-x<<endl;
    }
    return 0;
}
```

**EOF**

---

## 作者：CmsMartin (赞：1)

# 前置芝士 Simpson 公式

我看到题解中没有一篇认真讲过辛普森公式，于是就来水一篇题解。

### 基本思想

**将函数近似看做二次函数**

~~由于这个原因，这个公式及其的简单且不精确。~~

### 公式推导

$$\int_a^b f(x) dx$$

上方是最最基础的微积分求面积的公式；

刚刚的思想中讲到了思路是将 $f(x)$ 看做 $ax^2 + bx + c$ ,于是有:

$$= \int_a^b (Ax^2+Bx+C)dx$$
$$ \approx \int_a^b (\frac{Ax^2}{3} + \frac{Bx}{2} + \frac{C}{1})$$
$$= \frac{Ab^3}{3} - \frac{Aa^3}{3} + \frac{Bb ^2}{2} - \frac{Ba ^ 2}{2} + Cb - Ca$$
$$= \frac{2Ab^3 - 2Aa^3 + 3Bb^2 - 3Ba^2 + 6b - 6CaC}{6}$$
$$= \frac{2A(a^3 - b^3) +3B(b^2 - a^2) + 6C(b-a)}{6}$$
$$= \frac{2A(b-a)(a^2 + b^2 + ab) + 3B(a + b)(b-a) + 6C(b-a)}{6}$$
$$= \frac{(b-a)(2Aa^2 + 2Ab^2 + 2Aab + 3Ba + 3Bb + 6C)}{6}$$
$$= (b-a)\frac{(Aa^2 + Ba + C) + (Ab^2 + Bb + C) + (Aa^2 + Ab^2 + 2Ba + 2Bb + 2Aab + 4C)}{6}$$
$$= (b-a)\frac{f(a) + f(b) + 4(\frac{Aa^2}{4} + \frac{Ab^2}{4} + \frac{Ba}{2} + \frac{Bb}{2} + \frac{2Aab}{4} + C)}{6}$$
$$= (b-a)\frac{f(a) + f(b) + 4(\frac{Aa^2 + Aab}{4} + \frac{Ab^2 + Aab}{4} + \frac{Ba + Bb}{2} + C)}{6}$$
$$= (b-a)\frac{f(a) + f(b) + 4(A\frac{a(a + b)}{4} + A\frac{b(a + b)}{4} + B\frac{a +b}{2} + C)}{6}$$
$$= (b-a)\frac{f(a) + f(b) + 4(A\frac{(a + b) ^ 2}{4} + B\frac{a +b}{2} + C)}{6}$$
$$= (b-a)\frac{f(a) + f(b) + 4f(\frac{a + b}{2})}{6}$$
所以，我们得到：
$$\int_a^b f(x) dx \approx (b-a)\frac{f(a) + f(b) + 4f(\frac{a + b}{2})}{6}$$

### 处理精度问题

**为了控制精度，以及不必要的问题，保留两位小数时 eps 一般取 $10^{-6} \sim 10^{-8}$。**

有了 Simpson 公式，一个自然的想法是把积分区间拆成多个小区间后求和。

但是分成区间的个数和长度因积分区间和精度要求甚至被积函数而异。

换句话说，分的区间数太少不满足精度要求，太多了会 TLE 。

「自适应」就是求积分时能够自动控制切割的区间大小和长度，使精度能满足要求。

具体地： `solve(l , r)` 表示求 $\int_r^l f(x)dx$
1. 取 `mid = l+r >> 1`;
2. 用 Simpson 公式近似计算 $f(x)$ 在区间 $[l,mid]$ 和区间 $[mid,r]$ 内的积分，分别为 $l_s$ 和 $r_s$ ，及 $[l,r]$ 的近似积分 $sum$ ;
3. 如果 $l_s + r_s$ 与 $sum$ 的误差允许(即在 eps 之内)，则返回 $sum$ ;
4. 否则递归 `solve(l , mid)` 和 `solve(mid , r)` ，返回这两个递归计算结果的和;

摘自 [这篇博文](https://blog.csdn.net/xyz32768/article/details/81392369)。

## 分析

其实电线杆的数量可以贪心，即为 $\lceil\frac{n}{d}\rceil$, 然后使用弧长公式加辛普森乱搞就出来了

**公式**
$$f(x) = \sqrt{1 + 4a^2x^2}$$

## 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;

double a;

double Function (double x) {
    return sqrt(1 + 4 * a * a * x * x);
}

double Solve (double l , double r) {
    double mid = (l + r) / 2;
    return (Function(l) + Function(r) + Function(mid) * 4) * (r - l) / 6;
}

double Simpson (double l , double r , double eps , double res) {
    double mid = (l + r) / 2;
    double x1 = Solve(l , mid) , x2 = Solve(mid , r);
    if(abs(x1 + x2 - res) <= 15 * eps) return x1 + x2 + (x1 + x2 - res) / 15;
    else return Simpson(l , mid , eps / 2 , x1) + Simpson(mid , r , eps / 2 , x2);
}

const double eps = 1e-9;

double D , H , B , L , W;
int T;

double Check(double x) {
    a = 4 * x / (W * W);
    return Simpson(0 , W / 2 , eps , Solve(0 , W / 2)) * 2;
}


int main() {
    scanf("%d" ,&T);
    for(int i = 1; i <= T; i++) {
        cin >> D >> H >> B >> L;
        double l = 0 , r = H;
        int n = (B - 1) / D + 1;
        W = B / n;
        L = L / n;
        while(r > l + eps) {
            double Mid = (l + r) / 2;
            if(Check(Mid) <= L) {
                l = Mid;
            }
            else r = Mid;
        }
        printf("Case %d:\n%.2lf\n" ,i , H - l);
        if(i != T) {
        	printf("\n");
		}
    }
    return 0;
}
```

---

## 作者：二叉苹果树 (赞：1)

### 介绍下辛普森公式

首先明确题意，其实本题就是积分的计算.

本题是个抛物线，可以直接积分，如第一篇题解.但是对于一些无法积分的函数，辛普森公式可以简单地解决问题.当然，辛普森公式也适用于本题这种可积的函数.

若要计算 $f(x)$  下的阴影面积（定积分的几何意义），考虑将阴影部分的水平长度均分，再垂直划分阴影区域.



于是可以得到

$$\int_{a}^{b}f(x)\,dx\approx\frac{\Delta x}{3}(y_0+4y_1+y_2)+\frac{\Delta x}{3}(y_2+4y_3+y_4)+···+\frac{\Delta x}{3}(y_{n-2}+4y_{n-1}+y_n)$$

但是，近似程度越高时，计算量也越大，于是，辛普森公式有一个变种，称为自适应辛普森法，只需要设置一个精度阈值，算法便可以递归地划分区间.也就是在容易近似的地方少划几份，不容易近似的地方多划几份.

代码实现如下

```cpp
#include<cstdio>
#include<cmath>

double a;

double F(double x)
{
    return sqrt(1+4*a*a*x*x);
}

double simpson(double a,double b)
{
    double c=a+(b-a)/2;
    return (F(a)+4*F(c)+F(b))*(b-a)/6;
}

double asr(double a,double b,double eps,double A)
{
    double c=a+(b-a)/2;
    double L=simpson(a,c),R=simpson(c,b);
    if(fabs(L+R-A)<=15*eps)
        return L+R+(L+R-A)/15.0;
    return asr(a,c,eps/2,L)+asr(c,b,eps/2,R);
}

double asr(double a,double b,double eps)
{
    return asr(a,b,eps,simpson(a,b));
}

double parabola_arc_length(double w,double h)
{
    a=4.0*h/(w*w);
    return asr(0,w/2,1e-5)*2;
}
int main()
{
    int T;
    scanf("%d",&T);
    for(int kase=1;kase<=T;kase++)
    {
        int D,H,B,L;
        scanf("%d%d%d%d",&D,&H,&B,&L);
        int n=(B+D-1)/D;
        double D1=(double)B/n;
        double L1=(double)L/n;
        double x=0,y=H;
        while(y-x>1e-5)
        {
            double m=x+(y-x)/2;
            if(parabola_arc_length(D1,m)<L1)
                x=m;
            else
                y=m;
        }
        if(kase>1)
            printf("\n");
        printf("Case %d:\n%.2lf\n",kase,H-x);
    }
    return 0;
}
```


---

## 作者：Lyccrius (赞：0)

塔高为 $H$，桥长度为 $B$，绳索总长为 $L$，相邻两座塔之间的距离不能超过 $D$，求建最少的塔时伸缩的最下端离地面的高度 $y$。

塔的个数最小时，间隔数为 $n = \lceil \frac{B}{D} \rceil$，每个间隔宽度 $d = \frac{B}{n}$，每段绳索长度 $l = \frac{L}{n}$。

设宽度为 $w$，高度为 $h$ 的抛物线的长度为 $p(w, h)$，求解关于 $h$ 的方程 $p(d, h) = l$，然后计算 $y = H - h$。

由于 $p(w, h)$ 关于 $h$ 单调，所以可以二分求解。

可导函数 $f(x)$ 在区间 $[a, b]$ 的弧长为

$$
\begin{aligned}
& \int_a^b \sqrt{1 + f'(x)^2} dx \\
= & \int_a^b \sqrt{1 + 4 a^2 x^2} dx
\end{aligned}
$$

于是可以用自适应辛普森法求解。

---

## 作者：__stick (赞：0)

update: 积分过程被同学拍砖了，已经重构整个积分部分。

# 题意

给出一座长为 $B$ 的桥，要在桥上建造若干个高为 $H$ 的杆子，间距小于等于 $D$ 且完全相等，使相邻两杆子之间使用线相连，且线的长度为 $L$ ，求问线最低点离桥面有多高。

# 分析

首先 ~~由生活经验可知~~ 两根杆子距离越远，它们之间的线就会拉的越紧，所以我们要尽量减少杆子数量，由于有限制距离小于等于 $D$，所以我们最多只能放 $n=\lceil \frac{B}{D}\rceil $ 个杆子，现在的关键问题就在于如何求出最低点距离桥面的距离。

由于直接借出轨迹很难，我们考虑使用方程的思想，设出这个最小距离 $h$，然后求出抛物线上对应路径长即可。由于每一段都是相同的，我们只分析一段即可。

首先以桥面为 $x$ 轴，最低点所在处经过的竖直线为 $y$ 轴建系。为后文分析方便，我们记两个杆子间距离为 $d$，线的长度为 $l$。设抛物线方程为: $y=ax^2+h$，由于过点 $(\frac{d}{2},H)$，所以解得方程为：

$$y=\frac{4(H-h)}{d^2}x^2+h$$

由于可导函数 $y=f(x)$ 在区间 $[a,b]$ 之间的弧长为： $\int_a^b\sqrt{1+(f^{\prime }(x))^2}\mathrm{d}x$，这里就不证明了。带入柿子.令 $a=\frac{8(H-h)}{d^2}$，发现这个题的长度就是:

$$\int_{-\frac{d}{2}}^{-\frac{d}{2}}\sqrt{1+(ax)^2}\mathrm{d}x$$


这玩意应该是可积的，让我们先求不定积分：$F(x)=\int\sqrt{1+(ax)^2}\mathrm{d}x+C$，则：$\int_{-\frac{d}{2}}^{-\frac{d}{2}}\sqrt{1+(ax)^2}\mathrm{d}x=F(\frac{d}{2})-F(-\frac{d}{2})$。

发现 $a$ 的位置不太对，尝试令 $a=\frac{1}{a}$，则变成了：

$$\frac{1}{a}\int_{-\frac{d}{2}}^{-\frac{d}{2}}\sqrt{a^2+x^2}\mathrm{d}x$$

首先尝试分步积分：

$$\int\sqrt{a^2+x^2}\mathrm{d}x=x\sqrt{a^2+x^2}-\int{\frac{x^2\mathrm{d}x }{\sqrt{a^2+x^2}}}$$

$$=x\sqrt{a^2+x^2}-\int{\frac{x^2+a^2-a^2 }{\sqrt{a^2+x^2}}\mathrm{d}x}$$
$$=x\sqrt{a^2+x^2}-\int\sqrt{a^2+x^2}\mathrm{d}x+a^2\int \frac{\mathrm{d}x}{\sqrt{a^2+x^2}}$$

即：

$$2\int\sqrt{a^2+x^2}\mathrm{d}x =x\sqrt{a^2+x^2}+a^2\int \frac{\mathrm{d}x}{\sqrt{a^2+x^2}}$$

又令 $x=a\tan t$，则 $\frac{\mathrm{d}x}{\mathrm{d}t}= a \sec^2 t$
，所以：
$$\int \frac{\mathrm{d}x}{\sqrt{a^2+x^2}}=\int \frac{a\sec^2 t \mathrm{d}t}{\sec t}=\int \sec t \mathrm{d}t=\ln|a\sec t+a\tan t|+C$$

代入 $t=\frac{\arctan x}{a}$，得：

$$\int \frac{\mathrm{d}x}{\sqrt{a^2+x^2}}=\ln|x+\sqrt{a^2+x^2}|+C$$

ps：本来要讨论正负性的，这里略去。

于是有：

$$F(x)=\frac{x}{2a}\sqrt{a^2+x^2}+\frac{a}{2} \ln|x+\sqrt{a^2+x^2}|+C$$



带入 $a=\frac{d^2}{8(H-h)}$ ,即可获得原函数，后面就不用我说了吧，就是经典二分了。

# 代码

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void cmax(T& a,const T& b){a<b?a=b:0;}
template<typename T>
inline void cmin(T& a,const T& b){b<a?a=b:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define X first
#define Y second
#define mp make_pair
const int mod=998244353;
const int MAXN=1e6+10;
int main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(2);
	int T;cin>>T;int I=0;
	while(T--)
	{
		I++;
		cout<<"Case "<<I<<":\n";
		double H,D,B,L,l,r,lx,rx;
		cin>>D>>H>>B>>L;
		int n=(B+D-1)/D;
		double D1=1.0*B/n,L1=(double)L/n;
		auto F=[&](double a,double x)->double
		{
			double a2=a*a,x2=x*x;
			return x*sqrt(x2+a2)/(2*a)+a*log(fabs(x+sqrt(a2+x2)))/2;
		};
		auto getlen=[&](double w,double h)
		{
			double a=(w*w)/(8*h);
			return (F(a,w/2)-F(a,-w/2));
		};
		l=0,r=H;
		while(r-l>1e-6)
		{
			double mid=(l+r)/2;
			if(getlen(D1,mid)<L1)l=mid;
			else r=mid;
		}
		cout<<H-l<<'\n';
		if(T)cout<<'\n';
	}
	return 0;
}
```




---

