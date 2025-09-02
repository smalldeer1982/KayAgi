# Frog Traveler

## 题目描述

青蛙在 $n$ 米深的井中。

对于每一个深度，有两个量 $a_i$ 和 $b_i$。

$a_i$ 表示在深度为 $i$ 米的时候可以往上跳的最高高度，就是说在深度为 $i$ 米的地方可以往上跳 $\left[0,a_i\right]$ 米。

$b_i$ 表示在深度为 $i$ 米的地方时会往下滑 $b_i$ 米。

青蛙每跳一次，就会下滑一次。

请求出青蛙最少跳几次可以跳出井（深度为 $0$ 米）。

## 说明/提示

$1\le n\le3\times10^5,0\le a_i\le i,0\le b_i\le n-i$。

## 样例 #1

### 输入

```
3
0 2 2
1 1 0```

### 输出

```
2
1 0```

## 样例 #2

### 输入

```
2
1 1
1 0```

### 输出

```
-1```

## 样例 #3

### 输入

```
10
0 1 2 3 5 5 6 7 8 5
9 8 7 1 5 4 3 2 0 0```

### 输出

```
3
9 4 0```

# 题解

## 作者：GaryH (赞：18)

# CF1601B 题解

看见大家貌似都用的 $O(nlogn)$ 做法，那我就来一发 $O(n)$ 且很好实现的做法吧.

题意：有两个序列 $a,b$ ，若在位置 $i$ ，则可以跳到 $x \in [i,i - a_i]$ 中的所有位置，

但每次跳到了某个位置 $j$ 后，会滑落到第 $j + b_j$ 个位置。

求初始在位置 $n$ ，目标在位置 $0$ 的最少跳跃次数，并给出方案。

做法：

我们发现，每次跳跃后滑落前可以到达的位置集合，必然是一个右端点为 $n$ 的区间。

这个结论可以用数学归纳法证明，即：

若上一次滑落前可以到达的位置集合是一个区间，我们记这个区间为 $[l,n]$。那么：

这一次跳跃后，不可能出现两个可以到达的位置 $x,y$ （不妨令 $x<y$），使得：

1. $x \notin [l,n]$
2. $y \notin [l,n]$
3. $y \neq x + 1$

口头上说就是：这次跳跃后，可以到达的且不在区间 $[l,n]$ 内的位置，必然形成一段连续区间。

而上一次滑落前可以到达的区间，这一次也都可以到达。

至于原因，是：设上一次滑落前，我们已经跳跃了 $s$ 次，

则对于 $\forall x \in [l,n]$，我们都有一种方案，使得从起点跳跃 $s$ 次后到达位置 $x$ 。

我们只需要在这个方案的开头添加一次原地跳，就可以构造出一种跳 $s+1$ 次后到达位置 $x$ 的方案。

这一定可行，因为题意保证 $b_n = 0$，我们第一次跳 $0$ 个位置，原地不动即可。

于是，我们将 $[l,n]$ 和新增区间拼在一起后，就形成了一个更大的区间，也证明了上面的结论。

所以，我们可以动态的维护上面 $[l,n]$ 里的 $l$，

具体来说，我们令 $c_i = i + b_i - a_{i + a_i}$，代表上一次滑落前到达位置 $i$ ，这次能到达的最小位置。

那么我们对序列 $c$ 做前缀最大值，同时记录最大值所在的位置，

即可求出，在某次跳跃后滑落前，可以到达的点集区间是 $[l,n]$ 时，下一次能跳到哪里。即：

设 $mx_i = max(mx_{i+1},c_i)$，$rs_i = p$，其中 $c_p = mx_i$。

于是，对于某次跳跃后滑落前，可达的点集区间 $[l,n]$，其下一次就可以到达区间 $[mx_l,n]$，

而在最优解中，当前这次跳跃所到达的位置就是 $rs_l$.

我们还可以发现，若上面的 $mx_l \geq l$ ，则我们不可能跳到顶点，因为我们就会卡在这里。

