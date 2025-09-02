# Harry Potter and the Golden Snitch

## 题目描述

弗雷德和乔治 $·$ 韦斯莱两兄弟曾经进入了一个体育用品商店并打开了一盒魁地奇球。在漫长而痛苦的实验后，他们发现金色飞贼根本就没有被施过魔法：它只是一个被编了程的装置。它总是沿着同一个轨迹——一个顶点在 $ (x_0, y_0, z_0) $，$ (x_1, y_1, z_1) $……$ (x_n, y_n, z_n) $的折线——移动。

在比赛开始时飞贼被放在点 $ (x_0, y_0, z_0) $，然后以恒定的速度$ v_s $在折线上移动。双胞胎暂时还没发现在那之后飞贼的行为。尽管如此，他们仍希望收集回来的信息能够帮助哈利 $·$ 波特和他的队伍在即将到来的与斯莱特林的比赛中胜出。哈利$·$波特得知在比赛开始时他会在 $ (P_x,P_y,P_z) $，而他那超快的光轮 $ 2011 $ 允许他以恒定的速度 $ v_p $ 向任何方向移动或保持静止。$ v_p $ 不小于飞贼的速度 $ v_s $ 。

哈利 $·$ 波特当然想要尽快抓住飞贼。如果他能在折线上抓住飞贼，他想督促韦斯莱兄弟继续进行实验。当哈利 $·$ 波特和飞贼在同一坐标时，他就能抓住飞贼。

## 样例 #1

### 输入

```
4
0 0 0
0 10 0
10 10 0
10 0 0
0 0 0
1 1
5 5 25
```

### 输出

```
YES
25.5000000000
10.0000000000 4.5000000000 0.0000000000
```

## 样例 #2

### 输入

```
4
0 0 0
0 10 0
10 10 0
10 0 0
0 0 0
1 1
5 5 50
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
1
1 2 3
4 5 6
20 10
1 2 3
```

### 输出

```
YES
0.0000000000
1.0000000000 2.0000000000 3.0000000000
```

# 题解

## 作者：天亮codekiller (赞：1)

