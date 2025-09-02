# [ARC143E] Reversi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc143/tasks/arc143_e

$ N $ 頂点からなる木があります． 各頂点には $ 1 $ から $ N $ までの番号がついており， $ i $ 番目の辺は頂点 $ A_i $ と頂点 $ B_i $ を結んでいます． また，各頂点にはリバーシの石が $ 1 $ つずつ置かれています． 各頂点に置かれている石の状態は文字列 $ S $ によって与えられ， $ S $ の $ i $ 番目の文字が `B` のとき，頂点 $ i $ に置かれている石の表は黒色， $ S $ の $ i $ 番目の文字が `W` のとき，頂点 $ i $ に置かれている石の表は白色です．

以下の操作を $ N $ 回行い，すべての頂点から石を取り除くことが可能かどうか判定してください． また可能ならば，列 $ P_1,P_2,\ldots,P_N $ であって，頂点 $ P_1,P_2,\ldots,P_N $ をこの順に選ぶことが可能なもののうち，辞書順で最小のものを求めてください．

- 表が白色の石が置かれている頂点を $ 1 $ つ選び，その頂点から石を取り除く． そして，その頂点と隣接する頂点に置かれている石をすべて裏返す．
 
リバーシの石について リバーシの石は一方の面が黒色，もう一方の面が白色になっており，裏返すと表の色が入れ替わります． 数列の辞書順とは？ 相異なる数列 $ S $ と数列 $ T $ の大小を判定するアルゴリズムを以下に説明します．

以下では $ S $ の $ i $ 番目の要素を $ S_i $ のように表します．また， $ S $ が $ T $ より辞書順で小さい場合は $ S\ \lt\ T $ ，大きい場合は $ S\ \gt\ T $ と表します．

1. $ S $ と $ T $ のうち長さが短い方の文字列の長さを $ L $ とします．$ i=1,2,\dots,L $ に対して $ S_i $ と $ T_i $ が一致するか調べます．
2. $ S_i\ \neq\ T_i $ である $ i $ が存在する場合，そのような $ i $ のうち最小のものを $ j $ とします．そして，$ S_j $ と $ T_j $ を比較して， $ S_j $ が $ T_j $ より（数として）小さい場合は $ S\ \lt\ T $ ，大きい場合は $ S\ \gt\ T $ と決定して，アルゴリズムを終了します．
3. $ S_i\ \neq\ T_i $ である $ i $ が存在しない場合， $ S $ と $ T $ の長さを比較して，$ S $ が $ T $ より短い場合は $ S\ \lt\ T $ ，長い場合は $ S\ \gt\ T $ と決定して，アルゴリズムを終了します．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- 与えられるグラフは木である．
- $ S $ は `B` と `W` の文字からなる長さ $ N $ の文字列である．

### Sample Explanation 2

この場合，一度も操作を行うことができません．

## 样例 #1

### 输入

```
4
1 2
2 3
3 4
WBWW```

### 输出

```
1 2 4 3```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4
BBBB```

### 输出

```
-1```

# 题解

## 作者：CYZZ (赞：14)

# [Reversi](https://www.luogu.com.cn/problem/AT_arc143_e)
## 思路
考虑发生在叶子节点处的翻转，此时有两种情况：叶子是白的、叶子是黑的。讨论父亲和儿子的删除顺序。

- 叶子是白的，则必定先删叶子。如果先删父亲，叶子就会变为黑色，叶子与其他点不连通，就无法删掉它。
- 叶子是黑的，则必定先删父亲。叶子无法直接删除，只能先借助父亲把叶子变为白色，再删除。

那我们可以从 $1$ 开始 dfs（因为字典序要最小），从下往上模拟删除每个叶子。我们就可以根据父亲和儿子的删除顺序建出一个有向图，在有向图上跑拓扑，拓扑序就是操作序列。

dfs 完我们可以得到根节点的颜色，如果是黑色就是无解。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,tot,a[200005],head1[200005],head[200005],in[200005];
string s;
priority_queue<int>q;
struct Edge
{
    int next,to;
}e1[400005],e[400005];
void add_edge1(int u,int v)
{
    e1[++tot].next=head1[u];
    e1[tot].to=v;
    head1[u]=tot;
}
void add_edge(int u,int v)
{
    e[++tot].next=head[u];
    e[tot].to=v;
    head[u]=tot;
    in[v]++;
}
void dfs(int u,int fa)
{
    for(int i=head1[u];i;i=e1[i].next)
    {
        int v=e1[i].to;
        if(v==fa)
            continue;
        dfs(v,u);
        a[u]^=a[v];
        if(a[v])
            add_edge(v,u);
        else
            add_edge(u,v);
    }
}
void topo()
{
    for(int i=1;i<=n;i++)
    {
        if(!in[i])
            q.push(-i);
    }
    while(!q.empty())
    {
        int u=-q.top();
        q.pop();
        printf("%d ",u);
        for(int i=head[u];i;i=e[i].next)
        {
            int v=e[i].to;
            in[v]--;
            if(!in[v])
                q.push(-v);
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add_edge1(x,y);
        add_edge1(y,x);
    }
    for(int i=1;i<=n;i++)
    {
        char c;
        cin >> c;
        a[i]=c=='W'?1:0;
    }
    tot=0;
    dfs(1,0);
    if(!a[1])
    {
        printf("-1");
        return 0;
    }
    topo();
}
```
希望本篇题解能帮到大家！！！

