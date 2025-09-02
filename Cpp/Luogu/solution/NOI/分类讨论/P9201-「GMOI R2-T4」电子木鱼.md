# 「GMOI R2-T4」电子木鱼

## 题目背景

运营电子资本，招聘赛博佛祖，积累虚拟功德。

功德无量，随喜赞叹。

111

## 题目描述

给你 $n$，表示一共有 $n$ 位赛博佛祖，编号依次为 $1 \sim n$。

第 $i\ (1 \leq i \leq n)$ 位赛博佛祖可以对应为一个二元组 $\langle S_i, d_i \rangle$，其中 $S$ 在任意时刻均为 $\{1, 2, 3, \dots, m\}$ 的一个子集（可以为空），而 $d_i$ 为 $1 \sim m$ 间的整数。

如果在某一时刻，存在一位赛博佛祖的 $S_i$ 为空集，佛祖会感到很开心而给你加功德。具体地，他会敲响第 $d_i$ 个木鱼，并 **在下一时刻同时** 影响所有的 $n$ 位赛博佛祖（包括他自己）。对第 $j(1 \leq j \leq n)$ 位赛博佛祖，如果 $d_i \in S_j$，那么将从 $S_j$ 内删去 $d_i$；否则向 $S_j$ 内加入 $d_i$。如果有多位赛博佛祖的 $S_i$ 为空集，取编号最小的 $i$ 为你加功德。

现在作为电子资本家的你，想要功德无量。你想知道，最少再请来几位赛博佛祖，可以使得你的这些佛祖们 **源源不断地** 为你加功德。假设这个答案是 $s$（可以为 $0$），那么新的佛祖们的编号依次为 $(n+1) \sim (n+s)$。

**因为你是个资本家，有时候你不想请那么多佛祖**。所以你有许多组询问，对于一组 $l, r$，设 $f(l, r)$ 表示如果初始只有 $[l, r]$ 之间的佛祖，答案将会是多少，注意，每组询问相互独立，上一次添加的佛祖不会延续到以后的询问中。

为了避免太多的输出，你只需要输出： 

$$\sum\limits_{l=1}^n\sum\limits_{r=l}^n f(l,r)\times2^l$$

即可，答案对 $10^9 + 7$ 取模。

## 说明/提示

### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 0（10 pts）：$n \leq 10$，$m \leq 5$。
- Subtask 1（10 pts）：$n \leq 300$，$m \leq 10$。
- Subtask 2（15 pts）：$n \leq 1024$，$m \leq 10$。保证每个 $S_i$ 均不同。
- Subtask 3（15 pts）：$n \leq 10^4$。
- Subtask 4（10 pts）：每个 $S_i$ 均在 $2^m$ 种情况中等概率随机生成，$d_i$ 均在 $m$ 种情况中等概率随机生成。
- Subtask 5（40 pts）：无特殊限制。

对于所有数据，保证 $1 \leq n \leq 10^5$，$1 \leq m \leq 17$。

## 样例 #1

### 输入

```
4 3
1 010
2 001
3 000
3 001```

### 输出

```
52```

## 样例 #2

### 输入

```
5 4
1 1000
4 0100
1 0000
2 0001
2 0000```

### 输出

```
128```

# 题解

## 作者：wishapig (赞：9)

LCT 维护基环树森林的题似乎不常见，写篇题解记录一下。

### 题目大意

有 $n$ 个元素 $\operatorname{pair}(d,S)$，其中 $d\in[1,m]$，$S\subseteq\{1,2,\cdots,m\}$。

不断进行以下操作：

- 取出编号最小的 $S$ 为空的元素 $(d_*,S_*)$
- 把所有的元素的 $S$ 替换成 $S\oplus \{d_*\}$

问最少在末尾添加几个元素可以使操作无限进行。

对每个 $[1,n]$ 的子区间 $[l,r]$ 求出答案 $f(l,r)$，并输出 $\sum_{[l,r]}f(l,r)\cdot 2^l$ 对 $10^9+7$ 取模的结果。

$1\le n\le 10^5$，$1\le m\le 17$

---

先考虑单个询问。

状压集合，然后操作变成每个 $S$ 异或上 $2^{d_*}$。

由于是全局异或，显然只需要关心目前异或的总量。

并且，对一个总异或和为 $p$ 的局面，取出的元素是确定的（即编号最小的 $S=p$ 的元素），新局面是**唯一**的，如果取不出来那么操作结束，这是我们所需要避免的。因此可以对局面之间的转移**建图**（点集为 $\{0,1,\cdots 2^m-1\}$），用有向边刻画关系，形成一个**内向树或内向基环树森林**。

