# [AGC024D] Isomorphism Freak

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc024/tasks/agc024_d

木 $ G $ の頂点を何色かで塗り分ける方法が *良い彩色* であるとは、同じ色で塗られたどの $ 2 $ つの頂点 $ u,v $ に対しても、 $ G $ を $ u $ を根とする根付き木として見た木と $ v $ を根とする根付き木として見た木が同型であることを指します。

また、$ G $ の *カラフルさ* とは、$ G $ の良い彩色で使われる色の種類数の最小値を指します。

$ N $ 頂点の木が与えられます。頂点には $ 1 $ から $ N $ までの番号がついており、$ i $ 本目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結んでいます。 この木に以下の操作を何度か繰り返し施し、木 $ T $ を作ります。

- 新たな頂点を $ 1 $ つ作る。現在の木の頂点をひとつ選び、その頂点と新しく作った頂点を辺で結ぶ。

$ T $ としてありうるもののカラフルさの最小値を求めてください。 さらに、その最小値を達成する木 $ T $ の葉(次数 $ 1 $ の頂点)の数の最小値を出力してください。

## 说明/提示

### ノート

$ G $ を $ u $ を根とする根付き木として見た木と $ v $ を根とする根付き木として見た木が同型であるとは、 $ G $ の頂点集合からそれ自身への全単射な写像 $ f_{uv} $ であって、以下を満たすものが存在することを指します。

- $ f_{uv}(u)=v $
- どの $ 2 $ 頂点の組 $ (a,b) $ についても、$ (a,b) $ 辺があることと $ (f_{uv}(a),f_{uv}(b)) $ 辺があることが同値である

### 制約

- $ 2\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ a_i,b_i\ \leq\ N(1\leq\ i\leq\ N-1) $
- 与えられるグラフは木である

### Sample Explanation 1

頂点 $ 6 $ を用意し、頂点 $ 2 $ と結んだとき、頂点 $ (1,4,5,6) $ を赤で、頂点 $ (2,3) $ を青で塗る彩色は良い彩色です。 $ 1 $ 色で全頂点を塗る彩色は良い彩色ではないので、作った木のカラフルさは $ 2 $ となることが分かります。 この場合が最適であり、葉は $ 4 $ つあるので、$ 2 $ と $ 4 $ を出力します。

## 样例 #1

### 输入

```
5
1 2
2 3
3 4
3 5```

### 输出

```
2 4```

## 样例 #2

### 输入

```
8
1 2
2 3
4 3
5 4
6 7
6 8
3 6```

### 输出

```
3 4```

## 样例 #3

### 输入

```
10
1 2
2 3
3 4
4 5
5 6
6 7
3 8
5 9
3 10```

### 输出

```
4 6```

## 样例 #4

### 输入

```
13
5 6
6 4
2 8
4 7
8 9
3 2
10 4
11 10
2 4
13 10
1 8
12 1```

### 输出

```
4 12```

# 题解

## 作者：关怀他人 (赞：7)

#### Solution
首先发现一点，设直径的长度为$D$，那么答案的下界是$\lceil \frac{D}{2}\rceil$（因为两棵树如果最大深度不同那么肯定不同构），而且这个下界很容易就可以达到。

如果$D$是奇数，那么这棵树的中心就是一条边，我们把这条边的两个端点作为根分别考虑两棵子树，那么要求深度相同的点的子节点个数相同，设$c_i$为所有深度为$i$的点的儿子数量的$max$，那么最小的叶子个数即为$\prod c_i$

如果$D$是偶数，要么是以中心点为根，要么是中心点和与其相邻的点一起作为中心（满足两棵子树的最大深度都小于等于$\frac{D}{2}$），将两种情况的答案取$max$即可。

