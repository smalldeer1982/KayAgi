# [HNOI2007] 紧急疏散（EVACUATE）

## 题目描述

发生了火警，所有人员需要紧急疏散！

假设这个房间是一个 $N \times M$ 的矩形区域。每个格子有三个状态：

- 一块空地，可以通行，用 `.` 表示。
- 一面墙，不可以通行，用 `X` 表示。
- 一扇门，人们可以从这里撤出房间，用 `D` 表示。

已知门一定在房间的边界上，并且边界上不会有空地。

最初，每块空地上都有一个人。疏散开始后，每块空地上就没有人数限制了（也就是说每块空地可以同时站无数个人）。

在疏散的时候，每一秒钟每个人都可以向上 / 下 / 左 / 右四个方向移动一格，当然他也可以站着不动。

由于门很窄，每一秒钟只能有一个人移动到门的位置，一旦移动到门的位置，就表示他已经安全撤离了。

现在的问题是：如果希望所有的人安全撤离，最短需要多少时间？或者告知根本不可能。

## 说明/提示

Update on 2015.1.12：新加数据一组。鸣谢：1756500824

对于 C++ 语言，请使用 `scanf` 读入字符矩阵！

## 样例 #1

### 输入

```
5 5
XXXXX
X...D
XX.XX
X..XX
XXDXX```

### 输出

```
3```

# 题解

## 作者：Log_x (赞：10)

##BFS + 二分答案 + 最大流

（算补充楼下的把）

**【解题思路】**

[1] 二分答案 mid （所有人安全撤离所需时间）。

[2] 通过最大流来判断逃生时间为 mid 时，所有人能否安全撤离，能则缩小边界：

1. 将源点 S 向每个空地连一条容量为 1 的边，表示每个空地初始时有一个人；

2. 因为**每一秒钟只能有一个人移动到门的位置**，我们要将每个门拆成 mid 个点，分别表示时刻为第 1 ~ mid 秒的门，并向汇点 T 连一条容量为 1 的边；

3. 为了简化问题，在二分答案前我们先 BFS 求出每块空地到每个门所需时间（当然用SPFA也是可以的，其实这时两者效率相同），然后将每块空地与对应所需时间的门连边，容量为1（因为初始时每块空地上只有一个人）；

4. （这一点楼下没讲，但代码里有写）那么如果有一些人（人数大于等于1）进入任意一个时刻的门，那么这个时刻的这扇门对应的点必定有 1 的流量流入汇点，但可能会有多个人到达同一个门所需的时间相同，所以我们要让剩下的人等到下一秒再让其中一个人移动到门的位置，所以对于时刻为第 1 ~ mid - 1 秒的门，我们都要向时刻为下一秒的门连一条容量为无穷大的边（因为同一时刻到达门的人可能有任意多，且 mid >= 正确答案时，所有人所代表的流量都将流入汇点 T，所以这里就不多考虑人数了）；

5. 判断如此建图的最大流是否等于总人数（总的空地数），如果一直无法相等则说明所有人无法全部安全撤出，输出“impossible”。

**【注意】**

1. 因为要拆点，空间问题比较棘手（下面的代码空间开的可能会比较大，也是从MLE中慢慢调出来的）；

2. 因为要跑多次最大流，源点汇点以及建边都要注意重置。

**【AC代码】**












```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int Maxn = 0x3f3f3f3f;
const int L = 21, M = 1e6 + 5, N = 5e4 + 5;
const int dx[] = {-1, 1, 0, 0},
          dy[] = {0, 0, -1, 1};
int dis[N][L][L], h[N][2], G[L][L]; 
int lst[N], nxt[M], to[M], flw[M], cur[N], lev[N];
int n, m, T, E, R, l = 1, r = 1000, Ans = -1, src, des; 
bool vis[L][L]; char c[L][L];
template <class T> inline T Min(const T a, const T b) {return a < b? a : b;}
template <class T> inline void CkMax(T &a, const T b) {if (a < b) a = b;}
template <class T> inline void CkMin(T &a, const T b) {if (a > b) a = b;}
inline int get()
{
    char ch; bool f = false; int res = 0;
    while (((ch = getchar()) < '0' || ch > '9') && ch != '-');
    if (ch == '-') f = true;
     else res = ch - '0';
    while ((ch = getchar()) >='0' && ch <= '9')
        res = (res << 3) + (res << 1) + ch - '0';
    return f? ~res + 1 : res;
}
inline void put(int x)
{
    if (x < 0)
      x = ~x + 1, putchar('-');
    if (x > 9) put(x / 10);
    putchar(x % 10 + 48);
}
inline void add(const int x, const int y, const int z)
{
    nxt[++T] = lst[x]; lst[x] = T; to[T] = y; flw[T] = z;
    nxt[++T] = lst[y]; lst[y] = T; to[T] = x; flw[T] = 0;
}
inline bool Bfs()
{
    static int Qn, Q[N]; int x, y;
    for (int i = src; i <= des; ++i) cur[i] = lst[i], lev[i] = -1;
    Q[Qn = 1] = src; lev[src] = 0;
    for (int j = 1; j <= Qn; ++j)
    {
        x = Q[j];
        for (int i = lst[x]; i; i = nxt[i])
         if (flw[i] > 0 && lev[y = to[i]] == -1)
         {
             lev[y] = lev[x] + 1; Q[++Qn] = y;
             if (y == des) return true;
         }
    }
    return false;
}
inline int Dinic(const int x, const int fl)
{
    if (x == des) return fl;
    int Del, res = 0, y;
    for (int &i = cur[x]; i; i = nxt[i])
    if (flw[i] > 0 && lev[x] < lev[y = to[i]])
    {
        Del = Dinic(y, Min(flw[i], fl - res));
        if (Del)
        {
            flw[i] -= Del; flw[i ^ 1] += Del;
            res += Del; if (res == fl) break;
        }
    }    
    if (res != fl) lev[x] = -1;
    return res;
}
inline int MaxFlow()
{
    int res = 0;
    while (Bfs()) res += Dinic(src, Maxn);
    return res;
}
inline void Ready(const int s, const int px, const int py)
{
    memset(vis, false, sizeof(vis)); int x, y, t = 0, w = 1; 
    vis[px][py] = true; dis[s][px][py] = 0; h[w][0] = px; h[w][1] = py;
    while ((t++) < w)
     for (int i = 0; i < 4; ++i)
     {
        int tx = h[t][0] + dx[i], ty = h[t][1] + dy[i];
        if (tx < 1 || tx > n || ty < 1 || ty > m || vis[tx][ty] || c[tx - 1][ty - 1] != '.') continue;
        dis[s][tx][ty] = dis[s][h[t][0]][h[t][1]] + 1;
        h[++w][0] = tx; h[w][1] = ty; vis[tx][ty] = true;
     }
}
inline bool Judge(const int mi)
{
    src = 0; des = R + E * mi + 1; T = 1;
    memset(lst, 0, sizeof(lst));
    for (int i = 1; i <= n; ++i)
     for (int j = 1; j <= m; ++j)
      if (c[i - 1][j - 1] == '.') add(src, G[i][j], 1);
    for (int k = 1; k <= E; ++k)
     for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
       if (c[i - 1][j - 1] == '.' && dis[k][i][j] <= mi) 
           add(G[i][j], (k - 1) * mi + R + dis[k][i][j], 1);
    for (int i = 1; i <= E; ++i)
     for (int j = 1; j <= mi; ++j) 
     {    
        int tmp = (i - 1) * mi + R; add(tmp + j, des, 1);
        if (j != mi) add(tmp + j, tmp + j + 1, Maxn);
     }
    return MaxFlow() == R;
}
int main()
{
    memset(dis, Maxn, sizeof(dis));
    n = get(); m = get(); 
    for (int i = 0; i < n; ++i) scanf("%s", c[i]);
    for (int i = 1; i <= n; ++i)
     for (int j = 1; j <= m; ++j)
     if (c[i - 1][j - 1] == 'D') Ready(++E, i, j);
      else if (c[i - 1][j - 1] == '.') G[i][j] = ++R; 
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (Judge(mid)) Ans = mid, r = mid - 1;
         else l = mid + 1;
    } 
    if (Ans == -1) puts("impossible");
     else put(Ans);
    return 0;
}
```

---

## 作者：yqbylty (赞：5)

### 解题思路：

因为每一个时刻的每一个出口都只能出一个人，所以很容易想到按照时间来建图，然后跑二分图匹配就好了。首先$BFS$预处理出对于每一个出口，每个人到达它的时间是多少。然后我们枚举出口、人和时间，时间从最短距离到最大时间，对于每个时间都将出口和人之间连边，然后做二分图匹配就好了。

#### Code：

