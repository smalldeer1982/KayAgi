# Kilani and the Game

## 题目描述

有一个n行m列的棋盘和k个玩家，玩家从1到k编号。棋盘上每一格有可能是空格（用'.'表示）、墙（用'#'表示）或者某个玩家的城堡（用该玩家的编号表示）。从一个格子可以到任意一个与它有公共边的格子。
玩家i在一步操作内可以这样做：

1.找到所有与自己的任意一个城堡中间有一条长度不大于a[i]路线的空格（该路线上只能有空格和自己的城堡）。

2.把所有这样的格子都建成自己的城堡。
从玩家1开始，大家轮流操作。当任何人都无法执行操作时，游戏结束。
问：当游戏结束时，每个玩家分别有几座城堡？

## 样例 #1

### 输入

```
3 3 2
1 1
1..
...
..2
```

### 输出

```
6 3 
```

## 样例 #2

### 输入

```
3 4 4
1 1 1 1
....
#...
1234
```

### 输出

```
1 4 3 3 
```

# 题解

## 作者：pzc2004 (赞：7)

[题目传送门](https://www.luogu.org/problem/CF1105D)

这题思路不难想，直接按照题意模拟，每个回合找出每个玩家能到达的所有空格，把这些空格全部标记为他的城堡。

然后就是怎么找的问题了，这里我用的是BFS，给每个玩家开两个队列，队列2记录这一回合到达的最远的点，作为下一回合的起点，队列1记录将要遍历的点，每个回合开始时只需将队列2中的点丢入队列1即可。

代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,p,a[1005][1005],v[10],cas[10],s,l;//a[i][j]记录i行j列的点的状态，v[i]记录玩家i每回合可以移动的路程，cas[i]记录玩家i当前拥有的城堡，s记录剩余的空格数，l记录循环次数（防超时）
struct sb//记录点的状态
{
	int a,b,s;//a，b记录坐标，s记录剩余移动次数
};
queue<sb>q1[10],q2[10];//q1即描述中的队列1，q2级描述中的队列2
int main()
{
	//freopen("sb.in","r",stdin);
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1;i<=p;i++)scanf("%d",&v[i]);
	for(int i=1;i<=n;i++)
	{
		char c[m];
		scanf("%s",c);
		for(int j=1;j<=m;j++)
		{
			if(c[j-1]=='.'){a[i][j]=-2;s++;}//如果是空格就将空格数+1，将a[i][j]标为-2
			else if(c[j-1]=='#')a[i][j]=-1;//如果是墙就将a[i][j]标为-1
			else {cas[c[j-1]-'0']++;a[i][j]=c[j-1]-'0';q2[c[j-1]-'0'].push(sb{i,j,v[c[j-1]-'0']});}//如果是城堡就将a[i][j]标为该玩家，将该玩家的城堡数+1，将该点推入队列2
		}
	}
	int i=1;//i表示当前是玩家i的回合
	while(1)//开始模拟
	{
		q1[i]=q2[i];//每个回合开始时将队列2中的点丢入队列1
		while(!q2[i].empty())q2[i].pop();//清空队列2
		while(!q1[i].empty())//开始广搜
		{
			sb kkk=q1[i].front();
			q1[i].pop();
			if(kkk.s==0){q2[i].push(sb{kkk.a,kkk.b,v[i]});continue;}//如果移动不了了就将该点推入队列2，作为下一回合的起点
			if(a[kkk.a-1][kkk.b]==-2){cas[i]++;s--;if(s==0)break;q1[i].push(sb{kkk.a-1,kkk.b,kkk.s-1});a[kkk.a-1][kkk.b]=i;}//如果上下左右还未遍历就遍历,并将空格数减一，将该玩家的城堡数+1
			if(a[kkk.a][kkk.b-1]==-2){cas[i]++;s--;if(s==0)break;q1[i].push(sb{kkk.a,kkk.b-1,kkk.s-1});a[kkk.a][kkk.b-1]=i;}
			if(a[kkk.a+1][kkk.b]==-2){cas[i]++;s--;if(s==0)break;q1[i].push(sb{kkk.a+1,kkk.b,kkk.s-1});a[kkk.a+1][kkk.b]=i;}
			if(a[kkk.a][kkk.b+1]==-2){cas[i]++;s--;if(s==0)break;q1[i].push(sb{kkk.a,kkk.b+1,kkk.s-1});a[kkk.a][kkk.b+1]=i;}
		}
		if(s==0)break;//如果没有空格了就退出
		i=i%p+1;//换成下一个玩家
		l++;//循环次数+1
		if(l==10000000)break;//游戏次数不可能超过10000000，因此如果超出就说明是玩家被墙卡住了，直接退出防TLE
	}
	for(int i=1;i<=p;i++)printf("%d ",cas[i]);//输出
}
```
![](https://www.luogu.org/images/congratulation.png)

---

## 作者：hsfzLZH1 (赞：6)

## 题目大意

给出一个 $n\times m$ 的地图，并给出玩家个数 $p$ ，每个玩家有一个速度 $s_i$。地图上的一点若是 `#` ，代表有障碍；若是 `.` ，代表是空地；若是数字，则代表是一名玩家的城堡，数字即是该玩家的编号。每个玩家按照顺序轮流操作，每次操作找到所有从所有自己的城堡开始，能在 $s_i$ 步及之内，只往上下左右方向走，不经过和到达障碍和其他玩家的城堡所能到达的点，所能到达的点，并在这些点上放上自己的城堡。直到没有玩家能再扩张自己的领土为止。输出每名玩家城堡的个数。

