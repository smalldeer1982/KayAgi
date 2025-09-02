# [ICPC 2018 Qingdao R] Kawa Exam

## 题目描述

BaoBao 正在参加 Kawa 编程语言的在线考试，该考试由 $n$ 个多项选择题组成。考试并不容易，对于每一道题，BaoBao 都需要从 $10^5$ 个可用选项中选择唯一一个正确答案！但别担心，作为著名的 $\text{open-kdk}$ 的积极参与者，BaoBao 显然知道所有正确的答案。

虽然 BaoBao 是 Kawa 方面的专家，但考试系统的开发人员绝对不是软件工程方面的专家。考试系统中有 $m$ 个错误，第 $i$ 个错误可以描述为 $(u_i,v_i)$，这意味着 BaoBao 必须为第 $u_i$ 和 $v_i$ 个问题选择相同的选项（即使他选择的选项不正确！）。

但是考试必须继续，这就意味着开发人员只有时间修复一个错误。现在，开发人员想知道，对于所有的 $1\le i\le m$，如果他们修复 $i$，BaoBao 可以正确回答的最大问题数量是多少。

## 说明/提示

下表解释了第一个示例测试用例。

- “可能的选择”列表示 BaoBao 可以选择的每个问题的一组可能的选择，从而导致正确回答的问题的最大可能数量；

- “正确”列表示使用“可能的选择”列中提供的一组选择正确回答的问题的数量。

$$\begin{array}{|c|c|c|c|}
\hline
\textbf{Bug 编号} & \textbf{可能的选择} & \textbf{正确} \\
\hline
1 & (1, 2, 1, 2, 1, 1, 1) & 6 \\
\hline
2 & (2, 2, 1, 2, 1, 1, 1) & 5 \\
\hline
3 & (1, 1, 1, 2, 1, 1, 1) & 5 \\
\hline
4 & (1, 1, 1, 1, 1, 2, 1) & 5 \\
\hline
5 & (1, 1, 1, 1, 1, 1, 1) & 4 \\
\hline
\end{array}$$

对于第二个样本测试用例，无论哪个 bug 被修复，BaoBao 都必须为所有三个问题选择相同的选项。由于每个问题的正确答案不同，BaoBao 只能正确回答一个问题。

对于第三个示例测试用例，请注意，即使开发人员修复了第一个错误，第二个错误仍然有效，BaoBao 仍然必须为这两个问题选择相同的选项。如果第二个错误被修复，情况也是一样的。

## 样例 #1

### 输入

```
3
7 5
1 2 1 2 1 2 1
1 2
1 3
2 4
5 6
5 7
3 3
1 2 3
1 2
1 3
2 3
2 3
12345 54321
1 2
1 2
1 1```

### 输出

```
6 5 5 5 4
1 1 1
1 1 1```

# 题解

## 作者：Conan15 (赞：5)

PS：这题思维难度较低，代码难度较高。（或许是我的写法问题？）

容易想到如果删除的边在一个边双内，则答案和不删除这条边是一样的。
所以考虑先跑 tarjan 做一遍边双缩点，只有割边可能会改变答案。

然后将题目的模型转化，显然在同一个连通块内的点必须选择同一个选项。\
**所以一个连通块的贡献就是它内部出现次数最多的点权的次数。**\
然后显然，缩点之后会得到一个**森林**，存在于这个森林上的边就是原图中的割边。\
可以想到对于森林中的每棵树，从根节点往下遍历，并在线维护子树内和子树外的最大出现次数。似乎可以线段树合并？但感觉很难写。

于是我放弃了线段树合并。显然，如果只需要统计子树，那么这题等价于 CF600E，太模板了就不讲了。\
可是还要统计**子树外**？其实和子树内是同理，这里解释一下。

1. 访问到一个节点，先记录答案。
2. 然后加上**这个点**和它所有**轻儿子**的权值信息。
3. 往下递归，先求出重儿子的答案。
4. 然后再遍历每个轻儿子，先删除轻儿子的权值信息再往下递归轻儿子。

当 dfs 完一棵子树之后，统计数组内有存储这个子树的信息（因为步骤 2 中有加入这个点的点权）。\
因此在求完重儿子答案之后不需要再把重儿子加入一遍。

代码真的很难写，可能我写的比较抽象吧 QwQ，~~但是确实一遍就过了~~。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 15, M = 2e5 + 15;
int T, n, m, a[N];
int x[M], y[M];
int h[N], e[M], w[M], ne[M], idx = 0;
void add(int a, int b, int c) { e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++; }

int dfn[N], low[N], tot = 0;
bool cut[M];
void tarjan(int u, int pre) {
    dfn[u] = low[u] = ++tot;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v]) cut[i] = cut[i ^ 1] = 1/*, cout << "Cut " << e[i] << ' ' << e[i ^ 1] << endl*/;
        } else if (i != (pre ^ 1) ) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int ecc[N], cnt_ecc = 0;
void divide(int u) {    //get ecc
    ecc[u] = cnt_ecc;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (cut[i] || ecc[v]) continue;
        divide(v);
    }
}

void clr() {
    for (int i = 0; i <= idx; i++) cut[i] = 0;
    idx = tot = cnt_ecc = 0;
    for (int i = 1; i <= n + 5; i++) h[i] = -1, dfn[i] = low[i] = ecc[i] = 0;
}

int cnt[N], ccnt[N], now;   //now 是当前答案 ( Max )
void add(int x) {   //加入一个数字
    if (cnt[x]) ccnt[cnt[x]]--;
    cnt[x]++, ccnt[cnt[x]]++;
    if (now < cnt[x]) now = cnt[x];
}
void del(int x) {   //删掉一个数字
    ccnt[cnt[x]]--;
    if (ccnt[cnt[x]] == 0 && now == cnt[x]) now--;
    cnt[x]--;
    if (cnt[x]) ccnt[cnt[x]]++;
}

struct Graph {
    int h[N], e[M], w[M], ne[M], idx = 0;
    int sz[N], dep[N], son[N];
    vector<int> col[N]; //缩点后每个 点 的颜色列表
    void Add(int a, int b, int c) { e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++; }
    void addedge(int a, int b, int c) { Add(a, b, c), Add(b, a, c); }
    int ans_tree[N], ans_fa[N];

    void init() {
        memset(h, -1, sizeof h), idx = 0;
        for (int i = 1; i <= cnt_ecc; i++) col[i].clear(), sz[i] = son[i] = dep[i] = ans_tree[i] = ans_fa[i] = 0;
    }

    void dfs1(int u, int father) {
        sz[u] = 1, dep[u] = dep[father] + 1;
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (v == father) continue;
            dfs1(v, u), sz[u] += sz[v];
            if (!son[u] || sz[son[u]] < sz[v]) son[u] = v;
        }
    }
    void update(int u, int opt) {   //对 u 点进行 opt 操作
        // cout << "Update: " << u << ' ' << opt << endl;
        if (opt ==  1) for (int i : col[u]) add(i);
        if (opt == -1) for (int i : col[u]) del(i);
    }

    void dfs(int u, int father, int opt) {  //对 u 子树进行 opt 操作
        update(u, opt);
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (v == father) continue;
            dfs(v, u, opt);
        }
    }
    void dfs_tree(int u, int father, bool keep) {
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (v == father || v == son[u]) continue;
            dfs_tree(v, u, 0);
        }
        if (son[u]) dfs_tree(son[u], u, 1);
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (v == father || v == son[u]) continue;
            dfs(v, u, 1);
        }
        update(u, 1);
        ans_tree[u] = now;
        if (!keep) dfs(u, father, -1);
    }
    void dfs_fa(int u, int father) {
        ans_fa[u] = now, update(u, 1);
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (v == father || v == son[u]) continue;
            dfs(v, u, 1);
        }
        if (son[u]) dfs_fa(son[u], u);
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (v == father || v == son[u]) continue;
            dfs(v, u, -1);
            dfs_fa(v, u);
        }
    }
    void dfs_clr(int u, int father) {
        for (int i : col[u]) ccnt[cnt[i]] = 0, cnt[i] = 0;
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (v == father) continue;
            dfs_clr(v, u);
        }
    }
} G;

