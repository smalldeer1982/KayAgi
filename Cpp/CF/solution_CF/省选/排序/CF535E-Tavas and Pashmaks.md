# Tavas and Pashmaks

## 题目描述

现在有两个比赛项目:跑步和游泳.每一个人在这两个项目都有一个正整数的值,第i个人分别为$a_i,b_i$,表示他在这个项目上的速度.
我们假定游泳的距离为$S_1$,跑步的距离为$S_2$(都是**正实数**),知道每一个人的值,如果对于第i个人,存在这样子的$S_1$和$S_2$使得$S_1/a_i+S_2/b_i<=S_1/a_j+S_2/b_j(1<=j<=n)$,那么就称这个人可以夺冠.
求出有多少个人可以夺冠.

## 样例 #1

### 输入

```
3
1 3
2 2
3 1
```

### 输出

```
1 2 3 
```

## 样例 #2

### 输入

```
3
1 2
1 1
2 1
```

### 输出

```
1 3 
```

# 题解

## 作者：mrsrz (赞：5)

令$T=\dfrac A{a_i}+\dfrac B{b_i}$。

我们把每个人的状态$(\dfrac 1{a_i},\dfrac 1{b_i})$看成一个点$(x,y)$，则$T=Ax+By$就是$y$关于$x$的一次函数。

化简一下，得：$y=-\dfrac A B x+\dfrac T B$

这个是一条直线，其斜率$k=-\dfrac A B$。由于$A,B$为正实数，所以$k< 0$。

那么，由于我们对于每一个点的$x,y$是已知的，所以知道$k$就能求出$\dfrac T B$，而$B$相等，进而可以得出$T$的大小关系。

我们要对每个直线，找一个斜率，使得$T$最小，即$\dfrac T B$最小。

这样的点一定在所有点构成的下凸壳上，因为若其不在下凸壳上，则一定存在一个点$p$，在它的左下方。那么对于过这个点的任意一条斜率$k< 0$的直线，将其向左下平移，使得其过点$p$，则该直线的$\dfrac T B$一定比原直线小。

所以求凸包，用单调栈维护下凸壳，然后取斜率为负的那部分（左下凸壳）即可。

时间复杂度$O(n\log n)$（排序）。

注意细节：

1. 若对同一个$a$，有多个不同的$b_i$，则保留$b _i$最大的那个（速度快的显然比速度慢的优）。
2. 有可能出现两个人$i,j$的两个速度相同的情况，这两个点都要保留。

## Code：
```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
#define N 200005
struct point{
	double x,y;
	int id;
	inline bool operator<(const point&rhs)const{return(x!=rhs.x)?(x<rhs.x):(y<rhs.y);}
}q[N],p[N];
int n,m;
int sta[N],top;
std::vector<int>v,id[N];
inline double slope(int a,int b){
	return((p[a].y-p[b].y)/(p[a].x-p[b].x));
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		int a,b;
		scanf("%d%d",&a,&b);
		q[i]=(point){1./a,1./b,i};
	}
	std::sort(q+1,q+n+1);
	p[1]=q[1];m=1;
	for(int i=2;i<=n;++i)
	if(fabs(q[i].x-q[i-1].x)>1e-9)p[++m]=q[i];else
	if(fabs(q[i].y-p[m].y)<=1e-9)id[p[m].id].push_back(q[i].id);
	if(m==1){
		v.push_back(p[1].id);
		for(int i:id[p[1].id])v.push_back(i);
		std::sort(v.begin(),v.end());
		for(int i:v)printf("%d ",i);
		return 0;
	}
	sta[1]=1,sta[2]=2;
	top=2;
	for(int i=3;i<=m;++i){
		while(top>1&&slope(sta[top-1],sta[top])>slope(sta[top-1],i))--top;
		sta[++top]=i;
	}
	v.push_back(p[sta[1]].id);
	for(int i:id[p[sta[1]].id])v.push_back(i);
	for(int i=2;i<=top;++i)
	if(slope(sta[i-1],sta[i])<0){
		v.push_back(p[sta[i]].id);
		for(int j:id[p[sta[i]].id])v.push_back(j);
	}else break;
	std::sort(v.begin(),v.end());
	for(int i:v)printf("%d ",i);
	return 0;
}
```

---

## 作者：宇智波—鼬 (赞：3)

##  蒟蒻的第二篇题解    
~~终于做掉了这一题，趁此题暂无题解，赶紧发了庆祝一下qwq~~   
好了，重点说说此题。   
### 首先可得到这个式子：

### $\frac{A}{a_{i}}+\frac{B}{b_{i}}=T$   

