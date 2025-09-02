# [ABC233F] Swap and Sort

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc233/tasks/abc233_f

$ (1,2,\ldots,N) $ を並び替えた長さ $ N $ の順列 $ P=(P_1,P_2,\ldots,P_N) $ があります。

あなたが可能な操作は $ M $ 種類あり、操作 $ i $ は「 $ P $ の $ a_i $ 番目の要素と $ P $ の $ b_i $ 番目の要素を入れ替える」というものです。

操作を好きな順序で、合計 $ 5\times\ 10^5 $ 回以下行うことによって、$ P $ を昇順に並び替えることはできますか？

できるならば、操作手順を $ 1 $ つ教えてください。できないならばその旨を伝えてください。

## 说明/提示

### 制約

- $ 2\leq\ N\ \leq\ 1000 $
- $ P $ は $ (1,2,\ldots,N) $ を並び替えた順列
- $ 1\leq\ M\ \leq\ \min(2\times\ 10^5,\ \frac{N(N-1)}{2}) $
- $ 1\leq\ a_i\ \lt\ b_i\leq\ N $
- $ i\neq\ j $ ならば $ (a_i,b_i)\neq\ (a_j,b_j) $
- 入力に含まれる値は全て整数

### Sample Explanation 1

$ P $ は、$ (5,3,2,4,6,1)\to\ (5,2,3,4,6,1)\to\ (5,2,3,4,1,6)\to\ (1,2,3,4,5,6) $ と変化します。

### Sample Explanation 2

$ P $ を昇順に並び替えることはできません。

### Sample Explanation 3

初めから $ P $ が昇順に並んでいることもあります。 また、以下のような答えも正解になります。 ``` 4 5 5 5 5 ``` 操作の回数を最小化する必要はないことに注意してください。

## 样例 #1

### 输入

```
6
5 3 2 4 6 1
4
1 5
5 6
1 2
2 3```

### 输出

```
3
4 2 1```

## 样例 #2

### 输入

```
5
3 4 1 2 5
2
1 3
2 5```

### 输出

```
-1```

## 样例 #3

### 输入

```
4
1 2 3 4
6
1 2
1 3
1 4
2 3
2 4
3 4```

### 输出

```
0```

# 题解

## 作者：kkxacj (赞：9)

目前看上去应该没问题，如果有 `hack` 可以私信联系我。
#### 思路

$m$ 种操作可以理解为 $m$ 条无向边，记 $id_i$ 表示第 $i$ 个数在给出的序列中实际在的位置，如果 $id_i$ 和 $i$ 不在一个连通块里，那么一定无解。

否则对于每一个数看 $id_i$ 与 $i$ 是否相等，不相等就跑一遍最短路，记录一下用了哪些边，具体的就是在求最短路是记录是由哪个点转过来的以及转过来用了那条边，然后以从 $id_i$ 到 $i$ 的顺序加入答案序列。

