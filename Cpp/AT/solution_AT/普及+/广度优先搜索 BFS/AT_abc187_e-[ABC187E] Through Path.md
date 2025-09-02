# [ABC187E] Through Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc187/tasks/abc187_e

$ N $ 頂点 $ N-1 $ 辺から成る木があり、頂点には $ 1,\ 2,\ \dots,\ N $ の番号が、辺には $ 1,\ 2,\ \dots,\ N-1 $ の番号がついています。辺 $ i $ は頂点 $ a_i $ と頂点 $ b_i $ を結びます。 この木の各頂点には $ 1 $ つの整数が書かれています。頂点 $ i $ に書かれている整数を $ c_i $ とします。はじめ、 $ c_i\ =\ 0 $ です。

$ Q $ 個のクエリが与えられます。 $ i $ 番目のクエリでは、整数 $ t_i,\ e_i,\ x_i $ が与えられます。クエリの内容は以下の通りです。

- $ t_i\ =\ 1 $ のとき : 頂点 $ a_{e_i} $ から辺をたどって頂点 $ b_{e_i} $ を通らずに到達できるような全ての頂点 $ v $ に対して、$ c_v $ を $ c_v\ +\ x_i $ に書き換える。
- $ t_i\ =\ 2 $ のとき : 頂点 $ b_{e_i} $ から辺をたどって頂点 $ a_{e_i} $ を通らずに到達できるような全ての頂点 $ v $ に対して、$ c_v $ を $ c_v\ +\ x_i $ に書き換える。

すべてのクエリを処理した後、各頂点に書かれた整数を出力してください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ a_i,\ b_i\ \le\ N $
- 与えられるグラフは木である
- $ 1\ \le\ Q\ \le\ 2\ \times\ 10^5 $
- $ t_i\ \in\ \{1,\ 2\} $
- $ 1\ \le\ e_i\ \le\ N-1 $
- $ 1\ \le\ x_i\ \le\ 10^9 $

### Sample Explanation 1

$ 1 $ 番目のクエリでは、頂点 $ 1 $ から始めて頂点 $ 2 $ を通らずに到達できる頂点 $ 1 $ に $ 1 $ を足します。 $ 2 $ 番目のクエリでは、頂点 $ 4 $ から始めて頂点 $ 5 $ を通らずに到達できる頂点 $ 1,\ 2,\ 3,\ 4 $ に $ 10 $ を足します。 $ 3 $ 番目のクエリでは、頂点 $ 2 $ から始めて頂点 $ 1 $ を通らずに到達できる頂点 $ 2,\ 3,\ 4,\ 5 $ に $ 100 $ を足します。 $ 4 $ 番目のクエリでは、頂点 $ 3 $ から始めて頂点 $ 2 $ を通らずに到達できる頂点 $ 3 $ に $ 1000 $ を足します。

## 样例 #1

### 输入

```
5
1 2
2 3
2 4
4 5
4
1 1 1
1 4 10
2 1 100
2 2 1000```

### 输出

```
11
110
1110
110
100```

## 样例 #2

### 输入

```
7
2 1
2 3
4 2
4 5
6 1
3 7
7
2 2 1
1 3 2
2 2 4
1 6 8
1 3 16
2 4 32
2 1 64```

### 输出

```
72
8
13
26
58
72
5```

## 样例 #3

### 输入

```
11
2 1
1 3
3 4
5 2
1 6
1 7
5 8
3 9
3 10
11 4
10
2 6 688
1 10 856
1 8 680
1 8 182
2 2 452
2 4 183
2 6 518
1 3 612
2 6 339
2 3 206```

### 输出

```
1657
1657
2109
1703
1474
1657
3202
1474
1247
2109
2559```

# 题解

## 作者：Let_Fly (赞：7)

# 题意：

即指定某子树进行修改。

