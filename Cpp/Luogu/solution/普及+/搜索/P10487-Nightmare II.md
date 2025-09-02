# Nightmare II

## 题目描述

昨晚，小 erriyue 做了一个可怕的噩梦。他梦到自己和女朋友被困在一个大迷宫里。更可怕的是，迷宫里有两个鬼魂。它们会杀人。现在小 erriyue 想知道在鬼魂找到他们之前，他是否能找到他的女朋友。

假设小 erriyue 和他的女朋友可以向四个方向移动。在每一秒中，小 erriyue 可以移动 $3$ 步，而他的女朋友只能移动 $1$ 步。鬼魂是邪恶的，每一秒它们都会分裂成几部分，占领距离它们两步以内的网格，直到它们占领整个迷宫。你可以假设在每一秒钟，鬼魂首先分裂，然后小 erriyue 和他的女朋友开始移动，如果小 erriyue 或者他的女朋友到达一个有鬼魂的网格，他们就会死亡。

注意：新的鬼魂也可以像原来的鬼魂一样分裂。

## 样例 #1

### 输入

```
3
5 6
XXXXXX
XZ..ZX
XXXXXX
M.G...
......
5 6
XXXXXX
XZZ..X
XXXXXX
M.....
..G...

10 10
..........
..X.......
..M.X...X.
X.........
.X..X.X.X.
.........X
..XX....X.
X....G...X
...ZX.X...
...Z..X..X```

### 输出

```
1
1
-1```

# 题解

## 作者：齐芒 (赞：27)

**切入点**：男生和女友会同时的进行移动，所以考虑同时移动并且相聚时间最短。考虑多源点广搜。

（当然直接按照题目本身的表述意思就是双向广搜。）

* 多起点出发的时候，可以直接考虑男生和女友走的相同时间的队列扩展。
* 但是需要注意的是，本题因为男生会走三步，但是女友只能走一步，所以可以考虑先创建一个临时的队列，每次将男生走三步的所有点在临时队列之中扩展完成之后放入原队列，但是这样显然过于麻烦，并且最后的结构体之中需要多创建一个时间编号。
* 所以最终可以直接将男生和女友分开创建一个队列，也就是双向广搜的基本操作。如果每次二者都是移动一步，一个队列的写法也不错。

考虑创建开两个队列，分别存储男生和女友的移动点。

**注意点**

* 因为鬼魂的移动是按照时间记录步数的，比如鬼魂移动两步，可以先往右再往上，也可以先往上后往右，其实表述起来就是二者之间的曼哈顿距离小于两倍时间。所以记录一个全局的时间节点。
* 每次扩展的时候，男生和女友同时移动，相当于在一秒的时间单位内，先移动男生的所有上一层的节点，队列之中所有节点，扩展三次，后移动女友的所有上一层节点，扩展一次。当然交换二者之间的顺序关系也可以。
* 关于标记，采用三维的方式，最后一维表示是男生还是女生走过。

# Code

~~~cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 7;
char a[maxn][maxn];
int n, m;
struct Point
{
    int x, y;
    int flag; // 如果是0，表示是erriyue ，否则是他的女朋友
};
bool vis[maxn][maxn][2]; // 代表是否占领 最后一个维度表示是erriyue标记，还是女朋友标记的
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
vector<Point> op;         // 鬼魂存储的位置信息
int sum_t = 0;            // 总时间
int dis(Point A, Point B) // 曼哈顿距离计算
{
    return abs(A.x - B.x) + abs(A.y - B.y);
}

bool check1(int x, int y, int k) // 检查范围是否合法
{
    if (a[x][y] != 'X' && x >= 1 && x <= n && y >= 1 && y <= m && vis[x][y][k] == 0)
    {
        return true;
    }
    return false;
}
bool check2(Point A) // 检查是否会被追上
{
    for (int i = 0; i < 2; i++)
    {
        if (dis(A, op[i]) <= 2 * sum_t) // 说明被追上了
        {
            return false;
        }
    }
    return true;
}
queue<Point> Q1; // 男生
queue<Point> Q2; // 女生
int bfs()
{
    // 相当于是两个点的同时出发，多源点出发
    while (!Q1.empty() && !Q2.empty())
    {
        sum_t++;       // 时间+1
        int total = 3; // 代表总共的循环次数
        while (total--)
        {
            int len = Q1.size();
            while (len--) // 每一点都需要跑三次
            {
                Point u = Q1.front();
                Q1.pop(); // 直接删除
                if (!check2(Point{u.x, u.y}))
                {
                    continue;
                }
                for (int i = 0; i < 4; i++) // 四个方向
                {
                    int xx = u.x + dx[i];
                    int yy = u.y + dy[i];
                    if (check1(xx, yy, u.flag) && check2(Point{xx, yy}))
                    {
                        vis[xx][yy][u.flag] = 1;
                        if (vis[xx][yy][!u.flag] == 1)
                        {
                            return sum_t; // 说明找到答案了
                        }
                        Q1.push(Point{xx, yy, u.flag});
                    }
                }
            }
        }
        total = 1; // 代表总共的循环次数
        while (total--)
        {
            int len = Q2.size();
            while (len--) // 每一点都需要跑一次
            {
                Point u = Q2.front();
                Q2.pop(); // 直接删除
                if (!check2(Point{u.x, u.y}))
                {
                    continue;
                }
                for (int i = 0; i < 4; i++) // 四个方向
                {
                    int xx = u.x + dx[i];
                    int yy = u.y + dy[i];
                    if (check1(xx, yy, u.flag) && check2(Point{xx, yy}))
                    {
                        vis[xx][yy][u.flag] = 1;
                        if (vis[xx][yy][!u.flag] == 1)
                        {
                            return sum_t; // 说明找到答案了
                        }
                        Q2.push(Point{xx, yy, u.flag});
                    }
                }
            }
        }
    }
    return -1;
}
void init() // 清空
{
    memset(vis, 0, sizeof(vis));
    sum_t = 0; // 初始化操作
    while (!Q1.empty())
    {
        Q1.pop();
    }
    while (!Q2.empty())
    {
        Q2.pop();
    }
    op.clear();
    return;
}
int main()
{

    int t;
    cin >> t;
    while (t--)
    {
        init();
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cin >> a[i][j];
                if (a[i][j] == 'M') // 记录男生起点
                {
                    Q1.push(Point{i, j, 0});
                    vis[i][j][0] = 1;
                }
                if (a[i][j] == 'G') // 记录女生起点
                {
                    Q2.push(Point{i, j, 1});
                    vis[i][j][1] = 1;
                }
                if (a[i][j] == 'Z') // 鬼魂位置
                {
                    op.push_back(Point{i, j});
                }
            }
        }
        cout << bfs() << endl;
    }
    return 0;
}
~~~

