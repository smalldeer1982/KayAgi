# Memory and Casinos

## 题目描述

There are $ n $ casinos lined in a row. If Memory plays at casino $ i $ , he has probability $ p_{i} $ to win and move to the casino on the right ( $ i+1 $ ) or exit the row (if $ i=n $ ), and a probability $ 1-p_{i} $ to lose and move to the casino on the left ( $ i-1 $ ) or also exit the row (if $ i=1 $ ).

We say that Memory dominates on the interval $ i...\ j $ if he completes a walk such that,

- He starts on casino $ i $ .
- He never looses in casino $ i $ .
- He finishes his walk by winning in casino $ j $ .

Note that Memory can still walk left of the $ 1 $ -st casino and right of the casino $ n $ and that always finishes the process.

Now Memory has some requests, in one of the following forms:

- $ 1 $ $ i $ $ a $ $ b $ : Set ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF712E/c42dd9c43ce106339882f9fe876940fd18941cce.png).
- $ 2 $ $ l $ $ r $ : Print the probability that Memory will dominate on the interval $ l...\ r $ , i.e. compute the probability that Memory will first leave the segment $ l...\ r $ after winning at casino $ r $ , if she starts in casino $ l $ .

It is guaranteed that at any moment of time $ p $ is a non-decreasing sequence, i.e. $ p_{i}<=p_{i+1} $ for all $ i $ from $ 1 $ to $ n-1 $ .

Please help Memory by answering all his requests!

## 样例 #1

### 输入

```
3 13
1 3
1 2
2 3
2 1 1
2 1 2
2 1 3
2 2 2
2 2 3
2 3 3
1 2 2 3
2 1 1
2 1 2
2 1 3
2 2 2
2 2 3
2 3 3
```

### 输出

```
0.3333333333
0.2000000000
0.1666666667
0.5000000000
0.4000000000
0.6666666667
0.3333333333
0.2500000000
0.2222222222
0.6666666667
0.5714285714
0.6666666667
```

# 题解

## 作者：ywh666 (赞：12)

#  看到这题没人就写~~（shui）~~一发题解


首先设f(i)为从终点能活到i的方案数
则需求出$f(1)$的值

$f(i)=f(i-1)*(1-p(i))+f(i+1)*p(i)$

由此可推出
$p(i)*(f(i+1)-f(i-1))=f(i)-f(i-1)$

设$g(i)=f(i)-f(i-1)$

所以有$(g(i+1)+g(i))*p(i)=g(i)$

由此推出$g(i)*(1-p(i))/p(i)=g(i+1)$

因为$f(n)=1,f(0)=0$

所以$g(1)+g(2)+...+g(n)=1$

设$(1-p(i))/(p(i))=t(i)$

所以$g(1)*(1+t(1)+t(1)t(2)+...+t(1)t(2)...t(n))=1$

所以只需维护区间右边括号这个值即可

用线段树维护

$A=t(1)t(2)t(3)...t(n)$

$B=t(1)+t(1)t(2)+...+t(1)t(2)...t(n)$

则合并后的值$C=B[l,mid]+B(mid,r]*A[l,mid]$

#终于写完了~~（逃）~~# 

```cpp
#include <bits/stdc++.h>
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
using namespace std;
#define ll long long
template <class T> void read(T &x) {
	x = 0;
	int f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
	x *= f;
}
/*ti=(1/pi)/pi=(b-a)/a
ANS=1/(1+t1+t1t2+t1t2t3+t1t2t3t4+...+t1t2t3t4...tn-1)*/
/*线段树维护t1t2t3t4...tn
ANS=(t1+t1t2+t1t2t3+t1t2t3t4+...+t1t2t3t4...tmid)+(t1t2t3t4...tmid)*(tmid+tmidtmid+1.....-1)
*/
int n,m;
double jl[100005],tree1[400005],tree2[400005];
void build(int l,int r,int rt)
{
	if(l==r)
	{
		tree1[rt]=jl[l];
		tree2[rt]=jl[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(lson);build(rson);
	tree1[rt]=tree1[rt<<1]*tree1[rt<<1|1];
	tree2[rt]=tree2[rt<<1]+1.0*(tree2[rt<<1|1])*tree1[rt<<1];
}
void update(int to,double x,int l,int r,int rt)
{
	if(l==r)
	{
		tree1[rt]=x;
		tree2[rt]=x;
		return ;
	}
	int mid=(l+r)>>1;
	if(to<=mid)update(to,x,lson);
	else update(to,x,rson);
	tree1[rt]=tree1[rt<<1]*tree1[rt<<1|1];
	tree2[rt]=tree2[rt<<1]+1.0*(tree2[rt<<1|1])*tree1[rt<<1];
}
double query1(int L,int R,int l,int r,int rt)
{
	if(L<=l&&R>=r)return tree1[rt];
	int mid=(l+r)>>1;
	double ans=1.0;
	if(L<=mid)ans=1.0*ans*query1(L,R,lson);
	if(R>mid)ans=1.0*ans*query1(L,R,rson);
	return ans;
}
double query(int L,int R,int l,int r,int rt)
{
	if(L<=l&&R>=r)return tree2[rt];
	int mid=(l+r)>>1;
	double ans=0.0;
	if(L<=mid)ans+=1.0*query(L,R,lson);
	if(R>mid)ans+=1.0*query(L,R,rson)*query1(L,mid,lson);
	return ans;
}
int main()
{
	int a,b,c,qwq;
	read(n);read(m);
	for(int i=1;i<=n;++i)
	{
		read(a);read(b);
		jl[i]=1.0*(b-a)/a;
	}
	build(1,n,1);
	while(m--)
	{
		 read(qwq);
		 if(qwq==1)
		 {
			read(a);read(b);read(c);/*令a变为b/c*/
			jl[a]=1.0*(c-b)/b;
			update(a,jl[a],1,n,1);
		 }
		 if(qwq==2)
		 {
		 	read(a);read(b);
		 	printf("%.10f\n",1.0/(query(a,b,1,n,1)+1.0));
		 }
	}
}
```

---

## 作者：grass8cow (赞：9)

锻炼我思维水平的好题。

设 $f_i$ 表示从 $i$ 出发走到终点的概率，则需要查询的是 $f_l$ 。

由题知，$f_i=\begin{cases}0&i=l-1\\p_if_{i+1}+(1-p_i)f_{i-1}&l \le i \le r\\1&i=r+1\end{cases}$

把中间那个式子移项，得 $f_i-f_{i-1}=p_i(f_{i+1}-f_{i-1})$

设 $a_i=f_{i}-f_{i-1}$ ,则 $a_i=p_i(a_i+a_{i+1})$

移项，得 $a_{i+1}= \dfrac{1-p_i}{p_i}a_i$ (下面为了方便，设 $b_i=\dfrac{1-p_i}{p_i}$)

则 $a_i=a_l\prod_{j=l}^{i-1}b_j$

因为 $f_{r+1}-f_{l-1}=1$ ，所以 $\sum_{i=l}^{r+1}a_i=1$ 。

