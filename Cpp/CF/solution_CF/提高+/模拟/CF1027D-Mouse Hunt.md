# Mouse Hunt

## 题目描述

伯兰州立大学的医学部刚刚结束了招生活动。和以往一样，约80%的申请人都是女生并且她们中的大多数人将在未来4年（真希望如此）住在大学宿舍里。

宿舍楼里有$n$个房间和**一只老鼠**！女孩们决定在一些房间里设置捕鼠器来除掉这只可怕的怪物。在$i$号房间设置陷阱要花费$c_i$伯兰币。房间编号从$1$到$n$。

要知道老鼠不是一直原地不动的，它不停地跑来跑去。如果$t$秒时它在$i$号房间，那么它将在$t+1$秒时跑到$a_i$号房间，但这期间不会跑到别的任何房间里($i=a_i$表示老鼠没有离开原来的房间)。时间从$0$秒开始，一旦老鼠窜到了有捕鼠器的房间里，这只老鼠就会被抓住。

如果女孩们知道老鼠一开始在哪里不就很容易吗？不幸的是，情况不是这样，老鼠在第$0$秒时可能会在从$1$到$n$的任何一个房间内。

那么女孩们最少要花多少钱设置捕鼠器，才能保证老鼠无论从哪个房间开始流窜最终都会被抓到？

## 样例 #1

### 输入

```
5
1 2 3 2 10
1 3 4 3 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1 10 2 10
2 4 2 2
```

### 输出

```
10
```

## 样例 #3

### 输入

```
7
1 1 1 1 1 1 1
2 2 2 3 6 7 6
```

### 输出

```
2
```

# 题解

## 作者：Siyuan (赞：8)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[Codeforces 1027D](https://codeforces.com/contest/1027/problem/D)

有 $n$ 间屋子和 $1$ 只老鼠，老鼠会从第 $i$ 间房子跑到 $a_i$ 间房子。在每间房子放捕鼠夹都有代价 $c_i$，而老鼠的初始位置可能是任何一个房间，为了保证抓到老鼠（无论老鼠在哪个房间，总有一种路径会经过有捕鼠夹的房子），你需要在若干房间放上捕鼠夹，求最小代价和。

数据范围：$1\leqslant a_i\leqslant n\leqslant 2\cdot 10^5$，$1\leqslant c_i\leqslant 10^4$

---

## Solution

想象成是一张 $n$ 个点、$n$ 条边的基环图，对于每个弱连通块单独处理。

对于第 $i$ 个点，记录是否访问过，如果它还没有答案（起点在 $i$ 时已经能在某个房间抓到老鼠）则进行 $\text{DFS}$。在搜索的过程中，如果遇到了一个已经访问过的点，则说明出现了环。这个环的答案为“搜索中遇到的所有点（用栈维护）的代价最小值”。

代码中， $vis[i]$ 记录是否访问过（用于判环），$mark[i]$ 记录是否已经有答案（用于判断是否需要 $\text{DFS}$）

**时间复杂度**：$\Theta(n)$

---

## Code

```cpp
#include <cstdio>
#include <algorithm>
#include <cctype>
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)

char in() {
    static char buf[1000001],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
template <class Tp> void read(register Tp &s) {
    s=0;
    register bool neg=0;
    register char c;
    while(!isdigit(c=in())) if(c=='-') neg=1;
    while(s=(s<<3)+(s<<1)+c-48,isdigit(c=in()));
    s=(neg?-s:s);
}

const int N=200005;
int n,a[N],c[N],tot,hd[N],las[N],sz,m,st[N],x[N];
bool vis[N],mark[N];
struct Edge{
    int to,nxt;
}e[N<<1];

void add(int u,int v) {
    e[++tot].to=v;
    e[tot].nxt=hd[u];
    hd[u]=tot;
}
void findloop(int u) {
    if(vis[u]) {
        x[++m]=u;
        while(sz&&st[sz]!=u) x[++m]=st[sz],--sz;
        return;
    }
    vis[u]=1; st[++sz]=u; findloop(a[u]);
}
void dfs(int u) {
    mark[u]=1;
    for(int i=hd[u];i;i=e[i].nxt) if(!mark[e[i].to]) dfs(e[i].to);
}
int main() {
    read(n);
    FOR(i,1,n) read(c[i]);
    FOR(i,1,n) {
        read(a[i]);
        add(i,a[i]); add(a[i],i);
    }
    int ans=0;
    FOR(i,1,n) {
        if(mark[i]) continue;
        sz=0; m=0;
        findloop(i);
        int res=(1<<30);
        FOR(j,1,m) res=std::min(res,c[x[j]]);
        ans+=res;
        dfs(i);
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：starseven (赞：7)

[同步于我的博客](https://www.cnblogs.com/starseven/p/13052121.html)

[题目链接](https://codeforces.com/problemset/problem/1027/D)

[luogu链接](https://www.luogu.com.cn/problem/CF1027D)

这道题的简略题意是:

有一个$n$个点，$n$条边的有向图（可能有自环和重边），叫我们以最小代价选取一些点，使得无论从哪个点出发都要经过这些点。

思路：

因为有n个点，n条边，所以说我们可以知道一定至少有一个环。

而对于一条链来说，这条链必然要通向一个环！

所以我们就可以先进行topo排序，将所有的链删去，然后进行dfs来寻找环内的最大值！

$$ Talk \;is\;cheap,\;show\;the\;code\;!$$

```cpp
#include<cstdio>
#include<iostream>
#define ri register int
#define Starseven main
using namespace std;
const int N=2e5+20;
int n,m,cost[N],ans=0,k,to[N],du[N];
bool vis[N];

