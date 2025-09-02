# [USACO06OCT] Cows on Skates G

## 题目描述

**本题使用 Special Judge。**

Farmer John 把农场划分为了一个 $r$ 行 $c$ 列的矩阵，并发现奶牛们无法通过其中一些区域。此刻，Bessie 位于坐标为 $(1,1)$ 的区域，并想到坐标为 $(r,c)$ 的牛棚享用晚餐。她知道，以她所在的区域为起点，每次移动至相邻的四个区域之一，总有一些路径可以到达牛棚。

这样的路径可能有无数种，请你输出任意一种，并保证所需移动次数不超过 $100000$。

## 说明/提示

**【数据范围】**

对于 $100\%$ 的数据，$1\le r\le 113$，$1\le c\le 77$。

------------

**【样例说明】* *

![](https://cdn.luogu.com.cn/upload/image_hosting/3gsutffb.png)

图为样例输出的示意图。答案不唯一。

## 样例 #1

### 输入

```
5 8
..*...**
*.*.*.**
*...*...
*.*.*.*.
....*.*.```

### 输出

```
1 1
1 2
2 2
3 2
3 3
3 4
2 4
1 4
1 5
1 6
2 6
3 6
3 7
3 8
4 8
5 8```

# 题解

## 作者：MY（一名蒟蒻） (赞：122)

这题一看，妥妥的BFS嘛。

然鹅，窝秉承能深搜绝不广搜的想法，打了DFS（好久煤打忘得都差不多了）。

**DFS想法**：一条路走到黑，不行就返回。

蛋是，题目只需要窝们输出一条路径，所以窝们的**book数组不需要取消标记**（~~窝就是被这个坑了~~）。

### 注释详见代码。

**代码**
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
//定义r,c(如题)，输出路径用的数组，为了省事写的next数组和做标记的book数组。
int r,c,ax[13000],ay[13000],next[4][2]={{0,1},{1,0},{0,-1},{-1,0}},book[130][90];
char farm[130][90];//地图
bool f=false;//判断是否输出过路径的变量
void dfs(int x,int y,int step)
{
	if(x < 1 || x > r || y < 1 || y > c) return ;//越界
	if(book[x][y]) return ;//来过
	if(farm[x][y] == '*') return ;//无法通行
	if(f) return ;//输出过路径
	if(x == r && y == c)//找到终点
	{
		for(int i=1;i<step;i++) printf("%d %d\n",ax[i],ay[i]);//输出，注意这里是i<step，因为窝们煤油把终点存进数组
		printf("%d %d",r,c);//所以需要单独输出
		f=true;//标记为以输出
		return ;
	}
	ax[step]=x;ay[step]=y;//将当前点坐标存入数组
	book[x][y]=1;//标记已走过
	for(int i=0;i<4;i++)
	{
		dfs(x+next[i][0],y+next[i][1],step+1);//继续搜索
		if(f) return ;//保险起见
	} 
	return ;
}
int main()
{
	scanf("%d %d",&r,&c);//输入
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++) cin >> farm[i][j];
	dfs(1,1,1);//搜索
	return 0;
}
```
### Thank you for your watching! 不介意的话，请您点个赞吧！

---

## 作者：do_while_false (赞：30)

【大概思路】

这题数据范围不大，我们可以考虑用dfs(bfs貌似也行)。

用一个数组储存答案。如果找到了答案，就输出。否则，标记当前正在搜索的坐标，用两个方向数组标记下一步查找的坐标，搜完回溯。

具体的理解可以看看代码。

【代码】

```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int r,c,num=1,ans[10000][2],vis[120][80];//答案数组和标记数组 
char a[120][80];
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};//两个方向数组 
void print() {//输出答案 
	for(int i=1;i<=num;i++)
		cout<<ans[i][0]<<" "<<ans[i][1]<<endl;
}
void dfs(int x,int y) {
	if(x==r&&y==c) {//搜索完了，输出，结束程序。 
		print();
		exit(0);
	}
	for(int i=0;i<4;i++) {
		int xx=x+dx[i],yy=y+dy[i];//利用方向数组继续搜索 
		if(!vis[xx][yy]&&xx>0&&xx<=r&&yy>0&&yy<=c&&a[xx][yy]=='.') {
			vis[xx][yy]=1;//标记 
			num++;//总答案数+1 
			ans[num][0]=xx;
			ans[num][1]=yy;//记录答案 
			dfs(xx,yy);//继续dfs 
			num--;//回溯 
		}
	}
}
int main(void) {	
	cin>>r>>c;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			cin>>a[i][j];//输入 
	vis[1][1]=1;ans[1][0]=1;ans[1][1]=1;//初始化 
	dfs(1,1);//dfs
	return 0;
}
```

---

## 作者：☆木辛土申☆ (赞：16)

既然已经有篇dfs的了，我这里交一篇bfs的QwQ~

这题在普通的bfs上加上路径的存储即可，具体的实现和注解标注在代码注释中
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<utility>
#include<queue>

const int SIZE=120;
//地图和vis数组
char map[SIZE][SIZE];
bool vis[SIZE][SIZE];
//存路径的数组，[0]存x，[1]存y
int dist[SIZE][SIZE][2];
//方向常量数组，相邻的位置，即上下左右
const short fx[]={0,1,-1,0,0};
const short fy[]={0,0,0,1,-1};
//地图长宽
int r,c;

inline bool illegal(int x,int y){
	return x<1||x>r||y<1||y>c||vis[x][y];
}//合法性判断，如果越界或已经访问过，就跳过

inline void bfs(int sx,int sy){
	std::queue<std::pair<int,int> > q;
    q.push(std::make_pair(sx,sy));
	vis[sx][sy]=true;
	while(!q.empty()){
		int x=q.front().first;
		int y=q.front().second;
		q.pop();
        //取出队首元素拓展
		for(int i=1;i<=4;i++){
			int xx=x+fx[i];
			int yy=y+fy[i];
            //如果非法就跳过
			if(illegal(xx,yy)) continue;
            //存路径。
            dist[xx][yy][0]=x;
            dist[xx][yy][1]=y;
            //打标记
			vis[xx][yy]=true;
            //入队
			q.push(std::make_pair(xx,yy));
			if(xx==r&&yy==c) break;
		}
	}
}

void WriteWay(int x,int y){
	if(!(dist[x][y][0]+dist[x][y][1])) return;
    //如果数组中为0，表示到头了，return
	WriteWay(dist[x][y][0],dist[x][y][1]);
	printf("%d %d\n",x,y);//递归输出路径
}

int main(){
	scanf("%d%d",&r,&c); gets(map[0]);//吞掉换行符QwQ
	for(int i=1;i<=r;i++) gets(map[i]+1);//读图
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			if(map[i][j]=='*'){
				vis[i][j]=true;
                //标记障碍物
			}
		}
	}
	bfs(1,1); 
    puts("1 1");//先打印（1,1）
	WriteWay(r,c);
	return 0;
}
```

