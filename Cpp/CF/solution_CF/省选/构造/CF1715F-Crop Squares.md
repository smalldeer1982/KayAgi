# Crop Squares

## 题目描述

This is an interactive problem.

Farmer Stanley grows corn on a rectangular field of size $  n \times m  $ meters with corners in points $ (0, 0) $ , $ (0, m) $ , $ (n, 0) $ , $ (n, m) $ . This year the harvest was plentiful and corn covered the whole field.

The night before harvest aliens arrived and poisoned the corn in a single $ 1 \times 1 $ square with sides parallel to field borders. The corn inside the square must not be eaten, but you cannot distinguish it from ordinary corn by sight. Stanley can only collect a sample of corn from an arbitrary polygon and bring it to the laboratory, where it will be analyzed and Stanley will be told the amount of corn in the sample that was poisoned. Since the harvest will soon deteriorate, such a study can be carried out no more than $ 5 $ times.

More formally, it is allowed to make no more than $ 5 $ queries, each of them calculates the area of intersection of a chosen polygon with a square of poisoned corn. It is necessary to find out the coordinates of the lower-left corner of the drawn square (the vertex of the square with the smallest $ x $ and $ y $ coordinates).

## 说明/提示

In the first test from the statement, the aliens poisoned a square of corn with vertices at points with coordinates $ (1.5, 0.5) $ , $ (1.5, 1.5) $ , $ (2.5, 1.5) $ , $ (2.5, 0.5) $ . In the picture, it is red, the polygon selected in the query is blue, and their intersection is green.

Picture for the first query:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1715F/5905e23dc243a04aad10e5bcbe0e2cd6bb70131e.png)Picture for the second query:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1715F/55886132a04f6c81b89194c1c281874f100d6c79.png)

## 样例 #1

### 输入

```
3 3





0.5





0.5```

### 输出

```
? 4
0 0
2 0
2 3
0 3

? 4
0 0
0 1
3 1
3 0

! 1.5 0.5```

# 题解

## 作者：NoirCube1 (赞：11)

## CF1715F Crop Squares

### 说在前面

你可以每看完一个 Hint 过后进行思考，如果想不出来或者代码无法通过再看下面一个 Hint，而不是看到题目直接把这篇题解冲完。

### Hint 1

考虑像下图一样构造多边形：

