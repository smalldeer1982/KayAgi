# [USACO18DEC] The Cow Gathering P

## 题目描述

奶牛们从世界各地聚集起来参加一场大型聚会。总共有 $ N $ 头奶牛， $ N-1 $ 对奶牛互为朋友。每头奶牛都可以通过一些朋友关系认识其他每头奶牛。

她们玩得很开心，但是现在到了她们应当离开的时间了，她们会一个接一个地离开。她们想要以某种顺序离开，使得只要至少还有两头奶牛尚未离开，所有尚未离开的奶牛都还有没有离开的朋友。此外，由于行李寄存的因素，有 $ M $ 对奶牛 $ (a_i,b_i) $ 必须满足奶牛 $ a_i $ 要比奶牛 $ b_i $ 先离开。注意奶牛 $ a_i $ 和奶牛 $ b_i $ 可能是朋友，也可能不是朋友。

帮助奶牛们求出，对于每一头奶牛，她是否可以成为最后一头离开的奶牛。可能会发生不存在满足上述要求的奶牛离开顺序的情况。

## 样例 #1

### 输入

```
5 1
1 2
2 3
3 4
4 5
2 4
```

### 输出

```
0
0
1
1
1
```

# 题解

## 作者：Bartholomew (赞：20)



### 简化题意

简化为给定一棵大小为$n$的树, 有$m$个限制

-  限制$(u,v)$ 表示$u$必须在$v$前删除

问每次删除一个叶子节点, 可能最后留下的点的集合

### 分析

~~nice problem~~

不难发现: 如果没有限制, 那么所有的点都可行...

首先, 我们可以**贪心**先找出一个**可行点**, 解决方法如下

> 每次寻找一个没有限制条件的叶子节点删去
> 重复上述操作, 最后的节点即为可行答案之一
> 若不成功, 则视为无解

**Prove**

-  如果本身数据无解, 那么自然上述方法找不到一个合法的删点序列

-  同样的, 如果不存在一个合法的删点序列, 那么必定意味着存在一个连续的子树: 子树中的任意一个点都被其他点的约束限制着, 类似于形成了环. 那么就不会存在任意一个序列可以打破这种局面了.

于是证明了该方法是可以找出合法点以及判断无解的!

### sol

先提供一个$O(n^2)$的做法: 

-  每次判断一个点是否可行, 只要将它提为root,并将所有边记为子节点指向父节点
-  若不存在**环**便是可行点, 否则非法!

那么会发现一个trick:

-  若存在限制$(u,v)$那么以$v$为根的$u$的子树(包括$u$)都不可行



~~这样就可以搞事情了~~

我们既然已经找出了一个可行解(记为$rt$)

- 以$rt$为根可以发现任意一个限制(a,b)中, a的子树一定是不可行的(证明略)

- 那么标记完不可行点之后剩下的点都是可行的!

  **Prove**
  **利用数学归纳: 只要证明与一个可行点相邻的且未被标记过的点同样合法即可!**

  设该可行点为$s$, 转为root, 那么$t$为其子节点
  如果关于$s$的合法删除序列为$\{a_n\}$   s.t. $a_n=s,a_x=t$ ($x\in Z$)
  那么我们直接将$a_x$提至序列的$a_n$之后, 该序列同样合法
> 因为没有$t$必须在某一点前删除的限制, 否则$t$已经在之前被标记为非法!
>
> 且t的子树可以按序删除(不然$s$不会为合法点),以及$s$的非t子树部分同样可以删除,依旧不会被$t$所干扰

**那么可以发现所有的可行解必定都是一起的**, 一遍dfs即可...

复杂度: O(n)

### Code

```C++
// Made by Bar.
#include <bits/stdc++.h>
using namespace std;

namespace {
	template <typename T> inline void read(T &x) {
		x = 0; T f = 1; char c = getchar();
		for(; !isdigit(c); c = getchar())
			if(c == '-') f = -1;
		for(;  isdigit(c); c = getchar())
			x = (x << 3) + (x << 1) + (c ^ 48);
		x *= f;
	}
}

const int N = 1E5 + 50;

int n, m, rt, d[N], vis[N], ans[N];
vector<int> g[N], l[N];
queue<int> que;

int cnt;
int solve(int cnt = 0) {
	for(; !que.empty(); ) {
		int u = que.front(); que.pop();
		++ cnt;
		if(d[u] != 1) {
			if(d[u] < 1) return u;
			for(int i = 1; i <= n; ++i) printf("0\n");
			exit(0);
		} 
		for(auto v : g[u]) {
			-- d[v]; ++ cnt;
			if(d[v] == 1) que.push(v);
		}
		for(auto v : l[u]) {
			-- d[v]; ++ cnt;
			if(d[v] == 1) que.push(v);
		}
	}
	if(cnt != n) {
		for(int i = 1; i <= n; ++i) printf("0\n"); 
		exit(0);
	}
}
void dfs(int u, int fa = -1) {
	ans[u] = 1;
	for(auto v : g[u]) 
		if(v != fa && !vis[v]) 
			dfs(v, u);
}
int main() {
	read(n), read(m);
	for(int u, v, i = 1; i < n; ++i) {
		read(u), read(v);
		g[u].push_back(v), g[v].push_back(u); 
		++ d[u], ++ d[v];
	}
	for(int a, b, i = 1; i <= m; ++i) {
		read(a), read(b);
		l[a].push_back(b);
		++ d[b];
		vis[a] = true;
	}
	for(int i = 1; i <= n; ++i) 
		if(d[i] == 1) que.push(i);
	rt = solve();
	dfs(rt);
	for(int i = 1; i <= n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
```


---

## 作者：Owen_codeisking (赞：6)

终于 $A$ 了。

这是一道思维好题！我提供一个无解的数据：

