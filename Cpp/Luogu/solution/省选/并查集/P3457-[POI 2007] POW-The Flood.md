# [POI 2007] POW-The Flood

## 题目描述

**译自 POI 2007 Stage 2. Day 1「[The Flood](https://szkopul.edu.pl/problemset/problem/VutzcR1iPvGuYRGZgvNksmV1/site/?key=statement)」**

你有一张 $m \times n$ 的地图，地图上所有点都被洪水淹没了。你知道地图上每个网格的海拔高度，其中一部分点属于 Byteburg 城。你需要放置尽可能少的巨型抽水机，将 Byteburg 城从洪水中解救出来。巨型抽水机会抽干该格子的所有水，直到该格子不被洪水淹没为止。

水会在有公共边的格子间从高向低流动。

## 样例 #1

### 输入

```
6 9
-2 -2 -1 -1 -2 -2 -2 -12 -3
-2 1 -1 2 -8 -12 2 -12 -12
-5 3 1 1 -12 4 -6 2 -2
-5 -2 -2 2 -12 -3 4 -3 -1
-5 -6 -2 2 -12 5 6 2 -1
-4 -8 -8 -10 -12 -8 -6 -6 -4```

### 输出

```
2```

# 题解

## 作者：louhao088 (赞：19)

一道贪心好题。

首先我们发现如果在他周围比他低的点有抽水机，那么他肯定不用再放抽水机了。

很自然的得到一个想法，就是把所有点按高度排序。依次判断要抽水的点四周能连出去的点中是否有抽水机。

这个操作可以用并查集维护，把高的点放入四周低的点的并查集中，每次查询他所在并查集有没有抽水机，没有就加上。

可以证明这样操作能使答案最优。

时间复杂度 $O( nm \log{nm}) $ 。



------------
代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define re register
const int maxn=1e3+5;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
void print(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
int n,m,a[maxn][maxn],f[maxn][maxn],dx[4]={0,0,1,-1},dy[4]={1,-1,0,0},fa[maxn*maxn],s[maxn*maxn],ans=0;
struct node
{
	int x,y,num;
}b[1000005];
bool cmp(node a,node b){return a.num<b.num;}
int getf(int x){if(fa[x]==x)return x;fa[x]=getf(fa[x]);return fa[x];}
void gett(int x,int y)
{
	x=getf(x),y=getf(y);if(x==y)return ;
	fa[x]=y;s[y]|=s[x];
}
int id(int x,int y){return (x-1)*m+y;}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();memset(a,0x3f,sizeof a);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			a[i][j]=read();
			if(a[i][j]<0)a[i][j]=abs(a[i][j]);
			else f[i][j]=1;
			b[id(i,j)]=(node){i,j,a[i][j]};
			fa[id(i,j)]=id(i,j);
		}
	sort(b+1,b+id(n,m)+1,cmp);

	for(int i=1;i<=n*m;i++)
	{
		for(int j=0;j<4;j++)
		{
			int tx=b[i].x+dx[j],ty=b[i].y+dy[j];
			if(a[tx][ty]<=b[i].num)gett(id(tx,ty),id(b[i].x,b[i].y));
		}
		if(b[i].num!=b[i+1].num)
		{
			for(int j=i;;j--)
			{
				if(b[j].num!=b[i].num)break;
				if(f[b[j].x][b[j].y])
				{
					int h=getf(id(b[j].x,b[j].y));
					if(!s[h])s[h]=1,ans++;
				}
			}
		}
	}
	cout<<ans;
 	return 0;
}

