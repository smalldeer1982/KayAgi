# [ABC378F] Add One Edge 2

## 题目描述

给定一棵有 $N$ 个顶点的树。第 $i$ 条边 $(1\leq i\leq N-1)$ 连接了顶点 $u_i$ 和顶点 $v_i$，且为无向边。

在给定的树上添加一条无向边后，得到的图一定恰好包含一个简单环。

请计算满足以下所有条件的图的个数：

- 图是简单图。
- 图中环上所有顶点的度数都为 $3$。

## 说明/提示

## 限制条件

- $3\leq N\leq 2\times 10^5$
- $1\leq u_i,v_i\leq N$
- 给定的图是一棵树
- 输入的所有数值均为整数

## 样例解释 1

添加一条连接顶点 $2$ 和顶点 $4$ 的边后，得到的图是简单图，且环上所有顶点的度数都为 $3$，因此满足条件。

## 样例解释 2

有时不存在满足条件的图。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
1 2
2 3
3 4
4 5
3 6```

### 输出

```
1```

## 样例 #2

### 输入

```
7
1 2
2 7
3 5
7 3
6 2
4 7```

### 输出

```
0```

## 样例 #3

### 输入

```
15
1 15
11 14
2 10
1 7
9 8
6 9
4 12
14 5
4 9
8 11
7 4
1 13
3 6
11 10```

### 输出

```
6```

# 题解

## 作者：gesong1234 (赞：9)

题目传送门：[[ABC378F] Add One Edge 2](https://www.luogu.com.cn/problem/AT_abc378_f)。
# 思路
由于出现一个环需要添加一条边，因此连边的端点的度数在连完后需要加一，于是我们就得到了这两个点 $u,v$ 之间连边的可行判断条件：

1. $u,v$ 两端点的度数必须为 $2$。
2. $u$ 到 $v$ 的简单路径上经过的点（不包括 $u,v$）度数都为 $3$。

进一步发现一个度数为 $3$ 的点的连通块相邻的度数为 $2$ 的点均可两两互相到达，现在只需要求一个度数为 $3$ 的点的连通块相邻的度数为 $2$ 的点的个数。

我们假设 $w_u=\sum_{(u,v)\in E} [d_v=2]$，其中 $d_i$ 为点 $i$ 的度数，这样假设之后，前面的个数即可转化为这个连通块的 $w$ 之和。

因此我们只需要用 dfs 求解 $w$，然后 bfs 求解答案即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int w[N],n,d[N];
vector<int>a[N]; 
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
void dfs(int u,int fa){//求解 w 数组
	for (auto v:a[u]){
		if (v^fa) dfs(v,u);
		w[u]+=(d[v]==2);
	}
}
inline int bfs(int sx){//求解连通块 w 的和
	queue<int>q;
	q.push(sx);
	int ans=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		ans+=w[u];
		d[u]=0;
		for (auto v:a[u]){
			if (d[v]^3) continue;
			q.push(v);
		}
	}
	return ans;
}
main(){
	n=read();
	for (int i=1;i<n;i++){
		int u=read(),v=read();
		d[u]++,d[v]++;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	dfs(1,0);
	int ans=0;
	for (int i=1;i<=n;i++) if (d[i]==3){
		int x=bfs(i);
		ans+=x*(x-1)/2;//计算答案，任意两个点都可以组成题目满足的条件，因此这个连通块的贡献为 C(x,2)=x*(x-1)/2
	}
	cout <<ans;
    return 0;
}
// NOIP 2024 RP++
// NOIP 2024 RP++
// NOIP 2024 RP++
// NOIP 2024 RP++
// NOIP 2024 RP++
```

---

## 作者：DarkClever (赞：4)