---

## 作者：chzhh_111 (赞：8)

首先 BFS 启动。

设定一个 $time_{i,j}$，表示在 $time_{i,j}$ 秒之前都可以到达第 $i$ 行，第 $j$ 列的位置。则就有： 如果第 $i$ 行，第 $j$ 列的位置是 $\texttt{X}$，则 $time_{i,j} = 0$，除此之外其他无限大。

首先考虑鬼的情况，对于每一个鬼都以鬼为中心 BFS 一遍，同时对所经过的 $time_{i,j}$ 都去更新一下，则就有：$time_{i,j} = \min (time_{i,j},timeghost_{i,j})$，其中 $timeghost_{i,j}$ 为鬼到这个位置的时间。

接下来再考虑男孩和女孩的情况，设定两个数组，$timeboy_{i,j}$ 和 $timegirl_{i,j}$，表示，男孩和女孩分别到达第 $i$ 行，第 $j$ 列的位置所需的最少时间。所以现在只要对男孩和女孩的位置分别做一遍 BFS 就行了，在 BFS 的时候，对于能否往下走的标准是，到达下一个位置的时间是否小于那个位置目前记载的最小时间。

最后统计答案的时候就是看一下某一位置是否有 $timeboy_{i,j}$ 等于 $timegirl_{i,j}$，或者 $timeboy_{i,j}$ 等于 $timegirl_{i,j} + 1$，表示在 BFS 的过程中有没有男孩和女孩在同一个位置相遇的情况，然后取个最小值。没有任何一种情况相遇的话就输出 $-1$。

不过注意到鬼是一秒可移动两个单位，男孩是一秒可移动三个单位，因此还得在 BFS 的时候特殊实现一下。就是用另外一个变量去记载一下当前移动的步数，因此时间就是这个步数除以一秒内可移动的单位数，再向上取整。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1001;
int T,n,m,bx,by,gx,gy,times[N][N],tb[N][N],tg[N][N];char s[N][N];bool p[N][N];
int dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
struct dian{
	int x,y,ti,tim;
};
queue<dian>q,q1,q2;
void clean()
{
	memset(times,0x3f,sizeof(times));
	memset(tb,0x3f,sizeof(tb));
	memset(tg,0x3f,sizeof(tg));
}
void bfs1(int x,int y)
{
	memset(p,0,sizeof(p));
	q.push((dian){x,y,0,0});
	times[x][y]=0;
	p[x][y]=1;
	while(q.size())
	{
		dian u=q.front();
		q.pop();
		for(int i=0;i<4;i++)
		{
			int X=u.x+dx[i],Y=u.y+dy[i];
			if(X>=1&&X<=n&&Y>=1&&Y<=m&&!p[X][Y])
			{
				p[X][Y]=1;
				times[X][Y]=min(times[X][Y],u.ti+(!u.tim));
				q.push((dian){X,Y,u.ti+(!u.tim),(u.tim+1)&1});
			}
		}
	}
}
void bfs2()
{
	q1.push((dian){bx,by,0,0});
	q2.push((dian){gx,gy,0,0});
	tb[bx][by]=tg[gx][gy]=0;
	while(q1.size())
	{
		dian u=q1.front();
		q1.pop();
		if(u.ti+(!u.tim)>=times[u.x][u.y]) continue;
		for(int i=0;i<4;i++)
		{
			int X=u.x+dx[i],Y=u.y+dy[i];
			if(X>=1&&X<=n&&Y>=1&&Y<=m&&u.ti+(!u.tim)<times[X][Y]&&tb[X][Y]>u.ti+(!u.tim))
			{
				tb[X][Y]=u.ti+(!u.tim);
				q1.push((dian){X,Y,u.ti+(!u.tim),(u.tim+1)%3});
			}
		}
	}
	while(q2.size())
	{
		dian u=q2.front();
		q2.pop();
		if(u.ti+1>=times[u.x][u.y]) continue;
		for(int i=0;i<4;i++)
		{
			int X=u.x+dx[i],Y=u.y+dy[i];
			if(X>=1&&X<=n&&Y>=1&&Y<=m&&u.ti+1<times[X][Y]&&tg[X][Y]>u.ti+1)
			{
				tg[X][Y]=u.ti+1;
				q2.push((dian){X,Y,u.ti+1,0});
			}
		}
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		clean();
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
		for(int i=1;i<=n;i++)
		  for(int j=1;j<=m;j++)
		  {
			if(s[i][j]=='M') bx=i,by=j;
			if(s[i][j]=='G') gx=i,gy=j;
			if(s[i][j]=='X') times[i][j]=0;
			if(s[i][j]=='Z') bfs1(i,j);
		  }
		bfs2();
		int ans=1e9;
		for(int i=1;i<=n;i++)
		  for(int j=1;j<=m;j++)
		    if(tb[i][j]<1e9&&tg[i][j]<1e9&&(tb[i][j]==tg[i][j]||tb[i][j]==tg[i][j]+1)) ans=min(ans,tb[i][j]);\\tb[i][j]==tg[i][j]：女孩碰到男孩；tb[i][j]==tg[i][j]+1：男孩碰到女孩
		if(ans<1e9) printf("%d\n",ans);
		  else printf("-1\n");
	}
	return 0;
}
```

---

## 作者：sccc_ (赞：8)

## 分析
一道双向广搜的题目。  

我们可以考虑开两个队列分别维护两个人的坐标位置。  
（因为两个人一秒钟移动的步数不同。）  
***
如何处理标记问题？ 

我们可以在二维的基础上再增一维，这一位代表是男生走过还是女生走过。  
若 $vis_{i,j,0}$ 代表在 $(i,j)$ 这个点男生走过。  
若 $vis_{i,j,1}$ 代表在 $(i,j)$ 这个点女生走过。  
*** 
如何判断鬼魂在 $x$ 秒内能否到达这个点呢?

查看这个点到两个鬼魂位置的曼哈顿距离是否小于 $2x$ 即可。
***
注意点：  
多组数据数组清空。
***
```c++
#include <bits/stdc++.h>
using namespace std;

