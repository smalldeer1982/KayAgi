# [USACO07DEC] Mud Puddles S

## 题目描述

Farmer John is leaving his house promptly at 6 AM for his daily milking of Bessie. However, the previous evening saw a heavy rain, and the fields are quite muddy. FJ starts at the point (0, 0) in the coordinate plane and heads toward Bessie who is located at (X, Y) (-500 ≤ X ≤ 500; -500 ≤ Y ≤ 500). He can see all N (1 ≤ N ≤ 10,000) puddles of mud, located at points (Ai, Bi) (-500 ≤ Ai ≤ 500; -500 ≤ Bi ≤ 500) on the field. Each puddle occupies only the point it is on.

Having just bought new boots, Farmer John absolutely does not want to dirty them by stepping in a puddle, but he also wants to get to Bessie as quickly as possible. He's already late because he had to count all the puddles. If Farmer John can only travel parallel to the axes and turn at points with integer coordinates, what is the shortest distance he must travel to reach Bessie and keep his boots clean? There will always be a path without mud that Farmer John can take to reach Bessie.

## 样例 #1

### 输入

```
1 2 7
0 2
-1 3
3 1
1 1
4 2
-1 1
2 2```

### 输出

```
11```

# 题解

## 作者：Horizon20182201 (赞：11)

这题吸引我的地方竟然是它的题目。。。

Mud Puddles

一下我就想到了

![大家都喜欢跳泥坑](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1596166870888&di=766c394531adc4a0fe8d9ff439d2f97f&imgtype=0&src=http%3A%2F%2Fn.sinaimg.cn%2Fsinacn%2Fw870h489%2F20180114%2F631b-fyqrewh8860606.jpg)

~~大家都喜欢跳泥坑！！！~~

好了我们言归正传

这题其实是个裸的bfs

一道很好的练手题

先来看看题目中的重点：

“FJ的屋子在平面坐标(0, 0)的位置，贝茜所在的牛棚则位于坐标(X,Y) (-500 <= X <= 500; -500 <= Y <= 500)处。”

~~what？负数？USACO您在逗我？~~

其实面对负数，我们只要把坐标加上500即可，同时也不要忘记存储地图的数组也要相应增加大小。

“最少要走多少路才能到贝茜所在的牛棚呢？”

这。。。说的要多明显有多明显，就差一句“这题请用宽搜解决”。

“你可以认为从FJ的屋子到牛棚总是存在至少一条不经过任何泥塘的路径。”

这就是说此题一定有解，无需考虑走不通的情况。

好的我们先把代码贴上来

```cpp
#include<bits/stdc++.h>
using namespace std;

int X,Y,n,dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};//dir数组存储四个方向
bool mmap[1005][1005];//存储地图（注意这里不是500而是1000）
struct node{
    int x,y,sum;
};//定义结构体，x表示横坐标，y表示纵坐标，sum表示到这个点所需步数
queue <node> qwq;//当然要符合我们小猪佩奇的可爱气质啦

int bfs ()//宽搜
{
    while (!qwq.empty())//队列非空
    {
        int xx,yy,s;
        xx=qwq.front().x;
        yy=qwq.front().y;
        s=qwq.front().sum;//取队首元素进行扩展
        for (int i=0;i<4;i++)//4个方向
        {
            int nx=xx+dir[i][0],
                ny=yy+dir[i][1];//扩展
            if (nx==X && ny==Y)//如果到达目的地
            {
                while (!qwq.empty())
                  qwq.pop();//清空队列
                return s+1;//返回值
            }
            else//没有到达目的地
            {
                if (!mmap[nx][ny])//可以走（即这里不是泥坑）
                {
                    mmap[nx][ny]=true;//把这里标记成走过的
                    //其实可以再开一个vis数组，但对于这题完全没必要
                    qwq.push({nx,ny,s+1});//入队
                }
            }
        }
        qwq.pop();//出队
    }
}

int main()
{
    scanf ("%d%d%d",&X,&Y,&n);//输入
    memset (mmap,false,sizeof (mmap));//初始化
    X+=500;  Y+=500;//重要！！！一定要加500！！！
    qwq.push({500,500,0});//初始情况入队
    for (int i=1;i<=n;i++)
    {
        int a,b;
        scanf ("%d%d",&a,&b);
        a+=500; b+=500;//坐标加500
        mmap[a][b]=true;//标记泥坑
    }
    printf ("%d\n",bfs ());//输出
    return 0;//完结撒花
}
```
另附宽搜模板

