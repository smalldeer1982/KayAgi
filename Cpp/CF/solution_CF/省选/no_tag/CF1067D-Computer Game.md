# Computer Game

## 题目描述

Ivan 玩一个电脑游戏。游戏中有 $n$ 个任务。每个任务都可以升级一次，升级后完成该任务的奖励会增加。每个任务有 $3$ 个参数 $a_{i}$、$b_{i}$、$p_{i}$：升级前完成任务的奖励、升级后完成任务的奖励（$a_{i} < b_{i}$），以及成功完成该任务的概率。

每秒 Ivan 可以尝试完成一个任务，他成功的概率为 $p_{i}$。若成功，他将获得奖励，并可以选择升级任意一个任务（不一定是刚刚完成的那个）。若失败，则什么也得不到。任务在完成后不会消失。

Ivan 有 $t$ 秒时间。他希望在 $t$ 秒后获得的总期望收益最大。请帮助他计算这个期望值。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2
3 1000 0.5
1 2 0.48
3 20 0.3
```

### 输出

```
252.2500000000000
```

## 样例 #2

### 输入

```
2 2
1 1000 0.1
2 3 0.2
```

### 输出

```
20.7200000000000
```

# 题解

## 作者：lhm_ (赞：14)

先考虑贪心，发现当升级后一定是一直选取 $bp$ 最大，即期望收益最大的游戏，而升级前的选取要考虑升级的概率和当前选取的收益，所以考虑 $DP$ 来解决升级前的选取。

设 $f_t$ 为还剩 $t$ 秒且当前未成功升级的最大期望收益，$v$ 为 $bp$ 最大值，得：
$$
\large f_t=\max_{i=1}^n\{ p_i((t-1)v+a_i)+(1-p_i)f_{t-1} \}
$$
即为成功后就一直选取最优的选择，未成功就继续 $DP$。将方程转化为另一种形式，得：
$$
\large f_t=\max_{i=1}^n\{ p_i((t-1)v-f_{t-1})+p_ia_i \}+f_{t-1}
$$
发现转移可以表示为 $kx+b$ 的形式，$p_i$ 看作为 $k$，$p_ia_i$ 看作为 $b$。也就是每个转移都可以用一条直线来表示，考虑斜率优化，维护出下凸壳后二分出 $x=(t-1)v-f_{t-1}$ 在下凸壳的哪一条直线上即可。但是发现秒数 $t$ 很大，不能直接做。

发现 $tv-f_t$ 是单调不降的，假设有 $tv-f_t \geqslant (t-1)v-f_{t-1}$，得 $f_t-f_{t-1} \leqslant v$，根据 $v$ 的定义，每一次的最优决策所带来的收益不可能超过 $v$，因此得证 $tv-f_t$ 是单调不降的。

那么就可以直接扫一遍直线，二分每次连续可行转移的 $t$ 的区间，通过矩阵快速幂来优化转移：
$$
\large\begin{bmatrix}
  f_t &  t & 1
\end{bmatrix}

\times

\begin{bmatrix}
  1-p_i & 0 & 0 \\
  p_iv & 1 & 0 \\
  p_ia_i &  1 & 1
\end{bmatrix}

=

\begin{bmatrix}
  f_{t+1} &  t+1 & 1
\end{bmatrix}
$$
二分是两个 $\log$ 的，通过矩阵倍增来代替二分转移就可以做到一个 $\log$。

```cpp
#include<bits/stdc++.h>
#define maxn 100010
#define eps 1e-12
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,tot,top;
ll t,now;
double v;
struct matrix
{
    double a[5][5];
}f,g[36];
matrix operator *(const matrix &x,const matrix &y)
{
    matrix z;
    memset(z.a,0,sizeof(z.a));
    for(int k=1;k<=3;++k)
        for(int i=1;i<=3;++i)
            for(int j=1;j<=3;++j)
                z.a[i][j]+=x.a[i][k]*y.a[k][j];
    return z;
}
int sgn(double x)
{
    if(fabs(x)<eps) return 0;
    return x>0?1:-1;
}
struct line
{
    double k,b;
}l[maxn],st[maxn];
bool cmp(const line &x,const line &y)
{
    if(!sgn(x.k-y.k)) return x.b<y.b;
    return x.k<y.k;
}
double get(line x,line y)
{
    return (x.b-y.b)/(y.k-x.k);
}
int main()
{
    read(n),read(t);
    for(int i=1;i<=n;++i)
    {
        double a,b,p;
        scanf("%lf%lf%lf",&a,&b,&p);
        l[i]={p,p*a},v=max(v,b*p);
    }
    sort(l+1,l+n+1,cmp);
    for(int i=1;i<=n;++i)
        if(sgn(l[i].k-l[i+1].k))
            l[++tot]=l[i];
    for(int i=1;i<=tot;++i)
    {
        while(top>1&&sgn(get(st[top],st[top-1])-get(l[i],st[top-1]))>=0) top--;
        st[++top]=l[i];
    }
    f.a[1][3]=1;
    for(int i=1;i<=top;++i)
    {
        double pos=now*v-f.a[1][1];
        while(i<top&&sgn(pos-get(st[i],st[i+1]))>=0) i++;
        if(i<top) pos=get(st[i],st[i+1]);
        g[0].a[1][2]=g[0].a[1][3]=g[0].a[2][3]=0;
        g[0].a[2][2]=g[0].a[3][2]=g[0].a[3][3]=1;
        g[0].a[1][1]=1-st[i].k,g[0].a[2][1]=st[i].k*v,g[0].a[3][1]=st[i].b;
        for(int j=1;j<=34;++j) g[j]=g[j-1]*g[j-1];
        for(int j=34;j>=0;--j)
            if(now+(1ll<<j)<t)
                if(i==top||sgn(pos-(now+(1ll<<j))*v+(f*g[j]).a[1][1])>=0)
                    f=f*g[j],now+=1ll<<j;
        f=f*g[0],now++;
        if(now==t) break;
    }
    printf("%.10lf",f.a[1][1]);
    return 0;
}
```

---

## 作者：_Diu_ (赞：9)

一道有趣的，比较综合的动态规划。

首先有一个很显然的结论，第一次升级之后，我们会选择 $b_ip_i$ 最大的游戏升级，并且以后会狂刷这个游戏，这样子期望收益最高。

## 朴素 dp

我们考虑运气没那么好的情况：设 $f_i$ 表示剩下 $i$ 次机会尝试，到目前都还没有升级过，那么答案就是 $f_t$。

设 $M=\max(b_ip_i)$，那么容易想到转移：

$$
f_i=\max(p_j\times (a_j+(i-1)M)+(1-p_j)f_{i-1})
$$

也就是讨论这句胜利和失败的情况。

至此，我们活得了一个 $O(nt)$ 的做法。

## 斜率优化

我们考虑优化 dp 的转移过程

$$
f_i=\max(p_j((i-1)M-f_{i-1})+p_ja_j)+f_{i-1}
$$

我们发现，如果对于一个确定的 $i$，$((i-1)M-f_{i-1})$ 可以被当成一个已知的量，符合斜率优化的形式。

设 $s_i=(iM-f_i)$，则 $f_i=\max(s_{i-1}p_j+p_ja_j)+f_{i-1}$。

我们发现 $s_i$ 是单调不降的。

证明：

考虑作差法，
$$
s_i-s_{i-1}=iM+f_i-(i-1)M-f_{i-1}
$$
$$
=M+(f_i-f_{i-1})
$$
因为 $M$ 是一局游戏所能赚的最大收益，$f_i$ 和 $f_{i-1}$ 之间只有一局游戏，收益显然不可能超过 $M$。

所以 $s_i$ 单调不降。

我们考虑将游戏项目按照 $p_i$ 为第一关键字， $a_ip_i$ 为第二关键字排序，那么最后的决策肯定是连续玩若干次某个游戏之后，跳到下一个。

直接用单调队列维护凸包的话，时间复杂度 $O(n+t)$，显然还是过不了。

## 矩阵优化

看到 $t$ 是 $1e10$ 级别的，我们考虑矩阵优化。

对于一个游戏，它的转移矩阵是不会改变的。

我们考虑一次转移完一个游戏。

这样我们需要找到一个游戏的边界。

如果直接二分，每次暴力转移矩阵，时间复杂度 $O(n\log^2 t)$，可能会炸。

考虑先把每个可能转移的游戏的转移矩阵的 $2$ 的幂次的矩阵预处理出来，

然后倍增查询，时间复杂度就能压掉一个 $\log$ 了。

## code

注意精度问题，代码常数略大。

为了防止精度丢失，斜率优化部分用了乘法的形式

```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
using namespace std;
const int N=1e5+10;
const db eps=1e-14;
int n,t,id[N],pr,q[N];
db a[N],b[N],p[N],g[N],M;
struct Mat{
	int r,c;
	db a[4][4];
	Mat(int n=0,int m=0){for(int i=0;i<3;i++)for(int j=0;j<3;j++)a[i][j]=0;r=n,c=m;}
}pw[50];
Mat operator*(Mat a,Mat b){
	Mat c(a.r,b.c);
	for(int i=0;i<a.r;i++)
		for(int j=0;j<b.c;j++)
			for(int k=0;k<a.c;k++)c.a[i][j]+=a.a[i][k]*b.a[k][j];
	return c;
}
Mat maker(int x){//构造该游戏的转移矩阵
	Mat a(3,3);
	a.a[0][0]=1-p[x];a.a[1][0]=p[x]*M;
	a.a[1][1]=a.a[2][2]=a.a[2][1]=1;
	a.a[2][0]=g[x];
	return a;
}
bool cmp(int a,int b){
	if(fabs(p[a]-p[b])<eps)return g[a]>g[b];
	return p[a]<p[b];
}
db X(int i){return p[i];}
db Y(int i){return g[i];}
signed main(){
	scanf("%lld%lld",&n,&t);
	for(int i=1;i<=n;i++){
		scanf("%lf%lf%lf",&a[i],&b[i],&p[i]);
		g[i]=a[i]*p[i],id[i]=i;
		M=max(M,b[i]*p[i]);
	}
	sort(id+1,id+n+1,cmp);
	for(int I=1;I<=n;I++){
		int i=id[I];
		if(fabs(p[i]-p[id[I-1]])<eps)continue;
		while(pr>1&&(Y(i)-Y(q[pr]))*(X(q[pr])-X(q[pr-1]))>(Y(q[pr])-Y(q[pr-1]))*(X(i)-X(q[pr])))--pr;
        //先把一些不在凸壳上的点去掉
		q[++pr]=i;
	}
	int now=0,pl=1;
	db f=0;
	Mat F(1,3);F.a[0][2]=1;
	while(now<t){
		while(pl<pr&&(Y(q[pl+1])-Y(q[pl]))>-f*(X(q[pl+1])-X(q[pl])))++pl;
		pw[0]=maker(q[pl]);
		for(int i=1;i<40;i++)pw[i]=pw[i-1]*pw[i-1];//倍增
		for(int i=39;i>=0;i--){
			if(now+(1ll<<i)>=t)continue;
			Mat G=F*pw[i];
			db S=G.a[0][1]*M-G.a[0][0];
			if(pl==pr||Y(q[pl])-Y(q[pl+1])>S*(X(q[pl+1])-X(q[pl])))F=G,now+=(1ll<<i);
			//没得选或着优于就可以更新 
		}
		F=F*pw[0],++now;//跳到下一种
		f=F.a[0][1]*M-F.a[0][0];
	}
//	printf("%.10lf\n",F.a[0][0]); No Copy!!!
}
```

#### 完结撒花

---

## 作者：EternalAlexander (赞：6)

首先需要第一步观察：第一次升级之后，一定是一直打升级之后那个游戏，且这个一定是 $b_i \times p_i$ 最大的那个。

因为，在升级一次之后，打这个得到的期望收益一定是最大的。我们设这个最大的 $b_i \times p_i$ 为 $M$。

那么我们首先写出一个平凡的 dp ： $f_i$ 表示剩下 $i$ 时刻，且没有升级过的期望收益。有 $f_i = \max \{(1-p_j) f_{i-1} + p_jM(i-1) + p_j a_j \}$。 意义就是，枚举打哪个游戏，有 $(1-p_j)$ 的概率失败，变为 $i-1$ 时刻。有 $p_j$ 的概率成功，成功之后剩下 $i-1$ 时刻将会一直打最大的那个，同时这一时刻可以直接得到 $a_j$ 的收益。

记 $S_i = M \cdot i - f_i$，将转移式变形，得到 $\max \{f_{i-1} + p_j  S_{i-1}+p_j a_j \}$，$f_{i-1}$ 是一个常数，我们只需要最大化 $p_jS_{i-1}+p_ja_j$ 。这是一个斜率优化式，把每个 $j$ 当成二维平面上的一个点 $(p_j,p_ja_j)$，则相当于用一个斜率为 $-S_{i-1}$ 的直线切这些点，最大化截距。我们可以维护一个上凸壳进行转移。

然后注意到，$S_i$ 是单调不降的。

理性证明：

**upd: 这个证明好像有点问题，直接看下面那个吧**

假设对于所有 $i<n$，$S_i\geq S_{i-1}$，我们证明 $S_{i+1} \geq S_i$。

$S_{i+1} - S_i = M + f_i - f_{i+1} = M + (1-p_j) f_{i-1} + p_jM(i-1) + p_j a_j  - (1-p_j) f_{i}-p_jMi - p_j a_j = M-p_jM + (1-p_j) (f_{i-1} - f_i) = (1-p_j) (M+f_{i-1}-f_i)$。

由于对于所有 $i<n$，$S_i\geq S_{i-1}$，故 $M+f_{i-1}-f_i\geq 0$，得证 $S_{i+1}-S_i\geq 0$。

感性证明：

$S_{i+1} - S_i \geq 0 \leftrightarrow M \geq f_{i+1} - f_i$，后式的实际意义是两个时刻间期望收益的差，显然无论如何不可能大于 $M$。

接下来的问题就是如何处理 $t = 10^{10}$。考虑一次将切点为 $j$ 的所有转移处理完，注意到转移可以写成如下矩阵形式：

$
\quad
\begin{bmatrix} f_i & i & 1 \end{bmatrix}
\quad \times 
\quad
\begin{bmatrix} 1-p_j & 0 & 0 \\ p_jM &1 &0 \\ p_ja_j & 1& 1 \end{bmatrix}
\quad =
\quad
\begin{bmatrix} f_{i+1} & i+1 & 1 \end{bmatrix}
\quad $

那么我们只需要高速找出所得切点第一次变化的位置即可。有一个显然的做法是矩阵快速幂+二分答案，复杂度是 $O(n \log^2 t)$，不知道能不能通过。我们可以预处理出这个矩阵的所有 $2^k$ 次幂，然后倍增出这个位置，就可以做到 $O(n \log t)$。

注意精度，注意斜率优化细节，注意不要把凸壳维护反了。

```cpp
#include <bits/stdc++.h>
#define maxn 100005
#define ll long long