char a[1005][1005];
int n, m;
struct node
{
	int x, y;
	bool f; // 如果是0是erriyue 否则是女票 
};
bool vis[1005][1005][5]; // 标记这个点是女票走的还是erriyue走的   
int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};
vector<node> devil; // 鬼魂的位置
int t;
queue<node> p;
queue<node> q;

int get_dis(int x, int y, int xx, int yy)
{
	return abs (x - xx) + abs(y - yy);
}

bool check (int x, int y, bool f)
{
	return (x >= 1 and x <= n and y >= 1 and y <= m and vis[x][y][f] == 0 and a[x][y] != 'X');
}

bool to(node qwq) 
{
	for (int i = 0; i <= 1; i ++) // 状态 
		if (get_dis(qwq.x, qwq.y, devil[i].x, devil[i].y) <= 2 * t)
			return 0;
	return 1;
}

int bfs()
{
	while (!q.empty() and !p.empty())
	{
		t ++; // 时间花费一次 
		int op = 3; // 每个点跑3次队列 
		while (op --)
		{
			int len = q.size();
			while (len --)
			{
				node u = q.front();
				q.pop();
				node A = node({u.x, u.y});
				if (to (A))
				{
					for (int i = 0; i < 4; i ++) // 遍历方向数组 
					{
						int xx = u.x + dx[i];
						int yy = u.y + dy[i];
						node d = node({xx, yy});
						if (check (xx, yy, u.f) and to(d))
						{
							vis[xx][yy][u.f] = 1;
							if (vis[xx][yy][!u.f] == 1)
								return t; // 找到答案 
							q.push({xx, yy, u.f}); // 加入队列 
						}
					}
				}
			}
		}
		op = 1; // 每个点跑1次队列 
		while (op --)
		{
			int len = p.size();
			while (len --)
			{
				node u = p.front();
				p.pop();
				node A = node({u.x, u.y});
				if (to (u))
				{
					for (int i = 0; i < 4; i ++) // 遍历方向数组 
					{
						int xx = u.x + dx[i];
						int yy = u.y + dy[i];
						node d = node({xx, yy});
						if (check (xx, yy, u.f) and to(d))
						{
							vis[xx][yy][u.f] = 1;
							if (vis[xx][yy][!u.f] == 1)
								return t; // 找到答案 
							p.push({xx, yy, u.f}); // 加入队列 
						}
					}
				}
			}
		}
	}
	return -1;
}

void init()
{
	memset (vis, 0, sizeof vis);
	t = 0;
	while (!q.empty())
	{
		q.pop();
	}
	while (!p.empty())
	{
		p.pop();
	}
	devil.clear();
	return ;
}

void work()
{
	init();
	cin >> n >> m;
	for (int i = 1; i <= n; i ++)
	{
		for (int j = 1; j <= m; j ++)
		{
			cin >> a[i][j];
			if (a[i][j] == 'M')
			{
				q.push({i, j, 0});
				vis[i][j][0] = 1;
			}
			if (a[i][j] == 'G')
			{
				p.push({i, j, 1});
				vis[i][j][1] = 1;
			}
			if (a[i][j] == 'Z')
			{
				devil.push_back({i, j});
			}
		}
	}
	cout << bfs() << endl;
	return ;
}

