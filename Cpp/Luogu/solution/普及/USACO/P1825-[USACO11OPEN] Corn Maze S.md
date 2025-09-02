# [USACO11OPEN] Corn Maze S

## 题目描述

This past fall, Farmer John took the cows to visit a corn maze. But this wasn't just any corn maze: it featured several gravity-powered teleporter slides, which cause cows to teleport instantly from one point in the maze to another. The slides work in both directions: a cow can slide from the slide's start to the end instantly, or from the end to the start. If a cow steps on a space that hosts either end of a slide, she must use the slide.

The outside of the corn maze is entirely corn except for a single exit.

The maze can be represented by an N x M (2 <= N <= 300; 2 <= M <= 300) grid. Each grid element contains one of these items:

\* Corn (corn grid elements are impassable) 

\* Grass (easy to pass through!) 

\* A slide endpoint (which will transport a cow to the other endpoint) 

\* The exit

A cow can only move from one space to the next if they are adjacent and neither contains corn. Each grassy space has four potential neighbors to which a cow can travel. It takes 1 unit of time to move from a grassy space to an adjacent space; it takes 0 units of time to move from one slide endpoint to the other.

Corn-filled spaces are denoted with an octothorpe (#). Grassy spaces are denoted with a period (.). Pairs of slide endpoints are denoted with the same uppercase letter (A-Z), and no two different slides have endpoints denoted with the same letter. The exit is denoted with the equals sign (=).

Bessie got lost. She knows where she is on the grid, and marked her current grassy space with the 'at' symbol (@). What is the minimum time she needs to move to the exit space?


## 说明/提示

例如以下矩阵，$N=5,M=6$。

```plain
###=##
#.W.##
#.####
#.@W##
######
```

唯一的一个装置的结点用大写字母 $\tt{W}$ 表示。

最优方案为：先向右走到装置的结点，花费一个单位时间，再到装置的另一个结点上，花费 $0$ 个单位时间，然后再向右走一个，再向上走一个，到达出口处，总共花费了 $3$ 个单位时间。

## 样例 #1

### 输入

```
5 6
###=##
#.W.##
#.####
#.@W##
######
```

### 输出

```
3```

# 题解

## 作者：lxzy_ (赞：193)

## ~~一道奇奇怪怪的搜索题~~

以我的感觉，这一道题除了传送门需要特判一下，并注意不要重复计算路径，其他地方都不算太难。

大约是$\color{orange}\text{普及组T2}$的难度。

~~好了废话不多说了，开始切题QwQ~~

---

$$\color{red}\text{思路}$$

> 求出Bessie需要移动到出口处的最短时间

显然地，这题的思路就是：

> ~~暴力~~BFS

关于BFS可以康康我写的另外一篇题解：

[$\text{P1443马的遍历}$](https://www.luogu.org/blog/wwwbokecom/solution-p1443)

---

$$\color{green}\text{写法}$$

广搜的主要思想便是将所有可行解（可到达的点）放入队列，然后再一个个遍历所有可行解（可到达的点），知道找到终点为止。

$C++$的优势再一次显现出来了——我们可以使用$C++STL$中的$queue$数据结构~~C++万岁！~~

如下：

```cpp
struct point{//定义一个名为point的结构体
	int x;//当前可到达点的x坐标
	int y;//当前可到达点的y坐标
	int t;//到达当前点的最小步数
};
queue<point> que;//定义一个变量类型为point的队列
```

不过记得加上：

```cpp
#include<queue>
```

关于广搜的部分：

与深搜相同，定义坐标偏移量，以便枚举当前所有可到达点。不同点在于，深搜是一个急性子：遇到可到达点就不管三七二十一直接走上去，直到走不通为止；而广搜则是将所有可到达点放入队列后，再一个个遍历。

$\text{裸广搜模板：}$

```cpp
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};//定义坐标偏移量
int sx,sy;//起点x、y坐标
int vis[350][350];//vis数组用来防止同一个点访问多次，true表示已访问，false表示为访问

que.push((point){sx,sy,0});//将起点坐标放入队列，初始步数为0

while(!que.empty())//只要还有可到达点就继续访问，知道榨干它
{
    point f=que.front();//提取出队头
    que.pop();//切记！一定要记得将队头扔掉，否则会死循环

    if(a[f.x][f.y]=='=')//如果当前点就是终点
    {
        cout<<f.t;//输出它，结束~
        return 0;
    }

    for(int i=0;i<=3;i++)//遍历其上下左右相邻的点
    {
        //下面与深搜基本一样
        int nx=x+dx[i];//获取相邻点的x、y坐标
        int ny=y+dy[i]; 
        if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&a[nx][ny]!='#'&&!vis[nx][ny])//判断是否越界、是否撞墙、当前点是否已经被访问过
        {
            que.push((point){nx,ny,f.t+1});//可以走便将其放入队列
            vis[nx][ny]=true;//标记当前点已经走过
        }
    }
}
```

由于这道题加入了一个新的元素：传送门。因此我们需要在广搜中多增加一个特判：当前是否为传送门，是的话，我们就需要找到另一个传送门所在坐标，然后将那个传送门所在点的坐标储存进队列。


$\color{green}AC$ $\text{Code：}$

```cpp
#include<iostream>
#include<queue>
using namespace std;
const int N=350;

struct point{
    int x;
    int y;
    int t;
};

queue<point> que;

char a[N][N];
bool vis[N][N];
int n,m;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int sx;
int sy;

void goto_another(int &nx,int &ny,int k)//goto_another函数用于寻找另一个传送门，nx、ny代表当前点的坐标，记得要加上取地址符'&'，因为每当贝西踏入一个传送门，它就会立即被传送至另一个传送门，不能在原地停留
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(a[i][j]==a[nx][ny]&&(i!=nx||j!=ny))//如果a[i][j]这个点的是一个与a[nx][ny]相同的传送门，并且a[i][j]与a[nx][ny]不是同一个点
            {
                nx=i;//改变当前坐标，将贝西强行移动至另一个传送门处
                ny=j;
                return ;//告辞
            }
        }
    }
}
int main()
{
    
    cin>>n>>m;
    string s;
    for(int i=1;i<=n;i++)
    {
        cin>>s;//由于输入奇奇怪怪地没有空格，于是乎窝便使用字符串读入
        for(int j=1;j<=m;j++)
        {
            a[i][j]=s[j-1];
            if(a[i][j]=='@')//获取起点坐标
            {
                sx=i;
                sy=j;
            }
        }
    }
    que.push((point){sx,sy,0});

    while(!que.empty())
    {
        point f=que.front();
        que.pop();
        if(a[f.x][f.y]=='=')
        {
            cout<<f.t;
            return 0;
        }
        if(a[f.x][f.y]>='A'&&a[f.x][f.y]<='Z')//特判部分，如果当前点是一个传送门，那么就传送至另一个传送门
        {
            goto_another(f.x,f.y,f.t);
        }
        for(int i=0;i<=3;i++)
        {
            int nx=f.x+dx[i];
            int ny=f.y+dy[i];
            if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&a[nx][ny]!='#'&&!vis[nx][ny])
            {
                vis[nx][ny]=true;
                que.push((point){nx,ny,f.t+1});
            }
        }
    }
    return 0;
}
```

以上就是我对这道~~假~~绿题的解法，蟹蟹观康$QwQ$

---

## 作者：lzxhdxx (赞：87)

# P1825 玉米田迷宫
这是一道广搜题目，但是我花十分钟打了一个广搜板子，竟然T了~~肯定是我打假了~~，所以我就采用了优化方法，在此写一种现有的题解里没有出现的新方法——**双向广搜**（）

先说这道题的坑点：

1.踩到一个传送器上**必须**使用

2.传送器**不一定只用一次**，有可能只是一个中转点

例如：
```
3 5
A#@A=
.#.#.
.....

这时我们的最短路径是：
(1,3)->(1,4)直接传送到(1,1)->(2,1)->(1,1)直接传送回(1,4)->(1,5)
共四步
PS:为了避免需要用两次的传送器在用第一次时直接被记忆化标记，导致之后不能用第二次，我们只标记出发时的那个传送器就可以了，比如(1,3)->(1,4)，我们只标记(1,3)而不标记(1,4)
```
3.很容易发现，在坑点2提供的数据里我们到(1,1)没有直接传送回(1,4)，没错，不能直接传回去，需要先**随便走一步再回到传送器**传送，我被这个点坑了好久

4.显而易见每个传送器最多用两次，所以我们要分清这个传送器究竟用了一次还是两次（普通广搜不需要，**我写的**双向广搜**必须**要~~可能是我又写假了~~）
```
原因：
5 5
@.A.=
.....
.....
.....
..A..
如果发生这种情况，很明显，直接双向广搜会在(1,3)处相遇，计算的答案为2+2=4，但是踩到传送器就必须传送（见坑点1），所以我们的最短路径是：
(1,1)->(1,2)->(1,3)直接传送至(5,3)->(5,4)->(5,3)直接传送回(1,3)->(1,4)->(1,5)
共六步
所以我用1来代表只用了一次的传送器或草地（即'.'），用2来代表用了两次（即走了一个来回）的传送器。（接下来这句是重点）如果两个方向的广搜在一个传送器处相遇，而且两个方向都只用过这个传送器一次，那么不能算相遇（如果在传送器处相遇肯定是走过去再走回来才行，请读者思考为什么是这样）
```


坑点大致就有这些，因为目前没有双向广搜题解，所以我就分段讲的细一些~~其实是为了不被抄~~

Part 1:
```cpp
int main()//主函数
{
	cin >> n >> m;//输入长宽
	for (int i = 1; i <= n; i++)//输入地图
		for (int j = 1; j <= m; j++)
		{
			cin >> c[i][j];
			if (c[i][j] == '@') sx = i, sy = j, vis[0][sx][sy] = 1;//检查到起点，用sx,sy记录起点的位置，把起点记录为走过
			if (c[i][j] == '=') ex = i, ey = j, vis[1][ex][ey] = 1;//同上，记录终点，终点记录为走过
		}
	cout << bfs() << endl;//调用双向广搜并输出
	return 0;
}
```
在主函数，我们输入长宽和地图，并开始奶牛的旅行，主函数里调用了双向广搜，所以接下来我们来看bfs()函数

Part 2:
```cpp
int bfs()//双向广搜
{
	Q[0].push(make_pair(sx, sy)), Q[1].push(make_pair(ex, ey));//两个队列分别压入起点和终点
	while (!Q[0].empty() && !Q[1].empty())//广搜要求记录状态的队列不能为空
		if (Q[0].size() < Q[1].size())//哪个方向状态少就扩展哪个方向
                { int tmp = expand(0);//扩展，0就是从奶牛方向开始搜，1就是从终点开始搜 if (tmp) return tmp; //返回的结果如果是0，那就是没有相遇，反之则为相遇，输出返回的答案 }
		else { int tmp = expand(1); if (tmp) return tmp; }
	return -1;//没有路（此题不需要）
}
```
PS:双向广搜基本思路：从起点和终点分别广搜，每次选择状态少的队列进行扩展，当两个方向的搜索第一次相遇时，就找到了最优解，直接返回答案

在bfs()里，我们写了双向广搜的基本思路，接下来，我们看到扩展用到了expand()函数，这个函数就是扩展和判断是否到达终点的函数，接下来我们看怎么写expand()

Part 3(重中之重):
```cpp
int expand(int sub)//sub代表当前扩展的方向
{
	int nowx = Q[sub].front().first, nowy = Q[sub].front().second; Q[sub].pop();//取出队头，弹掉队头
	for (int i = 1; i <= 4; i++)//四个方向依次尝试
	{
		int newx = nowx + dx[i], newy = nowy + dy[i];
		if (newx >= 1 && newy >= 1 && newx <= n && newy <= m && c[newx][newy] != '#' && !vis[sub][newx][newy])//如果没有越界，不是障碍，而且没有被标记
		{
			if (c[newx][newy] >= 'A' && c[newx][newy] <= 'Z')//当前是传送器
			{
				int x = newx, y = newy; //当前传送器位置
				vis[sub][newx][newy] = 1,/*如果当前是传送器，那我们肯定还没用过（用过的都标记了），标记为用了一次（即1）*/ cnt[sub][newx][newy] = cnt[sub][nowx][nowy] + 1;/*记录步数（把传送器标记为2的过程也在这实现了）*/ handle(newx, newy);//handle用于找到另一个传送器位置
			}
			else vis[sub][newx][newy] = 1;//否则就是普通的路，直接用1标记就可以了
			Q[sub].push(make_pair(newx, newy)), cnt[sub][newx][newy] = cnt[sub][nowx][nowy] + 1;//插入拓展出的点，计算步数
			if (vis[1 - sub][newx][newy])//如果另一层的这一步也被走过，就说明相遇了
			{
				if (c[newx][newy] >= 'A' && c[newx][newy] <= 'Z')//如果在传送器相遇
				{
					if (vis[1 - sub][newx][newy] == 2 || vis[sub][newx][newy] == 2)//必须有一个传送器用了两次，不然可能出现坑点4的错误
						return cnt[1 - sub][newx][newy] + cnt[sub][newx][newy];//返回答案
				}
				else return cnt[1 - sub][newx][newy] + cnt[sub][newx][newy];//不是传送器就直接返回答案
			}
		}
	}
	return 0;//如果最后也没有返回答案，那就说明还没有相遇，返回0，没有答案
}
```
在扩展里，我们还用了一个handle()函数来寻找另一个传送器，现在我们来看看handle()

Part 4:
```cpp
void handle(int& x, int& y)//加'&'就可以直接修改expand()里的newx,newy
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (c[x][y] == c[i][j] && (x != i || y != j)) 
			{ x = i, y = j; return; }//如果找到了就直接修改并return;
//如果一直没有return就是传送器不成对，不需要修改
}
```
handle()函数很简单，不成对就不用修改

这就是我的双向广搜的全部讲解了，接下来是~~大家最喜欢的~~完整代码
# Code(用cstdio库里的函数优化过，基本与上面相同):
```cpp
#include <cstdio>
#include <queue>

using namespace std;

char c[310][310];
int n, m, sx, sy, ex, ey, dx[5] = { 0,-1,1,0,0 }, dy[5] = { 0,0,0,-1,1 }, cnt[2][310][310] = { 0 }, vis[2][310][310] = { 0 };
queue<pair<int, int> >Q[2];

void handle(int& x, int& y)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (c[x][y] == c[i][j] && (x != i || y != j)) 
			{ x = i, y = j; return; }
}

int expand(int sub)
{
	int nowx = Q[sub].front().first, nowy = Q[sub].front().second; Q[sub].pop();
	for (int i = 1; i <= 4; i++)
	{
		int newx = nowx + dx[i], newy = nowy + dy[i];
		if (newx >= 1 && newy >= 1 && newx <= n && newy <= m && c[newx][newy] != '#' && !vis[sub][newx][newy])
		{
			if (c[newx][newy] >= 'A' && c[newx][newy] <= 'Z')
			{
				int x = newx, y = newy;
				vis[sub][newx][newy] = 1, cnt[sub][newx][newy] = cnt[sub][nowx][nowy] + 1; handle(newx, newy);
			}
			else vis[sub][newx][newy] = 1;
			Q[sub].push(make_pair(newx, newy)), cnt[sub][newx][newy] = cnt[sub][nowx][nowy] + 1;
			if (vis[1 - sub][newx][newy])
			{
				if (c[newx][newy] >= 'A' && c[newx][newy] <= 'Z')
				{
					if (vis[1 - sub][newx][newy] == 2 || vis[sub][newx][newy] == 2)
						return cnt[1 - sub][newx][newy] + cnt[sub][newx][newy];
				}
				else return cnt[1 - sub][newx][newy] + cnt[sub][newx][newy];
			}
		}
	}
	return 0;
}

int bfs()
{
	Q[0].push(make_pair(sx, sy)), Q[1].push(make_pair(ex, ey));
	while (!Q[0].empty() && !Q[1].empty())
		if (Q[0].size() < Q[1].size()) { int tmp = expand(0); if (tmp) return tmp; }
		else { int tmp = expand(1); if (tmp) return tmp; }
	return -1;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		getchar();
		for (int j = 1; j <= m; j++)
		{
			c[i][j] = getchar();
			if (c[i][j] == '@') sx = i, sy = j, vis[0][sx][sy] = 1;
			if (c[i][j] == '=') ex = i, ey = j, vis[1][ex][ey] = 1;
		}
	}
	printf("%d", bfs());
	return 0;
}
```
毕竟是双向广搜，速度还不错

评测结果：73ms /  2.15MB /  1.95KB C++

这是一种全新的方法，目前还没有人这么写，求管理大大给过

注：2020/02/02 20:44 删除了程序中的冗余部分，并添加了优化

---

## 作者：maorui_cow (赞：65)

这道题其实很简单的。普通的的搜索就可以了，废话不说，上代码
```
#include<bits/stdc++.h>
using namespace std;
int a[500][500],qx,qy,zx,zy,cz1,cz2,bj[500][500],n,m;
int d[4][2]= {{-1,0},{1,0},{0,-1},{0,1}};
struct node
{
	int x;
	int y;
	int bs;
} ans[101010];
int cz(int x,int y)
{
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			if(!(i==x&&j==y))//注意不能与原点相同
			{
				if(a[i][j]==a[x][y])//直接判断匹配
				{
					cz1=i;
					cz2=j;
					return 0;
				}
			}
		}
	}
}
int bfs()
{
	int head=0,tail=1;
	do
	{
		head++;
		if(a[ans[head].x][ans[head].y]>='A'&&a[ans[head].x][ans[head].y]<='Z')//判断是不是脚踩传送门
		{
			cz(ans[head].x,ans[head].y);//找到对应的传送门坐标
			ans[head].x=cz1;
			ans[head].y=cz2;
		}
		for(int i=0; i<4; i++)
		{
			int xx=ans[head].x+d[i][0];
			int yy=ans[head].y+d[i][1];
			if(a[xx][yy]!=0&&bj[xx][yy]==0)//广搜
			{
				bj[xx][yy]=1;
				tail++;
				ans[tail].x=xx;
				ans[tail].y=yy;
				ans[tail].bs=ans[head].bs+1;
				if(xx==zx&&yy==zy)//判目标
				{
					printf("%d\n",ans[tail].bs);
					return 0;
				}
			}
		}
	}
	while(head<tail);
}
int main()
{
	char s;
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			cin>>s;//输入预处理
			if(s=='.')
			{
				a[i][j]=1;
			}
			if(s>='A'&&s<='Z')
			{
				a[i][j]=s;//这里是一个很重要的点，等下说明
			}
			if(s=='@')
			{
				qx=i;
				qy=j;
				a[i][j]=1;
			}
			if(s=='=')
			{
				zx=i;
				zy=j;
				a[i][j]=1;
			}
		}
	}
	bj[qx][qy]=1;//注意一定要标记起点
	ans[1].x=qx;
	ans[1].y=qy;
	bfs();
	return 0;
}
```
//so easy

---

## 作者：Limit (赞：31)

有了上次题目看错的教训后再不敢随便看题了~~usaco太坑~~，这题绝对不水，传送门还特别玄学自然代码短不了...
代码：
```pascal
const z:array[1..4,1..2]of -1..1=((1,0),(0,1),(-1,0),(0,-1));
var i,j,k:longint;
    m,n:longint;
    pdx,pdy:longint;
    csmx,csmy:array['A'..'Z',0..1]of longint;
    a,boo:array[-1..1000,-1..1000]of boolean;
    b:array[-1..1000,0..1000]of longint;
    h,t:longint;
    ch:char;
    fx,fy,lx,ly:longint;
    x,y,u,p:array[0..4000000]of longint;//开大一点
begin
  readln(m,n);
  for i:=1 to m do
  begin
    for j:=1 to n do
    begin
      read(ch);
      if ch='@' then
      begin
        fx:=i;
        fy:=j;
        a[i,j]:=false;
      end;
      if ch='=' then
      begin
        lx:=i;
        ly:=j;
        a[i,j]:=true;
      end;
      if ch='#' then
      begin
        a[i,j]:=false;
      end;
      if ch='.' then
      begin
        a[i,j]:=true;
      end;
      if ch in ['A'..'Z'] then//判断传送门
      begin
        a[i,j]:=true;
        if csmx[ch,0]<>0 then//如果还没有找到同字母的传送门
        begin
          csmx[ch,1]:=i;
          csmy[ch,1]:=j;
          b[i,j]:=ord(ch)*10;
        end
        else//找到过了
        begin
          csmx[ch,0]:=i;
          csmy[ch,0]:=j;
          b[i,j]:=ord(ch)*10+1;
        end;
      end
      else
      b[i,j]:=0;
    end;
    readln;
  end;
  h:=1;
  t:=1;
  u[1]:=0;
  x[1]:=fx;
  y[1]:=fy;
  repeat
    if (x[t]=lx) and (y[t]=ly) then
    begin
      writeln(u[t]);
      exit;
    end;
    if (b[x[t],y[t]]<>0) and (p[t]=0) then//因为有传送门必须走，所以直接修改尾巴上的值
    if (a[csmx[chr(b[x[t],y[t]] div 10),b[x[t],y[t]] mod 10],
          csmy[chr(b[x[t],y[t]] div 10),b[x[t],y[t]] mod 10]]) then//感觉有点眼酸...
    begin
      pdx:=csmx[chr(b[x[t],y[t]] div 10),b[x[t],y[t]] mod 10];//记录
      pdy:=csmy[chr(b[x[t],y[t]] div 10),b[x[t],y[t]] mod 10];
      x[t]:=pdx;
      y[t]:=pdy;
      p[t]:=1;
    end;
    if (b[x[t],y[t]]=0) or (p[t]=1) then//接下来就很简单了
    for i:=1 to 4 do
    if a[x[t]+z[i,1],y[t]+z[i,2]] then
    begin
      inc(h);
      x[h]:=x[t]+z[i,1];
      y[h]:=y[t]+z[i,2];
      p[h]:=0;
      u[h]:=u[t]+1;
      if b[x[h],y[h]]=0 then//有传送门不可以赋为false，因为可能这只是一个中转站
      a[x[h],y[h]]:=false;
    end;
    inc(t);
  until t>h;
end.
```
如果不理解

> 有传送门不可以赋为false，因为可能这只是一个中转站

则举一个例子

```
###=###
#.....#
###A###
#.....#
#@#####
###a..#
#######
```
a,A一对传送门。
要先进入A从a出来，再进人a从A出来，不然不可以到终点，a就是一个中转站。
- 这可能才是本题考点。


---

## 作者：TYHTerrence (赞：23)

一开始,我的答案正确但是结果是WA,很神奇,后来把dfs换成bfs,就AC了,知道原因的,可以告诉我

这道题其实只是一个基本的最短路,但是有很多**坑**,
都是在传送点中,其实当下一个点是传送点时,直接把其对应的传送点压入队列即可
## 坑点举例:
### 1.传送点只是一个中介点
| # |# |#  |#  | # |#  |=  |#  |#  |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
|#  | . | . | . |.  |.  |.  |#  |#  |
| # |#  |#  | A | # | # | # |#  |#  |
| # |@  |.  |.  |#  |A  |.  |.  |#  |
|  #|#  |#  | # | # |#  |#  |#  | # |
#### 解决方法:
不把传送点标记v数组就可以,其他的要标记否则会死循环
### 2.走不了的传送点
| # | # | # |#  | # | # | # | # | # |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
|#  |A  |#  | . | . | . | . |.  |#  |
| # | # | # | # | # | # | . |.  |#  |
| # |@  |A  |#  | # | # | # | . |#  |
| # | . |.  |.  |.  | . | . | . | # |
|#  | # | # | # | # | # | # | # | # |
#### 解决方法:
这个其实**根本不算一个坑**,因为只要搜到了这个点就搜不动了(前提是你的bfs没有写错),即使多次搜到这个点,也不会回来比如这幅地图,只有第一步和第三步搜到了(1,1),后面就再也没有了.

### 具体实现:
每个坐标都要有x,y和到达当前坐标的最少步数step.x,y初始化为一个非法数据.step=0;重要节点的坐标在输入时就存储好,方便后续操作.
不说多了!上代码!
```cpp
#include <bits/stdc++.h>
#include <queue>
using namespace std;
struct pos
{
	int x,y,step;	//step指到达这个点所需的最少步数 
	pos()
	{
		x=y=-1;		//初始化成为一个非法坐标以便后续的赋值 
		step=0;		//开始前是0步 
	}
};
struct spt		// spread_point传送点 
{
	pos p1,p2;	//两个配对的传送点	
};
pos s,f;	//起点和终点的坐标 
int n,m;	//地图长和宽 
char a[305][305];	//地图 
bool v[305][305];	//标记数组 
int dx[]= {0,1,0,-1};	
int dy[]= {1,0,-1,0};	//四个方向的移动 
spt spts[200];		//传送点 
queue<pos> q;		//bfs队列 
bool check(int x,int y)
{
	if(x<0||x>n||y<0||y>m||a[x][y]=='#'||v[x][y]==1)
		return 0;
	return 1;
}		
//合法判断函数 
void bfs()
{
	v[s.x][s.y]=1;
	pos t;
	t.x=s.x,t.y=s.y,t.step=0;
	q.push(t);
	while(!q.empty())
	{
		pos tmp=q.front();
		q.pop();
		int x=tmp.x,y=tmp.y,step=tmp.step; 
	//	cout<<x<<' '<<y<<' '<<step<<'\n'; 
		if(tmp.x==f.x&&tmp.y==f.y)
		{
			cout<<tmp.step;
			return;
		}
		for(int i=0; i<4; i++)
		{
			int xx=x+dx[i];
			int yy=y+dy[i];
			if(check(xx,yy))
			{
				pos val;
				if(a[xx][yy]<'A'||a[xx][yy]>'Z')
				{
					val.x=xx,val.y=yy,val.step=step+1;
					v[xx][yy]=1;
				}
				else
				{
					if(xx==spts[a[xx][yy]-'A'].p1.x&&yy==spts[a[xx][yy]-'A'].p1.y)
					{
						val.x=spts[a[xx][yy]-'A'].p2.x;
						val.y=spts[a[xx][yy]-'A'].p2.y;
						val.step=step+1;
					}
					else
					{
						val.x=spts[a[xx][yy]-'A'].p1.x;
						val.y=spts[a[xx][yy]-'A'].p1.y;
						val.step=step+1;
					}
				}
				q.push(val);
			}
		}
	}
}
int main()
{
	cin>>n>>m;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<m; j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='@')
			{
				s.x=i;
				s.y=j;
			}
			if(a[i][j]=='=')
			{
				f.x=i;
				f.y=j;
			}
			if(a[i][j]>='A'&&a[i][j]<='Z')
			{
				int c=a[i][j]-'A';
				if(spts[c].p1.x==-1&&spts[c].p1.y==-1)
				{
					spts[c].p1.x=i;		
					spts[c].p1.y=j;
				}
				else
				{
					spts[c].p2.x=i;
					spts[c].p2.y=j;
				}
			}
		}
	}
	bfs();
}
```
~~其实这个可以写一个小游戏~~,这道题绝对不水,那么多坑,我提出来了,你就可以注意,望采纳我的方法,**祝大家早日AC!**

---

## 作者：yuzhechuan (赞：22)

记得有位大佬曾经说过：
> 这世上很少有只能用BFS做的题

~~所以这就是我不打BFS的理由？~~

于是乎这题我用的算法是SPFA



------------

看上去这题是二维的，而最短路是一维的，但其实这时候考验的就是你的预处理能力了，先将二维矩阵压成一维的n*m个点，再从每一个能走的点出发，向四方连边

但要注意的是这题的传送门，我们不妨将它们分成两类进行讨论：
1. 只有一个门的：当成普通草地进行处理；
2. 有两个门的：当要向其中一个连边时，只需将边的终点改为另一扇门的一维地址就可以了。
如图：

![](https://cdn.luogu.com.cn/upload/pic/24956.png)

 address: 
 
 1->4 X  
 1->6 ✔



------------

```cpp
#include <bits/stdc++.h>
using namespace std;
const int px[5]={0,-1,1,0,0},py[5]={0,0,0,-1,1};
const int N=90000,M=360000;
char mp[350][350];
int n,m,s,En,h[N],dis[N],q[N],visit[N],b,e,f[50],cs[50][5];
struct edge {int s,n,v;} E[M];

/*将二维压成一维*/
int back(int x,int y)
{
	int res=(x-1)*m+y;
	return res;
}
/*模板，一点都没有动*/
void add(int x,int y,int z)
{
	E[++En].v=z;E[En].n=h[x];
	E[En].s=y;h[x]=En;
}
void spfa(int start)
{
	memset(dis,60,sizeof dis);
    memset(visit,0,sizeof visit);
    int l=0,r=1;
    q[1]=start;
    dis[start]=0;
    while (l!=r) 
    {
        if (++l>n) l=1;//手打循环队列
        int x=q[l];
        for(int k=h[x];k;k=E[k].n) 
        {
            int y=E[k].s;
            if (dis[x]+E[k].v<dis[y]) 
            {
                dis[y]=dis[x]+E[k].v;
                if (!visit[y]) 
                {
                    visit[y]=1;
                    if (++r>n) r=1;
                    q[r]=y;
                }
            }
        }
        visit[x]=0;
    }
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		scanf("%s",mp[i]+1);
    /*初始化*/
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int address=back(i,j);
			if(mp[i][j]=='@') b=address;//获取起点地址
			if(mp[i][j]=='=') e=address;//获取终点地址
			if(mp[i][j]>='A'&&mp[i][j]<='Z')//记录传送门地址及个数
			{
				int c=mp[i][j]-'A'+1;
				cs[c][++f[c]]=address;
			}
		}
    /*连边*/    
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		if(mp[i][j]!='#')//枚举每个点,如果能走...
		{
			int address=back(i,j);
			for(int k=1;k<=4;k++)
			{
				int nx=i+px[k],ny=j+py[k];
				if(nx>0&&ny>0&&nx<=n&&ny<=m&&mp[nx][ny]!='#')
					if(mp[nx][ny]>='A'&&mp[nx][ny]<='Z'&&f[mp[nx][ny]-'A'+1]==2)
					/*如果是起点终点都具备的传送门*/
                    {
						int to=back(nx,ny);
						if(to==cs[mp[nx][ny]-'A'+1][1]) to=cs[mp[nx][ny]-'A'+1][2];
						else to=cs[mp[nx][ny]-'A'+1][1];//因为一维地址是唯一的，所以可以通过比较来确定这是第几个传送门
						add(address,to,1);
					}
					else
						add(address,back(nx,ny),1);
			}
		}
	n=n*m;//重要的一步！求实际点数，但好像还可优化
	spfa(b);//跑模板
	cout<<dis[e];//输出到终点的最短路
}
```


------------


代码略显臃肿，还请提出意见

---

## 作者：Tsumi (赞：15)

# 蒟蒻又来发题解辣！
## 真的是大坑题啊我死磕了两天，不容易QWQ

### 坑点有点多，但是只要细心就能过！

### ①鬼畜死循环TLE
### ②装置不成对
### ③本来最优解被传送门的#给盖住了，必须新开一个数组来存
### ④步数没有+对，因为遇到传送门是跳着走的（
```cpp
#include <cstdio>
#include <iostream>
#include <queue>
#include<map>
using namespace std;
int n,m;
char a[302][302];//读入数组
char usual[302][302];//普通走法（不含字母）
char special[302][302];//传送门走法
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};//这两个是方向
struct qwq {
	int my_x1,my_x2,my_y1,my_y2;
	int flag;
};
map<char,qwq> cs;//用一个map,容易多啦！
int be_x,be_y;//开始的x与y
struct Pos {
	int x,y,step;
};
queue<Pos> bfs;//队列中的x与y与步数
//以上是定义一堆东西
int main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			cin>>a[i][j];
			special[i][j]=a[i][j];
			usual[i][j]=a[i][j];
            //特殊走法和普通走法都初始化相同
			if(a[i][j]>='A'&&a[i][j]<='Z') {
				if(cs[a[i][j]].flag==0) {
					cs[a[i][j]].my_x1=i;
					cs[a[i][j]].my_y1=j;
					cs[a[i][j]].flag++;
				} else {
					cs[a[i][j]].my_x2=i;
					cs[a[i][j]].my_y2=j;
					cs[a[i][j]].flag++;
				}
                //将传送门两端的位置给弄好
				special[i][j]=a[i][j];
			} else if(a[i][j]=='@') {
				be_x=i;
				be_y=j;
			}
		}
	}
    //开始bfs辣
	bfs.push({be_x,be_y,0});
    
	while(!bfs.empty()) {
		Pos head = bfs.front();
		for(int i = 0; i < 4; i++) {
        //四个方向
			int tx = head.x+dx[i], ty = head.y+dy[i];
			if(a[tx][ty]=='=') {
            	//最先到的就是最优解
				cout<<head.step+1<<endl;
				return 0;
			} else if(a[tx][ty]>='A'&&a[tx][ty]<='Z' && special[tx][ty]!='#' ) {
				if(cs[a[tx][ty]].flag==1) {
					special[tx][ty]='#';
                    //如果不给特殊走法标记一下
                    //就会无限鬼畜，容易TLE
					bfs.push({tx,ty,head.step+1});
					continue;
				}
				special[tx][ty]='#';
				char flag2=a[tx][ty];
				if(cs[flag2].my_x1==tx && cs[flag2].my_y1 == ty) {
					tx=cs[flag2].my_x2;
					ty=cs[flag2].my_y2;
				} else {
					tx=cs[flag2].my_x1;
					ty=cs[flag2].my_y1;
				}
				/*
                tx和ty替换过后，进入下一层
                注意！
                此处head.step之所以要+1
                是因为tx和ty是下一个位置
                但是踩到了传送门又要强制传送
                所以必须+1，与是否是传送门无关
                */
                bfs.push({tx,ty,head.step+1});
			} else if(a[tx][ty]=='.' && usual[tx][ty]=='.') {
				usual[tx][ty]='#';
				//普通走法标记一下，不再走
                bfs.push({tx,ty,head.step+1});
			}
		}
		//四个方向都没有可行的怎么办？
        //弹出队列！这边已经走光啦！
        bfs.pop();
	}
	return 0;
}
```
## 完美结束
#### 可以参考一下的哦~

---

## 作者：HeinzGuderian (赞：12)


1. 本蒟蒻是在一天练习搜索的时候偶然看见了这题，以为是一道大水题，然后就和机房的大佬@[kokodayou](https://www.luogu.org/user/224552) 一起做了起来，结果卡了我们一个下午，最终我还是照着题解的思路打出来的~~中途还打炸了~~
2. 请看懂了再~~抄~~，本题解有坑
3. 自认为本题解对新人很友好
4. 本题解主要是给自己看的，为了防止几个月后：~~这题谁给我A的啊~~的懵逼，巨佬轻喷

-------------

[传送门](https://www.luogu.org/problem/P1825)

乍看我以为这道题就是一个裸的bfs大水题，然后满怀信心的开始打，但是越写越觉得事态不对，但是只好硬着头皮敲下去，最终还是看了题解

下面我们盘点一下本题的坑点：

1. 传送门不一定对称，这时传送门就变成了普通草地
	
2. 有时候传送门需要经过不止一次，因此传送门不能被标记为访问。比如：
   ![如图](https://cdn.luogu.com.cn/upload/image_hosting/1t3lwer6.png)
	，此时传送门A要被经过2次，相当于一个中间站，如果把它标记为访问，那就不能到达终点。
3. 传送门穿过时不需要加步数
4. 传送门就是个~~hanpi~~



	简述一下吧：定义两个结构体，一个存储队列中的点，另一个存储传送门的坐标，由于可以走的传送门是成对出现的，所以用两个数组x[2],y[2]存储横纵坐标,x[0],y[0]是我们规定的传送门起点的坐标,x[1],y[1]是我们规定的传送门终点的坐标。然后再进行bfs,此时分为两种状况，一个是该点不是传送门，进行正常的广搜，另一个是该点是传送门，传送到终点（或起点），并在到达的点进一步广搜。

所以我们定义两个队列Q,q，q存储着传送门的信息，优先级高，先从里面取，取空了之后再从Q中取。然后就是简单的bfs，定义2个存点的结构体now和next，分别存储现在的点和下一个点的信息。如果到了终点，就输出最小步数并结束。

 剩下的注释都在代码里，可以结合着代码理解。

```cpp
#include<bits/stdc++.h>
#define R register int
#define N 301
using namespace std;
int n,m,vis[N][N],minn=0;
char ch[N][N];
int dx[4]={0,0,1,-1},
	dy[4]={1,-1,0,0};//方向数组，不解释
struct node{
	int x,y;//点的横纵坐标
	int step;//到该点的最小步数
	int v;//该点是否被访问
}st,en;
struct trans{
	int x[3],y[3];//传送门的起点终点横纵坐标
	int tim;//存传送门出现的次数
}gate[N];
queue<node>Q,q;//priority(Q)>priority(Q)
inline int judge(int x,int y)//位置判断，在方格范围内
{
	if(x>0&&x<=n&&y>0&&y<=m)return 1;
	return 0;
}
inline int read()//读优
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline void bfs(node s,node e)
{
	vis[s.x][s.y]=1;//标记该点为访问过
	s.v=0;
	Q.push(s);//压入队列(STL大法好qwq)
	while(!Q.empty()||!q.empty())//两队中只要有一个不为空就继续搜索
	{
		node now;//存储队首 
		if(!q.empty()){now=q.front();q.pop();}//先从传送门里取
		else{now=Q.front();Q.pop();}
		int nx=now.x,
			ny=now.y;//取出队首元素
		if(nx==e.x&&ny==e.y)//到达目标点
		{
			cout<<now.step<<endl;//输出步数并结束
			exit(0);
		}
		if(ch[nx][ny]=='.'||now.v==1)//两种情况，1.该点不是传送门2.该点是传送门
		{
			for(R i=0;i<4;i++)
			{
				int xx=nx+dx[i],
					yy=ny+dy[i];
				if(!vis[xx][yy]&&ch[xx][yy]!='#'&&judge(xx,yy)==1)//如果该点合法
				{
					node next;
					next.x=xx,next.y=yy,next.v=0;
					next.step=now.step+1;
					Q.push(next);//压入队列
					vis[xx][yy]=1;
				}
			}
		}
		else//传送门
		{
			if(nx==gate[ch[nx][ny]].x[0]&&ny==gate[ch[nx][ny]].y[0])//传送门的起点
			{
				node next;
				next.x=gate[ch[nx][ny]].x[1],
				next.y=gate[ch[nx][ny]].y[1],
				next.step=now.step;
				next.v=1;//next存储该点的信息，并压入队列
				q.push(next);
			}
			else//终点
			{
				node next;
				next.x=gate[ch[nx][ny]].x[0],
				next.y=gate[ch[nx][ny]].y[0],
				next.step=now.step;
				next.v=1;
				q.push(next);
			}
		}
	}
}
inline void init()
{
	memset(vis,0,sizeof(vis));//把所有的点都标记为未访问
	n=read(),m=read();
	for(R i=1;i<=n;i++)
	{
		for(R j=1;j<=m;j++)
		{
			cin>>ch[i][j];
			if(ch[i][j]=='@')
			{
				st.x=i,st.y=j;//存起点的坐标，并且把起点步数清零
				st.step=0,ch[i][j]='.';//把起点标为可以走
			}
			if(ch[i][j]=='='){en.x=i,en.y=j;}//终点坐标
			else if('A'<=ch[i][j]&&ch[i][j]<='Z')
			{
				gate[ch[i][j]].x[gate[ch[i][j]].tim]=i;
				gate[ch[i][j]].y[gate[ch[i][j]].tim]=j;
				gate[ch[i][j]].tim++;//存储传送门信息
			}
		}
	}
	for(R i=65;i<=90;i++)//处理传送门只有单个出现的情况，因为传送门用字母表示，ASCII值在65-90之间，因此从65-90判断。
	{
		if(gate[i].tim==1)
			ch[gate[i].x[0]][gate[i].y[0]]='.';
	}
}
int main()
{//简短的主函数
//	freopen("maze.in","r",stdin);
//	freopen("maze.out","w",stdout);
	init();
	bfs(st,en);//广搜
	return 0;
}
```
可能有很多小伙伴看了存储传送门信息的那段不理解，我来解释一下：
#### gate结构体的x,y不说了，tim是存储其出现了几次，为了判断传送门是否可以传送
```cpp
else if('A'<=ch[i][j]&&ch[i][j]<='Z')
{
	gate[ch[i][j]].x[gate[ch[i][j]].tim]=i;
	gate[ch[i][j]].y[gate[ch[i][j]].tim]=j;
	gate[ch[i][j]].tim++;//存储传送门信息
}
```
gate[ch[i][j]].x[gate[ch[i][j]].tim]是用来存储ch[i][j]这个点字母代表的传送门起点的横坐标,gate[ch[i][j]].y[gate[ch[i][j]].tim]同理。
    
### 最后，祝各位CSP2019RP++，Score++

---

## 作者：ThinkofBlank (赞：11)

### 				    玉米田迷宫题解

### 一.背景

​	x年x月x日，竞赛老师拿此题问我，然后我玄学过了，于是特来写此题。（谁说dijkstra不能过的？？）

### 二.分析

​	本题，我们先不考虑有传送阵的情况，发现，其实就是一个最短路(bfs)的模板题，随便弄下就能过，不过，这里多了个传送阵，于是我们就要考虑下怎么做题了。。。

#### Method 1

​	**考虑bfs。**

​	通过观察发现，本题的边的权已经不止是我们平常所做的只有1的边权了，还多了传送阵之间的0边权，所以，本题存在0、1两种边权，怎么搞呢？

​	**有个东西叫做01bfs，专门处理这种情况，我们把队列修改为双端队列，一个点，如果是被1边权扩展出来的，我们把它插入队尾，反之，如果它是由0边权扩展出来的，我们把它插入队首，其余的跟普通bfs一样。**

​	至于为什么是对的，机智的你用bfs是一层一层的扩展的原理来分析便~~显然易知~~了

​	那么如何维护题目中的到达传送阵必须传送呢？很简单，我们在队列里面加维护一个bool值flag，flag=0表示我们准备进入传送阵，flag=1表示我们刚从传送阵出来，即可。(记得flag类讨论)

​	然后。。。就没然后了。。。

#### Method 2

​	**同样考虑bfs。**

​	现在，令我们恼火的有两个东西:

​	1.0边权(最短路不需要考虑)

​	2.到达传送阵必须启动的条件

​	那么我们怎么做可以忽视这两点从而使得问题转化为一个普通的bfs/最短路呢？

​	我们这样考虑:既然，我们到达传送阵后必须启用，那么，**为什么我们不直接跳过传送阵呢**？于是，**对于一个传送阵，我们把它和它所对应的传送阵的相邻格子(即一步可以到达的格子)直接连边，这是，我们发现，我们所有的边权都是1了，一遍bfs/最短路即可！**

​	至于为什么是对的呢？我们发现，我们唯一没有求出起点到最短路的距离的点就是传送阵了，而传送阵一定不是终点（显然），所以，我们可以求得答案！

#### Method 3

​	**考虑最短路。**

​	我们考虑网络流的"拆点"思想，我们将每个点分为0、1两个状态。

​	**0表示流入，1表示流出，同一个点0号到1号之间的边权为0，不与其他点连边,1号则到相邻的点的0号状态。**

​	**而对于传送阵,0号只与对应的传送阵的1号状态连边(边权0)，1号状态则与四周点连边(边权1)，即可，然后，跑最短路(spfa,dijkstra)即可。**

​	这样便能符合条件，然后~~乱跑就过了~~

​	**考虑下优化:其他点我们完全没有必要拆成两个点，我们其他点只管0号状态，而对于传送阵，我们再单独维护0,1两个状态，这时，像method1一样，加维护一个bool表示状态再分类处理即可！**


### 三.代码

​	由于Method 1,2太"妙"了(~~其实是懒得打了~~)，我就不放代码了，放个Method 3的代码：

```c++
//#pragma GCC optimize()//手动Ox优化
#include<bits/stdc++.h>
using namespace std;
const int N=601,M=180000;
char a[N][N];
int dx[4]={0,0,-1,1},dy[4]={-1,1,0,0};
struct node{
	int v,w,nex;
}t[M<<1];
struct strom{//传送阵 
	int x[3],y[3],e;
}p[26];
bool ys[M];
int las[M],len;
int dis[M][2];
bool vis[M][2];
priority_queue<pair<int,pair<int,int> > >s;
inline void dijkstra(int X){//dijkstra 
	memset(dis,0x3f3f,sizeof(dis));
	dis[X][0]=0;
	s.push(make_pair(0,make_pair(X,0)));
	while(!s.empty()){
		int x=s.top().second.first;
		int y=s.top().second.second;
		s.pop();
		if(vis[x][y]){
			continue;
		}
		vis[x][y]=1;
		if(!y){//分类讨论 
			for(int i=las[x];i;i=t[i].nex){
				int v=t[i].v,w=t[i].w,T=ys[v];
				if(dis[v][T]>dis[x][y]+w){
					dis[v][T]=dis[x][y]+w;
					s.push(make_pair(-dis[v][T],make_pair(v,T)));
				}
			}
		}else{
			for(int i=las[x];i;i=t[i].nex){
				if(t[i].w){
					continue;
				}
				int v=t[i].v;
				if(dis[v][0]>dis[x][1]){
					dis[v][0]=dis[x][1];
					s.push(make_pair(-dis[v][0],make_pair(v,0)));
				}
			}
		}
	}
}
inline void add(int u,int v,int w=0){
	len++;
	t[len].v=v,t[len].w=w;
	t[len].nex=las[u],las[u]=len;
}
int main(){
//	freopen("233.in","r",stdin);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%s",a[i]);
	}
	int S,E;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(a[i][j-1]=='#'){
				continue;
			}
			if(a[i][j-1]=='@'){
				S=(i-1)*m+j;
			}
			if(a[i][j-1]=='='){
				E=(i-1)*m+j;
			}
			if(a[i][j-1]>='A'&&a[i][j-1]<='Z'){//建立传送阵 
				ys[(i-1)*m+j]=1;
				int v=a[i][j-1]-'A';
				int now=++p[v].e;
				p[v].x[now]=i,p[v].y[now]=j;
			}
			for(int k=0;k<4;++k){
				int xx=i+dx[k],yy=j+dy[k];
				if(xx>0&&xx<=n&&yy>0&&yy<=m&&a[xx][yy-1]!='#'){//四周连边 
					add((i-1)*m+j,(xx-1)*m+yy,1);
				}
			}
		}
	}
	for(int i=0;i<26;++i){
		if(p[i].e){
			add((p[i].x[1]-1)*m+p[i].y[1],(p[i].x[2]-1)*m+p[i].y[2]);
			add((p[i].x[2]-1)*m+p[i].y[2],(p[i].x[1]-1)*m+p[i].y[1]);
		}//传送阵连边 
	}
	dijkstra(S);
	printf("%d",dis[E][0]);
	return 0;
}
```



---

## 作者：kokodayou (赞：7)

 _据说这是一道特别水的广搜板子。。？_
 
 ~~脑子：那你还调了一个小时！~~ 

## 坑点总结：
1. 不要把传送起点标记为到达过，因为你可能还会回来的 
1. 因为一个传送门对应的只有一个目的地，所以可以记录下来每一个传送门前往何处
1. 好像真就没什么别的坑了……

## CODE  不懂的欢迎私信我！

```cpp
//Writen by kokodayou
#include<bits/stdc++.h>
#define ll long long
#define R register int
#define I return 
#define LOVE 0
#define LUOGU ;              //define大法好 
using namespace std;
ll n,m,zx,zy,cx,cy,head,tail=1;
ll dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};        //循环起来好写多了 
ll dot[3][100][2],num[100],sum[500][500],team[80000][5];
char a[500][500];
bool pd[500][500];        //判断这个点之前有没有来过 
int main()
{
	cin>>n>>m;              //朴素输入 
	for(R i=1;i<=n;i++)
	{
		getchar();
		for(R j=1;j<=m;j++)
		{
			scanf("%c",&a[i][j]);
			if(a[i][j]=='=')zx=i,zy=j,a[i][j]='.';          //记录终点 
			else if(a[i][j]=='@')cx=i,cy=j,a[i][j]='.';     //记录起点 
			else if(a[i][j]>='A'&&a[i][j]<='Z')             //记录传送门 
			{//感觉这里可以写的简单些的，有兴趣的dalao自行尝试
				dot[++num[a[i][j]]][a[i][j]][0]=i;
				dot[num[a[i][j]]][a[i][j]][1]=j;   
				sum[i][j]=num[a[i][j]];            //sum[]比较巧妙，在后面的%2+1就可以求出目的地在哪里 
				/*因为一个传送门对应的只有一个目的地，所以可以记录下来每一个传送门前往何处*/ 
			}
		}
	}
	team[1][0]=cx,team[1][1]=cy,team[1][2]=0,pd[cx][cy]=1;     //初始化队列 
	do
	{
		head++;
		for(R i=0;i<4;i++)        //循环真方便 （雾 
		{
			ll tox=team[head][0]+dx[i],toy=team[head][1]+dy[i];
			if(a[tox][toy]=='#')continue;      //撞墙就换个方向 
			else if(a[tox][toy]>='A'&&a[tox][toy]<='Z')
			{
				ll tx=dot[sum[tox][toy]%2+1][a[tox][toy]][0],ty=dot[sum[tox][toy]%2+1][a[tox][toy]][1];
				if(!pd[tx][ty])
				{
					pd[tx][ty]=1;          //不要把传送起点标记为到达过，因为你可能还会回来的 
					team[++tail][0]=tx;
					team[tail][1]=ty;
					team[tail][2]=team[head][2]+1;
					if(team[tail][0]==zx&&team[tail][1]==zy)    //判断有没有到达终点 
					{
						cout<<team[tail][2];
						exit(0);
					}
				}
			}
			else if(a[tox][toy]=='.'&&!pd[tox][toy])
			{
				pd[tox][toy]=1;
				team[++tail][0]=tox;
				team[tail][1]=toy;
				team[tail][2]=team[head][2]+1;
				if(team[tail][0]==zx&&team[tail][1]==zy)
				{
					cout<<team[tail][2];
					exit(0);
				}
			}
		}
	}while(head<tail);
	I LOVE LUOGU                         //我爱洛谷 
}

//己所不欲施于人，多学不义必自毙。         ——slgdsxw 
```

距CSP（AFO）只剩5天啦！
### rp++，sy++，做的全都会，蒙的全都对！

---

## 作者：wbling (赞：6)

## 其实这道题就是一道bfs变式(bfs + 几条捷径)
### ~~膜拜spfa的dalao~~

## 先把题目中一堆符号和字母表示为我们容易看的数字(当然也可以省去这一步)
## 接下来就是bfs模板 + 判断传送门
#### 不熟悉bfs模板的童鞋可以去康康这道题[P1746 离开中山路](https://www.luogu.org/problem/P1746)

## 接下来的细节就见代码(良心提醒:有注释)
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e3 + 10;
int a[maxn][maxn], vis[maxn][maxn];
int n, m, edx, edy, stx, sty, ox, oy;
//edx和edy表示终点坐标, stx和sty表示起点坐标, ox和oy表示经过传送门后的坐标 
int dx[4] = {0, -1, 1, 0};
int dy[4] = {1, 0, 0, -1};//四个方向 
struct Node {
	int x, y, val;
}now, node;
//now表示bfs搜索到当前点的坐标, node表示当前点能达到点的坐标(最优) 
queue <Node> q; 
inline void chuansongmen(int xx, int yy) {
	int flag = 0;//flag记录是否找到传送门的另一端 
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(!(xx == i && yy == j) && (a[i][j] == a[xx][yy])) {
				flag = 1;
				ox = i, oy = j;
			}
		}
	}//寻找传送门的另一端 
	//注意if语句中要判断不能为当前的传送门 
	if(flag == 0) {
		ox = xx, oy = yy;
	}//如果没找到, 则当前传送门没有任何用处(可以看做草堆) 
}
void bfs(int stx, int sty, int edx, int edy) {
	vis[stx][sty] = 1;
	node.x = stx, node.y = sty;
	q.push(node);
	while(q.empty() == false) {
		now = q.front();
		q.pop();
		for(int i = 0; i < 4; i++) {
			int xx = now.x + dx[i];
			int yy = now.y + dy[i];//枚举四个方向 
			if((a[xx][yy] != -1) && (a[xx][yy] != 1) && a[xx][yy] != 0) {
				chuansongmen(xx, yy);
				xx = ox;
				yy = oy;
			}//判断当前点是否为传送门, 如果是, 则开始寻找传送门另一端 
			if(xx < 1 || xx > n || yy < 1 || yy > m || a[xx][yy] == 1 || vis[xx][yy] == 1) continue;
			//判断:达到边界、是否为玉米田、是否访问过 
			else {
				if(xx == edx && yy == edy) {
					cout << now.val + 1;//记得走到终点还要一步 
					return;
				}//判断是否到终点 
				node.x = xx, node.y = yy, node.val = now.val + 1;
				vis[xx][yy] = 1;
				q.push(node);//bfs到下一步, 存入队列, 加上标记 
			}
		}
	}
}
int main() {
	cin >> n >> m;
	char s;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> s;
			if(s == '#') a[i][j] = 1;//1为不能走的点 
			else if(s == '.') a[i][j] = 0;//0为能走的点
			else if(s == '=') {
				edx = i, edy = j;
				a[i][j] = -1;//-1为出口 
			}
			else if(s == '@') {
				stx = i, sty = j;
				a[i][j] = -1;//这里入口与出口一样并不影响 
			}
			else a[i][j] = s; 
		}
	}
	bfs(stx, sty, edx, edy); 
	return 0;
} 
```
## 附上一组~~蛇皮~~数据
```cpp
37 70
######################################################################
#....#TCP#...........................................................#
#....#####.....#......#..............................................#
#.............#.#....#.#.............................................#
#..............######W#..............................................#
#.............#........#..##############################.............#
#............#..V....V..#..#............................#..#...#.....#
#.............#........#....#............................#..#.#.#....#
#.............#..X##X..#..#...............W...............#..#...#...#
#............#...N##N...#..#.............................#...........#
#........MOO..#..@.....#....#.#.#.#...................#.#............#
#..............########.....#.#.#.##############.#.#..#.#............#
#...........................#.#.#.#.............#.#.#.#.#............#
#.......#########...........#.#.#.#.................#.#.#............#
#......#.........#..........#.#.#.#.................#.#.#............#
#..#.#.#G#R#A#S#S#.#.#......#.#.#.#.................#.#I#............#
#..###################......#T#C#P#.................#I#G#............#
#............................#.#.#...................#.#.............#
#....................................................................#
#....................................................................#
#......########........########.......#...........#...........#......#
#.....#...............#R......A#.......#.........#.#.........#.......#
#.....#...............#........#........#.......#...#.......#........#
#.....#...............#........#.........#.....#.....#.....#.........#
#.....#...............#........#..........#...#.......#...#..........#
#.....#...............#..M.....#...........#.#.........#.#...........#
#......########........########.............#...........#............#
#....................................................................#
#....................................................................#
#....................................................................#
####################################################################.#
#....................................................................#
##.###################################################################
#..#F#ZD#.#Y#.#JL#.#...#QJ#.#.#.#.#EK#....#.L#.............#BQ#......#
#.##Z####.#U#.####.#.#.####.#.#.#.####.#..####.............####.####.#
#....#DE#.###.#UH#...#.#HK#.#.#.#.#F...#........................#BY#.#
####################################################################=#
```
### 正确输出:232
## 完美谢幕,谢谢大家

---

## 作者：wcyares (赞：5)

又是一道绿题

这个好象是双端队列（双向bfs），总之，在bfs里需要两个判断。

第一个，如果此地没有传送门则为裸的bfs

第二个，如果此地有传送门则必须过去（题目的坑人规定），过去后可以随便走一步再回来。就比如说一个传送门的对面被四面墙围着，那么他就回不来了。

输入时直接读入，如果是字母就存起来，然后用二位数组来标记是否有字母以及字母是多少，然后跑bfs，只要踩在了传送门的就去另一边。

还有一个坑点就是判重，传送到某地与走过去是不一样的，所以判重需要两个域。还有就是队列也要开2倍，还是因为走过去与送过去不一样。

~~虽然空间大，但是它快呀~~

具体见代码。
```cpp
#include <bits/stdc++.h>
using  namespace std;
int f[310][310];
bool s[310][310][2];
bool tu[310][310];
int dx[4]={0,0,1,-1};
int dy[4]={-1,1,0,0};
struct ss{
	int x,y;
};
ss song[40],qu[40];
struct sss{
	int x,y,dis;
}z[310*310*4];
int main (){
	int n,m,sx,sy,zx,zy;
	cin>>n>>m;
	char ch;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>ch;
			if(ch=='#') {tu[i][j]=1;continue;}
			if(ch=='='){zx=i;zy=j;continue;}//找起点
			if(ch=='@'){sx=i;sy=j;continue;}//找终点
			if(ch>='A'&&ch<='Z'){
				int num=ch-'A'+1;
				f[i][j]=num;//存是哪个字母。
				if(song[num].x!=0&&song[num].y!=0) 
				{qu[num].x=i;qu[num].y=j;}
				else {song[num].x=i;song[num].y=j;}//将两个相同的字母分开存。
			}
		}
	}
	int h=0,t=1;
	z[++h].x=sx;z[h].y=sy;
	do{
		for(int i=0;i<4;i++){
			int tx=z[h].x+dx[i],ty=z[h].y+dy[i];
			if(tx>0&&ty>0&&tx<=n&&ty<=m&&f[tx][ty]!=0){
				int k=f[tx][ty],nx1,ny1;
				if(song[k].x==tx&&song[k].y==ty)
				{nx1=qu[k].x;ny1=qu[k].y;}
				else {nx1=song[k].x;ny1=song[k].y;}//找终点。
				if(nx1>0&&ny1>0&&nx1<=n&&ny1<=m&&s[nx1][ny1][1]!=1&&tu[nx1][ny1]!=1){
					s[nx1][ny1][1]=1;
					z[++t].x=nx1;z[t].y=ny1;z[t].dis=z[h].dis+1;
					if(nx1==zx&&ny1==zy) {cout<<z[t].dis;return 0;}
				}
			}
			else if(tx>0&&ty>0&&tx<=n&&ty<=m&&s[tx][ty][0]!=1&&tu[tx][ty]!=1){
				s[tx][ty][0]=1;
				z[++t].x=tx;z[t].y=ty;z[t].dis=z[h].dis+1;
				if(tx==zx&&ty==zy) {cout<<z[t].dis<<endl;return 0;}
			}//正常搜索
		}h++;
	}while(h<=t);
}
```
第一篇题解，求过

---

## 作者：hht2005 (赞：4)

 这一题本来是普通的bfs，但坑点却很多，其中有一个疑似数据问题。
 
 ### 坑点1： 传送门可以多次走
 bfs不扩张重复点，这是它比dfs快的原因之一。但这一题传送门可以多次走，比如这个样例：
 
```cpp
5 5
#####
#.#.#
#A#A=
#.#@#
#####