思考加一个元素的直观感受，显然新加元素的 $S$ 不会与之前的某个 $S$ 相同（因为永远不会用到它），因此新加一个元素可以看做**选择一个无出边的点，加一条出边**，且指向的点和它差恰好一个二进制位。

而操作能无限进行，就相当于**从 $0$ 出发能到一个环**。

现在可以考虑求解答案了：

- $0$ 处于一个内向基环树中，那么答案为 $0$。
- $0$ 不在内向基环树中：
  - $0$ 所在弱连通块大小 $\ge 2$，那么答案为 $1$。
  - $0$ 为一个孤点：
    - 若某个 $\operatorname{popcnt}=1$ 的点在一个内向基环树中，那么答案为 $1$。
    - 否则，答案为 $2$。

这样，枚举 $l$，然后从小到大枚举 $r$，维护一个并查集即可。

```c++
int Find(int x){ return fa[x]==x?x:fa[x]=Find(fa[x]); }
void Union(int x, int y){
	x=Find(x),y=Find(y);
	if (x!=y) fa[x]=y,siz[y]+=siz[x],cnt[y]+=cnt[x],S[y]|=S[x];
	cnt[y]--;
	flag|=cnt[y]==0 && S[y];
}
int main(){
	scanf("%d%d",&n,&m); pw[0]=1;
	for (int i=1; i<=n+1; i++) pw[i]=pw[i-1]*2%mod;
	for (int i=1; i<=n; i++){
		scanf("%d%s",&d[i],s);
		for (int j=0; j<m; j++) sta[i]|=(s[j]-'0')<<j;
	}
	for (int i=1; i<=n; i++){
		flag=0;
		for (int j=0; j<(1<<m); j++) vis[j]=0,fa[j]=j,cnt[j]=siz[j]=1,S[j]=__builtin_popcount(j)==1;
		for (int j=i; j<=n; j++){
			if (!vis[sta[j]]) Union(sta[j]^(1<<(d[j]-1)),sta[j]);
			int u=Find(0); vis[sta[j]]=1;
			if (siz[u]==1) ans=(ans+(flag?pw[i]:pw[i+1]))%mod;
			else if (cnt[u]) ans=(ans+pw[i])%mod;
			else break;
		}
	}
	printf("%d\n",ans);
}
```

然后考虑正解。

$l$ 从大到小扫描线，$S$ 相同的体现为修改出边指向的节点。

那么我只需要分别求出从 $l$ 开始加边，$0$ 以及每个 $\operatorname{popcnt}=1$ 的节点在某个内向基环树的**最小右端点**。

设第一部分为 $T_1$，第二部分的 $\min$ 为 $T_2$，那么：

- $r\in[l,T_2-1]$，同时 $[l,r]$ 内不存在与 $0$ 相关的连边，这部分贡献 $1$。
- $r\in [l,T_1-1]$ 这部分也贡献 $1$。

（注意我把上面答案为 $2$ 的情况拆成两部分贡献了）

于是考虑怎么维护右端点，每个点记录一个点权表示它在序列中的下标，那么相当于从某个起点出发走到环，经过点权的 $\max$（如果不会走到环那么记为 $n+1$）。

于是变成了一个类似加边，删边，查到根路径点权 $\max$ 的问题，唯一区别在于变成了基环树，我们强行改造 LCT 使它能维护这个问题。

对于每个弱连通块维护一个**有根树**结构：

- 若它为内向树，以无出边的那个点为根。
- 若它为内向基环树，以环上任意一个点为根，并记录其出边指向的节点，称这条边为**附加边**。

再具体讨论一下加删边的细节：

##### 删边：删除 $u$ 的出边

- $u$ 为所在弱连通块的根，那么直接把附加边去掉即可。
- $u$ 不为根，如果弱连通块为内向树则直接断掉，如果是内向基环树，要分是否为环边进行讨论。
  - 首先确定是否为环边，记附加边的另一端为 $x$，那么相当于判定 $u$ 是否在 $x$ 到根路径上，这个可以通过 `access(x),splay(x)` 打通 $x$ 到根的路径，然后从 $u$ 开始跳到所在 splay 的根，判是否与 $x$ 相同即可。
  - 如果是环边，那么断掉它，连上附加边，同时把**树根定为 $u$**。
  - 如果不是环边，那么正常断边。

##### 加边：加上 $u$ 的出边 $u\rightarrow t$

- $u,t$ 在同一个弱连通块内，则**把树根定为 $u$**，并记录附加边。
- 否则，正常连边，连边后整个弱连通块的根定为原 $t$ 所在弱连通块的根。

