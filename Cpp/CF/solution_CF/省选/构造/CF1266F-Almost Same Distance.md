# Almost Same Distance

## 题目描述

给出一颗$n$个点的树($2\leq n\leq 5\times 10^5$)，对于$k\in[1,n]$，分别找出一个最大的点集，使得点集内任意两点间距离为$k$或$k+1$。

## 样例 #1

### 输入

```
5
1 2
1 3
1 4
4 5
```

### 输出

```
4 3 2 1 1
```

## 样例 #2

### 输入

```
6
1 2
1 3
1 4
4 5
4 6
```

### 输出

```
4 4 2 1 1 1
```

# 题解

## 作者：zhoukangyang (赞：13)

[更好的阅读体验](https://www.cnblogs.com/zkyJuruo/p/14254120.html)

看到其他题解里面全是什么 `bfs` 序上线段树啊，什么根号的奇怪东西啊，蒟蒻用一个非常好写的 $O(n)$ 做法（这里实现的时候用了 `vector`，所以比较慢），写篇题解来造福社会

目前在 cf 上是最短解

-----------
如果 $k = 1$，答案是 $\max(deg_i + 1)$

考虑有 $3$ 个点的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/mmlyhcfh.png)

通过放缩法可以证明（证明比较简单而繁琐略去）。考虑在这种情况下的链长(图中的 $a, b, c$)：
1. $k$ 为奇数：有一个中心结点，旁边的链最多只有一个长为 $\frac{k-1}{2}$ 的，其他都是 $\frac{k + 1}{2}$。
2. $k$ 为偶数：有一个中心结点，旁边的都是长为 $\frac{k}{2}$ 的链。

但是这样会发现在样例 $2$ 挂掉了。漏掉了下面的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/o2ty4vhp.png)

因此有了第 $3$ 种情况 ：在 $k$ 为偶数的时候，有两个中心结点，旁边链长要求为 $\frac{k}{2}$。

在这 $3$ 种情况下，我们发现一定满足 $ans_x \ge ans_{x + 2}$。

对于前两个情况，每一个结点我们记录以他为根时的子树深度，然后把这个深度进行排序。$k$ 为偶数时第 $i$ 大数 $t$ 的则表示  $ans_{2t} \ge i$ 。奇数稍微麻烦点，第 $i$ 大数 $t$ 的则表示  $ans_{2t-1} \ge i$，如果不和排在前面的数相同，那么我们发现长度为 $ans_{2t+1} \ge i$（用这条链和之前面的几条链放在一起，就是长度为 $t$ 和一堆 $t + 1$）。这里都很显然。

第 $3$ 种情况，显然可以把所有相邻的两个位置 $A$, $B$ 的子树深度数组给合并在一起，然后再按照第一种情况做就行了，可惜是 $n^2$ 的。

考虑从后到前，对于这个子树深度数组扫描线，扫到 $k$ 时更改每一个数的时候判一下和相邻结点的点的和 $sum - 2$ （$sum$ 会算到 $B$ 做 $A$ 子树和 $A$ 做 $B$ 子树的贡献，因此 $sum$ 要减 $2$）是否可以更新 $ans_{k}$。

这个可以套路地看作是计算父亲结点和子树结点的最大值，额外记录一下子树 $sum$ 的最大值 $mxs$，在修改一个结点的时候更新父亲结点的 $mxs$，同时用 $max(sum_{fa}, mxs)$ 来更新答案。

具体实现时，第 $1$ 和第 $2$ 种情况也可以把排序换成扫描线做到 $O(n)$

其余细节见代码。

