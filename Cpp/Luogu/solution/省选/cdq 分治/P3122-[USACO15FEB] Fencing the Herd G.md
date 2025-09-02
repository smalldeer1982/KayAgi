# [USACO15FEB] Fencing the Herd G

## 题目描述

Farmer John 需要你帮助他决定在哪里建造形状是一条无限长的直线的栅栏来限制他的牛的活动。他选出了几个可能的建造栅栏的位置，你需要帮助他判断哪些栅栏是有用的。一个栅栏是有用的当且仅当所有奶牛都在栅栏的同一侧。（如果有牛群在栅栏所在的直线上，那么栅栏是没用的），Farmer John 将会多次询问你一个栅栏是否有用，如果这个栅栏是有用的，需要输出 `YES`，反之输出 `NO`。

另外，Farmer John 也可能会带来一些新的奶牛加入这个牛群。一头牛加入之后，以后的所有询问中，这头牛也需要与其它的牛在栅栏的同一侧。


## 说明/提示

直线 $2x+2y=3$ 使得初始的三个牛群都在同侧；然而在该栅栏另一侧的牛群 $(1,1)$ 的加入使得它没有用了。

直线 $y=1$ 没用因为牛群 $(0,1)$，$(1,1)$ 恰好在它上面。

---

对于 $100\%$ 的数据，保证 $1\leq n\leq 10^5$，$1\leq q\leq 10^5$，所有牛群的坐标都各不相同且满足 $-10^9\leq x,y\leq 10^9$，$-10^9\leq A,B\leq 10^9$，$-10^{18}\leq C\leq 10^{18}$。

数据保证不存在栅栏满足 $A=B=0$。

## 样例 #1

### 输入

```
3 4 
0 0 
0 1 
1 0 
2 2 2 3 
1 1 1 
2 2 2 3 
2 0 1 1 
```

### 输出

```
YES 
NO 
NO 

```

# 题解

## 作者：BJpers2 (赞：9)

一道很好的计算几何题，结合了CDQ分治的思想，而且也不需要很毒瘤的前置知识（比如三维凸包，半平面交之类）。

为了表述方便，我们强制令$B \geq 0$

首先根据套路，遇到这种“只有插入，动态询问”的题目，往往可以往CDQ分治上面去想。

- 一个栅栏是有用的，当且仅当把它之前的所有点带入$Ax+By-C$中去计算，所得值的符号全部相同。又等价于最大，最小值同号。最大值在”以它为斜率的直线在上凸包上的切点”处取到(因为$B \geq 0$),特别地，当$B=0$,在凸包最右端取到。而最小值则相反。

下面只考虑在一次分治中如何转移最大值。

1. 构建上凸包。
2. 对所有直线按照斜率递减排序，竖线强制放在最后，实现上可以把每条非竖直线赋一个指向$x$轴正方向的方向向量，按后面$\times$前面$\leq 0$为基准排序,并令竖线方向指向下，就可以不用特判竖线了。
3. 此后类似于旋转卡壳，将斜率在$(slope(i-1,i),slope(i,i+1)]$中的所有直线的答案更新，在凸包两端的情况特殊注意。

最小值同理，注意几乎所有符号都要取反，且竖线要放左边。