那么 $f_l=a_l=1/(\sum_{i=l}^{r+1}\prod_{j=l}^{i-1}b_j)$

 $\sum_{i=l}^{r+1}\prod_{j=l}^{i-1}b_j$ 能用线段树维护：
 
 设 $p_{l,r}$ 表示 $\prod_{i=l}^rb_i$ ,$a_{l,r}$ 表示 $[l,r] $ 的查询结果。设 $mi$ 满足 $l\le mi\le r$ ，
 
则 $a_{l,r}=a_{l,mi}+(p_{l,mi}-1)a_{mi+1,r}$

发现满足结合律，可以用线段树维护。单点改，区间查。

注意精度问题，每个值都和 $1e9$ 取 $min$ ，因为大于 $1e9$ 不影响答案。 

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
double sum[400010],ans[400010];
//线段树维护区间积
void build(int p,int l,int r){
	if(l==r){ans[p]=2;sum[p]=1;return;}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);build(p<<1|1,mid+1,r);
	sum[p]=min(1e9,sum[p<<1]*sum[p<<1|1]);
	ans[p]=min(1e9,ans[p<<1]+sum[p<<1]*(ans[p<<1|1]-1));
}
void update(int p,int l,int r,int x,double z){
	if(l==r){ans[p]=z+1;sum[p]=z;return;}
	int mid=(l+r)>>1;
	if(x<=mid)update(p<<1,l,mid,x,z);
	else update(p<<1|1,mid+1,r,x,z);
	sum[p]=min(1e9,sum[p<<1]*sum[p<<1|1]);
	ans[p]=min(1e9,ans[p<<1]+sum[p<<1]*(ans[p<<1|1]-1));
}
struct qq{double as,sum;};
qq ask(int p,int l,int r,int x,int y){
	int mid=(l+r)>>1;
	if(x<=l&&y>=r)return (qq){ans[p],sum[p]};
	if(y<=mid)return ask(p<<1,l,mid,x,y);
	if(x>mid)return ask(p<<1|1,mid+1,r,x,y);
	qq t=ask(p<<1,l,mid,x,y),t2=ask(p<<1|1,mid+1,r,x,y);
	return (qq){min(1e9,t.as+t.sum*(t2.as-1)),min(t.sum*t2.sum,1e9)};
}
int main(){
	scanf("%d%d",&n,&m);
	build(1,1,n);
	for(int i=1,a,b;i<=n;i++)scanf("%d%d",&a,&b),update(1,1,n,i,1.0*(b-a)/a);
	for(int i=1,ty,l,r,a,b,x;i<=m;i++){
		scanf("%d",&ty);
		if(ty&1)scanf("%d%d%d",&x,&a,&b),update(1,1,n,x,1.0*(b-a)/a);
		else scanf("%d%d",&l,&r),printf("%.6lf\n",1.0/ask(1,1,n,l,r).as);
	}
	return 0;
}
```


---

## 作者：流水行船CCD (赞：2)

设 $f_i$ 表示走到 $i$，最后可以掌控该区间的概率，转移方程易得：

$$f_i = p_if_{i+1}+(1-p_i)f_{i-1}$$

边界（初始值）：$f_{l-1}=0,f_{r+1}=1$。

方程有环，这类期望题的套路就是代入消元解方程，对上述方程移项可得：

$$\forall i \in [l+1,r+1],\ f_i=\frac{1}{p_{i-1}}(f_{i-1}-(1-p_{i-1})f_{i-2})$$

由于我们要求 $f_l$，那么通过上述式子递推求系数就可以把 $[l+1,r+1]$ 中的每一个 $f_i$ 表示成 $kf_l$ 的形式。

如：$f_{l+1} = \frac{1}{p_l}(f_l-(1-p_{i-1})\times 0) = \frac{1}{p_l} f_l$。

如果我们可以快速求出 $f_{r+1}=kf_l=1$，则可以解出 $\operatorname{Ans}=f_l=\frac{1}{k}$。

这个系数递推式是一个典型的类斐波那契递推式，直接线段树+矩阵维护即可，$\mathcal{O}(n \log n \times C^3)$，其中矩阵大小 $C=2$。

[link](https://codeforces.com/problemset/submission/712/319378287)。

---

## 作者：Rainybunny (赞：2)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[$luogu$](https://www.luogu.org/problem/CF712E).
# 题解
## 题意转化
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;本题可以理解为:  
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于一行$n$个格子, 每个格子有一个向右走的概率$p_i$, 对应的, 向左走的概率$1-p_i$, 多次修改某个$p_i$或询问你站在$l$, 在不走向$l-1$的前提下走到$r+1$的概率.  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先, 我们设$f(l,r)$表示**站在$l$, 不到$l-1$, 从$r$走出的概率**; 为了方便转移, 对应的有$g(l,r)$表示**站在$r$, 不到$r+1$, 从$l$走出的概率**.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;观察题目对区间的各种询问, 可以想象这是一道线段树.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;而后, 我们的难点在于区间的合并操作.  
## 区间合并
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设线段树上左区间的有$(f_1,g_1)$, 右区间有$(f_2,g_2)$, 接下来我们考虑如何计算整个区间的$(f,g)$.  
### 考虑$f$:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle f=f_1f_2+f_1(1-f_2)(1-g_1)f_2+f_1((1-f_2)(1-g_1))^2f_2+...$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;形式地说:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle f=\sum_{i=0}^{+\infty}f_1f_2((1-f_2)(1-g_1))^i=f_1f_2\sum_{i=0}^{+\infty}((1-f_2)(1-g_1))^i$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;形象理解, $f$就是 $p($一遍通过区间$)+$ $p($在中间转一圈通过区间$)+$ $p($转两圈通过区间$)+...$ ~~转晕了没?~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;快乐地等比数列求和:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle f=\frac{f_1f_2(1-((1-f_2)(1-g_1))^{+\infty})}{1-(1-f_2)(1-g_1)}=\frac{f_1f_2}{1-(1-f_2)(1-g_1)}$  
### 类似地, 考虑$g$:
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle g=g_2g_1+g_2(1-g_1)(1-f_2)g_1+g_2((1-g_1)(1-f_2))^2g_1+...$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;它与$f$中的公比都是"$p($在中间完成转圈$)$". 所以:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle g=\frac{g_1g_2}{1-(1-f_2)(1-g_1)}$  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;特别地, 当$l=r$, $f(l,r)=p_l$, $g(l,r)=1-p_l$, 丢到树里维护即可.  
```cpp
#include <cstdio>
#include <utility>

#define Int register int

using namespace std;

typedef pair<double, double> pdd;

const int MAXN = 1e5;
int n, q;
double p[MAXN + 5] = {};

