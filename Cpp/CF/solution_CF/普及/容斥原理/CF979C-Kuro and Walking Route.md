# Kuro and Walking Route

## 题目描述

Kuro is living in a country called Uberland, consisting of $ n $ towns, numbered from $ 1 $ to $ n $ , and $ n - 1 $ bidirectional roads connecting these towns. It is possible to reach each town from any other. Each road connects two towns $ a $ and $ b $ . Kuro loves walking and he is planning to take a walking marathon, in which he will choose a pair of towns $ (u, v) $ ( $ u \neq v $ ) and walk from $ u $ using the shortest path to $ v $ (note that $ (u, v) $ is considered to be different from $ (v, u) $ ).

Oddly, there are 2 special towns in Uberland named Flowrisa (denoted with the index $ x $ ) and Beetopia (denoted with the index $ y $ ). Flowrisa is a town where there are many strong-scent flowers, and Beetopia is another town where many bees live. In particular, Kuro will avoid any pair of towns $ (u, v) $ if on the path from $ u $ to $ v $ , he reaches Beetopia after he reached Flowrisa, since the bees will be attracted with the flower smell on Kuro’s body and sting him.

Kuro wants to know how many pair of city $ (u, v) $ he can take as his route. Since he’s not really bright, he asked you to help him with this problem.

## 说明/提示

On the first example, Kuro can choose these pairs:

- $ (1, 2) $ : his route would be $ 1 \rightarrow 2 $ ,
- $ (2, 3) $ : his route would be $ 2 \rightarrow 3 $ ,
- $ (3, 2) $ : his route would be $ 3 \rightarrow 2 $ ,
- $ (2, 1) $ : his route would be $ 2 \rightarrow 1 $ ,
- $ (3, 1) $ : his route would be $ 3 \rightarrow 2 \rightarrow 1 $ .

Kuro can't choose pair $ (1, 3) $ since his walking route would be $ 1 \rightarrow 2 \rightarrow 3 $ , in which Kuro visits town $ 1 $ (Flowrisa) and then visits town $ 3 $ (Beetopia), which is not allowed (note that pair $ (3, 1) $ is still allowed because although Kuro visited Flowrisa and Beetopia, he did not visit them in that order).

On the second example, Kuro can choose the following pairs:

- $ (1, 2) $ : his route would be $ 1 \rightarrow 2 $ ,
- $ (2, 1) $ : his route would be $ 2 \rightarrow 1 $ ,
- $ (3, 2) $ : his route would be $ 3 \rightarrow 1 \rightarrow 2 $ ,
- $ (3, 1) $ : his route would be $ 3 \rightarrow 1 $ .

## 样例 #1

### 输入

```
3 1 3
1 2
2 3
```

### 输出

```
5```

## 样例 #2

### 输入

```
3 1 3
1 2
1 3
```

### 输出

```
4```

# 题解

## 作者：STA_Morlin (赞：5)

[题目](https://www.luogu.com.cn/problem/CF979C)

## 思路简析

观察这个问题，首先看到点和边数量分别是 $n$ 和 $n-1$，并且它是一个连通图，所以它一定是一棵树。

又看到“点对 $(u, v)$ 与点对 $(v, u)$ 被认为是不同的。”，可知它本质上是有向图。

这是一个容斥原理，具体说就是总共有 $A_n^2 = n\times (n-1)$ 个点对，将其中所有简单路径过 $(x, y)$ 的点对去掉，剩下的即为答案。

因此，考虑如何找到简单路径过 $(x, y)$ 的所有点对：

直观地说，先找到 $(x, y)$ 的简单路径，然后切断 $x$ 在简单路径上延伸（$x$ 到 $2$）的边和 $y$ 在简单路径上延伸（$y$ 到 $2$）的边。此时，图会分裂成三个部分（因为它是一棵树），即 $x$ 部分，$y$ 部分和其余部分。

如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/i6paouzb.png)

由于它是一棵树，所以任意一个点对都只有 $1$ 条简单路径。显然，有且只有蓝色点与红色点的点对的简单路径过 $(x, y)$。设蓝色（$x$）部分共有 $a$ 个点，红色（$y$）部分共有 $b$ 个点，则蓝色点与红色点的点对共有 $a\times b$ 个。

