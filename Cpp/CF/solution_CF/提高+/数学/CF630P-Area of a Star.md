# Area of a Star

## 题目描述

It was decided in IT City to distinguish successes of local IT companies by awards in the form of stars covered with gold from one side. To order the stars it is necessary to estimate order cost that depends on the area of gold-plating. Write a program that can calculate the area of a star.

A "star" figure having $ n>=5 $ corners where $ n $ is a prime number is constructed the following way. On the circle of radius $ r $ $ n $ points are selected so that the distances between the adjacent ones are equal. Then every point is connected by a segment with two maximally distant points. All areas bounded by the segments parts are the figure parts.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630P/39542693730deb3e42477c452be9d403bea1f94e.png)

## 样例 #1

### 输入

```
7 10
```

### 输出

```
108.395919545675```

# 题解

## 作者：XL4453 (赞：2)

### 解题思路:

![](https://cdn.luogu.com.cn/upload/image_hosting/mfrw4rdo.png)

由正多边形，可以算出一个中心角的度数以及一个顶角的度数，然后根据角平分线得到 $\angle IAB$ 和 $\angle AIB$ 的度数。

又有题目给出的 $AI$ 的长度，这样就在一个三角形中凑齐了两角一边，~~可以召唤神龙了~~，用三角形中的正弦定理求出三边，然后面积就随便求了。

---
### 公式推导：

设 $n$ 为顶点数，$r$ 为圆的半径。

则 $\angle IAB=\dfrac{180\degree}{n}$，$\angle AIB=\dfrac{90\degree}{n}$。

所以：$\angle IBA=180\degree-\dfrac{270\degree}{n}$。

根据正弦定理：$\dfrac{AI}{\sin\angle IBA}=\dfrac{AB}{\sin\angle BIA}$，得到：$AB=\dfrac{AI\sin\angle BIA}{\sin\angle IBA}$。

然后用正弦求面积：$S_{\triangle BIA}=\dfrac{AI^2\sin\angle BIA\sin\angle BAI}{2\sin\angle IBA}$。


根据之前的 $AI=r$，$S_{\triangle BIA}=\dfrac{r^2\sin\angle BIA\sin\angle BAI}{2\sin\angle IBA}$。

将角带入到公式中：$S_{\triangle BIA}=\dfrac{r^2\sin\dfrac{90\degree}{n}\sin\dfrac{180\degree}{n}}{2\sin(180\degree-\dfrac{270\degree}{n})}$。

然后乘以 $2n$ 就是总面积了。

注意：代码实现时要转弧度制。

---
### 代码：

```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
double n,r,S,a,b;
const double Pi=acos(-1.0);
int main(){
	scanf("%lf%lf",&n,&r);
	S=(r*r*sin(Pi/n)*sin(Pi/(2*n)))/(2*sin(Pi-Pi*3/2/n));
	printf("%.12lf\n",2*n*S);
	return 0;
}
```


---

## 作者：FuriousC (赞：2)

~~水蓝~~

[题目传送门](https://www.luogu.com.cn/problem/CF630P)

先上图：

![](https://img-blog.csdnimg.cn/20190806194034687.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2Vycm9yMzEx,size_16,color_FFFFFF,t_70)

图from @[error0318](https://blog.csdn.net/error311)

先求出一个小黄色三角形的面积，再$\times 2 n$即可

求三角形面积方法：

目标变更为求$∠OAB:$

∵∠$DOE=$∠$BOF($对顶角$)$

又∵$AC$平分∠$DOE$和∠$BOF$，

∴∠$DOC=$∠$AOB$

在△$ADC$中$:$

∵$O$是$AC$中点

∴∠$DOC=2\times $∠$DAC$

∵∠$DOC=$∠$AOB$

∴∠$AOB=2\times$∠$BAO$=$\pi \div n \div2$

可知∠$OBA=\pi-$∠$AOB-$∠$BAO$

然后用正弦定理求出$AB$

~~没学过正弦定理的建议回去重学whk~~

三角形面积公式：![](https://private.codecogs.com/gif.latex?S%3D%5Cfrac%7B1%7D%7B2%7D*a*b*sinC%3D%5Cfrac%7B1%7D%7B2%7D*a*c*sinB%3D%5Cfrac%7B1%7D%7B2%7D*b*c*sinA)

求完一个黄色三角形后再$\times 2n$即可

代码：

```
#include<bits/stdc++.h>
using namespace std; 
#define pi 3.1415926535897932384626433832795028
double n,r,s,ang_a,ang_b,ang_c,sid_a,sid_c;//ang_a为最小角，ang_c为最大角；sid_a为最短边，sid_c为最长边，s为一个小三角形的面积 
int main(){
    cin>>n>>r;//输入 
    ang_a=pi/(2.0*n);ang_b=2*ang_a;ang_c=pi-ang_a-ang_b;//求出三个角 
    sid_c=r;sid_a=sid_c*sin(ang_a)/sin(ang_c);//求出最长边与最短边 
    s=0.5*sid_a*r*sin(ang_b);//小三角形的面积
    cout<<fixed<<setprecision(9)<<2*n*s<<endl;//输出2*n*s 
    return 0;
}
```

代码看完了，你学废了吗？

---

## 作者：ZJMZJM (赞：2)

只需要求出黄色三角形的面积，首先可以求出三个角的值，正弦定理可以得到三边长度，面积公式求面积，最后乘上2n即可。
```
#include<stdio.h>
#include<math.h>
#define pi acos(-1.0)//pi
int main()
{
    double n,r;
    while(~scanf("%lf%lf",&n,&r))
    {
        double A,B,C,a,c,s;//大写为角，小写为边
        A=pi/(2.0*n);//最小的角
        B=2*A;//次小的角
        C=pi-A-B;//最大角
        c=r;//最长边
        a=c*sin(A)/sin(C);//正弦定理求出最短的边
        s=0.5*a*r*sin(B);//黄色三角形的面积
        printf("%.8f\n",2*n*s);
    }
    return 0;
}
```

---

## 作者：The_jester_from_Lst (赞：1)

简易数学题。

如果你看懂了这个百科，相信这题也没问题了：（[正弦定理](（[题解审核及反馈要求](https://baike.baidu.com/item/%E6%AD%A3%E5%BC%A6%E5%AE%9A%E7%90%86/2657575)）)）。

用正弦定理求出三角形三边的长度，再运用面积公式求出三角形的面积，最后乘 $2n$，就能愉快地解决这道题啦！

附上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int rd(){
	int jya=0,tl=1;char jyt=getchar();
	while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
	while(isdigit(jyt)){jya=jya*10+(jyt-'0');jyt=getchar();}
	return jya*tl;
}
inline void wr(int jjy){
	if(jjy<0)putchar('-'),jjy=-jjy;
	if(jjy>9)wr(jjy/10);
	putchar(jjy%10+48);
}
double n,r,s,a,b;
const double Pi=acos(-1.0);
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>r;
	s=(r*r*sin(Pi/n)*sin(Pi/(2*n)))/(2*sin(Pi-Pi*3/2/n));
	printf("%.12lf",2*n*s);
	return 0;
}
```


---

## 作者：王逸辰 (赞：0)

# CF630P Area of a Star 题解
## 思路
数学题，

需要用到**正弦定理**。


用**正弦定理**求出多角形的面积，
再乘上 $2n$ 就可以了。

## Code
~~数学题，代码一定很短。~~
```cpp
#include<bits/stdc++.h>
#define pi 3.1415926535897932//想取多少取多少
using namespace std;
double n,r,s,a,b,c,x,y;
int main(){
	scanf("%lf%lf",&n,&r);
	a=pi/(2.0*n);
	b=pi-3*pi/(2.0*n);
	y=r*sin(pi/(2.0*n))/sin(b);
	s=r*0.5*y*sin(2*a);
	printf("%.12lf",s*2*n);
}
```

---

## 作者：封禁用户 (赞：0)

***数论题。***

我们可以用正弦定理来做这道题。

这里引入一个函数：
```cpp
acos() 函数的功能是求反余弦值，即求角度。
```
***利用这个函数，我们能求出三个角的值，并轻松求出三边长度，然后求出面积，最后乘上 $2n$ 就可以了。***

***Code***

```cpp
#include <bits/stdc++.h>
using namespace std;
double n_a, r_b, s, a, b, s1, g = acos(-1.0);
int main()
{
	cin >> n_a >> r_b;
	s = r * r * sin(g / n_a) * sin(g / (2 * n_a));
	s1 = 2 * sin(g - g * 3 / 2 / n_a);
	printf("%0.12lf", 2 * n_a * (s / s1));//要保留12位小数
	return 0;
}
```

---

## 作者：_Sky_Dream_ (赞：0)

# [传送门](https://www.luogu.com.cn/problem/CF630P)

超级水……首先，你要知道[正弦定理](https://baike.baidu.com/item/%E6%AD%A3%E5%BC%A6%E5%AE%9A%E7%90%86/2657575)。

其次，你就可以敲代码了……

用正弦定理求出三角形面积，再乘以 $2n$ 即可。

附：[π小数点后一百万位](https://pi.hao86.com/20000/)……

```cpp
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define int long long
#define pai 3.141592653589793238462643383279502884197169399375105820974944592307//小数点后几位你自己选，不要打错了
using namespace std;
double n,r,s,a,b,c,x,y;
void Enchanted(){
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>r;
	a=pai/(2.0*n);b=2*a;c=pai-a-b;//正弦定理
	y=r;x=y*sin(a)/sin(c);
	s=0.5*x*r*sin(b);
	printf("%.12f",n*s*2);
	exit(0);
}
signed main(){Enchanted();}



```




---

