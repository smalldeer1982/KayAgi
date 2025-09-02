# Bombing

## 题目描述

The commanding officers decided to drop a nuclear bomb on the enemy's forces. You are ordered to determine the power of the warhead that needs to be used.

The enemy has $ N $ strategically important objects. Their positions are known due to the intelligence service. The aim of the strike is to deactivate at least $ K $ important objects of the enemy. The bombing impact point is already determined and has coordinates of $ [X_{0};\ Y_{0}] $ .

The nuclear warhead is marked by the estimated impact radius $ R>=0 $ . All the buildings that are located closer than $ R $ to the bombing epicentre will be destroyed. All the buildings that are located further than $ R $ from the epicentre, can also be deactivated with some degree of probability. Let's assume that $ D $ is the distance between a building and the epicentre. This building's deactivation probability $ P(D,R) $ is calculated according to the following formula:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50D/711e1c419c06d4e6b9f16e86aeb94f1d25925635.png) We should regard ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50D/5966d57c740e5c247c71ce7e978aac36c0d9200d.png) as $ e^{a} $ , where $ e≈2.7182818284590452353602874713527 $ If the estimated impact radius of the warhead is equal to zero, then all the buildings located in the impact point will be completely demolished and all the rest of important objects will not be damaged.

The commanding officers want the probability of failing the task to be no more than $ ε $ . Nuclear warheads are too expensive a luxury, that's why you have to minimise the estimated impact radius of the warhead.

## 样例 #1

### 输入

```
1
1 500
5 5
1 2
```

### 输出

```
3.84257761518762740
```

## 样例 #2

### 输入

```
5
3 100
0 0
3 4
60 70
100 100
10 10
5 12
```

### 输出

```
13.45126176453737600
```

# 题解

## 作者：Mint_Flipped (赞：3)

求最小的r，要求一个逼近的值，二分没跑了。

上下两个区间范围为l=0，r=?，r应该为里起点最远的点，所以输入时就要比较记录最大值

二分 eps设为1e-6(题目给的精度就是1e-6)，写一个二分答案的板子

check 有点难，题目给了一个不成功的概率，所以我们就要计算不成功的概率，

成功0-k-1个都是不成功的,根据给予的公式我们可以计算出每个点的成功的概率，不成功的概率就是1.0-该概率

准备工作完成，套一个概率DP，理一理转移式：
dp[ i ][ j ], i为共有i个地方接受爆破，j为有j个地方成功爆破，

dp[ i ][ j ]=上一个成功的概率+这一个成功失败的概率。

算出所有的概率，统计成功0-k-1的概率即为总的不成功率，与给定值比较，二分得出最小r即可

~~题太难了，作为一个学了半年的萌新来说太难了~~

代码如下：
```c
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define lowbit(a) (a&(-a))
#define fir(a) a->first 
#define sec(a) a->second 
const int inf=0x3f3f3f3f;
const int maxn=1e2+5;
const int mod=1e9+7;
const double eps=1e-6;
const double e=2.7182818284590452353602874713527;
int n,k,p;
double l,r,R,f[maxn][maxn],tp[maxn]; //失败的概率
struct node{
    double x,y;
}coor[maxn];
double coor_cal(double a,double b){
    return sqrt((a-coor[0].x)*(a-coor[0].x)+(b-coor[0].y)*(b-coor[0].y));
}
double exp(double a){
    return pow(e,a);
}
double cal(double D){
    if(D<=R)
        return 1.0;
    else
        return exp(1.0-D*D/(R*R));
}
bool check(double mid){
    mem(f,0);
    f[0][0]=1.0;
    R=mid;
    fo2(i,n)
    tp[i]=1.0-cal(coor_cal(coor[i].x,coor[i].y)); //爆炸失败
    fo2(i,n){
        f[i][0]=f[i-1][0]*tp[i]; //失败
        fo2(j,i){
            f[i][j]=f[i-1][j]*tp[i]+f[i-1][j-1]*(1.0-tp[i]); //失败 成功
        }
    }
    double sum=0.0;
    fo1(i,k)
    sum+=f[n][i];
    return sum<=p/1000.0;
}
int main()
{
    scanf("%d%d%d",&n,&k,&p);
    scanf("%lf%lf",&coor[0].x,&coor[0].y);
    fo2(i,n){
        scanf("%lf%lf",&coor[i].x,&coor[i].y);
        r=max(r,coor_cal(coor[i].x,coor[i].y));
    }
    double ans;
    while(l+eps<=r){
        double mid=(l+r)/2.0;
        if(check(mid))
        ans=mid,r=mid;
        else
        l=mid;
    }
    printf("%.12lf\n",ans);
    return 0;
}
```



---

## 作者：hgzxwzf (赞：1)

## 解题思路：

首先答案肯定具有单调性，所以可以二分。

假设现在炸弹的爆炸范围是 $R$，轰炸点为 $u$，由题意可知，对于城市 $v$，记 $u$ 与 $v$ 的距离为 $D$，一发炸弹能炸毁到它的概率为：

$p=\begin{cases}1&D\le R\\\exp(1-\frac{D^2}{R^2})&D>R\end{cases}$

我们不用关心函数 $\exp$ 是啥，我们只需要知道它是增函数，也就是说 $R$ 变大，$exp(1-\frac{D^2}{R^2})$ 也会变大（~~炮弹爆炸威力越大炸毁城市的概率越大~~）。

