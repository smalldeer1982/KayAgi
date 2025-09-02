# Galactic Council

## 题目描述

Monocarp 正在玩一个电脑游戏，他在游戏中掌控着一个太空帝国。这个帝国由 $n$ 个政党组成。起初，每个政党的政治影响力都是 $0$，并且没有执政党。

在接下来的 $m$ 个回合中，会发生如下事件：

1. 首先，Monocarp 要选择支持哪个政党。他可以支持任何一个政党，但不能是当前的执政党。每当他支持一个政党，该政党的政治影响力就增加 $1$。假如他在第 $j$ 回合支持第 $i$ 个政党，他会因此获得 $a_{i,j}$ 分的加分；
2. 接下来，进行选举，影响力最高的政党被选为新的执政党（如果有多个这样的政党，则选编号最小的）。前任执政党会被替换，除非它继续胜选；
3. 最后，一个事件会发生。在每个回合结束时，政党 $p_j$ 必须成为执政党，否则 Monocarp 将输掉游戏。

你的任务是帮助 Monocarp 确定在每个回合中支持哪个政党，以避免因为事件而输掉游戏，并且使他的得分达到最大。初始时，Monocarp 的得分为 $0$。

## 样例 #1

### 输入

```
2 3
2 1 2
1 2 3
4 5 6```

### 输出

```
2 1 2```

## 样例 #2

### 输入

```
3 5
1 1 1 2 1
1 1 1 1 1
10 5 7 8 15
7 10 9 8 15```

### 输出

```
1 3 2 2 1```

## 样例 #3

### 输入

```
3 5
1 1 1 1 1
1 1 1 1 1
10 5 7 8 15
7 10 9 8 15```

### 输出

```
-1```

# 题解

## 作者：Nt_Tsumiki (赞：5)

首先这个题意非常不可做，但是仔细观察会得到一些有用的性质。

首先我们发现他对于所有的 $m$ 个回合都给出了钦定的执政党 $p_i$，假如说第 $i$ 个回合执政党一共有多少 $val_{i}$ 票，那么对于第 $i+1$ 回合的执政党 $p_{i+1}$ 我们有：

1. $p_{i+1}<p_i$，在第 $i$ 回合我们有 $val_{i+1}-1<val_i$，在第 $i+1$ 回合我们有 $val_{i+1}\ge val_i$，解得 $val_{i+1}=val_i$。
2. $p_{i+1}=p_i$，由于不能选自己，所以票数不变。
3. $p_{i+1}>p_i$，在第 $i$ 回合我们有 $val_{i+1}-1\le val_i$，在第 $i+1$ 回合我们有 $val_{i+1}>val_i$，解得 $val_{i+1}=val_i+1$。

又因为一开始你只能选 $p_1$，所以我们可以知道任意回合执政党的票数，对于编号小的党派我们只用保证小于 $val_i$，编号大的党派我们只需要保证小于等于 $val_i$ 即可。

那我们考虑建立这样的一个流模型：

- 首先我们建立超级源点 $s$ 和超级汇点 $t$，用以控制流量和处理强制流满问题，以及源点 $S$ 和汇点 $T$。
- 对于每个回合我们把它们单独建一个点记做 $u$，然后连一条 $S\to u$ 的流量为 $1$ 费用为 $0$ 的边代表分配一个选票。
- 对于每个回合 $u$ 的每个党派 $v$ 我们单独建一个点记做 $(u,v)$，以下默认 $(m+1,v)$ 等价于 $T$。
  - 对于每个当前回合的非执政党我们连一条 $(u,v)\to (u+1,v)$ 的流量为当前的最大上界费用为 $0$ 的边。
  - 对于执政党，我们考虑考虑连一条 $(u,v)\to (u+1,v)$ 的流量为 $val_u$ 且必须流满的边，考虑上下界，直接从 $s$ 连一条流量为 $val_u$ 的边到 $(u+1,v)$，从 $(u,v)$ 连一条流量为 $val_v$ 的边到 $t$。
- 对于两边点集之间我们连 $u\to (u,v)$ 的一条流量为 $1$ 费用为 $a_{v,u}$ 的边。

然后跑最大费用最大流即可，对于输出方案我们直接对于每个 $u$ 去看哪条出边的流量用光了即可。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

#define N 5005
#define INF 0x3f3f3f3f