最后判同号时千万别偷懒写$mx[i] \times mi[i]>0$ ,这样做稳爆$long$ $long$,我就因为这拍了半天一直没拍出来，写成$mx[i]<0 || mi[i]>0$就好了

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long ll;
const int N=200200,M=200200;
const ll INF=4e18;
int n,m,cp,cl,r;
ll mx[M],mi[M];
struct vec{
	ll  x,y;
	vec(){}
	vec(ll  a,ll  b){x=a;y=b;}
	vec operator + (vec a){return vec(x+a.x,y+a.y);} 
	vec operator - (vec a){return vec(x-a.x,y-a.y);}
	ll  operator ^ (vec a){return x*a.y-y*a.x;} 
}p[N],h[N],di[M];
struct lin{vec d;int i;}L[M];
struct qry{int o;ll x,y,z;}q[M];
void upd(int i,ll x,ll y){
	ll va=x*q[i].x+y*q[i].y;
	mx[i]=max(mx[i],va);
	mi[i]=min(mi[i],va);
}
bool cmp(vec a,vec b){return a.x==b.x?a.y<b.y:a.x<b.x;}
bool cmp1(lin a,lin b){return (a.d^b.d)>0;}
bool cmp2(lin a,lin b){return (a.d^b.d)<0;}
void sol(int l,int r){
	if(l==r) return;
	int md=(l+r)>>1;
	sol(l,md),sol(md+1,r);cp=cl=0;
	FOR(i,l,  md) if(q[i].o==1) p[++cp]=vec(q[i].x,q[i].y);
	FOR(i,md+1,r) if(q[i].o==2) L[++cl]=(lin){di[i],i};
	if(!(cp*cl)) return; 
	sort(p+1,p+cp+1,cmp);
	h[r=1]=p[1];
	FOR(i,2,cp){
		while(1<r && ((h[r]-h[r-1])^(p[i]-h[r]))<=0) r--;
		h[++r]=p[i];
	} 
	sort(L+1,L+cl+1,cmp1);
	int j=1;
	FOR(i,1,r){
		for(;(i+1>r || (L[j].d^(h[i+1]-h[i]))>=0) && j<=cl;j++) 
			upd(L[j].i,h[i].x,h[i].y);
	}//下凸包 
	
	h[r=1]=p[1];
	FOR(i,2,cp){
		while(1<r && ((h[r]-h[r-1])^(p[i]-h[r]))>=0) r--;
		h[++r]=p[i];
	} 
	sort(L+1,L+cl+1,cmp2);
	j=1;
	FOR(i,1,r){
		for(;(i+1>r || (L[j].d^(h[i+1]-h[i]))<=0) && j<=cl;j++) 
			upd(L[j].i,h[i].x,h[i].y);
	}//上凸包 
} 
int main(){
	scanf("%d%d",&n,&m);m+=n;
	FOR(i,1,n) q[i].o=1,scanf("%lld%lld",&q[i].x,&q[i].y);
	FOR(i,n+1,m){
		scanf("%d",&q[i].o);
		if(q[i].o==1) scanf("%lld%lld",&q[i].x,&q[i].y);
		if(q[i].o==2){
			scanf("%lld%lld%lld",&q[i].x,&q[i].y,&q[i].z);
			if(q[i].y<0) q[i].x*=-1,q[i].y*=-1,q[i].z*=-1; 
			if(q[i].y==0 && q[i].x<0) q[i].x*=-1,q[i].z*=-1;
			di[i]=vec(q[i].y,-q[i].x); 
			mx[i]=-INF;mi[i]=INF;
		}
	}
	sol(1,m);
	FOR(i,n+1,m)if(q[i].o==2) 
		mx[i]-q[i].z<0 || mi[i]-q[i].z>0?puts("YES"):puts("NO");
}
```


---

## 作者：agicy (赞：4)

本文将同步发布于：

- [洛谷博客](https://www.luogu.com.cn/blog/Lu-Anlai/solution-p3122)；
- [csdn](https://blog.csdn.net/Lu_Anlai/article/details/117361523)；
- [博客园](https://www.cnblogs.com/Lu-Anlai/p/14821992.html)；
- [简书](https://www.jianshu.com/p/e7fa365ea718)；

## 题目

题目链接：[洛谷 P3122](https://www.luogu.com.cn/problem/P3122)、[USACO 官网](http://www.usaco.org/index.php?page=viewproblem2&cpid=534)。

### 题意概述

给你平面上的一些点和直线，有两种操作：

- 新加入一个点 $(x,y)$；
- 给定一条直线 $ax+by=c$，询问是否所有点都在这条直线的同侧（在直线上不合法）。

初始时有 $n\leq 10^5$ 个点，共有 $q\leq 10^5$ 次操作。

## 题解

### 对题意转化

我们考虑将 **所有点都在直线的同一侧** 这一条件进行转化。

具体地，我们先考虑一个简单的子问题。

#### 简单子问题

问题是这样的，对于一条标准形式的直线 $ax+by+c=0$，在它同侧的点 $(x_p,y_p)$ 满足什么性质？

我们倒推并分类讨论：

- 若 $ax_p+by_p+c=0$，显然点 $(x_p,y_p)$ 在这条直线上；
- 若 $ax_p+by_p+c<0$，显然它与所有点 $q$ 满足 $ax_q+by_q+c<0$ 在直线的同侧；
- 若 $ax_p+by_p+c>0$，显然它与所有点 $q$ 满足 $ax_q+by_q+c>0$ 在直线的同侧；

因此我们发现，如果两个点在一条直线的同侧，则将两点坐标代入直线方程得到的结果同号。

---

解决了子问题，我们对题意进行转化，得到如下式子。

一条直线合法当且仅当

$$\forall p\in S,\operatorname{sgn}(ax_p+by_p-c)=\operatorname{sgn}(ax_q+by_q-c)$$

意思就是所有点对应的符号相同（暂时不考虑点在直线上）。

进一步地，一堆数同号说明它们的最大值与最小值同号。

问题转变成为，给定一条直线 $ax+by-c=0$，求

$$\max_{p\in S}\{ax_p+by_p-c\}$$
$$\min_{p\in S}\{ax_p+by_p-c\}$$

### 利用几何性质解决问题

先来求解最大值吧。

设直线为 $ax+by-c=\texttt{max}$。

先将直线转化为斜截式：

$$y=-\frac{a}{b}x+\frac{c+\texttt{sum}}{b}$$

我们发现：

- 若 $b>0$，我们只需要最大化该直线在 $y$ 轴上的截距即可，维护一个上凸包，在上凸包上二分斜率求解即可；
- 若 $b<0$，我们则可以通过变号等方法修改成为 $b>0$ 的情况；
- 若 $b=0$，我们发现此时的最大值必定在凸包的右端点取到，若用 $\texttt{max}$ 值作为判据，则不受影响，无需考虑。

再来求解最小值，还是一样的步骤：

设直线为 $ax+by-c=\texttt{min}$。

先将直线转化为斜截式：

$$y=-\frac{a}{b}x+\frac{c+\texttt{min}}{b}$$

我们发现：

- 若 $b>0$，我们只需要最小化该直线在 $y$ 轴上的截距即可，维护一个下凸包，在下凸包上二分斜率求解即可；
- 若 $b<0$，我们则可以通过变号等方法修改成为 $b>0$ 的情况；
- 若 $b=0$，我们发现此时的最小值必定在凸包的右端点取到，若用 $\texttt{min}$ 值作为判据，则不受影响，无需考虑。

### 分治方法优化转移

上述方法需要动态维护两个凸包，并且凸包的横坐标不具有单调性，这需要用 平衡树 来维护。

考虑到本题并不强制在线，我们考虑离线下来，利用 cdq 分治来维护凸包，时间复杂度为 $\Theta(n\log^2n)$（视作 $n,q$ 同阶）。

具体地，我们考虑对点和直线的加入时间进行分治，假设当前要处理区间 $[l,r]$ 内的事件。我们就只要考虑 区间 $[l,\texttt{mid}]$ 内的点形成的凸包对 区间 $[\texttt{mid}+1,r]$ 内直线的贡献即可。

维护凸包所需时间复杂度为排序的 $\Theta(n\log_2n)$，结合主定理分析可知最终时间复杂度为 $\Theta(n\log_2^2n)$。

### 参考程序

更多细节参见参考程序。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline ll readll(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(const char* s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

struct Vector{
	int x,y;
	inline Vector(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a)const{
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a)const{
		return Vector(x-a.x,y-a.y);
	}
};

inline ll dot(const Vector& a,const Vector& b){
	return 1ll*a.x*b.x+1ll*a.y*b.y;
}

inline ll cross(const Vector& a,const Vector& b){
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}

typedef Vector Point;

inline bool operator<(const Point& a,const Point& b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}

const int MAXN=1e5+5;
const int MAXQ=1e5+5;
const ll inf=5e18;

struct updates{
	int tim;
	Point p;
};

struct querys{
	int tim;
	int A,B;
	ll C;
	ll Max,Min;
};

int n,q;
int totu,totq;
updates up[MAXN+MAXQ];
querys qu[MAXQ];

inline ll getVal(const querys& q,const Point& p){
	return 1ll*q.A*p.x+1ll*q.B*p.y-q.C;
}

inline void solve(reg int l,reg int r,reg int lu,reg int ru,reg int lq,reg int rq){
	if(l==r)
		return;
	if(lu>ru||lq>rq)
		return;
	reg int mid=(l+r)>>1;
	reg int midu,midq;
	if(up[lu].tim<=mid){
		reg int __l=lu,__r=ru,__mid;
		while(__l<__r){
			__mid=(__l+__r)>>1;
			if(up[__mid+1].tim<=mid)
				__l=__mid+1;
			else
				__r=__mid;
		}
		midu=__l;
	}
	else
		midu=lu-1;
	if(qu[lq].tim<=mid){
		reg int __l=lq,__r=rq,__mid;
		while(__l<__r){
			__mid=(__l+__r)>>1;
			if(qu[__mid+1].tim<=mid)
				__l=__mid+1;
			else
				__r=__mid;
		}
		midq=__l;
	}
	else
		midq=lq-1;
	solve(l,mid,lu,midu,lq,midq);
	if(lu<=midu&&midq+1<=rq){
		reg int tot=0;
		static Point tmp[MAXN+MAXQ];
		for(reg int i=lu;i<=midu;++i)
			tmp[++tot]=up[i].p;
		sort(tmp+1,tmp+tot+1);
		reg int top;
		static Point S[MAXN+MAXQ];
		top=0;
		for(reg int i=1;i<=tot;++i){
			while(top>1&&cross(S[top]-S[top-1],tmp[i]-S[top-1])>=0)
				--top;
			S[++top]=tmp[i];
		}
		for(reg int i=midq+1;i<=rq;++i){
			reg int __l=1,__r=top,__mid;
			while(__l<__r){
				__mid=(__l+__r)>>1;
				if(getVal(qu[i],S[__mid])<getVal(qu[i],S[__mid+1]))
					__l=__mid+1;
				else
					__r=__mid;
			}
			qu[i].Max=max(qu[i].Max,getVal(qu[i],S[__l]));
		}
		top=0;
		for(reg int i=1;i<=tot;++i){
			while(top>1&&cross(S[top]-S[top-1],tmp[i]-S[top-1])<=0)
				--top;
			S[++top]=tmp[i];
		}
		for(reg int i=midq+1;i<=rq;++i){
			reg int __l=1,__r=top,__mid;
			while(__l<__r){
				__mid=(__l+__r)>>1;
				if(getVal(qu[i],S[__mid])>getVal(qu[i],S[__mid+1]))
					__l=__mid+1;
				else
					__r=__mid;
			}
			qu[i].Min=min(qu[i].Min,getVal(qu[i],S[__l]));
		}
	}
	solve(mid+1,r,midu+1,ru,midq+1,rq);
	return;
}

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i){
		++totu;
		up[totu].tim=0,up[totu].p.x=read(),up[totu].p.y=read();
	}
	for(reg int i=1;i<=q;++i){
		static int opt;
		opt=read();
		switch(opt){
			case 1:{
				++totu;
				up[totu].tim=i,up[totu].p.x=read(),up[totu].p.y=read();
				break;
			}
			case 2:{
				++totq;
				qu[totq].tim=i,qu[totq].A=read(),qu[totq].B=read(),qu[totq].C=readll(),qu[totq].Max=-inf,qu[totq].Min=inf;
				if(qu[totq].B<0)
					qu[totq].A=-qu[totq].A,qu[totq].B=-qu[totq].B,qu[totq].C=-qu[totq].C;
				else if((!qu[totq].B)&&qu[totq].A<0)
					qu[totq].A=-qu[totq].A,qu[totq].C=-qu[totq].C;
				break;
			}
		}
	}
	solve(0,q,1,totu,1,totq);
	for(reg int i=1;i<=totq;++i)
		writeln((!qu[i].Max||!qu[i].Min||((qu[i].Max^qu[i].Min)>>63))?"NO":"YES");
	flush();
	return 0;
}
```


