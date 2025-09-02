# [COTS 2025] 吸尘 / Usisavač

## 题目描述



Mirko 有一所大房子，由 $N$ 个房间通过 $N-1$ 条走廊连接而成。每条走廊连接两个不同的房间，且所有房间互相连通。每条走廊长 $1$ 米。Mirko 经常打扫房间，但很少清理走廊。现在走廊积满灰尘，Mirko 想要用吸尘器清理它们。  

每个吸尘器都有电缆长度限制。**每个房间有插座，吸尘器必须插入某个房间的插座才能工作**。Mirko 从房间 $1$ 出发，可以进行以下操作：  

- 若吸尘器未通电，他可以：  
    - 将吸尘器插入当前所在房间的插座。  
    - 手持吸尘器移动到相邻房间。穿过走廊需 $1$ 分钟。  
- 若吸尘器已通电，他可以：  
    - 若处于插入吸尘器的房间，可以拔下插头。  
    - 移动到相邻房间并清理路径上的走廊。仅当电缆长度足够时可行（即插入插座房间与目标房间的距离不超过电缆长度）。清理走廊需 $1$ 分钟。  

Mirko 的吸尘器坏了。现在商店有 $Q$ 台吸尘器，第 $i$ 台的电缆长度为 $r_i$ 米。他想知道对于每台吸尘器，清理所有走廊的最短时间。请帮他计算这些时间！  

## 说明/提示


### 样例解释

样例 $1$ 解释：对于 $r_i=2$ 的询问，一个最优方案如下：

- 从房间 $1$ 走到房间 $3$。（$2$ 分钟）
- 在房间 $3$ 插入吸尘器。
- 吸尘房间 $3,4$ 间以及房间 $4,5$ 间的走廊（$2$ 分钟）。
- 返回房间 $3$。（$2$ 分钟）
- 吸尘房间 $3,2$ 间以及房间 $2,1$ 间的走廊（$2$ 分钟）。这样所有走廊都已清理干净。

### 数据范围

- $2 \leq N \leq 3 \times 10^5$；
- $1 \leq Q \leq 3 \times 10^5$；
- $1\le x_i,y_i\le N$；
- $x_i\neq y_i$；
- 任意两个房间都通过走廊连通；
- $1\le r_i\le N$；
- 所有输入的数均为整数。

### 子任务

Subtask 0 为样例。

| 子任务编号 | $N\le$ | $Q\le$ | 特殊性质 | 得分 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $10^3$    | $10^3$ | $-$ | $16$ |
| $2$ | $3\times 10^5$    | $3\times 10^5$ | $\text{A}$ | $10$ |
| $3$ | $3\times 10^5$    | $1$ | $-$ | $22$ |
| $4$ | $10^5$    | $10^5$ | $-$ | $31$ |
| $5$ | $3\times10^5$    | $3\times10^5$ | $-$ | $21$ |

特殊性质 $\text{A}$：$\forall 1\le i\le N-1$，存在一条连接 $i$ 和 $i+1$ 的走廊。


## 样例 #1

### 输入

```
5 2
1 2
2 3
3 4
4 5
2 5```

### 输出

```
8 4```

## 样例 #2

### 输入

```
10 2
1 2
2 4
5 2
6 3
3 1
6 7
9 7
8 6
8 10
1 3```

### 输出

```
24 16```

## 样例 #3

### 输入

```
6 2
3 1
3 5
4 3
4 2
2 6
5 1```

### 输出

```
6 12```

# 题解

## 作者：Sliarae (赞：3)

设结点 $i$ 的高度为 $\text{high}_i$，具体而言就是 $i$ 到子树内叶子距离的最大值，$i$ 的深度为 $\text{dep}_i$。

首先，假设我们最终停留在 $e$ 点。我们强制它走回 $1$ 点，构成一条回路，再将答案减去 $\text{high}_1$，也就是树高，因为最优策略是停留在深度最大的点。

假设某次询问给出一个 $r$，表示吸尘器的电缆长度为 $r$。

我们猜测最优策略是，沿着树的形状 dfs，假设我们现在位于 $u$，要走到 $u$ 的一个儿子 $v$：

