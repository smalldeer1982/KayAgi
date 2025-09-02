# [ABC266C] Convex Quadrilateral

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc266/tasks/abc266_c

$ 2 $ 次元座標平面があります。$ x $ 軸正方向を右向き、$ y $ 軸正方向を上向きとします。

この平面上に自己交差のない四角形があります。  
 $ 4 $ つの頂点の座標は反時計回りに $ (A_x,A_y),(B_x,B_y),(C_x,C_y),(D_x,D_y) $ です。

この四角形が凸であるか判定してください。

なお、四角形の $ 4 $ つの内角が全て $ 180 $ 度未満であるとき、かつ、その時に限り、その四角形は凸であるといいます。

## 说明/提示

### 制約

- $ -100\ \leq\ A_x,A_y,B_x,B_y,C_x,C_y,D_x,D_y\ \leq\ 100 $
- 入力に含まれる値は全て整数である
- 与えられる $ 4 $ 点は四角形の $ 4 $ 頂点を反時計回りに並べたものである
- 与えられる $ 4 $ 点のなす四角形は自己交差がなく退化していない。すなわち
  - どの $ 2 $ 頂点も同じ座標にない
  - どの $ 3 $ 頂点も同一直線上にない
  - 隣接しない $ 2 $ 辺は共有点を持たない

### Sample Explanation 1