```cpp
#include<bits/stdc++.h>
#define L(i, j, k) for(int i = j, i##E = k; i <= i##E; i++)
#define R(i, j, k) for(int i = j, i##E = k; i >= i##E; i--)
using namespace std;
const int N = 5e5 + 7;
void Max(int &x, int y) { if(x < y) x = y;  }
int n, deg[N], Fa[N], f1[N], f2[N], sum[N], mx1[N], mx2[N], up[N], mxs[N], las, u, v;
vector<int> G[N], e[N];
void dfs1(int x) {
	Max(f1[0], deg[x] + 1), mxs[x] = -1e9;
	for(int v : e[x]) if(v ^ Fa[x]) {
		Fa[v] = x, dfs1(v);
		if(mx1[v] + 1 > mx1[x]) mx2[x] = mx1[x], mx1[x] = mx1[v] + 1; else Max(mx2[x], mx1[v] + 1);
	}
}
void dfs2(int x) {
	if(x ^ 1) G[up[x]].push_back(x);
	for(int v : e[x]) if(v ^ Fa[x]) G[mx1[v] + 1].push_back(x);
	for(int v : e[x]) if(v ^ Fa[x]) up[v] = max(up[x], mx1[v] + 1 == mx1[x] ? mx2[x] : mx1[x]) + 1, dfs2(v);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n, f1[n] = f2[n] = 1;
	L(i, 1, n - 1)  cin >> u >> v, deg[u] ++, deg[v] ++, e[u].push_back(v), e[v].push_back(u);
	dfs1(1), dfs2(1);
	R(i, n, 1) {
		las = 0;
		for(int t : G[i]) {
			sum[t] ++, Max(mxs[Fa[t]], sum[t]);
			Max(f2[i], sum[t] + mxs[t] - 2), Max(f2[i], sum[t] + sum[Fa[t]] - 2); // case 3
			Max(f2[i], sum[t]); // case 1
			Max(f1[i - 1], sum[t]); // case 2
			if(las != t) Max(f1[i], sum[t]); las = t; // case 2
		}
	}
	R(i, n, 1) Max(f1[i - 1], f1[i]), Max(f2[i - 1], f2[i]);
	L(i, 1, n) cout << (i % 2 ? f1[i / 2] : f2[i / 2]) << " ";
	cout << endl;
	return 0;
} 
```

**祝大家学习愉快！**

---

## 作者：Leasier (赞：2)

