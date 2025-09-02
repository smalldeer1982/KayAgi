# Inquisition

## 题目描述

In Medieval times existed the tradition of burning witches at steaks together with their pets, black cats. By the end of the 15-th century the population of black cats ceased to exist. The difficulty of the situation led to creating the EIC - the Emergency Inquisitory Commission.

The resolution #666 says that a white cat is considered black when and only when the perimeter of its black spots exceeds the acceptable norm. But what does the acceptable norm equal to? Every inquisitor will choose it himself depending on the situation. And your task is to find the perimeter of black spots on the cat's fur.

The very same resolution says that the cat's fur is a white square with the length of $ 10^{5} $ . During the measurement of spots it is customary to put the lower left corner of the fur into the origin of axes $ (0;0) $ and the upper right one — to the point with coordinates $ (10^{5};10^{5}) $ . The cats' spots are nondegenerate triangles. The spots can intersect and overlap with each other, but it is guaranteed that each pair of the triangular spots' sides have no more than one common point.

We'll regard the perimeter in this problem as the total length of the boarders where a cat's fur changes color.

## 样例 #1

### 输入

```
1
1 1 2 1 1 2
```

### 输出

```
3.4142135624
```

## 样例 #2

### 输入

```
3
3 3 10 3 3 10
1 1 9 4 5 6
2 2 11 7 6 11
```

### 输出

```
37.7044021497
```

# 题解

## 作者：CarroT1212 (赞：1)

非常好计算几何，使我的大脑旋转卡壳。

~~虽然这题用不到旋转卡壳。~~

------------

### 题目大意

求平面上 $n$ 个三角形的面积并的周长。答案误差不超过 $10^{-6}$。保证没有两个三角形的边出现重合（但可以相交）。

$1 \le n \le 100$，$0<x_{1i},y_{1i},x_{2i},y_{2i},x_{3i},y_{3i}<10^5$。

------------

### 做法概要

我们可以把每一个三角形的边分割成若干条线段，使得每一段中间都没有其它三角形的边穿过，也就是按这个三角形的边与其它三角形的交点把每条边切割开来。

然后对于每一条线段，取它上面的一个点（比如中点），判一下这个点是否被某个其它的三角形包含。因为这是分割之后的线段，这个点被包含等价于这条线段被包含。把所有没被包含的线段长度加起来即是答案了。

复杂度 $O(n^3)$。STL 什么的可能带个 $\log$。

------------

### 某些细节

