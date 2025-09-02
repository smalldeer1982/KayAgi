# [USACO07FEB] Bronze Lilypad Pond B

## 题目描述

为了让奶牛们娱乐和锻炼，农夫约翰建造了一个美丽的池塘。这个长方形的池子被分成了 M 行 N 列个方格（1 ≤ M, N ≤ 30） 。一些格子是坚固得令人惊讶的莲花，还有一些格子是岩石，其余的只是美丽、纯净、湛蓝的水。

贝西正在练习芭蕾舞，她站在一朵莲花上，想跳到另一朵莲花上去，她只能从一朵莲花跳到另一朵莲花上，既不能跳到水里，也不能跳到岩石上。

贝西的舞步很像象棋中的马步：每次总是先横向移动 M1 (1 ≤ M1 ≤ 30)格，再纵向移动 M2 (1 ≤ M2 ≤ 30, M1≠M2)格，或先纵向移动 M1 格，再横向移动 M2 格。最多时，贝西会有八个移动方向可供选择。

给定池塘的布局和贝西的跳跃长度，请计算贝西从起点出发，到达目的地的最小步数，我们保证输入数据中的目的地一定是可达的。


## 样例 #1

### 输入

```
4 5 1 2
1 0 1 0 1
3 0 2 0 4
0 1 2 0 0
0 0 0 1 0```

### 输出

```
2```

# 题解

## 作者：顾z (赞：14)

# [顾z](http://www.cnblogs.com/-guz/)