$1\le n,m\le 1000,1\le p\le 9,1\le s_i\le 10^9$

## 解题思路

这是一道很裸的 BFS 题。唯一的问题就是保证时间复杂度。

首先，如果一个人的领地无法继续扩展，则停止扩展（不管 $s_i$ 有多大）。

其次，如果从这个点开始已经被扩展过，则不再从这个点开始扩展。因为再次扩展没有意义，这样做也保证了时间复杂度。

只需开 $9$ 个 `queue` ，轮流 BFS ，共用一个地图，保证不重复在节点上建城堡，模拟扩展就行了。

在具体的代码实现中，可以每次按照速度为 $1$ 的扩展，速度为 $s_i$ 就扩展 $s_i$ 次，如果中间不能继续扩展则停止。

由于每个点都只会被扩展并访问到一次，所以时间复杂度是 $O(nm)$ 的。空间复杂度也是 $O(nm)$ 的。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=1010;
const int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
typedef long long ll;
int n,m,p,s[maxn],ans[maxn];
char mp[maxn][maxn];
struct node{int x,y,t;}x;
queue<node>q[10];
int main()
{
	memset(s,'#',sizeof s);
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1;i<=p;i++)scanf("%d",s+i);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
	{
		scanf(" %c",mp[i]+j);
		if(mp[i][j]>='1'&&mp[i][j]<='9')
		{
			q[mp[i][j]-'0'].push((node){i,j,0});
			ans[mp[i][j]-'0']++;
		}
	}
	while(1)
	{
		bool tf=true;
		for(int i=1;i<=p;i++)if(!q[i].empty())tf=false;
		if(tf)break;
		//for(int i=1;i<=n;i++){for(int j=1;j<=m;j++)printf("%c",mp[i][j]);printf("\n");}
		//getchar();
		for(int i=1;i<=p;i++)if(!q[i].empty())
		{
			int t=s[i];
			while(t--)
			{
			if(q[i].empty())break;
			int col=q[i].front().t;
			while(!q[i].empty())
			{
				x=q[i].front();
				if(x.t!=col)break;
				q[i].pop();
				for(int j=0;j<4;j++)
				{
					int tx=x.x+dx[j],ty=x.y+dy[j];
					if(mp[tx][ty]=='.')
					{
						mp[tx][ty]=i+'0';
						ans[i]++;
						q[i].push((node){tx,ty,col+1});
					}
				}
			}
			}
		}
	}
	for(int i=1;i<=p;i++)printf("%d ",ans[i]);printf("\n");
	return 0;
}
```

---

## 作者：XCDRF_ (赞：1)

# CF1105D Kilani and the Game 题解

[原题传送门](https://codeforces.com/problemset/problem/1105/D)

[更好的阅读体验](https://www.luogu.com.cn/article/rvppa4in)

## 题目大意

有一个 $n \times m$ 的地图，有 $p$ 个人。地图上的一点若是 `#`，代表有障碍；若是 `.`，代表是空地；若是数字，代表是一个人的领地，数字即是这个人的编号，每个人在开始时可有一个或多个领地。之后每个玩家按照顺序轮流操作，每轮操作从这个人所有的领地向外（四连通）扩张 $s_i$ 格，不能经过障碍或别人的领地，直到所有人都无法扩张。最后输出每个人的领地数量。