前置芝士：[树形 dp](https://oi-wiki.org/dp/tree/)、[bfs 序](https://oi-wiki.org/graph/bfs/#bfs-%E5%BA%8F%E5%88%97)、[线段树](https://oi-wiki.org/ds/seg/)

当 $k = 1$，显然可以对每个节点取它自己和它相邻的点，即 $ans_1 = \displaystyle\max_{i = 1}^n d_i + 1$。

当 $k$ 为偶数，有如下两种情况：

- A. 一个点 $u$，上面挂了若干条长为 $\frac{k}{2}$ 或 $\frac{k}{2} + 1$ 的链（所求点集不包括 $u$ 且长为 $\frac{k}{2} + 1$ 的链不超过一条）。
- B. 两个点 $u, v$，$u, v$ 上面分别挂了若干条长为 $\frac{k}{2}$ 的链（所求点集不包括 $u$）。

当 $k$ 为 $> 1$ 的奇数，有如下一种情况：

- C. 一个点 $u$，上面挂了若干条长为 $\frac{k + 1}{2}$ 或 $\frac{k - 1}{2}$ 的链（所求点集不包括 $u$ 且长为 $\frac{k - 1}{2}$ 的链不超过一条）。

由上述情况的表述我们不难发现 $ans_i \geq ans_{i + 2}$，所以考虑处理长度**至少**为 $k$ 的链。

对于 A、C，注意到我们只需要固定一个节点 $u$，于是考虑对每个 $u$ 抓出所有 $u \to v$ 以及**当 $u$ 为根时**从 $u$ 经过 $v$ 向下延伸的链的最大长度（容易分为子树内和子树外两次树形 dp 预处理），将所有这样的极长链抓出来从大到小排序，讨论到链 $i$ 时表示允许使用长度 $\geq len_i$ 的链，对于情况 A，即为这样的链的条数；对于情况 C，当 $i$ 是唯一的长为 $\frac{k - 1}{2}$ 的链，我们可以双指针维护长 $> len_i$ 的链的数量，再加上这条链自己就行，当 $i$ 是长为 $\frac{k + 1}{2}$ 的链，答案即为长度 $\geq len_i$ 的链的条数。

对于 B，考虑固定其中一个端点求另一个端点的最优值。仿照上述做法，我们把**从每个端点出发的所有极长链**都抓出来从大到小排序并依次扫每一条链。下文中设当前链 $i$ 的端点为 $u$。

由于实现时肯定是在有根树上讨论该问题，我们不妨现在就分成在 $u$ 的儿子中选一个点 $v$ 和选择 $fa_u$ 两种情况。

1. 在 $u$ 的儿子中选一个 $v$

我们容易知道选每个儿子时可以对它有贡献的链的数量，可以通过双指针求出长度 $\geq len_i$ 的链中端点也为 $u$ 者的数量。

但这里我们需要 $- 1$，因为从 $v$ 出发经过 $u$ 的链也会对 $v$ 产生贡献（要不然 $u$ 就没有实际贡献了，矛盾）。

而 $u$ 本身的贡献为当前链在以 $u$ 为根时的排名 $- 1$，需要 $- 1$ 是因为从 $u$ 出发经过 $v$ 的链也会对 $u$ 产生贡献（要不然 $u$ 就没有实际贡献了，这不合法）。

注意到我们需要求一个点的所有儿子的贡献的 $\max$，还要支持单点加的操作，于是我们求出原树的 bfs 序并维护一棵支持单点加、区间 $\max$ 的线段树即可。

2. 选择 $fa_u$

类似地，我们也容易知道选 $fa_u$ 时可以对它有贡献的链的数量。

但这里我们也需要 $- 1$，因为从 $fa_u$ 出发经过 $u$ 的链也会对 $fa_u$ 产生贡献（要不然 $u$ 就没有实际贡献了，矛盾）。

而 $u$ 本身的贡献也为当前链在以 $u$ 为根时的排名 $- 1$，需要 $- 1$ 是因为从 $u$ 出发经过 $fa_u$ 的链也会对 $u$ 产生贡献（要不然 $fa_u$ 就没有实际贡献了，这不合法）。

最后做一次后缀 max 即可。时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdio>

using namespace std;

typedef struct {
	int nxt;
	int end;
} Edge;

typedef struct {
	int pos;
	int rank;
	int val;
} Node1;

typedef struct {
	int l;
	int r;
	int max;
} Node2;

int cnt = 0, pos = 0;
int l[500007], deg[500007], head[500007], fa[500007], bfn[500007], r[500007], down[500007], sec_down[500007], up[500007], each[500007], ans[1000007];
bool vis[500007];
Edge edge[1000007];
Node1 a[1000007];
Node2 tree[2000007];
queue<int> q;
vector<pair<int, int> > v[500007];

bool operator <(const Node1 a, const Node1 b){
	return a.val > b.val;
}

inline void init(int n){
	for (register int i = 1; i <= n; i++){
		l[i] = 0x7fffffff;
	}
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs1(int u, int father){
	fa[u] = father;
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != father){
			dfs1(x, u);
			if (down[u] < down[x] + 1){
				sec_down[u] = down[u];
				down[u] = down[x] + 1;
			} else {
				sec_down[u] = max(sec_down[u], down[x] + 1);
			}
		}
	}
}

inline void bfs(int start){
	int id = 0;
	vis[start] = true;
	q.push(start);
	while (!q.empty()){
		int cur = q.front();
		q.pop();
		bfn[cur] = ++id;
		if (fa[cur] != 0){
			l[fa[cur]] = min(l[fa[cur]], id);
			r[fa[cur]] = max(r[fa[cur]], id);
		}
		for (register int i = head[cur]; i != 0; i = edge[i].nxt){
			int x = edge[i].end;
			if (x != fa[cur]){
				vis[x] = true;
				q.push(x);
			}
		}
	}
}

void dfs2(int u){
	if (fa[u] != 0){
		up[u] = up[fa[u]] + 1;
		if (down[fa[u]] == down[u] + 1){
			up[u] = max(up[u], sec_down[fa[u]] + 1);
		} else {
			up[u] = max(up[u], down[fa[u]] + 1);
		}
	}
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != fa[u]) dfs2(x);
	}
}

