# Not So Simple Polygon Embedding

## 题目描述

The statement of this problem is the same as the statement of problem C1. The only difference is that, in problem C1, $ n $ is always even, and in C2, $ n $ is always odd.

You are given a regular polygon with $ 2 \cdot n $ vertices (it's convex and has equal sides and equal angles) and all its sides have length $ 1 $ . Let's name it as $ 2n $ -gon.

Your task is to find the square of the minimum size such that you can embed $ 2n $ -gon in the square. Embedding $ 2n $ -gon in the square means that you need to place $ 2n $ -gon in the square in such way that each point which lies inside or on a border of $ 2n $ -gon should also lie inside or on a border of the square.

You can rotate $ 2n $ -gon and/or the square.

## 样例 #1

### 输入

```
3
3
5
199```

### 输出

```
1.931851653
3.196226611
126.687663595```

# 题解

## 作者：皎月半洒花 (赞：26)

设所求为正 $n$ 边形。那么这个 `version` 就是  $n=4k+2$ 的 case。


这个需要一定的猜测…首先观察样例给出的 $1.931851653$ 这个数，通过百度搜索/自己猜测/计算器瞎按都可以得到，$1.931851653^2=\sqrt{2+\sqrt 3}=\sqrt{\frac{\sqrt 2+\sqrt 6}{2}}=\sqrt {\cot \frac{\pi}{12}}$ 。那么根据这个不难知道六边形的时候是怎么放的：

![](https://cdn.luogu.com.cn/upload/image_hosting/ucvdrdls.png)

于是不难猜出，对于正 $4k+2$ 变形，一定是四条边上各有一顶点，且对角线上有对称的两个顶点，这种方法可以最优。

考虑怎么计算边长，考虑与最底下这条正方形边相切的点 $Z$ 。

![](https://cdn.luogu.com.cn/upload/image_hosting/wgcvccnb.png)

不难知道它一定是离大小为 $\dfrac{\pi}{4}$ 的角 $\angle UE_1F_1$ 最近的那个点。因为 $Z$ 和 $W$ 之间还有好多点，于是设 $\angle UE_1Z$ 为 $\frac{m\pi}{2\cdot k+1}$，那么 

$$
\angle ZE_1F_1=|\frac{m\pi}{2\cdot k+1}-\frac{\pi}{4}|
$$

可以得到最小为 $\dfrac{\pi}{8\cdot k+4}$ 。于是考虑致力于用这角来解出 $|E_1F_1|$。

考虑这个正多边形的外接圆，设其半径为 $r$。那么根据正弦定理可以得到
$$
1=2\cdot r\cdot \sin\frac{\pi}{4\cdot k+2}
$$
同时设正方形边长为 $a$，根据小直角三角形 $\triangle E_1F_1Z$ 可以得到
$$
\frac{a}{2}=r\cdot \cos \dfrac{\pi}{8\cdot k+4}
$$
可以解得最后
$$
a=\frac{1}{2\sin\frac{\pi}{4\cdot k+2}}
$$
复杂度均为 $O(1)$ 。

---

## 作者：youdu666 (赞：3)

### 思路：实数三分

蒟蒻我不会什么神秘的式子，于是就只会三分这个多边形转过的角度，来计算外接正方形的边长。

发现如果不限制转过角度的最大值，会导致长度不是一个单峰函数，不好搞。可以想到正 $n$ 边形每转过 $(360/n)^{\circ}$ 就相当于没有旋转，于是可以把该值当做三分的上界，即可得到一个单峰函数。

于是就可以每次把多边形旋转一个角度，考虑如何计算正方形的边长。可以先计算出多边形每一个顶点到该多边形中心的距离，然后用三角函数计算可以得出外接正方形的宽与高。具体的计算方法可以看代码。

### 代码

```
#include <bits/stdc++.h>
#define double long double
#define int long long
using namespace std;
const double pi=acos(-1),eps=1e-15;//acos(-1)=π
int n;
double kl,d;
inline double chk(double st)
{
	double sst=st;
	st+=90-(kl/2.0);
	st=(st/180.0)*pi;//角度转弧度
	sst=(sst/180.0)*pi;
	double res1=sin(st)*d*2;//外接正方形的高，相当于是从最顶上的点作了一条垂线，垂直于正方形的宽
	double res2=cos(sst)*d*2;//外接正方形的宽，可以直接用cos(sst)算出宽的一半与中心距离的比值
	return max(res1,res2);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=0;
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		kl=360.0/(double)(2*n);
		double rd=(180.0-kl)/2.0;
		rd=(rd/180.0)*pi;
		d=0.5/cos(rd);//计算到中心的距离
		double l=0.0,r=kl-eps,mid=0.0,ans=d;
		while(l+eps*2.0<=r)//实数三分，个人还是喜欢用二分的写法实现，其实道理是一样的，都可以求单峰的极值
		{
			mid=(l+r)/2.0;
			double s1=chk(mid),s2=chk(mid+eps);
			if(s1>s2)ans=s2,l=mid+eps;
			else ans=s1,r=mid-eps;
		}
		printf("%.9Lf\n",ans);
	}
}
```


---

## 作者：Yyxxxxx (赞：3)

![](https://cdn.luogu.com.cn/upload/image_hosting/9lznvq2h.png?x-oss-process=image/resize,m_lfit,h_1000,w_2250)

如图为$n=3$时的情况，为一个正六边形，它的边长为 $EH=ED\cdot \sin\angle EDH$   
因为$\angle EDH$是$\triangle CDB$的外角  
即$\angle EDH=\angle DCB+\angle CBD$，$\angle CBD$是正方形中心与角的连线，所以有定值$\angle CBD=45^{\circ}=\dfrac{\pi}{4}$

而角$\angle DCB=\dfrac{1\times180^{\circ}}{6}$即$\dfrac{(n/2)\times2\pi}{2n}$

综上，
$$EH=ED\cdot\sin\angle EDH$$
$$EH=\dfrac{1}{\sin\dfrac{\pi}{2n}}\cdot\sin(\dfrac{\dfrac{n}{2}\times \pi}{2n}+\dfrac{\pi}{4})$$
$$EH=\dfrac{sin(\dfrac{\dfrac{n}{2}\times \pi}{2n}+\dfrac{\pi}{4})}{\sin\dfrac{\pi}{2n}}$$

$\Theta(1)$
```cpp
#include<bits/stdc++.h>
using namespace std;
const double Pi=acos(-1);
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		printf("%.8lf\n",sin((n/2)*Pi/2/n+Pi/4)/sin(Pi/2/n));
	}
} 
```


---

## 作者：HenryHuang (赞：2)

简要题意：给定一个正 $2n$ 边形，求最小的能将其完全覆盖的正方形的边长。

个人在考场上的思路是，联系作圆内接正多边形求圆周率的过程，内接正多边形的外接圆是不变的。用类似的方式将正 $2n$ 边形扩展为正 $4n$ 边形，然后按照前一题计算即可。

~~（还好样例给的良心）~~

晚上和同学讨论还得到根据对称性进行旋转同样可以得到答案。

剩下的就是计算变换后正 $4n$ 边形的边长和边心距了。这里直接将两个正多边形的外接圆圆心与顶点连接，在一个小的三角形里计算即可。

大概图是这样的

![](https://cdn.luogu.com.cn/upload/image_hosting/yvm8zmqg.png)

注意上面描述的 $n$ 与题目给出的 $n$ 有不同。

注意本算法由于大量三角函数的使用精度丢失较为严重。

贴代码：

```cpp
/*---Author:HenryHuang---*/
#include<bits/stdc++.h>
#define pi 3.1415926535
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;cin>>T;
	cout<<setprecision(6)<<fixed;
	while(T--){
		int n;cin>>n;
		n<<=2;
		double tmp=2.0/2*tan(1.0*(n-2)*pi/(2*n));
		n>>=1;
		double tmp2=1/(2*sin(pi/n));
		tmp2*=sin(pi/(2*n))*2;
		cout<<tmp*tmp2<<'\n';
	}
	return 0;
}
```





---

## 作者：囧仙 (赞：1)

## 题目大意

求边长为$1$的正$(2\times n)$边形的最小外接正方形的边长。

$T$组数据。$T\le 200,n\le 200$，且$\bf{n}$**为奇数**。

## 题解

与$\rm CF1354C2$不同，这次$n$换成了奇数。同样的，我们拿正六边形举例。

![6.JPG](https://i.loli.net/2020/05/18/BXFJKqfOmTPNMW7.jpg)

我们发现，这一次，问题变得棘手了起来。因为，这个正方形并不能很好地框住整个六边形。

我们不妨换一种思路。假设正方形的中心为坐标系原点$O(0,0)$，四条边与坐标轴平行，那么此时正方形的边长应该为$\max\{x_{max}-x_{min},y_{max}-y_{min}\}$才能将整个多边形包进去。

考虑到多边形最多旋转$\frac{\pi}{2\times n}$度，那么由于对称性，实际可能有关的点只有两个，即目前最靠右的点和$y$值最大且靠右边的那个点。（这里我们不妨假设这个多边形有两个顶点恰好在$x$轴上）。然后我们发现，随着旋转地不断变化，$C$的横坐标会不断减小，而$D$的横坐标会不断增大。根据对称性，只要旋转$\frac{\pi}{4\times n}$度就可以了。

## 参考代码

```
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
const int MOD =998244353;
const double pi=acos(-1);
double f(double a,double b,double c,double d,double w){ //旋转
    double x=a*cos(w)+b*sin(w),y=c*sin(w)+d*cos(w);
    return x>y?x:y;
}
int n; double t;
int main(){
    dn(qread(),1,T){
        n=qread()*2,t=pi/n;
        double p0=(double)0.5/sin(t),p1=0;
        double q0=(double)0.5,q1=(double)0.5/tan(t);
        printf("%.12lf\n",f(p0,p1,q0,q1,t/2)*2.0);
    }
    return 0;
}
```

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF1354C2](https://www.luogu.com.cn/problem/CF1354C2)

* **【解题思路】**

可以猜到结论：我们令这个多边形的某两条对边平行于 $x$ 轴，则最小外接正方形的边与坐标轴的夹角为 $\dfrac \pi2$，就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/8j68sc4w.png)

然后我们再来找切点，如果从 $(1,0)$ 开始逆时针标号，$(1,0)$ 标为 $0$，则标号为 $i$ 的点坐标为 $\left(\cos \dfrac{i\pi}n,\sin \dfrac{i\pi}n\right)$。可以发现在第一象限的切点的标号为 $\left\lfloor\dfrac{n+1}4\right\rfloor$。

于是我们就可以得到在第一象限的这条边的截距（就是切点横纵坐标之和），进而就能求出它的长度。当然，可以发现我们刚刚的这个多边形边长不一定是 $1$，我们只需要把它放缩相应的倍数即可。

于是答案就是

$$\frac{\sin\left(\left\lfloor\dfrac{n+1}4\right\rfloor\dfrac\pi n+\dfrac\pi4\right)}{\cos\left(\left\lfloor\dfrac{n-1}2\right\rfloor\dfrac\pi n\right)}$$

---