---

## 作者：Ryo_Yamada (赞：8)

这题2种方法，记录路径DFS或者记录路径BFS。我写的DFS。

DFS需要注意，记录路径数组需要回溯，但记录访问数组不用回溯。如果回溯你就会像我[这样](https://www.luogu.com.cn/record/31714563)~~悲惨的~~TLE一个点。

其他的不用多说吧，DFS迷宫题基本是最形象最好做的一道题了。

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int r, c, a[100005][2]; //a数组记录走过的路径
char maze[115][80];
bool vis[115][80];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};//下一步走到哪里
bool in(int x, int y) {
	return x > 0 && x <= r && y > 0 && y <= c;
}//判断图内
void dfs(int x, int y, int step) {
	if(x == r && y == c) {
		cout << "1 1\n"; //不要忘了第一步的1 1
		for(int i = 0; i < step; i++) {
			cout << a[i][0] << " " << a[i][1] << endl;
		}
		exit(0);
	}
	for(int i = 0; i < 4; i++) {
		int tx = x + dx[i], ty = y + dy[i];
		if(in(tx, ty) && !vis[tx][ty] && maze[tx][ty] == '.') {
			vis[tx][ty] = true;
			a[step][0] = tx, a[step][1] = ty;
			dfs(tx, ty, step + 1);
			//vis[tx][ty] = false;（vis数组不回溯）
			a[step][0] = a[step][1] = 0;//路径要回溯
		}
	}
}
int main() {
    ios::sync_with_stdio(false);
    cin >> r >> c;
    for(int i = 1; i <= r; i++) {
    	for(int j = 1; j <= c; j++) {
    		cin >> maze[i][j];
		}
	}
	vis[1][1] = true;
	dfs(1, 1, 0);
    return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/31714633)，比之前快了不少吧

---