如图：
![](https://img1.imgtp.com/2023/07/31/vH2jArZn.jpeg)

# 题解：

这里有很多种方法，树链剖分可以，不过直接树上差分就可以了。

无根，我们钦定 $1$ 为根，处理出深度（待会讲有什么用）。

然后对于每一个处理，我们需要判断是处理高的还是低的（因为不方便换根）。

如图：
![](https://img1.imgtp.com/2023/07/31/HDtgMBec.jpeg)

若低，则在**此点**打差分标记，若高，则在**根**和**此点通过指定边连接的点**上打差分。

然后我们进行第二遍 dfs 来把差分的结果求出来输出就可以了。

剩余的说明都在注释里。

# CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
 
int n,q;
int wei[N];//答案
int dep[N];//深度
vector<int> to[N];//树
int tag[N];//差分标记
struct Edge{
    int u,v;
}eg[2*N+5];//边集
 
void dfs1(int u,int fa){
    dep[u]=dep[fa]+1;//深度为父亲的深度加一
    for(auto v:to[u]){
        if(v==fa)continue;
        dfs1(v,u);
    }
}
 
void dfs(int u,int fa,int j){
    j+=tag[u];
    wei[u]+=j;//树上前缀和
    for(auto v:to[u]){
        if(v==fa)continue;
        dfs(v,u,j);
    }
}
 
signed main(){
    // freopen("tree.in","r",stdin);
    // freopen("tree.out","w",stdout);
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        eg[i]={u,v};
        to[u].push_back(v);//建双向边
        to[v].push_back(u);
    }
    cin>>q;
    dfs1(1,0);//处理深度
    for(int i=1;i<=q;i++){
        int op,bh,w;
        cin>>op>>bh>>w;
        if(op==1){
            int p=eg[bh].u,l=eg[bh].v;
            if(dep[p]>dep[l]){//如果要处理的点更深，说明是处理其子树
                tag[p]+=w;//所以给他自己打差分
            }else{
                tag[l]-=w;//否则是处理除掉其子树以外的部分，给子树打终止标记
                tag[1]+=w;//给全树打开始标记
            }
        }else{
            int p=eg[bh].u,l=eg[bh].v;
            if(dep[l]>dep[p]){
                tag[l]+=w;
            }else{
                tag[p]-=w;
                tag[1]+=w;
            }
        }
    }
    dfs(1,0,0);//处理差分
    for(int i=1;i<=n;i++){
        cout<<wei[i]<<'\n';//输出答案
    }
    return 0;
}
```


---

## 作者：tjtdrxxz (赞：6)

这题可以发现，当 $ op = 1 $ 时，从 $ u_i $ 开始，不经过 $ u_i \to v_i $，有两种情况：
- 如果 $ depth_{u_i} > depth_{v_i} $，说明 $ u_i $ 更深，所以这时候只用把以 $ u_i $ 为根的子树的点权都加上 $ x $。
- 如果 $ depth_{u_i} < depth_{v_i} $，说明 $ v_i $ 更深，此时把以 $ 1 $ 为根的子树的点权加上 $ x $，然后把以 $ v_i $ 为根的子树的点权再减去 $ x $ 就好了。

图一：
![](https://cdn.luogu.com.cn/upload/image_hosting/abmoif2y.png)
图二：
![](https://cdn.luogu.com.cn/upload/image_hosting/3vn1f2z6.png)


其中黑色的点和 $ u_i $ 都是要进行操作的点。

$ op = 2 $ 时就一样啦，只是 $ u_i $ 和 $ v_i $ 要交换一下。

code：
```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
namespace __gnu_pbds
{
	template <typename T>
	
	class segment_tree
	{
		private :
			
			struct node
			{
				int l; int r;
				T tag, add;
				T sum;
			}tree[1000012];
			
			int up1 (int a)
			{
				return a << 1;
			}
			int up2 (int a)
			{
				return a << 1 | 1;
			}
			
			void push (int ind)
			{
				tree[ind].sum = tree[up1 (ind)].sum + tree[up2 (ind)].sum;
			}
			
			void check (int ind)
			{
				if (tree[ind].tag)
				{
					tree[up1 (ind)].tag = tree[ind].tag, tree[up1 (ind)].add = 0;
					tree[up2 (ind)].tag = tree[ind].tag, tree[up2 (ind)].add = 0;
					tree[up1 (ind)].sum = (tree[up1 (ind)].r - tree[up1 (ind)].l + 1) * tree[ind].tag;
					tree[up2 (ind)].sum = (tree[up2 (ind)].r - tree[up2 (ind)].l + 1) * tree[ind].tag;
					tree[ind].tag = 0;
					tree[ind].add = 0;
				}
				if (tree[ind].add)
				{
					tree[up1 (ind)].add += tree[ind].add;
					tree[up2 (ind)].add += tree[ind].add;
					tree[up1 (ind)].sum += (tree[up1 (ind)].r - tree[up1 (ind)].l + 1) * tree[ind].add;
					tree[up2 (ind)].sum += (tree[up2 (ind)].r - tree[up2 (ind)].l + 1) * tree[ind].add;
					tree[ind].add = 0;
				}
			}
			
			void build_in (int l, int r, int ind)
			{
				tree[ind].l = l;
				tree[ind].r = r;
				if (l == r)
				{
					tree[ind].sum = 0;
					return;
				}
				int m1 = (l + r) / 2; build_in (l, m1, up1 (ind));
				int m2 = m1 * 1 + 1l; build_in (m2, r, up2 (ind));
			}
			
			void amend_in (int l, int r, T v, int ind)
			{
				if (tree[ind].l >= l and tree[ind].r <= r)
				{
					tree[ind].sum = (tree[ind].r - tree[ind].l + 1) * v * 1.0;
					tree[ind].tag = v, tree[ind].add = 0;
					return;
				}
				check (ind);
				if (tree[up1 (ind)].r >= l) amend_in (l, r, v, up1 (ind));
				if (tree[up2 (ind)].l <= r) amend_in (l, r, v, up2 (ind));
				push (ind);
			}
			
			void change_in (int l, int r, T v, int ind)
			{
				if (tree[ind].l >= l and tree[ind].r <= r)
				{
					tree[ind].sum += (tree[ind].r - tree[ind].l + 1) * v * 1.0;
					tree[ind].add += v;
					return;
				}
				check (ind);
				if (tree[up1 (ind)].r >= l) change_in (l, r, v, up1 (ind));
				if (tree[up2 (ind)].l <= r) change_in (l, r, v, up2 (ind));
				push (ind);
			}
			
			T get (int l, int r, int ind)
			{
				if (tree[ind].l >= l and tree[ind].r <= r)
				{
					return tree[ind].sum;
				}
				check (ind);
				T p1 = 0; if (tree[up1 (ind)].r >= l) p1 = get (l, r, up1 (ind));
				T p2 = 0; if (tree[up2 (ind)].l <= r) p2 = get (l, r, up2 (ind));
				return p1 + p2;
			}
			
		public :
			
			void build (int len)
			{
				build_in (1, len, 1);
			}
			
			void amend (int l, int r, T v)
			{
				change_in (l, r, v, 1);
			}
			
			void change (int l, int r, T v)
			{
				amend_in (l, r, v, 1);
			}
			
			T find (int l, int r)
			{
				return get (l, r, 1);
			}
	};
};
using namespace __gnu_pbds;

segment_tree <int> tree;

int depth[200012], fa[200012], s[200012], son[200012];
int pos, id[200012], top[200012]; vector <int> e[200012];
int a[200012], w[200012];

int n, m, q, k, mod;

inline void dfs1 (int u, int father,int dep)
{
	depth[u] = dep;
	fa[u] = father;
	s[u] = 1;
	int ch = -1;
	for(unsigned int i = 0; i < e[u].size (); i ++)
	{
		int v = e[u][i];
		if (v == father)
		{
			continue;
		}
		dfs1 (v, u, dep + 1);
		s[u] += s[v];
		if (s[v] > ch)
		{
			son[u] = v;
			ch = s[v];
		}
	}
}

inline void dfs2 (int u, int father)
{
	++ pos;
	id[u] = pos;
	a[pos] = w[u];
	top[u] = father;
	if (not son[u])
	{
		return;
	}
	dfs2 (son[u], father);
	for(unsigned int i = 0; i < e[u].size (); i ++)
	{
		int v = e[u][i];
		if (v == fa[u] or v == son[u])
		{
			continue;
		}
		dfs2 (v, v);
	}
}

void amend (int u, int v, int x)
{
	while (top[u] != top[v])
	{
		if (depth[top[u]] < depth[top[v]])
		{
			swap (u, v);
		}
		tree.amend (id[top[u]], id[u], x);
		u = fa[top[u]];
	}
	if (depth[u] > depth[v]) swap (u, v);
	tree.amend (id[u], id[v], x);
}

void change (int u, int v, int x)
{
	while (top[u] != top[v])
	{
		if (depth[top[u]] < depth[top[v]])
		{
			swap (u, v);
		}
		tree.change (id[top[u]], id[u], x);
		u = fa[top[u]];
	}
	if (depth[u] > depth[v]) swap (u, v);
	tree.change (id[u], id[v], x);
}

long long find (int u, int v)
{
	long long ret = 0;
	while (top[u] != top[v])
	{
//		cout << u << ' ' << v << endl;
		if (depth[top[u]] < depth[top[v]])
		{
			swap (u, v);
		}
		ret += tree.find (id[top[u]], id[u]);
		u = fa[top[u]];
	}
	if (depth[u] > depth[v]) swap (u, v);
	ret += tree.find (id[u], id[v]);
	return ret;
}

void amendson (int u, int x)
{
	tree.amend (id[u], id[u] + s[u] - 1, x);
}

long long findson (int u)
{
	return tree.find (id[u], id[u] + s[u] - 1) % mod;
}

int u[200012], v[200012];

signed main ()
{
	cin >> n;
	for (int i = 1; i < n; i ++)
	{
		cin >> u[i] >> v[i];
		e[u[i]].push_back (v[i]);
		e[v[i]].push_back (u[i]);
	}
	tree.build (n);
	dfs1 (1, 0, 0);
	dfs2 (1, 0);
	cin >> m;
	for (int i = 1; i <= m; i ++)
	{
		int op, id, x;
		cin >> op >> id >> x;
		if (op == 1)
		{
			amendson (1, x);
			if (depth[u[id]] < depth[v[id]])
			{
				amendson (v[id], -x);
			}
			else
			{
				amendson (1, -x);
				amendson (u[id], x);
			}
		}
		else
		{
			amendson (1, x);
			if (depth[u[id]] > depth[v[id]])
			{
				amendson (u[id], -x);
			}
			else
			{
				amendson (1, -x);
				amendson (v[id], x);
			}
		}
	}
	for (int i = 1; i <= n; i ++) cout << find (i, i) << endl;
}
```

---

## 作者：GI录像机 (赞：6)

更新：把树上前缀和的说法修正为树上差分。

## 题意：

给定一颗大小为 $N$ 的树，第 $i$ 条边连接 $a_i$ 和 $b_i$，初始每个点权值为 $0$，有 $Q$ 次操作，每次操作给出 $t$、$e$、$x$ 三个数。
- 若 $t=1$，给每个从 $a_e$ 出发不经过 $b_e$ 就能到达的顶点权值加 $x$。
- 若 $t=2$，给每个从 $b_e$ 出发不经过 $a_e$ 就能到达的顶点权值加 $x$。

最后输出每个点的权值。

## 思路：

我们先钦定 $1$ 为根，每条边连接的一定是父亲和儿子。若要加的是从儿子出发不经过父亲到达的点，实际上这些点都在儿子点的子树内；若要加的是从父亲出发不经过儿子到达的点，实际上这些点都在儿子点的子树外。然后修改就变成了给子树加和给非子树加。

给子树加，我们可以用树上差分的方式实现。给非子树加，也就等同于给全局加之后给子树减，也能转化为树上差分。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int n = read(), head[N], tot, sum[N], dep[N], q;
struct Edge {
	int to, nxt;
} e[N << 1];
struct Node {
	int a, b;
} a[N];
void add(int u, int v) {
	e[++tot].to = v;
	e[tot].nxt = head[u];
	head[u] = tot;
}
void dfs(int pos, int fa) {
	dep[pos] = dep[fa] + 1;
	sum[pos] += sum[fa];
	for (int i = head[pos]; i; i = e[i].nxt) {
		if (e[i].to == fa)continue;
		dfs(e[i].to, pos);
	}
}
signed main() {
	for (int i = 1; i < n; i++) {
		a[i].a = read(), a[i].b = read();
		add(a[i].a, a[i].b), add(a[i].b, a[i].a);
	}
	dfs(1, 0);
	q = read();
	for (int i = 1; i <= q; i++) {
		int t = read(), e = read(), x = read();
		if (t == 1) {
			if (dep[a[e].a] < dep[a[e].b]) {
				sum[1] += x;
				sum[a[e].b] -= x;
			} else sum[a[e].a] += x;
		} else {
			if (dep[a[e].a] > dep[a[e].b]) {
				sum[1] += x;
				sum[a[e].a] -= x;
			} else sum[a[e].b] += x;
		}
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++) {
		write(sum[i]);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Muh_Yih (赞：3)

# [ABC187E] Through Path 题解

## 题意

给定一棵 $N$ 节点的树，边形如 $(u_i, v_i)$。维护以下操作 $Q$ 次：

- $op_i = 1$，指定一条边 $i$，将所有从 $u_i$ 出发，**不经过这条边就能到达**的点，点权加 $k$。
- $op_i = 2$，指定一条边 $i$，将所有从 $v_i$ 出发，**不经过这条边就能到达**的点，点权加 $k$。

输出最终每个点的点权。初始点权为 $0$。

## 分析

刚开始看到这道题的时候，我想的是树链剖分——然而很快就~~因码力不足~~将其否决，于是开始考虑树上差分。

让我们来看看样例：

```
7
2 1
2 3
4 2
4 5
6 1
3 7
7
2 2 1
1 3 2
2 2 4
1 6 8
1 3 16
2 4 32
2 1 64
```

规定 1 号节点为根节点，把这棵树画出来，大概是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/8hxywvyh.png)

考虑第 $i$ 次操作为 $op_i,e_i,k_i$，无论 $op_i=1$ 还是 $op_i=2$，都会选中一条边，其中一个顶点作为出发点。

记出发点为 $st$，另一个顶点为 $at$，节点 $x$ 深度为 $depth_x$（$depth_1=1$）。

若 $depth_{st} < depth_{at}$，则修改的节点为树上除 $at$ 的子树（包括 $at$）外的所有节点；若 $depth_{st} > depth_{at}$，则修改的节点为 $st$ 的子树（包括 $st$）。

比如，对于操作 ```2 2 1``` ，有 $st=v_2=3,at=u_2=2;depth_{st}=depth_3=3,depth_{at}=depth_2=2$。此时 $depth_{st} > depth_{at}$。修改节点如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/xhi5n480.png)

对于操作 ```1 6 8``` ，有 $st=u_6=3,at=v_6=7;depth_{st}=depth_3=3,depth_{at}=depth_7=4$。此时 $depth_{st} < depth_{at}$。修改节点如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/5h36577g.png)

于是我们可以建一个差分数组 $d[N]$ ：对于操作 $op_i,e_i,k_i$，若 $depth_{st} < depth_{at}$，则 $d[1]+=k_i,d[at]-=k_i$；若 $depth_{st} > depth_{at}$，则 $d[st]+=k_i$。

最后从根往下统计答案即可。

总体思路：

- 处理深度
- 每次询问修改差分数组
- 统计答案

我的代码中使用 DFS 处理深度，时间复杂度 $O(N)$；每次询问修改差分数组，时间复杂度 $O(Q)$；使用 DFS 统计答案，时间复杂度 $O(N)$；总时间复杂度 $O(N+Q)$。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=410000;
int u[N],v[N],depth[N],chafen[N],ans[N];
int n,q;
vector <int> mp[N];
void depdfs (int x,int fa,int dep)
{
	depth[x]=dep;
	for (int i=0;i<mp[x].size();i++)
	{
		int pt=mp[x][i];
		if (pt!=fa) depdfs (pt,x,dep+1);
	}
}
void chafendfs (int x,int fa,int v)
{
	v+=chafen[x];
	ans[x]=v;
	for (int i=0;i<mp[x].size();i++)
	{
		int pt=mp[x][i];
		if (pt!=fa) chafendfs (pt,x,v);
	}
}
signed main()
{
	scanf ("%lld",&n);
	for (int i=1;i<n;i++)
	{
		scanf ("%lld%lld",u+i,v+i);
		mp[u[i]].push_back(v[i]);mp[v[i]].push_back(u[i]);
	}
	depdfs (1,0,1);
    scanf ("%lld",&q);
	for (int i=1;i<=q;i++)
	{
		int op,e,val;
		scanf ("%lld%lld%lld",&op,&e,&val);
		int ch,nch,chd,nchd;
		if (op==1)
		{
			ch=u[e],nch=v[e];
			chd=depth[ch],nchd=depth[nch];
			if (chd<nchd) chafen[1]+=val,chafen[nch]-=val;
			else chafen[ch]+=val;
		}
		if (op==2)
		{
			ch=v[e],nch=u[e];
			chd=depth[ch],nchd=depth[nch];
			if (chd<nchd) chafen[1]+=val,chafen[nch]-=val;
			else chafen[ch]+=val;
		}
	}
	chafendfs (1,0,0);
	for (int i=1;i<=n;i++) printf ("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：yinbe (赞：2)

## 题目描述

给定一棵树，边形如 $(u_i, v_i)$。维护以下操作：

- $op_i = 1$，指定一条边，将所有从 $u_i$ 出发，**不经过这条边就能到达**的点，点权加 $k$。
- $op_i = 2$，指定一条边，将所有从 $v_i$ 出发，**不经过这条边就能到达**的点，点权加 $k$。

输出最终每个点的点权。初始点权为 $0$。

### 数据范围

- $2\ \le\ N\ \le\ 2\ \times\ 10^5$
- $1\ \le\ a_i,\ b_i\ \le\ N$
- $1\ \le\ Q\ \le\ 2\ \times\ 10^5$
- $t_i\ \in\ \{1,\ 2\}$
- $1\ \le\ e_i\ \le\ N-1$
- $1\ \le\ x_i\ \le\ 10^9$

## 思路

题目很抽象，先理解一下题目在做什么。

约定：$c_{i}$ 表示顶点 $i$ 的权值，默认以 $1$ 为根，默认 $u_{i}$ 为 $v_{i}$ 的父亲。

- $op_i = 1$，指定一条边，将所有从 $u_i$ 出发，**不经过这条边就能到达**的点，点权加 $k$。

因为这是一棵树，所以从 $u_{i}$ 不经过 $v_{i}$ 是不能到达以 $v_{i}$ 为根的子树上的顶点，所以操作 $1$ 就相当于将除以 $v_{i}$ 为根的子树上的顶点以外的顶点的点权加 $x$。

同理，从 $v_{i}$ 不经过 $u_{i}$ 就只能到以 $v_{i}$ 为根的子树上的顶点，所以操作 $2$ 就相当于将以 $v_{i}$ 为根的子树上的顶点的点权加 $x$。

如何对一整个子树进行操作呢？DFS 序是我们在对树进行 DFS 时，对于每个顶点，在刚进入递归后以及即将回溯前各记录一次该点的编号，最后产生的长度为 $2\times n$ 的序列就是 DFS 序，DFS 序的特点是：设点 $x$ 两次出现的位置为 $l_{x}$ 和 $r_{x}$，那么 $\left [ l_{x},r_{x} \right ]$ 就是以 $x$ 为根的子树的 DFS 序。所以我们可以求出树的 DFS 序，$2$ 操作将以 $v_{i}$ 为根的子树上的顶点的点权加 $x$ 就是把 $\left [ l_{v_{i}},r_{v_{i}} \right ]$ 这段区间加 $x$，$1$ 操作就是把 $\left [ 1,l_{v_{i}}-1 \right ]$ 和 $\left [r_{v_{i}} +1,2\times n\right ]$ 这 $2$ 段区间加 $x$，对于这种问题，我们可以使用差分、树状数组 $+$ 差分、线段树等来解决，后两者可以解决这道题的加强版：多次询问、强制在线（虽然没有这道题，了解一下也挺好）。

## 代码

### 差分

```cpp
#include<iostream>
using namespace std;
int n,tot,head[400005],nxt[400005],ver[400005],depth[200005];
long long d[400005],s[400005];
int dfn[200005],low[200005],num;
int T;
struct road
{
	int u,v;
}r[200005];
void dfs(int x,int f,int d)
{
	depth[x]=d;
	num++;
	dfn[x]=num;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=ver[i];
		if(y!=f)dfs(y,x,d+1);
	}
	num++;
	low[x]=num;
}
void add(int x,int y)
{
	tot++;
	ver[tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
		r[i].u=a;
		r[i].v=b;
	}
	dfs(1,0,0);
	scanf("%d",&T);
	while(T--)
	{
		int op,e,x;
		scanf("%d%d%d",&op,&e,&x);
		int u=r[e].u,v=r[e].v;
		if(depth[u]>depth[v])
		{
			swap(u,v);
			op=3-op;
		}
		if(op==1)
		{
			d[1]+=x;
			d[dfn[v]]-=x;
			d[low[v]+1]+=x;	
			d[num+1]-=x;
		}
		else
		{
			d[dfn[v]]+=x;
			d[low[v]+1]-=x;
		}
	}
	for(int i=1;i<=num;i++)s[i]=s[i-1]+d[i];
	for(int i=1;i<=n;i++)printf("%lld\n",s[dfn[i]]);
	return 0;
}
```

### 树状数组

```cpp
#include<iostream>
using namespace std;
int n,tot,head[400005],nxt[400005],ver[400005],depth[200005];
long long d[400005];
int dfn[200005],low[200005],num;
int T;
struct road
{
	int u,v;
}r[200005];
void dfs(int x,int f,int d)
{
	depth[x]=d;
	num++;
	dfn[x]=num;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=ver[i];
		if(y!=f)dfs(y,x,d+1);
	}
	num++;
	low[x]=num;
}
void change(int x,int y)
{
	for(;x<=num;x+=x&-x)d[x]+=y;
}
long long ask(int x)
{
	long long ans=0;
	for(;x;x-=x&-x)ans+=d[x];
	return ans;
}
void add(int x,int y)
{
	tot++;
	ver[tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
		r[i].u=a;
		r[i].v=b;
	}
	dfs(1,0,0);
	scanf("%d",&T);
	while(T--)
	{
		int op,e,x;
		scanf("%d%d%d",&op,&e,&x);
		int u=r[e].u,v=r[e].v;
		if(depth[u]>depth[v])
		{
			swap(u,v);
			op=3-op;
		}
		if(op==1)
		{
			change(1,x);
			change(dfn[v],-x);
			change(low[v]+1,x);
			change(num+1,-x);
		}
		else
		{
			change(dfn[v],x);
			change(low[v]+1,-x);
		}
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ask(dfn[i]));
	return 0;
}
```

### 线段树

```cpp
#include<iostream>
using namespace std;
int n,tot,head[400005],nxt[400005],ver[400005],depth[200005];
int dfn[200005],low[200005],num;
int T;
struct road
{
	int u,v;
}r[200005];
struct tree
{
	int l,r;
	long long sum,add;
	#define l(x) t[x].l
	#define r(x) t[x].r
	#define sum(x) t[x].sum
	#define add(x) t[x].add
}t[1600005];
void build(int p,int l,int r)
{
	l(p)=l,r(p)=r;
	if(l==r)
	{
		return;
	}
	int mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	return;
}
void spread(int p)
{
	if(add(p))
	{
		sum(p*2)+=add(p)*(r(p*2)-l(p*2)+1);
		sum(p*2+1)+=add(p)*(r(p*2+1)-l(p*2+1)+1);
		add(p*2)+=add(p);
		add(p*2+1)+=add(p);
		add(p)=0;
	}
}
void change(int p,int l,int r,int d)
{
	if(l<=l(p)&&r>=r(p))
	{
		sum(p)+=(long long)(d)*(r(p)-l(p)+1);
		add(p)+=d;
		return;
	}
	spread(p);
	int mid=(l(p)+r(p))>>1;
	if(l<=mid)change(p*2,l,r,d);
	if(r>mid)change(p*2+1,l,r,d);
	sum(p)=sum(p*2)+sum(p*2+1);
	return;
}
long long ask(int p,int x)
{
	if(l(p)==r(p))
	{
		return sum(p);
	}
	spread(p);
	int mid=(l(p)+r(p))>>1;
	if(x<=mid)return ask(p*2,x);
	else return ask(p*2+1,x);
}
void dfs(int x,int f,int d)
{
	depth[x]=d;
	num++;
	dfn[x]=num;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=ver[i];
		if(y!=f)dfs(y,x,d+1);
	}
	num++;
	low[x]=num;
}
void add_bian(int x,int y)
{
	tot++;
	ver[tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add_bian(a,b);
		add_bian(b,a);
		r[i].u=a;
		r[i].v=b;
	}
	dfs(1,0,0);
	build(1,1,2*n);
	scanf("%d",&T);
	while(T--)
	{
		int op,e,x;
		scanf("%d%d%d",&op,&e,&x);
		int u=r[e].u,v=r[e].v;
		if(depth[u]>depth[v])
		{
			swap(u,v);
			op=3-op;
		}
		if(op==1)
		{
			change(1,1,dfn[v]-1,x);
			change(1,low[v]+1,num,x);
		}
		else
		{
			change(1,dfn[v],low[v],x);
		}
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ask(1,dfn[i]));
	return 0;
}
```

---

## 作者：Exp10re (赞：2)

我爱线段树。

提供一种线段树思路，~~以防以后遇到要求在线询问的相同题目。~~

## 解题思路

考虑对把树上结点的操作转化成区间操作，先钦定 1 为整棵树的根，然后跑一遍 DFS 记录节点的 DFS 序以及其子树的时间戳。

于是对于某个子树的修改就能转化成对其时间戳范围内的区间修改。

假定对于某一条边连接的两个点 $p$ 与 $q$，$p$ 是 $q$ 的父节点，若 $q$ 的时间戳范围为 $[l,r]$，那么对于题目中的某一次操作，如果选中了点 $q$，那么可以直接对 $[l,r]$ 进行区间修改，如果选中了点 $p$，那么可以对 $[1,N]$ 范围内的，所有不包含在 $q$ 的时间戳范围内的位置进行修改，容易发现这些位置至多包含在两个区间 $[1,l-1]$ 和 $[r+1,N]$ 内，所以两种修改都可以用线段树维护。

时间复杂度 $O(Q \log N)$，代码也比较长，显然是比不上树上差分的，但是可以解决在线询问就是这份代码的优点。

## 代码

代码太长就不贴在这里了，直接放剪贴板了。

[Code.](https://www.luogu.com.cn/paste/saezbx2g)

---

## 作者：lilong (赞：2)

考虑将 $1$ 号点定为树根，然后通过搜索确定结点之间的父子关系。对于每次操作，先判断该边两端的点的父子关系，然后再分类讨论进行操作。

如何维护每个点的点权呢？注意到，修改有很多次，但查询只在最后有一次，因此可以考虑树上差分。具体地，设 $a_i$ 表示 $i$ 的点权，$f_i$ 表示 $i$ 的父亲，$sum_i$ 表示 $a_i$ 与 $a_{f_i}$ 的差，对每次操作进行分类讨论。

假设选定边连接的点分别为 $u$ 和 $v$，且 $f_v=u$，则有如下情况：

- 从 $v$ 出发。等同于给**以 $v$ 为根的子树**的每个点点权加上 $k$，将 $sum_v$ 加上 $k$ 即可。

- 从 $u$ 出发。等同于给**除以 $v$ 为根的子树外**的每个点点权加上 $k$，也可理解为**全部点**点权加上 $k$，再给**以 $v$ 为根的子树**的每个点点权减去 $k$（相当于没有操作，符合要求）。将 $sum_1$ 加上 $k$，$sum_v$ 减去 $k$ 即可。

完成全部操作后，再进行一次搜索，通过差分数组求出每个点的点权，输出答案。

时间复杂度 $O(n+q)$，代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define int long long
#define N 1000001

using namespace std;

vector<int> G[N];
int n,m,fa[N],t,nw,k,u[N],v[N],sum[N],ans[N],tot;

void dfs( int nowu )
{
	for( int i = 0 ; i < G[nowu].size() ; i ++ )
	{
		int nowv = G[nowu][i];
		if( !fa[nowv] )
		{
			fa[nowv] = nowu;
			dfs( nowv );
		}
	}
}

void dfsans( int nowu , int s )
{
	ans[nowu] += s;
	for( int i = 0 ; i < G[nowu].size() ; i ++ )
	{
		int nowv = G[nowu][i];
		if( fa[nowv] == nowu )
			dfsans( nowv , s + sum[nowv] );
	}
}

signed main()
{
	int T;
	cin >> n;
	m = n - 1;
	for( int i = 1 ; i <= m ; i ++ )
	{
		cin >> u[i] >> v[i];
		G[u[i]].push_back( v[i] );
		G[v[i]].push_back( u[i] );		
	}
	fa[1] = 1;
	dfs( 1 );
	cin >> T;
	while( T -- )
	{
		cin >> t >> nw >> k;
		if( t == 1 )
		{
			if( fa[u[nw]] == v[nw] ) sum[u[nw]] += k;
			else
			{
				sum[1] += k;
				sum[v[nw]] -= k;
			}
		}
		else
		{
			if( fa[v[nw]] == u[nw] ) sum[v[nw]] += k;
			else
			{
				sum[1] += k;
				sum[u[nw]] -= k;
			}
		}
	}
	dfsans( 1 , sum[1] );
	for( int i = 1 ; i <= n ; i ++ )
		cout << ans[i] << endl;
	return 0;
}
```


