# Buying Sets

## 题目描述

十六进制病毒非常喜欢玩数字集合——求交集、并集。有一天，她惊讶地发现，她那只圆滚滚的宠物猫 Scuzzy 把所有集合都合并成一个并且吃掉了结果！她必须赶快采取行动，于是十六进制病毒匆匆赶往市场。

市场上有 $n$ 个数字集合出售。病毒想要购买如下集合：所选集合的数量，恰好等于所有被选集合的并集中的数字个数。此外，十六进制病毒希望以最低的价格买到满足条件的集合。

但事情并不简单！由于 Mainframe 是一个极度竞争的市场，我们知道任意 $k$ 个集合的并集，包含的不同数字不会少于 $k$ 个（对于任意正整数 $k$）。

请帮助病毒选择合适的集合。集合可以为空。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 1
2 2 3
1 3
10 20 -3
```

### 输出

```
-3
```

## 样例 #2

### 输入

```
5
2 1 2
2 2 3
2 3 4
2 4 5
2 5 1
1 -1 1 -1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5
2 1 2
2 2 3
2 3 4
2 4 5
2 5 1
-1 1 -1 1 -1
```

### 输出

```
-1
```

# 题解

## 作者：Marser (赞：18)

提供一种更为巧妙的做法，不需要进行二分图匹配。  
### 题意
有一个大小为 $n$ 的全集，每个元素是一个数，有 $n$ 个子集。题目**保证任意 $k$ 个子集的并的大小 $ \ge k $**。  
每个子集有一个可正可负的权值，你需要选出一些子集使得这些子集并的大小等于子集个数，且所选子集的权值和最小，可以为空集。

### 题解
把子集和元素分别看成两类物品，我们可以知道，如果我们选择了一个子集，那么我们必须选择所有属于它的元素。这启发我们往最大权闭合子图的方向转化。  
我们先忽略“子集并的大小等于子集个数”这个条件，就是最小权闭合子图的经典模型，把每个子集的权值取反就可以做了。

那么，如何解决这一限制呢？  
“任意 $k$ 个子集的并的大小 $ \ge k $”是一个很强的性质，我们可以考虑从这里入手。  
我们给每个元素赋上$-\infty$的权值，给每个子集赋上$+\infty$的权值，由上述条件，任意方案选择的子集数量都$\le$元素数量。所以所选择的$-\infty$的数量都$\le$选择的$+\infty$的数量。当且仅当方案满足限制时，所有赋上的权值会相互抵消。而最大流总是会寻找最优的方案，所以在有解的情况下，求出的答案一定合法，且所有附加权值都已消去。  
而由于我们可以选择空集，所以一定存在合法的方案。

实现中有两个细节要注意：  
1. 最大权闭合子图建模的过程中，必须同时选择的物品间流量为$+\infty$的边的权值必须大于赋上的权值。在代码中，我用```lim```表示赋上的无穷大权值，用```inf```表示建图过程中的无穷大权值。
2. 由于可以选择空集，输出时答案要和$0$取个$\min$。

### 代码
```cpp
#include<bits/stdc++.h>
#define reg register
using namespace std;
typedef long long ll;
const int lim=3e8+5;
const int inf=0x3f3f3f3f;
const int V=605;
const int E=181205;
int to[E],nxt[E],c[E],h[V],cnt;
inline void ins(int s,int t,int w){
	to[cnt]=t;nxt[cnt]=h[s];c[cnt]=w;h[s]=cnt++;
	to[cnt]=s;nxt[cnt]=h[t];c[cnt]=0;h[t]=cnt++;
}
int S,T,level[V],iter[V],que[V];
bool bfs(){
	memset(level,-1,sizeof(level));
	reg int he=0,ta=1;que[0]=S;level[S]=1;
	while(he<ta){
		reg int v=que[he++];
		for(reg int i=h[v];~i;i=nxt[i]){
			if(c[i]&&level[to[i]]<0){
				level[to[i]]=level[v]+1;
				que[ta++]=to[i];
			}
		}
	}
	return level[T]>0;
}
int dfs(int st,int f){
	if(st==T)return f;
	reg int used=0,w;
	for(reg int& i=iter[st];~i;i=nxt[i])
		if(c[i]&&level[to[i]]==level[st]+1){
			w=dfs(to[i],min(c[i],f-used));
			if(!w)continue;
			c[i]-=w;c[i^1]+=w;used+=w;
			if(f==used)return f;
		}
	return used;
}
int n;
int main(){
	memset(h,-1,sizeof(h));
	scanf("%d",&n);T=n+n+1;
	for(reg int i=1,k,x;i<=n;i++){
		scanf("%d",&k);
		while(k--)scanf("%d",&x),ins(i,x+n,inf);
	}
	reg ll Ans=0,f;
	for(reg int i=1,x;i<=n;i++)
		scanf("%d",&x),ins(S,i,lim-x),Ans+=lim-x;
	for(reg int i=1;i<=n;i++)ins(i+n,T,lim);
	while(bfs()){
		memcpy(iter,h,sizeof(h));
		while(f=dfs(S,inf))Ans-=f;
	}
	printf("%lld\n",min(-Ans,0ll));
	return 0;
}
```

---

## 作者：s_r_f (赞：15)

安利 : [九月杂题选做-洛谷博客](https://www.luogu.com.cn/blog/s-r-f/jiu-yue-za-ti-xuan-zuo) [九月杂题选做-cnblogs](https://www.cnblogs.com/s-r-f/p/13602350.html)

---

双倍经验 : [LOJ#6045. 「雅礼集训 2017 Day8」价](https://loj.ac/problem/6045)

首先把价值取反，然后问题转换为求最大权值。

考虑一个最小割模型:

S连向集合，容量INF+权值，割掉这条边相当于不选这个集合；

集合连向集合内的数字，容量INF；

数字连向T，容量INF，割掉这条边相当于选这个数字；

不难发现在最小割方案中，割掉集合连向集合内的数字的边是不优的。

因为有完美匹配，所以对于任意左部点集合 $S$ , $|N(S)| \geq |S|,$ 因此至少会割掉$n$条边。

又因为边权加上了 $INF$ ,所以不会割掉 $>n$ 条边。

因此不选的集合的个数 + 选的数字个数 = n，所以可以得到选的集合个数 = 选的数字的个数。

然后跑一个最小割即可。

$O(Dinic(n,n^2))$

代码见 : [my solution](https://www.cnblogs.com/s-r-f/p/13662769.html)

---

## 作者：stntn (赞：8)

做完了才发现有 $|N(S)| \ge |S|$ 的条件（？）。

首先很显然把一个集合看成一个点，一个集合向其内的元素连边，这样形成了一个二分图。我们要做的是找到左部（集合）点的一个集合，使得邻居集合大小与之相等且权值和最小。

下面令左部点集为 $L$，右部为 $R$。

我们发现如果存在两个集合 $S_1,S_2 \subseteq L,S_1 \ne S_2$ 分别满足题目条件，即 $|N(S_1)|=|S_1|$，$|N(S_2)|=|S_2|$，那么有 $|N(S_1 \cup S_2)|=|S_1 \cup S_2|$。

这有什么用呢，我们考虑钦定选择左部点 $l$，构造一个最小的包含它的合法集合，最后的答案一定是若干个这样的集合的并。

考虑构造：先求出原图的最大匹配。维护一个集合，初始为 $\{l\}$，每次找到左端点在集合中的非匹配边 $(u,v)$，将 $v$ 的匹配点加入。重复该操作直到不会有更多点加入为止。

思考这样构造的本质，用图论来刻画，实际上就是对于左部点 $u$，找到非匹配边 $(u,v)$，从 $u$ 向 $v$ 的匹配点连边，显然 $u$ 所能到达的所有点即上述所求集合。

然后就转化成了一个最小权闭合子图模型，选 $u$ 则必选 $u$ 的后继，跑最小割即可。

[ code](https://codeforces.com/problemset/submission/103/235650572)

感觉比他们的做法复杂不少但还是很有趣的。

---

## 作者：Acoipp (赞：6)

网络流神题。

## 题意

给定一张二分图，二分图左部的任意 $k$ 个点与右部都有不同的至少 $k$ 个点相连接。

若从左边选择一个点，右边与之相连接的所有点都要被选，问从左边选择 $k$ 个点，右边被选择也恰好 $k$ 个的方案中，左边选的点的权值和最小是多少。

可以不选任何数，此时答案为 $0$。

## 分析

首先忽略右边被选择恰好 $k$ 个的限制，那么直接把点权反过来跑最小割的最大权闭合子图即可。

此处点权中：左边的点权就是给定的，右边的点权都是 $0$。

那么考虑必须恰好 $k$ 个，如果左边选了 $k$ 个，右边一定选了超过 $k$ 个，考虑把左边的点权全部加上 $\text{inf}$，右边的点权全部减去 $\text{inf}$，那么我们一定不会让右边选择超过 $k$ 个，如果超过 $k$ 个，那么答案就会少 $\text{inf}$，绝对不优。

修改边权后跑一个模板的最大权闭合子图就可以了。

下面的增量取的是 $10^{15}$。

## 代码

```cpp
#include<bits/stdc++.h>
#define N 500005
#define ll long long
using namespace std;
ll n,s,t,inf,i,j,k,x,y,a[N];
ll la[N],ne[N],to[N],dis[N],cur[N],tot=1,sum[N],val[N],ans;
inline void merge(ll x,ll y,ll z){tot++,ne[tot] = la[x],la[x] = tot,to[tot] = y,val[tot] = z,tot++,ne[tot] = la[y],la[y] = tot,to[tot] = x,val[tot] = 0;}
ll dfs(ll x,ll step){
	if(x==t) return step;
	ll used = 0;
	for(ll i=cur[x];i;i=ne[i]){
		cur[x] = i;
		if(dis[to[i]]+1==dis[x]&&val[i]>0){
			ll temp = dfs(to[i],min(val[i],step-used));
			val[i] -= temp,val[i^1] += temp,used += temp;
			if(used==step||dis[s]>=inf) return used;
		}
	}
	if(--sum[dis[x]]==0) dis[s] = inf;
	sum[++dis[x]]++;
	return used;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	s=0,t=2*n+1,inf=t-s+1;
	for(i=1;i<=n;i++){
		cin>>x;
		while(x--) cin>>y,merge(i,y+n,1e18);
	}
	for(i=1;i<=n;i++) cin>>a[i],a[i]=-a[i],a[i]+=1e15,merge(s,i,a[i]),ans+=a[i];
	for(i=1;i<=n;i++) merge(i+n,t,1e15);
	sum[0] = inf;
	while(dis[s]<inf){
		for(i=s;i<=t;i++) cur[i]=la[i];
		ans-=dfs(s,1e18);
	}
	cout<<-ans<<endl;
	return 0;
}
```

---

## 作者：wind_whisper (赞：4)

## $\text{Description}$
有一个大小为 $n$ 的全集，每个元素是一个数，有 $n$ 个子集。题目保证任意 $k$ 个子集的并的大小 $\geqslant k$ 。

每个子集有一个可正可负的权值，你需要选出一些子集使得这些子集并的大小等于子集个数，且所选子集的权值和最小。可以为空集。  
$n\le 300$
## $\text{Solution}$
一道网络流比较神的题。  
首先可以补集转化，选的权值最小，转化为不选的权值最大。  
然后由于这种题大多数都是转成最小割，所以把所有权值取反。  

然后就是关键的建图：  
原点向所有集合连容量等于集合权值 $INF$ 的边，集合向包含的数字连 $INF$ 的边，数字向汇点连 $INF$ 的边。  
显然，断数字和集合之间的边是不优的；而其中集合断边相当于不选，数字断边相当于选。  
这样，考虑任意一种割的方案，都说明选择了所有的集合和他们的数字的并集。  

但是怎么保证数字数量等于集合数量呢？  
假设左边断了 $x$ 条边，剩的 $n-x$ 个集合必然连向不少于 $n-x$ 个数，所以右边断边不少于 $n-x$ 条，总断边数不少于 $n$ 条。  
同时，只断 $n$ 条的方案显然存在（只砍一边就行），又由于每条边的权值加上了 $INF$，所以显然最终的答案就会断 $n$ 条。  
回到刚才断边的定义，就是：未选集合+选取元素=n，也就是选取集合数等于选取元素数。  
得证。  

## $\text{Description}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=3e5+100;
#define ll long long
#define ui unsigned int
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}  
  while (isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}    
  return x*f;
}

int n,m;

#define inf 1000000000ll
struct node{
  int to,nxt,cap;
}p[N];
int fi[N],cur[N],cnt;
inline void addline(int x,int y,int w){
  p[++cnt]=(node){y,fi[x],w};fi[x]=cnt;
  p[++cnt]=(node){x,fi[y],0};fi[y]=cnt;
  return;
}
int s,t;
int bel[N],q[N],st,ed;
bool bfs(){
  q[st=ed=1]=s;
  memset(bel,0,sizeof(bel));bel[s]=1;
  while(st<=ed){
    int now=q[st++];
    for(int i=cur[now]=fi[now];~i;i=p[i].nxt){
      int to=p[i].to;
      if(!p[i].cap||bel[to]) continue;
      bel[to]=bel[now]+1;q[++ed]=to;
    }
  }
  return bel[t]?1:0;
}
int dfs(int x,int lim){
  if(!lim||x==t) return lim;
  int res(0);
  for(int &i=cur[x];~i;i=p[i].nxt){
    int to=p[i].to;
    if(!p[i].cap||bel[to]!=bel[x]+1) continue;
    int add=dfs(to,min(lim,p[i].cap));
    res+=add;lim-=add;
    p[i].cap-=add;p[i^1].cap+=add;
    if(!lim) break;
  }
  if(!res) bel[x]=-1;
  return res;
}
ll dinic(){
  ll flow(0),tmp(0);
  while(bfs()){
    while((tmp=dfs(s,2e9))) flow+=tmp;
  }
  return flow;
}

signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  memset(fi,-1,sizeof(fi));cnt=-1;
  n=read();
  ll sum(0);
  s=2*n+1;t=s+1;
  for(int i=1;i<=n;i++) addline(i+n,t,inf);
  for(int i=1;i<=n;i++){
    int k=read();
    for(int j=1;j<=k;j++){
      int x=read();
      addline(i,x+n,inf);
    }
  }
  for(int i=1;i<=n;i++){
    int w=read();sum-=w;
    addline(s,i,inf-w);
  }
  printf("%lld\n",(dinic()-1ll*n*inf)-sum);
  return 0;
}
/*
*/

```


