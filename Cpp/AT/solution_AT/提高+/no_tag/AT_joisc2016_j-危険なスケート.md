# 危険なスケート

## 题目描述

JOI 君的爱好是在大自然的广阔滑冰场上滑冰。

滑冰场呈长方形，由南北方向的 $R$ 个格子和东西方向的 $C$ 个格子组成。我们将北边第 $r$ 行、西边第 $c$ 列的格子称为格子 $( r , c )$ 。每个格子要么是 JOI 君可以通过的格子，要么是有冰块而无法通过的格子。此外，滑冰场的外周的格子上都有冰块，JOI君不会滑出场外。也就是说，格子 $( i , 1 )$、$( i , C ) (1 ≦ i ≦ R)$ 以及格子 $( 1 , j )$、$( R , j ) (1 ≦ j ≦ C)$ 上都有冰块。

JOI 君的滑冰技术并不好。JOI 君在滑冰场上移动时，会朝东、西、南、北其中一个方向滑出当前所在的格子，并在撞到冰块的前一个格子停下。滑出去并停下的过程算作一次移动。如果相邻的格子上有冰块，则无法朝该方向移动。

有一天，JOI 君在享受滑冰时，突然发现当他滑出格子时，那个格子上会长出冰块。除了滑出格子的地方，经过的格子上不会长出冰块。在这种情况下继续滑冰非常危险，因此 JOI 君想尽快逃离这个滑冰场。

JOI 君当前的位置是格子 $( r1 , c1 )$。要从这个滑冰场逃脱，必须在出口的格子 $( r2 , c2 )$ 停下。为了让 JOI 君安全地从滑冰场逃脱，请编写一个程序，计算从当前位置开始移动到出口的格子至少需要多少次移动。可能会出现无论如何移动都无法停在出口的格子的情况。请注意，仅仅经过而不是停在出口的格子并不能算作逃离滑冰场。

给定滑冰场上冰块的信息、JOI 君的当前位置和出口的格子的位置，请判断 JOI 君是否能够从当前位置开始移动并在出口的格子停下，如果可以，则求出所需的最小移动次数。

## 说明/提示

#### 子任务 $1$（$13$ 分）

$R \leq 10$，$C \leq 10$。

如果 JOI 君能够从当前位置开始移动并在出口的格子停下，则所需的移动次数在 $10$ 次以内。

#### 子任务 $2$（$65$ 分）

$R \leq 200$，$C \leq 200$。

#### 子任务 $3$（$22$ 分）

没有额外的限制。

