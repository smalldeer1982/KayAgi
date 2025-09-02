# [EC Final 2022] Coloring

## 题目描述

给定 $n$ 个元素，编号从 $1$ 到 $n$。元素 $i$ 的值为 $w_i$，颜色为 $c_i$。每个元素还有一个指针 $a_i$ 指向另一个元素。

最初，元素 $s$ 的颜色为 $1$，而所有其他元素的颜色都为 $0$。更正式地说，对于所有 $i\neq s$ $(1 \le i \le n)$，有 $c_s=1$ 和 $c_i=0$。

你可以任意多次执行以下操作：

- 以代价 $p_i$ 将 $c_i\leftarrow c_{a_i}$。

你的得分等于所有颜色为 $1$ 的元素值的总和减去操作的总代价。

找出你能够获得的最大可能得分。

## 样例 #1

### 输入

```
3 1
-1 -1 2
1 0 0
3 1 2```

### 输出

```
1```

## 样例 #2

### 输入

```
10 8
36175808 53666444 14885614 -14507677 
-92588511 52375931 -87106420 -7180697 
-158326918 98234152
17550389 45695943 55459378 18577244 
93218347 64719200 84319188 34410268 
20911746 49221094
8 1 2 2 8 8 4 7 8 4```

### 输出

```
35343360```

# 题解

## 作者：_jimmywang_ (赞：4)

晃了一圈没找到题解，官方题解又简略的很，因此记之。

首先对所有 $a_i$ 向 $i$ 连边可构成基环外向树森林，此时若有边 $(u,v)$ 即为可以进行操作 $c_u := c_v$，就是能将 $c_u$ 赋值给 $c_v$。

先不考虑这个 $s$ 的位置，考虑如果有一个环上的点 $rt$，它颜色的改变对子树的影响。

由于上面的连边方式，每次 $rt$ 都能将子树内任意一个与 $rt$ 连通的连通块染成和 $rt$ 一样的颜色。而为了最优，这次染色一定不会把上次染的全部覆盖掉（要不然上一次就白干了），因此最终子树内一定是 01 分层的情况，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ja6qo5cl.png)

其中 $rt=1$。注意分层并不是严格按照深度，而是按照每次染的点决定的。

显然越多的变换次数会给子树带来更多可能性，当也会增加 $p$ 的消耗。于是我们考虑在每棵子树都 $dp$ 出 $dp[u][i]$ 表示以 $u$ 为根的子树， $u$ 变换了 $i$ 次后 $u$ 的子树权值最大值（同时对 $rt$ 进行环上的贡献提前计算）。

需要对 $s$ 进行特殊处理。实现不难，具体的看代码。此处复杂度 $O(n^2)$。

如果 $s$ 不在环上，显然 $ans=\max(dp[s][0],dp[s][1])$ 就完事了。接下来考虑 $s$ 在环上的部分。

记 $r_i$ 为环上点 $i$ 01 变换了几次。若将 $s$ 作为环的起点且 $r_s$ 视作初始为 1，则有结论：从 $s$ 开始按照边的顺序，$r$ 单调不增且极差 $\le 2$。~~请自己手摸尝试证明或感性理解。~~

而且反过来，任意一组满足上述条件的 $r$ 都对应了一个变换结果（不一定唯一）。~~还是请自己手摸尝试感性理解。~~

因此在环上，我们可枚举 $r_s$，并进行 $dp$，$f[i][0/1/2]$ 表示环上第 $i$ 个点的 $r$ 为 $r_s/r_s-1/r_s-2$ 时的最大值。不难写。

