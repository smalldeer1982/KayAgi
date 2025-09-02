# Fear of the Dark

## 题目描述

Monocarp tries to get home from work. He is currently at the point $ O = (0, 0) $ of a two-dimensional plane; his house is at the point $ P = (P_x, P_y) $ .

Unfortunately, it is late in the evening, so it is very dark. Monocarp is afraid of the darkness. He would like to go home along a path illuminated by something.

Thankfully, there are two lanterns, located in the points $ A = (A_x, A_y) $ and $ B = (B_x, B_y) $ . You can choose any non-negative number $ w $ and set the power of both lanterns to $ w $ . If a lantern's power is set to $ w $ , it illuminates a circle of radius $ w $ centered at the lantern location (including the borders of the circle).

You have to choose the minimum non-negative value $ w $ for the power of the lanterns in such a way that there is a path from the point $ O $ to the point $ P $ which is completely illuminated. You may assume that the lanterns don't interfere with Monocarp's movement.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1886B/e2035d6f1a8a294e1d7b18148024db80f9680a4a.png) The picture for the first two test cases

## 样例 #1

### 输入

```
2
3 3
1 0
-1 6
3 3
-1 -1
4 3```

### 输出

```
3.6055512755
3.2015621187```

# 题解

## 作者：SDLTF_凌亭风 (赞：4)

简单题，注意分类讨论和精度问题即可。

无非就两种情况。一种情况是一个圆覆盖了两个点，另外一种情况就是需要两个圆有接触。

对于第一种情况，分类讨论到底以哪个点作为圆心半径最小。

对于第二种情况，分类讨论 $O,P$ 两点分别在哪个圆里。

此种情况下，我们的路线有两种走法。一种是 $O\rightarrow A(B)\rightarrow B(A) \rightarrow P$，另外一种是直接从 $O$ 走到 $P$。所以需要额外算一算圆心距再取最小值。

讲解在代码注释里。

```cpp
#include <bits/stdc++.h>
#define disAO sqrt((ax * ax) + (ay * ay))
#define disAP sqrt((ax - px) * (ax - px)+ (ay - py) * (ay - py))
#define disBO sqrt((bx * bx) + (by * by))
#define disBP sqrt((bx - px) * (bx - px)+ (by - py) * (by - py))
#define disAB sqrt((bx - ax) * (bx - ax)+ (by - ay) * (by - ay))
using namespace std;

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int T; cin >> T;
	for(long double px, py, ax, ay, bx, by, r1, r2, r3; T; -- T) {
		cin >> px >> py >> ax >> ay >> bx >> by;
		
		long double AO = disAO, BP = disBP, AP = disAP, BO = disBO, d = disAB / 2.0;
		// for case1: 一个圆覆盖所有
		r1 = min(max(AO, AP), max(BO, BP));
		
		// for case2: O 在 A，P 在 B, d 为 圆心距 
		r2 = max(max(AO, d), BP)
		
		// for case3: 和 case2 反过来
		r3 = max(max(BO, d), AP)
   
		cout << min(r1, min(r2, r3)) << '\n';
	}
}
```

---

## 作者：huanglihuan (赞：2)

### 题目大意和目的
题目给出三个坐标，分别为终点 $P$，两个圆心的 $A,B$ 的坐标。
现在，我们的起点被设置为在 $0,0$ 的地方，我们要去往终点 $P$，但是我们只能在两个圆的范围内进行行走，问，两个圆的半斤取值 $r$ 最小为多少？

### 算法思路
$笛卡尔坐标系思维计算 模拟$

1、 圆 $B$ 太远了，圆 $A$ 自身的范围就可以包裹住起点和终点 $P$。这时候取值为点 $A$ 距离起点和终点哪个比较远的取值 $r$ 就可以了。

2、圆 $A$ 太远了，圆B自身的范围就可以包裹住起点和终点 $P$。这时候取值为点 $B$ 距离起点和终点哪个比较远的取值 $r$ 就可以了。

