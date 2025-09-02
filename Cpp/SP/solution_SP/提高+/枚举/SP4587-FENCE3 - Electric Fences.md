# FENCE3 - Electric Fences

## 题目描述

　　农夫约翰已经决定建造电网。他已经把他的农田围成一些奇怪的形状，现在必须找出安放电源的最佳位置。
  
　　对于段电网都必须从电源拉出一条电线。电线可以穿过其他电网或者跨过其他电线。电线能够以任意角度铺设，从电源连接到一段电网的任意一点上（也就是，这段电网的端点上或者在其之间的任意一点上）。这里所说的“一段电网”指的是呈一条线段状的电网，并不是连在一起的几段电网。若几段电网连在一起，那么也要分别给这些电网提供电力。
  
　　已知所有的 F（1 <= F <= 150）段电网的位置（电网总是和坐标轴平行，并且端点的坐标总是整数，0 <= X,Y <= 100）。你的程序要计算连接电源和每段电网所需的电线的最小总长度，还有电源的最佳坐标。
  
　　电源的最佳坐标可能在农夫约翰的农田中的任何一个位置，并不一是整数。

## 样例 #1

### 输入

```
3
0 0 0 1
2 0 2 1
0 3 2 3```

### 输出

```
1.0 1.6 3.7```

# 题解

## 作者：_maojun_ (赞：6)

为什么要用模拟退火……

---

这题可以先猜一个结论，设当电源在 $(x,y)$ 时连接所有电线的最短长度为 $f(x,y)$，则在 $x$ 相同的或 $y$ 相同的切面上，$f(x,y)$ 是凹函数的。

那么就可以二分套三分的算，第一个二分找令 $\min\limits_{y\in\mathbb{R}}(f(x,y))$ 最小的 $x$，第二个在 $x$ 下三分找令 $f(x,y)$ 最小的 $y$，就可以找到 $f(x,y)$ 的最小值。

$f(x,y)$ 为 $(x,y)$ 到每条线段的距离之和。推一下线段到点的式子，注意一下奇奇怪怪的特判就可以了。

```cpp
db dis(db x1,db y1,db x2,db y2){return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));}
db distan(int t,db x,db y){
	db a=dis(lx[t],ly[t],rx[t],ry[t]),b=dis(x,y,lx[t],ly[t]),c=dis(x,y,rx[t],ry[t]);
	if(b>c)swap(b,c);
	if(a*a+b*b<=c*c||a+b==c)return b;
	if(a==b+c)return 0;
	db s=(a+b+c)/2;
	return sqrt(s*(s-a)*(s-b)*(s-c))/a*2;
}
db calc(db x,db y){db sum=0;for(int i=1;i<=n;i++)sum+=distan(i,x,y);return sum;}
```

然后所以总体的时间复杂度就只有 $O(n\log^3n)$ 了（算距离的时候开根多一个 $\log$）。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define y1 _
using namespace std;

using db=double;
const int MAXN=155;
const db eps=1e-3;
int n,lx[MAXN],ly[MAXN],rx[MAXN],ry[MAXN];
db ansx=0,ansy=0,miny=0;