注意 `Link`，`Cut` 均有可能改变树根，因此在做完 LCT 操作后都要注意恢复正确的树根。.

最后一部分是查询：

- 先查出 $u$ 所在弱连通块的根，若其没有附加边则为内向树，返回 $n+1$。
- 否则，求出 $u$ 到根路径的点权 $\max$，和环上点权 $\max$，取大的那个返回即可。

时间复杂度为 $O(nm\log n)$。

代码有相当的细节，而且考场代码相当丑陋，省略了标准 LCT 操作。

```c++
inline void upd(int u, int x, int i){
	if (To[u]){
		if ((u==1 || To[u]==1) && w[u]) S.erase(w[u]); //w[u] 为点权，To[u] 为 u 的出边
		int rt=Findroot(u);
		if (u==rt) E[u]=0; //E 为附加边指向的另一个节点
		else if (!E[rt]){
			int tmp=Findroot(To[u]);
			Cut(u,To[u]); makeroot(tmp);
		} else {
			access(E[rt]),splay(E[rt]); int k=u;
			while (nroot(k)) k=fa[k];
			if (k==E[rt]) Cut(u,To[u]),Link(rt,E[rt]),E[rt]=0,makeroot(u);
			else {
				int tmp=Findroot(To[u]);
				Cut(u,To[u]); makeroot(tmp);
			}
		}
	}
	
	To[u]=x;
	if (Findroot(To[u])==Findroot(u)) makeroot(u),E[u]=To[u];
	else {
		int tmp=Findroot(To[u]);
		Link(u,To[u]); makeroot(tmp);
	}
	
	splay(u); w[u]=i; pushup(u);
	if (u==1 || To[u]==1) S.insert(w[u]);
}
inline int qry(int u){
	int rt=Findroot(u);
	if (!E[rt]) return n+1;
	else {
		access(u),splay(u); int ret=val[u]; //val 为维护出来的实链点权 max
		access(E[rt]),splay(E[rt]); ret=max(ret,val[E[rt]]);
		return ret;
	}
}
int main(){
	scanf("%d%d",&n,&m); pw[0]=1;
	for (int i=1; i<=n; i++) pw[i]=pw[i-1]*2%mod;
	for (int i=1; i<=n; i++){
		scanf("%d%s",&d[i],s);
		for (int j=0; j<m; j++) sta[i]|=(s[j]-'0')<<j;
	}
	for (int i=n; i>=1; i--){
		upd(sta[i]+1,(sta[i]^(1<<(d[i]-1)))+1,i);
		int tim=qry(1),k=n+1;
		for (int j=0; j<m; j++) k=min(k,qry((1<<j)+1));
		ans=(ans+1ll*pw[i]*(tim-i))%mod;
		int mn=min(k,(S.empty()?n+1:*S.begin()));
		ans=(ans+1ll*pw[i]*(mn-i))%mod;
	}
	printf("%d\n",ans);
}
```



---

## 作者：yinhy09 (赞：3)

# Elct Solution

## Preface

Elect + LCT = Elct.

## Solution

### 算法一

考虑在只有一次全局询问的时候怎么做。

我们维护一个集合 $Q$，初始为空集，$Q$ 同时受到题目中每个佛祖的电子木鱼的影响。那么我们发现，某个时刻，$S_i$ 为空集的充分必要条件是 $Q$ 为初始的 $S_i$，因为你考虑，敲一次木鱼相当于在二进制上进行异或某一位的操作，而异或的逆运算就是异或本身。

经过这样的转化，我们可以把佛祖 $i$ 被激活转化为 $Q$ 是一个特定的集合，而佛祖 $i$ 被激活后对 $Q$ 产生的影响也是可以 $\mathcal O(1)$ 计算的，这样我们就容易找到这个佛祖的后继佛祖，哦当然要取这些合法后继佛祖里最小的那个。

**因此，对每个重复的 $\bm Q_i$，我们只保留编号最小佛祖的 $\bm i$**。然后对每个佛祖 $i$，我们计算它的后继（也有可能不存在）。因为一个数只有一个后继，这不难使我们想到建一条**有向边**，转化为一定程度上的图论问题。同样地，我们对 $0$ 号佛祖以激活后的 $Q$ 为空集寻找后继，但是我们不以 $0$ 号节点为任何后继。

我们开始一定的分类讨论（接下来，我们只会举出一个能够证明我们结论的添加佛祖方式，但并不会详细论证为什么答案恰好等于这个值、不多 $1$ 也不少 $1$，读者自证不难）。

