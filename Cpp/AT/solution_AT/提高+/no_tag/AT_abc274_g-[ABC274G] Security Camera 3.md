# [ABC274G] Security Camera 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc274/tasks/abc274_g

縦 $ H $ 行、横 $ W $ 列のグリッドがあります。上から $ i $ 行目、左から $ j $ 列目のマスをマス $ (i,j) $ と表します。  
 マス $ (i,j) $ は $ S_{i,j}= $ `#` のとき障害物が置かれており、$ S_{i,j}= $ `.` のとき何も置かれていません。

高橋君はグリッド内にいくつか監視カメラを設置しようとしています。

監視カメラは障害物のないマスに上下左右の $ 4 $ 方向のいずれかの向きで置くことができます。  
 $ 1 $ つのマスに複数台の監視カメラを設置することも可能です。

各監視カメラは、監視カメラの置かれたマス、及び、監視カメラの向いている向きにある直線上のマスを、障害物に遮られない範囲で監視することができます。

障害物の置かれていない全てのマスを監視するためには、最小でいくつの監視カメラを設置する必要がありますか？

## 说明/提示

### 制約

- $ 1\ \leq\ H,W\ \leq\ 300 $
- $ S_{i,j} $ は `.` または `#` である

### Sample Explanation 1

例えば、マス $ (1,1) $ に右向きと下向き、マス $ (3,3) $ に上向きと左向きの合計 $ 4 $ 台の監視カメラを設置すると、障害物の置かれていない全てのマスを監視することができます。

### Sample Explanation 2

例えば、マス $ (1,1) $ に右向きと下向き、マス $ (3,3) $ に左向き、マス $ (2,5) $ に左向きと下向きの合計 $ 5 $ 台の監視カメラを設置すると、障害物の置かれていない全てのマスを監視することができます。 マス $ (2,5) $ に左向きに設置したカメラは、マス $ (2,2) $ の障害物に遮られるため、マス $ (2,1) $ を監視できないことに注意してください。

## 样例 #1

### 输入

```
3 3
...
.#.
...```

### 输出

```
4```

## 样例 #2

### 输入

```
3 5
...##
.#...
...#.```

### 输出

```
5```

## 样例 #3

### 输入

```
14 107
...........................................................................................................
...........................................................................................................
..#########..###....###########..###.......###...###########..####.......###...###########...###########...
..########..###....###########....###.....###...###########...#####......###..###########...###########....
..#######..###.....###.............###...###....###...........######.....###..###...........###............
..######..###......###..............###.###.....###...........###.###....###..###...........###............
..#####..###.......############......#####......############..###..###...###..###...........############...
..####....###......############.......###.......############..###...###..###..###...........############...
..###......###.....###................###.......###...........###....###.###..###...........###............
..##........###....###................###.......###...........###.....######..###...........###............
..#..........###...############.......###.......############..###......#####..############..############...
..............###...###########.......###........###########..###.......####...###########...###########...
...........................................................................................................
...........................................................................................................```

### 输出

```
91```

# 题解

## 作者：llingy (赞：10)

