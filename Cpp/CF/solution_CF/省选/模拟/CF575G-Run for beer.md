# Run for beer

## 题目描述

People in BubbleLand like to drink beer. Little do you know, beer here is so good and strong that every time you drink it your speed goes 10 times slower than before you drank it.

Birko lives in city Beergrade, but wants to go to city Beerburg. You are given a road map of BubbleLand and you need to find the fastest way for him. When he starts his journey in Beergrade his speed is 1. When he comes to a new city he always tries a glass of local beer, which divides his speed by 10.

The question here is what the minimal time for him to reach Beerburg is. If there are several paths with the same minimal time, pick the one that has least roads on it. If there is still more than one path, pick any.

It is guaranteed that there will be at least one path from Beergrade to Beerburg.

## 样例 #1

### 输入

```
8 10
0 1 1
1 2 5
2 7 6
0 3 2
3 7 3
0 4 0
4 5 0
5 7 2
0 6 0
6 7 7
```

### 输出

```
32
3
0 3 7
```

# 题解

## 作者：快乐的大童 (赞：6)

## CF575G	Run for beer
默认编号从 $1$ 开始，与题面不同。

发掘性质。根据 $t=\frac{s}{v}$，由于速度每次变成原来的 $\frac{1}{10}$，经过每个单位长度用时变成原来的十倍。而 $0\le len\le 9$，这样我们就可以知道经过一条边等价于将当前用时的从左到右第一位的前面加上值为边权的数位，倒过来后就是从左往右填数位，能比较方便，所以我们选择倒着做，即从 $n$ 到 $1$。

先考虑如何满足首要限制“用时最短”。发现用时的位数和经过边的数量相同（特判前导 0），于是一个 bfs 处理出 `dep`，即从起点到每个点的最短距离，不计前导 0。对于前导 0，再进行一次 bfs 处理出每个点是否有从终点到当前点的一段 0 边。其次，在满足位数相同的前提下，要满足当前边权要小（贪心，对于位数相同的两个数，高位的数最大，数越大，这也是要倒着做的原因之一）。

再考虑如何满足次要限制“路径数量最少”。注意，此处不能忽略前导 0。进行一次 bfs 处理出 `num` 表示从终点到当前点的最短距离（此处只需要处理出有 0 边的部分即可，剩余部分以后会处理）。

最后，开始不断地去找路径。我们用一个 vector 记录当前的起点集合（即当前有可能会对答案有贡献的点），遍历这些起点的出边，寻找最小的 `dep` 值和边权。（优先级已在“用时最短”处提及）。这样，我们能找到下一次遍历有可能对答案有贡献的点，这样不断循环，直到找到起点，记录 `pre` 表示转移到当前点的点，不断递归找路径即可。时间复杂度 $O(n+m)$。

注意特判只经过 0 边就到达起点的情况。
## 代码
```cpp
#include<bits/stdc++.h>
#define P__ puts("")
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define per(a,b,c) for(int a=b;a>=c;a--)
#define graph(i,j,k,l) for(int i=k[j];i;i=l[i].nxt)
#define mem(x,y) memset(x,y,sizeof x);
using namespace std;
inline int rd(){
	int x=0,f=1;int ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}return x*f;
}
inline void write(int x,char ch='\0'){
	if(x<0){x=-x;putchar('-');}
	int y=0;char z[40];
	while(x||!y){z[y++]=x%10+48;x/=10;}
	while(y--)putchar(z[y]);if(ch!='\0')putchar(ch);
}
const int maxn=1e5+5,inf=0x7fffffff;
const bool TuKuaiEChouGuaFenJiWangJiaoFuSJN=true;
int n,m;
struct edge{
	int to,nxt,w;
}a[maxn<<1];
int head[maxn],edges;
void add(int x,int y,int z){
	a[++edges]=(edge){y,head[x],z};
	head[x]=edges;
}
int pre[maxn];
int dep[maxn],num[maxn];
void bfs0(int s){ 
	mem(num,63);num[s]=0;
	queue<int>q;q.push(s);
	while(!q.empty()){
		int now=q.front();q.pop();
		graph(i,now,head,a){
			int u=a[i].to;
			if(num[u]==0x3f3f3f3f){
				q.push(u);
				num[u]=num[now]+1;
			}
		}
	}
}
void bfs1(int s){
	mem(dep,63);queue<int>q;q.push(s);dep[s]=0;
	while(!q.empty()){
		int now=q.front();q.pop();
		graph(i,now,head,a){
			int u=a[i].to;
			if(dep[u]==0x3f3f3f3f){
				dep[u]=dep[now]+1;
				q.push(u);
			}
		}
	}
}
void bfs10(int s){
	queue<int>q;q.push(s);pre[s]=-1;
	while(!q.empty()){
		int now=q.front();q.pop();
		graph(i,now,head,a){
			int u=a[i].to;
			if(a[i].w) continue;
			if(!pre[u]) pre[u]=now,q.push(u);
		}
	}
}
vector<int>v,ans;
void bfs0x7fffffff(){
	while(TuKuaiEChouGuaFenJiWangJiaoFuSJN){ 
		pii res=mp(inf,inf);
		for(int x:v){
			graph(i,x,head,a){
				int u=a[i].to;
				if(dep[u]>dep[x]||(pre[u]&&num[pre[u]]<num[x])) continue;
				res=min(res,mp(dep[u],a[i].w));
			}
		}
		ans.push_back(res.second);
		vector<int>vv;
		for(int x:v){
			graph(i,x,head,a){
				int u=a[i].to;
				if(dep[u]>dep[x]||(pre[u]&&num[pre[u]]<num[x])) continue;
				if(dep[u]==res.first&&a[i].w==res.second)vv.push_back(u),pre[u]=x;
			}
		}
		for(int i:vv){
			if(i==1){
				for(int j:ans)write(j);P__;
				vector<int>path;int now=1;while(now!=-1)path.push_back(now),now=pre[now];
				write(path.size(),10);for(int j:path)write(j-1,32);
				return;
			}
		}
		v=vv;
	}
}
signed main(){
	n=rd(),m=rd();
	rep(i,1,m){
		int x=rd()+1,y=rd()+1,z=rd();
		add(x,y,z),add(y,x,z);
	}
	bfs0(n),bfs1(1),bfs10(n);
	if(pre[1]){ 
		puts("0");
		vector<int>path;int now=1;while(now!=-1)path.push_back(now),now=pre[now];
		write(path.size(),10);for(int j:path)write(j-1,32);
		return 0;
	}
	int mn=inf;rep(i,1,n)if(pre[i])mn=min(mn,dep[i]);
	rep(i,1,n)if(pre[i]&&mn==dep[i])v.push_back(i);
	bfs0x7fffffff();
}

```