预处理是 $O(n)$ 的，而动态维护区间 $[l,n]$ 时，每一次 $l$ 必然减 $1$，直到减到 $0$，否则会输出无解，

故这样的时间复杂度是 $O(n)$ 的。

这里给出代码实现：

```
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)

const int N (3e5 + 10);
int n, a[N], b[N], c[N], rs[N], mn[N];
vector < int > ans;
 
int main() {
	n = read(); rep (i, 1, n) a[i] = read();
	rep (i, 1, n) b[i] = read(), c[i] = max(0, i + b[i] - a[i + b[i]]);
	rep (i, 0, n + 1) mn[i] = rs[i] = 1e9;
	per (i, n, 1) mn[i] = min (mn[i + 1], min(i, c[i])),
				  rs[i] = min (i, c[i]) < mn[i + 1] ? i : rs[i + 1];
	int hi = n;
	rep (i, 1, n) {
		ans.pb(hi = rs[hi]);
		if (hi <= mn[hi]) break;
		hi = mn[hi]; if (!hi) break;
	}
	if (hi) return cout << -1, 0;
	int sz = ans.size(); cout << sz << endl;
	rep (i, 1, sz - 1) cout << ans[i] << ' ';
	return cout << 0, 0;
}
```



---

## 作者：itisover (赞：9)

考虑贪心，发现对于当前深度 $now$，我们能跳到的区间是 $[now-a_{now},now]$，我们肯定会跳这个区间内，实际深度最小（高）的点（实际深度定义为跳之后滑下来的深度）。

证明：

感性理解法：我们要跳的尽可能高以跳出井，所以我们要让能跳到的区间尽可能的大（左端点尽可能小），这样选到能跳出去的关键点的概率肯定是更大的。

反证法（算是？）：不合法当且仅当有一个实际深度更大的点能经过若干次跳跃能跳到关键点并跳出去，那我选实际深度更小的也一定能选到这个关键点。

考虑怎么维护，我们发现对于一个深度 $i$ 首先要满足 $i+b_i\ge now-a_{now}$ 且 $i \ge now-a_{now}$

考虑用主席树，所以我们对 $i+b_i$ 建时间轴，每个结点维护当前区间内的实际深度最小值和在哪个点能取到这个值，对于叶子结点 $l==r$，它的实际深度表示为 $l+b_l-a_{l+b_l}$，即先滑再跳，能取到这个值的显然是 $l$

类似于传统主席树前缀和建树，我们对时间轴后缀和建树

查询就是找大于等于 $now-a_{now}$ 的 $i+b_i$ 这棵树上的区间 $[now-a_{now},now]$ 的实际深度最小值和取到这个值的 $l$

显然，每次的 $l$ 就是我们的路径，对于下一个 $now$，它等于 $l+b_l$

特别地，对于无解的判断就是下一个 $now$ 和这个 $now$ 的值相同，即原地不动没法跳了。

智商不够 Data structures 来凑

