# [USACO23JAN] Subtree Activation P

## 题目描述

你有一棵根为 $1$ 的树，顶点标记为 $1 \dots N$ $(2 \le N \le 2 \cdot 10^5)$ 。每个顶点最初都是关闭的。在一次操作中，你可以将一个顶点的状态从关闭状态切换到开启状态，反之亦然。输出一个满足以下两个条件的操作序列的最小可能长度。

- 定义以顶点 $r$ 为根的子树由所有满足 $r$ 位于从 $1$ 到 $v$ 的路径上 $($包括 $v)$ , 的顶点 $v$ 组成。每一个顶点的子树，都有一个时刻，开启状态顶点的集合恰好是该子树中的顶点。
- 在整个操作序列之后，每个顶点都是关闭的。

## 说明/提示

有三个子树，分别对应 $\{1,2,3\}、\{2\}、\{3\}$ 。下面是最小可能长度的一个操作序列。

- 开启 $2$ (激活的顶点形成以 $2$ 为根的子树) 。
- 开启 $1$ 。
- 开启 $3$ (激活的顶点形成以 $1$ 为根的子树) 。
- 关闭 $1$ 。
- 关闭 $2$ (激活的顶点形成以 $3$ 为根的子树) 。
- 关闭 $3$ 。

子任务：
- 测试点 $2-3$ : $N \le 8$
- 测试点 $4-9$ : $N \le 40$
- 测试点 $10-15$ : $N \le 5000$
- 测试点 $16-21$ ：没有额外的限制。

## 样例 #1

### 输入

```
3
1 1```

### 输出

```
6```

# 题解

## 作者：Ecrade_ (赞：13)

题意：

- 给定一棵有 $n$ 个结点的树，$1$ 为根结点，初始时每个结点均为白色。
- 你可以改变任意一个结点的颜色（即白变黑，黑变白），称为一次操作。
- 当某个结点子树内的所有结点均为黑色且其余结点均为白色时，标记这个结点。
- 求使每个结点均被标记过且最终均为白色的最少操作次数。
- $2\le n\le 2\cdot10^5$。

---

下文中 “ 清空状态 ” 表示每个结点均为白色的状态，记 $sz_u$ 表示结点 $u$ 的子树大小，$fa_u$ 表示结点 $u$ 的父结点，$son_u$ 表示结点 $u$ 的子结点所组成的集合，$\text{lca}(u,v)$ 表示结点 $u,v$ 的最近公共祖先。

假如当前结点 $u$ 满足了可被标记的状态，那么我们下一步可以干什么？容易发现只有如下三种决策：

1. 进行 $2\cdot sz_u$ 次操作直接变为清空状态；
2. 进行 $2\cdot (sz_{fa_u}-sz_u)$ 次操作去标记 $fa_u$；
3. 进行 $2\cdot (sz_u-sz_v)$ 次操作去标记 $v$，其中 $v\in son_u$。

所以，**存在某个结点可被标记的状态才是我们应当去关注的状态**，且如何达成该状态的中间过程完全可以略去。

考虑将操作分段。具体地，对于每段操作，初始时以及经过这段操作之后均为清空状态，但中途不允许出现清空状态。可以发现，每段操作相互独立，那么我们接下来着重考察一段操作的性质。

根据定义，中途不允许出现清空状态，所以操作过程中仅能出现上文中的后两种决策，也就是依次标记一条树上路径的所有结点。注意，这条路径是**任意的**，它可以不是简单路径，也就是说，这条路径可以重复经过同一个结点任意多次。但是由于其任意性，这种路径的贡献很难直接计算出来，而且覆盖结点所形成的集合也难以描述。进而我们考虑，**能否对路径加一些限制，使其变得不那么 “ 任意 ” ？**

答案是可以的。选取两个叶子结点 $u,v$（$u,v$ 可以相同），再选取 $\text{lca}(u,v)$ **或其某个祖先结点** $w$，则我们可以将所有路径的形态都归为一类：依次标记 $u\to w$ 简单路径上的所有结点，再依次标记 $w\to v$ 简单路径上的所有结点。换句话来说，我们总是**先进行若干次第二种决策，再进行若干次第三种决策。** 不难通过计算得到，这样需要的操作次数恰好为 $2\cdot sz_w$。