3、两个圆刚好相切或者相交，同时包裹住了起点和终点，取值刚好相切即可。

4、两个圆相切或者相交，但是没有包裹住终点或者起点，这时候就无脑选择两个点当中距离较远的那个点，扩张半径直到触碰到为止。

### 代码示范
```cpp
#include<bits/stdc++.h>
using namespace std;
 
void solve(){
	double px,py,ax,ay,bx,by;
	cin >> px >> py >> ax >> ay >> bx >> by;
	double answer = 0 ;
	double get_end_r = min(sqrt(pow(px-ax,2) + pow(py-ay,2)) , sqrt(pow(px-bx,2) + pow(py-by,2))); // 取距离终点最近的圆心到达终点的取值r 
	double get_start_r = min(sqrt(pow(ax,2) + pow(ay,2)) , sqrt(pow(bx,2) + pow(by,2))); // 取距离起点最近的圆心到达的取值r 
	double touch_r =  sqrt(pow(bx-ax,2) + pow(by-ay,2)) / 2; // 相切的r取值 
	answer = max(get_end_r,max(get_start_r,touch_r));  // 题目的条件是同时包住起点和终点，假如说刚好到达终点或者起点的取值没有办法
//让圆相切那么就取相切的r取值，又或者相切的取值到达了，但是没有包住起点或者终点还是不满足题意，所以要取一个最大值。 
	double A_max = max(sqrt(pow(px-ax,2) + pow(py-ay,2)),sqrt(pow(ax,2) + pow(ay,2)));
	double B_max = max(sqrt(pow(px-bx,2) + pow(py-by,2)),sqrt(pow(bx,2) + pow(by,2)));
	printf("%.10lf\n",min(A_max,min(B_max,answer)));
}
 
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：xihegudiiakioi (赞：1)

这道题本来是学二分时老师给的作业，可是参考题解后决定用算术方法。

## 解题思路
使用勾股定理可以计算任意两点间的距离。这在题目中用于计算原点到灯笼、灯笼到家的距离。我们需要找到能够覆盖从原点到家的整个路径的最小半径。~~（废话）~~

半径 $r$ 为最小值的几种情况：

1. 直接路径：首先，我们考虑从原点到家的直线路径。这条路径必须被至少一个灯笼照亮，所以我们计算原点到家的直线与两个灯笼的距离，取最大值作为 $r$ 的一个可能值。这是因为如果 $r$ 小于这个距离，那么直线路径上就会存在未被照亮的部分。

1. 通过灯笼的路径：也可以选择先前往一个灯笼，再从灯笼前往家。这种情况下，我们需要考虑从原点到灯笼、从灯笼到家的两段路径。每段路径都需要被照亮，所以我们分别计算这两段路径与两个灯笼的距离，并取各自的最大值作为 $r$ 的另一个可能值。

1. 灯笼之间的路径：最后，我们还需要考虑一种特殊情况，即可能需要先前往一个灯笼，然后穿过两个灯笼之间的区域，再前往另一个灯笼，最后回到家。这种情况下，我们需要确保两个灯笼之间的路径也被照亮。因此，我们计算两个灯笼之间的距离的一半，作为 $r$ 的第三个可能值。这是因为当两个灯笼的照亮范围重叠时，它们可以共同照亮它们之间的区域。

最终，我们取这三种情况中计算出的 $r$ 的最小值作为答案。


## AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;  
typedef double db; //定义一个新的数据类型别名db，代表double类型  
  
int t;
  
struct pl {  //定义一个结构体pl来表示平面上的一个点，方便操作  
    int x, y; //点的x和y坐标  
    pl(int tx = 0, int ty = 0) { //构造函数，可以设置默认的x和y值为0  
        x = tx;  
        y = ty;  
    }  
    void read() { //读取x和y的值  
        scanf("%d%d", &x, &y);  
    }  
    friend pl operator-(const pl &a, const pl &b) { //重载减法运算符，用于计算两个点之间的差值  
        return pl(a.x - b.x, a.y - b.y);  
    }  
    double dist() { //计算该点到原点的距离  
        return sqrt(x * x + y * y);  
    }  
} p, a, b; //定义三个点p, a, b  
  
int main() {  
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {  
        p.read(); // 读取点的坐标  
        a.read(); 
        b.read(); 
        db dis_a = max((a - p).dist(), a.dist()); 
		// 计算点p到点a的距离和点a到原点的距离的最大值。  
        db dis_b = max((b - p).dist(), b.dist());  
        // 计算点p到点b的距离和点b到原点的距离最大值。 
        db ans = min(dis_a, dis_b);  
        db ans2 = (a - b).dist() / 2;  
        // 计算点a和点b之间距离的一半作为ans2的初始值 
		/*因为当这个圆恰好经过点a和点b时，
		它的半径至少应该是a和b之间距离的一半，
		这样才能保证两点都位于圆上或圆内 。*/ 
        db dis_p = min((a - p).dist(), (b - p).dist());  
        // 计算点p到点a和点b的距离中的最小值。  
        db dis_o = min(a.dist(), b.dist());  
        // 计算点a和点b到原点的距离中的最小值。  
        ans2 = max(ans2, max(dis_p, dis_o));  
        ans = min(ans, ans2);  
        printf("%.10lf\n", ans);
    }  
}
```