void dfs3(int u){
	if (fa[u] != 0) v[u].push_back(make_pair(up[u], fa[u]));
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != fa[u]) v[u].push_back(make_pair(down[x] + 1, x));
	}
	sort(v[u].begin(), v[u].end(), greater<pair<int, int> >());
	for (register int i = 0, j = 0; i < deg[u]; i++){
		int t1 = v[u][i].first * 2, t2 = v[u][i].first * 2 - 1, t3 = v[u][i].first * 2 + 1;
		pos++;
		a[pos].pos = u;
		a[pos].rank = i + 1;
		a[pos].val = v[u][i].first - 1;
		ans[t1] = max(ans[t1], i + 1);
		ans[t2] = max(ans[t2], i + 1);
		while (j < deg[u] && v[u][j].first > v[u][i].first) j++;
		ans[t3] = max(ans[t3], j + 1);
	}
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != fa[u]) dfs3(x);
	}
}

void build(int x, int l, int r){
	tree[x].l = l;
	tree[x].r = r;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
}

inline void update(int x){
	tree[x].max = max(tree[x * 2].max, tree[x * 2 + 1].max);
}

void add(int x, int pos, int val){
	if (tree[x].l == tree[x].r){
		each[pos] += val;
		tree[x].max += val;
		return;
	}
	if (pos <= ((tree[x].l + tree[x].r) >> 1)){
		add(x * 2, pos, val);
	} else {
		add(x * 2 + 1, pos, val);
	}
	update(x);
}

int get_max(int x, int l, int r){
	if (l <= tree[x].l && tree[x].r <= r) return tree[x].max;
	int mid = (tree[x].l + tree[x].r) >> 1, ans = 0;
	if (l <= mid) ans = get_max(x * 2, l, r);
	if (r > mid) ans = max(ans, get_max(x * 2 + 1, l, r));
	return ans;
}

int main(){
	int n;
	scanf("%d", &n);
	init(n);
	for (register int i = 1; i < n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		deg[u]++;
		deg[v]++;
		add_edge(u, v);
		add_edge(v, u);
	}
	for (register int i = 1; i <= n; i++){
		ans[1] = max(ans[1], deg[i] + 1);
	}
	for (register int i = 2; i <= n; i++){
		ans[i] = 1;
	}
	dfs1(1, 0);
	bfs(1);
	dfs2(1);
	dfs3(1);
	sort(a + 1, a + pos + 1);
	build(1, 1, n);
	for (register int i = 1, j = 1; i <= pos; i++){
		int x, t = (a[i].val + 1) * 2;
		while (j <= pos && a[j].val >= a[i].val) add(1, bfn[a[j++].pos], 1);
		x = get_max(1, l[a[i].pos], r[a[i].pos]) - 1;
		if (fa[a[i].pos] != 0) x = max(x, each[bfn[fa[a[i].pos]]] - 1);
		ans[t] = max(ans[t], x + (a[i].rank - 1));
	}
	for (register int i = n * 2 - 4; i >= 1; i--){
		ans[i] = max(ans[i], ans[i + 2]);
	}
	for (register int i = 1; i <= n; i++){
		printf("%d ", ans[i]);
	}
	return 0;
}
```

---

## 作者：csyakuoi (赞：1)

图片可在[博客](https://www.cnblogs.com/2005lz/p/13121667.html)上查看。

来一个O(nlogn)做法，跑得挺快。

假设点集S包含点X，Y，Z，红色链长度为a，黄色链长度为b，绿色链长度为c。

如果|a-b|>1，那么有|dis(X,Z)-dis(Y,Z)|=|(a+c)-(b+c)|=|a-b|>1，不符合题目要求。

所以a=b或|a-b|=1。所以存在一个点A，到S中每一个点的距离都为p或p+1(0<2p<n)。

接着发现一定是一下两种情况之一（证明留给读者自行思考）：

情况1：S中任两点到点A的链没有公共边。

情况2：S中任意一点P满足min(dis(P,A),dis(P,A'))=p（A'为一个与A相邻的点）。

于是，S中的点便是由A点或者A点及A'点伸出来的若干条“长度相近”链的另一端点组成（如图）。

其中“长度相近”指长度均为p或p+1，且长度为p的链只有一条或长度为p+1的链只有一条。

预处理出每一个点连出所有边引出链的最大长度，对于一个点P，设其引出第k长的链长度为len(p,k)，则$ans_{len(p,k)} \geq k$。

又因为$ans_x \geq ans_{x+2}$，所以可以先对于每个k，求出最大的x使$ans_x \geq k$，再做一边后缀最大值。

先枚举其中一个中心点，再枚举其引出的一条边，设k为这条边引出链的最大长度，一共可以引出d条长度为k的链。

那么执行ans[k]=max(ans[k],d)。对每个点，将其引出链按最大长度排序即可求得d和k。

这样一个中心点的情况就搞定了。

对于点i，设集合S_i中有deg_i个元素，分别为i引出deg_i条边所引出链长度的最大值。

枚举其中一个中心点P，设另一个为Q，则P，Q相邻。我们只需要对于每一个$S_{P,j}(0 \leq j<deg_P)$，找到点Q，使集合S_P，S_Q中大于$S_{P,j}$的数最多。因为每个数相当于一条链的长度。把问题离线下来（按照$S_{P,j}$从大到小排序），用bfs序把与P相邻的点转化为一段区间以及fa_P，然后写一个支持单点加，区间最大值的线段树即可。具体见代码吧。
```cpp
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n,cnt=-1,temp,qcnt=0;
int deg[500000],l1[500000],l2[500000];
int fir[500000],to[1000000],nxt[1000000];
int fa[500000],ans[500000],f[500000];
int id[500000],mx[2000000],o[500000];
vector<int> len[500000];
struct query{
	int x,val,o;
}qu[1000000];
inline bool comp(query q1,query q2)
{
	return q1.val>q2.val;
}
inline void Add(int a,int b,int c)
{
	qu[qcnt].x=a;
	qu[qcnt].val=c;
	qu[qcnt++].o=b;
	return;
}
inline void add(int a,int b)
{
	to[++cnt]=b;
	nxt[cnt]=fir[a];
	fir[a]=cnt;
	deg[b]++;
	return;
}

