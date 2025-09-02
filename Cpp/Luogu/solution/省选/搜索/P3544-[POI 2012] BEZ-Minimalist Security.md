# [POI 2012] BEZ-Minimalist Security

## 题目描述

**译自 POI 2012 Stage 3. Day 2「[Bezpieczeństwo minimalistyczne](https://szkopul.edu.pl/problemset/problem/aSbIC_LB4H-CGMYPEVue5jFw/site/?key=statement)」**

给定一张无向图，点有点权 $p(v)$，边有边权 $b(u,v)$，初始时保证对每条边有 $p(u) + p(v) \ge b(u,v)$。

现在需要减少一部分点的点权，使得对每条边都恰有 $p(u) + p(v) = b(u,v)$.

求整张图减少的点权和的最小值和最大值。

## 说明/提示

对于 $56\%$ 的数据有 $n \le 2000,m \le 8000$.

对于所有数据有 $1 \le n \le 500\ 000,0 \le m \le 3\ 000\ 000$.

翻译来自于 [LibreOJ](https://loj.ac/p/2702)。

## 样例 #1

### 输入

```
3 2
5 10 5
1 2 5
2 3 3```

### 输出

```
12 15```

# 题解

## 作者：i207M (赞：13)

给出一个N个顶点、M条边的无向图，边(u,v)有权值w(u,v)，顶点i也有权值p(i)，并且对于每条边(u,v)都满足p(u)+p(v)>=w(u,v)。

现在要将顶点i的权值减去z(i)，其中0<=z(i)<=p(i)。修改后设顶点i的权值p'(i)=p(i)-z(i)，对于每条边(u,v)都满足p'(u)+p'(v)=w(u,v)。求sum{z(i)}的最小值和最大值。

## 看到式子就自己动手推一推

我们可以得到这样的式子：$z(u)+z(v)=p(u)+p(v)-w(u,v)$，观察这样的式子，我们发现，只要确定联通块内的任意一点的权值，整个联通块每个点的权值就都确定了，而最终的答案一定与那个点的权值成正比，设那个点的权值为x，最终答案一定在x取到极值时最优；

我们可以通过BFS求出每个点的权值关于x的表达式，如果是一棵树那么很简单，但是对于图，我们要讨论一下：对于偶环，式子的符号一样，必须常数也一样；对于奇环，符号不一样，我们可以解出来这个x，这是唯一可能的x，代入验证；

如何求得x的极值：我们有若干个$ax+b>=0,ax+b<=p$的限制，解这个不等式组即可；

还有一种偷懒的办法：二分$l,r$，当x最小时，应该满足$x+b>=0,-x+b<=p$的限制；当x最大时，应该满足$x+b<=p,-x+b>=0$的限制；

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<vector>
#include<set>
#include<queue>
#include<map>
#include<cstring>
#include<string>
#include<bitset>
#include<iomanip>
using namespace std;
#define ri register int
#define il inline
#define pb push_back
#define LL long long
#define pairint pair<int,int>
#define fi first
#define se second
#define mp make_pair

namespace i207M
{

template<class T>il void in(T &x)
{
    x=0; bool f=0; char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-') f=1;
        c=getchar();
    }
    while(c>='0'&&c<='9') x=x*10+(c^'0'),c=getchar();
    if(f) x=-x;
}

#define N 500005
#define M 6000005
int n,m;
int vp[N];
int v[M],nx[M];
int w[M];
int head[N],cnte;
il void adde(int uu,int vv,int ww)
{
	v[++cnte]=vv,nx[cnte]=head[uu],head[uu]=cnte,w[cnte]=ww;
}
bool jud[N];
int vis[N],cur;
LL mxval,mnval;
il void gun()
{
	puts("NIE");
	exit(0);
}
struct Node
{
	LL a,b;
	Node(){ }
	Node(LL aa,LL bb)
	{
		a=aa,b=bb;
	}
	LL calc(LL x)
	{
		return a*x+b;
	}
	friend Node operator-(const Node &x,const Node &y)
	{
		return Node(x.a-y.a,x.b-y.b);
	}
};
int q[N],hd,tl;
Node zt[N];
LL zp[N];
LL calc(int st,LL dt)
{
	++cur;
	q[hd=tl=1]=st, vis[st]=cur;
	zp[st]=dt;
	LL res=0;
	while(hd<=tl)
	{
		int x=q[hd++];
		jud[x]=1;
		if(zp[x]<0||zp[x]>vp[x]) gun();
		res+=zp[x];
		for(ri i=head[x];i;i=nx[i])
		{
			LL tmp=vp[x]+vp[v[i]]-w[i]-zp[x];
			if(vis[v[i]]!=cur)
			{
				vis[v[i]]=cur,zp[v[i]]=tmp;
				q[++tl]=v[i];
			}
			else if(zp[v[i]]!=tmp) gun();
		}
	}
	return res;
}
int fa[N];
void solve(int st)
{
	++cur;
	q[hd=tl=1]=st, vis[st]=cur;
	zt[st]=Node(1,0);
	LL l=0,r=vp[st];
	while(hd<=tl)
	{
		int x=q[hd++];
		if(zt[x].a==1)
		{
			l=max(l,-zt[x].b);
			r=min(r,vp[x]-zt[x].b);
		}
		else 
		{
			l=max(l,zt[x].b-vp[x]);
			r=min(r,zt[x].b);
		}
		if(l>r) gun();
		for(ri i=head[x];i;i=nx[i])
			if(vis[v[i]]!=cur)
			{
				fa[v[i]]=x;
				vis[v[i]]=cur;
				zt[v[i]]=Node(0,vp[x]+vp[v[i]]-w[i])-zt[x];
				q[++tl]=v[i];
			}
			else if(v[i]!=fa[x])
			{
				Node t=Node(0,vp[x]+vp[v[i]]-w[i])-zt[x];
				if(zt[v[i]].a!=t.a)
				{
					LL tmp=(t.a==1?zt[v[i]].b-t.b:t.b-zt[v[i]].b);
					if(tmp%2==1) gun();
					else 
					{
						tmp=calc(st,tmp/2);
						mxval+=tmp,mnval+=tmp;
						return;
					}
				}
				else if(zt[v[i]].b!=t.b) gun();
			}
	}
	LL v1=calc(st,l),v2=calc(st,r);
	mxval+=max(v1,v2),mnval+=min(v1,v2);
}
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
//	freopen("out.out","w",stdout);
#endif
	in(n),in(m);
	for(ri i=1;i<=n;++i) in(vp[i]);
	for(ri i=1,a,b,c;i<=m;++i)
	{
		in(a),in(b),in(c);
		adde(a,b,c); adde(b,a,c);
	}
	for(ri i=1;i<=n;++i)
		if(!jud[i]) 
		{
			solve(i);
		}
	printf("%lld %lld\n",mnval,mxval);
    return 0;
}

}

