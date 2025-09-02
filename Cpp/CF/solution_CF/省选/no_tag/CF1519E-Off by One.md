# Off by One

## 题目描述

There are $ n $ points on an infinite plane. The $ i $ -th point has coordinates $ (x_i, y_i) $ such that $ x_i > 0 $ and $ y_i > 0 $ . The coordinates are not necessarily integer.

In one move you perform the following operations:

- choose two points $ a $ and $ b $ ( $ a \neq b $ );
- move point $ a $ from $ (x_a, y_a) $ to either $ (x_a + 1, y_a) $ or $ (x_a, y_a + 1) $ ;
- move point $ b $ from $ (x_b, y_b) $ to either $ (x_b + 1, y_b) $ or $ (x_b, y_b + 1) $ ;
- remove points $ a $ and $ b $ .

However, the move can only be performed if there exists a line that passes through the new coordinates of $ a $ , new coordinates of $ b $ and $ (0, 0) $ .

Otherwise, the move can't be performed and the points stay at their original coordinates $ (x_a, y_a) $ and $ (x_b, y_b) $ , respectively.

The numeration of points does not change after some points are removed. Once the points are removed, they can't be chosen in any later moves. Note that you have to move both points during the move, you can't leave them at their original coordinates.

What is the maximum number of moves you can perform? What are these moves?

If there are multiple answers, you can print any of them.

## 说明/提示

Here are the points and the moves for the ones that get chosen for the moves from the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1519E/552d757ed4044221f43bfc2dbbc4063ed579283e.png)

## 样例 #1

### 输入

```
7
4 1 5 1
1 1 1 1
3 3 3 3
1 1 4 1
6 1 1 1
5 1 4 1
6 1 1 1```

### 输出

```
3
1 6
2 4
5 7```

## 样例 #2

### 输入

```
4
2 1 1 1
1 1 2 1
2 1 1 2
1 2 1 2```

### 输出

```
1
1 2```

## 样例 #3

### 输入

```
4
182 168 60 96
78 72 45 72
69 21 144 63
148 12 105 6```

### 输出

```
1
2 4```

# 题解

## 作者：walk_alone (赞：6)

~~（我是不会告诉你我官方题解看不懂洛谷题解又看了三个多小时才会写的）~~

顺着CF的官方题解的思路来分析这个题。

首先第一，怎么样算共线。显然我们只用刻画它们的$\tan$值即可。由于是在第一象限，我们甚至不用算出它的值，只用刻画它的底和高就行，这里可以定义一个分数类来实现。

其次就是拆点。在这里我们把每一个点往上往右平移得到的两个新点用一条边连接了起来。**可以这么认为，我们用一条边来表示原图中的一个点**。为了方便之后匹配的实现，我们需要给构建的图（下称形式图）的每一条边都记录回去它在原图（坐标图）上的点的编号。

那么经过这样的处理之后，我们的问题就转化为了——在一个无向图上，找到尽可能多的组边数，使得每组边由两条有公共顶点的边组成，且每一条边仅在一个组中。这对应于实际问题中的点平移：形式图中的一个点代表一个正切值，形式图中一组边有公共点意味着这两条边分别对应于坐标图中的两个点朝着它们对应的方向移动之后可以使得它们的正切值相同。因而记**形式图上这样的公共点为枢轴点**，它们是一个公共的正切值。

然后问题就转化到了形式图中。（cross edge这里我又卡了半天）CF题解中那个结论是：对于一个无向图，使用dfs遍历同时给图中节点打上深度标记后，除去dfs走过的边，剩下的边连接的两个顶点它们的深度一定不相同。显然，如果存在某条边两端深度相同，那么在dfs遍历到其中一段时，一定会走这条边遍历到另一端。因而，这样没有被dfs遍历的边称为**返祖边**。

剩下的部分别人讲的都很清楚了。在dfs树上，如果一个节点下辖的边（包括直连儿子的边和它的后代返祖到它的边）为奇数，也就是有一条边没办法匹配，就把它和它父亲的边扯过来和它下面匹配，即，**它和它父亲相连的边的枢轴元素是它自己**。若为偶数则这条边枢轴元素归父亲，因为它自己的子树都能相互匹配。至于返祖边那就直接给祖宗就好。这里就是一个贪心。

~~（我是不会告诉你就这么点东西我生生看别人的代码看了几个小时才看明白的）~~

下面附上有详细注释的代码。

