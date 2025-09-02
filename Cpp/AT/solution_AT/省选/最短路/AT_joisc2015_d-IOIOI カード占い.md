# IOIOI カード占い

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2015/tasks/joisc2015_d



# 题解

## 作者：zac2010 (赞：6)

关于这类问题的一个经典的套路就是：利用差分将区间翻转转换为点对翻转。

既然操作差分了，那么原序列初始时也得以差分的形式进行表示。我们发现，原序列中一定恰好有 $4$ 个 $1$。

根据题目，翻转操作就是对两个端点采取异或运算。不妨把所有这样的两个端点连上一条边权为 $r-l+1$ 的边，我们发现，一条路径也就等价于对路径的两个端点进行翻转操作（中间的恰好翻转两次，抵消掉了）。

而我们的路径，必定是每次选择恰好两个 $1$ 进行翻转，否则必然不比这样优。

考虑预处理出每个 $1$ 之间两两的最短路，手动枚举一下 $3$ 种情况即可。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); ++i)
#define FR(i, a, b) for(int i = (a); i >= (b); --i)
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
const ll INF = 1e17;
struct E{int v, w;}; vector<E> e[N];
int n, m, a[6], s[6], vis[N]; ll ans = INF, d[3][N];
priority_queue<pair<ll, int> > q;
void dijkstra(int s, ll dis[]){
    fill(vis + 1, vis + n + 1, 0);
    fill(dis + 1, dis + n + 1, INF);
    q.push(make_pair(dis[s] = 0, s));
    while(!q.empty()){
        int u = q.top().second; q.pop();
        if(vis[u]) continue; vis[u] = 1;
        for(const auto &p: e[u]){
            if(dis[u] + p.w < dis[p.v])
                q.push(make_pair(-(dis[p.v] = dis[u] + p.w), p.v));
        }
    }
}
int main(){
    scanf("%d", &s[0]), a[0] = 1;
    FL(i, 1, 4){
        scanf("%d", &s[i]);
        s[i] += s[i - 1], a[i] = s[i - 1] + 1;
    }
    n = s[4] + 1, scanf("%d", &m);
    FL(i, 1, m){
        int l, r; scanf("%d%d", &l, &r);
        e[l].emplace_back((E){r + 1, r - l + 1});
        e[r + 1].emplace_back((E){l, r - l + 1});
    }
    FL(i, 1, 3) dijkstra(a[i], d[i - 1]);
    ans = min(ans, d[0][a[2]] + d[2][a[4]]);
    ans = min(ans, d[0][a[3]] + d[1][a[4]]);
    ans = min(ans, d[0][a[4]] + d[1][a[3]]);
    printf("%lld\n", ans >= INF? -1 : ans);
    return 0;
}
```

---

## 作者：PPL_ (赞：4)

# 前言

考场上想出$\text{dijkstra}$的是魔鬼吧

~~毫无防备地流下了属于真正弱者的泪水.jpg~~

# 题目

[洛谷](https://www.luogu.com.cn/problem/AT1252)

# 讲解

所有的 I 被我换成了$1$，而 O 换成了$0$

## 暴力

从考场思路开始吧

首先有显而易见的结论：

1.选择的操作顺序不影响答案

2.每个操作重复做没有意义

好了，这就是我们暴力的基础

$2^n$枚举操作，判断是否成立，取时间最小值即可

我是用$bitset$实现的，这里代码就不给出了

## 正解

**差分** & **最短路**

区间修改？好难啊！ -> 差分！单点修改

如果当前点和前一个点不一样，取$1$，反之取$0$

如样例可这样变化：

$100111000011111$

$010100100010000$

现在我们只需将所有的$1$改为$0$即可

上面所对应的$1$的位置为：

A+1 , A+B+1 , A+B+C+1 , A+B+C+D+1

由于差分后变为单点修改，那么我们的修改操作也变为了两个点的单点修改

即$u,v$的区间修改变为了$u,v+1$的单点修改

记上面对应的$1$的位置为$a,b,c,d$

我们就有三个修改方案：$ab\ \&\ cd\ ,\ ac\ \&\ bd\ ,\ ad\ \&\ bc$

而修改两个点的最小代价就可以用最短路算法$\text{dijkstra}$求得

由于起点只有$a,b,c$三个点，所以我们需要跑三次$\text{dijkstra}$

最后答案取最小值就好了

# 坑点

1. 注意开$\text{long long}$

2. 空间要开$5e5$而非$1e5$

3. 答案输出要**换行**! ($\text{AT}$老题特性)

# 代码
```cpp
//12252024832524
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std; 

