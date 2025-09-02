# [IOI 2009] Mecho

## 题目背景

IOI2009 D2T2

## 题目描述

小熊 Mecho 发现了一个宝藏 —— 蜜蜂的秘密蜜罐，里面装满了蜂蜜！他高兴地吃着他的新发现的宝藏，直到突然有一只蜜蜂看到了他，并发出了警报。他知道就在这个时刻，成群的蜜蜂会从蜂巢里出来，开始四处蔓延，试图抓住他。他知道他必须离开蜜罐，尽快回家，但蜂蜜太甜了， Mecho 不想太早离开。帮 Mecho 确定他最晚什么时候可以离开。

Mecho 所在的森林是 $N\times N$ 的正方形网格，其两侧平行于南北和东西方向。每个格子由一棵树、一小块草、一个蜂巢或 Mecho 的家占据。如果两个格子中的一个与另一个的北、南、东或西相邻（但不在对角线上），则认为这两个格子相邻。Mecho 是一只笨拙的熊，所以每次它走一步，都只能移动至相邻的格子。Mecho 只能在草地上行走，不能穿过树木或蜂巢，而且他每分钟最多能走 $S$ 步。

当蜜蜂警报响起的那一刻， Mecho 在装有蜜罐的草格子里，而蜜蜂则在每个包含蜂巢的格子里（森林里可能有不止一个蜂巢）。接下来的每一分钟内，以下事件按顺序发生:

1. 如果 Mecho 还在吃蜂蜜，他会决定是继续吃还是离开。如果它继续吃东西，就会一动不动。否则，他会立即离开，并像上面描述的那样移动至多 $S$ 步。 Mecho 不能带任何蜂蜜，所以一旦他移动了，他就不能再吃蜂蜜了。

2. 当 Mecho 吃完或移动了整整一分钟后，蜜蜂在网格中进一步扩散了一个单位，只移动到草格子中。具体地，蜂群扩散到每一个与任何已经有蜜蜂的格子相邻的草格子。此外，一旦一个格子有蜜蜂，它将永远有蜜蜂（也就是说，蜂群不移动，但它生长）。

换句话说，蜜蜂的分布如下：当蜜蜂警报响起时，蜜蜂只占据蜂巢所在的格子。在第一分钟结束时，它们占据了蜂巢附近所有长满草的格子（以及原本的所有蜂巢）。在第二分钟结束时，它们又占据了和 “与蜂巢相邻的草格子” 相邻的草格子，以此类推。只要有足够的时间，这些蜜蜂就会同时占据森林中它们能到达的所有草格子。

Mecho 和蜜蜂都不能走出森林。另外，根据上面的规则，Mecho 总是吃整数分钟的蜂蜜。

如果 Mecho 发现自己在一个被蜜蜂占据的格子里，蜜蜂就会抓住 Mecho。

**任务**：编写一个程序，给定一张森林地图，计算出  Mecho 可以在最初的位置继续吃蜂蜜的最长时间，同时还能在任何蜜蜂抓到他之前回到他的家。

## 说明/提示

### 样例解释

- 样例 1：吃了一分钟蜂蜜后，Mecho 可以沿着最短的路径直接往右走，再过两分钟他就可以安全到家了。

- 样例 2：吃了两分钟蜂蜜后，Mecho 可以在第三分钟向右，向上，向右走；在第四分钟向右走三步；在第五分钟向下，向右走。

### 数据范围与约定

- 对于 $40\%$ 的数据，$N\leq 60$。
- 对于 $100\%$ 的数据，$1\leq N\leq 800$，$1\leq S\leq 1000$。

注意在实际评测中，部分分和以上描述有出入。

## 样例 #1

### 输入

```
7 3
TTTTTTT
TGGGGGT
TGGGGGT
MGGGGGD
TGGGGGT
TGGGGGT
THHHHHT
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7 3
TTTTTTT
TGGGGGT
TGGGGGT
MGGGGGD
TGGGGGT
TGGGGGT
TGHHGGT
```

### 输出

```
2
```

# 题解

## 作者：zhzkiller (赞：7)

## 题外话
我本人写题解本来不写这个。

它不是紫题，为什么也要卡我 3 个小时！！！

## 题目描述 
这道题要求我们求出一个最大的等待时间，使得小熊 Mecho 能够及时回到家里而不被蜜蜂堵住去路。

