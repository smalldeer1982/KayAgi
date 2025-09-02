# Cannon

## 题目描述

**题目大意：**

有一门大炮，坐标在$(0,0)$，和$m$堵墙，现在大炮要射$n$发炮弹，每发炮弹的初始速度$v$是一样的，射击角度为$α(0<α<π/4)$，假设射击后经过时间$t$，重力加速度$g=9.8$，则有：

$v_x(t)=v*cos(α)$

$v_y(t)=v*sin(α)-g*t$

$x(t)=v_x(t)*t$

$y(t)=v*sin(α)*t-g*t^2/2$

给定$m$堵墙墙顶坐标$(x_i,y_i)$，墙垂直于$x$坐标轴，炮弹如果打到墙上，就会卡住；如果掉到地上，也不会再滚动。

求这$n$发炮弹最终的位置

## 样例 #1

### 输入

```
2 10
0.7853
0.3
3
5.0 5.0
4.0 2.4
6.0 1.9
```

### 输出

```
5.000000000 2.549499369
4.000000000 0.378324889
```

## 样例 #2

### 输入

```
2 10
0.7853
0.3
2
4.0 2.4
6.0 1.9
```

### 输出

```
10.204081436 0.000000000
4.000000000 0.378324889
```

# 题解

## 作者：Ave_1_Oblivionis (赞：1)

## 原题

