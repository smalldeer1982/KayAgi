# [POI 2007] ATR-Tourist Attractions

## 题目背景

[English Edition](/paste/gu4ksinh)

## 题目描述

给出一张有 $n$ 个点 $m$ 条边的无向图，每条边有边权。  

你需要找一条从 $1$ 到 $n$ 的最短路径，并且这条路径在满足给出的 $g$ 个限制的情况下可以在所有编号从 $2$ 到 $k+1$ 的点上停留过。

每个限制条件形如 $r_i, s_i$，表示停留在 $s_i$ 之前必须先在 $r_i$ 停留过。

**注意，这里的停留不是指经过**。

## 说明/提示

对于 $100\%$ 的数据， 满足：
- $2\le n\le2\times10^4$
- $1\le m\le2\times10^5$
- $0\le k\le\min(20, n-2)$
- $1\le p_i<q_i\le n$
- $1\le l_i\le 10^3$
- $r_i, s_i \in [2,k+1], r_i\not=s_i$
- 保证不存在重边且一定有解。

## 样例 #1

### 输入

```
8 15 4
1 2 3
1 3 4
1 4 4
1 6 2
1 7 3
2 3 6
2 4 2
2 5 2
3 4 3
3 6 3
3 8 6
4 5 2
4 8 6
5 7 4
5 8 6
3
2 3
3 4
3 5```

### 输出

```
19```

# 题解

## 作者：BJpers2 (赞：28)

这道题目自从改了空间限制以后就没几个人自己写程序过掉的，最近AC也几乎都是抄的POI的官方题解。就连两位楼主的代码在新的空间（64MB）之下也是无法通过的。

根据传统状压DP,多数人都选择用一个数组直接记录所有状态下的最优解。但无论怎么压缩都是不会低于$1048576 \times 20 \times 4B=80MB$，一定是会爆空间的。

于是有很多人觉得此题不可做，或者就指责管理员。管理员依照原题设定空间限制可以理解，但也没有给出不爆空间就AC的解决方案。

实际上这个问题是有解决方案的，而且这个方案不需要什么奇技淫巧，用一个$01$背包中常用的技巧就够了。这也是几乎所有DP中惯用的节省空间的技巧。

**滚动数组。**

滚动数组应用的条件是DP阶段之间之间存在拓扑序。更直白地说就是$DAG$上分层。
所有转移只从上一层转移到下一层，不会跨层转移，也不会层内转移。

放到原问题中，这个性质显然是满足的，假如$k$的二进制中有$x$个$1$,那$f[u][k]$能转移到的所有状态$f[v][k']$中,$k'$的二进制内一定有且仅有$x+1$个$1$。

那么我们对所有的二进制数做$1$的数量的分组，二进制中含相同数目$1$的分到同一组。然后每次从上一组转移到下一组。接着就是滚动数组的套路，把上一层腾出来更新更下面一组即可。可以数学的算出一组中的二进制数个数最大为$$C_{20}^{10} =184756$$

这样我们只要开$f[maxK][C_{20}^{10}][2]$的数组就够了。
它的大小是$20 \times 184756 \times 2 \times 4B < 30MB$这样就可以通过
了。

```
#include<iostream>
#include<cstdio>
#include<set>
#include<queue>
#define pr make_pair
#define fr first
#define sc second
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(u) for(int i=hd[u],v=e[i].v,w=e[i].w;i;i=e[i].n,v=e[i].v,w=e[i].w)
#define REQ(u) for(int i=Hd[u],v=E[i].v,w=E[i].w;i;i=E[i].n,v=E[i].v,w=E[i].w)
using namespace std;
typedef long long ll;
typedef pair<int,int> p;
const int N=50050,M=1050000,INF=1000010000,TK=23,S=190000;
struct edge{int n,v,w;}e[M],E[M];
int n,m,K,u,v,w,fl,Fl,to[TK],id[M];
int fa[N],hd[N],Hd[N],g[N],d[TK][N],f[TK][S][2],ans=INF;
set< p >h;
queue< p >q;
void add(int u,int v,int w){e[++fl]=(edge){hd[u],v,w};hd[u]=fl;}
void Add(int u,int v,int w){E[++Fl]=(edge){Hd[u],v,w};Hd[u]=Fl;}
void dijkstra(int x){
	FOR(i,1,n) d[x][i]=INF;
	d[x][x]=0;
	h.insert(p(0,x));
	while(h.size()){
		u=h.begin()->second;h.erase(h.begin());
		REP(u)if(d[x][u]+w<d[x][v]){
			if(d[x][v]<INF) h.erase(p(d[x][v],v));
			d[x][v]=d[x][u]+w;
			h.insert(p(d[x][v],v));
		}
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&K);K++;
	FOR(i,1,m) scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
	scanf("%d",&m);
	FOR(i,1,m) scanf("%d%d",&u,&v),g[v]|=(1<<u-2);
	FOR(i,1,K) dijkstra(i);
	FOR(i,2,K) g[i]|=(1<<i-2);
	if(K==1) {printf("%d",d[1][n]);return 0;}
	FOR(k,1,(1<<K-1)-1){int cn,tm;for(cn=0,tm=k;tm;tm-=(tm&-tm),cn++);Add(cn,k,0);id[k]=++to[cn];}
	FOR(j,1,K-1)REQ(j){
		FOR(u,2,K) f[u][id[v]][j&1]=INF;
		FOR(u,2,K)if((g[u]|v)==v){
			if(v-(v&-v)>0){
				FOR(x,2,K)if((1<<x-2&v) && x!=u)
					f[u][id[v]][j&1]=min(f[u][id[v]][j&1],f[x][id[v^(1<<u-2)]][j&1^1]+d[x][u]);
			}
			else f[u][id[v]][j&1]=d[1][u];
			if(v==(1<<K-1)-1) ans=min(ans,f[u][id[v]][j&1]+d[u][n]);
		}
	}
	printf("%d",ans);
}/*
8 15 4
1 2 3
1 3 4
1 4 4
1 6 2
1 7 3
2 3 6
2 4 2
2 5 2
3 4 3
3 6 3
3 8 6
4 5 2
4 8 6
5 7 4
5 8 6
3
2 3
3 4
3 5
*/
```

---

## 作者：H_D_NULL (赞：14)

#### 注：如果连这道题暴力状压的写法都不会，推荐先去康题解区的“错误”代码（大雾）

> ......写完状压以后自然是传统 OI 点到为止，保留 SPFA 把 Dij 注释掉，我笑一下决定 AC ，因为这时间，按照传统 OI 电刀喂纸他已经输了。如果用 Dij ，再强的数据也卡不掉我的时间了......我提交不优化了，他突然袭击，来卡我空间，啊，我大意了啊，没有卡空间......♂啊，看来是，有 bear 而来！
 

$K_{max}=20$ ，状压无疑，预处理出要经过的城市的单源最短路（类似一道叫新年好的题）；

按照传统的状压 DP ，状态应设为 $f[k][S]$ ：遍历集合为 $S$ 的点后（以下简称点集），停在 $k$ 点所走的最短路程，因为起始城市必为 1，终止城市为 n，故这两个点不计入状态，统计答案时特别处理即可；

但是我们发现即便如此，空间也会炸（其他题解说得很清楚了），所以考虑优化；

### 舍去冗余状态

要优化空间，最好的方式即是舍去冗余状态，比如滚动数组，但是一般的状压 DP 线性枚举点集，而状态并不线性转移，故无法直接滚动；

我们分析一下本题状态转移的实质以便优化。枚举到任意点集时，我们从中继续枚举出一点，然后用剩余点组成的点集的答案来优化本点集的答案。不难发现，如此转移状态，**点集中点的数量，即这个数二进制下一的个数，是递增的，且固定+1**，故可以用滚动数组优化；

按照传统状压 DP 无法使用滚动数组的原因是，通过线性枚举的点集，无法保证二进制下一的数量呈单增。为解决这个问题，只需要预处理出符合每个点集数目 $num$（$num \in (0,k]$）的所有点集即可。对于任一 $num$ ，其包含的点集数为 $C{n \atop k}$，最多为 $C{10 \atop 20}=184756$，空间完全可以承受；

### 细节

- 需要按顺序遍历点，具体操作为预处理出走到每个点之前需要遍历的点集，和状态转移时的点集进行位运算（乱搞）判断即可；

- 如果 $k=1$，直接输出起点到终点的最短路；

- （尽量）不要用已死的算法（逃


------------
> 这个出题人不讲武德，来，骗！来，卡常！我六十九岁的老OIer。这好吗？这不好！我劝，这位出题人耗子尾汁，好好反思，以后不要再犯这样的聪明，小聪明，♂啊…OI要以和为贵，要讲污的，不要搞窝里斗，谢谢朋友们！

------------

*Talk is cheap, show me the code*

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;

const int K=22;
const int N=20005;
const int M=200005;

inline int read(){
	re int ret=0;
	re char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9'){
		ret=(ret<<1)+(ret<<3)+(c^48);
		c=getchar();
	} return ret;
}