## 解题思路（正解）
很容易看出来这是一道广搜题，再一看就能看出来这是经典的双向 bfs 算法，而且本题答案具有单调性（更小的答案一定满足，更大的答案一定不满足）。我们只需每次二分答案后进行合法检查，具体表现为让小熊先搜 $S$ 步后让蜜蜂也搜 $1$ 步，看小熊是否能在 bfs 结束前到达终点即可。

**请注意 此题解不是上述算法。**

如果想练习双向 bfs 请移步它处。

## 解题思路（本人解法）

还是广搜和二分答案不变，我的做法是将蜜蜂所经过的路径打上类似时间戳的标记，在每次合法检查时仅对小熊进行移动，并实时与标记数组进行比较。该做法优点是比双向 bfs 好想，也好实现，缺点是有过多很细的细节需要注意，修死我了。

这个题解主要作用在于补充做题思路和服务想 AC 本题但是没有系统学习过双向 bfs 的同学。如果你没有更好的算法，那就和我一起坐牢吧~

完结撒花~

献上蒟蒻的 AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=810;

int n,k;
int stx,sty,edx,edy;
char a[N][N];
int dfn[N][N],d[N][N],cnt[N][N];
bool vis[N][N],v[N][N];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
queue< pair<int,int> > Q;

bool check(int t)
{
	memset(v,0,sizeof(v));
	Q.push({stx,sty});
	v[stx][sty]=true;d[stx][sty]=t==-1?0:t;
	while(Q.size())
	{
		int sx=Q.front().first,sy=Q.front().second;Q.pop();
		if(t==-1&&d[sx][sy]>dfn[sx][sy]) continue;
		if(sx==edx&&sy==edy)
		{
			while(Q.size()) Q.pop();
			return true;
		}
		int now=(d[sx][sy]-(t==-1?0:t))%k?(d[sx][sy]-(t==-1?0:t))/k+1:(d[sx][sy]-(t==-1?0:t))/k;
		for(int i=0;i<4;i++)
		{
			int tx=sx+dx[i],ty=sy+dy[i];
			if(tx&&ty&&tx<=n&&ty<=n&&!v[tx][ty]&&(a[tx][ty]=='G'||a[tx][ty]=='D')&&
			((t==-1?0:t)+now<dfn[tx][ty]-(k==1?k:0)||(t==-1?0:t)+now==dfn[tx][ty]
			-(k==1?k:0)&&cnt[sx][sy]!=(k-1?k-1:k))&&(now!=0||t+1<=dfn[tx][ty]))
			{
				if(cnt[sx][sy]==k&&t+now+1>dfn[tx][ty]) continue;
				v[tx][ty]=true;
				Q.push({tx,ty});
				if(t==-1)
				{
					cnt[tx][ty]=cnt[sx][sy]+1;
					if(cnt[tx][ty]==k+1)
					{
						d[tx][ty]=d[sx][sy]+1;
						cnt[tx][ty]=1;
					}
					else d[tx][ty]=d[sx][sy];
				}
				else d[tx][ty]=d[sx][sy]+1;
			}
		}
	}
	return false;
}

void bfs()
{
	dfn[edx][edy]=1e9;cnt[stx][sty]=k;
	while(Q.size())
	{
		int sx=Q.front().first,sy=Q.front().second;Q.pop();
		for(int i=0;i<4;i++)
		{
			int tx=sx+dx[i],ty=sy+dy[i];
			if(tx&&ty&&tx<=n&&ty<=n&&!vis[tx][ty]&&(a[tx][ty]=='G'||a[tx][ty]=='M'))
			{
				if(!dfn[tx][ty]) dfn[tx][ty]=dfn[sx][sy]+1;
				Q.push({tx,ty});vis[tx][ty]=true;
			}
		}
	}
}