typedef long long LL;
const int MAXN = 500005;
const LL INF = 0x3f3f3f3f3f3f3f3f;
int n,init[6];
LL dis[3][MAXN],ans = INF;
struct node
{
	int x;
	LL d;
	node(){}
	node(int x1,LL d1){
		x = x1;
		d = d1;
	}
	bool operator < (const node &px) const{
		return d >= px.d;
	}
};

int Read()
{
	int x = 0,f = 1;char c = getchar();
	while(c > '9' || c < '0'){if(c == '-')f = -1;c = getchar();}
	while(c >= '0' && c <= '9'){x = (x*10) + (c^48);c = getchar();}
	return x * f;
}
void Put1(LL x)
{
	if(x > 9) Put1(x/10);
	putchar(x%10^48);
}
void Put(LL x,char c = -1)
{
	if(x < 0) putchar('-'),x = -x;
	Put1(x);
	if(c >= 0) putchar(c);
}
template <typename T>T Max(T x,T y){return x > y ? x : y;}
template <typename T>T Min(T x,T y){return x < y ? x : y;}
template <typename T>T Abs(T x){return x < 0 ? -x : x;}

int head[MAXN],tot;
struct edge
{
	int v,val,nxt;
}e[MAXN << 1];
void Add_Edge(int x,int y,int z)
{
	e[++tot].v = y;
	e[tot].val = z;
	e[tot].nxt = head[x];
	head[x] = tot;
}
void Add_Double_Edge(int x,int y,int z)
{
	Add_Edge(x,y,z);
	Add_Edge(y,x,z);
}
void dij(int s,LL *DIS)
{
	priority_queue<node> q;
	q.push(node(s,0));
	DIS[s] = 0;
	while(!q.empty())
	{
		node t = q.top();
		q.pop();
		if(t.d > DIS[t.x]) continue;
		for(int i = head[t.x]; i ;i = e[i].nxt)
		{
			if(DIS[e[i].v] > DIS[t.x] + e[i].val) 
			{
				DIS[e[i].v] = DIS[t.x] + e[i].val;
				q.push(node(e[i].v,DIS[e[i].v]));
			}
		}
	}
}