---

## 作者：吴思诚 (赞：2)

# [[ABC187E] Through Path](https://www.luogu.com.cn/problem/AT_abc187_e)

## 思路

我们考虑利用 `dfs` 序将树转换成一个序列（树链剖分中的一小部分），如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/l5oxdkf2.png)

图上的括号里有两个参数，第一个参数 $in_u$ 就是所谓的 `dfs` 序，而后面的 $out_u$ 则是这个点为根的子树中 `dfs` 序最大的点的 `dfs` 序。

这两个参数对应的就是以某个点为根的子树内的所有点，如 $(2,5)$ 即以 $2$ 为根的子树（$dfs_2=2,dfs_3=5,dfs_4=3,dfs_5=4$）。

然后现在我们要进行操作，我们钦定 $(u,v)$ 边中，$u$ 为 $v$ 的父亲，然后我们考虑从 $u$ 出发和从 $v$ 出发。

1. 从 $u$ 出发，那么除了 $v$ 的子树内点无法到达，其余的所有点均可达，那么修改 $1\sim in_v-1,out_v+1\sim n$。
2. 从 $v$ 出发，那么只有 $v$ 的子树内点可达，修改 $in_v\sim out_v$。

可以发现查询是在操作做完之后，所以考虑做一遍序列上的差分即可。