void dfs1(int i,int f)
{
	fa[i]=f;
	for(int j=fir[i];j!=-1;j=nxt[j]){
		if(to[j]==f)
			continue;
		dfs1(to[j],i);
		l1[i]=max(l1[i],l1[to[j]]);
	}
	l1[i]++;
	return;
}
void dfs2(int i,int l)
{
	l2[i]=l;
	int mx1=0,mx2=0;
	for(int j=fir[i];j!=-1;j=nxt[j]){
		temp=to[j];
		if(temp==fa[i])
			continue;
		if(mx1<l1[temp]){
			mx2=mx1; mx1=l1[temp];
		}
		else if(mx2<l1[temp])
			mx2=l1[temp];
	}
	for(int j=fir[i];j!=-1;j=nxt[j]){
		temp=to[j];
		if(temp==fa[i])
			continue;
		if(mx1==l1[temp])
			dfs2(temp,max(mx2,l2[i])+1);
		else dfs2(temp,max(mx1,l2[i])+1);
	}
	return;
}

int t1,t2;
void upd(int i,int l,int r)
{
	if(l==r){
		mx[i]++;
		return;
	}
	int mid=(l+r)>>1;
	if(t1<=mid) upd(i<<1,l,mid);
	else upd(i<<1|1,mid+1,r);
	mx[i]=max(mx[i<<1],mx[i<<1|1]);
	return;
}
inline void update(int x)
{
	t1=x; upd(1,0,n-1); f[x]++;
	return;
}
int qry(int i,int l,int r)
{
	if(t1<=l&&r<=t2)
		return mx[i];
	int mid=(l+r)>>1,res=0;
	if(t1<=mid) res=qry(i<<1,l,mid);
	if(mid<t2) res=max(res,qry(i<<1|1,mid+1,r));
	return res;
}
inline int querymax(int x,int y)
{
	t1=x; t2=y;
	return qry(1,0,n-1);
}

