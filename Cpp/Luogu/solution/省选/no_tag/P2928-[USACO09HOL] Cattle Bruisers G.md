# [USACO09HOL] Cattle Bruisers G

## 题目描述

Canmuu is out for revenge after being utterly defeated by Bessie in paintball and has challenged Bessie to a video game.

In this game, Bessie starts out at point (BX, BY) in the coordinate grid (-1,000 <= BX <= 1,000; -1000 <= BY <= 1,000), and tries to escape, starting at time 0. She moves continuously at a velocity of (BVX, BVY) units/second (-100 <= BVX <= 100; -100 <= BVY <= 100). Thus, at time 1 she will be at point (BX + BVX, BY + BVY); at time 1.5 she will be at (BX + 1.5\*BVX, BY + 1.5\*BVY).

Unfortunately, Canmuu has sent N (1 <= N <= 50,000) cattle bruisers to pursue Bessie.  At time t=0, cattle bruiser i is at position (X\_i, Y\_i) (-1,000 <= X\_i <= 1,000; -1,000 <= Y\_i <= 1,000) with velocity (VX\_i, VY\_i) units/second (-1,000 <= VX\_i <= 1,000; -1,000 <= VY\_i <= 1,000).

Each cattle bruiser carries a 'proximity' weapon to fire at Bessie; the weapon can hurt Bessie when the cattle bruiser is no further than R (1 <= R <= 2,500) units from her.

Bessie has a shield to protect herself from these attacks. However, she does not want to waste any of her shield's power, so she would like to know the maximum number of cattle bruisers within firing range for any (potentially non-integer) time t >= 0.

In order to avoid precision errors with real numbers, it is guaranteed that the answer produced will be the same whether the attack range is decreased to R-0.0001 or increased to R+0.0001.

FEEDBACK: Your first 50  submissions for this problem will be run on some of the official test data, and you will receive a summary of the results.

自从卡门在弹珠游戏中被贝茜彻底击败，他一直在想找机会复仇.这会儿，他邀贝茜去玩一 个电脑游戏.

游戏中，贝茜在（BX,BY）处开始行动，这时时刻为0.她要试图 逃离.她的速度为(BVX，BVY)每秒.

不幸的是，卡门为了复仇，放出N(l<=N< =50000)个杀手追击贝茜.在t = 0时，杀手i的位置 是Xi, Yi他的速度是Vxi,Vyi每秒.

由于每个杀手配备了手枪，手枪的射程是R，也就是说贝茜要与这个杀手的距 离保持超过R，否则有性命之虞.

然而，贝茜还有一件秘密武器，盾.但是，她不想过多地消耗盾的能量.所以，她想知道在 逃脱过程中，某一个时刻她在最多为多少个杀手的射程内.当然这个时刻不一定是整数.

为了防止出现精度误差，数据保证在R 土 0.0001时也能得出正确结果.


## 说明/提示

Bessie starts at point (0, 0) and is moving at 2 units per second in the (positive) y-direction. There are 3 cattle bruisers, the first of which starts at point (0, -3) and travels 4 units per second in the y-direction. The maximum distance for a cattle bruiser to be in range of Bessie is 1 unit.


At time 1.5, Bessie is at point (0, 3), and the three bruisers are at points (0, 3), (-0.5, 3.5), and (4, -3.5). The first two cattle bruisers are within 1 unit of Bessie, while the third will never be within 1 unit of Bessie, so 2 is the most achievable.


## 样例 #1

### 输入

```
3 1 0 0 0 2 
0 -3 0 4 
1 2 -1 1 
1 -2 2 -1 
```

### 输出

```
2 
```

# 题解

## 作者：ycyaw (赞：4)

没有题解，来补一篇。

观察到题目中$Bessie$和杀手都在动，所以考虑相对运动，以$Bessie$的位置作为原点，$Bessie$不动，只考虑杀手运动。让$Bessie$不动，直接杀手的位置和速度减去$Bessie$的即可。