```cpp
/*Program from Luvwgyx*/
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=30;
const int maxm=1.6e6+10;
const int inf=1061109567;
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
struct node{int x,y;}a[maxm],b[maxm];
struct edge{int to,nxt;}e[maxm<<1];char s[maxn][maxn];
int n,m,tot,idx,cnt1,cnt2,head[maxm],match[maxm],vis[maxm],mp[maxn][maxn],dis[maxn][maxn][maxn][maxn];
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void print(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
void write(int x){print(x);puts("");}
int get(int x,int y){return x*m+y;}
void add(int u,int v){e[++tot].to=v;e[tot].nxt=head[u];head[u]=tot;}
bool dfs(int x){
    for(int i=head[x],v=e[i].to;i;i=e[i].nxt,v=e[i].to){
        if(vis[v]==idx)continue;vis[v]=idx;
        if(!match[v]||dfs(match[v])){match[v]=x;return 1;}
    }return 0;
}
queue<node >q;
bool vs[maxn][maxn];
void bfs(int u,int v){
    memset(vs,0,sizeof(vs));
    while(!q.empty())q.pop();
    memset(dis[u][v],63,sizeof(dis[u][v]));
    dis[u][v][u][v]=0;vs[u][v]=1;q.push((node){u,v});
    while(!q.empty()){
        node x=q.front();q.pop();
        for(int i=0;i<4;i++){
            int xx=x.x+dx[i],yy=x.y+dy[i];
            if(0<=xx&&xx<n&&0<=yy&&yy<m&&mp[xx][yy]==1&&!vs[xx][yy])
            	q.push((node){xx,yy}),dis[u][v][xx][yy]=dis[u][v][x.x][x.y]+1,vs[xx][yy]=1;
        }
    }
}
int main(){
    n=read();m=read();
    for(int i=0;i<n;i++){
        scanf("%s",s[i]);
        for(int j=0;j<m;j++){
            if(s[i][j]=='X')mp[i][j]=0;
            if(s[i][j]=='.')mp[i][j]=1,a[cnt1++]=(node){i,j};
            if(s[i][j]=='D')mp[i][j]=2,b[cnt2++]=(node){i,j};
        }
    }
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(mp[i][j]==2)bfs(i,j);
    for(int i=0;i<cnt2;i++)
        for(int j=0;j<cnt1;j++)
            if(dis[b[i].x][b[i].y][a[j].x][a[j].y]<inf)
                for(int k=dis[b[i].x][b[i].y][a[j].x][a[j].y];k<=n*m;k++)
                    add(k*cnt2+i,n*m*cnt2+j),add(n*m*cnt2+j,k*cnt2+i);
    int ret=0;
    for(int i=0;i<n*m*cnt2;i++){
        ++idx;if(dfs(i))ret++;
        if(ret==cnt1){write(i/cnt2);return 0;}
    }puts("impossible");
    return 0;
}
/*
4 5
XXDXX
XX.XX
X...X
XXDXX
*/
```

---

## 作者：zzxLLL (赞：3)


套路题，给个不用二分的写法。

---


一眼网络流。

将人看做流量。每个格子拆成两个点，从入点连向出点，如果是门那么容量是 $1$，否则是 $+\infin$。含义是这个位置能站几个人。

涉及到时间所以建分层图。现在在 $(x, y)$，那么从上一层的 $(x - 1, y), (x, y - 1), (x + 1, y), (x, y + 1), (x, y)$ 的出点连边到这一层 $(x, y)$ 的入点，容量 $+\infin$。表示人能从别的格子花费 $1$ 时间到达这里。注意上一层必须是空地才能连边过来。

对于第一层，源点向每个空地连边，容量为 $1$，表示最开始这里有一个人。

对于每一层，门位置的出点（入点也行）连向汇点，容量为 $1$，表示每个时间只能一个人逃出去。

但是因为时间不知道，所以不知道要建多少层。所以直接一层一层加上去，然后加上新增的流量，直到第一次总流量等于人数，此时的层数减去一就是答案。

注意判断无解的情况。因为 $nm \leq 400$ 所以如果建了 $400$ 层流量仍然小于人数，说明无解。

```cpp
#include<queue>
#include<cstdio>
#include<cstring>
const int M=5e5+10;
const int inf=1e9+7;
const int dx[]={-1,1,0,0},
		  dy[]={0,0,-1,1};

int n,m;
char mp[23][23];

int head[M],cnte=1;
struct Edge{
	int to,nxt,cap,flow;
}e[M<<2];
void add(int u,int v,int w){
	e[++cnte]={v,head[u],w,0};
	head[u]=cnte;
}
void Add(int u,int v,int w){
	add(u,v,w),add(v,u,0);
}

std::queue<int>q;
int dis[M],s,t,cntp;
bool bfs(){
	for(int i=0;i<=cntp;i++) dis[i]=0;
	dis[s]=1;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];~i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].cap>e[i].flow&&!dis[v]){
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	return dis[t];
}
int dfs(int u,int in){
	if(u==t) return in;
	int out=0;
	for(int i=head[u];~i;i=e[i].nxt){
		int v=e[i].to;
		if(dis[v]==dis[u]+1&&e[i].cap>e[i].flow){
			int res=dfs(v,std::min(in,e[i].cap-e[i].flow));
			e[i].flow+=res,e[i^1].flow-=res;
			in-=res,out+=res;
		}
	}
	if(!out) dis[u]=-1;
	return out;
}
int Dinic(){
	int ans=0;
	while(bfs()) ans+=dfs(s,inf);
	return ans;
}

int iD[2][23][23][2],cur;
void BasicLayer(){
	cur^=1;
	s=0,t=cntp=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='X') continue;
			iD[1][i][j][0]=++cntp;
			iD[1][i][j][1]=++cntp;
			if(mp[i][j]=='.'){
				Add(iD[1][i][j][0],iD[1][i][j][1],1);
				Add(s,iD[1][i][j][0],1);
			}
			if(mp[i][j]=='D'){
				Add(iD[1][i][j][0],iD[1][i][j][1],1);
				Add(iD[1][i][j][1],t,1);
			}
		}
	
}
void NewLayer(){
	cur^=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='X') continue;
			iD[cur][i][j][0]=++cntp;
			iD[cur][i][j][1]=++cntp;
			Add(iD[cur^1][i][j][1],iD[cur][i][j][0],inf);
			for(int dir=0;dir<4;dir++){
				int x=i+dx[dir],y=j+dy[dir];
				if(x<1||x>n||y<1||y>m) continue;
				if(mp[x][y]!='.') continue;
				Add(iD[cur^1][x][y][1],iD[cur][i][j][0],inf);
			}
			if(mp[i][j]=='.'){
				Add(iD[cur][i][j][0],iD[cur][i][j][1],inf);
			}
			if(mp[i][j]=='D'){
				Add(iD[cur][i][j][0],t,1);
			}
		}
}

int main(){
	memset(head,-1,sizeof head);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf(" %s",mp[i]+1);
	int cnt=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) cnt+=(mp[i][j]=='.');
	
	BasicLayer();
	int all=0;
	for(int t=1;;t++){
		if(t>=400) break;
		NewLayer();
		all+=Dinic();
		if(all==cnt){
			printf("%d\n",t);
			return 0;
		}
	}
	printf("impossible\n");
	return 0;
}
```

---

## 作者：JimmyLee (赞：2)

# 题目描述