int main()
{
    i207M::main();
    return 0;
}
```



---

## 作者：ywy_c_asm (赞：8)

~~话说这个神题居然没人写题解……~~

首先我们可以把题目的式子变一下，即对于一条边$(u,v,w)$，有：

$p_u-z_u+p_v-z_v=w$

$z_u+z_v=p_u+p_v-w$

那么我们就惊奇的发现每一条边都对应着一个组$z_u$与$z_v$之和，然后这个图就可以看做是$z$之间的约束关系。

然后我们很自然的就想到了差分约束，但是目前来看这玩意用差分约束是没法做的，我们要解决这么两个问题：①我们的约束关系并不是形如$x_i-y_i?k$的等式或者不等式，②答案要求的是**和**的最大值最小值而不是单个变量的。

先来考虑①如何解决，比如我们现在有这么3个点（为了便于说明下面的图上的边权并不是真的边权而是两个端点z的和）：

![](https://cdn.luogu.com.cn/upload/pic/40805.png)

然后就会有两个等式：

$a_1+a_2=k_{1,2}$

$a_2+a_3=k_{2,3}$

于是很自然的我们就会把它作个差：

$a_1-a_3=k_{1,2}-k_{2,3}$

于是我们就得到了可以用于差分约束的关系了，但是这样的话对于一个点要连所有跟他相连的点对那么多条边，不过我们发现这个用于差分约束的边权可以拆成两个分别只和$u$和$v$相关的部分，于是我们可以给中间点建立一个虚点然后就像这样连边：

![](https://cdn.luogu.com.cn/upload/pic/40808.png)

于是我们用于差分约束的图的规模就是$O(n+m)$级别的了。

然后考虑如何解决求和的问题，我们发现对于一个连通块里（要注意的是这图并不一定连通，所以我们可以分别把每个连通块的答案求出来相加），比如上面那个图，如果$z_1$知道了，我们就可以求出$z_2$（别忘了一条边代表一个$z$的和的等式），如果$z_2$知道了，我们就可以求出$z_3$，所以整个连通块的点的$z$是可以被任意一个点表示出来的，并且这是一个一次多项式，那么这个连通块的$\sum z_i$也可以被表示成关于任意一个点的一次多项式，假设我们取的点为$a$，那么$\sum z_i=kz_a+b$，显然这个$k$只会取到0、正数、负数~~这是废话~~，所以我们断言，当$\sum z_i$取最大或者最小的时候，$z_a$一定取最大或者最小，但不一定是最大时和最大或者最小时和最小，这个得根据$k$的符号而定。于是就可以直接跑差分约束了。

注意，不要以为无解的时候就等同于图上有正环或者负环，要知道在许多这样的题中无解的情况是很复杂的。这个图可能有环，我们在把所有点的一次多项式递推出来的时候要用$bfs$，在环上可能会出现前后递推不一致的矛盾的情况，我们需要把这个判为无解。

那么，这个题就做完了$……?$

其实我们还差最后一种情况没有考虑~~毕竟阴险的波兰人可不会让你这么轻松的切掉此题~~，我们先来看这题的第四个点的图的一个部分：

![](https://cdn.luogu.com.cn/upload/pic/40816.png)

然后我们从101开始$bfs$，然后我们走到173发现出事了，104的多项式已经求出来了是$-x+628$，173的多项式是$-x+113$，这条边对应$z_{104}+z_{173}=373$，按照173的推104的应该是$x+260$，就出现了矛盾于是我们认为他无解。但这个图实际上是有解的。

为什么会出现这种情况呢？很简单，因为出现了奇环。

显然按照我们这样的$bfs$递推，每个点的多项式的一次项系数不是1就是-1，并且边两边的一次项系数应该是相反数，这就相当于二分图染色——在没有奇环的情况下，但是出现奇环就代表着——我们可以把$x$直接解出来！那么这就不是矛盾了，这个“矛盾”的真正意义就是$x+260$与$-x+628$对于这个连通块都是成立的，所以$x=166$，在这种情况下我们需要注意解出来的$x$必须是非负整数，并且他能够使得这个连通块的所有约束条件都成立，否则是无解的。

好了，总结一下，这题我们需要对每个连通块分别求解，对于没有奇环的情况我们直接上差分约束通过和的关于随便一个点的一次多项式得出最值，有奇环需要我们直接解方程得出答案。然后这题就做完了。

其实细想一下这题好像是可以不用差分约束的……咱们都已经用一次函数把每个点表示出来了那么每个点都有一个范围然后就直接通过解不等式把$x$的最大值最小值解出来然后就做完了啊……~~翻了下评测记录和网上别的题解好像只有我用的是垃圾到不行的差分约束？~~

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define ll long long
#define abs(_o) ((_o<0)?-(_o):_o)
using namespace std;
inline int get() {//我的垃圾快读 
	int n=0;
	char c;
	while((c=getchar())||23333) {
		if(c>='0'&&c<='9')break;
		if(c=='-')goto s;
	}
	n=c-'0';
	while((c=getchar())||23333) {
		if(c>='0'&&c<='9')n=n*10+c-'0';
		else return(n);
	}
s:
	while((c=getchar())||23333) {
		if(c>='0'&&c<='9')n=n*10-c+'0';
		else return(n);
	}
}
typedef struct _b {//边 
	int dest;
	int nxt;
	int len;
} bian;
bian memchi[8000001];
int gn=2;
int heads[500001],fheads[1000001];//这两个是两个图的邻接表，前者为原图，后者为跑差分约束的图 
ll dis[1000001];//dis数组 
unsigned char bv[500001]；//用于跑spfa标记用的 
int que[3000001];//队列 
int n;
typedef struct _f {//把用于表示的一次多项式封装起来 
	ll k;
	ll b;
	friend _f operator -(const ll &a,const _f &b) {
		_f c;
		c.b=a-b.b;
		c.k=-b.k;
		return(c);
	} friend _f operator +(const _f &a,const _f &b) {
		_f c;
		c.k=a.k+b.k;
		c.b=a.b+b.b;
		return(c);
	} friend bool operator !=(const _f &a,const _f &b) {
		return(a.k!=b.k||a.b!=b.b);
	}
} f;
f val[500001];//每个点的一次多项式 
int xulie[500001];//把连通块内的点放到这个数组里 
int cnts[1000001];//跑spfa的时候记录距起点有几条边，当这个超过n的时候就出现负环（这个效率较高） 
inline void add(int s,int t,int l,int *hd) {
	memchi[gn].len=l;
	memchi[gn].dest=t;
	memchi[gn].nxt=hd[s];
	hd[s]=gn;
	gn++;
}
int ps[500001];
unsigned char sol[500001];//标记是否已经处理过该点 
int lims[500001];
int zs[500001];
void solve(int ltc,ll &mx,ll &mn) {//ltc为连通块任意一点，mx为最大答案，mn为最小答案用于输出 
	val[ltc].k=1;
	val[ltc].b=0;
	register int head=0,tail=1;
	que[0]=xulie[0]=ltc;
	sol[ltc]=1;
	ll x;
	unsigned char kejie=0;
	do {//bfs把一次多项式表示递推出来 
		int me=que[head];
		head++;
		for(register int i=heads[me]; i; i=memchi[i].nxt) {
			if(sol[memchi[i].dest]) {
				f cjr=(ps[me]+ps[memchi[i].dest]-memchi[i].len)-val[me];
				if(cjr!=val[memchi[i].dest]) {//发现矛盾 
					if(val[me].k==val[memchi[i].dest].k) {//奇环，解方程 
						ll gg=(ps[me]+ps[memchi[i].dest]-memchi[i].len)-val[me].b-val[memchi[i].dest].b;
						ll kk=val[me].k+val[memchi[i].dest].k;
						if(abs(gg)%abs(kk)!=0) {//不是整数无解 
							printf("NIE\n");
							exit(0);
						}
						x=gg/kk;
						if(x<0||x>ps[ltc]) {
							printf("NIE\n")； 
							exit(0);
						}
						kejie=1;
					} else {//没有奇环，真的是矛盾 
						if(val[me].b+val[memchi[i].dest].b!=(ps[me]+ps[memchi[i].dest]-memchi[i].len)) {
							printf("NIE\n");
							exit(0);
						}
					}
				}
				continue;
			}
			sol[memchi[i].dest]=1;
			que[tail]=xulie[tail]=memchi[i].dest;
			tail++;
			val[memchi[i].dest]=(ps[me]+ps[memchi[i].dest]-memchi[i].len)-val[me];
		}
	} while(head<tail);
	fheads[0]=0;
	int cnt=tail;
	f sig;
	sig.k=sig.b=0;
	if(kejie) {//如果可直接解方程的话，需要判断这个解是否合法 
		for(register int i=0; i<cnt; i++) {
			int me=xulie[i];
			ll dst=x*val[me].k+val[me].b;
			if(dst<0||dst>ps[me]) {
				printf("NlE\n");
				exit(0);
			}
			zs[me]=dst;
			sig=sig+val[me];
		}
		for(register int i=0; i<cnt; i++) {
			int me=xulie[i];
			for(register int j=heads[me]; j; j=memchi[j].nxt) {
				if(ps[me]-zs[me]+ps[memchi[j].dest]-zs[memchi[j].dest]!=memchi[j].len) {
					printf("NIE\n");
					exit(0);
				}
			}
		}
		mx=mn=x*sig.k+sig.b;
		return;
	}
	for(register int i=0; i<cnt; i++) {//差分约束建图（先跑最长路） 
		int me=xulie[i];
		for(register int j=heads[me]; j; j=memchi[j].nxt) {
			int w=ps[me]+ps[memchi[j].dest]-memchi[j].len;
			add(memchi[j].dest+n,me,w,fheads);
			add(me,memchi[j].dest+n,-w,fheads);
			lims[me]=max(lims[me],ps[me]-memchi[j].len);
		}
		sig=sig+val[me];
		add(0,me,lims[me],fheads);//注意这里的和0的连边是为最长路设计的，跑最短路的时候还要反过来 
		add(me,0,-ps[me],fheads);
		dis[me]=dis[me+n]=-123456789045678923;
	}
	dis[0]=0;
	head=0,tail=1;
	que[0]=0;
	cnts[0]=0;
	do {//最长路 
		int me=que[head];
		head++;
		bv[me]=0;
		for(register int i=fheads[me]; i; i=memchi[i].nxt) {
			if(dis[me]+memchi[i].len>dis[memchi[i].dest]) {
				dis[memchi[i].dest]=memchi[i].len+dis[me];
				cnts[memchi[i].dest]=cnts[me]+1;
				if(cnts[memchi[i].dest]>cnt) {//有正环 
					printf("NIE\n");
					exit(0);
				}
				if(!bv[memchi[i].dest]) {
					bv[memchi[i].dest]=1;
					que[tail]=memchi[i].dest;
					tail++;
				}
			}
		}
	} while(head<tail);
	int x1=dis[ltc];
	for(register int i=fheads[0]; i; i=memchi[i].nxt) {//把和0的连边反过来跑最短路 
		memchi[i].len=ps[memchi[i].dest];
		memchi[i^1].len=-lims[memchi[i].dest];
		dis[memchi[i].dest]=dis[memchi[i].dest+n]=0x7fffffffffffffff;
	}
	dis[0]=0;
	head=0;
	tail=1;
	que[0]=0;
	cnts[0]=0;
	do {
		int me=que[head];
		head++;
		bv[me]=0;
		for(register int i=fheads[me]; i; i=memchi[i].nxt) {
			if(dis[me]+memchi[i].len<dis[memchi[i].dest]) {
				dis[memchi[i].dest]=dis[me]+memchi[i].len;
				cnts[memchi[i].dest]=cnts[me]+1;
				if(cnts[memchi[i].dest]>cnt) {//负环 
					printf("NIE\n");
					exit(0);
				}
				if(!bv[memchi[i].dest]) {
					bv[memchi[i].dest]=1;
					que[tail]=memchi[i].dest;
					tail++;
				}
			}
		}
	} while(head<tail);
	int x2=dis[ltc];
	mx=max(x1*sig.k+sig.b,x2*sig.k+sig.b);//得出答案 
	mn=min(x1*sig.k+sig.b,x2*sig.k+sig.b);
}
int main() {
	n=get();
	int m=get();
	for(register int i=1; i<=n; i++)ps[i]=get();
	for(register int i=1; i<=m; i++) {
		int s=get(),t=get(),l=get();
		add(s,t,l,heads);
		add(t,s,l,heads);
	}
	ll mx=0,mn=0;
	for(register int i=1; i<=n; i++) {
		if(!sol[i]) {
			ll a,b;
			solve(i,a,b);//求解该连通块 
			mx+=a;
			mn+=b;
		}
	}
	printf("%lld %lld\n",mn,mx);
	return(0);
}
```

