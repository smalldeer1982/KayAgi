# [ABC263G] Erasing Prime Pairs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc263/tasks/abc263_g

黒板に $ N $ 種類の整数が書かれています。 $ i $ 種類目の整数は $ A_i $ で、書かれている個数は $ B_i $ 個です。

あなたは次の操作を可能な限り繰り返すことができます。

- 黒板に書かれている $ 2 $ 個の整数 $ x,y $ であって、$ x+y $ が素数であるものを選ぶ。 選んだ $ 2 $ 個の整数を黒板から消す。

操作を最大で何回行えるか求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ A_i\ \leq\ 10^7 $
- $ 1\ \leq\ B_i\ \leq\ 10^9 $
- $ A_i $ は全て異なる
- 入力は全て整数

### Sample Explanation 1

$ 2\ +\ 3\ =\ 5 $ であり、$ 5 $ は素数なので、$ 2 $ と $ 3 $ を選んで消す操作が行えます。また、それ以外の操作は行えません。 $ 2 $ は $ 4 $ 個、 $ 3 $ は $ 3 $ 個あるので、操作を $ 3 $ 回行うことができます。

### Sample Explanation 2

$ 1+\ 1\ =\ 2 $ であり、$ 2 $ は素数なので、$ 1 $ と $ 1 $ を選んで消す操作が行えます。$ 1 $ は $ 4 $ 個あるので、操作を $ 2 $ 回行うことができます。

## 样例 #1

### 输入

```
3
3 3
2 4
6 2```

### 输出

```
3```

## 样例 #2

### 输入

```
1
1 4```

### 输出

```
2```

# 题解

## 作者：liangbowen (赞：3)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc263_g)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17487119.html)

网络流。很好的题目。

## 思路

数据范围不大但是又跑不了指数算法，所以考虑网络流。

对于绝大多数情况，$a_i + a_j$ 是质数当且仅当 $a_i$ 是奇数且 $a_j$ 是偶数（反过来同理）。

所以有一个显然的做法：
+ $S \xrightarrow{1} a_i\ (a_i \text{ is odd})$。
+ $a_i \xrightarrow{1} T\ (a_i \text{ is even})$。
+ $a_i \xrightarrow{\infty} a_j\ (a_i \text{ is odd} \wedge a_j \text{ is even} \wedge (a_i + a_j) \text{ is prime})$。
+ 跑最大流即可。

唯一的反例是 $1+1=2$。这意味着要**尽可能多**地留下 $1$。显而易见，最小费用最大流模型，费用即 $1$ 留下的个数。

答案即 $\text{flow} + \left\lfloor\dfrac{\text{count of 1} - \text{cost}}2\right\rfloor$。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
typedef long long ll;
const int N = 1005; const ll inf = 0x3f3f3f3f3f3f3f3f;
namespace Graph {
	struct Edge {int now, nxt; ll w, cost;} e[1919810];
	int head[N], cur = 1;
	void ad(int u, int v, ll w, int cost)
	{
		e[++cur].now = v, e[cur].nxt = head[u], e[cur].w = w, e[cur].cost = cost;
		head[u] = cur;
	}
	void add(int u, int v, ll w, int cost) {ad(u, v, w, cost), ad(v, u, 0, -cost);}
	ll dis[N], icost[N]; int pre[N]; bool inque[N];
	int s, t;
	bool spfa()
	{
		queue <int> q;
		memset(dis, inf, sizeof dis), memset(icost, 0, sizeof icost);
		q.push(s), dis[s] = 0, icost[s] = inf, inque[s] = true;
		while (!q.empty())
		{
			int u = q.front();
			q.pop(), inque[u] = false;
			for (int i = head[u]; i; i = e[i].nxt)
			{
				int v = e[i].now;
				if (!e[i].w) continue;
				if (dis[u] + e[i].cost < dis[v])
				{
					dis[v] = dis[u] + e[i].cost, pre[v] = i;
					icost[v] = min(icost[u], e[i].w);
					if (!inque[v]) q.push(v), inque[v] = true;
				}
			}
		}
		return icost[t] > 0;
	}
	void EK(ll &flow, int &cost)
	{
		while (spfa())
		{
			ll w = icost[t];
			flow += w, cost += w * dis[t];
			for (int i = t; i != s; i = e[pre[i] ^ 1].now)
				e[pre[i]].w -= w, e[pre[i] ^ 1].w += w;
		}
	}
}; using namespace Graph;