考虑枚举 $i$ 表示前 $i-1$ 的数都排好了，开始排第 $i$ 个，若 $i$ 到 $id_i$ 的最短路有前 $i-1$ 个的数，则需要在跑完后需要把这条路径其他点放回去，否则若路径上 $j = id_j$ 的个数比其他更多，也需要把这条路径其他点放回去，即按从 $id_i$ 到 $i$ 的顺序交换，但不换与 $i$ 相邻的点，会发现**只改变了 $i$ 和 $id_i$ 的值**，否则不放。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
int n,m,a[10010],x,y,ok,ok1,xt[500010],yt[500010],v[10010],f[10010],id[200010],st[500010],cnt,bj[1010],bj1[1010],bj2[1010],cnt1,f1[10010];
vector<int>w[10010];
vector<int>w1[10010];
priority_queue<pair<int,int> > q;
inline int find(int x)
{
	if(f[x] == x) return x;
	return f[x] = find(f[x]);
}
inline void bfs(int x)
{
	while(!q.empty())
	{
		y = q.top().second;
		q.pop();
		v[y] = 0;
		for(int i = 0;i < w[y].size();i++)
		{
			if(bj[w[y][i]] == 1e16 || bj[w[y][i]] > bj[y]+1) 
			{
				bj[w[y][i]] = bj[y] + 1,bj1[w[y][i]] = y,bj2[w[y][i]] = w1[y][i];
				if(!v[w[y][i]]) 
				{
					q.push(make_pair(-bj[w[y][i]],w[y][i]));
					v[w[y][i]] = 1;
				}
			}
		}
	}
	return;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n);
	for(int i = 1;i <= n;i++) read(a[i]),f[i] = i,id[a[i]] = i;
	read(m);
	for(int i = 1;i <= m;i++) read(x),read(y),xt[i] = x,yt[i] = y,f[find(x)] = find(y),w[x].push_back(y),w[y].push_back(x),w1[x].push_back(i),w1[y].push_back(i);
	for(int i = 1;i <= n;i++)
		if(find(i) != find(id[i])) 
		{
			print(-1);
			flush();
			return 0;
		}//每次执行前保证前i-1个排好序 
		for(int i = 1;i <= n;i++)
			if(i != id[i])
			{
				for(int j = 1;j <= n;j++) v[j] = bj1[j] = bj2[j] = 0,bj[j] = 1e16; 
				bj[id[i]] = 0,q.push(make_pair(0,id[i]));
				bfs(id[i]);
				cnt1 = 0,y = i; ok = ok1 = 0;
				while(y != id[i])
				{
					if(id[y] == a[y] && id[y] < i) ok += n;//若有<i的点则一定要换回去 
					else if(id[y] == a[y]) ok++;
					else ok1++;//记录 
					f1[++cnt1] = bj2[y];
					y = bj1[y];
				}
				for(int j = cnt1;j >= 1;j--)
				{
					st[++cnt] = f1[j];
					swap(id[a[xt[f1[j]]]],id[a[yt[f1[j]]]]);
					swap(a[xt[f1[j]]],a[yt[f1[j]]]);
				}
				if(ok > ok1)//看是否将路径上其他点放回原位 
				{
					for(int j = 2;j <= cnt1;j++)
					{
						st[++cnt] = f1[j];
						swap(id[a[xt[f1[j]]]],id[a[yt[f1[j]]]]);
						swap(a[xt[f1[j]]],a[yt[f1[j]]]);
					}
				}
			}
	print(cnt),pc('\n');
	for(int i = 1;i <= cnt;i++) print(st[i]),pc(' ');
	flush();
	return 0;

```

---

## 作者：igAC (赞：5)

# $\text{Describe}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_abc233_f)

[ATlink](https://atcoder.jp/contests/abc233/tasks/abc233_f)

简要题意（洛谷翻译）：

给你一个长度为 $n$ 的排列和 $m$ 种操作. 每个操作形如 $(u,v)$ , 表示将 $a_u$ 和 $a_v$ 交换 .

请问是否存在一种方案, 经过适当操作, 把这个排列变为 $(1,2,3,\dots,n)$? 如果可以, 请给出一种构造, 要求长度不超过 $5 \times 10^5$. 否则请输出 $-1$.

$1 \le n \le 10^3 ,1 \le m \le 2 \times 10^5$.

# $\text{Solution}$

用图论的思路来思考这一题。

长度为 $n$ 的排列视为 $n$ 个点，将 $m$ 个操作视为 $m$ 条无向边。

那么题意就变为：

给定一个 $n$ 个点 $m$ 条边的无向图，每个点都有权值和目标值，你可以将一条边两端节点的权值互换，问是否有对于每个点，都有权值等于目标值的操作方案。

第一步我们需要判断是否有解。

可以证明，若每个节点和目标值所对应的那个节点都在同一个连通块内，那么是有解的，否则无解。

这个用并查集维护即可。

片段参考代码：

```cpp
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
bool same(int x,int y){return (find(x)==find(y));}

