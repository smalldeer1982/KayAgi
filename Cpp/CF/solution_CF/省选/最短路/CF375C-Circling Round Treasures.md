# Circling Round Treasures

## 题目描述

给你一个 $N \times M$ 的地图（$N,M \le 20$），地图上 `#` 表示障碍物，`B` 表示炸弹，数字表示宝藏序号（宝藏+炸弹个数 $\le 8$），每个宝藏有价值（$-200 \le v \le 200$），`S` 表示出发点。每次移动可以从一个格子移动到相邻格子（上下左右）。寻找一条路径从 `S` 出发再回到 `S` 的封闭路径，移动步数记为 $K$，这个路径所包围的宝藏价值总和记为 $V$，则这条路径的价值为 $V - K$。题目即是求可行的最大的路径价值，并且不能包围炸弹。

## 样例 #1

### 输入

```
4 4
....
.S1.
....
....
10
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7 7
.......
.1###2.
.#...#.
.#.B.#.
.3...4.
..##...
......S
100
100
100
100
```

### 输出

```
364
```

## 样例 #3

### 输入

```
7 8
........
........
....1B..
.S......
....2...
3.......
........
100
-100
100
```

### 输出

```
0
```

## 样例 #4

### 输入

```
1 1
S
```

### 输出

```
0
```

# 题解

## 作者：GKxx (赞：7)

首先明确一下翻译：

It is guaranteed that the map has not more than 8 objects in total. Objects are bombs and treasures.

意思是宝藏和炸弹一共不超过8个，不是最多只有8个宝藏，也不要像我一样误以为炸弹只有1个。。。

这个数据范围提示我们可以对这个东西状压，用一个01串表示宝藏的集合。

那么炸弹怎么办？

可以把炸弹当成价值为-inf的宝藏，就能统一起来了，并且最终找出的最优解一定不会把这种“宝藏”算进去，所以这样做是对的。

考虑设计状态，可以设$dp[x][y][S]$表示走到第$x$行第$y$列这个位置，当前的路径把$S$这个集合的物品围起来了，最小移动步数是多少。

预处理$sum[S]$表示$S$中的物品的总价值，就可以用$sum[S]-dp[sx][sy][S]$来更新答案了（$sx, sy$是起点位置）

转移的话，一种显然的做法是4个方向枚举下一步往哪走，然后枚举每个物品，用射线法检验有没有被围起来（射线法就是计算几何里用来判断点是否在多边形内部的方法，具体看代码），从而得到下一步的物品集合，实现转移

但是我们马上就会发现一个问题：这个状态转移是有环的，人们喜闻乐见的“for一for就可以了”的做法不再管用。

这时我们回到dp的本源来想一想：dp究竟在干嘛？

ZHX：“dp解决的是图论问题，当转移有环的时候要考虑用图论算法。”

因此这道题我们可以考虑用bfs来实现这个dp，具体看代码。

这样的思想在NOIP2014的飞扬的小鸟一题中也适用，那题虽然是一个dp，但是完全可以当成最短路来做（当然了不需要真的把图建出来，只要用类似spfa的做法即可），能省去一些麻烦。

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <queue>

template <typename T> inline void read(T& t) {
    int f = 0, c = getchar(); t = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
    if (f) t = -t;
}
template <typename T> inline bool chkMin(T& x, const T& y) { return y < x ? (x = y, true) : false; }
template <typename T> inline bool chkMax(T& x, const T& y) { return x < y ? (x = y, true) : false; }
#ifdef WIN32
#define LLIO "%I64d"
#else
#define LLIO "%lld"
#endif	// WIN32 long long
#define rep(I, A, B) for (int I = (A); I <= (B); ++I)
#define rrep(I, A, B) for (int I = (A); I >= (B); --I)
#define erep(I, X) for (int I = head[X]; I; I = next[I])

// inf不用设太大，不然小心溢出
const int inf = 2e6 + 207;
int dp[30][30][1 << 10];
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
int gx[30], gy[30], val[30];
int sum[1 << 10];
char G[30][30];
int n, m, t;
int sx, sy;