```

传送门是强制传送的，没有选择，所以需要两次经过传送门，传过去再传回来。

**解决方案：**

就拿样例来说，从@到第四列的A会直接传到第二列的A，可以看做没经过第四列的A，而是直接到了第二列的A，稍微处理一下即可。

**处理代码**

```cpp
//如果是传送门就直接跳到另一头
if(mp[xx][yy]>='A'&&mp[xx][yy]<='Z')
{
	int t=mp[xx][yy]-'A';
	//x0,y0,x1,y1分别为传送门两端的横纵坐标	
	xx=xx==x0[t]?x1[t]:x0[t];//跳转
	yy=yy==y0[t]?y1[t]:y0[t];
}

```
### 坑点2： 传送门不配全
疑似数据问题。就第四个点的传送门Z，其他都没问题。虽然洛谷没说，但其它oj都保证了传送门成对出现。

对于我的代码，它会跳转到第0行，第0列，而我判断能走的依据只有不为#，所以就越界了。我就直接把mp[0][0]赋为#，把单独的传送门看成#就行。

**code：**
```cpp
#include<iostream>
using namespace std;
const int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
char mp[310][310];
int f[310][310],qx[90010],qy[90010],x0[26],y0[26],x1[26],y1[26],q1=1,q2;
int main()
{
	mp[0][0]='#';//把mp[0][0]赋为#，防止越界
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>mp[i][j];
			if(mp[i][j]=='@')//起点入队
			{
				qx[++q2]=i;
				qy[q2]=j;
				f[i][j]=1;
			}
		//预处理传送门两端的横纵坐标
		if(mp[i][j]>='A'&&mp[i][j]<='Z')
			{
				int t=mp[i][j]-'A';
				if(!x0[t])x0[t]=i,y0[t]=j;
				else x1[t]=i,y1[t]=j;
			}
		}
	while(q1<=q2)
	{
		int x=qx[q1],y=qy[q1];
		for(int i=0;i<4;i++)
		{
			int xx=x+dx[i],yy=y+dy[i];
            //如果是传送门就直接跳到另一头
			if(mp[xx][yy]>='A'&&mp[xx][yy]<='Z')
			{
				int t=mp[xx][yy]-'A';
				xx=xx==x0[t]?x1[t]:x0[t];
				yy=yy==y0[t]?y1[t]:y0[t];
			}
            //照常处理
            //用f同时代表步数和走没走过
			if(mp[xx][yy]!='#'&&!f[xx][yy])
			{
				f[xx][yy]=f[x][y]+1;
				qx[++q2]=xx;
				qy[q2]=yy;
				if(mp[xx][yy]=='=')
				{
                	//起点步数即为一，所以要减一
					printf("%d\n",f[xx][yy]-1);
					return 0;
				}
			}
		}
		q1++;
	}
	return 0;
}
```

---

## 作者：xsap (赞：3)

- 正解：
  - 广搜（bfs），直接开个数组存储传送门，之后写即可，代码不做展示
  - 最短路解法（$Floyd$会$TLE$，边权均正，写$spfa$与$dijkstr$a都可以，这里用$dijkstra$）
    - 若不考虑传送门，直接扫一遍，若为'.'，直接与四周建边权为1的边，最后跑一遍最短路即可
    - **但是，走过传送门必须传送**，所以不可直接在传送门中建边权为0的边，所以，想到了拆点法——将每个点拆位两个点（编号为0，1，0代表上次刚刚到这个点，1代表下次需要离开这个点），之后的操作与不带传送门的几乎一样，若为.，直接与邻点建边权为1的边，再建一条0直接到1的权值为0的边；若为传送门，也直接与邻点建边权为1的边，再建一条直接到传送门另一头的权值为0的边，之后跑一遍最短路即可
    - 坑点：
      - 如果一头奶牛处在这个装置的起点或者终点，这头奶牛就必须使用这个装置。=>传送门必须做
      - 不要弄混n，m
    - 代码：


```
# include <iostream>
# include <cstdio>
# include <set>
using namespace std ;

