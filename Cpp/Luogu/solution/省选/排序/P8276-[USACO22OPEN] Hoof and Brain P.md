# [USACO22OPEN] Hoof and Brain P

## 题目描述

给定一个包含 $N$ 个结点和 $M$ 条边的有向图（$2 \leq N \leq 10^5$, $1 \leq M \leq 2 \cdot 10^5$），Farmer John 的奶牛们喜欢玩以下的双人游戏。

在图中的不同结点上放置两个指示物（可以用一些与奶牛相关的物品代替指示物）。每一回合，一名玩家，脑，选择一个需要沿某一条出边移动的指示物。另一名玩家，蹄，选择沿着哪条出边移动该指示物。两个指示物在任何时刻不允许处于同一个结点上。如果在某些时刻蹄不能做出合法的行动，则脑获胜。如果游戏可以无限进行下去，则蹄获胜。

给定 $Q$ 个询问（$1 \leq Q \leq 10^5$），包含两个指示物所在的初始结点。对于每个询问，输出哪名玩家获胜。

## 说明/提示

【数据范围】

脑可以通过选择结点 $5$ 赢得第一局游戏；此时蹄将没有合法的行动。

脑可以通过选择结点 $4$ 然后选择结点 $7$ 赢得最后一局游戏；此时蹄没有合法的行动。

蹄赢得其他局游戏。

【测试点性质】

- 测试点 2-3 满足 $N\le 100$，$M\le 200$。
- 测试点 4-9 满足 $N\le 5000$。
- 测试点 10-21 没有额外限制。

## 样例 #1

### 输入

```
9 10
1 2
2 3
3 4
4 7
3 5
1 6
6 8
8 9
9 6
7 2
4
1 5
1 2
1 6
2 4```

### 输出

```
BHHB```

# 题解

## 作者：peppaking8 (赞：31)

USACO 的题都超有意思的。忘了题意的同志们，我们再来回顾一下：

### 题意

给定 $n$ 个点，$m$ 条边的无重边、自环的有向图。甲乙两人玩游戏，起初在图上 $x,y$ 点处各放一个棋子，甲先选择一个棋子，乙必须将这个棋子沿着边移动，还需保证两个棋子不重合。轮流进行这一过程，若乙不能移动则乙输，若游戏能无限进行则甲输。对 $q$ 组询问 $(x,y)$，求谁有必胜策略。$n,q\le 10^5$，$m\le 2\times 10^5$。

### 分析

在做完 P 组的 T3 后，发现第一题~~是 Benq 出的，所以很不可做~~，所以我们有大把的时间来好好研究这道 T2。所以我们一步步地分析这个题目。下面称题目中的脑 (Brain,B) 为甲，蹄 (Hoof,H) 为乙。

![](https://cdn.luogu.com.cn/upload/image_hosting/8u8t5tuw.png)

首先，观察样例的询问，为什么 $(1,5)$ 甲会赢呢？因为 $5$ 点没有出边，于是甲选择这个棋子，乙无处可走。所以初步想法是，如果有一个棋子所在的点出发**只能走有限步**，就一定是甲赢。如何找到这样的点呢？经典的处理办法是建反图跑拓扑排序，在拓扑序里的点就是无法到达环的点，自然只能走有限步。所以在接下来的分析中，可以将这些点删去，从而不妨设**所有点出发都能到达环**。

题目没有结束，我们注意到样例中还有 $(2,4)$ 甲会赢。甲可以指定 $4$，此时乙只能移动到 $7$，然后甲选 $7$，乙无处可走。也就是说，如果对于一个棋子所在点 $u$，它想走无限多步**必须经过点** $v$，且另外一个棋子在 $v$，那么就是甲赢。这个要求感觉有些苛刻...有没有更一般的结论呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/quhbhwmx.png)

比如上图例子，如果棋子初始在 $(2,4)$，那么甲可以先选 $2$ 再选 $4$，这两个棋子都必须到 $3$，产生相遇，甲赢。所以说，我们还可以把这个结论加强，若 $u_1,u_2$ 想走无限步都一定会经过一个点 $v$，那么 $(u_1,u_2)$ 一定是甲赢。形式化地：
> 定义 $v$ 是 $u$ 的“**支配点**”，当且仅当 $u$ 走无限多步必须经过 $v$。也即，在删去 $v$ 后，$u$ 不在任何大小 $>1$ 的强连通分量内。$u$ 也是 $u$ 的支配点。令 $F(u)$ 为 $u$ 的所有支配点构成的集合，称为**支配集**。对于询问 $u_1,u_2$，若 $F(u_1)\cap F(u_2)$ 非空，则甲赢。