---

## 作者：auroraaa (赞：2)

## 动态凸包
题解区都是离线 CDQ 分治做法，这里提供一个 set 在线维护动态凸包的做法。
## [点此看题](https://www.luogu.com.cn/problem/P3122)
### 题意转换
维护一个只加点不删点的动态凸包，多次询问一条直线是否和凸包有交点。

我们发现直接求直线和凸包的交点不可做，考虑固定直线的斜率，不断平移直线（即改变直线的 $c$ ），发现和凸包相交的所有直线是一个连续的区间，而且最上/下的两条直线和凸包恰好相切。

于是可以找见斜率为 $-\frac{a}{b}$ 的直线与凸包的两个切点，计算出 $c_{min},c_{max}$，通过判断 $c_{min} \le c \le c_{max}$ 来判断相交。

### 具体实现
考虑怎么找出和凸包的两条切线，按逆时针顺序将凸包上相邻两点的线段存起来，按极角排序，直接二分第一个斜率大于等于 $-\frac{a}{b}$ 的线段，它的起始点就是其中一个切点，画一下图就能证明，同理，按顺时针顺序可以找出另一个切点。

考虑维护动态凸包，凸包是一个直线时，直接用 vector 维护直线的两个端点，变成三角形后，我们以三角形的重心作为凸包的中心，然后开一个 set，按照和中心的极角排序。

