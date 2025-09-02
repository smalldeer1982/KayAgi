# The Hidden Pair (Hard Version)

## 题目描述

Note that the only difference between the easy and hard version is the constraint on the number of queries. You can make hacks only if all versions of the problem are solved.

 This is an interactive problem.

You are given a tree consisting of $ n $ nodes numbered with integers from $ 1 $ to $ n $ . Ayush and Ashish chose two secret distinct nodes in the tree. You need to find out both the nodes. You can make the following query:

- Provide a list of nodes and you will receive a node from that list whose sum of distances to both the hidden nodes is minimal (if there are multiple such nodes in the list, you will receive any one of them). You will also get the sum of distances of that node to the hidden nodes.

Recall that a tree is a connected graph without cycles. The distance between two nodes is defined as the number of edges in the simple path between them.

More formally, let's define two hidden nodes as $ s $ and $ f $ . In one query you can provide the set of nodes $ \{a_1,       a_2, \ldots, a_c\} $ of the tree. As a result, you will get two numbers $ a_i $ and $ dist(a_i, s) + dist(a_i, f) $ . The node $ a_i $ is any node from the provided set, for which the number $ dist(a_i, s) + dist(a_i, f) $ is minimal.

 You can ask no more than $ 11 $ queries.

## 说明/提示

The tree from the first test is shown below, and the hidden nodes are $ 1 $ and $ 3 $ .

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1370F2/deea4b0040e770b1c1e50ebf95e24ae594eea667.png)

## 样例 #1

### 输入

```
1
3
1 2
1 3

1 1

2 3

3 1

3 1

Correct```

### 输出

```
? 1 1

? 1 2

? 1 3

? 2 2 3

! 1 3```

# 题解

## 作者：Loser_Syx (赞：13)

教练把这题和另外三道逆天题搞成了一个一蓝三紫的 noip 模拟赛，这下这下了。

我们记 $dis(u,v)$ 为 $u$ 到 $v$ 最短路径长度，$x,y$ 为两个标记点，则 $dis(x,y) = \text{?}\ n\  a_1,a_2,a_3,\ldots,a_n$。

我们考虑此时询问得到的顶点 $u$，它一定存在于 $x\rightarrow y$ 的最短路径上，由于是树所以此路径唯一，那么以 $u$ 为根后，$x,y$ 一定是把 $dis(x,y)$ 分成了两段：$dis(x,u)$ 与 $dis(y,u)$，我们这里默认 $dis(x,u) > dis(y,u)$ 即 $dep_x > dep_y$。

因为 $u$ 是 $x\rightarrow y$ 的一条路径，所以 $u\rightarrow x$ 一定依次经过深度为 $1 \sim dep_x$ 的，在这些点到 $x,y$ 的路径长度一定 $dis(x,y)$（到 $y$ 的路径长度增加等同于到 $x$ 路径减少的那么多），而在深度 $> dep_x$ 的点时一定包含了 $x \rightarrow y$ 的路径和一些其他乱七八槽的路径，所以一定比第一次询问的长度大。

如此可见满足单调性，可以二分深度得出 $x$，每次二分的 $mid$，因为我们不知道 $x$ 是哪一个，把同样深度的所有点一起塞进去询问即可，最后根据返回长度进行收缩区间。

因为在 $dep_i = dep_x$ 的 $i$ 的答案中，$i$ 永远是要多走一段路走到 $x \rightarrow y$ 的路径上的，所以 $x$ 是唯一的（或者当 $dep_x = dep_y$ 时为唯二的），无论如何，返回的点一定是一个答案。

接下来考虑以该点为根，查询新的深度等于 $dis(x,y)+1$ 的那些点（$+1$ 是因为点比边多一），得到的 $y$ 一定是唯一的，证明见上。

算下来次数一共是 $1 + \lceil \log_2 n \rceil + 1$ 次，共 $12$，**不足以**通过此题，但可以通过 F1。

****

上面是 F1 做法，考虑优化。

显然我们无法改变前后两次，那么只能缩小二分范围。

注意到这样的性质，由于 $u$ 在 $x \rightarrow y$ 的路径上，所以 $u$ 把这个路径分成了两段，$dep_x = dis(x,u),dep_y = dis(y,u)$。

