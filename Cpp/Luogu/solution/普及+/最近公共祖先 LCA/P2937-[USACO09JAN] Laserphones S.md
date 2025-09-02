# [USACO09JAN] Laserphones S

## 题目描述

奶牛们有一个新的激光系统，这样它们在牧场上时可以进行随意的交谈。牧场被建模为一个 $W \times H$ 的点阵（$1 \leq W \leq 100$，$1 \leq H \leq 100$）。

该系统需要某种视线连通性以维持通信。当然，牧场上有岩石和树木会干扰通信，但奶牛们购买了对角镜（如下的 '/' 和 '\\'）来使激光束偏转 90 度。下面是一个说明问题的地图。

对于这张地图，$H$ 是 8，$W$ 是 7。两个正在通信的奶牛用 'C' 表示；岩石和其他阻挡元素用 '*' 表示：

```plain
7 . . . . . . .         7 . . . . . . . 
6 . . . . . . C         6 . . . . . /-C 
5 . . . . . . *         5 . . . . . | * 
4 * * * * * . *         4 * * * * * | * 
3 . . . . * . .         3 . . . . * | . 
2 . . . . * . .         2 . . . . * | . 
1 . C . . * . .         1 . C . . * | . 
0 . . . . . . .         0 . \-------/ . 
0 1 2 3 4 5 6           0 1 2 3 4 5 6 
```
确定必须安装的最少镜子数量 $M$，以维持两头奶牛之间的激光通信。在给定的测试数据中，这一壮举总是可能的。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
7 8 
....... 
......C 
......* 
*****.* 
....*.. 
....*.. 
.C..*.. 
....... 
```

### 输出

```
3 
```

# 题解

## 作者：IRipple (赞：26)

很有意思的一道题，做法不是很难。~~但是卡住了机房大佬~~

### 理论分析

模拟一下走的过程。

第一次走的时候我们到起点的**上下左右四个方向**都需要0个镜子，我们把这些点都记录成第一次的扩展。
```
//拿样例来举个栗子，不妨设上面的C是起点，另一个是终点
....... 
......C 
......* 
*****.* 
....*.. 
....*.. 
.C..*.. 
....... 
```
那么我们标记出第一次可以确定的点

```
......1 
111111C 
......* 
*****.* 
....*.. 
....*.. 
.C..*.. 
....... 
```
所有被标记为1的点，都不需要平面镜，我们接着走第二步。

第二步我们把**所有标记为1的点**进行同样的操作，把这些点的上下左右扩展出来，记录成第二步扩展
```
2222221 
111111C 
222222* 
*****2* 
....*2. 
....*2. 
.C..*2. 
.....2. 
```
所有被标记为2的点，都需要1个平面镜。

... ...

像这样我们不断地扩展下去，就会得到到C点所需的镜子个数 0.0

### 代码实现

首先这种跑地图还问你最短xx的，我们就可以上bfs了。

设计一个结构体
```
struct node{
    int x,y;//点坐标
    int num;//记录这个点是第几步扩展得来的
}s,t;
```
然后随手~~瞎~~敲一下bfs就行了
```
void bfs(){
    while(!q.empty()){
        node u=q.front(),v=u;//u和v都是队首
        q.pop();
        u.num++;
        v=u; v.x=u.x-1;//上 
        dfs(1,v);
        v=u; v.x=u.x+1;//下 
        dfs(2,v);
        v=u; v.y=u.y-1;//左 
        dfs(3,v);
        v=u; v.y=u.y+1;//右 
        dfs(4,v);
    }
}
```
用这个bfs扩展队首点的四个方向，每次dfs去进行染色的工作
```
void dfs(int fx,node u){ //fx记录方向（1上2下3左4右） u为当前所在点 
    int x=u.x,y=u.y,p=u.num; 
    if(a[x][y]<p || a[x][y]==inf) return;//如果该点标记比这次扩展的小【即更优】，就直接跳过它。
    									//inf表示墙，返回
    if(x<1 || y<1 || x>n || y>m) return;//超出边界返回
    if(fx==1){
        a[x][y]=p;//染色
        q.push((node){x,y,p});//放入队列，之后进行拓展
        dfs(1,(node){x-1,y,p});//染下一个上边的点
    }
    if(fx==2){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(2,(node){x+1,y,p});
    }
    if(fx==3){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(3,(node){x,y-1,p});
    }
    if(fx==4){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(4,(node){x,y+1,p});
    }
}
```
**说明：我把数据给出的地图转成了int类型，inf代表墙。**

完整代码如下~
```
#include<bits/stdc++.h>
#include<queue>
#define inf 0x3f3f3f3f
using namespace std;
int n,m;
int a[110][110];//保存地图
struct node{
    int x,y;
    int num;
}s,t;
queue<node> q;
void dfs(int fx,node u){ //fx记录方向（1上2下3左4右） u为当前所在点 
    int x=u.x,y=u.y,p=u.num; 
    if(a[x][y]<p || a[x][y]==inf) return;
    if(x<1 || y<1 || x>n || y>m) return;

    if(fx==1){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(1,(node){x-1,y,p});
    }
    if(fx==2){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(2,(node){x+1,y,p});
    }
    if(fx==3){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(3,(node){x,y-1,p});
    }
    if(fx==4){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(4,(node){x,y+1,p});
    }
}

void bfs(){
    while(!q.empty()){
        node u=q.front(),v=q.front();
        q.pop();
        u.num++;
        v=u; v.x=u.x-1;//上 
        dfs(1,v);
        v=u; v.x=u.x+1;//下 
        dfs(2,v);
        v=u; v.y=u.y-1;//左 
        dfs(3,v);
        v=u; v.y=u.y+1;//右 
        dfs(4,v);
    }
}
int main(){
    cin>>m>>n;
    char zwh;
    memset(a,inf,sizeof(a));
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++) a[i][j]=inf-1;
    //如果地图范围全部是比答案小的数字（比如0），那么在dfs染色的时候就会直接返回，导致错误。
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf(" %c",&zwh);
            if(zwh=='C'){
                if(s.x) t.x=i,t.y=j,t.num=0;//找到起点和终点
                else s.x=i,s.y=j,s.num=0;
            }
            if(zwh=='*'){
                a[i][j]=inf;
            }
            
        }
    }
    q.push(s);
    bfs();
    cout<<a[t.x][t.y]-1;//注意减一
    return 0;
}