每次加点时，先在 set 里二分出前驱和后继，用叉积不断 check 前驱和后继的合法性，如果凹进去就删掉，加点删点同时维护一下相邻两点的线段即可。


### 细节见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
#define double long double

struct Point{
    int x,y;
    Point(){}
    Point(int x,int y):x(x),y(y){}
    Point operator+(const Point&a)const{return {x+a.x,y+a.y};}
    Point operator-(const Point&a)const{return {x-a.x,y-a.y};}
    Point operator/(int a)const{return {x/a,y/a};}
    int cross(const Point&a)const{return x*a.y-y*a.x;}
    double ang()const{return atan2(y,x);}
    double angle;
    // 按相对于重心的极角排序
    bool operator<(const Point&a)const{return angle<a.angle;}
};
typedef Point Vector;
struct Line{
    Point p;
    Vector v;
    Line(){}
    Line(Point p,Vector v):p(p),v(v){}
    // 按方向向量的极角排序
    bool operator<(const Line&a)const{return v.ang()<a.v.ang();}
};

set<Point>st;   // 维护凸包
set<Line>st2;   // 维护凸包的所有边
set<Point>::iterator nxt,pre,nnxt,ppre,t1,t2;

void ins(Point p){
    nxt=st.lower_bound(p);
    if(nxt==st.begin())pre=prev(st.end());
    else pre=prev(nxt);
    if(nxt==st.end())nxt=st.begin();

    auto del=[&](const auto&it){
        if(it==st.begin())t1=prev(st.end());
        else t1=prev(it);
        t2=next(it);
        if(t2==st.end())t2=st.begin();
        st2.erase({*t1,*it-*t1});
        st2.erase({*it,*t2-*it});
        st2.emplace(*t1,*t2-*t1);
        st.erase(it);
    };
    // check 后继
    while(true){
        nnxt=next(nxt);
        if(nnxt==st.end())nnxt=st.begin();
        if((*nxt-p).cross(*nnxt-*nxt)<=0){
            del(nxt);
            nxt=nnxt;
        }
        else break;
    }
    // check 前驱
    while(true){
        if(pre==st.begin())ppre=prev(st.end());
        else ppre=prev(pre);
        if((*pre-*ppre).cross(p-*pre)<=0){
            del(pre);
            pre=ppre;
        }
        else break;
    }
    // check 当前点
    if((p-*pre).cross(*nxt-p)>0){
        st2.erase({*pre,*nxt-*pre});
        st2.emplace(*pre,p-*pre);
        st2.emplace(p,*nxt-p);
        st.insert(p);
    }
}