---

## 作者：Federico2903 (赞：3)

## 思路

显然一个连通块中只要确定一个点，所有的点都确定了。

不妨设某一个点的值为 $x$，不难发现每一个点的点值都能表示为 $kx + b$，并且 $k \in \{-1, 1\}$。

考虑当你遇到一个奇环的时候，会遇到一个点同时有 $k = 1$ 和 $k = -1$ 两个方程，直接求解然后求出整个连通块。

如果不存在奇环，那就把所有的方程加起来，一次函数全部加起来还是一个一次函数，不难求出 $x$ 的取值范围，$x$ 取极值则答案取到极值。

## AC 代码

```cpp
#include <bits/stdc++.h>

#define int ll

#define rep(i, a, b) for(int i = (a), i##end = (b); i <= i##end; i++)
#define _rep(i, a, b) for(int i = (a), i##end = (b); i >= i##end; i--)
#define ec first
#define fb second
#define dl make_pair
#define dk(...) make_tuple(__VA_ARGS__)
#define de(val) cerr << #val << " = " << (val) << endl

using namespace std;

typedef long long ll;
typedef __int128 i128;
typedef pair <int, int> pii;

int read() {
	int x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}

template <typename _Tp>
void print(_Tp x) {
	if (x < 0) putchar('-'), x = -x;
	static int sta[40];
	int top = 0;
	do sta[top++] = x % 10, x /= 10; while (x);
	while (top) putchar(sta[--top] + 48);
}

const int MAXN = 3e6 + 5;
int n, m, p[MAXN];
vector <pii> G[MAXN];
int k[MAXN], b[MAXN], a[MAXN];
int cer, maxl, minr;
bool flg = 0;
vector <int> pt;

void dfs(int u, int fa) {
	if (k[u] == 1) {
		maxl = max(maxl, -b[u]);
		minr = min(minr, p[u] - b[u]);
	}
	else {
		maxl = max(maxl, b[u] - p[u]);
		minr = min(minr, b[u]);
	}
	pt.push_back(u);
	for (auto [v, w] : G[u]) {
		if (v == fa) continue;
		if (k[v]) {
			if (k[v] == -k[u]) { if (b[v] != w - b[u]) exit((puts("NIE"), 0)); }
			else {
				int nb = b[u] + b[v] - w;
				int nk = -(k[u] + k[v]);
				if (nk * nb < 0) exit((puts("NIE"), 0));
				nb = abs(nb), nk = abs(nk);
				if (nb % nk) exit((puts("NIE"), 0));
				cer = nb / nk;
				flg = 1;
				return;
			}
			continue;
		}
		k[v] = -k[u];
		b[v] = w - b[u];
		dfs(v, u);
		if (flg) return;
	}
}

int ansmax, ansmin;

void solve(int u) {
	ansmax += p[u] - a[u];
	ansmin += p[u] - a[u];
	k[u] = 1;
	for (auto [v, w] : G[u]) {
		if (~a[v]) {
			if (a[v] != w - a[u]) exit((puts("NIE"), 0));
			continue;
		}
		a[v] = w - a[u];
		if (a[v] < 0 || a[v] > p[v]) exit((puts("NIE"), 0));
		solve(v);
	}
}

signed main() {
#ifndef LOCAL
#ifndef ONLINE_JUDGE
	freopen("add.in", "r", stdin);
	freopen("add.out", "w", stdout);
#endif
#endif
	memset(a, -1, sizeof a);
	n = read(), m = read();
	rep (i, 1, n) p[i] = read();
	rep (i, 1, m) {
		int u = read(), v = read(), w = read();
		G[u].push_back(dl(v, w));
		G[v].push_back(dl(u, w));
	}
	rep (i, 1, n) {
		if (k[i]) continue;
		k[i] = 1, b[i] = 0;
		cer = 0, flg = 0;
		maxl = 0, minr = 1e9;
		pt.clear();
		dfs(i, 0);
		if (flg) {
			a[i] = cer;
			if (cer < 0 || cer > p[i]) return puts("NIE"), 0;
			solve(i);
		}
		else {
			maxl = max(0ll, maxl);
			minr = min(minr, p[i]);
			if (maxl > minr) return puts("NIE"), 0;
			int fk = 0, fb = 0;
			for (auto v : pt) fk += -k[v], fb += p[v] - b[v];
			int pl = maxl * fk + fb;
			int pr = minr * fk + fb;
			ansmax += max(pl, pr);
			ansmin += min(pl, pr);
		}
	}
	print(ansmin), putchar(32), print(ansmax), puts("");
	return 0;
}
```

---

## 作者：Alex_Wei (赞：2)