for(int i=1;i<=n;++i){
	if(!same(i,a[i])){
		puts("-1");
		exit(0);
	}
}
```

接下来我们就要构造操作方案了。

我们要通过交换来满足一个节点的需求的话，就需要将目标值通过交换转移到与它相邻的节点上。

![](https://cdn.luogu.com.cn/upload/image_hosting/qrsu629g.png)

如此图（w 指 wish，即其目标值）。

我们要满足目标值为 $2$ 的节点，就要交换 $2$ 和 $3$，接着交换 $2$ 和 $4$。

这就启发了我们要满足某一个节点，枚举与它相邻的节点，若能交换过来，那就进行这一步操作。

片段参考代码：

```cpp
bool Swap(int x,int f,int to){
	if(a[x]==to) return true;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==f) continue;
		if(Swap(y,x,to)){
			ans.push_back(e[i].pos);//记录操作
			swap(a[x],a[y]);
			return true;
		}
	}
	return false;
}
```

具体实现可参考完整代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define N 1005
#define M 500005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,m,head[N],tot;
int a[N],fa[N];
bool vis[N];
vector<int>ans;
struct Edge{
	int to,nxt;
	int pos;
}e[M];
void add_edge(int x,int y,int z){
	e[++tot].to=y;
	e[tot].pos=z;
	e[tot].nxt=head[x];
	head[x]=tot;
}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
bool same(int x,int y){return (find(x)==find(y));}
void merge(int x,int y){fa[find(x)]=find(y);}
bool Swap(int x,int f,int to){
	if(a[x]==to) return true;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==f) continue;
		if(Swap(y,x,to)){
			ans.push_back(e[i].pos);
			swap(a[x],a[y]);
			return true;
		}
	}
	return false;
}
void dfs(int x){
	vis[x]=true;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(vis[y]) continue;
		dfs(y);
	}
	if(!Swap(x,0,x)){
		puts("-1");
		exit(0);
	}
}
int main(){
	n=read();
	for(int i=1;i<=n;++i) fa[i]=i;
	for(int i=1;i<=n;++i) a[i]=read();
	m=read();
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		if(!same(x,y)){
			merge(x,y);
			add_edge(x,y,i);
			add_edge(y,x,i);
		}
	}
	for(int i=1;i<=n;++i){
		if(!same(i,a[i])){
			puts("-1");
			return 0;
		}
	}
	for(int i=1;i<=n;++i) if(!vis[i]) dfs(i);
	printf("%d\n",ans.size());
	for(int i:ans) printf("%d ",i);
	return 0;
}
```

---

## 作者：TLEWA (赞：4)

## 观前注意

本篇题解是乱搞题解，不保证能在操作次数限制内构造出合法解。如果要学习正经的解题思路可以选择跳过本篇题解。

## 解题思路

首先考虑把可交换关系视为无向边建图，将单个数字归位的最优方案可以通过在图上进行一遍 BFS 求出，在随机数据下每个数字归位的最优方案的交似乎不长，尝试乱搞。

考虑将所有数字放入队列按顺序沿最优路径归位，在最优路径的交换过程中，可能有已经归位的点被交换出来，此时需要将其重新加入队列。

在随机数据下，这个做法可以得到较优的答案。但是在 AT 强大的构造数据下，上述策略可能会导致归位点无限被交换导致死循环或者操作次数超限，于是我们采取以下方式优化我们的做法：

1. 初始构造队列的时候，将归位路径较短的点排序在前，直觉上这样较为优秀。
2. 我们存储每个点归位的每一条最短路径，需要存储总边数上界显然在 $O(n^2 \sqrt{n})$ 以下，可以接受。在归位时，我们等概率随机选择一条最短路径边进行交换操作，如果目标点已经归位，则重新随机一条边，重复至多十次。
3. 在进行上述操作后，如果仍然选择了一条目标点已经归位的最短路径边，为了防止构造数据导致方案退化，我们借鉴 SPFA 的 SLF 优化思路，每次将已经归位的点重新加入队列时，以万分之一的概率接受将此点直接加入队首，反之加入队尾，有效防止了在极限数据下的退化情况。

应用以上优化思路之后，我们直接通过了此题，以下是 AC 代码：


