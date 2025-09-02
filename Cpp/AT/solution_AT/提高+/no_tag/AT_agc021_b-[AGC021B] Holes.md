# [AGC021B] Holes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc021/tasks/agc021_b

平面上に $ N $ 個の穴があります。$ i $ 個目の穴の座標は、$ (x_i,y_i) $ です。

$ R=10^{10^{10^{10}}} $ とします。りんごさんは、以下の操作を行います。

- 原点を中心とする半径 $ R $ の円内から無作為に $ 1 $ 点を選び、すぬけ君を置く。すぬけ君は、置かれた点からユークリッド距離が最も近い穴に移動し、落ちる。そのような穴が複数ある場合は、添え字の最も小さいものを選ぶ。

全ての $ 1\leq\ i\leq\ N $ に対し、すぬけ君が $ i $ 番目の穴に落ちる確率を求めてください。

ただし、半径 $ R $ の円内から無作為に $ 1 $ 点を選ぶ操作とは、以下の操作を指します。

- $ [-R,R] $ 上の独立な一様分布にしたがって実数 $ x,y $ を選ぶ。
- もし$ x^2+y^2\leq\ R^2 $ なら、座標 $ (x,y) $ を選ぶ。そうでないなら、その条件が満たされるまで実数 $ x,y $ を選びなおし続ける。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 100 $
- $ |x_i|,|y_i|\ \leq\ 10^6(1\leq\ i\leq\ N) $
- 与えられる点は全て相異なる
- 入力はすべて整数である

### Sample Explanation 1

りんごさんが $ x+y\leq\ 1 $ なる領域にすぬけ君を置いた場合、すぬけ君は $ 1 $ 番目の穴に落ちます。このような確率は $ 0.5 $ に非常に近いです。 また、そうでない場合すぬけ君は $ 2 $ 番目の穴に落ち、そのような確率も $ 0.5 $ に非常に近いです。

## 样例 #1

### 输入

```
2
0 0
1 1```

### 输出

```
0.5
0.5```

## 样例 #2

### 输入

```
5
0 0
2 8
4 5
2 6
3 10```

### 输出

```
0.43160120892732328768
0.03480224363653196956
0.13880483535586193855
0.00000000000000000000
0.39479171208028279727```

# 题解

## 作者：LittleMoMol (赞：6)

## 前言

学校基础模拟赛的题，当时有思路但是不太会写凸包就没做，下来看了看，自己的思路大部分是正确的，有些细节没有想到，在此写篇题解。

我用的是 Andrew 求凸包。

[欢迎博客阅读！](https://www.cnblogs.com/LittleMoMol-kawayi/p/solution_LuoGu_AT_agc021_b.html)

## 思路

### 答案为 0 的点

题目说：坐标系半径 $R=10^{10^{10^{10}}}$，你可以感受一下这个数字的大小，这个数字比 $10^6$ 要大得多得多！根本不在一个数量级上！如果我们把题目中的所有点的**凸包**求出来，那么随机出来的点在这个凸包里面的概率非常非常小，小到在精确度 $10^{-5}$ 的要求上**可以忽略**。

这样就可以得到很重要的一个结论：**对于不在凸包上的所有点，它们的答案为 0** 

### 凸包上的点

考虑凸包上的点的答案怎么求。到点的距离这个东西，初中数学书上有一条重要的定理：**一个线段的中垂线上的点到这个线段的两个端点的距离相等**。那对于一个点，如何求凸包上的那个点离它最近呢？不太好求，换一种思路，能不能求出：对于凸包上的每个点 $A_i$，求出与之对应的**极大**的一个区域，使得这个区域上的**所有点**离点 $A_i$ 的距离是最近的，且不在这个区域上的**所有点**离点 $A_i$ 的距离不是最近的。先上图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2a5hc31h.png)

两条粉色的线分别为线段 $AB,BC$ 的中垂线，那么能够直观感受到蓝色框框就是所求的**极大的区域**，这个区域里的所有点离点 $B$ 是最近的。至于为什么不加凸包里面的部分，其实加和不加都一样，这么一点点面积，怎么能够和我 $R=10^{10^{10^{10}}}$ 的坐标系相比较呢？根本不会影响答案。

那么点 $B$ 的答案是多少呢？比较显然，就是两个中垂线所成夹角再除以 $360^\circ$，中垂线夹角也就是图中灰色的角。