时间复杂度$\mathcal O(n^2)$
#### Code
```cpp
int n,len,D,rt,d;
ll ans = llINF;
int head[MAXN],f[MAXN],dis[MAXN],maxSon[MAXN],dep[MAXN],ban[MAXN];

struct Edge{
    int to,next;
} e[MAXN << 1];

void add_edge(int u,int v){
    e[++len] = (Edge){v,head[u]};
    head[u] = len;
}

void dfs1(int u,int fa){
    f[u] = fa; dis[u] = dis[fa] + 1;
    if(dis[u] > dis[rt]) rt = u;
    checkMax(D,dis[u]);
    for(int i = head[u];i != -1;i = e[i].next){
        int v = e[i].to;
        if(v == fa) continue;
        dfs1(v,u);
    }
}

void dfs2(int u,int fa){
    int cnt = 0; dep[u] = dep[fa] + 1;
    for(int i = head[u];i != -1;i = e[i].next){
        int v = e[i].to;
        if(v == fa || ban[v]) continue;
        cnt += 1;
        dfs2(v,u);
    }
    checkMax(maxSon[dep[u]],cnt);
}

void Solve(int u,int v){
    memset(maxSon,0,sizeof(maxSon));
    maxSon[1] = 2; dep[0] = 1;
    ban[u] = ban[v] = 1;
    dfs2(v,0); dfs2(u,0);
    ban[u] = ban[v] = 0;
    ll c = 1;
    for(int i = 1;i <= d;i++) c *= maxSon[i];
    checkMin(ans,c);
}

int main(){
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i = 1,u,v;i < n;i++){
        scanf("%d%d",&u,&v);
        add_edge(u,v); add_edge(v,u);
    }
    dfs1(1,0); int t = rt; rt = 0; dfs1(t,0);
    d = (D + 1) >> 1;
    printf("%d ",d);
    if(D & 1){
        int u = rt;
        for(int i = 1;i < d;i++) u = f[u];
        dfs2(u,0); ll c = 1;
        for(int i = 1;i < d;i++) c *= maxSon[i];
        checkMin(ans,c);
        for(int i = head[u];i != -1;i = e[i].next){
            int v = e[i].to;
            Solve(u,v);
        }
    }else{
        int u = rt;
        for(int i = 1;i < d;i++) u = f[u];
        int v = f[u];
        Solve(u,v); 
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：pufanyi (赞：4)

我们发现其实最终所得的树只有两种，一种是以一条边为中心，左右两边同构，一种是以点为中心，呈放射状分布。

其实这两种都一样，以边为放射状的只要把这条边看成一个点就可以了。

这样我们考虑枚举中心，要求其权值，首先不难发现同构的数量其实就是以中心为根的树的深度。然后我们考虑叶子个数，我们只要想想构造这棵树的过程，其实就是把每一层深度的所有点的儿子数补成相同，那么补完后树的叶子个数就是每层非叶子节点儿子个数的乘积，对于原树来讲就是每层儿子树最多的儿子个数的乘积。

复杂度 $\mathcal{O}(n^2)$，开 $100$ 大概是为了不爆 `long long`。

---

## 作者：Kinandra (赞：4)

标签: 暴搜.

为了达到颜色数最少, 最终的树必定是以某一个点或某一个边为根, 深度相同的所有点的子树同构, 这样的答案是深度个颜色.

那么我们枚举每个点/边作为最后的根, bfs 就可以解决最小深度的问题了.

最小叶子节点数也很好处理, 显然深度相同的所有点的子树同构等价于深度相同的点度数相同, 我们对每一层的连向下一层度数取个最大值相乘即可.

时间复杂度 $\mathcal O(n^2)$.

ps: 实际上最后的根必定是直径的中点, 我们只需要做一次 bfs 就好了, 但是这个题目的数据范围很小(大概是因为叶子节点的个数增长很快), 所以可以直接枚举.

```cpp
#include <bits/stdc++.h>
#define pil pair<int, long long>
using namespace std;
int read();
int n;
vector<int> e[200005];
int deg[200005];
void add(int f, int t) {
    e[f].push_back(t), e[t].push_back(f), ++deg[f], ++deg[t];
}

int mxdeg[200005], dep[200005];

void chmax(int &x, int y) { x < y ? x = y : x; }

queue<int> q;