int p[N];
int find(int x) { return (x == p[x]) ? x : p[x] = find(p[x]); }
void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x ^ y) p[x] = y;
}

vector<int> c[N];   //缩点后每个 连通块 的颜色列表
int Ans[N], sum; //缩点后每个 连通块 不删的答案
bool st[N]; //连通块是否遍历过

void build_graph() {
    for (int i = 1; i <= n; i++) c[i].clear();
    G.init();
    for (int i = 1; i <= n; i++) G.col[ecc[i]].push_back(a[i]);
    for (int i = 1; i <= cnt_ecc; i++) st[i] = 0, p[i] = i;
    for (int i = 1; i <= m; i++) {
        int u = x[i], v = y[i];
        if (ecc[u] == ecc[v]) continue;
        G.addedge(ecc[u], ecc[v], i);
        merge(ecc[u], ecc[v]);
    }

    for (int i = 1; i <= n; i++) c[ find(ecc[i]) ].push_back(a[i]);
    sum = 0;
    for (int i = 1; i <= cnt_ecc; i++) st[i] = 0;
    for (int i = 1; i <= cnt_ecc; i++) {
        int id = find(p[i]);
        if (st[ id ]) continue;   //每个连通块只处理一次 Ans
        st[ id ] = 1;
        int Max = 0;
        for (int j : c[id]) cnt[j]++, Max = max(Max, cnt[j]);
        Ans[ id ] = Max, sum += Max;
        for (int j : c[id]) cnt[j]--;
    }

    for (int i = 1; i <= cnt_ecc; i++) st[i] = 0;
    for (int i = 1; i <= cnt_ecc; i++)
        if (!st[find(i)]) st[find(i)] = 1, G.dfs1(i, 0);
    // for (int i = 1; i <= n; i++) cout << G.son[i] << ' '; puts("");


    for (int i = 1; i <= cnt_ecc; i++) st[i] = 0;
    for (int i = 1; i <= cnt_ecc; i++)
        if (!st[find(i)]) {
            st[find(i)] = 1, now = 0, G.dfs_tree(i, 0, 0);
            G.dfs_clr(i, 0), now = 0;
            // cout << "QwQ " << i << endl;
        }

    for (int i = 1; i <= cnt_ecc; i++) st[i] = 0;
    for (int i = 1; i <= cnt_ecc; i++)
        if (!st[find(i)]) {
            st[find(i)] = 1, now = 0, G.dfs_fa(i, 0);
            G.dfs_clr(i, 0), now = 0;
            // cout << "AwA " << i << endl;
        }
    
    // G.dfs_tree(1, 0, 0);
    // for (int i = 1; i <= 3; i++) cout << cnt[i] << ' '; puts("");
    // for (int i = 1; i <= 3; i++) cout << ccnt[i] << ' '; puts("");
    // exit(0);
}

void solve() {
    scanf("%d%d", &n, &m);
    clr();
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) scanf("%d%d", &x[i], &y[i]), add(x[i], y[i], i), add(y[i], x[i], i);
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i, -1);
    for (int i = 1; i <= n; i++)
        if (!ecc[i]) ++cnt_ecc, divide(i);
    build_graph();
    // for (int i = 1; i <= n; i++) printf("%d\t%d %d\n", i, G.ans_tree[i], G.ans_fa[i]);
    // for (int i = 1; i <= n; i++) cout << '\t' << i << ' ' << low[i] << endl;
    for (int i = 1; i <= m; i++) {
        int u = ecc[x[i]], v = ecc[y[i]];
        if (u == v) printf("%d", sum);
        else {
            if (G.dep[u] < G.dep[v]) swap(u, v);
            // cout << "Query: " << u << ' ' << v << ' ' << G.dep[u] << ' ' << G.dep[v] << endl;
            printf("%d", sum - Ans[ find(u) ] + G.ans_tree[u] + G.ans_fa[u]);
        }
        putchar(i == m ? '\n' : ' ');
    }
}

int main() {
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}
```

---

## 作者：未来姚班zyl (赞：5)

## 题目大意

给定一个无向图，点有颜色。每个连通块的权值为其出现最多的颜色的出现次数，图的权值为每个连通块权值之和。对于每一条边，请你求出如果断开它，图的权值会是多少。

## 题目分析

首先要考虑将图按照边双缩点，则位于边双内的边断开是不会影响权值的，这个权值可以先整体计算出来，然后考虑割边。

由于边双缩点后的图是森林，所以割边被断后相当于所在连通块被分为一棵子树和其补集，分别计算就可以得到答案。

这就是树上启发式合并板子题，复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for (int i = h[x], y = to[i]; i; i = nxt[i], y = to[i])
#define E(x) for (auto y : p[x])
#define Pi pair<int, int>
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =1e5+5;
using namespace std;
int T=read(),n,m,Ans,bel[N],a[N],h[N],tot,nxt[N<<1],cnt=1,to[N<<1],dfn[N],Time,low[N],s[N],tp,c[N],out[N],son[N],siz[N],Mx,ct[N],mx,Ct[N],S[N],Tp;
bool instac[N];
inline void add(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt,to[++cnt]=a,nxt[cnt]=h[b],h[b]=cnt;
} 
vector<int>q[N];
inline void tarjan(int x,int fr){
	dfn[x]=low[x]=++Time,s[++tp]=x,instac[x]=1;
	e(x)if(i==(fr^1))continue;
	else if(!dfn[y])tarjan(y,i),low[x]=min(low[x],low[y]);
	else if(instac[y])low[x]=min(low[x],dfn[y]);
	if(low[x]==dfn[x]){
		tot++;
		for(int y=s[tp--];;y=s[tp--]){
			bel[y]=tot,instac[y]=0,q[tot].pb(y);
			if(y==x)return;
		}
	}
}
vector<Pi >p[N];
#define Y y.first
inline void add(int x){
	s[++tp]=x,ct[c[a[x]]]--,c[a[x]]++,ct[c[a[x]]]++,Mx=max(Mx,c[a[x]]);
}
inline void del(int x){
	ct[c[a[x]]]--,c[a[x]]--,ct[c[a[x]]]++;
	while(!ct[Mx]&&Mx)Mx--;
}
inline void dfs(int x,int fa){
	siz[x]=q[x].size();
	for(auto y:q[x])add(y);
	E(x)if(Y^fa)dfs(Y,x),siz[x]+=siz[Y],son[x]=siz[Y]>siz[son[x]]?Y:son[x];
}
inline void clear(){
	while(tp)del(s[tp--]);
}
inline void Del(int x){
	s[++tp]=x,del(x),mx=max(mx,++Ct[a[x]]);
}
inline void Clear(){
	while(tp)add(s[tp]),tp--,Ct[a[s[tp--]]]=0;
	mx=0;
}
bool v[N];
inline void got(int x,int fa){
	for(auto y:q[x])Del(y);
	E(x)if(Y^fa)got(Y,x);
}
inline void Dfs(int x,int fa){
	v[x]=1;
	int nw=Mx;
	E(x)if(Y^fa&&Y^son[x])Dfs(Y,x),out[y.second]+=Mx+mx-nw,Clear();
	E(x)if(Y==son[x])Dfs(son[x],x),out[y.second]+=Mx+mx-nw;
	E(x)if(Y^fa&&Y^son[x])got(Y,x);
	for(auto y:q[x])Del(y);
}
inline void clear_(){
	repn(i)siz[i]=h[i]=dfn[i]=v[i]=son[i]=0,p[i].clear(),q[i].clear();
	cnt=1,Time=tp=tot=Ans=0;
}
signed main(){
	while(T--){
		n=read(),m=read();
		repn(i)a[i]=read();
		repm(i)add(read(),read());
		repn(i)if(!dfn[i])tarjan(i,0),tp=0;
		repn(x)e(x)if(bel[x]^bel[y])p[bel[x]].pb({bel[y],i/2});
		rep(i,1,tot)if(!siz[i])dfs(i,0),Ans+=Mx,clear();
		repm(i)out[i]=Ans;
		rep(i,1,tot)if(!v[i]){
			dfs(i,0),Tp=tp;
			rep(j,1,tp)S[j]=s[j];
			tp=0,Dfs(i,0),Clear();
			rep(j,1,Tp)del(S[j]);
		}
		repm(i){
			pf(out[i]);if(i^m)putchar(' ');
		}
		putchar('\n'),clear_();
	}
	return 0;
}
```