### 怎么方便地求角度

你直接硬算肯定没问题，但是有更简单的方法，还拿上图举例子，如果我们能求出 $\angle ABC$ 的大小，那么所求的灰色角的角度就是 $180^\circ - \angle ABC$，那么考虑如何求 $\angle ABC$ 

高中数学书上有一条重要的定理“余弦定理”：在 $\triangle ABC$，$\cos C = \dfrac{a^2+b^2-c^2}{2ab}$，其中线段 $a,b,c$ 分别为角 $A,B,C$ 对着的边，即：$a=BC,b=AC,c=AB$。

那么要求出 $\angle ABC$，我们可以先求出 $\cos \angle ABC$，再用反三角函数即可求出 $\angle ABC$

在这个图中 $\cos \angle ABC = \dfrac{AB^2+BC^2-AC^2}{2 \cdot AB \cdot BC}$，而点 $A,B,C$ 的坐标都是已知的，那么很容易就能求出来，不赘述了。

## 细节问题

首先考虑如果一些点共线了该怎么办？如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7fjyph4g.png)

你还是每两个相邻点作中垂线，然后划分区域，得到下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2lc0smu3.png)

不用我多说，聪明的你一定能够知道每个区域是对应哪个点的，那么你考虑 $C,D,E,F,G$ 这个五个点的答案分别是多少，答案：除了最左边的点 $C$ 和最右边的点 $G$ 的答案为 $0.5$，其他点的答案均为 $0$ 

为什么？虽然说 $D,E,F$ 这三个点的区域也是无限向外延申的，但是他们可以形象地理解为“一维延伸”，确实，**与直线垂直的方向上是无限延伸的，但是直线方向的长度是固定的**；而对于 $C,G$ 两点，他们可以形象地理解为“二维延伸”，**与直线垂直的方向上是无限延伸的，直线方向上也是无限延伸的**。还是那句话：“一维延伸”的区域怎么能够和我 $R=10^{10^{10^{10}}}$ 的坐标系相比较呢？根本不会影响答案！

这说明求凸包时，要把共线的点当作**不在凸包上**，否则答案会错。

还有就是，如果只有一个点，那么直接输出 1 即可，这个很好理解。

## Code

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#define x first
#define y second

using namespace std;

typedef pair<double, double> PDD;
const int N = 210;
const double pi = acos(-1), pi_2 = 2 * acos(-1);

int n;
int top, stk[N];
struct warma
{
    PDD q;
    int id;
} poi[N];
double ans[N];

bool cmp(warma a, warma b)
{
    return a.q < b.q;
}