[可能更好的阅读体验](https://llingy.ml/posts/72694809/)

## 题意简述
一个 $H\times W$ 的矩形区域，某些格子上会有障碍，你可以在没有障碍的格子上放置任意个摄像头，摄像头可以朝向上下左右四个方向，每个摄像头能监视到的区域是从当前格子开始，向该摄像头的方向延伸直到边界或者障碍物的区域，求至少需要多少个摄像头才能让所有没有障碍的格子都被监视到。

$1\le H,W\le300$，时间限制 $\rm{2s}$，内存限制 $\rm{1GB}$。

## 思路
![图 1](https://cdn.luogu.com.cn/upload/image_hosting/1pq6gmvq.png)

首先，我们可以得出一些结论：

* 在一段连续的空地中间放置这个方向的摄像头不会让答案变优。如图 1，在 $1$ 和 $2$ 中间放置摄像头不会让答案变优。于是只需在障碍旁边以及边界旁边放置摄像头。
* 事实上，四个方向中只用在横向和纵向中分别选一个方向设置，剩余两个方向是无需设置摄像头的。如图 1，在 $1$ 号位置放一个方向向右的摄像头和在 $2$ 放置一个方向向左的摄像头的效果是完全一致的，通过这种方式，我们总能把横向和纵向的摄像头统一为两个方向，且选摄像头的本质是在这个方向上选出一段极长的连续空地并覆盖。

问题转化为需要在横向和纵向选择一些极长连续的空地并覆盖，使得每个空地都至少被覆盖一遍。

由于只有两个方向，很容易想到二分图。二分图左边是横向的极长连续段，右边是纵向的极长的连续段。枚举每个空地，将其所属的横向极长连续段与纵向极长连续段连边。每个空地都被覆盖转化为求这个二分图的最小覆盖。

根据 $\rm{K\ddot onig}$ 定理，二分图最大匹配数等于二分图最小覆盖数。由于该二分图点数是 $HW$，边数也是 $HW$ 的，朴素二分图匹配时间复杂度不可接受，使用网络流高效求解，时间复杂度 $O(HW\sqrt{HW})$。

## Code
需要预处理出每个空地属于哪个极长连续段。
```cpp
constexpr int N=305;
char mp[N][N];
struct edge{int to,nxt,w;}e[N*N*8];
int head[N*N*2],cnt=1;
inline void _add(int u,int v,int w){e[++cnt]=(edge){v,head[u],w};head[u]=cnt;}
inline void add(int u,int v,int w){_add(u,v,w);_add(v,u,0);}
int dep[N*N*2],cur[N*N*2],s,t;
inline bool bfs()
{
　　memset(dep,-1,sizeof(dep));memcpy(cur,head,sizeof(head));
　　dep[s]=0;queue<int>q;q.push(s);
　　while(!q.empty())
　　{
　　　　int u=q.front();q.pop();
　　　　for(int i=head[u];i;i=e[i].nxt)
　　　　{
　　　　　　int v=e[i].to;
　　　　　　if(~dep[v]||!e[i].w)continue;
　　　　　　dep[v]=dep[u]+1;q.push(v);
　　　　}
　　}
　　return ~dep[t];
}
inline int dfs(int u,int fin)
{
　　if(!fin||u==t)return fin;
　　int fout=0;
　　for(int i=cur[u];i;i=e[i].nxt)
　　{
　　　　cur[u]=i;int v=e[i].to;
　　　　if(dep[v]==dep[u]+1&&e[i].w)
　　　　{
　　　　　　int f=dfs(v,min(fin,e[i].w));
　　　　　　e[i].w-=f;e[i^1].w+=f;fin-=f;fout+=f;
　　　　　　if(!fin)break;
　　　　}
　　}
　　return fout;
}
inline int dinic()
{
　　int ans=0;
　　while(bfs())ans+=dfs(s,1e9);
　　return ans;
}
int prel[N][N],preu[N][N];
inline void work()
{
　　ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
　　int n,m;cin>>n>>m;
　　for(int i=1;i<=n;i++)cin>>(mp[i]+1);
　　int tot=3;s=1,t=2;
　　for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(mp[i][j]=='.'){if(prel[i][j-1])prel[i][j]=prel[i][j-1];else prel[i][j]=++tot,add(s,tot,1);}
　　for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(mp[i][j]=='.'){if(preu[i-1][j])preu[i][j]=preu[i-1][j];else preu[i][j]=++tot,add(tot,t,1);}
　　for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(mp[i][j]=='.')add(prel[i][j],preu[i][j],1);
　　cout<<dinic();
}
```

---

## 作者：Inter12 (赞：3)

## 题意

我们先审题意，发现：

- 如果我们只看一行或者一列的时候，出现的一个**不带有障碍**的连续范围内的格子（也就是一个在一行或者一列中的**连通块**）会被一个监控发现。

- 当我们只看一个**不是障碍**的格子的时候，我们会发现，只看他所对应的第 $i$ 行中，有一个连通块，而只看他所对应的第 $j$ 列时，也有一个连通块，那么就出现了选择：要么在行向的连通块上放置一个监控，要么在列向放置一个监控，或者两个都放，使其被监控范围罩住，这样就出现了**至少二选一**的情形。

## 二分图最小点覆盖

而，**至少二选一**的特性，就正好对应上了**二分图最小点覆盖**的特性。

而**二分图最小点覆盖**的答案和**二分图最大匹配**的答案一样（待会会讲证明），因此，我们可以如下建模：

1. 将行看作型号为 $A$ 的点，将列看作型号为 $B$ 的点；

2. 给每一个连通块（也就是只看每一行每一列的连通块）编上号，连通块中的每一个点都会拥有两个编号，一个是 $A$ 型号上的连通块编号，一个是 $B$ 型号上的。统计 $A$ 型号上或者 $B$ 型号上的连通块数量；

3. 遍历全图，如果出现空地，就将 $A$ 型号上的连通块编号连向 $B$ 型号上的联通快编号（如果你前文统计的是 $B$ 型号上的连通块数量，就正好相反），一般建的都是**单项边**。

讲完建模，这里回应前文，讲一下为什么**二分图最小点覆盖**的答案和**二分图最大匹配**的答案一样。

## 证明（忙的请跳过）

### 证明方法一：

借鉴巨佬@[金珂拉](https://www.luogu.com/user/147670)帖子里的求解方式。

用网络流最大权闭合子图证明二分图最大点覆盖等于其最大匹配：

我们发现网络流最大权闭合子图的构造是 $i$ 到 $j$ 有边，则意味着有 $i \to j$ 的约束条件，同时正权点与 $S$ 连边，负权点与 $T$ 连边。

然后二分图最大点覆盖有一个性质：对于两边的点 $a_i,b_j$ 若他们之间有一条边，则意味着他们中至少有一个需要被选取到点覆盖内。

根据集合论的知识：

$$p∣q=!p \to q$$

则我们对于每个左侧节点 $i$，新建节点否 $i$，现在我们要求一个最大的集合，假设我们先让所有的左侧节点进入集合。因为我们要集合的元素个数最小，所以我们每次拿出一个节点（也就是在最大权闭合子图中选取了左侧节点的否节点）计为 $1$，放入一个节点（选取右侧节点）则计为 $-1$，最后求最大权闭合子图即可。

观察最大权闭合子图，容易发现，若不考虑边权，其构造恰好与二分图最大匹配的构造相同。因为每个点最多只有一个入流，所以本来为正无穷的边其实与 $1$ 的边是相同的。所以实际上最大权闭合子图的最小割与二分图最大匹配的最大流一模一样！

于最大权闭合子图需要先累加正权点，也就是 $num_{lt}$，而这里最大权的意义又恰好是在只有左侧节点的点集中删去最大权个数的点。

也就是说最后的答案是 $num_{lt} - (num_{lt} - mxflow) = mxflow$，也就是二分图最大匹配。

### 证明方法二：

更简单，更易懂。

1. 设二分图最小覆盖为 $s$ 个，最大匹配 $ans$ 条；

2. 由于最大匹配的 $ans$ 条边不共点，那么覆盖 $ans$ 条边至少需要 $ans$ 个点，也就是 $ans \leq s$，第一步成立；

3. 从点集内每个点都可以找到一个匹配，否则就可以删除选择这个点，也不影响整个选点，反而更优。因此可以选至少 $s$ 条边，得到大小至少为 $s$ 的匹配，$s \leq ans$，第二步成立；

4. 所以 $s = ans$ 恒成立。

## 代码（主函数核心代码）：

```cpp
cin >> n >> m;
for(int i = 1; i <= n; i++)
	for(int j = 1; j <= m; j++)
		cin >> field[i][j];
siz = 1;
for(int i = 1; i <= n; i++)
	for(int j = 1; j <= m + 1; j++)
		if(field[i][j] == '.')
		 	id[i][j][0] = siz; // id[i][j][0] 表示 (i, j) 点上位于行向的连通块的编号 
		else
			siz++; // 遇到障碍连通块就断掉了，需要加一 
int n1 = siz - 1; // 减一是因为最后还加了一次，需要在统计 A 型号上的连通块数量时减一
for(int i = 1; i <= m; i++)
	for(int j = 1; j <= n + 1; j++)
		if(field[j][i] == '.')
			id[j][i][1] = siz; // id[i][j][1] 表示 (i, j) 点上位于列向的连通块的编号 
		else
			siz++;
for(int i = 1; i <= n; i++)
	for(int j = 1; j <= m; j++)
		if(field[i][j] == '.')
			nbr[id[i][j][0]].push_back(id[i][j][1]); // 连有向边 
for(int i = 1; i <= n1; i++)
{
	if(hungary(i, ++tim)) // 打时间戳减少时间消耗 
		ans++;
}
cout << ans << '\n';
```

---

## 作者：yuruilin2026 (赞：3)

$upd:2025/5/4$：修改名称错误，简化语言。\
一道同机房的超级神犇 [Hootime](https://www.luogu.com.cn/user/1275540) 看到就能秒了的~~水~~好题。\
本题解默认已经熟练掌握了匈牙利算法。\
若没有，请移步 [P3386](https://www.luogu.com.cn/problem/P3386)。\
话不多说，开始！
1. 题意：\
   在地图内放监控摄像头，只能在空地上放。\
   除非有障碍的阻隔，否则不能再同一行列中放监控摄像头。\
   求最多的监控摄像头数量。
2. 思路：\
   ~~二分图秒了~~。\
   用行列作为二分图的左部点和右部点。\
   跑一遍匈牙利就行了。
3. 细节：\
   如果真的这么简单是不可能的。\
   考虑障碍对二分图的影响。\
   如果没有障碍，那么只需将行看作是二分图的左部点，列看作右部点，然后可以放置监控摄像头的地方的行向列连边即可。\
   本来一行只能放一个监控摄像头，但障碍的出现导致一行被隔开，所以在有障碍的情况下，可以把一行看成多行，记录行的起始位置和终止位置，可以判断能否相交。\
   列同理，在有障碍的情况下，把一列看成多列连边。

那么，上代码！\
代码里面有注释！

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
char ch[1145][1145];
bool vis[1145][1145];
string str;
int g[114514],match[114514],re[114514],n,m,sum,next1[114514],head[114514],cnt;
int tot1,tot2;
struct ppp{
	int d,x,y;
}a1[114514],a2[114514];
void add(int u,int p){ //链式前向星 
	++cnt;
	next1[cnt] = head[u],g[cnt] = p,head[u] = cnt;
}
bool dfs(int x){//匈牙利 
	for(register int i = head[x];i;i = next1[i]){//枚举右部点
		if(re[g[i]] == 0){//有边并且没被匹配 
			re[g[i]] = 1;//匹配上 
			if(match[g[i]] == 0){//match[i]存储的是匹配的人 
				match[g[i]] = x;
				return 1;
			}
			else if(dfs(match[g[i]])){
				match[g[i]] = x;
				return 1;
			}
		}
	}
	return 0;
}
void init(){//re存储的是有没有被dfs过 
	for(register int i = 0;i <= m*n+2;++i) re[i] = 0;
}
void init2(){//初始化
	memset(vis,0,sizeof(vis));
	memset(g,0,sizeof(g));
	memset(match,0,sizeof(match));
	memset(re,0,sizeof(re));
	memset(next1,0,sizeof(next1));
	memset(head,0,sizeof(head));
	cnt = 0,tot1 = 0,tot2 = 0,sum = 0,n = 0,m = 0;
	for(register int i = 0;i <= 1513;++i){
		a1[i] = ppp{0,0,0};
		a2[i] = ppp{0,0,0};
	}
}
signed main(){
	cin.tie(0),cout.tie(0);
	init2();
	cin >> n >> m;
	for(register int i = 1;i <= n;i++){
		cin >> str;
		for(register int j = 1;j <= m;j++){
			 ch[i][j] = str[j-1];
		}
	}
	for(register int i = 1;i <= n;i++){
		for(register int j = 1;j <= m;j++){
			if(vis[i][j]) continue;
			if(ch[i][j] != '.') continue;
			int xx11 = i,xx22 = i,yy11 = j,yy22 = j;
			while(xx11 > 1 && ch[xx11-1][j] != '#'){
				xx11--;//区间左端点 
			}
			while(xx22 < n && ch[xx22+1][j] != '#'){
				xx22++;//区间右端点 
			}
			for(register int k = xx11;k <= xx22;k++){
				vis[k][j] = 1;
			}
			a1[++tot1] = ppp{j,xx11,xx22};
		}
	}
	memset(vis,0,sizeof(vis));
	for(register int i = 1;i <= n;i++){
		for(register int j = 1;j <= m;j++){
			if(vis[i][j]) continue;
			if(ch[i][j] != '.') continue;
			int xx11 = i,xx22 = i,yy11 = j,yy22 = j;
			while(yy11 > 1 && ch[i][yy11-1] != '#'){
				yy11--;//区间上端点 
			}
			while(yy22 < m && ch[i][yy22+1] != '#'){
				yy22++;//区间下端点 
			}
			for(register int k = yy11;k <= yy22;k++){
				vis[i][k] = 1;
			}
			a2[++tot2] = ppp{i,yy11,yy22};
		}
	}
	for(register int i = 1;i <= tot1;i++){
		for(register int j = 1;j <= tot2;j++){
			if(a1[i].x <= a2[j].d && a1[i].y >= a2[j].d){
				if(a2[j].x <= a1[i].d && a2[j].y >= a1[i].d){
					if(ch[a2[j].d][a1[i].d] == '#') continue;//交点是障碍不能建边  
					add(i,j+n);
				}
			}
		}
	}
	
	for(register int i = 1;i <= tot1;i++){
		init();
		if(dfs(i)) sum++;
	}
	cout << sum;
	return 0;
}
```

---

## 作者：Code_AC (赞：2)

[更好的阅读体验](https://www.cnblogs.com/yhx-error/p/16818379.html)

## 题目大意

给定一张大小为 $H\times W$ 的图，上面有一些空地 `.` 和一些障碍物 `#`，现在有一种摄像机，你可以任意摆放在某个位置并选择上下左右中任意一个方向，摄像机能够照到该方向未被障碍物阻挡的地方。

求至少要多少台摄像机使得所有的空地都能被照到。

## solution

这是一个比较经典的网络流的建模。

首先我们可以横着和竖着给原图编两遍号，能够一次照到的编号相同。

以样例一为例：

```
. . .
. # .
. . .
```

先横着编号：

```
1 1 1
2 # 3
4 4 4
```

再竖着编号：

```
5 6 8
5 # 8
5 7 8
```

然后我们将横着的图连源点，竖着的图连汇点，横着的与竖着的之间编号相对位置对应的也要连边，即 $1$ 连 $5$，$2$ 连 $6$，$3$ 连 $7$，$4$ 连 $8$，然后直接跑一边最大流即可。

**Code**


```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5;
const int INF=0x7f7f7f7f;

// char buf[1<<21],*p1=buf,*p2=buf;
// #define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){ if(ch=='-') f=-1; ch=getchar(); }
    while(isdigit(ch))
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}

struct edge
{
    int to,nxt,flow;
}e[MAXN<<1];

int head[MAXN],cnt=1;

inline void add(int x,int y,int f)
{
    e[++cnt].to=y;
    e[cnt].flow=f;
    e[cnt].nxt=head[x];
    head[x]=cnt;
    return;
}

inline void addn(int x,int y,int f)
{
    add(x,y,f);
    add(y,x,0);
    return;
}

int dep[MAXN],gap[MAXN];
int n,m,s,t;

inline void bfs()
{
    queue<int>q;
    memset(dep,0,sizeof(dep));
    memset(gap,0,sizeof(gap));
    dep[t]=1;
    gap[1]=1;
    q.push(t);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=e[i].nxt)
        {
            int y=e[i].to;
            if(dep[y]) continue;
            q.push(y);
            dep[y]=dep[x]+1;
            gap[dep[y]]++;
        }
    }
    return;
}

int maxflow,cur[MAXN];

inline int dfs(int x,int flow)
{
    if(x==t)
    {
        maxflow+=flow;
        return flow;
    }
    int used=0;
    for(int i=cur[x];i;i=e[i].nxt)
    {
        cur[x]=i;
        int y=e[i].to,f=e[i].flow;
        if(dep[x]==dep[y]+1 && f)
        {
            int w=dfs(y,min(f,flow-used));
            e[i].flow-=w;
            e[i^1].flow+=w;
            used+=w;
            if(used==flow) return used;
        }
    }
    gap[dep[x]]--;
    if(!gap[dep[x]]) dep[s]=n*m*2+3;
    dep[x]++,gap[dep[x]]++;
    return used;
}

inline int Isap()
{
    maxflow=0;
    bfs();
    while(dep[s]<=n*m*2+1)
        memcpy(cur,head,sizeof(cur)),dfs(s,INF);
    return maxflow;
}

char c[305][305];
int id1[305][305],id2[305][305];

int main()
{
    n=read(),m=read();
    s=0,t=n*m*2+1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>c[i][j];
    int tot=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(c[i][j]=='#') continue;
            id1[i][j]=++tot;
            int k=j+1;
            while(c[i][k]=='.') id1[i][k]=tot,k++;
            j=k;
        }
    int mid=tot;
    for(int j=1;j<=m;j++)
        for(int i=1;i<=n;i++)
        {
            if(c[i][j]=='#') continue;
            id2[i][j]=++tot;
            int k=i+1;
            while(c[k][j]=='.') id2[k][j]=tot,k++;
            i=k;
        }
    for(int i=1;i<=mid;i++) addn(s,i,1);
    for(int i=mid+1;i<=tot;i++) addn(i,t,1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            addn(id1[i][j],id2[i][j],1);
    printf("%d\n",Isap());
    return 0;
}
```


---

## 作者：Conan15 (赞：1)

弱化版：洛谷 P6062。[弱化版题解通道](https://www.acwing.com/solution/content/256284/)。

这题相较于弱化版不需要想到木板长度最大化。\
对于一个点，它显然至少被横向或者竖向之一覆盖。\
所以容易想到对每个横向、竖向的极长连续段建立一个点。

横竖这个性质长得很像**二分图**，那么我们令横向为左部、竖向为右部。\
对于一个点把它所属的横竖连续段相连，则原图一个点对应到二分图中一条边，覆盖原图一个点相当于在二分图中选择对应的左部或右部点。\
这东西显然是**最小点覆盖**，即选择最少的点覆盖二分图中所有边。\
显然**最小点覆盖=二分图最大匹配**。建图跑 Dinic 即可。

弱化版数据范围较小，可以直接用匈牙利。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 315, N1 = 5e5 + 15, M1 = N1 << 1, INF = 0x3f3f3f3f;
int n, m;
char ch[N][N];
int c1[N][N], c2[N][N], tot;

int S, T, ans = 0;
int h[N1], e[M1], w[M1], ne[M1], idx = 0;
void add(int a, int b, int c) { e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++; }
void addedge(int a, int b, int c) { add(a, b, c), add(b, a, 0); }

int d[N1], cur[N1];
bool bfs() {
    queue<int> q; while (q.size()) q.pop();
    for (int i = 1; i <= tot; i++) d[i] = 0;
    cur[S] = h[S], d[S] = 1, q.push(S);
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (!w[i] || d[v]) continue;
            d[v] = d[u] + 1, cur[v] = h[v];
            q.push(v);
            if (v == T) return 1;
        }
    }
    return 0;
}
int dfs(int u, int rest) {
    if (u == T) return rest;
    if (rest == 0) return 0;
    int flow = 0;
    for (int i = cur[u]; ~i; cur[u] = i = ne[i]) {
        int v = e[i];
        if (d[v] != d[u] + 1 || w[i] == 0) continue;
        int now = dfs(v, min(w[i], rest - flow));
        if (now == 0) d[v] = -1;
        else w[i] -= now, w[i ^ 1] += now, flow += now;
        if (flow == rest) break;
    }
    return flow;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("\n %s", ch[i] + 1);
    S = ++tot, T = ++tot;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (ch[i][j] == '.' && ch[i][j - 1] != '.') tot++, addedge(S, tot, 1);
            if (ch[i][j] == '.') c1[i][j] = tot;
        }
    for (int j = 1; j <= m; j++)
        for (int i = 1; i <= n; i++) {
            if (ch[i][j] == '.' && ch[i - 1][j] != '.') tot++, addedge(tot, T, 1);
            if (ch[i][j] == '.') c2[i][j] = tot;
        }
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (ch[i][j] != '.') continue;
            addedge(c1[i][j], c2[i][j], 1);
        }
    while (bfs()) ans += dfs(S, INF);
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：yedalong (赞：1)

[双倍经验](https://www.luogu.com.cn/problem/P6062)  
话说为啥双倍经验是紫的，这题却是蓝的呢？  
个人觉得这种题目有紫色，毕竟二分图的最小点覆盖模版都有蓝，而这题的建图也有一定的难度。  
## Solution
假设输入的数组是 $ch$。  

首先先处理一下 $ch_{i,j}$ 是 `#` 的情况。由于监控会被挡住，就相当于这一行被一分为二了，那么我们就可以将这一行分为两行，列亦是如此。  

考虑如果 $ch_{i,j}$ 是 `.` 时由 $i$ 向 $j$ 建边。  
这时候很容易发现，我们建出来的边其实就是需要覆盖监控地方，由于监控可以看到一整行或者一整列，那么题目就转化为了在建出来的图中选出几个点，使这些点能够覆盖到所有边，这里的点就是监控，边就是需要被看到的地方。当然，选出来的那些点个数要最小。那这道题就成了二分图的最小点覆盖问题了。  

根据柯尼希定理，二分图的最小点覆盖即为二分图的最大匹配，直接跑一遍匈牙利算法就好了。  

有关柯尼希定理的证明，这里不多赘述，有兴趣的同学可以参考[这篇文章](https://www.cnblogs.com/C202202chenkelin/p/14437260.html)。  

## AC code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
int n,m,cntx=1,cnty=1,ans,match[90005];
bool pd[90005];
char mp[305][305];
vector<int> edge[90005];
pair<int,int> a[305][305];
bool dfs(int now){
	if(pd[now]) return 0;
	pd[now]=1;
	for(auto to:edge[now]){
		if(!match[to]|dfs(match[to])){
			match[to]=now;
			return 1;
		}
	}
	return 0;
}
int main(){
	cin>>n>>m;
	for(int i = 1;i<=n;i++) for(int j = 1;j<=m;j++) cin>>mp[i][j];
	for(int i = 1;i<=n;i++) for(int j = 1;j<=m;j++) if(mp[i][j]=='#') cntx++;else if(j==1) a[i][j].x=++cntx;else a[i][j].x=cntx;
	for(int i = 1;i<=m;i++) for(int j = 1;j<=n;j++) if(mp[j][i]=='#') cnty++;else if(j==1) a[j][i].y=++cnty;else a[j][i].y=cnty;
	for(int i = 1;i<=n;i++) for(int j = 1;j<=m;j++) if(mp[i][j]=='.') edge[a[i][j].x].push_back(a[i][j].y);
	for(int i = 1;i<=cntx;i++) memset(pd,0,sizeof(pd)),ans+=dfs(i); 
	cout<<ans;
}
```

---

## 作者：liyixin0514 (赞：1)

# [[ABC274G] Security Camera 3](https://www.luogu.com.cn/problem/AT_abc274_g)

给你一个 $n\times m$ 的网格图，$n,m\le 300$，每个空地上可以放任意多个任意方向的监控，一个监控视野覆盖对应方向最长连续空地，问监控覆盖所有空地最小化监控数量。

对于一个极长的连续空地，我们一定是在边边放置一个监控，而且两边是一样的，因此我们只需要考虑放置向右和向上的监控就行了。不需要考虑四个方向。

预处理出所有极长连续空地，一个连续空地我们只会放一个监控。问题变成最小化极长连续空地数量，使得覆盖所有空地。

显然一个方向的极长连续空地是互不相交的。因此对于每个空地，我们把它对应的横向极长连续空地和纵向极长连续空地连一条边，问题就是求二分图最小点覆盖（选择最少的点覆盖所有边）。显然这是一个二分图，选择一个点就是选择一个极长连续空地建一个监控。每个点必须被横向或者纵向的极长连续空地覆盖，所以就是最小点覆盖问题。

二分图最小点覆盖问题可以转化为网络流最大流问题。源点向所有横向的点连一条流量为 $1$ 的边，所有纵向的点向汇点连一条流量为 $1$ 的边，一个点属于编号为 $x$ 的横向区间，同时属于编号为 $y$ 的纵向区间，那么就连一条 $x\to y$ 的流量为 $1$ 的边。

其实中间连的那些边的流量不一定要设为 $1$ 设为 inf 也可以。因为一个空地只会和两个极大块有关，所以最多只会有 $1$ 的流量经过这条边。

做完啦！现在分析下时间复杂度。$n,m$ 同阶，时间复杂度是 $O(n^3)$ 的。

网络流点的数量是 $O(n^2)$ 的，边的数量也是 $O(n^2)$ 的。

时间复杂度证明参考 oiwiki。

![p1](https://cdn.luogu.com.cn/upload/image_hosting/gpxmvccy.png)

因此网络流的复杂度是 $O(n^2\sqrt{n^2})=O(n^3)$。

## code

```cpp
#include<bits/stdc++.h>
// #define LOCAL
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
using namespace std;
typedef long long ll;
const int N=305,inf=0x3f3f3f3f,M=N*N;
int n,m;
char c[N][N];
int id[2][N][N],s;
struct edge{
    int to,ne,f;
}e[M<<4];
int head[M<<4],cnt=1,cur[M<<4];
void addedge(int u,int v,int val){
    e[++cnt]={v,head[u],val};head[u]=cnt;
}
void adde(int u,int v,int val){
    addedge(u,v,val),addedge(v,u,0);
}
int S,T;
int dep[M<<4];
bool bfs(){
    queue<int> q;
    memset(dep,0,sizeof(dep));
    // memcpy(cur,head,sizeof(head));
    q.push(S);
    dep[S]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        cur[u]=head[u];
        // pf("u %d\n",u);
        for(int i=head[u];i;i=e[i].ne){
            int v=e[i].to,w=e[i].f;
            // pf("v %d\n",v);
            if(dep[v]!=0||w<=0) continue;
            dep[v]=dep[u]+1;
            q.push(v);
        }
    }
    // pf("%d\n",(int)dep[T]!=0);
    return dep[T]!=0;
}
int dfs(int u,int res){
    int flow=0;
    if(u==T||!res) return res;
    for(int &i=cur[u];i;i=e[i].ne){
        int v=e[i].to,w=e[i].f;
        if(dep[v]!=dep[u]+1||!w) continue;
        int fl=min(res,w);
        int x=dfs(v,fl);
        if(x==0) dep[v]=-1;
        res-=x,flow+=x;
        e[i].f-=x,e[i^1].f+=x;
    }
    return flow;
}
int dinic(){
    int flow=0;
    while(bfs()) flow+=dfs(S,inf);
    return flow;
}
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("my.out","w",stdout);
    #endif 
    sf("%d%d",&n,&m);
    rep(i,1,n){
        sf("%s",c[i]+1);
    }
    S=1,T=2;s=2;
    rep(i,1,n) {
        rep(j,1,m) {
            if(c[i][j]=='.'){
                if(id[0][i][j-1]) id[0][i][j]=id[0][i][j-1];
                else s++,id[0][i][j]=s,adde(S,s,1);
            }
        }
    }
    rep(j,1,m) {
        rep(i,1,n) {
            if(c[i][j]=='.'){
                if(id[1][i-1][j]) id[1][i][j]=id[1][i-1][j];
                else s++,id[1][i][j]=s,adde(s,T,1);
            }
        }
    }
    rep(i,1,n){
        rep(j,1,m){
            if(c[i][j]=='.') adde(id[0][i][j],id[1][i][j],1);
        }
    }
    pf("%d\n",dinic());
}
```

---

## 作者：Resolute_Faith (赞：1)

匈牙利算法的做法，主要讲的是常见匈牙利算法的优化。

[原题](https://www.luogu.com.cn/problem/P6062)

### 建模

一个 `.` 显然要么被横着的覆盖，要么被竖着的覆盖。又因为每一个覆盖的两端显然都是障碍，所以我们从横向的覆盖到竖着的覆盖连边，即最小点覆盖。

定义 $x_i$ 表示横着覆盖的第 $i$ 行，$y_j$ 表示竖着覆盖的第 $j$ 行，边为 $x_i$ 到 $y_j$。但是这样有一个问题，一行可能会有多个可以覆盖的位置：

```
.#...#.
```

这样我们可以放下三块横着的，因此我们不能直接以第几行第几列建图，用一种类似离散化的方式去做，就做完了。

### 优化

由于不知道上述算法是否正确（也许你们可以用朴素的匈牙利算法跑一下看一下会不会 TLE，我急需知道这个结果），我们一般打匈牙利算法是要优化的，常见的优化包括前向星优化和时间戳优化（我自己取的名字）。

[例题，建议掌握](https://www.luogu.com.cn/problem/P1640)

考虑到每次执行匈牙利算法都要 `memset` $vis$ 数组，这很麻烦，我们直接定义 $dfn$ 数组表示当前是第几轮，如果一个点的 $dfn$ 还在上一轮，那他就得更新，原理跟 $vis$ 是一样的，但是要快很多。

时间复杂度未知，但就是这么神奇。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,head[N],id=1,ans=0,dfn[N],f[N],cnt,A[305][305],B[305][305];
struct edge{int to,nxt;}a[N];
char ch[305][305];
void add(int x,int y){
	a[++cnt].to=y;
	a[cnt].nxt=head[x];
	head[x]=cnt;
}
bool dfs(int x){
	for(register int i=head[x];i;i=a[i].nxt){
		int y=a[i].to;
		if(dfn[y]-id){
			dfn[y]=id;
			if(!f[y]||dfs(f[y])){
				f[y]=x;
				return true;
			}
		}
	}
	return false;
}
int main(){
	scanf("%d %d",&n,&m);
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++){
			cin>>ch[i][j];
		}
	}
	int cntx=0,cnty=0;
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++){
			if(ch[i][j]=='.'){
				A[i][j]=j>1&&ch[i][j-1]=='.'?A[i][j-1]:++cntx;
				B[i][j]=i>1&&ch[i-1][j]=='.'?B[i-1][j]:++cnty;
			}
		}
	}
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++){
			if(ch[i][j]=='.') add(A[i][j],B[i][j]);
		}
	}
	for(register int i=1;i<=cntx;i++,id++) ans+=dfs(i);
	printf("%d",ans);
}
```

顺便放一个 Dinic 的做法（我直接从匈牙利上改的所以比较丑）：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,m,head[N],id=1,ans=0,dfn[N],f[N],cnt=1,A[305][305],B[305][305],s,t;
int dis[N],now[N];
const int inf=1e9;
struct edge{int to,nxt,l;}a[N];
char ch[305][305];
void add(int x,int y,int z){
	a[++cnt].to=y;
	a[cnt].nxt=head[x];
    a[cnt].l=z;
	head[x]=cnt;
}
bool bfs(){
	for(register int i=1;i<=n*m+2;i++) dis[i]=inf;
	queue<int> q;
	q.push(s),dis[s]=s,now[s]=head[s];
	while(!q.empty()){
		int x=q.front();q.pop();
		for(register int i=head[x];i;i=a[i].nxt){
			int y=a[i].to;
			if(a[i].l>0&&dis[y]==inf){
				dis[y]=dis[x]+1;
				now[y]=head[y];
				q.push(y);
				if(y==t) return true;
			}
		}
	}
	return false;
}
int dfs(int x,int flow){
	if(x==t) return flow;
	int ans=0;
	for(register int i=now[x];i&&flow;i=a[i].nxt){
		int y=a[i].to;
		now[x]=i;
		if(a[i].l>0&&dis[y]==dis[x]+1){
			int k=dfs(y,min(flow,a[i].l));
			a[i].l-=k,a[i^1].l+=k;
			if(!k) dis[y]=inf;
			ans+=k,flow-=k;
		}
	} 
	return ans;
}
int main(){
	scanf("%d %d",&n,&m);
    s=n*m+1,t=n*m+2;
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++){
			cin>>ch[i][j];
		}
	}
	int cntx=0,cnty=0;
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++){
			if(ch[i][j]=='.'){
				A[i][j]=j>1&&ch[i][j-1]=='.'?A[i][j-1]:++cntx;
				B[i][j]=i>1&&ch[i-1][j]=='.'?B[i-1][j]:++cnty;
			}
		}
	}
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++){
			if(ch[i][j]=='.'){
                add(A[i][j],B[i][j]+cntx,1);
                add(B[i][j]+cntx,A[i][j],0);
            }
		}
	}
	for(register int i=1;i<=cntx;i++) add(s,i,1),add(i,s,0);
    for(register int i=1;i<=cnty;i++) add(i+cntx,t,1),add(t,i+cntx,0);
    while(bfs()) ans+=dfs(s,inf);
	printf("%d",ans);
}
```


---

## 作者：yzh_Error404 (赞：1)

~~一眼网络流板子所以没写EF就来写G~~

先套路的将每一行和每一列标上号，每隔一个障碍物就再加一次，类似于下面的操作：
```
...    111       ...    568
.#. -> 2#3       .#. -> 5#8
...    444       ...    578
```
然后将每一个格子的行标号与列标号相连，超级源点连向行标号，列标号连向超级汇点。

然后就变成了求二分图最小覆盖，跑个最大流就过了。

代码实现：
```cpp
#include<bits/stdc++.h>
#define s 0
#define t n*m*2+1
using namespace std;
const int MAXN=1e6+5;
const int INF=0x7f7f7f7f;
struct node
{
	int to,nxt,flow;
}e[MAXN];
int head[MAXN],cnt=1;
inline void adde(int x,int y,int f)
{
	e[++cnt].to=y;
	e[cnt].flow=f;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
inline void add(int x,int y,int f)
{
	adde(x,y,f);
	adde(y,x,0);
}
int n,m;
int cur[MAXN],dis[MAXN];
bitset<MAXN>vis;
inline bool bfs()
{
	queue<int>q;
	memset(dis,-1,sizeof dis);
	q.push(s);
	dis[s]=0;
	cur[s]=head[s];
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(register int i=head[x];i;i=e[i].nxt)
		{
			int y=e[i].to,f=e[i].flow;
			if(dis[y]==-1&&f)
			{
				dis[y]=dis[x]+1;
				cur[y]=head[y];
				if(y==t)return true;
				q.push(y);
			}
		}
	}
	return false;
}
inline int dfs(int x,int lim)
{
	if(x==t)return lim;
	int f=0;
	for(register int i=cur[x];i&&f<lim;i=e[i].nxt)
	{
		int y=e[i].to;
		cur[x]=i;
		if(dis[y]==dis[x]+1&&e[i].flow)
		{
			int w=dfs(y,min(e[i].flow,lim-f));
			if(!w)dis[y]=-1;
			e[i].flow-=w;
			e[i^1].flow+=w;
			f+=w;
		}
	}
	return f;
}
inline int dinic()
{
	int ans=0,f;
	while(bfs())while(f=dfs(s,INF))ans+=f;
	return ans;
}
char ma[305][305];
int id1[305][305],id2[305][305];
int tot,sum;
int main()
{
    scanf("%d%d",&n,&m);
    for(register int i=1;i<=n;i++)
        for(register int j=1;j<=m;j++)
        {
            cin>>ma[i][j];
            if(ma[i][j]=='.')sum++;
        }
    for(register int i=1;i<=n;i++)
        for(register int j=1;j<=m;j++)
        {
            if(ma[i][j]=='#')continue;
            id1[i][j]=++tot;
            int k=j+1;
            while(ma[i][k]=='.')id1[i][k]=tot,k++;
            j=k;
        }
    int mid=tot;
    for(register int j=1;j<=m;j++)
        for(register int i=1;i<=n;i++)
        {
            if(ma[i][j]=='#')continue;
            id2[i][j]=++tot;
            int k=i+1;
            while(ma[k][j]=='.')id2[k][j]=tot,k++;
            i=k;
        }
    for(register int i=1;i<=mid;i++)
        add(s,i,1);
    for(register int i=mid+1;i<=tot;i++)
        add(i,t,1);
    for(register int i=1;i<=n;i++)
        for(register int j=1;j<=m;j++)
            add(id1[i][j],id2[i][j],1);
    printf("%d",dinic());
    return 0;
}
```

---