- 若 $\text{high}_u  \le r$，就把吸尘器插在 $u$ 的位置，将 $u$ 子树内所有边都清理一遍，拔掉插座。

- 若 $\text{high}_u > r$，那么把吸尘器插在 $u$，将边 $(u, v)$ 清理后回到 $u$，将插座拔掉后正常走到 $v$。

对于一条边 $(v, fa_v)$，易知若 $\text{high}_v < r$，则它会被经过 $2$ 次，否则会被经过 $4$ 次，则答案为：

$$ 4(n - 1) - 2\sum\limits_{i = 2}^{n} [\text{high}_i < r] - \text{high}_1$$

这个容易前缀和维护，单次询问 $O(1)$。

现在我们通过说明，对于每条边 $(v, fa_v)$，若 $\text{high}_v \ge r$，则它至少被经过 $4$ 次。

考虑它是如何被清理的，如果吸尘器在 $v$ 子树外，那么清理时要经过边 $(v, fa_v)$ $2$ 次，由 $\text{high}_v \ge r$，之后还要在 $v$ 子树内插吸尘器，所以还要带吸尘器经过 $2$ 次。

如果吸尘器在 $v$ 子树内，可能会使得 $v$ 向上 $r$ 条边都少经过 $2$ 次，但是最终停留的点的深度会减少 $2r$，所以还是不会变优。

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int kN = 3e5 + 5; 

int n, q;
vector<int> e[kN];
int dep[kN], high[kN], p[kN];

void Dfs (int u, int r) {
  for (auto v : e[u]) {
    if (v == r) continue;
    dep[v] = dep[u] + 1;
    Dfs(v, u);
    high[u] = max(high[u], high[v] + 1);
  }
}