---

## 作者：EuphoricStar (赞：9)

翻转一个点会把它相邻的点全部翻转，因此先从叶子开始自下而上考虑。不难发现，如果这个叶子是白色，那么它一定比它的父亲先翻转（否则它就翻不了了）；而对于黑色的叶子，它一定比它的父亲后翻转。经过一波操作，我们得到了所有叶子的父亲的颜色。此时就可以把它们当作叶子处理，因为那些还没被删的叶子暂时影响不了它们。

经过模拟我们得到了树根的颜色。显然如果此时树根是黑点就无解，否则就自上而下操作。

这样我们发现父子之间的操作顺序可以确定，并且它们是充要的。建出 DAG 后跑拓扑排序即可求出字典序最小的解。

[code](https://atcoder.jp/contests/arc143/submissions/37237209)

---

## 作者：AbsMatt (赞：7)

### [题目传送器](https://www.luogu.com.cn/problem/AT_arc143_e)

### [更爽的阅读体验](https://www.luogu.com.cn/blog/yaohaoyou/solution-at-arc143-e)

## 题意

翻译讲的很清楚了，这里不做过多的解释了。

## 做法

从每个叶子节点出发，向上进行遍历。设 $fa$ 为 $u$ 的父亲，棋子当前的颜色为 $c_i$（$c_i$ 为 $1$ 代表白，$c_i$ 为 $0$ 代表黑），则能发现当 $c_u$  为白色时一定会先删除 $u$ 再删除 $fa$，反之，先删除 $fa$。即
$$
c_{fa} = \begin{cases} c_u=1 & c_{fa}\\ c_u=0&!c_{fa} \end{cases}
$$

上面的处理可以用一次 dfs 完成，时间复杂度为 $O(n)$。在完成 dfs 后，还要判断根节点的当前颜色是否为白色，若不是，则必定没有可行的操作，输出 $-1$。



知道相邻两个点的删除顺序后我们就可以新建一个有向图，然后建一条由先删的点到后删的点的单向边。建完图后只要跑一边拓扑排序就完成了，但为了输出的字典序最小，拓扑排序中的队列要改成小根堆，以保证小的数在前面。时间复杂度为 $O(n \times \log_2n)$。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n, ans[maxn];
string col;
bool c[maxn];
namespace Graph
{
    // Old
    int cnt = 0, head[maxn << 1];
    struct edge
    {
        int nxt, to;
    } e[maxn << 1], New[maxn << 1];
    void add(int u, int v)
    {
        e[++cnt] = {head[u], v};
        head[u] = cnt;
    }

    // New 新建的图
    int in[maxn];
    int cnt1 = 0, he[maxn << 1];
    void make(int u, int v)
    {
        New[++cnt1] = {he[u], v};
        he[u] = cnt1;
        in[v]++;
        // printf("%d -> %d\n", u, v);
    }
} // namespace Graph
using namespace Graph;

namespace Dfs
{

    void dfs(int u, int fa)  // dfs
    {
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int t = e[i].to;
            if (t == fa)
                continue;
            dfs(t, u);
            if (!c[t]) // 先 father 后 son
                make(u, t);
            else // 先 son 后 father
            {
                make(t, u);
                c[u] = !c[u];  // 记得更改 c 数组
            }
        }
        // printf("u=%d c[u]=%d\n", u, c[u]);
    }
} // namespace Dfs
using namespace Dfs;

