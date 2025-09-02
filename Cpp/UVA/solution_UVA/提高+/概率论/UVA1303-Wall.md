# Wall

## 题目描述

给定一些点，求出最短的包围所有点的轮廓且满足任意点到轮廓的距离不小于给定的$L$。

# 题解

## 作者：替罪羊树 (赞：11)

### 为您读题：
T组数据，每组有n,L,和给定的n组整数数对。整数数对表示点的坐标。求：一个周长最小的几何图形，使得该图形上任何一点到原点对构成的多边形的距离都不小于L。
### 为您解析：
- 既然是不小于，那么我们当然取等于。
- 在一条边外距离为L的是和该边构成矩形的一条平行边
#### 拐角怎么办？
    - 一种想法是：我们使得拐角处图形的任何一处到该拐点的距离都是L
    - 这构成了一个圆弧
    - 多边形的拐角（即为外角和）永远是360°，所以我们在统计答案的时候加上$2*\pi*L$即可。
    
如图所示：
![拐点和边的处理](https://cdn.luogu.com.cn/upload/pic/28166.png)
### 为你答疑：
万一是个凹多边形怎么办呢？

再如图所示
![](https://cdn.luogu.com.cn/upload/pic/28171.png)

如果我们让城墙随着D点的凹陷而拐进去，会发现反而不如直接连接与圆E和圆N的城墙拐点，因为三角形两边之和大于第三边。

我们发现，直线的城墙，每条边都和城堡的边长一样啊，这不就是一个凸包吗？

于是，问题被转化成了求二维凸包的问题。

### 为你提示：
这道题有点抽风，UVA给定的要求是每两个答案之间空一行并且文末只有一个换行。

特判剩余组数T即可。
### 为你打码（大雾）：
```
#include<bits/stdc++.h>
using namespace std;
const double pi=acos(-1);
struct point
{
    double x,y;
};
point all[2000],chose[2000];
inline point operator -(const point& a,const point& b)
{return (point){a.x-b.x,a.y-b.y};}
inline double operator *(const point& a,const point& b)
{return a.x*b.y-a.y*b.x;}
inline double dis(point a,point b)
{return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}

bool cmp(point a,point b)
{
    return (a.x==b.x)?(a.y<b.y):(a.x<b.x);
}//按照横坐标排序 
int INCLUDE(int n)
{
    //上下求两个凸壳
    int m=1;
    chose[1]=all[1];
    for(int i=2;i<=n;i++)
    {
        while(m>1&&(all[i]-chose[m])*(chose[m]-chose[m-1])<0) m--;
        chose[++m]=all[i];
    }
    int last=m;
    for(int i=n-1;i>0;i--)
    {
        while(m>last&&(all[i]-chose[m])*(chose[m]-chose[m-1])<0) m--;
        chose[++m]=all[i];
    }
    if(m>1) m--;
    return m;
}
inline int read()
{
    int n=0,k=1;
    char c=getchar();
    while(c>'9'||c<'0') {if(c=='-') k=-1; c=getchar();}
    while(c<='9'&&c>='0') {n=(n<<1)+(n<<3)+(c^48); c=getchar();	}
    return n*k;
}
int n,mm,T;
inline void prtans(int m)
{
    double ans=0;
    for(int i=1;i<=m;i++)
    {
        ans+=dis(chose[i],chose[i+1]);
    }
    ans+= 2.0*pi*mm;
    if(T) printf("%.0lf\n\n",ans);
    else printf("%.0lf\n",ans);
}

int main()
{
    T=read();
    while(T--)
    {
        n=read();
        mm=read();
        for(int i=1;i<=n;i++)
        {
            all[i].x=read();
            all[i].y=read();
        }
        stable_sort(all+1,all+n+1,cmp);
        int tot=INCLUDE(n);
        prtans(tot);
    }
    return 0;
}
```

---

## 作者：scp020 (赞：5)

# UVA1303 Wall 题解

凸包裸题

## 解法

### 结论

答案是凸包长度和一个直径是 $L$ 的圆周长的和，如图。

![图](https://cdn.luogu.com.cn/upload/image_hosting/v7ccy8r8.png)

黑色实线即为答案所求的轮廓的长度。

因为题中要求轮廓到所有点的距离大于等于 $L$，显然我们要控制所有凸包上的点到轮廓的距离等于 $L$。我们自然想到了如图的方法，把凸包平移出去 $L$ 的长度，在有点的地方，轮廓即为一段圆弧。因为凸包多凸多边形，而凸多边形的外角和为 $360^{\circ}$，所以所有圆弧长度和等于一个直径为 $L$ 的圆的周长。

### 为什么要选凸包

如果不选凸包而选一个凹进去的形状，如图，显然答案的折现比凹进去的点 $Q,O,T,U,R$ 连成的线更优。

## 代码

```cpp
#include<bits/stdc++.h>
int t,n,beginning,L;
double ans,pi=acos(-1),bx,by;
struct point
{
	double x,y,deg;
	point()
	{
		x=0x3f3f3f3f,y=0x3f3f3f3f;
	}
	point(int x,int y)
	{
		this->x=x,this->y=y;
	}
	inline void calc()
	{
		if(x==0)
		{
			if(y==0) deg=0;
			else deg=90;
		}else deg=atan2(y,x)*180/pi;
	}
	inline friend double distance(const point &lhs,const point &rhs)
	{
		return sqrt((lhs.x-rhs.x)*(lhs.x-rhs.x)+(lhs.y-rhs.y)*(lhs.y-rhs.y));
	}
	inline bool operator<(const point &rhs) const
	{
		if(deg==rhs.deg) return distance((point){0,0},*this)<distance((point){0,0},rhs);
		return deg<rhs.deg;
	}
};
point a[10010];
std::vector<point> v;
inline int min(const int &lhs,const int &rhs)
{
	if(a[lhs].y==a[rhs].y) return a[lhs].x<a[rhs].x?lhs:rhs;
	return a[lhs].y<a[rhs].y?lhs:rhs;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&L),beginning=0,v.clear();
		for(int i=1;i<=n;i++) scanf("%lf%lf",&a[i].x,&a[i].y),beginning=min(beginning,i);
		bx=a[beginning].x,by=a[beginning].y;
		for(int i=1;i<=n;i++) a[i].x-=bx,a[i].y-=by,a[i].calc();
		std::swap(a[1],a[beginning]),std::sort(a+2,a+n+1),a[++n]=a[1],v.push_back(a[1]),v.push_back(a[2]);
		ans=distance(v[0],v[1]);
		for(int i=3;i<=n;i++)
		{
			while(1)
			{
				if((a[i].x-v[v.size()-2].x)*(v.back().y-v[v.size()-2].y)>(v.back().x-v[v.size()-2].x)*(a[i].y-v[v.size()-2].y))
					ans-=distance(v.back(),v[v.size()-2]),v.pop_back();
				else break;
			}
			v.push_back(a[i]),ans+=distance(v.back(),v[v.size()-2]);
		}
		printf("%.0lf\n",ans+pi*L*2);
		if(t) printf("\n");
	}
	return 0;
}
```

---

## 作者：Grisses (赞：4)

[题面](https://www.luogu.com.cn/problem/UVA1303)

对于一堆平面上的点，如果要用一个一个多边形框住的话，周长最小的无疑是凸包了（这很好证明，三角形的任意两边之和大于第三边，所以凸的会优于凹的）。要距离所有城池至少 $L$，再加一段弧就行了，不难发现，所有的弧的圆心角都是多边形的外角，对于一个凸多边形，外角和为 $360^{\circ}$。即一个圆。

![](https://cdn.luogu.com.cn/upload/image_hosting/lomqusqh.png)

所有答案是凸包的周长加上半径为 $L$ 的圆的周长。

代码：
```cpp
  #include<bits/stdc++.h>
  #define db double
  using namespace std;
  int T,n,L,top=0;//投票表示栈顶
  db p=3.14159265358979323846;//求圆的周长需要Pi
  struct node{//存储点
      db x,y;
      node(){}
      node(int a,int b){x=a,y=b;}
      bool operator<(const node &t)const{//重载小于（最左最下的一个点）
          return y<t.y||(y==t.y&&x<t.x);
      }
      node operator-(const node &t)const{//重载减
          return node(x-t.x,y-t.y);
      }
  }a[200005],s[200005];//s是栈
  db ans,_x,_y;
  int CPr(node A,node B){
      return A.x*B.y-A.y*B.x;//向量叉积
  }
  db len(node A,node B){return sqrt(1.0*(A.x-B.x)*(A.x-B.x)+1.0*(A.y-B.y)*(A.y-B.y));}//求距离
  bool cmp(node A,node B){//以最左最下的点为极点，建立极坐标系，按极角从小到大排序，如果极角相同则按距离从小到大排序
      _x=CPr(A-a[1],B-a[1]);
      if(_x>0)return 1;
      if(_x==0)return len(A,a[1])<len(B,a[1]);
      return 0;
  }
  int main()
  {
      scanf("%d",&T);
      while(T--){
          scanf("%d%d",&n,&L);
          for(int i=1;i<=n;i++)scanf("%lf%lf",&a[i].x,&a[i].y);
          sort(a+1,a+n+1);
          sort(a+2,a+n+1,cmp);//排序
          top=ans=0;
          s[++top]=a[1];
          s[++top]=a[2];
          for(int i=3;i<=n;i++){
              while(top>2&&CPr(s[top]-s[top-1],a[i]-s[top-1])<=0)top--;
              s[++top]=a[i];//求凸包
          }
          for(int i=1;i<=top;i++)ans+=len(s[i],s[i%top+1]);//求周长
          ans+=p*L*2;//加上圆的周长
          printf("%.0lf\n",ans);
          if(T)puts("");//沙雕的输出
      }
      return 0;
  }
```

---

## 作者：Heartlessly (赞：4)

## Description

共 $T$ 组数据。给定 $n$ 个点，求出最短的包围所有点的轮廓且满足任意点到轮廓的距离不小于给定的 $L$ 。

$(3 \leq n \leq 10^3,1 \leq L \leq 10^3,-10^4 \leq x_i,y_i \leq 10^4)$

## Solution

所有点到轮廓的距离都 $\geq L$，显然取等于时是最优的。

因此轮廓一定由若干线段和圆弧构成。

![VNDe3t.png](https://s2.ax1x.com/2019/06/05/VNDe3t.png)

而所有的线段都可以由点与点之间的连线平移得到，而且点围成的图形一定是一个凸多边形（凹多边形显然不优，比如图中的 $GH + HF > GF$）。也就是说线段的长度和就是凸包的长度。

那圆弧的长度呢？我们可以大胆猜想圆弧的总长刚好是一个圆周。

**证明：**

以图中底部的圆为例。

$\because IB$ 和 $CJ$ 分别是 $\odot A$ 和 $\odot D$，$\odot A$ 和 $\odot E$ 的外公切线，$AD \parallel IB,AE \parallel CJ$

$\therefore \angle DAB = \angle EAC = \angle ABI = \angle ACJ = 90^\circ$

$\therefore \angle DAE$ 与 $\angle BAC$ 互补

$\because$ $\angle DAE$ 与它的外角互补

$\therefore \angle BAC$ 等于 $\angle DAE$ 的外角

同理，每个圆弧所对的圆心角都是凸多边形的一个外角，而凸多边形的外角和为 $360^\circ$，因此圆弧的总长即是半径为 $L$ 的圆的周长。

凸包长度加上圆弧总长即是答案。时间复杂度为 $O(n \log n)$ 。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

const int MAXN = 1e3;
const double PI = acos(-1);
int t, n, l, top, tag;
double ans;
struct Vector {
    double x, y;
    
    inline friend bool operator<(Vector a, Vector b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }
    inline friend Vector operator-(Vector a, Vector b) {
        return (Vector) { a.x - b.x, a.y - b.y };
    }
} a[MAXN + 5], sta[MAXN + 5];

inline double dist(Vector a, Vector b) {//两点的直线距离 
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline double cross(Vector a, Vector b) {//叉积 
    return a.x * b.y - a.y * b.x;
}

inline void getConvexHull(Vector *a, int n) {//求凸包长度 
    top = ans = 0;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        for (; top > 1 && cross(sta[top] - sta[top - 1], a[i] - sta[top]) <= 0; --top);
        sta[++top] = a[i];
    }
    tag = top;
    for (int i = n - 1; i; --i) {
        for (; top > tag && cross(sta[top] - sta[top - 1], a[i] - sta[top]) <= 0; --top);
        sta[++top] = a[i];
    }
    for (int i = 1; i < top; ++i) ans += dist(sta[i], sta[i + 1]);
}

int main() {
    for (read(t); t; --t) {
        read(n), read(l);
        for (int i = 1; i <= n; ++i) scanf("%lf %lf", &a[i].x, &a[i].y);
        getConvexHull(a, n);
        ans += 2 * PI * l;//加上圆弧总长 
        printf("%.0lf\n", ans);
        if (t > 1) putchar('\n');//最后一组数据一个换行，其它数据两个换行 
    }
    return 0;
}
```



---

## 作者：lailai0916 (赞：2)

## 原题链接

- [洛谷 UVA1303 Wall](https://www.luogu.com.cn/problem/UVA1303)

## 题意简述

给定平面上 $n$ 个点，求出最短的包围所有点的轮廓且满足任意点到轮廓的距离不小于给定的 $L$。

## 解题思路

凸多边形是指所有内角大小都在 $[0, \pi]$ 范围内的简单多边形。在平面上能够包含所有给定点的最小凸多边形被称为 **凸包**，因此不会出现类似 $\angle GHF$ 这种凹角的情况。

借用 [Heartlessly](https://www.luogu.com.cn/user/32139) 大佬的图示：

![](https://s2.ax1x.com/2019/06/05/VNDe3t.png)

整个外轮廓由 **线段** 和 **圆弧** 组成。

每条线段（红色）的长度都等于多边形（凸包）对应边（蓝色）的长度，因此所有线段的总长度正好等于凸包的周长。

每段圆弧的长度与对应圆心角成正比。对于每个类似 $\angle BAC$ 的角，我们可以表示为：

$$
\angle BAC = 2\pi - \angle DAE - \angle BAD - \angle CAE = \pi - \angle DAE
$$

注意到 $\pi - \angle DAE$ 刚好等于 $\angle DAE$ 的外角，而多边形所有外角之和为 $2\pi$。因此，所有圆弧的总长度等于一个半径为 $L$ 的圆的周长，即 $2\pi L$。

使用 Andrew 算法 或 Graham 扫描法计算凸包的周长，再加上 $2\pi L$，即为最终结果。

## 参考代码

### Andrew 算法

```cpp
#include <bits/stdc++.h>
using namespace std;

const double pi=acos(-1);
const int N=1005;
struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y):x(_x),y(_y){}
	Point operator-(Point B){return Point(x-B.x,y-B.y);}
}a[N];
double Dis(Point A,Point B){return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));}
double Cross(Point A,Point B){return A.x*B.y-A.y*B.x;}
bool cmp(Point A,Point B)
{
	return A.x!=B.x?A.x<B.x:A.y<B.y;
}
int s[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		int n,l;
		cin>>n>>l;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i].x>>a[i].y;
		}
		sort(a+1,a+n+1,cmp);
		int m=0;
		for(int i=1;i<=n;i++)
		{
			while(m>1&&Cross(a[s[m]]-a[s[m-1]],a[i]-a[s[m]])<=0)m--;
			s[++m]=i;
		}
		int t=m;
		for(int i=n-1;i>=1;i--)
		{
			while(m>t&&Cross(a[s[m]]-a[s[m-1]],a[i]-a[s[m]])<=0)m--;
			s[++m]=i;
		}
		if(m>1)m--;
		double ans=l*pi*2;
		for(int i=1;i<=m;i++)ans+=Dis(a[s[i]],a[s[i%m+1]]);
		cout<<int(ans+0.5)<<'\n';
		if(T)cout<<'\n';
	}
	return 0;
}
```

### Graham 扫描法

```cpp
#include <bits/stdc++.h>
using namespace std;

