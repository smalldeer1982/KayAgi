# [ARC179D] Portable Gate

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc179/tasks/arc179_d

頂点 $ 1,2,\dots\ ,N $ の $ N $ 頂点からなる木が与えられます. $ i $ 番目の辺は頂点 $ u_i,v_i $ を双方向に結んでいます.

すべての頂点ははじめ白に塗られています.

この木のすべての頂点を効率よく訪れるべく, Alice は不思議なゲートを発明しました. Alice は駒とゲートを $ 1 $ 個ずつ用いて次の手順で旅をします.

まず好きな頂点を選び, 駒とゲートをその頂点に置きます. その後, すべての頂点が黒に塗られるまで次の操作を何度も行います.

- 次のうち $ 1 $ つを選んで実行する.
  1. 駒が置かれている頂点を黒に塗る.
  2. 駒が置かれている頂点に隣接した頂点をひとつ選び, その頂点に駒を移動させる, コストが $ 1 $ かかる.
  3. ゲートが置かれている頂点に駒を移動させる.
  4. 駒が置かれている頂点にゲートを移動させる.
 
コストがかかるのは $ 2 $ 番目の操作のみであることに注意してください.

有限回の操作ですべての頂点を黒に塗ることができることが証明できます. かかるコストの合計の最小値を求めてください.

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ u_i,v_i\ \leq\ N $
- 与えられるグラフは木である.
- 入力される値はすべて整数.
 
### Sample Explanation 1

Alice の手順の一例を示します. 駒が頂点 $ u $ にありゲートが頂点 $ v $ にある状態を $ (u,v) $ と表すことにします. - 頂点 $ 4 $ に駒とゲートを置く. - 状態は $ (4,4) $ となる. - 操作 $ 1 $ を行う. - 頂点 $ 4 $ が黒く塗られる. - 状態は $ (4,4) $ となる. - 操作 $ 2 $ を行い, 駒を頂点 $ 1 $ に移動させる. - コストが $ 1 $ かかる. - 状態は $ (1,4) $ となる. - 操作 $ 1 $ を行う. - 頂点 $ 1 $ が黒く塗られる. - 操作 $ 4 $ を行う. - 状態は $ (1,1) $ となる. - 操作 $ 2 $ を行い, 駒を頂点 $ 2 $ に移動させる. - コストが $ 1 $ かかる. - 状態は $ (2,1) $ となる. - 操作 $ 1 $ を行う. - 頂点 $ 2 $ が黒く塗られる. - 操作 $ 3 $ を行う. - 状態は $ (1,1) $ となる. - 操作 $ 2 $ を行い, 駒を頂点 $ 3 $ に移動させる. - コストが $ 1 $ かかる. - 状態は $ (3,1) $ となる. - 操作 $ 1 $ を行う. - 頂点 $ 3 $ が黒く塗られる. - すべての頂点が黒く塗られたので, 操作を終了する. 操作 $ 2 $ を行った回数は $ 3 $ なので, かかるコストの合計は $ 3 $ となります. $ 3 $ より小さいコストの手順は存在しません.

## 样例 #1

### 输入

```
4
1 2
1 3
1 4```

### 输出

```
3```

## 样例 #2

### 输入

```
10
1 7
7 10
10 8
8 3
8 4
10 9
9 6
9 5
7 2```

### 输出

```
10```

# 题解

## 作者：Eraine (赞：6)

编号：AT_arc179_d

难度：*2627（$\texttt{Clist}$ 数据）

tag：贪心，换根 dp

首先傻子都知道按照 dfn 序遍历绝对是最优的。

由于是按照 dfn 序遍历，所以每次回退的时候就把门放到哪。这步可以保证门所在的节点一定是当前棋子所在节点的祖先。

这个性质很重要，由这个性质可以推得每棵子树相互独立。假定根（即最开始访问的节点）已经确定，那么就可以求得每棵子树的答案然后在根节点合并。

对于不同的根，只有父节点对应的子树需要重新处理。很显然换根 dp。

先考虑根固定的情况。由于结束的位置可以不用在根，所以我们对于每个子树要处理两个信息：$f$ 表示遍历完该子树不用返回的最小代价，$g$ 表示遍历完该子树需要返回子树的根的代价。

$$f_u=\min_{v_0\in son_u}(\min(f_{v_0}+1,2\times size_{v_0}-(maxdep_{v_0}+1))+\sum_{v\in son_u,v\neq v_0}\min(g_v+2,2\times size_v-(maxdep_v+1)))$$

$$g_u=\sum_{v\in son_u}\min(g_v+2,2\times size_v-(maxdep_v+1))$$

这里假设叶节点的 $maxdep$ 为 $0$。

除了维护每个子树的 $f,g$ 还要多维护两个信息 $size$ 和 $dep$。

运用一下换根 dp 的常见套路，将 $f_u$ 的式子稍微转换可以将转移复杂度 $\Theta(k^2)$ 优化为 $\Theta(k)$。其中 $k$ 是儿子个数：

$$f_u=\sum_{v\in son_u}\min(g_v+2,2\times size_v-(maxdep_v+1))+\min_{v\in son_u}(\min(f_v+1,2\times size_v-(maxdep_v+1))-\min(g_v+2,2\times size_v-(maxdep_v+1)))$$

前面一坨可以用 $g_u$ 代替，再转换一下：

$$f_u=g_u+\min_{v\in son_u}(\min(f_v+1,2\times size_v-(maxdep_v+1))-\min(g_v+2,2\times size_v-(maxdep_v+1)))$$

换根转移父节点的四个信息时，$size$ 直接用 $n-sz_v$ 即可；$maxdep$ 需要处理出最大值和次大值；$g$ 用 $g_u$ 减去 $g_v$ 所造成的贡献再加上 $g_{fa}$ 的贡献；$f$ 只需加上 $g$ 并处理出最大值和次大值即可。

实现有些史，娱乐一下就好。

$\Theta(n)$。

