# [BalticOI 2008] 游戏

## 题目描述

玩家 $\text{A}$ 和玩家 $\text{B}$，在一个 $n\times n$ 的正方形方格板上玩游戏。方格板上的方格要么是白的，要么是黑的。游戏只在白色区域上进行，黑色区域是禁区。初始时，每位玩家的起点上，会放置一个棋子。保证两人起点不同。

玩家交替移动，玩家 $\text{A}$ 先移动。每次移动，玩家会将他的棋子移动到相邻的白色方格中。如果玩家将棋子移动到对方现在的位置，玩家可以再移动一步，以越过对手。注意在这种情况下，第二步移动的方向可以与第一步移动的不同。

这个游戏的目标是玩家的棋子首先到达对方的起点，先到者为胜。即使玩家的最后一步包含两次移动，并且他只是越过了对手的起点（如果对手现在在起点），这个玩家也获得胜利。

给出方格板的布局和两个玩家的起点，判定哪个玩家有必胜策略（如果对手不管怎样移动，一个玩家能获得胜利，就称一个玩家有必胜策略）。 

## 说明/提示

**样例解释**

对于第一组数据： 

![0](https://i.loli.net/2018/02/19/5a8ab4a17e247.gif)

如果 $\text{A}$ 在前三次移动中移动到方格最右边，$\text{B}$ 将在前三次移动中向上移动。因此，在第三次移动中玩家 $\text{B}$ 将会到达 $\text{A}$ 的方块所在方格，并且给 $\text{B}$ 一次额外的移动机会。因此，$\text{B}$ 会首先到达 $\text{A}$ 的起点并且赢得游戏。

对于第二组数据： 

![1](https://i.loli.net/2018/02/19/5a8ab4a17e132.gif)

$\text{A}$ 可以先向右移动一次，再向下移动一次。然后，$\text{A}$ 可以由 $\text{B}$ 的前两次移动决定他向下或向右移动来回避 $\text{B}$。这样的话 $\text{A}$ 会首先到达 $\text{B}$ 的起点，因此赢得比赛。事实上我们已经证明了 $\text{A}$ 有必胜策略。

**数据范围**

对于 $40\%$ 的数据， $n \le 40$。

对于 $60\%$ 的数据， $n \le 150$。

对于所有数据，$2\le n\le 300$。

## 样例 #1

### 输入

```
2
4
A...
.#..
....
...B
4
A...
....
..#.
...B```

### 输出

```
B
A```

# 题解

## 作者：_LPF_ (赞：5)

~~大概是全网找不到什么题解所以写一发，顺便求个卡常大师卡卡常。~~

[[BalticOI 2008]游戏](https://www.luogu.com.cn/problem/P4658)

> 给定 $n\times n$ 的矩阵，有 A 和 B 两人的起点和障碍物。
>
> 由 A 先走，每次每人轮流走一步，如果走到另一个人头上就必须再走一步。
>
> 谁先到达另一个人的起点谁获胜，如果到达对方起点时对方恰好在自己起点上，也视为获胜。

不难发现先手具有巨大优势，因为两人的最短路径长度（设为 $D$）是一样的，唯一的翻盘点在 B 跳到 A 头上一次。

**性质一：每个人必走最短路径**。

否则另一个人只要坚定的走最短路径就必然获胜。

这样预处理从 A,B 两点出发，到每个格子的最短距离，称 $\text{dis}_{A}=D-\text{dis}_{B}$ 的格子为**合法格子**。

**性质二：若 $D$ 为奇数则 A 必胜**。

这个也显然，因为这样 B 想碰到 A 也碰不上。

同时发现，偶数时，如果 B 碰上了 A，一定是两者同时到达 $\text{dis}_A=\text{dis}_B=\dfrac{D}{2}$ 的格子，称这样的格子为**关键格子**。

基于这些性质，就很容易想到做法。

设 $S(x,y)$ 表示从 $(x,y)$ 出发，只通过 合法格子 能到达的 关键格子 集合。

**性质三：B 能获胜当且仅当：**

**对于 A 的每条从起点到某个 关键格子 路径：$(ax_0,ay_0),(ax_1,ay_1),\cdots,(ax_{\frac{D}{2}},ay_{\frac{D}{2}})$。（其中 $0$ 下标表示对应人的起点）**

**都有至少一条 B 的路径：$(bx_0,by_0),(bx_1,by_1),\cdots,(bx_{\frac{D}{2}},by_{\frac{D}{2}})$，满足 $\forall i\in[0,\frac{D}{2}],S(ax_i,ay_i)\subset S(bx_i,by_i)$。**

相当于，对于每次 A 的移动，B 总能合理的移动，使得 A 能到的关键格子 B 都能到。这样显然 B 能碰上 A，否则不能。

具体实现上，只需要对于每个同层的 A,B 路径中的格子对枚举判断。

如果对于 A 格子的下一步的每个格子，都有至少一个 B 的下一步能到的格子与之匹配，那么它们匹配。

最终只要验证 A,B 的起点是否匹配即可。

因为每层的格子数是 $O(n)$ 的，所以总复杂度是 $O(Tn^3)$ 的，在 loj 上通过了，但在洛谷上还是 t 了两个点。

在线求卡常大师/kel

```cpp
#include<bits/stdc++.h>
typedef long long LL;
#define rep(i, a, b) for(register int i = (a); i <= (b); i ++)
#define per(i, a, b) for(register int i = (a); i >= (b); i --)
#define Ede(i, u) for(int i = head[u]; i; i = e[i].nxt)
using namespace std;

inline int read() {
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') f = (c == '-') ? - 1 : 1, c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
	return x * f;
}

typedef pair<int, int> pii;
#define mp make_pair
#define fi first
#define se second

const int N = 310;
int n, dis[2][N][N], flg[N][N], num[N][N];
char str[N][N];
vector<pii> vec[N * N];
bool vis[2][N << 1][N << 1];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

inline void clear() {memset(vis, false, sizeof(vis)); rep(i, 0, n << 1) vec[i].clear();}

inline int get(pii cur) {return num[cur.fi][cur.se];}

inline void calc(int sx, int sy, int o) {
	rep(i, 1, n) rep(j, 1, n) dis[o][i][j] = -1;
	dis[o][sx][sy] = 0;
	queue<pii> q; q.push(mp(sx, sy));
	while(! q.empty()) {
		pii u = q.front(); q.pop();
		int x = u.fi, y = u.se;
		rep(d, 0, 3) {
			int nx = x + dx[d], ny = y + dy[d];
			if(nx < 1 || nx > n || ny < 1 || ny > n || str[nx][ny] == '#' || dis[o][nx][ny] != -1) continue;
			dis[o][nx][ny] = dis[o][x][y] + 1;
			q.push(mp(nx, ny));
		}
	}
}

inline vector<pii> solve(pii cur, int o) {
	int x = cur.fi, y = cur.se;
	vector<pii> now;
	rep(d, 0, 3) {
		int nx = x + dx[d], ny = y + dy[d];
		if(nx < 1 || nx > n || ny < 1 || ny > n || str[nx][ny] == '#') continue;
		if(flg[nx][ny] == flg[x][y] + o) now.push_back(mp(nx, ny));
	}
	return now;
}

inline bool involve(pii a, vector<pii> bcur) {
	for(pii b : bcur) if(vis[0][get(a)][get(b)]) return true;
	return false;
}

int ax, ay, bx, by;

void work() {
	n = read(), clear();
	rep(i, 1, n) scanf("%s", str[i] + 1);
	rep(i, 1, n) rep(j, 1, n)
		if(str[i][j] == 'A') ax = i, ay = j;
		else if(str[i][j] == 'B') bx = i, by = j;
	calc(ax, ay, 0);
	calc(bx, by, 1);
	int Dis = dis[0][bx][by];
	if(Dis & 1) {puts("A"); return;}
	rep(i, 1, n) rep(j, 1, n) {
		flg[i][j] = -1;
		if(dis[0][i][j] != -1 && dis[1][i][j] != -1 && Dis - dis[0][i][j] == dis[1][i][j]) {
			flg[i][j] = dis[0][i][j], vec[flg[i][j]].push_back(mp(i, j));
			num[i][j] = vec[flg[i][j]].size();
		}
	}
	rep(i, 1, (int) vec[Dis / 2].size()) vis[0][i][i] = true;

	per(d, Dis / 2 - 1, 0) {
		for(pii a : vec[d]) {
			vector<pii> acur = solve(a, 1);
			for(pii b : vec[Dis - d]) {
				vector<pii> bcur = solve(b, - 1);
				bool flag = true;
				for(pii o : acur) if(! involve(o, bcur)) {flag = false; break;}
				if(flag) vis[1][get(a)][get(b)] = true;
			}
		}
		rep(i, 1, (int) vec[d + 1].size()) rep(j, 1, (int) vec[Dis - d - 1].size()) vis[0][i][j] = false;
		rep(i, 1, (int) vec[d].size()) rep(j, 1, (int) vec[Dis - d].size()) vis[0][i][j] = vis[1][i][j], vis[1][i][j] = false;
	}
	puts(vis[0][get(mp(ax, ay))][get(mp(bx, by))] ? "B" : "A");
}

int main() {
	int t = read();
	while(t --) work();
	return 0;
}
```



---

## 作者：Jerrywang09 (赞：2)

本题至少得是紫题吧……反正思路很复杂，代码也难写，还要卡时、空常数。

拿出草稿纸手玩样例后，首先有如下结论：

1. 双方一定走最短路。

> 证明：如果有一方不走最短路，那么另一方走最短路就一定能赢。

2. 如果最短路的长度为奇数，则 A 必胜。

> 证明：如果 A、B 不碰面，则 A 必胜（显然）。如果 A、B 碰面，则一定是 A 从 B 头上跳过，A 反而走得更快了，B 没法翻盘。

3. 如果 A 有一种走法，使得无论 B 怎么走，A 都可以不碰上 B，则 A 必胜；否则 A 必败。

> 证明：如果 A 碰上 B，此时是 B 从 A 的头上跳过，B 可以实现翻盘。不然 B 永远无法翻盘。

有了上述结论，本题还是很困难。第三个结论比较难判。

先两次 bfs，求出 A、B 到达每个点的最短距离。下面只关心**关键点**，也就是在 A、B 最短路径上的点。同样也可以求出 A、B 可能在哪些点上相遇，这些点称作**相遇点**。

这样我们有思路：

枚举一个从 A 开始走 $i$ 步到达的**关键点**，看看其继续往下走，能到达的**相遇点**集合 $S_1$；

再枚举从 B 开始走 $i$ 步到达的**关键点**，其继续往下走，能到达的**相遇点**集合记为 $S_2$；

如果对于所有的 $S_2$ 都有 $S_1 \not \subset S_2$，则意味着从 A 开始走到达了这个点，就可以避开 B，A 就可以获胜，完美！

对于集合属于关系的判定，可以考虑 `bitset`，每个**关键点**能到达的**相遇点**用 `bitset` 存储。倒序循环 $i$，类似于动态规划来转移集合。

不知道为啥空间限制这么严。建议多使用动态数组 `vector` 以节省内存。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=305;
using namespace std;

int n; char mp[N][N]; bool flag[N][N];
bitset<N> finals[N][N];
struct node {int i, j;} sa, sb;
int da[N][N], db[N][N], dis;
int dx[]={-1, 1, 0, 0}, dy[]={0, 0, -1, 1};
void bfs(node st, int d[N][N])
{
	memset(d, 0x3f, sizeof da);
	queue<node> q; q.push(st); d[st.i][st.j]=0;
	while(q.size())
	{
		auto [i,j]=q.front(); q.pop();
		rep(k, 0, 3)
		{
			int ni=i+dx[k], nj=j+dy[k];
			if(ni<1 || ni>n || nj<1 || nj>n) continue;
			if(mp[ni][nj]=='#') continue;
			if(d[i][j]+1<d[ni][nj])
				d[ni][nj]=d[i][j]+1, q.push({ni, nj});
		}
	}
}

void extend(int i, int j, int d[N][N])
{
	rep(k, 0, 3)
	{
		int ni=i+dx[k], nj=j+dy[k];
		if(ni<1 || ni>n || nj<1 || nj>n) continue;
		if(mp[ni][nj]=='#') continue;
		if(d[i][j]+1==d[ni][nj] && flag[ni][nj])
			finals[i][j]|=finals[ni][nj];
	}
}

void solve()
{	
	scanf("%d", &n);
	rep(i, 1, n) scanf("%s", &mp[i][1]);
	rep(i, 1, n) rep(j, 1, n)
	{
		finals[i][j].reset();
		flag[i][j]=0;		
		if(mp[i][j]=='A') sa={i, j};
		if(mp[i][j]=='B') sb={i, j};
	}
	bfs(sa, da), bfs(sb, db);	
	dis=da[sb.i][sb.j];
	if(dis&1) return puts("A"), void();
	rep(i, 1, n) rep(j, 1, n) if(da[i][j]+db[i][j]==dis) flag[i][j]=1;
	int k=0;
	rep(i, 1, n) rep(j, 1, n) if(da[i][j]*2==dis)
	{
		finals[i][j]=1<<k, k++;
	}
	vector<vector<node>> vec(dis+1);
	rep(i, 0, dis) vec[i].clear(); 
	rep(i, 1, n) rep(j, 1, n) if(flag[i][j])
		vec[da[i][j]].push_back({i, j});
	for(int k=dis/2-1; k>=0; k--)
	{
		for(auto [i,j]:vec[k]) extend(i, j, da);
		for(auto [i,j]:vec[dis-k]) extend(i, j, db);
		for(auto [i,j]:vec[k])
		{
			bool can_reach=0;
			for(auto [ii,jj]:vec[dis-k])
			{
				if((finals[i][j]&finals[ii][jj])==finals[i][j])
				{
					can_reach=1; break;
				}
			}
			if(!can_reach)
			{
				puts("A"); return;
			}
		}
	}
	puts("B");
}

int main()
{
#ifdef Jerrywang
	freopen("E:/OI/in.txt", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) solve();
	
	return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：2)

真的才蓝？真的才蓝？真的才蓝？

--------

容易发现两人都会一直走最短路。而对于 B 来说，除非它能保证跨越 A 一次，否则永远是 B 负。

这个跨越可能难以理解，假设去掉跨越，那么实质上是 B 要保证某个时刻，B 走完（注意不是 A 走完）之后和 A 重叠。

那么由此容易得出首先最短距离是奇数的时候 B 不可能跨越到 A。

然后可以考虑 dp：设 $dp(x_A,y_A,x_B,y_B)$ 表示 A 此时在  $(x_A,y_A)$，B 在 $(x_B,y_B)$ ，B 能否保证做到和 A 重叠。

这样我们得到了一个单次 $O(n^4)$ 的做法，但其显然不够优秀。

注意到设 $d_{A}(x,y)$ 表示 A 的出发点到 $(x,y)$ 的最短路，$d_B(x,y)$ 表示 B 的出发点到 $(x,y)$ 的最短路。则 $(x_A,y_A,x_B,y_B)$ 满足 $d_A(x_A,y_A)=d_B(x_B,y_B)$，换言之不是所有的 $(x_A,y_A,x_B,y_B)$ 都是有意义的。

此时，有趣的问题是探讨有意义的点对的数量级。

事实上可以近似地看作这个问题：若干个和为 $n^2$ 的正整数的平方和的最大值，且每个数都小于等于 $n$。

根号分治做多了的人都可以立马看出平方和的上界是 $n^3$ 级别的。

那么这个分析道理何在呢？我们本质上是把所有最短路上的点划分进了 A，B 两个集合。离哪个点的最短路近，就划分进哪一个。然后我们的 $(x_1,y_1,x_2,y_2)$ 有意义，当且仅当这两个点在两边集合，且层数相同。所以对于每一层，设左边有 $x$ 个，右边有 $y$ 个。则 $xy\le (x+y)^2$。而注意到每一层的 $x+y$ 上限是 $O(n)$ 级别的，所有层的 $x+y$ 之和不超过 $n^2$ 级别，所以就可以近似地视作上面的那个模型。

实现上也要注意，因为本题极小的空间设置，必须运用类似分层 dp 的想法然后滚动数组去优化空间。即先处理层数最大的点之间的匹配，然后处理层数小一级的...最后就只剩下了两个初始点。

时间复杂度 $O(n^3)$ 空间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
const int MAXN=310,INF=1e9,px[4]={-1,0,1,0},py[4]={0,1,0,-1};
int T,n,sx,sy,ex,ey;
int d[2][MAXN][MAXN],idx[MAXN][MAXN];
char s[MAXN][MAXN];
queue<array<int,2> >pq;
vector<array<int,2> >p1[MAXN*MAXN],p2[MAXN*MAXN];
bool dp[MAXN*2][MAXN*2],tmp[MAXN*2][MAXN*2];
int valid(array<int,2> q){
    return q[0]>=1 && q[0]<=n && q[1]>=1 && q[1]<=n;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>T;
    
    while(T--){
        cin>>n;
        rep(i,1,n){
            cin>>(s[i]+1);
        }
        rep(i,1,n)rep(j,1,n)if(s[i][j]=='A')sx=i,sy=j;else if(s[i][j]=='B')ex=i,ey=j;
        rep(i,1,n)rep(j,1,n)d[0][i][j]=d[1][i][j]=INF;       
        d[0][sx][sy]=0;pq.push({sx,sy});
        while(pq.size()){
            auto p=pq.front();pq.pop();
            rep(k,0,3){
                array<int,2> q={p[0]+px[k],p[1]+py[k]};
                if(!valid(q))continue;
                if(s[q[0]][q[1]]=='#')continue;
                if(d[0][q[0]][q[1]]>d[0][p[0]][p[1]]+1){
                    d[0][q[0]][q[1]]=d[0][p[0]][p[1]]+1;
                    pq.push(q);
                }
            }
        }
        d[1][ex][ey]=0;pq.push({ex,ey});
        while(pq.size()){
            auto p=pq.front();pq.pop();
            rep(k,0,3){
                array<int,2> q={p[0]+px[k],p[1]+py[k]};
                if(!valid(q))continue;
                if(s[q[0]][q[1]]=='#')continue;
                if(d[1][q[0]][q[1]]>d[1][p[0]][p[1]]+1){
                    d[1][q[0]][q[1]]=d[1][p[0]][p[1]]+1;
                    pq.push(q);
                }
            }
        }
        int D=d[0][ex][ey];
        if(odd(D)){
            cout<<"A\n";continue;
        }
        rep(i,0,D/2)p1[i].clear(),p2[i].clear();
        rep(i,1,n)rep(j,1,n){
            if(d[0][i][j]+d[1][i][j]==D){
                if(d[0][i][j]<=D/2)p1[d[0][i][j]].push_back({i,j}),idx[i][j]=p1[d[0][i][j]].size()-1;
                if(d[0][i][j]>=D/2)p2[D-d[0][i][j]].push_back({i,j}),idx[i][j]=p2[D-d[0][i][j]].size()-1;
            }
        }
        memset(dp,0,sizeof dp);
        int sz=p1[D/2].size();
        rep(i,0,sz-1)dp[i][i]=1;
        per(lvl,D/2-1,0){
            //calc new dp
            int sz1=p1[lvl].size(),sz2=p2[lvl].size();
            rep(i,0,sz1-1)rep(j,0,sz2-1){
                array<int,2>X=p1[lvl][i],Y=p2[lvl][j];
                p1[lvl+1].clear();p2[lvl+1].clear();
                tmp[i][j]=1;
                rep(k1,0,3){
                    array<int,2>X2={X[0]+px[k1],X[1]+py[k1]};
                    if(!valid(X2))continue;
                    if(s[X2[0]][X2[1]]=='#')continue;
                    if(d[0][X2[0]][X2[1]]!=d[0][X[0]][X[1]]+1 || d[0][X2[0]][X2[1]]+d[1][X2[0]][X2[1]]!=D)continue;
                    int flag=0;
                    rep(k2,0,3){
                        array<int,2>Y2={Y[0]+px[k2],Y[1]+py[k2]};
                        if(!valid(Y2))continue;
                        if(s[Y2[0]][Y2[1]]=='#')continue;
                        if(d[1][Y2[0]][Y2[1]]!=d[1][Y[0]][Y[1]]+1 || d[1][Y2[0]][Y2[1]]+d[0][Y2[0]][Y2[1]]!=D)continue;
                        int idx1=idx[X2[0]][X2[1]],idx2=idx[Y2[0]][Y2[1]];
                        if(dp[idx1][idx2]){
                            flag=1;break;
                        }
                    }
                    if(!flag){
                        tmp[i][j]=0;break;
                    }
                }
            }
            rep(i,0,sz1-1)rep(j,0,sz2-1)dp[i][j]=tmp[i][j];

        }
        if(dp[0][0])cout<<"B\n";
        else cout<<"A\n";
    }

    return 0;
}
```

---

## 作者：masonpop (赞：0)

首先有结论：双方一定会走最短路，因为只要对方坚定的走最短路就会赢。

并且，只要最短路长度 $T$ 为奇数，那么先手一定赢，因为双方无法相遇。

否则，问题就变成了 B 能否保证抓住 A。注意到双方只会走满足 $dis(A,x)+dis(B,x)=T$ 的点 $x$。令这些点为**关键点**。满足 $dis(A,x)=\dfrac{T}{2}$ 的点称为**相遇点**。那么很容易问题转化为这样一个问题：

对 A 每条通往某个相遇点的路径，是否总能对应找到 B 的一条路径，使得对于他们对应的每一步，A 能走到的相遇点集合包含于 B 能走到的。

显然，只需维护每一层能“匹配”的点对，然后倒着考虑即可。

复杂度单组 $O(n^3)$。轻微卡常，实测通过调整变量顺序，避免重复访问相当有效。[代码](https://www.luogu.com.cn/paste/oqsnmvie)。

---