题目描述：[题目传送门](https://www.luogu.com.cn/problem/CF65C)
## 题意简述：
已知哈利波特的初始三维坐标、以及飞怪的 $n$ 次运动经过的 $n+1$ 个折点（或起点、终点）的三维坐标，还有他们各自的速度。求哈利波特能不能抓住飞怪，能就输出最短时间和抓住的点的三维坐标。
## 思路：
题目中的信息 “ $v_s$ $\le$ $v_p$ ”这句话很关键。

这就是说，当哈利波特在某一个点可以抓住飞贼时，他在飞贼运动轨迹后面的点也一定可以抓住飞贼。

所以这道题我们可以先找到一个点使得哈利波特在这个点无法抓住飞贼，而在它下一个点可以抓住。如果这个点不存在，输出 “ NO ” 就可以了。

在找到了这个点以后，我们可以确定最快抓住的点一定在这个点与下一个点的连线之间。显然答案具有单调性（还是因为 $v_s$ $\le$ $v_p$ ），所以用二分答案来确定解的位置。具体实现见代码。

## 注意点：

先输入 $v_p$ ，再输入 $v_s$ ,不然 WA 两行泪；

精度差 $eps$ 用 $10^{-11}$ ，用 $10^{-9}$ WA 两行泪；

不要自作聪明地（说的正是本蒟蒻）在头尾加极大值或极小值，不然毫无头绪的 WA 两行泪；

二分取等符号反， WA 两行泪……

## 代码：
大家最感兴趣，本蒟蒻却写得很烂……

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e4+5;//n的最大值 
const double eps=1e-11;//精度控制（用1e-9会WA） 
inline double dist(double x1,double y1,double z1,double x2,double y2,double z2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2)); 
}//计算三维坐标下点的距离 
int n;
int x[MAXN],y[MAXN],z[MAXN];//记录飞贼运动的轨迹 
double t[MAXN];//时间前缀和，记录飞贼运动到每个点所需的时间（t[1]=0） 
int vs,vp;//飞贼和哈利波特各自的速度 
int sx,sy,sz;//哈利波特的起始坐标 
int catchid;//题解中解释的点，即抓住飞贼的点所在直线的出发点 
double thieftime,catchtime,nowx,nowy,nowz;//二分中贼到所求点达的时间，哈利波特所需的时间，以及所求点的坐标 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n+1;++i)
		scanf("%d%d%d",&x[i],&y[i],&z[i]);
	scanf("%d%d",&vp,&vs);
	scanf("%d%d%d",&sx,&sy,&sz);//读入 
	for(int i=2;i<=n+1;++i)
		t[i]=t[i-1]+dist(x[i-1]*1.0,y[i-1]*1.0,z[i-1]*1.0,x[i]*1.0,y[i]*1.0,z[i]*1.0)*1.0/vs;//计算时间前缀和t数组 
	for(int i=1;i<=n;++i){//枚举点catchid
		double l=t[i]-dist(x[i]*1.0,y[i]*1.0,z[i]*1.0,sx,sy,sz*1.0)*1.0/vp;//计算这个点的两人移动的时间差 
		double r=t[i+1]-dist(x[i+1]*1.0,y[i+1]*1.0,z[i+1]*1.0,sx,sy,sz*1.0)*1.0/vp;//计算这个点的所到达的点的两人移动的时间差 
		if(r+eps>=0&&l-eps<=0){//如果在左端点时间差为负，且右端点时间差为正，则该点就是目标点 
			catchid=i;
			break;
		}//原因是左端点无法抓住，而右端点可以抓住，则最快抓住的点一定在它们之间 
	}
	if(catchid==0)return puts("NO"),0;//如果没有找到该点，则无法抓住，退出 
	double lambda=0.5,piece=0.25;//piece是二分答案时lambda下一次比较时的偏移量，初始值为0.25，每次更新时除以2 
	//lambda指的是二分答案的目标点到左端点的距离与左右端点的距离的比值，一开是赋值0.5，即中点。 
	while(true){
		thieftime=t[catchid]+lambda*(t[catchid+1]-t[catchid]);//计算飞贼运动到目标点的时间 
		nowx=x[catchid]+lambda*(x[catchid+1]-x[catchid]);//计算目标点的x坐标 
		nowy=y[catchid]+lambda*(y[catchid+1]-y[catchid]);//计算目标点的y坐标 
		nowz=z[catchid]+lambda*(z[catchid+1]-z[catchid]);//计算目标点的z坐标 
		catchtime=dist(sx*1.0,sy*1.0,sz*1.0,nowx,nowy,nowz)*1.0/vp;//计算哈利波特运动到目标点的时间 
		if(fabs(thieftime-catchtime)<eps){//如果两个时间相同，则输出答案 
			puts("YES");
			printf("%.8lf\n",catchtime);
			printf("%.8lf %.8lf %.8lf",nowx,nowy,nowz);
			return 0;//提前结束程序 
		}
		else if(thieftime<catchtime)lambda+=piece;
		//如果飞贼运动到目标点的时间小于哈利波特运动到目标点的时间，那么目标点距离catchid点偏近
		else lambda-=piece;//否则说明目标点距离catchid点偏远 
		piece/=2;//偏移量除以2 
	}
	return 0;//程序结束 
}
```


---

## 作者：HMZHMZHMZ (赞：0)

### 题意

有一个金色飞贼，它会沿着 $ (x_1,y_1,z_1) \rightarrow (x_2,y_2,z_2) \rightarrow \dots \rightarrow (x_{n+1},y_{n+1},z_{n+1}) $ 的轨迹以 $ v_s $ 的速度移动。

哈利波特位于点 $ (P_x,P_y,P_z) $，他的移动速度是 $ v_p $，保证 $ v_s \leq v_p$。

问哈利波特最早可以在什么时候抓住金色飞贼。

### 思路

题目中给出了 $ v_s \leq v_p $ 这一条件，那么我们就可以知道，如果在一个时刻哈利波特抓住了飞贼，那么在这个时刻之后也一定可以抓住飞贼。

有了这个想法，那么就可以找到两个节点，当飞贼抵达左边的节点时，哈利波特无法抓到飞贼，而在右边节点时就可以抓到，那么最小答案必然存在于这个区间之内。

我们考虑二分抓住飞贼的时间，飞贼的到达时间就是我们二分的值，但哈利波特的到达时间就不是很好算了。

我们定义当前二分的值是 $ mid $，左边的节点是 $ i $，右边的节点是 $ i + 1 $，飞贼到达第 $ i $ 个点的时间是 $ t_i $。

以 $ x $ 坐标为例，$ x_{new} = x_i + (x_{i+1}-x_i) \times \frac{(mid-t_i)}{t_{i+1}-t_i} $。这个式子运用相似三角形的知识可以推出来，这里就不讲了。

那么同上，将剩下两个坐标也求出来，然后计算距离和时间即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define vi vector<int>
#define pii pair<int,int>
#define pb(x) push_back(x)
using namespace std;
const int N=1e4+10;
const double eps=1e-10;
int n,m,T;
double x[N],y[N],z[N],t[N],HP_speed,FZ_speed,X,Y,Z,ans;
inline int read(){
	int s=0,f=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch<='9'&&ch>='0') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return f?-s:s;
}
double P(double x){
	return x*x;
}
double dist(double x,double y,double z,double _x,double _y,double _z){
	return sqrt(P(x-_x)+P(y-_y)+P(z-_z));
}
int main(){
	 n=read();
	 for(register int i=1;i<=n+1;++i) cin>>x[i]>>y[i]>>z[i];
	 cin>>HP_speed>>FZ_speed>>X>>Y>>Z;
	 t[1]=0.0;
	 for(register int i=2;i<=n+1;++i){
	 	double tim=dist(x[i],y[i],z[i],x[i-1],y[i-1],z[i-1])/FZ_speed;
	 	t[i]=t[i-1]+tim;
	 }
	 int id=-1;
	 for(register int i=1;i<=n;++i){
	 	double now=t[i]-dist(X,Y,Z,x[i],y[i],z[i])/HP_speed;
	 	double _now=t[i+1]-dist(X,Y,Z,x[i+1],y[i+1],z[i+1])/HP_speed;
	 	if(now<=eps&&_now+eps>=0){
	 		id=i;
	 		break;
		 }
	 }
	 if(id==-1){
	 	printf("NO");
	 	return 0;
	 }
	 double l=t[id],r=t[id+1];
	 double xx,yy,zz;
	 while(1){
	 	double mid=(l+r)/2;
	 	double mor=mid-t[id];
	 	xx=x[id]+(x[id+1]-x[id])*mor/(t[id+1]-t[id]);
	 	yy=y[id]+(y[id+1]-y[id])*mor/(t[id+1]-t[id]);
	 	zz=z[id]+(z[id+1]-z[id])*mor/(t[id+1]-t[id]);
	 	double HP_time=dist(xx,yy,zz,X,Y,Z)/HP_speed;
	 	if(fabs(HP_time-mor-t[id])<=eps){
	 		printf("YES\n");
	 		printf("%.8lf\n",HP_time);
	 		printf("%.8lf %.8lf %.8lf",xx,yy,zz);
	 		return 0;
		 }
		 if(mor+t[id]<HP_time) l=mid;
		 else r=mid;
	 }
	 return 0;
}
```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
有一个金色飞贼沿着 $(x_1,y_1,z_1)\to (x_2,y_2,z_2)\to ...\to (x_n,y_n,z_n)\to $的轨迹以 $v_s$ 的速度匀速运动.  
哈利的最大速度是 $v_p$，初始位置是 $(p_x,p_y,p_z)$.  
请求出哈利抓住金色飞贼的最快时间和抓住它的位置.  
$n\le 10000,v_p\ge v_s$.
## $\text{Solution}$  
$v_p\ge v_s$ 是本题的关键条件，这意味着本题的答案是具有**单调性**的.  
所以二分时间判断是否可以抓到即可.  