---

## 作者：MhxMa (赞：1)

## 解法
利用一个 distance 函数用于计算两点之间的欧几里德距离。

在主函数中，读取测试用例的数量，处理每个测试用例。  
对于每个测试用例，计算 $PA$、$PB$、$OA$ 和 $OB$ 的距离。  
使用条件语句来确定 $w$ 的最小值，最后将结果打印为精确到小数点后 $10$ 位的浮点数。

使用直观的方法来比较距离，并找到问题要求的 $w$ 的最小值。

## 代码
```
#include <bits/stdc++.h>
using namespace std;

long double distance(long double x1, long double y1, long double x2, long double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
	int t;
	cin >> t;

	while (t--) {
		long double px, py, ax, ay, bx, by;
		cin >> px >> py >> ax >> ay >> bx >> by;

		long double PA = distance(px, py, ax, ay);
		long double PB = distance(px, py, bx, by);
		long double OA = distance(0.0, 0.0, ax, ay);
		long double OB = distance(0.0, 0.0, bx, by);

		if (PA < PB && OA < OB)
			cout << fixed << setprecision(10) << max(OA, PA) << endl;
		else if (PA > PB && OA > OB)
			cout << fixed << setprecision(10) << max(OB, PB) << endl;
		else if (PA < PB && OA > OB)
			cout << fixed << setprecision(10) << min(min(max(OA, PA), max(OB, PB)), max(max(PA, OB), distance(ax, ay, bx, by) / 2.0)) << endl;
		else
			cout << fixed << setprecision(10) << min(min(max(OA, PA), max(OB, PB)), max(max(PB, OA), distance(ax, ay, bx, by) / 2.0)) << endl;
	}

	return 0;
}
```

---

## 作者：Wf_yjqd (赞：1)

比较水的 2B，但手速慢了。

------------

考虑共四种走法：

- 原点到 $a$，$a$ 到终点
- 原点到 $b$，$b$ 到终点
- 原点到 $a$，$a$ 到 $b$，$b$ 到终点
- 原点到 $b$，$b$ 到 $a$，$a$ 到终点

于是求出给点之间距离，取每种走法上需要半径的最大值，再将所有走法的答案取最小值即可。

注意 $a$ 和 $b$ 需要的半径是两点距离的一半。

------------