[CF47E Cannon](https://www.luogu.com.cn/problem/CF47E)

---

## 思路概述

### 题意分析

给定 $n$ 个起点坐标 $(0,0)$ 速度大小同为 $v$ ，抛射角分别为 $\alpha_1,\alpha_2...\alpha_n$ 的炮弹初速度；再给定 $m$ 面顶端坐标为 $(x_1,y_1),(x_2,y_2)...(x_m,y_m)$ 的墙壁，求每颗炮弹的最终落点（不考虑滑落和滚动）。

### 思路分析

一眼物理题，套斜抛运动公式即可。但是 $1≤n≤10^4,1≤m≤10^5$ 的数据使得对每一颗炮弹枚举所有墙壁的算法不可能在时限内跑完，所以考虑贪心。

---

## 算法实现

### 关于斜抛运动公式

由高中物理必修二第一章的物理知识不难推导出斜抛运动的射程、射高公式。由于本题只要求求解最终落点而非某一时刻炮弹位置，所以我们采用斜抛运动的轨迹方程。

速度的分解不解释，直接套公式即可：

$$v_x=v\cos\alpha,v_y=v\sin\alpha$$

首先考虑一种特殊情况：炮弹没有碰到墙壁或已经越过所有墙壁。这时炮弹的最终坐标即为其最远射程与地面形成的点，即 $(x_{max},0)$ 。由相关物理常识可以得出（重力加速度 $g$ 根据题目要求取 $9.8m/s^2$ ，下文同理）： 

$$x_{max}=v_x\frac{2v_y}{g}$$

对于给定水平位移求竖直高度的问题，回到运动学公式本身即可推导：

$$x=v_xt,y=v_yt-\frac{1}{2}gt^2$$
$$t=\frac{x}{v_x}$$
$$y=\frac{v_yx}{v_x}-\frac{gx^2}{2v_x^2}$$

### 关于排序和贪心

如前文所述，由于本题数据规模的原因，所以不可能用 $O(nm)$ 的时间复杂度来对每颗炮弹分别枚举所有墙壁，故考虑排序后的贪心策略。

阅读题目时，不难注意到，所有同炮弹的抛射角都满足 $\alpha_i∈(0,\frac{\pi}{4}]$ 。又根据物理常识可知，这个范围内抛射物在任意时间点的高度都是随抛射角递增的。所以得出结论：在本题抛射角要求范围内，抛射角越大，更有可能越过更多的墙壁。因此，我们先将给定的速度分解后，按抛射角从小到大排序。

### 贪心算法和双指针

将墙壁按横坐标排序，原因不再冗述。

由上文所得结论，不难得知：在按抛射角递增的顺序给所有炮弹排序后，以当前炮弹的速度 $v_i(1≤i≤n)$ 可以越过的墙壁（设其集合为 $W_i$），其后抛射角更大的炮弹一定能越过，即 $W_i⊆W_j(i<j)$ 。

根据上述结论，就可以形成本题的算法流程：首先用变量 $i$ 枚举炮弹，然后用 $j(r_{i-1}≤j≤m)$ 枚举墙壁（此处 $r_i$ 表示第 $i$ 颗炮弹能越过的最远的墙壁下标），并使用上文提到的轨迹方程计算坐标即可。

### 一些注意事项

由于在最开始的预处理中需要将炮弹按抛射角大小排序，而本题又采用的是离线查询，所以需要在读入数据时给每颗炮弹编号，计算出坐标后再将结果映射回原下标。

---

## AC code
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<set>
#include<ctime>
#define RI register int
#define RD register double
#define RN register point
using namespace std;
const int maxn=1e5+10;
const double g=9.8000000000,pi=3.1415926535,eps=1e-10;
typedef struct velocity
{
	double s,agl;
	double x,y,d;
	int ord;
	inline void divide(void)
	{
		x=s*cos(agl);y=s*sin(agl);/*分解速度*/
		d=x*2*y/g;/*最大射程*/ 
		return;
	}
	inline bool operator <(const velocity &x)const
	{
		return x.agl>agl;
	}
};
typedef struct wall
{
	double x,y;
	inline bool operator <(const wall &X)const
	{
		return X.x>x;
	}
};
velocity v[maxn];
wall w[maxn],ans[maxn];/*由于需要对速度按抛射角排序后进行离线查询 所以此处用结构体数组存储答案*/
int n,m;
double vel;/*速度大小*/
inline double calc(velocity a,double x);/*通过斜抛运动轨迹方程计算高度*/
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);
	cin >> n >> vel;
	for(RI i=1;i<=n;++i)
	{
		v[i].s=vel;cin >> v[i].agl;
		v[i].divide();v[i].ord=i;
	}
	sort(v+1,v+n+1);
	cin >> m;
	for(RI i=1;i<=m;++i) cin >> w[i].x >> w[i].y;
	sort(w+1,w+m+1);
	for(RI pv=1,pw=1/*pv为速度指针 pw为墙壁指针*/;pv<=n;++pv)
		if(w[pw].x>v[pv].d) ans[v[pv].ord]=(wall){v[pv].d,0};/*墙壁横坐标已经大于最大射程*/
		else
		{
			while(w[pw].y<calc(v[pv],w[pw].x) && pw<=m) ++pw;/*当前墙壁无法挡住炮弹 墙壁指针后移*/
			if(pw<=m) ans[v[pv].ord]=(wall){w[pw].x,calc(v[pv],w[pw].x)};/*炮弹落在墙壁上*/
			else ans[v[pv].ord]=(wall){v[pv].d,0};/*炮弹越过所有墙壁落在空地上*/
		}
	for(RI i=1;i<=n;++i) printf("%.9lf %.9lf\n",ans[i].x,ans[i].y);	
	return 0;
}
inline double calc(velocity a,double x)
{
	return a.y*(x/a.x)-0.5*g*(x/a.x)*(x/a.x);/*斜抛轨迹方程 详见题解*/
}
```



---

## 作者：Yuby (赞：1)

[题面传送](https://www.luogu.com.cn/problem/CF47E)

点数：2200

#### 分析

注意到 $v$ 的范围很小，但是。。。。。有用吗？

这时注意到 $n^2$ 并不会超时，所以在这个思路上卡了感觉一年。。。

排除 $n^2$ 之后就注意到 $ \alpha \le 45^\circ$ 我们要注意下面的公式。

简单推导一下得到没墙时： $t = 2v/g$，这时能飞 $\frac{v^2\sin 2\alpha_i}{g}$。

因为 $y= \sin x$ 在当前范围内单调递增，那么又由于这个运动是平滑的抛物线（不会证明，扯淡两句

所以说角度越大飞的越远。

于是，第一步，把这些角度排序，理所应当的也把所有墙按照横坐标排序。

``` cpp
const db G=9.8;const ll MAXN=1e5+7;
ll n,m,v;
struct node
{
	db x,y;
	bool operator<(const node& xx)
	{
		return x<xx.x;
	}
}a[MAXN];
struct Node
{
	db alpha,r;
	ll id;
	bool operator<(const Node& xx)
	{
		return alpha<xx.alpha;
	}
}b[MAXN];
db r[MAXN],ans[MAXN],ans1[MAXN];
map<ll,ll>mp;
```



定义也在上面。

那么从上面的结论继续下去，如果这一发炮弹能被前面的墙挡住，那么它一定会被前面的墙挡住（废话）

结合前面的推导，如果他能拦住角度更大的炮弹，他就一定能拦住比他角度更小的。

这不就是 $n+m$ 的算法了？代码如下。

```cpp
db get_y(ll x,ll y)
{
	db xx=a[x].x;
	db t=xx/1.0/v/cos(b[y].alpha);
	return (db)v*sin(b[y].alpha)*t-G*t*t/2.0;
}
db get_x(ll x)
{
	return 2.0*v*v/G*sin(b[x].alpha)*cos(b[x].alpha);
}
int main()
{
 	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	n=read(),v=read();
	for(ll i=1;i<=n;i++)
	{
		b[i].alpha=dread();
		b[i].id=i;
		b[i].r=1.000*v*v*sin(2.0*b[i].alpha)/G;
		ans[i]=-1;
	}
	sort(b+1,b+n+1);
	for(ll i=1;i<=n;i++)mp[b[i].id]=i;
	m=read();
	for(ll i=1;i<=m;i++)
		a[i].x=dread(),a[i].y=dread();
	sort(a+1,a+m+1);
	ll las=0;
	for(ll i=1;i<=m;i++)
		for(ll j=las+1;j<=n;j++)
		{
			if(get_y(i,j)>a[i].y)break;
			ans[b[j].id]=a[i].x;ans1[b[j].id]=get_y(i,j);
			las=j;
		}
	for(ll i=1;i<=n;i++)
		if(ans[i]<0)
		{
			ans[i]=get_x(mp[i]);
			ans1[i]=0.0;
		}
	for(ll i=1;i<=n;i++)
		printf("%.10Lf %.10Lf\n",ans[i],ans1[i]);
	return 0;
}
```

做完了？没有。

注意到上面的代码没有考虑某一发炮弹刚好落在两个墙之间的情况。

要加一句

``` cpp
if(b[j].r<a[i].x)continue;
```

完整代码（禁止抄袭）：

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a));
#define pc putchar
#define fast_iostream ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef long double ld;d
typedef long double db;
const ld EPS=1e-8;
const ll INF=ll(1e9+7);
const ll LLINF=ll(1e18+7);
const ld LDEPS=1e-18;
inline ll max(ll x,ll y){return x>y?x:y;}
inline ll min(ll x,ll y){return x<y?x:y;}
inline ld dmax(ld x,ld y){return x>y?x:y;}
inline ld dmin(ld x,ld y){return x<y?x:y;}
inline ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
inline ll lcm(ll a,ll b){return a*b/gcd(a,b);}
inline ll lowbit(ll x){return x&(-x);}
inline ll read(){ll read_result=0,is_below_0=0;char now_ch=0;while(!isdigit(now_ch)){is_below_0|=now_ch=='-';now_ch=getchar();}while(isdigit(now_ch)){read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);now_ch=getchar();}return is_below_0?-read_result:read_result;}
inline ld dread(){ld x=0,d=0.1;char f=0,ch=getchar();while(!isdigit(ch))f|=(ch=='-'),ch=getchar();while(isdigit(ch)) x=x*10+ch-48,ch=getchar();if(ch=='.'){ch=getchar();while(isdigit(ch))x+=d*(ch^48),d*=0.1,ch=getchar();}return f?-x:x;}
inline void write(ll x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
const db G=9.8;const ll MAXN=1e5+7;
ll n,m,v;
struct node
{
	db x,y;
	bool operator<(const node& xx)
	{
		return x<xx.x;
	}
}a[MAXN];
struct Node
{
	db alpha,r;
	ll id;
	bool operator<(const Node& xx)
	{
		return alpha<xx.alpha;
	}
}b[MAXN];
db r[MAXN],ans[MAXN],ans1[MAXN];
map<ll,ll>mp;
db get_y(ll x,ll y)
{
	db xx=a[x].x;
	db t=xx/1.0/v/cos(b[y].alpha);
	return (db)v*sin(b[y].alpha)*t-G*t*t/2.0;
}
db get_x(ll x)
{
	return 2.0*v*v/G*sin(b[x].alpha)*cos(b[x].alpha);
}
int main()
{
 	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	n=read(),v=read();
	for(ll i=1;i<=n;i++)
	{
		b[i].alpha=dread();
		b[i].id=i;
		b[i].r=1.000*v*v*sin(2.0*b[i].alpha)/G;
		ans[i]=-1;
	}
	sort(b+1,b+n+1);
	for(ll i=1;i<=n;i++)mp[b[i].id]=i;
	m=read();
	for(ll i=1;i<=m;i++)
		a[i].x=dread(),a[i].y=dread();
	sort(a+1,a+m+1);
	ll las=0;
	for(ll i=1;i<=m;i++)
		for(ll j=las+1;j<=n;j++)
		{
			if(b[j].r<a[i].x)continue;
			if(get_y(i,j)>a[i].y)break;
			ans[b[j].id]=a[i].x;ans1[b[j].id]=get_y(i,j);
			las=j;
		}
	for(ll i=1;i<=n;i++)
		if(ans[i]<0)
		{
			ans[i]=get_x(mp[i]);
			ans1[i]=0.0;
		}
	for(ll i=1;i<=n;i++)
		printf("%.10Lf %.10Lf\n",ans[i],ans1[i]);
	return 0;
}
```