```cpp
#include<bits/stdc++.h>

using namespace std;

/*
只要一个贪心它很对，那它就不是错的！ 
*/

const int N=1005,M=500005;

int n,m;
int arr[N],rf[N],dis[N][N],id[N][N],ans[M],sarr[N],tot;
vector<int> vec[N],nxt[N][N];

void BFS(int S) {
	dis[S][S]=0;
	queue<int> que;que.push(S);
	int u;
	while(!que.empty()) {
		u=que.front();
		que.pop();
		for(auto& v:vec[u]) {
			if(dis[S][v]>=dis[S][u]+1) {
				if(dis[S][v]!=dis[S][u]+1)que.push(v);
				dis[S][v]=dis[S][u]+1,nxt[S][v].push_back(u);
			}
		}
	}
}

mt19937 rnd(time(0));
deque<int> que;
int main() {
	cin >> n;
	for(int i=1;i<=n;++i) cin >> arr[i];
	
	cin >> m;int u,v;
	for(int i=1;i<=m;++i) {
		cin >> u >> v;
		id[u][v]=id[v][u]=i;
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	
	memset(dis,63,sizeof(dis));
	for(int i=1;i<=n;++i) BFS(i);
	
	for(int i=1;i<=n;++i) sarr[i]=i,rf[arr[i]]=i;
	sort(sarr+1,sarr+1+n,[&](int a,int b) {
		return dis[a][rf[a]]<dis[b][rf[b]];
	});
	for(int i=1;i<=n;++i) que.push_back(sarr[i]);
	
	int siz;
	while(!que.empty()) {
		u=que.front();
		que.pop_front();
		for(;dis[u][rf[u]];) {
			if(nxt[u][rf[u]].empty()) {
				cout << -1;
				return 0;
			}
			siz=nxt[u][rf[u]].size();
			v=arr[nxt[u][rf[u]][rnd()%siz]];
			for(int i=1;i<=10&&dis[v][rf[v]]==0;++i)
				v=arr[nxt[u][rf[u]][rnd()%siz]];
			if(dis[v][rf[v]]==0) {
				if(rnd()%10000) que.push_back(v);
				else que.push_front(v);
			}
			ans[++tot]=id[rf[u]][rf[v]];
			if(tot>5e5) {
				cout << -1;
				return 0;
			}
			swap(arr[rf[u]],arr[rf[v]]);
			swap(rf[u],rf[v]);
		}
	}
	
	cout << tot << '\n';
	for(int i=1;i<=tot;++i) cout << ans[i] << ' ';
	
	return 0;
}

```

---

## 作者：loser_seele (赞：4)

差点又喜提最劣解。

不难发现，如果将元素视为点，关系视为边，则如果有一个点和它的编号不在一个连通块则显然无解，因为根本无法交换到编号的位置。

如果不存在这样的点，一定有解。

因为考虑最差情况下，所有点都是逆序，那么需要交换次数 $ \frac{1000 \times 999}{2}<5 \times 10^5 $ 次，所以次数的限制没啥用。

于是考虑怎么交换，显然对每个连通块取其生成树并不影响连通性，于是得到了生成森林，然后对每个点暴力移动到指定位置就行了。注意优先选择叶子，否则会影响前面的答案。

这个可以朴素 dfs，但用 LCT 也可以做，每次将一条路径 split 出来后记录路径即可。