为啥要放代码呢？

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef double db;
db px,py,ax,ay,bx,by,dspa,dspb,dsab,dsa,dsb;
int T;
inline db dis(db x,db y,db xx,db yy){
    return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%lf%lf%lf%lf%lf%lf",&px,&py,&ax,&ay,&bx,&by);
        dspa=dis(px,py,ax,ay);
        dspb=dis(px,py,bx,by);
        dsab=dis(ax,ay,bx,by)/2.0;
        dsa=dis(0,0,ax,ay);
        dsb=dis(0,0,bx,by);
        printf("%lf\n",min(min(max(dsa,dspa),max(dsb,dspb)),min(max(max(dsa,dsab),dspb),max(max(dsb,dsab),dspa))));
    }
    return 0;
}
```


---

## 作者：liaoz123 (赞：1)

## 简要题意：
给定点 $P,A,B$ 和一个原点 $O$，求以 $A,B$ 为圆心画出的圆的最小的半径 $R$，使得 $O$ 可以经过圆的内部或边界到达 $P$。

## 做法
分两种情况讨论：

$\bullet$ 一个圆就把 $O,P$ 覆盖，此时考虑分别以 $A,B$ 为圆心的答案，取较小值。

$\bullet$ 两圆相交，各覆盖一个点，此时分别考虑 $O$ 在圆 $A$ 内，$P$ 在圆 $B$ 内，或 $O$ 在圆 $B$ 内，$P$ 在圆 $A$ 内的情况。

上述答案取较小值。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
double a,b,c,d,e,f;
int t;
double dis(double x,double y,double n,double m){
	return sqrt((x-n)*(x-n)+(y-m)*(y-m));
}
void work(){
	cin>>a>>b>>c>>d>>e>>f;
	double sa,sb,sc;
	sa=max(dis(a,b,c,d),dis(c,d,0,0));
	sb=max(dis(a,b,e,f),dis(e,f,0,0));
	sc=max(dis(c,d,e,f)/2.0,min(max(dis(e,f,a,b),dis(c,d,0,0)),max(dis(e,f,0,0),dis(c,d,a,b))));
	printf("%.8lf\n",min(sa,min(sb,sc)));
}
int main(){
	cin>>t;
	while(t--)work();
	return 0;
} 
```


---

## 作者：Jerrycyx (赞：0)

看到图第一眼以为是分类讨论，一看题面，原来不是求最短路，而且坐标确定，距离相同，那就好做了。

思考一下什么情况下有一条合法路径：**首先起点和终点都必须被灯光覆盖，其次覆盖起点和终点的灯光范围需要相交**。

注意，**覆盖起点和终点的灯可以是同一盏灯**。

某盏灯覆盖起点或终点所需 $w$ 为灯到它的距离，而使灯光范围接触所需 $w$ 为两灯距离的一半。

设 $\operatorname{dis}(x_a,y_a,x_b,y_b)=\sqrt{(x_a-x_b)^2+(y_a-y_b)^2}$ 表示 $A(x_a,y_a)$、$B(x_b,y_b)$ 两点间距离，两盏灯坐标分别为 $(lx_0,ly_0)$、$(lx_1,ly_1)$。令灯 $i$ 为覆盖起始点的灯，灯 $j$ 为覆盖终点的灯，那么答案就为：

$$
\min_{i \in \{0,1\},j \in \{0,1\}}
\max \left\{
\begin{aligned}
&\operatorname{dis}(0,0,lx_i,ly_i)\\
&\operatorname{dis}(px,py,lx_j,ly_j)\\
&\operatorname{dis}(lx_i,ly_i,lx_j,ly_j) \times \tfrac{1}{2}
\end{aligned}
\right.
$$

[AC 记录](https://codeforces.com/contest/1886/submission/292259192)

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

inline double dis(double xa,double ya,double xb,double yb)
{
	return sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb));
}

