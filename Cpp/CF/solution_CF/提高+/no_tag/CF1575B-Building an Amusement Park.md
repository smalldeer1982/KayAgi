# Building an Amusement Park

## 题目描述

Mr. Chanek lives in a city represented as a plane. He wants to build an amusement park in the shape of a circle of radius $ r $ . The circle must touch the origin (point $ (0, 0) $ ).

There are $ n $ bird habitats that can be a photo spot for the tourists in the park. The $ i $ -th bird habitat is at point $ p_i = (x_i, y_i) $ .

Find the minimum radius $ r $ of a park with at least $ k $ bird habitats inside.

A point is considered to be inside the park if and only if the distance between $ p_i $ and the center of the park is less than or equal to the radius of the park. Note that the center and the radius of the park do not need to be integers.

In this problem, it is guaranteed that the given input always has a solution with $ r \leq 2 \cdot 10^5 $ .

## 说明/提示

In the first example, Mr. Chanek can put the center of the park at $ (-3, -1) $ with radius $ \sqrt{10} \approx 3.162 $ . It can be proven this is the minimum $ r $ .

The following illustrates the first example. The blue points represent bird habitats and the red circle represents the amusement park.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1575B/54e2f785adec78851495651eb26cc87067684ebf.png)

## 样例 #1

### 输入

```
8 4
-3 1
-4 4
1 5
2 2
2 -2
-2 -4
-1 -1
-6 0```

### 输出

```
3.1622776589```

## 样例 #2

### 输入

```
1 1
0 0```

### 输出

```
0.0000000000```

# 题解

## 作者：djwj223 (赞：14)

[题目](https://www.luogu.com.cn/problem/CF1575B)

这题的题解似乎都没我这种简洁？

大水题，建议评 $\textcolor{blue}{blue}$。

发现这题中半径小的时候能满足，则半径更大些必然能满足，于是考虑二分答案。

而枚举到固定半径，就可以知道一个点贡献答案的范围，差分一下，最后求差分数组最大前缀和即可。

画一下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/135cu1wm.png)

发现点的答案贡献范围即为:

$$\arctan \left( \frac{y_i}{x_i} \right) -\arccos \left( \frac{dis(node_0,node_i)}{d} \right)$$

到

$$\arctan \left( \frac{y_i}{x_i} \right) +\arccos \left( \frac{dis(node_0,node_i)}{d} \right)$$

好这题做完了，稍微注意下细节。

Code：

```cpp
#include<bits/stdc++.h>
#define db double
#define mp make_pair
#define fi first
#define se second
#define PDD pair<double,double>
#define pi 3.14159265358979
using namespace std;
const int M=1e5+7; const db Eps=1e-6;
int n,k; PDD a[M+M+1];
db x[M],y[M],l,r=2e5,mid;
db dis(int i){
	return sqrt(x[i]*x[i]+y[i]*y[i]);
}
bool cmp(PDD a,PDD b){
	if(a.fi!=b.fi) return a.fi<b.fi;
	return a.se>b.se;
}
int check(db r){
	int ans=0,s=0,t=0; db af,bt,d=r+r;
	for(int i=1;i<=n;i++) if(dis(i)<=d){
		af=atan2(x[i],y[i]),bt=acos(dis(i)/d);
		a[++t]=mp(af-bt<-pi?af-bt+3*pi:af-bt+pi,1);
		a[++t]=mp(af+bt>pi?af+bt-pi:af+bt+pi,-1);
		s+=(a[t].fi<a[t-1].fi);
	}
	sort(a+1,a+t+1,cmp);
	for(int i=1;i<=t;i++)
		s=max(s,0)+a[i].se,ans=max(s,ans);
	return ans>=k;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&x[i],&y[i]);
	while(r>l+Eps){
		mid=(l+r)*0.5;
		if(check(mid)) r=mid;
		else l=mid;
	}
	printf("%.7lf",l);
	return 0;
}
```

$s$ 是用来记录我割开圆变成链，割开处有多少点能产生贡献的

完结撒花~

---