int n,m,k;

struct Edge{
	int nxt;
	int to;
	int v;
} e[M<<1];

int h[N],cnt;

inline void Add(int x,int y,int v){
	e[++cnt].nxt=h[x];
	e[cnt].to=y;
	e[cnt].v=v;
	h[x]=cnt;
}

int cond[K];
int dis[K][N];

bool vis[N];

#define MK(x,y) make_pair((x),(y))

inline void DIJ(int st) {
    memset(vis,0,sizeof(vis));
    memset(dis[st],63,sizeof(dis[st]));
    priority_queue < pair<int,int> > q;
    dis[st][st]=0; q.push(MK(0,st));
    while(!q.empty()){
        re int l=q.top().second; q.pop();
        if(vis[l]) continue; vis[l]=1;
        for(re int i=h[l],to,v;i;i=e[i].nxt){
            to=e[i].to;
            v=e[i].v;
            if (dis[st][l]+v<dis[st][to]){
                dis[st][to]=dis[st][l]+v;
                q.push(MK(-dis[st][to],to));
            }
        }
    }
}

inline void Init(){
	n=read(); m=read(); k=read()+1;
	for(re int i=1,x,y,v;i<=m;i++){
		x=read(); y=read(); v=read();
		Add(x,y,v); Add(y,x,v);
	} re int T=read();
	for(re int i=1,x,y;i<=T;i++){
		x=read(); y=read();
		cond[y]|=(1<<(x-2)); //处理到达之前需要遍历的点集
	}
	for(re int i=2;i<=k;i++) DIJ(i); //为了省时间，1和n不必处理
}

struct K{
	int nxt;
	int to;
} R[1<<21];

int h_R[K],cnt_R;
int sum[K],bl[1<<21];
int f[2][K][184760];

inline void Add_K(int x,int y){
	R[++cnt_R].nxt=h_R[x];
	R[cnt_R].to=y;
	h_R[x]=cnt_R;
}

#define lowbit(x) ((x)&(-(x)))
#define For(p) for(re int rg=h_R[(p)],to=R[rg].to;rg;rg=R[rg].nxt,to=R[rg].to)
//遍历点个数为p的点集的集合（绕）