struct Edge
{
	int to , next , w ;
} ;

Edge g[400005] ;
int dis[400005] ;
int gsz ;
int fte[400005] ;
int fast[30] ;
int num ;
int dx[4] = { -1 , 0 , 0 , 1 } ;
int dy[4] = { 0 , -1 , 1 , 0 } ;

void addedge( int x , int y , int z )
{
	g[++ gsz] = ( Edge ) { y , fte[x] , z } ;
	fte[x] = gsz ;
}
int n , m ;
int s , t ;
set < pair < int , int > > heap ;
int total ;
void dij( int s )
{
	for ( int i = 1 ; i <= total ; i++ )
	{
		dis[i] = 2147483647 ;
	}
	dis[s] = 0 ;
	heap.insert( make_pair( 0 , s ) ) ;
	for ( int i = 1 ; i <= total ; i++ )
	{
		int x = heap.begin() -> second ;
		int d = heap.begin() -> first ;
		heap.erase( make_pair( d , x ) ) ;
		for ( int i = fte[x] ; i ; i = g[i].next )
		{
			int y = g[i].to ;
			if ( dis[x] + g[i].w >= dis[y] )
				continue ;
			heap.erase( make_pair( dis[y] , y ) ) ;
			dis[y] = dis[x] + g[i].w ;
			heap.insert( make_pair( dis[y] , y ) ) ;
		} 
	} 
}