double ox,oy;
vector<Point>vec;
void ins2(int x,int y){
    if(vec.size()<=3)vec.emplace_back(x,y);
    if(vec.size()==3){
        // 凸包退化成直线
        if((vec[1]-vec[0]).cross(vec[2]-vec[0])==0){
            sort(vec.begin(), vec.end(),[&](Point a,Point b){return a.x==b.x?a.y<b.y:a.x<b.x;});
            vec[1]=vec[2];
            vec.pop_back();
            return;
        }
        ox=(vec[0].x+vec[1].x+vec[2].x)/3.0l;
        oy=(vec[0].y+vec[1].y+vec[2].y)/3.0l;
        for(auto&i:vec){
            i.angle=atan2(i.y-oy,i.x-ox);
            st.insert(i);
        }
        sort(vec.begin(), vec.end());
        st2.emplace(vec[0],vec[1]-vec[0]);
        st2.emplace(vec[1],vec[2]-vec[1]);
        st2.emplace(vec[2],vec[0]-vec[2]);
    }
    else if(vec.size()>3){
        Point p(x,y);
        p.angle=atan2(y-oy,x-ox);
        ins(p);
    }
}

void solve(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        ins2(x,y);
    }
    for(int i=1;i<=q;i++){
        int op,x,y,a,b,c;
        cin>>op;
        if(op==1){
            cin>>x>>y;
            ins2(x,y);
        }
        else{
            cin>>a>>b>>c;
            if(vec.size()<=3){
                // 直线时暴力
                int mx=-5e18,mn=5e18;
                for(auto p:vec){
                    mx=max(mx,a*p.x+b*p.y-c);
                    mn=min(mn,a*p.x+b*p.y-c);
                }
                if(mx<0 || mn>0)cout<<"YES"<<endl;
                else cout<<"NO"<<endl;
            }
            else{
                Line l;
                if(b!=0)l=Line(Point(0,0),Vector(b,-a));
                else l=Line(Point(0,0),Vector(0,1));
                int mn=5e18,mx=-5e18;
                auto cal=[&](){
                    auto it=st2.lower_bound(l);
                    if(it==st2.end())it=st2.begin();
                    int val=a*(*it).p.x+b*(*it).p.y;
                    mn=min(mn,val),mx=max(mx,val);
                };
                cal();
                l.v=Point(0,0)-l.v;
                cal();
                if(c<mn || c>mx)cout<<"YES"<<endl;
                else cout<<"NO"<<endl;
            }
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T=1;
//    cin>>T;
    while(T--){
        solve();
    }
}

---

## 作者：TonyYin (赞：1)

# 问题

给定 $q$ 次询问，每次询问有两种操作：

1. 向凸包中加入点 $(x,y)$.
2. 给定直线 $y=kx+b$，询问是否与凸包相交。

数据范围：$1\leq q\leq 10^5$.

# 凸包与直线的交

显然，我们首先需要维护上凸包和下凸包。

对直线作两条平行线，分别切于上凸包和下凸包。

![](https://cdn.tonyyin.top/2022/03/16/8098fc57b4f17.svg)

如图，找切点可以利用上下凸包的斜率单调性。

形式化地，对于斜率为 $k$ 的直线 $Ax+By=C$，我们要在上凸包找到点 $A_i(x_{a_i},y_{a_i})$ 满足 $\operatorname{slope}(\overrightarrow {A_{i-1}A_{i}})<k<\operatorname{slope}(\overrightarrow {A_{i}A_{i+1}})$，在下凸包中找到点 $B_i(x_{b_i}, y_{b_i})$ 满足 $\operatorname{slope}(\overrightarrow {B_{i-1}B_{i}})<k<\operatorname{slope}(\overrightarrow {B_{i}B_{i+1}})$.

之后，将 $(x_{a_i}, y_{a_i})$ 和 $(x_{b_i}, y_{b_i})$ 代入直线方程，得到 $C_a=A\cdot x_{a_i}+B\cdot y_{a_i}$ 和 $C_b=A\cdot x_{b_i}+B\cdot y_{b_i}$.

若 $C_b\leq C\leq C_a$ 或 $C_a\leq C\leq C_b$，说明直线与凸包相交，否则不交。

问题只剩下如何维护凸包。

# CDQ 分治优化

需要动态维护两个凸包，可以平衡树在线处理，但没必要。题目不要求在线，考虑离线下来利用 CDQ 分治优化，更加简单。

对每条直线记录两个变量，$\operatorname{mx}=\max\limits_{i=1}^n(A\cdot x_i + B\cdot y_i)$，$\operatorname{mn}=\min\limits_{i=1}^n(A\cdot x_i + B\cdot y_i)$， 代表把凸包中的每个点代入方程，所得到数值的最大值和最小值。

在此之后，只需判断 $\operatorname{mn} \leq C \leq \operatorname{mx}$ 是否成立即可。

与CDQ分治的大致思想相同，把初始的 $n$ 个点的时间戳设为 $[1,n]$，后面的操作从 $n+1$ 开始顺序排列。

设当前在处理区间 $[l,r]$，我们用 $[l,mid]$ 中的点来更新 $[mid+1, r]$ 区间中的线，这样以保证时间顺序。

每次分治过程中的更新操作：

1. 构建上凸包，线性，保证斜率按降序排序。
2. 把直线按照斜率降序排序。
3. CDQ 分治的常规操作，用左半部分更新右半部分中斜率在 $[\operatorname{slope}(\overrightarrow {A_{i-1}A_{i}}), \operatorname{slope}(\overrightarrow {A_{i}A_{i+1}})]$ 范围内的直线所对应的最大纵坐标。
5. 构建下凸包，直线按斜率升序排序，剩余操作与 $3$ 类似，更新纵坐标的最小值。

注意到，过程中利用了斜率单调性。观察发现，当 $Ax+By=C$ 的 $B<0$，也就是斜率为负时，会用上凸包更新最小值，下凸包更新最大值，会出现问题。

因此，对于所有 $Ax+By=C,B<0$，进行操作 $A\leftarrow -A$，$B\leftarrow -B$，$C\leftarrow -C$ 即可。

# 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
	int ret = 0, ch = getchar(), f = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1, ch = getchar(); }
	while(ch <= '9' && ch >= '0') {
		ret = ret * 10 + ch - '0';
		ch = getchar();
	}
	return ret * f;
}
const int MAXN = 4e5 + 10, inf = 0x3f3f3f3f3f3f3f3f;
int n, Q;
struct Point{
	int opt, x, y, z;
	Point() {}
	Point(int _x, int _y) { x = _x; y = _y; }
	Point(Point a, Point b): x(b.x - a.x), y(b.y - a.y) {} //从A指向B的向量
	friend Point operator + (const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	}
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	friend int operator * (const Point &a, const Point &b) {
		return a.x * b.y - a.y * b.x;
	}
} pt[MAXN], dir[MAXN], ch[MAXN];
typedef Point Vec;
inline bool cmp_p(Point A, Point B) { return A.x < B.x || (A.x == B.x && A.y < B.y); }
struct Query{
	int opt, x, y, z;
} q[MAXN];
struct Line{
	Line() {}
	Line(Point _v, int _id) { v = _v, id = _id; }
	Point v; int id;
} ln[MAXN];

