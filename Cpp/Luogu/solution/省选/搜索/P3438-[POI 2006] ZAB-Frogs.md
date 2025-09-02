# [POI 2006] ZAB-Frogs

## 题目描述

A scourge of frogs destroying all the crop has started in Byteotia. A farmer named Byteasar has decided to fight the vermin with peculiar "scarefrogs", that he has set up at certain points of his field. While moving from one place to another, every frog tries to keep as far of them as possible, i.e. maximizes the distance to the closest scarefrog.

The field that belongs to Byteasar has rectangular shape. The frogs leap in directions parallel to the field's sides and their leaps are unitary (of length 1). The scarefrogs-distance, for a given frog's route, is the minimum of all distances from all scarefrogs at all inter-leap-points of the route.

Byteasar already knows the most common starting and destination points of the frogs' routes, therefore he experiments with various deployments of the scarefrogs. He asks you for help, namely he would like you to write a programme that calculates the maximum (over all routes) scarefrogs-distance for a given deployment of scarefrogs - which we call in short the frogshold distance.

TaskWrite a programme that:

reads from the standard input the size of the field, the coordinates of the screfrogs and the source and target position of a frog,determines the frogshold distance (the maximum scarefrogs-distance a frog may achieve while still being able to reach the target point)writes the square of this number to the standard output.

给定一个网格图，其中有一些坏点，要求使起点到终点的路径上的所有点到离该点最近的坏点的最小距离距离最大，求这个最大值。


## 样例 #1

### 输入

```
5 5
1 1 5 5
2
3 3
4 2```

### 输出

```
4```

# 题解

## 作者：Alex_Wei (赞：9)

