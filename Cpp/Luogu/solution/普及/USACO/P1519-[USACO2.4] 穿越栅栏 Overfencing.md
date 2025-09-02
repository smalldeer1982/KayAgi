# [USACO2.4] 穿越栅栏 Overfencing

## 题目描述

Farmer John 在外面的田野上搭建了一个巨大的用栅栏围成的迷宫。幸运的是，他在迷宫的边界上留出了两段栅栏作为迷宫的出口。更幸运的是，他所建造的迷宫是一个“完美的”迷宫：即你能从迷宫中的任意一点找到一条走出迷宫的路。

给定迷宫的宽度 $W$（$1 \leq W \leq 38$）及高度 $H$（$1 \leq H \leq 100$）。$2 \times H+1$ 行，每行 $2 \times W+1$ 的字符以下面给出的格式表示一个迷宫。然后计算从迷宫中最“糟糕”的那一个点走出迷宫所需的步数（即使从这一点以最优的方式走向最靠近的出口，它仍然需要最多的步数）。

当然了，牛们只会水平或垂直地在 X 或 Y 轴上移动，他们从来不走对角线。每移动到一个新的方格算作一步（包括移出迷宫的那一步）。

这是一个 $W=5,H=3$ 的迷宫：

```plain
+-+-+-+-+-+
|         |
+-+ +-+ + +
|     | | |
+ +-+-+ + +
| |     |  
+-+ +-+-+-+
```
如上图的例子，栅栏的柱子只出现在奇数行或奇数列。每个迷宫只有两个出口。

## 说明/提示

翻译来自NOCOW

USACO 2.4


## 样例 #1

### 输入

```
5 3
+-+-+-+-+-+
|         |
+-+ +-+ + +
|     | | |
+ +-+-+ + +
| |     |  
+-+ +-+-+-+```

### 输出

```
9
```

# 题解

## 作者：奔波儿霸 (赞：32)

#### 题目大意

按照字符画的形式给定一个地图，这个地图有两个出口，现在你需要求出从所有的点到任意一个出口的距离中的最短路径的最大值

#### 吐槽大会

这道搜索题，真恶心。我调了俩小时。。。。。。~~丧尽天良~~

#### 解题思路

从数据范围来看的话，从每个点都搜一遍最短距离是不现实的了。

当然不排除你写的很好看QwQ。

我的想法是将两个出口找出来，然后跑两边BFS，每个点都维护一个距离的最小值

要注意分类讨论从出口往别的格子跳和从普通格子跳往普通格子。

跑的还挺快，空间消耗也不大。我排在最优解的第二页QwQ

#### 巨坑所在

你以为这样就完了吗，你就能轻易AC吗？

显然是不能的，这个题还有四个不易发现的坑点，要不我怎么会调那么久呢？

- 从出口往里跳的时候只能挑一格。

- 从别的格子跳往其他格子的时候只能跳两格

- 跳两格的时候还必须判断中间隔过去的一格是不是空格

- 输入格式也很恶心，在要求读空格的前提下好的办法只有gets，但是用gets会把两个整数后面的回车读进去。

#### 附上代码

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>

const int INF = 2147483647;

using namespace std;

int n, m, sx[3], sy[3], cnt, ans;
char map[208][90];
int dis[208][90];
int dx[5] = {0, 2, 0, -2};
int dy[5] = {2, 0, -2, 0};

int rx[5] = {0, 1, 0, -1};
int ry[5] = {1, 0, -1, 0};
struct node {
    int x, y, sum;
}temp, now;
queue<node> Q;
bool vis[208][90];

inline void BFS(int num) {
    memset(vis, 0, sizeof(vis));
    while (!Q.empty()) Q.pop();
    vis[sx[num]][sy[num]] = 1;
    temp.sum = 0, temp.x = sx[num], temp.y = sy[num];
    Q.push(temp);
    while (!Q.empty()) {
        now = Q.front();
        int x = now.x, y = now.y, s = now.sum;
        Q.pop();
        dis[x][y] = min(s, dis[x][y]);
        for(int i=0; i<4; i++) {
            int xx = dx[i]+x, yy = dy[i]+y;
            int zx = rx[i]+x, zy = ry[i]+y;
            if(!vis[xx][yy] && map[xx][yy] == ' ' && xx <= 2*n+1 && xx > 0 && yy <= 2*m+1 && yy > 0 && map[zx][zy] == ' ' && (x != sx[num] || y != sy[num])) {
                vis[xx][yy] = 1;
                temp.x = xx, temp.y = yy, temp.sum = s+1;
                Q.push(temp);
            }
            if(!vis[zx][zy] && map[zx][zy] == ' ' && x == sx[num] && y == sy[num] && zx <= 2*n+1 && zy <= 2*m+1 && zx > 0 && zy > 0) {
                vis[zx][zy] = 1;
                temp.x = zx, temp.y = zy, temp.sum = s+1;
                Q.push(temp);
            }
        }
    }
}

int main() {
    scanf("%d%d", &m, &n);
    for(int i=1; i<=2*n+1; i++) {
        for(int j=1; j<=2*m+1; j++) {
            dis[i][j] = INF;
        }
    }
    gets(map[0]);
    for(int i=1; i<=2*n+1; i++) {
        gets(map[i]+1);
        for(int j=1; j<=2*m+1; j++) {
            if(i == 1 || j == 1 || i == 2*n+1 || j == 2*m+1)
                if(map[i][j] == ' ') {
                    sx[++cnt] = i;
                    sy[cnt] = j;
                }
        }
    }
    BFS(1);
    BFS(2);
    for(int i=1; i<=2*n+1; i++) {
        for(int j=1; j<=2*m+1; j++) {
            if(dis[i][j] != INF)
                ans = max(ans, dis[i][j]);
        }
    }
    printf("%d", ans);
}
```

管理大大求求您给我个通过吧
![](https://i.loli.net/2018/08/03/5b642ebf1a2d6.jpg)

---

## 作者：Manjusaka丶梦寒 (赞：15)

讲解会比较长：建议去[这里](https://www.cnblogs.com/rmy020718/p/9297006.html)查看

刚读完题，感觉挺简单啊，不过研究了一下样例，一脸懵逼，这咋可能？。

经过机房某位 S型 dalao(son)的解读，哦，so ga si nei，吆西吆西，interisting！！！

再次就借花献佛了。

关于的理解题意：
为了便于理解，这里稍微修改一下题目。

奇数行的栅栏（就是由‘+’和‘-’号组成）将其看做一层类似膜结构，一层防护膜(没有厚度)，穿越不占距离。

然后看偶数列，这里需要将偶数列和其两侧的‘-’看做一个整体，亦可以理解为忽略偶数列，只考虑奇数列。

这里拿样例图解：
![](https://images2018.cnblogs.com/blog/1376345/201807/1376345-20180711215609680-1438269407.png)

结合上图，对题意理解就没什么问题了。

解题剖析：
### ## 1.读入含空格矩阵：

想了半天，试了多种输入方法，最终貌似只有getline(:不会用戳我啊)可以用。

但是在输入时，需要多输入一行，并且第一行和第二行会重复，其他没毛病，最后貌似没啥大碍。
```cpp
    scanf("%d%d",&w,&h);
    w=w*2+1;h=h*2+1;
    for(int i=1;i<=h+1;i++)getline(cin,a[i]);
```
读入是这样的，若有某位dalao明白以上出现的情况，希望讨论区不吝赐教。

### 2.字符矩阵转换数字矩阵

在这里定义一个int型map数组。

map[i][j]表示走到这个点需要消耗的距离(偶数行为0，奇数行有空地的话消耗为1)

在字符矩阵中[i][j]这个点为栅栏，不能走，将map[i][j]定义为2.

注意前边说到，输入字符时会有一行多余，所以在转换时处理一下。

此部分代码为：
```cpp
for(int i=2;i<=h+1;i++)
        for(int j=0;j<w;j++)
        {
            
            if(a[i][j]==32)
            {
                if((i-1)%2==1)map[i-1][j+1]=0;
                else if((j+1)%2==0)map[i-1][j+1]=1;
                else map[i-1][j+1]=0;
            }
            else map[i-1][j+1]=2;
        }
```
### 3.初始化：

ans[i][j]数组记录走到 i,j这个点到出口的最近距离，栅栏处直接定义为-1。
```cpp
void initial()
{
    for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++)
            if(map[i][j]==2)ans[i][j]=-1;
            else ans[i][j]=214748364;
}
```
### 4.找出出口：

这没啥好说的，四个边找出口(注意经以上过程出口可能为0，可能为1)。
```cpp
    for(int i=1;i<=w;i++)if(map[1][i]==0||map[1][i]==1)bfs(1,i);
    for(int i=1;i<=w;i++)if(map[h][i]==0||map[h][i]==1)bfs(h,i);
    for(int i=1;i<=h;i++)if(map[i][1]==0||map[i][1]==1)bfs(i,1);
    for(int i=1;i<=h;i++)if(map[i][w]==0||map[i][w]==1)bfs(i,w);
