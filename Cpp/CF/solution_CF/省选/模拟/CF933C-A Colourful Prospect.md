# A Colourful Prospect

## 题目描述

Firecrackers scare Nian the monster, but they're wayyyyy too noisy! Maybe fireworks make a nice complement.

Little Tommy is watching a firework show. As circular shapes spread across the sky, a splendid view unfolds on the night of Lunar New Year's eve.

A wonder strikes Tommy. How many regions are formed by the circles on the sky? We consider the sky as a flat plane. A region is a connected part of the plane with positive area, whose bound consists of parts of bounds of the circles and is a curve or several curves without self-intersections, and that does not contain any curve other than its boundaries. Note that exactly one of the regions extends infinitely.

## 说明/提示

For the first example,

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF933C/14c0de76a74c3258bd3ded40e0d00e7a0e02f324.png)For the second example,

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF933C/3893f9bc640d7c681b3a0c6aad769a8cc35a6b03.png)For the third example,

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF933C/6be8f427aaa2ce9d8da71a1bbf6003246592b3ca.png)

## 样例 #1

### 输入

```
3
0 0 1
2 0 1
4 0 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
0 0 2
3 0 2
6 0 2
```

### 输出

```
6
```

## 样例 #3

### 输入

```
3
0 0 2
2 0 2
1 1 2
```

### 输出

```
8
```

# 题解

## 作者：ycyaw (赞：4)

调了一下午才调出来。主要是这道题的数据太能构造了，导致每次改完都只能多过几个点。

对于这种问平面被图形分割成几个部分的题，如果你对欧拉公式熟悉的话，发现直接套用就好：
$$
V-E+R=2
$$
其中，$V$是交点个数，$E$是边数，$R$是被分割的平面数
。
由于这道题几个分割的圆可以不连通，改一下公式即可：
$$
V-E+R=C+1
$$
其中$C$是平面上圆所构成的联通块个数。

发现答案就是求$R$，所以我们考虑求出$V,E,C$：

首先是求$V$，也是最麻烦的一个，其实就是圆与圆求交点，然后进行去重。$dalao$请略过。我是直接利用两个圆的解析方程相减，求出经过交点的直线，然后再直线与圆求交。~~应该有更简单的方法，我太菜了。~~ 具体在草稿纸上手算一下即可，然后存下所有的点排序去重。

$WA$了十多次，最后发现主要是求直线与圆的交点，解一元二次方程算$delta$的时候，如果两圆刚好相切，算出来总是$-0.0000000\dots$导致错误。所以用$eps$判一下

求$E$，直接统计每个圆上的交点个数，累加即可。

求$C$，对于有交的两个圆，用并查集并起来，最后就是联通块个数。