时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
#define pw(a) (1<<a)
#define PP push_back
#define X first
#define Y second
using namespace std;
typedef long long LL;
typedef double DD;
typedef pair<int,int> PAIR;
const int INF=1e9;
const int mod=1e9+7;
const int N=2e5+10;
int n,m,k,T,sum;
vector<int>ans;
vector<int>gra[N];
int vis[N];
int A[N];
struct Node
{
	int s[2],v,p;
	int rev;
}tre[N<<4];
void pushrev(int x)
{
	swap(tre[x].s[0],tre[x].s[1]);
	tre[x].rev^=1;
}
void pushdown(int x)
{
	if(!tre[x].rev) 
    return ;
	pushrev(tre[x].s[0]);
	pushrev(tre[x].s[1]);
	tre[x].rev=0;
}
bool isroot(int x)
{
	int p=tre[x].p;
	return tre[p].s[0]!=x&&tre[p].s[1]!=x;
}
void update(int x)
{
	if(!isroot(x)) 
    update(tre[x].p);
	pushdown(x);
}
void rotate(int x)
{
	int y=tre[x].p,z=tre[y].p;
	int k=tre[y].s[1]==x;
	if(!isroot(y)) 
    tre[z].s[tre[z].s[1]==y]=x;
	tre[x].p=z;
	tre[y].s[k]=tre[x].s[k^1],tre[tre[x].s[k^1]].p=y;
	tre[x].s[k^1]=y,tre[y].p=x;
}
void splay(int x)
{
	update(x);
	while(!isroot(x))
	{
		int y=tre[x].p,z=tre[y].p;
		if(!isroot(y))
		{
			if((tre[y].s[1]==x)^(tre[z].s[1]==y)) 
            rotate(x);
			else 
            rotate(y);
		}
		rotate(x);
	}
}
void access(int x)
{
	int z=x;
	for(int y=0;x;y=x,x=tre[x].p)
	{
		splay(x);
		tre[x].s[1]=y;
	}
	splay(z);
}
void makeroot(int x)
{
	access(x);
	pushrev(x);
}
int getroot(int x)
{
	access(x);
	while(tre[x].s[0]) 
    pushdown(x),x=tre[x].s[0];
	splay(x);
	return x;
}
void split(int x,int y)
{
	makeroot(x);
	access(y);
}
bool isconnect(int x,int y)
{
	makeroot(x);
	return  getroot(y)==x;
}
void link(int x,int y)
{
	makeroot(x);
	if(getroot(y)!=x) tre[x].p=y;
}
void move(int x,int i)
{
	pushdown(x);
	if(tre[x].s[0]) 
    move(tre[x].s[0],i);
	if(!tre[x].v) 
    ans.PP(x);
	else
	{
		int j=tre[x].v;
		swap(tre[A[i]].v,tre[x].v);
		swap(A[i],A[j]);
	}
	if(tre[x].s[1]) 
    move(tre[x].s[1],i);
}
void dfs(int u)
{
	vis[u]=1;
	for(auto v:gra[u])
	if(!vis[v]) 
    dfs(v);
	split(A[u],u);
	move(u,u);
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>tre[i].v;
		A[tre[i].v]=i;
	}
	cin>>m;
	for(int i=1,x,y;i<=m;i++)
	{
		cin>>x>>y;
		if(isconnect(x,y)) 
        continue;
		gra[x].PP(y);
		gra[y].PP(x);
		link(x,i+n);
		link(y,n+i);
	}
	for(int i=1;i<=n;i++)
		if(!isconnect(A[i],i))
			return !puts("-1");
	for(int i=1;i<=n;i++)
	if(!vis[i]) 
    dfs(i);
	cout<<ans.size()<<'\n';
	for(auto v:ans) 
    cout<<v-n<<' ';
}

```


---

## 作者：WaterSun (赞：4)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DAT_abc233_f%20%5BABC233F%5D%20Swap%20and%20Sort/)

# 思路

一眼可以把两个可以交换的数之间建一条边，显然在一个连通块里面的元素可以**两两之间**交换。

由于是排列，每一个元素 $i$ 最终的位置是 $i$。

考虑将元素从小到大放置，令 $ad_i$ 表示当前 $i$ 元素的位置。

现在我们想让 $i$ 换到 $i$ 位置上，并且想使用最小的步数（因为有 $5 \times 10^5$ 的限制），那么在图上找到 $i$ 到 $ad_i$ 的最短路即可。

需要注意的是，我们让 $i$ 换到 $i$ 位置后，需要将它们在图之中的点换回去。

# Code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register

using namespace std;

typedef pair<int,int> pii;
const int N = 2e5 + 10,M = 1010,inf = 1e9 + 10;
int n,m;
int ty[M][M],p[N],ad[N],d[N];
pii arr[N];
bool vis[N];
vector<int> ans,g[N];

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

inline void bfs(int s){
    fill(d + 1,d + n + 1,inf);
    fill(vis + 1,vis + n + 1,false);
    queue<int> q;
    q.push(s); vis[s] = true;
    while (!q.empty()){
        int u = q.front(); q.pop();
        for (int v:g[u]){
            if (vis[v]) continue;
            d[v] = d[u] + 1;
            vis[v] = true; q.push(v);
        }
    }
}

int main(){
    n = read();
    for (re int i = 1;i <= n;i++) ad[p[i] = read()] = i;
    m = read();
    for (re int i = 1;i <= m;i++){
        int a,b; a = read(),b = read();
        g[a].push_back(b); g[b].push_back(a);
        arr[i] = {a,b}; ty[a][b] = ty[b][a] = i;
    }
    for (re int i = 1;i <= n;i++){
        if (i == ad[i]) continue;
        bfs(i);
        if (d[ad[i]] == inf) return puts("-1"),0;
        int u = ad[i];
        vector<int> t;
        while (u != i){
            for (int v:g[u]){
                if (d[v] + 1 == d[u]){
                    swap(p[u],p[v]);
                    t.push_back(ty[u][v]);
                    ans.push_back(ty[u][v]);
                    u = v; break;
                }
            }
        }
        if (t.size() >= 2){
            for (re int j = t.size() - 2;~j;j--){
                int x = t[j];
                swap(p[arr[x].fst],p[arr[x].snd]);
                ans.push_back(x);
            }
        }
        for (re int j = 1;j <= n;j++) ad[p[j]] = j;
    }
    if (ans.size() > 5e5) puts("-1");
    else{
        printf("%d\n",ans.size());
        for (int x:ans) printf("%d ",x);
    }
    return 0;
}
```