---

## 作者：Union_Find (赞：2)

首先很容易发现的是，一个连通块内只能选一种答案，而且在最优解情况下，我们肯定是选择这个连通块的众数。

因为在手模样例时，以为保证是一个**森林**，所以有了如下想法。

我们考虑一个块内拆掉一条边，对答案的影响。很简单的就是，子树内外可以选择不一样的数了。所以我们先减去原来整个连通块的贡献，然后求出分别子树内外的众数的出现次数，加上即可。

一开始因为有子树内的部分，可以使用线段树合并，但是发现线段树合并无法处理子树外的情况，所以放弃了。考虑到这种出现次数的问题十分的 DSU on Tree，所以我们考虑如何使用 DSU on Tree 解决这题。

> 作者提醒，以下部分为 DSU on Tree 的部分，如果会了请移步至后。

首先是子树内，很简单的就是，我们直接先跑轻儿子，每次跑完轻儿子就清空，最后跑重儿子，重儿子不用清空。跑完重儿子之后，再把轻儿子的子树内加回来。这样子时间复杂度就是 $O(n\log n)$ 的。

然后是子树外的，这一部分也比较经典，因为我们需要存子树外但不包括子树内的信息，所以我们每次先跑重儿子，求答案的同时把重儿子子树内的信息加上。然后处理轻儿子，在进入轻儿子子树之前把子树内的信息先删掉，然后再跑。时间复杂度同样是 $O(n\log n)$ 的。