代码：
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define ll long long
#define hh puts("")
using namespace std;
int n,R,V,E,C,tot,f[105],s[105],vis[105];
double eps=1e-5,r[105];
struct point{
    double x,y;
    int id1,id2;
}a[105],jiao[105];
//R+V-E=C+1
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-ff;ch=getchar();}
    while(isdigit(ch)){ret=(ret<<3)+(ret<<1)+(ch^48);ch=getchar();}
    return ret*ff;
}
point operator + (point A,point B){
    return (point){A.x-B.x,A.y+B.y};
}
point operator - (point A,point B){
    return (point){A.x-B.x,A.y-B.y};
}
inline int dis(point A,point B){
    return (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);
}
inline int find(int p){
    return f[p]==p?p:f[p]=find(f[p]);
}
inline bool cmp(point A,point B){
    return fabs(A.x-B.x)<eps?A.y<B.y:A.x<B.x;
}
signed main(){
	n=read();
    for(int i=1;i<=n;i++){
        a[i].x=read();
        a[i].y=read();
        r[i]=read();
        f[i]=i;
    }
    C=n;
    for(int i=1;i<=n;i++){//这么长全是在求圆的交点
        for(int j=i+1;j<=n;j++){
            int ds=r[i]+r[j];
            if(ds*ds<dis(a[i],a[j])) continue;//两圆相离
            int tx=find(i),ty=find(j);
            if(dis(a[i],a[j])<fabs(r[i]-r[j])*fabs(r[i]-r[j])) continue;
            if(tx!=ty) f[tx]=ty,C--;
            double a1=a[i].x,b1=a[i].y,a2=a[j].x,b2=a[j].y,r1=r[i],r2=r[j];
            double k,b;
            if(fabs(b1-b2)<eps){
                double x=(a2*a2-a1*a1+r1*r1-r2*r2)/(2*a2-2*a1);
                jiao[++tot].x=x;
                jiao[tot].y=b1+sqrt(r1*r1-(x-a1)*(x-a1));
                jiao[tot].id1=i;
                jiao[tot].id2=j;
                jiao[++tot].x=x;
                jiao[tot].y=b1-sqrt(r1*r1-(x-a1)*(x-a1));
                jiao[tot].id1=i;
                jiao[tot].id2=j;
                if(fabs(sqrt(r1*r1-(x-a1)*(x-a1)))<eps) tot--;
                continue;
            }
            else k=(2*a1-2*a2)/(2*b2-2*b1),b=(r1*r1-r2*r2+a2*a2+b2*b2-a1*a1-b1*b1)/(2*b2-2*b1);
            // printf("k=%.2lf\n",k);
            double A=(k*k+1),B=(2*b*k-2*a1-2*k*b1),C=(a1*a1+b*b-2*b*b1+b1*b1-r1*r1);
            double delta=B*B-4*A*C;
            if(fabs(delta)<eps) delta=0;
            jiao[++tot].x=((-B)-sqrt(delta))/(2*A);
            jiao[tot].y=jiao[tot].x*k+b;
            jiao[tot].id1=i;
            jiao[tot].id2=j;
            jiao[++tot].x=((-B)+sqrt(delta))/(2*A);
            jiao[tot].y=jiao[tot].x*k+b;
            jiao[tot].id1=i;
            jiao[tot].id2=j;
            if(fabs(delta)<eps) tot--;
        }
    }
    sort(jiao+1,jiao+tot+1,cmp);
    jiao[tot+1].x=-666,jiao[tot+1].y=-666;
    for(int i=1;i<=tot;i++){
        // printf("%.2lf %.2lf id1=%d id2=%d\n",jiao[i].x,jiao[i].y,jiao[i].id1,jiao[i].id2);
        vis[jiao[i].id1]=vis[jiao[i].id2]=1;
        if(fabs(jiao[i].x-jiao[i+1].x)>eps||fabs(jiao[i].y-jiao[i+1].y)>eps){
            for(int j=1;j<=n;j++) if(vis[j]) s[j]++;
            V++;
            memset(vis,0,sizeof(vis));
            continue;
        }
    }
    for(int i=1;i<=n;i++) E+=s[i];
    // printf("%d\n",E);
    printf("%d",E+C-V+1);
    return 0;
}
```


---

## 作者：Saliеri (赞：2)

精神污染。给一个不需要那么多特判的做法。

首先，求答案显然考虑平面图欧拉定理：$V-E+F=C+1$。

我们求 $F$ 因而需要 $V,E,C$，依次考虑：

$C$：并查集。二圆相交是容易判的。因为需要判相切，所以需要 eps 辅助。

$V$：显然就是圆两两的交点数量。因为可能三圆共点，为了正确去重，我们必须解决圆圆交点问题。

首先明确，我们不采用解几 Tish 考虑，因为那会必然地导出例如 “竖直线” 等 Corner Case。

考虑用计算几何里的正统向量做法。首先判掉内切外切。否则你会爆 `nan`。

考虑到，两个交点必然位于二圆心连线的某一条垂线上。考虑求出该垂线在二圆心连线上的垂足到其中一个圆心的距离 $d$（其可能解出负数，这对应在圆心连线线段的外侧）。

设圆心连线长度为 $D$。注意到对称性，

$\begin{cases}d^2+v^2=r_1^2\\(D-d)^2+v^2=r_2^2\end{cases}\to d = \dfrac{r_1^2-r_2^2+D^2}{2D}$。

$v$ 自然也可以解得。求点坐标的过程采用向量实现。具体看代码。

最后来考虑 $E$。考虑一个圆上的边数就是其上的点数。因而对所有点 $p$ 与圆 $C$ 求和 $[\text{p is on C}]$ 即是。

于是我们做完了。这个题可以加强到 $n\le 2000$。

___

```cpp
//上帝说：“要有月光”。于是便有了 Prean。
#include <cmath>
#include <cstdio>
#include <algorithm>
using std :: swap;
namespace HyjMh{
	typedef double db;
	const db eps = 1e-10;
	db sq(db x){return x*x;}
	bool feq(db x,db y){return fabs(x-y)<eps;}
	struct pt{db x,y;pt(db X=0,db Y=0):x(X),y(Y){};};
	typedef pt vct;struct circ{pt O;db r;}C[10];
	bool operator ==(pt A,pt B){return feq(A.x,B.x)&&feq(A.y,B.y);}
	bool operator <(pt A,pt B){return feq(A.x,B.x)?A.y<B.y:A.x<B.x;}
	pt operator +(pt A,vct B){return pt(A.x+B.x,A.y+B.y);}
	vct operator -(pt A,pt B){return vct(A.x-B.x,A.y-B.y);}
	vct operator *(vct A,db v){return vct(A.x*v,A.y*v);}
	vct Rot(vct A){return vct(-A.y,A.x);}
	db Len(vct A){return sqrt(sq(A.x)+sq(A.y));}
	db Dis(pt A,pt B){return Len(A-B);}
	bool Itsc(circ A,circ B){return Dis(A.O,B.O)<=A.r+B.r+eps&&Dis(A.O,B.O)+eps>=fabs(A.r-B.r);}
	vct setLen(vct A,db L){return A*(L/Len(A));}
	bool onCir(pt A,circ C){return feq(Dis(A,C.O),C.r);}
	int n,eds,blks,cnt;pt its[10];
	void Gits(circ A,circ B){
		db D = Dis(A.O,B.O);
		if(A.r < B.r)std :: swap(A,B);
		if(feq(A.r+B.r,D)||feq(A.r-B.r,D))
			return its[++cnt] = A.O+setLen(B.O-A.O,A.r),void();
		vct M = setLen(B.O-A.O,(sq(A.r)-sq(B.r)+sq(Dis(A.O,B.O)))/2/D); 
		db L = sqrt(sq(A.r)-sq(Len(M)));pt P = A.O+M;
		its[++cnt] = P+setLen(Rot(M),L),its[++cnt] = P-setLen(Rot(M),L);	
	}
	int main(){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%lf %lf %lf",&C[i].O.x,&C[i].O.y,&C[i].r);
		for(int i=1;i<=n;++i)
			for(int j=i+1;j<=n;++j)
				if(Itsc(C[i],C[j]))++eds,Gits(C[i],C[j]);
		std :: sort(its+1,its+cnt+1),cnt = std::unique(its+1,its+cnt+1)-its-1;
		blks = (n<=2?n-eds:(eds==3?1:n-eds));
		int ans = blks+1-cnt;
		for(int i=1;i<=cnt;++i)
			for(int j=1;j<=n;++j)
				ans += onCir(its[i],C[j]);
		return printf("%d\n",ans),0;
	}
}
int main(){return HyjMh::main();}
```



---

## 作者：Mr_罗 (赞：1)

本文提供平面图欧拉公式的证明。

## 公式

摘自本人文章 [平面图欧拉公式](https://www.luogu.com.cn/article/fhv9slkn)。

公式内容：$V-E+F=1+C$ ，其中 $V$ 是点数，$E$ 是边数，$F$ 是面数，$C$ 是连通块数。

**定理** 对于平面图 $G=(V,E)$ ，设其对偶图为 $G^*=(V^*,E^*)$ ，$C$ 表示 $G$ 的连通块数，则 $|V|-|E|+|V^*|=1+C$ 。

*一个简单的证明方法是归纳，每次删掉一个小犄♂角，欧拉公式仍成立，直到只剩若干三角形。本文通过对偶图和生成树证明。*

**证明** 记 $E^*$ 表示 $E$ 中的所有边在对偶图 $G^*$ 中对应的边构成的集合。

> **引理** 取 $G$ 的一棵生成树 $T=(V,E_1)$ ，记 $E_2=E\backslash E_1$ ，那么 $G^*$ 的子图 $T^*=(V^*,E_2^*)$ 也是一棵树。
>
> **证明** 先证明 $T^*$ 连通。由于 $T$ 无环，则每个面都可通过 $e\in E_2$ 走到另一个面（若不行，找一块连通的面，那么环绕着该连通块的 $E_1$ 中的边显然成环了，与 $T$ 是树矛盾），即 $T^*$ 中所有点连通。
>
> 再证明 $T^*$ 无环。和上面类似，有环代表一坨面包围了 $T$ 的子图使其不与外界连通，与 $T$ 是树矛盾。因此 $T^*$ 无环。
>
> 综上，$T^*$ 也是一棵树。
>
> $\square$

先考虑 $G$ 连通的情况，此时 $C=1$ ，就是我们最熟悉的平面图欧拉公式。

取出 $G$ 的生成树 $T=(V,E_1)$ ，记 $E_2=E\backslash E_1,T^*=(V^*,E_2^*)$ 。由引理得 $T^*$ 也是一棵树。

已知 $E_1+E_2=E,|E_2^*|=|E_2|$ ，因此 $|V|-|E|+|V^*|=(|V|-|E_1|)+(|V^*|-|E_2^*|)=2$ 。这样原图连通的情况就证完了。

对于 $G$ 存在若干连通块的情况也类似，只不过需要把 $|V|-|E_1|$ 拆成 $\sum_{G'\ {\sf 是}\ G\ {\sf 的连通子图}}|V(G')|-|E(G')|$ 。每个连通块贡献 $1$（树的点比边多 $1$），因此 $|V|-|E|+|V^*|=1+C$ 。

$\square$

## 求圆交点

设两圆分别为 $\big(O_1=(x_1,y_1),r_1\big),\big(O_2=(x_2,y_2),r_2\big)$ ，要求交点 $X_1,X_2$ 。先判掉分离和包含。

大致思路是求出圆心连线和 $O_1X_1$ 之间的夹角 $\alpha$ ，再设 $\overrightarrow{O_1O_2}$ 的辐角为 $\theta$ ，那么 $\overrightarrow{O_1X_1}$ 的辐角就是 $\theta+\alpha$ ，$\overrightarrow{O_1X_2}$ 的辐角就是 $\theta-\alpha$ ，因此 ${X_1}_x={O_1}_x+r_1\cos(\theta+\alpha),{X_1}_y={O_1}_y+r_1\sin(\theta+\alpha)$ ，$X_2$ 类似。

## 本题

把交点看作顶点，圆弧看作边，本题要求的就是 $1+C-V+E$（对于单独一个圆，可以看作一个点和一个自环，并不影响）。

先求出所有交点再去重，所得到的点的个数就是 $V$ 。

由于一个圆上有几个点就有几段弧，也就有几条边，因此对于每一个圆统计有几个点在它上面，加起来就是 $E$ 。

$C$ 就用并查集简单判一下就好了。

时间复杂度 $\mathcal O(n^2\log n)$ ，排序去重是瓶颈。

[CF 提交记录](https://codeforces.com/contest/933/submission/295962915)。

```cpp
#define N 5
#define mod 998244353
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define eps 1e-10