## 作者：letitdown (赞：3)

转化一下题意，有一个以原点为圆心，$r$ 为半径的圆，求最小的 $r$ 满足使得圆周上的某个点，同时被包括在至少 $k$ 个以某个特殊点为圆心，半径为 $r$ 的圆内。

显然当比较小的半径满足条件时，大的半径也会满足条件，所以可以考虑二分答案。

那么现在问题就在如何检查答案合法性了。

当原点和另一个点的距离大于 $2r$ 时，两个圆显然没有交点，没有贡献。

当这个点与原点重复时相当于对于圆上的每一个点都有一的贡献。

否则，这个点和原点的距离在 $0$ 与 $2r$ 之间，形成的两个圆一定有两个交点，且这两个交点与原点连线的夹角在一个平角之内，被包含在这个角之内的圆上的点都有一的贡献。

~~第三种情况有点抽象？~~ 上图：

![](https://i.loli.net/2021/11/09/HgylVFROP9IUtbc.png)

如图，在以 $EF$ 为两个端点的弧上的点都有一的贡献

于是对于第一种情况直接跳过，对于第二种情况开一个计数器，对于第三种情况，还是用上面的图，我们求出线段 $AF$ 和 $AE$ 的角度，在线段树上区间修改即可。

求角度时，先连接 $AC$，$EF$ 交于点 $G$，勾股定理求出 $EG$ 再求得 $\angle EAG$，利用点 $C$ 坐标求出 $AC$ 的角度，于是一加一减就分别是 $AE$ 和 $AF$ 的角度了。

下标怎么用浮点数类型？可以动态开点啦~

```cpp
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
namespace EMT{
	typedef long long ll;typedef long double db;//(double)clock() / (double)CLOCKS_PER_SEC;
	#define pf printf
	#define F(i,a,b) for(register int i=a;i<=b;i++)
	#define D(i,a,b) for(register int i=a;i>=b;i--)
	inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
	inline void file(){freopen("in.in","r",stdin);freopen("my.out","w",stdout);}
	inline int max(int a,int b){return a>b?a:b;}inline int min(int a,int b){return a<b?a:b;}
	inline void pi(db x){pf("%.10Lf ",x);}inline void pn(){pf("\n");}
	const int N=1e5+10;const db pai=acos(-1.0);
	int n,k,rt;
	struct point{int x,y;}p[N];
	inline db dis(int x1,int y1,int x2,int y2){return sqrt(1ll*(x1-x2)*(x1-x2)+1ll*(y1-y2)*(y1-y2));}
	struct seg{
		int tot,val[N*60],lz1[N*60],ls[N*60],rs[N*60];bool lz2[N*60];
		inline void down(int p){
			if(lz2[p]){
				if(ls[p]){
					lz1[ls[p]]=val[ls[p]]=0;
					lz2[ls[p]]=1;
				}
				if(rs[p]){
					lz1[rs[p]]=val[rs[p]]=0;
					lz2[rs[p]]=1;
				}
				lz2[p]=0;
			}
			if(lz1[p]){
				if(!ls[p])ls[p]=++tot;
				if(!rs[p])rs[p]=++tot;
				val[ls[p]]+=lz1[p],
				lz1[ls[p]]+=lz1[p],
				val[rs[p]]+=lz1[p],
				lz1[rs[p]]+=lz1[p],
				lz1[p]=0;
			}
		}
		inline void change(int &p,db l,db r,db ql,db qr,int v){
			if(!p)p=++tot;
			if((l>=ql&&r<=qr)||r-l<=1e-4){
				lz1[p]+=v;
				val[p]+=v;
				return;
			}db mid=(l+r)/2.0;down(p);
			if(qr<=mid)change(ls[p],l,mid,ql,qr,v);
			else if(ql>mid)change(rs[p],mid,r,ql,qr,v);
			else change(ls[p],l,mid,ql,mid,v),change(rs[p],mid,r,mid,qr,v);
			val[p]=max(val[ls[p]],val[rs[p]]);
		}
	}segm;
	inline db range(db x){return (x>=0&&x<=2.0*pai)?x:(x<0?x+2.0*pai:x-pai*2.0);}
	inline bool check(db r){
		int ans=0;
		segm.val[1]=segm.lz1[1]=0,segm.lz2[1]=1;
		F(i,1,n){
			db d=dis(0,0,p[i].x,p[i].y);
			if(d>2.0*r)continue;
			if(p[i].x==0&&p[i].y==0){ans++;continue;}
			db base=atan2(p[i].y,p[i].x),half=d/2.0,h=sqrt(r*r-half*half),on=atan2(h,half);
			db x1=range(base+on),x2=range(base-on);
			if(x2<=x1)segm.change(rt,0,2*pai,x2,x1,1);
			else segm.change(rt,0,2.0*pai,x2,2.0*pai,1),segm.change(rt,0,2.0*pai,0,x1,1);
		}
		return ans+segm.val[1]>=k;
	}
	inline short main(){
		n=read();k=read();
		F(i,1,n)p[i].x=read(),p[i].y=read();
		db l=0,r=2e5,ans;
		while(r-l>=1e-6){
			db mid=(l+r)/2.0;
			if(check(mid))r=mid,ans=mid;
			else l=mid;
		}pi(ans);
		return 0;
	}
}
signed main(){return EMT::main();}
```

---

## 作者：rpdg (赞：2)

[更屑的阅读体验](https://www.cnblogs.com/rpdg-bz/p/15407515.html)

**注：** 本文中的弧都指劣弧，角度都是弧度制（C++ 不就是吗），若无下表标记，所有角一概指内角。

#### Description

平⾯上有 $n$ 个点，你要找⼀个圆，使得 $(0,0)$ 点在圆周，并且覆盖了⾄少 $k$ 个点。

问最⼩的半径是多少。

#### Solution

我们不难发现，如果半径为 $r$ 可以，那么 $\ge r$ 的半径照样可以（答案满足单调性），所以我们考虑二分。

设我们二分了一个半径 $r$，那么我们如何判断答案可行呢?

我们发现，$(0,0)$ 必须在圆周，那么圆心和原点的距离就是 $r$，所以圆心可能的位置就是在以原点为圆心，以 $r$ 为半径的圆上。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5vf7urss.png)

对于其他点，我们发现如果圆要包含他们，圆心一定在以这个点为圆心，以 $r$ 为半径的**圆内**（注意，是圆内）。

我们假设有一个点 $C$，假设它可以被包含，那么圆心的位置就是下图中的 $\overset{\frown}{DE}$（$\odot A$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/cfr5s3vy.png)