inline void Solve(){
	if(k==1){
		DIJ(1); //因为刚刚没处理1
		printf("%d",dis[1][n]);
		return;
	}
	for(re int i=1,num,now;i<1<<(k-1);i++){
		for(num=0,now=i;now;now-=lowbit(now),num++); //求"1"的个数
		Add_K(num,i); bl[i]=++sum[num];//处理编号
	}
	For(1){
		for(re int i=2;i<=k;i++){
			if(to&(1<<(i-2))){
				f[0][i][bl[to]]=dis[i][1]; //从1出发到此的距离
				break;
			}
		}
	}
	re int l=1,ans=1<<30;
	for(re int NUM=2;NUM<k;NUM++,l^=1){
		For(NUM){
			for(re int i=2,now;i<=k;i++){
				if((to&(1<<(i-2)))&&((cond[i]&to)==cond[i])){
					now=to^(1<<(i-2));  f[l][i][bl[to]]=1<<30;
					for(re int j=2;j<=k;j++){
						if((now&(1<<(j-2)))&&((cond[j]&now)==cond[j])){
							if(f[l][i][bl[to]]>f[l^1][j][bl[now]]+dis[i][j]){
								f[l][i][bl[to]]=f[l^1][j][bl[now]]+dis[i][j];
							}
						}
					}
				}
			}
		}
	}
	For(k-1){
		for(re int i=2;i<=k;i++){
			if((to&(1<<(i-2)))&&((cond[i]&to)==cond[i])){
				ans=min(ans,f[l^1][i][bl[to]]+dis[i][n]);//加上从这个点到n的距离
			}
		}
	}
	printf("%d",ans);
}

int main(){
	Init(); Solve();
	return 0;
}
```


---

## 作者：loverintime (赞：13)

本题中文题意略有不清， 再看了英文之后我才知道， 你需要在 $2-k+1$ 这几个城市**停留**， 在这之前可以随意**经过**， 限制条件是对于**停留**而言的。

到这里， 就容易想到状压。 令 $f(s,i)$ 表示现在已经在 $s$ 集合中的城市**停留**， 现在在第 $i$ 个城市的最短路径长度。 令 $u_i$ 表示第 $i$ 个城市的前置集合。 那么 $f(s,i)$ 成立的条件是 $u_i\subset s$， 有转移方程：
$$
f(s,i)=\min_{j\in s-\{i\}}\{f(s-\{i\},j)+dis_{j,i} \}
$$

其中边界条件为 $f(\{i\},i)=dis_{1,i}, ~u_i=\varnothing$。

容易想到先用堆优 $\texttt{dijkstra}$ 跑 $k$ 个点的最短路， 算出两两之间的 $dis$， 就可以开始转移了。

容易发现这样要爆空间， 容易想到滚动数组。 观察转移方程， 发现转移集合 $s$ 需要用到的集合大小只比 $s$ 小 $1$， 那么可以先处理每个集合的元素个数， 把集合大小作为拓扑序， 就可以使用滚动数组了。

时间复杂度： $\Theta(km\log m+2^kk^2)$。

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e4+5,M=2e5+5;
int read(){
	int ans=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while('0'<=c&&c<='9') ans=(ans<<1)+(ans<<3)+c-'0',c=getchar();
	return ans;
}
struct node{
	int v,w;
	bool operator<(const node &b)const{
		return w>b.w;
	}
};
int n,m,k,Q,uset[21];
int tl[21][21],Map[21],kdis[21][2],sum[(1<<20)+1];
int f[2][184757][21],cur,pMap[(1<<20)+1];
vector <int> p[21];
vector <node> s[N];
priority_queue <node> q;
int dis[N];
bool vis[N];
void dijkstra(int S){
	memset(dis,0x3f,sizeof dis);dis[Map[S]]=0;memset(vis,0,sizeof vis);
	q.push({Map[S],0});
	while(!q.empty()){
		node x=q.top();q.pop();
		if(vis[x.v]) continue;
		vis[x.v]=1;
		int len=s[x.v].size();
		for(int i=0; i<len; i++){
			node t=s[x.v][i];
			if(!vis[t.v]&&dis[t.v]>dis[x.v]+t.w){
				dis[t.v]=dis[x.v]+t.w;
				q.push({t.v,dis[t.v]});
			}
		}
	}
	kdis[S][0]=dis[1],kdis[S][1]=dis[n];
	for(int i=0; i<k; i++) tl[S][i]=dis[Map[i]];
}

int main(){
	n=read();m=read();k=read();
	for(int i=1; i<=m; i++){
	    int u=read(),v=read(),w=read();
	    s[u].push_back({v,w});s[v].push_back({u,w});
	}
	if(k==0){
		Map[1]=1;
		dijkstra(1);
		printf("%d\n",dis[n]);
		return 0;
	}
	for(int i=0; i<k; i++){
		Map[i]=i+2;
	}
	for(int s=1; s<(1<<k); s++) sum[s]=sum[s&(~(s&-s))]+1,p[sum[s]].push_back(s),pMap[s]=p[sum[s]].size()-1;
	Q=read();
	while(Q--){
		int u=read(),v=read();
		uset[v-2]|=(1<<(u-2));
	}
	memset(f,0x3f,sizeof f);
	for(int i=0; i<k; i++){
		dijkstra(i);if(!uset[i]) f[0][pMap[1<<i]][i]=kdis[i][0];
	} 
	for(int w=2; w<=k; w++){
		int len=p[w].size();cur^=1;memset(f[cur],0x3f,sizeof f[cur]);
		for(int e=0; e<len; e++){
			int s=p[w][e];
			for(int i=0; i<k; i++) if((s&(1<<i))&&((uset[i]&(s&(~(1<<i))))==uset[i])){
				for(int j=0; j<k; j++) if(i!=j&&(s&(1<<j))){
					f[cur][e][i]=min(f[cur][e][i],f[cur^1][pMap[s&(~(1<<i))]][j]+tl[j][i]);
				}
			}
		}
	}
	int ans=0x3f3f3f3f;
	for(int i=0; i<k; i++) ans=min(ans,f[cur][0][i]+kdis[i][1]);
	printf("%d\n",ans);
	return 0;
}

---

## 作者：qianfujia (赞：10)

## 这是一种卡常的做法
> 考虑普通做法$dp[i][state]$表示结尾$i$，状态为$state$的最短路径，空间复杂度$n*2^n=20*2^{20}*4KB=80MB$

我们会发现$80MB$和$64MB$没差多少，所以卡常

> 发现只有当$i \in state$时状态合法，所以state可以少存一位，空间复杂度$n*2^{n-1}=20*2^{19}=40MB<64MB$

 _**Solved！**_ 
 
 贴上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 20010;
const int M = 400010;
struct edge{
	int v, d, nxt;
}g[M];
int tot = 0, head[N];
inline void add(int u, int v, int d){
	g[++ tot] = edge{v, d, head[u]}; head[u] = tot;
	g[++ tot] = edge{u, d, head[v]}; head[v] = tot;
}
int n, m, K;
int dis[22][N];
bool vis[N];
queue <int> q;
inline void spfa(int s){
	memset(vis, 0, sizeof(vis));
	q.push(s); dis[s][s] = 0; vis[s] = 1;
	while(! q.empty()){
		for(int i = head[q.front()]; i; i = g[i].nxt){
			if(dis[s][g[i].v] > dis[s][q.front()] + g[i].d){
				dis[s][g[i].v] = dis[s][q.front()] + g[i].d;
				if(! vis[g[i].v]){
					vis[g[i].v] = true;
					q.push(g[i].v);
				}
			}
		}
		vis[q.front()] = 0;
		q.pop();
	}
}
int dp[21][1 << 19];
int e;
int c[22];
inline int solve(int x, int y){
	return (y & ((1 << x - 1) - 1)) + (y >> x << (x - 1));
}
int main(){
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= m; ++ i){
		int u, v, d;
		scanf("%d%d%d", &u, &v, &d);
		add(u, v, d);
	}
	
	scanf("%d", &e);
	for(int i = 1; i <= e; ++ i){
		int x, y;
		scanf("%d%d", &x, &y);
		c[y] += (1 << x - 2);
	}
	memset(dis, 127 / 3, sizeof(dis));
	for(int i = 1; i <= K + 1; ++ i)
		spfa(i);
	if(K == 0){
		printf("%d", dis[1][n]);
		return 0;
	}
	memset(dp, 127 / 3, sizeof(dp));
	for(int i = 1; i <= K; ++ i)
		if(!c[i + 1])
			dp[i][0] = dis[1][i + 1];
	for(int i = 1; i < (1 << K); ++ i)
		for(int j = 1; j <= K; ++ j){
			if(~i & (1 << j - 1))continue;
			if((i & c[j + 1]) != c[j + 1])continue;
			for(int k = 1; k <= K; ++ k){
				if(k == j || (~i & (1 << k - 1)))
					continue;
				dp[j][solve(j, i)] = min(dp[j][solve(j, i)], dp[k][solve(k, i - (1 << j - 1))] + dis[k + 1][j + 1]);
			}
		}
	int ans = 1e9;
	for(int i = 1; i <= K; ++ i)
		ans = min(ans, dp[i][(1 << K - 1) - 1] + dis[i + 1][n]);
	printf("%d", ans);
	return 0;
}
```

