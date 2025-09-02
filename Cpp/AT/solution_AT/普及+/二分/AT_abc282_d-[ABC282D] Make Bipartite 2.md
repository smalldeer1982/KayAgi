# [ABC282D] Make Bipartite 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc282/tasks/abc282_d

$ N $ 個の頂点と $ M $ 本の辺からなる単純な（すなわち、自己ループも多重辺も含まない）無向グラフ $ G $ が与えられます。 $ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結びます。

$ 1\ \leq\ u\ \lt\ v\ \leq\ N $ を満たす整数の組 $ (u,\ v) $ であって、下記の $ 2 $ つの条件をともに満たすものの個数を出力してください。

- グラフ $ G $ において、頂点 $ u $ と頂点 $ v $ を結ぶ辺は存在しない。
- グラフ $ G $ に、頂点 $ u $ と頂点 $ v $ を結ぶ辺を追加して得られるグラフは、二部グラフである。
 
  二部グラフとは？無向グラフが**二部グラフ**であるとは、下記の条件を満たすように各頂点を黒または白のどちらかの色で塗ることができることを言います。

- 同じ色に塗られた頂点どうしを結ぶ辺は存在しない。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ \min\ \lbrace\ 2\ \times\ 10^5,\ N(N-1)/2\ \rbrace $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- グラフ $ G $ は単純
- 入力はすべて整数
 
### Sample Explanation 1

問題文中の条件を満たす整数の組 $ (u,\ v) $ は、$ (1,\ 4) $ と $ (1,\ 5) $ の $ 2 $ つです。よって、$ 2 $ を出力します。 他の組については、例えば、$ (1,\ 3) $ はグラフ $ G $ において頂点 $ 1 $ と頂点 $ 3 $ を結ぶ辺が存在することから、 $ (4,\ 5) $ はグラフ $ G $ に頂点 $ 4 $ と頂点 $ 5 $ を結ぶ辺を追加して得られるグラフが二部グラフではないことから、 それぞれ問題文中の条件を満たしません。

### Sample Explanation 2

与えられるグラフが二部グラフであったり連結であるとは限らないことに注意してください。

## 样例 #1

### 输入

```
5 4
4 2
3 1
5 2
3 2```

### 输出

```
2```

## 样例 #2

### 输入

```
4 3
3 1
3 2
1 2```

### 输出

```
0```

## 样例 #3

### 输入

```
9 11
4 9
9 1
8 2
8 3
9 2
8 4
6 7
4 6
7 5
4 5
7 8```

### 输出

```
9```

# 题解

## 作者：Pengzt (赞：9)

[ABC282D](https://www.luogu.com.cn/problem/AT_abc282_d)

如果这个图不是二分图，输出 $0$ 即可。

正难则反，可以用总数减去不能相互连边的数量。

如果不考虑二分图的限制，显然答案应该是 $n\times(n-1)$。

如果这是一个二分图，那么它的每一个连通块都将是二分图。

那么这个连通块的左部点间不能互相连边，右部点同理。

设该连通块左部点有 $x$ 个，右部点有 $y$ 个，那么答案就应减去 $x\times(x-1)+y\times(y-1)$。

对每一个连通块都减一遍即可。

[评测记录](https://www.luogu.com.cn/record/97992931)

---

## 作者：ran_qwq (赞：6)

## 题目大意

给你一个无向图，你要添加一条边，求有多少种方法之后的图是**二分图**。

## 题目解法

首先，这题暴力 $O(n^3)$ 肯定是过不了的。

我们可以给图进行黑白染色，使得黑点旁边是白点，白点旁边是黑点。如果做不到，那这个图就不是二分图，再加边肯定也不是二分图，特判这种情况输出 $0$。

- 对于在一个连通块内，如果这条边不存在且连接这条边的两个点颜色不同（如果颜色相同就不是二分图了），则可以染色。假如一个连通块黑点个数为 $cnt1$，白点个数为 $cnt2$，则可染色边数为 $cnt1\times cnt2$。

- 对于不同连通块之间，因为一个连通块的黑白可以倒转，所以如果这条边的两个点颜色相同，可以将对方的连通块颜色倒转，两个点黑白就不同了。所以两个不同连通块的点肯定可以连边。换句话说，一个连通块大小若为 $siz$，则这个连通块对答案的贡献为 $siz(n-siz)$。当然，每条边算了两次，所以要除以 $2$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+10,INF=1e9;
//省略快读快写
int n,m,cnt1,cnt2,ans,sum,col[N];
int id,to[N],ne[N],head[N];
void add(int x,int y)
{
	to[++id]=y,ne[id]=head[x],head[x]=id;
}
void dfs(int u,int fa)
{
	if(col[u])
		cnt1++;
	else
		cnt2++;
	for(int i=head[u];i;i=ne[i])
	{
		int v=to[i];
		if(col[v]==-1)
			col[v]=col[u]^1,dfs(v,u);
		else if(col[v]==col[u])
			puts("0"),exit(0);
	}
}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		add(x,y),add(y,x);
	}
	for(int i=1;i<=n;i++)
		col[i]=-1;
	for(int i=1;i<=n;i++)
		if(col[i]==-1)
		{
			col[i]=1,cnt1=cnt2=0,dfs(i,0);
			ans+=cnt1*cnt2,sum+=(cnt1+cnt2)*(n-cnt1-cnt2);
		}
	write(ans-m+sum/2,"\n");
}