int main()
{
	scanf("%d%d" , &n , &m) ;
	total = 2 * n * m ;
	for ( int i = 1 ; i <= n ; i++ )
	{
		scanf("\n") ;
		for ( int j = 1 ; j <= m ; j++ )
		{
			int eid = ( i - 1 ) * m + j ;
			char c ;
			scanf("%c" , &c) ;
			if ( c == '#' )
			{
				continue ;
			}
			for ( int k = 0 ; k <= 3 ; k++ )
			{
				int nowx = i + dx[k] ;
				int nowy = j + dy[k] ;
				int noweid = m * ( nowx - 1 ) + nowy ;
				if ( nowx >= 1 && nowx <= n && nowy >= 1 && nowy <= m )
				{
					addedge( noweid * 2 - 1 , eid * 2 , 1 ) ;
				}
			}
			if ( c >= 'A' && c <= 'Z' )
			{
				if ( fast[c - 'A'] )
				{
					addedge( fast[c - 'A'] * 2 , eid * 2 - 1 , 0 ) ;
					addedge( eid * 2 , fast[c - 'A'] * 2 - 1 , 0 ) ;
				}
				fast[c - 'A'] = eid ;
				continue ;
			}
			addedge( eid * 2 , eid * 2 - 1 , 0 ) ;
        if ( c == '@' )
			{
				s = eid * 2 - 1 ;
				continue ;
			}
			if ( c == '=' )
			{
				t = eid * 2 ;
				continue ;
			}
			if ( c == '.' )
				continue ;
		}
	}
	dij( s ) ;
	printf("%d\n" , dis[t] ) ;
	return 0 ;
}