---

## 作者：miemieQWQ (赞：6)

像这种题面有点长的, 多半是(划掉),

为了防止读题杀, 我们需要仔细看看题面, 比如第二段的"himdetermine"没打空格(拖走)(其实还有几个)


------------



其实就是叫你求一个有序最短路, 因为K的值那么小, 所以我们可以用二进制集合压缩一下

我们用$Prev[i]$表示第$i$个点之前必须停留的所有点

再来一波预处理, 将所有必须经过的点与其他点的最短距离$Len$求出, 边数有点多......

接下来我们按那个顺序更新最短路, 这个顺序我们很清楚, 记忆化搜索就免了

用$Dist[i][j]$表示已经停留了$i$集合中的城市, 最后一步在j城市,

那么显然当 $Dist[i][j]>Dist[i_0][k]+Len[k][j]$,并且满足对应条件时我们就要松弛一下.**((S1|S2)==S1表示S2包含于S1)**

最后就是找答案啦, 对全集求一遍最小值就ok啦~, 记得加上j到n的距离就好了~


------------



**PS:** 第一遍交的时候左移了一个负数, 华丽RE, 完美爆零......

还有, 我认为本题最坑的地方, 题面的那个图, 对就是它, 那个洛谷的防伪标识, 把6号点挡住了.

然后, 我把1到3的最短路看成了2, 还以为有重边(题目说了没有)

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int rnum()
{
    int fh = 1, res = 0; char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') fh = -1; ch = getchar(); }
    while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
    return fh * res;
}

const int N = 20020, oo = 0x3f3f3f3f;
struct Edge { int to, w; };
vector<Edge> G[N];
int n, m, K, Len[22][N], Dist[1<<20][22], Prev[22];
//Len[i][j] i(i∈[2, k+1])城市到j城市的最短路
//Dist[i][j] 已经访问了i集合所有城市，正在访问j的最短路 
//Prev[i] 要访问i(i∈[2, k+1])点需要先访问的城市集合 

void SPFA(const int &Source) //其实稠密图不适合SPFA 
{
    queue<int> q;
    bool inq[N] = {false};
    q.push(Source), inq[Source] = true, Len[Source][Source] = 0;
    
    int u, v;
    while (!q.empty())
    {
        u = q.front(), q.pop(), inq[u] = false;
        for (int i = 0; i < (int)G[u].size(); i++)
        {
            v = G[u][i].to;
            if (Len[Source][v] > Len[Source][u] + G[u][i].w)
            {
                Len[Source][v] = Len[Source][u] + G[u][i].w;
                if (!inq[v]) q.push(v), inq[v] = true;
            }
        }
    }
}