要求复杂度 $O(nm)$ 实现。

## 解题思路

看到向外扩张，首先想到 BFS。

共有 $p$ 个起点，考虑开 $p$ 个队列维护，每轮操作按顺序扩张 $s_i$ 格，直到所有人都无法扩张，程序结束。

在实际操作中，每次记录扩张格数。如果当前格数较上次扩张结束时的格数多了 $s_i$ 格以上，就停止扩张。在每轮扩张前都要判断是否还能扩张，如果不能就跳过。

所有格子最多只能被遍历一次，复杂度为 $O(nm)$，问题得解。

## 注意事项

1. 记得判断边界条件，已经被占领的格子或障碍不能扩张。
2. 每人每轮都要扩张，直到周围没有能扩张的格子。
3. 结束条件是所有队列都为空，所以每轮开始前，先看一下所有队列是否全部为空。

## 参考代码

```cpp
#include <iostream>
#include <queue>
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
using namespace std;
const int N=15,M=1e3+5;;
const int dx[]={0,1,-1,0,0};
const int dy[]={0,0,0,1,-1};
queue<pair<pii,int> > q[N];
int n,m,k;
int a[N],ans[N];
char c; 
bool vis[M][M];
bool check(int x,int y){
	if(vis[x][y]||x<1||x>n||y<1||y>m) return 0;
	return 1;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); 
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>c;
			if(c>='1'&&c<='9'){//判数字 
				q[c-'0'].push(mp(mp(i,j),0));
				ans[c-'0']++;
				vis[i][j]=1;
			}
			else if(c=='#') vis[i][j]=1;//判障碍 
		}
	while(1){//一直循环直到所有人都不能扩张 
		bool flag=0;
		for(int i=1;i<=k;i++)
			if(!q[i].empty()) flag=1;
		if(!flag) break;
		//开始一轮操作 
		for(int i=1;i<=k;i++){//所有人都要扩张 
			if(q[i].empty()) continue;//判断是否还能扩张
			int tmp=q[i].front().se;//上次扩张结束时的格数 
			while(!q[i].empty()){
				auto u=q[i].front();
				if(u.se>=tmp+a[i]) break;//每次让所有点向外扩张s[i]格 
				q[i].pop();
				for(int j=1;j<=4;j++){
					int xx=u.fi.fi+dx[j],yy=u.fi.se+dy[j];
					if(!check(xx,yy)) continue;
					vis[xx][yy]=1;
					ans[i]++;
					q[i].push(mp(mp(xx,yy),u.se+1));
				}
			}			
		}
	}
	for(int i=1;i<=k;i++) cout<<ans[i]<<" ";
	return 0;
}
```