> [P3544 [POI2012]BEZ-Minimalist Security](https://www.luogu.com.cn/problem/P3544)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

每个连通块独立，单独考虑。对于一个连通块 $G=(V,E)$，显然 $|E|\geq |V|-1$，故其自由度 $\leq 1$，即一旦钦定连通块内任何一个 $q_i=p_i-z_i$，则整个连通块确定。

不妨将连通块内的点编号为 $1\sim |V|$，考虑用 $q_1$ 表示 $q_2\sim p_{|V|}$。根据题目的限制 $q_u+q_v=w$，我们知道最后每个 $q_i$ 都能被写成 $k_iq_1+c_i$ 的形式，其中 $k_i=\pm 1$。因此，找到 $G$ 的任意一棵生成树，求出 $k_i$ 和 $c_i$。

与此同时，对于非树边 $(u,v,w)$，若 $k_u$ 与 $k_v$ 相同，说明我们能解出 $q_1$。此时可以判断无解：有两条非树边解得的 $q_1$ 不同，或 $q_1$ 不是整数（即 $2\nmid w-k_u-k_v$），或 $q_1$ 不在 $[0,p_1]$ 范围内。相反，若 $k_u$ 与 $k_v$ 不同，则需检查 $c_u+c_v=w$。上述操作可以一遍 `DFS` 完成。

接下来，若 $q_1$ 被钦定，那么 $q_i$ 也已经固定下来，检查每条边是否满足要求以及 $q_i$ 是否在 $[0,p_i]$ 范围内，判断无解。

否则，根据若干组 $0\leq k_iq_1+c_i\leq p_i$ 的不等式，我们可以解得 $q_1$ 的取值范围 $[l,r]$。我们知道 $q_i$ 的总和为 $\sum_{i=1}^{|V|}k_iq_1+c_i$，记 $K=\sum_{i=1}^{|V|}k_i$，$C=\sum{i=1}^{|V|}c_i$，$P=\sum_{i=1}^{|V|}p_i$，则代价为 $P-Kq_1C$。显然，该式的最小值与最大值在 $q_1$ 等于边界值时取到，分 $K\leq 0$ 和 $K>0$ 两种情况讨论一下即可。时间复杂度线性。

```cpp
#define wa puts("NIE"), exit(0)

const int N = 5e5 + 5;
const int M = 3e6 + 5;

int cnt, hd[N], nxt[M << 1], to[M << 1], val[M << 1];
void add(int u, int v, int w) {nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v, val[cnt] = w;}

int n, m, fix, anc, p[N], q[N], vis[N];
int top, stc[N], sgn[N], cons[N];
ll mn, mx;
void dfs(int id) {
	vis[id] = 1, stc[++top] = id;
	if(cons[id] > 1e6) wa;
	for(int i = hd[id]; i; i = nxt[i]) {
		int it = to[i];
		if(!vis[it]) sgn[it] = -sgn[id], cons[it] = val[i] - cons[id], dfs(it);
		if(sgn[id] == sgn[it]) {
			int res = val[i] - cons[id] - cons[it];
			if(res & 1) wa; res /= sgn[id] * 2;
			if(res < 0 || res > p[anc] || fix != -1 && fix != res) wa;
			fix = res;
		} else if(cons[id] + cons[it] != val[i]) wa;
	}
}

int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) p[i] = read();
	for(int i = 1, u, v, w; i <= m; i++) u = read(), v = read(), add(u, v, w = read()), add(v, u, w);
	for(int i = 1; i <= n; i++) if(!vis[i]) {
		top = 0, fix = -1, sgn[i] = 1, anc = i, dfs(i);
		if(fix != -1) {
			for(int j = 1, it = stc[1]; j <= top; it = stc[++j]) {
				q[it] = sgn[it] * fix + cons[it], mn += p[it] - q[it], mx += p[it] - q[it];
				if(q[it] < 0 || q[it] > p[it]) wa;
			} for(int j = 1, it = stc[1]; j <= top; it = stc[++j])
				for(int k = hd[it]; k; k = nxt[k])
					if(val[k] != q[it] + q[to[k]]) wa;
		} else {
			int l = 0, r = p[anc];
			for(int j = 1, it = stc[1]; j <= top; it = stc[++j]) {
				if(sgn[it] == 1) cmax(l, -cons[it]), cmin(r, p[it] - cons[it]);
				else cmax(l, cons[it] - p[it]), cmin(r, cons[it]);
			} if(l > r) wa;
			ll res = 0, tsign = 0;
			for(int j = 1, it = stc[1]; j <= top; it = stc[++j])
				res += p[it] - (l * sgn[it] + cons[it]), tsign -= sgn[it];
			if(tsign > 0) mx += res + 1ll * tsign * (r - l), mn += res;
			else mx += res, mn += res + 1ll * tsign * (r - l);
		}
	} cout << mn << " " << mx << endl;
	return flush(), 0;
}
```

---

## 作者：Resurgammm (赞：2)

upd : 修改了 $\LaTeX$

一道神题。

> 给定一张 $n$ 个点 $m$ 条边的无向图，每个点有点权，每条边有边权，满足点权和边权都非负，且每条边的权值小于等于两个顶点的权值和，现在要将每个点减一个数，满足非负且小于等于点权，使得每条边权等于两个顶点的点权和，问最大修改代价和最小修改代价。

设 $val_i$ 为点权，$z_i$ 为减去的代价，$w(u,v)$ 为边权，根据题意能列出来这个式子：

$$val_u-z_u+val_v-z_v=w(u,v)$$

将式子移项，有：

$$z_u+z_v=val_u+val_v-w(u,v)$$

等号右边这一串式子是个定值，所以只要确定了一个点 $i$ 的代价 $z_i$，那么和 $i$ 点在同一个连通块的点 $j$ 的代价 $z_j$ 都能确定，且都能用 $k_j\times z_i+b_j$ 来表示。

那么一个连通块的答案为 $z_i\times \sum\limits_{j=1}^{n}k_j+\sum\limits_{j=1}^{n}b_j$。

具体做法是将连通块内任意一点代价设为 $z$，然后 bfs 遍历整个连通块。

如果没有访问过当前点，那么就用 $z$ 来表示当前点的代价。

如果已经访问过当前点，那么联立解方程组，判断有解，无解和无数解。

* 无解：直接返回，输出 `NIE`。

* 有解：将 $z$ 求出，然后代回逐一验证是否可行。

* 无数解：因为限制了 $z_i\in[0,val_i]$，所以 bfs 后，联立来解一个不等式组求交集，然后取端点值代入求得最大值和最小值。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
#define int long long 
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout);
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(y,x,sizeof(x))
	
	const int maxn=5e5+5,maxm=3e6+5,inf=0x7fffffff;
	
	int n,m,ans1,ans2;
	int val[maxn];
	bool vis[maxn];
	vector<int> vec;
	namespace Graph{
		int head[maxn],id;
		struct e{int v,w,next;}edge[maxm<<1];
		inline void add(int u,int v,int w){
			edge[++id].v=v;
			edge[id].w=w;
			edge[id].next=head[u];
			head[u]=id;
		}
	}using namespace Graph;
	namespace ReDefine_Num{
		struct Segment{//无数解时求不等式交集用
			int l,r;
			Segment operator +(const Segment &x)const{
				return (Segment){max(l,x.l),min(r,x.r)};
			}
		};
		struct node{//用 kx+b 来表示每一个点的代价
			int k,b;
			inline int get(int x){return k*x+b;}
			inline Segment get_seg(int x)const{//解不等式用
				if(k>0) return (Segment){-b/k,(x-b)/k};
				if(k<0) return (Segment){(x-b)/k,-b/k};	
			}
			node operator +(const node &x)const{//重载加号减号
				return (node){k+x.k,b+x.b};
			}
			node operator -(const node &x)const{
				return (node){k-x.k,b-x.b};
			}
		}p[maxn];
		inline int check(node x,node y){//判断无解，无数解，返回有解时的系数
			if(x.k==y.k){
				if(x.b==y.b) return inf;
				else return -inf;
			}
			if((y.b-x.b)%(x.k-y.k)) return -inf;
			return (y.b-x.b)/(x.k-y.k);
		}
	}using namespace ReDefine_Num;
	inline int bfs(int s){
		int res=inf;
		queue<int> q;
		p[s]=(node){1,0}; 
		vis[s]=1; q.push(s); 
		vec.clear(); vec.push_back(s);
		while(!q.empty()){
			int u=q.front(); q.pop();
			for(int i=head[u];i;i=edge[i].next){
				int v=edge[i].v,w=edge[i].w;
				if(!vis[v]){//没有访问过直接表示
					vis[v]=1;
					p[v]=(node){0,w}-p[u];
					q.push(v); vec.push_back(v);
				}else{//已经访问过联立求解并回代
					int tmp=check((node){0,w}-p[u],p[v]);
					if(tmp!=inf){
						if(res!=inf && res!=tmp) return -inf;
						res=tmp;
					}
				}
			}
		}
		return res;
	}
	inline pair<int,int> solve(int x){
		if(x!=inf){//唯一解
			for(vector<int>::iterator it=vec.begin();it!=vec.end();it++){//不满足限制无解
				int u=*it;
				if(p[u].get(x)<0 || p[u].get(x)>val[u]) return make_pair(-inf,-inf); 
			}
			int res=0;
			for(vector<int>::iterator it=vec.begin();it!=vec.end();it++){
				int u=*it;
				res+=p[u].get(x);//将唯一解求出
			}
			return make_pair(res,res);
		}//无数解
		Segment res=(Segment){-inf,inf};
		for(vector<int>::iterator it=vec.begin();it!=vec.end();it++){
			int u=*it;
			res=res+p[u].get_seg(val[u]);//取交集
		}
		if(res.l>res.r) return make_pair(-inf,-inf);
		node now=(node){0,0};
		for(vector<int>::iterator it=vec.begin();it!=vec.end();it++){
			int u=*it;
			now=now+p[u];
		}//取端点值代入并返回
		return make_pair(min(now.get(res.l),now.get(res.r)),max(now.get(res.l),now.get(res.r)));
	}
	
	inline int main(){
		n=read(); m=read();
		for(int i=1;i<=n;i++) val[i]=read();
		for(int i=1;i<=m;i++){
			int x=read(),y=read(),z=read();
			add(x,y,val[x]+val[y]-z);
			add(y,x,val[x]+val[y]-z);
		}
		for(int i=1;i<=n;i++){
			if(vis[i]) continue;
			int tmp=bfs(i);
			if(tmp==-inf){puts("NIE"); exit(0);}
			else{
				pair<int,int> res=solve(tmp);	
				if(res.first==-inf){puts("NIE"); exit(0);}
				ans1+=res.first;
				ans2+=res.second; 
			}
		}
		printf("%lld %lld\n",ans1,ans2);
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：kkxacj (赞：1)

#### 前言

模拟赛中因为判无解判错了错一个点再次喜提 $0$ 分。

#### 思路

不难想到，对于一个联通块，确定一个点的值，这个联通块其它的点的值都确定了，当然无法确定就是无解。

考虑优化上诉过程，容易发现合法的取值一定是一段区间，我们想做到在 $i$ 最终值为 $0$ 时，最少加多少会合法，最多加多少会合法，我们二分图染色，与 $i$ 颜色一样的记为 $+1$，不一样的记为 $-1$，其和就是每次 $i$ 值增加会新增的值。

我们给每个点记录两个 $\verb!vector!$，分别表示一些会增加的量和一些会减少的量，举个例子，我们设 $b_i$ 为颜色，我们设根节点颜色为 $1$，在 $b_i = 1$ 时，与 $i$ 相邻的点 $j$ 边权为 $z$，$j$ 就会加入一个会减少的量 $z-a_i$，$b_i = 0$ 就加入一个会减的，可以理解为插入一条直线。

我们现在来考虑每个点会造成的影响，如果它又有斜率为正的直线又有斜率为负的直线，就看一下是否存在一个时刻，所有直线交于一点，没有就无解。

同时对于每一条直线，我们要找出它在那一段区间合法，然后更新左右端点，最后在求答案时，把无解判掉即可，详情可以看题解，有注释。

**code**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf1) + fread(buf1, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf1[1 << 23], *p1 = buf1, *p2 = buf1, ubuf[1 << 23], *u = ubuf;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 5e5+10,M = 3e6+10;
int n,m,a[N],head[N],d[N],v[N],v2[N],t[2],st[N],cnt,x,y,z,l,r,mid,ans,ans1,sum2,sum3,sum,sum1,mi,mx,op,op1,op2;
vector<int>v1[N],V1[N];
/*
v1:存储斜率为正的直线
V1:存储斜率为负的直线
t_i：颜色i出现几次
st:联通快出现的点 
*/ 
struct w1
{
	int to,nxt,z;
}b[M<<1];
inline void add(int x,int y,int z)
{
	b[++cnt].nxt = head[x];
	b[cnt].to = y,b[cnt].z = z;
	head[x] = cnt;
}
void dfs(int x,int y)
{
	v[x] = 1; v2[x] = !v2[y]; st[++cnt] = x; t[v2[x]]++; sum2 += d[x];
	for(int i = head[x];i;i = b[i].nxt)
	{
		if(!v[b[i].to]) d[b[i].to] = b[i].z-d[x],dfs(b[i].to,x);//dfs gen xin da an
		if(v2[x] == 1) v1[b[i].to].push_back(b[i].z-d[x]);//yi ge hui jian de shu
		else V1[b[i].to].push_back(b[i].z-d[x]);//yi ge hui jia de shu
	}
}
signed main()
{
//	freopen("add.in","r",stdin);
//	freopen("add.out","w",stdout);
	read(n),read(m);
	for(int i = 1;i <= n;i++) read(a[i]),sum3 += a[i];
	for(int i = 1;i <= m;i++) read(x),read(y),read(z),add(x,y,z),add(y,x,z); 
	for(int i = 1;i <= n;i++)
		if(!v[i])
		{
			d[i] = cnt = 0;
			mi = 1e16,mx = 0,op = -1e16; t[0] = t[1] = 0; sum2 = 0;
			V1[i].push_back(0); dfs(i,0);
			for(int j = 1;j <= cnt;j++) 
			{
				x = st[j];
				for(int z = 0;z < v1[x].size();z++) mx = max(mx,v1[x][z]-a[x]),mi = min(mi,v1[x][z]);//hui jian de
				for(int z = 0;z < V1[x].size();z++) mx = max(mx,-V1[x][z]),mi = min(mi,a[x]-V1[x][z]);//hui jia de
				if(v1[x].size() != 0 && V1[x].size() != 0)
				{
					op1 = -1e16;
					for(int z = 0;z < v1[x].size();z++)
					{
						if(op1 == -1e16) op1 = v1[x][z];
						else if(op1 != v1[x][z]){ op1 = -1e17; break; }
					}
					if(op1 == -1e17) { op == -1e17; break; }//1:多个斜率相同的直线且初值不一样，永不相交 
					op2 = -1e16;
					for(int z = 0;z < V1[x].size();z++)
					{
						if(op2 == -1e16) op2 = V1[x][z];
						else if(op2 != V1[x][z]){ op2 = -1e17; break; }
					}//同上 || 两个无法某一刻相同 || 上升的初值比下降的初值大，不相交 
					if(op2 == -1e17 || (op1-op2)%2==1 || op2 > op1) { op = -1e17; break; }
					if(op == -1e16 || op == (op1-op2)/2) op = (op1-op2)/2;
					else { op == -1e17; break; }//2:多个必须选的点，无解 
				}
			}//mx,op,mi
			if(op == -1e17) { printf("NIE"); return 0; } 
			if(mx > mi) { printf("NIE"); return 0; }//3:左端点大于右端点，无解 
			if(op != -1e16 && (mx > op || op > mi)) { printf("NIE"); return 0; }//4:必须选的点不在区间里面，无解 
			if(op != -1e16) ans = ans1 = op*(t[1]-t[0])+sum2;//选取的点确定了 
			else ans = mi*(t[1]-t[0])+sum2,ans1 = mx*(t[1]-t[0])+sum2;//最大值和最小值一定是两个端点，哪个最大哪个最小不重要，加的时候取min,max就好了 
			sum += max(ans,ans1),sum1 += min(ans,ans1);
		}
	print(sum3-sum),pc(' '),print(sum3-sum1),pc('\n');
	flush();
	return 0;
}
```

---

## 作者：Composite_Function (赞：1)

0.5h 秒了。/oh

---

首先做一步转化，把点权和约束换成要删去的点权和约束。考虑对于每一个连通分支单独处理。考虑一颗搜索树，能根据这棵树的约束得到这个连通分支中所有点要减去的点权关于其中一个点的值。

有点抽象。具体一点，其中钦定一个点的要减去的点权，假设为 $u$ 要删去的 $x$，那么根据所有连着这个点的边，假设 $(u,v,w)$ 表示 $u$ 要删去的点权和 $v$ 要删去的点权和为 $w$，那么这指出 $v$ 要删去的点权是 $-x+w$。

那么根据一颗搜索树，可以得到所有在 $u$ 点所在的连通分支中的点 $v$ 可以表示为 $\pm x+q_v$。然后把这些值加起来可以得到该连通分支的要删去的点权和，其本质是一个关于 $x$ 的一次函数。那么我们只用考虑 $x$ 的上下界和是否有解。

注意到还有很多非树边没处理，这对应了很多线性方程。这约束了 $x$ 的范围。同时还有每个点删去的不能超过每个点本身的权值。以上就是全部约束。

---

```cpp
const int N = 5e5 + 10, M = 6e6 + 10;
const ll inf = LLONG_MAX;
int n, m, p[N];
int ver[M], cst[M], hd[N], nxt[M], nE;
ll a[N], b[N], lx, rx, sa, sb, mn, mx;
bool vis[N], flag = true;
inline void add(int u, int v, int w) {
	ver[++nE] = v;
	cst[nE] = w;
	nxt[nE] = hd[u];
	hd[u] = nE;
}
void dfs(int u) {
	sa += a[u], sb += b[u];
	vis[u] = true;
	if (a[u] == 1) {
		lx = max(lx, -b[u]);
		rx = min(rx, p[u] - b[u]);
	} else {
		lx = max(lx, b[u] - p[u]);
		rx = min(rx, b[u]);
	}
	for (int e = hd[u]; ~e; e = nxt[e]) {
		int v = ver[e], w = cst[e];
		if (vis[v] == false) {
			a[v] = -a[u];
			b[v] = w - b[u];
			dfs(v);
		} else {
			if (a[v] + a[u] == 0) {
				if (b[v] + b[u] != w) flag = false;
			} else {
				if ((b[v] + b[u] - w) & 1) flag = false;
				else {
					ll x = -(b[v] + b[u] - w) / (a[v] + a[u]);
					lx = max(lx, x);
					rx = min(rx, x);
				}
			}
		}
	}
}
signed main() {
	rin >> n >> m;
	for (int i = 1; i <= n; ++i) rin >> p[i];
	memset(hd, -1, sizeof(hd));
	for (int i = 1, u, v, w; i <= m; ++i) {
		rin >> u >> v >> w;
		add(u, v, p[u] + p[v] - w);
		add(v, u, p[u] + p[v] - w);
	}
	for (int i = 1; i <= n; ++i)
		if (vis[i] == false) {
			a[i] = 1, b[i] = 0;
			lx = 0, rx = inf;
			sa = sb = 0;
			dfs(i);
			if (lx > rx) flag = false;
			if (sa >= 0) {
				mn += sa * lx + sb;
				mx += sa * rx + sb;
			} else {
				mn += sa * rx + sb;
				mx += sa * lx + sb;
			}
		}
	if (flag == false) cout << "NIE" << endl;
	else cout << mn << " " << mx << endl;
	return 0;
}
```

---

## 作者：Suffix_Sum (赞：1)

原题翻译不太严谨，$p_i$ 原意指警察人数，所以只能降到非负整数。

显然每一个联通块之间完全独立，所以我们不妨只讨论一个联通块的情况。

先把联通块的任一生成树拿出来，任选一点当根，设根最后的权值为 $x$，那么根据树边的关系我们会发现任意点 $u$ 都可以表示成 $x+a_u$ 或 $-x+a_u$。

我们再考虑其他树边，如果一个树边同时连接 $x$ 正负号相同的两点，我们直接可以解出 $x$ 的大小，直接再遍历一遍整个联通块看能否满足条件，其余边需要判断是否能满足边的条件，最后每一个点 $u$ 都有点值 $x+a_u$ 或 $-x+a_u$，那么每一个点对应的限制即为 $0 \le x+a_u \le p_u$ 或 $0 \le -x+a_u \le p_u$，我们可以解出 $x$ 的一个上界下界，因为答案是一个一次函数，所以在 $x$ 取最值时答案也取最值，对每一个联通块计算答案取和即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int p[500005];
vector<pair<int,int> >adj[500005];
int vis[500005];//1:x+a 2:-x+a
int a[500005];
int ans[500005][2];
long long anss[2];
int flag=0;
long long ans1=0,ans2=0;
void dfss(int x,int fl)
{
	if(ans[x][fl]>p[x])
	{
		flag=-1;
		return;
	}
	if(ans[x][fl]<0)
	{
		flag=-1;
		return;
	}
	anss[fl]+=p[x]-ans[x][fl];
	//cout<<"~~"<<x<<" "<<fl<<" "<<anss[fl]<<endl;
	for(auto xx:adj[x])
	{
		if(ans[xx.first][fl]!=0x3f3f3f3f)
		{
			if(ans[xx.first][fl]!=xx.second-ans[x][fl])
			{
				flag=-1;
				//cout<<"~~"<<endl;
				return;
			}
		}
		else
		{
			ans[xx.first][fl]=xx.second-ans[x][fl];
			dfss(xx.first,fl);
			if(flag==-1)
				return;
		}
	}
}
int ll,rr;
void dfs(int x,int key)
{
	if(vis[x]==1)//0<=x+a<=p[x]
	{
		rr=min(rr,p[x]-a[x]);
		ll=max(ll,-a[x]);
	}
	else//0<=-x+a<=p[x]
	{
		ll=max(ll,a[x]-p[x]);
		rr=min(rr,a[x]);
	}
	//cout<<"::"<<x<<" "<<vis[x]<<" "<<a[x]<<endl;
	for(auto xx:adj[x])
	{
		if(vis[xx.first]!=0)
		{
			if(vis[xx.first]==vis[x])
			{
				if(flag==-1)
					return;
				if(flag==1)
					continue;
				flag=1;
				//cout<<"!!"<<key<<endl;
				//cout<<"!!"<<(xx.second-a[x]-a[xx.first])<<endl;
				if((xx.second-a[x]-a[xx.first])%2!=0)
				{
					//cout<<"~~"<<endl;
					flag=-1;
					//cout<<"!!"<<flag<<endl;
					return;
				}
				if(vis[x]==1)
					ans[key][0]=(xx.second-a[x]-a[xx.first])/2;
				else
					ans[key][0]=(xx.second-a[x]-a[xx.first])/-2;
				dfss(key,0);
				ans1+=anss[0];
				ans2+=anss[0];
				if(flag==-1)
					return;
			}
			else
				if(a[xx.first]!=xx.second-a[x])
				{
					//cout<<"^"<<endl;
					flag=-1;
					return;
				}
		}
		else
		{
			vis[xx.first]=3-vis[x];
			a[xx.first]=xx.second-a[x];
			dfs(xx.first,key);
		}
		if(flag==-1)
			return;
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	memset(ans,0x3f,sizeof(ans));
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>p[i];
	int s,t,w;
	for(int i=1;i<=m;i++)
	{
		cin>>s>>t>>w;
		adj[s].push_back(make_pair(t,w));
		adj[t].push_back(make_pair(s,w));
	}
	for(int i=1;i<=n;i++)
	{
		if(vis[i]==0)
		{
			//cout<<"!!"<<i<<endl;
			vis[i]=1;
			a[i]=0;
			anss[0]=0;
			anss[1]=0;
			ll=-0x3f3f3f3f;
			rr=0x3f3f3f3f;
			flag=0;
			dfs(i,i);
			//cout<<"^^"<<flag<<endl;
			//cout<<ll<<" "<<rr<<endl;
			if(flag==-1)
			{
				cout<<"NIE"<<endl;
				//cout<<"!!"<<endl;
				return 0;
			}
			if(flag==1)
				continue;	
			if(ll>rr)
			{
				cout<<"NIE"<<endl;
				return 0;
			}
			ans[i][0]=ll;
			dfss(i,0);
			ans[i][1]=rr;
			dfss(i,1);
			if(flag==-1)
			{
				cout<<"NIE"<<endl;
				return 0;
			}
			ans1+=min(anss[0],anss[1]);
			ans2+=max(anss[0],anss[1]);
		//	cout<<ans1<<" "<<ans2<<endl;
			
		}
	}
	cout<<ans1<<" "<<ans2<<endl;
	return 0;
}
```

---

## 作者：ZH_qaq (赞：1)

## P3544 [POI2012]BEZ-Minimalist Security 的题解
#### [题目传送门](https://www.luogu.com.cn/problem/P3544)
### 思路
化下题面给的式子：$z(u)+z(v)=p(u)+p(v)-b(u,v)$

发现 $p(u)+p(v)-b(u,v)$ 是确定的，所以只要确定了一个点 $i$ 的权值 $x(i)$，和它在同一个联通块的所有点 $j$ 的权值 $x(j)$ 都确定下来了，并且那些点的权值都可以用 $k_jz_i+b_j(k_j\in \{-1,1\})$ 来表示。因此一个联通块的答案 $ans$ 为：$z_i\Sigma {k_j}+\sum{b_j}$

然后因为限制了 $0\le z_j \le p_j$，所以把所有 $x(j)$ 用 $x(i)$ 表示出来可以得到一个不等式组。解出来 $z(i)$ 的极值可以对应到 $ans$ 的极值了。
### 代码
```cpp
#include<bits/stdc++.h>
#define endl "\n"
#define mem(vis, num) memset(vis, num, sizeof(vis));
#define map mapp
using namespace std;
typedef long long ll;
int p[500005], b[500005], k[500005], cnt = 0, head[500005], mn, mx;
bool vis[500005];
ll ans1 = 0, ans2 = 0, K, B;
struct ed {
    int v, w, nxt;
}e[1000005];
void add(int u, int v, int w) {
    e[++ cnt] = (ed){v, w, head[u]}, head[u] = cnt;
    e[++ cnt] = (ed){u, w, head[v]}, head[v] = cnt; 
}
void dfs(int u, int fa) {
    if(k[u] < 0) {
    	mn = max(mn, b[u] - p[u]);
		mx = min(mx, b[u]);
	}
    else {
    	mn = max(-b[u], mn);
		mx = min(p[u] - b[u], mx);
	}	
    K += 1ll * k[u];
	B += 1ll * b[u];
    if(mn > mx) {
        cout << "NIE" << endl;
        exit(0);
	}
    for(int i = head[u]; i; i = e[i].nxt) {
        int to = e[i].v, wi = e[i].w;
        if(to != fa) {
            int tmp = wi - b[u];
            if(vis[to]) {
                if(k[to] != k[u] && tmp != b[to]) {
                    cout << "NIE" << endl;
                    exit(0);
                }
				else {
                    if(k[to] == k[u]) {
                        if((b[to] - tmp) % (-2 * k[u]) != 0) {
                            cout << "NIE" << endl;
                            exit(0);                            
                        } 
                        mn = max(mn, (b[to] - tmp) / (-2 * k[u]));
                        mx = min(mx, (b[to] - tmp) / (-2 * k[u]));
                        if(mn > mx) {
                            cout << "NIE" << endl;
                            exit(0);        
                        }
                    }
                }
            } 
			else {
                vis[to] = 1;
                k[to] = -k[u];
                b[to] = tmp;
                dfs(to, u);
            }
        }
    }
}
int main() {
	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	int n, m, u, v, w;
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) cin >> p[i];
    for(int i = 1; i <= m; i ++) {
        cin >> u >> v >> w;
        add(u, v, p[u] + p[v] - w);
    }
    for(int i = 1; i <= n; i ++) {
        if(!vis[i]) {
            vis[i] = 1;
            K = B = 0;
            k[i] = 1, b[i] = 0;
            mx = 100000000, mn = -100000000;
            dfs(i, 0);
            ans1 += min(1ll * mn * K + B, 1ll * mx * K + B);
            ans2 += max(1ll * mn * K + B, 1ll * mx * K + B);
        }
    }   
    cout << ans1 << " " << ans2;
	return 0;
}
```

---

## 作者：Code_星云 (赞：1)

先将式子化为 $z(u) + z(v) =w(u,v)-p(u)-p(v)$。然后发现对于不同的连通块贡献是独立的。考虑如何做一个连通块。

我们先钦定联通块内任意一个点 $x$，使其 $z(x)=t$。然后可以发现，连通块内任意一个点 $i$ 都能被表示为 $k_it+c_i$ 的形式，其中 $k_i=1$ 或 $-1$。这是因为每条边其实是一个二元的方程，知道了一个一定能推出另外一个。因此我们找出连通块的一个 DFS 树并求出每个结点的 $k_i$ 和 $c_i$。此时考虑非树边。容易发现非树边 $(u,v)$ 可能有以下几种情况：

1. $k_u+k_v=0$，此时若 $c_u+c_v=w(u,v)$，则解不受限制，否则无解。
2. $k_u=-k_v$，那么令 $k_ut+c_u+k_vt+c_t=w(u,v)$，可以解出 $t$。在这种情况下，若有多条非树边解出的 $t$ 不一样，则也无解。另外，由于 $k_i=1$ 或 $-1$，则若 $t$ 为整数，则必有 $w(u,v)-c_u-c_t$ 为偶数。

然后其实还有限制。对于连通块的一个权值为 $p_u$ 的点，令其 $z(u)=k_ut+c_u$，必须要满足 $0 \le z(u)\le \min(p_u,l_u)$。其中 $l_u$ 表示与 $u$ 相连的边的边权的最小值。那么我们就可以利用这些不等式求出 $t$ 的取值范围 $[l,r]$。

接下来考虑如何求极值。对于一个联通块 $D$，其答案为 $\sum_{i\in D}^{}{k_i}t+\sum_{i \in D}c_i$，其极值一定在 $t=l$ 或 $r$ 时取到。那么最大值最小值也就可以求得了。

```cpp
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <utility>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
#define pb push_back
#define px first
#define py second

const int N = 500005;
const int M = 3000005;
const int inf = 1e8;
struct edges{int to, next, w;}; edges edge[M << 1];
int n, m, cnt, tmpans; ll minn, maxn; vector<int> v;
int p[N], head[N], lim[N]; bool vis[N]; pii sol[N];
void chmin(int &x, int y){x = min(x, y);}
void chmax(int &x, int y){x = max(x, y);}

void add_edge(int u, int v, int w){
	edge[++ cnt].to = v; edge[cnt].next = head[u]; edge[cnt].w = w; head[u] = cnt;
}
void dfs(int u, int fa){
	vis[u] = true; v.pb(u);
	for(int i = head[u]; ~ i; i = edge[i].next){
		int v = edge[i].to, w = edge[i].w;
		if(v == fa) continue;
		if(! vis[v]){
			sol[v].px = - sol[u].px;
			sol[v].py = w - sol[u].py;
		    dfs(v, u);
		}else{
			if(sol[u].px == - sol[v].px){
				int tmp = sol[u].py + sol[v].py;
				if(tmp != w){puts("NIE"); exit(0);}
			}else{
				if(sol[u].px == 1){
					if((w - (sol[u].py + sol[v].py)) % 2 == 1){puts("NIE"); exit(0);}
					if(tmpans != inf){if(tmpans != (w - (sol[u].py + sol[v].py)) / 2){puts("NIE"); exit(0);}}
					else tmpans = (w - (sol[u].py + sol[v].py)) / 2;
				}else{
					if(((sol[u].py + sol[v].py) - w) % 2 == 1){puts("NIE"); exit(0);}
					if(tmpans != inf){if(tmpans != ((sol[u].py + sol[v].py) - w) / 2){puts("NIE"); exit(0);}}
					else tmpans = ((sol[u].py + sol[v].py) - w) / 2;
				}
			}
		}
	}
}
bool inseg(int x, int l, int r){if(x < l | x > r) return false; return true;}
int main(){
	scanf("%d %d", &n, &m); memset(head, -1, sizeof head); memset(lim, 0x3f, sizeof lim);
	for(int i = 1; i <= n; i ++) scanf("%d", &p[i]), lim[i] = p[i];
	for(int i = 1; i <= m; i ++){
		int u, v, w; scanf("%d %d %d", &u, &v, &w);
		w = p[u] + p[v] - w; add_edge(u, v, w); add_edge(v, u, w);
	}
	for(int u = 1; u <= n; u ++) for(int i = head[u]; ~ i; i = edge[i].next) chmin(lim[u], edge[i].w);
	for(int i = 1; i <= n; i ++) if(! vis[i]){
		sol[i] = {1, 0}; tmpans = inf; v.clear(); dfs(i, 0);
		ll k = 0, b = 0; int l = 0, r = inf;
		for(auto u: v){
			k += 1ll * sol[u].px; b += 1ll * sol[u].py;
			if(sol[u].px == 1) chmin(r, lim[u] - sol[u].py);
			else{chmin(r, sol[u].py); chmax(l, sol[u].py - lim[u]);}
		}
		if(l > r){puts("NIE"); exit(0);}
		if(tmpans != inf){
		    if(inseg(tmpans, l, r)){minn += k * tmpans + b; maxn += k * tmpans + b;} 
			else{puts("NIE"); exit(0);}
		}else{
		    ll tmax, tmin; tmax = max(k * l + b, k * r + b); tmin = min(k * l + b, k * r + b);
		    maxn += tmax; minn += tmin;
		}
	}
	printf("%lld %lld\n", minn, maxn); return 0;
}
```


---

## 作者：Jerrywang09 (赞：1)

## 解析

性质图论题。前置知识：初一数学。

### Part 1 连通块递推

变形 $p(u)-z(u)+p(v)-z(v)=b(u,v)$，
得 $z(v)=p(u)+p(v)-b(u,v)-z(u)$。
实际代码实现中可以将 $p(u)+p(v)-b(u,v)$ 当作边权 $w(u,v)$ 存储，$z(v)=-z(u)+w(u,v)$。

这意味着什么？如果一个连通块内有一个点的 $z$ 值确定了，整个连通块的 $z$ 要么都能确定，要么发现不合法！

再回头看刚才的式子。假设连通块中一个点的 $z$ 值为 $x$， 其它点的 $z$ 值可以表示为 $kx+b$ 的形式。$k\in\{-1, 1\}$，$b$ 代表 $w(u,v)$。

### Part 2 解出 $x$？

假如要去搜索 $v$，发现其已经走过了，那么，其 $z$ 值理应是惟一的。联立其之前推出的表示和将要推出的表示，可以得到方程：
$$
nk\cdot x+nb=ok\cdot x+ob
$$

其中，$\texttt{n}$ 取 $\texttt{new}$ 之意，$\texttt{o}$ 取 $\texttt{original}$ 之意。

解得：
$$
x=\frac{ob-nb}{nk-ok}
$$

有哪些情况是不合法的呢？

1. 无解。也就是 $nk=ok, ob\ne nb$。
2. $x$ 非整数。可以直接取余判断。

特判一下恒等式的情况。

### Part 3 确定上下界

对于每个点 $u$，都有不等式 $0\le kx+b\le p(u)$。对 $k\in\{-1, 1\}$ 分类讨论，可以求得 $x$ 的上下界 $mx,mn$。

对于多个这样的不等式组成的不等式组，$mx$ 取 $\min$，$mn$ 取 $\max$，就能得到不等式组解集。任何时候出现 $mn>mx$，就可以直接判不合法。

如何处理 Part 2 中 $x$ 的确切解呢？假设解得 $x=y$，写成不等式的形式就是 $y\le x\le y$，可以继续按照解不等式组的方法做。

### Part 4 统计答案

对于每个连通块，累加所有的 $k$ 和 $b$，就是连通块答案。

坑点是，可能 $k$ 的累计 $K$ 为负数，此时全局 `Max+=K*mn+B`。

需要开 long long。

## 代码

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, s, t) for(int i=(s); i<=(t); ++i)
#define F first
#define S second
#define pii pair<int, int>
#define int long long
#define all(x) x.begin(), x.end()
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=500010, inf=1e18;
using namespace std;