```
### 5.大搜索

已经处理处每一格的消耗距离，在搜索时，加上就好啦。

两个出口，需要搜索两边所以搜完注意初始化，bool型数组。
```cpp
bool vis[N][M];
struct ahah{
    int x,y;
}str,cur;
queue <ahah> que;
void bfs(int x,int y)
{
    ans[x][y]=0;
    vis[x][y]=1;
    str.x=x;str.y=y;
    que.push(str);
    while(!que.empty())
    {
        cur=que.front();
        que.pop() ;
        for(int i=0;i<4;i++)
        {
            str.x=cur.x+dx[i];
            str.y=cur.y+dy[i];
            if(map[str.x][str.y]!=2&&str.x>=1&&str.x<=h
            &&str.y>=1&&str.y<=w&&!vis[str.x][str.y])
            {
                ans[str.x][str.y]=min(ans[cur.x][cur.y]+map[str.x][str.y],ans[str.x][str.y]);
                            
                vis[str.x][str.y]=1;
                que.push(str); 
            }
        }
    } 
    memset(vis,0,sizeof(vis));
}
```
### 6.找出最大值

将ans数组循环一遍，找出最大值，输出即可。

### 完整代码：
```cpp
/*.........................
作者：Manjusaka
时间：2018/7/11
题目：P1519 Overfencing
..........................*/

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue> 
using namespace std;
#define N int(100)
#define M int(210)
int dx[5]={0,0,1,-1},dy[5]={1,-1,0,0};
string a[N];
int w,h,MAX;
int x[4],y[4],k;
int map[N][M];
int ans[N][M];
void check();
void _scanf();
void initial();
void bfs(int ,int );
void _scanf()
{
    scanf("%d%d",&w,&h);
    w=w*2+1;h=h*2+1;
    for(int i=1;i<=h+1;i++)getline(cin,a[i]);
    for(int i=2;i<=h+1;i++)
        for(int j=0;j<w;j++)
        {
            
            if(a[i][j]==32)
            {
                if((i-1)%2==1)map[i-1][j+1]=0;
                else if((j+1)%2==0)map[i-1][j+1]=1;
                else map[i-1][j+1]=0;
            }
            else map[i-1][j+1]=2;
        }
//    cout<<"\n";for(int i=1;i<=h;i++){for(int j=1;j<=w;j++){cout<<map[i][j];}cout<<endl;}
    check();
}
void check()
{
    initial();    
    for(int i=1;i<=w;i++)if(map[1][i]==0||map[1][i]==1)bfs(1,i);
    for(int i=1;i<=w;i++)if(map[h][i]==0||map[h][i]==1)bfs(h,i);
    for(int i=1;i<=h;i++)if(map[i][1]==0||map[i][1]==1)bfs(i,1);
    for(int i=1;i<=h;i++)if(map[i][w]==0||map[i][w]==1)bfs(i,w);
    for(int i=1;i<=h;i++)
    {
        cout<<"\n";
        for(int j=1;j<=w;j++)
        {
            printf("%3d",ans[i][j]);
        }
    }
}
void initial()
{
    for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++)
            if(map[i][j]==2)ans[i][j]=-1;
            else ans[i][j]=214748364;
}
bool vis[N][M];
struct ahah{
    int x,y;
}str,cur;
queue <ahah> que;
void bfs(int x,int y)
{
    ans[x][y]=0;
    vis[x][y]=1;
    str.x=x;str.y=y;
    que.push(str);
    while(!que.empty())
    {
        cur=que.front();
        que.pop() ;
        for(int i=0;i<4;i++)
        {
            str.x=cur.x+dx[i];
            str.y=cur.y+dy[i];
            if(map[str.x][str.y]!=2&&str.x>=1&&str.x<=h
            &&str.y>=1&&str.y<=w&&!vis[str.x][str.y])
            {
                ans[str.x][str.y]=min(ans[cur.x][cur.y]+map[str.x][str.y],ans[str.x][str.y]);
                            
                vis[str.x][str.y]=1;
                que.push(str); 
            }
        }
    } 
    memset(vis,0,sizeof(vis));
}
void _printf()
{
    for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++)
            MAX=max(MAX,ans[i][j]);
    printf("\n%d",MAX);
}
int main()
{
    _scanf();
    _printf();
}
```


---

## 作者：「QQ红包」 (赞：10)

题解by：redbag


原题解地址：http://redbag.duapp.com/?p=1361


我的博客：http://redbag.duapp.com/


欢迎来踩!


读入有点坑。我选择全部读进来，然后存，如图所示：


１１１１１１１１１１１

１０００００００００１

１１１０１１１０１０１

１０００００１０１０１

１０１１１１１０１０１

１０１０００００１００

１１１０１１１１１１１


我们把图以外的部分全都标记为墙，那么，门的周围则只有一个方向有路。


0代表格子？


不不不，如过0代表各自的话，格子就多很多。


不难发现，真正的格子横坐标与纵坐标都是偶数。这样就很好处理了，每次横坐标纵坐标移动2步。


把出口入队很不方便啊，于是我们就将离出口最近的格子入队。也就是图中&所示


１１１１１１１１１１１

１０００００００００１

１１１０１１１０１０１

１０００００１０１０１

１０１１１１１０１０１

１０１& ００００１& ０

１１１０１１１１１１１


然后就开始灌水了。


其实还是很快的


Executing...


Test 1: TEST OK [0.000 secs, 6104 KB]

Test 2: TEST OK [0.000 secs, 6104 KB]

Test 3: TEST OK [0.000 secs, 6104 KB]

Test 4: TEST OK [0.000 secs, 6104 KB]

Test 5: TEST OK [0.000 secs, 6104 KB]

Test 6: TEST OK [0.000 secs, 6104 KB]

Test 7: TEST OK [0.011 secs, 6104 KB]

Test 8: TEST OK [0.000 secs, 6104 KB]

Test 9: TEST OK [0.000 secs, 6104 KB]

Test 10: TEST OK [0.000 secs, 6104 KB]


All tests OK.


以下程序有很多没用的东西，可以删掉提交试试23333。

```cpp
/*
ID: ylx14271
PROG: maze1
LANG: C++     
*/
#include<set>  
#include<map>  
#include<list>
#include<queue>
#include<stack>
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>
#include<sstream>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#define LL unsigned long long
using namespace std;
int m,n,mm,i,j,k,ss,l,r;//mm:max
int a[310][310];//存地图，1代表墙， 
int f[310][310]={0};//标记用 
int dx[5]={0,-2,2,0,0};//上下左右 
int dy[5]={0,0,0,-2,2};
int ddx[5]={0,-1,1,0,0};//上下左右 
int ddy[5]={0,0,0,-1,1};
struct he
{
    int x,y;
    int t;//步数 
}d[100000]; 
char x[500];
int main() 
{
    freopen("maze1.in","r",stdin);
    freopen("maze1.out","w",stdout);
    cin>>m>>n;
    cin.getline(x,500);
    ss=n*m;//格子数量 
    m=m*2+1;
    n=n*2+1;
    for (i=0;i<=n+3;i++)
    {
        for (j=0;j<=m+3;j++)
            a[i][j]=1;//初始化 
    }
    for (i=1;i<=n;i++)
    {
        char c[500];
        cin.getline(c,500);//读入 
        for (j=1;j<=m;j++)
        {
            if (c[j-1]!='+'&&c[j-1]!='-'&&c[j-1]!='|')//判断 
                a[i][j]=0;//标记不是墙
        }
    }
 
     
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
            f[i][j]=0;//初始化 
             
     
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
        if ((i==1)||(j==1)||(i==n)||(j==m))//在边框上
            if (a[i][j]==0)//是出口
            {//出口的外围赋初值的时候就变成墙了,所以保证只有一边为0 
                for (k=1;k<=4;k++)
                {
                    if ((a[i+ddx[k]][j+ddy[k]]==0)&&//是格子 
                    (i+ddx[k]>=1)&&(i+ddx[k]<=n)&&
                    (j+ddy[k]>=1)&&(j+ddy[k]<=m)&&
                    (f[i+ddx[k]][j+ddy[k]]==0))//没入队 
                    {
                        r++; //入队 
                        d[r].x=i+ddx[k];//坐标 
                        d[r].y=j+ddy[k];
                        d[r].t=1;//步数 
                        f[i+ddx[k]][j+ddy[k]]=1;//标记
                        break;
                    } 
                }
            }
    mm=1; 
    while (l<r)
    {
        l++;
        for (i=1;i<=4;i++)//四个方向 
        {
            if (a[d[l].x+ddx[i]][d[l].y+ddy[i]]==0&&//没墙挡着 
            d[l].x+dx[i]<=n&&d[l].y+dy[i]<=m&&//在范围内 
            d[l].x+dx[i]>=1&&d[l].y+dy[i]>=1&&//在范围内 
            f[d[l].x+dx[i]][d[l].y+dy[i]]==0)//没入队 
                    {
                        r++; //入队 
                        ss--;
                        d[r].x=d[l].x+dx[i];//坐标 
                        d[r].y=d[l].y+dy[i];
                        d[r].t=d[l].t+1;//步数 
                        f[d[r].x][d[r].y]=1;
                        if (d[r].t>mm) mm=d[r].t;//找最大步数 
                    } 
        } 
    }
    printf("%d\n",mm); //输出 
    return 0;
}
```

---

## 作者：Limit (赞：4)

usaco里的搜索其实还是不错的，这自然也不是一道水题（~~其实是我题目看错了~~）
这类题目一般都是一题多解，既然如此垃圾的我自然用bfs

```pascal
const z:array[1..4,1..2]of -1..1=((1,0),(0,1),(-1,0),(0,-1));
var i,j,k:longint;
    a,b:array[0..1000,0..1000]of boolean;
    p:array[0..1000,0..1000]of longint;
    x,y,u:array[0..1010101]of longint;
    m,n,x1,y1,x2,y2,h,t,max:longint;
    ch:char;