class Segment_Tree {
private:
	struct Node {
		int l, r;
		double f, g;
	} Tree[MAXN << 2];

public:
	inline void Push_up ( const int i ) {
		double f1 = Tree[i << 1].f, f2 = Tree[i << 1 | 1].f;
		double g1 = Tree[i << 1].g, g2 = Tree[i << 1 | 1].g;
		Tree[i].f = f1 * f2 / ( 1 - ( 1 - f2 ) * ( 1 - g1 ) );
		Tree[i].g = g1 * g2 / ( 1 - ( 1 - f2 ) * ( 1 - g1 ) );
	}
	inline void Build ( const int i, const int l, const int r, double* p ) {
		Tree[i] = { l, r, 0.0, 0.0 };
		if ( l == r ) { Tree[i].f = p[l], Tree[i].g = 1 - p[l]; return ; }
		int mid = l + r >> 1;
		Build ( i << 1, l, mid, p ), Build ( i << 1 | 1, mid + 1, r, p );
		Push_up ( i );
	}
	inline void Update ( const int i, const int Indx, const double p ) {
		if ( Tree[i].r < Indx || Indx < Tree[i].l ) return ;
		if ( Tree[i].l == Indx && Tree[i].r == Indx ) {
			Tree[i].f = p, Tree[i].g = 1 - p;
			return ;
		}
		Update ( i << 1, Indx, p ), Update ( i << 1 | 1, Indx, p );
		Push_up ( i );
	}
	inline pdd Query ( const int i, const int l, const int r ) {
		if ( l <= Tree[i].l && Tree[i].r <= r ) return { Tree[i].f, Tree[i].g };
		int mid = Tree[i].l + Tree[i].r >> 1;
		if ( r <= mid ) return Query ( i << 1, l, r );
		else if ( mid < l ) return Query ( i << 1 | 1, l, r );
		pdd lret = Query ( i << 1, l, mid ), rret = Query ( i << 1 | 1, mid + 1, r );
		return { lret.first * rret.first / ( 1 - ( 1 - rret.first ) * ( 1 - lret.second ) ),
				lret.second * rret.second / ( 1 - ( 1 - rret.first ) * ( 1 - lret.second ) ) };
	}
} SegTree;

inline int rint () {
	int x = 0, f = 1; char s = getchar ();
	for ( ; s < '0' || '9' < s; s = getchar () ) f = s == '-' ? -f : f;
	for ( ; '0' <= s && s <= '9'; s = getchar () ) x = ( x << 3 ) + ( x << 1 ) + ( s ^ '0' );
	return x * f;
}

inline void Work () {
	n = rint (), q = rint ();
	for ( Int i = 1; i <= n; ++ i ) p[i] = 1.0 * rint () / rint ();
	SegTree.Build ( 1, 1, n, p );
	for ( Int opt, i, a, b; q --; ) {
		opt = rint ();
		if ( opt & 1 ) {
			i = rint (), a = rint (), b = rint ();
			SegTree.Update ( 1, i, 1.0 * a / b );
		} else {
			a = rint (), b = rint ();
			printf ( "%.10lf\n", SegTree.Query ( 1, a, b ).first );
		}
	}
}

int main () {
	Work ();
	return 0;
}
```

---

## 作者：crashed (赞：2)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/CF712E)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看到这种跟区间和修改有关的，当场线段树开搞。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑区间的合并（这个最难搞），我们用一个函数$f(l,r)(1\le l \le r \le n)$表示从$l$开始不从左边走出$[l,r]$（也就是不走到$l-1$）的情况下，从右边走出区间$[l,r]$（也就是走到$r+1$）的概率。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑转移......emmmmmm......做不来......  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;再加一个状态，$g(l,r)$类似于$f(l,r)$，只不过是在区间$[l,r]$中右进左出。假设区间的中点是$mid$，我们考虑这样转移：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle f(l,r)=f(l,mid)f(mid+1,r)\ \ \ \ \ \ \ \text{一遍走出去}$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle \ \ \ \ \ \ \ \ \ \ \ \ +f(l,mid)(1-f(mid+1,r))(1-g(l,mid))f(mid+1,r)\ \ \ \ \ \ \ \text{中间穿一遍才出去}$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle \ \ \ \ \ \ \ \ \ \ \ \ +f(l,mid)[(1-f(mid+1,r))(1-g(l,mid))]^2f(mid+1,r)\ \ \ \ \ \ \ \text{反反复复......}$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;令$t=(1-f(mid+1,r))(1-g(l,mid))$，则可以得到：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle f=f(l,mid)f(mid+1,r)(1+t+t^2+t^3+......)$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle \ \ \ \ =f(l,mid)f(mid+1,r)\frac{1-t^\infty}{1-t}$    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle \ \ \ \ =f(l,mid)f(mid+1,r)\frac 1 {1-t}$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle \ \ \ \ =\frac{f(l,mid)f(mid+1,r)}{f(mid+1,r)+g(l,mid)-f(mid+1,r)g(l,mid)}$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这样就可以直接算了，$g$的算法类似，就是把分子换一下。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;注意，如果$f(mid+1,r)$和$g(l,mid)$同时为$0$和同时为$1$，分母就会变成$0$。解决方法就是——  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;用一个$eps$修正一下就就好了，精度范围之内不会影响结果。  
# 代码
```cpp
#include <cstdio>

#define isLeaf( a ) ( segTree[a].l == segTree[a].r )

const double eps = 1e-8;
const int MAXN = 1e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T ABS( const _T a )
{
	return a < 0 ? -a : a;
}

struct segmentTreeNode
{
	int l, r;
	double f, g;
}segTree[MAXN << 2];

typedef struct result
{
	double f, g;
	result() { f = 0, g = 0; }
	result( const double F, const double G ) { f = F, g = G; }
}R;

double p[MAXN];
int N, M;

void upt( const int now )
{
	segTree[now].f = segTree[now << 1].f * segTree[now << 1 | 1].f / ( segTree[now << 1 | 1].f + segTree[now << 1].g - segTree[now << 1].g * segTree[now << 1 | 1].f );
	segTree[now].g = segTree[now << 1].g * segTree[now << 1 | 1].g / ( segTree[now << 1 | 1].f + segTree[now << 1].g - segTree[now << 1].g * segTree[now << 1 | 1].f );
}

R upt( const R v, const R w )
{
	R u;
	u.f = v.f * w.f / ( w.f + v.g - v.g * w.f );
	u.g = v.g * w.g / ( w.f + v.g - v.g * w.f );
	return u;
}

void build( const int now, const int left, const int right )
{
	segTree[now].l = left, segTree[now].r = right;
	if( isLeaf( now ) ) { segTree[now].f = p[left], segTree[now].g = 1 - p[left]; return; }
	build( now << 1, left, ( left + right ) >> 1 ), build( now << 1 | 1, ( ( left + right ) >> 1 ) + 1, right );
	upt( now );
}

void update( const int now, const int indx, const double val )
{
	if( indx < segTree[now].l || segTree[now].r < indx ) return ;
	if( indx <= segTree[now].l && segTree[now].r <= indx ) { segTree[now].f = val, segTree[now].g = 1 - val; return ; }
	if( isLeaf( now ) ) return ;
	update( now << 1, indx, val ), update( now << 1 | 1, indx, val );
	upt( now );
}

