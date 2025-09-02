# [CERC2015] Ice Igloos

## 题目描述

给你$n$个圆$,m$条线段$,$求每条线段与多少圆相交

$n,m\le10^5,1\le x_i,y_i\le500,0\lt r_i\lt 1$

## 样例 #1

### 输入

```
5 
4 2 0.6 
7 3 0.7 
8 5 0.8 
1 3 0.7 
3 4 0.4 
2 
3 1 9 6 
3 4 7 2```

### 输出

```
2
1```

# 题解

## 作者：lemonfor (赞：7)

一道经典的计算几何题，并不难~~然而我还是交了好多遍~~

我们有两个思路：

 一.暴力：对于每一条给出的线段，我们把每一个圆扫一遍并判断是否相交，但是这样太慢了，最后四个点TLE跑不掉惹QAQ。。。

 方法还是值得借鉴的：

 1) 如果线段有且只有一个端点在圆内，肯定相交
 
 2) 如果线段两个端点都在圆内，肯定不相交
 
 3) 如果线段两个端点都不在圆内，则可以用距离公式去判断是否相交
 
 
 ~~想要图？没有图，自己脑补~~
 
 代码如下：

 ```cpp
 #include<cstdio>
#include<cmath>
#include<algorithm>
#define _ 0
#define N 200000
#define drep(k ,l ,r) for(register int k = (l) ; k >= r ; -- k)
#define rep(k ,l ,r) for(register int k = l ; k <= r ; ++ k)
#define re register
using namespace std;
struct node {
	int x ,y;
	double r;
} cir[N];
int n ,m ,_x1 ,_yi ,_x2 ,_y2;
int read() {
	char cc = getchar() ; int cn = 0 ,flus = 1;
	while(cc < '0' || cc > '9') {if(cc == '-') flus = - flus ; cc = getchar();}
	while(cc >= '0' && cc <= '9') cn = cn * 10 + cc - '0' ,cc = getchar();
	return flus * cn;
}
bool in_cir(int _x ,int _y ,int now) {//判断点是否在圆内
	if((_x - cir[now].x) * (_x - cir[now].x) + (_y - cir[now].y) * (_y - cir[now].y) - cir[now].r * cir[now].r <= 0) 
		return 1;
    return 0;
}
bool judge(int now) {//总的判断函数
	re bool inc1 = in_cir(_x1 ,_yi ,now) ,inc2 = in_cir(_x2 ,_y2 ,now);
	if(inc1 && inc2) return 0;
	if(((!inc1) && inc2) || ((!inc2) && inc1)) return 1;
	re double A ,B ,C ,dis1 ,dis2 ,ang1 ,ang2;
	if(_x1 == _x2) A = 1 ,B = 0 ,C = - _x1;
	else if(_yi == _y2) A = 0 ,B = 1 ,C = - _yi;
		 else A = _yi - _y2 ,B = _x2 - _x1 ,C = _x1 * _y2 - _x2 * _yi;
	/*dis1 = A * cir[now].x + B * cir[now].y + C; dis1 *= dis1;
	dis2 = (A * A + B * B) * cir[now].r * cir[now].r;
	if(dis1 > dis2) return 0;
	ang1 = (cir[now].x - _x1) * (_x2 - _x1) + (cir[now].y - _yi) * (_y2 - _yi);
	ang2 = (cir[now].x - _x2) * (_x1 - _x2) + (cir[now].y - _y2) * (_yi - _y2);
	if(ang1 > 0 && ang2 > 0) return 1;
	return 0;*/ 利用余弦公柿判断是否相交，然而还比距离公柿麻烦多了
	double d = abs((A * cir[now].x + B * cir[now].y + C) / sqrt(A * A + B * B));//距离公柿
	return cir[now].r - d >= 0;
}
int main() {
	n = read();
	rep(i ,1 ,n) cir[i].x = read() ,cir[i].y = read() ,scanf("%lf" ,&cir[i].r);
	m = read();
	while(m --) {
		re int ans = 0;
		_x1 = read() ,_yi = read() ,_x2 = read() ,_y2 = read();
		rep(i ,1 ,n) {
        	if((max(_yi ,_y2) >= cir[i].y - cir[i].r) && min(_yi ,_y2) <= cir[i].y + cir[i].r && max(_x1 ,_x2) >= cir[i].x - cir[i].r && min(_x1 ,_x2) <= cir[i].x + cir[i].r)//一个并无啥子用的特判
            if(judge(i)) ++ans;
        }
		printf("%d\n" ,ans);
	}
	return ~~(0^_^0);
}
 ```
 然后你就有了63分，并为怎么剪枝而抓狂。。。。。。

