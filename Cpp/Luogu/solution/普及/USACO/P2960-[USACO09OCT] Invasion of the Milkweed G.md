# [USACO09OCT] Invasion of the Milkweed G

## 题目描述

Farmer John has always done his best to keep the pastures full of luscious, delicious healthy grass for the cows. He has lost the battle, though, as the evil milkweed has attained a foothold in the northwest part of his farm.

The pasture, as usual, is partitioned into a rectilinear grid of height Y (1 <= Y <= 100) and width X (1 <= X <= 100) with (1,1) being in the lower left corner (i.e., arranged as a normal X,Y coordinate grid). The milkweed has initially begun growing at square (Mx,My). Each week the milkweed propagates to all non-rocky squares that surround any square it already occupies, as many as eight more squares (both the rectilinear squares and the diagonals). After only one week in those squares, it is ready to move on to more squares.

Bessie wants to enjoy all the grass she can before the pastures are taken over by milkweed. She wonders how long it can last. If the milkweed is in square (Mx,My) at time zero, at what time does it complete its invasion of the pasture (which, for the given input data, will always happen)?

The pasture is described by a picture with '.'s for grass and '\*'s for boulders, like this example with X=4 and Y=3:

```
....
..*.
.**.
```

If the milkweed started in the lower left corner (row=1, column=1), then the map would progress like this:

```
    ....  ....  MMM.  MMMM  MMMM
    ..*.  MM*.  MM*.  MM*M  MM*M
    M**.  M**.  M**.  M**.  M**M
week  0    1    2    3    4
```

The milkweed has taken over the entire field after 4 weeks.

## 样例 #1

### 输入

```
4 3 1 1 
.... 
..*. 
.**. 
```

### 输出

```
4 
```

# 题解

## 作者：hater (赞：46)

这是一道对懒得看题意的~~我 没错就是我~~人非常不友好的一道题

令人发指的横坐标与纵坐标 与 起点坐标 ~~坑了我很久~~

看了讨论区的帖子才知道自己的问题

话不多说了 先看第一种解法

### 递推 
------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[105][105],tot=1,n,m,sx,sy,Time=1,sum;
char Map[105][105];
int l[8][2]={{1,0},{0,1},{-1,0},{0,-1},{-1,-1},{1,-1},{-1,1},{1,1}};
int main()
{
	memset(f,-1,sizeof(f));
	cin>>m>>n>>sy>>sx;
	for(int i=n;i>0;i--)
	 for(int j=1;j<=m;j++)
	   {
	   	  cin>>Map[i][j];
	   	  if(Map[i][j]=='.') sum++;
	   }
	f[sx][sy]=0; 
	while(tot!=sum)
	{
	    for(int i=1;i<=n;i++)
	       for(int j=1;j<=m;j++)
	          {
	             bool flag=0;
                     if(f[i][j]>0) continue;
	    	     if(Map[i][j]=='*') continue;
	    	     for(int q=0;q<8;q++)
	             {
	   	         int tx=i+l[q][0];
	   	         int ty=j+l[q][1];
	   	         if(tx<1||tx>n||ty<1||ty>m) continue;
	   	         if(Map[tx][ty]=='*') continue;
	   	         if(f[tx][ty]!=Time-1) continue;
	   	         f[i][j]=Time; flag=1;
	             }
	             if(flag) tot++;
		   }
	    Time++;
	}
	cout<<Time<<endl;
	return 0;
}
```

sum表示草的数量 tot表示已经占领的草的数量

Time 表示已经到第几天了 

f 数组存储着每个草点第一次被占领的时间

第一层循环表示 ： 如果还有草地没被占领 （tot！=sum）

就继续扩展

第二三层循环枚举点 

显然点本身不能是石头且没被占领过

第四层循环枚举邻近的点

如果旁边有被占领的点并且它是被上一次扩展占领的 

那么就标记这个点 被占领的点（tot）++

#### 结果

似乎令人悲愤 

开了o2也只有18分 

不过细想实际上是情理之中

分析一下算法 ：

后三重循环都是确定的（100*100*8） 

只有第一重循环不确定（时间）

当时间多起来的时候 程序就跑的很慢很慢 

但是反而在第十个点 n m 大 但是时间小的时候 

递推还是跑的可以的 

### 深搜


------------

有宽搜AC的地方就会有深搜的骗分记录 

本蒟蒻用深搜尝试了一下 

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
int n,m,sx,sy,ans[105][105];
char Map[105][105];
int l[8][2]={{1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,1},{1,-1},{-1,-1}};
inline void dfs(int x,int y,int step)
{
    ans[x][y]=step;
    int tx,ty;
    for(register int i=0;i<8;i++)
    {
        tx=x+l[i][0]; ty=y+l[i][1];
        if(tx<1||tx>n||ty<1||ty>m) continue;
        if(Map[tx][ty]=='*') continue;
        if(step+1>=ans[tx][ty]) continue;
        dfs(tx,ty,step+1);
    }
}
int main()
{
    memset(ans,0x3f,sizeof(ans));
    cin>>m>>n>>sy>>sx;
    for(register int i=n;i>0;i--)
      for(register int j=1;j<=m;j++)
        cin>>Map[i][j];
    dfs(sx,sy,0); 
    int cnt=0;
    for(register int i=1;i<=n;i++)
      for(register int j=1;j<=m;j++)
        if(Map[i][j]!='*') cnt=max(cnt,ans[i][j]);
    cout<<cnt<<endl;
    return 0;
}
```
基本上用深搜写迷宫是要用记忆化的

