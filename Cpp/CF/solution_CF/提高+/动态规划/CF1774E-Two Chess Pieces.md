# Two Chess Pieces

## 题目描述

# Two Chess Pieces


Cirno\_9baka 有一棵包含 $n$ 个节点的树。他愿意把它与你分享，这意味着你可以对它进行一些操作。  

最初，树的 $1$ 号节点上有两个棋子。对每个操作，您可以选择任意一个棋子，并将其移动到相邻节点。你需要确保两个棋子之间的距离不会超过 $d$。

给你两个序列，分别表示两个棋子需要经过的节点（可以以**任何顺序**经过）。最终，它们必须回到根节点。作为一个好奇的男孩，Cirno\_9baka 想知道最少操作次数。

## 样例 #1

### 输入

```
4 2
1 2
1 3
2 4
1 3
1 4```

### 输出

```
6```

## 样例 #2

### 输入

```
4 2
1 2
2 3
3 4
4 1 2 3 4
1 1```

### 输出

```
8```

# 题解

## 作者：蒟蒻君HJT (赞：13)

简单题。

考虑对于某个棋子，每个点 $x$ 是否需要到达。

设结点深度为 $d_x$ 。

结论：

1. $x$ 子树内存在这个棋子需要达到的点，那么必须到达。

2. $x$ 子树内另一个棋子最深的需要达到的点为 $y$，若 $d_y-d_x > D - 1$ 那么必须到达。

所以直接一遍 dfs 搜出每个子树内两个棋子分别最深的深度就可以了。

假设每个点都要被两个棋子到达，则 $ans = 4(n-1)$ ；

对于每个棋子，每不必达到一个非 $1$ 号结点的点，则对答案贡献为 $-2$ 。

时间复杂度：$O(n)$ 。

