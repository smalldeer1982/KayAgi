# [HNOI/AHOI2018] 排列

## 题目描述

给定 $n$ 个整数 $a_1,a_2,\dots,a_n,0\le a_i\le n$，以及 $n$ 个整数 $w_1,w_2,\dots,w_n$。称 $a_1,a_2,\dots,a_n$ 的一个排列 $a_{p_1},a_{p_2},\dots,a_{p_n}$ 为 $a_1,a_2,\dots,a_n$ 的一个合法排列，当且仅当该排列满足：对于任意的 $k$ 和任意的 $j$，如果 $j\le k$，那么 $a_{p_j}$ 不等于 $p_k$。（换句话说就是：对于任意的 $k$ 和任意的 $j$，如果 $p_k$ 等于 $a_{p_j}$，那么 $k<j$。）定义这个合法排列的权值为 $w_{p_1}+2w_{p_2}+\dots+nw_{p_n}$。

你需要求出在所有合法排列中的最大权值。如果不存在合法排列，输出 $-1$。 

样例解释中给出了合法排列和非法排列的实例。

## 说明/提示

### 【样例解释 1】
对于 $a_1=0,a_2=1,a_3=1$，其排列有：
- $a_1=0,a_2=1,a_3=1$，是合法排列，排列的权值是 $1\times 5+2\times 7+3\times 3=28$；
- $a_2=1,a_1=0,a_3=1$，是非法排列，因为 $a_{p_2}$ 等于 $p_2$；
- $a_1=0,a_3=1,a_2=1$，是合法排列，排列的权值是 $1\times 5+2\times 3+3\times 7=32$；
- $a_3=1,a_1=0,a_2=1$，是非法排列，因为 $a_{p_1}$ 等于 $p_2$；
- $a_2=1,a_3=1,a_1=0$，是非法排列，因为 $a_{p_1}$ 等于 $p_3$；
- $a_3=1,a_2=1,a_1=0$，是非法排列，因为 $a_{p_1}$ 等于 $p_3$。

因此该题输出最大权值 $32$。 
### 【样例解释 2】 
对于 $a_1=2,a_2=3,a_3=1$，其排列有：
- $a_1=2,a_2=3,a_3=1$，是非法排列，因为 $a_{p_1}$ 等于 $p_2$；
- $a_2=3,a_1=2,a_3=1$，是非法排列，因为 $a_{p_1}$ 等于 $p_3$； 
- $a_1=2,a_3=1,a_2=3$，是非法排列，因为 $a_{p_1}$ 等于 $p_3$；  
- $a_3=1,a_1=2,a_2=3$，是非法排列，因为 $a_{p_2}$ 等于 $p_3$； 
- $a_2=3,a_3=1,a_1=2$，是非法排列，因为 $a_{p_2}$ 等于 $p_3$； 
- $a_3=1,a_2=3,a_1=2$，是非法排列，因为 $a_{p_1}$ 等于 $p_3$。

因此该题没有合法排列。 

### 【数据范围】 
- 对于前 $20\%$ 的数据，$1\le n\le 10$。
- 对于前 $40\%$ 的数据，$1\le n\le  15$。
- 对于前 $60\%$ 的数据，$1\le n\le 1000$。  
- 对于前 $80\%$ 的数据，$1\le n\le 10^5$。  
- 对于 $100\%$ 的数据，$1\le n\le 5\times10^5$，$0\le a_i\le n$，$1\le w_i\le10^9$，所有 $w_i$ 的和不超过 $1.5×10^{13}$。

## 样例 #1

### 输入

```
3 
0 1 1 
5 7 3 ```

### 输出

```
32```

## 样例 #2

### 输入

```
3 
2 3 1 
1 2 3 ```

### 输出

```
-1```

## 样例 #3

### 输入

```
10 
6 6 10 1 7 0 0 1 7 7 
16 3 10 20 5 14 17 17 16 13 ```

### 输出

```
809```

# 题解

## 作者：Kelin (赞：38)

## [题意](https://blog.csdn.net/BeNoble_/article/details/79973942)

给你一个序列$a$

定义$a$的一个排列$p$合法需要满足当$p[j]\le p[k]$时不存在$a_{p[j]}=p[k]$

定义一个排列的权值是$\sum_{i=1}^n iw_{p[i]}$

求最大权值

---

你永远不会想到会在正式考试上看到原题$,$而且还在某校集训上讲过$???$