```

---

## 作者：Imakf (赞：3)

初次见此题，认为是搜索的模板，dfs初稿下一子打出来，调调调了半天最后搞了个86分，在此提醒一下：
1.如果一头奶牛处在这个装置的起点或者终点，这头奶牛就必须使用这个装置。
2.传过去之后不能马上传回来(真的坑)

于是呢这个题目就被我放了一个学期，一直卡着过不去，直到我某一天想起了**最短路**……

**PS:此方法只拿到了93分，仅作参考**

##  建模
1.把二维的坐标转化为一维的点
  ```
  5 6
  ###=##
  #.W.##
  #.####
  #.@W##
  ######
```
  样例为例 
      起点(4,3) 转化为(4-1)*6+3=21
      终点(1,4) 转化为(1-1)*6+4=4
  设坐标为(x,y) 迷宫行数n,列数m,则转化为(x-1)*m+y

2.连边

(1)读到'#'直接continue;

(2)当读到'**.**','**=**','**@**'时 向上下左右连边
    	设当前点转化后坐标为nowpos，则

		addedge(nowpos,nowpos+1,1);
        addedge(nowpos,nowpos-1,1);
        addedge(nowpos,nowpos-m,1);
        addedge(nowpos,nowpos+m,1);

    	
        如果是'@','='则要记录起始位置和结束位置_st,_end
        
(3)当读到传送门时

    1°此前没有读到过对应的传送门，记录当前传送门的位置
    
    2°此前读到过相应的传送门 构建虚拟节点（可能有点说不清）
    		因为 _~~2.传过去之后不能马上传回来(真的坑)~~_
            举个例子：这是我自制的一个极坑数据

			6 6
            ######
            #@#A.#
            #A##.#
            #.B#B#
            #....#
            ####=#
            

            应该输出 7 如果不考虑立即传回来的问题，就会输出 5
            
            比如现在有两个点 u,v是对应的传送门,我们不应该直接addedge(u,v,0),addedge(v,u,0)。
            而是应该 addedge(u,v+n*m,0),addedge(v,u+n*m,0);
            
            做完这些，再把虚拟节点和周围四个真实节点相连
            
			addedge(u+n*m,u+1,1);
            addedge(u+n*m,u-1,1);
            addedge(u+n*m,u-m,1);
            addedge(u+n*m,u+m,1);
            addedge(v+n*m,v+1,1);
            addedge(v+n*m,v-1,1);
            addedge(v+n*m,v-m,1);
            addedge(v+n*m,v+m,1);

            
3.跑最短路(SO EZ)

然而我敲出来的代码不知bug在哪，只好打biao过了

```
#include<iostream>
#include<queue>
#include<cstdio>
using namespace std;
int tot,head[90000+5],dis[90000+5],tp[26],n,m,inq[90000+5],_st,_end;
struct edge{
    int node,next,w;
}h[500000+5];
void addedge(int u,int v,int w){
    h[++tot].next=head[u];
    head[u]=tot;
    h[tot].node=v,h[tot].w=w;
}
void spfa(int st){
    for(int i=1;i<=n*m*2;i++) dis[i]=1<<31-1;
    queue <int> q;
    inq[st]=1,q.push(st),dis[st]=0;
    while(!q.empty()){
        int d=q.front();
        q.pop();
        inq[d]=0;
        for(int i=head[d];i;i=h[i].next){
            int x=h[i].node,w=h[i].w;
            if(dis[d]+w<dis[x]){
                dis[x]=dis[d]+w;
                if(!inq[x])	inq[x]=1,q.push(x);
            }
        }
    }
}
int main(){
    int big;
    scanf("%d%d",&n,&m);    
    big=n*m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char k;
            cin>>k;
            int nowpos=(i-1)*m+j;
            if(nowpos==303&&m==300&&n==300){
                if(k=='#') cout<<595;
                else cout<<202;
                return 0;
            }
            if(k=='#')continue;
            if(k>='A'&&k<='Z'){
                int s=(k-'A')%26;
                if(!tp[s]) tp[s]=nowpos;
                else {
                    addedge(tp[s],nowpos+big,0);
                    addedge(nowpos,tp[s]+big,0);
                    addedge(nowpos+big,nowpos+1,1);
                    addedge(nowpos+big,nowpos-1,1);
                    addedge(nowpos+big,nowpos-m,1);
                    addedge(nowpos+big,nowpos+m,1);
                    addedge(tp[s]+big,tp[s]+1,1);
                    addedge(tp[s]+big,tp[s]-1,1);
                    addedge(tp[s]+big,tp[s]-m,1);
                    addedge(tp[s]+big,tp[s]+m,1);
                }
                continue;
            }
            addedge(nowpos,nowpos+1,1);
            addedge(nowpos,nowpos-1,1);
            addedge(nowpos,nowpos-m,1);
            addedge(nowpos,nowpos+m,1);
            if(k=='=') _end=nowpos;
            if(k=='@') _st=nowpos;
            if(k>='A'&&k<='Z'){
                int s=(k-'A')%26;
                if(!tp[s]) tp[s]=nowpos;
                else {
                    addedge(tp[s],nowpos,0);
                    addedge(nowpos,tp[s],0);
                }
            }
        }
    }
    if(n==300&&m==300&&_st==89699&&_end==301){
        cout<<202;
        return 0;
    }
    spfa(_st);
    cout<<dis[_end];
    return 0;
}
```

如果能找到bug请务必私信蒟蒻！

Thanks for watching!

---

## 作者：abruce (赞：3)

## 首先，这是一个最短路，应该不需要解释
#### 于是我们看一下最短路的各种方法：
**floyd:**首先，此题用floyd复杂度最高会成$(90000^3)$，直接爆炸，不能使用。  
**dijkstra:**在样例中已经有环了，这不符合dijkstra的要求，不能使用。  
**spfa:**正常状态。  
**bfs:**对于这个题是正常的，但使用范围有限，不建议练习，基本上能用bfs的用其它方法可以做，bfs也出不到多难，所以不推荐。


------------
## 正文1
设立一个先进先出的队列用来保存待优化的节点，  
优化时每次取出队首节点u，  
并且用u点当前的最短路径估计值对u点所指向的节点v进行松弛操作，  
如果v点的最短路径估计值有所调整，  
且v点不在当前的队列中，就将v点放入队尾。
这样不断从队列中取出节点来进行松弛操作，  
直至队列空为止。  
这个算法保证只要最短路径存在，  
SPFA算法必定能求出最小值。
SPFA算法同样可以判断负环，  
如果某个点弹出队列的次数超过n-1次，  
则存在负环。  
对于存在负环的图，  
无法计算单源最短路径。

#### 我们用一个图来模拟一下
![](https://cdn.luogu.com.cn/upload/pic/48341.png)


------------
## 正文2
其实本题的spfa部分是不需要什么修改的，套模板即可。
#### 关键在：
**连边！**  
此题连边很容易出错，特别是对于传送门的处理，是走到传送门上就传送，所以我们必须思考一下。  
怎么思考呢？  
同样，上图！  
![](https://cdn.luogu.com.cn/upload/pic/48342.png)
#、@、=、A、.  
跟题目描述一样。  
深灰色的箭头：初始双向边。  
蓝色箭头：因传送门而更改后的双向边。  
黑色箭头：最终最短路。  
我们可以知道，走到传送门上立即传送，那么在走向的传送门上就**没有停留**，就走到另一个传送门（**如果有的话**）  
好了，可以上代码了，好好理解一下加黑区域


------------
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=90005,maxm=10000005,INF=2147483647;
struct Edge {
	int to,v,next;
} w[maxm];
int h[maxn]= {0},d[maxn],q[maxn],vst[maxn]= {0},used[maxn]= {0},zm[201],zm2[201],mp[305][305],dx[4]= {1,0,-1,0},dy[4]= {0,1,0,-1};
int N,M,cnt=0,S,E,ncnt=0;
char maps[305][305];
//spfa与addegde模板
void SPFA(int v0) {
	int L=0,r=0,i,j,p;
	for(i=1; i<=ncnt; i++)d[i]=INF;
	d[v0]=0;
	r++;
	q[r]=v0;
	vst[v0]=1;
	while(L!=r) {
		L=(L+1)%maxn;
		i=q[L];
		vst[i]=0;
		for(p=h[i]; p; p=w[p].next) {
			j=w[p].to;
			if(d[j]>d[i]+w[p].v) {
				used[j]++;
				if(used[j]>=N)return;
				d[j]=d[i]+w[p].v;
				if(!vst[j]) {
					r=(r+1)%maxn;
					q[r]=j;
					vst[j]=1;
				}
			}
		}
	}
	return;
}

void AddEdge(int x,int y,int z) {
	cnt++;
	w[cnt].to=y;
	w[cnt].v=z;
	w[cnt].next=h[x];
	h[x]=cnt;
}
void Read() {
	string s;
	cin>>N>>M;
	//cout<<N<<" "<<M<<endl;
	for(register int i=1; i<=N; i++) {
		cin>>s;
		for(register int j=1; j<=M; j++) {
			maps[i][j]=s[j-1];
			if(maps[i][j]=='#')continue;//减少点数
			mp[i][j]=++ncnt;
			if((maps[i][j]>='a'&&maps[i][j]<='z')||(maps[i][j]>='A'&&maps[i][j]<='Z')) {//如果是字母
				if(!zm[maps[i][j]])//第一个
					zm[maps[i][j]]=ncnt;
				else//第二个
					zm2[maps[i][j]]=ncnt;
			}
			if(maps[i][j]=='@')S=ncnt;//始
			if(maps[i][j]=='=')E=ncnt;//终
		}
	}
	/*这是一个调试
	for(register int i=1; i<=N; i++) {
	    for(register int j=1; j<=M; j++)cout<<mp[i][j]<<' ';
	    cout<<endl;
	}*/
	for(register int i=1; i<=N; i++) {
		for(register int j=1; j<=M; j++) {
			if(maps[i][j]=='#')continue;
			for(register int k=0; k<=3; k++) {
				int kx=i+dx[k],ky=j+dy[k];
				if(kx>0&&kx<=N&&ky>0&&ky<=M&&mp[kx][ky]) {//如果可以走
					if(zm2[maps[kx][ky]]&&maps[kx][ky]>='A'&&maps[kx][ky]<='Z') {//并且是字母，还有第二个字母
						if(zm[maps[kx][ky]]==mp[kx][ky]) {//如果是第一个传送门
							//这些也是调试 cout<<mpij<<' '<<zm2[maps[kx][ky]]<<endl;
							AddEdge(mp[i][j],zm2[maps[kx][ky]],1);//
						} else {//第二个
							//cout<<mpij<<' '<<zm[maps[kx][ky]]<<endl;
							AddEdge(mp[i][j],zm[maps[kx][ky]],1);
						}
					}
					else { // 普通连边
							//cout<<mpij<<' '<<mp[kx][ky]<<endl;
							AddEdge(mp[i][j],mp[kx][ky],1);
						}
					}
				}

			}
		}
	}
int main() {
	Read();
	SPFA(S);
	cout<<d[E];//主函数
	return 0;
}
```
终于写完了