```
初始状态入队;       
while(队列不为空)
{
	取队首元素进行扩展; 
	for(对所有可能的拓展状态)
	{
		if(新状态合法)
			入队;
        if(当前状态是目标状态)	
        	处理(输出解或比较解的优劣); 
	}
	队首结点扩展完毕，出队; 
}

```


---

## 作者：啃丁狗 (赞：5)

# 一道BFS，宽搜题
## 注意题目有个坑，那就是xi，yi为负数的时候，应该先把所有坐标都加个500
### 本题解作为没有用STL的感到非常2333
```cpp
#include<bits/stdc++.h>
#define forup(i,a,b) for(i=a;i<=b;i++)
#define fordown(i,a,b) for(i=a;i>=b;i--)
using namespace std;
int x,y,N,a,b,road=0x7fffff;
int mapp[1500][1500];
bool vis[1500][1500],nt[1500][1500];//vis为是否访问过，nt是是否存在泥潭
int dx[5]={0,-1,0,1,0},
    dy[5]={0,0,1,0,-1};
void bfs(int nx,int ny)//nx，ny为现在所在的坐标
{
    int i,j,k,sum=0;
    int head=0,tail=1;
    int tx,ty;
    int h[2300000][3];
    vis[nx][ny]=true;
    h[1][1]=nx;h[1][2]=ny;h[1][0]=0;//h[][]为队列，h[][0]存的是当前的解
    while(head<=tail)//当队列不为空
    {
        head++;
        forup(i,1,4)
        {
            tx=h[head][1]+dx[i];ty=h[head][2]+dy[i];
            if(tx==x&&ty==y)
            {
                road=min(road,h[head][0]+1);//更新最优解
                return;
            }
            if((tx>=0)&&(tx<=1000)&&(ty>=0)&&(ty<=1000)&&(nt[tx][ty]==false)&&(vis[tx][ty]==false))
            {
                tail++;
                h[tail][0]=h[head][0]+1;
                h[tail][1]=tx;
                h[tail][2]=ty;
                vis[tx][ty]=true;
            }
        }
    }
}
int main()
{
    int i,j,k;
    memset(vis,false,sizeof(vis));//初始化
    memset(nt,false,sizeof(nt));
    cin>>x>>y>>N;
    x+=500;
    y+=500;//一定要加500
    forup(i,1,N)
    {
        cin>>a>>b;
        nt[a+500][b+500]=true;
    }
    bfs(500,500);
    cout<<road;
    return 0;
}
```

---

## 作者：hensier (赞：3)