题目描述--->[p2385 青铜莲花池](https://www.luogu.org/problemnew/show/P2385)

## 分析

很明显了,题目告诉我们有八个方向,当然优先考虑**bfs**!

很简单的bfs,重点在于**考虑清楚8个方向**.

~~自己刚开始打错了 emmm~~

给大家上一个图.↓

**(假定m1为3,m2为2)**

![](https://i.loli.net/2018/09/10/5b96513412cc0.png)

对应加减的就是我们的原来的坐标.

然后就完了 emmmm

~~感觉写的不算太丑~~

---------------------代码--------------------
```cpp
#include<bits/stdc++.h>
#define IL inline
#define RI register int
IL void in(int &x)
{
    int f=1;x=0;char s=getchar();
    while(s>'9' or s<'0'){if(s=='-')f=-1;s=getchar();}
    while(s>='0' and s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
int n,m,a,b,sx,sy,tx,ty;
int res[33][33];
bool vis[33][33];
int ax[10],ay[10];
struct cod{int x,y,step;};
IL int bfs()
{
	std::queue<cod>q;
	q.push((cod){sx,sy,0});
	vis[sx][sy]=true;
	while(!q.empty())
	{
		int x=q.front().x,y=q.front().y,cnt=q.front().step;
		if(x==tx and y==ty)return cnt;
		q.pop();
		for(RI i=1;i<=8;i++)
		{
			int nx=x+ax[i],ny=y+ay[i];
			if(nx<1 or nx>n or ny<1 or ny>m )continue;
			if(vis[nx][ny]==true or res[nx][ny]==0 or res[nx][ny]==2)continue;
			if(nx==tx and ny==ty)return cnt+1;
			q.push((cod){nx,ny,cnt+1});
			vis[nx][ny]=true;
		}
	}
}
main(void)
{
	in(n),in(m),in(a),in(b);
	for(RI i=1;i<=n;i++)
		for(RI j=1;j<=m;j++)
		{
			in(res[i][j]);
			if(res[i][j]==3)sx=i,sy=j;
			if(res[i][j]==4)tx=i,ty=j;
		}
	if(a!=b)
	{
		ax[1]=a,ay[1]=b;
    	ax[2]=a,ay[2]=-b;
    	ax[3]=-a,ay[3]=b;
    	ax[4]=-a,ay[4]=-b;
    	ax[5]=b,ay[5]=a;
    	ax[6]=b,ay[6]=-a;
    	ax[7]=-b,ay[7]=a;
    	ax[8]=-b,ay[8]=-a;
	}
	printf("%d",bfs());
}
```

---

## 作者：yyandy (赞：9)

## 此题也可以用DFS
本蒟蒻写一篇DFS

思路很简单，真的非常类似跳马问题

是简单的DFS

但注意：

要写记忆化，否则TLE

还有，注意，题目说，可以向8个方向

如果只写了四个方向，就只能对2个点

注释见代码
```cpp
#include<iostream>
using namespace std;
int a[100][100],f[100][100],i,j,n,m,m1,m2,x1,y1,x2,y2;
//f[i][j]记录到i行j列最少要用几步
int xd[10];
int yd[10];
inline void dfs(int x,int y,int k)//x,y坐标，k步数
{
	int i=0;
	if (a[x][y]==0||a[x][y]==2||f[x][y]<=k||x<0||y<0||x>n||y>m)
	return;
    //如果是边界，退出
   //如果x,y是石头或者水，退出
   //如果当前路径比已知路径长，退出
	f[x][y]=k;
   //否则标记为最短路径
	if (a[x][y]==4)
	return;
    //到达了终点，不用搜索了
	for (i=1;i<=8;i++)
	dfs(x+xd[i],y+yd[i],k+1);//向8个方向搜索
}
int main()
{
	cin>>n>>m>>m1>>m2;
    
 xd[1]=m1;xd[2]=m1;xd[3]=0-m1;xd[4]=0-m1;
 yd[5]=m1;yd[6]=m1;yd[7]=0-m1;yd[8]=0-m1;
 xd[5]=m2;xd[6]=0-m2;xd[7]=0-m2;xd[8]=m2;
 yd[1]=m2;yd[2]=0-m2;yd[3]=0-m2;yd[4]=m2;
 //设置8个方向
	for (i=1;i<=n;i++)
	for (j=1;j<=m;j++)
	{
		f[i][j]=210000000/3;
       //f初始化
	cin>>a[i][j];
	if (a[i][j]==3)
	{
		x1=i;
		y1=j;
        //寻找起点
	}
	if (a[i][j]==4)
	{
		x2=i;
		y2=j;
        //寻找终点
	}
}
	
	dfs(x1,y1,0);
	cout<<f[x2][y2];//最小结果存在里面了
 } 
```
会的人请略过这一段

记忆化：用一个数组标记最短的路径，

可以节省大量的时间（以空间换时间）

~~（所以就不会TLE了）~~

---

## 作者：维迭生 (赞：6)

标准的搜索题（就比如什么迷宫之类的），所以适合用来练广搜或深搜的熟练度。  
我更倾向于用广搜来写（因为深搜更好写嘛，而且比如单词接龙这些题目只能用深搜写，到时候再练）。  
广搜的思想，就是只处理“在手边上的事”；而深搜是“一条道走到黑”；具体来说，对一个状态（比如在迷宫中的位置），我们需要做四件事：  
  （1）检验是否处理完了整个事件（比如走到了出口），  
  以及（2and3）扩展（就是接下来能往那些方向走），  
  并（4）标记本状态为“已访问”，防止掉头回到这个状态。  
  广搜是扩展完再进入下一层，深搜是对一个状态扩展出的状态再扩展，尽可能"深"地搜索一张图。  
那么，广搜如何实现呢？  
我建议使用STL里的队列 (queue)(queue) 容器。  
想象你每一个扩展到的结点去排队，等待处理；排到的结点做那四件事，扩展出的新结点再去排队，直到找到目标为止。  
在你的头文件里加上#include<queue>  
  并在“using namespace std;”后加上“queue<int>q;”  
  来使用queue；  
  
queue的常用操作：

q.push() :让结点去排队  
q.front() :排最前面的结点。  
q.pop() :处理完毕，最前面的结点离开。  
q.empty() :队列里是否还有结点（有则为true）。  

经常你能看到诸如pair<int,int>以及q.push(make_pair(x,y))之类的东西，那是因为系统自带的queue只能处理一个东西，如果你想把两个东西放进去就只有让它们成为“一对”，这就用到了pair。  
某些情况下，我们可以用vis数组储存步数来减小空间复杂度（比如本题）。  
代码见下：  
```
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=35;
int n,a,b,m,p,steps;
string s="suzhidiaocha";	//虽然本题均可到达，但还是防止万一
int maps[MAXN][MAXN];		//存图
int vis[MAXN][MAXN];		//存步数
void bfs(int sx,int sy,int fx,int fy){
    queue <pair<int ,int> >q;
    int dx[]={a,b,-a,-b,a,b,-a,-b};		//八个方向
    int dy[]={b,a,b,a,-b,-a,-b,-a};
    q.push(make_pair(sx,sy));			//基本上这就是模板了
    while(!q.empty()){
        int x=q.front().first;
		int y=q.front().second;
        if(x==fx&&y==fy){				//到终点就输出终点的步数，返回主程序
            cout<<vis[fx][fy]<<endl;
            return ;
        }
        q.pop();
        for(int z=0;z<=7;z++){
        	int nx=x+dx[z];
        	int ny=y+dy[z];
            if(nx<=m&&ny<=n&&nx>=1&&ny>=1&&!vis[nx][ny]&&maps[nx][ny]==1){								//走得通
                vis[nx][ny]=vis[x][y]+1;	//存步数
                q.push(make_pair(nx,ny));	//	去排队
            }
        }
    }
    cout<<s<<endl;		//假如队空了也没找到，就是到不了
    return ;
}
int main(){
	int sx,sy,fx,fy;
    cin>>m>>n>>a>>b;
    for(int i=1;i<=m;i++){
    	for(int j=1;j<=n;j++){
    		cin>>maps[i][j];
    		if(maps[i][j]==3){		//	找起始点
    			sx=i;				//标记
    			sy=j;
    			maps[i][j]=1;
			}
			if(maps[i][j]==4){		//终点
				fx=i;
				fy=j;
				maps[i][j]=1;
			}
		}
	}
	
	bfs(sx,sy,fx,fy);
	
    return 0;			结束
}

```


---

## 作者：AveMarina (赞：4)

# 别样的小技巧
__看到求最短路径且边权为固定值的题一般都可以用广搜__ 当然这是前人经过证明才得到的结论~~反正我不会证啦~~

那么就和我上面说的一样，这个题用广搜就能AC了，但是，这篇题解并不是为了介绍BFS，而是希望能教大家一个技巧:__如何更方便的标记访问过的点__

对于这个题而言，地图上的每个点都只有两种状态（岩石和水都是无法访问，所以是一个状态）：__访问过或未访问，且访问过的点无法再次访问__，那么由此我们可以发现，既然访问过的点已经没必要访问了，__那为什么不把它直接改成不能访问的点呢__

__利用上面这个技巧，我们可以少开一个数组记录是否访问，而且标记访问只需要赋值为非法值即可__，其实这个技巧不仅适用于BFS，还 __适用于DFS__

__在DFS里存在一个回溯的过程，那么我们只需要把当前走的点用一个变量存起来，在回溯的过程中再把它还原回去就行__

## 例如

```cpp
dfs(int x, int y){
	int temp = graph[x][y];
   graph[x][y] = 访问过;
   ...
   graph[x][y] = temp; // 还原该点状态
}
```
## 但是
这种方法并不适用于所有题目，如果有的题目一个 __点的值__ 会被多次使用，那么大家最好还是不要这样写!

### 正题
__一个标准的BFS，这里就不多介绍了~~__
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
struct Node {
	int x, y, step;
	Node(int x, int y, int step) : x(x), y(y), step(step) {}
	Node() {}
};
const int N = 35;
int m, n, m1, m2;
bool graph[N][N];
int sx, sy, ex, ey;
int move[8][2];
Node que[N * N];
int bfs(int sx, int sy) {
	int qtop = 0, qback = 0;
	que[qtop] = Node(sx, sy, 0);
	while (qtop <= qback) {
		Node now = que[qtop++];
		if (now.x == ex && now.y == ey) return now.step;
		for (int i = 0; i < 8; i++) {
			int nx = now.x + move[i][0], ny = now.y + move[i][1];
			if (nx > n || nx < 1 || ny > m || ny < 1) continue;
			if (!graph[nx][ny]) continue;
			// 标记为走过，不然会有重复访问 
			graph[nx][ny] = false;
			que[++qback] = Node(nx, ny, now.step + 1);
		}
	}
	return 0;
}
// 初始化八个方向的走法
void initMove() {
	move[0][0] = m1, move[0][1] = m2;
	move[1][0] = m2, move[1][1] = m1;
	move[2][0] = -m1, move[2][1] = m2;
	move[3][0] = -m2, move[3][1] = m1;
	move[4][0] = m1, move[4][1] = -m2;
	move[5][0] = m2, move[5][1] = -m1;
	move[6][0] = -m1, move[6][1] = -m2;
	move[7][0] = -m2, move[7][1] = -m1;
}
int main() {
	scanf("%d%d%d%d", &n, &m, &m1, &m2);
	int t;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
        // 岩石和水可以标记为“已访问”，这样判断时只用处理两个状态
			scanf("%d", &t);
			if (t == 3) sx = i, sy = j;
			else if (t == 4) ex = i, ey = j;
			else if (t != 1) t = 0;
			graph[i][j] = t;
		}
	}
	initMove();
	cout << bfs(sx, sy);
	return 0;
}
```
第一次交忘了改访问状态，我太蒻了..~~结果就RE了几个点~~

---

## 作者：NIMNIM (赞：4)

## 这道题我有两个阶段：

1.只会用深搜[（评测记录是这样的）](https://www.luogu.org/record/20097169)

2.学会用广搜+卡常了【显然我是菜鸡】[评测记录变成了这样的](https://www.luogu.org/record/23522736)

咳咳，现在我们来讲一下相对会快辣么一点点的广搜+hash，当然也可以双向广搜（但这只是一道黄题）

广搜呢定义我不想解释得太冗杂，这里就从网上找一个给大家看看：

 _“广度优先搜索（也称宽度优先搜索，缩写BFS，以下采用广度来描述）是连通图的一种遍历策略。因为它的思想是从一个顶点V0开始，辐射状地优先遍历其周围较广的区域，故得名。”_ 
 
简单概括一下，就是说：每次扩展到一个状态时，就将其所能到达的所有状态记录入队列，并继续从原来已经在队列的状态中继续扩展，有一种辐射的形状。
~~一般广搜我个人喜欢用STL队列记录状态~~

至于hash呢，主要就是在搜索的基础上加上判断状态是否重复，比如上面那段话加上hash就可以变成这样：

每次扩展到一个状态时，就将其所能到达的所有状态（除了已经推到的状态）记录入队列，并继续从原来已经在队列的状态中继续扩展，有一种辐射的形状。

这道题里面呢，还有一点就是有不能走到的地方，这时候只要加一个特判就行了

代码先放出来：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
#define coi const int
#define il inline int
#define re register int
int n,m,m1,m2,stx,sty,edx,edy;
int a[35][35],dis[35][35];
bool hash[35][35]={};
int dx[4]={-1,1,-1,1},
	dy[4]={-1,-1,1,1};
int main ( )
{
	scanf("%d%d%d%d",&n,&m,&m1,&m2);
	for(re i=1;i<=n;i++)
		for(re j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			if(a[i][j]==3) stx=i,sty=j;
			if(a[i][j]==4) edx=i,edy=j,a[i][j]=1;
		}
	queue <int> quex;  queue <int> quey;
	quex.push(stx);    quey.push(sty);
	hash[stx][sty]=true;dis[stx][sty]=0;
	int xx,yy,x,y;
	while(!quex.empty())
	{
		xx=quex.front();quex.pop();
		yy=quey.front();quey.pop();
		if(xx==edx&&yy==edy) break;
		for(re i=0;i<=3;i++)
		{
			x=dx[i]*m1+xx;y=dy[i]*m2+yy;
			if(!hash[x][y]&&a[x][y]==1&&x>=1&&x<=n&&y>=1&&y<=m)
				hash[x][y]=true,dis[x][y]=dis[xx][yy]+1,
				quex.push(x),quey.push(y);
		}
		swap(m1,m2);
		for(re i=0;i<=3;i++)
		{
			x=dx[i]*m1+xx;y=dy[i]*m2+yy;
			if(!hash[x][y]&&a[x][y]==1&&x>=1&&x<=n&&y>=1&&y<=m)
				hash[x][y]=true,dis[x][y]=dis[xx][yy]+1,
				quex.push(x),quey.push(y);
		}
	}
	printf("%d",dis[edx][edy]);
}
```
然后解释一下：