procedure bfs(x1,y1:longint);//一个裸的bfs
var h,t,i,j,k:longint;
begin
  h:=1;
  t:=1;
  x[1]:=x1;
  y[1]:=y1;
  b:=a;
  u[1]:=0;
  while h>=t do
  begin
    for i:=1 to 4 do
    if b[x[t]+z[i,1],y[t]+z[i,2]] then
    begin
      inc(h);
      b[x[t]+z[i,1],y[t]+z[i,2]]:=false;
      x[h]:=x[t]+z[i,1];
      y[h]:=y[t]+z[i,2];
      u[h]:=u[t]+1;
      if u[h]<p[x[h],y[h]] then p[x[h],y[h]]:=u[h];//记录最优解，因为有两个出口
    end;
    inc(t);
  end;
end;
begin
  read(n,m);
  readln;//读入麻烦一点
  for i:=1 to m*2+1 do
  begin
    for j:=1 to n*2+1 do
    begin
      read(ch);
      if ch=' ' then
      begin
        a[i,j]:=true;
      end
      else
      begin
        a[i,j]:=false;
      end;
      if (i=1) or (i=m*2+1) or (j=1) or (j=n*2+1) then//在边上
      if ch=' ' then
      begin
        if (x1=0) and (y1=0) then
        begin
          x1:=i;
          y1:=j;
        end
        else
        begin
          x2:=i;
          y2:=j;
        end;
      end;
    end;
    readln;
  end;
  p[x1,y1]:=1;
  p[x2,y2]:=1;
  for i:=1 to m*2+1 do
  for j:=1 to n*2+1 do
  begin
    p[i,j]:=maxlongint;//初值
  end;
  //两个出口
  bfs(x1,y1);
  bfs(x2,y2);
  for i:=2 to m*2 do
  for j:=2 to n*2 do if (p[i,j]>max) and (p[i,j]<>maxlongint) and (i mod 2=0) and (j mod 2=0) then {找最大值}max:=p[i,j];
  write(max div 2+1);//因为记录的是格数不是字符数
end.
```
最后才发现这题难度其实是在读入和处理。~~还是蛮水的~~

---

## 作者：HighPerformanceRobot (赞：3)

#### 吐槽

调了三小时的题目。。~~好吧我都不知道我是第几次调这么长时间了QAQ~~

### 题目大意

给你一个字符串地图，让你求从任意一个出口到迷宫内距出口最长的那个点的距离。

#### 解题思路

每个点都搜暴搜一次最短距离肯定会炸的。那怎么办呢？

我们可以运用反向思维，将两个出口找出来，然后跑两次BFS，更新出口到迷宫内每个点的最短距离，最后最大的就是答案。

还不理解？

那我用常识来帮助你理解一下：

假设从你家到你的学校有1km那么远，那么从你家到你的学校的距离是不是跟从你的学校到你家的距离是一样的，都是1km那么远呢？

同理，迷宫内距出口最远的那个点到出口的距离也就是出口到迷宫内距出口最远的那个点的距离。

但是！

### 坑点来了！

这是个字符串，怎么办？

其实各种办法都可以通用。你直接用字符串当地图也可以，转化成int数组也可以，关键是读入！

读入一个字符串的方法有：

gets，fgets，getline，cin.getline等等。

这里不推荐用gets，原因请自行百度。

但是，注意一个点：如果你读入长和宽的时候用的是cin而不是scanf，那么你就要在读入真正的地图之前多读入一行！

这里又要牵扯到cin跟scanf的区别了：scanf读入完数据后会清掉输入的数据后面的所有空格、Tab和回车，而cin不会。这就造成，你在使用cin的时候，你在长和宽这两个整数后面，还有一个“隐形”的换行符，导致你读入的地图第一行只有一个回车，你说坑不坑？

直接上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int dx[]= {1,-1,0,0},dy[]= {0,0,1,-1};
char x[500];  //读入的字符串，单行读入
int w,h;	//宽和长
int ans,now_long;
int fx[2],fy[2];
int f[210][210];		//记录点到任意一个出口的最短距离
int flag[210][210];		//标记是不是墙
bool arr[210][210];		//标记访问过没有
struct node
{
	int x,y;
} now;
queue <node> que;		//BFS队列
void init()
{
	cin.getline(x,500);	//我用的cin，所以要多加这一行
	for(int i=0; i<210; i++)	//初始化
		fill(f[i],f[i]+210,INT_MAX),fill(flag[i],flag[i]+210,1);
	for(int i=1; i<=h; i++)	//读入和转换
	{
		cin.getline(x,500);
		for(int j=1; j<=w; j++)
			if(x[j-1]==' ')	//是路而不是墙
			{
				flag[i][j]=0;//标记为可以访问
				if((i==1||j==1||i==h||j==w)&&flag[i][j]==0)
					fx[now_long]=i,fy[now_long]=j,f[i][j]=1,now_long++;		//找出口
			}
	}
}
void bfs(int x,int y)
{
	node begin;
	begin.x=x,begin.y=y;
	que.push(begin);
	arr[x][y]=1;
	while(!que.empty())
	{
		node stor=que.front();
		que.pop();
		for(int i=0; i<4; i++)
		{
			int sx=stor.x+dx[i],sy=stor.y+dy[i];
			if(sx>0&&sx<=h&&sy>0&&sy<=w&&flag[sx][sy]==0&&arr[sx][sy]==0)
			{
				arr[sx][sy]=1;
				f[sx][sy]=min(f[sx][sy],f[stor.x][stor.y]+1);
				now.x=sx,now.y=sy;
				que.push(now);
			}
		}
	}
}
int main()
{
//	freopen("maze1.in","r",stdin);
//	freopen("maze1.out","w",stdout);
	ios::sync_with_stdio(0);
	cin>>w>>h;
	w=2*w+1,h=2*h+1;
	init();		//读入+初始化，这样弄个函数主要是方便调试
	for(int i=0; i<now_long; i++)
	{
		bfs(fx[i],fy[i]);
		for(int j=0; j<210; j++)
			fill(arr[j],arr[j]+210,0);	//注意：这里要重新初始化！否则就会WA！
	}
	for(int i=1; i<=h; i++)
		for(int j=1; j<=w; j++)
			if(f[i][j]<INT_MAX)		//被更新过，因为初值是INT_MAX
				ans=max(ans,f[i][j]);
	cout<<ans/2<<endl;		//这个就自己去想为什么吧，凭各位大佬聪明的脑袋瓜应该不难
	return 0;
}
```

---

## 作者：撤云 (赞：3)

```cpp
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
using namespace std;
int h,w,js=1,ans=0;
char a[500][500];
int bj[3],b[3],dj[10000],dj1[10000],dj2[10000];
int f[500][500],n,m;
bool l[500][500];
int fx[10]= {0,0,0,1,-1};
int fy[10]= {0,1,-1,0,0};
int bfs(int x,int y) {
    int head=0,tail=1;
    dj[1]=x;
    dj1[1]=y;
    dj2[1]=0;
    do {
        head++;
        for(int i=1; i<=4; i++) {
            x=dj[head]+fx[i];
            y=dj1[head]+fy[i];
            if(a[x][y]==' '&&x>0&&x<=n&&y>0&&y<=m&&l[x][y]==0) {//判断这点是不是在迷宫里面或为不为空格
                tail++;
                f[x][y]=min(f[x][y],dj2[head]+1);//坐标为(x,y)的点到迷宫的最短路径
                dj[tail]=x;
                dj1[tail]=y;
                dj2[tail]=dj2[head]+1;
                l[x][y]=1;//标记坐标为(x,y)的点
            }
        }
    } while(head<tail);//当头<尾时循环
}
int main() {
    for(int i=1; i<=500; i++)
        for(int j=1; j<=500; j++)
            f[i][j]=10000;//把f数组赋一个很大的值
    cin>>w>>h;//输入
    char c;
    n=2*h+1;
    m=2*w+2;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            do scanf("%c",&a[i][j]);
            while(a[i][j]=='\n');
            if((i==1||j==2||i==n||j==m)&&a[i][j]==' ') {//寻找迷宫出口
                b[js]=i;//标记出口的坐标i
                bj[js]=j;//标记出口的坐标j
                js++;
            }
        }
    }
    int ja=0;
    for(int i=1; i<js; i++) {//枚举迷宫出口
        memset(l,0,sizeof(l));//把l数组清空
        bfs(b[i],bj[i]);//开始搜索
    }
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            if(f[i][j]!=10000)
                ja=max(f[i][j],ja);
    cout<<(ja+1)/2;
    return 0;
}
```

---

## 作者：lenaalyth (赞：2)

