# Messages on a Tree

## 题目描述

有一棵编号为$0$~$n$的树，$0$为根节点

在一些时刻，某一些节点会向根节点发送信息并开始等待收到根节点的回复，**这些节点被称作发送者**，向根节点发送信息的过程是将信息沿着父节点不断向上传递，**经过的节点都将开始等待根节点的回复**，根节点收到信息后立刻回复，回复的过程是逆着刚才的路径向下传递直至传递回发送信息的节点。

但在这一过程中，如果向上传递信息时遇到的某一个节点本身正在等待根节点的回复，那么这个节点会拒绝向上传递并直接向下回复一个终止的信息，这一向下的过程与从根节点向下回复的过程相同。

父子节点之间传递信息的过程需要花费$1$单位时间

如果一个节点同时收到了很多来自子节点的信息，那么这个节点只处理来自编号最小的**发送者**（不是子节点！！！），然后拒绝剩余的所有信息

如果一个节点同时收到了来自子节点的信息和来自父节点的回复，那么向下传递回复和向上传递信息的过程可以同时进行

如果一个节点在等待的过程中自己成为了发送者，那么这条信息被立刻拒绝，所用时间是$0$

## 样例 #1

### 输入

```
6 3
0 1 2 3 2 5
4 6
6 9
5 11
```

### 输出

```
14 13 11 ```

## 样例 #2

### 输入

```
3 2
0 1 1
2 1
3 1
```

### 输出

```
5 3 ```

## 样例 #3

### 输入

```
8 3
0 1 1 2 3 3 4 5
6 1
8 2
4 5
```

### 输出

```
7 6 11 ```

# 题解

## 作者：FZzzz (赞：3)

怎么没有题解，水一篇。

考虑每条信息经过的过程一定是：从起点出发往上走到某个节点，然后走回来。所以我们只关心它能走到哪个节点。考虑若信息 $i$ 走到了节点 $y_i\ne1$，此时节点 $y_i$ 正在处理信息 $j$，那么：
$$\begin{cases}(t_j+d_{x_j}-d_{y_i},x_j)<(t_i+d_{x_i}-d_{y_i},x_i)\\t_i+d_{x_i}-d_{y_i}<t_j+d_{x_j}+d_{y_i}-2d_{y_j}\end{cases}$$
其中 $d_u$ 表示节点 $u$ 的深度，二元组的比较是先比较第一关键字，若相等再比较第二关键字。整理一下：
$$\begin{cases}(t_j+d_{x_j},x_j)<(t_i+d_{x_i},x_i)\\t_i+d_{x_i}<t_j+d_{x_j}+2d_{y_i}-2d_{y_j}\end{cases}$$
因此我们将信息按 $t_i+d_{x_i}$ 为第一关键字，$x_i$ 为第二关键字排序，依次处理每个信息。处理信息 $i$ 时，我们需要找出 $x_i$ 的祖先中最近的节点 $u$，使得存在一个信息 $j$ 经过节点 $u$ 且 $t_i+d_{x_i}<t_j+d_{x_j}+2d_u-2d_{y_j}$。

对每个节点 $u$ 维护经过它的所有信息 $j$ 中，$t_j+d_{x_j}+2d_u-2d_{y_j}$ 的最大值。再用树剖和线段树维护上述信息的区间最大值，这样我们寻找 $y_i$ 时只需要顺着树剖往上跳，每次再进行线段树二分即可。找到 $y_i$ 后我们需要更新线段树，这可以打标记实现。