## 作者：封禁用户 (赞：5)

### 前言

先讲讲我这一番艰辛的路程吧... 

我交上去：第一次 WA 1个点 TLE 2个点

然后 TLE 2个点

之后 TLE 1个点

最后 AC 了

这正确率 就这样整低了 ...

### 分析

首先，~~我们打开标签发现是 DFS~~题目要求是走迷宫，但是这数据范围有点诡异呀 ...

113 和 77 ...

然后，我就用了神奇的 DFS 回溯了一下。

反正是一道 $\texttt{SPJ}$ 所以找到之后直接走人，也就是 $\operatorname{exit(0)}$。

于是我就写出了以下毒瘤代码：

```cpp
#include <iostream>
#include <cstdio>
//头文件不多说。
using namespace std;
const int INF=125;
int r,c,fx[]={0,0,1,-1},fy[]={1,-1,0,0},ans[INF][2];
char Map[INF][INF];
//Map 为读入的地图，ans 记录答案，fx 和 fy 分别掌握 x 和 y 的方向。
inline void DFS(int x,int y,int tot)//DFS 深度优先搜索 开始。
{
	if (x==r && y==c)
	{
      //如果找到了那么输出。
		for (int i=1;i<tot;i++)
			printf("%d %d\n",ans[i][0],ans[i][1]);
		exit(0);
     //直接走人 这个函数是可以跳出子程序的。
	}
	for (int i=0;i<4;i++)
		{
			int dx=x+fx[i],dy=y+fy[i];
			if (Map[dx][dy]!='.' || dx<1 || dy<1 || dx>r || dy>c) continue;
        //判断是否可以走。
			Map[dx][dy]='*';
        //如果可以 那么打上标记。
			ans[tot][0]=dx;
			ans[tot][1]=dy;
        //记录答案
//			printf("%d %d\n",dx,dy);
			DFS(dx,dy,tot+1);
			Map[dx][dy]='.';
        //回溯。
		}
	return ;
}
signed main()
{
	scanf("%d %d\n",&r,&c);
	for (int i=1;i<=r;i++) {
		for (int j=1;j<=c;j++)
			scanf("%c",&Map[i][j]);
		scanf("\n");
		}
   //读入 Map 以及 r 和 c
	Map[1][1]='*';
   //防止它乱跑到 1 1的格子。
	printf("1 1\n");
	DFS(1,1,1);//DFS 调用
	return 0;
}
```

然后我们发现了一件非常尴尬的事情 WA1个 TLE 2个

于是我将回溯的 Map 改成 vis 标记

于是 TLE 2个 

...

然后 我开大了数据范围 并且记录答案 的 改成 记录当前的坐标

最后输出 r 和 c

然而又 TLE1 个

所以呢？~~开 O2 呀~~

又发现 只要找到一个路径就可以了！所以回溯可以去掉了！