double get_dist(PDD a, PDD b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double cross(PDD a, PDD b)
{
    return a.x * b.y - a.y * b.x;
}

double area(PDD a, PDD b, PDD c)
{
    PDD ab = (PDD){b.x - a.x, b.y - a.y};
    PDD ac = (PDD){c.x - a.x, c.y - a.y};
    return cross(ab, ac);
}

void andrew()
{
    sort(poi + 1, poi + 1 + n, cmp);
    top = 0;
    for (int i = 1; i <= n; i ++ )
    {
        while (top >= 2 && area(poi[stk[top - 1]].q, poi[stk[top]].q, poi[i].q) < 0) top -- ;
        stk[ ++ top] = i;
    }
    for (int i = n - 1; i >= 1; i -- )
    {
        while (top >= 2 && area(poi[stk[top - 1]].q, poi[stk[top]].q, poi[i].q) < 0) top -- ;
        stk[ ++ top] = i;
    }
    top -- ;
    stk[0] = stk[top], stk[top + 1] = stk[1]; //这么做为了防止越界，把它变成一个“环”
    return;
}


int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    cin >> n;
    if (n == 1)
    {
        printf("1\n");
        return 0;
    }
    for (int i = 1; i <= n; i ++ ) cin >> poi[i].q.x >> poi[i].q.y, poi[i].id = i;
    andrew();
    //以上是求凸包
    for (int i = 1; i <= top; i ++ )
    {
        double a = get_dist(poi[stk[i - 1]].q, poi[stk[i]].q);
        double b = get_dist(poi[stk[i]].q, poi[stk[i + 1]].q);
        double c = get_dist(poi[stk[i - 1]].q, poi[stk[i + 1]].q);
        double angle = pi - acos((a * a + b * b - c * c) / (2 * a * b)); //余弦定理
        ans[poi[stk[i]].id] = angle / pi_2;
    }
    for (int i = 1; i <= n; i ++ ) printf("%.10lf\n", ans[i]);
    return 0;
}
```

## 尾声

细节真是太多了，写这篇题解花了大概俩小时吧，还是有一些收获！还有 16 天左右就要 NOIP 了，准备退役啦！完结撒花！

---

## 作者：听取MLE声一片 (赞：3)

首先题目可以看成无限的平面。

有一个知识，就是有限的面积在无限的平面里面取到的概率为 $0$。

什么情况一个点占据的面积是有限的呢？不难看出被三角形包进去的点占据的面积一定是有限的。然后这个用极角排序做就行了，如果按照三角形面积写会出现一些玄学问题，就别这样写了。

处理完 $0$ 的点，剩下的点显然是一个凸包（虽然没啥用）。因为有限的面积可以忽略，我们只需要考虑最关键的两条线围成的角度即可。到一个点的距离首先想到中垂线，这个点和所有点连成线段的中垂线就是划出的所有范围，又因为要到这个点距离最短，那就是取两两夹角中最小的一个就行了。求出一个角再求出占整个圆的比例即可。

---

## 作者：Zesty_Fox (赞：2)

也许更好的阅读体验：[cnblogs](https://www.cnblogs.com/acceptedzhs/p/agc021b-sol.html)

不难发现其实就是在平面上随机取点。

首先要判断一个点被取到的概率是否为 $0$。设这个点为 $A$，显然，所有除 $A$ 以外的点都要在 $A$ 点同侧。枚举其周围 $3$ 个点 $B,C,D$，如果 $A$ 点在 $\triangle BCD$ 内部，则 $A$ 被取到的概率为 $0$。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/n8dcsft8.png)

（能取到 $A$ 点的区域，即红色区域，面积是有限的，在无限的平面上随机取点，落到红色区域的概率为 $0$）

然后考虑怎么算概率。不难发现，我们只需将 $A$ 点与周围点连边，取所有边的中垂线，计算中垂线形成的的最小夹角即可。答案即为 $\frac{\text{最小夹角}}{2\pi}$。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/wtjblsk1.png)

（最小夹角为 $\alpha$，即为 $\angle BAE$ 的补角）

只要极角排序或枚举两个点即可。

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

template<typename T>
inline T read(){
    T x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

#define rdi read<int>
#define rdll read<ll>
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N=110;
const double pi=acos(-1);

int n;
pii p[N];
double deg[N][N],res[N];

int main(){
    n=rdi();
    for(int i=1;i<=n;i++) p[i].fi=rdi(),p[i].se=rdi();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i!=j) deg[i][j]=atan2(p[j].se-p[i].se,p[j].fi-p[i].fi);
    for(int i=1;i<=n;i++){
        bool flg=0;
        for(int i1=1;i1<=n;i1++){
            for(int i2=i1+1;i2<=n;i2++){
                for(int i3=i2+1;i3<=n;i3++){
                    if(i1==i||i2==i||i3==i) continue;
                    double d[3]={deg[i][i1],deg[i][i2],deg[i][i3]};sort(d,d+3);
                    if(d[2]-d[0]>=pi&&d[2]-d[1]<pi&&d[1]-d[0]<pi) {flg=1;goto ed;}
                }
            }
        }
        ed:
        if(flg) continue;
        double ang=pi;
        for(int i1=1;i1<=n;i1++){
            for(int i2=i1+1;i2<=n;i2++){
                if(i1==i||i2==i) continue;
                double tmp=fabs(deg[i][i1]-deg[i][i2]);
                if(tmp>=pi) tmp=2*pi-tmp;
                ang=min(ang,pi-tmp);
            }
        }
        res[i]=ang/(2*pi);
    }
    for(int i=1;i<=n;i++) printf("%.6lf\n",res[i]);
    return 0;
}

```


---

## 作者：wmy_goes_to_thu (赞：1)

这个 $R$ 很大，其实就是告诉我们这是一个平面（在允许误差之内）。

然后你会发现，只要有一个指标（长度）是有限的，那么占比就是 $0$。

所以只需要维护一个凸包，因为凸包内部的点的答案是 $0$，如果有 $m$ 点共线那么中间那些点的答案也是 $0$。所以维护的凸包不能有共线的情况。凸包咋维护都行，我这里采用 Graham 算法。