[P3191 HNOI2007 紧急疏散EVACUATE](https://www.luogu.com.cn/problem/P3191)

# 题目解法

看到数据范围：**网络流**

看到求时间：**二分**或**分层**

再看到给出的数据：**BFS**

所以我选择**网络流**+**分层**+**BFS**

## 建图

1. 首先每个空地 $(i,j)$ 都有一个人，所以从源点 $s$ 连一条流量为 $1$ 的边到 $(i,j)$。

2. 然后对每个门 $D_x$ 进行 BFS，若点 $(i,j)$ 到 $x$ 号门的距离为 $d$，则说明从 $(i,j)$ 到门 $D_x$ 最短耗时 $d$。由于每个门每个时刻只能撤离 $1$ 个人，所以我们对门进行**拆点**，将门 $D_x$ 拆成 $t$ 个点，对于 $i\in [1, t]$，$D_{x,i}$ 就代表第 $i$ 时刻的门。所以从 $(i,j)$ 连一条流量为 $1$ 的边到 $D_{x,d}$，$D_{x,d}$ 代表第 $x$ 号门的第 $d$ 时刻的状态。

3. 从 $D_{x,d}$ 连一条流量为 $\infty$ 的边到 $D_{x,d+1}$，该时刻没有撤离的人，可以向下一时刻 $D_{x,d+1}$ 转移。

在 BFS 过程中判断是否有解。

~~本蒟蒻因为 BFS 写错 **MLE** on #2~~

## 分层

鉴于本题中 $3\leq N\le20,3\le M\le20$，最多不超过 $400$ 步即可撤离，使用分层，从 $1$ 到 $400$ 依次枚举时刻 $y$，每次在残量网络中从 $D_{x,y}$ 连一条流量为 $1$ 的边到汇点 $t$。

在每次连边完成后在残量网络上跑最大流，如果最大流的和等于总人数，那么就输出 $y$ 并退出。

因为每次跑最大流不需要重新建图，只需要连边，效率并不差。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

template<typename Tp, size_t sizn, size_t sizm>
struct netflow
{
    int cnt=1, s=sizn-3, t=sizn-2;
    Tp val[sizm<<1], dis[sizn];

    void link(int u, int v, Tp w) 
    {
        to [++cnt]=v;       val [cnt]=w;
        nxt[ cnt ]=head[u]; head[ u ]=cnt;
        to [++cnt]=u;       val [cnt]=0;
        nxt[ cnt ]=head[v]; head[ v ]=cnt;
    }

    private:

    int head[sizn], to[sizm<<1], nxt[sizm<<1], now[sizm<<1];
    const Tp inf=((Tp)INFINITY)>>1;
    
    int bfs() 
    {
        for(int i=1;i<sizn;i++) dis[i]=inf;
        queue<int> q;
        q.push(s);
        dis[s]=0;
        now[s]=head[s];
        while (!q.empty())
        {
            int idx=q.front(); q.pop();
            for(int i=head[idx];i;i=nxt[i])
            {
                int arr=to[i];
                if(val[i]>0&&dis[arr]==inf)
                {
                    q.push(arr);
                    now[arr]=head[arr];
                    dis[arr]=dis [idx]+1;
                    if(arr==t) return 1;
                }
            }
        }
        return 0;
    }
    
    Tp dfs(int idx, Tp sum)
    {
        if(idx==t) return sum;
        Tp k, res=0;
        for(int i=now[idx];i&&sum;i=nxt[i])
        {
            now[idx]=i;
            int arr=to[i];
            if(val[i]>0&&(dis[arr]==dis[idx]+1))
            {
                k=dfs(arr, min(sum, val[i]));
                if(k==0) dis[arr]=inf;
                val[i]-=k;      res+=k;
                val[i^1]+=k;    sum-=k;
            }
        }
        return res;
    }
    public:
    
    Tp maxflow()
    {
        Tp ans=0;
        while (bfs()) ans+=dfs(s, inf); 
        return ans;
    }
};

netflow<int, 50004, 1000006> nf;

struct st
{
    int d, y, x;
    st(int x, int y, int d=0): x(x), y(y), d(d) {};
};

char mp[25][25];
int vis[25][25], dis[25][25];

int dx[]={1, -1, 0, 0};
int dy[]={0, 0, 1, -1};

int n, m;

#define chk(x, y) ((x)&&(y)&&((x)<=n)&&((y)<=m))
#define pos(x, y) (((x)-1)*m+(y))

queue<st> q;
int tot=0, cdd;
void bfs(int x, int y, int cc)
{
    q.emplace(x, y);
    memset(vis, 0, sizeof vis);
    while(!q.empty())
    {
        auto [d, y, x]=q.front();
        q.pop();
        for(int i=0;i<4;i++)
        {
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(!chk(nx, ny)||mp[nx][ny]!='.'||vis[nx][ny]) continue;
            dis[nx][ny]=vis[nx][ny]=1;
            nf.link(pos(nx, ny), n*m+cdd*d+cc, 1);
            q.emplace(nx, ny, d+1);
        }
    }
}

char gc()
{
    char c=getchar();
    while(c!='X'&&c!='.'&&c!='D') c=getchar();
    return c;
}

vector<pair<int, int> > vp;

int main()
{
    int cnt=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            mp[i][j]=gc();
            if(mp[i][j]=='D')
                vp.emplace_back(i, j), cdd++;
            if(mp[i][j]=='.')
                nf.link(nf.s, pos(i, j), 1), cnt++;
        }
    int tmp=0;
    for(auto [x, y]:vp) bfs(x, y, ++tmp);
    tmp=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            tmp+=dis[i][j];
    if(tmp!=cnt) return cout<<"impossible", 0;
    int flow=0;
    for(int i=1;;i++) 
    {
        for(int j=1;j<=cdd;j++)
            nf.link(n*m+(i-1)*cdd+j, nf.t, 1);
        for(int j=1;j<=cdd;j++) 
            nf.link(n*m+(i-1)*cdd+j, n*m+i*cdd+j, 0x3f3f3f3f);
        flow+=nf.maxflow();
        if(flow==cnt) return cout<<i, 0;
    }
}
```

---

## 作者：香风智乃 (赞：2)

**费用流+卡常优化**

我们只关心一个人通过门时的时间，在空地的行走时间可以分层维护

于是根据时间分层，到门的时候再计算代价，即代价$=$层数

每经过$1$单位时间就向下走一层

然后就是优化：

1. 删去多余点（层）：只要开和人数相同的层，因为一个人的等待时间一定小等于人数

2. 能预处理的尽量预处理

3. register，快读，inline等

4. 能不用stl尽量不用（使用stl:queue=TLE），建议手写队列

复杂度$O($卡常能过$)$，详情可看code

[blog](https://www.cnblogs.com/kafuuchino/p/11380587.html)

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define re register
using namespace std;
#define N 200005
#define M 3000005
const int d1[4]={0,1,0,-1};
const int d2[4]={1,0,-1,0};
char a[30][30];
int n,m,nm,mx,ans,tot,S,T,v[N],p[N],id[30][30];
bool vis[N]; int h[M],L,R;
int Cnt=1,hd[N],nxt[M],ed[N],poi[M],con[M],val[M];
void adde(int x,int y,int v1,int v2){
	nxt[ed[x]]=++Cnt; hd[x]=hd[x]?hd[x]:Cnt;
	ed[x]=Cnt; poi[Cnt]=y; con[Cnt]=v1; val[Cnt]=v2;
}
inline void link(int x,int y,int v1,int v2){adde(x,y,v1,v2),adde(y,x,0,-v2);}
#define to poi[i]
bool bfs(){//普通费用流
	memset(v,63,sizeof(v)); int inf=v[0];
	h[L=1]=S; R=2; vis[S]=1; v[S]=0;
	while(L!=R){
		re int x=h[L++]; vis[x]=0;
		if(L>=M) L=1;
		for(re int i=hd[x];i;i=nxt[i])
			if(con[i]&&v[to]>v[x]+val[i]){
				v[to]=v[x]+val[i]; p[to]=i;
				if(!vis[to]){
					vis[to]=1,h[R++]=to;
					if(R>=M) R=1;
				}
			}
	}if(v[T]==inf) return 0;
	tot-=1; ans=max(ans,v[T]);
	for(re int u=T;u!=S;u=poi[p[u]^1])
		con[p[u]]-=1,con[p[u]^1]+=1;
	return 1;
}//因为每次流量均为1，可以省去流量数组
void draw(int x,int y){
	re int p=id[x][y];
	if(a[x][y]=='X') return ;
	if(a[x][y]=='D') for(re int i=1;i<=mx;++i) link(p+i*nm,T,1,i);//分层与终点连边，代价=层数
	if(a[x][y]=='.'){
		link(S,p,1,0); ++tot;
		for(re int i=0;i<mx;++i){
			link(p+i*nm,p+(i+1)*nm,1e9,0);
			for(re int j=0;j<4;++j){
				int rx=x+d1[j],ry=y+d2[j];
				if(a[rx][ry]=='X') continue;
				link(p+i*nm,id[rx][ry]+(i+1)*nm,1e9,0);//与四周连边
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);  S=N-4; T=N-3; nm=n*m;
	for(re int i=1;i<=n;++i) scanf("%s",a[i]+1);
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j)
			mx+=(a[i][j]=='.'),id[i][j]=(i-1)*m+j;//mx：人数，建图需要的层数
	for(re int i=1;i<=n;++i) for(re int j=1;j<=m;++j) draw(i,j);
	while(bfs()) ;
	if(tot) puts("impossible");
	else printf("%d",ans);
	return 0;
}
```


---

## 作者：Resurgammm (赞：1)

Floyed $+$ 二分 $+$ 最大流。

不难想到逃离时间具有单调性，所以可以二分一个时间用最大流判断以当前时间是否能使所有人都逃出。

这道题的难点在于建图。

第一个点恶心的点在于每个门一秒只能通过一个人，如果把人直接向门连边跑最大流的话是错的。