int val[N], cnt[N];
bool isprime(int x)
{
	if (x <= 1) return false;
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0)
			return false;
	return true;
}
int main()
{
	int n, cnt1 = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &val[i], &cnt[i]);
		if (val[i] == 1) cnt1 += cnt[i];
	}
	
	s = 0, t = n + 1;
	for (int i = 1; i <= n; i++)
		if (val[i] % 2 == 1) add(s, i, cnt[i], val[i] == 1);
		else add(i, t, cnt[i], 0);
	for (int i = 1; i <= n; i++)
		if (val[i] % 2 == 1)
			for (int j = 1; j <= n; j++)
				if (val[j] % 2 == 0 && isprime(val[i] + val[j]))
					add(i, j, inf, 0);
	
	ll flow = 0; int cost = 0;
	EK(flow, cost);
	cout << flow + (cnt1 - cost) / 2;
	return 0;
}
```

希望能帮助到大家！

---

## 作者：rizynvu (赞：2)

[我的博客](https://www.cnblogs.com/rizynvu/p/18498740)。

$a_i$ 和质数看着并没有很特殊，于是一些贪心或者是 DP 的大抵是做不了的。

于是一个想法是对于 $a_i + a_j = p(p\in \mathbf{P})$ 的 $(i, j)$ 连边，然后跑网络流。  
但是需要确定的是这个建出来的图能不能拿来跑。

能够发现的是对 $p\in \mathbf{P}, p\not = 2$，都满足 $p\bmod 2 = 1$，这说明这些和为 $p$ 的连边都是由  $a_i\bmod 2 = 0$ 和 $a_i\bmod 2 = 1$ 连上的，那么显然为一个二分图。  

于是就可以建图了。  
对于 $a_i\bmod 2 = 1$，连边 $(\operatorname{S}, i, b_i)$；对于 $a_i\bmod 2 = 0$，连边 $(i, \operatorname{T}, b_i)$。  
对于 $a_i\bmod 2 = 1, a_j\bmod 2 = 0, a_i + a_j=  p(p\in \mathbf{P})$，连边 $(i, j, \operatorname{inf})$。

注意到其实还有 $p = 2$ 的特殊情况。  
但时发现此时只有可能是 $(1, 1)$。  
于是可以最后跑完看下 $1$ 还有多少流量没用，就可以计算了（因为用 $1$ 个 $1$ 显然比 $2$ 个 $1$ 优）。

但是一个问题是如果直接最大流可能会导致没有先去配对 $(a_i, a_j)(a_i\not = 1)$ 而是去配对了 $(1, a_j)$。  
这可能导致 $1$ 剩余流量变少而使答案变小。

于是可以先不把 $1$ 加入图中跑一次最大流，此时就已经保证了非 $1$ 的奇数已经尽量匹配完了。  
然后再加入 $1$，再跑一次最大流，让 $1$ 去匹配。  
最后再统计流量即可。

时间复杂度 $\mathcal{O}(V + \operatorname{flow}(n, n^2))$。

```cpp
#include<bits/stdc++.h>
using ll = long long;
constexpr ll inf = 1e18;
int N, S, T;
namespace flow {
   static const int maxn = 1e2 + 10, maxm = 2e4 + 10;
   ll val[maxm * 2];
   int to[maxm * 2], nxt[maxm * 2], fir[maxn], tot = 1;
   inline void add(int x, int y, ll w, bool f = 1) {
      to[++tot] = y, val[tot] = w, nxt[tot] = fir[x], fir[x] = tot;
      if (f) add(y, x, 0, 0);
   }
   int hd[maxn], dep[maxn];
   inline bool bfs() {
      for (int i = 1; i <= N; i++)
         hd[i] = fir[i], dep[i] = -1;
      dep[S] = 0;
      std::queue<int> Q; Q.push(S);
      while (! Q.empty()) {
         int u = Q.front(); Q.pop();
         if (u == T) return true;
         for (int i = hd[u]; i; i = nxt[i])
            if (dep[to[i]] == -1 && val[i])
               dep[to[i]] = dep[u] + 1, Q.push(to[i]);
      }
      return false;
   }
   inline ll dfs(int u, ll fl) {
      if (u == T) {
         return fl;
      }
      ll ud = 0;
      for (int &i = hd[u]; i; i = nxt[i])
         if (dep[u] + 1 == dep[to[i]] && val[i]) {
            ll k = dfs(to[i], std::min(fl - ud, val[i]));
            if (! k) dep[to[i]] = -1;
            ud += k, val[i] -= k, val[i ^ 1] += k;
            if (ud == fl)
               return fl;
         }
      return ud;
   }
   inline ll Dinic() {
      ll ans = 0, f;
      while (bfs()) {
         while ((f = dfs(S, inf)) > 0) {
            ans += f;
         }
      }
      return ans;
   }
};
const int maxn = 1e2 + 10, maxV = 2e7 + 10, V = 2e7;
std::bitset<maxV> f;
int n;
int a[maxn], b[maxn];
int main() {
   for (int i = 2; i <= V; i++) {
      if (! f[i]) {
         for (int j = i + i; j <= V; j += i) {
            f[j] = 1;
         }
      }
   }
   scanf("%d", &n);
   for (int i = 1; i <= n; i++) {
      scanf("%d%d", &a[i], &b[i]);
   }
   S = n + 1, N = T = n + 2;
   for (int i = 1; i <= n; i++) {
      if (a[i] == 1) continue;
      if (a[i] & 1) {
         flow::add(S, i, b[i]);
      } else {
         flow::add(i, T, b[i]);
      }
   }
   for (int i = 1; i <= n; i++) {
      if (a[i] == 1) continue;
      if (a[i] & 1) {
         for (int j = 1; j <= n; j++) {
            if (j != i && ! f[a[i] + a[j]]) {
               flow::add(i, j, inf);
            }
         }
      }
   }
   ll ans = flow::Dinic();
   for (int i = 1; i <= n; i++) {
      if (a[i] == 1) {
         for (int j = 1; j <= n; j++) {
            if (j != i && ! f[a[j] + 1]) {
               flow::add(i, j, inf);
            }
         }
         flow::add(S, i, b[i]);
         ans += flow::Dinic();
         ans += flow::val[flow::tot - 1] / 2;
      }
   }
   printf("%lld\n", ans);
   return 0;
}
```

---

## 作者：yanghanyv (赞：2)

**这是一个只用最大流的做法。**

## 思路

首先发现一个性质，除了 2 以外的所有质数都是奇数，而奇数 = 奇数 + 偶数，所以大多数情况下只能一奇一偶配对，唯一的特例是 $1+1=2$。

考虑先处理大于 1 的所有数的配对，对于所有 $a_i + a_j$ 为质数的 $(i,j)$ 连边，由于合法的配对一定是奇偶配对，所以会得到一张二分图，容易想到用网络流。

具体建图方式：

- 源点向 $a_i$ 为奇数的 $i$ 连边，流量 $b_i$。

- $a_i$ 为偶数的 $i$ 向汇点连边，流量 $b_i$ 。
- 对所有 $a_i$ 为奇数，$a_j$ 为偶数，且 $a_i+a_j$ 为质数的，从 $i$ 到 $j$ 连边，流量 $+\infin$。

在最大流结束后，考虑加入 $a_i=1$ 进行调整，容易发现最优策略一定是先将 1 尽可能与剩下的数配对，最后将剩下的 1 两两配对。可以用网络流模拟这个过程，在求过一次最大流的残量网络上按上面的建图方式加入和 $a_i=1$ 的 $i$ 相连的边，再求一次最大流即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e2+5;
const int INF=0x3f3f3f3f;
int n,a[N],b[N],cnt1,s,t,dep[N];
ll ans;
int id=1,h[N],cur[N],e[2*N*N],w[2*N*N],ne[2*N*N];
bool check(int x){
	for(int i=2;i*i<=x;i++){
		if(!(x%i)){
			return 0;
		}
	}
	return 1;
}
void add(int a,int b,int c){
	id++;
	ne[id]=h[a];
	h[a]=id;
	e[id]=b;
	w[id]=c;
}
bool bfs(){
	queue<int> que;
	memset(dep,0,sizeof(dep));
	dep[s]=1;
	que.push(s);
	while(que.size()){
		int p=que.front();
		que.pop();
		for(int i=h[p];i;i=ne[i]){
			if(w[i]&&!dep[e[i]]){
				dep[e[i]]=dep[p]+1;
				que.push(e[i]);
			}
		}
	}
	return dep[t];
}
ll dfs(int p,ll flow){
	ll res=0;
	if(p==t){
		res=flow;
	}else{
		for(int i=cur[p];i;i=ne[i]){
			cur[p]=i;
			if(w[i]&&dep[e[i]]==dep[p]+1){
				int v=dfs(e[i],min(flow,1ll*w[i]));
				w[i]-=v;
				w[i^1]+=v;
				res+=v;
				if(!(flow-=v)){
					break;
				}
			}
		}
	}
	return res;
}
ll Dinic(){
	ll res=0;
	while(bfs()){
		memcpy(cur,h,sizeof(h));
		res+=dfs(s,1ll*n*INF);
	}
	return res;
}
int main(){
	scanf("%d",&n);
	s=n+1;
	t=n+2;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
		if(a[i]>1){
			if(a[i]&1){
				add(s,i,b[i]);
				add(i,s,0);
			}else{
				add(i,t,b[i]);
				add(t,i,0); 
			}
		}	
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(check(a[i]+a[j])){
				if(a[i]&1){
					add(i,j,INF);
					add(j,i,0);
				}else{
					add(j,i,INF);
					add(i,j,0);
				}	
			}
		}
	}
	ans=Dinic();
	for(int i=h[s];i;i=ne[i]){
		w[i]=w[i^1]=0;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==1){
			add(s,i,b[i]);
			add(i,s,0);
			int v=Dinic();
			ans+=v+(b[i]-v)/2;
			break;
		}
	}
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：EuphoricStar (赞：1)

## 题意

有 $i$ 种数，第 $i$ 种数是 $a_i$，有 $b_i$ 个。每次可以选择两个数 $x,y$ 满足 $x+y$ 为质数，将它们删除。问最多能删多少次。

## 思路

如果不存在 $1$，那么可以对 $i \ne j$ 且 $a_i + a_j$ 为质数的 $(i,j)$ 之间连边，容易证明这是一张二分图，因为 $a_i$ 和 $a_j$ 必然一奇一偶。那么做一遍二分图带权最大匹配，跑最大流即可。

现在问题就是 $1$ 可以和自己删，我们需要在保证其他数字删的对数最多的前提下，保留的 $1$ 的个数最多，使得最后删的最多。想到最小费用最大流，将 $S \to i$ 且 $a_i = 1$ 的弧的费用设为 $1$，其他弧的费用设为 $0$，最小费用就是最少删的 $1$ 的个数。

## 代码

[code](https://atcoder.jp/contests/abc263/submissions/35860712)

---

## 作者：Take_A_Single_6 (赞：0)

智慧的网络流题目。  
看到题先想的贪心，易证不对。发现 dp 也难以设计。一般这个时候，就可以开始考虑使用神奇的网络流建模。  
观察题目要求，由于质数除了 $2$ 都是奇数，所以除了 $1+1=2$ 以外一定是一奇一偶相加，这样就转化成一个匹配问题了。  
经典套路：  
- 若 $a_i$ 为奇数，由源点连一条权为 $b_i$ 的边。
- 若 $a_i$ 为偶数，向汇点连一条权为 $b_i$ 的边。
- 对于所有 $a[i]+a[j]$ 为质数的 $i,j$ 由奇数向偶数连一条边权为 $\inf$ 的边。

跑一遍 dinic，复杂度远远顶不到上界 $O(n^4)$。  
再单独考虑 $1$ 的情况，显然先和其他数配对再自己配对更优。这时加入源点和 $1$ 的边，再跑一遍 dinic，算一下增量，再加上剩下的 $1$ 的配对就是答案。  
代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 1000005
#define mod 1000000007
#define fir first
#define sec second
#define pr pair<int,int>
#define pb push_back
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX%10+'0');
}
struct edge
{
	int to,val,nxt;
}e[maxn];
int head[maxn],cnt=1,n,s,t,ans,dis[maxn],now[maxn];
queue<int>q;
void add(int x,int y,int z)
{
	e[++cnt].to=y;
	e[cnt].val=z;
	e[cnt].nxt=head[x];
	head[x]=cnt;
	e[++cnt].to=x;
	e[cnt].val=0;
	e[cnt].nxt=head[y];
	head[y]=cnt;
}
bool bfs()
{
	for(int i=1;i<=n+2;i++)dis[i]=inf;
	while(q.size())q.pop();
	q.push(s),dis[s]=0,now[s]=head[s];
	int u;
	while(q.size())
	{
		u=q.front(),q.pop();
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if(e[i].val&&dis[v]==inf)
			{
				dis[v]=dis[u]+1,now[v]=head[v],q.push(v);
				if(v==t)return 1;
			}
		}
	}
	return 0;
}
int dfs(int u,int flow)
{
	if(u==t)return flow;
	int w,res=0;
	for(int i=now[u];i&&flow;i=e[i].nxt)
	{
		int v=e[i].to;
		now[u]=i;
		if(e[i].val&&dis[v]==dis[u]+1)
		{
			w=dfs(v,min(e[i].val,flow));
			if(!w)dis[v]=inf;
			e[i].val-=w,e[i^1].val+=w,res+=w,flow-=w;
		}
	}
	return res;
}//真dinic板子
int a[maxn],b[maxn];
bool check(int x)
{
	for(int i=2;i*i<=x;i++)
		if(x%i==0)return false;
	return true;
}//暴力检查即可
signed main()
{
	int x,y,z;
	n=read(),s=n+1,t=n+2;
	for(int i=1;i<=n;i++)
	{
		a[i]=read(),b[i]=read();
		if(a[i]>1)
		{
			if(a[i]&1)add(s,i,b[i]);
			else add(i,t,b[i]);
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
			if(check(a[i]+a[j]))
			{
				if(i&1)add(i,j,inf);
				else add(j,i,inf);
			}
	}
	while(bfs())ans+=dfs(s,inf);
	for(int i=head[s];i;i=e[i].nxt)e[i].val=e[i^1].val=0;//注意清空
	for(int i=1,j=0;i<=n;i++)
	{
		if(a[i]==1)//考虑1
		{
			add(s,i,b[i]);
			while(bfs())j+=dfs(s,inf);
			write(ans+j+(b[i]-j)/2);
			return 0;
		}
	}
	write(ans);
	return 0;
}
```