int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='H') Q.push({i,j}),vis[i][j]=true;
			else if(a[i][j]=='M') stx=i,sty=j;
			else if(a[i][j]=='D') edx=i,edy=j;
		}
	}
	
	bfs();
	
	if(!check(-1))
	{
		printf("-1");
		return 0;
	}
	
	int l=0,r=n*n;
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(mid<dfn[stx][sty]&&check(mid)) l=mid;
		else r=mid-1;
	}
	printf("%d",l);
	return 0;
}
```

### 必要细节

1.多测必清空，队列要出完。

2.蜜蜂并不能占领小熊的家，即：

```cpp
a[tx][ty]!='D';
```

3.二分注意上下界及如何取 `mid` 的问题。

### 此代码细节

1.`mid<dfn[stx][sty]` 时可以不进搜索直接二分，优化不少。

2.时刻记得保持 `d[sx][sy]<=dfn[sx][sy]`。

### 注：题解代码仅供参考，可自行二次缩减优化，但严禁抄袭。

---

## 作者：lyhqwq (赞：1)

# Solution

一眼题。

如果小熊一次只能走一步，无脑搜索即可，考虑如何处理小熊走 $s$ 步的情况。

我们把一次走多步的情况变为一次走多步的情况，我们将蜜蜂走一格视为走 $s$ 步， bfs 预处理出蜜蜂扩展到某个格子所需要的最少步数。

然后显然是二分答案， bfs 判定即可。

十分简单。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=805;
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};
struct node{
    int x,y,step;
};
int n,m,sx,sy,ex,ey,cnt;
int Maxt[N][N],Minstp[N][N];
char a[N][N];
queue<node> q;
int check(int k){
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) Minstp[i][j]=1e9;
    while(!q.empty()) q.pop();
    q.push((node){sx,sy,k*m});
    while(!q.empty()){
        node u=q.front();
        q.pop();
        int x=u.x,y=u.y,stp=u.step;
        if(stp>=Maxt[x][y]) continue;
        if(x==ex&&y==ey) return 1;
        if(stp>=Minstp[x][y]) continue;
        Minstp[x][y]=stp;
        for(int o=0;o<4;o++){
            int nx=x+dx[o],ny=y+dy[o];
            if(nx<=0||nx>n||ny<=0||ny>n||a[nx][ny]=='T') continue;
            q.push((node){nx,ny,stp+1});
        }
        q.push((node){x,y,stp+1});
    }
    return 0;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",a[i]+1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][j]=='H') q.push((node){i,j,0});
            if(a[i][j]=='M') sx=i,sy=j;
            if(a[i][j]=='D') ex=i,ey=j;
            cnt+=(a[i][j]=='T');
            Maxt[i][j]=1e9;
        }
    }
    while(!q.empty()){
        node u=q.front();
        q.pop();
        int x=u.x,y=u.y,stp=u.step;
        if(stp>=Maxt[x][y]) continue;
        Maxt[x][y]=stp;
        for(int o=0;o<4;o++){
            int nx=x+dx[o],ny=y+dy[o];
            if(nx<=0||nx>n||ny<=0||ny>n||a[nx][ny]=='T'||a[nx][ny]=='D') continue;
            q.push((node){nx,ny,stp+m});
        }
    }
    int l=0,r=n*n-cnt,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：XSS_Worm (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P9116)

# 本题解亮点：

- 不需要双向广搜。
- 用普及组方法也能做！

# 大致思路

1. bfs 蜜蜂在各个时间点会到达的地方。

2. 二分答案，枚举小熊等待时长。

# 具体实现

1. 读入地图。

2. 进行第一轮 bfs，求蜜蜂占领各个点需要的时间。我们先将所有蜜蜂的初始位置加入队列，随后再把相邻的单元格入队。

3. 二分小熊等待时长。每一次二分校验时，需要再跑一次 bfs，而且 bfs 时要设一个时间戳，每到一个点，看他是否超时。对于   $l$ 和 $r$，如果 $mid$ 合法，则将 $l$ 赋值为 $mid$，否则将 $r$ 赋值为 $mid-1$，

#### OK，我们可以开始愉快地写代码了（本蒟蒻代码暴丑，大佬勿喷）

```cpp
#include <bits/stdc++.h>
#define array(x, j) \
    for (int i = 0; i < j; i++) cout << x[i] << " ";
