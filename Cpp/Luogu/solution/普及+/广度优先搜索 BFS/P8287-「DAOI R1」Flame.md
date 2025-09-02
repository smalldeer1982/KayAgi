# 「DAOI R1」Flame

## 题目背景

>尝尝天堂里的苹果有什么了不起，我要尝尝地狱里的苹果。

## 题目描述

黑暗里有黑色的火焰，只有目光敏锐的人才可以捕捉到,

借着这点卑微之光,走进地狱深处......

欢迎来到地狱的审判之地。

$ \texttt{hhpq.} $ 将 D 押入了地狱的审判之地，D 必须在业火之城成功生成一座业火监狱之前逃离，所以他想知道还有多少秒时间。

在这座业火之城中，共有 $n$ 个祭坛，共有 $m$ 条可以蔓延火苗的业火之路，且业火之路是双向连通。

已知在这一座业火之城共有 $k$ 个火种已被点燃的业火祭坛，且从第一秒开始，火种将开始从被点燃的业火祭坛向可以蔓延且未被点燃的业火祭坛蔓延。

当祭坛被点燃后，则会瞬间激活，和与之有路的祭坛连接业火圣壁。

当存在一片由业火圣壁构成的封闭图形时，则业火监狱生成成功。

### 简化题意
给出一个 $n$ 个点，$m$ 条边的无向图，每一个点有一个标记，初始有 $k$ 个点的标记为 `1`（将给出这 $k$ 个点的编号），其余的点标记为 `0`。

每一秒，对于每个标记为 `1` 的点，与它**有边相连**的点的标记都会变成 `1`。

求最少需要多少秒，图中标记为 `1` 的点与其相邻的边可以构成一个简单环。

**换言之，求最少多少秒后存在一个由 `1` 构成的集合形成简单环。**

## 说明/提示

### 样例解释

#### 样例1解释

当时间到第一秒时，祭坛 $1$ 的火焰将蔓延到祭坛 $2$ 和 $3$，此时已经构成一个封闭图形了，故答案为 $1$。

#### 样例2解释

可以证明到此时是无法产生简单环的。

### 数据规模

| Subtask | $n\leq$ | $m\leq$ | $k\leq$ | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $10^6$ | $n-1$ | $10^4$ | $5$ |
| $1$ | $10^6$ | $2\times10^6$ | $1$ | $10$|
| $2$ | $10$ | $45$ | $1$ | $5$ |
| $3$ | $200$ | $500$ | $10$ | $10$ |
| $4$| $2\times 10^3$ | $5\times 10^3$ | $50$ | $10$ |
| $5$ | $5\times10^5$ | $6\times10^5$ | $500$ | $30$ |
| $6$ | $10^6$ | $2\times10^6$ | $10^4$ | $30$ |

### 保证与约定

保证数据无重边和自环；

保证数据给定的图是一张无向连通图。

### 帮助

输入量较大，建议使用较为快速的读入方式。

## 样例 #1

### 输入

```
3 3 1
1 2
2 3
3 1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 4 2
1 2
2 3
3 4
2 5
1 5
```

### 输出

```
Poor D!
```

## 样例 #3

### 输入

```
15 15 2
2 1
2 3
2 9
5 9
4 5
5 7
6 7
7 8
7 11
11 10
10 9
10 14
14 15
11 12
12 13
4 15
```

### 输出

```
3
```

# 题解

## 作者：Augen_stern (赞：12)

题目的意思就是求在某个时间时，图中有效边可以构成至少一个简单环；

可以注意到无解的情况存在且只存在于原图是一棵树的情况：$m=n-1$。

暴力我们就抛开不论了，这里提几种有意思的做法：

## $\mathcal{O}(m\log m)$ $100 pts$

不难发现可以用二分去枚举时间。

所以我们可以先对源点进行多起点求到全图所有点的最短路；

接下来我们有两种思路：

1. 根据图的定义，统计每一个联通块的边数和点数，根据树与环的定义来判断答案。

2. 用 Tarjan 来统计环，直接暴切！

