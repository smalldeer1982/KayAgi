# Arpa’s overnight party and Mehrdad’s silent entering

## 题目描述

有2n个人围成一圈坐在桌子边上，每个人占据一个位子，对应这2n个人是n对情侣，要求情侣不能吃同一种食物，并且桌子上相邻的三个人的食物必须有两个人是不同的，只有两种食物（1或者是2），问一种可行分配方式。

## 样例 #1

### 输入

```
3
1 4
2 5
3 6
```

### 输出

```
1 2
2 1
1 2
```

# 题解

## 作者：王奕清 (赞：16)

这道题的做法就是通过建立二分图然后跑二分图染色就可以了。

首先我们在每对情侣之间连边，表示他们2个吃的不一样。

然后对于相邻3个人中要有2个吃的不同的限制，我们就在$2-1$和$2i$之间连边
因为这样就可以保证三个人中必定有2个吃的不同。

但是为什么这样建出来的图一定是二分图呢？

关于二分图有个性质，如果这个图不是二分图的话，那么就一定有奇环，如果没有，就一定是二分图。

我们假设$2i$和$2i-1$之间已经有一条路径，因为一个点只会有一个对应的情侣，所以这条路径一定是有$x$条情侣之间的边和$x-1$条相邻点之间的边组成的（这个可以画个图理解一下），再加上这条边，所以这个环就是偶环。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,x[200005],y[200005],c[200005];
vector<int>v[200005];
bool vis[200005];
void dfs(int x,int y)//二分图染色
{
    c[x]=y;
    vis[x]=1;
    for(int i=0; i<v[x].size(); i++)
    {
        int h=v[x][i];
        if(!c[h])dfs(h,3-y);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x[i]>>y[i];
        v[x[i]].push_back(y[i]);
        v[y[i]].push_back(x[i]);
    }
    for(int i=1;i<=n;i++)
    {
        v[i*2-1].push_back(i*2);
        v[i*2].push_back(i*2-1);
    }
    for(int i=1;i<=n*2;i++)if(!vis[i])dfs(i,1);
    for(int i=1;i<=n;i++)printf("%d %d\n",c[x[i]],c[y[i]]);
}
```

---

## 作者：do_while_true (赞：4)

直接无脑随机调整！

大力钦点 $121212\cdots$ 分配。

有限制的之间记录一下，强制改成相反的，此后其中一个改变另一个也要改变。

这个时候可能不满足相邻三个不能都相同了，把冲突的拉到一个队列里面，每次取出队头随机钦点一个修改，再把修改后新产生的冲突拉到队列里面去。

复杂度玄学，实测跑的飞快。

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<ctime>
#include<algorithm>
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T>
T& read(T& r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 1000010;
int n;
int to[N], pai[N][2];
int lastpos(int x) { return (x-2+n)%n+1; }
int nextpos(int x) { return x%n+1; }
int a[N];
bool vis[N];
std::queue<int>q;
bool chk(int i) {return (a[i] == a[nextpos(i)] && a[nextpos(i)] == a[nextpos(nextpos(i))]); }
void chk2(int pos) {
	if(chk(pos)) {
		if(!vis[pos]) q.push(pos);
		vis[pos] = 1;
	}
	else vis[pos] = 0;
	if(chk(lastpos(pos))) {
		if(!vis[lastpos(pos)]) q.push(lastpos(pos));
		vis[lastpos(pos)] = 1;
	}
	else vis[lastpos(pos)] = 0;
	if(chk(lastpos(lastpos(pos)))) {
		if(!vis[lastpos(lastpos(pos))]) q.push(lastpos(lastpos(pos)));
		vis[lastpos(lastpos(pos))] = 1;
	}
	else vis[lastpos(lastpos(pos))] = 0;
	if(chk(nextpos(pos))) {
		if(!vis[nextpos(pos)]) q.push(nextpos(pos));
		vis[nextpos(pos)] = 1;
	}
	else vis[nextpos(pos)] = 0;
	if(chk(nextpos(nextpos(pos)))) {
		if(!vis[nextpos(nextpos(pos))]) q.push(nextpos(nextpos(pos)));
		vis[nextpos(nextpos(pos))] = 1;
	}
	else vis[nextpos(nextpos(pos))] = 0;
}
signed main() { //freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
	srand(time(NULL)^(unsigned)(* new char));
	read(n); bool fl = 0; n <<= 1;
	for(int i = 1; i <= n/2; ++i) {
		int x, y; read(x); read(y);
		pai[i][0] = x; pai[i][1] = y;
		to[x] = y; to[y] = x;
		if(!(y == (x-2+n)%n+1 || y == x%n+1)) fl = 1;
	}
	for(int i = 1; i <= n; ++i) a[i] = i&1;
	for(int i = 1; i <= n; ++i)
		if(a[i] == a[to[i]])
			a[to[i]] = !a[to[i]];
	for(int i = 1; i <= n; ++i) {
		vis[i] = chk(i);
		if(vis[i])
			q.push(i);
	}
	while(!q.empty()) {
		int x = q.front(); q.pop();
		if(!chk(x)) continue ;
		int pos = rand()%2+1;
		if(pos == 1) pos = x;
		else if(pos == 2) pos = nextpos(x);
		else if(pos == 3) pos = nextpos(nextpos(x));
		a[pos] = !a[pos]; a[to[pos]] = !a[to[pos]];
		chk2(pos); chk2(to[pos]);
	}
	for(int i = 1; i <= n/2; ++i)
		printf("%d %d\n", 2-a[pai[i][0]], 2-a[pai[i][1]]);
	return 0;
}
```

