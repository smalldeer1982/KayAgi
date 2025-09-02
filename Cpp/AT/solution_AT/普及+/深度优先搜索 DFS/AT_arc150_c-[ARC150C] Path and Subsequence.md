# [ARC150C] Path and Subsequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc150/tasks/arc150_c

$ N $ 頂点 $ M $ 辺の連結無向グラフ $ G $ があります。頂点には $ 1 $ から $ N $ の番号がついています。$ i $ 番目の辺は頂点 $ U_i,\ V_i $ を結びます。

また、長さ $ N $ の整数列 $ A=(A_1,\ A_2,\ \dots,\ A_N) $ 、および長さ $ K $ の整数列 $ B=(B_1,\ B_2,\ \dots,\ B_K) $ が与えられます。

$ G,\ A,\ B $ が以下の条件を満たすか判定してください。

- $ G $ における頂点 $ 1 $ から $ N $ への任意の単純パス $ v=(v_1,\ v_2,\ \dots,\ v_k)\ (v_1=1,\ v_k=N) $ に対し、$ B $ は $ (A_{v_1},\ A_{v_2},\ \dots,\ A_{v_k}) $ の（連続とは限らない）部分列になる。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ K\ \leq\ N $
- $ N-1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ U_i\ <\ V_i\ \leq\ N $
- $ i\ \neq\ j $ ならば $ (U_i,\ V_i)\ \neq\ (U_j,\ V_j) $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- 入力される値はすべて整数
- 与えられるグラフ $ G $ は連結

### Sample Explanation 1

頂点 $ 1 $ から頂点 $ 6 $ への単純パスは $ (1,\ 2,\ 4,\ 6),\ (1,\ 3,\ 5,\ 6) $ の $ 2 $ 通りであり、これらに対する $ (A_{v_1},\ A_{v_2},\ \dots,\ A_{v_k}) $ はそれぞれ $ (1,\ 2,\ 5,\ 6),\ (1,\ 4,\ 2,\ 6) $ です。 これらはいずれも $ B=(1,\ 2,\ 6) $ を部分列に持つので答えは `Yes` です。

### Sample Explanation 2

頂点 $ 1 $ から頂点 $ 5 $ への単純パスである $ (1,\ 2,\ 5) $ に対する $ (A_{v_1},\ A_{v_2},\ \dots,\ A_{v_k}) $ は $ (1,\ 2,\ 2) $ であり、これは $ B=(1,\ 3,\ 2) $ を部分列に持ちません。

## 样例 #1

### 输入