1.这里的dx，dy是移动的距离，中间的swap其实就是将原来的四个方向换一下，再搜索四个方向

2.hash数组就是上面的hash的用法

3.stx是出发的x坐标，sty是出发的y坐标，edx是结束的x坐标，edy是结束的y坐标 ~~（其实就是英文缩写）~~

4.xx，yy是当前节点的横纵坐标，即状态


还有问题的可以私信我 ~~（如果我通过了题解）~~，我只要有时间，应该大概或许都会回你的

---

## 作者：Dr_殇 (赞：3)

#一道DFS题目，如果简单粗暴的不用剪枝的DFS肯定会超时（[就像这样](https://www.luogu.org/record/show?rid=4769919)），所以我们应该优化。

#题目分析

裸的DFS，不过话说其实DFS和BFS是通用的，不过闪现本人不会BFS，于是就用DFS了。（楼下的BFS根本看不懂）

我们只要每个点搜索一点下一个点是不是可以搜（有8个方向），如果搜到了就更新答案，然后如果每个点的价值比原来方法走的价值还要多的话就剪枝（为什么要继续走啊，Bessie又不傻）。

##代码如下：





```cpp
//--新阶梯工作室防伪水印--
//--By新阶梯工作室 闪现--
#include <ctime>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>//头文件准备
#define in freopen (".in","r",stdin)
#define out freopen (".out","w",stdout)
#define INF 2147483647
#define UNINF -2147483648ll
#define ch char
#define bo bool
#define ui unsigned int
#define ll long long//闪现为了少打几个字符，弄了好多好多宏定义
using namespace std;
int n,m,a,b,ans=INF,map[35][35],d[35][35],dx[9],dy[9];//dx和dy是方向数组，map数组用于存储池塘，d数组用于存储当前最优解，ans一开始要赋为无穷大
inline void dfs(int x,int y,int tmp);
inline void work();
int main(){
    //in;out;
    work();
    return 0;
}
inline void dfs(int x,int y,int tmp){//搜索函数
    if (d[x][y]<=tmp)return;//如果用这个走法的价值比最优价值大，就剪枝
    if (map[x][y]==4){ans=min(ans,tmp);return;}//如果到达了终点就更新答案
    map[x][y]=0;//将这个点赋为0，以防兜圈子
    d[x][y]=tmp;//这个解就是当前的最优解
    for (int i=1;i<=8;i++){//然后搜索8个方向
        if (x+dx[i]>=1&&x+dx[i]<=n&&y+dy[i]>=1&&y+dy[i]<=m&&(map[x+dx[i]][y+dy[i]]==1||map[x+dx[i]][y+dy[i]]==4))dfs(x+dx[i],y+dy[i],tmp+1);//如果不越界且不是水和石头，就继续搜索
    }
    map[x][y]=1;//然后将它赋为原值
}
inline void work(){
    int x,y;
    scanf ("%d %d %d %d",&n,&m,&a,&b);
    dx[1]=a,dy[1]=b;
    dx[2]=a,dy[2]=-b;
    dx[3]=-a,dy[3]=b;
    dx[4]=-a,dy[4]=-b;
    dx[5]=b,dy[5]=a;
    dx[6]=b,dy[6]=-a;
    dx[7]=-b,dy[7]=a;
    dx[8]=-b,dy[8]=-a;//8个方向，实在不懂可以自己画画，就和马的走法一样
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            d[i][j]=INF;//注意，一定要将d数组赋为无穷大，如果赋为0根本做不起来
            scanf ("%d",&map[i][j]);
            if (map[i][j]==3)x=i,y=j;//如果这个点是起点就记下来
        }
    }
    dfs(x,y,0);//搜索
    if (ans==INF)printf ("-1\n");//如果ans没变，那么就是无法到达
    else printf ("%d\n",ans);//否则就输出答案
}

```