void bfs(void)
{
	cnt=0;
	id[0]=cnt++;
	queue<int> q;
	q.push(0);
	while(q.size()>0){
		int i=q.front();
		q.pop();
		o[i]=cnt-1;
		for(int j=fir[i];j!=-1;j=nxt[j])
			if(to[j]!=fa[i]){
				id[to[j]]=cnt++;
				q.push(to[j]);
			}
	}
	return;
}
void solve(void)
{
	for(int i=2;i<n;i++)
		ans[i]=1;
	for(int i=0;i<n;i++){
		int s=deg[i];
		for(int d=1;d<=s;d++){
			temp=len[i][s-d]*2;
			if(temp<n) ans[temp]=max(ans[temp],d);
			if(temp<=n) ans[temp-1]=max(ans[temp-1],d);
			if(temp+1<n&&d>1&&len[i][s-d+1]>len[i][s-d])
				ans[temp+1]=max(ans[temp+1],d);
		}
	}
	
	for(int i=0;i<n;i++)
		for(int d=1;d<=deg[i];d++)
			Add(i,d,len[i][deg[i]-d]);
	sort(qu,qu+qcnt,comp);
	int pos=0;
	for(int i=0;i<qcnt;i++){
		while(pos<qcnt&&qu[pos].val>=qu[i].val)
			update(id[qu[pos++].x]);
		int X=qu[i].x,D=2*qu[i].val;
		temp=querymax(o[X]+1,o[X]+deg[X]-1);
		if(X!=0) temp=max(temp,f[id[fa[X]]]);
		ans[D]=max(ans[D],temp+qu[i].o-2);
	}
	return;
}