然后 $n=1$ 特判一下，否则可能就输出 `nan` 了。

代码也很简洁：

```cpp
#include<bits/stdc++.h>
using namespace std;
double pi=acos(-1),pi_2=2*acos(-1),as[105];
struct apple
{
	int x,y,wz;
	double ar;
	bool operator<(const apple &other)const
	{
		return ar<other.ar;
	}
}e[105];
int q[105];
long long chaji(int a,int b,int c)
{
	return 1ll*(e[a].x-e[b].x)*(e[b].y-e[c].y)-1ll*(e[b].x-e[c].x)*(e[a].y-e[b].y);
}
double dist(int a,int b)
{
	return sqrt(1ll*(e[a].x-e[b].x)*(e[a].x-e[b].x)+1ll*(e[a].y-e[b].y)*(e[a].y-e[b].y));
}
int main()
{
	int n,x0=INT_MAX,y0=INT_MAX,w;
	cin>>n;
	if(n==1)
	{
		cout<<1<<endl;
		return 0;
	}
	map<pair<int,int>,int>mp;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&e[i].x,&e[i].y);
		e[i].wz=i;
		if(y0>e[i].y||y0==e[i].y&&x0>e[i].x)y0=e[i].y,x0=e[i].x,w=i;
	}
	for(int i=1;i<=n;i++)if(i!=w)e[i].x-=e[w].x,e[i].y-=e[w].y;
	e[w].x=e[w].y=0;
	e[w].ar=-1;
	for(int i=1;i<=n;i++)if(i!=w)
	{
		e[i].ar=atan(1.0*e[i].y/e[i].x);
		if(e[i].ar<0)e[i].ar=pi+e[i].ar;
	}
	sort(e+1,e+n+1);
	int r=0;
	q[++r]=1;
	for(int i=2;i<=n;i++)
	{
		int flag=1;
		while(r>=2)
		{
			long long dd=chaji(q[r-1],q[r],i);
			if(dd>0)break;
			if(dd==0&&fabs(dist(q[r-1],q[r])+dist(q[r],i)-dist(q[r-1],i))>1e-8)
			{
				flag=0;
				break;
			}
			r--;
		}
		if(flag)q[++r]=i;
	}
	q[0]=q[r],q[r+1]=q[1];
	for(int i=1;i<=r;i++)
	{
		double a=dist(q[i-1],q[i]),b=dist(q[i],q[i+1]),c=dist(q[i-1],q[i+1]);
		as[e[q[i]].wz]=(pi-acos((a*a+b*b-c*c)/(2*a*b)))/pi_2;
	}
	for(int i=1;i<=n;i++)printf("%.10f\n",as[i]);
	return 0;
}
```

---

## 作者：AC_love (赞：0)

首先：能走到每个点的所有点对应的一定是平面上的一个块。

我们知道：在一个无限大的平面上随机选点，选择的点在一块有限的面积里的概率是 $0$。

因此，如果某个点对应的块是一个有面积的多边形，那么这个点一定不可能被走到。

把所有不可能的点都删光，剩下的应该是一个凸包。

所以我们不需要考虑删除哪些点了，直接求一个凸包就行，只有最后留在凸包上的点才是没被删除的。

对于凸包上的每个点，当我们选择的点位于其相邻的两条边的两条中垂线的夹角内部时，这个点会被选到。

而所有夹角的和是 $360 \degree$，因此我们直接用夹角度数除以 $360 \degree$ 即可。

这个夹角的求法可以使用余弦定理，先求出对角的 $\cos$ 值，然后利用反三角函数求出对角的角度，然后这个夹角就是 $180 \degree$ 减去对角角度。