const double pi=acos(-1);
const int N=1005;
struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y):x(_x),y(_y){}
	Point operator-(Point B){return Point(x-B.x,y-B.y);}
}a[N];
double Dis(Point A,Point B){return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));}
double Cross(Point A,Point B){return A.x*B.y-A.y*B.x;}
bool cmp(Point A,Point B)
{
	double t=Cross(A-a[1],B-a[1]);
	return t!=0?t>0:Dis(A,a[1])<Dis(B,a[1]);
}
int s[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		int n,l;
		cin>>n>>l;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i].x>>a[i].y;
			if(a[i].y!=a[1].y?a[i].y<a[1].y:a[i].x<a[1].x)swap(a[i],a[1]);
		}
		sort(a+2,a+n+1,cmp);
		int m=0;
		for(int i=1;i<=n;i++)
		{
			while(m>1&&Cross(a[s[m]]-a[s[m-1]],a[i]-a[s[m]])<=0)m--;
			s[++m]=i;
		}
		double ans=l*pi*2;
		for(int i=1;i<=m;i++)ans+=Dis(a[s[i]],a[s[i%m+1]]);
		cout<<int(ans+0.5)<<'\n';
		if(T)cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Yaha (赞：2)

### 二维凸包

借用一下Heartlessly大佬的图