如果不会加入和删除的话，可以学习一下 [P3709 大爷的字符串题](https://www.luogu.com.cn/problem/P3709) 的非回滚莫队和值域分块做法。这图就是求静态区间众数的出现次数。简单说就是存一下 $t_i$ 表示 $i$ 这个数出现了几次，$cnt_i$ 表示满足 $t_j = i$ 的 $j$ 出现了几次，然后删除的时候特判一下，因为每次修改都只会有至多 $1$ 的变动。

---

这样子我们就会做**森林**的情况了，但是我们发现，题目有可能是一张普通的图，还会有重边和自环，怎么办？不能浪费前面的思路，那就把它转化成**森林**吧。

我们按照边双缩点，这样子就是森林了。值得注意的是，这题会有重边和自环，缩点的时候记得处理。

还有一个点，我们缩点之后暴力修改轻儿子子树时的时间复杂度是和原图上点的数量有关的，所以缩点的点大小初始值应该是该边双内的点的数量，不能直接设成 $1$。~~虽然好像也能过。~~

最后一点提醒，如果一条边的两个点在同一个边双内，那么删除后答案不变，因为连通性不变。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define N 100005
#define M 200005
#define rep(u, v) for (int ii = hd[u], v = to[ii]; ii; ii = nxt[ii], v = to[ii])
#define cut(u, v) ((fat[u] == (v) && isb[u]) || (fat[v] == (u) && isb[v]))
il int rd(){
	int s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
int n, m, a[N], u, v, col[N], dfn[N], low[N], isb[N], fat[N], ex, edcc, sz[N], dep[N];
int t[N], cnt[N], res, rt[N], tu[N], tv[N], sum[N], ans_son[N], ans_outson[N], son[N], ans;
vector <int> ed[N];
int hd[N], nxt[M], to[M], en;
il void add(int u, int v){nxt[++en] = hd[u], to[en] = v, hd[u] = en;}


void tarjan(int u, int fa){
	dfn[u] = low[u] = ++ex, fat[u] = fa;
	bool flag = 0;
	rep(u, v){
		if (!dfn[v]){
			tarjan(v, u), low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) isb[v] = 1;
		}else if (v != fa || flag) low[u] = min(low[u], dfn[v]);
		else if (v == fa) flag = 1;
	}
}void cover(int u, int c){
	sz[c]++, col[u] = c, ed[c].push_back(u);
	rep(u, v) if (!cut(u, v) && !col[v]) cover(v, c);
}
// tarjan 求边双 


il void insert(int u){
	for (int i : ed[u]){
		cnt[t[a[i]]]--, t[a[i]]++, cnt[t[a[i]]]++;
		if (cnt[t[a[i]]] == 1 && res < t[a[i]]) res++;
	}
}
il void del(int u){
	for (int i : ed[u]){
		if (cnt[t[a[i]]] == 1 && res == t[a[i]]) res--;
		cnt[t[a[i]]]--, t[a[i]]--, cnt[t[a[i]]]++;
	}
}
void add_son(int u, int fa){
	insert(u);
	rep(u, v) if (v != fa) add_son(v, u);
}
void del_son(int u, int fa){
	del(u);
	rep(u, v) if (v != fa) del_son(v, u);
}
// DSU 的加点和删点


void dfs_init(int u, int fa, int root){
	rt[u] = root, dep[u] = dep[fa] + 1, insert(u);
	rep(u, v) if (v != fa) dfs_init(v, u, root), sz[u] += sz[v], son[u] = (sz[son[u]] > sz[v] ? son[u] : v);
}// 预处理树 
void dfs_son(int u, int fa, bool light){
	rep(u, v) if (v != fa && v != son[u]) dfs_son(v, u, 1);
	if (son[u]) dfs_son(son[u], u, 0);
	rep(u, v) if (v != fa && v != son[u]) add_son(v, u);
	insert(u), ans_son[u] = res;
	if (light) del_son(u, fa);
}// DSU on Tree 1 -- 子树内 
void dfs_outson(int u, int fa){
	ans_outson[u] = res, insert(u);
	rep(u, v) if (v != fa && v != son[u]) add_son(v, u);
	if (son[u]) dfs_outson(son[u], u);
	rep(u, v) if (v != fa && v != son[u]) del_son(v, u), dfs_outson(v, u);
}// DSU on Tree 2 -- 子树外 


il void G_init(){
	for (int i = 1; i <= n; i++) hd[i] = 0;
	for (int i = 1; i <= en; i++) nxt[i] = to[i] = 0;
	en = 0;
}
il void init(){
	for (int i = 1; i <= n; i++) cnt[t[a[i]]] = 0, t[a[i]] = 0;
	for (int i = 1; i <= n; i++) a[i] = col[i] = dfn[i] = low[i] = isb[i] = fat[i] = sz[i] = dep[i] = 0;
	for (int i = 1; i <= n; i++) rt[i] = tu[i] = tv[i] = sum[i] = ans_son[i] = ans_outson[i] = son[i] = 0, ed[i].clear();
	ex = edcc = res = ans = 0, G_init();
}// 预处理


void solve(){
	n = rd(), m = rd();
	for (int i = 1; i <= n; i++) a[i] = rd();
	for (int i = 1; i <= m; i++) tu[i] = u = rd(), tv[i] = v = rd(), add(u, v), add(v, u);
	
	
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i, 0);
	for (int i = 1; i <= n; i++) if (!col[i]) cover(i, ++edcc);// 处理边双 
	G_init();
	for (int i = 1; i <= m; i++){
		int u = tu[i], v = tv[i];
		if (col[u] != col[v]) add(col[u], col[v]), add(col[v], col[u]);
	}// 缩点
	for (int i = 1; i <= edcc; i++) if (!rt[i]) dfs_init(i, 0, i), sum[i] = res, ans += sum[i], del_son(i, 0);// 预处理树 
	for (int i = 1; i <= edcc; i++) if (rt[i] == i) dfs_son(i, 0, 1);// DSU on Tree 1 
	for (int i = 1; i <= edcc; i++) if (rt[i] == i) dfs_outson(i, 0), del_son(i, 0);// DSU on Tree 2
	
	
	for (int i = 1; i <= m; i++){
		u = tu[i], v = tv[i];
		if (col[u] == col[v]) printf ("%d", ans);
		else{
			u = col[u], v = col[v];
			if (dep[u] > dep[v]) swap(u, v);
			printf ("%d", ans - sum[rt[v]] + ans_son[v] + ans_outson[v]);
		}putchar(i == m ? '\n' : ' ');
	}
	
	init();
}
int main(){
	for (int T = rd(); T--;) solve();
	return 0;
}
```

---

## 作者：cflsfzh (赞：1)

## [题目链接](https://www.luogu.com.cn/problem/P9886)

我们可以将冗长的题目简化，对于原图的每一条边，断掉它后的新图，算对于每一个连通块内点的答案的众数的数量之和。

发现断边这个东西不好做，所以优先考虑断边怎么解决。容易发现，有两种情况，一种是断掉没有影响，一种是将原图的一个连通块变成了两个。这两种情况的分界点也很好找，显然是割边，所以我们的第一步就清晰了，做缩点。

接着考虑缩完点后该如何计算每条边的贡献。看数据范围，容易想出时间复杂度为单 $\log$ 的启发式合并，显然我们需要维护的众数是很模板的。我们考虑分开计算子树内的答案和子树外的答案，子树内的不必多说，子树外的情况提一下，我们考虑先加入所有轻儿子的状态，然后计算重儿子的答案，接着枚举每个轻儿子，先删除它子树内的所有状态再边计算边加回来，时间复杂度显然正确。最终时间复杂度 $O(n \log n)$，代码实现时有一点点痛苦，但是没什么细节，就是要注意一下多测清空哦。

*Code*，这边建议仅参考，因为我的代码是分成 $4$ 天完成的（零散时间码的），所以很不适合看，望原谅。


```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define pii pair<int,int>
#define fs first
#define sc second
#define il inline
#define re register 
using namespace std;
int read()
{
	int x=0;
	int ff=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')
			ff=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar(); 
	}
	return x*ff;
}
const int N=1e5+6;
struct edge{
	int v,next,bh;
};
edge e[2*N];
int t_,n,m,a[N],k,head[N],qwq,awa[N],awa_[N];
int dfn[N],q[N],cnt,top,low[N],t[N];
int son[N],sz[N],mx,b[N],vis[N];
vector<pii> mp[N];
vector<int> d[N];
void init()
{
	k=mx=qwq=cnt=top=0;
	for(int i=0;i<=max(n,m);i++){
		head[i]=b[i]=0;
		son[i]=vis[i]=0;
		sz[i]=t[i]=q[i]=0;
		dfn[i]=low[i]=0;
		awa[i]=awa_[i]=0;
		mp[i].clear();
		d[i].clear();
	}
	return;
}
void tarjan(int u,int fa)
{
	dfn[u]=low[u]=++cnt;
	q[++top]=u,vis[u]=1;
	for(auto x:mp[u]){
		int v=x.fs;
		int bh=x.sc;
		if(bh==fa)
			continue;
		if(!dfn[v]){
			tarjan(v,bh);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		qwq++;
		while(q[top+1]!=u)
			d[qwq].pb(q[top]),t[q[top]]=qwq,vis[q[top--]]=0;
	}
	return;
}
void add_(int u,int v,int bh)
{
	e[++k].v=v;
	e[k].bh=bh;
	e[k].next=head[u];
	head[u]=k;
	return;
}
void get_son(int u,int fa)
{
	sz[u]=d[u].size();
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v==fa)
			continue;
		get_son(v,u);
		sz[u]+=sz[v];
		if(sz[v]>sz[son[u]])
			son[u]=v;
	}
	return;
}
void insert(int u,int z)
{
	for(auto x:d[u]){
		vis[b[a[x]]]--;
		if(mx==b[a[x]]&&!vis[b[a[x]]])
			mx=0;
		b[a[x]]+=z;
		mx=max(mx,b[a[x]]);
		vis[b[a[x]]]++;
	}
	return;
}
void add(int u,int fa,int z)
{
	insert(u,z);
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v==fa)
			continue;
		add(v,u,z);
	}
	return;
}
void dfz_son(int u,int fa,int flag,int x)
{
//	printf("%lld-%lld-%lld-%lld\n",u,fa,flag,x);
	t[x]=top;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v==fa||v==son[u])
			continue;
		int bh=e[i].bh;
		dfz_son(v,u,0,bh);
	}
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		int bh=e[i].bh;
		if(v==son[u])
			dfz_son(v,u,1,bh);
	}
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v!=son[u]&&v!=fa)
			add(v,u,1);
	}
	insert(u,1);
	awa[x]+=mx;
	if(!flag)
		add(u,fa,-1);
	return;
}
void dfz_fa(int u,int fa,int flag,int x)
{
	awa[x]+=mx;
	insert(u,1);
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v!=fa&&v!=son[u])
			add(v,u,1);
	}
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		int bh=e[i].bh;
		if(v==son[u])
			dfz_fa(v,u,1,bh);
	}
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		int bh=e[i].bh;
		if(v!=fa&&v!=son[u]){
			add(v,u,-1);
			dfz_fa(v,u,1,bh);
		}
	}
	if(!flag)
		add(u,fa,-1);
	return;
}
signed main()
{
	t_=read();
	for(;t_;t_--){
		n=read();
		m=read();
		for(int i=1;i<=n;i++)
			a[i]=read();
		for(int i=1;i<=m;i++){
			int u,v;
			u=read();
			v=read();
			mp[u].pb({v,i});
			mp[v].pb({u,i});
		}
		for(int i=1;i<=n;i++){
			if(dfn[i])
				continue;
			top=0;
			tarjan(i,0);
		}
		for(int i=1;i<=n;i++)
			for(auto x:mp[i])
				if(t[x.fs]!=t[i])
					add_(t[i],t[x.fs],x.sc);
		top=0;
		for(int i=1;i<=qwq;i++){
			if(sz[i])
				continue;
			top++;
			get_son(i,0);
			dfz_son(i,0,0,0);
			dfz_fa(i,0,0,0);
			awa_[top]=awa[0];
			awa[0]=0;
		}
		for(int i=1;i<=qwq;i++)
			awa[0]+=awa_[i];
		if(!awa[1])
			printf("%lld",awa[0]);
		else
			printf("%lld",awa[0]-awa_[t[1]]+awa[1]);
		for(int i=2;i<=m;i++){
			if(!awa[i])
				printf(" %lld",awa[0]);
			else
				printf(" %lld",awa[0]-awa_[t[i]]+awa[i]);
		}
		printf("\n");
		init();
	}
	return 0;
}
```

---

## 作者：Sampson_YW (赞：1)

将 $(u_i,v_i)$ 当成一条边，那么对于同一个连通块里的点，颜色都必须相同。也就是对每个连通块找每种颜色出现次数的最大值。

从加边的角度考虑，就有了一个分治+可撤销并查集+启发式合并的做法（过不了）：

对边集做序列分治。将 $[l,r]$ 砍半，加入 $[l,mid]$ 的边递归到 $(mid,r]$，撤销后加入 $(mid,r]$ 的边递归到 $[l,mid]$，递归完再撤销。递归到叶子的时候就已经把除了这条边之外的所有边都连上了。中途用可撤销并查集维护连通性，并用一个数据结构维护一下每个连通块中每种颜色的出现次数。但是用 umap 启发式合并也需要 $O(n\log^2n)$ 的复杂度，过不了一点。

从加边的角度考虑看起来已经到头了，那么我们从删边的角度考虑。

对于一条边，如果删去它不影响连通性，那么这条边不能对答案造成任何影响。也就是说这条边在一个环上。

由于树是一个没有环的无向图，那么我们提取出这张图的一棵生成树，不妨提取一棵 DFS 生成树。那么不在这棵树上的边，他们的答案一定不变。如果一条树边被一条非树边覆盖了，那么这条树边的答案也不变。那么先对所有树边求出答案，再清空答案不变的树边。

对于一条树边，删去这条边后会变成两个连通块（先假设这张图就是一棵树）。容易发现这两个连通块，一个是以某个点为根的子树，另一个是这个子树的子树补。我们要对这两个连通块分别求出每种颜色的出现次数最大值。这显然是 dsu on tree 的板子（子树补的求法就是先将所有点加入，再删去子树里的点）。

但是我学不明白 dsu on tree，所以讲一个序列分治做法（虽然本质相同，但是可能好理解一些）：

将这棵树拍成 DFS 序，一棵子树就是一个区间，并且所有的区间要么包含，要么不交。对 DFS 序进行序列分治。

对于子树内的情况：将 $[l,r]$ 砍半，对于所有跨过 $mid$ 的区间求答案。那么这些区间都是相互包含的。按询问区间的左端点从大到小排序，那么它们的右端点是单调不降的。双指针，每次左指针向左扩展到当前询问区间的左端点，然后右指针向右扩展到对应的询问区间右端点。中途遍历到的颜色开个桶维护一下每种颜色的出现次数就能找到区间内的最大值。

对于子树补的情况：类似于一开始从加边角度考虑的做法。对于一个区间 $[l,r]$，先将 $[l,mid]$ 中的颜色都加到桶里递归 $(mid,r]$，然后撤销，将 $(mid,r]$ 中的颜色都加到桶里递归 $[l,mid]$。这样我们到区间 $[l,r]$ 的时候，维护的这个桶中已经包含了区间 $[1,l)\cup(r,n]$ 中的所有颜色。然后再处理跨过 $mid$ 的询问区间。这回我们按区间左端点从小到大排序，那么它们的右端点是单调不增的。同样双指针，每次左指针向右扩展到当前询问区间的左端点（不包含这个左端点），右指针向左扩展。把遍历到的颜色都加到桶里，就能找到区间补的最大值。

最后就是处理被非树边覆盖的边。由于 DFS 树只有返祖边，非树边的两个端点中有一个是 LCA，直接差分一下就行。

[code](https://www.luogu.com.cn/paste/2zg29ice)

---

## 作者：Unnamed114514 (赞：0)

首先对于每个连通块显然会选择出现次数最多的颜色。然后的话这个就是最基本的答案，显然断一条边只会让答案只增不减，所以考虑计算增加量。

容易发现只有断掉桥的时候答案才会变化，然后转化成了求子树内和排掉子树的出现最多的颜色次数，直接用 DSU on Tree 即可。

然后注意缩点之后每个点的大小不一定是 $1$，所以找的是带权的重儿子。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N=1e5+5;
int T,n,m,tot,fa[N],a[N],dfn[N],low[N],cnt,root[N],ans[N],res,ret,siz[N],son[N];
bool flg[N],vis[N];
vector<pair<int,int> > G1[N],G2[N];
vector<int> v[N];
int LINE;
struct SegmentTree{
	int t[N<<2];
	#define ls p<<1
	#define rs p<<1|1
	void update(int p,int l,int r,int pos,int val){
		if(l==r){
			t[p]+=val;
			return;
		}
		int mid=l+r>>1;
		if(pos<=mid) update(ls,l,mid,pos,val);
		else update(rs,mid+1,r,pos,val);
		t[p]=max(t[ls],t[rs]);
	}
}f,g;
int find(int x){ return fa[x]=(fa[x]==x?x:find(fa[x])); }
void tarjan(int u,int fa){
	low[u]=dfn[u]=++tot;
	for(auto H:G1[u]){
		int v=H.first,id=H.second;
		if(id==fa) continue;
		if(!dfn[v]){
			tarjan(v,id);
			low[u]=min(low[u],low[v]);
			if(dfn[u]<low[v]) flg[id]=1;
		} else low[u]=min(low[u],dfn[v]);
	}
}
void dfs(int u){
	vis[u]=1;
	for(auto p:v[u]) f.update(1,1,100000,p,1);
	siz[u]=v[u].size(),son[u]=0;
	for(auto H:G2[u]){
		if(vis[H.first]) continue;
		dfs(H.first);
		siz[u]+=siz[H.first];
		if(siz[H.first]>siz[son[u]]) son[u]=H.first;
	}
}
void clear(int u,int fa){
	for(auto p:v[u]) f.update(1,1,100000,p,-1);
	for(auto H:G2[u]){
		if(H.first==fa) continue;
		clear(H.first,u);
	}
}
void clean(int u,int fa){
	for(auto p:v[u]){
		g.update(1,1,100000,p,-1);
		f.update(1,1,100000,p,1);
	}
	for(auto H:G2[u]){
		if(H.first==fa) continue;
		clean(H.first,u);
	}
}
void work(int u,int fa){
	for(auto p:v[u]){
		g.update(1,1,100000,p,1);
		f.update(1,1,100000,p,-1);
	}
	for(auto H:G2[u]){
		if(H.first==fa) continue;
		work(H.first,u);
	}
}
void DSU(int u,int fa){
	if(son[u]){
		for(auto H:G2[u]){
			if(H.second==fa||H.first==son[u]) continue;
			DSU(H.first,H.second);
			clean(H.first,u);
		}
		for(auto H:G2[u]){
			if(H.second==fa||H.first!=son[u]) continue;
			DSU(H.first,H.second);
		}
		for(auto H:G2[u]){
			if(H.second==fa||H.first==son[u]) continue;
			work(H.first,u);
		}
	}
	for(auto p:v[u]){
		g.update(1,1,100000,p,1);
		f.update(1,1,100000,p,-1);
	}
	if(fa) ans[fa]=g.t[1]+f.t[1]-ret;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;++i) cin>>a[i];
		for(int i=1,u,v;i<=m;++i){
			cin>>u>>v;
			G1[u].emplace_back(make_pair(v,i));
			G1[v].emplace_back(make_pair(u,i));
		}
		for(int i=1;i<=n;++i) if(!dfn[i]) tarjan(i,0);
		for(int i=1;i<=n;++i) fa[i]=i;
		for(int i=1;i<=n;++i) for(auto H:G1[i]) if(!flg[H.second]) fa[find(i)]=find(H.first);
		for(int i=1;i<=n;++i) root[i]=++cnt;
		for(int i=1;i<=n;++i) v[find(i)].emplace_back(a[i]);
		for(int i=1;i<=n;++i) for(auto H:G1[i]) if(flg[H.second]) G2[find(i)].emplace_back(make_pair(find(H.first),H.second));
		++LINE;
		for(int i=1;i<=n;++i) if(!vis[i]&&find(i)==i){
			dfs(i);
			ret=f.t[1];
			res+=ret;
			DSU(i,0);
			clean(i,0);
			clear(i,0);
		}
		for(int i=1;i<=m;++i){
			cout<<ans[i]+res;
			if(i!=m) cout<<' ';
		}
		cout<<endl;
		tot=cnt=res=0;
		for(int i=1;i<=m;++i) flg[i]=ans[i]=0;
		for(int i=1;i<=n;++i){
			low[i]=dfn[i]=vis[i]=0;
			G1[i].clear(),G1[i].shrink_to_fit();
			G2[i].clear(),G2[i].shrink_to_fit();
			v[i].clear(),v[i].shrink_to_fit();
		}
	}
	return 0;
}
```