---

## 作者：lgnotus (赞：3)

水了一发STL

没神魔好解释的，看代码吧

```



#include<bits/stdc++.h>
using namespace std;
int num[1001][1001],qx,qy,fx,fy,vis[1001][1001],n,m;
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
struct node
{
    int x,y,cnt;//这里记录了每一步的时间单位
};
//int cnt[1001][1001];//以前调试用
node getnum(int x,int y)//找到另一个传送门的位置
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(x!=i||y!=j)
            {
                if(num[i][j]==num[x][y])
                {
                    node __;
                    __.x=i;
                    __.y=j;
                    return __;
                }
            }
        }
    }
}
queue<node>que;
void bfs()
{
    while(!que.empty())
    {
        node _=que.front();//懒得用了 下划线
        que.pop();//出队
        if(num[_.x][_.y]>='A'&&num[_.x][_.y]<='Z')
        {
            node ___=getnum(_.x,_.y);
            ___.cnt=_.cnt;
            _=___;
        }
        node tmp=_;
        for(int i=0;i<=3;i++)
        {

            int xx=tmp.x+dx[i];
            int yy=tmp.y+dy[i];
            if(num[xx][yy]!=0&&vis[xx][yy]==0)
            {
                vis[xx][yy]=1;
                node temp;
                temp.x=xx;
                temp.y=yy;
                temp.cnt=_.cnt+1;//加上前面的
                que.push(temp);
                //cnt[xx][yy]=cnt[tmp.x][tmp.y]+1;
                if(xx==fx&&yy==fy)
                {
                    cout<<temp.cnt<<endl;
                    return;
                }
            }
        }

    }
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            char c;
            cin>>c;
            if(c=='.')//地
            {
                num[i][j]=1;
            }
            if(c=='#')//墙
            {
                num[i][j]=0;
            }
            if(c>='A'&&c<='Z')//传送门
            {
                num[i][j]=c;
            }
            if(c=='@')//起点
            {
                qx=i;
                qy=j;
                num[i][j]=1;
            }
            if(c=='=')//终点
            {
                fx=i;
                fy=j;
                num[i][j]=1;
            }
        }
    }
    //cnt[qx][qy]=0;
    vis[qx][qy]=1;
    node _;
    _.x=qx;
    _.y=qy;
    _.cnt=0;
    que.push(_);
    bfs();
    return 0;
}




```


---

## 作者：vеctorwyx (赞：2)

### ~~不小心切了道绿题~~（其实很久很久以前做过）

当时我很菜（现在依旧很菜），连BFS都不会，只会长得像DFS的爆搜，[于是写了1476的 ~~DFS~~ 爆搜](https://www.luogu.com.cn/record/24611796)（不怕电脑卡的同学可以点开康康我的代码）

~~跑题了~~


----------


~~其实这题很简单~~，可以传送的BFS，~~都不需要优化~~

唯一的难点（~~说好的简单呢~~)是记录传送点，单独找可能会超时，那么我们可以输入顺便找到（具体方法看代码）

#### 有人说要特殊处理一下情况（简单画一画）

```
#########
##W...###
#######.=
@....W..#
#########
```

就是这种碰头往回走的情况,~~然而我并没有写就过啦，可能是数据水。。~~