用一个数组来记录最小到达的时间 

假设 ： 你走到这用了x步 但是有人用更少的步数走到了这里过

你还要继续走吗 ？ 你继续走会使答案变小吗？ 

显然不会的 那么遇到这种情况就别搜了 

这就叫最优解剪枝

最后一遍循环寻找最大值 

#### 结果 

似乎令人忧伤

不开o2 63分 吸氧后 90 

即使我再加了一些register inline 但是也没有用

望哪位大佬来帮我修到AC 

## 正解 ———— 宽搜


------------

实际上蒟蒻一开始就想到宽搜

但是为了尝试提供新的思路 连续失败多次

发现这题还是得用宽搜 

```cpp
#include<bits/stdc++.h>
using namespace std;
char Map[105][105];
int n,m,l[8][2]={{1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};
bool vis[105][105];
struct mmp
{
	int x,y,step;
}f,v;
queue <mmp> q; 
int bfs()
{
	int tot=0;
	f.step=0; q.push(f);
	while(!q.empty())
	{
		f=q.front();
		q.pop(); tot=max(tot,f.step);
		for(int i=0;i<8;i++)
		{
			v.x=f.x+l[i][0];
			v.y=f.y+l[i][1];
			v.step=f.step+1;
			if(v.x<1||v.x>n||v.y<1||v.y>m) continue;
			if(vis[v.x][v.y]) continue;
			if(Map[v.x][v.y]=='*') continue;
			q.push(v); vis[v.x][v.y]=1; 
		}
	}
	return tot;
}
int main()
{
	cin>>m>>n>>f.y>>f.x;
	vis[f.x][f.y]=1;
	for(int i=n;i>0;i--)
	 for(int j=1;j<=m;j++)
	  cin>>Map[i][j];
	cout<<bfs()<<endl;
	return 0;
}
```
~~洛谷缩进有小小的毛病但是别怪我哦QAQ~~

利用宽搜 我们只用输出最后出队列的点的步数就够了

主要是细节上的问题 不细心是要排错一会儿的

### 小小的总结



------------

实际上只打算发宽搜的程序 

但是洛谷多篇重复 

蒟蒻就另辟蹊径 用其他稍劣的方法拿部分分

实际上就是想告诉看到这篇题解的大佬

一道题不要局限自己的一种思维

有想法就要大胆的去实现 

这样做一题比做十题相同解法的题目的效果要好得多

最后感谢耐心看完蒟蒻题解的大佬 ！！！

谢谢您尊重我的劳动成果

---

## 作者：Arcturus1350 (赞：13)

首先这道题是一道经典的BFS。非常适合刚刚学习深搜的同学。

现在分析一下这个问题。首先，每周是八个方向。就是一圈。

