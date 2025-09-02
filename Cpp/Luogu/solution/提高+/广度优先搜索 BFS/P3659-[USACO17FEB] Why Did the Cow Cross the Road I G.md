# [USACO17FEB] Why Did the Cow Cross the Road I G

## 题目描述

奶牛为什么要过马路？其中一个原因是 Farmer John 的农场有很多道路，使得他的奶牛在四处走动时不可避免地要穿过许多道路。

FJ 的农场被安排成一个 $N \times N$ 的方形网格田地（$3 \leq N \leq 100$），其中有 $N-1$ 条南北向的道路和 $N-1$ 条东西向的道路穿过农场内部，作为田地之间的分隔。农场外部有一圈高高的围栏，防止奶牛离开农场。奶牛 Bessie 可以自由地从任何田地移动到相邻的田地（北、东、南或西），只要她在穿过分隔两块田地的道路时小心地左右看看。她穿过一条道路需要花费 $T$ 单位时间（$0 \leq T \leq 1,000,000$）。

有一天，FJ 邀请 Bessie 去他家进行一场友好的国际象棋比赛。Bessie 从西北角的田地出发，而 FJ 的家在东南角的田地，因此 Bessie 需要走很长一段路。由于她在路上会感到饥饿，她会在每经过第三个田地时停下来吃草（不包括她的起始田地，但可能包括最终到达的 FJ 家的田地）。有些田地的草比其他田地更茂盛，因此停下来吃草所需的时间取决于她停下的田地。

请帮助 Bessie 确定她到达 FJ 家所需的最少时间。

## 说明/提示

这个例子的最优解是向东移动 3 个方格（吃“10”），然后向南移动两次，向西移动一次（吃“5”），最后向南和向东移动到目的地。

## 样例 #1

### 输入

```
4 2
30 92 36 10
38 85 60 16
41 13 5 68
20 97 13 80```

### 输出

```
31```

# 题解

## 作者：Rachel_in (赞：20)

# 没看见有SPFA的题解，那我就来一发吧！
我们对于每一个位置，将他们与自己走三步的点进行连边，边的权值为$t*3+$到达的点的权值。如图所示（注意它可以向上再向下再向上这类的情况，所以有16个方向）：

![](https://cdn.luogu.com.cn/upload/pic/52757.png)

随后，从起点$(1,1)$跑一遍SPFA，最后统计答案分别从$(n,n),(n-1,n),(n,n-1),(n-2,n),(n,n-2),(n-1,n-1)$中转移过来。具体看代码。

由于本题边的构造可以发现很难卡SPFA，~~SPFA没有死~~，而且就算卡了复杂度也可以接受QWQ

```cpp
#include<bits/stdc++.h>
#include<queue>
using namespace std;
const int N=105;
inline int read(){//快读
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int cnt,fir[N*N],nxt[N*N*16],go[N*N*16],val[N*N*16];//邻接表存边
int n,t,a[N][N];
long long ans,d[N*N];
bool vis[N*N];
int h(int x,int y)//给每个点设立一个编号
{
	return (x-1)*n+y;	
}
inline void Add(int u,int v,int w)
{
	nxt[++cnt]=fir[u];	
	fir[u]=cnt;
	go[cnt]=v;
	val[cnt]=w;
}//连边
const int dx[16]={-2,-1,1,2,2,1,-1,-2,0,1,0,-1,0,3,0,-3};
const int dy[16]={1,2,2,1,-1,-2,-2,-1,1,0,-1,0,3,0,-3,0};//枚举16个方向

inline void COCO_made_me_Do_it(int x,int y)
{
	for(int i=0;i<16;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];	
		if(xx>0&&xx<=n&&yy>0&&yy<=n)//判断是否越界
		{
			Add(h(x,y),h(xx,yy),a[xx][yy]+3*t);//建边；
		}	
	}
}
queue<int> q;
void SPFA(int x,int y)//SPFA跑最短路
{
	memset(vis,false,sizeof(vis));
	memset(d,0x3f,sizeof(d));
	d[h(x,y)]=0;
	vis[h(x,y)]=true;
	q.push(h(x,y));
	while(!q.empty())
	{
		int xx=q.front();q.pop();
		vis[xx]=false;
		for(int e=fir[xx];e;e=nxt[e])
		{
			int yy=go[e];
			if(d[xx]+val[e]<d[yy])
			{
				d[yy]=d[xx]+val[e];	
				if(!vis[yy])
				{
					vis[yy]=true;q.push(yy);
				}
			}
		}	
	}
}
int main()
{
	n=read();t=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			a[i][j]=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			COCO_made_me_Do_it(i,j);
	SPFA(1,1);
	ans=0x7fffffff;
	ans=min(ans,d[h(n,n)]);
	if(n>=2)ans=min(ans,d[h(n,n-1)]+t);
	if(n>=2)ans=min(ans,d[h(n-1,n)]+t);
	if(n>=3)ans=min(ans,d[h(n-2,n)]+2*t);
	if(n>=3)ans=min(ans,d[h(n,n-2)]+2*t);
	if(n>=2)ans=min(ans,d[h(n-1,n-1)]+2*t);//没什么意义的特判，更新答案
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：fighter (赞：8)

# P3659 [USACO17FEB]Why Did the Cow Cross the Road

​	翻了翻题解，好像大部分都是用跨三步连边转移的方式来跑最短路。但我一看到这道题，就发现了一个特征：

​	**奶牛每走一步，并不影响整张地图的结构，只是改变了自身的状态**，也就是改变了自身走几步之后需要休息。这是一个很明显的**分层图**模板。

​	于是，我们可以把整张地图分层。我们考虑分为4层，第0层表示一步都没有走过，即刚刚休息完时的状态，第1、2、3层则分别表示走了1、2、3步后的状态，所以对于0、1、2层，只需要向四周扩展，并向下一层连边，边权为穿过马路的时间T，而第三层较为特殊，我们把第3层的点和它自身在第0层的点连边，边权为这个网格内停留的时间，表示在这个网格休息。然后无脑跑最短路（代码中为堆优化dijkstra）。

​	对于答案的统计，要注意到题目中的一个条件，**需要休息的点可能包括终点**，于是我们就不能统计第三层的终点答案，因为此时奶牛已经需要休息了，必须到第0层才能统计答案。

## Code

```cpp
#include <bits/stdc++.h>
#define MAXB 105
#define MAXN 40005
#define MAXM 200005
#define ll long long
#define get(x,y) ((x-1)*n+y)
using namespace std;

int n, T, cnt;
int head[MAXN], vet[MAXM], Next[MAXM];
ll cost[MAXM], val[MAXB][MAXB];

void add(int x, int y, ll w) {
    cnt++;
    Next[cnt] = head[x];
    head[x] = cnt;
    vet[cnt] = y;
    cost[cnt] = w;
}

const int mx[] = {1, 0, -1, 0};
const int my[] = {0, 1, 0, -1};

void build() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int k = 0; k < 3; k++) {
                for(int l = 0; l < 4; l++) {
                    int u = i + mx[l], v = j + my[l];
                    if(u<=0 || u>n || v<=0 || v>n)
                        continue;
                    add(get(i,j)+k*n*n, get(u,v)+(k+1)*n*n, T);
                }
            }
            add(get(i,j)+3*n*n, get(i,j), val[i][j]);
        }
    }
}