[code](https://codeforces.com/contest/1602/submission/133111419)

---

## 作者：little_sun (赞：7)

### 题目大意

有一只青蛙掉到了井底，这口井被划分为 $n+1$ 个位置，井口是 $0$ ，井
底是 $n$ 。

现在这只青蛙想跳出这口井，假设它当前在位置 $i$，则它可以向上跳 $0$ 到 $a_i$ 的任意整数距离。

又因为井口很滑，所以如果青蛙跳到了位置 $j$，则它会往下滑 $b_j$ 个位置。

给定 $n, a, b$，你需要求出青蛙最少跳多少次才能跳出井（跳到位置 $0$ ），并给出方案。

$1 \leq n \leq 3 \times 10^5$ 

### 题目分析

如果忽略跳到位置 $i$ 会往下滑 $b_i$ 这个限制，那么这题可以轻松使用线段树优化建图+最短路解决。

考虑添加了这个限制怎么做，我们建立 $n+1$ 个虚点 $[n+1,2n+1]$ 表示跳到 $[0, n]$ 且还没往下滑时的状态。

由于 $b_i$ 不变，那么每次建边就可以拆成两个部分：

1. $i$ 到 $[i-a[i],i]$ 的虚点，边权为 $1$。
2. $[i-a[i],i]$ 的虚点 到其各自对应的点，边权为 $0$。

$1$ 部分可以用线段树优化建图解决， $2$ 部分则可以在初始化时建立。

最后我们发现所有边边权为 $0,1$，故我们可以用双端队列 $\texttt{bfs}$ 降低复杂度，总时间复杂度 $ \Theta (n \log n)$

### 代码

``` cpp
#include <bits/stdc++.h>

#define R register
#define ll long long
#define sum(a, b, mod) (((a) + (b)) % mod)
#define meow(cat...) fprintf(stderr, cat)

const int MaxN = 4e5 + 10;
const int Max = MaxN << 5;
const int inf = 0x3f3f3f3f;

struct edge
{
    int next, to, dis;
} e[Max];

int head[Max], a[MaxN], b[MaxN];
int n, m, cnt, dis[Max], vis[Max], pre[Max];

void add_edge(int u, int v, int d)
{
    ++cnt;
    e[cnt].to = v;
    e[cnt].dis = d;
    e[cnt].next = head[u];
    head[u] = cnt;
};

inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x;
}

struct SegmentTree
{
    int cnt, idx[Max];
    void build(int id, int l, int r)
    {
        if(l == r) 
            return (void) (idx[id] = l + n + 1);
        idx[id] = ++cnt; int mid = (l + r) >> 1;
        build(id << 1, l, mid), build(id << 1 | 1, mid + 1, r);
        if(idx[id << 1]) add_edge(idx[id], idx[id << 1], 0);
        if(idx[id << 1 | 1]) add_edge(idx[id], idx[id << 1 | 1], 0);
    }
    void modify(int id, int l, int r, int ql, int qr, int u)
    {
        if(ql > r || l > qr) return;
        if(ql <= l && r <= qr) 
            return add_edge(u, idx[id], 1);
        int mid = (l + r) >> 1;
        modify(id << 1, l, mid, ql, qr, u);
        modify(id << 1 | 1, mid + 1, r, ql, qr, u);
    }
} T;

void bfs()
{
    std::deque<int> q;
    dis[n] = 0, q.push_back(n);
    while(!q.empty())
    {
        int u = q.front(); q.pop_front();
        if(vis[u]) continue; vis[u] = 1;
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].to;
            if(dis[v] > dis[u] + e[i].dis)
            {
                dis[v] = dis[u] + e[i].dis;
                if(!vis[v])
                {
                    if(e[i].dis) q.push_back(v);
                    else q.push_front(v); pre[v] = u;
                }
            }
        }
    }
}

signed main()
{   
    int now = 0;
    n = read(), T.cnt = 2 * n + 1, memset(dis, 0x3f, sizeof(dis));
    for(int i = 1; i <= n; i++) a[i] = read();
    for(int i = 1; i <= n; i++) b[i] = read();
    for(int i = 0; i <= n; i++)
        add_edge(i + n + 1, i + b[i], 0);
    T.build(1, 0, n);
    for(int i = 1; i <= n; i++)
        T.modify(1, 0, n, i - a[i], i, i);
    bfs(), printf("%d\n", dis[0] == inf ? -1 : dis[0]);
    if(dis[0] != inf)
    {
        std::vector<int> path;
        while(now != n) 
        {
            if(n + 1 <= now && now <= 2 * n + 1) 
                path.push_back(now - n - 1);
            now = pre[now];
        }
        std::reverse(path.begin(), path.end());
        for(auto x : path) printf("%d ", x);
    }
    return 0;
}
```

---

## 作者：SenriAkane (赞：5)

$f[i]$ 代表从 $n$ 跳到 $i$ 的最少的次数。从 $n$ 到 $1$ 进行 $dp$：如果已求得 $f[i]$，我们令 $low=i+b[i]$, 那么就可以用 $f[i]+1$ 来更新 $low-a[low] \leq k \leq low$ 的 $f[k]$ 值。更新过程中保存被更新的 $k$ 是由 $i$ 跳来的。由于要更新整个区间，所以用线段树维护区间最小值和区间最小值点是由哪个点跳转而来的。
```cpp
#include <bits/stdc++.h>
#define L k<<1
#define R k<<1|1
#define fi first
#define se second
#define int long long
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
const int maxn = 3e5+7;
const int INF = 1e9;
struct Node {
	int val,to;
};
Node t[maxn<<2];
Node lazy[maxn<<2];
int a[maxn];
int b[maxn];
Node min(Node a,Node b) {
	if (a.val<b.val) return a;
	return b;
}
void pushDown(int k,int l,int r) {
	if (lazy[k].val>=INF||r<l) return;
	lazy[L] = min(lazy[L],lazy[k]);
	lazy[R] = min(lazy[R],lazy[k]);
	t[L] = min(t[L],lazy[k]);
	t[R] = min(t[R],lazy[k]);
	lazy[k].val = INF; 
}
Node query(int k,int l,int r,int x) {
	if (r==l) {
		return t[k];
	}
	else {
		pushDown(k,l,r);
		int mid = (l+r)/2;
		if (x<=mid) return query(L,l,mid,x);
		else return query(R,mid+1,r,x);
	}
}
void update(int k,int l,int r,int x,int y,int v,int to) {
	if (x<=l&&r<=y) {
		Node tmp = {v,to};
		t[k] = min(t[k],tmp);
		lazy[k] = min(lazy[k],tmp);
	}
	else {
		int mid = (l+r)/2;
		pushDown(k,l,r);
		if (x<=mid) update(L,l,mid,x,y,v,to);
		if (y>mid) update(R,mid+1,r,x,y,v,to);
		t[k] = min(t[L],t[R]);
	}
}
signed main() {
	int n;
	cin>>n;
	for (int i=1;i<=n;i++) {
		cin>>a[i];
	}
	for (int i=1;i<=n;i++) {
		cin>>b[i];
	}
	for (int i=0;i<maxn*4;i++) {
		lazy[i].val = t[i].val = INF;
	}
	update(1,0,n,n-a[n],n,1,n);
	for (int i=n-1;i>=1;i--) {
		int low = i+b[i];
		int f = query(1,0,n,i).val;
		update(1,0,n,low-a[low],low,f+1,i);
	}
	int ans = query(1,0,n,0).val;
	if (ans>=INF) cout<<-1;
	else {
		vi v;
		int now = 0;
		while (1) {
			v.push_back(now);
			if (now==n) break;
			now = query(1,0,n,now).to;
		}
		cout<<ans<<'\n';
		for (int i=v.size()-2;i>=0;i--) {
			cout<<v[i]<<" ";
		}
	}
}
```


---

## 作者：kirky_wang (赞：4)


### 做法

发现需要输出方案，考虑用广搜来做，如果跳到了一个位置 $j$ ，那么深度小于 $ j$
  的位置我们一定都已经在之前的跳跃过程中枚举过，也就是已经入队了，所以没有再次遍历一遍的需要。所以我们可以维护一个现在已经枚举到的最高位置，然后每次取出队首去扩展位置的时候，我们只需要枚举从之前的最高位置到这个点能到的最高位置即可，这样可以保证每个元素最多被入队一次，保证了时间复杂度为 $O(n)$ 。然后对于输出方案，用一种类似链表的方法输出即可。

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int qu[N*3],hea=1,tal=0;
int a[N],b[N],ans[N],pre[N],sp[N];
bool used[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int j=1;j<=n;j++)
		scanf("%d",&b[j]);
	used[n]=1;
	qu[++tal]=n;
	int mins=n;
	bool flag=0;
	while(hea<=tal){
		int j=qu[hea++];
		if(j-a[j]<=0){
			flag =1;
			printf("%d\n",ans[j]+1);
			vector<int> otp;
			int now=j;
			while(now!=n){
				otp.push_back(pre[now]);
				now=sp[now];
			}
			for(int i=otp.size()-1;i>=0;i--)
				printf("%d ",otp[i]);
			printf("%d\n",0);
			break;
		}
		for(int i=mins-1;i>=j-a[j];i--){
			if(used[i])
				continue;
			int dest=i+b[i];
			if(used[dest])
				continue;
			sp[dest]=j;
			used[dest]=1;
			pre[dest]=i;
			ans[dest]=ans[j]+1;
			qu[++tal]=dest;
		}
		mins=min(mins,j-a[j]);
	}
	if(!flag)
		cout<<"-1";
	return 0;
}
```



---

## 作者：方杰123 (赞：3)

## 思路
提供一种简单好想的 $O(n)$ 思路。
首先正常的想法枚举目前点每一种向上跳的方法，那么暴力 $BFS$ 即可，但是这样会超时。所以可以考虑优化，如图：


![](https://cdn.luogu.com.cn/upload/image_hosting/z3ie7dh7.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

浅蓝色方块是青蛙原本的位置，他能跳到绿色区间的点上，然后跳，再下滑到深蓝色方块的地方，此时他能跳到紫色的区间。我们发现青蛙紫色区间与第一次跳的绿色区间有大量重复，所以我们可以设置一个变量，记录一下青蛙历史最高访问区间在哪里，每次从历史最高点开始访问，同时维护一下历史最高点即可。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=6e5+10;
int read(){
	int x=0,f=1;char c=getchar();
	while(c>'9' || c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0' && c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,a[N],ans,b[N],dis[N],aim[N],from[N];
int lu[N],tot,rcd[N];
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read(),aim[i]=i+b[i];
	memset(dis,0x3f,sizeof(dis));
	dis[n]=0;int now=n;
	queue<int>q;
	q.push(n);
	while(!q.empty()){
		int u=q.front();q.pop();
		int l=u-a[u];
		if(l<=0){ans=dis[u]+1;from[0]=u;break;}
		for(int i=now-1;i>=l;i--){//now是历史最高点 
			if(dis[aim[i]]==0x3f3f3f3f){
				dis[aim[i]]=dis[u]+1;
				from[aim[i]]=u;//记录他来自哪里 
				rcd[aim[i]]=i;//记录他来自的地方下滑前在哪里 
				q.push(aim[i]);
			}
		}
		now=min(now,l);
	}
	
	if(ans==0){printf("-1");return 0;}
	else printf("%d\n",ans);
	//输出路径 
	tot=0;
	lu[++tot]=0;
	while(lu[tot]!=n){
		lu[tot+1]=from[lu[tot]];tot++;
	}
	for(int i=tot-1;i>=1;i--)printf("%d ",rcd[lu[i]]);
	return 0;
} v
```