```cpp
8 2
1 2
2 3
1 4
4 5
4 6
6 7
6 8
2 8
4 3
```

![](https://cdn.luogu.com.cn/upload/pic/50658.png)

我们先考虑只有一组询问怎么做。

我们定义 $x$ 比 $y$ 先删除。

1、若 $y$ 在 $x$ 子树内

那么我们可以树上倍增到 $y$ 所属的 $x$ 的子节点 $z$，那么 $[1,st_z)$ 和 $(ed_z,n]$ 中的点答案一定为 $0$

2、其他情况

我们把 $x$ 子树全部删除即可，$[st_x,ed_x]$ 中的点答案一定为 $0$

此题难在判断无解的情况。

如果 $x$ 比 $y$ 先删除，我们新建一个图，将 $x$ 向 $y$ 连一条边。实际上无解的情况就是拓扑后无解的情况。

那为什么无解的情况单独判掉就答案成立呢？

因为无解的情况判掉后，我们在删除点的时候没有其他限制，各组询问是没有冲突的。

此题就做完了，时间复杂度 $O(n\log n)$，瓶颈在树上倍增。

@123asdfghjkl 感谢他发现了我判无解一个错误，我们在判的时候有可能出现度数为负数的情况，所以原来的 `dg[x]==1` 改成 `dg[x]<2` 就行了。

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int maxn=100000+10;
int n,m,c[maxn],dg[maxn],vis[maxn],ans[maxn];
int dep[maxn],fa[maxn][18],st[maxn],ed[maxn],mp[maxn],tim;
int head[maxn],fir[maxn],tot,cnt,now;

struct node{
    int to,next;
}e[maxn<<1],edge[maxn];

inline int read(){
    register int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return (f==1)?x:-x;
}

inline void add(int x,int y){
    e[++tot].to=y;e[tot].next=head[x];head[x]=tot;
}

inline void addedge(int x,int y){
    edge[++cnt].to=y;edge[cnt].next=fir[x];fir[x]=cnt;
}

void dfs(int x,int f){
    st[x]=++tim;mp[tim]=x;
    fa[x][0]=f;dep[x]=dep[f]+1;
    for(int i=1;i<18;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int i=head[x],y;i;i=e[i].next){
        y=e[i].to;
        if(y==f) continue;
        dfs(y,x);
    }
    ed[x]=tim;
}

inline int getson(int x,int y){
    for(int i=17;i>=0;i--)
        if(dep[fa[y][i]]>dep[x]) y=fa[y][i];
    return y; 
}

inline bool check(){
	queue<int> q;
    for(int i=1;i<=n;i++)
        if(dg[i]<2) vis[i]=1,q.push(i);
    int x,y;
    while(!q.empty()){
        x=q.front(),q.pop();
        for(int i=head[x];i;i=e[i].next){
            y=e[i].to;dg[y]--; 
            if(!vis[y]&&dg[y]<2) vis[y]=1,q.push(y);
        }
        for(int i=fir[x];i;i=edge[i].next){
            y=edge[i].to;dg[y]--;
            if(!vis[y]&&dg[y]<2) vis[y]=1,q.push(y);
        }
    }
    for(int i=1;i<=n;i++)
    	if(!vis[i]) return 0;
    return 1;
}

int main()
{
    n=read(),m=read();
    int x,y,z;
    for(int i=1;i<n;i++){
        x=read(),y=read();
        add(x,y);add(y,x);
        dg[x]++;dg[y]++;
    }
    dfs(1,0);
    while(m--){
        x=read(),y=read();
        addedge(x,y);dg[y]++;
        if(st[x]<=st[y]&&st[y]<=ed[x]){
            z=getson(x,y);
            c[1]++;c[st[z]]--;
            c[ed[z]+1]++;c[n+1]--;
        }
        else {
            c[st[x]]++;c[ed[x]+1]--;
        }
    }
    if(!check()){
        for(int i=1;i<=n;i++) printf("0\n");
        return 0;
    }
    for(int i=1;i<=n;i++){
        c[i]+=c[i-1];
        if(c[i]==0) ans[mp[i]]=1;
    }
    for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
    return 0;
}
```



---

## 作者：hongzy (赞：6)

### USACO 2018 DEC Platinum The Cow Gathering

**题意**：给定树和一些树上有向边，每次删去叶子，询问每个结点能否最后一个删去

**题解**：

判断一个点能否最后一个删，就把它提做根，然后把所有儿子都往上指

加入一条边 $(u,v)$ 可以发现以$v$为根时$u$的子树都没法最后删

根据这个性质，每次加边钦定一些点答案就是$0$

怎样快速找到$u$在以$v$为根的树中的子树？用类似「遥远的国度」那题的方法，直接以$1$号点为根建树，然后这时换根只需要分类讨论一下：如果$v$在$u$子树外，不用动；如果v在子树内，那找到$v$在$u$的哪个儿子的子树里，除了这个子树其他所有结点钦定答案为$0$。具体实现就找倍增找$v$的$deep[v]-deep[u]-1$级祖先（因为如果暴力遍历儿子，复杂度不对），覆盖就dfs序差分一下

其实此时的做法还是有一些问题的，USACO比赛时很多选手就这样写的，但后来出题人中途加数据把他们叉掉了

因此需要判下图是否无解

我们把已经确定答案为$0$的结点确定边的方向，然后加上树上有向边判环。

```cpp
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int N = 1e5 + 10;

int n, m, dfn[N], idx[N], sz[N];
int fa[N][20], d[N];
vector<int> G[N], g[N];
bool ans[N];

void dfs(int u, int f = 0) {
	fa[u][0] = f; d[u] = d[f] + 1;
	for(int i = 1; i < 20; i ++)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	dfn[u] = ++ dfn[0]; idx[dfn[u]] = u; sz[u] = 1;
	for(int i = 0; i < G[u].size(); i ++) if(G[u][i] != f)
		dfs(G[u][i], u), sz[u] += sz[G[u][i]];
}

int c[N];

inline void cover(int l, int r) {
	if(l <= r) c[l] ++, c[r + 1] --;
}

void kthfa(int & u, int k) {
	if(k > 0) for(int i = 0; i < 20; i ++) 
		if(k >> i & 1) u = fa[u][i];
}

bool vis[N];
void fixdir(int u, int f) {
	for(int & v : G[u]) if(v != f) {
		if(!vis[v]) {
			g[v].push_back(u);
			vis[v] = 1; fixdir(v, u);
		}
	}
}

bool vis2[N], ins[N];
bool cir(int u) {
	if(ins[u]) return 1;
	if(vis2[u]) return 0;
	vis2[u] = ins[u] = 1;
	for(const int & v : g[u]) 
		if(cir(v)) return 1;
	return ins[u] = 0;
}

int main() {
	scanf("%d%d", &n, &m);
	int u, v;
	for(int i = 1; i < n; i ++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	for(int i = 1; i <= m; i ++) {
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		int l = dfn[u], r = l + sz[u] - 1;
		if(dfn[v] < l || dfn[v] > r) {
			cover(l, r), fixdir(u, fa[u][0]);
		} else {
			kthfa(v, d[v] - d[u] - 1);
			int l2 = dfn[v], r2 = l2 + sz[v] - 1;
			cover(1, l2 - 1), cover(r2 + 1, n);
			for(const int & j : G[v]) if(!vis[j]) {
				if(dfn[j] < l2 || dfn[j] > r2) {
					vis[j] = 1;
					fixdir(j, v);
				}
			}
		}
	}
	bool tag = true;
	for(int i = 1; i <= n; i ++) if(!vis2[i])
		if(cir(i)) tag = false, i = n;

	if(!tag) {
		for(int i = 1; i <= n; i ++) puts("0");
		return 0;
	}
	
	int val = 0;
	for(int i = 1; i <= n; i ++)
		val += c[i], ans[idx[i]] = (val > 0) ? 0 : 1;
	for(int i = 1; i <= n; i ++)
		printf("%d\n", ans[i]);
	return 0;
}
```



---

## 作者：zyy121212 (赞：2)

让我们先整理一下：已知一个数图，求一个点是否可以最后删除。


既然是求顺序，当然优先想到的是dfs序：
``` cpp
int st[100010],ed[100010],mp[100010],tim=0;
  //开始时间   结束时间   dfs顺序  时间标记
void dfs(int x,int f){
     //现点   父点
   st[x]=++tim,mp[tim]=x;
   for(int i=head[x];i;i=a[i].next){//遍历
       int y=a[i].to;
       if(y==f)continue;
       dfs(y,x);
   }
   ed[x]=tim;
}
```

下面还要解决m个条件，既然要求一个点是否可以最后删除，就要用排除法，每个条件都可以排除一段子树，而在dfs中处理子树用差分（数组为c[])就可以了。
而条件又两种可能：

1. 子孙指向祖先：排除子孙及下面的点：
```
c[st[x]]++;c[ed[x]+1]--;
```

2. 祖先指向子孙：排除祖先及上面的点并排除分支：排除分支时要求出子节点，用LCA就可以了。

```
if(st[x]<=st[y]&&st[y]<=ed[x]){//判断祖先是否指向子孙
   z=LCA(x,y);
   c[1]++;c[st[z]]--;
   c[ed[z]+1]++;c[n+1]--;
}
```
LCA：

```
int LCA(int x,int y){//求子节点
    for(int i=17;i>=0;i--)
    if(dep[fa[y][i]]>dep[x]) y=fa[y][i];
    return y;
}
```
这时还要改一下dfs:

```
void dfs(int x,int f){
   st[x]=++tim,mp[tim]=x;
	fa[x][0]=f;dep[x]=dep[f]+1;
   for(int i=1;i<18;i++)fa[x][i]=fa[fa[x][i-1]][i-1];//预处理LCA并求出深度
   for(int i=head[x];i;i=a[i].next){
       int y=a[i].to;
       if(y==f)continue;
       dfs(y,x);
   }
   ed[x]=tim;
}
```

以及判断条件是否有环以求无解：

```
int vis[100010];//标记
bool qwe(){
    queue<int> q;
    for(int i=1;i<=n;i++)
        if(dg[i]<2) vis[i]=1,q.push(i);
    int x,y;
    while(!q.empty()){//广搜
        x=q.front(),q.pop();
        for(int i=head[x];i;i=a[i].next){
            y=a[i].to;dg[y]--;
            if(!vis[y]&&dg[y]<2) vis[y]=1,q.push(y);
        }
        for(int i=fir[x];i;i=edge[i].next){
            y=edge[i].to;dg[y]--;
            if(!vis[y]&&dg[y]<2) vis[y]=1,q.push(y);
        }
    }
    for(int i=1;i<=n;i++)//判断
        if(!vis[i]) return 0;
    return 1;
}
```
最后连起来：

```
#include <bits/stdc++.h>
using namespace std;
int n,m,c[100010],ans[100010];
int st[100010],ed[100010],mp[100010],tim=0,dg[100010],vis[100010];
int dep[100010],fa[100010][18];
int head[100010],fir[100010],tot,cnt,now;
struct node{
    int to,next;
}a[200020],edge[100010];
void add(int x,int y){
    a[++tot].to=y;a[tot].next=head[x];head[x]=tot;
}
void addedge(int x,int y){
    edge[++cnt].to=y;edge[cnt].next=fir[x];fir[x]=cnt;
}
void dfs(int x,int f){
    st[x]=++tim;mp[tim]=x;
    fa[x][0]=f;dep[x]=dep[f]+1;
    for(int i=1;i<18;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int i=head[x],y;i;i=a[i].next){
        y=a[i].to;
        if(y==f) continue;
        dfs(y,x);
    }
    ed[x]=tim;
}
int getson(int x,int y){
    for(int i=17;i>=0;i--)
        if(dep[fa[y][i]]>dep[x]) y=fa[y][i];
    return y;
}
 bool qwe(){
    queue<int> q;
    for(int i=1;i<=n;i++)if(dg[i]<2)vis[i]=1,q.push(i);
    int x,y;
    while(!q.empty()){
        x=q.front(),q.pop();
        for(int i=head[x];i;i=a[i].next){
            y=a[i].to;dg[y]--;
            if(!vis[y]&&dg[y]<2) vis[y]=1,q.push(y);
        }
        for(int i=fir[x];i;i=edge[i].next){
            y=edge[i].to;dg[y]--;
            if(!vis[y]&&dg[y]<2) vis[y]=1,q.push(y);
        }
    }
    for(int i=1;i<=n;i++)if(!vis[i])return 0;
    return 1;
}
int main(）
{
    cin>>n>>m;
    int x,y,z;
    for(int i=1;i<n;i++){
        cin>>x>>y;
        add(x,y);add(y,x);
        dg[x]++;dg[y]++;
    }
    dfs(1,0);
    while(m--){
        cin>>x>>y;
        addedge(x,y);dg[y]++;
        if(st[x]<=st[y]&&st[y]<=ed[x]){
            z=getson(x,y);
            c[1]++;c[st[z]]--;
            c[ed[z]+1]++;c[n+1]--;
        }
        else {
            c[st[x]]++;c[ed[x]+1]--;
        }
    }
    if(qwe()==0){
        for(int i=1;i<=n;i++)cout<<0
        return 0;
    }
    for(int i=1;i<=n;i++){
        c[i]+=c[i-1];
        if(c[i]==0) ans[mp[i]]=1;
    }
    for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
}


```













---

## 作者：kkxacj (赞：1)

[博客园阅读の传送门](https://www.cnblogs.com/kkxacj/p/18719625)

挺有趣的一道题。

#### 思路

先不考虑那 $m$ 条限制来看一下这道题，容易发现，如果 $n$ 个点构成的不是一颗树，则一定是不合法的，因为无论你怎么选择最终每个连通块至少剩下一个点无法离开。

那么剩下的只有 $n$ 个点构成一颗树的情况，容易发现，每次离开的人一定是度数为 $1$ 的点，否则它离开后会使得连通块大于一个，**也就是说必须保证操作时连通块不会变多**。

接下来考虑一下限制，先假设只有一条限制，我们默认以一为跟，若 $x$ 比 $y$ 先离开且为 $y$ 的祖先，则一定不会是最后一个的点如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/4rm9pjzk.png)

否则就是 $x$ 的子树。

对于多个限制，可能会存在相互约束导致无解情况，我们可以这样做：

刚开始的 $n-1$ 条边视为两条有向边，然后把 $m$ 个限制变成有向边，然后每次选择一个入度为一的点，然后删除它连出去的边，如此操作，若最终所有点都被删除，则一定不是全部无解。

不是全部无解的话，这 $m$ 个限制相当于互相独立，就对每个操作看一下，最后树上差分即可。

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
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
const int N = 1e5+10;
int v[N],n,m,x,y,f[N],lg[N],in[N],dep[N],head[N],head1[N],cnt,cnt1,fa[N][20],sum,ans[N],o;
queue<int>p;
struct w
{
	int to,nxt;
}b[N<<1],c[N<<2];
int find(int x)
{
	if(f[x] == x) return x;
	return f[x] = find(f[x]); 
}
inline void add(int x,int y)
{
	b[++cnt].nxt = head[x];
	b[cnt].to = y;
	head[x] = cnt;
}
inline void add1(int x,int y)
{
	c[++cnt1].nxt = head1[x];
	c[cnt1].to = y;
	head1[x] = cnt1;
}
void dfs(int x,int y)
{
	dep[x] = dep[y]+1,fa[x][0] = y;
	for(int i = 1;i <= lg[dep[x]];i++) fa[x][i] = fa[fa[x][i-1]][i-1];
	for(int i = head[x];i;i = b[i].nxt)
		if(b[i].to != y)
			dfs(b[i].to,x);
}
void dfs1(int x,int y)
{
	ans[x] += ans[y];
	for(int i = head[x];i;i = b[i].nxt)
		if(b[i].to != y)
			dfs1(b[i].to,x);
}
inline int go_up(int x,int y)
{
	for(int i = lg[dep[x]];i >= 0;i--)
		if(((1<<i)&y)) x = fa[x][i];
	return x;
}
inline void bfs()
{
	while(!p.empty())
	{
		x = p.front(); p.pop();
		for(int i = head1[x];i;i = c[i].nxt) 
		{
			in[c[i].to]--;
			if(in[c[i].to] == 1) p.push(c[i].to),o++;
		}
	}
} 
signed main()
{
	read(n),read(m);
	for(int i = 1;i < n;i++) read(x),read(y),add(x,y),add(y,x),add1(x,y),add1(y,x),in[x]++,in[y]++,f[find(x)] = find(y);
	for(int i = 1;i <= n;i++)
		if(find(i) == i) sum++;
	if(sum > 1)//多个联通快一定无解 
	{
		for(int i = 1;i <= n;i++) print(0),pc('\n');
		flush();
		return 0;
	} 
	for(int i = 2;i <= n;i++) lg[i] = lg[i/2]+1;
	cnt= 0,dfs(1,0);
	for(int i = 1;i <= m;i++) 
	{
		read(x),read(y);//x比y先走 
		add1(x,y),in[y]++;
		if(x == y) ans[1]++; //相等显然不合法 
		else if(dep[x] < dep[y] && fa[go_up(y,dep[y]-dep[x]-1)][0] == x) ans[1]++,ans[go_up(y,dep[y]-dep[x]-1)]--;//x为y祖先 
		else ans[x]++;
	}
	for(int i = 1;i <= n;i++)
		if(in[i] == 1) p.push(i),o++;
	bfs();//判是否无解 
	if(o != n)
	{
		for(int i = 1;i <= n;i++) print(0),pc('\n');
		flush();
		return 0;
	}
	dfs1(1,0);
	for(int i = 1;i <= n;i++) print((ans[i] == 0)),pc('\n');
	flush();
	return 0;
}
/*
首先发现原图必须是一颗树，否则一定全部无解 
在没m条限制的时候，先走的一定是叶子节点，然后会有新的叶子节点出现
m条限制通过观察可得，以任意一个点为根，若x比y先选，则以y为根时x为子树不可行
不过多条限制可能会互相约束以达到无解，可以跑拓扑判是否有解 
直接树上差分即可，单log，来自lca 
*/
```

---

## 作者：ABookCD (赞：1)

### P5157 [USACO18DEC] The Cow Gathering P 题解

一种比正解复杂的但是比较好想的做法。

我们先简化一下题意，对于每一个限制对 $(a,b)$，我们令 $b$ 为根结点，那么 $a$ 的子树内的点都无法最后被删去，（因为 $a$ 无法最后被删去，删了 $a$ 就断了）。

我们将这些点与 $b$ 暴力连边，那么出度为 $0$ 的点就可以最后选。

当然，还要判断无解情况：如果这些边构成了一个环，那么本身无论如何都删不完，所以所有点都无解。

因此我们有了 $O(n^2)$ 的暴力做法，可以得到 20 分。

考虑优化，发现换根的过程增大了不必要的时间开销，尝试省掉这个过程。

我们钦定 $1$ 为根结点，那么对于限制对 $(a,b)$，有如下两种情况：

1.  $b$ 在 $a$ 的子树之外。

这种情况下，换成以 $b$ 为根的时候，$a$ 的子树是不变的。

2. $b$ 在 $a$ 的子树之内。

这种情况子树就会变化。

![](https://pic.imgdb.cn/item/654660cfc458853aef2624f6.png)



如这一张图，我们换到 $b$ 为根时，$a$ 的子树包含的点是 $\{a,4,9,5,2,1,3\}$。也就是说，我们要把 $a$ 的子树中 $b$ 所在的子树删掉。如果我们对原树做一个 dfn 序，新的子树会被分成两连续部分。 

考虑寻找 $b$ 所在子树对应的 $a$ 的儿子 $v$，我们相当于要把 $v$ 所在的子树删去。

这个寻找的过程显然可以用树链剖分进行维护，我们从 $b$ 开始暴力跳链，如果 $a$ 和 $b$ 链顶不一样就跳到链顶，如果已经满足 $fa[b]=a$ 就结束，否则上跳到下一条链继续。

若已经跳到在同一个重链上了，那么 $v$ 就是 $son[u]$。



我们对于一段 dfn 连续的区间的出度 $+1$，可以用差分实现，但是还要找到环判断无解，因此还是需要线段树优化建图，跑一个 tarjan 找环。

时间复杂度 $O(n \log n)$。

-------------------

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int f[500010],dep[500010],sz[500010],dfn[500010],son[500010],top[500010],idx;
int oedge[500010];
vector<int> nG[2000010],g[500010];
void dfs(int u,int fa){
	f[u]=fa,dep[u]=dep[fa]+1,sz[u]=1;
	for(auto v:g[u]){
		if(v^fa){
			dfs(v,u);
			son[u]=sz[v]>sz[son[u]]?v:son[u];
			sz[u]+=sz[v];
		}
	}
}
void dfs2(int u,int topnode){
	top[u]=topnode,dfn[u]=++idx;
	if(son[u]) dfs2(son[u],topnode);
	for(auto v:g[u]){
		if((v^son[u])&&(v^f[u])) dfs2(v,v);
	}
}
int dfn_tar[2000010],n_tar,scc,low[2000010],idx_tar,gid[2000010],fid[500010],n,m,ons[2000010];
int st[2000010],top_tar;
void build(int id,int l,int r){
	gid[id]=++n_tar;
	if(l==r){
		fid[l]=gid[id];
		return;
	}
	int mid=(l+r)>>1;
	build(id<<1,l,mid);
	build(id<<1|1,mid+1,r);
	nG[gid[id<<1]].push_back(gid[id]);
	nG[gid[id<<1|1]].push_back(gid[id]);
}
void update(int id,int l,int r,int ql,int qr,int v){
	if(ql<=l&&r<=qr){
		nG[gid[id]].push_back(fid[v]);
		return;
	}
	int mid=(l+r)>>1;
	if(ql<=mid) update(id<<1,l,mid,ql,qr,v);
	if(qr>mid) update(id<<1|1,mid+1,r,ql,qr,v);
}
void tarjan(int u){
	low[u]=dfn_tar[u]=++idx_tar;
	ons[u]=1;
	st[++top_tar]=u;
	for(auto v:nG[u]){
		if(!dfn_tar[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(ons[v]) low[u]=min(low[u],dfn_tar[v]);
	}
	if(low[u]==dfn_tar[u]){
		scc++;
		while(st[top_tar]!=u){
			ons[st[top_tar]]=0;
			top_tar--;
		}
		ons[u]=0;
		top_tar--;
	}
}
int main(){

	n=read(),m=read();
	for(int i=2;i<=n;i++){
		int u=read(),v=read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	dfs2(1,1);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		int vp=v;
		if(dfn[v]<dfn[u]||dfn[v]>dfn[u]+sz[u]-1){
			update(1,1,n,dfn[u],dfn[u]+sz[u]-1,dfn[vp]);
			oedge[dfn[u]]++,oedge[dfn[u]+sz[u]]--;
			continue;
		}
		while(top[v]!=top[u]){
			v=top[v];
			if(f[v]==u) break;
			v=f[v];
		}
		if(f[v]!=u) v=son[u];
		if(dfn[v]>=2){
			update(1,1,n,1,dfn[v]-1,dfn[vp]);
			oedge[1]++,oedge[dfn[v]]--;
		}
		if(dfn[v]+sz[v]<=n){
			update(1,1,n,dfn[v]+sz[v],n,dfn[vp]);
			oedge[dfn[v]+sz[v]]++;
		}
	}
	for(int i=1;i<=n_tar;i++){
		if(!dfn_tar[i]) tarjan(i);
	}
	if(scc!=n_tar){
		for(int i=1;i<=n;i++) printf("0\n");
		return 0;
	} 
	for(int i=2;i<=n;i++){
		oedge[i]+=oedge[i-1];
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",oedge[dfn[i]]==0);
	}
	return 0;
}
```



---

## 作者：一只绝帆 (赞：1)

> 给定一棵树和若干限制，限制形如 $x_i$ 必须在 $y_i$ 前删掉，你需要在满足限制的情况下由外而内删掉这棵树。
> 
> 问多少个点可以成为最后一个被删的点。
> 
> $n\le 10^5$。

先说结论：找出一个合法点后以其为根，其所在的极大满足不作为 $x_i$ 的连通块（即不是限制的起点）就是答案为 $1$ 的部分。

找合法点可以用普通的拓扑排序思路（但每次要找树上度数最小的点，用 `std::set` 实现），也可以把两个图建在一起，每次把度数为 $1$ 的点加入队列。

来证明一下这个结论：

- 首先所有合法点不会有隔断，因为如果存在两个合法点满足 $a,b$ 不相邻，那么一定可以从 $a$ 删到 $b$，也一定可以从 $b$ 删到 $a$，所以路径内部没有任何限制，所以这之间任意一点的合法操作序列都可以用路径两端的两者的合法操作序列拼起来（可以手模一下）。

- 其次 $x_i$ 的子树不可能合法：保证根是最后一个删的所以 $x_i$ 的子树可以独立删掉，所以 $y_i$ 不可能在 $x_i$ 内，而这导致了如果不删掉 $x_i$，$x_i$ 子树外就一定删不干净，所以必须通过删掉 $x_i$ 子树的方式来删掉 $x_i$，所以 $x_i$ 和 $x_i$ 子树都是不合法的。

- 最后由于合法点的邻域无限制，所以可以先把外边删完再自由安排邻域删除的顺序，所以邻域均合法。

Code：

```cpp
// Problem: P5157 [USACO18DEC] The Cow Gathering P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5157
// Memory Limit: 125 MB
// Time Limit: 1000 ms

#include<bits/stdc++.h>
#define pb emplace_back
#define F(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
using namespace std;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char *p1,*p2,buf[1<<21];
int read() {
	int s=0,w=0;char ch=gc();
	while(ch<'0'||ch>'9') w|=(ch=='-'),ch=gc();
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=gc();
	return w?-s:s;
} const int N=1e5+5,M=N<<1;
int n,m,ans[N],d[N];vector<int> G[N],G2[N];
queue<int> q;
void df(int x,int fa) {
	if(G2[x].size()) return;
	ans[x]=1;
	for(int y:G[x]) if(y^fa) {
		df(y,x);
	}
}
int main() {
	n=read();m=read();
	if(n==1) return puts("1"),0;
	F(i,2,n) {
		int x=read(),y=read();
		G[x].pb(y);G[y].pb(x);d[x]++;d[y]++;
	} 
	F(i,1,m) {
		int x=read(),y=read();
		G2[x].pb(y);d[y]++;
	}
	df([](){
		F(x,1,n) d[x]==1&&(q.push(x),1);
		int cnt=0,x=-1;while(!q.empty()) {
			x=q.front();q.pop();++cnt;
			for(int y:G[x]) d[y]--,d[y]==1&&(q.push(y),1);
			for(int y:G2[x]) d[y]--,d[y]==1&&(q.push(y),1);
		} if(cnt<n) {
			F(i,1,n) printf("0\n");
			return exit(0),0;
		} return x;
	}(),0);
	F(i,1,n) printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：_Fontainebleau_ (赞：1)

刚学了拓扑排序，A了这道题
```
#include<iostream>
#include<cctype>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<ctime>
#include<queue>
#include<cstdlib>
#include<algorithm>
#define N 220000
#define L 200000
#define eps 1e-7
#define inf 1e9+7
#define db double
#define ll long long
#define ldb long double
using namespace std;
inline int read()
{
    char ch=0;
    int x=0,flag=1;
    while(!isdigit(ch)){ch=getchar();if(ch=='-')flag=-1;}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x*flag;
}
struct edge{int to,nxt;}e[N*2],E[N*2];
int num,head[N],NUM,HEAD[N];
inline void add(int x,int y){e[++num]=(edge){y,head[x]};head[x]=num;}
inline void ADD(int X,int Y){E[++NUM]=(edge){Y,HEAD[X]};HEAD[X]=NUM;}
queue<int>q;
bool vis[N];
int times,c[N],sz[N],deg[N],deg_[N],dep[N],dfn[N],nxt[N][25];
void dfs(int x,int fa)
{
    sz[x]=1;dfn[x]=++times;dep[x]=dep[fa]+1;
    for(int i=head[x];i!=-1;i=e[i].nxt)
    {
        int to=e[i].to;
        if(to==fa)continue;
        dfs(to,x);sz[x]+=sz[to];nxt[to][0]=x;
    }
}
int get(int x,int k){for(int i=0;i<=20;i++)if(1<<i&k)x=nxt[x][i];return x;}
int main()
{
    num=NUM=-1;memset(head,-1,sizeof(head));memset(HEAD,-1,sizeof(HEAD));
    int n=read(),m=read(),tot=0;
    for(int i=1;i<n;i++){int x=read(),y=read();add(x,y);add(y,x);deg[x]++;deg[y]++;}
    dfs(1,1);
    for(int k=1;k<=20;k++)for(int i=1;i<=n;i++)nxt[i][k]=nxt[nxt[i][k-1]][k-1];
    for(int i=1;i<=m;i++)
    {
        int x=read(),y=read();
        ADD(x,y);deg_[y]++;
        int l=dfn[x],r=dfn[x]+sz[x]-1;
        if(l<=dfn[y]&&dfn[y]<=r)
        {
            int to=get(y,dep[y]-dep[x]-1);
            int pl=dfn[to],pr=dfn[to]+sz[to]-1;
            c[pl]--;c[pr+1]++;c[1]++;c[n+1]--;
        }
        else c[l]++,c[r+1]--;
    }
    for(int i=1;i<=n;i++)if(deg[i]==1&&!deg_[i])q.push(i);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        if(vis[x])continue;vis[x]=true;tot++;
        for(int i=head[x];i!=-1;i=e[i].nxt){int to=e[i].to;deg[x]--;deg[to]--;}
        for(int i=HEAD[x];i!=-1;i=E[i].nxt){int to=E[i].to;deg_[to]--;}
        for(int i=head[x];i!=-1;i=e[i].nxt){int to=e[i].to;if(deg[to]==1&&!deg_[to])q.push(to);}
        for(int i=HEAD[x];i!=-1;i=E[i].nxt){int to=E[i].to;if(deg[to]==1&&!deg_[to])q.push(to);}
    }
    if(tot<n){for(int i=1;i<=n;i++)printf("0\n");return 0;}
    for(int i=1;i<=n;i++)c[i]+=c[i-1];
    for(int i=1;i<=n;i++)printf("%d\n",c[dfn[i]]?0:1);
    return 0;
}
```


---

## 作者：VictorChen (赞：0)

首先考虑观察题目性质；
>
> 使得只要至少还有两头奶牛尚未离开，所有尚未离开的奶牛都还有没有离开的朋友。

这说明每次移除都必然只能移除某个叶子节点；即整张图必须一直保持着连通的状态。

接下来考虑分析 $(a_i,b_i)$ 的性质。发现对于一个这样的数对，如果 $a_i$ 为树根，则只有 $b_i$ 所在的子树有可能成为最终的节点。简要证明如下：

1. 如果要移除 $a_i$，则必须使得只剩一个与其联通的节点；
2. $b_i$ 所在的子树的节点必然不能被提前移除；
3. 必须先移除其他子树所有的节点；

拥有了这个结论，我们就可以进行简单的分类讨论。

- 如果 $a_i$ 是 $b_i$ 的祖先：
	
 	此时除去 $b_i$ 所在的 $a_i$ 的子树，其它奶牛均不可能成为最后离开的奶牛；
    
- 其他情况

	此时 $a_i$ 及其子树必然不可能成为最后离开的奶牛；
    
因此我们可以发现，如果满足要求的奶牛存在，他们必然全部属于某一个特定的子树。对于所有的第一类情况，我们可以求出所有对应子树的交，找出对应的子树（或者判断其不存在）。随后我们再通过在树上打标记的方法来处理所有的第二种情况。这两部分的核心代码如下：

```cpp
// 寻找两个子树的交
int merge(int x, int y)
{
    if(x == 0 || y == 0)
        return 0;

    int k = lca(x, y);
    if(k == x) return y;
    else if(k == y) return x;
    else return 0;
}

// 寻找x在y中对应的子树
int find_bel(int x, int y)
{
    for(int i=mxLog; i>=0; i--)
        if(dep[fa[x][i]] > dep[y])
            x = fa[x][i];
    return x;
}

// 以下部分为主函数中的代码
for(int i=1; i<=m; i++)
{
    int x, y;
    scanf("%d%d", &x, &y);
    
    v[x].push_back(y);
    val[y]++;

    int k = g.lca(x, y);

    if(k == x)
        lst[++len] = g.find_bel(y, x); // 把所对应的子树放入要取交集的序列中
    else
        neg[x] = 1; // 在对应的子树上打标记
}

int nw_root = 1;
for(int i=1; i<=len; i++)
    nw_root = g.merge(nw_root, lst[i]); // 通过合并来找子树的交集
```

在找到这些符合要求的牛之后，我们只需要找到一种可能的把他们移除掉的方法即可（判断正确性）。这里我们可以选择把一头可以最后被移除的牛作为新的根节点，随后逐渐移除掉所有的叶子节点即可。如果发现无法全部移除，则说明存在冲突，不存在移除所有奶牛的方法。

本题的完整代码可以参考[这个剪贴板](https://www.luogu.com.cn/paste/7hphw3pc)。

---

## 作者：Mariposa (赞：0)

题意就是要使任意时刻不存在孤点。显然我们每次只能删叶子，否则分为两个子树后最后总会至少存在两个孤点。

考虑一个限制 $a$ 要在 $b$ 前面，其实意思就是把 $b$ 提作根后 $a$ 的整个子树都要在 $b$ 之前，于是我们可以连出一张图。显然若此图存在环则无解，否则没有出度的点就是答案。

我们可以用线段树优化建图实现，时空复杂度 $O(n\log n)$

```
#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
const int maxn=2e5+10;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,dfn[maxn],f[maxn][20],ti,ed[maxn],S[maxn],dep[maxn],tr[maxn<<2],id[maxn],tot;
vector<int>G[maxn],nG[maxn<<2];
#define pb push_back
inline void dfs(int x,int fa){
	dfn[x]=++ti,f[x][0]=fa;
	for(int i=1;i<20;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	dep[x]=dep[fa]+1;
	for(auto t:G[x])
		if(t^fa)dfs(t,x);
	ed[x]=ti;
}
inline void build(int h,int l,int r){
	tr[h]=++tot;
	if(l==r)return void(id[l]=tr[h]);
	int mid=(l+r)>>1;
	build(h<<1,l,mid);
	build(h<<1|1,mid+1,r);
	nG[tr[h<<1]].pb(tr[h]);
	nG[tr[h<<1|1]].pb(tr[h]);
}
inline void modify(int h,int l,int r,int x,int y,int z){
	if(l>y||r<x||x>y)return;
	if(l>=x&&r<=y)return void(nG[tr[h]].pb(z));
	int mid=(l+r)>>1;
	modify(h<<1,l,mid,x,y,z);
	modify(h<<1|1,mid+1,r,x,y,z);
}
inline bool in(int y,int x){return dfn[y]>=dfn[x]&&dfn[y]<=ed[x];}
inline int jump(int y,int x){for(int i=19;~i;--i)if(dep[f[y][i]]>dep[x])y=f[y][i];return y;}
inline void add(int l,int r,int x){
	++S[l],--S[r+1],modify(1,1,n,l,r,id[dfn[x]]);
}
int Dfn[maxn],low[maxn],ins[maxn],now,scc;stack<int>St;
inline void tarjan(int x){
	Dfn[x]=low[x]=++now;
	ins[x]=1;St.push(x);
	for(auto t:nG[x]){
		if(!Dfn[t]){
			tarjan(t);
			low[x]=min(low[x],low[t]);
		}else if(ins[t])low[x]=min(low[x],Dfn[t]);
	}if(Dfn[x]==low[x]){
		++scc;ins[x]=0;
		while(St.top()!=x)ins[St.top()]=0,St.pop();
		St.pop();
	}
}
int main(){
	n=read(),m=read();
	for(int i=1,x,y;i<n;i++)
		x=read(),y=read(),G[x].pb(y),G[y].pb(x);
	dfs(1,0);build(1,1,n);
	for(int i=1,x,y;i<=m;i++){
		x=read(),y=read();
		if(in(y,x)){
			x=jump(y,x);
			add(1,dfn[x]-1,y),add(ed[x]+1,n,y);
		}else add(dfn[x],ed[x],y);
	}
	for(int i=1;i<=tot;i++)
		if(!Dfn[i])tarjan(i);
	if(scc<tot){
		for(int i=1;i<=n;i++)puts("0");
		return 0;
	}
	for(int i=1;i<=n;i++)S[i]+=S[i-1];
	for(int i=1;i<=n;i++)
		printf("%d\n",(S[dfn[i]]==0));
	return 0;
}
```

---

## 作者：yxy666 (赞：0)

看到这道题我们自然而然地就会想到拓扑。但是拓扑的时候不能满足题目的第二个条件：必须满足奶牛 $Ai$ 要比奶牛 $Bi$  先离开。那我们就先按照 $M$ 行的数据建个单向边，然后等会刷拓扑的时候一起刷，这样就能保证 $Ai$ 要先比 $Bi$ 刷到，也就是先离开。等我们找到第一个入度为 $0$ 的点时，我们就找到了树根。接下来我们从树根开始反推,比如限定条件的 $(A,B)$ ,那么 $A$ 所在的子树(包括 $A$ )都必须先处理掉,因为这帮家伙都不可能最后删除,那么剩下的都是可零可一的节点。按照题目的要求，那么我们绝对要全给 $1$ 啊。

$code$ :
```cpp
#include<bits/stdc++.h>
#define TT 200000
using namespace std;
const int maxn=100005,maxe=200005;
int n,m,fa,hed,til,tot[2],du[maxn],ans[maxn],que[maxe],son[2][maxe],lnk[2][maxn],nxt[2][maxe];
bool vis[maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}

void add_e(int k,int x,int y){du[y]++;son[k][++tot[k]]=y;nxt[k][tot[k]]=lnk[k][x];lnk[k][x]=tot[k];} 
void Topu(){
	for(int i=1;i<=n;i++)if(du[i]==1)que[++til]=i;
	while(hed<=til){
		hed=(hed+1)%TT;
		if(du[que[hed]]==0){fa=que[hed];return ;}
		for(int j=lnk[0][que[hed]];j;j=nxt[0][j])if(--du[son[0][j]]==1)que[til=(til+1)%TT]=son[0][j];
		for(int j=lnk[1][que[hed]];j;j=nxt[1][j])if(--du[son[1][j]]==1)que[til=(til+1)%TT]=son[1][j];
	}
}
void dfs(int x,int father){
	ans[x]=1;
	for(int j=lnk[0][x];j;j=nxt[0][j]){
		if(son[0][j]==father||vis[son[0][j]])continue;
		dfs(son[0][j],x);
	}
}
int main(){
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		add_e(0,x,y);add_e(0,y,x);
	}//建双向边
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		add_e(1,x,y);
		vis[x]=1;
	}//再建图
	Topu();//找树根
   dfs(fa,0);//从根上开始遍历
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);//输出答案
	return 0;
} 
```


---

