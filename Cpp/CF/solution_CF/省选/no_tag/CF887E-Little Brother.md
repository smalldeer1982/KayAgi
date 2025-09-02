# Little Brother

## 题目描述

Masha's little brother draw two points on a sheet of paper. After that, he draws some circles and gave the sheet to his sister.

Masha has just returned from geometry lesson so she instantly noticed some interesting facts about brother's drawing.

At first, the line going through two points, that brother drew, doesn't intersect or touch any circle.

Also, no two circles intersect or touch, and there is no pair of circles such that one circle is located inside another.

Moreover, for each circle, Masha drew a square of the minimal area with sides parallel axis such that this circle is located inside the square and noticed that there is no two squares intersect or touch and there is no pair of squares such that one square is located inside other.

Now Masha wants to draw circle of minimal possible radius such that it goes through two points that brother drew and doesn't intersect any other circle, but other circles can touch Masha's circle and can be located inside it.

It's guaranteed, that answer won't exceed $ 10^{12} $ . It should be held for hacks as well.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF887E/c56ab2a2cf4434792fa48955a8bcd4695bbfb437.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF887E/a5776f5def7ef4a4aa8e3a9f35c33da2f858ab42.png)

## 样例 #1

### 输入

```
2 4 7 13
3
3 0 1
12 4 2
-4 14 2
```

### 输出

```
5.1478150705```

## 样例 #2

### 输入

```
-2 3 10 -10
2
7 0 3
-5 -5 2
```

### 输出

```
9.1481831923```

# 题解

## 作者：OIerBoy (赞：1)

# Sol
我们知道，对于两个圆，我们无非就只有三种情况：相离，相切，相交。而这道题目是不允许其他圆相交，而两个圆不相交只有两种情况：包含，不包含。

