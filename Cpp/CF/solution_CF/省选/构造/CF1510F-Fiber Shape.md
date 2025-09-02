# Fiber Shape

## 题目描述

Imagine a board with $ n $ pins put into it, the $ i $ -th pin is located at $ (x_i, y_i) $ . For simplicity, we will restrict the problem to the case where the pins are placed in vertices of a convex polygon.

Then, take a non-stretchable string of length $ l $ , and put it around all the pins. Place a pencil inside the string and draw a curve around the pins, trying to pull the string in every possible direction. The picture below shows an example of a string tied around the pins and pulled by a pencil (a point $ P $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510F/3b434456ce86779edbd75c1c31032e6011c62ac7.png)Your task is to find an area inside this curve. Formally, for a given convex polygon $ S $ and a length $ l $ let's define a fiber shape $ F(S, l) $ as a set of points $ t $ such that the perimeter of the convex hull of $ S \cup \{t\} $ does not exceed $ l $ . Find an area of $ F(S, l) $ .

## 说明/提示

The following pictures illustrate the example tests.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510F/73efb05d151b205642c75f0c21efa36e2790cfd3.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510F/3d7b56874f36b0db8d6135c9d751060f7ad68412.png)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510F/e25400dd84baf171efc8e3b94be6a87e03a7df61.png)

## 样例 #1

### 输入

```
3 4
0 0
1 0
0 1```

### 输出

```
3.012712585980357```

## 样例 #2

### 输入

```
4 5
0 0
1 0
1 1
0 1```

### 输出

```
5.682061989789656```

## 样例 #3

### 输入

```
5 17
0 0
2 -1
3 0
4 3
-1 4```

### 输出

```
37.719371276930820```

# 题解

## 作者：strapplE (赞：3)

计算几何神题。对于 OIer 们，难度至少也有黑了，因为后面计算部分的积分（格林公式？）属实有点唐。我这里还是侧重介绍下计算几何一点点小计算和前面较为 OI 一点的思想吧。照搬原题题解，争取说得更浅显易懂一些。

首先，对一个凸多边形，新加的点的位置和区域周长之间是什么联系？这部分应该不难，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/aiwvg6k7.png)

原多边形为 $ABCDE$，加的点为 $P$。新的周长 $d'$ 为 $d-\operatorname{dist}(B,P,E)+EP+PB$，其中 $d$ 为原周长，$\operatorname{dist}$ 表示 $BE$ 经过 $P$ 的那一侧所有原多边形边的长度之和。这样，就把题目中的不明所以的限制用数学语言大概地刻画出来了。下面就要探究每个 $P$ 点，对应刚才图中 $B,E$ 那两个点是谁？

把原多边形每个点重新标号为 $A_1,A_2,\dots,A_n$。不难发现，图中所有满足线段 $A_iP$ 不穿过多边形的点（按逆时针顺序）只有 $B,A,E$ 三个。同时因为最后选择的是 $B,E$，所以不难发现，$P$ 只连接到这里面最靠前和最靠后的两个点，才能保持凸性。之后我们将其（按逆时针顺序）分别记为 $A_i,A_j$。

假如 $A_i,A_j$ 已固定，$P$ 的区域是怎样的图形？把限制重新写为 $\operatorname{dist}(i\rightarrow j)+A_jP+PA_i\leq l$，即 $A_jP+PA_i\leq c=l-\operatorname{dist}(i\rightarrow j)$ 为定值。容易根据高中数学知识，判断出这是一个焦点为 $A_i$ 和 $A_j$ 的**椭圆**。最后的总区域一定是若干个椭圆的并。

下一个要思考的问题，最终的区域会出现多少椭圆呢？乍一看是平方量级的。下面我们感性认知一下，它其实是线性的！

先随便找出一个椭圆（由点 $A_i,A_j,P$ 确定）。接下来考虑让 $P$ 在这个曲线上按轨迹移动，直到超出了 $A_i$ 和 $A_j$ 两点“统治”的范围为止。何时会超出呢？请看下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/1ldhlrdu.png)

根据刚才我们的定义，$A_i$ 对应这里就是 $E$ 点，$A_j$ 对应 $B$ 点。如果椭圆要顺时针推进，则至少 $P$ 要挪动到此图中 $X$ 点和 $Y$ 点的一个。其实我们应该选择里 $P$ 更近的那个交点（在图中为 $X$），则 $PX$ 这一段将出现在最终答案区域的轮廓中。（当然，这个 $P$ 实际并不对应这个点，这里只是方便起见这么说。但是下一个点一定是 $X$ 开始，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5n6a1c2q.png)