考虑杀手攻击半径为$R$，转化一下即进入以$Bessie(0,0)$为圆心，$R$为半径的圆，就可攻击到$Bessie$。

所以我们只要求出每个杀手进入该圆与离开该圆的时间点即可。最后就可以对所以时间点进行排序，然后对整条时间线进行类似于扫描线的方法统计答案。

显然就是这样一张图：![](https://s2.ax1x.com/2019/06/05/VNvuY4.png)

求出直线与圆的交点即可。

设杀手起点为$(x,y)$，速度为$(vx,vy)$，设在$t$时刻恰好在交点，那么：
$$
(x+t\times vx)^2+(y+t\times vy)^2=r^2
$$
化简得到一个一元二次方程：
$$
(vx^2+vy^2)\times t^2+(2x\times vx+2y\times vy)\times t+x^2+y^2-r^2=0
$$
解出来即可。$($即程序里的$work)$

注意判断$vx,vy$均为0的情况。

```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define int long long
#define hh puts("")
using namespace std;
int n,r,top;
double bx,by,bvx,bvy,eps=1e-8,L,R;
struct node{
    double x,y,vx,vy;
}a[500005];
struct TM{
    double t;
    int s;
}b[500005];
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-1;ch=getchar();}
    while(isdigit(ch)){ret=(ret<<3)+(ret<<1)+(ch^48);ch=getchar();}
    return ret*ff;
}
inline void work(double A,double B,double C){//a*t*t+b*t+c=0
    if(fabs(A)<eps){
        if(C<=0) L=0,R=1e9;
        else L=R=-1;
        return;
    }
    double delta=B*B-4*A*C;
    if(delta<0){//一元二次方程判根 
        L=R=-1;
        return;
    }
    L=(-B-sqrt(delta))/(2*A);
    R=(-B+sqrt(delta))/(2*A);
    if(L<0) L=0;
    if(R<0) R=-1;
}
inline bool cmp(TM a,TM b){
    return a.t<b.t;
}
signed main(){
    n=read(),r=read();
    bx=read(),by=read(),bvx=read(),bvy=read();
    for(int i=1;i<=n;i++){
        a[i].x=read()-bx;
        a[i].y=read()-by;
        a[i].vx=read()-bvx;
        a[i].vy=read()-bvy;
    }
    for(int i=1;i<=n;i++){
        double ds=a[i].x*a[i].x+a[i].y*a[i].y-r*r;
        work(a[i].vx*a[i].vx+a[i].vy*a[i].vy,2*a[i].x*a[i].vx+2*a[i].y*a[i].vy,ds);
        if(R!=-1) b[++top]=(TM){L,1},b[++top]=(TM){R,-1};
    }
    sort(b+1,b+top+1,cmp);
    int sum=0,ans=0;
    for(int i=1;i<=top;i++){
        sum+=b[i].s;
        ans=max(ans,sum);
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：1234567890sjx (赞：1)

让杀手的所有属性减去 `Bessie` 的所有属性就变成了只有杀手动 `Bessie` 不动的情况。

然后发现杀手的杀伤边界是一个圆的方程，和杀手的运动方向所构成的一次方程联立起来，就得到的该杀手可以对 `Bessie` 进行攻击的时间段。

用扫描线扫描一遍即可。时间复杂度 $O(n\log n)$，瓶颈在于排序。

---

## 作者：SimonSu (赞：0)

题目要求求一个运动的点 在 一堆运动的点的多少个的一定范围内

那么我们可以先转换为一个运动的点的一定范围内有其他运动的点中的多少个（求最多的时刻的个数）

那么聪明的我们都学过物理

物体的运动是相对的 所以我们让那个要找范围的运动点不动 所以就成了相对的 相对位置减一下 相对速度也减一下

~~所以这道题和牛绣有了异曲同工之妙~~

先算出交点 但是此时我们是以时间为未知量的 他不可能为负数吧！
（注意速度是有方向的）

然后我们可以推导三种情况

## 第一种 两端点都是正数

![图片说明](https://uploadfiles.nowcoder.com/images/20190806/978569483_1565102367191_D4C3F89B131E41E46DF38B9940F42B93 "图片标题") 

那么两个点的时间就是方程解得的时间

## 第二种 两端点都是负数

![图片说明](https://uploadfiles.nowcoder.com/images/20190806/978569483_1565102491079_901B803EE1A19A3A4C7D5AE7234A2EF4 "图片标题") 

两个点都是反向延长线 答案此时不存在

## 第三种 两端点一正一负

![图片说明](https://uploadfiles.nowcoder.com/images/20190806/978569483_1565102603442_072774B6B658B3603E1AA7198722775C "图片标题") 

此时点在那个圆的中间 所以两端点时间一个为0 另一个为所求得的正值

所以我们用计算几何先求出点 之后再用一次扫描线就可以得到答案啦！

```
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<queue>
#include<stack>
#include<cmath>
#define LL long long
using namespace std;

struct node{
	int num;
	double v;
}e[100100];
int v[100100];
double r,bx,by,bvx,bvy;
int n,cnt;
double x,y,vx,vy;
inline int cmp(node a,node b)
{
	return a.v < b.v;
}
int main()
{
	scanf("%d%lf%lf%lf%lf%lf",&n,&r,&bx,&by,&bvx,&bvy);
	//敌动我动还能算吗？ 
	//考虑位移是相对的  把速度改一下 位置也改一下 
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf%lf%lf",&x,&y,&vx,&vy);
		x-=bx;//3
		y-=by; //1
		vx-=bvx;//3
		vy-=bvy;//1
		
		// X= x + t*vx 
		// Y= y + t*vy
		// X*X+Y*Y=r*r 
		if(vx==0 && vy==0)
		{
			if(x*x+y*y<=r*r)
			{
				e[++cnt].v = 0;
				e[cnt].num = i; 
			}
			
			continue;
		}
		// x*x + vx*vx*t*t + 2*x*vx*t +
		// y*y + vy*vy*t*t + 2*y*vy*t = r*r
		// (vx*vx+vy*vy)*t*t+ (2*x*vx+2*y*vy)*t + x*x+y*y-r*r =0
		double A=vx*vx+vy*vy;
		double B=2*x*vx+2*y*vy;
		double C=x*x+y*y-r*r;
		double delta=B*B-4*A*C;
//		cout<<x<<" "<<y<<" "<<vx<<" "<<vy<<" "<<A<<" "<<B<<" "<<C<<" "<<delta<<" YYYY "<<endl; 
		if(A<=1e-8)
		{
			if(C>0) continue;
			e[++cnt].v = 0;
			e[cnt].num = i;
			e[++cnt].v = 1e9;
			e[cnt].num = i;  
			continue;
		}
		else if(delta<0) continue;
		else
		{
			if((-B-sqrt(delta))*1.0/(2*A)<0 && (-B+sqrt(delta))*1.0/(2*A)<0) continue;
				e[++cnt].v = (-B-sqrt(delta))*1.0/(2*A);
				e[cnt].num = i;
				e[++cnt].v = (-B+sqrt(delta))*1.0/(2*A);
				e[cnt].num = i;
		}
	}
	sort(e+1,e+1+cnt,cmp);
	LL ans=0,tmp=0;
	for(int i=1;i<=cnt;i++)
	{
//		cout<<e[i].num <<"   "<<e[i].v<<" TYTYTYT "<<endl;
		int num=e[i].num;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
		if(v[num]==0)
		{
			tmp++;
			v[num]=1;
		}
		else
		{
			tmp--;
		}
		if(tmp>ans) ans=tmp;
	}
	printf("%lld",ans);
}
```

---