---

## 作者：暴力出奇迹NB (赞：2)

看到大部分题解都是 BFS，在这里来一发 DFS     
(我的BFS写得像 sh*t 一样 qwq)

1. 第一步，我们肯定会先想到裸搜
```
//TLE的裸搜
#include<stdio.h>
int m,n,m1,n1,a[35][35];
int t[35][35],x,y;
int dx[10],dy[10],ans=2147483647; 
void dfs(int x,int y,int z){
	if(a[x][y]==4){
		if(z<ans)ans=z;
		return;
	}
	for(int i=1;i<=8;i++){
		int xx=x+dx[i],yy=y+dy[i];
		if(a[xx][yy]&&t[xx][yy]==0&&xx>=1&&xx<=n&&yy>=1&&yy<=m){
			t[xx][yy]=1;
			dfs(xx,yy,z+1);
			t[xx][yy]=0; 
		}
	}
}
int main(){
	scanf("%d%d%d%d",&n,&m,&n1,&m1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
			if(a[i][j]==2)a[i][j]=0;
			if(a[i][j]==3)x=i,y=j;
		}
	}
	dx[1]=m1,dy[1]=n1;
	dx[2]=m1,dy[2]=-n1;
	dx[3]=-m1,dy[3]=-n1;
	dx[4]=-m1,dy[4]=n1;
	dx[5]=n1,dy[5]=m1;
	dx[6]=n1,dy[6]=-m1;
	dx[7]=-n1,dy[7]=-m1;
	dx[8]=-n1,dy[8]=m1;
	dfs(x,y,0);
	printf("%d",ans);
	return 0;
}
```
结果 TLE 5个点……

2. 接下来想想怎么优化呢？                
我们可以在 DFS 中 加一段代码```if(z>=ans)return;```
如果当前步数已经超过答案，那么肯定舍去

结果 TLE 1个点……

3. 这个时候，我们就要用到**记忆化搜索**   
设一个二维数组f，它存的是当前位置的最优解，如果当前步数大于它，直接舍去

接下来上 AC 代码,无坑请放心食用（含注释）：

```
#include<stdio.h>
int m,n,m1,n1,a[35][35];
int f[35][35]={2147483647},t[35][35],x,y;//x,y存起点，t数组防止走重复 
int dx[10],dy[10],ans=2147483647;
//ans和f数组都要赋最大值哦~ 
void dfs(int x,int y,int z){
	if(z>=ans)return;//最优性剪枝，因为有记忆化搜索可以不加 
	if(f[x][y]<=z)return;//记忆化搜索 
	if(a[x][y]==4){//走到终点 
		if(z<ans)ans=z;//找最少步数 
		return;
	}
	f[x][y]=z;//将当前步数存进f数组 
	for(int i=1;i<=8;i++){//8个方向搜索 
		int xx=x+dx[i],yy=y+dy[i];
		//注意判断边界和有没有走过 
		if(a[xx][yy]&&t[xx][yy]==0&&xx>=1&&xx<=n&&yy>=1&&yy<=m){ 
			t[xx][yy]=1;
			dfs(xx,yy,z+1);
			t[xx][yy]=0;//恢复状态 
		}
	}
}
int main(){
	scanf("%d%d%d%d",&n,&m,&n1,&m1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			f[i][j]=2147483647;
			scanf("%d",&a[i][j]);
			if(a[i][j]==2)a[i][j]=0;//2是石头，也不能走 
			if(a[i][j]==3)x=i,y=j;//记下起点 
		}
	}
	//八个方向赋值 
	dx[1]=m1,dy[1]=n1;
	dx[2]=m1,dy[2]=-n1;
	dx[3]=-m1,dy[3]=-n1;
	dx[4]=-m1,dy[4]=n1;
	dx[5]=n1,dy[5]=m1;
	dx[6]=n1,dy[6]=-m1;
	dx[7]=-n1,dy[7]=-m1;
	dx[8]=-n1,dy[8]=m1;
	dfs(x,y,0);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：chenxirui (赞：2)

### ~~个人认为这是普及-，因为太经典了~~


------------

## 其实捏，这是一道很简单的dfs，只需要稍稍记忆化一下就AC了




------------
# 相信大家有很多疑惑（大佬勿喷）：如何想到记忆化？

###### ~~被虐多了~~

看到步数就容易想到：
如果有两条路径，都可以到达同一个点，那么哪条路程段就走哪条。

秉承这条思想，我们只需把每个点的最短步数记下来，就可以提高很多效率

只要这条路到达某个点比这个点所需的的最短路径长或者一样，就直接返回

### 那么，我们上代码：
```cpp
#include<cstdio>
#include<cstring>
const int N = 35;
int n, m, m1, m2, g[N][N], z, minn[N][N], sx, sy, fx, fy, dx[8], dy[8], ans = 2e9;
bool v[N][N];

