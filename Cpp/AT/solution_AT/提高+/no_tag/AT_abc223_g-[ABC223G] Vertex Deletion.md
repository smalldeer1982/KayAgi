# [ABC223G] Vertex Deletion

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc223/tasks/abc223_g

$ N $ 頂点の木が与えられます。頂点には $ 1,2,\ldots\ ,N $ の番号がついており、$ i\,(1\ \leq\ i\ \leq\ N-1) $ 本目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結んでいます。

以下の条件を満たす整数 $ i\,(1\ \leq\ i\ \leq\ N) $ の個数を求めてください。

- 元の木から頂点 $ i $ およびそれに接続する全ての辺を削除して得られるグラフの最大マッチングの大きさが、元の木の最大マッチングの大きさに等しい。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ u_i\ <\ v_i\ \leq\ N $
- 与えられるグラフは木
- 入力は全て整数

### Sample Explanation 1

元の木の最大マッチングの大きさは $ 1 $ です。 頂点 $ 1 $ およびそれに接続する全ての辺を削除して得られるグラフの最大マッチングの大きさは $ 1 $、 頂点 $ 2 $ およびそれに接続する全ての辺を削除して得られるグラフの最大マッチングの大きさは $ 0 $、 頂点 $ 3 $ およびそれに接続する全ての辺を削除して得られるグラフの最大マッチングの大きさは $ 1 $ です。$ i=1,3 $ の $ 2 $ つが条件を満たすので、$ 2 $ を出力します。

## 样例 #1

### 输入

```
3
1 2
2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
2
1 2```

### 输出

```
0```

## 样例 #3

### 输入

```
6
2 5
3 5
1 4
4 5
4 6```

### 输出

```
4```

# 题解

## 作者：Empty_Dream (赞：7)

## 题意

给定一棵树，其中有 $N$ 个节点。求出满足以下条件的点 $u$ 的数量：

- 把 $u$ 和连接 $u$ 的边全部删除后得到的图的最大匹配与原树的最大匹配（二分图最大匹配）相等。

## 分析
> 树的二分图最大匹配 = 总结点数 - 最大独立集。

显然需要先去计算原树上的最大独立集是多少。考虑 dp，设 $f_{u,0/1}$ 表示取或不取 $u$ 时 $u$ 的子树上最大独立集的大小，转移有两种：

- $f_{u,0}=\sum \max(f_{v,0},f_{v,1})$，其中 $v$ 是 $u$ 的子节点。
- $f_{u,1}=\sum f_{v,0} + 1$，其中 $v$ 是 $u$ 的子节点。

