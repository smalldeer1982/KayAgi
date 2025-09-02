# Rectangle Painting 2

## 题目描述

有一个$n*n$的网格，网格中有一些点是黑的，其他点都是白的。你每次可以花费$\min(h,w)$的代价把一个$h*w$的矩形区域变白。求把所有黑格变白的最小代价。

## 样例 #1

### 输入

```
10 2
4 1 5 10
1 4 10 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7 6
2 1 2 1
4 2 4 3
2 5 2 5
2 3 5 3
1 2 1 2
3 2 5 3
```

### 输出

```
3
```

# 题解

## 作者：tribool4_in (赞：1)

首先容易发现一次覆盖一定覆盖满整行或整列，于是问题变为选择若干行和列覆盖，每个黑点要求被所在行或列覆盖。

到这里可以有一个经典二分图建图，将行、列分别作为二分图的两侧点，每个黑点作为边，将其所在行、列连边。于是问题变为需要选择最少的点，使得所有边均被覆盖，即最小点覆盖。

然后由 **Konig 定理** 可知二分图最小点覆盖等于最大匹配，最大匹配等价于网络最大流问题。于是获得了高贵的 $O(\operatorname{poly}(n))$ 算法。

值域过大，于是考虑离散化，对于一段行值域，每行的结构完全相同，连边也相同，若选择覆盖则一定均覆盖。列同理。于是在网络流建图上将这些点合并，并将源汇点到他的边权设为点数。

于是复杂度就对了。

虽然是 codeforces 题但是代码中使用了 atcoder lib，哈哈。

```cpp
#include <bits/stdc++.h>
#include <atcoder/maxflow>
using namespace std;
using namespace atcoder;
const int N = 100 + 1, INF = 0x3f3f3f3f;
int n, m;
struct Rect {
    int x1, y1, x2, y2;
} r[N];
vector<int> xl, yl;
int calc(int p, vector<int> l) { return lower_bound(l.begin(), l.end(), p) - l.begin(); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> r[i].x1 >> r[i].y1 >> r[i].x2 >> r[i].y2;
        xl.push_back(r[i].x1), xl.push_back(r[i].x2 + 1);
        yl.push_back(r[i].y1), yl.push_back(r[i].y2 + 1);
    }
    sort(xl.begin(), xl.end()), xl.erase(unique(xl.begin(), xl.end()), xl.end());
    sort(yl.begin(), yl.end()), yl.erase(unique(yl.begin(), yl.end()), yl.end());
    int p = xl.size(), q = yl.size();
    int S = p + q, T = p + q + 1;
    mf_graph<int> G(p + q + 2);
    auto add_edge = [&](int u, int v, int w) { G.add_edge(u, v, w); };
    for (int i = 0; i < p - 1; i++) add_edge(S, i, xl[i + 1] - xl[i]);
    for (int i = 0; i < q - 1; i++) add_edge(p + i, T, yl[i + 1] - yl[i]);
    for (int i = 1; i <= m; i++) {
        int x1 = calc(r[i].x1, xl), x2 = calc(r[i].x2 + 1, xl), y1 = calc(r[i].y1, yl), y2 = calc(r[i].y2 + 1, yl);
        for (int x = x1; x < x2; x++)
            for (int y = y1; y < y2; y++) add_edge(x, p + y, INF);
    }
    cout << G.flow(S, T) << '\n';
    return 0;
}
```

---

## 作者：chenxia25 (赞：1)

首先有一个显然的二分图最小点覆盖。

但是这样点数是关于值域的，考虑优化。

我们注意到，对于一个黑色矩形，要么是行全被选，要么是列全被选（要么是 both），否则就不可能填满。进一步的，我们将横纵分别离散化，那么每一个离散化后的数所代表的区间都连为一个整体，要么全选，要么不选。

那么就显然有一个点数 $m$ 边数 $m^2$ 的二分图最小权点覆盖啦。

---

## 作者：yuzhechuan (赞：1)


网络流好题，模型是二分图的最小覆盖