struct node{
    int ord;
    ll dis;
    friend bool operator <(node n1, node n2){
        return n1.dis > n2.dis;
    }
};

ll dis[MAXN];
priority_queue<node> q;
void dijkstra(){
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    q.push((node){1, 0});
    while(!q.empty()){
        node t = q.top();
        q.pop();
        if(t.dis > dis[t.ord])
            continue;
        for(int i = head[t.ord]; i; i = Next[i]){
            int v = vet[i];
            if(dis[v] > t.dis+cost[i]){
                dis[v] = t.dis+cost[i];
                q.push((node){v, dis[v]});
            }
        }
    }
}

int main() {
    cin >> n >> T;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            scanf("%d", &val[i][j]);
        }
    }
    build();
    dijkstra();
    ll ans = 1e17;
    for(int i = 1; i <= 3; i++){
        ans = min(ans, dis[i*n*n]);
    }
    cout << ans << endl;

    return 0;
}
```



---

## 作者：Okarin (赞：8)

这道题其实根本不用什么算法技巧，直接爆搜就可以过。

BFS和DFS随便选，但是DFS可能会爆，毕竟BFS可以用循环队列来优化空间，最后一个点好像只能用循环队列不然过不去。

队列分别存x,y,步数，花费。因为只有在走第3步时才会“吃草”，所以步数直接%3来判断就好了。

再放一个visit数组来记录。数组开3维，分别表示在x,y且步数为z时的最小花费。每当我们搜到一个点时，如果花费大于这个最小花费，就直接剪掉。

~~可能这个算记忆化然后剪枝？不管了，就是爆搜！~~

丢代码
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<set>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
inline int read()
{
    int sum=0;
    char ch =getchar();
    while(ch<'0'||ch>'9')
        ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        sum=sum*10+ch-'0';
        ch=getchar();
    }
    return sum;
}
void write(int x)
{
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n,m;
int Map[105][105],q[10000005][4],dx[4]={0,1,-1,0},dy[4]={1,0,0,-1};
int visit[105][105][4];
int main()
{
	memset(visit,63,sizeof(visit));
	n=read();m=read();
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=n;++j)
			Map[i][j]=read();
	int head=1,tail=1;
	q[1][0]=1;q[1][1]=1;
	q[1][2]=0;q[1][3]=0;
	visit[1][1][0]=0;
	while(head<=tail)
	{
		if(tail>1000005)
		{
			int delta=tail-head+1;
			for(register int i=1;i<=delta;++i)
			{
				q[i][0]=q[head+i-1][0];
				q[i][1]=q[head+i-1][1];
				q[i][2]=q[head+i-1][2];
				q[i][3]=q[head+i-1][3];
			}
			head=1;
			tail=delta;
		}
		for(register int i=0;i<4;++i)
		{
			int x=q[head][0]+dx[i],y=q[head][1]+dy[i];
			if(x>=1&&x<=n&&y>=1&&y<=n)
			{
				q[++tail][2]=(q[head][2]+1)%3;
				if(q[tail][2]==0)
					q[tail][3]=q[head][3]+m+Map[x][y];
				else
					q[tail][3]=q[head][3]+m;
				if(q[tail][3]<visit[x][y][q[tail][2]])
				{
					q[tail][0]=x;
					q[tail][1]=y;
					//cout<<x<<' '<<y<<' '<<q[tail][3]<<' '<<tail<<endl;
					visit[x][y][q[tail][2]]=q[tail][3];
				}
				else --tail;
			}
		}
		++head;
	}
	/*for(register int i=1;i<=n;++i)
		for(register int j=1;j<=n;++j)
			cout<<visit[i][j][0]<<' '<<visit[i][j][1]<<' '<<visit[i][j][2]<<endl;*/
	cout<<min(visit[n][n][0],min(visit[n][n][1],visit[n][n][2]))<<endl;
    return 0;
}
```

