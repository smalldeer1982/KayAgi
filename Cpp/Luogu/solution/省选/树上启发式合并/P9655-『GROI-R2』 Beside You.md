# 『GROI-R2』 Beside You

## 题目背景

記憶の森

始まりの謎 いつか

この未知の果てに告げ知らせて

——江口孝宏《Beside You》

## 题目描述

我相信所有读过这一段剧情的人都不想让别人也经历一样的痛苦，但是坦尼尔还是只能消失，对吗？

坦尼尔最后留下了一棵以 $1$ 为根的有根树，在树的每个结点上，都有一个记忆碎片。有的碎片表示着一个世界记忆的开始，而另外的碎片表示着一个世界记忆的终结。

这时，树上飞来了一只蝴蝶~~モリモリあつし~~。蝴蝶在树上飞舞的过程中，经过了一些结点。爱丽丝能确定蝴蝶经过的结点个数至少有 $2$ 个，但是她忘记了具体的点数。

爱丽丝发现，蝴蝶经过的所有点都是互相连通的。当她把目光朝向每一条经过点数大于 $1$ 的从连通块**深度最小的结点**通往**连通块的任意一个叶子结点**（一个点是连通块的叶子结点，当且仅当它在树上没有子结点，或者它在树上的任意子结点均不在该连通块内）的简单路径时，她发现这些路径上的记忆都是完整的。爱丽丝认为一条路径上的记忆是完整的，当且仅当这条路径上既没有出现一个世界的记忆**没开始就结束**（路径中途在没有未结束的记忆的时候，出现了表示记忆终结的碎片）的情况，也没有出现一个世界的记忆**开始之后没有终结**（路径结束之后还有没结束的记忆）的情况。

可惜她已经遗忘了蝴蝶经过了哪些点，所以你需要告诉她蝴蝶**最多**可能经过多少点。

**形式化题面**

给定一棵以 $1$ 为根的 $n$ 个节点的树 $T=(V,E)$，每个节点上的点权 $c_i$ 为一个**左括号或一个右括号**，节点编号为 $1\sim n$。

我们定义点集 $V'\subseteq V$ 合法，当且仅当 $|V'|>1$（**即 $V'$ 的大小大于 $1$**） 且 $\forall u,v \in V'$，从 $u$ 到 $v$ 的简单路径只经过 $V'$ 中的点。

同时我们定义 $E'\subseteq E$ 为能使得 $\forall u,v \in V'$，从 $u$ 到 $v$ 的简单路径，只经过 $E'$ 中的边的大小最小的边集。

定义一个合法点集 $V'$ 的根为 $V'$ 中深度最小的结点。

定义 $u$ 为合法点集 $V'$ 的叶子节点，当且仅当 $u$ 不是 $V'$ 的根，且满足 $v \in V', (u,v) \in E'$ 的 $v$ 的数量为 $1$。

求一个合法点集 $S$，**满足其根节点到其任意一个叶子的路径上，每个点的点权顺次相接为一个合法的括号序列**，并**最大化** $|S|$。

我们通过如下规则定义一个合法的括号序列：

- 空串（即长度为 $0$ 的串）是一个合法的括号序列。

- 若串 $\text{A,B}$ 都是合法的括号序列，则字符串 $\text{AB}$ （即将字符串 $\text{A}$ 与 $\text{B}$ 按顺序拼接起来）也是合法的括号序列。

- 若串 $\text{A}$ 是合法的括号序列，则字符串 $\text{(A)}$ 是一个合法的括号序列。

你需要输出符合要求的最大 $|S|$。

## 说明/提示

**样例解释**

