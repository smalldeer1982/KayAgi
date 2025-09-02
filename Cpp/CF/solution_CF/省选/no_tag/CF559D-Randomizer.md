# Randomizer

## 题目描述

给定一个包含$n$个点的凸多边形，等概率选取顶点集中大于等于三的子集形成一个新凸多边形，求新凸多边形内部(不包含边界)整点个数的期望值。

## 样例 #1

### 输入

```
4
0 0
2 0
2 2
0 2
```

### 输出

```
0.2
```

## 样例 #2

### 输入

```
5
0 0
2 0
2 2
1 3
0 2
```

### 输出

```
0.8125
```

# 题解

## 作者：81179332_ (赞：5)

皮克定理：顶点为整点的凸多边形，面积 $=$ 内部整点数 $+$ 边界整点数的一半 $-1$。

所求可转化为求原凸包内部整点数 $-$ 不被凸包包含的整点数期望值

考虑枚举在新的凸多边形上相邻的两个点 $i$ 和 $j$，则显然由点 $i,i+1,i+2\dots j$ 共 $k$ 个点构成的凸包内的整点和 $(i,j)$ 这条边上的整点都不被新凸包包含(假设有 $num$ 个)。

那么对不被新凸包包含的整点数的期望值的贡献即为 $num \times \frac{2^{n-k}-1}{2^n-C_n^0-C_n^1-C_n^2}$。在枚举 $i$ 和 $j$ 的同时维护由 $i,i+1,i+2\dots j$ 组成凸包的面积及边界上整点的数量求出 $num$

观察公式可以发现，当 $k$ 较大时可以忽略，通过实验发现，$k$ 枚举到 $60$ 较为合适。当 $n$ 较大时，原式可以看成 $num \times \frac{1}{2^k}$ 来避免超出 double 范围

```cpp
#include<cctype>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdio>
#define sp putchar(' ')
#define en putchar('\n')
#define ex return 0
#define pprint(x) print(x),sp
#define fprint(x) print(x),en
using namespace std;
//#define getchar() (SS == TT && (TT = (SS = BB) + fread(BB,1,1 << 15,stdin),TT == SS) ? EOF : *SS++)
char BB[1 << 15],*SS = BB,*TT = BB;
bool fl;
inline long long read()
{
	long long x = 0;int f = 1;
	char ch = getchar();
	for(;!isdigit(ch);ch = getchar())
		if(ch == '-')
			f = -1;
	for(;isdigit(ch);ch = getchar())
		x = x * 10 + (ch ^ 48);
	return x * f;
}
inline void print(long long x)
{
	if(x < 0)
	{
		putchar('-');
		x = -x;
	}
	char ch = x % 10 + '0';
	if(x > 9)
		print(x / 10);
	putchar(ch);
}
const int N = 100010;
struct node
{
	double x,y;
	node(double xx = 0,double yy = 0)
	{
		x = xx,y = yy;
	}
	friend node operator - (node u,node v)
	{
		return node(u.x - v.x,u.y - v.y);
	}
	friend double operator * (node u,node v)
	{
		return u.x * v.y - u.y * v.x;
	}
}a[N];
int n;
int _gcd(int a,int b)
{
	return b == 0 ? a : _gcd(b,a % b);
}
int gcd(node u)
{
	return _gcd(abs(u.x),abs(u.y));
}
double Pick_theorem(double s,double t)
{
	return s + 1 - 0.5 * t;
}
double f[110];
#define C2(x) x * (x - 1) * 0.5
double work(int n,int k)
{
	if(n > 100)
		return 1.0 / f[k];
	return (f[n - k] - 1) / (f[n] - 1 - n - C2(n));
}
double S,T;
int main()
{
	n = read();
	for(int i = 0;i < n;i++)
		a[i].x = read(),a[i].y = read();
	f[0] = 1;
	for(int i = 1;i <= 100;i++)
		f[i] = f[i - 1] * 2;
	for(int i = 0;i < n;i++)
	{
		int j = (i + 1) % n;
		S += 0.5 * ((a[i] - a[0]) * (a[j] - a[0]));
		T += gcd(a[j] - a[i]);
	}
	double res = 0;
	for(int i = 0;i < n;i++)
	{
		node pre = a[(i + 1) % n] - a[i];
		double s = 0,t = gcd(pre);
		for(int j = (i + 2) % n,k = 3;k <= 60 && (j + 1) % n != i;j = (j + 1) % n,k++)
		{
			node now = a[j] - a[i];
			node temp = now - pre;
			double num = gcd(now);
			t += num + gcd(temp);
			s += 0.5 * (pre * now);
			res += (Pick_theorem(s,t) + num - 1) * work(n,k);
			t -= num;
			pre = now;
		}
	}
	printf("%.10lf",Pick_theorem(S,T) - res);
}
```

