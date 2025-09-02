# [COCI 2009 Final Exam#2] Dvapravca

## 题目描述

给定平面上的$N$个点$,$其中有一些是红的$,$其他是蓝的

现在让你找一对平行线$,$在满足在平行线之间没有蓝点$,$并且平行线不经过任何一个点的情况下$,$使得被夹在平行线之间的红色点个数最多

给出的点没有三点共线的情况$,$平行线可以不平行坐标轴

## 说明/提示

$N\le10^3,|x_i|,|y_i|\le10^9$

## 样例 #1

### 输入

```
4
0 0 R
0 1 B
1 1 R
1 0 B```

### 输出

```
2```

# 题解

## 作者：juruo999 (赞：6)

# P4385 Dvapravca 题解

[我的Blog](https://juruo999.blog.luogu.org/solution-p4385)  
[样例演示1](https://www.geogebra.org/m/j4sh5mbv)  
[样例演示2](https://www.geogebra.org/m/ryqzkt3b)

给定 $n$ 个红色或蓝色的点，**三点不共线**，求中间没有蓝点的两条平行线间最多能有几个红点。

显然，两条平行线一定不会是两点间的连线，否则将平行线旋转**足够小的**角度 $\delta$ 后可以得到另一个更优的解。

假设两条平行线都垂直于直线 $l$，过每个点作 $l$ 的垂线，得到 $n$ 个点，那么问题就转化为**求投影序列上的最长连续红色子段**。[样例演示1](https://www.geogebra.org/m/j4sh5mbv) 可以很直观的解释这个思路。

考虑动态维护这个序列。找出这 $n$ 个点间的所有连线，当 $l$ 垂直于连线时，就交换连线两端的点对应的颜色。看下面这张图就可理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/uahs62n6.png)

当你理解这一步时，你已经能做出这道题了。

用线段树维护最长连续零个数，时间复杂度 $O(n^2\log n)$。

 _P.S. 不用线段树，暴力维护连续零加上 `O2` 也能 AC……主要是我线段树写挂了！_ 

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>

using namespace std;

#define il inline
typedef long long ll;

ll gcd(ll a,ll b){
	return b==0?a:gcd(b,a%b);
}

typedef double Grad;

int n;
struct Node{
	int x,y;
	int p;
	char c;
}a[1005];
bool cmp(Node a,Node b){
	return a.x!=b.x?a.x<b.x:a.y>b.y;
}

int s[1005];

struct Line{
	int i1,i2;	// id
	Grad G;
	Line(){} Line(int a_,int b_){i1=a_,i2=b_;G=1.0*(a[i2].y-a[i1].y)/(a[i2].x-a[i1].x);}
	bool operator<(Line b){
		return G<b.G;
	}
}ls[1000006];
int ms=0;

vector<pair<int,int> > sw[1000006];int st;

int did[1006],id[1006];

int main(){

	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].c=getchar(); while(a[i].c!='R' && a[i].c!='B'){ a[i].c=getchar(); }
	}
	sort(a+1,a+n+1,cmp);
	
	for(int i=1;i<=n;i++){
		s[i]=((a[i].c=='R')?0:1);
	}

	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			ls[++ms]=Line(i,j);
		}
	}
	sort(ls+1,ls+ms+1);
	st=1;sw[1].push_back(make_pair(ls[1].i1,ls[1].i2));
	for(int i=2;i<=ms;i++){
		if(ls[i].G!=ls[i-1].G){
			st++;
		}
		sw[st].push_back(make_pair(ls[i].i1,ls[i].i2));
	}
   
	int ans=0;
	int l=1;		// 永远焕发光芒的暴力维护区间
	for(int j=1;j<=n;j++){
		if(s[j]==1){
			l=j+1;
		}
		if(s[l]==0 && s[j]==0){ans=max(ans,j-l+1);}
	}

	for(int i=1;i<=n;i++){id[i]=did[i]=i;}

	for(int i=1;i<=st;i++){
		for(int j=0;j<sw[i].size();j++){
			int x=sw[i][j].first,y=sw[i][j].second,u,v;

			swap(did[x],did[y]);
			swap(id[did[x]],id[did[y]]);
			u=s[did[x]],v=s[did[y]];
			s[did[x]]=v,s[did[y]]=u;	// 完全没用的调试信息
		}
		
		int l=1;	// 运用反复的修辞手法
		for(int j=1;j<=n;j++){
			if(s[j]==1){
				l=j+1;
			}
			if(s[l]==0 && s[j]==0){ans=max(ans,j-l+1);}
		}
		
	}

	printf("%d\n",ans);

	return 0;
}
```

---

## 作者：Kelin (赞：3)

## [题意](https://blog.csdn.net/BeNoble_/article/details/79855890)

给定平面上的$N$个点$,$其中有一些是红的$,$其他是蓝的

现在让你找一对平行线$,$在满足在平行线之间没有蓝点$,$并且平行线不经过任何一个点的情况下$,$使得被夹在平行线之间的红色点个数最多

给出的点没有三点共线的情况$,$平行线可以不平行坐标轴

---

## 题解

做一条垂直于平行线的线$,$然后把所有点排序后都投影到这条线上形成一个序列

那么考虑在序列上我们要求的就是最长全红子串了

这个可以用线段树直接维护$;$考虑到平行线的角度会变

那么答案就是我们把这条垂线在旋转$180^\circ$的过程中所有投影序列的答案的最大值

我们显然不能直接去旋转$,$考虑要怎么样投影序列才会发生变化

![这里写图片描述](https://img-blog.csdn.net/20180408173509394?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JlTm9ibGVf/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

投影序列是$\{1,2,3,4\}$,那么颜色序列就是$1001,$答案是$1$

![这里写图片描述](https://img-blog.csdn.net/20180408174445827?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JlTm9ibGVf/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

当投影线是$L1$时投影序列是$\{1,2,3,4\}$

当投影线是$L2$时投影序列是$\{1,2,4,3\}$

也就是说当投影线的斜率从小于两点连线垂线$(Lx)$斜率到大于他的过程中这两个点在投影序列上的位置会互换

因为垂线的斜率和原直线的斜率是一一对应的$,$那么我们可以直接按照两点之间的连线的斜率排序

那么旋转投影线每次就可以直接旋转到下一个垂线的位置

即使有两点投影位置相同也没关系$,$因为我们可以微调一下

注意对于所有斜率相同的直线我们需要一次性在线段树上处理完

因为总共有$n^2$条线$,$所以会发生$n^2$次交换$,$所以复杂度是$O(n^2\log n)$的

>$Hint:$

>连线的方向和转动的方向要一致(需要脑补一下)

>斜率判等的精度要高一点

---

## 作者：newbiechd (赞：2)

# [COCI2009]Dvapravca

[LG传送门](https://www.luogu.org/problemnew/show/P4385)

[蒟蒻的Blog](https://www.cnblogs.com/cj-chd/p/10235775.html)

先给出考场上的$O(n^3)$乱搞方法：枚举一个蓝点和一个红点，找出过着两个点的直线，再枚举蓝点找出这条直线最多能往两边扩展多宽，最后枚举红点计算贡献。

注意在确定一条直线能往两边扩展多宽时不要求点到直线的距离，否则常数会太大，只要求竖直方向的距离就可以了。正确性显然，具体看代码。

现在有个重要的问题，求大佬来解决：如果直接这样写会被卡到65到70分，但是如果把蓝点和红点按$x$为第一关键字$y$为第二关键字从小到大排个序，就能得到90至100分（考试时用的评测机能跑到90分，洛谷神机上能切）。然而我不会证明这样究竟优化在哪里，求大佬证明。

```cpp
#include<cstdio>
#include<algorithm>
#define R register
#define I inline
#define D double
using namespace std;
const int N=1003,inf=0x3f3f3f3f;
struct V{int x,y;}r[N],b[N];
struct L{D k,b;}f;
I int operator<(V a,V b){return a.x^b.x?a.x<b.x:a.y<b.y;}
I D min(D x,D y){return x<y?x:y;}
I int max(int x,int y){return x>y?x:y;}
I L lin(V a,V b){
    if(a.x==b.x)
        return (L){inf,0};
    D k=(D)(b.y-a.y)/(b.x-a.x);
    return (L){k,(D)a.y-k*a.x};
}
I D dst(V a){return f.k*a.x+f.b-a.y;}
int main(){
    R int n,x,y,i,j,t,p=0,q=0,g,h,o=0;
    R char c[2];
    D d,u,v;
    scanf("%d",&n);
    for(i=1;i<=n;++i){
        scanf("%d%d%s",&x,&y,c);
        if(c[0]=='R')
            r[++p]=(V){x,y};
        else
            b[++q]=(V){x,y};
    }
    sort(b+1,b+q+1),sort(r+1,r+p+1);//就是这里，不加会慢很多
    for(i=1;i<=q;++i)
        for(j=1;j<=p;++j){
            f=lin(b[i],r[j]),u=v=inf,g=h=1;
            for(t=1;t<=q;++t)
                if(t^i)
                    if((d=dst(b[t]))>0)
                        u=min(u,d);
                    else
                        v=min(v,-d);
            for(t=1;t<=p;++t)
                if(t^j)
                    if((d=dst(r[t]))>0)
                        g+=d<u;
                    else
                        h+=-d<v;
            o=max(o,max(g,h));
        }
    printf("%d",o);
    return 0;
}