也就是说入侵的范围关于时间是成辐射型扩散。让求最大时间。

也就是完美的BFS。算出来之后，维护一个最大用时就好。

不过说一句。这个数区范围对于一个不会stl的人来说可以直接手写队列。

好了上代码：

```cpp
#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;//头文件不说
int dx[8]={0,1,0,-1,1,1,-1,-1};
int dy[8]={1,0,-1,0,1,-1,1,-1};//定义八个方向
int dis[102][102];//储存所需要的时间
int n,m;int ans;//ans是需要维护的最大值。
int head=1;int tail=1;//定义队列。注意队头队尾是1！；
bool book[102][102];//图
int q[10002][2];//手写队列，第二维一个是横坐标，一个是纵坐标
int mx;int my;//初始位置
int main()
{
    scanf("%d%d%d%d",&n,&m,&mx,&my);//输入并且处理
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            char now;
            cin>>now;
            if(now=='.') book[i][j]=true;
            else book[i][j]=false;
        }
    }//注意我的建图顺序
/*    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            printf("%d ",book[i][j]);
        }
        printf("\n");
    }
*///测试点
    q[1][0]=m-my+1;//把起始点压进队列
    q[1][1]=mx;
    dis[my][m-my+1]=0;//初始化
    while(head<=tail)//判断是否为空队列
    {
        int now_x=q[head][0];
        int now_y=q[head][1];
        int tx,ty;
        head++;//取出队头横纵坐标
        for(int i=0;i<8;i++)//八个方向
        {
            tx=now_x+dx[i];ty=now_y+dy[i];
            if(book[tx][ty]==true&&!dis[tx][ty])
            /*
            这里有个小优化。就是判断能不能走之后。如果搜过了（dis[tx][ty]！=0）就可以不搜了。因为一定会重，直接跳过。
            */
            {
                dis[tx][ty]=dis[now_x][now_y]+1;
                q[++tail][0]=tx;
                q[tail][1]=ty;//判断，更新，入队
            }
        }
    }
/*    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            printf("%d ",dis[i][j]);
        }
        printf("\n");
    }*///测试数据
    
        for(int i=1;i<=m;i++)
        {
            for(int j=1;j<=n;j++)
            {
                ans=max(ans,dis[i][j]);
            }
        }//找最大值
        printf("%d",ans);//输出
    return 0;//程序拜拜
}
```
实际上我最后67行开始可以有一个优化。就是在更新的时候就连ans一起维护了。就像这样

```cpp
//54行开始
    if(book[tx][ty]==true&&!dis[tx][ty])
            {
                dis[tx][ty]=dis[now_x][now_y]+1;
                ans=max(ans,dis[tx][ty]);
                q[++tail][0]=tx;
                q[tail][1]=ty;
            }
        }
    }
    printf("%d",ans);
    return 0;
```

---

## 作者：华恋_韵 (赞：11)

**首先**

我第一眼看这个题，就觉得用广搜，但是广搜要使用队列，所以我先简单教大家一下队列的用法

#### 队列

队列（queue） 是一种线性的数据结构，和栈一样是一种运算受限制的线性表。其限制只允许从表的
前端（front）进行删除操作，而在表的后端（rear）进行插入操作。一般允许进行插入的一端我们称为
队尾，允许删除的一端称为队首。队列的插入操作又叫入队，队列的删除操作又叫出队。

队列的主要操作包括：

入队（push）

出队（pop）

判断队列是否为空（empty）

统计队列元素的个数（size）

访问队首元素（front）