## 代码实现

首先需要找到根。

在解决蓝色部分的大小时考虑以 $y$ 为根，在搜索到 $x$ 时停止搜索，记录其余所有能搜到的点的数量 $ly$，则 $a = n-ly$。同理，$b = n-lx$。

## _CODE_
Time complexity：$\Omega(n)$.

```cpp
#include <bits/stdc++.h>
namespace {
#define filein(x) freopen(x".in", "r", stdin)
#define fileout(x) freopen(x".out", "w", stdout)
#define files(x) filein(x), fileout(x)
using namespace std;
#define ll long long
#define db double

const int man = 3e5+10, mam = 3e5+10, mmp = 1e9+1;
class Graph {
public:
    int len = 1, hed[man];
    int nxt[mam<<1], ver[mam<<1];
    template <typename T>
    void Ins (T u, T v) {
        ver[++len] = v;
        nxt[len] = hed[u];
        hed[u] = len;
    }
    template <typename T>
    void DIns (T u, T v) {
        Ins(u, v), Ins(v, u);
        return ;
    }
} G;
}

int n, x, y, a, b;
bool vis[man];
void dfs (int, int&, int) ;
int main () {
#ifndef ONLINE_JUDGE
    files("test");
#endif
    scanf("%d%d%d", &n, &x, &y);
    for (int u, v, i = 1; i < n; ++ i) 
        scanf("%d%d", &u, &v), G.DIns(u, v);
    dfs(x, a, y); a = n-a;
    memset(vis, 0, sizeof(vis));
    dfs(y, b, x); b = n-b;
    printf("%lld", 1LL*n*(n-1)-1LL*a*b);
    // Attention, n*(n-1) and a*b both need 1LL.
    return 0;
}

// ---

void dfs (int x, int& l, int nt) {
    vis[x] = 1, ++ l;
    for (int i = G.hed[x]; i; i = G.nxt[i]) {
        int v = G.ver[i];
        if (!vis[v] && v!=nt) dfs(v, l, nt);
    } return ;
}
```

---

## 作者：RainbOwO (赞：5)

# 两步dfs遍历图（其实是树）即可求解
翻译题目里面已经有了在这就不多加赘述了
总共n个节点n-1条边，说明这个无向图图是个树

我们可以先以x为根节点遍历图，遇到y即停止，
计算x不经过y所能到达的节点数numx，n-numx即为y及y一侧的节点数（不包括x与y之间的节点）

再以y为根节点，重复上述过程

所有路径的总数为组合数Cn2即n*（n-1）

x到y的路径数为总数减去x，y及各自两侧节点的积

因为数据较大，应用long long计算

```cpp
#include<bits/stdc++.h>
using namespace std;

vector<int>ve[300005];
bool vis[300005];
bool pos[300005];
long long n,x,y,numx=0,numy=0;
void build(int a,int b)
{
    ve[a].push_back(b);
    ve[b].push_back(a);
}

void dfs1(int node)
{
    if(node==y)
    {
        return;
    }
    vis[node]=1;
    int big=ve[node].size();
    for(int i=0;i<big;i++)
    {
        if(!vis[ve[node][i]])
        {
            vis[ve[node][i]]=1;
            numx++;
            dfs1(ve[node][i]);
        }
    }
}

void dfs2(int node)
{
    if(node==x)
    {
        return;
    }
    vis[node]=1;
    int big=ve[node].size();
    for(int i=0;i<big;i++)
    {
        if(!vis[ve[node][i]])
        {
            vis[ve[node][i]]=1;
            numy++;
            dfs2(ve[node][i]);
        }
    }
}

int main()
{

    scanf("%lld%lld%lld",&n,&x,&y);
    for(int i=1;i<=n-1;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        build(a,b);
    }
    dfs1(x);
    memset(vis,0,sizeof(vis));
    dfs2(y);
    printf("%lld\n",n*(n-1)-(n-numx)*(n-numy));
    return 0;
}

```