```










---

## 作者：Delva (赞：21)

都有最短路的标签了，居然没人写题解

这道题是求镜子数量的最小值，即求转弯次数的最小值。

我们考虑分层图，建立4层相同的图。层内只能向着某个方向走，因此在可以走的地方建权值为0的边，层间实现转弯，两两建权值为1的边，表示可以转弯，但有花费。最后从每一层的起点到每一层的终点跑最短路，统计花费就行了。
```cpp
#include<bits/stdc++.h>
using namespace std;
template<class T>inline void read(T &aa) {
  int k=0,f=1;char c=getchar();for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
  for(;isdigit(c);c=getchar()) k=(k<<3)+(k<<1)+(c-'0');aa=k*f;
}
template<class T>void _out(T x){if(x>9)_out(x/10);putchar(x%10+'0');}
template<class T>void out(T x){if(x<0)putchar('-');_out(x<0?-x:x);}
template<class T>void outln(T x){out(x);putchar('\n');}
const int inf = 0x7fffffff, maxn = 103, maxp = maxn*maxn*4;
const int dx[]={0,0,0,1,-1},dy[]={0,1,-1,0,0};
char M[maxn][maxn];
#define pNum (n*m*4)//总点数
#define point_ID(t,i,j) ((t-1)*n*m+(i-1)*m+j)//给每个点（t层i行j列）分配编号
int n,m,head[maxp],cnt,dis[maxp],sx,sy,ex,ey;
struct Edge{
	int next,to,w;
	Edge(){}
	Edge(int a,int b,int c){next=a,to=b,w=c;}
	bool operator <(const Edge &e)const{return w>e.w;}
}edge[maxp<<2];
void addEdge(int u,int v,int w){
	edge[++cnt]=Edge(head[u],v,w);
	head[u]=cnt;
}
int dj(int s){
    for(int i=1;i<=pNum;++i)dis[i]=inf;dis[s]=0;
    priority_queue<Edge> que;
    que.push(Edge(0,s,dis[s]));
    while(!que.empty()){
        Edge fe = que.top();que.pop();
        if(dis[fe.to]!=fe.w)continue;
        for(int i=head[fe.to];i;i=edge[i].next) {
            Edge ne = edge[i];
            if(dis[ne.to]>dis[fe.to]+ne.w){
                dis[ne.to]=dis[fe.to]+ne.w;
                que.push(Edge(0,ne.to,dis[ne.to]));
            }
        }
    }
}
//以上为最短路相关
int main(){char ch;int tot=0;
	read(m),read(n);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>ch;
			if(!tot&&ch=='C')sx=i,sy=j,++tot;
			if(tot&&ch=='C')ex=i,ey=j;
			M[i][j]=ch;
		}
	}
	for(int t=1;t<=4;++t){//层内建图 
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				int nx=i+dx[t],ny=j+dy[t];
				if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&M[i][j]!='*'&&M[nx][ny]!='*')addEdge(point_ID(t,i,j),point_ID(t,nx,ny),0);
			}
		}
	}
	for(int i=1;i<=n;++i){//层间建图 
		for(int j=1;j<=m;++j){if(M[i][j]=='*')continue;
			for(int t=1;t<=4;++t){
				for(int u=1;u<=4;++u){
					if(t^u)addEdge(point_ID(t,i,j),point_ID(u,i,j),1);
				}
			}
		}
	}
    //每层都从起点跑最短路，最优花费也可能在每层出现
	int ans=inf;
	for(int t=1;t<=4;++t){
		dj(point_ID(t,sx,sy));
		for(int u=1;u<=4;++u){
			ans=min(ans,dis[point_ID(u,ex,ey)]);
		}
	}
	outln(ans);
	return 0;
}

```

---

## 作者：hongzy (赞：14)

(~~这题LCA、最短路等标签可能都是假的，应该是枚举、暴力~~)

首先，用dfs爆搜，每次换方向就把累加变量+1，到终点更新答案，可以拿到30分

然后，加上一个优化：每次搜先按之前的方向搜，再尝试其他方向，可以尽快找到最优解。然而还是不能通过。

最后加上记忆化。f(i, j, k) 表示到(i, j)这个点并且前一次方向为k (0<k<4)最少需要点转弯次数

~~跑了48ms好慢~~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int dx[] = {1, 0, -1, 0}; 
const int dy[] = {0, 1, 0, -1};

int n, m, ans(199), f[502][502][4];
char a[502][502];
bool vis[501][501];

void dfs(int i, int j, int c, int d) { //c为转弯次数，d为方向
	if(d != -1 && f[i][j][d] <= c) return; //记忆化取最优解 
	if(d != -1) f[i][j][d] = c; //记录最优解 
	if(a[i][j] == 'C') {
		if(ans > c) ans = c;
		return;
	}
	int nx, ny;
	if(d != -1) { //同方向搜索 
		nx = i + dx[d], ny = j + dy[d];
		if(nx >= 1 && ny >= 1 && nx <= n && ny <= m && !vis[nx][ny] && a[nx][ny] != '*') {
			vis[nx][ny] = true;
			dfs(nx, ny, c, d);
			vis[nx][ny] = false;
		}
	}
	for(int k=0; k<4; k++) { //异方向搜索 
		if(k == d) continue; 
		nx = i + dx[k], ny = j + dy[k];
		if(nx >= 1 && ny >= 1 && nx <= n && ny <= m) {
			if(vis[nx][ny] || a[nx][ny] == '*') continue;
			vis[nx][ny] = true;
			dfs(nx, ny, c + (d != -1), k);
			vis[nx][ny] = false;
		}
	}
}

int main() {
	scanf("%d %d\n", &m, &n);
	memset(f, 127, sizeof f); //f初始值INF 
	for(int i=1; i<=n; i++) gets(a[i] + 1);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			if(a[i][j] != 'C') continue;
			vis[i][j] = true;
			a[i][j] = '*'; //以防被误认为是终点 
			dfs(i, j, 0, -1);
			printf("%d\n", ans);
			return 0;
		}
	return 0;
}
```

---

## 作者：学而思李老师 (赞：7)

发现我的做法和其他题解不太一样，来水一波

