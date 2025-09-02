# Nature Reserve

## 题目描述

There is a forest that we model as a plane and live $ n $ rare animals. Animal number $ i $ has its lair in the point $ (x_{i}, y_{i}) $ . In order to protect them, a decision to build a nature reserve has been made.

The reserve must have a form of a circle containing all lairs. There is also a straight river flowing through the forest. All animals drink from this river, therefore it must have at least one common point with the reserve. On the other hand, ships constantly sail along the river, so the reserve must not have more than one common point with the river.

For convenience, scientists have made a transformation of coordinates so that the river is defined by $ y = 0 $ . Check whether it is possible to build a reserve, and if possible, find the minimum possible radius of such a reserve.

## 说明/提示

In the first sample it is optimal to build the reserve with the radius equal to $ 0.5 $ and the center in $ (0,\ 0.5) $ .

In the second sample it is impossible to build a reserve.

In the third sample it is optimal to build the reserve with the radius equal to $ \frac{5}{8} $ and the center in $ (\frac{1}{2},\ \frac{5}{8}) $ .

## 样例 #1

### 输入

```
1
0 1
```

### 输出

```
0.5```

## 样例 #2

### 输入

```
3
0 1
0 2
0 -3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
2
0 1
1 1
```

### 输出

```
0.625```

# 题解

## 作者：Grisses (赞：4)