int main()
{
//	freopen("cards.in","r",stdin);
//	freopen("cards.out","w",stdout);
	memset(dis,INF,sizeof(dis));
	for(int i = 1;i <= 5;++ i) init[i] = Read() + init[i-1];
	n = Read();
	for(int i = 1,u,v;i <= n;++ i) u = Read(),v = Read(),Add_Double_Edge(u,v+1,v-u+1);
	dij(init[1]+1,dis[0]);//A
	dij(init[2]+1,dis[1]);//B
	dij(init[3]+1,dis[2]);//C
	ans = Min(ans,dis[0][init[2]+1] + dis[2][init[4]+1]);//AB & CD
	ans = Min(ans,dis[0][init[3]+1] + dis[1][init[4]+1]);//AC & BD
	ans = Min(ans,dis[0][init[4]+1] + dis[1][init[3]+1]);//AD & BC
	if(ans == INF) Put(-1,'\n');
	else Put(ans,'\n');
	return 0;
}
```

---

## 作者：HeRaNO (赞：2)

原版题解移步[这里](https://www.ioi-jp.org/camp/2015/2015-sp-tasks/2015-sp-d1-ioioi_cards-review.pdf)。

## Overview
- 主要算法：差分，最短路算法;
- 时间复杂度：$\mathcal{O}(N\log N)$；
- 空间复杂度：$\mathcal{O}(A+B+C+D+E)$。

## Subtask 1
通过观察，可以发现操作顺序对于最后结果没有影响。重要的是各个位置被反转几次。同一个操作的使用不会多于一次，因为翻两次就回到原来状态了。

于是可以想到一个朴素的暴搜，先用 $\mathcal{O}(2^N)$ 的时间决定使用哪些操作，然后检查操作后的卡片序列是否符合要求，这样记 $S=A+B+C+D+E$，于是朴素暴力的复杂度是 $\mathcal{O}(S\times 2^N)$ 的，过不去。

我们知道，`I` 要翻偶数次，`O` 要翻奇数次，因此判断一下我们选出的操作区间是不是覆盖了偶数次 `I` 区间，奇数次 `O` 区间即可。对于这个问题，原题解提出：「压缩区间」，将复杂度降为 $\mathcal{O}(2^N\times N\log N)$，可以通过第一个子任务。

~~不知道 Chtholly Tree 能不能做……~~
## Subtask 2,3
当然我们还需要优化，这里引入差分序列。

这里构造的差分序列是：从第二位起，这一位与之前一位相同，则写 $0$，否则写 $1$。观察可知，只有四个位置为 $1$，其余位置均为 $0$。

可以发现，一次翻转只改变两个位置的值，即 $l$ 和 $r+1$。取反即可。

于是我们只需要把差分序列中 $A+1,A+B+1,A+B+C+1,A+B+C+D+1$ 这 $4$ 个位置的值经过操作后变为 $0$ 即可。

把差分序列中每一个元素看成一个点，$A+1,A+B+1,A+B+C+1,A+B+C+D+1$ 两两看成起点和终点，把每次修改看成两点之间的一条边，边权为修改的代价，每次修改意味着将通过的边相连的两个点取反。可以发现只有起点和终点经过一次，其余经过点都经过两次，于是其余点与之前的点相同关系不变，只有起点和终点变了，而且只能变成相同，对于这个图，求其最短路即为最小代价。

对于原序列的第一个位置，可以不用考虑，因为第一个位置确定为 `I`,并且算法中并不需要原序列第一个元素与其前一个元素的差分值。

对于 Subtask 2，用 Floyd 求最短路，时间复杂度为 $\mathcal{O}(S^3)$。

用堆优化的 Dijkstra 算法可以通过全部测试数据，我们发现差分序列中最多只有 $2N$ 个点对于我们有用，因此时间复杂度为 $\mathcal{O}(N\log N)$。

代码如下
```cpp
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAXM 100005
#define MAXN 500005
#define pi pair<long long,int>
#define mp make_pair
using namespace std;

const long long inf=0x3f3f3f3f3f3f3f3fLL;

struct link
{
    int to;long long val;int nxt;
};

link e[MAXM<<1];
int head[MAXN],cnt;
int A,B,C,D,E,T,n,l,r;
priority_queue <pi,vector <pi >,greater<pi > > q;
long long dis[MAXN],ans=inf;

inline long long mymin(long long a,long long b){return a<b?a:b;}

inline void add(int u,int v,long long w)
{
    e[cnt]=(link){v,w,head[u]};head[u]=cnt++;
    e[cnt]=(link){u,w,head[v]};head[v]=cnt++;
}

inline long long Dijkstra(int S,int T)
{
    memset(dis,0x3f,sizeof dis);q.push(mp(0LL,S));dis[S]=0LL;
    while (!q.empty())
    {
        int x=q.top().second;q.pop();
        for (int i=head[x];~i;i=e[i].nxt)
            if (dis[e[i].to]>dis[x]+e[i].val)
            {
                dis[e[i].to]=dis[x]+e[i].val;
                q.push(mp(dis[e[i].to],e[i].to));
            }
    }
    return dis[T];
}

inline void read(int &x)
{
    x=0;char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return ;
}