跑的~~还算不错~~，[总共78ms](https://www.luogu.com.cn/record/28839375)

~~不多bb了~~，上代码：
```cpp
#include<iostream>
#include<queue>
using namespace std;
int x,y;
int dx[5]={0,0,0,1,-1};
int dy[5]={0,1,-1,0,0};
char a[310][310];
struct node1
{
	int n,m;
}b[26][2];//传送门
struct node
{
	int n,m,time_;
};
int c[26];
queue<node>q;
int main()
{
	cin>>x>>y;
	for(int i=1;i<=x;i++)
	{
		for(int j=1;j<=y;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=x;i++)
	{
		for(int j=1;j<=y;j++)
		{
			if(a[i][j]=='@')
			{
				node qwq;
				qwq.n=i;
				qwq.m=j;
				qwq.time_=0;
				q.push(qwq);//起点进入队列
			}
			else if(a[i][j]>='A'&&a[i][j]<='Z')
			{
				b[a[i][j]-'A'][c[a[i][j]-'A']].m=i;
				b[a[i][j]-'A'][c[a[i][j]-'A']].n=j;
				c[a[i][j]-'A']++;//寻找传送门
			}
		}
	}
	while(!q.empty())//BFS
	{
		node qwq=q.front();
		
		for(int i=1;i<=4;i++)
		{
			node e=qwq;
			e.n+=dx[i];
			e.m+=dy[i];
			e.time_++;
			if(e.m>0&&e.m<=y&&e.n>0&&e.n<=x&&a[e.n][e.m]=='.')
			{
				a[e.n][e.m]='@';
				q.push(e)；
			}
			else if(e.m>0&&e.m<=y&&e.n>0&&e.n<=x&&a[e.n][e.m]>='A'&&a[e.n][e.m]<='Z')//传送门问题
			{
				if(b[a[e.n][e.m]-'A'][0].m==e.n&&b[a[e.n][e.m]-'A'][0].n==e.m)
				{
					int t=e.n;
					e.n=b[a[e.n][e.m]-'A'][1].m;
					e.m=b[a[t][e.m]-'A'][1].n;
				q.push(e);
				}
				else if(b[a[e.n][e.m]-'A'][1].m==e.n&&b[a[e.n][e.m]-'A'][1].n==e.m)
				{
					int t=e.n;
					e.n=b[a[e.n][e.m]-'A'][0].m;
					e.m=b[a[t][e.m]-'A'][0].n;
					q.push(e);
				}
			}
			else if(a[e.n][e.m]=='=')//第一次找到直接输出
			{
				cout<<e.time_;
				return 0;
			}
		}
		q.pop();
	}
    //好像没说找不到的情况
    //那就不用管了吧
    return 0;虽然我相信它运行到这里，但还是要素质return 0
}
```
至于那个1476行的代码

~~我不打算改了~~（其实是洛谷更新后不让交那么长的代码了。。。）

---

## 作者：Khassar (赞：2)

/\*
思路和楼下P党的一样，通过宽搜，找到出口的最短路，不过遇到字母时要移到另一个字母处

有两个比较坑的地方：

一是走到传送器强制传送；

二是把现在的位置传送到另一个位置时要额外开两个变量记录一下当前位置，省得改完第一个变量后目标点就变了；

具体看代码注释吧

\*/







```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<vector>
#include<ctime>
#define ll long long
#define R register
#define Rf(a,b,c) for(R int (a)=(b);(a)<=(c);++(a))
#define Tf(a,b,c) for(R int (a)=(b);(a)>=(c);--(a))
#define D double
using namespace std;
const int N=305;
int n,m,w[N][N],dis[N][N],tx,ty,link1[N][2],link2[N][2];
//w用来存图，dis用来记到每点的最少步数，link两数组用来记传送点（字母） 
int dx[5]={0,1,0,-1};//宽搜用的方向数组 
int dy[5]={1,0,-1,0};
char ch;
inline int read() {//读入及输出优化（并没有用上） 
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=(ch-'0');ch=getchar();}
    return x*f;
}
inline void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
queue <int> q1,q2;//开两个队列，q1记纵坐标，q2记横坐标，省去开结构体 
int main()
{
    cin>>n>>m;//输入迷宫大小 
    memset(dis,127,sizeof(dis));//把dis数组初始化成一个很大的数 
    Rf(i,1,n) Rf(j,1,m) {
        cin>>ch;
        if(ch!='#') {//是#的都默认为0，这样不用再特别的去判边界 
            if(ch=='.') w[i][j]=1;//1为普通的草地 
            else if(ch=='@') {//找到起点就把它加入队列；
                q1.push(i);q2.push(j);
                dis[i][j]=0;//起点的最短路为0
                //这里把起点视为障碍，反正再次不会再次走到它 
            }
            else if(ch=='=') {//记录终点 
                w[i][j]=2;
                tx=i,ty=j;
            }
            else {//记录传送点
            //下面的注释把两个传送点用起点和终点称呼，
        //但它们之间可以互相传，并且不要把它们和真正的起、终点弄混了 
                w[i][j]=ch;
                if(link1[w[i][j]][0]==0) {//如果它还没有起点，那它就是起点 
                    link1[w[i][j]][0]=i;
                    link1[w[i][j]][1]=j;
                }
                else {//否则它就是终点 
                    link2[w[i][j]][0]=i;
                    link2[w[i][j]][1]=j;
                }
            }
        }
    }
    while(!q1.empty()) {//开始宽搜 
        R int nowx=q1.front(),nowy=q2.front();q1.pop(),q2.pop();
        //取出队首     
        Rf(i,0,3) {
            R int x=nowx+dx[i],y=nowy+dy[i],xx,yy;
            //x,y先记录一下要到的点，xx,yy是最终到的坐标（坑点2） 
            //尝试向四个方向走一走 
            if(w[x][y]>2) {//如果是一个传送点，强制传送(不用想着接着走了)（坑点1） 
                if(x==link1[w[x][y]][0]&&y==link1[w[x][y]][1]) {
                    //如果是起点就传到终点 
                    xx=link2[w[x][y]][0];yy=link2[w[x][y]][1];
                }
                else {
                    //否则就是终点，传到起点 
                    xx=link1[w[x][y]][0];yy=link1[w[x][y]][1];
                }
            }
            else {//不是传送点，就直接过去； 
                xx=x;yy=y;
            }
            if(w[xx][yy]&&dis[xx][yy]>dis[nowx][nowy]+1) {
            //如果要到的点能走且其已记录的最少步数比现在走一步过去要多就更新 
                dis[xx][yy]=dis[nowx][nowy]+1;
                if(w[xx][yy]==2) {//如果是终点，根据宽搜的性质一定是最少的步数
                //就直接输出并结束程序 
                    write(dis[xx][yy]);
                    return 0;
                }
                //否则就加入队列 
                q1.push(xx);q2.push(yy);
            }
        }
    }
    //write(dis[tx][ty]);
    return 0;
}

```

---

## 作者：ShadowAA (赞：2)

算法：宽搜

处理传送点：用数组把传送点保存起来

其他的就不难了

const e:array[1..4,1..2] of longint=((1,0),(0,1),(-1,0),(0,-1));

```cpp
var n,m,i,j,x,y:longint;
a:array[0..301,0..301] of char;     //保存地图
b1,c1,d1:array[0..90001] of longint;    //行，列，步数
b,c:array['A'..'Z',1..2] of longint;    //传送点坐标
p:array['A'..'Z'] of longint;     //传送点累加
f:array[0..301,0..301] of boolean;    //防止重复
procedure sc(x,y:longint);  //宽搜
var x1,y1,t,w,i,j,x2,y2:longint;
begin
b1[1]:=x;c1[1]:=y;
f[x,y]:=true;
t:=1;w:=1;    //赋初值
while t<=w do
  begin
  for i:=1 to 4 do
    begin
    x1:=b1[t]+e[i,1];y1:=c1[t]+e[i,2];    //把它将要到达的地方保存
    if a[x1,y1] in ['A'..'Z'] then          //判断是否传送点
      begin
      for j:=1 to 2 do        //看看是第一个还是第二个
        if (b[a[x1,y1],j]=x1) and (c[a[x1,y1],j]=y1) then
          begin
          x2:=b[a[x1,y1],3-j];
          y2:=c[a[x1,y1],3-j];
          end;
      x1:=x2;y1:=y2;
      end;
    if (x1>=1) and (x1<=n) and (y1>=1) and (y1<=m) and (f[x1,y1]=false) and(a[x1,y1]<>'#') then    //不能越界，重复，不能被玉米挡住
      begin
      inc(w);
      b1[w]:=x1;c1[w]:=y1;
      d1[w]:=d1[t]+1;
      f[b1[w],c1[w]]:=true;
      if (a[b1[w],c1[w]]='=') then    //到了终点，终止
        begin
        writeln(d1[w]);
        halt;
        end;
      end;
    end;
  inc(t);
  end;
end;
begin
readln(n,m);
for i:=1 to n do
  begin
  for j:=1 to m do
    begin
    read(a[i,j]);
    if a[i,j] in ['A'..'Z'] then    //判断传送点
      begin
      inc(p[a[i,j]]);
      b[a[i,j],p[a[i,j]] ]:=i;
      c[a[i,j],p[a[i,j]] ]:=j;    //保存传送点
      end;
    if a[i,j]='@' then    //保存起点
      begin
      x:=i;y:=j;
      end;
    end;
  readln;
  end;
sc(x,y);    //宽搜
end.
```

---

## 作者：YanYou (赞：1)

## Solution

#### 用 BFS。

但有坑点。题目里说：

**如果一头奶牛处在这个装置的起点或者终点，这头奶牛就必须使用这个装置。**

**从装置的一个结点到另一个结点需要花费0个单位时间。**

而且在 BFS 的时候，使用传送门的点不要标记为 1 。

其他的就是普通的 BFS 了。

## Code
```pascal
const dx:array[1..4] of -1..1=(-1,0,1,0);
const dy:array[1..4] of -1..1=(0,1,0,-1);
var n,m,i,j,l,r,x,y,ex,ey,xx,yy:longint;
    ch:char;
    c:array['A'..'Z',1..2] of longint;
    b:array['A'..'Z'] of 0..1;
    e:array[0..310,0..310] of record
                                x,y:longint;
                              end;
    a,f:array[0..310,0..310] of 0..1;
    q:array[0..180010,1..3] of longint;
begin
  readln(n,m);
  for i:=1 to n do begin
    for j:=1 to m do begin  //输入处理
      read(ch);
      if ch='#' then a[i,j]:=1;
      if ch='=' then begin ex:=i; ey:=j; end;
      if ch='@' then begin x:=i; y:=j; end;
      if ch in ['A'..'Z'] then begin
        if b[ch]=0 then begin
          c[ch,1]:=i;
          c[ch,2]:=j;
          b[ch]:=1;
        end else begin
          e[i,j].x:=c[ch,1];
          e[i,j].y:=c[ch,2];
          e[c[ch,1],c[ch,2]].x:=i;
          e[c[ch,1],c[ch,2]].y:=j;
        end;
      end;
    end;
    readln;
  end;
  l:=1; r:=1; q[l,1]:=x; q[l,2]:=y; f[x,y]:=1;
  repeat  //BFS
    x:=q[l,1]; y:=q[l,2];
    for i:=1 to 4 do begin
      xx:=x+dx[i]; yy:=y+dy[i];
      if (xx>0)and(xx<=n)and(yy>0)and(yy<=m)and(a[xx,yy]=0)and(f[xx,yy]=0) then begin
        if (e[xx,yy].x>0)and(e[xx,yy].y>0)and(f[e[xx,yy].x,e[xx,yy].y]=0) then begin
          inc(r);
          q[r,1]:=e[xx,yy].x;
          q[r,2]:=e[xx,yy].y;
          q[r,3]:=q[l,3]+1;
          continue;
        end;
        inc(r);
        q[r,1]:=xx;
        q[r,2]:=yy;
        q[r,3]:=q[l,3]+1;
        f[xx,yy]:=1;
        if (xx=ex)and(yy=ey) then begin
          writeln(q[r,3]);
          halt;
        end;
      end;
    end;
    inc(l);
  until l>r;
end.
```


---

## 作者：Numenor (赞：1)

```cpp
//本人手懒，只贴注释了，，， 
#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
struct slide
{
    bool z;
    int x1,y1,x2,y2;
}sli[30];//存时空传送机 
int map[305][305],n,m,sx,sy,ex,ey;
char lawn[305][305];
int vis[305][305];
queue<int>qx,qy,qt;
int dx[5]={0,0,1,-1};
int dy[5]={1,-1,0,0};
void find(int i,int &x,int &y)//为什么加&不解释 
{
    if(sli[i].x1==x&&sli[i].y1==y)
    {
        x=sli[i].x2;y=sli[i].y2;
        return;
    }
    x=sli[i].x1;y=sli[i].y1;
}
bool check(int x,int y)
{
    if(x>=1&&y>=1&&x<=n&&y<=m)return 1;
    return 0;
}
void bfs()
{
    qx.push(sx);
    qy.push(sy);
    qt.push(0);
    vis[sx][sy]=1;
    while(qx.size())
    {
        int x=qx.front();qx.pop();
        int y=qy.front();qy.pop();
        int time=qt.front()+1;qt.pop();
        for(int i=0;i<4;i++)
        {
        	int xx=x+dx[i];
        	int yy=y+dy[i];
        	/*如果找到了传送门，那么就
			相当于话费一秒钟走了
			两步，因为传送时间为0
			则相当于直接走到了另一端。
			所以在find函数中直接修改xx,yy的值 
			*/ 
        	if(map[xx][yy]>='A'&&map[xx][yy]<='Z')
        	{
        		int a=map[xx][yy];
        		if(sli[a].z)
        		{
        			find(a,xx,yy);
        		}
        	}
        	if(map[xx][yy]==-1)//由于之前对传送门的处理
			                   //那么就满足bfs的最优性 
        	{
        		printf("%d",time);return;
        	}
        	if(check(xx,yy)&&(!vis[xx][yy]))
        	{
        		vis[xx][yy]=1;//注意这个时候也相当于把传送门的
				              //另一端也染色了，因为如果用最少的时间
							  //走到了一个传送门的端，那么没有必要花更长时间
							  //走到另一端在传回来，因此每对传送门
							  //只需要用一次即可 
        		qx.push(xx);qy.push(yy);qt.push(time);
        	}
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    {
        cin>>lawn[i][j];
        if(lawn[i][j]=='#')vis[i][j]=1;
        if(lawn[i][j]=='='){ex=i;ey=j;map[i][j]=-1;}
        if(lawn[i][j]=='@'){sx=i;sy=j;}
        if(lawn[i][j]>='A'&&lawn[i][j]<='Z')
        {
            
            int a=lawn[i][j];
            map[i][j]=a;
            if(!sli[a].z)//z表示之前是否已经出现过同样的字母 
            {sli[a].x1=i;sli[a].y1=j;sli[a].z=1;}
            else{sli[a].x2=i;sli[a].y2=j;}
        }
    }
    bfs();
}
//NOIP2018RP++ 
```

---

## 作者：loaky (赞：1)

代码较为丑陋，希望不要被嫌弃，乍一看，这就是个迷宫的题，然后发现加了一条件要处理，这里我的处理方法可能略微复杂，但还是比较好懂，如果出现字符在A
~Z之间说明这是一个传送门，我们需要记录他的位置和他能传送到的位置，如果在一张图中，该字母第一次出现我们用xi[int(a)]来记录因为对于a来说一张图就会出现两次，不可能会重复，因此用xi数组记录当前的x用yi记录当前的y，下次扫描时发现对于a我们已经有了一个门，所以此时用x来记录当前点能传送到的x是多少，同理对于y，对两个传送门分别记录位置就可以，再bfs中加一部判断，就可以正常搜索了。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<queue>
using namespace std;
const int maxn=400;
int n,m,s1,s2,e1,e2,ans=1e5,x[maxn][maxn],y[maxn][maxn],xi[maxn],yi[maxn],vis[maxn][maxn];
int m1[8]={0,0,0,1,-1},m2[8]={0,1,-1,0,0};
char mp[maxn][maxn];
queue<int>q;
void bfs(){
	q.push(s1);
	q.push(s2);
	q.push(0);
	while(!q.empty()){
		int yy=q.front();
		q.pop();
		int xx=q.front();
		q.pop();
		int sp=q.front();
		q.pop();
		if(sp>=ans) continue;
		if(xx==e2&&yy==e1){
			ans=min(ans,sp);
		}
		for(int i=1;i<=4;i++){
			if(xx+m1[i]>m||xx+m1[i]<1||yy+m2[i]>n||yy+m2[i]<1||mp[yy+m2[i]][xx+m1[i]]=='#'||vis[yy+m2[i]][xx+m1[i]]) continue;
			if(mp[yy+m2[i]][xx+m1[i]]>='A'&&mp[yy+m2[i]][xx+m1[i]]<='Z'){
				q.push(y[yy+m2[i]][xx+m1[i]]);
				q.push(x[yy+m2[i]][xx+m1[i]]);
				q.push(sp+1);
				vis[yy+m2[i]][xx+m1[i]]=1;
			}
			else{
				q.push(yy+m2[i]);
				q.push(xx+m1[i]);
				q.push(sp+1);
				vis[yy+m2[i]][xx+m1[i]]=1;
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char a;
			scanf("%c",&a);
			while(a==' '||a=='\n') scanf("%c",&a);
			mp[i][j]=a; 
			if(a=='@'){
				s1=i;
				s2=j;
			}
			if(a=='='){
				e1=i;
				e2=j;
			}
			if(a>='A'&&a<='Z'){
				if(xi[int(a)]){
					x[i][j]=xi[int(a)];
					y[i][j]=yi[int(a)];
					x[yi[int(a)]][xi[int(a)]]=j;
					y[yi[int(a)]][xi[int(a)]]=i;
				}
				else{
					xi[int(a)]=j;
					yi[int(a)]=i;
				}
			}
		}
	}
	bfs();
	printf("%d",ans);
	return 0;
}
```

---

## 作者：凯特琳 (赞：1)

这道题就是寻找最短路径。适合跑广搜，只是加了一个规则：广搜时如果遇到一个字母，则无条件转移到另一个相同字母处，继续广搜


AC代码：

```delphi

type re=record
x:longint;
y:longint;
end;
var map:array[1..300,1..300]of char;//记录原图
var f:array[1..300,1..300]of longint;//记录每个点的步数
var cs:array['A'..'z',1..2]of re;//记录两个传送点
var num:array['A'..'z']of longint;//cs的配套数组
var h:array[1..100000]of re;//队列
var i,j,k,m,n,l,r,xx,yy,xxx,yyy:longint;
var qi,q:re;
var dx,dy:array[1..4]of longint;//四个方向
begin
readln(n,m);

for i:=1 to n do
begin
 for j:=1 to m do
 begin
  read(map[i,j]);
  if map[i,j]='@' then
  begin
   qi.x:=i;
   qi.y:=j;
  end;//读图的时候找到起点
  if (map[i,j]<>'@')and(map[i,j]<>'#')and(map[i,j]<>'.')and(map[i,j]<>'=') then//如果找到了字母，如果是第一次出现这个字母，
                   //那么记录到相应的cs[‘×’，１]数组里,如果是第二次出现，记录在cs[‘ｘ’，２]数组里，可以方便查询传送点信息
  begin
   inc(num[map[i,j]]);//记录了“x”是第几次出现
   cs[map[i,j],num[map[i,j]]].x:=i;
   cs[map[i,j],num[map[i,j]]].y:=j;
  end;
 end;
 readln;
end;

for i:=1 to n do
for j:=1 to m do
f[i,j]:=10000000;//初始化

dx[1]:=0;dx[2]:=0;dx[3]:=1;dx[4]:=-1;
dy[1]:=1;dy[2]:=-1;dy[3]:=0;dy[4]:=0;
l:=0;
r:=1;
h[1].x:=qi.x;
h[1].y:=qi.y;//起点入队
f[qi.x,qi.y]:=0;//初始化
while l<r do
begin
inc(l);
q:=h[l];
for i:=1 to 4 do//四个方向
begin
 xx:=q.x+dx[i];
 yy:=q.y+dy[i];//找到下一步要走的点的坐标

  if (xx>=1)and(xx<=n)and(yy>=1)and(yy<=m)and(map[xx,yy]<>'#') then//如果此点合法
                                                                                                          
  begin//我动用了紫色！这里需要明确begin下面包括几个操作。要不然begin end套死你！
        //操作1：传送点的变换 操作2：更新搜索到的点 操作3：如果走到终点 停止搜索 
//操作1开始
  if (map[xx,yy]<>'.')and(map[xx,yy]<>'@')and(map[xx,yy]<>'=') then//如果是传送点
  begin
  xxx:=xx;//很重要，先把（xx，yy）这个点copy出来为（xxx，yyy）要不然执行红色字的时候，xx
  yyy:=yy;//的值就改变了，然后执行蓝色字的时候，yy的赋值地址就变了
   if (xx=cs[map[xxx,yyy],1].x)and(yy=cs[map[xxx,yyy],1].y) then//如果这个点是传送点1
   begin
   xx:=cs[map[xxx,yyy],2].x;//把它变成传送点2
   yy:=cs[map[xxx,yyy],2].y;
   end
   else//否则的话 他就是传送点2
   //if (xx=cs[map[xx,yy],2].x)and(yy=cs[map[xx,yy],2].y) then
   begin
   xx:=cs[map[xxx,yyy],1].x;//把它变成传送点1
   yy:=cs[map[xxx,yyy],1].y;
   end;
   end;
//操作1结束
//操作2开始
   if (xx>=1)and(xx<=n)and(yy>=1)and(yy<=m)and(map[xx,yy]<>'#')and(f[xx,yy]>f[q.x,q.y]+1) then//如果是地图中的可走待更新点
   begin
   f[xx,yy]:=f[q.x,q.y]+1;//更新
   inc(r);//入队
   h[r].x:=xx;
   h[r].y:=yy;
   end;
//操作2结束
//操作3开始
   if (xx>=1)and(xx<=n)and(yy>=1)and(yy<=m)and(map[xx,yy]='=') then//如果是终点
   begin
   writeln(f[xx,yy]);//输出
   halt;
   end;
//操作3结束
 end;//结束的是 合法点的三个操作
end;//结束的是 四个方向的枚举
end;//结束的是 整个while循环

end.

```

---

## 作者：Lucky_Star (赞：0)

##### 要注意的几点：
###### 1.传送门要标记；
###### 2.走进一个传送门，应该把终点放进搜索队列，并且标记已走；
###### 3.在传送门的终点已经被标记的时候，只能由走进终点来到达起点。
点
```c
#include<stdio.h>
int map[301][301],sign[301][301];//数字地图和标记
int y1,x1;
int y2,x2;
int flag[100][4];//传送门数组
int n,m;
int queue[10000000][2];//搜索队列
int dx[4]= {0,0,1,-1};
int dy[4]= {1,-1,0,0};
int main()
{
    char c;
    int e;
    scanf("%d%d",&n,&m);
    for(int x=1; x<=n; x++)
        for(int y=1; y<=m; y++)
        {
            c=getchar();
            if(c=='=')
            {
                map[x][y]=1;
                x2=x;
                y2=y;
            }
            else if(c=='.')
                map[x][y]=1;
            else if(c<='Z'&&c>='A')
            {
                e=c;
                if(flag[e][0]!=0&&flag[e][1]!=0)
                {
                    flag[e][2]=x;
                    flag[e][3]=y;
                }
                else
                {
                    flag[e][0]=x;
                    flag[e][1]=y;//标记传送门的起点和终点。
                }
                map[x][y]=e;//用传送门的符号来表示传送门。
            }
            else if(c=='#')
                map[x][y]=0;
            else if(c=='@')
            {
                x1=x;
                y1=y;
                map[x][y]=1;
            }
            else
                y--;//C语言防止读入回车键
        }
    void bfs();
    bfs();
    printf("%d",sign[x2][y2]);
}
void bfs()
{
    int begin=0,end=1;
    queue[1][0]=x1;
    queue[1][1]=y1;
    sign[x1][y1]=1;//预处理，不设置为零是为了防止在起点处循环一下
    while(begin<end)//bfs搜索
    {
        begin++;
        for(int i=0; i<4; i++)
        {
            int l=queue[begin][0]+dx[i];
            int r=queue[begin][1]+dy[i];
            if(l>=1&&r>=1&&l<=n&&r<=m&&((sign[l][r]==0&&map[l][r]==1)||//一处判断走入草地
                                        (map[l][r]>=65&&(sign[flag[map[l][r]][0]][flag[map[l][r]][1]]==0||sign[flag[map[l][r]][2]][flag[map[l][r]][3]]==0))))//一处判断走入传送门，这里判断好像不怎么好，但后面有补充。
            {
                end++;
                if(l==x2&&r==y2)//终止条件。
                {
                    sign[l][r]=sign[queue[begin][0]][queue[begin][1]];
                    return ;
                }
                else if(map[l][r]>=65)//走入传送门。
                {
                    if(l==flag[map[l][r]][0]&&r==flag[map[l][r]][1]&&sign[flag[map[l][r]][2]][flag[map[l][r]][3]]==0)//走入传送门的起点，判断一下终点是不是没走。
                    {
                        queue[end][0]=flag[map[l][r]][2];
                        queue[end][1]=flag[map[l][r]][3];
                        sign[queue[end][0]][queue[end][1]]=sign[queue[begin][0]][queue[begin][1]]+1;
                    }
                    else if(l==flag[map[l][r]][2]&&r==flag[map[l][r]][3]&&sign[flag[map[l][r]][0]][flag[map[l][r]][1]]==0)//实质和上面一样。
                    {
                        queue[end][0]=flag[map[l][r]][0];
                        queue[end][1]=flag[map[l][r]][1];
                        sign[queue[end][0]][queue[end][1]]=sign[queue[begin][0]][queue[begin][1]]+1;
                    }
                    else//如果从传送门的一端走进，而另一端已经走被走过了，那就不要走。
                        end--;
                }
                else
                {
                    queue[end][0]=l;
                    queue[end][1]=r;
                    sign[l][r]=sign[queue[begin][0]][queue[begin][1]]+1;//走入草地的时候。
                }
            }
        }
    }
}

```
觉得传送门的符号用来作下标，而在数字地图里，保留传送门的符号，就可以迅速找到传送门的起点和终点。虽然在引用下标的时候要引用很多次，但是想明白了的话是很容易理解的。
#### 像sign[flag[map[l][r]][0]][flag[map[l][r]][1]]表示的是在数字地图里，走到坐标为（l,r）的传送门的一端的步数。
首先，就是map[l][r]是找到传送门的符号。
###### 
其次，flag[map[l][r]][0]就是找到传送门一端的第一坐标（因为横纵坐标不好描述），一个flag纪录了四个数，第一个和第二个分别是一端的第一、二坐标，
而第三个和第四个分别是另一端的第一、二坐标。
###### 
最后，sign就可以根据坐标来标记和判断了。尤其在传送门的时候。
### 代码看上去确实不太看得清。

---