#define ln cout << endl;
#define rpp(i, n) for (int i = 1; i <= n; i++)
#define rep(i, n) for (int i = 0; i < n; i++)
#define bk(i, st, ed) for (int i = st; i >= ed; i--)
#define debug(x) cout << #x << " : " << x << " , on line " << __LINE__ << endl;
#define pb push_back
#define pf push_front
#define iter iterator
#define fi first
#define se second
#define ll long long
using namespace std;
void file(string x) {
    freopen((x + ".in").c_str(), "r", stdin);
    freopen((x + ".out").c_str(), "w", stdout);
}
inline int read() {
    int f = 1, s = 0;
    char c = getchar();
    for (; (c < '0' || c > '9') && c != '-'; c = getchar())
        ;
    if (c == '-') {
        f = -1;
        c = getchar();
    }
    for (; c >= '0' && c <= '9'; c = getchar()) s = (s << 1) + (s << 3) + c - 48;
    return s * f;
}
void FastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
template <class Tp>
inline void input(Tp &x) {
    cin >> x;
}
template <class Tp, class... Oth>
inline void input(Tp &x, Oth &... y) {
    input(x), input(y...);
}
template <class Tp>
inline void print(Tp x) {
    cout << x << " ";
};
template <class Tp, class... Oth>
inline void print(Tp x, Oth... y) {
    print(x), print(y...), cout << endl;
}
const int N = 805;
const int dx[] = { -1, 1, 0, 0 };
const int dy[] = { 0, 0, -1, 1 };
char mp[N][N];
bool vis[N][N];
int t[N][N];
int n, s;
struct pos {
    int x, y;
};
struct node {
    int x, y, stp, used;
};
vector<pos> bee;
pos st;
pos ed;
inline bool chk(int x, int y) {
    return x > 0 and x <= n and y > 0 and y <= n and mp[x][y] != 'T' and mp[x][y] != 'D';
}
inline bool chk1(int x, int y, int z) {
    return x > 0 and x <= n and y > 0 and y <= n and !vis[x][y] and t[x][y] > z;
}
void bfs() {
    memset(t, -1, sizeof(t));
    queue<node> q;
    rep(i, bee.size()) {
        q.push({ bee[i].x, bee[i].y, 0 });
        t[bee[i].x][bee[i].y] = 0;
    }
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        int x = cur.x;
        int y = cur.y;
        rep(i, 4) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (chk(xx, yy) and t[xx][yy] == -1) {
                t[xx][yy] = cur.stp + 1;
                q.push({ xx, yy, cur.stp + 1 });
            }
        }
    }
}
bool calc(int x) {
    memset(vis, 0, sizeof(vis));
    queue<node> q;
    if (t[st.x][st.y] <= x)
        return false;
    q.push({ st.x, st.y, x, 0 });
    vis[st.x][st.y] = 1;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        int x = cur.x;
        int y = cur.y;

        if (cur.x == ed.x and cur.y == ed.y) {
            return true;
        }
        rep(i, 4) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (cur.used + 1 == s) {
                if (chk1(xx, yy, cur.stp + 1) or (ed.x == xx and ed.y == yy)) {
                    q.push({ xx, yy, cur.stp + 1, 0 });
                    vis[xx][yy] = 1;
                }
            } else {
                if (chk1(xx, yy, cur.stp) or (ed.x == xx and ed.y == yy)) {
                    q.push({ xx, yy, cur.stp, cur.used + 1 });
                    vis[xx][yy] = 1;
                }
            }
        }
    }
    return false;
}
int main() {
    input(n, s);
    rpp(i, n) {
        scanf("%s", mp[i] + 1);
        rpp(j, n) {
            if (mp[i][j] == 'M') {
                st = { i, j };
            }
            if (mp[i][j] == 'D') {
                ed = { i, j };
            }
            if (mp[i][j] == 'H') {
                bee.pb((pos){ i, j });
            }
        }
    }
    bfs();
    int l = 0, r = n * n;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (calc(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    if (calc(l)) {
        print(l);
    } else {
        print(-1);
    }
    return 0;
}
```


---

## 作者：Jerrywang09 (赞：1)

## 解析

暴力二分答案+搜索题。单调性易于看出，重点在于搜索验证。很暴力，没什么好说的。

但是，有很多坑点，我碰到了，希望各位不要碰到：

1. ```cpp
   while(!Q.empty() && Q.front().s<wait)
   ```
   必须在没有取出队头元素前判断时间是否越界。不然，取出后，因为这个队列对后面有影响，会导致一些区域应该被蜜蜂占领的却没被标记。

2. 严格遵循题目描述：小熊先走，蜜蜂后走。

3. 小熊的家 `D` 蜜蜂不可入。

4. ```cpp
   memset(vis, 0, sizeof(vis));
   ```
   ```cpp
   vis[start.x][start.y]=1;
   ```
   这两句话的次序问题。

这样，这题就解决了。看上去这题很吓人，实际上算法也不高端。但是细节很多，码量巨大。详见代码。

## 代码

```cpp
// C
/*
Input
7 3
GGGGGGG 
GTTGTTG
GTTGTTG
MTTGTTD
GTTGTTG
GGGGGGG
HHHHHHH
Output
2

Input
5 1
DGMGG
GGGGG
GGGGG
GGGGG
GHGHG
Output
2
*/
#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
#define SIZE 805
#define all(x) x.begin(), x.end()
#define debug(x) cout<<#x<<":"<<x<<endl;
using namespace std;

int n, mxstep;
char a[SIZE][SIZE];
bool vis[SIZE][SIZE];
bool bee[SIZE][SIZE];
struct node
{
	int x, y;
	int s;
	bool operator ==(node b)
	{
		return x==b.x && y==b.y;
	}
};
vector<node> hive;
node start;
node endpo;

int dx[]={-1, 1, 0, 0};
int dy[]={0, 0, -1, 1};

bool bfs(int wait)
{
	queue<node> q;	// bear
	q.push(start);
	queue<node> Q;	// bee
	memset(vis, 0, sizeof(vis));
	memset(bee, 0, sizeof(bee));
	vis[start.x][start.y]=1;
	for(node t:hive)
	{
		bee[t.x][t.y]=1;
		Q.push(t);
	}
	// 吃蜜时间蜜蜂围攻 
	while(!Q.empty() && Q.front().s<wait)
	{
		node w=Q.front(); Q.pop();
		int i=w.x, j=w.y;
		for(int k=0; k<4; k++)
		{
			int ni=i+dx[k];
			int nj=j+dy[k];
			// 不越界 
			if(ni<0 || ni>=n || nj<0 || nj>=n)
				continue;
			// 不走回头路 
			if(bee[ni][nj])
				continue;
			// 不入禁区 
			if(a[ni][nj]=='D' || a[ni][nj]=='T')
				continue;
			bee[ni][nj]=1;
			Q.push({ni, nj, w.s+1});
		}
	}
	// 原始位置已被攻占 
	if(bee[start.x][start.y])
		return 0;
	int steps=1;	// 行走的次数 
	while(!q.empty())
	{
		// 小熊先走 
		while(!q.empty() && q.front().s<steps*mxstep)
		{
			node w=q.front(); q.pop();
			int i=w.x, j=w.y;
			if(w==endpo) return 1;
			if(bee[i][j]) continue;
			for(int k=0; k<4; k++)
			{
				int ni=i+dx[k];
				int nj=j+dy[k];
				// 不越界
				if(ni<0 || ni>=n || nj<0 || nj>=n)
					continue;
				// 不被蜜蜂蛰 
				if(bee[ni][nj])
					continue;
				// 不走回头路 
				if(vis[ni][nj])
					continue;
				// 不入禁区 
				if(a[ni][nj]=='T')
					continue;
				vis[ni][nj]=1;
				q.push({ni, nj, w.s+1});
			}
		}
		// 蜜蜂后走
		while(!Q.empty() && Q.front().s<wait+steps)
		{
			node w=Q.front(); Q.pop();
			int i=w.x, j=w.y;
			for(int k=0; k<4; k++)
			{
				int ni=i+dx[k];
				int nj=j+dy[k];
				// 不越界
				if(ni<0 || ni>=n || nj<0 || nj>=n)
					continue;
				// 不走回头路 
				if(bee[ni][nj])
					continue;
				// 不入禁区 
				if(a[ni][nj]=='D' || a[ni][nj]=='T')
					continue;
				bee[ni][nj]=1;
				Q.push({ni, nj, w.s+1});
			}
		}
		steps++;
	}
	return 0;
}

signed main()
{
	cin>>n>>mxstep;
	int si, sj;
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='H')
				hive.push_back({i, j, 0});
			if(a[i][j]=='M')
				start={i, j, 0};
			if(a[i][j]=='D')
				endpo={i, j, 0};
		}
	int l=0, r=n*n;
	int ans=-1;
	while(l<=r)
	{
		int m=(l+r)>>1;
		if(bfs(m))
		{
			ans=m;
			l=m+1;
		}
		else
			r=m-1;
	}
	cout<<ans;

    return 0;
}
```

---

## 作者：_EternalRegrets_ (赞：0)

## 题目描述

地图中有一只小熊，它在 $M$ 地方开始。

还有一些蜜蜂，它们在 $0$ 时刻都在 $H$ 地方。

每一分钟，小熊可以走 $S$ 步，而蜜蜂会向四周走一步。

小熊不可以走到被蜜蜂走到过的地方。

地图中还有一些树，用 $T$ 标出，小熊和蜜蜂都不可以进入。

## 解题思路

从蜜蜂扩散区域这个题目要素，就很容易想到用广搜求出每个格子被蜜蜂走到的最短时间。

而二分答案求解最长等待时间。

对于小熊一分钟可以走 $S$ 步的条件，可以将小熊走到某一个地方的总时间除以 $S$。（还有一种方法是将蜜蜂的速度看为是每 $S$ 分钟一格 , 小熊是每一分钟一格）

码量很大，注意细节。

## 代码:（有些地方写的有点怪，请见谅）
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

struct node{
	int x;
	int y;
	int t;
};

struct pt{
	int x;
	int y;
};

const int dx[10]={0,0,0,1,-1};
const int dy[10]={0,1,-1,0,0};

char a[805][805];
int t[805][805];
int f[805][805];

int n,s;
bool vis[805][805];
void bfs1(){
	queue <node> q;
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]=='H'){
				t[i][j]=0;
				q.push({i,j,0});
			}
		}
	}
	
	memset(vis,0,sizeof vis);
	
	while(!q.empty()){
		//cout<<"/";
		node p; p=q.front(); q.pop();
		for(int i=1;i<=4;i++){
			int nx,ny; nx=p.x+dx[i]; ny=p.y+dy[i];
			if(nx>=1 && ny>=1 && nx<=n && ny<=n && !vis[nx][ny] && a[nx][ny]!='T' && a[nx][ny]!='D' && p.t+1<=t[nx][ny]){
				vis[nx][ny]=1;
				t[nx][ny]=p.t+1;
				q.push({nx,ny,p.t+1});
				//cout<<"*"<<p.x<<" "<<p.y<<" "<<nx<<" "<<ny<<" "<<p.t<<" "<<p.t+s<<endl;
			}
		}
	}
}

int xd,yd; int xm,ym;
int ans=0x3f3f3f3f;

int bfs2(int mid){ //check
	queue <pt> q;
	q.push({xm,ym});
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f[i][j]=1e18;
		}
	}
	f[xm][ym]=0;
	
	while(!q.empty()){
		pt p; p=q.front(); q.pop();
		for(int i=1;i<=4;i++){
			int nx,ny; nx=p.x+dx[i]; ny=p.y+dy[i];
			if(nx>=1 && ny>=1 && nx<=n && ny<=n && (a[nx][ny]=='G' || a[nx][ny]=='D') && f[p.x][p.y]+1<f[nx][ny] && (f[p.x][p.y]+1)/s+mid<t[nx][ny]){
				f[nx][ny]=f[p.x][p.y]+1;
				q.push({nx,ny});
			}
		}
	} 
	/*
	cout<<endl<<mid<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<f[i][j]<<" ";
		}
		cout<<endl;
	}*/
	
	if(f[xd][yd]!=1e18){
		return 1;
	}
	
	return 0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	//freopen("mecho.in","r",stdin);
	//freopen("mecho.out","w",stdout);
	
	cin>>n>>s;
	
	memset(t,0x3f3f3f3f,sizeof t);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
			
			if(a[i][j]=='T'){
				t[i][j]=-1;
			}
			
			if(a[i][j]=='D'){
				xd=i; yd=j;
			}
			
			if(a[i][j]=='M'){
				xm=i; ym=j;
			}
		}
	}
	
	bfs1();
	
	t[xd][yd]=0x3f3f3f3f;
	/*
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<t[i][j]<<" ";
		}
		
		cout<<endl;
	}*/
	
	int l,r; l=0,r=t[xm][ym]-1;
	//cout<<l<<" "<<r<<endl;
	
	int ans; ans=-1;
	while(l<=r){
		int mid; mid=(l+r+1)/2;
		
		if(bfs2(mid)){
			l=mid+1;
			ans=mid;
		}
		else{
			r=mid-1;
		}
		
		//char c; cin>>c;
		//cout<<l<<" "<<r<<" "<<mid<<" "<<bfs2(mid)<<endl;
	}
	
	cout<<ans;
	return 0;
}
```