[代码](https://codeforces.com/contest/1774/submission/185683299)

---

## 作者：wind_seeker (赞：4)

~~写写题解也是有必要的。~~

## 正文

### 性质

还是一样，拿到题目先推性质，在这道题中，即为**最优**操作的性质。

各种模拟手推，观察之后，我们发现:

- 每条必须经过的边**最多**经过**往返两次**。
- 如果一个棋子到达深度为 $k$，则此时，另一枚棋子**至少**到达深度为 $k-d$。

好，我们小小的证明一下...

~~好了，相信大家一顿脑补过后已然证明出来了。~~

对于第二点，显然，难的是第一点。

一条边需要经过，一定是因为深度在这条边之下有必经点，由于在下面阐述的两类必经点都产生后，两个点共同行动和每个点单独行动距离变为一样了，我们可以保证单独行动时最多往返两次，也就意味着共同行动时可以保证最多往返两次。


### 操作

得到了性质以后，我们即需要推理具体的操作。

我们知道每条必须经过的边只会往返两次，所以我们只需知道那些点是必须要经过的:

- 题目中已给的目标点为第一类。
- 还有一类为另一枚棋子达到目标点时距离他深度为 $d$ 的祖先。

接下来求出即可。

### 实现

倍增求深度为 $d$ 的祖先。

深搜一遍，只要子树中有目标点，自己必然会被经过。

### code
```cpp
/* let life be like summer flowers	*/
/* by wind_seeker					*/
/* 2023-01-13 10:27					*/
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+1e3;

inline int read(){
	int res=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) res=(res<<3)+(res<<1)+(c^48);
	return res*f;
}

int n,d,ma,mb,ansa,ansb;
bool flag_a[N],flag_b[N];
struct EDGE{
	int to,nxt;
	EDGE(){}
	EDGE(int _to,int _nxt){
		to=_to,nxt=_nxt;
	}
}e[N<<2];
int tot=1,head[N];

void add(int u,int v){
	e[++tot]=(EDGE){v,head[u]};
	head[u]=tot;
}

int fat[N][23];
void dfs(int u,int fa){
	fat[u][0]=fa;
	for(int i=1;i<=22;i++) fat[u][i]=fat[fat[u][i-1]][i-1]; 
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
 		dfs(v,u);
	}
}
int fa_d[N];
void find_fa(int u){
	int k=d,i=u;
	while(k!=0){
		u=fat[u][__lg(k)];
		k-=(1<<__lg(k));
	}
	fa_d[i]=u;
}

void dfs_ab(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fat[u][0]) continue;
		dfs_ab(v);
		flag_a[u]|=flag_a[v];
		flag_b[u]|=flag_b[v];
	}
	if(flag_a[u]) ansa++;
	if(flag_b[u]) ansb++;
}

int main(){
	n=read(),d=read();
	for(int i=1,u,v;i<n;i++)
		u=read(),v=read(),add(u,v),add(v,u);
	dfs(1,0);
	for(int i=1;i<=n;i++) find_fa(i);
	/*for(int i=1;i<=n;i++)
		printf("u:%d fa_d:%d\n",i,fa_d[i]);*/
	ma=read();
	for(int i=1;i<=ma;i++){
		int x=read();
		flag_a[x]=1,flag_b[fa_d[x]]=1;
	}
	mb=read();
	for(int i=1;i<=mb;i++){
		int x=read();
		flag_b[x]=1,flag_a[fa_d[x]]=1;
	}
	/*puts("a:");
	for(int i=1;i<=n;i++){
		if(flag_a[i]) cout<<i<<" ";
	}puts("");
	puts("b:");
	for(int i=1;i<=n;i++){
		if(flag_b[i]) cout<<i<<" ";
	}puts("");*/
	dfs_ab(1);
	printf("%d\n",(ansa+ansb-2)*2);
	return 0;
}
/*
4 2
1 2
1 3
2 4
1 3
1 4
*/
/*
4
*/
/*
4 2
1 2
2 3
3 4
4 1 2 3 4
1 1
*/
/*
5
*/

```

---

## 作者：MSqwq (赞：4)

考场沉迷于插 B 去了，看了 E 没写，血亏。。。  
首先考虑哪些点一定要去，我们假设讨论 A 棋子。那么显然的，题目直接给的那个序列里的点肯定必须去，这个是毫无疑问的。然后就是考虑 $d$ 的限制，你会发现这个 $d$ 限制的是另一个棋子，比如 A 棋子要到很下面一个点，那么你 B 棋子也要到很下面去，那么你发现其实就是 A 现在这个点往上面数 $d$ 个的那个点是 B 必须要去的。    
还有一个很重要的性质，比如你 A 要去一个点 $p$，那么 A 不可能飞过去吧，那么 A 就必须经过 $1$ 到 $p$ 这条链上的所有的点。    
好了你讨论了哪些点是必须要去的，要算这个很简单，就回溯的时候更新一下就好了。   
那么这时你知道 A 要到的所有点， B 要到的所有点。画个图，你就发现，其实对于每个棋子的路径图就是由根节点向外面延伸，那么假设你要去 $sum$ 个点，那么就是你要进过 $sum-1$ 条边，算上往返就是 $2\times(sum-1)$。  
那么两个棋子的总答案就是 $2\times(sum_a-1+sum_b-1)$。  
代码其实很简单：  
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=998244353;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}
const int N=2e5+10;
int d,ans1,ans2;
bool va[N],vb[N];
bool fa[N],fb[N];
vector<int>v[N];
int path[N],now;
void dfs(int x,int fat)
{
	path[++now]=x;
	for(auto to:v[x])
	{
		if(to==fat)continue;
		dfs(to,x);
		if(fa[to])fa[x]=1;
		if(fb[to])fb[x]=1;
	}
	int upd;
	if(now-d<=0)upd=1;
	else upd=path[now-d];
	now--;
	if(va[x])vb[upd]=1,fa[x]=1;
	if(vb[x])va[upd]=1,fb[x]=1;
	if(fa[x])ans1++;
	if(fb[x])ans2++;
}
int main()
{
	int n=read();d=read();
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		v[x].push_back(y),v[y].push_back(x);
	}
	int k1=read();for(int i=1;i<=k1;i++)va[read()]=1;
	int k2=read();for(int i=1;i<=k2;i++)vb[read()]=1;
	dfs(1,0);
	printf("%d\n",2*(ans1-1+ans2-1));
	return 0;
}