int main(void)
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		fir[i]=-1;
	int a,b;
	for(int i=1;i<n;i++){
		scanf("%d%d",&a,&b);
		add(a-1,b-1); add(b-1,a-1);
	}
	dfs1(0,-1); dfs2(0,0); bfs();
	for(int i=1;i<n;i++){
		len[fa[i]].push_back(l1[i]);
		len[i].push_back(l2[i]);
	}
	for(int i=0;i<n;i++){
		sort(len[i].begin(),len[i].end());
		ans[1]=max(ans[1],deg[i]+1);
	}
	solve();
	for(int i=n-3;i>0;i--)
		ans[i]=max(ans[i],ans[i+2]);
	for(int i=1;i<n;i++)
		printf("%d ",ans[i]);
	printf("1\n");
	return 0;
}
```

---

## 作者：baka24 (赞：0)

按照 $k$ 的奇偶性分类讨论一下，答案有以下几种构成方式：

当 $k$ 是奇数时：

![](https://cdn.luogu.com.cn/upload/image_hosting/4fxyspyi.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/phebg79o.png)

如图所示，答案只有可能是一个点周围有一些长度为 $\frac{k-1}{2}$ 链，至多再有一条长度为 $\frac{k+1}{2}$ 的链。

当 $k$ 为偶数时：

![](https://cdn.luogu.com.cn/upload/image_hosting/l9v3xgbh.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/0z7wv1e1.png)

如图，$k$ 为偶数时会有一条边的两个点上有一些长度相等的链的情况。

关于只有这几种情况的证明：考虑一条长度为 $k$ 或 $k+1$ 的链，再加入一个点只能在中点上加，之后就一定会变成如上情况。

之后便考虑如何统计答案。

首先可以发现对于所有 case，把 $x$ 的长度减一后仍合法，也就是说有 $ans_k\ge ans_{k+2}$，只统计部分答案最后再后缀和即可。

具体的，考虑每个点为中心的贡献，最后再加上两个相邻点对偶数的贡献。

对于一个点作中心的情况，先预处理出这个点的每个子树（包括父亲）距离这个点的最远距离，这便是可以取到的最长链。

之后对于长度为 $x$ 的链，它的基础贡献便是长度大于等于 $x$ 的个数，贡献到 $2x$ 和 $2x-1$，如果存在链长 $x-1$，便对于 $2x-1$ 的贡献再加一。

之后考虑两个相邻点。

考虑统计一个点和其所有儿子之间的答案，对于长度 $x$，需要统计二者有多少条链长度大于等于 $x$。同样只需要考虑存在链的长度。

对于每个儿子的长度，提前建出父亲所有链的树状数组，区间查询即可。

对于父亲的每个长度，扫出儿子所有链的长度，以及对应的点上大于此长度链的个数，排序后双指针统计即可。

然后就没了，排序可以桶排，可惜树状数组暂时没想到怎么优化，求评论区大佬指教qwq。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int> 
#define fr first
#define sc second 
#define mk make_pair
#define pb push_back
#define inx(u) int I=h[u],v=edge[I].v;I;I=edge[I].nx,v=edge[I].v
int read(){int x=0,f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}x=c-'0';c=getchar();while(c<='9'&&c>='0'){x*=10;x+=c-'0';c=getchar();}return x*f;}
const int MAXN=500010;
struct Edge{int v,nx;}edge[MAXN<<1];int h[MAXN],CNT=1;void add_side(int u,int v){edge[++CNT]={v,h[u]};h[u]=CNT;edge[++CNT]={u,h[v]};h[v]=CNT;}
int n,m,ans,f[MAXN],d[MAXN],g[MAXN],son[MAXN],as[MAXN];
vector<pii>st[MAXN];
void dfs(int u,int lst){
    f[u]=g[u]=0;
    for(inx(u))if(v!=lst){
        dfs(v,u);
        if(f[v]+1>=f[u]){
            g[u]=f[u],f[u]=f[v]+1,son[u]=v;
        }
        else if(f[v]+1>g[u])g[u]=f[v]+1;
    }
}
void dfs2(int u,int lst,int mx){
    for(inx(u))if(v!=lst)st[u].pb(mk(f[v]+1,v));
    if(mx)st[u].pb(mk(mx,lst));
    sort(st[u].begin(),st[u].end());
    for(inx(u))if(v!=lst)dfs2(v,u,v==son[u]?max(g[u],mx)+1:max(f[u],mx)+1);
}
struct treearray{
    int C[MAXN];
    int lb(int x){return x&(-x);}
    void upd(int x,int y){for(int i=x;i<=n;i+=lb(i))C[i]+=y;}
    int qry(int x){int res=0;for(int i=x;i>=1;i-=lb(i))res+=C[i];return res;}
    int qry(int l,int r){return qry(r)-qry(l-1);}
}T;
pii at[MAXN];
int cnt;
void sol(int u,int lst){
    for(auto o:st[u])T.upd(o.fr,1);
    cnt=0;
    for(inx(u))if(v!=lst){
        int tmp=st[v].size();
        for(auto o:st[v]){
            as[2*o.fr]=max(as[2*o.fr],T.qry(o.fr,n)+tmp-2);
            if(o.sc!=u)at[++cnt]=mk(o.fr,tmp);
            tmp--;
        }
    }
    sort(at+1,at+cnt+1);
    int i=cnt,tp=0,tmp=0;
    reverse(st[u].begin(),st[u].end());
    for(auto o:st[u]){
        tmp++;
        while(i&&at[i].fr>=o.fr)tp=max(tp,at[i].sc),i--;
        as[o.fr*2]=max(as[o.fr*2],tp+tmp-2);
    }
    reverse(st[u].begin(),st[u].end());
    for(auto o:st[u])T.upd(o.fr,-1);
}
void dfs3(int u,int lst){
    int tmp=st[u].size(),ls=0;
    for(auto o:st[u]){
        int x=o.fr,v=o.sc;
        if(ls==x-1)as[x+x-1]=max(as[x+x-1],tmp+1);
        else as[x+x-1]=max(as[x+x-1],tmp);
        if(ls!=x)as[ls+ls+1]=max(as[ls+ls+1],tmp+1);
        as[x+x]=max(as[x+x],tmp);
        tmp--,ls=x;
    }
    sol(u,lst);
    for(inx(u))if(v!=lst)dfs3(v,u);
}
void slv(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add_side(u,v);
        d[u]++,d[v]++;
    }
    dfs(1,1);
    for(int i=1;i<=n;i++)if(i<=g[1]+f[1])as[i]=2;else as[i]=1;
    dfs2(1,1,0),dfs3(1,1);
    for(int i=n;i>=1;i--)as[i]=max(as[i],as[i+2]);
    for(int i=1;i<=n;i++)printf("%d ",as[i]);
}
signed main(){
 	freopen("1.in","r",stdin);freopen("1.out","w",stdout);  
	slv();
    cerr<<clock()*1.0/CLOCKS_PER_SEC<<"s\n";
    return 0;
}
```

---

## 作者：SegTree (赞：0)

$O(n\sqrt n)$ 的唐龙做法，看题解区没有于是来写一篇。