因为 $dis(x,u)+dis(y,u)=dis(x,y)$，而 $dis(x,u)\geq dis(y,u)$，所以 $dis(x,u)\geq\frac{dis(x,y)}{2}$，即 $dep_x\geq\frac{dis(x,y)}{2}$，故二分时 $l$ 端点可以扩大为 $\lceil \frac{dis(x,y)}{2} \rceil$。

我们在 F1 题解中说到的二分 $r$ 端点初值是 $\max dep_i$，但是是否还能缩小呢？答案是肯定的，因为 $u$ 在 $x \rightarrow y$ 的路径上，所以 $dis(x,u)\leq dis(x,y)$，即 $dep_x \leq dis(x,y)$。

一个显而易见的事实是 $dis(x,y) < n$，而二分区间为 $[\lceil \frac{dis(x,y)}{2} \rceil,\min(\max dep_i, dis(x,y))]$，则长度一定小于 $\frac{n}{2}$，省去了一次二分。

这样的话一共用了 $11$ 次，可以通过。

```cpp
const int N = 1010;
vector<int> g[N], all, d[N];
int dep[N], dmax;
void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	smax(dmax, dep[u]);
	d[dep[u]].emplace_back(u);
	for (const int i : g[u]) if (i != fa) dfs(i, u);
}
signed main() {
	int t; cin >> t;
	while (t--) {
		int n; dmax = 0; cin >> n;
		for (int i = 1; i <= n; ++i) g[i].clear(), d[i].clear();
		for (int i = 1, u, v; i < n; ++i) {
			cin >> u >> v;
			g[u].emplace_back(v);
			g[v].emplace_back(u);
		}
		cout << "? " << n << ' ';
		for (int i = 1; i <= n; ++i) cout << i << ' ';
		cout << endl;
		int root, dis; cin >> root >> dis;
		dfs(root, 0);
		int l = (dis+1)/2, r = min(dis+1, dmax), ans = 0;
		while (l <= r) {
			int mid = (l + r) >> 1;
			cout << "? " << d[mid].size() << ' ';
			for (const int i : d[mid]) cout << i << ' ';
			cout << endl;
			int s, t; cin >> s >> t;
			if (t == dis) ans = s, l = mid + 1;
			else r = mid - 1;
		}
		for (int i = 1; i <= n; ++i) d[i].clear();
		dfs(ans, 0);
		int a, b;
		cout << "? " << d[dis + 1].size() << ' ';
		for (const int i : d[dis + 1]) cout << i << ' ';
		cout << endl;
		cin >> a >> b;
		cout << "! " << ans << ' ' << a << '\n';
		fflush(stdout);
		string s; cin >> s;
	}
	return 0;
}
```

---

## 作者：Caro23333 (赞：4)

不甚困难的交互题，但最后一步确实没想到，还是技不如人。

不妨称两个被标记的点之间的路径为“标记路径”。

需要先获取一些全局的信息。第一次查询中，我们令查询的集合为所有顶点，这样我们会得到一个必然在标记路径上的顶点 $r$，以及标记路径的长度 $l$。自然地，我们将 $r$ 定为树的根。

注意到一个性质：设一个点 $x$ 到两个标记点的距离和为 $d$，则：

- 若 $x$ 处在标记路径上，则 $d=l$；

- 否则 $d>l$。

利用这一条性质，我们可以判断查询的集合中是否有点在标记路径上。

在确定根之后，我们可以预处理出每个点的深度，再预处理出若干集合 $S_1,S_2,\cdots$，其中 $S_t$ 是所有深度为 $t$ 的点组成的集合。

显然，标记路径上深度最大的顶点一定是答案之一，根据这一点我们想到可以二分此深度。

具体来讲，如果当前二分的中值为 $m$，那我们就查询 $S_m$ 这个集合，并判断返回的 $d$ 值是否等于 $l$。如果相等，那么最大深度不小于 $m$，否则最大深度小于 $m$。这样下去，最后一次 $d=l$ 的查询中，返回的 $x$ 值即为其中一个答案点，不妨记为 $a_1$。

最后再查询所有与 $a_1$ 距离为 $l$ 的点即可，所得的 $x$ 即为另一个答案点。这样的查询次数至多是 $1+\lceil\log_2 1000\rceil+1=12$，可以通过简单版。