```


---

## 作者：Alex_Wei (赞：4)

如果第一颗棋子要经过 $i$，相当于第二颗棋子要经过 $i$ 的 $d$ 级祖先。用 DP 实现该过程，设 $d_i$ 表示 $i$ 子树内距离 $i$ 最远的第二颗棋子必须经过的位置与 $i$ 的距离，对于第二颗棋子的 $d$ 级祖先也是类似。答案即第一颗棋子必须经过的位置的虚树大小的两倍，加上第二颗棋子必须经过的位置的虚树大小的两倍。

时间复杂度 $\mathcal{O}(n)$，[代码](https://codeforces.com/contest/1774/submission/185659777)。

---

## 作者：baiABC (赞：4)

大力 dp 做法。

首先用 $dep_u$ 表示结点深度（根节点为 $0$），$tp_u$ 表示要经过 $u$ 结点的集合（$\varnothing$，$\{1\}$，$\{2\}$ 或 $\{1,2\}$），$a_u$ 表示以 $u$ 为根的子树中满足 $tp_v\not= \varnothing$ 的结点最大深度，$hv_u$ 表示经过 $u$ 子树结点的棋子集合，$g_u$ 表示只移动一个结点遍历子树中需经过结点且回到 $u$ 的答案（如果有可能的话）（第一步是根节点），$b_u$ 表示 $u$ 子树的答案（开始走根节点不算一步）。

$tp$ 是输入的，$dep$ 和 $hv$ 和 $a$ 的转移就不说了，$b$ 和 $g$ 的转移具体见代码。

需要注意的是只有有定义的 $g$ 才会被使用，所以只要保证这部分 $g$ 转移正确，其他的 $g$ 赋成什么值都没有关系。

### Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
vector <int> G[200010];
int n, d, dep[200010], tp[200010], hv[200010];
long long g[200010], a[200010], b[200010];
void dfs1(int u, int f)
{
   if(tp[u]) a[u] = dep[u];
   hv[u] = tp[u];
   for(auto it : G[u])
      if(it != f)
      {
         dep[it] = dep[u]+1;
         dfs1(it, u);
         a[u] = max(a[u], a[it]);
         hv[u] |= hv[it]; // 类似于状压
      }
}
void dfs2(int u, int f)
{
   g[u] = 1;
   for(auto it : G[u]) if(it != f)
   {
      dfs2(it, u);
      if(!hv[it]) continue;
      if(hv[it] == 3 || a[it]-dep[u] > d) b[u] += 4+b[it];
      else b[u] += g[it]+1, g[u] += g[it]+1;
   }
}
int main()
{
   ios::sync_with_stdio(0);
   cin >> n >> d;
   for(int i = 1; i < n; ++i)
   {
      int u, v; cin >> u >> v;
      G[u].push_back(v);
      G[v].push_back(u);
   }
   int m1, m2;
   cin >> m1;
   for(int i = 0; i < m1; ++i){int x; cin >> x; tp[x] |= 1;}
   cin >> m2;
   for(int i = 0; i < m2; ++i){int x; cin >> x; tp[x] |= 2;}
   dfs1(1, 0); dfs2(1, 0);
   cout << b[1] << '\n';
   return 0;
}
```

---

## 作者：WaterSun (赞：3)