struct State {
    int x, y, S;
    State(int xx, int yy, int s)
        : x(xx), y(yy), S(s) {}
    State() : x(0), y(0), S(0) {}
};

// 判断从(x, y)走到(nx, ny)时会不会把第i个物品围起来
inline bool in(int x, int y, int nx, int ny, int i) {
    if (nx == gx[i] && ny < gy[i]) if (x < nx) return 1;
    if (x == gx[i] && y < gy[i]) if (x > nx) return 1;
    return 0;
}

inline int bfs() {
    std::queue<State> q;
    q.push(State(sx, sy, 0));
    int ans = 0;
    rep(i, 1, n) rep(j, 1, m) rep(S, 0, (1 << t)) dp[i][j][S] = -1;
    dp[sx][sy][0] = 0;
    while (!q.empty()) {
        State curr = q.front(); q.pop();
        int x = curr.x, y = curr.y, S = curr.S;
        // 更新答案
        if (x == sx && y == sy)
            chkMax(ans, sum[S] - dp[x][y][S]);
        rep(i, 0, 3) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > m || (G[nx][ny] != '.' && G[nx][ny] != 'S')) continue;
            int ns = S;
            rep(j, 1, t) if (in(x, y, nx, ny, j)) ns ^= 1 << (j - 1);
            if (dp[nx][ny][ns] == -1) {
                dp[nx][ny][ns] = dp[x][y][S] + 1;
                q.push(State(nx, ny, ns));
            }
        }
    }
    return ans;
}