## [代码](https://atcoder.jp/contests/abc187/submissions/44161938)



---

## 作者：Super_Cube (赞：1)

# Solution

先随便选根把树的形态定下。对于树上相邻节点 $(u,v)$，若 $u$ 为 $v$ 的父亲，那么 $u$ 不经过这条边所能到达的节点就是整棵树除去 $v$ 及其子树的部分；反之若 $v$ 为 $u$ 的父亲，那么 $u$ 不经过这条边所能到达的节点就是 $u$ 及其子树部分。

所以现在需要维护子树加，最后查询所有节点的点权。由于不要求在线，可通过树上前缀和做到线性。

时间复杂度：$O(n+q)$。

# Code
```cpp
#include<bits/stdc++.h>
struct edge{
	int nxt,to;
}v[400005];
int head[200005],edx=1;
inline void adds(int x,int y){
	++edx;
	v[edx].nxt=head[x];v[edx].to=y;
	head[x]=edx;
}
int dep[200005];
void dfs(int p,int dad){
	dep[p]=dep[dad]+1;
	for(int i=head[p];i;i=v[i].nxt)
		if(v[i].to!=dad)dfs(v[i].to,p);
}
long long sum[200005];
void solve(int p,int dad){
	for(int i=head[p];i;i=v[i].nxt)
		if(v[i].to!=dad)
			sum[v[i].to]+=sum[p],solve(v[i].to,p);
}
int n,m;
int main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<n;++i)
		scanf("%d%d",&x,&y),
		adds(x,y),adds(y,x);
	dfs(1,0);
	scanf("%d",&m);
	for(int op,x,y;m--;){
		scanf("%d%d%d",&op,&x,&y);
		if(op==1){
			if(dep[v[x<<1|1].to]>dep[v[x<<1].to])sum[v[x<<1|1].to]+=y;
			else sum[1]+=y,sum[v[x<<1].to]-=y;
		}else{
			if(dep[v[x<<1].to]>dep[v[x<<1|1].to])sum[v[x<<1].to]+=y;
			else sum[1]+=y,sum[v[x<<1|1].to]-=y;
		}
	}
	solve(1,0);
	for(int i=1;i<=n;++i)
		printf("%lld\n",sum[i]);
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：1)

题目大意不用多讲，大家都懂。      
这是根据样例一画的图。      
![](https://cdn.luogu.com.cn/upload/image_hosting/lrxnn2lf.png)   
首先，为了方便后面处理，我们使用节点一为根，利用树链剖分，求出每个点的深度以及整棵树的 DFS 序列。        
因为一棵子树在 DFS 序列中是一连串的，所以一棵子树可以看做一个连续的区间；而区间修改单点查询，可使用差分数组维护。
接着我们判断我们的方向是由下往上还是由上往下。    
这里的方向不是我们通常说的方向，举个例子，样例一中 `1 1 1` 的意思是从节点 $1$ 出发，不能经过节点 $2$，而从节点 $1$ 到 节点 $2$ 是往下的，我们就说这个方向是由上往下。       
 - 如果是由上往下，那么我们把整棵树每个点的权值都加 $k$，再把以那个不能走的点为根的子树每个点的权值减去 $k$。   
 如同这个 `1 1 1` 的例子，我们把一整棵树每个点的权值加 $1$，再把以节点 $2$ 为根的子树每个点的权值减去 $1$。
 - 如果是由下往上，那么我们把以起点为根的子树每个点的权值加上 $k$。  
 如同 `2 1 100` 的例子，我们从 $2$ 出发，不能经过 $1$，那么我们只需要把以节点 $2$ 为根的子树每个点的权值加上 $100$ 即可。   
 
最后询问的时候就把差分数组的前缀求出来，便可得到原数组。      
```cpp
#include<stdio.h>
#include<string.h>
long long n,q,first[200005],num,numm,a,b,c,x[200005],y[200005];
long long size[200005],father[200005],son[200005],top[200005],duiying[200005],cf[200005];
struct sss{long long end,next;}bian[400005];
void dfs1(long long where,long long fa)
{
    for(int i=first[where];i;i=bian[i].next) if(bian[i].end!=fa)
    {
        father[bian[i].end]=where,dfs1(bian[i].end,where),size[where]+=size[bian[i].end];
        if(size[son[where]]<size[bian[i].end]) son[where]=bian[i].end;
    }
    size[where]++;
}
void dfs2(long long where,long long tops)
{
    top[where]=tops,duiying[where]=++numm;
    if(!son[where]) return;
    dfs2(son[where],tops);
    for(int i=first[where];i;i=bian[i].next) if(bian[i].end!=son[where]&&bian[i].end!=father[where])
    dfs2(bian[i].end,bian[i].end);
}
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<n;i++) scanf("%lld%lld",&a,&b),x[i]=a,y[i]=b,
    bian[++num].end=b,bian[num].next=first[a],first[a]=num,
    bian[++num].end=a,bian[num].next=first[b],first[b]=num;
    dfs1(1,0),dfs2(1,1);
    scanf("%lld",&q);
    while(q--)
    {
        scanf("%lld%lld%lld",&a,&b,&c);
        long long num1,num2;
        if(a==1)
        {
            num1=duiying[x[b]],num2=duiying[y[b]];
            if(num1<num2) cf[1]+=c,cf[n+1]-=c,cf[duiying[y[b]]]-=c,cf[duiying[y[b]]+size[y[b]]]+=c;
            else cf[duiying[x[b]]]+=c,cf[duiying[x[b]]+size[x[b]]]-=c;
        }
        else
        {
            num1=duiying[y[b]],num2=duiying[x[b]];
            if(num1<num2) cf[1]+=c,cf[n+1]-=c,cf[duiying[x[b]]]-=c,cf[duiying[x[b]]+size[x[b]]]+=c;
            else cf[duiying[y[b]]]+=c,cf[duiying[y[b]]+size[y[b]]]-=c;
        }
    }
    for(int i=1;i<=n;i++) cf[i]+=cf[i-1];
    for(int i=1;i<=n;i++) printf("%lld\n",cf[duiying[i]]);
}
```

---

## 作者：hanchengyi (赞：0)

## 思路

对于树上点权修改和询问的操作，显然想到树链剖分。

![](https://cdn.luogu.com.cn/upload/image_hosting/xets0su2.png)

对于两个操作，本质一样，只有指定点不同。假设我们选定上图中标注的边。

如果选定 $4$ 号点，能到达的显然就是以 $4$ 为根的子树。

如果选定 $3$ 号点，能到达的不再是简单的子树或链。但是我们换一种思路想，$3$ 号点不能到达的是以 $4$ 为根的子树，所以能到达的就是整棵树减去以 $4$ 为根的子树。

具体地，我们用线段树实现对子树的修改操作，最后查询每个节点的权值就行了。

## 代码

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define endl '\n'
#define int long long
using namespace std;
const int N=8e5+7;
const int M=8e5+7;

int h[M],nt[M],v[M];
int tot;
void add(int x,int y){
	v[++tot]=y;
	nt[tot]=h[x];
	h[x]=tot;
}
int dep[N],siz[N],son[N],top[N],seg[N],rev[N];
int f[N];
int cnt;
int a[N];
struct Seg{
	struct node{
		int l,r,val,ly;
	}t[M];
	#define ls (p<<1)
	#define rs (p<<1|1)
	friend node operator + (const node &a,const node &b){
		node res;
		res.ly=0;
		res.l=a.l,res.r=b.r;
		res.val=a.val+b.val;
		return res;
	}
	void build(int l,int r,int p){
		t[p].l=l,t[p].r=r;
		if(l==r){
			t[p].val=0;
			return ;
		}
		int mid=l+r>>1;
		build(l,mid,ls);
		build(mid+1,r,rs);
		t[p]=t[ls]+t[rs];
	}
	void pushdown(int p){
		if(t[p].ly!=0){
			t[ls].ly+=t[p].ly,t[rs].ly+=t[p].ly;
			t[ls].val+=t[p].ly*(t[ls].r-t[ls].l+1);
			t[rs].val+=t[p].ly*(t[rs].r-t[rs].l+1);
			t[p].ly=0;
		}
	}
	void modify(int l,int r,int v,int p){
		if(l<=t[p].l&&t[p].r<=r){
			t[p].ly+=v;
			t[p].val+=v*(t[p].r-t[p].l+1);
			return ;
		}
		pushdown(p);
		int mid=t[p].l+t[p].r>>1;
		if(l<=mid) modify(l,r,v,ls);
		if(r>mid) modify(l,r,v,rs);
		t[p]=t[ls]+t[rs];
	}
	node query(int l,int r,int p){
		if(l<=t[p].l&&t[p].r<=r)
			return t[p];
		pushdown(p);
		int mid=t[p].l+t[p].r>>1;
		if(r<=mid) return query(l,r,ls);
		if(l>mid) return query(l,r,rs);
		return query(l,r,ls)+query(l,r,rs);
	}
}T;
void dfs1(int x,int fa){
	siz[x]=1;
	f[x]=fa;
	dep[x]=dep[fa]+1;
	for(int i=h[x];i;i=nt[i]){
		int y=v[i];
		if(y==fa) continue ;
		dfs1(y,x);
		siz[x]+=siz[y];
		if(siz[y]>siz[son[x]]) son[x]=y;
	}
}
void dfs2(int x,int fa){
	top[x]=fa;
	seg[x]=++cnt;
	rev[cnt]=x;
	if(!son[x]) return ;
	dfs2(son[x],fa);
	for(int i=h[x];i;i=nt[i]){
		int y=v[i];
		if(y==f[x]||y==son[x]) continue;
		dfs2(y,y);
	}
}
void update_tree(int x,int v){
	T.modify(seg[x],seg[x]+siz[x]-1,v,1);
}
int query_chain(int x,int y){
	int ans=0;
	Seg::node tmp;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		tmp=T.query(seg[top[x]],seg[x],1);
		ans+=tmp.val;		
		x=f[top[x]];		
	}
	if(dep[x]>dep[y]) swap(x,y);
	tmp=T.query(seg[x],seg[y],1);
	ans+=tmp.val;
	return ans;
}
int n,m,r,p;
int ex[N],ey[N];
signed main(){
	cin>>n;
	int x,y;
	for(int i=1;i<=n-1;i++){
		cin>>x>>y;
		add(x,y);add(y,x);
		ex[i]=x,ey[i]=y;
	}
	r=1;
	cnt=0;
	dfs1(r,0);
	dfs2(r,r);
	T.build(1,n,1);
	int op,z,id;
	cin>>m;
	while(m--){
		cin>>op>>id>>z;
		x=ex[id],y=ey[id];
		if(op==1){
			if(dep[x]<dep[y]){
				update_tree(1,z);
				update_tree(y,-z);
				/*
				先给整棵树加 k，再给以 y为根的子树减 k，就实现了对 x能到达的点加 k 
				*/
			}else{
				update_tree(x,z);
			}
		}else if(op==2){
			if(dep[x]>dep[y]){
				update_tree(1,z);
				update_tree(x,-z);
			}else{
				update_tree(y,z);
			}
		}

	} 
	for(int i=1;i<=n;i++) cout<<query_chain(i,i)<<endl;
	return 0;
}
/*
7
2 1
2 3
4 2
4 5
6 1
3 7
3
1 3 2
1 6 8
1 3 16
*/ 
```