C++ 中直接构造一个 queue 的语句为： queue<T> vec 。这样我们定义了一个名为 vec 的储存 T 类型数
据的队列。其中 T 是我们数组要储存的数据类型，可以是 int 、 float 、 double 或者其他自定义的数
据类型等等。初始的时候 vec 是空的。 比如 queue<int> q 定义了一个储存整数的队列 q 
  
  
  接下来感受一下代码
  
  ```
#include<bits/stdc++.h>//万能头 
using namespace std;
const int dir[8][2]{{1,0},{-1,0},{1,1},{0,1},{-1,1},{1,-1},{0,-1},{-1,-1}};//方位打表 
char G[1005][1005];//存图 
int g[1005][1005];//判断是否被搜索过 
int ttt=0;
struct node{//构造函数 
	int y;//y坐标 
	int x;//x坐标 
	int t;//到达路径 
	node(int yy,int xx,int tt)//构造 
	{
		y=yy;
		x=xx;
		t=tt;
	}
};
void bfs(int y,int x)//广搜 
{
    queue<node> sj;//定义一个队列 
    sj.push(node(y,x,0));//插入第一个乳草起点 
    g[y][x]=true;//做标记，搜索过 
    while(!sj.empty())//如果队列中还有数 
    {
        node now=sj.front();//从队首取出当前数 
        sj.pop();//并踢出他 
        ttt=now.t;//记录步数 
        for(int j=0;j<8;j++)//检测八个方位角 
        {
            int ty=now.y+dir[j][1];//记录方位坐标 
            int tx=now.x+dir[j][0];
            if(G[ty][tx]=='.'&&!g[ty][tx])//如果他没有被检测并且是草 
            {
            	g[ty][tx]=true;//侵略他 
			    sj.push(node(ty,tx,now.t+1));//插入他 
			}
        }
    }
    cout<<ttt;//如果结束了（搜索完了） 输出周数 
} 
int main()//主程序 
{
	int x,y,mx,my;
	scanf("%d%d%d%d",&x,&y,&mx,&my);//输入 
	for(int i=y;i>=1;i--)
	{
		for(int j=1;j<=x;j++)
		{
			cin>>G[i][j];//千万不能用scanf，莫名其妙错误 
		}
	}
	bfs(my,mx);//调用函数 
	return 0;//完美结束 
}
```
好了，谢谢大家！

---

## 作者：qzcbw (赞：4)



## 题目分析

这道题就是经典的 **bfs** 题，适合新学搜索的同学。

对于此题，我们应该从原点开始，每次向八个方向搜索。

判断搜索到的点是否被乳草占领就可以了。

注意：

1.题目给的坐标系是从 **左下角** 开始的。

2.题目的行列输入是先输入 **列数** ，再输入 **行数** ,所以 $x$ 是宽度，$y$ 是长度。

3.起点的坐标也是反着的。

 ~~（全是当时被坑的点）~~ 

## Code
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct node{
	int u,v,w;
};
int dx[8]={1,1,1,-1,-1,-1,0,0};
int dy[8]={1,0,-1,1,0,-1,1,-1};
char a[101][101];
int g[101][101],n,m,mx,my,ans=0;
void bfs(int x,int y){
	queue<node> q;
	q.push((node){x,y,0});
	g[x][y]=1;
	while(!q.empty()){
		node h=q.front();
		q.pop();
		ans=h.w;
		for(int i=0;i<8;i++){
			int fx=h.u+dx[i];
			int fy=h.v+dy[i];
			if(a[fx][fy]=='.'&&g[fx][fy]==0){
				g[fx][fy]=1;
				q.push((node){fx,fy,ans+1});
			}
		}
	}
}
int main(){
	//freopen("1.in","r",stdin);
	int i,j;
	memset(g,0,sizeof(g));
	scanf("%d%d%d%d",&m,&n,&my,&mx);
	for(i=n;i>=1;i--)
		for(j=1;j<=m;j++)
			cin>>a[i][j];
	bfs(mx,my);
	printf("%d",ans);
	return 0;
}
```




---

## 作者：SUNCHAOYI (赞：4)

**bfs搜索，从起始点开始，往八个方向进行搜索，搜到符合要求的入队即可**

**运用结构体记录坐标与时刻，最后一起输出**


------------
### 算法的主要框架：参考《信息奥赛一本通》
```
int bfs()
{
	初始化，初始状态存入队列;
	队列首指针 head=0;尾指针 tail=1;
	do
	{
		指针 head 后移动一位,指向待扩展结点;
		for(int i = 1; i <= max; i++)//max为产生子节点的规则数
		{
			if(子节点符合条件)
			{
				tail指针+1,把新结点存入队尾;
				if(新结点与原有已产生的结点重复)删去该结点(取消入队,tail-1);
				else if(新结点是目标点)输出并退出; 
			} 
		} 
	}while(head<tail);//队列为空 
} 