在此再次感谢验题人 [Erinyes](https://www.luogu.com.cn/user/444235) 对本题的巨大贡献。

## $\mathcal{O}(m)$ $100pts$

我们可以发现，上述做法中的 $m$ 有点过大，注意到 $k$ 较小，发现二分其实是多余的，我们可以直接模拟整个蔓延过程，用宽搜遍历实现，并在其中用类似于最短路算法一样不断更新遍历到的结点（提前预处理出最短路的话没必要但可行）；

接着用并查集，将每一个源点记作一个集合，当两不同集合相遇时则合并；

若不相同，则更新答案，取时间最小值，顺带一提，此时直接输出是错误的。

此时的并查集若只考虑使用**路径压缩**，那么时间复杂度会退化 $\mathcal{O}(m\log m)$，也是可以接受的；

更好的，若要考虑 $\mathcal{O}(m)$，则须使用**按秩合并**。

且对于此时的时间复杂度，接近于 $\mathcal{O}(m)$。（注意到，就遍历一张图的时间；由于并查集的时间复杂度为反阿克曼函数，所以也就是常数时间。）

通过上述做法，可以 AC。

为了追求极致的最优解，我们可以发现在某个时间点后，遍历到的点时间将超过答案；

所以我们可以用**记忆化**来优化，只要搜到答案后，如果当前起始点的时间不比答案小，那么程序运行结束；

当然这种优化的极限复杂度还是 $\mathcal{O}(m)$ 级别，但由于 $n$ 较小，特殊构造可以为 $k=1$ 且在一条链的一端，而构造一个完全图（甚至只有一个三元环）在另一端，但这样要么使 $m$ 和 $n$ 差不多大，要么使最后的答案变小。综上，这无法使优化退化，就当是一种玄学优化吧。

在此再次感谢验题人 [jinqihao2023](https://www.luogu.com.cn/user/529491) 和 [leihonglongyin](https://www.luogu.com.cn/user/440943) 对本题的巨大贡献。

代码如下：

并查集：

```cpp
int find(int x){
	if(fa[x]==x) return x;
	fa[x]=find(fa[x]);
	return fa[x];
}
void merge(int a,int b){
	int x=find(a),y=find(b);
	if(x==y) return;
	if(rank[x]<=rank[y]) fa[x]=y,rank[y]=max(rank[y],rank[x]+1);
	else fa[y]=x,rank[x]=max(rank[x],rank[y]+1);
} // 按秩合并 路径压缩（其实只需要路径压缩就行了）
signed main() {
	for(int i=1;i<=n;i++) fa[i]=i,rank[i]=i;
}
```

宽搜：

```cpp
signed main() {
	while(!q.empty()){
		int x=q.front(); q.pop();
		if(dis[x]>ans) break; // 记忆化
		for(int i=h[x];i;i=t[i].next){
			if(vst[i]) continue;
			int y=t[i].to;
			dis[y]=min(dis[y],dis[x]+1); // 更新时间
			vst[i]=vst[i^1]=1; // 不走回路
			if(!c[y]) c[y]=c[x], q.push(y); // 蔓延
			else{
				if(find(c[x])==find(c[y])) ans=min(ans,dis[y]);
				else merge(c[x],c[y]); // 合并
			}
		}
	}
}
```


---

## 作者：我是逍逍 (赞：8)

#### 题目大意  
在一个由 $n$ 个点，$m$ 条边组成的无向图中有 $k$ 个源点，每个源点的流扩散速率都为 $1$ ，求最早形成简单环的时间。
#### 吐槽  
一看到环，立刻就想到了 $Tarjan$ 算法，但是不知为何打炸了，也没有在题解里看到类似的做法（没看懂），如有解法，欢迎留言赐教。
#### 算法概述  
使用广搜模拟扩散过程，使用并查集维护扩散源关系：
- 若某一已扩散节点 $x$ 与带扩散节点 $y$ 同属于一个集合中，则此次扩展已经成环，统计答案。
- 若不满足条件，则将 $x$ 与 $y$ 所在集合合并，为未来统计答案做准备。
- 特别的，如果数据为树形结构，即 $m = n - 1$ ，那么可以直接判定无解。由于题目保证图联通，因此其它情况均有解。

搜索过程中，记录 $dis_x$ 表示节点 $x$ 与其最近的源点的距离， $vis_x$ 表示节点 $x$ 是否已经扩展过， $f_x$ 记录节点 $x$ 所在的集合编号。  
注：此题的输入数据量较大，建议使用快读，下方代码中使用 `sync_with_stdio(false)` 关闭流同步，勉强能过。  
#### 代码
```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int Max = 1000005;

int n, m, k, ans = Max, f[Max], dis[Max];
vector<int> g[Max];
queue<pair<int, int>> q;
bool vis[Max];

int father(int x) { // 并查集 
	if (f[x] == x)
		return x;
	return f[x] = father(f[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    
    if (m == n - 1) { // 判定无解 
        cout << "Poor D!" << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++) // 并查集初始化 
    	f[i] = i;

    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    for (int i = 1, x; i <= k; i++) {  
        cin >> x;
        q.push(make_pair(x, 0)); // 搜索由 k 个源点同时开始 
        dis[x] = 1;
    }

	while (!q.empty()) {
		int x = q.front().first; // 当前节点 
		int fa = q.front().second; // 父节点 
		q.pop();
		if (vis[x])  
			continue;
		vis[x] = true;
		
		for (auto y: g[x]) 
			if (y != fa) { // 跳过父节点 
				if (!dis[y]) {
					dis[y] = dis[x] + 1;
					q.push(make_pair(y, x));
					f[father(y)] = father(x);
				} else if (!(dis[y] + 1 == dis[x] || (vis[y] && dis[y] == dis[x]))) {
					if (father(y) == father(x)) // 已经同属一个集合 统计答案 
						ans = min(max(dis[y], dis[x]) - 1, ans);
					else
						f[father(y)] = father(x);
				}
			}
	}
	
	cout << ans << endl;
	return 0; 
}

```


---

## 作者：Icyfires18 (赞：5)

### 题意

给定无向连通图 $G(n,m)$ 以及 $k$ 个流源点，流扩散速率为 $1$ ，求形成流环路的最早时间。

### 思路

算法：模拟，广搜，并查集；

先观察一下题面，完全可以轻松得出一种暴力解法：

依次模拟每秒的扩散操作，每秒结束后判断是否形成环路，成功则输出答案。

对于模拟扩散操作，显而易见是裸的**广搜图遍历**。

至于环路判断，也无需每秒结束后进行全图找环，在每次扩散时即时判断成环即可。

显然能看出这是**子图连通性问题**，若当前待扩散节点与扩散节点早已连通（即属于相同连通块），则此次扩散可成环。

于是便可引出专门解决这类问题的经典算法——[**并查集**](https://www.luogu.com.cn/problem/P3367)。

具体地说，在广搜时同步维护并查集，在每次扩散时利用其查询判断，扩散结束后合并双方节点各自的点集，代表双方连通。

而扩散的时间，既可以选择在外部用 for 循环变量广搜记录，也可以记录每个点的扩散时间，答案取成环扩散双方节点的较大值。

说了那么多，其实这题思路就不难，题意形式和暗示都很明显，可以一眼看出，下面说一下代码实现的细节处理。

时间复杂度：$O(m+n\alpha(k))$，$k$ 为常数，$\alpha$ 为反阿克曼函数。

### 代码

[记录](https://www.luogu.com.cn/record/73594484)

1. 为避免产生回流误判的情况，故须删除流过的边，使其不会反向流回来，详见 len 数组；

2. 搜到的第一个环不一定是正解，队列内与其时间记录相同的节点都筛选后才能确定正解；

3. 由于初始化 lab 值为 1（原应为 0 ），故输出时减回；

```cpp
#include<cstdio>
#include<queue>
using namespace std;
const int INF=0x7fffffff;
const int N=1000001;
const int M=4000001;
int cnt=1,beg[N],nex[M],go[M];//链式前向星存图
int n,m,k,ans,lab[N],fa[N];
//lab为该点被扩散到的用时，fa为并查集
//广搜过程中 lab 时间是递增的
bool len[M];//表示边的存在，0为无，1为有
queue<int>Q;
inline void fip(int &rer){
	register char ch;
	for(ch=0;ch<'0'||ch>'9';ch=getchar());
	for(rer=0;ch>='0'&&ch<='9';ch=getchar())
		rer=(rer<<3)+(rer<<1)+(ch^48);
}
void fop(int wer){
	if(wer>9)fop(wer/10);
	putchar(wer%10+48);
}
inline void adde(int u,int v){
	nex[++cnt]=beg[u],beg[u]=cnt,
	go[cnt]=v,len[cnt]=1;
	nex[++cnt]=beg[v],beg[v]=cnt,
	go[cnt]=u,len[cnt]=1;
}
int findfa(int u){
	if(fa[u]==u)return u;
	return fa[u]=findfa(fa[u]);
}
int main(){
	register int i,u,v,fu,fv;
	scanf("%d%d%d",&n,&m,&k);
	if(n>m){puts("Poor D!");return 0;}
   	//特判若为树即直接输出
	for(i=1;i<=n;++i)fa[i]=i;//并查集初始化
	for(i=1;i<=m;++i)fip(u),fip(v),adde(u,v);
	for(i=1;i<=k;++i)fip(u),Q.push(u),lab[u]=1;//广搜初始化
	for(ans=INF;!Q.empty();Q.pop()){
		u=Q.front();//出队
		if(lab[u]>ans)break;//时间超过答案就退出
		for(i=beg[u];v=go[i];i=nex[i]){
			if(!len[i])continue;//不走回头路
			fu=findfa(u),fv=findfa(v);
			if(fu==fv)ans=min(ans,max(lab[u],lab[v]));//更新
			fa[fv]=fu,len[i^1]=0;//合并，删边
			if(!lab[v])Q.push(v),//入队
				lab[v]=lab[u]+1;//记录
		}
	}printf("%d",ans-1);
	return 0;
}
```

**Thx for reading:)**

---

## 作者：Binary_Lee (赞：5)

## [题面传送门](https://www.luogu.com.cn/problem/P8287)

### 解决思路

本题解是对 [这篇题解](https://www.luogu.com.cn/blog/0MIRACLES0/solution-p8287) 部分内容的补充，讨论的是两种 $\mathcal{O(m \log n)}$ 的做法。

大体思路都是一样的，先预处理出每一条边需要多少时间后才能连上，可以用 $\text{BFS}$ 实现。

然后二分答案时间，在每个时间下连接当前已经通的边。设点 $i$ 第一次被“点燃”的时间为 $dis_i$，当前二分的时间为 $t$，则 $(u,v)$ 联通的条件是 $dis_u\le t \land dis_v\le t$，然后再新图上判断是否有环即可。

---

首先是 $\text{Tarjan}$。本题数据范围较大，而且 $\text{Tarjan}$ 常数较大，需要快读 $+$ 邻接表才能通过。

具体实现就是常规的 $\text{Tarjan}$，做完一个点 $x$ 之后，若 $low_x<dfn_x$，说明它可以通过非树边到达其祖先，也就是存在环了。另外，因为二分答案做多次 $\text{Tarjan}$，所以每次要清空！

### AC Code（Tarjan）

```cpp
//If, one day, I finally manage to make my dreams a reality...
//I wonder, will you still be there by my side?
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define y1 cyy
#define fi first
#define se second
#define cnt1(x) __builtin_popcount(x)
#define mk make_pair
#define pb push_back
#define pii pair<int,int>
#define psi pair<string,int>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define lbt(x) (x&(-x))
using namespace std;
int n,m,k,u[2000005],v[2000005],b,dis[1000005];
int dfn[1000005],low[1000005],timer,head[4000005],tot,Head[1000005],Tot;
int stk[1000005],top,col[1000005];
bool mark[1000005],vis[1000005],fl;
struct node{
	int to,nxt;
}e[4000005];
struct NODE{
	int to,nxt;
}E[4000005];
queue<int> q;
inline char gc(){
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	char c=gc();int res=0,f=1;
	for(;c<'0'||c>'9';c=gc()) if(c=='-')f=-1;
	for(;c>='0'&&c<='9';c=gc()) res=res*10+c-'0';
	return res*f;
}
inline void write(int x){
	static int sta[205],top=0;
	if(x<0)putchar('-'),x=-x;
	do{sta[top++]=x%10;x/=10;}while(x);
	while(top) putchar(sta[--top]+48);
}
inline void writesp(int x){
	write(x);putchar(' ');
}
inline void writeln(int x){
	write(x);putchar('\n');
}
void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
}
void ADD(int u,int v){
	E[++Tot]={v,Head[u]},Head[u]=Tot;
}
void init(){
	for(int i=1;i<=m*2;i++) head[i]=0;
	for(int i=1;i<=n;i++) dfn[i]=low[i]=col[i]=0,vis[i]=0;
	tot=timer=0,fl=0;
}
void tarjan(int x,int fa){
	if(fl) return ;
	dfn[x]=low[x]=++timer;
	for(int i=head[x];i;i=e[i].nxt){
		int tmp=e[i].to;
		if(tmp==fa) continue;
		if(!dfn[tmp]){
			tarjan(tmp,x);
			if(fl) return ;
			low[x]=min(low[x],low[tmp]);
		}
		else low[x]=min(low[x],dfn[tmp]);
	}
	if(low[x]<dfn[x]){
		fl=1;
		return ;
	}
}
bool check(int mid){
	init();
	for(int i=1;i<=m;i++) if(dis[u[i]]<=mid&&dis[v[i]]<=mid){
		add(u[i],v[i]),add(v[i],u[i]);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) top=0,tarjan(i,0);
	return fl;
}
signed main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;i++){
		u[i]=read(),v[i]=read();
		ADD(u[i],v[i]),ADD(v[i],u[i]);
	}
	for(int i=1;i<=n;i++) dis[i]=1e9;
	for(int i=1;i<=k;i++) b=read(),q.push(b),dis[b]=0;
	while(q.size()){
		int x=q.front();q.pop();
		vis[x]=1;
		for(int i=Head[x];i;i=E[i].nxt){
			int tmp=E[i].to;
			if(vis[tmp]) continue;
			if(dis[tmp]>dis[x]+1){
				dis[tmp]=dis[x]+1;
				q.push(tmp);
			}
		}
	}
	int l=0,r=n,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;	
		else l=mid+1;
	}
	if(ans==-1) puts("Poor D!");
	else writeln(ans);
	return 0;
}
```

---

然后是并查集。并查集在本题中简单很多，而且效率也更高。具体实现就是依次判断每条边，如可以连接的两点已经在同一个连通块中了，就说明有环，否则就连上。同样注意要清空。

### AC Code（DSU）

```cpp
//If, one day, I finally manage to make my dreams a reality...
//I wonder, will you still be there by my side?
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define y1 cyy
#define fi first
#define se second
#define cnt1(x) __builtin_popcount(x)
#define mk make_pair
#define pb push_back
#define pii pair<int,int>
#define psi pair<string,int>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define lbt(x) (x&(-x))
using namespace std;
int n,m,k,u[2000005],v[2000005],b,dis[1000005];
int Head[1000005],Tot;
bool vis[1000005];
struct DSU{
	int fa[1000005];
	void init(int n){
		for(int i=1;i<=n;i++) fa[i]=i;
	}
	int find(int x){
		if(fa[x]==x) return x;
		return fa[x]=find(fa[x]);
	}
	void merge(int x,int y){
		fa[find(x)]=find(y);
	}
	bool query(int x,int y){
		return find(x)==find(y);
	}
}dsu;
struct NODE{
	int to,nxt;
}E[4000005];
queue<int> q;
inline char gc(){
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	char c=gc();int res=0,f=1;
	for(;c<'0'||c>'9';c=gc()) if(c=='-')f=-1;
	for(;c>='0'&&c<='9';c=gc()) res=res*10+c-'0';
	return res*f;
}
inline void write(int x){
	static int sta[205],top=0;
	if(x<0)putchar('-'),x=-x;
	do{sta[top++]=x%10;x/=10;}while(x);
	while(top) putchar(sta[--top]+48);
}
inline void writesp(int x){
	write(x);putchar(' ');
}
inline void writeln(int x){
	write(x);putchar('\n');
}
void ADD(int u,int v){
	E[++Tot]={v,Head[u]},Head[u]=Tot;
}
bool check(int mid){
	dsu.init(n);
	for(int i=1;i<=m;i++) if(dis[u[i]]<=mid&&dis[v[i]]<=mid){
		if(dsu.query(u[i],v[i])) return 1;
		else dsu.merge(u[i],v[i]);
	}
	return 0;
}
signed main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;i++){
		u[i]=read(),v[i]=read();
		ADD(u[i],v[i]),ADD(v[i],u[i]);
	}
	for(int i=1;i<=n;i++) dis[i]=1e9;
	for(int i=1;i<=k;i++) b=read(),q.push(b),dis[b]=0;
	while(q.size()){
		int x=q.front();q.pop();
		vis[x]=1;
		for(int i=Head[x];i;i=E[i].nxt){
			int tmp=E[i].to;
			if(vis[tmp]) continue;
			if(dis[tmp]>dis[x]+1){
				dis[tmp]=dis[x]+1;
				q.push(tmp);
			}
		}
	}
	int l=0,r=n,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;	
		else l=mid+1;
	}
	if(ans==-1) puts("Poor D!");
	else writeln(ans);
	return 0;
}
```

---

## 作者：ICE__LX (赞：2)

题意已经被讲透了，所以这里不再重述，直接讲思路吧。  
### 具体思路
思路：最优性剪枝 bfs。  
bfs 模拟火焰蔓延，用并查集判简单环。为了维护正确性，每通过一条边访问一个结点，就把这条无向边删除。用一个数组记录点权，点权代表从初始结点到达某一结点的最短路径长度（边权为 $1$）。  
### 代码描述
#### 效率优化
为了获得更高的效率，写了快读和宏定义。  

```cpp
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define deap(i,a,b) for(int i=a;i>=b;i--)
#define in(a) a=read()
const int maxn=2e6+5;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
```
#### 并查集与链式前向星存图  
并查集套板子即可。链式前向星建边时，初始化双向链表，方便静态删边。

```cpp
int s[maxn];
inline int find(int x) {//压缩路径并查集查询 
	return s[x]==x?x:s[x]=find(s[x]);
}
struct Edge { //链式前向星存图
	int act,lnex=0,rnex=0;//双向链表实现删边
}*edge;
int head[maxn],eid;
inline void eadd(int u,int v) { //加边
	eid++;
	edge[eid].act=v;
	edge[head[u]].rnex=eid;
	edge[eid].lnex=head[u];
	head[u]=eid;
}
inline void erase(int i,int k) { //静态删边
	edge[edge[i].lnex].rnex=edge[i].rnex;
	if(i!=head[k])
		edge[edge[i].rnex].lnex=edge[i].lnex;
	else head[k]=edge[i].lnex;
}
```
#### 数据读入与一系列初始化

```cpp
queue<int>q;
int ans[maxn];//记录答案 
signed main() {
	memset(ans,0x3f,sizeof(ans));
	int n,m,k;
	in(n),in(m),in(k);
	edge=new Edge[2*m+5];//动态开辟空间
	rep(i,1,m) {
		int u,v;
		in(u),in(v);
		if(u==v)continue;
		eadd(u,v);//建图 
		eadd(v,u);
	}
	rep(i,1,n)s[i]=i;//并查集初始化 
```
#### bfs 求解
模拟题意，用一个数组记录点权，点权代表从初始结点到达某一结点的最短路径长度，即火焰多少秒蔓延到某一结点。  
如果访问的弧头与弧尾属于同一集合，说明找到了一个简单环，答案为弧头与弧尾的点权的中的最大值，如果其优于历史最优解，更新答案。  
同时，如果当前解劣与历史最优解，剪枝。  
每条边被访问后就会被删除，因此时间复杂度为 $O(m)$。
```cpp
rep(i,1,k) {//初始化状态入队 
		int x;
		in(x);
		q.push(x);
		ans[x]=0;
	}
	int best=INT_MAX;
	do {
		int size=q.size();
		while(size--) {
			int u=q.front();
			q.pop();
			for(int i=head[u]; i; i=edge[i].lnex) {
				int v=edge[i].act,x=find(u),y=find(v);
				ans[v]=min(ans[u]+1,ans[v]);//更新点权 
				erase(i,u);//删除无向边 
				erase((i&1)?i+1:i-1,v);
				if(ans[v]>best)continue;//最优性剪枝 
				if(x==y) {//如果找到环 
					best=min(best,max(ans[u],ans[v]));//更新答案 
				}
				s[x]=y;//并查集合并 
				q.push(v);
			}
		}
	} while(!q.empty());
	if(best==INT_MAX)//判断无解 
		puts("Poor D!");
	else cout<<best;
	return 0;
```
### 全代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define deap(i,a,b) for(int i=a;i>=b;i--)
#define in(a) a=read()
const int maxn=2e6+5;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
int s[maxn];
inline int find(int x) {//压缩路径并查集查询 
	return s[x]==x?x:s[x]=find(s[x]);
}
struct Edge { //链式前向星存图
	int act,lnex=0,rnex=0;//双向链表实现删边
}*edge;
int head[maxn],eid;
inline void eadd(int u,int v) { //建边
	eid++;
	edge[eid].act=v;
	edge[head[u]].rnex=eid;
	edge[eid].lnex=head[u];
	head[u]=eid;
}
inline void erase(int i,int k) { //静态删边
	edge[edge[i].lnex].rnex=edge[i].rnex;
	if(i!=head[k])
		edge[edge[i].rnex].lnex=edge[i].lnex;
	else head[k]=edge[i].lnex;
}
queue<int>q;
int ans[maxn];//记录答案 
signed main() {
	memset(ans,0x3f,sizeof(ans));
	int n,m,k;
	in(n),in(m),in(k);
	edge=new Edge[2*m+5];
	rep(i,1,m) {
		int u,v;
		in(u),in(v);
		if(u==v)continue;
		eadd(u,v);//建图 
		eadd(v,u);
	}
	rep(i,1,n)s[i]=i;//并查集初始化 
	rep(i,1,k) {//初始化状态入队 
		int x;
		in(x);
		q.push(x);
		ans[x]=0;
	}
	int best=INT_MAX;
	do {
		int size=q.size();
		while(size--) {
			int u=q.front();
			q.pop();
			for(int i=head[u]; i; i=edge[i].lnex) {
				int v=edge[i].act,x=find(u),y=find(v);
				ans[v]=min(ans[u]+1,ans[v]);//更新点权 
				erase(i,u);//删除无向边 
				erase((i&1)?i+1:i-1,v);
				if(ans[v]>best)continue;//最优性剪枝 
				if(x==y) {//如果找到环 
					best=min(best,max(ans[u],ans[v]));//更新答案 
				}
				s[x]=y;//并查集合并 
				q.push(v);
			}
		}
	} while(!q.empty());
	if(best==INT_MAX)//判断无解 
		puts("Poor D!");
	else cout<<best;
	return 0;
}
```

---

## 作者：DevilsFlame (赞：2)

我的算法是 **并查集**。  
在开始，我们可以求出每个点变成 $1$ 状态的时间。在此我用的是 bfs，dfs 也可以。  
首先要初始化：
```cpp
for(int i = 1;i <= k;i ++)
	{
		read(a);
		s[a] = 0;
		q.push(a);
		vis[a] = 1;
	}
```
宽搜部分：
```cpp
void min_s()
{
	while(!q.empty())
	{
		int x = q.front();
		q.pop();
		for(int i = 0;i < e[x].size();i ++)
		{
			int v = e[x][i];
			if(vis[v]) continue;//判重
			vis[v] = 1;
			s[v] = s[x] + 1;
			q.push(v);
		}
	}
	return;
}
```
题目：**求最少多少秒后存在一个由 $1$ 构成的集合形成简单环。** 每条边可以设置边权为连接两点的最晚变成 $1$ 的时间，我们就先将这些边排序（边权从小到大）。  
排序后，就是并查集。  
如果排序后的前 $N$ 个边能构成环的话，那第 $N$ 边的边权就是我们的答案了。  
如果无解，那么就无环，也是树，判定一下即可。  
```cpp
#include<bits/stdc++.h>
#define N 1000010
#define NN 2000010
#define M 1e9
using namespace std;
vector <int> e[N];
struct Node
{
	int a,b,w;
}l[NN];
int n,m,k,a,b,ans = M,s[N],f[N];
bool vis[N];
int col;
queue <int> q;
void min_s()//宽搜求时间（点变为 1 时刻）
{
	while(!q.empty())
	{
		int x = q.front();
		q.pop();
		for(int i = 0;i < e[x].size();i ++)
		{
			int v = e[x][i];
			if(vis[v]) continue;
			vis[v] = 1;
			s[v] = s[x] + 1;
			q.push(v);
		}
	}
	return;
}
bool rt[N];
inline void read(int &x)//快读（指针）
{
	x = 0;
	int f = 1;
	char s = getchar();
	while(s < '0' || s > '9')
	{
		if(s == '-') f = -1;
		s = getchar();
	}
	while(s >= '0' && s <= '9')
	{
		x = x * 10 + s - 48;
		s = getchar();
	}
	x *= f;
	return;
}
bool cmp(Node x,Node y)
{
	return x.w < y.w;
}
inline int find(int x)
{
	return (f[x] == x ? x : f[x] = find(f[x]));
}
int main()
{
	read(n),read(m),read(k);
	if(m < n)//成树肯定无解
	{
		puts("Poor D!");
		return 0;
	}
	for(int i = 1;i <= m;i ++)
	{
		read(a),read(b);
		e[a].push_back(b);
		e[b].push_back(a);
        l[i].a = a,l[i].b = b;//边
	}
	for(int i = 1;i <= k;i ++)
	{
		read(a);
		s[a] = 0;
		q.push(a);
		vis[a] = 1;
	}
	min_s();//宽搜
	for(int i = 1;i <= m;i ++) l[i].w = max(s[l[i].a],s[l[i].b]);//建边权
	sort(l + 1,l + 1 + m,cmp);//排序
	for(int i = 1;i <= n;i ++) f[i] = i;//初始并查集
	for(int i = 1;i <= m;i ++)
	{
		a = find(l[i].a),b = find(l[i].b);
		if(a == b)//在同一集合（构成环）
		{
			cout << l[i].w << endl;
			return 0;
		}
		else f[a] = b;//合并
	}
	puts("Poor D!");
	return 0;
}
```

---

## 作者：ycy1124 (赞：2)

### 题意
题目讲的很详细，这里不再赘述了。
### 思路
首先发现是要求一个最小值，很容易想到二分答案。考虑 check，发现我们可以把每个点距离业火的最小距离求出来，然后去 dfs 判环。但是我们将 $r=n$ 时 TLE 了。此时发现将 $r$ 初始值设为每个点距离业火的最小距离的最大值即可。

dfs 如何判环，我们可以将到达的每个点标记一下，并且每个点不能向自己的父亲前进，假如有一个点能被标记两次，那么就有环。
### 代码
```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
inline int rint(){//此题卡常。
	register int x(0),f(1);
	char ch=(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++);
	while(!(ch>='0'&&ch<='9'))
		ch=(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++);
	while(ch>='0'&&ch<='9')
		x=x*10+(ch^48),ch=(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++);
	return x*f;
}
vector<int>a[N];
int mid,bj[N];
bool vis[N],qwq[N];
int n,m,k;
struct Node{
    int p,w;
};
queue<Node>q;
bool Check;
// int ans=1e;
int ma=0;
inline void bfs(int p,int w){//每个点距离业火的最小距离
    ma=max(ma,w);
    bj[p]=w;
    for(auto it:a[p]){
        if(!bj[it]){
            bj[it]=w+1;
            q.push({it,w+1});
        }
    }
}
void Dfs(int p,int fa){//dfs判环
    qwq[p]=1;
    if(Check){
        return;
    }
    for(auto it:a[p]){
        if(it==fa){
            continue;
        }
        if(qwq[it]){
            Check=1;
            break;
        }
        if(bj[it]<=mid+1){
            qwq[it]=1;
            Dfs(it,p);
        }
    }
    return;
}
inline bool check(){//check
    Check=0;
    for(int i=1;i<=n;i++){
        qwq[i]=0;
    }
    for(int i=1;i<=n;i++){
        if(qwq[i]||bj[i]>mid+1){
            continue;
        }
        Dfs(i,0);
        if(Check){
            return 1;
        }
    }
    return 0;
}
int main(){
    n=rint(),m=rint(),k=rint();
    for(int i=1;i<=m;i++){
        int u=rint(),v=rint();
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for(int i=1;i<=k;i++){
        int w;
        w=rint();
        vis[w]=1;
    }
    for(int i=1;i<=n;i++){
        qwq[i]=0;
        if(vis[i]){
            q.push({i,1});
        }
    }
    while(!q.empty()){
        bfs(q.front().p,q.front().w);
        q.pop();
    }
    mid=ma;
    if(!check()){//无解
        cout<<"Poor D!";
        return 0;
    }
    int l=0,r=ma,ans;
    while(l<=r){
        mid=((l+r)>>1);
        if(check()){
            ans=mid;
            r=mid-1;
        }
        else{
            ans=l=mid+1;
        }
    }
    cout<<ans;
    return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/191804963)。

---

## 作者：JOKER_chu (赞：1)

## 题意

有一个 $n$ 个点 $m$ 条边的无向图，现在有 $k$ 个点被染成了黑色，每个黑色点在每一时间单位里会将与它相邻的点全部染成黑色，求一个最小的时间 $t$ 使得 $t$ 时间单位后 $n$ 个点全部被染成黑色。

## 解法

先使用多元广搜求出每个点距离最近的黑点的距离，然后使用二分，单调性是显然的，$t$ 时间内能全部染成黑，那么 $t + 1$ 时间内肯定也能全部染成黑，然后思考如何判定可行。

发现可行判定可以先将所有距离最近的黑点 $\leq$ 二分出的时间 $t$ 的点染成黑色，然后使用并查集判断图上是否存在环。具体的，我们对所有两个端点都已经被染成黑色的边讨论，如果当前两个点未在一个集合中，那么将两个点所在的集合合并，否则图上就出现了环。

## 代码

这个做法似乎需要稍微卡一下常才能通过。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

inline int read(){
	int s(0), w(1);
	char ch = getchar_unlocked();
	while (ch < '0' || ch>'9'){
		if (ch == '-')
			w = -1;
		ch = getchar_unlocked();
	}
	while (ch >= '0' && ch <= '9'){
		s = s * 10 + ch - '0';
		ch = getchar_unlocked();
	}
	return s * w;
}

struct State {
  int x, c;
};

struct Edge {
  int x, y;
} e[N << 1];

int n, m, k, a[N], dis[N], fa[N], w[N];

queue<State> que;
vector<int> g[N];

void add_edge( int x, int y ) {
  g[x].push_back(y), g[y].push_back(x);
}

inline int seek( int x ) {
  return fa[x]  == x ? x : fa[x] = seek(fa[x]);
}

inline void inco( int x, int y ) {
  x = seek(x), y = seek(y);
  if (w[x] < w[y]) swap(x, y);
  fa[y] = x, w[x] += w[y], w[y] = 0;
}

inline bool query( int x, int y ) {
  return seek(x) == seek(y);
}

inline bool check( int x ) {
  for (int i = 1; i <= n; ++i) {
    fa[i] = i, w[i] = 1;
  }
  for (int i = 1; i <= m; ++i) {
    if (dis[e[i].x] <= x && dis[e[i].y] <= x) {
      if (query(e[i].x, e[i].y)) {
        return 1;
      } else {
        inco(e[i].x, e[i].y);
      }
    }
  }
  return 0;
}

void Record( int x, int c ) {
  if (dis[x] != INT_MAX >> 1) return ;
  dis[x] = c;
  que.push({x, c});
}

void bfs() {
  fill (dis + 1, dis + n + 1, INT_MAX >> 1);
  for (int i = 1; i <= k; ++i) {
    Record(a[i], 0);
  }
  while (!que.empty()) {
    State u = que.front();
    que.pop();
    for (auto to : g[u.x]) {
      Record(to, u.c + 1);
    }
  }
}

int main() {
  n = read(), m = read(), k = read();
  for (int i = 1, x, y; i <= m; ++i) {
    x = read(), y = read();
    add_edge(x, y);
    e[i] = {x, y};
  }
  for (int i = 1; i <= k; ++i) {
    a[i] = read();
  }
  bfs();
  int l = 0, r = n;
  while (l < r) {
    int mid = l + r >> 1;
    if (check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  if (l != n) {
    cout << l;
  } else {
    cout << "Poor D!";
  }
  return 0;
}

```

---

## 作者：Melo_DDD (赞：1)

据说考试之前发题解会 rp++，马上地生中考，希望好运。
# 题目大意
生成一个封闭图形的意思是图上有环，要求的是最短的生成环的时间。

注意无解的情况是原图是一棵树，不过本人没有特判。
# 题目实现
首先应求出每个祭坛被点燃的时间，采用队列加搜索实现即可。

求的时候注意这个祭坛被点燃的路径可能不唯一，所以应在所有可能中取最小值。

如何判断生成环？采用并查集实现（其实我是冲着 tarjan 来的）。

对于每一个时间节点，我们直接枚举 $m$ 条路径，如果这个路径的两端点在此时均被点燃，且已经处于同一连通块中，把它们连接起来就可以生成环。

注意多测一定要清空。

求最小答案当然要用二分啦。

如何判断无解：二分后答案没有更新说明没有合法方案，就无解。

## 代码

```cpp
#include <bits/stdc++.h>
#define rep(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
const int N = 2e6 + 7 ; // 数组千万别开小
int n ,m ,k ,dis[N] ,u[N] ,v[N] ,head[N << 1] ,tot ,fa[N] ; // dis 就是时间
bool vis[N] ;
struct edge {
	int to ,nxt ;
} e[N << 1] ;
queue <int> q ;
namespace shin {
	template <typename T> inline void read (T &x) {
		x = 0 ;
		char ch = getchar () ;
		while (! isdigit (ch)) {
			ch = getchar () ;
		}
		while (isdigit (ch)) {
			x = (x << 1) + (x << 3) + (ch xor 48) ;
			ch = getchar () ;
		}
	}
	inline void add (int u ,int v) {
		e[++ tot].to = v ;
		e[tot].nxt = head[u] ;
		head[u] = tot ;
	}
	inline void init () {
		rep (i ,1 ,n ,1) {
			fa[i] = i ;
		}
	} // 并查集一定要初始化
	inline int find (int x) {
		return x == fa[x] ? x : fa[x] = find (fa[x]) ;
	}
	inline void dfs () {
		while (! q.empty ()) {
			int cur = q.front () ;
			q.pop () ;
			vis[cur] = true ;
			for (int i = head[cur] ;i ;i = e[i].nxt) {
				int nex = e[i].to ;
				if (vis[nex]) goto her ;
				vis[nex] = true ;
				if (dis[nex] > dis[cur] + 1) {
					dis[nex] = dis[cur] + 1 ;
					q.push (nex) ;
				}
				her : ; 
			}		
		}
	}
	inline bool check (int x) {
		shin :: init () ;
		rep (i ,1 ,m ,1) {
			if (dis[u[i]] <= x and dis[v[i]] <= x) {
				int fu = shin :: find (u[i]) ,fv = shin :: find (v[i]) ;
				if (fu == fv) return 1 ;
				fa[fu] = fv ;
			}
		}
		return 0 ;
	}
}
int main () {
	memset (dis ,0x3f ,sizeof (dis)) ;
	shin :: read (n) ,shin :: read (m) ,shin :: read (k) ;
	rep (i ,1 ,m ,1) {
		shin :: read (u[i]) ,shin :: read (v[i]) ;
		shin :: add (u[i] ,v[i]) ,shin :: add (v[i] ,u[i]) ;
	}
	rep (i ,1 ,k ,1) {
		int num ;
		shin :: read (num) ;
		dis[num] = 0 ;
		q.push (num) ;
	}
	shin :: dfs () ;
	int l = 0 ,r = n ,ans = -2147483647 ;
	while (l <= r) {
		int mid = l + r >> 1 ;
		if (shin :: check (mid)) {
			ans = mid ;
			r = mid - 1 ;
		}
		else l = mid + 1 ;
	}
	if (ans < 0) return puts ("Poor D!") ,0 ;
	return cout << ans << '\n' ,0 ;
}
//kafka & かみや & 申鶴
```

---

## 作者：Nephren_Sakura (赞：1)

题目传送门：[link](https://www.luogu.com.cn/problem/P8287)

因为这是一个无向连通图，所以无解当且仅当原图是一颗树，即 $m=n-1$。

首先，我们可以考虑求出每一个点在多少秒后会被标记，可以简单 bfs 实现。

然后，我们可以发现，因为没有删除操作，所以只要在第 $i$ 秒构成了一个环，在第 $i$ 秒之后这个简单环不可能消失，即答案满足单调性。

所以可以考虑二分答案，然后 check 函数判断当前这个时间有没有出现简单环，这个可以用并查集实现。

具体的实现看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k,dis[1000005],b[1000005],cnt,fa[1000005];
bool vis[1000005];
struct node{
	int x,y;
}a[1000005];
struct edge{
	int tot;
	int head[1000005],to[4000005],next[4000005];
	void add(int x,int y){
		tot++;
		next[tot]=head[x];
		to[tot]=y;
		head[x]=tot;
		return;
	}
}e;
void bfs(){
	queue<int> q;
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	for(int i=1; i<=k; i++)
		dis[b[i]]=0,q.push(b[i]),vis[b[i]]=true;
	while(q.empty()==false){
		int cur=q.front();
		q.pop();
		for(int i=e.head[cur]; i; i=e.next[i]){
			int nxt=e.to[i];
			if(vis[nxt]==false)
				dis[nxt]=dis[cur]+1,vis[nxt]=true,q.push(nxt);
		}
	}
	return;
}
int find(int x){
	if(x==fa[x])
		return x;
	return fa[x]=find(fa[x]); 
}
bool check(int x){
	memset(vis,false,sizeof vis);
	for(int i=1; i<=n; i++)
		fa[i]=i;
	for(int i=1; i<=n; i++)
		if(dis[i]<=x)
			vis[i]=true;
	for(int i=1; i<=n; i++)
		if(vis[i]==true)
			for(int j=e.head[i]; j; j=e.next[j])
				if(i<e.to[j]&&vis[e.to[j]]==true){
					int fx=find(i),fy=find(e.to[j]);
					if(fx!=fy)
						fa[fx]=fy;
					else
						return true;
				}
	return false;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	if(m==n-1){
		cout<<"Poor D!";
		return 0;
	}
	for(int i=1; i<=m; i++)
		cin>>a[i].x>>a[i].y,e.add(a[i].x,a[i].y),e.add(a[i].y,a[i].x);
	for(int i=1; i<=k; i++)
		cin>>b[i];
	bfs();
	int lt=-1,rt=n+1;
	while(lt+1<rt){
		int mid=lt+rt>>1;
		if(check(mid)==true)
			rt=mid;
		else
			lt=mid;
	}
	cout<<rt;
	return 0;
}
```

---

## 作者：eastcloud (赞：1)

## P8287 「DAOI R1」Flame 题解

### 题目分析

题目求的是图中最早出现环的时间，而由题意中每一秒为 1 的点都可以感染周围 0 的点，我们便可以发现如果上一秒没有产生环，呢么新的环便一定由一部分新被感染的点构成。我们便可以通过此性质设计算法。

### 具体做法

通过性质可以简单地想出一个做法，对图进行广度优先遍历，对于每一个队头一边将相连的点加入队列（没搜过的），一边检测是否环由自己构成。

检测环可以通过并查集实现，当在同一集合时更新答案（构成环），否则合并。

### 代码

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
vector<int> l[1000100];
struct Node{
	int root;
	int u;
};
queue<Node> t;
int v[1000100];
int f[1000100];
int vis[1000100];
int ans=10000000;
int find(int x){
	if(x==f[x]) return f[x];
	else return f[x]=find(f[x]);//这里只使用了按秩合并
}
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int main(){
	int x,y,n,m,k;
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=m;i++){
		x=read();y=read();
		l[x].push_back(y);
		l[y].push_back(x);
	}
	for(int i=1;i<=k;i++){
		x=read();
		t.push((Node){0,x});//从初始为1的点开始搜
		v[x]=1;
	}
	int flag=1;
	while(!t.empty()){
		int root=t.front().root,u=t.front().u;//记录当前节点和被谁感染
		t.pop();
		if(vis[u]) continue;
		vis[u]++;//vis标记，v存时间
		for(int i=0;i<l[u].size();i++){
			if(l[u][i]==root) continue;//不重复走
			if(v[l[u][i]]==0){
				v[l[u][i]]=v[u]+1;
				t.push((Node){u,l[u][i]});
				f[find(l[u][i])]=find(u);//感染，合并
			}
			else{
				if(v[l[u][i]]+1==v[u] || (vis[l[u][i]] && v[l[u][i]]==v[u])) continue;//特判
				if(find(l[u][i])==find(u)){
					ans=min(max(v[l[u][i]]-1,v[u]-1),ans);
				}
				else f[find(l[u][i])]=find(u);
			}
		}
	}
	if(ans==10000000) cout<<"Poor D!";
	else cout<<ans;
	return 0;
}

```


---

## 作者：technopolis_2085 (赞：1)

## P8287 「DAOI R1」Flame 题解

简要题意：
初始时有k的点被标记为 $1$，每一秒，对于标记为 $1$ 的点，与它相邻的点变为 $1$。求最少需要多少秒使得存在一个环，环上所有点都被标记为 $1$。


------------
## Analysis:
看到数据范围 $n≤10^6$，$m≤2\times10^6$，考虑二分。
我们发现，如果时间 $x$ 时图上存在环，则时间 $x+1$ 时必然存在环，满足单调性，所以可以二分答案。

预处理出每一个点最早在什么时候标记到，这个过程通过一遍广搜即可实现。

假设当前二分到的答案为 $x$。
如果一条边的两节点都在 $x$ 秒内可以被标记到，则说明这条边可以使用。

筛选出所有可以使用的边之后，就需要判断这些边能否形成环。这里可以使用 tarjan 或者并查集，本篇题解讲解并查集做法。

考虑每一条边，如果节点两端已经在同一个并查集内，则加上这一条边后就一定能形成环；否则就合并两个并查集。

------------
## AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,k;
const int maxn=2e6+10;
struct edge
{
	int u,v;
};
int head[maxn*2],nxt[maxn*2],to[maxn*2];
int E=0;
edge a[maxn];
int fa[maxn];
int dist[maxn];

void add(int u,int v)
{
	E++;
	to[E]=v;
	nxt[E]=head[u];
	head[u]=E;
}

int find(int u)
{
	if (fa[u]==u) return fa[u];
	
	fa[u]=find(fa[u]);
	return fa[u];
}

void bfs()
{
	for (int i=1;i<=n;i++) dist[i]=1e9+7;
	queue<int> q;
	for (int i=1;i<=k;i++)
	{
		int x;
		scanf("%d",&x);
		q.push(x);
		dist[x]=0;
	}
	
	while (!q.empty())
	{
		int u=q.front();
		q.pop();
		
		for (int i=head[u];i;i=nxt[i])
		{
			int v=to[i];
			if (dist[v]>dist[u]+1)
			{
				dist[v]=dist[u]+1;
				q.push(v);
			}
		}
	}
}

bool check(int x)
{
	for (int i=1;i<=n;i++) fa[i]=i;
	for (int i=1;i<=m;i++)
	{
		int u=a[i].u,v=a[i].v;
		if (dist[u]>x||dist[v]>x) continue;
		
		if (find(u)!=find(v)) fa[find(u)]=find(v);
		else return true;
	}
	
	return false;
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	
	for (int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		a[i].u=u,a[i].v=v;
		add(u,v);
		add(v,u);
	}
	
	bfs();
	
	int l=0,r=n;
	int ans=-1;
	
	while (l<=r)
	{
		int mid=(l+r)/2;
		if (check(mid))
		{
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	
	if (ans==-1) printf("Poor D!\n");
	else printf("%d",ans);
	return 0;
}
```


---

## 作者：GJX_Algorithm (赞：0)

# P8287 题解
## 解题思路
- 首先求最少时间，不难想到如果在该时间已经有简单环，那么其之后时间简单环仍然存在，说明它是具有单调性的，就可以对时间进行二分答案。

- 对于二分到的时刻，显然我们只需要跑一遍找是否有简单环即可，那么对于简单环的判定，我们可以：

  1. tarjan 双连通分量。
 
  2. 并查集判环。
 
- 现在我们还缺一个基础东西：每个点被遍历到的时间。我们可以把标记为 `1` 的点设为源点，扩散可以看作边权为一，跑一遍 `BFS` 即可（其实边权为一的 `BFS` 本质上与 `dijkstra` 是一样的，但由于 `dijkstra` 有优先队列，所以 `BFS` 比 `dijkstra` 要快，~~笔者就是因为这个 TLE 了好久~~）。

- 无解情况非常好理解：原图为树。
## AC Code
- 并查集做法：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e6 + 5;
int n, m, k, u[N], v[N];
int fa[N];
int cnt = 1;
struct edge
{
    int y, w;
};
vector<edge> nbr[N];
bool vis[N];
int dis[N];
queue<int> q;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void bfs() //bfs得到点被遍历到的时刻
{
    while (q.empty() == 0)
    {
        int cur = q.front();
        q.pop();
        if (vis[cur] == 1) continue;
        vis[cur] = 1;
        for (auto [nxt, w] : nbr[cur])
        {
            if (dis[nxt] > dis[cur] + w)
            {
                dis[nxt] = dis[cur] + w;
                q.push(nxt);
            }
        }
    }
    return ;
}
int find(int x)
{
    return (fa[x] == x) ? x : fa[x] = find(fa[x]);
}
bool check(int mid)
{
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) //并查集判环
    {
        if (dis[u[i]] > mid || dis[v[i]] > mid) continue;
        int fu = find(u[i]), fv = find(v[i]);
        if (fu != fv) fa[fu] = fv;
        else return 1;
    }
    return 0;
}
int main()
{
    memset(dis, 0x3f, sizeof dis);
    n = read(), m = read(), k = read();
    if (m == n - 1) //原图为树，该数据无解
    {
        printf("Poor D!");
        return 0;
    }
    for (int i = 1; i <= m; i++)
    {
        u[i] = read(), v[i] = read();
        nbr[u[i]].push_back({v[i], 1});
        nbr[v[i]].push_back({u[i], 1});
    }
    for (int i = 1; i <= k; i++)
    {
        int x;
        x = read();
        dis[x] = 0;
        q.push(x);
    }
    bfs();
    int maxi = 0;
    for (int i = 1; i <= n; i++) maxi = max(maxi, dis[i]);
    //二分答案
    int lt = 0, rt = maxi;
    while (lt <= rt)
    {
        int mid = (lt + rt) / 2;
        if (check(mid) == 1) rt = mid - 1;
        else lt = mid + 1;
    }
    cout << rt + 1;
    return 0;
}
```

- tarjan 写法。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 4e6 + 5;
int n, m, k;
int u[N], v[N], dis[N];
int cnt = 1, tot;
int to[N], head[N], Next[N];
int dfn[N], low[N], cut[N];
bool vis[N], flag;
queue<int> q;
vector<int> nbr[N];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void bfs() //bfs得到点被遍历到的时刻
{
    while (q.empty() == 0)
    {
        int cur = q.front();
        q.pop();
        if (vis[cur] == 1) continue;
        vis[cur] = 1;
        for (auto nxt : nbr[cur])
        {
            if (dis[nxt] > dis[cur] + 1)
            {
                dis[nxt] = dis[cur] + 1;
                q.push(nxt);
            }
        }
    }
    return ;
}
void add(int u, int v)
{
    to[++cnt] = v;
    Next[cnt] = head[u];
    head[u] = cnt;
    return ;
}
void tarjan(int cur, int in_edge)
{
    if (flag == 1) return ; //注意，不写会TLE
	dfn[cur] = low[cur] = ++tot;
	for (int i = head[cur]; i; i = Next[i])
	{
		int nxt = to[i];
		if (dfn[nxt] == 0)
		{
			tarjan(nxt, i);
			low[cur] = min(low[cur], low[nxt]);
		}
		else if (i != (in_edge ^ 1))
        {
			low[cur] = min(low[cur], dfn[nxt]);
        }
	}
    if (dfn[cur] > low[cur]) //只要该点可以通过非树边走到之前，就会形成环
    {
        flag = 1;
        return ;
    }
    return ;
}
void init()
{
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(head, 0, sizeof head);
    memset(to, 0, sizeof to);
    memset(Next, 0, sizeof Next);
    memset(dfn, 0, sizeof dfn);
    cnt = 1, flag = tot = 0;
    return ;
}
bool check(int mid)
{
    init();
    for (int i = 1; i <= m; i++)
    {
        if (dis[u[i]] > mid || dis[v[i]] > mid) continue;
        add(u[i], v[i]);
        add(v[i], u[i]);
    }
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i, 0);
    return flag;
}
int main()
{
    memset(dis, 0x3f, sizeof dis);
    n = read(), m = read(), k = read();
    if (m == n - 1) //原图为树，该数据无解
    {
        printf("Poor D!");
        return 0;
    }
    for (int i = 1; i <= m; i++)
    {
        u[i] = read(), v[i] = read();
        nbr[u[i]].push_back(v[i]);
        nbr[v[i]].push_back(u[i]);
    }
    for (int i = 1; i <= k; i++)
    {
        int x;
        x = read();
        dis[x] = 0;
        q.push(x);
    }
    bfs();
    int maxi = 0;
    for (int i = 1; i <= n; i++)
	{
		if (dis[i] == 0x3f3f3f3f) continue; 
		maxi = max(maxi, dis[i]);
	}
    //二分答案
    int lt = 0, rt = maxi;
    while (lt <= rt)
    {
        int mid = (lt + rt) / 2;
        if (check(mid) == 1) rt = mid - 1;
        else lt = mid + 1;
    }
    cout << rt + 1;
    return 0;
}
```

## 修改记录
Update 2024/12/7：新增添 tarjan 做法代码。

---

## 作者：Autumn_Rain (赞：0)

学校模拟赛想到正确思路了没去实现，有点悲伤的一道题。

一步一步慢慢做吧。。。先按照题意模拟建图。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
vector<int>G[N];
int n,m,k;
int x,y,p;
int main(){
	cin>>n>>m>>k;
	while(m--){
		cin>>x>>y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	while(k--){
		cin>>p;
	}
	return 0;
}
```
建完之后想到，题目可以先预处理出每个点染色的时间，然后找到图中的环，取最晚可以染上色的那个就是这个环能形成的时间。用 $t$ 数组记录每个点染色的时间，用队列 $q$ 把所有一开始就染色了的点记录一下。

找环用并查集，对于一条从 $u$ 到 $v$ 的边，如果他们的祖先是同一个，那么他们形成一个环。此时更新这个环中的最大 $t$ 值，把 $u$ 和 $v$ 的都放进去打个擂台。

此时我们的代码变成了这样。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct node{int from,u;};
//from是来时点，u是原先就标为1的那个点
queue<node>q;
vector<int>G[N];
int n,m,k;
int x,y,p;
int t[N],fa[N];
int find(int x){
	if(x==fa[x])return fa[x];
	return find(fa[x]);
}
int main(){
	cin>>n>>m>>k;
  for(int i=1;i<=n;i++){
		fa[i]=i;//并查集初始化
		t[i]=inf;//t初始化为极大值
	}
	while(m--){
		cin>>x>>y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	while(k--){
		cin>>p;
		t[p]=0;
		q.push((node){0,p});
	}
	return 0;
}
```

然后开始搜索每一个原先就染色了的点们，按上面模拟。

```cpp
while(!q.empty()){
	int f=q.front().from;//来时点
	int u=q.front().u;//原先就标为 1 的点
	q.pop();//弹出这个点
	if(vis[u]){//以前处理过了跳过
		continue;
	}
	vis[u]=1;//否则标记访问
	for(int i=0;i<G[u].size();i++){
      	//枚举u连到得所有点,G[u].size就是u到点数量
      	//G[u][i]就是u的第i条连边所到达的点
		int v=G[u][i];//u的到点
		if(v==f){//双向边往回走到了来时点
			continue;
		}
		int fu=find(u);
		int fv=find(v);
      	//找爸爸
		if(t[v]==inf){//以前没更新过t 
			t[v]=t[u]+1;//时间+1
			q.push((node){u,v});
         	//推入标记为1的点，v的爸爸是u
			fa[fv]=fu;//v祖先的爸爸变成了u的祖先 
		}
		else{//以前更新过t 
			if(t[v]+1==t[u]){//v是u爸爸就跳过
			//为什么这种情况代表v是u爸爸?
			//因为v再走一步就到u了,而且t[v]<t[u] 
				continue;
			}
			if(vis[u]&&vis[v]){
			//两者都曾标为1
				continue;
			}
			if(fu==fv){//祖先一样 
				ans=min(max(t[v],t[u]),ans);
				//打擂台 
			}
			else{//祖先不一样 
				fa[fv]=fu;
				////v祖先的爸爸变成了u的祖先 
			}
		}
	}
}
```

合并一下就变成了下面那样，如果图形成不了环就输出 ```Poor D！```。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
const int inf=0x3f3f3f3f;
struct node{int from,u;};
queue<node>q;
vector<int>G[N];
int n,m,k;
int x,y,p,ans=inf;
int t[N],fa[N],vis[N];
int find(int x){
	if(x==fa[x])return fa[x];
	return find(fa[x]);
}
int main(){
	cin>>n>>m>>k;
	if(m<=n-1){
		cout<<"Poor D!";
		return 0;
	}
	for(int i=1;i<=n;i++){
		fa[i]=i;
		t[i]=inf;
	}
	while(m--){
		cin>>x>>y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	while(k--){
		cin>>p;
		t[p]=0;
		q.push((node){0,p});
	}
	while(!q.empty()){
		int f=q.front().from;
		int u=q.front().u;
		q.pop();
		if(vis[u]){
			continue;
		}
		vis[u]=1;
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(v==f){
				continue;
			}
			int fu=find(u);
			int fv=find(v);
			if(t[v]==inf){
				t[v]=t[u]+1;
				q.push((node){u,v});
				fa[fv]=fu;
			}
			else{
				if(t[v]+1==t[u]){
					continue;
				}
				if(vis[u]&&vis[v]){
					continue;
				}
				if(fu==fv){
					ans=min(ans,max(t[v],t[u]));
				}
				else{
					fa[fv]=fu;
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```
事实上，补题我就是这样 TLE 的，你需要加一些优化才能过。

```cpp
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
const int N=1e6+10;
const int inf=0x3f3f3f3f;
struct node{int from,u;};
queue<node>q;
vector<int>G[N];
int n,m,k;
int x,y,p,ans=inf;
int t[N],fa[N],vis[N];
int find(int x){
	if(x==fa[x])return fa[x];
	return fa[x]=find(fa[x]);
}
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-48;c=getchar();}
    return x*f;
}
int main(){
	n=read();m=read();k=read();
	if(m<=n-1){
		printf("Poor D!");
		return 0;
	}
	for(int i=1;i<=n;i++){
		fa[i]=i;
		t[i]=inf;
	}
	while(m--){
		x=read();y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	while(k--){
		p=read();
		t[p]=0;
		q.push((node){0,p});
	}
	while(!q.empty()){
		int f=q.front().from;
		int u=q.front().u;
		q.pop();
		if(vis[u]){
			continue;
		}
		vis[u]=1;
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(v==f){
				continue;
			}
			int fu=find(u);
			int fv=find(v);
			if(t[v]==inf){
				t[v]=t[u]+1;
				q.push((node){u,v});
				fa[fv]=fu;
			}
			else{
				if(t[v]+1==t[u]){
					continue;
				}
				if(vis[u]){
					if(vis[v]){
						continue;
					}
				}
				if(fu==fv){
					ans=min(ans,max(t[v],t[u]));
				}
				else{
					fa[fv]=fu;
				}
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：yx666 (赞：0)

# P8287 Flame 题解
## Part 1：题意
一道并查集的好题。

### Part 1.1：题目描述
给出 $n$ 个点，$m$ 条边的无环图。其中有 $k$ 个有色点，每隔 $1$ 秒将周围点染色，染成有色点。

问最少需要多少秒使得一部分有色点能构成一个简单环。

### Part 1.2：限制
- $n\le1\times10^6$。

- $m\le 2\times10^6$。
- $k\le 4\times10^4$。

## Part 2：思路
### Part 2.1：概括
链式前向星、广搜，并查集、二分答案。

两句话概括：

1. 用链式前向星、广搜模拟扩散，找到每一个点被染色的时间。

2. 用并查集、二分答案，二分枚举时间，并查集判断是否成环（也可以用 Tarjan）。

### Part 2.2：二分可行性
设答案为 $ans$，是否成环为 $[P]$。

1. 如果能成环：

	- $\forall t<ans,[P]=0$。
	- $\forall t\ge ans,[P]=1$。

2. 如果不能成环：

	- $\forall t,[P]=0$。
    
具备单调性。

### Part 2.3：复杂度
- 模拟扩散时间复杂度是 $O(m+2m+k+2n)$，即 $O(3m+2n+k)$。

- 二分复杂度是 $O(\log n\times p)$，其中 $p$ 为[并查集的时间复杂度](https://oi-wiki.org/ds/dsu-complexity/)，差不多是 $O(m\alpha(n))$ 的（~~因为不会写按秩合并~~）。

- 所以总复杂度近似于 $O(m+\log n\times m\alpha(n))$，加上优化绰绰有余。

## Part 3：代码
``` cpp
#include<bits/stdc++.h>
using namespace std;

/* 快读快写 */
#define T int
inline T read(){T x=0;char ch=getchar();while(ch<'0'||'9'<ch) ch=getchar();while('0'<=ch&&ch<='9') {x=(x<<3)+(x<<1)+(ch-'0');ch=getchar();}return x;}
void write(T x){if(x>9) write(x/10);putchar(x%10+'0');return ;}
#undef T
/* 快读快写 end */

#define N 1000005
#define M 2000005
#define pii pair<int,int>

/* 链式前向星 */
int cnt=0,head[N];
struct EDGE{
	int next,to;
}edge[M<<1];

inline void addEdge(int from,int to){
	++cnt;
	edge[cnt].next=head[from];
	edge[cnt].to=to;
	head[from]=cnt;
	return ;
}
/* 链式前向星 end */

/* 并查集*/
int fa[N];
inline int getfa(int x){
	int t=x,rx=x;
	while(fa[rx]!=rx) rx=fa[rx];
	while(x!=rx){
		t=fa[x];
		fa[x]=rx;
		x=t;
	}
	return rx;
}
/* 并查集 end */

int n,m,k;
int dis[N];
pii line[M];
signed main(){
	n=read(),m=read(),k=read();
	
	// 特判，点数比边多，肯定构不成环。
	if(n>m){
		printf("Poor D!");
		return 0;
	}
	
	// 初始化与建图
	memset(head,-1,sizeof head);
	memset(dis,0x3f,sizeof dis);
	
	for(int i=1,x,y;i<=m;++i){
		x=read(),y=read();
		line[i]={x,y};
		addEdge(x,y);
		addEdge(y,x);
	}
	
	// bfs 模拟扩散
	queue<int>q;
	for(int i=1,x;i<=k;++i){
		x=read();
		dis[x]=0;
		q.push(x);
	}
	
	while(q.size()){
		auto x=q.front();
		q.pop();
		
		for(auto i=head[x];~i;i=edge[i].next){
			auto to=edge[i].to;
			if(dis[to]>dis[x]+1){
				dis[to]=dis[x]+1;
				q.push(to);
			}
		}
	}
	
	// 二分答案
	auto check=[&](int t)->bool{
		for(int i=1;i<=n;++i) fa[i]=i;
		
		for(int i=1;i<=m;++i){
			auto x=line[i].first,y=line[i].second;
			if(dis[x]>t||dis[y]>t) continue;
			
			auto fx=getfa(x),fy=getfa(y);
			if(fx!=fy) fa[fy]=fx;
			else return 1;
		}
		
		return 0;
	};
	
	auto l=0,r=n,mid=(l+r)>>1,ans=-1;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}else{
			l=mid+1;
		}
	}
	if(ans==-1)
		printf("Poor D!");
	else
		printf("%d",ans);
	return 0;
}
```

说明：因为在二分的时候不好直接用链式前向星找起点和终点，所以用了一个 $line_i$ 表示第 $i$ 条无向边。

[AC 记录](https://www.luogu.com.cn/record/157860424)。

---

## 作者：VitrelosTia (赞：0)

题解区好多高深解法，本菜鸡只能想到一种比较 naive 的做法。

首先考虑到假如某个时间生成成功，那么以后的时间都会是成功的，于是可以二分。

二分答案时间 $x$。先预处理出所有点被激活的时间 $dis$，对于一条边 $(u, v)$，能连上的条件是 $dis_u, dis_v \le x$，连上边之后判断环路即可。

预处理直接大力 bfs。判断环路最暴力的做法就是并查集维护，如果 $u$ 和 $v$ 的祖先相同那就有环了，否则合并 $u, v$，最后还没合并出来就不是环了。将二分上界 $r$ 设为 $n$，由于 $1\le k$，无解就是 $r = n$。

时间复杂度 $O(n + \log n \times (n + m \alpha(n)))$，跑得很慢。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 5, M = 2e6 + 5;
int n, m, k, u[M], v[M];

struct Edge { int to, nxt; } e[M << 1];
int cur, head[N];
void Add(int u, int v) { e[++cur] = {v, head[u]}; head[u] = cur; }
#define GoEdge(i, u, v) for (int i = head[u], v; v = e[i].to, i; i = e[i].nxt)

queue <int> q; int dis[N]; bool vis[N];
void bfs() {
	memset(dis, 0x3f, sizeof dis);
	for (int i = 1, u; i <= k; i++) {
		cin >> u;
		q.push(u); dis[u] = 0;
	}
	while (!q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = true;
		GoEdge(i, u, v) {
			if (vis[v]) continue;
			if (dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				q.push(v);
			}
		}
	}
}

namespace UnionSet {
	int f[N];
	void init(int n) { for (int i = 1; i <= n; i++) f[i] = i; }
	int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
	bool merge(int x, int y) { x = find(x), y = find(y); if (x == y) return true; else { f[x] = y; return false; } }
} using namespace UnionSet;
bool check(int x) {
	init(n);
	for (int i = 1; i <= m; i++) {
		if (dis[u[i]] > x || dis[v[i]] > x) continue;
		if (merge(u[i], v[i])) return true;
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++) {
		cin >> u[i] >> v[i]; 
		Add(u[i], v[i]); Add(v[i], u[i]);
	}
	bfs();
	int l = 0, r = n;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	if (r == n) cout << "Poor D!";
	else cout << r;
	return 0;
}
```

---