```

亲测如果没加sort应该是过不了的，xzz大神仙尝试把坐标系随机旋转了一下，变得更快了。所以这道题告诉我们一个经验：碰见不会的计算几何题，先随机旋转坐标系，再把点排一遍序，打起暴力更有自信！

还是放一下正解$O(n^2 log n)$的做法吧。考虑如果要求直线垂直于$x$轴，那么如果把点按刚才所说的排一遍序，要求的就是序列上连续的最长的$1$的个数（如果把红色视作$1$）。由于直线可以倾斜，考虑旋转坐标系，当某两个点连线的斜率与当前$y$轴在原坐标系中的斜率相等时，这两个点在序列上的位置就会交换，这下可以用线段树来维护，由于最多交换$O(n^2)$次顺序，复杂度是$O(n^2 log n)$。

```cpp
#include<cstdio>
#include<algorithm>
#define R register
#define I inline
#define D double
using namespace std;
const int N=1003,M=1000003,S=4003;
int f[N],n;
struct T{int f,l,r,d;}e[S];
struct V{int x,y,c;}p[N];
struct L{D k; int x,y;}q[M];
I int operator<(V a,V b){return a.x^b.x?a.x<b.x:a.y<b.y;}
I int operator<(L a,L b){return a.k>b.k;}
I int max(int x,int y){return x>y?x:y;}
I T operator+(T x,T y){
	T z;
	z.f=max(x.r+y.l,max(x.f,y.f)),z.d=x.d+y.d;
	if(x.l==x.d)
		z.l=x.d+y.l;
	else
		z.l=x.l;
	if(y.r==y.d)
		z.r=x.r+y.d;
	else
		z.r=y.r;
	return z;
}
I void swp(int&x,int&y){x^=y,y^=x,x^=y;}
I void upd(int k,int v){e[k]=(T){v,v,v,1};}
I void bld(int k,int l,int r){
	if(l==r){
		upd(k,p[l].c);
		return ;
	}
	R int p=k<<1,q=p|1,m=l+r>>1;
	bld(p,l,m),bld(q,m+1,r),e[k]=e[p]+e[q];
}
void mdf(int k,int l,int r,int x,int v){
	if(l==r){
		upd(k,v);
		return ;
	}
	R int p=k<<1,q=p|1,m=l+r>>1;
	if(x<=m)
		mdf(p,l,m,x,v);
	else
		mdf(q,m+1,r,x,v);
	e[k]=e[p]+e[q];
}
int main(){
	R int i,j,x,y,t=0,o;
	R char c[2];
	scanf("%d",&n);
	for(i=1;i<=n;++i){
		scanf("%d%d%s",&x,&y,c);
		if(c[0]=='R')
			p[i]=(V){x,y,1};
		else
			p[i]=(V){x,y,0};
	}
	sort(p+1,p+n+1);
	for(i=1;i<=n;++i)
		f[i]=i;
	for(i=1;i<n;++i)
		for(j=i+1;j<=n;++j)
			q[++t]=(L){(D)(p[j].y-p[i].y)/(p[j].x-p[i].x),i,j};
	sort(q+1,q+t+1),bld(1,1,n),o=e[1].f;
	for(i=1;i<=t;++i){
		x=f[q[i].x],y=f[q[i].y],swp(f[q[i].x],f[q[i].y]);
		if(p[x].c^p[y].c)
			swp(p[x].c,p[y].c),mdf(1,1,n,x,p[x].c),mdf(1,1,n,y,p[y].c),o=max(o,e[1].f);
	}
	printf("%d",o);
	return 0;
}