[submission](https://atcoder.jp/contests/arc179/submissions/54269236)

若有疑问和错误请指出，虚心接受您的意见。

upd：2024.6.7 12:56 更改了部分公式错误

---

## 作者：快乐的大童 (赞：6)

### 题意简述
有一棵树 $n$ 个点，你有一个门，你现在从一个你选定的点开始走，目标是所有点都至少访问一次。每次你可以选择：

- 经过一条树边走到相邻点，花费 $1$。
- 将门放在当前点。
- 将自己传送到门所在的点。

求最小花费。$n\le 2\times10^5$。
### 分析
先考虑根（出发点）固定怎么做。

由于放门没有任何代价，我们可以视为在正常行走时随身把门也带上。正常情况下我们肯定是访问完一个子树后进入另一个子树继续访问，而显然门的位置一定在子树的祖先上，所以子树之间的花费相互独立。

再发现一个比较重要的性质：一个子树内若门在子树祖先上，则传送技能仅会使用至多一次。

证明：若使用两次以上，证明该点和门点之间的边要走两遍，那么我们将门放在该点上，该点和门点之间的边也要走两遍，但遍历该子树的代价不会变劣。

由此考虑树形 dp，设 $f_{i,0/1}$ 表示走完 $i$ 子树内的所有点，是否需要返回根节点的最小花费（注意原题中也无需返回出发点），转移：

- 令 $g_u$ 表示 $u$ 子树中离 $u$ 距离最远的点的距离。
- 令 $t_u=2\cdot(siz_u-1)-g_u$，表示在走 $u$ 子树时门在 $u$ 的祖先上时走完 $u$ 子树且不返回根节点的最小花费，$2\cdot(siz_u-1)$ 表示走完 $u$ 子树且返回根节点的最小花费，若不返回根节点，肯定要尽可能的少走，我们贪心的选离 $u$ 和离其最远的点这条链少走一遍，则减掉 $g_u$。
- $f_{x,1}=\sum_{u\in x}\min(f_{u,1}+2,t_u+1)$，表示对于 $x$ 的每个子树 $u$，遍历 $u$ 子树可以选择把门给 $u$，然后该边（指 $u$ 和 $x$ 之间的边，下同）一进一出花费 $2$，即 $f_{u,1}+2$；也可以在该子树内选择使用传送技能，则门留在 $x$，无需返回 $u$，且该边一进不出花费 $1$，即 $t_u+1$。
- $f_{x,0}=f_{x,1}+\min_{u\in x}(\min(f_{u,0}+1,t_u+1)-\min(f_{u,1}+2,t_u+1))$，由于不回根节点，肯定终点会落在恰好一个子树内，则该子树无需返回根节点，其他子树需要返回根节点，考虑枚举这个子树，则在回根节点的基础上，减掉原来的贡献，加上新的贡献，即，可以选择把门留下（花费仍是 $t_u+1$），也可以把门给 $u$，该边一进不出花费 $1$，即 $f_{u,0}+1$。

再考虑根不固定的情况，有了树形 dp 式子，直接换根即可。

简述换根流程：

- 计算以该点为根时的答案。
- 枚举子树，删掉子树的贡献（若是取最值可以同时保留次值，若最值是该子树贡献的则减掉最值加上次值），递归进子树。
### 代码
注意代码中的 $t_x$ 和题解中的 $t_x$ 定义有略微不同。

[https://atcoder.jp/contests/arc179/submissions/54430907](https://atcoder.jp/contests/arc179/submissions/54430907)

upd on 2024-11-12：修改了两处笔误。

upd on 2024-11-12：第一次修改又改出一个错误。我是什么唐诗 /ll

---

## 作者：UniGravity (赞：4)

根据套路，显然这题是树形 dp 加换根。

那么首先设计状态。发现棋子不一定要回到起点，这启发我们对必须回起点和不用回分别设计状态。加上门的限制，我们设计以下状态：
$$f_{x,a,b}$$
* $x$ 是当前子树的根。
* $a$ 为 $0$ 代表子树内没有门（也无法使用），$1$ 代表传送门在点 $x$ 处。
* $b$ 为 $0$ 代表无需返回起点 $x$，$1$ 代表需要返回。

那么写出以下转移方程：
* $f_{x,0,1}=2(siz_x-1)$。子树中的每个点都要进入和返回一次。
* $f_{x,0,0}=f_{x,0,1}-farthest_x$。$farthest_x$ 是子树 $x$ 内距离 $x$ 最远的点与 $x$ 的距离。我们贪心地选择那个最远的点作为终点（不返回）。
* $f_{x,1,1}=\sum\min(f_{y,1,1}+2,f_{y,0,0}+1)$。 
  * $f_{y,1,1}+2$ 代表将门和棋子都移到 $y$。$y$ 内走完后由于门接下来还要使用，再移动棋子从 $y$ 回到 $x$，此时把门传送回来。
  * $f_{y,0,0}+1$ 代表先移动去 $y$。由于门在 $x$ 处，棋子不用返回，直接传送回来即可。
* $f_{x,1,0}=f_{x,1,1}-\max(\min(f_{y,1,1}+2,f_{y,0,0}+1)-(f_{y,1,0}+1))$。
  * $f_{y,1,0}+1$ 可以理解为钦定一个 $y$ 为终点，此时门就没有必须留在 $x$ 的限制，可以跟着棋子一起走。
  * $\max(\min(f_{y,1,1}+2,f_{y,0,0}+1)-(f_{y,1,0}+1))$ 则是找出最优的钦定的 $y$。
  
直接 dp 是 $O(n^2)$ 的。考虑换根 dp。这里推荐一篇 [换根 DP 的常用处理方式](https://www.cnblogs.com/cpchenpi/p/-/Rerooting)。

首先把 $y$ 对 $x$ 的贡献删去。由于有 max 的存在，我们可以开个结构体记录 $\max(\min(f_{y,1,1}+2,f_{y,0,0}+1)-(f_{y,1,0}+1))$ 的次大值。

然后根据转移方程把 $x$ 当作 $y$ 的儿子。

[代码](https://atcoder.jp/contests/arc179/submissions/54315972)里挺详细的，就不说了。时间复杂度 $O(n)$。

---

## 作者：Sorato_ (赞：2)

# ARC179D Portable Gate 题解

## 题目大意

你在一棵 $n$ 个节点的树上并且有一个门。选定任意节点作为起点，然后每次执行以下操作之一：

- 移动到当前节点的相邻节点，耗费代价 1；
- 移动到门所在节点；
- 将门移动到当前节点。

求至少消耗多少代价能遍历树上的所有节点。

## Solve

将选定的起点视为根，考虑树形 DP。

设 $f(u)$ 表示将 $u$ 的子树内遍历完回到 $u$ 所需的最小代价，那么对于一个儿子 $v$，转移分两种情况：

- 门放在 $u$ 上，徒步走完 $v$ 的子树。
- 门放在 $v$ 上，可以使用门走完 $v$ 的子树。

考虑徒步走完 $v$ 的子树代价是多少，由于门放在 $u$ 上，最后可以传送回来，显然我应该走到 $v$ 的子树内的最深的那个叶子后传送回来。所以记 $v$ 子树内最深的叶子到 $v$ 的距离是 $h(v)$。记徒步走完 $v$ 的子树的代价为 $g(v)$，则 $g(v)=2(siz(v)-1)-h(v)$。

所以有转移：
$$
f(u)\longleftarrow\min(g(v)+1,f(v)+2)
$$
$g(v)+1$ 代表只走 1 步到 $v$，走完 $v$ 的子树后用门传送回来。$f(v)+2$ 表示走一步到 $v$，带门走完 $v$ 子树后再走 1 步回来。

但是，题目并没有要求最后必须回到起点，所以 $f(u)$ 现在的意义是不够的，我们还应讨论遍历完 $u$ 的子树后是否回到节点 $u$。由此我们改变一下状态。

记 $f(u,1/0)$ 表示遍历完 $u$ 的子树，是 / 否回到节点 $u$ 的最小代价。$f(u,1)$ 还是沿用上面的状态转移，对于 $f(u,0)$，我考虑去枚举最后落在 $u$ 的哪个儿子的子树里，这个儿子记为 $v$，那么我要求遍历除了 $v$ 的其他所有儿子的子树后，都要回到节点 $u$，只有 $v$ 不需要。那么只需把 $v$ 的贡献从 $f(u,1)$ 中刨去，再加上不要求遍历 $v$ 的子树后回到 $v$ 的贡献。

至于怎么算这个贡献，还是上面的分情况讨论。若门在 $u$ 上，则代价为 $g(v)+1$，否则若带门进 $v$ 的子树，代价为 $f(v,0)+1$。

所以记 $t(v)=-\min(g(v)+1,f(v,1)+2)+\min(g(v)+1,f(v,0)+1)$ 为 $v$ 对 $f(u,0)$ 的贡献，那么有：
$$
f(u,1)=\sum\limits_{v\in son(u)}\min(g(v)+1,f(v,1)+2)\\
f(u,0)=\min\limits_{v\in son(u)}\{f(u,1)+t(v)\}
$$
这样我们就处理完了根固定时的答案。接下来考虑换根。

感觉线性换根非常困难，我不会。但由于数据范围是 $n\leq 2\times 10^5$，所以我们可以考虑用比较苟脑的带 $\log$ 的换根方式。

考虑把 $u$ 的所有儿子 $v$ 的 $h(v)$ 和 $t(v)$ 分别放进 `set` 里，换根时只需要用 `set` 的 `erase` 函数就可以把 $v$ 的贡献从 $u$ 里刨去，刨去后容易算出以 $v$ 为根时的 $g(u),h(u),f(u),t(u)$，用这些信息更新 $v$ 的相应值和 $v$ 的两个 `set` 即可。具体看代码吧。

## Code

```c++
std::set<std::pair<int,int>>s[N],q[N];
void F(int u,int fa)
{
	for(int v:e[u])
		if(v!=fa)
		{
			F(v,u);
			f[u][1]+=min(f[v][1]+2,g[v]+1);
			q[u].insert({t[v],v});
			siz[u]+=siz[v];s[u].insert({h[v],v});
		}
	f[u][0]=f[u][1];
	if(!s[u].empty())//谨防RE
	{
		f[u][0]=min(f[u][0],f[u][1]+q[u].begin()->first);
		h[u]=s[u].rbegin()->first+1;
	}
	g[u]=(siz[u]++<<1)-h[u];
	t[u]=-min(f[u][1]+2,g[u]+1)+min(f[u][0]+1,g[u]+1);
}
void G(int u,int fa)
{
	int _f[2],_h,_g,_t;//把某个儿子刨去后的相应值
	for(int v:e[u])
		if(v!=fa)
		{
			s[u].erase({h[v],v});q[u].erase({t[v],v});
			_h=s[u].empty()?0:s[u].rbegin()->first+1;
			_g=(n-siz[v]-1<<1)-_h;
			_f[1]=f[u][1]-min(f[v][1]+2,g[v]+1);
			_f[0]=_f[1];
			if(!q[u].empty())//谨防RE
				_f[0]=min(_f[0],_f[1]+q[u].begin()->first);
			_t=-min(_f[1]+2,_g+1)+min(_f[0]+1,_g+1);
			q[v].insert({_t,u});s[v].insert({_h,u});//更新儿子的 set
			f[v][1]+=min(_f[1]+2,_g+1);
			f[v][0]=min(f[v][1],f[v][1]+q[v].begin()->first);
			s[u].insert({h[v],v});q[u].insert({t[v],v});
			G(v,u);
		}
}
signed main()
{
	n=read();
	for(int i=1,u,v;i<n;i=-~i)
		u=read(),v=read(),
		e[u].push_back(v),e[v].push_back(u);
	F(1,0);G(1,0);
	for(int i=1;i<=n;i=-~i)	ans=min(ans,min(f[i][0],f[i][1]));
	return printf("%d",ans),0;
}
```

---

## 作者：gdf_yhm (赞：2)

[arc179d](https://www.luogu.com.cn/problem/AT_arc179_d)

### 思路

设计树形 dp。$dp_{u,0}$ 表示进子树 $u$ 并不再出去的代价。$dp_{u,1}$ 表示进子树 $u$ 并返回，且传送门在 $fa$、不在子树内使用传送门的代价。$dp_{u,2}$ 表示进入子树 $u$ 并返回，且可以在子树内使用传送门。

发现 $dp_{u,1}$ 一定是遍历子树最后到子树中最深的点通过传送门返回，一定是 $2\times siz_u+\max (dep_i-dep_u)$。$dp_{u,0}$ 和 $dp_{u,2}$ 的唯一区别在于 $dp_{u,0}$ 最后进入的一个子树不用返回。

$$dp_{u,2}=\sum \max(dp_{v,1}+1,dp_{v,2}+2),dp_{u,0}=dp_{u,2}+\min (dp_{v,0}+1-\min(dp_{v,1}+1,dp_{v,2}+2))$$

然后换根 dp。考虑 $\max (dep_i-dep_u)$ 和 $\min (dp_{v,0}+1-\min(dp_{v,1}+1,dp_{v,2}+2))$ 的转移，需要记录最大值和次大值。

### code

```cpp
int n,ans=inf;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dp[maxn][3],siz[maxn];
pii dep[maxn],mn[maxn];
void dfs(int u,int fa){
	siz[u]=1;mn[u].fi=mn[u].se=0,dep[u].fi=dep[u].se=0;
	if(u!=1&&!e[head[u]].nxt){dp[u][0]=dp[u][1]=dp[u][2]=0;return ;}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);siz[u]+=siz[v];
		if(dep[u].fi<dep[v].fi+1)dep[u].se=dep[u].fi,dep[u].fi=dep[v].fi+1;
		else if(dep[u].se<dep[v].fi+1)dep[u].se=dep[v].fi+1;
		int val=dp[v][0]+1-min(dp[v][1]+1,dp[v][2]+2);
		if(val<mn[u].fi)mn[u].se=mn[u].fi,mn[u].fi=val;
		else if(val<mn[u].se)mn[u].se=val;
		dp[u][0]+=min(dp[v][1]+1,dp[v][2]+2);
		dp[u][2]+=min(dp[v][1]+1,dp[v][2]+2);
	}
	dp[u][0]+=mn[u].fi;dp[u][1]=(siz[u]-1)*2-dep[u].fi;
	// cout<<u<<" "<<dp[u][0]<<" "<<dp[u][1]<<" "<<dp[u][2]<<"\n";
}
void dfs1(int u,int fa){
	ans=min(ans,dp[u][0]);
	// cout<<u<<" "<<dp[u][0]<<" "<<dp[u][1]<<" "<<dp[u][2]<<"\n";
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		int u0=dp[u][0],u1=dp[u][1],u2=dp[u][2];pii du=dep[u],mnu=mn[u];
		siz[u]-=siz[v],siz[v]+=siz[u];
		if(dep[u].fi==dep[v].fi+1)dep[u].fi=dep[u].se;
		int val=dp[v][0]+1-min(dp[v][1]+1,dp[v][2]+2);
		if(mn[u].fi==val)mn[u].fi=mn[u].se;
		dp[u][1]=(siz[u]-1)*2-dep[u].fi;
		dp[u][2]-=min(dp[v][1]+1,dp[v][2]+2);
		dp[u][0]=dp[u][2]+mn[u].fi;
		
		if(dep[v].fi<dep[u].fi+1)dep[v].se=dep[v].fi,dep[v].fi=dep[u].fi+1;
		else if(dep[v].se<dep[u].fi+1)dep[v].se=dep[u].fi+1;
		val=dp[u][0]+1-min(dp[u][1]+1,dp[u][2]+2);
		if(val<mn[v].fi)mn[v].se=mn[v].fi,mn[v].fi=val;
		else if(val<mn[v].se)mn[v].se=val;
		dp[v][0]+=min(dp[u][1]+1,dp[u][2]+2);
		dp[v][2]+=min(dp[u][1]+1,dp[u][2]+2);
		dp[v][0]=dp[v][2]+mn[v].fi;dp[v][1]=(siz[v]-1)*2-dep[v].fi;
		
		dfs1(v,u);
		dp[u][0]=u0,dp[u][1]=u1,dp[u][2]=u2;dep[u]=du,mn[u]=mnu;
		siz[v]-=siz[u],siz[u]+=siz[v];
	}
}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1,0);
	dfs1(1,0);
	printf("%lld\n",ans);
}
```

---

## 作者：under_the_time (赞：1)

## 题意

> 给定一棵 $n$ 个点的树，你有一个棋子和一个传送门，有 $3$ 种操作：
>
> - 将棋子移到相邻点，代价为 $1$；
> - 将棋子传送到传送门的位置，代价为 $0$；
> - 将传送门传送到棋子的位置，代价为 $0$；
>
> 一开始你需要选择一个点 $u$，使得棋子和传送门一开始都在点 $u$ 上，求经过每个点至少一次的最小代价。
>
> $2\le n\le 2\times 10^5$。

## 题解

前情提要：这是一篇比较详细的题解。

考虑树形 dp，考虑先钦定点 $1$ 为根（起点），然后换根得出其他点为起点的答案。设当前走到 $u$，当前任务是将 $u$ 子树内的点访问完。此时按照**传送门放哪**有两种策略：把传送门留在 $u$ 的**某个祖先**上，**徒步访问**完 $u$ 子树内所有节点后，直接**传送**到 $u$ 点的祖先，接着考虑下一个子树；把传送门放在**子树**中，最后**回到** $u$ 点**继续往祖先方向**走，接着考虑下一个子树。若传送门留在了 $u$ 的某个祖先上（即第一种策略下），那么在访问 $u$ 的子树的过程中就不能传送了。

为什么传送门不会留在 $u$ 的兄弟子树中？对于 $u$ 的两个儿子 $v_1,v_2$，假设先访问 $v_1$ 再访问 $v_2$，过程中一定会回到一次 $u$ 点（没有去 $u$ 点的祖先是因为 $u$ 的子树还差 $v_2$ 的子树没访问完），在访问 $v_1$ 子树前专门跑到 $v_2$ 的子树中放传送门显然不优，不如回到 $u$ 点、开始访问 $v_2$ 的子树时再顺便把传送门带上。当然若没给 $u$ 的子树分配传送门就没这个问题。故在最优策略下 $v_1$ 子树和 $v_2$ 子树的答案**互不影响**。

于是我们这么设计状态：令 $f(u,0/1,0/1)$ 表示考虑 $u$ 的子树，访问完整颗子树后是否需要走回点 $u$，过程中传送门是否放在 $u$ 的子树中。令 $u$ 的儿子点集为 $S_u$，转移就考虑四种情况：

- $f(u,1,0)$，即从 $u$ 出发、途中**不传送**（即传送门不在 $u$ 的子树中），走完整颗子树后再**走回**到 $u$，那么整个过程就可以拆为：枚举 $u$ 的儿子 $v\in S_u$，从 $u$ 走到点 $v$，$v$ 按照同样方式走完 $v$ 的子树再回到 $v$，再从 $v$ 走到 $u$ 继续考虑下一个儿子。$(u,v)$ 这条边走了两次，有 $2$ 的代价，于是就有转移：
  $$
  f(u,1,0)=\sum_{v\in S_u}2+f(v,1,0)
  $$

- $f(u,0,0)$，即从 $u$ 出发，途中**不传送**，走完整颗子树后**无需走回**到 $u$（可能就直接传到 $u$ 的祖先去了）。相较 $f(u,1,0)$ 而言，对于 $u$ 子树中的一个点 $v$，若 $v$ 是最后一个访问的点，在算 $f(u,1,0)$ 时显然最终会从 $v$ 走回到 $u$，但算 $f(u,0,0)$ 时不需要，相当于省了 $\operatorname{dis(u,v)}$ 这条从 $u$ 到 $v$ 的链的代价，其中 $\operatorname{dis}(u,v)$ 表示 $u,v$ 之间的距离，这里 $u,v$ 有祖先后代关系所以 $\operatorname{dis}(u,v)=\operatorname{dep}(v)-\operatorname{dep}(u)$，其中 $\operatorname{dep}$ 表示深度。我们贪心地选择最长的链减掉，令从 $u$ 出发的最长链长度为 $g(u)$，得到 $g(u)$ 后即得 $f(u,0,0)=f(u,1,0)-g(u)$，对于 $g$ 的转移显然有：
  $$
  g(u)=\max_{v\in S_u}g(v)+1
  $$

- $f(u,1,1)$，即从 $u$ 出发，途中**可以传送**（即传送门可以放在 $u$ 的子树里进行传送），访问完整颗子树后**回到** $u$。前面提到兄弟子树间答案互不影响，于是我们对 $u$ 的每个儿子分别考虑，答案即为每个孩子的代价之和。对于一个 $v\in S_u$，有两种选择：一种是把传送门放在 $u$ 上，那么在 $v$ 的子树中将无传送门可用，此时过程可以拆为：从 $u$ 走到 $v$，从 $v$ 出发不传送、无需回到 $v$ 走完整颗子树，最后传送到点 $u$，那么该选择代价即为 $1+f(v,0,0)$；另一种是把传送门放到 $v$ 的子树中，那么最后一定要回到点 $v$（可以是传回来也可以是走回来），再走回点 $u$，此时过程可以拆为：从 $u$ 走到 $v$，从 $v$ 出发允许传送、需要回到 $v$ 点走完整颗子树，最后从 $v$ 走回到 $u$，那么该选择代价即为 $2+f(v,1,1)$，两者贪心地取较小值即可。于是就有转移：
  $$
  f(u,1,1)=\sum_{v\in S_u}\min(f(v,0,0)+1,f(v,1,1)+2)
  $$

- $f(u,0,1)$，即从 $u$ 出发，途中**可以传送**，访问完整颗子树后**无需回到** $u$。我们考虑枚举一个 $u$ 的儿子 $v$，表示 $v$ 的子树访问完后就不需要回到 $u$ 了。因为不需要回到 $u$，传送门可以直接给 $v$ 用，那么过程可以拆分为：从 $u$ 走到 $v$，从 $v$ 出发允许传送、需要回到 $v$ 点走完整颗子树，最后不需要从 $v$ 走回到 $u$。那么此时 $v$ 产生的代价就是 $f(v,0,1)+1$，答案即为 $f(u,1,1)-\big(\min(f(v,0,0)+1,f(v,1,1)+2)\big)+(f(v,0,1)+1)$，我们贪心地令 $\min(f(v,0,0)+1,f(v,1,1)+2)-f(v,0,1)-1$ 尽可能大，那么就有转移：
  $$
  f(u,0,1)=f(u,1,1)-\max_{v\in S_u}\left(\min(f(v,0,0)+1,f(v,1,1)+2)-f(v,0,1)-1\right)
  $$

这样以 $1$ 为起点的答案就算出来了，即 $f(1,0,1)$。接下来考虑换根。对于点 $u$ 和它的一个孩子 $v$，我们先删掉 $v$ 对 $u$ 的所有贡献，然后把 $u$ 当成 $v$ 的孩子再做一遍上述转移即可。具体地，要删的贡献有：

- 对 $f(u,1,0)$ 的贡献 $2+f(v,1,0)$；
- 对 $g(u)$ 的贡献 $g(v)+1$；
- 对 $f(u,1,1)$ 的贡献 $\min(f(v,0,0)+1,f(v,1,1)+2)$；
- 对 $f(u,0,1)$ 的贡献 $\min(f(v,0,0)+1,f(v,1,1)+2)-f(v,0,1)-1$。

有些是减掉，有些是最大值变次大值。之后做同样的转移即可。

时间复杂度 $O(n)$。

## 实现

对于最大值变次大值可以写个结构体，写个 `chg` 函数并记录最大值和次大值从哪转移得到。

```cpp
const ll inf = 1e16; 
const int maxn = 2e5 + 5;
int n;
namespace Graph {
    struct Edge { int to, nxt; } e[maxn << 1];
    int head[maxn], ecnt;
    void addEdge(int u, int v) { e[++ ecnt] = Edge { v, head[u] }, head[u] = ecnt; }
} using namespace Graph;
ll f[maxn][2][2], g[maxn][2][2]; // 是/否 返回起点，是/否 门在子树里
struct Rec {
    ll mx0, mx1; int frm0, frm1;
    Rec (ll m0 = 0, ll m1 = 0, int f0 = -1, int f1 = -1) { mx0 = m0, mx1 = m1, frm0 = f0, frm1 = f1; }
    void chg(ll val, int frm) {
        if (val >= mx0) { mx1 = mx0, frm1 = frm0; mx0 = val, frm0 = frm; }
        else if (val >= mx1) mx1 = val, frm1 = frm;
    }
} mxdep[maxn], h[maxn];
int main() {
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; i ++)
        scanf("%d %d", &u, &v), addEdge(u, v), addEdge(v, u);
    auto dfs = [&](auto self, int u, int fa) -> void {
        f[u][1][1] = 0; 
        for (int i = head[u], v; i; i = e[i].nxt) {
            if ((v = e[i].to) == fa) continue;
            self(self, v, u), mxdep[u].chg(mxdep[v].mx0 + 1, v);
            f[u][1][1] += min(f[v][0][0] + 1, f[v][1][1] + 2), f[u][1][0] += f[v][1][0] + 2;
        } f[u][0][0] = f[u][1][0] - mxdep[u].mx0;
        for (int i = head[u], v; i; i = e[i].nxt) if ((v = e[i].to) != fa)  {
            ll dt = min(f[v][0][0] + 1, f[v][1][1] + 2) - f[v][0][1] - 1;
            h[u].chg(dt, v);
        } f[u][0][1] = f[u][1][1] - h[u].mx0;
    }; dfs(dfs, 1, 0);
    auto dfs0 = [&](auto self, int u, int fa) -> void {
        if (fa) {
            for (int i = 0; i < 2; i ++) for (int j = 0; j < 2; j ++) g[fa][i][j] = 0;
            g[fa][1][0] = f[fa][1][0] - f[u][1][0] - 2;
            if (mxdep[fa].frm0 == u) g[fa][0][0] = g[fa][1][0] - mxdep[fa].mx1;
            else g[fa][0][0] = g[fa][1][0] - mxdep[fa].mx0;
            g[fa][1][1] = f[fa][1][1] - min(f[u][0][0] + 1, f[u][1][1] + 2);
            if (h[fa].frm0 == u) g[fa][0][1] = g[fa][1][1] - h[fa].mx1;
            else g[fa][0][1] = g[fa][1][1] - h[fa].mx0;
            if (mxdep[fa].frm0 == u) mxdep[u].chg(mxdep[fa].mx1 + 1, fa);
            else mxdep[u].chg(mxdep[fa].mx0 + 1, fa);
            f[u][1][0] = (n - 1) << 1, f[u][0][0] = f[u][1][0] - mxdep[u].mx0;
            f[u][1][1] += min(g[fa][0][0] + 1, g[fa][1][1] + 2);
            ll dt = min(g[fa][0][0] + 1, g[fa][1][1] + 2) - g[fa][0][1] - 1;
            h[u].chg(dt, fa), f[u][0][1] = f[u][1][1] - h[u].mx0;
        } for (int i = head[u]; i; i = e[i].nxt) if (e[i].to != fa)
            self(self, e[i].to, u);
    }; dfs0(dfs0, 1, 0); ll ans = inf; 
    for (int i = 1; i <= n; i ++) 
        ans = min(ans, f[i][0][1]);
    
    return printf("%lld\n", ans), 0;
}
```

---

## 作者：strcmp (赞：1)

很强的换根 dp 题，当然代码难度也不低。

最基础的想法是直接欧拉序，但是肯定要考虑怎么用门减少遍历次数的。

「将门传送到 $u$」这种操作看起来就很难受，同时考虑它们的互相传送我们避免不了记录门和 $u$ 的二元组状态，$n^2$ 的状态数就锁死了我们继续优化的可能性，更别提我们还要换根了。

$u$ 向下走的过程，可以看作 $u$ 要么带着门一起走，要么干脆门待在原地然后自己走。

发现门的轨迹形成了一个包含根的联通块，当然它也是一棵树。

于是直接对这棵树（门的轨迹）开滴批，设个 $f_u$ 代表 $u$ 子树内全部遍历完的最小代价，并且钦定必须回到 $u$ 且开始和结束门都在 $u$ 上。

设个 $w_v = 2 \times (\text{siz}_v - 1) - \left(\max\limits_{x \in \text{subtree}(v)}\text{dep}_x - \text{dep}_v\right)$。这就是不移动门遍历 $v$ 的最小代价，具体来说就是先遍历完其它子树，最后搜到最深的叶子的时候就传送回去。

有转移：$f_u \leftarrow f_u + \min(w_v + 1,\,f_v + 2)$。也就是决策 $v$ 到底在不在门的轨迹里面，在门的轨迹里我们走进 $v$ 还要回到 $u$。

但是还是有两个问题，第一个是从 $u$ 出发我们不一定必须回到 $u$，第二个是根可以任意定我们还没有换根。

再设个 $g_u$ 代表遍历完 $u$ 子树内所有点，但是可以不回到 $u$ 的最小代价。

转移显然：

$$
\begin{aligned}
& \forall v \in \text{son}(u):\\
& f_u \leftarrow f_u + \min(w_v + 1,\,f_v + 2)\\
& \text{After calculating $f_u$:}\\
& g_u \leftarrow \min (g_u,\,f_u + \min \{ \min(w_v + 1,\,g_v + 1) - \min(w_v + 1,\,f_v + 2)) \}\\
\end{aligned}
$$

答案显然为 $g_{\text{rt}}$。

根固定的情况就处理好了，接下来考虑 up and down（换根 dp）。

发现定根为 $u$ 的影响就是 $u$ 多出来一棵子树，这棵额外子树的最大深度以及 $f,\,g$ 值可以 $\Theta(n)$ 维护好，维护次大深度和次小 $\min \{ \min(w_v + 1,\,g_v + 1) - \min(w_v + 1,\,f_v + 2)) \}$ 值即可。

时间复杂度 $\Theta(n)$，可以通过，但是细节不少。

```cpp
#include <bits/stdc++.h>
#include <set>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long int ll;
using pli = pair<ll, int>;
using ld = double;
constexpr int maxn = 3e5 + 10, mod = 1e9 + 7;
vector<int> e[maxn]; int n, f[maxn], g[maxn], s[maxn], d[maxn], d2[maxn], mx[maxn], mx2[maxn], ans = 1e9;
void dfs1(int u, int fa) {
	if (e[u].size() != 1) d[u] = -1e9;
	s[u] = 1; int w, k; d2[u] = -1e9;
	for (int v : e[u]) {
		if (v == fa) continue;
		dfs1(v, u); s[u] += s[v], w = 2 * (s[v] - 1) - d[v] + 1;
		if (d[v] + 1 > d[u]) d2[u] = d[u], d[u] = d[v] + 1; else if (d[v] + 1 > d2[u]) d2[u] = d[v] + 1;
		f[u] += min(w, f[v] + 2); k = min(w, f[v] + 2) - min(w, g[v] + 1); 
		if (k > mx[u]) mx2[u] = mx[u], mx[u] = k; else if (k > mx2[u]) mx2[u] = k;
	}
	g[u] = f[u] - mx[u];
}
void dfs2(int u, int fa, int F, int G, int D) {
	int k = (n - s[u]) * 2 - D, w = 0;
	if (u != 1) w = min(F + 2, k), ans = min(ans, f[u] + w - max(mx[u], w - min(G + 1, k)));
	for (int v : e[u]) {
		if (v == fa) continue;
		int D1 = d[u] - 1, D2 = d2[u] - 1, M1 = mx[u], M2 = mx2[u], h = 2 * (s[v] - 1) - d[v] + 1, t = min(f[v] + 2, h);
		if (d[v] + 1 == d[u]) swap(D1, D2); if (mx[u] == t - min(g[v] + 1, h)) swap(M1, M2);
		dfs2(v, u, w + f[u] - t, w + f[u] - t - max(M1, w - min(k, G + 1)), max(D1 + 2, D + 1));
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), e[u].pb(v), e[v].pb(u);
	dfs1(1, 0); ans = g[1]; dfs2(1, 0, 0, 0, 0);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：CCPSDCGK (赞：1)

先考虑假设已经定了根，那么该如何做。

显然 Piece 要按照 dfs 序遍历，设 $f_u$ 为遍历以 $u$ 为根的子树花费的最小代价（不强制回到 $u$），$g_u$ 为遍历以 $u$ 为根的子树花费的最小代价（强制回到 $u$）。

对于 $g_u$ 来说，当 Piece 到 $u$ 的其中一个儿子 $v$ 的子树中，如果将 Gate 带入到了 $v$ 的子树中，那不等到 Piece 完全遍历完子树并出来，Gate 只能永远待在 $v$ 的子树里，那么问题就完全转化成 $v$ 的子问题，代价为 $g_v+2$，此时只剩下 Gate 永远在 $u$ 的（或在 $u$ 子树之外）情况，这时 Gate 需要遍历完整个子树，但有一条直上直下的链可以直接通过 Gate 传送回去，所以答案是 $2siz_v-maxdep_v-1$。

至此可以写出关于 $g$ 的转移方程式：$g_u=\sum\limits_{v\in \text{son}(u)}\min(g_v+2,2siz_v-maxdep_v-1)$。

至于 $f_u$，只需要选择一个儿子 $v$ 进入它以后不用出来，其它的都需要出来，不用出来的那个转移和 $g$ 基本相同，一个是 $2siz_v-maxdep_v-1$ 与之前相同，一个是 $f_v+1$。

所以 $f_u$ 需要我们找到最大的 $\min(g_v+2,2siz_v-maxdep_v-1)-\min(f_v+1,2siz_v-maxdep_v-1)$，直接用 $g_u$ 一减就好了。

然而这只是一个起点的情况，题中没有限制起点，所以我们需要换根。

那就需要多记录子树外的 $maxdep,siz,f,g$ 子树外合并的时候如果是合并最大值，只需要记录每个点所有儿子的最大值和次大值，合并的时候判断选哪个即可，加法合并直接差分即可。

代码有点难写，对我这种一年没动代码的人来说是一个很大的挑战。
```cpp
vector<int> edge[200005];
int f[200005],n,g[200005],mxdep[200005],siz[200005],ans,maxn[200005];
void dfs1(int u,int fa){
	siz[u]=1;
	for(int v:edge[u]) if(v^fa){
		dfs1(v,u),mxdep[u]=max(mxdep[u],mxdep[v]+1),siz[u]+=siz[v];
		int tmp=min(g[v]+2,(siz[v]<<1)-mxdep[v]-1);
		g[u]+=tmp,maxn[u]=max(maxn[u],tmp-min(f[v]+1,(siz[v]<<1)-mxdep[v]-1));
	}
	f[u]=g[u]-maxn[u];
}
void dfs2(int u,int fa,int nowd,int nowg,int nowf){
	int gg;
	if(fa) gg=min(nowg+2,(n-siz[u]<<1)-nowd),ans=min(ans,g[u]+gg-max(maxn[u],gg-min(nowf+1,(n-siz[u]<<1)-nowd)));
	else gg=0;
	int mxd1=-inf,mxd2=-inf,mx1=0,mx2=0;
	for(int v:edge[u]) if(v^fa){
		if(mxd1<mxdep[v]) mxd2=mxd1,mxd1=mxdep[v];
		else if(mxd2<mxdep[v]) mxd2=mxdep[v];
		int val=min(g[v]+2,(siz[v]<<1)-mxdep[v]-1)-min(f[v]+1,(siz[v]<<1)-mxdep[v]-1);
		if(mx1<val) mx2=mx1,mx1=val;
		else if(mx2<val) mx2=val;
	}
	for(int v:edge[u]) if(v^fa){
		int tmp=min(g[v]+2,(siz[v]<<1)-mxdep[v]-1);
		if(mxd1==mxdep[v]){
			if(mx1==tmp-min(f[v]+1,(siz[v]<<1)-mxdep[v]-1)) dfs2(v,u,max(nowd+1,mxd2+2),gg+g[u]-tmp,gg+g[u]-tmp-max(gg-min(nowf+1,(n-siz[u]<<1)-nowd),mx2));
			else dfs2(v,u,max(nowd+1,mxd2+2),gg+g[u]-tmp,gg+g[u]-tmp-max(gg-min(nowf+1,(n-siz[u]<<1)-nowd),mx1));
		}
		else{
			if(mx1==tmp-min(f[v]+1,(siz[v]<<1)-mxdep[v]-1)) dfs2(v,u,max(nowd+1,mxd1+2),gg+g[u]-tmp,gg+g[u]-tmp-max(gg-min(nowf+1,(n-siz[u]<<1)-nowd),mx2));
			else dfs2(v,u,max(nowd+1,mxd1+2),gg+g[u]-tmp,gg+g[u]-tmp-max(gg-min(nowf+1,(n-siz[u]<<1)-nowd),mx1));
		}
	}
}
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		edge[u].eb(v),edge[v].eb(u);
	}
	dfs1(1,0),ans=f[1],dfs2(1,0,0,0,0),cout<<ans;
	return 0;
}
```

---

## 作者：happybob (赞：0)

当根固定时，我们希望一个一个子树走，记 $f_{i,0/1,0/1}$ 表示从点 $i$ 出发遍历子树内所有点，要求能否用门，要求是否需要回到 $i$ 的答案。转移是很容易的，于是 $O(n^2)$ 是很显然的。

这个 DP 很容易做换根，做完了。

---

## 作者：huhangqi (赞：0)

以出发点为根，我们可以发现门一定在一个节点的祖先上，如果你走到一个点放下门，再继续走子树部分，然后去走其它子树时，一定会经过放门的这个点，那么此时这个门在这已经没有用了，如果你先去走其它子树，可以发现必定不是最优情况，所以门一定是在节点的祖先。

题目需要求出遍历完所有位置得到的答案。

我们需要对每个子树进行处理，由于问题是全部涂完色而不需要回到根，而对于根的子树需要先走回来才可以计入答案。

我们设 $f_{i,0/1}$ 表示涂完 $i$ 所在的子树所走的步数。

我们先考虑第一种情况，我们很容易想到我们在处理以一个节点所在的子树部分时，以此节点为根，对于这个节点的子树有节点放门和不放门两种情况。

假设此时的节点为 $u$，儿子节点为 $v$。

在不放门的情况下这一个子树的次数是为 $f_{v,1}+2$ 。

而在放门的情况下，我们可以有一次不返回，直接传送回来，假设 $siz_i$ 表示以 $i$ 为根的子树中的节点数量，而 $g_i$ 表示从 $i$ 向子树内可以连到的最长链长度，也可以理解为最大深度。

此时次数就是 $2\times (siz_i-1) - g_i$ 。

那么最后就可以得到 $f_{u,1}$ 的转移式为：

$$$
f_{u,1}=\sum _{v\in son_u} \min(f_{v,1}+2,2\times (siz_v-1) - g_v)$$$

对于 $f_{u,0}$ 我们只需要让一个子树不回来即可。

那么此时将上一次的这棵子树的答案减掉，然后再加上不用返回的情况即可，转移式为：

$$$
f_{u,0}=f_{u,1}-\max(\min(f_{v,1}+2,2\times (siz_v-1) - g_v)-\min(f_{v,0}+1,2\times (siz_v-1)-g_v+1))
$$$

这样就处理完成了，但是我们并不知道起点在哪里，所以要换根，后面就比较板子了。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,f[200005][2],g[200005][2],ma[200005][2],siz[200005],ans=1e18;
vector<int> e[200005];
void dfs(int p,int fa){
	siz[p]=1;
	for(int i:e[p]){
		if(i==fa)continue;
		dfs(i,p);
	}
	ma[p][0]=ma[p][1]=-1e16;
	for(int i:e[p]){
		if(i==fa)continue;
		f[p][1]+=min(f[i][1]+2,2*(siz[i]-1)-g[i][0]+1);
		if(g[i][0]+1>g[p][0])g[p][1]=g[p][0],g[p][0]=g[i][0]+1;
		else if(g[i][0]+1>g[p][1])g[p][1]=g[i][0]+1;
		siz[p]+=siz[i];
		int tmp=min(f[i][1]+2,2*(siz[i]-1)-g[i][0]+1)-min(f[i][0]+1,2*(siz[i]-1)-g[i][0]+1);
		if(tmp>ma[p][0])ma[p][1]=ma[p][0],ma[p][0]=tmp;
		else if(tmp>ma[p][1])ma[p][1]=tmp;
	}
	if(siz[p]==1)ma[p][0]=0;
	f[p][0]=f[p][1]-ma[p][0];
}
void dfs2(int p,int fa){
	ans=min(ans,f[p][0]);
	int fp0=f[p][0],fp1=f[p][1],gp0=g[p][0],map0=ma[p][0],sizp=siz[p];
	for(int i:e[p]){
		if(i==fa)continue;
		f[p][1]-=min(f[i][1]+2,2*(siz[i]-1)-g[i][0]+1);
		if(g[i][0]+1==g[p][0])g[p][0]=g[p][1];
		siz[p]-=siz[i];
		int tmp=min(f[i][1]+2,2*(siz[i]-1)-g[i][0]+1)-min(f[i][0]+1,2*(siz[i]-1)-g[i][0]+1);
		if(tmp==ma[p][0])ma[p][0]=ma[p][1];
		f[p][0]=f[p][1]-ma[p][0];
		swap(i,p);
		f[p][1]+=min(f[i][1]+2,2*(siz[i]-1)-g[i][0]+1);
		if(g[i][0]+1>g[p][0])g[p][1]=g[p][0],g[p][0]=g[i][0]+1;
		else if(g[i][0]+1>g[p][1])g[p][1]=g[i][0]+1;
		siz[p]+=siz[i];
		tmp=min(f[i][1]+2,2*(siz[i]-1)-g[i][0]+1)-min(f[i][0]+1,2*(siz[i]-1)-g[i][0]+1);
		if(tmp>ma[p][0])ma[p][1]=ma[p][0],ma[p][0]=tmp;
		else if(tmp>ma[p][1])ma[p][1]=tmp;
		f[p][0]=f[p][1]-ma[p][0];
		swap(i,p);
		dfs2(i,p);
		f[p][0]=fp0,f[p][1]=fp1,g[p][0]=gp0,ma[p][0]=map0,siz[p]=sizp;
	}
}
signed main(){
	cin>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,0);
	dfs2(1,0);
	cout<<ans;
	return 0;
}

``````

---