R query( const int now, const int segL, const int segR )
{
	if( segL <= segTree[now].l && segTree[now].r <= segR ) { return R( segTree[now].f, segTree[now].g ); }
	int mid = ( segTree[now].l + segTree[now].r ) >> 1;
	if( segR <= mid ) return query( now << 1, segL, segR );
	else if( segL > mid ) return query( now << 1 | 1, segL, segR );
	else return upt( query( now << 1, segL, segR ), query( now << 1 | 1, segL, segR ) );
}

bool equal( const double x, const double y = 0 ) { return ABS( x - y ) <= eps; }
double fix( const double x ) { return equal( x ) ? x + eps : ( equal( x, 1 ) ? x - eps : x ); }

int main()
{
	int a, b;
	read( N ), read( M );
	for( int i = 1 ; i <= N ; i ++ )
		read( a ), read( b ), p[i] = fix( 1.0 * a / b );
	int opt, pos;
	R t;
	build( 1, 1, N );
	while( M -- )
	{
		read( opt );
		if( opt & 1 )
		{
			read( pos ), read( a ), read( b );
			update( 1, pos, fix( 1.0 * a / b ) );
		}
		else
		{
			read( a ), read( b );
			t = query( 1, a, b );
			printf( "%.10lf\n", t.f );
		}
	}
	return 0;
}
```

---

## 作者：czpcf (赞：2)

## 题意
每次询问一段区间[l,r]，求从最左边走到最右边（r+1）的概率（若走到l-1，则GG了），每个点上写有向右走的概率。支持单点修改。


## 思考
若只查询一次，那只要知道每个点在不走到l-1的情况下，向右移动一格的概率就行了，最后乘起来就是答案。

但我们忽略了一件事情，若从一个区间的某一点出发，从左边走出去和右边走出去的概率和为1（不可能停在中间），于是我们要设计一个状态，并能够合并，这样才有可能优化复杂度。


设 [l,r] 区间的L为从第l个点（最左边）出发，在右边走出去的概率，R为第R个点出发，在左边走出去的概率。


|[L1|-->|R1]|[L2|-->|R2]|
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
|[ L|--|--|--|-->|R ]|



请记住，他们每个的实际意义。因为每个点要么从左边走出去，要么从右边走出去，所（1-L1）的实际意义就是从（左边出发，不从右边走出），即（从左边出发，从左边走出去的概率）。

那么若有两个连续的区间，合并成一个新区间会有怎样的答案？
设左右两个区间的答案分别为L1,R1,L2,R2，则：

###### L= L1*L2----走到右边还要再走到更右边
###### +L1*(1-L2)*(1-R1)*L2----第一次向右边走失败了，再退回来再向右走
###### +L1*(1-L2)*(1-R1)*(1-L2)*(1-R1)*L2----反反复复.......
###### +.......

整理一下，

###### L=L1*L2+L1*L2*(1-L2)*(1-R1)+L1*L2*(1-L2)^2+.......
###### (1-L2)*(1-R1)L=L1*L2*(1-L2)*(1-R1)+L1*L2*(1-L2)^2+.......
作差，
###### L(1-(1-L2)(1-R1))=L1L2
###### L=L1L2/(1-(1-L2)(1-R1))
R也可以类似地得到，但注意它们的和不一定为1，因为是两个不同的端点。

简单地线段树维护。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1E5+5;
int n,m;
double x,y,a[maxn];
struct tree{int l,r;double L,R;}t[maxn*4];
tree merge(tree x,tree y)
{
	tree z;
	z.l=x.l;z.r=y.r;
	z.L=x.L*y.L/(1-(1-y.L)*(1-x.R));
	z.R=x.R*y.R/(1-(1-y.L)*(1-x.R));//不要认为反一反就对了QAQ 
	return z;
}
void build(int l,int r,int num)
{
	t[num].l=l,t[num].r=r;
	if(l==r)
	{
		t[num].L=a[l];
		t[num].R=1-a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,num*2);build(mid+1,r,num*2+1);
	t[num]=merge(t[num*2],t[num*2+1]);
}
void change(int pos,double val,int num)
{
	if(t[num].l==t[num].r)
	{
		t[num].L=val;
		t[num].R=1-val;
		return;
	}
	int mid=(t[num].l+t[num].r)>>1;
	if(pos<=mid)change(pos,val,num*2);
	else change(pos,val,num*2+1);
	t[num]=merge(t[num*2],t[num*2+1]);
}
tree ask(int L,int R,int num)
{
	if(L<=t[num].l&&t[num].r<=R)return t[num];
	int mid=(t[num].l+t[num].r)>>1;
	if(R<=mid)return ask(L,R,num*2);
	else if(mid<L)return ask(L,R,num*2+1);
	else return merge(ask(L,R,num*2),ask(L,R,num*2+1));
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
	{
		cin>>x>>y;
		a[i]=x/y;
	}
	build(1,n,1);
	while(m--)
	{
		int opt,d;
		cin>>opt;
		if(opt==1)
		{
			cin>>d>>x>>y;
			change(d,x/y,1);
		}
		else
		{
			int l,r;
			cin>>l>>r;
			cout<<fixed<<setprecision(8)<<ask(l,r,1).L<<endl;
		}
	}
	return 0;
}

```

---

## 作者：Purslane (赞：0)

# Solution

先吐槽：

1. 题目中保证 $p$ 递增的条件几乎没用。
2. 很容易构造数据让你的 double 溢出，所以在运算过程中要和 $10^9$ 取 $\min$。

设 $f_i$ 为从 $i$ 出发，能安全到达 $r+1$ 的概率。

则

$$
f_i = p_i f_{i+1} + (1-p_i)f_{i-1}
$$

其中 $f_{l-1}=0$，$f_{r+1}=1$。

直接高斯消元肯定没前途，考虑用 $f_{l}$ 表示 $f_{l+1}$、$f_{l+2}$、$\dots$、$f_{r+1}$，最后利用 $f_{r+1} = 1$ 解除 $f_l$。

很容易发现，这些数都可以写作 $k_i f_l$ 的形式，已知 $k_{l-1}=0$，$k_l=1$。

而：

$$
k_{i+1} = \dfrac{1}{1-p_i} k_i - \dfrac{p_i}{1-p_i} k_{i-1}
$$