---

## 作者：SunnyYuan (赞：3)

## 思路

其实本题很简单，只要将树的根换为 $x$，然后答案就是 $n \times (n - 1)$ 减去这两个 $size$ 相乘，即所有的方案减去这两个被我圈出来的部分的点两两组合的个数。

![](https://cdn.luogu.com.cn/upload/image_hosting/0lkza61b.png)

第一个 $size_1$ 就是原本的 $size_x$ 减去 $y$ 所在的子树的 $size_v$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 300010, M = 600010;

struct edge {
    int to, next;
} e[M];

int head[N], idx;

void add(int u, int v) {
    idx++, e[idx].to = v, e[idx].next = head[u], head[u] = idx;
}

int n, x, y;
int sz[N];

bool dfs(int u, int fa) {
    bool flag = (u == y);
    sz[u] = 1;
    for (int i = head[u]; i; i = e[i].next) {
        int to = e[i].to;
        if (to == fa) continue;
        bool d = dfs(to, u);
        if (!d) sz[u] += sz[to];
        flag |= d;
    }
    return flag;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >>n >> x >> y;

    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }

    dfs(x, 0);
    cout << 1ll * n * (n - 1) - 1ll * sz[x] * sz[y] << '\n';
    return 0;
}
```

---

## 作者：大菜鸡fks (赞：3)

根据x和y的相对位置讨论需要容斥（其实也不是容斥）掉的方案数

```cpp
#include<cstdio>
using namespace std;
typedef long long ll;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(ll x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(ll x){write(x); puts("");}
const int N=3e5+5;
struct edge{
	int link,next;
}e[N<<1];
int n,tot,x,y,head[N];
inline void add_edge(int u,int v){
	e[++tot]=(edge){v,head[u]}; head[u]=tot;
}
inline void insert(int u,int v){
	add_edge(u,v); add_edge(v,u);
}
inline void init(){
	n=read(); x=read(); y=read();
	for (int i=1;i<n;i++){
		insert(read(),read());
	}
}
int flag,Fa[N],sz[N];
ll ans;
void dfs(int u,int fa){
	sz[u]=1; Fa[u]=fa;
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (v!=fa){
			dfs(v,u);
			sz[u]+=sz[v];
		}
	}
}
inline void solve(){
	dfs(1,0); ans=1ll*(n-1)*n; int X=x,Y=y;
	for (;x;x=Fa[x]) if (Fa[x]==y) ans-=1ll*sz[X]*(n-sz[x]),flag=1;
	x=X; y=Y;
	for (;y;y=Fa[y]) if (Fa[y]==x) ans-=1ll*sz[Y]*(n-sz[y]),flag=1;
	if (!flag) ans-=1ll*sz[X]*sz[Y];
	writeln(ans);
}
int main(){
	init();
	solve();
	return 0;
} 
```

---

## 作者：npqenqpve (赞：2)

### 思路：
考虑容斥，总方案数是 $n\times(n-1)$，因为有方向所以不用除以 $2$，应该减去的是顺序经过 $x$，$y$ 的，考虑以 $x$ 为根把树拎起来，记 $d_u$ 为以 $u$ 为根的子树大小，则有 $n\times d_y$ 种方法经过 $y$，但我们希望先经过 $x$，考虑 $v$ 是 $x$ 的一个直接子节点，那么必然存在恰好一个 $v$ 使 $y$ 在以 $v$ 为根的子树内，这棵子树内的点走到 $y$ 的子树内的任意一点不会经过 $x$，答案为 $n\times (n-1)-(n-d_v)\times d_y$，其中 $v$ 是子树中有 $y$ 的那个 $x$ 的直接子节点。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define ld long double
using namespace std;
int n,x,y,sz[(int)(3e5+10)];
vector<int>edge[(int)(3e5+10)];
void dfs(int u,int fa)
{
    sz[u]=1;
    for(int i=0;i<edge[u].size();i++)
    {
        int v=edge[u][i];
        if(v==fa) continue;
        dfs(v,u);
        sz[u]+=sz[v];
    }
}
bool f[(int)(3e5+10)];
void dfs1(int u,int fa)
{
    for(int i=0;i<edge[u].size();i++)
    {
        int v=edge[u][i];
        if(v==fa) continue;
        dfs1(v,u);
//        cout<<u<<" "<<v<<"\n";
        f[u]|=f[v];
    }
}
signed main()
{
    cin>>n>>x>>y;
    for(int i=1;i<n;i++)
    {
        int u,v;cin>>u>>v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    int ans=n*(n-1);f[y]=1;
    dfs(x,0);
    dfs1(x,0);
//    for(int i=1;i<=n;i++) cout<<f[i]<<" ";
//    puts("");
    for(int i=0;i<edge[x].size();i++)
    {
        int v=edge[x][i];
//        cout<<v<<" "<<dfs1(v,x)<<"\n";
        if(f[v])
        {
            ans-=(sz[x]-sz[v])*sz[y];break;
        }
    }
    cout<<ans;
}
```