---

## 作者：yuzhechuan (赞：4)

### 题解：

情侣关系等价两者之间连一条边

改变连续三个的限制，变为要求 $2i$ 和 $2i -1$ 食物类型不同，连一条边

发现这张图上不存在奇环，即这是张二分图

所以直接二分图染色即可

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx")
#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
#define getchar gc
inline char gc(){
	static char buf[1<<16],*p1=buf,*p2=buf;
	if(p1==p2){
		p2=(p1=buf)+fread(buf,1,1<<16,stdin);
		if(p2==p1) return EOF;
	}
	return *p1++;
}
#endif
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=2e5+5;
int n,a[N],b[N],col[N],ans[N];
bool tg[N];
vector<int> g[N];

void dfs(int x){ //染色
	for(int y:g[x]){
		if(ans[y]){
			if(ans[y]==ans[x]){
				write(-1);
				exit(0);
			}
		}
		else ans[y]=3-ans[x],dfs(y);
	}
}

signed main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);
		read(b[i]);
		if(a[i]>b[i]) swap(a[i],b[i]),tg[i]=1; //存在a>b的情况
		col[a[i]]=col[b[i]]=i; //记下是哪对情侣
		g[i*2].push_back(i*2-1); //相邻边
		g[i*2-1].push_back(i*2);
		g[a[i]].push_back(b[i]); //情侣边
		g[b[i]].push_back(a[i]);
	}
	for(int i=1;i<=2*n;i++) if(!ans[i]) ans[i]=1,dfs(i);
	for(int i=1;i<=n;i++) if(tg[i]) swap(a[i],b[i]);
	for(int i=1;i<=n;i++) printf("%d %d\n",ans[a[i]],ans[b[i]]);
}
```

---

## 作者：RyexAwl (赞：3)

本题解主要提供一种容易理解的二分图证明方法。

考虑按下面的策略构造一张二分图：

对于点 $2x$ 连一条无向边 $2x-1$  ，对该类边称为 “一类边”，所有 “一类边”构成的边集集合为 $E_1$ 。

对于一对情侣 $x,y$ 连一条无向边 $(x,y)$ 对该类边称为 “二类边”，所有 “二类边”构成的边集集合为 $E_2$ 。

令点集 $V = \{x | 1\le x\le 2\times n,x\in Z\}$ 。

对图 $G=(V,E_1\bigcup E_2)$ 进行二分图染色，对于任意一种合法的二分图染色方案其一定是满足要求的，并且这样建图保证图一定是二分图。


证明：

首先，有一个关键性质：对于任意一个点，其度数一定是小于等于二的（因为一个点至多连一条“一类边”和一条“二类边”）。

因此对于每个连通块，一定是简单环或者链。

那么我们证明这个图是二分图即证明图中所有的简单环都是偶数环。

考虑图 $G_1=(V,E_1)$ ，通过 “加边” 将图 $G_1$ “改造” 成图 $G$ 。

对于图 $G_1$ ，若点 $u,v$ 间存在一条边 $(u,v)$ 我们将其看成一个点 $x$ （即一个连通块），将添加的 $E_2$ 集合中的边看成所有这样的点 $x$ 间的连边。

并且我们发现，所有这诸如这样的点 $x$ 的度数也一定是不超过 $2$ 的。

并且可以发现，如果若干个点 $x$ 不构成环，那么这些点 $x$ 代表的连通块内的点也构不成环；如果若干个点 $x$ 构成环，若该环由 $k$ 个这样的点 $x$ 构成，那么其相当于有 $2\times k$ 个点集 $V$ 内的点构成的环，因此 “新图”的任意一个环，一定是偶环。

由此可证，图 $G=(V,E1\bigcup E2)$ 一定是二分图。

---

## 作者：Demoe (赞：3)

### [题目传送门](https://www.luogu.com.cn/problem/CF741C)

## $\text{Description}$

- 有 $2n$ 个人，排成一个圈，标号为 $i$ 的人的两侧是 $((i-2)\bmod 2n)+1$ 和 $(i\bmod 2n)+1$ 。这 $2n$ 个人两两为一组，一共 $n$ 组。
- 现在让你给这些人编号 $1/2$，要求不存在连续三个人同编号，要求给出染色方案。
- 若不存在输出 $-1$。

## $\text{Solution}$

~~呜呜，模拟赛考了这题考场降智了。~~

考虑强制让 $2i$ 与 $2i-1$ 编号不同。

对每个人建点，我们考虑让编号不同的限制为边，即连边 $2i\to 2i-1$ 与 $2i-1\to 2i$。

同时也在每组人之间连无向边。

有结论该图必能分成二分图。

考虑证明结论。

图能分成二分图的充要条件是该图不存在奇环。

考虑到组限制和相邻限制都对于一个点有恰好一条边。

那么在环上必定是一条组限制边和一条相邻限制边相互交替。

那么环长必定是偶数。

证毕。

因此直接二分图染色即可。

## $\text{Code}$

```cpp
const int N=1e6+5;
int n,a[N]={2},cnt,hd[N],b[N],g[N];
struct edge{int nxt,t;}es[N<<2];
inline void add(int x,int y){es[++cnt]=(edge){hd[x],y};hd[x]=cnt;}