**注意：**
1. 虽然精度只要求到 $10^{-6}$，但是由于坐标的计算会放大精度，所以我们的精度需要开到 $10^{-12}$（这里不是平方关系，只是要开小一点）.
2. 需要开 long double，否则精度太小可能会死循环.
3. 注意不等号的精度问题.

## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define double long double 
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=1e4+100;
const double eps=1e-12;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m;
double t[N],sum[N],v;
double x[N],y[N],z[N];
double X,Y,Z,V;
inline double tim(double x,double y,double z){
  return sqrt((x-X)*(x-X)+(y-Y)*(y-Y)+(z-Z)*(z-Z))/V;
}
bool check(double w){
  for(int i=1;i<=n;i++){
    if(sum[i]>=w-eps){
      double o=(w-sum[i-1])/t[i];
      double xx=x[i-1]+(x[i]-x[i-1])*o,yy=y[i-1]+(y[i]-y[i-1])*o,zz=z[i-1]+(z[i]-z[i-1])*o;
      return tim(xx,yy,zz)-eps<w;
    }
  }
  return false;
}
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();
  for(int i=0;i<=n;i++) scanf("%Lf%Lf%Lf",&x[i],&y[i],&z[i]);
  scanf("%Lf%Lf%Lf%Lf%Lf",&V,&v,&X,&Y,&Z);
  for(int i=1;i<=n;i++){
    double d=sqrt((x[i]-x[i-1])*(x[i]-x[i-1])+
		  (y[i]-y[i-1])*(y[i]-y[i-1])+(z[i]-z[i-1])*(z[i]-z[i-1]));
    t[i]=d/v;sum[i]=sum[i-1]+t[i];
  }
  if(tim(x[n],y[n],z[n])>sum[n]+eps){
    printf("NO\n");return 0;
  }
  double st=0,ed=sum[n];
  while(ed-st>eps){
    double mid=(st+ed)/2;
    if(check(mid)) ed=mid;
    else st=mid;
  }
  printf("YES\n%.10Lf\n",st);
  double w=st;
  for(int i=1;i<=n;i++){
    if(sum[i]>w-eps){
      double o=(w-sum[i-1])/t[i];
      double xx=x[i-1]+(x[i]-x[i-1])*o,yy=y[i-1]+(y[i]-y[i-1])*o,zz=z[i-1]+(z[i]-z[i-1])*o;
      printf("%.10Lf %.10Lf %.10Lf",xx+eps,yy+eps,zz+eps);return 0;
    }
  }
}
/*
*/
```


---

