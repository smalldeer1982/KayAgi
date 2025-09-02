# [PA 2016] 雨后的蘑菇 2 / Grzyby po deszczu 2

## 题目背景


译自 [Potyczki Algorytmiczne 2016](https://sio2.mimuw.edu.pl/c/pa-2016-1/p/) R3 Grzyby po deszczu 2 [A] (GRZ)。


## 题目描述


给定长度为 $n$ 的整数数列 $a_1,\ldots,a_n$ 和 $b_1,\ldots,b_n$。

第 $1$ 天早上，第 $i$ 块地上有 $b_i$ 个蘑菇。每天的晚上，第 $i$ 块地上都会长出 $a_i$ 个蘑菇。

采蘑菇只能在早上进行，一次只能在一块地上采集，一次采集的数量没有限制。

对于 $k=1,2,\cdots,n$，求出：如果在前 $k$ 天**每天早上**选择一块地（可以重复选择同一块地）采蘑菇，最多能采多少个蘑菇？

## 说明/提示


- $1\le n\le 10^6$；
- $0\le a_i\le 10^6$；
- $0\le b_i\le 10^{12}$。


## 样例 #1

### 输入

```
3
5 10
16 0
5 10```

### 输出

```
10
26
57```

# 题解

## 作者：Wuyanru (赞：7)

莫名其妙被卡了好几天，然后莫名其妙想明白了，写篇题解。

[题目链接](https://www.luogu.com.cn/problem/P11608)。

## 题意

现在有 $n$ 块蘑菇地，第 $i$ 块蘑菇地初始有 $b_i$ 个蘑菇，每天晚上一块地会长出 $a_i$ 个蘑菇。

你每天早上可以选择一块地，并把这块地的所有蘑菇都拿走。

对每一个 $1\le k\le n$ 求出，如果只有前 $k$ 天早上你可以拿蘑菇，最多能拿多少。

$n\le 10^6$。

## 题解

首先有一些比较简单的观察。

观察一：一块地不可能被采摘两次，因为如果被摘了两次，那么第一次采摘完全是可以省略掉的。

此时这一块地拿到的总蘑菇量不变，你还可以拿多出来这一天去采一块别的蘑菇地，稳赚不亏。

观察二：按照时间顺序，所有采摘的蘑菇地，$a_i$ 是递增的。

这个也很好理解，因为如果你已经确定了采集哪些蘑菇地，那么 $b$ 的贡献就是确定的，你把 $a_i$ 大的换到后面让他多长一些肯定更优。

那么这个时候就有一个 $O(n^2)$ 的暴力了。

首先将所有蘑菇地按照 $a_i$ 升序进行排序，那么一定是先拿前面的再拿后面的。

设 $dp_{i,j}$ 表示从前 $i$ 块蘑菇地里面，选出 $j$ 块地，作为前 $j$ 天采摘的目标，最多能有多少蘑菇。

转移比较简单，直接枚举第 $i$ 块蘑菇地选不选就行。

转移方程是 $dp_{i,j}=\max(dp_{i-1,j},dp_{i-1,j-1}+(j-1)a_i+b_i)$。

那么考虑怎么优化这个东西呢，不妨想一想他有没有别的性质。

考虑相邻两天，采集蘑菇地的变化。

打个表或者自己瞎猜一下，都可以发现，第 $i$ 天与第 $i+1$ 天最优方案不同的地方，一定是恰好多采集了一块蘑菇地。

而不会出现，去掉 $2$ 块蘑菇地，再添加 $3$ 块蘑菇地这种情况。

为什么呢，假设 $i+1$ 天的最优方案，少了 $k$ 个蘑菇地而新添了 $k+1$ 个蘑菇地（特殊的，如果有多个最优方案，选择 $k$ 最小的那个）：

![](https://cdn.luogu.com.cn/upload/image_hosting/pb7kzojq.png)

图中的 $0$ 表示蘑菇地两天的状态相同，$+$ 表示只有后一天选中，$-$ 表示只有前一天选中。

若 $k>0$，那么一定可以找到一对 $+1$ 和 $-1$，使得他们中间只有 $0$，比如图中的绿色框内两块蘑菇地。

考虑设当前的答案为 $S_1$，将这两块地有 $+1,-1$ 变成 $0,0$ 的方案答案设为 $S_2$。

如果有 $S_2\ge S_1$，说明 $i+1$ 天这个方案不是最优的，违背了我们的假设。

这说明有 $S_1>S_2$，这同样是矛盾的。

因为如果 $+1,-1$ 这个方案更优，那么在第 $i$ 天的时候，这两块地就应该是现在 $S_1$ 这个状态了，这说明第 $i$ 天的方案又不是最优的。

这样，我们使用了反证法，证明第 $i+1$ 天恰好比第 $i$ 天多选了一块蘑菇地。

那么这个时候我们又有一个 $O(n^2)$ 做法，对于每一天，直接枚举新选的蘑菇地是哪一块，然后选择增量最大的那个加入方案。

这是一个非常好的性质，再看一下之前的 dp 转移。

如果 $dp_{i-1,j}>dp_{i-1,j-1}+(j-1)a_i+b_i$，这说明最优方案是不选 $i$ 这块蘑菇地。

否则 $dp_{i-1,j}\le dp_{i-1,j-1}+(j-1)a_i+b_i$，这说明最优方案是选择 $i$ 这块蘑菇地。

那么考虑我们刚刚的结论，可以发现一定存在一个 $k$，满足对于 $j<k$ 的部分，最优方案是不选 $i$，而对于 $j\ge k$ 的部分，最优方案是选择 $i$。

那么这个 dp 就可以直接使用平衡树维护了，每一次直接在平衡树上二分找到 $k$ 的位置，然后分左右两侧分别转移。

左边的转移是直接不变就行，右边需要整体加一个等差数列，然后中间需要额外插入一个点。

这个做法是 $O(n\log n)$ 的，显然太难写了，因为不仅需要区间加等差数列，还需要二分，你还得维护每一个子树的第一个和最后一个节点编号。

所以我们考虑一个稍微好写一点的做法，我们直接去维护相邻两项 dp 的差。

我们设 $fp_{i,j}=dp_{i-1,j}-dp_{i-1,j-1}$，其中 $j\ge 1$，我们维护 $fp_{i,j}$ 的值。

首先来考虑 $k$ 怎么找，可以发现 $k$ 是满足 $dp_{i-1,j}\le dp_{i-1,j-1}+(j-1)a_i+b_i$ 的最小的 $j$。

而这个条件等价于 $fp_{i-1,j}\le (j-1)a_i+b_i$，这个条件可以直接在平衡树上二分。

再写出 $dp_{i,j}$ 的转移式子：
$$
dp_{i,j}=\begin{cases}dp_{i-1,j}&j<k\\dp_{i-1,j-1}+(j-1)a_i+b_i&j\ge k\end{cases}
$$
那么我们就能写出 $fp_{i,j}$ 的转移式子 
$$
fp_{i,j}=\begin{cases}fp_{i-1,j}&j<k\\(j-1)a_i+b_i&j=k\\fp_{i-1,j-1}+a_i&j>k\end{cases}
$$
这样我们的平衡树就只需要维护区间加，而不是区间加等差数列了，并且由于这个二分只涉及到一个值，你也不需要记每一个子树的第一个或者最后一个点了，这实在是太牛了。

时间复杂度 $O(n\log n)$。

## 代码

```c++
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f3f3f3f3fll
#define debug(x) cerr<<#x<<"="<<x<<endl
using namespace std;
using ll=long long;
using ld=long double;
using pli=pair<ll,int>;
using pi=pair<int,int>;
template<typename A>
using vc=vector<A>;
template<typename A,const int N>
using aya=array<A,N>;
inline int read()
{
    int s=0,w=1;char ch;
    while((ch=getchar())>'9'||ch<'0') if(ch=='-') w=-1;
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline ll lread()
{
    ll s=0,w=1;char ch;
    while((ch=getchar())>'9'||ch<'0') if(ch=='-') w=-1;
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
mt19937 _rand(time(0)^clock());
struct node
{
    ll a,b;
}v[1000005];
int pri[1000005];
ll num[1000005];
ll tag[1000005];
int siz[1000005];
int ls[1000005];
int rs[1000005];
int n,rt,cnt;
inline void T(int p,ll y)
{
    num[p]+=y;
    tag[p]+=y;
}
inline void push_down(int p)
{
    if(ls[p]) T(ls[p],tag[p]);
    if(rs[p]) T(rs[p],tag[p]);
    tag[p]=0;
}
inline void push_up(int p)
{
    siz[p]=siz[ls[p]]+siz[rs[p]]+1;
}
int merge(int u,int v)
{
    if(!u||!v) return u|v;
    push_down(u),push_down(v);
    if(pri[u]>pri[v])
    {
        rs[u]=merge(rs[u],v);
        push_up(u);
        return u;
    }
    else
    {
        ls[v]=merge(u,ls[v]);
        push_up(v);
        return v;
    }
}
void split(int p,int &x,int &y,ll a,ll b,int bef)
{
    if(!p){ x=y=0;return ;}
    push_down(p);
    if(num[p]<=(bef+siz[ls[p]])*a+b)
    {
        y=p;
        split(ls[p],x,ls[y],a,b,bef);
        push_up(y);
    }
    else
    {
        x=p;
        split(rs[p],rs[x],y,a,b,bef+siz[ls[p]]+1);
        push_up(x);
    }
}
inline int New(ll v)
{
    cnt++;
    num[cnt]=v,tag[cnt]=0;
    ls[cnt]=rs[cnt]=0;
    siz[cnt]=1,pri[cnt]=_rand();
    return cnt;
}
ll ans;
void output(int p)
{
    if(!p) return ;
    push_down(p);
    output(ls[p]);
    ans+=num[p];printf("%lld\n",ans);
    output(rs[p]);
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++) v[i].a=lread(),v[i].b=lread();
    sort(v+1,v+n+1,[](node a,node b){ return a.a<b.a;});

    for(int i=1;i<=n;i++)
    {
        int x,y;
        split(rt,x,y,v[i].a,v[i].b,0);
        T(y,v[i].a);
        rt=merge(x,merge(New(siz[x]*v[i].a+v[i].b),y));
    }
    output(rt);
    return 0;
}
```

---

## 作者：Reunite (赞：2)

简单题。先找一些性质：

- 一个点不会被重复选择，否则仅保留后一次更优。

- 若确定好选择哪些位置，则一定按照斜率递增的顺序依次选择。

第一条显然，对于第二条，考虑调整法，关注两个位置 $i,j$，满足 $a_i>a_j$，容易调整证明先选斜率小的更优，所以一定按照斜率递增顺序选。

因此按照 $a_i$ 排序，即可列出 $O(n^2)$ 的 dp：设 $f_{i,j}$ 为考虑排序后前 $i$ 位置，选择了 $j$ 个的方案，转移是朴素的：

$$f_{i,j}=\max(f_{i-1,j},f_{i-1,j-1}+a_i\times (j-1)+b_i)$$

于是我们得到了这样一个经典的 $O(n^2)-O(1)$ 的二维 dp 转移形式，考虑一些经典做法：发现第二维有凸性，直接维护凸包；发现第二维差分数组改变量很小；发现对 $\max$ 里的取值有决策单调性等等。

打表发现，最优情况下一定存在一个位置 $pos$，使得 $j\le pos$ 的位置一定取 $f_{i-1,j}$ 最优，后面的一定取 $f_{i-1,j-1}+a_i\times (j-1)+b_i$ 最优。因此上平衡树动态维护第二维的差分值，每轮平衡树上二分找到决策断点，则单点插入，后缀对差分区间加即可。复杂度 $O(n\log n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <random>
#define int long long
using namespace std;

int n,tot,root,S,C,pos;
int lc[1000005];
int rc[1000005];
int tg[1000005];
int sz[1000005];
int wei[1000005];
int cha[1000005];
int val[1000005];
struct node{int k,b;}a[1000005];
mt19937 rnd(time(NULL));

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline int newnode(int x){
	tot++;
	lc[tot]=rc[tot]=0;
	sz[tot]=1;
	wei[tot]=rnd();
	cha[tot]=val[tot]=x;
	return tot;
}

inline void pushup(int u){
	sz[u]=sz[lc[u]]+sz[rc[u]]+1;
	cha[u]=cha[lc[u]]+cha[rc[u]]+val[u];
	return ;
}

inline void down(int u,int x){
	tg[u]+=x;
	val[u]+=x;
	cha[u]+=sz[u]*x;
	return ;
}

inline void pushdown(int u){
	if(!tg[u]) return ;
	if(lc[u]) down(lc[u],tg[u]);
	if(rc[u]) down(rc[u],tg[u]);
	tg[u]=0;
	return ;
}

inline int merge(int p,int q){
	if(!p||!q) return p|q;
	if(wei[p]<wei[q]){
		pushdown(p);
		rc[p]=merge(rc[p],q);
		pushup(p);
		return p;
	}
	else{
		pushdown(q);
		lc[q]=merge(p,lc[q]);
		pushup(q);
		return q;
	}
}

inline void split(int u,int k,int &l,int &r){
	if(!u) l=r=0;
	else{
		pushdown(u);
		if(sz[lc[u]]<k) l=u,split(rc[u],k-sz[lc[u]]-1,rc[u],r);
		else r=u,split(lc[u],k,l,lc[u]);
		pushup(u);
	}
	return ;
}

inline void Find(int u,int i){
	if(!u) return ;
	pushdown(u);
	int v1=S+cha[lc[u]]+val[u];
	int v2=S+cha[lc[u]]+a[i].k*(C+sz[lc[u]])+a[i].b;
	if(v1>=v2){
		S+=cha[lc[u]]+val[u];
		C+=sz[lc[u]]+1;
		pos=C;
		Find(rc[u],i);
	}
	else Find(lc[u],i);
	pushup(u);
	return ;
}

inline void out(int u){
	if(!u) return ;
	pushdown(u);
	out(lc[u]);
	S+=val[u];
	C++;
	if(C>1) printf("%lld\n",S);
	out(rc[u]);
	pushup(u);
	return ;
}

signed main(){
	in(n);
	for(int i=1;i<=n;i++) in(a[i].k),in(a[i].b),a[i].b-=a[i].k;
	sort(a+1,a+1+n,[](node p,node q){return p.k<q.k;});
	root=newnode(0);
	for(int i=1;i<=n;i++){
		pos=1;
		S=0,C=1;
		int x,y;
		split(root,1,x,y);
		Find(y,i);
		root=merge(x,y);
		split(root,pos,x,y);
		x=merge(x,newnode(a[i].k*pos+a[i].b));
		down(y,a[i].k);
		root=merge(x,y);
	}
	S=C=0;
	out(root);

	return 0;
}
```

---

## 作者：_ChongYun_ (赞：0)

### Solution

在最终选择的若干个位置中：

- 由于多次选择是没有必要的，于是每个位置只会被选择一次。

- 由于 $b_i$ 的总和确定，于是我们让 $a_i$ 大的往后放一定最优。

考虑 $\mathcal{O}(n^2)$ 的暴力 dp 做法。令 $dp_{i,j}$ 表示在前 $i$ 个位置中，前 $j$ 天选择 $j$ 个位置采摘的最大贡献。那么有状态转移方程：

$$dp_{i,j}=\max\{dp_{i-1,j},dp_{i-1,j-1}+b_i+(j-1)a_i\}$$

接下来考虑如何优化它。我们打表观察发现一个很对的性质：相邻两天的变化一定是恰好多选择了一个位置。

那么在最优情况下，一定存在一个断点 $p$：

- 当 $j<p$ 时满足 $dp_{i-1,j}>dp_{i-1,j-1}+b_i+(j-1)a_i$。

- 当 $j\ge p$ 时满足 $dp_{i-1,j}\le dp_{i-1,j-1}+b_i+(j-1)a_i$。

那么 $p$ 等价于满足 $dp_{i-1,j}- dp_{i-1,j-1}\le b_i+(j-1)a_i$ 的最小的 $j$。我们可以使用平衡树来维护这个差分值，平衡树上二分来查找 $p$。时间复杂度 $\mathcal{O}(n \log n)$。

### Code

```cpp
/* ChongYun */
#include<bits/stdc++.h>
#define START_LL 1
using namespace std;
#define start(x) using namespace x
#if START_LL 
#define int long long
#endif
namespace IO{
    #define flush() fwrite(obuf,1,O-obuf,stdout)
    #define putchar(x) ((O==obuf+(1<<21))&&(flush(),O=obuf)),*O++=x
    char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
    #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
    inline int read(){
        register int x=0,f=1;
        register char ch=getchar();
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
    inline void write(int x){
        if(x>9) write(x/10);
        putchar((x%10)^48);
        return ;
    }
    struct Flush{ ~Flush(){flush();} }_;
}start(IO);
const int N=1e6+5;
int n,ans=0;
struct Node{ int a,b; }qwq[N];
bool cmp(Node pt,Node qt){ return pt.a<qt.a; }
namespace FHQ_Treap{
    #define ls(p) Treap[p].l
    #define rs(p) Treap[p].r
    int rt,tot=0;
    struct node{
        int l,r,siz,val,rnd;
    }Treap[N<<1];
    int lazy[N<<1];
    void Modify(int p,int x){
        if(!p) return ;
        lazy[p]+=x,Treap[p].val+=x;
        return ;
    }
    void pushup(int p){
        if(!p) return ;
        Treap[p].siz=Treap[ls(p)].siz+Treap[rs(p)].siz+1;
        return ;
    }
    void pushdown(int p){
        if(!p) return ;
        if(ls(p)) Modify(ls(p),lazy[p]);
        if(rs(p)) Modify(rs(p),lazy[p]);
        lazy[p]=0;
        return ;
    }
    int NewNode(int x){
        Treap[++tot]={0,0,1,x,rand()};
        return tot;
    }
    void Split(int p,int pos,int &l,int &r,int A,int B){
        if(!p){
            l=r=0;
            return ;
        }
        pushdown(p);
        if(Treap[p].val<=B+(pos+Treap[ls(p)].siz)*A) Split(ls(r=p),pos,l,ls(p),A,B);
        else Split(rs(l=p),pos+Treap[ls(p)].siz+1,rs(p),r,A,B); 
        pushup(p);
        return ;
    }
    int Merge(int l,int r){
        if(!l||!r) return l+r;
        pushdown(l),pushdown(r);
        if(Treap[l].rnd<=Treap[r].rnd){
            rs(l)=Merge(rs(l),r);
            pushup(l);
            return l;
        }
        ls(r)=Merge(l,ls(r));
        pushup(r);
        return r;
    }
}start(FHQ_Treap);
void Print(int p){
    if(!p) return ;
    pushdown(p);
    Print(ls(p));
    ans+=Treap[p].val;
    write(ans),putchar('\n');
    Print(rs(p));
    return ;
}
signed main(){
    srand(201110191);
    n=read();
    for(int i=1;i<=n;i++) qwq[i]={read(),read()};
    sort(qwq+1,qwq+n+1,cmp);
    for(int i=1,pl,pr;i<=n;i++){
        Split(rt,0,pl,pr,qwq[i].a,qwq[i].b);
        Modify(pr,qwq[i].a);
        rt=Merge(Merge(pl,NewNode(qwq[i].b+Treap[pl].siz*qwq[i].a)),pr);
    }
    Print(rt);
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

如果开了这道题应该就场切了把。。。

显然，将 $a$ 排序。我们等价于求出 $1 \le i_1 < i_2 < \cdots < i_k \le n$，使得：

$$
\sum_{j=1}^k b_{i_j} + (j-1) a_{i_j}
$$

最大。（因为一块地不会被取多次。而根据排序不等式，应该优先取 $a$ 最小的）

不妨先写一个 $O(n^2)$ 的 DP，大概长这样：

```cpp
memset(dp,-0x3f,sizeof(dp));
ffor(i,0,n) dp[i][0]=0;
ffor(i,1,n) ffor(j,1,i) dp[i][j]=max(dp[i-1][j-1]+b[i]+a[i]*(j-1),dp[i-1][j]);
```

这个东西看起来就不是很好优化。考虑一些凸优化技巧。

很遗憾，我们发现 $dp_{i,*}$ 并不是关于 $*$ 的凸数列。但是打表发现，$dp_{i,*}-* a_i$ 是凸的——换句话说，上述转移方程中，$j$ 的一段前缀是直接沿袭 $dp_{i-1,j}$，剩下的后缀是从 $dp_{i-1,j-1}$ 转移而来的。

因此我们可以维护 $dp_{i,*}$ 的差分，找到转移的断点。发现只有区间加，区间平移和插入操作，可以使用平衡树加速。

在平衡树上二分可以做到 $O(n \log n)$，常数略大。

我竟然未经调试一发入魂直接过了，代码能力惊人。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10;
int n,tot,rt,a[MAXN],b[MAXN];
mt19937 myrand(time(NULL));
struct INFO {int sze,key,tag,v,ls,rs;}t[MAXN];
void push_up(int u) {return t[u].sze=t[t[u].ls].sze+t[t[u].rs].sze+1,void();}
void assign(int u,int tag) {return t[u].v+=tag,t[u].tag+=tag,void();}
void push_down(int u) {
	if(t[u].ls) assign(t[u].ls,t[u].tag);
	if(t[u].rs) assign(t[u].rs,t[u].tag);
	return t[u].tag=0,void();
}
void split(int u,int s,int &p,int &q) {
	if(!u) return p=q=0,void();
	push_down(u);
	if(s<=t[t[u].ls].sze) q=u,split(t[u].ls,s,p,t[u].ls);
	else p=u,split(t[u].rs,s-t[t[u].ls].sze-1,t[u].rs,q);
	return push_up(u),void();
}
int merge(int u,int v) {
	if(!u||!v) return u|v;
	push_down(u),push_down(v);
	if(t[u].key<=t[v].key) return t[u].rs=merge(t[u].rs,v),push_up(u),u;
	return t[v].ls=merge(u,t[v].ls),push_up(v),v;
}
int ANS;
void bfind(int u,int a,int b,int sze) {
	if(!u) return ;
	push_down(u);
	int rnk=sze+t[t[u].ls].sze+1;
	if(t[u].v<=a*(rnk-1)+b) return bfind(t[u].ls,a,b,sze),void();
	ANS=rnk,bfind(t[u].rs,a,b,rnk);
	return ;
}
int get_node(int v) {return t[++tot]={1,myrand(),0,v,0,0},tot;}
void dfs(int u) {
	if(!u) return ;
	push_down(u),dfs(t[u].ls),ANS+=t[u].v,cout<<ANS<<'\n',dfs(t[u].rs);
	return ;	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	vector<pair<int,int>> pr;
	ffor(i,1,n) cin>>a[i]>>b[i],pr.push_back({a[i],b[i]});
	sort(pr.begin(),pr.end());
	ffor(i,1,n) a[i]=pr[i-1].first,b[i]=pr[i-1].second;
	rt=get_node(b[1]);
	ffor(i,2,n) {
		ANS=0,bfind(rt,a[i],b[i],0);
		int A,B;
		split(rt,ANS,A,B);
		assign(B,a[i]),rt=merge(A,merge(get_node(b[i]+ANS*a[i]),B));	
	}
	ANS=0,dfs(rt);
	return 0;
}
```

---

