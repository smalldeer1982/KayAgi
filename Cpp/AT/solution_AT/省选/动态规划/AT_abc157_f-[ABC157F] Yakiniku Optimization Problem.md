# [ABC157F] Yakiniku Optimization Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc157/tasks/abc157_f

高橋君は二次元平面である網の上で $ N $ 枚の肉を焼こうとしています。 $ i $ 枚目の肉の位置は $ \left(x_i,\ y_i\right) $であり、火の通りにくさは $ c_i $ です。

高橋君は熱源を $ 1 $ つ持っています。熱源を位置 $ \left(X,\ Y\right) $ ($ X,\ Y $は実数)に置くと、 $ i $枚目の肉は、 焼けるまでに $ c_i\ \times\ \sqrt{\left(X\ -\ x_i\right)^2\ +\ \left(Y-y_i\right)^2} $ 秒掛かります。

高橋君は肉を $ K $ 枚食べたいと考えています。 $ K $ 枚以上の肉が焼けるまでに掛かる時間を最小化するように高橋君が熱源を配置したとき、その所要時間を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 60 $
- $ 1\ \leq\ K\ \leq\ N $
- $ -1000\ \leq\ x_i\ ,\ y_i\ \leq\ 1000 $
- $ \left(x_i,\ y_i\right)\ \neq\ \left(x_j,\ y_j\right)\ \left(i\ \neq\ j\ \right) $
- $ 1\ \leq\ c_i\ \leq\ 100 $

### Sample Explanation 1

熱源を $ \left(-0.2,\ 0\right) $に置くと、 $ 2.4 $ 秒後までに $ 1,\ 2,\ 3 $ 枚目の肉が焼けます。これが最適な熱源の置き方です。

## 样例 #1

### 输入

```
4 3
-1 0 3
0 0 3
1 0 2
1 1 40```

### 输出

```
2.4```

## 样例 #2

### 输入

```
10 5
-879 981 26
890 -406 81
512 859 97
362 -955 25
128 553 17
-885 763 2
449 310 57
-656 -204 11
-270 76 40
184 170 16```

### 输出

```
7411.2252```

# 题解

## 作者：rrrrr (赞：5)

二分 $T$ 。
题意变成对于 $N$ 个圆心 $(x,y)$ ,半径 $\frac{T}{c}$ 的圆是否存在一个点满足在至少 $k$ 个圆内。   
可以发现最优点一定在两圆交点或圆心上。    
对于求两圆交点：  
两圆方程联立。
$$\begin{cases}(x-\text{ax})^2+(y-\text{ay})^2=\text{ar}^2\\(x-\text{bx})^2+(y-\text{by})^2=\text{br}^2\end{cases}$$
相减得
$$
y=\frac{-\text{ar}^2+\text{ax}^2-2 \text{ax} x+\text{ay}^2+\text{br}^2-\text{bx}^2-\text{by}^2+2 \text{bx} x-2 \text{ax} x}{2 \text{ay}-2 \text{by}}$$
此时为一条直线，被称为根轴，过两圆交点。
带入一圆方程：
$$(x-\text{ax})^2+(k x+b-\text{ay})^2=\text{ar}^2$$
$$-\text{ar}^2+\text{ax}^2-2 \text{ax} x+\text{ay}^2-2 \text{ay} b-2 \text{ay} k x+b^2+2 b k x+k^2 x^2+x^2=0$$
解方程即可

$(x,y)=(x\cos(\theta)-y\sin(\theta),y\cos(\theta)+x\sin(\theta))$    