+ 如果 $0$ 号佛祖自身能走到环，答案是 $0$，因为这样已经形成了循环。
+ 如果 $0$ 号佛祖有出边，走不到环，答案是 $1$：
	+ 对于走到最后没有出边的那个佛祖，让它对应集合 $Q$，它的出边对应集合 $Q'$，我们可以添加一个对应集合 $Q'$、后继对应集合 $Q$ 的佛祖。
+ 如果 $0$ 号佛祖没有出边，且有至少一个对应集合为 $T$ **满足 $\bm{\lvert T \rvert = 1}$** 的佛祖 1) 能走到环或 2) 走到最后后继对应集合为空集，答案是 $1$：
	+ 添加一个对应集合 $Q$ 为空集、后继对应集合 $T$ 的佛祖。
+ 否则答案是 $2$：
	+ 一个简单的方式是新添加两个自循环的佛祖；如果所有有可能的对应集合为 $T$ **满足 $\bm{\lvert T \rvert = 1}$** 的佛祖均存在，那么我们选择一个 $T$，添加一个对应集合 $Q$ 为空集、后继对应集合 $T$ 的佛祖后，转化为「如果 $0$ 号佛祖有出边，走不到环」情况，答案为 $1 + 1 = 2$。

枚举所有询问暴力，复杂度 $\mathcal O(n^3 + nm)$。

### 算法二

我们想要把边全都建好然后优化......诶，等等，你会发现，因为根据 $[l, r]$ 的不同，「因此，对每个重复的 $Q_i$，我们只保留编号最小佛祖的 $i$」处的编号不同，其后继佛祖对应的集合也不相同，这就让我们感觉很 /oh！

所以我们想到对 $l$ 扫描线，这样保证每个 $Q_i$ 的最小性是一定的。假如有 $l \leftarrow l + 1$，相当于删去 $l$ 这个佛祖；那么我们**把 $\bm l$ 当做虚点**，将 $l$ 的出边改为下一个使得对应集合 $Q$ 和 $Q_l$ 相等的佛祖。

我们的问题就转化为了 $\mathcal O(n)$ 次删边，加边，维护上面的那个问题。接着思考一下，我们需要维护的操作好像就是看一些点能不能走到环。那就 LCT！

我们用 LCT 维护的是 splay 森林。每次加边的时候，如果不连通，那么直接 link；否则记录这个 splay 上有一个多出来的环边然后更新答案。这个联通块里一旦存在一个**在环上的 cut**，再把它加进来即可（需要维护原树的根不变，可以通过一定的 `findroot()` 实现；而这样我们就可以**维护有向边**）。

详细地描述这个过程，我们要对所有 $l$ 相等的询问分组进行扫描线，然后对于每个 $l$，$0$ 号佛祖有没有后继是简单计算的，然后只需要查询对于每个 $l$ 有哪些 $r$ 满足 $0$ 号佛祖 或 对应集合 $T$ 满足 $\lvert T \rvert = 1$ 的佛祖（最多只有 $m$ 个这样的佛祖能被激活，所以暴力 check 可以做到 $\mathcal O(nm\log n)$）能走到环 / 空集（**这里的实现有一定难度，我的做法是分两遍分别维护**），这个 $r$ 显然应该是 $\ge$ 某个能走到环路的可行佛祖的路径上的佛祖编号的最大值（为什么要求这个最大值？因为你的 $r$ 要满足能**走过一个完整的环才能进入循环**啊），也就是最大值的最小值。把这些值都计算出来后，经过简单的区间并集计算可以得到最后的答案。

时间复杂度 $\mathcal O(nm\log n)$。

## Code & Details

先放上 LCT：