int main()
{
    memset(head,-1,sizeof head);
    read(A);read(B);read(C);read(D);read(E);
    B+=A;C+=B;D+=C;E+=D;++A;++B;++C;++D;
    read(n);
    for (int i=1;i<=n;i++)
        read(l),read(r),add(l,r+1,r-l+1);
    ans=mymin(ans,Dijkstra(A,B)+Dijkstra(C,D));
    ans=mymin(ans,Dijkstra(A,C)+Dijkstra(B,D));
    ans=mymin(ans,Dijkstra(A,D)+Dijkstra(B,C));
    if (ans==inf) puts("-1");
    else printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Anaxagoras (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT1252)

Update:2022.09.07 修改了一些错别字

### 0x00 前言

这题差分是很容易想到的，但是 dijkstra 是什么东西啊！！！

本篇题解是根据样例来讲解的。

### 0x01 思路

这题是区间修改，如果真的一个一个改不爆掉才怪。这时候我们想到了：

**差分数组！**

这样我们就可以单点修改左端点与右端点加 $1$ 了，用 $\Theta(1)$ 代替掉了 $\Theta(n)$。

可是修改方式的枚举时间复杂度也很高啊。

我们把序列变化一下，如果当前卡牌与前面卡牌正反一样，则为 $1$，否则为 $0$（特别的，第 $1$ 张我们认为它与第 $0$ 张一样），则原序列为：

`IOOIIIOOOOIIIII`

变换后则为：

$101011011101111$

显而易见，我们只需要把每一个 $0$ 变成 $1$ 即可。并且我们可以发现一个美妙的性质：$0$ 一定只有 $4$ 个，且一定在 $A+1,A+B+1,A+B+C+1,A+B+C+D+1$。这个性质对求解有什么用呢？

我们可以跑 dijkstra！

将修改操作抽象成边，每张卡牌抽象成点，最短路即是最优解。

记上面 $0$ 的点序号分别为 $a,b,c,d$，则一共有 $3$ 个修改方案：

1. $ab,cd$

1. $ac,bd$

1. $ad,bc$

上面每一个对中，第一个字母为起点，第二个字母为终点，一共有 $a,b,c$ 三个起点，所以我们要跑 $3$ 次 dijkstra。

### 0x02 注意

1. 十年 OI 一场空，不开 long long 见祖宗

1. 数组开到 $10^5$ 不够，要开到 $5\times10^5$；

### 0x03 AC Code

```cpp
//by olkieler
#include <bits/stdc++.h>
#define int long long
#define linf LLONG_MAX
#define iinf INT_MAX
#define ios ios::sync_with_stdio(0);cin.tie(0);
#define N 500005
#define M 300005
#define mod 1000000007
#define pint pair<int, int>
#define mp make_pair
using namespace std;
priority_queue<pint, vector<pint>, greater<pint> >q;
struct node
{
    int next;
    int value;
    int pointer;
};
node edge[N << 1];
int tot;
int head[N];
int a[7];
int dis[3][N];
inline void add(int u, int v, int w)
{
    edge[++ tot].next = v;
    edge[tot].value = w;
    edge[tot].pointer = head[u];
    head[u] = tot;
}
inline void dijkstra(int s, int rk)
{
    while (!q.empty())
    {
        q.pop();
    }
    q.push(mp(0, s));
    dis[rk][s] = 0;
    while (!q.empty())
    {
        pint ls = q.top();
        q.pop();
        if (ls.first > dis[rk][ls.second])
        {
            continue;
        }
        for (int i = head[ls.second]; i; i = edge[i].pointer)
        {
            int y = edge[i].next;
            if (dis[rk][y] > dis[rk][ls.second] + edge[i].value)
            {
                dis[rk][y] = dis[rk][ls.second] + edge[i].value;
                q.push(mp(dis[rk][y], y));
            }
        }
    }
}
signed main()
{
    ios;
    memset(dis, 0x3f, sizeof(dis)); 
    int n, ans = 0x3f3f3f3f3f3f3f3f;
    for (int i = 1; i <= 5; i ++)
    {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    cin >> n;
    for (int i = 1; i <= n; i ++)
    {
        int u, v;
        cin >> u >> v;
        add(u, v + 1, v - u + 1);
        add(v + 1, u, v - u + 1);
    }
    dijkstra(a[1] + 1, 0);
    dijkstra(a[2] + 1, 1);
    dijkstra(a[3] + 1, 2);
    ans = min(ans, dis[0][a[2] + 1] + dis[2][a[4] + 1]);
    ans = min(ans, dis[0][a[3] + 1] + dis[1][a[4] + 1]);
    ans = min(ans, dis[0][a[4] + 1] + dis[1][a[3] + 1]);
    if (ans == 0x3f3f3f3f3f3f3f3f)
    {
        cout << "-1\n";
    }
    else
    {
        cout << ans << '\n';
    }
    return 0;
}
```

还有什么不懂的可以私信或评论，不足的可以指正。

---

## 作者：BigJoker (赞：1)

读完题过后感觉这个题目挺魔怔的。

虽然这个操作还是无限次并且很多，但是细想一下每个操作实际上就是选不选的问题，因为一旦执行了每个操作偶数次，就相当于什么都没做，所以无限次本质上是一个无效信息，对于每一个操作，只有选择或者不选这两种状态。所以可以 $2^n$ 枚举选择那些状态，然后进行这些选择的操作。

发现一个很显然的事情，我们只需要在操作完成后查看是否全部相等了，意思是在操作过程中并不需要查询，所以我们让操作所消耗的时间复杂度尽可能小。

只修改，最后才查询，差分是不是就可以支持这样的操作？

每次修改的复杂度为 $\Theta(1)$，查询是 $\Theta(n)$

问题来了，如何差分呢？

在序列求和差分中，我们把 $a_i-a_{i-1}$ 作为差分数组，修改的时候，我们将 $l$ 加上标记，将 $r-1$ 减去标志，最后得到的前缀和就是每一个位置上的数。

我们将 $a_i\oplus a_{i-1}$ 作为差分数组的值，同理的，把 $l$ 上的位置异或一下，把 $r+1$ 位置上的异或一下，然后再求一遍前缀异或，如果异或数组全都是 $0$，那么肯定异或出来后每一位上都是 $0$

我们现在不能思考暴力了，可以来想正解了。

对于初始的序列，只有 $4$ 个位置是 $1$，分别是 $a+1,a+b+1,a+b+c+1,a+b+c+d+1$，我们设这四个位置分别为 $p_1,p_2,p_3,p_4$，我们的目标是通过操作将这些位置上的数都变成 $0$

接着就是这道题最魔怔的地方，最短路。

我们把每次操作都抽象为 $l\rightarrow r+1,r+1\rightarrow l$ 的连边操作。

然后从 $4$ 个点中将两组点分组。

$p_1\rightarrow p_2,p_3\rightarrow p_4$

$p_1\rightarrow p_3,p_2\rightarrow p_4$

$p_1\rightarrow p_4,p_2\rightarrow p_3$

然后分别跑最短路。

其实最短路的过程实际上就是差分修改中，因为只有 $4$ 个点为 $1$，所以对于中间的 $0$ 号点来说，我把它改为了 $1$，肯定还要改回来。

```cpp
#include<bits/stdc++.h>
//#define int long long
#define mem(a,x) memset(a,x,sizeof(a))
#define re register
#define il inline
using namespace std;
typedef long long LL;
const int N=5e5+5;
const LL inf=1e18; 
il int qr(){
	int s=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9') (ch=='-'?f=-1:1),ch=getchar();
	while(ch>='0' && ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*f;
}
il void qw(LL x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) qw(x/10);
	putchar(x%10+'0');
}
int a,b,c,d,f[6],m,vis[N];
LL ans=inf,dis[N];
vector<pair<int,int> >G[N];
struct state{
	int x;
	LL val;
	bool operator<(const state&P)const{
		return val>P.val;
	}
};
LL dij(int s,int t){
	priority_queue<state>q;
	for(re int i=1;i<=f[5]+1;i++) dis[i]=inf,vis[i]=0;
	dis[s]=0,q.push((state){s,0});
	while(!q.empty()){
		state st=q.top();
		q.pop();
		if(vis[st.x]) continue;
		vis[st.x]=1;
		for(re int i=0,to;i<G[st.x].size();i++){
			to=G[st.x][i].first;
			if(dis[to]>dis[st.x]+G[st.x][i].second) dis[to]=dis[st.x]+G[st.x][i].second,q.push((state){to,dis[to]});
		}
	}
	return dis[t];
}
int main(){
	for(re int i=1;i<=5;i++) f[i]=qr()+f[i-1];
	m=qr();
	while(m--){
		int l=qr(),r=qr()+1;
		G[l].push_back(make_pair(r,r-l)),G[r].push_back(make_pair(l,r-l));
	}
	a=f[1]+1,b=f[2]+1,c=f[3]+1,d=f[4]+1,ans=min(ans,min(dij(a,b)+dij(c,d),min(dij(a,c)+dij(b,d),dij(a,d)+dij(b,c))));
	if(ans==inf) ans=-1;
	qw(ans),putchar('\n');
	return 0;
}
```

---

## 作者：Nygglatho (赞：0)

[更好的阅读体验？](https://www.cnblogs.com/Cleshm/p/18117116)

似乎区间修改不是很好做，发现取反有可逆性，考虑差分。

令：$f_i$ 表示 $s_i$ 和 $s_{i-1}$ 是否不同 ($\tt 0/1$）。

然后区间修改就变为了对 $f_{l_i}$ 和 $f_{r_i+1}$ 取反了。

观察得到初始的 $f$ 有一个性质：**只有 $f_1, f_{a+1}, f_{a+b+1}, \cdots$ 为 $1$，其余为 $0$。**

$f_1$ 为 $1$ 不用管。关键是后面的 $1$ 要消掉。

发现性质：$f_x$ 和 $f_y$ 取反，$f_y$ 再和 $f_z$ 取反，相当于 $f_x$ 和 $f_z$ 取反。

于是 $f_{a+1}$ 和 $f_{a+b+1}$ 取反，相当于 $f_{a+1}$ 和其他的数取反，其他的数再和 $f_{a+1}$ 取反。如图。

![](https://s21.ax1x.com/2024/04/11/pFXcAZ4.png)

发现这样很像最短路的节点，考虑求最短路。

具体地，对于每一段 $l_i, r_i$，考虑连一条连通 $l_i, r_{i+1}$ 的无向边。

对于 $f_1, f_{a+1}, f_{a+b+1}, \cdots$ 取反，可以改为 **先两两之间取反再算出总代价**。

由于两两之间取反仅有 $3$ 种可能，$f_{a+1}, f_{a+b+1}$ 和 $f_{a+b+c+1}, f_{a+b+c+d+1}$ 取反，$f_{a+1},f_{a+b+c+1}$ 和 $f_{a+b+1},f_{a+b+c+d+1}$ 取反，$f_{a+1}, f_{a+b+c+d+1}$ 和 $f_{a+b+1},f_{a+b+c+1}$ 取反。

令 $\text{dis}(x,y)$ 代表 $x$ 到 $y$ 最短路，只需要求出：
- $\text{dis}(a+1,a+b+1)+\text{dis}(a+b+c+1,a+b+c+d+1)$
- $\text{dis}(a+1,a+b+c+1)+\text{dis}(a+b+1,a+b+c+d+1)$
- $\text{dis}(a+1,a+b+c+d+1)+\text{dis}(a+b+1,a+b+c+1)$

之后求 $\text{min}$ 即可。使用堆优化 Dijkstra，复杂度 $O(n \log (a+b+c+d+e))$。

```c
#include "bits/stdc++.h"
#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define ll long long
#define ull unsigned long long

#define OPEN freopen (".in", "r", stdin); freopen (".out", "w", stdout);
#define DATA freopen (".in", "w", stdout);

#define pc __builtin_popcount
#define db double
#define pii pair<int, int>
#define fi first
#define se second

#define F(i,x,y) for (int i = (x); i <= (y); ++i)
#define D(i,x,y) for (int i = (y); i >= (x); --i)

using namespace std;

const ll inf = 45ll * 1e17;
const ll mod = 998244353ll;
//const ll mod = 1ll * 1e9 + 7ll;

inline void Rd(int& x) {
	int f = 1; x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') f = -1; c = getchar();}
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c - 48), c = getchar();
	x *= f;
}

inline void Wt(int x) {
	if (x < 10) {putchar(x + 48); return;}
	Wt(x / 10); putchar((x % 10) + 48);
}

int a, b, c, d, e, n, m;

int f[5];

ll minf[5][5];

ll dis[650000];

int cnt;

int hd[560000];

struct Node {
	ll dis;
	
	int x;
	
	bool operator <(const Node& p) const {
		return dis > p.dis;
	}
};

priority_queue<Node> q;

struct Edge {
	int to, nxt;
	ll dis;
}_e[560000];

void addedge(int u, int v, ll d) {
	++ cnt;
	
	_e[cnt].to = v;
	_e[cnt].dis = d;
	_e[cnt].nxt = hd[u];
	hd[u] = cnt;
}

void init() {
	
	F(i, 1, m) dis[i] = inf;
}

void dij(int s) {
	dis[s] = 0ll;
	
	Node _; _.dis = 0ll; _.x = s;
	
	q.push(_);
	
	while (!q.empty()) {
		Node _ = q.top(); q.pop();
		
		int u = _.x;
		
		for (int i = hd[u]; i; i = _e[i].nxt) {
			int v = _e[i].to;
			
			ll d = _.dis + _e[i].dis;
			
			if (dis[v] > d) {
				dis[v] = d;
				
				Node t;
				t.dis = d; t.x = v;
				
				q.push(t);
			}
		}
	}
}

int main() {
	IOS
	
	cin >> a >> b >> c >> d >> e >> n;
	
	m = a + b + c + d + e + 1;
	
	F(i, 1, n) {
		int x, y;
		
		cin >> x >> y;
		
		++ y;
		
		addedge(x, y, 1ll * (y - x));
		addedge(y, x, 1ll * (y - x));
	}
	
	f[1] = a + 1, f[2] = a + b + 1, f[3] = a + b + c + 1, f[4] = a + b + c + d + 1;
	
	F(i, 1, 4) {
		init();
		dij(f[i]);
		F(j, i + 1, 4) minf[i][j] = dis[f[j]];
	}
	
	ll mn = min(minf[1][2] + minf[3][4], min(minf[1][3] + minf[2][4], minf[1][4] + minf[2][3]));
	
	if (mn > inf) cout << "-1\n";
	else cout << mn << '\n';
}
```

---

## 作者：shinkuu (赞：0)

如果你做过 CF79D 你就会把这题秒了。

记 $A+B+C+D+E=m$。

首先区间反转差分一下变成两个点同时反转，然后发现原序列差分序列上只有 $4$ 个 $1$，于是把反转转化成差分数组上 $1$ 的移动。

这是因为差分操作顺序不影响结果，所以每次操作的 $x,y$ 两个位置中，至少有一个 $1$ 才可能是最优的。

最后 $1$ 要不两个移动到同一位置然后相抵消，要不移动到 $m+1$，对原序列没有影响。

于是先预处理 $4$ 个开始的 $1$ 到所有位置的最短路，然后状压 dp 一下当前已经两两抵消的点集为 $S$，花费的最小的代价，再加上剩下点移动到 $m+1$ 的代价即可。

code：

```cpp
int n,m,a[4];
bool vis[N];
ll f[4][4],dis[4][N],dp[1<<5];
int tot,head[N];
struct node{
	int to,nxt,cw;
}e[N<<1];
il void add(int u,int v,int w){
	e[++tot]={v,head[u],w},head[u]=tot;
}
void dij(int s,int p){
	priority_queue<pii> q;
	mems(vis,0);
	dis[p][s]=0,q.emplace(0,s);
	while(q.size()){
		int u=q.top().se;
		q.pop();
		if(vis[u]){
			continue;
		}
		vis[u]=1;
		go(i,u){
			int v=e[i].to;
			if(dis[p][v]<=dis[p][u]+e[i].cw){
				continue;
			}
			dis[p][v]=dis[p][u]+e[i].cw;
			q.emplace(-dis[p][v],v);
		}
	}
}
void Yorushika(){
	int A,B,C,D,E;
	read(A,B,C,D,E,n),m=A+B+C+D+E;
	a[0]=A+1,a[1]=A+B+1,a[2]=A+B+C+1,a[3]=A+B+C+D+1;
	rep(i,1,n){
		int l,r;read(l,r);
		add(l,r+1,r-l+1),add(r+1,l,r-l+1);
	}
	mems(dis,0x3f),mems(f,0x3f),mems(dp,0x3f);
	rep(i,0,3){
		dij(a[i],i);
	}
	rep(i,0,3){
		rep(j,i+1,3){
			rep(k,1,m){
				f[i][j]=min(f[i][j],dis[i][k]+dis[j][k]);
			}
		}
	}
	ll ans=1ll*inf*inf;
	dp[0]=0;
	rep(S,0,15){
		rep(i,0,3){
			rep(j,i+1,3){
				if((S>>i&1)||(S>>j&1)){
					continue;
				}
				dp[S|(1<<i)|(1<<j)]=min(dp[S|(1<<i)|(1<<j)],dp[S]+f[i][j]);
			}
		}
		rep(i,0,3){
			if(S>>i&1){
				continue;
			}
			if(dis[i][m+1]>1e18){
				dp[S]=1ll*inf*inf;
			}else{
				dp[S]+=dis[i][m+1];
			}
		}
		ans=min(ans,dp[S]);
	}
	printf("%lld\n",ans>1e18?-1:ans);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：orz_z (赞：0)

### AT1252 IOIOI カード占い

记原数组为 $01$ 数组。

差分，转化为一堆 $0$ 和 $4$ 个 $1$。

每次区间翻转操作即翻转差分数组两点。

答案即翻转 $4$ 个 $1$ 的最小操作数，转化为操作任意两点和操作另外两次两次操作。

以每个 $1$ 点为起点跑最短路即可，一条路径对应翻转两点。

时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define ha putchar(' ')
#define he putchar('\n')

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * f;
}

inline void write(ll x)
{
	if(x < 0)
	{
		putchar('-');
		x = -x;
	}
	if(x > 9)
		write(x / 10);
	putchar(x % 10 + 48);
}

const int _ = 5e5 + 10;
const ll inf  = 0x3f3f3f3f3f3f3f3f;

int n, a[6];

bool vis[_];

ll dis[3][_], ans = inf;

vector<ll> d[_], w[_];

void dij(int s, ll *di)
{
	memset(vis, 0, sizeof vis);
	priority_queue<pair<ll, int>> q;
	q.push({0, s});
	di[s] = 0;
	while(!q.empty())
	{
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = 0; i < d[u].size(); ++i)
		{
			int v = d[u][i];
			if(di[v] > di[u] + w[u][i])
			{
				di[v] = di[u] + w[u][i];
				if(!vis[v]) q.push({-di[v], v});
			}
		}
	}
}

signed main()
{
	memset(dis, inf, sizeof dis);
	for(int i = 1; i <= 5; ++i) a[i] = read() + a[i - 1];
	n = read();
	for(int i = 1, u, v; i <= n; ++i)
	{
		u = read(), v = read();
		d[u].push_back(v + 1), d[v + 1].push_back(u);
		w[u].push_back(v - u + 1), w[v + 1].push_back(v - u + 1);
	}
	dij(a[1] + 1, dis[0]), dij(a[2] + 1, dis[1]), dij(a[3] + 1, dis[2]);
	ans = min(ans, dis[0][a[2] + 1] + dis[2][a[4] + 1]);
	ans = min(ans, dis[0][a[3] + 1] + dis[1][a[4] + 1]);
	ans = min(ans, dis[0][a[4] + 1] + dis[1][a[3] + 1]);
	write(ans == inf ? -1 : ans), he;
	return 0;
}
```



---