---

## 作者：VitrelosTia (赞：0)

这么一眼的题写了快 1h，我太唐了。

首先题目条件中的两种操作其实是一样的，形如“走到 $u$ 而不走到 $v$ 的点，点权加 $k$”。

考虑分类讨论，第一种是 $dep_u > dep_v$，由于一个节点的父亲唯一，那么 $v$ 就是 $u$ 的父亲，此时操作的点就是 $u$ 子树内的点。反之则 $u$ 是 $v$ 的父亲，那么操作的点就是 $v$ 子树外的点，画一下图应该容易理解。

我们知道一个子树的 dfn 序是连续的，那么对于一个子树 内/外 的操作就是容易的，考虑到不需要在线回答，那么把 dfn 序拍到序列上差分即可简单维护。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int n, Q, u[N], v[N];

struct Edge { int to, nxt; } e[N << 1];
int cur, head[N];
void Add(int u, int v) { e[++cur] = {v, head[u]}; head[u] = cur; }
#define GoEdge(i, u, v) for (int v, i = head[u]; v = e[i].to, i; i = e[i].nxt)

int idx, dfn[N], rnk[N], dep[N], siz[N];
void dfs(int u, int fa) {
	dfn[u] = ++idx, rnk[idx] = u; dep[u] = dep[fa] + 1, siz[u] = 1;
	GoEdge(i, u, v) if (v != fa) {
		dfs(v, u);
		siz[u] += siz[v];
	}
}