---

## 作者：AC_love (赞：3)

每个操作 $(u, v)$ 相当于从 $u$ 到 $v$ 连了一条无向边。

如果某个位置 $x$ 上有一个数字 $y$，那么 $y$ 一定要最终从 $x$ 位置换到 $y$ 位置。如果 $x, y$ 不在同一个联通块中就寄了，无解。

如果在的话，我们找一下最短路，一路把 $y$ 换过去即可。

但这样还会交换其他点的位置，会造成影响。为了消除这个影响，我们还需要把 $y$ 原来的东西换回到 $x$ 位置。

举个例子，我们一路换过去的路径长这样：

$n, 2, 3, 4, \cdots, n - 2, n - 1, 1$

我们想把 $1$ 换到第一个位置，一路换过去之后会变成：

$1, n, 2, 3, 4, \cdots, n - 2, n - 1$

然后我们要把原本在第一个位置上的 $n$ 换到原本 $1$ 的位置，变成：

$1, 2, 3, 4, \cdots, n - 2, n - 1, n$

就这样。

我们只要把 $1 \sim n$ 的数都换到它该在的位置即可。

显然这样很好构造方案，可问题是构造出来的方案会不会超过 $5 \times 10^5$ 呢？

答案是会的，考虑构造一组这样的数据：

```
8 7 5 6 1 2 3 4
```

其中只能交换两两相邻的数。

我们先把 $1 \sim 4$ 换到位置上：

```
1 2 3 4 8 7 5 6
```

然后把 $5 \sim 6$ 换到位置上：

```
1 2 3 4 5 6 8 7
```

最后把 $7$ 换到位置上：

```
1 2 3 4 5 6 7 8
```

不难发现，最后一共交换了 $35$ 次，这个数超过了 $\dfrac{n^2}{2} = 32$。

实际上，用类似的构造，在 $n = 960$ 的时候可以将答案卡到 $613421$，这个数超过了 $5 \times 10^5$。

有没有办法挽救一下呢？

考虑到按照 $1 \sim n$ 的顺序换会被构造的数据卡掉，那么只要我不按照 $1 \sim n$ 的顺序换，就很难被卡了。

我们可以 `shuffle` 一个交换的序列，然后按照这个序列的顺序交换即可，这样被卡掉的几率就大大降低了。

如果还是被卡了，我们就再 `shuffle` 一次，直到不被卡为止。