最后的优化也十分简明：最大深度至少是 $\lceil\frac{l}{2}\rceil$，所以可以将二分左端点初值设为 $\lceil\frac{l}{2}\rceil$，即可将二分部分的查询次数减少 $1$，从而通过此题。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second

using namespace std;
typedef long long ll;
const int MAXN = 1005;
inline int readint()
{
	int res = 0, f = 1;
	char c = 0;
	while(!isdigit(c))
	{
		c = getchar();
		if(c=='-')
			f = -1;
	}
	while(isdigit(c))
		res = res*10+c-'0', c = getchar();
	return res*f;
}
int n;
struct Edge
{
	int u,v;
	Edge *next;
}*h[MAXN],pool[MAXN<<1];
int tot;
inline void addEdge(int u, int v)
{
	Edge *p = &pool[++tot], *q = &pool[++tot];
	p->v = v, p->next = h[u], h[u] = p;
	q->v = u, q->next = h[v], h[v] = q; 
}
vector<int> qs;
inline pii query(vector<int> &a)
{
	cout << "? " << a.size() << " ";
	for(int i = 0; i<a.size(); i++)
		cout << a[i] << " ";
	cout << endl, cout.flush();
	pii res;
	res.fi = readint(), res.se = readint();
	return res;
}
int dep[MAXN],dis[MAXN];
vector<int> d[MAXN];
inline void dfs(int u, int fa)
{
	d[dep[u]].push_back(u);
	for(Edge *p = h[u]; p; p = p->next)
		if(p->v!=fa)
			dep[p->v] = dep[u]+1, dfs(p->v,u);
}
inline void dfs1(int u, int fa)
{
	for(Edge *p = h[u]; p; p = p->next)
		if(p->v!=fa)
			dis[p->v] = dis[u]+1, dfs1(p->v,u);
}
int len,res;
inline bool check(int x)
{
	if(!d[x].size())
		return false;
	pii t = query(d[x]);
	if(t.se==len)
		res = t.fi;
	return t.se==len;
}
char stat[MAXN];
inline bool solve()
{
	memset(h,0,sizeof(h));
	memset(dep,0,sizeof(dep));
	memset(dis,0,sizeof(dis));
	res = tot = 0;
	for(int i = 0; i<MAXN; i++)
		d[i].clear();
	n = readint();
	for(int i = 1; i<n; i++)
		addEdge(readint(),readint());
	qs.clear();
	for(int i = 1; i<=n; i++)
		qs.push_back(i);
	pii t = query(qs);
	dfs(t.fi,0), len = t.se;
	int left = (len-1)/2+1, right = len, mid;
	while(left<=right)
	{
		mid = (left+right)>>1;
		if(check(mid))
			left = mid+1;
		else
			right = mid-1; 
	}
	int ans1 = res, ans2;
	dfs1(ans1,0);
	qs.clear();
	for(int i = 1; i<=n; i++)
		if(dis[i]==len)
			qs.push_back(i);
	ans2 = query(qs).fi;
	cout << "! " << ans1 << " " << ans2 << endl;
	cout.flush();
	cin >> stat+1;
	return stat[1]=='C';
}

int main()
{
	int T = readint();
	while(T--)
		if(!solve())
			break;
	return 0;
}