```
6 6 3
1 2
1 3
2 4
3 5
4 6
5 6
1 2 4 5 2 6
1 2 6```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5 5 3
1 2
2 3
3 4
4 5
2 5
1 2 3 5 2
1 3 2```

### 输出

```
No```

## 样例 #3

### 输入

```
10 20 3
5 6
5 10
5 7
3 5
3 7
2 6
3 8
4 5
5 8
7 10
1 6
1 9
4 6
1 2
1 4
6 7
4 8
2 5
3 10
6 9
2 5 8 5 1 5 1 1 5 10
2 5 1```

### 输出

```
Yes```

# 题解

## 作者：do_while_true (赞：4)

由于子序列匹配是贪心能匹配就匹配，所以想要判断一个点 $u$ 是否有一条到 $n$ 的失配的路径，最优一定是选择已经匹配个数最少的那条路径继续往后走。

所以令 $dis_u$ 为 $1$ 点走到 $u$ 点是最短已经匹配到了 $B$ 的哪个前缀。然后 $(u,v)\in E$ 则更新 $dis_v\gets dis_u+[B_{dis_u+1}=A_v]$．如果注意到边权仅与 $dis_u$ 有关而与 $u$ 无关，所以每个点只有在第一次时被松弛才是有用的，故 Dijkstra 时间复杂度为 $\mathcal{O}(N\log N+M+K)$，使用 01 bfs 的时间复杂度为 $\mathcal{O}(N+M+K)$．

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n'
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n'
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
#define Win do{puts("Yes");return ;}while(0)
#define Lose do{puts("No");return ;}while(0)
#define Alice do{puts("Alice");return ;}while(0)
#define Bob do{puts("Bob");return ;}while(0)
#define Line cerr << "----------\n"
const int N=200010;
const int inf=0x7fffffff;
int n,m,k,a[N],b[N];
int dis[N],vis[N];
vi eg[N];
void solve(){
	read(n,m,k);
	for(int i=1,x,y;i<=m;i++){
		read(x,y);
		eg[x].pb(y);
		eg[y].pb(x);
	}
	for(int i=1;i<=n;i++)read(a[i]),dis[i]=inf;
	for(int i=1;i<=k;i++)read(b[i]);
	dis[1]=a[1]==b[1];
	priority_queue<pii,vector<pii>,greater<pii>>q;
	q.push(mp(dis[1],1));
	while(!q.empty()){
		int x=q.top().se;q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(auto v:eg[x]){
			int w=dis[x]+(a[v]==b[dis[x]+1]);
			if(dis[v]==inf)dis[v]=w,q.push(mp(dis[v],v));
		}
	}
	if(dis[n]>=k)Win;
	Lose;
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	int T=1;
//	read(T);
	while(T--){
		solve();
//		Line;
	}
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：luxiaomao (赞：1)

## 前言（~~废话~~）

竟然交了一次就过，激动~赶紧整理了一下思路，发个题解。

## 算法选择

[这道题](https://www.luogu.com.cn/problem/AT_arc150_c#submit)是一道练习最短路算法的好题。

首先我们发现，要求解的答案和“从 $1$ 到 $n$ 的所有路径”有关，再看看数据范围——嗯很正常，那么这道题可以用单源最短路实现。

由于“匹配数量”这类数据只可能是非负整数，所以不可能出现负权的情况，排除 SPFA（~~它死了~~），我们使用亲爱的 dijkstra 算法。

为防止有同学没接触过这种算法，推荐一篇[讲最短路算法的 blog](https://oi-wiki.org/graph/shortest-path/)。

## 题目分析

其实这道题的难点在于：**怎样将匹配数量和最短路连接起来呢？**

啪黑板！

题目要求的是：“是否「所有从 $1$ 到 $n$ 的路径上依次经过的点的点权形成的序列」都含有 $B$ 作为子序列？”

那么，“含有 $B$ 作为子序列”可以表述为“能够匹配 $k$ 个 $B$ 中的数据”！

这说明，在所有从 $1$ 到 $n$ 到路径中，如果有路径“匹配 $B$ 数据的数量”不足 $k$，那么就应输出 ```No```！

既然如此，我们便从所有从 $1$ 到 $n$ 的路径中找出匹配量最小的，如果它小于 $k$，那么输出 ```No```，否则输出 ```Yes```。

我们用 $dis_i$ 表示从 $1$ 到 $i$ 的路径中最少能匹配几个序列 $B$ 中的数据，诶等等，那将匹配数量转化为了边权，这不就是 dijkstra 吗？

那么这道题的思路就是这样啦！

## 代码实现

给大家送上代码，自己感觉码风还是比较干净的。只可理解，不可抄袭哦!

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;

int n,m,k;
vector<int> mp[N];
int a[N],b[N];

priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
bool vis[N];
int dis[N];

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i <= m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		mp[u].push_back(v);
		mp[v].push_back(u);
	}
	for(int i = 1;i <= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i <= k;i++)scanf("%d",&b[i]);
		
	for(int i = 2;i <= n;i++)dis[i] = k+1;
	dis[1] = (a[1] == b[1]);
	q.push(make_pair(dis[1],1));
	
	while(!q.empty())
	{
		int u = q.top().second;
		q.pop();
		if(vis[u])continue;
		vis[u] = 1;
		
		for(int i = 0;i < (int)mp[u].size();i++)
		{
			int v = mp[u][i];
			if(dis[u] < dis[v])
			{
				dis[v] = dis[u] + (a[v]==b[dis[u]+1]);
				q.push(make_pair(dis[v],v));	
			}
		}
	}
	printf("%s\n",dis[n]==k?"Yes":"No");
	return 0;
}
```
PS：这是本蒟蒻的第三篇题解，看在我写得这么认真，管理员大大给过吧 QAQ!

---

## 作者：CrTsIr400 (赞：0)

题意：一张 $n$ 个点 $m$ 边的图，点有点权 $A_i$ ，求找出一条 $1\to n$ 的路径使得 $B$ 序列不是路径上所有点权组成的子序列。$n\le 10^5$ 。

题解：可以观察到这样的路径取简单路径一定比走一遍或者两遍环会更优。

观察子序列自动机算法，它是到了某个位置匹配到 $B$ 的第几位，越高越好。

因为本题之中要不能使该路径匹配，进而推出从起点到了某一个点匹配 $B$ 中元素越少越好。

所以设置 $d[x]$ 为从 $1$ 到达 $x$ 路径最少匹配到 $B$ 的第 $d[x]$ 位。转移易，使用 dijkstra 算法计算最短路即可。