int ds[N], ans[N];
void update(int l, int r, int k) { if (l <= r) ds[l] += k, ds[r + 1] -= k; }

signed main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i < n; i++) {
		cin >> u[i] >> v[i];
		Add(u[i], v[i]); Add(v[i], u[i]);
	}
	dfs(1, 0);
	cin >> Q; for (int opt, i, k, x, y; Q--; ) {
		cin >> opt >> i >> k; x = u[i], y = v[i];
		if (opt == 2) swap(x, y); // go to x without y
		if (dep[x] < dep[y]) update(1, dfn[y] - 1, k), update(dfn[y] + siz[y], n, k);
		else update(dfn[x], dfn[x] + siz[x] - 1, k);
	}
	for (int i = 1; i <= n; i++) ds[i] += ds[i - 1], ans[rnk[i]] = ds[i];
	for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：Network_Flow (赞：0)

### 题意：

给定一棵树，按照规则给加点权，输出每个点的最终点权。

### 做法：
直接暴力是 $O(nq)$ 的，显然会超时。我们可以发现，进行一次操作的时候，只有修改自己的子树或者修改非自己子树所有点两种操作，可以使用树上差分来维护这样连续的一段区间。

所以我们规定 $1$ 为根，每次如果操作的是深度大的点就对它及它的子树操作，深度小的则是它和它的非子树。最后跑一遍 dfs 统计答案即可。