![](https://s1.ax1x.com/2023/08/07/pPEj56K.png)

蝴蝶经过的最大合法点集 $S$ 为 $\{1,2,3\}$。

![](https://s1.ax1x.com/2023/08/07/pPEv90g.png)

蝴蝶经过的最大合法点集 $S$ 为 $\{1,2,3,5,7\}$。

**数据范围**

**本题采用捆绑测试**。

| $\text{Subtask}$ | $n\le$ | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $20$ |  | $5$ |
| $2$ | $3000$ |  | $20$ |
| $3$ | $5\times10^5$ | $\text{A}$ | $15$  |
| $4$ | $5\times10^5$ | $\text{B}$ |  $10$ |
| $5$ | $2\times10^5$ |  | $15$ |
| $6$ | $5\times10^5$ |  | $35$ |

特殊性质 $\text{A}$：保证树退化成一条链（不保证 $1$ 号节点为其一个端点）。

特殊性质 $\text{B}$：保证原树上任意结点到叶子的路径上右括号数量不少于左括号数量。

对于 $100\%$ 的数据满足 $1\le n\le 5\times 10^5$，$1\le u,v \le n$，$c_i$ 为 ``(`` 或 ``)``。

## 样例 #1

### 输入

```
3
())
1 2
1 3```

### 输出

```
3```

## 样例 #2

### 输入

```
8
()))())(
1 2
1 3
3 4
3 5
3 6
5 7
2 8```

### 输出

```
5```

# 题解

## 作者：do_while_true (赞：12)

是不是爆标了啊/yiw。

把每个点权值 $a_x$ `(` 看成 -1。`)` 看成 1。首先得到一个简单的 $\mathcal{O}(n^2)$ dp。$f_{x,i}$ 表示 $x$ 子树内到 $x$ 前缀和为 $i$ 的最多点数。如果 $a_x=1$ 对于儿子 $v$ 那么 $f_{x,i+1}\gets f_{x,i+1}+f_{v,i}$。否则 $f_{x,i-1}\gets f_{x,i-1}+f_{v,i}$。最后再将 $f_x$ 中有值的加上 $1$（也就是存在这种方案就把 $x$ 这个点算上）。如果 $a_x=1$ 且 $f_{x,1}$ 没值那么把 $f_{x,1}$ 设为 $1$。

```cpp
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
void dfs(int x,int fa){
	len[x]=1;
	for(auto v:eg[x])if(v!=fa){
		dfs(v,x);
		cmax(len[x],len[v]+1);
		if(a[x]==1){
			for(int i=0;i<=len[v];i++)
				f[x][i+1]+=f[v][i];
		}
		else{
			for(int i=1;i<=len[v];i++)
				f[x][i-1]+=f[v][i];
		}
	}
	for(int i=0;i<=len[x];i++)if(f[x][i])++f[x][i];
	if(a[x]==1&&!f[x][1])f[x][1]=1;
	cmax(ans,f[x][0]);
}
```

尝试长剖优化。首先是后缀非零位置加这个东西。可以再记一个 $t_{x,i}$ 表示要将 $f_{x,\geq i}$ 的非零位置加上 $t_{x,i}$。需要用到 $f$ 真实值的时候去更新（用多少更新多少）。也就是在短儿子往自己合并的时候把短儿子更新掉。也把自己用到的 $f$ 更新掉。然后轻儿子再合并上来。

$a_x=1$ 的时候 $f_x$ 就是其长儿子 $f_{son}$ 整体右移一位。而 $a_x=0$ 的时候是整体左移一位。也就是赋指针的时候可能会 $f_{son}=f_x-1$。所以分配空间的时候给 $f_x$ 分配两倍的最深深度大小的空间就行。

时间复杂度是 $\mathcal{O}(n)$。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n'
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n'
#define DE(fmt,...) fprintf(stderr, "Line %d : " fmt "\n",__LINE__,##__VA_ARGS__)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pll>vpll;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
const int N=3000010;
int n;
vi eg[N];
char str[N];
int a[N],len[N],son[N];
int buff[N],*f[N],*fp=buff; 
int buft[N],*t[N],*tp=buft;
int ans;
void dfs1(int x,int fa){
	len[x]=1;
	for(auto v:eg[x])if(v!=fa){
		dfs1(v,x);
		cmax(len[x],len[v]+1);
		if(len[v]>len[son[x]])son[x]=v;
	}
}
int top[N];
void remake(int x,int p){
	p=min(p,len[x]);
	int s=0;
	for(int i=top[x];i<=p;i++){
		s+=t[x][i];
		if(f[x][i])f[x][i]+=s;
		t[x][i]=0;
	}
	if(p+1<=len[x])
		t[x][p+1]+=s;
	top[x]=p+1;
}
void dfs2(int x,int fa){
	if(son[x]){
		f[son[x]]=f[x]+a[x];
		t[son[x]]=t[x]+a[x];
		dfs2(son[x],x);
		if(a[x]==-1){
			remake(son[x],1);
			f[son[x]][0]=t[son[x]][0];
		}
	}
	for(auto v:eg[x])if(v!=fa&&v!=son[x]){
		f[v]=fp+len[v]+1;fp+=2*len[v]+2;
		t[v]=tp+len[v]+1;tp+=2*len[v]+2;
		dfs2(v,x);
		if(a[x]==1){
			remake(v,len[v]);
			remake(x,len[v]+1); 
			for(int i=0;i<=len[v];i++)
				f[x][i+1]+=f[v][i];
		}
		else{
			remake(v,len[v]);
			remake(x,len[v]);
			for(int i=1;i<=len[v];i++)
				f[x][i-1]+=f[v][i];
		}
	}
	if(a[x]==1&&!f[x][1]){
		remake(x,1);
		f[x][1]=1;
		if(f[x][0])f[x][0]++;
		if(len[x]>=2)t[x][2]++,top[x]=0;
	}
	else t[x][0]++,top[x]=0;
	if(f[x][0])cmax(ans,f[x][0]+t[x][0]);
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n);
	scanf("%s",str+1);
	for(int i=1;i<=n;i++)a[i]=str[i]=='('?-1:1;
	for(int i=1,u,v;i<n;i++){
		read(u,v);
		eg[u].pb(v);eg[v].pb(u);
	}
	dfs1(1,0);
	f[1]=fp+len[1]+1;fp+=2*len[1]+2;
	t[1]=tp+len[1]+2;tp+=2*len[1]+2;
	dfs2(1,0);
	cout<<ans<<'\n';
    #ifdef do_while_true
//		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：_Fatalis_ (赞：8)

场下第二天切的 /wq

题面过于复杂，差评

## 简化题面

给定一颗括号树（即每个点都有一个括号）。

要求找到一个树上的最大子结构，使得这个子结构连通，且从这个结构的根（即选择的子结构在原树高度最低的节点）出发到达每一个叶子结点（除根之外所有度数不超过 $1$ 的节点）的链构成的括号序列合法。

![](https://s1.ax1x.com/2023/08/07/pPEv90g.png)

对于样例 2 而言，$\{1,2,3,5,7\}$ 这个子结构，根为 $1$，叶子分别为 $\{2,7\}$，对应的括号序列为 $\{\text{()},\text{()()}\}$，都是合法的括号序列。

可以发现是最大的符合要求的子结构。

## 题解正文

先观察部分分。有退化成链的部分分，于是思考如何在链上找最大结构。

于是我们发现，其实就是最大的合法括号序列。对于最大合法括号序列，我们可以进行 $O(n)$ dp 一遍即可。

那么，如果不是一条链，那么应该怎么做呢？

由特殊到一般，大体思路可以确定，是一个树上的 dp。

那么如何 dp 呢？

重新观察括号序列的要求，那么我们一个个满足。

考虑先找到每一个最大的形如 $(A)$ 的括号子树，之后再通过合并（我们可以在原来找到的子树下面接上另一个合法的子树即可集成 $A$ 的序列）找到形如 $AB$ 的括号子树。

那么，如何找到最大的形如 $(A)$ 的括号子树呢？

随意画一个符合条件的子树，发现其实就是根为 $($，叶子都是 $)$，且要求从所有的叶子节点到根都能满足合法。

注意到每个叶子结点都只会对应一个根满足合法性（或没有对应）。

那么，对于一个根，我们就能找到它所有可以对应它合法的叶子结点。中间寻找到所有叶子结点和根的最小连通图就是那个括号子树了（为什么是最小？因为如果在从叶子结点到根的路上再有分支，就会增加新的叶子，但我们知道新的叶子并不满足合法括号序列的要求）。

寻找以某个节点为根的最大括号子树例子如下。其中加粗的点为无关点，未加粗的点为根或叶子节点。

![](https://cdn.luogu.com.cn/upload/image_hosting/h6z9bvf1.png)

于是，问题转换为了求一些点的最小连通图。

先想想若用暴力 dfs 求这个最小连通图的情景（如上图的有颜色的划线）。

那么，结论就是相邻 dfs 访问到的两个（重要）点之间的距离，全部加起来距离的二分之一，就是图的大小减一了。

这个结论在树上显然成立，因为两点间简单距离唯一，每次算距离都会多算一次，如先前提到的图。

（在图上实际上也成立，实际上找到最短路径后构成的还是一棵树）

这样子，每个叶子节点都会带来一次计算，假设就算每个节点都当做根算了一遍，总时间复杂度为 $O(n\log n)$（$\log n$ 是 lca 带来的），均摊下来是 $O(\log n)$ 一个节点。

时间复杂度非常优秀（）听说可以用虚树离线实现 $O(n)$ 的做法（？）应该可以刷新最优解（因为下文的树形 dp 复杂度为 $O(n)$）。

话说回来，找到了括号子树，我们考虑处理答案之间的继承关系。

每个符合括号序列的子树接在更低的子树的叶子上都可以进行转移，如下图。

如果不是叶子节点，分两种：

1. 在树内不是叶子结点，那么连接之后必定不是合法的，因为相对低的根提供了新的 $($，必须要求后面对应到单独的 $)$。但那个子树后面一定没有对应的的 $)$，假设有就一定会被算在这个树内，假设没有就没有继承贡献。所以不能转移。

2. 不在子树内，那么就不会产生连接的可能。即没有贡献。

如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/pl4mz13j.png)

其中红色的子树挂在橙色的叶子上，可以连接起来，可以转移。

而蓝色并未挂在上面（即根节点父亲不是叶子），所以不能连接并转移。

那么考虑清楚转移了，剩下就是 coding time！

```cpp
// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>

const int maxn = 5e5 + 10;
char ch[maxn];
std::vector<int> G[maxn];
int upd[maxn];
std::stack<int> st;

int siz[maxn], son[maxn], dep[maxn], last[maxn], fa[maxn];
void dfs1(int u, int f) {
    if (ch[u] == '(') st.push(u), last[u] = u;
    else {
        if (st.empty()) upd[u] = -1;
        else upd[u] = st.top(), st.pop();
    }

    son[u] = -1; siz[u] = 1; fa[u] = f;
    for (int v : G[u]) {
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1;
        dfs1(v, u);
        siz[u] += siz[v];
        if (son[u] == -1 || siz[v] > siz[son[u]]) son[u] = v;
    }

    if (ch[u] == '(') st.pop();
    else if (upd[u] != -1) st.push(upd[u]);
}

int top[maxn];
void dfs2(int u, int tp) {
    top[u] = tp;
    if (son[u] == -1) return;
    dfs2(son[u], tp);
    for (int v : G[u]) {
        if (v != fa[u] && v != son[u]) {
            dfs2(v, v);
        }
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] > dep[top[v]])
            u = fa[top[u]];
        else
            v = fa[top[v]];
    }
    return dep[u] > dep[v] ? v : u;
}

int dis(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

int sizz[maxn];
void dsiz(int u) {
    if (upd[u] != -1 && upd[u] != u) {
        // writeln(u, upd[u]);
        sizz[upd[u]] += dis(last[upd[u]], u);
        last[upd[u]] = u;
    }
    for (int v : G[u]) {
        if (v != fa[u]) {
            dsiz(v);
        }
    }
}

int f[maxn];
void dp(int u) {
    for (int v : G[u]) {
        if (v != fa[u]) dp(v);
    }
    if (ch[u] == '(') {
        int up = upd[fa[u]];
        if (up > 0) f[up] += f[u];
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    scanf("%s", ch + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        read(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    memset(upd, -1, sizeof(upd));
    memset(last, -1, sizeof(last));
    dfs1(1, 1);
    dfs2(1, 1);
    dsiz(1);
    for (int i = 1; i <= n; i++) {
        if (last[i] != -1 && last[i] != i) {
            // writeln(last[i]);
            // writeln(i, upd[last[i]], last[i]);
            sizz[upd[last[i]]] += dis(upd[last[i]], last[i]);
            sizz[upd[last[i]]] /= 2;
            sizz[upd[last[i]]]++;
            f[upd[last[i]]] = sizz[upd[last[i]]];
            // writeln(i, sizz[i]);
        }
    }
    dp(1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, f[i]);
    }
    writeln(ans);
    return 0;
}
```

考场上观察到了树形 dp，可惜时间不太够，并未想清楚如何独立的转移，下次可以在考虑 dp 的时候优先考虑怎样孤立状态并连接状态。

做法挺优秀的（？）抢了最优解 387ms，可能后面的人有更好的 $O(n)$ 可以做吧，看啥时候有人能超过我（）

---

## 作者：qijianci (赞：7)

比较暴力的一种做法，简单易懂。

首先我们容易得到一个 $O(n^2)$ 的暴力来求出以每个节点为根的最大联通块。

考虑自下而上递推的优化这个过程。

为方便起见我们下面用 $1$ 表示左括号，用 $0$ 表示右括号。

若当前节点为 $1$ ：

> 若儿子为 $1$，则当前节点与儿子构成的最大连通块下方的 $0$ 节点构成连通块。
> 
> 若儿子为 $0$，则当前节点与儿子下方的连通块可直接并起来。

若当前节点为 $0$：

> 那么不用操作等上方的节点来更新它即可。

举个例子

![](https://cdn.luogu.com.cn/upload/image_hosting/h75u10e9.png)

此时整个树的根节点为 $1$，它的右儿子为 $1$，那么它可以与红连通块下方的 $0$ 构成连通块。它的左儿子为 $0$,那么它可以与左儿子下方的黄联通块合并。

最后构成的就是这样一个紫色的大连通块。

![](https://cdn.luogu.com.cn/upload/image_hosting/cxe3v4xh.png)

具体实现我们可以用三个数组分别记录与当前连通块可以合并的联通块，当前联通块不算上合并连通块的叶子节点，当前联通块下的 $0$ 节点。

转移的时候若儿子为 $0$ 节点就直接放入叶节点集合，并合并下方连通块和记录下方 $0$ 节点。若儿子为 $1$ 节点就找儿子连通块和与儿子联通块合并的块下方的 $0$ 节点放入叶节点集合，并合并下方连通块和记录下方 $0$ 节点。

容易证明这样每个节点只会被当作叶节点放入一次。

最后每个节点答案就是叶节点与自身构成的联通块大小加上与之合并的连通块大小。

算答案的部分可用类似建虚树的方法解决。

复杂度找叶节点部分 $O(n)$,算答案 $O(n \log n)$。

所以总复杂度 $O(n \log n)$。

下面是代码，细节不懂的可以看注释。

```
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,f[N],a[N],fa[N],ans;
int dfn[N],dfc,dep[N],st[N<<2][21],pos[N],num;
string s;
vector<int>e[N];
vector<int>t1[N],t2[N],t3[N];
\\t1表示的是与当前联通块可以合并的连通块
\\t2表示的是当前联通块下的0节点
\\t3表示的是当前联通块的叶子节点
int Min(int x,int y){return dep[x]<dep[y]?x:y;}
int lca(int x,int y){
	x=pos[x],y=pos[y];
	if(x>y)swap(x,y);
	int k=__lg(y-x+1);
	return Min(st[x][k],st[y-(1<<k)+1][k]);
}
bool v[N];
void calc(int x,int now){
	v[now]=true;
	t3[x].push_back(now);
    \\放入叶节点集合
	for(auto u:e[now]){
		if(u==fa[now])continue;
		if(!a[u])t2[x].push_back(u);
        \\记录下方的0节点
		else if(t3[u].size())t1[x].push_back(u);
        \\与下方合并
	}
}
void sol(int x,int now){
	for(auto u:t2[now])calc(x,u);
	for(auto u:t1[now])sol(x,u);
}
void dfs(int x){
	st[pos[x]=++num][0]=x;
	dfn[x]=++dfc,dep[x]=dep[fa[x]]+1;
	for(auto u:e[x]){
		if(u==fa[x])continue;
		fa[u]=x,dfs(u),st[++num][0]=x;
		if(a[x]){
			if(a[u])sol(x,u);
			else calc(x,u);
		}
	}
}
int c[N];
bool cmp(int x,int y){return dfn[x]<dfn[y];}
void gtans(int x){
	for(auto u:e[x]){
		if(u==fa[x])continue;
		gtans(u);
	} int cnt=0;
	if(t3[x].empty())return;
	for(auto u:t1[x])f[x]+=f[u];
    \\记得加上合并的联通块的答案
	for(auto u:t3[x])c[++cnt]=u;
	c[++cnt]=x,sort(c+1,c+1+cnt,cmp);
	for(int i=cnt;i>1;--i)c[++cnt]=lca(c[i],c[i-1]);
	sort(c+1,c+1+cnt,cmp);
	for(int i=2;i<=cnt;++i){
		int L=lca(c[i-1],c[i]);
		f[x]+=dep[c[i]]-dep[L];
	} ans=max(ans,++f[x]);
    \\类似建虚树算答案
}
signed main(){
	ios::sync_with_stdio(false);
	int i,j,k,l,r,x,y,z;
	cin>>n>>s;
	for(i=0;i<s.size();++i)a[i+1]=(s[i]=='(');
	for(i=2;i<=n;++i){
		cin>>x>>y;
		e[x].push_back(y);
		e[y].push_back(x);
	} dfs(1);
	for(j=1;(1<<j)<=num;++j)
		for(i=1;i+(1<<j)-1<=num;++i)
			st[i][j]=Min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	gtans(1),printf("%d\n",ans);
	return 0;
}
```

---

## 作者：lsj2009 (赞：6)

## Problem

给定一棵以 $1$ 为根的 $n$ 个节点的树 $T=(V,E)$，每个节点上的点权 $c_i$ 为一个**左括号或一个右括号**，节点编号为 $1\sim n$。

我们定义点集 $V'\subseteq V$ 合法，当且仅当 $|V'|>1$ 且 $\forall u,v \in V'$，从 $u$ 到 $v$ 的简单路径只经过 $V'$ 中的点。

同时我们定义 $E'\subseteq E$ 为能使得 $\forall u,v \in V'$，从 $u$ 到 $v$ 的简单路径，只经过 $E'$ 中的边的大小最小的边集。

定义一个合法点集 $V'$ 的根为 $V'$ 中深度最小的结点。

定义 $u$ 为合法点集 $V'$ 的叶子节点，当且仅当 $u$ 不是 $V'$ 的根，且满足 $v \in V', (u,v) \in E'$ 的 $v$ 的数量为 $1$。

求一个合法点集 $S$，**满足其根节点到其任意一个叶子的路径上，每个点的点权顺次相接为一个合法的括号序列**，并**最大化** $|S|$。


你需要输出符合要求的最大 $|S|$。

$n\le 5\times 10^5$。

## Solution

感谢 @[ducati](/user/87064) 巨佬的帮助。

套路地，我们记 ``(`` 为 $1$ 且 ``)`` 为 $-1$，并设 $s_u$ 表示为根节点到 $u$ 节点上点权之和。

那么容易发现的是点 $u$ 到点 $v$（这里默认 $u$ 是 $v$ 的祖先节点）路径上括号匹配合法当且仅当 $s_v-s_{fa_u}=0$ 且 $\nexists x\in(u,v)$ 使得 $s_x-s_{fa_u}<0$ 同时要有 $c_u,c_v$ 分别为左、右括号。我们称上述条件为“优秀关系”。

- 证明：对于前者，保证的是路径上左括号数量必然等于右括号数量；对于后者，保证的是路径上不存在 ``())`` 这种右括号过多的情况。则对于每个右括号都存在一个唯一的左括号与其对应。

那么我们不妨把所有满足“优秀关系”的 $u,v$ 丢到同一个集合里。

考虑如何实现。首先我们考虑记录离 $v$ 最近的满足 $s_{fa_u}=s_v$ 且 $s_u$ 为左括号的节点 $u$，然后将两者连一条边。

为什么这样做？

首先，“连接”这一操作是具有传递性的，即我们已知 $u,v$ 在同一个集合，$v,w$ 在同一个集合，那我们就可以得到 $u,v,w$ 在同一个集合。

其次，考虑“优秀关系”的第二个条件，由于单调性的原因，如果 $(u,v)$ 不满足条件，那么一个离 $v$ 更远的点 $w$ 就更不可能满足条件了。

- 证明：设节点 $x\in (u,v)$ 使得 $s_x-s_{fa_u}<0$，因为 $x\in (u,v)$ 且 $(u,v)\subseteq (v,w)$ 同时 $s_{fa_u}=s_{fa_w}$ 所以 $s_x-s_{fa_w}<0$ 且 $x\in (v,w)$。

至于如何判断点对 $(u,v)$ 是否满足第二个条件，树上倍增一下即可。

这样，所有满足“优秀条件”的 $u,v$ 都在同一集合内。

考虑最开始的问题，我们对每个集合求在树上能覆盖其的最小连通块，对所有连通块大小的最大值即为所求。

至于树上能覆盖其的最小连通块，我们先放上代码：

```cpp
bool cmp(const int &u,const int &v) {
	return dfn[u]<dfn[v];
}
int solve(vector<int> vec) {
	int last=0; tot=0;
	sort(vec.begin(),vec.end(),cmp);
	for(auto x:vec) {
		t[++tot]=x;
		if(last)
			t[++tot]=lca(last,x);
		last=x;
	}
	sort(t+1,t+tot+1,cmp);
	tot=unique(t+1,t+tot+1)-t-1;
	int ans=0;
	rep(i,2,tot) {
		int u=lca(t[i-1],t[i]);
		ans+=d[t[i]]-d[u];
	}
	return ans+1;
}
```

可以从三个角度进行理解：

- 相当于我们每次合并两个最接近的节点（两节点之间没有其他节点）变成一个节点，然后计算。
- 相当于在计数时进行容斥，可以参考 P2336。
- 相当于我们对于每个集合建虚树，然后求虚树的大小。

但是，结束了吗？我们考虑下面的一组数据：

```
4
()()
1 2
2 3
3 4
```

符合条件的点集应为 $\{1,2,3,4\}$ 恰为一条链，括号序列为 ``()()``。但是我们求出的点集却为：$\{1,2\}\{3,4\}$。

为什么？因为我们计算时对于合法括号序列中 $\text{AB}$ 这种情况并没有考虑。

至于如何处理，在做一遍树上 $\text{dp}$ 即可，具体的，自上而下枚举每一个节点，设 $ans_v$ 为 $v$ 节点为根时当前的答案，那么对于其父节点 $u$ 如果 $s_u$ 为右括号、$s_v$ 为左括号且 $u,v$ 分别为一个合法点集的叶子和根节点，则令 $ans_{r_u}\gets ans_{r_u}+ans_v$，其中 $r_u$ 为 $u$ 所在合法点集的根。

至此，问题得到完美解决，复杂度 $\Theta(n\log n)$。

## Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=5e5+5;
int head[N],len;
struct node {
	int to,nxt;
}; node edge[N<<1];
void add_edge(int u,int v) {
	edge[++len]={v,head[u]}; head[u]=len;
}
int c[N],d[N],last[N*2],fa[N],f[N][20],g[N][20],n;
int dfn[N],p;
bool used[N];
char s[N];
bool check(int u) {
	if(!last[c[u]+n])
		return false;
	int res=INF,v=last[c[u]+n]; u=f[u][0];
	per(i,19,0) {
		if(d[f[u][i]]>=d[v])
			res=min(res,g[u][i]),u=f[u][i];
	}
	return res>=c[v];
}
void dfs(int u,int from) {
	c[u]=c[from]+(s[u]=='('? 1:-1);
	f[u][0]=from; g[u][0]=c[u];
	d[u]=d[from]+1;
	dfn[u]=++p;
	rep(i,1,19) {
		f[u][i]=f[f[u][i-1]][i-1];
		g[u][i]=min(g[u][i-1],g[f[u][i-1]][i-1]);		
	}
	if(check(u))
		fa[u]=last[c[u]+n],used[fa[u]]=used[u]=true;
	int tmp;
	if(s[u]=='(') {
		tmp=last[c[from]+n];
		last[c[from]+n]=u;
	}
	for(int i=head[u];i;i=edge[i].nxt) {
		int v=edge[i].to;
		if(v!=from)
			dfs(v,u);
	}
	if(s[u]=='(')
		last[c[from]+n]=tmp;
}
int ans[N];
void dfs1(int u,int from) {
	for(int i=head[u];i;i=edge[i].nxt) {
		int v=edge[i].to;
		if(v!=from) {
			dfs1(v,u);
			if(used[u]&&used[v]&&s[u]==')'&&s[v]=='(')
				ans[fa[u]]+=ans[v];
		}
	}
}
vector<int> vec[N];
int lca(int u,int v) {
	if(d[u]>d[v])
		swap(u,v);
	per(i,19,0) {
		if(d[f[v][i]]>=d[u])
			v=f[v][i];
	}
	if(u==v)
		return u;
	per(i,19,0) {
		if(f[u][i]!=f[v][i])
			u=f[u][i],v=f[v][i];
	}
	return f[u][0];
}
bool cmp(const int &u,const int &v) {
	return dfn[u]<dfn[v];
}
int t[N],tot;
int solve(vector<int> vec) {
	int last=0; tot=0;
	sort(vec.begin(),vec.end(),cmp);
	for(auto x:vec) {
		t[++tot]=x;
		if(last)
			t[++tot]=lca(last,x);
		last=x;
	}
	sort(t+1,t+tot+1,cmp);
	tot=unique(t+1,t+tot+1)-t-1;
	int ans=0;
	rep(i,2,tot) {
		int u=lca(t[i-1],t[i]);
		ans+=d[t[i]]-d[u];
	}
	return ans+1;
}
signed main() {
	scanf("%d",&n);
	scanf("%s",s+1);
	rep(i,2,n) {
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	rep(i,1,n)
		fa[i]=i;
	dfs(1,0);
	rep(i,1,n)
		vec[fa[i]].push_back(i);
	rep(i,1,n) {
		if(vec[i].size()!=1)
			ans[i]=solve(vec[i]);
	}
	dfs1(1,0);
	int res=0;
	rep(i,1,n)
		res=max(res,ans[i]);
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：xieziheng (赞：5)

好题。这道题其实不难，可惜赛时没做出来。

首先注意到到对于以点 $x$ 为根的点集的最大值为 $x$ 和其子树中所有能和其拼接成合法括号序列的连通块的大小。所以可以暴力枚举每个点，搜它的子树，找到所有满足条件的点，算一下连通块大小，再取 $\max$，可以得到 $25$ 分。

考虑一个序列的括号匹配：从左向右扫，遇到左括号加到栈里，遇到右括号和栈顶匹配并弹栈。

类似的，在这里，搜的时候可以遇到左括号塞进栈里，右括号匹配弹栈。然后在一个点搜完后为了消除它对它兄弟的影响，所以如果是左括号就弹掉，如果是右括号且匹配上了再插回去。

于是可以得到每个节点向上匹配到的祖先。然后考虑每个节点所在的最大集合的大小：初始只包含自己，然后和祖先匹配，将路径上的所有点加入集合，并和祖先上的点合并。但是这样会有一点问题，就是 $()()$ 这样的括号序列中间不会合并。考虑括号序列的结构：$(A)$ 或 $AB$，对于第一种是不需要处理的，这是由于两端的匹配括号已经覆盖了全部路径，但是第二种情况需要处理。记 $f_x$ 为 $x$ 匹配上的点。则如果 $f_x$ 的父亲也可以继续向上匹配，说明这是一个 $AB$ 型的括号序列，于是把 $f_x$ 合并到 $f_x$ 的父亲上。合并可以启发式合并。

然后是快速计算树上连通块的大小。直接给出结论：按照 dfs 序从小到大排，则大小为 $\frac {\sum_{\operatorname{cyc}} {\operatorname{dis}(a_i,a_{i+1})}} 2 +1$，这是个经典结论，可以参见 $P3320$ 和 $CF372D$。

时间复杂度线性对数。

代码：

```cpp
#include <bits/stdc++.h>
#define il inline
using namespace std;
const int N=5e5+5;
int n,fa[N][20],de[N],lg[N],dfn[N],cnt,st[N],top,to[N],ans;char s[N];
vector<int> e[N],g[N];
il void add(int x,int y){e[x].push_back(y);}
int f[N],siz[N];
int find(int x){return x==f[x]?x:f[x]=find(f[x]);}
il void Union(int x,int y){
    x=find(x),y=find(y);
    if(x==y) return ;
    if(siz[x]<siz[y]) swap(x,y);
    f[y]=x,siz[x]+=siz[y];
    for(int u:g[y]) g[x].push_back(u);
}
void dfs(int x,int fath){
    if(s[x]=='(') st[++top]=x;
    else{
        if(!top) to[x]=-1;
        else to[x]=st[top--];
    }
    fa[x][0]=fath,de[x]=de[fath]+1,dfn[x]=++cnt;
    for(int i=1;i<=19;++i) fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int y:e[x]) if(y!=fath) dfs(y,x);
    if(s[x]=='(') --top;
    else if(to[x]>0) st[++top]=to[x];
}
il int lca(int x,int y){
    if(de[x]<de[y]) swap(x,y);
    while(de[x]>de[y]) x=fa[x][lg[de[x]-de[y]]];
    if(x==y) return x;
    for(int i=19;i>=0;--i) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
il int dis(int x,int y){return de[x]+de[y]-2*de[lca(x,y)];}
void dfs1(int x,int fath){
    for(int y:e[x]) if(y!=fath) dfs1(y,x);
    int y=to[x];if(y<=0) return ;
    Union(y,x);
    if(to[fa[y][0]]>0) Union(fa[y][0],y);
}
int x,y,cur;
int main(){
    //freopen("P9655_8.in","r",stdin);
    scanf("%d%s",&n,s+1);
    for(int i=2;i<=n;++i) scanf("%d%d",&x,&y),add(x,y),add(y,x),lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;++i) f[i]=i,siz[i]=1,g[i].push_back(i);
    dfs(1,0),dfs1(1,0);
    for(int i=1;i<=n;++i){
        if(find(i)!=i) continue;
        sort(g[i].begin(),g[i].end(),[](int x,int y){return dfn[x]<dfn[y];});
        cur=0;
        for(int j=1;j<g[i].size();++j) cur+=dis(g[i][j-1],g[i][j]);
        cur+=dis(*(--g[i].end()),g[i][0]),ans=max(ans,cur/2+1);
    }
    if(ans==1) ans=0;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：min_inf (赞：5)

首先每个右括号匹配到的左括号是固定的，可以用并查集找到 ~~（但是这里是我调的最久的）~~。

对于每个右括号，向匹配到的左括号的父亲连边，重新建一个森林，容易想到转化为每颗树在原树上构成的连通块大小。

但是这样容易出问题：

![](https://cdn.luogu.com.cn/upload/image_hosting/g2d7oyud.png)

所以对根的每个儿子跑一下即可。

时间复杂度 $O(n \log n)$。[场上的代码](https://www.luogu.com.cn/paste/tu636lef)，很长常数还贼大但是有一大半代码其实都是没用的。貌似能够优化到 $O(n)$，不过没啥必要。

---

## 作者：vegetable_king (赞：4)

[可能更好的阅读体验](https://yjh965.github.io/post/p9655-groi-r2-beside-you-ti-jie/)

无脑 $O(n \log^2 n)$ 做法，但是跑的比官方题解 $O(n \log n)$ 快。

先套路的设 $\texttt{"("}$ 为 $1$，$\texttt{")"}$ 为 $-1$，那么一条路径合法，当且仅当从上（深度小的一端）至下（深度大的一端）的所有前缀和都 $\ge 0$，同理，从下至上的所有前缀和都 $\le 0$。

考虑从下至上树形 DP，设 $f_{u, i}$ 表示 $u$ 子树内，$u$ 到每个叶子的路径上的权值和都恰好为 $i$ 的最大连通块的大小。根据上面的结论，$i \le 0$ 时这才是一个合法的状态。

可以推出转移方程：

$$f_{u, i + a_u} \gets 1 + \sum_v f_{v, i}$$

$$f_{u, a_u} \gets 1$$

所有状态初始设为 $0$。

暴力转移是 $O(\sum_u sz_u)$ 的，可以卡到 $O(n^2)$，我们考虑优化。稍微将转移方程进行变形，得：

$$f'_{u, i} \gets \sum_v f_{v, i}$$

$$f'_{u, 0} \gets 0$$

$$f_{u, i + a_u} = 1 + f'_{u, i}$$

可以发现，我们只需要支持单点修改、快速合并每棵子树的集合、整体加、以及整体平移即可快速维护 $f$。

因为我们要支持合并，所以考虑树上启发式合并。对于每个 $f_u$ 都开一个 `map` 维护非 $0$ 的位置，合并时将小的集合暴力合并到大的集合里，而整体加、整体平移可以打两个 tag 分别维护。最后将平移后下标 $> 0$ 的所有位置都删掉即可。

时间复杂度 $O(n \log^2 n)$，跑不满，可以通过。

注意合并与修改时对 tag 的处理。

```cpp
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;
class edge{
	public:
		edge(int x, int y, int z, int zz){v = x, w = y, c = z, nxt = zz;}
		int v, w, c, nxt;
};
class graph{
	private:
		vector<int> head;vector<edge> e;
	public:
		void init(int n){head.clear(), e.clear();for (int i = 0;i <= n;i ++) head.emplace_back(-1);}
		graph(){}graph(int n){init(n);}
		inline int addedge(int u, int v, int w = 0, int c = 0){e.emplace_back(v, w, c, head[u]), head[u] = e.size() - 1;return e.size() - 1;}
		inline int add2edge(int u, int v, int w = 0){int tmp = addedge(u, v, w);addedge(v, u, w);return tmp;}
		inline int addfedge(int u, int v, int w, int c){int tmp = addedge(u, v, 0, c);addedge(v, u, w, -c);return tmp;}
		inline int& h(int u){return head[u];}
		inline edge& operator[](int i){return e[i];}
}G;
const int N = 500005;map<int, int> f[N];
int n, a[N], mv1[N], mv2[N], ans;char ch[N];
void dp(int u, int fa){
	for (int i = G.h(u);i != -1;i = G[i].nxt){
		int v = G[i].v;if (v == fa) continue;
		dp(v, u);if (f[u].size() < f[v].size())
		swap(f[u], f[v]), swap(mv1[u], mv1[v]), swap(mv2[u], mv2[v]);
		for (auto [x, y] : f[v]){
			int p = x - mv1[v] + mv1[u], pp = y + mv2[v];
			if (f[u].find(p) != f[u].end()) f[u][p] += pp;
			else f[u][p] = pp - mv2[u];
		}f[v].clear();
	}
	if (f[u].find(mv1[u]) == f[u].end())
	f[u][mv1[u]] = -mv2[u];mv1[u] -= a[u], mv2[u] ++;
	if (f[u].find(mv1[u]) != f[u].end())
	ans = max(ans, f[u][mv1[u]] + mv2[u]);
	else f[u][mv1[u]] = -mv2[u];
	while (f[u].size()){auto ptr = f[u].end();ptr --;
		if (ptr -> first - mv1[u] > 0) f[u].erase(ptr);
		else break;
	}
}
int main(){scanf("%d%s", &n, ch + 1), G.init(n);
	for (int i = 1;i <= n;i ++) a[i] = ch[i] == '(' ? 1 : -1;
	for (int i = 1, u, v;i < n;i ++) scanf("%d%d", &u, &v), G.add2edge(u, v);
	dp(1, 0), printf("%d", ans);
}
```

---

## 作者：not_clever_syl (赞：3)

首先考虑 dp。

可以发现把 `(` 看成 `-1` , `)` 看成 `+1`，就相当于要最大化一个树上的连通块 $|S|$，且 $S$ 的根到所有的叶子的权值和为 $0$。

考虑设 $dp_{i,j}$ 表示当前连通块的根为 $i$，根到所有叶子的权值和为 $j$ 时的最大的 $|S|$ 的大小。显然 $j<0$ 时，当前的括号序列一定是 `(...`，此时最左边的左括号在以后一直都不能匹配。

可以推出转移式：
$$
dp_{i,j}=1+\sum\limits_{k \in son(i)}{dp_{k,j-c_i}}
$$

其中 $c_i$ 表示第 $i$ 个结点的权值( `+1` 或 `-1` ，$son(i)$ 表示以 $1$ 为根时 $i$ 的所有儿子。

答案即为 $\max\limits_{i=1}^{n}(dp_{i,0})$。

这样做的时间复杂度是 $O(n^2)$，考虑优化。

发现这个转移式可以树上启发式合并。

维护 $n$ 个 map, 记录两个懒标记 $add$ 和 $sum$，$add$ 表示存储在 $j$ 位置的实际上是 $dp_{i,j-add}$，$sum$ 表示取出来的结果需要在加上 $sum$。

具体细节可以参考代码。

这个做法的复杂度是启发式合并的 $O(n \log n)$ 乘上 map 的 $O(\log n)$，即 $O(n \log^2 n)$。

以下是部分代码。

```cpp
#define MAXN 500005
int n;
char ch[MAXN];
vector<int>e[MAXN];
int ans=0;
struct ds{
	int add,sum;
	map<int,int>mp;
	int get(){
		if(!mp.count(-add))return 0;// 代码中不存在的位置为0
		return mp[-add]+sum;
	}
	void clear_ne(){
		while(!mp.empty()&&mp.begin()->first+add<0)mp.erase(mp.begin());//清除负数
	}
	void merge(ds&x){
		if(mp.size()<x.mp.size()){
			swap(add,x.add);
			swap(sum,x.sum);
			swap(mp,x.mp);
		}
		for(auto it:x.mp){
			int t=it.first+x.add-add;
			if(!mp.count(t))mp[t]=-sum;//注意在这个map里不存在这个下标时，要减去sum(因为最后拿结果的时候要加上)
			mp[t]+=it.second+x.sum;
		}
		x.mp.clear();
	}
	void create(){
		if(!mp.count(-add))mp[-add]=-sum;//把0处设为0，因为转移时用懒标记
	}
	void print(){//调试用的
		for(auto it:mp){
			cout<<it.first+add<<' '<<it.second+sum<<endl;
		}
	}
};
ds f[MAXN];
void dfs(int u,int fa){
	for(auto v:e[u]){
		if(v!=fa){
			dfs(v,u);
			f[u].merge(f[v]);
		}
	}
	f[u].create();
	f[u].add+=(ch[u]==')')?1:-1;//要先改add再清负数
	f[u].clear_ne();
	++f[u].sum;
	ans=max(ans,f[u].get());
}
```

---

## 作者：yxzy4615 (赞：2)

~~又是线性，这场线性场。~~

首先，可以找到一种合法的 $S$ 的刻画方案，定义每个点 $i$ 向上可以找到的第一个满足其完成括号匹配的节点记为 $f_i$，父亲记为 $fa_i$。

那么对于一个合法的根 $u$ 和叶子 $v$，必然可以用 $v \rightarrow f_v \rightarrow fa_{f_v} \rightarrow \dots \rightarrow f_x=u$ 的路径刻画。

于是就可以将这种边连起记为一个点集，问题转化为对于节点互不相同且总数 $\leq n$ 的 $k$ 个点集，每个点集的权值定义为包含其所有节点的最小连通块点数，求最大的点集权值。这个是虚树的经典运用之一，但由于节点互不相同，排序部分可以使用桶排，LCA部分使用 $O(n)-O(1)$ 的~~四毛子等~~算法即可做到线性复杂度。

具体细节可以参照代码，由于笔者水平太菜，实现的是树剖（时间复杂度 $O(n\log n)$）。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int n,d[N],fa[N],sz[N],zs[N],top[N],dfn[N],ct;
char a[N];
vector<int>to[N],sr[N],tp;
void dfs(int x,int fat){
    dfn[++ct]=x;//桶排
    fa[x]=fat,d[x]=d[fat]+1;sz[x]=1;
    for(int y:to[x]) if(y^fat){
        dfs(y,x);sz[x]+=sz[y];
        if(sz[y]>sz[zs[x]]) zs[x]=y;
    }
}
void dfs2(int x,int t){//剖
    top[x]=t;if(zs[x]) dfs2(zs[x],t);
    for(int y:to[x]) if(y!=zs[x]&&y!=fa[x]) dfs2(y,y);
}
int lca(int x,int y){
    while(top[x]^top[y]){
        if(d[top[x]]<d[top[y]]) swap(x,y);
        x=fa[top[x]];
    }return d[x]<d[y]?x:y;
}
int stk[N],T,f[N];
void dfs3(int x){//树上模拟栈+撤销求f
    if(a[x]=='(') stk[++T]=x;
    else if(T) f[x]=stk[T],T--;
    for(int y:to[x]){
        if(y==fa[x]) continue;
        dfs3(y);
    }
    if(a[x]=='(') T--;
    else if(f[x]) stk[++T]=f[x];
}
int ans,s[N],v[N],pr[N];
void dfs4(int x){v[x]=ct;for(int y:sr[x]) dfs4(y);}//标记相同点集
int main(){
    ios::sync_with_stdio(0);
    cin>>n>>a+1;
    for(int i=1,x,y;i<n;i++) cin>>x>>y,to[x].emplace_back(y),to[y].emplace_back(x);
    dfs(1,0),dfs2(1,1),dfs3(1);
    for(int i=1;i<=n;i++){
        if(f[i]==0) continue;
        sr[f[i]].emplace_back(i);
    }// x -> f_x
    for(int i=1;i<=n;i++)
        if(!f[i]&&f[fa[i]]&&sr[i].size()) sr[fa[i]].emplace_back(i); //x ->fa_x
    ct=0;for(int i=1;i<=n;i++){
        if(v[i]||!sr[i].size()||f[i]||f[fa[i]]) continue;
        ct++;dfs4(i);
    }
    for(int i=1,x;i<=n;i++){
        x=dfn[i];if(!v[x]) continue;
        if(pr[v[x]]) s[v[x]]+=d[x]-d[lca(x,pr[v[x]])];
        else s[v[x]]=1;
        pr[v[x]]=x;
    }
    for(int i=1;i<=ct;i++) ans=max(ans,s[i]);
    cout<<ans<<endl;
    return 0;
}
```



---

## 作者：irris (赞：2)

## Preface

赛时被 C 题整破防了所以没写。

现在补了一下。是好题，但是似乎有一万种做法。

## Solution

考虑到，假如某个 `)` 括号作为了连通块的叶子，那么和它匹配的 `(` 要么不存在，要么唯一确定。我们先考虑找到它。

#### Part 1

设 $m_i$ 表示点 $i$ 匹配的 `(` 的标号，$g_i = k$ 表示最浅的标号 $k$ 满足 $k \to i$ 路径上形成合法括号序列（$f_i, g_i$ 均仅在 $S_i = \texttt{)}$ 时有意义），那么我们 **从上向下地** 处理以确保后续调用的状态都已被计算过：

+ 更新 $m_i$：
	+ 若 $S_{fa_i} = \texttt{(}$，则 $m_i \gets fa_i$；
	+ 否则 $m_i \gets fa_{g_{fa_i}}$，这是因为 $g_{fa_i} \to fa_i$ 是最长的合法括号序列，那么就是有 $fa_{g_{fa_i}} = \texttt{(}$，否则肯定还能接着向上延伸。

> 你要是问我诸如 $S = \texttt{)())}$，树为一条 $1 \to 2 \to 3 \to 4$ 的链，那么在第四个点的时候 $m_4 = 1$ 是错误的，你不是漏讨论了一种情况吗？  
但是，后面我们会讲到，由于我们把每个右括号挂在匹配的左括号 $m_i$ 处处理，而这里的 $m_i$ 是右括号，所以它 **并不会被统计到**；与此同时，虽然 $m_i$ 处理错了，但本来它并不匹配，进一步地，也不会参与后续的任何可能的匹配，所以它 **并不可能计入最终答案**。  
细节可以在阅读全文后参考代码。

+ 更新 $g_i$：
	+ 若 $fa_{m_i}$ 不存在 $g$（$S_{fa_{m_i}} = \texttt{(}$ 或 $g_{fa_{m_i}} = 0$），则 $g_i \gets m_i$；
	+ 否则，$g_i$ 的位置可以更加向上，即 $g_i \gets g_{fa_{m_i}}$。

#### Part 2

我们在找到了 $m_i$ 之后，考虑得到以每个左括号 `(` 点 $u$ 为根的答案，$dp_u$，的具体构成形式。设 $D_u$ 表示 $m_i = u$ 的点的集合。特判 $\lvert D_u\rvert = 0$（直接退出即可）。

那么，$dp_u$ 应该是由两部分组成的：

1. 以 $u$ 为根，$D_u$ 的「虚树」大小，这是因为我们为了让连通块大小尽可能大，肯定要选择 $D_u$ 中的每一个点作为叶子；
2. $\displaystyle \sum_{v\text{是}u\text{儿子}}dp_v$，因为若 $\tt A$ 是合法括号序列，$\tt B$ 是合法括号序列，那么 $\tt AB$ 也是合法括号序列。如果我们把能拼上的儿子再拼上，连通块肯定会再扩大。

虚树大小可以根据 dfn 排序后，使用 LCA 实现，也就是每次用新的点和最右链求 LCA 后，深度相减得到新的若干条边的数量，全部加起来即可。

## Code

```cpp
#include <bits/stdc++.h>

namespace FastIO {
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= ch == '-', ch = getchar(); while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); return w ? ((~x) + 1) : x; }
	template <typename T> inline void write(T x) { x && (write<T>(x / 10), putchar(x % 10 ^ '0')); }
	template <typename T> inline void print(T x) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x); }
	template <typename T> inline void print(T x, char end) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x), putchar(end); }
}; using namespace FastIO;

#define MAXN 500005
std::vector<int> h[MAXN], D[MAXN];
char S[MAXN];

int sz[MAXN], fa[MAXN], top[MAXN], dfn[MAXN], dep[MAXN], cntD = 0;
void dfs1(int u = 1, int f = 0) {
	sz[u] = 1, dep[u] = dep[f] + 1, fa[u] = f, dfn[u] = ++cntD;
	for (int v : h[u]) if (v != f) dfs1(v, u), sz[u] += sz[v];
}
void dfs2(int u = 1) {
	int hson = 0;
	for (int v : h[u]) if (v != fa[u] && sz[hson] < sz[v]) hson = v;
	for (int v : h[u]) if (v != fa[u]) top[v] = (v == hson ? top[u] : v), dfs2(v);
}
inline int lca(int u, int v) {
	while (top[u] != top[v]) 
		if (dep[top[u]] > dep[top[v]]) u = fa[top[u]]; else v = fa[top[v]];
	return (dep[u] < dep[v] ? u : v);
}

int g[MAXN], dp[MAXN];
void solve(int u = 1) {
	if (S[u] == ')') {
		int mat = (S[fa[u]] == '(' ? fa[u] : fa[g[fa[u]]]);
		D[mat].push_back(u), g[u] = (fa[mat] == '(' || g[fa[mat]] == 0 ? mat : g[fa[mat]]);
	}
	for (int v : h[u]) if (v != fa[u]) solve(v);
	if (S[u] == '(' && !D[u].empty()) {
		std::sort(D[u].begin(), D[u].end(), [&](int a, int b) -> bool { return dfn[a] < dfn[b]; });
		int cur = u; dp[u] = 1;
		for (int t : D[u]) {
			dp[u] += dep[t] - dep[lca(cur, t)], cur = t;
			for (int v : h[t]) if (v != fa[t]) dp[u] += dp[v];
		}
	}
}
int main() {
	int N = read<int>(); scanf("%s", S + 1);
	for (int i = 1, u, v; i < N; ++i) 
		u = read<int>(), v = read<int>(), h[u].push_back(v), h[v].push_back(u);
	dfs1(), top[1] = 1, dfs2(), solve();
	return print<int>(*std::max_element(dp + 1, dp + N + 1)), 0;
}
```

---

## 作者：ARIS2_0 (赞：1)

提供一篇倍增+虚树的题解，很好想，但是写起来比较麻烦。

### 思路

容易发现，每一个右括号对应的左括号是唯一的，考虑找出每一个右括号对应的左括号。

记节点 $i$ 的父亲为 $fa_i$。

令左括号的权值为 $1$，右括号的权值为 $-1$，记 $s_i$ 为从 $1$ 到 $i$ 的路径上的权值和，显然可以一次 DFS 求出。

那么，如果点 $i$ 上的右括号和点 $j$ 上的左括号匹配，则满足：

- 点 $j$ 为点 $i$ 的祖先

- $s_i=s_{fa_j}(s_{fa_1}=0)$

- $i$ 到 $j$ 之间的所有点 $k$（不含 $i$，含 $j$）都有 $s_k\not=s_i$。

容易发现，因为有 $s_{fa_i}>s_i$，第三条限制中的 $s_k\not=s_i$ 等价于 $s_k>s_i$。

所以我们只需要找到 $i$ 上面第一个点 $p$，满足 $fa_i$ 到 $p$ 这条链上的最小值为 $s_i$，则此时有 $p=fa_j$。$p$ 显然可以用倍增求解。

然而求出 $p$ 后并不能直接知道 $j$，所以还需要一个倍增查 $k$ 级祖先来求出 $j$。

找出每一个右括号对应的左括号后，考虑用并查集将左括号节点与右括号节点合并，问题变为对于每一个并查集集合求出其在树上对应的联通块大小。

然而这样会有点问题。考虑以下括号序列：

`()()`

它们显然是可以存在于同一个集合内的，但是并查集内它们被分割成了两个集合。

解决方法也是简单的：对于每一个 $i$，如果 $i$ 是**有匹配的左括号** 且 $fa_i$ 是**有匹配的右括号**，将 $i$ 和 $fa_i$ 在并查集内合并。这样就可以保证正确性了。

最后，于每一个并查集集合求出其在树上对应的联通块大小，直接虚树做即可，非常好想且暴力。

### Code

实现是一坨，仅供参考。

注意是有答案 $=0$ 的点的。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define fi first
#define se second
#define mp make_pair
#define debug1(x) cerr<<(#x)<<"="<<(x)<<" "
#define debug2(x) cerr<<(#x)<<"="<<(x)<<"\n"
const int maxn=2e6+10,maxlog=25;
int n,b[maxn];
vector<int>v[maxn];
int f[maxlog][maxn],s[maxn],minn[maxlog][maxn],dep[maxn],p[maxn],tot=0;
void dfs1(int x){
    s[x]=s[f[0][x]]+b[x];
    minn[0][x]=s[x];
    if(x!=n+1)p[x]=++tot;
    for(int y:v[x]){
        if(y!=f[0][x]){
            f[0][y]=x;
            dep[y]=dep[x]+1;
            dfs1(y);
        }
    }
}
int pd[maxn];
int findet(int x,int val){
    for(int j=maxlog-1;j>=0;j--){
        if(minn[j][x]>val)x=f[j][x];
    }
    return x;
}
int findist(int x,int pos){
    for(int j=maxlog-1;j>=0;j--){
        if((1<<j)<=pos)pos-=(1<<j),x=f[j][x];
    }
    return x;
}
void presolve(){
    for(int j=1;j<maxlog;j++){
        for(int i=1;i<=n;i++){
            f[j][i]=f[j-1][f[j-1][i]];
            minn[j][i]=min(minn[j-1][i],minn[j-1][f[j-1][i]]);
        }
    }
    for(int i=1;i<=n;i++){
        if(b[i]==-1){
            if(minn[maxlog-1][f[0][i]]>s[i]){
                // debug1(i);debug1(f[0][i]);
                
                continue;
            }
            // debug2(minn[0][f[0][i]]);
            int x=findet(f[0][i],s[i]);
            // debug1(f[0][i]);debug1(s[i]);debug2(x);
            int dist=dep[i]-dep[x]-1;
            // debug2(dist);
            // debug2(f[0][2]);
            pd[i]=findist(i,dist);
        }
    }
}
int lca(int x,int y){
    // debug2("Start");
    // debug1(x);debug2(y);
    if(dep[x]<dep[y])swap(x,y);
    for(int j=maxlog-1;j>=0;j--){
        if(dep[x]-dep[y]>=(1<<j))x=f[j][x];
    }
    // debug1(x);debug2(y);
    if(x==y){
        // debug2("End");
        return x;
    }
    for(int j=maxlog-1;j>=0;j--){
        if(f[j][x] and f[j][y] and f[j][x]!=n+1 and f[j][y]!=n+1 and f[j][x]!=f[j][y])x=f[j][x],y=f[j][y];
    }
    // debug1(x);debug2(y);
    return f[0][x];
}
bool vis[maxn];
int fa[maxn];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
vector<int>ps[maxn];
int res[maxn<<1],cnt[maxn];
int solve(int x){
    // debug2(x);
    tot=0;
    for(int pos:ps[x])res[++tot]=pos;
    sort(res+1,res+tot+1,[](int pa,int pb){return p[pa]<p[pb];});
    // debug2("wefgewg\n");
    int ptot=tot;
    for(int i=1;i<ptot;i++)res[++tot]=lca(res[i],res[i+1]);
    // debug2("sdf");
    sort(res+1,res+tot+1,[](int pa,int pb){return p[pa]<p[pb];});
    tot=unique(res+1,res+tot+1)-res-1;
    for(int i=1;i<=tot;i++)cnt[res[i]]=0;
    int ans=0;
    for(int i=1;i<tot;i++){
        int x=lca(res[i],res[i+1]),y=res[i+1];
        ans+=dep[y]-dep[x]+1;
        cnt[x]++;cnt[y]++;
    }
    for(int i=1;i<=tot;i++){
        ans-=(cnt[res[i]]-1);
    }
    return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
    memset(minn,0x3f,sizeof(minn));
    cin>>n;
    for(int i=1;i<=n;i++){
        char c;cin>>c;
        if(c=='(')b[i]=1;
        else b[i]=-1;
    }
    for(int i=1,x,y;i<n;i++){
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    // debug2("");
    v[n+1].push_back(1);
    // debug2("");
    dfs1(n+1);
    // debug2("");
    presolve();
    // debug2("");
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=n;i++){
        if(pd[i]){
            fa[find(i)]=find(pd[i]);
            if(pd[f[0][pd[i]]]){
                fa[find(pd[i])]=find(f[0][pd[i]]);
            }
        }
    }
    // debug2("");
    for(int i=1;i<=n;i++){
        ps[find(i)].push_back(i);
        // debug1(i);debug2(find(i));
    }
    // debug2("");
    int ans=0;
    for(int i=1;i<=n;i++){
        int pos=find(i);
        if(!vis[pos]){
            vis[pos]=1;
            ans=max(ans,solve(pos));
        }
    }
    if(ans==1)ans=0;
    cout<<ans<<"\n";
	return 0;
}
/*
g++ -std=c++14 -Wall -Wextra -Wshadow -Wconversion
*/
```

---

## 作者：zxh923 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9655)

### 思路

我们令 `(` 为 $1$，`)` 为 $-1$，然后设 $s$ 为前缀和数组。

我们考虑什么样的一条路径链是合法的。假设这条链两端点为 $u,v$，那么必然有 $s_{fa_u}=s_v$ 且路径上 $s$ 的最小值等于 $s_v$。

于是我们得出了一条性质，假如我们的根是选定的，那么能成为叶子节点的点也唯一确定了，且能成为叶子节点的点数之和为 $n$。

注意到有一个点数之和的限制，这使得我们想到虚树。

于是我们枚举根的权值，然后找出所有该权值的点，建出虚树，然后 dp 一下即可。

转移方程是简单的，判断一个点的某个儿子到他的路径是否合法，如果合法直接加上儿子的 dp 值即可。

至于判断路径是否合法，可以在建边时预先判断，使用树剖和线段树即可。

时间复杂度 $O(n\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 500005
#define pii pair<int,int>
#define x first
#define y second
#define mod 1000000007
#define inf 2e18
using namespace std;
int T=1,n,cur;
char c[N];
vector<int>e[N],v[N<<1];
void add(int a,int b){
	e[a].push_back(b);
}
struct tc{
	int dep[N],fa[N],siz[N],son[N],top[N];
	int dfn[N],tot,s[N],nw[N];
	void dfs1(int u,int f){
		dep[u]=dep[f]+1;
		fa[u]=f;
		siz[u]=1;
		for(auto j:e[u]){
			if(j==fa[u])continue;
			if(c[j]=='(')s[j]=s[u]+1;
			else s[j]=s[u]-1;
			dfs1(j,u);
			siz[u]+=siz[j];
			if(siz[j]>siz[son[u]])son[u]=j;
		}
	}
	void dfs2(int u,int f){
		top[u]=f;
		dfn[u]=++tot;
		nw[tot]=s[u];
		if(son[u])dfs2(son[u],f);
		for(auto j:e[u]){
			if(j==fa[u]||j==son[u])continue;
			dfs2(j,j);
		}
	}
	int get_lca(int a,int b){
		while(top[a]!=top[b]){
			if(dep[top[a]]<dep[top[b]])swap(a,b);
			a=fa[top[a]];
		}
		return dep[a]<dep[b]?a:b;
	}
	int get_dist(int a,int b){
		int p=get_lca(a,b);
		return dep[a]+dep[b]-dep[p]*2;
	}
	int tr[N<<2];
	void pushup(int u){
		tr[u]=min(tr[u<<1],tr[u<<1|1]);
	}
	void build(int u,int l,int r){
		if(l==r){
			tr[u]=nw[l];
			return;
		}
		int mid=l+r>>1;
		build(u<<1,l,mid);
		build(u<<1|1,mid+1,r);
		pushup(u);
	}
	int qry(int u,int l,int r,int L,int R){
		if(l>=L&&r<=R)return tr[u];
		int mid=l+r>>1;
		int res=inf;
		if(L<=mid)res=min(res,qry(u<<1,l,mid,L,R));
		if(R>mid)res=min(res,qry(u<<1|1,mid+1,r,L,R));
		return res;
	}
	int qry_path(int a,int b){
		int res=inf;
		while(top[a]!=top[b]){
			if(dep[top[a]]<dep[top[b]])swap(a,b);
			res=min(res,qry(1,1,tot,dfn[top[a]],dfn[a]));
			a=fa[top[a]];
		}
		if(dep[a]<dep[b])swap(a,b);
		res=min(res,qry(1,1,tot,dfn[b],dfn[a]));
		return res;
	}
}tc;
struct vt{
	struct node{
		int b,c,d;
	};
	int stk[N],s[N],top,f[N],res;
	vector<node>e[N];
	vector<int>all;
	void add(int a,int b,int c,int d){
		all.push_back(a);
		all.push_back(b);
		e[a].push_back({b,c,d});
		e[b].push_back({a,c,d});
	}
	void clear(){
		for(auto it:all){
			e[it].clear();
		}
		all.clear();
	}
	void build(int id){
		top=0;
		stk[++top]=0;
		for(auto it:v[id]){
			stk[++top]=it;
		}
		sort(stk+1,stk+top+1,[&](int x,int y){
			return tc.dfn[x]<tc.dfn[y];
		});
		int m=unique(stk+1,stk+top+1)-stk-1;
		top=1;
		s[top]=stk[1];
		for(int i=2;i<=m;i++){
			int u=stk[i],l=tc.get_lca(s[top],u);
			while(top>1&&tc.dep[s[top-1]]>=tc.dep[l]){
				add(s[top-1],s[top],tc.get_dist(s[top-1],s[top]),tc.qry_path(s[top-1],s[top]));
				top--;
			}
			if(s[top]!=l){
				add(l,s[top],tc.get_dist(l,s[top]),tc.qry_path(l,s[top]));
				s[top]=l;
			}
			s[++top]=u;
		}
		while(top>1){
			add(s[top-1],s[top],tc.get_dist(s[top-1],s[top]),tc.qry_path(s[top-1],s[top]));
			top--;
		}
	}
	void dfs(int u,int fa,int val){
		f[u]=0;
		for(auto it:e[u]){
			int j=it.b,w=it.c,v=it.d;
			if(j==fa)continue;
			dfs(j,u,val);
			if(tc.s[u]==val&&v>=val)res=max(res,f[j]+w);
			if(v>=val)f[u]+=f[j]+w;
		}
	}
	void solve(){
		for(int i=0;i<=n+n;i++){
			if(v[i].size()<=1)continue;
			res=-1;
			build(i);
			dfs(0,0,i-n);
			cur=max(cur,res);
			clear();
		}
	}
}vt;
void solve(int cs){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c[i];
	}
	add(0,1);add(1,0);
	for(int i=1;i<n;i++){
		int a,b;
		cin>>a>>b;
		add(a,b);add(b,a);
	}
	tc.dfs1(0,0);
	tc.dfs2(0,0);
	tc.build(1,1,tc.tot);
	for(int i=0;i<=n;i++){
		v[tc.s[i]+n].push_back(i);
	}
	vt.solve();
	cout<<cur<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//	cin>>T;
//	init();
	for(int cs=1;cs<=T;cs++){
		solve(cs);
	}
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

考虑设计状态 $dp_{u,i}$ 表示考虑以 $u$ 为根的子树，满足子树内连通块做完括号匹配后形如 $i$ 个右括号的最大连通块大小，注意到转移形如先将所有儿子的 dp 数组按位做一些处理，再对 dp 数组做整体平移与整体加，观察到 dp 数组第二维小于等于子树高度，容易在长剖优化 dp 的过程中利用整体标记与动态分配 dp 数组下标做到 $O(n)$。注意到平移的过程中可能出现超出原定的下标范围的情况，这个时候由于所有儿子的 dp 已经贡献并且分配下标的顺序是自己，长儿子子树，轻儿子子树，所以直接把超出的范围也变成自己的就行，被挤占的位置一定已经用完了。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+114;
int beg[maxn];
int now;
int n;
vector<int> E[maxn];
int dp[maxn<<1];
int tag[maxn];
int maxdep[maxn],son[maxn];
char ty[maxn];
int endpos[maxn];
void dfs1(int u,int fa){
    maxdep[u]=1;
    for(int v:E[u]){
        if(v!=fa){
            dfs1(v,u);
            maxdep[u]=max(maxdep[u],maxdep[v]+1);
            if(maxdep[v]+1==maxdep[u]) son[u]=v;
        }
    }
}
void dfs2(int u,int fa){
    if(u!=son[fa]){
        beg[u]=now;
        now+=(maxdep[u]+1);
        endpos[u]=now-1;
    }else{
        beg[u]=beg[fa]+1;
        endpos[u]=endpos[fa];
    }
    if(son[u]!=0) dfs2(son[u],u);
    for(int v:E[u]){
        if(v!=fa&&v!=son[u]) dfs2(v,u);
    }
}
int ans;
void DP(int u,int fa){
    if(son[u]!=0){
        DP(son[u],u);
        beg[u]=beg[son[u]];
        endpos[u]=endpos[son[u]];
        tag[u]=tag[son[u]];
    }else{
        dp[beg[u]]=0;
        if(ty[u]==')') dp[beg[u]+1]=1;
        return ; 
    }
    for(int v:E[u]){
        if(v!=fa&&v!=son[u]){
            DP(v,u);
            for(int i=beg[v];i<=endpos[v];i++){
                if(beg[u]+i-beg[v]>endpos[u]){
                    endpos[u]++;
                    dp[endpos[u]]=-1e9;
                }
                dp[beg[u]+i-beg[v]]+=max(dp[i]+tag[v],0),dp[beg[u]+i-beg[v]]=max(dp[beg[u]+i-beg[v]],dp[i]+tag[v]-tag[u]);
            }
        }
    }
    if(ty[u]=='('){
        if(beg[u]==endpos[u]){
            tag[u]=0;
            dp[beg[u]]=0;
        }else{
            dp[beg[u]]=-1e9;
            beg[u]++;
            tag[u]++;
        }
    }else{
        tag[u]++;
        beg[u]--;
        dp[beg[u]+1]=max(dp[beg[u]+1],1-tag[u]);
    }
    dp[beg[u]]=max(dp[beg[u]],-tag[u]);
    ans=max(ans,dp[beg[u]]+tag[u]);
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>ty[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,0);
    for(int i=0;i<=now;i++) dp[i]=-1e9;
    DP(1,0);
    cout<<ans<<'\n';
    return 0;
}
```

---