int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		double px,py,lx[2],ly[2];
		scanf("%lf%lf%lf%lf%lf%lf",&px,&py,&lx[0],&ly[0],&lx[1],&ly[1]);
		double ans=1e18;
		for(int i=0;i<=1;i++)
			for(int j=0;j<=1;j++)
			{
				double w=max({
					dis(0,0,lx[i],ly[i]),
					dis(px,py,lx[j],ly[j]),
					dis(lx[i],ly[i],lx[j],ly[j])/2.0
				});
				ans=min(ans,w);
			}
		printf("%.10lf\n",ans);
	}
	return 0;
}
```

---

## 作者：Super_Builder (赞：0)

考虑二分。

## 思路

我们把两盏灯分别命名为 $A$ 和 $B$。

如何**走回家**？

走回家有**四种走法**。

- 最开始在 $A$ 所照的区域内，家也在 $A$ 所照的区域内，这样就可以直接走到家。
- 最开始在 $A$ 所照的区域内，家在 $B$ 所照的区域内，先走到 $B$ 所照的区域内，再走回家。
- 最开始在 $B$ 所照的区域内，家也在 $B$ 所照的区域内，这样也可以直接走到家。
- 最开始在 $B$ 所照的区域内，家在 $A$ 所照的区域内，先走到 $A$ 所照的区域再回家。

这些走法是需要判断是否可行的，比如如果做开始不在 $A$ 所照的区域内，那么第一种和第二种走法都不行。

怎样**判断是否在此区域内或是否能走到另一个区域**？

- 判断在不在区域内看圆心和当前点的距离是否小于圆的半径。  
- 判断能不能走到另一个圆，即两个圆是否相切或相交，只需要判断两个圆心的距离是否小于它们的半径之和。

**知道前面这些后**，我们基本上就可已做出这题了。

可以采用二分答案，二分圆的半径，如果当前的半径符合要求，即可以回到家，则将当前半径是一个合法的答案，记录并缩小二分上界。否则增加二分下界。

符合要求的话，具体而言，就是看看能不能用上面四种走法回到家。

## AC CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
double px,py,ax,ay,bx,by;
double diss(int x,int y,int x2,int y2){
	return sqrt(1.0*(x-x2)*(x-x2)+1.0*(y-y2)*(y-y2));
}
inline bool check(double r){
	if(diss(0,0,ax,ay)<=r){
		if(diss(ax,ay,px,py)<=r)return true;
		if(diss(ax,ay,bx,by)<=2*r){
			if(diss(bx,by,px,py)<=r)return true;
		}
	}
	if(diss(0,0,bx,by)<=r){
		if(diss(bx,by,px,py)<=r)return true;
		if(diss(ax,ay,bx,by)<=2*r){
			if(diss(ax,ay,px,py)<=r)return true;
		}
	}
	return false;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		cin>>px>>py>>ax>>ay>>bx>>by;
		double l=0,r=1e7,ans;
		while(r-l>1e-10){
			double mid=(l+r)/2;
			if(check(mid)){
				r=mid;
				ans=mid;
			}
			else{
				l=mid;
			}
		}
		printf("%.10lf\n",ans);
	}
	return 0;
}
```

---

## 作者：U•ェ•*U (赞：0)

### [我的CSDN文章地址（转载请标明）](https://lsm2024.blog.csdn.net/article/details/134836865)
## 思路

这题可以**二分+check**，但是好像会被卡精度

其实，这题**分类讨论**就好了。

只经过一个圆；经过两个圆，需要两个圆相交。

这题具体实现的时候可以使用**结构体/类的思想**，把**一个圆想成一个类**，判断的时候不用写两遍了

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
double x1, y1, x2, y2, x3, y3;
bool c1(double x, double y, double dou, double x1, double y1) {
	return (x1 - x) * (x1 - x) + (y1 - y) * (y1 - y) < dou * dou;
}
bool c2(double x1, double y1, double x2, double y2, double dou) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) < (dou * 2) * (dou * 2);
}
bool check(double dou) {
	if (c1(x2, y2, dou, 0, 0) && c1(x2, y2, dou, x1, y1)) return true;
	if (c1(x3, y3, dou, 0, 0) && c1(x3, y3, dou, x1, y1)) return true;
	if (c2(x2, y2, x3, y3, dou)) {
		if (c1(x2, y2, dou, 0, 0) && c1(x3, y3, dou, x1, y1)) return true;
		if (c1(x3, y3, dou, 0, 0) && c1(x3, y2, dou, x1, y1)) return true;
	}
	return 0;
}
int main() {
	ios :: sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
		double l = 0, r = 5e3, ans = r, mid;
		while (abs(r - l) > 1e-9) {
			mid = (r + l) / 2;
			if (check(mid)) {
				ans = min(ans, mid);
				r = mid;
			} else l = mid;
		}
		printf("%.9lf\n", ans);
	}
	return 0;
}
```


---

## 作者：Dr_Octopus (赞：0)

### 思路 ：

**共分四种情况** ：

+ 原点到 $a$ 到终点
+ 原点到 $b$ 到终点
+ 原点到 $a$ 到 $b$ 到终点 
+ 原点到 $b$ 到 $a$ 到终点 

分别求出每种情况的距离再取最小值即可。

### CODE :

```cpp
#include<bits/stdc++.h>