考虑这样一组数据：

```
4 5
XXDXX
XX.XX
X...X
XXDXX
```

答案是 $3$ 但会输出 $2$。

考虑将每个门拆开，不同的时间对应不同的门。

这样只要算出人到门的最短时间，从人向这个门所拆出来的对应最短时间的门及其对应时间更长的门连边就可以解决这个问题。

我这里是当输入到门时给它预留出 $400$ 个编号，再记录一下这 $400$ 个门的第一个编号，然后人向从第一个编号 $+$ 最短时间的门到第一个编号 $+$ 二分出来的时间的门连边。

第二个点恶心的点在于有的门是没用的。

考虑这样一组数据：

```
5 4
XDXX
DXXX
D..X
X..X
XXXX
```

答案是 $4$ 但会输出 $3$。

显然 $(1,2)$ 和 $(2,1)$ 的门是没用的，因为不会有人走到那两个位置。

所以判一下每个门周围是不是有人即可。

然后因为点数 $\leq 400$ 跑 Floyed 预处理每个人到每个门的最短时间就行了。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout)
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		if(x<0) putchar('-'),x=-x;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(x,y,sizeof(y))
	
	const int maxn=5e5+5,maxm=5e6+5,inf=0x3f3f3f3f;
	
	int n,m,tot,cnt;
	int mp[25][25],uid[25][25],st[25][25],w[405][405],pos[405][405];
	namespace Graph{
		int head[maxn],id=1;
		struct e{int v,w,next;}edge[maxm<<1];
		inline void add(int u,int v,int w){
			edge[++id].v=v;
			edge[id].w=w;
			edge[id].next=head[u];
			head[u]=id;
		}
	}using namespace Graph;
	namespace MaxFlow{// Dinic 板子
		int s,t,reset[maxn],dis[maxn];
		inline bool bfs(){
			copy(head,reset); fill(dis,inf);
			queue<int> q;
			dis[s]=0; q.push(s);
			while(!q.empty()){
				int u=q.front(); q.pop();
				for(int i=head[u];i;i=edge[i].next) if(edge[i].w){
					int v=edge[i].v;
					if(dis[v]>dis[u]+1){
						dis[v]=dis[u]+1;
						q.push(v);
					}
				}
				if(u==t) return 1;
			}
			return 0;
		}
		int dfs(int u,int in){
			if(u==t) return in;
			int rest=in,out;
			for(int i=head[u];i;head[u]=i=edge[i].next) if(edge[i].w){
				int v=edge[i].v;
				if(dis[v]==dis[u]+1){
					out=dfs(v,min(rest,edge[i].w));
					if(out) edge[i].w-=out,edge[i^1].w+=out,rest-=out;
					else dis[v]=0;
				}
				if(!rest) break;
			}	
			return in-rest;
		}
	}using namespace MaxFlow;
	inline bool check(int x){// 二分 check
		id=1; fill(head,0); fill(reset,0);// 注意把图清空
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(mp[i][j]==2){// 源点和人连边
					add(s,uid[i][j],1),add(uid[i][j],s,0);
					for(int k=1;k<=n;k++)
						for(int l=1;l<=m;l++)
							if(mp[k][l]==3){
								int d=w[pos[i][j]][pos[k][l]];
								//cout<<"("<<i<<","<<j<<") ("<<k<<","<<l<<") "<<d<<"\n";
								for(int o=st[k][l]+d;o<=st[k][l]+min(x,400);o++)
									add(uid[i][j],o,1),add(o,uid[i][j],0);
							}// 人和门连边
				}
				if(mp[i][j]==3)
					for(int o=st[i][j];o<=st[i][j]+min(x,400);o++)
						add(o,t,1),add(t,o,0);
			}// 门和汇点连边
		//cout<<"tim:"<<x<<"\n";
		copy(reset,head);
		int ans=0;
		while(bfs()) ans+=dfs(s,inf);
		//cout<<ans<<"\n";
		return (ans==cnt);// 是否都能逃出
	}
	
	inline int main(){
		n=read(); m=read();
		s=++tot,t=++tot;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				char ch=getchar();
				while(ch!='X' && ch!='.' && ch!='D') ch=getchar();
				if(ch=='X') mp[i][j]=1;
				if(ch=='.') mp[i][j]=2,uid[i][j]=++tot,cnt++;
				if(ch=='D') mp[i][j]=3,st[i][j]=uid[i][j]=++tot,tot+=400;// 预留 400 个门
				pos[i][j]=(i-1)*m+j;
			}
		fill(w,inf);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(mp[i][j]==1) continue;
				if(i-1>=1 && mp[i-1][j]!=1) w[pos[i][j]][pos[i-1][j]]=w[pos[i-1][j]][pos[i][j]]=1;
				if(j-1>=1 && mp[i][j-1]!=1) w[pos[i][j]][pos[i][j-1]]=w[pos[i][j-1]][pos[i][j]]=1;
				if(i+1<=n && mp[i+1][j]!=1) w[pos[i][j]][pos[i+1][j]]=w[pos[i+1][j]][pos[i][j]]=1;
				if(j+1<=m && mp[i][j+1]!=1) w[pos[i][j]][pos[i][j+1]]=w[pos[i][j+1]][pos[i][j]]=1; 
				w[pos[i][j]][pos[i][j]]=0;
			}
		
		for(int k=1;k<=pos[n][m];k++)// Floyed 预处理最短时间
			for(int i=1;i<=pos[n][m];i++)
				for(int j=1;j<=pos[n][m];j++)
					if(w[i][j]>w[i][k]+w[k][j])
						w[i][j]=w[i][k]+w[k][j];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(mp[i][j]==3)
					if(!(mp[i-1][j]==2 || mp[i][j-1]==2 || mp[i+1][j]==2 || mp[i][j+1]==2)){
						for(int k=1;k<=n;k++)
							for(int l=1;l<=m;l++)
								if(k!=i && l!=j) w[pos[i][j]][pos[k][l]]=w[pos[k][l]][pos[i][j]]=inf;
					}// 判门是否合法
		int l=0,r=400,res=inf;
		//cout<<cnt<<" "<<tot<<"\n";
		while(l<=r){
			int mid=(l+r)>>1;
			//cout<<l<<" "<<r<<" "<<mid<<"\n";
			if(check(mid)) r=mid-1,res=mid;
			else l=mid+1;
		}		
		if(res==inf) puts("impossible");
		else printf("%d\n",res);
		return 0;
	}
}
signed main(){return CL::main();}