inline void dfs(int x,int fa){
	a[x]=a[fa]^3;
	for(re i=hd[x];i;i=es[i].nxt)
		if(!a[es[i].t]) dfs(es[i].t,x);
}

// ---------- Assign ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	rd(n);
	for(re i=1;i<=n;++i) add(2*i,2*i-1),add(2*i-1,2*i);
	for(re i=1;i<=n;++i){rd(b[i]);rd(g[i]);add(b[i],g[i]);add(g[i],b[i]);}
	for(re i=1;i<=n*2;++i) if(!a[i]) dfs(i,0);
	for(re i=1;i<=n;++i) wr(a[b[i]]),putchar(' '),wr(a[g[i]]),puts("");
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：violin_wyl (赞：1)

## CodeForces 741C

#### 思路

这题被某模拟赛当成T2，读一遍题，emmm，二分图没跑了。

考虑建图，考场上我第一眼想到的是对每一个对 $(i,i+1)$ 都建一条边，并且对每对情侣之间建一条边，然后跑二分图染色，但这样建边可能会存在奇环，也就意味着原图不能保证是二分图，然后就假掉了。

事实上我们并不需要对每一对相邻的点都建边，转而对类似 $(1,2),(3,4),(5,6)$ 这样的形如 $(i\times2,i\times2+1)$ 的点建边，这样既保证了连续三个之中至少有一对是不一样的，而且也满足一对情侣之间食物不同的要求。

现在我们需要证明一下这样的图不会出现奇环，不难发现唯一有可能产生奇环的情况一定是由一对情侣之间的边贡献的，可以简单分类讨论一下：