int main () {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> q;
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  Dfs(1, 0);
  int mxd = 0; 
  for (int i = 1; i <= n; ++i) mxd = max(mxd, dep[i]);
  for (int i = 2; i <= n; ++i) ++p[high[i]];
  for (int i = 1; i <= n; ++i) p[i] += p[i - 1];
  for (int i = 1, r; i <= q; ++i) {
    cin >> r;
    cout << 4 * (n - 1) - mxd - 2 * p[r - 1] << ' ';
  }
  cout << '\n';
  return 0; 
}
```

---

## 作者：Mr_Az (赞：2)

# [\[COTS 2025\] 吸尘 / Usisavač](https://www.luogu.com.cn/problem/P12449)

### Algorithm:

构造 + 模拟。

### Solution:

一般这种题目思考方式可以是从链上的做法扩展到树上（但这道题比较困难），所以笔者先考虑了链上的特殊情况。

#### Subtask 2（10 pts）:

可以按照以下方法进行贪心：

**此处 $n$ 代表边数，即 $n \leftarrow n-1$。**

1. 如果 $r \ge n$，那么直接输出 $n$。
2. 将长度为 $n$ 的路径分成若干个长度不超过 $r$ 的子段，若最后剩余部分长度不足 $r$，则单独作为一段处理。
3. 将最后一段长度为 $r$ 的段与剩余段交换顺序，然后按如图所示方法清扫（橙色代表手上吸尘器插入，黑色代表手上吸尘器没有插入）：

![1.png](https://s2.loli.net/2025/05/09/UuY9AgcEDnm7Mso.png)

经过计算（令 $n \bmod x \equiv m$），答案应为：$3 \times (x(\lfloor \frac{n}{x} \rfloor -1)+m)+x=3n-2x$。

```cpp
while(m--){
    int x;read(x);
    if(x>=n) printf("%lld ",n)
    else printf("%lld ",3*n-2*x);
}
```

本质上我们需要走完整条路径 $n$ 的三倍长度，但最后一段只需走一遍，无需返回，因而可省下 $2x$，总共 $3n - 2x$。

#### 正解：

但是在树上的时候，我们发现链上的情况比较难以扩展。所以我们推翻前面的过程，直接考虑树的做法。经过手玩我们会发现一些性质：

1. 最终结束的位置一定是一个**深度最大的点**，从 $1$ 到该点的最短路上的边可以**少走一次**（在这里结束就不需要返回到根去扫另一棵子树了）；
2. 加上从 $1$ 到结束点最短路上的边后，每条边要么经过**两次**，要么经过**四次**；
3. 经过两次的边一定为**某些子树**。

**以下讨论边经过的次数默认加上从 $1$ 到结束点最短路上的边。**

类比 Subtask 2 中对最后一段的处理，树上对应的做法是：在靠近叶子的某个点插入电源，并**恰好能够扫完它的整棵子树**。

形式化地说，记 $mx_i$ 为 $\max_{v \in subtree_u} dep_v-dep_u+1$，也就是**子树中最深的点为根时，这个点的深度**。那么上面那句话的这个点要满足 $mx_u \le r$ 并且 $mx_{fa_u} > r$。我们把这样的点提出来之后会发现：这些点子树里的边都**只经过两次**。

（**请读者在这里思考**：为什么条件是 $mx_u \le r$ 并且 $mx_{fa_u} > r$。）

对于这个发现，证明非常好想，我们考虑每一次经过这条边都在干啥：

| 边类型     | 情况         | 次数  | 原因                             |
| ------- | ---------- | --- | ------------------------------ |
| 关键点子树内边 | 子树可独立清扫    | 2 次 | 插吸尘器清扫 + 返回                    |
| 非关键点子树边 | 需递归清扫其剩余子树 | 4 次 | 插吸尘器清扫 + 返回拿吸尘器 + 下去子树里清扫 + 返回 |

如何**证明**这是最优的方案，我们称插入电源的点记为**关键点**，那么则有：

1. 若这个点的子树内没有**关键点**，则至少要走**两次**，对应上方子树里的边经过两次；
2. 若这个点的子树内有**关键点**，则至少要走**四次**，对应上方非子树里的边经过四次；

由此可见，我们想让该方案**最优**必须要让 $2$ **情况覆盖的边数更多**，而对于 $mx_u > r$ 的点，其内部必然存在**至少一个关键点**，因为只凭这个点无法扫到其的所有子树。所以最优的方案就是将所有 $mx_u \le r$ 并且 $mx_{fa_u} > r$ 的点**全部选择**。

至于统计答案，可以直接 `dfs` 预处理答案，也可以观察到对于任意一条父子边 $(u,son)$，如果 $mx_u \le r$，那么这条边走**两次**，反之走**四次**，证明显然。

记 $cnt_i$ 为 $mx_u=i$ 的点的数量，那么答案即为：$4(n-1)-\max\{dep_u\}-2\sum_{i=1}^{r} cnt_i$，给 `cnt` 数组做个前缀和即可。

**需要注意**，$cnt_{mx_1}$ 需要减一，不然会少算。

这道题目的关键在于发现**深度最大路径可以少走一次**以及**关键点如何选择以减少遍历次数**。

### Code:

```cpp
namespace Mr_Az{
	const int N=3e5+8;
	int T=1;
	int n,m,MAX;
	int deg[N],dep[N],cnt[N],mx[N];
	bool spj1=1;
	vector<int> e[N];
	void dfs(int u,int fa){
		dep[u]=dep[fa]+1;MAX=max(MAX,dep[u]-1);
		if(e[u].size()==1) mx[u]=1;
		for(auto v:e[u]){
			if(v==fa) continue;
			dfs(v,u);
			mx[u]=max(mx[u],mx[v]+1);
		}
		cnt[mx[u]]++;
		return ;
	}
	inline void solve(){
		read(n,m);
		for(rint i=1,u,v;i<n;i++){
			read(u,v),e[u].pb(v),e[v].pb(u);
			deg[u]++;deg[v]++;
			spj1&=(deg[u]<=2&&deg[v]<=2);
		}
		if(spj1){
			n--;
			while(m--){
				int x;read(x);
                printf("%lld ",3*n-2*x);
			}
			return ;
		}// 可删去，链情况特判。
		dfs(1,0);
		cnt[mx[1]]--; // 小细节
		for(rint i=1;i<=n;i++) cnt[i]+=cnt[i-1];
		while(m--){
			int x;read(x);
			printf("%lld ",4*(n-1)-MAX-2*cnt[x]);
		}
		return ;
	}
	inline void mian(){if(!T) read(T);while(T--) solve();}
}
```

### 样例解释

下面为样例二的手玩结果：![graph 2.png](https://s2.loli.net/2025/05/09/2aB14zlemJohdEG.png)

---

## 作者：Undead2008 (赞：1)

[COTS 2025 题解合集](https://www.luogu.com.cn/article/dupadkce)

先考虑吸完尘回到 $1$ 怎么做，你一定会使用开着的吸尘器将每条边经过两遍，现在就变成了最小化关着吸尘器走的路。

下文中的讨论不认为点 $1$ 是叶子，无论他度数是几。

考虑对每个 $i=1\sim n$ 分别求解，$i=1$ 时你需要拿着关着的吸尘器经过每个不是叶子的节点，$i=2$ 时你不用经过这些节点形成的连通块中的叶子节点，$i=3$ 时你不用经过 $i=2$ 时经过的节点形成的连通块中的叶子节点，以此类推，可以发现这是一个删叶子的过程，直接模拟就行。

然后就是不回到 $1$ 的情况，这时你一定会在 $1$ 能到达的最远点停留，将所有答案减去 $1$ 到最远点的距离即可。

```cpp
#include"bits/stdc++.h"
#ifdef REANI
	#include"windows.h"
	using namespace std;
	void SetMemoryLimit(SIZE_T MB){
		HANDLE job=CreateJobObject(NULL,NULL);
		assert(job!=NULL);
		JOBOBJECT_EXTENDED_LIMIT_INFORMATION info={0};
		info.BasicLimitInformation.LimitFlags=JOB_OBJECT_LIMIT_PROCESS_MEMORY;
		info.ProcessMemoryLimit=MB;
		assert(SetInformationJobObject(job,JobObjectExtendedLimitInformation,&info,sizeof(info))&&AssignProcessToJobObject(job,GetCurrentProcess()));
	}