对于相交为空的情形，事实上乙会获胜，因为每次都可以避免走到另一个棋子的支配点上。所以至此我们已经找到了甲获胜的等价条件：**支配集相交非空**。

接下来自然就有了 $O(n^2+qn)$ 的算法：每次删掉一个点，看有多少点无法走到环上，就更新这些点的支配集。询问的时候直接暴力判交即可。事实上，后者还可以用 bitset 优化到 $O(\dfrac{qn}{w})$，可以通过测试点 1-9。

想要获得更加优秀的做法，就不能暴力求出支配集，而是研究支配的特殊性质。这里我们给出两条：

> 1. **传递性**：$v$ 支配 $u$，$w$ 支配 $v$，则 $w$ 支配 $u$。     
> 2. **偏序性**：$v_1,v_2$ 都支配 $u$，则 $v_1,v_2$ 之间也有支配关系。

根据支配点的定义，容易证明以上两条。其中第二条给了我们启发：既然 $v_1,v_2$ 有共同支配的点，那么它们之间也会互相支配，也就是说，$u,v_1,v_2$ 两两有共同支配点。那么...如果将支配关系看作无向图的话，是不是连通块内的任两点都有共同支配点呢？

回顾 [NOI2021 庆典](https://www.luogu.com.cn/problem/P7737)。发现那道题对图的限制和第二条很相似，最后的结论是在缩强连通分量之后图为一棵树。强连通分量内的任两点自然有共同支配点；在树上的两点，因为它们共同指向祖先，那么它们也会有共同支配点——祖先！所以至此我们发现，**若将支配的关系看作无向，那么连通分支里的任两点的支配集相交非空**。

为什么这一结论十分重要？因为它让这道题变得可做：只需要找到不超过 $n-1$ 个支配关系，就能找到所有的连通分支，进而可以用并查集快速地处理询问！

那么如何找到这些支配关系呢？容易想到的是，若出度 $\deg u=1$，设 $u$ 连向 $v$，则 $v$ 一定支配 $u$。那再想，既然 $u,v$ 在支配关系图中同属一个连通块，那是否能在原图里把它们合并呢？事实上可以，因为但凡经过 $u$ 的点一定会下一步经过 $v$，故将他们合并起来并无大碍。合并时，注意 $u,v$ 缩成的点 $u'$ 可能存在自环。删去重边后，可能会出现新的 $u_0$ 满足 $\deg u_0=1$，就接着缩点就好了。为了快速地维护缩点的过程，我们可以回顾 [WC2021 括号路径](https://www.luogu.com.cn/problem/P7323) 这一题，用线段树合并/启发式合并解决。实现的好可以 $O(n\log n)$，不过两个 $\log $ 也问题不大。

当然在缩点后，虽然所有点的出度都 $\ge 2$ 了，但仍然不知道是否找全了支配关系。这时惊奇地发现：当前求出的连通分支就是正确的！

> **引理**：若图中每个点的出度 $\ge 2$，则不存在任何不相同两点的支配关系。   
> **证明**：每次从 $u$ 都可找到不经过点 $v$ 的路径，故对任意 $u\not=v$，$v$ 都不支配 $u$。证毕。

至此我们解决了这道题。或许你在担心实现起来是不是非常麻烦，或是在后悔赛时没有想到正解...不过没关系，~~USACO 算什么~~ 无论何时，只要领悟了这道题的精髓，从每道题里学到新知识，为什么不值得高兴呢？:)