---

## 作者：szh_AK_all (赞：7)

## 分析
看到这题，很容易想到 dp。

在不考虑牛每走三步便要吃一次草的情况下，对于每个点 $(i,j)$，可以由 $(i-1,j),(i,j-1)$ 转移过来（由 $(i+1,j),(i,j+1)$ 转移过来是没有意义的）。设 $f_{i,j}$ 表示到达 $(i,j)$ 所需的最短时间，则转移为 $f_{i,j}=\min (f_{i-1,j},f_{i,j-1})+T$。

接着考虑牛每走三步便要吃一次草的条件。

由于有步数限制，所以在 $f$ 数组中增加一维，设 $f_{i,j,k}$ 表示当前在 $(i,j)$，且走的步数对 $3$ 取模的值为 $k$，所需的最短时间。

很显然的一个转移是由 $(i,j)$ 走向相邻的点，且步数 $k$ 加一。也即 $f_{i,j,k}$ 可以转移到 $f_{i-1,j,(k+1)\bmod 3},f_{i+1,j,(k+1)\bmod 3},f_{i,j-1,(k+1)\bmod 3},f_{i,j+1,(k+1)\bmod 3}$（注意到此时相邻的四个点都应当被转移到，原因可从下文中理解）。

但是单纯的这样转移是错误的，因为这些步数对 $3$ 取模的值是我们被动转移的。假设转移到终点 $(n,n)$ 时，当前的步数刚好是 $3$ 的步数，且在 $(n,n)$ 吃草的时间相当长，还不如在其他地方多走几步，然后吃草再走到 $(n,n)$，那么此时的 dp 转移便是不完整的，错误的。

用上述反例思考另一个转移，我们可以用当前步数 $k$ 转移到 $k+1$，那么是否可以转移到 $k+2,k+3$ 呢？首先考虑 转移到 $k+3$，合理的策略是选择在其他位置来回走，消耗两步，再走到当前所需要转移的位置，此时需要分类讨论 $k$ 对 $3$ 取模的值，从而选出在吃草时所需花费的最短时间。以下伪代码以 $(i,j)$ 转移到 $(i+1,j)$ 为例：

```
int now = min(a[i - 1][j], a[i + 1][j]);
now = min(now, min(a[i][j + 1], a[i][j - 1]));
int tmp = 0;
if (k + 1 == 3)
    tmp = now;
else if (k + 2 == 3)
    tmp = a[i][j];
else if (k + 3 == 3)
    tmp = a[i + 1][j];
f[i + 1][j][k] = min(f[i + 1][j][k], f[i][j][k] + 3 * T + tmp);
```

在考虑是否可以转移到 $k+2$，由于从 $(i,j)$ 走到需要转移的位置得花费一步，而剩下的一步是无法使用的，所以 $k+2$ 无法转移到。且其他更多的情况可以由其他的 dp 状态转移到。

最后，考虑到这个转移是有后效性的，也就是说对于一个位置，在被之前的某个状态转移过来时，它对于其它的位置而言，此时可能是最优的。那么可以进行多次转移，对于最优秀的位置，它被“扩散”到、成为优秀的位置时，最多要进行 $n$ 次整体转移；再由它向四周“扩散”最优情况时，最多要“扩散” $n$ 次，所以整体转移是不超过 $2n$ 次的。

当然，一个在考场上骗分的做法是直接转移 $1000$ 次，很具有~~教育~~诱导意义。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[105][105];
int f[105][105][5];

