# [IOI 2007] training 训练路径 

## 题目描述

马克(Mirko)和斯拉夫克(Slavko)正在为克罗地亚举办的每年一次的双人骑车马拉松赛而紧张训练。他们需要选择一条训练路径。

他们国家有$N$个城市和$M$条道路。每条道路连接两个城市。这些道路中恰好有$N-1$条是铺设好的道路，其余道路是未经铺设的土路。幸运的是，每两个城市之间都存在一条由铺设好的道路组成的通路。换句话说，这$N$个城市和$N-1$条铺设好的道路构成一个树状结构。

此外，每个城市最多是$10$条道路的端点。

一条训练路径由某个城市开始，途经一些道路后在原来起始的城市结束。因为马克和斯拉夫克喜欢去看新城市，所以他们制定了一条规则：绝不中途穿越已经去过的城市，并且绝不在相同的道路上骑行两次（不管方向是否相同）。训练路径可以从任何一个城市开始，并且不需要访问所有城市。

显然，坐在后座的骑行者更为轻松，因为坐在前面的可以为他挡风。为此，马克和斯拉夫克在每个城市都要调换位置。为了保证他们的训练强度相同，他们要选择一条具有偶数条道路的路径。

马克和斯拉夫克的竞争者决定在某些未经铺设的土路上设置路障，使得他们两人不可能找到满足上述要求的训练路径。已知在每条土路上设置路障都有一个费用值（一个正整数），并且竞争者不能在铺设好的道路上设置路障。

给定城市和道路网的描述，写一个程序计算出为了使得满足上述要求的训练路径不存在，而需要的设置路障的最小总费用。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/pic/20676.png )

第一个样例中道路与城市的布置。已被铺设好的道路以粗边显示。