struct node
{
	int u, w;
};
vector<node> a[N];
struct formula
{
	int k, b;
} f[N];
int p[N];
bool vis[N];
int n, m;
int mn, mx;
int K, B;

#define fail puts("NIE"), exit(0);
void dfs(int u, int fa)
{
	int k=f[u].k, b=f[u].b;
	K+=k, B+=b;												// 统计一整个连通块的答案
	if(k>0) mn=max(mn, -b), mx=min(mx, p[u]-b);				// 解不等式组的上下界
	else mn=max(mn, b-p[u]), mx=min(mx, b);
	if(mn>mx) fail
	for(auto t:a[u])
	{
		int v=t.u, w=t.w;
		if(v==fa) continue;
		int nk=-k, nb=w-b;
		if(vis[v])
		{
			int ok=f[v].k, ob=f[v].b;
			if(ok==nk && nb!=ob) fail						// 新旧式建立方程，无解
			if(ok!=nk)										// 不是恒等式
			{
				if((ob-nb)%(nk-ok)!=0) fail					// 解不是整数
				int x=(ob-nb)/(nk-ok);
				mx=min(mx, x), mn=max(mn, x);
				if(mn>mx) fail
			}
		}
		else
		{
			f[v].k=nk, f[v].b=nb;
			vis[v]=1, dfs(v, u);
		}
	}
}