---

### 题解：

首先要想到一个很显然的贪心，对于一个黑格，他要么是在纵向上被完全覆盖，要么是在横向上被完全覆盖，其中“完全覆盖”是指整行或整列都被一次性涂白

稍微思考一下，题目变成了在纵向上选一些列，在横向上选一些行，使得将他们完全覆盖后不存在一个黑格，问最少的选择数

我们可以将有黑格的行看成一个点集，将有黑格的列看成另一个点集，对于两者之间的交点，看成两个点集之间的连边，于是我们就得到了一个二分图

题目变成了二分图的最小覆盖问题

由于这张二分图的点数很和边数多，我们考虑离散与压缩，并用网络流进行优化，因为有一个重要定理：最小覆盖=最大流

离散后，对于一个矩形，我们只考虑它的四个边界，两个对立边界中所有点的代价全部赋给靠右（或下）的边界点，即（右减左，或下减上）

我们知道，网络流中点的代价是由超源和超汇给他的，于是从超源向行点连边，容量为其代价，从列点向超汇连边，容量为其代价，行点和列点之间的连边即两者是否相交，容量为无穷大

具体的，在代码实现中，我们将一条边界形如$[l,r]$的左闭右闭区间，修改成形如$[l,r+1)$的左闭右开区间

这是一个十分套路的方便操作，我们可以清楚的判定一个点到底是要被算进左边的代价还是右边的代价，并防止最右边被漏掉，详细可以看代码

---

代码轻微复杂，特先做出注释：

.x.x=x1

.x.y=y1

.y.x=x2

.y.y=y2

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	x=0;char c=getchar();bool f=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return  x;
}
template<class t> inline void write(t x){
	if(x<0){putchar('-'),write(-x);}
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}

#define pii pair<int,int>
#define x first
#define y second

const int oo=0x7fffffff,N=405,M=N*N+5;
int en=1,h[N],n,m,s,t,cur[N],d[N],ux[N],uy[N],uxn,uyn;

pair<pii,pii> a[N]; //pii套pii~

struct edge{
	int n,v,w;
}e[M<<1];

void add(int x,int y,int z){
	e[++en]=(edge){h[x],y,z};
	h[x]=en;
}

bool bfs(int s,int t){
	for(int i=s;i<=t;i++) d[i]=0,cur[i]=h[i];
	queue<int> q;
	q.push(s);
	d[s]=1;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=h[x];i;i=e[i].n){
			int y=e[i].v;
			if(!d[y]&&e[i].w){
				d[y]=d[x]+1;
				if(y==t) return 1;
				q.push(y);
			}
		}
	}
	return 0;
}

int dfs(int x,int flow,int t){
	if(x==t) return flow;
	int rest=flow;
	for(int &i=cur[x];i&&rest;i=e[i].n){
		int y=e[i].v;
		if(d[y]==d[x]+1&&e[i].w){
			int tp=dfs(y,min(rest,e[i].w),t);
			rest-=tp;
			e[i].w-=tp;
			e[i^1].w+=tp;
		}
	}
	return flow-rest;
}

int dinic(int s,int t){
	int res=0;
	while(bfs(s,t)) res+=dfs(s,oo,t);
	return res;
}