```


---

## 作者：45dinо (赞：3)

本来想把CF1370F1的文章 Ctrl+C+V 上来的，但感觉十有八九过不了，所以重新写一篇题解。

~~其实就是把不同之处写一写~~

>**这是一道交互题。困难版与简单版唯一的区别是交互次数限制。**

简单版：14次
复杂版：11次

$2\le n\le 1000$

所以最多要进行 $1+log2(1000)+1\approx 12$ 次操作。

~~啊啊啊啊，居然多了一次，太珂怕了吧！~~

其实有一个地方可以化简：在二分时初始的 $l,r$ 分别设定的是 $0,max(y,dis)$ （y的意义见简单版题解,dis指所有点的深度的最大值），但其实 $l$ 可以设成 $\frac y 2$ 。

原因很简单：$a$ 的深度大于等于 $b$ ，和等于 $y$ ，所以 $a$ 的深度大于等于 $\frac y 2$ 。

这样就可以少一次操作。 （$log2(1000)->log2(500)$）

~~还有一个彩蛋，如果你的程序能AC，就不会出现 ``Incorrect`` ，所以对 ``Incorrect`` 的处理对答案不影响，如果读入了 ``Incorrect`` 不一定要按照它的方法结束程序，甚至可以继续下去，但 AC 是不可能的了。~~

喜闻乐见的代码：（别跑，后面还有）
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int to,next;
} edge[2000];
int t,n,cnt,maxx,ans,head[1001],dep[1001];
vector<int> v,d[1001];
string s;
void add(int x,int y)
{
	edge[++cnt].to=y;
	edge[cnt].next=head[x];
	head[x]=cnt;
}
pair<int,int> query(vector<int> &x)
{
	cout<<"? "<<x.size()<<" "; 
	for(int i=0;i<x.size();i++)
		cout<<x[i]<<" ";
	cout<<endl;
	pair<int,int> p;
	scanf("%d%d",&p.first,&p.second);
	return p;
}
void dfs(int x,int fa)
{
    d[dep[x]].push_back(x);
    maxx=max(maxx,dep[x]);
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa)
		{
			dep[edge[i].to]=dep[x]+1;
			dfs(edge[i].to,x);
		}
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		maxx=cnt=ans=0; 
		v.clear();
		d[0].clear();
		for(int i=1;i<=n;i++)
		{
			head[i]=0;
			v.push_back(i);
			d[i].clear();
		}
		for(int i=1;i<n;i++)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			add(a,b);
			add(b,a);
		}
		pair<int,int> p=query(v);
		int dis=p.second;
		dep[p.first]=0;
		dfs(p.first,0);
		int l=(dis-1)/2,r=min(maxx,dis);
		while(l<=r)
		{
			int mid=(l+r)>>1;
			p=query(d[mid]);
			if(p.second==dis)
			{
				ans=p.first;
				l=mid+1;
			}	
			else
				r=mid-1;
		}
		dep[ans]=0;
		v.clear();
		dfs(ans,0);
		for(int i=1;i<=n;i++)
			if(dep[i]==dis)
				v.push_back(i);
		cout<<"! "<<ans<<" "<<query(v).first<<endl;
		cin>>s;
		if(s!="Correct")
        while(1)
				puts("MikeMirzayanov is an idiot!");//大危
	}
	return 0;
}
```
### 写在最后
~~花了三天时间A两道紫题好像不亏~~

通过这道题，对交互题和树形结构都有了较多的认识。

当时看到正解时，觉得每一步都十分巧妙。

其实能想到二分（这数据范围不二分干什么），但没有想到二分的范围和 $check$ 函数。

总而言之，还是太蒻了，继续加油QAQ！！！