---

## 作者：strcmp (赞：0)

首先被 $u,\,v$ 捆绑在一起形成联通块的，一定只能选一个数做为答案，自然要选择众数。

问题就转化为删掉第 $i$ 条边之后，各自联通块的众数出现次数之和。

先考虑如何加边维护联通块的众数出现次数和。

好做，每个联通块维护一个 Hash 表，合并就是启发式合并，时间复杂度 $\Theta(n \log n)$。

删掉第 $i$ 个位置的贡献，这种问题是经典分治，先将右半部分纳入修改并递归左半部分。回溯到当前，再撤销右半部分的修改，进行左半部分的修改，递归右半部分。撤销直接用个操作栈维护即可。

好了你得到一个 $\Theta(Tn \log^2 n)$ 的垃圾做法，它的两只 log 甚至还要再乘一个 Hash 表，常数炸完了。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define mid (l + r >> 1)
using namespace std;
typedef long long int ll;
using ull = unsigned long long int;
using pii = pair<int, int>;
using pli = pair<ll, int>;
#define tb __gnu_pbds::gp_hash_table<int, int>
constexpr int maxn = 2e5 + 10, mod = 1e9 + 7;
int T, n, m, fa[maxn], sz[maxn], top, a[maxn], ans = 0, mx[maxn]; tb t[maxn]; vector<pii> st[maxn];
int fd(int x) { return fa[x] == x ? x : fd(fa[fa[x]]); }
inline void mg(int x, int y) {
	x = fd(x), y = fd(y);
	if (x == y) return;
	if (sz[y] < sz[x]) swap(x, y);
	fa[x] = y; sz[y] += sz[x];
	vector<pii> o(t[x].size() + 2); o[0] = { x, -1 }; int p = 1, W = mx[y];
	for (pii u : t[x]) {
		t[y][u.X] += u.Y, o[p] = u, ++p;
		if (t[y][u.X] > W) W = t[y][u.X];
	}
	o[p] = { mx[y], -2 }; ans += W - mx[x] - mx[y]; mx[y] = W; 
	st[++top] = o;
}
inline void rvk() {
	int x = st[top].front().X, W = st[top].back().X;
	sz[fa[x]] -= sz[x]; ans += W + mx[x] - mx[fa[x]]; mx[fa[x]] = W;
	for (pii u : st[top]) {
		if (u.Y != -1 && u.Y != -2) {
			t[fa[x]][u.X] -= u.Y;
			if (!t[fa[x]][u.X]) t[fa[x]].erase(u.X);
		}
	}
	fa[x] = x; st[top].clear(); --top;
}
int U[maxn], V[maxn];
void solve(int l, int r) {
	if (l == r) return void(printf("%d ", ans)); int pre = top;
	rep(i, mid + 1, r) mg(U[i], V[i]); solve(l, mid);
	while (top > pre) rvk();
	rep(i, l, mid) mg(U[i], V[i]); solve(mid + 1, r);
}
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		rep(i, 1, n) scanf("%d", &a[i]), t[i][a[i]] = 1, fa[i] = i, sz[i] = mx[i] = 1; ans = n;
		rep(i, 1, m) scanf("%d%d", &U[i], &V[i]);
		solve(1, m); ans = top = 0; puts("");
		rep(i, 1, n) t[i].clear(), mx[i] = fa[i] = sz[i] = 0;
	}
	return 0;
}
```

因为两只 log 甚至要乘一个哈希表，目前应该很难有希望卡过去。

所以考虑 $\Theta(n \log n)$ 的做法。

首先图是不好做的，但是我们显然可以先缩边双，它变成了一棵树，然后我们一定是删树边才会对答案有影响。

注意众数出现次数是**可以支持减**的，维护桶的权值桶即可。

先把不删树边的答案求出来塞到非树边上。

然后考虑删树边，相当于求子树内和子树外的众数。

前者简单，DSU on tree 板子。

后者也是 DSU on tree 板子，你考虑先让桶为整棵树，然后将子树时候的 `ins` 改为 `del`，`del` 改为 `ins`。

时间复杂度 $\Theta(Tn \log n)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define mid (l + r >> 1)
using namespace std;
typedef long long int ll;
using ull = unsigned long long int;
using pii = pair<int, int>;
using pli = pair<ll, int>;
#define tb unordered_map<int, int>
constexpr int maxn = 2e5 + 10, mod = 1e9 + 7;
struct edge { int to, nxt; } nd[maxn << 1]; int h[maxn], cnt, n, m, a[maxn], T, id[maxn];
inline void add(int u, int v, int p) { id[cnt] = p, nd[cnt].nxt = h[u], nd[cnt].to = v, h[u] = cnt++; }
int dfn[maxn], low[maxn], ecc[maxn], tot, dct, vis[maxn], st[maxn], top = 0, dw[maxn]; vector<int> g[maxn];
void tj(int u, int f) {
	dfn[u] = low[u] = ++dct; st[++top] = u; 
	for (int i = h[u]; ~i; i = nd[i].nxt) {
		int v = nd[i].to;
		if (!dfn[v]) tj(v, i), low[u] = min(low[u], low[v]);
		else if ((i ^ 1) != f) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		++tot; ecc[u] = tot; 
		while (st[top] != u) ecc[st[top]] = tot, --top; --top;
	}
}
int s[maxn], c[maxn], sz[maxn], son[maxn], fa[maxn], ans, U[maxn], V[maxn], S[maxn], mx[maxn], rmx[maxn], ALL, ANS[maxn];
inline void ins(int x) { for (int u : g[x]) { --s[c[a[u]]], ++c[a[u]], ++s[c[a[u]]]; if (c[a[u]] > ans) ans = c[a[u]]; } }
inline void del(int x) { for (int u : g[x]) { --s[c[a[u]]]; if (!s[ans]) --ans; --c[a[u]]; ++s[c[a[u]]]; } }
void all(int u, int f, int o) { o == 1 ? (ins(u), dw[u] = 1) : (del(u), 1); for (int i = h[u]; ~i; i = nd[i].nxt) { int v = nd[i].to; if (v != f) all(v, u, o); } }
void pre(int u, int f) {
	sz[u] = g[u].size();
	for (int i = h[u]; ~i; i = nd[i].nxt) {
		int v = nd[i].to;
		if (v != f) pre(v, u), sz[u] += sz[v], sz[son[u]] < sz[v] && (son[u] = v);
	}
}
void dfs(int u, int f, int o, int t) {
	for (int i = h[u]; ~i; i = nd[i].nxt) { int v = nd[i].to; if (v != f && v != son[u]) dfs(v, u, 0, t); }
	if (son[u]) dfs(son[u], u, 1, t);
	for (int i = h[u]; ~i; i = nd[i].nxt) { int v = nd[i].to; if (v != f && v != son[u]) all(v, u, t); }
	t ? ins(u) : del(u); (t == 1 ? mx[u] : rmx[u]) = ans; if (o == 0) all(u, f, t ^ 1);
}
void dfs2(int u, int f) {
	for (int i = h[u]; ~i; i = nd[i].nxt) {
		int v = nd[i].to; 
		if (v != f) ANS[id[i]] = ALL + rmx[v] + mx[v], dfs2(v, u);
	}
}
int rt[maxn], p = 0;
int main() {
	scanf("%d", &T);
	while (T--) {
		memset(h, -1, sizeof(h)); cnt = tot = 0; 
		scanf("%d%d", &n, &m);
		rep(i, 1, n) scanf("%d", &a[i]);
		for (int i = 1, u, v; i <= m; i++) scanf("%d%d", &u, &v), add(u, v, i), add(v, u, i), U[i] = u, V[i] = v;
		rep(i, 1, n) if (!dfn[i]) tj(i, 0);
		rep(i, 1, n) g[ecc[i]].pb(i);
		memset(h, -1, sizeof(h)); cnt = 0;
		rep(i, 1, m) {
			int u = ecc[U[i]], v = ecc[V[i]];
			if (u != v) add(u, v, i), add(v, u, i);
		}
		int SUM = 0;
		rep(i, 1, tot) if (!dw[i]) all(i, 0, 1), rt[++p] = i, S[p] = ans, SUM += S[p], all(i, 0, 0);
		rep(i, 1, m) ANS[i] = SUM;
		rep(i, 1, p) {
			int u = rt[i]; ALL = SUM - S[i];
			pre(u, 0); dfs(u, 0, 0, 1); all(u, 0, 1); 
			dfs(u, 0, 0, 0); dfs2(u, 0); all(u, 0, 0);
		}
		rep(i, 1, m) printf("%d ", ANS[i]); puts("");
		ALL = p = 0; 
		rep(i, 1, n) g[i].clear(), s[i] = c[i] = sz[i] = son[i] = fa[i] = S[i] = mx[i] = rmx[i] = ANS[i] = dw[i] = ecc[i] = dfn[i] = low[i] = vis[i] = dw[i] = 0; top = dct = ans = 0;
		rep(i, 1, m) id[i] = 0;
	}
	return 0;
}
```