---

## 作者：yaodiguoan (赞：0)

## 题目描述
给你一个 $n$ 个点 $(n-1)$ 条边的图，给定 $2$ 个点 $x,y$，问有多少个点对 $(u,v)$ 使得点 $u$ 到点 $v$ 的最短距离中**不存在**先到达 $x$，在到达 $y$ 的情况。点对 $(u,v)$ 与点对 $(v,u)$ 被认为是不同的。\
$1 \le x,y \le n \le 3 \times 10^5,x \ne y$
## 思路
首先，这个图是一棵树，这样，问题就简化了许多。\
然后，因为这个图是一棵树，所以不存在环，且图上连点的最短距离为它们与其 `lca` 的距离之和。\
我们让 $x$ 作为树根，这样，除了 $y$ 所在子树（根为 $x$ 的子节点）的节点后的其它节点个数与 $y$ 为根的子树的节点个数的乘积，就为不符合题意的点对的数量。用 $n \times (n-1)$ 减去他，就是题目所求的答案。\
举个例子，如下图，$\begin{cases}x=1\\y=2\end{cases}$，答案即为 $n\times (n-1) - siz1 \times siz2$。
![](https://cdn.luogu.com.cn/upload/image_hosting/s5effe54.png)
## 代码
```cpp
// LUOGU_RID: 164406305
#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize(2)
//#pragma GCC optimize(3, "Ofast", "inline")
#define hh putchar('\n')
#define kg putchar(' ')
#define debug puts("debug")
#define int long long
//#define int __int128
namespace quickread{
	inline int read(){
		int x=0,f=1;char ch=getchar();
		while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
		while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
		return x*f;
	}
	inline void write(int x){
	    if(x<0){putchar('-');x=-x;}
	    if(x>9)write(x/10);
	    putchar(x%10+'0');
	}
	inline string readstr(){
    	char ch=getchar();string str="";
		while(!(ch>='0'&&ch<='9')&&!(ch>='a'&&ch<='z')&&!(ch>='A'&&ch<='Z')) ch=getchar();
		while((ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){str+=ch;ch=getchar();}
		return str;
	}
	inline char readchar(){
		char ch=getchar();
		while(!(ch>='0'&&ch<='9')&&!(ch>='a'&&ch<='z')&&!(ch>='A'&&ch<='Z')) ch=getchar();
		return ch;
	}
}
using namespace quickread;
const int N=3e5+10,M=110,inf=2147483647;
long long n,sum[N];int x,y;
vector<int> tree[N];
bool dfs(int u,int f){
    bool flag=1;
    if(u==y) flag=0;
    sum[u]=1;
    for(int v:tree[u])
        if(v!=f) {
            bool k=dfs(v,u);
            sum[u]+=sum[v]*k;
            if(!k) flag=0;
        }
    return flag;
}
signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
    n=read(),x=read(),y=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        tree[u].push_back(v),tree[v].push_back(u);
    }
    int f=dfs(x,0);
    write(n*(n-1)-sum[x]*sum[y]);
	return 0;
}
```
[AC 记录](https://codeforces.com/contest/979/submission/269162611)

---