inline int R() {
    int x=0; bool f=0; char c=getchar();
    while (!isdigit(c)) f|=(c=='-'),c=getchar();
    while (isdigit(c)) x=x*10+c-'0',c=getchar();
    return f?-x:x;
}

template<typename T>
void W(T x,char Extra=0) {
    if (x<0) putchar('-'),x=-x; if (x>9) W(x/10);
    putchar(x%10+'0'); if (Extra) putchar(Extra);
}

using namespace std;
int n,m,a[N][N];

int tot=1,s,t,S,T,mcmf,cur[N],head[N],dis[N],vis[N];
struct Node { int to,nxt,dis,val; }e[N*N];

void add(int u,int v,int dis,int val) { e[++tot]=Node{v,head[u],dis,val},head[u]=tot; }

bool SPFA() {
    memcpy(cur,head,((n+1)*m+4)*sizeof(head[0]));
    memset(dis,0x3f,((n+1)*m+4)*sizeof(dis[0]));
    memset(vis,0,((n+1)*m+4)*sizeof(vis[0]));
    queue<int> q; q.push(s); dis[s]=0;
    while (!q.empty()) {
        int u=q.front(); q.pop(); vis[u]=0;
        for (int i=head[u];i;i=e[i].nxt) {
            int v=e[i].to;
            if (e[i].dis and dis[v]>dis[u]+e[i].val) {
                dis[v]=dis[u]+e[i].val;
                if (!vis[v]) q.push(v),vis[v]=1;
            }
        }
    }
    return dis[t]!=INF;
}

int dfs(int u,int flow) {
    if (u==t) return flow;
    int res=0; vis[u]=1;
    for (int i=cur[u];i and flow;i=e[i].nxt) {
        int v=e[i].to; cur[u]=i;
        if (e[i].dis and !vis[v] and dis[v]==dis[u]+e[i].val) {
            int k=dfs(v,min(e[i].dis,flow));
            e[i].dis-=k,e[i^1].dis+=k,res+=k,flow-=k,mcmf+=k*e[i].val;
        }
    }
    vis[u]=0; return res;
}

int p[N],val[N];