做完了，有一些细节，然后是代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(ll i=a;i<=b;i++)
inline ll rd(){
    ll x=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c))x=x*10+c-'0',c=getchar();
    return x*f;
}
#define d rd()
ll n,m,s;
ll w[5010],p[5010];
vector<ll>e[5010],ee[5010];
ll in[5010];
bool vis[5010];
queue<ll>q;
ll dis[5010];
ll dp[5010][5010];
void dfs(ll u){
    f(i,0,n){
        ll x=(i&1);if(u==s)x^=1;
        dp[u][i]=x*w[u]-i*p[u];
    }for(int i=0;i<e[u].size();i++){
        ll v=e[u][i];if(!vis[v])continue;
        dfs(v);ll mx=dp[v][0];
        f(j,0,n)dp[u][j]+=(u==s?max(mx,dp[v][j+1]):mx),mx=max(mx,dp[v][j+1]);
    }dp[u][n+1]=-1e18;
}
ll lp[5010],cl;
void dfl(ll u){
	if(u==s&&cl)return;
	lp[++cl]=u;
	for(int i=0;i<e[u].size();i++){
		ll v=e[u][i];if(vis[v])continue;
		dfl(v);
	}
}
ll sum[5010][5010];
ll f[5010][3],res=-1e18;
#define Max(a,b) (a>b?a:b)
int main(){
    n=d,s=d;f(i,1,n)w[i]=d;f(i,1,n)p[i]=d;
    f(i,1,n){
        ll x=d;e[x].push_back(i);
        ee[i].push_back(x);in[x]++;
    }f(i,1,n)if(!in[i])q.push(i);
    while(!q.empty()){
        ll u=q.front();q.pop();
        vis[u]=1;for(int i=0;i<ee[u].size();i++){
            ll v=ee[u][i];if(in[v]&&!(--in[v]))q.push(v);
        }
    }if(vis[s]){
        dfs(s);cout<<max(dp[s][0],dp[s][1]);return 0;
    }dfl(s);f(i,1,cl)dfs(lp[i]);
    if(cl==2){
    	cout<<max(dp[s][0]+dp[lp[2]][1],max(dp[s][1]+dp[lp[2]][0],dp[s][0]+dp[lp[2]][0]));
    	return 0;
    }
   	f(k,1,n+1){
   		f[1][0]=dp[s][k-1],f[1][1]=f[1][2]=-1e18;
   		f(i,2,cl){
   			f[i][0]=f[i-1][0]+dp[lp[i]][k];
   			f[i][1]=max(f[i-1][0],f[i-1][1])+dp[lp[i]][k-1];
   			if(k>=2)f[i][2]=max(f[i-1][0],max(f[i-1][1],f[i-1][2]))+dp[lp[i]][k-2];
   			if(f[i][0]<-1e18)f[i][0]=-1e18;
    		if(f[i][1]<-1e18)f[i][1]=-1e18;
    		if(f[i][2]<-1e18)f[i][2]=-1e18;
   		}res=max(res,max(f[cl][1],f[cl][0]));
   		if(k>=2)res=max(res,f[cl][2]);
   	}cout<<res;
    return 0;
}