双换行双换行双换行双换行双换行双换行双换行。。。。这是这道题的重点。。。。
很简单的bfs裸题。。和楼上说的一样，用两个起点作为开头bfs求最短点，不过有几点要注意：
1：两次bfs可能会导致的覆盖问题。
2：因为图的问题，最后的输出要加一除二，因为移动两次才算一步，而最后的一个移动一步算一次。
3.可能是我电脑的问题？他的后面如果全是空格的话会不输入，注意补全。
接下来上代码。。我的命名不可能这么恶心。。。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
using namespace std;
int m,x,h,n,cx,cy,ans=0;
char p[222][222],v;
int bj1[210][210],l,k,j,g,f[210][210],s[4][2]= {1,0,-1,0,0,1,0,-1},bj2[210][210],xx[2],yy[2],qqq;
typedef struct
{
    int x,y;
} fhs;
fhs a,b,c,d,e;
queue<fhs> ll;
int bfs(int x,int y,int z)
{
    b.x=x;
    b.y=y;
    if(z==1)
    {
        ll.push(b);
        while(!ll.empty())
        {
            c.x=ll.front().x;
            c.y=ll.front().y;
            ll.pop();
            for(int x1=0; x1<4; x1++)
            {
                int cx=c.x+s[x1][0];
                int cy=c.y+s[x1][1];
                if(cx>0&&cx<(2*m)&&cy>0&&cy<2*n&&p[cx][cy]==' '&&bj1[cx][cy]==0)
                {
                    bj1[cx][cy]=1;
                    f[cx][cy]=min(f[cx][cy],f[c.x][c.y]+1);
                    d.x=cx;
                    d.y=cy;
                    ll.push(d);
                }
            }
        }
    }
    if(z==2)
    {
        ll.push(b);
        while(!ll.empty())
        {
            c.x=ll.front().x;
            c.y=ll.front().y;
            ll.pop();
            for(int x1=0; x1<4; x1++)
            {
                int cx=c.x+s[x1][0];
                int cy=c.y+s[x1][1];
                if(cx>0&&cx<(2*m)&&cy>0&&cy<2*n&&p[cx][cy]==' '&&bj2[cx][cy]==0)
                {
                    bj2[cx][cy]=1;
                    f[cx][cy]=min(f[cx][cy],f[c.x][c.y]+1);
                    d.x=cx;
                    d.y=cy;
                    ll.push(d);
                }
            }
        }
    }
}
int main()
{
    for(int x=0; x<210; x++)
        for(int y=0; y<210; y++)
        {
            f[x][y]=10000000;

        }
    cin>>n>>m;
    getchar();
    getchar();//这个getchar（）让我找了一个小时。。。。。。双换行！
    for(int x=0; x<(2*m)+1; x++)
    {
        gets(p[x]);
        int ppp=strlen(p[x]);
        if(ppp!=2*n+1)
        {
            for(int z=ppp; z<2*n+1; z++)
            {
                p[x][z]=' ';
            }
            ppp=2*n+1;
            p[x][ppp]=0;
        }
        for(int y=0; y<ppp; y++)
        {
            if((x==0||y==0||x==2*m||y==ppp-1)&&p[x][y]==' ')
            {
                xx[qqq]=x;
                yy[qqq]=y;
                f[x][y]=0;
                qqq++;
            }
        }
    }
    for(int x=1; x<=qqq; x++)
    {
        bfs(xx[x-1],yy[x-1],x);
    }
    for(int x=1; x<2*m; x++)
        for(int y=1; y<2*n; y++)
        {
            if(f[x][y]<11000)
            {
                ans=max(ans,f[x][y]);
            }
        }
    cout<<(ans+1)/2<<endl;
}

```

---

## 作者：liaohaoping (赞：2)

很裸的宽搜题，其实不需要搜两次，以两个出口同时作为起点搜一遍就行了，搜到的最后一个点就是最远的。

另外注意一下这里是先输入宽度（~~mmp坑我好久~~），还有输入的一些细节即可（具体见代码）。

**注意Linux环境下里面的换行为\r\n**,即输入时判断换行还要判断'\r'。

**代码**

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
inline int read()
{
    int x=0,w=0;char ch=getchar();
    while(ch<'0'||ch>'9')w|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return w?-x:x;
}
int n,m;
struct node{int x,y,d;}a[4200];
bool map[105][40][4];//map[a][b][c]=1表示在第a行b列的格子可向c方向走
bool v[105][40];
const int dx[4]={-1,0,1,0};
const int dy[4]={0,1,0,-1};
int bfs()
{
	int head=0,tail=0;
	for(register int i=n;i;--i)
	{
		if(map[i][1][3]&&!v[i][1])
		{
			a[++tail].x=i,a[tail].y=1;
			a[tail].d=1,v[i][1]=1;
		}
		if(map[i][m][1]&&!v[i][m])
		{
			a[++tail].x=i,a[tail].y=m;
			a[tail].d=1,v[i][m]=1;
		}
	}
	for(register int i=m;i;--i)
	{
		if(map[1][i][0]&&!v[1][i])
		{
			a[++tail].x=1,a[tail].y=i;
			a[tail].d=1,v[1][i]=1;
		}
		if(map[n][i][2]&&!v[n][i])
		{
			a[++tail].x=n,a[tail].y=i;
			a[tail].d=1,v[n][i]=1;
		}
	}//找出口
	while(head<tail)
	{
		int x=a[++head].x,y=a[head].y;
		for(register int i=0;i<=3;++i)
		{
			int xx=x+dx[i],yy=y+dy[i];
			if(map[x][y][i]&&!v[xx][yy]&&xx>0&&yy>0&&xx<=n&&yy<=m)
			{
				a[++tail].x=xx,a[tail].y=yy;
				a[tail].d=a[head].d+1,v[xx][yy]=1;
			}
		}
	}
	return a[tail].d;//最远的点 
}
int main()
{
	m=read(),n=read();
	for(register int i=1;i<=2*n+1;++i)
	{
		if(i&1)
		{
			char ch=getchar();
			while(ch!='+')ch=getchar();
			for(register int j=1;j<=m;++j)
			{
				map[i>>1][j][2]=map[(i>>1)+1][j][0]=getchar()==' ';//记录栅栏信息
				getchar();//读入无用的'+' 
			}getchar();
		}
		else
		{
			char ch=getchar();
			while(ch=='\n'||ch=='\r')ch=getchar();
			for(register int j=1;j<=m;++j)
			{
				map[i>>1][j-1][1]=map[i>>1][j][3]=ch==' ';
				getchar(),ch=getchar();
			}map[i>>1][m][1]=map[i>>1][m+1][3]=ch==' ';
		}
	}//输入
	printf("%d\n",bfs());
    return 0;
}
```

---

## 作者：Owen_codeisking (赞：2)

首先我声明一下，我的代码洛谷样例单纯是通不过的，要删掉一个getchar();为什么呢？讨论里的几个大佬提醒了我，终于把USACO训练题AK了。详情见讨论版"!!!!注意换行符"

Linux里面是\r\n，Windows里面是\n;

这道题具体是广搜，深搜炸了。首先读入初始化，然后找到出口以后按出口开始遍历两遍，取两者的最小值比较其中的最大值qwq

Code Below:



```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
struct Point
{
    int value;
    int Exit[3];
}e[510][510];//地图
int w,h;
int x1,y1,x2,y2,x3,y3,x4,y4;
int Exit[2][2],tot=0;//出口
int rx[4]={0,0,1,-1};
int ry[4]={1,-1,0,0};//方向
int used[510][510];//哈希
int check(int x,int y);
void BFS(int x,int y,int num)
{
    queue<int> q;
    q.push(x),q.push(y);
    memset(used,0,sizeof(used));
    used[x][y]=1;
    while(!q.empty())
    {
        int p1,q1;
        p1=q.front(),q.pop();
        q1=q.front(),q.pop();
        for(int k=0;k<4;k++)
        {
            int u=p1+rx[k];
            int v=q1+ry[k];
            if(u<1||u>2*h+1||v<1||v>2*w+1||used[u][v]==1)
                continue;
            if(e[u][v].value==0||e[u][v].value==1){
                if(check(u,v)==0)
                    e[u][v].Exit[num]=e[p1][q1].Exit[num]+1;
                else e[u][v].Exit[num]=e[p1][q1].Exit[num];
                used[u][v]=1;q.push(u);q.push(v);
            }
        }
```
}//广搜，碰到+就直接copy,其他情况+1

```cpp
}
int check(int x,int y)
{
    for(int k=0;k<4;k++)
    {
        int u=x+rx[k];
        int v=y+ry[k];
        if(u<1||u>2*h+1||v<1||v>2*w+1)
            continue;
        if(e[u][v].value==-2)
            return 1;
    }
    return 0;
```
}//看看是否遇到+号

```cpp
int main()
{
    char c;
    scanf("%d%d",&w,&h);getchar();getchar();
    for(int i=1;i<=2*h+1;i++){
        for(int j=1;j<=2*w+1;j++){
            scanf("%c",&c);
            if(c=='-'||c=='|')
                e[i][j].value=-1;
            else if(c=='+') e[i][j].value=-2;
            else e[i][j].value=0;
            e[i][j].Exit[1]=e[i][j].Exit[2]=0;
```
/\*+赋值-2.-和|赋值-1，空格赋值0\*/
```cpp
        }
        getchar();getchar();
    }
    /*for(int i=1;i<=2*h+1;i++){
        for(int j=1;j<=2*w+1;j++){
            printf("%d ",e[i][j].value);
        }
        printf("\n");
    }*/
    for(int i=1;i<=2*w+1;i++){
        if(e[1][i].value==0){
            Exit[tot][0]=1,Exit[tot][1]=i;tot++;
        }
        if(e[2*h+1][i].value==0){
            Exit[tot][0]=2*h+1,Exit[tot][1]=i;tot++;
        }
    }
    for(int i=1;i<=2*h+1;i++){
        if(e[i][1].value==0){
            Exit[tot][0]=i,Exit[tot][1]=1;tot++;
        }
        if(e[i][2*w+1].value==0){
            Exit[tot][0]=i,Exit[tot][1]=2*w+1;tot++;
        }
```
}//找出口
e[Exit[0][0]][Exit[0][1]].value=e[Exit[0][0]][Exit[0][1]].Exit[1]=0;