int main()
{
    n = rnum(), m = rnum(), K = rnum();
    const int sta = (1 << K) - 1; //计算全集，之后会用到 
    for (int i = 1, p, q, l; i <= m; i++)
    {
        p = rnum(), q = rnum(), l = rnum();
        G[p].push_back((Edge){q, l});
        G[q].push_back((Edge){p, l});
    }
    for (int i = 1, g = rnum(), r, s; i <= g; i++)
    {
        r = rnum() - 2, s = rnum();
        Prev[s] |= 1 << r;
    }
    
    memset(Len, 0x3f, sizeof (Len));
    for (int i = 1; i <= K + 1; i++) SPFA(i);
    
    memset(Dist, 0x3f, sizeof (Dist));
    Dist[0][1] = 0; //这是起点(然而可有可无)
    for (int i = 2; i <= K + 1; i++) //最开始这里的Dist第一维的i没-2
        if (!Prev[i]) Dist[1<<(i-2)][i] = Len[1][i]; 
    for (int i = 0; i <= sta; i++)
        for (int j = 0; j < K; j++)
            if (i >> j & 1) for (int k = 0; k < K; k++)
                if (!(i >> k & 1) && (i | Prev[k+2]) == i)
                    Dist[i|1<<k][k+2] = 
                min(Dist[i|1<<k][k+2], Dist[i][j+2] + Len[j+2][k+2]);
                
    int ans = +oo;
    for (int i = 1; i <= K + 1; i++) //实测这里把i起点改成2会挂掉一个点 
        ans = min(ans, Dist[sta][i] + Len[i][n]); //原因就是忽略了没有限制的情况(即g==0) 
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：stdlifg (赞：5)


这种稠密图还是建议你不要跑spfa，你跑dijkstra堆优化会快很多

要看原图[戳我](http://www.lydsy.com/JudgeOnline/images/1097.jpg)(左下角被洛谷图标遮住了)


#题意

题目给你的意思就是

求1到n的

必须经过一些点（2→k+1）

而且过这些点还要讲先后顺序

的最短路长度


#解题

首先看到k<=20

它这是告诉你

对于这k个必须经过的点

你怎么暴力怎么搞

所以我们对这k个点每个点单元最短路（dijkstra）一下，求出他们到所有点的距离。`dis[i][j]`表示由`i`出发到`j`的距离


然后是处理先后关系。我们建立一个数组`r[i]`，`r[i]`的值，表示到达第i个点之前，必须停留的点的状压集合，1为必经，0为无所谓（因为k<=20所以可以状压）


接着就是状压DP。这里``f[i][j]``表示当前状态集合为`i`（1为停留过，0为没有），目前停留在`j`的最短路径。

转移就是普通状压dp套路，从0到（1<<k-1）[全都有] 枚举状态，找到一个集合中存在的点和一个集合中不存在的点，如果当前状态满足这个不在集合内的点的`r[i]`（也就是经过它之前必须经过的点都经过了）那么就进行转移。

初始状态，f设为INF,如果一个点`i`在停留之前不需要在任何点停留，那么`f[1][i]=dis[1][i]`，`f[0][1]=0`


#几点注意（长者的经验教训）

1.当k=0时直接跑最短路不然会WA第六个点

2.INF不能开太大（第三个点会爆成负数）

3.数组要卡空间，不然要么RE要么MLE

4.如果数组太大最好不用memset，最好自己给数组赋值，这样会快很多

5.注意位运算的先后顺序，能打括号就打括号。

#代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

#define rg register int
#define RG register
#define ll long long
#define il inline
#define INF 1000000000 // INF 不要太大会飞起
#define mk make_pair
using namespace std;
typedef pair <int,int> P;

il int gi()
{
    rg x=0,o=0;RG char ch=getchar();
    while((ch!='-')&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-') o=1,ch=getchar();
    while('0'<=ch&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return o?-x:x;
}

struct Edge{int to,nxt,w;}e[300001];
int Ehead[30001],Ecnt=1;
il void Eadd(rg u,rg v,rg w)
{
    e[Ecnt]=(Edge){v,Ehead[u],w};
    Ehead[u]=Ecnt++;
    e[Ecnt]=(Edge){u,Ehead[v],w};
    Ehead[v]=Ecnt++;
}

int n,m,k,g;
int r[32],dis[32][30001];
priority_queue <P,vector<P>,greater<P> > Q;
il void dijkstra(rg rt)
{
    for(rg i=1;i<=n;++i) dis[rt][i]=INF;
    while(!Q.empty()) Q.pop();
    Q.push(mk(0,rt));dis[rt][rt]=0;
    while(!Q.empty())
    {
        rg u=Q.top().second;Q.pop();
        for(rg i=Ehead[u];i;i=e[i].nxt)
        {
            rg v=e[i].to;
            if(dis[rt][v]>dis[rt][u]+e[i].w)
            {
                dis[rt][v]=dis[rt][u]+e[i].w;
                Q.push(mk(dis[rt][v],v));
            }
        }        
    }
}
// dijkstra 无vis数组

int f[1<<20][25],Ans=INF;
int a,b,u,v,w;
int main()
{
    n=gi(),m=gi(),k=gi();
    for(rg i=1;i<=m;++i)
    {
        u=gi(),v=gi(),w=gi();
        Eadd(u,v,w);    
    }

    if(!k) 
    {
        dijkstra(1);
        printf("%d",dis[1][n]);
        return 0;
    } //不加这个判断第6个点会WA

    g=gi();
    for(rg i=1;i<=g;++i)
    {
        a=gi(),b=gi();
        r[b] |= (1<<(a-2));
    }
    for(rg i=1;i<=k+1;++i)  dijkstra(i);
    
    for(rg i=0;i<=(1<<k)-1;++i)
     for(rg j=1;j<=k+1;++j)
      f[i][j]=INF;
    // 数组大就尽量不用memset
    
    f[0][1]=0;
    for(rg i=2;i<=k+1;++i)
     if(!r[i])
      f[1<<(i-2)][i]=dis[1][i];
    
    for(rg i=1;i<=(1<<k)-1;++i)
     for(rg j=0;j<k;++j)
      if(i&(1<<j))
       for(rg l=0;l<k;++l)
        if( !(i&(1<<l)) && (i|r[l+2])==i )
         f[i|(1<<l)][l+2]=min(f[i|(1<<l)][l+2],f[i][j+2]+dis[j+2][l+2]);        
    
    for(rg i=2;i<=k+1;++i)
     Ans=min(Ans,f[(1<<k)-1][i]+dis[i][n]);           
      printf("%d",Ans);
    return 0;
}
```

---

## 作者：Bewegt (赞：5)

### 首先声明：其实这个程序并没有AC，只有95分，但是比单纯的状压DP要好很多（那是直接MLE爆0的QAQ）


## 题解：
前面一部分是跑K+1次dijkstra，用一个二维数组存起来

后面是用map优化状压DP的空间，用dp[i][j]表示走到了i，且路径为j的最短路，然后枚举转移就行了

## 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<map>
#include<algorithm>
#define M 400010
#define N 20010
using namespace std;
int getint(){
    int w=0;bool f=false;char c=getchar();
    while((c<'0'||c>'9')&&c!='-')c=getchar();
    if(c=='-')f=true,c=getchar();
    while(c>='0'&&c<='9')w=w*10+c-'0',c=getchar();
    return f?-w:w;
}
int n,m,k,G,last[N],len(0),num,que[24],qt(0),dis[24][N],d[N],maxn,ans=0x3f3f3f3f,aqr[24];
map<int,int>dp[22];
bool v[N];
struct EDGE{
    int to,las,wi;
}edge[M];
struct ono{
    int xi,dit;
}dui[N<<1];
void add1(int x,int y,int z){
    len++;edge[len].to=y;edge[len].las=last[x];
    edge[len].wi=z;last[x]=len;return;
}
void insert(){
    int now=num;
    while(dui[now].dit<dui[now>>1].dit&&now>1)
        swap(dui[now],dui[now>>1]),now>>=1;
    return;
}
void top(){
    dui[1]=dui[num--];
    int now=2;
    while(now<=num){
        if(dui[now].dit>dui[now+1].dit)now++;
        if(dui[now].dit<dui[now>>1].dit)
            swap(dui[now],dui[now>>1]),now<<=1;
        else break;
    }return;
}
void dij(int x){
    memset(d,0x3f3f3f3f,sizeof(d));memset(v,false,sizeof(v));
    d[x]=num=0;dui[++num].xi=x;dui[num].dit=0;insert();
    int t;
    while(num){
        while(v[dui[1].xi]==true&&num)top();
        if(num<=0)break;
        t=dui[1].xi;top();v[t]=true;
        for(register int i=last[t];i;i=edge[i].las)
        if(d[edge[i].to]>(d[t]+edge[i].wi)){
            d[edge[i].to]=d[t]+edge[i].wi;
            if(v[edge[i].to]==false)
            dui[++num].xi=edge[i].to,dui[num].dit=d[edge[i].to],insert();
        }
    }
    for(register int i=1;i<=n;i++)dis[x][i]=d[i];
    return;
}
int main()
{
    int x,y,z;
    n=getint();m=getint();k=getint();maxn=(1<<k)-1;
    for(register int i=1;i<=m;i++)x=getint(),y=getint(),z=getint(),add1(x,y,z),add1(y,x,z);
    G=getint();memset(aqr,false,sizeof(aqr));
    for(register int i=1;i<=G;i++)x=getint(),y=getint(),aqr[y]=(aqr[y]|(1<<(x-2)));
    for(register int i=1;i<=k+1;i++)dij(i);
    dp[1][0]=0;
    for(register int i=2;i<=k+1;i++)
    if(aqr[i]==0)dp[i][1<<(i-2)]=dis[1][i];
    for(register int i=1;i<=maxn;i++)
    for(register int j=0;j<k;j++)
        if((i&(1<<j))!=0&&dp[j+2].find(i)!=dp[j+2].end())
            for(register int z=0;z<k;z++)
                if((i&(1<<z))==0&&(i|aqr[z+2])==i){
                    if(dp[z+2].find(i|(1<<z))==dp[z+2].end())dp[z+2][i|(1<<z)]=dp[j+2][i]+dis[j+2][z+2];
                    else dp[z+2][i|(1<<z)]=min(dp[z+2][i|(1<<z)],dp[j+2][i]+dis[j+2][z+2]);
                }
    for(register int i=1;i<=k+1;i++)
    if(dp[i].find(maxn)!=dp[i].end())ans=min(ans,dp[i][maxn]+dis[i][n]);
    printf("%d",ans);
    return 0;
}
```

---

## 作者：plafle (赞：4)

# Analysis

这道题我从10月31日调到11月3日，后来发现是自己把$max$从 $2^{20}$ 定义为 $2^{21}$了 ，实在是自闭了。

这道题首先看到$k<=20$，再加上没有什么限制条件，就可以说是一道状态压缩动态规划了。

为了表述方便，我们把**想要停留的点**记作**必留点**。因为题目说可以**路过**而不**停留**，所以我们可以直接先预处理出所有的**必留点**到其他点的**最短路径**（这道题最好用$dijkstra$加优化来跑，$spfa$可能会被卡掉）。令$dis[0][i]$表示第1个点到第$i$个**必留点**的最短路径（这一步也要预处理），$dis[k+1][i]$表示第$n$个点到$i$个必留点的最短路径（依旧要提前预处理）。题目其实就是让我们求一组这$k$个**必留点**的排列，不妨令这组排列为$P$,答案为$ans$：
$$
ans = min(dis[0][P_1]+\sum_{i=1}^{k - 1}dis[P_i][P_{i+ 1}]+dis[k+1][P_k])
$$
好了，题意表述完整。由于$k <= 20$,所以我们可以直接上手动规，用$f[i][j][l]$表示已经走了$i$个**必留点**，当前停在第$j$个必留点，当前已走的必留点状态为$l$时的最短路径。我们可以得到状态转移方程：
$$
f[i][j][l] = min(f[i-1][u][l - (1 << (j - 1))])
$$
当然这里我们要判断一下$f[i - 1][u][l - (1 << (j - 1))]$的状态是否合法。

然后你发现你的空间炸了。观察一下方程式，发现$f[i]$只于$f[i - 1]$有关，可以用滚动数组来弄掉一维。那么当前状态就是$f[j][l][2]$，我们算一下空间：
$$
2^{20}*20*2*4B = 160MB>62.50MB
$$
~~钦定的空间限制就是这么强~~。怎么办呢？

我们观察一下，发现实际上第二维的$l$的许多状态都是浪费的。如果$i=20$,那么$l$其实只有一个状态是有用的，其他都没有用。事实上，当$i = 10,k = 20$的时候$j$有用的状态是最多的。此时$max_j = C_{20}^{10} = 184756$。所以说我们此时的空间就是这个亚子：
$$
C_{20}^{10}*2*20*4B=28.19MB<65.20MB
$$
然而可能会有人问：

- 这样的状态怎么转化成二进制继而表示真正的状态呢？
- 即使表示成了二进制，在状态转移后$l - (1 << (j - 1))$这个二进制状态又怎么转移回这种状态呢？

为了表述方便，我们把**"这样的状态"**定义为**"组合数类型状态"**

- 对于第一个问题，我们只要开一个$state[i][j]$的数组表示当前2进制状态中有$i$个1时第$j$个**组合数类型状态**的**二进制状态**可以提前预处理。
- 对于第二个问题，我们可以开一个$st2$ _to _ $num[i] = j$表示2进制状态$i$转化成的**组合数类型状态**$state[t][j]$，因为**每个二进制状态所包含的1的个数是相同的**，所以$t$是确定的，不用再另外表示。这个数组可以在预处理$state$数组的同时预处理。

最后给出$ans$的数学表达式：
$$
ans = min(f[j][l][now] + dis[k + 1][j])(1 <= j <= k,0 <=l<2^k)
$$


# Notes

- 当$k = 1$的时候要特判，不然会炸掉。
- 走第一个点的时候可以先预处理，这样可能会比较好些。
- 一定要耐心地写，耐心地调。



# Code

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int maxm = 200001,maxn = 20001,maxk = 22,inf = 0x3f3f3f3f,max_state = 184758,max_2 = (1 << 20);
int first[maxn],nxt[2 * maxm],last[maxn],dx[2 * maxm],w[2 * maxm];
int dis[maxk][maxn],xb,n,m,k,x,y,z,f[maxk][max_state][2],state[maxk][max_state],num[max_2];
int g,st2_to_num[max_2],now,pre,ans,xx,sum; 
bool vis[maxn],r[maxk][maxk],cnt[maxk];//r[i][j] = 1 表示i必须在j前面 
pair<int,int> v;

priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;


void build(int x,int y,int z) {
	dx[++xb] = y,w[xb] = z;
	if (!first[x])
		first[x] = xb; else
		nxt[last[x]] = xb;
	last[x] = xb;
}

void dijkstra(int x) {
	if (x == n)
		x = 0,xx = n; else
		if (x == n + 1)
			x = k + 1,xx = n - 1; else
			xx = x;
	for (int i=0; i<maxn; i++)
		dis[x][i] = inf;
		
	dis[x][xx] = 0;
	while (!q.empty())
		q.pop();
	for (int i=first[xx]; i; i = nxt[i])
		dis[x][dx[i]] = w[i];
	for (int i=first[xx]; i; i = nxt[i]) 
		q.push(make_pair(w[i],dx[i]));
	for (int i=0; i<=n; i++)
		vis[i] = 0;
		
	vis[xx] = 1;
	for (int i=1; i<n; i++) {
		if (q.empty()) 
			break;
		v = q.top();
		while (vis[v.second] && !q.empty()) {
			q.pop();
			if (q.empty())
				break;
			v = q.top();
		}
		vis[v.second] = 1;
		dis[x][v.second] = v.first;
		for (int j = first[v.second]; j; j = nxt[j]) {
			if (dis[x][dx[j]] > dis[x][v.second] + w[j]) {
				dis[x][dx[j]] = dis[x][v.second] + w[j];
				if (!vis[dx[j]]) 
					q.push(make_pair(dis[x][dx[j]],dx[j]));
				
			}
		}
	}
}

int get_num(int x) {
	sum = 0;
	while (x > 0) {
		sum += (x & 1);
		x >>= 1;
	}
	return sum;
}

int main() {
//    freopen("p3451.in","r",stdin);
//    freopen("p3451.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1; i<=m; i++) {
		scanf("%d%d%d",&x,&y,&z);
		if (x == 1)
			x = n; else
			x--;
		if (y == 1)
			y = n; else
			y--;
		build(x,y,z);
		build(y,x,z);
	}
	
	for (int i=1; i<=k; i++)
		dijkstra(i);	
	dijkstra(n);
	dijkstra(n + 1);
	scanf("%d",&g);
	for (int i=1; i<=g; i++) {
		scanf("%d%d",&x,&y);
		x--;
		y--;
		r[x][y] = 1;
		cnt[y] = 1;
	}
	for (int i=0; i<max_2; i++)
		num[i] = get_num(i);
		
	for (int i=0; i<=k + 1; i++)
		for (int j=0; j<max_2; j++)
			if (num[j] == i) {
				state[i][++state[i][0]] = j;
				st2_to_num[j] = state[i][0];
			}
				
	memset(f,0x3f,sizeof(f));
	for (int i=1; i<=k; i++)
		if (!cnt[i])
			f[i][st2_to_num[1 << (i - 1)]][1] = dis[0][i];
				
	for (int i=2; i<=k; i++) { ///经过i个点
		now =(i & 1),pre = 1 - now;
		for (int j=0; j<=k; j++)
			for (int l=1; l<=state[i][0]; l++)
				f[j][l][now] = inf;
				
		for (int j=1; j<=k; j++) //当前到 j点 
			for (int l=1; l<=state[i][0]; l++) { //到j点后状态为state[i][l]
				if (((state[i][l] | (1 << (j - 1))) == state[i][l])) {
					if (state[i][l] >= (1 << k))
						break;
					int p_state = state[i][l] - (1 << (j - 1)); //p_state 即pre_state,表示前一次状态 
					bool t = 1;
 					for (int v = 1; v <= k; v++)
						if (r[v][j] && (((1 << (v - 1)) | p_state) != p_state)) {
							t = 0;
							break;
						}
					if (!t)
						continue;
					for (int v = 1; v <= k; v++)
						if (((1 << (v - 1)) | p_state) == p_state)
							f[j][l][now] = min(f[j][l][now],f[v][st2_to_num[p_state]][pre] + dis[v][j]);
				}
			}  
//		if (i == 2)
//			printf("%d\n",f[2][3][now]);
	}
	ans = inf;
	if (k < 2)
		now = 1;
	if (k == 0) {
		printf("%d\n",dis[0][n - 1]);
		return 0; 
	}
	for (int i=1; i<=k; i++)
		for (int j=1; j<=state[k][0]; j++)
			ans = min(ans,f[i][j][now] + dis[k + 1][i]);		
	if (ans == inf)
		ans = -1;
	printf("%d\n",ans);
	
	return 0;
}
```





---

## 作者：楠枫 (赞：1)

## 题解

[更好的阅读体验](https://www.cnblogs.com/nanfeng-blog/p/14994781.html)

这里的做法是卡空间的做法，相比于滚动数组，这种做法因为没有三维数组寻址的大常数，所以较快。

在普通的做法中，$dp_{state,i}$ 表示以 $i$ 结尾，那么 $state$ 一定是包含 $i$ 的状态，所以在 $state$ 中可以省掉 $i$ 这一位。

所以 $cost=(k+1)×2^{k-1}×4kb$ ，大约为 42MB 。

注：本题用 spfa 会比 dijkstra 快很多。

Code：
```cpp
#include<bits/stdc++.h>
#define ri register signed
#define p(i) ++i
using namespace std;
namespace IO{
    char buf[1<<21],*p1=buf,*p2=buf;
    #define gc() p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++
    template<typename T>inline void read(T &x) {
        ri f=1;x=0;register char ch=gc();
        while(ch<'0'||ch>'9') {if (ch=='-') f=0;ch=gc();}
        while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=gc();}
        x=f?x:-x;
    }
}
using IO::read;
namespace nanfeng{
    #define node(x,y) (node){x,y}
    #define cmax(x,y) ((x)>(y)?(x):(y))
    #define cmin(x,y) ((x)>(y)?(y):(x))
    #define FI FILE *IN
    #define FO FILE *OUT
    static const int N=2e4+7,M=2e5+7;
    int first[N],dp[1<<19][21],pre[21],dis[21][N],vis[N],n,m,q,k,t=2,S;
    struct edge{int v,w,nxt;}e[M<<1];
    struct node{int x,dis;};
    priority_queue<node> que;
    inline int operator<(const node &n1,const node &n2) {return n1.dis>n2.dis;}
    inline void add(int u,int v,int w) {
        e[t].v=v,e[t].w=w,e[t].nxt=first[u],first[u]=t++;
        e[t].v=u,e[t].w=w,e[t].nxt=first[v],first[v]=t++;
    }
    inline void dij(int rt){
        memset(vis,0,sizeof(vis));
        memset(dis[rt-1],0x3f,sizeof(dis[rt-1]));
        dis[rt-1][rt-1]=0;
        que.push(node(rt,0));rt-=1;
        while(!que.empty()) {
            int x(que.top().x),dist(que.top().dis);
            que.pop();
            if (vis[x]) continue;
            vis[x]=1;
            for (ri i(first[x]),v;i;i=e[i].nxt) {
                if (dis[rt][v=e[i].v-1]>dist+e[i].w) {
                    dis[rt][v]=dist+e[i].w;
                    que.push(node(v+1,dis[rt][v]));
                }
            }
        }
    }
    inline int calc(int x,int l) {
        if ((1<<l)>x) return x;
        ri tmp=x&((1<<l)-1);
        return (x>>(l+1))<<l|tmp; 
    }
    inline int main() {
        // FI=freopen("nanfeng.in","r",stdin);
        // FO=freopen("nanfeng.txt","w",stdout);
        read(n),read(m),read(k);
        for (ri i(1),u,v,w;i<=m;p(i)) read(u),read(v),read(w),add(u,v,w);
        read(q);
        for (ri i(1),r,s;i<=q;p(i)) {
            read(r);read(s);
            pre[s-2]|=1<<(r-2);
        }
        for (ri i(1);i<=k+1;p(i)) dij(i);
        if (!k) {printf("%d\n",dis[0][n-1]);return 0;} 
        memset(dp,0x3f,sizeof(dp));
        dp[0][0]=0;
        for (ri i(1);i<=k;p(i)) if (!pre[i-1]) dp[0][i]=dis[0][i];
        S=(1<<k)-1;
        for (ri i(1);i<=S;p(i)) {
            for (ri j(0);j<k;p(j)) {
                if (!((1<<j)&i)) continue;
                ri tmp1=calc(i,j);
                for (ri l(0);l<k;p(l)) {
                    if (!(i&(1<<l))&&((i&pre[l])==pre[l])) {
                        ri tmp2=calc(i,l);
                        dp[tmp2][l+1]=cmin(dp[tmp1][j+1]+dis[j+1][l+1],dp[tmp2][l+1]);
                    }
                }  
            }
        }
        ri ans=INT_MAX;
        for (ri i(1),tmp;i<=k;p(i)) {
            tmp=calc(S,i-1);
            ans=cmin(ans,dp[tmp][i]+dis[i][n-1]);    
        }
        printf("%d\n",ans);
        return 0;
    } 
}
int main() {return nanfeng::main();}
```

---