- 如果其是形如 $(i\times2\rightarrow i\times2+1)$ 这样边，由于一个人只能有一个配偶（~~其实多个也行嘛~~），那这对情侣就构成了一个**不与外界联通**的偶环（即他们构成独立的联通块），最终这两个人任意分配两种食物即可。
- 我们将这种独立的联通块排除之后（我们把 $(i\times2,i\times2+1)$ 这样的点对称为一个“联通块”），剩下的边一定是介于不同联通块之间的，这种“大联通块”中的所有点都一定有恰好两条出边，而且一个“大联通块”之间的边数一定是偶数条（偶数个点，每个点只有两条出边，一条边会对两个点做贡献，最后的边数一定是偶数个）。我们对这个图跑欧拉回路，根据欧拉回路的定义每个点只可能被经过一次（两条边一条入一条出），所以整个欧拉回路是这个图唯一的环，而且整个欧拉回路构成的大环是有偶数条边的，那么肯定不会构成奇环了。

-------

#### code

 ```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
const int INF = 0x3f3f3f3f;
const int mods = 1e8 - 3;
inline int read ( )
{
    int x = 0, f = 1;
    char ch = getchar ( );
    while (ch < '0' || ch > '9') {if (ch == '-') f = - 1; ch = getchar ( );}
    while (ch >= '0' && ch <='9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar ( );}
    return x * f;
}
int n;
int a[N], b[N];
struct edge{ 
    int ver, nxt;
}e[N << 2];
int head[N << 1], tot;
void add_edge (int u, int v) { e[++tot] = (edge) {v, head[u]}; head[u] = tot;}
bool vis[N << 1];
int ans[N << 1];
void dfs (int u, int col)
{
    ans[u] = col;
    vis[u] = true;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].ver;
        if (vis[v]) continue;
        dfs (v, col ^ 1);
    }
}
signed main()
{
    n = read ( );
    for (int i = 1, u, v; i <= n; i++)
    {
        a[i] = read ( ), b[i] = read ( );
        add_edge (a[i], b[i]);
        add_edge (b[i], a[i]);
    }
    for (int i = 1; i <= n; i++) add_edge (i * 2 - 1, i * 2), add_edge (i * 2, i * 2 - 1);
    for (int i = 1; i <= 2 * n; i++) if (!vis[i]) dfs (i, 0);
    for (int i = 1; i <= n; i++) printf ("%d %d\n", ans[a[i]] + 1, ans[b[i]] + 1);
    return 0;
}
 ```

###### CSP2021 rp++

---

## 作者：BBD186587 (赞：1)

首先，在题目中给出的每一组的两个人之间连边。设这些边为 1 类边。

其次，连上所有编号形如 $2x-1$ 和 $2x$ 的人之间的边。设这些边为 2 类边。

对新图跑二分图染色即可。

若能跑出一个结果，则结果的正确性显然。下面证明这个图一定是一个二分图。

首先，给出二分图的定义：对于一个二分图，能将点集分为两个集合，使得这两个集合内部的点没有连边。

根据这个定义，可以得到一个性质：二分图不存在长度为奇数的环。若没有这样的环，则它一定是一个二分图。

（每条边都是从一个集合走到另一个集合，只有走偶数次才可能回到同一个集合）

对于新图中的两个点，$2x-1$ 和 $2x$，假设在加上它们之间的边之前，它们之间就已经有路径了。

假设路径是从 $2x-1$ 到 $2x$ 的。

可以发现，它们都不可能再有向外的 2 类边了，所以路径的第一条边一定是 1 类边。

走到一个新点，因为一个点只可能和另一个点在同一组中，所以这个点不可能有向外的 1 类边了，所以路径的第二条边一定是 2 类边。

以此类推，这条路径中的边的类型一定形如：1 类，2 类，1 类，2 类 $\cdots$。

同时，一定是由一条 1 类边到达路径的终点 $2x$ 的。

所以，这条路径的长度为奇数，连上这条新边后形成一个长度为偶数的环。