signed main()
{
	scanf("%lld%lld", &n, &m);
	rep(i, 1, n) scanf("%lld", p+i);
	rep(i, 1, m)
	{
		int u, v, w; scanf("%lld%lld%lld", &u, &v, &w);
		a[u].pb({v, p[u]+p[v]-w}), a[v].pb({u, p[u]+p[v]-w});
	}
	int Min=0, Max=0;
	rep(i, 1, n) if(!vis[i])
	{
		K=0, B=0;
		mn=-inf, mx=inf;
		f[i].k=1, f[i].b=0;
		vis[i]=1, dfs(i, 0);
		if(K>0) Min+=K*mn+B, Max+=K*mx+B;					// 对K的正负性分类讨论
		else Max+=K*mn+B, Min+=K*mx+B;
	}
	printf("%lld %lld", Min, Max);
	
	return 0;
}
```

---

## 作者：modfisher (赞：0)

## 思路
容易发现，当某个点的值确定后，只要解是存在的，其余所有与之连通的点的值都会被确定。

提出结论：当某个连通块中存在奇环时，这个连通块的解要么不存在，要么唯一。证明是容易的，设这 $m$ 个点的值为 $v_1,v_2,\dots,v_m$，则有如下限制：

$$\begin{cases}v_1+v_2=b_1\\v_2+v_3=b_2\\\dots\\v_m+v_1=b_m\end{cases}$$

这是一个 $m$ 元一次方程组，可以证明这 $m$ 个方程互不等价，故可以解出。若解不是非负整数，则无解。

顺便一提，之所以限定为奇环，是因为如果 $m$ 为偶数，那么有：

$$(v_1+v_2)-(v_2+v_3)+(v_3+v_4)-\dots+(v_{m-1}+v_m)=v_m+v_1$$

故由前 $m-1$ 项，可推出 $v_n+v_1=\sum_{i=1}^{m-1}b_i$，只有 $m-1$ 个方程是独立的，所以没有唯一解。

于是我们得出一种做法：直接钦定某个点 $r$ 的值为 $v_r=0$，然后 DFS 一棵生成树，确定每个点的值，之后寻找是否有奇环，有的话就反过来确定 $v_r$；否则，若这些值不互相矛盾，考虑到如果将 $v_r$ 加上 $1$，那么对于生成树上到 $r$ 距离为奇数的点 $x$，$v_x$ 应减去 $1$，而距离为偶数的应加上 $1$。于是可以将每个点的值 $v_x$ 用 $v_r$ 表示，列出不等式即可得到 $v_r$ 的范围，通过该范围确定减去的值的范围即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 5e5 + 5, maxm = 3e6 + 5;
const ll INF = (ll)1e18;

ll p[maxn], v[maxn], vl[maxn], vr[maxn];
int vis[maxn], dep[maxn];
int head[maxn], nxt[maxm << 1], to[maxm << 1], cnt = 0;
ll ww[maxm << 1];

void match(int u, int v, ll w){
    nxt[++ cnt] = head[u], to[cnt] = v, ww[cnt] = w, head[u] = cnt;
}
ll dfs(int x, int f){
    dep[x] = dep[f] + 1, vis[x] = 1;
    for(int i = head[x]; i; i = nxt[i]){
        int j = to[i];
        if(vis[j]){
            if(j == f) continue;
            if(v[x] + v[j] == ww[i]) return -INF;
            else{
                if((dep[x] ^ dep[j]) & 1) return INF;
                else{
                    if((v[x] + v[j] + ww[i]) & 1) return INF;
                    else return (dep[x] & 1) ? (ww[i] - v[x] - v[j]) / 2 : (v[x] + v[j] - ww[i]) / 2;
                }
            }
        }
        v[j] = ww[i] - v[x];
        ll res = dfs(j, x);
        if(res != -INF) return res;
    }
    return -INF;
}
int vis2[maxn], ps[maxn], pnt = 0;
void check(int x){
    vis2[x] = 1;
    ps[++ pnt] = x;
    for(int i = head[x]; i; i = nxt[i]){
        int j = to[i];
        if(vis2[j]) continue;
        v[j] = ww[i] - v[x];
        check(j);
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i ++) scanf("%lld", &p[i]);
    for(int i = 1; i <= m; i ++){
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        match(u, v, w), match(v, u, w);
    }
    ll ansl = 0, ansr = 0;
    for(int i = 1; i <= n; i ++){
        if(!vis[i]){
            ll res = dfs(i, 0);
            if(res == INF){
                printf("NIE\n");
                return 0;
            }else if(res == -INF){
                check(i);
                ll L = -INF, R = INF;
                for(int j = 1; j <= pnt; j ++){
                    int x = ps[j];
                    if(dep[x] & 1) L = max(L, 0 - v[x]), R = min(R, p[x] - v[x]);
                    else L = max(L, v[x] - p[x]), R = min(R, v[x] - 0);
                }
                if(L > R){
                    printf("NIE\n");
                    return 0;
                }
                ll resl = 0, resr = 0;
                while(pnt){
                    int x = ps[pnt --];
                    if(dep[x] & 1) resl += p[x] - (v[x] + L), resr += p[x] - (v[x] + R);
                    else resl += p[x] - (v[x] - L), resr += p[x] - (v[x] - R);
                }
                ansl += min(resl, resr), ansr += max(resl, resr);
            }else{
                v[i] = res;
                check(i);
                while(pnt){
                    int x = ps[pnt --];
                    vis[x] = 1;
                    if(v[x] < 0 || v[x] > p[x]){
                        printf("NIE\n");
                        return 0;
                    }
                    ansl += p[x] - v[x], ansr += p[x] - v[x];
                    for(int j = head[x]; j; j = nxt[j]){
                        int k = to[j];
                        if(v[x] + v[k] != ww[j]){
                            printf("NIE\n");
                            return 0;
                        }
                    }
                }
            }
        }
    }
    printf("%lld %lld\n", ansl, ansr);
    return 0;
}
```