![](https://cdn.luogu.com.cn/upload/image_hosting/57cg8qlo.png)

### Hint 2

如 **Hint 1**，对于答案的 $y$ 值和重叠面积 $s_0$，有一定的函数关系，一个 $y$ 对应一个 $s_0$，一个 $s_0$ 对应一个 $y$。

![](https://cdn.luogu.com.cn/upload/image_hosting/bo2oaqs1.png)

换言之，同一 $y$ 值得到的重叠面积相同，同一重叠面积得到的 $y$ 值相同，

### Hint 3

容易得到，重叠面积是一个 $\frac{y}{m}\times 1$ 的矩形加上一个 $\frac{1}{m}\times1$ 的直角三角形，即，$s_0=\frac{y+0.5}{m}$，稍微变化下形式即可得到 $y=s_0m-0.5$。

证明略，运用相似即可。

### Hint 4

同理的锯齿状，横着询问，对于重叠面积 $s_1$ 同理得到 $x=s_1n-0.5$。

这样，在两次询问内，我们就得到了答案的 $x,y$。

### Hint 5（一些细节）

注意到这样的锯齿状不被认为是封闭的多边形，所以我们可以将这些点稍微下调 $10^{-7}$ 个单位长度即可：

![](https://cdn.luogu.com.cn/upload/image_hosting/t2mz7zzr.png)

如图，橙色的点下调即可。（横式同理）

当然，还有别的解决方案，可以保证精度，即：（图片来源：官方题解）

![](https://espresso.codeforces.com/f8fbbde4a353dfda4f4d7b0dc70b75a7fda9d3ff.png)

### Solution

对于 C++ 语言，`cout << endl` 会自动刷新缓存，所以可以不使用 `cout << flush`。

本题的询问次数很少，所以你刷不刷新都没关系。

[AC link](https://codeforces.com/contest/1715/submission/169294236)

```cpp
void query(int x, int y, long double &d, bool opt) {
	printf("? %d\n", 2 * x + 2);
	for(int i = 0; i < x; i++) {
		int tx = i, ty = 0, ttx = i, tty = y;
		if(opt) {
			printf("%d %d\n", ty, tx);
			printf("%d %d.99999999\n", tty, ttx);
		}
		else {
			printf("%d %d\n", tx, ty);
			printf("%d.99999999 %d\n", ttx, tty);
		}
	}
	if(opt) printf("%d %d\n%d %d\n", y, x, y, 0);
	else printf("%d %d\n%d %d\n", x, y, 0, y);
	cin >> d;

	return ;
}
signed main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	long double s0, s1;
	query(n, m, s0, 0);
	query(m, n, s1, 1);
	printf("! %.8Lf %.8Lf\n", s1 * n - 0.5, s0 * m - 0.5);
	return 0;
}
```

---

## 作者：BigSmall_En (赞：3)

### [CF1715F](https://www.luogu.com.cn/problem/CF1715F) Crop Squares solution

> 有一个 $n \times m$ 的长方形，四个角的坐标分别为 $ (0, 0) $ , $ (0, m) $ , $ (n, 0) $ , $ (n, m) $。在长方形里面有一个 $1 \times 1$ 的正方形，边平行于长方形边界。你需要询问出这个正方形的位置。每次询问，每次你可以询问正方形与你提问的多边形的相交面积。你最多可以进行 $5$ 次询问。
>
> 额外信息：答案要求精度为 $10^{-6}$，而询问和回复的精度为 $10^{-15}$。

题解给出的做法非常巧妙，但是数学巨佬 [majorGYY](https://codeforces.com/profile/MajorGYY) 给出了另一种实用的方法。

一个通用的思路是分别询问出纵坐标和横坐标。

如图，黑色框为总的范围，蓝色矩形的宽度互不相等，两个蓝色矩形之间的间隔为 $1.0$，红色为要求的正方形。

![](https://cdn.luogu.com.cn/upload/image_hosting/7ahidpng.png)

可以发现一个正方形恰好只会覆盖一个蓝色矩形，同时如果是覆盖了整个矩形的宽（即矩形较短的一边）的话，还能发现覆盖的面积的值就是矩形的宽。又因为每个矩形的宽互不相同，那么可以得到正方形的大致位置。

为了保证正方形完全覆盖矩形的宽，我们可以给矩形的宽定一个很小的值，这样没有被完全覆盖的概率就很小了。

确定了正方形的大致位置后，我们需要第二次询问来定位正方形一个坐标的具体值，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/vntld9hk.png)

我们查询上次覆盖的矩形到坐标轴所形成的矩形与正方形的交，可以得出面积交即为上次覆盖矩形的坐标减去这个正方形的坐标。自此就得到了矩形的一个精准坐标，花费 $2$ 次询问，然后另一个坐标用同样的方法做就好了，一共 $4$ 次询问。

那么这时就会有同学说了，第一次查询时候不是要查询 $n$ 个矩形吗，怎么就能一次搞定呢？其实也好办，题目并不要求一定是凸多边形，我们只需要给这 $n$ 个矩形一个公共的矩形作为底即可，这个作为底的矩形宽度还要远小于其他矩形的宽。

#### 实现

我是给作为查询的蓝色矩形在 $[10^{-12},10^{-10}]$ 的取值范围，作为底的矩形的宽度取到 $10^{-14}$。然后没有调参什么的就一遍过了。

其他实现见代码，不涉及斜率什么的计算几何知识，应该不是很难。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;
const ld EPS=1e-14;
mt19937 gen(chrono::system_clock::now().time_since_epoch().count());
uniform_real_distribution<ld>lent(1e-10,1e-12);
const int N=103;
int n,m;
ld hei[N],ansx,ansy,area,pos[N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)hei[i]=lent(gen);
	sort(hei+1,hei+1+n);
	ld x=0;
	cout<<"? "<<4*n+2<<endl;
	cout<<fixed<<setprecision(15)<<x<<' '<<0.0<<endl<<flush;
	for(int i=1;i<=n;++i){
		cout<<fixed<<setprecision(15)<<x<<' '<<EPS<<endl<<flush;
		cout<<fixed<<setprecision(15)<<x<<' '<<(ld)m<<endl<<flush;
		x+=hei[i];
		pos[i]=x;
		cout<<fixed<<setprecision(15)<<x<<' '<<(ld)m<<endl<<flush;
		cout<<fixed<<setprecision(15)<<x<<' '<<EPS<<endl<<flush;
		if(i!=n)x+=1.0;
	}
	cout<<fixed<<setprecision(15)<<x<<' '<<0.0<<endl<<flush;
	cin>>area;
	int loc=lower_bound(hei+1,hei+1+n,area)-hei;
	if(fabs(area-hei[loc])>fabs(area-hei[loc-1]))loc=loc-1;
	cout<<"? "<<4<<endl<<flush;
	cout<<0<<' '<<0<<endl<<flush;
	cout<<0<<' '<<m<<endl<<flush;
	cout<<fixed<<setprecision(15)<<pos[loc]<<' '<<(ld)m<<endl<<flush;
	cout<<fixed<<setprecision(15)<<pos[loc]<<' '<<0.0<<endl<<flush;
	cin>>area;
	ansx=pos[loc]-area;
	
	for(int i=1;i<=m;++i)hei[i]=lent(gen);
	sort(hei+1,hei+1+m);
	x=0;
	cout<<"? "<<4*m+2<<endl;
	cout<<fixed<<setprecision(15)<<0.0<<' '<<x<<endl<<flush;
	for(int i=1;i<=m;++i){
		cout<<fixed<<setprecision(15)<<EPS<<' '<<x<<endl<<flush;
		cout<<fixed<<setprecision(15)<<(ld)n<<' '<<x<<endl<<flush;
		x+=hei[i];
		pos[i]=x;
		cout<<fixed<<setprecision(15)<<(ld)n<<' '<<x<<endl<<flush;
		cout<<fixed<<setprecision(15)<<EPS<<' '<<x<<endl<<flush;
		if(i!=m)x+=1.0;
	}
	cout<<fixed<<setprecision(15)<<0.0<<' '<<x<<endl<<flush;
	cin>>area;
	loc=lower_bound(hei+1,hei+1+m,area)-hei;
	if(fabs(area-hei[loc])>fabs(area-hei[loc-1]))loc=loc-1;
	cout<<"? "<<4<<endl<<flush;
	cout<<0<<' '<<0<<endl<<flush;
	cout<<n<<' '<<0<<endl<<flush;
	cout<<fixed<<setprecision(15)<<(ld)n<<' '<<pos[loc]<<endl<<flush;
	cout<<fixed<<setprecision(15)<<0.0<<' '<<pos[loc]<<endl<<flush;
	cin>>area;
	ansy=pos[loc]-area;
	cout<<"! "<<fixed<<setprecision(15)<<ansx<<' '<<ansy<<endl<<flush;
	return 0;
}
```

#### 后记

再次感谢 majorGYY 提供的全新思路（如有雷同，纯属巧合）。此外这个做法对精度以及一些细节的要求比较严格，我实现的时候肯定也有地方处理不当，相信是可以被 hack 的，还请大家多多指正。

---

## 作者：ExplodingKonjac (赞：3)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1715F)**

人类高质量诈骗题。

## 题目分析

一个显然的想法是二分出横坐标和纵坐标，但是给的次数太少了。

注意到题目返回的是精确值，所以肯定要用精确值算的。

考虑一个锯齿形：

![](https://cdn.luogu.com.cn/upload/image_hosting/r9g2ptc9.png)

然后你惊奇地发现，由于锯齿的周期性，中间这个蓝色正方形在范围内左右平移不会改变与锯齿相交的面积，也就是说，这个面积之和 $y$ 有关。

然后你使用小学数学知识就可以算出 $y=m-mS-\dfrac{1}{2}$。

把这个图形旋转 $90^\circ$ 后也可以得到 $x=n-nS-\dfrac{1}{2}$。

这样就以 $2$ 次询问完成了该题。这题的 $5$ 次询问是纯纯的诈骗。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m;
double ansx,ansy;
int main()
{
	double S;
	cin>>n>>m;

	cout<<"? "<<(2*n+2)<<'\n';
	for(int i=0;i<n;i++) cout<<i<<' '<<0<<'\n'<<(i+1)<<' '<<m<<'\n';
	cout<<n<<" -1\n"<<"0 -1\n";
	fflush(stdout);
	cin>>S,ansy=m-m*S-0.5;

	cout<<"? "<<(2*m+2)<<'\n';
	for(int i=0;i<m;i++) cout<<0<<' '<<i<<'\n'<<n<<' '<<(i+1)<<'\n';
	cout<<"-1 "<<m<<"\n-1 0\n";
	fflush(stdout);
	cin>>S,ansx=n-n*S-0.5;
	
	printf("! %.10lf %.10lf",ansx,ansy);
	fflush(stdout);
	return 0;
}
```


---

## 作者：OE_AiHAn (赞：0)

## [CF1715F](https://codeforces.com/problemset/problem/1715/F)

### 题意
给定一个 $n \times m$ 的矩形区域，区域内有一个边长为 $1$ 的正方形。交互最多五次进行询问，每次询问可以给出一个不自交的多边形（不要求为凸多边形），评测姬返回该多边形与正方形的交的面积。要求猜测正方形的靠原点方向的顶点坐标 $(x, y)$。

### 解析
这题在CF上有计算几何标签，但没涉及多少计算几何相关，更像是一道思维题。

官方题解为使用横纵两个方向的锯齿形多边形进行两次询问。这里使用另一种思路，仅从横向（或纵向）单个方向构造多边形，使用 2 到 3 次询问。

这里使用下面样例进行解释：

```Python
6 5
2.2 3
```

由于要查找的正方形边长固定为 $1$，我们以上面样例构造如下图的矩形波：

![](https://cdn.luogu.com.cn/upload/image_hosting/ggsc26at.png)

作为第一次询问，我们得到 $res_1$，得到的结果用于后面对齐询问的横坐标，此时的询问能计算出 $x$ 为 $C + res_1$ 或 $C - res_1$，其中 $C$ 为整数。

第二次询问将第一次询问的多边形向右移动 $1 - res_1$，确认 $x$ 为 $C + res_1$ 还是 $C - res_1$。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/jztkypur.png)

如果询问得到的 $res_2$ 为 $1$ 则 $x$ 为 $C - res_1$。

第三次询问。设偏移距离 $l$，若 $x = C - res_1$ 则 $l = 1 - res_1$；否则 $l = res_1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/xzrb3d7w.png)

构造如图多边形，如图中所示，$A_1A_2$ 及其它与 $A_1A_2$ 位于同一直线上的线段的长度成等差数列，设 $step$，这些线段的长度从左到右依次为 $step, step \times 2, step \times 3, \dots, step \times (n - 1)$；$A_1A_3$ 及其它斜线斜率 $k$ 均为 $- \frac{m}{step}$。

第三次询问得到的面积 $res_3$，则有答案：

$$x = l + \left \lfloor \frac{res_3}{step} \right \rfloor$$

$$y = k \times (res_3 - \left \lfloor \frac{res_3}{step} \right \rfloor \times step) + m - 0.5$$
（利用直线方程 $y_0 = k \times x_0 + m$ 计算得到的结果为正方形中心的纵坐标，因而需要减去 $0.5$）。

### 代码
```c++
#include <bits/stdc++.h>
#include <unordered_map>
#define LL long long
#define pii pair<int, int>
#define pll pair<LL, LL>
#define double long double
#define pdd pair<double, double>
#define eps 1e-15

using namespace std;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int n, m;
    double res1, res2, l, res3;
    cin >> n >> m;
    
    //第一次询问
    printf("? %d\n", max(n + 1 >> 1 << 2, 8)); //这里取至少8是因为循环前后直接进行了两次坐标输出
    printf("0 -1\n0 %d\n1 %d\n1 0\n", m, m);
    int idx = 3;
    for (; idx <= n - 2; idx += 2)
        printf("%d 0\n%d %d\n%d %d\n%d 0\n", idx - 1, idx - 1, m, idx, m, idx);
    printf("%d 0\n%d %d\n%d %d\n%d -1\n", idx - 1, idx - 1, m, idx, m, idx);
    fflush(stdout);
    cin >> res1;

    if (fabs(res1 - (double)1.0) <= eps || fabs(res1 - (double)0.0) <= eps) //对横坐标在允许误差内是否为整数进行判断
        l = 0.0;
    else
    {
        //第二次询问
        printf("? %d\n",max(n + 1 >> 1 << 2, 8));
        printf("%.15LF -1\n%.15LF %d\n%.15LF %d\n%.15LF 0\n", (double)1.0 - res1, (double)1.0 - res1, m, (double)2.0 - res1, m, (double)2.0 - res1);
        int idx = 3;
        for (; idx <= n - 2; idx += 2)
            printf("%.15LF 0\n%.15LF %d\n%.15LF %d\n%.15LF 0\n", (double)idx - res1, (double)idx - res1, m, (double)(idx + 1) - res1, m, (double)(idx + 1) - res1);
        printf("%.15LF 0\n%.15LF %d\n%.15LF %d\n%.15LF -1\n", (double)idx - res1, (double)idx - res1, m, (double)(idx + 1) - res1, m, (double)(idx + 1) - res1);
        fflush(stdout);
        cin >> res2;

        if (fabs(res2 - (double)1.0) <= eps)
            l = (double)1.0 - res1;
        else
            l = res1;
    }

    //第三次询问
    printf("? %d\n", (n << 2) + 1);
    double step = 0.00390625; //步长设为2的幂次防止丢精度
    printf("%.15LF -1\n%.15LF -1\n%.15LF %d\n%.15LF 0\n%.15LF 0\n", l + (double)n, l, l, m, l + step, l + (double)1.0);
    for (int i = 1; i < n; i++)
        printf("%.15LF %d\n%.15LF %d\n%.15LF 0\n%.15LF 0\n", l + (double)i, m, l + (double)i + (double)i * step, m, l + (double)i + (double)(i + 1) * step, l + (double)(i + 1));
    fflush(stdout);
    cin >> res3;

    int xi = res3 / step;
    double x = (double)xi + l, y = (double)m - (res3 - (double)xi * step) * ((double)m / step) - (double)0.5;

    printf("! %.15LF %.15LF\n", x, y);
    fflush(stdout);
}
```

最后祝各位顺利AC。>w<

---

## 作者：周子衡 (赞：0)

考虑按下图方法选取区域。为了使红色部分构成一个多边形，需要适当在外部补充一些区域。

![](https://cdn.luogu.com.cn/upload/image_hosting/7sogvr1b.png)

注意到在这样的染色方法下，一个题中的 $1\times 1$ 的正方形与红色部分的公共面积与 $x$ 坐标无关，且随 $y$ 坐标增加而下降。这意味着我们可以通过查询的结果来确定 $y$ 坐标。（具体来说，可以通过解一个一元二次方程求得。）把整张图旋转 $90^\circ$，可以如法炮制解出 $x$ 坐标。这样就可以在两次询问内解决此题了。

---