```


------------
## 代码如下：
```
#include<iostream>
#include<queue>
using namespace std;
const int MAX=101;
int dx[8]={1,1,1,0,0,-1,-1,-1},dy[8]={1,0,-1,1,-1,-1,0,1};//八个方向 
char a[MAX][MAX];int n,m,x,y,ans=0;bool b[MAX][MAX]={0};//标记的数组 
struct node
{
	int x,y,num;
	node(int y1,int x1,int num1)//结构体式记录 
	{
		x=x1;y=y1;num=num1;
	}
};
int bfs(int y,int x);//注意坐标顺序 
int main()
{
	cin>>n>>m>>x>>y;
	for(int i=m;i>=1;i--)
        for(int j=1;j<=n;j++)cin>>a[i][j];
	cout<<bfs(y,x)<<endl;//输出即可
	return 0;
} 
int bfs(int y,int x)
{
	queue<node>f;
	f.push(node(y,x,0));//入队 
	b[y][x]=1;//标记已到过 
	while(!f.empty())//还不为空
	{
		node newn=f.front();//取队首的数并储存
		f.pop();//出队
		ans=newn.num;
		for(int i=0;i<8;i++)//检测八个方位
        {
            int y2=newn.y+dy[i];//记录坐标 
            int x2=newn.x+dx[i];
            if(a[y2][x2]=='.'&&!b[y2][x2])//如果他没有被检测
            {
                b[y2][x2]=1;//标记为1 
                f.push(node(y2,x2,newn.num+1));//新的入队 
            }
        } 
	} 
	return ans;
}
```


---

## 作者：functionendless (赞：3)

一道完全没有技术含量的搜索题

就是有几个坑点 1:题目中说的（mx，my） 写成了坐标形式，但其实my是横坐标（来自讨论的提示）

2:读入的时候数组微微处理一下

代码也很简单

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#define N 110
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
using namespace std;
int map[N][N],n,m;
int dx[9]={0,1,1,1,0,0,-1,-1,-1},dy[9]={0,-1,0,1,1,-1,0,1,-1};
queue<pii> que;
inline int max(int a,int b) {return a>b?a:b;}
int bfs()
{
    int i,j;
    while(!que.empty())
    {
        pii p=que.front(); que.pop();
        for(i=1;i<=8;i++)
        {
            int x=p.F+dx[i],y=p.S+dy[i];
            if(map[x][y]==0)
            {
                map[x][y]=map[p.F][p.S]+1;
                que.push(mp(x,y));
            }
        }
    }
    int ans=0;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            ans=max(map[i][j],ans);
    return ans-1;
}
int main()
{
    int i,j; char ch;
    scanf("%d %d %d %d\n",&m,&n,&j,&i);
    map[i][j]=1; que.push(mp(i,j));
    for(i=n;i>=1;i--)
    {
        for(j=1;j<=m;j++)
            {ch=getchar(); if(ch=='*') map[i][j]=-1;}
        while(ch!='\n') ch=getchar();
    }
    for(i=0;i<=n+1;i++) map[i][0]=map[i][m+1]=-1;
    for(i=0;i<=m+1;i++) map[0][i]=map[n+1][i]=-1;
    printf("%d",bfs());
    return 0;
}
```

---

## 作者：Doubeecat (赞：2)