---

## 作者：qzhwlzy (赞：0)

### 题目大意

给定一张地图。其中 `T` 表示树，`G` 表示草地，`H` 表示蜂巢，`M` 表示起点，`D` 表示终点。有一只小熊开始在起点处，每一分钟可以走 $s$ 步（一步定义为移动到上下左右之一的一个格子上），不能走到树上。蜜蜂在蜂巢处，每一分钟会往外扩散一格，能扩散到起点，不能到终点。每分钟小熊先动，蜜蜂后动。问小熊最晚何时出发能不碰到蜜蜂到终点。

[题面](https://www.luogu.com.cn/problem/P9116)

### 思路

首先蜜蜂的扩散是确定的，于是我们可以先 BFS 搜到每个点蜜蜂最早什么时候会到。

然后由于答案具有单调性，即若某时刻可行，其之前的时刻也一定可行，于是我们可以二分答案，用 BFS 检验即可。

### 代码

~~代码有点难写。~~

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#define maxn 805
#define pii pair<int,int>
#define m_p make_pair
#define a_f first
#define a_s second
using namespace std;
int n,s,tim[maxn][maxn],stx,sty; bool vis[maxn][maxn]; char ch; queue<pii> q;
int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
// tim[i][j] 表示蜜蜂扩散到 (i,j) 的时间
void bfs(){
	while(!q.empty()){
		pii top=q.front(); q.pop(); for(int i=0;i<4;i++){
			int nx=top.a_f+dx[i],ny=top.a_s+dy[i];
			if(!tim[nx][ny]&&!vis[nx][ny]&&nx>0&&nx<=n&&ny>0&&ny<=n)
				vis[nx][ny]=1,tim[nx][ny]=tim[top.a_f][top.a_s]+1,q.push(m_p(nx,ny));
		}
	}
}
int ti[maxn][maxn],st[maxn][maxn];
// ti[i][j] 和 st[i][j] 表示到达点 (i,j) 要走的分钟数和当前分钟内的步数
bool check(int t){
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) vis[i][j]=ti[i][j]=0; ti[stx][sty]=t+1;
	while(!q.empty()) q.pop(); vis[stx][sty]=1; q.push(m_p(stx,sty)); while(!q.empty()){
		pii top=q.front(); q.pop(); if(tim[top.a_f][top.a_s]==1e9) return 1;
		for(int i=0;i<4;i++){
			int nx=top.a_f+dx[i],ny=top.a_s+dy[i];
			if(!(nx>0&&nx<=n&&ny>0&&ny<=n&&tim[nx][ny]!=2e9&&!vis[nx][ny])) continue;
			int resti=ti[top.a_f][top.a_s],resst=st[top.a_f][top.a_s]+1; if(resst==s+1) resti++,resst=1;
			if(tim[nx][ny]>=resti&&!(tim[nx][ny]==resti&&resst==s))
				ti[nx][ny]=resti,st[nx][ny]=resst,vis[nx][ny]=1,q.push(m_p(nx,ny));
		}
	}
	return 0;
}
int main(){
	scanf("%d%d",&n,&s); for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
		scanf("%c",&ch); while(ch=='\n') scanf("%c",&ch);
		if(ch=='T') tim[i][j]=2e9; if(ch=='M') stx=i,sty=j;
		if(ch=='D') tim[i][j]=1e9; if(ch=='H') q.push(m_p(i,j)),vis[i][j]=1;
	} bfs(); int l=0,r=min(tim[stx][sty],n*n),mid,ans=-1;
	// 蜜蜂会扩散到起点，于是从扩散到起点的时间为上界
	while(l<=r){mid=(l+r)>>1; if(check(mid)) ans=mid,l=mid+1; else r=mid-1;} printf("%d",ans); return 0;
}
```

---