---

## 作者：kkxacj (赞：0)

#### 前言

此题本人交了四页，感觉自己很抽象，写篇题解加深影响。

#### 思路

显然，这 $m$ 个限制可以转化为 $m$ 条边，构成的若干联通快都必须选相同的颜色，统计每个联通快相同颜色就行了。

对于 $m$ 次询问，容易发现，若这条边**不是桥**，即删去这条边联通快个数没有增加，那么答案和没删是一样的，所以我们可以先 **`tarjan` 缩点**。

缩完点后，设每个点变为了 $col_i$，对于一次询问，若 $col_x$ 与 $col_y$ 不一样，我们钦定 $col_y$ 为 $col_x$ 父亲，则这个联通块贡献变为了 **$col_x$ 子树含自己最大颜色出现次数和子树外不含自己最大颜色出现次数**，很经典的 `dsu on tree` 对于求子树内的，显然就是[这道题](https://www.luogu.com.cn/problem/CF600E)了，对于求子树外的，我们先把所有以轻儿子为子树的贡献加入，然后去递归重儿子，最后暴力枚举轻儿子删掉子树贡献然后递归即可。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 1e5+10;
int t,n,m,a[N],head[N],son[N],v2[N],fa[N],bj[N],id,siz[N],v[N],v1[N],o1,cnt,col[N],dfn[N],low[N],st[N],tot,o,ans;
int mx_son[N],mx_fa[N],sum;//子树内(含)和子树外(不含)最大颜色相同个数 
vector<int>V[N];//注意这里缩点后每个点会包含多个点权，可以用vector存储 
struct w1
{
	int x,y;
}c[N];
struct w
{
	int to,nxt;
}b[N<<1];
inline void add(int x,int y)
{
	b[++cnt].nxt = head[x];
	b[cnt].to = y;
	head[x] = cnt;
}
void tarjan(int x,int y)//缩点 
{
	st[++tot] = x,cnt++,low[x] = dfn[x] = cnt; int Sum = 0;
	for(int i = head[x];i;i = b[i].nxt)
	{
		if(b[i].to == y) Sum++;
		if(!dfn[b[i].to]) tarjan(b[i].to,x),low[x] = min(low[x],low[b[i].to]);
		else if(b[i].to != y) low[x] = min(low[x],dfn[b[i].to]);
	}
	if(low[x] == dfn[x] && Sum <= 1)
	{
		o++;
		while(st[tot+1] != x) V[o].push_back(a[st[tot]]),col[st[tot]] = o,tot--; 
	} 
}
void dfs(int x,int y)//初始化，求重儿子，fa 
{ 
	bj[x] = id; siz[x] = V[x].size(); fa[x] = y,son[x] = 0;
	for(int i = head[x];i;i = b[i].nxt)
		if(b[i].to != y)
		{
			dfs(b[i].to,x),siz[x] += siz[b[i].to];
			if(siz[b[i].to] > siz[son[x]]) son[x] = b[i].to;
		}
}
inline void Add(int x)//加操作 
{
	for(int i = 0;i < V[x].size();i++) 
	{
		v1[v[V[x][i]]]--,v[V[x][i]]++,v1[v[V[x][i]]]++;
		if(v[V[x][i]] > sum) sum = v[V[x][i]]; 
	}
}
inline void Del(int x)//减操作 
{
	for(int i = 0;i < V[x].size();i++) 
	{
		v1[v[V[x][i]]]--;
		if(!v1[sum]) sum--;
		v[V[x][i]]--,v1[v[V[x][i]]]++;
	}
}
void dfs_add(int x,int y)//加
{
	Add(x);
	for(int i = head[x];i;i = b[i].nxt)
		if(b[i].to != y)
			dfs_add(b[i].to,x);
} 
void dfs_del(int x,int y)//减 
{
	Del(x); 
	for(int i = head[x];i;i = b[i].nxt)
		if(b[i].to != y)
			dfs_del(b[i].to,x);
} 
void dfs_empty(int x,int y)//清空 
{
	for(int i = 0;i < V[x].size();i++) v[V[x][i]] = 0;
	for(int i = head[x];i;i = b[i].nxt)
		if(b[i].to != y)
			dfs_empty(b[i].to,x);
} 
void Dfs1(int x,int y)//计算子树外贡献 
{
	mx_fa[x] = sum; Add(x);
	for(int i = head[x];i;i = b[i].nxt)
		if(b[i].to != y && b[i].to != son[x])
			dfs_add(b[i].to,x);
	if(son[x]) Dfs1(son[x],x);//先跑重儿子 
	for(int i = head[x];i;i = b[i].nxt)
		if(b[i].to != y && b[i].to != son[x])
		{
			dfs_del(b[i].to,x);
			Dfs1(b[i].to,x);
		}
}
void Dfs(int x,int y)//计算子树贡献 
{
	for(int i = head[x];i;i = b[i].nxt)
		if(b[i].to != y && b[i].to != son[x])//先跑轻儿子
			Dfs(b[i].to,x),dfs_del(b[i].to,x),sum = 0; 
	if(son[x]) Dfs(son[x],x);
	for(int i = head[x];i;i = b[i].nxt)
		if(b[i].to != y && b[i].to != son[x])
			dfs_add(b[i].to,x);
	Add(x); mx_son[x] = sum;
}
signed main()
{
	read(t);
	while(t--)
	{
		read(n),read(m); ans = cnt = tot = o = 0;
		for(int i = 1;i <= n+10;i++) V[i].clear(),st[i] = v[i] = v1[i] = bj[i] = fa[i] = col[i] = son[i] = head[i] = low[i] = dfn[i] = 0;
		for(int i = 1;i <= n;i++) read(a[i]);
		for(int i = 1;i <= m;i++) 
		{
			read(c[i].x),read(c[i].y);
			if(c[i].x != c[i].y) add(c[i].x,c[i].y),add(c[i].y,c[i].x);
		}
		cnt = 0; for(int i = 1;i <= n;i++) if(!dfn[i]) tarjan(i,0);
		for(int i = 1;i <= n;i++) mx_son[i] = mx_fa[i] = head[i] = 0; cnt = 0;
		for(int i = 1;i <= m;i++)
			if(col[c[i].x] != col[c[i].y]) 
				add(col[c[i].x],col[c[i].y]),add(col[c[i].y],col[c[i].x]); 
		for(int i = 1;i <= o;i++)
			if(!mx_son[i])
			{
				id = i,sum = 0,dfs(i,0),Dfs(i,0);
				dfs_empty(i,0);  for(int j = 1;j <= siz[i];j++) v1[j] = 0;//清空 
				sum = 0; Dfs1(i,0),ans += mx_son[i]; 
				dfs_empty(i,0); for(int j = 1;j <= siz[i];j++) v1[j] = 0;//清空 
			}
		for(int i = 1;i < m;i++)
			if(col[c[i].x] == col[c[i].y]) print(ans),pc(' ');//分讨情况 
			else if(fa[col[c[i].x]] == col[c[i].y]) print(ans-mx_son[bj[col[c[i].x]]]+mx_son[col[c[i].x]]+mx_fa[col[c[i].x]]),pc(' ');
			else print(ans-mx_son[bj[col[c[i].y]]]+mx_son[col[c[i].y]]+mx_fa[col[c[i].y]]),pc(' ');
		for(int i = m;i <= m;i++) //行末不能有空格 
			if(col[c[i].x] == col[c[i].y]) print(ans);
			else if(fa[col[c[i].x]] == col[c[i].y]) print(ans-mx_son[bj[col[c[i].x]]]+mx_son[col[c[i].x]]+mx_fa[col[c[i].x]]);
			else print(ans-mx_son[bj[col[c[i].y]]]+mx_son[col[c[i].y]]+mx_fa[col[c[i].y]]);
		pc('\n');
	}
	flush();
	return 0;
}
/*

m条边可以构成一个图
tarjan缩点，因为若该边在环上，删去后未改变图的连通性
缩完后变成若干颗树，dsu on tree 统计最大子树颜色数和最大子树外颜色数即可 
*/
```

---

## 作者：王江睿 (赞：0)

图 $G$ 中各点有颜色 $c_i$。**断去一条边后**，对每一个连通分量 $H_j$ 指定颜色 $d_j$。求

$$\sum_{i \in V} \exists j : i \in H_j : [c_i = d_j]$$
的最大值。

----

方法是，首先边双缩点，然后用 `std::map` 维护子树内和子树外的最大颜色数（利用两个 `std::map`，分别保存各颜色的数量，和各颜色数的数量）。需要注意的是处理子树外的最大颜色数时，受限于单个 `std::map` 空间占用 $O(N)$，必须用传统的先加轻儿子，再加重儿子的写法。

（实际上，笔者认为这样的写法称不上 `dsu on tree`，和合并关系也不大：虽然我们长期这末称呼它。其本质大概算是启发式和分治思想的一个结合。分拆到子树的问题是分治；而向上回溯时，延续最重子树贡献，则应当归于启发式。）

注意减到 $0$ 以后 `erase` 的问题。不仅刨除时要 `erase`，**增加时同样要 `erase`**。考虑增加前的低位置，之后也可能是干扰答案的最高位置。

最后本题是多测，有重边，带自环。

```cpp
// # for GNU C++14
#include<bits/stdc++.h>
using namespace std;
#define RSET(_$,$_) for(int _=1;_<=$_;++_) _$[_].clear()
constexpr int N=1e5+7;

int c[N],po[N],low[N],c1,c2;
basic_string<pair<int,int>> e[N],g[N];
basic_string<int> stk,cpo[N];
inline void tarjan(int x,int f){
	stk+=x;
	int dfn=low[x]=++c1;
	for(auto [i,_]:e[x]) if(_!=f){
		if(!low[i]) tarjan(i,_);
		low[x]<low[i]?: low[x]=low[i];
	}
	if(low[x]==dfn){
		++c2;
		do	cpo[c2]+=stk.back(),
			po[stk.back()]=c2,
			stk.pop_back();
		while(cpo[c2].back()!=x);
	}
}

map<int,int> M[N],P,_p,Q,_q;
int A[N],h[N],s[N],res[N];
bitset<N> vi;
inline void dfs1(int x,int f){
	int t=0;
	s[x]=1;
	for(auto [i,_]:g[x]) if(i!=f){
		A[i]=_, dfs1(i,x);
		s[i]<t?: t=s[h[x]=i];
		s[x]+=s[i];
	}
}
inline void upd(int x){
	int t=0;
	for(auto [k,c]:M[x])
		--_p[t=P[k]], P[k]=t+c, ++_p[t+c];
	for(auto [k,c]:M[x])
		--_q[t=Q[k]]?: _q.erase(t),
		Q[k]=t-c, ++_q[t-c];
}
inline void dfs2(int x,int f){
	for(auto [i,_]:g[x]) if(i!=f)
		dfs2(i,x);
	upd(x);
}
int la;
void dfs3(int x,int f,bool d=0){
	vi[x]=1;
	if(!h[x]) goto tag;
	for(auto [i,_]:g[x]) if(i!=f&&i!=h[x]) dfs3(i,x);
	dfs3(h[x],x,1);
	for(auto [i,_]:g[x]) if(i!=f&&i!=h[x]) dfs2(i,x);
	tag: upd(x);
	res[A[x]]=_p.rbegin()->first+
			  _q.rbegin()->first-la;
	if(!d){
		for(auto [k,c]:P) --_q[f=Q[k]]?: _q.erase(f), Q[k]=f+c, ++_q[f+c];
		P.clear(); _p.clear();
	}
}
inline void dfs4(int x,int f){
	for(auto [i,_]:g[x]) if(i!=f)
		dfs4(i,x);
	for(auto [k,c]:M[x])
		--_q[f=Q[k]]?: _q.erase(f), Q[k]=f+c, ++_q[f+c];
}

main(){
cin.tie(0)->sync_with_stdio(0);
int t;
cin>>t;
while(t--){
	int n,m,tans=c1=c2=0;
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>c[i];
	for(int i=1,p,q;i<=m;++i) cin>>p>>q,
		e[p]+={q,i}, e[q]+={p,i};
	for(int i=1;i<=n;++i) 
		if(!low[i]) tarjan(i,0);
	for(int i=1;i<=c2;++i)
		for(int j:cpo[i])
			++M[i][c[j]];
	for(int i=1;i<=n;++i) for(auto [j,id]:e[i])
		if(po[i]!=po[j])
			g[po[i]]+={po[j],id};

	for(int i=1;i<=c2;++i) 
		if(!s[i]) dfs1(i,A[i]=0);
	for(int i=1;i<=c2;++i) if(!vi[i]){
		P.clear(), _p.clear();
		Q.clear(), _q.clear();
		dfs4(i,0);
		tans+=la=_q.rbegin()->first;
		dfs3(i,0,1);
	}
	for(int i=1;i<=m;++i)
		cout<<res[i]+tans<<" \n"[i==m];

RSET(e,n); RSET(g,c2); RSET(cpo,c2); RSET(M,c2);
vi.reset();
bzero(h+1,4*c2);
bzero(s+1,4*c2);
bzero(res+1,4*m);
bzero(low+1,4*n);
}
}
```

---