db dis(db x1,db y1,db x2,db y2){return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));}
db distan(int t,db x,db y){
	db a=dis(lx[t],ly[t],rx[t],ry[t]),b=dis(x,y,lx[t],ly[t]),c=dis(x,y,rx[t],ry[t]);
	if(b>c)swap(b,c);
	if(a*a+b*b<=c*c||a+b==c)return b;
	if(a==b+c)return 0;
	db s=(a+b+c)/2;
	return sqrt(s*(s-a)*(s-b)*(s-c))/a*2;
}
db calc(db x,db y){db sum=0;for(int i=1;i<=n;i++)sum+=distan(i,x,y);return sum;}
void binary_searchY(db x){	// 找最优 y
	db l=0,r=100,lm,rm;
	while(r-l>eps){
		lm=l+(r-l)/3,rm=r-(r-l)/3;
		if(calc(x,lm)>calc(x,rm))miny=l=lm;
		else r=rm;
	}
}
void binary_searchX(){		// 找最优 x
	db l=0,r=100,mid;
	while(r-l>eps){
		mid=(l+r)/2;binary_searchY(mid);ansy=miny; 
		if(calc(mid,miny)<calc(mid-eps,miny))ansx=l=mid;	// 在最优的 y 上比较判断在最优解在那个区间。
		else r=mid;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d%d",&lx[i],&ly[i],&rx[i],&ry[i]);
	binary_searchX();
	printf("%.1lf %.1lf %.1lf\n",ansx,ansy,calc(ansx,ansy));
	return 0;
}
```

好像比模拟退火写得短也好写多了（而且跑得快多了）。

---

upd 2023.1.25 之前的证明是有问题的，其实早就该改，但是太懒了（雾

之前是因为没有看到题目的一句话：电网总是和坐标轴平行。

~~我谔谔那我写个怎么乱七八糟的算距离函数干什么。~~

线段是和坐标轴垂直的，所以 $f(x,y)$ 为三维凸函数，像一座山峰（自行脑补）。显然结论成立。

---

## 作者：Durancer (赞：4)

### 前言

适合模拟退火的入门后的题目，多了一些计算函数的技巧。

### 思路

首先我们要看清楚，只有斜率为 $1$ 或者 $0$ 的 **线段**，这是一个计算的关键点。

对于预处理，我们首先处理出每一个线段是竖直的还是水平的，横坐标相等为竖直，纵坐标相等为水平。还有一点要注意的是，最好是把不相等的那个坐标从小到大排，便于判断。

计算函数的设计是最关键的：

对于水平的线段，如果当前随机到的点的横坐标不在这个线段的左右横坐标的范围内，那么就省去判断，在这个点到线段左右两端点的距离中选一个较小的即可。

如果在范围内，那么就直接取纵坐标的差值的绝对值即可。

对于竖直的线段同理。

初温设置在 $2020$ 左右，降温系数 $\text{d=0.996}$，末温为 $10^{-10}$ ，可以通过本题，表示不需要用种子=_=。

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int N=2e2+9;
const double d=0.996;
const double lim=1e-10;
double sx[N],tx[N],sy[N],ty[N];
bool k[N];//false 是平行于 x 轴;
//true 是垂直于 y 轴 
double ans;
double ansx;
double ansy;
double limx;
double limy;
int n;
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
}
double gougu(double ax,double ay,double bx,double by)
{
	return sqrt((ax-bx)*(ax-bx)+(ay-by)*(ay-by));
}
double calc(double x,double y)
{
	double ret=0;
	for(int i=1;i<=n;i++)
	{
		if(!k[i])//水平
		{
			if(x>tx[i] or x<sx[i])//不能构成垂直 
				ret+=min(gougu(x,y,sx[i],sy[i]),gougu(x,y,tx[i],ty[i]));
			else ret+=fabs(y-sy[i]);//一条竖直的线 
		}
		else if(k[i])//垂直
		{
			if(y>ty[i] or y<sy[i])//不能构成垂直
				ret+=min(gougu(x,y,sx[i],sy[i]),gougu(x,y,tx[i],ty[i]));
			else ret+=fabs(x-sx[i]);	
		} 
	}
	return ret;
}
void SA()
{
	double T=2020;
	while(T>lim)
	{
		double x=limx+((rand()<<1)-RAND_MAX)*T;
		double y=limy+((rand()<<1)-RAND_MAX)*T;
		double tmp=calc(x,y);
		double del=tmp-ans;
		if(del<0)
		{
			ansx=limx=x;
			ansy=limy=y;
			ans=tmp;
		}
		else if(exp(-del/T)>(double)rand()/RAND_MAX)
		{
			limx=x;
			limy=y;
		}
		T*=d;
	}
}
void work()
{
	limx/=2.0*n;
	limy/=2.0*n;
	ansx=limx;
	ansy=limy;
	ans=calc(ansx,ansy);
	SA();
	SA();
	SA();
	SA();
	SA();
	SA();
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf",&sx[i],&sy[i]);
		scanf("%lf%lf",&tx[i],&ty[i]);
		limx+=sx[i]+tx[i];
		limy+=sy[i]+ty[i];
		if(sx[i]==tx[i])//竖直
		{
			k[i]=true;
			if(sy[i]>ty[i])
				swap(sy[i],ty[i]);
		}
		else if(sy[i]==ty[i])//水平，Q:会不会出现点？ 
		{
			k[i]=false;
			if(sx[i]>tx[i])//保证递增好判断 
				swap(sx[i],tx[i]);
		}
	}
	work();
	printf("%.1lf %.1lf %.1lf",ansx,ansy,ans); 
	return 0;
}
```

---

## 作者：挪威的森林 (赞：4)

# 模拟退火
***

> 模拟退火模板，主要就是处理距离那点。  还有这题没有明确说保留一位小数，保留一位小数就行了。

```c

/*
exp(-de/t)*RAND_MAX>rand()
模拟退火主要就是这个式子
*/
#include<bits/stdc++.h>
using namespace std;
struct node{
    int x,y,xx,yy;
}s[1010];
double ansx,ansy,ansz,answ,down=0.996;
int n;
namespace FIFO{
	char ch,B[1<<20],*S=B,*T=B;
	#define getc() (S==T&&(T=(S=B)+fread(B,1,1<<20,stdin),S==T)?0:*S++)
	#define isd(c) (c>='0'&&c<='9')
	int aa,bb;int F(){
		while(ch=getc(),!isd(ch)&&ch!='-');ch=='-'?(aa=bb=0):(aa=ch-'0',bb=1);
		while(ch=getc(),isd(ch))aa=aa*10+ch-'0';return bb?aa:-aa;
	}
}
#define gi FIFO::F()
double get(double a,double b){
    double res=0;
    for(int i=1;i<=n;i++){
        int x=s[i].x,y=s[i].y,xx=s[i].xx,yy=s[i].yy;
        if(x==xx){ //垂直的
            if(b>=min(y,yy)&&b<=max(y,yy)){
                res+=fabs(a-x);
            }
            else{
                double dis1=sqrt((x-a)*(x-a)+(y-b)*(y-b));
                double dis2=sqrt((x-a)*(x-a)+(yy-b)*(yy-b));
                res+=min(dis1,dis2);
            }
        }
        else{  //水平的
            if(a>=min(x,xx)&&a<=max(x,xx)){
                res+=fabs(y-b);
            }
            else{
                double dis1=sqrt((x-a)*(x-a)+(y-b)*(y-b));
                double dis2=sqrt((xx-a)*(xx-a)+(y-b)*(y-b));
                res+=min(dis1,dis2);
            }
        }
    }
    return res;
}
void mt(){ //模拟退火
    double t=3000; //设定温度
    while(t>1e-15){
        double nx=ansx+(rand()*2-RAND_MAX)*t;//随机产生一个新的数
        double ny=ansy+(rand()*2-RAND_MAX)*t;
        double now=get(nx,ny); //弄出解进行比较
        double cha=now-answ; //求出解的差值
        if(cha<0){ //现在的解更优 那我直接跳
            ansx=nx,ansy=ny;
            answ=now;
        }
        //  现在的解不一定是最优的，我不能不跳。所以我小概率跳。
        //温度越低 跳的概率越小
        else if(exp(-cha/t)*RAND_MAX>rand()){ //关键点   随机调
            ansx=nx,ansy=ny;  //这里不需要更新答案  因为不一定最优
            //一定概率进行跳  也可能会跳
        }
        t=t*down;
    }
}
void solve(){
    mt();
    mt();
    mt();
    mt();
}
int main(){
    n=gi;
    for(int i=1;i<=n;i++){
        s[i].x=gi,s[i].y=gi,s[i].xx=gi,s[i].yy=gi;
    }
    ansx=0,ansy=0;
    answ=get(ansx,ansy);
    solve();
    printf("%.1lf %.1lf %.1lf\n",ansx,ansy,answ);
//    printf("%.10lf",answ);
}
/*
3
0 0 0
3 0 0
0 4 0
4
0 0 0
1 0 0
0 1 0
0 0 1
*/
```


---

## 作者：Creroity (赞：3)

发现一道**模拟退火**的入门题。

有兴趣的朋友们可以去看看[这题](https://www.luogu.com.cn/problem/P1337)。

### 众所周知模拟退火的核心是求当先目标解的函数值。

而这道题目的函数值求法应该最多只能算是橙题吧……

因为题目中已经说了所有的电网都是平行于坐标轴的，所以我们只需要计算每条电网到此时枚举的电源位置的最短距离就行。

那么处理的方法显而易见就是分成两种情况：

第一种情况就是当当前电网平行于 x 轴时。

第二种情况则是当当前电网平行于 y 轴时。

每种情况又需要分两种不同的情况：

第一种是电源在线段的垂线上，其次是不在线段的垂线上。

那么这就是函数值计算点主要代码。

其次就是模拟退火的部分。

这部分主要就是模板，记下来就是了，需要改变的地方并不多，所以就不多讲了，都打在注释里吧！

#### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double down=0.996;//降温系数 
double ansx,ansy,ansl;//记录结果的函数 
struct node{
	int hx,tx,hy,ty;
}f[155];
double getlen(double x,double y){
	double res=0;
	for(int i=1;i<=n;i++){
		int a=f[i].hx,b=f[i].hy,c=f[i].tx,d=f[i].ty;
		if(a==c){//平行于 y 轴 
			if(y>=min(b,d)&&y<=max(b,d)){//当电源在线段垂线上 
				res+=fabs(a-x);
			}
			else{
				double head=sqrt((x-a)*(x-a)+(y-b)*(y-b));//否则用距离公式计算两点距离 
				double tail=sqrt((x-a)*(x-a)+(y-d)*(y-d));//算另一端离电源的距离 
				res+=min(head,tail);//求最小值 
			}
		}
		else{//平行于 x 轴，其余同上 
			if(x>=min(a,c)&&x<=max(a,c)){
				res+=fabs(b-y);
			}
			else{
				double head=sqrt((x-a)*(x-a)+(y-b)*(y-b));
				double tail=sqrt((x-c)*(x-c)+(y-b)*(y-b));
				res+=min(head,tail);
			}
		}
	}
	return res;//返回答案 
}
void sa(){
	double t=3000;//初始温度 
	while(t>1e-15){
		double nextx=ansx+(rand()*2-RAND_MAX)*t;//随机生成下一个目标点的位置 
		double nexty=ansy+(rand()*2-RAND_MAX)*t;
		double nextl=getlen(nextx,nexty);//计算函数值 
		double f=nextl-ansl;//求出函数值的差 
		if(f<0){//找到更优解 
			ansx=nextx;
			ansy=nexty;
			ansl=nextl;
		}
		else if(exp(-f/t)*RAND_MAX>rand()){//核心，按照概率接受此时的次优解 
			ansx=nextx;
			ansy=nexty;//注意，此处不需要记录答案的函数值，因为不是最优解 
		}
		t*=down;//降温 
	}
}
int main(){
	srand(rand());//玄学 rand 
	srand(rand());
	srand(rand());
	srand(rand());
	cin>>n;
	for(int i=1;i<=n;i++)cin>>f[i].hx>>f[i].hy>>f[i].tx>>f[i].ty;
	ansl=getlen(ansx,ansy);//求初始函数值 
	sa();//模拟退火 
	printf("%.1lf %.1lf %.1lf",ansx,ansy,ansl);//输出保留一位小数 
	return 0;
}
```
~~卑微求个赞~~

---

## 作者：blackjack (赞：2)

这题实际上没有什么好的方案。
首先可以想到的是枚举，虽然显得有点傻。然而这题数据有精度要求，数据量比较大，枚举必定超时。
但是很容易就发现，结果大体上具有凹凸性，就是说，假设f(x,y)表示在(x,y)点的ans，f(x,y)大体上具有凹凸性。
那么就可以三分了。由于是二维的，所以三分套三分，很快的。
```cpp
#include <bits/stdc++.h>

using namespace std;

int f;//电网的数量;
const double eps = 1e-3;
struct fen{
   int x1;
   int y1;
   int x2;
   int y2;
};
fen ef[160];//电网组
double l,r;
int minnx = 1000, maxnx = -1000;
int minny = 1000, maxny = -1000;
double ansx, ansy;
double ansd = 10000000;
void thrx(double l,double r);
double thry(double a);
double getmid(double x);
double poww(double x);

int main(){
   cin >> f;
   for (int i = 1; i <= f; i++){
      cin >> ef[i].x1 >> ef[i].y1 >> ef[i].x2 >> ef[i].y2;
      if (ef[i].x1 < minnx) minnx = ef[i].x1;
      if (ef[i].x2 < minnx) minnx = ef[i].x2;
      if (ef[i].x1 > maxnx) maxnx = ef[i].x1;
      if (ef[i].x2 > maxnx) maxnx = ef[i].x2;
      if (ef[i].y1 < minny) minny = ef[i].y1;
      if (ef[i].y2 < minny) minny = ef[i].y2;
      if (ef[i].y1 > maxny) maxny = ef[i].y1;
             if (ef[i].y2 > maxny) maxny = ef[i].y2;
   }//读入时记录三分范围;
   l = minnx;
   r = maxnx;
   thrx(l,r);//卡范围枚举，更优。
   printf("%.1lf %.1lf %.1lf\n", ansx, ansy, ansd);
   return 0;
}

double getmid(double x,double y){//求距离之和。
   double res = 0;
   for (int i = 1; i <= f; i++){
      double tmp = min(sqrt(poww(ef[i].x1 - x) + poww(ef[i].y1 - y)), sqrt(poww(ef[i].x2 - x) + poww(ef[i].y2 - y)));
      if (ef[i].y1 == ef[i].y2 && ef[i].x1 <= x && x <= ef[i].x2)
      tmp = min(tmp, fabs(ef[i].y1 - y));
      if (ef[i].x1 == ef[i].x2 && ef[i].y1 <= y && y <= ef[i].y2)
      tmp = min(tmp, fabs(ef[i].x1 - x));
      res += tmp;
   }
   return res;
}

double poww(double x){
   return x * x;
}
void thrx(double l,double r){//大三分x，可以和下面的倒位。
   while (fabs(l-r) >= eps){
      double k = (r-l)/3.0;
      double mid1 = l + k;
      double mid2 = r - k;
      if (thry(mid1) < thry(mid2)) r = mid2;
      else
         l = mid1;
   }
}

double thry(double a){//三分y，返回长度。
   double l = 0, r = 100;
   while (fabs(l-r) >= eps){
      double k = (r-l)/3.0;
      double mid1 = l + k;
      double mid2 = r - k;
      if (getmid(a,mid1) < getmid(a,mid2)) r = mid2;
      else
         l = mid1;
   }
   double t = getmid(a,l);
   if (ansd > t){//更新。
      ansd = t;
      ansx = a;
      ansy = l;
   }
   return t;
}
```
代码比较丑，凑合看吧，我同学写的。
当然，我们既然已经发现了凹凸性，那么也就没有什么必要三分了，三分代码比较复杂。我们完全可以直接枚举，不过，先枚举大致范围，然后对结果进行排序，再在结果小的几个里面进一步寻找ans。这是有点像模拟退火的算法（这题也确实可以用模拟退火，但是你愿意靠RP获胜吗?),但是我觉得更像迭代加深。（当然，完全不是）
以下是我自己大的程序
```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
#include<algorithm>

using namespace std;

struct line{
	double bex;//beginx
	double bey;
	double enx;//endx
	double eny;
	double dir;//direction
}A[160];

struct ANS{
	double x;
	double y;
	double l;
}TE[10001];
int n;

inline double gpow(double x){
	return x*x;
}

inline ANS cal(int XX,int YY){
	double X=(double)XX/10,Y=(double)YY/10;
	ANS tans;
	tans.l=0;
	double tlength;
	for (int i=1;i<=n;i++){
		if (A[i].bey<Y and A[i].eny>Y){
			tans.l+=abs(A[i].bex-X);
		}
		else if (A[i].bex<X and A[i].enx>X){
			tans.l+=abs(A[i].bey-Y);
		}
		else{
			double	tx=min(abs(A[i].bex-X),abs(A[i].enx-X)),
			ty=min(abs(A[i].bey-Y),abs(A[i].eny-Y));
			tans.l+=sqrt(tx*tx+ty*ty);
		}
	}
	tans.x=X;
	tans.y=Y;
	return tans;
}

bool cmpTE(ANS a,ANS b){
	return a.l<=b.l;
}

int main(){
	ANS temp,ans;
	cin>>n;
	double maxx=0,maxy=0,minx=11111.111,miny=11111.111;
	for (int i=1;i<=n;i++){
		cin>>A[i].bex>>A[i].bey>>A[i].enx>>A[i].eny;
		if (A[i].bex==A[i].enx)
			A[i].dir=0;
		else
		A[i].dir=1;//横
	}
	int t=0;
	for (double i=1.0;i<=100;i=i+1.0){
		for (double j=1.0;j<=100;j=j+1.0){
			temp=cal(i*10,j*10);
			t++;
			TE[t]=temp;
		}
	}
	sort(TE,TE+t,cmpTE);
	ans.l=111111.11111;
	for (int i=1;i<=50;i++){
		int tx=(TE[i].x-1)*10,ty=(TE[i].y-1)*10;
		for (int xx=tx;xx<=tx+20;xx=xx+1){
			for (int yy=ty;yy<=ty+20;yy=yy+1){
				temp=cal(xx,yy);
				if (temp.l<ans.l)
					ans=temp;
			}
		}
	}
	printf("%.1lf %.1lf %.1lf \n",ans.x,ans.y,ans.l);
	return 0;
}

```

---

## 作者：Buried_Dream (赞：1)

## Solution

我们考虑模拟退火。

我们随机一个点，不断的统计答案即可。

首先只有水平和竖直的线，我们分类讨论。

水平的线，当点在范围内，也就是点能与线垂直的时候，答案就是垂线的长度。

如果不在范围内，到两个端点的距离取个 $\min$ 就行了。

竖直的线同理。

对于模拟退火，概率性接受的式子要和 $T$ 和 $del$ 有关，很多人却不知道为什么。

这是因为越到后面，$T$ 越小，$del$ 越小，接受的概率就越小。

```cpp
/*
	Work by: TLE_Automation
*/
#include<cmath>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL long long
#define int long long
using namespace std;

const int N = 1e6 + 10;
const int MAXN = 2e5 + 10;

inline char readchar() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline int read() {
#define readchar getchar
	int res = 0, f = 0;char ch = readchar();
	for(; !isdigit(ch); ch = readchar()) if(ch == '-') f = 1;
	for(; isdigit(ch); ch = readchar()) res = (res << 1) + (res << 3) + (ch ^ '0');
	return f ? -res : res;
}

inline void print(int x) {
	if (x < 0 ) putchar('-'), x = -x;
	if (x > 9 ) print(x / 10);
	putchar(x % 10 + '0');
}

inline double getin() {
	double x;
	scanf("%lf", &x);
	return x;
}

struct node {
	double sx, sy, ex, ey;
}a[MAXN];

int n;
int vis[MAXN];

double nowx, nowy, limx, limy, ansx, ansy;
double nowans, ans;

inline double dis(double a, double b, double c, double d) {
	return sqrt((c - a) * (c - a) + (d - b) * (d - b));
}

double Calc(double x, double y) {
	double Sum = 0.0;
	for(int i = 1; i <= n; i++) {
		double A = 0.0;
		if(vis[i] == 2) {
			if(a[i].sx <= x  && x <= a[i].ex) {
//				A = sqrt((dis(a[i].sx, a[i].sy, x, y) * dis(a[i].sx, a[i].sy, x, y))  - ((x - a[i].sx) * (x - a[i].sx)));
				A = fabs(y - a[i].sy);
			} 
			else {
				A = min(dis(a[i].sx, a[i].sy, x, y), dis(a[i].ex, a[i].ey, x, y));
			}
		}
		else if(vis[i] == 1) {
			if(a[i].sy <= y && y <= a[i].ey) {
//				A = sqrt((dis(a[i].sx, a[i].sy, x, y) * dis(a[i].sx, a[i].sy, x, y))  - ((x - a[i].sx) * (x - a[i].sx)));
				A = fabs(x - a[i].sx);
			}
			else {
				A = min(dis(a[i].sx, a[i].sy, x, y), dis(a[i].ex, a[i].ey, x, y));
			}
		}
		Sum += A;
	}
	return Sum;
}

void SA() {
	#define down 0.999
	#define lim 1e-12
	double T = 2022;
	while(T >= lim) {
		nowx = ansx +( (rand() << 1) - RAND_MAX) * T;
		nowy = ansy +( (rand() << 1) - RAND_MAX) * T;
		nowans = Calc(nowx, nowy);
		double del  = nowans - ans;
		if(del < 0) {
			ans = nowans;
			ansx  = nowx, ansy  = nowy;
		}
		else if(exp(-del / T) > (double)rand() / RAND_MAX) {
			ansx = nowx, ansy = nowy;
		}
		T *= down;
	}
}
#include<ctime>
signed main() {
//	freopen("date.in","r",stdin);
//	freopen("yysb.out","w",stdout);
	srand(time(NULL));
	n = read();
	for(int i = 1; i <= n; i++) {
		a[i].sx = getin(), a[i].sy = getin(), a[i].ex = getin(), a[i].ey = getin();	
		ansx += a[i].sx + a[i].ex, ansy += a[i].ey + a[i].sy;
		if(a[i].sx == a[i].ex) {
			vis[i] = 1; // 竖直 
			if(a[i].sy > a[i].ey) swap(a[i].sy, a[i].ey);
		} 
		if(a[i].sy == a[i].ey) {
			vis[i] = 2; // 水平 
			if(a[i].sx > a[i].ex) swap(a[i].sx, a[i].sy);	
		} 
	}
	ansx /= (n << 1), ansy /= (n << 1);
	ans = Calc(ansx, ansy);
//	cout <<ans << "\n";
	for(int i = 1; i <= 100; i++) SA();
	printf("%.1lf %.1lf %.1lf",ansx,ansy,ans);
}

---

## 作者：BFSDFS123 (赞：0)

对于一个线段 $AB$ 和一个点 $C$ 的距离，有两种情况：

- 过直线 $AB$ 作 $C$ 垂线，且垂足落在线段 $AB$ 上。
- 过直线 $AB$ 作 $C$ 垂线，但垂足不在线段 $AB$ 上。

第一种情况，距离即为垂线段长度。

第二种情况，最短距离的点只会在线段端点上，判定即可。

这题拥有的一个条件是，所有线段垂直或平行与 x 轴。

那我们甚至不用将军~~喝水~~饮马，直接判定即可。

好了，我们现在会了求某个点的答案的方式，怎么求最值呢？

瞪眼一看盲猜单调或单峰，然后就不会了。

再想想，坐标，最值，单峰/单调，可以想到模拟退火。

然后调调参就过了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define eps 1e-8
const int inf=0x3f3f3f3f;
double temper=100;
double lower=0.997;
double dx[]={0,0,1,-1},dy[]={1,-1,0,0};
const int Maxn=200;
double X1[Maxn],Y1[Maxn],X2[Maxn],Y2[Maxn];
int n;
double calc(double nx,double ny)
{
	double ans=0;
	for(int i=1;i<=n;i++)
	{
		if(X1[i]==X2[i]) // 平行于 y 轴 
		{
			if(Y1[i]>Y2[i])
			{
				swap(Y1[i],Y2[i]);
			}
			if(Y2[i]<=ny)
			{
				ans+=sqrt((nx-X1[i])*(nx-X1[i])+(ny-Y2[i])*(ny-Y2[i]));
			}else if(ny<=Y1[i]){
				ans+=sqrt((nx-X1[i])*(nx-X1[i])+(ny-Y1[i])*(ny-Y1[i]));
			}else{
				ans+=sqrt((nx-X1[i])*(nx-X1[i]));
			}
		}else{ // 平行于 x 轴 
			if(X1[i]>X2[i])
			{
				swap(X1[i],X2[i]);
			}
			if(X2[i]<=nx)
			{
				ans+=sqrt((nx-X2[i])*(nx-X2[i])+(ny-Y2[i])*(ny-Y2[i]));
			}else if(nx<=X1[i]){
				ans+=sqrt((nx-X1[i])*(nx-X1[i])+(ny-Y2[i])*(ny-Y2[i]));
			}else{
				ans+=sqrt((ny-Y2[i])*(ny-Y2[i]));
			}
		}
	}
	return ans;
}
double ansx,ansy;
void mountainclimbing(double nowx,double nowy)
{
//	cout<<nowx<<" "<<nowy<<endl;
	temper=1e4;
	double ans=calc(nowx,nowy);
	while(temper>=1e-5)
	{
		for(int i=0;i<4;i++)
		{
			double nx=nowx+temper*dx[i];
			double ny=nowy+temper*dy[i];
			
			double genans=calc(nowx,nowy);
			double nowans=calc(nx,ny);
			
			double delta=nowans-genans;
			if(delta<0)
			{
				nowx=nx,nowy=ny;
				ans=nowans;
			}
			if(exp(-delta/temper)>double(rand())/RAND_MAX)
			{
				nowx=nx,nowy=ny;
			}
		}
		temper*=lower;
	}
	
	double genans=calc(ansx,ansy);
	if(ans<genans)
	{
		ansx=nowx;
		ansy=nowy;
	}
}
void work()
{
	srand(time(0));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf%lf%lf",&X1[i],&Y1[i],&X2[i],&Y2[i]);
	}
	while(((double)clock()/CLOCKS_PER_SEC<=0.9))
	{
		int X=rand()%100,Y=rand()%100;
		mountainclimbing(X*1.0,Y*1.0);
	}
	printf("%.1lf %.1lf %.1lf\n",ansx,ansy,calc(ansx,ansy));
}
int main()
{
	work();
	return 0;
}
```

---