所以，这个图中不存在长度为奇数的环，它是二分图。故问题一定有解，且这样做一定能解出一组解。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
const int N=1e6+10;
int n,a[N],b[N],ans[N];
vector <int> e[N];
void dfs(int x,int y)
{
	ans[x]=y;
	for(int i=0;i<e[x].size();i++)
		if(!ans[e[x][i]]) dfs(e[x][i],1-y);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[i]=x,b[i]=y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	for(int i=1;i<=n*2;i+=2)
	{
		e[i].push_back(i+1);
		e[i+1].push_back(i);
	}
	for(int i=1;i<=n*2;i++)
		if(!ans[i]) dfs(i,0);
	for(int i=1;i<=n;i++)
		printf("%d %d\n",ans[a[i]]+1,ans[b[i]]+1);
	return 0;
}
```

---

## 作者：Digital_Sunrise (赞：0)

## 思路

设两个有边相连的点颜色不同。

将情侣之间连边，对于 $i\in[1,n]$ ，将 $2i+1$ 和 $2i$ 连边（这样能满足相邻三个人两个人的菜不同），得到一个二分图。

原因是任何一个环都是由若干条情侣边和若干条“3人”边互相交错而成，所以不存在奇环。

然后跑二分图染色即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int _ = 2e5 + 5;

int n;
int u[_],v[_],col[_];
vector<int> G[_];
bitset <_> vis;

void dfs(int u,int v)
{
    col[u] = v;
    vis[u] = 1;
    for(int i = 0;i < G[u].size();i++)
    {
        int v_ = G[u][i];
        if(!col[v_])
			dfs(v_,3 - v);
    }
}
int main()
{
    cin >> n;
    for(int i = 1;i <= n;i++)
    {
        cin >> u[i] >> v[i];
        G[u[i]].push_back(v[i]);
        G[v[i]].push_back(u[i]);
    }
    for(int i = 1;i <= n;i++)
    {
        G[i * 2 - 1].push_back(i * 2);
        G[i * 2].push_back(i * 2 - 1);
    }
    for(int i = 1;i <= n * 2;i++)
	{
		if(!vis[i])
			dfs(i,1);
	}
    for(int i = 1;i <= n;i++)
		cout << col[u[i]] << " " << col[v[i]] << endl;
	return 0;
}
```

---

## 作者：xfrvq (赞：0)

我们建出一个图，使得图中有边的两点颜色不同。

首先情侣之间连（$\tt1$ 类边）。

接着 $\forall i\in[1,n]$，$2i$ 和 $2i-1$ 连，因为这样等价于相邻三个不能相同（$\tt2$ 类边）。

然后这个东西是二分图。原因是任何一个环都是由若干条 $\tt1$ 类边和若干条 $\tt2$ 类边互相交错而成，所以不存在奇环。

```cpp
const int N = 2e5 + 5;

int n,a[N],b[N],col[N];
vector<int> G[N];

void dfs(int u,int c){
	if(col[u] && col[u] != c)
		printf("-1\n"),exit(0);
	if(col[u]) return;
	col[u] = c;
	for(int v : G[u]) dfs(v,c ^ 1);
}

signed main(){
	read(n);
	rep(i,1,n){
		read(a[i],b[i]);
		G[a[i]].push_back(b[i]);
		G[b[i]].push_back(a[i]);
	}
	rep(i,1,n){
		int x = 2 * i,y = 2 * i - 1;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	rep(i,1,2 * n) if(!col[i]) dfs(i,0);
	rep(i,1,n) printf("%d %d\n",col[a[i]] + 1,col[b[i]] + 1);
	return 0;
}
```

---

## 作者：Wilson_Lee (赞：0)

## 思路

这是一道裸的二分图判定题，这里考虑使用染色法。

对于限制一：显然情侣之间要连一条边。

对于限制二：考虑将编号为 $i\times2-1$ 和 $i\times2$ 的人之间连一条边，这样一定能保证每 $3$ 个人吃的食物都不一样（毕竟是构造题，找最特殊的情况）。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;
struct node
{
    int a,b;
}cp[MAXN];
vector<int>G[MAXN<<1];
int col[MAXN<<1];
bool bfs(int s)
{
    queue<int>q;
    col[s]=1,q.push(s);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(auto y:G[x])
        {
            if(!col[y]) col[y]=3-col[x],q.push(y);
            else if(col[y]==col[x]) return 0;
        }
    }
    return 1;
}
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;++i) scanf("%d %d",&cp[i].a,&cp[i].b),G[cp[i].a].push_back(cp[i].b),G[cp[i].b].push_back(cp[i].a);
    for(int i=1;i<=n;++i) G[i*2-1].push_back(i*2),G[i*2].push_back(i*2-1);
    for(int i=1;i<=n*2;++i)
    {
        if(col[i]) continue;
        if(!bfs(i))
        {
            printf("-1");
            return 0;
        }
    }
    for(int i=1;i<=n;++i) printf("%d %d\n",col[cp[i].a],col[cp[i].b]);
    return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：0)