[code](https://atcoder.jp/contests/agc021/submissions/59545151)

---

## 作者：NATO (赞：0)

计算几何题。

首先，题目中的 $R$ 范围太大，与给出点的范围相比可以视为正无穷（即有限的空间对答案没有影响）。

我们考虑每个点集凸包上的点对一个在点集凸包内的点的限制，我们考虑三角形的情况（剩余情况的限制显然比三角形更严格）：

![](https://cdn.luogu.com.cn/upload/image_hosting/tighvlly.png)

我们通过将三角形的顶点与三角形内的点一一连线，作它们的垂直平分线，由于顶点与三角形内的点连线必然不平行，所以它们必有交点，故它们将三角形内的点的可行区域限制在了一个有限空间内（如上图红色部分所示，$\Delta ABC$ 中的点 $D$ 的可行区域被限制在了一个有限空间内），即答案为 $0$。

更多边的凸多边形均可以拆成多个三角形来看，故限制只会更严格。

因此，我们发现只有在点集凸包上的点答案才可能不为 $0$。

那么，凸包上的点的答案是什么呢？

我们将这个平面想象成一个无限大的圆，那么答案就是 $\frac{\theta}{2\pi}$，其中 $\theta$ 为凸包上的点“分走的”圆心角弧度。

我们先跑一遍任意一个求凸包的算法求出凸包上的点，同样考虑作垂直平分线来考虑凸包上的点对一个点的影响。

我们可以发现由相邻边引出的垂直平分线对一个点的限制最严格，此时该点所对圆心角弧度为 $\pi-\alpha$，其中 $\alpha$ 为该点作为顶点的凸包内角的弧度，答案即为 $\frac{\pi-\alpha}{2\pi}$。

那么 $\alpha$ 如何计算呢？

拆成以该点为原点的平面直角坐标系中凸包相邻点与该点连线和 $x$ 正半轴所夹角之差即可。

最后，我们来考虑三点共线的情况。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/kz89cnzw.png)

$B$ 点的可行区域为中间部分，大小也是无限的，那么答案是多少呢？

考虑 $A,C$ 点可行区域均为 $\infty^2$，而 $B$ 点可行区域为 $\infty$，它们的阶不同，且 $A,C$ 的阶更大，所以 $B$ 点答案实际上是 $0$。

求凸包时将其不纳入凸包即可。

细节可查看代码。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 214748364719260817ll
#define ll long long 
#define db double
using namespace std;
const db pi=atan2(0,-1);
ll n;
ll sx=INF,sy=INF;
ll st[105],r=1;
struct px
{
	ll x,y,uid;
	bool operator<(const px&b)const
	{
		return (atan2(y-sy,x-sx)!=atan2(b.y-sy,b.x-sx))?(atan2(y-sy,x-sx)<atan2(b.y-sy,b.x-sx)):(sqrt((x-sx)*(x-sx)+(y-sy)*(y-sy))<sqrt((b.x-sx)*(b.x-sx)+(b.y-sy)*(b.y-sy)));
	}
	px operator-(const px&b)const
	{
		return (px){x-b.x,y-b.y};
	}
	ll operator*(const px&b)const
	{
		return x*b.y-y*b.x;
	}
}a[105];
ll point(px a,px b)
{
	return a.x*b.x+a.y*b.y;
}
db jl(px a,px b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
bool vis[105];
db ans[105];
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(ll i=1;i<=n;++i)
	{
		cin>>a[i].x>>a[i].y;a[i].uid=i;
		if(a[i].y<sy)
			sy=a[i].y,sx=a[i].x;
		else if(a[i].y==sy)
			sx=min(sx,a[i].x);
	}
	a[0].x=sx;a[0].y=sy;
	sort(a+1,a+1+n);
	st[r]=0;
	for(ll i=1;i<=n;++i)
	{
		if(a[i].x==sx&&a[i].y==sy)
		{
		vis[i]=1;st[1]=i;continue;	
		}
		while(r>=2)
		{
			if((a[st[r-1]]-a[st[r]])*(a[i]-a[st[r]])>=0)vis[st[r--]]=0;
			else break;
		}
		vis[st[++r]=i]=1;
	}
	st[r+1]=st[1];st[0]=st[r];
	for(ll i=1;i<=r;++i)
	{
		ans[a[st[i]].uid]=(atan2(1.00*(a[st[i+1]]-a[st[i]]).y,1.00*(a[st[i+1]]-a[st[i]]).x)-atan2((a[st[i]]-a[st[i-1]]).y*1.00,1.00*(a[st[i]]-a[st[i-1]]).x))*1.00/(pi*2.00);	
		if(ans[a[st[i]].uid]<0)ans[a[st[i]].uid]=1.000+ans[a[st[i]].uid];//可能我们在某个位置凸包方向改变，答案与之前相反。
	}
	for(ll i=1;i<=n;++i)cout<<fixed<<setprecision(10)<<ans[i]<<'\n';
}
```


---