[题面](https://www.luogu.com.cn/problem/CF1059D)

求一个能覆盖所有点的与 $y$ 轴相切的最小的圆。

对于所有的点，如果它们同时出现在 $y$ 轴的上下，输出 $-1$。

然后，我们二分枚举圆的半径。

如果半径为 $r$，

![](https://cdn.luogu.com.cn/upload/image_hosting/xjeu00ed.png)

$AD=AE=r$，圆 $p,c,k$ 的半径也为 $r$。

$DJ=JE=\sqrt{r\times r-X_A\times X_A}$。

我们只需枚举每一个点在半径为 $r$  时的 $D,E$ 坐标，到最后如果还满足 $\max\limits_{i=1}^nX_D\le \min\limits_{i=1}^nX_E$ 就说明半径为 $r$ 是成立的。

代码：
```cpp
  #include<bits/stdc++.h>
  #define db long double
  using namespace std;
  int n;
  struct node{
      int x,y;
  }a[100005];//储存点的坐标
  bool ch(db x){
      db maxl=-1e15,minr=1e15;//初始化左右端点
      for(int i=1;i<=n;i++){
          db c,d;
          if(x*x<(a[i].y-x)*(a[i].y-x))return 0;//无法与y轴相切
          c=a[i].x-sqrt(x*x-(a[i].y-x)*(a[i].y-x));
          d=a[i].x+sqrt(x*x-(a[i].y-x)*(a[i].y-x));
          maxl=max(maxl,c);
          minr=min(minr,d);//更新
      }
      return maxl<=minr;
  }
  int main()
  {
      scanf("%d",&n);
      bool f1,f2;
      f1=f2=0;
      for(int i=1;i<=n;i++){
          scanf("%d%d",&a[i].x,&a[i].y);
          if(a[i].y>0)f1=1;
          if(a[i].y<0)f2=1;
          a[i].y=abs(a[i].y);//取绝对值方便处理
      }
      if(f1&&f2){//y轴上下都有点
          printf("-1");
          return 0;
      }
      int T=1000;//防止死循环（血与泪的教训）
      db l=0,r=1e14+10,mid;
      while(T--){
          mid=(l+r)/2;
          if(ch(mid))r=mid;
          else l=mid;//二分
      }
      printf("%.6Lf",r);
      return 0;
  }
```

---

## 作者：那个男人 (赞：4)

题意是求解与x轴相切且覆盖所有点半径最小的圆
求解圆心与每个点距离可以这样
```cpp
y=md;x>=md
dis=md*md-(md-y[i])*(md-y[i])=2*md*y[i]-y[i]*y[i]=（2*md-y[i]）*y[i]
```
这题主要是要注意精度
我看到有一篇题解就是没有注意精度，连样例都过不了，~~为什么能过审~~
在double类型的计算中尽量避免多次乘法，能用分配率结合律就用。
代码如下
```cpp
#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1e5+7;
int n,i,x[N],y[N];
bool check(double md){
    double L=-1e18,R=1e18;
    double dis;
    for(i=1;i<=n;i++){
        if(2*md<y[i])return false;
        dis=sqrt((2*md-y[i])*y[i]);
        L=max(L,x[i]-dis);R=min(R,x[i]+dis);
    }
    return L<R;
}

double l=0,r=1e14+10,mid,ans;
bool fl1,fl2;
int main(){
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d%d",&x[i],&y[i]);
        if(y[i]>0)fl1=true;
        if(y[i]<0)fl2=true;
    }
    if(fl1&&fl2){
        printf("-1");
        return 0; 
    }
    if(fl2){
        for(i=1;i<=n;i++)y[i]=-y[i];
    }
    int ti=500;
    while(ti--){
        mid=(l+r)/2;
        if(check(mid))ans=mid,r=mid;
        else l=mid;
    }
    printf("%.6lf",ans);
}
/*
y=md;x>=md
dis=md*md-(md-y[i])*(md-y[i])=2*md*y[i]-y[i]*y[i]
*/
```

---

## 作者：紊莫 (赞：3)

## 简洁题意

有 $N$ 个点，求与 $y=0$ 相切的，包含这 $N$ 个点的最小圆的半径。

## 思路
首先 $r$ 显然满足单调性，于是我们可以二分 $r$，然后考虑怎么计算当前的 $r$ 满不满足要求，一个极度暴力的想法是去枚举圆心的位置，然后判断，考虑一下这个位置满足什么性质，显然极值只可能在中间取到，所以这是一个单峰函数，考虑三分。  

当你写完后，发现挂的很惨，怎么回事呢？详见我发的[讨论帖](https://www.luogu.com.cn/discuss/763750)。

所以我们只能另辟蹊径来判断答案是否正确，我们不妨看看，对于一个点，能覆盖到它的圆心的左右范围是多少，把这些集合取个并集，若不为空集，证明有解。为什么会这么想呢》因为我们一个是不必知道圆心的具体位置，第二个是圆心是未知的，直接求不方便，但是已知的点求起来是方便的。

[参考代码。](https://codeforces.com/contest/1059/submission/243070830)

---

## 作者：Querainy (赞：3)

看到这个题就想起随机增量，然后题解区也有人说可以随机增量，然后就学了一下随机增量，自己胡了一个（

geogebra 画一画，发现两个圆上的点和一条切线可以确定两个圆(而不需要三个点确定一个圆)，这两个圆可以硬解二次方程解出来，具体可以自己手推一下或者见代码。所以爆力做法就是枚举两个点然后求出所有 $O(n^2)$ 个圆并爆力 check。

为了随机增量，我们大概并不能拿两个圆都尝试一遍(，然而也可能可以?没有尝试)。为了把它减少到一个圆，注意到这个圆可以在 $x$ 轴上平移而仍与 $x$ 轴相切，于是如果这两个圆上的点在圆心的同一侧，把圆向那一侧平移则这两个点都不再在圆上，于是我们知道即使这个圆是答案，也不是由这两个点确定的。

任意一个点和 $x$ 轴可以确定一个圆。geogebra 画一画，可以发现两个点确定的两个圆中有最多一个满足圆心的横坐标在这两点之间，并且如果没有这样的圆，则其中一个点必然在另一个点确定的圆中，取这个圆作为新的答案即可。复杂度应该是线性的。

具体细节请见代码。其中 `get_c` 实现了求两个点和 $x$ 轴确定的圆。

```cpp
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<random>
using std::shuffle;

const long double eps=1e-12;

struct P{ double x,y; }a[100002];
struct C{ P o; long double r2; };

#define sq(x) ((x)*(x))
inline long double dist2(P a,P b){ return sq(a.x-b.x)+sq(a.y-b.y); }

inline long double min(long double x,long double y){ return x<y?x:y; }
inline long double max(long double x,long double y){ return x>y?x:y; }

inline C get_c(P p,P q)
{
	long double a=p.y/2-q.y/2,b=p.x*q.y-q.x*p.y,c=(sq(q.x)+sq(q.y))*p.y/2-(sq(p.x)+sq(p.y))*q.y/2;
	long double d=sq(b)-4*a*c;
	P o;
	if(abs(a)<eps) return o={(p.x+q.x)/2,sq((p.x+q.x)/2)/(2*p.y)-p.x/p.y*(p.x+q.x)/2+(sq(p.x)+sq(p.y))/(2*p.y)},(C){o,dist2(p,o)};
	long double t=sqrt(d),x1=(-b+t)/(2*a),x2=(-b-t)/(2*a);
	if(min(p.x,q.x)-eps<x1&&x1<max(p.x,q.x)+eps) return o={x1,sq(x1)/(2*p.y)-p.x/p.y*x1+(sq(p.x)+sq(p.y))/(2*p.y)},(C){o,dist2(p,o)};
	if(min(p.x,q.x)-eps<x2&&x2<max(p.x,q.x)+eps) return o={x2,sq(x2)/(2*p.y)-p.x/p.y*x2+(sq(p.x)+sq(p.y))/(2*p.y)},(C){o,dist2(p,o)};
}

int n;

int main()
{
	scanf("%d",&n);
	bool flag1=0,flag2=0;
	for(int i=1;i<=n;i++) scanf("%lf%lf",&a[i].x,&a[i].y),flag1|=(a[i].y>0),flag2|=(a[i].y<0);
	if(flag1&&flag2){ printf("-1");return 0; }
	std::mt19937 _r(std::random_device{}());
	shuffle(a+1,a+n+1,_r);
	C c={{0,0},0};
	for(int i=1;i<=n;i++)
		if(dist2(c.o,a[i])>c.r2+eps)
		{
			c={{a[i].x,a[i].y/2},sq(a[i].y/2)};
			for(int j=1;j<i;j++)
				if(dist2(c.o,a[j])>c.r2+eps)
					if(dist2({a[j].x,a[j].y/2},a[i])<sq(a[j].y/2)) c={{a[j].x,a[j].y/2},sq(a[j].y/2)};
					else c=get_c(a[i],a[j]);
		}
	printf("%.10lf\n",(double)sqrt(c.r2));
	return 0;
}
```

---

## 作者：piuke (赞：3)

看了一下题目,瞬间MMP(~~话说构造是什么鬼~~)

先说一下正解:三分(虽然二分也能过,而且某些OJ的三分还比二分慢)  
反正我是看不懂,只好送上[大佬题解链接](https://blog.csdn.net/qq_37555704/article/details/82949337
)

如果你看到了这里,感谢你对本蒟蒻的支持(话说二分还是太蒟了)

```
首先,我们要把部分分骗到。
对于如果x轴上下都有点的话,直接输出-1 +10
第一组数据可以用另外一种简单二分做… +10
对于第二组数据,取x值最小的和x值最大的,然后由于y值确定,勾股定理即可 +10
你就有30分了
我们发现,对于任意圆半径R，都有y[i]<=2*R
然后我们不妨让这个圆只包含一个点会怎么得到什么
```


![](https://cdn.luogu.com.cn/upload/pic/44140.png)
```
我们可以发现AB=CD=EF=R-yi
圆心的横坐标必须在在HI上,我们想让圆尽量往左走,或尽量往右走
那么BG=sqrt(R^2-(R-yi)^2)(但这样写有(莫名其妙的)精度问题,需要变形,先忽略)
令BG=len，圆心横坐标范围就是
xi-len<=X<=xi+len,
那么对于所有坐标而言,就是取交集的问题.
一开始让圆心范围为（-1e7,1e7）即为(l,r)
然后对于每个点计算完后l不断取max,r不断取min,最后只需l<r即可
```

于是就有了这样一个check

``` cpp
inline bool check(double mid){
    double L=-1e7,R=1e7;
    for(int i=1;i<=n;i++)
    {
        if(2*mid<y[i]) return false;
        double len=sqrt(mid*mid-(mid-y[i])*(mid-y[i]));
        L=max(L,x[i]-len),R=min(R,x[i]+len);
    }
    return L<R;
}
```

所以我们二分半径R，带入检验即可  
R范围(0,INF),INF这里可以取1e17

接下来讲一下精度问题

```
1: 输出需要6位小数,所以需要 while(r-l<1e-6) 
2: sqrt(R^2-(R-yi)^2)=sqrt(mid-(mid-y[i])*sqrt(mid+(mid-y[i])))=sqrt(y[i])*sqrt(mid*2-y[i])
```

综上,代码如下(自动和谐注释)

``` cpp
#include<set>
#include<map>
#include<stack>
#include<cmath>
#include<queue>
#include<deque>
#include<cstdio>
#include<bitset>
#include<vector>
#include<climits>
#include<cstring>
#include<iostream>
#include<algorithm>
using std::max;
using std::min;
#define reg register
const int M=1e5+1;
inline long long read() {
    long long x=0;char c=getchar(),f=1;
    while(c<'0'||'9'<c) { if(c=='-')f=-1; c=getchar(); }
    while('0'<=c&&c<='9') x=(x<<3)+(x<<1)+c-'0',c=getchar();
    return f*x;
}
inline void write(long long a) {
    if(a<0) a=(~a)+1;
    if(a/10) write(a/10);
    putchar(a%10+48);
}
int n=read();
double x[M],y[M];
inline bool check(double mid) {
    double L=-1e7,R=1e7;
    for(int i=1;i<=n;i++) {
        if(2*mid<y[i]) return false;
        double len=sqrt(mid-(mid-y[i]))*sqrt(mid+(mid-y[i]));
        L=max(L,x[i]-len),R=min(R,x[i]+len);
    }
    return L<R;
}
bool f,f1;
double l=0,r=1e17,ans;
int main() {
    for(reg int i=1;i<=n;i++) {
        x[i]=read(),y[i]=read();
        if(y[i]<0) {
            y[i]=-y[i];
            f=1;
        }
        else f1=1;
    }
    if(f&&f1) return puts("-1");
    while(r-l>1e-6) {
        double mid=(l+r)/2;
        if(check(mid)) r=ans=mid;
        else l=mid;
    }
    printf("%.8lf",ans);
}
```


---

## 作者：LXcjh4998 (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1059D)
# 题意
在坐标系中有 $n$（$1\le n\le 10^5$）个点，其中第 $i$ 个点的坐标为 $(x_i,y_i)$（$-10^7\le x_i,y_i\le 10^7,y_i\ne 0$）。

求包含这 $n$ 个点，且与 $x$ 轴相切的圆的最小半径 $r$（与答案误差不超过 $10^{-6}$ 即可，若无解则输出 $-1$）。
# 思路
首先，由于这个圆与 $x$ 轴相切，所以它所包含的点一定是全在 $x$ 轴上方或全在 $x$ 轴下方。

因此我们可以先遍历这 $n$ 个点，用两个布尔变量记录是否有在 $x$ 轴上方或在 $x$ 轴下方的点。若两个变量同时为真，则输出 $-1$。

如果 $n$ 个点全在 $x$ 轴下方，我们可以将它们关于 $x$ 轴做个轴对称，转移到 $x$ 轴上方，这样就只需要处理在 $x$ 轴上方的情形。

然后我们可以对 $r$ 进行二分答案，此时圆心的 $y$ 坐标我们就知道了（$y=r$），但 $x$ 坐标仍然不知道，该怎么办呢？

其实并没有关系，我们可以对于每个点都计算下当圆包含它时，圆心的 $x$ 坐标的取值范围，然后判断这 $n$ 个区间是否有交集即可。若有，则该 $r$ 可行，否则不可行。

例如，对于第 $3$ 组样例，模拟情况如下：
- $r=1$  
![](https://cdn.luogu.com.cn/upload/image_hosting/cgz3k87i.png)

圆心 $x$ 坐标的取值范围为 $[0,1]$。
- $r=0.5$  
![](https://cdn.luogu.com.cn/upload/image_hosting/ppiodu2n.png)

圆心 $x$ 坐标的取值范围为空集。
- $r=0.75$  
![](https://cdn.luogu.com.cn/upload/image_hosting/zt9ofehk.png)

圆心 $x$ 坐标的取值范围为 $[1-\frac{\sqrt 2}{2},\frac{\sqrt 2}{2}]$，约为 $[0.293,0.707]$。
- $r=0.625$  
![](https://cdn.luogu.com.cn/upload/image_hosting/7src6r1q.png)

圆心 $x$ 坐标的取值范围为 $\{0.625\}$。

因此输出结果为：
```
0.625
```
# 程序
```
#include<cstdlib>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cstdio>
#include<iostream>
#include<vector>
#include<map>
#include<cmath>
#include<iomanip>
#include<stack>
using namespace std;
int T=1;
#define ll long long
#define ull unsigned long long
#define LL 2e18
#define INT 1e9
#define INF 0x3f3f3f3f
#define mod int(1)
#define MAX int(1e5)
//#define DEBUG
//#define use_cin
//#define more_text

struct point{//x为点的横坐标，y为点的纵坐标 
	double x,y;
};
int n;point arr[MAX];//n为点的个数，arr[]存点的坐标 
double l,r,mid,ans;//用于二分答案 
bool flag1,flag2;//用于判断点与x轴的相对位置（在上方还是在下方）

bool check(double num){//检查函数 ，num为圆的半径 
	double le=-1e18,ri=1e18;//le记录当前区间左端点的最大值，ri记录当前区间右端点的最小值 
	double dis;
	
	for(int i=0;i<n;++i){
		if(2*num<arr[i].y)return false;//如果圆中y坐标最大的点仍低于该点，则返回false 
		dis=sqrt((2*num-arr[i].y)*arr[i].y);//计算区间端点到圆心的距离 
		le=max(le,arr[i].x-dis);//左端点 
		ri=min(ri,arr[i].x+dis);//右端点 
	}
	
	return le<ri;//返回 
}
void solve(int step){
	scanf("%d",&n);//输入 
	for(int i=0;i<n;++i)scanf("%lf%lf",&arr[i].x,&arr[i].y);
	
	flag1=flag2=false;//判断点与x轴的相对位置 
	for(int i=0;i<n;++i){
		if(arr[i].y>0)flag1=true;
		if(arr[i].y<0)flag2=true;
	}
	if(flag1&&flag2){//若存在两个点分居x轴的两侧，则输出-1 
		printf("-1");
		return;
	}
	
	if(flag2)for(int i=0;i<n;++i)arr[i].y=-arr[i].y;//如果在x轴下方，则改为在x轴上方 
	
	l=0,r=1e14+10;//二分答案 
	int t=1000;
	while(t--){
		mid=(l+r)/2;
		if(check(mid))ans=mid,r=mid;
		else l=mid;
	}
	
	printf("%.6lf",ans);//输出 
}
int main(){//模板，不用在意
	#ifdef DEBUG
	freopen("test.in","r",stdin);freopen("test.out","w",stdout);
	#endif
	#ifdef more_text
	#ifdef use_cin
	cin>>T;
	#else
	scanf("%d",&T);
	#endif
	#endif
	for(int i=0;i<T;++i)solve(i);
	#ifdef DEBUG
	fclose(stdin);fclose(stdout);
	#endif
	return 0;
}
/*
Input:

*/
```

---

## 作者：Mihari (赞：2)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF1059D)

# 题解

一道十分巧妙的二分题 ~~然而精度要求较高~~

首先考虑无解情况——有某两个点在 $x$ 轴的上下方，此时输出 `-1`

否则，考虑二分这个圆的半径 $r$，那么这个圆心所在的位置一定是一条直线 $y=r$（此处我们将所有的点都转移到 $x$ 轴上方，故不考虑正负号问题），然后，根据 $r$ 和所有点的位置，我们得以用勾股定理求得，要包含点 $(x_i,y_i)$ 的合法圆心的 $x$ 坐标一定在 $[x_i-\sqrt{r^2-(y_i-r)^2},x_i+\sqrt{r^2-(y_i-r)^2}]$，然后我们将所有的区间取并集，如果最后的集合为空，说明 $r$ 过小，不为空则继续往小二分。

# 代码

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
using namespace std;

const double eps=1e-8;
const int MAXN=1e5;

struct node{double x,y;}p[MAXN+5];

int n,pos;

double L,R;

template<class T>const T fab(const T a){return a<0?-a:a;}

inline void Init(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
    	scanf("%lf %lf",&p[i].x,&p[i].y);
        if((p[i].y<0 && pos==1) || (p[i].y>0 && pos==-1)){
            puts("-1");
            exit(0);
        }else pos=(p[i].y<0)?-1:1,p[i].y=fab(p[i].y);
    }
}

inline bool Check(const double x){
	double l=-1e18,r=1e18,len;
	for(int i=1;i<=n;++i){
		if(p[i].y>2*x)return false;
		len=sqrt(p[i].y)*sqrt(2*x-p[i].y);
		l=max(l,p[i].x-len);
		r=min(r,p[i].x+len);
	}return l<r;
}

inline void Bisearch(){
	double mid,ans;
	R=1e18;
	for(int times=1;times<=1000;++times){
//		printf("Now L == %f, R == %f\n",L,R);
		mid=(L+R)/2;
		if(Check(mid))ans=R=mid;
		else L=mid;
	}
	printf("%f\n",ans);
}

signed main(){
    Init();
    Bisearch();
    return 0;
}
/*
2
-10000000 1
10000000 1
*/
```



---

## 作者：mango2011 (赞：1)

有趣的二分题。

显然我们可以二分半径 $r$，考虑如何检查合法性。接下来考虑圆心 $O$ 可能的位置 $(x_0,r)$。要满足：$\sqrt{(x_i-x_0)^2+(y_i-r)^2}\le r$。

两边平方，$(x_i-x_0)^2+(y_i-r)^2\le r^2$。整理成关于 $x_0$ 的式子：${x_0}^2-(2x_i)x_0+({x_i}^2+{y_i}^2-2y_i r)\le 0$。令 $f_i(x)={x_0}^2-(2x_i)x_0+({x_i}^2+{y_i}^2-2y_i r)$，根据二次函数的增减性发现使得 $f_i(x)\le 0$ 的值要么不存在，要么构成一段连续的区间 $[l_i,r_i]$（求出零点即可）。当所有 $f_i(x)$ 都存在零点且 $[l_1,r_1]\cap [l_2,r_2]\cap [l_3,r_3]\cap \dots \cap [l_n,r_n]\not =\empty$ 时满足条件。于是我们就可以确定接下来如何选择 $l,r$。

由于是实数二分，所以我们可以考虑直接二分 $100$ 次，总复杂度 $O(Bn)$，其中 $B$ 为二分次数，取 $100$。

---

## 作者：bztMinamoto (赞：1)

二分半径右端点开小了结果交了二十几次都没A……mmp……

考虑一下，显然这个半径是可以二分的

再考虑一下，如果所有点都在y轴同一侧就有解，否则肯定无解

然后现在只要考虑在y轴同一侧时某一个半径是否能够包含所有点即可

因为得和y轴相切，所以半径确定时，圆心的y坐标是确定的

然后我们考虑对于每一个点，圆心的x坐标必须处在什么范围内

设这个点坐标为（x,y），圆半径为r，如果y>2*r显然不行

然后用勾股定理算一下两点之间的x坐标最多相差多少，那么就可以知道圆心的x坐标在什么范围内了

然后所有的范围并起来，如果是空集不可行，否则可行

然后注意判断x坐标相差多少时候的写法……代码里写了……
```
//minamoto
#include<bits/stdc++.h>
using namespace std;
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
const int N=2e5+5;
int n,flag1=0,flag2=0;double l=0,r=1e18,ans=0,mx,x[N],y[N];
bool check(double mid){
	double L=-1e18,R=1e18;
	for(int i=1;i<=n;++i){
		if(2*mid<y[i]) return false;
		double len=sqrt(mid-(mid-y[i]))*sqrt(mid+(mid-y[i]));
		//这里判断往左右能延伸多少时要这样写
		//据说不这样写会导致严重的精度误差
		//所以要先开方再相乘 
		L=max(L,x[i]-len),R=min(R,x[i]+len);
	}
	return L<R;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>x[i]>>y[i];
		if(y[i]>0) flag1=1;
		if(y[i]<0) flag2=1;
	}
	if(flag1&&flag2) return puts("-1"),0;
	if(flag2){
		for(int i=1;i<=n;++i) y[i]=-y[i];
	}
	int times=500;
	while(times--){
		double mid=(l+r)/2;
		if(check(mid)) ans=mid,r=mid;
		else l=mid;
	}
	printf("%.10lf\n",ans);
	return 0;
}
```

---

## 作者：Walrus (赞：0)

# CF1059D
我这里简单补充一下。

## 题意
在一个平面内有 $n$ 个点，求一个包含所有点且与 $x$ 轴**有且仅有一个公共点**的最小圆。

- 有两个交点代表 $x$ 轴为此圆的**割线**。
- 有且仅有一个交点代表 $x$ 轴为此圆的**切线**。
- 没有交点代表 $x$ 轴与此圆**相离**。

## 做法

先考虑无解的情况，想到与 $x$ 轴相切的圆有什么性质。相信都能想到，此圆要么全在 $x$ 轴上方，要么全在 $x$ 轴下方。就像这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/6m7kv7b4.png)

所以，当我们发现有两个点分别位于 $x$ 轴上方与下方时，应当输出 `-1`。

- 有且仅当所有点全部位于 $x$ 轴上方或下方时才有解。

显然，越大的圆所能包含的范围就会变多，所以答案具有单调性，考虑二分半径 $r$。我们这里统一将所有点取绝对值，便于计算。

因为圆心到所有点的距离都为 $r$，所以此圆到与 $x$ 轴相交的那点的**距离**也应该是 $r$，注意说的是**距离**。所以我们可以很容易地知道圆心一定在**直线 $y=r$** 上。

最后枚举每一个点，若其到 $x$ 轴的距离大于了圆的半径的**两倍**，也就是**直径**，那么此答案显然不成立。然后我们去寻找**能够包含该点的圆心坐标范围**，我们可以通过勾股定理求得，最后如 [Mihari](https://www.luogu.com.cn/user/125355) 的文章所说（2020 年前的我引不了），我们对这些范围求**交集**，若最后集合为空，则此半径不合法。

![](https://cdn.luogu.com.cn/upload/image_hosting/1jy4xs5x.png)

图中，$OB=Y_A-r$，因为我们要的是能包括该点的临界范围，所以这点应该在**圆上**，所以 **$OA$ 实际上应该为 $r$**。于是我们就可以通过勾股定理求出 $AB$ 的长度。这里给出左边的情况，右边同理，减法变加法即可。 

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 5;
int n, tag1, tag2;
struct node {
	long double x, y;
#define x(p) a[p].x
#define y(p) a[p].y
} a[N];

bool check(double x) {
	long double l = -1e14, r = 1e14;
	for(int i = 1; i <= n; ++i) {
		if(2 * x < y(i)) return false;
		l = max(l, x(i) - sqrt((2 * x - y(i)) * y(i)));
		r = min(r, x(i) + sqrt((2 * x - y(i)) * y(i)));
	}
	return l <= r;
}
signed main() {
//	ios::sync_with_stdio(0);
//	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> x(i) >> y(i), tag1 += (y(i) > 0), tag2 += (y(i) < 0), y(i) = abs(y(i));

	if(tag1 && tag2)
		return cout << -1, 0;

	long double l = 0, r = 1e14 + 10;
	int T = 500;
	while(T--) {
		long double mid = (l + r) / 2.0;
		if(check(mid)) r = mid;
		else l = mid;
	}
	printf("%.6Lf", r);
	return 0;
}
```

最后补充一点，因范围较大且为浮点类型，我们需要控制二分的次数，通过测试，当 $T=500$ 时就已经可以通过本题了。


---

## 作者：Cure_Wing (赞：0)

[CF1059D Nature Reserve](https://www.luogu.com.cn/problem/CF1059D)

### 思路

因为圆不能穿过直线 $y=0$，所以一旦出现不同符号的 $y_i$ 那一定是不可能了。

然后答案要求最小半径，尝试一下二分。显然的，随着半径的增加，保护区覆盖的范围也越大，那么也就越容易包括所有的巢穴。

如果拿着这个圆在 $x$ 轴滑动，挺不舒服的。我们换个角度，对于一个点，如果半径为 $r$ 的圆要包括它，求圆与 $y$ 轴的切点的范围。

把图画出来就知道有两个极端，一个在左边，一个在右边，就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/tqib332f.png)

点 $C$ 是巢穴， $A,B$ 是两圆圆心，$D,E$ 是切点，$CG$ 垂直于 $DE$。

考虑怎么求点 $D,E$ 的坐标。

根据已有的条件 $C$ 点的坐标，我们知道了 $CG,GH$ 的长，所以只需要求 $DG,EG$ 的长就可以了。

过 $C$ 往 $AD$ 做垂线，所以 $DF=CG=|y_A|$，所以 $AF=AD-DF=r-|y_A|$，所以 $DG=CF=\sqrt{AC^2-AF^2}=\sqrt{r^2-(r-|y_A|)^2}=\sqrt{2|y_A|r-r^2}$。同理可得 $EG=DG$，所以 $D(x_A-DG,0),E(x_A+EG,0)$，解决了切点的范围。

所以半径 $r$ 是否合法，只要判断所有点能够被圆包括的区间是否有交集就可以了。

时间复杂度 $O(n\log V)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<iomanip>
#include<cmath>
#define double long double
using std::cin;using std::cout;
constexpr int N=100005;
int n,x[N],y[N];
bool a1,a2;
inline bool check(double r){
    double l=-1e15,r0=1e15;
    for(int i=1;i<=n;++i){
        if(y[i]>2*r) return 0;//根号下为负数说明不存在交点，则交集定为空集。
        double o=y[i]*(2*r-y[i]);
        double l1=x[i]-sqrtl(o),r1=x[i]+sqrtl(o);
        l=std::max(l,l1);r0=std::min(r0,r1);//可行区间求交集
    }
    return r0>=l;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>x[i]>>y[i];
        if(y[i]<0) a1=1;
        if(y[i]>0) a2=1;
        y[i]=std::abs(y[i]);//对称方便计算（去绝对值）
    }
    if(a1&&a2){cout<<-1;return 0;}//x轴两侧均有点，无解。
    double l=0,r=1e14;
    for(int i=1;i<=1000;++i){
        double mid=(l+r)/2;
        if(check(mid)) r=mid;
        else l=mid;
    }
    cout<<std::fixed<<std::setprecision(6)<<l;
    return 0;
}
```

---

## 作者：Rice_Porridge (赞：0)

这道题我写的是一个二分（三分不会写）。以下主要讨论check函数的写法

考虑二分半径的长度，首先拆分出每一个点的情况。发现可以根据二分出的半径可以发现，可以用勾股定理求出此时圆心横坐标的取值范围

![](https://cdn.luogu.com.cn/upload/image_hosting/wtufkdvi.png)

可以发现，DF的取值范围是可以根据DE与EF算出然后就可以算出圆心在取当前点的可能存在的区间，如果计算完所有点之后仍然有不为零的区间交，那么此种半径便是合法的，否则便是不合法的，可以根据这个单调性二分。
## code

```
 
#include<bits/stdc++.h>
using namespace std;

const long double eps=1e-6;
const int N=1e5+10;

int n;
struct node{
	long double x;
	long double y;
}zb[N];

bool cmp(node a,node b){
	return a.x<b.x;
}

bool check(long double mid){
	long double xx=-1e9,xn=1e9;
	for(int i=1;i<=n;i++){
		if(2*mid<zb[i].y) return 0;
		long double x1=zb[i].x,y1=zb[i].y;
		long double l=sqrt(mid*mid-(mid-y1)*(mid-y1));
		xx=max(x1-l,xx);xn=min(x1+l,xn);
	}
	return xx<xn;
} 

int main(){
	scanf("%d",&n);
	int u=-1;
	long double mn=1e9,mx=-1e9;
	for(int i=1;i<=n;i++){
		long double a,b;scanf("%Lf%Lf",&a,&b);
		if(u==-1){if(b>0) u=1;if(b<0) u=0;}
		else{
			if(u==0&&b>0){cout<<-1;return 0;}
			if(u==1&&b<0){cout<<-1;return 0;}
		}
		mx=max(mx,a);
		mn=min(mn,a);
		if(u==1)zb[i].x=a,zb[i].y=b;
		if(u==0)zb[i].x=a,zb[i].y=-b;
	}
	long double l=0,r=1e17,ans;
	long long ui=0;
	while(r-l>eps){
		ui++;
		if(ui>=200) break;//防止因为精度问题死循环
		long double mid=(l+r)/2.0;
		if(check(mid)) {
			r=mid,ans=mid;	
		}
		else l=mid;
	}
	printf("%Lf",ans);
	return 0;
} 
```
完结撒花

---