考虑直接来一种更 trick 的限制，即连边 $(2i - 1,2i)$，这样就可以保证三人之中至少有两人不相同。               

称如上连接的图为原图。

接着你发现根据题目的连边要求无论再怎么连边都无法生成奇环：因为每个点的度数为 $2$ 所以若生成一个环毕然每个点一进一出，而同时我们发现如果视情侣之间的连边是一种抽象意义上的“连接”关系，那么可以把环上的所有点拆分为若干组原图的 $(2i - 1,2i)$ 连边关系的点对（因为你都生成环了所以必然选择了原图的边），这样就保证了当前环的大小必然是偶数。    

然后直接二分图染色。             


```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 4e5 + 5;
int n,m,head[Len],cnt,vis[Len];
struct node
{
	int next,to;
}edge[Len << 1];
void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
void dfs(int x)
{
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(vis[to]) continue;
		vis[to] = 3 - vis[x];
		dfs(to);	
	}
}
struct Node
{
	int x,y;
}Edge[Len << 1];
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++) 
	{
		int x,y;scanf("%d %d",&x,&y);
		add(x , y) , add(y , x);
		Edge[i].x = x , Edge[i].y = y;
	}
	for(int i = 1 ; i <= n ; i ++) add(2 * i - 1 , 2 * i) , add(2 * i , 2 * i - 1);
	for(int i = 1 ; i <= (n << 1) ; i ++) 
	{
		if(!vis[i])
		{
			vis[i] = 1;
			dfs(i);
		}
	}
	for(int i = 1 ; i <= n ; i ++) printf("%d %d\n",vis[Edge[i].x],vis[Edge[i].y]);
	for(int i = 1 ; i <= 2 * n ; i ++) head[i] = vis[i] = 0;
	cnt = 0;
	return 0;
}
```

---

## 作者：huangxianghui (赞：0)

不得不说，二分图的题，你什么时候都得注意点：千万记得判一下图是否联通（~~为此不惜牺牲掉 $O(n)$ 的复杂度~~）

### Solution

首先情侣必然连线（吃不同的食物）

其次，由于特性（spj），我们可以随便构造一个二分图来满足第二条约束条件（即三人里必有两人吃不同的食物）~~做构造题实在太快乐了~~

此处规定：在 $2i-1$ 与 $2i$ 之间连一条边，这样能保证第二约束条件

#### 重点：如何证明构造出来的图保证是二分图？

要保证存在二分图，必须保证该图不存在奇环。而首先情侣关系产生 $n$ 条边，我们构造的时候又产生 $n$ 条边，保证不会出现奇环

代码走起：

```
#include<bits/stdc++.h>
#define ll long long
#define f(i,a,b) for (ll i=a;i<=b;i++)
#define fx(i,a,b) for (ll i=a;i>=b;i--)
#define HgS 998244353
using namespace std;
const int maxn=2e5+10;
int n;
int a[maxn];
vector<int> v[maxn];
int num[maxn];
queue<int> q;
inline ll read()
{
	ll l=0,f=1;
	char c;
	while (!isdigit(c=getchar())) if (c=='-') f=-1;
	while (isdigit(c)) l=(l<<3)+(l<<1)+(c^48),c=getchar();
	return l*f;
}
signed main()
{
	n=read()*2;
	for (int i=1; i<=n; i+=2) v[i].push_back(i+1),v[i+1].push_back(i);
	f(i,1,n/2)
	{
		a[i*2-1]=read(),a[i*2]=read();
		v[a[i*2-1]].push_back(a[i*2]),v[a[i*2]].push_back(a[i*2-1]);
	}
	f(i,1,n)
	{
		if (!num[i])
		{
			q.push(i),num[i]=1;
			while (!q.empty())
			{
				int x=q.front();
				q.pop();
				f(i,0,v[x].size()-1)
				{
					if (!num[v[x][i]]) num[v[x][i]]=((num[x]==1)?2:1),q.push(v[x][i]);
				}
			}
		}
	}
	for (int i=1; i<=n; i+=2) printf("%d %d\n",num[a[i]],num[a[i+1]]);
	return 0;
}
```


---