```
如有帮到你，请点赞支持，谢谢。

---

## 作者：M_seа (赞：13)

**样例说明：**

![](http://img.blog.csdn.net/20180225095401231?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzYyODg5NzY=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

**题意解析：**
若在I放置一个抽水机，且J与I之间存在一条路径使得max(H)<=H[j]，那么J的水可以被抽干。

**算法：并查集**

1. 先将所有点按高度排序。
2. 枚举每个点，并将它 相邻的点且高度<=这个点的高度 的点与它合并。假设：这个点是a[i], 有一个满足 相邻的点且高度<=这个点的高度 这一条件的点a[j]，很明显a[i]的水可以流向a[j]， 所以如果a[j]的水已经被抽水机抽完了，那么a[i]的水也会被抽完。
3. 判断该点是否为城市。如果不为城市，则不需要抽水机。如果为城市且该联通块内没有抽水机，则在该城市放一个抽水机。（注意：这里必须先将同一高度的点都合并了才能判断）

**为什么必须先将同一高度的点都合并了才能判断呢？**

例如数据：
1 4
3 3 2 1

很明显答案是1
我们来模拟一下，排完序后，数据可能会变为
1 2 3 3（第3个 ‘3’为 原来序列的第1个）
那么边做时边判断是否有抽水机
到第3个3时 联通块为： 1-2 3 就要用两个抽水机了

[完整代码](http://blog.csdn.net/qq_36288976/article/details/79367178)

---

## 作者：AuSquare (赞：5)

# 洛谷P3457 [POI2007]POW-The Flood结题报告

[题目链接戳这里](https://www.luogu.org/problemnew/show/P3457)

~~这道题的题目描述是真的有毒~~

## 题面解释:

对于布置有抽水机的点$i$和希望被抽干的某一点$j$,保证$j$的高度比$i$高,如果存在一条从$i$到$j$的路径使该路径上最高点的高度不超过$j$,则$j$节点可以被抽干(这里需要一点空间想象能力)

## 总体思路:BFS~~(貌似百度上还没有BFS的题解)~~

## 具体实现:

显然只有当抽水机建在较低的"山谷"中时才能够保证每一台抽水机能抽干的范围尽可能大从而减少抽水机的数量.

我们用$w[i][j]$表示位置$(i,j)$处当前能使水位下降到的最低高度.将城市中的所有位置按照海报高度递增排序并依次枚举,如果$w[i][j]>h[i][j]$说明在当前条件下的抽水机无法将这一点抽干,则考虑在该布置抽水机并更新$w$

对于点$(x_0, y_0)$上下左右的一点$(x_1, y_1)$对$w[x_0][y_0]$的可能贡献为$max(w[x_1][y_1], h[x_0][y_0])$,对$w[x_0][y_0]$取最小值即可,我们考虑借用$SPFA$的思路更新时将当前不在队列中的点加入队列中,每次从队列首取出元素进行更新.

代码片段如下

```cpp
void floodfill(int stx, int sty) {
    ans++; q.push((POINT){stx, sty}); inqueue[stx][sty]=true; w[stx][sty]=sq[stx][sty];
    while (!q.empty()) {
        POINT p=q.front(); q.pop();
        int nx=p.x, ny=p.y;
        for (int i=0; i<=3; i++) {
            int tx=nx+dx[i], ty=ny+dy[i];
            if (tx<1 || tx>n || ty<1 || ty>m) continue;
            int height=max(w[nx][ny], abs(sq[tx][ty]));
            if (height<w[tx][ty]) {
                w[tx][ty]=height;
                if (!inqueue[tx][ty]) {q.push((POINT){tx, ty}); inqueue[tx][ty]=true;}
            }
        }
        inqueue[nx][ny]=false;
    }
}
```

做完了吗?并没有,我们愉快的**超时**了

原因何在?注意到$SPFA$存在重复入队与更新的情况,因此为了尽量避免这种情况我们更新时优先从当前最低水位更低的点开始更新尽量保证到每一点时都获得最低水位高度.具体实现只需要将高度更低的点尽量向队首方向加入即可.然后这里在队列部分用的是循环队列(其实理论上来说这里用优先队列应该也可以,但是我反正$TLE$了,有哪位大佬写出来以后借我看一看QAQ)

附上代码片段:

```cpp
void floodfill(int stx, int sty) {
	int l=0, r=0; ans++; 
	q[l].x=stx; q[l].y=sty; inqueue[stx][sty]=true; w[stx][sty]=sq[stx][sty];
	while (l!=r+1) {
		int nx=q[l].x, ny=q[l].y; l=(l+1)%maxl;
		for (int i=0; i<=3; i++) {
			int tx=nx+dx[i], ty=ny+dy[i];
			if (tx<1 || tx>n || ty<1 || ty>m) continue;
			//if (sq[tx][ty]>0 && w[nx][ny]>sq[tx][ty]) continue;
			int height=max(w[nx][ny], abs(sq[tx][ty]));
			if (height<w[tx][ty]) {
				w[tx][ty]=height;
				if (!inqueue[tx][ty]) {//此时我们优先访问抽水高度更低的 
					inqueue[tx][ty]=true;
					if (w[tx][ty]<=w[q[l].x][q[l].y]) {
                      	l--; if (l<0) l=maxl-1;q[l].x=tx; q[l].y=ty;} 
					else {r=(r+1)%maxl; q[r].x=tx; q[r].y=ty;}
				}
			}
		}
		inqueue[nx][ny]=false;
	}
}
```

然后就AC啦!!!

附上完整AC代码:

```cpp
/*尝试优化SPFA*/ 
#include <bits/stdc++.h>
using namespace std;
const int maxn=1100, maxp=maxn*maxn, maxl=1000000;
const int dx[]={-1, 0, 0, 1}, dy[]={0, -1, 1, 0};
struct POINT {int x, y, h;}point[maxp], q[maxl];
int n, m, ans=0, cnt=0, sq[maxn][maxn], w[maxn][maxn];
bool inqueue[maxn][maxn];
 