#else
	using namespace std;
#endif
const int maxn = 3e5+10;
int n,q,Dg[maxn],A[maxn],Dp[maxn];
vector<int>e[maxn];
int M;
void D(int p,int Fa){
	M=max(M,Dp[p]);
	for(auto To:e[p]){
		if(To==Fa)continue;
		Dp[To]=Dp[p]+1;
		D(To,p);
	}
}
int main(){
	#ifdef REANI
		SetMemoryLimit(512*1048576);
	#endif
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>n>>q;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
		Dg[u]++,Dg[v]++;
	}
	D(1,0);
	vector<int>Db;
	for(int i=1;i<=n;i++)
		if(Dg[i]==1&&i!=1)
			Db.push_back(i);
	int S=n;
	for(int i=1;i<=n;i++){
		vector<int>Nw;
		for(auto x:Db){
			for(auto To:e[x]){
				if(Dg[To]==-1)continue;
				Dg[To]--;
				if(Dg[To]==1&&To!=1)Nw.push_back(To);
			}
			Dg[x]=-1,S--;
		}
		Db=Nw;
		A[i]=2*(n-1)+2*(S-1)-M;
	}
	for(int i=1,T;i<=q;i++)
		cin>>T,cout<<A[T]<<' ';
	cout<<'\n';
}
```

---

## 作者：Purslane (赞：1)

# Solution

简单结论题。

考虑 $r$ 非常大的时候，显然等价于一个经典问题：你要遍历树上的每个点（也就是每条边）至少 $1$ 次，问你至少要走多少步。这个就是，$2(n-1) - \text{mxlen}_1$，其中 $\rm mxlen$ 表示从 $1$ 开头的最长链。

假设我们知道了最终在 $p_1$，$p_2$，$\cdots$，$p_k$ 处插了插头，以这些点为起点清理到的最长路径为 $r_1$、$r_2$、$\cdots$、$r_k$。

我们可以这么计算代价：

1. 每条边在清理的时候都会遍历两次（当然如果停在 $p_i$，就有 $r_i$ 条边不会被清理），$2(n-1)$；
2. 要在这些插插头的位置抱着吸尘机游荡，设 $\{p_i\} \cup \{1\}$ 构成的虚树有 $t$ 条边，就得花 $2t$ 的代价。如果停在 $p_i$，就有 $\text{dis}(1,p_i)$ 条边只用走一次。

所以代价是 $2(n+t-1) - \max_i \{\text{dis}(1,p_i)+r_i\}$。要将其最小化。

这个咋做呢。首先看 $\min t$。发现一条边必须在 $\{p_i\} \cup \{1\}$ 的虚树中，当且仅当 $\text{mxlen}_u \ge r$，其中 $u$ 是这条边深度（以 $1$ 为根）较大的点。因此可以求一个后缀和统计一下。当然如果你乱放 $t$ 肯定不能保证取到最小值，但是下面会证明最优解一定取到了最小值。

然后是 $\max_i \{\text{dis}(1,p_i)+r_i\}$。如果 $\text{mxlen}_{p_i} < r$ 我们可以将 $p_i$ 往父亲移动。这样 $t$ 会至少减少 $1$，而 $\max_i \{dis(1,p_i) + r_i\}$ 最多减少 $2$，发现代价不变。（准确来说这个调整需要按照 $p_i$ 的深度从大到小进行，不过我们不是 MO 不需要管这些无关紧要的细节）

这样每个 $\text{mxlen}_{p_i} \ge r$。而每个 $\text{mxlen}_{p_i}=r_i$ 的位置一定放了点，这样 $t$ 就取到了最小值。

发现次数 $r_i \le r$，$\text{dis}(1,p_i) \le \text{mxlen}_1 - r$，所以 $\max_{i}\{dis(1,p_i)+r_i\} \le \text{mxlen}_1$，等号是取得到的。

那么本题就做完了，复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e5+10;
int n,q,r,mxlen[MAXN],suf[MAXN];
vector<int> G[MAXN];
void dfs(int u,int f) {for(auto v:G[u]) if(v!=f) dfs(v,u),mxlen[u]=max(mxlen[u],mxlen[v]+1);return ;}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	ffor(i,1,n-1) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
	dfs(1,0);
	ffor(i,2,n) suf[mxlen[i]]++;
	roff(i,n,1) suf[i]+=suf[i+1];
	ffor(i,1,q) cin>>r,cout<<2*suf[r]+2*(n-1)-mxlen[1]<<' ';	
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：1)

先手玩一下，对于固定的 $r$，我们可以发现如下策略：

- 我们认为插座会被用到的点是关键点，我们只在关键点进行清扫。假设关键点按 dfs 序排序后为（默认包括点 $1$） $1,a_1,a_2,\dots a_n$。则我们一定会沿着 $1\to a_1\to a_2\to \dots \to a_n$ 的顺序走一遍，注意最后无需走 $a_n\to 1$，因为已经扫完了。

- 考虑关键点怎么确定最优。贪心地，我们肯定让这些点深度尽可能小，因此从下往上贪心就是优的。

- 考虑贡献。每条边先默认会被清扫一个来回，即为 $2(n-1)$，设走关键点造成的贡献为 $dis$，答案即为 $2(n-1)+dis-r$，因为同样地，最后一次清扫工作不需要走回关键点。

有了上述策略，我们考虑如何快速求 $dis$。首先 $dis$ 只会与关键点形成的虚树的叶子节点有关。并且显然最后的终点也会在其中。考虑先求出 $r=1$ 时的状态，这是容易的。然后每次 $r+1$ 时，我们暴力把叶子节点往上挪一步，$dis$ 在这个过程中对应更新即可。

直接模拟整个过程复杂度是正确的，因为我们只关心叶子节点，一旦某个点不再是叶子，我们可以直接把它扔掉，因此操作总次数是 $O(n)$ 的。可能需要数据结构判定某个点是否为叶子，所以总时间复杂度 $O(n\log n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e18;
bool M1;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N=3e5+5;
struct edge{
	int to,nxt;
}e[N<<1];
int n,q,cnt,head[N],ans[N];
void Add(int u,int v){
	e[++cnt].to=v;e[cnt].nxt=head[u];head[u]=cnt;
}
vector<int>g;
int dfn[N],ttt,dis,mx,mxdep;
int sz[N],fa[N],deep[N];
bool flag[N],tag[N];
int mxd[N];
void init(int u,int _fa,int dep){
	sz[u]=1;dfn[u]=++ttt;mxdep=max(mxdep,dep);
	fa[u]=_fa;deep[u]=dep;
	bool FLAG=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==_fa)continue;
		init(v,u,dep+1);
		sz[u]+=sz[v];
		if(sz[v]==1)FLAG=1;
		tag[u]|=tag[v];
		mxd[u]=max(mxd[u],max(deep[v],mxd[v]));
	}
	if(FLAG){
		flag[u]=1;tag[u]=1;
		//leaf
	}
}
map<int,int>mp;
void getdis(int u,int fa){
	mx=max(mx,deep[u]);
	if(flag[u])return;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa||!tag[v])continue;
		dis++;
		getdis(v,u);
	}
}
int c[N];
void add(int x,int w){
	for(x;x<=n;x+=(x&-x))c[x]+=w;
}
int ask(int x){
	int aaa=0;for(x;x>0;x-=(x&-x))aaa+=c[x];
	return aaa;
}
int query(int l,int r){
	return ask(r)-ask(l-1);
}
void solve(){
	vector<int>G;
	for(int i=2;i<=mxdep;i++){
		//cerr<<"work:"<<i<<'\n';
		mp.clear();G.clear();
		for(int j=0;j<g.size();j++){
			int x=g[j],X=fa[x];dis--;
			add(dfn[x],-1);
			if(!mp[X]&&X){
				mp[X]=1;G.push_back(X); //cout<<"???"<<X<<'\n';
				add(dfn[X],1);
			}
		}
		g.clear();
		for(int j=0;j<G.size();j++){
			int x=G[j];
			if(query(dfn[x]+1,dfn[x]+sz[x]-1))continue;
			g.push_back(x);//cout<<"???"<<x<<'\n';
		}
		for(int j=0;j<G.size();j++)add(dfn[G[j]],-1);
		for(int j=0;j<g.size();j++)add(dfn[g[j]],1);
		mx--;
		ans[i]=2*dis+2*(n-1)-mx-i;
		//cerr<<"!!!"<<i<<" "<<dis<<'\n';
		//for(int j=0;j<g.size();j++)cout<<g[j]<<" ";
		//cout<<'\n';
	}
}
bool M2;
signed main(){
    //freopen("data.in","r",stdin);
    n=read();q=read();
    for(int i=1;i<n;i++){
    	int u,v;u=read();v=read();Add(u,v);Add(v,u);
	}
	init(1,0,0);
	for(int i=1;i<=n;i++)if(flag[i])add(dfn[i],1);//,cout<<"!"<<dfn[i]<<'\n';
	for(int i=1;i<=n;i++){
		if(!flag[i])continue;
		//cout<<"?"<<i<<" "<<dfn[i]+1<<" "<<dfn[i]+sz[i]-1<<'\n';
		if(query(dfn[i]+1,dfn[i]+sz[i]-1)){
			flag[i]=0;continue;	
		}
		g.push_back(i);
		//cout<<"!!!"<<i<<'\n';
	}
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++)if(flag[i])add(dfn[i],1);
	getdis(1,0);
	ans[1]=2*dis+2*(n-1)-mx-1;
	//cerr<<"dis:"<<dis<<'\n';
	//cerr<<"mx:"<<mx<<'\n';
	//cout<<"mxdep: "<<mxdep<<'\n';
	solve();
	for(int i=1;i<=q;i++){
		int x;x=read();
		if(x>=mxdep)cout<<2*(n-1)-mxdep<<" ";
		else{
			cout<<ans[x]<<" ";
			//cout<<2*(n-1)+(n-1-x)-x<<" "; 
		}
	}
	cout<<'\n';
    cerr<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC<<"s"<<endl;
    cerr<<"Memory:"<<(&M1-&M2)/1024/1024<<"MB"<<endl;
    return 0;
}
```

---