Talk is cheap, show you the code... 提前声明，代码太丑，仅供参考~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n,m,q;
struct Edge{
	int u,v;
	int nxt;
}edge[N<<1];
int head[N],tot=0;
int ind[N],outd[N];
bool ok[N];
int fa[2][N];
int rt[2][N];
struct Tree{
	int siz;
	int ch[2];
}t[N<<6];
int ttot=0,was[N<<5],wastot=0;
bool have[N];
queue<int> tq;
string ans;
inline void add_edge(int u,int v){
	tot++;
	edge[tot]=(Edge){u,v,head[u]};
	head[u]=tot;
	ind[v]++,outd[u]++;
}
#define lson t[id].ch[0]
#define rson t[id].ch[1]
inline void pushup(int id){
	t[id].siz=t[lson].siz+t[rson].siz;
}
inline int NewNode(){ // 加了空间回收，不然会 MLE
	if(wastot){
		return was[wastot--];
	}
	return (++ttot);
}
inline void addwas(int id){
	if(wastot>=(N<<5)) return ;
	t[id].siz=t[id].ch[0]=t[id].ch[1]=0;
	was[++wastot]=id;
}
void Add(int &id,int L,int R,int k,bool del){
	if(!id) id=NewNode();
	if(L==R){
		t[id].siz=del;
		if(!del) addwas(id),id=0;
		return ;
	}
	int mid=(L+R)>>1;
	if(k<=mid) Add(lson,L,mid,k,del);
	else Add(rson,mid+1,R,k,del);
	pushup(id);
	if(!t[id].siz) addwas(id),id=0;
}
bool Have(int id,int L,int R,int k){
	if(!id) return false;
	if(L==R&&t[id].siz) return true;
	int mid=(L+R)>>1;
	return (k<=mid)?Have(lson,L,mid,k):Have(rson,mid+1,R,k);
}
int Findson(int id,int L,int R){
	if(L==R) return L;
	int mid=(L+R)>>1;
	if(t[lson].siz) return Findson(lson,L,mid);
	else return Findson(rson,mid+1,R);
}
inline int find(int k,int x){
	if(x==fa[k][x]) return x;
	return fa[k][x]=find(k,fa[k][x]);
}
int shanx,shany;
void Merge(int &x,int y,int L,int R){
	if(!y) return ;
	if(!x) x=y;
	if(L==R){
		if(t[y].siz){
			Add(rt[1][shanx],1,n,L,1);
			int pp=find(0,L);
			Add(rt[0][pp],1,n,shany,0),Add(rt[0][pp],1,n,shanx,1);
			if(t[rt[0][pp]].siz==1 && !have[pp]) tq.push(pp);
		}
		t[x].siz=(t[x].siz|t[y].siz);
		return ;
	}
	int mid=(L+R)>>1;
	Merge(t[x].ch[0],t[y].ch[0],L,mid);
	Merge(t[x].ch[1],t[y].ch[1],mid+1,R);
	pushup(x);
}
inline int makemerge(int k,int x,int y){ // y merge in x
	int fx=find(k,x),fy=find(k,y);
	if(fx!=fy) fa[k][fy]=fx;
}
void Topo(){
	for(int i=1;i<=n;i++){
		if(!ind[i]) tq.push(i),ok[i]=true;
	}
	while(!tq.empty()){
		int tp=tq.front();tq.pop();
		for(int i=head[tp];i;i=edge[i].nxt){
			int v=edge[i].v;
			if(!(--ind[v])) tq.push(v),ok[v]=true;
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(v,u);
	}
	Topo();
	for(int i=1;i<=m;i++){
		int u=edge[i].u,v=edge[i].v;
		if(ok[u] || ok[v]) continue;
		Add(rt[0][v],1,n,u,1);
		Add(rt[1][u],1,n,v,1);
	}
	for(int i=1;i<=n;i++){
		fa[0][i]=fa[1][i]=i;
		if(ok[i]) continue;
		if(t[rt[0][i]].siz==1) tq.push(i);
	}
	while(!tq.empty()){
		int tp=tq.front();tq.pop();
		int now=find(0,tp),now1=find(1,tp);
		if(t[rt[0][now]].siz!=1 || have[now]) continue;
		int to=Findson(rt[0][now],1,n),nowto=find(0,to),nowto1=find(1,to);
		makemerge(0,to,tp);
		if(Have(rt[0][nowto],1,n,now1)) Add(rt[0][nowto],1,n,now1,0),Add(rt[1][now1],1,n,nowto,0),have[nowto]=true;
		Add(rt[1][nowto1],1,n,now,0);
		if(t[rt[1][now1]].siz < t[rt[1][nowto1]].siz){
			makemerge(1,nowto1,now1);
			shanx=nowto1,shany=now1,Merge(rt[1][nowto1],rt[1][now1],1,n);
		}
		else{
			makemerge(1,now1,nowto1);
			shanx=now1,shany=nowto1,Merge(rt[1][now1],rt[1][nowto1],1,n);
		}
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		if(ok[u] || ok[v]){
			ans+='B';
			continue; 
		}
		int fu=find(0,u),fv=find(0,v);
		if(fu==fv) ans+='B';
		else ans+='H';
	}
	cout<<ans<<endl;
}
```

---

## 作者：Kubic (赞：26)

牛题，场上硬磕 2.5h 淦出来了。

先对**反图**进行拓扑排序，如果一个点在拓扑排序的过程中入度变为了 $0$，那么称这个点为好点。

如果询问的两个点中有至少一个是好点，那么显然 Brain 必胜。

由于 Hoof 一旦走到好点上就死定了，所以我们可以直接把所有好点都删除，考虑这个新图。

显然这个新图中每个点出度都不为 $0$。

我们考虑给每一个点 $u$ 染一种颜色 $col_u$。进行如下过程：

- 初始时每个点 $u$ 都有 $col_u=u$。

- 如果 $u$ 的所有出边指向的 $v$ 颜色全部都相同，那么将所有颜色为 $col_u$ 的点的颜色改为 $col_v$。

- 重复上一步直到颜色不再变化。

先给出结论：如果初始两个点颜色相同，则 Brain 必胜，否则 Hoof 必胜。

为什么它是对的呢？

我们考虑一个点的颜色的实际意义：假设有一颗棋子在 $u$ 上，令 Brain 不断地钦定这颗棋子，那么它无论怎么移动一定在某个时刻经过了 $col_u$ 这个点。

分两种情况分别讨论：

- 如果初始两个点颜色都为 $c$，那么我们可以让它们在 $c$ 这个点上堵死。因此 Brain 必胜。

- 如果初始两个点颜色分别为 $c_1,c_2$，那么无论 Brain 怎么选，Hoof 都有至少一种走法可以使得走完后两个点颜色不同。因此 Hoof 必胜。

有了这些结论后，我们就只需要快速维护每个点的 $col$ 即可。

这一部分就很容易了，只需要对于每个点维护它的出边指向的点的颜色种数，每次启发式合并两个集合即可。

时间复杂度 $O(m\log n)$。

参考代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100005
#define pb push_back
int n,m,c,dg[N],q[N],rt[N],w1[N],ps[N];bool vs[N];
vector<int> e[N],e1[N],vc[N];map<int,int> w[N];
void upd(int u,int vl)
{
	for(auto v:e[u]) if(!vs[v])
	{
		--w[v][rt[u]];if(!w[v][rt[u]]) --w1[v];
		if(!w[v][vl]) ++w1[v];++w[v][vl];
		if(w1[v]==1) vs[v]=1,q[++q[1]]=v;
	}rt[u]=vl;
}
void merge(int u,int v)
{
	u=rt[u];v=rt[v];if(u==v) return;
	if(vc[u].size()>vc[v].size()) swap(u,v);
	for(auto i:vc[u]) upd(i,v),vc[v].pb(i);vc[u].clear();
}
int main()
{
	scanf("%d %d",&n,&m);q[0]=2;q[1]=1;
	for(int i=1,u,v;i<=m;++i)
		scanf("%d %d",&u,&v),e1[v].pb(u),++dg[u];
	for(int i=1;i<=n;++i) {vc[i].pb(i);if(!dg[i]) q[++q[1]]=i;}
	while(q[0]<=q[1])
	{
		int u=q[q[0]++];rt[u]=0;
		for(auto v:e1[u]) {--dg[v];if(!dg[v]) q[++q[1]]=v;}
	}q[0]=2;q[1]=1;
	for(int i=1;i<=n;++i) if(dg[i])
		for(auto j:e1[i]) if(dg[j]) e[i].pb(j),ps[j]=i;
	for(int i=1;i<=n;++i) if(dg[i])
	{rt[i]=i;for(auto j:e[i]) {if(!w[j][i]) ++w1[j];++w[j][i];}}
	for(int i=1;i<=n;++i) if(w1[i]==1) q[++q[1]]=i;
	while(q[0]<=q[1]) {int u=q[q[0]++];merge(u,ps[u]);}
	scanf("%d",&c);
	for(int i=1,u,v;i<=c;++i)
	{
		scanf("%d %d",&u,&v);u=rt[u];v=rt[v];
		if(!u || !v) putchar('B');else putchar(u==v?'B':'H');
	}return 0;
}
```

---

## 作者：Elma_ (赞：5)

首先可以注意到，如果某个棋子所在的点没有出边，那么甲只需要选择这个棋子就能够获胜。

于是我们可以将这些点标记，然后将它们从原图中删除。但在完成删除操作后，可能又会有新的节点出边数量变成了 $0$，我们需要重复这样的删除操作只到图中任意节点都有至少 $1$ 条出边。

现在我们考虑一个只有 $1$ 条出边的节点 $x$，假设这条边指向的节点是 $y$，那么对于任意 $x$ 上的棋子，移动后都一定会到达 $y$。如果甲能够通过让两个棋子都移动到 $x$ 获胜，那么甲显然也能够通过让两个棋子都移动到 $y$ 获胜。于是我们可以将 $x$ 和 $y$ 合并，具体来说，我们对于每条边 $z \to x$，将其删除，然后若 $z \to y$ 不存在则加入边 $z \to y$。和之前相同，此时可能又会有新的节点出边数量变为 $1$，我们需要将它们继续合并。

合并后，新图中的所有点都有至少 $2$ 条出边，或有一个自环。先考虑所有点都至少有 $2$ 条出边的情况，显然乙的每次操作都能够避免使两个棋子进入同一个节点。而有自环的情况同样平凡。

于是，对于询问 $(x,y)$，我们可以按照如下方式判定胜负：

若 $x$ 或 $y$ 被删除，那么甲必胜。否则，如果 $x$ 和 $y$ 被合并成了一个节点，那么甲必胜，否则乙必胜。

使用启发式合并 ```set``` 维护每个节点的出边集合 $f$ 和入边集合 $g$，并查集维护合并后每个点所在的集合，时间复杂度 $\mathcal{O}(m \log n + q)$。 

```cpp
#include <bits/stdc++.h>
#define ins insert
#define era erase
using namespace std;
const int N = 2e5 + 5;
int n, m, k, fa[N];
set <int> f[N], g[N]; // f : out, g : in
queue <int> q;
int gf(int x) {
    return x == fa[x] ? x : fa[x] = gf(fa[x]);
}
int main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) 
        fa[i] = i;
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        f[x].ins(y);
        g[y].ins(x);
    }
    for (int i = 1; i <= n; i++)
        if (f[i].size() == 0) q.push(i);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        fa[v] = 0;
        for (auto u : g[v]) {
            f[u].era(v);
            if (f[u].size() == 0) q.push(u);
        }
    }
    for (int i = 1; i <= n; i++)
        if (f[i].size() == 1) q.push(i);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        int y = 0;
        for (auto v : f[x]) y = v;
        x = gf(x);
        y = gf(y);
        if (x == y) continue;
        if (g[x].size() > g[y].size())
            swap(x, y);
        for (auto z : g[x]) {
            f[z].era(x);
            f[z].ins(y);
            g[y].ins(z);
            if (f[z].size() == 1) q.push(z);
        }
        fa[x] = y;
    }
    cin >> k;
    while (k--) {
        int x, y; cin >> x >> y;
        x = gf(x);
        y = gf(y);
        if (x == 0 || y == 0 || x == y) {
            cout << "B";
        } else {
            cout << "H";
        }
    }
    return 0;   
}
```


---

## 作者：cff_0102 (赞：4)

注意到如果有一个棋子在一个没有出边的点，那么 H 可以指示 B 移动这个点，这样 B 无法移动这个点，就输了。我们把这个点“删除”，如果在询问中发现有一个点被“删除”，H 就必胜。

把这些没有出边的点删除后，可能又会出现一些新的点没有出边，这些点也可以跟着删除，因为在原图上 B 无论怎么移动都一定会把它移到一个没有出边的点上。

最终，剩下的图上每个点都至少有一条出边。

注意到如果有一个点只有一条出边，那么它可以和它指向的点直接合并，因为如果在这里有一个棋子，想要移动也只能移动到那一个点。

把这些只有一个出边的点与其它点合并后，可能又会出现一些新的点只有一条出边（比如有一个点连出的两条边指向的点合并了），这些点也可以跟着合并。

最终，剩下的图上每个点都至少有两条出边。

考虑处理询问。如果输入的两个点（在最终的图上）有一个被删除，那么 H 必胜；如果这两个点在同一个位置，说明它们合并了，也就是有一个棋子可以挡住另一个棋子的去路，因此 H 也可以通过指示 B 移动被挡住的那个棋子来获胜。如果这两个点都存在且不相同，由于 B 在原图上的操作在新图上无非原地踏步或向前移动一步，而在新图上每个点都有至少两条出边，因此移动的那个点一定可以找到一条路径，它指向的点没有被另一个棋子挡住。B 选择往那里移动即可。所以此时，B 有必胜策略。

可以使用并查集和 set（用来存储每个点入边和出边的信息）进行上面所说的两个操作。如果一个点被删除，就将其合并到 $0$ 号点；如果两个点要合并，正常使用并查集合并即可。不要忘记修改那些指向了这些点的边。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int fa[N];
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
set<int>in[N],out[N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,m;cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;cin>>u>>v;
		in[v].insert(u);
		out[u].insert(v);
	}
	queue<int>q;
	for(int i=1;i<=n;i++){
		fa[i]=i;
		if(out[i].empty())q.push(i);
	}
	while(!q.empty()){
		int x=q.front();q.pop();fa[x]=0;
		for(int y:in[x]){
			out[y].erase(x);
			if(out[y].empty())q.push(y);
		}
	}
	for(int i=1;i<=n;i++){
		if(out[i].size()==1)q.push(i);
	}
	while(!q.empty()){
		int x=q.front();q.pop();
		int y=*out[x].begin();
		x=find(x);y=find(y);
		if(x!=y){
			if(in[x].size()>in[y].size())swap(x,y);
			fa[x]=y;
			for(int z:in[x]){
				out[z].erase(x);
				out[z].insert(y);
				in[y].insert(z);
				if(out[z].size()==1)q.push(z);
			}
		}
	}
	int qq;cin>>qq;
	while(qq--){
		int x,y;cin>>x>>y;
		x=find(x);y=find(y);
		if(x==0||y==0||x==y)cout<<"B";
		else cout<<"H";
	}
	return 0;
}
```

---

## 作者：strcmp (赞：3)

好题。

把脑叫做 A，蹄叫做 B。

别被强连通分量算法带偏了，你发现在同一个强连通分量内的情况基本不可能简单处理。

怎么做？

发现 $0$ 出度点可以直接删，如果有一个点是 $0$ 出度点那 A 直接赢麻了。

过程中生成的 $0$ 度点也要删。

反图拓扑排序即可。

$1$ 出度点也可以直接合并到唯一指向的那个结点上，因为 B 肯定只能走上去。

还是直接反图拓扑。

现在只剩下了 $2$ 以上出度的点。

发现这个时候 B 怎么走都能避免相撞，毕竟出度 $\ge 2$，有一个点被占了那就去另外一个点就好了，B 赢麻了。

剩下情况有没有可能 A 赢呢。如果两个点都在二度点联通块内，肯定 B 赢。好多种情况都是 B 赢，那不妨直接考虑 A 赢的条件。

除了有一个是 $0$ 出度点，A 赢还可以是一种情况。就是两个点都只能在 $1$ 出度点的环上走到死，A 只操作一个点即可。或者两个 $1$ 出度点同时连向一个 $2$ 出度点，此时先让 $x$ （不得不）走到这个 $2$ 出度点，再操控 $y$ （不得不）走到 $2$ 出度点跟 $x$ 撞车。

这一定是充要条件，因为其它任何时候 B 都可以在二度点联通块上走到赢。

于是拓扑排序继续缩 $1$ 度点即可，set 启发式合并做到 $\Theta(m \log^2 n)$，使用 finger search 的平衡树或者线段树合并可以做到 $\Theta(m \log n)$。

```cpp
#include <bits/stdc++.h>
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
constexpr int maxn = 3e5 + 10, mx = 1e5, mod = 1e9 + 7;
set<int> s[maxn], t[maxn]; int n, m, Q, q[maxn], fa[maxn], del[maxn], hd = 1, tl = 0;
int fd(int x) { return fa[x] ? fa[x] = fd(fa[x]) : x; }
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++) scanf("%d%d", &u, &v), s[u].insert(v), t[v].insert(u);
	rep(i, 1, n) if (s[i].empty()) q[++tl] = i;
	while (hd <= tl) {
		int u = q[hd++]; del[u] = 1;
		for (int v : t[u]) {
			s[v].erase(u);
			if (s[v].empty()) q[++tl] = v;
		}
	}
	hd = 1, tl = 0;
	rep(i, 1, n) if (s[i].size() == 1) q[++tl] = i;
	while (hd <= tl) {
		int u = q[hd++], v = *s[u].begin();
		u = fd(u), v = fd(v); if (u == v) continue;
		if (t[u].size() > t[v].size()) swap(u, v);
		fa[u] = v;
		for (int x : t[u]) {
			t[v].insert(x);
			s[x].erase(u), s[x].insert(v);
			if (s[x].size() == 1) q[++tl] = x;
		}
		t[u].clear();
	}
	scanf("%d", &Q);
	while (Q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (del[x] || del[y] || fd(x) == fd(y)) putchar('B');
		else putchar('H');
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：2)