```cpp
/* Link-cut Tree Powered by OIer @rui_er. thx/bx */

#define MAXN 100001
struct LinkCutTree {
	int fa[MAXN], val[MAXN], maxv[MAXN], tag[MAXN], son[MAXN][2];
	void clearAll() {
		memset(fa, 0, sizeof(fa));
		memset(maxv, 0, sizeof(maxv));
		memset(tag, 0, sizeof(tag));
		memset(son, 0, sizeof(son));
	}
	int get(int u) {
		if (son[fa[u]][0] == u) return 0;
		if (son[fa[u]][1] == u) return 1;
		return -1;
	}
	void connect(int u, int f, int tp) {
		fa[u] = f;
		if (tp >= 0) son[f][tp] = u;
	}
	void pushup(int u) {
		maxv[u] = std::max({maxv[son[u][0]], maxv[son[u][1]], val[u]});
	}
	void reverse(int u) {
		std::swap(son[u][0], son[u][1]), tag[u] ^= 1;
	}
	void pushdown(int u) {
		if (!tag[u]) return;
		if (son[u][0]) reverse(son[u][0]);
		if (son[u][1]) reverse(son[u][1]);
		tag[u] = 0;
	}
	void pushall(int u) {
		if (get(u) != -1) pushall(fa[u]);
		pushdown(u);
	}
	void rotate(int u) {
		int v = fa[u], w = fa[v], p = get(u), q = get(v), c = son[u][p ^ 1];
		connect(c, v, p), connect(v, u, p ^ 1), connect(u, w, q);
		pushup(v), pushup(u);
	}
	int splay(int u) {
		pushall(u);
		if (get(u) == -1) return u;
		for (int f; true; ) {
			f = fa[u];
			if (get(f) == -1) {
				rotate(u); return f;
			} else rotate(get(u) == get(f) ? f : u);
			f = fa[u];
			if (get(f) == -1) {
				rotate(u); return f;
			} else rotate(u);
		}
	}
	void access(int u) {
		for (int v = 0; u; v = u, u = fa[u])
			splay(u), son[u][1] = v, pushup(u);
	}
	void makeroot(int u) {
		access(u), splay(u), reverse(u);
	}
	int findroot(int u) {
		access(u), splay(u), pushdown(u);
		for(; son[u][0]; u = son[u][0]) pushdown(u);
		splay(u); return u;
	}
	void link(int u, int v) {
		int t = findroot(v);
		makeroot(u), fa[u] = v;
		makeroot(t);
	}
	void cut(int u, int v) {
		int t = findroot(v);
		makeroot(u), access(v), splay(v);
		fa[u] = son[v][0] = 0, pushup(v);
		makeroot(u), makeroot(t);
	}
	int query(int u, int v) {
		int t = findroot(u);
		makeroot(u), access(v), splay(v);
		int z = maxv[v]; makeroot(t);
		return z;
	}
} R;
```

其中，不同寻常的是：

+ $\text{splay}(u)$ 除了将 $u$ 旋转至其 splay 的根以外，同时附带查询 $u$ 所在 splay 的原根。
+ $\text{link}(u, v), \text{cut}(u, v)$ 均调用一定的 $\text{makeroot}$ 保证根不变。
+ $\text{query}(u, v)$ 查询 $u$ 到 $v$ 的路径上点权最大值。

接下来是三个经过大量简略和封装的函数：

```cpp
void addEdge(int u, int v) {
	if (u == R.findroot(v)) ex[u] = v;
	else R.link(u, v);
}
```

很好理解，如果 $u, v$ 在同一个联通块里就标记 $u$ 有一条到 $v$ 的边。

```cpp
void delEdge(int u, int v) {
	int t = R.findroot(u);
	if (t == u && ex[t] == v) {
		ex[u] = 0;
	} else if (ex[t]) {
		R.makeroot(t), R.access(ex[t]), R.splay(ex[t]);
		if (R.splay(u) == ex[t]) {
			R.cut(u, v), R.link(t, ex[t]), R.makeroot(u), ex[t] = 0;
		} else R.cut(u, v), R.makeroot(t);
	} else R.cut(u, v);
}
```

最抽象的实现细节之一。

+ 首先，如果被标记了就直接删除是很显然的。
+ 接着，如果有一条标记边，我们要看删掉之后要不要加标记边。
	+ 充分必要条件是 $u \rightarrow v$ 边在基环树的环上，可以转化为 $\text{split}(t, ex_t)$ 后 $u$ 点在 $ex_t$ 的 splay 子树内（想象一下，如果 $u$ 在环上，$v$ 肯定在环上；否则不一定）。
	+ 然后就用的上上面的带返回值的 $\text{splay}(u)$ 了，这里别忘了 link cut 完之后**把根变成 $\bm u$** 以及清空原标记。
+ 最后，如果不满足上述条件，直接 cut 即可。

```cpp
int maxId(int u) {
	if (!u || u > N) return N + 1;
	int t = R.findroot(u);
	if (!ex[t]) return N + 1;
	return std::max(R.query(u, t), R.query(u, ex[t]));
}
```

查询 $u$ 如果能走到环，环上的节点编号最大值。如果不合法为 $n + 1$。

## Postscript

GMOI 团员们曾经尝试过线段树分治，但是后来假了，无果。笔者同样坚信会有不带 $m$ 的做法，或许是 CF1588F 类根号重构，或许是真正的不带 $m$ 的 1log 或者 2log 做法。总之，欢迎数据结构爱好者来 GMOI 一起交流。

---