namespace Topu
{
    priority_queue<int, vector<int>, greater<int>> q;  // 建立小根堆
    bool vis[maxn];
    int dep[maxn];
    void topu()  // 拓扑排序
    {
        for (int i = 1; i <= n; i++)
        {
            if (!in[i])
            {
                q.push(i);
                vis[i] = 1;
            }
        }
        while (!q.empty())
        {
            int u = q.top();
            q.pop();
            printf("%d ", u);
            for (int i = he[u]; i; i = New[i].nxt)
            {
                int t = New[i].to;
                in[t]--;
                if (!vis[t] && !in[t])
                {
                    vis[t] = 1;
                    q.push(t);
                }
            }
        }
    }
} // namespace Topu
using namespace Topu;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    cin >> col;
    for (int i = 1; i <= n; i++)
    {
        c[i] = bool(col[i - 1] == 'W'); // W:1 B:0
    }
    dfs(1, 0);
    if (!c[1])  // 特判：若 c[1] 为黑色输出 -1
    {
        printf("-1");
        return 0;
    }
    topu();
    return 0;  // 完成！！！
}
// orz zlt ！！！


```

---

## 作者：UniGravity (赞：0)

有点厉害的题。想了好久，最后看了官方题解的第一句话的 leaf 然后就会了/kel

这个问题一开始看不太好做，因为会涉及到相邻的多个节点。  
于是考虑叶子 $x$ 的情况，因为只与一个点相邻（记为 $y$）。分类讨论一下：

* $x$ 为黑色，我们发现只有当 $y$ 先取走后才能轮到 $x$，且此时 $x$ 的操作与其它点无关，直接取走就行。我们连一条 $y$ 到 $x$ 的边表示 $y$ 要在 $x$ 之前操作。发现只有这个限制就足够了。
* $x$ 为白色，假如先对 $y$ 操作则此时 $x$ 变为黑色且无法操作。因此 $x$ 必须在 $y$ 前，连边 $x\to y$。

当所有的叶子都连完后，我们发现此时这些叶子对剩下的点就没有影响了，将其删去后又多出了一些新的叶子，继续操作即可。

注意剩下 $2$ 个点时边的连向可能不确定，需要两边分别连一次判断是否合法。

接下来就变成给一个定向后的图，由于我们定向时没有依赖其它的条件，因此如果存在答案则任意的拓扑序都满足条件。使用优先队列贪心即可。

[submission](https://atcoder.jp/contests/arc143/submissions/62945427)

---

## 作者：BreakPlus (赞：0)

+ 本来以为我的做法挺好。结果发现纯纯小丑。

----

+ 先考虑找到一棵树存在合法方案的判定。这样我们可以贪心删除最小的能删除的（具体判断是否能删除则需剩余每个连通块都满足判定）。

+ **结论：``W`` 的数量为奇数时，树存在合法方案。（下文可以略过不读）**

+ 发现 $n=2$ 时，两个 ``W`` 和两个 ``B`` 都是不行的。为了推进后面的思路，我们顺便提一下 $n=1$ 时 ``B`` 是不行的。

+ $n=3$ 时，树必然是一条链，发现 ``WBW`` 和 ``WWB`` 都不行。因为不管动哪一个 ``W``，分离出的连通块都会变成 $n=2$ 或 $n=1$ 的一种情况。

+ 隐约发现有点归纳的影子。假设已经有了一颗大小为 $k$ 的树不符合条件，对它加一个点，是否能搞出一个新的不符合条件的大小为 $k+1$ 的树？

+ 如果加一个点 ``W``，这个点若被操作，则其连向的点会翻转。我们希望能形成归纳，即这个点被操作后，整棵树会形成 $n=k$ 的不合法情形。那么找一个原树上的 ``W``，把它改成 ``B``，再给他连一个新的 ``W``。

+ 发现若新加入点所连接的原树点先被操作，那么新加入点就必死了。所以肯定是新加入点先被操作，这样归约到了 $n=k$。

+ 同理，加入点 ``B`` 的情形类似，读者可以自行考虑。

+ 发现每次加入点，``W`` 的总数的奇偶性不变。**归纳，结论得证。**

----

+ 问题得到了转化。每次都是取一个 ``W``，删除它后，分离出的每个连通块 ``W`` 的数量都是偶数。然后每个连通块都有一个点被翻转了，于是都变成了，还能够继续操作。

+ 如果我们可以保证每时每刻所有连通块 ``W`` 的数量都是奇数，那么判定可以松一点：

+ 把树看成有根树，下一个选择的点只需满足每个儿子的子树内 ``W`` 的数量都是偶数。分离后其父亲所在的连通块受到总量约束必然也是偶数。

+ 现在着眼于**有根树**。维护每个点 $u$ 对应子树内部的 ``W`` 的奇偶性 $p_u$。发现每次删一个点，只有其所有儿子 $v$ 的 $p_v$ 改变。

+ 维护每个时刻有哪些点满足 $p_x = 1$ 且 $\forall y \in son_x ,p_y = 0$ 就做完了。

```cpp
vector<ll>ans; set<ll>S;
ll n,p[200005],del[200005],ff[200005],tot[200005]; vector<ll>E[200005];
char s[200005];
bool check(ll nd){
    if(del[nd] || !p[nd]) {return 0;}
    for(auto y: E[nd]){
        if(!del[y] && p[y]) {return 0;}
    }
    return 1;
}
void dfs(ll x,ll fa){
    ff[x] = fa;
    if(fa) E[x].erase(find(E[x].begin(), E[x].end(), fa));
    for(auto y: E[x]){
        dfs(y, x);
        p[x] ^= p[y];
        tot[x] += p[y];
    }
}
void ADD(ll x){ if(S.find(x) == S.end()) S.insert(x); }
void DEL(ll x){ if(S.find(x) != S.end()) S.erase(x); }
void solve(){
    n=read();
    for(ll i=1;i<n;i++){
        ll u=read(), v=read();
        E[u].pb(v); E[v].pb(u);
    }
    scanf("%s", s+1);
    for(ll i=1;i<=n;i++)
        if(s[i]=='W') p[i]=1; 
    dfs(1, 0);
    if(!p[1]) { puts("-1"); return; }
    for(ll i=1;i<=n;i++)
        if(check(i)) S.insert(i);
    for(ll i=1;i<=n;i++){
        ll x = *S.begin();
        ans.pb(x); del[x] = 1; if(ff[x]) tot[ff[x]]--; DEL(x);
        for(auto y: E[x]){
            p[y] ^= 1;
            if(check(y)) ADD(y); else DEL(y);
        }
        if(ff[x] && p[ff[x]] && !tot[ff[x]]) ADD(ff[x]); else DEL(ff[x]);
    }
    for(auto v: ans) printf("%lld ", v); puts("");
}
```

---

## 作者：binbin_200811 (赞：0)

# [ARC143E Reversi](https://www.luogu.com.cn/problem/AT_arc143_e)

简单的分析题。

### 思路

如果分析一个节点状态，那么时不方便的。但可以注意到，状态的改变好相连的边数有关。

从叶子节点开始考虑。

* 白色：在父亲翻转前选中，并改变父亲状态。
* 黑色：在父亲翻转后选中。

这里可以用拓扑排序建边描述这个问题。

我们把叶子节点解决后，在按照一样的方法，逐层向上解决问题。

最后如果根节点变成黑色，那么无解，否则拓扑排序输出答案（可以开小根堆优先队列，先访问小点）。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=2e5+5;

struct Edge
{
    int tot;
    int head[maxn];
    struct edgenode{int to,nxt;}edge[maxn*2];
    void add(int x,int y)
    {
        tot++;
        edge[tot].to=y;
        edge[tot].nxt=head[x];
        head[x]=tot;
    }
}E,G;

int n;
int ind[maxn];

bool vis[maxn];

void dfs(int u,int f)
{
    for(int i=E.head[u];i;i=E.edge[i].nxt)
    {
        int v=E.edge[i].to;
        if(v==f) continue;
        dfs(v,u);
    }
    if(u==1&&vis[u]){printf("-1");exit(0);}
    else if(u==1) return ;
    if(vis[u]) G.add(f,u),ind[u]++;
    else G.add(u,f),ind[f]++,vis[f]^=1;
}
int cnt;
int ans[maxn];
priority_queue<int,vector<int>,greater<int>>que;
void topu()
{
    for(int i=1;i<=n;i++) if(ind[i]==0) que.push(i);
    while(!que.empty())
    {
        int u=que.top();
        que.pop();
        ans[++cnt]=u;
        for(int i=G.head[u];i;i=G.edge[i].nxt)
        {
            int v=G.edge[i].to;
            if(!(--ind[v])) que.push(v);
        }
    }
    for(int i=1;i<=cnt;i++) printf("%d ",ans[i]);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        E.add(u,v);
        E.add(v,u);
    }
    for(int i=1;i<=n;i++)
    {
        char op;
        cin>>op;
        vis[i]=(op=='B');
    }
    dfs(1,0);
    topu();
}
```