int main()
{
	int t;
	cin >> t;
	while (t --)
	{
		work ();
	} 
}
```

---

## 作者：_yang_yi_bo_ (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/P10487)

这题要用到双向广搜，使用两个队列，一个存储男生所在的点，一个存储女生所在的点，并使用两个标记数组，一个标记男生走过的点，一个标记女生走过的点。

对于鬼魂，由于鬼魂会穿墙，所以鬼魂走到一个点走的步数为两点之间的曼哈顿距离，时间为 $\lceil$ 两点之间的曼哈顿距离 $\div 2\rceil$。

注意 $t$ 组数据，记得清空。


```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1005][1005];
int n,m,t;
struct kkk{
	int x,y,f;
};
bool vis[1005][1005][2];
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
vector<kkk> op;
int sumt=0;
int dis(kkk a,kkk b){
	return abs(a.x-b.x)+abs(a.y-b.y);
}bool check1(int x,int y,int k){
	if(a[x][y]!='X'&&x>=1&&x<=n&&y>=1&&y<=m&&vis[x][y][k]==0){
		return true;
	}return false;
}bool check2(kkk a){
	for(int i=0;i<2;i++){
		if(dis(a,op[i])<=2*sumt){
			return false;
		}
	}return true;
}
queue<kkk> q1;
queue<kkk> q2;
int bfs(){
	while(!q1.empty()&&!q2.empty()){
		sumt++;
		int tot=3;
		while(tot--){
			int len=q1.size();
			while(len--){
				kkk u=q1.front();
				q1.pop();
				if(!check2(kkk{u.x,u.y})){
					continue;
				}for(int i=0;i<4;i++){
					int xx=u.x+dx[i];
					int yy=u.y+dy[i];
					if(check1(xx,yy,u.f)&&check2(kkk{xx,yy})){
						vis[xx][yy][u.f]=1;
						if(vis[xx][yy][!u.f]){
							return sumt;
						}q1.push(kkk{xx,yy,u.f});
					}
				}
			}
		}tot=1;
		while(tot--){
			int len=q2.size();
			while(len--){
				kkk u=q2.front();
				q2.pop();
				if(!check2(kkk{u.x,u.y})){
					continue;
				}for(int i=0;i<4;i++){
					int xx=u.x+dx[i];
					int yy=u.y+dy[i];
					if(check1(xx,yy,u.f)&&check2(kkk{xx,yy})){
						vis[xx][yy][u.f]=1;
						if(vis[xx][yy][!u.f]){
							return sumt;
						}q2.push(kkk{xx,yy,u.f});
					}
				}
			}
		}
	}return -1;
}
void init(){
	memset(vis,0,sizeof vis);
	while(!q1.empty()){
		q1.pop();
	}while(!q2.empty()){
		q2.pop();
	}op.clear();
	sumt=0;
}
int main(){
	cin>>t;
	while(t--){
		init();
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
				if(a[i][j]=='M'){
					q1.push({i,j,0});
					vis[i][j][0]=1;
				}else if(a[i][j]=='G'){
					q2.push({i,j,1});
					vis[i][j][1]=1;
				}else if(a[i][j]=='Z'){
					op.push_back(kkk{i,j});
				}
			}
		}cout<<bfs()<<"\n";
	}
	return 0;
}
```

---

## 作者：program_xwl (赞：1)

### 思路：
这题是一个多源点广搜题，因为小 erriyue 一时刻内能走三格，而女友一时刻内只能走一格，放在一个队列中更新小 erriyue 是遇到了女友的节点还需要装回去，同时广搜主循环的循环条件应该是两人都有还有节点。这样常数项会很大，所以考虑使用两个队列，一个存小 erriyue 的节点，一个存女友的节点，循环条件是两个队列都不为空。鬼魂不需要单独开一个队列，因为它不受墙的阻挡，可以直接算曼哈顿距离。

用两个队列，该怎么判断是否相遇呢？广搜模板中的 $vis$ 数组可以让这个判断很方便，我们给他多开一维，存储具体是谁标记了这个点，我们在判断该节点是否走过是，如果是自己，那么就照旧，如果是对方，说明可以相遇了，就算是以前标记的。

用这种简化方法写的化代码可以短几十行。
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

struct node {long long x,y;bool type;};

long long T,n,m,zstx,zsty,zstx2,zsty2,stx,sty,gstx,gsty,sum_t;
char mp[805][805];
bool vis[805][805][2];
const long long dx[4] = {0,0,-1,1};
const long long dy[4] = {-1,1,0,0};
queue<node>mq,gq;

long long dis(node x,node y) {return abs(x.x-y.x)+abs(x.y-y.y);}

bool check(node x)
{
	if(dis(x,node{zstx,zsty}) <= 2*sum_t || dis(x,node{zstx2,zsty2}) <= 2*sum_t) return 0;
	return 1;
}

bool check_the_pos(long long x,long long y)
{
	if(x < 1 || y < 1 || x > n || y > m) return 0;
	if(mp[x][y] == 'X' || check({x,y}) == 0) return 0;
	return 1;
}

long long bfs(void)
{
	mq.push({stx,sty,0});
	gq.push({gstx,gsty,1});
	vis[stx][sty][0] = vis[gstx][gsty][1] = 1;
	while(mq.size() && gq.size())
	{
		sum_t++;
		for(long long steps = 1;steps <= 3;steps++)
		{
			long long len = mq.size();
			while(len--)
			{
				node u = mq.front();
				mq.pop();
				if(check(u) == 0) continue;
				for(long long i = 0;i < 4;i++)
				{
					long long nx = u.x+dx[i],ny = u.y+dy[i];
					if(check_the_pos(nx,ny))
					{
						if(vis[nx][ny][u.type]) continue;
						vis[nx][ny][u.type] = 1;
						if(vis[nx][ny][!u.type] == 1) return sum_t;
						mq.push({nx,ny,u.type});
					}
				}
			}
		}
		long long len = gq.size();
		while(len--)
		{
			node u = gq.front();
			gq.pop();
			if(check(u) == 0) continue;
			for(long long i = 0;i < 4;i++)
			{
				long long nx = u.x+dx[i],ny = u.y+dy[i];
				if(check_the_pos(nx,ny))
				{
					if(vis[nx][ny][u.type]) continue;
					vis[nx][ny][u.type] = 1;
					if(vis[nx][ny][!u.type] == 1) return sum_t;
					gq.push({nx,ny,u.type});
				}
			}
		}
	}
	return -1;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while(T--)
	{
		cin >> n >> m;
		zstx = zsty = 0;
		for(long long i = 1;i <= n;i++)
		{
			for(long long j = 1;j <= m;j++)
			{
				cin >> mp[i][j];
				if(mp[i][j] == 'M')
				{
					stx = i;
					sty = j;
				}else if(mp[i][j] == 'G')
				{
					gstx = i;
					gsty = j;
				}else if(mp[i][j] == 'Z')
				{
					if(zstx == 0 && zsty == 0)
					{
						zstx = i;
						zsty = j;
					}else
					{
						zstx2 = i;
						zsty2 = j;
					}
				}
			}
		}
		memset(vis,0,sizeof(vis));
		sum_t = 0;
		while(mq.size()) mq.pop();
		while(gq.size()) gq.pop();
		cout << bfs() << '\n';
	}
	return 0;
}
```