---

## 作者：duyi (赞：5)

## 题解 CF575G Run for beer

### 题目大意

给定一张$n$个点$m$条边的无向图。节点标号为$0\dots n-1$。每条边连接两个节点$u_i,v_i$，有一个长度$w_i$。

你从$0$号节点出发，前往$n-1$号节点。初始时，速度为$1$。每经过一个节点（出发点不算），速度除以$10$。

求一条用时最短的路径。用时相同时，输出经过边数最少的路径。如果还有多条路径，输出任意一条。

数据范围：$1\leq n,m\leq 10^5$，$0\leq w_i\leq 9$。

### 本题题解

一条路径的总用时，就是每条边的用时之和。而一条边的用时，等于长度除以速度。我们可以把速度的变化，看成每走过一条边，所有边的长度都乘以$10$，然后求一条路程最短的路径。又因为$0\leq w_i\leq9$，我们每次乘以$10$，再加起来，可以看做得到一个十进制数！具体来说，我们把路径反一下，从$n-1$出发走向$0$，定义一条路径的长度是**经过的边权依次拼接得到的十进制数**（靠近$n-1$的是高位），问题转化为求这样定义下的最短路径。

因为把路径反过来了，所以以下称起点$s=n-1$，终点$t=0$。（别忘了最后输出答案时，按从“终点”到“起点”的顺序输出）。

考虑边权只有$1\dots 9$的情况。此时比较两条路径的长度，就是先比边数，然后比字典序。我们可以从$t$出发，做一遍bfs求出每个点到$t$的距离（这里“距离”指的是**最少边数**而不是“路径长度”，路径长度是那个大十进制数，我们存不下的），记为$d(u,t)$。

然后从$s$出发，每次贪心地，走向$d(u,t)$最小的前提下，入边边权最小的节点。当然，这样的节点可能不止一个：也就是有多个节点，两个关键字都相等。把这些可能的“下一个节点”，存在一个$\texttt{vector}$里，称为“一层”。然后每次从当前层的点，一起转移向下一层的点。也就是**逐层推出最优路径**。因为每层$d(u,t)$相等，且到下一层一定会恰好减少$1$，所以只会经过一个节点至多一次，复杂度是$O(n+m)$的。

再考虑边权有$0$的情况。这带来的问题是：“前导零”产生的边数，是不应该计入总边数里比较的。为了解决这个问题，我们需要**强行忽略前导零**。那么，可以从$s$出发，只走边权为$0$的边，把能走到的这些节点，作为起点。然后找出起点里，$d(u,t)$最小的（一些）点，以他们作为“第一层”，再逐层推出答案。

为了输出路径，我们在逐层递推时，给每个点记一个$\text{pre}[u]$，表示它是从哪里走过来的，即可。

此时还有一个小问题，就是题目要求，用时（也就是我们新定义的“路径长度”）相同的话，要输出边数最少的路径。这里的“边数”，就又**不能忽略**长度为$0$的边了。解决方法是，我们再预处理一个“起点到每个点的距离”：$d(s,u)$。在逐层推答案时，如果下一层的一个点$v$，能被本层的多个点$u_1,u_2,\dots ,u_k$转移到，则选择$d(s,u)$最小的点，作为$\text{pre}[v]$。

时间复杂度$O(n+m)$。

参考代码：