const double eps = 1e-14;

int n,rk[maxn],hull[maxn],tl;
ll t;
double p[maxn],g[maxn],a[maxn],b[maxn],M;

struct Matrix {
	double A[4][4];
	int r,c;
	Matrix (int r1=0,int c1=0){
		std::memset(A,0,sizeof(A));
		r=r1;c=c1;
	}
};

Matrix B[40];

Matrix mul(Matrix A,Matrix B){
	Matrix C = Matrix(A.r,B.c);
	for(int i=1;i<=A.r;++i)
	for(int j=1;j<=A.c;++j)
	for(int k=1;k<=B.c;++k)
		C.A[i][k]+=A.A[i][j]*B.A[j][k];
	return C;
}

Matrix build(int x){
	Matrix A = Matrix(3,3);
	A.A[1][1]=1-p[x];A.A[2][1]=p[x]*M;A.A[2][2]=A.A[3][3]=A.A[3][2]=1;
	A.A[3][1]=g[x];
	return A;
}

double get(double s,int x){
	return p[x]*s+g[x];
}

int cmp(int a,int b){
	if(fabs(p[a]-p[b])<eps) return g[a]>g[b];
	return p[a]<p[b];
}

int main(){
	scanf("%d%lld",&n,&t);
	for(int i=1;i<=n;++i){
		scanf("%lf%lf%lf",&a[i],&b[i],&p[i]);
		g[i] = a[i] * p[i];
		rk[i]=i;
		M=std::max(M,p[i]*b[i]);
	}std::sort(rk+1,rk+n+1,cmp);
	
	for(int j=1;j<=n;++j){
		int i=rk[j];
		if(fabs(p[rk[j]]-p[rk[j-1]])<eps)continue;
		if(tl<2)hull[++tl]=i;
		else {
			while ( (g[i]-g[hull[tl]]) * (p[hull[tl]]-p[hull[tl-1]]) > 
			(g[hull[tl]]-g[hull[tl-1]]) * (p[i]-p[hull[tl]]) ) tl--;
			hull[++tl]=i;
		}
		
	}

	ll cur = 0;
	int p1 = 1;
	double cur_pt = 0;
	
	Matrix F = Matrix(1,3);
	F.A[1][2]=0;F.A[1][3]=1;
	
	while (1) {
		while(p1<tl && g[hull[p1+1]]-g[hull[p1]] > -cur_pt * (p[hull[p1+1]] - p[hull[p1]]))
			 p1++;

		Matrix G = build(hull[p1]);
		B[0]=G;
		
		for(int i=1;i<=34;++i)B[i]=mul(B[i-1],B[i-1]);
		
		for(int i=34;i>=0;i--){
			if (cur + (1ll<<i) >= t) continue;
			Matrix N = mul(F,B[i]);
			double new_pt = -N.A[1][1]+N.A[1][2]*M ;
			
			if (p1 == tl || get(new_pt, hull[p1]) > get(new_pt, hull[p1+1])) {
				F = N;
				cur += (1ll<<i);
				
			}
		} 
		
		F = mul(F,B[0]); 
		
		cur ++;
		
		cur_pt = -F.A[1][1] + F.A[1][2]*M;
		
		if (cur == t) break;
	}
	printf("%.8f", F.A[1][1]);
	return 0;
}