signed main(){
	read(n);read(m);
	for(int i=1;i<=m;i++){
		read(a[i].x.x);
		read(a[i].x.y);
		read(a[i].y.x);a[i].y.x++; //改成左闭右开区间
		read(a[i].y.y);a[i].y.y++;
		ux[++uxn]=a[i].x.x;
		uy[++uyn]=a[i].x.y;
		ux[++uxn]=a[i].y.x;
		uy[++uyn]=a[i].y.y;
	}
	ux[++uxn]=uy[++uyn]=n+1; //加一个边界，以防遗漏最右点
	sort(ux+1,ux+1+uxn);
	sort(uy+1,uy+1+uyn);
	uxn=unique(ux+1,ux+1+uxn)-ux-1; //离散
	uyn=unique(uy+1,uy+1+uyn)-uy-1;
	s=0,t=uxn+uyn+1; //超源超汇
	for(int i=1;i<=m;i++){
		a[i].x.x=lower_bound(ux+1,ux+1+uxn,a[i].x.x)-ux; //离散后的坐标
		a[i].x.y=lower_bound(uy+1,uy+1+uyn,a[i].x.y)-uy;
		a[i].y.x=lower_bound(ux+1,ux+1+uxn,a[i].y.x)-ux;
		a[i].y.y=lower_bound(uy+1,uy+1+uyn,a[i].y.y)-uy;
		for(int x=a[i].x.x;x<a[i].y.x;x++)
			for(int y=a[i].x.y;y<a[i].y.y;y++)
				add(x,y+uxn,oo),add(y+uxn,x,0); //添加交点的无穷边
	}
	for(int i=1;i<uxn;i++) add(s,i,ux[i+1]-ux[i]),add(i,s,0); //根据相邻边之间的距离，计算它的代价，并从超源向行点连边
	for(int i=1;i<uyn;i++) add(i+uxn,t,uy[i+1]-uy[i]),add(t,i+uxn,0);
	write(dinic(s,t)); //最大流=最小覆盖
}
```

---

## 作者：QianianXY (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1198E)

## 前置知识

- 二分图最小顶点覆盖：假如选了一个点就相当于覆盖了以它为端点的所有边，最小顶点覆盖就是选择最少的点来覆盖所有的边。

- König定理：二分图最小点覆盖的点的数量**等于**二分图最大匹配的边的数量。

## 题目分析

二分图最小顶点覆盖模型。

将一个矩形区域变白的代价是该矩形的最短边长。所以一整行或一整列地变白性价比更高。

因此将行的集合和列的集合分别看作二分图的两个点集，行和列的交点为二分图的边，进行建图。

注意到 $n\le10^9$，但 $m\le50$，所以对行和列的坐标离散化。整个矩形的代价赋给顶点。

源汇点与二分图点的边权为所需代价，二分图点间边权为正无穷。

用匈牙利算法或 ``Dinic`` 跑最大流均可。

## code

喜提次优解。

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 100010
using namespace std;
const int inf = 1e9;

template <typename T> inline void read(T &x)
{
	x = 0; int f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int n, m, X[N], Y[N], lenx, leny, s, t, head[N], edge_cnt = 1, cur[N], dep[N];
struct Squ {int x1, y1, x2, y2;} a[N];
struct edge {int nxt, v, w;} e[N << 1];

inline void add_edge(int u, int v, int w) {e[++edge_cnt].nxt = head[u]; head[u] = edge_cnt; e[edge_cnt].v = v; e[edge_cnt].w = w;}

inline bool Bfs()
{
	queue<int> q; 
	memset(dep, 0, sizeof(dep)); 
	dep[s] = 1; 
	q.push(s); 
	while (q.size())
	{
		int u = q.front(); q.pop(); cur[u] = head[u];
		for (rei i = head[u]; i; i = e[i].nxt)
		{
			int v = e[i].v;
			if (!dep[v] && e[i].w)
			{
				dep[v] = dep[u] + 1;
				q.push(v);
			}
		}
	}
	return dep[t] != 0;
}

inline int Dfs(int u, int flow)
{
	if (u == t) return flow;
	int rest = flow;
	for (rei i = cur[u]; i; i = e[i].nxt)
	{
		int v = e[i].v; cur[u] = i;
		if (dep[v] == dep[u] + 1 && e[i].w)
		{
			int tmp = Dfs(v, min(rest, e[i].w));
			e[i].w -= tmp;
			e[i ^ 1].w += tmp;
			rest -= tmp;
			if (!rest) break;
		}
	}
	return flow - rest;
}

inline int Dinic()
{
	int ret = 0;
	while (Bfs()) ret += Dfs(s, inf);
	return ret;
}

int main()
{
	read(n); read(m);
	for (rei i = 1; i <= m; i++)
	{
		read(a[i].x1); read(a[i].y1); read(a[i].x2); read(a[i].y2); a[i].x2++; a[i].y2++;
		X[++lenx] = a[i].x1; Y[++leny] = a[i].y1; X[++lenx] = a[i].x2; Y[++leny] = a[i].y2;
	}
	X[++lenx] = Y[++leny] = n + 1;
	sort(X + 1, X + 1 + lenx); lenx = unique(X + 1, X + 1 + lenx) - X - 1; 
	sort(Y + 1, Y + 1 + leny); leny = unique(Y + 1, Y + 1 + leny) - Y - 1;
	t = lenx + leny + 1; s = 0;
	for (rei i = 1; i <= m; i++)
	{
		a[i].x1 = lower_bound(X + 1, X + 1 + lenx, a[i].x1) - X; 
		a[i].y1 = lower_bound(Y + 1, Y + 1 + leny, a[i].y1) - Y;
		a[i].x2 = lower_bound(X + 1, X + 1 + lenx, a[i].x2) - X;
		a[i].y2 = lower_bound(Y + 1, Y + 1 + leny, a[i].y2) - Y; 
		for (rei x = a[i].x1; x < a[i].x2; x++)
			for (rei y = a[i].y1; y < a[i].y2; y++)
				add_edge(x, y + lenx, inf), add_edge(y + lenx, x, 0);
	}
	for (rei i = 1; i < lenx; i++) add_edge(s, i, X[i + 1] - X[i]), add_edge(i, s, 0);
	for (rei i = 1; i < leny; i++) add_edge(i + lenx, t, Y[i + 1] - Y[i]), add_edge(t, i + lenx, 0);
	printf("%d", Dinic());
	return 0;
}
```