我们将这些弧都打上标记，如果有一个点被打了 $\ge k$ 的标记，那么这个答案就一定可以。

具体怎么实现呢？

我们可以差分。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/1tbp1gkg.png)

我们将 $\vec{u}$ 和 $\vec{v}$ 的极角打上标记（就是在 $\vec{u}$ 打上 $1$，在 $\vec{v}$ 打上 $-1$，差分都会吧？）。

最后，我们极角排序后遍历所有标记，用一个计数器 $cnt$ 来判断标记数，如果 $cnt \ge k$，这个答案肯定合法。

为了方便，以下负数角我们都把它转成 $[0,2\pi]$ 区间中的角（因为 $\alpha + 2\pi$ 和 $\alpha$ 是等价的）。

极角怎么求？

![](https://cdn.luogu.com.cn/upload/image_hosting/i993ukjk.png)

我们要求的就是 $\angle DAB$ 和 $\angle EAB$。

我们设 $\angle CAB$（$\overrightarrow{AC}$ 的极角）$= \alpha$，$\angle CAE = \beta$

不难发现，四边形 $ABCD$ 是菱形（四边都是 $r$），那么 $AF=\frac{AC}{2}$，且 $DE \bot AC$，那么 $\frac{AF}{AE} = \cos \beta$，则 $\beta = \arccos \frac{AF}{AE}$。

所以 $\angle DAB = \alpha + \beta$，$\angle EAB = \alpha - \beta$。

但这只是一种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/n8dsejo1.png)