---

## 作者：0xyz (赞：0)

我去看了一下英语题解，感觉理解起来有些困难，所以写一下非官方做法。

首先，我们看见这个 $n\le 100$ 的匹配问题就想到网络流，看到 $b_i\le 10^9$ 就知道一定不是费用流。如果没有 $1$，可以直接在可以组成质数的奇数、偶数之间连边，构成一个二分图，创造一个源点和一个汇点，然后直接跑最大流即可。

但是现在有 $1+1=2$，所以我们要换一种建图方式。对于每一个数，我们将它拆成 $2$ 个点，一个入点，一个出点，然后对于所有和为质数的 $x$ 和 $y$，我们从 $x$ 的入点向 $y$ 的出点连流量为无限的边，建立源点向所有入点连流量为其个数限制的边，所有出点向汇点连流量为其个数限制的边，跑出最大流除以 $2$ 即可。

用 Dinic 和试除法，时间复杂度 $O(n^4+n^2\sqrt {a_i})$。

[AC 代码](https://atcoder.jp/contests/abc263/submissions/43528612)。

当然也可以用 HLPP 和 Miller_Rabin，时间复杂度 $O(n^3+n^2\log a_i)$。

---

## 作者：happybob (赞：0)

有趣的网络流。

首先，除了 $2$，所有质数都是奇数，所以只能被表示成两个奇偶性不同的数的和。所以我们先抛开 $2$ 不谈。

如果抛开 $2$，意味着原序列没有 $1$。若是这样，我们可以直接最大流解决，具体是这样：

- 考虑对于 $a_i+a_j$ 为质数且 $a_i$ 是奇数的数对 $(i,j)$，连边 $i \rightarrow j$，容量为 $+\infty$。

- 对于 $a_i$ 是奇数的 $i$，连 $S \rightarrow i$，容量为 $b_i$，表示只有 $i$ 个 $a_i$。

- 对于 $a_i$ 是偶数，连 $i \rightarrow T$，容量为 $b_i$，表示只有 $i$ 个 $a_i$。

- 求 $S \rightarrow T$ 最大流 $p$，即为答案。

但是我们发现，$1+1=2$，并不是奇数和偶数之和。这是本题的难点。

我们对于上述方案，求出最大流后，令 $S \rightarrow 1$ 的容量为 $c$，实际流量为 $f$。那么我们可以用 $1+1=2$ 得到质数 $\lfloor \frac{c-f}{2} \rfloor$ 个。为了最大化 $p + \lfloor \frac{c-f}{2} \rfloor$，我们需要在最大化 $p$ 的前提下最小化 $f$。

若我们没有最大化 $p$，那么相当于至少少获得了一个质数，即少用了两个数，而这两个数不可能都是 $1$，所以 $p + \lfloor \frac{c-f}{2} \rfloor$ 不会更优。所以我们应该先最大化 $p$。

于是转化成费用流模型，$S \rightarrow 1$ 的边费用为 $1$，其余费用为 $0$，最小费用最大流即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 5e4 + 5, M = 2e7 + 5;

int e[N], h[N], c[N], ne[N], idx, a[N], b[N], n, cs[N];
int prime[M], cnt, S = 0, T, ret;
bool np[M], isin[N];

void Init()
{
	np[1] = 1;
	for (int i = 2; i < M; i++)
	{
		if (!np[i])
		{
			prime[++cnt] = i;
		}
		for (int j = 1; j <= cnt && 1LL * i * prime[j] < M; j++)
		{
			np[1LL * i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

inline void add(int u, int v, int w, int cc)
{
	e[idx] = v, c[idx] = w, ne[idx] = h[u], cs[idx] = cc, h[u] = idx++;
	e[idx] = u, c[idx] = 0, ne[idx] = h[v], cs[idx] = -cc, h[v] = idx++;
}

int dis[N], cur[N];

inline bool bfs()
{
	for (int i = 0; i <= T; i++) dis[i] = 1e18, cur[i] = -1;
	queue<int> q;
	q.push(S);
	dis[S] = 0, cur[S] = h[S];
	while (q.size())
	{
		int u = q.front();
		q.pop();
		isin[u] = 0;
		for (int i = h[u]; ~i; i = ne[i])
		{
			int j = e[i];
			if (c[i] > 0 && dis[j] > dis[u] + cs[i])
			{
				dis[j] = dis[u] + cs[i];
				cur[j] = h[j];
				if (!isin[j]) q.push(j), isin[j] = 1;
			} 
		} 
	}
	return (dis[T] != 1e18);
}

inline int dfs(int u, int lim)
{
	if (u == T) return lim;
	isin[u] = 1;
	int res = 0;
	for (int i = cur[u]; ~i && res < lim; i = ne[i])
	{
		cur[u] = i;
		int j = e[i];
		if (!isin[j] && dis[j] == dis[u] + cs[i] && c[i] > 0)
		{
			int p = dfs(j, min(lim - res, c[i]));
			ret += p * cs[i];
			res += p;
			c[i] -= p;
			c[i ^ 1] += p;
		}
	}
	isin[u] = 0;
	return res;
}

inline int dinic()
{
	int sum = 0, p;
	while (bfs())
	{
		while (p = dfs(S, INT_MAX)) sum += p;
	}
	return sum;
} 

signed main()
{
	memset(h, -1, sizeof h);
	Init();
	scanf("%lld", &n);
	int p = 0;
	for (int i = 1; i <= n; i++) 
	{
		scanf("%lld%lld", &a[i], &b[i]);
		if (a[i] == 1) p = b[i];
	}
	T = n + 1;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] % 2 == 0) continue;
		for (int j = 1; j <= n; j++)
		{
			if (i != j && !np[a[i] + a[j]])
			{
				add(i, j, INT_MAX, 0);
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (a[i] & 1) add(S, i, b[i], (a[i] == 1));
		else add(i, T, b[i], 0);
	}
	int res = dinic();
	printf("%lld\n", res + (p - ret) / 2);
	return 0;
}
```


---

## 作者：allenchoi (赞：0)

### 题意：  
有 $n$ 种整数 $a_i$ ，第 $i$ 种有 $b_i$ 个。进行若干次操作，每次在这些数中取出两个，若它们的和为质数，分数加一，操作后把这两个数移去，求最大分数。  
### 科技：  
三分，网络流  
### 思路：  
先考虑 $a_i>1$ 。那么每次加起来为质数的两个数一定是一奇一偶。如果我们在和为质数的两个数间建边，那么显然会构成一张二分图。我们在源点与奇数 $a_i$ 间建一条流量为 $b_i$ 的边，在偶数 $a_j$ 与汇点建一条流量为 $b_j$ 的边，前面的边流量赋为无穷大，跑网络流即可。  
如果有 $a_i=1$ 呢？  
会有特殊情况 $1+1=2$ ，但是我们可以三分 $1$ 用于与自己相加的数量。  
为啥它满足三分性质捏？感性理解一下：  
设在最优解的情况下，有 $a$ 个 $1$ 与别的数相加得质数，我们用了 $b$ 个 $1$。  
我们只需用一个 $1$ 与其他数相加就可以对答案加一，而如果要 $1+1=2$ 的话需要两个。  
我们肯定要尽量用第一种方案，因此在 $b\le a$ 的情况下 $b$ 越大越好，即与自己相加的 $1$ 越少越好；  
然而，如果 $b>a$ ，剩下的 $b-a$ 个 $1$ 就没用了。为了答案最大，我们肯定要~~榨干~~充分利用每个数，所以在 $b\ge a$ 的情况下， $b$ 越小越好，即与自己相加的 $1$ 越多越好。  
综上所述，随着与自己相加的 $1$ 的数量的上升，分数会先上升后下降，因此满足三分性质。   
### 代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,s,t,p,u,v,l,r,mid,a[110],b[110],dep[110];
long long mp[110][110],g[110][110];
long long maxn;
queue <int> q;
bool check(int x)
{
	for(int i = 2;i * i <= x;i++) if(x % i == 0) return false;
	return true;
}
bool bfs()
{
	memset(dep,0,sizeof(dep));
	dep[s] = 1;
	q.push(s);
	int i;
	while(!q.empty())
	{
		i = q.front(),q.pop();
		for(int j = s;j <= t;j++)
		{
			if(g[i][j] && !dep[j])
			{
				q.push(j);
				dep[j] = dep[i] + 1;
			}
		}
	}
	return dep[t];
}
long long dfs(int x,long long y)
{
	if(x == t) return y;
	long long ret = 0,tmp;
	for(int i = s;i <= t;i++)
		if(g[x][i] && dep[i] == dep[x] + 1)
		{
			tmp = dfs(i,min(y,g[x][i]));
			g[x][i] -= tmp;
			g[i][x] += tmp;
			y -= tmp;
			ret += tmp;
		}
	return ret;
}
long long f(int x)
{
	for(int i = s;i <= t;i++) for(int j = s;j <= t;j++) g[i][j] = mp[i][j];
	g[s][p] -= 2 * x;
	long long ret = 0;
	while(bfs()) ret += dfs(s,1e17);
	return ret + x;
}
int main()
{
	scanf("%d",&n);
	s = 0,t = n + 1;
	for(int i = 1;i <= n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		if(a[i] == 1) p = i;
		if(a[i] % 2 == 1) mp[s][i] = b[i];
		else mp[i][t] = b[i];
		for(int j = 1;j < i;j++)
			if(check(a[i] + a[j]))
				if(a[i] % 2 == 1) mp[i][j] = 1e17;
				else mp[j][i] = 1e17;
	}
	r = b[p] / 2;
	while(r - l > 5)
	{
		mid = (r - l) / 3;
		if(f(l + mid) > f(r - mid)) r -= mid;
		else l += mid;
	}
	maxn = -1e17;
	for(int i = l;i <= r;i++) maxn = max(maxn,f(i));
	printf("%lld\n",maxn);
	return 0;
}
```

---