---

## 作者：zero_range (赞：0)

**题意**

给出一个 $N$ 个顶点、$M$ 条边的无向图，每条边和顶点都有权值，并且对于每条边 $(u,v)$ 都满足 $p(u)+p(v)\geq p(u,v)$。

现在要将每一个顶点的权值减去 $k(i)$，其中 $0\leq k(i)\leq p(i)$，使得每条边 $(u,v)$ 都满足 $(p(u)-k(u))+(p(v)-k(v))=p(u,v)$ 求 $\sum{k(i)}$ 的最小值和最大值。

**分析**

很明显，将这个式子 $(p(u)-k(u))+(p(v)-k(v))=p(u,v)$ 变形可得：
$$
k(v)=p(u)+p(v)-p(u,v)-k(u)
$$
所以在无向图的一个连通块里只要确定一个节点的 $k$，便可以得到所有节点的 $k$。

想到了什么？设未知数！

我们设一个连通块里的一个节点的 $k$ 为 $x$，然后用 BFS 根据上面的公式求出所有节点的 $k$ 值关于 $x$ 的表达式。

此时有两种情况：

1. 连通块中所有节点都有唯一的表达式，这时可以根据 $0\leq k(i)\leq p(i)$ 求出 $x$ 的取值范围，然后将所有表达式求和并带入 $x$ 的范围求得连通块 $k$ 值之和的范围；
2. 连通块中有的节点有多种表达式，这时可以列方程解出 $x$ 的值，如果解出的 $x$ 值相矛盾或者带入表达式后不符合 $0\leq k(i)\leq p(i)$，则输出 `NIE`，否则将所有表达式求和并带入 $x$ 的值求得连通块 $k$ 值之和。