翻自[此处](https://www2.ioi-jp.org/camp/2016/2016-sp-tasks/2016-sp-d4.pdf)。

# 题解

## 作者：ollo (赞：3)

# 题目大意

给出一个四周都是冰块的冰场，JOI 君在滑冰，每次滑冰只能在这个方向上最近的冰块旁停止，同时在它的起点位置产生一块冰块，问从起点到终点的最小代价。

# 大致思路

看到题之后显然就会发现，如果你要去一个身边的格子，左右横跳一定是最优解，且只需要两步。但是此时有了一个问题，每次滑冰产生的障碍是否会重复使用？

答案是不会，考虑到一个冰块只会对周围四个格子产生影响，若你回到了一次滑冰的旁边，则至少需要三次（如图）：

```cpp
u 起点 v 终点
######
#...##
#.uv.#
######
```

这张图对于上面的情况来说是最好的情况，但它依旧需要向上，向右，向下三次，但按照左右横跳法只要往右并往左再跳一次即可。所以直接往后来回到的方向跳是更好的，一次滑冰产生的障碍不会重复使用。

此时有了一个模型，往上下左右连边，边权为 $2$。但是如果一个点旁边本来就有一个冰块，从同方向其他地方往这跳只要 $1$ 次操作，特判一下即可。建完图后跑最短路。

# code
```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define int long long


using namespace std;

const int N = 1e3 + 10;
const int fx[] = {0, 0, 1, -1};
const int fy[] = {1, -1, 0, 0};

char c[N + 10][N + 10];
int id[N + 10][N + 10];
int n, m;
struct S{int v, w;};
vector<S> g[N * N + 10];

bool check(int x, int y){return x >= 1 && x <= n && y >= 1 && y <= m && c[x][y] != '#';}
int qx, qy, zx, zy;

int dis[N * N + 10];bool vis[N * N + 10];
priority_queue<pii, vector<pii>, greater<pii> > p;
int s, t;

void Dijkstra(int x){
    memset(dis, 0x3f3f3f3f, sizeof(dis));
    dis[x] = 0;p.push({dis[x], x});
    while(!p.empty()){ 
        auto u = p.top();
        p.pop();
        if(vis[u.second]) continue;
        vis[u.second] = 1;
        for(int i = 0; i < g[u.second].size(); i++){
            int v = g[u.second][i].v, w = g[u.second][i].w;
            if(vis[v] || u.first + w >= dis[v]) continue;
            dis[v] = u.first + w;
            p.push({dis[v], v});
        }
    }
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i = 1, w = 1; i <= n; i++){
        for(int j = 1; j <= m; j++) cin >> c[i][j], id[i][j] = w++;
    }
    cin >> qx >> qy >> zx >> zy;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            for(int f = 0; f < 4; f++){
                int tx = i + fx[f], ty = j + fy[f];
                if(!check(tx, ty)) continue;
                g[id[i][j]].push_back({id[tx][ty], 2});
            }
            if(c[i][j] == '#'){
                for(int f = 0; f < 4; f++){
                    int tx = i + fx[f], ty = j + fy[f];
                    if(!check(tx, ty)) continue;
                    for(int x = tx + fx[f], y = ty + fy[f]; check(x, y); x += fx[f], y += fy[f])g[id[x][y]].push_back({id[tx][ty], 1});
                }
            }
        }
    }
    s = id[qx][qy];t = id[zx][zy];
    Dijkstra(id[qx][qy]);
    if(!vis[t]) dis[t] = -1;
    cout << dis[t] << endl;
    return 0;
}
```

---

## 作者：lsz0205 (赞：2)

# AT_joisc2016_j 危険なスケート 题解

## **观题有感：**
1. 每一次移动都会产生副产物冰块，搜索不太好写，故考虑最短路。
1. 如何移动？不难发现，停下无非两种情况：路径上有冰块或者碰到边界。那么我们要想走到相邻的点，就需要利用好滑走时产生的冰块停下，移动方式如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/1w95ftxu.png)

3. 建图：由上可知，到达相邻点需要跑两次，我们记边权为 2，到达路径上原有冰块旁的点只需要一次，边权记为 1。

## 最优证明：
1. 要到达周围没有冰块的位置，我们需要反复利用产生的冰块和已有的冰块，因此需要一步一步挪。
1. 如果需要再次利用已产生的冰块，至少需要经反弹 3 次。
## 注意：
1. 为了方便建边，我们可以把点的下标由二维转化为一维，然后编号。
1. 存在建重边的情况，链式前向星数组尽可能开大。
## 代码

```cpp
#include<bits/stdc++.h>
#define PII pair<int,int>
#define fi first
#define se second 
using namespace std;
int n,m;
int s,t,sx,sy;
int dx[]={1,0,-1,0};//下 左 上 右
int dy[]={0,-1,0,1};
char a[1005][1005];
int p(int x,int y){//将坐标转化为点的编号 
	return (x-1)*m+y;
}

priority_queue<PII,vector<PII>,greater<PII> > hp;
int h[4000010];
int to[8000010];
int nt[8000010];
int w[8000010];
int idx;

void add(int x,int y,int z) {
	to[idx]=y;
	nt[idx]=h[x];
	w[idx]=z;
	h[x]=idx++;
}

int dis[1000010];
bool v[1000010];
void dijkstra(int u) {
	dis[u]=0;
	hp.push((PII) {
		0,u
	});
	while(!hp.empty()) {
		PII X=hp.top();
		hp.pop();
		int t=X.se;
		if(!v[t]) {
			v[t]=true;
			for(int i=h[t]; i!=-1; i=nt[i]) {
				int j=to[i];
				if(dis[t]+w[i]<dis[j]) {
					dis[j]=dis[t]+w[i];
					hp.push((PII){dis[j],j
					});
				}
			}
		}
	}
	return ;
}

signed main() {
	
	memset(h,-1,sizeof(h));//初始化链式前向星，不然爆炸 
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",a[i]+1);//下标从1开始处理原图，便于操作理解 
	}
	
	//建边
	
	for(int i=2;i<n;i++){
		for(int j=2;j<m;j++){
			if(a[i][j]=='#') continue;//无法到达此点，没必要建边
			for(int k=0;k<=3;k++){//与四周的点 
				int x=i+dx[k];
				int y=j+dy[k];
				if(1<x&&x<n&&1<y&&y<m){
					add(p(i,j),p(x,y),2);
				}
			} 
			//同一行、列
			int x=i,y=j;
			while((x--)>=1){
				if(a[x][j]=='#'){
					add(p(i,j),p(x+1,j),1);
					break;
				}
			} 
			x=i;
			while((x++)<=n){
				if(a[x][j]=='#'){
					add(p(i,j),p(x-1,j),1);
					break;
				}
			} 
			
			while((y--)>0){
				if(a[i][y]=='#'){
					add(p(i,j),p(i,y+1),1);
					break;
				}
			} 
			y=j;
			while((y++)<=m){
				if(a[i][y]=='#'){
					add(p(i,j),p(i,y-1),1);
					break;
				}
			} 
		}
	} 
	scanf("%d%d%d%d",&s,&t,&sx,&sy);
	
	if(s==sx&&t==sy){
		puts("0");
		return 0;
	}
	
	memset(dis,0x3f,sizeof(dis));//与起点距离记得初始化无穷大 
	dijkstra(p(s,t));
	if(dis[p(sx,sy)]==0x3f3f3f3f) puts("-1");
	else printf("%d\n",dis[p(sx,sy)]);
	return 0;
}
```