```


---

## 作者：李柯欣 (赞：5)

题目传送门：[AT_abc282_d](https://www.luogu.com.cn/problem/AT_abc282_d)。

[更好的阅读感受](https://www.luogu.com.cn/blog/likexin/solution-at-abc282-d)？

### 题目大意：

给定一个 $N$ 个点，$M$ 条边的无向图，求问有多少对还未经连接的点对满足在连接它们后，该图为一个二分图？注意这里边 $(u,v)$ 和边 $(v,u)$ 是同一对点对。

数据保证没有自环与重边。

什么是二分图？

>节点集合由两个集合组成，且两个集合内部没有边的图，称为二分图。
>
>摘自 [oi wiki](https://oi.wiki/)。

### 思路：

呀呀呀，什么是二分图哇，好神奇！这道题好难的样子！

先不要慌，知道二分图是什么后就简单了。

虽然题目说的是二分图，但是仔细分析一下，其实和二分图没有什么太大的关系。

好好想一想就会发现对于一个点对 $(u,v)$ 来讲，如果连接边 $(u,v)$ 后该图为二分图，那么去掉这条边后仍为二分图。

换句话说，要使连接 $(u,v)$ 后该图是一个二分图，该图本身也需要是一个二分图。

如果原图是一个二分图，那么满足题目要求的边只有以下几种情况：

1. 两点原本属于不同的集合内，可以连边。（题目未保证图联通，这里是个坑）

2. 两点在同一个集合内，在二分图内属不同的集合，且原本未连边。

如果原图本身就不是个二分图，就不可能存在点对，直接输出 $0$ 结束。

### 代码：

其实代码不算很长。

首先建图。

由于不保证联通，就需要对每个点都跑一遍，判断该点所在的集合是不是二分图，一但发现不是就输出 $0$，结束。

同一个集合的点不需要重复遍历。

对于第一种点对，开一个数字 $sum$ 来存储之前共有多少个点，遍历一个集合后 $ans$ 加上集合的点数乘 $sum$ 就是第一种边的数量。

对于第二种点对相当于一个二分图集合中两个不同集合的点两两连边后减去已经连上的边。

把这两种边加起来就是答案。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<vector>
#include<bitset>
#include<string>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<deque>
#include<queue>
#include<stack>
#include<list>
#include<map>
#include<set>
#define int unsigned long long
using namespace std;
vector<int> g[200010];
int zy[10];
int vis[200010];
int jg=0;//是不是二分图。
int kk=0;
void dfs(int x,int zoy){//二分图的判定。
	vis[x]=zoy+1;
	zy[vis[x]]++;
	kk+=g[x].size();
	for(int i=0;i<g[x].size();i++){
		if(vis[g[x][i]]==vis[x]){
			jg=1;//不是二分图。
			return;
		} 
		if(vis[g[x][i]]) continue;
		dfs(g[x][i],(zoy^1));
	}
}
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		g[x].push_back(y);
		g[y].push_back(x);
	}//读入，建图。
	int tot=0,qqq=0;
	for(int ii=1;ii<=n;ii++){
		if(vis[ii]) continue;
		kk=0;//该集合中已经连的边。
		dfs(ii,1);//判断是不是二分图。
		kk/=2;//
	//	cout<<jg<<endl;
		if(jg){//不是二分图直接结束。
			cout<<0;
			return 0;
		}
		int ans=0,zuo=0,you=0;
		for(int i=1;i<(zy[1]+zy[2]);i++){
			ans+=i;
		}
		for(int i=1;i<zy[1];i++){
			zuo+=i;
		}
		for(int i=1;i<zy[2];i++){
			you+=i;
		}
		tot+=(ans-zuo-you-kk)+qqq*(zy[1]+zy[2]);//(ans-zuo-tou-kk) 是第二种点对，qqq 表示之前的点的数量，qqq*(zy[1]+zy[2]) 是第一种点对。
		qqq+=(zy[1]+zy[2]);
		zy[1]=zy[2]=0;
	}
	cout<<tot;
	return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/98040846)。


---

## 作者：Phartial (赞：2)

首先如果原图不为二分图，答案显然为 $0$，可以把这一档判掉。

考虑每个连通块，它有两种贡献：

1. 自身的贡献：即为左部点和右部点之间还可以连的边，可以简单计算。
2. 与别人的贡献：显然一个连通块的点可以和其他连通块的任意一个点连边，可以在找连通块的时候维护一下之前找出来的连通块的大小和。

然后就做完了了。代码极其好写，因为完全没有细节。

```cpp
#include <iostream>
#include <vector>