$\alpha < \beta$ 了，我们为方便，将负数角转成正数角，即 $\angle DAB = \alpha + \beta$，$\angle EAB = \alpha - \beta + 2\pi$。

但是这个时候 $\angle EAB > \angle DAB$ 了，我们怎么打标记？

我们可以把 $\overset{\frown}{DE}$ 拆成 $\overset{\frown}{DB}$ 和 $\overset{\frown}{EB}$ 两部分，分别打标记。

具体怎么写可以看代码。

![](https://cdn.luogu.com.cn/upload/image_hosting/35rgoodt.png)

我们发现这个 $\alpha$ 是负数了，怎么办？

我们把 $\alpha$ 加上 $2\pi$，同第一种情况处理。

![](https://cdn.luogu.com.cn/upload/image_hosting/2b8jq8kg.png)

$\alpha < 0 $ 且 $ -\alpha < \beta$。

此时 $\angle DAB = \beta - (-\alpha) = \beta + \alpha$，$\angle EAB_{外} = 2\pi - (-\alpha +\beta )$。

同情况2处理。

~~其实情况和1情况3本质上一样，情况2和情况4也是，但我还要分讨，果然没题解贺的我就是菜狗，望 dalao 不要 D~~

代码（有坑，能被 hack，请自己写）

```cpp
#include<bits/stdc++.h>
#define pi acos(-1)
using namespace std;
const int N=3e5+8;
const double eps=1e-6;
inline int read() {
    int s=1,a=0;char c=getchar();
    while(!isdigit(c)) s=(c=='-')?(-s):s,c=getchar();
    while(isdigit(c)) a=(a<<3)+(a<<1)+c-'0',c=getchar();
    return s*a;
}
struct vec {
    double angle;
    int opt;
    bool operator <(const vec &fff) const {
        return angle<fff.angle;
    }
};
struct node {
    double x,y;
} nd[N];
vector <vec> G;
int n,k;
double mx;
bool check(double mid) {
    double r=mid;
    G.clear();
    // printf("%.5f\n",mid);
    for(int i=1; i<=n; i++) {
        double d=sqrt(nd[i].x*nd[i].x+nd[i].y*nd[i].y);
        if(d-2*r>=eps) continue;
        double alpha=atan2(nd[i].y,nd[i].x),beta=acos(d/(2*r));
        if(alpha>beta&&alpha>0) {
            G.push_back((vec){alpha-beta,1});
            G.push_back((vec){alpha+beta,-1});
        }
        else if(alpha>0&&alpha<beta) {
            G.push_back((vec){0,1});
            G.push_back((vec){alpha+beta,-1});
            G.push_back((vec){alpha-beta+2*pi,1});
            G.push_back((vec){2*pi,-1});
            // G.push_back((vec){alpha+2*pi});
        }
        else if(-alpha>beta){
            alpha+=2*pi;
            G.push_back((vec){alpha-beta,1});
            G.push_back((vec){alpha+beta,-1});
        }
        else {
            G.push_back((vec){0,1});
            G.push_back((vec){beta+alpha,-1});
            G.push_back((vec){2*pi-(beta-alpha),1});
            G.push_back((vec){2*pi,-1});
        }
    }
    int cnt=0;
    sort(G.begin(),G.end());
    for(auto v:G) {
        cnt+=v.opt;
        if(cnt>=k) return 1;
    }
    return 0;
}
int main() {
    n=read(),k=read();
    for(int i=1; i<=n; i++) {
        int x=read(),y=read();
        nd[i].x=x*1.0,nd[i].y=y*1.0;
        mx=max(sqrt(nd[i].x*nd[i].x+nd[i].y*nd[i].y),mx);
        // printf("%.5f\n",mx);
    }
    double l=0.0000,r=mx,ans=0.0;
    while(r-l>eps) {
        double mid=(l+r)/2.0;
        if(check(mid)) r=mid;
        else l=mid;
    }
    printf("%.5f",r);
    return 0;
}
```

---