注意要开 long long，时间复杂度 $O(n+q)$

### AC Code:
```cpp
#include <iostream>
#include <cstdio>
#include <map>
#define SIZE 200005

using namespace std;
long long head[SIZE], nxt[2*SIZE], ver[2*SIZE], tot, w[SIZE], n, q, cnt, dep[SIZE];
void add(long long x, long long y){ //建图
	ver[++tot]=y, nxt[tot]=head[x], head[x]=tot;
}
map<long long, pair<long long, long long> > s;
void dfs(long long x, long long fa){ //计算深度，方便判断
	for (long long i=head[x]; i; i=nxt[i]){
		long long y=ver[i];
		if(y==fa) continue;
		dep[y]=dep[x]+1;
		dfs(y, x);
	}
}
void dfs1(long long x, long long fa, long long cnt){ //统计差分答案
	long long tmp=cnt+w[x];
	w[x]+=cnt;
	for (long long i=head[x]; i; i=nxt[i]){
		long long y=ver[i];
		if(y==fa) continue;
		dfs1(y, x, tmp);
	}
}
int main(){
	scanf("%lld", &n);
	for (long long i=1; i<n; i++){
		long long x, y;scanf("%lld%lld", &x, &y);
		add(x, y), add(y, x);
		s[i]=make_pair(x, y);
	}
	dfs(1, 0);
	scanf("%lld", &q);
	while(q--){
		long long opt, e, k;
		scanf("%lld%lld%lld", &opt, &e, &k);
		long long x=s[e].first, y=s[e].second;
		if(opt==1){
			if(dep[x]<dep[y]) w[1]+=k, w[y]-=k; //如果 x 深度比 y 小，则说明操作的是 x 的非子树
			else w[x]+=k;//反之操作的是 x 的子树
		}
		if(opt==2){ //同理
			if(dep[x]<dep[y]) w[y]+=k;
			else w[1]+=k, w[x]-=k;
		}
	}
	dfs1(1, 0, 0);
	for (long long i=1; i<=n; i++) printf("%lld\n", w[i]);
	
	return 0;
}
```