于是我们完整解决了问题。若令 $n$ 与 $m$ 同级，时间复杂度 $O(n\log^2n)$。使用其他的树上数据结构可以做到 $O(n\log n)$。
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
const int maxn=2e5+5;
int n,m,x[maxn],t[maxn];
vector<int> g[maxn];
int fa[maxn],dep[maxn],sz[maxn],son[maxn];
void dfs1(int u){
	dep[u]=dep[fa[u]]+1;
	sz[u]=1;
	for(int v:g[u]){
		dfs1(v);
		sz[u]+=sz[v];
		if(sz[v]>sz[son[u]]) son[u]=v;
	}
}
int pos[maxn],top[maxn];
vector<int> f;
void dfs2(int u){
	pos[u]=f.size();
	f.push_back(u);
	top[u]=son[fa[u]]==u?top[fa[u]]:u;
	if(son[u]) dfs2(son[u]);
	for(int v:g[u]) if(v!=son[u]) dfs2(v);
}
const int inf=2e9;
struct node{
	int l,r;
	node* ch[2];
	int mx,tag=-inf;
	void pushup(){
		mx=max(ch[0]->mx,ch[1]->mx);
	}
	node(int l,int r):l(l),r(r),mx(l?-inf:inf){
		if(l==r) return;
		int mid=l+(r-l)/2;
		ch[0]=new node(l,mid);
		ch[1]=new node(mid+1,r);
	}
	void pushtag(int k){
		mx=max(mx,k+dep[f[r]]*2);
		tag=max(tag,k);
	}
	void pushdown(){
		ch[0]->pushtag(tag);
		ch[1]->pushtag(tag);
		tag=-inf;
	}
	void modify(int ql,int qr,int k){
		if(ql>r||qr<l) return;
		if(ql<=l&&qr>=r){
			pushtag(k);
			return;
		}
		pushdown();
		ch[0]->modify(ql,qr,k);
		ch[1]->modify(ql,qr,k);
		pushup();
	}
	void get(int ql,int qr,vector<node*>& vec){
		if(ql>r||qr<l) return;
		if(ql<=l&&qr>=r){
			vec.push_back(this);
			return;
		}
		pushdown();
		ch[0]->get(ql,qr,vec);
		ch[1]->get(ql,qr,vec);
	}
	int query(int x){
		if(l==r) return r;
		pushdown();
		return ch[ch[1]->mx>x]->query(x);
	}
}*rt;
void modify(int x,int y,int k){
	while(top[x]!=top[y]){
		rt->modify(pos[top[x]],pos[x],k);
		x=fa[top[x]];
	}
	rt->modify(pos[y],pos[x],k);
}
int query(int x,int k){
	while(1){
		vector<node*> vec;
		rt->get(pos[top[x]],pos[x],vec);
		reverse(vec.begin(),vec.end());
		for(node* u:vec)
			if(u->mx>k) return f[u->query(k)];
		x=fa[top[x]];
	}
}
int ord[maxn],ans[maxn];
int main(){
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	n=read();
	m=read();
	for(int i=2;i<=n+1;i++)
		g[fa[i]=read()+1].push_back(i);
	dfs1(1);
	dfs2(1);
	for(int i=1;i<=m;i++){
		x[i]=read()+1;
		t[i]=read();
		ord[i]=i;
	}
	sort(ord+1,ord+m+1,[](int a,int b){
		if(t[a]+dep[x[a]]!=t[b]+dep[x[b]])
			return t[a]+dep[x[a]]<t[b]+dep[x[b]];
		return x[a]<x[b];
	});
	rt=new node(0,n);
	for(int i=1;i<=m;i++){
		int u=ord[i],y=query(x[u],t[u]+dep[x[u]]);
		ans[u]=t[u]+dep[x[u]]*2-dep[y]*2;
		modify(x[u],y,t[u]+dep[x[u]]-dep[y]*2);
	}
	for(int i=1;i<=m;i++) printf("%d ",ans[i]);
#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

## 作者：houzhiyuan (赞：1)

为什么没有 LCT。

先按照 $dep+T$ 排序，这样后面的不会影响前面的。

暴力挺简单的，就相当于记录每个节点等待时间的最大值，然后一个点暴力向上跳，一直跳到第一个等待时间比自己大的就停下，然后回去。

发现从上面下来的这个过程会形成一条下面大，上面小的链，在这个链上只要跳过最下面一个就可以直接跳到链顶。

但是这个链会修改啊，然后发现这个可以直接 LCT，相当于一个点打通到根的路径，但是遇到比自己大的就停下。

我写的是双 $\log$，不过可以轻松优化，懒。

比树剖好写得多。

```cpp
#include <bits/stdc++.h>
#define V vector
#define Vi vector<int>
#define sz(a) ((int)a.size())
#define fi first
#define se second
#define Int pair<int, int>
#define Inf ((int)1e9)
#define pb push_back
#define ins insert
#define For(i, x, y) for (auto i = (x); i <= (y); i++)
#define Rep(i, x, y) for (auto i = (x); i >= (y); i--)
#define seg int p, int l, int r
#define lid p << 1, l, mid
#define rid p << 1 | 1, mid + 1, r
#define mid ((l + r) / 2)
#define IO(x) freopen(#x ".in", "r", stdin), freopen(#x ".out", "w", stdout);
using namespace std;
struct hzy {
  int x, T, id;
};
struct Link_Cut_Tree {
  static const int N = 2e5 + 5;
  int isrt(int x) { return e[fa[x]][0] != x && e[fa[x]][1] != x; }
  void up(int x) {
    int y = fa[x], k = e[y][1] == x;
    fa[x] = fa[y];
    if (!isrt(y)) e[fa[y]][e[fa[y]][1] == y] = x;
    e[y][k] = e[x][k ^ 1];
    if (e[x][k ^ 1]) fa[e[x][k ^ 1]] = y;
    e[x][k ^ 1] = y, fa[y] = x;
  }
  void splay(int x) {
    for (int y; !isrt(x); up(x))
      if (!isrt(y = fa[x])) up((e[fa[y]][0] == y) == (e[y][0] == x) ? y : x);
  }
  int getval(int x) {
    splay(x);
    int y = x;
    while (e[y][0]) y = e[y][0];
    return v[y] + dep[x];
  }
  int getrt(int x) {
    splay(x);
    int y = x;
    while (e[y][0]) y = e[y][0];
    return y;
  }
  int ask(int x, int T) {
    int y = 0;
    for (; x && T - dep[x] >= getval(x); x = fa[y = x]) {
      if (e[x][1]) {
        int t = getrt(x), g = e[x][1];
        e[x][1] = y;
        g = getrt(g);
        v[g] = v[t];
      }
      e[x][1] = y;
    }
    if (y) {
      int t = getrt(y);
      v[t] = T - dep[t] + 2 - dep[t];
    }
    return x;
  }
  int la[N], e[N][2], fa[N], v[N], dep[N];
};
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int n, m;
  cin >> n >> m;
  n++;
  V<Vi> e(n + 5);
  Vi fa(n + 5);
  for (int i = 2; i <= n; i++) cin >> fa[i], fa[i]++, e[fa[i]].pb(i);
  Vi dep(n + 5);
  auto dfs = [&](auto lf, int x) -> void {
    for (int y : e[x]) {
      dep[y] = dep[x] + 1;
      lf(lf, y);
    }
  };
  dfs(dfs, 1);
  V<hzy> b(m + 5);
  for (int i = 1; i <= m; i++) {
    cin >> b[i].x >> b[i].T;
    b[i].x++;
    b[i].id = i;
  }
  sort(&b[1], &b[m + 1], [&](hzy x, hzy y) {
    if (dep[x.x] + x.T != dep[y.x] + y.T)
      return dep[x.x] + x.T < dep[y.x] + y.T;
    return x.x < y.x;
  });
  Link_Cut_Tree lct;
  for (int i = 2; i <= n; i++) lct.fa[i] = fa[i];
  for (int i = 1; i <= n; i++) lct.dep[i] = dep[i], lct.v[i] = -Inf;
  lct.v[1] = Inf;
  Vi las(n + 5), Ans(m + 5);
  for (int i = 1; i <= m; i++) {
    int t = lct.ask(b[i].x, b[i].T + dep[b[i].x]);
    Ans[b[i].id] = b[i].T + (dep[b[i].x] - dep[t]) * 2;
  }
  For(i, 1, m) cout << Ans[i] << '\n';
}
```

---