using namespace std;
using LL = long long;

const int kN = 2e5 + 1;

int n, m, c[kN];
LL s, ans;
vector<int> e[kN], l[2];
bool v[kN];

void D(int x, int _c) {
  if (c[x]) {
    if (c[x] != _c) {  // 如果不是二分图
      cout << "0";
      exit(0);
    }
    return;
  }
  l[(c[x] = _c) - 1].push_back(x);  // 记录是左部点还是右部点
  for (int i : e[x]) {
    D(i, _c ^ 3);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    e[x].push_back(y), e[y].push_back(x);
  }
  for (int i = 1; i <= n; ++i) {
    if (!c[i]) {
      l[0].clear(), l[1].clear();
      D(i, 1);  // 搜出连通块
      for (int j : l[1]) {
        v[j] = 1;
      }
      ans += 1LL * l[0].size() * l[1].size();  // 左部点和右部点的连线
      for (int j : l[0]) {
        for (int k : e[j]) {
          if (v[k]) {  // 把所有原来就有的边删掉
            --ans;
          }
        }
      }
      for (int j : l[1]) {
        v[j] = 0;
      }
      int _l = l[0].size() + l[1].size();
      ans += _l * s, s += _l;  // 与其他连通块的贡献
    }
  }
  cout << ans;
  return 0;
}
```

---

## 作者：fengxiaoyi (赞：1)

### 思路

**核心算法：二分图染色**

如果不知道二分图染色的话，自己百度去。

首先，定义一个计数器 $sum$，表示有多少组颜色相同的点对无法用边连起来。

#### 注意，这个图不一定连通。

所以就遍历连通块进行二分图染色，如果不是二分图，直接输出 $0$，收工。

#### 为什么？

![](https://cdn.luogu.com.cn/upload/image_hosting/nl6vpxrm.png)

如图，可以发现，无法只添加一个边使得图为二分图。

定义 $B$ 为这个连通块黑点的个数，$W$ 为这个连通块黑点的个数。

那，如果是二分图，将这个连通块内的黑点的对数 $B\times(B-1)\div2$ 和白点的对数 $W\times(W-1)\div2$ 累加到 $sum$ 里边。 

最后，输出 这个图的点对总量（$N\times(N-1)\div2$）$-$ $sum$ $-$ 边数 $M$（有 $M$ 个点对已经相连）。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,c[200010],num,k[3];
long long g;
int f[400010],nxt[400010],to[400010];
bool v;
void Color(int u,int fa,int now){
	if(c[u]&&c[u]!=now){
		v=1;
		return;
	}
	else if(c[u]) return;
	else{
		c[u]=now;
		k[now]++;
	}
	for(int i=f[u];i;i=nxt[i]){
		if(to[i]==fa) continue;
		if(now==1)
			Color(to[i],u,2);
		else if(now==2)
			Color(to[i],u,1);
	}
}
void add(int a,int b){
	to[++num]=b;
	nxt[num]=f[a];
	f[a]=num;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	for(int i=1;i<=n;i++){
		if(!c[i]){
			memset(k,0,sizeof(k));
			v=0;
			Color(i,0,1);
			if(v) return !printf("0\n");
			g+=1ll*k[1]*(k[1]-1)/2+1ll*k[2]*(k[2]-1)/2;
		}
	}
	return !printf("%lld",1ll*n*(n-1)/2-g-m);
}
```