---

## 作者：newbieTroll (赞：1)

口糊题解，不喜勿喷。

考虑双向广搜，以小 erriyue 和他 npy 的位置为起点，交替扩展队列。bfs 的过程就是将小 erriyue 走到的位置用 $viss$ 标记，将他 npy 的位置用 $vist$ 标记。如果在搜索的过程中发现对方的相应位置已经标记过了，结束搜索。如果一直找不到就说明无解，输出 $-1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=805;
struct Node{
	int x,y;
}b,g,gh1,gh2;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
char a[N][N];
bool viss[N][N];
bool vist[N][N];
int x,y;
void bfs2(){
	int tm=0;
	queue<Node> qs,qt;
	viss[b.x][b.y]=1;
	vist[g.x][g.y]=1;
	qs.push(b);
	qt.push(g);
	while(!qs.empty()||!qt.empty()){
		++tm; 
		for(int j=1;j<=3;++j){
			int t=qs.size();
			for(int k=1;k<=t;++k){
					Node tmp=qs.front();
					qs.pop();
					if(abs(tmp.x-gh1.x)+abs(tmp.y-gh1.y)<=2*tm){
						continue;
					}if(abs(tmp.x-gh2.x)+abs(tmp.y-gh2.y)<=2*tm){
						continue;
					}
					for(int i=0;i<4;++i){
						int xx=tmp.x+dx[i],yy=tmp.y+dy[i];
						if(xx<1||xx>x||yy<1||yy>y||viss[xx][yy]){
							continue;
						}if(abs(xx-gh1.x)+abs(yy-gh1.y)<=2*tm){
							continue;
						}if(abs(xx-gh2.x)+abs(yy-gh2.y)<=2*tm){
							continue;
						}if(a[xx][yy]=='X'){
							continue;
						}
						viss[xx][yy]=1;
						if(vist[xx][yy]==1){
							cout<<tm<<endl;
							return ;
						}
						qs.push({xx,yy});
					}
			}
		}int t=qt.size();
			for(int k=1;k<=t;++k){
				Node tmp=qt.front();
				qt.pop();
				if(abs(tmp.x-gh1.x)+abs(tmp.y-gh1.y)<=2*tm){
					continue;
				}if(abs(tmp.x-gh2.x)+abs(tmp.y-gh2.y)<=2*tm){
					continue;
				}
				for(int i=0;i<4;++i){
					int xx=tmp.x+dx[i],yy=tmp.y+dy[i];
					if(xx<1||xx>x||yy<1||yy>y||vist[xx][yy]){
						continue;
					}if(abs(xx-gh1.x)+abs(yy-gh1.y)<=2*tm){
						continue;
					}if(abs(xx-gh2.x)+abs(yy-gh2.y)<=2*tm){
						continue;
					}if(a[xx][yy]=='X'){
						continue;
					}
					vist[xx][yy]=1;
					if(viss[xx][yy]==1){
						cout<<tm<<endl;
						return ;
					}
					qt.push({xx,yy});
				}
			}
	}cout<<-1<<endl;
	return ;
}
void work(){
	cin>>x>>y;
	memset(viss,0,sizeof(viss));
	memset(vist,0,sizeof(vist));
	gh1.x=0;
	for(int i=1;i<=x;++i){
		for(int j=1;j<=y;++j){
			cin>>a[i][j];
			if(a[i][j]=='M'){
				b={i,j};
			}else if(a[i][j]=='G'){
				g={i,j};
			}else if(a[i][j]=='Z'){
				if(gh1.x==0){
					gh1={i,j};
				}else{
					gh2={i,j};
				}
			}else{
				continue;
			}
		}
	}
	bfs2();
	return ;
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		work();
	}
	return 0;
}
```

---

## 作者：Yurinaxu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10487)

[博客食用更加](https://www.luogu.com.cn/article/l0zjvsb3)

一道简单的双向广搜，小 erriyue 的三步只需遍历三次就好了，用一个数组记录对方有没有走到这里过，并且走的时候要和鬼的距离进行班比较，符合题意就走并记录。

# code

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int vis[2][805][805],gx,gy,mx,my,n,m,f[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
char a[805][805];
struct node{
    int x,y;
}z[2];
queue<node>q[2];
bool pd(node b,int k){
    if(b.x<0 || b.y<0 || b.x>=n || b.y>=m) return 0;
    if(a[b.x][b.y]=='X') return 0;
    if((abs(b.x-z[0].x)+abs(b.y-z[0].y))<=2*k) return 0;
    if((abs(b.x-z[1].x)+abs(b.y-z[1].y))<=2*k) return 0;
    return 1;
}
int bfs(int borg,int k){
    int i,sum;
    sum=q[borg].size();
    while(sum--){
        node aa=q[borg].front();
        q[borg].pop();
        if(pd(aa,k)==0) continue;
        for(i=0;i<4;i++){
        	node bb={aa.x+f[i][0],aa.y+f[i][1]};
            if(pd(bb,k)==0) continue;
            if(vis[borg][bb.x][bb.y]==0){
                if(vis[1-borg][bb.x][bb.y]==1) return 1;
                vis[borg][bb.x][bb.y]=1;
                q[borg].push(bb);
            }
        }
    }
    return 0;
}
int dfs(){
    q[0].push({mx,my});
    q[1].push({gx,gy});
    vis[0][mx][my]=vis[1][gx][gy]=1;
    int k=0;
    while(!q[0].empty() && !q[1].empty()){
        k++;
        if(bfs(0,k)==1) return k;
        if(bfs(0,k)==1) return k;
        if(bfs(0,k)==1) return k;
        if(bfs(1,k)==1) return k;
    }
    return -1;
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int i,j,cnt;
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++){
        	scanf("%s",a[i]);
		}
        cnt=0;
        for(int i=0;i<n;i++){
        	for(int j=0;j<m;j++){
        		if(a[i][j]=='M'){
                    mx=i;
					my=j;
                }
                if(a[i][j]=='G'){
                    gx=i;
					gy=j;
                }
                if (a[i][j]=='Z'){
                    z[cnt].x=i;
                    z[cnt].y=j;
                    cnt++;
                }
            }
		}
		memset(vis,0,sizeof(vis));
		while(!q[0].empty()) q[0].pop();
        while(!q[1].empty()) q[1].pop();
        printf("%d\n",dfs());
    }
    return 0;
}
~~~

---

## 作者：zcz0263 (赞：1)

## 思路
一道双向 BFS 题目。因为两个人必须在同一时刻汇合，所以用两个队列分别维护当前时刻两个人的所有目标位置，在同一次 BFS 中更新。

考虑开一个 $vis$ 数组，若 $vis_{i,j}=0$，表示第一个和第二个人都还没到达过该点，若 $vis_{i,j}=1$，表示第一个人到达过该点，若$vis_{i,j}=2$，表示第二个人到达过该点，当一个人的 BFS 过程中遇到另一个人到达过的点时，返回当前时刻数作为答案。

对于被鬼占领位置的判断，只需要判断该点和两个鬼的曼哈顿距离是否均小于二倍的当前时刻数即可。

时间复杂度 $O(T \times n \times m)$。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define pii pair<int,int>
#define vi vector<int>
#define dis(x1,y1,x2,y2) (abs((x1)-(x2))+abs((y1)-(y2)))
int n,m,vis[805][805];
constexpr int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
char a[805][805];
pii boy,girl;
pii z[4];
inline bool check(int x,int y,int t){
	return !((a[x][y]=='X'||x>n||x<1||y<1||y>n||dis(x,y,z[1].first,z[1].second)<=2*t||dis(x,y,z[2].first,z[2].second)<=2*t));
}
int bfs(){
    int cnt=0,ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]=='M'){
                boy={i,j};
                boy.second=j;
            }
            if(a[i][j]=='G'){
                girl={i,j};
            }
            if(a[i][j]=='Z') z[++cnt]={i,j};
        }
    }
    queue<pii> qb,qg;
    qb.push(boy);
    qg.push(girl);
    while(qb.size()|qg.size()){
    	++ans;
        int t;
    	for(int i=1;i<=3;i++){
    		t=qb.size();
            for(int j=1;j<=t;j++){
                int x=qb.front().first,y=qb.front().second;
                qb.pop();
                if(!check(x,y,ans)) continue;
                for(int i=0;i<4;i++){
                    int tx=x+dx[i],ty=y+dy[i];
                    if(vis[tx][ty]==1||!check(tx,ty,ans)) continue;
                    if(vis[tx][ty]==2) return ans;
                    vis[tx][ty]=1;
                    qb.push({tx,ty});
                }
            }
        }
        t=qg.size();
        for(int j=1;j<=t;j++){
            const int x=qg.front().first,y=qg.front().second;
            qg.pop();
            if(!check(x,y,ans))
                continue;
            for(int i=0;i<4;i++){
                int tx=x+dx[i],ty=y+dy[i];
                if(vis[tx][ty]==2||!check(tx,ty,ans)) continue;
                if(vis[tx][ty]==1) return ans;
                vis[tx][ty]=2;
                qg.push({tx,ty});
            }
        }
	}
    return -1;
}
int _;
main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	for(cin>>_;_--;){
		cin>>n>>m;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++) cin>>a[i][j];
		cout<<bfs()<<"\n";
		memset(vis,0,sizeof(vis));
	}
}


```