void dfs(int x, int y, int cnt)//cnt代表当前已走的步数
{
	if(x < 1 || y < 1 || x > n || y > m) return；//边界条件，其实不加也不影响
	if(x == fx && y == fy)
	{
		ans = ans>cnt?cnt:ans;//记得ans是最小值
		return;
	}
	for(int i = 0; i <= 7; i++)
	{
		int xx = x+dx[i], yy = y+dy[i], cc = cnt+1;
		if(v[xx][yy] == 0 && cc < minn[xx][yy] && g[xx][yy])//判断要不要走下一步
		{
			v[xx][yy] = 1;
			minn[xx][yy] = cc;
			dfs(xx, yy, cc);
			v[xx][yy] = 0;//记得恢复状态
		}
	}
}


int main()
{
	scanf("%d%d%d%d", &n, &m, &m1, &m2);
	int ddx[8] = {m1,m1,-m1,-m1,m2,m2,-m2,-m2};
	int ddy[8] = {m2,-m2,m2,-m2,m1,-m1,m1,-m1};//记下八个方向
	memcpy(dx, ddx, sizeof(dx));
	memcpy(dy, ddy, sizeof(dy));
	for(int i = 1; i <= 30; i++)
	{
		for(int j = 1; j <= 30; j++)
		{
			minn[i][j] = 900;//记得最小值要初始化
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			scanf("%d", &z);
			if(z == 1)
			{
				g[i][j] = 1;
			}
			else if(z == 3)
			{
				g[i][j] = 1;
				v[i][j] = 1;
				sx = i;
				sy = j;
			}//起点
			else if(z == 4)
			{
				g[i][j] = 1;
				fx = i;
				fy = j;
			}//终点
		}
	}
	dfs(sx, sy, 0);
	printf("%d", ans);//华丽的结束吧
	return 0;
}
```
### 这样看下来，这道题是不是很明朗了？


---

## 作者：氟铀碳钾 (赞：2)

本蒟蒻的第一篇题解（希望各位大佬不要鄙视）

这其实是一道宽搜题

题目中的条件很好，限制了很多的不能跳的点


接下来是代码（码风奇特，多多包涵）

```c
#include<bits/stdc++.h>
using namespace std;
int a[31][31]={0},step[31][31]={0};//分别为该点的类型，和到该点的步数
int gx[8],gy[8];//提前列举八种走向
bool pd[31][31]={0};//判断是否宽搜到过
int n,m,n1,m1;
int sx,sy,ex,ey;//记录开始的点和结束的点
void hgc(int x,int y)//宽搜BFS
{
	int xxx,yyy;
	queue<int> xx,yy;
	xx.push(x);
	yy.push(y);
	while(!xx.empty())
	{
		xxx=xx.front();
		yyy=yy.front();
		xx.pop();
		yy.pop();
		for(int i=0;i<8;i++)
		{
			if(pd[xxx+gx[i]][yyy+gy[i]]==0&&(a[xxx+gx[i]][yyy+gy[i]]==1||a[xxx+gx[i]][yyy+gy[i]]==4)&&yyy+gy[i]<=m&&yyy+gy[i]>0&&xxx+gx[i]>0&&xxx+gx[i]<=n)//判断是否可跳
			{
				xx.push(xxx+gx[i]);
				yy.push(yyy+gy[i]);
				pd[xxx+gx[i]][yyy+gy[i]]=1;
				step[xxx+gx[i]][yyy+gy[i]]=step[xxx][yyy]+1;
			}
		}
	}
}
int main()
{
	cin>>n>>m>>n1>>m1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			if(a[i][j]==4)
			{
				ex=i;
				ey=j;
			}
			if(a[i][j]==3)
			{
				sx=i;
				sy=j;
			}
         //记录开始的点和结尾的点
		}
	}
	gx[0]=n1;
	gx[1]=n1;
	gx[2]=-n1;
	gx[3]=-n1;
	gx[4]=m1;
	gx[5]=m1;
	gx[6]=-m1;
	gx[7]=-m1;
	gy[0]=m1;
	gy[1]=-m1;
	gy[2]=m1;
	gy[3]=-m1;
	gy[4]=n1;
	gy[5]=-n1;
	gy[6]=n1;
	gy[7]=-n1;//记录跳动方式
	pd[sx][sy]=1;
	hgc(sx,sy);
	cout<<step[ex][ey]<<endl;
	return 0;
}
```
希望大家多多支持，有什么问题或建议可以评论  Orz

[个人博客有兴趣可以看一下（不过可能空空如也）](https://www.luogu.org/blog/hgczs/)

---

## 作者：樱式分解 (赞：2)

### 一道求路线最短的题，我们可以用宽搜
## 不要害怕，代码很短。
```
#include <iostream>
using namespace std;
int n,m;
int m1,m2;
int a[31][31];
int vis[31][31];
int x,y;
int t=1,w=1;
int q[1010][2];
int dp[31][31];//记步数
bool flag=false;//flag可以提前判断然后停止循环。
int main(){
	cin>>m>>n>>m2>>m1;
	int dx[10]={m2,-m2,m1,-m1,m2,-m2,m1,-m1};//方向组
	int dy[10]={m1,m1,m2,m2,-m1,-m1,-m2,-m2};
	for(int i=1;i<=m;i++)
	for(int j=1;j<=n;j++){
	cin>>a[i][j];
      if(a[i][j]==3)q[t][0]=i,q[t][1]=j,dp[i][j]=0;加入队头
	}\\下面开始宽搜。
	while(t<=w){
    for(int s=0;s<8;s++){
	x=dx[s]+q[t][0];
	y=dy[s]+q[t][1];
       if(x>0&&x<=m&&y>0&&y<=n）//判断是否出界
       if((a[x][y]==1||a[x][y]==4)&&!vis[x][y]){//判断有是否过和可以走
		vis[x][y]=true;//标记走过
	q[++w][0]=x;
	q[w][1]=y;
        dp[x][y]=dp[q[t][0]][q[t][1]]+1;//这里一定要加一，而不是++，否则自增，我因此wa
	if(a[x][y]==4){
	flag=true;//标记走过
	break;
	}
       }
      }if(flag)break;t++;//如果找到就退出，否则继续
     }
	cout<<dp[x][y]<<endl;//x,y没变，直接输
	return 0;
}
```
### 用心写题解，希望给大家带来点帮助呀！


---

## 作者：installb (赞：2)

标准的BFS题  
有点像马的遍历 输入$ M_1 $和$ M_2 $处理出向八个方位走x y加上的值  
$ (+M_1,+M_2),(-M_1,M_2),(+M_1,-M_2),(-M_1,-M_2),(+M_2,+M_1),(-M_2,+M_1),(+M_2,-M_1),(-M_2,-M_1) $  
由于BFS是一层一层往下搜索的 每一层步数+1 所以第一次搜到终点一定是最优解 搜到就直接出答案并退出  
~~题目似乎默认了一定有解~~  
## code:
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
#include <string>
#define LL long long
using namespace std;

int dx[8],dy[8];
int mp[35][35] = {0};
int m,n,m1,m2,sx,sy,tx,ty;

struct node{
	int x,y,step;
}nd;

queue <node> q;

int main(){
	cin >> m >> n >> m1 >> m2;
	dx[0] = dx[1] = m1; dx[2] = dx[3] = -m1; dx[4] = dx[5] = m2; dx[6] = dx[7] = -m2;
	dy[0] = dy[2] = m2; dy[1] = dy[3] = -m2; dy[4] = dy[6] = m1; dy[5] = dy[7] = -m1;
	// 处理8个方位
    
	for(int i = 1;i <= m;i ++){
		for(int j = 1;j <= n;j ++){
			cin >> mp[i][j];
			if(mp[i][j] == 2) { mp[i][j] = 0; }   
            // 为方便把石头和水这些不能到达的点全部变成0
			if(mp[i][j] == 3) { sx = i; sy = j; } // 起点
			if(mp[i][j] == 4) { tx = i; ty = j; } // 终点
		}
	}
	
	nd = {sx,sy,0};
	q.push(nd);
	
	while(!q.empty()){
		nd = q.front();
		q.pop();
		if(nd.x == tx && nd.y == ty){
			printf("%d\n",nd.step);
			return 0; // 到达终点 直接输出答案并退出
		}
		register int nx,ny;
		for(register int i = 0;i < 8;i ++){ // 枚举八个方位
			nx = nd.x + dx[i]; ny = nd.y + dy[i];
			if(nx < 1 || nx > m || ny < 1 || ny > n) continue; // 越界就continue
			if(mp[nx][ny]){
				q.push({nx,ny,nd.step + 1}); // 入队继续搜索
				mp[nx][ny] = 0; // 防止重复搜索同一个点 走过一个点后直接把它变成0
			}
		}
	}
	return 0;
}
```

---

## 作者：RiverHamster (赞：1)

## 这题最简单的方法当然是BFS

时间`O(n^2)` 空间`O(n^2)`(队列)

直接套用基本BFS方法：使用一个**队列**，每次从队头取出要搜的位置，然后把搜到的放在队尾，**实现按层次搜索**（距离为1->距离为2...）

当队列非空时，就取出第一个元素，如果到达了，**就直接输出答案，必定是最小的（搜索的层次）**，否则向8个方向搜索，如果下一个点**没有访问过**，就把它加到队列尾部，并且把它的答案设为当前答案+1

核心代码：
```cpp
int bfs(int x,int y){
	push(x,y);    //把第一个点加入队列
	s[x][y]=0;    //第一个点答案为0
	int dx[]={m1,m1,-m1,-m1,m2,m2,-m2,-m2};
	int dy[]={m2,-m2,m2,-m2,m1,-m1,m1,-m1}; //八个方向
	while(__start<=__end){  //数组实现的队列
		if(a[top.x][top.y]==4) return s[top.x][top.y];  //第一个到达终点必定是最小值，因为搜索的层次顺序
		for(int i=0;i<8;i++){
			if(range(nx,ny)&&(a[nx][ny]==1||a[nx][ny]==4)&&s[nx][ny]==0){ //越界，是否可以跳，没有访问
				s[nx][ny]=s[top.x][top.y]+1;
				push(nx,ny); //加入队列，答案为现在的+1
			} //nx=top.x+dx[i],ny=top.y+dy[i]（define好写）
		}
		pop;      //当前点退出队列
	}
	return -1;    //没有路径（只是为了解决一个警告）
}
```
[点击查看完整代码](https://paste.ubuntu.com/26512758/)

---

## 作者：Chinese_zjc_ (赞：0)

看遍了所有的人也没有人用最直接的动态规划做的,那我就来水一篇.

显然我们知道对于一个状态$dis[i][j]$我们可以设定为从起点到坐标为$(i,j)$的最少跳跃次数.

那我们就能够得到状态转移方程了:
$$
dis[i][j]=min(dis[i+xx[k]][j+yy[k]])
$$
其中$xx$和$yy$都是指一种运动方向运动的坐标值(这个想必不用我说了).

那还有什么好说的,直接上代码:

```cpp
//This code was made by Chinese_zjc_.
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#define int long long
#define INF 0x3fffffffffffffff
//我的传统头文件
using namespace std;
int n,m,a,b,map[31][31],dis[31][31],xx[8],yy[8],ansx,ansy;
signed main()
{
	std::ios::sync_with_stdio(false);
    //这个可以给你的cin和cout加速,甚至比scanf和printf快!
    //不过要注意的就是:如果用了这句话,就不能再用scanf和printf之类的了,会RE.
	cin>>n>>m>>a>>b;
    //输入前四个数据
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			cin>>map[i][j];
            //读入数据
			if(map[i][j]!=3)
			{
				dis[i][j]=INF;
                //初始化,除了起点的地方都设为无限距离
			}
			if(map[i][j]==4)
			{
				ansx=i;
				ansy=j;
                //存储终点坐标
			}
		}
	}
	xx[0]=a;yy[0]=b;
	xx[1]=b;yy[1]=a;
	xx[2]=b;yy[2]=-a;
	xx[3]=a;yy[3]=-b;
	xx[4]=-a;yy[4]=b;
	xx[5]=-b;yy[5]=a;
	xx[6]=-b;yy[6]=-a;
	xx[7]=-a;yy[7]=-b;
    //记录8种运动方向的坐标改变情况
	for(int t=1;t<=n*m;++t)
    //每个地方不可能重复去,所以最多只要跑n*m次(当然搜到答案就退出也可以)
	{
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=m;++j)
			{
				if(map[i][j]==2||map[i][j]==0)
                //简单的特判,防止枚举无用状态
				{
					continue;
				}
				for(int I=0;I<8;++I)
				{
					int x=i+xx[I],y=j+yy[I];
					if(x<1||y<1||x>n||y>m)
                    //判断边界
					{
						continue;
					}
					dis[i][j]=min(dis[i][j],dis[x][y]+1);
				}
			}
		}
	}
	cout<<dis[ansx][ansy];
    //最后输出即可
	return 0;
}

```



---

## 作者：namespace_std (赞：0)

贡献一篇SPFA代码。

对1,3,4的块设计为点，然后将所有可以连通的两个点之间连边

则问题变为关于3和4的最短路

用SPFA可以很容易地求出最优解

预估时间复杂度：

最多30*30=900个点

每个点最多引出8条边，总边数至多为900*8/2=3600

根据SPFA的平均O(2e)（e为边数）不难发现总耗时很小

（理论上，n、m的极限值大概是1000）

欣赏一下SPFA的过程：（此代码可以随便拿走）
```
void spfa()
{
	while(l<=r)
	{
		int tp=p[q[l]].h;  //链式前向星头指针h
		while(tp)  //遍历出边
		{
			int pp=e[tp].t;
			if(v[pp]>v[q[l]]+1)  //松弛操作
			{
				v[pp]=v[q[l]]+1;
				if(!isin[pp])  //将需要更新的点加入队列
				{
					isin[pp]=1;
					r++;
					q[r]=pp;
				}
			}
			tp=e[tp].p;
		}
		isin[q[l]]=0;
		l++;  //将目标点推出队列
	}
}
```
有了SPFA~~指导~~思想，代码实现难度不大

注意特判边界，然后就是耐心下来码代码了

代码：
```
#include<cstdio>
#include<cstring>
struct Node
{int x,y,h;}p[1111];
struct Edge
{int p,t;}e[11111];
int n,m,t1,t2,k,g,f,mp[66][66],lo[33][33],q[111111],v[1111],l,r;
bool isin[1111];
void buildedge(int x,int y)
{g++,e[g].p=p[x].h,e[g].t=y,p[x].h=g;}
void bul()
{
	int i,ii;
	for(i=1;i<=n;i++)
		for(ii=1;ii<=m;ii++)
			if(mp[i][ii]==1)
			{
				int px=lo[i][ii];
				if(i>t2&&ii>t1)
					if(mp[i-t2][ii-t1]==1)
						buildedge(px,lo[i-t2][ii-t1]);
				if(i>t1&&ii>t2)
					if(mp[i-t1][ii-t2]==1)
						buildedge(px,lo[i-t1][ii-t2]);
				if(i>t1)
					if(mp[i-t1][ii+t2]==1)
						buildedge(px,lo[i-t1][ii+t2]);
				if(ii>t1)
					if(mp[i+t2][ii-t1]==1)
						buildedge(px,lo[i+t2][ii-t1]);
				if(ii>t2)
					if(mp[i+t1][ii-t2]==1)
						buildedge(px,lo[i+t1][ii-t2]);
				if(i>t2)
					if(mp[i-t2][ii+t1]==1)
						buildedge(px,lo[i-t2][ii+t1]);
				if(mp[i+t1][ii+t2]==1)
					buildedge(px,lo[i+t1][ii+t2]);
				if(mp[i+t2][ii+t1]==1)
					buildedge(px,lo[i+t2][ii+t1]);
			}
}
void spfa()
{
	while(l<=r)
	{
		int tp=p[q[l]].h;
		while(tp)
		{
			int pp=e[tp].t;
			if(v[pp]>v[q[l]]+1)
			{
				v[pp]=v[q[l]]+1;
				if(!isin[pp])
				{
					isin[pp]=1;
					r++;
					q[r]=pp;
				}
			}
			tp=e[tp].p;
		}
		isin[q[l]]=0;
		l++;
	}
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&t1,&t2);
	int i,ii;
	for(i=1;i<=n*m;i++)v[i]=23232323;
	for(i=1;i<=n;i++)
		for(ii=1;ii<=m;ii++)
		{
			scanf("%d",&mp[i][ii]);
			if(mp[i][ii]==1||mp[i][ii]==3||mp[i][ii]==4)
				k++,p[k].x=i,p[k].y=ii,lo[i][ii]=k;
			if(mp[i][ii]==4)f=k,mp[i][ii]=1;
			if(mp[i][ii]==3)
				isin[k]=1,q[0]=k,v[k]=0,mp[i][ii]=1;
		}
	bul();
	spfa();
	printf("%d\n",v[f]);
}
```

---

## 作者：Widerg (赞：0)

广搜实现动态规划。从起始点开始搜索，只要不是石头的点都可以访问。对于网格中每一个点，维护三个参数：从起始点到当前点所要添加的莲花数lily，总起始点到前点的走过的点数skip，到当前点当前满足条件的路径条数cnt。初始化所有点skip=lily=无穷大，cnt=0。起始点skip=lily=0，cnt=1。

当位置i时，跳跃有8个方向，最多会访问8个点，对于每个点j，根据当前位置i更新其参数。分以下4种情况：

1.如果 i.lily < j.lily ，由i点更新点j所有参数，并把点j加入队列

1.j.lily <- i.lily 

2.j.skip <- i.skip 

3.j.cnt <- i.cnt 

2.如果 i.lily = j.lily 并且 i.skip < j.skip ，由i点更新点j的跳跃次数和路径条数，并把点j加入队列

1.j.skip <- i.skip 

2.j.cnt <- i.cnt 

3.如果 i.lily = j.lily 并且 i.skip = j.skip ，j的路径条数满足条件，增加量为i的路径条数，并把点j加入队列

1.j.cnt <- j.cnt + i.cnt 

4.如果不满足以上条件，不更新改点。

最终结果为目标点T的lily,skip,cnt。

```cpp
" #include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
FILE *in = fopen("silvlily.in", "r"), *out = fopen("silvlily.out", "w");
int m,n,d[50][50];
struct p {int x, y;};
```
class node
{
public:



            


```cpp
    int bestlily;
    int bestjump;
    long long nways;
    node() {bestlily=-1; bestjump=-1; nways=0;}
};
node grid[50][50];
bool inq[50][50];
#define QSIZE 10000
p q[QSIZE];
int qstart,qend;
void enq(int x, int y)
{
    if (!inq[x][y])
    {
        inq[x][y]=true;
        q[qend].x=x;
        q[qend].y=y;
        qend++; qend%=QSIZE;
    }
}
void updateq(int x, int y, int bl, int bj, long long pways)
{
    if (grid[x][y].bestlily==-1 || bl<grid[x][y].bestlily)
    {
        grid[x][y].bestlily=bl;
        grid[x][y].bestjump=bj;
        grid[x][y].nways=pways;
        enq(x,y); return;
    }
    if (grid[x][y].bestlily==bl && bj<grid[x][y].bestjump)
    {
        grid[x][y].bestlily=bl;
        grid[x][y].bestjump=bj;
        grid[x][y].nways=pways;
        enq(x,y); return;
    }
    if (grid[x][y].bestlily==bl && bj==grid[x][y].bestjump)
    {
        grid[x][y].nways+=pways;
        return;
    }
}
int dirs[8][2]={{1,2},{2,1},{-1,2},{-2,1},{-1,-2},{-2,-1},{1,-2},{2,-1}};
void processqhead(void)
{
    int x=q[qstart].x,y=q[qstart].y,nx,ny;
    for (int i=0;i<8;i++)
    {
        nx=x+dirs[i][0];
        ny=y+dirs[i][1];
        if (nx>=0 && ny>=0 && nx<m && ny<n)
        {
            if (d[nx][ny]!=2)
updateq(nx,ny,grid[x][y].bestlily+(d[nx][ny]==1?0:1),grid[x][y].bestjump+1,grid[x][y].nways);
        }
    }
    inq[x][y]=false;
    qstart++; qstart%=QSIZE;
}
int main(void)
{
    int i,j;
    p a,b;
    fscanf(in,"%i %i",&m,&n);
    for (i=0;i<m;i++) for (j=0;j<n;j++) fscanf(in,"%i",&d[i][j]);
    for (i=0;i<m;i++) for (j=0;j<n;j++)
    {
        if (d[i][j]==3) {d[i][j]=1; a.x=i;a.y=j;}
        if (d[i][j]==4) {d[i][j]=1; b.x=i;b.y=j;}
        inq[i][j]=false;
    }
    qstart=0; qend=0;
    updateq(a.x,a.y,0,0,1);
    while (qstart!=qend)
    {
        processqhead();
    }
    if (grid[b.x][b.y].bestlily==-1) fprintf(out,"-1\n");
    else
fprintf(out,"%i\n%i\n%lld\n",grid[b.x][b.y].bestlily,grid[b.x][b.y].bestjump,grid[b.x][b.y].nways);
    fclose(in); fclose(out); return 0;

```

---

## 作者：Goder (赞：0)

判断一下奇偶就可以了。

```cpp
var f:array[-100..100,-100..100] of longint;
q:array[1..200,1..2] of integer;
z:array[-100..100,-100..100] of boolean;
min:array[1..8,1..2] of longint;
i,j,n,m,n1,m1,k,x,y,sum,t,w,e,w1,e1,a,b:longint;
begin
readln(n,m,n1,m1);
min[1,1]:=n1;min[1,2]:=m1;
min[2,1]:=-n1;min[2,2]:=m1;
min[3,1]:=-n1;min[3,2]:=-m1;
min[4,1]:=n1;min[4,2]:=-m1;
min[5,1]:=m1;min[5,2]:=n1;
min[6,1]:=m1;min[6,2]:=-n1;
min[7,1]:=-m1;min[7,2]:=-n1;
min[8,1]:=-m1;min[8,2]:=n1;
if n1>m1 then k:=n1 else k:=m1;
for i:=-k to n+k do
for j:=-k To m+k do
f[i,j]:=maxlongint;
for I:=1 to n do
for J:=1 to m do
begin
read(k);
if (k=0) or (k=2) then f[i,j]:=maxlongint else f[i,j]:=0;
if k=3 then begin x:=i;y:=j;end;
if k=4 then begin a:=i;b:=j;end;
end;
sum:=1;t:=1;
q[1,1]:=x;q[1,2]:=y;
z[x,y]:=true;
while sum<=t do
begin
w:=q[sum,1];e:=q[sum,2];
for i:=1 to 8 do
begin
w1:=w+min[i,1];e1:=e+min[i,2];
if (z[w1,e1]=false) and (f[w1,e1]<maxlongint) then
if (f[w1,e1]=0) or (f[w1,e1]>f[w,e]+1) then
begin
f[w1,e1]:=f[w,e]+1;
t:=t+1;
q[t,1]:=w1;q[t,2]:=e1;
z[w1,e1]:=true;
end;
end;
sum:=sum+1;
end;
writeln(f[a,b]);
end.
```

---