这题我们可以使用和[P1849](https://www.luogu.com.cn/problem/P1849)类似的做法，开一个双端队列记录BFS的状态。唯一不一样的，这一题还需要记录上一步是往哪个方向行走的，从而判断这一步是否需要另一个平面镜。这种方法可以去参考P1849的题解，这里说一下注意事项：

1. 因为一些不是最优的状态可能在最优状态前加入队列（这也是双端队列BFS和普通队列BFS的最大区别），所以我们在判重时 vis 数组其实记录的是当前到达这个点的最优解

2. 注意什么时候push到队首什么时候push到队尾：队首的状态一定比队尾的状态优，所以不需要改变方向的状态push到队首，需要改变的方向push到队尾。

更具体的思路见代码注释：

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cstring> 
using namespace std;

typedef long long ll;
const int NR = 105;
int n, m;
int a[NR][NR];
int vis[NR][NR];
char mp[NR][NR];
int x, y;		//起点坐标 
int ex, ey;		//终点坐标 
bool flg;
struct Node
{
	int x, y, t, last;
	//x, y：当前坐标 t：当前使用了多少个平面镜 last：上一步方向，即方向数组下标 
};
deque<Node> d;
//方向数组，不解释 
const int dx[] = {0, -1, 0, 0, 1};
const int dy[] = {0, 0, -1, 1, 0};

int main()
{
	cin >> m >> n;
	for(int i = 1; i <= n; i ++)
	{
		for(int j = 1; j <= m; j ++)
		{
			char c;
			scanf(" %c", &c);
			mp[i][j] = c;
		//	printf("%c", mp[i][j]);
			if(c == '.')
				a[i][j] = 0;
			else if(c == '*')
				a[i][j] = 1;
			else if(c == 'C')
			{
				if(!flg)
				{
					flg = true;
					x = i, y = j;
				}	
				else
					ex = i, ey = j;
			}
			//读入并寻找起点和终点 
		}
	//	puts("");
	}
	//开始BFS 
//	printf("%d %d %d %d\n", x, y, ex, ey);
	memset(vis, 0x3f, sizeof vis);
	d.push_front(Node{x, y, 0, 0});
	vis[x][y] = 0;
	while(!d.empty())
	{
		Node tmp = d.front();		//取出队首	 
//		printf("%d %d %d %d\n", tmp.x, tmp.y, tmp.t, tmp.last);
		d.pop_front();
		if(tmp.x == ex && tmp.y == ey)//到了终点 
		{
			cout << tmp.t << endl;
			return 0;
		}
		
		for(int i = 1; i <= 4; i ++)	//向四个方向走 
		{
			int xx = tmp.x + dx[i], yy = tmp.y + dy[i];//算坐标 
			if(xx <= 0 || xx > n || yy <= 0 || yy > m)	//判断是否出界 
				continue;
			if(tmp.last == 0 || i == tmp.last)//如果是第一步(last==0)或和上一步方向相同 
			{
				if(vis[xx][yy] >= tmp.t && a[xx][yy] != 1)//是最优解(vis[xx][yy] >= tmp.t)且没有障碍 
				{
					vis[xx][yy] = tmp.t;		//标记最优解 
					d.push_front(Node{xx, yy, tmp.t, i});//push到队首，因为平面镜数量不变 
				}
			}
			else										//与上一步方向不同 
			{
				if(vis[xx][yy] >= tmp.t + 1 && a[xx][yy] != 1) 
				{
					vis[xx][yy] = tmp.t + 1;
					d.push_back(Node{xx, yy, tmp.t + 1, i});//push到队尾，因为平面镜数量增加了1 
				}
			}
		}
	}
	return 0;
}
```


---

## 作者：saipubw (赞：6)

BFS大法吼，不开优化也能拿到23ms的成绩~~（话说洛谷为啥最少都需要2ms)~~

首先，我们从起点开始搜索。

搜索方法如下：


先看看这个点的上下左右四个方向有没有走过，如果没有就走走看。

比如往上,那么就不停的往上走，把遇到的每个点都加入队列

有几种情况下可以不用把这个点加入队列：

1.是终点，直接可以结束bfs

2.是障碍物/到达地图边界，这时候我们就不能接着往上走了，回到之前激光射出的点，这回我们不往上走，往左走………直到上下左右四个方向都走过了。然后我们就从序列中取出下一个点，接着bfs…………

3.之前已经有激光经过这里，并且方向相同，那么不用往上走了，换个方向吧

4.之前有激光经过这里，方向和我相反，那么也不用往上走了。

具体看代码吧

```c
//思路:BFS+疯狂剪枝
#include<stdio.h>
#include<string.h>
#define maxn 105
#define maxp 40005
int mark[maxn][maxn][4], map[maxn][maxn];
//mark:标记点(x,y)的四个方向是不是已经走过了
//map: 就是地图啦
const int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
//方向数组，方便枚举四个方向
struct POINT
{
	int x, y, mir;
}typedef Point;
//POINT:搜索时，对于每一个状态，我们要记录的有：x，y坐标，镜子数量
Point queue[maxp];
int bfs(void);//广度优先搜索，返回从起点到终点需要几个镜子，-1代表无解
void read(void);//读取地图，起点和终点
_Bool legal(Point p);//判断是否越界，是否遇到障碍物
int w, h;//地图的长宽
Point begin, end;
int main(void)
{
	memset(mark, 0, sizeof(mark));
    read();
    end.mir = bfs();
	printf("%d", end.mir);
	return 0;
}
int bfs(void)//重点
{
	int top = 0, tail = 1, i;
	Point now, lis;
	queue[0] = begin;//把起点加入队列
	while (top < tail)//队列不为空，接着搜索
	{
		now = queue[top++];//取出队首
		++now.mir;
		for (i = 0; i < 4; i++)//枚举上下左右四个方向
		{
			if (mark[now.x][now.y][i])//如果当前选择的方向已经走过了，就跳过
				continue;
			mark[now.x][now.y][i] = 1;//这个方向已经走过了，以后不用走了
			lis.x = now.x + dir[i][0];
			lis.y = now.y + dir[i][1];
			lis.mir = now.mir;
			while (legal(lis)&&(!mark[lis.x][lis.y][i]))//不断的往这个方向走，除非已经走过，或者遇到障碍物
			{
				if (lis.x == end.x&&lis.y == end.y)//发现终点，结束bfs
					return lis.mir;
                queue[tail++] = lis;//把点加入队列
                mark[lis.x][lis.y][i] = 1;//标记走过了
				mark[lis.x][lis.y][(i + 2) % 4] = 1；//相反的方向也走过了
				lis.x += dir[i][0];
				lis.y += dir[i][1];
			}
		}
	}
	return -1;//无解的时候才会跳到这里，返回-1代表无解。
}
inline _Bool legal(Point p)//内联函数：如果坐标未越界且未遇到障碍物，返回真，否则返回假
{
	return (1 <= p.x && p.x <= h && 1 <= p.y && p.y <= w && map[p.x][p.y] != '*');
}
void read(void)//这部分可以不用看了
{
    int temp = 1, i, j;
	char nouse[5];
	scanf("%d%d", &w, &h);//读取地图的长宽
	for (i = 1; i <= h; i++)
	{
		fgets(nouse, 5, stdin);//吃掉上一行的换行符
		for (j = 1; j <= w; j++)
		{
			map[i][j] = getchar();
			if (map[i][j] == 'C')
			{
				if (temp)//第一个遇到的‘C’当作是起点
				{
					begin.x = i;
					begin.y = j;
					begin.mir = -1;
					temp = 0;
				}
				else//第二个遇到的‘C’当作终点
				{
					end.x = i;
					end.y = j;
					end.mir = 0;
				}
			}
		}
	}
}
```

---

## 作者：GTAyin (赞：5)

数据较小，考虑爆搜，直接上DFS的板子
```c
#include<iostream>
#include<cstdio>
#include<cstring>
const int N=2e3;
using namespace std;
char map[N][N];
int n,m,cnt,ans=20000;
struct node {
	int x,y;
} e[3];
int next[4][2]= {{1,0},{0,1},{-1,0},{0,-1}};
bool viz[N][N];
void dfs(int x,int y,int w,int to) {
	if(x==e[2].x&&y==e[2].y) {
		ans=min(ans,w);
		return;
	}
	for(int i=0; i<4; i++) {
		int dx=x+next[i][0];
		int dy=y+next[i][1];
		if(map[dx][dy]!='*'&&!viz[dx][dy]&&dx<=m&&dx>=1&&dy<=n&&dy>=1) {	
		    viz[dx][dy]=true;
		        int f=0;//确定是否应该加镜子
			if(to!=i) f=1;//当方向不与当前方向一致时，就要加一面镜子
			if(to==-1) f=0;//当方向为-1时，则任何方向都行
			dfs(dx,dy,w+f,i);
		    viz[dx][dy]=false;
		}
	}
}
int main() {
	cin>>n>>m;
	for(int i=1; i<=m; i++) {
		for(int j=1; j<=n; j++) {
			cin>>map[i][j];
			if(map[i][j]=='C') {
				e[++cnt].x=i;//分别找到起点与终点
				e[cnt].y=j;
			}
		}
	}
	dfs(e[1].x,e[1].y,0,-1);//方向先标为-1，表示任何方向都行
	cout<<ans;
	return 0;
}
```

但我们惊讶的发现它TLE了，很惨。我们就不得不考虑剪枝。首先，因为我们找的是最小值，所以当我们在搜索时找到的w比ans还大的话，则果断放弃。其次，因为是深搜，所以一个点就不可避免的被访问很多次，这时我们就又要再多开一个数组表示每一个点当前状态的最小值，如果搜到时比存的还大，也果断放弃。于是AC代码就出来了。

```c
#include<iostream>
#include<cstdio>
#include<cstring>
const int N=2e3;
using namespace std;
char map[N][N];
int n,m,cnt,ans=20000;
struct node {
	int x,y;
} e[3];
int dis[N][N][5];
int next[4][2]= {{1,0},{0,1},{-1,0},{0,-1}};
bool viz[N][N];
void dfs(int x,int y,int w,int to) {
	if(w>=dis[x][y][to]) return;
	dis[x][y][to]=w;
	if(w>=ans) return ;
	if(x==e[2].x&&y==e[2].y) {
		ans=w;
		return;
	}
	for(int i=0; i<4; i++) {
		int dx=x+next[i][0];
		int dy=y+next[i][1];
		if(map[dx][dy]!='*'&&!viz[dx][dy]&&dx<=m&&dx>=1&&dy<=n&&dy>=1) {	
		    viz[dx][dy]=true;
		    int f=0;
			if(to!=i) f=1;
			if(to==-1) f=0;
			dfs(dx,dy,w+f,i);
		    viz[dx][dy]=false;
		}
	}
}
int main() {
	cin>>n>>m;
	for(int i=1; i<=m; i++) {
		for(int j=1; j<=n; j++) {
			cin>>map[i][j];
			if(map[i][j]=='C') {
				e[++cnt].x=i;
				e[cnt].y=j;
			}
		}
	}
	memset(dis,0x7f,sizeof(dis));
	dfs(e[1].x,e[1].y,0,-1);
	cout<<ans;
	return 0;
}
```

完结撒花！！！


---

## 作者：yangyujia18 (赞：5)

这道题是典型的01最短路  
可以用BFS，DFS也可以  
上DFS代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
struct point
{
	int x,y,cost,went;
};
const int INF=1000005;
int heng,shu,sx,sy,ex,ey,ans=INF,f[105][105][5];
bool m[105][105];
bool flag=false;
const int dx[4]={1,0,-1,0};
const int dy[4]={0,1,0,-1};
void dfs(int x,int y,int nans,int move)
{
	int xx,yy;
	if(move!=-1&&f[y][x][move]<=nans)
		return;
	if(move!=-1)
		f[y][x][move]=nans;
	if(nans>ans)
		return;
	if(x==ex&&y==ey)
	{
		ans=nans;
		return;
	}
	if(move!=-1)
	{
		xx=x+dx[move];
		yy=y+dy[move];
		if(!m[yy][xx]&&xx>=0&&xx<heng&&yy>=0&&yy<shu)
		{
			m[yy][xx]=true;
			dfs(xx,yy,nans,move);
			m[yy][xx]=false;
		}
	}
	for(int i=0;i<4;i++)
		{
			if(i==move)
				continue;
			xx=x+dx[i];
			yy=y+dy[i];
			if(!m[yy][xx]&&xx>=0&&xx<heng&&yy>=0&&yy<shu)
			{
				m[yy][xx]=true;
				dfs(xx,yy,nans+(move!=-1),i);
				m[yy][xx]=false;
			}
		}
	return;
}
int main()
{
	cin>>heng>>shu;
	memset(m,false,sizeof(m));
	for(int i=shu-1;i>=0;i--)
		for(int j=0;j<heng;j++)
		{
			char tmp;
			cin>>tmp;
			if(tmp=='*')
				m[i][j]=true;
			else
				m[i][j]=false;
			if(tmp=='C')
			{
				if(!flag)
				{
					sx=j;
					sy=i;
					flag=true;
				}
				else
				{
					ex=j;
					ey=i;
				}
			}
		}
	for(int i=0;i<105;i++)
		for(int j=0;j<105;j++)
			for(int l=0;l<5;l++)
				f[j][i][l]=INF;
	/*bfs();
	cout<<ans<<endl;*/
	m[sy][sx]=true;
	dfs(sx,sy,0,-1);
	cout<<ans<<endl;
	return 0;
}
```
第四次写题解~~前三次都被打回来了qwq~~  
支持我鸭！

---

## 作者：Limit (赞：4)

这题算是[P1126 机器人搬重物](https://www.luogu.org/problemnew/show/P1126)的升级版。
[P1126 机器人搬重物题解-传送门](https://blog.csdn.net/sxy__orz/article/details/85080143)
大概上思路就是找最少转弯次数(~~为什么我想到了-横冲直撞QAQ~~)对于这类问题BFS最方便了。。
```
const z:array[1..4,1..2]of-1..1=((1,0),(0,1),(-1,0),(0,-1));//方便呀
var i,j,k:longint;
    m,n:longint;
    a:array[0..200,0..200,1..4{四个方向}]of boolean;//判断是否走过
    ch:char;
    fx,fy,lx,ly:longint;
    h,t:longint;
    x{记录横坐标},y{记录纵坐标},u{记录当前转了几个弯},pfx{记录方向}:array[0..400000]of longint;//队列
    sum:array[0..200,0..200]of longint;//测试时的数组QAQ
begin
  readln(n,m);
  for i:=1 to m do
  begin
    for j:=1 to n do
    begin
      read(ch);
      if ch='C' then//找到起点和终点
      if fx=0 then
      begin
        fx:=i;
        fy:=j;
      end
      else
      begin
        lx:=i;
        ly:=j;
      end;
      if ch<>'*' then 
      begin
      for k:=1 to 4 do
      a[i,j,k]:=true;
      end;
    end;
    readln;
  end;
  //////////////////////////////队列处理开始了
  h:=1;
  t:=1;
  x[1]:=fx;
  y[1]:=fy;
  u[1]:=0;
  pfx[1]:=0;
  //////////////////////////////队列处理结束了
  a[fx,fy,1]:=false;//起点不可以再走
  a[fx,fy,2]:=false;
  a[fx,fy,3]:=false;
  a[fx,fy,4]:=false;
  repeat//标准的bfs
    if (x[t]=lx) and (y[t]=ly) then//到了呀
    begin
      write(u[t]-1);//第一个点开始没有方向所以比题目多转了一次要-1
      exit;
    end;
    for i:=1 to 4 do
    if i<>pfx[t] then//不可以和之前方向相同
    if a[x[t]+z[i,1],y[t]+z[i,2],i] then
    begin
      inc(h);//先把第一个点入队列
      x[h]:=x[t]+z[i,1];
      y[h]:=y[t]+Z[i,2];
      u[h]:=u[t]+1;
      pfx[h]:=i;
      a[x[h],y[h],i]:=false;
      sum[x[h],y[h]]:=u[h];
      while a[x[h]+z[i,1],y[h]+z[i,2],i] do//直到撞到....不然一直走
      begin
        inc(h);//入队列
        x[h]:=x[h-1]+z[i,1];
        y[h]:=y[h-1]+Z[i,2];
        u[h]:=u[t]+1;
        pfx[h]:=i;
        a[x[h],y[h],i]:=false;
        sum[x[h],y[h]]:=u[h];
      end;
    end;
    inc(t);
  until t>h;//bfs结束了QAQ
end.
```
这题其实不难呀，感觉比[P1126 机器人搬重物](https://www.luogu.org/problemnew/show/P1126)还简单....

---

## 作者：songhongyi (赞：2)

题意：最小转弯次数

考虑BFS，对于队头的每个点，向四个方向不断拓展，记录每个点的答案即可

但考虑到可能出现已访问的点可以被更少次数的转弯到达，所以对于已经访问过的点仍然接着走下去，但不需要再次入队

代码如下：
```cpp
//
// Problem: P2937 [USACO09JAN]Laserphones S
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2937
// Memory Limit: 125 MB
// Time Limit: 1000 ms

#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
struct Node
{
    int x, y;
    Node( int _x, int _y )
    {
        this->x = _x;
        this->y = _y;
    }
    Node() {}
};
queue< Node > q;
char a[ 110 ][ 110 ];
bool vis[ 110 ][ 110 ];
int ans[ 110 ][ 110 ];
const int dx[ 4 ] = { 0, 0, 1, -1 };
const int dy[ 4 ] = { 1, -1, 0, 0 };
int main()
{
    int n, m;
    cin >> m >> n;
    int x1, y1, x2, y2;
    bool f = 0;
    for ( int i = 1; i <= n; i++ )
    {
        for ( int j = 1; j <= m; j++ )
        {
            cin >> a[ i ][ j ];
            if ( f == 0 && a[ i ][ j ] == 'C' )
            {
                x1 = i, y1 = j;
                f = 1;
            }
            else if ( a[ i ][ j ] == 'C' )
            {
                x2 = i, y2 = j;
            }
        }
    }  //输入&处理起点和终点位置
    // cerr << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    q.push( Node( x1, y1 ) );
    while ( !q.empty() )
    {
        Node root = q.front();
        for ( int i = 0; i < 4; i++ ) //枚举四个方向
        {
            int gox = root.x + dx[ i ];
            int goy = root.y + dy[ i ];
            while ( gox >= 1 && gox <= n && goy >= 1 && goy <= m
                    && a[ gox ][ goy ] != '*' ) //不出界或遇到障碍物就不停
            {
                if ( !vis[ gox ][ goy ] )  //对于没到过的，更新拓展
                {
                    q.push( Node( gox, goy ) );
                    ans[ gox ][ goy ] = ans[ root.x ][ root.y ] + 1; //从起点到这里转弯了一次，所以要加1
                    if ( gox == x2 && goy == y2 )
                    {
                        cout << ans[ gox ][ goy ] - 1 << endl; //因为起点出发的第一个段也更新了答案，所以要减1
                        return 0;
                    }
                    vis[ gox ][ goy ] = 1;
                }
                gox += dx[ i ];
                goy += dy[ i ];  //无论到没到过都接着走
            }
        }
        q.pop();
    }
}
```

---

## 作者：da32s1da (赞：2)

数据较小，暴力即可。

我们从一个起点出发，枚举可以直接到达的点，然后**标记方向**，比如该点是横着搜过来的，那么标记该点**只能竖着搜**，然后用**vis[][]**标记一下，节约时间。

没想到是**最优解第一**OwO
```
#include<cstdio>
const int N=105;
int n,m,dt[N][N],lb[N][N],vis[N][N],net[N*N*3],cnt;
char s[N];
int x1,y1,x2,y2,bj,tot;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%s",&s);
		for(int j=0;j<n;j++){
			if(s[j]=='*') vis[i][j+1]=2;
			if(s[j]=='C') 
			if(!bj) x1=i,y1=j+1,bj=1;
			else x2=i,y2=j+1;
		}
	}
	vis[x1][y1]=1;
	net[++net[0]]=x1;
	net[++net[0]]=y1;
	net[++net[0]]=2;
	net[++net[0]]=10000001;
	while(true){
		int x=net[++cnt],y=net[++cnt],z=net[++cnt];
		if(z!=0){//横着搜
			if(y>1)
			for(int i=y-1;i>=1;i--){
				if(vis[x][i]==1) continue;
				if(vis[x][i]==2) break;
				if(vis[x][i]==0)
				vis[x][i]=1,net[++net[0]]=x,net[++net[0]]=i,net[++net[0]]=0;
				if(x==x2&&i==y2){printf("%d\n",tot);return 0;}
			}
			if(y<n)
			for(int i=y+1;i<=n;i++){
				if(vis[x][i]==1) continue;
				if(vis[x][i]==2) break;
				if(vis[x][i]==0)
				vis[x][i]=1,net[++net[0]]=x,net[++net[0]]=i,net[++net[0]]=0;
				if(x==x2&&i==y2){printf("%d\n",tot);return 0;}
			}
		}
		if(z!=1){//竖着搜
			if(x>1)
			for(int i=x-1;i>=1;i--){
				if(vis[i][y]==1) continue;
				if(vis[i][y]==2) break;
				if(vis[i][y]==0)
				vis[i][y]=1,net[++net[0]]=i,net[++net[0]]=y,net[++net[0]]=1;
				if(i==x2&&y==y2){printf("%d\n",tot);return 0;}
			}
			if(x<m)
			for(int i=x+1;i<=m;i++){
				if(vis[i][y]==1) continue;
				if(vis[i][y]==2) break;
				if(vis[i][y]==0)
				vis[i][y]=1,net[++net[0]]=i,net[++net[0]]=y,net[++net[0]]=1;
				if(i==x2&&y==y2){printf("%d\n",tot);return 0;}
			}
		}
		
		if(net[cnt+1]>10000000) tot++,net[++net[0]]=net[++cnt]+1;
	}
}
```

---

## 作者：caiwenkaiyaoyao (赞：2)

## 大致题意：

      就是给你一张图，有两个c表示起点和终点，光线可以从一个c到另一个c，光线可以沿直线传播，使用一个反光镜可以是光线旋转90度，问最少使用多少个，使得两个c联通，“*”光线不能通过。

## 解题思路
      
      一看到题目就感觉可以用bfs搜也不需要剪枝，因为规模比较小，关键处理旋转90度的问题，可以使用标记，处理之前是什么方向，然后就可以开始bfs模板
      
## 代码
```cpp
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
#include<stack>
#include<vector>
#include<cstdio>
#define ll long long
using namespace std;
const int maxn=110;
const int dir[4][2]={{0,-1},{0,1},{1,0},{-1,0}};//上下左右
int n,m;
bool vis[maxn][maxn][3];//标记坐标和方向
char tu[maxn][maxn];
struct newt
{
    int x,y,dir,cs;
}dian;
int main()
{
    int bx=-1,by=-1,ex,ey;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",tu[i]+1);
        for(int j=1;j<=m;j++)
        {
            if(bx==-1&&tu[i][j]=='C'){
                bx=i;by=j;
            }
            else if(bx!=-1&&tu[i][j]=='C')
            {
                ex=i;ey=j;
            }
        }
    }
    queue<newt>q;
    dian.x=bx;dian.y=by;dian.dir=0;dian.cs=-1;
    dian.dir=0;q.push(dian);dian.dir=2;q.push(dian);//方向0表示原来横着走，2表示原来竖着走，因为只能转990度，不能180度
    vis[bx][by][0]=1;vis[bx][by][2]=1;
    int ans=-1;
    while(!q.empty())
    {
        int x=q.front().x,y=q.front().y,fx=q.front().dir,cs=q.front().cs;
        q.pop();
        if(x==ex&&y==ey){ans=cs;break;}
        for(int i=0;i<2;i++)
        {
            int modx=dir[i+fx][0],mody=dir[i+fx][1];
            for(int j=1;j<=max(n,m);j++)//优先走不用使用反光镜，就是将一个方向能到的都走下
            {
                int nx=x+modx*j,ny=y+mody*j,nfx=(fx+2)%4;//方向在0，2之间变换
                if(nx<1||ny<1||nx>n||ny>m||tu[nx][ny]=='*')break;//如果出现*或者越界就退出
                if(vis[nx][ny][nfx])continue;
                dian.x=nx;dian.y=ny;dian.dir=nfx;dian.cs=cs+1;
                q.push(dian);
                vis[nx][ny][nfx]=1;
            }
        }

    }
    printf("%d\n",ans);//初始化ans=-1，最后就直接输出
    return 0;
}

```

---

## 作者：hulean (赞：1)

看到这题，一下就想到了爆搜。（不过这题输入也是够坑的）

爆搜的思路楼上楼下也说过了，这里详细解析一遍

单纯的搜索肯定是会超时的，所以这里需要考虑一些剪枝。

我们令``bin[i][j][k]``为在第i行j列时，方向为k的最小镜子数，若当时的镜子数已大于或等于此记录，那么就不必要更新了

否则往该点的四个方向进行更新：

- 方向相同

没必要放镜子了

- 方向相反

不存在这种可能，忽略（否则你的镜子要怎么放呢？）

- 其他

放一面镜子，更新方向

BFS代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100+10;
char Map[MAXN][MAXN];
int n,m;
int bx,by,ex,ey;
int dx[5]={0,0,1,0,-1};
int dy[5]={0,1,0,-1,0};
int ans=0x3f3f3f3f;
int bin[MAXN][MAXN][5];//剪枝用
struct Node
{
	int x,y;
	int cnt;
	int dir;//表示的方向
	/*
	1:right
	2:down
	3:left
	4:up
	*/
};
inline int read()
{
	int tot=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		tot=tot*10+c-'0';
		c=getchar();
	}
	return tot;
}
inline void BFS()
{
	queue<Node>q;
	q.push((Node){bx,by,0,1});//推四种方向到队列中
	q.push((Node){bx,by,0,2});
	q.push((Node){bx,by,0,3});
	q.push((Node){bx,by,0,4});
	bin[bx][by][1]=bin[bx][by][2]=bin[bx][by][3]=bin[bx][by][4]=0;
	while(q.size())
	{
		Node now=q.front();
		//cout<<now.x<<" "<<now.y<<" "<<now.cnt<<" "<<now.dir<<endl;
		q.pop();
		if(now.cnt>=ans)continue;
		if(now.x==ex&&now.y==ey)
		{
			ans=min(ans,now.cnt);//更新答案
			continue;//注意：这里不能用break
		}
		for(int i=1;i<=4;i++)
		{
			int a=dx[i]+now.x,b=dy[i]+now.y;
			if(a<1||b<1||a>n||b>m)continue;
			if(now.cnt>=bin[a][b][i])continue;//没必要更新了
			if(Map[a][b]=='*')continue;
			if(now.dir==i)
			{
				q.push((Node){a,b,now.cnt,i});
				bin[a][b][i]=now.cnt;//更新最小值
			}
			else 
			{
				if(now.dir+i==4)continue;//这是方向相反时，看不懂的回去看一下各个数字代表的方向
				q.push((Node){a,b,now.cnt+1,i});
				bin[a][b][i]=now.cnt+1;//更新最小值
			}
		}
	}
}
int main()
{
	m=read();n=read();
	memset(bin,0x3f3f3f3f,sizeof(bin));//赋初值
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>Map[i][j];
			if(Map[i][j]=='C'&&!bx&&!by)bx=i,by=j;//寻找起点
			else if(Map[i][j]=='C')ex=i,ey=j;//寻找终点
		}
	}
	BFS();
	/*for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			for(int k=1;k<=4;k++)cout<<bin[i][j][k]<<" ";
			cout<<endl;
		}
		cout<<endl<<endl;
	}*/
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：wanghanjun (赞：1)

这道题应该用bfs来做~~（但我不明白题目标签里为什么没有）~~

题目大意：求两点间路线最少的拐弯90度的次数

然后我们发现，这道题和[P1649](https://www.luogu.org/problemnew/show/P1649)很像呀。。。

大致思路：bfs，每次向上、下、左、右分别扩展到第一个障碍（或者到边界）结束，然后求出来的是答案+1。

如果还不理解请看代码：
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN=101;
char a[MAXN][MAXN];
bool vis[MAXN][MAXN];
int n,m,c=0,d=0;
struct node{
	int x,y,dis;
}tmp;
queue <node> q;

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%s",a[i]+1);
		for(int j=1;j<=n;j++){
			if(a[i][j]=='C'&&c==0&&d==0){
				c=i;d=j;
                //记录起点，避免直接输出-1
				tmp.x=i;tmp.y=j;
				tmp.dis=-1;
                //初始值赋-1
				q.push(tmp);
			}
		}
	}
	while(!q.empty()){
		node u=q.front();q.pop();
		if(vis[u.x][u.y]) continue;
		if(a[u.x][u.y]=='C'&&(u.x!=c||u.y!=d/*不同于起点*/)){
			printf("%d",u.dis);
			break;
		}//找到终点，输出答案
		vis[u.x][u.y]=1;
		for(int i=u.x;i>0;i--){
			if(a[i][u.y]=='*')
			    break;//遇到墙就结束
			else{
				tmp.x=i;tmp.y=u.y;
				tmp.dis=u.dis+1;
				q.push(tmp);
			}
		}//向上搜索
		for(int i=u.x;i<=m;i++){
			if(a[i][u.y]=='*')
			    break;
			else{
				tmp.x=i;tmp.y=u.y;
				tmp.dis=u.dis+1;
				q.push(tmp);
			}
		}//向下搜索
		for(int i=u.y;i>0;i--){
			if(a[u.x][i]=='*')
			    break;
			else{
				tmp.x=u.x;tmp.y=i;
				tmp.dis=u.dis+1;
				q.push(tmp);
			}
		}//向左搜索
		for(int i=u.y;i<=n;i++){
			if(a[u.x][i]=='*')
			    break;
			else{
				tmp.x=u.x;tmp.y=i;
				tmp.dis=u.dis+1;
				q.push(tmp);
			}
		}//向右搜索
	}
	return 0;
}
```
共72ms，虽然慢但是能过

效率。。。也许O(n^3)。。。

---

## 作者：Loser_King (赞：0)

### Part 0 前言

最近在USACO上找BFS的题来做，然后就翻到了这道题。

第一眼看上去有难度，但是只要把好BFS的主思想，解出这道题来也是很简单的事情了。

## Part 1 题意

> 给定一个点阵，从一个点出发，不穿过障碍物，只从上下左右四个方向移动任意步**并转向**花费一个单位。求从一个点到另一个点的最小花费单位数。

_注意：虽然这里所述的题意与原题意略有不同，但是这样可以更简单地帮助我们展开后面的BFS。_

## Part 2 做法

我们在设计BFS算法（DP也类似）时，总是要注意这几点：

1. **状态。**(节点)

   在这里，这个结构体`node`里只要有三个变量即可：`x`记录当前该点的横坐标，`y`当前该点的纵坐标，`stp(step)`记录当前已花费的单位。

   _（这里的x和y和题面中的x,y是不同的）_

   ```c++
   struct node{
   	int x,y,stp;
   	inline bool operator==(const node&r)const{
   		return x==r.x&&y==r.y;
   	}//判断两个节点是否相同，主要用于判断是否到达终点。（其实你也可以不写）
   }st,ed;//st表示起点，ed表示终点
   ```

2. **拓展。**(节点延伸)

   根据上面的题目描述可以看出，只要当前的点不是终点，就往四边拓展，碰到障碍物或边界才停止。

   为什么不记录当前的方向呢？因为一个节点被拓展时，它的方向和反方向上的`vis`一定皆为`true`。

   ```c++
   int const dx[]={0,0,1,-1,},dy[]={1,-1,0,0};//方向数组
   queue<int>q;
   void exp(node x){//expand拓展
   	for(int i=0;i<4;i++){//下上右左四个方向
   		node t=x;
   		while(t.x>0&&t.y>0&&t.x<=n&&t.y<=m&&mp[t.x][t.y]!=42){
                   //判断是否到达边界和障碍物
   		    if(!vis[t.x][t.y])vis[t.x][t.y]=1,q.push(t);
                   //如果这个节点已经到达过了，就不再入队
   		    t.x+=dx[i];t.y+=dy[i];
                   //开始不断移动
   		}
   	}
   }
   ```

3. **初始。**(初始节点)

   我在题意中加粗了几个字：**并转向**

   这是为什么呢？因为如果不转向的话，是不会消耗价值的。

   所以初始节点是`exp(st);`

4. **答案。**(终结点)

   显然。如果BFS的当前节点`==ed`，就输出答案。

## Part 3 代码

代码实现如下：（并没有加注释，主要部分上面都讲过了）

```c++
#include<bits/stdc++.h>
using namespace std;
int const N=233,dx[]={0,0,1,-1,},dy[]={1,-1,0,0};
int n,m,vis[N][N];
char mp[N][N];
struct node{
	int x,y,stp;
	inline bool operator==(const node&r)const{
		return x==r.x&&y==r.y;
	}
}st,ed;
queue<node>q;
void exp(node x){
	for(int i=0;i<4;i++){
		node t=x;
		while(t.x>0&&t.y>0&&t.x<=n&&t.y<=m&&mp[t.x][t.y]!=42){
		    if(!vis[t.x][t.y])vis[t.x][t.y]=1,q.push(t);
		    t.x+=dx[i];t.y+=dy[i];
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>m>>n;
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++){
	    	cin>>mp[i][j];
	    	if(mp[i][j]=='C'){
	    		node t=(node){i,j,0};
	    		if(st.x)ed=t;else st=t;
	    	}
	    }
	exp(st);
	while(!q.empty()){
		node x=q.front();q.pop();
		if(x==ed){cout<<x.stp<<endl;return 0;}
		x.stp++;exp(x);
	}
}
```



---

## 作者：Zekrom (赞：0)

   # 惨痛教训 
1.一开始觉得只有0，1边考虑用双端队列做最短路  
  结果发现就是普通队列就行了qaq  
  写挂了整整一小时  
2.原因：双端队列基于单调性，将0边放队头，1边放队尾，实现最短路的优化  
但由于此题激光的方向性，单调性不成立，故不能直接使用双端队列求最短路  
3.那么真正的做法，就是将vis数组扩展到3维，记录当前点某个方向是否被访问过，然后bfs求最短路即可  
上代码  
注意：bfs（）是写挂的双端队列 ，bfs2（）才是正解  
~~写错成双端队列好不甘心，不知道能不能改~~  
```cpp
#include<iostream>
#include<cstdio>
#define N 110
#include<deque>
#include<queue>
using namespace std;
bool map[N][N],flag,vis[N][N][5],cnt;
int n,m,sx,sy,ex,ey;
struct Node{
	int x,y,dir,val;
	void init(int v1,int v2,int v3,int v4){x=v1,y=v2,dir=v3,val=v4;}
}s[5]; 
int dx[]={0,-1,0,0,1};
int dy[]={0,0,1,-1,0};
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return  x*f;
}
void bfs(){//1↑2→3←4↓   //不能使用双端队列 
	deque<Node>q;
	vis[sx][sy][1]=vis[sx][sy][2]=vis[sx][sy][3]=vis[sx][sy][4]=1;
	for(int i=1;i<=4;i++){
		int x=sx+dx[i],y=sy+dy[i];
		while(x>=1&&x<=n&&y>=1&&y<=m&&!map[x][y]){
			Node s;s.init(x,y,i,0);vis[x][y][i]=vis[x][y][5-i]=1;
			q.push_front(s);
			x+=dx[i];y+=dy[i];
		}
	}
	while(q.size()){
		Node u=q.front();q.pop_front();
		for(int i=1;i<=4;i++){
			if(i==5-u.dir)continue;
			Node v;
			v.x=u.x+dx[i];v.y=u.y+dy[i];
			if(vis[v.x][v.y][i]||vis[v.x][v.y][5-i]||v.x<1||v.x>n||v.y<1||v.y>m||map[v.x][v.y])continue;
			vis[v.x][v.y][i]=vis[v.x][v.y][5-i]=1;
			if(i==u.dir){
				v.val=u.val,v.dir=u.dir,q.push_front(v);
				//if(cnt<=100)printf("%d %d val:%d dir:%d\n",v.x,v.y,v.val,v.dir),cnt++;
				if(v.x==ex&&v.y==ey){
					printf("%d\n",v.val);	
					return;
				}
				int x=v.x+dx[i],y=v.y+dy[i];
				while(!vis[x][y]&&!map[x][y]&&x>=1&&x<=n&&y>=1&&y<=m){
					Node s;s.x=x,s.y=y;s.val=v.val;s.dir=i;
					q.push_front(s);vis[x][y][i]=vis[x][y][5-i]=1;
					if(x==ex&&y==ey){
						printf("%d\n",s.val);
						return ;
					}
					x+=dx[i];y+=dy[i];
				} 
			}else {
				v.val=u.val+1,v.dir=i,q.push_back(v);
				//if(cnt<=100)printf("%d %d val:%d dir:%d\n",v.x,v.y,v.val,v.dir),cnt++;
				if(v.x==ex&&v.y==ey){
					printf("%d\n",v.val);
					return ;
				}
				int x=v.x+dx[i],y=v.y+dy[i];
				while(!vis[x][y]&&!map[x][y]&&x>=1&&x<=n&&y>=1&&y<=m){
					Node s;s.x=x,s.y=y;s.val=v.val;s.dir=i;
					q.push_back(s);vis[x][y][i]=vis[x][y][5-i]=1;
					if(x==ex&&y==ey){
						printf("%d\n",s.val);
						return ;
					}
					x+=dx[i];y+=dy[i];
				}
			}
		}
	}
}
void bfs2() {
	queue<Node>q;
	Node s;s.init(sx,sy,1,-1);
	q.push(s);
	while(q.size()){
		Node u=q.front();q.pop();
		u.val++;
		for(int i=1;i<=4;i++){
			if(vis[u.x][u.y][i])continue;
			vis[u.x][u.y][i]=1;
			Node v;
			v.x=u.x+dx[i];v.y=u.y+dy[i];v.val=u.val;
			while(v.x>=1&&v.x<=n&&v.y>=1&&v.y<=m&&!vis[v.x][v.y][i]&&!map[v.x][v.y]){
				if(v.x==ex&&v.y==ey){
					printf("%d\n",v.val);return; 
				}
				q.push(v);
				vis[v.x][v.y][i]=vis[v.x][v.y][5-i]=1;
				v.x+=dx[i];v.y+=dy[i]; 
			}
		}
	}
}
int main()
{
	m=read();n=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			char ch;cin>>ch;
			if(ch=='*')map[i][j]=true;
			else if(ch=='C'){
				if(flag)ex=i,ey=j;
				else sx=i,sy=j,flag=1;
			}
		}
	bfs2();
	return 0;
}