很厉害的题目。

考虑一层层化简问题。

首先所有零度点（下文度均指出度）上假若放了指示物，那么就一定没法移动，所以将其删除，然后会产生新的零度点，也将其删去。

现在图上所有点度数至少为 $1$。

考虑找到一个度数为 $1$ 的点 $x$，假若其唯一的出边指向 $y$ 满足 $x \not = y$，我们发现 $x,y$ 上不可能同时存在指示物，因为那时 $x$ 无法移动，因此发现此时 $x,y$ 实际上处于一个等价的状态，考虑直接删掉边 $x \to y$ 再合并两个点，边集直接 set 启发式合并维护。

现在图上所有点要么度数大于等于 $2$ 要么存在自环，对于两个指示物的初始位置，如果有一个位置被删掉或者两个位置被合并到一个点上都是无法无限移动，否则我们可以证明一定可以无限移动。

证明考虑对于一个放在有自环的位置上的指示物，可以无限走自环，否则由于一个点至少有两个出边，所以另一个指示物最多挡住一个，因此可以无限移动。

总时间复杂度 $O(n \log^2 n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e5+114;
int fa[maxn];
int vis[maxn];
int find(int u){
	return fa[u]=(fa[u]==u?u:find(fa[u]));
}
set<int> In[maxn],Out[maxn];
int n,m;
queue<int> q;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		Out[u].insert(v);
		In[v].insert(u);
	}
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=n;i++){
		if(Out[i].size()==0) q.push(i);
	}
	while(q.size()>0){
		int u=q.front();
		q.pop();
		vis[u]=1;
		for(int v:In[u]){
			Out[v].erase(u);
			if(Out[v].size()==0) q.push(v);
		}
		In[u].clear();
	}
	for(int i=1;i<=n;i++){
		if(vis[i]==0&&Out[i].size()==1) q.push(i);
	}
	while(q.size()>0){
		int u=q.front();
		q.pop();
		u=find(u);
		int v=(*Out[u].begin());
		if(u==v||Out[u].size()!=1) continue;
		Out[u].erase(v);
		In[v].erase(u);
		if((In[v].size()+Out[v].size())>(In[u].size()+Out[u].size())) swap(u,v);
		fa[v]=u;
		bool flag=false;
		for(int x:In[v]){
			if(x==v){
				flag=true;
				continue;
			}
			Out[x].erase(v);
			Out[x].insert(u);
			In[u].insert(x);
			if(Out[x].size()==1) q.push(x);
		}
		for(int x:Out[v]){
			if(x==v){
				flag=true;
				continue;
			}
			In[x].erase(v);
			In[x].insert(u);
			Out[u].insert(x);
		}
		if(flag==true) Out[u].insert(u),In[u].insert(u);
		In[v].clear(),Out[v].clear();
		if(Out[u].size()==1) q.push(u); 
	}
	int Q;
	cin>>Q;
	while(Q--){
		int x,y;
		cin>>x>>y;
		cout<<((find(x)==find(y)||vis[find(x)]==1||vis[find(y)]==1)?'B':'H');
	} 
	return 0;
}
```

---

## 作者：mskqwq (赞：1)

首先对图拓扑，每次入队出度为 $0$ 的点并删去，如果询问的两个点中存在被删去的点就是 $B$ 赢。

接着考虑出度为 $1$ 的点，如果 $B$ 选了它那么 $H$ 只能将它往它所连向的点移动，那么不妨把这两个点看作一个点，将它们合并起来。

然后合并的过程中可能会产生新的出度为 $1$ 的点，比如下面这个情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/at3pspl7.png)

将 $1,2,3,4$ 合并后，$5$ 成为了新的出度为 $1$ 的点，于是要接着将 $5$ 合并。这个过程可以类似拓扑排序的方式完成，每次入队出度为 $1$ 的点，用 set 维护每个点连出去的和连向它的点，合并时启发式合并，复杂度 $O(n \log ^2 n)$。也有线段树合并的单 $\log$ 做法。 

最后判一下两个点是否在一个连通块就行，因为一个连通块内的点一定能走到某个固定的点。

```cpp
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>
#define fi first
#define se second
#define ep emplace
#define MISAKA main
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define rg(x) x.begin(),x.end()
#define mems(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _rep(i,a,b) for(int i=(a);i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char c=getchar();int f=1,x=0;
    for(;c<48||c>57;c=getchar())if(c=='-') f=-1;
    for(;47<c&&c<58;c=getchar()) x=(x<<3)+(x<<1)+(c^48);
    return x*f;
}
const int N=1e5+10,mod=998244353;
int n,m,Q,fa[N];set<int> to[N],in[N];
int find(int x){return fa[x]=x==fa[x]?x:find(fa[x]);}
void misaka(){
    n=read(),m=read();
    rep(i,1,n) fa[i]=i;
    rep(i,1,m){
        int u=read(),v=read();
        to[u].ep(v);in[v].ep(u);
    }
    queue<int> q;
    rep(i,1,n)if(to[i].empty()) q.ep(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int v:in[u]){
            to[v].erase(u);
            if(to[v].empty()) q.ep(v);
        }
    }
    rep(i,1,n)if(to[i].size()==1) q.ep(i);
    while(!q.empty()){
        int u=q.front(),v=*to[u].begin();q.pop();
        if((u=find(u))==(v=find(v))) continue;
        if(in[u].size()>in[v].size()) swap(u,v);
        fa[u]=v;
        for(int x:in[u]){
            in[v].ep(x);
            to[x].erase(u);to[x].ep(v);
            if(to[x].size()==1) q.ep(x);
        }
    }
    Q=read();
    while(Q--){
        int u=read(),v=read();
        if(to[u].empty()||to[v].empty()||find(u)==find(v)) putchar('B');
        else putchar('H');
    }
}
bool __ed;
signed MISAKA(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB",abs(&__st-&__ed)/1024./1024);});
    #endif
    int T=1;
    while(T--) misaka();
    return 0;
}