使用线段树维护矩阵即可。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,q;
struct Matrix {ld v[2][2];}t[MAXN<<2];
Matrix operator *(Matrix A,Matrix B) {
	Matrix C;
	C.v[0][0]=A.v[0][0]*B.v[0][0]+A.v[0][1]*B.v[1][0];
	C.v[0][1]=A.v[0][0]*B.v[0][1]+A.v[0][1]*B.v[1][1];
	C.v[1][0]=A.v[1][0]*B.v[0][0]+A.v[1][1]*B.v[1][0];
	C.v[1][1]=A.v[1][0]*B.v[0][1]+A.v[1][1]*B.v[1][1];
	ffor(a,0,1) ffor(b,0,1) C.v[a][b]=min(C.v[a][b],(ld)1000000000.0);
	return C;
}
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void update(int k,int l,int r,int pos,ld a,ld b) {
	if(l==r) return t[k].v[0][0]=0,t[k].v[0][1]=1.0*(a-b)/a,t[k].v[1][0]=1,t[k].v[1][1]=1.0*b/a,void();
	if(pos<=mid) update(lson,l,mid,pos,a,b);
	else update(rson,mid+1,r,pos,a,b);
	return t[k]=t[lson]*t[rson],void();
}
Matrix query(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return t[k];
	if(y<=mid) return query(lson,l,mid,x,y);
	if(x>mid) return query(rson,mid+1,r,x,y);
	return query(lson,l,mid,x,y)*query(rson,mid+1,r,x,y);	
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	ffor(i,1,n) {ld a,b;cin>>a>>b,update(1,1,n,i,a,b);}
	ffor(i,1,q) {
		int op;
		cin>>op;
		if(op==1) {
			int pos;
			ld a,b;
			cin>>pos>>a>>b,update(1,1,n,pos,a,b);
		}
		else {
			int l,r;
			cin>>l>>r;
			auto mt=query(1,1,n,l,r);
			cout<<fixed<<setprecision(10)<<1.0/mt.v[1][1]<<'\n';	
		}
	}
	return 0;
}
```

---

## 作者：white_carton (赞：0)

[更好的阅读体验](https://starback24.github.io)

[题目链接](https://codeforces.com/problemset/problem/712/E)

### 闲话

写这篇题解的原因是因为唯一一篇矩阵线段树题解的作者写矩阵的习惯令人瞳孔震惊。

---

### 分析

设 $f_i$ 为 $i$ 可以到达目标的概率，由于 $i$ 有 $p_i\%$ 的概率走到 $i+1$，有 $1-p\%$ 的概率走到 $i-1$，所以 $f_i$ 就等于 $p_if_{i+1}$ 和 $(1-p_i)f_{i-1}$ 的和，也就是
$$
f_i=p_if_{i+1}+(1-p_{i})f_{i-1}
$$
对于这种中间由左边和右边推出的式子，一个很常用的方法就是将他们移项，使下标最大的单独在一边。我们将其移项。
$$
p_if_{i+1}=f_i+(p_i-1)f_{i-1}
\\
f_{i+1}=\frac{1}{p_i}f_i+(1-\frac{1}{p_i})f_{i-1}
$$
对于这个递推式，我们可以将其写成矩阵形式转移。
$$
\left[f_{i+1},f_i\right]=\left[f_i,f_{i-1}\right]\begin{bmatrix}\frac{1}{p_i} &1\\1-\frac{1}{p_i} & 0\end{bmatrix}
$$
然后我们用线段树维护矩阵的乘积，令每次查询区间 $\left[l,r\right]$ 查询到的矩阵为 $A$，$A$ 是 $r-l+1$ 个矩阵相乘的结果，所以 $\left[f_l,f_{l-1}\right]A$ 的结果为 $\left[f_r+1,f_r\right]$。设 $A=\begin{bmatrix}A_1&A_2\\A_3&A_4\end{bmatrix}$，我们有 $\left[f_l,f_{l-1}\right]\begin{bmatrix}A_1&A_2\\A_3&A_4\end{bmatrix}=\left[f_{r+1},f_r\right]$。我们将矩阵拆开可以得到 $f_lA_1+f_{l-1}A_3=f_{r+1}$，因为我们在 $\left[l,r\right]$，所以 $f_{r+1}=1,f_{l-1}=0$，带入上式可以得到，$f_l=\frac{1}{A_1}$，于是我们可以开心地敲代码了。

### 代码

```cpp
//火车头略
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Dor(i,a,b) for(int i=a;i>=b;i--)
const int N=1e5+3;
struct matrix{
	double a,b,c,d;
	matrix friend operator *(matrix x,matrix y){
		matrix res;
		res.a=min(1e10,x.a*y.a)+min(1e10,x.b*y.c);
		res.b=min(1e10,x.a*y.b)+min(1e10,x.b*y.d);
		res.c=min(1e10,x.c*y.a)+min(1e10,x.d*y.c);
		res.d=min(1e10,x.c*y.b)+min(1e10,x.d*y.d);
		return res;
	}
}t[N<<2];
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
void pushup(int p){
	t[p]=t[ls]*t[rs];
}
double a[N];
void build(int p,int l,int r){
	if(l==r){
		double x=1/a[l];
		t[p]={x,1.0,1.0-x,0};
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(p);
}
void update(int p,int l,int r,int x,matrix dx){
	if(l==r){
		t[p]=dx;
		return;
	}
	if(x<=mid){
		update(ls,l,mid,x,dx);
	}
	else{
		update(rs,mid+1,r,x,dx);
	}
	pushup(p);
}
matrix query(int p,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr){
		return t[p];
	}
	matrix tmp={1,0,0,1};
	if(ql<=mid){
		tmp=query(ls,l,mid,ql,qr);
	}
	if(qr>mid){
		tmp=tmp*query(rs,mid+1,r,ql,qr);
	}
	return tmp;
}
int n,m;
signed main(){
	cin>>n>>m;
	For(i,1,n){
		int x,y;
		cin>>x>>y;
		a[i]=(double)x/(1.0*y);
	}
	build(1,1,n);
	For(i,1,m){
		int opt;
		cin>>opt;
		if(opt==1){
			int pos,x,y;
			cin>>pos>>x>>y;
			double p=((double)x/(1.0*y));
			a[pos]=p;
			p=1.0/p;
			matrix tmp={p,1,1.0-p,0};
			update(1,1,n,pos,tmp);
		}
		else{
			int l,r;
			cin>>l>>r;
			matrix tmp=query(1,1,n,l,r);
			double ans=1.0/tmp.a;
			printf("%.9lf\n",ans);
		}
	}
}
//正难则反
//是否考虑了所有情况
```

### 闲话

我是一边听着イエスタデイ一边写下这篇题解的，歌非常好听，建议大家都听一听。

---

## 作者：zifanwang (赞：0)

假设只保留数组上 $[l,r]$ 的这段数，记 $f_i$ 表示从点 $i$ 出发到达 $n+1$ 的概率，则有 $f_0=0,f_{n+1}=1,f_i=(1-p_i)f_{i-1}+p_if_{i+1}$，题目要求的是 $f_1$。

考虑对最后一个等式进行一些变换，把 $f_i$ 的系数拆开得：

$$
p_if_i+(1-p_i)f_i=(1-p_i)f_{i-1}+p_if_{i+1}
$$
移项得：
$$
(1-p_i)(f_i-f_{i-1})=p_i(f_{i+1}-f_i)
$$

记 $d_i=f_{i+1}-f_i$，那么由上式得 $d_i=\frac{1-p_i}{p_i}d_{i-1}$。

显然有 $\sum_{i=0}^nd_i=1,f_1=d_0$，于是 $f_1=\frac 1{1+\sum_{i=1}^n d_i}$，线段树维护即可。

时间复杂度 $\mathcal O(n\log n)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define mxn 100003
#define ld long double
#define rep(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
struct node{
	ld s,d;
}t[mxn<<2];
int n,q,a,b;
ld d[mxn];
inline node operator+(node x,node y){
	return {x.s+x.d*(y.s-1),x.d*y.d};
}
void build(int p,int l,int r){
	if(l==r){
		t[p]={d[l]+1,d[l]};
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	t[p]=t[p<<1]+t[p<<1|1];
}
void change(int p,int x,int l,int r){
	if(l==r){
		t[p]={d[l]+1,d[l]};
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)change(p<<1,x,l,mid);
	else change(p<<1|1,x,mid+1,r);
	t[p]=t[p<<1]+t[p<<1|1];
}
node ask(int p,int l,int r,int L,int R){
	if(l<=L&&R<=r)return t[p];
	int mid=(L+R)>>1;
	if(l<=mid&&r>mid)return ask(p<<1,l,r,L,mid)+ask(p<<1|1,l,r,mid+1,R);
	if(l<=mid)return ask(p<<1,l,r,L,mid);
	return ask(p<<1|1,l,r,mid+1,R);
}
signed main(){
	scanf("%d%d",&n,&q);
	rep(i,1,n)scanf("%d%d",&a,&b),d[i]=(ld)a/b,d[i]=(1-d[i])/d[i];
	build(1,1,n);
	int op,x,l,r;
	while(q--){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d%d",&x,&l,&r);
			d[x]=(ld)l/r;
			d[x]=(1-d[x])/d[x];
			change(1,x,1,n);
		}else{
			scanf("%d%d",&l,&r);
			printf("%.9Lf\n",1/ask(1,l,r,1,n).s);
		}
	}
	return 0;
}
```