e[Exit[1][0]][Exit[1][1]].value=e[Exit[1][0]][Exit[1][1]].Exit[2]=0;

//printf("%d %d\n%d %d\n",Exit[0][0],Exit[0][1],Exit[1][0],Exit[1][1]);

```cpp
    BFS(Exit[0][0],Exit[0][1],1);
    BFS(Exit[1][0],Exit[1][1],2);
    int Max=0;
    /*for(int i=1;i<=2*h+1;i++){
        for(int j=1;j<=2*w+1;j++){
            if(min(e[i][j].Exit[1],e[i][j].Exit[2])>=10)
                printf("%d ",min(e[i][j].Exit[1],e[i][j].Exit[2]));
            else printf("%d  ",min(e[i][j].Exit[1],e[i][j].Exit[2]));
        }
        printf("\n");
    }*/
    for(int i=1;i<=2*h+1;i++){
        for(int j=1;j<=2*w+1;j++){
            if(e[i][j].value==0&&min(e[i][j].Exit[1],e[i][j].Exit[2])>Max)
                Max=min(e[i][j].Exit[1],e[i][j].Exit[2]);
        }
```
}//取最大值
    printf("%d\n",Max);

    return 0;

}
我敢保证我的题解虽然不是最简洁的但一定是最好懂的！！！！！！！！！！！！！！！！！！！！！！！！！


---

## 作者：Berkry·Lanrings (赞：1)

[原题链接](https://www.luogu.com.cn/problem/P1519)

这道题目是一道经典的广搜题，但是题目阅读起来有一些困难。这幅图读起来有误导性。为处理这种误导性，有的dalao用跳两步的方法处理。但是我们可以用另一种方法处理。

首先，我们面前创造有一个 $H\times W$ 的方格阵。

然后，我们在某些方格之间画上一条直线，直线不可越过。

然后，作 BFS 。

这就是我的代码的基本思路。

我们创建一个 bool 数组 $Ways_{i,j,k}$ 来标识在方格     $Maps_{i,j}$ 向 k 方向走一格是否可以。怎么判断呢？？很简单。看走一步是空格还是栅栏（注意输入的图与我们创建的图之间需要 $\times 2$ 转换）。


如何判断出口呢也很简单，只要这一跳出界了就可以。


```cpp
for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			for(int k=1;k<=4;k++)
			{
				int xf=i*2+xgo[k],yf=j*2+ygo[k];//奶牛的四个方向
				if(Maps[xf][yf]==' ')	Ways[i][j][k]=true;
				else					Ways[i][j][k]=false;

				if(Ways[i][j][k]==true && (i+xgo[k]>n || i+xgo[k]<1 || j+ygo[k]>m || j+ygo[k]<1) )//这一跳跳出了地图的边界
				{
					Get.x=i,Get.y=j,Get.h=1;
					Railways.push(Get);
				}
			}
		}
	}
```

然后反向作BFS。

顺便附一句，gets(s+1) 是从$s_{1}$开始读的。

附上代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
int xgo[10]={0,1,-1,0,0};
int ygo[10]={0,0,0,1,-1};
int n,m,Ans;
char Maps[205][205];
bool Ways[205][205][10];
int Flag[205][205];
struct node
{
	int x,y,h;
};
node Put,Get;
queue<node> Railways;//广搜的标准模板
int main()
{
	memset(Flag,0,sizeof(Flag));
	scanf("%d%d",&m,&n);
	gets(Maps[0]);//读掉换行符
	
	for(int i=1;i<=n*2+1;i++)
	gets(Maps[i]+1);//读入地图
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			for(int k=1;k<=4;k++)
			{
				int xf=i*2+xgo[k],yf=j*2+ygo[k];//奶牛的四个方向
				if(Maps[xf][yf]==' ')	Ways[i][j][k]=true;
				else					Ways[i][j][k]=false;

				if(Ways[i][j][k]==true && (i+xgo[k]>n || i+xgo[k]<1 || j+ygo[k]>m || j+ygo[k]<1) )//这一跳跳出了地图的边界
				{
					Get.x=i,Get.y=j,Get.h=1;
					Railways.push(Get);
				}
			}
		}
	}
	while(Railways.empty()==false)
	{
		Get=Railways.front();
		Railways.pop();
		Ans=Get.h;
		for(int i=1;i<=4;i++)
		{
			int xf=Get.x+xgo[i];
			int yf=Get.y+ygo[i];
			if(Ways[Get.x][Get.y][i]==true && Flag[xf][yf]==0 && (Get.x+xgo[i]>n || Get.x+xgo[i]<1 || Get.y+ygo[i]>m || Get.y+ygo[i]<1)==false)
			{
				Put.x=xf,Put.y=yf,Put.h=Get.h+1;
				Flag[xf][yf]=Put.h;
				Railways.push(Put);
			}
		}
	}
	printf("%d\n",Ans);
	/*for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		printf("%3d",Flag[i][j]);
		putchar('\n');
	}*/
	//system("pause");
	return 0;
 } 
```



---

## 作者：Ireliaღ (赞：1)

**最短路SPFA**

作为第一篇最短路题解，我感觉这貌似是最简单的一个思路。

我们首先把整个字符矩阵读到字符二维数组中

### 建图

* 对于$ch_{x,y}$，如果$x mod 2 == 0$且$y mod 2 == 0$，暂且管这样的一格叫做房间

* 对于每一个房间，如果它四面有一个墙壁是空格，那么向它通向的那个房间建边

### 思路

扫一遍边缘找到两个开口，以它们为起点跑SPFA，对于每个节点的结果取这两次的较小值，最终答案为所有**房间**节点的距离最大值**$+1$**

### 注意事项

本题读入毒瘤，每行需要两个`getchar()`过滤回车

### 代码

```cpp
// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 205;
const int INF = 0x3f3f3f3f;
const int DX[4] = {-2, 0, 2, 0};
const int DY[4] = {0, -2, 0, 2};
const int BX[4] = {-1, 0, 1, 0};
const int BY[4] = {0, -1, 0, 1};

char mp[MAXN][MAXN];
int dis[MAXN * MAXN];
int w, h, n, m, cnt = -1;
int s[MAXN * 4];
int res[3][MAXN * MAXN];
bool vis[MAXN * MAXN];

struct Edge{
    int to, val;
    Edge *next;
    Edge(int to, int val, Edge *next): to(to), val(val), next(next){}
};

Edge *head[MAXN * MAXN];

void AddEdge(int u, int v, int w) {
    head[u] = new Edge(v, w, head[u]);
}

int Id(int x, int y) {
    return m * (x - 1) + y;
}