---

## 作者：江户川·萝卜 (赞：2)

给一个不用容斥的简单做法。

Pick 定理：对于一个凸多边形，定义 $S$ 为其面积，$A$ 为内部整点数，$B$ 为边上整点数，则有 $A=S-\frac B2+1$。

利用期望线性性，有 $E A=ES-\frac{EB}2+1$。

由凸多边形面积 $S=\frac12\sum\overrightarrow{V_k}\times\overrightarrow{V_{k+1}}$，得 $ES=\frac12\sum\limits_{i\neq j}{p_{i,j}\overrightarrow{V_i}\times\overrightarrow{V_j}}$。

$EB$ 类似，设 $f(\overrightarrow{V})$ 表示当 $\overrightarrow{V}$ 起点终点均是整点时，该向量上的整点数量（不含终点），即得 $f(\overrightarrow{V})=\operatorname{abs}(\gcd(x_V,y_V))$。则 $B=\sum f\left(\overrightarrow{V_k},\overrightarrow{V_{k+1}}\right)$，得 $EB=\sum\limits_{i\neq j}p_{i,j}f\left(\overrightarrow{V_i}-\overrightarrow{V_j}\right)$。

则 $EA=1+\frac12\sum\limits_{i\neq j}p_{i,j}\left(\overrightarrow{V_i}\times\overrightarrow{V_j}-f\left(\overrightarrow{V_i}-\overrightarrow{V_j}\right)\right)$。

其中 $p_{i,j}$ 表示选出的多边形存在 $\overrightarrow{V_iV_j}$ 这个有向边的概率，记 $k$ 表示顺时针方向 $i$ 到 $j$ 的弧上共几个顶点，则 $p_{i,j}=\dfrac{2^{n-k}-1}{2^n-1-n-\frac{n(n-1)}2}$，这个值在 $n$ 较大的时候近似为 $\dfrac1{2^k}$，在 $k>60$ 时可以忽略，所以只要算 $k\le 60$ 的部分。

复杂度 $O(-n\log V\log \epsilon)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn=1e5+5;
typedef long long ll;
struct vec{
	ll x,y;
	vec(ll x=0,ll y=0):x(x),y(y){}
	inline vec operator - (const vec&o)const{return vec(x-o.x,y-o.y);}
	inline double operator * (const vec&o)const{return x*o.y-y*o.x;}
	inline int sk(){return abs(__gcd(x,y));}
}g[maxn];
double pw[maxn];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n;cin>>n;
	double ans=0;
	for(int i=pw[0]=1;i<=n;i++) pw[i]=pw[i-1]*2;
	double ww=pw[n]-1-n-n*1ll*(n-1)/2;
	for(int i=1;i<=n;i++) cin>>g[i].x>>g[i].y;
	for(int i=1;i<=n;i++)
	for(int j=i%n+1,k=2;j!=i&&k<=60;j=j%n+1,k++)
		ans+=(g[i]*g[j]-(g[j]-g[i]).sk())*(n<100?(pw[n-k]-1)/ww:1/pw[k]);
	cout<<fixed<<setprecision(10)<<ans/2+1<<'\n';
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2800}$
---
神仙题，把精度玩这么花第一次见。

---
### 皮克定理：

定理内容是 $S=a+\dfrac{b}{2}-1$，其中 $S$ 表示一个顶点全都在格点上的多边形的面积，$a$ 表示多边形内部的格点数量，$b$ 为边上的格点数。

一种可行的证明是从矩形开始，拓展到直角三角形，再到一般三角形，最后到所有格点多边形。不严谨的过程大体如下：