---

## 作者：xfrvq (赞：0)

[$\tt Link$](/problem/CF712E)。

这一看就很线段树。于是我们考虑把问题转化成有结合律的信息。

下面对于一个询问 $[l,r]$ 进行讨论。

我们记 $a_i$ 为从 $i\to r$ 的概率。（你会发现确实存在无限循环的情况，但是我们对式子进行转化，使得可以维护）。

（默认下 $a_0=a_l=0,a_r=a_n=n$）而有

$$a_i=a_{i-1}(1-p_i)+a_{i+1}p_i$$

移项得

$$p_i(a_{i+1}-a_{i-1})=a_i-a_{i-1}$$

我们定义 $a_{1\cdot\cdot n}$ 的差分 $b_i=a_i-a_{i-1}$。

因为 $a_{i+1}-a_{i-1}=b_{i+1}+b_i,a_i=a_{i-1}=b_i$。

所以

$$p_i(b_{i+1}+b_i)=b_i$$

移项，即

$$\dfrac{1-p_i}{p_i}\times b_i=b_{i+1}$$

我们设 $v_i=\dfrac{1-p_i}{p_i}$，这时观察到有

$$1+\color{red}\sum_{i=1}^n\prod_{j=1}^iv_j\color{black}=\dfrac 1{b_1}$$

所以我们用线段树维护红色部分的值就行了。

维护

$$
\begin{cases}
f_{l,r}=\prod_{j=l}^rv_j\\
g_{l,r}=\sum_{i=l}^r\prod_{j=l}^iv_j
\end{cases}
$$

转移有（$u,v$ 分别是左儿子和右儿子）

$$
\begin{cases}
f_i=f_uf_v\\
g_i=g_u+f_ug_v
\end{cases}
$$

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5,S = N << 2;

int n,m,cc = 0;

namespace ST{
	using node = pair<double,double>; node T[S];
	
	#define f first
	#define g second
	
	#define lc (i << 1)
	#define rc (i << 1 | 1)
	#define mid ((L + R) >> 1)
	
	#define id int i,int L,int R
	
	auto mrg(const auto &cl,const auto &cr){
		return node(cl.f * cr.f,cl.g + cl.f * cr.g);
	}
	
	void build(id){
		if(L == R){
			int p,q; scanf("%d%d",&p,&q);
			double v = 1.0 * (q - p) / p;
			T[i] = node(v,v);
			return;
		}
		build(lc,L,mid);
		build(rc,mid + 1,R);
		T[i] = mrg(T[lc],T[rc]);
	}
	
	void upd(int v,id){
		if(L == R){
			int p,q; scanf("%d%d",&p,&q);
			double v = 1.0 * (q - p) / p;
			T[i] = node(v,v);
			return;
		}
		v <= mid ? upd(v,lc,L,mid) : upd(v,rc,mid + 1,R);
		T[i] = mrg(T[lc],T[rc]);
	}
	
	node qry(int l,int r,id){
		if(l <= L && R <= r) return T[i];
		if(r <= mid) return qry(l,r,lc,L,mid);
		if(l > mid) return qry(l,r,rc,mid + 1,R);
		return mrg(qry(l,r,lc,L,mid),qry(l,r,rc,mid + 1,R));
	}
}

int main(){
	scanf("%d%d",&n,&m);
	ST::build(1,1,n);
	while(m--){
		int op; scanf("%d",&op);
		if(op == 1){
			int i; scanf("%d",&i);
			ST::upd(i,1,1,n);
		} else {
			int l,r; scanf("%d%d",&l,&r);
			cc = 0;
			printf("%.10f\n",1.0 / (ST::qry(l,r,1,1,n).g + 1.0));
		}
	}
	return 0;
}
```

---

## 作者：_HL_ (赞：0)

看题解区没写矩阵线段树的 写一发题解

设 $f_i$ 为 $i$ 可以按要求到达目标的概率 发现不管限制设成什么都有 

$f_i=p_if_{i+1}+(1-p_i)f_{i-1}$ 

即分别统计往左往右到达目标的概率

变一个形 $f_{i+1}=\dfrac{1}{p_i}f_i+(1-\dfrac{1}{p_i})f_{i-1}$

发现是一个二阶线性递推的形式 写成矩阵

$\begin{bmatrix} f_{i+1}&f_{i}\end{bmatrix}=\begin{bmatrix} f_{i}&f_{i-1}\end{bmatrix}\begin{bmatrix} \frac{1}{p_i}&1-\frac{1}{p_i}\\1&0\end{bmatrix}$

然后线段树维护矩阵乘积 每次区间查询得到的矩阵 $A$ 有

$\begin{bmatrix} f_{r+1}&f_{r}\end{bmatrix}=\begin{bmatrix} f_{l}&f_{l-1}\end{bmatrix}A$

有 $f_{r+1}=1,f_{l-1}=0$ 可以解出 $f_l$

为啥不取模 调了好久精度。。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+3;
double a[N];
struct matrix
{
	double a,b,c,d;
}t[N<<2];
#define ls p<<1
#define rs p<<1|1
inline matrix mul(const matrix &x,const matrix &y)
{
	matrix res;
	res.a=min(1e10,x.a*y.a)+min(1e10,x.b*y.c);
	res.b=min(1e10,x.a*y.b)+min(1e10,x.b*y.d);
	res.c=min(1e10,x.c*y.a)+min(1e10,x.d*y.c);
	res.d=min(1e10,x.c*y.b)+min(1e10,x.d*y.d);
	return res;
}
inline void update(int p)
{
	t[p]=mul(t[rs],t[ls]);
}
void build(int l,int r,int p)
{
	if(l==r)
	{
		double o=1.0/a[l];
		t[p]={o,1.0-o,1.0,0.0};
		return;
	}
	int mid=l+r>>1;
	build(l,mid,ls);
	build(mid+1,r,rs);
	update(p);
}
void modify(int l,int r,int x,const matrix &dx,int p)
{
	if(l==r)
	{
		t[p]=dx;
		return;
	}
	int mid=l+r>>1;
	if(x<=mid)modify(l,mid,x,dx,ls);
	else
	modify(mid+1,r,x,dx,rs);
	update(p);
}
matrix query(int l,int r,int ql,int qr,int p)
{
	if(ql<=l&&r<=qr)
	{
		return t[p];
	}
	int mid=l+r>>1;
	matrix tmp={1.0,0.0,0.0,1.0};
	if(ql<=mid)tmp=query(l,mid,ql,qr,ls);
	if(qr>mid)tmp=mul(query(mid+1,r,ql,qr,rs),tmp);
	return tmp;
}
signed main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[i]=(double)(x)/(double)(y);
	}
	build(1,n,1);
	for(int i=1;i<=m;i++)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			int pos,x,y;
			scanf("%d%d%d",&pos,&x,&y);
			double p=(double)(x)/(double)(y);
			a[pos]=p;
			p=1.0/p;
			matrix tmp={p,1.0-p,1.0,0.0};
			modify(1,n,pos,tmp,1);
		}
		else
		{
			int l,r;
			scanf("%d%d",&l,&r);
			matrix tmp=query(1,n,l,r,1);
			double ans=1.0/tmp.a;
			printf("%.9lf\n",ans);
		}
	}
	return 0;
}
```


