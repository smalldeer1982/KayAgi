# Simple Polygon Embedding

## 题目描述

The statement of this problem is the same as the statement of problem C2. The only difference is that, in problem C1, $ n $ is always even, and in C2, $ n $ is always odd.

You are given a regular polygon with $ 2 \cdot n $ vertices (it's convex and has equal sides and equal angles) and all its sides have length $ 1 $ . Let's name it as $ 2n $ -gon.

Your task is to find the square of the minimum size such that you can embed $ 2n $ -gon in the square. Embedding $ 2n $ -gon in the square means that you need to place $ 2n $ -gon in the square in such way that each point which lies inside or on a border of $ 2n $ -gon should also lie inside or on a border of the square.

You can rotate $ 2n $ -gon and/or the square.

## 样例 #1

### 输入

```
3
2
4
200```

### 输出

```
1.000000000
2.414213562
127.321336469```

# 题解

## 作者：皎月半洒花 (赞：18)

设所求为正 $n$ 边形。那么这个 `version` 就是 $n=4k$ 的 case。

考虑最后一定是边贴边。具体证明从略，首先很显然，其次根据样例猜不能猜出来吗?

![](https://cdn.luogu.com.cn/upload/image_hosting/f8y4o2bg.png)

考虑如图的 $12$ 变形。对于边长让我们拆开计算，即分别计算 $|MQ|+|QB|+|BC|+|CR|+|RN|$ 。那么不难知道诸如 $|QM|=|LA|\cdot \sin(\angle ALM)$，$|QB|=|AB|\cdot \sin(\angle BAQ)$ 之类的这种结论。那么发现最后答案就是
$$
\sum_{j=1}^{2\cdot k-1} \sin{\frac{j\cdot \pi}{2\cdot k}}
$$
到此就可以直接停了。~~但是身为高中生就这么停了你对得起你的数学老师吗。~~ 

于是可以继续化。具体的，设 
$$
s=\sum_{j=1}^{2\cdot k-1} \sin{\frac{j\cdot \pi}{2\cdot k}}
$$
然后考虑求 $\sin{\dfrac{\pi}{2\cdot k}}\cdot s$ 。同时根据**积化和差**可以得到
$$
\sin{\dfrac{\pi}{2\cdot k}}\cdot \sin{\dfrac{j\cdot \pi}{2\cdot k}}=\frac{1}{2}\left(\cos{\dfrac{(j-1)\cdot \pi}{2\cdot k}}-\cos{\dfrac{(j+1)\cdot \pi}{2\cdot k}}\right)
$$
那么也就是 $\sin{\dfrac{\pi}{2\cdot k}}\cdot s$ 中有许多项都可以消掉，最后得到
$$
\sin{\dfrac{\pi}{2\cdot k}}\cdot s=1+\cos\frac{\pi}{2\cdot k}
$$
根据二倍角公式可以整理得到
$$
s=\frac{\cos\frac{\pi}{4\cdot k} }{\sin\frac{\pi}{4\cdot k}}=\cot \frac{\pi}{4\cdot k}
$$


---

## 作者：囧仙 (赞：2)

## 题目大意

求边长为 $1$ 的正 $(2\times n)$ 边形的最小外接正方形的边长。

$T$ 组数据。$T\le 200,n\le 200$，且 $\bm{n}$**为偶数**。

## 题解

由于 $n$ 为偶数，所以这个多边形边的个数是 $4$ 的倍数；因此，这个多边形可以分为左上、右下、左下、右上四个部分。

这里以八边形为例。

![8.JPG](https://i.loli.net/2020/05/18/l6foqFNbI9PtXkZ.jpg)

事实上，这个正方形已经是最小的正方形了。倘若我们旋转这个正方形，就会发现无论如何正八边形都会与他相交/相切。

![8.gif](https://i.loli.net/2020/05/18/KEcfZXtTgYHVzl8.gif)

这个东西是非常容易证明的。因为我们显然最多只需要旋转 $\frac{\pi}{n}$。而在这个范围内，无论怎样旋转，都会与 $EF$ 重合。

因此这个问题变得非常简单了。我们取 $EF$ 中点 $P$，连接 $EM,PM$，那么可以求出 $\angle EMP=\frac{\pi}{2\times n}$，然后通过 $\tan \angle EMP=\frac{EP}{PM}$  求出 $PM$，进而求出边长。

## 参考代码

```cpp
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
const double pi=acos(-1);
int n; double t;
int main(){
    dn(qread(),1,T){
        n=qread()*2,t=pi/n;
        printf("%.12lf\n",(double)1/tan(t));
    }
    return 0;
}
```

---

## 作者：To_Carpe_Diem (赞：1)

## 题目简述

这道题目是关于正多边形嵌套的问题。给定一个边长为 $1$ 的 $(2 \times n)$ 边形，要求找到一个最小的正方形，使得该正方形能够将正 $(2 \times n)$ 边形完全包含。

## 思路简述

我们可以观察到，当 $n$ 较小时，正 $(2 \times n)$ 边形的形状更接近一个圆形，而当 $n$ 较大时，正 $(2 \times n)$ 边形的形状更接近一个正多边形。因此，我们可以通过计算正 $(2 \times n)$ 边形的外接圆的半径来得到最小正方形的边长。

根据正多边形的性质，正 $(2 \times n)$ 边形的外接圆的半径可以通过以下公式计算：

$$r=\frac{1}{2\times\sin\left(\frac{\pi}{2n}\right)}$$

而正方形的边长等于正 $(2 \times n)$ 边形的外接圆的直径，即 $2r$。

因此，我们可以通过计算上述公式得到最小正方形的边长。

## 代码实现

```cpp
#include<iostream>
#include<cmath>
using namespace std;

#define M_PI 3.141592653589793238462643383279

int T;
int n;

int main() {
    cin>>T;
    while(T--){
        cin>>n;
        double sh=1.0/tan(M_PI/(2.0*n));
        cout<<fixed;
        cout.precision(9);
        cout<<sh<<"\n";
    }
    return 0;
}
```

---

## 作者：HenryHuang (赞：1)

简要题意：给定一个正 $4n$ 边形，求最小的能将其完全覆盖的正方形的边长。

容易得到正 $4n$ 边形在两个方向上（上下、左右）的最长的一条边均为 $2$ 倍边心距。

> 正多边形的**边心距**是正多边形的外接圆圆心（同时也是内切圆圆心）到正多边形某一边的距离。正多边形的边心距都相等。

于是正方形的边长即为 $2$ 倍边心距，因为正 $4n$ 边形一定存在四条边与正方形的四条边平行。

或者可以这么说，正 $4n$ 边形一定是从一个正四边形当中分割出来的。

关于边心距，计算的方法很多，可以百度一下，这里不再赘述。

注意上面描述的 $n$ 与题目给出的 $n$ 有所不同。

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
		n<<=1;
		cout<<2.0/2*tan(1.0*(n-2)*pi/(2*n))<<'\n';
	}
	return 0;
}
```





---

## 作者：LazySheep (赞：1)

[CF题目链接](http://codeforces.com/contest/1354/problem/C1)

---

先放结论：

$$ans=\dfrac{sin\frac{\pi(n-1)}{2n}}{sin\frac{\pi}{2n}}$$

证明：

对于正 $2n$ 边形的外接圆，我们~~查百度~~知道边长 $l$ 与半径 $r$ 有如下关系：

$$L=2R\,sin{\frac{\pi}{2n}}\Rightarrow R=\dfrac{L}{2sin\frac{\pi}{2n}}$$

以正 $8$ 边形为例进行说明。

![正八边形](https://s1.ax1x.com/2020/05/18/YhaHWn.png)

原题求最小外接正方形边长，画图可以发现，其实是求上图中三角形的最长边。

根据初中数学知识可知，图中 $\Theta=\frac{\pi(n-1)}{n}$ 。

所以三角形最长边长度为：

$$2Rsin\frac{\Theta}{2}=2\times\dfrac{L}{2sin\frac{\pi}{2n}}\times sin\dfrac{\frac{\pi(n-1)}{n}}{2}=\dfrac{sin\frac{\pi(n-1)}{2n}}{sin\frac{\pi}{2n}}$$

---

CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
const double P=3.1415926535;
int main(){
	int TTT;double n;
	scanf("%d",&TTT);
	while(TTT--){
		scanf("%lf",&n);
		double m=n*2;
		printf("%.7lf\n",sin(P*(n-1)/(m))/sin(P/m));
	}
	return 0;
}
```

---

## 作者：EternalEpic (赞：0)

这道题，是一道几何体，由于：

$$n \equiv 0 \pmod{2}$$

所以，我们知道它最小的外接正方形的边与正2n边形的边重合。

则正方形边长为正多边形两对边的距离。

做外接圆，求每边所对圆心角，再使用三角函数即可解决。

即:
$$b = 1 / \tan \tfrac{a}{2}$$

注意：c++ std :: tan() 中使用的是弧度制，记得角度转换。

精度要注意保留。

简要代码：

```cpp
const double PI = 3.141592653;
int T, m;
double n, deg, deg2, s;

signed main(void) {
//	file("");
	for (read(T); T; T--) {
		read(m); n = m * 2;
		deg = (double)1 / n; deg = deg * PI;
		printf("%.9lf\n", (double) 1.0 / tan(deg));
	}
//	fwrite(pf, 1, o1 - pf, stdout);
	return 0;
}
```


---