using namespace std;

double xp, yp, xa, ya, xb, yb;
double dispa, dispb, disab;
double disa, disb;
int t;

double get_dist(double x, double y, double x2, double y2)
{
    return (double)sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
}

signed main()
{
    cin >> t;
    while (t -- )
	{
        cin >> xp >> yp >> xa >> ya >> xb >> yb;
        
        dispa = get_dist(xp, yp, xa, ya);
        dispb = get_dist(xp, yp, xb, yb);
        disab = get_dist(xa, ya, xb, yb) / 2.0;
        disa = get_dist(0, 0, xa, ya);
        disb = get_dist(0, 0, xb, yb);
        
        double res = 1e9;
        res = min(res, min(max(max(disa, disab), dispb), max(max(disb, disab), dispa)));
		res = min(res, min(max(disa, dispa), max(disb, dispb)));
		
		printf("%.10lf\n", res);
    }
    return 0;
}
```
------------

---

## 作者：Leeb (赞：0)

### 题目大意

给定三个点 $P$，$A$，$B$，求出最小的 $r$ 使得从 $O(0,0)$ 到达 $P$ 所通过的路程完全被以 $A$、$B$ 为圆心，$r$ 为半径的两个圆所覆盖（包括圆的边界）。

### 解题思路

很容易想到两种情况：

- $O$、$P$ 被同一个园覆盖
  
- $O$、$P$ 分别被两个圆覆盖
  

在以上两种情况中的答案取最小值即可。下面将给出参考代码。

### 参考代码

```cpp
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// Code Author : Leeb
// #include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100005
#define inf 0x3f3f3f3f
#define elif else if
#define int long long
#define ub upper_bound
#define lb lower_bound
#define ls (x << 1)
#define rs (x << 1 | 1)
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
inline int in();
struct Point {
    double x, y;
    inline void read() {
        x = in(), y = in();
    }
} P, A, B, O;
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        {if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;   
    return a;
}
inline void print(int x) {
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
inline void output(int x, char ch) {
    print(x);
    putchar(ch);
}
inline void init() {
    O = {0, 0};
    P.read(), A.read(), B.read();
}
inline double dis(Point A, Point B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}
inline void work() {
    double dis1 = max(dis(O, A), dis(A, P));
    double dis2 = max(dis(O, B), dis(B, P));
    double dis3 = max(dis(A, B) / 2.0, min(max(dis(O, A), dis(B, P)), max(dis(O, B), dis(A, P))));
    double ans = min(dis1, min(dis2, dis3));
    printf("%.9lf\n", ans);
}
signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int t = in();
    while (t--) {
        init();
        work();
    }
    return 0;
}
```

---

## 作者：_空白_ (赞：0)

本题我采用了分类讨论的方法，分出的种类如下：

1. 让一个灯笼同时包含起点和终点。

2. 让两个灯笼的照亮范围相切（此时两个灯笼的照亮范围必须已经包含了起点和终点）。

3. 让两个灯笼各照亮一个点（此时照亮范围必须相交）。

不难发现，在 $2$ 中的条件无法满足时，$3$ 一定可以满足，因为 $2$ 要求满足灯笼间距离的一半 **大于等于** 每个灯笼到离较近一点的距离，而 $3$ 要求满足灯笼间距离的一半 **小于等于** 离较近一点的距离（当然取到等于时两种情况相当于一种情况）。

那么我们只要算出两个灯笼间的距离、两个灯笼到起点和终点的距离即可。

最后计算和输出时注意精度。（$\le 10^{-6}$）

_AC code_

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int ans=0,fh=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){ans=ans*10+ch-'0';ch=getchar();}
	return ans*fh;
}
 
double Max(double a,double b)
{
	if(a>b)
		return a;
	return b;
}
 
double Min(double a,double b)
{
	if(a<b)
		return a;
	return b;
}
 
double dis(int ax,int ay,int bx,int by)
{
	return sqrt(abs(ax-bx)*abs(ax-bx)+abs(ay-by)*abs(ay-by));
}
 
int main()
{
	int T=read();
	while(T--)
	{
		double ans=0x7fff;
		double px,py,ax,ay,bx,by;
		cin>>px>>py>>ax>>ay>>bx>>by;
		double da=dis(ax,ay,px,py),dao=dis(ax,ay,0,0),db=dis(bx,by,px,py),dbo=dis(bx,by,0,0);//两个灯笼到终点和起点（原点）的距离
		double di=dis(ax,ay,bx,by)/2;//两个灯笼的间距
		ans=Min(Max(da,dao),Max(db,dbo));
		if((di>da&&di>dbo)||(di>db&&di>dao))
			ans=Min(ans,di);
		else
		{
			ans=Min(ans,Min(Max(da,dbo),Max(db,dao)));
		}
		cout<<setprecision(10)<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

我们可以使用二分和并查集算法。

设起点 $O$ 为 $1$ 号点，终点 $P$ 为 $2$ 号点，两盏灯分别为 $3$ 号点和 $4$ 号点。

接下来，二分枚举每个点是否可以连通。当两个点都是灯时，直接连通标准为距离大于等于两倍灯光；当两个点都不是灯时，直接连通就要求两个点重合；当两个点一个是灯一个不是时，直接连通标准为距离大于等于一倍灯光。

### 二、代码

```cpp
// Author: cyrxdzj
// Problem: Fear of the Dark
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1886B
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<cstdio>
#include<cmath>
using namespace std;
//#define debug
int t;
long double p[5][2];
int fa[5];
long double get_dis(int x,int y)
{
    return sqrt((p[x][0]-p[y][0])*(p[x][0]-p[y][0])+(p[x][1]-p[y][1])*(p[x][1]-p[y][1]));
}
int find_fa(int x)//并查集
{
    if(x==fa[x])
    {
        return x;
    }
    return fa[x]=find_fa(fa[x]);
}
void reset_fa()//重置
{
    for(int i=1;i<=4;i++)
    {
        fa[i]=i;
    }
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        for(int i=2;i<=4;i++)
        {
            long long a,b;
            scanf("%lld%lld",&a,&b);//话说scanf允许输入负小数么？我记得是不能的
            p[i][0]=a;
            p[i][1]=b;
        }
        long double ans=1e7;
        long double left=0,right=1e7;//二分板子
        while(right-left>1e-7)
        {
            long double mid=(left+right)/2;
            reset_fa();
            for(int i=1;i<=4;i++)
            {
                for(int j=i+1;j<=4;j++)//枚举
                {
                    if(get_dis(i,j)<=((i+j==3)?0:((i+j==7)?(2*mid):mid)))//判断是否符合连通标准
                    {
                        #ifdef debug
                        printf("i %d j %d dis %lf\n",i,j,get_dis(i,j));
                        #endif
                        fa[find_fa(i)]=find_fa(j);
                    }
                }
            }
            if(find_fa(1)==find_fa(2))
            {
                ans=mid;
                right=mid;
            }
            else
            {
                left=mid;
            }
        }
        printf("%.8Lf\n",ans);
    }
    return 0;
}
```

---