以一个边平行于坐标轴的矩形的左下角为 $(0,0)$，右上角为 $(x,y)$，则矩形面积为 $S=xy$，矩形内部格点为 $a=(x-1)(y-1)$，恰好在矩形边上的格点为 $b=4+2(x-1)+2(y-1)=2x+2y$，$a+\dfrac{b}{2}-1=xy=S$。

拓展到两直角边平行于坐标轴的直角三角形，斜边的两顶点坐标为 $(x,0)$ 和 $(0,y)$，$S=\dfrac{xy}{2}$，$a=\dfrac{(x-1)(y-1)-(\gcd(x,y)+1-2)}{2}=\dfrac{xy-x-y-\gcd(x,y)+2}{2}$，$b=\gcd(x,y)+x+y$，$a+\dfrac{b}{2}-1=\dfrac{xy}{2}=S$。

对于任意三角形，只需要将其补成一个矩形，再从其中扣掉三个三角形就行。转化为证明从一个满足皮克定理的图形中扣去一个满足皮克定理的图形仍然满足。

虽然此处只需要用到直角减直角，但是不妨将问题直接拓展任意图形减去任意图形。令较大的图形为面积为 $S_1$，内部点的数量为 $a_1$，边上的点的数量为 $b_1$，较小的分别为 $S_2,a_2,b_2$，其中令小的与大的重合的部分边上的点数为 $b_2'$，未重合的未 $b_2''$，明显有 $b_2'+b_2''=b_2$。

新的图形边上的点数为 $b_0=b_1-b_2'+b_2''+2$，内部的点的数量为 $a_0=a_1-a_2-b_2''$，且 $S_0=S_1-S_2=a_1-a_2+\dfrac{b_1-b_2}{2}=a_0+\dfrac{b_0}{2}-1$。

很有趣的事情是证明外面拼接一个的过程和上面几乎一模一样，可以理解为符号的变化。

最后用一下归纳法就行。

---
### 解题思路：

然后终于开始做这道题了。

直接弄出任意的多边形不好计算，将问题转化为整个图形内部点的数量减去不在多边形内点的数量的期望。好处是这样所有的不在多边形内的点一定是由若干个连续的区间构成的，利用期望的线性性就能单独算出来之后再加起来了。

有了皮克公式，希望得到的内部点的数量的期望就可以转化为 $a=S-\dfrac{b}{2}+1$。然后就有一个很明显的的 $O(n^2)$ 做法，枚举每一段区间，计算出这个区间对于结果的贡献。写出这个式子，不妨设当前考虑的是点区间 $[i,i+k-1]$ 构成的凸包。则选出区间的概率为 $\dfrac{2^{n-k}-1}{2^n-C_n^0-C_n^1-C_n^2}$。

然后就是这个题神仙的地方。发现当 $k$ 较大的时候值其实非常小，当 $k\ge 60$ 的时候，整个式子的值也远远小于要求的精度，不妨直接忽略。

细节上在 $n$ 较大的时候，即使是算出分别分子分母相除也无法做到，这时候就需要舍弃一些精度，将式子直接约等于 $2^{-k}$。 