int n, ans;
int x[N], y[N], r[N];
int fa[N];

struct P { db x, y; };
vector<P> vt;

int sgn(db X) {
    if (X > eps) return 1;
    if (X < -eps) return -1;
    return 0;
}

int operator<=>(P a, P b) {
    return sgn(a.x - b.x) == 0 ? sgn(a.y - b.y) : sgn(a.x - b.x);
}

bool operator==(P a, P b) {
    return (a <=> b) == 0;
}

int fdrt(int i) { return fa[i] == i ? i : fa[i] = fdrt(fa[i]); }

template<typename T> T sq(T X) { return X * X; }

void mslv() {
    scanf("%d", &n);
    rep(i, 1, n) scanf("%d%d%d", x + i, y + i, r + i), fa[i] = i;
    rep(i, 1, n) rep(j, i + 1, n) {
        int dx = x[j] - x[i], dy = y[j] - y[i];
        int d2 = sq(dx) + sq(dy);
        if (d2 > sq(r[i] + r[j]) || d2 < sq(r[i] - r[j])) continue;
        fa[fdrt(i)] = fdrt(j);
        db t = atan2(dy, dx);
        db a = acos((sq(r[i]) - sq(r[j]) + d2) / (2. * r[i] * sqrt(d2)));
        db X = x[i] + r[i] * cos(t + a), Y = y[i] + r[i] * sin(t + a);
        if (vt.eb(X, Y); !sgn(a)) continue;
        X = x[i] + r[i] * cos(t - a), Y = y[i] + r[i] * sin(t - a), vt.eb(X, Y);
    }
    sort(all(vt)), vt.resize(unique(all(vt)) - vt.begin());
    ans = 1 - vt.size();
    rep(i, 1, n) ans += i == fdrt(i);
    for (auto [X, Y] : vt) rep(i, 1, n)
        if (sgn(sq(X - x[i]) + sq(Y - y[i]) - sq(r[i])) == 0) ans++;
    printf("%d\n", ans);
}
```

---

## 作者：Lates (赞：0)

非联通的时候欧拉定理的归纳证明。

显然 $V=1,E=0,C=1$ 时，$V-E+R=2 =C+1$

$C$ 为联通块数量。
$R$ 为区域数量。

设 $V=a,E=b,C=c$ 的时候，命题成立。

- 当新增一个点不与原图连边时，

$V+1,E$ 不变$,C+1,R$ 不变。

$V+1-E+R=C+1+1$ 成立。

- 当新增一个点与原图连边时,

$V+1,E+1,C$ 不变$,R$ 不变

$V+1-(E+1)+R=C+1$ 成立。

- 当新增一条边（连上原图中的两个点）时

$V$ 不变$,E+1,C$ 不变$,R+1$

$V-(E+1)+R+1=C+1$ 成立。

所以命题成立了。

把任意两圆交点当做图上的点，被交点分割的弧当做边。

然后交点要去重。

则区域数量可以由这两个求出来。

而联通块数，我是在当联立完方程组得到一个一元二次方程时 $\Delta >=0$ 时用并查集合并。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
const int MAX=105;
const double eps=1e-4;
int n,fa[MAX];
double x[MAX],y[MAX],r[MAX];
inline double dis(int a,int b){
	return (x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]);
}
inline int sgn(double x){
	return x<-eps?-1:x<eps?0:1;
}
inline int check(int a,int b){
	double p=dis(a,b),q=(r[a]+r[b])*(r[a]+r[b]);
	return -sgn(p-q);
//	printf(" %d %d %lf %lf\n",a,b,p,q); 
}
int link(int x){
	return fa[x]==x?x:fa[x]=link(fa[x]);
}
int CC;
void merge(int x,int y){
	x=link(x);
	y=link(y);
	if(x!=y)fa[y]=x,--CC; 
}

struct node{
	double x,y;
};
	inline bool cmp (node A,node B){
		if(sgn(A.x-B.x)==0)return sgn(A.y-B.y)==-1;
		return sgn(A.x-B.x)==-1;
	}
vector<node>v;
inline void sol(int i,int j){
	double c1=r[i]*r[i]-x[i]*x[i]-y[i]*y[i],
		   c2=r[j]*r[j]-x[j]*x[j]-y[j]*y[j];
		   
	double A=2.0*(x[j]-x[i]),
		   B=2.0*(y[j]-y[i]),
           C=c2-c1;
	double a,b,c;
	if(B==0){
		a=1.0+(B*B)/(A*A),	
		b=2*0*B*C/(A*A)-2.0*y[i]+B*2.0*x[i]/A,
		c=2.0*x[i]*C/A+C*C/(A*A)-c1; 
	} else {
	   	a=1.0+(A*A)/(B*B),
	   	b=2.0*A*C/(B*B)-2.0*x[i]+A*2.0*y[i]/B,
	   	c=2.0*y[i]*C/B+C*C/(B*B)-c1;		
	}
	
	
	double delta=b*b-4.0*a*c;
	if(sgn(delta)==0){
		if(B==0){
			double Y=-b/(2.0*a);
			double X=-B*Y-C;X/=A; 
			v.push_back((node){X,Y});
		}else {
			double X=-b/(2.0*a);
			double Y=-A*X-C;Y/=B; 
			v.push_back((node){X,Y});
		}
			merge(i,j);
	} else if(sgn(delta)>0){
		if(B==0){
			double Ya=-b-sqrt(delta);
					Ya/=2.0*a;
			double Yb=-b+sqrt(delta);
			       	Yb/=2.0*a;
			double Xa=(-C-B*Ya)/A,
				   Xb=(-C-B*Yb)/A;
			v.push_back((node){Xa,Ya});
			v.push_back((node){Xb,Yb});
			
		}else {
			double Xa=-b-sqrt(delta);
					Xa/=2.0*a;
			double Xb=-b+sqrt(delta);
					Xb/=2.0*a;
			double Ya=(-C-A*Xa)/B,
				   Yb=(-C-A*Xb)/B;		
			v.push_back((node){Xa,Ya});
			v.push_back((node){Xb,Yb});
		}		
			merge(i,j);
	}
	
}
int V,E; 
inline void addE(int p){
	double xx=v[p].x,yy=v[p].y;
	for(register int i=1;i<=n;++i){
		if(sgn((xx-x[i])*(xx-x[i])+(yy-y[i])*(yy-y[i])-r[i]*r[i])==0)++E;
	}
}
signed main(){
			
//	freopen("firework.in","r",stdin);
//	freopen("firework.out","w",stdout);
	n=CC=read();
	for(register int i=1;i<=n;++i){
		scanf("%lf %lf %lf",&x[i],&y[i],&r[i]);
		fa[i]=i;
	}
	if(n==1){
		puts("2");
		return 0;
	}
	if(n==2){
//		puts("QAQ");
		if(check(1,2)==1)puts("4");
		else puts("3");
		return 0;
	}
	
	for(register int i=1;i<=n;++i){
		for(register int j=i+1;j<=n;++j){
			if(sgn(x[i]-x[j])==0&&sgn(y[i]-y[j])==0)continue;
			sol(i,j);
		}
	}
	sort(v.begin(),v.end(),cmp);
	V=v.size();
	if(v.size())addE(0);
	for(register int i=1;i<v.size();++i){
		node A=v[i],B=v[i-1];
		if(sgn(A.x-B.x)==0&&sgn(A.y-B.y)==0)--V;
		else {
			addE(i);
		}
	}
	printf("%d\n",CC-V+E+1);
	return 0;
}


```


---