---

## 作者：teylnol_evteyl (赞：2)

网络流妙题。

先把所有的权值取相反数，求最大答案，最后再取相反数。

可以想到最大权闭合子图模型，对每个集合和数字都建立一个点，对于每个集合的点，如果权值大于于 $0$，则从源点向它连一条容量为权值的边，否则从它向汇点连一条容量为权值绝对值的边，然后向它包含的数字连一条容量为 $\infty$ 的边。

然后是数字会向集合连边。根据霍尔定理，因为 $k$ 个子集的并的大小大于等于 $k$，则一定存在完美匹配，所以可以猜到先找一组完美匹配，每个数字向它的匹配点连容量为 $\infty$ 的边。

答案就是所有正权集合的权值之和减去最小割。

考虑证明：

这实际上是在跑这样一个图的最大权闭合子图：

- 集合向它包含的数字连边。
- 数字向它匹配的集合连边。

对于选择的集合，它们的并集大小一定大于等于选择的数，而第二类边保证了选择的集合数大于等于选择的数字数，则选择的集合的并集大小一定等于集合数量。

对于一种满足条件的选择方案，假设它不是闭合子图，则说明了一些集合会和它并集之外的数字匹配，矛盾。

综上，选择方案和闭合子图是对应的。

[code](https://www.luogu.com.cn/paste/qfg5iceo)。

---

## 作者：mqmhaaaa1 (赞：1)

好题啊好题，感觉不止 2900。

# 题意

给你 $n$ 个集合，这些集合每个元素都是正整数且不大于 $n$。同时，每个集合有一个价值。问你选哪些集合，满足这些集合的并集内元素数量等于选择的集合数量（不选也行），且这些集合的价值之和最小。同时题目保证**题目保证任意 $k$ 个子集的并的大小 $ \ge k$**。

# 思路

不难想到，我们选择一个集合就相当于选择了集合内所有元素，于是很容易有一个大致的想法：将集合与每个元素连边，自然形成一个二分图，我们用每一个选择的集合去匹配元素（匹配自然是每个点只用一次），如果匹配的数量等于集合数量，则说明这些集合内所有元素的并集等于选择的集合数量，就满足了要求。

接下来解决两个问题：

1. 如何表示选哪些集合。

2. 如何求最小价值和。

# 办法

不难想出，如果理解为**选一个集合就得选集合内所有元素**这种思想，就会变成一个**闭合子图**问题，如果我们把价值取负，就会变成**最大权闭合子图**问题。但是，如何满足上述说的**元素数大于等于集合数**的限制呢。

事实上网络流里一直有一个套路，那便是用调配特殊的流量来满足限制，本题也不例外。

很容易发现，如果把每个元素的价值设为 $-\inf$（$\inf$ 是一个很大的数），每个集合的价值加上 $\inf$ 的话，在选择一个集合时，必然会将流量流向元素，再由元素流向汇点 $t$。

我们不妨这样想，几种情况：

1. 集合数等于元素数，那么所有多出来的 $\inf$ 与 $-\inf$ 抵消，只剩下原本的价值。

2. 集合数小于元素数，无法让所有元素到 $t$ 的边满流，就是说这些集合边被割了。

3. 集合数大于元素数，这不可能，因为题目满足**题目保证任意 $k$ 个子集的并的大小 $ \ge k$**，这也是本题的破局妙处。

那么，这样建图之后，无法满足要求的选择方式由源点 $s$ 到集合的边会被割掉，价值不够优也一样。只有价值够优，且满足条件的选择方式才能保证所选元素到汇点 $t$ 的所有边被割掉，不然就干脆一个不选。

这样就可以通过本题了，同时，以下有几个细节：

1. 除了上述的 $\inf$ 外，应该开一个更大的数，用来表示真实网络流图中的 $\inf$，建议 1e18。

2. 因为本题求最小价值，所以所有价值取反，记得输出的时候再翻回来。

3. 因为可以一个都不选，所以答案一定是小于等于 $0$ 的，算答案的时候记得和 $0$ 取 min。

看看码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
void write(ll x) {static ll sta[35];ll top = 0;do {sta[top++] = x % 10, x /= 10;} while (x);while (top) putchar(sta[--top] + 48);}
ll read() {ll x = 0, w = 1;char ch = 0;while (ch < '0' || ch > '9') {  if (ch == '-') w = -1;ch = getchar();}while (ch >= '0' && ch <= '9') {x = x * 10 + (ch - '0'); ch = getchar(); }return x * w; }
const ll N=1e3+10,M=1e6+10,inf=0x7f7f7f7f,inff=0x3f3f3f3f3f3f3f3f; //这里两个inf。inff是图中真正的最大数，inf是用来做限制的 
ll to[M<<1],nxt[M<<1],w[M<<1],bh[N],tot=1;
ll head[N],st[N];
bool vis[N];
inline void add(ll u,ll v,ll z){
	to[++tot]=v;
	nxt[tot]=bh[u];
	w[tot]=z;
	bh[u]=tot;
//	cout<<u<<" "<<v<<" "<<z<<'\n';
	to[++tot]=u;
	nxt[tot]=bh[v];
	w[tot]=0;
	bh[v]=tot;
}
ll s,t;
inline bool bfs(){
	for(ll i=s;i<=t;i++){
		head[i]=bh[i];
		vis[i]=0;
		st[i]=0;
	}
	queue<ll>q;
	q.push(s);
	st[s]=0;vis[s]=1;
	while(q.size()){
		ll u=q.front();q.pop();
//		cout<<u<<'\n';
		vis[u]=0;
		for(ll i=bh[u];i;i=nxt[i]){
			ll v=to[i];
			if(w[i]&&!st[v]&&v!=s){
				st[v]=st[u]+1;
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
	return st[t];
}
ll mxf=0;
ll dic(ll u,ll flow){
//	cout<<u<<" "<<flow<<'\n';
	vis[u]=1;
	if(u==t){
		mxf+=flow;return flow;
	}
	ll zy=0;
	for(ll i=head[u];i&&flow;i=nxt[i]){
		ll v=to[i];head[u]=i;
		if(w[i]&&(!vis[v]||v==t)&&st[v]==st[u]+1){
			ll jb=dic(v,min(w[i],flow));
			w[i]-=jb,w[i^1]+=jb;
			zy+=jb;flow-=jb;
			if(!flow)break;
		}
	}
	vis[u]=0;
	return zy;
}//令人骄傲的dinic 
ll fy[400],sum;
ll n;
int main(){
	n=read();
	s=0;t=n*2+1;
	for(ll i=1;i<=n;i++){
		ll m=read();
		add(i+n,t,inf);//这里偷点懒，直接用i+n表示元素i，所以直接建边 
		while(m--){
			ll v=read()+n;
			add(i,v,inff);//这里用图中真正的inff 
		}
	}
	for(ll i=1;i<=n;i++){
		fy[i]=read();
		add(s,i,inf-fy[i]);
		sum+=inf-fy[i];
		//记得取反 
	}
	while(bfs()){
		vis[t]=1;
		while(vis[t]){
			memset(vis,0,sizeof vis);
			dic(s,inff);//inff才是真无穷 
		}
	}
	cout<<min((ll)0,-(sum-mxf));//取反后再取min 
}

```

我的手机在自动充值源点.jpg。

---

## 作者：naoliaok_lovely (赞：1)

看题解区的基本都是增量的做法，这里给一个二分图匹配的。

## 分析
突破点肯定在于第一句话：这 $n$ 个子集的并集刚好是 $n$ 个元素，且任意 $k$ 个子集的并集大小 $\ge k$。显然这是一个二分图（左边表示集合，右边表示元素），进一步的，这句话其实可以翻译为：**这个二分图存在完美匹配！**（读者自证不难 qwq)

于是跑完美匹配，用一个元素代表一个集合，那么选择了这个元素就必须选择对应集合的其他元素。证明如下：  
我们称选择的所有集合对应的元素为 $A$ 类元素，被集合包含了且不属于 $A$ 类的为 $B$ 类，其余的为 $C$ 类。再设集合个数为 $cnt$。显然我们最后要使得 $cnt=|A|,|B|=0$。在我们选择一个集合之后，可能会使得 $|B|>0$。这时，如果我们选对应元素 $\in C$，那么显然 $|B|$ 不会变化；为了使 $|B|$ 减小，自然选择 $B$ 类对应的集合。

于是，我们可以对元素建图，题目就变成了最大权闭合子图的模板题。

```
#include<bits/stdc++.h>
using namespace std;

const int N = 610, M = 1e6 + 10;
int n, t, ans, id[N];
vector<int> s[N];

int h[N], ne[M], e[M], w[M], idx = 1;
void add(int a, int b, int c)
{
    e[++idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx;
}

int dis[N], cnt[N], cur[N];
int sap(int x, int inflow)
{
    if(x == t) return inflow;
    int outflow = 0;
    for(int i = cur[x]; i; i = ne[i])
        if(w[i] && dis[x] == dis[e[i]] + 1)
        {
            cur[x] = i;
            int flow = sap(e[i], min(inflow - outflow, w[i]));
            w[i] -= flow, w[i ^ 1] += flow, outflow += flow;
            if(inflow == outflow || dis[0] >= t + 1) return outflow;
        }
    if(!--cnt[dis[x]]) dis[0] = t + 1;
    cnt[++dis[x]]++, cur[x] = h[x];
    return outflow;
}

int main()
{
	cin >> n;
	for(int i = 1, cnt, x; i <= n; i++)
	{
		scanf("%d", &cnt);
		while(cnt--) scanf("%d", &x), s[i].push_back(x), add(i, n + x, 1), add(n + x, i, 0);
		add(0, i, 1), add(i, 0, 1), add(n + i, 2 * n + 1, 1), add(2 * n + 1, n + i, 0);
	}
	
	for(int i = 0; i <= 2 * n + 1; i++) cur[i] = h[i];
	t = 2 * n + 1;
	while(dis[0] < 2 * n + 2) sap(0, 1e9);
	for(int i = 1; i <= n; i++)
		for(int j = h[i]; j; j = ne[j])
			if(e[j] && !w[j]) id[i] = e[j] - n;
	memset(h, 0, sizeof(h)), idx = 1;
	memset(dis, 0, sizeof(dis));
	memset(cnt, 0, sizeof(cnt));
	
	for(int i = 1; i <= n; i++)
		for(int j : s[i]) add(id[i], j, 1e9), add(j, id[i], 0);
	for(int i = 1, x; i <= n; i++)
	{
		scanf("%d", &x), x = -x;
		if(x >= 0) ans += x, add(0, id[i], x), add(id[i], 0, 0);
		else add(id[i], n + 1, -x), add(n + 1, id[i], 0);
	}
	for(int i = 0; i <= n + 1; i++) cur[i] = h[i];
	t = n + 1;
	while(dis[0] < n + 2) ans -= sap(0, 1e9);
	cout << -ans << endl;
	return 0;
}
```

---

## 作者：sunzh (赞：1)

我们要求集合数与集合并的大小相等，且最后的价格最小

我们考虑把价格取相反数，因为$n\le 300$，显然可以网络流

因为价格有正有负，我们从源点到集合的流量统一取$inf+(-p_i)$，对每个数向汇点取$inf$，然后集合到每个数的流量取一个远大于inf的数即可

我们来证明他的正确性

对于一个权值和$>=0$的集合集，左边的流量一定会流满，因为对应的右边至少有$k\times inf$的流量，

对于一个权值和$<0$的集合集，若对应的右边个数$>k$，只要$inf$取得足够大，多余流量都会流满，因此流不满的情况当且仅当权值和$<0$且对应的右边节点数等于左边节点数

我们跑一个最大流，把左边的满流-maxflow即可



---

## 作者：liujy_ (赞：0)

很好的一个题。  
首先我们将集合和元素看成二分图的两个部分，这样的话原图要求的东西就是一个闭合子图。所以可以权值取反转为最大权闭合子图。  
继续考虑并集等于所选集合元素的这一个要求，我们发现题目给了任意 $k$ 个集合并集大小大于等于 $k$ 这一性质，也就是说，如果我给选择每一个元素的代价减去一个巨大的权值，给选择一个集合的代价加上相同的权值，那么我选择一个闭合子图总的权值和中减去这个巨大的权值的量肯定是大于等于零的。所以这个时候再来跑最大权闭合子图肯定是减去权值正好为零的一个闭合子图会更优。   

另外一个做法是，首先根据 Hall 定理该图存在完美匹配。跑出一个完美匹配来。  
然后继续观察，我们对于一个集合点考虑找到一个最小的包含他的合法闭合子图。首先选了他之后属于他的元素肯定都得选。  
然后对于一个元素点，他在闭合子图里，但是他的匹配点不在的话，我们说明他的匹配点也必须在这里面。具体来说，假设我们选择了一个包含该元素但是并不是他的匹配的集合点进来的话，那么这个集合点的匹配的元素点也会被加进来，所以这只会让元素点与集合点的个数的差值不变或变大，只有加入一开始这个元素的匹配的集合进来才可能让这个东西变小。  
到这一步后，相当于是一些元素点之间有了选了你就必须选择我这样子的关系，可以对元素点建图跑最大权闭合子图。

---

## 作者：User_Authorized (赞：0)

由于已经满足对于任意 $k$ 个集合的大小不小于 $k$。因此只需要保证对于任意 $k$ 个集合的大小不大于 $k$ 即可满足题目限制要求。

这也就是意味着只要选择了一个元素，那么就必须选择一个集合，否则该解就是不合法的。

不妨将集合的权值均增加一个较大值，同时让每个元素的权值均减少一个较大值，这里的较大值要满足任意答案减去这个值均不会是最优解。

剩下的问题就是如何求出最优解，由于元素有负权值，因此是有最小权闭合子图解决即可。

---

## 作者：dz_ice (赞：0)

[博客里阅读](https://www.cnblogs.com/dzice/p/13061241.html)

~~最近博客里奇奇怪怪的东西越来越多了~~,是时候写一篇题解了

这是模拟赛的一道题，考试时只会打暴力QWQ，后来发现这道题的建图真的十分巧妙

首先，看到$n<=300$的数据范围，很像是网络流，我们先把子集和子集中的元素拆开来看，将子集的价值取相反数，最后输出答案时再取个相反数，于是便为选了这个子集就必须要选其中的元素，使得选出的子集价值尽量大，将子集向元素连$inf$边，那么这就是一个最大权闭合子图的模型，

然后难点在于如何处理使得子集并的大小等于子集个数，看到题目中给的“任意$k$个子集的并的大小$k\ge k$”，我们可以想一想如何从这个角度来建图，由源点向子集连$lim+P_i$的边($lim$是比$inf$小的一个极大值，防止$inf$边被割掉)，这条边被割意味着不选这个子集，由元素向汇点连$lim$边，这条边被割意味着这个元素最终会被选，这里可以~~感性理解一下~~画个图手玩一下，最终被割掉的边肯定为$n$条，并且任意$k$个子集的并的大小$k\ge k$

放个代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int s,t,dep[1003],n,t1,x,p,ans;
vector<int>l[1003],l1[1003],nu[1003];
queue<int>q;
void bfs()
{
	memset(dep,0,sizeof(dep));
	q.push(s),dep[s]=1;
	while(!q.empty())
	{
		p=q.front(),q.pop();
		for(int j=0;j<l[p].size();j++)
			if(l1[p][j]!=0&&dep[l[p][j]]==0)
				q.push(l[p][j]),dep[l[p][j]]=dep[p]+1;
	}
}
int dfs(int x1,int wat)
{
	if(x1==t)
		return wat;
	int sum=0,cnt;
	for(int j=0;j<l[x1].size();j++)
		if(l1[x1][j]!=0&&dep[l[x1][j]]==dep[x1]+1)
			cnt=dfs(l[x1][j],min(l1[x1][j],wat)),l1[x1][j]-=cnt,l1[l[x1][j]][nu[x1][j]]+=cnt,sum+=cnt,wat-=cnt;
	if(sum==0)
		dep[x1]=0;
	return sum;
}
void add(int x,int y,int wat)
{
	l[x].push_back(y),l[y].push_back(x),l1[x].push_back(wat),l1[y].push_back(0),nu[x].push_back(l[y].size()-1),nu[y].push_back(l[x].size()-1);
}
signed main()
{
	scanf("%lld",&n);
	s=0,t=2*n+1;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&t1);
		add(i+n,t,5e8);
		for(int j=1;j<=t1;j++)
		{
			scanf("%lld",&x);
			add(i,x+n,2e9);
		}
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&x);
		add(s,i,5e8-x),ans+=5e8-x;
	}
	while(1)
	{
		bfs();
		if(dep[t]==0)
			break;
		ans-=dfs(s,2e9);
	}
	cout<<min(0ll,-ans);
	return 0;
}

```

---