根据垂径定理得知，过线段两端的圆的圆心是一定在线段的中垂线上的。而对于每一个其他的圆，与其相交的圆心一定是在一个连续的区间之间的。那么我们就可以考虑用二分来对每一个圆判断不能存在的区间，再将这一段区间打到一个数轴上，用扫描线来找最小半径就行了。
![](https://cdn.luogu.com.cn/upload/image_hosting/570hzmwa.png)

如图，我们就需要将 $O'O''$ 打到一个数轴上，用扫描线找到最小半径就行了。

细节比较多，请看代码。
# Code
```cpp
#include<bits/stdc++.h>
#define inf LONG_LONG_MAX
#define db long double
#define fir first
#define sec second
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((db)(l+r)*1.0/2)
#define Pii pair<db,int>
#define PB(i) push_back(i)
#define MP(i,j) make_pair(i,j)
#define Fo(i,j) for(auto i:j)
#define mem(i,j) memset(i,j,sizeof(i))
#define FO(i,j,k) for(int i=j;i;i=k)
#define FFF(i,j,k) for(auto i=j;i!=k;++i)
#define For(i,j,k) for(int i=j;i<=k;++i)
#define FoR(i,j,k) for(int i=j;i^k;++i)
#define FOR(i,j,k) for(int i=j;i>=k;--i)
#define int long long
using namespace std;
template <typename _Tp>void read(_Tp& first) {
    _Tp x = 0, f = 1; char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ '0'), c = getchar();
    first = x * f;
}inline void write(auto x){
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
#define N 1000005
#define Mod 998244353
struct Node{
	db x,y;
}a,b,x;
int n,cnt;
Pii q[N];
db dis(db a,db b){return sqrtl(a*a+b*b);}
db check(Node x,db t){
	db Ox=(a.x+b.x)*1.0/2+(a.y-b.y)*1.0*t;
	db Oy=(a.y+b.y)*1.0/2+(b.x-a.x)*1.0*t;
	return (db)(dis(Ox-a.x,Oy-a.y)-dis(Ox-x.x,Oy-x.y));
}
db Find(Node x,db R){
	db l=-1e12,r=1e12;
	int Lx=check(x,l)>R;
	int Rx=check(x,r)>R;
	For(i,1,100){
//		cout<<mid<<endl;
		int Mx=check(x,mid)>R;
		if(Lx==Mx)l=mid;
		else r=mid;
	}
	return l;
}bool cmp(Pii a,Pii b){return a.fir<b.fir;}
signed main(){
	scanf("%Lf%Lf%Lf%Lf",&a.x,&a.y,&b.x,&b.y);
	scanf("%lld",&n);
	For(i,1,n){
		Node x;db R;
		scanf("%Lf%Lf%Lf",&x.x,&x.y,&R);
		db l=Find(x,R);
		db r=Find(x,-R);
		if(l>r)swap(l,r);
//		cout<<l<<' '<<r<<endl;
		q[++cnt]=MP(l,1);
		q[++cnt]=MP(r,-1);
	}q[++cnt]=MP(0,0);
	sort(q+1,q+1+cnt,cmp);
//	For(i,1,cnt)cout<<q[i].fir<<' ';cout<<endl;
	db R=1e12;
	int j=0;
	For(i,1,cnt){
		if(!j&&fabsl(q[i].fir)<R)R=fabsl(q[i].fir);j+=q[i].sec;
		if(!j&&fabsl(q[i].fir)<R)R=fabsl(q[i].fir);
//		cout<<R<<endl;
	}
	printf("%.12Lf\n",(db)sqrtl(.25+R*R)*dis(a.x-b.x,a.y-b.y));
	return 0;
}

```

---

## 作者：凑个热闹吖 (赞：0)

[CF887E Little Brother](https://www.luogu.com.cn/record/135437697)

今天模拟赛第一题。

看到题的一瞬间就想到了模拟退火。

不妨设 $P_1(x_1 , y_1)$，$P_2(x_2 , y_2)$，很显然我们要找的圆的圆心在线段 $P_1P_2$ 的中垂线上，然后我们可以算出 $P_1$ 与 $P_2$ 的中点 $M$ 并求出中垂线的解析式。

我们以点 $M$ 作为起点，并将答案设为 $10^{12}$，每次沿着中垂线**随机向左或向右**移动 $Len$ 个单位，拟定为下一个点，设为 $T$。（其中 $Len$ 随着温度的降低从 $10 ^ {12}$ 减少至 $0$） 

接着对 $T$ 进行处理。

- 如果以 $T$ 点为圆心的圆与其它圆相交，就直接跳过当前拟定的点。

- 如果以 $T$ 点为圆心的圆的半径小于当前的答案，就更新答案，并以 $T$ 为起点拟定下一个点。

- 如果以 $T$ 点为圆心的圆半径大于当前的答案，就以一定的概率以 $T$ 为起点拟定下一个点，但不更新答案。

然后用阳寿调一下参数，就可以过掉这道题了。

（cf 的数据好强。。。交了四页才过）

```cpp
#include<bits/stdc++.h>
#define rep(i , m , n) for(register int i = m; i <= n; i++)
#define drp(i , m , n) for(register int i = n; i >= m; i--)

using namespace std;
const long long Max_ans = 1000000000000;
int read(){
	int x = 0 , f = 1;
	char c = getchar();
	while(c < '0' || c > '9')f = c == '-' ? -1 : 1 , c = getchar();
	while(c >= '0' && c <= '9')x = (x << 3) + (x << 1) + (c ^ 48) , c = getchar();
	return x * f;
}
int x_1 , y_1 , x_2 , y_2;
double b , k;
struct Round{
	int x , y , r;
}a[100005];
int n;
double Calc_distance(long double x_1 , long double y_1 , long double x_2 , long double y_2){
	return sqrt((x_1 - x_2) * (x_1 - x_2) + (y_1 - y_2) * (y_1 - y_2));
}
double stx , enx , midx , midy;
bool flag;
void Calc_Limit(){
	if(k == 0){
		if(flag)stx = enx = midx;
		else stx = midx - Max_ans , enx = midx + Max_ans;
		return;
	}
	double diff;
	if(abs(k) >= 1)diff = (double)Max_ans / abs(k);
	else diff = Max_ans;
	stx = midx - diff , enx = midx + diff;
}
void Calc_Line(){
	midx = (double)(x_1 + x_2) / 2 , midy = (double)(y_1 + y_2) / 2;
	if(x_1 == x_2){
		k = 0 , b = midx;
		return;
	}
	if(y_1 == y_2){
		k = 0 , flag = true , b = 0;
		return;
	}
	k = (double)(y_1 - y_2) / (x_1 - x_2);
	k = -(double)1 / k;
	b = midy - k * midx; 
}
double ans_x , ans_y , ans_r = Max_ans;
double tmp_x , tmp_y;
double R;
bool Check(){
	R = Calc_distance(tmp_x , tmp_y , x_1 , y_1);
	rep(i , 1 , n){
		double dis = Calc_distance(tmp_x , tmp_y , a[i].x , a[i].y);
		if((dis < R && dis + a[i].r > R) || (dis > R && dis - a[i].r < R))return false;
	}
	return true;
}
void SA(){
	double Len = flag ? ans_r : (stx - midx);
    Len *= 2;
	double d = 0.975 , T = 1 , T_Min = 1e-16;
	while(T >= T_Min){
		tmp_x = ans_x , tmp_y = ans_y;
		double diff = Len * T * ((rand() % 2 == 1) ? -1 : 1);
		if(!flag)tmp_x += diff , tmp_y = k * tmp_x + b;
		else tmp_y += diff;
		if(!Check()){
			T *= d;
			continue;
		}
		if(R < ans_r)ans_x = tmp_x , ans_y = tmp_y , ans_r = R;
		else if((double)exp((double)(ans_r - R) / T) > (double)rand() / RAND_MAX)ans_x = tmp_x , ans_y = tmp_y;
		T *= d;
	}
}
int main(){
	srand(time(NULL));
	x_1 = read() , y_1 = read() , x_2 = read() , y_2 = read();
	n = read();
	rep(i , 1 , n)a[i].x = read() , a[i].y = read() , a[i].r = read();
	Calc_Line();
	Calc_Limit();
	ans_x = midx , ans_y = midy;
	while((double)clock() / CLOCKS_PER_SEC < 1.5)SA();
	double ans = Calc_distance(ans_x , ans_y , x_1 , y_1);
    printf("%.5f" , ans);
	return 0;
}
```


---

## 作者：EuphoricStar (赞：0)

根据初中数学知识，圆心在 $AB$ 线段的中垂线上。

又因为给定圆与 $AB$ 线段所在直线不交，所以圆心在中垂线的一端极远处完全包含这个给定圆，在另一端极远处与这个给定圆相离。而具体在哪一端只与圆心在 $AB$ 的左侧还是右侧有关。

![](https://z1.ax1x.com/2023/10/16/piCum3q.png)

因此可以二分找到与给定圆外切和内切时圆心的坐标。那么一个给定圆只可能挡住一段连续的坐标。扫描线即可。

[code](https://codeforces.com/contest/887/submission/228357386)

---

## 作者：Kreado (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF887E)。

最不计算几何的一集。

## 思路

我们设 $p_1(x_1,y_1),p_2(x_2,y_2)$，$x_1,x_2,y_1,y_2$ 和题面定义一样。

很显然的一件事，如果一个圆经过了一条线段的两个端点，那么说明这个圆的圆心就在该线段中垂线所在直线上。

那么我们现在就要最小化这个半径，且不与其他圆相交。

不难发现，若一个圆和另一个圆相交，由一个圆心到另一个圆的最短/距离我们不妨设为 $A,B$，那么这个圆的半径取值范围就是 $(-\infty,A]\cup [B,\infty)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/gih6y7ux.png)

如果我们直接算出 $A,B$ 的话，可能比较麻烦，但是我们发现这个具有单调性，所以直接二分求出即可。

对于每个圆我们都这么求一遍，最终我们能得到若干个半径的取值范围，我们直接取最小值即可。

注意在求 $A$ 和 $B$ 的时候，我们设 $P$ 表示当前解决圆的圆心，我们还要判断 $P$ 点在线段 $|p_1p_2|$ 的哪一端，这个我们直接用同向法解决即可。

接下来看代码注释。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int Maxn=4e5+7;
const double inf=1e12;
struct point{
	double x,y;
	point(){}
	point(double x,double y):x(x),y(y){}
	point operator +(const point &a)const{return point(a.x+x,a.y+y);}
	double operator *(const point &a)const{return a.y*x-a.x*y;}
	point operator -(const point &a)const{return point(x-a.x,y-a.y);}
	point operator *(const double &a)const{return point(a*x,y*a);}
}A,B,C,O,k;
struct node{
	double x;int k;
}q[Maxn];
int cnt,n;
inline double mo(const point x){
	return sqrtl(x.x*x.x+x.y*x.y);
}
double l,r,mid,ans=inf;
int main(){
	scanf("%lf%lf%lf%lf",&A.x,&A.y,&B.x,&B.y);
	C=(A+B)*0.5;
	// C AB中点 
	k=B-A;k=k*(1.0/mo(k));
	k=point(-k.y,k.x);
	// 增长率 
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		point p;double R;
		scanf("%lf%lf%lf",&p.x,&p.y,&R);
		bool flg=((p-A)*(B-p)>0);
		// 同向法 
		l=-inf,r=inf;
		for(int i=1;i<=80;i++){
			mid=(l+r)/2;
			O=C+(k*mid);
			// 二分 O 坐标 
			if((mo(p-O)-R>mo(A-O))^flg) l=mid;
			else r=mid;
		}
		q[++cnt]=(node){l,flg?-1:1};
		// 差分 
		l=-inf,r=inf;
		for(int i=1;i<=80;i++){
			mid=(l+r)/2;
			O=C+(k*mid);
			if((mo(A-O)>mo(p-O)+R)^flg) r=mid;
			else l=mid;
		}
		q[++cnt]=(node){r,flg?1:-1};
	}
	q[++cnt]=(node){inf,0},q[++cnt]=(node){-inf,0},q[++cnt]=(node){0,0};
	// 注意加入这几个点值 
	sort(q+1,q+cnt+1,[](node x,node y){return x.x<y.x;});
	int sum=0;
	for(int i=1;i<=cnt;i++){
		if(!sum) ans=min(ans,fabs(q[i].x));
		sum+=q[i].k;
		if(!sum) ans=min(ans,fabs(q[i].x));
	}// 扫描线求前缀和 ，如果 sum=0，说明该点可以被选 
	O=C+(k*ans);
	printf("%.6f",mo(A-O));
	return 0;
}


```


---