---

## 作者：Alex_Wei (赞：0)

> [CF712E Memory and Casinos](https://www.luogu.com.cn/problem/CF712E)

考虑对全局求答案。

这种可能经过重复状态的概率期望题一般都考虑列方程高斯消元。因为获胜概率和之前的经历无关，只需当前位置有关，故设 $f_i$ 表示在 $i$ 处获胜的概率。$f_0 = 0$，$f_{n + 1} = 1$。

对于 $f_i$，根据实际意义，有方程 $f_i = p_i f_{i + 1} + (1 - p) f_{i - 1}$。对 $n$ 个这样的方程做高斯消元实在是太蠢了。考虑化简。
$$
\begin{aligned}
p_if_i + (1 - p_i)f_i & = p_i f_{i + 1} + (1 - p) f_{i - 1} \\
(1 - p_i)(f_i - f_{i - 1}) & = p_i(f_{i + 1} - f_i) \\
d_{i + 1} & = \dfrac {1 - p_i}{p_i} d_i
\end{aligned}
$$
这样我们得到了 $f$ 的差分数组的递推式。令 $pd_i$ 表示 $\dfrac {1 - p_i}{p_i}$ 的前缀积，则 $d_i = pd_{i - 1} d_1$，而答案即 $\dfrac {d_1}{\sum\limits_{i = 1} ^ {n + 1} d_i}$，相当于 $\dfrac 1 {1 + \sum\limits_{i = 1} ^ n pd_i}$。

对于区间 $[l, r]$，根据上述推导，容易得出答案式 $\dfrac{1}{1 + \sum\limits_{i = l} ^ r\prod\limits_{j = l} ^ i p_j}$。为支持带修，线段树维护区间 $p_i$ 的前缀积以及前缀积的和即可。

时间复杂度 $\mathcal{O}(n + q\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool Mbe;
constexpr int N = 1e5 + 5;
struct dat {
  double prod, sum;
  dat operator + (const dat &rhs) const {
    dat res;
    res.prod = prod * rhs.prod;
    res.sum = sum + prod * rhs.sum;
    return res;
  }
} val[N << 2];
void modify(int l, int r, int p, int x, double v) {
  if(l == r) return val[x] = {v, v}, void();
  int m = l + r >> 1;
  if(p <= m) modify(l, m, p, x << 1, v);
  else modify(m + 1, r, p, x << 1 | 1, v);
  val[x] = val[x << 1] + val[x << 1 | 1];
}
dat query(int l, int r, int ql, int qr, int x) {
  if(ql <= l && r <= qr) return val[x];
  int m = l + r >> 1;
  dat ans = {1, 0};
  if(ql <= m) ans = query(l, m, ql, qr, x << 1);
  if(m < qr) ans = ans + query(m + 1, r, ql, qr, x << 1 | 1);
  return ans;
}
bool Med;
int main() {
  fprintf(stderr, "%.4lf\n", (&Mbe - &Med) / 1048576.0);
#ifdef ALEX_WEI
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif
  int n, q;
  cin >> n >> q;
  for(int i = 1; i <= n; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    double p = 1. * a / b;
    modify(1, n, i, 1, (1 - p) / p);
  }
  for(int i = 1; i <= q; i++) {
    int op;
    scanf("%d", &op);
    if(op == 1) {
      int x, a, b;
      scanf("%d%d%d", &x, &a, &b);
      double p = 1. * a / b;
      modify(1, n, x, 1, (1 - p) / p);
    }
    if(op == 2) {
      int l, r;
      scanf("%d%d", &l, &r);
      printf("%.9lf\n", 1. / (query(1, n, l, r, 1).sum + 1));
    }
  }
  return 0;
}
/*
2022/6/16
start coding at 14:24
finish debugging at 14:35
*/
```

---

## 作者：dsidsi (赞：0)

### Description

有 $n$ 个点，每个点有一个概率$p_i$，站在这个点时，你有$p_i$的概率移动到$i + 1$,有$1 − p_i $的概率移动到$i−1$，支持以下操作：
    
 - 修改一个$p_i$
 - 给定一个区间$[l, r]$，求在这个区间从 $l$ 移动到 $r + 1$，且在移动到 $r + 1$ 之前不走出区间边界的概率。
    
$n,q \leq 10^5$
    
### Solution

设$L(l,r),R(l,r)$分别表示从$l,r$出发到达$r+1$的概率（一旦走出$[l,r]$立即停止）。

现在要合并两段区间的$L,R$，设对应的值分别为$l_1,r_1,l_2,r_2$

$$
\begin{matrix}
L(l,r)&=&l_1l_2\sum_{i=0}^\infty(1-l_2)^ir_1^n\\
&=&\frac{l_1l_2}{1-(1-l_2)r_1}\\
R(l,r)&=&r_2+(1-r_2)r_1l_2\sum_{i=0}^\infty(1-l_2)^nr_1^n\\
&=&r_2+\frac{(1-r_2)r_1l_2}{1-(1-l_2)r_1}
\end{matrix}
$$

线段树维护即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;

inline int gi()
{
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	int sum = 0;
	while ('0' <= c && c <= '9') sum = sum * 10 + c - 48, c = getchar();
	return sum;
}

int n, q;

struct node
{
	double l, r;
	node (double _x = 0) {l = r = _x;}
	node (double _l, double _r) {l = _l; r = _r;}
	node operator + (const node &a) const {
		return node(l * a.l / (1 - (1 - a.l) * r), a.r + (1 - a.r) * r * a.l / (1 - (1 - a.l) * r));
	}
} t[maxn << 2];

#define mid ((l + r) >> 1)
#define lch (s << 1)
#define rch (s << 1 | 1)

void build(int s, int l, int r)
{
	if (l == r) return t[s] = node(1. * gi() / gi()), void();
	build(lch, l, mid);
	build(rch, mid + 1, r);
	t[s] = t[lch] + t[rch];
}

void modify(int s, int l, int r, int x)
{
	if (l == r) return t[s] = node(1. * gi() / gi()), void();
	if (x <= mid) modify(lch, l, mid, x);
	else modify(rch, mid + 1, r, x);
	t[s] = t[lch] + t[rch];
}

node query(int s, int l, int r, int ql, int qr)
{
	if (ql <= l && r <= qr) return t[s];
	if (qr <= mid) return query(lch, l, mid, ql, qr);
	else if (ql >= mid + 1) return query(rch, mid + 1, r, ql, qr);
	else return query(lch, l, mid, ql, qr) + query(rch, mid + 1, r, ql, qr);
}

int main()
{
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);

	n = gi(); q = gi();
	build(1, 1, n);

	int op, x, y;
	while (q--) {
		op = gi();
		if (op == 1) modify(1, 1, n, gi());
		else x = gi(), y = gi(), printf("%.10lf\n", query(1, 1, n, x, y).l);
	}
	
	return 0;
}
```

---

## 作者：resftlmuttmotw (赞：0)

## 题目链接

[CF712E Memory and Casinos](https://www.luogu.org/problem/CF712E)

## $Firstly$,前言

这道题是道假的黑题

~~一群学弟比我先A ，我真是太弱了~~

我们的思路都应该是来自于这位大佬的 [czpcf](https://www.luogu.org/space/show?uid=65771)

~~自我认为他们的公式都推得很草率~~

所以我才决定再 写一篇

## $Secondly$,思路

定义 $f(i,j)$ 为从赌场$i$出发 在赌场$i$赢 在赌场$j$赢并结束的概率

定义 $f(j + 1,k)$ 为从赌场$j$ ＋ 1出发 在赌场$j$ + 1赢 在赌场$k$赢并结束的概率

定义 $g(i,j)$ 与 $f$恰相反

那么 $f(i,k)$ = 直接走过去的概率（这里中间也可能转了圈 但没有过$j$） + 在中间转了圈且走过去的概率(中间的圈过了$j$)

直接走过去的概率 = $f(i,j) *f(j + 1,k)$

在中间转了圈且走过去的概率 = $f(i,j) *f(j + 1,k)$*$\displaystyle\sum^{+\infty}_{p=1}w^p$

其中$w$为在中间转一圈的概率

重点就是 $w$怎么算

$w$ = $(1-f(j+1,k))(1-g(i,j))$

这个式子是怎么得出的呢？

先理解$1-f(j+1,k)$

为从赌场$j$ ＋ 1出发 在赌场$j$ + 1赢 在赌场$k$赢并结束的概率

这里 $1-f(j+1,k)$ 

赌场$j$ ＋ 1出发是默认的 

条件只有
- **1**:在赌场$j$ + 1赢 

- **2**:在赌场$k$赢

两个中至少有一个不成立

但最后$1,2$造成的结果都是从右区间返回 （不管她在$[j + 1,k]$转多少圈）

## $Additionally$,化简


$$f(i,k)$$

$$= f(i,j) *f(j + 1,k)\displaystyle\sum^{+\infty}_{p=1}w^p$$

$$= f(i,j) *f(j + 1,k)\frac{1-w^{+\infty}}{1-w}$$

$$w^{+\infty} = 0$$

$$\Rightarrow= \frac{f(i,j) *f(j + 1,k)}{1-(1-f(j+1,k))(1-g(i,j))}$$


这下就可以用线段树维护了

## $Eventually$，$Code$

```cpp
#include <map>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define reg register int
#define isdigit(x) ('0' <= (x)&&(x) <= '9')
template<typename T>
inline T Read(T Type)
{
	T x = 0,f = 1;
	char a = getchar();
	while(!isdigit(a)) {if(a == '-') f = -1;a = getchar();}
	while(isdigit(a)) {x = (x << 1) + (x << 3) + (a ^ '0');a = getchar();}
	return x * f;
}
#define fi first
#define se second
typedef double db;
const int MAXN = 100010;
db p[MAXN];
struct node
{
	double g,f;
}tree[MAXN << 2];
inline void sum(db &f,db &g,db f1,db f2,db g1,db g2)
{
	f = f1 * f2 / (1 - (1 - f2) * (1 - g1));
	g = g1 * g2 / (1 - (1 - f2) * (1 - g1));
}
inline void BuildTree(int k,int l,int r)
{
	if(l == r)
	{
		tree[k].f = p[l],tree[k].g = 1 - p[l];
		return;
	}
	int mid = l + r >> 1;
	BuildTree(k << 1,l,mid);
	BuildTree(k << 1 | 1,mid + 1,r);
	sum(tree[k].f,tree[k].g,tree[k << 1].f,tree[k << 1 | 1].f,tree[k << 1].g,tree[k << 1 | 1].g);
}
inline pair<db,db> query(int k,int l,int r,int L,int R)
{
	if(L <= l&&r <= R) return make_pair(tree[k].f,tree[k].g);
	int mid = l + r >> 1;
	pair<db,db> k1,k2;k1.fi = k2.fi = k1.se = k2.se = 1;
	if(L <= mid) k1 = query(k << 1,l,mid,L,R);
	if(mid < R) k2 = query(k << 1 | 1,mid + 1,r,L,R);
	db T1,T2;
	sum(T1,T2,k1.fi,k2.fi,k1.se,k2.se);
	return make_pair(T1,T2);
}
inline void update(int k,int l,int r,int pos,db x)
{
	if(l == r)
	{
		tree[k].f = x,tree[k].g = 1 - x;
		return;
	}
	int mid = l + r >> 1;
	if(pos <= mid) update(k << 1,l,mid,pos,x);
	else update(k << 1 | 1,mid + 1,r,pos,x);
	sum(tree[k].f,tree[k].g,tree[k << 1].f,tree[k << 1 | 1].f,tree[k << 1].g,tree[k << 1 | 1].g);
}
int main()
{
	int n = Read(1),q = Read(1);
	for(reg i = 1;i <= n;i++)
	{
		int a = Read(1),b = Read(1);
		p[i] = (db)a / b;
	}
	BuildTree(1,1,n);
	while(q--)
	{
		int sit = Read(1);
		if(sit & 1)
		{
			int pos = Read(1),a = Read(1),b = Read(1);
			update(1,1,n,pos,((db)a / b));
		} else {
			int l = Read(1),r = Read(1);
			cout << query(1,1,n,l,r).fi << endl;
		}
	}
    return 0;
}
```






 

---