```

---

## 作者：楠枫 (赞：1)

## 题解
本篇题解做法为 BFS + 二分 + 最大流

二分需要撤离的时间，也就是答案（这算是一个比较套路的了）

重点在于建模（设时间为 $tim$）

我们将每个门拆点，拆成 $tim$ 个，每个点向汇点连边，边权为 $1$，代表每个门在 $tim$ 内能送走的人

将源点和每个空地连边，边权为 $1$ 代表这个空地有一个人

先进行一次 BFS，算出每个人到不同门的时间

将每个人和它在 $tim$ 时间内能到的门连边，边权为 $1$，注意，连的是那个门拆出的 $tim_i$ 门。

如果有多个人在同一时间到达同一个门，怎么解决？我们再将每个门的 $tm$ 向 $tm+1$ 连一条边权为 $\infty$ 的边 $(tm\in [1,tim)\kern 0.6em tm\in Z)$

剩下的就是一些小优化了，记得输入要开 ``scanf("%s")``

```cpp
#include<bits/stdc++.h>
#define ri register signed
#define p(i) ++i
using namespace std;
namespace IO{
    char buf[1<<21],*p1=buf,*p2=buf;
    #define gc() p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++
    inline int read() {
        ri x=0,f=1;char ch=getchar();
        while(ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
        while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
        return x*f;
    }
}
using IO::read;
namespace nanfeng{
    #define node(x,y,id) (node){x,y,id}
    #define jud(x,y) (x>=1&&x<=n&&y>=1&&y<=m&&(k=idp[x][y])>0)
    #define cmax(x,y) ((x)>(y)?(x):(y))
    #define cmin(x,y) ((x)>(y)?(y):(x))
    #define FI FILE *IN
    #define FO FILE *OUT
    #undef bool
    static const int N=25;
    int idp[N][N],dis[N*N][N*N],dx[5]={0,1,0,-1,0},dy[5]={0,0,-1,0,1},tot,out,n,m;
    char s[N];
    struct node{int x,y,id;};
    struct Que{
        node que[N*N];
        int hd,tl;
        inline void init() {hd=1,tl=0;}
        inline void push(node q) {que[p(tl)]=q;}
        inline node top() {return que[hd++];}
        inline bool empty() {return hd>tl;}
    }que;
    inline void bfs(int id,int x,int y) {
        memset(dis[id],127,sizeof(dis[id]));
        que.init();
        que.push(node(x,y,0));
        dis[id][0]=0;//我们将dis的第二维换成点（i，j）的编号，三位数组寻址太慢
        while(!que.empty()) {
            node tmp=que.top();
            for (ri d(1);d<=4;p(d)) {
                int tx=tmp.x+dx[d],ty=tmp.y+dy[d],k;
                if (!jud(tx,ty)) continue;
                if (dis[id][k]>dis[id][tmp.id]+1) dis[id][k]=dis[id][tmp.id]+1,que.push(node(tx,ty,k)); 
            }
        }
    }
    namespace NetworkFlow{//封装
        static const int INF=1e9+7;
        static const int NUM=N*N*N;
        int first[NUM],dep[NUM],cur[NUM],que[NUM],t=2,s,et;
        struct edge{int v,nxt,w;}e[NUM*N*N>>1];
        inline void add(int u,int v,int w) {
            e[t].v=v,e[t].w=w;
            e[t].nxt=first[u];
            first[u]=t++;
        }
        inline void init() {memset(first,0,sizeof(first));t=2;}
        inline void build(ri tim) {
            int tt=out*tim;
            et=tt+tot+1;
            for (ri d(1);d<=out;p(d)) {
                for (ri i(1);i<=tim;p(i)) {
                    ri bs=tim*(d-1);
                    add(bs+i,et,1),add(et,bs+i,0);
                    if (i<tim) add(bs+i,bs+i+1,INF),add(bs+i+1,bs+i,0);
                }
            }
            for (ri i(1);i<=tot;p(i)) add(s,tt+i,1),add(tt+i,s,0);
            for (ri d(1);d<=out;p(d)) {
                for (ri i(1),bs;i<=tot;p(i)) 
                    if (dis[d][i]<=tim) add(tt+i,bs=(d-1)*tim+dis[d][i],1),add(bs,tt+i,0);
            }
        }
        inline bool bfs(int s,int t) {
            memset(dep,0,sizeof(dep));
            int hd=1,tl=0;
            dep[que[p(tl)]=s]=1;
            cur[s]=first[s];
            while(hd<=tl) {
                s=que[hd++];
                for (ri i(first[s]),v;i;i=e[i].nxt) {
                    if (e[i].w&&!dep[v=e[i].v]) {
                        dep[que[p(tl)]=v]=dep[s]+1;
                        cur[v]=first[v];
                        if (v==t) return 1;
                    }
                }
            }
            return 0;
        }
        int dfs(int x,int flow) {
            if (x==et||!flow) return flow;
            int rst=flow;
            for (ri i(cur[x]),v;i&&rst;i=e[i].nxt) {
                if (e[i].w&&dep[v=e[i].v]==dep[x]+1) {
                    ri k=dfs(v,cmin(e[i].w,rst));
                    if (!k) dep[v]=0;
                    e[i].w-=k,e[i^1].w+=k,rst-=k;
                }
                cur[x]=i;//弧优化
            }
            return flow-rst;
        }
        inline int dinic() {
            int res=0;
            while(bfs(s,et)) res+=dfs(s,INF);
            return res;
        }
    }
    inline bool check(int tim) {
        NetworkFlow::init();
        NetworkFlow::build(tim);
        return NetworkFlow::dinic()==tot;
    }
    inline int main() {
        // FI=freopen("nanfeng.in","r",stdin);
        // FO=freopen("nanfeng.out","w",stdout);
        n=read(),m=read();
        for (ri i(1);i<=n;p(i)) {
            scanf("%s",s+1);//记得%s
            for (ri j(1);j<=m;p(j)) 
                if (s[j]=='.') idp[i][j]=p(tot);
                else if (s[j]=='X') idp[i][j]=-1;
        }
        for (ri i(1);i<=n;p(i)) {
            for (ri j(1);j<=m;p(j)) 
                if (!idp[i][j]) bfs(p(out),i,j);
        }
        ri l=0,r=tot+1,res=-1;
        while(l<=r) {
            int mid((l+r)>>1);
            if (check(mid)) r=mid-1,res=mid;
            else l=mid+1;
        }
        res==-1?puts("impossible"):printf("%d\n",res);
        return 0;
    }
}
int main() {return nanfeng::main();}
```

---

## 作者：MarSer020 (赞：0)

$\Large\text{Solution}$

首先看~~标签~~数据范围，$1\le n,m\le 20$，一眼丁真，鉴定为网络流。

然后考虑如何建图：

- 首先考虑可以将源点和每个空地上的人连边，流量为 $1$，代表这个位置上有 $1$ 个人。
- 然后考虑如何给门连边：
	+ 注意到题目限制每个时刻每个门最多出去一个人，那么我们考虑拆点，把每个门拆成若干个时刻上的门，每个点向汇点连边，流量为 $1$，代表每个时刻只能出去一个人。
    + 再考虑一个时刻如果有多个人跑到同一个位置你该怎么办，那就把剩下的人留到下一个时刻再出去，所以每个门每个时刻向这个门下一个时刻的点连边，流量为 $+\infty$。
- 然后你人要从门出去对吧，因为每个空地上都能站无数个人，所以无论如何你的人都不会绕远路，直接把每个空地上的人对最早能到达每个门的时刻的点连边，流量为 $1$，这样就可以了。

然后就有人要问了，你这样连我怎么知道它最早要多久呢？那就直接把时间二分，每次大力重构一遍图，如果此时的最大流就等于人数，那它就是可以的，否则就是不行的。上界大概开个 $500\sim2\times10^3$ 都是可以的，我开的 $10^3$。

然后为了保证复杂度，最开始可以预处理每个空地到每个门的最短路。

这样就可以很好地解决这个问题了，是一道很好的网络流题。

$\Large\text{Code}$

代码比较勾史，将就看看。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
int n,m,s,t,h[100005],tot,lev[100005],mf,dis[25][25][25],cnt,pcnt,l=1,r=1000,mid,ans;
//前面的是dinic板子要用的，cnt是门个数，pcnt是空地个数，dis是空地和门的距离，其他的是二分要用的
char mp[25][25];
queue<int>q;
queue<pair<int,int>>que;//bfs跑最短路用
struct edge{
	int to,val,nxt;
}e[5000005];
void add(int u,int v,int w){
	e[++tot]=(edge){v,w,h[u]},h[u]=tot,e[++tot]=(edge){u,0,h[v]},h[v]=tot;
}
int pid(int x,int y){
    return (x-1)*m+y;
}//获得空地编号
int eid(int x,int y,int z){
    return n*m+(y-1)*x+z;
}//获得某个门某个时刻的点编号
void pre(int x,int y,int cnt){//注意这里是dis=1的位置
    dis[cnt][x][y]=1,que.emplace(make_pair(x,y));
    while(!que.empty()){
        int x=que.front().first,y=que.front().second;
        que.pop();
        if(mp[x-1][y]=='.'&&dis[cnt][x-1][y]==inf)
            dis[cnt][x-1][y]=dis[cnt][x][y]+1,que.emplace(make_pair(x-1,y));
        if(mp[x+1][y]=='.'&&dis[cnt][x+1][y]==inf)
            dis[cnt][x+1][y]=dis[cnt][x][y]+1,que.emplace(make_pair(x+1,y));
        if(mp[x][y-1]=='.'&&dis[cnt][x][y-1]==inf)
            dis[cnt][x][y-1]=dis[cnt][x][y]+1,que.emplace(make_pair(x,y-1));
        if(mp[x][y+1]=='.'&&dis[cnt][x][y+1]==inf)
            dis[cnt][x][y+1]=dis[cnt][x][y]+1,que.emplace(make_pair(x,y+1));
    }//大力最短路
}
void init(){
    cin>>n>>m,s=0,t=1;//因为1号点肯定不会被用到就用来存汇点
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>mp[i][j],pcnt+=(mp[i][j]=='.');
    for(int i=2;i<n;i++){
        if(mp[i][1]=='D'&&mp[i][2]=='.')//注意判空地
            pre(i,2,++cnt);
        if(mp[i][m]=='D'&&mp[i][m-1]=='.')
            pre(i,m-1,++cnt);
    }
    for(int i=2;i<m;i++){
        if(mp[1][i]=='D'&&mp[2][i]=='.')
            pre(2,i,++cnt);
        if(mp[n][i]=='D'&&mp[n-1][i]=='.')
            pre(n-1,i,++cnt);
    }
}
bool bfs(){
	memset(lev,0,sizeof(lev));
	while(!q.empty())
		q.pop();
	q.emplace(s);
	lev[s]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=h[u];i;i=e[i].nxt)
			if(e[i].val){
				int v=e[i].to;
				if(lev[v])
					continue;
				lev[v]=lev[u]+1;
				q.emplace(v);
				if(v==t)
					return 1;
			}
	}
	return 0;
}//板子
int dinic(int x,int fl){
	if(x==t)
		return fl;
	int res=fl,inc;
	for(int i=h[x];i&&res;i=e[i].nxt)
		if(e[i].val){
			int v=e[i].to;
			if(lev[v]!=lev[x]+1)
				continue;
			inc=dinic(v,min(res,e[i].val));
			if(!inc){
				lev[v]=0;
				continue;
			}
			e[i].val-=inc,e[i^1].val+=inc,res-=inc;
		}
	return fl-res;
}//板子
bool check(int x){
    tot=1,mf=0;
    memset(h,0,sizeof(h));
    for(int i=2;i<n;i++)
        for(int j=2,tmp;j<m;j++)
            if(mp[i][j]=='.'){
                tmp=pid(i,j),add(s,tmp,1);
                for(int k=1;k<=cnt;k++)
                    if(dis[k][i][j]<=x)
                        add(tmp,eid(x,k,dis[k][i][j]),1);
            }
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<x;j++)
            add(eid(x,i,j),eid(x,i,j+1),inf),add(eid(x,i,j),t,1);
        add(eid(x,i,x),t,1);
    }//大力重构
    while(bfs())
        mf+=dinic(s,inf);//板子
    return mf==pcnt;//判一下是不是满足条件
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	init();//预处理
    while(l<=r){//二分
        mid=(l+r)>>1;
        if(check(mid))
            ans=mid,r=mid-1;
        else
            l=mid+1;
    }
    if(ans)
        cout<<ans;
    else
        cout<<"impossible";
	return 0;
}
```

---

## 作者：Gary818 (赞：0)

如果图挂了就看[这个](https://www.cnblogs.com/rui-4825/p/13983295.html)吧

## Solution
### 二分答案
看到题目不难想到  
假设给定一个时间  
那么可以验证当前时间内能不能保证所有的人跑出去  
显然，时间越长，能跑掉的人越多  
所以答案具有单调性  
可以进行二分  
如果当前时间都可以跑出去  
那么考虑适当缩小答案（减少时间）  
反之，扩大答案（增加时间）  
  
### 建图  
身为网络流最核心的部分  
这道题建图ex死了，加上本人菜死了，足足改了4天  
建立超级源点s，超级汇点t  
先来说时间对答案的影响  
假设现在拥有一个答案时间为$x$  
那么相当于把每个门拆出来$x$个门  
保证在x时间内，每个门都能通过一个人  
拆出的门按照拆出的编号从小到大依次建边  
（比如拆出了1，2，3，那么就1到2，2到3分别建边，边权为inf，表示不受限制）  
由于每个人到门的距离不同  
所以人应该指向门拆出的第距离个门（md好乱）  
没错我知道这句话没人看明白  
举个栗子  
有一个人他站在坐标7  
有一个门它在坐标9  
人和门相距距离为3  
就是这个图（我把二维拍成一维了）  
$\begin{matrix}
 &X  &X  &X &X \\ 
 &X  &.  &.  &X \\ 
 &D  &.  &X  &X \\ 
 &X  &X  &X  &X 
\end{matrix}$
如果现在二分出一个答案为3  
那么就要把坐标9按照某种对应方式（这个对应自己随便编一下，只要保证门编号不重复即可）拆开  
由于7号点的人到门的距离为3  
那么应该向9拆出的第三个门建边  
像这样（右边的点是拆出来的新门）  
![](https://img2020.cnblogs.com/blog/1718530/202011/1718530-20201116070530767-1130136569.png)

剩下的边就是传统方法了  
s到所有人建，边权为1  
所有门到t建，边权为1  
可以看下样例  
在时间为3的时候图长这个样子  
![](https://img2020.cnblogs.com/blog/1718530/202011/1718530-20201116070720796-1105085959.png)

### BFS
要预处理出所有人到所有门的距离  
bfs扫一遍即可  

## Code
注 意 细 节  
我写的代码比较麻烦  
尤其是建边那一块  
只要不重不漏，门编号可以简单点不一定非要按照这个写  
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#define min(a, b) ({register int AA = a, BB = b; AA < BB ? AA : BB;})
#define inf 0x7fffffff
using namespace std;

inline int read(){
	int x = 0, w = 1;
	char ch = getchar();
	for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') w = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	return x * w;
}

const int ss = 300005;
const int dx[5] = {0, 1, 0, -1};
const int dy[5] = {1, 0, -1, 0};

struct node{
	int to, nxt, w;
}edge[ss];

int head[ss], tot = 1;
inline void add(register int u, register int v, register int w){
	edge[++tot].to = v;
	edge[tot].nxt = head[u];
	edge[tot].w = w;
	head[u] = tot;
}

int pre[405][405];
int cur[ss], dis[ss];
bool vis[405][405];
int n, m, s, t;
queue<int> q;
inline bool bfs(register int s){
	for(register int i = 0; i <= t; i++)
		dis[i] = 0x3f3f3f3f, cur[i] = head[i];
	dis[s] = 0;
	q.push(s);
	while(!q.empty()){
		register int u = q.front();
		q.pop();
		for(register int i = head[u]; i; i = edge[i].nxt){
			register int v = edge[i].to;
			if(dis[v] == 0x3f3f3f3f && edge[i].w){
				q.push(v);
				dis[v] = dis[u] + 1;
			}
		}
	}
	return dis[t] != 0x3f3f3f3f;
}

inline int dfs(register int u, register int flow){
	register int res = 0;
	if(u == t) return flow;
	for(register int i = cur[u]; i; i = edge[i].nxt){
		cur[u] = i;
		register int v = edge[i].to;
		if(dis[v] == dis[u] + 1 && edge[i].w){
			if(res = dfs(v, min(flow, edge[i].w))){
				edge[i].w -= res;
				edge[i ^ 1].w += res;
				return res;
			}
		}
	}
	return 0;
}

long long maxflow;
inline long long dinic(){
	register long long minflow = 0;
	while(bfs(s)){
		while(minflow = dfs(s, 0x7fffffff))
			maxflow += minflow;
	}
	return maxflow;
}

inline int change(register int i, register int j){
	return (i - 1) * m + j;
}

int a[25][25], person, cnt;
char ch[25];

int l = 1, r = 400;
inline bool check(register int x){
	memset(head, 0, sizeof head);
	tot = 1;
	for(register int i = 1; i <= n; i++)
		for(register int j = 1; j <= m; j++)
			if(a[i][j] == 1) add(s, change(i, j), 1), add(change(i, j), s, 0);
	for(register int i = 1; i <= n; i++){
		for(register int j = 1; j <= m; j++){
			if(a[i][j] == 2){//门
				for(register int id = change(i, j) * x; id < (change(i, j) + 1) * x; id++){
					add(id + n * m, t, 1);
					add(t, id + n * m, 0);
				}
				for(register int id = change(i, j) * x; id < (change(i, j) + 1) * x - 1; id++){
					add(id + n * m, id + n * m + 1, inf);
					add(id + n * m + 1, id + n * m, 0);
				}
				for(register int p = 1; p <= n; p++){
					for(register int q = 1; q <= m; q++)
						if(a[p][q] == 1){//人
							if(pre[change(p, q)][change(i, j)] <= x){
								add(change(p, q), change(i, j) * x + n * m + pre[change(p, q)][change(i, j)] - 1, inf);
								add(change(i, j) * x + n * m + pre[change(p, q)][change(i, j)] - 1, change(p, q) ,0);
							}
						}
				}
			}
		}
	}
	maxflow = 0;
	return dinic() >= person;
}

int st, ed;
queue<pair<int, int> > que;
inline void matrix(register int x, register int y){
	que.push(make_pair(x, y));
	pre[change(x, y)][change(x, y)] = 0;
	while(!que.empty()){
		register int xxx = que.front().first, yyy = que.front().second;
		que.pop();
		for(register int i = 0; i < 4; i++){
			register int xx = xxx + dx[i], yy = yyy + dy[i];
			if(xx < 0 || xx > n || yy < 0 || yy > m || a[xx][yy] != 1 || vis[xx][yy]) continue;
			vis[xx][yy] = 1;
			if(pre[change(xx, yy)][change(st, ed)] > pre[change(xxx, yyy)][change(st, ed)] + 1){
				que.push(make_pair(xx, yy));
				pre[change(xx, yy)][change(st, ed)] = pre[change(xxx, yyy)][change(st, ed)] + 1;
			}
		}
	}
}

signed main(){
	memset(pre, 0x3f, sizeof pre);
	n = read(), m = read();
	for(register int i = 1; i <= n; i++){
		scanf("%s", ch + 1);
		for(register int j = 1; j <= m; j++){
			if(ch[j] == '.') a[i][j] = 1, person++;
			else if(ch[j] == 'D') a[i][j] = 2, cnt++;
			else a[i][j] = 0;
		}
	}
	for(register int i = 1; i <= n; i++)
		for(register int j = 1; j <= m; j++){
			if(a[i][j] == 2){
				memset(vis, 0, sizeof vis);
				st = i, ed = j;
				matrix(i, j);
			}
		}
	s = 0, t = 30000;
	while(l <= r){
		register int mid = l + r >> 1;
		if(check(mid)) r = mid - 1;
		else l = mid + 1;
	}
	if(l == 401) puts("impossible");
	else printf("%d\n", l);
	return 0;
}
```


---

## 作者：STrAduts (赞：0)

### Sol.

可以发现人的移动除了不能穿墙以外没有别的限制。也就是说人的移动多半不是解题的突破口。

接下来会发现出口的限制很强，即出口每个时刻只能允许一个人出去。

每个时刻？

不难想到对于每一个时刻每一个门，我们单独考虑。也就是说每一个门具有三个属性，横坐标、纵坐标、时间坐标。

于是我们就有了很多很多的门，就可以将限制转换为每一个门都只能让该时刻到达的那一个人出去。

每一扇门仅允许一个人？

这就是一个匹配问题嘛。并且如果考虑人作为左部，门作为右部，这就是一个简单的二分图最大匹配。

显然可以通过 bfs 求得每一个人到任意一扇门所需的时间，设坐标 $(U_x, U_y)$ 这个人到坐标 $(V_x, V_y)$ 这扇门需要 $t$ 的时间。

也就是说当前这个点对于这扇门可以走所有空间坐标 $(V_x, V_y)$，时间坐标晚于 $t$ 的所有门。

但这只能判断可行性，难以算出具体答案啊？

容易想到直接二分答案。若当前二分到答案 $T$，我们就可以将门的空间坐标限制到 $[t, T]$ 内，然后每个人相对于可以走的门连边跑匈牙利即可。

可以简单估算一下二分上界。假设有 $nm - 1$ 个人，$1$ 扇门，最远的人到达这扇门的距离是 $n + m$，而不能发现每个时候都会有人到达，所以上界应是 $n m$。

另外一种情况，一个人为了绕开所有墙，最多也只会耗费 $n m$ 的时间，且对于门来说，$n m$ 的时间一定可以把人全部送出去。

---

### Code.

```cpp
#include <queue>
#include <cstdio>
using namespace std;

int Abs(int x) { return x < 0 ? -x : x; }
int Max(int x, int y) { return x > y ? x : y; }
int Min(int x, int y) { return x < y ? x : y; }

int read() {
    int k = 1, x = 0;
    char s = getchar();
    while (s < '0' || s > '9') {
        if (s == '-')
            k = -1;
        s = getchar();
    }
    while (s >= '0' && s <= '9') {
        x = (x << 3) + (x << 1) + s - '0';
        s = getchar();
    }
    return x * k;
}

void write(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

void print(int x, char s) {
    write(x);
    putchar(s);
}

const int MAXM = 2e6 + 5;
const int MAXN = 2e4 + 5;

struct Bipartite_Graph {
    struct edge {
        int v, nxt;
        edge() {}
        edge(int V, int Nxt) {
            v = V, nxt = Nxt;
        }
    } e[MAXM << 1];
    int head[MAXN], n, cnt;
    void Add_Edge(int u, int v) { 
        e[cnt] = edge(v, head[u]);
        head[u] = cnt++;
    }
    int Mat[MAXN], Tim[MAXN], p[MAXN], len, tot;

    void init(int N) {
        n = N;
        for(int i = 1; i <= n; i++) 
            head[i] = -1, Tim[i] = 0, Mat[i] = 0;
        cnt = 0, tot = 0, len = 0;
    }

    bool dfs(int u) {
        if (Tim[u] == tot)
            return false;        
        Tim[u] = tot;
        for (int i = head[u], v; ~i; i = e[i].nxt) {
            v = e[i].v;
            if (!Mat[v] || dfs(Mat[v])) {
                Mat[v] = u;
                return true;
            }
        }
        return false;
    }

    int calc() {
        int ans = 0;
        for (int i = 1; i <= len; i++) {
            tot++;
            ans += dfs(p[i]);
        }
        return ans;
    }    
} Graph; // 二分图最大匹配模板。

char s[MAXN][MAXN];
int pos[MAXN][MAXN], dist[MAXN][MAXN], n, m, num, cnt;

struct node {
    int x, y;
    node() {}
    node(int X, int Y) {
        x = X, y = Y;
    }
};
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
void bfs(node st) { // 求人到门所需时间。
    queue<node> q;
    q.push(st);
    while(!q.empty()) {
        node u = q.front(); q.pop();
        for(int i = 0, cx, cy; i < 4; i++) {
            cx = u.x + dir[i][0], cy = u.y + dir[i][1];
            if(cx < 1 || cx > n || cy < 1 || cy > m)
                continue;
            if(s[cx][cy] == '.' && !dist[pos[st.x][st.y]][pos[cx][cy]]) {
                dist[pos[st.x][st.y]][pos[cx][cy]] = dist[pos[st.x][st.y]][pos[u.x][u.y]] + 1;
                q.push(node(cx, cy));
            }
        }
    }
}

bool check(int mid) { // 二分可行性判断。
    Graph.init(num + (cnt - num) * mid);   
    for(int i = 1; i <= num; i++) {
        Graph.p[++Graph.len] = i;
        for(int j = num + 1; j <= cnt; j++)
            if(dist[j][i])
                for(int k = dist[j][i]; k <= mid; k++)
                    Graph.Add_Edge(i, j + (k - 1) * (cnt - num)); // 时间范围内 拆点 建边
    }
    int res = Graph.calc(); 
    return res >= num;
}

int main() {
    n = read(), m = read();
    num = 0;
    for(int i = 1; i <= n; i++) {
        scanf ("%s", s[i] + 1);        
        for(int j = 1; j <= m; j++)
            if(s[i][j] == '.')
                pos[i][j] = ++num; 
    }
    cnt = num;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) 
            if(s[i][j] == 'D') {
                cnt++;
                pos[i][j] = cnt;
                bfs(node(i, j));
            }
    // 这部分处理打得有点奇怪了，转整数标号还是按照自己的喜好来。
    int l = 0, r = n * m * 2, mid, res = -1;
    while(l <= r) {
        mid = (l + r) >> 1;
        if(check(mid)) {
            r = mid - 1;
            res = mid;
        }
        else    
            l = mid + 1;
    }
    if(res == -1)
        printf("impossible\n");
    else
        print(res, '\n');
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

先由S向每个有人的点连一条容量为1的边，然后二分时间t，对于每个每个门拆成t个点，每个点向T和下一个时间的点分别连容量为1和inf的边，表示这个门可以在每个时间里出来一个人，多余的人等到下一个时间

'''cpp
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cassert>
#include<cstring>
#include<algorithm>
#define maxn 160000
#define maxm 400000
#define inf 1061109567
using namespace std;
char ch;
bool ok;
void read(int &x){
    for (ok=0,ch=getchar();!isdigit(ch);ch=getchar()) if (ch=='-') ok=1;
    for (x=0;isdigit(ch);x=x*10+ch-'0',ch=getchar());
    if (ok) x=-x;
}
char graph[22][22];
int n,m,cnt,pos[22][22],l,r,mid;
struct flow{
    int s,t,idx,tot,now[maxn],son[maxm],pre[maxm],val[maxm];
    int dis[maxn],head,tail,list[maxn];
    bool bo[maxn];
    void init(){s=0,t=1,idx=1,tot=1,memset(now,0,sizeof(now));}
    void put(int a,int b,int c){pre[++tot]=now[a],now[a]=tot,son[tot]=b,val[tot]=c;}
    void add(int a,int b,int c){put(a,b,c),put(b,a,0);}
    bool bfs(){
        memset(bo,0,sizeof(bo));
        head=0,tail=1,list[1]=s,bo[s]=1,dis[s]=0;
        while (head<tail){
            int u=list[++head];
            for (int p=now[u],v=son[p];p;p=pre[p],v=son[p])
                if (val[p]&&!bo[v]) bo[v]=1,dis[v]=dis[u]+1,list[++tail]=v;
        }
        return bo[t];
    }
    int dfs(int u,int rest){
        if (u==t) return rest;
        int ans=0;
        for (int p=now[u],v=son[p];p&&rest;p=pre[p],v=son[p])
            if (val[p]&&dis[v]==dis[u]+1){
                int d=dfs(v,min(rest,val[p]));
                val[p]-=d,val[p^1]+=d,ans+=d,rest-=d;
            }
        if (!ans) dis[u]=-1;
        return ans;
    }
    int dinic(){
        int ans=0;
        while (bfs()) ans+=dfs(s,inf);
        return ans;
    }
}f,tmp;
struct Point{
    int x,y,id;
}list[405];
int head,tail,g[405][405],dep[42][42];
bool bo[42][42],flag;
const int dx[4]={1,0,-1,0};
const int dy[4]={0,1,0,-1};
void bfs(int x,int y,int id){
    memset(bo,0,sizeof(bo));
    head=0,tail=1,list[1]=(Point){x,y,0},bo[x][y]=1,dep[x][y]=0;
    while (head<tail){
        Point p=list[++head];
        int d=dep[p.x][p.y];
        if (d) g[p.id][id]=d;
        for (int i=0;i<4;i++){
            int xx=p.x+dx[i],yy=p.y+dy[i];
            if (xx<=0||xx>n||yy<=0||yy>m||graph[xx][yy]!='.'||bo[xx][yy]) continue;
            list[++tail]=(Point){xx,yy,pos[xx][yy]},bo[xx][yy]=1,dep[xx][yy]=d+1;
        }
    }
}
bool check(int lim){
    f=tmp;
    for (int i=2;i<=f.idx;i++) for (int j=1;j<=cnt;j++) if (g[i][j]<=lim&&g[i][j])
        f.add(i,f.idx+cnt*(g[i][j]-1)+j,1);
    for (int i=1;i<=cnt;i++) for (int j=1;j<=lim;j++){
        f.add(f.idx+cnt*(j-1)+i,f.t,1);
        if (j!=lim) f.add(f.idx+cnt*(j-1)+i,f.idx+cnt*j+i,inf);
    }
    return f.dinic()==f.idx-1;
}
int main(){
    read(n),read(m),f.init();
    for (int i=1;i<=n;i++) scanf("%s",graph[i]+1);
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++)
        if (graph[i][j]=='.') pos[i][j]=++f.idx,f.add(f.s,f.idx,1);
        else if (graph[i][j]=='D') pos[i][j]=++cnt;
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) if (graph[i][j]=='D') bfs(i,j,pos[i][j]);
    for (int i=2;i<=f.idx;i++){
        bool fuck=1;
        for (int j=1;j<=cnt;j++) if (g[i][j]!=0) fuck=0;
        if (fuck){flag=1;break;}
    }
    if (flag){puts("impossible");return 0;}
    for (tmp=f,l=1,r=400,mid=(l+r)>>1;l<r;mid=(l+r)>>1) if (check(mid)) r=mid; else l=mid+1;
    printf("%d\n",l);
    return 0;
}
'''
```

---

## 作者：kakakaka (赞：0)

题解：(详见本人博客:<http://www.cnblogs.com/huangdalaofighting/>)

这是一道二分答案与网络流算法的结合的题目，小编也是头一次做这样的题目，所以被坑了很久。

一开始没有什么头绪，后来才发现可以先SPFA一下每一个点到门的距离（也就是时间），然后二分时间求解。

1.这道题可以考虑拆点，也可以考虑拆门，显然拆门更简单，于是就果断将每一个门拆成mid个不同的点，如果一个点可以在mid时间内到达一个门d，那么就将这个点和d的mid分点连在一起。

2.虚拟一个汇点和每一个门连一条流量为1的边，虚拟一个源点和每一个点连一条流量为1的边，其余的边流量为最大值。（这样就保证了同一时间只有一个人可以通过一扇门）

3.然后不断地跑Dinic求最大流。如果可行则说明在mid时间时可以逃生，r=mid-1，如果不可行则l=mid+1。（普通的二分答案）

需要注意的地方：

1.size的初值为奇数，不然就没法跑Dinic。

2.数组的大小。（本人运行错误了好多次，所以代码中的数组开得比较大，实际上不需要这么多）

好了，应该可以上代码了：

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<cstring>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<queue>
#include<stack>
using namespace std;
const int inf=233;
int n,m;
int place[201][301],depth[40001],map[40001],dis[1001][1001],root,g,sum,q[501][40001],flow=0;
int xx[40001],yy[40001],t[5]={1,0,-1,0,1};
int head[40001],size;
struct Edge
{
    int next,to,dis;
}edge[100001];
int b[40001];
vector<int>p;
int read()
{
    char i=getchar();int ans=0,f=1;
    while(i<'0'||i>'9')if(i=='-')f=-1,i=getchar();
    while(i>='0'&&i<='9')ans=ans*10+i-'0',i=getchar();
    return ans*f;
}
void spfa(int x,int y)
{
    int i,j,head=0,tail=0;
    xx[tail]=x;yy[tail++]=y;
    for(i=1;i<=g;i++)dis[place[x][y]][i]=inf;
    dis[place[x][y]][place[x][y]]=0;
    while(head!=tail)
    {
        int xxx=xx[head],yyy=yy[head++];
        for(i=0;i<4;i++)
        {
            int nx=xxx+t[i],ny=yyy+t[i+1];
            if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&map[place[nx][ny]]&&dis[place[x][y]][place[nx][ny]]>dis[place[x][y]][place[xxx][yyy]]+1)
            {
                dis[place[x][y]][place[nx][ny]]=dis[place[x][y]][place[xxx][yyy]]+1;
                if(map[place[nx][ny]]==1)
                {
                    xx[tail]=nx;
                    yy[tail++]=ny;
                }
            }
        }
    }
}
void putin(int from,int to,int dis)
{
    size++;
    edge[size].next=head[from];
    edge[size].to=to;
    edge[size].dis=dis;
    head[from]=size;
}
void in(int from,int to,int dis)
{
    putin(from,to,dis);
    putin(to,from,0);
}
bool bfs()
{
    int i;
    for(i=root;i<=g;i++)depth[i]=0;
    int top=0,tail=0;
    b[tail++]=root;depth[root]=1;
    while(top!=tail)
    {
        int x=b[top++];
        if(x==g)return 1;
        for(i=head[x];i;i=edge[i].next)
        {
            int y=edge[i].to;
            if(depth[y]==0&&edge[i].dis)
            {
                depth[y]=depth[x]+1;
                b[tail++]=y;
            }
        }
    }
    return 0;
}
int dfs(int root,int mmax)
{
    int i;
    if(root==g)return mmax;
    int rev=0;
    for(i=head[root];i;i=edge[i].next)
    {
        int y=edge[i].to,x=edge[i].dis;
        if(depth[y]==depth[root]+1&&x)
        {
            int mmin=min(mmax-rev,x);
            x=dfs(y,mmin);
            edge[i].dis-=x;
            edge[i^1].dis+=x;
            rev+=x;
            if(rev==mmax)break;
        }
    }
    return rev;
}
bool judge(int mid)
{
    memset(head,0,sizeof(head));
    size=1;
    g=sum;
    int i,j,k;
    for(i=0;i<p.size();i++)
        for(j=0;j<=mid;j++)
            q[p[i]][j]=++g;
    g++;
    for(i=0;i<p.size();i++)
        for(j=0;j<=mid;j++)
        {
            in(q[p[i]][j],g,1);
            if(j!=mid)in(q[p[i]][j],q[p[i]][j+1],inf);
        }
    int ret=0;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            if(map[place[i][j]]==1)
            {
                ret++;
                in(root,place[i][j],1);
                for(k=0;k<p.size();k++)
                {
                    if(dis[place[i][j]][p[k]]<=mid)
                    {
                        in(place[i][j],q[p[k]][dis[place[i][j]][p[k]]],1);
                    }
                }
            }
        }
    }
    flow=0;
    while(bfs())
    {
        flow+=dfs(root,2000000000);
    }
    return flow==ret;
}
int main()
{
    int i,j;
    n=read();m=read();
    root=0;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
        place[i][j]=++g;
    sum=g;
    char ch[101];
    for(i=1;i<=n;i++)
    {
        scanf("%s",ch+1);
        for(j=1;j<=m;j++)
        {
            if(ch[j]=='.')map[place[i][j]]=1;
            if(ch[j]=='D')map[place[i][j]]=2,p.push_back(place[i][j]);
        }
    }
    if(p.size()==0){printf("impossible");return 0;}
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
            if(map[place[i][j]]==1)spfa(i,j);
    }
    int l=0,r=inf,ans=inf;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(judge(mid))r=mid-1,ans=mid;
        else l=mid+1;
    }
    if(ans==inf)printf("impossible");
    else printf("%d\n",ans);
    return 0;
}
```

---

