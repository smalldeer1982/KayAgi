# [AGC011C] Squared Graph

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc011/tasks/agc011_c

高橋君は，$ N $ 頂点 $ 1 $, $ 2 $, ..., $ N $ からなる無向グラフをもらいました． このグラフの辺は $ (u_i,\ v_i) $ で表されます． このグラフには，自己辺や多重辺は存在しません．

高橋君は，このグラフをもとに，$ N^2 $ 頂点 $ (a,\ b) $ ($ 1\ \leq\ a\ \leq\ N $, $ 1\ \leq\ b\ \leq\ N $) からなるグラフを作ることにしました． このグラフの辺は，次の規則で定まります．

- 元のグラフにおいて $ a $ と $ a' $ の間および $ b $ と $ b' $ の間の両方に辺があるとき，またそのときに限り，$ (a,\ b) $ と $ (a',\ b') $ の間に辺を張る．

このようにして作ったグラフの連結成分の個数を求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 100,000 $
- $ 0\ \leq\ M\ \leq\ 200,000 $
- $ 1\ \leq\ u_i\ <\ v_i\ \leq\ N $
- $ u_i\ =\ u_j $ かつ $ v_i\ =\ v_j $ を満たすような異なる $ i,\ j $ の組は存在しない

### Sample Explanation 1