int main() {
    read(n); read(m);
    rep(i, 1, n) scanf("%s", G[i] + 1);
    rep(i, 1, n) rep(j, 1, m) {
        char c = G[i][j];
        if (c == 'S') {
            sx = i;
            sy = j;
        } else if (c != '#' && c != '.' && c != 'B') {
            gx[c - 48] = i;
            gy[c - 48] = j;
            ++t;
        }
    }
    rep(i, 1, t) read(val[i]);
    rep(i, 1, n) rep(j, 1, m) {
        char c = G[i][j];
        if (c == 'B') {
            gx[++t] = i;
            gy[t] = j;
            val[t] = -inf;
        }
    }
    for (int S = 1; S < 1 << t; ++S) {
        rep(i, 1, t) if (1 << (i - 1) & S)
            sum[S] += val[i];
    }
    int ans = bfs();
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：CDFLS_mao_zx (赞：3)

## CF375C

### 题意

给定一张地图，里面有宝藏 (数字)，炸弹 'B',障碍物 '#' ，需要从起点出发，绕一圈回到起点，不能把炸弹绕在路径里面，得到的价值时围住的宝藏的价值之和减去走的路径长度。最大化价值。

### 思路

我们考虑如何判断一个点是否在一个多边形内。

有一种比较方便的方法：从这个点引一条射线，如果与多边形的交点为奇数个，那么它在多边形内。

但是，有一种情况考虑不到：

![gbohgtci.png](https://image.blackwhitetony.com/2021/05/17/b0440f90e8c2c.png)

懒得自己画了，用一下楼上奆佬的。

$A$ 点显然在形内，但是判断出来有两个交点。

这种情况有点麻烦，但如果能把靠右的那个线段拼过来就行了，我们发现其实只需要把单位线段看成上开下闭就可以了，当然，前提是方向只有两个。

所以我们考虑 $\text{dp}$ ，$dp[i][j][s]$ 表示走到 $(i,j)$ ，引一条水平向左的射线与路线的交点数为奇数的点的集合的最短路径长度。

答案是枚举起点的所有状态，总点权减去路径长度，取最大值。

对于炸弹，我们认为它的权值为 $-inf$ 。

这样的转移是有环的，但是我们可以把它看成最短路跑。$\text{DP}$ 解决的本质上就是一个图论问题，当转移有环时，考虑图论算法。

所以直接 $\text{BFS}$ 。

### 参考代码：

```cpp
#include<bits/stdc++.h>
#define y1 y3647
#define next nxt
#define LL long long
using namespace std;
inline void read(int &x)
{
	x=0;int f=1;
	char ch=getchar();
	while(ch!=45&&(ch>'9'||ch<'0'))ch=getchar();
	if(ch==45){f=-1,ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	x*=f;
}
int i,j,k,n,s,t,m,ans;
const int N=1<<8;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
char ch[21][21];
int dp[21][21][N],vis[21][21][N],mp[N][N],g[N],w[N],val[N][N];
struct node{
	int x,y,s;
}p;
queue<node> q;
void bfs()
{
	while(!q.empty())
	{
		node now=q.front();
		q.pop();
		for(int j=0;j<4;j++)
		{
			int x=now.x+dx[j],y=now.y+dy[j],s=now.s;
			if(j<=1)
			{
				int x0=x-(j==0);
				for(i=y;i<=m;i++)
				if(~val[x0][i])
				s^=(1<<val[x0][i]);
			}
			if(x>n||x<1||y>m||y<1||mp[x][y]||vis[x][y][s])continue;//注意不能走到宝藏上面。
			dp[x][y][s]=dp[now.x][now.y][now.s]+1;
			vis[x][y][s]=1;
			node np=(node){x,y,s};
			q.push(np);
		}
	}
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//freopen(".ans","w",sdtout);
	memset(dp,1,sizeof(dp));
	int px,py;
	read(n),read(m);
	for(i=1;i<=n;i++)
	{
		scanf("%s",ch[i]+1);
		for(j=1;j<=m;j++)
		{
			if(ch[i][j]=='S')px=i,py=j;
			if(ch[i][j]!='.'&&ch[i][j]!='S')mp[i][j]=1;
			if((ch[i][j]>='0'&&ch[i][j]<='9'))
			val[i][j]=ch[i][j]-'1',t++;
			if((ch[i][j]>'9'||ch[i][j]<'0')&&ch[i][j]!='B')val[i][j]=-1;
		}
	}
	for(i=0;i<t;i++)
	read(w[i]);
	int lst=t;
	for(i=1;i<=n;i++)
	for(j=1;j<=m;j++)
	if(ch[i][j]=='B')
	val[i][j]=t++;
	
	for(i=lst;i<t;i++)
	w[i]=-1e8;//不要1e9 不然炸int
	for(i=1;i<1<<t;i++)
	for(j=0;j<t;j++)
	if(i&(1<<j))
	g[i]+=w[j];
	
	q.push((node){px,py,0});
	vis[px][py][0]=1,dp[px][py][0]=0;
	bfs();
	for(i=0;i<1<<t;i++)
	ans=max(ans,g[i]-dp[px][py][i]);
	cout<<ans;
	return 0;
}
```

### 总结:

对于有环的 $\text{dp}$ 可以考虑图论算法。



---

## 作者：tzc_wk (赞：3)

安利个人 blog：https://www.cnblogs.com/ET2006/

[题面传送门](https://codeforces.ml/contest/375/problem/C)

注意到这题中宝藏 $+$ 炸弹个数最多只有 $8$ 个，故考虑状压，设 $dp[x][y][S]$ 表示当前坐标为 $(x,y)$，有且仅有 $S$ 当中的物品被包围在凸多边形内部所走过的最少步数。

考虑转移，枚举与 $(x,y)$ 相邻的点 $(x',y')$。但是 $S$ 的变化可能有些棘手。这里有一个结论，对于某一点 $(x,y)$，任意引出一条射线，如果它与多边形有奇数个交点，那么 $(x,y)$ 就在多边形内部。由于这里引出的射线可以沿任何方向，那么我们不妨统一假设射线的方向都是向右，故这里的状态 $S$ 就可以理解为：满足 $(x,y)$ 向右引出的射线与多边形交点个数为奇数的点的集合。

这样一来状态是倒搞明白了，但是直接这样转移还是可能会出现一些问题，因为有可能我们是从某个点 $(x,y)$ 向右走到 $(x,y+1)$，而对于某个横坐标也为 $x$ 的点 $(x,y')$，它向右引出的射线与多边形出现了重合的情况，进而就不好计算交点个数。不过这个问题很容易解决，因为行走的路径不会经过宝藏/炸弹，故横向的线段并不会影响交点个数，于是只需计算纵向的线段就行了。

但是这样还是会出现问题。比方说下图，对于点 $A$ 向右引出的橙色射线，如果按照我们的判断其与多边形有两个交点 $B,C$，但如果我们把横向的线段去掉，将两个纵向线段拼在一起，就会发现有用的交点只有 $1$ 个。这个问题也异常容易解决，考虑将每条纵向的线段看作一个上开下闭的线段，当从 $(x,y)$ 走到 $(x+1,y)$ 时只改变满足 $x'=x+1,y'<y$ 的点 $(x',y')$ 的状态；当从 $(x,y)$ 走到 $(x-1,y)$ 时只改变满足 $x'=x,y'<y$ 的点 $(x',y')$ 的状态。这样一来就可以避免这个问题了。

![](https://cdn.luogu.com.cn/upload/image_hosting/gbohgtci.png)

最短路转移即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc((x%10)+'0');}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=20;
const int MAXP=256;
const int MAXM=8;
const int INF=0x3f3f3f3f;
const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
int n,m,sx,sy;char s[MAXN+3][MAXN+3];
int dp[MAXN+2][MAXN+2][MAXP+3];
int px[MAXM+2],py[MAXM+2],a[MAXM+2],c1=0,c2=0;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(s[i][j]=='S') sx=i,sy=j;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(isdigit(s[i][j])){
		px[s[i][j]^48]=i;py[s[i][j]^48]=j;c1++;
	} c2=c1;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(s[i][j]=='B') px[++c2]=i,py[c2]=j;
	for(int i=1;i<=c1;i++) scanf("%d",&a[i]);
	memset(dp,63,sizeof(dp));dp[sx][sy][0]=0;
	queue<pair<pii,int> > q;q.push(mp(mp(sx,sy),0));
	while(!q.empty()){
		pair<pii,int> p=q.front();q.pop();
		int x=p.fi.fi,y=p.fi.se,msk=p.se;
//		printf("%d %d %d %d\n",x,y,msk,dp[x][y][msk]);
		for(int i=0;i<4;i++){
			int nx=x+dx[i],ny=y+dy[i];
			if(nx<1||nx>n||ny<1||ny>m) continue;
			if(s[nx][ny]!='.'&&s[nx][ny]!='S') continue;
			int nmsk=msk;
			for(int j=1;j<=c2;j++) if((!(px[j]^x)&&!(i^2)||!(px[j]^nx)&&!i)&&py[j]<ny)
				nmsk^=1<<j-1;
			if(dp[nx][ny][nmsk]==INF){
				dp[nx][ny][nmsk]=dp[x][y][msk]+1;
				q.push(mp(mp(nx,ny),nmsk));
			}
		}
	}
	int ans=-INF;
	for(int i=0;i<(1<<c1);i++) if(dp[sx][sy][i]!=INF){
		int sum=0;
		for(int j=0;j<c1;j++) sum+=a[j+1]*(i>>j&1);
		chkmax(ans,sum-dp[sx][sy][i]);
	} printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Rikka__ (赞：2)





题目链接：[CF375C Circling Round Treasures](https://www.luogu.com.cn/problem/CF375C)

题意：

　　给定一个 $n \times m$ 的棋盘，有障碍、宝藏、陷阱（陷阱和宝藏的数量加起来不超过 8）。每个宝藏有一定的权值，要求用折线围成一个多边形，使得其内部不含有陷阱。对于一个多边形的价值为 **围住的宝藏权值和**减去**多边形的周长** ，求最大价值。

题解：

　　如何判断一个点 $p$ 在多边形的内部？

　　以 $p$ 为起点画一条不经过多边形端点的射线，若和多边形的边有奇数个交点则 $p$ 在多边形内部，偶数个则在外部。

发现宝藏和陷阱的数量极少，可以考虑状压，给每个 **宝藏** \ **陷阱** 格子选一条射线，在转移的时候去更新有宝藏或陷阱的格子的射线与当前路径交点的奇偶性。

　　设 $f[i][j][S]$ 表示当前格子为 $(i,j)$ ，宝藏和陷阱的奇偶性的状态为 $S$ ,多边形的周长的最小值。

　　dfs 转移不太可行，我们发现每次转移只会让多边形的周长增加 1，故可以考虑BFS转移(没得选了QAQ)。

　　转移的时候枚举每个宝藏是否被包围就行了。

Code：

 

```cpp
#include <bits/stdc++.h> 
using namespace std; 
const int Maxn = 25; 
const int Maxm = 500; 
const int Maxk = 1<<9; 
const int inf = 1e6 + 100; 
const int dx[4] = { 1, -1, 0, 0 }; 
const int dy[4] = { 0, 0, 1, -1 }; 
int n;
int m;
int s;
int t; 
int cnt;
int res; 
int val[Maxm];
int sum[Maxk]; 
int f[Maxn][Maxn][Maxk]; 
char c[Maxn][Maxn]; 
struct node {
	int x;
	int y;
	int v;
}; 
struct point {
	int x;
 	int y;
}p[Maxm]; 

bool check(int x, int y, int xx, int yy, int i) {
	if (xx == p[i].x && yy < p[i].y && x < xx) return 1; 
	if (x == p[i].x && y < p[i].y && x > xx) return 1; 
	return 0; 
}
queue<node> q; 
signed main() { 
	
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> c[i][j]; 
			if (c[i][j] == 'S') {
				s = i; 
				t = j; 
			} else if (c[i][j] != '.' && c[i][j] != '#' && c[i][j] != 'B') {
	 			p[c[i][j] - '0'].x = i; 
				p[c[i][j] - '0'].y = j; 
				++cnt; 
			}
		}
	}
	
	for (int i = 1; i <= cnt; ++i) cin>>val[i]; 
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (c[i][j] == 'B') { 
				p[++cnt].x = i; 
				p[cnt].y = j; 
				val[cnt] = -inf; 
			}
		}
	}
	
	for (int i = 1; i < (1<<cnt); ++i) {
		for (int j = 1; j <= cnt; ++j) {
			if (i & (1<<(j-1))) sum[i] += val[j]; 
		}
	}
	res = 0; 
	memset(f, -1, sizeof f); 
	q.push({s, t, 0}); 
	f[s][t][0] = 0; 
		
	while (!q.empty()) {
		node now = q.front(); 
		q.pop(); 
		int x = now.x, y = now.y, v = now.v; 
		if (x == s && y == t) {
			res = max(res, sum[v] - f[x][y][v]); 
		}
		for (int i = 0; i < 4; ++i) {
			int xx = x + dx[i], yy = y + dy[i], val = v; 
			if (xx < 1 || xx > n || yy < 1 || yy > m) continue; 
			if (c[xx][yy] != 'S' && c[xx][yy] != '.') continue; 
			for (int j = 1; j <= cnt; ++j) {
				if (check(x, y, xx, yy, j)) val ^= 1<<(j-1); 
			}
			if (f[xx][yy][val] == -1) {
				f[xx][yy][val] = f[x][y][v] + 1; 
				q.push({xx, yy, val}); 
			}
		}
	}
	cout<<res;
	return 0;
}
```

​	

---

## 作者：pengyule (赞：1)

Q1：如何判断一个点在不在边可交叉的多边形内部？  
A1：作出一条不与多边形任意一边平行的射线，与多边形边的交点个数为奇则在内部否则在外部。  

Q2：这条射线可以随便选吗？比如钦定向右？  
A2：可以，但是需要考虑某一边与射线共线的情况，稍加思考可发现：横着的边没有贡献，竖着的边看成上开下闭的线段，射线与这些上开下闭线段的交点个数即为判断依据。

Q3：DP 前有什么准备工作？  
A3：将炸弹看成价值为 $-\infty$ 的宝藏。

Q4：如何设计状压 DP 状态？  
A4：由于状态只与交点个数奇偶性有关，用 $f(x,y,s)$ 表示从 $(sx,sy)$ 走到 $(x,y)$，目前 $s$ 这些状态的物品满足从各自出发的向右射线的贡献为奇数，最少步数。

Q5：如何转移？  
A5：从一个状态 $f(x,y,s)$ 转移到相邻状态 $f(nx,ny,t)$ 时，如果 $(x,y)\to (nx,ny)$ 为横向线段则 $t=s$，否则根据是向上走还是向下走判断新增了哪一个点，并考察各个物品的射线是否经过该点。由于 DP 状态并没有明显的顺序性，而我们本质上要求一个最少步数，也就是可以用 BFS 来做这个转移。

Q6：如何实现？  
A6：代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF=1e7;
int n,m,K,sx,sy,tx[10],ty[10],tc[10],f[25][25][1<<8],Log[1<<8],sum[1<<8];
char a[25][25];
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
struct node {
	int x,y,s;
};
queue<node>Q;
int get(int x,int y,int nx,int ny,int i){
	if(x==nx)return 0;
	if(nx<x&&tx[i]==x&&ty[i]<y)return 1;//上开下闭 
	if(nx>x&&tx[i]==nx&&ty[i]<y)return 1;
	return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		if(a[i][j]>='0'&&a[i][j]<='9'){
			K++;
			tx[a[i][j]-'0']=i,ty[a[i][j]-'0']=j;
		}
	}
	for(int i=1;i<=K;i++)scanf("%d",&tc[i]);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		if(a[i][j]=='B'){
			K++;
			tx[K]=i,ty[K]=j;
			tc[K]=-INF;
		}
		if(a[i][j]=='S')sx=i,sy=j;
	}
	memset(f,0x3f,sizeof f);
	f[sx][sy][0]=0;
	Q.push(node{sx,sy,0});
	while(!Q.empty()){
		int x=Q.front().x,y=Q.front().y,s=Q.front().s;Q.pop();
		for(int i=0;i<4;i++){
			int nx=x+dx[i],ny=y+dy[i];
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&a[nx][ny]!='#'&&a[nx][ny]!='B'&&!(a[nx][ny]>='0'&&a[nx][ny]<='9')){
				int ss=s;
				for(int j=1;j<=K;j++)ss^=get(x,y,nx,ny,j)<<(j-1);
				if(f[nx][ny][ss]==f[0][0][0])f[nx][ny][ss]=f[x][y][s]+1,Q.push(node{nx,ny,ss});
			}
		}
	}
	int ans=-1e9;
	for(int i=0;i<K;i++)Log[1<<i]=i;
	for(int i=1;i<(1<<K);i++)sum[i]=sum[i-(i&-i)]+tc[1+Log[i&-i]];
	for(int i=0;i<(1<<K);i++)ans=max(ans,sum[i]-f[sx][sy][i]);
	cout<<ans<<'\n';
} 
```

---

## 作者：MILLOPE (赞：0)

## my blog 
[$\color{blue} my \ \ \ blog$](https://blog.csdn.net/qq_34493840/article/details/94588642)
## 题目
[题目传送门](https://www.luogu.org/problemnew/show/CF375C)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190703191356579.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM0NDkzODQw,size_16,color_FFFFFF,t_70)

输入输出样例
输入样例一
```cpp
4 4
....
.S1.
....
....
10
```
输出样例一
```cpp
2
```
输入样例二
```cpp
7 7
.......
.1###2.
.#...#.
.#.B.#.
.3...4.
..##...
......S
100
100
100
100
```
输出样例二
```cpp
364
```
输入样例三
```cpp
7 8
........
........
....1B..
.S......
....2...
3.......
........
100
-100
100
```
输出样例三
```cpp
0
```
输入样例四
```cpp
1 1
S
```
输出样例四
```cpp
0
```

## 题解
- 设$sum[i]$表示获得宝藏的状态为$i$时所得到的价值
- 设$f[i][j][k]$表示走到点$(i，j)$选取宝藏的状态为$k$时的最小步数
- 答案为$sum[k]-f[s][t][k]$
- $DP$时$BFS$即可

## $code$
```cpp
#include <bits/stdc++.h> 
using namespace std; 
const int maxn = 25; 
const int maxm = 500; 
const int maxk = 1<<9; 
const int inf = 1e6 + 100; 
const int dx[4] = { 1, -1, 0, 0 }; 
const int dy[4] = { 0, 0, 1, -1 }; 

template <typename T> 
inline void read(T &s) { 
	s = 0; 
	T w = 1, ch = getchar(); 
	while (!isdigit(ch)) { if (ch == '-') w = -1; ch = getchar(); } 
	while (isdigit(ch)) { s = (s<<1) + (s<<3) + (ch^48); ch = getchar(); } 
	s *= w; 
} 

int n, m, s, t; 
int cnt, res; 
int val[maxm], sum[maxk]; 
int f[maxn][maxn][maxk]; 
char c[maxn][maxn]; 
struct node { int x, y, v; }; 
struct point { int x, y; } p[maxm]; 

inline bool check(int x, int y, int xx, int yy, int i) {
	if (xx == p[i].x && yy < p[i].y && x < xx) return true; 
	if (x == p[i].x && y < p[i].y && x > xx) return true; 
	return false; 
}

void bfs() {
	res = 0; 
	memset(f, -1, sizeof(f)); 
	queue<node> q; 
	q.push((node){s, t, 0}); 
	f[s][t][0] = 0; 
		
	while (!q.empty()) {
		node now = q.front(); 
		q.pop(); 
		int x = now.x, y = now.y, v = now.v; 
		if (x == s && y == t) {
			res = max(res, sum[v] - f[x][y][v]); 
		}
		for (int i = 0; i < 4; ++i) {
			int xx = x + dx[i], yy = y + dy[i], vv = v; 
			if (xx < 1 || xx > n || yy < 1 || yy > m) continue; 
			if (c[xx][yy] != 'S' && c[xx][yy] != '.') continue; 
			for (int j = 1; j <= cnt; ++j) {
				if (check(x, y, xx, yy, j)) vv ^= 1<<(j-1); 
//				cout << vv << endl;  
			}
			if (f[xx][yy][vv] == -1) {
				f[xx][yy][vv] = f[x][y][v] + 1; 
				q.push((node){xx, yy, vv}); 
			}
		}
	}
}

int main() {
//	freopen("1.in", "r", stdin); 
	
	read(n), read(m); 
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> c[i][j]; 
			if (c[i][j] == 'S') {
				s = i; 
				t = j; 
			} else if (c[i][j] != '.' && c[i][j] != '#' && c[i][j] != 'B') {
	 			p[c[i][j] - '0'].x = i; 
				p[c[i][j] - '0'].y = j; 
				++cnt; 
			}
		}
	}
	
	for (int i = 1; i <= cnt; ++i) read(val[i]); 
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (c[i][j] == 'B') { 
				p[++cnt].x = i; 
				p[cnt].y = j; 
				val[cnt] = -inf; 
			}
		}
	}
	
	for (int i = 1; i < (1<<cnt); ++i) {
		for (int j = 1; j <= cnt; ++j) {
			if (i & (1<<(j-1))) sum[i] += val[j]; 
		}
	}
	
	bfs();
	
	printf("%d\n", res);
	return 0;
}
```

---