特别提一下以造福之后跟我一样做这题时对计算几何一窍不通的人。本段部分参考自 [OIwiki 二维计算几何基础](https://oiwiki.com/geometry/2d)，有误欢迎指出。

#### 如何求两条线段的交点坐标？

你当然可以列出解析式暴力解方程，但是要特判斜率不存在之类的阴间情况。有一种稍微优美一点的向量做法。假设你知道高中向量以及三角函数相关知识。

![](https://cdn.luogu.com.cn/upload/image_hosting/zj313pd0.png)

借用一张 OIwiki 的图。假设只考虑两条线段所在的直线。现在我们想要求出直线 $AB,CD$ 的交点 $E$。因为 $AB,CD$ 方向已知，只要知道直线上某一个点与 $E$ 的距离 $l$，简单计算一下就可以知道 $E$ 的坐标了。

考虑设 $\textbf{a}=\overrightarrow{AB}$，$\textbf{b}=\overrightarrow{CD}$，$\textbf{u}=\overrightarrow{DB}$，那么由向量叉积的几何意义与正弦定理，$|\textbf{a}\times \textbf{b}|=|\textbf{a}||\textbf{b}|\sin \beta$，$|\textbf{u}\times \textbf{b}|=|\textbf{u}||\textbf{b}|\sin \theta$，作商得 $T=\frac{|\textbf{u}\times \textbf{b}|}{|\textbf{a}\times \textbf{b}|}=\frac{|\textbf{u}|\sin\theta}{|\textbf{a}|\sin\beta}$。$\textbf{a},\textbf{b}$ 平行时 $T$ 无意义，即没有交点。

又由图知 $\left|\frac{|\textbf{u}|\sin\theta}{\sin\beta}\right|=|BE|=l$，那么 $T|\textbf{a}|=l$，这是一个数的形式，把 $|\textbf{a}|$ 换成 $\textbf{a}$ 就可以使其变为与 $\textbf{a}$ 同向的一条长度为 $l$ 的向量。所以用 $B$ 减去 $T\textbf{a}$ 就可以得到 $E$ 坐标了。

这么做比较优美是因为叉积可以用另一种方式计算：两个空间向量 $\textbf{a}=(x_1,y_1,z_1),\textbf{b}=(x_2,y_2,z_2)$ 的叉积结果 $\textbf{c}=\textbf{a}\times \textbf{b}=(y_1z_2-y_2z_1,x_2z_1-x_1z_2,x_1y_2-x_2y_1)$，代入 $z_1=z_2=0$ 即 $c=(0,0,x_1y_2-x_2y_1)$。这可太好算了。

这是直线的情况，放到线段上，看一下这个交点合不合法即可。总之就是 $E=B-\frac{|\textbf{u}\times\textbf{b}|}{|\textbf{a}\times\textbf{b}|}\textbf{a}$。

#### 如何判断一个点是否在三角形内部？

有几个常用的方法。命名也许不太准确。

+ 射线定理：从这个点引出一条**不与多边形相切**的射线，那么如果射线与多边形相交的点数为**奇数**则说明在**内部**，否则在外部。容易感性理解。对任意多边形都成立。

+ 向量叉积：用叉积判一下这个点是否在每一条边的同一侧。对凸多边形成立。

+ 回转数算法：将此点与多边形的所有顶点连线，然后**将相邻两个顶点连的线的夹角相加**（有正负性），为 $0$ 则在外部，否则在内部。对任意多边形都成立。

+ 面积法：把三角形的三个顶点与这个点连边，又形成三个小三角形。很明显这个点在三角形内部仅当**三个小三角形的面积和等于原三角形**。海伦公式/叉积（如果是坐标系上）计算三角形面积即可。对凸多边形成立，叉积算面积。

本题使用面积法应该是最方便且最易于理解的。

#### 如何求出每条边被分割成了哪几条线段？

给每条边开一个 `set`，把交点扔进去去重排序一下即可。这里用 `pair` 非常方便。

------------

### 代码

事实证明写计算几何题你的码题体验直线取决于选用的实现方式。用 `pair<long double,long double>` 封装好点/向量再写可以写得非常舒适。

由于写的时候向量基础不好于是算三角形面积时没想起来有个东西叫做叉积。

upd：代码里求线段交点的地方有点小问题，求出来可能在直线（而不是线段）上。

```cpp
using ll=long long; using ld=long double;
using pii=pair<int,int>; using pll=pair<ll,ll>;
using pld=pair<ld,ld>; using lin=pair<pld,pld>;
const int I=1e9;
const ll J=1e18,N=107;
const ld eps=1e-5;
ll n;
ld ans;
pld a[N][3];
lin b[N][3];
set<pld> s[N][3];
ld operator * (pld x,pld y) { return x.fi*y.se-x.se*y.fi; }
pld operator * (pld x,ld y) { return {x.fi*y,x.se*y}; }
pld operator + (pld x,pld y) { return {x.fi+y.fi,x.se+y.se}; }
pld operator - (pld x,pld y) { return {x.fi-y.fi,x.se-y.se}; }
ld dis(pld x,pld y) { return sqrt((x.fi-y.fi)*(x.fi-y.fi)+(x.se-y.se)*(x.se-y.se)); }
ld are(ld x,ld y,ld z) { ld p=(x+y+z)/2; return sqrt(p*(p-x)*(p-y)*(p-z)); }
pld its(lin x,lin y) {
	pld xx=x.se-x.fi,yy=y.se-y.fi,zz=x.se-y.se;
	if (xx*yy==0) return {-1,0};
	else {
		ld t=(zz*yy)/(xx*yy);
		if (t<0||t>1) return {-1,0};
		return x.se-xx*t;
	}
}
bool in(pld x,pld y,pld z,pld w) {
	ld s=are(dis(x,y),dis(y,z),dis(x,z)),s1=are(dis(x,y),dis(y,w),dis(x,w)),
	s2=are(dis(x,z),dis(z,w),dis(x,w)),s3=are(dis(y,z),dis(z,w),dis(y,w));
	return abs(s-s1-s2-s3)<eps;
}
void mian() {
	scanf("%lld",&n);
	for (ll i=1;i<=n;i++) {
		for (ll j=0;j<3;j++) scanf("%Lf%Lf",&a[i][j].fi,&a[i][j].se);
		for (ll j=0;j<3;j++) b[i][j]={a[i][j],a[i][(j+1)%3]};
	}
	for (ll i=1;i<=n;i++) for (ll j=0;j<3;j++) {
		s[i][j].insert(b[i][j].fi),s[i][j].insert(b[i][j].se);
		for (ll k=1;k<=n;k++) if (k!=i) for (ll l=0;l<3;l++) {
			lin x=b[i][j],y=b[k][l];
			pld ret=its(x,y);
			if (ret.fi>=0) s[i][j].insert(ret);
		}
	}
	for (ll i=1;i<=n;i++) for (ll j=0;j<3;j++) {
		auto it=s[i][j].begin(),ti=it;
		ti++;
		for (;ti!=s[i][j].end();it++,ti++) {
			pld x=*it,y=*ti,z=(x+y)*0.5; ld flg=1;
			for (ll o=1;o<=n&&flg>0;o++) if (o!=i) if (in(a[o][0],a[o][1],a[o][2],z)) flg=0;
			ans+=flg*dis(x,y);
		}
	}
	printf("%.10Lf",ans);
}
```

---