---

## 作者：Yuzimy (赞：0)

又是一道好题。~~图论建模都是好题~~

好吧先说一下这道题要用到拓扑排序，其中：“取走所有棋子的字典序最小的序列”就提示了我们需要用到。

既然是染色，而且会改变相邻节点的状态，那我们不妨从叶节点（即最简单状态）考虑起。

当叶节点 $u$ 本身就为 ```W``` 时，对于它的父节点 $fa$，取得顺序是 $u->fa$。同时注意，由于先取 $u$，会改变 $fa$ 的颜色，所以需要同时更改 $fa$ 的值。

当叶节点 $u$ 为 ```B``` 时，对于它的父节点 $fa$，取得顺序是 $fa->u$。

若一个非叶子节点的儿子全部被考虑完，由于不同子树相互独立（互不影响结果），那么这个节点可以等价于一个叶节点重新做。

注意到根节点 $rt$ 的时候，若颜色为 ```B```，说明无解，则需返回 $-1$。

一遍 DFS 下来，我们得到了 $n-1$ 组两个节点的先后遍历顺序。现在需要求 $n$ 个节点的字典序最小的遍历顺序。先不考虑“最小”，我们发现可以通过前面的 $n-1$ 组遍历顺序构建出一张有向无环图（易证，有向边若无视方向则为树边，不可能有环）。拓扑排序求出顺序即可。由于要“字典序最小”，所以把队列换成优先队列。程序瓶颈在于拓扑排序，为 $\Theta(n\log n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5;
int n,f[N+5];
char s[N+5];
vector<int>E[N+5],E2[N+5];
int deg[N+5];
void dfs(int u,int fa){
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i];
		if(v==fa){
			continue;
		}
		dfs(v,u);
		if(!f[v]){//该节点为B
			if(u){//构建u->v的顺序
				E2[u].push_back(v);
				deg[v]++;
			}
		}else{
			if(u){//构建v->u的顺序
				E2[v].push_back(u);
				deg[u]++;
			}
			f[u]=1-f[u];//记得改变u的颜色
		}
	}
	if(!fa&&!f[u]){//根节点特判
		printf("-1\n");
		exit(0);
	}
}
void topo(){
	priority_queue<int>q;//优先队列
	//以下为拓扑排序模板，故不做更多的解释
	for(int i=1;i<=n;i++){
		if(!deg[i]){
			q.push(-i);//懒得写成小根堆了，就用-号特殊处理
		}
	}
	while(!q.empty()){
		int u=-q.top();
		printf("%d ",u);
		q.pop();
		for(int i=0;i<E[u].size();i++){
			int v=E[u][i];
			deg[v]--;
			if(!deg[v]){
				q.push(-v);
			}
		}
	}
	printf("\n");
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		E[u].push_back(v);
		E[v].push_back(u);
	}
	scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		f[i]=s[i]=='W';//W用1表示，B用0表示
	}
	dfs(1,0);//DFS遍历
	topo();//拓扑排序
	return 0;
}
```


---