原题链接[$Poj2054$](http://poj.org/problem?id=2054)

---

## 题解

### 考虑转化

考虑到如果$a_j=k$那么$k$一定要排在$j$前面

可以理解为对于$j$来说$k$需要先选

考虑建出一个图$,$连边$k=a_j\to j$方向表示顺序

这样$[1,n]$每个点的入度都会是$1$

如果有环那么就无解$,$否则这个图就是一棵以$0$为根树

如果是在树上的话$,$也就是说必须要先选父亲才能选儿子

对于一个点$i,$如果选到他的时间是$T$也就是说他在排列中的位置是$T,$那么他的贡献就是$Tw_i$

这样我们就成功把这道题转化成那个[原题](http://poj.org/problem?id=2054)了~~但是这并没有什么用~~

### 考虑怎么求最大值

考虑一种贪心

考虑一个当前权值最小的点$i$

$1.$如果$i$没有父亲$(fa[i]=0),$那么我们当前一定是选$i$

$2.$如果$i$有父亲$,$那么当$fa[i]$选了后我们一定会最先选$i$

也就是说在最后的排列中$fa[i]$和$i$是挨在一块的

但是考虑到实际上多次合并后每个节点就是一个序列

考虑一个长度为$m_1$的序列$a$和一个长度为$m_2$的序列$b$

考虑$ab$和$ba$两种合并后的序列的答案(假设当前在第$i$位)

$$W_{ab}=\sum_{j=1}^{m_1}(i+j)w_{a_j}+\sum_{j=1}^{m_2}(i+j+m_1)w_{b_j}$$

$$W_{ba}=\sum_{j=1}^{m_2}(i+j)w_{b_j}+\sum_{j=1}^{m_1}(i+j+m_2)w_{a_j}$$

$$W_{ab}-W_{ba}=m_1W_b-m_2W_a$$

如果$W_{ab}\gt W_{ba}\Rightarrow \frac{W_a}{m_1}\lt\frac{W_b}{m_2}$

也就是平均权值小的放前面答案会更优

那么我们把平均权值作为合并后的新权值继续操作即可

计算答案的话就把答案拆开来计算

根据上面的式子可以得到把一个序列$b$放在一个序列$a$后面会产生独立的$W_b\times m_1$的贡献$,$边合并边求和就好了

每次取最小可以用堆实现

因为要修改权值~~所以你可以用set~~

你可以用$pb\_ds$里面的带修改堆$,$或者你拿个东西做标记就好了

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
    while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
template<class T>inline void we(T x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=5e5+5;
typedef int arr[N];
typedef long long ll;
struct Da{
    int u,sz;ll w;
    inline bool operator<(const Da b)const{return w*b.sz>b.w*sz;}
};
struct eg{int nx,to;}e[N];
int n,Cnt;arr fi,fa,Fa,sz,vis;ll ans,w[N];priority_queue<Da>q;
void dfs(int u){vis[u]=1;++Cnt;go(u)if(vis[v]){puts("-1"),exit(0);}else dfs(v);}
inline void add(int u,int v){static int ce=0;e[++ce]={fi[u],v},fi[u]=ce;}
int gf(int x){return Fa[x]==x?x:Fa[x]=gf(Fa[x]);}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    sd(n);
    fp(i,1,n)sd(fa[i]),add(fa[i],i);
    dfs(0);if(Cnt<=n)return puts("-1"),0;
    fp(i,0,n)Fa[i]=i,sz[i]=1;
    fp(i,1,n)sd(w[i]),q.push(Da{i,1,w[i]});
    int u,p;Da s;
    while(!q.empty()){
        s=q.top();q.pop();
        if(sz[u=gf(s.u)]^s.sz)continue;
        Fa[u]=p=gf(fa[u]);
        ans+=w[u]*sz[p],w[p]+=w[u],sz[p]+=sz[u];
        if(p)q.push(Da{p,sz[p],w[p]});
    }
    printf("%lld\n",ans);
return 0;
}
```

---

## 作者：Jμdge (赞：9)

思路和楼上巨佬（们）是一样的，就是考虑先把这个问题转化求解


我们首先发现题意就是某个数有一个权值 ai ，这个 ai 指向的点在排列中必须在 i 的前面，为 0 的话就不用管，然后每个点最多一个出边，这样就构成了一棵内向树森林

那么现在我们要做的就是每次取一个点，然后乘上当前已取的次数累加进答案，并且要求答案的最大值

如楼上所言，我们考虑贪心，从当前权值最小的点 （假设为 i ） 谈起


如果现在它可以被取出：先取它肯定最优


如果它上面还有点没被取出：考虑它的父亲节点被取出后必然会第一时间取它

于是乎，如果 i 上面有父亲的话，我们就考虑直接合并 i 和它的父亲了，并且此时合并得到的节点代表的是一个**连续**序列

但首先我们要将 i 的权值累加进答案，为什么？因为这两个点在答案序列中是一前一后的，后面的点乘上的取点次数比前面的多一次

但是新节点的权值怎么算？

我们假设现在要取两个合并过的新节点合并在一起，

那么方案有两种： a b 和 b a 


我们发现当 a 的权值除去长度后比 b 的权值出去长度 小时第一种方案更佳，反之则选第二种方案

然后一直合并下去...

有点迷？那么可以看下一篇题解

这篇题解主要讲的是判无解的简单方式（也就是对楼下的一点优化）

我们其实不需要深搜，甚至不需要连边，对于无解的判断，只需要并查集就好了...

我们发现按存在答案的数据连边，最后得到的是一颗森林，忽视方向，那么森林中肯定不存在环，我们只需要并查集判环就好了



```
//by Judge
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int M=5e5+3;
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline ll read(){ ll x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} int n,pat,fa[M],Fa[M]; ll w[M],siz[M],ans;
struct node{ int u,sz; ll w;
	bool operator <(const node b)const{ return w*b.sz>b.w*sz; }
}tp; priority_queue<node> q;
int find(int x){ return Fa[x]^x?Fa[x]=find(Fa[x]):x; }
inline void merge(int x,int y){ x=find(x),y=find(y);
	if(x^y) Fa[x]=y; else puts("-1"),exit(0);
}
int main(){ n=read();
	for(int i=0;i<=n;++i) Fa[i]=i;
	for(int i=1;i<=n;++i)
		fa[i]=read(),merge(fa[i],i);
	for(int i=0;i<=n;++i)
		Fa[i]=i,siz[i]=1;
	for(int i=1;i<=n;++i) w[i]=read(),
		q.push((node){i,1,w[i]});
	for(int u,p;!q.empty();){ tp=q.top(),q.pop();
		if(siz[u=find(tp.u)]^tp.sz) continue;
		Fa[u]=p=find(fa[u]),ans+=w[u]*siz[p],
		w[p]+=w[u],siz[p]+=siz[u];
		if(p) q.push((node){p,siz[p],w[p]});
	} return !printf("%lld\n",ans);
}
```

---

## 作者：chenxia25 (赞：8)

题解咕到了现在。。

> ### [洛谷题目页面传送门]( https://www.luogu.com.cn/problem/P4437 )
>
> 有 $n$ 个数 $b_i$，你需要重新排列 $b$ 得到 $b'$ 使得 $b_{a_i}$ 必须排在 $b_i$ 前面。最大化 $\sum\limits_{i=1}^nib'_i$ 或报告无解。
>
> $n\in\left[1,5\times10^5\right]$。

首先建图。如果有环的话肯定就无解，否则不难发现一定是一个森林。于是就转化成了 POJ 2054（只不过 POJ 的这题平方可过）。

首先想到的是贪心，每次选当前能选的节点集合中最小的，而这肯定是不行的，反例随便举。

考虑当前可选的节点集合中任意两个 $x,y$，来比较当前选它们两个哪个更好。一个比较自然的想法是尝试找到一种方法，能将所有选 $x$ 的方案交换几次变成选 $y$ 并且更优。那我们就来看，我们假设当前选的是 $x$，然后 $y$ 在位置 $p$。考虑将 $y$ 移动到 $x$ 当前位置，然后将 $x$ 换过去？可能会不行，因为 $[1,p]$ 内可能会有依赖于 $x$ 的。

想到一种方法，即将 $y$ 移到最前面，然后将 $[1,p]$ 内依赖于或等于 $x$ 的子序列整体顺移。但是这样又不太好比较是否更优了，因为涉及到了 $x$ 的无穷匮子孙。那我们只好退一万步，假设 $y$ 是全树权值最小的节点，那么不难证明换过去一定更优（证明就是你会发现 $x$ 的子孙们移动的距离之和等于 $p-1$，恰好每格与 $y$ 对应，那么每次 $y$ 肯定能干得过其他节点，因为他是最强的嘛）。

你现在虽然能保证一定更优了，但是你毕竟退步了，是有条件的，即必须是全树最小点。也就意味着不是任何时候我们都能应用这个理论来比较优劣。那怎么办呢？我们不考虑当前，我们规划未来，即一旦全树最小点进入了候选集合，那么最先选的一定是它。那么什么时候它进入候选集合呢？那显然是当且仅当它爸爸被选了的时候，也就转化成了最小点爸爸被选之后一定选它。那么不难想到将它和它爸爸合并，这样总结点数 $-1$，似乎可以归纳了。

然后你又会发现问题，因为想要归纳的话，你在任意时刻面临的节点不再是单一的节点，而可能是若干个曾经的节点合并起来的合体。那么我们需要将先前那条理论上升一下。直觉告诉我们应该是内部包含数们的平均数最小的合体。推理起来也不难，我们设 $[1,p]$ 内对应位置上的合体大小为 $sz_i$，和为 $sum_i$，平均数为 $avg_i$，移动前后位置差为 $d_i$，那么显然有 $\sum\limits_{i=1}^p sz_id_i=0$。而每个合体对答案变化量的贡献是 $sum_id_i$，也即 $avg_isz_id_i$，又因为 $sz_id_i$ 是守恒的，所以选 $avg$ 最小的一定没问题。

实现就比较简单了，用 `set` 随便维护一下即可。

根据考察能力守恒定律，思维题代码一定很好写（

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
#define Y second
const int N=500000;
void read(int &x){
	x=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
}
int n;
int a[N+1],b[N+1];
int vis[N+1];
void dfs(int x){
	if(vis[x]==2)exit((puts("-1"),0));
	if(vis[x]==1)return;
	vis[x]=2;
	if(a[x])dfs(a[x]);
	vis[x]=1;
}
struct ufset{
	int ycx[N+2],sz[N+2];
	void init(){for(int i=1;i<=n+1;i++)ycx[i]=0,sz[i]=i>1;}
	int root(int x){return ycx[x]?ycx[x]=root(ycx[x]):x;}
	void mrg(int x,int y){x=root(x),y=root(y),sz[y]+=sz[x],ycx[x]=y;}
}ufs;
int ans[N+1],sum[N+1];
struct frac{
	int a,b;
	frac(int x,int y){a=x,b=y;}
	friend bool operator<(frac x,frac y){
		return x.a*y.b<y.a*x.b;
	}
};
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=n;i++)read(b[i]);
	for(int i=1;i<=n;i++)if(!vis[i])dfs(i);
	set<pair<frac,int> > st;
	for(int i=1;i<=n;i++)st.insert(mp(frac(b[i],1),i)),ans[i]=sum[i]=b[i];
	ufs.init();
	while(st.size()){
		int x=st.begin()->Y;
		int hsc=ufs.root(x+1)-1,ycx=ufs.root(a[hsc]+1)-1;
//		cout<<hsc<<" "<<ycx<<" "<<sum[hsc]<<" "<<sum[ycx]<<"!\n";
		st.erase(st.begin());
		if(ycx)st.erase(st.find(mp(frac(sum[ycx],ufs.sz[ycx+1]),ycx)));
		ans[ycx]+=ans[hsc]+sum[hsc]*ufs.sz[ycx+1];
		sum[ycx]+=sum[hsc];
		ufs.mrg(hsc+1,ycx+1);//确定关系 
		if(ycx)st.insert(mp(frac(sum[ycx],ufs.sz[ycx+1]),ycx));
	}
	cout<<ans[0];
	return 0;
}
```

顺便插一嘴，某 libra 姓神仙似乎提出了一个对平方 DP 的平衡树 + 启发式合并的平方二次对数的优化，不过似乎是假的，欢迎去 D 她（

---

## 作者：Great_Influence (赞：7)

坚决抵制这种在省选出这种原题+乱搞题+简单贪心题+数据水题。

然而出都出了。。。更骚的是这道题我们集训的时候考过，我没点记忆了。。。

具体思路就是贪心。考虑将权值拆开考虑，发现只要每个点计算时，它的子树的权值顺便加上1就可以保证题目要求，所以考虑直接贪心取点。每次取 权值和/点数 最小的团（因为权值大的在后面会加更多次），取玩后将它的权值和当前团的点数加到它父亲所在团中，在删去它。这样贪心取点就可以保证最优。

顺便提一下，该题的堆需要支持堆内修改，你可以手打堆，然而pbds内的堆可以直接实现以上所有操作。。。

代码：

```cpp
#include<bits/stdc++.h>
#include<cctype>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define For(i,a,b) for(i=(a),i##end=(b);i<=i##end;++i)
#define Forward(i,a,b) for(i=(a),i##end=(b);i>=i##end;--i)
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
#define Chkmax(a,b) a=a>b?a:b
#define Chkmin(a,b) a=a<b?a:b
using namespace std;
template<typename T>inline void read(T &x){
    T s=0,f=1;char k=getchar();
    while(!isdigit(k)&&k^'-')k=getchar();
    if(!isdigit(k)){f=-1;k=getchar();}
    while(isdigit(k)){s=s*10+(k^48);k=getchar();}
    x=s*f;
}
void file(void){
    #ifndef ONLINE_JUDGE
    freopen("water.in","r",stdin);
    freopen("water.out","w",stdout);
    #endif
}

const int MAXN=5e5+7;

static struct edge
{
	int v,nxt;
}p[MAXN];

static int n,fa[MAXN],head[MAXN],e;

static long long w[MAXN];

inline void add(int u,int v)
{p[++e]=(edge){v,head[u]};head[u]=e;}

inline void init()
{
	read(n);
	Rep(i,1,n)read(fa[i]),add(fa[i],i);
	Rep(i,1,n)read(w[i]);
}

static long long ans;

static int vis[MAXN],cnt,sz[MAXN];

inline void dfs(int u)
{
	++cnt;vis[u]=true;
	for(register int v=head[u];v;v=p[v].nxt)
	{
		if(vis[p[v].v])puts("-1"),exit(0);
		dfs(p[v].v);
	}
}

typedef pair<long double,int>Pr;

__gnu_pbds::priority_queue<Pr,greater<Pr> >G;
__gnu_pbds::priority_queue<Pr,greater<Pr> >::point_iterator its[MAXN];

static int F[MAXN];

int Find(int x){return x==F[x]?x:F[x]=Find(F[x]);}

inline void solve()
{
	dfs(0);
	if(cnt<=n)return (void)puts("-1");
	Rep(i,1,n)F[i]=i;
	Rep(i,0,n)sz[i]=1;
	Rep(i,1,n)its[i]=G.push(Pr(w[i],i));
	static int u,rt;
	while(!G.empty())
	{
		u=G.top().second;
		G.pop();
		F[u]=rt=Find(fa[u]);
		ans+=w[u]*sz[rt];
		w[rt]+=w[u];
		sz[rt]+=sz[u];
		if(rt)G.modify(its[rt],Pr((long double)w[rt]/sz[rt],rt));
	}
	printf("%lld\n",ans);
}

int main(void){
    file();
	init();
	solve();
	return 0;
}
```

---

## 作者：SXqwq (赞：3)

### Description

给定两个长度为 $n$ 的序列 $a$ 和 $w$。我们称 $a$ 的一个排列 $a_{p_1},a_{p_2},\dots a_{p_n}$ 是一个合法排列，当且仅当对于 $\forall k,j$，若 $p_k=a_{p_j}$，都有 $k<j$。

定义合法排列的权值为 $w_{p_1}+2w_{p_2}+3_{w_{p_3}}+\dots +nw_{p_n}$，求构造一个合法排列，使得权值最大。

### Analysis

贪心题。

首先将题目转换为图论模型。对于 $\forall i$，向 $a_i$ 连边。求图的一个拓扑序 $b_1,b_2,\dots b_n$，使得 $\sum\limits_{i=1}^niw_{b_i}$ 最小。

显然，若建图后存在环，就无解。用并查集判断即可。

若忽略图上限制，我们只需要将 $w$ 序列降序排序。依据排序不等式可以很容易得到答案。这也就说明，**我们希望尽可能早地染权值较大的点。**

不妨考虑一张图的全局最大值，若它的父亲被染色，我们令它下一步立即染色，这一定是不劣的。所以我们可以将它和父亲绑定，二者看作一组一起染色。

为了把上述操作转化成子问题，我们需要考虑新节点的权值，即全局最大值和它父亲“绑定”后形成的新节点。也就是说，我们需要这一组和其他节点的染色优先级。

形式化的，下文我们讨论当点 $a$ 为全局最大值，它和父亲 $b$ 分为一组，和其他节点 $c$ 的染色优先级。

- 若先染组 $ab$，再染 $c$。则价值 $C_{abc}=w_a+2w_b+3w_c$。

- 若先染 $c$，再染组 $ab$，则价值 $C_{cab}=w_c+2w_a+3w_b$。

借鉴调整的思路，我们对二者作差，以得知满足何条件时执行什么策略。

由 $C_{abc}-C_{cab}=2w_c-w_a-w_b$，得当且仅当 $\frac{w_a+w_b}{2}>w_c$ 时，先染组 $ab$，再染其他点 $c$。这也符合人类直觉。

因此，我们可把 $\frac{w_a+w_b}{2}$ 看作组 $ab$ 的权值。进一步地，把组 $ab$ 看作一个权值为 $\frac{w_a+w_b}{2}$ 的新点。

我们尝试将该结论推广，若组 $A$ 中有 $n$ 个点，分别为 $A_1,A_2\dots A_n$。组 $B$ 中有 $m$ 个点，分别为 $B_1,B_2\dots B_m$。

则组 $N$ 和组 $M$ 分别先染色的代价分别表示如下。

$$C_{NM}=\sum\limits_{i=1}^ni\times a_{N_i}+\sum\limits_{i=n+1}^{n+m}i\times a_{M_{i-n}}$$

$$C_{MN}=\sum\limits_{i=1}^m i\times a_{M_i}+\sum\limits_{i=m+1}^{n+m}i\times a_{N_{i-m}}$$

和上面一样，我们将二者作差，得。

$$C_{NM}-C_{MN}=n\times \sum \limits_{i=1}^m a_{M_i}-m\times \sum\limits_{i=1}^n a_{N_i}$$

所以，仅在满足 $\frac{\sum_{i=1}^n a_{N_i}}{n}>\frac{\sum_{i=1}^m a_{M_i}}{m}$ 时，组 $N$ 在组 $M$ 前。

这也就说明，我们将一个组看作一个点时，它的权值为 **组内所有点权的平均值。**

因此，我们每次寻找当前点权最大值，并将其与父亲合并。直到最后只剩下一个点。具体实现的时候可以用堆或者平衡树。

---

## 作者：我打 (赞：3)

简单贪心题。

首先判无解，如果有环就一定无解，否则就有解，这一步可以用并查集来判。

然后考虑如何求出答案，我们将 $i$ 连向 $a_i$，连出以 $0$ 为根一颗树。

假设当前的最小值为 $x$，如果 $x$ 点没有父亲，我们肯定直接选了，如果它有父亲，那么也会在父亲选了之后直接选。

于是我们就可以每一次取出权值最小的点（这一步可以用堆或者set实现），然后将这个点和父亲合并，统计新产生的答案。

考虑一个点的权值表示什么。

设有两个序列$A$和$B$，他们的权值和分别为 $w_a,w_b$，他们的大小分别为$siz_a,siz_b$。

- 如果 $AB$ 连接，那么新产生的权值为 $siz_a \times w_b$。
- 如果 $BA$ 连接，那么新产生的权值为 $siz_b \times w_a$。

假设 $AB$ 连接更优，那么 $siz_a \times w_b \ge siz_b \times w_a$

也就是 $\frac{w_a}{siz_a} \le \frac{w_b}{siz_b}$。

那么，我们每一次取出平均权值最小的点即可。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=710000;
int n,a[maxn];
long long w[maxn];
int fa[maxn],siz[maxn];
struct ljq
{
	int x,siz;
	long long w;
	const bool operator < (const ljq &x)const{return w*x.siz>siz*x.w;}
};
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
	return x*f;
}
priority_queue<ljq> S;
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void Union(int x,int y)
{
	int fx=find(x),fy=find(y);
	if(fx==fy)
	{
		puts("-1");
		exit(0);
	}
	fa[fx]=fy;
}
signed main()
{
	n=rd();
	for(int i=0;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=n;i++)
		a[i]=rd(),Union(i,a[i]);
	for(int i=1;i<=n;i++)
		w[i]=rd(),S.push({i,1,w[i]});
	for(int i=0;i<=n;i++)
		fa[i]=i,siz[i]=1;
	long long ans=0;
	while(!S.empty())
	{
		ljq p=S.top();S.pop();int u;
		if(siz[u=find(p.x)]!=p.siz)
			continue;
		int t=find(a[u]);
		fa[u]=t;
		ans+=1ll*siz[t]*w[u];
		siz[t]+=siz[u],w[t]+=w[u];
		if(t)
			S.push({t,siz[t],w[t]});
	}
	printf("%lld\n",ans);

	return 0;
}
```

---

## 作者：tzc_wk (赞：3)

安利个人 blog：https://www.cnblogs.com/ET2006/

[题面传送门](https://www.luogu.com.cn/problem/P4437)

开始 WA ycx 的~~遗产~~（bushi

首先可以将题目转化为图论模型：$\forall i$ 连边 $a_i\to i$，然后求图的一个拓扑序 $b_1,b_2,\dots b_n$ 使得 $\sum\limits_{i=1}^niw_{b_i}$ 最小。显然如果原图出现环就 $-1$ 了。否则原图一定是一棵森林。

~~然后我就在那儿想各种乱搞，包括但不限于 DP、贪心之类，然后都假掉了~~

我们知道有个东西叫排序不等式，它是说 $\forall a_1\leq a_2\leq a_3\leq\dots\leq a_n,b_1\leq b_2\leq b_3\leq\dots\leq b_n$ 都有 $\sum\limits_{i=1}^na_ib_i\geq\sum\limits_{i=1}^na_ib_{p_i}\geq\sum\limits_{i=1}^na_ib_{n-i+1}$，其中 $p$ 为 $1\sim n$ 的任意一个排列。

将排序不等式应用于此题。如果设 $a_i=i$，$b$ 为 $w$ 排好序的结果可得理论最大值为 $\sum\limits_{i=1}^nib_i$。换句话说，假设使 $w_i$ 取到最小值的 $i$ 为 $x$，那么我们肯定贪心地想把 $x$ 放在前面，越靠前越好。

不过问题是，$a_x$ 不一定等于 $0$，也就是说 $x$ 不一定有能力成为拓扑序的第一个元素。这时候该怎么办呢？我们不考虑现在，我们考虑未来。我们定义当前状态下的“可选集合”为满足 $a_x=0$ 或者 $a_x$ 已经被加入拓扑序的 $x$ 的集合，也就是说可选集合内的元素都可以成为拓扑序中的下一个元素。考虑什么时候 $x$ 能够进入可选集合。显然要当 $a_x$ 已经被加入拓扑序之后。而根据之前的推论我们肯定希望 $x$ 越靠前越好，也就是说一旦 $a_x$ 被加入拓扑序，我们就令 $x$ 为拓扑序中下一个元素，相当于将 $a_x$ 与 $x$ 捆绑在了一起。

P.S：如果你对为什么 $x$ 越靠前越好的证明感兴趣的话，可以从这里往下看：

假设 $a_x$ 是第 $s$ 个加入拓扑序的，$x$ 是第 $t(t>s+1)$ 个加入拓扑序的，第 $i$ 个加入拓扑序的元素为 $b_{i}$，那么我们显然有代价为 $\sum\limits_{i=1}^siw_{b_i}+\sum\limits_{i=1}^{t-s-1}(s+i)w_{b_{i+s}}+tw_x+\sum\limits_{i=t+1}^niw_{b_i}$

而倘若我们将第 $x$ 个元素加入拓扑序的时间提前到 $s+1$，其他元素加入拓扑序的时间保持不变，那么代价变为 $\sum\limits_{i=1}^siw_{b_i}+(s+1)w_x+\sum\limits_{i=1}^{t-s-1}(s+i+1)w_{b_i+s}+\sum\limits_{i=t+1}^niw_{b_i}$

二者做差可得 $\Delta=\sum\limits_{i=1}^{t-s-1}w_{b_i+s}-(t-s-1)w_x$

根据 $w_x$ 为 $\min\{w_i\}$ 可知 $\dfrac{\sum\limits_{i=1}^{t-s-1}w_{b_i+s}}{t-s-1}\geq w_x$，换句话说，任意 $t-s-1$ 个 $w_i$ 的平均值 $\geq w_x$。 

故 $\Delta\geq 0$。而显然将第 $x$ 个元素加入拓扑序的时间提前到 $s+1$ 依旧合法。故我们选择 $x$ 越靠前越好。

还有一个问题，就是经过若干次合并后树上的每一个元素都是一个**合并序列**，也就是若干个形如 $t_1,t_2,\dots t_m$，其中 $t_i$ 拓扑序下一个必须是 $t_{i+1}$ 的序列。此时我们就要探究合并序列的大小关系，考虑两个序列 $x_1,x_2,\dots x_p$ 和 $y_1,y_2,\dots,y_q$ 合并的大小关系。

- 若 $x$ 合并到 $y$ 前面，$W=\sum\limits_{i=1}^piw_{x_i}+\sum\limits_{i=1}^q(i+p)w_{y_i}$
- 若 $y$ 合并到 $x$ 前面，$W=\sum\limits_{i=1}^qiw_{y_i}+\sum\limits_{i=1}^p(i+q)w_{x_i}$

二者做差可得 $\Delta=-q\times\sum\limits_{i=1}^pw_{x_i}+p\times\sum\limits_{i=1}^qw_{y_i}$

我们不妨假设 $\Delta\geq 0$，不等号两边同除 $pq$ 可得 $-\dfrac{\sum\limits_{i=1}^pw_{x_i}}{p}+\dfrac{\sum\limits_{i=1}^qw_{y_i}}{q}\geq 0$。

即 $\dfrac{\sum\limits_{i=1}^qw_{y_i}}{q}\geq \dfrac{\sum\limits_{i=1}^pw_{x_i}}{p}$

也就是说我们选择将**平均值大**的序列合并到**平均值小**的序列的后面。

用堆维护即可。

复杂度线性对数。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=5e5;
int n,a[MAXN+5],b[MAXN+5],vis[MAXN+5];
void dfs(int x){
	if(!(vis[x]^2)) puts("-1"),exit(0);
	if(!(vis[x]^1)) return;vis[x]=2;
	if(a[x]) dfs(a[x]);vis[x]=1;
}
int f[MAXN+5],siz[MAXN+5];ll sum[MAXN+5],val[MAXN+5];
int getf(int x){return (!~f[x])?x:f[x]=getf(f[x]);}
void merge(int x,int y){
	x=getf(x);y=getf(y);
	f[y]=x;sum[x]+=sum[y];
	val[x]+=val[y]+1ll*sum[y]*siz[x];
	siz[x]+=siz[y];
//	printf("merge %d %d %d %lld %lld\n",x,y,siz[x],sum[x],val[x]);
}
struct frac{
	ll x,y;
	frac(ll _x=0,ll _y=1):x(_x),y(_y){}
	bool operator <(const frac &rhs) const{
		return x*rhs.y<rhs.x*y;
	}
};
set<pair<frac,int> > st;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	for(int i=1;i<=n;i++) dfs(i);f[0]=-1;
	for(int i=1;i<=n;i++) f[i]=-1,siz[i]=1,sum[i]=val[i]=b[i];
	for(int i=1;i<=n;i++) st.insert(mp(frac(b[i],1),i));
	while(!st.empty()){
		pair<frac,int> pp=*st.begin();st.erase(st.begin());
		int id=pp.se,f1=getf(id),f2=getf(a[f1]);
		if(f2) st.erase(st.find(mp(frac(sum[f2],siz[f2]),f2)));
		merge(f2,f1);if(f2) st.insert(mp(frac(sum[f2],siz[f2]),f2));
	} printf("%lld\n",val[0]);
	return 0;
}
```



---

## 作者：VenusM1nT (赞：1)

~~这题的题解代码都好毒瘤啊~~  
首先看到题目想到连边 $a_i\to i$，若有环则无解，否则构成一个森林，这一步可以用并查集直接判掉。  
然后考虑求解，贪心取 权值/点数 最小的点，可以保证最后取到最大的值。这一步可以用堆来模拟。取完之后把这个点的数据加到它的父亲上，一步步取就做完了。
```cpp
#include<bits/stdc++.h>
#define N 500000
#define reg register
#define inl inline
#define int long long
using namespace std;
struct Node
{
	int x,siz,w;
	friend bool operator < (const Node &x,const Node &y)
	{
		return x.w*y.siz>x.siz*y.w;
	}
};
priority_queue <Node> q;
int n,a[N+5],f[N+5],w[N+5],siz[N+5],ans;
int Find(reg int x)
{
	return x==f[x]?x:f[x]=Find(f[x]);
}
signed main()
{
	scanf("%lld",&n);
	for(reg int i=0;i<=n;i++) f[i]=i;
	for(reg int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		reg int x=Find(a[i]),y=Find(i);
		if(x^y) f[x]=y;
		else return puts("-1"),0;
	}
	for(reg int i=1;i<=n;i++)
	{
		scanf("%lld",&w[i]);
		q.push((Node){i,1,w[i]});
	}
	for(reg int i=0;i<=n;i++)
	{
		f[i]=i;
		siz[i]=1;
	}
	while(!q.empty())
	{
		reg Node now=q.top();
		q.pop();
		reg int x=Find(now.x);
		if(siz[x]^now.siz) continue;
		reg int y=Find(a[x]);
		f[x]=y;
		ans+=w[x]*siz[y];
		w[y]+=w[x];
		siz[y]+=siz[x];
		if(y) q.push((Node){y,siz[y],w[y]});
	}
	printf("%lld\n",ans);
	return 0;
	
}
```

---

## 作者：_ChongYun_ (赞：0)

### Solution

考虑到先后顺序进行图论建模。对于每一个 $i$，将 $a_i$ 向 $i$ 连边。于是当图出现环时无解。有解则转化为一个以 $0$ 为根的树。

设当前权值最小的节点为 $x$，那么如果 $x$ 之前的节点被染过色了，$x$ 就一定要染色。不妨将 $x$ 与之前的节点合并成一个块。

对于每一个块，我们需要判断如何调整先后顺序来使得贡献最小。先给一个贪心结论吧：根据平均数从小到大。

如何证明？

对于两个块 $A$ 和 $B$，我们设它们的大小分别为 $n$ 和 $m$。

- 若将 $A$ 排在 $B$ 前进行操作，贡献即为 $\sum\limits_{i=1}^{n} A_i \times i +\sum\limits_{i=1}^{m} B_i \times (i+n)$。

- 若将 $B$ 排在 $A$ 前进行操作，贡献即为 $\sum\limits_{i=1}^{m} B_i \times i +\sum\limits_{i=1}^{n} A_i \times (i+m)$。

相减得出：$m\sum\limits_{i=1}^{n} A_i-n\sum\limits_{i=1}^{m} B_i$。

当该值 $<0$ 时，也就是如下时，$A$ 排在 $B$ 前进行操作贡献更小。否则反之：
$$m\sum\limits_{i=1}^{n} A_i-n\sum\limits_{i=1}^{m} B_i<0$$

$$m\sum\limits_{i=1}^{n} A_i<n\sum\limits_{i=1}^{m} B_i$$

$$\frac{\sum\limits_{i=1}^{n} A_i}{n}<\frac{\sum\limits_{i=1}^{m} B_i}{m}$$

易发现，这便是 $A$ 和 $B$ 两者的平均数。

证毕。

使用并查集维护块的大小、总和，使用小根堆维护当前权值最小的节点即可。时间复杂度 $\mathcal{O}(n \log n)$。

### Code


```cpp
/* 云云珂爱！ */ 
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int t,n,rt,ans=0;
struct node{
	int fa,sum,siz;
}qwq[500005];
int f[500005];
int sum=0;
bool vis[500005];
priority_queue<pair<long double,int>,vector<pair<long double,int> >,greater<pair<long double,int> > > q;
int find(int x){
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
struct Edge{
	int to,nxt;
}w[500005];
int hd[500005],ecnt;
void Link(int x,int y){
	++ecnt;
	w[ecnt].to=y;
	w[ecnt].nxt=hd[x];
	hd[x]=ecnt;
	return ;
}
void dfs(int x){
	if(vis[x]) return ;
	vis[x]=1; sum++;
	for(int i=hd[x];i!=0;i=w[i].nxt){
		int y=w[i].to;
		dfs(y);
	}
	return ;
}
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
signed main(){
	n=read(); rt=0;
	for(int i=0;i<=n;i++) f[i]=i;
	for(int i=0;i<=n;i++) qwq[i].siz=1;
	for(int i=1;i<=n;i++){
		qwq[i].fa=read(); 
		Link(qwq[i].fa,i);
	}
	dfs(0);
	if(sum<=n){
		printf("-1\n");
		return 0;
	}
	for(int i=1;i<=n;i++){
		qwq[i].sum=read();
		q.push(make_pair(qwq[i].sum,i));
	}
	memset(vis,0,sizeof(vis));
	while(!q.empty()){
		int x=q.top().second;
		q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		int fa=find(qwq[x].fa);
		ans+=qwq[fa].siz*qwq[x].sum;
		qwq[fa].siz+=qwq[x].siz;
		qwq[fa].sum+=qwq[x].sum;
		f[x]=fa;
		if(fa^rt) q.push(make_pair((long double)((1.0*qwq[fa].sum)/(long double)(1.0*qwq[fa].siz)),fa));
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