---

## 作者：iranai (赞：2)

# 关于题目
其实就是一个几乎模板的最短路题目，只需要额外思考如何建边。
# 思路
1. 当往一个方向滑冰时，只要遍历到一个格子是冰块，就回退一步，即从起点到该点的路径权值为 1。

1. 如何最快到达身边的一个点？不难发现，我们随意往一个方向滑冰，就会在起点产生一个冰块，此时重新往起点滑冰，就能停在最开始的起点的旁边一格，即相邻两个点的路径权值为 2。

1. 按以上方式建边，最后跑一遍最短路就好。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;
priority_queue<PII,vector<PII>,greater<PII> > hp;
int dx[4]={-1,0,+1,0};
int dy[4]={0,+1,0,-1};
int n,m;
char a[2010][2010];
int h[4200000+10];
int to[8400000+10];
int nt[8400000+10];
int w[8400000+10];
int idx;
void add(int x,int y,int z){
	to[idx]=y;
	w[idx]=z;
	nt[idx]=h[x];
	h[x]=idx;
	idx++;
}
int d[4200000+10];
bool v[4200000+10];
void dijkstra_hp(int u){
	memset(d,0x3f,sizeof(d));
	d[u]=0;
	hp.push((PII){0,u});
	while(hp.size()>0){
		PII top=hp.top();
		hp.pop();
		int t=top.second;
		if(!v[t]){
			v[t]=true;
			for(int i=h[t];i!=-1;i=nt[i]){
				int j=to[i];
				if(d[t]+w[i]<d[j]) d[j]=d[t]+w[i],hp.push((PII){d[j],j});
			}
		}
	}
}
int main(){
	memset(h,-1,sizeof(h));
	cin>>n>>m;
	for(int i=1;i<=n;i++){
			cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=m;j>=1;j--){
			a[i][j]=a[i][j-1];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=i,y=j;
			if(a[i][j]=='#') continue;
			for(int k=0;k<=3;k++){
				int xx=x+dx[k];
				int yy=y+dy[k];
				if(1<=xx&&xx<=n&&1<=yy&&yy<=m){
					add((i-1)*m+j,(xx-1)*m+yy,2);
				}
			}
			while(x--){
				if(x==0) break;
				if(a[x][y]=='#'){
					x+=1;
					add((i-1)*m+j,(x-1)*m+y,1);
					break;
				}
			}
			x=i;
			while(x++){
				if(x==n+1) break;
				if(a[x][y]=='#'){
					x-=1;
					add((i-1)*m+j,(x-1)*m+y,1);
					break;
				}
			}
			x=i;
			while(y--){
				if(y==0) break;
				if(a[x][y]=='#'){
					y+=1;
					add((i-1)*m+j,(x-1)*m+y,1);
					break;
				}
			}
			y=j;
			while(y++){
				if(y==m+1) break;
				if(a[x][y]=='#'){
					y-=1;
					add((i-1)*m+j,(x-1)*m+y,1);
					break;
				}
			}
		}
	}
	int s,t,x,y;
	cin>>s>>t>>x>>y;
	dijkstra_hp((s-1)*m+t);
	if(d[(x-1)*m+y]==0x3f3f3f3f) cout<<-1<<endl;
	else cout<<d[(x-1)*m+y]<<endl;