[code](https://atcoder.jp/contests/abc233/submissions/59720230)

---

## 作者：YFF1 (赞：3)

## 思路：
首先，这是一道构造题。题目中说到，要求构造一种能够通过不超过限度次数的交换使得序列变得有序。由于题目中没有说必须要最优，所以只需要构造一种不超过限度的即可。

有一种较为优秀的构造方法：首先把各种交换关系抽象成一张图，如果有一个点和它想要变成的值不在同一个连通块里面，就说明无论怎样换都换不出有序序列。此时直接输出无解。然后，在图上每个连通块内部选取一些边，构造一棵生成树。从树上的叶子节点开始，每个点把它想要的权值通过和相邻节点交换权值换给它。处理完毕叶子节点，把处理完的节点“删掉”。然后按照同样的方式处理新的叶子节点。最后就可以把每个节点都换成它的对应值了。

为什么要换叶子节点呢？因为这种构造方式的核心就是每个处理完毕的节点都不会受到影响。这样每个点最多只会和剩下的所有点都交换一次，很大程度上避免了操作的重复。尝试取到极限数据，这样的构造方式刚好可以通过样例。

## 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,p[1005],a[200005],b[200005],fa[200005],edge[1005][1005];
vector<int>ans,g[200005];
bool vis[10005];
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
bool spp(int x,int fa,int num){
	if(p[x]==num)return true;
	for(int i:g[x]){
		if(i==fa)continue;
		if(spp(i,x,num)){
			ans.push_back(edge[i][x]);
			swap(p[x],p[i]);
			return true;
		}
	}
	return false;
}
void dfs(int x){
	vis[x]=1;
	for(int i:g[x]){
		if(!vis[i])dfs(i);
	}
	if(!spp(x,0,x)){
		cout<<-1;
		exit(0);
	}
}
signed main () {
	cin>>n;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)scanf("%lld",&p[i]);
	cin>>m;
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&a[i],&b[i]);
		edge[a[i]][b[i]]=i;
		edge[b[i]][a[i]]=i;
		if(find(a[i])!=find(b[i])){
			fa[find(a[i])]=fa[find(b[i])];
			g[a[i]].push_back(b[i]);
			g[b[i]].push_back(a[i]);
		}
	}
	for(int i=1;i<=n;i++){
		if(find(p[i])!=find(i)){
			cout<<-1;
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i])dfs(i);
	}
	cout<<ans.size()<<endl;
	for(int i:ans)cout<<i<<" ";
	return 0;
}
```

---

## 作者：chengning0909 (赞：2)

# abc 233 f

## 题意

给定一个长度为 $n$ 的全排列 $P$，有 $m$ 种操作，每种操作交换 $a_i$ 和 $b_i$。

请问可不可以用至多 $5 \times 10 ^ 5$ 次操作，使得序列升序排序。

如果可以，输出操作序列，否则输出 `-1`。

## 思路

将 $m$ 种操作看成一条无向边，那么题目就会变成这样：

给定一个 $n$ 个点，$m$ 条边的无向图，每次操作可以交换相邻两个点的数字 $p_i, p_j$，请你求出需要多少次操作，使得所有 $p_i = i$。

所以，就有三种情况了，我们一一来看：

- 链：那么，很明显，我们会先考虑满足这条链的两端，因为满足这两个点后，只要对中间的一段进行操作即可。

- 树：树就和链很像，其实可以把链的两端看做成两个入度为 $1$ 的点，那么每次优先操作的就是入度为 $1$ 的点了。

- 图：既然我们都知道了树应该如何处理，那么我们就可以直接在图上搜出生成树，再分别选择入度为 $1$ 的点进行操作即可。

所以，直接按照这种来模拟即可。

---

## 作者：CodingOIer (赞：0)

## [ABC233F] Swap and Sort 题解

### 思路分析

显然的，对于每一个联通的块，当且仅当原序列包含的元素与目标序列包含的元素相同时有解。

并查集后哈希即可。

```cpp
for (int i = 1; i <= m; i++)
{
    int u, v;
    scanf("%d%d", &u, &v);
    link[u].push_back(v);
    link[v].push_back(u);
    map[{u, v}] = i;
    map[{v, u}] = i;
    merge(u, v);
}
for (int i = 1; i <= n; i++)
{
    v1[find(i)].push_back(i);
    v2[find(i)].push_back(p[i]);
}
for (int i = 1; i <= n; i++)
{
    unsigned long long sum1, sum2;
    sum1 = 0;
    sum2 = 0;
    for (auto x : v1[i])
    {
        sum1 += sha[x];
    }
    for (auto x : v2[i])
    {
        sum2 += sha[x];
    }
    if (sum1 != sum2)
    {
        printf("-1\n");
        return 0;
    }
}
```

现在我们可以确定这样的一组数据一定是有解的了。

现在对于每一个 $i \in [1, n]$，我们求出在原数组中 $i$ 的位置。

把题目给出的点对建成一张无向图，跑一遍 Dijkstra 即可求出最短的交换序列。（其实其他算法的答案优越性同样远远够用，但 Dijkstra 时间复杂度合适，而且较短）

然后我们把每一个交换序列里的点对两两互换即可。

为什么还不贴代码？因为 RE 了……

考虑 AtCoder 数据中的 `kill001`：

```plain
>>>>> INPUT <<<<<
9
1 6 7 8 9 2 3 4 5
14
1 2
1 9
2 3
2 4
2 5
3 4
3 5
4 5
6 7
6 8
6 9
7 8
7 9
8 9
>>>>> OUTPUT <<<<<
22
4 1 2 11 10 3 1 2 11 9 4 1 2 11 4 5 1 4 2 1 3 1
```

在我们的算法跑出 $2$ 交换序列并交换后，我们发现 $1$ 不再是在 $p_1$。

导致了后面有一个数无法找到对应的下标，进而导致 Dijkstra 在乱跑，不出意外的越界了。

如何解决？

考虑我们的算法特性，如交换下面的 $1$ 和 $5$。

```plain
>>>>> BEFORE <<<<<
5 4 3 2 1
>>>>> AFTER <<<<<
1 5 4 3 2
```

其中有可能被意外交换的是除了 $p_1, p_5$ 的 $p_2, p_3, p_4$。

因为 $p_1$ 是原位置，会被替换为 $5$。

而 $p_5$ 绝对在 $p_1$ 后面，因为前面的已经排列为了目标序列，所以不会有影响。

考虑再把 $p_2$ 移动到 $p_5$。

```plain 
>>>>> BEFORE <<<<<
1 5 4 3 2
>>>>> AFTER <<<<<
1 4 3 2 5
```

我们发现，其实这样就只交换了 $p_1$ 和 $p_5$，没有对路径上的其他点做修改。

问题迎刃而解。

### 代码实现

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <map>
#include <queue>
#include <random>
#include <utility>
#include <vector>
std::mt19937_64 rnd(std::random_device{}());
constexpr int MaxN = 1e3 + 5;
int n, m;
int p[MaxN];
int f[MaxN];
int w[MaxN];
int pre[MaxN];
int dis[MaxN];
bool vis[MaxN];
unsigned long long sha[MaxN];
std::map<std::pair<int, int>, int> map;
std::vector<int> v1[MaxN];
std::vector<int> v2[MaxN];
std::vector<int> link[MaxN];
std::vector<int> answer;
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> queue;
int find(int x)
{
    if (f[x] != x)
    {
        f[x] = find(f[x]);
    }
    return f[x];
}
void merge(int x, int y)
{
    int fx, fy;
    fx = find(x);
    fy = find(y);
    if (fx == fy)
    {
        return;
    }
    f[fy] = fx;
}
void Dijkstra(int u)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[u] = 0;
    memset(vis, false, sizeof(vis));
    queue.push({0, u});
    for (; !queue.empty();)
    {
        auto [_, u] = queue.top();
        queue.pop();
        if (vis[u])
        {
            continue;
        }
        vis[u] = true;
        for (auto v : link[u])
        {
            if (dis[u] + 1 < dis[v])
            {
                pre[v] = u;
                dis[v] = dis[u] + 1;
                queue.push({dis[v], v});
            }
        }
    }
}
std::vector<std::pair<int, int>> rev(int u, int v)
{
    Dijkstra(u);
    std::vector<std::pair<int, int>> response;
    int x = v;
    for (; x != u;)
    {
        response.push_back({x, pre[x]});
        x = pre[x];
    }
    return response;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        f[i] = i;
        sha[i] = rnd();
        scanf("%d", &p[i]);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        link[u].push_back(v);
        link[v].push_back(u);
        map[{u, v}] = i;
        map[{v, u}] = i;
        merge(u, v);
    }
    for (int i = 1; i <= n; i++)
    {
        v1[find(i)].push_back(i);
        v2[find(i)].push_back(p[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        unsigned long long sum1, sum2;
        sum1 = 0;
        sum2 = 0;
        for (auto x : v1[i])
        {
            sum1 += sha[x];
        }
        for (auto x : v2[i])
        {
            sum2 += sha[x];
        }
        if (sum1 != sum2)
        {
            printf("-1\n");
            return 0;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int w = i;
        for (; w <= n; w++)
        {
            if (p[w] == i)
            {
                break;
            }
        }
        auto response = rev(i, w);
        for (auto [u, v] : response)
        {
            std::swap(p[u], p[v]);
            answer.push_back(map[{u, v}]);
        }
        for (int i = int(response.size()) - 2; i >= 0; i--)
        {
            auto [u, v] = response[i];
            std::swap(p[u], p[v]);
            answer.push_back(map[{u, v}]);
        }
    }
    printf("%zu\n", answer.size());
    for (auto x : answer)
    {
        printf("%d ", x);
    }
    printf("\n");
    return 0;
}
```

---