# Add One Edge 2
[F - Add One Edge 2](https://atcoder.jp/contests/abc378/tasks/abc378_f)
## 题意简述
给你一颗由无向边组成的有 $n$ 个节点的树，显然在任意两点上增加一条边都会产生一个环。

问有多少种加边的方式可以产生一个带环的简单图（即没有重边和自环的环），且环上所有点的度数为 $3$。

$3≤n≤2 \times 10^5$

## solution
一道比较容易的树上问题。

注意到每一次增加一条边只会使得两个点的度数增加一，所以我们肯定是要给两个度数为 $2$ 的点连一条边。

并且构成的环内度数都为 $3$，所以选中的两个度数为 $2$ 的点之间路径上的点的度数必须都为 $3$。

考虑使用并查集维护并且统计答案。

对于一个所有点度数都为 $3$ 的连通块，显然与其之中的点直接相连的度数为 $2$ 的点之间形成的点对都符合标准，假设与连通块 $i$ 直相连 $sz_i$ 个点，那么这个连通块对答案的贡献为 $\frac {sz_i \times (sz_i-1)} {2}$。

然后统计并且输出答案就行了( •̀ ω •́ )y。

不过这里有个坑点，考虑到产生的是**简单图**，即没有**重边**和自环，所以两个直接相连的度数为 $2$ 的点是没有贡献的哈。

代码放在下面了，注释个人感觉还是比较详细的哈。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+114;
int n,m,s;
vector<int> e[N];//使用 vector 存边
long long ds[N];//度数
int fa[N];//并查集的 fa
long long sz[N];//与连通块直接相连的度数为 2 的点的数量
int find(int x){//并查集板子
    if(fa[x]==x)return x;
    return fa[x] = find(fa[x]);
}
void dfs1(int x,int f){//
    for(int xx:e[x]){
        if(xx!=f){
            dfs1(xx,x);
            if(ds[x]==2 && ds[xx]==3){//度数为 2 的点对它儿子有贡献
                sz[find(xx)]++;
            }else if(ds[xx]==2 && ds[x]==3){//如果儿子的度数为 2 则它对自己有贡献
                sz[find(x)]++;
            }
            if(ds[x]==3 && ds[xx]==3){//度数为 3 的点之间要合并哈
                sz[find(x)] += sz[find(xx)];//合并的时候要把 sz 一同合并
                fa[find(xx)] = find(x);
            }
        }
    }
}
int main() {
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)fa[i] = i;//初始化~~~
    for(int i=1;i<=n-1;i++){
        int x,y;//输入边
        cin>>x>>y;
        e[x].push_back(y);
        e[y].push_back(x);
        ds[x]++;
        ds[y]++;
    }
    long long ans = 0;
    dfs1(1,0);
    for(int i=1;i<=n;i++){
        int anc = find(i);//所在的连通块
        if(anc == i){
            ans+=(sz[anc]*(sz[anc]-1))/2;//统计答案
        }
    }
    while(1){//qwq（嘻嘻）
      cout<<ans<<endl;//输出答案
    }
    return 0;
}
```

---

## 作者：Dtw_ (赞：3)

# 题意
有一颗树，求有多少种方案 $(u, v)$ 使得将 $(u, v)$ 连起来后这个环上的点的度数都为 $3$。

# Solution
考虑转化题意，就是让求一条链，使得链的两端的度数为 $2$，中间点的度数为 $3$。

那么我们可以统计满足要求的端点的数量然后从数量里任选 $2$ 个，组合数就行。

考虑如何求端点的数量？考虑如果遇到一个度数为 $3$ 的点，那么他一定可以向外扩展，直到遇到度数为 $2$ 的点的时候停止。所以我们可以从一个度数为 $3$ 的点开始向外走，此时他的儿子有 $4$ 种情况：

* 走过了
* 度数为 $2$
* 度数为 $3$
* 度数为其他的数

那么这 $4$ 种情况显然的对于第一种和第四种都是不做任何操作。对于第二种则是记录数量，对于第三种则是继续往下 dfs。

有一个问题，就是起点的选择。我们只能选择度数为 $3$ 的点作为起点，不可以用度数为 $2$ 的点作为起点。

因为度数为 $2$ 的点向所有儿子拓展，但是这个点的左边和右边因为中间这个点的度数为 $2$ 所以不可以走，那答案也不会记录，但是这样答案会被记录，所以算多了。

# Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 1e6 + 10;

bool vis[N];

int n, cnt;

vector<int> G[N]; 

void dfs(int u)
{
	vis[u] = 1;
	for (auto v : G[u])
	{
		if (vis[v]) continue;
		if (G[v].size() == 2) cnt++;
		if (G[v].size() == 3) dfs(v);
	}
}

signed main()
{
	fst
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	int res = 0;
	for (int i = 1; i <= n; i++)
	{
		if (G[i].size() != 3 || vis[i]) continue;
		cnt = 0;
		dfs(i);
		res += cnt * (cnt - 1) / 2;
	}
	cout << res;
	return 0;
}



```

---

## 作者：qfy123 (赞：3)