高橋君の作ったグラフは下のようになります． !\[\](https://atcoder.jp/img/agc011/6d34a4ddeba67b2286c00acda56abbcc.png)

## 样例 #1

### 输入

```
3 1
1 2```

### 输出

```
7```

## 样例 #2

### 输入

```
7 5
1 2
3 4
3 5
4 5
2 6```

### 输出

```
18```

# 题解

## 作者：w4p3r (赞：23)

可以考虑点$(x,y)$和点$(x',y')$在同一个连通块需要满足什么条件。

新图点$(a,b)$和点$(a',b')$有边的条件是$a$到$a'$有边，$b$到$b'$有边，可以把这个过程视作我们从$a$走到了$a'$，从$b$走到了$b'$。

那么这个条件就比较直观了，为：

在原图中存在一条$x$到$x'$，$y$到$y'$，且长度相同的路径。

因为我们可以在两点间来回走动，所以可以进一步把这个条件简化为：

在原图中存在一条$x$到$x'$，$y$到$y'$，且长度奇偶性相同的**简单路径**。

此时可以发现，若一个连通块中存在奇环，则该连通块任意两点间既存在一条偶路径，又存在一条奇路径。否则可以对该连通块进行黑白染色，相同颜色的点之间路径为偶数，不同颜色的点之间为奇数。

对于只有一个点的连通块因为其无法走动，所以需要单独处理。

可以发现该问题与每个连通块的大小并无关（因为相同属性的二元点新图中一定在同一个连通块），至于三种连通块的数量有关，不妨假设其数量分别为$A,B,C$，分别为$a$类，$b$类，$c$类。

（相同属性同一维指在同一个连通块，且该连通块有奇环或两点颜色相同）

略加推导可以发现（统计答案是先统计$a$类，再统计$b$类，最后统计$c$类）：

对于一个$a$类，自己可以产生$1$的贡献（两维都属于该连通块），可以与其它$a$类造成$2$的贡献（自己在第一维/第二维）。

对于一个$b$类，自己可以产生$2$的贡献（两维颜色相同/颜色不同），可以与其他$b$类造成$4$的贡献（自己在第一维/第二维，两维颜色相同/不同），可以与其他$a$类造成$2$的贡献（自己在第一维/第二维）。

对于一个$c$类，假设现在有$num$个**节点**（不是连通块），那么其可以造成$2*num+1$的贡献（自己在第一维/第二维+自己跟自己）。

直接$O(n)$统计即可。

### 代码

```cpp
//W4P3R
#include<bits/stdc++.h>
#define inf 1e9
#define eps 1e-6
#define mp make_pair
#define pb push_back
#define re register ll
#define fr first
#define sd second
#define pa pair<ll,ll>
#define FOR(i,a,b) for(re i=a;i<=b;i++)
#define REP(i,a,b) for(re i=a;i>=b;i--)
#define N 100010
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
inline ll read()
{
	char ch=getchar();
	ll s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
inline ll lowbit(ll x){return x&(-x);}
ll n,m,vis[N],deg[N],A,B,C;vector<ll>e[N];
ll dfs(ll x,ll col)
{
	vis[x]=col;ll flag=1;
	for(ll y:e[x])
	{
		if(vis[y]){if(vis[y]!=3-vis[x]){flag=0;}}//有奇环
		else {flag&=dfs(y,3-col);}
	}
	return flag;
}//黑白染色
int main()
{
	//ios::sync_with_stdio(false);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();
	FOR(i,1,m)
	{
		ll x=read(),y=read();
		e[x].pb(y),e[y].pb(x);
		deg[x]++,deg[y]++;
	}
	FOR(i,1,n)if(!vis[i])
	{
		if(!deg[i]){C++;continue;}//c类
		else dfs(i,1)?B++:A++;
	}
	ll s=0,ans=0;
	while(A--)
	{
		ans++;
		ans+=2*s;
		s++;
	}
	while(B--)
	{
		ans+=2;
		ans+=2*s;
		s+=2;
	}
	s=n-C;//num
	while(C--)
	{
		ans++;
		ans+=s*2;
		s++;
	}
	cout<<ans<<'\n';
	return 0;
}
//gl

```

**如果你觉得这篇题解对你有帮助，那你可以点个赞支持我一下qwq。如果你对题解有任何问题/认为我的题解有任何问题，可以私信/在评论区发出来，当然如果你对我的题解有任何意见/建议也欢迎指出。我会尽我全力把我题解写到最好的qwq**




---

## 作者：myee (赞：5)

### 思路

考虑找到一个奇环 $(p_1,p_2,\dots,p_m)$，则考虑一条边 $(a,b)$，我们有

$$(a,p_1)-(b,p_2)-(a,p_3)-\dots-(a,p_m)-(b,p_1)$$

因此一个第二维含奇环的联通块，对于第一维的各个联通块，都是分别联通的。**只要第一维不是单点**。

第一维含奇环同理。

对于单点，其作为第一维或第二维时，仍然不与其他点联通。

考虑两维都不含奇环的非单点的联通块，那就是二分图，点集总可分成左、右部。

容易发现这样的情况恰有 $2$ 个联通块：两维均在左部，或均在右部；两维一个在左部，一个在右部。这两类分别构成一个联通块。

因此，设单点有 $a$ 个，含奇环的联通块有 $b$ 个，非单点的二分图联通块有 $c$ 个，总点数有 $n$ 个，则总答案为

$$a(2n-a)+(b+c)^2+c^2$$

直接二分图染色判奇环即可解决。

总复杂度 $O(n)$。

### Code

核心代码很短。

```cpp
std::vector<uint>Way[100005];
uint Dfn[100005],cnt;
bol C[100005];
bol dfs(uint p){
    Dfn[p]=cnt++;
    bol op=false;
    for(auto s:Way[p])if(~Dfn[s])op|=C[p]==C[s];else C[s]=!C[p],op|=dfs(s);
    return op;
}
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    // freopen("QAQ.out","w",stdout);
#endif
    uint n,m;scanf("%u%u",&n,&m);for(uint i=0;i<n;i++)Dfn[i]=-1;
    while(m--){uint u,v;scanf("%u%u",&u,&v),Way[--u].push_back(--v),Way[v].push_back(u);}
    uint a=0,b=0,c=0;
    for(uint i=0;i<n;i++)if(!~Dfn[i]){if(Way[i].empty())a++;else(dfs(i)?b:c)++;}
    // printf("%u %u %u\n",a,b,c);
    printf("%llu\n",(ullt)a*(2*n-a)+(ullt)(b+c)*(b+c)+(ullt)c*c);
    return 0;
}
```


---

## 作者：Ebola (赞：5)

# 【AGC011C】Squared Graph

一道结论题。题解的结论真是神了，并不知道出题人是怎么想到这东西的，这里说一下结论吧

1. 对于一个原图中独立的点x，新图的(x,i)与(i,x)均为独立的点。故设原图中独立点数量为p，那么独立点对答案的贡献就是pn+(n-p)p

2. 对于原图中的一个无奇环联通块，它可以与任一联通块组成新图的两个不同联通块。那么设这种联通块有c个，这种联通块两两组合对答案的贡献就是c\*c\*2
3. 对于原图种的一个有奇环联通块，它可以与任一联通块组成新图的一个联通块（若与它组合的是无奇环联通块，则两个）。设这种联通块有d个，则它与其它联通块组合对答案的贡献就是d\*(d+c\*2)

严格证明我也不会。但仔细思考，正确性还是比较显然的。YY过程比较乱，就不献丑了

```cpp
#include<bits/stdc++.h>
#define MP make_pair
#define FR first
#define SE second
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int N=200010;
struct Edge{int to,next;} e[N<<1];
int fa[N],sz[N],n,m,h[N],sum=0;
pair<int,int> circle[N];
bool parity[N],odd[N];
int cnt[2];

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs(int u,int fa)
{
    parity[u]=parity[fa]^1;
    for(int t=h[u];t;t=e[t].next)
        if(e[t].to!=fa) dfs(e[t].to,u);
}

int main()
{
    int u,v,tot=0;
    n=read();m=read();
    for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;
    for(int i=1;i<=m;i++)
    {
        u=read();v=read();
        if(find(u)!=find(v))
        {
            add_edge(u,v);
            add_edge(v,u);
            u=find(u);v=find(v);
            fa[u]=v;sz[v]+=sz[u];
        }
        else circle[++tot]=MP(u,v);
    }
    for(int i=1;i<=n;i++)
        if(fa[i]==i) dfs(i,0);
    for(int i=1;i<=tot;i++)
        if(parity[circle[i].FR]==parity[circle[i].SE])
            odd[find(circle[i].FR)]=1;
    int alone=0;
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        if(fa[i]!=i) continue;
        if(sz[i]==1) alone++,ans+=n;
        else cnt[odd[i]]++;
    }
    ans+=1ll*(n-alone)*alone;
    ans+=2ll*cnt[0]*cnt[0];
    ans+=1ll*cnt[1]*(cnt[1]+2*cnt[0]);
    cout<<ans<<endl;
    return 0;
}
```



---

## 作者：Gorenstein (赞：3)

考虑 $(a,b)$ 和 $(c,d)$ 在一个连通块的条件。

观察新图上一条边的涵义：$(u,v)\leftrightarrow(p,q)$ 则说明原图有 $u\to p$ 和 $v\to q$，即有两个点能从 $u,v$ 走到 $p,q$。

顺着这个思路，因为一个点可以来回走（$u\to p\to w,v\to q\to v\;\Longrightarrow\;(u,v)\leftrightarrow(w,v)$），所以 $(a,b)$ 与 $(c,d)$ 处于一个连通块表明原图存在 $a$ 到 $c$ 与 $b$ 到 $d$ 的简单路径，满足它们的长度相差偶数。

我们将图的连通块分为以下三种情况考虑：
1. 含奇环的图。每个点到另一个点存在一奇一偶两条路径。
2. 二分图。进行黑白染色，两种颜色之间的点距离为奇数，同色点距离为偶数。
3. 孤立点。它不与其他点连通。

现在把某个连通块的点放到其中一维上，考虑另一维。设奇环、二分图、孤立点的数量是 $a,b,c$。

以下先不考虑孤立点。对于一个奇环，其中的两点定能适配第一维，故能和第一维的连通块分别形成一个连通块。考虑到两维之间的顺序，其贡献是 $a^2+2ab$。

对于二分图与二分图之间的计数，由上面的讨论可得两个二分图的同色和不同色能分别形成一个新图的连通块，这部分的贡献是 $2b^2$。

最后算上孤立点的贡献。设 $x$ 是孤立点，则 $\forall y$，$(x,y)$ 与 $(y,x)$ 是孤立点，$(x,x)$ 也是孤立点。于是它的贡献是 $c^2+2c(n-c)$。

---

## 作者：Graphcity (赞：0)

首先我们思考 $(a,b)$ 和 $(c,d)$ 怎样才能够连通，答案是存在一条路径 $a\to s_1\to s_2\to \cdots \to s_n\to c$，且有一条同样长度的路径 $b\to t_1\to t_2\to \cdots\to t_n\to d$ 时才能够连通。

先从简单的情况开始考虑：

- 孤立点与其它所有点之间的二元组都不互相连通，因为孤立点没有一条路径可走。

- 对于一棵树，可以发现距离奇偶性相同的点对之间可以连边，方案可以由同时尽量移到直径两端的方法来构造。

- 扩展一下：对于一张连通二分图，可以根据点对所在集合的相同 / 不同来划分成两个连通块。首先这两个连通块直接一定不能互相连边，因为同时走一步不能改变所在集合的相同或不同，充分性易证。必要性可以找一棵生成树。

- 对于有奇环的连通图，将两个点同时移到奇环处就可以改变所在集合的相同或不同。这个时候只有一个连通块。

- 对于两个不同连通块之间的点，显然它们不会跟其它连通块扯上关系。根据之前的论证，可以得到这条法则：

|     | 孤立点 | 二分图 | 奇环图 |
| :----------: | :----------: | :----------: | :----------: |
| **孤立点** | 1 | 二分图大小 | 奇环图大小 |
| **二分图** | 二分图大小 | 2 | 1 |
| **奇环图** | 奇环图大小 | 1 | 1 |

统计有多少个连通块是孤立点 / 二分图 / 奇环图即可。时间复杂度 $O(n+m)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,col[Maxn+5],cnt[3],tot,chk; ll ans;
vector<int> v[Maxn+5];
// 孤立点,二分图,奇环图

inline void dfs(int x,int id)
{
    col[x]=id,++tot;
    for(auto y:v[x])
    {
        if(!col[y]) dfs(y,id^1);
        else if(col[x]==col[y]) chk=1;
    }
}
inline void Solve(int x)
{
    tot=0,chk=0,dfs(x,2);
    if(tot==1) cnt[0]++;
    else if(!chk) cnt[1]++;
    else cnt[2]++;
}

int main()
{
    n=read(),m=read();
    For(i,1,m)
    {
        int a=read(),b=read();
        v[a].push_back(b),v[b].push_back(a);
    }
    For(i,1,n) if(!col[i]) Solve(i);
    ans=cnt[0]+cnt[1]*2+cnt[2];
    // 孤立点+孤立点
    ans+=1ll*cnt[0]*(cnt[0]-1);
    // 孤立点+其它点
    ans+=2ll*cnt[0]*(n-cnt[0]);
    // 二分图+二分图
    ans+=2ll*cnt[1]*(cnt[1]-1);
    // 二分图+奇环图
    ans+=2ll*cnt[1]*cnt[2];
    // 奇环图+奇环图
    ans+=1ll*cnt[2]*(cnt[2]-1);
    cout<<ans<<endl;
    return 0;
}
```

---