int read() {
	int x=0, f=1; char ch=getchar();
	while (ch>'9' || ch<'0') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0' && ch<='9') {x=x*10+ch-'0'; ch=getchar();}
	return x*f;
}
bool cmp(POINT a, POINT b) {return a.h<b.h;}
void init() {
	n=read(), m=read();
	for (int i=1; i<=n; i++) 
		for (int j=1; j<=m; j++) {
			sq[i][j]=read();
			if (sq[i][j]>0) {point[++cnt].x=i; point[cnt].y=j; point[cnt].h=sq[i][j];}
		}
	sort(point+1, point+1+cnt, cmp);
}
void floodfill(int stx, int sty) {
	int l=0, r=0; ans++; 
	q[l].x=stx; q[l].y=sty; inqueue[stx][sty]=true; w[stx][sty]=sq[stx][sty];
	while (l!=r+1) {
		int nx=q[l].x, ny=q[l].y; l=(l+1)%maxl;
		for (int i=0; i<=3; i++) {
			int tx=nx+dx[i], ty=ny+dy[i];
			if (tx<1 || tx>n || ty<1 || ty>m) continue;
			if (sq[tx][ty]>0 && w[nx][ny]>sq[tx][ty]) continue;
			int height=max(w[nx][ny], abs(sq[tx][ty]));
			if (height<w[tx][ty]) {
				w[tx][ty]=height;
				if (!inqueue[tx][ty]) {//此时我们优先访问抽水高度更低的 
					inqueue[tx][ty]=true;
					if (w[tx][ty]<=w[q[l].x][q[l].y]) {
						l--; if (l<0) l=maxl-1;
						q[l].x=tx; q[l].y=ty;} 
					else {r=(r+1)%maxl; q[r].x=tx; q[r].y=ty;}
				}
			}
		}
		inqueue[nx][ny]=false;
	}
}
void work() {
	memset(w, 0x3f, sizeof(w));//w[i][j]表示当前点(i,j)处能使洪水降低到的最低高度 
	for (int i=1; i<=cnt; i++) 
		if (w[point[i].x][point[i].y]>sq[point[i].x][point[i].y]) floodfill(point[i].x, point[i].y);
	/*for (int i=1; i<=n; i++) {
		for (int j=1; j<=m; j++) 
			printf("%d ", w[i][j]);
		cout << endl;
	}*/
	printf("%d\n", ans);
}
int main() {
	init();
	work();
	return 0;
}
```



---

## 作者：Danny_chan (赞：1)

我们发现只要高度比这个点低的所有点只用放一台抽水机。

我们可以先按高度排序，然后查看这个格子是否比周围的高，如果高那把这两个格子合并。


最后，在高度不相等的情况下查看所在的集合是否有抽水机，如果没有就加一台。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,s[1000010];
int a[1010][1010],f[1010][1010];
struct node{
	int x,y,z;
}b[1000010];
int fa[1000010],sum=0;
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
bool cmp(node x,node y){
	return x.z<y.z;
}
int find(int x){
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
void add(int x,int y){
	int f_x=find(x);
	int f_y=find(y);
	if(f_x!=f_y){
		fa[f_x]=f_y;
		s[f_y]|=s[f_x];
	}
}
int w(int x,int y){
	return (x-1)*m+y;
}
signed main() {
	cin>>n>>m;
	memset(a,0x3f,sizeof(a)); 
	for(int i=1;i<=n;i++){//预处理数据 
		for(int j=1;j<=m;j++){ 
			cin>>a[i][j];
			if(a[i][j]<0){
				a[i][j]=abs(a[i][j]);
			}
			else f[i][j]=1;
			b[w(i,j)]={i,j,a[i][j]};
			fa[w(i,j)]=w(i,j);
		}
	}
	sort(b+1,b+n*m+1,cmp);//排序 
	for(int i=1;i<=n*m;i++){
		for(int j=0;j<4;j++){
			int x=b[i].x+dx[j];
			int y=b[i].y+dy[j];
			if(b[i].z>=a[x][y]){//查看是否比他大 
				add(w(x,y),w(b[i].x,b[i].y));
			}
		}
		if(b[i].z!=b[i+1].z){
			for(int j=i;j>=0;j--){
				if(b[j].z!=b[i].z) break;
				if(f[b[j].x][b[j].y]>0){
					int x=find(w(b[j].x,b[j].y));
					if(s[x]==0){//如果没有抽水机，加一台 
						s[x]=1;
						sum++;
					}
				}
			}
		}
	}
	cout<<sum<<endl;
	return 0;
}
```