---

## 作者：junxis (赞：1)

# Perface
并查集好题。
# Statement
给定一个图 $G=(V,E)$，求出有多少 $e=(u,v),u<v,e \not \in E$ 使得 $G'=(V,E \cup e)$ 是一个二分图。
# Analysis

记 $f_u$ 为 $u$ 所属的集合。

熟知利用扩域并查集判二分图的方法：

$\forall (u,v)\in E$：$\mathtt{unite}(u,v'),\mathtt{unite}(u',v)$。

然后判断 $\bigwedge\limits_{u\in V}[f_u \not = f_u']$。

显而易见地，增加一条边绝无可能让原来同属一个集合的点分开，所以 $G$ 必须是一个二分图，答案才不为 $0$。

一条边 $(u,v)$ 被添加，则 $\mathtt{unite}(u,v'),\mathtt{unite}(u',v)$。

所以添加后 $f_u \not = f_{u'} \wedge f_v \not = f_{v'}$ 的充要条件为 $f_u \not = f_v \wedge f_{u'} \not = f_{v'}$（自行验证即可得证）。

答案即为：

$$\frac{1}{2}\sum\limits_{(u,v)\not\in E}[f_u \not = f_v \wedge f_{u'} \not = f_{v'}]$$

$$=\frac{1}{2}\sum\limits_{u\in V}(\sum\limits_{v\in V}[f_u \not = f_v \wedge f_{u'} \not = f_{v'}]-\deg_u)$$

$$=\frac{1}{2}\sum\limits_{u\in V}[\operatorname{card}(V)-(\sum\limits_{v\in V}[f_u = f_v]+\sum\limits_{v\in V}[f_{u'} = f_{v'}]-\sum\limits_{v\in V}[f_u=f_v \wedge f_{u'} = f_{v'}])-\deg_u]$$

并查集的时候维护一个当前集合里的原点个数，虚点个数，用 $\mathtt{std::map}$ 处理一下括号里的第三个 $\sum$ 即可。

时间复杂度 $\mathcal{O}(n\log n)$。

# CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b)-1; i>=(a); i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int, int> PII;
typedef double db;
mt19937 mrand(random_device{}());
const ll mod=1000000007;
int rnd(int x) {return mrand() % x;}
ll powmod(ll b, ll e, ll md=mod) {ll a=1; b %= md; assert(e>=0); for (;e;e>>=1, b=b*b%md) if(e&1) {a=a*b%md;} return a;}
ll gcd(ll a, ll b) {return b?gcd(b,a%b):a;}
// head

const int N = 401000;
int n, m, f[N], totreal[N], totimag[N], deg[N];

int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

void unite(int x, int y) {
	int u = find(x), v = find(y);
	if (u != v) {
		f[u] = v;
		totreal[v] += totreal[u];
		totimag[v] += totimag[u];
	}
}

int main() {
	scanf("%d%d", &n, &m);
	
	rep(i,1,2*n+1) f[i] = i, totreal[i] = bool(i <= n), totimag[i] = bool(i > n);
	
	rep(i,0,m) {
		int u, v;
		scanf("%d%d", &u, &v);
		++deg[u]; ++deg[v];
		unite(u, v + n); unite(u + n, v);
	}

	bool ok = true;
	rep(i,1,n+1) ok &= (find(i) != find(i + n));
	if (!ok) return puts("0"), 0;

	map<PII, int> cnt;
	rep(i,1,n+1) cnt[{find(i), find(i + n)}] += 1;

	ll ans = 0;
	rep(i,1,n+1) {
		ans += n - (totreal[find(i)] + totimag[find(i + n)] - cnt[{find(i), find(i + n)}]) - deg[i];
	}
	printf("%lld\n", ans / 2);
}
```

---