c++ 的 cmath 库中包含了 $\exp()$ 函数，可以直接返回浮点数。

现在已经解决了 $R$，那么可以开始我们的 DP 了。

定义 $dp(i,j)$ 表示前 $i$ 座城市炸掉了 $j$ 座城市的概率。

对于第 $i$ 城市，如果这一发炮弹把它炸毁了，概率为 $p$，所以前 $i-1$ 座城市被炸毁 $j-1$ 座，$dp(i,j)=dp(i-1,j-1)\times p$；

没有炸毁，所以前 $i-1$ 座城市被炸毁 $j$ 座，$dp(i,j)=dp(i-1,j)\times p$。

所以 $dp(i,j)=dp(i-1,j-1)\times p+dp(i-1,j)\times (1-p)$。

最后需要统计的是炸毁城市 $\ge k$ 的总概率，因为炸毁城市数不同的两个事件是独立的，所以 $\sum_{j=k}^{n}dp(n,j)$ 就是总概率，最后判断是否比最小允许成功率大就可以了（题目中给的概率是最大允许失败概率）。

## 代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)
using namespace std;
const int N=110;
double dp[N][N],x[N],y[N];
int n,X0,Y0,k,pro;
inline double get_p(int i,double mid)
{
	int d=(x[i]-X0)*(x[i]-X0)+(y[i]-Y0)*(y[i]-Y0);
	double dis=sqrt(d);
	if(dis<=mid) return 1;
	else return exp(1-d/mid/mid);
}
bool pd(double mid)
{
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	rep(i,1,n)
		rep(j,0,i)
		{
			double p=get_p(i,mid);
			dp[i][j]=dp[i-1][j]*(1-p);
			if(j) dp[i][j]+=dp[i-1][j-1]*p;
		}
	double ans=0;
	rep(i,k,n) ans+=dp[n][i];
	return ans>=(1-1.0*pro/1000);
}
int main()
{
	scanf("%d%d%d%d%d",&n,&k,&pro,&X0,&Y0);//最大允许失败的概率为千分之pro
	rep(i,1,n) scanf("%lf%lf",&x[i],&y[i]);
	double l=0,r=1e9;
	while(r-l>1e-8)
	{
		double mid=(l+r)/2;
		if(pd(mid)) r=mid;
		else l=mid;
	}
	printf("%.15lf",l);
	return 0;
}
```


---

## 作者：mango2011 (赞：0)

显然 $R$ 的取值具有单调性。所以我们考虑二分这个 $R$，由于一般二分的写法有可能被卡，所以建议写直接二分若干次的写法。考虑如何判断当前的 $R$ 是否合适：

令 $p_i$ 为第 $i$ 座建筑物被炸毁的概率。考虑 dp，令 $dp_{i,j}$ 为前 $i$ 座建筑，炸毁了 $j$ 座的概率，有转移：

当 $j>0$ 时 $dp_{i,j}=dp_{i-1,j-1}\times p_i +dp_{i-1,j}\times (1.0-p_i)$；当 $j=0$ 时 $dp_{i,j}=dp_{i-1,j}\times p_i$。

于是完成任务的可能型就是 $T=\displaystyle\sum_{i=k}^{n} dp_{n,i}$。当 $T>\frac{1000-h}{1000}$ 时就说明当前的 $R$ 可行；否则说明不可行。

下面具体说一下 $p_i$ 的求法：

由两点距离公式 $(x_1,y_1)$ 与 $(x_2,y_2)$ 的距离为 $D=\sqrt {(x_1-x_2)^2+(y_1-y_2)^2}$，可以算出这个建筑与爆炸点的举例。

当 $D\le R$ 的时候，$p_i=1.0$；否则，除了 $R=0$ 是都是 $e^{1.0-\frac{D^2}{R^2}}$，$R=0$ 的情形也是简单的。

分析一下时间复杂度：$O(Bnm)$，其中 $B$ 为二分次数，取 $100$ 左右时较优，不过常数应该不小。

最后，贴上我们的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=105;
const double eps=1e-7;
double e=2.718281828459;
double dp[maxn][maxn];
double p[maxn],x[maxn],y[maxn];
double xx,yy,h;
int n,k;
double dis(double x1,double y1,double x2,double y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
double P(double d,double r){
	if(d<=r){
		return 1.0;
	}
	if(r<eps){
		return 0.0;
	} 
	return pow(e,1.0-d*d/(r*r));
}
bool check(double r){
	for(int i=1;i<=n;i++){
		p[i]=P(dis(x[i],y[i],xx,yy),r);
		//printf("%.5lf\n",p[i]);
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			dp[i][j]=0.0;
		}
	}
	dp[0][0]=1.0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			if(j>0){
				dp[i][j]+=dp[i-1][j-1]*p[i];
			}
			dp[i][j]+=dp[i-1][j]*(1.0-p[i]);
		}
	}
	double tot=0.0;
	for(int i=k;i<=n;i++){
		tot+=dp[n][i];
	} 
	if(tot>=h){
		return 1;
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
	cin>>n>>k>>h>>xx>>yy;
	h/=1000.0;
	h=1.0-h;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
	double l=0.0,r=4000.0;
	for(int i=1;i<=100;i++){
		double mid=(l+r)/2.0;
		if(check(mid)){
			r=mid;
		}
		else{
			l=mid;
		}
	}
	cout<<fixed<<setprecision(15)<<l<<endl;
	return 0;
}
```

---