```cpp
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
long long gcd(long long x,long long y)
{
    return y == 0 ? x : gcd(y, x % y);
}
struct frac
{
    long long p;
    long long q;  
    bool operator <(const frac &b)const
    {
        return (long double)p / q < (long double)b.p / b.q;//这里精度问题堪忧，直接乘会炸long long，用double不够。当然也可以选择用别的方法判断大小或者直接用unordered_map
    }
};
frac norm(frac a)//约分
{
    long long gcd_num = gcd(a.p, a.q);
    return (frac){a.p / gcd_num, a.q / gcd_num};
}
map<frac, int> id;
struct line
{
    int from;
    int to;
    int id;
    int next;
};
struct line que[2000005];
int cnt, headers[500005], tot;
void add(int from,int to,int id)
{
    cnt++;
    que[cnt].from = from;
    que[cnt].to = to;
    que[cnt].id = id;//记录当前这条边是坐标图上哪一个节点产生的这条边
    que[cnt].next = headers[from];
    headers[from] = cnt;
}
vector<int> con[500005];//con记录了枢轴元素所经过的边。即，con[i]内存储着形式图中以i节点为枢轴元素的边。
int depth[500005];
void dfs(int place,int father)
{
    int nownode = -1;//和父亲的直连边。注意，可能有重边，多余的边一律按返祖边处理
    depth[place] = depth[father] + 1;
    for (int i = headers[place]; i;i=que[i].next)
    {
        if(!depth[que[i].to])
            dfs(que[i].to, place);
        else
        {
            if(depth[que[i].to]>depth[place])//深度比它大，一定不是它的返祖边。返祖边需要到着节点深度小于它自己
                continue;
            if(que[i].to==father && nownode==-1)//防止重边造成影响，因而有nownode==-1的判断
                nownode = que[i].id;//nownode为这条直连边对应的点。之后会用到。
            else
                con[que[i].to].push_back(que[i].id);//一条返祖边。该边的枢轴元素直接给祖宗。
        }
    }
    if(father)//如果是根节点，则没有向上的直连边，也就没有这部分了。
    {
        if(con[place].size()&1)//以place为枢轴元素的边不足以配对，因而需要把直连边牵过来配对。
            con[place].push_back(nownode);
        else//反过来，子节点内部都可以匹配，那么这条直连边就给父亲去匹配。
            con[father].push_back(nownode);
    }
    return;
}
int main()
{
    int ans = 0, n;
    frac x, y;
    scanf("%d", &n);
    for (int i = 1; i <= n;i++)
    {
        scanf("%lld%lld%lld%lld", &x.p, &x.q, &y.p, &y.q);
        x = norm(x);
        y = norm(y);
        frac left = (frac){y.p * x.q, (x.p + x.q) * y.q}, up = (frac){(y.p + y.q) * x.q, x.p * y.q};
        if(!id[left])//记录移动后的点在形式图中的编号
            id[left] = ++tot;
        if(!id[up])
            id[up] = ++tot;
        add(id[left], id[up], i);
        add(id[up], id[left], i);
    }
    for (int i = 1; i <= tot; i++)
        if(!depth[i])//注意图不一定联通，因而需要对每一个连通子图都要进行操作。
            dfs(i, 0);
    for (int i = 1; i <= tot; i++)
        ans += con[i].size() / 2;//匹配个数为各枢轴元素下辖线段条数/2
    printf("%d\n", ans);
    for (int i = 1; i <= tot;i++)
        for (int j = 0; j + 1 < con[i].size(); j += 2)
            printf("%d %d\n", con[i][j], con[i][j + 1]);//对于一个枢轴元素，其线段匹配数目是一定的，因而可以随便分配。
    return 0;
}
```


---

## 作者：STrAduts (赞：3)

判断两点是否可以执行移动并删除是很容易的。我们可以先将所有可以直接删除的点对连边，那么答案就转化为无向图的最大边独立集。

然后会发现边是 $n ^ 2$ 级别的，并且这个边独立集也很难做，G。

对于一个点 $(x, y)$，将它与两个表示斜率 $\frac {x + 1} {y},\frac {x} {y + 1}$ 的点相连。则原问题转化为求一个最大匹配，定义匹配形如 `Node1 - Slope` 与 `Slope - Node2` 的两边，注意 `Slope` 是可以共用的。

感觉能做啊。来整个 DFS 森林，易知叶子节点一定是 `Slope` 节点，而根也为 `Slope` 节点。

我们强制让深度小的连向深度大的，使其全部改造为有向边。则对于 `Slope` 点 $u$：

让他所有连向儿子的边依次相邻匹配，如果一个不剩就回溯；如果剩一个就和父亲连向自己的边匹配。注意 `Node` 顶点不能重复匹配，所以匹配了的边的 `Node` 顶点要打上标记。

最后每棵树的根没父亲帮忙收尾，但可见这样每棵树最多只会损失一条边，也就是说我们的答案可以取 $\sum\lfloor \frac {m} {2} \rfloor$，这一定是最大的！漂亮。