---

## 作者：Zechariah (赞：0)

这个题是最小覆盖问题  
根据题意，如果我已经确定了在$x$方向上选择的长度，那么在$y$方向上肯定是选满  
也就是每次选择都是横着穿或者纵着穿肯定是不会使答案变差  
离散化后分别记录$x,y$，每一个方块都要至少从一个方向上消灭掉，连边之后跑最大流（最大流=最小覆盖）就行了

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define jh(x, y) x ^= y ^= x ^= y
#define loc(x, y) (x - 1) * m + y
#define rg register
#define inl inline
#define PI 3.141592654
typedef long long ll;
const int N = 5e5 + 5, INF = 0x3f3f3f3f, mod = 998244353;
using namespace std;
namespace fast_IO {
	inl ll read() {
		rg char c;
		rg ll x = 0;
		rg bool flag = false;
		while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
		if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
		while ((c = getchar()) != ' ' && c != '\n' && c != '\r' && ~c)
			x = (x << 1) + (x << 3) + (c ^ 48);
		if (flag)return -x; return x;
	}
	inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
int p[N], b[N], nt[N], num = 1, dist[N], w[N], st, ed, q[N], cur[N], sx[N], sy[N], ex[N], ey[N], tmpx[N], tmpy[N];
bool flag[N];
inl void add(rg int x, rg int y, rg int z) {
	b[++num] = y, w[num] = z;
	nt[num] = p[x]; p[x] = num;
	b[++num] = x, w[num] = 0;
	nt[num] = p[y]; p[y] = num;
}
inl bool bfs() {
	memset(dist, -1, sizeof(dist));
	dist[st] = 0; q[0] = st;
	rg int head = 1, tail = 0;
	while (head != tail) {
		rg int k = q[tail++]; if (tail == N)tail = 0;
		flag[k] = false;
		for (rg int e = p[k]; e; e = nt[e]) {
			rg int kk = b[e];
			if (dist[kk] < 0 && w[e] > 0) {
				dist[kk] = dist[k] + 1;
				if (!flag[kk]) {
					flag[kk] = true;
					q[head++] = kk;
					if (head == N)head = 0;
				}
			}
		}
	}
	return dist[ed] > 0;
}
int dfs(rg int x, rg int minv) {
	if (x == ed)return minv;
	rg int ans = 0;
	for (rg int e = cur[x], tmp; e && ans < minv; e = nt[e]) {
		cur[x] = e;
		rg int k = b[e];
		if (dist[k] == dist[x] + 1 && w[e] > 0 && (tmp = dfs(k, fast_IO::min(minv - ans, w[e]))))
			w[e] -= tmp, w[e ^ 1] += tmp, ans += tmp;
	}
	if (ans < minv)dist[x] = -1;
	return ans;
}

int main() {
	rg int n = fast_IO::read(), m = fast_IO::read();
	for (rg int i = 1; i <= m; ++i) {
		sx[i] = fast_IO::read(), sy[i] = fast_IO::read();
		ex[i] = fast_IO::read() + 1, ey[i] = fast_IO::read() + 1;
		tmpx[++*tmpx] = sx[i], tmpx[++*tmpx] = ex[i];
		tmpy[++*tmpy] = sy[i], tmpy[++*tmpy] = ey[i];
	}
	sort(tmpx + 1, tmpx + *tmpx + 1); sort(tmpy + 1, tmpy + *tmpy + 1);
	*tmpx = unique(tmpx + 1, tmpx + *tmpx + 1) - tmpx - 1;
	*tmpy = unique(tmpy + 1, tmpy + *tmpy + 1) - tmpy - 1;
	st = *tmpx + *tmpy + 1; ed = st + 1;
	for (rg int i = 0; i < *tmpx; ++i)add(st, i, tmpx[i + 1] - tmpx[i]);
	for (rg int i = 0; i < *tmpy; ++i)add(i + *tmpx, ed, tmpy[i + 1] - tmpy[i]);
	for (rg int i = 0; i < *tmpx; ++i)
		for (rg int j = 0; j < *tmpy; ++j)
			for (rg int k = 1; k <= m; ++k)
				if (sx[k] <= tmpx[i] && ex[k] >= tmpx[i + 1] && sy[k] <= tmpy[j] && ey[k] >= tmpy[j + 1]) {
					add(i, j + *tmpx, INF); break;
				}
	rg int ans = 0;
	while (bfs()) {
		memcpy(cur, p, sizeof(int) * (num + 1));
		rg int tmp;
		while (tmp = dfs(st, INF))ans += tmp;
	}
	fast_IO::write(ans);
	return 0;
}

```


---

## 作者：TruchyR (赞：0)

考虑一下代价的问题，发现一次涂满整行或列一定不比不涂满劣。  

问题转化为：  

涂满一行或一列需要 $1$ 的代价，求涂到所有黑格的最小代价。

但是 $n$ 非常巨大，所以考虑将输入的矩形离散化。  

$m$ 的范围很小，所以可以考虑网络流，这里用最小割的方式思考这个问题：  

假设离散化后行有 $x$ 个点，列有 $y$ 个点。  

- 从源点向行的每个点连边，边权为每个点代表的区间长。  
- 从列的每个点向汇点连边，边权为每个点代表的区间长。  
- 对于每一块要涂色的黑矩形，假设点 $i$ 代表这格行的区间，点 $j$ 代表这格列的区间，那么从 $i$ 向 $j$ 连边，边权为正无穷。  

由于最小割等于最大流所以直接跑出结果即可，下面讲一下为什么这样可行：  

- 每个点与源点或汇点相连的边如果割掉代表选择这段区间。  
- 对于每块黑矩形，对应的两段区间至少要选择一段。  
  - 如果两段都不选，那么行的点分到一边，列的点分到另一边，这条边就必须割。  
  - 如果至少选了一段，这条边就不用割。  
  - 由于这条边长为正无穷所以两段区间一定至少选一段。  
  
代码如下，有一些说明在代码里。  
```cpp
#include<bits/stdc++.h>
#define MX 705
#define int long long
#define INF 2000000000009ll
using namespace std;
int n,m,s=1,cnt=1,t,Xl[MX],Xh[MX],Xp,Yl[MX],Yh[MX],Yp;
int Xs[MX],Ys[MX],hdd[MX][MX],ans;

int hd[MX],st[MX],dep[MX];
struct eg{int to,nxt,qz;}edge[MX*MX];
void ae(int u,int v,int w) {
    edge[++cnt].to=v;edge[cnt].qz=w;
    edge[cnt].nxt=hd[u];hd[u]=cnt;
}
void bae(int u,int v,int w){ae(u,v,w);ae(v,u,0);}
bool bfs(){
	memset(dep,0,sizeof(dep));
	queue<int> q;q.push(s);
	dep[s]=1;
	while(q.size()){
		int u=q.front();q.pop();	
        for(int i=hd[u];i;i=edge[i].nxt) {
        	if(edge[i].qz<=0) continue;
        	int v=edge[i].to;
        	if(dep[v]) continue;dep[v]=dep[u]+1;
        	if(v==t){return true;}
        	q.push(v);
        }
	}
	return false;
}
int dfs(int u,int sm){
	if(u==t) return sm;
	int result=0;
    for(int i=st[u];i;i=edge[i].nxt) {
        st[u]=i;
        if(edge[i].qz<=0) continue;
		int v=edge[i].to;
        if(dep[v]!=dep[u]+1) continue;
        int res=dfs(v,min(sm,edge[i].qz));
        if(!res) dep[v]=0;
        edge[i].qz-=res;edge[i^1].qz+=res;
        result+=res;sm-=res;
        if(!sm) break;
    }
    return result;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;s=700,t=701;
	//输入和离散化
	for(int i=1;i<=m;i++){
		cin>>Xl[i]>>Yl[i]>>Xh[i]>>Yh[i];
		//某些区间有一些共用的端点所以不能直接离散化
		//这里选择将每个数相邻的数也加入离散化来规避这个问题
		Xs[i*6-5]=Xl[i]-1,Xs[i*6-4]=Xl[i],Xs[i*6-3]=Xl[i]+1;
		Xs[i*6-2]=Xh[i]-1,Xs[i*6-1]=Xh[i],Xs[i*6-0]=Xh[i]+1;
		Ys[i*6-5]=Yl[i]-1,Ys[i*6-4]=Yl[i],Ys[i*6-3]=Yl[i]+1;
		Ys[i*6-2]=Yh[i]-1,Ys[i*6-1]=Yh[i],Ys[i*6-0]=Yh[i]+1;}
	sort(Xs+1,Xs+m*6+1);Xp=unique(Xs+1,Xs+m*6+1)-Xs-1;
	sort(Ys+1,Ys+m*6+1);Yp=unique(Ys+1,Ys+m*6+1)-Ys-1;
	//源点向行的点连边
	for(int i=1;i<=Xp;i++) bae(s,i,max(1ll,Xs[i+1]-Xs[i]));
	//列的点向汇点连边
	for(int i=1;i<=Yp;i++) bae(i+Xp,t,max(1ll,Ys[i+1]-Ys[i]));
	//对于所有黑矩形进行连边操作
	for(int i=1;i<=m;i++){
		Xl[i]=lower_bound(Xs+1,Xs+Xp+1,Xl[i])-Xs;
		Xh[i]=lower_bound(Xs+1,Xs+Xp+1,Xh[i])-Xs;
		Yl[i]=lower_bound(Ys+1,Ys+Yp+1,Yl[i])-Ys;
		Yh[i]=lower_bound(Ys+1,Ys+Yp+1,Yh[i])-Ys;
		for(int X=Xl[i];X<=Xh[i];X++)
		for(int Y=Yl[i];Y<=Yh[i];Y++){
			if(hdd[X][Y]++) continue;
			bae(X,Y+Xp,INF);
		}
	}
	//网络流
	while(bfs()){
	    memcpy(st,hd,sizeof(hd));
		ans+=dfs(s,INF);
	}
	cout<<ans;
	return 0;
}
```

---