```cpp
//problem:
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

template<typename T>inline void ckmax(T& x,T y){x=(y>x?y:x);}
template<typename T>inline void ckmin(T& x,T y){x=(y<x?y:x);}

const int MAXN = 1e5;
const int INF = 1e9;

int n,m;

struct EDGE { int nxt,to,w; } edge[MAXN*2+5];
int head[MAXN+5],tot;
inline void add_edge(int u,int v,int w){ edge[++tot].nxt=head[u]; edge[tot].to=v; edge[tot].w=w; head[u]=tot; }

int dis_s[MAXN+5],dis_t[MAXN+5],pre[MAXN+5];
void solve(int s,int t) {
	for(int i=1; i<=n; ++i) {
		dis_t[i] = INF;
		dis_s[i] = INF;
	}
	dis_t[t]=0;
	queue<int>q;
	q.push(t);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int i=head[u]; i; i=edge[i].nxt) {
			int v = edge[i].to;
			if(dis_t[v] > dis_t[u]+1) {
				dis_t[v] = dis_t[u]+1;
				q.push(v);
			}
		}
	}
	dis_s[s] = 0;
	q.push(s);
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int i=head[u]; i; i=edge[i].nxt) {
			int v = edge[i].to;
			if(dis_s[v] > dis_s[u]+1) {
				dis_s[v] = dis_s[u]+1;
				q.push(v);
			}
		}
	}
	
	q.push(s); pre[s]=n+1;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int i=head[u]; i; i=edge[i].nxt) {
			if(edge[i].w) continue;
			int v = edge[i].to;
			if(!pre[v]) {
				pre[v] = u;
				q.push(v);
			}
		}
	}
	if(pre[t]) {
		cout << 0 << endl;
		int u = t;
		vector<int>ans;
		while(1) {
			ans.pb(u);
			if(u == s)
				break;
			u = pre[u];
		}
		cout << SZ(ans) << endl;
		for(int i=0; i<SZ(ans); ++i)
			cout << ans[i]-1 << " ";
		cout << endl;
		return;
	}
	int start_dis = INF;
	for(int i=1;i<=n;++i)
		if(pre[i]){
			ckmin(start_dis,dis_t[i]);
		}
	vector<int>vec;
	for(int i=1;i<=n;++i)
		if(pre[i] && dis_t[i] == start_dis){
			vec.push_back(i);
		}
	//for(int i=1;i<=n;++i)
	//	cout<<dis_t[i]<<" ";
	//cout<<endl;
	vector<int>path;
	while(1){
		//cout<<"****"<<endl;
		//for(int i=0;i<SZ(vec);++i)
		//	cout<<vec[i]<<" ";
		//cout<<endl;
		pii cur_best=mk(INF,INF);
		for(int i=0;i<SZ(vec);++i){
			int u=vec[i];
			for(int j=head[u];j;j=edge[j].nxt){
				int v=edge[j].to;
				if(dis_t[v] > dis_t[u]) continue;
				if(pre[v] && dis_s[pre[v]]<dis_s[u])
					continue;
				ckmin(cur_best,mk(dis_t[v],edge[j].w));
			}
		}
		assert(cur_best.fi!=INF);
		path.push_back(cur_best.se);
		vector<int>nxt_vec;
		for(int i=0;i<SZ(vec);++i){
			int u=vec[i];
			for(int j=head[u];j;j=edge[j].nxt){
				int v=edge[j].to;
				if(dis_t[v] > dis_t[u]) continue;
				if(pre[v] && dis_s[pre[v]]<dis_s[u])
					continue;
				if(dis_t[v]==cur_best.fi && edge[j].w==cur_best.se){
					nxt_vec.push_back(v);
					pre[v] = u;
				}
			}
		}
		for(int i=0;i<SZ(nxt_vec);++i){
			int u=nxt_vec[i];
			if(u == t){
				for(int j=0;j<SZ(path);++j)
					cout<<path[j];
				cout<<endl;
				vector<int>ans;
				while(1){
					ans.pb(u);
					if(u==s) break;
					u=pre[u];
				}
				cout<<SZ(ans)<<endl;
				for(int j=0;j<SZ(ans);++j)
					cout<<ans[j]-1<<" ";
				cout<<endl;
				return;
			}
		}
		vec=nxt_vec;
	}
}
int main() {
	cin>>n>>m;
	for(int i=1; i<=m; ++i) {
		int u,v,w; cin>>u>>v>>w; ++u; ++v;
		add_edge(u,v,w); add_edge(v,u,w);
	}
	int s=n,t=1;
	solve(s,t);
	return 0;
}
```







---

## 作者：EasonLiang (赞：3)