![image-20240327202054177](https://cdn.luogu.com.cn/upload/image_hosting/m900053v.png)

这里 $f$ 是从叶子节点往上转移的，$f_V$ 都已经求得。求出来这些之后，原树的最大独立集就是 $\max (f_{1,0},f_{1, 1})$，匹配数为 $n-\max(f_{1,0},f_{1,1})$。记得初始化每一个点 $f_{u,1} = 1$。

之后的问题就变成了如何计算删去一个节点的贡献，可以继续用换根 dp。有了上面的 $f$，这一步就很方便了，删去这个节点出来的答案就是这个节点上面的加上子树上的。我们就需要另一个数组 $g$ 来记录 $u$ 上面的最大独立集个数，按照 $f$ 的方法，$g_{u,0/1}$ 表示取或不取 $fa_u$ 时，$u$ 子树之外的最大独立集大小，还是分两种转移：

- $g_{u,0}=\max(g_{fa,0},g_{fa,1})+f_{fa,0}-\max(f_{u,0},f_{u,1})$。
- $g_{u,1}=g_{fa,0}+f_{fa,1}-f_{u,0}$。

![image-20240327202650141](https://cdn.luogu.com.cn/upload/image_hosting/md58q1z6.png)

这里 $g$ 是从根节点往下转移的，所以 $g_{fa}$ 的值是知道的。这时不选 $u$ 的最大独立集是 $f_{u,0}+\max(g_{u,0},g_{u,1})$，匹配数为 $n-1-(f_{u,0}+\max (g_{u,0},g_{u,1}))$，与原树的匹配数比较一下，统计答案。

![image-20240327202124330](https://cdn.luogu.com.cn/upload/image_hosting/x7swsx7b.png)

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, ans;
int f[200005][2], g[200005][2];
vector<int> e[200005];

void dfs1(int x, int fa){
    f[x][1] = 1;//初始化
    for (int i = 0; i < e[x].size(); i++){
        int v = e[x][i];
        if (v == fa) continue;
        dfs1(v, x);//先往下递归，再向上转移
        f[x][0] += max(f[v][0], f[v][1]);//转移
        f[x][1] += f[v][0];
    }
}

void dfs2(int x, int fa){
    for (int i = 0; i < e[x].size(); i++){
        int v = e[x][i];
        if (v == fa) continue;
        g[v][0] = max(g[x][0], g[x][1]) + f[x][0] - max(f[v][0], f[v][1]);//先向下转移，再往下递归
        g[v][1] = g[x][0] + f[x][1] - f[v][0];//转移
        dfs2(v, x);
    }
}

int main(){
    cin >> n;
    for (int i = 1, u, v; i < n; i++){
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++){
        if (n - 1 - (f[i][0] + max(g[i][0], g[i][1])) == n - max(f[1][1], f[1][0])) ans++;//判断两个匹配是否相等
    }
    cout << ans;
    return 0;
}
```

---

## 作者：hxhhxh (赞：6)

## 题意

给一棵树，求有多少个点，使得删掉这个点后最大匹配的边数不变。

## 做法

首先，树是一个二分图。我们可以随便使用一种方式求出它的一组匹配。代码里使用的是贪心。

发现题目里求的点满足存在一组匹配，使得这个点不在匹配内。这个是不容易处理的，所以考虑对于每个点，求出如果往这个点上挂一个临时叶子，最大匹配是否会增加。不难发现如果会增加，那么一定存在一组匹配使得这个点不在匹配内，否则不会增加。

考虑如何判断是否会增加。当我们求解二分图最大匹配是，我们会寻找增广路是否存在。如果增广路存在，那么我们就可以使最大匹配增大。这启发我们对于每个点，考察加一个叶子后，增广路是否存在。

![](https://cdn.luogu.com.cn/upload/image_hosting/doiq8niq.png)

如图，加粗的边是匹配边，红色的点是不在匹配内的点，所有不是白色的点都是满足题目条件的点。图中 $*-7-4-6$，$*-2-1-3$，$*-8-5-2-1-3$ 都是增广路（$*$ 是临时的叶子，图中未画出）。如果将 $*$ 忽略并将路径反过来，那么 $6-4-7$，$3-1-2$，$3-1-2-5-8$ 都是“增广路”。

显然这样的“增广路”都是从红点开始，交替经过非匹配边和匹配边。所以我们可以从每个红点开始，每次一次性跳过非匹配边和匹配边，所有能到达的点就是黄点。

但是如果你直接从每个红点开始搜整个图，虽然你可能能过掉这个题，但是它的复杂度是错误的。考虑下面这种图：

![](https://cdn.luogu.com.cn/upload/image_hosting/xqe634bo.png)

每次我们都会把右边的所有点搜一遍，时间复杂度是 ${\rm O}(n^2)$ 的。

解决方案也很简单，由于每个点能到的点是固定的，所以如果我们已经到过一个点（已经被标黄），就不用继续搜下去了。这样每个点只会变黄一次，的时间复杂度是 ${\rm O}(n)$ 的。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c[200005],p[200005],ans;
//c[x]表示x匹配的点，若为0则未匹配
//p[x]表示x是否满足条件 
vector<int>e[200005];
int dfs(int x,int f){
	for(int i:e[x]){
		if(i!=f){
			if(!dfs(i,x)){//i没有匹配 
				if(!c[x]){//x没有匹配 
					c[x]=i,c[i]=x;//把x和i匹配 
				}
			}
		}
	}
	return c[x];
}
void dfs2(int x,int f){
	if(p[x]) return;
	p[x]=1;//x是黄点（或者红点） 
	for(int i:e[x]){
		if(i==f) continue;//要么f是0，要么x-f是x唯一的匹配边。 
		if(c[i]){//x-i是非匹配边，i-c[i]是匹配边 
			dfs2(c[i],i);//直接跳过x-i-c[i] 
		}
	}
}
int main(){
	cin>>n;
	for(int i=1,j,k;i<n;i++) scanf("%d %d",&j,&k),e[j].push_back(k),e[k].push_back(j);
	dfs(1,0);
	for(int i=1;i<=n;i++){
		if(!c[i]){//i是红点 
			dfs2(i,0);
		}
	}
	for(int i=1;i<=n;i++) ans+=p[i];
	cout<<ans;
	return 0;
}
```

---

## 作者：forest114514 (赞：3)

### [ABC223G] Vertex Deletion

有意思的一道题，首先上一些基本结论：

> 树 $\to$ 二分图 的最大匹配数目=总点数-二分图的最大权独立集

我们记  $f_{u,0/1}$ 为 不选/选 $u$ 时 $u$ 子树的最大权独立集大小，$g_{u,0/1}$为 不选/选 $fa_u$ 时 $u$ 子树外的部分的最大权独立集大小

所以有：
$$
f_{u,0}=\sum\limits_{v\in son_u}\max{\{f_{v,0},f_{v,1}\}}\quad f_{u,1}=\sum\limits_{v\in son_u}f_{v,0}+1
$$
 
$$
g_{u,0}=\max{\{g_{fa,0},g_{fa,1}\}}+f_{fa,0}-\max{\{f_{u,0},f_{u,1}\}}\quad g_{u,1}=g_{fa,0}+f_{fa,1}-f_{u,0}
$$


最后不选点 $u$ 时的最大匹配大小为 $n-1-\left(f_{u,0}+\max\{g_{u,0},g_{u,1}\}\right)$，而整个树的最大匹配大小为 $n-\max\{f_{rt,0},f_{rt,1}\}$，一一比较即可。

code：

```cpp
#include<bits/stdc++.h>
#define re register
#define il inline
#define gc() getchar()
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
#define tep(i,x) for(re int i=head[x];~i;i=ne[i])
#define ls(x) tr[x].son[0]
#define rs(x) tr[x].son[1]
#define eps (1e-9)
#define inf 0x3f3f3f3f
#define INF 1e18+100
#define pii pair<int,int>
#define mp(i,j) make_pair(i,j)
#define pb push_back
#define fi first
#define sc second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
template<typename T> inline void read(T &x){
	bool f=1;x=0;char ch=gc();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=gc();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch&15),ch=gc();
	x=f?x:-x;
}
template<typename T> inline void write(T x){
	if(x<0) putchar('-'),x=-x;
   	if(x>9) write(x/10);
   	putchar(('0'+x%10));
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
template<typename T> inline void write(T x,char c){write(x),putchar(c);}
const int N=2e5+100;
int n,f[N][2],g[N][2],maxx,ans;
vector<int> E[N];
void dfs1(int x,int fa){
	f[x][1]=1;
	for(auto y:E[x]){
		if(y==fa) continue;
		dfs1(y,x);
		f[x][0]+=max(f[y][0],f[y][1]),f[x][1]+=f[y][0];
	}
}
void dfs2(int x,int fa){
	for(auto y:E[x]){
		if(y==fa) continue;
		g[y][0]=max(g[x][0],g[x][1])+f[x][0]-max(f[y][0],f[y][1]);
		g[y][1]=g[x][0]+f[x][1]-f[y][0];
		dfs2(y,x);
	}
}
signed main(){
	//ios::sync_with_stdio(false);
	//cin.tie(0);cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n);
	int u,v;
	rep(i,1,n-1){
		read(u,v);
		E[u].pb(v),E[v].pb(u);
	}
	dfs1(1,0);
	maxx=max(f[1][1],f[1][0]);
	dfs2(1,0);
	rep(i,1,n){
		int val=f[i][0]+max(g[i][0],g[i][1]);
		if(n-1-val==n-maxx) ans++;
	} 
	write(ans,'\n');
	return 0;
}
```



---

## 作者：EuphoricStar (赞：3)

设 $f_{u,0/1}$ 为 $u$ 的子树，$u$ 是否在匹配内的最大匹配数。

注意到对于一个匹配，在它深度较浅的点上才会被计入答案。

转移大概是 $f_{u,0}$ 取 $\sum\limits_{v \in son_u} \max(f_{v,0}, f_{v,1})$，$f_{u,1}$ 要从儿子中选一个 $f_{v,0}$，剩下的选 $\max(f_{v,0}, f_{v,1})$。先假设全部选 $\max(f_{v,0}, f_{v,1})$，求出 $\max\limits_{v \in son_u} f_{v,0} - \max(f_{v,0}, f_{v,1})$，加进 $f_{u,1}$ 即可。

发现还要求以父亲为根的子树的最大匹配，这个是换根基础操作，转移式同上。减去儿子的 $\max$ 部分，维护前缀 $\max$ 和后缀 $\max$ 即可。注意特殊处理根。

[code](https://atcoder.jp/contests/abc223/submissions/41445506)

---

## 作者：鲤鱼江 (赞：0)

考虑到最大匹配=总结点数-最大独立集，而最大独立集正是树形动规可以做的。

设 $f_{x,0}$ 表示不选 $x$，其子树内的最大独立集大小，$f_{x,1}$ 表示选 $x$。

则 $f_{x,0}=\sum_{v\in Son_x}\max(f_{v,0},f_{v,1})$，$f_{x,1}=1+\sum_{v\in Son_x}f_{v,0}$。

那么去掉根节点 $1$ 的最大匹配就是 $n-1-f_{1,0}$。

现在要求每一个节点的答案，这种形式不难想到换根。

具体来讲，设 $g_{x,1/0}$ 表示选/不选 $x$ 时的答案，$y$ 是节点 $x$ 的父亲，有 $g_{x,0}=f_{x,0}+\max(g_{y,0}-\max(f_{x,0},f_{x,1}),g_{y,1}-f_{x,0})$。$g_{x,1}$ 的转移类似，详情可见代码。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;
        	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;
	        return *this;
    	}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        if(x<0){putchar('-');x=-x;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer(){}
	}cout;
}
#define endl '\n'
#define cin Fastio :: cin
#define cout Fastio :: cout

const int N=2e5+10;int h[N],cnt,f[N][2],g[N][2],n,ans;
struct edge{int to,ne;edge(int to=0,int ne=0):to(to),ne(ne){;}}a[N<<1];
inline void add(const int x,const int y){a[++cnt]=edge(y,h[x]);h[x]=cnt;}
void dfs1(int x,int y){
	f[x][1]=1;
	for(int i=h[x];i;i=a[i].ne){
		if(a[i].to==y) continue;
		dfs1(a[i].to,x);f[x][1]+=f[a[i].to][0];
		f[x][0]+=max(f[a[i].to][0],f[a[i].to][1]);
	}
}

void dfs2(int x,int y){
	if(y){
		g[x][1]=g[y][0]-max(f[x][0],f[x][1])+f[x][1];
		g[x][0]=f[x][0]+max(g[y][0]-max(f[x][0],f[x][1]),g[y][1]-f[x][0]);
	}else {g[x][1]=f[x][1];g[x][0]=f[x][0];}
	for(int i=h[x];i;i=a[i].ne) if(a[i].to!=y) dfs2(a[i].to,x);
}

signed main(){
	cin>>n;
	for(int i=1,x,y;i<n;++i){cin>>x>>y;add(x,y);add(y,x);}
	dfs1(1,0);dfs2(1,0);for(int i=1;i<=n;++i) if(g[i][0]+1==max(g[1][0],g[1][1])) ++ans;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：forgotmyhandle (赞：0)

[原题传送门](https://atcoder.jp/contests/abc223/tasks/abc223_g)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc223_g)

## 分析

由于树是二分图，而二分图最大匹配等于最小点覆盖，我们转化为最小点覆盖来做。$dp[x][0 / 1]$ 表示 $x$ 子树内 $x$ 不选 / 选的最小点覆盖。整棵树的答案是 $\min\{dp[1][0], dp[1][1]\}$。接下来考虑换根，递归时 $x$ 向子树 $y$ 传入两个参数表示 $x$ 选 / 不选时 $y$ 子树外的最小点覆盖。这样就相当于以 $y$ 为根，做 $x$ 子树的 dp。考虑对 $x$ 的子树做前后缀 dp 值的合并，然后结合父亲传下来的 dp 值就可以很容易地求出 $y$ 为根时 $x$ 的 dp 值。然后去掉 $x$ 这个点相当于以 $x$ 为根并且强制选 $x$ 这个点时整棵树的最小点覆盖减 $1$（减去 $x$）。于是答案就很好求了。

## 代码

```cpp
#include <iostream>
using namespace std;
int n;
int head[200005], nxt[400005], to[400005], ecnt;
void add(int u, int v) { to[++ecnt] = v, nxt[ecnt] = head[u], head[u] = ecnt; }
int dp[200005][2];
int dp2[200005][2];
int ps[200005], ns[200005];
int pre[200005][2], suf[200005][2];
void dfs1(int x, int fa) {
    dp[x][1] = 1;
    int tmp = 0;
    for (int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        if (v != fa) {
            dfs1(v, x);
            dp[x][1] += min(dp[v][0], dp[v][1]);
            dp[x][0] += dp[v][1];
            ns[ps[v] = tmp] = v;
            pre[v][0] = min(dp[v][0], dp[v][1]) + pre[ps[v]][0];
            pre[v][1] = dp[v][1] + pre[ps[v]][1];
            tmp = v;
        }
    }
    while (tmp) {
        suf[tmp][0] = min(dp[tmp][0], dp[tmp][1]) + suf[ns[tmp]][0];
        suf[tmp][1] = dp[tmp][1] + suf[ns[tmp]][1];
        tmp = ps[tmp];
    }
}
void dfs2(int x, int fa, int up0, int up1) {
    dp2[x][0] = dp[x][0];
    dp2[x][1] = dp[x][1];
    if (fa) {
        dp2[x][0] += up1;
        dp2[x][1] += min(up0, up1);
    }
    for (int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        if (v != fa) {
            int t1 = up1 + pre[ps[v]][1] + suf[ns[v]][1];
            int t2 = min(up0, up1) + pre[ps[v]][0] + suf[ns[v]][0] + 1;
            dfs2(v, x, t1, t2);
        }
    }
}
int main() {
    // freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    int ans = 0;
    dfs1(1, 0);
    ans = min(dp[1][0], dp[1][1]);
    dfs2(1, 0, 0, 0);
    int cnt = 0;
    for (int i = 1; i <= n; i++) cnt += (dp2[i][1] - 1 == ans);
    cout << cnt << "\n";
    return 0;
}
```

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://watersun.top/[%E9%A2%98%E8%A7%A3]AT_abc223_g%20[ABC223G]%20Vertex%20Deletion)

# 思路

显然我们需要求出原树的最大匹配。

定义 $dp_{i,0/1}$ 表示在 $i$ 为根的子树中进行匹配，且 $i$ 不选/选 的最大匹配。状态转移方程比较显然：

$$
\left\{\begin{matrix}
dp_{u,0} = \sum{val_v}\\
dp_{u,1} = (\sum{val_v}) - val_t + dp_{t,0} + 1
\end{matrix}\right.
$$

其中 $val_u = \max(dp_{u,0},dp_{u,1})$，然后 $t$ 是使得 $dp_{u,1}$ 最大的一个 $v$。显然这一步是可以 $\Theta(n)$ 计算的。

注意到，我们需要计算删除 $u$ 后的最大匹配，这等同于计算以 $u$ 为根时的 $dp_{u,0}$。于是考虑换根 DP。

令当前的根由 $u$ 转为 $v$。接下来只需简单分讨，记转移 $dp_{u,1}$ 时的 $t$ 为 $id_u$，$dp_{t,0} - val_t + 1$ 为 $Max_u$。

由于 $v$ 由 $u$ 的儿子变为了父亲，$dp_u$ 的值一定发生变化。显然 $dp_{u,0} \leftarrow dp_{u,0} - val_v$。其次：

1. 当 $id_u = v$ 时：$dp_{u,1} \leftarrow dp_{u,0} - dp_{v,1} - 1$，然后和其次大值进行匹配。因此还需在第一次 DFS 时处理出次大的儿子。

2. 否则：$dp_{u,1}$ 直接减去 $val_v$ 即可。

然后可以更新 $val_u \leftarrow \max(dp_{u,0},dp_{u,1})$。接下来更新 $dp_v$。

显然的是 $dp_{v,0/1}$ 都需要加上 $val_u$。

其次，如果 $Max_v$ 小于 $u$ 带来的贡献，那么更新掉即可。需要注意的是，$id_v,Max_v$ 以及维护的次大值都需要被更新。

这样就完成了所有元素的更新，继续向下换根即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2e5 + 10,M = 4e5 + 10,inf = 1e9 + 10;
int n,ans;
int idx,h[N],ne[M],e[M];
int res,dp[N][2],val[N],Max[2][N],id[2][N];
// 这里 Max[0/1] 和 id[0/1] 分别维护的是最小值和次小值

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

inline void dfs1(int u,int fa){
    int mMax = -inf,fMax = -inf;
    int mid = 0,fid = 0;
    val[u] = dp[u][0] = dp[u][1] = 0;
    for (re int i = h[u];~i;i = ne[i]){
        int j = e[i];
        if (j == fa) continue;
        dfs1(j,u);
        dp[u][0] += val[j];
        dp[u][1] += val[j];
        int t = dp[j][0] - val[j] + 1;
        if (mMax < t){
            fMax = mMax; fid = mid;
            mMax = t; mid = j;
        }
        else if (fMax < t){
            fMax = t; fid = j;
        }
    }
    Max[0][u] = mMax; Max[1][u] = fMax;
    id[0][u] = mid; id[1][u] = fid;
    dp[u][1] += max(0,mMax);
    val[u] = max(dp[u][0],dp[u][1]);
}

inline void dfs2(int u,int fa){
    ans += (dp[u][0] == res);
    for (re int i = h[u];~i;i = ne[i]){
        int j = e[i];
        if (j == fa) continue;
        int dpu0 = dp[u][0],dpu1 = dp[u][1],valu = val[u];
        int Max0u = Max[0][u],Max1u = Max[1][u],id0u = id[0][u],id1u = id[1][u];
        int dpj0 = dp[j][0],dpj1 = dp[j][1],valj = val[j];
        int Max0j = Max[0][j],Max1j = Max[1][j],id0j = id[0][j],id1j = id[1][j];
        dp[u][0] -= val[j];
        if (id[0][u] == j){
            dp[u][1] -= (dp[j][0] + 1);
            if (id[1][u]) dp[u][1] += Max[1][u];
        }
        else dp[u][1] -= val[j];
        val[u] = max(dp[u][0],dp[u][1]);
        dp[j][0] += val[u]; dp[j][1] += val[u];
        int t = dp[u][0] - val[u] + 1;
        if (Max[0][j] < t){
            dp[j][1] -= Max[0][j];
            Max[1][j] = Max[0][j]; id[1][j] = id[0][j];
            Max[0][j] = t; id[0][j] = u;
            dp[j][1] += Max[0][j];
        }
        else if (Max[1][j] < t){
            Max[1][j] = t; id[1][j] = u;
        }
        dfs2(j,u);
        dp[u][0] = dpu0; dp[u][1] = dpu1; val[u] = valu;
        Max[0][u] = Max0u; Max[1][u] = Max1u; id[0][u] = id0u; id[1][u] = id1u;
        dp[j][0] = dpj0; dp[j][1] = dpj1; val[j] = valj;
        Max[0][j] = Max0j; Max[1][j] = Max1j; id[0][j] = id0j; id[1][j] = id1j;
    }
}


int main(){
    memset(h,-1,sizeof(h));
    n = read();
    for (re int i = 1;i < n;i++){
        int a,b; a = read(),b = read();
        add(a,b); add(b,a);
    }
    dfs1(1,0); res = val[1];
    dfs2(1,0);
    printf("%d",ans);
    return 0;
}
```

---

## 作者：yqr123YQR (赞：0)

### 分析
记 $p_i$ 为 $i$ 在树上的父亲。

考虑删除 $u$ 后树的形态，分成两大部分：
1. $u$ 的子节点所在子树

   这部分的最大匹配可以 DP 求出。设 $f_{i,0/1}$ 表示 $i$ 在其子树中未连 / 连了匹配边时的最大匹配，则有如下转移：
   $$
   \left\{\begin{matrix}
   f_{i,0}&=&\sum\limits_{(i,j)\in E}\max\{f_{j,0},f_{j,1}\}\\
   f_{i,1}&=&f_{i,0}+\max\limits_{(i,j)\in E}(f_{j,0}-\max\{f_{j,0},f_{j,1}\})+1
   \end{matrix}\right.
   $$
   ~~认真看看应该能明白~~
   
   鉴于多处出现形如 $\max\{f_{i,0},f_{i,1}\}$ 的式子，记为 $val_i$。
2. 原树挖去 $u$ 所在子树的部分

   类似地，由于 $i$ 的状态对除 $i$ 字数外的状态毫无影响，故记录的状态改为 $p_i$ 的状态：

   令 $mx_i,nmx_i$ 分别表示 $i$ 的子节点中，$f_{v,0}-val_v$ 的最 / 次大值；$g_{i,0/1}$ 表示在原树除了 $i$ 所在子树的部分，$p_i$ 是否连过匹配边（**另一端点亦在此部分内**）。转移如下：
   $$
   \left\{\begin{matrix}
   g_{i,0}&=&f_{p_i,0}-\max\{f_{i,0},f_{i,1}\}+g_{p_i}\\
   g_{i,1}&=&\begin{cases}
   \max\{f_{p_i,1}-val_i+\max\{g_{p_i,0},g_{p_i,1}\},~f_{p_i,0}-val_i+g_{p_i,0}+1\}&\qquad f_{i,0}-val_i\ne mx_{p_i}\\
   \max\{f_{p_i,1}-val_i-mx_{p_i}+nmx_{p_i}+\max\{g_{p_i,0},g_{p_i,1}\},~f_{p_i,0}-val_i+g_{p_i,0}+1\}&\qquad f_{i,0}-val_i=mx_{p_i}
   \end{cases}
   \end{matrix}\right.
   $$
因为 $g$ 依赖于 $f$，我们需要两次 dfs 以求值，最后统计时判断 $\left(\sum\limits_{(u,v)\in E}val_v\right)+\max\{g_{i,0},g_{i,1}\}$ 是否等于 $val_1$ 即可。
### 代码
```cpp
#include<stdio.h>
#include<ctype.h>
#include<vector>
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 200005;
namespace IO {
	const int bufsize = 230005;
	char gtchar()
	{
		static char buf[bufsize], *p1 = buf, *p2 = buf;
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufsize, stdin), p1 == p2)? EOF: *p1++;
	}
	int read()
	{
		int ret = 0;
		char ch = gtchar();
		while(!isdigit(ch)) ch = gtchar();
		while(isdigit(ch)) ret = (ret << 3) + (ret << 1) + (ch ^ 48), ch = gtchar();
		return ret;
	}
}using IO::read;
std::vector<int> G[maxn];
int n, ans, mx[maxn], nmx[maxn], f[maxn][2], g[maxn][2], p[maxn], son[maxn];
int max(const int a, const int b) {return a < b? b: a;}
void dfs(int k)
{
	mx[k] = -maxn;
	for(int i : G[k])
	{
		if(i == p[k]) continue;
		son[k]++;
		p[i] = k;
		dfs(i);
		f[k][0] += max(f[i][0], f[i][1]);
		int t = f[i][0] - max(f[i][0], f[i][1]);
		if(mx[k] <= t) nmx[k] = mx[k], mx[k] = t;
		else nmx[k] = max(nmx[k], t);
	}
	if(son[k]) f[k][1] = f[k][0] + mx[k] + 1;
}
void dfs2(int k)
{
	if(k != 1)
	{
		int t = max(f[k][0], f[k][1]);
		g[k][0] = f[p[k]][0] - t + max(g[p[k]][0], g[p[k]][1]);
		g[k][1] = max((son[p[k]] > 1? f[p[k]][1] - mx[p[k]] + (mx[p[k]] == f[k][0] - t? nmx[p[k]]: mx[p[k]]) - t + max(g[p[k]][0], g[p[k]][1]): 0), (p[k] == 1? 0: f[p[k]][0] - t + g[p[k]][0] + 1));
	}
	for(int i : G[k]) if(i != p[k]) dfs2(i);
}
int main()
{
	// freopen("tree.in", "r", stdin);
	// freopen("tree.out", "w", stdout);
	n = read();
	for(int i = 1, u, v; i < n; i++) u = read(), v = read(), G[u].push_back(v), G[v].push_back(u);
	dfs(1), dfs2(1);
	for(int i = 1; i <= n; i++)
	{
		// printf("%d %d %d %d\n", f[i][0], f[i][1], g[i][0], g[i][1]);
		if(f[i][0] + max(g[i][0], g[i][1]) == max(f[1][0], f[1][1]))
			ans++;
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

首先考虑对于原树怎么计算答案。

对于树上最大匹配有一个贪心策略：自底向上匹配当前点和其父亲，删除这两个点，直至只剩一个点或空树。这个可以平凡树形 dp，用一个 dfs 实现。

然后对于这个过程，我们可以假设刚开始所有点都是白点，随便指定一个根节点，将所有叶子节点向上递归，如果至少有一个子节点是白的则匹配，涂黑，那么很显然只有涂色后根节点是白色去掉根节点才不会影响答案。

推广到对于所有点的情况，只需要用换根 dp 维护即可，所以只需要两遍 dfs 即可解决问题，时间复杂度 $ \mathcal{O}(n) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
const int N=233333;
int n,ans,c[N];
vector<int>e[N];
void dfs1(int x,int fa)
{
	for(int y:e[x])
	if(y^fa)
	dfs1(y,x),c[x]+=!c[y];
}
void dfs2(int x,int fa,int s)
{
	ans+=!c[x]&&s;
	for(int y:e[x])
	if(y^fa)
	dfs2(y,x,!s+c[x]-!c[y]); 
} 
int main()
{
	cin>>n;
	for(int i=1,x,y;i<n;i++)
	cin>>x>>y,e[x].push_back(y),e[y].push_back(x);
	dfs1(1,0),dfs2(1,0,1);
	cout<<ans;
}
```


---