```

---

## 作者：Stdinout (赞：0)

# Hoof and Brain P 题解
[Link](https://www.luogu.com.cn/problem/P8276)

模拟考考场上没干出来，赛后几分钟过了。

首先考虑一个简单情况，如果一个节点的出度为 $0$，那么这个节点就是 B 的必胜点，我们可以将这个点删掉，重复这样的操作，使得每个节点都有出度。

除了上面这一种情况，B 赢的情况就只有使得两个棋子重叠了。要使两个棋子重叠，就必须使其中一个棋子没有其他路可以走，也就是说这颗棋子一定可以通过一直走出度为 $1$ 的点到达另一个棋子。

考虑启发式合并。对于出度为 $1$ 的节点，我们可以将这个节点和他指向的节点合并，并继承其所有的入度。

最后统计答案时，如果节点不存在，B 赢；如果两个节点在同一个节点，B 赢；否则 H 赢。

代码： 
```cpp
#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int N = 1e5 + 5;
set<int> g[N], re[N];
int n, m, q;
int fa[N], siz[N];
queue<int> que;
queue<int> quw;
int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (re[x].size() > re[y].size()) swap(x, y);
    for (int u : re[x]) { // 继承入度
        re[y].insert(u);
        g[u].erase(x);
        g[u].insert(y);
        if (g[u].size() == 1) quw.push(u);
    }
    re[x].clear();
    fa[x] = y;
}
int main() {
    FASTIO;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) fa[i] = i; 
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        g[u].insert(v);
        re[v].insert(u);
    }
    for (int i = 1; i <= n; ++i) {
        if (g[i].empty()) {
            que.push(i);
        }
    }
    while (que.size()) { // 删点
        int f = que.front();
        fa[f] = 0;
        que.pop();
        for (int v : re[f]) {
            g[v].erase(f);
            if (g[v].empty())
                que.push(v);
        }
        re[f].clear();
    }
    for (int i = 1; i <= n; ++i) {
        if (g[i].size() == 1) 
        	quw.push(i);
    }
    while (quw.size()) { // 合并
    	int f = quw.front();
    	quw.pop();
    	if (g[f].size() == 1) {
    		merge(f, *g[f].begin());	
		}
	}
    cin >> q;
    for (int i = 1; i <= q; ++i) {
        int x, y;
        cin >> x >> y;
        if (!fa[x] || !fa[y]) cout << "B";
        else if (find(x) == find(y)) cout << "B";
        else cout << "H";
    }
    return 0;
}
```

---

