# [AGC010F] Tree Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc010/tasks/agc010_f

$ N $ 頂点からなる木があり、頂点には $ 1 $ から $ N $ の番号がついています。 また、$ N-1 $ 本の辺の内、$ i $ 番目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結んでいます。

今、各頂点 $ i $ には $ A_i $ 個の石が置いてあります。 高橋君と青木君はこの木を使ってゲームをすることにしました。

まず、高橋君が一つの頂点を選び、そこに駒を置きます。 その後、高橋君から始めて以下の操作を交互に繰り返します。

- 今、駒がおいてある頂点から石を一つ取り除く。
- その後、その頂点に隣接する頂点を一つ選び、そこに駒を動かす。

駒が置いてある頂点に石がなく、操作を行えない人が負けです。 高橋君がこのゲームに勝つために、最初に駒を置くことができる頂点をすべて求めてください。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 3000 $
- $ 1\ ≦\ a_i,b_i\ ≦\ N $
- $ 0\ ≦\ A_i\ ≦\ 10^9 $
- 与えられるグラフは木である。

### Sample Explanation 1

高橋君が頂点 $ 2 $ に駒を置いたとき、例えば以下のようにゲームが進みます。 - 高橋君が駒を頂点 $ 1 $ に動かす。このとき、各頂点にある石の個数は $ (1,1,3) $ である。 - 青木君が駒を頂点 $ 2 $ に動かす。このとき、各頂点にある石の個数は $ (0,1,3) $ である。 - 高橋君が駒を頂点 $ 1 $ に動かす。このとき、各頂点にある石の個数は $ (0,0,3) $ である。 - 青木君が石を取れないため、高橋君の勝ちとなる。

### Sample Explanation 3

題意を満たす頂点が存在しない場合があることに注意してください。

## 样例 #1

### 输入

```
3
1 2 3
1 2
2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
5
5 4 1 2 3
1 2
1 3
2 4
2 5```

### 输出

```
1 2```

## 样例 #3

### 输入

```
3
1 1 1
1 2
2 3```

### 输出

```
```

# 题解

## 作者：yyxmy (赞：27)

#### 			$[AGC010F]做题记录$
对于这种博弈题， 乍一看上去没啥想法， 我们不妨由易到难，
从简单的情况入手：