void Topo(int x){
	vis[x]=true;
	du[to[x]]--;
	if(!du[to[x]]) Topo(to[x]);
}

int Dfs(int x){
	vis[x]=true;
	if(!vis[to[x]]) return min(Dfs(to[x]),cost[x]);
	else return cost[x];
}

int Starseven(void){
	cin>>n;
	for(ri i=1;i<=n;i++) cin>>cost[i];
	for(ri i=1;i<=n;i++){
		int x;cin>>x;
		to[i]=x,du[x]++;
	}
	for(ri i=1;i<=n;i++) if(!du[i]&&!vis[i]) Topo(i);
	for(ri i=1;i<=n;i++) if(!vis[i]) ans+=Dfs(i);
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Diamiko (赞：5)

# 缩点

请看下图

![](https://cdn.luogu.com.cn/upload/image_hosting/zaec0m25.png)

我们在脑中想象一下这个过程，我们会发现，老鼠如果跑进一个强连通分量，那它一定会经过这个强连通分量内的所有点，那我们只需要在一个强连通分量中任意一个点放置一个捕鼠夹，就可以捕捉到进入这个强连通分量的老鼠。

所以一个强连通分量在图中就相当于一个点。

在上图中，$(6,7)$构成一个强连通分量，$(2,3,4)$构成一个强连通分量，我们发现，老鼠只要进入$5$或$1$，就一定会进入$(6,7)$或$(2,3,4)$，并且无法再跑出来。

那要是$7$向$4$有一条边呢？

那老鼠就可以从$(6,7)$跑到$(2,3,4)$，但在$(2,3,4)$中不会出来了。

那么就有一个显然易见的结论，在把所有的强连通分量缩成一个点后，我们只需要在所有出度为$0$的点设置捕鼠夹就可以捕获所有的老鼠，而强连通分量我们只要在其中任意一个点放置捕鼠夹就可以了，所以答案就是所有出度为$0$的强连通分量中花费最小的点权之和。

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
vector<int>G[N];
int deep,dfn[N],low[N],col[N],colcnt,out[N],val[N];
bitset<N>in_stack;
stack<int>st;
int n,cost[N],x;
vector<pair<int,int>>edge;
void Tarjan(int u)
{
	dfn[u]=low[u]=++deep;
	st.push(u);
	in_stack[u]=1;
	for(int v:G[u])
	{
		if(!dfn[v])
		{
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(in_stack[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		int top;
		colcnt++;
		do
		{
			top=st.top();
			st.pop();
			col[top]=colcnt;
			in_stack[top]=0;
			val[colcnt]=min(val[colcnt],cost[top]);
		}
		while(top!=u);
	}
}
int main()
{
	memset(val,0x3f,sizeof val);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&cost[i]);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		G[i].push_back(x);
		edge.push_back(make_pair(i,x));
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			Tarjan(i);
	for(pair<int,int> e:edge)
	{
		int u=e.first,v=e.second;
		if(col[u]!=col[v])
		{
			out[col[u]]++;
		}
	}
	int ans=0;
	for(int i=1;i<=colcnt;i++)
	{
		if(out[i]==0) ans+=val[i];
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Mickey_snow (赞：4)

[CF1027D](www.codeforces.com/problemset/problem/1027/D) _Mouse Hunt_ : 模拟

题目大意：有一只老鼠在女生宿舍的某一个房间中，女生们希望抓住它，现在我们知道了如果老鼠第 $i$ 秒在房间 $s$ 中，那么到了第 $i+1$ 秒它将到达 $next_i$ 号房间，此过程中不经过任何其它的房间，房间编号从 $1$ 到 $n$ .我们不知道一开始老鼠在哪个房间中，但是可以花费 $cost_i$ 的代价在 $i$ 号房间布置陷阱。布置的陷阱需要满足无论老鼠一开始在那个房间中，最后都会落入陷阱，在此基础之上，要求这个尽可能少的代价 $\sum cost_i$ .

我们将老鼠走的路径抽离出来，发现有三种情况：

1. 老鼠从一个房间 $s$ 出发，走过一条链，到达一个房间 $t$ 满足 $next_t = t$ ,此后一直停留在 $t$.
2. 老鼠从一个房间 $s$ 出发，走过一个环，又回到 $s$ ,此后一直这样循环。
3. 老鼠从一个房间 $s$ 出发，先走过一条链到达 $t$ 这时进入一个环，走了若干步又回到 $t$ ,如此循环。

对于不同的情况，很好设计对策：

1. 唯一的方法是在 $t$ 布置陷阱，在其它地方布置只可能花费更高的代价。
2. 在环中选择一个代价最小的房间布置陷阱。
3. 同2，链接这个环的链可以去掉不看。

这样，无论老鼠一开始在哪个房间，都会最终落入陷阱当中，实现可以依靠暴力。从一个点 $s$ 不停地往下走，我们将这称作第 $s$ 次模拟，同时记录一个数组 $vis_i$ 代表 $i$ 号房间是在哪一次模拟当中经过的，每到达一个房间就将这个房间的 $vis$ 赋值为 $s$ .如果遇到了一个房间 $j$ 满足 $vis_j < s$ 证明这条路走下去一定有一个陷阱(在此之前布置的)，直接 break 掉。如果到达一个房间 $j$ 满足 $next_j = j$ 对应情况1，在$j$ 布置陷阱。如果到达一个房间 $j$ 满足 $vis_j = s$ 对应情况 2 或 3，从这里开始将整个环遍历一遍，找出一个最小值。

由于每一个点我们只赋了一次 $vis$ ，以后看到它就直接停止走下去了，算上判环每个点经过至多2次(算上判环3次)，时间复杂度为 $O(N)$.

具体的实现细节见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 200050
int nxt[MAXN], cost[MAXN];
int vis[MAXN];

int getMin(int start) {
	int _min = cost[start];
	for (int i = nxt[start];; i = nxt[i]) {
		if (i == start)return _min;
		else _min = min(_min, cost[i]);
	}
}

int main()
{
	memset(vis, false, sizeof(vis));

	int totRooms, _min; long long _count = 0;
	cin >> totRooms;

	for (int i = 0; i < totRooms; i++)scanf("%d", cost + i);
	for (int i = 0; i < totRooms; i++) {
		cin >> nxt[i]; nxt[i]--;
		if (nxt[i] == i) { vis[i] = -1; _count += cost[i]; }
	}

	for (int start = 0; start < totRooms; start++) {
		if (vis[start] != 0)continue;

		_min = cost[start];
		for (int i = start;; i = nxt[i]) {
			if (vis[i] != 0) {
				if (vis[i] == start + 1)_count += getMin(i);
				break;
			}
			vis[i] = start + 1; 
			_min = min(_min, cost[i]);
		}
	}

	cout << _count << endl;

	//system("pause");
	return 0;
}
```

---

## 作者：0xFF (赞：3)

#### 题目大意


------------
有 $n$ 间屋子和 $1$ 只老鼠，老鼠每次会从第 $i$ 间屋子跑到第 $a_i$ 间屋子。在每间屋子放置一个捕鼠夹都有一个代价值 $c_i$，在若干的房间放置捕鼠夹使得一定可以抓到老鼠，最小化放置捕鼠夹的代价之和。

#### 思路分析


------------

![](https://cdn.luogu.com.cn/upload/image_hosting/75r1ectl.png)

观察样例 $1$ 可以发现选择 $1$ 和 $4$ 这两点是最优策略，因为无论从哪一个点出发，最后必然可以到达这两个点，所以选择这两个点是最优的。

由于题设中图是有 $n$ 个点和 $n$ 条边的有向图，所以必定存在环。观察样例不难发现该图是由若干个环构成的，每一个图都是一个强连通分量，考虑对整张图进行缩点，因为老鼠必定会进过强连通分量中的每一个点。进一步的考虑，缩点之后只需要在出度为 $0$ 的点处放置捕鼠夹就必然可以捕到老鼠，因为老鼠必然不可能从该点再去往其他的点。由于我们只需要在每个强连通分量中的任意一个点放置捕鼠夹就能满足题设，所以答案就是所有出度为 $0$ 的点的权值之和。

#### 代码实现


------------

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#define int long long
using namespace std;
const int N = 200010;
const int INF = 0x3f3f3f3f;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
struct edge{
	int to,next;
}edge[N];
int head[N],cnt=1;
inline void add(int u,int v){
	edge[++cnt].next = head[u];
	edge[cnt].to = v;
	head[u] = cnt;
}
int n,a[N];
int dfn[N],low[N],timeclock;
int belong[N],color,minv[N];
int stk[N],top;
bool vis[N];
inline void tarjan(int u){
	dfn[u] = low[u]=++timeclock;
	vis[u] = 1;
	stk[++top] = u;
	for(int i = head[u];i;i = edge[i].next){
		int v = edge[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u] = min(low[u],low[v]);
		}
		if(vis[v])
			low[u] = min(low[u],dfn[v]);
	}
	if(low[u] == dfn[u]){
		belong[u] = ++color;
		while(stk[top] != u){
			belong[stk[top]] = color;
			minv[color] = min(minv[color],a[stk[top]]);
			vis[stk[top--]] = 0;
		}
		minv[color] = min(minv[color],a[stk[top]]);
		vis[stk[top--]] = 0;
	}
}
int ans = 0;
int out[N],to[N];
signed main(){
	n = read();
	for(int i=1;i<=n;i++)
		a[i] = read(),minv[i] = INF;
	minv[0]=INF;
	for(int i=1;i<=n;i++){
		to[i] = read();
		add(i,to[i]);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	for(int i=1;i<=n;i++){
		if(belong[i] != belong[to[i]])
			out[belong[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(out[belong[i]] == 0){
			ans += minv[belong[i]];
			minv[belong[i]] = 0;
		}	
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：huangxianghui (赞：2)

# 题意
每个房间有一个老鼠，老鼠会按固定路线乱窜，求在哪些房间布置老鼠夹在既能抓到老鼠的情况下又能使代价最小
# solution
说实话我一开始想到的竟然是并查集……当然很明显，你用并查集并不能维护这道题目所需答案。

那怎么办？~~暴力解决一切~~

首先我们可以知道，从一个点开始，一条路走下去（假设没有环），使抓这只老鼠的代价最小，老鼠夹只能设在路的尽头，这样的代价肯定最小（你中间只要断一下代价就会加，因为后面一段还是要抓老鼠的）。

再来看环，因为是个环，老鼠跑到哪都会被抓，所以这里可以取路径上最小代价。

怎么判环？鉴于我不会什么缩点，所以直接暴力（~~反正不会炸~~）

```
f(i,1,n)//宏定义不要管他……^_^，枚举每个点作为路径的开始往下走
	{
		int num=i;//指针
		while (!l[num]) l[num]=i,num=a[num];//没到之前走过的路上就往下走
		if (l[num]==i)//到环了，走到之前走过的路上了
		{
			int num1=num,minn=0x7f7f7f7f;//再重走一遍环
			do
			{
				minn=min(minn,c[num1]),num1=a[num1];
			}
			while (num1!=num);
			do
			{
				c[num1]=minn,a[num1]=num;//优化，把环拆了，全部指向最小值的点
			}
			while (num1!=num);
		}
	}
```
由于这里我需要知道每一轮有哪些点走过，并且不能和之前的重上，所以我直接用数字标记了（只要空间不炸一切好说）

接下来就是轻松愉快的暴力了
```
f(i,1,n)
	{
		int num=i;
		while (!b[num]) b[num]=i,num=a[num];//跟刚才一样
		if (b[num]==i) ans+=c[num];//如果和之前走的路重复就不要设老鼠夹了，因为之前设过了
	} 
```
总代码
```
#include<bits/stdc++.h>
#define f(i,a,b) for (int i=a;i<=b;i++)
#define ll long long
using namespace std;
const int maxn=2e5+10;
int n,ans;
int a[maxn],c[maxn];
int l[maxn],b[maxn];
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
	n=read();
	f(i,1,n) c[i]=read();
	f(i,1,n) a[i]=read();
	f(i,1,n)
	{
		int num=i;
		while (!l[num]) l[num]=i,num=a[num];
		if (l[num]==i)
		{
			int num1=num,minn=0x7f7f7f7f;
			do
			{
				minn=min(minn,c[num1]),num1=a[num1];
			}
			while (num1!=num);
			do
			{
				c[num1]=minn,a[num1]=num;
			}
			while (num1!=num);
		}
	}
	f(i,1,n)
	{
		int num=i;
		while (!b[num]) b[num]=i,num=a[num];
		if (b[num]==i) ans+=c[num];
	} 
	printf("%d",ans);
}
```
tip：记得暴力的时候请加快读等各种稀奇古怪的常数优化


---

## 作者：Priori_Incantatem (赞：2)

根据题目给出小老鼠去向的方式，我们可以发现每一个点只有一条出边，而这些边构成的图就是一条链  
对于这条链，我们发现链的尾端有可能为一个环（如下图）
![image.png](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pLmxvbGkubmV0LzIwMTkvMTIvMTIvUWJPM2VWSVJhOVNtWXRGLnBuZw?x-oss-process=image/format,png)
又因为每个点只能有一条出边，所以这个环不可能在链的中间

这样，答案就被转换成了链尾端的强联通分量中的最小点权

```cpp
#include<cstdio>
#include<iostream>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;
const int Maxn=200000+10,inf=0x3f3f3f3f;
vector <int> e[Maxn];
stack <int> s;
int a[Maxn],f[Maxn],minv[Maxn];
int dfn[Maxn],low[Maxn],ind[Maxn];
bool vis[Maxn];
int n,timecnt,ans;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
void tarjan(int x)
{
	dfn[x]=low[x]=++timecnt;
	vis[x]=1,s.push(x);
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i];
		if(!dfn[y])
		{
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(vis[y])low[x]=min(low[x],low[y]);
	}
	if(dfn[x]==low[x])
	{
		while(s.size())
		{
			int y=s.top();
			s.pop();
			f[y]=x,vis[y]=0;
			minv[x]=min(minv[x],a[y]);
			if(x==y)break;
		}
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	n=read();
	for(int i=1;i<=n;++i)
	a[i]=read();
	for(int i=1;i<=n;++i)
	{
		int x=i,y=read();
		e[x].push_back(y);
	}
	fill(minv+1,minv+1+n,inf);
	for(int i=1;i<=n;++i)
	if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<e[i].size();++j)
		{
			int x=i,y=e[i][j];
			if(f[x]==f[y])continue;
			ind[f[x]]++;  //这里ind[]存的是出度，原谅我ind写惯了
		}
	}
	for(int i=1;i<=n;++i)
	{
		if(f[i]!=i || ind[i])continue;
		ans+=minv[i];
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：zsc2003 (赞：2)


- codeforces div 2 D
- 2018.8.18

- 题目大意：
- 有n个房间，保证每一个房间只会通向另一个房间(可能会通向自己，可能有多个房间通向一个房间)
- 有一只老鼠，初始房间不一定，它会在相通的房间内乱窜
- 你有无数个老鼠夹，可以放到任意房间内，保证老鼠已进入该房间就会被抓住，在不同的房间内放老鼠夹都会有一个对应的代价
- 请你计算：最少花费多少的代价，才能保证老鼠不管初始在哪个房间内都会被抓住

- 做法：
- 首先建图：让第i个房间指向它所能到的房间的编号to[i]，然后使用tarjan缩点，将图变为DAG后，统计每一个强连通分量的出度数（一定要是该点所在的强连通分量的出度数！！！！）
- 然后只需要统计出度数为0的强连通分量内的最小代价即可

- 样例1建好图的模样如下
- 红色的是代价
![](https://cdn.luogu.com.cn/upload/pic/29532.png)

- 具体的细节详见我的代码

- 下面附上我的代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline void read(int &x)
{
	x=0;
	char ch=getchar();
	bool flag=0;
	while('0'>ch||ch>'9')
	{
		if(ch=='-')
			flag=1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	if(flag)
		x=-x;
}
const int N=210000,inf=1e9+7;
int n,f;
int a[N];
struct edge
{
	int to,next;
}mem[N];
int head[N],cnt=1;
inline void add(int u,int v)
{
	mem[++cnt].next=head[u];
	mem[cnt].to=v;
	head[u]=cnt;
}
int dfn[N],low[N],t;
int scc[N],color,minn[N],num[N];
bool vis[N];
int st[N],top;
inline void tarjan(int u)//使用tarjan缩点
{
	dfn[u]=low[u]=++t;
	vis[u]=1;
	st[++top]=u;
	for(int e=head[u];e;e=mem[e].next)
	{
		int to=mem[e].to;
		if(!dfn[to])
		{
			tarjan(to);
			low[u]=min(low[u],low[to]);
		}
		if(vis[to])
			low[u]=min(low[u],dfn[to]);
	}
	if(low[u]==dfn[u])
	{
		scc[u]=++color;
		while(st[top]!=u)
		{
			scc[st[top]]=color;
			minn[color]=min(minn[color],a[st[top]]);
			vis[st[top--]]=0;
		}
		minn[color]=min(minn[color],a[st[top]]);//minn数组标记该强连通分量内的最小花费
		vis[st[top--]]=0;
	}
}
int ans=0;
int out[N],to[N];
int main()
{
	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]),minn[i]=inf;//先将每个强连通分量的最小花费清为正无穷
	minn[0]=inf;
	for(int i=1;i<=n;i++)
	{
		read(to[i]);
		add(i,to[i]);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);//tarjan缩点
	for(int i=1;i<=n;i++)
	{
		if(scc[i]!=scc[to[i]])
			out[scc[i]]++;	//统计每一强连通分量的出度个数
	}
	for(int i=1;i<=n;i++)
	{
		if(!out[scc[i]])//如果某一强连通分量的出度为0，那么这个强连通分量内必须放一个捕鼠器，代价是该强连通分量内的最小代价
		{
			ans+=minn[scc[i]];
			minn[scc[i]]=0;//为防止出现某一强联通分量内重复放入的情况，在选取过一次后将最小赋为0
		}	
	}
	printf("%d\n",ans)；
	return 0;
}
```

---

## 作者：RuntimeErr (赞：1)

### 直入主题

我们要在一个 $n$ 个点 $n$ 条边的有向图里找到找到一些点，使得无论从哪个点出发都会至少经过这些点中的一个。

也就是说，无论从哪个点出发最终都会引向您找到的这些点。由于 $n$ 条边一定会出现**环**，我们需要**缩点**，答案就是**出度为 $0$** 的强连通分量中的元素**最小值之和**。用 tarjan 算法做的时间复杂度是 $O(n+m)$。

### $Code:$

```cpp
#include<cstdio> 
#include<iostream>
#include<vector>
using namespace std;

const int N=2e5+10,inf=0x7fffffff;

int n,c[N],a[N],du[N];
vector<int>e[N];
int dfn[N],low[N],tim,stk[N],top,id[N],minn[N],cnt;
bool in_stk[N];

void tarjan(int u){
	dfn[u]=low[u]=++tim;
	stk[++top]=u;in_stk[u]=true;
	for(int i=0;i<e[u].size();++i){
		int v=e[u][i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		minn[++cnt]=inf;int v;
		do{
			v=stk[top--];
			id[v]=cnt;in_stk[v]=false;
			minn[cnt]=min(minn[cnt],c[v]);
		}while(v^u);
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&c[i]);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		e[i].push_back(a[i]);
	}
	for(int i=1;i<=n;++i)if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;++i){
		if(id[i]^id[a[i]])++du[id[i]];
	}
	int ans=0;
	for(int i=1;i<=cnt;++i)if(!du[i])ans+=minn[i];
	printf("%d",ans);
	return 0;
}
```


---

## 作者：DrownedFish (赞：1)

### 缩点

根据老鼠跑房间的方向建立一张有向图，则图的边数为 $n$ ，且每个点的出度都是 $1$。


易知老鼠从任意起点开始跑必定通向某一个环，而且最后会停留在这个环里。

- 对于环内的点：选择费用最小的设置捕鼠器即可。

- 对于环外的点：一定通向一个环，通向的环里有捕鼠器，所以不用另外设置。


缩点时，以环上价值最小的点为缩点后的费用。得到的新图中，出度为 $0$ 的点即是原来的环，所有出度为 $0$ 的点价值和即答案。


------------


### **Code**

```
#include <bits/stdc++.h>
#define maxn 200050
#define maxm 200050
#define INF 2147483647
#define I zx(i)
#define F zx(e[i].fr)
#define T zx(e[i].to)
using namespace std;

int vis[maxn],f[maxn];
int val[maxn],ans,ou[maxn];

int n,m,hd[maxn],cne,cnt,a,b;
struct edge{int to,nx,fr;} e[maxm];
void Add(int u,int v)
{
	cne++;
	e[cne].fr=u;
	e[cne].to=v;
	e[cne].nx=hd[u];
	hd[u]=cne;
}

// 并查集实现的缩点
int zx(int x)
{return f[x]==x? x:f[x]=zx(f[x]);}

void dfs(int x)
{
	for(int i=hd[x];i;i=e[i].nx)
	{
		int t=e[i].to;
		if(!vis[t]) vis[t]=vis[x]+1,dfs(t);
		int fx=zx(x),ft=zx(t);
		if(vis[ft]>0)
		{
			if(vis[fx]<vis[ft]) f[ft]=fx;
			else                f[fx]=ft;
		}
	}
	vis[x]=-1;
}

int main()
{
	ios::sync_with_stdio(0); cin>>n;
	
	for(int i=1;i<=n;i++) {cin>>val[i]; f[i]=i;}
	for(int i=1;i<=n;i++) {cin>>a; Add(i,a);}
	// 缩点
	for(int i=1;i<=n;i++) if(!vis[i]) vis[i]=1,dfs(i);
	for(int i=1;i<=n;i++) val[I]=min(val[I],val[i]);   // 选花费最少的
	// 统计
	for(int i=1;i<=n;i++) if(F!=T) ou[F]++;            // 记录出度 
	for(int i=1;i<=n;i++) if(I==i && !ou[i]) ans+=val[i];
	
	cout<<ans<<endl; return 0;
}

```

---

## 作者：Nero_Claudius (赞：1)

这道题原本写了一个很复杂的DFS，然后陷入绝望的调试。

看了一下题解发现自己完全想复杂了。

这里大概就是补充一些题解没有详细解释的代码吧。。。

------------

（小声BB）现在最优解rank4（话说O2负优化什么鬼啊）

```cpp
read(n);
for(register int i=1;i<=n;++i)read(c[i]);
for(register int i=1;i<=n;++i){
	read(a[i]);
	if(a[i]==i){
		vis[i]=1;
		ans+=c[i];
	}
}
for(register int i=1;i<=n;++i){
	if(vis[i])continue;
	for(register int j=i;;j=a[j]){
		if(vis[j]){
			if(vis[j]==i+1)ans+=find(j);
			break;
		}
		vis[j]=i+1;
	}
}
write(ans);
```

程序主题内容如下。

前面是读入数据没有什么好讲的。

在读入a的时候先判断一下有没有自环，有的话就不用看了直接加上。

然后我们对每一个点都瞎搞搞（其实就是一个DFS）。

我们从这个点开始一直向下跳。如果遇到已经走过的点就说明有环出现了，这个时候根据vis的值决定是不是这一轮跳出的环（由于可能是之前的）。

然后我们在这个环上跑一下求最小值。（为什么只在环上不在链上前面题解讲得很清楚了）

如果不是已经走过的点，那我们还在链上，继续往下跳吧。

find函数如下：

```cpp
inline int find(int s){
	int res=c[s];
	for(register int i=a[s];;i=a[i]){
		if(i==s)return res;
		else res=min(res,c[i]);
	}
}
```

------------

祝大家$NOIP2018^{RP++}$

---

## 作者：Plozia (赞：0)

宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/113756104)

先容我吐槽一句：话说老鼠竟然变成了可怕的怪物。。。。。。有那么可怕吗？~~好吧还真有~~

开始正题。

显然这是一道图论题。

我们将 $n$ 个房间视为 $n$ 个点，将 $(i,a_i)$ 连一条边。

那么问题就变成了：在一张有向图上，每个点都有权值 $c_i$，选取一些点使得所有点沿边行动过程中一定会碰上这些点，求最小权值和。

这不是就变成了求环上最小权值吗？

为什么？

首先对于一个环（包括自环），如果环上有一个点被选中，那么其余点都能到这个点。

那么那些不在环上的呢？由于每一个点恰好有一条出边，那么不在环上的点总能到达在环上的点。

于是问题解决。我们把环找出来，然后取出权值最小的点即可。

这里有两种思路：

1. 基环树森林。~~但是我不会啊~~
2. 拓扑排序+并查集。

大致思路就是先使用拓扑排序删除不在环上的点，剩下的点合并，取出最小值，求和。

代码：

```cpp
#include <bits/stdc++.h>
#define Min(a, b) ((a < b) ? a : b)
using namespace std;

typedef long long LL;
const int MAXN = 2e5 + 10;
int n, c[MAXN], a[MAXN], cnt[MAXN], fa[MAXN];
LL ans, v[MAXN];
bool book[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

int gf(int x) {return (fa[x] == x) ? x : (fa[x] = gf(fa[x]));}
void hb(int x, int y) {if (gf(x) != gf(y)) fa[fa[x]] = fa[y];}

void topsort()
{
	queue <int> q;
	for (int i = 1; i <= n; ++i)
		if (cnt[i] == 0) {book[i] = 1; q.push(i);}
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		cnt[a[x]]--;
		if (cnt[a[x]] == 0) {book[a[x]] = 1; q.push(a[x]);}
	}
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i) c[i] = read();
	for (int i = 1; i <= n; ++i) {cnt[a[i] = read()]++;}
	topsort();
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int i = 1; i <= n; ++i)
		if (!book[i] && !book[a[i]]) hb(i, a[i]);
	for (int i = 1; i <= n; ++i) fa[i] = gf(i);
	for (int i = 1; i <= n; ++i) v[i] = 0x7f7f7f7f;
	for (int i = 1; i <= n; ++i) v[fa[i]] = Min(v[fa[i]], c[i]);
	for (int i = 1; i <= n; ++i)
		if (fa[i] == i && !book[i]) ans += (LL)v[i];
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：LXH5514 (赞：0)

## CF1027D

### 题目大意

n个房间，有一只老鼠在期间穿梭，但他在某一个房间的时候，下一秒跳到的房间是确定的，也就是有固定的顺序$a_i$。我们要放置老鼠夹，然后将它抓住，每个房间放置老鼠夹的费用不同。但我们不知道老鼠一开始在哪个房间，因此要求出无论老鼠在哪里都能将他抓住并且费用最低的方案。数据范围：$1\le n \le 2*1e5$。

### 思路

如果老鼠要从a房间跳到b房间，那么无论b房间和a房间的费用如何，在b房间放老鼠夹一定更划算，因为你在a房间放老鼠夹，那么你就不能维护b房间，一次呢还要再在b房间再放一个，而你如果只在b房间放一个，那么你同时也维护了a房间。

举个例子

```cpp
6
1 1 1 1 1 1
1 1 1 2 2 6
```

![img](https://cdn.luogu.com.cn/upload/image_hosting/6njv1h4o.png))

~~图很丑~~ 在1放老鼠夹最划算且1是必选的，他可以维护所有的房间，而你如果选了其他的房间，那么就不能维护1房间，所以还是要选1，因此直接选1就行了。

OK，讲到这里，思路就很明显了，你要找到每一个点的父亲节点，然后在那个房间放就好了。那么就是并查集，就是将每个并查集的根的价值加起来就好了。

~~口糊完毕~~，但当你仔细写时，你会发现一些问题。让我们来看样例1.

```cpp
5
1 2 3 2 10
1 3 4 3 3
```

![img](https://cdn.luogu.com.cn/upload/image_hosting/0826e9pq.png)

你会发现4连向3这条边，很特别，貌似不满足并查集性质。一开始我想着这种边不管就行了，但是再仔细想就不对劲了。

对于2345这个并查集，3可以维护所有的点，4也可以维护所有的点，他两个是等价的，因此他俩都是这个并查集的根，那你放老鼠夹得肯定是两个中小的那一个，因此就将他俩比较一下。但不是只比较他们两个，如果3和4之间还有其他的点，那么他们和3，4，也是等价的，因此要将这个环进行路径压缩，将这个环上的最小值记录在跟上，相当于缩成一个点。

```cpp
#include<iostream>
#include<stdio.h> 
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+f*(c-'0'),c=getchar();
	return x;
}
const int MAXN=2*1e6+10;
int a[MAXN],b[MAXN];
struct node
{
	int f,v;
}d[MAXN];
int n,ans;
int cz(int x)
{
	if(d[x].f==x)return x;
	int y=cz(d[x].f);
	d[x].v=min(d[x].v,d[d[x].f].v);
	d[x].f=y;//路径压缩 
	return y;
}
void hb(int x,int y)
{
	
	int l,r;
	l=cz(x);
	r=cz(y);
	if(l!=r)
	d[x].f=y;//如果不是特殊的边，就是没有环，就正常合并
	//说实话，路径压缩不是特别会写。 
	else
	{
		d[x].v=d[y].v;//缩点，将环上的最小值记录到根上。 
	}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	a[i]=read();
	for(int i=1;i<=n;i++)
	d[i].f=i,d[i].v=a[i];//并查集初始化。 v数组记录这个点到根路径上的最小值，方便合并的时候用。 
	for(int i=1;i<=n;i++)
	{
		int x;
		x=read();
		hb(i,x);
	}
	for(int i=1;i<=n;i++)
	{
		ans+=d[cz(i)].v;//将每个并查集的根的值加起来 
		d[cz(i)].v=0;
	}
	printf("%d\n",ans);
return 0;
}
```



---

## 作者：Segmentree (赞：0)

我们可以将这道题分解为两个子任务依次分析

1. “保证老鼠无论从哪个房间开始流窜最终都会被抓到” 
2. "最少要花多少钱设置捕鼠器"

**对于子问题1**

我们阅读题干如果将老鼠流窜的路线保存为一张图，那么就能将子问题1转为“求出度为0的连通分量的个数”

如下图（对应样例1）：

图中有强连通分量（1）（2）（3,4）（5）

其中有出度为0的点的强连通分量有（3,4）（1）

因此我们只需要再其中寻找子问题二的解即可
![](https://s2.ax1x.com/2019/08/13/mCj8YD.png)


**对于子问题2**

我们只需要在子问题1找到的强连通分量中找到代价最小的点即可。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define c getchar()
#define r(x) x=read()
#define ll long long
inline int read()
{
    int w=1,s=0;
    char ch=c;
    while(ch>'9'||ch<'0'){if(ch=='-')w=-1;ch=c;}
    while(ch>='0'&&ch<='9')s=(s<<1)+(s<<3)+ch-'0',ch=c;
    return s*w;
}
const int maxn=2e5+1;
stack <int> s;
bool flag[maxn];
int tot[maxn];
int dis[maxn],vis[maxn],dfn[maxn],low[maxn],scc[maxn],head[maxn],ans,cnt,num,outqueue[maxn],min_tot[maxn],paid;
struct node
{
    int to,next;
}edge[maxn<<1];
inline void add(int from,int to)
{
    edge[++cnt].next=head[from];
    edge[cnt].to=to;
    head[from]=cnt;
}
inline void tarjan(int u)//tarjan求强连通分量
{
    dfn[u]=low[u]=++num;
    s.push(u),vis[u]=1;
    for(re int i=head[u];i;i=edge[i].next)
    {
        int v=edge[i].to;
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
            continue;
        }
        if(vis[v])low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        int v;
        ans++;
        do{v=s.top(),s.pop(),vis[v]=0,scc[v]=ans,min_tot[ans]=min(min_tot[ans],tot[v]);}while(u!=v);
    }//这里用min_cost来记录每个强连通分量中的最小代价
}
int n;
int main()
{
    memset(tot,0x3f,sizeof(tot)),
    memset(min_tot,0x3f,sizeof(min_tot));
    r(n);
    for(re int i=1;i<=n;++i)r(tot[i]);
    for(re int i=1,u;i<=n;++i)r(u),add(i,u);
    for(re int i=1;i<=n;++i)if(!dfn[i])tarjan(i);
    for(re int i=1;i<=n;++i)
        for(re int j=head[i];j;j=edge[j].next)
        {
            int v=edge[j].to;
            if(scc[i]!=scc[v])++outqueue[scc[i]],min_tot[scc[i]]=min_tot[scc[i]]>min_tot[scc[v]]?min_tot[scc[i]]:min_tot[scc[v]];
        }//缩点求每个强连通分量的出度,再次维护强连通分量中的最小代价
    for(re int i=1;i<=ans;++i)
    {
        if(!outqueue[i])paid+=min_tot[i];//累加出度为0所在强连通分量中的最小代价
    }
    cout<<paid;//完结撒花
}
```


---