```cpp
#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
int Abs (int x) { return x < 0 ? -x : x; }
int Max (int x, int y) { return x > y ? x : y; }
int Min (int x, int y) { return x < y ? x : y; }

int Read () {
    int x = 0, k = 1;
    char s = getchar ();
    while (s < '0' || s > '9') {
        if (s == '-')
            k = -1;
        s = getchar ();
    }
    while ('0' <= s && s <= '9') 
        x = (x << 3) + (x << 1) + (s ^ 48), s = getchar ();
    return x * k;
}

void Write (int x) {
    if (x < 0)
        putchar ('-'), x = -x;
    if (x > 9)
        Write (x / 10);
    putchar (x % 10 + '0');
}

void Print (int x, char s) { Write (x), putchar (s); }

const int Maxn = 2e5 + 5;

vector <int> Graph[Maxn * 3];
map <pair <LL, LL>, int> Pos;
vector <pair <int, int> > Res;
bool Vis[Maxn * 3], Used[Maxn];
int n, Deg[Maxn * 3], Dep[Maxn * 3];

LL Gcd (LL a, LL b) { return !b ? a : Gcd (b, a % b); }

void Add_Edge (int u, int v) { Graph[u].push_back (v), Graph[v].push_back (u), Deg[u]++, Deg[v]++; }

void Dfs (int u, int Last, int Fa) {
    Vis[u] = true;
    for (int i = 0, v; i < Graph[u].size (); i++) {
        v = Graph[u][i];
        if (!Vis[v]) 
            Deg[v] = Deg[u] + 1, Dfs (v, u > n ? u : Last, u);
    }
    if (u > n) {
        int x = 0, y = 0;
        for (int i = 0; i < Graph[u].size (); i++) 
            if (Deg[Graph[u][i]] > Deg[u] && !Used[Graph[u][i]]) {
                if (!x)
                    x = Graph[u][i];
                else {
                    y = Graph[u][i];
                    Used[x] = true, Used[y] = true;
                    Res.push_back (make_pair (x, y));
                    x = y = 0;
                }
            }
        if (x && !y && Fa) {
            y = Fa;
            Used[x] = true, Used[y] = true;
            Res.push_back (make_pair (x, y));
            x = y = 0;
        }
    }
}

int main () {
    n = Read ();
    int Cnt = n;
    for (int i = 1; i <= n; i++) {
        LL a = Read (), b = Read (), c = Read (), d = Read ();
        LL t = Gcd ((a + b) * d, (b * c));
        if (!Pos[make_pair ((a + b) * d / t, b * c / t)])
            Pos[make_pair ((a + b) * d / t, b * c / t)] = ++Cnt;
        Add_Edge (i, Pos[make_pair ((a + b) * d / t, b * c / t)]);

        t = Gcd ((a * d), (c + d) * b);
        if (!Pos[make_pair (a * d / t, (c + d) * b / t)])
            Pos[make_pair (a * d / t, (c + d) * b / t)] = ++Cnt;
        Add_Edge (i, Pos[make_pair (a * d / t, (c + d) * b / t)]);
    }
    for (int i = n + 1; i <= Cnt; i++)
        if (!Vis[i])
            Deg[i] = 1, Dfs (i, 0, 0);
    Print (Res.size (), '\n');
    for (int i = 0; i < Res.size (); i++)
        Print (Res[i].first, ' '), Print (Res[i].second, '\n');
    return 0;
}

// (a + b) * d / b * c
// a * d / (c + d) * b
```

---

## 作者：Mihari (赞：2)

# 壹、题目描述 &para;