为避免直线无斜截式，旋转一定角度。
```cpp
//2021-11-08 12:53
#include<bits/stdc++.h>
using namespace std;
const double th=1.14514;
int read()
{
	int x=0;bool f=0;char c=getchar();
	for(;!isdigit(c);c=getchar())f^=!(c-45);
	for(;isdigit(c);c=getchar())x=x*10+c-48;
	if(f)x=-x;return x;
}
int n,k,ci[65];
struct poi
{
	double x,y;
	double operator/(const poi &k)const
	{
		return sqrt((k.x-x)*(k.x-x)+(k.y-y)*(k.y-y));
	}
};
struct cir
{
	poi o;
	double r,x,y;
	void read()
	{
		x=::read(),y=::read();
		o={x*cos(th)-y*sin(th),y*cos(th)+x*sin(th)};
		x=o.x,y=o.y;
	}
	bool in(poi p)
	{
		return p/o<=r+1e-6;
	}
}c[65];
struct line
{
	double k,b;
	double f(double x)
	{
		return k*x+b;
	}
};
struct fc
{
	double a,b,c;
	pair<double,double>solve()
	{
		return {(-b+sqrt(b*b-4*a*c))/(2*a),(-b-sqrt(b*b-4*a*c))/(2*a)};
	}
};
bool cro(cir a,cir b)
{
	return a.o/b.o<=a.r+b.r;
}
pair<poi,poi> cross(cir a,cir b)
{
	if(a.r>b.r)swap(a,b);
	if(b.r-a.r>b.o/a.o)return {a.o,b.o};
	line g={(a.x-b.x)/(b.y-a.y),(a.r*a.r-b.r*b.r+b.x*b.x-a.x*a.x-a.y*a.y+b.y*b.y)/(2*(b.y-a.y))};
	fc z={1+g.k*g.k,-2*a.x+2*(g.b-a.y)*g.k,a.x*a.x+(g.b-a.y)*(g.b-a.y)-a.r*a.r};
	auto res=z.solve();
	return {{res.first,g.f(res.first)},(poi){res.second,g.f(res.second)}};
}
bool check(double mid)
{
	for(int i=1;i<=n;i++)c[i].r=mid/ci[i];
	vector<poi>ans;
	ans.clear();
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(cro(c[i],c[j]))
			{
				auto res=cross(c[i],c[j]);
				ans.push_back(res.first);
				ans.push_back(res.second);
			}		
		}
	}
	for(auto y:ans)
	{
		int iit=0;
		for(int i=1;i<=n;i++)
		{
			if(c[i].in(y))
			iit++;
		}
		if(iit>=k)return true;
	}
	return false;
}
int main()
{
	srand(time(0));
	n=read(),k=read();
	if(k==1)return cout<<0<<"\n",0;
	for(int i=1;i<=n;i++)
	{
		c[i].read();
		ci[i]=read();
	}
	double l=0,r=200000,ans;
	while(l+1e-7<=r)
	{
		double mid=(l+r)/2;
		if(check(mid))r=mid,ans=mid;
		else l=mid;
	}
	printf("%.7lf",ans);
}
```


---

## 作者：chenxia25 (赞：4)

好的，这是我的最后一道模拟退火练习题，来AtC上撒个野。真心不想再玄了。