---

## 作者：Arghariza (赞：2)

屯的题解不够用了……

思路很明显，将青蛙每次跳的状态表示出来，每个深度 $i$ 向 $i+b_i$ 连边，长度为 $0$，代表下滑的过程；每个 $i$ 如果向上跳的话，可以跳到深度 $[i-a_i,i]$，所以对这个深度所有的点连边，长度为 $1$。建完图后跑一个 $01\ \mathtt{bfs}$ 即可。

然后你发现这个点向区间连边的操作可以线段树优化建图，然后你搞上去就发现连样例都过不去。

因为题目很明确地说了，每跳一次就会下滑一次，然而我们建出来的图有可能让这只可怜的青蛙一直下滑。

换而言之，就是我们图建错了。

然后你仔细一想，发现每次青蛙移动包含两个过程：向上跳和向下滑。

于是你建一堆点放在左边，表示向上跳之后青蛙处在的点。

然后再来一堆点扔到右边，表示向下滑之后青蛙处在的点。

每次向上跳，右边的点往左边一堆点连边。

每次向下滑，左边的点向右边的点连边。

然后没了。

```cpp
const int maxn = 1e7 + 100;
const int inf = 1e9;
struct edge { int to, nxt, w; } e[maxn];
struct node { int u, w; };
int n, tot, cnt, rt, len, ans[maxn], a[maxn], b[maxn], head[maxn], id[maxn], ls[maxn], rs[maxn], dis[maxn], pr[maxn];

void add_edge(int u, int v, int w) {
	e[++cnt] = (edge) { v, head[u], w };
	head[u] = cnt;
}

void build(int l, int r, int &x) {
	x = ++tot;
	if (l == r) {
		add_edge(x, l, 0);
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, ls[x]);
	build(mid + 1, r, rs[x]);
	add_edge(x, ls[x], 0), add_edge(x, rs[x], 0);
}

void link(int l, int r, int s, int t, int c, int x) {
	if (s <= l && r <= t) {
		add_edge(c, x, 1);
		return;
	}
	int mid = (l + r) >> 1;
	if (s <= mid) link(l, mid, s, t, c, ls[x]);
	if (t > mid) link(mid + 1, r, s, t, c, rs[x]);
}

int main() {
	n = tot = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) b[i] = read();
	for (int i = 0; i <= n; i++) id[i] = ++tot;
	build(0, n, rt);
	for (int i = 1; i <= n; i++) add_edge(i, id[i + b[i]], 0);
	for (int i = 1; i <= n; i++) link(0, n, i - a[i], i, id[i], rt);
	fill(dis, dis + tot + 1, inf);
	dis[id[n]] = 0;
	deque<node> q;
	q.push_back((node) { id[n], 0 });
	while (!q.empty()) {
		node t = q.front(); q.pop_front();
		int u = t.u;
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (dis[v] > dis[u] + e[i].w) {
				pr[v] = u;
				dis[v] = min(dis[v], dis[u] + e[i].w);
				if (e[i].w) q.push_back((node) { v, dis[v] });
				else q.push_front((node) { v, dis[v] });
			}
		}
	}
	if (dis[0] == inf) return puts("-1");
	write(dis[0]), puts("");
	int u = 0;
	while (u != id[n]) {
		if (u <= n) ans[++len] = u;
		u = pr[u];
	}
	for (int i = len; i >= 1; i--) write(ans[i]), putchar(' ');
	return 0; 
}

```