signed main() {
	int n, T;
	cin >> n >> T;
	for (int i = 0; i <= 103; i++)
		for (int j = 0; j <= 103; j++)
			a[i][j] = f[i][j][0] = f[i][j][1] = f[i][j][2] = 100000000000000000;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> a[i][j];
	f[1][1][0] = 0;
	for (int ii = 1; ii <= 2 * n; ii++)
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = 0; k < 3; k++) {
					f[i + 1][j][(k + 1) % 3] = min(f[i + 1][j][(k + 1) % 3], f[i][j][k] + T + (k + 1 == 3) * a[i + 1][j]);
					f[i][j + 1][(k + 1) % 3] = min(f[i][j + 1][(k + 1) % 3], f[i][j][k] + T + (k + 1 == 3) * a[i][j + 1]);
					f[i - 1][j][(k + 1) % 3] = min(f[i - 1][j][(k + 1) % 3], f[i][j][k] + T + (k + 1 == 3) * a[i - 1][j]);
					f[i][j - 1][(k + 1) % 3] = min(f[i][j - 1][(k + 1) % 3], f[i][j][k] + T + (k + 1 == 3) * a[i][j - 1]);
					int now = min(a[i - 1][j], a[i + 1][j]);
					now = min(now, min(a[i][j + 1], a[i][j - 1]));
					int tmp = 0;
					if (k + 1 == 3)
						tmp = now;
					else if (k + 2 == 3)
						tmp = a[i][j];
					else if (k + 3 == 3)
						tmp = a[i + 1][j];
					f[i + 1][j][k] = min(f[i + 1][j][k], f[i][j][k] + 3 * T + tmp);
					tmp = 0;
					if (k + 1 == 3)
						tmp = now;
					else if (k + 2 == 3)
						tmp = a[i][j];
					else if (k + 3 == 3)
						tmp = a[i][j + 1];
					f[i][j + 1][k] = min(f[i][j + 1][k], f[i][j][k] + 3 * T + tmp);
					tmp = 0;
					if (k + 1 == 3)
						tmp = now;
					else if (k + 2 == 3)
						tmp = a[i][j];
					else if (k + 3 == 3)
						tmp = a[i][j - 1];
					f[i][j - 1][k] = min(f[i][j - 1][k], f[i][j][k] + 3 * T + tmp);
					tmp = 0;
					if (k + 1 == 3)
						tmp = now;
					else if (k + 2 == 3)
						tmp = a[i][j];
					else if (k + 3 == 3)
						tmp = a[i - 1][j];
					f[i - 1][j][k] = min(f[i - 1][j][k], f[i][j][k] + 3 * T + tmp);
				}
			}
		}
	cout << min(f[n][n][0], min(f[n][n][1], f[n][n][2]));
}
```

---

## 作者：communist (赞：4)

### 一开始想写$DP$，发现直接转移完全有后效性

### 所以本小蒟蒻写了个最短路

每走三步就要吃草是这个题最难搞的地方，我们建图时不妨只对于距离等于三的点连边

考虑完全覆盖所有情况，从一个点走一步，两步，然后三步，和直接走三步代价是等价的

这样从每个点到与其曼哈顿距离为三的所有点连边即可

考虑到终点的答案，对于所有小于三步到终点的位置到终点的代价，找到最小值即为答案

有个坑就是比如右左右这种走法，我们也需要从一个点向其周围的点连边

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define int long long
using namespace std;
const int maxn=20010;
struct edge{
    int next,to,dis;
}e[12*maxn];
int n,t,g[110][110],len[maxn],head[maxn],cnt,ans=1e9;
int dx[]={-1,-2,-3,-1,-2,0,1,2,1,2,3,0,0,1,0,-1};
int dy[]={-2,-1,0,2,1,-3,-2,-1,2,1,0,3,1,0,-1,0};
bool exist[maxn];
inline void add(int x,int y,int d)
{
    e[++cnt].next=head[x];
    e[cnt].to=y;
    e[cnt].dis=d;
    head[x]=cnt;
}
inline int make(int x,int y)
{
    return x*n+y;
}
int dijkstra()
{
    priority_queue<pair<int,int> >q;
    memset(len,0x3f,sizeof(len));
    q.push(make_pair(0,make(1,1)));
    len[make(1,1)]=0;
    while(!q.empty())
    {
        int u=q.top().second;
        q.pop();
        if(exist[u])
            continue;
        exist[u]=1;
        for(int v,i=head[u];i;i=e[i].next)
            if(len[v=e[i].to]>len[u]+e[i].dis)
            {
                len[v]=len[u]+e[i].dis;
                q.push(make_pair(-len[v],v));
            }
    }
}
void check(int x,int y)
{
	for(int i=0;i<16;i++)
		if(x+dx[i]>0&&x+dx[i]<=n&&y+dy[i]>0&&y+dy[i]<=n)
			add(make(x,y),make(x+dx[i],y+dy[i]),3*t+g[x+dx[i]][y+dy[i]]);
}
signed main()
{
	scanf("%lld%lld",&n,&t);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lld",&g[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			check(i,j);
	dijkstra();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(2*n-i-j<3)
				ans=min(ans,len[make(i,j)]+(2*n-i-j)*t);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：xfrvq (赞：2)

[原题链接](https://www.luogu.com.cn/problem/P3659)

[博客食用](https://www.luogu.com.cn/blog/368107/solution-p3659-2)

# 广搜模板？

一道广搜题

这里队列所用的 $node$ 需要包含以下四种东西：

横坐标 $x$ ，纵坐标 $y$ ，步数 $step$ ，时间 $cnt$

用 步数 $\%$ $3$，代表当前的饥饿程度

同时开一个 $visit$ 数组， $vis_{i,j,k}$ 表示坐标为 $(i ,j )$ 且饥饿程度为 $k$ 的情况有没有出现过

~~然后直接糊~~

```cpp
#include<stdio.h>
#include<queue>
#define Min(a,b) ((a) < (b) ? (a) : (b))
int dx[] = {0,1,0,-1},dy[] = {1,0,-1,0};
bool vis[101][101][3];
int mp[101][101],ans = 0x7f7f7f7f;
struct point{int x,y,step,cnt;};
std::queue<point> q;
int main(){
	int n,t;
	scanf("%d%d",&n,&t);
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j) scanf("%d",mp[i] + j); // 输入
	q.push({1,1,0,0});
	while(!q.empty()){
		point u = q.front();
		q.pop();
		int x = u.x,y = u.y,step = u.step,cnt = u.cnt;
		if(x == n && y == n){ //如果到终点就更新ans
			ans = Min(ans,cnt);
			continue;
		}
		for(int i = 0;i < 4;++i){ //上下左右4种状态
			int nx = x + dx[i],ny = y + dy[i],st = step + 1,ncnt = cnt + t;
			if(nx < 1 || nx > n || ny < 1 || ny > n) continue;// 出界则跳过当前状态
			if(vis[nx][ny][st % 3]) continue;// 被走过则跳过当前状态
			vis[nx][ny][st % 3] = true;
			if(st % 3 == 0) ncnt += mp[nx][ny]; // 如果现在走了3的倍数步就加上当前这块田地的值
			q.push({nx,ny,st,ncnt});
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

~~过样例，交，9分！！1~~

原因：两次以同一种状态到达同一个点，可能第一次的时间大于第二次的时间（毕竟队列并不能每次取出时间小的元素）

所以可以用优先队列求解，优先队列按 $cnt$ 大小优先

但注意，默认优先队列是大根堆，实现是小于号比较，每次取出大的元素，而这里是小根堆，要用大于号比较。

AC代码：

```cpp
#include<stdio.h>
#include<queue>
#define Min(a,b) ((a) < (b) ? (a) : (b))
int dx[] = {0,1,0,-1},dy[] = {1,0,-1,0};
bool vis[101][101][3];
int mp[101][101],ans = 0x7f7f7f7f;
struct point{
    int x,y,step,cnt;
    bool operator<(const point& p) const{
        return cnt > p.cnt; //注意是大于号
    }
};
std::priority_queue<point> q;// 优先队列
int main(){
	int n,t;
	scanf("%d%d",&n,&t);
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j) scanf("%d",mp[i] + j);
	q.push({1,1,0,0});
	while(!q.empty()){
		point u = q.top();
		q.pop();
		int x = u.x,y = u.y,step = u.step,cnt = u.cnt;
		if(x == n && y == n){
			ans = Min(ans,cnt);
			continue;
		}
		for(int i = 0;i < 4;++i){
			int nx = x + dx[i],ny = y + dy[i],st = step + 1,ncnt = cnt + t;
			if(nx < 1 || nx > n || ny < 1 || ny > n) continue;
			if(vis[nx][ny][st % 3]) continue;
			vis[nx][ny][st % 3] = true;
			if(st % 3 == 0) ncnt += mp[nx][ny];
			q.push({nx,ny,st,ncnt});
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

但这样复杂度就是 $O(nm\log (nm))$ ，有没有更快的方法呢？

## 另一种思路

把 bool 类型的 $visit$ 改成 int 类型的 $dis$ ，$dis_{i,j,k}$ 表示坐标为 $(i ,j )$ 且饥饿程度为 $k$ 的情况的最小时间

这样就不会担心以同一种状态到达同一个点且时间不一样会出问题了

相比起优先队列的 $O(nm\log (nm))$ 复杂度，这种方法就是以空间换时间

```cpp
#include<stdio.h>
#include<string.h>
#include<queue>
#define Min(a,b) ((a) < (b) ? (a) : (b))
#define int long long
int dx[] = {0,1,0,-1},dy[] = {1,0,-1,0};
int dis[101][101][3];
int mp[101][101],ans = 0x7f7f7f7f,anstep;
struct point{int x,y,step,cnt;};
std::queue<point> q;
signed main(){
	memset(dis,0x3f,sizeof dis);
	int n,t;
	scanf("%lld%lld",&n,&t);
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j) scanf("%lld",mp[i] + j);
	q.push({1,1,0,0});
	while(!q.empty()){
		point u = q.front();
		q.pop();
		int x = u.x,y = u.y,step = u.step,cnt = u.cnt;
		if(x == n && y == n) continue;
		for(int i = 0;i < 4;++i){
			int nx = x + dx[i],ny = y + dy[i],st = step + 1,ncnt = cnt + t;
			if(nx < 1 || nx > n || ny < 1 || ny > n) continue;
			if(dis[nx][ny][st % 3] <= ncnt) continue;
			if(st % 3 == 0) ncnt += mp[nx][ny];
			dis[nx][ny][st % 3] = ncnt;
			q.push({nx,ny,st,ncnt});
		}
	}
	printf("%lld\n",Min(dis[n][n][0],Min(dis[n][n][1],dis[n][n][2])));
	return 0;
```

~~90分，离正确答案又近了一步~~

懂 SPFA 的各位知道，SPFA ~~它虽然慢，但是~~有一种优化：把原来的队列改成双端队列，在 push 的时候，拿当前的距离与双端队列队首元素的距离比较，小于则 push_front，大于则 push_back ，这样和 dijkstra 的比较距离的优先队列有异曲同工之妙，做到让一个距离短的节点先被松弛，以达到优化的目的。

同样是广搜，借鉴一下 SPFA 的思想，即可过掉那个数据点。

AC代码2：

```cpp
#include<stdio.h>
#include<string.h>
#include<deque>
#define Min(a,b) ((a) < (b) ? (a) : (b))
#define int long long
int dx[] = {0,1,0,-1},dy[] = {1,0,-1,0};
int dis[101][101][3];
int mp[101][101],ans = 0x7f7f7f7f,anstep;
struct point{int x,y,step,cnt;};
std::deque<point> q;
signed main(){
	memset(dis,0x3f,sizeof dis);
	int n,t;
	scanf("%lld%lld",&n,&t);
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j) scanf("%lld",mp[i] + j);
	q.push_back({1,1,0,0});
	while(!q.empty()){
		point u = q.front();
		q.pop_front();
		int x = u.x,y = u.y,step = u.step,cnt = u.cnt;
		if(x == n && y == n) continue;
		for(int i = 0;i < 4;++i){
			int nx = x + dx[i],ny = y + dy[i],st = step + 1,ncnt = cnt + t;
			if(nx < 1 || nx > n || ny < 1 || ny > n) continue;
			if(dis[nx][ny][st % 3] <= ncnt) continue;
			if(st % 3 == 0) ncnt += mp[nx][ny];
			dis[nx][ny][st % 3] = ncnt;
			if(ncnt > q.front().cnt) q.push_back({nx,ny,st,ncnt});
			else q.push_front({nx,ny,st,ncnt});
		}
	}
	printf("%lld\n",Min(dis[n][n][0],Min(dis[n][n][1],dis[n][n][2])));
	return 0;
}
```

---

## 作者：elijahqi (赞：2)

把每个点拆成三个点，分别表示走了%3余0步到i，记作3\*i+0,走了%3余1步到i，记作3 \*i+1，走了%3余2步到i，记作3 \*i+2。每个点i可以向上下左右走一步到达j点，所以对于i，j我们建三条有向边，从 3\*i走到3\*j+1，边权为t，从3\*i+1走到3\*j+2，边权为t，从3\*i+2走到3\*j，边权为t+a[j] (第三步有附加值)。然后以3为源点跑一遍spfa即可。最后答案就是3\*n\*n,3\*n\*n+1,3\*n\*n+2中最小的一个。

另外提醒一下这道题关于点的数组一定要开的足够大（敲黑板） 3\*n\*n

欢迎光临蒟蒻的blog qwq

(http://www.elijahqi.win/2017/09/07/bzoj4992-usaco17febwhy-did-the-cow-cross-the-road-i-g/)


```cpp
#include<cstdio>
#include<queue>
#define N 110
#define inf 0x7f7f7f7f
using namespace std;
inline int read(){
    int x=0;char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch<='9'&&ch>='0') {x=x*10+ch-'0';ch=getchar();}
    return x;
}
struct node{
    int x,y,z,next;
}data[12*N*N];
int num=0,h[3*N*N],n,t,nn,map[N][N];
inline void insert1(int x,int y,int z){
    data[++num].x=x;data[num].y=y;data[num].z=z;data[num].next=h[x];h[x]=num;
}
int f[3*N*N];bool flag[3*N*N];
queue<int> q;
void spfa(){
    for (int i=1;i<=3*nn;++i) f[i]=inf;
    flag[1]=true;f[1]=0;q.push(1);
    while (!q.empty()){
        int x=q.front();q.pop();
        for (int i=h[x];i;i=data[i].next){
            int y=data[i].y,z=data[i].z;
            if (f[x]+z<f[y]){
                f[y]=f[x]+z;
                if (flag[y]==false){
                    flag[y]=true;q.push(y);
                }
            }
        }
        flag[x]=false;
    }
}
inline int min(int x,int y){
    return x<y?x:y;
}
int main(){
    freopen("3659.in","r",stdin);
    n=read();t=read();nn=n*n;
    for (int i=1;i<=n;++i) for (int j=1;j<=n;++j) map[i][j]=read();
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j){
            int x[3],y[3];
            if (i-1>0){
                x[0]=(i-1)*n+j,y[0]=(i-2)*n+j;x[1]=x[0]+nn;y[1]=y[0]+nn;x[2]=x[1]+nn;y[2]=y[1]+nn;
                for (int z=0;z<=2;++z) insert1(x[z],y[(z+1)%3],z+1==3?t+map[i-1][j]:t);
            }
            if (i+1<=n){
                x[0]=(i-1)*n+j,y[0]=(i)*n+j;x[1]=x[0]+nn;y[1]=y[0]+nn;x[2]=x[1]+nn;y[2]=y[1]+nn;
                for (int z=0;z<=2;++z) insert1(x[z],y[(z+1)%3],z+1==3?t+map[i+1][j]:t);
            }
            if (j-1>0){
                x[0]=(i-1)*n+j,y[0]=(i-1)*n+j-1;x[1]=x[0]+nn;y[1]=y[0]+nn;x[2]=x[1]+nn;y[2]=y[1]+nn;
                for (int z=0;z<=2;++z) insert1(x[z],y[(z+1)%3],z+1==3?t+map[i][j-1]:t);
            }
            if (j+1<=n){
                x[0]=(i-1)*n+j,y[0]=(i-1)*n+j+1;x[1]=x[0]+nn;y[1]=y[0]+nn;x[2]=x[1]+nn;y[2]=y[1]+nn;
                for (int z=0;z<=2;++z) insert1(x[z],y[(z+1)%3],z+1==3?t+map[i][j+1]:t);
            }
        }