void Spfa(int s) {
    memset(vis, false, sizeof(vis));
    memset(dis, INF, sizeof(dis));
    dis[s] = 0;
    queue<int> q; q.push(s); vis[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop(); vis[u] = false;
        for (Edge *e = head[u]; e; e = e->next) {
            int v = e->to;
            if (dis[v] > dis[u] + e->val) {
                dis[v] = dis[u] + e->val;
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int main() {
    cin >> w >> h;
    n = h * 2 + 1; m = w * 2 + 1;
    /*getchar();
    for (int i = 1; i <= n; i++) {
        int cnt = 0; char ch;
        while (ch = getchar(), ch != '\n') mp[i][++cnt] = ch;
    }*/
    for (int i = 1; i <= n; i++) {
        getchar();
        for (int j = 1; j <= m; j++) {
            mp[i][j] = getchar();
            if (mp[i][j] == '\n') mp[i][j] = getchar();
        }
    }
    for (int i = 2; i < n; i += 2) {
        for (int j = 2; j < m; j += 2) {
            for (int k = 0; k < 4; k++) {
                int x = i + DX[k], y = j + DY[k], bx = i + BX[k], by = j + BY[k];
                if (x < 1 || x > n || y < 1 || y > m || mp[bx][by] != ' ') continue;
                AddEdge(Id(i, j), Id(x, y), 1);
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        if (mp[1][i] == ' ') s[++cnt] = Id(2, i);
        if (mp[n][i] == ' ') s[++cnt] = Id(n - 1, i);
    }
    for (int i = 1; i <= n; i++) {
        if (mp[i][1] == ' ') s[++cnt] = Id(i, 2);
        if (mp[i][m] == ' ') s[++cnt] = Id(i, m - 1);
    }
    Spfa(s[0]);
    for (int i = 1; i <= n * m; i++) res[0][i] = dis[i];
    Spfa(s[1]);
    for (int i = 1; i <= n * m; i++) res[1][i] = dis[i];
    for (int i = 1; i <= n * m; i++) res[2][i] = min(res[1][i], res[0][i]);
    int ans = 0;
    for (int i = 1; i <= n * m; i++) {
        if (res[2][i] < INF) ans = max(ans, res[2][i]);
    }
    cout << ans + 1 << endl;
    return 0;
}

---

## 作者：依依 (赞：1)

 做了这道题之后，整个人都升华了。  
 **洛谷是双换行符******# ****

这道题主要考察了两个方面

1）你的代码能力  2）你的读题能力

是一道好题

解法：

主要是宽搜的实现过程

我们从每个出口开始去搜索，得到到每个点的最短距离

然后max{每个点的最短距离}  就是我们的答案

在判断相邻各点之间是否联通的时候，可以分四种情况（上下左右）去判断，然后

在搜索，实现起来会好很多

[广告（代码）](https://www.cnblogs.com/adelalove/p/9101893.html)




---

## 作者：源氏可以吃吗 (赞：1)

### 题目大意
一个宽2W+1，长2H+1的迷宫，栅栏的柱子只出现在奇数行或奇数列，求最优解通过最差点的步数。
### 解法
正统BFS出道。
### 难点
有多个起点，求最差一点的最优。
### 解题思路
在一开始找到所有的起点，放进队列，然后每次取出队首，跑BFS。
## 注意
#### 每次走的时候走两格，但是最后到出口只走一步，所以最后答案要加1，读取的时候用gets，要用tmp将回车过滤掉。
### 下面直接贴代码
```cpp
#include<bits/stdc++.h>	//美美的万能头 
using namespace std;
int w,h,ans=0;
char g[210][210],tmp[10];
struct point 
{
	int x,y,step;
};
int det[4][2]={{2,0},{-2,0},{0,2},{0,-2}};
bool used[210][210];
int f=1,e=0;
point q[20001],s;
int main()
{
	cin>>w>>h; gets(tmp);	//过滤回车 
	w=w*2+1;
	h=h*2+1;
	for(int i=0;i<h;i++)
	gets(g[i]);	//读取地图 
	for(int i=1;i<=w;i+=2)
	{
		if(g[0][i]==' ')
		{
			s.x=1,s.y=i,s.step=0;
			used[s.x][s.y]=1;
			q[++e]=s;
		}
		if(g[h-1][i]==' ')
		{
		    s.x=h-2,s.y=i,s.step=0;
			used[s.x][s.y]=1;
			q[++e]=s;	
		}
	}
	for(int i=1;i<=h;i+=2)
	{
		if(g[i][0]==' ')
		{
			s.x=i,s.y=1,s.step=0;
			used[s.x][s.y]=1;
			q[++e]=s;
		}
		if(g[i][w-1]==' ')
		{
		    s.x=i,s.y=w-2,s.step=0;
			used[s.x][s.y]=1;	//标记已走 
			q[++e]=s;	//放入队列 
		}
	}	//将所有起点放入队列 
	while(f<=e)	//判断队列是否为空 
	{
		point u=q[f++];
		for(int i=0;i<4;i++)
		{
			point v=u;
			v.x=u.x+det[i][0],v.y=u.y+det[i][1];
			v.step++;
			if(v.x<0||v.x>=h||v.y<0||v.y>=w)continue;	//若果越界 
			if(g[(v.x+u.x)/2][(v.y+u.y)/2]!=' ')continue;	//	如果是栅栏 
			if(used[v.x][v.y]==1)continue;	//如果走过 
			used[v.x][v.y]=1;	//标记已走 
			q[++e]=v;	//结构体入队 
			if(v.step>ans)ans=v.step;	//判断是否为最差一点的最优解 
		}
	}
	cout<<ans+1<<endl;	//每次走的时候走两格，但是最后到出口只走一步，所以最后答案要加1	 
	return 0;	//华丽结束 
 } 
```

---

## 作者：resftlmuttmotw (赞：0)

题解区里都是一次性走两步

这里我就说一点

按普通(每次走一步)的来最后$+1$再除以$2$就行了

另外输入时加个时间限制 （$q++ if(q>=w)break;$）

```cpp
/*
ID:death_r2
TASK:maze1
LANG:C++
*/
#include <queue>
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
#define reg register int
#define isdigit(x) ('0' <= x&&x <= '9')
template<typename T>
inline T Read(T Type)
{
    T x = 0,f = 1;
    char a = getchar();
    while(!isdigit(a)) {if(a == '-') f = -1;a = getchar();}
    while(isdigit(a)) {x = (x << 1) + (x << 3) + (a ^ '0');a = getchar();}
    return x * f;
}
string mp[210];
bool vis[3][210][210];
int cnt,ans,d[3][210][210],dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}},w,h;
pair<int,int> s[3];
#define pii_pii pair<int,pair<int,int> >
inline void bfs(pair<int,int> s,int index)
{
    priority_queue<pii_pii,vector<pii_pii >,greater<pii_pii > > q;
    q.push(make_pair(0,s));
    vis[index][s.first][s.second] = 1;
    while(!q.empty())
    {
        pii_pii it = q.top();q.pop();
        for(reg i = 0;i < 4;i++)
        {
            int x = it.second.first + dir[i][0];
            int y = it.second.second + dir[i][1];
            if(x < 1||x > h||y < 0||y >= w||mp[x][y] != ' '||vis[index][x][y]) continue;
            d[index][x][y] = d[index][it.second.first][it.second.second] + 1;
            vis[index][x][y] = 1;
            q.push(make_pair(d[index][x][y],make_pair(x,y)));
        }
    }
}
int main()
{
//    freopen("maze1.in","r",stdin);
//    freopen("maze1.out","w",stdout);
    w = Read(1) << 1 ^ 1,h = Read(1) << 1 ^ 1;
    for(reg i = 1;i <= h;i++)
    {
        char x = getchar();
        while(x != ' '&&x != '|'&&x != '+'&&x != '-') x = getchar();
        int q = 0;
		while(x != '\n')
        {
        	++q;
            mp[i] += x;
            x = getchar();
 			if(q >= w) break;
        }
    }
    for(reg i = 1;i <= h;i++)
        while(mp[i].size() < w) mp[i] += ' ';
    for(reg i = 0;i < w;i++)
    {
        if(cnt == 2) break;
        if(mp[1][i] == ' ') s[++cnt] = make_pair(1,i);
        if(mp[h][i] == ' ') s[++cnt] = make_pair(h,i);
    }
    for(reg i = 1;i <= h;i++)
    {
        if(cnt == 2) break;
        if(mp[i][0] == ' ') s[++cnt] = make_pair(i,0);
        if(mp[i][w - 1] == ' ') s[++cnt] = make_pair(i,w - 1);
    }
    bfs(s[1],1),bfs(s[2],2);
    for(reg i = 1;i <= h;i++)
        for(reg j = 0;j < w;j++)
            ans = max(ans,min((d[1][i][j] + 1) / 2,(d[2][i][j] + 1) / 2));
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Celebrate (赞：0)

感觉这一道题用宽搜会比深搜好很多，因为深搜总是一搜到底，就少了很多可以优化的地方了

这一题完全没有必要把栅栏去掉（比如定义f[x][y][t]这个点四个方向是否能走），只需要一次走两格就可以了，并且判断一下是否可以走

首先找出两个出口的坐标，用stx,sty来记录

为了方便我们就逆向思维，从两个起点倒推回去，看看哪一个点是答案，这样比暴力枚举方便了很多很多

代码如下:

```cpp
#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
struct node
{
	int x,y;
};//list记录坐标 
int head,tail;//头和尾 
const int dx[4]={-1,1,0,0};//上下左右四个方向（按顺序） 
const int dy[4]={0,0,-1,1};
int n,m;
int stx[11],sty[11],len;//记录起点和终点 
int f[210][210];//表示这一个点到出口的最短距离 
char st[210][210];//记录字符串 
bool v[210][210];//这一个点是否在list队列之中 
int maxx=0;//最大值 
inline void bfs(int x,int y)//从这一个点开始宽搜 
{
    head=tail=1;node list[21000];
	list[1].x=x;list[1].y=y;//第一步记录一下 
    while(head<=tail)
    {
    	x=list[head].x;y=list[head].y;//这个可有可无 
    	for(int t=0;t<=3;t++)//四个方向 
    	{
    		int xx=x+dx[t];//判断这个方向是否能走 
    		int yy=y+dy[t];
    		if(xx>=1 && xx<=n && yy>=1 && yy<=m)//判断边界 
    		{
    			if(st[xx][yy]==' ')//如果没有墙 （墙没有长度的） 
    			{
    				xx=xx+dx[t];yy=yy+dy[t];//走到点上（一次走两格嘛） 
    				if(xx>=1 && xx<=n && yy>=1 && yy<=m)//再次判断边界 
    				{
		    			if(f[x][y]+1<f[xx][yy])//如果这次为更优值，就采用这一次的值 
		    			{
		    				f[xx][yy]=f[x][y]+1;//赋值 
		    				if(v[xx][yy]==true)//如果没有在队列里面 
		    				{
		    					v[xx][yy]=false;//放进队列里面 
		    					tail++;
								list[tail].x=xx;list[tail].y=yy;
							}
						}
					}
				}
			}
		}
		v[x][y]=true;//回溯 
		head++;//把头+1 
	}
}
int main()
{
    int i,j;
    scanf("%d %d\n",&m,&n);
    m=m*2+1;n=n*2+1;//直接增大地图 
    for(i=1;i<=n;i++) 
    {
        gets(st[i]+1);//记得用gets输入 
        for(j=strlen(st[i]+1)+1;j<=m;j++) st[i][j]=' ';//把没有的补上空格 
    }
    for(i=2;i<=m;i+=2)//上下两边查找出口 
    {
        if(st[1][i]==' ') len++,stx[len]=2  ,sty[len]=i;
        if(st[n][i]==' ') len++,stx[len]=n-1,sty[len]=i;
    }
    for(i=2;i<=n;i+=2)//左右两边查找出口 
    {
        if(st[i][1]==' ') len++,stx[len]=i,sty[len]=2;
        if(st[i][m]==' ') len++,stx[len]=i,sty[len]=m-1;
    }
    memset(f,127,sizeof(f));//初始化f无限大 
    for(i=1;i<=len;i++)//枚举出口 
    {
   		memset(v,true,sizeof(v));v[stx[i]][sty[i]]=false;//出口是不能走的 
    	f[stx[i]][sty[i]]=1;bfs(stx[i],sty[i]);//出口的值一开始为1，逆向思维宽搜这个点
    }
    for(i=2;i<=n;i+=2)//找最大值 
    {
    	for(j=2;j<=m;j+=2)
    	{
    		maxx=max(maxx,f[i][j]);
    	}
    }
    printf("%d",maxx);//输出 
    return 0;
}

```

---

## 作者：3269224138刘 (赞：0)

读入图的时候和“城堡 The Castle”差不多，只要一个格子上下左右有墙就标记一下。（当然要注意横，纵坐标是偶数）

在标记的时候对边界的格子进行处理，如果它往外再扩展的时候没有墙就说明这是出口，存下来。

读好图之后从两个出口分别广搜，如果四周某个方向没有墙就往那个方向继续做，如果当前广搜到的深度小于前面得到的深度就换一下。（注意边界条件）

最后再扫一遍，取出最大值。





```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
int n,m;
char a[1012][1012],s[1012];
int q[1012][1012][12],qq[1012][1012],tot=0,exitx[6],exity[6],f[1012][1012];
void doing(int x,int y,int dist){//广搜最小深度
    if (x<1||y<1||x>m*2+1||y>n*2+1)
      return ;
    if (dist<f[x][y])
    {
      f[x][y]=dist;
      if (q[x][y][1]==0) doing(x-2,y,dist+1);//向四个方向找，我定义的是上北（1）下南（2）左西（3）右东（4）
      if (q[x][y][2]==0) doing(x+2,y,dist+1);
      if (q[x][y][3]==0) doing(x,y-2,dist+1);
      if (q[x][y][4]==0) doing(x,y+2,dist+1);
    }
    else
      return ;
}
int main(){
    cin>>n>>m;
    for (int i=0;i<=m*2+1;i++)
    {
      gets(s);
      for (int j=1;j<=n*2+1;j++)//读入图，可能大家还有更先进的方法......
        a[i][j]=s[j-1];
    }
    for (int i=1;i<=m*2+1;i++)
      for (int j=1;j<=n*2+1;j++)
        if (i%2==0&&j%2==0)
        {
          if (a[i-1][j]=='-')//判断四周是否有墙，我定义的是上北（1）下南（2）左西（3）右东（4）
            q[i][j][1]=1;
          if (a[i+1][j]=='-')
            q[i][j][2]=1;
          if (a[i][j-1]=='|')
            q[i][j][3]=1;
          if (a[i][j+1]=='|')
            q[i][j][4]=1;
              // 判断是否为出口，还要用数组去掉重复出现的出口
          if (i==2&&q[i][j][1]==0&&!qq[i][j])//在上方边界就判断上面是否没墙
          {
            qq[i][j]=1;
            exitx[++tot]=i,exity[tot]=j;//exit存储出口的横，纵坐标
          }
          if (i==m*2&&q[i][j][2]==0&&!qq[i][j])//在下方边界就判断下面是否没墙
          {
            qq[i][j]=1;
            exitx[++tot]=i,exity[tot]=j;
          }
          if (j==2&&q[i][j][3]==0&&!qq[i][j])//在左方边界就判断左面是否没墙
          {
            qq[i][j]=1;
            exitx[++tot]=i,exity[tot]=j;
          }
          if (j==n*2&&q[i][j][4]==0&&!qq[i][j])//在右方边界就判断右面是否没墙
          {
            qq[i][j]=1;
            exitx[++tot]=i,exity[tot]=j;
          }
        }
    for (int i=1;i<=m*2+1;i++)//f[i][j]为i,j这个点的深度
      for (int j=1;j<=n*2+1;j++)
        f[i][j]=100000;
    doing(exitx[1],exity[1],1);//从两个出口分别广搜
    doing(exitx[2],exity[2],1);
    int ans=0;
    for (int i=1;i<=m*2+1;i++)
      for (int j=1;j<=n*2+1;j++)
        if (i%2==0&&j%2==0)
          ans=max(ans,f[i][j]);//ans取最大值
    printf("%d\n",ans);
    return 0;
}
//当然还可以压缩一下，把格子的横，纵坐标都除以2，内存，时间都可以更优
```

---

## 作者：Drinkwater (赞：0)

主要是格式，从两个起点广搜一遍，每个点取最小值，记得图要处理好

/*************************************************************************

    > Author: Drinkwater-cnyali
    > Created Time: 2017/3/23 18:11:43
************************************************************************/













```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long LL;
#define REP(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
#define DREP(i, a, b) for(register int i = (a), i##_end_ = (b); i >= i##_end_; -- i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mem(a, b) memset((a), b, sizeof(a))
template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
int read()
{
    int sum = 0, fg = 1; char c = getchar();
    while(c < '0' || c > '9') { if (c == '-') fg = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return sum * fg;
}
const int Size = 100000;
const int inf = 0x3f3f3f3f;
int n,m,tx,ty,sx,sy;
char s[300];
int map[1010][1010];
int    step1[1010][1010],step2[1010][1010],vis[1010][1010];
int mo[4][2] = {{1,0},{-1,0,},{0,1},{0,-1}};
struct T
{
    int x,y,s;    
};
void bfs1()
{
    queue<T>q;
    vis[sx][sy] = 1;
    step1[sx][sy] = 0;
    q.push((T){sx,sy,0});
    while(!q.empty())
    {
        T ls = q.front();q.pop();
        REP(i,0,3)
        {
            int tmp;
            int Tx = ls.x + mo[i][0];
            int Ty = ls.y + mo[i][1];
            if(Tx < 1 || Ty < 1 || Tx > m || Ty > n || map[Tx][Ty] == 1 || vis[Tx][Ty])continue;
            if(map[Tx][Ty] == 2)tmp = ls.s;
            else tmp = ls.s+1;
            q.push((T){Tx,Ty,tmp});
            step1[Tx][Ty] = tmp;
            vis[Tx][Ty] = 1;
        }
    }
}
void bfs2()
{
    memset(vis,0,sizeof(vis));
    queue<T>q;
    vis[tx][ty] = 1;
    step2[tx][ty] = 0;
    q.push((T){tx,ty,0});
    while(!q.empty())
    {
        T ls = q.front();q.pop();
        REP(i,0,3)
        {
            int tmp;
            int Tx = ls.x + mo[i][0];
            int Ty = ls.y + mo[i][1];
            if(Tx < 1 || Ty < 1 || Tx > m || Ty > n || map[Tx][Ty] == 1 || vis[Tx][Ty])continue;
            if(map[Tx][Ty] == 2)tmp = ls.s;
            else tmp = ls.s+1;
            q.push((T){Tx,Ty,tmp});
            step2[Tx][Ty] = tmp;
            vis[Tx][Ty] = 1;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    gets(s);
    REP(i,1,m*2+1)
    {
        gets(s);
        REP(j,0,strlen(s))
        {
            if(i&1)
            {
                if(s[j] == '+' || s[j] == '-')map[i][j+1] = 1;
            }
            else map[i][j+1] = (s[j] == '|');
        }
    }
    n = n*2+1,m = m*2+1;
    int cnt = 0;
    REP(i,1,n)
    {
        if(!map[1][i])
        {
            if(!cnt)sx = 1,sy = i,cnt++;
            else tx = 1,ty = i;
        }
        if(!map[m][i])
        {
            if(!cnt)sx = m,sy = i,cnt++;
            else tx = m,ty = i;
        }
    }
    REP(i,1,m)
    {
        if(!map[i][1])
        {
            if(!cnt)sx = i,sy = 1,cnt++;
            else tx = i,ty = 1;
        }
        if(!map[i][n])
        {
            if(!cnt)sx = i,sy = n,cnt++;
            else tx = i,ty = n;
        }
    }
    REP(i,2,m-1)
    {
        REP(j,2,n-1)
        {
            if(!map[i][j])
            {
                if(j%2 == 1)map[i][j] = 2;
                else if(i%2 == 1)map[i][j] = 2;
            }
        }
    }
    bfs1();bfs2();
    int ans = 0;
    REP(i,1,m)
    {
        REP(j,1,n)
        {
            if(step1[i][j] && step2[i][j])
                step1[i][j] = min(step1[i][j],step2[i][j]),ans = max(step1[i][j],ans);
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：functionendless (赞：0)

注意换行符是双换行，其它就没什么了，，深搜处理取两次比较较小的，然后再找整张地图里最大的

至于为什么我要写>10000因为我的初始化奇数的单元是不会更改的，所以如果不加就全部输出初值

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int map[300][300],n,m;
int dx[]={-2,0,2,0},dy[]={0,-2,0,2},dx1[]={-1,0,1,0},dy1[]={0,-1,0,1};
void dfs(int x,int y)
{
    int i;
    for(i=0;i<=3;i++)
    {
        if(x+dx[i]>=1 && x+dx[i]<=n && y+dy[i]>=1 && y+dy[i]<=m && map[x+dx1[i]][y+dy1[i]]!=-1&&map[x+dx[i]][y+dy[i]]!=-1&&map[x+dx[i]][y+dy[i]]>map[x][y]+1)
        {
            map[x+dx[i]][y+dy[i]]=map[x][y]+1;
            dfs(x+dx[i],y+dy[i]);
        }
    }
}
int main()
{
    int i,j,x,y,cnt=0;
    char tmp[300];
    memset(map,31,sizeof(map));
    cin>>m>>n;
    m=2*m+1;n=2*n+1;
    for(i=0;i<=n;i++)
        {
            cin.getline(tmp,300);
            int lt=strlen(tmp);
            for(j=0;j<lt;j++)
                if(tmp[j]=='|'||tmp[j]=='+'||tmp[j]=='-') map[i][j+1]=-1;
        }
    for(i=1;i<=n;i++)
    {
        if(cnt>=2) break;
        if(map[i][1]!=-1){cnt++;map[i][2]=1;dfs(i,2);} 
        if(map[i][m]!=-1){cnt++;map[i][m-1]=1;dfs(i,m-1);}
    }
    for(j=1;j<=m;j++)
    {        
        if(cnt>=2) break;
        if(map[1][j]!=-1){cnt++;map[2][j]=1;dfs(2,j);}
        if(map[n][j]!=-1){cnt++;map[n-1][j]=1;dfs(n-1,j);}
    }
    int ans=0;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            if(ans<map[i][j]&&map[i][j]<10000)
                ans=map[i][j];
    printf("%d",ans);
    return 0;
}
```

---

## 作者：nbqdd_2003 (赞：0)

[/color][codep ]

```cpp
const  
  dx:array[1..4]of longint=(-1,0,0,1);  
  dy:array[1..4]of longint=(0,-1,1,0);  
  maxn=201;  
  maxm=80;  
  maxx=100000;  
var  
  i,j,n,m,fmax,fmin,k,l,u,tmp,cnt:longint;  
  map:array[1..maxn,1..maxm]of char;  
  app,obt,loc:array[1..maxn,1..maxm]of longint;  
  done:boolean;  
  opp:array[1..maxn*maxm,1..2]of longint;  
  que:array[1..maxx]of longint;  
  mark:array[1..maxn*maxm]of boolean;  
  dis,dis1,dis2:array[1..maxn*maxm]of longint;  
  spe:array[1..2,1..2]of longint;  
function min(x,y:longint):longint;  
begin  
  if x<y then  
    exit(x)  
  else  
    exit(y);  
end;  
function check(a,b,c,d:longint):boolean;  
begin  
  if (obt[a,b]<>1)and(obt[c,d]<>1) then   
    exit(true)  
  else   
    exit(false);  
end;  
function spfa(st,en,cho:longint):longint;  
var  
  i,now,tail,head,nx,ny,tx,ty:longint;  
begin  
  fillchar(que,sizeof(que),0);  
  fillchar(mark,sizeof(mark),false);  
  for i:=1 to n*m do  
    dis[i]:=maxlongint;  
  dis[st]:=0;   
  mark[st]:=true;    
  que[1]:=st;  
  tail:=1;   
  head:=1;  
  while tail<=head do  
    begin  
      now:=que[tail];  
      nx:=opp[now,1];  
      ny:=opp[now,2];  
      for i:=1 to 4 do  
        begin  
          tx:=nx+dx[i];   
          ty:=ny+dy[i];  
          if (tx>=1)and(tx<=n)and(ty>=1)and(ty<=m) then  
            begin  
              if check(nx,ny,tx,ty) then  
                begin  
                  if (dis[now]<>maxlongint)and(dis[now]+1<dis[loc[tx,ty]]) then  
                    begin  
                      dis[loc[tx,ty]]:=dis[now]+1;  
                      if not mark[loc[tx,ty]] then  
                        begin  
                          inc(head);  
                          que[head]:=loc[tx,ty];  
                          mark[loc[tx,ty]]:=true;  
                        end;  
                    end;  
                end;  
            end;  
        end;  
      mark[now]:=false;  
      inc(tail);  
    end;  
  if cho=1 then  
    dis1:=dis   
  else  
    dis2:=dis;  
  exit((dis[en]+1) div 2);  
end;  
begin  
  readln(m,n);  
  n:=2*n+1;  
  m:=2*m+1;  
  for i:=1 to n do  
    begin  
      for j:=1 to m do  
        begin  
          read(map[i,j]);  
          if (map[i,j]='+')or(map[i,j]='-')or(map[i,j]='|') then  
            obt[i,j]:=1;    //障碍就意味着这是一个篱笆。     
          loc[i,j]:=(i-1)*m+j;    //指标使用数哈希的位置（i，j）。
          opp[(i-1)*m+j,1]:=i;  
          opp[(i-1)*m+j,2]:=j;  
        end;  
      readln;  
    end;  
  for i:=1 to n  do  
    begin  
      if map[i,1]=' ' then   
        begin   
          inc(cnt);   
          spe[cnt,1]:=i;   
          spe[cnt,2]:=1;   
        end;  
      if map[i,m]=' ' then  
        begin  
          inc(cnt);   
          spe[cnt,1]:=i;   
          spe[cnt,2]:=m;   
        end;  
    end;  
  for i:=1 to m do  
    begin  
      if map[1,i]=' ' then  
        begin   
          inc(cnt);  
          app[1,i]:=1;   
          spe[cnt,1]:=1;  
          spe[cnt,2]:=i;  
        end;  
      if map[n,i]=' ' then  
        begin  
          inc(cnt);   
          app[n,i]:=1;  
          spe[cnt,1]:=n;   
          spe[cnt,2]:=i;  
        end;  
    end;       //目的是找到2个出口。                
  fmax:=0;  
  done:=false;  
  for i:=1 to n do  
    begin  
      for j:=1 to m do  
        begin  
          if (obt[i,j]<>1)and(app[i,j]<>1) then    //不是篱笆。
            begin  
              if not done then  
                begin  
                  fmin:=maxlongint;  
                  for k:=1 to 2 do  
                    begin  
                      tmp:=spfa(loc[spe[k,1],spe[k,2]],loc[i,j],k);  
                      if tmp<fmin then  
                        fmin:=tmp;  
                    end;  
                  done:=true;  
                  if fmin>fmax then  
                    fmax:=fmin;  
                end  
              else  
                begin  
                  tmp:=min(dis1[loc[i,j]],dis2[loc[i,j]])+1;  
                  tmp:=tmp div 2;  
                  if tmp>fmax then   
                    fmax:=tmp;  
                end;  
            end;  
        end;  
    end;  
  writeln(fmax);  
end.  
```
[/codep ]
大家可以参考一下这位老先辈的博客，超赞！！------->http://www.cnblogs.com/strawberryfou/


---

## 作者：麻省理工学院 (赞：0)

其实这题还是比较简单的（我还调了30分钟，我真是个zz）

不过这道题还是挺恶心的， 不是一般的那种迷宫形式，而是迷宫的形状， 以需要转化,把输入矩阵首行首列的坐标标号为0,那些横纵坐标为基数且自身为空格的点就是一个标准棋盘上的格子。

对原矩阵进行扫描标记，转化为普通的墙障碍问题。

但要注意的是,由于没有给出具体的出口坐标,所以要用循环查找,但要注意特殊的点(四个角上的点不管一面无墙还是两面无墙都只存一次)

**Code**
```pascal
var
    n,m,i,j,k,ans,l,q,x,y:longint;
    a:array[0..201,0..77]of char;
    f:array[1..4,1..2]of longint=((1,0),(0,1),(-1,0),(0,-1));
    b:array[1..9000,1..2]of longint;
begin
    readln(m,n);
    n:=2*n+1;
    m:=2*m+1;
    for i:=1 to n do
    begin
        for j:=1 to m do
        begin
            read(a[i,j]);
            if (a[i,j]=' ')and((i=1)or(i=n)or(j=1)or(j=m)) then
            begin
                k:=k+1;
                b[k,1]:=i;
                b[k,2]:=j;
            end;
        end;
        readln;
    end;
    i:=0;
    repeat
         i:=i+1;
         ans:=ans+1;
         q:=k;
         for l:=i to k do
         begin
             for j:=1 to 4 do
             begin
                 x:=b[l,1]+f[j,1];
                 y:=b[l,2]+f[j,2];
                 if a[x,y]=' ' then
                 begin
                     a[x,y]:='*';
                     k:=k+1;
                     b[k,1]:=x;
                     b[k,2]:=y;
                 end;
             end;
         end;
         i:=q;
    until i>=k;
    writeln(ans div 2);
end.
```

自己很久前的代码了（现在都转C++了），大家凑合着看吧


---