---

## 作者：LHY_Ian (赞：0)

### 题目大意
小 erriyue 和他的女朋友可以向四个方向移动，他们移动速度分别为 $3$ 步/秒，和 $1$ 步/秒。鬼魂会每秒分裂成几部分并占领距离它们两步以内的网格，直到占领整个迷宫。每秒钟鬼魂先分裂。若两人相遇且不碰到鬼魂则输出最短时间，没有则输出 $-1$ 。
### 解题思路
这是一道典型的双向 BFS 的题目。那么双向 BFS 的思想是什么呢？双向 BFS 的思想其实是和双向搜索是一样的。以普通的求最少步数的双向 BFS 为例，我们只需从起始状态、目标状态分别开始，两边轮流进行，每次各扩展一整层。当两边各自有一个状态在记录数组中发生重复时，就说明这两个搜索过程相遇了，可以合并得出起点到终点的最少步数。

所以，这道题我们可以建立两个对列，分别从小 erriyue 的初始位置、他的女朋友的初始位置开始轮流进行 BFS ，在每一轮中，小 erriyue 这边 BFS 三层（可以移动三步），他女朋友这边 BFS 一层（可以移动一步），同时，我们使用数组 $d$ 记录每个位置对于男孩和女孩的可达性。

当然，在 BFS 的每次扩展时，要注意实时计算新状态与鬼魂之间的曼哈顿距离，如果已经小于等于当前轮数（即秒数）的 $2$ 倍，就判定这个新状态不合法，不再记录或入队。