**[CF575G Run for beer](https://www.luogu.com.cn/problem/CF575G)**

作为一个做过 [CF464E](https://www.luogu.com.cn/problem/CF464E) 的人，见到这题怎么能没有用主席树维护跑最短路的冲动？

注意到本题的最短路转移的一个性质：每走过一条边，之后所用的时间都要乘以 $10$。我们不妨反过来考虑，即从终点出发走到起点，每经过一条边，就将当前所用时间乘以 $10$，再加上这条边的权值。

不难发现，这是很好用线段树维护的。多走一条边，实际上相当于在原来所用时间的十进制表示后，直接添加一个数位，而这个过程恰好可以通过线段树的单点修改实现。

然而有一个问题：假设我们已经知道起点到 $u$ 的最短路 $dis_u$，它的每一条出边 $(u, v)$ 都需要进行转移。直接在原来的线段树上修改，就没有办法重复使用 $dis_u$ 了；但复制一个新的线段树，时间、空间开销又都太大。聪明的你想必已经知道应该怎么办了：用主席树维护这个过程，只要新开少量的节点就可以完成转移。

由于一条最短路至多经过 $m$ 条边，所用时间的十进制表示最多只有 $m$ 位。因此转移的时间复杂度是 $O(\log(m))$ 的。

如何比较两个数值的大小？首先我们需要维护每个数值十进制表示的长度（忽略前导零），若长度不同则直接得出结果；若长度相同，则通过哈希 + 线段树二分，找到两个数首个不同的位置进行比较。这个过程也是 $O(\log(m))$ 的。

知道怎么维护最短路以后，我们就可以直接跑 Dijkstra 了。

计算一下复杂度：单次比较和转移的复杂度为 $O(\log m)$，所以套上 Dijkstra 以后，总的时间复杂度就是 $O(m \log^2 m)$；转移的次数总共为 $O(m)$，因此空间复杂度为 $O(m \log m)$，250MB 绰绰有余。

其实笔者最开始是从 $0$ 到 $n - 1$ 正着跑最短路的，后来 WA 得惨不忍睹。正着跑不正确的原因大概是因为不满足最优子结构：

> 从起点 $s$ 走到当前节点 $u$ 所用时间最短的方案 A，从全局来看不一定是最优的；考虑另一种方案 B，走到 $u$ 所用时间比方案 A 更长，但路径长度比方案 A 更短。  
> 此时若 $u$ 到终点 $t$ 的路径出现非零权值边，方案 B 会相较方案 A 更优。

由于 Dijkstra 的本质是贪心 + DP，不满足 DP 前提条件的做法自然是无法得出正确答案的。

最后附上蒟蒻惨不忍睹的代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn = 1e5 + 20, maxm = 1e5 + 20;
int n, m;

#define mid ((l + r) >> 1)

const int maxcnt = 5e6 + 20;
const ll mod = 1e9 + 7, base[2] = {11451, 13331};
int cnt, num, rt[2 * maxm], siz[2 * maxm];
int ls[maxcnt], rs[maxcnt];
ll hval[maxcnt][2];

void modify (int u, int v) {
	hval[u][0] = hval[u][1] = v;
}

void modify (int &u, int l, int r, int p, int v) {
	int pu = u; u = ++cnt; ls[u] = ls[pu]; rs[u] = rs[pu];
	hval[u][0] = hval[pu][0]; hval[u][1] = hval[pu][1];
	if (l == r) return modify (u, v);
	if (p <= mid) modify (ls[u], l, mid, p, v);
	else modify (rs[u], mid + 1, r, p, v);
	hval[u][0] = (hval[ls[u]][0] * base[0] + hval[rs[u]][0]) % mod;
	hval[u][1] = (hval[ls[u]][1] * base[1] + hval[rs[u]][1]) % mod;
}

void print (int u, int l, int r, int p) {
	if (p < l) return;
	if (l == r) return putchar (hval[u][0] | 48), void ();
	print (ls[u], l, mid, p); print (rs[u], mid + 1, r, p);
}

bool cmp (int lhs, int rhs, int l, int r) {
	if (l == r) return hval[lhs][0] < hval[rhs][0];
	return
		hval[ls[lhs]][0] != hval[ls[rhs]][0] ||
		hval[ls[lhs]][1] != hval[ls[rhs]][1] ?
		cmp (ls[lhs], ls[rhs], l, mid) :
		cmp (rs[lhs], rs[rhs], mid + 1, r);
}

bool cmp (int lhs, int rhs) {
	if (!~lhs && !~rhs) return 0;
	if (!~lhs || !~rhs) return ~lhs;
	if (siz[lhs] != siz[rhs])
		return siz[lhs] < siz[rhs];
	return cmp (rt[lhs], rt[rhs], 1, m);
}

#undef mid

int dis[maxn], len[maxn], pre[maxn];
bool vis[maxn];

struct To {
	int v, w;
	
	To (int v, int w):
		v (v), w (w) {}
};

vector<To> g[maxn];

struct Node {
	int u, d, l;
	
	Node (int u, int d, int l):
		u (u), d (d), l (l) {}
	
	bool operator< (const Node &oth) const {
		bool f[2] = {cmp (d, oth.d), cmp (oth.d, d)};
		return f[0] != f[1] ? f[1] : l > oth.l;
	}
};

priority_queue<Node> q;

int main () {
	scanf ("%d%d", &n, &m);
	
	for (int i = 1, u, v, w; i <= m; ++i) {
		scanf ("%d%d%d", &u, &v, &w);
		g[u].emplace_back (v, w);
		g[v].emplace_back (u, w);
	}
	
	memset (dis, ~0, sizeof (dis));
	q.emplace (n - 1, dis[n - 1] = 0, 0);
	
	while (!q.empty ()) {
		auto item = q.top (); q.pop ();
		
		if (vis[item.u]) continue;
		vis[item.u] = 1;
		
		int u = item.u, d = item.d, l = item.l + 1;
		
		for (auto nxt : g[u]) {
			int nd = ++num; rt[nd] = rt[d]; siz[nd] = siz[d];
			
			if (siz[nd] || nxt.w)
				modify (rt[nd], 1, m, ++siz[nd], nxt.w);

			bool f[2] = {cmp (nd, dis[nxt.v]), cmp (dis[nxt.v], nd)};

			if (f[0] || (!f[1] && l < len[nxt.v]))
				pre[nxt.v] = u,
				q.emplace (nxt.v, dis[nxt.v] = nd, len[nxt.v] = l);
		}
	}
	
	int u = 0;
	
	if (siz[dis[u]])
		print (rt[dis[u]], 1, m, siz[dis[u]]);
	else putchar ('0');
	
	printf ("\n%d\n0", len[u] + 1);
	
	while (u != n - 1)
		printf (" %d", u = pre[u]);
	
	puts ("");
	
	return 0;
}
```

---

## 作者：_edge_ (赞：3)

头一回做出这样的题目，~~(虽然有一部分还是看数据才能调出来)~~


题意讲得稍微有点偏差，这里重新描述一下，题意就是给你一张无向图，然后图上求一条路径，这条路径是从 $1$ 到 $n$，然后需要满足这条路径边权从右到左拼出来的十进制数最小，前导零忽略。

看到这种题目，我们就要想到如何去比较两个数的大小，显然我们先是比较两个数的位数，然后再从高位到低位进行比较，如果有一位出现偏差，那么就是可以判断大小。

这道题目也是同理，发现边权只有 $[0,9]$ 那意味着我们每走一条路就会多一个数，**前导零在这里先忽略**。

然后我们想让它位数尽可能小，那么肯定是走将边权视为 $1$ 的最短路径。

当然，这样的最短路径可不止一条，这时候我们就需要把这些最短路径都拿出来。

拿出来之后，可以发现它本质上是一个 DAG，然后我们这时候从 $n$ 开始跑，每次走尽可能小边权的路。

这样子的话，每次可以拿出同一位的候选点，然后扩展下一批候选点，每个点每条边只会被扩展一次，总时间复杂度 $O(n+m)$。

但是但是，我们这里发现一个特别特别棘手的问题，就是前导零，在这里，前导零不会被算进位数，那么我们先要从 $1$ 开始跑，跑全都是 $0$ 边权的边，这样才能避免这些问题，但是这样处理起来就非常的麻烦。

需要注意的是，如果两个数大小相同，那么他们走的点要尽可能少。

如果你 Wrong Answer on test 2，那么请尝试这组数据：

```
7 7
0 1 3
1 2 4
2 3 0
3 4 9
4 5 8
5 6 0
3 3 1 

```

```
89043
7
0 1 2 3 4 5 6
```

如果你 Wrong Answer on test 9，请尝试这组数据：

```
5 5
0 4 9
0 1 0
1 2 0
2 3 0
3 4 0
```

```
0
5
0 1 2 3 4
```

```cpp
const int INF=3e5+5;
struct _node_edge{
	int to_,next_,disv_;
}edge[INF<<1];
int head[INF],tot;
void add_edge(int x,int y,int z) {
	edge[++tot]=(_node_edge){y,head[x],z};
	head[x]=tot;return ;
}
int n,m,vis[INF],dis_[INF],aa[INF],pre[INF],ll[INF];
queue <int> q;
void BFS(int s) {
	memset(dis_,63,sizeof dis_);
	q.push(s);dis_[s]=0;
	while (q.size()) {
		int x=q.front();q.pop();
		vis[x]=0;
		for (int i=head[x];i;i=edge[i].next_) {
			int v=edge[i].to_;
			if (dis_[v]>dis_[x]+1) {
				dis_[v]=dis_[x]+1;
				if (!vis[v]) 
					q.push(v),vis[v]=1;
			}
		}
	}
	return ;
}
void print(int x) {
	if (x==0) return ;
	cout<<x-1<<" ";
	print(pre[x]);
}
queue <int> q1;
void SPFA(int s) {
	memset(vis,0,sizeof vis);
	int T=55;
	q1.push(s);
	while (q1.size()) {
		int x=q1.front();q1.pop();q.push(x);vis[x]=1;
		for (int i=head[x];i;i=edge[i].next_) {
			int v=edge[i].to_,d=edge[i].disv_;
			if (d || vis[v]) continue;
//			cout<<v<<" "<<x<<" aweirjiwejr\n";
			if (!vis[v]) q1.push(v),vis[v]=1,ll[v]=ll[x]+1;pre[v]=x;
		}
	}
	if (vis[1]) aa[++aa[0]]=0;
	while (q.size() && !vis[1]) {
		int x=q.front();int Min=1e9,Minv=9,Mind=1e9;
//		cout<<x<<" ???\n"; 
		if (x==1) break;
		vector <int> v;
		while (q.size()) {
			int x=q.front();q.pop();
			for (int i=head[x];i;i=edge[i].next_) {
				int v=edge[i].to_,d=edge[i].disv_;
//				cout<<v<<" "<<x<<" "<<vis[v]<<" sdfwer?\n";
				if (vis[v]) continue;
				if (Min>dis_[v]) Min=dis_[v],Minv=d,Mind=ll[x];
				else if (Min==dis_[v] && Minv>d) Minv=d,Mind=ll[x];
				else if (Min==dis_[v] && Minv==d && Mind>ll[x]) Mind=ll[x];
			}
			v.push_back(x);
		}
		aa[++aa[0]]=Minv;
		for (int x:v) {
			for (int i=head[x];i;i=edge[i].next_) {
				int v=edge[i].to_,d=edge[i].disv_;
				if (vis[v]) continue;
//				cout<<v<<" aeoiiajefioj\n";
//				if (d==0 && x==s) continue;
				if (Min==dis_[v] && Minv==d && Mind==ll[x]) 
					ll[v]=ll[x],q.push(v),pre[v]=x;
			}
		}
	}
	int la=0;
	while (aa[la+1]==0 && la+1<aa[0]) la++;
	for (int i=la+1;i<=aa[0];i++) cout<<aa[i];
	cout<<"\n";
	if (vis[1]) ll[1]--;
	cout<<aa[0]+1+ll[1]<<"\n";
	print(1);
//	for (int i=aa[0];i;i--) cout<<aa[i];
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=m;i++) {
		int x=0,y=0,z=0;cin>>x>>y>>z;
		x++;y++;add_edge(x,y,z);add_edge(y,x,z);
	}
	BFS(1);
	SPFA(n);
	return 0;
}
```


---

## 作者：duanyll (赞：2)

[更好的阅读体验](https://duanyll.com/2019/10/03/Codeforces-575G.html)

## 题意

$n$个点$m$条边的带权图, 求$0$到$n-1$的最小权值且最小长度的路径, 权值为把路径经过的边的权从终点到起点往依次写下组成的十进制数, $0\leq w_i\leq9$.

## 思路

先把到终点距离为$0$的点预处理出来, 然后从多起点开始跑字典序最小最短路(分层BFS).

## 代码

```cpp
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

#include <cctype>
#include <cstdio>

template <typename T = int>
inline T read() {
    T X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch)) {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch)) {
        X = (X << 3) + (X << 1) + (ch ^ 48);
        ch = getchar();
    }
    return w ? -X : X;
}

