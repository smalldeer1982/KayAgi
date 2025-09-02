# Biridian Forest

## 题目描述

你发现你身处一片森林，你需要找到出口逃离这里。但是在森林中还有其他人和很多树木。他们会给你造成阻碍。

所有人都会沿向终点的最短路径行进。

## 样例 #1

### 输入

```
5 7
000E0T3
T0TT0T0
010T0T0
2T0T0T0
0T0S000
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1 4
SE23
```

### 输出

```
2
```

# 题解

## 作者：hswfwkj_ (赞：25)

## 本题主要算法：广度优先搜索
[博客食用更佳哟！](https://www.luogu.com.cn/blog/374318/solution-cf329b1)
### 题意简述：
有一个 n\*m 的地图，$S$ 是我的起点，$T$ 是树木，也就是障碍，$E$ 是出口,0到9之间的数字代表该点上有人，并且数字就是该点上的人数，问我到终点前有多少人也能到终点。
### 思路：
不难看出，如果其他人要先于我或与我同时到达终点，那么他们离终点的距离就应小于等于我到出口的距离。所以我们可以用广搜，以出口作为起点（这样可以提高算法效率），记录下每个点到出口的距离并且记录下我到出口的距离，最后用循环嵌套扫一遍，发现有到达出口距离小于等于我到出口距离的就加上该点的人数。
### 说一下注意事项：
 
- 最好是从出口开始搜到每个点的距离而不是从每个点搜到出口的距离，这样可以提升搜索效率
- 其他人到达出口的距离等于我到达出口的距离的也应算在内
- 已搜过的点需要标记，防止再次搜索
- 距离应初始化为无限大，防止误判，加上不该加的人数

知道这些之后，本题思路就很明确了，个人认为注释比较详细，读懂代码应该不难，贴上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int x,y,step,sum;//step变量储存该点到出口的距离，sum变量储存该点的人数
}q[1000001];
int a[4001][4001],k,n,m,xx,yy;
void Bfs(int X,int Y){
    int head=0,tail=1,rx,ry,i;
    int dx[5]={0,0,0,1,-1};
    int dy[5]={0,1,-1,0,0};//定义向四个方向扩展的方向数组
    q[1].x=X;
    q[1].y=Y;
    q[1].step=0;
    q[1].sum=a[X][Y];
    while(head<tail){
        head++;
        for(i=1;i<=4;i++){
            rx=q[head].x+dx[i];
            ry=q[head].y+dy[i];
            if(a[rx][ry]<10&&a[rx][ry]>=0&&rx<=n&&rx>=1&&ry<=m&&ry>=1){//如果这里有人并且没有越界
                tail++;
                q[tail].step=q[head].step+1;//记录下这个点到出口的距离
                q[tail].sum=a[rx][ry];//记录下这个点的人数
                a[rx][ry]=10;//把这个点标记为已走过
                q[tail].x=rx;
                q[tail].y=ry;
                if(q[tail].x==xx&&q[tail].y==yy)
                k=q[tail].step;//如果是我所在的位置，就记录下这个点到出口的距离
            }
        }
    }
}
int main(){ 
    int i,j,xx1,yy1,sum=0;
    cin>>n>>m;
    char c;
    for(i=1;i<=1000000;i++)
    q[i].step=99999999;//先把距离标记为无穷大，以免误加
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++){
            cin>>c;
            if(c=='S'){
                xx=i;yy=j;
                a[i][j]=0;//如果是我的出发位置，就将该点的坐标记录下来
            }
            if(c=='E'){
                xx1=i;yy1=j;
                a[i][j]=0;//如果是出口，记录下坐标，作为起点用bfs遍历
            }
            if(c>='0'&&c<='9')
            a[i][j]=c-'0';//如果是有人的格子记录下人数
            if(c=='T')
            a[i][j]=10;//如果是障碍标记为10
        } 
    Bfs(xx1,yy1);//从出口坐标开始遍历
    for(i=1;i<=n*m;i++)
    if(q[i].step<=k){//如果这个点离出口的距离小于我到出口的距离就加上这个点的人数
    sum+=q[i].sum;
    }
    cout<<sum;
}
```
最后，如果觉得我的题解对你们有帮助的话，请挪动你们的鼠标为我点赞，你们的支持就是对我最大的鼓励！

---

## 作者：Asphy7xia (赞：3)

## 题解：CF329B


[题目传送门：CF329B](https://www.luogu.com.cn/problem/CF329B)

[博客食用更佳](https://www.luogu.com.cn/blog/Miracle-Marta0512/post-ti-xie-cf329b-biridian-forest)
#### 题意简述
给出一个 $n * m $的地图，其中$S$为起点，$E$为终点，$T$为障碍，其余格子上有一个数，代表格子上的人数，问从起点走到终点前有多少人也能走到终点。

#### 题目分析
（为方便起见，下文中的“距离”一律指”到终点的距离“）

不难想到，如果一个格子上的人能够在我们到达终点前先到达，那么这个格子的距离应不大于起点的距离。但直接搜索出每个点的距离时间复杂度太高，因此可以用BFS从终点开始搜索，这样还能剪去一些点，注意在起点前被搜到的格子都应被统计进答案。

对于如何判断一个点是否合法，可以使用一个变量$len$表示起点的距离。$len$应初始化为无穷大（因为由于队列先进先出的特点，先于起点被搜索到的点的距离一定不大于起点距离），当搜索到起点时更新$len$，这样只要判断点的距离是否小于等于$len$就行了。

#### 一些注意点
- 有人的点也可以通行。
- 题目中有一句“包括与你同时到达终点的人”，因此距离等于$len$的点也应被算进答案。
- 可以编写一个读入字符的函数来完成地图的输入，这样会方便许多。
- 可以使用一个$vis$数组标记已经搜过的点，提升搜索效率（话说这应该是BFS基操吧）。

#### 最后贴上AC代码：
```
#include <queue>
#include <string>
#include <ctype.h>
using namespace std;
int n, m, len = 0x3f3f3f3f, ans = 0;
const int N = 1634;
int map[N][N];
int fx[5] = {0, -1, 0, 1, 0};
int fy[5] = {0, 0, 1, 0, -1};
bool vis[N][N];