[更好的阅读体验](https://watersun.top/[%E9%A2%98%E8%A7%A3]CF1774E%20Two%20Chess%20Pieces/)

# 思路

正难则反，假设每一个棋子都要走过每一个点，所需的步数显然是 $4(n - 1)$。然后考虑对于每一个棋子那些点是必走的。

1. 如果 $x$ 子树内有这个棋子需要到达的点，则 $x$ 必走。

2. 对于另一个棋子在 $x$ 子树内必走过的深度最深的点的深度记作 $md$，如果 $md - d_x > D - 1$，则 $x$ 必走。

因此，排除掉上述点，其它点都是不用经过的，每一个点将为答案减 $2$ 的贡献。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2e5 + 10,M = 4e5 + 10;
int n,k,m[2],ans;
int d[N],md[2][N];
int idx,h[N],ne[M],e[M];
bool st[2][N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void add(int a,int b){
    ne[idx] = h[a];
    e[idx] = b;
    h[a] = idx++;
}

inline void dfs(int u,int fa){
    d[u] = d[fa] + 1;
    if (st[0][u]) md[0][u] = d[u];
    if (st[1][u]) md[1][u] = d[u];
    for (re int i = h[u];~i;i = ne[i]){
        int j = e[i];
        if (j == fa) continue;
        dfs(j,u);
        md[0][u] = max(md[0][u],md[0][j]),md[1][u] = max(md[1][u],md[1][j]);
    }
    if (!md[0][u] && md[1][u] - d[u] < k) ans -= 2;
    if (!md[1][u] && md[0][u] - d[u] < k) ans -= 2;
}

int main(){
    memset(h,-1,sizeof(h));
    n = read(),k = read();
    ans = 4 * (n - 1);
    for (re int i = 1;i < n;i++){
        int a,b;
        a = read(),b = read();
        add(a,b),add(b,a);
    }
    for (re int ty = 0;ty <= 1;ty++){
        m[ty] = read();
        for (re int i = 1;i <= m[ty];i++){
            int x;
            x = read();
            st[ty][x] = true;
        }
    }
    dfs(1,0);
    printf("%d",ans);
    return 0;
}
```

---

## 作者：ningago (赞：3)

一个点可能是 $A$ 关键点，$B$ 关键点，也可能两个都是，但这不重要，因为两个棋子是分开走的。

相同地，一条边可能是 $A$ 关键边，$B$ 关键边，也可能都是，表示这个边 $A$ 或 $B$ 必须走。

一个容易证明的性质是一条边至多被两个棋子各经过两次（来回）。

如果一个点是 $A$ 关键点，那么这个点到根的路径上的边都是 $A$ 关键边。

因为两个棋子的距离不能超过 $d$，则这个点的 $d$ 级祖先到根的路径上的边都是 $B$ 关键边。

相同的，如果一个点是 $B$ 关键点，那么这个点到根的路径上的边都是 $B$ 关键边，这个点的 $d$ 级祖先到根的路径上的边都是 $A$ 关键边。

答案就是 $(A \text{关键边个数} + B \text{关键边个数})\times 2$。(来回经过两次)

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

#define N 200010

int n,m;
int h[N],e[N << 1],ne[N << 1],idx;

void add_edge(int x,int y)
{
	ne[++idx] = h[x];
	h[x] = idx;
	e[idx] = y;
}

void add(int x,int y)
{
	add_edge(x,y);
	add_edge(y,x);
}

int a[N][2];
int edge_val[N][2];
int ans;

int dfs1(int k,int f,int id)
{
	int res = a[k][id];
	for(int i = h[k];~i;i = ne[i])
	{
		int nx = e[i];
		if(nx == f)
			continue;
		res |= dfs1(nx,k,id);
	}
	edge_val[k][id] = res;
	return res;
}

int dfs2(int k,int f,int id)
{
	int res;
	if(a[k][id])
		res = m;
	else
		res = 0x3f3f3f3f;
	for(int i = h[k];~i;i = ne[i])
	{
		int nx = e[i];
		if(nx == f)
			continue;
		int t = dfs2(nx,k,id);
		res = std::min(res,t - 1);
	}
	if(res <= 0)
		edge_val[k][id ^ 1] = 1;
	return res;
}

void dfs3(int k,int f)
{
	if(k != 1)
		ans += (edge_val[k][0] + edge_val[k][1]) * 2;
	for(int i = h[k];~i;i = ne[i])
	{
		int nx = e[i];
		if(nx == f)
			continue;
		dfs3(nx,k);
	}
}

int main()
{
	memset(h,-1,sizeof(h));
	scanf("%d%d",&n,&m);
	for(int i = 1,x,y;i < n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	int t;
	scanf("%d",&t);
	for(int i = 1,x;i <= t;i++)
	{
		scanf("%d",&x);
		a[x][0] = 1;
	}
	scanf("%d",&t);
	for(int i = 1,x;i <= t;i++)
	{
		scanf("%d",&x);
		a[x][1] = 1;
	}
	dfs1(1,0,0);
	dfs1(1,0,1);
	dfs2(1,0,0);
	dfs2(1,0,1);
	dfs3(1,0);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Cxny (赞：2)

贪心。

先考虑如果没有 $d$ 的限制怎么做。对于 $u$ 的子树 $v$，若子树内部没有棋子 $1$ 必须经过的点，那么棋子 $1$ 必然不会进入子树 $v$。棋子 $2$ 同理。

对于 $d$ 的限制，继续讨论 $u$ 的子树 $v$。

- 两颗棋子都需要经过 $v$ 子树内：直接进，与没有限制相同。
- 只有某一颗棋子需要经过 $v$ 子树：另一颗棋子最好不进入，除非进入 $v$ 后距离超过 $d$ 才向下走 $1$ 步。

维护两颗棋子所在位置以及当前链即可。注意细节。

```cpp
const int maxn = 2e5 + 10;
int n, m, val[maxn], dep[maxn];
vector<int> edge[maxn];
int pos0, pos1, cur0, cur1;
ll ans = 0;
void dfs(int u, int f){
    dep[u] = dep[f] + 1;
    for(int v : edge[u]) if(v != f) dfs(v, u), val[u] |= val[v];
}
vector<int> ch;
void solve(int u, int f){
    int pre0 = pos0, pre1 = pos1, qwq0 = cur0, qwq1 = cur1;
    // fprintf(stderr, "%d: %d %d\n", u, pos0, pos1);
    for(int v : edge[u]) if(v != f && val[v]){
        ch.pb(v);
        if(val[v] == 3){
            ans += (dep[v] * 2 - dep[pos0] - dep[pos1]);
            pos0 = pos1 = v, cur0 = cur1 = ch.size() - 1;
        }else if(val[v] == 1){
            ans += (dep[v] - dep[pos0]), pos0 = v, cur0 = ch.size() - 1;
            if(dep[pos0] - dep[pos1] > m) ans++, pos1 = ch[++cur1];
        }else if(val[v] == 2){
            ans += (dep[v] - dep[pos1]), pos1 = v, cur1 = ch.size() - 1;
            if(dep[pos1] - dep[pos0] > m) ans++, pos0 = ch[++cur0];
        }
        solve(v, u);
        ch.ppb();
        if(dep[pos0] > dep[u]) ans += dep[pos0] - dep[u], pos0 = u, cur0 = ch.size() - 1;
        if(dep[pos1] > dep[u]) ans += dep[pos1] - dep[u], pos1 = u, cur1 = ch.size() - 1;
    }
}
signed main(){
    scanf("%d%d", &n, &m);
    for(int i = 1, x, y; i < n; i++){
        scanf("%d%d", &x, &y);
        edge[x].pb(y), edge[y].pb(x);
    }
    int x0, x1; scanf("%d", &x0);
    for(int i = 1, x; i <= x0; i++) scanf("%d", &x), val[x] |= 1;
    scanf("%d", &x1);
    for(int i = 1, x; i <= x1; i++) scanf("%d", &x), val[x] |= 2;
    dfs(1, 0);
    ch.pb(1), pos0 = pos1 = 1;
    solve(1, 0);
    printf("%lld\n", ans);
    return 0;
}
```

---