~~最后这种方法还是被我抛弃了QAQ~~
 
 二.暴力：对于每一条给出的线段，枚举线段上的每一个整数 $x$ 和每一个对应的 $y$ ,因为圆的半径 $r\leq1$,所以我们只需要在一定范围内查找是否有圆，是否相交就行了。
 
   1) 如果存在垂直于 $x$ 轴的情况，那么只要判断线段经过的地方是否有圆。
 
   2) 如果存在垂直于 $y$ 轴的情况，同上。
 
   3) 如果线段存在斜率，则需要划定一个区间去检查其中是否有圆。 
 
   -  若线段递增，则查询 $ [x][floor(k * (x - 1) + b - Eps)] $ 到 $ [x][ceil(k * (x + 1) + b + Eps)] $
    
   -  若线段递减，则查询 $ [x][floor(k * (x + 1) + b - Eps)] $ 到 $ [x][ceil(k * (x - 1) + b + Eps)] $
    
   -  叫你忘记特判端点!
    


代码如下：
```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#define _ 0
#define drep(k ,l ,r) for(register int k = (l) ; k >= (r) ; -- k)
#define rep(k ,l ,r) for(register int k = l ; k <= r ; ++ k)
#define re register 
using namespace std;
const int Eps = 1e-8;
double xoy[700][700] ,r ,k ,b ,len ,A ,B ,C;
int x1 ,yI ,x2 ,yS ,n ,m ,ans ,_x ,_y;
int read() {
    char cc = getchar() ; int cn = 0 ,flus = 1;
    while(cc < '0' || cc > '9') {if(cc == '-') flus = - flus ; cc = getchar();}
    while(cc >= '0' && cc <= '9') cn = cn * 10 + cc - '0' ,cc = getchar();
    return flus * cn;
}
void line() {//解直线
    A = (double)(yS - yI) ,B = (double)(x1 - x2) ,C = (double)yI * (double)(x2 - x1) + (double)x1 * (double)(yI - yS);
    re double tmp = (double)sqrt(A * A + B * B);
    A /= tmp ,B /= tmp ,C /= tmp;
    k = (double)(yS - yI) / (double)(x2 - x1) ,b = (double)(yI - x1 * k);
}
bool get(int x ,int y) {//判断是否相交
    re double tmp = fabs(A * x + B * y + C) - xoy[x][y];
    if(fabs(tmp) <= Eps || tmp <= 0) return 1;
    else return 0;
}
int maker(int op ,int y_ ,int y__) {//在区间内查询
    re int res = 0;
    rep(i ,y_ ,y__) {
        if(xoy[op][i] <= Eps) continue;
        res += get(op ,i);
    }
    return res;
}
int main() {
    n = read();
    while(n--) 
	x1 = read() ,yI = read() ,scanf("%lf" ,&r) ,xoy[x1][yI] = r;
    m = read();
    while(m --) {
        x1 = read() ,yI = read() ,x2 = read() ,yS = read() ,ans = 0;
        if(x1 == x2) {//垂直于x轴
            if(yI > yS) swap(yI ,yS);
            rep(i ,yI ,yS) if(xoy[x1][i]) ++ ans;//查询线段上是否存在圆，统计答案
        }
        else if(yI == yS) {//垂直于y轴
            if(x1 > x2) swap(x1 ,x2);
            rep(i ,x1 ,x2) if(xoy[i][yI]) ++ans;
        }
        else {
            if(x1 > x2 || ((x1 == x2) && (yI > yS))) swap(x1 ,x2) ,swap(yI ,yS);
            line();
            if(k > 0) {//递增
                ans += maker(x1 ,yI ,ceil(k * (x1 + 1) + b + Eps));//左端点
                rep(x ,x1 + 1 ,x2 - 1) ans += maker(x ,floor((double)(k * (x - 1) + b - Eps)) ,ceil((double)(k * (x + 1) + b + Eps)));//中间部分
                ans += maker(x2 ,floor(k * (x2 - 1) + b - Eps) ,yS);//右端点
            }
            else {//递减
                ans += maker(x1 ,floor(k * (x1 + 1) + b - Eps) ,yI);
                rep(x ,x1 + 1 ,x2 - 1) ans += maker(x ,floor((double)(k * (x + 1) + b - Eps)) ,ceil((double)(k * (x - 1) + b + Eps)));
                ans += maker(x2 ,yS ,ceil(k * (x2 - 1) + b + Eps));
            }
        }
        printf("%d\n" ,ans);
    }
    return ~~(0^_^0);
}
```
然后你就得到了100分QAQ

~~不怎么温馨的~~温馨提醒：因为头文件的锅 $y1$ 不能直接定义,上面代码中的 _ $yi$ 则为 $y1$ ,下面代码中的 $yI$ 为 $y1$ , $yS$ 为 $y2$~~别问，问就是心血来潮的全局替换~~

---

## 作者：wwt100127 (赞：1)

## 思路