```

---

## 作者：FFTotoro (赞：2)

连边 $a_i\to i$ 建出外向基环树，方便接下来的处理。

先考虑如果 $s$ 不在环上怎么做，即解决树的问题。不妨认为 $s$ 为根；对于不是 $s$ 的每个结点 $u$，考虑其颜色改变的次数 $c_u$，那么**它的儿子 $k$ 必然满足 $c_u\ge c_k$**（因为对于一个结点，如果在连续的两次操作中给了它相同的颜色，那么后面一个操作就没有意义）；结点 $s$ 特殊一些，它的儿子只需满足 $c_u+1\ge c_k$。

于是做树形 DP，设 $f_{u,i}$ 表示结点 $u$ 颜色被改变了 $i$ 次，$u$ 子树能产生的最大得分。初始时 $f_{u,i}=((i+[u=s])\bmod 2)\cdot w_u-i\cdot p_u$（其中 $[]$ 表示艾弗森括号），转移时对于每个儿子 $k$，$f_{u,i}\gets f_{u,i}+\max\limits_{j=0}^{i+[u=s]}f_{k,j}$。

可以针对这个 DP 的过程进行操作的构造，所以它的正确性并没有问题。使用前缀 $\max$ 优化即可做到 $O(n^2)$。

于是对于 $s$ 不在环上的情况，答案即为 $\max\limits_{j=0}^n f_{s,j}$。进一步地，可以证明答案即为 $\max\{f_{s,0},f_{s,1}\}$，只需要考虑 DP 的过程，其他情况都可以调整成更优的。

---

对于 $s$ 在环上且环长 $=2$ 的情况，令环上另一个点为 $t$，答案为 $\max\{f_{s,0}+f_{t,0},f_{s,1}+f_{t,0},f_{s,0}+f_{t,1}\}$。

对于 $s$ 在环上且环长 $>2$ 的情况，同样地令 $c_u$ 表示点 $u$ 颜色改变的次数，**并且将 $c_s$ 视为 $1$**。令该环为 $\mathrm{cyc}_1(=s)\to\mathrm{cyc}_2\to\cdots\to\mathrm{cyc}_k(=t)$，那么有如下的结论：

- $c_{\mathrm{cyc}_{i+1}}\le c_{\mathrm{cyc}_i}$；
- $c_s-c_t\le 2$。

前者是显然的，因为一个结点的前驱没法给它提供更多的次数。后者只需考虑最大化不等式左边的值，让 $t$ 把颜色 $0$ 推给 $s$，这样 $c_s=2$，而其他点 $c_{\mathrm{cyc}_i}=0$，此时差为 $2$：想让 $c_s$ 变得更大，需要把 $s$ 最开始时的颜色 $1$ 在环上推一圈，此时其他的 $c_{\mathrm{cyc}_i}$ 变为 $1$，差仍然为 $2$，所以后者是正确的。

于是枚举 $c_s=r=1,2,\ldots,n+1$，再做一个 DP $g_{i,j}(0\le j\le 2)$ 表示考虑了环上前 $i$ 个点，$c_{\mathrm{cyc}_i}=r-j$ 的最大答案（对于环上每个点做树形 DP 求解）。于是初始状态为 $g_{1,0}=f_{s,r-1}$（$-1$ 是因为将 $c_s$ 的初始状态视为 $1$，所以应该减掉），$g_{1,1}=g_{1,2}=-\infin$。对于 $i>1$ 有转移 $g_{i,j}=f_{\mathrm{cyc}_i,r-j}+\max\limits_{k=0}^j g_{i-1,k}$。在这些 $r$ 中取答案最大的即可。

时间复杂度 $O(n^2)$，可以通过。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll I=1e18;
inline void chmax(ll &x,ll y){if(y>x)x=y;}
vector<int> find_cycle(vector<int> a){
  int x=0; vector<bool> b(a.size());
  while(!b[x])b[x]=true,x=a[x];
  fill(b.begin(),b.end(),false);
  vector<int> c;
  while(!b[x])c.emplace_back(x),b[x]=true,x=a[x];
  return c;
} // 基环树找环
int main(){
  ios::sync_with_stdio(false);
  int n,s; cin>>n>>s,s--;
  vector<int> w(n),p(n),a(n);
  for(auto &i:w)cin>>i;
  for(auto &i:p)cin>>i;
  for(auto &i:a)cin>>i,i--;
  vector<vector<int> > g(n);
  for(int i=0;i<n;i++)
    g[a[i]].emplace_back(i);
  vector<int> c=find_cycle(a);
  reverse(c.begin(),c.end());
  vector<bool> b(n);
  for(int i:c)b[i]=true;
  vector f(n,vector<ll>(n+2));
  function<void(int)> dfs=[&](int u){
    for(int i=0;i<=n;i++)
      f[u][i]=(i&1^(u==s)?w[u]:0)-(ll)i*p[u];
    f[u][n+1]=-I;
    for(int i:g[u])
      if(!b[i]){
        dfs(i); ll mx=-I;
        for(int j=0;j<=n;j++){
          chmax(mx,f[i][j]);
          f[u][j]+=max(mx,u==s?f[i][j+1]:-I);
        } // 前缀和优化转移
      }
  }; // 进行树形 DP
  if(b[s]){
    rotate(c.begin(),find(c.begin(),c.end(),s),c.end());
    // 使 s 成为环上第一个点
    for(int i:c)dfs(i); // 对于环上每个点跑树形 DP
    if(c.size()==2)cout<<max({f[s][0]+f[c[1]][0],f[s][0]+f[c[1]][1],f[s][1]+f[c[1]][0]})<<endl,exit(0);
    // 注意特判 k=2
    ll w=-I;
    for(int r=1;r<=n+1;r++){
      vector g(c.size(),vector<ll>(3,-I));
      g[0][0]=f[s][r-1];
      for(int i=1;i<c.size();i++){
        chmax(g[i][0],g[i-1][0]+f[c[i]][r]);
        chmax(g[i][1],max(g[i-1][0],g[i-1][1])+f[c[i]][r-1]);
        if(r>1)chmax(g[i][2],max({g[i-1][0],g[i-1][1],g[i-1][2]})+f[c[i]][r-2]);
      } // 在环上跑外层 DP
      chmax(w,*max_element(g.back().begin(),g.back().end()));
    }
    cout<<w<<endl;
  }
  else dfs(s),cout<<max(f[s][0],f[s][1])<<endl;
  return 0;
}
```