首先你观察一下，你发现可能情况如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/3e8h3ue5.png)

前两种情况枚举中间的那个点维护一下每个子节点最多能延申的长度打个 tag 取后缀 $\min$ 即可，容易在线性时间内计算，但是第三种暴力就是度数平方的，假掉了。

记 $mx_u$ 为以 $u$ 为根的子树内 $u$ 最多能延申多少，则  $mx$ 的本质不同种数是根号的（证：它们的总和 $\le n$，大于根号的种数不超过根号，所以 $mx$ 的本质不同种数为 $O(\sqrt n)$）。

于是就可以类似第一种和第二种扫一遍，复杂度做到 $O(n\sqrt n)$，空间线性。

---

## 作者：约瑟夫用脑玩 (赞：0)

\*2900

这道题在第一步上会分出两种解法：你看没看出 $ans_x\ge ans_{x+2}$。

- 如果你看出来了，~~而且你和 zky 一样强~~，你可以直接对所有可能距离为 $d$ 的集合进行考虑。

  由于 $\ge d+2$ 的可以直接继承，只用考虑距离恰为 $d$ 的，从而得到正确的复杂度。
- 如果你没有看出来，你需要对每种 $S_{x,y}$ 集合对距离 $x/y$ 的贡献进行考虑，这里 $S_{x,y}$ 表示点对距离含 $x,y$ 的集合。

第一种解法左转隔壁看 zky 的，代码写得很好，我是来讲第二种平民解法的：

------------

如果 $S_{x,y}$ 中距离 $x,y$ 都存在，由于 $|x-y|=1$，其中必定存在奇数。

先特殊考虑只有偶数的情况，集合形如 $S_{2d}$。

从集合中取出两个点 $a,b$，令它们的路径中点为 $c$，那么对于这个集合的其他所有点都得是从 $c$ 接上去的，否则到 $a,b$ 的距离不可能都等于 $2d$。

那么我们枚举中点 $c$，贪心的使每个子树对集合贡献尽可能多，设对 $ans_{2d},ans_{2d-1}$ 的贡献为 $T_d$，则 $T_d=\sum_{p\in son_c}[mxd_p\ge d]$，其中 $mxd_p$ 为从 $p$ 延伸到子树内的最长单链的长度。

考虑含奇数长度的集合 $S_{2d+1,?}$，还是取两个点 $x,y$，则中点为一条边 $e_{u,v}$。

首先集合内的其他点必须从 $u,v$ 接到路径上，分两种情况考虑：

- 只从 $u,v$ 中的一端接入，接入的长度 $k\in\{d,d+1\}$ **且均相等**，若接入长度为 $d$ 则对 $ans_{2d}$ 产生贡献，若接入长度为 $d+1$ 则对 $ans_{2d+1}$ 产生贡献。

  我们枚举接入的那一端，贡献不好形式化的写出来：
  
  - 一个 $mxd_p\ge d$，其他的有 $\sum[mxd_q\ge d+1]$ 个，则对 $ans_{2d}$ 产生 $1+\sum[mxd_q\ge d+1]$ 的贡献。
  - 一个 $mxd_p\ge d+1$，其他的有 $\sum[mxd_q\ge d]$ 个，则对 $ans_{2d+1}$ 产生 $1+\sum[mxd_q\ge d]$ 的贡献。
- 从 $u,v$ 两端都接入，那么接入长度只能为 $d$，对 $ans_{2d}$ 产生贡献。

  不能枚举边再枚举儿子，菊花图就卡成 $n^2$ 了，应该枚举儿子接入长度为 $d$，然后给父亲的 $d$（对应位置）取 $\max$，再在父亲处考虑贡献。
  
不难发现，只要使得每个点 $x$ 儿子的 $mxd$ 排好序，相邻两项 $mxd$ 区间的贡献相同，把区间提出来离线单调栈一下即可。

瓶颈在排序，由于对每个点的儿子最长单链都要排序，不能进行桶排，根据实现复杂度为 $O(n\log_2n)$ 或 $O(\min{(n\log_wn,n\log_2w)})$。

~~不要问我后面那个丢人的复杂度是怎么来的。~~

---