$Z$ 为 $BC$ 与椭圆的交点，$W$ 为 $AB$ 与椭圆的交点。显然这里我们取了 $Z$，也就是说明 $XZ$ **一定**为答案轮廓上的一段。

更一般地，假如已经有了一个点 $P$ 在以 $A_i,A_j(i<j)$ 为两个焦点的椭圆 $E$ 上，作 $A_iA_{i+1}$ 与 $E$ 的交点 $X$，$A_jA_{j+1}$ 与 $E$ 的交点 $Y$。则找到一个离 $P$ 更近的点，将这段加入答案，并把 $i$ 加一（如果 $Y$ 比 $X$ 离得更近，应该把 $j$ 加一）。这是一个双指针移动的过程，最后必然会出现 $2n$ 段椭圆弧。

这样大体思想就已经完全解出来了，现在去思考下细节：

第一点：首先如何找到一个 $P$，使得这里的 $P$ 一定是一个分段点。一种可能的办法是，因为如果 $P$ 与原多边形上的两点共线，那肯定就结束了。所以去固定 $A_i=A_n$，并设 $P=A_n+k\overrightarrow{A_nA_1}(k>0)$。显然 $k$ 越大区域面积越大，因此直接二分就好了。这样对应即可切出点 $A_j$，往后找每一段都双指针进行即可。

第二点：怎么去算一个射线和一个椭圆的交？其实还是要利用下本题的特殊性：射线中的一个点为这个椭圆的一个焦点。不妨我们正在计算 $\overrightarrow{A_iA_{i+1}}$ 与 $PA_i+PA_j=c$ 的交。设 $\vec{v}=A_{i+1}-A_i,P=A_i+k\vec{v}$（千万别忘了我们这是计算几何，和解析几何完全不是一套系统！坐标几乎不影响任何东西），则可以列出：

$$k\lvert\vec{v}\rvert+\sqrt{(P-A_j)(P-A_j)}=c$$

$$\lvert(A_i-A_j+k\vec{v})\rvert^2=(c-k\lvert\vec{v}\rvert)^2$$

$$(A_i-A_j)^2+2k\vec{v}\cdot (A_i-A_j)=c^2-2kc\lvert\vec{v}\rvert$$

这样子就是一个关于 $k$ 的一次方程了，很容易求解（主要是因为另一个交点就在 $A_i$ 处，直接消了）。

目前，我们已经知道了所有 $2n$ 段椭圆弧的信息，包括焦点和弧上两点。注意这里两点的顺序你可能需要特判下，有些时候要交换。不过因为都只是判一些角度是否 $>0$，因此都很容易用叉乘解决。

最后一个问题就是求面积了。可能有多种方法解决？这里遵循原题解，给出格林公式：

$$\oint_{L} (Pdx + Qdy) = \iint_{D} \left( \frac{\partial Q}{\partial x} - \frac{\partial P}{\partial y} \right) dxdy$$

取 $P=-y,Q=x$，则 $\frac{\partial Q}{\partial x}=- \frac{\partial P}{\partial y}=1$，而面积就是 $\iint_{D}dxdy$，于是有：

$$ans=\dfrac{1}{2}\oint_{L} (xdy - ydx)$$

因此我们把每一段曲线都用如上式子做积分就行了。

回归下解几。众所周知，椭圆有隐式方程：$x=a\cos \theta,y=b\sin \theta$，其中 $a$ 和 $b$ 为椭圆的长半轴和短半轴。但本题椭圆不一定是平行于坐标轴的，因此要回到计算几何上，考虑对应的一组基 $e_x,e_y$，设椭圆中心为 $O$，则这次坐标就可以完完全全地列出来了：

$$P(\theta)=O+ae_x\cos \theta+be_y\sin \theta$$

回到曲线积分。曲线是不好做的，但是可以改成关于 $\theta$ 的形式。设椭圆上两点坐标分别为 $P(\alpha),P(\beta)$。又有 $xdy-ydx=(x,y)\times (dx,dy)=P(\theta)\times P'(\theta)$，因此就只和 $\theta$ 有关了。于是可以改写为：

$$\int\limits_{\alpha}^{\beta}(O+ae_x\cos \theta+be_y\sin \theta)\times (be_y\cos \theta-ae_x\sin\theta)d\theta$$

这是一个小学生积分形式。于是就做完了！复杂度或许可以做到 $O(n)$，我二分里写的不太精细多了个 $\log$，但显然都可过。代码如下：