```


---

## 作者：Kubic (赞：5)

这是一个不用矩阵快速幂的 $O(n\log t)$ 做法。

凸包精度被卡爆了。。。调试一年才过。。。

首先可以发现当我们赢了一局之后，剩下的时间我们肯定对着那个 $b_ip_i$ 最大的关卡刷。于是我们可以设 $w=\max\limits_i b_ip_i$。

再设 $f_t$ 表示 $t$ 秒时间内最优策略下的期望分数，可得递推式：

$$f_t=\max\limits_i\{f_{t-1}(1-p_i)+(w(t-1)+a_i)p_i\}$$

即

$$f_t=f_{t-1}+\max\limits_i\{(w(t-1)-f_{t-1})p_i+a_ip_i)\}$$

我们考虑 $f_t$ 的最优决策点 $i$。这显然是一个可以斜率优化的形式，其中第 $i$ 个点是 $(p_i,a_ip_i)$，我们要用一条斜率为 $f_{t-1}-w(t-1)$ 的直线来切这些点使得在 $y$ 轴上的截距最大，那么求出上凸壳之后就可以在凸壳上二分查找切点。

此时我们就可以得到一个 $O(t\log n)$ 的做法，但 $t$ 太大了，我们需要更多性质。

设 $g_t=wt-f_t$。可得递推式：

$$g_t=g_{t-1}+w-\max\limits_i\{g_{t-1}p_i+a_ip_i\}$$

由于 $g_0=0$，所以我们可以归纳证明 $g$ 是单调不减的，证明比较简单，此处不再赘述。

所以我们可以得出每次切在凸壳上的直线的斜率单调不增，那么凸壳上的每一个点作为决策点的时间一定是一段区间。

观察发现 $g$ 的递推式是一次函数的形式，即 $g_t=k_1g_{t-1}+k_2$ 且 $k_1,k_2$ 都是常数。所以只要确定了决策点就可以快速计算出中任何一项 $g_t$。

所以我们可以对于凸壳上的每一个点依次计算出它作为决策点的时间区间，并计算贡献。

二分+快速幂可以做到 $O(n\log^2t)$，倍增预处理幂次可以做到 $O(n\log t)$。

实现时候需要注意一下精度，尽量避免除法（我被精度卡了很久）。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100005
#define ll long long
#define db long double
const db EPS=1e-15;
int n,a[N],b[N],h[N];ll t,m;db w,nw,tmp,p[N],pw[N],s[N];
struct Point
{
	int id;db x,y;Point(db _x=0,db _y=0) {id=0;x=_x;y=_y;}
	Point operator - (Point t) {return Point(x-t.x,y-t.y);}
}z[N];
bool cmp(Point x,Point y) {return fabs(x.x-y.x)<EPS?x.y>y.y:x.x<y.x;}
db crsMul(Point x,Point y) {return x.x*y.y-x.y*y.x;}
bool chk(int x,db w)
{
	w=-w;if(x>1 && crsMul(z[h[x]]-z[h[x-1]],Point(1,w))>0) return 0;
	if(x<h[0] && crsMul(z[h[x+1]]-z[h[x]],Point(1,w))<0) return 0;return 1;
}
int main()
{
	scanf("%d %lld",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%d %d %Lf",&a[i],&b[i],&p[i]);
		w=max(w,p[i]*b[i]);z[i]=Point(p[i],p[i]*a[i]);z[i].id=i;
	}sort(z+1,z+n+1,cmp);
	for(int i=1;i<=n;++i)
	{
		if(fabs(z[i].x-z[i-1].x)<EPS) continue;
		while(h[0]>1 && crsMul(z[i]-z[h[h[0]-1]],z[h[h[0]]]-z[h[h[0]-1]])<0)
			--h[0];h[++h[0]]=i;
	}
	for(int i=1,id;i<=h[0];++i) if(t<m && chk(i,nw))
	{
		id=z[h[i]].id;pw[0]=1-p[id];s[0]=1;
		for(int j=1;j<=40;++j) pw[j]=pw[j-1]*pw[j-1],s[j]=s[j-1]*(pw[j-1]+1);
		for(int j=40;j>=0;--j) if(t+(1ll<<j)<=m)
		{tmp=nw*pw[j]+s[j]*(w-p[id]*a[id]);if(chk(i,tmp)) t+=1ll<<j,nw=tmp;}
		if(t<m) ++t,nw=nw*pw[0]+s[0]*(w-p[id]*a[id]);
	}printf("%.10Lf\n",w*m-nw);return 0;
}
```