---

## 作者：ForgetOIDuck (赞：0)

### 思路

为了方便处理，首先我们把整棵树搞成一棵有根树，并把每个点的深度搞出来。

对于每个操作，这条边上两个点的深度就有两种情况：

- 操作点的深度比另一个点的深度大，则操作转化为所有 **操作点子树内** 的节点点权加上 $x$（设为操作 $1$）；
- 操作点的深度比另一个点的深度小，则操作转化为所有 **非操作点子树内** 的节点点权加上 $x$（设为操作 $2$）。

我们发现这东西似乎是可以树上差分的。

对于每个操作 $1$相当于整个子树加上 $x$，只需要给操作点加上 $x$。

对于每个操作 $2$ 相当于先给全局加上 $x$，再给另一个点的子树减去 $x$，也就是给根结点先加上 $x$，再给另一个点减去 $x$。

时间复杂度 $O(N)$。
### AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll q, n, a[200002], idx, b[200002], e[400002], ne[400002], h[200002], as, s[200002], dep[200002];
void add(ll x, ll y) {
	e[idx] = y, ne[idx] = h[x], h[x] = idx ++;
}
void dph(ll x, ll fa, ll dp) {
	dep[x] = dp;
	for (ll i = h[x]; i != -1; i = ne[i]) {
		ll y = e[i];
		if (y != fa) dph(y, x, dp + 1); 
	}
}
void dfs(ll x, ll fa) {
	s[x] += s[fa];
	for (ll i = h[x]; i != -1; i = ne[i]) {
		ll y = e[i];
		if (y != fa) dfs(y, x);
	}
}
int main() {
	memset(h, -1, sizeof h);
	cin >> n;
	for (ll i = 1; i < n; i ++ ) cin >> a[i] >> b[i], add(a[i], b[i]), add(b[i], a[i]);
	dph(1, 1, 1);
	cin >> q;
	for (ll t, e, x; q --; ) {
		cin >> t >> e >> x;
		if (t == 1) {
			if (dep[a[e]] < dep[b[e]]) as += x, s[b[e]] -= x;
			else s[a[e]] += x;
		} 
		else {
			if (dep[b[e]] < dep[a[e]]) as += x, s[a[e]] -= x;
			else s[b[e]] += x;
		}
	}
	dfs(1, 0);
	for (ll i = 1; i <= n; i ++ ) cout << s[i] + as << endl;
}
```

使用 cin,cout 似乎会爆 1s，但是本题较良心给出了 2s 的时限。拜谢远古 AtCoder。

---

## 作者：Down_syndrome (赞：0)

## 题意
对一棵树进行修改，输出最后的点权。

## 思路
具体分析一下两种操作。可以发现，如果操作的是深度小的点，相当于把**除了深度大的点的子树中的点以外的点**的点权加上对应的值；如果操作的是深度大的点，相当于把**这个点的子树中的点**的点权加上对应的值。这显然可以树上差分。这里提供一种差分的思路。我们知道，在同一棵子树上的点的 dfs 序是连续的。所以，我们可以把每个点的 dfs 序和子树大小求出来，直接把树上差分转换为一般的数组差分，最后做一遍前缀和，求出答案就行了。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const int M=4e5+5; 
int n,m,op,x,y,cnt,u[M],v[M],to[M],nxt[M],h[N],dep[N],add[N],dfn[N],siz[N];
void save(int u,int v){
	to[++cnt]=v;
	nxt[cnt]=h[u];
	h[u]=cnt;
}
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	dfn[u]=++cnt;//dfs序
	siz[u]=1;
	for(int i=h[u];i;i=nxt[i]){
		if(to[i]==fa) continue;
		dfs(to[i],u);
		siz[u]+=siz[to[i]];
	}
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<n;i++){
		scanf("%lld%lld",&u[i],&v[i]);
		save(u[i],v[i]);
		save(v[i],u[i]);
	}
	cnt=0;
	dfs(1,0);
	scanf("%lld",&m);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld",&op,&x,&y);
		if(op==2) swap(u[x],v[x]);//方便操作
		if(dep[u[x]]<dep[v[x]]){//对应的差分
			add[1]+=y;
			add[dfn[v[x]]]-=y;
			add[dfn[v[x]]+siz[v[x]]]+=y;
		}
		else{
			add[dfn[u[x]]]+=y;
			add[dfn[u[x]]+siz[u[x]]]-=y;
		}
		if(op==2) swap(u[x],v[x]);
	}
	for(int i=1;i<=n;i++) add[i]+=add[i-1];
	for(int i=1;i<=n;i++) printf("%lld\n",add[dfn[i]]);
	return 0;
}
```

---