template <typename T>
inline void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

class lfs {
   public:
    lfs(int N) {
        memset(head, -1, sizeof head);
        ecnt = 0;
        n = N;
    }
    void adde(int from, int to, int w) {
        e[ecnt].to = to;
        e[ecnt].w = w;
        e[ecnt].next = head[from];
        head[from] = ecnt++;
    }
    void addde(int a, int b, int w) {
        adde(a, b, w);
        adde(b, a, w);
    }

    void solve() {
        vector<int> bfs_order;
        memset(dis, INF, sizeof dis);
        dis[0] = 0;
        bfs_order.push_back(0); 
        int cur = 0; // bfs队列不用pop, 空间换时间
        while (cur < bfs_order.size()) {
            int u = bfs_order[cur];
            for (int i = head[u]; i != -1; i = e[i].next) {
                int v = e[i].to;
                if (dis[v] == INF) {
                    dis[v] = dis[u] + 1;
                    bfs_order.push_back(v);
                }
            }
            cur++;
        }

        vector<int> end_point;
        end_point.push_back(n - 1);
        memset(vis, false, sizeof vis);
        memset(pre, 0, sizeof pre);
        vis[n - 1] = true;
        cur = 0;
        int mindis = dis[n - 1];
        while (cur < end_point.size()) {
            int u = end_point[cur];
            for (int i = head[u]; i != -1; i = e[i].next) {
                int v = e[i].to;
                if (e[i].w == 0 && !vis[v]) {
                    end_point.push_back(v);
                    pre[v] = u;  // 实际顺序是反的
                    vis[v] = true;
                    mindis = min(mindis, dis[v]);
                }
            }
            cur++;
        }

        bool leading_zeros = true;  // 当前bfs是否还在前导零中
        for (int l = mindis; l > 0; l--) {
            int now = INF;
            vector<int> next_point;
            for (auto& u : end_point) {
                for (int i = head[u]; i != -1; i = e[i].next) {
                    int v = e[i].to;
                    if (dis[v] + 1 == l) {
                        now = min(now, e[i].w);
                    }
                }
            }

            if (now != 0) leading_zeros = false;
            if (l == 1 || !leading_zeros) cout << now;

            for (auto& u : end_point) {
                for (int i = head[u]; i != -1; i = e[i].next) {
                    int v = e[i].to;
                    if (dis[v] + 1 == l && e[i].w == now && !vis[v]) {
                        vis[v] = true;
                        next_point.push_back(v);
                        pre[v] = u;
                    }
                }
            }
            end_point = next_point;
        }
        if (leading_zeros) cout << 0; // 都是0的情况
        cout << endl;
        vector<int> path;
        int u = 0;
        path.push_back(u);
        while (u != n - 1) {
            u = pre[u];
            path.push_back(u);
        }
        cout << path.size() << endl;
        for (auto& i : path) {
            cout << i << ' ';
        }
        cout << endl;
    }