---

## 作者：lottle1212__ (赞：3)

# [Computer Game](https://www.luogu.com.cn/problem/CF1067D)

可以发现赢下一局后，会选择升级后期望收益 $p\times b$ 最高的一种游戏玩到结束位置，记 $(p\times b)_{\operatorname{max}}$ 为 $V$ 。接下来考虑升级前的策略，由于不能找出直观的贪心策略，那就使用动态规划。设 $f_t$ 表示游戏还剩 $t$ 秒且在此之前没有赢过的期望收益最大值。可以列出转移方程：

$$f_t=\max_{i=1}^n\{p_i(a_i+(t-1)V)+f_{t-1}(1-p_i)\}$$

这样直接转移是 $O(nt)$ 的，因此要优化转移。

首先把常量扔外面，再按照 $i, t$ 整理式子：

$$f_t=\max_{i=1}^n\{p_i((t-1)V-f_{t-1})+p_ia_i)\}+f_{t-1}$$

由于转移的时候 $t-1, f_{t-1}$ 是已知的，在一步转移中可以视为常量。而 $V$ 也是已知常量，所以 $(t-1)V-f_{t-1}$ 在一步转移中也可以视为常量。关于 $i$ 的变量 $p_i, p_ia_i$，与转移的量相乘与相加，这种形式可以用使用斜率优化。还有不懂斜率优化的同学可以看[这里](https://www.luogu.com.cn/article/ta88qdqn)。

然后显然有 $f_t-f_{t-1}\leq V$，所以 $(t-1)V-f_{t-1}\leq tV-f_t$，即式子中的 $(t-1)V-f_{t-1}$ 是递增的，因此可以用单指针来维护最优解在凸包上的位置，即转移是 $O(1)$ 的。

此时的复杂度就变成了 $O(n+t)$。

然后由于 $(t-1)V-f_{t-1}$ 递增，所以游戏 $i$ 作为最优解的时刻一定是一个区间，则对于每一段连续的区间，可以使用矩阵加速转移。即：

$$\begin{bmatrix}f_t&t&1\end{bmatrix}\times\begin{bmatrix}1-p_i&0&0\\p_iv&1&0\\p_ia_i&1&1\end{bmatrix}=\begin{bmatrix}f_{t+1}&t+1&1\end{bmatrix}$$

然后使用矩阵倍增，就可以在 $O(\log t)$ 的时间内转移一段连续的区间了。总时间复杂度 $O(n\log t)$。

Code

```cpp
#include <iostream>
#include <algorithm>
#include <string.h>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define fst first
#define scd second
#define db double
#define ll long long
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector <int>
#define pii pair <int, int>
#define sz(x) ((int)x.size())
#define ms(f, x) memset(f, x, sizeof(f))
#define L(i, j, k) for (int i=(j); i<=(k); ++i)
#define R(i, j, k) for (int i=(j); i>=(k); --i)
#define ACN(i, H_u) for (int i=H_u; i; i=E[i].nxt)
using namespace std;
template <typename INT> void rd(INT &res) {
	res=0; bool f=false; char ch=getchar();
	while (ch<'0'||ch>'9') f|=ch=='-', ch=getchar();
	while (ch>='0'&&ch<='9') res=(res<<1)+(res<<3)+(ch^48), ch=getchar();
	res=(f?-res:res);
}
template <typename INT, typename...Args>
void rd(INT &x, Args &...y) { rd(x), rd(y...); }
//dfs
const int maxn=1e5;
const int N=maxn+10;
int n, stk[N], top; ll tv; db V;
//wmr
struct node {
	db x, y;
	bool operator < (const node &k) const { return x<k.x; }
} g[N];
struct matrix {
	db f[3][3];
	matrix() { L(i, 0, 2) L(j, 0, 2) f[i][j]=0; }
	void unit() { f[0][0]=f[1][1]=f[2][2]=1; }
} bin[40];
matrix operator * (const matrix &x, const matrix &y) {
	matrix z;
	L(k, 0, 2) L(i, 0, 2) L(j, 0, 2) z.f[i][j]+=x.f[i][k]*y.f[k][j];
	return z;
}
// db slope(int i, int j) { return (g[j].y-g[i].y)/(g[j].x-g[i].x); }
//incra

//lottle
signed main() {
//	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	freopen("CF1067D.in", "r", stdin);
	freopen("CF1067D.out", "w", stdout);
	rd(n, tv);
	L(i, 1, n) {
		int a, b; db p;
		rd(a, b); scanf("%lf", &p);
		V=max(V, p*b); g[i].x=p, g[i].y=p*a;
	}
	sort(g+1, g+n+1);
	L(i, 1, n) {
		// while (top>1&&slope(i, stk[top])>=slope(stk[top], stk[top-1])) --top;
		while (top>1&&(g[i].y-g[stk[top]].y)*(g[stk[top]].x-g[stk[top-1]].x)>=(g[stk[top]].y-g[stk[top-1]].y)*(g[i].x-g[stk[top]].x)) --top;
		stk[++top]=i;
	}
	matrix res; res.f[0][2]=1; ll t=0;
	L(i, 1, top) {
		db val=t*V-res.f[0][0];
		// while (i<top&&-val<=slope(stk[i], stk[i+1])) ++i;
		while (i<top&&g[stk[i+1]].y-g[stk[i]].y+val*(g[stk[i+1]].x-g[stk[i]].x)>=0) ++i;
		bin[0].f[0][0]=1-g[stk[i]].x, bin[0].f[1][0]=g[stk[i]].x*V, bin[0].f[2][0]=g[stk[i]].y, bin[0].f[1][1]=bin[0].f[2][1]=bin[0].f[2][2]=1;
		int uj=__lg(tv-t);
		L(j, 1, uj) bin[j]=bin[j-1]*bin[j-1];
		R(j, uj, 0) if (t+(1ll<<j)<tv) {
			matrix tmp=res*bin[j]; val=(t+(1ll<<j))*V-tmp.f[0][0];
			// if (i==top||-val>=slope(stk[i], stk[i+1])) res=tmp, t+=(1ll<<j);
			if (i==top||g[stk[i+1]].y-g[stk[i]].y+val*(g[stk[i+1]].x-g[stk[i]].x)<=0) res=tmp, t+=(1ll<<j);
		}
		res=res*bin[0], ++t;
		if (t==tv) break;
	}
	printf("%.12lf\n", res.f[0][0]);
	return 0;
}
/*
input
4 1000000
2 3 0.00001
3 100 0.000004
5 1000 0.000001
8 3000 0.0000004
output
1082.0053569238542
*/
```

---

## 作者：Phartial (赞：1)

由于一个游戏可以打多次，我们的最优策略必然形如：在开始尝试得到一次升级机会，然后选择升级后期望收益最大的游戏升级并一直打它。

设 $v=\max_i p_i b_i$，我们只需要决策一开始选择哪些游戏。直觉上 $p_i$ 越大越好，但是当时间很短时 $a_i$ 也需要纳入考虑，于是考虑 dp。设 $f_i$ 表示 $i$ 秒能得到的最大收益，枚举这一秒玩哪个游戏，有转移：

$$
f_i=\max_j \{p_j(a_j+(i-1)v)+(1-p_j)f_{i-1}\}
$$

整理后可以发现这是一个类似斜率优化的形式，我们预处理出 $(p_j,p_ja_j)$ 组成的上凸壳，那么 $f_i$ 的转移点就是用斜率为 $f_{i-1}-(i-1)v$ 的直线切这个上凸壳得到的。但是 $t$ 过大，考虑找一些性质。

回顾一下我们的直觉：为了触发激活事件，我们希望每次用的 $p_i$ 尽量大，而显然随着剩余时间变长，第一步用的 $p_i$ 会越来越大，于是 $f_i$ 实际上关于 $p_j$ 有决策单调性！严谨地说明这件事，发现 $(f_i-iv)-(f_{i-1}-(i-1)v)=f_i-f_{i-1}-v\le 0$（因为一秒内的收益不可能大于 $v$），于是每次切上凸壳的直线斜率是单调不增的，决策点的 $x$ 一维自然单调不减。

那么枚举每个转移点，倍增地转移 $f_i$，并随时查看什么时候下一个转移点更优即可。转移不难写成矩阵乘法的形式，时间复杂度 $\Theta(n \log t)$。

[code](https://codeforces.com/contest/1067/submission/293517405)。

---

## 作者：不知名用户 (赞：1)

题意：有 $n$ 种游戏，第 $i$ 种游戏的成功概率是 $p_i$，升级前的收益是 $a_i$，升级后的收益是 $b_i$，成功后可以选择一个游戏升级。求玩 $t$ 次（每次可以任选一个游戏玩）的最大期望收益。$n\le10^5,t\le10^{10}$。

观察到升级之后就玩收益期望最大的游戏，即收益是 $\max\limits_{i=1}^n\{b_ip_i\}$，记为 $B$。考虑 DP，记 $f_i$ 表示还未升级且剩下 $i$ 次机会的最大期望收益。列出转移方程：

$$f_i=\max\limits_{j=1}^n(p_j(b_j+(i-1)B)+(1-p_j)f_{i-1})$$

加号前面表示升级成功，加号后面表示升级失败。直接寻找决策点不行，需要用斜率优化等方法。

先扯开怎么寻找决策点，还有个很重要的事情：$t\le10^{10}$。一看就要矩阵快速幂优化递推。如果选择一次 $j$，$f_i$ 会变成什么样？先把式子整理成几个定值（只和 $j$ 有关也算）乘上 $f_{i-1},i-1,1$：$(1-p_j)f_{i-1}+p_jB(i-1)+p_jb_j$。列出矩乘：

$$
\begin{bmatrix}
f_{i-1}&i-1&1
\end{bmatrix}
\times
\begin{bmatrix}
1-p_j&0&0\\
p_jB&1&0\\
p_jb_j&1&1
\end{bmatrix}
=
\begin{bmatrix}
f_i&i&1
\end{bmatrix}
$$

然后对于一段连续的决策 $j$ 矩阵快速幂即可。

这个式子看起来非常能斜率优化。整理：$\max(p_jb_j+p_j((i-1)B-f_{i-1})+f_{i-1}$。

众所周知，斜率优化的式子可以考虑斜线切点和竖线交斜线（李超树）两种方法。

口胡一下前者（本人没写过）：插入一些 $k=(i-1)B-f_{i-1},b=p_jb_j,y=kx+b$ 的直线求下凸包（U 型），决策点就是 $x=f_i$ 交的直线。发现 $f$ 递增（显然玩游戏不会掉收益），所以对于凸包的每一段直线对应的转移点的下标是连续的。

从左到右枚举凸包的每条直线，考虑从大到小确定二进制位来得到能转移的连续下标的右端点，处理出来上面那个 $3\times3$ 矩阵的 $2^i$ 次方。用矩乘判断转移到的 $f_{i}$ 是否还在这段直线对应的 $x$ 坐标内。注意如果最后还在对应 $x$ 坐标内且未用完 $t$ 次，还要再转移一次。

后者就相当于一些点 $(p_j,p_jb_j)$ 用斜率为 $f_{i-1}-(i-1)B$ 的直线切到的最高点，这条直线与 $y$ 轴的交点就是转移到的 $f$。其实和上面的做法差不多。几点变化：

求斜线下凸包变成点的上凸包；枚举边变成枚举点；还是最有决策的条件从 $f_i$ 对应直线的 $x$ 坐标内变成 $f_{i-1}-(i-1)B$ 大于这个点和凸包下一个连线的斜率。

被精度整了好久。代码不到 2k。

```cpp
#include<bits/stdc++.h>
using namespace std;
using lf = long double;
const int N = 1e5 + 10;
const lf eps = 1e-12;
lf a[N], b[N], p[N], B;
struct dot{lf x,y;}d[N];int top;
lf slope(int a, int b){if(d[a].x-d[b].x<=eps&&d[a].x-d[b].x>=-eps)return 1e18;return(d[a].y-d[b].y)/(d[a].x-d[b].x);}
struct mat
{
	lf a[3][3], r, c;
	void cl(){for(int i=0;i<3;i++)for(int j=0;j<3;j++)a[i][j]=0;}
	friend mat operator * (const mat &a, const mat &b)
	{
		mat c;c.cl();
		c.r = a.r, c.c = b.c;
		for(int i=0;i<c.r;i++) for(int j=0;j<c.c;j++) for(int k=0;k<a.c;k++) c.a[i][j] += a.a[i][k] * b.a[k][j];
		return c;
	}
}now,nn,pw[40];

int main()
{
	int n, i, j;
	long long t;
	scanf("%d%lld", &n, &t);
	for(i=1;i<=n;i++) scanf("%Lf%Lf%Lf", &a[i], &b[i], &p[i]), B = max(B,b[i]*p[i]), d[i].x = p[i], d[i].y = p[i] * a[i];
	sort(&d[1],&d[n]+1,[](dot a,dot b){if(fabs(a.x-b.x)>eps)return a.x<b.x;return a.y<b.y;});
	for(i=1;i<=n;i++)
	{
		while(top>1&&slope(top-1,top)<slope(top,i)) top--;
		d[++top] = d[i];
	}
	n = top;
	now.r = 1, now.c = 3, now.cl(), now.a[0][2] = 1;
	for(i=1;i<=n;i++)
	{
		pw[0].r = pw[0].c = 3;
		pw[0].a[0][1] = pw[0].a[0][2] = pw[0].a[1][2] = 0, pw[0].a[1][1] = pw[0].a[2][1] = pw[0].a[2][2] = (lf)1.0;
		pw[0].a[0][0] = (lf)1.0- d[i].x, pw[0].a[1][0] = d[i].x * B, pw[0].a[2][0] = d[i].y;
		for(j=1;now.a[0][1]+(lf)(1ll<<j)-eps<=(lf)t;j++) pw[j] = pw[j-1] * pw[j-1];
		for(j=35;j>=0;j--) if(now.a[0][1]+(lf)(1ll<<j)-eps<=(lf)t)
		{
			nn = now * pw[j];
			if(i==n||nn.a[0][0]-nn.a[0][1]*B>=slope(i,i+1)) now = nn;
		}
		if(now.a[0][1]+1.0-eps<t&&now.a[0][0]-now.a[0][1]*B>=slope(i,i+1)) now = now * pw[0];
	}
	printf("%.20Lf", now.a[0][0]);
	return 0;
}
```

---