与えられた四角形は正方形であり、$ 4 $ つの内角は全て $ 90 $ 度です。したがって、この四角形は凸です。 !\[図\](https://img.atcoder.jp/abc266/cda66d9b9f4291781d1ce47f59f29ab0.png)

### Sample Explanation 2

角 $ A $ が $ 270 $ 度です。したがって、この四角形は凸ではありません。 !\[図\](https://img.atcoder.jp/abc266/2927f9f67e2cb7c35aeab05269b6fcc2.png)

## 样例 #1

### 输入

```
0 0
1 0
1 1
0 1```

### 输出

```
Yes```

## 样例 #2

### 输入

```
0 0
1 1
-1 0
1 -1```

### 输出

```
No```

# 题解

## 作者：ikunTLE (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc266_c)

### 思路

对于任意一个凸多边形，它的每一个角都是 $<180\degree$ 的。求四边形是否满足这个条件，可以求出 $4$ 个点所构成的 $4$ 条边的叉积，如果 $4$ 个叉积符号相同，说明它们是顺时针或逆时针排列的，可以构成一个凸四边形。

**AC CODE**

```cpp
#include<bits/stdc++.h>
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
struct node{
	int x,y;
}p1,p2,p3,p4;
int vector(node x1,node x2,node x3){
	return (x2.x-x1.x)*(x3.y-x2.y)-(x2.y-x1.y)*(x3.x-x2.x);
}
int main(){
	p1={read(),read()},p2={read(),read()},p3={read(),read()},p4={read(),read()};
	int l1=vector(p1,p2,p3),l2=vector(p2,p3,p4),l3=vector(p3,p4,p1),l4=vector(p4,p1,p2);
	printf(l1>0&&l2>0&&l3>0&&l4>0||l1<0&&l2<0&&l3<0&&l4<0?"Yes\n":"No\n");
	return 0;
}
```

---

## 作者：2020luke (赞：7)

# [[ABC266C] Convex Quadrilateral](https://www.luogu.com.cn/problem/AT_abc266_c) 题解

## 思路解析

此题思路难点就在如何判断四边形是否为凹四边形，强行计算角度需要使用三角函数公式，过于复杂，于是就需要转换思路。可以发现如果是凹四边形那么就会有一个三角形大于原四边形，并且正好等于剩下三个三角形之和，因此便可以使用这一性质判断凹四边形。

如下图，此时 $\Delta ABC + \Delta ACD + \Delta BCD = \Delta ABD$，是凹四边形。

![](https://cdn.luogu.com.cn/upload/image_hosting/klsmsc8n.png)

而对于计算面积公式的方法就很多种多样，可以采用公式法和割补法。割补法即为给原三角形套上一个大长方形，然后减去空白部分即可。如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/g6q1kswn.png)

# code

割补法计算面积部分：

```cpp
int s(int xa, int ya, int xb, int yb, int xc, int yc) {
	int mnx = min({xa, xb, xc});
	int mxx = max({xa, xb, xc});
	int mny = min({ya, yb, yc});
	int mxy = max({ya, yb, yc});
	int tot = (mxx - mnx) * (mxy - mny) * 2;
	int tri1 = abs(xa - xb) * abs(ya - yb);
	int tri2 = abs(xb - xc) * abs(yb - yc);
	int tri3 = abs(xa - xc) * abs(ya - yc);
	int rec1 = min((abs(xa - xb)) * abs(ya - yc), abs(xa - xc) * abs(ya - yb)) * 2;
	int rec2 = min((abs(xa - xb)) * abs(yb - yc), abs(xb - xc) * abs(ya - yb)) * 2;
	int rec3 = min((abs(xb - xc)) * abs(ya - yc), abs(xa - xc) * abs(yb - yc)) * 2;
	if(xa == mxx || xa == mnx || ya == mxy || ya == mny) rec1 = 0;
	if(xb == mxx || xb == mnx || yb == mxy || yb == mny) rec2 = 0;
	if(xc == mxx || xc == mnx || yc == mxy || yc == mny) rec3 = 0;
	return tot - tri1 - tri2 - tri3 - rec1 - rec2 - rec3;
}
```

公式法及代码剩余部分：

```cpp
#include<bits/stdc++.h>
using namespace std;
int s(int xa, int ya, int xb, int yb, int xc, int yc) {
	return abs((xb - xa) * (yc - ya) - (xc - xa) * (yb - ya));
}
int main() {
	int xa, ya, xb, yb, xc, yc, xd, yd;
	cin >> xa >> ya >> xb >> yb >> xc >> yc >> xd >> yd;
	int tri1 = s(xa, ya, xb, yb, xc, yc);
	int tri2 = s(xa, ya, xb, yb, xd, yd);
	int tri3 = s(xa, ya, xc, yc, xd, yd);
	int tri4 = s(xb, yb, xc, yc, xd, yd);
	if(tri1 + tri2 + tri3 == tri4) {
		cout << "No";
		return 0;
	}
	if(tri1 + tri2 + tri4 == tri3) {
		cout << "No";
		return 0;
	}
	if(tri1 + tri3 + tri4 == tri2) {
		cout << "No";
		return 0;
	}
	if(tri2 + tri3 + tri4 == tri1) {
		cout << "No";
		return 0;
	}
	cout << "Yes";
	return 0;
}
```

---

## 作者：zzhbpyy (赞：4)

### [原题传送门](https://www.luogu.com.cn/problem/AT_abc266_c)

## 思路

本题方法较多，此题解介绍较为简单易懂的面积法。

与另一篇题解不同，此处介绍高斯鞋带定理：[鞋带定理](https://zhuanlan.zhihu.com/p/575204782)。

计算四边形面积 $ss$ 和四边形**四个顶点构成的三个三角形**中面积最大值 $st$，若 $ss > st$ 则为凸四边形，否则为凹四边形。具体公式请见代码。

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int ax,ay,bx,by,cx,cy,dx,dy;
double ss,st;
signed main(){
	cin>>ax>>ay>>bx>>by>>cx>>cy>>dx>>dy;
	ss=(ax*by+bx*cy+cx*dy+dx*ay
	-ax*dy-bx*ay-cx*by-dx*cy)/2.0;
	ss=fabs(ss);//一定别忘取绝对值！！！
	st=max(abs(ax*by+bx*cy+cx*ay-bx*ay-cx*by-ax*cy)
	,max(
	max(   abs(ax*by+bx*dy+dx*ay-bx*ay-dx*by-ax*dy)
	,	   abs(ax*dy+dx*cy+cx*ay-dx*ay-cx*dy-ax*cy))
	,	   abs(bx*dy+dx*cy+cx*by-dx*by-cx*dy-bx*cy)
	))/2.0;
	if(ss>st)cout<<"Yes\n";
	else cout<<"No\n";
} 
```
感谢温岭市第三中学陈玲玲老师教我这么好用的公式。

---

## 作者：PigNotFound (赞：2)

其他题解用的都是面积来判，这里我还有另一种解法。
根据凸四边形的定义，只要四边形每条边除了顶点以外的另外两个点都在这条边的同一侧就是凸四边形。如果不会判点在边哪一侧，左转[这里](https://blog.csdn.net/qq_39027890/article/details/125803790)。
代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long double d;
struct point{
    d x, y;
};
bool left_or_right(point a, point b, point c) {
    d tmp = (b.x - c.x) / (b.y - c.y) * (a.y - c.y) + c.x;
    if (tmp > a.x)
        return 1; //左侧
    return 0;
}

int main() {
    vector<point> pos;
    for (int i = 0; i < 4; i++) {
        point cur;
        cin >> cur.x >> cur.y;
        pos.push_back(cur);
    }
    bool flag = 1;
    for (int i = 0; i < 4; i++) {
        int c = -1;
        for (int j = 0; j < 4; j++) {
            if (i != j and (i + 1) % 4 != j) {
                if (c == -1)
                    c = left_or_right(pos[j], pos[(i + 1) % 4], pos[i]);
                else
                    flag &= (c == left_or_right(pos[j], pos[(i + 1) % 4], pos[i]));
            }
        }
    }
    cout << (flag ? "Yes" : "No");
    return 0;
}

```

---

## 作者：Luogu_916767 (赞：1)

[In Luogu](https://www.luogu.com.cn/problem/AT_abc266_c)

### 题目大意

给定 $4$ 个点的坐标，求这 $4$ 个点按顺序组成的四边形是不是凸四边形。

### 思路分析

题目中明确说明，两组对边均不相交。

如果此四边形是凹四边形，一定会有一个点是在另外 $3$ 个点围成的三角形中。如下图：

![如图](https://cdn.luogu.com.cn/upload/image_hosting/yy5ysd87.png)

此时存在 $S_{\bigtriangleup}ABC + S_{\bigtriangleup}BCD + S_{\bigtriangleup}CDA = S_{\bigtriangleup}ABC$，则这个四边形是凹四边形。

所以，我们就有了一个思路，求出每一个小三角形的面积，判断最小的 $3$ 个三角形面积之和是否等于最大的三角形面积之和，若相等，则这个四边形不是凸四边形，否则，这个四边形是凸四边形。

### Code

代码较丑，大佬勿喷。

```cpp
#include<bits/stdc++.h>

using namespace std;

double len(double ax,double ay,double bx,double by){
    //勾股定理计算边长
    return sqrt(abs(ax - bx) * abs(ax - bx) + abs(ay - by) * abs(ay - by));
}

double heron(double ax,double ay,double bx,double by,double cx,double cy){
    //Heron公式计算三角形面积
    double lab,lbc,lca;
    lab = len(ax,ay,bx,by);
    lbc = len(bx,by,cx,cy);
    lca = len(cx,cy,ax,ay);
    double p = (lab+lbc+lca)/2.0000;
    return sqrt(p*(p-lab)*(p-lbc)*(p-lca));
}

double ax,ay,bx,by,cx,cy,dx,dy;
double a[4];

int main(){
    cin>>ax>>ay>>bx>>by>>cx>>cy>>dx>>dy;
    a[0] = heron(ax,ay,bx,by,cx,cy);//求三角形ABC的面积
    a[1] = heron(ax,ay,bx,by,dx,dy);//求三角形ABD的面积
    a[2] = heron(ax,ay,cx,cy,dx,dy);//求三角形ACD的面积
    a[3] = heron(bx,by,cx,cy,dx,dy);//求三角形BCD的面积
    sort(a,a+4);
    if(abs(a[3] - (a[0] + a[1] + a[2])) <= 0.000001){//这样写是为了减小精度丢失造成的影响
        cout<<"No";
    }else{
        cout<<"Yes";
    }
}
```

---

## 作者：Vitamin_B (赞：1)

# 思路
提供一种不太一样的方法。首先，因为四边形内角和为 $360\degree$，所以不可能有两个角同时 $>180\degree$，因此凹四边形有且只有一种方法可以沿一条对角线分割求面积，而凸四边形的两组对角线都可以分割求面积，所以我们只要判断四边形分别沿两条对角线分割出的两个三角形面积和是否相同就可以。注意精度误差！！！
# 代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
const double eps = 1e-9; //精度误差
int x[5], y[5];
double dis (int x1, int x2, int y1, int y2) { //两点间的直线距离
	return sqrt ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
double s (int x1, int y1, int x2, int y2, int x3, int y3) { //海伦公式求面积
	const double a = dis (x1, x2, y1, y2), b = dis (x1, x3, y1, y3), c = dis (x2, x3, y2, y3), p = (a + b + c) / 2;
	return sqrt (p * (p - a) * (p - b) * (p - c));
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	for (int i = 0; i < 4; ++ i)
		cin >> x[i] >> y[i];
	cout << (fabs ((s (x[0], y[0], x[1], y[1], x[2], y[2]) + s (x[0], y[0], x[3], y[3], x[2], y[2])) - (s (x[1], y[1], x[3], y[3], x[0], y[0]) + s (x[1], y[1], x[3], y[3], x[2], y[2]))) < eps ? "Yes" : "No"); //用差比较可以判断精度误差
	I AK IOI
}
```

---

## 作者：yanxu_cn (赞：0)

法一：我会求解析式！考虑凸四边形的边的性质，可以判对于每一条边，不在边上的两点均在其同侧。所以暴力求边的解析式。斜截式还是很方便的，但是要特判平行于纵轴的边，将其斜率取一个接近于 $+\infty$ 的值，否则概率性 RE。其实用一般式最为通用，但是一般式是高中解析几何内容，而且代码写起来也不太方便，就算了。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast","unroll-loops","inline")
typedef pair<int,int> pii;
inline constexpr bool check(pii x,pii y,pii a,pii b)
{
	long double k=0;
	if(x.first==y.first)k=1e10;//特判竖直的边
	else k=(long double)(y.second-x.second)/(y.first-x.first);
	long double b0=x.second-x.first*k;
	if((k*a.first+b0<a.second&&k*b.first+b0<b.second)||
	(k*a.first+b0>a.second&&k*b.first+b0>b.second))
	return true;
	else return false;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	pii a,b,c,d;
	cin>>a.first>>a.second>>
	b.first>>b.second>>
	c.first>>c.second>>
	d.first>>d.second;
	if(check(a,b,c,d)&&check(b,c,d,a)&&check(c,d,a,b)&&check(d,a,b,c)) cout<<"Yes\n";
	else cout<<"No\n";
	return 0;
}
```

法二：我会求解析式！判其余两点是否在对角线两侧。这个挺显然的。代码和上面大差不差。

法三：我会求面积！我们分别使用海伦公式之类的方法求以任意三个四边形为顶点的三角形面积。如果其中一个等于其他三个面积之和，则是不是凸四边形。

法四：我会用向量求角！考虑暴力求出四个顶点上小于平角的角。如果四角之和为 $2\pi$ 则是凸四边形；外角定理告诉我们如果一个角的大小为其他三个角的

法五：我会求边的解析式！我们求任意两条对边的解析式。如果两条对边所在的直线交点位于其中一边上则为凹四边形。注意特判平行。

---

## 作者：4041nofoundGeoge (赞：0)

初三党欢喜！

## 思路 $1$

下面的题解蒟蒻看不懂，我来介绍一种直接的做法！三角函数。

首先，研究这个问题，建立平面直角坐标系，原点为 $H$。我们先设四个坐标 $A(x_a,y_a)$、$B(x_b,y_b)$、$C(x_c,y_c)$、$D(x_d,y_d)$。我们过 $A$ 点做垂线，交 $B$ 的延长线于一点，同理我们设出 $F$ 和 $G$，如下图所示：（$E$ 是个多余的点）

![](https://cdn.luogu.com.cn/upload/image_hosting/aint737a.png)

根据上图我们可以求出 $BH$ 和 $AH$ 的长度（因为长度因情况讨论，故不列出 $BH$ 和 $AH$ 的长度代数式）。我们根据勾股定理可以求出 $AB=\sqrt{AH^2+BH^2}$。接着我们根据小学二年级学习的三角函数轻松求出

$$\sin{∠HAB}=\dfrac{HB}{AB}$$

以及

$$\sin{∠HBA}=\dfrac{HA}{AB}$$

同理另外几个角也可以求出来了。角度全知道了，那么四边形的内角也就知道了，这道题也就呼之欲出了！

## 思路 $2$

高中狂喜！

我们还可以用向量！

我们直接给出推论：对于两个不同的点 $A=(A_x,A_y)$、$B=(B_x,B_y)$，如果 $A_xB_y-A_yB_x>0$，则 $∠AOB<180°$。

![](https://cdn.luogu.com.cn/upload/image_hosting/0mcfwok4.png)

具体证明方法，要用到向量积。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
  int n = 4;
  vector<pair<int,int>> points(n);
  for (auto &&[x, y] : points) {
    cin >> x >> y;
  }
  int fail = 0;
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n, k = (i + 2) % 4;
    int x1 = points[j].first - points[i].first;
    int x2 = points[k].first - points[j].first;
    int y1 = points[j].second - points[i].second;
    int y2 = points[k].second - points[j].second;
    if (x1 * y2 - x2 * y1 <= 0) fail = 1;
  }
  if (fail)
    cout << "No\n";
  else
    cout << "Yes\n";
}
int main() {
  solve();
}
```

---

## 作者：Euclid_llq (赞：0)

### 题目解析

就是给你平面直角坐标系上的四个点，判断由着四个点围成的图形是否是凸四边形。

那么四边形有个重要而基本的性质，就是内角和等于 $360\degree$（至于为什么我这里没说是凸四边形，等下解释）。而凸四边形的每个内角都小于 $180\degree$。

### 解题思路

看到评论区里[有位大佬用的向量](https://www.luogu.com.cn/discuss/888759)。仔细想了一下，用向量解决是可行的，因为通过向量确实可以求出角度。

前置知识：[向量](https://oi-wiki.org/math/linear-algebra/vector/)。

设有两个向量 $\bold{a}=\lparen x1,y1\rparen，\bold{b}=\lparen x2,y2 \rparen$，则两向量夹角 $\theta$ 的余弦 $\cos \theta= \frac{\bold{a}\cdotp\bold{b}}{\lvert\bold{a}\rvert\cdotp\lvert\bold{b}\rvert}$，其中 $\bold{a}\cdotp\bold{b}$ 表示向量 $\bold{a}$ 与 $\bold{b}$ 的数量级，记为 $\bold{a}\cdotp\bold{b}=x1\cdotp x2+y1\cdotp y2$。$\lvert\bold{a}\rvert$ 表示 $\bold{a}$ 的模（你可以把它理解为向量的长度），记为 $\lvert\bold{a}\rvert=\sqrt{x1^2+y1^2}$。

综上可得，向量 $\bold{a}$ 与向量 $\bold{b}$ 形成的夹角为：$\theta=\arccos(\frac{x1\cdotp x2+y1\cdotp y2}{\sqrt(x1^2+y1^2)\cdotp \sqrt(x2^2+y2^2)})$。但是由于反余弦函数 $\arccos$ 在弧度制下的值域是 $[0,\pi]$（即角度制下的 $[0,180\degree]$），所以即便两向量夹角大于 $180\degree$，返回的也只能是一个小于 $180\degree$ 的角，那么四个向量（也就是四边形的四条边）形成的角度之和就会比 $360\degree$ 小了，也就不是凸四边形。

### 注意事项

- 题目中说明，四个点按逆时针给出，建向量时一定要按这个顺序；

- 由于开了根号，结果可能会有误差，所以就像二分小数时的做法那样，判断四个角的和与 $360\degree$ 的差是否小于 $0.001$ 即可；

- 最后，如果你的第一个向量是 $(bx-ax,by-ay)$，那么请你在后面不要出现 $(bx-cx,by-cy)$ 等诸如此类的东西，因为作者这么写，调了快有半小时！

### 给出代码


```cpp
#include<bits/stdc++.h>
#include<cmath>
#define PI 3.1415926
#define pii pair<int,int>
using namespace std;
int times(pii A,pii B){return A.first*B.first+A.second*B.second;}
double iv(pii A){return sqrt(A.first*A.first+A.second*A.second);}
int main(){
	int ax,ay,bx,by,cx,cy,dx,dy;
	cin>>ax>>ay>>bx>>by>>cx>>cy>>dx>>dy; 
	pii vab=make_pair(bx-ax,by-ay);
	pii	vbc=make_pair(cx-bx,cy-by);
	pii vcd=make_pair(dx-cx,dy-cy);
	pii vda=make_pair(ax-dx,ay-dy);
	double a=acos(times(vab,vbc)/(iv(vab)*iv(vbc)));
	double b=acos(times(vbc,vcd)/(iv(vbc)*iv(vcd)));
    double c=acos(times(vcd,vda)/(iv(vcd)*iv(vda)));
	double d=acos(times(vda,vab)/(iv(vda)*iv(vab)));
	if(abs(a+b+c+d-2*PI)<=0.0001)printf("Yes\n");
	else printf("No\n");
	return 0;
}
```
这是本蒟蒻的第一篇题解，不喜勿喷，感谢您耐心看完。

---

## 作者：封禁用户 (赞：0)

## 思路

很水一道题。

[前置知识——向量](https://oi-wiki.org/math/linear-algebra/vector/)

看到这道题其实可以联想到叉积的。对于凸多边形，它的内角一定小于180度，所以，如果其每一对相邻的边所形成的向量叉积都指向同一侧（即同为顺时针或者同为逆时针），那么这个四边形是凸的。

## Code

```cpp
#include <iostream>
using namespace std;

inline int cros(int x1, int y1, int x2, int y2) { return x1 * y2 - y1 * x2; }

int main() 
{
    int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
    cin >> Ax >> Ay >> Bx >> By >> Cx >> Cy >> Dx >> Dy;
	//计算叉积 
    int cross1 = cros(Bx - Ax, By - Ay, Cx - Bx, Cy - By);
    int cross2 = cros(Cx - Bx, Cy - By, Dx - Cx, Dy - Cy);
    int cross3 = cros(Dx - Cx, Dy - Cy, Ax - Dx, Ay - Dy);
    int cross4 = cros(Ax - Dx, Ay - Dy, Bx - Ax, By - Ay);
	//检测 
    if ((cross1 > 0 && cross2 > 0 && cross3 > 0 && cross4 > 0) 
	|| (cross1 < 0 && cross2 < 0 && cross3 < 0 && cross4 < 0)) 
        cout << "Yes" << endl;
	else  cout << "No" << endl;
    return 0;
}
```

---