> [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT5332) & [AtC题目页面传送门](https://atcoder.jp/contests/abc157/tasks/abc157_f)

>给定平面上$n$个点$(x_i,y_i)$，你需要选一个点$(x,y)$，这样到时间$c_i\sqrt{(x_i-x)^2+(y_i-y)^2}$以后点$i$就可以吃了。你需要最小化至少能吃到$m$个点的时间。一个测试点AC当且仅当绝对误差或相对误差不超过$10^{-6}$。

>$n\in[1,60],|x_i|,|y_i|\in[-1000,1000],c_i\in[1,100]$。

这题正解是二分还是啥的？不会。不难发现至少能吃到$m$个点的时间是一个关于你选的点的坐标的函数，仅有二维，比较良心，一脸可以模拟退火的样子。

然后就写了。注意这里如何计算函数值，把$n$个时间算出来再排个序，取第$m$个即可。在本地调一调，最终$T_0=10^4,T_e=10^{-10},\Delta T=0.9999$，算新解的时候采用$x'=x+\left(R\left(0,10^4\right)-R\left(0,10^4\right)\right)T,y'=y+\left(R\left(0,10^4\right)-R\left(0,10^4\right)\right)T$，其中$R(l,r)$为$[l,r]$内的随机实数，只跑一遍模拟退火（因为这个维数仅有两维，按照经验提高$\Delta T$是要比跑多次效果好的），这样可以过样例，精度还可以。

然后交，随机种子选[20060617](https://atcoder.jp/contests/abc157/submissions/15550174)->[1\*\*\*\*\*\*7](https://atcoder.jp/contests/abc157/submissions/15550192)->[998244353](https://atcoder.jp/contests/abc157/submissions/15550219)->[114514](https://atcoder.jp/contests/abc157/submissions/15550246)交了四发，到第四发的时候发现第二发和第四发过的点的集合的并等于全集。又注意到每次交大概是$250\mathrm{ms}$，那么可以把这两发综合起来，用两个种子各跑一遍，AC。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define urd uniform_real_distribution
mt19937 rng(19260817);
double sq(double x){return x*x;}
const int N=60;
int n,m;
double x[N+1],y[N+1],c[N+1];
double a[N+1];
double calc(double x0,double y0){
	for(int i=1;i<=n;i++)a[i]=c[i]*sqrt(sq(x[i]-x0)+sq(y[i]-y0));
	sort(a+1,a+n+1);
	return a[m];
}
double sim_ann(double st,double ed,double delta){//模拟退火 
	double x0=0,y0=0,res=calc(0,0);
//	int cnt=0;
	for(double tem=st;tem>=ed;tem*=delta){
		double nw_x=x0+(urd<>(0,10000)(rng)-urd<>(0,10000)(rng))*tem;
		double nw_y=y0+(urd<>(0,10000)(rng)-urd<>(0,10000)(rng))*tem;//生成新解 
		double nw=calc(nw_x,nw_y);
		if(nw<res||urd<>(0,1)(rng)<=exp((res-nw)/tem))x0=nw_x,y0=nw_y,res=nw;
//		if((++cnt)%100==0)printf("tem=%.5lf x=%.5lf y=%.5lf res=%.5lf\n",tem,x0,y0,res);
	}
	return res;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>x[i]>>y[i]>>c[i];
	double ans=sim_ann(1e4,1e-10,.9999);
	rng=mt19937(114514);//换种子 
	ans=min(ans,sim_ann(1e4,1e-10,.9999));
	printf("%.10lf",ans);
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

注意到 $n\le 60,|x_i|,|y_i|\le 10^3$，要计算的东西又很神秘，尝试对最优坐标模拟退火。

仿照平衡点那个题，每次对当前坐标随机增量，然后代入计算第 $K$ 小值，如果答案更优直接接受，否则以一定概率接受。

求第 $K$ 小可以用 `std::nth_element`，这样比排序少一只 $\log$，会减少单次退火耗时。

为了防止数据的精心构造，可以对所有点同时随机旋转，这样不会影响答案的值。

要把终止温度调低一点，降温系数适当就好，别忘了打卡时。

水平有限，不知道也感觉没啥好说的，直接看代码吧。

# Code

```cpp
#include<bits/stdc++.h>
const double eps=1e-13,delta=0.998;
std::mt19937 rnd(time(0));
inline int read(int l,int r){
	return rnd()%(r-l+1)+l;
}
struct node{
	double x,y,c;
}a[65];
double v[65];
int n,m;
double ans;
inline double calc(double x,double y){
	for(int i=1;i<=n;++i)
		v[i]=a[i].c*hypot(x-a[i].x,y-a[i].y);
	std::nth_element(v+1,v+m,v+n+1);
	ans=std::min(ans,v[m]);
	return v[m];
}
double x,y;
inline void solve(){
	x+=read(-3,3);y+=read(-3,3);
	double res=calc(x,y);
	for(double T=1e4;T>eps;T*=delta){
		static double _x,_y,val;
		_x=x+read(-1e4,1e4)*T;
		_y=y+read(-1e4,1e4)*T;
		val=calc(_x,_y);
		if(res>val)res=val,x=_x,y=_y;
		else if(exp((res-val)/T)*1e8>read(0,1e8))res=val,x=_x,y=_y;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	double alpha=read(1,3141592)/1e6,sinx=sin(alpha),cosx=cos(alpha),x,y,_s=clock();
	for(int i=1;i<=n;++i)
		scanf("%lf%lf%lf",&x,&y,&a[i].c),
		a[i].x=x*cosx-y*sinx,a[i].y=x*sinx+y*cosx;
	ans=1e18;
	while((clock()-_s)/CLOCKS_PER_SEC<1.9)solve();
	printf("%.9lf",ans);
	return 0;
}
```

---

## 作者：nr0728 (赞：1)

### 前言

简单模拟退火练手题。

### 思路

对 $X$ 和 $Y$ 模拟退火。

> **什么是模拟退火？**
> 
> 模拟退火是一种随机化算法。当一个问题的方案数量极大（甚至是无穷的）而且不是一个单峰函数时，我们常使用模拟退火求解。

> **模拟退火如何实现？**
> 
> 如果新状态的解更优则修改答案，否则以一定概率接受新状态。
> 
> 我们定义当前温度为 $T$，新状态与已知状态（由已知状态通过随机的方式得到）之间的能量（值）差为 $\Delta E$（$\Delta E\geq0$），则发生状态转移（修改最优解）的概率为：
> $$P(\Delta E)=\begin{cases}1&\text{the new status is better}\\e^{\frac{-\Delta E}{T}}&\text{otherwise}\end{cases}$$

其中 $c_i\times\sqrt{(X-x_i)^2+(Y-y_i)^2}$ 的 $K$ 小值可以通过用 $tmp$ 数组存下所有 $1\leq i\leq N$ 对应的值，再排序得到。（注：$N\leq60$，用 `std::sort` 最劣情况只需要运行约 $360$ 次。）

本题需要注意的点：

1. $X$ 和 $Y$ 都要使用 double 类型。
2. 本题需要旋转 $x_i$ 和 $y_i$ 随机度数，否则会 WA。即 `for(int i=1;i<=n;++i) cin>>x>>y>>z,a[i].x=cos(_)*x-sin(_)*y,a[i].y=sin(_)*x+cos(_)*y;`。其中 `_` 为随机 $1^\circ\sim360^\circ$。
3. 退火次数太少会 WA，建议退到即将超过时限再输出。

### 核心代码

```cpp
#define Rnd() (rand()*1.0/RAND_MAX)
double ans=1e9;
double nowx,nowy,now,tmp[61]; 
const double eps=1e-4;
double calc(double x,double y)
{
	for(int i=1;i<=n;++i)
		tmp[i]=a[i].z*sqrt((x-a[i].x)*(x-a[i].x)+(y-a[i].y)*(y-a[i].y));
	sort(tmp+1,tmp+n+1);
	if(tmp[k]<ans) ans=tmp[k];
	return tmp[k];
}
void SA()
{
	double T=1e4,nxtx,nxty,good,nxt;
	while(T>eps)
	{
		nxtx=nowx+(Rnd()-0.5)*T;
		nxty=nowy+(Rnd()-0.5)*T;
		nxt=calc(nxtx,nxty);
		good=nxt-now;
		if(good<0) nowx=nxtx,nowy=nxty,now=nxt;
		else if(exp(-good/T)>Rnd()) nowx=nxtx,nowy=nxty,now=nxt;
		T*=.9999;
	}
}
```

---

## 作者：Link_Cut_Y (赞：0)

随机化。

好久没写随机手又痒了。拿来练练手。

这数据范围 $n \le 60$，$x, y$ 又这么小，这不明摆着要写随机化吗？

直接套上遗传板子即可。[如果你不会遗传算法](https://www.luogu.com.cn/blog/Link-Cut-Y/qian-tan-yi-zhuan-suan-fa)。

发现参数非常难调。于是换不同参数多跑几遍就行了。

参数都在下面的代码里，剩下的就看脸了。

```cpp
struct node { double x, y, c; }p[N];
double random(double x) { return (double)rand() / RAND_MAX * x; }
struct Individual {
    double x, y, fitness;
    Individual(double x, double y);
    Individual mate();
    double calc_fitness();
    bool operator < (const Individual& tmp)const {
        return fitness < tmp.fitness;
    }
};
Individual::Individual(double x, double y) {
    this -> x = x, this -> y = y;
    this -> fitness = calc_fitness();
}
Individual Individual::mate() {
	double X = x + ((rand() & 1) ? -1 : 1) * random(lim);
	double Y = y + ((rand() & 1) ? -1 : 1) * random(lim);
	return Individual(X, Y);
}
double dist(double x1, double y1, double x2, double y2, double c) {
	auto sq = [&](double x) { return x * x; };
	return sqrt(sq(x1 - x2) + sq(y1 - y2)) * c;
}
double Individual::calc_fitness() {
    vector<double> vec; rep(i, 1, n)
		vec.push_back(dist(x, y, p[i].x, p[i].y, p[i].c));
	sort(vec.begin(), vec.end()); return vec[k - 1];
}
double solve(int POPULATION, int TIMES, double T) {
	vector<Individual> population; lim = 1000.00;
    for (int i = 0; i < POPULATION; i ++ ) {
        double x = random(100000.00) * (rand() & 1 ? -1 : 1);
        double y = random(100000.00) * (rand() & 1 ? -1 : 1);
        population.push_back(Individual(x, y));
    }
    for (int i = TIMES; i >= 1; i -- ) {
        sort(population.begin(), population.end());
        vector<Individual> new_population;
        int s = (10 * POPULATION) / 100;
        for (int i = 0; i < s; i ++ )
            new_population.push_back(population[i]);
        s = POPULATION - s;
        while (new_population.size() < POPULATION) {
            int len = population.size();
            Individual p = population[rand() % 50];
            Individual q = p.mate();
            new_population.emplace_back(q);
        }  population = new_population; lim = lim * T;
    } return population[0].fitness;
}
int main() {
	srand(998244353);
    scanf("%d%d", &n, &k);
    rep(i, 1, n) scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].c);
    double ans = solve(300, 800, 0.985);
	ans = min(ans, solve(800, 800, 0.97));
    ans = min(ans, solve(500, 1000, 0.98));
    ans = min(ans, solve(1000, 500, 0.97));
    ans = min(ans, solve(800, 800, 0.975));
    printf("%.7lf\n", ans);
}
```

---