然后我再思考了一下，发现 vis 数组 也可以去掉，直接在 Map 地图上打标记就可以了！

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=205;
int r,c,fx[]={0,0,1,-1},fy[]={1,-1,0,0},ans[INF][2];
char Map[INF][INF];
bool vis[INF][INF];
inline void DFS(int x,int y,int tot)
{
	if (x==r && y==c)
	{
		for (int i=1;i<tot;i++)
			printf("%d %d\n",ans[i][0],ans[i][1]);
		printf("%d %d\n",r,c);//最后输出 r 和 c 不要忘记
		exit(0);
	}
	for (int i=0;i<4;i++)
		{
			int dx=x+fx[i],dy=y+fy[i];
			if (Map[dx][dy]!='.' || dx<1 || dy<1 || dx>r || dy>c || vis[dx][dy]) continue;
			Map[dx][dy]='*';
			ans[tot][0]=x;
			ans[tot][1]=y;
        //改为记录当前坐标。
//			printf("%d %d\n",dx,dy);
			DFS(dx,dy,tot+1);
		}
	return ;
}
signed main()
{
	scanf("%d %d\n",&r,&c);
	for (int i=1;i<=r;i++) {
		for (int j=1;j<=c;j++)
			scanf("%c",&Map[i][j]);
		scanf("\n");
		}
	Map[1][1]='*'; //同样 在 1 1 上打标记
//	printf("1 1\n");
	DFS(1,1,1);
	return 0;
}
```

### 写在后面的话

我这篇题解如果有错误，那么请在评论区里留言，我将会很感谢反映的人。

**谢谢观赏！**

---

## 作者：wuyonghuming (赞：4)

## 思路：

这道题只要可以用dfs做，没有必要回溯，可以节省效率。

用两个数组记好方向，开始dfs。

先从第一个点开始找，找到一个可以走的而且之前没走过的点继续dfs，并且再用数组把答案记录下来。最后到了右下角输出就行了。

## 代码：
```cpp
#include <bits/stdc++.h>//头文件
using namespace std;
int ansx[100001],ansy[100001],r,c;//ansx,ansy来记录答案
int fx[4]={1,0,0,-1};//规定搜索方向
int fy[4]={0,1,-1,0};//规定搜索方向
bool p[121][81];//这里要记录哪些点走过，那些点没走过
char m[121][81];//存的输入的矩阵
void dfs(int x,int y,int w)//这里的w指的是第几步
{
	ansx[w]=x;
	ansy[w]=y;
	if(x==r&&y==c)
	{
		for(int i=1;i<=w;i++)
		{
			printf("%d %d\n",ansx[i],ansy[i]);//输出答案
		}
		exit(0);//在dfs中结束
	}
	for(int i=0;i<=3;i++)
	{
		int nx=x+fx[i],ny=y+fy[i];
		if(nx>0&&nx<=r&&ny>0&&ny<=c&&m[nx][ny]!='*'&&p[nx][ny]==false)//这里判断有没有走出去和这个点能不能走
		{
			p[nx][ny]=true;//把这个点设为走过，不用回溯。
			dfs(nx,ny,w+1);
		}
	}
}
int main()
{
	cin>>r>>c;
	memset(p,false,sizeof(p));//设所有点没走过
	for(int i=1;i<=r;i++)
	{
		scanf("%s",m[i]+1);//小小的输入优化
	}
	p[1][1]=true;//设第一行第一列的那个点走过
	dfs(1,1,1);
  	return 0;//不要忘了
}
```

希望大家能看懂，谢谢观看。


---

## 作者：monstersqwq (赞：3)

#### 题目大意：

给出一个 $r \times c$ 的矩阵 $a$，其中有一些障碍不可通过，求一条从 $a_{1,1}$ 到 $a_{r,c}$ 的路径，输出经过的点。

数据范围：$1 \le r \le 113,1 \le c \le 77$ ~~USACO的数据范围果然玄学~~

#### 思路：

作为一个大法师（DFS）爱好者，这道题一定要用 DFS 来做。

迷宫的题目简直就是 DFS 的模板题，只需要往四个方向搜索，遇到障碍或走过或出界就返回，没有就记录然后继续搜，搜到终点就输出，然后用 $\operatorname{exit}(0)$ 终止程序。

含有好多注释的代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>//可爱的头文件 
using namespace std;
int r,c,a[205][205],ans[10005][2];//a数组是地图，1表示有障碍，0表示没有；ans数组是答案，ans[i][0]是第i步的行数，ans[i][1]是列数
bool vis[205][205];//记录有没有访问过 
int nex[4]={-1,1,0,0};
int ney[4]={0,0,-1,1};//打表记录方向（DFS常用技巧） 
void dfs(int x,int y,int step)//step记录当前是第几步 
{
	if((x<1||x>r||y<1||y>c)||a[x][y]==1||vis[x][y]==true) return;//如果该点出界或有障碍或走过，直接返回 
	ans[step][0]=x;
	ans[step][1]=y;
	if(x==r&&y==c)
	{
		for(int i=1;i<=step;i++)
		{
			cout<<ans[i][0]<<" "<<ans[i][1]<<endl;//输出答案 
		}
		exit(0);//此语句可在函数中结束整个程序 
	}
	vis[x][y]=true;
	for(int i=0;i<=3;i++)
	{
		dfs(x+nex[i],y+ney[i],step+1);//进一步搜索 
	}
	vis[x][y]=false;//回溯 
	return;
}
int main()
{
	cin>>r>>c;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
		{
			char x;
			cin>>x;
			if(x=='*')
				a[i][j]=1;//读入地图 
		}
	dfs(1,1,1);
	return 0;
}
```
别急，并没有结束，如果把上面的代码交上去的话，就会[这样](https://www.luogu.com.cn/record/31819563) TLE 一个点。

我们观察到，如果从一个点出发有两种方向，先搜完了第一种，发现没有答案，再搜第二种，发现可以到达第一种，再次搜索，还有没有必要呢？

没有，既然已经知道了第一种没有答案，从第二种到第一种再到终点肯定更没有答案，于是，可以把 DFS 中的回溯删除，可以节省很多的时间。

AC 代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>//可爱的头文件 
using namespace std;
int r,c,a[205][205],ans[10005][2];//a数组是地图，1表示有障碍，0表示没有；ans数组是答案，ans[i][0]是第i步的行数，ans[i][1]是列数
bool vis[205][205];//记录有没有访问过 
int nex[4]={-1,1,0,0};
int ney[4]={0,0,-1,1};//打表记录方向（DFS常用技巧） 
void dfs(int x,int y,int step)//step记录当前是第几步 
{
	if((x<1||x>r||y<1||y>c)||a[x][y]==1||vis[x][y]==true) return;//如果该点出界或有障碍或走过，直接返回 
	ans[step][0]=x;
	ans[step][1]=y;
	if(x==r&&y==c)
	{
		for(int i=1;i<=step;i++)
		{
			cout<<ans[i][0]<<" "<<ans[i][1]<<endl;//输出答案 
		}
		exit(0);//此语句可在函数中结束整个程序 
	}
	vis[x][y]=true;
	for(int i=0;i<=3;i++)
	{
		dfs(x+nex[i],y+ney[i],step+1);//进一步搜索 
	}
	return;
}
int main()
{
	cin>>r>>c;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
		{
			char x;
			cin>>x;
			if(x=='*')
				a[i][j]=1;//读入地图 
		}
	dfs(1,1,1);
	return 0;
}
```


---

## 作者：_Clown_ (赞：2)

~~看了一下，应该没人像我这样储存答案的。~~

这道题，是明显的搜索题。我比较喜欢用DFS。

这道题与其他题不同之处在于：这道题是**Special Judge**，走的路径有无数种可能，只要**输出一种**就够了！

所以，我们要将找出的路径存下来，这时，我们就不得不用上C++ STL库中的**STACK**(栈）了。
# 一.介绍一下栈
栈（stack）是C++ STL库中提供的数据结构之一。它是一种特殊的线性表，最大的特点是先进后出。也就是：先进的元素压入栈底，而后进的元素放在栈顶。

接下来我讲讲直接调用STL栈有哪些操作？

第一种：进栈操作（push）

第二种：出栈操作（pop）

第三种：返回长度（size）

第四种：判断是否为空（empty）

其他不多讲，因为在这道题中用不到！

哦对了，如果想普及的话，可以去[这里](https://baike.baidu.com/item/%E6%A0%88/12808149)学习，看一看伟大的百度百科是怎么写的！
# 二.关于这道题
深搜！

题目大意：我们要从(1,1)走到(n,m)，有障碍的地方不能走，并输出路径。

~~概括的是不是很简练？！~~

我们先列个思路吧
### 1.输入
### 2.dfs
### 3.输出路径
第一部分不说了……

dfs对图进行遍历，之所以要避免走重复点，是因为走重复没有意义，找到了做个标记，然后将点压入栈，返回，如果已经有解，就跳出。如果不会写搜索，建议先去做[这题](https://www.luogu.com.cn/problem/P1596)和[这题](https://www.luogu.com.cn/problem/P1506)。

最后讲一下栈部分，我对着代码解释吧。
```cpp
while(!s.empty())//判断栈是否为空，如果空了，就不用继续做了
{
	ttt t=s.top();//提出栈顶元素
	s.pop();//栈顶元素出栈
	cout<<t.x<<' '<<t.y<<endl;//输出
}
```
最后，放代码（有注释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct ttt
{
	int x;
	int y;
};
stack<ttt>s;//栈，记录答案 
int n,m;//行数与列数 
char a[115][80];//输入进来的数组 
bool vis[115][80];//记录是否走过某点 
bool f;//记录是否找到解 
int dir[4][2]={1,0,0,1,-1,0,0,-1};//方向数组 
void dfs(int nx,int ny)
{
	if(nx==n&&ny==m)
	{
		f=true;//标记：已经找到解了 
		ttt now;
		now.x=nx;
		now.y=ny;
		s.push(now);//压入栈 
		return;//立刻返回 
	}
	int i;
	for(i=0;i<4;i++)
	{
		int dx,dy;
		dx=nx+dir[i][0];
		dy=ny+dir[i][1];
		if(dx>0&&dy>0&&dx<=n&&dy<=m&&!vis[dx][dy]&&a[dx][dy]!='*')//判断是否能走过去 
		{
			vis[dx][dy]=true;//标记已经去过 
			dfs(dx,dy);//继续搜索 
			vis[dx][dy]=false;//回溯 
			if(f)//如果找到解了 
			{
				ttt now;
				now.x=nx;
				now.y=ny;
				s.push(now);//压入栈 
				return;//立刻返回 
			}
		}
	}
}
int main()
{
	int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			cin>>a[i][j];//输入 
		}
	}
	vis[1][1]=true;//第一个点去过了 
	dfs(1,1);//开始搜索 
	while(!s.empty())//判断栈是否为空，如果空了，就不用继续做了
	{
		ttt t=s.top();//提出栈顶元素
		s.pop();//栈顶元素出栈
		cout<<t.x<<' '<<t.y<<endl;//输出
	}
    return 0;//结束程序 
}

```
还有，无注释版：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct ttt
{
	int x;
	int y;
};
stack<ttt>s;
int n,m;
char a[115][80];
bool vis[115][80];
bool f;
int dir[4][2]={1,0,0,1,-1,0,0,-1};
void dfs(int nx,int ny)
{
	if(nx==n&&ny==m)
	{
		f=true;
		ttt now;
		now.x=nx;
		now.y=ny;
		s.push(now);
		return;
	}
	int i;
	for(i=0;i<4;i++)
	{
		int dx,dy;
		dx=nx+dir[i][0];
		dy=ny+dir[i][1];
		if(dx>0&&dy>0&&dx<=n&&dy<=m&&!vis[dx][dy]&&a[dx][dy]!='*')
		{
			vis[dx][dy]=true;
			dfs(dx,dy);
			vis[dx][dy]=false;
			if(f)
			{
				ttt now;
				now.x=nx;
				now.y=ny;
				s.push(now);
				return;
			}
		}
	}
}
int main()
{
	int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
	vis[1][1]=true;
	dfs(1,1);
	while(!s.empty())
	{
		ttt t=s.top();
		s.pop();
		cout<<t.x<<' '<<t.y<<endl;
	}
    return 0;
}
```
# 最后说一句，这道题需要卡常，但是，只要用O2就行了！
### THE END

---

## 作者：Snow_Dreams (赞：1)

这道题DFS,BFS都可以，我建议用bfs，因为bfs的速度其实有时候比dfs快很多，然后模板性强，写起来比较简单

bfs的特点就是使用队列，队列具有先进先出的特点。

具体实现：通过把起点压入队列中，然后将队首弹出，如果vis[x] = false,就将队首一步可以到达的点压入队列中，然后再将vis[x]设为true，然后就一直重复这一操作，直到队列为空

这样就可以更快的求出是否起点与终点是否联通

在bfs的过程中，可以通过记录点来完成路径的输出

具体做法：在bfs的过程中打标记

然后提供一份bfs的模板代码：

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn=100;
bool vst[maxn][maxn]; // 访问标记
int dir[4][2]={0,1,0,-1,1,0,-1,0}; // 方向向量

struct State // BFS 队列中的状态数据结构
{
int x,y; // 坐标位置
int Step_Counter; // 搜索步数统计器
};

State a[maxn];

bool CheckState(State s) // 约束条件检验
{
if(!vst[s.x][s.y] && ...) // 满足条件
return 1;
else // 约束条件冲突
return 0;
}

void bfs(State st)
{
queue <State> q; // BFS 队列
State now,next; // 定义2 个状态，当前和下一个
st.Step_Counter=0; // 计数器清零
q.push(st); // 入队
vst[st.x][st.y]=1; // 访问标记
while(!q.empty())
{
now=q.front(); // 取队首元素进行扩展
if(now==G) // 出现目标态，此时为Step_Counter 的最小值，可以退出即可
{
...... // 做相关处理
return;
}
for(int i=0;i<4;i++)
{
next.x=now.x+dir[i][0]; // 按照规则生成下一个状态
next.y=now.y+dir[i][1];
next.Step_Counter=now.Step_Counter+1; // 计数器加1
if(CheckState(next)) // 如果状态满足约束条件则入队
{
q.push(next);
vst[next.x][next.y]=1; //访问标记
}
}
q.pop(); // 队首元素出队
}
 return;
}

int main()
{
......
 return 0;
}

```
注：此代码为转载https://blog.csdn.net/sunyuhang99/article/details/81427910


---