如果当前只有两个节点  
![](https://cdn.luogu.com.cn/upload/image_hosting/igv3ccc5.png)

假设棋子在1号点， 那么先手只能往2节点走， 而后手只能返回1节点，
也就是说， 双方的选择是唯一的， 那么此时胜负情况就很明了了， 先手必胜当且
$A_1 > A_2$, 等于的话是不行的。

我们现在把情况变得复杂一点， 如果是这样一种情况
![](https://cdn.luogu.com.cn/upload/image_hosting/zq7j2yze.png)  
假设当前棋子在1号点， 那么先手必须向某个叶节点移动， 后手必须从叶节点反回1号点，
比较显然,先手每次移到$A_i$最小的那个叶节点是最优的， 那么此时先手必胜当且仅当$minA_i < A_1$.

我们让情况再复杂一点  
![](https://cdn.luogu.com.cn/upload/image_hosting/xlbr57jh.png)  
如果棋子在6号节点， 那么先手下一步会移动到1， 或者是7。		
 
假设在1的这棵子树内， 1号点是先手必胜的话， 那么6一定不会往1走， 因为一旦走到1， 后手就会有必胜的策略， 而如果1是后手必胜的话， 那么6往1走后， 后手一定会返回6节点， 因为继续往下走的话， 先手会有必胜策略。 这似乎又回到了我们上一幅图的情况， 先手会往一个节点走， 而该点会返回。   
那么此时先手必胜， 当且仅当所有后手必胜的儿子节点A的最小值小于$A_i$

于是我们可以枚举所有点作为根， dfs处理每个点儿子的情况， 然后判断该点的胜负状况， 代码十分简单。
```cpp
#include<bits/stdc++.h>
#define N 10001
#define mod 1000000007

#define reg register
using namespace std;
inline int  read() {
    reg int s = 0, t = 0; reg char ch = getchar();
    while(ch > '9' || ch < '0') t |= ch == '-', ch = getchar();
    while(ch >= '0' && ch <= '9') s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
    return t ? -s : s;
}
int nt[N], fi[N], go[N], dp[N], a[N], cnt, n;
int inc(int x, int y){
    return x + y >= mod ? x + y - mod : x + y;
}
void add(int x, int y){
    nt[++cnt] = fi[x]; fi[x] = cnt; go[cnt] = y;
}
void DFS(int x, int fa){
    dp[x] = false;
    for(int i = fi[x]; i; i = nt[i]){
        int v = go[i]; if(v == fa) continue;
        DFS(v, x); 
        if(dp[v] == false && a[x] > a[v]) dp[x] = true;
    }
}
int main(){
    n = read();
    for(int i = 1; i <= n; i++) a[i] = read();
    for(int i = 1; i < n; i++){
        int x = read(), y =  read();
        add(x, y); add(y, x);
    }
    for(int i = 1; i <= n; i++){
        memset(dp, 0, sizeof dp);
        DFS(i, 0); if(dp[i]) printf("%d ", i);
    }
}
```



---

## 作者：FZzzz (赞：9)

定理：走到一个权值不小于当前点的点是不优的。

证明：对权值从小到大进行归纳，假设我们证明了当前点权值权值较小时的情况。如果你走向了一个权值不小于当前点的点，那么对手总可以走回来，直到你走不动或者走向一个权值更小的点。此时根据归纳法，对手不会再走回来，那你不如一开始就走向这个点。

于是只会不断走向权值更小的点，如果不存在这样的点就必败。那么我们的结论是一个点必胜当且仅当它有一个权值比它小并且必败的邻居。
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline ll read(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=3e3+5;
int n,a[maxn],ord[maxn];
vector<int> g[maxn];
bool f[maxn];
int main(){
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<n;i++){
		int u,v;
		u=read();
		v=read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i=1;i<=n;i++) ord[i]=i;
	sort(ord+1,ord+n+1,[](int x,int y){
		return a[x]<a[y];
	});
	for(int i=1;i<=n;i++){
		int u=ord[i];
		for(int v:g[u]) f[u]|=a[v]<a[u]&&!f[v];
	}
	for(int i=1;i<=n;i++) if(f[i]) printf("%d ",i);
#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
	return 0;
}
```
写题解的原因是感觉其他题解的证明要么不够严谨，要么没有我这个漂亮（

---

## 作者：素质玩家孙1超 (赞：7)

题意：

一颗 $n$ 个点的带权树，先手会在一个节点上放一个棋子，从先手开始，他们进行以下操作，将棋子节点的权值 $-1$，选择一个相邻的权值不为零的节点移动棋子。如果有一个人移动之前该节点权值就变成 $0$ 了，那么他就输了。

---

考虑最初始的节点 $u$ ，对于他的相邻节点 $v$ 若有 $a_v\ge a_u$ 则 $u$ 无法去到 $v$ （后手会让棋子移回来，这样就输了）。那么 $u$ 只能去到 $v$ 其中 $a_v<a_u$ ，那么在去到 $v$ 的过程中能不能去到其他的地方“蹭”一下呢？

答案是否定的，因为 $a_v<a_u$ 所以到了 $v$ 之后，后手是不会想要回到 $u$ 的，因为上述原因，所以可以看做 $a_u$ 的大小不会影响后面的操作。如果去蹭了，那么 $a_u$ 会无端减小，对于先手来说不利。这个时候就可以得到结论了：每次都只会去权值较小的节点，其他节点不会去，且不会原路返回。

这样就转换成只要套一个必胜/必败点的板子了。

---

看到别人给的代码都是 $\mathcal O(n^2)$ 的，所以就复读了一下做法然后发一份自己的 $\mathcal O(n)$ 的代码。

```cpp
int f[N],val[N];bool vis[N];
bool dfs(int u){
    if(vis[u])return f[u];
	f[u]=0;vis[u]=1;
    for(int i=head[u];i;i=e[i].nxt)
    if(val[u]>val[e[i].to])
    if(!dfs(e[i].to))f[u]=1;
    return f[u];
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&val[i]);
    for(int u,v,i=1;i<n;i++)scanf("%d%d",&u,&v),add(u,v),add(v,u);
    for(int i=1;i<=n;i++)
    if(dfs(i))printf("%d ",i);
}
```

---

## 作者：ezoixx174 (赞：3)

链接：[AT2307 Tree Game](https://www.luogu.org/problemnew/show/AT2307)（翻译在讨论中有）

大致题意：给定一颗树，树上的某个节点上有一颗棋子，每个点有一定权值，双方轮流执行：将当前棋子位置权值-1，并将之移动至相邻节点，先无法移动者输；问初始棋子在哪些节点可使先手必胜。

#### 题解#### 

典型的博弈论题目，先来证明一条性质：最优解一定是往比当前棋子节点权值小的地方移动；若没有，则该节点为先手的必败点。

假设当前棋子节点为$u$，可移动的点为$v_1,v_2$，其中$w_{v_1}<w_u<w_{v_2}$，若向$w_2$移动，则对手可以再次移回$u$，最后先手输。因此最优解为向$v_1$移动，同理若不存在$v$使得$w_v<w_u$则对手可以利用上述策略获胜。

因此我们的判断条件就变为了是否存在比当前节点权值小的点。

#### 代码####

```cpp
#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

bool check[3001];
int n,x,y,w[3001];
vector<int> point[3001];

bool dfs(int u,int f){
	check[u]=false;
	for(int v:point[u])if(v!=f&&w[v]<w[u]){dfs(v,u);if(!check[v]){check[u]=true;break;}}
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",w+i);
	for(int i=1;i<n;++i)scanf("%d%d",&x,&y),point[x].push_back(y),point[y].push_back(x);
	for(int i=1;i<=n;++i){dfs(i,0);if(check[i])printf("%d ",i);}
}
```

---

## 作者：qzhwlzy (赞：2)

题目大意：有一棵含 $n$ 个节点的树，每个节点上有 $a_i$ 颗石子。现在两人进行游戏，先手先将一个标记放在某个节点处，之后先后手轮流进行以下操作：取走有标记节点的一颗石子，然后沿边将标记移到下一个节点，最先没有石子可取者输。输出先手所有可以放标记且有必胜策略的点（$2\le n\le 3000$，时限 $2s$）。

记先手第一次放标记的点为根。

![](https://cdn.luogu.com.cn/upload/image_hosting/s41xtwz0.png)

我们先来看一些简单的情况。如上左图，若只有两个点，显然只有 $a_r > a_c$ 时才能赢，否则后手可以和先手反复横跳直至 $a_r$ 先会等于 $0$。若根有多个子节点（假设子节点没有子树），一旦存在一个子节点 $c$ 使得 $a_r > a_c$，那么先手就能必胜。这是我们以下情况的基础。

我们先给出结论：当且仅当一个节点 $v$ 存在一个子节点 $c$ 满足 $a_c < a_v$ 且以 $c$ 为根的子树中先手必败（P - position），那么这个节点先手必胜（N - position），否则先手必败（P - position）。

下面给出证明：
若一个节点 $v$ 满足上述条件，那么先手可以将标记移到子节点 $c$ 上。之后，后手有两种方式：一是将标记移回 $v$，那么先手可以再移回 $c$，反复横跳直到 $a_c$ 先为 $0$，此时先手胜；二是往 $c$ 的子树移，因为 $c$ 是 P - position，所以先手也胜。即使后手先反复横跳几次使得 $a_c$ 和 $a_v$ 变小了，也不会改变 $c$ 的状态（P - position）。

若一个节点 $v$ 不满足上述条件：假设 $v$ 的所有子节点都是 N - position，那么若把标记移过去后手一定必胜；假设 $a_c \ge a_v$，那么由上面的基础情况，后手可以和先手反复横跳直到先手输。

所以，我们可以枚举根节点（第一次放标记的位置），进行 DFS 即可。复杂度 $\mathcal{O}(n^2)$，可以过。

```cpp
#include<iostream>
#include<cstdio>
#define maxn 3005
using namespace std;
int n,uu,vv,s[maxn]; struct node{int to,nex;}a[maxn*2]; int head[maxn],tot=0;
void add(int from,int to){a[++tot].to=to;a[tot].nex=head[from];head[from]=tot;}
int dfs(int p,int fa){
	bool flag=0;
	for(int i=head[p];i;i=a[i].nex) if(a[i].to!=fa) if(!dfs(a[i].to,p)&&s[a[i].to]<s[p]) flag=1; return flag;
}
int main(){
	scanf("%d",&n); for(int i=1;i<=n;i++) scanf("%d",&s[i]);
	for(int i=1;i<n;i++){scanf("%d%d",&uu,&vv); add(uu,vv); add(vv,uu);}
	for(int i=1;i<=n;i++) if(dfs(i,0)) printf("%d ",i);
	return 0;
}
```

---

## 作者：dfkdsmbd (赞：2)

不是很懂楼下哥哥为何只需要判断$a_u>a_v$，我这种newbie还是写一个我看得懂的题解吧，不过复杂度没有楼下这么神仙罢了。

考虑这么一个事情，对于一个点$x$和他的子树，这个点先手必胜，一定存在一个儿子$son$，使得$a_{x}>a_{son}$并且$son$这个子树先手必败。

假如$a_{x} \leq a_{son}$，那么后手就可以通过不停回到$x$然后耗死先手，而$a_{x}>a_{son}$时候，后手如果跳回$x$则会被耗死，所以他只能往$son$这个子树跳，进入这个子树，先后手交换，原来的后手变成了先手，这个时候先手必败，也就说原来的后手必败。

边界条件是跳到叶子节点，这个时候没有任何一个点可以供这个点上的先手跳，为先手必败态。

每次考虑一个点的时候dfs一遍 ，时间复杂度$O(n^2)$
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <utility>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <map>
#include <set>
#define ri register int
#define pi acos(-1.0)

using namespace std;

inline char gch()
{
    static char buf[100010], *h = buf, *t = buf;
    return h == t && (t = (h = buf) + fread(buf, 1, 100000, stdin), h == t) ? EOF : *h ++;
}

typedef long long lo;

typedef unsigned int uint;

template<typename inp_typ>

inline void re(inp_typ &x)
{
    x = 0;
    char a; bool b = 0;
    while(!isdigit(a = getchar()))
        b = a == '-';
    while(isdigit(a))
        x = x * 10 + a - '0', a = getchar();
    if(b == 1)
        x = - x;
}

bool sta[5050];

int tot = -1, lx, ly, head[5050], n, a[5050];

struct in
{
    int to, ne;
}ter[10010];

inline void build(int f, int l)
{
    ter[++ tot] = (in){l, head[f]}, head[f] = tot;
    ter[++ tot] = (in){f, head[l]}, head[l] = tot;
}

void dfs(int no, int f)
{
    sta[no] = 0;
    for(ri i = head[no]; i >= 0; i = ter[i].ne)
    {
        int to = ter[i].to;
        if(to == f)
            continue;
        dfs(to, no);
        if(a[no] > a[to] && (!sta[to]))
        {
            sta[no] = 1; break;
        }
    }
}

int main()
{
    re(n), memset(head, -1, sizeof(head));
    for(ri i = 1; i <= n; re(a[i ++]));
    for(ri i = 1; i < n; i ++)
        re(lx), re(ly), build(lx, ly);
    for(ri i = 1; i <= n; i ++)
    {
        dfs(i, 0);
        if(sta[i])
            printf("%d ", i);
    }
    system("pause");
}
```

---

## 作者：Genius_Star (赞：1)

**这里提供一个 $O(N)$ 的拓扑排序算法。**

### 思路：

先说结论：若一个点 $u$ 为必胜点，必有一个它的儿子 $son$ 满足 $a_u > a_{son}$，且 $son$ 为必败点。

证明：

- 若 $a_u \le a_{son}$：

  - 则当先手移到别的点时，后手可以又将其移回来；这样可以不断耗死先手。

- 弱 $a_u > a_{son}$：

  - 则若后手执意要跳回 $u$，则先手可以又将其移到 $son$ 这个点；这样可以耗死后手。
  
当一个点为叶子节点时，这个点肯定是必败点。

那么可以直接暴力枚举根，然后深搜一遍即可，时间复杂度为 $O(N^2)$。

考虑优化，因为若 $v$ 能对 $u$ 造成影响当且仅当 $a_u > a_v$，且 $v$ 是 $u$ 的儿子。

那么建图的时候就可以按照 $a_u,a_v$ 的大小建单向边。

此时进行拓扑排序即可。

时间复杂度优化为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=3030;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n;
ll a[N],d[N];
bool f[N];
vector<ll> E[N];
void add(ll u,ll v){
	E[u].push_back(v);
	d[v]++;
}
void topo(){
	queue<ll> q;
	for(int i=1;i<=n;i++)
	  if(!d[i])
	    q.push(i);
	while(!q.empty()){
		ll u=q.front();
		q.pop();
		for(auto v:E[u]){
			if(!f[u])
			  f[v]=1;
			if(!--d[v])
			  q.push(v);
		}
	}
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	for(int u,v,i=1;i<n;i++){
		u=read(),v=read();
		if(a[u]>a[v])
		  add(v,u);
		if(a[u]<a[v])
		  add(u,v);
	}
	topo();
	for(int i=1;i<=n;i++){
		if(f[i]){
			write(i);
			putchar(' ');
		}
	}
	return 0;
}
```

---

## 作者：TachibanaKanade (赞：1)

最近在练一些思维难度的题，尽量做到一题写一篇题解加深印象。

题意：在一棵树上，每个点都有一个点权。两人依次把上一人所选的节点的其中一个相邻节点的点权减 $1$，直到其中一个人把任意节点的点权变为 $0$ 时获胜。求先手的所有必胜点。

首先考虑只存在叶子节点和根节点的树。对于根节点而言，显然先手一定会往权值最小的叶子节点走（因为后手只有一条往根节点走的路径，此时先手为了先使自己获胜一定先往点权更容易变成 $0$ 的节点，即点权最小的叶子节点走）。此时先手当且仅当根节点的点权大于所有叶子节点的最小点权时可获胜。

而事实上，由上可知，当父结点节点的点权大于其所有子节点的最小点权时，该节点就是先手必胜态；否则，它就是先手必败态。

而当树的层数变多时，不妨从下到上考虑。此时，对于每一层的节点，我们都可以求出它们的子节点是先手必胜态或先手必败态。而对于节点 $u$，若其子节点 $v$ 是必胜态，则先手必不可能从 $u$ 走到 $v$（因为如果到达 $v$ 点，则后手转为先手，后手有必胜策略）。故先手必会走到先手必败态的子节点。

而此时后手必不可能继续向下走（因为在当前子树中后手是先手，必败），故后手一定往回走回 $u$ 节点。此时，不用考虑 $u$ 所有子节点的子树（因为上已证后手不可能往子树走），故此时又回到了最上面所讨论的只存在叶子节点和根节点的情况，只需判断 $u$ 的点权大于其所有子节点的最小点权即可（换言之，只要枚举 $u$ 所有子节点，当中只要有点权小于 $u$ 的，则 $u$ 是先手必胜态）。

综上，先手的策略即为：不断去权值更小的子节点且不会回溯，直到找不到更小的节点为止。

而对于每一个节点是否是先手必胜态，只需以该节点为根节点（因为是树所有根节点所以不用考虑环的情况），`dfs` 跑一遍必胜必败点的板子即可。

代码略。

---

## 作者：xcyle (赞：0)

好水的F......

我们只考虑初始点$rt$确定的情况，此时这是一棵有根树

考虑若$\forall v \in nxt(rt)$（$nxt(u)$表示$u$的邻接点集合），$a_v \ge a_u$，则无论先手怎么走，后手可以再一步回到$rt$，这时先手必败

那么如果不是这样的，先手一定会一步走到满足$a_v<a_u$的$v$，因为它先走一些比它大的是对自己不利的，这样会让自己的$a_u$变小。

这样我们会发现双方每次一定会向当前点的孩子走，搜一下就行了，因为没有环显然有正确性与优秀的时间复杂度

---