其中 $T$ 表示时间，这个式子应该不难理解，题目就转换成了对于一对 $(a_{i}$ , $b_{i})$ ，如果存在一对 $(A,B)$ 使得时间 $T$ 在 $(a_{i}$ , $b_{i})$ 上最小，就输出。     
### 接下来是做法：
考虑把 $(\frac{1}{a_{i}}$  , $\frac{1}{b_{i}})$ 看做平面上的点，原式变成 $Ax+By=T$ ，这就是你们~~喜欢~~的一次函数啦。继续把原式变得更通俗

### $y=-\frac{A}{B}x+\frac{T}{B}$ 
   
由于点 $(x,y)$ 是给定的，假设你已经确定直线的斜率，也就是 $-\frac{A}{B}$ ，你就可以算出时间 $T$ ，进而轻松地确定哪对点是答案。       
那么，怎么确定斜率呢？我们可以通过画图发现，是答案的点一定在平面图的左下凸包上，如果明白凸包的思想，
那么问题就很简单了，至于没学过凸包的同学，可以参考[yyb的博客](https://www.cnblogs.com/cjyyb/p/7260523.html)或[这篇博客](https://www.cnblogs.com/aiguona/p/7232243.html)~~（没学凸包还想做此题?）~~，蒟蒻我就不多说了qwq     


上代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double 
using namespace std;
inline ll read(){
    ll f=1,w=0;char x=0;
    while(!(x>='0'&&x<='9'))
    {
        x=getchar();
        if(x=='-') f=-1;
    }
    while(x>='0'&&x<='9')
    {
        w=(w<<3)+(w<<1)+(x^48);
        x=getchar();
    }
    return f*w;
}//习惯性的快读
struct people{
    ll a,b,id;
}p[300010];
ll n,s[300010],t;
bool v[300010],ans[300010];
bool cmp(people a,people b){
    if(a.a==b.a) return a.b>b.b;
    return a.a>b.a;
}//凸包排序
ld check(people a,people b){
    return (ld)a.a*b.a*(b.b-a.b)/(b.a-a.a)/b.b/a.b;
}//斜率的计算
int main(){
    n=read();
    for(int i=1;i<=n;i++) p[i].a=read(),p[i].b=read(),p[i].id=i;
    sort(p+1,p+n+1,cmp);
    s[1]=1,t=1;
    ll maxb=p[1].b;
    for(int i=2;i<=n;i++)
        if(p[i].b<=maxb) v[i]=1;
        else maxb=p[i].b;
    //去重和排除能一眼看出非答案的点，譬如a和b都比另一个点小
    for(int i=2;i<=n;i++)
    {
        if(v[i]||check(p[i],p[s[t]])>0) continue;//斜率大于0排除（并不知道有没有用
        while(t>1&&check(p[i],p[s[t]])<check(p[s[t-1]],p[s[t]]))
            t--;
        s[++t]=i;
    }//单调栈维护的类似于凸包的过程
    for(int i=1;i<=t;i++)
    {
        ans[p[s[i]].id]=1;
        for(int j=s[i]+1;j<=n&&p[s[i]].a==p[j].a&&p[s[i]].b==p[j].b;j++)
            ans[p[j].id]=1;
    }//还原位置相同的点
    for(int i=1;i<=n;i++)
        if(ans[i]) cout<<i<<" ";
    return 0;
}
```



---

## 作者：_Felix (赞：2)

[宇智波—鼬的此题题解，代码注释很可读。](https://www.luogu.com.cn/blog/yuzhiboyou/solution-cf535e)

### 一.转化成n条直线

不难看出，每个人所花费的时间是$t=\frac S {s_i} +\frac R {r_i}$

不妨设R=1,则$t=\frac {\frac S R} {s_i} +\frac 1 {r_i}$

现在准备一个点$(\frac 1 {s_i},\frac 1 {r_i})$

则$t=\frac {\frac S R} {s_i} +\frac 1 {r_i}$

令$k=-\frac S R,x=\frac 1 {s_i},y=\frac 1 {r_i}$ $(k<0)$

∴ $t=-kx+y$

∴ $y=kx+t$

也就是说，我们拥有了n条直线。

### 二.答案在左下凸包上

对于每条直线，需要寻找使得t最小的k。

对于一个点A，它的左下方如果有一个点B时，

$y_A=kx_A+t_A,y_B=kx_B+t_B$

$t_A=-kx_A+y_A,t_B=-kx_B+y_B$

∵$x_B\le x_A,y_B\le y_A$

∴$t_B \le t_A$

因此答案在左下凸包上。

### 三.关于左下凸包

可以先排除x和y都比其他的点中某一个小的。

先按照x从小到大排序，x一样按照y从小到大排序。

求左下凸包的时候，每两个凸包上的点k<0并且k逐渐减小。

### 四.警告

1.宇智波—鼬 的代码，为了不损失精度，x的存储是$s_i$，y的存储是$r_i$，不要看着四就搞错了。

2.要去重。

---