```





---

## 作者：λᴉʍ (赞：0)

首先特判掉蓝点数量$<2$的情况。没有蓝点答案就是$n$，有一个蓝点可以枚举一个红点，选择过这个蓝点和红点的一条线和在无穷远处的平行线（即这条线对应的两个半平面）。

这里认为过一个点是与这个点无限接近，红点的话认为红点在平行线中，蓝点不在平行线中

构造方案的时候想象两个阶段：

- 如果有一条线不过蓝点，可以继续向外扩张直到过蓝点为止，现在两条平行线固定过两个蓝点
- 如果没有平行线过红点，可以旋转这两条平行线知道一个平行线过红点为止。这个过程不会损失红点，而且可能加入新的红点。

所以结论是：两条平行线肯定分别过两个蓝点，而且还有一条平行线过一个红点。

先枚举一个蓝点和一个红点，一条线过这两个点；然后找到在两个方向距离这条线最近的蓝点，直接算红点数量即可。

复杂度$O(n^3)$。

直接做肯定过不去，所以先把整张图随机旋转，然后按照x坐标排序。

时间的正确性请咨询@Leo______ 。

```cpp
#include<bits/stdc++.h>
#define il inline
#define vd void
il int gi(){
    int x=0,f=0;char ch=getchar();
    while(!isdigit(ch))f^=ch=='-',ch=getchar();
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}
struct point{double x,y;}r[1010],b[1010];
il bool operator<(const point&a,const point&b){return a.x<b.x;}
char col;
int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    int n=gi(),R=0,B=0;
    srand(time(NULL));
    double v=rand()%1000*0.1+0.1;
    for(int i=1;i<=n;++i){
        int _x=gi(),_y=gi();
        do col=getchar();while(col!='R'&&col!='B');
        if(col=='R')r[++R]=(point){sin(v)*_x-cos(v)*_y,sin(v)*_y-cos(v)*_x};
        else b[++B]=(point){sin(v)*_x-cos(v)*_y,sin(v)*_y-cos(v)*_x};
    }
    std::sort(r+1,r+R+1);
    std::sort(b+1,b+B+1);
    if(!B)return printf("%d\n",n),0;
    int ans=0;
    double kk,bb,dist,dist_up,dist_dn;
    int upans,dnans;
    for(int i=1;i<=B;++i)
        for(int j=1;j<=R;++j){
            kk=1.0*(b[i].y-r[j].y)/(b[i].x-r[j].x),bb=b[i].y-kk*b[i].x;
            dist_up=1e18,dist_dn=1e18;
            for(int k=1;k<=B;++k)
                if(k!=i){
                    dist=kk*b[k].x+bb-b[k].y;
                    if(dist<0){
                        if(-dist<dist_up)dist_up=-dist;
                    }else{
                        if(dist<dist_dn)dist_dn=dist;
                    }
                }
            upans=1,dnans=1;
            for(int k=1;k<=R;++k)
                if(k!=j){
                    dist=kk*r[k].x+bb-r[k].y;
                    if(dist<0){
                        if(-dist<=dist_up+1e-7)++upans;
                    }else{
                        if(dist<=dist_dn+1e-7)++dnans;
                    }
                }
            ans=std::max(ans,std::max(upans,dnans));
        }
    printf("%d\n",ans);
    return 0;
}
```


---