//	cout<<d[(x-1)*m+y]==0x3f3f3f3f?-1:d[(x-1)*m+y];
	return 0;
}
```

代码很笨，但很好懂。

---

## 作者：harmis_yz (赞：1)

题解摘自 [CSP2024 前做题情况](https://www.luogu.com.cn/article/9zpicw3e)。

## 分析

注意力极强。

注意到，我们最优的方案显然是走最短路。也就是说，只要我们将 $(r1,c1)$ 到 $(r2,c2)$ 的最短路求出来，这题就解决了。

考虑最短路是什么形式的。记最短路依次经过的点的序列为 $P$。如果存在 $P_i=P_j\land i<j$，那么我们完全可以不要 $(i,j]$ 这一段，直接从 $P_i$ 到 $P_{j+1}$。所以，如果一条路径是最短的，一定不会经过同一个点两次。

有这个性质，这题就好做了。不难发现，题目中将经过的点设为不可走实际上没有任何用。那么考虑建图。对于点 $(i,j)$ 要到相邻的点，其最少步数一定为 $2$，如果直接向相邻点移动之后直接停在相邻点除外。因为我们过去再回来，出发点已经不可走了，所以会停在那个点上。同时，我们再将一个点向四周移动所到达的点连一条边权为 $1$ 的边。

接下来证明该建图的可行性。对于一个点 $(x,y)$ 到 $(x',y')$，如果能够通过这些边直连，那么一定是最短路。如果不能，考虑到 $(x,y)$ 这个点下一步只能向某个方向行走，再下一步要么折返要么继续朝其它地方走。其它地方走的情况 $(x,y)$ 对其没有影响，只有折返时会停在 $(x,y)$ 的一个四联通点上。所以连这种边可以保证正确性。由于点只能这么走，所以最短路一定会是这些边组成的路径。

建完边之后跑个最短路就行了。时间复杂度 $O(hw\log hw)$。

## 代码

```cpp
il void dij(){
	memset(dis,0x3f,sizeof(dis));
	priority_queue<pii,vector<pii>,greater<pii>> qu;
	qu.push({0,id(r1,c1)}),dis[id(r1,c1)]=0;
	while(!qu.empty()){
		pii u=qu.top();qu.pop();
		if(vis[u.y]) continue;
		vis[u.y]=1;
		for(auto v:e[u.y])
		if(dis[v.x]>dis[u.y]+v.y){
			dis[v.x]=dis[u.y]+v.y;
			qu.push({dis[v.x],v.x});
		}
	}
	return ;
}

