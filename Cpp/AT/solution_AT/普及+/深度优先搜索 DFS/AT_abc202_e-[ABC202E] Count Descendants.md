# [ABC202E] Count Descendants

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc202/tasks/abc202_e

$ N $ 頂点の根付き木があり、頂点は $ 1,\ 2,\ \dots,\ N $ と番号付けられています。

頂点 $ 1 $ が根であり、頂点 $ i\ \,\ (2\ \leq\ i\ \leq\ N) $ の親は $ P_i $ です。

$ Q $ 個のクエリが与えられます。$ i\ \,\ (1\ \leq\ i\ \leq\ Q) $ 番目のクエリでは、整数 $ U_i,\ D_i $ が与えられるので、次の条件を全て満たす頂点 $ u $ の個数を求めてください。

- $ u $ から根への最短パス上（端点も含む）に頂点 $ U_i $ が存在する。
- $ u $ から根への最短パスに含まれる辺の数が**ちょうど** $ D_i $ である。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ P_i\ <\ i $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ U_i\ \leq\ N $
- $ 0\ \leq\ D_i\ \leq\ N\ -\ 1 $
- 入力は全て整数である。

### Sample Explanation 1

$ 1 $ 番目のクエリでは、頂点 $ 4,\ 5,\ 7 $ が条件を満たします。 $ 2 $ 番目のクエリでは、頂点 $ 7 $ のみが条件を満たします。 $ 3 $ 番目、$ 4 $ 番目のクエリでは、条件を満たす頂点は存在しません。 !\[sample\](https://img.atcoder.jp/ghi/abc202\_e\_sample\_00.jpg)

## 样例 #1

### 输入

```
7
1 1 2 2 4 2
4
1 2
7 2
4 1
5 5```

### 输出

```
3
1
0
0```

# 题解

## 作者：Ray662 (赞：15)

[洛谷 传送门](https://www.luogu.com.cn/problem/AT_abc202_e) | [AtCoder 传送门](https://atcoder.jp/contests/abc202/tasks/abc202_e)

[更好的阅读体验](https://www.luogu.com.cn/blog/sunrize/solution-at-abc202-e)

~~这题的翻译是我写的。~~

没人写题解，那我就来发一篇吧~

题目大意：

- 给出一个 $n$ 个点的有根树，节点编号为 $1, 2, \cdots n$，树根为 $1$，第 $i$（$2 \le i \le n$）号节点的父亲是 $p_i$。

- 给出 $q$ 个查询，第 $i$ 个查询包含 $a_i, b_i$，计算满足以下条件的点 $u$ 的个数：

	1. $a_i$ 位于 $u$ 到 $1$ 的最短路径上（端点也算）；
    
    2. $u$ 到根上的路径恰好有 $b_i$ 条边。

- $n, q \le 2 \times 10^5, 0 \le b_i < n$。

---

### 分析

**时间戳**的模板题。

- **WHAT：什么是时间戳**

可以理解为，每个节点有两个属性 $Tin_i, Tout_i$。

那么对于一个节点 $u$ 以及它的任意一个儿子 $v$，都有 $Tin_u \le Tin_v, Tout_u \ge Tout_v$。

也就是晚辈 $[Tin_i, Tout_i]$ 是包含于祖先的区间内的。

- **HOW：怎么算时间戳**

DFS。

我们先开一个全局变量 $timer$，表示当前的时间戳。

每次搜索到一个点的时候，`Tin[u] = ++ timer`。

当遍历完当前点的儿子时，`Tout[u] = ++ timer`。

因为是深搜，所以晚辈的 $Tin$ 一定不小于祖先的 $Tin$，$Tout$ 同理。

```cpp
void dfs(int u, int depth) {
	Tin[u] = timer ++ ;
	D[depth].push_back(Tin[u]);  // 还要把同一层的点记录一下
	for (int i = 0; i < e[u].size(); i ++ )  dfs(e[u][i], depth + 1);
	Tout[u] = timer ++ ;
}
```

---

### 查询

性质 $2$ 等价于什么？$u$ 的深度是 $b_i$！

由于我们在 DFS 的时候把同一层的点的时间戳都存进了 vector，所以只需要查找同一层的点中，$\ge Tin_{a_i}$ 且 $\le Tout_{a_i}$ 的点都符合条件！

继续考虑。由于是 DFS，所以同一个 vector 中的数一定是有序的！lower_bound！

```cpp
cin >> u >> depth;
cout << lower_bound(D[depth].begin(), D[depth].end(), Tout[u]) - lower_bound(D[depth].begin(), D[depth].end(), Tin[u]) << endl;
```

于是，此题便可以在 $O(q \times \log n)$ 的复杂度内解决。

---

### 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, q, fa[N], Tin[N], Tout[N], timer;
vector<int> D[N], e[N];
void dfs(int u, int depth) {
	Tin[u] = timer ++ , D[depth].push_back(Tin[u]);
	for (int i = 0; i < e[u].size(); i ++ )  dfs(e[u][i], depth + 1);
	Tout[u] = timer ++ ;
}
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	for (int i = 2, fa; i <= n; i ++ )  cin >> fa, e[fa].push_back(i);
	dfs(1, 0);
	int u, depth;
	cin >> q;
	while (q -- ) {
		cin >> u >> depth;
		cout << lower_bound(D[depth].begin(), D[depth].end(), Tout[u]) - lower_bound(D[depth].begin(), D[depth].end(), Tin[u]) << endl;
	}
	return 0;
}
```

---

### 拓展

时间戳还可以求 LCA。

原理是倍增，倍增找到深度最低的且不是 $v$ 的祖先的 $u$ 的祖先 $w$，那么 $w$ 的父亲便是 $u, v$ 的 LCA。

```cpp
void dfs(int u, int fa)
{
	// UP[u][i]：u 节点往上跳 2^i 的点
	Tin[u] = ++ timer, UP[u][0] = fa;
	if (u != fa)  dep[u] = dep[fa] + 1;
	_for (i, 1, L)  UP[u][i] = UP[UP[u][i - 1]][i - 1];  // L = log(n)
	for (int v : G[u])  if (v != fa)  dfs(v, u);
	Tout[u] = ++ timer;
}
inline bool is_Ancestor(int u, int v) { return Tin[u] <= Tin[v] && Tout[u] >= Tout[v]; }
inline int LCA(int u, int v) {
	if (dep[u] > dep[v])  swap(u, v);
	if (is_Ancestor(u, v))  return u;
	_all(i, L, 0)  if (! is_Ancestor(UP[u][i], v)) u = UP[u][i];
	return UP[u][0];
}
```

$$
  \color{red}\Large\texttt{THE END}
$$

---

## 作者：_Ponder_ (赞：5)

[Count Descendants](https://www.luogu.com.cn/problem/AT_abc202_e)

### 题目大意

给定一颗以 $1$ 为根的树，多次询问求某点的子树中深度为给定值的点的个数。

### 思路分析

对于每个深度开一个 `vector`，从大到小存下这个深度的所有点的 dfs 序开始值和结束值，询问时只需要在对应深度的 `vector` 中二分作差即可。

### 代码

```
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
const int N=400100;

int to[N],nxt[N],head[N];
int n,idx=1,cnt,q,in1,in2;
int dfn[N],dep[N],End[N];

vector<int> v[N];

void add(int u,int v){
    idx++;to[idx]=v;nxt[idx]=head[u];head[u]=idx;
}

void dfs(int s,int fa){
    dfn[s]=++cnt;
    dep[s]=dep[fa]+1;
    v[dep[s]].push_back(dfn[s]);
    for(int i=head[s];i;i=nxt[i]){
        int v=to[i];
        if(v==fa) continue;
        dfs(v,s);
    }
    End[s]=++cnt;
}

int main(){
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        scanf("%d",&in1);
        add(i,in1);add(in1,i);
    }
    dfs(1,0);
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&in1,&in2);in2++;
        cout<<lower_bound(v[in2].begin(),v[in2].end(),End[in1])-lower_bound(v[in2].begin(),v[in2].end(),dfn[in1]-1)<<'\n';
    }
    return 0;
}
```

---

## 作者：fengenrong (赞：5)

### 题意

有一棵 $N$ 个点的有根树，其中 $1$ 号节点为根，点 $i$ 的父亲为 $P_i$。

有 $Q$ 次查询，每次查询给出两个数 $U_i$ 和 $D_i$，表示在 $U_i$ 的子树中，到根的最短路径刚好经过 $D_i$ 条边的点有多少个？
 
### 思路

这道题，我们可以用利用两次搜索，第一次先将统计每一个点的孩子统计出来，并且记录一下当前这个点到根节点经过了多少个点。而第二次搜索呢，我们记录一下每一个点是在第次搜索搜到的和当前这一次遍历所用的点到根节点经过了多少个点。接着，每一次询问，我们只需要遍历一次就行了，而遍历的起点则是这个点是第几个被搜索到的，终点是起点加上它的孩子的数量减去一。

但是，这样会超时，所以我们可以利用分块去优化它。分块，其实是一种思想，而不是一种数据结构。分块的基本思想是，通过对原数据的适当划分，并在划分后的每一个块上预处理部分信息，从而较一般的暴力算法取得更优的时间复杂度。换到此题，我们可以将原本的进行分块，从而做到询问时最慢只用跑大约 $400$ 次，满足题意。

### 代码
```
#include <bits/stdc++.h>
using namespace std;
const int MAX = 2 * 1e5 + 5;
int n;
int book[MAX];
struct op {//链式前向星
    int from, to;
} a[MAX];
int head[MAX];
int cnt = 1;
void hb(int father, int me) {//链式前向星存图
    a[cnt].from = head[father];
    a[cnt].to = me;
    head[father] = cnt++;
}
int sum_son[MAX];
int f[MAX];
inline void dfs(int x) {//第一次搜索
    sum_son[x] = 1;//统计子树的节点数量
    for (int i = head[x]; i; i = a[i].from) {
        int xx = a[i].to;
        f[xx] = f[x] + 1;//记录距离根节点的节点数量
        dfs(xx);//继续搜索
        sum_son[x] += sum_son[xx];//加上子节点子树的节点数量
    }
}
int sl[MAX];
int top;
bool tp[MAX];
int dian[MAX];
inline void dfs1(int x) {//第二次搜索
    sl[++top] = f[x];//记录当前第top次遍历的点距离根节点的节点数量
    dian[x] = top;//记录当前点的dfs序
    for (int i = head[x]; i; i = a[i].from) {
        int xx = a[i].to;
        dfs1(xx);//继续搜索
    }
}
int lefta[MAX], righta[MAX];
int dp[505][MAX];
int k;
signed main() {
    cin >> n;
    int ks = ceil(sqrt(n));//块数
    for (int i = 2; i <= n; i++) {
        scanf("%d", &k);
        hb(k, i);//建图
    }
    dfs(1);
    dfs1(1);
    for (int i = 1; i <= n; i++) {
        book[i] = i / ks + 1;//第几块
        lefta[book[i]] = min(lefta[book[i]], i);//求当前这一块的左端点
        righta[book[i]] = max(righta[book[i]], i);//求当前这一块的右端点
    }
    for (int i = 1; i <= n; i++) {
        dp[book[i]][sl[i]]++;//第book[i]块的sl[i]出现的数量增加
    }
    int m;
    cin >> m;
    while (m--) {
        int x, sum;
        scanf("%d%d", &x, &sum);
        int ans = 0;
        int l_now = dian[x], r_now = dian[x] + sum_son[x] - 1;//左端点和右端点
        int b1 = book[l_now], b2 = book[r_now];//左右两段点所在的分别是第几块
        if (b1 == b2) {//在同一块
            for (int j = l_now; j <= r_now; j++) {//直接遍历
                ans += (sl[j] == sum);
            }
            printf("%d\n", ans);
            continue;
        }
        for (int j = b1 + 1; j <= b2 - 1; j++) {//加上左右两块中的数量
            ans += dp[j][sum];
        }
        int lb1 = lefta[b1], rb1 = righta[b1];//记录左边那一块的左端点和右端点
        int midb1 = (lb1 + rb1) >> 1;//求中间点
        if (l_now >= midb1) {//要是大于，就直接遍历
            for (int j = l_now; book[j] == b1; j++) {
                if (sl[j] == sum) {
                    ans++;
                }
            }
        } else {//否则减去相反的一边，再加上这一块的
            int l = 0;
            for (int j = l_now - 1; book[j] == b1; j--) {
                if (sl[j] == sum) {
                    l++;
                }
            }
            ans += dp[b1][sum] - l;
        }
        int lb2 = lefta[b2], rb2 = righta[b2];//记录右边那一块的左端点和右端点
        int midb2 = (lb2 + rb2) >> 1;//求中间点
        if (r_now >= midb2) {//要是大于就减去相反的一边，再加上这一块的
            int l = 0;
            for (int j = r_now + 1; book[j] == b2; j++) {
                if (sl[j] == sum) {
                    l++;
                }
            }
            ans += dp[b2][sum] - l;
        } else {//否则就直接遍历
            for (int j = r_now; book[j] == b2; j--) {
                if (sl[j] == sum) {
                    ans++;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

首先用 `dfn` 序转化为区间问题，然后用线段树维护即可。

怎么维护呢？首先你可以发现，因为线段树深度 $O(\log n)$，所以所有节点维护的区间大小加起来就是 $O(n\log n)$。

那么我们给线段树每个节点用个 `map` 维护以下内部每种深度有几个即可。

但是 `map` 似乎会被卡，发现 $[1,n]$ 域很小，换成 `unorderd_map` 似乎没问题。

时间 $O(n\log n)$，空间 $O(n\log n)$。

---

## 作者：MYiFR (赞：1)

### 写在前面
扫了一眼题解区，居然没有分块在线？这不得补上一篇？

后天 CSP，祝各位 `RP+=(RP++ + ++RP)`。

### 解题思路
其实还真挺一眼的。把问题转化一下就变成了求 $U_i$ 的子树中有多少个深度为 $D_i+1$ 的点，注意是 $D_i+1$。把 dfs 序拎出来就变成了求区间内某个值的数量。于是将按 dfs 序转换后的深度序列分块，块长 $\sqrt N$。预处理出一个深度前缀和序列，不过记录的是前 $i$ 个块中不同深度点的数。

```
m=sqrt(n); k=n/m;
for(int i=1;i*m<=n;++i){
	memset(sum1,0,sizeof sum1);
	for(int j=(i-1)*m+1;j<=i*m;++j) ++sum1[dep[j]];
	for(int j=1;j<=n;++j) sum[i][j]=sum[i-1][j]+sum1[j];
	ls[i]=(i-1)*m+1; rs[i]=i*m;
}
if(m*m!=n){
	memset(sum1,0,sizeof sum1);
	for(int j=n/m*m+1;j<=n;++j) ++sum1[dep[j]];
	++k;
	for(int j=1;j<=n;++j) sum[k][j]=sum[k-1][j]+sum1[j];
	ls[k]=(k-1)*m+1; rs[k]=n;		//ls，rs分别是左端点和右端点
}
```

（为了方便理解贴份代码）

对于一个询问 $(U_i,D_i)$，将其转化为序列上的一段询问很简单，相当于是求 $[U_i,U_i+siz_{U_i}-1]$ 中值为 $D_i$ 个元素个数，用之前预处理的前缀和，外加两段最长在 $2\sqrt N$ 的暴力求解即可。

```
int calc(int l,int r,int c){
	int res=0;
	int L=(l+m-2)/m+1,R=r/m;
	res+=sum[R][c]-sum[L-1][c];
	for(int i=l;i<=rs[L-1];++i) if(dep[i]==c) ++res;
	for(int i=ls[R+1];i<=r;++i) if(dep[i]==c) ++res;
	return res;
}
```

这里有个小问题值得注意。当 $N$ 是一个完全平方数的时候，如果询问区间在 $[N,N]$，那么 $R+1=\sqrt N +1$，$ls_{R+1}$ 就会等于 $0$，答案就是错的。但是 AT 的数据似乎没有卡掉这个错，还是后来我自己偶然间测出来的（本来是想找之前代码为什么挂了，结果放在了[第一版的 AC 代码](https://atcoder.jp/contests/abc202/submissions/46739838)上跑，发现把自己 HACK 了）。虽然过了，但是万一什么时候就炸了呢？所以应该把最后的块的下一个（实际上不存在的）块的左端点设大一点。

```
ls[k+1]=n+5;
```

### AC 代码
```
#include<bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned ll
#define ldb long db
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define pdd pair<db,db>
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;
const int N=2e5+5,M=505;
int n,m,k,p,q,u,d,siz[N],dep[N],id[N],cnt,sum[M][N],sum1[N],ls[M],rs[M];
vector<int> e[N];
void dfs(int cur,int fa){
	siz[cur]=1;
	id[cur]=++cnt;
	dep[id[cur]]=dep[id[fa]]+1;
	for(int to:e[cur]){
		dfs(to,cur);
		siz[cur]+=siz[to];
	}
}
int calc(int l,int r,int c){
	int res=0;
	int L=(l+m-2)/m+1,R=r/m;
	res+=sum[R][c]-sum[L-1][c];
	for(int i=l;i<=rs[L-1];++i) if(dep[i]==c) ++res;
	for(int i=ls[R+1];i<=r;++i) if(dep[i]==c) ++res;
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;++i){
		scanf("%d",&p);
		e[p].PB(i);
	}
	dfs(1,0);
	m=sqrt(n); k=n/m;
	for(int i=1;i*m<=n;++i){
		memset(sum1,0,sizeof sum1);
		for(int j=(i-1)*m+1;j<=i*m;++j) ++sum1[dep[j]];
		for(int j=1;j<=n;++j) sum[i][j]=sum[i-1][j]+sum1[j];
		ls[i]=(i-1)*m+1; rs[i]=i*m;
	}
	if(m*m!=n){
		memset(sum1,0,sizeof sum1);
		for(int j=n/m*m+1;j<=n;++j) ++sum1[dep[j]];
		++k;
		for(int j=1;j<=n;++j) sum[k][j]=sum[k-1][j]+sum1[j];
		ls[k]=(k-1)*m+1; rs[k]=n;
	}
	ls[k+1]=n+5;
	scanf("%d",&q);
	while(q--){
		scanf("%d%d",&u,&d);
		printf("%d\n",calc(id[u],id[u]+siz[u]-1,d+1));
	}
	return 0;
}
//To wish upon the satellite.
```

整体看来，这份代码跑的不算快（354ms），码量也有点浪费（语出某位代码长度从未上过 3000 的机房大佬），不过还算容易理解，个人感觉作为分块和树上问题的引入还是可行的。

---

## 作者：CQ_Bob (赞：1)

## 分析

我不会二分、线段树合并、时间戳……但是，我会莫队~

说一下莫队解法。把题目转化一下，就是：查询在以节点 $1$ 为根的情况下，$a_i$ 为根的子树中深度为 $b_i+1$ 的节点数量。

把这棵树转化成 DFS 序，我们就可以得到每次询问的区间是 $[dfsx_{a_i},dfsx_{a_i}+siz_{a_i}-1]$。我们定义 $num_i$ 表示在当前区间内，深度为 $i$ 的节点的数量。那么第 $i$ 个询问的答案，就是 $num_{b_i}$ 了。复杂度是 $O(n\sqrt{n})$ 的，能过。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=4e5+10;
int n,q;
int ne[N],e[N],h[N],idx;
int x[N],dfsx[N],siz[N],dep[N],cnt;
struct node{
	int l,r,k,id;
}Q[N];int ans[N],len;
int num[N];

il void add(int a,int b){ne[++idx]=h[a],e[idx]=b,h[a]=idx;}
il void dfs(int now,int fa){
	dep[now]=dep[fa]+1,dfsx[now]=++cnt,x[cnt]=now,siz[now]=1;
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa) continue;
		dfs(j,now),siz[now]+=siz[j];
	}
	return ;
}
il bool cmp(node a,node b){return ((a.l/len!=b.l/len)?(a.l<b.l):(((a.l/len)&1)?a.r<b.r:a.r>b.r));}

il void read(){
	cin>>n;
	for(re int i=2;i<=n;++i){
		int x;cin>>x;
		add(i,x),add(x,i);
	}
	dfs(1,0),len=sqrt(n);
	cin>>q;
	for(re int i=1;i<=q;++i){
		int a,b;cin>>a>>b;
		Q[i]={dfsx[a],dfsx[a]+siz[a]-1,b+1,i};
	}
}
il void solve(){
	sort(Q+1,Q+q+1,cmp);
	int l=1,r=0;
	for(re int i=1;i<=q;++i){
		while(l>Q[i].l) --l,++num[dep[x[l]]];
		while(r<Q[i].r) ++r,++num[dep[x[r]]];
		while(l<Q[i].l) --num[dep[x[l]]],++l;
		while(r>Q[i].r) --num[dep[x[r]]],--r;
		ans[Q[i].id]=num[Q[i].k];		
	}
	for(re int i=1;i<=q;++i) cout<<ans[i]<<"\n";
}

signed main(){
	read(),solve();return 0;
}
```


---

## 作者：AntonyD (赞：1)

# ABC202E Count Descendants

[Luogu原题传送门](https://www.luogu.com.cn/problem/AT_abc202_e)

[AtCoder原题传送门](https://atcoder.jp/contests/abc202/tasks/abc202_e)

~~这道题真的很难，做了我一个小时~~

## 题目大意

给定一棵以 $1$ 号节点为根的有根树，多次询问求某个点的子树中深度为给定值的点的个数。

## 思路分析

开一个 `vector` 二维数组存储每个深度的所有节点的出入DFS函数时间，

然后用 `lower_bound` 函数查询两个时间 `l,r` 在该 `vector` 数组中的位置，

求出其差，就是 $U$ 的所有合法点的数量。

由：如果 $V$ 是 $U$ 的子孙节点，那么定有 $in[u]≤in[v]≤out[u]$，

所以 `r,l` 的差就是合法节点的个数。

## 代码

```c++
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
vector<int> tr[MAXN],re[MAXN];
//in和out数组分别是统计某个节点的入dfs和出dfs时间，由此看出这个节点下有几个子节点
int n,dep[MAXN],in[MAXN],out[MAXN];
int now=0;
//声明各种变量，不用说了吧
void dfs(int p) { //
	in[p]=now++;
    //因为now持续++，所以in[]中的所有数据呈单调递增
	re[dep[p]].push_back(in[p]);
    //把in[p]的值加入到深度为dep[p]的数据中
	for(auto v:tr[p]) {
        //用auto进行对vector数组的遍历，其中的v是tr[p]即p节点的所有子节点（儿子）
		dep[v]=dep[p]+1;
        //因为v是p的子节点，在该树中的深度自然++啦
		dfs(v);
        //递归
	}
	out[p]=now++;
    //与上同理，out[]中的所有数据同样呈单调递增
}
int main() {
	cin>>n;
	for(int i=2; i<=n; i++) {
        //建树
		int p;
		cin>>p;
		tr[p].push_back(i);
	}
	dfs(1);
	int q;
	cin>>q;
	for(int i=1; i<=q; i++) {
		int u,len;
		cin>>u>>len;
		auto l=lower_bound(re[len].begin(),re[len].end(),in[u]);
        //由DFS函数中的代码可以看出
		auto r=lower_bound(re[len].begin(),re[len].end(),out[u]);
        //re[]数组中的数据是单调递增的,r,l分别是in[u]和out[u]在re数组中的位置
		cout<<r-l<<endl;
        //if v是u的子孙节点 则定有in[u]<in[v]<out[u]<out[v],r与l的差就是节点的个数
	}
    return 0;//养成好习惯哦~~
}
```

## 代码解析

### $now$ 变量：

由思路分析中的第一段可以得出，

我们需要求某节点的出入 DFS 函数时间，通过在进入函数时的 `in[p]=now++`，可以得入的时间。

出函数的时候 `out[p]=now++` 可以得出该节点离开 DFS 函数的时间。

这两个 $now$ 很有用处，可以体现该节点总共有几个子孙节点。

由于 $in[v]>in[u]$ 且 $out[v]<out[v]$，所以可以看出晚辈 $v$ 是包含在祖先 $u$ 的区间内的。

### 如何计算 now?

```c++
in[p]=now++;
	re[dep[p]].push_back(in[p]);
	for(auto v:tr[p]) { 
		dep[v]=dep[p]+1;
		dfs(v);
	}
	out[p]=now++;
```

### 建树

很简单，只需要开一个 `vector` 函数 `tree`，

行数为 $p$ 的数据存储编号 $p$ 的节点的所有子节点编号，利用 `push_back()` 进行数据增删。

建树的模板很容易，就是利用 STL 中的 `vector` 类型数组进行存储子节点就行。

**注意，此题中编号为 $1$ 的节点是根，所以建树只需从编号为 $2$ 的节点开始就行。**

### 很简单的建树代码

```c++
vector<int> tr[MAXN]；
for(int i=2; i<=n; i++) {
		int p;
		cin>>p;
		tr[p].push_back(i);
}
```

### 查询

因为时间 $now$ 只会增加不会减少，在 DFS 函数中也可以看到只有 ++，所以 re 数组中的数据是单调递增的！所以可以使用 `lower_bound()`！

考虑到有些同学可能忘记了 `lower_bound()` 怎么写，那这里再讲一次 `lower_bound()` 和 `upper_bound()` 的格式吧！

`lower_bound(begin,end,num)` ：从数组的 $begin$ 位置到 $end-1$ 位置二分查找第一个大于或等于 $num$ 的数字，找到返回该数字的地址，不存在则返回 $end$ 。通过返回的地址减去起始地址 $begin$ ,得到找到数字在数组中的下标。

`upper_bound(begin,end,num)` ：从数组的 $begin$ 位置到 $end-1$ 位置二分查找第一个大于 $num$ 的数字，找到返回该数字的地址，不存在则返回 $end$ 。通过返回的地址减去起始地址 $begin$ ,得到找到数字在数组中的下标。

**假如在数组中查询第一个大于或等于 $x$ 的值的位置，那么使用 `lower_bound()` :**

`lower_bound(begin,end,x)`

**假如在数组中查询第一个大于 $x$ 的值的位置，那么使用 `upper_bound()` :**

`upper_bound(begin,end,x)`

### 可以这样算

```c++
auto l=lower_bound(re[len].begin(),re[len].end(),in[u]);
auto r=lower_bound(re[len].begin(),re[len].end(),out[u]);
//其中的l,r都是迭代器
```

# 完结撒花~

---

## 作者：Genius_Star (赞：1)

**随便找了道水题，发现我的思路目前题解区里没有，就决定写一下了。**

### 题意：

给定一棵树，有 $q$ 次询问，给定 $a$ 和 $b$，每次询问有多少个点到根节点的路径上包含 $a$ 点，且到根节点的路径边数为 $b$。

### 思路：

首先，如果一个点到根节点的路径上包含 $a$ 点，那么这个点肯定是 $a$ 子树内的点。

刚开始，我们可以先预处理出每一个点到根节点的边数（即深度），然后可以用类似树链剖分的方法将每一个点的 DFS 序求出来。

那么 $u$ 号点的子树内的编号编号应该为 $A_u \sim (A_u+p_u-1)$，其中 $A_u$ 为 $u$ 点的 DFS 序，$p_u$ 为 $u$ 号点的子树大小。

那么对于每次询问操作，只需要询问 $A_u \sim (A_u+p_u-1)$ 之间深度为 $b$ 的点的个数，因为点的个数可能很多，所以不能暴力，需要优化。

感觉线段树有点儿不好处理，那么考虑分块，对于每一个块，我们可以维护块内深度为某值的个数，比如当前在第 $x$ 个块，当前处理在第 $i$ 个元素，则将 $P_{x,a_i} \to P_{x,a_i}+1$，其中 $a_i$ 为 DFS 序为 $i$ 的点的深度。

对于每次查询，如果是在同一个块，暴力计算，否则算中间的整块，然后暴力算旁边的散块。

时间复杂度为：$O(N \times \sqrt N)$。

**在 AT 上跑了 794ms，感觉挺快的。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=200200,M=505;
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
ll n,q,t,k,l,r,cnt=0;
ll a[N],L[M],R[M],B[N],K[N];
ll p[N],d[N],z[N],fa[N],A[N];
ll P[M][N];
vector<ll> E[N];
void add(ll u,ll v){
	E[u].push_back(v);
	E[v].push_back(u);
}
void dfs1(ll u,ll f){
	p[u]=1;
	for(auto v:E[u]){
		if(v==f)
		  continue;
		d[v]=d[u]+1;
		fa[v]=u;
		dfs1(v,u);
		p[u]+=p[v];
		if(p[z[u]]<p[v])
		  z[u]=v;
	}
}
void dfs2(ll u,ll k){
	A[u]=++cnt;
	K[cnt]=u;
	a[cnt]=d[u];
	if(!z[u])
	  return ;
	dfs2(z[u],k);
	for(auto v:E[u]){
		if(v==fa[u]||v==z[u])
		  continue;
		dfs2(v,v);
	}
}
ll qurey(ll x,ll y,ll z){
	ll l=B[x],r=B[y];
	ll ans=0;
	if(l==r){
		for(int i=x;i<=y;i++)
		  ans+=(a[i]==z);
	}
	else{
		for(int i=(l+1);i<=(r-1);i++)
		  ans+=P[i][z];
		for(int i=x;i<=R[l];i++)
		  ans+=(a[i]==z);
		for(int i=L[r];i<=y;i++)
		  ans+=(a[i]==z);
	}
	return ans;
}
int main(){
	n=read();
	for(int i=2;i<=n;i++)
	  add(i,read());
	dfs1(1,1);
	dfs2(1,1);
	k=sqrt(n),t=n/k;
	if(n%k!=0)
	  t++;
	for(int i=1;i<=t;i++){
		L[i]=(i-1)*k+1;
		R[i]=i*k;
	} 
	R[t]=n;
	for(int i=1;i<=n;i++){
		B[i]=(i-1)/k+1;
		P[B[i]][a[i]]++;
	}
	q=read();
	while(q--){
		l=read(),r=read();
//		for(int i=A[l];i<=A[l]+p[l]-1;i++)
//		  printf("%lld ",K[i]);
//		putchar('\n');
		write(qurey(A[l],A[l]+p[l]-1,r));
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Natori (赞：1)

>[ABC202E Count Descendants](https://www.luogu.com.cn/problem/AT_abc202_e)

线段树合并模板题。

------------
每次询问就是给定有序数对 $(u,d)$，求有根树 $T$ 上，点 $u$ 的子树内有多少点 $v$，使得 $v$ 的深度恰好等于 $d+1$。定义根节点深度为 $1$。

考虑对每一个点开一个长度为 $n$ （因为 $T$ 的最大深度为 $n$）的数组 $a_u$，$a_{u,i}$ 表示 $u$ 的子树内深度为 $i$ 的点有多少，同时记录每个点的深度 $depth$。

每递归到叶节点 $v$，就将 $a_{v,i}$ 加上 $1$。

回溯时，将 $a_v$ 暴力合并到 $a_u$，即 $\forall i \in [1,n],a_{u,i} \leftarrow a_{u,i}+a_{v,i}$，这一步的时间复杂度为 $\mathcal{O}(n)$。单次查询可以做到 $\mathcal{O}(1)$。于是该做法的时间、空间复杂度均为 $\mathcal{O}(n^2)$。

------------
显然，时间复杂度的瓶颈在于合并操作，考虑如何优化这一步。

考虑线段树合并，对每一个 $u$ 开一棵动态开点权值线段树，每次回溯时将 $v$ 对应的线段树与 $u$ 合并即可，单次时间复杂度 $\mathcal{O}( \log n)$。

注意不能将 $v$ 对应的线段树直接合并到 $u$，因为这样会导致 $u$ 对应线段树的信息丢失，所以应该先新建一个节点 $o$，再将 $u$ 和 $v$ 的节点信息合并至 $o$。当然离线询问也可以解决这个问题。

由于每次会多开 $\mathcal{O}(\log n)$ 个点，所以线段树的数组大小要在原来的基础上再多开一倍。总复杂度 $\mathcal{O}(n \log n)$。

**树上启发式合并** 也可以解决本题，时间复杂度仍然是 $\mathcal{O}(n \log n)$。

下面是线段树合并的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool Mbegin;
void File_Work(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
namespace Fast_In_Out{
	char buf[1<<21],*P1=buf,*P2=buf;
	#define gc (P1==P2&&(P2=(P1=buf)+fread(buf,1,1<<21,stdin),P1==P2)?EOF:*P1++)
	int read(){
		int f=1,x=0;
		char c=gc;
		while(c<'0'||c>'9'){
			if(c=='-')
			    f=-1;
			c=gc;
		}
		while(c>='0'&&c<='9'){
			x=x*10+c-'0';
			c=gc;
		}
		return f*x;
	}
	void write(int x){
		if(x<0)
			x=-x,putchar('-');
		if(x>9)
			write(x/10);
		putchar(x%10+'0');
	}
	#undef gc
}
using namespace Fast_In_Out;
const int N=2e5+8;
int n,m;
struct Graph{
	int head[N],edge_tot=1,to[N],next[N];
	void add_edge(int u,int v){
		edge_tot++;
		to[edge_tot]=v;
		next[edge_tot]=head[u];
		head[u]=edge_tot;
	}
}Tree;
int depth[N];
int rt[N];
struct Segemnt_Tree{
	int ocnt,ls[N<<6],rs[N<<6],sum[N<<6];
	void push_up(int o){
		sum[o]=sum[ls[o]]+sum[rs[o]];
	}
	void insert(int &o,int l,int r,int pos){
		o=++ocnt;
		if(l==r){
			sum[o]++;
			return;
		}
		int mid=(l+r)/2;
		if(pos<=mid)
			insert(ls[o],l,mid,pos);
		else
			insert(rs[o],mid+1,r,pos);
		push_up(o);
	}
	int query(int o,int l,int r,int pos){
		if(o==0)
			return 0;
		if(l==r)
			return sum[o];
		int mid=(l+r)/2;
		if(pos<=mid)
			return query(ls[o],l,mid,pos);
		else
			return query(rs[o],mid+1,r,pos);
	}
	int merge(int u,int v){
		if(u==0||v==0)
			return u+v;
		int o=++ocnt;
		ls[o]=merge(ls[u],ls[v]);
		rs[o]=merge(rs[u],rs[v]);
		sum[o]=sum[u]+sum[v];
		return o;
	}
}smt;
void dfs(int u,int father){
	depth[u]=depth[father]+1;
	smt.insert(rt[u],1,n,depth[u]);
	for(int i=Tree.head[u];i;i=Tree.next[i]){
		int v=Tree.to[i];
		dfs(v,u);
		rt[u]=smt.merge(rt[u],rt[v]);
	}
}
bool Mend;
int main(){
//	File_Work();
	fprintf(stderr,"%.3lf MB\n\n\n",(&Mbegin-&Mend)/1048576.0);
	n=read();
	for(int i=2;i<=n;i++){
		int father=read();
		Tree.add_edge(father,i);
	}
	dfs(1,0);
	m=read();
	while(m--){
		int a=read(),b=read()+1;
		write(smt.query(rt[a],1,n,b)),putchar('\n');
	}
	fprintf(stderr,"\n\n\n%.0lf ms",1e3*clock()/CLOCKS_PER_SEC);
	return 0;
}
```

线段树合并的题，通常可以先想 $\mathcal{O}(n^2)$ 做法，再进行优化。

思想几乎一样的题：[CF208E Blood Cousins](https://www.luogu.com.cn/problem/CF208E)。

另一道线段树合并模板题：[CF600E Lomsat gelral](https://www.luogu.com.cn/problem/CF600E)。

---

## 作者：_Kenma_ (赞：0)

# AT_abc202_e 解题报告

## 前言

提供一种目前没有的 $O(n)$ 做法。

话说在绿题写莫队、分块、线段树合并、启发式合并真的好吗。

## 思路分析

首先转化题意为多次询问，求 $a$ 子树内深度为 $b$ 的点的个数。

如果你做过天天爱跑步的话，应该并不难想。

首先离线，将询问挂到每个点上。

考虑开一个全局桶，桶内维护每个深度的节点个数。

然后 dfs 整棵树，在 dfs $x$ 子树前，先分别记录 $x$ 子树每个询问深度的点的个数，回溯时再记录一次，两次记录做差，就是 $x$ 子树内某一深度的点的个数。

然后就是 $O(n)$ 的了。

感觉比其他大部分做法好写。

没卡常，关个同步流就跑到了最优解第四。

但是你们真是太能卡了。根本卡不过。

具体实现看代码。

## 代码实现

```cpp

#include<bits/stdc++.h>
using namespace std;
int n,m,x,k,ans[200005];
int head[200005],nxt[400005],target[400005],tot;
inline void add(int x,int y){
	tot++;
	nxt[tot]=head[x];
	head[x]=tot;
	target[tot]=y;
}
int dep[200005],t[200005];
inline void dfs1(int x,int fa){
	for(int i=head[x];i;i=nxt[i]){
		int y=target[i];
		if(y==fa) continue;
		dep[y]=dep[x]+1;
		dfs1(y,x);
	}
}
struct node{
	int k,id;
};
vector<node> v[200005];
inline void dfs2(int x,int fa){
	for(int i=0;i<v[x].size();i++){
		ans[v[x][i].id]=t[v[x][i].k];
	}
	for(int i=head[x];i;i=nxt[i]){
		int y=target[i];
		if(y==fa) continue;
		dfs2(y,x);
	}
	t[dep[x]]++;
	for(int i=0;i<v[x].size();i++){
		ans[v[x][i].id]=t[v[x][i].k]-ans[v[x][i].id];
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(register int i=2;i<=n;i++){
		cin>>x;
		add(i,x);
		add(x,i);
	}
	dfs1(1,0);
	cin>>m;
	for(register int i=1;i<=m;i++){
		cin>>x>>k;
		v[x].push_back((node){k,i});
	}
	dfs2(1,0);
	for(register int i=1;i<=m;i++){
		cout<<ans[i]<<'\n';
	} 
	return 0;
}

```

感觉很好写。

---

## 作者：LCat90 (赞：0)

建一棵主席树，以深度为下标，记录以每个点的 dfn 构成的权值线段树。查询就是在 $a_i$ 的子树范围内找深度为 $b_i$ 的点的个数。  

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 2e5 + 5;
int n, m, q, a[N], Root[N], cnt;
struct node { int l, r, sum; } T[N << 5]; 
int build(int l, int r);
int update(int o, int l, int r, int k, int x); // 按照深度为下标建主席树
int query(int p, int l, int r, int ql, int qr);

int dfn[N], ct, d[N], siz[N];
vector <int> G[N];
void dfs(int x, int fa) {
    d[x] = d[fa] + 1, dfn[x] = ++ct; siz[x] = 1;
    for(auto to : G[x]) {
        if(to == fa) continue ;
        dfs(to, x); siz[x] += siz[to];
    } 
}

signed main() {
    // freopen("query.in", "r", stdin);
    // freopen("query.out", "w", stdout);
    cin >> n;
    for(int i = 2, x;i <= n; ++i) {
        scanf("%d", &x);
        G[i].pb(x), G[x].pb(i);
    }
    dfs(1, 0); 
    for(int i = 1;i <= n; ++i) Root[d[i]] = update(Root[d[i]], 1, n, dfn[i], 1);
    cin >> q; 
    while(q--) {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", query(Root[y + 1], 1, n, dfn[x], dfn[x] + siz[x] - 1)); // 
    }
    return 0;
}
/* 
询问：x 的子树中有多少个深度为 d 主席树薄纱
*/
int build(int l, int r) {
    int p = ++cnt; if(l == r) return p;
    int mid = l + r >> 1;
    T[p].l = build(l, mid), T[p].r = build(mid + 1, r);
    return p;
}
int update(int o, int l, int r, int k, int x) {
    int p = o; if(!p) p = ++cnt;
    if(l == k and r == k) { T[p].sum += x; return p; }
    int mid = l + r >> 1;
    if(k <= mid) T[p].l = update(T[p].l, l, mid, k, x);
    else T[p].r = update(T[p].r, mid + 1, r, k, x);
    T[p].sum = T[T[p].l].sum + T[T[p].r].sum;
    return p;
}
int query(int p, int l, int r, int ql, int qr) { 
    if(ql <= l and r <= qr) return T[p].sum;
    int mid = l + r >> 1, ans = 0;
    if(ql <= mid) ans += query(T[p].l, l, mid, ql, qr);
    if(qr > mid) ans += query(T[p].r, mid + 1, r, ql, qr);
    return ans; 
}
```

---

## 作者：AlicX (赞：0)

一道可以用启发式合并秒的题。 

但是为什么题解区里没有？？？

题目要求我们求在 $a$ 的子树内（包括 $a$）深度为 $b$ 的节点个数（根节点深度为 $0$）。于是发现这是一道树上求 $k$ 级儿子的经典题。所以考虑启发式合并。

详细过程为，首先把询问挂到树上，然后通过第一遍 `dfs` 找出重儿子（重儿子为子节点最多的节点）以及每个店的深度，然后第二遍 `dfs` 计算每个儿子的子树的贡献，再计算重儿子的贡献，然后计算每个儿子的贡献和本身的贡献，最后求答案，求完答案后如果不是重儿子要清零。

对于此题用 $cnt_i$ 表示深度为 $i$ 的节点的数量即可。

具体可以参考关键代码。

```cpp
il void Add(int u){ cnt[dep[u]]++; } 
il void Del(int u){ cnt[dep[u]]--; } 
il void modify(int u,bool flg){ 
	for(int i=in[u];i<=out[u];i++){ 
		if(flg) Add(mp[i]); 
		else Del(mp[i]);  
	} 
} 
il void dfs2(int u,bool flag){ 
	for(int i=h[u];i!=-1;i=tr[i].ne){ 
		int to=tr[i].to; 
		if(to==son[u]) continue; 
		dfs2(to,false); 
	} if(son[u]) dfs2(son[u],true); 
	for(int i=h[u];i!=-1;i=tr[i].ne){
		int to=tr[i].to; 
		if(to==son[u]) continue; 
		modify(to,true); 
	} Add(u); 
	for(int i=0;i<q[u].size();i++) ans[q[u][i].y]=cnt[q[u][i].x]; 
	if(!flag) modify(u,false); 
} 
```

---