```


---

## 作者：杨铠远 (赞：0)

###### 记忆化搜索+vis数组
这道题只有一个坑：初始状态转弯无代价 姑且将此状态置为-1```
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
int n,m,tx,ty,ans=9998;
bool vis[101][101],flag;
char c;
int f[101][101][5];//记搜数组 
int fx[4]={0,0,1,-1};
int fy[4]={1,-1,0,0};
inline void dfs(int x,int y,int dir,int sum)
{
	if(f[x][y][dir]<=sum&&dir!=-1)return;//来过了 回头吧 
	if(dir!=-1)f[x][y][dir]=sum;//没来过  记一下 
	if(x==tx&&y==ty){//到达终点 
	if(ans>sum)ans=sum;
	return;
	}
	int nx,ny;//先不转弯 再尝试转弯 
	if(dir!=-1){
		nx=x+fx[dir];
		ny=y+fy[dir];
		if(vis[nx][ny]){
			vis[nx][ny]=0;
			dfs(nx,ny,dir,sum);//正常状态+不转弯   sum不变 
			vis[nx][ny]=1; 
		}
		for(int k=0;k<4;k++){
			if(k==dir)continue;//不能直走啦 
			nx=x+fx[k];
			ny=y+fy[k];
			if(vis[nx][ny]){
				vis[nx][ny]=0;
				dfs(nx,ny,k,sum+1);//     sum+1 
				vis[nx][ny]=1;
			}
		}
	}
	else{
		for(int k=0;k<4;k++){//初始状态  （乱搞）sum不变 
			nx=x+fx[k];
			ny=y+fy[k];
			if(vis[nx][ny]){
				vis[nx][ny]=0;
				dfs(nx,ny,k,sum);
				vis[nx][ny]=1;
			}
		}
	}
}
int main()
{
	int sx,sy;
	ios::sync_with_stdio(0);
	cin>>m>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>c;//思路主要是  能走VIS为一，其他都为0 比大佬们少用一个数组 
			if(c=='.')
			vis[i][j]=1;
			if(c=='C')
			{
				vis[i][j]=1;
				if(flag==0)//自已随便搞一个起点 一个终点 
				{
					sx=i;sy=j;
					flag=1;
				}
				if(flag==1) tx=i,ty=j;
			}
			if(c=='#'){
				vis[i][j]=0;
			}
		}
	}
	memset(f,127,sizeof(f));
//	for(int i=1;i<=100;i++)
//	for(int j=1;j<=100;j++)
//	for(int l=0;l<4;l++)
//	f[i][j][l]=9999;
	dfs(sx,sy,-1,0);
	cout<<ans<<endl;
	return 0;
}//赢了！ 
```
结束了 ~~绿题真简单~~



---

