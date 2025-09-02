# Triangle Fun

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2432

[PDF](https://uva.onlinejudge.org/external/114/p11437.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11437/f4b807f28b80b04a563e92fb3605213be81cada3.png)

## 样例 #1

### 输入

```
2
3994.707 9251.677 4152.916 7157.810 5156.835 2551.972
6903.233 3540.932 5171.382 3708.015 213.959 2519.852```

### 输出

```
98099
206144```

# 题解

## 作者：交警 (赞：6)

## Solution
这道题其实挺惊喜的。我的想法是用比例写，本来没想着正确性，就想着乱搞（考场上很需要乱搞的能力）。其实我用比例写的原因是我觉得这道题的答案跟大三角形的面积肯定有关系，AC也证明了有这个关系。点$D$ , $E$ , $F$是唯一的，所得到的三角形也只可能是唯一的，而点$D$ , $E$ , $F$ 跟 边$AB$ , $BC$ , $CA$是比例关系，所以小三角形肯定跟大三角形呈比例关系。

### 题目传送门：[qwq](https://www.luogu.org/problemnew/solution/UVA11437)
接下来开始推导比例关系。为了便于推导，我这里不用字母而用具体数值。虽然可能有偶然性，但是上面已经证明了唯一性，所以这里的偶然性并不能保证偶然。我们用好算的数值去推一下比例关系：  
$A(-3, 0)$ $B(3,0)$  $C(3, 3)$  
然后我们画图（强烈推荐graphEQ，画图非常方便，重点：免费）  
$AC:y=\frac{1}{2}x + \frac{3}{2}$  
$BC:x=3$  
$AB:y=0$  
![](https://i.loli.net/2019/10/08/LtJkoAb4Iy2Cix9.png)  
根据比例关系我们可以求出$D$ , $E$ , $F$  
$D(3,1)$  $E(1,2)$ $F(-1,0)$  
然后我们可以求出$AD$ , $BE$ , $CF$的解析式  
$AD:y=\frac{1}{6}x + \frac{1}{2}$  
$BE:y = -x + 3$  
$CF:y=\frac{3}{4}x + \frac{3}{4}$  
![](https://i.loli.net/2019/10/08/8RKiclJGFYDgrn4.png)  
解得：  
$P(\frac{15}{7}, \frac{6}{7})$ $Q(-\frac{3}{7}, \frac{3}{7})$ $R(\frac{9}{7}, \frac{12}{7})$

然后解面积。作平行于$y$轴的直线交$AD$于$H$
$H(\frac{9}{7}, \frac{5}{7})$
$S_{PQR}=\frac{9}{7},S_{ABC}=9$
所以比例就是7啦  
求出大面积除以7  
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    scanf ( "%d", &t );
    while ( t -- )
    {
        double ax, ay, bx, by, cx, cy;
        scanf ( "%lf%lf%lf%lf%lf%lf", &ax, &ay, &bx, &by, &cx, &cy );
        double x, y, z;
        x = sqrt ( ( by - ay ) * ( by - ay ) + ( bx - ax ) * ( bx - ax ) );
        y = sqrt ( ( cy - ay ) * ( cy - ay ) + ( cx - ax ) * ( cx - ax ) );
        z = sqrt ( ( cy - by ) * ( cy - by ) + ( cx - bx ) * ( cx - bx ) );
        double S, p;
        p = ( x + y + z ) / 2;
        S = sqrt ( p * ( p - x ) * ( p - y ) * ( p - z ) );
        printf ( "%.0lf\n", S / 7 );
    }
    return 0;
}
```
好

---

## 作者：紪絽 (赞：2)

这道题的难点在于求 $\triangle ABC$ 和 $\triangle PQR$ 之间的面积关系。题目给出了 $\triangle ABC$ 三个顶点的坐标，我们可以用海伦公式求出它的面积：

$$S_{\triangle ABC} = \sqrt{p(p-a)(p-b)(p-c)}$$

其中 $a,b,c$ 为三角形三边的长，$p = \dfrac{a+b+c}{2}$。

求 $\triangle ABC$ 和 $\triangle PQR$ 之间的面积关系，我们可以用梅涅劳斯定理：如果一直线与 $\triangle ABC$ 的边 $BC, CA, AB$ 或其延长线分别交于 $L, M, N$，则有：

$$\dfrac{AN}{NB} \cdot \dfrac{BL}{LC} \cdot \dfrac{CM}{MA} = 1$$

图例：

![](https://upload.wikimedia.ahau.cf/wikipedia/commons/6/69/Menelaus_Theorem1.png)

对题目中的 $\triangle ABE$ 使用梅涅劳斯定理，可得 $\dfrac{BQ}{QE} \cdot \dfrac{EC}{CA} \cdot \dfrac{AF}{FB} = 1$，则 $\dfrac{BQ}{QE} = \dfrac{6}{1}$。

同理，$\dfrac{AP}{PD} = \dfrac{CR}{FR} = \dfrac{6}{1}$。

设 $S_{\triangle ABC} = 1$，由 $\dfrac{AF}{FB} = \dfrac{1}{2}, \dfrac{BQ}{QE} = \dfrac{AP}{PD} = \dfrac{CR}{FR} = \dfrac{6}{1}$ 可得 $S_{\triangle BCF} = \dfrac{2}{3}$，$S_{\triangle BCQ} = \dfrac{6}{7} S_{\triangle BCE} = \dfrac{6}{21},  S_{\triangle_{BPD}} = S_{\triangle AFR} = \dfrac{1}{7}S_{\triangle ABD} = \dfrac{1}{21}$。

$∴ S_{BPRF} = \dfrac{5}{7} S_{\triangle ABC} = \dfrac{5}{21}, S_{\triangle PQR} = S_{\triangle BCF} - S_{\triangle BCQ} - S_{BPRF} = \dfrac{1}{7}$，即 $S_{\triangle ABC} = 7 \cdot S_{\triangle PQR}$。

关键的两个问题求完了，代码应该就能很轻松地写出来。只要把 $\triangle ABC$ 的面积除以 $7$ 就好了。注意输入是小数，输出不是小数。代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
	{
		double xa, ya, xb, yb, xc, yc;
		scanf("%lf%lf%lf%lf%lf%lf", &xa, &ya, &xb, &yb, &xc, &yc);
		double x, y, z;
		x = sqrt((yb - ya) * (yb - ya) + (xb - xa) * (xb - xa));
		y = sqrt((yc - ya) * (yc - ya) + (xc - xa) * (xc - xa));
		z = sqrt((yc - yb) * (yc - yb) + (xc - xb) * (xc - xb));
		double s, p;
		p = (x + y + z) / 2;
		s = sqrt(p * (p - x) * (p - y) * (p - z));
		printf("%.0lf\n", s / 7);
	}
	return 0;
}

```



---

## 作者：wbh20090611 (赞：1)

看现在全是三角形面积除以七的方法，我来发个新方法的题解

### 前置芝士

1. [海伦公式](https://baike.baidu.com/item/%E6%B5%B7%E4%BC%A6%E5%85%AC%E5%BC%8F)
2. [两点间距离公式](https://baike.baidu.com/item/%E4%B8%A4%E7%82%B9%E9%97%B4%E8%B7%9D%E7%A6%BB%E5%85%AC%E5%BC%8F)
3. [余弦定理](https://baike.baidu.com/item/%E4%BD%99%E5%BC%A6%E5%AE%9A%E7%90%86)
4. [诱导公式](https://baike.baidu.com/item/%E8%AF%B1%E5%AF%BC%E5%85%AC%E5%BC%8F)
5. [三角函数](https://baike.baidu.com/item/%E4%B8%89%E8%A7%92%E5%87%BD%E6%95%B0/1652457)
6. [平行线分线段成比例定理](https://baike.baidu.com/item/%E5%B9%B3%E8%A1%8C%E7%BA%BF%E5%88%86%E7%BA%BF%E6%AE%B5%E6%88%90%E6%AF%94%E4%BE%8B%E5%AE%9A%E7%90%86)
7. [相似三角形](https://baike.baidu.com/item/%E7%9B%B8%E4%BC%BC%E4%B8%89%E8%A7%92%E5%BD%A2)

### 解决思路

#### Step 1：输入

```cpp
scanf("%lf%lf%lf%lf%lf%lf", &ax, &ay, &bx, &by, &cx, &cy);
```
#### Step 2：计算出三边的长

```cpp
A = sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by)) / 3;
B = sqrt((ax - cx) * (ax - cx) + (ay - cy) * (ay - cy)) / 3;
C = sqrt((cx - bx) * (cx - bx) + (cy - by) * (cy - by)) / 3;
```

**注：因为有三等分点除以三方便计算**

#### Step 3：相似三角形推导

![](https://cdn.luogu.com.cn/upload/image_hosting/dl946wqn.png)

在上面的图像中除了 $JQ$ 以外可以很轻易地计算出来，我详细讲一下 $JQ$ 怎么计算：

$\because$ $KE = \frac{1}{2} a$ 且 $RH = \frac{4}{7}a$\
$\therefore$ $\frac{CK}{CR} = \frac{\frac{1}{2}}{\frac{6}{7}} = \frac{7}{12}$\
$\therefore$ 设 $CK = 7x, CR = 12x$\
$\therefore$ $RK = 5x$\
又 $\because$ $\frac{BC}{EK} = \frac{\frac{1}{2}a}{3a} = \frac{1}{6}$\
$\therefore$ $\frac{KQ}{CQ} = \frac{1}{6}$\
$\therefore$ $KQ = x$\
$\therefore$ $RQ = 5x + x = 6x, CQ = 7x - x = 6x$
$\therefore$ $RQ = CQ$
$\therefore$ $KJ = \frac{1}{2}CD = a$

同理我们可以计算出其他三条线，并且我们可以发现，这三条线是三角形 RQP 的三条三等分线。

#### Step 4：三角函数推导

我们就可以看成：在这个三角形中知道三条三等分线的长度求三角形面积，所以只要求出三边即可，那么怎么求呢？

根据上面的相似我们知道：\
$BP:PG:QE=3:3:1$\
$AR:RP:PD=3:3:1$\
$CQ:QR:RF=3:3:1$

所以我们可以算出除了三边以外的所有边。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/uesoydqc.png)

通过余弦定理可以算出：\
$\cos ∠RPQ = \frac{PR^2+PQ^2-RQ^2}{2PQ \cdot PR}$\
$\cos ∠RQP = \frac{PQ^2+RQ^2-PR^2}{2PQ \cdot QR}$\
$\cos ∠QRP = \frac{PR^2-PQ^2+RQ^2}{2PR \cdot PR}$

通过诱导公式推出这三个角的补角

在下面这三个红色的三角形中再用余弦定理算出三边：

![](https://cdn.luogu.com.cn/upload/image_hosting/40mhutxb.png)

#### 最后的最后附上**代码**吧


```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
double ax, ay, bx, by, cx, cy, A, B, C, a, b, c, S, p, ja, jb, jc, x, y, z;
int main()
{
	cin >> T;
	while(T--)
	{
		scanf("%lf%lf%lf%lf%lf%lf", &ax, &ay, &bx, &by, &cx, &cy);
		A = sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by)) / 3.0;
		B = sqrt((ax - cx) * (ax - cx) + (ay - cy) * (ay - cy)) / 3.0;
		C = sqrt((cx - bx) * (cx - bx) + (cy - by) * (cy - by)) / 3.0;
		a = A / 7.0;
		b = B / 7.0;
		c = C / 7.0;
		ja = -(b * b + c * c - a * a) / (2 * b * c);
		jb = -(a * a + c * c - b * b) / (2 * a * c);
		jc = -(b * b + a * a - c * c) / (2 * b * a);
		x = b * b * 9 + c * c * 36 - 36 * b * c * ja;
		y = c * c * 9 + a * a * 36 - 36 * a * c * jb;
		z = a * a * 9 + b * b * 36 - 36 * a * b * jc;
		x = sqrt(x);
		y = sqrt(y);
		z = sqrt(z);
		p = (x + y + z) / 2;
		printf("%.0lf\n", sqrt(p * (p - x) * (p - y) * (p - z)));
	}
}
```

---

## 作者：L2_sheep (赞：1)

这道计算几何题，需要推导一下，用到一些初中的数学知识。

![推导比例关系](https://cdn.luogu.com.cn/upload/pic/45932.png)
已知三角形ABC的三点坐标，可以求出三条边长，进而求得它的面积，通过推导出的比例关系，就可以求出答案。

附上已知三角形三边长求面积的公式推导
![已知三角形三边长求面积的公式推导](https://cdn.luogu.com.cn/upload/pic/45933.png)

最后附上代码：
```cpp
#include <stdio.h>
#include <math.h>


int main()
{	 
	int n;
	double ax, ay, bx, by, cx, cy, a, b, c, t, s;
	
	scanf("%d", &n);
	while(n--){
		scanf("%lf%lf%lf%lf%lf%lf", &ax, &ay, &bx, &by, &cx, &cy);
		a = sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
		b = sqrt((ax - cx) * (ax - cx) + (ay - cy) * (ay - cy));
		c = sqrt((cx - bx) * (cx - bx) + (cy - by) * (cy - by));
		t = sqrt((a + b + c) * (a + b - c) * (a + c - b) * (b + c - a));
		printf("%.0f\n", s = t / 28.0);
	}
    
	return 0;
}

```

---

## 作者：Siteyava_145 (赞：0)

大水题。

给了你三角形三点坐标，求

![](https://cdn.luogu.com.cn/upload/image_hosting/mvugjcg8.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

内 $\triangle PQR$ 的面积。

先求出 $\dfrac{S\triangle PQR}{S\triangle ABC}$ 的比值。

这里我们可以把 $S\triangle PQR$ 看作 $S\triangle ABC - S\triangle ARC-S\triangle BQC -S\triangle ABP$。

所以 $S\triangle PQR=S\triangle ABC-3S\triangle ARC$。（易证上面的三个三角形面积相等）

另

$\begin{aligned}AR:RD & = S\triangle AFC:S\triangle DFC \\& = S\triangle AFC:S\triangle DFC\\&=\dfrac{1}{3}S\triangle ABC:\dfrac{2}{3}S\triangle BFC\\&=\dfrac{1}{3}S\triangle ABC:\dfrac{4}{9}S\triangle ABC\\&=3:4\end{aligned}$

所以 

$\begin{aligned}S\triangle ARC &=\dfrac{3}{3+4}\cdot S\triangle ADC\\&=\dfrac{2}{7}S\triangle ABC\end{aligned}$

$\begin{aligned}S\triangle PQR &=S\triangle ABC-3S\triangle ARC\\&=S\triangle ABC-\dfrac{6}{7}S\triangle ABC\\&=\dfrac{1}{7}S\triangle ABC\end{aligned}$

然后用海伦公式求出 $S\triangle ABC$，就能求出 $S\triangle PQR$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
		double ax,ay,bx,by,cx,cy;
		cin>>ax>>ay>>bx>>by>>cx>>cy;
		double A=sqrt((bx-ax)*(bx-ax)+(by-ay)*(by-ay));//勾股定理求三边长度
		double B=sqrt((bx-cx)*(bx-cx)+(cy-by)*(cy-by));
		double C=sqrt((ax-cx)*(ax-cx)+(ay-cy)*(ay-cy));
		double p=(A+B+C)/2;
		double S=sqrt(p*(p-A)*(p-B)*(p-C));
		printf("%.0lf\n",S/7);
	}
}
```


---

## 作者：F3_Dy (赞：0)

# 数学题
这道题非常简单的一道数学题，我们班的数竞生都会算这道题呢。~~（其实这是一道非常简单的计算几何基础题。）~~

## 言归正传
我们可以把这道题的问题划分为两个部分，第一个问题是求出三角形        $ABC$ 的面积，第二个问题是根据三角形 $ABC$ 的面积求出三角形 $PQR$ 的面积。那么，这个问题似乎就简单了许多。

好，兄贵们，我们来看第一个问题。一个三角形的面积该怎么求呢？学过数学竞赛的人不可能没有听说过海伦-秦九韶公式,而没有学过数学竞赛的人民也会多多少少听说过向量的叉积。我们再看这题的题面，这题的题面给了我们三角形三个顶点的坐标，更适合用向量的叉积来解决这件事，接下来我来介绍一下这种方法。简单的说，两个向量的叉积等于这两个向量组成的有向面积的两倍，我们可以根据坐标算出组成三角形的向量，然后即可算出三角形的面积。

![辅助线](https://cdn.luogu.com.cn/upload/image_hosting/99mfn6ek.png)

看来，第一个问题已经基本解决了，所以让我们来看第二个问题。我们可以考虑用构造相似三角形的方法来解决。让我们作 $AM$ // $BC$ 交 $CF$ 延长线于 $M$ 点，作 $AN$ // $BC$ 交 $BE$ 延长线于 $N$ 点，如上图所示。由 $MN$ // $BC$ 可知，三角形 $AMF$ 和三角形 $BCF$ 相似，三角形 $ANE$ 和三角形 $CBE$ 相似，进而可得 $AF$ : $FB$ = $AM$ : $BC$ = 1 : 2 ， $AE$ : $EC$ = $AN$ : $BC$ = 2 : 1 ,即 $AM = \frac{1}{2}\ BC $ , $AN=2BC$ 。再用另一组相似即可证明 $AR=\frac{3}{7}\ AD $ , $DP=\frac{1}{7}\ AD $ ，因此 $AR=RP=\frac{3}{7}\ AD$ 。由此易证三角形 $RPQ$ 的面积等于三角形 $ABC$ 面积的 $\frac{1}{7}$ 。

接下来让我们看一下完整的代码（

```cpp
#include<iostream>
using namespace std;
double x[3],y[3];
int n;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x[0]>>y[0]>>x[1]>>y[1]>>x[2]>>y[2];
		cout<<(int)(((x[1]-x[0])*(y[2]-y[0])-(x[2]-x[0])*(y[1]-y[0]))/14+0.5)<<endl;
	}
	return 0;
}
```


---

## 作者：OIer991215 (赞：0)

好像是很麻烦的数学题，也许能用几何知识证明出来S与大三角形面积的比值吧。

既然是OI题目，那我们可以考虑根据输入的坐标，题目描述的D、E、F三点从而确立三条一次函数直线。那么要求的面积的三角形的三点坐标就都求出来了。（用海伦公式）

好像还是太麻烦了。

那就打表找规律吧，既然已知大三角形三点，又通过大眼观察法看出来要求面积的三角形与大三角形长得很相似。那么可以猜测面积与大三角形有关系。根据样例进行计算，发现大三角形面积是要求三角形面积的7倍。于是这个题就做完了。。

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		double x1,x2,x3,y1,y2,y3;
		cin>>x1>>y1>>x2>>y2>>x3>>y3;
		double e1=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		double e2=sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
		double e3=sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
		double p=(e1+e2+e3)/2;
		printf("%.0lf\n",sqrt(p*(p-e1)*(p-e2)*(p-e3))/7);
	}
	return 0;
}
```

---