[AC 记录](https://codeforces.com/contest/1105/submission/292599721)

感谢管理大大审核，求通过 QwQ。

---

## 作者：Christopher_Yan (赞：1)

[原题链接](https://codeforces.com/contest/1105/problem/D)

#### 解题思路
挺裸的BFS+模拟，只可惜我在考场上都没来得及看这道题一眼。
我们可以选择开p个队列分别进行BFS，每次BFS加入一层点，BFS $s[i]$次，一轮下来如果还有队列非空就再来一轮，不断BFS直到所有的队列都空了为止。

注意小坑：
1. 一个玩家不止又一个城堡（英语太差，读英文题面总是出锅）
2. 一旦有一个队列空了，就标记下来这个玩家，以后不要扩展，否则即使你扩展时在跳过的话，循环$s[i]$次也足以令人TLE（也行只有我会犯这么2的错误吧）。

#### AC代码
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

const int N = 1010;

int n, m, p, cnt;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int s[11], us[11], vis[N][N], ns[N], f[N][N], ans[N];
char in[N];

struct Node
{
	int lev, x, y;
}u;

queue <Node> Q[11];

inline void BFS(int now, int ste)
{
	if (us[now]) return;
	if (Q[now].empty()) ++cnt, us[now] = 1;
	while (!Q[now].empty())
	{
		u = Q[now].front();
		if (u.lev != ste) return;
		Q[now].pop();
		for (int i = 0; i < 4; ++i)
		{
			int nx = u.x + dx[i];
			int ny = u.y + dy[i];
			if (vis[nx][ny]) continue;
			vis[nx][ny] = 1, f[nx][ny] = now, 
			Q[now].push((Node){ste + 1, nx, ny});
		}
	}
}

int main()
{
	cin >> n >> m >> p;
	fill(ns + 1, ns + p + 1, 1);
	for (int i = 1; i <= p; ++i)
		cin >> s[i];
	for (int i = 1; i <= n; ++i)
	{
		scanf("%s", in + 1);
		for (int j = 1; j <= m; ++j)
			if (in[j] == '.');
			else if (in[j] == '#') vis[i][j] = -1;
			else vis[i][j] = 1, f[i][j] = int(in[j] - '0'), Q[f[i][j]].push((Node){1, i, j});
	}
	for (int i = 0; i <= n + 1; ++i) vis[i][0] = vis[i][m + 1] = 1;
	for (int i = 0; i <= m + 1; ++i) vis[0][i] = vis[n + 1][i] = 1;
	for (; cnt < p;)
	{
		for (int col = 1; col <= p; ++col)
			for (int i = 1; i <= s[col]; ++i)
				if (us[col]) break;
				else BFS(col, ns[col]), ++ns[col];
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			++ans[f[i][j]];
	for (int i = 1; i <= p; ++i)
		cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：liuli688 (赞：0)

### 思路
发现每个不为空的格子都只会被覆盖一遍，又发现玩家是向外扩张，因此想到 BFS。

对每个人建一个队列，轮流扩展。BFS 状态设为三维，分别为横纵坐标和扩展层数。对于每个玩家 $i$ 只需扩展 $s _ i$ 层即可。对扩展多层不明白的读者可以看一下 [P10487](https://www.luogu.com.cn/problem/P10487)。

在输入时将每个数字压入队列，当所有队列都为空时说明所有能到达的地方都被占领了，输出即可。
### 代码
```cpp
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <queue>

class State
{
public:
    int x, y, step;
};

constexpr int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

std::queue<State> q[10];
int n, m, p, s[10], ans[10];
char c[1001][1001];

signed main()
{
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= p; ++i)
        scanf("%d", s + i);
    for (int i = 1; i <= n; ++i)
        scanf("%s", (c[i] + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (isdigit(c[i][j]))
                q[c[i][j] - 48].push(State{i, j, 0});
    while (q[1].size() or q[2].size() or q[3].size() or q[4].size() or q[5].size() or q[6].size() or q[7].size() or q[8].size() or q[9].size())
        for (int i = 1; i <= 9; ++i)
        {
        	if (q[i].empty())
        		continue;
        	for (int st = q[i].front().step; q[i].size() and q[i].front().step < st + s[i]; )
            {
                int x = q[i].front().x, y = q[i].front().y, step = q[i].front().step;
                q[i].pop();
                for (int j = 0, xx, yy; j < 4; ++j)
                {
					xx = x + dx[j];
                    yy = y + dy[j];
                    if (c[xx][yy] == '.' and xx and xx <= n and yy and yy <= m)
                    {
                        c[xx][yy] = i + 48;
                        q[i].push(State{xx, yy, step + 1});
                    }
                }
            }
		}
            
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (isdigit(c[i][j]))
                ++ans[c[i][j] - 48];
    for (int i = 1; i <= p; ++i)
        printf("%d ", ans[i]);
    return 0;
}
```

---

## 作者：Merge_all (赞：0)

### 思路：
- 明显的一道广搜题目，只是增加了几个起点。
- 用 $p$ 个队列分别进行广搜，注意边界情况和什么时候**停止循环**。
- 具体做法：在输入时我们就可以判断输入是否是数字，是的话就先**加入队列**。在广搜时，先判断每个玩家是否还可以扩展城堡，**如果都不可以，就结束程序**。若**当前的不能扩展**，则**跳过这个玩家**。若可以扩展，则进行 $a_{i}$ 步的扩展。
- 代码中有注释，不懂可以看一看。
### 代码：
```
#include <bits/stdc++.h>
using namespace std;
const int N = 1000 + 10;
typedef pair<int, int> pi;
int n, m, p;
char mp[N][N];//地图
struct node {
	int x, y, t;
};
queue<node> q[10];//最多有十个人，先开十个队列
int s[N], ans[N];
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> p;
	for (int i = 1; i <= p; i ++)
		cin >> s[i];
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			cin >> mp[i][j];
			if (isdigit(mp[i][j])) {//如果是数字（一个玩家的起点）
				ans[mp[i][j] - '0'] ++;
				q[mp[i][j] - '0'].push({i, j, 0});
			}
		}
	}
	while (1) {//一直循环到每个队列都没有可去的地方才会结束
		bool flag = 1;
		for (int i = 1; i <= p; i ++) {
			if (!q[i].empty()) {
				flag = 0;
			}
		}
		if (flag)
			break;//判断结束
		for (int i = 1; i <= p; i ++) {
			int step = s[i];
			while (step --) {//一共走step步
				if (q[i].empty())
					break;//无路可走立刻停止
				int tmp = q[i].front().t;
				while (!q[i].empty()) {
					node u = q[i].front();
					if (u.t != tmp)
						break;
					q[i].pop();
					for (int e = 0; e < 4; e ++) {
						int nx = u.x + dx[e], ny = u.y + dy[e];
						if (mp[nx][ny] == '.' && nx >= 1 && nx <= n && ny >= 1 && ny <= m) {//判断能否到达（在不在图内，是否没有被占领）
							mp[nx][ny] = i + '0';
							ans[i] ++;
							q[i].push({nx, ny, tmp + 1});
						}
					}
				}
			}
		}
	}
	for (int i = 1; i <= p; i ++)
		cout << ans[i] << ' ';
	return 0;
}
```

---

## 作者：_dijkstra_ (赞：0)

小号不写题解就要掉屁用没有的咕值了。

## 思路

首先很显然，这题直接模拟就可以了。我们可以采取 bfs。

但是，如果只用一个队列来记录的话并不容易，所以我们可以**对每个玩家开一个队列**。

这样就比较容易了，只要全部队列不为空，直接每个队列往外同时扩张一格的地盘即可。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 1005, K = 15, dict[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
struct Node {int x, y;}; queue <Node> q[K];
int n, m, k;
int a[K], ans[K];
char map[N][N]; int dis[N][N];
bool not_empty() //全部队列是否为空
{
    for (int i = 1; i <= k; i++)
        if (!q[i].empty())
            return true;
    return false;
}
void bfs() //爆搜
{
    while (not_empty())
    {
        for (int i = 1; i <= k; i++)
            for (int _ = 1; !q[i].empty() && _ <= a[i]; _++)
            {
                int nowx = q[i].front().x, nowy = q[i].front().y;
                while (!q[i].empty())
                {
                    int x = q[i].front().x, y = q[i].front().y;
                    if (dis[nowx][nowy] != dis[x][y]) break;
                    q[i].pop();
                    for (int k = 0; k < 4; k++)
                    {
                        int dx = x + dict[k][0], dy = y + dict[k][1];
                        if (dx < 1 || dx > n || dy < 1 || dy > m) continue;
                        if (map[dx][dy] != '.' || dis[dx][dy]) continue;

                        map[dx][dy] = (i + '0'), ans[i]++;
                        q[i].push((Node){dx, dy}), dis[dx][dy] = dis[x][y] + 1;
                    }
                }
            }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) cin >> a[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            cin >> map[i][j];
            if ('1' <= map[i][j] && map[i][j] <= '9')
            {
                int pos = map[i][j] - '0';
                q[pos].push((Node){i, j}), ans[pos]++;
            }
        }
    bfs();
    for (int i = 1; i <= k; i++) cout << ans[i] << ' ';
    return 0;
}
```

---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/CF1105D)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;虽然是紫色的，但是并不难。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;如果每次一个人走的时候，都从他的每个城堡开始扩展，那么这个速度显然是极其慢的。我们需要丢弃那些即使不作为起点开始扩展，也不会使新一次扩展的增加城堡数量减小的那些城堡。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;该留下哪些呢？不难想到，应该是上一次扩展完成后最外面的那一圈城堡。内部的城堡所能扩展的显然都也能被外部城堡扩展到。于是我们可以在上一次的扩展完成后，将最外层的一圈新城堡存下来，下一次就直接从这些城堡开始继续扩展就可以了。由于游戏的过程只会导致整个地图全部被遍历一次，所以时间为$O(nm)$。
# 代码
```cpp
#include <queue>
#include <cstdio>
#include <utility>
using namespace std;

typedef pair<int, int> pos;
#define xx first
#define yy second

const int MAXN = 1005, MAXM = 1005, MAXP = 10;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar(); int f = 1;
	while( s < '0' || '9' < s ){ f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ){ x = ( x << 3 ) + ( x << 1 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ), x = -x; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

queue<pos> q[10], las[10];

int dir[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
int ans[MAXP];
char str[MAXM];
int s[MAXP];
int N, M, P;
int col[MAXN][MAXM], dist[MAXN][MAXM];

bool chk( const int x, const int y )
{
	return 1 <= x && x <= N && 1 <= y && y <= M && ! col[x][y];
}

bool expand( const int indx )
{
	bool flag = false; 
	pos head; int tx, ty;
	while( ! las[indx].empty() )
	{
		head = las[indx].front(); las[indx].pop();
		for( int i = 0 ; i < 4 ; i ++ )
		{
			tx = head.xx + dir[i][0], ty = head.yy + dir[i][1];
			if( chk( tx, ty ) ) q[indx].push( pos( tx, ty ) ), col[tx][ty] = indx, dist[tx][ty] = 1, flag = true;
		}
	}
	while( ! q[indx].empty() )
	{
		head = q[indx].front(); q[indx].pop();
		if( dist[head.xx][head.yy] == s[indx] ) { las[indx].push( head ); continue; }
		for( int i = 0 ; i < 4 ; i ++ )
		{
			tx = head.xx + dir[i][0], ty = head.yy + dir[i][1];
			if( chk( tx, ty ) ) 
				q[indx].push( pos( tx, ty ) ), col[tx][ty] = indx, dist[tx][ty] = dist[head.xx][head.yy] + 1, flag = true;
		}
	}
	return flag;
}

int main()
{
	read( N ), read( M ), read( P );
	for( int i = 1 ; i <= P ; i ++ ) read( s[i] );
	for( int i = 1 ; i <= N ; i ++ )
	{
		scanf( "%s", str + 1 );
		for( int j = 1 ; j <= M ; j ++ )
		{
			if( str[j] == '#' ) col[i][j] = -1;
			else if( str[j] ^ '.' ) 
				col[i][j] = str[j] - '0', las[col[i][j]].push( pos( i, j ) ), dist[i][j] = 1;
		}
	}
	for( bool flag = false ; ; flag = false )
	{
		for( int i = 1 ; i <= P ; i ++ ) flag |= expand( i );
		if( ! flag ) break;
	}
	for( int i = 1 ; i <= N ; i ++ )
		for( int j = 1 ; j <= M ; j ++ ) 
			ans[col[i][j]] ++;
	for( int i = 1 ; i <= P ; i ++ ) 
		write( ans[i] ), putchar( i == P ? '\n' : ' ' );
	return 0;
}
```

---

## 作者：Zechariah (赞：0)

这题没什么方法...纯粹按照题意模拟  
p个人，我们就用p个队列bfs，bfs的过程中扩展的时候我用的是dfs，最后统计地图上每个人有多少棋子就行了  
关键是要读懂题，题目给出的s指的是曼哈顿距离，只要是距离当前地图上某玩家的棋子小于等于s的空格子都可以扩展
```cpp
#include <bits/stdc++.h>
#define jh(x,y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 1e3 + 5, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
    inl ll read()
    {
        rg ll num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg long long x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
bool flag[N][N];
char mp[N][N];
int p, n, m, s[N], head[10], tail[10], ans[10];
int dx[5] = { 0,0,0,1,-1 };
int dy[5] = { 0,1,-1,0,0 };
struct Node {
    int x, y;
    Node() {}
    Node(rg int x, rg int y) :x(x), y(y) {}
}q[10][N*N], fa;
void dfs(rg int p, rg int x, rg int y, rg int len)
{
    if (abs(x - fa.x) + abs(y - fa.y) >= len)return;
    for (rg int i = 1; i <= 4; ++i)
    {
        rg int fx = x + dx[i], fy = y + dy[i];
        if (fx<1 || fy<1 || fx>n || fy>m || flag[fx][fy] || mp[fx][fy] != '.')continue;
        q[p][++head[p]] = Node(fx, fy);
        flag[fx][fy] = true;
        mp[fx][fy] = p + '0';
        dfs(p, fx, fy, len);
    }
}
inl void bfs()
{
    while (1)
    {
        rg bool con = true;
        for (rg int i = 1; i <= p; ++i)if (head[i] >= tail[i]) { con = false; break; }
        if (con)break;
        for (rg int i = 1; i <= p; ++i)
        {
            if (head[i] < tail[i])continue;
            rg int last = head[i];
            while (tail[i] <= last)
            {
                rg Node k = q[i][tail[i]++]; fa = k;
                dfs(i, k.x, k.y, s[i]);
            }
        }
    }
}

int main(void)
{
    n = fast_IO::read(); m = fast_IO::read(); p = fast_IO::read();
    for (rg int i = 1; i <= p; ++i)s[i] = fast_IO::read(), tail[i] = 1;
    for (rg int i = 1; i <= n; ++i)
    {
        scanf("%s", mp[i] + 1);
        for (rg int j = 1; j <= m; ++j)
            if (mp[i][j] >= '1'&&mp[i][j] <= '9')
                q[mp[i][j] - '0'][++head[mp[i][j] - '0']] = Node(i, j), flag[i][j] = true;
    }
    bfs();
    for (rg int i = 1; i <= n; ++i)
        for (rg int j = 1; j <= m; ++j)
            if (mp[i][j] >= '1'&&mp[i][j] <= '9')
                ++ans[mp[i][j] ^ 48];
    for (rg int i = 1; i <= p; ++i)printf("%d ", ans[i]);
    return 0;
}

```

---