![](https://cdn.luogu.com.cn/upload/image_hosting/2udom91v.png)

---

## 作者：sunkuangzheng (赞：1)

如果您还不会 F1，请先阅读 [F1 题解](https://www.luogu.com.cn/blog/679936/solution-cf1370f1)。

$\Large \textbf{1.Hints}$

$\textbf{1.1 Hint 1}$

尝试减少二分次数。

$\textbf{1.2 Hint 2}$

$l$ 的下界能收紧一些吗？

$\Large \textbf{2.Solution}$

我们知道在 easy version 里，我们需要 $12$ 次询问，而 $10$ 次用在二分上。显然最开始和最后一次的询问是不可避免的，考虑优化二分过程。

我们知道我们二分的是深度较大的那个点的深度，而链长为 $d$。显然的，最大深度一定不小于 $\lceil \dfrac{d}{2} \rceil$。因此，调整二分下界 $l$，二分只需要 $\lceil \log_2(\dfrac{d}{2}) \rceil \le 9$ 次询问，总询问次数不会超过 $11$ 次。



```cpp
/**
 *    author: sunkuangzheng
 *    created: 23.10.2023 10:47:19
**/
#include<bits/stdc++.h>
using namespace std;
int t,n,k,w,u,v,dep[1005],nk,t1,t2;vector<int> acc,g[1005],d[1005];string sb;
pair<int,int> ask(vector<int> &acc){
    cout << "? " << acc.size() << " ";
    for(int i : acc) cout << i << " ";
    cout << endl,cin >> k >> w;return {k,w};
}void dfs(int u,int fa){
    dep[u] = dep[fa] + 1,d[dep[u]].push_back(u);
    for(int v : g[u]) if(v != fa) dfs(v,u);
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> t;
    while(t --){
        cin >> n,acc.clear();
        for(int i = 1;i <= n;i ++) g[i].clear(),acc.push_back(i),d[i].clear();
        for(int i = 1;i < n;i ++) cin >> u >> v,g[u].push_back(v),g[v].push_back(u);
        auto [u,nk] = ask(acc);dfs(u,0);
        int r = min(nk + 1,*max_element(dep+1,dep+n+1)),l = (r + 1) / 2,ans = -1;//调整二分下界
        while(l <= r){
            int mid = (l + r) / 2;
            if(auto [t1,t2] = ask(d[mid]);t2 == nk) ans = t1,l = mid + 1;
            else r = mid - 1;
        }for(int i = 1;i <= n;i ++) d[i].clear();
        dfs(ans,0);auto [res,fkccf] = ask(d[nk + 1]);
        cout << "! " << ans << " " << res << endl,cin >> sb;
    }
}
```

---

## 作者：墨舞灵纯 (赞：1)

### 题意

给定一棵树，有两个点 $a,b$ 被暗中标记，每次可以询问一个集合，会返回这个集合里的某个节点 $u$ ，满足 $dis_{a,u}+dis_{b,u}$ 最小。请在 $11$ 次以内完成询问并输出被标记的点。

### 题解

考虑如何知道 $s \rightarrow t$ 的路径长度：把所有点拿去询问一遍。这样我们一定会得到路径上的任意一点 $x$ 以及路径长度 $L$ 。

然后我们把 $x$ 作为树的根 $root$ 进行 $dfs$ ，这样我们就是找两个点 $a,b$ 使得 $dis_{a,root}+dis_{b,root}=L$ ，易得知一定有一个点到 $root$ 的距离 $\geq \lceil \frac{L}{2} \rceil$ ，另一个点到 $root$ 的距离 $\leq \lfloor \frac{L}{2} \rfloor$ ，又发现$11-1=10=log_2(1024)$ ，也就是最多进行 $log$  次询问，可以想到二分。所以我们二分其中一个点到 $root$ 的距离再通过询问找另一个点就可以了。

### 注意

每次要读入一个表示正确和错误的字符串！

### 代码

$\color{#abcdef}{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
int h[N], nxt[N], adj[N], u, v, t, rot, T, L, d[N], n;
string tmp;
vector<int> vec, g[N];
inline void add() { nxt[++t] = h[u], h[u] = t, adj[t] = v, nxt[++t] = h[v], h[v] = t, adj[t] = u; }
inline void que() {
    cout << '?' << ' ' << vec.size();
    for (const int &i : vec) cout << ' ' << i;
    cout << endl, cout << flush, cin >> u >> v;
}
void dfs(int x, int fa) {
    d[x] = d[fa] + 1, g[d[x] - 1].push_back(x);
    for (int i = h[x]; i; i = nxt[i])
        if (adj[i] != fa)
            dfs(adj[i], x);
}
void dfs(int x, int fa, int dis) {
    if (!dis) return vec.push_back(x), void();
    for (int i = h[x]; i; i = nxt[i])
        if (adj[i] != fa)
            dfs(adj[i], x, dis - 1);
}
void MidSearch() {
    int l = L + 1 >> 1, r = L, mid, s = 0;
    while (l <= r) {
        mid = l + r >> 1, vec = g[mid];
        if (vec.empty()) {
            r = mid - 1;
            continue;
        }
        que(), v <= L ? s = u, l = mid + 1 : r = mid - 1;
    }
    vec.clear(), dfs(s, 0, L), que(), cout << '!' << ' ' << s << ' ' << u << endl, cout << flush;
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> T; int i;
    while (T--) {
        cin >> n, vec.clear();
        for (i = 1; i <= n; ++i) h[i] = 0, vec.push_back(i), g[i].clear(); t = 0;
        for (i = 1; i < n; ++i) cin >> u >> v, add();
        que(), rot = u, L = v, dfs(rot, 0), MidSearch(), cin >> tmp;
    }
    return 0;
}

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1370F2 The Hidden Pair (Hard Version) (*2700)](https://www.luogu.com.cn/problem/CF1370F2)

# 题目描述

真的很难吗？

我们首先考虑找出第一个特殊点。

我们可以先求出这两个点路径中的任意一个点。发现询问 $1 \sim n$ 就使我们需要的询问、

接下来以这个路径中的一个点为根来确定每个节点的深度。

接下来考虑二分出两个特殊点的路径中最深的点，容易发现这个东西是有单调性的。

我们找到一个点后，我们发现这个点就是路径的边界，那么我们就可以以找到的这个特殊点为根来根据我们的第一次询问确定另一个特殊点的深度。

这样就能找到两个特殊点了。

询问次数为 $12$ 次，可以通过 F1。

我们继续考虑优化二分的边界。

假设这条路径为 $dis$，根节点深度为 $1$，那么最深的那个节点深度至少为 $\lceil \frac{dis}{2} \rceil$，至多为 $dis + 1$，

那么我们就将二分次数减少了 $1$ 次。

此时总共询问 $11$ 次，可以通过 F2。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll (i)=(a);i<=(b);(i)++)
#define forr(i,a,b) for(re ll (i)=(a);i>=(b);(i)--)
#define forll(i,a,b,c) for(re ll (i)=(a);i<=(b);(i)+=(c))
#define forrr(i,a,b,c) for(re ll (i)=(a);i>=(b);(i)-=(c))
#define forL(i,a,b,c) for(re ll (i)=(a);((i)<=(b)) && (c);(i)++)
#define forR(i,a,b,c) for(re ll (i)=(a);((i)>=(b)) && (c);(i)--)
#define forLL(i,a,b,c,d) for(re ll (i)=(a);((i)<=(b)) && (d);(i)+=(c))
#define forRR(i,a,b,c,d) for(re ll (i)=(a);((i)>=(b)) && (d);(i)-=(c))
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) (1ll*(x)/__gcd(x,y)*(y))
#define Sum(x,y) (1ll*((x)+(y))*((y)-(x)+1)/2)
#define x first
#define y second
template<typename T1,typename T2>bool Max(T1&x,T2 y){if(y>x)return x=y,1;return 0;}
template<typename T1,typename T2>bool Min(T1&x,T2 y){if(y<x)return x=y,1;return 0;}
ll _t_;
void _clear(){}
ll n;
ll x,y;
ll dep[1010];
vector<ll>G[1010];
vector<ll>D[1010];
vector<ll>q;
string s;
ll L,R;
pii ans;
pii ask(vector<ll>a)
{
    
    cout<<"? "<<a.size()<<' ';
    for(auto i:a)
        cout<<i<<' ';
    cout<<endl;
    ll x,y;
    cin>>x>>y;
    return {x,y};
}
void dfs(ll x,ll fa,ll deep)
{
    Max(R,deep);
    D[deep].pb(x);
    for(auto i:G[x])
        if(i!=fa)
            dfs(i,x,deep+1);
}
void solve()
{
    _clear();
    cin>>n;
    forl(i,1,n)
        G[i].clear();
    forl(i,2,n)
        cin>>x>>y,
        G[x].pb(y),
        G[y].pb(x);
    q.clear();
    forl(i,1,n)
        q.pb(i);
    pii num=ask(q);
    q.clear();
    forl(i,1,n)
        D[i].clear();
    R=0;
    dfs(num.x,0,1);
    L=max(1ll,(num.y+1)/2);
    Min(R,num.y+1);
    while(L<R)
    {
        ll Mid=(L+R+1)/2;
        pii now=ask(D[Mid]);
        if(now.y==num.y)
            ans.x=now.x,
            L=Mid;
        else
            R=Mid-1;
    }
    forl(i,1,n)
        D[i].clear();
    dfs(ans.x,0,1);
    pii num2=ask(D[num.y+1]);
    ans.y=num2.x;
    cout<<"! "<<ans.x<<' '<<ans.y<<endl;
    cin>>s;
}
int main()
{
//    freopen("tst.txt","r",stdin);
//    freopen("sans.txt","w",stdout);
//    IOS;
    _t_=1;
    cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

---

## 作者：tzl_Dedicatus545 (赞：0)

$f$ 是题目里的询问。。。

一眼丁真，先问 $f([n])$，得到 $u\to v$ 路径上的一个点以及 $dis(u,v)$。

知道了这个以后，我们不妨以这个点定做根，则 $u$ 与 $v$ 必定位于不同的子树。

我们按照 $dep_x$ 分层，每次我们问所有深度为 $d$ 的点，可以知道 $\max(dep_u,dep_v)$ 是否大于 $d$。

重要的技巧是：因为 $dep_u+dep_v$ 为定值 $k$，我们只需二分 $[1,\dfrac{k}{2}]$ 即可。

可以通过 F1、F2。

---

## 作者：under_the_time (赞：0)

## 题意

> *交互题。* 给你一棵 $n$ 个点的树，需要得出树上两个点 $X,Y$ 的位置。你可以向评测机询问一个点集，评测机会回答点集中与 $X,Y$ 距离和最小的点，以及这个距离和。询问不超过 $11$ 次。 

## 思路

询问次数不能超过 $11$ 次，这个数字与 $\log n$ 的值很接近。考虑先对所有 $n$ 个点进行询问，这样就可以得到 $X,Y$ 之间的距离，和一个必定在 $X,Y$ 路径上的点。设这个点为 $rt$，$X,Y$ 之间的距离为 $dis$。如果我们以 $rt$ 为树根，那么对于树中深度为 $dep$ 的点集 $\{A\}$，且 $dep$ 大于等于 $X,Y$ 中较小的深度，我们对其进行询问：

- 如果询问得到的距离和为 $dis$，则表示询问得到的点在 $X,Y$ 的路径上，即 $X,Y$ 中较大的深度大于等于 $dep$；
- 如果询问得到的距离和大于 $dis$，则表示该深度的点中没有在 $X,Y$ 的路径上的，即 $X,Y$ 中较大深度小于 $dep$。

对于第一种情况询问到的点都可能是 $X,Y$ 中深度较大的点，不妨令 $dep_X\ge dep_Y$。考虑二分，区间为 $[\lfloor\cfrac{dis}{2}\rfloor,\min(dis,Dep)]$，其中 $Dep$ 为最大深度。每一轮都询问一次深度为 $mid$ 的点集，按照上述两种情况二分，最终可以得到深度较大的 $X$。然后我们以 $X$ 为树根，然后询问深度为 $dis$ 的点集，得到的点即为 $Y$。

**为什么二分区间上界可以这么取？**

感性理解一下，因为我们要处理出 $X,Y$ 较深的一个点，所以深度小于 $dis(X,Y)$ 的点都不会是那个较深的点。

## 实现

实现没什么难点，注意每次询问/回答都要 `fflush(stdout)`。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;
vector<int> mp[maxn << 1];
void addEdge(int u,int v) {
    mp[u].push_back(v);
}
vector<int> a[maxn]; int Dep;
void dfs(int u,int fa,int dep) {
    a[dep].push_back(u);
    Dep = max(Dep,dep);
    for (auto v : mp[u]) {
        if (v == fa) continue;
        dfs(v,u,dep + 1);
    }
}
pair<int,int> Query(const vector<int> &ask) {
    printf("? %d",ask.size());
    for (auto x : ask) printf(" %d",x);
    puts(""); 
    fflush(stdout);
    int x,d;
    scanf("%d %d",&x,&d);
    return make_pair(x,d);
}
pair<int,int> Solve(int n,const vector<pair<int,int> > &edge) {
    for (int i = 1;i <= n;i ++)
        mp[i].clear();
    for (int i = 0;i <= Dep;i ++) a[i].clear();
    Dep = 0;
    for (auto E : edge) {
        int u = E.first, v = E.second;
        addEdge(u,v); addEdge(v,u);
    }
    vector<int> ask;
    for (int i = 1;i <= n;i ++) ask.push_back(i);
    pair<int,int> res = Query(ask);
    int rt = res.first, sum = res.second;
    dfs(rt,0,0);
    int l = sum >> 1, r = min(Dep,sum);
    int X = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        res = Query(a[mid]);
        if (res.second == sum) l = mid + 1, X = res.first;
        else r = mid - 1;
    }
    for (int i = 0;i <= Dep;i ++) a[i].clear();
    Dep = 0; dfs(X,0,0);
    return make_pair(X, Query(a[sum]).first);
}
int T,n; char AC_or_WA[maxn];
vector<pair<int,int> > Edge;
int main() {
    scanf("%d",&T);
    while (T --) {
        scanf("%d",&n);
        Edge.clear();
        for (int i = 1,u,v;i < n;i ++) {
            scanf("%d%d",&u,&v);
            Edge.emplace_back(u,v);
        }
        pair<int,int> ans = Solve(n,Edge);
        printf("! %d %d\n",ans.first,ans.second);
        fflush(stdout);
        scanf("%s",AC_or_WA + 1);
    }
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

唐人做唐题。考虑 $\text{query}(\{1,2,3,\dots,n\})$，得到了两个关键点之间的距离和他们路径上的某一个节点 $u$。

以 $u$ 为根，两个关键点 $c$ 和 $d$ 在两个不同的子树内。

考虑到 $c$ 和 $d$ 之间的路径和一个水平面（深度相同的点）只有一个交点，那么就可以通过二分得到较深的那一个点，设为 $c$。

再以 $c$ 为根，按照 $c$ 和 $d$ 之间的距离画一个水平面，与路径也只有一个交点，为 $d$。

这样需要 $2+ \log(n)$ 次询问。

注意到我们是找到较深点，所以它所在的可能深度范围小于等于 $\dfrac{n}{2}$，审掉了一次询问。

可以通过 $\rm Easy \ version$ 和 $\rm Hard \ version$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000+10;
int n,T,dis[MAXN],dep[MAXN];
vector<int> G[MAXN];
pair<int,int> query(vector<int> vc) {
	if(vc.empty()) return {0,0};	
	cout<<"? "<<vc.size()<<' ';for(auto id:vc) cout<<id<<' ';cout<<endl;
	int x,d; cin>>x>>d;
	return {x,d};
}
void dfs(int u,int f,int *dis) {
	dis[u]=dis[f]+1;
	for(auto v:G[u]) if(v!=f) dfs(v,u,dis);
	return ;	
}
vector<int> gen(int deep) {
	vector<int> ans;
	ffor(i,1,n) if(dep[i]==deep) ans.push_back(i);
	return ans;	
}
int main() {
	cin>>T;
	while(T--) {
		cin>>n; ffor(i,1,n) G[i].clear();
		ffor(i,1,n-1) {int u,v; cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
		vector<int> vc; ffor(i,1,n) vc.push_back(i);
		auto pr=query(vc); int len=pr.second,rt=pr.first;
		dfs(rt,0,dep);
		int L=(len+1)/2,R=len,ans=0;
		while(L<=R) {
			int mid=L+R>>1;
			auto pr=query(gen(mid+1));
			if(pr.second==len) ans=pr.first,L=mid+1;
			else R=mid-1;	
		}
		dfs(ans,0,dep);
		int ot=query(gen(len+1)).first;
		cout<<"! "<<ans<<' '<<ot<<endl;
		string result; cin>>result;
	}
	return 0;
}
```

---

## 作者：N1K_J (赞：0)

写这道题的时候旁边打音游的不停肘我，RMJ 似了几次，真的难蚌。

约定标记点为 $p,q$，点 $x,y$ 之间的距离为 $dis(x,y)$，点 $x,y$ 之间的路径为 $Path_{x,y}$。

首先，考虑询问一次所有的点，这时结果 $(x_0,d_0)$ 必定满足 $x_0$ 在 $Path_{p,q}$ 上，$d_0=dis(p,q)$。

考虑以 $x_0$ 为根，考虑此时 $p,q$ 中深度较深的点。

我们考虑二分这个深度，每次将所有二分到的深度 $M$ 上所有点询问一次，设答案为 $x_M,d_M$。若 $d_M = d_0$，那么这相当于这些点中存在 $Path_{p,q}$ 上的点，也就是 $p,q$ 中较深点深度不低于 $M$，否则，说明较深点深度小于 $M$。

应当注意到，最后一次询问会得到较深点的位置（除非两个点深度相同，但是这是不会影响后面的过程的）。

接下来，以这个较深点为根，显然我们可以计算出另一点的深度，直接对该深度的所有点做一次询问就好了。

注意到这会最多有 $1+\log_2{1024}+1=12$ 次询问。

不过由于较深点的深度肯定不小于 $\dfrac{d_0}{2}$，所以我们将二分时左端点设为 $\dfrac{d_0}{2}$ 节省 $1$ 次询问就能通过本题。

[Code](codeforces.com/contest/1370/submission/255481610)

---