还有就是不要把常数写得太大，虽然复杂度是 $O(n\log n)$ 的，但是这里面本身就已经带了一个 $60$ 的常数，最大公约数能存的就尽量存一下吧。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=200005;
int n,x[MAXN],y[MAXN];
double ans,pow[105],S,cnt,ds,dcnt,lx,ly,dans,g,lg;
int _gcd(int a,int b){
	if(b==0)return a;
	return _gcd(b,a%b);
}
int gcd(int a,int b){
	if(a<0)a=-a;if(b<0)b=-b;
	return _gcd(a,b);
}
int s_calc(int x1,int y1,int x2,int y2){
	return x1*y2-x2*y1;
}
double f_calc(int k){
	if(n>100)return 1.0/pow[k];
	return (pow[n-k]-1)/(pow[n]-1-n-n*(n-1)/2);
}
double num_calc(int s2,int t){
	return 0.5*(s2-t)+1.0;
}
signed main(){
	pow[0]=1;
	for(int i=1;i<=100;i++)pow[i]=pow[i-1]*2;
	
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&x[i],&y[i]);
	for(int i=2;i<=n;i++)x[i]-=x[1],y[i]-=y[1];x[1]=y[1]=0;
	for(int i=1;i<=n;i++)x[i+n]=x[i],y[i+n]=y[i];
	
	for(int i=2;i<=n+1;i++){
		S+=s_calc(x[i-1],y[i-1],x[i],y[i]);
		cnt+=gcd(x[i]-x[i-1],y[i]-y[i-1]);
	}
	ans=num_calc(S,cnt);
	
	for(int i=1;i<=n;i++){
		lx=x[i+1]-x[i];ly=y[i+1]-y[i];
		ds=0;dcnt=2*gcd(lx,ly);
		lg=gcd(lx,ly);
		for(int j=i+2;j<=i+min(n-2,60ll);j++){
			ds+=s_calc(lx,ly,x[j]-x[i],y[j]-y[i]);
			g=gcd(x[j]-x[i],y[j]-y[i]);
			dcnt=dcnt-lg+g+gcd(x[j]-x[j-1],y[j]-y[j-1]);
			dans+=f_calc(j-i+1)*(num_calc(ds,dcnt)+g-1);
			lg=g;lx=x[j]-x[i];ly=y[j]-y[i];
		}
	}
	printf("%.9lf",ans-dans);
	return 0;
}
```


---

## 作者：Leap_Frog (赞：1)

### Link.
[Codeforces](https://codeforces.com/problemset/problem/559/D)  
[Luogu](https://www.luogu.com.cn/problem/CF559D)  

### P.S.
太nb了  

### Description.
给定一个凸包，随机选一个点数 $\ge3$ 的点集。  
问选出点集构成凸包内整点数的期望。  
精度 $10^{-9}$  

### Solution.
首先，凸包内整点显然想到皮克定理。  
皮克定理是 $Area=Cnt_{inside}+\frac{Cnt_{edge}}{2}-1$。  
然后如果求凸包内好像牵扯的信息比较多，可以考虑容斥。  
答案就是原凸包内的整点减去被切掉的凸包内整点。  
然后被切掉凸包肯定是原凸包上的一段序列。  
于是显然就有一个 $O(n^2)$ 做法，就考虑枚举新凸包的下一个点。  
可以直接维护，概率是 $\frac{2^{n-k}-1}{2^n-1-n-n\times(n-1)\div 2}$，其中 $k$ 表示选点个数，$-1$ 表示剩下的不能全不选。  

但是怎么从 $O(n^2)$ 优化到更优呢。  
**哈哈，我们发现 $\frac{1}{60}\le 10^{18}$，所以直接枚举后 $60$ 个点即可，复杂度变成了 $O\left(n\log\left(\frac{10^9}{10^{-9}}\right)\right)$，直接 A 了！**  

细节：`long double` 也无法处理 $2^{100}$，但是观察上式，发现 $k$ 比较小，$n$ 比较大的时候可以把分子近似成 $2^{n-k}$，分母近似成 $2^n$，所以可以把概率当成 $\frac 1{2^k}$

### Coding.
不会可以参考代码注释  
```cpp
struct vec
{
	int x,y;
	inline vec operator+(vec b) {return(vec){x+b.x,y+b.y};}
	inline vec operator-(vec b) {return(vec){x-b.x,y-b.y};}
	inline ll operator*(vec b) {return 1ll*x*b.y-1ll*y*b.x;}
	inline int count() {return abs(__gcd(x,y));}
	//count 表示左闭右开的线段上有多少个整点，经典结论，不表。
}a[N];
db pw[N];vec a[N];
inline db gl(int k)
{//算的概率，2^100 远远大于 100^2
	if(n>100) return 1.0/pw[k];
	return (pw[n-k]-1)/(pw[n]-1-n-1.0*n*(n-1)/2);
}
int main()
{
	read(n);for(int i=1;i<=n;i++) read(a[i].x,a[i].y);
	pw[0]=1;for(int i=1;i<=100;i++) pw[i]=pw[i-1]*2;
	ll Cn=0,S=0;for(int i=1;i<=n;i++) S+=a[i]*a[i%n+1],Cn+=(a[i%n+1]-a[i]).count();//算出总边界点数和面积
	db del=0;for(int i=1;i<=n;i++)
	{
		ll s=a[i]*a[i%n+1],cn=(a[i%n+1]-a[i]).count();
		for(int k=3,j=(i+1)%n+1;k<=60&&j%n+1!=i;k++,j=j%n+1)
		{
			s+=a[(j-2+n)%n+1]*a[j],cn+=(a[j]-a[(j-2+n)%n+1]).count();
			del+=gl(k)*(s+a[j]*a[i]-cn+(a[i]-a[j]).count())/2.0;
			//注意这里式子化简过了
			//原来应该是(s+a[j]*a[i]-cn-(a[i]-a[j]).count()+2)/2.0+(a[i]-a[j]).count()-1
			//表示内部整点数加上新凸包上一条边删掉的整点数
#ifdef debug
			printf("gl : %.10Lf\n",gl(k));
			printf("del : %.10lf\n",(s+a[j]*a[i]-cn+(a[i]-a[j]).count())/2.0);
#endif
		}
	}
	return printf("%.10Lf\n",(S+2-Cn)/2.0-del),0;
}
```
完结撒花

---

## 作者：DaiRuiChen007 (赞：0)

# CF559D 题解

[Problem Link](https://www.luogu.com.cn/problem/CF559D)

**题目大意**

> 给一个大小为 $n$ 的凸多边形，随机选 $k$ 个点（$k\ge 3$），求 $k$ 个点构成凸包内部（不包含边界）上点数的期望。
>
> 数据范围：$n\le 10^5$。

**思路分析**

首先考虑如何算一个多边形内部整点的数量，用皮克定理 $S=a+\dfrac b2-1$，得到 $a=S-\dfrac b2+1$，其中 $S$ 是多边形面积，$b$ 是边界上整点数量。

考虑容斥，先算整个多边形中整点的数量，然后容斥掉每一对 $i,j$ 在选出的凸包上相邻所产生的一个小多边形内整点的数量。

对于一对 $i,j$，记 $k=j-i+1$，那么 $i,j$ 在选出多边形上相邻的概率就是 $\dfrac{2^{n-k}}{2^n-1-n-n\times (n-1)/2}$。

注意到这个函数在  $n$ 很大的时候可以近似为 $2^{-k}$，由于本题是输出实数，因此对于 $k\ge 60$ 的项都可以忽略，因此我们关心的 $(i,j)$ 只有 $\mathcal O(n)$ 对，枚举 $i$ 递推即可。

时间复杂度 $\mathcal O(n\log V)$，瓶颈在求线段上整点个数（即 $\gcd(x,y)$）。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int MAXN=1e5+5;
inline int gcd(int x,int y) { return y?gcd(y,x%y):x; }
struct Vect {
	int x,y;
	inline friend Vect operator -(Vect u,Vect v) { return {u.x-v.x,u.y-v.y}; }
	inline friend double operator *(Vect u,Vect v) { return 0.5*abs(u.x*v.y-u.y*v.x); }
	inline int len() { return gcd(abs(x),abs(y)); }
}	a[MAXN];
inline double count(double area,double dia) {
	return area-dia*0.5+1;
}
double pw[100];
inline double prob(int n,int k) {
	if(n>=100) return 1/pw[k];
	return (pw[n-k]-1)/(pw[n]-1-n-n*(n-1)/2);
}
signed main() {
	pw[0]=1;
	for(int i=1;i<100;++i) pw[i]=pw[i-1]*2;
	int n;
	scanf("%lld",&n);
	for(int i=0;i<n;++i) scanf("%lld%lld",&a[i].x,&a[i].y);
	double area=0,dia=0;
	for(int i=0;i<n;++i) {
		area+=(a[i]-a[0])*(a[(i+1)%n]-a[0]);
		dia+=(a[i]-a[(i+1)%n]).len();
	}
	double ans=count(area,dia);
	for(int i=0;i<n;++i) {
		double dia=(a[(i+1)%n]-a[i]).len(),area=0;
		for(int j=(i+2)%n,k=(i+1)%n,d=3;d<=60&&(j+1)%n!=i;++d,j=(j+1)%n,k=(k+1)%n) {
			area+=(a[j]-a[i])*(a[k]-a[i]);
			dia+=(a[j]-a[k]).len();
			ans-=(count(area,dia+(a[j]-a[i]).len())+(a[j]-a[i]).len()-1)*prob(n,d);
		}
	}
	printf("%.9Lf\n",ans);
	return 0;
}
```

---