//    for (int i=1;i<=num;++i) printf("%d %d %d\n",data[i].x,data[i].y,data[i].z);
    spfa();
    printf("%d",min(f[nn],min(f[nn<<1],f[nn*3])));
    return 0;
}
(elijahqi.win)

```

---

## 作者：yxy666 (赞：1)

为什么我一看到这道题就想到了 CSP2020 入门级的第四题，但是这道题是四个方向。

定义 $f_{i,j,k}$ 表示从 1,1 到 i,j 走了 k 步的最优解,$check(k,x)$ 用来判断当前走的第 k 步时是否需要吃草。那么就是从上面走来和从左边走来。

但是从下面和从右边来应该如何判断呢？
我们可以另开一个 $F_{i,j,k}$ 表示从 n,n 走到了 i,j 用了 k 步的最优解。然后两个数组倒腾来倒腾去就好了。用不来公式，详见代码。
```

我也不知道为什么可以这么干但是跟笨蛋 dfs 对拍就是拍不停

滚动数组可开可不开，反正不会爆空间

code :

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=102;
int n,a[maxn][maxn],T;
long long ans=((long long)1<<60),f[maxn][maxn][705],F[maxn][maxn][705];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}//快读
int check(int x,int y){
	if(x%3==0)return y;
	return 0;
}
int main(){
	n=read();T=read();
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)a[i][j]=read();
	memset(F,127,sizeof F);
	memset(f,127,sizeof f);//刷最小值，所有需要初始化
	f[1][1][0]=0;
	for(int k=1;k<=700;k++)//枚举步数
	for(int i=1;i<=n;i++)/枚举行
	for(int j=1;j<=n;j++)if(i+j-2<=k&&(i!=1||j!=1))/枚举列，如果最短步数都无法到达，就不管了
	{
		f[i][j][k]=f[i-1][j][k-1]+T+check(k,a[i][j]);
		f[i][j][k]=min(f[i][j-1][k-1]+T+check(k,a[i][j]),f[i][j][k]);//从上面来和从左边来
		f[i][j][k]=min(F[i+1][j][k-1]+T+check(k,a[i][j]),f[i][j][k]);
		f[i][j][k]=min(F[i][j+1][k-1]+T+check(k,a[i][j]),f[i][j][k]);//从下面来和从右边来
		F[i][j][k]=min(F[i][j][k],f[i][j][k]);
	}
	for(int k=2*(n-1);k<=700;k++)ans=min(ans,f[n][n][k]);//刷答案
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：曹老师 (赞：1)