struct node
{
	int x, y, step;
};

std :: queue <node> q; 

inline char cread ()  //读入字符
{
	char c = getchar ();
	while (c != 'S' && c != 'T' && c != 'E' && ! isdigit (c))  c = getchar ();
	return c;
}

int main(){
	scanf ("%d%d", &n, &m);
	char ch;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			ch = cread ();
			if (isdigit (ch))  map[i][j] = ch - '0';
			if (ch == 'T')  map[i][j] = -1;
			if (ch == 'S')  map[i][j] = -2; 
			if (ch == 'E')
			{
				q.push ((node) {i, j, 0});
				vis[i][j] = true;
			}  //分别进行标记
		}
	}
	while (! q.empty ())
	{
		node tmp = q.front ();
		q.pop ();
		int x = tmp.x, y = tmp.y;
		if (map[x][y] == -2)  len = tmp.step;  //更新len
		if (tmp.step <= len && map[x][y] != -2)  ans += map[x][y];
		if (tmp.step >= len)  continue;  //后续的点不满足题意，就直接剪掉
		for (int i = 1; i <= 4; i++)  //进行下一步搜索
		{
			int nx = x + fx[i], ny = y + fy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && map[nx][ny] != -1 && ! vis[nx][ny])
			{
				q.push ((node) {nx, ny, tmp.step + 1});
				vis[nx][ny] = true; 
			}
		}
	}
	printf ("%d", ans);
	return 0;
} 
```
#### 希望这篇题解对大家有所帮助，谢谢 !

---

## 作者：Terraria (赞：1)

看到地图，应该能够很自然的想到动态规划或者搜索。

再仔细看一眼，就不难得到，这是一个用**宽搜**解的题目。

考虑有两个方法：

- 从每个不是 ```T``` 的点出发，记录从这个点到终点的最小距离。由于最劣时间复杂度可能达到 $O(n^3) \sim O(n^4)$，显然会超时。

- 从终点出发，首先记录自己的位置 ```S``` 到终点的最小距离，再从终点处开始宽度优先搜索，对于所有的**有人的格子、且到终点的最小距离小于等于自己到终点的最小距离**进行答案累加。

由于这是宽度优先搜索，故可以保证首先搜到的点一定是距离最小的，因此从 ```S``` 出发到达出口的距离可以在搜索过程中一旦搜到了 ```S``` 可以直接记录最大距离 $maxn$，并且此后的所有格子一旦距离大于这个距离则可以直接跳过。

~~PS：太久没有写宽搜了，于是写爆了~~

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct infor{
	int dis;
	int x;
	int y;
}from;
int ans;
int n,m;
int maxn=1e9;
queue<infor> q;
char mp[1009][1009];
bool vis[1009][1009];
int dx[5]={0,0,1,0,-1};
int dy[5]={0,1,0,-1,0};
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];
			if(mp[i][j]=='E'){
				from.x=i;
				from.y=j;
			}
		}
	}
	from.dis=0;
	q.push(from);
	while(!q.empty()){
		infor now=q.front();
		q.pop();
		int x=now.x,y=now.y,dis=now.dis;
		//cout<<x<<" "<<y<<endl;
		if(dis>maxn||vis[x][y]) continue;
		vis[x][y]=true;
		if(mp[x][y]=='S'){
			maxn=dis;
			continue;
		}
		if(mp[x][y]>='0'&&mp[x][y]<='9') ans=ans+(mp[x][y]-'0');
		for(int i=1;i<=4;i++){
			int xx=x+dx[i];
			int yy=y+dy[i];
			if(xx<1||xx>n||yy<1||yy>m||mp[xx][yy]=='T'||vis[xx][yy]) continue;
			infor to;
			to.x=xx,to.y=yy,to.dis=dis+1;
			q.push(to);
		}
	}
	cout<<ans;
}
```


---

## 作者：听取MLE声一片 (赞：1)