# Solution
我们考虑用并查集维护度数为 $3$ 的连通块，并同时统计对于一个度数**全**为 $3$ 的连通块，与其**直接相连**的度数为 $2$ 的点的个数。最后对于每个度数全为 $3$ 的连通块，若他有 $cnt$ 个与其直接相连的度数为 $2$ 的点，那就对答案有 $\frac{cnt \times (cnt - 1)}{2}$ 的贡献，累加起来即可。
# Code

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ull unsigned long long
#define ri register int
#define rep(i,j,k) for(ri i=(j);i<=(k);++i) 
#define per(i,j,k) for(ri i=(j);i>=(k);--i)
#define repl(i,j,k,l) for(ri i=(j);(k);i=(l))
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define pc(x) putchar(x)
#define fir first
#define se second 
#define MP pair<int,int>
#define PB push_back
#define lson p << 1
#define rson p << 1 | 1
using namespace std;
char BUFFER[100000],*P1(0),*P2(0);
#define gtc() (P1 == P2 && (P2 = (P1 = BUFFER) + fread(BUFFER,1,100000,stdin), P1 == P2) ? EOF : *P1++)
inline int R(){
    int x;char c;bool f = 0;
	while((c = gtc()) < '0') if(c == '-') f = 1;
	x = c ^ '0';
	while((c = gtc()) >= '0') x = (x << 3) + (x << 1) + (c ^ '0');
	return f?(~x + 1):x;
}
inline void O(int x){
    if(x < 0) pc('-'),x = -x;
    if(x < 10) pc(x + '0');
    else O(x / 10),pc(x % 10 + '0');
}
inline void out(int x,int type){
	if(type == 1) O(x),pc(' ');
	if(type == 2) O(x),pc('\n');
	if(type == 3) O(x);
}
inline void OI(){
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
const int N = 2e5 + 10;
struct E{
	int to, nxt;
}e[N << 1];
int head[N << 1], n, tot, fa[N], siz[N], ans, deg[N];
int find(int x){
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void add(int x, int y){
	e[++tot].to = y;
	e[tot].nxt = head[x];
	head[x] = tot;
}
void dfs(int x, int ff){
	repl(i, head[x], i, e[i].nxt){
		int v = e[i].to;
		if(v == ff) continue;
		dfs(v, x);
		int fx = find(x), fy = find(v);
		if(deg[x] == 3 && deg[v] == 2) siz[fx]++;
		//若 x 的度数为 3，v 的度数为 2，则 x 所在的连通块 直接连接的 度数为 2 的点的个数 增加 1
		else if(deg[x] == 2 && deg[v] == 3) siz[fy]++; // 同上
		else if(deg[x] == 3 && deg[v] == 3){ //合并两个度数为 3 的连通块
			siz[fx] += siz[fy];
			fa[fy] = fx;
		}
	}
}
inline void solve(){
	n = R();
    rep(i, 1, n) fa[i] = i;
    rep(i, 1, n - 1){
    	int u = R(), v = R();
    	add(u, v); add(v, u);
    	deg[u]++, deg[v]++; // 计算度数
    }
    dfs(1, 0);
    rep(i, 1, n) if(i == find(i)) ans += siz[i] * (siz[i] - 1) / 2; // 统计答案
    out(ans, 2);
}
signed main(){
    // OI();
    int T = 1;
    // T = R();
	while(T--) solve();
	return 0;
}


```

---

## 作者：WuMin4 (赞：2)

## [[ABC378F] Add One Edge 2](https://atcoder.jp/contests/abc378/tasks/abc378_f)

## 题意

给定一棵树，你需要加入一条边使树成为基环树（即包含恰好一个环的无向连通图），问有多少种加边的方案使环上的点度数都为 $3$。

## 思路

若两个点 $x,y$ 之间连边后满足条件，即环上的点度数都为 $3$，则一定满足点 $x,y$ 的度数为 $2$，$x,y$ 的简单路径经过的点（除了这两个点）的度数为 $3$，因为 $x,y$ 连边后它们的度数会变成 $2+1=3$，就满足了环上的点度数都为 $3$。

有了这个思路后，我们可以找到所有度数为 $3$ 的点并按照原图合并，操作后便会形成一些连通块，然后对于每个连通块找到相连的度数为 $2$ 的点，这些点之间的任意两点连边都可以形成满足条件的环，因为它们之间的简单路径只会经过该连通块中的点（除了这两个点），且连通块中的点在原树上度数都为 $3$。设这些点共有 $x$ 个，则它们两两连边可以产生 $\frac{x\times (x-1)}{2} \pod{x\ge 2}$ 种方案，将所有连通块产生的方案加起来即可得到方案数。

比如对于样例 $3$，该样例输入为：

```
15
1 15
11 14
2 10
1 7
9 8
6 9
4 12
14 5
4 9
8 11
7 4
1 13
3 6
11 10
```

这棵树的形态如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/nxzm90b8.png)

找到所有度数为 $3$ 的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/xhl77eof.png)

可以发现，这些点构成了 $3$ 个连通块，我们对于每个连通块分别处理。

![](https://cdn.luogu.com.cn/upload/image_hosting/63s3lfq6.png)

对于红色的连通块，有 $1$ 个度数为 $2$ 的点相连，所以这个连通块的贡献为 $0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/fm8sa4vp.png)

对于橙色的连通块，有 $3$ 个度数为 $2$ 的点相连，所以这个连通块的贡献为 $3$。

![](https://cdn.luogu.com.cn/upload/image_hosting/cib6gx56.png)

对于绿色的连通块，有 $3$ 个度数为 $2$ 的点相连，所以这个连通块的贡献为 $3$。

最终的答案即为 $3+3=6$。

## 代码

写的很丑，参考意义不大（

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,d[400005],fa[400005],ans;
bool vis[400005],ist[400005];
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
void uni(int x,int y){
	int p1=find(x),p2=find(y);
	if(p1!=p2)
		fa[p1]=p2;
}
vector<int> t[400005],t2[400005];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int x,y,i=1;i<n;i++){
		cin>>x>>y;
		t[x].push_back(y);
		t[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
		if(t[i].size()==3){
			for(int v:t[i])
				if(t[v].size()==3)
					uni(i,v);
		}
	for(int i=1;i<=n;i++)
		if(t[i].size()==3)
			ist[find(i)]=true;
	for(int i=1;i<=n;i++){
		for(int v:t[i])
			if(find(i)!=find(v))
				t2[find(i)].push_back(find(v));
	}
	for(int i=1;i<=n;i++){
		if(!ist[i]) continue;
		int cnt=0;
		for(int v:t2[i]){
			if(t2[v].size()==2)
				cnt++;
		}
		if(cnt>=2)
			ans+=cnt*(cnt-1)/2;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Noah2022 (赞：1)

### 题目大意
  给你一棵树，问有多少种加边方式使得构成环的点度数都为 $ 3 $ 。

### 思路
先找出枚举每个度数为 $ 3 $ 的点，搜索它连着的度数为 $ 2 $ 的点，求出个数，设有 $ N $ 个点，通过组合数这个点的贡献为 $ \sum_{i=1}^{N-1} i $ ，即 $ \frac{n\times (n+1)}{2} $ 。 用 $ sum $ 变量记录，最后输出 $ sum $ 即可。

**十年 OI 一场空，不开 long long 见祖宗。**
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
vector<int> e[maxn];
int du[maxn];
bool vis[maxn];
int dfs(int x){
	if(du[x] != 3)return du[x] == 2; // 度数为2时加1
	vis[x] = true; // 标记避免重复计算
	int ans = 0;
	for(int i:e[x]) // 遍历边
		if(!vis[i])ans += dfs(i); // 计数
	return ans;
}
signed main(){
	int n;
	scanf("%d",&n);
	for(int i = 1;i < n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v),e[v].push_back(u); // 存边
		++du[u],++du[v]; // 记录度数
	}
	long long ans = 0;
	for(int i = 1;i <= n;i++)
		if(!vis[i] && du[i] == 3){
			int x = dfs(i);
			ans += x * (x - 1ll) / 2;
		}
	cout << ans;
}
```

---

## 作者：Chenyanxi0829 (赞：1)

题目相当于要求满足以下条件的点对 $(x,y)$ 的个数：
- $x,y$ 在树上不相邻
- $x,y$ 度数均为 2
- $x$ 到 $y$ 路径上的其他点度数均为 3

所以可以先统计出每个点与之相邻的度数为 2 的点的个数 $c_i$，接着把图中度数不为 3 的点删掉，对于剩下的每个连通块统计出 $c_i$ 总和 $s$，由于不会有点算重（算重了就表示形成了环，不满足树的性质），所以 $s$ 就表示与这个连通块相邻的度数为 2 的点的个数，而这 $s$ 个点内任选两个点都能构成合法的点对，所以答案就是 $\binom{s}{2}$ 之和。

### 代码
其他细节见代码。
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int kMaxN = 2e5 + 100;

int n, c[kMaxN], s;
bool g[kMaxN], v[kMaxN];
long long ans;
vector<int> e[kMaxN];

void dfs(int x) {
  if (g[x] && !v[x]) {
    v[x] = 1, s += c[x];
    for (int i : e[x]) {
      dfs(i);
    }
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    cin >> u >> v, e[u].push_back(v), e[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    if (e[i].size() == 3) {
      g[i] = 1;
      for (int j : e[i]) {
        c[i] += e[j].size() == 2;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (!v[i] && g[i]) {
      s = 0, dfs(i), ans += 1ll * s * (s - 1) / 2;
    }
  }
  cout << ans;
  return 0;
}
```

---

## 作者：xxseven (赞：1)

赛时忘记了新图必须是简单图的条件，$40$ 分钟 $0$ 罚时变为 $70$ 分钟 $4$ 罚时，希望大家引以为戒。

考虑加边的两个顶点，有可能为祖孙关系，有可能分属不同子树。我们考虑树形 DP，在 LCA 处计算贡献。

以下记深度从小到大时度数形如 $3,3,3,2$，且以当前钦定的 LCA 的儿子为链头的链为合法链。

对于祖孙关系的加边，要求 LCA 的度数为 $2$，且整个环为一条合法链加一条新边组成。方案数即为合法链的个数。

对于分属不同子树的加边，要求 LCA 的度数为 $3$，且由两条合法链加一条新边组成。方案数即为选取两条合法链，使链尾分属不同子树的方案数。

我们在 DP 过程中，维护以当前节点为根，合法链的数量即可。

[AC link](https://atcoder.jp/contests/abc378/submissions/59387508)。

---

## 作者：ZhaoV1 (赞：1)

首先，节点的度可以简单表示为该节点的连边数量。  
观察下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/x1379ar0.png)

要使环中每个节点的度都为 $3$，也就是说我们必须要将两个度为 $2$ 且它们之间的所有节点的度为 $3$ 的节点相连才符合条件（环的节点数必须大于 $3$）。该图应连接序号 $1$，$6$ 的节点。

为了求得最多能连多少条符合条件的边，可以从根节点（暂设为 $1$）出发，见到度为 $2$ 的节点就将该节点所连接的所有度为 $3$ 的节点设为 bfs 的起点，在 bfs 中遇到度为 $3$ 就拉进队继续，遇到 $2$ 的就计数加一，否则不进行操作。最后每次 bfs 的计数 $num$ 计算 $\frac{num\times(num-1)}{2}$ 累加即可。

AC Code
---


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
const int N = 2e5+5;
int res = 0;
vector<int> e[N];
bool vis[N];
int de[N];//degree节点的度

void bfs(int s){
	queue<int> que;
	que.push(s);

	int num = 0;
	while(!que.empty()){
		int temp = que.front();
		que.pop();
		if(vis[temp]) continue;
		else vis[temp] = true;

		for(auto it : e[temp]){
			if(de[it]==3) que.push(it);
			else if(de[it] == 2){
				num++;
			}
		}
	}
	res += num*(num-1)/2;
}

void solve(){
	cin >> n;
	for(int i=1,pos1,pos2;i<n;i++){
		cin >> pos1 >> pos2;
		e[pos1].push_back(pos2);
		e[pos2].push_back(pos1);
	}
	for(int i=1;i<=n;i++) de[i] = e[i].size();
	for(int i=1;i<=n;i++){
		if(de[i] == 2){
			for(auto it : e[i]){
				if(de[it]==3 && !vis[it]){
					bfs(it);
				}
			}
		}
	}
	cout << res << '\n';
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	t = 1;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：modfisher (赞：0)

## 思路
显然，我们需要寻找满足下列条件的点对 $(u,v)$：

- $deg_u=deg_v=2$。

- 对于 $u$ 到 $v$ 路径上的所有点（$u,v$ 除外）$x$，$deg_x=3$。

其中，$deg_i$ 表示点 $i$ 的度数。

不妨用并查集把所有度数为 $3$ 的点连起来，称这些连通块为 $3$ 连通块。然后枚举度数为 $2$ 的点，查询与其相邻的 $3$ 连通块有多少个相邻的度数为 $2$ 的结点即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 2e5 + 5;

int fa[maxn], siz[maxn], deg[maxn];
int us[maxn], vs[maxn], c[maxn][2];
ll tag[maxn];

int find(int x){
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
void merge(int x, int y){
	x = find(x), y = find(y);
	if(x == y) return;
	fa[x] = y, siz[y] += siz[x];
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i < n; i ++){
		int u, v;
		scanf("%d %d", &u, &v);
		deg[u] ++, deg[v] ++;
		us[i] = u, vs[i] = v;
	}
	for(int i = 1; i <= n; i ++) fa[i] = i, siz[i] = deg[i] == 3;
	for(int i = 1; i < n; i ++){
		if(deg[us[i]] == 3 && deg[vs[i]] == 3) merge(us[i], vs[i]);
		if(deg[us[i]] == 2){
			if(c[us[i]][0]) c[us[i]][1] = vs[i];
			else c[us[i]][0] = vs[i];
		}
		if(deg[vs[i]] == 2){
			if(c[vs[i]][0]) c[vs[i]][1] = us[i];
			else c[vs[i]][0] = us[i];
		}
	}
	ll ans = 0;
	for(int i = 1; i <= n; i ++){
		if(deg[i] == 2){
			ans += tag[find(c[i][0])], ans += tag[find(c[i][1])];
			if(siz[find(c[i][0])]) tag[find(c[i][0])] ++;
			if(siz[find(c[i][1])]) tag[find(c[i][1])] ++;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Liyunze123 (赞：0)

很容易得出的性质：答案为满足条件的点对 $(i,j)$ 的个数：两个点度数都是二，两个点路径上的点度数是三。

将这些点对按照最近公共祖先的度数分类：二或三。

在解决问题之前，先求出 $dp_i$ 和 $f_i$。$dp_i$ 是 $i$ 的子树内的点 $j$，满足 $i$ 到 $j$ 除了 $i$ 和 $j$ 以外其他点度数为三，$j$ 的度数为 $2$ 的 $j$ 的个数。$dp_i$ 是所有儿子的 $f_i$ 之和。当 $i$ 的度数为 $3$ 时，$f_i$ 就是 $dp_i$。当 $i$ 的度数为 $2$ 时，$f_i$ 是 $1$。其他情况，$f_i$ 都是零。

接下来求答案了：对于最近公共祖先度数是二的点，答案就是 $dp_i$；对于三，答案是对于所有儿子，$f_i \times (s-f_i)$，$s$ 是所有儿子的 $f_i$ 之和。

注意最近公共祖先度数是三的点答案要除以二。

上代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,a,b,f[200010],dp[200010],e[400010],ne[400010],h[200010],d[200010],idx;
long long ans,N;
void add(int a,int b){e[idx]=b,ne[idx]=h[a],h[a]=idx++;}
int dfs(int i,int fa){
	f[i]=fa;
	for(int w=h[i];~w;w=ne[w])if(e[w]!=fa)dp[i]+=dfs(e[w],i);
	if(d[i]==3)return dp[i];
	if(d[i]==2)return 1;
	return 0;
}
int main(){
	scanf("%d",&n),memset(h,-1,sizeof(h));
	for(int w=1;w<n;w++)scanf("%d%d",&a,&b),add(a,b),add(b,a),d[a]++,d[b]++;
	dfs(1,0);
	for(int w=1;w<=n;w++)
		if(d[w]==3){
			int s=0;
			for(int x=h[w];~x;x=ne[x])if(d[e[x]]==2&&e[x]!=f[w])s++;else if(d[e[x]]==3&&e[x]!=f[w])s+=dp[e[x]];
			for(int x=h[w];~x;x=ne[x])if(d[e[x]]==2&&e[x]!=f[w])ans+=s-1;else if(d[e[x]]==3&&e[x]!=f[w])ans+=1ll*dp[e[x]]*(s-dp[e[x]]);
		}else if(d[w]==2)N+=dp[w];
	for(int w=1;w<=n;w++)for(int x=h[w];~x;x=ne[x])if(e[x]!=f[w]&&d[e[x]]==2&&d[w]==2)N--;
	printf("%lld",ans/2+N);
	return 0;
}
```

---

## 作者：zhouruoheng (赞：0)

先理解下题意，要满足条件，就是找到两个度数为 $2$ 的点，这两个点的路径上全是度数为 $3$ 的点，将这两个点连接即可。

那么考虑暴力查找，对于每个度数为 $2$ 的点，找到另一个度数为 $2$ 的点，只有下一个点度数为 $3$ 才能走过去。显然这样的做法是 $O(n^2)$ 的，也很容易被卡。

再进一步思考，将路径换成两点到最近公共祖先的路劲拼起来，而且最近公共祖先的度数必须是 $3$。那么就可以枚举所有度数为 $3$ 的点作为根节点，搜索度数为 $2$ 的点的个数 $sum$，贡献就是 $sum \times (sum-1)/2$，标记经过的所有度数为 $3$ 的点，不用重复计算。

复杂度为 $O(n)$。
``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>

using namespace std;
typedef long long ll;
const int N=2e5+5;
int n;
vector<int> g[N];
bool v[N];
int dfs(int x,int fa)
{
    int ret=0;
    v[x]=1;
    for(int i=0;i<g[x].size();i++)
    {
        int y=g[x][i];
        if(y==fa) continue;
        if(g[y].size()==2) ret++;
        else if(g[y].size()==3) ret+=dfs(y,x);
    }
    return ret;
}
void solve()
{
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    ll ans=0;
    for(int i=1;i<=n;i++) 
    {
        if(g[i].size()==3&&!v[i])
        {
            ll x=dfs(i,0);
            ans+=x*(x-1)/2;
        }
    }
    cout<<ans<<'\n';
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif 
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    solve();
    return 0;
}

```

---

## 作者：Redamancy_Lydic (赞：0)

题目让我们求一棵给定的树有多少环上点度数均为 $3$ 的基环树。

容易想到，新添加的环连接的两个节点一定都是度数为 $2$ 的点，且这两个点之间所有节点的度数均为 $3$。

所以我们可以找到每一个由度数为 $3$ 的点组成的连通块，并对于每一个连通块找到它的边缘有几个度数为 $2$ 的点。

设度数为 $2$ 的点的个数为 $sum$，那么该连通块能够产生的贡献显然就是这 $sum$ 个点中选任意两个点的方案数，显然就是 $sum\cdot(sum-1)\over 2$。

找连通块的时候我们用一个 $vis$ 数组标记已经找过的点，每次只对度数为 $3$ 且之前没被标记的点进行搜索，这样可以保证不重不漏。

[提交记录](https://atcoder.jp/contests/abc378/submissions/59412864)

---

## 作者：cyq32ent (赞：0)

题意：树上有 $N$ 个点，连一条边，求有多少连边方法使得出现一个度数全为 $3$ 的环。

连边的点度数会加一，所以连的两个点必定度数都是 $2$。考虑某个点的子树，如果在子树内可以连出一个环，而且经过这个点，那么这个点将环分为两条链，每一条满足以下条件：互不重合；除了最下方的点度数为 $2$ 之外的点度数都为 $3$。直接dfs即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int f0[202020],N,deg[202020];long long ans;
vector<int>G[202020];
void dfs(int u,int p){
	for(auto v:G[u])if(v!=p)dfs(v,u);
	if(deg[u]==2){
		f0[u]=1;
		for(auto v:G[u])if(v!=p)if(deg[v]==3)ans+=f0[v];
	}
	else if(deg[u]==3){
		for(auto v:G[u])if(v!=p)f0[u]+=f0[v];
		int tmp=0;
		for(auto v:G[u]){
			if(v==p)continue;
			ans+=(f0[v]*tmp);
			tmp+=f0[v];
		}
	}
}
int main(){
	cin>>N;for(int i=1,u,v;i<N;i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
		deg[u]++,deg[v]++;
	}dfs(1,0);
	cout<<ans<<endl;
	//for(int i=1;i<=N;i++)cout<<f0[i]<<' ';
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

## [ABC378F] Add One Edge 2

> 比较水的一个 F。

考虑加一条边时，一定会增加两个点的度数，并且这两个点一定会在环上，所以原图上这两个点的度数一定为 $2$。

同时，需要保证这两个点之间所有点都是 $3$ 度点，所以可以直接遍历每一个所有点度数都为 $3$ 的子树，统计周围有多少个 $2$ 度点与这个子树相连（记为 $c$），则环上的点都是这个子树的点的方案数即为 $c \choose 2$。最终把每个子树答案求和即可。

这样计数不会重复，不用考虑除去重边，时间复杂度 $O(n)$。

代码：[赛时提交记录](https://atcoder.jp/contests/abc378/submissions/59375838)。

---

## 作者：under_the_time (赞：0)

## 题意

> 给定一棵 $n$ 个点的树，现在给这棵树添加且仅添加一条边（**不能重边**），此时树上会出现一个环；求添加后满足环上点的度数都是 $3$ 的方案数。
>
> $3\le n\le 2\times 10^5$。

## 题解

记 $u$ 的深度为 $dep_u$、度数为 $d_u$。钦定 $1$ 号点为根，那么对于点对 $(u,v)$，不妨令 $dep_u\le dep_v$，进行分类讨论：

- 如果 $u$ 是 $v$ 的祖先，那么环就由从 $u$ 到 $v$ 的直的链和 $(u,v)$ 这条边组成；这种情况下，要满足 $d_u=d_v=2$ 且链上其他点度数为 $3$。
- 否则，环由从 $u$ 到 $\operatorname{lca}(u,v)$、从 $v$ 到 $\operatorname{lca}(u,v)$ 两条直的链和 $(u,v)$ 这条边组成；这种情况下，要满足 $d_u=d_v=2$、$d_{\operatorname{lca}(u,v)}=3$、链上其他点度数为 $3$。

对于点 $u$，我们考虑这个环在 $u$ 子树内且包含 $u$ 的方案数。按照 $d_u$ 进行分类讨论：

- 若 $d_u=2$，那么对于一个在 $u$ 子树内的点 $v$，连一条 $(u,v)$ 的边合法当且仅当 $d_v=2$ 且从 $u$ 到 $v$ 链上的其他点度数为 $3$；
- 若 $d_u=3$，那么对于两个在 $u$ 子树内的点 $v_1,v_2$，连一条 $(v_1,v_2)$ 的边合法当且仅当 $d_{v_1}=d_{v_2}=2$ 且从 $u$ 到 $v_1$ 和到 $v_2$ 的两条链上其他点的度数为 $3$；
- 否则 $u$ 就不能出现在任何一个环上，一定不合法。

可以发现我们要统计 $u$ 子树内这一类点的个数：

![](https://cdn.luogu.com.cn/upload/image_hosting/xch5hy4y.png)

即图中绿色点的数量，它们满足自己度数为 $2$，且从自己的父亲到点 $u$ 上的所有点（除了点 $u$）度数都为 $3$（图中蓝色的点）。

我们考虑树形 dp，令 $f(u)$ 表示考虑到点 $u$ 时我们要记录的点的数量。一个细节：因为不能有重边，所以 $f(u)$ 不能算上点 $u$。仍然按照 $d_u$ 分情况计算答案：

- 若 $d_u=3$，令 $u$ 的子树集合为 $S_u$，那么 $f_u=\sum_{v\in S_u}f_v+[d_v=2]$（这个时候不是和 $u$ 连边，所以与合法的 $v$ 连也是可以的），计算答案时我们依次考虑 $u$ 的每个孩子 $v$，令在 $v$ 之前考虑的所有孩子的 $f$ 值（包括 $[d_v=2]$ 的和）之和为 $s$，那么此时对答案的贡献即为 $s\times (f_v+[d_v=2])$。
- 若 $d_u=2$，那么 $f_u=0$ 因为 $d_u\ne 3$，对答案的贡献即为 $\sum_{v\in S_u}f_v$​。
- 否则同样 $f_u=0$，此时对答案无贡献。

时间复杂度 $O(n)$。

## 代码

```cpp
// Problem: F - Add One Edge 2
// Contest: AtCoder - AtCoder Beginner Contest 378
// URL: https://atcoder.jp/contests/abc378/tasks/abc378_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Good luck to the code >w<
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define open(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define abs(x) (((x) > (0)) ? (x) : (-(x)))
#define lowbit(x) ((x) & (-(x)))
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
#define BCNT __builtin_popcount
#define cost_time (1e3 * clock() / CLOCKS_PER_SEC)
mt19937 rnd(time(0));
const int maxn = 2e5 + 5;
int d[maxn];
namespace Graph {
	struct Edge { int to, nxt; } e[maxn << 1];
	int head[maxn], ecnt = 0;
	void addEdge(int u, int v) {
		e[++ ecnt] = Edge { v, head[u] };
		head[u] = ecnt;
	}
} using namespace Graph;
int n; ll f[maxn], ans = 0;
void dfs(int u, int fa) {
	if (d[u] == 2) {
		f[u] = 0;
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (v == fa) continue;
			dfs(v, u), ans += f[v];
		} 
	} else if (d[u] == 3) {
		f[u] = 0; ll all = 0;
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (v == fa) continue;
			dfs(v, u); if (d[v] == 2) f[v] ++;
			ans += all * f[v];
			all += f[v], f[u] += f[v];
		}
	} else {
		f[u] = 0; for (int i = head[u]; i; i = e[i].nxt)
			if (e[i].to != fa) dfs(e[i].to, u);
   	}
}
int main() {
	scanf("%d", &n);
	for (int u, v, i = 1; i < n; i ++)
		scanf("%d %d", &u, &v), d[u] ++, d[v] ++, addEdge(u, v), addEdge(v, u);
	dfs(1, 0);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：liuziqin (赞：0)

## 思路

对于任意合法点对 $(u,v)$，仅当在路径 $(u,v)$ 上的每一个点（除去点 $u$ 和点 $v$）的度数都为 3 且点 $u$ 和点 $v$ 的度数为 2，因此点 $u$ 和点 $v$ 一定与同一个内部所有点的度数都为 3 的联通块直接相连。

对于一个每内部所有点度数都为 3 的联通块，任意两个在联通块内的点都有且仅有一条路径，因此，我们可以对这个联通块进行缩点操作。

因此我们只需计算出每一个合法联通块直接相邻的度数为 2 的点的数量，最后用排列组合计算出贡献即可。

## Code

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200005;
struct edge{
	int to,nxt;
}e[N<<1];
int head[N],cnt;
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int fa[N];
void init(int n){
	for(int i=1;i<=n;i++)fa[i]=i;
}
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y){
	int p=find(x),q=find(y);
	if(p==q)return ;
	fa[p]=q;
}//并查集
int du[N],tot[N];
signed main(){
	int n;
	cin>>n;
	init(n);
	for(int i=1;i<n;i++){
		 int x,y;
		 cin>>x>>y;
		 add(x,y);
		 add(y,x);
		 du[x]++,du[y]++;//预处理度数
	}
	for(int i=1;i<=n;i++){
		if(du[i]==3){
			for(int j=head[i];j;j=e[j].nxt){
				int v=e[j].to;
				if(du[v]==3)merge(i,v);
			}
		}
	}//用并查集缩点
	for(int i=1;i<=n;i++){
		if(du[i]==2){
			for(int j=head[i];j;j=e[j].nxt){
				int v=e[j].to;
				if(du[v]==3)tot[find(v)]++;
			}
		}
	}//计算出与每一个联通块直接相邻的度数为2的点数
	int ans=0;
	for(int i=1;i<=n;i++)ans+=tot[i]*(tot[i]-1)/2;//计算贡献
	cout<<ans<<"\n";//输出
	return 0;
}
```

---

## 作者：bryce (赞：0)

## [F - Add One Edge 2](https://atcoder.jp/contests/abc378/tasks/abc378_f)
### 思路
题目要求连边后这个环的所有点的度数为 $3$，那么连接的这两个点的度数一定为 $2$，其它环上的点的度数都为 $3$，那么在一个度数为 $3$ 的点开始遍历，找到连续的度数为 $3$ 的点，直到找不了，于是这些度数为 $3$ 的点相互连通，它们上面连接的度数为 $2$ 的点任意两两连接都能形成一个符合题目要求的环，设这个连通的度数为 $3$ 的点上面的度数为 $2$ 的点的个数为 $m$，那么答案加上 $\frac{m\times (m - 1)}{2}$。
### 代码
```cpp
#include<iostream>
#define int long long

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}

const int N = 2e5 + 10;
int n, res, ans;
struct edge{
    int v, nxt;
}e[N << 1];
int head[N], cnt;
int in[N];
void add(int u, int v){
    e[++cnt] = (edge){v, head[u]};
    head[u] = cnt;
}
bool vis[N];
void solve(int u){
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if (vis[v]) continue;
        if (in[v] == 3){
            solve(v);
        }
    }
    for (int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if (!vis[v] && in[v] == 2) res++;
    }
}

signed main(){
    n = read();
    for (int i = 1; i < n; i++){
        int u = read(), v = read();
        add(u, v), add(v, u);
        in[u]++, in[v]++;
    }
    for (int i = 1; i <= n; i++){
        if (in[i] == 3 && !vis[i]){
            res = 0;
            solve(i);
            ans += res * (res - 1) / 2;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：RAND_MAX (赞：0)

#### 题意简述
给一棵 $n$ 个节点的树，加一条边会让树上出现一个环，求有多少种加边方案使环上的点度数均为 3。

#### 思路
转化题意，想要 $u,v$ 加边后环上度数均为 3，那么要满足 $u,v$ 的度数均为 2 且树上 $u,v$ 的路径（不包括 $u,v$）上的点度数均为 3。

我们记 $f_i$ 为以 $i$ 为根的子树中满足点度数为 2 且点到根节点路径上的点度数均为 3 的点个数。\
进行分类讨论，若 $i$ 的度数为 2，那么点 $i$ 到其子树内满足条件的点均可连边，故答案可以加上 $f_i$。若 $i$ 的度数不为 3，由于 $f_i$ 无法转移至其父亲节点，所以将 $f_i$ 记为 0，方便转移。注意若 $i$ 的度数为 2，要将 $f_i$ 记为 1，因为点 $i$ 满足条件。\
若 $i$ 的度数为 3，$i$ 中不同子树中满足条件的点均可连边。我们设 $s=\sum\limits_{j\in son(i)}f_j$，运用排列组合，答案要加上 $\frac{\sum\limits_{j\in son(i)}((s-f_j)\times f_j)}{2}$。又因 $f_i$ 可以转移至父亲节点，故要将 $f_i$ 记为 $s$。

递归处理即可，注意已经连边的两点不能再次连边，统计答案时需要减去。

#### 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
#define R read()
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-48,c=getchar();
	return x*f;
}
void write(int x,char xx)
{
	static int st[35],top=0;
	if(x<0){x=-x;putchar('-');}
	do
	{
		st[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(st[--top]+48);
	putchar(xx);
}
int n,in[200010],f[200010],ans;
vector<int>g[200010];
void dfs(int x,int fa)
{
	int nnn=0,sum=0;
	for(int i:g[x])
	{
		if(i==fa) continue;
		dfs(i,x);
		f[x]+=f[i];
		nnn+=(in[i]==2);
	}
	if(in[x]==2) sum+=f[x]-nnn;
	if(in[x]!=3) f[x]=0;
	else
	{
		for(int i:g[x])
		{
			if(i==fa) continue;
			sum+=(f[i])*(f[x]-f[i]);
		}
		sum>>=1;
	}
	if(in[x]==2) f[x]=1;
	ans+=sum;
}
signed main()
{
	n=R;
	for(int i=1,x,y;i<n;i++) x=R,y=R,g[x].push_back(y),g[y].push_back(x),in[x]++,in[y]++;
	dfs(1,0);
	cout<<ans<<'\n';
 	return 0;
}
```

---

## 作者：xixisuper (赞：0)

# AT_abc378_f [ABC378F] Add One Edge 2 题解

比 E 简单不少。

## 思路

注意到加一条边只会使两个点的度数都增加 $1$，所以我们能够注意到这样几条性质：

- 加的那条边连接的两个点的度数都为 $2$。
- 这两个点直连到同一个全部都由度数为 $3$ 的点构成的连通块里。

不难发现能够加这条边与这两个点满足上述两条性质互为充要条件，所以我们就能够得到这一题的做法：

- 找到所有极大的由度数为 $3$ 的点构成的连通块，记这个连通块直连的度数为 $2$ 的点的个数为 $cnt$，则对答案的贡献为 $\frac{cnt\cdot (cnt-1)}{2}$。

跑一次 dfs 即可，时间复杂度 $O(n)$。

## 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
const ll N=2e5+10;
vector<ll> e[N];
ll n,deg[N],ans,cnt[N];
void dfs(ll u,ll f){
	ll lz=e[u].size();
	for(ll i=0;i<lz;i++){
		if(e[u][i]==f) continue;
		dfs(e[u][i],u);
		if(deg[u]==3){
			if(deg[e[u][i]]==3) cnt[u]+=cnt[e[u][i]];
			else if(deg[e[u][i]]==2) cnt[u]++;
		}
		else{
			if(deg[u]==2) ans+=cnt[e[u][i]]*(cnt[e[u][i]]+1)/2;
			else ans+=cnt[e[u][i]]*(cnt[e[u][i]]-1)/2;
		}
 	}
	if(deg[u]!=3) cnt[u]=0;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
		deg[u]++,deg[v]++;
	}
	dfs(1,0);
	if(cnt[1]) ans+=cnt[1]*(cnt[1]-1)/2;
	cout<<ans;
	return 0;
} 
```

---

## 作者：Binah_cyc (赞：0)

感觉 F 难度大于 E 啊。

题目要求加一条边，使得环上的点度数均为 $3$。

简单分析，可以得知，我们加的边合法，当且仅当它的两个端点度数为 $2$，并且两点间路径上所有的点度数均为 $3$。

因此，我们统计每一个度数为 $3$ 的点构成的联通块与多少个度数为 $2$ 的点直接相连，从这些点中任选两个就是一组方案。正确性显然。

代码：
```
// Problem: F - Add One Edge 2
// Contest: AtCoder - AtCoder Beginner Contest 378
// URL: https://atcoder.jp/contests/abc378/tasks/abc378_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Author: Binah_cyc

#include<bits/stdc++.h>
using namespace std;
constexpr int N=2e5+5;
#define int long long
int n,deg[N],ans;

int head[N],tot;
struct Node{int nxt,to;}edge[N<<1];
void add(int u,int v){edge[++tot]=Node{head[u],v},head[u]=tot;}

bool vis[N];
int cnt;
queue<int> q;
void bfs(int start)
{
	q.push(start);
	vis[start]=1;
	while(q.size())
	{
		int now=q.front();
		q.pop();
		for(int i=head[now];i;i=edge[i].nxt)
		{
			if(deg[edge[i].to]==2) cnt++;
			if(deg[edge[i].to]==3&&!vis[edge[i].to]) vis[edge[i].to]=1,q.push(edge[i].to);
		}
	}
}
signed main(signed argc,char** argv)
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1,x,y;i<n;i++) cin>>x>>y,deg[x]++,deg[y]++,add(x,y),add(y,x);
	for(int i=1;i<=n;i++) if(deg[i]==3&&!vis[i]) cnt=0,bfs(i),ans+=cnt*(cnt-1)/2;
	cout<<ans;
	return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

给定一个 $n$ 个点的树，你需要连接一条边，使得树转换成一个**简单图**，且环上所有点的度数均为 $3$，输出连边的方案数。

$3\leq n\leq 2\times 10^5$。

## 思路

我们发现原问题等价于选择一个长度大于 $1$ 的路径，使得路径端点度数为 $2$，路径上的其余点路径为 $3$。

考虑树形 dp，我们在路径的 LCA 处统计答案。设 $f(i)$ 表示以 $i$ 为根的链中，最深的一个点度数为 $2$，其余点度数为 $3$，这样的路径数量。

考虑转移。首先如果点 $u$ 度数不为 $2$ 或 $3$，则 $f(u)=0$，如果 $u$ 度数为 $2$，则度数为 $1$，否则为其子节点的 $f$ 之和。

然后我们在此统计答案，对于度数为 $2$ 的点，每个子节点的 $f$ 都会对答案产生贡献。对于度数为 $3$ 的点，我们将两两子节点的路径合并，它们都是答案。

注意判掉连出重边的情况。

时间复杂度 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int n;
vector<int> g[N];

int f[N], deg[N], ans;

void dfs(int u, int fa){
    deg[u] = g[u].size();
    if(deg[u] == 2) f[u] = 1;
    for(int v : g[u]){
        if(v == fa) continue;
        dfs(v, u);
        if(deg[u] == 3){
            ans += f[u] * f[v];
            f[u] += f[v];
        }
        if(deg[u] == 2){
            ans += f[v];
        }
        if(deg[u] == 2 && deg[v] == 2) ans--;
    }
    // cerr << u << ' ' << f[u] << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<n;i++){
        int u, v; cin >> u >> v;
        g[v].emplace_back(u); g[u].emplace_back(v);
    }
    dfs(1, 0);
    cout << ans << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