---

## 作者：7KByte (赞：0)

物理好题（

首先我们知道角度 $\alpha$ 和速度 $v$ ，将速度分解为竖直和水平两个分量，得到 $v_x=v\cos \alpha \ ,\ v_y=v\sin \alpha$。

没有墙时，飞行时间为 $t=\dfrac{2v_y}{g}$，水平位移为 $s=v_xt=\dfrac{2v^2\sin\alpha \cos\alpha}{g}=\dfrac{v^2\sin 2\alpha}{g}$ 。

不难发现当 $\alpha =\dfrac{\pi}{4}$ 时 $s$ 取得最大值，$\alpha \le \dfrac{\pi}{4}$ 时 $s$ 单调递增。

所以随着角度增大，落地点越来越远，我们可以知道所有的抛物线除原点之外没有交点。所以随着 $\alpha $ 增大，终止点 $x$ 坐标不降。

这样我们将所有询问从小到大排序，然后所有墙按 $x$ 坐标从小到大，然后扫一遍即可。

时间复杂度$\rm O(N\log N+M\log M)$，瓶颈在于排序。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 1000005
using namespace std;
int n,m;double v,x[N],y[N];
struct node{
	int op;double val;
	bool operator<(const node o)const{return val<o.val;}
}a[N];
pair<double,double>u[N];
int main(){
	scanf("%d%lf",&n,&v);
	rep(i,1,n)scanf("%lf",&a[i].val),a[i].op=i;
	sort(a+1,a+n+1);scanf("%d",&m);
	rep(i,1,m)scanf("%lf%lf",&u[i].first,&u[i].second);
	sort(u+1,u+m+1);int j=1;
	rep(i,1,n){
		double vx=v*cos(a[i].val),vy=v*sin(a[i].val),t=vy/4.9;
		bool flag=false;
		while(j<=m&&u[j].first<=vx*t){
			double tm=u[j].first/vx,cur=vy*tm-4.9*tm*tm;
			if(cur<=u[j].second){
				flag=true;
				x[a[i].op]=u[j].first;y[a[i].op]=cur;
				break;
			}
			j++;
		}
		if(!flag)x[a[i].op]=vx*t,y[a[i].op]=0;
	}
	rep(i,1,n)printf("%.10lf %.10lf\n",x[i],y[i]);
	return 0;
}
```

---

## 作者：XL4453 (赞：0)


~~没给式子说不定能紫，但是都给式子了，那不直接红题吗。~~

本题使用弧度制。

---
### 解题思路：

双指针法。

首先算出在如果没有板子球空中的时间，也就是当 $y=0$ 时求 $t$，将 $y=0$ 带入题目中给的式子，得：$\dfrac{gt^2}{2}-v\sin(a) t=0$，直接提取 $t$，立刻解得：$t_1=0,t_2=\dfrac{2v\sin(a)}{g}$。

带入到 $x=vt\cos(a)$ 中，得到 $x=\dfrac{v^2\cos(2a)}{g}$，由于 $a\in(0,\dfrac{\pi}{4})$，$x$ 单调递增。

由于所有的炮弹都是速度相等的，所以若将所有的炮弹按照 $a$ 从小排序，则对于一个单一隔板（不考虑被其他的拦截的情况），若其能挡到 $a$ 大的炮弹，则一定能挡到 $a$ 相对小的炮弹。

所以从整体上看，每一次都是 $a$ 最小的几个被拦截或者落地。

---
到这里做法就已经清楚了，将所有的隔板按照 $x$ 从小到大排序，将所有的炮弹按照 $a$ 从小到大排序。依次考虑每一个隔板能拦截到的炮弹，记录下一个已经被拦截炮弹的编号，依次向上算。

注意炮弹落地也要考虑。

---

考察内容：~~物理~~。

---
### 代码：

```cpp
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
struct str{
	int id;
	double a,x,y;
	bool operator <(const str x)const{
		return a<x.a;
	}
}p[10005];
struct bd{
	double x,y;
}b[100005];
bool cmp(str a,str b){
	return a.id<b.id;
}
bool cmb(bd a,bd b){
	return a.x<b.x;
}
int n,v,now,m;
double g=9.8;
double calc_t(double a,double v,double x){
	return x/(v*cos(a));
}
double calc_y(double a,double v,double t){
	return v*t*sin(a)-4.9*t*t;
}
double calc_t2(double a,double v,double y){
	return 2*v*sin(a)/9.8;
}
double calc_x(double a,double v,double t){
	return v*cos(a)*t;
}
bool check(double a,double v,double x,double y){
	return calc_y(a,v,calc_t(a,v,x))<y;
}
int main(){
	scanf("%d%d",&n,&v);
	for(int i=1;i<=n;i++){
		scanf("%lf",&p[i].a);
		p[i].id=i;
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	scanf("%lf%lf",&b[i].x,&b[i].y);
	m++;
	b[m].x=1e5;
	sort(p+1,p+n+1);
	sort(b+1,b+m+1,cmb);
	now=1;
	for(int i=1;i<=m;i++){
		while(check(p[now].a,v,b[i].x,b[i].y)&&now<=n){
			if(calc_y(p[now].a,v,calc_t(p[now].a,v,b[i].x))>0){
				p[now].x=b[i].x;
				p[now].y=calc_y(p[now].a,v,calc_t(p[now].a,v,b[i].x));
			}
			else{
				p[now].x=2*v*v*sin(p[now].a)*cos(p[now].a)/9.8;
				p[now].y=0;
			}
			now++;
		}
	}
	sort(p+1,p+n+1,cmp);
	for(int i=1;i<=n;i++){
		printf("%.8lf %.8lf\n",p[i].x,p[i].y);
	}
	return 0;
}
```


---