---

## 作者：Rem_CandleFire (赞：2)

模拟赛搬了这题，感觉很神奇，写篇题解记录一下。

[推销博客](https://www.luogu.com.cn/user/421421#article)

### 分析与做法

首先将每一个 $a_i$ 向 $i$ 连一条有向边，这样的好处是可以从环上往外建立出外向基环树（似乎是这个名字），方便了后续的操作。对于基环树，我们自然要找环，这里采取了拓扑排序找环的方式，当然也可以深搜等方法，不多赘述。

接下来我们要对给出的点 $S$ 的位置进行讨论。

若 $S$ 不在环上，则很显然问题转化成了单纯的树上问题，因为用其它颜色为 $0$ 的点将 $S$ 覆盖掉对于答案没有意义。考虑树上问题如何去做。设 $f_{u,i}$ 表示以 $u$ 为根的子树中，节点 $u$ 的颜色改变了 $i$ 次的最大价值。有初始化 $f_{u,i}=x\times w_u-i\times p_u $。这里的意思是，对于一个不是 $S$ 的节点 $u$，赋值奇数次可以获得价值（即 $x=i\bmod 2$），以节点 $S$ 为根时刚好相反（即 $x=(i+1)\bmod2$）。

设 $v$ 是 $u$ 的子节点，有转移 $f_{u,i}=\max_{j=0}^{i} {f_{v,j}}$，$j$ 要小于等于 $i$ 的原因是在 $u$ 的子树之下不存在节点比 $u$ 颜色改变了更多次，可能会覆盖之前的某次赋值结果，特殊的是，$S$ 可以允许取到 $j=i+1$。这个转移可以通过简单的前缀取最大值优化到 $O(n^2)$。

对于 $S$ 不在环上的情况，答案就是 $\max(f_{S,0},f_{S,1})$，表示节点 $S$ 不改变，或只改变一次颜色，更多的改变一定不优。

对于 $S$ 在环上的情况，每次处理到环的一个节点时，可以顺便考虑了它的子树，即基本套路：先处理子树，再考虑环上问题。而子树事实上也能通过上述 DP 来解决，只是要增加判断避免通过环上的边。此时拓扑排序求环的方便之处就得到了体现（打标记简单，代码简短）。处理了每一个子树之后，考虑环上如何处理。

仍然设环上的点 $u$ 改变颜色的次数为 $c_u$，且初始时设 $c_S=1$，不妨设 $S$ 为环的起点，**则顺着有向边的方向 $c_u$ 单调不增且极差小于等于 $2$**。考虑感性理解，想象一个环，起始点是 $S$，设节点 $T$ 指向了 $S$ 作为环的结束边。

- 若 $S$ 点需要被染白，则由 $T$ 将 $S$ 染色，符合结论。
- 若需要将 $S$ 之后的若干点染黑，则从 $S$ 开始将以下点染黑即可，符合结论（这也是一开始将 $c_u$ 设为 $1$ 的意义）。
- 若染黑之后需要将其中一段染白，则需从 $T$ 开始绕环染色，符合结论。
- 不会出现超过两段的黑白交替的情况，这是染色方式决定的。

综上所述呢，我们感性理解了这一个结论。不妨设从 $l_1=S$ 开始环上的点依次为 $l_2,l_3\dots,l_m$，其中 $l_m=T$。设 $d_{i,j}$ 表示前 $i$ 个环上点，其中第 $i$ 个点颜色改变的次数和 $S$ 相差 $j$ 的最大价值（$j=0,1,2$）。

考虑如何转移，每次枚举 $k$ 表示节点 $S$ 的改变次数，每个 $i=2,3\dots,m$ 转移时对于 $j=0,1,2$ 分别写式子就行了，不难写。

- $d_{i,0}=d_{i-1,0}+f_{l_i,k}$。
- $d_{i,1}=\max(d_{i-1,0},d_{i-1,1})+f_{l_i,k-1}$。

$d_{i,2}$ 的情况是类似的，懒得写了。答案就是所有的 $k$ 中 $d_{m,j}$ 最大值的最大值。

代码实现略有些细节，注释了。时间复杂度 $O(n^2)$。

### Code

```
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=5e3+5;
const LL Inf=1e18;
int n,m,S;
int in[N],cir[N],lp[N];
LL f[N][N],d[N][4],w[N],p[N];
vector<int> g[N],ng[N];
void Find_Circle(int u) // 找环 
{
	if(u==S&&m) return ; // 找完一圈 
	lp[++m]=u; // 记录 
	for(auto v:g[u]) 
		if(!cir[v]) Find_Circle(v);
}
void Circle() // 拓扑排序标记环 
{
	queue<int> q;
	for(int i=1;i<=n;i++) if(!in[i]) q.push(i);
	while(!q.empty())
	{
		int u=q.front(); q.pop();
		cir[u]=1; // 不在环上为 1，在为 0 
		for(auto v:ng[u])
			if(in[v]&&!(--in[v])) q.push(v);
	}
}
void Solve_Tree(int u)
{
	for(int i=0;i<=n;i++)
	{
		int x=(i&1); x^=(u==S);
		f[u][i]=x*w[u]-i*p[u]; // 初始化 
	}
	f[u][n+1]=-Inf;
	for(auto v:g[u])
	{
		if(!cir[v]) continue; // 防止环上的点沿着环走
		Solve_Tree(v);
		LL mx=f[v][0];
		for(int j=0;j<=n;j++)
		{
			f[u][j]+=(u==S?max(mx,f[v][j+1]):mx);
			mx=max(mx,f[v][j+1]); // 前缀 max 优化 
		}
	}
}
int main()
{
	scanf("%d%d",&n,&S);
	for(int i=1;i<=n;i++) scanf("%lld",&w[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&p[i]); // 记得开 LL 
	for(int x,i=1;i<=n;i++)
	{
		scanf("%d",&x);
		g[x].push_back(i);
		ng[i].push_back(x); in[x]++; // 拓扑排序需要反图 
	}
	Circle();
	if(cir[S]) // 不在环上 
	{
		Solve_Tree(S);
		return !printf("%lld\n",max(f[S][0],f[S][1])); // 将 return 0 和 printf 压行了 
	}
	Find_Circle(S);
	for(int i=1;i<=m;i++) Solve_Tree(lp[i]); // DP 所有子树 
	if(m==2) return !printf("%lld",max({f[S][0]+f[lp[2]][1],f[S][0]+f[lp[2]][0],f[S][1]+f[lp[2]][0]}));
	// 对于两个点的环需要特判以下，不然过不了 
	LL ans=-Inf;
	for(int k=1;k<=n+1;k++)
	{
		fill(&d[0][0],&d[m+1][3],-Inf); // 记得初始化 
		d[1][0]=f[S][k-1];
		for(int i=2;i<=m;i++)
		{
			d[i][0]=d[i-1][0]+f[lp[i]][k];
			d[i][1]=max(d[i-1][0],d[i-1][1])+f[lp[i]][k-1];
			if(k>=2) d[i][2]=max({d[i-1][0],d[i-1][1],d[i-1][2]})+f[lp[i]][k-2]; // 分别转移 
			for(int j=0;j<=2;j++) d[i][j]=max(d[i][j],-Inf); // 如果转移了更劣不如不转	
		}
		ans=max(ans,max(d[m][0],d[m][1]));
		ans=max(ans,d[m][2]); // 取最值 
	}
	printf("%lld",ans);
	return 0;
}

```

---