[获得更好的阅读体验](https://shenyouran.github.io/P2873/)

观察本题之后，发现有一个易错点：坐标可能为负。

我们知道，$\text{C++}$中数组下标必须是非负。题目中给出了$-500 \le X \le 500,-500 \le Y \le 500$的条件，所以只需要把所有的下标加上$500$，就一定能满足所有下标为非负。这样，数组大小只需要开到$1000$以上（不包括$1000$）即可。

程序的实现可以使用宽搜，因为宽搜适合处理最优解。而深搜会暴力枚举每一个点，然而这里的点是杂乱无章的，所以深搜的效率是很低的。

我们可以建立一个二维数组来保存对应位置是否有泥，同时在访问过没有泥地的地方之后就可以把这个地方标记为有泥。因为题目要求不进入泥地，而走过的路就不可能再走了，所以可以把`visit`和`mud`两个数组结合起来使用。这样做的根本原因是$\text{BFS}$不需要回溯，因此不需要重新标记。

代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int ex,ey,n,front=1,rear=1,dx[]={-1,0,0,1},dy[]={0,-1,1,0};//ex,ey为结束坐标，n为泥地个数，front,rear分别为队头、队尾，dx,dy为增量数组
bool mud[1001][1001];//注意下标要开到1000以上（不含）
struct node
{
    int x,y,step;
}q[1000001];//1000*1000=10^6，所以队列下标只需要开到10^6（不含）以上即可
int main()
{
    scanf("%d%d%d",&ex,&ey,&n);
    for(int i=0,a,b;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        mud[a+500][b+500]=true;//对每一个输入的坐标都要加500
    }
    q[1]=(node){500,500,0};//注意初始坐标要加500
    while(front<=rear)
    {
        node f=q[front++];
        for(int i=0;i<4;i++)
        {
            int nx=f.x+dx[i],ny=f.y+dy[i];
            if(nx<0||ny<0||nx>1000||ny>1000||mud[nx][ny])continue;//这里原来是<-500或>500就不能走，而现在变成<(-500+500=)0或者>(500+500=)1000
            mud[nx][ny]=true;//标记访问
            q[++rear]=(node){nx,ny,f.step+1};//入队
            if(nx==ex+500&&ny==ey+500)//注意结束坐标也要加500
            {
                printf("%d",q[rear].step);
                return 0;//注意BFS找的是最优解，所以可以在输出后直接结束程序
            }
        }
    }
    return 0;
}
```

当然，要考虑数组下标为负的时候，我们很难忘记$\color{red}\text{STL(标准模板库)}$中的一个秘宝（~~标准模板库里面全是好东西~~），即$\text{map}$。

$\text{map}$可以实现两个任意类型变量的一一对应。来看几个例子：

```cpp
#include<map>//需要引入头文件
map<int,int>m1;//实现int和int之间一一对应的关系
map<string,bool>m2;//实现string和int之间一一对应的关系
m1[-1]=5;//这里可以把-1位置赋值为5
m2["AC is fun"]=true;
```

然而，这里需要二维数组，表面上看起来没有办法实现。但由于递归是合法的，所以我们可以将两个$\text{map}$进行叠加，即：

```cpp
map<int,map<int,bool>>mud;//最终的结果是bool类型，相当于bool mud[][];，只不过下标范围不同（int可以为负）
```

这样，我们就可以更加方便地实现本题的负数坐标问题了（~~尽管常数不小~~）：

```cpp
//注意定义了map之后，前面的500都不需要加了
#include<bits/stdc++.h>//map头文件在万能头文件中
using namespace std;
int ex,ey,n,front=1,rear=1,dx[]={-1,0,0,1},dy[]={0,-1,1,0};
map<int,map<int,bool>>mud;
struct node
{
    int x,y,step;
}q[1000001];
int main()
{
    scanf("%d%d%d",&ex,&ey,&n);
    for(int i=0,a,b;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        mud[a][b]=true;
    }
    while(front<=rear)
    {
        node f=q[front++];
        for(int i=0;i<4;i++)
        {
            int nx=f.x+dx[i],ny=f.y+dy[i];
            if(nx<-500||ny<-500||nx>500||ny>500||mud[nx][ny])continue;
            mud[nx][ny]=true;
            q[++rear]=(node){nx,ny,f.step+1};
            if(nx==ex&&ny==ey)
            {
                printf("%d",q[rear].step);
                return 0;
            }
        }
    }
    return 0;
}
```

然而，$\text{STL}$常数太大，解决方法有：

- 开启$\text{O2}$

- 语言使用$\text{C++17}$

- 和$\text{unordered\_map}$互换

注：$\text{map}$和$\text{unordered\_map}$的时间复杂度极不稳定，可以直接互换（不用万能头文件的话要换头文件）。但是在竞赛中建议不要冒这么大的风险，最好还是少用$\text{STL}$为妙。

对于本题来说，最好的方法还是把横纵坐标全部加上$500$，并把二维数组开到$1000$以上，因为这样下来，$10$个测试点的运行时间可以控制在$\text{100ms}$以内。因此，任何东西都有利有弊——$\text{map}$虽说方便好用，但时间常数是很大的。根据实际情况合理应用才是最关键的。

---

## 作者：Steinway (赞：3)

嗯..惊了 这道题竟然只有一道题解  
（个人认为该题解已经十分清楚）  
不过这位dalao代码的部分细节并不值得学习  
于是我重新码了一遍代码（第一次忘标记WA了是真的惨）  
个人认为代码美了不少..（求dalao别嘲笑）  
因为是道很地道的广搜 这里就不带注释了  
祝福大家 切题愉快！
```cpp
//#define fre yes

#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1005;
int Map[maxn][maxn];

struct Node{
    int x,y,sum;
};

int sx,sy,ex,ey,n;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

template<typename T>inline void read(T&x)
{
    x = 0;char c;int lenp = 1;
    do { c = getchar();if(c == '-') lenp = -1; } while(!isdigit(c));
    do { x = x * 10 + c - '0';c = getchar(); } while(isdigit(c));
    x *= lenp;
}

bool legal(int x,int y)
{
    if(x >= 0 && y >=0 && x <= 1000 && y<=1000 ) return true;
     return false;
}

int main()
{
    read(ex);read(ey);read(n);
    for (int i=1;i<=n;i++)
    {
        int x,y;
        read(x);read(y);
        x += 500;
        y += 500;
        Map[x][y] = 1;
    } 

    queue<Node> q;
    q.push({500,500,0});
    while(!q.empty())
    {
        Node x = q.front();q.pop();
        for (int i=0;i<4;i++)
        {
            int nx = x.x + dx[i];
            int ny = x.y + dy[i];
            if(nx == ex+500 && ny == ey+500) { printf("%d\n",x.sum+1); return 0; }
            if(legal(nx,ny) && Map[nx][ny] == 0)
            {
                Map[nx][ny] = 1;
                q.push({nx,ny,x.sum+1});
            }
        }
    } return 0;
}
```

---

## 作者：Leaved_ (赞：2)

### 详解输出（一个小的剪枝）

~~虽然没什么卵用~~

题解里很多都是用的更新答案法，我来讲一下直接输出的

# 原理：BFS 第一个搜到的就是最优解

为什么呢 ？

我们都知道，BFS的最显著特点就是队列记录，所以不会像DFS那样无法移动才回溯

所以因为BFS是“一步一步走的”

所以最先到达目标点的状态一定是最优解状态（即走的步数最少的状态）

所以找到奶牛位置时直接输出即可

### 另外我用的不是 STL 所以可以了解一下 ~~手写队列~~

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define s(x) scanf("%d",&(x))
#define p(x) printf("%d\n",(x))
#define f(i,a,b) for(int (i)=(a);i<=(b);++i)
#define ll long long 
#define INF 0x7777777f

int n,ans=INF;
bool map_t[10100][10100],vis[10100][10010];
int endx,endy;
int head=1,tail=1;
int que[1010100][3];
int go[4][2] ={{1,0},{0,1},{0,-1},{-1,0}};

void input() {
	s(endx);s(endy);s(n);
	endx+=500;endy+=500;
	f(i,1,n) {
		int x,y;
		s(x);s(y);
		x+=500;
		y+=500;
		map_t[x][y]=1;
	}
	que[head][0]=500;que[head][1]=500;que[head][2]=0;
	vis[500][500]=1;
}

bool can_bfs(int a,int b) {
	if(a>=0 and a<=1000 and b>=0 and b<=1000) return true;
	return false;
}

void Bfs() {
	while(head<=tail) {
		int now_x=que[head][0],now_y=que[head][1],sum=que[head][2];
		head++;
		f(i,0,3) {
			int tx=now_x+go[i][0],ty=now_y+go[i][1];
			if(tx==endx and ty==endy) {
				p(sum+1);
				return;
			}
			if(can_bfs(tx,ty)) {
				if(!map_t[tx][ty] and !vis[tx][ty]) {
					++tail;
					que[tail][0]=tx;que[tail][1]=ty;que[tail][2]=sum+1;
					vis[tx][ty]=1;
				}
			}
		}
	}
}

void output() {
	Bfs();
	return;
}

int main() {
	input();
	output();
	return 0;
}
```


~~又 AC 了一道水题~~

---

## 作者：ez_lcw (赞：2)

# 最短路（广搜）裸题！！！
这题其实没啥好讲的，**直接先用一个bool数组，记录一下某个点有没有泥塘**，然后跑一边最短路（广搜）即可。

注意：因为会有负坐标，所以我把所有的坐标都加了500（坐标上限），然后就不会有用来记录有没有泥塘的$b[i][j]$有$i<0||j<0$的情况啦！

代码如下：

```cpp
#include<cstdio>
#include<queue>
#include<iostream>
#include<cmath>
 
#define N 3000
 
using namespace std;
 
int x,y,n,ans;
bool b[N][N],vis[N][N];
int fx[4]={-1,0,1,0},fy[4]={0,1,0,-1};//上下左右的x、y坐标

struct data{
    int x,y,s;//x，y为坐标，s为走了多远
}now;
 
queue<data>q;
 
bool right(int x,int y){//考虑边界
    if(x>=0&&x<=1000&&y>=0&&y<=1000){//看有没有出边
        return true;
    }else{
        return false;
    }
}
 
void bfs(){
    q.push((data){500,500,0});//把坐标加500
    now.x=-1;
    now.y=-1;
    while(!q.empty()){
        now=q.front();
        q.pop();
        if(now.s>ans){//剪枝，如果现在走的路已经比答案大，那么就continue；
            continue;
        }
        if(vis[now.x][now.y]){//判断是不是泥塘和有没有走过
            continue;
        }
        if(now.x==x&&now.y==y){//更新答案ans
            ans=min(ans,now.s);
        }
        vis[now.x][now.y]=true;//标记已走过
        for(int i=0;i<4;i++){//枚举4个方向
            int xi=now.x+fx[i];
            int yi=now.y+fy[i];
            if(right(xi,yi)&&!b[xi][yi]&&!vis[xi][yi]){//记住！判断边界问题的一定要放在最前面，不然后面的数组可能会访问非法内存。
                q.push((data){xi,yi,now.s+1});
            }
        }
    }
}
 
int main(){
    ans=0x7fffffff;
    scanf("%d%d%d",&x,&y,&n);
    x+=500;//把坐标加500
    y+=500;//把坐标加500
    for(int i=1;i<=n;i++){
        int xi,yi;
        scanf("%d%d",&xi,&yi);
        xi+=500;//把坐标加500
        yi+=500;//把坐标加500
        b[xi][yi]=true;//记录泥塘
    }
    bfs();
    printf("%d\n",ans);//输出
    return 0;
}
```


---

## 作者：hylong (赞：2)

#### 宽搜入门题
[P2873泥水坑](https://www.luogu.org/problemnew/show/P2873)
####  题意转述：
清早6：00，Farmer John就离开了他的屋子，开始了他的例行工作：为贝茜挤奶。前一天晚上，整个农场刚经受过一场瓢泼大雨的洗礼，于是不难想见，FJ 现在面对的是一大片泥泞的土地。FJ的屋子在平面坐标(0, 0)的位置，贝茜所在的牛棚则位于坐标(X,Y) (-500 <= X <= 500; -500 <= Y <= 500)处。当然咯， FJ也看到了地上的所有N(1 <= N <= 10,000)个泥塘，第i个泥塘的坐标为 (A_i, B_i) (-500 <= A_i <= 500；-500 <= B_i <= 500)。每个泥塘都只占据了它所在的那个格子。 Farmer John自然不愿意弄脏他新买的靴子，但他同时想**尽快**到达贝茜所在的位置。为了数那些讨厌的泥塘，他已经耽搁了一些时间了。如果Farmer John 只能平行于坐标轴移动，并且只在x、y均为整数的坐标处转弯，那么他从屋子门口出发，最少要走多少路才能到贝茜所在的牛棚呢？你可以认为从FJ的屋子到牛棚**总是存在至少一条不经过任何泥塘的路径**。
#### 思路：
  根据“尽快”以及数据范围可以想出用BFS解答。但坐标可能为负数，故将泥坑坐标，原点坐标和终点坐标加500是个不错的选择；
  
小提醒：
  1：洛谷评测机最近不能有move，用```move[4][2]  ```
来移动的请改为``` mv[4][2]   ```
 
  2:初始化时不要忘记把原点定义为500,500,0,~~（我因此WA了一次）~~

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int x;
    int y;
    int step;
};//结构体，用于储存
int mv[4][2]={{1,0},{-1,0},{0,-1},{0,1}};//移动方向
int n,nx,ny;
bool mark[1010][1010]={false},vis[1010][1010]={false};//mark数组用于记录泥坑位置，vis用于记录是否走过这个点
int BFS()//广搜
{
    int i,j;
    node a,b,c;
    a.x=500;
    a.y=500;
    a.step=0;//原点初始化
    queue<node>que;//定义队列，貌似可以用数组模拟
    que.push(a);//将原点压入队列
    while(!que.empty())
    {
     b=que.front();
     que.pop();//取出原点
     if(vis[b.x][b.y])
      continue;//当这个点走过时可以跳过这次寻找，因为要找最短路径
     if(b.x==nx+500 && b.y==ny+500)
      return b.step;//当到达终点时结束循环，并将步数返回至主函数
     vis[b.x][b.y]=true;//标记这个点
     for(i=0;i<4;i++)
     {
      c.x=b.x+mv[i][0];
      c.y=b.y+mv[i][1];//寻找下一个点，其实下面的c.step一句可以放到这里
      if(c.x>=0 && c.x<=1000 && c.y>=0 && c.y<=1000 && !mark[c.x][c.y])
      {
       c.step=b.step+1;
       que.push(c);
      }//判断扩展的点是否在边界内，若是，则将其压入队列
     }
    }
}
int main()
{
    int i,x,y;
    cin>>nx>>ny>>n;//输入原点坐标及泥坑个数
    for(i=1;i<=n;i++)
    {
     cin>>x>>y;
     mark[x+500][y+500]=true;
    }//预处理
    printf("%d\n",BFS());//调用BFS函数并输出
    return 0;
}
```


---

## 作者：皮卡丘最萌 (赞：1)

这题题解好像不多，蒟蒻来水一发。

此题可以直接用BFS做，只是要注意几个地方：

我们设f[i,j]表示走到(i,j)这个位置的最小步数。

1.先把所有点设成maxlongint/2.

2.起点f[0,0]=0。

3.泥潭所在位置f[x,y]直接设成-1，表示为不可能走到。

4.当我们BFS时发现第二次走到这个点，但是步数比第一次少时，仍然加入队列，并且把这个点的步数更新，否则不加。

5.C++党的负数问题在PASCAL这里不存在。

上AC代码：

```pascal
const e:array[1..4,1..2] of longint=((-1,0),(1,0),(0,-1),(0,1));
var a,b:array[0..2000000] of longint;
f:array[-502..502,-502..502] of longint;
i,n,x,y,x1,y1,t,w:longint;
begin
readln(x,y,n);
fillchar(f,sizeof(f),63);    //先把所有点设成maxlongint/2.
for i:=1 to n do
  begin
  readln(x1,y1);
  f[x1,y1]:=-1;  //读入泥潭位置并把它设成不可能走到，因为步数是非负的
  end;
t:=1;w:=1;a[1]:=0;b[1]:=0;f[0,0]:=0;  //BFS初始化
while t<=w do
  begin
  for i:=1 to 4 do
    begin
    x1:=a[t]+e[i,1];y1:=b[t]+e[i,2];       //四个方向扩展
    if (x1>=-501) and (x1<=501) and (y1>=-501) and (y1<=501) and (f[a[t],b[t]]+1<f[x1,y1]) then    //没有越界并且当前步数更少
      begin
      f[x1,y1]:=f[a[t],b[t]]+1;   //把这个点的步数更新
      w:=w+1;a[w]:=x1;b[w]:=y1;   //加入队列
      end;
    end;
  t:=t+1;
  end;
writeln(f[x,y]);            //输出步数
end.
```


---

## 作者：翼德天尊 (赞：1)

**一道很普通的广搜题**

[题目传送门](https://www.luogu.com.cn/problem/P2873)

[更好的阅读体验？](https://www.luogu.com.cn/blog/5y2d1n/solution-p2873)

------------
### STEP 1 审题&&提取条件

1.给你一张地图（虽然没有边界）；

2.已知起始点$(0,0)$和终止点$(x,y)$；

3.地图上有$n$个点不能走；

4.求最短行走距离


------------
### STEP 2 分析题意&&提炼方法

- 有起始点~有终止点~有地图~还让求最短行走距离——**广度优先搜索**无疑啊！

- 所以我们要构造队列，并且用一个$visit$数组记录是否走过该点，用一个$ans$数组记录每个点的最短距离，然后用广搜的经典做法就好啦（稍后会有详细代码及注释）

- 但是这个地图**没有边界**啊？没关系，自己造一个足够大但又不是特别大的范围就好啦（当然应该可以不管边界，不过为了体现一般性，还是设个边界吧）

- 怎么处理**负数下标**呢？观察题目数据范围可知，每个点都在$-500$~$500$之间，所以我们可以将所以的点的坐标都加上1000，取相对位置就好啦


------------
### STEP 3 AC代码及完整注释
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int x,y,n,ma[2000][2000],v[2000][2000],ans[2000][2000];//x,y,n如题，ma为该点是否可以走（可以开成bool），v,ans如上所述
int dx[4]={0,0,-1,1};
int dy[4]={1,-1,0,0};//移动数组，每个下标相对应，代表四个方向
struct node{
	int x,y;
};//每个点的结构体
queue <node> q;//结构体队列
int main(){
    scanf("%d %d %d",&x,&y,&n);//输入
    x+=1000,y+=1000;//处理
    while (n--){//输入不能走的点
    	int x1,y1;
		scanf("%d %d",&x1,&y1);
		ma[x1+1000][y1+1000]=1;//标记	
	}
	node s;
	s.x=1000;s.y=1000;
	q.push(s);//放入初始点
	v[1000][1000]=1;//标记
	while (!q.empty()){//队列不为空时
		node w=q.front();//取出首位
		q.pop();//删除
		int s=ans[w.x][w.y]+1;//该变量为此次循环时所要标记的点的最短距离
		if (w.x==x&&w.y==y){
			printf("%d\n",s-1);//符合条件即输出
			return 0;
		}
		for (int i=0;i<4;i++){//四个方向
			node ww;
			ww.x=w.x+dx[i],ww.y=w.y+dy[i];//下一个点
			if (ww.x>=0&&ww.x<=2000&&ww.y>=0&&ww.y<=2000&&v[ww.x][ww.y]==0&&ma[ww.x][ww.y]==0){//在范围内并且该点没有走过而且可以走
				q.push(ww);//放入该点
				v[ww.x][ww.y]=1;//标记
				ans[ww.x][ww.y]=s;//记录
			}
		}
	}
    return 0;//虽然我相信它运行不到这里……
}
```


------------
### STEP 4 完结撒花！

本次题解就这么愉快地结束啦！如果还有什么不懂的问题，评论区恭候您的到来！我会第一时间回复哒！

如果都看懂了，就点个赞纪念一下你的成长吧！


---

## 作者：Pheasant_YQ (赞：0)


## BFS裸题
~~考试T2 打了个DFS之后发现是BFS 然后没时间WA了.~~

# 题目有坑,xi,yi为负数的时候,应该先把所有坐标都加个500.

~~此外本题就很水了.~~

Code ：

```
/*
万恶的USACO.
熟悉的 FJ (Farmer John) and 贝茜. 
BFS 搜索. 
*/
#include <bits/stdc++.h>  

#define ll long long

using namespace std;

struct node{
    int x,y,sum;
};

inline int read() {
    int x = 0,f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
        f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
} 

const int maxn = 1005;
int ma [maxn][maxn];
int sx,sy,ex,ey,n;
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

bool check (int x,int y) {
    if(x >= 0 and y >= 0 and x <= 1000 and y <= 1000 ) return true;
    return false;
}

void bfs () {
	queue <node> q;
    q.push ({500,500,0});
    while (!q.empty ()) {
        node x = q.front (); q.pop ();
        for (int i = 0; i < 4; ++ i) {
            int nx = x.x + dx [i];
            int ny = x.y + dy [i];
            if (nx == ex + 500 and ny == ey + 500) { 
			    printf ("%d\n",x.sum + 1);
			    return ;//必须回溯,不然WA九个. 
			}
            if (check (nx,ny) and ma [nx][ny] == 0) {
                ma [nx][ny] = 1;
                q.push ({nx,ny,x.sum + 1});
            }
        }
    }
}

int main() {
//	freopen ("crossml.in","r",stdin);
//	freopen ("crossml.out","w",stdout);
	ex = read (); ey = read (); n = read ();
	for (int i = 1; i <= n; ++ i) {
		int x,y;
		x = read (); y = read ();
		x += 500;
        y += 500;
        ma [x][y] = 1;
	}
	bfs ();
	fclose (stdin);
	fclose (stdout);
	return 0;
}
/*
4   .  .  .  .  .  .  .  .
3   .  M  .  .  .  .  .  .
2   .  .  M  B  M  .  M  .
1   .  M  .  M  .  M  .  .
0   .  .  *  .  .  .  .  .
-1  .  .  .  .  .  .  .  .
YX -2 -1  0  1  2  3  4  5
*/
```


---

## 作者：Drinkwater (赞：0)

这是一道裸的广搜题，只是要处理下标为负数的情况就好了，全部加500。







```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
#define REP(i,a,b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++i)
inline int read()
{
    char c = getchar();register int fg = 1, sum = 0;
    while(c > '9' || c < '0')
    {
        if(c == '-')fg = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9')
    {
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return fg * sum;
}
const int maxn = 1000+10; 
int sx,sy,n;
struct T
{
    int x,y,step;
};
queue<T>q;
bool p[1010][1010];
int mo[4][2] = {{1,0},{-1,0},{0,1},{0,-1}},a[2010][2010];
int main()
{
    int mx = 0x3f3f3f3f,my = 0x3f3f3f3f;
    sx = read(), sy = read(), n = read();
    sx+=500,sy+=500;
    REP(i,1,n)
    {
        int A,B;
        A = read();
        B = read();
        p[A+500][B+500] = 1;
    }
    q.push((T){500,500,0});
    int flag = 0;
    p[500][500] = 1;
    while(!q.empty())
    {
        T u = q.front();
        q.pop();
        REP(i,0,3)
        {
            int tx = u.x+mo[i][0];
            int ty = u.y+mo[i][1];
            if(tx < 0 || ty < 0 || p[tx][ty]) continue;
            T ls;
            p[tx][ty] = 1;
            ls.x = tx, ls.y = ty ,ls.step = u.step+1;
            q.push(ls);
            if(tx == sx && ty == sy){
                T ls = q.back();
                printf("%d\n",ls.step);
                flag = 1;
                break;
            }
        }
        if(flag)break;
    }
}
```

---

