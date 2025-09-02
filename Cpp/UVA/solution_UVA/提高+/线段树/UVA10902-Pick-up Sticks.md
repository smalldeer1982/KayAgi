# Pick-up Sticks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1843

[PDF](https://uva.onlinejudge.org/external/109/p10902.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10902/702970269e727240519ea95b134ce15226100639.png)

## 样例 #1

### 输入

```
5
1 1 4 2
2 3 3 1
1 -2.0 8 4
1 4 8 2
3 3 6 -2.0
3
0 0 1 1
1 0 2 1
2 0 3 1
0```

### 输出

```
Top sticks: 2, 4, 5.
Top sticks: 1, 2, 3.```

# 题解

## 作者：haoyun1 (赞：5)

# 题目大意：

按照顺序给你n个线段(1<=n<=100000)，后来的如果与前面的相交，就会压住前面的线段，问哪几根线段没有被压着。

（最后没有被压着的线段不超过1000）

## 知识准备

向量的叉乘（矢量积、外积）

有两个自由向量(x1,y1)(x2,y2)

由于是自由向量可以看成是共面的(一般也就用到这样)，于是可以看成(x1,y1,0)(x2,y2,0)，他们的向量积为(0,0,x1*y2-y1*x2)，一般就只用到最后那个,我设为z=x1*y2-y1*x2;其值的大小为以两个向量为邻边作的平行四边形的面积，方向用右手定则判定(也就是值的正负)，好像是手指的卷曲方向为第一个向量转向第二个向量。

判断两条线段是否相交：

第一步：快速矩形排除，以两个向量作两个矩形，如果这两个矩形不相交，那么这两根线段也不可能相交（显然）。但是如果两个矩形相交，两根线段也不一定相交。所以我们还有第二步。

第二步：跨立实验，任取一条线段的其中一端点x，对另一条线段两个端点作出两个向量，分别与x的另一端点作出的向量作积，根据符号可以判断是否位于该线段两侧，如果相同则不跨立，不同则跨立。然后再取另一个线段的端点再做一次跨立实验。如果两次都通过跨立实验，则两根线段相交（不算重合的情况，或刚好擦到的情况）



------------


这道题一开始看着十分难，因为我认为这可能可以用一些数据结构来快速排除一些线段使得时间复杂度优化到O(nlogn)，于是我开始胡思乱想，想到树状数组，线段树，平衡树等操作……

想了一波后我又想起一句话：暴力出奇迹！~~真理啊！~~

然后我又发现题目中有一句话是top sticks不超过1000,显然一根棍子被任一棍子覆盖后就不是top sticks了，所以我们可以用一个双向链表来优化时间。

~~（其实我觉得还是可以出数据卡超时的）~~

最后贴上代码。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef double db;
double a[100100][4];
int n,nex[100100],pre[100100];//nex和pre模拟双向链表
//快速矩阵排除
inline bool fast(db x1,db y1,db x2,db y2,db x3,db y3,db x4,db y4){
	return (max(x1,x2)>=min(x3,x4)&&max(x3,x4)>=min(x1,x2)&&max(y1,y2)>=min(y3,y4)&&max(y3,y4)>=min(y1,y2));
}
//求矢量积
inline db cross_product(db x1,db y1,db x2,db y2){
	return x1*y2-x2*y1;
}
//跨立实验*2
inline bool cross(db x1,db y1,db x2,db y2,db x3,db y3,db x4,db y4){
	db a,b,c,d;
	a=cross_product(x3-x1,y3-y1,x2-x1,y2-y1);
	b=cross_product(x4-x1,y4-y1,x2-x1,y2-y1);
	c=cross_product(x1-x3,y1-y3,x4-x3,y4-y3);
	d=cross_product(x2-x3,y2-y3,x4-x3,y4-y3);
	return (a>0&&b<0||a<0&&b>0)&&(c>0&&d<0||c<0&&d>0);
}
//判断两条线段是否相交
inline bool segmentcross(db x1,db y1,db x2,db y2,db x3,db y3,db x4,db y4){
	if (fast(x1,y1,x2,y2,x3,y3,x4,y4))
		if (cross(x1,y1,x2,y2,x3,y3,x4,y4))
			return 1;
	return 0;
}
int main(){
	scanf("%d",&n);
	while (n!=0){
		nex[n]=n+1;
		pre[1]=0;
		for (int i=1;i<=n;i++){
			nex[i-1]=i;
			pre[i+1]=i;
		}
		for (int i=1,j;i<=n;i++){
			scanf("%lf%lf%lf%lf",&a[i][0],&a[i][1],&a[i][2],&a[i][3]);
			for (j=nex[0];j<i;j=nex[j])
					if (segmentcross(a[i][0],a[i][1],a[i][2],a[i][3],a[j][0],a[j][1],a[j][2],a[j][3])){
						nex[pre[j]]=nex[j];
						pre[nex[j]]=pre[j];
					}
		}
		bool flag=1;
		printf("Top sticks: ");
		int i=nex[0];
		printf("%d",i);
		for (i=nex[i];i<=n;i=nex[i]) printf(", %d",i);
		puts(".");
		scanf("%d",&n);
	}
	return 0;
}
```

---

## 作者：Acestar (赞：2)

>**题意简述：**
>
>输入 $n$ 个棍子，输出最上面的棍子的编号。

**向量叉积：**

![](https://cdn.luogu.com.cn/upload/image_hosting/3hnfjoyd.png)

$\bold{a}×\bold{b}=|\bold{a}|*|\bold{b}|*\sin\theta=S_{ABCO}=x1*y2-x2*y1$

![](https://cdn.luogu.com.cn/upload/image_hosting/wvsxncjw.png)

对于本题，首先我们要判断线段 $l1$ 和 $l2$ 所在的直线是否有交点。

代码如下（不懂的话可以自己手画一下）：

```cpp
max(l1.s.x,l1.e.x)>=min(l2.s.x,l2.e.x)&&max(l1.s.y,l1.e.y)>=min(l2.s.y,l2.e.y)//l1的端点在l2的两侧。
max(l2.s.x,l2.e.x)>=min(l1.s.x,l1.e.x)&&max(l2.s.y,l2.e.y)>=min(l1.s.y,l1.e.y)//l2的端点在l1的两侧。
```

然后，我们只需要用**右手定则**（右手定则：如果 $\bold{a}$ 在 $\bold{b}$ 的顺时针方向，那么 $\bold{a}×\bold{b}=1$，否则 $=0$。）来判断的线段 $l1$ 和 $l2$ 的两个端点是否在另一条线段的两侧，这样就可以保证线段 $l1$ 和 $l2$ 有交点了。

如图，我们可以判断 $sgn((l1.s,l2.s)×(l1.s,l1.e))*sgn((l1.s,l2.e)×(l1.s,l1.e))≤0\&\&sgn((12.e,l1.s)×(l2.e,l2.s))*sgn((l2.e,l1.e)×(l2.e,l2.s))≤0$。

$(l1.s,l2.s)$ 表示向量 $l1.s$ 到 $l2.s$。

我们可以重载 "$-$"，使 $l2.s-l1.s$ 表示 $(l1.s,l2.s)$。

$sgn(x)$ 返回 $x$ 的正负性。

$sgn(x)=
\begin{cases}
1& \text{x>0}\\
0& \text{x=0}\\
-1& \text{x<0}
\end{cases}$

最后，我们发现答案不超过 $1000$，所以直接暴力判断每个棍子即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define N 100010
#define eps 1e-8
#define pi acos(-1.0) 

using namespace std;

int sgn(double x)
{
	if(fabs(x)<eps) return 0;
	if(x>0) return 1;
	else return -1;
}

struct point
{
	double x,y;
	point(){}
	point(double _x,double _y)
	{
		x=_x,y=_y;
	}
	point operator - (const point &b) const	//向量(b.x,b.y)->(x,y)
	{
		return point(x-b.x,y-b.y);
	}
	double operator ^ (const point &b) const//(x,y)×(b.x,b.y) 
	{
		return x*b.y-y*b.x;
	}
	double operator * (const point &b) const//(x,y)*(b.x,b.y)
	{
		return x*b.x+y*b.y;
	}
};

struct Line
{
	point s,e;//两个端点 
	Line(){}
	Line(point _s,point _e)
	{
		s=_s,e=_e;
	}
};

bool inter(Line l1,Line l2)	//判断l1,l2是否有交点 
{
	return max(l1.s.x,l1.e.x)>=min(l2.s.x,l2.e.x)&&max(l1.s.y,l1.e.y)>=min(l2.s.y,l2.e.y)&&
		   max(l2.s.x,l2.e.x)>=min(l1.s.x,l1.e.x)&&max(l2.s.y,l2.e.y)>=min(l1.s.y,l1.e.y)&&
		   sgn((l2.e-l1.s)^(l1.e-l1.s))*sgn((l2.s-l1.s)^(l1.e-l1.s))<=0&&
		   sgn((l1.s-l2.e)^(l2.s-l2.e))*sgn((l1.e-l2.e)^(l2.s-l2.e))<=0;
}

Line line[N];
int flag[N];

int main()
{
	int n;
	while(scanf("%d",&n)!=EOF)
	{
		if(!n) break;
		double x1,y1,x2,y2;
		for(int i=1; i<=n; i++)
		{
			scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
			line[i]=Line(point(x1,y1),point(x2,y2));
			flag[i]=true;
		}
		for(int i=1; i<=n; i++)
			for(int j=i+1; j<=n; j++)
				if(inter(line[i],line[j]))
				{
					flag[i]=false;
					break;
				}
		printf("Top sticks: ");
		bool first=true;
		for(int i=1; i<=n; i++)
		{
			if(flag[i])
			{
				if(first) first=false;
				else printf(", ");
				printf("%d",i);
			}
		}
		printf(".\n");
	}
	return 0;
}
```


---

## 作者：bloodstalk (赞：0)

## Description
按顺序给出 $n$ 个棍子两个端点的坐标。如果后来的棍子与前边的棍子相交，则说后面的把前面的挡住了。问最后有多少个棍子没被挡住。

$n\leq 10^5$，且**答案不超过 $1000$**。

## Solution
叉积基本运用。

1. 定义：$\overrightarrow{a} \times \overrightarrow{b} = |\overrightarrow{a}||\overrightarrow{b}|\sin \theta$。

2. 几何意义：向量 $\overrightarrow{a}$ 与向量 $\overrightarrow{b}$ 张成的平行四边形的**有向面积**。$\overrightarrow{b}$ 在 $\overrightarrow{a}$ 的**逆时针**方向为**正**，**顺时针**方向为**负**。

3. **坐标运算**：$\overrightarrow{a} \times \overrightarrow{b}=x_1y_2 - y_1x_2$。

4. 应用：

(1)：判定**点线**的位置关系

$(\overrightarrow{b}-\overrightarrow{a}) \times (\overrightarrow{c}- \overrightarrow{a}) > 0 \Rightarrow c$ 点在直线 $ab$ 的左侧；
    
$(\overrightarrow{b}-\overrightarrow{a}) \times (\overrightarrow{c}- \overrightarrow{a}) < 0 \Rightarrow c$ 点在直线 $ab$ 的右侧；
   
$(\overrightarrow{b}-\overrightarrow{a}) \times (\overrightarrow{c}- \overrightarrow{a}) = 0 \Rightarrow $ 三点共线。
   
```cpp
il double operator *(Point a,Point b) { return a.x*b.y - a.y*b.x; }//叉积

il double cross(Point a,Point b,Point c) { return (b-a)*(c-a); }//判断c和直线ab的关系
```

(2)：判定**线线**之间的位置关系

①`cross(a,b,c) * cross(a,b,d) > 0` $\Rightarrow$ 直线 $ab$ 与 线段 $cd$ 无交点。

②`cross(a,b,c) * cross(a,b,d) <= 0` $\Rightarrow$ 直线 $ab$ 与 线段 $cd$ 有交点。

$= 0$ 的情况就是端点 $c$ 或 $d$ 在直线 $ab$ 上。

③线段相交

$\text{Part 1}$：判断必不可交的情况

```cpp
//如果四条判断有一个为真，则代表两线段必不可交，否则应该进行第二步判断。
max(c.x,d.x)<min(a.x,b.x) || max(c.y,d.y)<min(a.y,b.y) || max(a.x,b.x)<min(c.x,d.x) || max(a.y,b.y)<min(c.y,d.y)
```

$\text{Part 2}$: 利用叉积求交

Ⅰ.`cross(a,b,c) * cross(a,b,d) > 0` **或** `cross(c,d,a) * cross(c,d,b) > 0` $\Rightarrow$ 线段 $ab$ 与线段 $cd$ 无交点。

Ⅱ.`cross(a,b,c) * cross(a,b,d) <= 0` **且** `cross(c,d,a) * cross(c,d,b) <= 0` $\Rightarrow$ 线段 $ab$ 与线段 $cd$ 有交点。

注意有交的时候必须两个条件都满足，这样就排除了一个线段在另一个线段的直线上但是不在线段上的情况。如果不理解可以自己推一推。

由于答案不会超过 $1000$ ，玄学复杂度暴力 $O(n^2)$ 就能通过。

## Code
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
//#define int long long
#define ll long long
#define y1 y11
#define re register
#define il inline
const int N = 1e5 + 5;
using namespace std;

struct Point{
	double x,y;
}a[N],b[N];
int n,m,ans[N],cnt;
bool flag = 1;

il int read()
{
	int f=0,s=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f |= (ch=='-');
	for(; isdigit(ch);ch=getchar()) s = (s<<1) + (s<<3) + (ch^48);
	return f ? -s : s;
}

Point operator +(Point a,Point b) { return Point{a.x+b.x,a.y+b.y}; }//加

Point operator -(Point a,Point b) { return Point{a.x-b.x,a.y-b.y}; }//减

il double operator *(Point a,Point b) { return a.x*b.y - a.y*b.x; }//叉积

il double operator &(Point a,Point b) { return a.x*b.x + a.y*b.y; }//点积

il double cross(Point a,Point b,Point c) { return (b-a)*(c-a); }//判断c和直线ab的关系 

il double len(Point a) { return sqrt(a&a); }

il double dis(Point a,Point b) { return len(b-a); }

il bool Intersect(int i,int j)
{
	return (cross(a[i],b[i],a[j])*cross(a[i],b[i],b[j]) <= 0) && (cross(a[j],b[j],a[i])*cross(a[j],b[j],b[i]) <= 0);
}

il void Main()
{
	n = read();
	if(!n) exit(0);
	cnt = 0;
	for(re int i=1;i<=n;i++) scanf("%lf%lf%lf%lf",&a[i].x,&a[i].y,&b[i].x,&b[i].y);
	for(re int i=1;i<=n;i++)
	{
		flag = 1;
		for(re int j=i+1;j<=n;j++)
			if(Intersect(i,j)) { flag = 0; break; }
		if(flag) ans[++cnt] = i;
	}
	printf("Top sticks:");
	for(re int i=1;i<cnt;i++) printf(" %d,",ans[i]);
	printf(" %d.\n",ans[cnt]);
}

signed main()
{
	while(1) Main();
	return 0;
}
```

---