---

## 作者：摸鱼酱 (赞：2)

可以冲一发 [线段树优化建图](https://www.moyujiang.com/982.html) 莽过去，但是太难写了。

考虑 bfs，每个点 $y$ 被跳上来，下滑 $b_y$ 米之前第一次到达就是最优的，所以每个点只会被搜到一次。

那么我们就可以把 $[0,n-1]$ 塞进 STL::set，每次把 $[u-a_u,u]$ 中还没被访问过的点拉出来更新并放入下滑后的点入队列，然后把它们删除掉，每个点只会贡献一次删除和入队，时间复杂度 $O(n\log n)$。

[code](https://codeforces.com/contest/1601/submission/133001541)。

---

## 作者：jun头吉吉 (赞：0)

## 题意
有一只 Frog 掉到了井底，井底的深度为 $n$，深度为 $0$ 则为跳出，小青蛙在深度为 $x$ 的地方可以向上跳 $[0,a_x]$ 的距离，跳过一次之后若在深度 $y$ 且没有跳出井，那么小青蛙会下滑 $b_y$ 的距离，问小青蛙最少跳几次并输出方案，无解输出 $-1$。

$1\le n\le 300\ 000$
## 题解
考虑现在是位置 $x$，跳一步可以到那些位置。如果可以直接跳出去就跳出去，否则先跳一下到 $[x-a_x,x]$ 再下滑。这个东西直接广搜复杂度是 $\mathcal O(n^2)$ 的。

所以我们不要枚举跳一步能到哪些位置，而是枚举跳一步再滑下来能到哪些位置。把 $(x,x+b_x)$ 当成一个二元组，就相当于询问二元组第一维在 $[x-a_x,x]$ 且第二维还没有被访问过的。用`set`维护这些二元组，如果广搜搜到了 $x$ 就把所有第二维为 $x$ 的给删掉。因为一共 $n$ 条边每条边最多访问一次就删掉所以复杂度是 $\mathcal O(n\log n)$。

输出方案可能稍微有点麻烦，因为我们现在广搜搜的是滑下来的位置。可以对每个位置维护两个值 $from_i$ 和 $lst_i$，分别表示从哪个位置滑下来和转移过来的点，输出方案也就不难了。

## 代码
```cpp
// Problem: B. Frog Traveler
// Contest: Codeforces - Codeforces Round #751 (Div. 1)
// URL: https://codeforces.com/contest/1601/problem/B
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define pb push_back
#define pc putchar
#define mp make_pair
#define fi first
#define se second
#define chkmx(a,b) ((a)=max((a),(b)))
#define chkmn(a,b) ((a)=min((a),(b)))
using namespace std;
template<typename T>
inline void read(T &x){x=0;char c=getchar();bool f=false;for(;!isdigit(c);c=getchar())f|=c=='-';for(;isdigit(c);c=getchar())x=x*10+c-'0';if(f)x=-x;}
template<typename T ,typename ...Arg>inline void read(T &x,Arg &...args){read(x);read(args...);}
template<typename T>inline void write(T x){if(x<0)putchar('-'),x=-x;if(x>=10)write(x/10);putchar(x%10+'0');}
//#define int long long
#define lc (x<<1)
#define rc (x<<1|1)
#define mid (l+r>>1)
typedef long long ll;
const int N=3e5+100;
int n,a[N],b[N];
vector<int>can[N];
set<pair<int,int>>st;
void add(int u){
	for(auto v:can[u])
		if(st.find(mp(v,u))!=st.end())
			st.erase(mp(v,u));
}
int lst[N],fr[N];
//lst是上一个点
//fr是上一个滑下来的点
signed main(){
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=n;i++)read(b[i]),can[i+b[i]].pb(i),st.insert(mp(i,i+b[i]));
	add(n);queue<int>q;q.push(n);
	while(q.size()){
		int u=q.front();q.pop();
		if(u-a[u]<=0){
			vector<int>ans;ans.pb(0);
			while(u!=n)ans.pb(fr[u]),u=lst[u];
			reverse(ans.begin(),ans.end());
			write(ans.size());pc('\n');
			for(auto x:ans)write(x),pc(' ');
			return 0;
		}
		int l=u-a[u],r=u;
		while(1){
			auto it=st.lower_bound(mp(l,0));
			if(it==st.end())break;
			if(it->first>r)break;
			fr[it->second]=it->first;
			lst[it->second]=u;q.push(it->second);
			add(it->second);
		}
	}
	puts("-1");
}
```

---

## 作者：一Iris一 (赞：0)

# 题目大意

有一只青蛙在 $n$，在点 $i$ 可以向上跳最多 $a[i]$ 的距离，跳完之后若在 $j$ 点，当前位置则会变为 $j+b[j]$

这个做法是 xmz 教给我的

# 题解

显然可以转化为一个图论问题，然后区间加边求单源最短路，需要 DS 优化建图。

但这个东西比较复杂，这里介绍一种简单的图论做法。

我们考虑我们上述问题的复杂度瓶颈是什么，就是在每个点都会扫一遍全部出边，这很有可能让复杂度退化到 $O(n^2)$。但考虑到这些点中有一些是我们已经扫过的，显然再遍历一遍肯定不如上一次的答案优秀，如果能够去掉这些点复杂度就能降下来。

观察可得，已经扫过的点肯定是呈现为一个区间，所以我们可以借用树上冰茶姬覆盖的想法来维护这个东西。

具体来说每个点维护一个冰茶姬，当扫过 $i$ 点之后，就将它的前驱 $i+1$ 和自己 $unite$ 起来，这样就可以很方便的维护出下一个未覆盖的点是谁。

我自己实现的时候冰茶姬似乎只能路径压缩，不能按秩合并。所以复杂度也只能做到 $O(n\log n)$

[代码](https://codeforces.com/contest/1601/submission/133240216)


---