[传送门 to CF](http://codeforces.com/contest/1519/problem/E)

# 贰、题解 &para;

对于一些点 $(x_i,y_i)$，如果它们的斜率相同，即说明 $({x_i\over k},{y_i\over k})$ 也是相同的（其中 $k\overset{\Delta}=\gcd(x_i,y_i)$）我们可以考虑将一个点 $(x,y)$ 能够到达的两个点连起来，这条边的编号为这个点的编号，即我们将相同的斜率当成点，而将原来的点当成边，那么我们的问题就转化为了：

>给一个无向图（或许有很多连通块），**一个匹配为一对共用至少一个顶点的边**，现在你要找出这个图的最大匹配数量。

贪心地想，对于一个有 $m$ 条边的无向图，我们期望地匹配数量应该是 $\lfloor{m\over 2}\rfloor$，并且一定能够达到。

>简要证明一下：对于这张图，遍历出一个 $\tt dfs$ 树，对于每一条边（不论是树边还是非树边），强制将其看作为从深度小的连向深度大的（即往下走），那么，对于一个度数为 $d$ 的点，，我们分情况讨论：
>
>- 若 $d=2k$，那么它自己内部就可以搞定；
>- 若 $d=2k+1$，那么它自己内部搞定之后，让它剩下的边和它父亲的一条边再构成一个匹配~~让你父亲给你收尾？~~；
>  比较特别的是 <ruby>树<rt>gu</rt></ruby> <ruby>根<rp>(</rp><rt>er</rt><rp>)</rp></ruby>，因为它没有父亲，所以它如果剩下一条边，就没人给他收尾了。

在代码实现时，定义 $\tt match[i]$ 表示 $i$ 点尚未被匹配的边的编号是多少，特别的，若为 $0$ 即没有剩余的边。

对于 $({x_i\over k},{y_i\over k})$ 的离散，有更好的做法，考虑 $({a\over b},{c\over d})$ 的斜率实际上和 $(ad,cb)$ 是一样的，那么，对于 $({a\over b}+1,{c\over d})$ 或者 $({a\over b},{c\over d}+1)$ 也是一样，只需要同时乘上 $bd$ 就行了。

时间复杂度 $\mathcal O(n\log n)$，瓶颈在 $\tt hash$.

# 叁、参考代码 &para;

```cpp
#include<cstdio>
#include<vector>
#include<map>
#include<cstring>
#include<algorithm>
using namespace std;

#define Endl putchar('\n')
#define mp(a, b) make_pair(a, b)
#define rep(i, l, r) for(int i=(l), i##_end_=(r); i<=i##_end_; ++i)
#define fep(i, l, r) for(int i=(l), i##_end_=(r); i>=i##_end_; --i)
#define fi first
#define se second
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
template<class T>inline T fab(T x){ return x<0? -x: x; }
template<class T>T gcd(T x, T y){ return y? gcd(y, x%y): x; }
template<class T>inline T readin(T x){
	x=0; int f=0; char c;
	while((c=getchar())<'0' || '9'<c) if(c=='-') f=1;
	for(x=(c^48); '0'<=(c=getchar()) && c<='9'; x=(x<<1)+(x<<3)+(c^48));
	return f? -x: x;
}

const int maxn=200000<<1;

struct edge{
    int to, nxt, id;
    edge(){}
    edge(int T, int N, int I): to(T), nxt(N), id(I){}
}e[maxn<<1|1];
int tail[maxn+5], ecnt;
inline void add_edge(int u, int v, int id){
    // printf("add_edge :> u == %d, v == %d, id == %d\n", u, v, id);
    e[ecnt]=edge(v, tail[u], id); tail[u]=ecnt++;
    e[ecnt]=edge(u, tail[v], id); tail[v]=ecnt++;
}

int n;
map<pll, int>htable;
int ncnt;
inline int getid(ll x, ll y){
    ll d=gcd(x, y);
    pll cur=mp(x/d, y/d);
    if(!htable[cur]) htable[cur]=++ncnt;
    return htable[cur];
}

inline void input(){
    memset(tail, -1, sizeof tail);
    n=readin(1);
    int a, b, c, d, u, v;
    rep(i, 1, n){
        a=readin(1), b=readin(1), c=readin(1), d=readin(1);
        u=getid(1ll*(a+b)*d, 1ll*c*b);
        v=getid(1ll*a*d, 1ll*(c+d)*b);
        add_edge(u, v, i);
    }
}

vector<pii>ans;

int vis[maxn+5], match[maxn+5];
void dfs(int u){
    vis[u]=1;
    for(int i=tail[u], v, nde; ~i; i=e[i].nxt){
        v=e[i].to, nde=e[i].id;
        e[i].to=e[i^1].to=0;
        if(v){
            if(!vis[v]) dfs(v);
            if(match[v]){
                ans.push_back(mp(nde, match[v]));
                match[v]=0;
            }
            else if(match[u]){
                ans.push_back(mp(nde, match[u]));
                match[u]=0;
            }
            else match[u]=nde;
        }
    }
}

signed main(){
    input();
    rep(i, 1, ncnt) if(!vis[i])
        dfs(i);
    printf("%d\n", (int)ans.size());
    for(int i=0, siz=ans.size(); i<siz; ++i)
        printf("%d %d\n", ans[i].fi, ans[i].se);
	return 0;
}
```

# 肆、用到 の Trick

这是 “最大边匹配”，可以使用这种贪心思路来构造。

另外，有个思想：有些子节点欠下的债，可以留到父节点来还。但并不是所有的债都可以子债父还罢？

---

## 作者：丛雨 (赞：2)

## CF1519E

> 题意:平面上有$n$个点,每个点坐标为一个非负分数。每个点**必须**选择向上或向右移动一个单位(y+1或x+1)。对于移动后的点，每次可以选择与(0,0)三点共线的点对(重合也算)，将该点对的点除去。问在最优方案下最多能除去多少对点（每个点只能被除去一次）

首先我们可以知道，若是$A$,$B$,$(0,0)$三点共线，则说明$\frac{\overrightarrow A}{|\overrightarrow  A|}=\frac{\overrightarrow B}{|\overrightarrow  B|}$

所以我们不难转换题意：我们令点$i$向上移动后形成的向量所成的单位向量为$\alpha_i$,向右移动所成的单位向量为$\beta_i$.则我们在$\alpha_i$与$\beta_i$之间连一条边，令图$G=(\{\alpha_i|i\in[1,n]\cap N^+\}\cup \{\beta_i|i\in[1,n]\cap N^+\},\{(\alpha_i,\beta_i)|i\in[1,n]\cap N^+\})$

，则要求将每条边分配给端点中的一个，设每个端点$i$分配得的边数为$v_i$,则答案$Ans=f(G)=\sum_{i\in V}\lfloor\frac{v_i}{2}\rfloor$

题意转换后则变成了一个经典问题

首先我们不难得到对于原图的任意极大联通导出子图$G'$,边集$V'$,$f(G')\leq \lfloor \frac{|V'|}{2}\rfloor$

然后我们的任务就变成了构造一种满足条件的方案

首先对于每个联通块，我们进行$dfs$遍历，这里有个结论，原图除去$dfs$树边形成的生成子图上不存在$\tt cross\space edge$,即剩余的边一定为返祖边

所以我们就有了最优策略，当$dfs$到点$n$时，若当前$n$已经有的边为奇数，则将父边给自己，否则给父亲，返祖边则全部给祖先 ~~（带孝子）~~

可以证明，这样至多在总边数为奇数时在$dfs$树根处浪费一条边

```cpp
#include<bits/stdc++.h>
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;
	char k;
	bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
int s,tot,h[500005];
ll Gcd(ll x,ll y){while(y)swap(x%=y,y);return x;}
vector<int>G[500005],V[500005];
map<pair<ll,ll>,int>ma;
pair<ll,ll> mul(ll x,ll y,ll z,ll w){
	x*=w;y*=z;swap(x,y);z=Gcd(x,y);
	return make_pair(x/z,y/z);
}
vector<int>ans[500005];
void dfs(int n,int fa){
	h[n]=h[fa]+1;vector<int>tem;
	int lau=-1;
	for(int i=0;i<G[n].size();++i)
		if(h[G[n][i]]){
			if(h[G[n][i]]>h[n])continue;
			if(G[n][i]==fa&&!~lau)lau=i;
			else tem.push_back(i);
		}else dfs(G[n][i],n);
	if(fa)if(ans[n].size()&1)ans[n].push_back(V[n][lau]);
		else ans[fa].push_back(V[n][lau]);
	for(int i=0;i<tem.size();++i)
		ans[G[n][tem[i]]].push_back(V[n][tem[i]]);
}
int main(){
	s=read;
	for(int i=1;i<=s;++i){
		ll x=read,y=read,z=read,w=read;
		int &u=ma[mul(x+y,y,z,w)],&v=ma[mul(x,y,z+w,w)];
		if(!u)u=++tot;if(!v)v=++tot;
		G[u].push_back(v);G[v].push_back(u);
		V[u].push_back(i);V[v].push_back(i);
	}
	for(int i=1;i<=tot;++i)
		if(!h[i])dfs(i,0);
	int t=0;
	for(int i=1;i<=tot;++i)
		t+=ans[i].size()/2;
	printf("%d\n",t);
	for(int i=1;i<=tot;++i)
		for(int j=1;j<ans[i].size();j+=2)
			printf("%d %d\n",ans[i][j-1],ans[i][j]);
	return 0;
}
```



---

## 作者：cirnovsky (赞：1)

点 $A$ 与 $(0,0)$，$B$ 共线的充要条件是 $\frac{y_A}{x_A}=\frac{y_B}{x_B}$，即 $k_{OA}=k_{OB}$。又考虑到题目提出刻画斜率相等双点间的关系，所以不妨把所有斜率相同的点看作一个。再考虑刻画点的移动，由于与共线的点是移动后两者之间的哪一者无妨，所以我们可以在移动后的两点所代表的斜率集合之间连一条边，问题就转化成了在一张无向图中，删除或一条三点二边的链，或一个二点二边的环，询问最多可以删除多少次，并给出可行方案。那么答案中最大值的部分我们可以拿出来，即 $\lfloor\frac{\text{\# edges}}{2}\rfloor$。

论删边的顺序，我们可以建出转化后图的任一生成树，并考虑非树边。考虑任一结点 $x$，设有非树边边 $\lang x,y\rang$，我们可以将 $y$ 给“拖下去”，意即新建一个点，并将 $x$ 连向该点。其正确性并非自明，但是考虑深度可以简单证明。至于答案的求解过程，参见常见 trick 树的最大匹配（但是略有不同，具体见代码）。

说一下如何精简实现，你的代码逻辑可以不是「建出原图 - 得到生成树 - 新建节点 - 求匹配」，更加优秀的逻辑可以是「建出原图并通过动态维护连通性新建节点 - 在求出生成树的同时获得深度信息 - 求匹配」。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n, rn, uset[500100], head[500100], to[1000100], nxt[1000100], ent;
ll gcd(ll x, ll y) {
    return y == 0 ? x : gcd(y, x%y);
}
int ldr(int x) {
    while (x != uset[x]) x = uset[x] = uset[uset[x]];
    return x;
}
bool sm(int x, int y) {
    return ldr(x) == ldr(y);
}
void mrg(int x, int y) {
    if (ldr(x) != ldr(y)) {
        uset[ldr(y)] = ldr(x);
    }
}
struct frac {
    ll p, q;
    frac() {}
    explicit frac(ll a, ll b) : p(a), q(b) {
        norm(*this);
    }
    bool operator<(const frac& o) const {
        return p < o.p || (p == o.p && q < o.q);
    }
    void norm(frac& x) {
        ll g = gcd(x.p, x.q);
        x.p /= g, x.q /= g;
    }
};
map<frac, int> mp;
void add(int x, int y) {
    to[++ent] = y, nxt[ent] = head[x], head[x] = ent;
}
bool vis[500100];
int dep[500100], fa[500100], eid[500100], mxd;
set<int> ch[500100], sd[500100];
void dfs(int x) {
    mxd = max(mxd, dep[x]);
    vis[x] = 1;
    sd[dep[x]].insert(x);
    for (int i = head[x], y; i; i = nxt[i]) {
        if (vis[y = to[i]]) {
            continue;
        }
        fa[y] = x, dep[y] = dep[x]+1;
        ch[x].insert(y);
        eid[y] = (i+1)/2;
        dfs(y);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        frac cur((a+b)*d, b*c);
        if (!mp.count(cur)) {
            ++rn;
            mp[cur] = uset[rn] = rn;
        }
        int u = mp[cur], v;
        cur = frac(a*d, b*(c+d));
        if (!mp.count(cur)) {
            ++rn;
            mp[cur] = uset[rn] = rn;
        }
        v = mp[cur];
        if (sm(u, v)) {
            v = ++rn;
        }
        else mrg(u, v);
        add(u, v), add(v, u);
    }
    for (int i = 1; i <= rn; ++i) {
        if (!vis[i]) dfs(i);
    }
    vector<pair<int, int>> ans;
    for (int d = mxd; d >= 1; --d) {
        for (int x : sd[d]) {
            if (int(ch[fa[x]].size()) >= 2) {
                ch[fa[x]].erase(x);
                int bro = *ch[fa[x]].begin();
                ch[fa[x]].erase(bro), sd[dep[bro]].erase(bro);
                ans.emplace_back(eid[x], eid[bro]);
            }
            else if (fa[fa[x]]) {
                ch[fa[x]].erase(x);
                ch[fa[fa[x]]].erase(fa[x]);
                sd[dep[fa[x]]].erase(fa[x]);
                ans.emplace_back(eid[x], eid[fa[x]]);
            }
        }
    }
    cout << ans.size() << "\n";
    for (auto it : ans) {
        cout << it.first << " " << it.second << "\n";
    }
}
```

---

## 作者：RedreamMer (赞：1)

[$\Large\texttt{CF1519E}$](https://www.luogu.com.cn/problem/CF1519E)

## 题意

给定 $n$ 个点，每个点 $(x_i,y_i)$ 可以变成 $(x_i + 1, y_i)$ 或 $(x_i, y_i + 1)$，极角相同的两个点可以两两匹配，每个点可以匹配一次，问最大的匹配数量是多少。

## 思路

$\Large\texttt{stO George1123}$

首先判断极角相同可以用 $\frac{x}{y}$ 解决。

我们可以将每个极角标号，而对于一个点，我们可以看作它是把两个不同的极角连边，而问题变成了：

给定一张图 $G$，对于 $E\in G$ 两条边 $e_1$，$e_2$ 可匹配当且仅当它们连接一个相同的点 $v$，求每条边唯一匹配的最大匹配数量。

这是一个经典问题。

我们对这个图不重复遍历一遍，得到一个 DFS 树。

那么我们从叶子节点开始考虑，先不考虑这个点连向父亲的边，如果连接其的边的数量是偶数个，那么直接两两匹配掉，如果不是，利用父亲的边平衡这个奇偶性，可以保证匹配数最大，**因为每个点（除了根节点）都有一条连向父亲的边平衡奇偶性，且必然没被用过，所以对于每个点（除了根节点），连接它的边都能够两两匹配不剩（除连接的父边）**。

注意图可能不连通。

答案就是 $\sum{|E_i| - |E_i|\texttt{ mod }2}$。

## 代码

由于实现过于垃圾，请谨慎参考QwQ。

```cpp
int a, top, sum;
bool vis[N + 5], use[N + 5];
struct road {
	int v, id;
	bool fa;
};
struct frac {
	LL x, y;
	bool operator<(const frac& o) const {return 1.0L * x * o.y < 1.0L * o.x * y;}
	bool operator==(const frac& o) const {return x == o.x && y == o.y;}
} q1[N + 5], q2[N + 5], q[N + 5];
frac f(LL n, LL m) {
	int gcd = __gcd(n, m);
	return (frac) {n / gcd, m / gcd};
}
vector<road> st[N + 5];
vector<int> ans[N + 5];

void dfs(int n, int fa) {
	vis[n] = 1;
	int tmp = 0;
	bool p = 0;
	rep(i, 0, siz(st[n]) - 1) {
		road v = st[n][i];
		if (v.v == fa && !p) {
			st[n][i].fa = 1, p = 1;
			continue;
		}
		if (vis[v.v]) {
			tmp += !use[v.id];
			continue;
		}
		dfs(v.v, n);
		tmp += !use[v.id];
	}
	if (tmp & 1) {
		rep(i, 0, siz(st[n]) - 1) {
			road v = st[n][i];
			if (use[v.id]) continue;
			ans[n].PB(v.id);
			use[v.id] = 1;
		}
	}
	else {
		rep(i, 0, siz(st[n]) - 1) {
			road v = st[n][i];
			if (use[v.id] || v.fa) continue;
			ans[n].PB(v.id);
			use[v.id] = 1;
		}
	}
	sum += siz(ans[n]) / 2;
}
signed main() {
	// freopen("in1.in", "r", stdin);
	// freopen("out.out", "w", stdout);
	LL x, xx, y, yy;
	a = read();
	rep(i, 1, a) {
		x = read();
		xx = read();
		y = read();
		yy = read();
		q1[i] = f(y * xx, yy * (x + xx));
		q2[i] = f((y + yy) * xx, yy * x);
		q[++top] = q1[i];
		q[++top] = q2[i];
	}
	sort(q + 1, q + top + 1);
	top = unique(q + 1, q + top + 1) - q - 1;
	rep(i, 1, a) {
		x = lower_bound(q + 1, q + top + 1, q1[i]) - q;
		y = lower_bound(q + 1, q + top + 1, q2[i]) - q;
		st[x].PB((road) {y, i, 0});
		st[y].PB((road) {x, i, 0});
	}
	rep(i, 1, top) if (!vis[i]) dfs(i, 0);
	printf("%lld\n", sum);
	rep(i, 1, top) {
		int lst = 0;
		rep(j, 0, siz(ans[i]) - 1) {
			if (lst) {
				printf("%lld %lld\n", lst, ans[i][j]);
				lst = 0;
			}
			else lst = ans[i][j];
		}
	}
	return 0;
}
```

---

## 作者：lsj2009 (赞：1)

### Solution

闲话：这个题 zzd 上课讲了一次，lcd 上课讲了一次，模拟赛考了一次，一共遇到了三次，绷不住了。

挺好 & 挺典的构造题。

我们称原本给定的点为 ``node``，将其向上/右移的点为 ``slope``，然后连边 ``node-slope``，显然我们得到的图每条边必然连接了一个 ``slope`` 和一个 ``node``。

而对于 ``node-slope-node`` 这么一条长为 $3$ 的链，我们显然可以考虑配对左右两个 ``node``，且有限制的是一个 ``node`` 只能配对一次。

我们考虑找出这个图的一个 dfs 生成树，假设一个树内恰有 $k$ 个 ``node`` 节点，显然我们至多只能配 $\lfloor \frac{k}{2}\rfloor$ 对，我们接下来将通过构造说明可以达到这个上界。

对于一个节点 ``slope`` 我们考虑将他的两个儿子节点 ``node1`` 和 ``node2`` 进行配对，如果说恰好有偶数个没有被配对的儿子，则我们刚好完成配对，直接回溯，否则恰有一个儿子未完成配对，我们考虑到该 ``slope`` 的父亲节点同样是一个 ``node`` 节点，将该儿子节点与其父亲节点完成配对即可。

脑内膜你一下，这种方案显然可以取到配对上界 $\lfloor \frac{k}{2}\rfloor$。

然后就做完了，由于我们需要为 ``slope`` 节点离散化标号，所以复杂度是 $\Theta(n\log{n})$，理论上用哈希可以做到线性复杂度。

### Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=1e6+5;
int head[N],len;
struct node {
	int to,nxt;
}; node edge[N<<1];
void add_edge(int u,int v) {
	edge[++len]={v,head[u]}; head[u]=len;
}
bool used[N],vis[N];
vector<PII> vec;
int d[N],n;
void link(int &x,int &y) { //配对两个node节点x,y
	used[x]=used[y]=true;
	vec.push_back({x,y});
	x=y=0;	
}
void dfs(int u,int fa) {
	vis[u]=true;
	d[u]=d[fa]+1;
	for(int i=head[u];i;i=edge[i].nxt) { //现在子树内进行配对
		int v=edge[i].to;
		if(!vis[v])
			dfs(v,u);
	}
	if(u>n) { //如果当前点是slope节点
		int x=0,y=0;
		for(int i=head[u];i;i=edge[i].nxt) {
			int v=edge[i].to;
			if(d[v]==d[u]+1&&!used[v]) { //取出未被配对的儿子节点
				if(!x)
					x=v;
				else
					y=v,link(x,y);
			}
		}
		if(x&&!y&&fa) //如果有多余没有完成配对的儿子节点，则与父亲节点配对
			y=fa,link(x,y);
	}
}
map<pair<ll,ll>,int> num;
void upd(pair<ll,ll> &t) { //约分
	ll g=__gcd(t.first,t.second);
	t.first/=g; t.second/=g;
}
signed main() {
	scanf("%d",&n);
	int cnt=n;
	rep(i,1,n) {
		ll a,b,c,d;
		scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
		//(a/b+1,c/d)*bd=(ad+bd,bc)
		pair<ll,ll> x={a*d+b*d,b*c}; upd(x);
		if(!num.count(x)) //为slope节点标号
			num[x]=++cnt;
		int v=num[x];
		add_edge(i,v);
		add_edge(v,i);
		//(a/b,c/d+1)*bd=(ad,bc+bd)
		x={a*d,b*c+b*d}; upd(x);
		if(!num.count(x))
			num[x]=++cnt;
		v=num[x];
		add_edge(i,v);
		add_edge(v,i);
	}
	rep(i,n+1,cnt) { //钦定根节点为slope节点，方便配对
		if(!vis[i])
			dfs(i,0);
	}
	printf("%d\n",(int)vec.size());
	for(auto x:vec)
		printf("%d %d\n",x.first,x.second);
    return 0;
}
```

---

## 作者：Tenshi (赞：0)

## 题意

给你 $n$ 个点，你需要对每个点都进行上/右移动一个单位的操作。

在操作完后，你每次可以选择一个点对，这两个点和 $(0, 0)$ 点三点共线，然后将这两个点删去。

求一个方案，使得你能够删掉的点对数最大。

## 思路

因为对答案的贡献有共线的约束，所以考虑从每个点操作后与 $(0, 0)$ 连线的斜率出发。利用建图刻画约束关系。

## 做法

考虑建图 $G$，对所有可能出现的斜率分别建成 $G$ 中的一个点。而对于每个题目中的点，可以发现都有两种斜率可以选择，故建为 $G$ 中对应两个点之间的*边*。

那么题目就变为让你从 $G$ 中找到最多的边对（当然边对之间的边是没有交集的），使得每个边对的边都共享至少一个点。

因为要构造具体方案，使用 DFS 树做这东西。把所有的*非树边*视作*前向边*。

然后做个匹配就行，记 DFS 到的当前点为 $u$：

- 如果 $u$ 的儿子 $go$ 在做完匹配后还有一条边剩下，那么直接把这条边拉去和 $(u, go)$ 做匹配。
- 其他边两两做一次匹配即可。

细节见代码。

## 代码

```cpp
// Problem: E. Off by One
// Contest: Codeforces - Educational Codeforces Round 108 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1519/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
 
#define debug(x) cerr << #x << ": " << (x) << endl
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
#define pb push_back
#define all(x) (x).begin(), (x).end()
 
#define x first
#define y second
#define int long long
using pii = pair<int, int>;
using ll = long long;
 
inline void read(int &x){
    int s=0; x=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=4e5+5;

pii K(int a, int b){
	int g=__gcd(a, b);
	a/=g, b/=g;
	return pii(a, b);
}

map<pii, int> ind;
int V;

int get(pii x){
	if(ind.count(x)) return ind[x];
	return ind[x]=++V;
}

vector<pii> g[N];
vector<pii> res;
int vis[N]; // 记录点状态：0 表示还未访问，1 表示在栈中，2 表示已经出栈。

int dfs(int u){
	vis[u]=1;
	int cur=0;
	for(auto [go, eid]: g[u]){
		if(vis[go]==1) continue;
		if(!vis[go]){
			int son_e=dfs(go); // 儿子 go 剩下来的边的编号。
			if(son_e){
				res.pb({eid, son_e});	
				continue;
			}
		}
		if(!cur) cur=eid;
		else{
			res.pb({cur, eid});
			cur=0;
		}
	}
	vis[u]=2;
	return cur;
}

void solve(){
	int n; cin>>n;
	rep(i, 1, n){
		int a, b, c, d; read(a), read(b), read(c), read(d);
		auto fir=K((a+b)*d, b*c);
		auto sec=K(a*d, b*(c+d));
		int u=get(fir), v=get(sec);
		g[u].pb({v, i}), g[v].pb({u, i});
	}
	
	rep(i, 1, V) if(!vis[i]) dfs(i);
	cout<<res.size()<<endl;
	for(auto &[x, y]: res) cout<<x<<" "<<y<<"\n";
}

signed main(){
	solve();	
	return 0;
}
```

---

## 作者：Mr_Wu (赞：0)

将斜率看做点，给的点看做边，那么给点 $(x,y)$ 表示在 $\frac{x+1}{y}$ 与 $\frac{x}{y+1}$ 之间连一条边。问题变为给一张无向图，每次将两有公共端点的边删除，问最多删除多少次。

容易猜出对于每个连通块，若它含 $e$ 条边则能匹配到理论最大值：$\lfloor \frac{e}{2}\rfloor$ 对边。

然后我卡了好久，最后得到了一个简单的处理方法：对于一个连通块求出它的一棵生成树，然后对于一条从 $u$ 到 $u$ 的祖先 $v$ 的返祖边 $(u,v)$，我们把这条边变成 $(u,v')$，其中 $v'$ 是 $u$ 的一个新的儿子。我们发现这个问题实际上是被加强了，因为本来边 $(u,v)$ 可以同时和端点为 $u$ 或 $v$ 的边匹配，但现在它只能和端点为 $u$ 的边匹配了。

但其实这个问题的难度变简单了，因为现在每个连通块都是一棵树。给每个连通块都定一个根，令 $K_u$ 为 $u$ 到父亲节点的边的编号。考虑每次找到深度最深的点 $u$，如果它有兄弟节点 $x$ 则匹配 $(K_u,K_x)$，否则匹配 $(K_u,K_{fa_u})$。

$O(n\log n)$，实现精细一点可能可以 $O(n)$ 吧我也不太清楚。

---