int main() {
    n=R(),m=R();
    for (int i=1;i<=m;i++) p[i]=R(),val[i]=val[i-1]+(p[i]>p[i-1]);
    s=0,t=(n+1)*m+1,S=(n+1)*m+2,T=(n+1)*m+3;
    int Sum=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++) Sum+=(a[i][j]=R());
    int sum=0;
    for (int i=1;i<=m;i++) {
        add(S,i+n*m,1,0),add(i+n*m,S,0,0);
        for (int j=1;j<=n;j++) {
            add(i+n*m,(i-1)*n+j,1,-a[j][i]),add((i-1)*n+j,i+n*m,0,a[j][i]);
            if (j<p[i]) add((i-1)*n+j,i==m?T:i*n+j,val[i]-1,0),add(i==m?T:i*n+j,(i-1)*n+j,0,0);
            else if (j==p[i]) {
                add(s,i==m?T:i*n+j,val[i],0),add(i==m?T:i*n+j,s,0,0);
                add((i-1)*n+j,t,val[i],0),add(t,(i-1)*n+j,0,0);
                sum+=val[i];
            } else add((i-1)*n+j,i==m?T:i*n+j,val[i],0),add(i==m?T:i*n+j,(i-1)*n+j,0,0);
        }
    }
    add(s,S,m,0),add(S,s,0,0); add(T,t,m,0),add(t,T,0,0);
    int ans=0;
    while (SPFA()) ans+=dfs(s,INF);
    if (ans<sum+m) return W(-1,'\n'),0;
    for (int u=1;u<=m;u++) {
        int res=0;
        for (int i=head[u+n*m];i;i=e[i].nxt) {
            int v=e[i].to;
            if (v>=(u-1)*n+1 and v<=(u-1)*n+n and !e[i].dis) {
                res=v-(u-1)*n;
                break;
            }
        }
        W(res,' ');
    }
    return 0;
}
```

---

## 作者：mqmhaaaa1 (赞：2)

超超超超超级有意思的题，太有意思了。

题意题目讲的很清晰了，这里不讲。

# step1 

看完题，一阵头脑风暴后，我们发现每天执政党当天所拥有的票数是固定的，我们设第 $j$ 天党派 $i$ 票数为 $ps_{i,j}$，如下。（以下默认 $i \ge 1$，因为第一天只能投给 $p_1$）

1. 当 $p_{j-1} = p_j$，因为不能给执政党投票，所以 $ps_{p_j,j}=ps_{p_{j-1},j-1}$。

2. 当 $p_{j-1}>p_j$，因为 $p_j$ 编号更小。所以为了使 $i-1$ 天执政党为 $p_{j-1}$，所以 $ps_{p_j,j-1}<ps_{p_{j-1},j-1}$，又为了令 $ps_{p_j,j-1}+1 \ge ps_{p_{j-1},j}$，所以 $ps_{p_j,j}=ps_{p_{j-1},j-1}$。（$ps_{p_{j-1},j-1}$ 与 $ps_{p_{j-1},j}$ 相等，上面提到了）

3. 当 $p_{j-1} < p_j$，与情况 2 同理（我不想再写依托 latex 了），得到 $ps_{p_j,j}=ps_{p_{j-1},j-1}+1$。

这是好的开始，但是接下来呢？

# step2 转化为网络流

如果你思维开阔，或喜欢做网络流（像本蒟蒻一样），那么可能会这样想：每一天票数从昨天继承，所有党派票数每天有每天的限制，选某个党派可以得到贡献。

这样想后，会有一个思路（oier 的神奇出思路方式），我们将票数变成流量，贡献就是费用。我们的目标建图是可以表示每天每个党派的流量限制，同时将昨天的流量继承到今天，贡献就是费用。因此，应该是跑最大费用最大流这种东西。

# step3 具体建图

我们先搞点基础的，为每一天建立一个虚点 $x$，同时每天建立 $m$ 层分图用来方便表示每天之间的关系。每个分层图由虚点 $x$ 和 $n$ 个党派构成。

每天的虚点 $x$ 就是表示向那个党派投票，于是连 $s \to x$（$s$ 是源点），流量 1，费用 0，表示每天提供一个流量调配。然后 $x$ 向该天这层图中所有政党连边，流量 1，费用为该天选该党派的贡献（就是 $a_{i,j}$ 啦），表示每天分配流量给每个党派以及贡献。

接下来就是天与天之间的限制了。

不难发现，只要昨天向今天连边就既可以继承流量也可以限制流量了。

因为今天既会继承昨天的流量，昨天的流量也有一个上限，用边的容量用来限制流量不超过上限是很好的。这个上限很好理解，一起看一下每天每个点的流量上限（也就是所持票数上限）。（在这里，我们令 $(i,j)$ 表示党派 $i$ 在第 $j$ 天所对应的点）

1. 点 $i$ 为第 $j$ 执政党，那么该天这个点所持票数必须为 $ps_{p_j,j}$，这个是确定的，所以连 $(i,j) \to (i,j+1)$，上下界都为 $ps_{p_j,j}$，因为限制是**票数必须为** $ps_{p_j,j}$，所以需要用上下界（是的，就因为这个还需要写个上下界）

2. 点 $i$ 编号小于 $p_j$，上面也说过了，所以 $ps_{i,j}<ps_{p_j,j}$，因此连 $(i,j) \to (i,j+1)$，上界为 $ps_{p_j,j}-1$（因为这就是上限），没有下界是因为该天对该政党流量没有硬性的下限要求。

3. 点 $i$ 编号大于 $p_j$，与情况 2 过程一样，连边 $(i,j) \to (i,j+1)$ 后上界为 $ps_{p_j,j}$。

这里说明一下，以上默认 $(i,m+1)$ 为汇点 $t$。

然后本题就解决了。输出方案去找每天虚点 $x$ 向每个政党连边那条满流，满流说明该天选了该政党。在判断无解时，有两种情况，第一个是没有可行流，第二个是最大流小于 $m$，因为每天只出去 1 流量，若最大流不到 $m$，说明某些天没投票，不满足要求（因为我们跑的是最大费用最大流），这一点也可以把 $s \to x$ 的每条边加一个下界为 1 来限制，不过我比较懒我就直接判最大流了。

# step4 偷懒

因为上下界写得很恶心，所以我选择用费用流直接写上下界。

具体而言，我们可以把一条有上下界的边拆成两条边，一条表示必须流满的下界，一条是流量为上界减去下界，表示除了下界以外可以随便流的。表示必须流那条边费用为 $- \inf$，这样在找增光路的时候会贪心的先找这种费用最小的在增广路中。

这样可以偷点懒，但不建议多用，因为这样做复杂度一般略劣与直接上下界，我还被卡过。

吃吃码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
void write(ll x) {static ll sta[35];ll top = 0;do {sta[top++] = x % 10, x /= 10;} while (x);while (top) putchar(sta[--top] + 48);}
ll read() {ll x = 0, w = 1;char ch = 0;while (ch < '0' || ch > '9') {  if (ch == '-') w = -1;ch = getchar();}while (ch >= '0' && ch <= '9') {x = x * 10 + (ch - '0'); ch = getchar(); }return x * w; }
const ll N=2e4+10,M=2e6+10,inf=0x7f7f7f7f;
ll to[M<<1],nxt[M<<1],w[M<<1],c[M<<1],bh[N],tot=1;
ll head[N],dis[N];
bool vis[N];
inline void add(ll u,ll v,ll flow,ll cost){
	to[++tot]=v;
	nxt[tot]=bh[u];
	w[tot]=flow;
	c[tot]=cost;
	bh[u]=tot;
//	cout<<u<<' '<<v<<' '<<flow<<'e'<<'\n';
	to[++tot]=u;
	nxt[tot]=bh[v];
	w[tot]=0;
	c[tot]=-cost;
	bh[v]=tot;
}
ll s,t;
inline bool spaf(){
	for(ll i=0;i<=t;i++){
		vis[i]=0;head[i]=bh[i];
		dis[i]=inf;
	}
	deque<ll>q;
	vis[s]=1;dis[s]=0;
	q.push_front(s);
	while(q.size()){
		ll u=q.front();q.pop_front();
		vis[u]=0;
		for(ll i=bh[u];i;i=nxt[i]){
			ll v=to[i];
			if(w[i]&&dis[u]+c[i]<dis[v]){
				dis[v]=dis[u]+c[i];
				if(!vis[v]){
					vis[v]=1;
					if(q.size()&&dis[v]<=dis[q.front()])q.push_front(v);
					else q.push_back(v);
				}
			}
		}
	}
	return dis[t]!=inf;
}//优化small label first
ll ans,mxf;
ll dic(ll u,ll flow){
//	cout<<u<<' '<<flow<<'\n';
	vis[u]=1;
	if(u==t){
		mxf+=flow;
		return flow;
	}
	ll zy=0;
	for(ll i=head[u];i&&flow;i=nxt[i]){
		ll v=to[i];head[u]=i;//当前弧
		if(w[i]&&(!vis[v]||v==t)&&dis[v]==dis[u]+c[i]){
			ll jb=dic(v,min(w[i],flow));
			w[i]-=jb;w[i^1]+=jb;
			zy+=jb;flow-=jb;
			ans+=jb*c[i];
			if(!flow)break;//优化点
		}
	}
	vis[u]=0;
	return zy;
}
ll n,m,sum;
ll p[60],ps[60];
ll id(ll ts,ll i){
	if(ts<=m)return (ts-1)*n+i;
	return t;
}
int main(){
	n=read(),m=read();
	s=0,t=n*m+m+1;
	ps[1]=1;
	for(ll i=1;i<=m;i++){
		p[i]=read();
		ll x=n*m+i;
		add(s,x,1,0);
		if(i==1)continue;
		if(p[i]>p[i-1]){
			ps[i]=ps[i-1]+1;
		}else{
			ps[i]=ps[i-1];
		}
		
	}
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			ll val=read(),x=n*m+j,u=id(j,i);
			add(x,u,1,-val);
			if(p[j]==i){
				add(u,id(j+1,i),ps[j],-inf);sum+=ps[j];
			}else if(i<p[j]){
				add(u,id(j+1,i),ps[j]-1,0);
			}else if(i>p[j]){
				add(u,id(j+1,i),ps[j],0);
			}
		}
	}
	while(spaf()){
		vis[t]=1;
		while(vis[t]){
			memset(vis,0,sizeof vis);
			dic(s,inf);
		}
	}
	
	ans+=sum*inf;//加上多减去的费用后如果大于原本的费用，说明-inf与inf没有完全抵消，就是没有可行流了 
	if(ans>7e6||mxf<m){
		puts("-1");return 0;
	}
	for(ll j=1;j<=m;j++){
		ll u=n*m+j;
		for(ll i=bh[u];i;i=nxt[i]){
			ll v=to[i];
			if(v!=s&&!w[i]){
				write(v-id(j,0)),putchar(' ');
			} 
		}
	}
}

```

这题真的很有意思，还有 Kyotsugyon 就是神啊。

---