   protected:
    struct Edge {
        int to, next, w;
    } e[MAXN * 2];
    int head[MAXN];
    int ecnt;
    int n;

    int dis[MAXN];
    bool vis[MAXN];
    int pre[MAXN];
};

int main() {
    int n = read();
    int m = read();
    auto graph = new lfs(n);
    for (int i = 1; i <= m; i++) {
        int u = read();
        int v = read();
        int w = read();
        graph->addde(u, v, w);
    }
    graph->solve();
}
```

---

## 作者：_ajthreac_ (赞：1)

这道题难度不大，只要理解了题意就可以直接 BFS 解决。不过有很多细节需要注意：

1. 注意前导零的处理，可以从终点再 BFS 一遍，看只走边权为 $0$ 的边能到哪些点；
2. 时间相同时要取边数最少的，可以记录方案时判断一下；
3. 题目给的编号从 $0$ 开始。

这里放上比较混乱的代码，仅供参考。

```cpp
const int N=100010;
int n,m;
struct Edge {
  int to,nxt,w;
}e[N<<1];
int hd[N],cn;
il void ade(int u,int v,int w){
  e[++cn].to=v,e[cn].w=w,e[cn].nxt=hd[u],hd[u]=cn;
}
int dis[N],mn[N],frm[N],lst[N],dn[N];bool vis[N];
int main(){
  Read(n),Read(m);
  for(int i=1,u,v,w;i<=m;i++){
    Read(u),Read(v),Read(w),u++,v++;
    ade(u,v,w),ade(v,u,w);
  }
  queue<int> q;memset(dis,0x3f,sizeof dis);
  q.push(1),dis[1]=0,vis[1]=1;
  while(!q.empty()){
    int u=q.front();q.pop();
    for(int i=hd[u];i;i=e[i].nxt){
      int v=e[i].to;
      if(!vis[v])dis[v]=dis[u]+1,q.push(v),vis[v]=1;
    }
  }
  memset(vis,0,sizeof vis);
  memset(dn,0x3f,sizeof dn);
  q.push(n),vis[n]=1,dn[n]=0;vector<int> zr;
  while(!q.empty()){
    int u=q.front();q.pop();
    for(int i=hd[u];i;i=e[i].nxt){
      if(e[i].w)continue;
      int v=e[i].to;
      if(!vis[v]){
        dn[v]=dn[u]+1;
        vis[v]=1,q.push(v),lst[v]=u,zr.pub(v);
      }
    }
  }
  zr.pub(n);
  int res=dis[n];set<int> p;
  for(int i:zr){//要保证权值最小
    if(dis[i]<res)res=dis[i],p.clear();
    if(dis[i]==res)p.insert(i);
  }
  set<int> tmp;
  for(int o=1;o<=res;o++){
    int mn=INF;
    for(int u:p){
      for(int i=hd[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(dis[v]+1!=dis[u])continue;
        if(e[i].w<mn)mn=e[i].w,tmp.clear();
        if(e[i].w==mn){
          if(tmp.find(v)!=tmp.end()){//要保证边数最少
            if(dn[v]>dn[u]+1)dn[v]=dn[u]+1,frm[v]=u;
          }else {
            tmp.insert(v),dn[v]=dn[u]+1,frm[v]=u;
          }
        }
      }
    }
    putchar(mn+48);
    swap(p,tmp),tmp.clear();
  }
  if(!res)putchar(48);
  puts("");vector<int> st;int u,cnt;
  //分别加入非零段和前导零
  for(u=1,cnt=1;cnt<=res;cnt++,u=frm[u])st.pub(u);
  for(;u!=n;u=lst[u])st.pub(u);st.pub(n);
  printf("%d\n",(int)st.size());
  for(int i:st)printf("%d ",i-1);
  KafuuChino HotoKokoa
}
```

---

## 作者：2023lpx (赞：0)

# CF575G Run for beer 题解

十年前的紫题。

编号默认从 $1$ 开始，便于理解。

发现 $0 \le w \le 9$，每走一步速度为上一次的 $\frac{1}{10}$，显然最后的序列为 $\overline{w_{h}w_{h-1}w_{h-2}w_{2}w_{1}}$。

先考虑用时最短。

显然，走的步数越少，用时越短。

但是要考虑有前导零的情况。

我们将 $n$ 点能只通过走 $w=0$ 的边所能到的点标记起来，过滤掉到 $1$ 点的距离不是最短的。

接着贪心从留下来的点想 $1$ 点跑，优先选边最小的。

如果跑到 $1$ 点时有多条路径，选取实际距离最少的。

求最短路径用 bfs 或 dij 均可。

我用的 dij，时间复杂度 $O(n \log n+n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n,m;
int const maxn=100000;
struct To{
	int to;
	int lst;
	int w;
}to[maxn*2+1];
int head[maxn+1];
int cnt;
inline void add(int u,int v,int w){
	cnt++;
	to[cnt].to=v;
	to[cnt].lst=head[u];
	to[cnt].w=w;
	head[u]=cnt;
}
int const inf=1000000000+7;
int jl[maxn+1];
int jll[maxn+1];
priority_queue<pair<int,int>>q;
int dis[maxn+1];
int vis[maxn+1];
void dij(int s){
	for(int i=1;i<=n;i++){
		dis[i]=inf;
		vis[i]=0;
	}
	dis[s]=0;
	q.push({0,s});
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		if(vis[u]){
			continue;
		}
		vis[u]=1;
		for(int i=head[u];i;i=to[i].lst){
			int v=to[i].to;
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				q.push({-dis[v],v});
			}
		}
	}
	for(int i=1;i<=n;i++){
		jl[i]=dis[i];
	}
}
void init(){
	int s=n;
	for(int i=1;i<=n;i++){
		dis[i]=inf;
		vis[i]=0;
	}
	dis[s]=0;
	q.push({0,s});
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		if(vis[u]){
			continue;
		}
		vis[u]=1;
		for(int i=head[u];i;i=to[i].lst){
			if(to[i].w!=0){
				continue;
			}
			int v=to[i].to;
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				q.push({-dis[v],v});
			}
		}
		
	}
	
	for(int i=1;i<=n;i++){
		jll[i]=dis[i];
	}
	int minn=inf;
	for(int u=1;u<=n;u++){
		if(jll[u]==inf){
			continue;
		}
		minn=min(minn,jl[u]);
	}
	for(int u=1;u<=n;u++){
		if(jll[u]==inf){
			continue;
		}
		jl[u]=minn;
	}
}
struct ABC{
	int a,b,c;
};
queue<ABC>s[2];
int use[maxn+1];
int from[maxn+1];
int ue[maxn+1];
queue<int>g;
void find(){
	g.push(n);
	while(!g.empty()){
		int u=g.front();
		g.pop();
		int k=0;
		use[u]=1;
		for(int i=head[u];i;i=to[i].lst){
			if(to[i].w==0&&use[to[i].to]==0){
				use[to[i].to]=1;
				g.push(to[i].to);
				from[to[i].to]=u;
			}
			if(to[i].w!=0){
				k=1;
			}
		}
		if(k==1&&ue[u]==0){
			ue[u]=1;
			s[1].push({u,jll[u]+jl[u],from[u]});
		}
	}
}
int best[maxn+1];
void bfs(){
	for(int i=1;i<=n;i++){
		best[i]=inf;
	}
	for(int t=1;t<=jl[n];t++){
		int g=t&1;
		int gg=g^1;
		int minn=inf;
		while(!s[gg].empty()){
			s[gg].pop();
		}
		while(!s[g].empty()){
			ABC u=s[g].front();
			s[g].pop();
			if(best[u.a]<=u.b){
				continue;
			}
			best[u.a]=u.b;
			from[u.a]=u.c;
			for(int i=head[u.a];i;i=to[i].lst){
				if(jl[to[i].to]!=jl[u.a]-1){
					continue;
				}
				if(to[i].w<minn){
					while(!s[gg].empty()){
						s[gg].pop();
					}
					minn=to[i].w;
					s[gg].push({to[i].to,u.b,u.a});
				}
				else if(to[i].w==minn){
					s[gg].push({to[i].to,u.b,u.a});
				}
			}
		}
		printf("%d",minn);
	}
	if(jl[n]==0){
		printf("0\n");
		int p=0;
		for(int i=1;i!=n;i=from[i]){
			p++;
		}
		printf("%d\n",p+1);
	}
	else{
		printf("\n");
		int g=(jl[n]&1)^1;
		int ans=inf;
		while(!s[g].empty()){
			if(s[g].front().b<ans){
				ans=s[g].front().b;
				from[1]=s[g].front().c;
			}
			s[g].pop();
		}
		printf("%d\n",ans+1);
	}
	for(int i=1;i!=n;i=from[i]){
		printf("%d ",i-1);
	}
	printf("%d",n-1);
}
signed main(){
	scanf("%d%d",&n,&m);
	int u,v,w;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		u++;
		v++;
		add(u,v,w);
		add(v,u,w);
	}
	dij(1);
	init();
	find();
	bfs();
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
很有意思的题，~~但是我读入都能写错~~。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
（下面的叙述中点编号从 $1$ 开始。）

首先先转化一步题意，速度变成 $\frac{1}{10}$ 显然非常难做。

考虑走了 $k$ 步后走过一条边权为 $w$ 的边的时间即为 $w\times10^k$，发现边权只有 $0\sim9$，就可以直接把一条路径的边权压为一个整数。

也就是我们设从 $1$ 走到 $u$ 需要的时间为 $t$，$u\rightarrow v$ 的边权为 $w$，那么从 $1$ 走到 $v$ 的时间即为 $\overline{wt}$。

接着考虑怎么做。

对于两个大整数 $x,y$ 比大小，假设不存在前导 $0$，那么必然是：
1. 优先对比 $x,y$ 的位数，位数更少的更小。
2. 如果相同再对比其一位位的数字大小。

那么我们就可以通过先一次从 $1$ 开始的 bfs 处理出经过边数，也就是数字位数。

接着考虑如何实现比较过程中的 $2$ 以及处理前导 $0$。

对于前导 $0$，考虑其是最后加上去的，所以倒序整个过程，从 $n$ 开始往 $1$ 号节点跑，那么最开始走过的 $0$ 边都为前导 $0$。

接着是对于如何对比一位位的数字大小。

首先根据预处理，我们已经知道了 $1$ 走到 $x$ 的数字位数，显然的是在不考虑前导 $0$ 的情况下，位数更多的严格不优。

接着因为倒序跑，所以我们的数字位数是从前到后填的，也就是可以贪心的选择数字，每次选最小即可。

最后如果这两个条件都相同，就找最短路径长度，即为最少前导 $0$。

具体实现的时候因为出发点很多，所以要全部都跑一边然后跑第二遍存下转移点。

对于输出，每次存下走的边权输出即可。

**注意特判 $1$ 与 $n$ 间存在全 $0$ 路径的情况。**
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,mod=998244353,INF=0x3f3f3f3f3f3f3f3f,lim=20;
int n,m,tot,d[N],mp[N],a[N],l[N],f[N];vector<pair<int,int>>e[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='A'&&c<='Z'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void bfs(int s)
{
    queue<int>q;q.push(s);memset(d,0x3f,sizeof d);d[s]=0;
    while(!q.empty())
    {
        auto u=q.front();q.pop();mp[u]=1;
        for(auto [v,w]:e[u])
            if(d[v]>d[u]+1)
            {
                d[v]=d[u]+1;
                if(!mp[v]) mp[v]=1,q.push(v);
            }
    }
}
inline void putf(int u){if(!u) return;print(u-1),put(' ');putf(f[u]);}
inline void solve(int s)
{
    memset(mp,0,sizeof mp);queue<int> q;q.push(s);vector<int>ss;
    while(!q.empty())
    {
        auto u=q.front();q.pop();mp[u]=1;ss.emplace_back(u);
        for(auto [v,w]:e[u])
        {
            if(w||mp[v]) continue;f[v]=u;
            if(!mp[v]) q.push(v),mp[v]=1,l[v]=l[u]+1;
        }
    }
    if(mp[1]) a[++tot]=0;for(auto u:ss) q.push(u);
    while(!q.empty()&&!mp[1])
    {
        int md=INF,mw=INF,m0=INF;if(q.front()==1) break;vector<int> nxt;
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(auto [v,w]:e[u])
            {
                if(mp[v]) continue;
                if(md>d[v]) md=d[v],mw=w,m0=l[u];
                else if(md==d[v]&&mw>w) mw=w,m0=l[u];
                else if(md==d[v]&&mw==w&&m0>l[u]) m0=l[u];
            }
            nxt.emplace_back(u);
        }a[++tot]=mw;
        for(int u:nxt)
            for(auto [v,w]:e[u])
            {
                if(mp[v]) continue;
                if(md==d[v]&&mw==w&&m0==l[u]) l[v]=l[u],q.push(v),f[v]=u;
            }
    }
    int st=0;while(!a[st+1]&&st+1<tot) st++;
    for(int i=st+1;i<=tot;i++) print(a[i]);
    put('\n');print(tot+1+l[1]-mp[1]),put('\n');
    putf(1);
}
signed main()
{
    n=read(),m=read();
    for(int i=1,u,v,w;i<=m;i++) u=read()+1,v=read()+1,w=read(),e[u].push_back({v,w}),e[v].push_back({u,w});
    bfs(1);solve(n);
    genshin:;flush();return 0;
}
```

---