最终将所有连通块范围加和得到结果。

看代码：

[提交记录](https://www.luogu.com.cn/record/111456342)

```cpp
#include<stdio.h>
#define M 500005
#define N 3000005
#define quit {puts("NIE");return 0;}
typedef long long ll;
struct ex{ //表达式
	ll a,b; //ax+b;
	ll get(ll x) const{return a*x+b;} //带入 
} k[M];
ex operator+(const ex &a,const ex &b){return ex({a.a+b.a,a.b+b.b});} //加减法 
ex operator-(const ex &a,const ex &b){return ex({a.a-b.a,a.b-b.b});}
bool operator!=(const ex &a,const ex &b){return a.a!=b.a&&a.b!=b.b;}
struct edge{int x,nxt,w;} e[N<<1];
int h[M],tot,n,m,p[M],vis[M],cur,Q[M],st,ed;
ll MIN,MAX;
inline void add(int a,int b,int w){e[++tot]={b,h[a],w},h[a]=tot;}
const ll inf=0x7fffffffffffffff;
ll fill(int x){
	st=ed=0;
	Q[ed++]=x,vis[x]=++cur,k[x]={1,0};
	ll res=inf;//inf:无数解  -inf:无解
	while(st^ed){
		int t=Q[st++];
		for(int i=h[t];i;i=e[i].nxt){
			ex tmp=ex({-k[t].a,p[t]+p[e[i].x]-e[i].w-k[t].b}); 
			if(!vis[e[i].x]){
				vis[e[i].x]=cur,
				k[e[i].x]=tmp,
				Q[ed++]=e[i].x;
			}else if(k[e[i].x]!=tmp){
				int a=k[e[i].x].a-tmp.a,b=tmp.b-k[e[i].x].b; //解方程 
				if(!a||b%a) return -inf; //无解与非整除情况 
				else{
					b/=a;
					if(res==inf) res=b;
					else if(b!=res) return -inf; //没有公共解 
				}
			}
		}
	}
	return res;
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",p+i);
	for(int i=0,u,v,w;i<m;++i){
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w),add(v,u,w);
	}
	for(int i=1;i<=n;++i) if(!vis[i]){
		ll t=fill(i);
		if(t==-inf) quit
		else if(t==inf){
			ex r({0,0});
			ll mn=-inf,mx=inf;
			for(int j=1;j<=n;++j) if(vis[j]==cur){
				r=r+k[j]; //累加
				int l=-k[j].b/k[j].a,r=(p[j]-k[j].b)/k[j].a; //解不等式
				if(l>r) l^=r^=l^=r; 
				(mn<l)&&(mn=l),(mx>r)&&(mx=r); //更新最大最小值 
			}
			if(mn>mx) quit 
			if(r.a<0) MIN+=r.get(mx),MAX+=r.get(mn); //一次项系数小于0时最大最小值要倒过来
			else MAX+=r.get(mx),MIN+=r.get(mn);
		}else{
			ll r=0;
			for(int j=1;j<=n;++j) if(vis[j]==cur){
				int tmp=k[j].get(t);
				if(tmp<0||tmp>p[j]) quit //不合法情况 
				r+=tmp; //累加
			}
			MIN+=r,MAX+=r;
		}
	}
	printf("%lld %lld",MIN,MAX);
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

模拟赛题。

设 $p'_u = p_u - x_u(0 \le x_u \le p_u)$，则对于边 $(u, v, w)$ 有：

$$p_u - x_u + p_v - x_u = w_u$$

即：

$$x_u + x_v = p_u + p_v - w$$

故对于一个连通块，随便钦定其中的一个点为根 $rt$，若 $x_{rt}$ 是确定的，则连通块内的所有 $x$ 都确定了（但是可能有无解）。

对于这个连通块内的其它点都可以表示为 $x_i = a_i x_{rt} + b_i$，其中 $a_i \in \{1, -1 \}$，可以搜一遍得到。

然后考虑一个 $x_i$ 可能有多种表达形式（因为可以由多条边更新过来），若 $x_i = a_i x_{rt} + b_i = a_i'x_{rt} + b_{i'}$，则分讨一下：

- 若 $a_i = a_i'$，则想要使得 $x_{rt}$ 有解，只能 $b_i = b_i'$。

- 若 $a_i \ne a'_i$，则 $x_{rt} = \frac{b_i - b_i'}{-2a_i}$，因为 $x_{rt}$ 为整数，所以 $b_i - b_i'$ 必须为偶数；此时可以得到 $x_{rt}$ 只能为这个数。

因为有 $0 \le x_u \le p_u$，则 $0 \le a_ux_{rt} + b_u \le p_u$，这样可以解出若干个 $x_{rt}$ 的范围 $[l_i, r_i]$。

注意到一个连通块的贡献：

$$\sum x_u = x_{rt} \sum a_u + \sum b_u$$

故我们要找到 $x_{rt}$ 的最大值与最小值，即前面 $x_{rt}$ 的范围的交集的左右端点。

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 5e5 + 10, INF = 2e9;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
ll sa, sb, ans1, ans2;
int n, m, u, v, w, Min, Max;
int a[N], b[N], p[N];
bool f[N];
vector<pair<int, int>> E[N];
inline void add(int u, int v, int w){
	E[u].push_back({v, w});
	E[v].push_back({u, w});
}
inline void dfs(int u, int fa){
	sa += a[u], sb += b[u];
	f[u] = 1;
    if(a[u] < 0){
    	Min = max(Min, b[u] - p[u]);
    	Max = min(Max, b[u]);
	}
    else {
    	Min = max(Min, -b[u]);
    	Max = min(Max, p[u] - b[u]);
	}	
	if(Min > Max){
		puts("NIE");
		exit(0);
	}
	for(auto t : E[u]){
		int v = t.fi, w = t.se;
		if(v == fa)
		  continue;
		int h = w - b[u];
		if(f[v]){
			if(a[u] == a[v]){
				if((b[v] - h) & 1){
					puts("NIE");
					exit(0);
				}
				Min = max(Min, (b[v] - h) / (-2 * a[u]));
				Max = min(Max, (b[v] - h) / (-2 * a[u]));
				if(Min > Max){
					puts("NIE");
					exit(0);
				}				
			}
			else if(h != b[v]){
				puts("NIE");
				exit(0);
			}
		}
		else{
			a[v] = -a[u];
			b[v] = h;
			dfs(v, u);
		}
	}
}
bool End;
int main(){
	n = read(), m = read();
	for(int i = 1; i <= n; ++i)
	  p[i] = read();
	while(m--){
		u = read(), v = read(), w = read();
		add(u, v, p[u] + p[v] - w);
	}
	for(int i = 1; i <= n; ++i){
		if(f[i])
		  continue;
		Max = INF, Min = -INF;
		sa = sb = 0;
		a[i] = 1, b[i] = 0;
		dfs(i, 0);
//		cerr << Min << ' ' << Max << '\n';
		ans1 += min(Min * sa + sb, Max * sa + sb);
		ans2 += max(Min * sa + sb, Max * sa + sb);
	}
	write(ans1);
	putchar(' ');
	write(ans2);
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