**知识点：BFS DP**

to数组存一下四个方位~~很简单~~

然后对于每一个点都遍历四个方位

三维数组 前两维为坐标 最后一维为访问的次数（第几次访问的

（以下：x，y为当前坐标 fx，fy为上一节点坐标

**于是很容易就能得到每一个的方程：**

```
f[x][y][i]=min(f[x][y][i],f[fx][fy][i-1]+t)
```

**至于是不是要加上吃草的时间 方程：**

```
f[x][y][i]=min(f[x][y][i],f[fx][fy][2]+t+w[x][y])
```

每一个点都不止跑一次

于是问题就简化成了：

无vis数组的bfs + 三维DP ~~还是挺好打的~~
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#define MAXN 100005
#define LL long long
#define INF 2147483647
#define MOD 1000000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
#define debug(x) cout<<x<<endl;
using namespace std;
const int L=105;
struct node{
	int x,y;
};
queue<node>que;
LL int n,t,w[L][L],f[L][L][4],to[4][2]={1,0,-1,0,0,1,0,-1};
LL int bfs()
{
	memset(f,0x3f,sizeof(f));
	f[1][1][0]=0;
	que.push({1,1});
	while(!que.empty())
	{
		node now=que.front();
		que.pop();
		for(int i=0;i<4;i++)
		{
			int a=now.x+to[i][0],b=now.y+to[i][1];
			bool flag=false;
			if(a<=n&&a>=1&&b<=n&&b>=1)
			{
                if(f[now.x][now.y][0]+t<f[a][b][1])
				{
                    f[a][b][1]=f[now.x][now.y][0]+t;
                    flag=true;
                }
                if(f[now.x][now.y][1]+t<f[a][b][2])
				{
                    f[a][b][2]=f[now.x][now.y][1]+t;
                    flag=true;
                }
                if(f[now.x][now.y][2]+t+w[a][b]<f[a][b][0])
				{
                    f[a][b][0]=f[now.x][now.y][2]+t+w[a][b];
                    flag=true;
                }
            	if(flag)
					que.push({a,b});
			}
		}
	}
	return min(min(min(f[n][n][3],f[n][n][0]),f[n][n][1]),f[n][n][2]);
}
int main()
{
	scanf("%lld%lld",&n,&t);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lld",&w[i][j]);
	printf("%lld",bfs());
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

这道题本质上就是一道最短路。

首先，设在点 $(i,j)$ 吃草花费的时间为 $a[i][j]$。

然后，找出所有的 $(x,y)$ 与 $(nx,ny)$，满足 $|x-nx|+|y-ny|=1\text{或}3$，从 $(x,y)$ 向 $(nx,ny)$ 连一条边，权值为 $a[nx][ny]+t\times3$。

之所以让两个点的曼哈顿距离为 $3$，是因为每走过了 $3$ 步就要吃草；而两个相邻的点还能走，是因为这是可以故意凑到 $3$ 步而往回走的，可能能更省时间哦。

然后从 $(1,1)$ 开始跑一遍已经 `NOIP（复活）` 的 `SPFA`。

最后，从以下 $6$ 个点：

$$(n,n),(n-1,n),(n,n-1),(n-1,n-1),(n-2,n),(n,n-2)$$

中选择一个，使得从起点到达这个点的距离与这个点到终点的距离最小。

另外，这个点到终点的距离等于两者间曼哈顿距离乘以 $t$。

输出答案即可。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define max_n 100
#define inf 0x3f3f3f3f
int n;
int t;
int a[max_n+2][max_n+2];
struct E{
	int u,v,w,nx;
}e[max_n*max_n*20];
int ei=0;
int fir[max_n*max_n+20];
const int dx[16]={-1,-2,-3,-2,-1,0,1,2,3,2,1,0,-1,0,1,0};
const int dy[16]={-2,-1,0,1,2,3,2,1,0,-1,-2,-3,0,1,0,-1};
int dis[max_n*max_n+2];
bool vis[max_n*max_n+2];
queue<int>q;
inline int askid(int x,int y){
	return (x-1)*n+y;
}
inline void addedge(int u,int v,int w){
	e[++ei]=(E){u,v,w,fir[u]}; fir[u]=ei;
}
inline int mi(int a,int b){
	return a<b?a:b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("P3659_1.in","r",stdin);
	freopen("P3659_1.out","w",stdout);
	#endif
	scanf("%d%d",&n,&t);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			scanf("%d",a[i]+j);
		}
	}
	memset(fir,0,sizeof(fir));
	for(int x=1;x<=n;++x){
		for(int y=1;y<=n;++y){
			for(int d=0,nx,ny;d<16;++d){
				nx=x+dx[d];
				ny=y+dy[d];
				if(nx<1||nx>n||ny<1||ny>n)continue;
				addedge(askid(x,y),askid(nx,ny),a[nx][ny]+t*3);
			}
		}
	}
	memset(dis,inf,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[1]=0;
	vis[1]=true;
	q.push(1);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=fir[u],v;i;i=e[i].nx){
			v=e[i].v;
			if(dis[u]+e[i].w<dis[v]){
				dis[v]=dis[u]+e[i].w;
				if(!vis[v]){
					vis[v]=true;
					q.push(v);
				}
			}
		}
	}
	printf("%d\n",mi(dis[askid(n,n)],mi(dis[askid(n-1,n)]+t,mi(dis[askid(n,n-1)]+t,mi(dis[askid(n-1,n-1)]+t*2,mi(dis[askid(n-2,n)]+t*2,dis[askid(n,n-2)]+t*2))))));
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/59059134)