### First
注意到 $1 \le x_i,y_i \le 500$ 且为整数，考虑从此处入手。

用一个 `vector[505][505]` 存储每个点圆的半径，并将同一个 `vector` 里半径从小到大排序。


### Second
考虑如何查询每个点上的圆到某条线段的**距离**是否小于等于半径。

值得注意，这里的距离与以往所说的距离并不完全相同（下面会说到）。

不妨设点 $P(x_p,y_p)$ 和线段 $l:y=kx+b(x_1 \le x \le x_2)$，线段端点 $A(x_1,y_1)$，$B(x_2,y_2)$，以及从 $P$ 向直线 $y=kx+b$ 作垂线后垂足 $H(x_h,y_h)$。

如果 $x_h < x_1$ 或者 $x_h > x_2$，那么这里的“距离”就应该定义为 $\min(dist(A,P),dist(B,P))$，否则就是 $dist(P,l)$。

二分即可。

### Third
对于每条直线，分成以下三种情况。

- 如果这条直线是“横平竖直”的，那么直接统计即可。
- 如果直线斜率的绝对值小于或者等于 $1$，则对于直线上每个点 $G(x_G,y_G)$，则可能对答案产生影响的圆心横坐标为 $x_G$ 的只可能圆心纵坐标在 $\left [ \left \lfloor y_G-1 \right \rfloor ,\left \lceil y_G+1 \right \rceil  \right ]$ 里的。
- 如果直线斜率的绝对值大于 $1$，那么与上一种情况类似，只需将横纵坐标交换的考虑即可。

## 代码
```cpp
const int N=1e5+5;
const int M=505;
const double eps=1e-9; 
int n,m;
double K,B,X,XX,Y,YY;
double fx(int x){return (x-B)/K;}
double fy(int x){return K*x+B;}
vector<double> G[M][M];
struct Line
{
	double a,b,c;
	Line(int x,int y,int xx,int yy)
	{
		K=1.0*(y-yy)/(x-xx);
		B=y-x*K;
		a=K,b=-1,c=B;
	}
};

double Pow2(double x){return x*x;}
bool check(Line E,int x,int y)
{
	double K1=K,B1=B;
	double K2=-1/K1;
	double B2=(y-K2*x);
	double Px=(B2-B1)/(K1-K2);
	return (Px>=min(X,XX) && Px<=max(X,XX));
}
double Distance(Line E,int x,int y)
{
	return 1.0*fabs(E.a*x+E.b*y+E.c)/sqrt(Pow2(E.a)+Pow2(E.b));
}
double dist(double x,double y,double xx,double yy)
{
	return sqrt(Pow2(xx-x)+Pow2(yy-y));
}
int Get(int x,int y,double r)
{
	return lower_bound(G[x][y].begin(),G[x][y].end(),r)-G[x][y].begin();
}
int Doit(Line E,int x,int y)
{
	if(x<0 || y<0 || x>500 || y>500) return 0;
	if(!G[x][y].size()) return 0;
	if(check(E,x,y)) return G[x][y].size()-Get(x,y,Distance(E,x,y));
	return G[x][y].size()-Get(x,y,min(dist(x,y,XX,YY),dist(x,y,X,Y)));
}
int solvex(Line E,int x,int xx,int y)
{
	int i,ans=0;
	for(i=x;i<=xx;i++)
	ans+=Doit(E,i,y);
	return ans;
}
int solvey(Line E,int x,int y,int yy)
{
	int i,ans=0;
	for(i=y;i<=yy;i++)
	ans+=Doit(E,x,i);
	return ans;
}
int Get_ans(int x,int y,int xx,int yy)
{
	int i,ans=0;
	if(mp(x,y)>mp(xx,yy)) swap(x,xx),swap(y,yy);
	Line E=Line(x,y,xx,yy);
	if(fabs(K)<=1)
	{
		if(mp(x,y)>mp(xx,yy)) swap(x,xx),swap(y,yy);
		X=x,Y=y,XX=xx,YY=yy;
		for(i=x;i<=xx;i++)
		ans+=solvey(E,i,floor(fy(i)-1-eps),ceil(fy(i)+1+eps));
	}
	else
	{
		if(mp(y,x)>mp(yy,xx)) swap(x,xx),swap(y,yy);
		X=x,Y=y,XX=xx,YY=yy;
		for(i=y;i<=yy;i++)
		ans+=solvex(E,floor(fx(i)-1-eps),ceil(fx(i)+1+eps),i);
	}
	return ans;
}
void I_Love_Her_Forever()
{
	int i,j,x,y,xx,yy,q,ans;
	double k;
	n=read();
	for(i=1;i<=n;i++)
	{
		read(x,y);
		scanf("%lf",&k);
		G[x][y].push_back(k);
	}
	for(i=1;i<=500;i++)
	{
		for(j=1;j<=500;j++)
		sort(G[i][j].begin(),G[i][j].end());
	}
	for(q=read();q;q--)
	{
		read(x,y,xx,yy);
		if(x==xx)
		{
			if(mp(y,x)>mp(yy,xx)) swap(x,xx),swap(y,yy);
			for(i=y,ans=0;i<=yy;i++)
			ans+=G[x][i].size();
			write(ans,'\n'); 
			continue;
		}
		if(y==yy)
		{
			if(mp(x,y)>mp(xx,yy)) swap(x,xx),swap(y,yy);
			for(i=x,ans=0;i<=xx;i++)
			ans+=G[i][y].size();
			write(ans,'\n');
			continue;
		}
		write(Get_ans(x,y,xx,yy),'\n');
	}
}
```