> [P3438 [POI2006]ZAB-Frogs](https://www.luogu.com.cn/problem/P3438)
>
> [在我的 cnblogs 中查看](https://www.cnblogs.com/alex-wei/p/interesting_frogs.html)。

给出一个不一样的解法。不需要用到斜率优化等高级算法。

下文记 $n=w_x,m=w_y$。

---

首先，答案显然满足可二分性，因此二分答案 $d\in [0,nm]$ 确定距离的平方。

这样我们将题目转化为：求起点到终点之间是否有一条路径使得任何一个点都不被圆心是整点且半径相同的若干个圆所覆盖。记 $r=\sqrt d$。如果处理出一个点是否被覆盖，那么可以 $\mathcal{O}(nm)$ BFS 求出答案

枚举每一竖列即 $x$，显然覆盖到该列的圆的圆心 $x_i$ 坐标满足 $(x_i-x)^2\leq d$ 即 $x_i-r\leq x\leq x_i+r$。将所有圆按照 $x_i$ 从小到大排序，Two-pointers 维护即可。

如果直接考虑一个点被覆盖的圆会很难做。不妨转换思路，枚举能够覆盖这一竖列的所有圆，记圆心为 $(x_i,y_i)\ (x_i-r\leq x\leq x_i+r)$。显然，它能覆盖到的第 $x$ 列的所有点的纵坐标 $y$ 形成了一段区间。差分计算线段覆盖即可。

当然这么做显然是过不去的，因为一共有 $m$ 列，而枚举到的圆的个数为 $\mathcal{O}(nm)$。因此时间复杂度为 $nm^2\log(nm)$。

---

考虑优化上面的算法。注意到在枚举所有圆时，如果出现两个圆 $(x_1,y_1)$ 和 $(x_2,y_2)$ 满足 $y_1=y_2$ 且 $|x_1-x|>|x_2-x|$，那么我们根本不需要考虑第一个圆 $(x_1,y_1)$，因为它能覆盖到的第 $x$ 列的所有点**包含于** $(x_2,y_2)$ 能覆盖到的第 $x$ 列的所有点。这是很显然的，因为前者的 $y$ 需要满足 $|y-y_1|\leq \sqrt {d-(x_1-x)^2}$，后者的 $y$ 需要满足 $|y-y_2|\leq \sqrt {d-(x_2-x)^2}$，而 $\sqrt {d-(x_1-x)^2}>\sqrt {d-(x_2-x)^2}$。

因此，对于每一行 $y$，维护圆心纵坐标为 $y$ 且与当前 $x$ 距离最小的圆，那么最终我们只需枚举 $\mathcal{O}(n)$ 个圆即可。具体地，维护 $n$ 个存**横坐标 $x_i$** 的队列，在 Two-pointers 添加或删除一个圆 $(x_i,y_i)$ 时，对第 $y_i$ 个队列进行添加或删除操作即可。此外，移动到下一列 $x\gets x+1$ 时，不断弹出每个队的队首元素直至队列只剩下一个元素或队列队首横坐标与 $x+1$ 的距离**小于**队首下一个横坐标与 $x+1$ 的距离。

时间复杂度为 $\mathcal{O}(nm\log (nm))$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define gc getchar()
#define pii pair <int,int>
#define fi first
#define se second
#define mem(x,v) memset(x,v,sizeof(x))

inline int read(){
	int x=0,sign=0; char s=gc;
	while(!isdigit(s))sign|=s=='-',s=gc;
	while(isdigit(s))x=(x<<1)+(x<<3)+(s-'0'),s=gc;
	return sign?-x:x;
}

const int N=1e3+5;

int n,m,leg[N][N];
int stx,sty,edx,edy,num;
struct point{
	int x,y;
}p[N*N],mp[N][N];

bool vis[N][N];
pii q[N*N];
bool bfs(){
	if(vis[stx][sty]==1)return 0;
	int h=1,tl=0; q[++tl]={stx,sty},vis[stx][sty]=1;
	while(h<=tl){
		int x=q[h].fi,y=q[h++].se;
		if(x==edx&&y==edy)return 1;
		if(!vis[x+1][y])vis[x+1][y]=1,q[++tl]={x+1,y};
		if(!vis[x-1][y])vis[x-1][y]=1,q[++tl]={x-1,y};
		if(!vis[x][y+1])vis[x][y+1]=1,q[++tl]={x,y+1};
		if(!vis[x][y-1])vis[x][y-1]=1,q[++tl]={x,y-1};
	} return 0;
}

int dist(int a,int b,int c,int d){return (a-c)*(a-c)+(b-d)*(b-d);}

int d[N][N],hd[N],len[N],s[N];
void add(point x){d[x.y][len[x.y]++]=x.x;}
void del(point x){if(d[x.y][hd[x.y]]==x.x)hd[x.y]++;}
void update(int y,int x){while(d[y][hd[y]+1]&&abs(d[y][hd[y]]-x)>=abs(d[y][hd[y]+1]-x))hd[y]++;}

bool check(int x){
	int dis=sqrt(x);
	mem(vis,0),mem(d,0),mem(hd,0),mem(len,0);
	for(int i=0;i<=max(n,m);i++)vis[0][i]=vis[i][0]=vis[n+1][i]=vis[i][m+1]=1;
	for(int i=1,l=1,r=1;i<=n;i++,mem(s,0)){
		while(r<=num&&i+dis>=p[r].x)add(p[r++]);
		while(l<=num&&i-dis>p[l].x)del(p[l++]);
		for(int j=1;j<=m;j++){
			update(j,i); int xx=d[j][hd[j]];
			if(!xx)continue;
			int radius=sqrt(x-(xx-i)*(xx-i)),l=j-radius,r=j+radius+1;
			s[max(1,l)]++,s[min(m+1,r)]--; 
		} for(int j=1;j<=m;j++)vis[i][j]=(s[j]+=s[j-1])>0;
	} return bfs();
}

int main(){
	cin>>n>>m>>stx>>sty>>edx>>edy>>num;
	for(int i=1;i<=num;i++)p[i].x=read(),p[i].y=read(),mp[p[i].x][p[i].y]=p[i];
	for(int i=1,cnt=0;i<=n;i++)for(int j=1;j<=m;j++)if(mp[i][j].x!=0)p[++cnt]=mp[i][j];
	int l=-1,r=2e6;
	while(l<r){
		int m=(l+r>>1)+1;
		check(m)?l=m:r=m-1;
	} cout<<l+1<<endl;
	return 0;
}
```



---

## 作者：小粉兔 (赞：3)

瓶颈在于处理每个点到最近的坏点的距离。

考虑每行分开考虑，每次$O(w_y)$处理一整行的答案。

拆式子可得一个一次函数，也就是直线。

求个半平面交就好了，这题的半平面交可以对偶到凸壳，单调栈维护即可。

注意预处理复杂度。有很多坑。

做完之后可以并查集，也可以二分答案。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MN = 1000005;
const int MS = 1005;

int C, R;
int Sx, Sy, Tx, Ty;
int N;

struct P{ int x, y; } A[MN];

inline bool Cmp(P i, P j) { return i.y == j.y ? i.x < j.x : i.y > j.y; }

void Init() {
	scanf("%d%d", &R, &C);
	scanf("%d%d%d%d", &Sx, &Sy, &Tx, &Ty);
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d%d", &A[i].x, &A[i].y);
	std::sort(&A[1], &A[N + 1], Cmp);
}

int P[MS];
int stk[MS], top;

int Id[MS][MS];

void Pre() {
	for (int i = 1; i <= N; ++i)
		if (i == 1 || A[i - 1].y != A[i].y)
			P[A[i].y] = i;
	for (int row = 1; row <= R; ++row) {
		top = 0;
		for (int i = 1; i <= C; ++i) if (P[i]) {
			if (P[i] < N && A[P[i] + 1].y == i && A[P[i] + 1].x - row < row - A[P[i]].x)
				++P[i];
			#define Calc(p1, p2) ((A[p1].x * (A[p1].x - 2 * row) - A[p2].x * (A[p2].x - 2 * row) + A[p1].y * A[p1].y - A[p2].y * A[p2].y) / (2 * (A[p1].y - A[p2].y)))
			while (top > 1 && Calc(stk[top], P[i]) <= Calc(stk[top - 1], stk[top]))
				--top;
			stk[++top] = P[i];
		}
		for (int i = 1; i <= top; ++i) {
			int lb = (i == 1 ? 1 : std::max(Calc(stk[i - 1], stk[i]) + 1, 1));
			int rb = (i == top ? C : std::min(Calc(stk[i], stk[i + 1]), C));
			if (lb > C || rb < 1 || lb > rb) continue;
			for (int j = lb; j <= rb; ++j)
				Id[row][j] = stk[i];
		}
	}
}

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0 ,1, 0, -1};

int qx[MN], qy[MN], l, r;
bool vis[MS][MS];

void BFS(int mid) {
	memset(vis, 0, sizeof vis);
	if ((A[Id[Sx][Sy]].x - Sx) * (A[Id[Sx][Sy]].x - Sx) + (A[Id[Sx][Sy]].y - Sy) * (A[Id[Sx][Sy]].y - Sy) <= mid)
		return;
	qx[l = r = 1] = Sx, qy[1] = Sy;
	vis[Sx][Sy] = 1;
	while (l <= r) {
		int X = qx[l], Y = qy[l++];
		for (int d = 0; d < 4; ++d) {
			int nX = X + dx[d], nY = Y + dy[d];
			if (nX < 1 || nX > R || nY < 1 || nY > C || vis[nX][nY]) continue;
			if ((A[Id[nX][nY]].x - nX) * (A[Id[nX][nY]].x - nX) + (A[Id[nX][nY]].y - nY) * (A[Id[nX][nY]].y - nY) <= mid)
				continue;
			qx[++r] = nX; qy[r] = nY;
			vis[nX][nY] = 1;
		}
	}
}

void Solve() {
	int lb = 0, rb = 2000000, mid, ans = -1;
	while (lb <= rb) {
		BFS(mid = (lb + rb) / 2);
		if (!vis[Tx][Ty]) ans = mid, rb = mid - 1;
		else lb = mid + 1;
	}
	printf("%d\n", ans);
}

int main() {
	Init();
	Pre();
	Solve();
	return 0;
}
```

---

## 作者：kouylan (赞：2)

~~我就说我怎么调了这么长时间，原来读入是先列后行啊……~~

很明显我们要计算出每个格点 $(i,j)$ 到坏点的最近距离，记为 $d(i,j)$，然后二分 bfs 求出答案即可。

所以难点是求 $d(i,j)$。

我们可以先求出在第 $i$ 行中格点 $(i,j)$ 与本行内的坏点的最近距离，记为 $ner(i,j)$，这只需要正反扫过每一行就行。然后我们就能把 $d(i,j)$ 的式子写出来

$$d(i,j)=\min\limits_{1\leq k\leq n}\{(i-k)^2+ner(k,j)^2\}$$

为了方便，我们去掉 $\min$，并拆括号

$$d(i,j)=i^2+(ner(k,j)^2+k^2)-2ik$$

我们记 $Y(k)=ner(k,j)^2+k^2$，$X(k)=k$

接下来，我们就要分 $k<i$ 和 $k>i$ 两种情况（当 $k=i$ 时 $d(i,j)=ner(i,j)^2$）。

当 $k<i$ 时，若 $k_1<k_2$ 且 $k_2$ 优于 $k_1$，则

$$i^2+Y(k_2)-2iX(k_2)\leq i^2+Y(k_1)-2iX(k_1)$$

$$Y(k_2)-Y(k_1)\leq 2i(X(k_2)-X(k_1))$$

$$\dfrac{Y(k_2)-Y(k_1)}{X(k_2)-X(k_1)}\leq 2i$$

然后用单调队列维护下凸包

当 $k>i$ 时，方法一样，只是最后一步一项时要变号。因为 $X(k)$ 在这种情况下是单调减的，所以依然是维护下凸包，只不过是从右往左。

下面是 AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 0x7f7f7f7f;
const int DX[] = {0,-1,0,1};
const int DY[] = {-1,0,1,0};

int n,m,sx,sy,tx,ty,ans,w,g[1005][1005];
int ll[1005][1005],rr[1005][1005],ner[1005][1005],d[1005][1005];
int hd=1,tl,dq[1005];
bool vis[1005][1005];

int y_(int k,int j)
{
	return ner[k][j]*ner[k][j]+k*k;
}

double k_(int k1,int k2,int j)
{
	return 1.0*(y_(k2,j)-y_(k1,j))/(k2-k1);
}

bool bfs(int lim)
{
	queue<pair<int,int> > q;
	memset(vis,0,sizeof(vis));
	vis[sx][sy] = 1, q.push(make_pair(sx,sy));
	while(!q.empty())
	{
		int x=q.front().first,y=q.front().second;
		q.pop();
		if(vis[tx][ty])
			return 1;
		for(int k=0;k<4;k++)
		{
			int xx=x+DX[k],yy=y+DY[k];
			if(xx>=1 && xx<=n && yy>=1 && yy<=m &&  d[xx][yy]>=lim && !vis[xx][yy])
				vis[xx][yy] = 1, q.push(make_pair(xx,yy));
		}
	}
	return vis[tx][ty];
}

signed main()
{
	cin>>m>>n>>sy>>sx>>ty>>tx>>w;
	for(int i=1,x,y;i<=w&&cin>>y>>x;i++)
		g[x][y] = 1;
	for(int j=0;j<=m+1;j++)
		ner[0][j] = ner[n+1][j] = INF;
	for(int i=1;i<=n;i++)
	{
		ll[i][0] = -INF, rr[i][m+1] = INF;
		for(int j=1;j<=m;j++)
			ll[i][j] = (g[i][j] ? j : ll[i][j-1]);
		for(int j=m;j>=1;j--)
			rr[i][j] = (g[i][j] ? j : rr[i][j+1]);
		for(int j=1;j<=m;j++)
			ner[i][j] = min(j-ll[i][j],rr[i][j]-j);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			d[i][j] = INF;
	for(int j=1;j<=m;j++)
	{
		for(int i=1;i<=n;i++)
			d[i][j] = ner[i][j]*ner[i][j];
		hd = 1, tl = 0, memset(dq,0,sizeof(dq));
		dq[++tl] = 0;
		for(int i=1;i<=n;i++)
		{
			while(hd<tl && k_(dq[hd],dq[hd+1],j)<2.0*i)
				hd++;
			int k=dq[hd];
			d[i][j] = min(d[i][j],(i-k)*(i-k)+ner[k][j]*ner[k][j]);
			while(hd<tl && k_(dq[tl],i,j)<=k_(dq[tl-1],dq[tl],j))
				tl--;
			dq[++tl] = i;
		}
		hd = 1, tl = 0, memset(dq,0,sizeof(dq));
		dq[++tl] = n+1;
		for(int i=n;i>=1;i--)
		{
			while(hd<tl && k_(dq[hd],dq[hd+1],j)>2.0*i)
				hd++;
			int k=dq[hd];
			d[i][j] = min(d[i][j],(i-k)*(i-k)+ner[k][j]*ner[k][j]);
			while(hd<tl && k_(dq[tl],i,j)>=k_(dq[tl-1],dq[tl],j))
				tl--;
			dq[++tl] = i;
		}
	}
	int l=0,r=d[sx][sy];
	while(l<=r)
	{
		int mid=l+r>>1;
		if(bfs(mid))
			ans = mid, l = mid+1;
		else
			r = mid-1;
	}
	cout<<ans<<endl;
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：Cry_For_theMoon (赞：2)

[传送门](https://www.luogu.com.cn/problem/P3438)

没想到竟然用这个题当斜率优化入门题（）

如果我们可以求出每个点到给定点的最短欧几里得距离，然后就可以二分+bfs check. 这是显然的。问题在于如何求出每个点到给定点的最短欧几里得距离。两部分都是 $O(nm)$ 级别的。感觉带 $log$ 都很危险。

斜率优化的部分好像都不是很清晰，补充一下吧：

显然我们对于一个 $x,y$ 要求
$$
dis_{x,y}=\min\{(x_2-x)^2+(y_2-y)^2\}
$$
其中 $(x_2,y_2)$ 是一个给定的点。注意到要求的是距离的平方，不然会很麻烦有小数。

把 $\min$ 化简：
$$
dis_{x,y}=\min\{x_2^2-x^2+y_2^2-y^2-2xx_2-2yy_2\}
$$
这个式子里有些项与 $(x,y)$ 和 $(x_2,y_2)$ 都有关，所以可以排除大多数优化。一个可能的候选是斜率优化。

拆掉 $\min$：
$$
dis_{x,y}=x_2^2-x^2+y_2^2-y^2-2xx_2-2yy_2
$$
改写成：
$$
x_2^2+y_2^2-2xx_2=2yy_2 + (dis_{x,y}-x^2-y^2)
$$
注意到如果我们先固定 $x$ ，然后计算所有的 $y$，那么对于 $(x_2,y_2)$ 来说 $(-2xx_2)$ 是个定值。具体地：
$$
y=x_2^2+y_2^2-2xx_2 ,k=2y,x=y_2,b=(dis_{x,y}-x^2-y^2)
$$
最小化的是截距，其它三个要么只和 $(x_2,y_2)$ 有关要么只和 $(x,y)$ 有关。因此我们就可以斜率优化了。

但是注意，我们要 $n$ 次斜优，每次有 $nm$ 级别个点，复杂度是立方级别的。

但是不难发现在 $x$ 固定的情况下对于每个 $y$ 只会有一个 $(k,y)$ 会对答案造成影响。比如说如果规定 $x=3$，显然 $(2,2)$ 一定比 $(1,2)$ 优秀。每次我们只需要 $O(m)$ 级别个点。所以复杂度变成 $O(nm)$.

至于每次处理候选点。$\log$ 做法应该是找前驱后继。但是我们注意到对于一个 $y$，其有效的 $x$ 坐标 $k$ 在 $x \rightarrow x+1$ 的时候要么不变，要么后移一位。所以每次可以 $O(m)$ 找到候选点。

因此预处理复杂度为 $O(nm) $总复杂度为 $O(nm \log (n^2m^2))$.

```C++
//POI,2006
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1010,next_x[4]={1,0,-1,0},next_y[4]={0,1,0,-1};
int n,m,k;
ll dis[MAXN][MAXN],top;
struct Point{
	ll x,y;
	bool operator<(const Point& p2)const{return x<p2.x;}
	bool operator==(const Point& p2)const{return x==p2.x && y==p2.y;}
}s,e,p[MAXN*MAXN],st[MAXN],st2[MAXN]; //st2维护点 
vector<ll>V[MAXN];//V[i]维护y=i的所有x值(x单调递增)
int now[MAXN]; //now为候选集合 
int vis[MAXN][MAXN];
queue<Point>q;
il int valid(const Point& p){return p.x>=1 && p.x<=n && p.y>=1 && p.y<=m;}
void ins(ll x,ll y,ll i,ll j){
	Point k=(Point){x,y};
	while(top>=2){
		Point i=st[top-1],j=st[top]; //i-j 斜率应该小于 j-k 斜率
		if((j.y-i.y)*(k.x-j.x)>=(k.y-j.y)*(j.x-i.x))top--;
		else break; 
		
	}
	st[++top]=k;st2[top]=(Point){i,j};
} 
Point query(ll val){
	//找到最后一个(i-1 - i)斜率小于val的i 
	int ret=1,L=2,R=top;
	while(L<=R){
		int mid=(L+R)>>1;
		if((st[mid].y-st[mid-1].y)<(st[mid].x-st[mid-1].x)*val){
			ret=mid;L=mid+1;
		}else{
			R=mid-1;
		}
	}
	return st2[ret];
}
int check(ll mid){
	memset(vis,0,sizeof vis);
	if(dis[s.x][s.y]<mid)return 0;
	while(q.size())q.pop();
	q.push(s);
	while(q.size()){
		Point now=q.front();q.pop();
		rep(k,0,3){
			Point to=(Point){now.x+next_x[k],now.y+next_y[k]};
			if(!valid(to) || vis[to.x][to.y])continue;
			if(dis[to.x][to.y]<mid)continue;
			if(to==e)return 1;
			vis[to.x][to.y]=1;
			q.push(to);
		}
	}
	return 0;
} 
void pre(){
	//预处理dis
	//每一行分开来处理
	rep(i,1,m)now[i]=1;
	rep(i,1,n){
		top=0;
		//不超过m个对答案有贡献的点 
		rep(j,1,m){
			if(now[j]>V[j].size())continue; 
			if(now[j]+1<=V[j].size()){
				if(abs(V[j][now[j]-1]-i)>abs(V[j][now[j]]-i)){
					now[j]++; //更新 
				}
			}
		}
		//单调栈维护斜率递增
		rep(j,1,m){
			if(now[j]>V[j].size())continue;
			ll x=j,y=V[j][now[j]-1]*V[j][now[j]-1]+j*j-2*i*V[j][now[j]-1];
			//加入当前决策点(x,y)
			ins(x,y,V[j][now[j]-1],j);
		} 
		rep(j,1,m){
			//在单调栈上二分斜率2j
			Point p=query(2*j);
			dis[i][j]=(p.x-i)*(p.x-i)+(p.y-j)*(p.y-j);
		}
	} 
}
int main(){
	scanf("%d%d",&m,&n);
	scanf("%lld%lld%lld%lld",&(s.y),&(s.x),&(e.y),&(e.x));
	scanf("%d",&k);
	rep(i,1,k){
		scanf("%lld%lld",&(p[i].y),&(p[i].x));
	}
	sort(p+1,p+1+k);
	rep(i,1,k){V[p[i].y].pb(p[i].x);}
	pre();
	if(s==e)return printf("%lld",dis[s.x][s.y]),0;
	//二分+bfs
	ll L=0,R=dis[s.x][s.y],ret=0;
	while(L<=R){
		ll mid=(L+R)>>1;
		if(check(mid)){
			ret=mid;L=mid+1;
		}else{
			R=mid-1;
		}
	} 
	printf("%lld",ret);
	return 0;
}
```



---

## 作者：xtx1092515503 (赞：1)

一种复杂度最优可以做到 $O(nm\alpha)$ 的做法。

------

一个显然的想法就是求出每个节点到达最近坏点的距离。假如求出之后，显然就可以通过二分来在 $nm\log$ 的时间内求解。

但是，为了压缩复杂度，一个更好的方式是用桶排对所有点按距离排序，然后从大到小依次加入某个距离的所有点，这样如果起点终点在何时联通，则显然此时最后一个被加入的点的距离即是答案。使用冰茶姬维护连通性，即可做到 $nm\alpha$。

（虽然，在实际代码中我使用的还是二分法，因为这种方法码量小）

------

现在考虑如何求解距离。

两点间距离等于横向距离+纵向距离。因此，我们如果设 $f_{i,j}$ 表示关于点 $(i,j)$，$i$ 与之相同的所有坏点中距离其最近的点的距离的平方——显然求出这个数组是简单的。这样之后，我们就可以对于每个 $j$ 分开考虑了，因为显然如果某个 $(i,j)$ 的最近距离要从某个 $i'$ 这一行转移过来，则肯定要选取距离 $(i',j)$ 最近的点作为目标，而显然这一目标就是 $f_{i',j}$。

于是我们现在考虑固定一个 $j$，这样就可以将两维的 $f_{i.j}$ 暂记为一维的 $f_i$。同时，我们设 $g_{i,j}$ 表示位置 $(i,j)$ 的答案，并也将其暂记为一维。

现在考虑转移。则，$g_i=\min\limits_{i'} f_{i'}+(i-i')^2$。

这是一个经典的斜率优化式。具体而言，我们可以先将所有 $i'$ 关于 $i$ 拆做 $<i$ 和 $>i$ 的两半。然后，再将式子写作

$$g_i=\min\limits_{i'<i} f_{i'}+i^2-2ii'+i'^2$$

看着没啥感觉，我们来考虑设 $j<k<i$，这样再列出 $j$ 劣于 $k$ 时的式子：

$$f_j+i^2-2ij+j^2>f_k+i^2-2ik+k^2$$

考虑消去相同的项，并令 $F_i=f_i+j^2$。

$$F_j-2ij>F_k-2ik$$

移项，即得

$$\dfrac{F_j-F_k}{j-k}<2i$$

右侧 $2i$ 显然随着 $i$ 增加而增加，因此就可以斜率优化。求出单个 $g_i$ 的复杂度做到 $O(n)$。

因此求解全部 $g$ 的复杂度就是 $O(nm)$。

------

总复杂度 $O(nm\alpha)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,Q,sx,sy,tx,ty,dsu[1001000];
int f[1010][1010],g[1010][1010];
int find(int x){return dsu[x]==x?x:dsu[x]=find(dsu[x]);}
void merge(int x,int y){x=find(x),y=find(y);if(x!=y)dsu[x]=y;}
bool che(int ip){
	for(int i=1;i<=n*m;i++)dsu[i]=i;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		if(i+1<=n&&g[i][j]>=ip&&g[i+1][j]>=ip)merge((i-1)*m+j,i*m+j);
		if(j+1<=m&&g[i][j]>=ip&&g[i][j+1]>=ip)merge((i-1)*m+j,(i-1)*m+j+1);
	}
	return find((sx-1)*m+sy)==find((tx-1)*m+ty);
}
bool occ[1010][1010];
int q[1010],l,r;
void calc(int j){
	l=1,r=0;
	for(int i=1;i<=n;i++){
		f[i][j]+=i*i;
		while(l+1<=r&&f[q[l]][j]-f[q[l+1]][j]>=2*i*(q[l]-q[l+1]))l++;
		if(l<=r)g[i][j]=min(g[i][j],f[q[l]][j]+i*i-2*i*q[l]);
		while(l<=r-1&&1ll*(f[q[r-1]][j]-f[q[r]][j])*(q[r]-i)>=1ll*(f[q[r]][j]-f[i][j])*(q[r-1]-q[r]))r--;
		q[++r]=i;
	}
}
int main(){
	scanf("%d%d%d%d%d%d%d",&n,&m,&sx,&sy,&tx,&ty,&Q),memset(f,0x3f,sizeof(f)),memset(g,0x3f,sizeof(g));
	for(int i=1,x,y;i<=Q;i++)scanf("%d%d",&x,&y),occ[x][y]=true;
	for(int i=1;i<=n;i++){
		for(int j=1,k=-1;j<=m;j++){
			if(occ[i][j])k=j;
			if(k!=-1)f[i][j]=min(f[i][j],(j-k)*(j-k));
		}
		for(int j=m,k=-1;j;j--){
			if(occ[i][j])k=j;
			if(k!=-1)f[i][j]=min(f[i][j],(j-k)*(j-k));
		}
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)g[i][j]=f[i][j];
	for(int j=1;j<=m;j++){
		calc(j);
		for(int i=1;i<=n;i++)f[i][j]-=i*i;
		for(int l=1,r=n;l<r;l++,r--)swap(f[l][j],f[r][j]),swap(g[l][j],g[r][j]);
		calc(j);
		for(int l=1,r=n;l<r;l++,r--)swap(g[l][j],g[r][j]);
	}
	int l=0,r=min(g[sx][sy],g[tx][ty]);
	while(l<r){
		int mid=(l+r+1)>>1;
		if(che(mid))l=mid;
		else r=mid-1;
	}
	printf("%d\n",l);
	return 0;
}
```



---

## 作者：糪眾脦颰罷 (赞：1)

## 斜率优化+二分+BFS+单调栈
拿到这个题目，第一个想法就是暴力把所有点离其最近的scarefrog的距离给处理出来。

但是，看一下数据范围是1000×1000的，这样铁T。

所以，预处理需要是On的，这就需要斜率优化和单调栈了。

But，如何斜率优化呢？

对于一个点(x,y)，若位于(xa,ya)的scarefrog比位于(xb,yb)的更近，那么就有：

$
(x_a-x)^2+(y_a-y)^2<(x_b-x)^2+(y_b-y)^2
$

去括号移项得:

$
\frac{x_a^2-x_b^2+2x(x_b-x_a)}{y_a-y_b}+y_a+y_b<2y
$

那么对于某个固定的x，我们就可以**从小到大**枚举y，这样**y就是单调递增的**。同时，我们也开个单调栈维护不等式左边的一大串式子，**注意这维护的是一个有关两点的表达式**。

那么，怎么维护单调栈的单调性呢？

设之前单调栈里面有一个式子，是关于点A和B的（定义左边式子的运算用K表示，且令K（A,B）<2y则表示B比A更优），这次我们加入一个点C，那么我们讨论一下：

若
$K(A,B)<K(B,C)$:

由于y是调递增的，故最优解可能出现在A（满足$K(A,B)>2y$和$K(B,C)>2y$）或者B(满足$K(A,B)<2y$和$K(B,C)>2y$)或者C(满足$K(A,B)<2y$和$K(B,C)<2y$)上，**因此需要把K(B,C)加入到单调栈中**

若$K(A,B)>K(B,C)$:

若最优解出现在B点，那么：

$
K(A,B)<2y_1
$①

$
K(B,C)>2y_2
$②

$
K(A,B)>K(B,C)
$③

$
y_1<y_2
$④

根据①、②和④式得：

$
K(A,B)<2y_1<2y_2<K(B,C)
$

那么：

$
K(A,B)<K(B,C)
$

显然这与③式冲突，那么B点肯定不是最优解，类似的，我们也可以推出A点和C点有可能是。**故该情况下把B点弹出**，再将A点和C点结合。

在最后计算答案时，在单调栈中找到下标最大的stk[i]满足$K(stk[i-1],stk[i])<2y$的点，此时stk[i]刚好是对应y的最优解（此时$K(stk[1],stk[2])<2y$且$K(stk[2],stk[3])<2y$...$K(stk[i-1],stk[i])<2y$）

此外，预处理时还需要注意时间，尽可能多运用单调性去处理。

代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,K,H[1000010],Max[1000010],bel[1000010],dis[1010][1010];
struct node{
	int x,y;
}st,ed,frog[1000010],P[1000010];
double stk[1000010];
int mx[]={1,0,-1,0},my[]={0,1,0,-1};
bool cmp(node A,node B){
	if(A.y!=B.y)return A.y<B.y;
	else return A.x<B.x;
}
double calc(int xa,int ya,int xb,int yb,int x){
	double mum=xa*xa*1.0-xb*xb*1.0+2.0*x*(xb-xa);
	double son=(ya-yb)*1.0;
	double ans;
	ans=mum*1.0/son+(ya+yb)*1.0;
	return ans;
}
void pre(){
	sort(frog+1,frog+1+K,cmp);
	for(int i=1;i<=K;){
		int pos=frog[i].y;
		H[pos]=i;
		while(frog[i+1].y==pos)i++;
		Max[pos]=i;
		i++;
	}
	for(int i=1;i<=n;i++){
		int tot=0,cnt=0;
		P[0]=node{1000,-1000};
		for(int j=1;j<=m;j++){
			if(!Max[j])continue;
			int minn=abs(frog[H[j]].x-i);
			while(H[j]+1<=Max[j]&&abs(frog[H[j]+1].x-i)<minn)H[j]++,minn=abs(frog[H[j]].x-i);
			P[++tot]=frog[H[j]];
		}
		for(int j=1;j<=tot;j++){
			double res=calc(P[j].x,P[j].y,P[bel[cnt]].x,P[bel[cnt]].y,i);
			while(cnt>=1&&res<=stk[cnt])cnt--,res=calc(P[j].x,P[j].y,P[bel[cnt]].x,P[bel[cnt]].y,i);
			stk[++cnt]=res,bel[cnt]=j;
		}
		for(int j=1,l=1;j<=m;j++){
			while(stk[l+1]<j*2.0&&l+1<=cnt)l++;
			dis[i][j]=(i-P[bel[l]].x)*(i-P[bel[l]].x)+(j-P[bel[l]].y)*(j-P[bel[l]].y);
		}
	}
}
bool BFS(int len){
	bool vis[1010][1010];
	memset(vis,0,sizeof(vis));
	queue<node> Q;
	while(!Q.empty())Q.pop();
	if(dis[st.x][st.y]<len)return false;
	Q.push(st);
	while(!Q.empty()){
		node now=Q.front();
		Q.pop();
		if(now.x==ed.x&&now.y==ed.y)return true;
		for(int k=0;k<=3;k++){
			int nex=now.x+mx[k],ney=now.y+my[k];
			if(nex<1||nex>n||ney<1||ney>m)continue;
			if(dis[nex][ney]<len)continue;
			if(vis[nex][ney])continue;
			Q.push(node{nex,ney});
			vis[nex][ney]=true;
		}
	}
	return false;
}
int main(){
	scanf("%d %d",&n,&m);
	scanf("%d %d %d %d",&st.x,&st.y,&ed.x,&ed.y);
	scanf("%d",&K);
	for(int i=1;i<=K;i++)scanf("%d %d",&frog[i].x,&frog[i].y);
	pre();
	int l=0,r=1e9+7;
	while(l<=r){
		int mid=(l+r)>>1;
		if(BFS(mid))l=mid+1;
		else r=mid-1;
	}
	cout<<r;
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

貌似没有人提到决策单调性？

考虑求出每个点到最近的关键点的距离 $dis_{i,j}$。求出 $dis$ 数组之后，我们就可以按照 $dis$ 倒序加入，用并查集维护连通性，就可以求解出答案。

---------

不妨求出所有 $(i,j)$ 左侧的点到他的最小距离（这里的坐标用的是平面直角坐标系）。

按照列的顺序扫描。对于当前行来说，它有若干个可能的决策点 $(i_1,j_1)$、$(i_2,j_2)$、$\cdots$。不妨设 $i_1 < i_2 < \cdots$（如果有 $i$ 相同的节点，保留 $j$ 和当前行最接近的那个）

我们发现，这些点之间显然具有决策单调性。

因此可以二分队列实现。不过发现我们需要二分的结构实际上是两个点垂直平分线和一条水平线的交点，可以 $O(1)$ 计算。

那么总的复杂度就是 $O(nm)$。（把并查集当做 $O(1)$。）

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(register int i=(a);i<=(b);++i)
#define roff(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
const int MAXN=1000+10;
int n,m,q,ans[MAXN][MAXN];
bool a[MAXN][MAXN];
struct INFO {int l,r,x,y;}st[MAXN][MAXN];
int hd[MAXN],tl[MAXN];
#define max(a,b) ((a)>(b)?a:b)
#define min(a,b) ((a)<(b)?a:b)
inline int find_better(const int lstx,const int lsty,const int nwx,const int nwy,const int y) {
    if(abs(y-nwy)<=abs(y-lsty)) return nwx;
    int fz=nwx*nwx+(nwy-y)*(nwy-y)-lstx*lstx-(lsty-y)*(lsty-y);
    int fm=(nwx-lstx)<<1,xmn=fz/fm+1;
    xmn=max((int)xmn,nwx);
    xmn=min(xmn,m+1);
    return xmn;
}
inline void update(const int y,const int nwx,const int nwy) {
    if(hd[y]>tl[y]) return st[y][++tl[y]]={nwx,m,nwx,nwy},void();
    int lst=m+1;
    while(hd[y]<=tl[y]) {
        int nxt=find_better(st[y][tl[y]].x,st[y][tl[y]].y,nwx,nwy,y);
        if(nxt>st[y][tl[y]].r) break ;
        else if(nxt<=st[y][tl[y]].l) lst=st[y][tl[y]].l,tl[y]--; 
        else {lst=nxt,st[y][tl[y]].r=nxt-1;break ;}
    }
    if(lst!=m+1) st[y][++tl[y]]={lst,m,nwx,nwy};
    return ;
}
inline void flip(void) {ffor(i,1,n) ffor(j,1,m) if(m-j+1>=j) swap(a[i][j],a[i][m-j+1]);return ;}
inline int get(void) {
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    return ch-'0';  
}
int sx,sy,tx,ty,lst[MAXN],nxt[MAXN];
inline int dis(const int Ax,const int Ay,const int Bx,const int By) {
    return (Ax-Bx)*(Ax-Bx)+(Ay-By)*(Ay-By);
}
void calc(int op) {
    ffor(i,1,n) hd[i]=1,tl[i]=0;
    ffor(j,1,m) {
        int cnt=0;
        ffor(i,1,n) cnt|=a[i][j];
        if(cnt) {
            lst[0]=nxt[n+1]=0;
            ffor(i,1,n) if(a[i][j]) lst[i]=i;
            else lst[i]=lst[i-1];
            roff(i,n,1) if(a[i][j]) nxt[i]=i;
            else nxt[i]=nxt[i+1];
            ffor(i,1,n) {
                int near=n+n+n+n;
                if(lst[i]!=0&&abs(lst[i]-i)<abs(near-i)) near=lst[i];
                if(nxt[i]!=0&&abs(nxt[i]-i)<abs(near-i)) near=nxt[i];
                update(i,j,near);
            }
        }
        ffor(i,1,n) {
            while(hd[i]<=tl[i]&&st[i][hd[i]].r<j) hd[i]++;
            if(hd[i]<=tl[i]) {
				int val=dis(st[i][hd[i]].x,st[i][hd[i]].y,j,i);
				if(!op) ans[i][j]=min(ans[i][j],val);
				else ans[i][m-j+1]=min(ans[i][m-j+1],val);
			}
        }
    }
    return ;
}
int id[MAXN][MAXN],fa[MAXN*MAXN];
int find(int k) {return (fa[k]==k)?k:(fa[k]=find(fa[k]));}
vector<int> upd[MAXN*MAXN*2];
const int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
void merge(int u,int v) {
	return fa[find(v)]=find(u),void();	
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>sx>>sy>>tx>>ty>>q;
	ffor(i,1,q) {int x,y;cin>>x>>y,a[x][y]=1;}
	memset(ans,0x3f,sizeof(ans));
	calc(0),flip(),calc(1);
	ffor(i,1,n) ffor(j,1,m) id[i][j]=(i-1)*m+j;
	ffor(i,1,n*m) fa[i]=i;
	ffor(i,1,n) ffor(j,1,m) upd[ans[i][j]].push_back(id[i][j]);
	if(sx==tx&&sy==ty) return cout<<ans[sx][sy],0;
	roff(i,2000000,0) {
		for(auto tmp:upd[i]) {
			int x=(tmp-1)/m+1,y=tmp-(x-1)*m;
			ffor(d,0,3) {
				if(x+dx[d]<1||x+dx[d]>n||y+dy[d]<1||y+dy[d]>m) continue ;
				int nx=x+dx[d],ny=y+dy[d];
				if(ans[nx][ny]>=i) merge(id[x][y],id[nx][ny]);		
			}
		}
		if(find(id[sx][sy])==find(id[tx][ty])) return cout<<i,0;
	}
    return 0;
}
```

---

## 作者：tzc_wk (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/P3438)

首先一眼二分答案，我们假设距离 $(i,j)$ 最近的 scarefrog 离它的距离为 $mn_{i,j}$，那么当我们二分到 $mid$ 时我们显然只能经过 $mn_{i,j}\ge mid$ 的点，如果我们已经知道了 $mn_{i,j}$，那么检验 $mid$ 是否可行就是一遍 BFS 能搞定的事，于是我们的目标就是求出 $mn_{i,j}$ 即可。

故下面就有两种做法，一种是我的乱搞做法，一种是正经的做法。

---

> 乱搞做法

这就是某个奇怪的人自己~~发明出来的~~某个奇怪的基于某个奇怪的假做法的乱搞做法（

显然对于某个点 $(x,y)$ 而言，对它产生贡献的点可能在它的左上方、右上方、左下方、右下方（对于与 $(x,y)$ 在同一行或同一列的点，我们显然可以把它简单归约到 $(x,y)$ 的某一侧），显然四种情况是类似的，我们只需解决一种情况即可求出解决另外几种。考虑怎样求出左上角的答案，那么对于两个 scarefrog 所在的点 $(x_1,y_1),(x_2,y_2)$，如果 $x_1<x_2,y_1<y_2$ 且 $(x_1,y_1),(x_2,y_2)$ 都在 $(x,y)$ 的左上角，那 $(x_1,y_1)$ 显然是不优的，因此我们维护一个队列满足随着 $x$ 的增大，$y$ 单调递减，表示决策点的集合。其次我们还可以发现，对于一个点 $P(x,y)$ 和两个决策点 $A(x_1,y_1),B(x_2,y_2)$，如果 $PA>PB$，且 $x_1>x_2$，那么如果我们将 $P$ 再往右多移动几格，到 $P(x,y+k)$，那么感性理解一下，$PA$ 增加的长度 $\Delta PA$ 大于 $PB$ 增加的长度 $\Delta PB$，因此还有 $PA>PB$，此时 $A$ 点就是没有用的了，因此我们考虑维护一个**单调队列**，随着 $x$ 的增大，$y$ 在不断减小，同时该点到点 $P$ 的距离也在不断减小，那么我们只需取出队首的元素更新答案即可。

这个做法看起来非常正确，但非常抱歉，它是有漏洞的，因为当你将 $P$ 从 $(x,y)$ 移至 $(x,y+1)$ 时，队列中的元素并不一定还满足到 $P$ 点的距离单调。

不过这个做法在随机数据下表现非常优秀，它奇迹般地只 WA 了 $3$ 个点，取得了 $88$ 分的好成绩，于是我就灵机一动，将“取对首元素更新答案”改为“取队列前 $30$ 个元素更新答案”，然后……它！过！了！

时间复杂度 $\mathcal O(30nm+nm\log nm)$

~~感觉这个做法非常不靠谱，欢迎鸽鸽们来叉~~

```cpp
const int MAXN=1000;
const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
int dis(int x1,int y1,int x2,int y2){
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
int n,wx,wy,sx,sy,ex,ey;
bool is[MAXN+5][MAXN+5];
int pos[MAXN+5],mn[MAXN+5][MAXN+5];
bool vis[MAXN+5][MAXN+5];
bool check(int lim){
	if(mn[sx][sy]<lim||mn[ex][ey]<lim) return 0;
	memset(vis,0,sizeof(vis));queue<pii> q;
	q.push(mp(sx,sy));vis[sx][sy]=1;
	while(!q.empty()){
		pii p=q.front();q.pop();int x=p.fi,y=p.se;
		for(int d=0;d<4;d++){
			int nx=x+dx[d],ny=y+dy[d];
			if(nx<1||nx>wx||ny<1||ny>wy) continue;
			if(mn[nx][ny]<lim||vis[nx][ny]) continue;
			vis[nx][ny]=1;q.push(mp(nx,ny));
		}
	} return vis[ex][ey];
}
int main(){
	scanf("%d%d%d%d%d%d%d",&wx,&wy,&sx,&sy,&ex,&ey,&n);
	for(int i=1,x,y;i<=n;i++) scanf("%d%d",&x,&y),is[x][y]=1;
	memset(mn,63,sizeof(mn));
	memset(pos,0,sizeof(pos));
	for(int i=1;i<=wx;i++){
		static pii q[MAXN+5];int hd=1,tl=0;
		for(int j=1;j<=wy;j++){
			if(is[i][j]) pos[j]=i;
			if(pos[j]){
				while(hd<=tl&&dis(i,j,pos[j],j)<=dis(i,j,q[tl].fi,q[tl].se)) --tl;
				q[++tl]=mp(pos[j],j);
			} while(hd<tl&&dis(i,j,q[hd].fi,q[hd].se)>=dis(i,j,q[hd+1].fi,q[hd+1].se)) ++hd;
			for(int l=hd;l<=min(hd+30,tl);l++)
				chkmin(mn[i][j],dis(i,j,q[l].fi,q[l].se));
		}
	}
	memset(pos,0,sizeof(pos));
	for(int i=1;i<=wx;i++){
		static pii q[MAXN+5];int hd=1,tl=0;
		for(int j=wy;j;j--){
			if(is[i][j]) pos[j]=i;
			if(pos[j]){
				while(hd<=tl&&dis(i,j,pos[j],j)<=dis(i,j,q[tl].fi,q[tl].se)) --tl;
				q[++tl]=mp(pos[j],j);
			} while(hd<tl&&dis(i,j,q[hd].fi,q[hd].se)>=dis(i,j,q[hd+1].fi,q[hd+1].se)) ++hd;
			for(int l=hd;l<=min(hd+30,tl);l++)
				chkmin(mn[i][j],dis(i,j,q[l].fi,q[l].se));
		}
	}
	memset(pos,0,sizeof(pos));
	for(int i=wx;i;i--){
		static pii q[MAXN+5];int hd=1,tl=0;
		for(int j=1;j<=wy;j++){
			if(is[i][j]) pos[j]=i;
			if(pos[j]){
				while(hd<=tl&&dis(i,j,pos[j],j)<=dis(i,j,q[tl].fi,q[tl].se)) --tl;
				q[++tl]=mp(pos[j],j);
			} while(hd<tl&&dis(i,j,q[hd].fi,q[hd].se)>=dis(i,j,q[hd+1].fi,q[hd+1].se)) ++hd;
			for(int l=hd;l<=min(hd+30,tl);l++)
				chkmin(mn[i][j],dis(i,j,q[l].fi,q[l].se));
		}
	}
	memset(pos,0,sizeof(pos));
	for(int i=wx;i;i--){
		static pii q[MAXN+5];int hd=1,tl=0;
		for(int j=wy;j;j--){
			if(is[i][j]) pos[j]=i;
			if(pos[j]){
				while(hd<=tl&&dis(i,j,pos[j],j)<=dis(i,j,q[tl].fi,q[tl].se)) --tl;
				q[++tl]=mp(pos[j],j);
			} while(hd<tl&&dis(i,j,q[hd].fi,q[hd].se)>=dis(i,j,q[hd+1].fi,q[hd+1].se)) ++hd;
			for(int l=hd;l<=min(hd+30,tl);l++)
				chkmin(mn[i][j],dis(i,j,q[l].fi,q[l].se));
		}
	} int l=0,r=2e6,p=0;
//	for(int i=1;i<=wx;i++) for(int j=1;j<=wy;j++) printf("%d%c",mn[i][j]," \n"[j==wy]);
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)) p=mid,l=mid+1;
		else r=mid-1;
	} printf("%d\n",p);
	return 0;
}
```

> 正经做法

还是考虑怎样求 $mn_{i,j}$，我们记 $f_{i,j}$ 表示与 $(i,j)$ 在同一列的点中，与 $(i,j)$ 距离最近的坏点的距离——那么显然 $f_{i,j}$ 可以通过扫一遍整个 `matrix` 求出，时间复杂度 $nm$。

接下来考虑知道了 $f_{i,j}$ 怎样求 $mn$，那么我们就枚举离 $(i,j)$ 最近的坏点所在的列 $k$，可得转移方程 $mn_{i,j}=\min\limits_{k}\{f_{i,k}^2+(j-k)^2\}$，稍微变形一下即可得到 $mn_{i,j}=j^2+\min\limits_{k}\{-2jk+f_{i,k}^2+k^2\}$，这显然就是一个个一次函数，如果我们记 $l_k:y=-2kx+f_{i,k}^2+k^2$，那么求 $mn_{i,j}$ 只需求出 $\max\{l_k(j)\}$，可以用凸包/斜率优化/李超线段树维护，本人写的是李超线段树的求法，~~因为不容易爆精度~~。

```cpp
const int MAXN=1000;
const int INF=0x3f3f3f3f;
const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
int wx,wy,sx,sy,ex,ey,n;
bool is[MAXN+5][MAXN+5];
int mn[MAXN+5][MAXN+5],f[MAXN+5][MAXN+5];
struct line{
	int k,b;
	line(int _k=0,int _b=INF):k(_k),b(_b){}
	int get(int x){return x*k+b;}
};
struct node{int l,r;line v;} s[MAXN*4+5];
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;s[k].v=line();if(l==r) return;
	int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
}
void modify(int k,line v){
	int l=s[k].l,r=s[k].r,mid=l+r>>1;
	int l1=s[k].v.get(l),r1=s[k].v.get(r),m1=s[k].v.get(mid);
	int l2=v.get(l),r2=v.get(r),m2=v.get(mid);
	if(l2>=l1&&r2>=r1) return;
	if(l1>=l2&&r1>=r2) return s[k].v=v,void();
	if(m2<=m1){
		if(l2<=l1) modify(k<<1|1,s[k].v),s[k].v=v;
		else modify(k<<1,s[k].v),s[k].v=v;
	} else {
		if(l2<=l1) modify(k<<1,v);
		else modify(k<<1|1,v);
	}
}
int query(int k,int x){
	if(s[k].l==s[k].r) return s[k].v.get(x);int mid=s[k].l+s[k].r>>1;
	return min(((x<=mid)?query(k<<1,x):query(k<<1|1,x)),s[k].v.get(x));
}
bool vis[MAXN+5][MAXN+5];
bool check(int lim){
	if(mn[sx][sy]<lim||mn[ex][ey]<lim) return 0;
	memset(vis,0,sizeof(vis));queue<pii> q;
	q.push(mp(sx,sy));vis[sx][sy]=1;
	while(!q.empty()){
		pii p=q.front();q.pop();int x=p.fi,y=p.se;
		for(int d=0;d<4;d++){
			int nx=x+dx[d],ny=y+dy[d];
			if(nx<1||nx>wx||ny<1||ny>wy) continue;
			if(mn[nx][ny]<lim||vis[nx][ny]) continue;
			vis[nx][ny]=1;q.push(mp(nx,ny));
		}
	} return vis[ex][ey];
}
int main(){
	scanf("%d%d%d%d%d%d%d",&wx,&wy,&sx,&sy,&ex,&ey,&n);
	for(int i=1,x,y;i<=n;i++) scanf("%d%d",&x,&y),is[x][y]=1;
	memset(f,63,sizeof(f));
	for(int j=1;j<=wy;j++){
		int pre=-INF;
		for(int i=1;i<=wx;i++){
			if(is[i][j]) pre=i;
			chkmin(f[i][j],i-pre);
		} pre=INF;
		for(int i=wx;i;i--){
			if(is[i][j]) pre=i;
			chkmin(f[i][j],pre-i);
		}
	}
	for(int i=1;i<=wx;i++){
		build(1,1,wy);
		for(int j=1;j<=wy;j++) if(f[i][j]<1e9)
			modify(1,line(-2*j,j*j+f[i][j]*f[i][j]));
		for(int j=1;j<=wy;j++) mn[i][j]=query(1,j)+j*j;
	} int l=0,r=2e6,p=0;
//	for(int i=1;i<=wx;i++) for(int j=1;j<=wy;j++) printf("%d%c",mn[i][j]," \n"[j==wy]);
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)) p=mid,l=mid+1;
		else r=mid-1;
	} printf("%d\n",p);
	return 0;
}
```



---