## 本题核心：广度优先搜索

这道题感觉不应该上绿啊，应该是黄题或以下吧。

首先根据经验可得，从起点到终点的距离等于终点到起点的距离。

这有什么用呢？我们知道，广度优先搜索队列队头始终保持着当前最优解（指走的路最短）。如果我们的队列中出现了起点，这就说明了比起点到终点路程短人都已经到达终点了。这个时候还有一些与起点距离相等的点还没有搜到，这只需要把 `maxn`从 `inf` 更新为起点到终点的距离，如果队列中的点的距离比 `maxn` 要大，直接弹出即可。

其他部分仿照的普通 `bfs` 就行了。

下面是代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
struct point{
	int x,y,s;
};
queue<point>q;
int maxn=1e9,n,m,sx,sy,ans,book[1001][1001];
char a[1001][1001];
int xx[4]={1,-1,0,0},yy[4]={0,0,1,-1};
void bfs(){
	point p1={sx,sy,0};
	q.push(p1);
	while(!q.empty()){
		point p=q.front();
		q.pop();
		if(book[p.x][p.y]||p.s>maxn)
			continue;
		book[p.x][p.y]=1;
		if(a[p.x][p.y]=='S'){//搜到起点把maxn赋值，之前为inf
			maxn=p.s;
			continue;
		}
		if(a[p.x][p.y]>='0'&&a[p.x][p.y]<='9')
			ans+=a[p.x][p.y]-'0';//搜到数字就在ans上加人数
		for(int i=0;i<4;i++){
			int tx=p.x+xx[i],ty=p.y+yy[i];
			if(a[tx][ty]=='T'||tx<0||tx>=n||ty<0||ty>=m)
				continue;
			point p2={tx,ty,p.s+1};
			q.push(p2);
		}
	}
}
int main()
{
	n=read(),m=read();
	for(int i=0;i<n;i++){
		scanf("%s",&a[i]);
		for(int j=0;j<m;j++)
			if(a[i][j]=='E')//从终点开始搜
				sx=i,sy=j;
	}	
	bfs();
	printf("%d",ans);
	return 0;
}

```
谢谢大家！

---

## 作者：Oscar12345 (赞：1)

嗯...一道优美的BFS题目

不难想到，若小队a距出口的最小距离小于等于主人公距出口的最小距离，小队a一定可一追到主人公，所以只要以出口为起点，做一个bfs记录下出口到各点的距离，之后统计人数即可。需要注意的一点是有些区域可能会被障碍物个离开，初始化的时候要将所有区域到出口的距离设为无穷大，不然在统计时可能会把隔了区的小队人数也统计进去。

丑陋的代码：
```
#include <iostream>
#include <queue>
#include <cstring>
 
using namespace std;
 
const int MAX_N = 1000 + 100;
const int fx[5]={0,0,1,0,-1};
const int fy[5]={0,1,0,-1,0};
const int inf = (1 << 30);
int dis[MAX_N][MAX_N];
bool vis[MAX_N][MAX_N];
char _map[MAX_N][MAX_N];
struct Node
{
    int x,y,num;
};
struct Point
{
    int x,y,dis;
};
Node node[MAX_N * MAX_N];
Node st,en;//start,end
int r,c;
 
void BFS()
{
    queue<Point> point;
    Point p_en;
    p_en.x = en.x;
    p_en.y = en.y;
    p_en.dis = 0;
    point.push(p_en);
    vis[p_en.x][p_en.y] = true;
    while(!point.empty())
    {
        Point q = point.front();
        point.pop();
        Point _new;
        for(int i = 1;i <= 4;i++)
        {
            _new.x = q.x + fx[i];
            _new.y = q.y + fy[i];
            if(_new.x <= r && _new.x > 0 && _new.y <= c && _new.y > 0 && _map[_new.x][_new.y] != 'T' && !vis[_new.x][_new.y])
            {
                _new.dis = q.dis + 1;
                vis[_new.x][_new.y] = true;
                point.push(_new);
                dis[_new.x][_new.y] = _new.dis;
            }
        }
    }
}
int main()
{
    memset(vis,0,sizeof(vis));
    int cnt = 0;
    cin >> r >> c;
    for(int i = 1;i <= r;i++)
    {
        for(int j = 1;j <= c;j++)
        {
            cin >> _map[i][j];
            dis[i][j] = inf;
            if(_map[i][j] == 'S')
            {
                st.x = i;
                st.y = j;
            }
            else if(_map[i][j] == 'E')
            {
                en.x = i;
                en.y = j;
            }
            else if(_map[i][j] >= '0' && _map[i][j] <= '9')
            {
                cnt++;
                node[cnt].x = i;
                node[cnt].y = j;
                node[cnt].num = _map[i][j] - '0';
            }
        }
    }
    BFS();
    int ans = 0;
    for(int i = 1;i <= cnt;i++)
    {
        if(dis[node[i].x][node[i].y] <= dis[st.x][st.y])
            ans += node[i].num;
    }
    cout << ans << endl;
    return 0;
}
```

欢迎大佬前来拍砖

---