By **dengziyue**

---

## 作者：asdfczf (赞：0)

## bfs暴搜题解queue版本

因为没有看懂那个 @Okarin 大佬的 if（tail > 1000005）是什么意思，所以来提供一个STL版本

一般写这种题个人还是挺喜欢结构体 + queue的

[具体思路在这里！](https://www.luogu.org/blog/Okarin/solution-p3659)

放代码qwq

```cpp
#include <bits/stdc++.h>
using namespace std;

struct node {
	int x, y, step, c;
} st;
int n, t, Ans;
int mapp[1003][1003], vis[1003][1003][4];
int fx[4] = {0, 0, -1, 1};
int fy[4] = {-1, 1, 0, 0};

inline void bfs() {
	queue<node> q;
	memset(vis, 0x3f, sizeof(vis));
	st.x = 1, st.y = 1, st.step = 0, st.c = 0;
	vis[1][1][0] = 0;
	q.push(st);
	while(q.size()) {
		node u = q.front();
		q.pop();
		for(register int i = 0; i < 4; i++) {
			int xi = u.x + fx[i], yi = u.y + fy[i];
			if (xi >= 1 && xi <= n && yi >= 1 && yi <= n) {
				node d;
				d.step = (u.step + 1) % 3;
				if (d.step == 0) d.c = u.c + t + mapp[xi][yi];
				else d.c = u.c + t;
				if (d.c < vis[xi][yi][d.step]) {
					d.x = xi, d.y = yi;
					vis[xi][yi][d.step] = d.c;
					q.push(d);
				}
			}
		}
	}
}

int main() {
	cin >> n >> t;
	for(register int i = 1; i <= n; i++) {
		for(register int j = 1; j <= n; j++) {
			cin >> mapp[i][j];
		} 
	}
	bfs();
	Ans = min(vis[n][n][0], min(vis[n][n][1], vis[n][n][2]));
	cout << Ans;
	return 0;
} 
```

# csps rp++


---

## 作者：S__Z (赞：0)

题目解释：牛可以往回走，牛也可以直接走。


例：    1 ——2——3——4


牛可以1->2->1->2;也可以1->2->3->4


 ![](https://cdn.luogu.com.cn/upload/pic/9857.png) 

这样就可以类比于牛走一步和走三步（但是走一步时的时间也是加上走3步的时间）


将所有的方向枚举出来。。。然后。。宽搜？


所以这道题不用想楼下和其他大佬一样进行拆点，只要多想想所有情况，就可以了。


安利博客： <http://www.cnblogs.com/Slager-Z/>


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>
using namespace std;
int n,v[110][110];
long long dis[110][110],t;
bool vis[110][110];
struct node
{
    int x,y;
};
int dx[]={0,0,3,-3,1,1,2,2,-1,-1,-2,-2,0,0,1,-1};
int dy[]={3,-3,0,0,2,-2,1,-1,2,-2,1,-1,1,-1,0,0};
void spfa(int x,int y)
{
    queue<node>q;
    q.push((node){x,y});
    memset(dis,0x7f,sizeof(dis));
    dis[x][y]=0; vis[x][y]=1;
    do
    {
    node u=q.front();q.pop();
        vis[u.x][u.y]=0;
        for(int i=0;i<16;i++)
        {    int tx=u.x+dx[i],ty=u.y+dy[i];
            if(tx>=1&&tx<=n&&ty>=1&&ty<=n)
            {
             if(dis[tx][ty]>dis[u.x][u.y]+v[tx][ty]+t*3)
            {    
                dis[tx][ty]=dis[u.x][u.y]+v[tx][ty]+t*3;
                if(!vis[tx][ty])
                {
                    vis[tx][ty]=1;q.push((node){tx,ty});
                    }
                }
            }
        }
    }while(q.size()!=0);
}
int main()
{    ios::sync_with_stdio(false);
    cin>>n>>t;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>v[i][j];
    spfa(1,1);
    long long ans;
    ans=dis[n][n];//参照题解：牛不可能直接到达，所以得枚举终点3步之内的所有点的值+位移的时间； 
    ans=min(ans,dis[n][n-1]+t);
    ans=min(ans,dis[n-1][n]+t);
    ans=min(ans,dis[n][n-2]+t*2);
    ans=min(ans,dis[n-2][n]+t*2);
    ans=min(ans,dis[n-1][n-1]+t*2);
    printf("%lld",ans);
    return 0;
}

```

---