il void solve(){
	n=rd,m=rd;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j) cin>>ch[i][j];
	r1=rd,c1=rd,r2=rd,c2=rd;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j)
	if(ch[i][j]=='.'){
		for(re int k=0;k<4;++k){
			int i_=dx[k]+i,j_=dy[k]+j;
			if(ch[i_][j_]=='.') e[id(i,j)].push_back({id(i_,j_),2});
		}	
		for(re int j_=j+1;j_<=m;++j_)
			if(ch[i][j_]=='.'&&ch[i][j_+1]=='#') e[id(i,j)].push_back({id(i,j_),1});
			else if(ch[i][j_]=='#') break;	
		for(re int j_=j-1;j_>=1;--j_)
			if(ch[i][j_]=='.'&&ch[i][j_-1]=='#') e[id(i,j)].push_back({id(i,j_),1});
			else if(ch[i][j_]=='#') break;	
		for(re int i_=i+1;i_<=n;++i_)
			if(ch[i_][j]=='.'&&ch[i_+1][j]=='#') e[id(i,j)].push_back({id(i_,j),1});
			else if(ch[i_][j]=='#') break;			
		for(re int i_=i-1;i_>=1;--i_)
			if(ch[i_][j]=='.'&&ch[i_-1][j]=='#') e[id(i,j)].push_back({id(i_,j),1});
			else if(ch[i_][j]=='#') break;			
	}
	dij();
	if(dis[id(r2,c2)]>1e18) printf("-1\n");
	else printf("%lld\n",dis[id(r2,c2)]);
    return ;
}
```

---

## 作者：lizicheng3042 (赞：0)

首先，我的大致思路和其他题解一样，所以我并不打算去讲怎么转化题目，证明结论和讲解建图方法，这没必要。  
看了一下其他题解，都是写的最短路算法，但是其实这里可以用特化的 bfs 求解，我打算讲一下这个。  
首先，我们注意到这道题里边权只有 $1$ 和 $2$ 两种，所以我们直接跑的话只能跑堆优化 Dijkstra，但是边权只有两种，我们有两种方法可以让 bfs 成为可行的算法。  
1. 建虚点拆边权。边权为 $1$ 的图用 bfs 找最短路可行是因为每一次用来更新的点都是剩余点中点权最小的之一，所以，我们完全可以把边权为 $2$ 的边拆成是先连向一个虚点，然后再连向终点，简单好写，而且跑得不慢。  
2. 两个队列。我们刚才说了，bfs 的可行性建立在用于更新的点的点权单调不降，所以，我们可以开两个队列，分别维护由边权为 $2$ 的边转移过来的点和由边权为 $1$ 的边转移过来的点，每一次从两个队列的队首取更小的那个用来转移，这样，首先保证了更新点的点权单调不降，进而也保证了两个队列的点的点权单调不降，从而保证了 bfs 的正确性。  
以上两种做法都可以推广到边权种类更多的算法，但是第一种时间复杂度是 $O(n+m\max a_i)$（$m$ 表示边数，$a$ 表示所有的边所组成的集合，$\max a_i$ 表示所有边的权值和最大值），空间复杂度相同，第二种时间复杂度是 $O(n|a|+m)$（这里 $|a|$ 表示边权种类数），空间复杂度 $O(n+m)$，虽然不如 Dijkstra 泛用，但是在特殊情境下对优化时间复杂度比较有帮助。  
  
我这里只写了第二种方法，跑得很快，在不优化的情况下只用了 $200$ 多毫秒。  
## 代码  
```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
int n,m,fir[1000005],nxt[8000005],to[8000005],tot,lst,id[1005][1005],sx,sy,ex,ey,dis[1000005];
char map[1005][1005];
bool z[8000005],vis[1000005];
void add(int x,int y,int w)
{
	nxt[++tot]=fir[x];to[fir[x]=tot]=y;z[tot]=w;
}
void bfs()
{
	queue<int>k,t;
	k.push(id[sx][sy]);
	for(int a=1;a<=n;a++)
		for(int b=1;b<=m;b++)
			dis[id[a][b]]=m*n*3;
	dis[id[sx][sy]]=0;
	while(k.size()+t.size())
	{
		int u;
		if(k.empty())
		{
			u=t.front();
			t.pop();
		}
		else if(t.empty())
		{
			u=k.front();
			k.pop();
		}
		else
		{
			dis[t.front()]<dis[k.front()]?(u=t.front(),t.pop()):(u=k.front(),k.pop());
		}
		for(int a=fir[u];a;a=nxt[a])
		{
			int v=to[a];
			if(dis[v]>dis[u]+1+z[a])
			{
				dis[v]=dis[u]+1+z[a];
				if(vis[v])
					continue;
				if(z[a])
					t.push(v);
				else
					k.push(v);
				vis[v]=true;
			}
		}
	}
}
int main()
{	
	scanf("%d%d",&n,&m);
	for(int a=1;a<=n;a++)
		scanf("%s",map[a]+1);
	for(int a=1;a<=n;a++)
	{
		lst=1;
		for(int b=1;b<=m;b++)
		{
			id[a][b]=(a-1)*m+b; 
			if(map[a][b]=='#')
			{
				if(b-lst>1)
				{
					add(id[a][lst],id[a][b-1],0);add(id[a][b-1],id[a][lst],0);
					for(int c=lst+1;c<b-1;c++)
						add(id[a][c],id[a][b-1],0),add(id[a][c],id[a][lst],0);
					if(lst<b-2)
					{
						for(int c=lst+2;c<b;c++)
							add(id[a][c],id[a][c-1],1);
						for(;lst<b-2;lst++)
							add(id[a][lst],id[a][lst+1],1);	
					}
				}
				lst=b+1;
			}
		}
	}
	for(int a=1;a<=m;a++)
	{
		lst=1;
		for(int b=1;b<=n;b++)
		{
			if(map[b][a]=='#')
			{
				if(b-lst>1)
				{
					add(id[lst][a],id[b-1][a],0);add(id[b-1][a],id[lst][a],0);
					for(int c=lst+1;c<b-1;c++)
						add(id[c][a],id[b-1][a],0),add(id[c][a],id[lst][a],0);
					if(lst<b-2)
					{
						for(int c=lst+2;c<b;c++)
							add(id[c][a],id[c-1][a],1);
						for(;lst<b-2;lst++)
							add(id[lst][a],id[lst+1][a],1);	
					}
				}
				lst=b+1;
			}
		}
	}
	scanf("%d%d%d%d",&sx,&sy,&ex,&ey);
	bfs();
	printf("%d\n",dis[id[ex][ey]]==n*m*3?-1:dis[id[ex][ey]]);
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

首先明确，滑冰产生的冰块并不会挡道。

因为假若滑冰产生的冰块挡道了，那么在滑这块冰之前就可以直接往目标点滑去。

那么考虑建立一个最短路模型。

如果两个点没有冰块，那么需要滑两次，否则需要一次。

一个行或者列上连续段上的点到连续段的两端也只需要一次。

求解最短路即可。

```cpp
#include<bits/stdc++.h>
#define pos(i,j)((i-1)*m+j)
using namespace std;
const int maxn = 1e3+114;
int mp[maxn][maxn];
int dx[4]={0,0,-1,1};
int dy[4]={1,-1,0,0};
#define RI register int
typedef pair<int,int> PR;
int n,m,S;
vector<int> road[maxn*maxn],ans[maxn*maxn];
int d[maxn*maxn],vis[maxn*maxn];
priority_queue<PR,vector<PR>,greater<PR> > f;

void Dijkstra() {
	for(RI i=0;i<=n*(m+2)+10;++i) d[i]= INT_MAX;
	d[S]=0,f.push((PR){d[S],S});
	while(!f.empty()) {

		PR tmp=f.top();f.pop();
		int x=tmp.second;
		if(d[x]!=tmp.first) continue;
		if(vis[x]) continue;
	
		vis[x]=1;
		for(RI i=0;i<road[x].size();++i)
			if(d[x]+ans[x][i]<d[road[x][i]]) {
				d[road[x][i]]=d[x]+ans[x][i];
				f.push((PR){d[road[x][i]],road[x][i]});
			}
	}
}

void add(int u,int v,int w){
	if(u==v) return ;
	road[u].push_back(v);
	ans[u].push_back(w);
}

void build(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=0;k<4;k++){
				int nx=i+dx[k],ny=j+dy[k];
				if(nx<1||nx>n||ny<1||ny>m||mp[nx][ny]==0) continue;
				if(mp[nx+dx[k]][ny+dy[k]]==0){
					add(pos(i,j),pos(nx,ny),1);
				}
				else{
					add(pos(i,j),pos(nx,ny),2);
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		int lst=-1;
		for(int j=1;j<=m;j++){
			if(mp[i][j]==0){
				if(lst!=-1){
					for(int k=lst;k<j;k++){
						add(pos(i,k),pos(i,lst),1);
						add(pos(i,k),pos(i,j-1),1);
					}
				}
				lst=-1;
			}
			else if(lst==-1){
				lst=j;
			}
		}
		if(lst!=-1&&mp[i][m]==1){
			for(int k=lst;k<=m;k++){
				add(pos(i,k),pos(i,lst),1);
				add(pos(i,k),pos(i,m),1);
			}
		}
	}
	for(int j=1;j<=m;j++){
		int lst=-1;
		for(int i=1;i<=n;i++){
			if(mp[i][j]==0){
				if(lst!=-1){
					for(int k=lst;k<i;k++){
						add(pos(k,j),pos(lst,j),1);
						add(pos(k,j),pos(i-1,j),1);
					}
				}
				lst=-1;
			}
			else if(lst==-1){
				lst=i;
			}
		}
		if(lst!=-1&&mp[n][j]){
			for(int k=lst;k<=n;k++){
				add(pos(k,j),pos(lst,j),1);
				add(pos(k,j),pos(n,j),1);
			}
		}
	}
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c;
			cin>>c;
			if(c=='.'){
				mp[i][j]=1;
			}
		}
	}
	int r1,c1,r2,c2;
	cin>>r1>>c1>>r2>>c2;
	build();
	S=pos(r1,c1);
	Dijkstra();
	cout<<(d[pos(r2,c2)]!=INT_MAX?d[pos(r2,c2)]:-1)<<'\n';
}
//#...#....#
```


---

## 作者：wangyibo201026 (赞：0)

## 思路

考虑一个点要到达另外一个点需要怎么做：

- 一格一格挪动，滑过去再滑回来，不断重复。
- 直接在一行滑到头，然后再往其他方向滑。

具体的，可以分成两种基本情况：

- 移动到相邻的格子，滑过去再滑回来，耗费 $2$ 个时间单位。
- 直接滑到头，直到撞到冰为止，只需要花费 $1$ 个时间单位。

很明显这样做是局部最优的。

于是我们想到可以建图跑最短路，每个点往旁边可以走的点连边权为 $2$ 的边，然后如果一个方向有冰块，那么同方向枚举一下，往这个点建边权为 $1$ 的边，然后跑最短路就好了。

然后我们思考一个问题，滑动一个冰块是否会对最短路有影响，zyb 告诉我们是不会的，因为显然跑到自己原来那个格子再去滑不是最优的。

## 代码

Code：

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e3 + 10;
const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

int n, m, sx, sy, fx, fy;
int dis[N * N];
char a[N][N];

bool vis[N * N];

bool Check ( int x, int y ) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

int head[N * N], tot;

struct Graph {
    int to, w, next;
} edges[10 * N * N];

void add ( int u, int v, int w ) {
    tot ++;
    edges[tot].to = v;
    edges[tot].w = w;
    edges[tot].next = head[u];
    head[u] = tot;
}

int getid ( int x, int y ) {
    return ( x - 1 ) * m + y;
}

void dijkstra ( int s ) {
    priority_queue < pair < int, int > > q;
    memset ( dis, 0x7f, sizeof ( dis ) );
    dis[s] = 0;
    q.push ( make_pair ( dis[s], s ) );
    while ( !q.empty () ) {
        int x = q.top ().second;
        q.pop ();
        if ( vis[x] ) {
            continue;
        }
        vis[x] = true;
        for ( int i = head[x]; i; i = edges[i].next ) {
            if ( dis[x] + edges[i].w < dis[edges[i].to] ) {
                dis[edges[i].to] = dis[x] + edges[i].w;
                q.push ( make_pair ( -dis[edges[i].to], edges[i].to ) );
            }
        }
    }
}

signed main () {
    cin >> n >> m;
    for ( int i = 1; i <= n; i ++ ) {
        for ( int j = 1; j <= m; j ++ ) {
            cin >> a[i][j];
        }
    }
    cin >> sx >> sy >> fx >> fy;
    for ( int i = 1; i <= n; i ++ ) {
        for ( int j = 1; j <= m; j ++ ) {
            if ( a[i][j] == '.' ) {
                for ( int k = 0; k < 4; k ++ ) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if ( Check ( nx, ny ) && a[nx][ny] == '.' ) {
                        add ( getid ( i, j ), getid ( nx, ny ), 2 );
                    }
                }
                if ( Check ( i, j + 1 ) && a[i][j + 1] == '#' ) {
                    int p = j - 1;
                    while ( Check ( i, p ) && a[i][p] == '.' ) {
                        add ( getid ( i, p ), getid ( i, j ), 1 );
                        p --;
                    }
                }
                if ( Check ( i, j - 1 ) && a[i][j - 1] == '#' ) {
                    int p = j + 1;
                    while ( Check ( i, p ) && a[i][p] == '.' ) {
                        add ( getid ( i, p ), getid ( i, j ), 1 );
                        p ++;
                    }
                }
                if ( Check ( i - 1, j ) && a[i - 1][j] == '#' ) {
                    int p = i + 1;
                    while ( Check ( p, j ) && a[p][j] == '.' ) {
                        add ( getid ( p, j ), getid ( i, j ), 1 );
                        p ++;
                    }
                }
                if ( Check ( i + 1, j ) && a[i + 1][j] == '#' ) {
                    int p = i - 1;
                    while ( Check ( p, j ) && a[p][j] == '.' ) {
                        add ( getid ( p, j ), getid ( i, j ), 1 );
                        p --;
                    }
                }
            }
        }
    }
    dijkstra ( getid ( sx, sy ) );
    cout << ( dis[getid ( fx, fy )] <= 5e9 ? dis[getid ( fx, fy )] : -1 ) << '\n';
    return 0;
}

/*
6 8
########
#......#
######.#
######.#
######.#
########
2 2
5 7
*/
```

---