![](https://s2.ax1x.com/2019/06/05/VNDe3t.png)

一个很直观的想法就是，既然题目要求每处离城堡的距离大于等于 $L$ ，那我们就处处距离为 $L$ 。这一定比某个地方莫名其妙凸出来一坨要优。但是难道题目就是让你求一遍原多边形周长吗？

Of course not.

来看能不能更优。观察上图中那一块凹进去的部分，根据三角形三边关系可以知道，上方平滑的那条一定比下面两条之和更优。已经不能更优了。我们再来考虑怎样求这个图形的周长。

对于那些平滑的直线，容易发现，长度和就是凸包周长。再看旁边的圆弧。例如点 $A$ 处，圆弧角度 $∠BAC+$ 多边形内角 $∠DAE+$ 两个直角 $=360°$ ,所以圆弧角度数值上等于该点外角。凸多边形外角和 $360°$ ，所以所有圆弧的角度加起来为 $360°$ 。

所以答案就是 凸包周长 $+2πL$

代码：
```cpp
#include<bits/stdc++.h>

#define D double
#define x first
#define y second

using namespace std;

const int amou=2100;
const D eps=1e-8,PI=acos(-1);
typedef pair<D,D>PDD;

int n,L;
PDD p[amou];
int top,stac[amou];
bool we[amou];

PDD operator-(PDD a,PDD b){
	return {a.x-b.x,a.y-b.y};
}

D cross(PDD a,PDD b){
	return a.x*b.y-a.y*b.x;
}

D area(PDD a,PDD b,PDD c){
	return cross(b-a,c-a);
}

D get_dist(PDD a,PDD b){
	D X=a.x-b.x,Y=a.y-b.y;
	return sqrt(X*X+Y*Y);
}

D get_convex(){
	sort(p+1,p+n+1);
	top=0;
	memset(we,0,sizeof we);
	memset(stac,0,sizeof stac);
	for(int i=1;i<=n;i++)
	{
		while(top>=2&&area(p[stac[top-1]],p[stac[top]],p[i])>=0)
		{
			if(area(p[stac[top-1]],p[stac[top]],p[i])>0)
				we[stac[top]]=0;
			top--;
		}
		stac[++top]=i;
		we[i]=1;
	}
	we[1]=0;
	for(int i=n;i>=1;i--)
	{
		if(we[i]) continue;
		while(top>=2&&area(p[stac[top-1]],p[stac[top]],p[i])>=0)
			top--;
		stac[++top]=i;
	}
	D ret=0;
	for(int i=1;i<top;i++)
		ret+=get_dist(p[stac[i]],p[stac[i+1]]);
	return ret;
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&L);
		for(int i=1;i<=n;i++)
			scanf("%lf%lf",&p[i].x,&p[i].y);
		printf("%.lf\n",get_convex()+2*PI*L);
		if(t) puts("");
	}

	return 0;
}
```


---

## 作者：HYdroKomide (赞：1)

双倍经验：[P2116 城墙](https://www.luogu.com.cn/problem/P2116)，唯一的区别在多测，需要注意清空~~和诡异的输出方式~~。

## 题意：

给定一些点，求一条围住所有点且距离所有点距离不小于 $L$ 的围墙长度。

## 思路：

首先，能够围住所有点的最短围墙即为这些点所组成的凸包。这是凸包定义的一部分，证明起来也很容易：如果有任何大于 $180\degree$ 的角度出现，利用三角形两点之和大于第三边可知，直接连上对应的两个点一定更短。

因为有墙的距离与点距离不小于 $L$ 这一条件，对于每一个凸包上的顶点都一定有一个 $L$ 为半径、该顶点外角为夹角的一段圆弧。由凸多边形外角和为 $180\degree$ 可得，最终所有圆弧对围墙长度的贡献就是一个圆周，即 $2\pi L$。

剩下的就是平面凸包模板题，使用 Andrew 算法即可，个人认为更容易想且可用范围更大（相同的思想可以在一些斜率优化 dp 中求下凸包）。

简单回顾一下 Andrew 算法。其总体思想就是将上下凸壳分开来求，对于每一个凸壳，其连线斜率必然单调。以从左到右的顺序扫描，开个栈维护单调性即可做到带排序 $O(n\log n)$ 时间复杂度。

先从左到右依次入栈，找到有与栈顶的斜率比次栈顶小，即可弹出栈顶。简单来说，对于以下的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/vbs8ji1u.png)

如图我们先让 $A$、$B$ 依次进栈，发现次栈顶 $AC$ 斜率比栈顶 $BC$ 斜率还小，我们让 $B$ 速速出栈。从头遍历到尾，然后把栈里的相邻元素距离加入答案。

上凸壳反着做一遍一模一样的即可。

注意，为防止三点共线或斜率为无穷的情况，需要提前对所有节点的坐标做微小扰动，**随机加或减一个极小值**。

## 程序如下：

```cpp
#include<cstdio>
#include<algorithm>
#include<random>
#include<stack>
#include<cmath>
using namespace std;
const int N=1e3+5;
const double eps=1e-6,PI=3.1415926;
int T,n,top;
double r,ans;
struct NODE{double x,y;}a[N],st[N];
mt19937 rnd(19491001);
double disturb(){
	int rn=rnd();
	return (double)rn/2e9*eps;
}
bool cmp(NODE x,NODE y){return x.x<y.x;}
double getk(NODE x,NODE y){return (x.y-y.y)/(x.x-y.x);}
double getdis(NODE x,NODE y){return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));}
int main(){
	scanf("%d",&T);
	while(T--){
		ans=0;
		scanf("%d%lf",&n,&r);
		for(int i=1;i<=n;i++)scanf("%lf%lf",&a[i].x,&a[i].y),a[i].x+=disturb(),a[i].y+=disturb();
		sort(a+1,a+n+1,cmp);
		top=0;
		st[++top]=a[1];
		for(int i=2;i<=n;i++){
			while(top>1&&getk(a[i],st[top-1])<getk(a[i],st[top]))top--;
			st[++top]=a[i];
		}
		for(int i=1;i<top;i++)ans+=getdis(st[i],st[i+1]);
		top=0;
		st[++top]=a[n];
		for(int i=n-1;i>=1;i--){
			while(top>1&&getk(a[i],st[top-1])<getk(a[i],st[top]))top--;
			st[++top]=a[i];
		}
		for(int i=1;i<top;i++)ans+=getdis(st[i],st[i+1]);
		printf("%.0lf\n",ans+2*PI*r);
		if(T)puts("");
	}
	return 0;
}
```

## THE END

AC 经历：不断尝试修改输出方式但是依然没有过。与标程对拍几万组后发现是扰动的随机种子 $19491001$ 和 $eps=10^{-9}$ 恰好被卡了，原地破防。（防止被卡以后还是写向量叉乘吧）

---

## 作者：SpeMars (赞：1)

## 关于凸包の题

这道题是一道凸包的题

题目要求其实就是在原来凸包的基础上加上了原所有点到凸包的距离大于等于 $L$

的限制。所以我们可在凸包的基础上进行平移

注:(此图来自奆佬[替罪羊树](https://www.luogu.com.cn/user/32234))

![](https://cdn.luogu.com.cn/upload/pic/28171.png)

通过对于图片的分析，我们不难得知原凸包中的每条边都可以通过平移

转移到距离原凸包的点长度 $L$的位置但是这样原凸包就不相连了(即不为封闭图形)

我们要连接这些零散的边，且始终保持原凸包上的点到新凸包的距离大于等于 $L$

所以我们可以用圆弧来连接，既能保证各个位置到原凸包点的距离大于等于 $L$，

并且能保证这种方案是最短的。

又因为所有圆弧的圆心角之和为 $360$度，所以其周长总和刚好构成一个半径为 $L$的圆

所以我们只需要在原凸包周长的基础上加上半径为 $L$的圆的周长即可

code:

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
const int N=1e4+10;
const double pi=acos(-1.0);
int t,n,l,top;
struct node{
    int x,y;
}p[N],s[N];
double ans;
//a1,a2 b1,b2 叉积 =0 共线，<0 b在a逆时针方向,>0 b在a顺时针方向 
int check(node a1,node a2,node b1,node b2){
    return (a2.x-a1.x)*(b2.y-b1.y)-(b2.x-b1.x)*(a2.y-a1.y);
}
int fdis(node p1,node p2){
    return (p2.y-p1.y)*(p2.y-p1.y)+(p2.x-p1.x)*(p2.x-p1.x);
}
double dis(node p1,node p2){
	return (double)(sqrt(fdis(p1,p2)));
}
bool cmp(node p1,node p2){
    double tmp=check(p[1],p1,p[1],p2);
    if(tmp>0)return true;
    if(tmp==0&&fdis(p[0],p1)<fdis(p[0],p2))return true;
    return false;
}
int main(){
	scanf("%d",&t);
	for(;t--;){
		ans=0,top=0;
		scanf("%d%d",&n,&l);
		for(int i=1;i<=n;++i){
		    scanf("%d%d",&p[i].x,&p[i].y);
		    if(p[i].y<p[1].y)swap(p[i],p[1]);
		    else if(p[i].y==p[1].y&&p[i].x<p[1].x)swap(p[i],p[1]);
		}
		sort(p+2,p+n+1,cmp);
		s[++top]=p[1];
		for(int i=2;i<=n;++i){
		    for(;top>1&&check(s[top-1],s[top],s[top],p[i])<=0;--top);
		    s[++top]=p[i];
		}
		s[top+1]=s[1];
		for(int i=1;i<=top;++i)ans+=dis(s[i],s[i+1]);
		ans+=(pi*2*l);
		printf("%.0lf\n",ans);
		if(t)puts("");
	} 
    return 0;
}
```

---

## 作者：EternalEpic (赞：1)

暑假做的，因为只有此题三篇题解，所以补档题解。

这道题呢，乍一看，是一个二维凸包。可是它有一个对点最小距离的限制，也就是说，不是求直线凸包，而是求几个半径为L的圆的凸包。

借用一下Heartlessly大佬的图。

![图](https://s2.ax1x.com/2019/06/05/VNDe3t.png)

我们可以看到，圆的凸包，就是其圆心的凸包线段长度，加上最外层圆弧的长度。

然后圆弧长怎么求？我提供一个与Heartlessly大佬不同的证法。

首先，都是r = L的等圆，所以我们只要求出其圆心角度数之和。

其次，圆心凸包一定是凸多边形（如图），而我们用平移线段造出来矩形，将矩形各边延长，交出一个与ADGFE相似的五边形。通过矩形的直角，可以知道单个圆的圆心角与其所对五边形内角互补。

所以扩展到n边形，内角和为(n - 2) * 180。

则圆心角和为n * 180 - (n - 2) * 180 = 360。也就是一个圆周长。

到这儿，问题迎刃而解。

代码：

```cpp
enum {
	Maxn = 1005
};
const double PI = acos(-1.0);

int T, n, l, top, tag;
double ans;

struct Vector {
	double x, y;
	Vector(double _x = 0, double _y = 0) : x(_x), y(_y) {}
	inline void Scanner(void) { read(x), read(y); }

	inline bool operator < (const Vector&rhs)
	const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
	inline Vector operator - (const Vector&rhs)
	const { return Vector(x - rhs.x, y - rhs.y); }
	inline Vector operator + (const Vector&rhs)
	const { return Vector(x + rhs.x, y + rhs.y); }
	
	inline Vector operator * (const double&rhs)
	const { return Vector(x * rhs, y * rhs); }
	inline Vector operator / (const double&rhs)
	const { return Vector(x / rhs, y / rhs); }
} a[Maxn], sta[Maxn];

inline double dist(const Vector&a, const Vector&b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline double cross(const Vector&a, const Vector&b) {
	return a.x * b.y - a.y * b.x;
}

inline bool check(int i) { return cross(sta[top] - sta[top - 1], a[i] - sta[top]) <= 0; }

inline void GetConvexHull(void) {
	top = ans = 0; sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		for (; top > 1 && check(i); --top);
		sta[++top] = a[i];
	} tag = top;
	for (int i = n - 1; i; i--) {
		for (; top > tag && check(i); --top);
		sta[++top] = a[i];
	}
	for (int i = 1; i < top; i++) ans += dist(sta[i], sta[i + 1]);
}

signed main(void) {
	//file("");
	read(T);
	while (T--) {
		read(n), read(l);
		for (int i = 1; i <= n; i++) a[i].Scanner();
		GetConvexHull(); ans += 2.0 * PI * l;
		printf("%.0lf\n", ans); if (T) puts("");
	}
	//fwrite(pf, 1, o1 - pf, stdout);
	return 0;
}

/**/

```

最后注意UVA是多测！


---

## 作者：VenusM1nT (赞：1)

二维凸包。

首先看题目，围的墙要离点 $r$ 距离，也就是说在以点为圆心，半径为 $r$ 的这个范围内不能有墙，我们不妨将这些圆画起来，如下图：

![](https://i.loli.net/2019/07/17/5d2eebd5c788a11943.png)

再看题，要求最短的长度，不由自主地我们会想到凸包，但是这道题由于有 $r$ 的限制，看起来并不是很容易用凸包，怎么办呢？

我们想一道小学时做的题目，一个矩形的四个角被替换成 $\frac{1}{4}$ 圆，然后计算周长 / 面积。我们可以从这道题中获得启发，也就是说我们依然使用二维凸包的做法，但是凸包的边是从一个圆上连到另一个圆上。比如，我们原来直接求凸包是这样的：

![](https://i.loli.net/2019/07/17/5d2eed29daf9845433.png)

移到圆上后，就变成了这样的：

![](https://i.loli.net/2019/07/17/5d2eedadaea5630902.png)

显然，这就是最短的方案了，而它的长度是多少呢？

其实就是上面直接求凸包的长度，加上一个额外的圆。因为我们相当于是将原来的线段向外平移后接到了圆上，正好是多出一个圆的周长。

所以我们直接求凸包即可。

```cpp
#include<bits/stdc++.h>
#define MAXN 1005
#define reg register
#define inl inline
#define db double
using namespace std;
struct Node
{
    double x,y;
    friend bool operator < (const Node &x,const Node &y)
    {
        return x.y==y.y?x.x<y.x:x.y<y.y;
    }
}a[MAXN];
const double Pi=acos(-1.0);
int n,r,stk[MAXN],top;
double res;
inl bool Cross(reg Node x,reg Node y,reg Node z)
{
    return (x.y-y.y)*(y.x-z.x)>(x.x-y.x)*(y.y-z.y);
}
inl db Dist(reg Node x,reg Node y)
{
    return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}
int main()
{
    reg int Time;
    scanf("%d",&Time);
    while(Time--)
    {
        memset(a,0,sizeof(a));
        memset(stk,0,sizeof(stk));
        top=0;
        res=0.0;
        scanf("%d %d",&n,&r);
        for(int i=1;i<=n;i++) scanf("%lf %lf",&a[i].x,&a[i].y);
        sort(a+1,a+n+1);
        stk[++top]=1;
        stk[++top]=2;
        for(int i=3;i<=n;i++)
        {
            while(top>1 && !Cross(a[i],a[stk[top]],a[stk[top-1]])) top--;
            stk[++top]=i;
        }
        for(int i=1;i<top;i++) res+=Dist(a[stk[i]],a[stk[i+1]]);
        memset(stk,0,sizeof(stk));
        top=0;
        stk[++top]=1;
        stk[++top]=2;
        for(int i=3;i<=n;i++)
        {
            while(top>1 && Cross(a[i],a[stk[top]],a[stk[top-1]])) top--;
            stk[++top]=i;
        }
        for(int i=1;i<top;i++) res+=Dist(a[stk[i]],a[stk[i+1]]);
        reg db ans=res+2.0*r*Pi;
        printf("%.0lf\n",ans);
        if(Time) puts("");
    }
    return 0;
}
```

---

## 作者：ivyjiao (赞：0)

根据凸包的性质，对于一些平面上的点，用一个多边形框住，周长最小的是凸包。所以我们先把凸包求出来，然后无视掉剩下的城堡。

不难发现，要求距离所有城池至少 $L$ 的城墙长度，还需要加一段弧，画个图就能得到，所有的弧的圆心角都是凸包对应角的外角，因为对于任意一个凸多边形（显然凸包是凸多边形），外角和为 $360$ 度，所以要加上的弧长是一个半径为 $L$ 的圆的周长。

注意一个点：$\pi$ 要取到 $3.14159$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1;
int t,n,m,s[N],l;
double ans;
struct node{
    double x,y;
}a[N];
int angel(node a,node b,node c){
    return (a.y-b.y)*(b.x-c.x)-(a.x-b.x)*(b.y-c.y);
}
double dis(node a,node b){
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}
bool cmp(node a,node b){
    if(a.x==b.x) return a.y<b.y;
    return a.x<b.x;
}
int main(){
    cin>>t;
    while(t--){
        ans=0;
        cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
        sort(a+1,a+1+n,cmp);
        s[1]=1,s[2]=2;
        l=2;
        for(int i=3;i<=n;i++){
            while(l>1&&angel(a[i],a[s[l]],a[s[l-1]])<=0) l--;
            s[++l]=i;
        }
        for(int i=1;i<l;i++) ans+=dis(a[s[i]],a[s[i+1]]);
        s[1]=1,s[2]=2;
        l=2;
        for(int i=3;i<=n;i++){
            while(l>1&&angel(a[i],a[s[l]],a[s[l-1]])>=0) l--;
            s[++l]=i;
        }
        for(int i=1;i<l;i++) ans+=dis(a[s[i]],a[s[i+1]]);
        printf("%.0f\n",ans+3.14159*m*2);
        if(t) cout<<endl;
    }
}
```

---

## 作者：Emp7iness (赞：0)

## 前置知识：二维凸包

[二维凸包模板传送门](https://www.luogu.com.cn/problem/P2742)

[OI Wiki](https://oi-wiki.org/geometry/convex-hull/)

凸包的定义：在平面上能包含所有给定点的最小凸多边形叫做凸包。

求凸包的算法一般有两种，分别是 Andrew 算法和 Graham 算法，这里只介绍 Graham 算法。

Graham 算法的原理就是维护一个点集，通过扫描所有点向点集中不断添加更优的点和删除“凹”点最终形成凸包（因为如果一个凹多边形符合要求，那么必有一个凸多边形在周长上优于它，不然为什么不叫凹包）。

### 算法步骤

首先需要对点集排序。

Graham 算法快的一个很重要的原因就是因为预先进行了排序，所以可以减少扫描次数。

我们选择一个 $y$ 值最小的点（这里记为 $P_1$），将剩余点按照极角的大小排序（这里记为 $P_2$ - $P_5$）

![](https://cdn.luogu.com.cn/upload/image_hosting/arbcuh04.png)

我们按照排序的顺序，依次连接每一个点，如果发现当前点 $p[i]$ 与前两个点 $p[i-1]$ 与 $p[i-2]$ 形成了一个“凹壳”，那么点 $p[i-1]$ 就肯定不在凸包的点集当中。

下面是图解：

![](https://cdn.luogu.com.cn/upload/image_hosting/3fjgvkha.png)

首先连接 $P_1P_2$ 和 $P_2P_3$ ，暂时没有发现问题。

![](https://cdn.luogu.com.cn/upload/image_hosting/1p40zsug.png)

连接 $P_3P_4$ ，依然没有发现问题。

![](https://cdn.luogu.com.cn/upload/image_hosting/nsni3brs.png)

连接 $P_4P_5$ ，问题来了，$P_3P_4P_5$ 组成了一个“凹壳”，这样我们就应该把 $P_4$ 踢出去，直接连接 $P_3P_5$ 。

![](https://cdn.luogu.com.cn/upload/image_hosting/he6qm0wg.png)

踢出 $P_4$ ，连接 $P_3P_5$ 和 $P_5P_1$ ，凸包就求出来了。

回到本题。

[UVA1303 Wall](https://www.luogu.com.cn/problem/UVA1303)

题目要求最近距离不小于 $L$	,还要求周长最小值，那肯定恰好等于 $L$ 是最优的。

![](https://cdn.luogu.com.cn/upload/image_hosting/a7wq4ipu.png)

按照题意画出图，可以发现要求的就是多边形外面围的这一圈，由若干圆弧和线段组成。

易得 $P_1P_4IH$ 为矩形，所以 $IH=P_1P_4$ ，所以这一圈中的线段长度之和就是多边形周长。

怎么求多边形周长？可以用凸包求解，将给定点丢进凸包板子里就行了。

至于圆弧的总长度，猜想它就是一个圆的周长，也就是 $2 \pi L$ 。

证明：易得在 $\odot P_1$ 上的圆弧所对的圆心角与 $\angle P_2P_4P_1$ 互补。

同理，每个圆弧所对的圆心角都与多边形的一个内角互补。

因为凸多边形的外角和为 $360^{\circ}$ ，所以所有圆弧所对的圆心角之和为 $360^{\circ}$ ，所以所有圆弧的长度之和就是一个圆的周长。

最终答案即为凸包周长 $+ 2 \pi L$ 。

**提醒：注意细节，有多组数据，而且要输出两个换行，而且最后一组数据要少输出一个换行**

双倍经验 [P2116 城墙](https://www.luogu.com.cn/problem/P2116)

## 代码

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int T,n,l,t=1;
double ans;
struct point
{
	double x,y;
}p[1005],s[1005];
double dis(point a,point b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double check(point a1,point a2,point b1,point b2)
{
	return (a1.x-a2.x)*(b1.y-b2.y)-(a1.y-a2.y)*(b1.x-b2.x);
}
bool cmp(point a,point b)
{
	double k=check(a,p[1],b,p[1]);
	if(k>0||(k==0&&dis(a,p[1])<dis(b,p[1])))	return 1;
	return 0;
}
int main()
{
	cin>>T;
	while(T--)
	{
		t=1; ans=0;
		cin>>n>>l;
		for(int i=1;i<=n;i++)
		{
			cin>>p[i].x>>p[i].y;
			if(p[i].y<p[1].y)	swap(p[i],p[1]);
		}
		sort(p+2,p+n+1,cmp);
		s[1]=p[1];
		for(int i=2;i<=n;i++)
		{
			if(p[i-1].x==p[i].x&&p[i-1].y==p[i].y)	continue;
			while(t>1&&check(s[t],s[t-1],p[i],s[t])<0)	t--;
			s[++t]=p[i];
		}
		s[t+1]=p[1];
		for(int i=1;i<=t;i++)	ans+=dis(s[i],s[i+1]);
		cout<<round(ans+l*6.2831853)<<endl;
		if(T)	cout<<endl;
	}
	return 0;
}
```


---

## 作者：zmza (赞：0)

这题的思路大概就是先跑一个凸包，再加上一个圆的面积。


代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
struct node{double x,y;}a[100005],z[100005];
bool cmp(node a,node b,node c){return (a.y - b.y) * (b.x - c.x) <= (b.y - c.y) * (a.x - b.x);}
bool c(node a,node b){return a.x < b.x;}
double get(node a,node b){return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));}
int main()
{
	int n,m;
	int t;
	scanf("%d",&t);
	while(t--)
	{
	    scanf("%d%d",&n,&m);
		for(int i = 1; i <= n; i++)scanf("%lf%lf",&a[i].x,&a[i].y);
		sort(a + 1,a + 1 + n,c);//开始跑凸包
        int top = 2;
		z[1] = a[1],z[2] = a[2];
		for(int i = 1; i <= n; i++)
		{
			while(top > 1 && cmp(a[i],z[top],z[top - 1]))top--;
			z[++top] = a[i];
		}	
		double ans = 0;
		for(int i = 1; i <= top - 1; i++)ans += get(z[i],z[i + 1]);//算凸包
		top = 2;
		z[1] = a[n],z[2] = a[n - 1];
		for(int i = n; i >= 1; i--)
		{
			while(top > 1 && cmp(a[i],z[top],z[top - 1]))top--;
			z[++top] = a[i];
		}
		for(int i = 1; i <= top - 1; i++)ans += get(z[i],z[i + 1]);//同上
		printf("%.0lf\n",ans + 3.1415926535 * 2 * m);//输出要加上一个圆的面积。
		if(t != 0)puts("");//换行。
	}
	return 0;
}
```

---

## 作者：H_D_NULL (赞：0)

~~其实如果直接给出答案计算公式，这就是道绿题~~

### 凸包实际运用


------------
#### 题意
一个贪婪的国王要求他的建筑师建一堵墙（图中虚线）围绕他的城堡（图中实线），且墙与城堡之间的距离总不小于一个数L。输入城堡各个节点（图中实线与实线的交点）的坐标和L，要求最小的墙壁周长。

![](https://cdn.luogu.com.cn/upload/image_hosting/4828k303.png)

#### 解：

看完题面我们可以知道，~~所以这和贪婪有毛关系~~，若 $L=0$ ，不难想到，此最小周长即为所给结点的凸包周长。

题面要求围墙和城堡之间的距离不小于 $L$ ，则我们把 $L=0$ 时的状况推广，想象将上述凸包的每一条边都向外平移 $L$ 单位长度，形成多条距城堡 $L$ 的线段，其总和为上述凸包周长。题目要求墙为封闭图形，则我们用最短的方式将这些线段连接，故两两线段之间用以对应凸包结点为圆心，半径为 $L$ 的圆上的一段圆弧连接。

不难证得，所有圆弧的圆心角之和为 $360$ 度，所以题目条件转化为：**求给定节点的凸包周长，在加上以 L 为半径的圆的周长**。现在我们就可以发现题目中最大的坑点，~~图给了个“凹”字~~，怎样，迷惑吧。

关于读入输出的格式，此处不再赘述，详见代码。

如果对求凸包的操作不了解的，我也。。。

#### 完


------------

_Talk is cheap, show me the code_

```cpp
#include<bits/stdc++.h>
#define re register
#define Pi 3.1415926
#define mn 1005
using namespace std;

int n,L,T;

struct dr{
	double x,y;
} q[mn];

inline bool cmp(dr a,dr b){
	return a.y<b.y||(a.y==b.y&&a.x<b.x);
}

inline int Cross(dr p1,dr p2,dr p3){
	return (p1.x-p3.x)*(p2.y-p3.y)-(p1.y-p3.y)*(p2.x-p3.x);
}

int a[mn],b[mn],top;

inline void Scan(){ //水平排序法求凸包
	a[1]=1; a[2]=2; top=2;
	for(re int i=3;i<=n;i++){
		while(top>1&&Cross(q[a[top]],q[i],q[a[top-1]])<=0) top--;
		a[++top]=i;
	}
	for(re int i=1;i<=top;i++) b[++b[0]]=a[i];
	a[1]=n; a[2]=n-1; top=2;
	for(re int i=n-2;i;i--){
		while(top>1&&Cross(q[a[top]],q[i],q[a[top-1]])<=0) top--;
		a[++top]=i;
	}
	if(b[b[0]]==a[1]){
		for(re int i=2;i<top;i++){
			b[++b[0]]=a[i];
		}
	}
	else{
		for(re int i=1;i<top;i++){
			b[++b[0]]=a[i];
		}
	}
	b[++b[0]]=b[1];
}

inline double Dis(dr x,dr y){
	return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&L);
    	for(re int i=1;i<=n;i++) scanf("%lf %lf",&q[i].x,&q[i].y);
    	sort(q+1,q+1+n,cmp);
    	b[0]=0; //初始化
    	Scan();
    	re double sum=L*2*Pi;
    	for(re int i=2;i<=b[0];i++){
    		sum+=Dis(q[b[i]],q[b[i-1]]);
    	}
    	printf("%.0lf\n",sum);
    	if(T) puts(""); //特殊格式，答案之间有一空行，最后一行只有一个换行（好绕）
    }
	return 0;
}
```


---