这道题是一题经典的bfs题，~~甚至被拿来当某弱市夏令营的考试题~~  
言归正传，这道题有几个坑点：    
1. 如图，从最左下角开始是$[1,1]$,如果直接读入会出问题  
![](https://cdn.luogu.com.cn/upload/pic/62529.png)  
2. 题目中的$x,y$分别指宽度与高度，有可能会被坑  
3. 从0时刻开始，不要从1开始进行搜索  

认真读题，避开这些坑点之后你就可以写出这样的一份bfs代码了：
```cpp
#include <cstdio>
#include <cctype>
#include <queue>
#include <iostream>
#include <algorithm>
#define MAXN 110
using namespace std;
#define mp make_pair

inline int read() {
    int a=0,f=1;char v=getchar();
    while(!isdigit(v)) {if (v == '-') {f = -1;}v = getchar();}
    while (isdigit(v)) {a = a * 10 + v - 48;v = getchar();}
    return a * f;
}

int n,m,x,y,xx[8] = {0,1,0,-1,1,1,-1,-1},yy[8] = {1,0,-1,0,1,-1,1,-1},ans;
bool f[MAXN][MAXN];
char ch;

int main() {
    n = read(),m = read(),x = read(),y = read();
    for (int i = m;i > 0;--i) {
        for (int j = 1;j <= n;++j) {
            cin >> ch;
            if (ch == '*') {
                f[i][j] = 1;
            }
        }
    }
    queue <pair<pair<int,int>,int> > q;
    q.push(mp(mp(y,x),0));
    f[y][x] = 1;
    while (!q.empty()) {
        int x1 = q.front().first.first,y1 = q.front().first.second,t = q.front().second;q.pop();
        for (int i = 0;i < 8;++i) {
            if (!f[x1+xx[i]][y1+yy[i]] && x1+xx[i] <= m && x1+xx[i] > 0 && y1+yy[i] <= n && y1+yy[i] > 0) {
                f[x1+xx[i]][y1+yy[i]] = 1;
                q.push(mp(mp(x1+xx[i],y1+yy[i]),t+1));
                ans = max(ans,t+1);
            }
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：江山_远方 (赞：2)

一道BFS经典题

思路很简单，不过题目还是比较坑的，有几个点需要细读题目才能发现（本蒟蒻被坑了N次）

我的思路是这样的：BFS从起点开搜，记录到每一个点的步数，由于乳草蔓延的时间是越往后搜越后，每次求一下最大步数即可

坑点是这样的：

No.1 y是行 x是列

No.2 交换之后，x还要=（n-x+1）(不知道为什么）

No.3 八方向

注意一下即可：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int dx[]={0,-1,0,1,0,-1,-1,1,1};
const int dy[]={0,0,1,0,-1,-1,1,1,-1};
int n,m,M,x,y,b[200][200],c[40000][5];
char ch;
string st;
void bfs()
{
    int h=0,t=1,cx,cy;
    b[x][y]=1;
    c[1][1]=x;
    c[1][2]=y;
    c[1][3]=0;//初始化
    while(h<t)
    {
        h++;
        for(int i=1;i<=8;i++)
        {
            cx=c[h][1]+dx[i];
            cy=c[h][2]+dy[i];//拓展位置
            if(cx<1||cy<1||cx>n||cy>m||b[cx][cy])continue;//越界或遍历过或有石头
            t++;
            c[t][1]=cx;
            c[t][2]=cy;
            c[t][3]=c[h][3]+1;
            M=max(M,c[t][3]);
            b[cx][cy]=1;//加入队列,求最大值
        }
    }
}
int main()
{
    cin>>m>>n>>x>>y;
    swap(x,y);
    x=n-x+1;//交换
    getline(cin,st);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            ch=getchar();
            if(ch=='*')b[i][j]=1;
        }
        getline(cin,st);
    }//读入预处理
    bfs();//广搜从起点遍历
    cout<<M;//输出
    return 0;//华丽的结束 
}
```


---

## 作者：fls233666 (赞：1)

由题目可知，**草地的长和宽都不会超过** $100$ ，数据范围比较小。这个时候，我们就可以考虑**使用搜索算法**。 

搜索算法包括深度优先搜索和广度优先搜索。通过题目描述和样例可以得知，题目要求的是乳草**最快**需要多少天占领整个草地。根据这一点，我们**使用广度优先搜索**解决问题。具体的实现流程如下：

1. 读入草地地图时统计地图上有多少个点是牧草，结果记为 $s$ ；
2. 将乳草起始坐标加入队列，并把起点标记；
3. 取出队首，向**八个方向**拓展；
4. 将所有没有被乳草占领的点标记成不可以走的格子，即代表被乳草占领，同时在 $s$ 中扣除相应的数量；
5. 把这些格子加入队列；
6. 重复3~5步，直到 $s$ 为 $0$ 。这时输出队尾【 _因为最后要拓展到队尾，所以输出队尾时间_ 】。

最后再提一下这题的一些细节问题：

- 注意用数组存储时，要把题目给出的 $X$ 和 $Y$ 坐标， $n$ 和 $m$ 反过来。
- 注意左下角才是 $(1,1)$ ，这说明读入后**要把草场地图上下反转**。

最终代码如下：

```cpp
#include<iostream>
#include<cstdio>
#define rgt register int
#define ll long long
using namespace std;

const int mxn = 111;

char tmp[mxn][mxn],mp[mxn][mxn];

int n,m,sx,sy,hd=0,tl=1,s=0;   //hd和tl为队首和队尾指针

int px[8]={-1,-1,-1,0,0,1,1,1};
int py[8]={-1,0,1,-1,1,-1,0,1};

struct mode_que{
	int x;
	int y;
	int time;
}que[mxn*mxn]; 
//手写队列，个人感觉STL太慢

inline int work(){
	que[tl].time=0;  //起始时间为0
	que[tl].x=sx;
	que[tl].y=sy;
	mp[sx][sy]='*';  //标记
	s--;   //起点被乳草占领，s-1
	while(hd!=tl){
		hd++;
		for(rgt tpx,tpy,i=0;i<8;i++){
			tpx=que[hd].x+px[i];
			tpy=que[hd].y+py[i];   //拓展新的坐标
			if(tpx<=n&&tpy<=m&&tpx>0&&tpy>0&&mp[tpx][tpy]=='.'){
				s--;   //占领格子
				tl++;   //入队
				que[tl].x=tpx;
				que[tl].y=tpy;
				que[tl].time=que[hd].time+1;  
				mp[tpx][tpy]='*';   //标记
				if(s==0){   //占领完了
					return que[tl].time;   //返回答案
				}
			}
		}
	}
}

int main()
{
	char tch;
	scanf("%d%d%d%d",&m,&n,&sy,&sx);   //x和y反过来读入，n和m反过来读入
    
	for(rgt i=1;i<=n;i++){
		scanf("%c",&tch);   //干掉换行符
		for(rgt j=1;j<=m;j++){
			scanf("%c",&tmp[i][j]);  //读入初始草场地图
			if(tmp[i][j]=='.')
				s++;  //统计牧草的格子
		}
	}
    
	for(rgt i=1;i<=n;i++){
		for(rgt j=1;j<=m;j++){
			mp[i][j]=tmp[n-i+1][j]; 
		}
	}  //反转地图
    
	printf("%d",work());
    
	return 0;
}
```


---

## 作者：珅肐 (赞：1)

提供简洁的代码

首先题目是一道入门$BFS$，也没有其他算法掺杂，相对比较简单

注意几点：

- 读入

题目中的起始点写成了坐标的形式，即以左下角为$(1,1)$，而我们平常以左上角为$(1,1)$，这样的话我们需要把它向右旋转一下。

我是把起始点坐标向左旋转，反正$bfs$对此没有要求，只要点正确就好。

向左旋转，稍微推一下就知道，$sy$变成$sx$，$sx$变成$n-sy+1$

别忘了也把$n$和$m$互换

- 能否经过及是否越界的判断

有些人是这么写的
```
if (!f[x1+xx[i]][y1+yy[i]] && x1+xx[i] <= m && x1+xx[i] > 0 && y1+yy[i] <= n && y1+yy[i] > 0)
```
其实不需要，我们知道，能走的点都是$'.'$那我们只要判断这一个条件就好了

如果越界，一定不会是$'.'$

然后只要再把经过的点标为其他符号就行了
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
#include<queue>
using namespace std;
inline int read(){//快读，虽然这道题没用
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
int dx[]={0,1,0,-1,1,1,-1,-1};
int dy[]={1,0,-1,0,1,-1,1,-1};//dx、dy数组表示下一步向哪里走
int t[107][107],ans;//t数组存占领的时间，ans是最后的答案
char c[107][107];//地图
queue<int> qx,qy;//两个队列，分别存x坐标和y坐标，不喜欢用pair或者二维数组模拟，嵌套会显得很恶心
inline void bfs(){
	while(!qx.empty()){
		int x=qx.front(),y=qy.front();qx.pop(),qy.pop();
		for(int i=0;i<8;++i){
			int xx=x+dx[i],yy=y+dy[i];//xx和yy分别表示下一步的位置
			if(f[xx][yy]!='.')continue;//不可以占领或者占领了就跳过
			c[xx][yy]='*';//标记为不可以走
			qx.push(xx),qy.push(yy);//压入队列
			ans=max(ans,t[xx][yy]=t[x][y]+1);//时间比它的来源多1，因为bfs的性质，这个时间就是最短时间，正确性显然（顺便统计答案）
		}
	}
}
int main(){
	int m=read(),n=read(),sy=read(),sx=n-read()+1;
    //这里输入做了处理, 方便以后操作（具体见上）
	qx.push(sx),qy.push(sy);//将一开始的乳草压入队列
	for(int i=1;i<=n;++i)scanf("%s",c[i]+1);//读入
	bfs(); 
	printf("%d",ans);//输出
	return 0;//好习惯
}
```
又：其实还可以用堆优$dij$做，每个点向周围的八个点连边，然后跑一边最短路，统计答案的时候也是找最大值（就是复杂度稍高，多一个log，不过可以无脑直接做啊）

---

## 作者：AveMarina (赞：1)

## 这是一道~~简单的~~有点坑的题

__为什么用广搜__:相信大家都知道广搜可以用来**求边权唯一的最短路**，也就是说**广搜存在最短距离的性质**，由于这个性质，我们可以得到**从某一个点扩展到下一个，这个点到上个点的距离一定是最短的**，当然，这是前人经过了严谨的证明得出的~~反正我是不会的~~，那么我们把这个题目抽象一下，就可以得到题目要求的是**从起点处的草开始算起，起点的草到最后一个长出来的草的距离。**

### 坑~~对于我这种直接开写的~~
1. 题目给的坐标系是从 __左下角__ 开始的
2. 题目的行列输入是 __先输入列数，再输入行数__
3. 因为1所以 __起点的坐标也是反着的__

## 正题
```cpp
#include <iostream>
#include <cstring>
using namespace std;

// BFS
// 方便使用
#define x first
#define y second
typedef pair<int, int > PII;
int n, m;
int sx, sy;
const int N = 110;
char graph[N][N];
// 记录最短距离，同时可以通过距离值来判断是否访问过某点
int dist[N][N];
// 模拟队列，可以比STL快很多
PII que[N * N];
// 八向搜
int move[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};
void bfs(int sx, int sy) {
	memset(dist, -1, sizeof dist);
	int qtop = 0, qback = 0;
	que[qtop] = PII(sx, sy);
   // 不要忘记自己到自己的距离就是最短的
	dist[sx][sy] = 0;
	while (qtop <= qback) {
		PII now = que[qtop++];
		for (int i = 0; i < 8; i++) {
			int nx = now.x + move[i][0], ny = now.y + move[i][1];
			if (nx > n || nx < 1 || ny > m || ny < 1) continue;
        // 如果这个点是石头或者已经访问过了，跳过
			if (dist[nx][ny] != -1 || graph[nx][ny] == '*') continue;
        // 当前点的最短距离就是上一个的最短距离加上权值
			dist[nx][ny] = dist[now.x][now.y] + 1;
			que[++qback] = PII(nx, ny);
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);  
	// 先输入列，再输入行 
	cin >> m >> n >> sx >> sy;
	for (int i = n; i >= 1; i--) {
		for (int j = 1; j <= m; j++) {
			cin >> graph[i][j];
		}
	}
   // 起点坐标也是反着的
	bfs(sy, sx);
	int res = 0;
	for (int i = n; i >= 1; i--) {
		for (int j = 1; j <= m; j++) {
        // 找到最远的草距离起点的草的距离
			res = max(res, dist[i][j]);
		}
	}
	cout << res;
	return 0;
}
```
因为上面的坑WA了两次，第一次是因为踩坑，第二次是因为忘了还原调试注释

~~这篇题解长草了：wwwwwwwwwwww~~

---