---

## 作者：qwer6 (赞：0)

## Description

[摘自洛谷题面](https://www.luogu.com.cn/problem/P3457)。

你有一张 $m \times n$ 的地图，地图上所有点都被洪水淹没了。你知道地图上每个网格的海拔高度，其中一部分点属于 Byteburg 城。你需要放置尽可能少的巨型抽水机，将 Byteburg 城从洪水中解救出来。巨型抽水机会抽干该格子的所有水，直到该格子不被洪水淹没为止。

水会在有公共边的格子间从高向低流动。

## Solution

首先我们可以发现，在相邻的格子中，放在海拔低的地方一定会比放在海拔高的地方更优，不管两个地方是不是城区，因为放在海拔低的地方一定可以抽干海拔高的地方可以抽干的地方，所以我们先把所有坐标按照海拔从低到高排序，然后依次考虑。

考虑到这其实是一个连通性问题，所以我们使用并查集维护。

把所有海拔相同的坐标放在一起考虑，假设现在取出了一个坐标 $(x,y)$，那么将与 $(x,y)$ 相邻且海拔不高于 $(x,y)$ 的位置并入同一个并查集。

然后检查是否需要放抽水机，由于我们从低到高考虑位置，所以现在如果在一个并查集中的海拔最低的位置放一个抽水机，那么一定可以抽完并查集内的水，所以当这个位置是城区，并且这个并查集中还没有放抽水机，那么就放一个抽水机即可。

注意，一定要将所有海拔相同的坐标都并入并查集之后再检查是否需要放抽水机！

## Code

```c++
/*by qwer6*/
/*略去缺省源和快读快写*/
const int N=1005,dx[]={1,-1,0,0},dy[]={0,0,1,-1};
int n,m,ans;
int h[N][N];
vector<pii>a[N];
struct DSU{
	int n,m;
	int fa[N*N],siz[N*N];
	void init(int _n){
		n=_n;
		for(int i=1;i<=n;i++)
			fa[i]=i,siz[i]=0;
	}
	int find(int x){
		if(fa[x]==x)return x;
		return fa[x]=find(fa[x]);
	}
	void merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y)return ;
		fa[x]=y;
		siz[y]+=siz[x];
	}
}dsu;
signed main(){
	read(m),read(n);
	dsu.init(n*m);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			read(h[i][j]);
			a[abs(h[i][j])].push_back({i,j});
		}
	for(int i=1,x,y,xx,yy,fa;i<=1000;i++){
		for(pii tmp:a[i]){
			x=tmp.first,y=tmp.second;
			for(int j=0;j<4;j++){
				xx=x+dx[j],yy=y+dy[j];
				if(xx<1||xx>m)continue;
				if(yy<1||yy>n)continue;
				if(abs(h[x][y])<abs(h[xx][yy]))continue;
				dsu.merge(id(x,y),id(xx,yy));
			}
		}
		for(pii tmp:a[i]){
			x=tmp.first,y=tmp.second;
			fa=dsu.find(id(x,y));
			if(h[x][y]>0&&dsu.siz[fa]==0){
				ans++;
				dsu.siz[fa]=1;
			}
		}
	}
	write(ans);
}
```

---

## 作者：huhangqi (赞：0)

感觉难度全部都在题面了，完全看不懂。

简单来讲就是有一个点经过相邻的不大于它的数字可以到达一个抽水机，那么这里就会被抽水。

那么我们很明显会发现可以从低的地方放。

但是这道题目唯一的难点在于有的点是不需要被抽水的。

那么我们也可以想到某一些点的值会在放某一处时一起被抽水，并且容易发现，这样的点在每一组中一定是唯一存在的，毕竟这是有传递性的。

但是由于一个点可能会连接多个点，而并查集又不是连有向边，因此我们枚举完一个高度之后，需要直接统计是否需要安放，然后记录到并查集之中，方便下一次转移操作。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,fa[1000005],d[1000005],a[1005][1005],dx[]={0,0,1,-1},dy[]={1,-1,0,0},ans;
int id(int x,int y){
	return (x-1)*m+y;
}
int find(int x){
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return;
	d[x]|=d[y];
	fa[y]=x;
}
vector<pair<int,int>> e[1005];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)fa[id(i,j)]=id(i,j);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)e[abs(a[i][j])].push_back({i,j});
	for(int i=1;i<=n;i++)a[i][0]=a[i][m+1]=1001;
	for(int i=1;i<=m;i++)a[0][i]=a[n+1][i]=1001;
	for(int i=1;i<=1000;i++){
		for(auto j:e[i]){
			int x=j.first,y=j.second;
			for(int k=0;k<4;k++){
				if(abs(a[x+dx[k]][y+dy[k]])<=abs(a[x][y]))merge(id(x,y),id(x+dx[k],y+dy[k]));
			}
		}
		for(auto j:e[i]){
			int x=j.first,y=j.second;
			if(a[x][y]<0)continue;
			if(!d[find(id(x,y))]){
				d[find(id(x,y))]=1;
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
}

``````

---

## 作者：ty_mxzhn (赞：0)

可以建出图来。假设 $h_i \le h_j$ 并且 $i,j$ 相邻，则连边 $i \to j$。

显然这有点像一个 DAG（但是并不是）。你可以把这个图缩点，答案是对缩点后的图拓扑，所有城市假设没被另一个城市支配掉就一定要放一个抽水机。

这个图论问题显然其实很经典。但是这个二维网格图显然有性质，所以你不需要这么写。你可以按照高度从低到高排序，每次处理一堆高度相等的点，如果所连接到的联通块里面还没有抽水机就放一个抽水机。

显然的，这样子做和之前的图论做法并没有什么本质区别。我们一开始只是想办法把他规约到了一个图论问题上而已。

代码很短。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

struct stu{
	int x,y,h,t;
	bool operator < (stu b)const{
		return h<b.h;
	}
}a[1000007];
int h[1007][1007],ps[1007][1007],fa[1000007],vi[1000007];
int n,m;
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]); 
}
int dx[]={0,0,-1,1},dy[]={-1,1,0,0};
void link(int x,int y){
	int r=find(ps[x][y]);
	for(int i=0;i<4;i++){
		int nx=x+dx[i],ny=y+dy[i];
		if(nx<1||nx>n||ny<1||ny>m) continue;
		int z=find(ps[nx][ny]);
		if(h[nx][ny]<=h[x][y]){
			fa[z]=r;
			vi[r]|=vi[z];
		}
	}
}
int ans;
void work(int x,int y){
	int r=find(ps[x][y]);
	if(vi[r]) return;
	vi[r]=true;
	ans++;
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1,p;j<=m;j++){
			ps[i][j]=(i-1)*m+j;
			scanf("%d",&h[i][j]);
			if(h[i][j]>0) a[ps[i][j]].h=h[i][j],a[ps[i][j]].t=1;
			else h[i][j]=a[ps[i][j]].h=-h[i][j];
			a[ps[i][j]].x=i,a[ps[i][j]].y=j;
		}
	}
	for(int i=1;i<=n*m;i++) fa[i]=i;
	sort(a+1,a+n*m+1);
	a[0].h=a[n*m+1].h=-1001;
	for(int i=1;i<=n*m;i++){
		link(a[i].x,a[i].y);
		if(a[i].h!=a[i+1].h){
			for(int j=i;a[j].h==a[i].h;j--){
				if(a[j].t) work(a[j].x,a[j].y);
				//printf("%d ",a[j].h);
			}
			//printf("\n");
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：mountzhu (赞：0)

### 先说明一下抽水的定义：
假设当前有一个抽水机放在 $i$ 点，若存在一条到 $j$ 的路径 $P$（不包含 $i,j$）使得 $\small \max\limits_{k\in P} h_k \le h_j$，则 $j$ 点也可以被抽干。每个点的高度是其对应位置数的绝对值。这一点后面会用到。

---

非常直接的想法就是选择最低的地方放抽水机，但是在什么地方放呢？

我们是要在抽干城市的水，所以只在城市放是不劣的，这一点很多题解没有说清楚。

考虑反证法，如果有一个低的点，可以使得放在这里能让这个连通块内的城市全都被抽干，那么一定存在一个城市也可以。因为一定有一个路径，可以通过低的那个点走到其他城市；而如果对于高的点，放抽水机肯定不优。~~感性理解一下~~

其实这个可以看一下[这篇题解](https://www.luogu.com.cn/article/9he926c7)，不是一定放在城市，只是可以。

---

### 那么我们的步骤：
我们将点从小到大排序，并对这个点进行合并操作，维护连通块。如果这个点所在连通块中没有城市且这个点是城市，就放一个抽水机。

---
### 一个非常重要的事情我们要申明：
+ 连通块存在的意义是**判断当前点的水能不能流到前面判过了的海拔较低的点**，是判断一个连通块内的点都可以走到最低的点，而我们的实现是**反着的**，是判断这个点能不能被周围的点到达。

+ 因为我们是从前往后扫，只知道小的点的联通情况，所以这个点与前面的点是被到达的关系（BFS 是正着的）！我们正着思考是如我上面所说的**抽水定义**来判断的，反着思考虽然因为对称性（应该不叫对称性，姑且一用）是一样的，但是**本质上**是有区别的。

+ 更通俗一点就是我们**是根据水能不能从当前点流到最低点来判断能不能被低的点抽到，是判断当前点能否被代表元到达，而不是以当前点为代表元，那样就成了高的点抽低的点的水了**。


---
### 还有一个问题：
由于每次每个点**只会在周围四个点向外合并**，所以如果一个点被所有相同的海拔包在里面了（虽然高度相同，但是由于排序了，所以不会在一个地方），并查集是会把它们判成不同连通块的的。**是出于这个问题才应该将所有海拔相同的合并完**，再返回去处理前面的。

Hack 数据我借用一下第二篇题解的：
```cpp
3(1) 3(2) 2(3) 1(4)
```
括号里是编号

排完序变成：
```cpp
1 2 3(1) 3(2)
```
我们从前往后扫，发现第一个 $3$ 和后面的 $1,2$ 中间是有一个 $3$ 隔着的，因而第一个 $3$ 没有更新。

为什么会出错？其实是因为**手太短了，一次搜索没有将所有可以并的点都并进来**。前面我们说了，我们是**正着反过来做的，所以其实是传递性出了问题**，而 **BFS** 一次搜到底就没有这个问题。

我们可以发现，只有这种情况会有问题，因为如果高了就出不去，低了之前就被合并过。所以**不是因为海拔相同出问题**，是因为**只有海拔相同这个问题才会暴露出来**。所以我们先将海拔相同的合并完再回去判断前面的才是对的。

时间复杂度 $O(nm\log nm)$，细节见代码。

这个题的本质见[另一篇题解](https://www.luogu.com.cn/article/9he926c7)。

------
### Code

并查集，~~好久没写过这么不压行的代码了~~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
struct P{
	int x,y,h;
}p[N]; 
int n,m,f[1005][1005];
int fa[N],tag[N],ans;
inline int read(){
	char ch=getchar();int x=0,f=1;
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
inline bool cmp(P A,P B){return abs(A.h)<abs(B.h);}
inline int pos(int x,int y){return m*(x-1)+y;}
inline int find(int x){
	if(fa[x]==x)return x;
	else return fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y) return;
	fa[y]=x,tag[x]|=tag[y];//从哪里到，就是哪里的儿子
}
int main(){
	n=read(),m=read();
	for(int i=0;i<=n+1;++i){
		for(int j=0;j<=m+1;++j){
			f[i][j]=1e9+5;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			p[pos(i,j)].x=i,p[pos(i,j)].y=j;
			f[i][j]=p[pos(i,j)].h=read();
		}
	}
	sort(p+1,p+n*m+1,cmp);
	for(int i=1;i<=n*m;++i) fa[i]=i;
	for(int i=1;i<=n*m;++i){
		if(abs(p[i].h)>=abs(f[p[i].x-1][p[i].y])){
			merge(pos(p[i].x,p[i].y),pos(p[i].x-1,p[i].y));
		}
		if(abs(p[i].h)>=abs(f[p[i].x+1][p[i].y])){
			merge(pos(p[i].x,p[i].y),pos(p[i].x+1,p[i].y));
		}
		if(abs(p[i].h)>=abs(f[p[i].x][p[i].y-1])){
			merge(pos(p[i].x,p[i].y),pos(p[i].x,p[i].y-1));
		}
		if(abs(p[i].h)>=abs(f[p[i].x][p[i].y+1])){
			merge(pos(p[i].x,p[i].y),pos(p[i].x,p[i].y+1));
		}
		if(abs(p[i].h)==abs(p[i+1].h))continue;
		int y;
		for(int j=i;abs(p[j].h)==abs(p[i].h);--j){//对之前所有海拔相同的点都统计 
			if(f[p[j].x][p[j].y]>0){
				y=find(pos(p[j].x,p[j].y));
				if(!tag[y]) tag[y]=1,++ans;
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：wgyhm (赞：0)

## Description

https://www.luogu.com.cn/problem/P3457



## Solution

丹砂成功了，但是做完看题解发现想复杂了。/kk

首先，观察到如果在 $x$ 放抽水机能把 $y$ 中的水抽干，当且仅当存在一条路径，路径上的点都 $\le h_y$。

这启发我们给所有点按海拔排序。

并查集维护满足在这个点放抽水机使得 $x$ 被抽干的连通块。 

然后观察到如果在不是城市的点放抽水机肯定不优。我们直接钦定把饮水机放在当前连通块中是城市且高度最小的点上。并查集维护连边的方向。这样贪心感觉很对。

复杂度 $O(nm)$，要乘上并查集复杂度（一般我认为是常数）。

---

写完之后看题解，发现如果合并时当前点为城市且连通块没有饮水机就在当前城市放，这样更好写啊，而且和上面啊的做法似乎本质相同。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define maxn 1005
#define put() putchar('\n')
#define Tp template<typename T>
#define Ts template<typename T,typename... Ar>
using namespace std;
Tp void read(T &x){
    int f=1;x=0;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    x*=f;
}
namespace Debug{
	Tp void _debug(char* f,T t){cerr<<f<<'='<<t<<endl;}
	Ts void _debug(char* f,T x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	#define gdb(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
#define fi first
#define se second
#define mk make_pair
const int mod=1e9+7;
int power(int x,int y=mod-2) {
	int sum=1;
	while (y) {
		if (y&1) sum=sum*x%mod;
		x=x*x%mod;y>>=1;
	}
	return sum;
}
int n,m;
int id(int x,int y) {return (x-1)*m+y;}
int a[maxn][maxn],vis[maxn][maxn];
int fa[maxn*maxn*4],t[maxn*maxn],g[maxn*maxn],ans=0;
int fx[5]={1,-1,0,0},fy[6]={0,0,1,-1};
int getfa(int x) {return x==fa[x]?x:fa[x]=getfa(fa[x]);}
vector<pair<int,int> >O[maxn];
signed main(void){
	int i,x,j,k,l;
	read(n);read(m);
	for (i=1;i<=n;i++) 
		for (j=1;j<=m;j++) {
			read(x);
			if (x>0) a[i][j]=x,vis[i][j]=1;
			else a[i][j]=-x;
			fa[id(i,j)]=id(i,j);
			if (vis[i][j]) g[id(i,j)]=a[i][j];
			else g[id(i,j)]=1e9;
			O[a[i][j]].push_back(mk(i,j));
		}
	for (l=0;l<=1000;l++) {
		for (auto tmp:O[l]) {
			i=tmp.fi,j=tmp.se;
			int Min=a[i][j],idx=0,idy=0;
			for (k=0;k<4;k++) {
				int xx=i+fx[k],yy=j+fy[k];
				if (xx&&yy&&xx<=n&&yy<=m&&a[xx][yy]<=a[i][j]) {
					if (g[getfa(id(xx,yy))]<=g[getfa(id(i,j))]) {
						fa[getfa(id(i,j))]=getfa(id(xx,yy));
					}
					else fa[getfa(id(xx,yy))]=getfa(id(i,j));
				} 
			}
		}
		for (auto tmp:O[l]) {
			i=tmp.fi,j=tmp.se;
			if (vis[i][j]) t[getfa(id(i,j))]=1,x=getfa(id(i,j));//,gdb(l,i,j,(x-1)/m+1,(x-1)%m+1);
		}
	}
	for (i=1;i<=n*m;i++) ans+=t[i];
	printf("%d\n",ans);
	return 0;
}
//i=begin && g++ $i.cpp -o $i -std=c++14 && ./$i
```





---