在 BFS 的过程中，第一次出现某个位置 $(x,y)$ 既能被男孩到达，也能被女孩到达时，那么当前轮数就是两人的最短会合时间， return 便可。
### 代码
```cpp
#include <queue>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 806;
char s[N][N];
bool v1[N][N], v2[N][N];
int n, m, bx, by, gx, gy, px, py, qx, qy, s1, s2;
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};

bool pd(int x, int y, int k) {
	if (x <= 0 || x > n || y <= 0 || y > m) return 0;
	if (abs(x - px) + abs(y - py) <= 2 * k) return 0;
	if (abs(x - qx) + abs(y - qy) <= 2 * k) return 0;
	if (s[x][y] == 'X') return 0;
	return 1;
}

int bfs() {
	queue<pair<int, int> > q1, q2;
	px = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (s[i][j] == 'M') {
				bx = i;
				by = j;
			} else if (s[i][j] == 'G') {
				gx = i;
				gy = j;
			} else if (s[i][j] == 'Z') {
				if (!px) {
					px = i;
					py = j;
				} else {
					qx = i;
					qy = j;
				}
			}
	int ans = 0;
	memset(v1, 0, sizeof(v1));
	memset(v2, 0, sizeof(v2));
	v1[bx][by] = 1;
	v2[gx][gy] = 1;
	q1.push(make_pair(bx, by));
	q2.push(make_pair(gx, gy));
	while (q1.size() || q2.size()) {
		ans++;
		s1 = q1.size();
		for (int i = 1; i <= s1; i++) {
			pair<int, int> now = q1.front();
			q1.pop();
			if (!pd(now.first,now.second,ans)) continue;
			for (int j = 0; j < 4; j++) {
				int nx = now.first + dx[j];
				int ny = now.second + dy[j];
				if (pd(nx,ny,ans) && !v1[nx][ny]) {
					v1[nx][ny] = 1;
					q1.push(make_pair(nx, ny));
				}
			}
		}
		s1 = q1.size();
		for (int i = 1; i <= s1; i++) {
			pair<int, int> now = q1.front();
			q1.pop();
			if (!pd(now.first,now.second,ans)) continue;
			for (int j = 0; j < 4; j++) {
				int nx = now.first + dx[j];
				int ny = now.second + dy[j];
				if (pd(nx,ny,ans) && !v1[nx][ny]) {
					v1[nx][ny] = 1;
					q1.push(make_pair(nx, ny));
				}
			}
		}
		s1 = q1.size();
		for (int i = 1; i <= s1; i++) {
			pair<int, int> now = q1.front();
			q1.pop();
			if (!pd(now.first,now.second,ans)) continue;
			for (int j = 0; j < 4; j++) {
				int nx = now.first + dx[j];
				int ny = now.second + dy[j];
				if (pd(nx,ny,ans) && !v1[nx][ny]) {
					v1[nx][ny] = 1;
					q1.push(make_pair(nx, ny));
				}
			}
		}
		s2 = q2.size();
		for (int i = 1; i <= s2; i++) {
			pair<int, int> now = q2.front();
			q2.pop();
			if (!pd(now.first,now.second,ans)) continue;
			for (int j = 0; j < 4; j++) {
				int nx = now.first + dx[j];
				int ny = now.second + dy[j];
				if (pd(nx,ny,ans) && !v2[nx][ny]) {
					if (v1[nx][ny]) return ans;
					v2[nx][ny] = 1;
					q2.push(make_pair(nx, ny));
				}
			}
		}
	}
	return -1;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
			scanf("%s", s[i] + 1);
		cout << bfs() << endl;
	}
	return 0;
}
```

---

## 作者：charlieqi (赞：0)