>对路径形态给出一个不怎么严谨的证明，大家意会下即可。假如出现了如下图所示的情形（一条黑边上可能有多个结点）：
>
>![](https://cdn.luogu.com.cn/upload/image_hosting/fbtjm5e0.png)
>
>这种情况下需要的操作次数为 $2\cdot (sz_w+sz_x)-sz_y$。而我们完全可以如下图所示将其分为两条满足条件的路径：
>
>![](https://cdn.luogu.com.cn/upload/image_hosting/w978hj5q.png)
>
>假设 $x$ 的在 $x$ 到 $v$ 路径上的子结点为 $z$，那么这种情况下需要的操作次数为 $2\cdot (sz_w+sz_z)<2\cdot (sz_w+sz_x-sz_y)<2\cdot (sz_w+sz_x)-sz_y$，严格优于原先的路径。

那么题目可以转化为：**用若干条如上形态的路径覆盖所有结点**，每条路径所需的操作次数为，**路径上深度最小的结点的子树大小的两倍**。

很自然地考虑使用树形 DP 求解。令 $f_{u,0}$ 表示覆盖结点 $u$ 子树内所有结点所需的最少操作次数，$f_{u,1}$ 表示有且仅有一条从结点 $u$ 到其子树内某个叶结点的链，其上的所有结点均未被覆盖，而结点 $u$ 子树内其余结点均被覆盖所需的最少操作次数。

转移方程为：

$$\begin{cases}f_{u,0}=\min\left(2\cdot (sz_u-\max\limits_{v\in son_u}\left\{sz_v\right\})+\sum\limits_{v\in son_u}{f_{v,0}},\ 2\cdot sz_u+\min\limits_{v_1,v_2\in son_u,v_1\neq v_2}\left\{f_{v_1,1}+f_{v_2,1}+\sum\limits_{v\in son_u,v\neq v_1,v\neq v_2}{f_{v,0}}\right\}\right)\\f_{u,1}=\min\limits_{v\in son_u}\left\{f_{v,1}+\sum\limits_{v'\in son_u,v'\neq v}{f_{v',0}}\right\}\end{cases}$$

$f_{u,1}$ 的转移方程比较好理解，就是 $u$ 与某个子结点 $v$ 中未被覆盖的链合并成一条新的未被覆盖的链，其余子结点的子树均被完全覆盖。

$f_{u,0}$ 的转移需分为两种情况考虑，第一种情况是假设 $u$ 的所有子结点的子树均被完全覆盖，那么我们就需要选择 $u$ 的某个子结点 $v$，将 $v$ 中覆盖 $v$ 的路径拉长一截来覆盖 $u$，原本路径上深度最小的结点为 $v$，而现在路径上深度最小的结点变为了 $u$，那么这条路径的操作次数也就相应地增加了 $2\cdot (sz_u-sz_v)$；第二种情况是将 $u$ 与其某两个子结点 $v_1,v_2$ 中的两条未被覆盖的链合并成一条操作次数为 $2\cdot sz_u$ 的路径，其余子结点的子树均被完全覆盖。

实现时记录 $f_{v,0}$ 的和、$f_{v,1}-f_{v,0}$ 的最小值及次小值、以及 $sz_v$ 的最大值即可。

至此，我们便用 $O(n)$ 的时间复杂度解决了本题。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,x,tot,hd[200009],sz[200009],f[200009][2];
struct st{ll x,y;}eg[400009];
void addedge(ll u,ll v){eg[++ tot] = (st){v,hd[u]},hd[u] = tot;}
inline ll read(){
	ll s = 0,w = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0'){ if (ch == '-') w = -1; ch = getchar();}
	while (ch <= '9' && ch >= '0') s = (s << 1) + (s << 3) + (ch ^ 48),ch = getchar();
	return s * w;
}
void dfs(ll u,ll fa){
	sz[u] = 1;
	ll sum = 0,mx = 0,mn = 1e18,mn2 = 1e18;
	for (ll i = hd[u];i;i = eg[i].y){
		ll v = eg[i].x;
		if (v == fa) continue;
		dfs(v,u),sum += f[v][0],mx = max(mx,sz[v]),sz[u] += sz[v];
		ll qwq = f[v][1] - f[v][0];
		if (qwq <= mn) mn2 = mn,mn = qwq;
		else mn2 = min(mn2,qwq);
	}
	if (sz[u] == 1){f[u][0] = 2; return;}
	f[u][0] = 2 * sz[u] + sum,f[u][1] = sum + mn;
	if (mn2 < 1e18) f[u][0] += mn + mn2;
	f[u][0] = min(f[u][0],sum + 2 * (sz[u] - mx));
}
int main(){
	n = read();
	for (ll i = 2;i <= n;i += 1) x = read(),addedge(x,i),addedge(i,x);
	dfs(1,0),printf("%lld",f[1][0]);
	return 0;
}
```


---

## 作者：luogubot (赞：8)

给定一棵以 $1$ 为根的树，初始每个点都没被点亮，每个时刻可以改变一个点的点亮状态，需要让每个点 $u$ 都在某个时刻满足”有且仅有 $u$ 的子树被点亮“，最终所有点都没被点亮。求至少经过多少时刻。

$n\leq 2\times 10^5$。

转化一下题意：记 $sz_u$ 为 $u$ 子树大小。对于一条树边 $(u,fa_u)$，在新图 $G$ 上添加 $u,fa_u$ 之间权值为 $sz_{fa_u}-sz_u$ 的双向边；对于一个点 $u$，在 $G$ 上添加 $u$ 和新点 $S$ 之间权值为 $sz_u$ 的边。则原问题等价于找到一个边的多重集，满足：

- $1\sim n$ 中的每个点度数都 $>0$ 且为偶数。
- $1\sim n$ 连通。

如果满足这两个条件，就可以构造出一组 $S$ 出发的欧拉回路，其中 $S$ 表示没有任何点点亮的状态，$u$ 表示仅 $u$ 子树点亮的状态，则显然是充要条件。每条边只会被加入多重集 $0,1$ 或 $2$ 次，更多次显然是不优的。设计一个树形 dp $f_{u,0/1,0/1}$ 表示 $u$ 子树是否满足以下条件的最小花费：

- 根节点是否与 $S$ 连通。需要保证所有不与根节点连通的结点都与 $S$ 连通。
- 根节点的度数是否是奇数。

转移先考虑第一维。有 $f_{u,0,0}=0,f_{u,1,1}=w,f_{u,1,0}=2w$。其实是 $(u,S)$ 边的选择次数，所以 $w=sz_u$。

然后合并 $u$ 连通块和儿子 $v$ 子树，其中 $w$ 代表 $G$ 中 $(u,v)$ 的权值：

- $(u,v)$ 选 $0$ 次。$f_{u,i,j}+f_{v,1,0}\to f'_{u,i,j}$。
- $(u,v)$ 选 $1$ 次。$f_{u,i,j}+f_{v,i',1}+w\to f'_{u,i\operatorname{or} i',j\operatorname{xor} 1}$。
- $(u,v)$ 选 $2$ 次。$f_{u,i,j}+f_{v,i',0}+2w\to f'_{u,i\operatorname{or} i',j}$。

wow，居然 $O(n)$ 了。

---

## 作者：PersistentLife (赞：4)

### [【USACO23JAN_Pt T3】Subtree Activation](http://usaco.org/index.php?page=viewproblem2&cpid=1286)

[cnblogs](https://www.cnblogs.com/znstz2018/p/17087422.html)

令 $size(u)$ 表示 $u$ 的子树大小，考虑这样一个无向图：

- 点集为树的点集加上一个新的点，令其为点 $0$。
- 对于原树上的一条边 $(u,v)$，在图中加入一条 $(u,v)$ 的边，边权为 $|size(u)-size(v)|$。
- 对于原树上的所有点 $u$，在图中加入一条 $(0,u)$ 的边，边权为 $size(u)$。

这张图有一个很好的性质，对于两个点 $x,y$，从 $x$ 的子树被点亮到 $y$ 的子树被点亮，代价为新图中 $x,y$ 的最短路（若 $x,y$ 有祖先关系，则不断跳儿子或跳父亲。若没有祖先关系，则先从 $x$ 跳到 $0$，再从 $0$ 跳到 $y$，可以把 $0$ 感性理解成“熄灭操作”）。 

问题转化成了在这张图中选一些边（一条边可以被多次选择），满足将图联通且有欧拉回路。考虑树形 dp，令 $dp(u,0/1,0/1)$ 表示，在原树上 $u$ 的子树中，除了 $u$，都满足 $deg \bmod 2 = 0$ 且和节点 $0$ 联通，其中 $u$ 是否和 $0$ 联通，$deg_u \bmod 2$ 为什么的最小代价。

- 初始值根据 $(0,u)$ 这条边定：$dp(u,0,0)=0,dp(u,0,1)=\inf,dp(u,1,0)=2size(u),dp(u,1,1)=size(u)$。
- 转移不断合并子树，枚举合并前的两个 $0/1$ 和子树的两个 $0/1$，然后就可以确定父亲到儿子的边选不选（奇数次还是偶数次，是否 $\gt 0$）。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define se second
#define pii pair<long long,long long>
#define mp make_pair
#define pb push_back
const int mod=998244353;
const int inf=0x3f3f3f3f;
const int INF=1e18;
int n;
vector <int> g[200005];
vector <int> res;
int sz[200005],dp[200005][2][2];
void dfs0(int u)
{
	sz[u]=1;
	for(int i=0;i<g[u].size();i++) dfs0(g[u][i]),sz[u]+=sz[g[u][i]];
}
int tmp[2][2];
void dfs1(int u)
{
	dp[u][0][1]=INF,dp[u][1][0]=2*sz[u],dp[u][1][1]=sz[u];
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		dfs1(v);
		memset(tmp,0x3f,sizeof(tmp));
		for(int iu=0;iu<2;iu++) for(int ju=0;ju<2;ju++) for(int iv=0;iv<2;iv++) for(int jv=0;jv<2;jv++)
		{
			if(jv==0)
			{
				tmp[iu|iv][ju^jv]=min(tmp[iu|iv][ju],dp[u][iu][ju]+dp[v][iv][jv]+2*(sz[u]-sz[v]));
				if(iv) tmp[iu][ju]=min(tmp[iu][ju],dp[u][iu][ju]+dp[v][iv][jv]);
			} 
			else
			{
				tmp[iu|iv][ju^jv]=min(tmp[iu|iv][ju^1],dp[u][iu][ju]+dp[v][iv][jv]+(sz[u]-sz[v]));
			}
		} 
		for(int j=0;j<2;j++) for(int l=0;l<2;l++) dp[u][j][l]=tmp[j][l];
	}
}
void solve()
{
	scanf("%lld",&n);
	for(int i=2;i<=n;i++)
	{
		int u;
		scanf("%lld",&u);
		g[u].pb(i);
	}
	dfs0(1),dfs1(1);
	printf("%lld",dp[1][1][0]);
}
signed main()
{
	int _=1;
//	cin>>_;
	while(_--) solve();
	return 0;
}
```

---

## 作者：qczrz6v4nhp6u (赞：2)

感觉这种题目想到了转化就秒出做法，想不到转化就啥都憋不出来。

### Solution

设 $siz_x$ 为 $x$ 子树的点数。

考虑一个转化：建立新图 $G$，其中结点 $0$ 表示空状态，结点 $x$ 表示仅有 $x$ 的子树被激活的状态。

对于原图中的边 $(x,y)$，在 $G$ 中 $(x,y)$ 之间连两条权值为 $|siz_x-siz_y|$ 且方向相反的有向边；对于原图中的点 $x$，在 $G$ 中 $(0,x)$ 之间连两条权值为 $siz_x$ 且方向相反的有向边。
  
则答案对应 $G$ 的一个子图，满足其点集大小等于 $G$ 的点集大小，是一个欧拉图且边权和最小。

如果把 $0$ 删掉，将会剩下若干个连通块，其中每个连通块内 **恰好** 有 $2$ 条边满足一端是 $0$，另一端属于该连通块。考虑以这个作为树形 DP 的维度。

设计树形 DP：设 $f_{x,0/1/2}$ 表示以 $x$ 为根的子树，删掉 $0$ 后 $x$ 所在连通块有 $0/1/2$ 条边满足一端是 $0$，另一端属于该连通块的最小花费。状态有限制条件：对于第二维是 $0/1$ 的状态，路径以 $x$ 结尾；除 $x$ 所在连通块均 **恰好** 有 $2$ 条边满足一端是 $0$，另一端属于该连通块。

初始状态是 $f_{x,0}=0,f_{x,1}=siz_x,f_{x,2}=2\times siz_x$。

设 $y$ 是 $x$ 的其中一个儿子，$z=siz_x-siz_y$，则有转移：

$$\begin{aligned}
f'_{x,0}&\gets \min(f_{x,0}+f_{y,0}+2z,f_{x,0}+f_{y,2})\\
f'_{x,1}&\gets \min(f_{x,1}+f_{y,0}+2z,f_{x,0}+f_{y,1}+z,f_{x,1}+f_{y,2})\\
f'_{x,2}&\gets \min(f_{x,0}+f_{y,2}+2z,f_{x,2}+f_{y,0}+2z,f_{x,1}+f_{y,1}+z,f_{x,2}+f_{y,2})
\end{aligned}$$

时间复杂度 $O(n)$。

### Code

```cpp
constexpr int N=2e5+5,INF=1e9;
int n,siz[N];
ll f[N][3];
std::vector<int> Gr[N];
void dfs(int x){
	siz[x]=1;
	for(auto &y:Gr[x])
		dfs(y),siz[x]+=siz[y];
	f[x][0]=0,f[x][1]=siz[x],f[x][2]=siz[x]<<1;
	for(auto &y:Gr[x]){
		int z=siz[x]-siz[y];
		f[x][2]=min(f[x][2]+f[y][0]+(z<<1),f[x][0]+f[y][2]+(z<<1),f[x][1]+f[y][1]+z,f[x][2]+f[y][2]);
		f[x][1]=min(f[x][1]+f[y][0]+(z<<1),f[x][0]+f[y][1]+z,f[x][1]+f[y][2]);
		f[x][0]=min(f[x][0]+f[y][0]+(z<<1),f[x][0]+f[y][2]);
	}
}
int main(){
	read(n);
	for(int i=2,f;i<=n;i++){
		read(f);
		Gr[f].emplace_back(i);
	}
	dfs(1);
	writeln(f[1][2]);
	return 0;
}
```

---

## 作者：henryhu2006 (赞：2)

### 题意

给定一个根节点为 $1$ 的树，一开始所有节点全部关闭。你每次可以激活一个关闭的点或将一个激活的点关闭。**要求最后所有节点都是关闭的。**

要求求出最短的操作序列长度，使得对于每个 $i$，都存在一个时刻，满足被激活的点的集合恰好为以 $i$ 为根的子树。

$n\le 2\times 10^5$。

### 观察

首先挖掘一些性质：

1. 对于任何一次操作，其必然处在从一个子树 $u$ 调整到另一个子树 $v$ 的过程中，不会有任何多余的操作。
2. 如果**在操作序列中相邻**（即 $u$ 完成任务后 $v$ 完成任务）的两个子树 $u$ 和 $v$ 不存在祖孙关系（即 $u$ 不是 $v$ 的祖先且 $v$ 不是 $u$ 的祖先），显然将 $u$ 子树删空，然后将 $v$ 子树从空集开始加入不劣。
3. 将操作序列删成空集的位置断开，可以得到若干操作序列段。
4. 对于同一个操作序列段中相邻的子树 $u,v$，根据性质二，$u,v$ 一定存在祖孙关系，如果 $u,v$ 不是父子节点关系，那么将 $u,v$ 中间的过渡节点全部加入序列不劣。
5. 如果一段操作序列的子树第一个是 $u$，最后一个是 $v$，那么 $u,v$ 路径上的点可以全部加入。
6. 对于 $u,v$ 路径上的旁系分叉，一定不优。**例如**对于 $u\to \text{lca}(u,v)\to \text{lca}(x,v)\to x\to \text{lca}(x,v)\to v$ 的一条典型路径，原来的代价为 $2sz(\text{lca}(u,v))+2sz(\text{lca}(v,x))-2sz(x)$。设 $\text{lca}(v,x)$ 子节点中包含 $v$ 的是 $v'$，包含 $x$ 的是 $x'$，如果选择 $u\to x,v\to v'$，那么代价为 $2sz(\text{lca}(u,v))+2sz(v')\le 2sz(\text{lca}(u,v))+2sz(\text{lca}(v,x))-2sz(x)$。
7. 去掉了旁系分叉，此时路径为 $u\to v$ 的路径，**加上 $\text{lca}(u,v)$ 以上若干长度的延伸**，类似一个人字形。
8. 如果一个节点被来自父节点方向的路径覆盖，显然不需要将这个节点作为其他路径的 $\text{lca}$ 或者人字形的顶。因为将跨越这个节点的路径调整到两个子树内，分成两个路径，答案不劣。类似的，对于被人字形顶部覆盖的节点，不需要其他路径延申出来覆盖。

### 解法

于是设计 DP：
- $f(u)$ 表示没有父节点的路径进入子树 $u$，子树 $u$ 的最小代价。
- $g(u)$ 表示有一条来自父节点的路径进入子树 $u$，子树 $u$ 的最小代价。
- $h(u)$ 表示 $u$ 处在人字形顶部，子树 $u$ 的最小代价。

边界：对于叶节点，$f(u)=2,g(u)=h(u)=0$。

- 设 $u$ 的子节点中，$f(v)-g(v)$ 最大的两个**值**是 $m_1,m_2$，如果不存在，则设为 $0$。
- 设 $f(v)-h(v)$ 最大的**值**是 $m_3$。
- 设 $w=\sum_{v} f(v)$。

对于 $f(u)$，必然需要覆盖 $u$，由于没有来自父节点的链，所以必然要付出 $2sz(u)$ 的代价，使得 $u$ 可以作为一条路径的人字形顶。可以选择在 $u$ 处直接分叉，或者将某个子树纳入人字形顶部，显然优先选择 $f(v)-g(v)$ 或者 $f(v)-h(v)$ 最大的节点替代。因此有：

$$
f(u)=w+sz(u)-\max(m_1+m_2,m_3)
$$

对于 $g(u)$，只能选择一个子树继承，因此有：

$$
g(u)=w-m_1
$$

对于 $h(u)$，可以选择在 $u$ 处分叉或传递给一个子树，因此有：

$$
h(u)=w-\max(m_1+m_2,m_3)
$$

于是就可以转移了，最后答案为 $f(1)$，时间复杂度 $\mathcal O(n)$。

由于题目的输入满足 $p_i<i$，所以只要循环就可以了。代码很短。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int n,p[N],sz[N];
ll f[N],g[N],h[N];
vector<int> e[N];
int main(){
	cin>>n;
	for(int i=2;i<=n;++i) scanf("%d",p+i);
	for(int i=n;i;--i){
		e[p[i]].emplace_back(i);
		++sz[i],sz[p[i]]+=sz[i];
		ll m1=0,m2=0,m3=0;
		for(int v:e[i]){
			int val=f[v]-g[v]; f[i]+=f[v];
			if(val>m1) m2=m1,m1=val;
			else if(val>m2) m2=val;
			m3=max(m3,f[v]-h[v]);
		}
		g[i]=f[i]-m1;
		h[i]=f[i]-max(m3,m1+m2);
		f[i]=f[i]+sz[i]-max(m1+m2,m3);
	}
	cout<<f[1]*2;
	return 0;
}
```

---

## 作者：Felix72 (赞：1)

这个题的第一个难点在于自由度很高，操作方式是任意的，因此我们需要来点限制以此达到形式化的目的。如果现有一节点 $p$ 满足有且只有 $p$ 内的节点有标记，接下来要做的不外乎这些：

- 整体标记 $fa_p$；
- 整体标记 $son_p$ 集合的其中一个元素；
- 把 $p$ 清空。

当没有标记时，接下来要做的一定是：

- 整体标记某个 $p$。

整体标记的意思是对某个节点 $p$ 使得有且只有它的子树内有标记。

那么问题变成了特殊图的最短哈密顿回路，这个可以 DP。设 $f_{pos, dg, c}$ 表示 $pos$ 节点的所有后代都合法，自己现在的度数奇偶性是 $dg$，与无标记状态的联通情况是 $c$ 时的最小代价。用树形背包的方式转移。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 200010;
int n, fa[N], f[N][2][2], siz[N]; vector < int > tr[N];
inline void init(int now)
{siz[now] = 1; for(int to : tr[now]) init(to), siz[now] += siz[to];}
inline void treedp(int now)
{
	f[now][0][0] = 0;
	for(int to : tr[now])
	{
		treedp(to); int tmp[2][2];
		memset(tmp, 0x3f, sizeof(tmp));
		for(int now_dg = 0; now_dg <= 1; ++now_dg)
		{
			for(int now_c = 0; now_c <= 1; ++now_c)
			{
				for(int to_dg = 0; to_dg <= 1; ++to_dg)
				{
					for(int to_c = 0; to_c <= 1; ++to_c)
					{
						if(to_dg == 0)
						{
							tmp[now_dg][now_c | to_c] = min(tmp[now_dg][now_c | to_c], f[now][now_dg][now_c] + f[to][to_dg][to_c] + (siz[now] - siz[to]) * 2);
							if(!to_c) continue;
							tmp[now_dg][now_c] = min(tmp[now_dg][now_c], f[now][now_dg][now_c] + f[to][to_dg][to_c]);
						}
						else
						{
							tmp[now_dg ^ 1][now_c | to_c] = min(tmp[now_dg ^ 1][now_c | to_c], f[now][now_dg][now_c] + f[to][to_dg][to_c] + (siz[now] - siz[to]));
						}
					}
				}
			}
		}
		for(int now_dg = 0; now_dg <= 1; ++now_dg)
			for(int now_c = 0; now_c <= 1; ++now_c)
				f[now][now_dg][now_c] = tmp[now_dg][now_c];
//		cerr << "-> " << now << " " << to << " : " << f[now][0][0] << " " << f[now][0][1] << " " << f[now][1][0] << " " << f[now][1][1] << '\n';
	}
	int tmp[2] = {(int)1e9, (int)1e9};
	for(int now_dg = 0; now_dg <= 1; ++now_dg)
		for(int now_c = 0; now_c <= 1; ++now_c)
			for(int ex = 1; ex <= 2; ++ex)
				tmp[(now_dg + ex) % 2] = min(tmp[(now_dg + ex) % 2], f[now][now_dg][now_c] + siz[now] * ex);
	for(int now_dg = 0; now_dg <= 1; ++now_dg) f[now][now_dg][1] = min(f[now][now_dg][1], tmp[now_dg]);
//	cerr << now << " : " << f[now][0][0] << " " << f[now][0][1] << " " << f[now][1][0] << " " << f[now][1][1] << '\n';
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.err", "w", stderr);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 2; i <= n; ++i) cin >> fa[i], tr[fa[i]].push_back(i);
	memset(f, 0x3f, sizeof(f));
	init(1), treedp(1); cout << f[1][0][1] << '\n';
	return 0;
}
/*
8
1 2 1 1 5 3 4
*/
```

---

## 作者：Add_Catalyst (赞：0)

# P9021 [USACO23JAN] Subtree Activation P 题解

------

## 知识点

树形 DP。

## 分析

### 转化

首先我们可以想到直接在树上进行移动覆盖，最优答案就是覆盖所有节点的最小花费。

我们设初始状态为 $0$ 节点，从 $0$ 节点移动到任意节点 $u(u>0)$ 花费都是 $siz_u$。

当我们现在的状态满足都为 $u(u>0)$ 的子树，我们有以下三种选择：

1. 移动到 $0$ 节点，花费 $siz_u$。
2. 移动到父节点 $fa_u$，花费 $siz_{fa_u}-siz_u$。
3. 移动到子节点 $v$，花费 $siz_u-siz_v$。

我们发现，最优的方式就是在树上一条简单路径覆盖过去，直到每个点都被覆盖过，列式发现这样可以避免一些重复。那么每次花费为 $2\max_{u}{siz_u}$，其中 $u$ 是路径上的点。

问题转化为**树上最小路径覆盖问题**。

### DP

此时我们就可以来做树形 DP 了：

- 设 $f_{u,0}$ 表示当 $u$ 的子树全部被覆盖过了的最小花费。
- 设 $f_{u,1}$ 表示当 $u$ 的子树中除了 $u$ 到某个叶节点的路径其余全部被覆盖过的最小花费。

那么有转移：

0. $f_{u,0}$ 的转移有两种，取其中较小值：

   - 子树中选一条经过 $u$ 的链，把它覆盖了，其余都是已经覆盖过的：
     $$
     \sum_{v\in Son_{u}} f_{v,0}
     + \min_{x\in Son_{u}} (f_{x,1}-f_{x,0})
     + \min_{y\in Son_{u},x\neq y} (f_{y,1}-f_{y,0})
     + 2siz_u \\
     $$

   - 找一条经过子节点 $v$ 的链，把它延长到 $u$：（这样可能会把它弄得不是链，但是不影响最终的答案）
     $$
     \sum_{v\in Son_{u}} f_{v,0} + 2(siz_u - \max_{v\in Son_u}siz_v) \\
     $$

1. $f_{u,1}$ 的转移十分简单，直接从子节点连接过来即可：
   $$
   \min_{x\in Son_u} f_{x,1} + \sum_{y\in Son_{u},x\neq y} f_{y,0} \\
   $$

复杂度 $O(n)$。

```cpp
//#define Plus_Cat ""
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define ll long long
#define RCL(a,b,c,d) memset(a,b,sizeof(c)*(d))
#define FOR(i,a,b) for(int i(a);i<=(int)(b);++i)
#define DOR(i,a,b) for(int i(a);i>=(int)(b);--i)
#define tomax(a,...) ((a)=max({(a),__VA_ARGS__}))
#define tomin(a,...) ((a)=min({(a),__VA_ARGS__}))
#define EDGE(g,i,x,y) for(int i=(g).h[(x)],y=(g)[(i)].v;~i;y=(g)[(i=(g)[i].nxt)>0?i:0].v)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);return Main();}signed Main
using namespace std;
constexpr int N(2e5+10);

namespace IOEcat {
    //...
} using namespace IOEcat;

int n,ans(INF);
int siz[N];
int f[N][2];
vector<int> g[N];

void dfs(int u,int fa) {
	siz[u]=1;
	int sum(0),mn(0),mn2(0),mx(-INF);
	for(const int &v:g[u]) {
		dfs(v,u),siz[u]+=siz[v],tomax(mx,siz[v]),sum+=f[v][0];
		if(f[v][1]-f[v][0]<mn)mn2=mn,mn=f[v][1]-f[v][0];
		else tomin(mn2,f[v][1]-f[v][0]);
	}
	if(siz[u]==1)return f[u][0]=2,void();
	f[u][0]=min((siz[u]<<1)+sum+mn+mn2,sum+((siz[u]-mx)<<1)),f[u][1]=sum+mn;
}

signed main() {
#ifdef Plus_Cat
	freopen(Plus_Cat ".in","r",stdin),freopen(Plus_Cat ".out","w",stdout);
#endif
	I(n);
	FOR(i,2,n) {
		int fa;
		I(fa),g[fa].push_back(i);
	}
	dfs(1,0),O(f[1][0],'\n');
	return 0;
}
```

------

---

## 作者：Laoshan_PLUS (赞：0)

## [[USACO23JAN] Subtree Activation P](https://www.luogu.com.cn/problem/P9021)

这种问题一看满足条件就知道，一般不用想着怎么模拟题意。考虑转化问题。

假如节点 $u$ 满足了条件一，也就是仅有子树节点全部开启。那么我们把转化具象为：

- 进行 $\text{siz}_u$ 次操作直接清空；
- 进行 $\text{siz}_{\text{fa}(u)}-\text{siz}_u$ 次操作使 $\text{fa}(u)$ 满足条件一；
- 对于任意 $v\in\text{son}_u$，进行 $\text{siz}_u-\text{siz}_v$ 次操作使 $v$ 满足条件一；

发现我们关注的条件只有：

1. 清空状态和全满状态的转化；
2. 两棵子树之间的转化。

于是考虑转化问题为：建新图，对于原图中任意的 $(u,\text{fa}(u))$ 的边，添加两条 $\{u,\text{fa}(u),\text{siz}_{\text{fa}(u)}-\text{siz}_u\}$ 的双向边。然后对于任意一点 $u$，添加两条 $\{0,u,\text{siz}_u\}$ 的双向边。然后问题转化为在新图找一个**点数为原图点数且边权最小的欧拉子图**。

这个欧拉子图找出来之后，我们发现：若删去 $0$ 点，则这个欧拉子图形成了若干连通块，每个连通块都**恰好**有 $2$ 条边与 $0$ 点相连。

然后设计 DP 方程为：设 $f_{u,0/1/2}$ 表示以 $u$ 为根的子树，删掉 $0$ 后有 $0/1/2$ 条边满足一端是 $0$、另一端属于这个子树的最小花费。初始状态 $f_{u,0}=0$，$f_{u,1}=\text{siz}_u$，$f_{u,2}=2\,\text{siz}_u$。

注意方程第二维为 $0/1$ 的情况，可以<u>类比</u>为当前点是连通块的一端；对于 $2$ 的情况，则就是上文说的恰好 $2$ 条边和 $0$ 相连的情况。

令 $v\in\text{son}_u$，$w=\text{siz}_u-\text{siz}_v$。有转移：

$$
f_{u,0}\gets\min(f_{u,0}+f_{v,0}+2w,f_{u,0}+f_{v,2})
$$

可以理解为要么 $v$ 要转移到 $u$，这两个状态转移需要 $2w$ 的花费；要么 $v$ 已经是一个欧拉图，把 $u$ 接入 $v$ 的花费。

$$
\begin{matrix}
f_{u,1}\gets\min(f_{u,1}+f_{v,0}+2w,f_{u,0}+f_{v,1}+w,f_{u,1}+f_{v,2})\\[1ex]
f_{u,2}\gets\min(f_{u,0}+f_{v,2}+2w,f_{u,2}+f_{v,0}+2w,f_{u,1}+f_{v,1}+w,f_{u,2}+f_{v,2})
\end{matrix}
$$

和上面是同理的。

最后答案就是 $f_{1,2}$。复杂度做到了 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
using namespace std;

char buf[1<<20],*p1=buf,*p2=buf;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))ch=='-'&&(f=-1),ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
constexpr int MAXN=2e5+5;
int n,head[MAXN],tot;
struct{
	int v,to;
}e[MAXN];
void addedge(int u,int v){
	e[++tot]={v,head[u]};
	head[u]=tot;
}
int siz[MAXN],f[MAXN][3];
void dfs(int u){
	siz[u]=1;
	for(int i=head[u];i;i=e[i].to) dfs(e[i].v),siz[u]+=siz[e[i].v];
	f[u][0]=0,f[u][1]=siz[u],f[u][2]=siz[u]<<1;
	for(int i=head[u],v,w,t0,t1,t2;i;i=e[i].to){
		v=e[i].v,w=siz[u]-siz[v];
		t0=min(f[u][0]+f[v][0]+2*w,f[u][0]+f[v][2]);
		t1=min({f[u][1]+f[v][0]+2*w,f[u][0]+f[v][1]+w,f[u][1]+f[v][2]});
		t2=min({f[u][2]+f[v][0]+2*w,f[u][0]+f[v][2]+2*w,f[u][1]+f[v][1]+w,f[u][2]+f[v][2]});
		f[u][0]=t0,f[u][1]=t1,f[u][2]=t2;
	}
}

int main(){
	n=read();
	for(int i=2;i<=n;++i) addedge(read(),i);
	dfs(1);
	printf("%d\n",f[1][2]);
	return 0;
}
```

---

## 作者：Leasier (赞：0)

如果任意一组操作次数 $\leq O(n \log n)$ 的方案都可以得分，则我们可以按 DSU on Tree 的操作方式给出一组合法方案。

~~可惜交上去[一分没有](https://loj.ac/s/2004523) /ng~~

------------

直接思考构造方式是没有出路的，考虑一组最优方案中 activate 序列的性质。设之为 $p_1, p_2, \cdots, p_n$。

- **相邻操作次数**：若 $p_i, p_{i + 1}$ 无祖先后代关系，则从 $i$ 到 $i + 1$ 的操作次数为 $size_{p_i} + size_{p_{i + 1}}$；否则，操作次数为 $|size_{p_i} - size_{p_{i + 1}}|$。

由此，我们尝试给出哪些 $p$ 一定不优。

- **祖先后代链**：若 $p_i, p_{i + 1}$ 有祖先后代关系（不妨设 $p_i$ 为 $p_{i + 1}$ 的祖先），则 $fa_{p_{i + 1}} = p_i$ 不劣。

证明：若不然，将 $p_i \to p_{i + 1}$ 路径上的点插入 $p_i, p_{i + 1}$ 间，这样显然不劣。

自然地，想到我们可以将 $p$ 分段，使得段内相邻点有祖先后代关系，而段间无。

- **路径形态**：每段只可能是祖先 $-$ 后代的直链（$\mathcal{P}$）或 $u - \operatorname{lca}(u, v) - v$ 的两段直链拼接（$\mathcal{Q}$）。

证明：由相邻点有祖先后代关系不难归纳。

- **路径端点**：若 $\mathcal{P}$，则后代为一个叶子；若 $\mathcal{Q}$，则 $u, v$ 均为叶子。
- **路径对答案的贡献**：路径上最浅点 $size$ 乘 $2$。

于是考虑 dp，设 $f_u$ 表示 $u$ 为一条祖先 $-$ 后代直链上端时 $u$ 子树内的答案，$g_u$ 表示 $u$ 为某个 $\operatorname{lca}(u, v)$ 时 $u$ 子树内的答案，$h_u$ 表示 $u$ 子树内的答案。

转移略去，唯一需要注意的地方是我们可以既不继承儿子的直链，也不为某个 $\operatorname{lca}(u, v)$，而是选择一个 $size$ 最大的儿子，在其 deactivate 前插入 $u$ 子树中其他部分并达成 $u$ 的目标。

~~如果不注意这一点会 [WA 33pts](https://loj.ac/s/2004539)。~~

时间复杂度为 $O(n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt = 0;
int head[200007], size[200007];
ll dp1[200007], dp2[200007], dp3[200007];
Edge edge[200007];

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

inline int max(int a, int b){
	return a > b ? a : b;
}

inline ll min(ll a, ll b){
	return a < b ? a : b;
}

void dfs(int u){
	size[u] = 1;
	if (head[u] == 0){
		dp1[u] = dp3[u] = 2;
		dp2[u] = 0x7fffffffffffffffll;
		return;
	}
	if (edge[head[u]].nxt == 0){
		int x = edge[head[u]].end;
		dfs(x);
		size[u] += size[x];
		dp1[u] = dp1[x] + 2;
		dp2[u] = 0x7fffffffffffffffll;
		dp3[u] = dp3[x] + 2;
		return;
	}
	int max_size = 0;
	ll sum = 0, min_val = 0x7fffffffffffffffll, cmin_val = 0x7fffffffffffffffll;
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		ll y, z;
		dfs(x);
		size[u] += size[x];
		max_size = max(max_size, size[x]);
		y = dp3[x];
		sum += y;
		z = -y + dp1[x] - size[x] * 2;
		if (min_val > z){
			cmin_val = min_val;
			min_val = z;
		} else if (cmin_val > z){
			cmin_val = z;
		}
		dp3[u] += dp3[x];
	}
	dp1[u] = sum + min_val + size[u] * 2;
	dp2[u] = dp1[u] + cmin_val;
	dp3[u] = min(dp3[u] + (size[u] - max_size) * 2, min(dp1[u], dp2[u]));
}

int main(){
	int n;
	ll ans = 0;
	scanf("%d", &n);
	for (int i = 2; i <= n; i++){
		int p;
		scanf("%d", &p);
		add_edge(p, i);
	}
	dfs(1);
	printf("%lld", dp3[1]);
	return 0;
}
```

---

## 作者：_ZSR_ (赞：0)

### [P9021 [USACO23JAN] Subtree Activation P](https://www.luogu.com.cn/problem/P9021)

考虑建一个新图出来。新图中包含原图的所有点以及一个超级原点 $S$。对于原图中的点 $u$，我们将它在新图中对应的点和超级原点连边，边权为 $size_{u}$。对于原图中直接相连的两个点 $u,v$，我们将它们两个在新图中对应的点连边，边权为 $size_{u}-size_{v}$。问题就可以转化成在新图中选择一些边，一条边可以选择多次，求出满足选择的所有边构成了欧拉回路的最小边权和。

这样为什么是对的呢？首先考虑从没有点亮任何节点的状态变为点亮了以 $u$ 为根的子树的状态，代价就是 $S$ 到 $u'$ 的边权，其中 $u'$ 表示 $u$ 在新图中对应的节点，下文同。然后考虑从点亮 $u$ 的子树到点亮 $v$ 的子树。这里有两种情况，如果 $u$ 是 $v$ 的祖先，那么就是 $v'$ 不断沿着 $v$ 的父亲走到 $u'$ 的路径长度；如果 $u$ 不是 $v$ 的祖先，那么显然就只能先把 $u$ 整个熄灭，然后再打开 $v$，也就是 $u'$ 到 $S$ 再到 $v'$。至此，所有的可能的操作便可以在新图中表示出来。

那么怎么求最小的边权和呢？考虑在原图上做树形 $dp$。令 $dp_{i,0/1,0/1}$ 表示节点 $i$ 是否和 $S$ 连通，节点 $i$ 的度数模 $2$ 的余数是多少的情况下的最小边权和。初始状态可以根据 $S$ 到 $i'$ 的这条边确定。最后的答案就是 $dp_{1,1,0}$。时间复杂度 $O(n)$。

code
```
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10,INF=0x3f3f3f3f;
int n;
int h[N],to[N],nxt[N],idx;
int size[N];
int f[N][2][2],g[2][2];
inline void add(int a,int b)
{
    to[++idx]=b;
    nxt[idx]=h[a];
    h[a]=idx;
}
void dfs1(int u)
{
    size[u]=1;
    for (int i=h[u];i;i=nxt[i])
    {
        int v=to[i];
        dfs1(v);
        size[u]+=size[v];
    }
}
void dfs2(int u)
{
    f[u][0][1]=INF,f[u][1][0]=2*size[u],f[u][1][1]=size[u];
    for (int i=h[u];i;i=nxt[i])
    {
        int v=to[i];
        dfs2(v);
        memset(g,0x3f,sizeof g);
        for (int cu=0;cu<2;++cu)
        {
            for (int mu=0;mu<2;++mu)
            {
                for (int cv=0;cv<2;++cv)
                {
                    for (int mv=0;mv<2;++mv)
                    {
                        if (mv==0)
                        {
                            g[cu|cv][mu^mv]=min(g[cu|cv][mu^mv],f[u][cu][mu]+f[v][cv][mv]+2*(size[u]-size[v]));
                            if (cv) g[cu][mu]=min(g[cu][mu],f[u][cu][mu]+f[v][cv][mv]);
                        }
                        else g[cu|cv][mu^mv]=min(g[cu|cv][mu^mv],f[u][cu][mu]+f[v][cv][mv]+(size[u]-size[v]));
                    }
                }
            }
        }
        for (int cu=0;cu<2;++cu)
        {
            for (int mu=0;mu<2;++mu)
            {
                f[u][cu][mu]=g[cu][mu];
            }
        }
    }
}
int main()
{
    scanf("%d",&n);
    for (int i=2,j;i<=n;++i)
    {
        scanf("%d",&j);
        add(j,i);
    }
    dfs1(1);
    dfs2(1);
    printf("%d\n",f[1][1][0]);
    return 0;
}
```


---