![](https://cdn.luogu.com.cn/upload/pic/20677.png )

共有5种可能的路线。如果边1-3、3-5和2-5被封锁，则两人将会不能使用5种路线的任何一种。封锁这三条边的代价是5。

只封锁两条边，像是2-4和2-5，也是可以的，但这样会导致较高的代价，6。

在前30分的测试数据中，铺设好的道路会形成一条链。

## 样例 #1

### 输入

```
5 8 
2 1 0 
3 2 0 
4 3 0 
5 4 0 
1 3 2 
3 5 2 
2 4 5 
2 5 1 ```

### 输出

```
5```

## 样例 #2

### 输入

```
9 14 
1 2 0 
1 3 0 
2 3 14 
2 6 15 
3 4 0 
3 5 0 
3 6 12 
3 7 13 
4 6 10 
5 6 0 
5 7 0 
5 8 0 
6 9 11 
8 9 0 ```

### 输出

```
48```

# 题解

## 作者：XG_Zepto (赞：23)

[原题地址](http://ioi2007.hsin.hr/tasks/day2/training.pdf)

[官方题解](http://ioi2007.hsin.hr/tasks/solutions.pdf)

[我的博客](https://zepto.page/post/ioi-2007-training)


### 题意概述

给定 $n$ 个点 $m$ 条边的无向图，你需要删掉一些边，使得此图没有长度为偶数的简单环。 

删掉第 $i$ 条边有 $C_i$ 的花费，有些边又是不能删的。不能删的边形成图的一棵生成树。 

$n\leq 1000,m \leq 5000$，点的度数不超过 10。

### 思路

对于所有非树边，如果非树边所连接的两个点在树上的距离为奇数，那么会构成一个偶环，删去这些边。

考虑两个仅含有一条非树边的奇环，如果他们在树上的部分有交，那么把两个环合并在一起再去掉那些重复的部分剩下的就一定是一个偶环，所以说我们需要留下一张图，使得没有一条边同时属于两个简单环，也就是一个仙人掌（此处没有考虑在最初就被我们删掉的非树边）。容易证明满足上述条件的方案一定合法。

如果让每条非树边覆盖他连接两点树上的路径上的所有边，那么树上的每一条边最多只能被覆盖一次，再将必须删除的最小边权改为总边权-能留下的最大边权。

因为每个点的度数不超过 10，我们就可以状态压缩。

定义 $f_{(i,S)}$ 为以 $i$ 为根的子树中，不考虑儿子集合 $S$ 的最大边权。

对于一条左右端点$u, v$ 的 $LCA$ 为 $i$ 的非树边，

- 如果不选择，此时的 $f_{(i,S)}=\sum_{son\notin S} f_{(son,0)}$；

- 如果选择这条边，这条边的贡献 $val$ 分为两个部分：

1. $f_{(u,0)} + f_{(v,0)}$

2. 对于到 $LCA$ 路径上的的每个点 $p$。设对于 $p$，不包含 $u$ 或 $v$ 的儿子集合为 $K$，贡献为 $\sum f_{(p,K)}$

现在我们可以枚举点 $i$ 的子集 $S$，令子树包含 $u,v$ 的儿子分别为 $x,y$。对于 $\{ S| x\notin S, y\notin S\}$

$$f_{(i,S)}=\max f_{(i,S|x|y)}+val$$

最终的答案为总边权减去 $f_{(root,0)}$。

时间复杂度 $\Theta (m2^{10}+mn)$。

### 代码

```cpp
#include <bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define pb push_back
#define maxn 1010
#define maxm 5010
struct Edge{
	int to,next;
	Edge(int a=0,int b=0){
		to=a,next=b;
	}
}l[maxn<<1];
struct Brid{
	int from,to,val;
	Brid(int a=0,int b=0,int c=0){
		from=a,to=b,val=c;
	}
}H[maxm];
int head[maxn],p[maxn][12],cnt,n,m;
int dep[maxn],f[maxn][maxn<<2];
int id[maxn],rid[maxn],tot,sum;
std::vector<int>B[maxn];
//H 存储题目给定的所有非树边
//B 存储不构成偶环的边，将它挂在相应的 LCA 处。
void Add(int a=0,int b=0){
	l[++cnt]=Edge(b,head[a]);
	head[a]=cnt;
}
void Dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	p[u][0]=fa;
	for (register int i=1;i<12;i++)
	p[u][i]=p[p[u][i-1]][i-1];
	for (register int i=head[u];i;i=l[i].next){
		int v=l[i].to;if (v!=fa) Dfs(v,u);
	}
}
int Lca(int a,int b){
	if (dep[b]<dep[a]) std::swap(a,b);
	for (register int i=11;~i;i--)
		if (dep[p[b][i]]>=dep[a]) b=p[b][i];
	if (a==b) return a;
	for (register int i=11;~i;i--)
		if (p[a][i]!=p[b][i])
		a=p[a][i],b=p[b][i];
	return p[a][0];
}
#define fa(i) (p[i][0])
void Solve(int u){
	int son=0;
	for (register int i=head[u];i;i=l[i].next){
		int v=l[i].to;
		if (v==fa(u)) continue;
		Solve(v);
	}
	for (register int i=head[u];i;i=l[i].next){
		int v=l[i].to;
		if (v==fa(u)) continue;
		id[son]=v,rid[v]=1<<son,son++;//id 是儿子编号对应的点，rid 是每个点在父亲处对应的二进制位置
	}
	for (register int S=0,tem=0;S<1<<son;++S,tem=0){
		for (register int i=0;i<son;i++)
			if (!(S>>i&1))
			tem+=f[id[i]][0];
		f[u][S]=tem;
	}//不选择挂在 u 上的非树边。
	for (register int k=B[u].size()-1;~k;--k){
		int i=B[u][k],tem=H[i].val;
		if (H[i].from!=u)
		tem+=f[H[i].from][0];
		if (H[i].to!=u)
		tem+=f[H[i].to][0];
		int a=0,b=0;
		if (H[i].from!=u)
			for (a=H[i].from;fa(a)!=u;a=fa(a))
			tem+=f[fa(a)][rid[a]];
		if (H[i].to!=u)
			for (b=H[i].to;fa(b)!=u;b=fa(b))
			tem+=f[fa(b)][rid[b]];
		for (register int S=0;S<1<<son;++S)
			if ((S&rid[a])==0&&(S&rid[b])==0)
			f[u][S]=max(f[u][S],f[u][S|rid[a]|rid[b]]+tem);
	}
}
#undef fa
int main(){
	scanf("%d%d",&n,&m);
	for (register int i=1,a,b,c;i<=m;++i){
		scanf("%d%d%d",&a,&b,&c);
		if (!c) Add(a,b),Add(b,a);
		else H[++tot]=Brid(a,b,c),sum+=c;
	}
	Dfs(1,0);
	for (register int i=1;i<=tot;++i){
		int t=Lca(H[i].from,H[i].to);
		if (!((dep[H[i].from]+dep[H[i].to]-2*dep[t])&1))
		B[t].pb(i);
	}
	Solve(1);
	printf("%d",sum-f[1][0]);
	return 0;
}
```

---

## 作者：FOX_konata (赞：13)

## P4649 [IOI2007] training 训练路径
#### 题意：

[原题地址](https://www.luogu.com.cn/problem/P4649)

给你一棵 $n$ 个节点的树，上面还有 $m-(n-1)$ 条非树边，每条非树边有一个代价 $c_i$，要求你删掉若干条非树边使得之后的这棵树满足不存在任意一个长度为偶数的简单环。保证每个节点度数 $\le 10$。

#### trick：如果树上不存在偶环，那么树上任意两个奇环之间没有公共边。

- 考虑到假如树上两个奇环之间有公共边，设这两个奇环的长度是 $x,y$，公共部分长 $k$，那么 $x+y-2k$ 一定是偶数，换言之诞生了一个偶环，假设不成立。
- ![](https://cdn.luogu.com.cn/upload/image_hosting/hhjyom4a.png)

#### 30pts 链：

- 知道了这个 trick 后我们可以做这道题了。
  
- 首先删边对于判断是否存在满足条件的环对我们来说是一个困难的问题，但是加边就相对简单一些。
  
- 因此我们考虑要加入哪些非树边，使得加入的边权和最大，最后再拿总边权减去选择加入的非树边即可。
  
- 对于链的部分分，每条非树边连接的两点构成一个区间，环两两无交就是不存在一个点被两个区间覆盖；不能出现偶环只需要在加入非树边 $(u,v)$ 时确保链上 $dist(u,v)$ 是偶数即可。
  
- 我们可以直接 dp，设 $dp_i$ 表示进行了前 $i$ 个区间的选择，第 $i$ 个位置已被覆盖的最大边权和。转移：
  
- $$
  \begin{align}
  dp_i + w(u,v) & \to dp_v &\text{if $i \leq u$}
  \end{align}
  $$
- 直接暴力选边就行，复杂度 $O(nm)$
  

#### 100pts 树：

- 树比链困难的地方在于树要考虑兄弟节点。
  
- 我们发现我们还有节点度数 $\leq 10$ 的限制没有用上，我们可以延续链的思路，直接把 $10$ 个兄弟看成同时操作 $10$ 条链来解决，那么我们可以直接在 dp 里进行状压。
  
- 设 $dp_{u,S}$ 表示以 $u$ 为根的子树中，不考虑 $S$ 集合中的儿子的子树的最大和。
  
- 至于这里为什么使用“不考虑”，之后会再提到。
  
- 对于每个非树边显然要在两点的 lca 处进行 dp 考虑。这里要分两种情况：
  
  - 不选择 $(u,v)$ 这条非树边：那么有 $dp_{lca,S} = \sum_{v \notin S} dp_{v,0}$
    
  - 选择 $(u,v)$ 这条非树边：
    
    - 这时候 $u \to v \to lca \to u$ 成为一个奇环。
      
    - 那么我们要加上排除掉这个奇环里所有点外其他节点产生的贡献。
      
    - 设 $u,v$ 两点分别在 $lca$ 第 $x,y$ 儿子子树内。可以得到
      
    - $$
      dp_{lca,S} = dp_{lca,S+x+y} + dp_{u,0} + dp_{v,0} + \sum_{t \in path(u,v)}^{fa(t) \neq lca, t \neq lca} dp_{fa(t),t} + w(u,v)
      $$
    - ![](https://cdn.luogu.com.cn/upload/image_hosting/2gz9de88.png)
      
    - 其中第一部分是如图红色部分，表示除了这两个儿子子树外其他儿子产生的贡献。
      
    - 第二三部分为图中绿色部分，表示这个奇环的底部 $u,v$ 两点两颗子树产生的贡献
      
    - 第四部分为图中橙色部分，表示奇环从 $u \to lca \to v$ 的路径上分叉出去的部分产生贡献
      
    - 第五部分就是加入非树边的贡献。
      
- 可以注意到第四部分我们只需要去除掉 $t$ 的一个儿子，这就是为什么我们使用“不考虑”定义 dp 式子。实际上考虑也是可以做的，只不过要麻烦一点。
  
- 第四个式子暴力是没法算的，会直接 TLE 掉。但是我们可以把它拆成 $u \to lca$ 和 $v \to lca$ 两部分。设 $val_u$ 表示从当前节点到 $u$ 的路径上的 $dp$ 之和，这样可以做到 $O(nm)$。
  
- 最终答案为 $\sum w_i - dp_{1,0}$。
  
- 复杂度为 $O(mn + m \times 2^{10})$
  
- 最后要注意一些细节，例如当 $u,v$ 中某一个本身就是 $lca$ 时，贡献只需要加上 $dp_{v,0}$ 和 $val_{v}$；以及处理第二种情况时，要按照集合 $1$ 的数量从多到少来算。
  

#### Code：
  
```cpp
#include <bits/stdc++.h>
#define ll long long
#define ckmax(a, b) (a = max(a, b))
#define MP make_pair
#define pcn putchar('\n')
#define fi first
#define se second
using namespace std;

const int maxn = 1000;
const int maxm = 5000;
const int maxlg = 10;
const int maxs = 10;
const int max2s = (1 << 10);
const int INT = 1e9 + 50;

int n, m;
struct E{int v, w, id, nx;} e[maxm * 2 + 50];
int hd[maxn + 50], cnt = 1;
map<pair<int, int>, int> edge; // 用于寻找 (u, v) 这条边的编号 
struct E2{int u, v, x, y, w;}; // 非树边的 (u, v)，是 lca 的第 x, y 编号的儿子，边权为 w 
vector<E2> e_lca[maxn + 50]; 
bool vis[maxm * 2 + 50];
int fa[maxn + 50], pos[maxn + 50][maxs + 5]; // pos[u][i] 是 u 子树中第 i 个儿子在前向星的位置 
int fa2[maxn + 50][maxlg + 5], dep[maxn + 50], lg[maxn + 50]; // 倍增 LCA 
vector<int> T(max2s); // 长度为 10 的集合按照 1 个数从大到小排列 
int val[maxn + 50], dp[maxn + 50][max2s + 50];

void ade(int u, int v, int w){
	e[++ cnt] = E{v, w, 0, hd[u]};
	hd[u] = cnt;
	edge[MP(u, v)] = cnt;
}

void Ade(int u, int v, int w){
	ade(u, v, w), ade(v, u, w);
}

void dfs(int u, int father){
	vis[u] = true;
	fa[u] = father;
	dep[u] = dep[father] + 1;
	
	int cntid = 0;
	
	for(int i = hd[u]; i; i = e[i].nx){
		int v = e[i].v, w = e[i].w;
		
		if(vis[v] || w) continue;
		
		// 预处理每条树边的编号 
		e[i].id = e[i ^ 1].id = cntid ++;
		pos[u][e[i].id] = i;
		
		dfs(v, u);
	}
}

void LCA_Init(){
	for(int i = 1; i <= n; ++ i){
		fa2[i][0] = fa[i];
	}
	
	for(int j = 1; j <= lg[n]; ++ j){
		for(int i = 1; i <= n; ++ i){
			fa2[i][j] = fa2[fa2[i][j - 1]][j - 1];
		}
	}
}

// 返回 u, v 跳到 lca 的两个儿子 
pair<int, int> LCA(int u, int v){
	if(dep[u] < dep[v]) swap(u, v);
	
	for(int i = lg[dep[u] - dep[v]]; i >= 0; -- i){
		if(dep[fa2[u][i]] > dep[v]){
			u = fa2[u][i];
		}
	}
	
	if(fa[u] == v) return MP(u, u);
	
	if(dep[u] != dep[v]) u = fa[u];
	
	for(int i = lg[dep[u]]; i >= 0; -- i){
		if(fa2[u][i] != fa2[v][i]){
			u = fa2[u][i];
			v = fa2[v][i];
		}
	}
	
	return MP(u, v);
}

int dist(int a, int b, int lca){
	return dep[a] + dep[b] - 2 * dep[lca];
}
 
void getValue(int u){
	for(int i = hd[u]; i; i = e[i].nx){
		int v = e[i].v, w = e[i].w;
		
		if(v == fa[u] || w) continue;
		
		val[v] = val[u] + dp[u][1 << e[i].id];
		
		getValue(v);
	}
}

void dfs2(int u){
	val[u] = 0;
	
	for(int i = hd[u]; i; i = e[i].nx){
		int v = e[i].v, w = e[i].w;
		
		if(v == fa[u] || w) continue;
		
		dfs2(v);
		
		val[v] = 0;
		getValue(v);
	}
	
	// 计算不选非树边的情况 
	for(int S = 0; S < max2s; ++ S){
		for(int i = 0; i < 10; ++ i){
			if((S >> i & 1) == 0){
				dp[u][S] += dp[e[pos[u][i]].v][0];
				// 这里如果 in[u] < 10，那么 pos[u][i] 为 0，不会对答案产生贡献 
			}
		}
	}
	
	// 计算选树边的情况 
	for(auto S : T){
		for(auto j : e_lca[u]){
			if((S >> j.x & 1) || (S >> j.y & 1)) continue;
			
			if(j.x != j.y){
				// u, v 自己都不是 lca 
				ckmax(dp[u][S], dp[u][S | (1 << j.x) | (1 << j.y)] + dp[j.u][0] + dp[j.v][0] + j.w + val[j.u] + val[j.v]);
			}
			else{
				// u, v 有一个是 lca 
				ckmax(dp[u][S], dp[u][S | (1 << j.x) | (1 << j.y)] + dp[dep[j.u] > dep[j.v] ? j.u : j.v][0] + j.w + val[j.u] + val[j.v]);
			}
		}
	}
}

int main(){
	
	lg[0] = -1;
	for(int i = 2; i <= maxn + 30; ++ i){
		lg[i] = lg[i >> 1] + 1;
	}
	
	// 集合按照元素个数从大到小枚举 
	for(int S = 0; S < max2s; ++ S){
		T[S] = S;
	}
	
	sort(T.begin(), T.end(), [](int x, int y){
		return __builtin_popcount(x) > __builtin_popcount(y);
	});
	
	scanf("%d%d", &n, &m);
	
	int u, v, w, sumw = 0;
	for(int i = 1; i <= m; ++ i){
		scanf("%d%d%d", &u, &v, &w);
		
		Ade(u, v, w);
		
		sumw += w;
	}
	
	dfs(1, 0);
	
	LCA_Init();
	
	for(int i = 1; i <= n; ++ i){
		vis[i] = false;
	}
	
	// 求出每条边由谁来处理 
	for(int u = 1; u <= n; ++ u){
		for(int i = hd[u]; i; i = e[i].nx){
			int v = e[i].v, w = e[i].w;
			
			if(vis[i] || !w) continue;
			
			vis[i] = vis[i ^ 1] = true;
			
			pair<int, int> t = LCA(u, v);
			int lca = fa[t.fi];
			
			// 去除构成偶环的非树边 
			if((dep[u] + dep[v] - (dep[lca] << 1) & 1) == 0){
				e_lca[lca].push_back(E2{u, v, e[ edge[MP(lca, t.fi)] ].id, e[ edge[MP(lca, t.se)] ].id, w});
			}
		}
	}
	
	dfs2(1);
	
	printf("%d\n", sumw - dp[1][0]);
	
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：7)

# 洛谷 P4649 题解

[$\text{Link}$](https://www.luogu.com.cn/problem/P4649)

## 思路分析

反面考虑，计算最多能加几条非树边使图上没有偶环

如果某条非树边 $(u,v)$ 添加后使得 $u\to \operatorname{LCA}(u,v)\to v\to u$ 的长度为偶数，则不能必选择 $(u,v)$

只考虑添加 $(u,v)$ 使得 $u\to \operatorname{LCA}(u,v) \to v\to u$ 的长度为奇数的边 $(u,v)$

如果两条边 $(u,v)$ 和 $(x,y)$ 的树上路径有交集，如下图所示，也会形成一个偶环：

[![vV2JmR.png](https://s1.ax1x.com/2022/08/03/vV2JmR.png)](https://imgtu.com/i/vV2JmR)

所以我们的目标就是在树上选择若干条不相交的非树边使得其权值和最大

考虑在添加某条非树边 $(u,v)$ 后把 $u\to v$  的所有边都删掉，然后分成若干棵子树进行 dp

我们把每条非树边 $(u,v)$ 在 $\operatorname{LCA}(u,v)$ 处考虑，设 $dp_{p,\mathbf S}$ 表示以 $u$ 为根的子树，且 $p$ 到集合 $\mathbf S$（状态压缩）中的儿子的边已经被删掉后能选择的最优答案

那么对于一条路径 $(u,v)$ 满足 $\operatorname{LCA}(u,v)=p$ 他能带来的价值为：
$$
value(u,v)=w(u,v)+\sum_{x\in path(u,v)}^{fa(x)\neq p,x\neq p} dp_{fa(x),\{x\}}
$$
设 $u\to v$ 的路径包含 $x\to p\to y$ 且 $x,y$ 均为 $p$ 的儿子，我们可以用用这个价值去转移：

$$
\forall \mathbf S:x,y\not\in \mathbf S\\
dp_{p,S}\gets value(u,v)+dp_{p,\mathbf S\cup\{x,y\}}
$$

最终的答案为 $\sum w(u,v)-dp_{1,\varnothing}$

 时间复杂度 $\Theta(m\log n+n2^{|\mathbf S|})$

> 总结：
>
> 神仙题
>
> 观察性质转化成生成仙人掌
>
> 然后状压树上 dp
>
> 很强

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1001;
vector <int> tree[MAXN];
struct node {
	int src,des,val;
};
vector <node> vec,link[MAXN];
int dep[MAXN],fa[MAXN],siz[MAXN],son[MAXN],root[MAXN],fid[MAXN];
int dp[MAXN][1<<10];
inline int bit(int x) {
	return 1<<x;
}
inline void init1(int p,int f) {
	fa[p]=f,siz[p]=1,dep[p]=dep[f]+1;
	for(int v:tree[p]) {
		if(v==f) continue;
		init1(v,p);
		siz[p]+=siz[v];
		if(siz[v]>siz[son[p]]) son[p]=v;
	}
}
inline void init2(int p,int r) {
	root[p]=r;
	if(son[p]) init2(son[p],r);
	for(int v:tree[p]) {
		if(v==son[p]||v==fa[p]) continue;
		init2(v,v);
	}
}
inline void init3(int p) {
	for(int i=0;i<tree[p].size();++i) {
		int v=tree[p][i];
		if(v==fa[p]) continue;
		fid[v]=bit(i);
		init3(v);
	}
}
inline int LCA(int u,int v) {
	while(root[u]!=root[v]) {
		if(dep[root[u]]<dep[root[v]]) swap(u,v);
		u=fa[root[u]];
	}
	return dep[u]>dep[v]?v:u;
}
inline void dfs(int p) {
	for(int v:tree[p]) {
		if(v==fa[p]) continue;
		dfs(v);
	}
	for(int s=0;s<bit(tree[p].size());++s) {
		for(int i=0;i<tree[p].size();++i) {
			if(!((s>>i)&1)) dp[p][s]+=dp[tree[p][i]][0];
		}
	}
	for(auto e:link[p]) {
		int val=e.val,u=0,v=0;;
		if(e.src!=p) {
			val+=dp[e.src][0];
			for(u=e.src;fa[u]!=p;u=fa[u]) val+=dp[fa[u]][fid[u]];
		}
		if(e.des!=p) {
			val+=dp[e.des][0];
			for(v=e.des;fa[v]!=p;v=fa[v]) val+=dp[fa[v]][fid[v]];
		}
		int t=fid[u]|fid[v];
		for(int s=0;s<bit(tree[p].size());++s) {
			if(!(s&t)) dp[p][s]=max(dp[p][s],val+dp[p][s|t]);
		}
	}
}
signed main() {
	int n,m,res=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		if(!w) {
			tree[u].push_back(v);
			tree[v].push_back(u);
		} else {
			res+=w;
			vec.push_back((node){u,v,w});
		}
	}
	init1(1,0);
	init2(1,1);
	init3(1);
	for(auto e:vec) {
		int lca=LCA(e.src,e.des);
		if(!((dep[e.src]+dep[e.des]-dep[lca]*2)&1)) link[lca].push_back(e);
	}
	dfs(1);
	printf("%d\n",res-dp[1][0]);
	return 0;
}

```

---

## 作者：CarroT1212 (赞：3)

+ 关键词：树上状压 DP。

首先把原树拎起来，于是你获得了很多在树上随便连接两个点的带权边。

直接求使得图中不存在偶环需要删的边权之和似乎有点难搞啊，不如反过来，求最多能加多少边权使得图中不存在偶环。

首先如果一条带权边连接的两个点距离为奇数，那这条边加上就会出偶环，肯定得删掉，于是不管它。

然后就要求剩下的边形成的奇环互不相交，也就是没有任何一条边被多个奇环经过，否则就会出偶环。

这怎么搞啊。发现还有个条件没用：每个点度数不超过 $10$。

考虑把每个带权边拿到两点的 LCA 上处理，然后状压每个点还有哪些边没有被奇环经过。设 $dp_{i,S}$ 为点 $i$ 的出边集合状态 $S$ 还没有被奇环经过时，$i$ 子树内对答案产生的贡献。

那么初值为 $dp_{u,S}=\sum\limits_{v\in son(u),v\notin S}dp_{v,0}$。

转移时，枚举所有 LCA 为点 $u$ 的带权边。考虑这条边被选中时能给 $u$ 的答案带来多少贡献。设其为 $res$，带权边两端为 $x,y$。

则首先 $res$ 要加上 $dp_{x,0}+dp_{y,0}$。然后对于 $x,y$ 间的路径 $path(x,y)$，$res$ 要加上 $\sum\limits_{c\in path(x,y)c\neq u}dp_{fa_c,2^{num_c}}$，其中 $fa_c$ 为 $c$ 的父亲，$num_c$ 为从 $c$ 的父亲到 $c$ 经过的父亲的出边的编号。根据定义不难理解。

这个过程就是求在选了这条带权边的情况下，这一条路径上还能再加的贡献。然后用这个算出来的 $res$ 把 $dp_{u,S}$ 一路往下转移即可。

最后答案是 $\sum C-dp_{1,0}$。

```cpp
int n,m,a[W],b[W],c[W];
int fa[N][12],dep[N];
int dp[N][1<<10],cnt[N],tnc[N];
vector<int> e[N],me[N];
vector<pair<pii,int> > ee;
void dfs(int p,int f) {
	fa[p][0]=f,dep[p]=dep[f]+1;
	for (int i=1;i<=10;i++) fa[p][i]=fa[fa[p][i-1]][i-1];
	for (int i:e[p]) if (i!=f) dfs(i,p);
}
int lca(int x,int y) {
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=10;~i;i--) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
	if (x==y) return x;
	for (int i=10;~i;i--) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
void cal(int p,int f) {
	int tmp=0;
	for (int i:e[p]) if (i!=f) cal(i,p),cnt[i]=tmp++,tnc[i]=1<<cnt[i];
	for (int i=0;i<1<<tmp;i++) for (int j:e[p]) if (j!=f&&i>>cnt[j]&1^1) dp[p][i]+=dp[j][0];
	for (int i:me[p]) {
		int x=a[i],y=b[i],z=c[i];
		if (x!=p) {
			z+=dp[x][0];
			while (fa[x][0]!=p) z+=dp[fa[x][0]][tnc[x]],x=fa[x][0];
		}
		if (y!=p) {
			z+=dp[y][0];
			while (fa[y][0]!=p) z+=dp[fa[y][0]][tnc[y]],y=fa[y][0];
		}
		for (int j=0;j<1<<tmp;j++) if ((x==p||j>>cnt[x]&1^1)&&(y==p||j>>cnt[y]&1^1))
			dp[p][j]=max(dp[p][j],dp[p][j|tnc[x]|tnc[y]]+z);
	}
}
void mian() {
	scanf("%d%d",&n,&m);
	for (int i=1,x,y,z;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		if (!z) e[x].pb(y),e[y].pb(x);
		else ee.pb({{x,y},z});
	}
	dfs(1,0);
	for (int i=0;i<m-n+1;i++) {
		a[i]=ee[i].first.first,b[i]=ee[i].first.second,c[i]=ee[i].second;
		if (dep[a[i]]+dep[b[i]]&1^1) me[lca(a[i],b[i])].pb(i);
	}
	cal(1,0);
	cout<<accumulate(c,c+m-n+1,0)-dp[1][0];
}
```

---

## 作者：XFlypig (赞：1)

[P4649 [IOI2007] training 训练路径](https://www.luogu.com.cn/problem/P4649)

之前就想着能不能出一道树上状压 DP，一直没有好的想法，然后就发现 IOI 十几年前就出过了，菜菜子一枚，~~这种题果然和我想得一样毒瘤~~。

题目大意：给一棵树和一些非树边，非树边有权值可以删去，要求最终的图不存在长度为偶数的简单环，要求保留边的总权值最小。

首先简单分析一下题目就可以发现如果某一条非树边连接的两个点之间的距离为奇数那一定需要设置路障，否则直接就是一个偶环，再者如果两个非树边在树上的路径有交集，那也需要删去一个，证明大概就是单独看两条边和树边组成的环都是奇环，拼起来后总边数为偶数（这里重边算两条），然后把重边删掉，每一条重边对应两条边，所以最后的环一定是一个偶环。

所以我们稍微处理了这颗树后（把不能保留的非树边去掉），要求的就是保留的非树边总权值最大。

然后就是神仙的树上状压 DP 了。

最简单的思路是设 $f_i$ 表示只考虑 $i$ 子树内部的最大权值和，然后套路的把一条非树边放到 LCA 处考虑，然后~~看题解~~会发现转移时需要路径上的点**不考虑**某个儿子的 DP 值，然后发现可以状压儿子，即设 $f_{i,S}$ 表示在 $i$ 的子树中不考虑 $S$ 中的儿子所保留的最大权值和。

转移就是（此处借用[大佬](https://www.luogu.com.cn/article/k9hipwth)的$\LaTeX$）

$$f_{(i,S)}=\max f_{(i,S|x|y)}+val，\{ S| x\notin S, y\notin S\}$$

这里的 $val$ 是对于非树边的两端点 $u,v$，它们的$f_{u,0},f_{v, 0}$加上在两点间路径上除两端点和 LCA 的其他点不考虑某个儿子的 DP 值，这个儿子就是包含 $u$ 或者 $v$ 的那个儿子。

时间复杂度为 $\Theta (m2^{10}+mn)$。

```cpp

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1010, M = 5010, S = 1 << 10;

int n, m;
int rid[N], rk[N];
int h[N], e[N << 1], ne[N << 1], idx;
int fa[N][10], dep[N];
int f[N][S];
struct Node
{
    int a, b, c;
} edge[M];
vector<int> g[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs_lca(int u, int p)
{
    dep[u] = dep[p] + 1, fa[u][0] = p;
    for (int k = 1; k <= 9; k ++ )
        fa[u][k] = fa[fa[u][k - 1]][k - 1];
    for (int i = h[u]; ~i; i = ne[i])
        if (e[i] != p) dfs_lca(e[i], u);
}

int lca(int a, int b)
{
    if (dep[a] < dep[b]) swap(a, b);
    for (int k = 9; k >= 0; k -- )
        if (dep[fa[a][k]] >= dep[b])
            a = fa[a][k];
    if (a == b) return a;
    for (int k = 9; k >= 0; k -- )
        if (fa[a][k] != fa[b][k])
            a = fa[a][k], b = fa[b][k];
    return fa[a][0];
}

void dfs(int u)
{
    for (int i = h[u]; ~i; i = ne[i])
        if (e[i] != fa[u][0]) dfs(e[i]);
    int cnt = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int ver = e[i];
        if (ver != fa[u][0])
            rid[ver] = 1 << cnt, rk[cnt ++ ] = ver;
    }
    
    for (int i = 0; i < 1 << cnt; i ++ )
        for (int j = 0; j < cnt; j ++ )
            if (!(i >> j & 1))
                f[u][i] += f[rk[j]][0];
    for (int  t : g[u])
    {
        int a = edge[t].a, b = edge[t].b, c = edge[t].c;
        if (a != u)
        {
            c += f[a][0];
            while (fa[a][0] != u)
                c += f[fa[a][0]][rid[a]], a = fa[a][0];
        }
        if (b != u)
        {
            c += f[b][0];
            while (fa[b][0] != u)
                c += f[fa[b][0]][rid[b]], b = fa[b][0];
        }
        for (int i = 0; i < 1 << cnt; i ++ )
            if ((i & rid[a]) + (i & rid[b]) == 0)
                f[u][i] = max(f[u][i], f[u][i | rid[a] | rid[b]] + c);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    int res = 0, pm = 0;
    for (int i = 1; i <= m; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (!c) add(a, b), add(b, a);
        else edge[ ++ pm] = {a, b, c}, res += c;
    }
    
    dfs_lca(1, 0), m = pm;
    for (int i = 1; i <= m; i ++ )
    {
        int a = edge[i].a, b = edge[i].b, t = lca(a, b);
        if ((dep[a] + dep[b] - 2 * dep[t]) % 2 == 0)
            g[t].push_back(i);
    }
    
    dfs(1);
    
    cout << res - f[1][0] << endl;
    
    return 0;
}

```

---