inline bool cmp_l1(Line A, Line B) { return A.v * B.v < 0; }
inline bool cmp_l2(Line A, Line B) { return A.v * B.v > 0; }
int mx[MAXN], mn[MAXN];
inline bool check1(Point s1, Point s2, Point p) {
	return Vec(s2, s1) * Vec(s1, p) >= 0;
}
inline bool check2(Point s1, Point s2, Point p) {
	return Vec(s2, s1) * Vec(s1, p) <= 0;
}
inline void update(int id, int x, int y) {
	mx[id] = max(mx[id], x * q[id].x + y * q[id].y);
	mn[id] = min(mn[id], x * q[id].x + y * q[id].y);
}
void cdq(int l, int r) {
	if(l == r) return ;
	int mid = (l + r) >> 1;
	cdq(l, mid); cdq(mid + 1, r);

	int cntp = 0, cntl = 0;
	for(int i = l; i <= mid; i++) if(q[i].opt == 1) pt[++cntp] = Point(q[i].x, q[i].y);
	for(int i = mid + 1; i <= r; i++) if(q[i].opt == 2) ln[++cntl] = Line(dir[i], i);
	if(cntp == 0 || cntl == 0) return ;
	sort(pt + 1, pt + cntp + 1, cmp_p);
	//找上凸包
	int top = 0;
	ch[++top] = pt[1];
	for(int i = 2; i <= cntp; i++) {
		while(top > 1 && check1(ch[top], ch[top - 1], pt[i]))
			top--;
		ch[++top] = pt[i];
	}
	sort(ln + 1, ln + cntl + 1, cmp_l1);
	int j = 1;
	for(int i = 1; i <= top; i++) {
		while((i == top || ln[j].v * (ch[i + 1] - ch[i]) <= 0) && j <= cntl) {
			update(ln[j].id, ch[i].x, ch[i].y);
			j++;
		}
	}
	//找下凸包
	top = 0;
	ch[++top] = pt[1];
	for(int i = 2; i <= cntp; i++) {
		while(top > 1 && check2(ch[top], ch[top - 1], pt[i]))
			top--;
		ch[++top] = pt[i];
	}
	sort(ln + 1, ln + cntl + 1, cmp_l2);
	j = 1;
	for(int i = 1; i <= top; i++) {
		while((i == top || ln[j].v * (ch[i + 1] - ch[i]) >= 0) && j <= cntl) {
			update(ln[j].id, ch[i].x, ch[i].y);
			j++;
		}
	}
}
signed main() {
	n = read(), Q = read();
	for(int i = 1; i <= n; i++) q[i].x = read(), q[i].y = read(), q[i].opt = 1;
	Q += n;
	for(int i = n + 1; i <= Q; i++) {
		q[i].opt = read();
		if(q[i].opt == 1) q[i].x = read(), q[i].y = read();
		else {
			q[i].x = read(), q[i].y = read(), q[i].z = read();
			if(q[i].y < 0) q[i].x *= -1, q[i].y *= -1, q[i].z *= -1;
			if(q[i].y == 0 && q[i].x < 0) q[i].x *= -1, q[i].z *= -1;
			dir[i] = Point(q[i].y, -q[i].x);
			mx[i] = -inf, mn[i] = inf;
		}
	}
	cdq(1, Q);
	for(int i = n + 1; i <= Q; i++) if(q[i].opt == 2) {
		if(mx[i] - q[i].z < 0 || mn[i] - q[i].z > 0) puts("YES");
		else puts("NO");
	}
	return 0;
}
```




---