```cpp
const I maxn=1e5+10,maxm=4e5+10;
I d[maxn],n,m,k,a[maxn],b[maxn];
I Ey[maxm],NX[maxm],HD[maxn],Ec;
void conn(I x,I y){
	Ey[++Ec]=y;NX[Ec]=HD[x];HD[x]=Ec;
}priority_queue<pair<I,I> >pq;
bool bz[maxn];
int main(){
	in(n,m,k);
	for(I i=1,x,y;i<=m;++i){
		in(x,y);
		conn(x,y);
		conn(y,x);
	}for(I i=1;i<=n;++i)in(a[i]);
	for(I i=1;i<=k;++i)in(b[i]);
	b[k+1]=-inf;
	memset(d,0x3f,sizeof(d));
	d[1]=(a[1]==b[1])?1:0;
	pq.push(make_pair(-d[1],1));
	while(pq.size()){
		I x=pq.top().second,y,z;pq.pop();
		if(bz[x])continue;
		bz[x]=1;
		for(I i=HD[x];i;i=NX[i]){
			y=Ey[i];
			if(d[y]>d[x]+(z=(a[y]==b[d[x]+1]?1:0))){
				d[y]=d[x]+z;
				pq.push(make_pair(-d[y],y));
			}
		}
	}puts(d[n]==k?"Yes":"No");
	return 0;
}

```

---

## 作者：Missa (赞：0)

- 庆祝 AT 复活，从做题记录中搬一道最近的题当题解。
- 题意简述：给定一个数组 $B$ 和一张点带点权的图，询问是否「所有从 $1$ 到 $n$ 的路径上依次经过的点的点权形成的序列」都含有 $B$ 作为子序列。
- 如何判断一个串 $S$ 是否是另一个串 $T$ 的子序列？考虑逐位匹配 $T$ 和 $S$，开一个计数数组 $cnt$，表示 $T[1 \dots n]$ 最多和 $S$ 匹配几位，转移 $cnt_i = cnt_{i-1} + [S_{cnt_{i-1}+1}=T_i]$。
- 现在是所有了，怎么做呢？
- 直接修改状态为最少匹配几位，查看答案是否与 $B$ 数组等长即可。
- 状态转移应变成 $\min$。
- 这是无向图，不应草率按照节点与原点最短路排序处理，而应该贪心地选择 $cnt_i$ 最小的节点进行转移，使得这个节点一定不会被后面更新。（无有效性）
- 最后的转移公式 $cnt_u = \min \{ {cnt_v + [A_u = B_{cnt_v+1}]} \}$，$A$ 为点权数组。注意这里的更新顺序是用 $v$ 更新 $u$。
- [code](https://atcoder.jp/contests/arc150/submissions/35573816)

---

## 作者：mountain_climber (赞：0)

~~感觉比B简单~~

题意：判断所有 $1$ 到 $n$ 的简单路径上依次经过的点权序列是否都满足序列 $B$ 是其子序列。

考虑正难则反。

变为判断是否存在一个 $1$ 到 $n$ 的简单路径，其依次经过的点组成的序列不满足 $B$ 是其子序列。

考虑如果存在这样的路径，那么这条路径一定可以是跟 $B$ 匹配最少的路径。

反之如果跟 $B$ 匹配最少的路径也全部与 $B$ 匹配，则说明不存在这样一条满足新判断条件的路径。（即满足题意条件）

于是变成求从 $1$ 到 $n$ 与 $B$ 匹配最少的路径的匹配数量。

发现是类似最短路的。

我们使 $dis_u$ 表示 $1$ 到 $u$ 最少与 $B$ 匹配的长度。每次拿一个点去松弛别的点的时候，如果这点能够继续匹配，那么边权就是 $1$，否则边权就是 $0$。显然，我们直接跑 Dijsktra 就行了。当然，由于边权只可能是 $0$ 或 $1$，所以使用 0-1bfs 也能够维护。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,k,v[N],b[N],dis[N];
vector<int> g[N];
bool vis[N]={false};
struct node{
    int d;
    int u;
    bool operator >(const node& x) const{
        return d>x.d;
    }
};
priority_queue<node,vector<node>,greater<node> > q;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL),cout.tie(NULL);
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        cin>>v[i];
    }
    for(int i=1;i<=k;i++){
        cin>>b[i];
    }
    for(int i=1;i<=n;i++){
        dis[i]=k+1;
    }
    dis[1]=v[1]==b[1];
    q.push({dis[1],1});
    while(q.size()){
        node tp=q.top();
        q.pop();
        if(!vis[tp.u]){
            vis[tp.u]=true;
            for(auto i:g[tp.u]){
                if(dis[i]>dis[tp.u]+(v[i]==b[dis[tp.u]+1])){
                    dis[i]=dis[tp.u]+(v[i]==b[dis[tp.u]+1]);
                    q.push({dis[i],i});
                }
            }
        }
    }
    cout<<(dis[n]==k?"Yes\n":"No\n");
    return 0;
}
```

---