# 题意
两个人同时移动，一个人 $1$ 秒 $3$ 步，一个人 $1$ 秒 $1$ 步。问，在一个迷宫里，两个人何时相遇，若相遇，输出秒数，否则，输出 $-1$。
# 分析
我们需要模拟两个人走的过程，在这个过程中，鬼魂其实可以忽略不计，只需要保证人不会走到鬼一开始的位置即可。因为，如果鬼魂已经包围了人，那人就不会走出去，否则，就可以走出去。因此，我们在模拟的过程中，要判断鬼在 $t$ 秒前是否可以走到这个格，即 $|x_1-x-2|+|y_1-y_2|\le 2t$，如果成立，那人就不可以走这个格子，否则，就可以走这个格子。
# code
```cpp
#include<bits/stdc++.h>
#define qu queue<pair<int,int> >
#define p pair<int,int>
#define l(x1,y1,x2,y2) (abs((x1)-(x2))+abs((y1)-(y2)))
using namespace std;
int t,n,c,vis[1001][1001],d[4][2]={{0,1},{0,-1},{1,0},{-1,0}};\\方位。
char a[1001][1001];
p m;
p g;
p b[10];
bool ok(int x,int y,int t){\\判断位置是否合法。
	return !((a[x][y]=='X'||x>n||x<1||y<1||y>c||l(x,y,b[1].first,b[1].second)<=2*t||l(x,y,b[2].first,b[2].second)<=2*t));
}
void two_ways_bfs(){\\模拟
	int ans=0,cnt=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=c;j++){
			if(a[i][j]=='M')m={i,j};
			if(a[i][j]=='G')g={i,j};
			if(a[i][j]=='Z')b[++cnt]={i,j};
		}
	}
	qu qm;
	qu qg;
	qm.push(m),qg.push(g);
	while(qm.size()||qg.size()){
		ans++;
		int len;
		for(int i=1;i<=3;i++){
			len=qm.size();
			for(int j=1;j<=len;j++){
				int x0=qm.front().first,y0=qm.front().second;
				qm.pop();
				if(!ok(x0,y0,ans))continue;
				for(int i=0;i<4;i++){
					int nx=x0+d[i][0],ny=y0+d[i][1];
					if(vis[nx][ny]==1||!ok(nx,ny,ans))continue;
					if(vis[nx][ny]==2){
						cout<<ans<<'\n';
						return;
					}
					vis[nx][ny]=1,qm.push({nx,ny});
				}
			}
		}
		len=qg.size();
		for(int i=1;i<=len;i++){
			int x0=qg.front().first,y0=qg.front().second;
			qg.pop();
			if(!ok(x0,y0,ans))continue;
			for(int i=0;i<4;i++){
				int nx=x0+d[i][0],ny=y0+d[i][1];
				if(vis[nx][ny]==2||!ok(nx,ny,ans))continue;
				if(vis[nx][ny]==1){
					cout<<ans<<'\n';
					return;
				}
				vis[nx][ny]=2,qg.push({nx,ny});
			}
		}
	}
	cout<<"-1\n";
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>c;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=c;j++)cin>>a[i][j];
		}
		two_ways_bfs();
		memset(vis,0,sizeof(vis));
	}
	return 0;
}
```
声明：代码部分借鉴了 [zcz0263](https://www.luogu.com.cn/user/760433) 的文章。
# 此题知识点：
双向 BFS；队列；方位；曼哈顿距离。
# 常见疑问点：
- 1.什么是双向 BFS？答：起点和终点同时移动。
- 2.什么是曼哈顿距离？答：用 $x_1,y_1,x_2,y_2$ 表示两点坐标，曼哈顿距离即 $|x_1-x_2|+|y_1-y_2|$。
- 3.为什么男生遍历多加一层循环？答：男生一步 $3$ 米。

---

## 作者：dsj2012 (赞：0)

## 题意
男生和女生每次都会向四个方向移动，还有一个鬼魂会吃人。

问：男生能否在鬼魂没吃掉自己或女朋友的情况下找到女朋友。 

## 思路

这一看就知道是一个双向广搜的题目了。
              
首先，男生每次是可以移动三步，而女生却只能走出去一步。那么我们可以用两个队列去分别维护两人的坐标。 
      
对于男生与女生的标记问题，我们考虑三维标记数组。  
         
$vis_{i,j,0}$ 代表 $i,j$ 这个点男生走过。       

$vis_{i,j,1}$ 代表 $i,j$ 这个点女生走过。       

然后有人又会问了，鬼魂怎么办呢？难道也给他一个队列去维护鬼魂的位置吗？   
         
我们知道，鬼魂是可以穿墙的，且每次只走一步，发现就是曼哈顿距离。我们只需看这个点，通过曼哈顿距离看看鬼魂是否能到即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 7;
char a[maxn][maxn];
int n,m,sum_t;
struct pi{
	int x, y;
	int flag;
};
bool vis[maxn][maxn][2];
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
vector<pi> op;
int dis(pi a,pi b){
	return abs(a.x - b.x) + abs(a.y - b.y);
}
bool check1(int x,int y,int k){
	if(a[x][y] != 'X' && x >= 1 && x <= n && y >= 1 && y <= m && vis[x][y][k] == 0){
		return true;
	}
	return false;
}
bool check2(pi a){
	for(int i = 0 ; i < 2 ; i ++){
		if(dis(a,op[i]) <= 2 * sum_t){
			return false;
		}
	}
	return true;
}
queue<pi> q1;
queue<pi> q2;
int bfs(){
	while(!q1.empty() && !q2.empty()){
		sum_t++;
		int total = 3;
		while(total--){
			int len = q1.size();
			while(len--){
				pi u = q1.front();
				q1.pop();
				if(!check2(pi {u.x, u.y})){
					continue;
				}
				for (int i = 0 ; i < 4 ; i ++){
					int xx = u.x + dx[i];
					int yy = u.y + dy[i];
					if(check1(xx, yy, u.flag) && check2(pi {xx, yy})){
						vis[xx][yy][u.flag] = 1;
						if(vis[xx][yy][!u.flag] == 1){
							return sum_t;
						}
						q1.push(pi {xx, yy, u.flag});
					}
				}
			}
		}
		total = 1;
		while(total--){
			int len = q2.size();
			while (len--) {
				pi u = q2.front();
				q2.pop();
				if(!check2(pi {u.x, u.y})){
					continue;
				}
				for(int i = 0 ; i < 4 ; i ++){
					int xx = u.x + dx[i];
					int yy = u.y + dy[i];
					if(check1(xx, yy, u.flag) && check2(pi {xx, yy})){
						vis[xx][yy][u.flag] = 1;
						if(vis[xx][yy][!u.flag] == 1){
							return sum_t;
						}
						q2.push(pi {xx, yy, u.flag});
					}
				}
			}
		}
	}
	return -1;
}
void qing(){
	memset(vis, 0, sizeof(vis));
	sum_t = 0;
	while(!q1.empty()){
		q1.pop();
	}
	while(!q2.empty()){
		q2.pop();
	}
	op.clear();
	return;
}
int main(){
	int T;
	cin >> T;
	while(T --){
		qing();
		cin >> n >> m;
		for(int i = 1 ; i <= n ; i ++){
			for(int j = 1 ; j <= m ; j ++){
				cin >> a[i][j];
				if(a[i][j] == 'M'){
					q1.push({i, j, 0});
					vis[i][j][0] = 1;
				}
				if(a[i][j] == 'G'){
					q2.push({i, j, 1});
					vis[i][j][1] = 1;
				}
				if(a[i][j] == 'Z'){
					op.push_back({i, j});
				}
			}
		}
		cout << bfs() << endl;
	}
	return 0;
}
```

---