最后放两组数据。

第一组：
```cpp
input：
1
284 244 0.62
1
261 269 451 61
  
answer：1
```

第二组：
```cpp
input：
5
2 2 0.99
2 3 0.99
3 2 0.99
3 3 0.99
2 1 0.99
1
2 2 3 3
  
answer：4
```

---

## 作者：Purslane (赞：0)

## Solution

题解还是太聪明了，其实可以简单分讨一下。

注意到圆的半径很小，方格也很小，所以应该是依赖值域计算。

如果线段是横线或者竖线，都可以直接快速 $O(x)$ 计算。

如果斜线，不妨设这条线的斜率的绝对值 $\le 1$，否则可以通过旋转 $90^{\circ}$ 实现。

![](https://s21.ax1x.com/2024/08/06/pkxt4Mt.png)

我们发现，在线段每个 $x \in \mathbb N$ 对应的位置，假设对应纵坐标为 $y$，那么 只有 $\lfloor y \rfloor$、$\lfloor y \rfloor - 1$、$\lceil y \rceil$、$\lceil y \rceil + 1$  四个位置为圆心的圆有可能和这条线段相交。暴力判断即可。

复杂度 $O(nk)$，$k$ 为方格大小。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10,MAXM=500+10;
int n,m,id[MAXM][MAXM];
ld r[MAXN];
int check(int x,int y,int xx,int yy,int rx,int ry,ld r) {
	int S=abs((rx-x)*(yy-y)-(ry-y)*(xx-x));
	ld d=1.0*S/sqrt(1.0*(xx-x)*(xx-x)+1.0*(yy-y)*(yy-y));
	if(d>r+1e-10) return 0;
	if((x-xx)*(x-xx)+(y-yy)*(y-yy)+(rx-x)*(rx-x)+(ry-y)*(ry-y)<(rx-xx)*(rx-xx)+(ry-yy)*(ry-yy)||(x-xx)*(x-xx)+(y-yy)*(y-yy)+(rx-xx)*(rx-xx)+(ry-yy)*(ry-yy)<(rx-x)*(rx-x)+(ry-y)*(ry-y)) {
		return r*r>(rx-x)*(rx-x)+(ry-y)*(ry-y)||r*r>(rx-xx)*(rx-xx)+(ry-yy)*(ry-yy);
	}
	return 1;
}
int solve(int rx,int ry,int x,int y,int xx,int yy) {
	if(rx<1||ry<1||rx>500|ry>500) return 0;
	if(id[rx][ry]) return check(x,y,xx,yy,rx,ry,r[id[rx][ry]]);
	return 0;	
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) {int x,y;cin>>x>>y>>r[i],id[x][y]=i;}
	cin>>m;
	ffor(i,1,m) {
		int x,y,xx,yy;
		cin>>x>>y>>xx>>yy;
		if(abs(x-xx)>=abs(y-yy)) {
			if(x>xx) swap(x,xx),swap(y,yy);
			int ans=0;
			ffor(j,x,xx) {
				ld Y=y+1.0*(yy-y)/(xx-x)*(j-x);
				ans+=solve(j,floor(Y),x,y,xx,yy);
				ans+=solve(j,floor(Y)-1,x,y,xx,yy);
				ans+=solve(j,floor(Y)+1,x,y,xx,yy);
				ans+=solve(j,floor(Y)+2,x,y,xx,yy);	
			}
			cout<<ans<<'\n';
		}
		else {
			if(y>yy) swap(x,xx),swap(y,yy);
			int ans=0;
			ffor(j,y,yy) {
				ld X=x+1.0*(xx-x)/(yy-y)*(j-y);
				ans+=solve(floor(X),j,x,y,xx,yy);
				ans+=solve(floor(X)-1,j,x,y,xx,yy);
				ans+=solve(floor(X)+1,j,x,y,xx,yy);
				ans+=solve(floor(X)+2,j,x,y,xx,yy);	
			}
			cout<<ans<<'\n';	
		}
	}
	return 0;
}
```

---