int bfs(int u, int v) {
    int rt = 0;
    for (int i = 1; i <= n; ++i) dep[i] = 0;
    q.push(u), dep[u] = 1;
    if (v) q.push(v), dep[v] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop(), chmax(mxdeg[dep[u]], deg[u]), chmax(rt, dep[u]);
        for (int i = 0, v; i < e[u].size(); ++i)
            if (!dep[v = e[u][i]]) dep[v] = dep[u] + 1, q.push(v);
    }
    return rt;
}
pil res;
pil work(int u, int v) {
    pil rt;
    for (int i = 1; i <= n; ++i) mxdeg[i] = 0;
    rt = (pil){bfs(u, v), mxdeg[1] - (v != 0)};
    for (int i = 2; i <= n; ++i) {
        if (mxdeg[i] == 1) break;
        rt.second *= (mxdeg[i] - 1);
    }
    if (v) rt.second *= 2;
    return rt;
}

int main() {
    n = read();
    if (n == 2) return puts("1 2"), 0;
    for (int i = 1; i < n; ++i) add(read(), read());
    res.first = 200000;
    for (int i = 1; i <= n; ++i) {
        res = min(res, work(i, 0));
        for (int j = 0; j < e[i].size(); ++j) res = min(res, work(i, e[i][j]));
    }
    printf("%d %d", res.first, res.second);
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
int read() {
    int x = 0, f = 1;
    char c = gc;
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x * f;
}
```


---

## 作者：TernaryTree (赞：0)

结论是如果直径是 $l$（直径上**点**的个数为 $l$）那你第一问答案下界是 $\left\lceil\dfrac l2\right\rceil$。

如果 $l$ 是偶数，我们这样看：把最中间那条边拎出来断掉，都接上一个新点作为根，我们要求若两个结点距离根距离相等，则它们为根的树同构。构造：同一深度的点的儿子个数均为原树当前深度结点儿子个数最大值，补全即可。第二问答案为 $\prod maxcnt_i$，$maxcnt_i$ 表示第 $i$ 层结点中儿子个数最多的儿子个数。

如果是奇数，不全面的想法是直接沿用 $l$ 偶数，将正中心的点作为根。这错误的原因是，注意到此时 $\left\lceil\dfrac {l+1}2\right\rceil=\left\lceil\dfrac l2\right\rceil$，所以我们把直径再变长 $1$ 也无所谓，此时就是用与中心相邻的边做 $l$ 是偶数的做法了。

时间复杂度 $\Theta(n^2)$。

```cpp
int dfs1(int u, int fa) {
	dep[u] = dep[fa] + 1;
	f[u] = fa;
	int ans = u;
	for (int v : tr[u]) {
		if (v == fa) continue;
		int p = dfs1(v, u);
		if (dep[p] > dep[ans]) ans = p;
	}
	return ans;
}

void dfs2(int u, int fa) {
	int cnt = 0;
	for (int v : tr[u]) {
		if (v == fa) continue;
		dfs2(v, u);
		++cnt;
	}
	br[dep[u]] = max(br[dep[u]], cnt);
}

int solve(int u) {
	rep(i, 0, n) br[i] = 0;
	dfs1(u, 0), dfs2(u, 0);
	int res = 1;
	rep(i, 0, n) if (br[i]) res *= br[i];
	return res;
}

int solve(int u, int v) {
	rep(i, 0, n) br[i] = 0;
	dep[v] = -1, dfs1(u, v), dfs2(u, v);
	dep[u] = -1, dfs1(v, u), dfs2(v, u);
	int res = 2;
	rep(i, 0, n) if (br[i]) res *= br[i];
	return res;
}

void fake_main() {
	n = read();
	rep(i, 1, n - 1) {
		int u = read(), v = read();
		tr[u].push_back(v);
		tr[v].push_back(u);
	}
	dep[0] = -1;
	int u = dfs1(1, 0), v = dfs1(u, 0), w = v, d = dep[v];
	ans1 = d / 2 + 1;
	vector<int> path;
	do {
		path.push_back(w);
		w = f[w];
	} while (w != u);
	if (d & 1) {
		ans2 = solve(path[d / 2], path[d / 2 + 1]);
	} else {
		int root = path[d / 2];
		for (int v : tr[root]) ans2 = min(ans2, solve(root, v));
		ans2 = min(ans2, solve(root));
	}
	cout << ans1 << " " << ans2 << endl;
}
```

---

## 作者：hegm (赞：0)

### [[AGC024D] Isomorphism Freak](https://www.luogu.com.cn/problem/AT_agc024_d)

有意思的题目，考虑把树的直径找出来，那么如果两个点关于中心对称，那么一定存在一种加点方式可以让他们为根的时候树是同构的，即以中心为根的树，深度一样的点一定存在一种方法同构。方法就是让同深度的点的子树都相同。

那么答案就是以中心为根节点的时候的最大深度。（如果中心有两个的话两节点深度都为 $1$。）

考虑如何同时让叶子数量尽可能的小，由于上面说过了，最好的方案就是让所有同深度的节点的子树都相同。所以我们对于深度 $i$ 的节点，他的儿子数一定是深度为 $i$ 的节点中儿子数量最多的节点。

那么答案就是所有深度的最大孩子数相乘。

但是这不全面，因为如果你本来直径长度为奇数，你可以再让直径长度加一变成偶数，这时同构数量不会变化，但是叶子数量是会变化的。

这里直接枚举一个出点也作为深度为 $1$ 的根就好。

### CODE

```cpp
#include<bits/stdc++.h>
#define fi first
#define int long long
#define se second
#define ull unsigned long long
#define make make_pair
#define N 105
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n;
struct fig
{
	int to,next;
}k[N*2];int tot,head[N],dep[N],a,b,fa[N],w[N];
void add(int from,int to)
{
	k[++tot].to=to;
	k[tot].next=head[from];
	head[from]=tot;
}
void dfs(int now)
{
	for(int i=head[now];i;i=k[i].next)
	{
		if(dep[k[i].to])continue;
		dep[k[i].to]=dep[now]+1;
		fa[k[i].to]=now;
		dfs(k[i].to);
	}
}
signed main()
{
	n=read();
	for(int i=1,u,v;i<n;i++)
	{
		u=read();v=read();
		add(u,v);add(v,u);
	}
	dep[1]=1;dfs(1);
	for(int i=1;i<=n;i++)if(dep[a]<dep[i])a=i;
	memset(dep,0,sizeof(dep));
	dep[a]=1;dfs(a);
	for(int i=1;i<=n;i++)if(dep[b]<dep[i])b=i;
	int len=(dep[b]+1)/2,x=b;int pos=len;
	len--;
	while(len--)x=fa[x];
	int ans=1;
	if(dep[b]%2)
	{
		memset(dep,0,sizeof(dep));
		dep[x]=1;
		dfs(x);
		for(int i=1;i<=n;i++)
		{
			int x=0;
			for(int j=head[i];j;j=k[j].next)
			if(dep[k[j].to]>dep[i])x++;
			w[dep[i]]=max(w[dep[i]],x);
		}
		for(int i=1;i<=n;i++)
		{
			if(!w[i])break;
			ans=ans*w[i];
		}
		for(int i=head[x];i;i=k[i].next)
		{
			int ans1=2;
			memset(dep,0,sizeof(dep));
			memset(w,0,sizeof(w));
			dep[x]=1;dep[k[i].to]=1;
			dfs(x);dfs(k[i].to);
			for(int j=1;j<=n;j++)
			{
				int x=0;
				for(int s=head[j];s;s=k[s].next)
				if(dep[k[s].to]>dep[j])x++;
				w[dep[j]]=max(w[dep[j]],x);
			}
			for(int j=1;j<=n;j++)
			{
				if(!w[j])break;
				ans1=ans1*w[j];
			}
			ans=min(ans,ans1);
		}
		cout<<pos<<" "<<ans<<"\n";
	}
	else
	{
		memset(dep,0,sizeof(dep));
		dep[x]=1;ans=2;
		dep[fa[x]]=1;
		dfs(x);dfs(fa[x]);
		for(int i=1;i<=n;i++)
		{
			int x=0;
			for(int j=head[i];j;j=k[j].next)
			if(dep[k[j].to]>dep[i])x++;
			w[dep[i]]=max(w[dep[i]],x);
		}
		for(int i=1;i<=n;i++)
		{
			if(!w[i])break;
			ans=ans*w[i];
		}
		cout<<pos<<" "<<ans<<"\n";
	}
	return 0;
}

```

---

## 作者：樱雪喵 (赞：0)

Tags: 构造。

手玩一下样例，设这棵树的直径长度为 $d$，猜测第一问的答案是 $\lceil\frac{d}{2}\rceil$。

由于结论比较好猜到，这里略证一下：

- 对于一条长度为 $d$ 的链，在不改变链长度的情况下链上的所有点只能两两对应，答案为 $\lceil\frac{d}{2}\rceil$。在链的尽头加点也一定不会让答案变小。
- 对于一棵树，我们找出它长度为 $d$ 的直径，显然这是一个答案下界。我们令链的中点为树的根（如果中点是一条边其实也同理），只要补全叶子让所有深度相同的子树均同构，就可以保证深度相同的节点均同色，一定能够取到这个下界。

对于第二问，我们直接采用上文的构造，答案为每层最多的节点儿子数之积。

代码太丑不放了。

---

## 作者：xht (赞：0)

## [Isomorphism Freak](https://atcoder.jp/contests/agc024/tasks/agc024_d)

### 题意

- 给定一棵 $n$ 个点的树。
- 你可以添加若干个新点，每次可以将其与某个已有的点相连。
- 要求最小化这棵无根树在以每个点为根对应的有根树中本质不同的树的数量，在此基础上最小化叶子的数量。
- $n \le 100$。

### 题解

设直径为 $d$，本质不同的有根树的数量有下界：

- 若 $d$ 为奇数，下界为 $\frac {d+1}2$。
- 若 $d$ 为偶数，下界为 $\frac d2$。

显然这个下界是可以取到的，设为 $ans$。

考虑如何最小化叶子的数量，显然叶子的数量也有一个下界，**大致上**为 $\prod_{i=1}^{ans-1} c_i$，其中 $c_i$ 为所有深度为 $i$ 的点的儿子数量的 $\max$（真实值还要根据 $d$ 的奇偶性分类讨论进行微调）。

显然这个下界也是可以取到的。

时间复杂度 $\mathcal O(n^2 \sim n^3)$。

### 代码

```cpp
const int N = 107;
int n, d[N], f[N], ans;
vi e[N];

void dfs(int x) {
	for (int y : e[x])
		if (y != f[x]) f[y] = x, d[y] = d[x] + 1, dfs(y);
}

inline ll calc(int x) {
	d[x] = 1, f[x] = 0, dfs(x);
	static int c[N];
	for (int i = 1; i <= ans; i++) c[i] = 0;
	for (int i = 1; i <= n; i++)
		c[d[i]] = max(c[d[i]], (int)e[i].size());
	ll ret = e[x].size();
	for (int i = 2; i < ans; i++) ret *= c[i] - 1;
	return ret;
}

inline ll calc(int x, int y) {
	d[x] = 1, f[x] = y, dfs(x);
	d[y] = 1, f[y] = x, dfs(y);
	static int c[N];
	for (int i = 1; i <= ans; i++) c[i] = 0;
	for (int i = 1; i <= n; i++)
		c[d[i]] = max(c[d[i]], (int)e[i].size()); 
	ll ret = 1;
	for (int i = 1; i < ans; i++) ret *= c[i] - 1;
	return ret * 2;
}

int main() {
	rd(n);
	for (int i = 1, x, y; i < n; i++)
		rd(x, y), e[x].pb(y), e[y].pb(x);
	d[1] = 1, f[1] = 0, dfs(1);
	int x = max_element(d + 1, d + n + 1) - d;
	d[x] = 1, f[x] = 0, dfs(x);
	int y = max_element(d + 1, d + n + 1) - d;
	int c = d[y];
	if (c & 1) {
		ans = (d[y] + 1) / 2;
		while (d[y] != ans) y = f[y];
		x = y;
		ll now = calc(x);
		for (int y : e[x])
			now = min(now, calc(x, y));
		print((ll)ans, now);
	} else {
		ans = d[y] / 2;
		while (d[y] != ans + 1) y = f[y];
		x = f[y];
		print((ll)ans, calc(x, y));
	}
	return 0;
}
```

---