```cpp
#include<bits/stdc++.h>
#define double long double
using namespace std;
int x[10005],y[10005];
struct point{
	double x,y;
	point(double x=0,double y=0):x(x),y(y){}
}p[10005];
point operator+(point a,point b){
	return point(a.x+b.x,a.y+b.y);
}
point operator-(point a,point b){
	return point(a.x-b.x,a.y-b.y);
}
double operator*(point a,point b){
	return a.x*b.x+a.y*b.y;
}
point operator*(double a,point b){
	return point(a*b.x,a*b.y);
}
double operator^(point a,point b){
	return a.x*b.y-a.y*b.x;
}
double dist(point a,point b){
	return sqrt((a-b)*(a-b));
}
int p1[50005],p2[50005];
point p0[50005];
long long cha(int a,int b,int c,int d){
	return 1ll*(x[b]-x[a])*(y[d]-y[c])-1ll*(y[b]-y[a])*(x[d]-x[c]);
}
double wt[10005];
point getjp(point pi,point pj,point v,double r){
	double t=(r*r-(pi-pj)*(pi-pj))/2/(v*(pi-pj)+r*sqrt(v*v));
	return pi+t*v;
}
int main(){
	int n,l;
	scanf("%d%d",&n,&l);
	for(int i=1;i<=n;++i)scanf("%d%d",&x[i],&y[i]),p[i]=point(x[i],y[i]);
	p[0]=p[n],p[n+1]=p[1];
	int w=n;
	for(int i=1;i<n;++i){
		if(cha(n,1,i,i+1)<=0){
			w=i;break;
		}
	}
	for(int i=1;i<w;++i){
		wt[i]=((p[i]-p[1])^(p[i+1]-p[i]))/((p[1]-p[n])^(p[i+1]-p[i]));
	}
	double L=0,R=1e9;
	while(R-L>1e-13){
		double mid=(L+R)/2,x=mid;
		point P=p[1]+x*(p[1]-p[n]);
		int z=w;
		for(int i=1;i<w;++i){
			if(x<=wt[i]){
				z=i;break;
			}
		}
		double he=0;
		for(int i=z;i<=n;++i)he+=dist(p[i],p[i+1]);
		he+=dist(p[1],P)+dist(P,p[z]);
		if(he<=l)L=mid;
		else R=mid;
	}
	double x=(L+R)/2;
	int z=w;
	for(int i=1;i<w;++i){
		if(x<=wt[i]){
			z=i;break;
		}
	}
	int k=0;
	++k;p1[k]=1,p2[k]=z,p0[k]=p[1]+x*(p[1]-p[n]);
	int i=1,j=z;
	while(1){
		double r=dist(p[i],p0[k])+dist(p[j],p0[k]);
		point A=getjp(p[i],p[j],p[i+1]-p[i],r);
		point B=getjp(p[j],p[i],p[j]-p[j+1],r);
		double dA=dist(A,p[i]),dB=dist(B,p[i]);
		if(dA<=dB){
			i=i%n+1;
			++k,p1[k]=i,p2[k]=j,p0[k]=A;
		}else{
			j=j%n+1;
			++k,p1[k]=i,p2[k]=j,p0[k]=B;
		}
		//焦点 p[i] p[j] 距离是 r
		//线段 p[i+1]-p[i] p[j]-p[j+1]
		//交点 A B
		//距离 dist(A,p[i]) dist(B,p[i])
		//情况一 i=i%n+1 否则 j=j%n+1
		//++k;p1[k]=i,p2[k]=j,p0[k]=A?B?;
		if(i==1&&j==z)break;
	}
	double ans=0;
	for(int i=1;i<=n;++i)ans+=p[i]^2*p[i+1];
	for(int i=1;i<k;++i){
		point P1=p[p1[i]],P2=p[p2[i]];
		point A=p0[i],B=p0[i+1];
		if(((P2-P1)^(A-P2))<0)swap(P1,P2);
		double c=dist(P1,P2)/2;
		double a=(dist(P1,A)+dist(P2,A))/2;
		double b=sqrt(a*a-c*c);
		point O=0.5*(P1+P2);
		point OA=a/c*(P2-O);
		point OB(-OA.y,OA.x);OB=b/a*OB;
		double a1=acos(((A-O)^OB)/a/b);
		double a2=acos(((B-O)^OB)/a/b);
		assert(a1<=a2);
		ans+=(a2-a1)*(OA^OB);
		ans+=O^((sin(a1)-sin(a2))*OB+(cos(a1)-cos(a2))*OA);
		//焦点 p[p1[i]] p[p2[i]]
		//段 p0[i]~p0[i+1]
	}
	printf("%.8Lf\n",ans/2);
	return 0;
}
```

灵异事件：直接按格林公式算出来后，不知道为什么答案极小无比。不过可以发现和样例只差一个常数，经过简单计算发现常数就是多边形面积的常数倍！因此加上就可以过了。别忘了需要 long double，这个抽象计几题就被我们攻破了，赢！

---

