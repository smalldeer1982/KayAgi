# 流れ

## 题目描述

有一个$w\times h$的网格，网格上的每个格子都有对应的高度。

现在，往方格上倒水。

当某个方格内有水，而相邻的方格又比此方格低时，水就会向相邻的方格扩散。

两个方格在有同一条边时被认为是相邻的。

求一格水扩散的方格数量。

## 说明/提示

$1\leq w,h\leq 20$\
$0\leq p\leq w \times h$\
$0\leq Z_{i,j}\leq 100$\
$0\leq X_{i}<w$\
$0\leq Y_{i}<h$

# 题解

## 作者：GODking (赞：2)

### 一、题目描述 ###
**1.**$\quad$输入顺序是 $w$ 、 $h$ ，**实际上是 $h$ 行 $w$ 列**。输入顺序是 $X_i$ 、 $Y_i$ ，**实际上是第 $Y_i$ 行 $X_i$ 列**。这个地方我卡了好久。
### 二、数据范围 ###
**1.**$\quad1≤ w , h ≤20$ ，可想到搜索做这道题。广度优先搜索楼上大佬已讲，我就用深度优先搜索了。

**2.**$\quad0≤ Z_{i,j} ≤100$ ，所以数组用 int 类型是完全能存的下的。
### 三、思路
**1.**$\quad$判断上下左右四个格子是否比当前格子低，如果相邻的格子低于当前格子，计数加 1 ，搜索那个格子，重复至没有格子可以继续搜索。
### 四、打代码
**1.**$\quad$需要注意的地方是数组是**从 0 开始**的，不要从 1 开始或多打等于号。

**2.**$\quad$代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int w,h,p;
int z[25][25];//存储每个格子的高度 
int x[405],y[405];//存储倒水的方格的坐标 
bool f[25][25];//表示每个方格是否能被水扩散到 
int dir[4][2]={{0,1},{1,0},{-1,0},{0,-1}};//方向数组 
int ans;
//深度优先搜索
void dfs(int sx,int sy){//水已经扩散到第sx行sy列的格子 
	for(int i=0;i<4;i++){//遍历与第sx行sy列相邻的格子 
		if(dx>=0&&dy>=0&&dx<h&&dy<w&&z[dx][dy]<z[sx][sy]&&!f[dx][dy]){//判断第dx行dy列的格子是否在网格内，是否有水 
			f[dx][dy]=true;//第dx行dy列的格子有水 
			dfs(dx,dy);
		}
	}
	return ;
}
int main(){
	while(cin>>w>>h>>p){
		//清空 
		ans=0;
		memset(f,false,sizeof(f));
		if(w==0&&h==0&&p==0){
			break;
		}
		for(int i=0;i<h;i++){
			for(int j=0;j<w;j++){
				cin>>z[i][j];
			}
		}
		for(int i=1;i<=p;i++){
			cin>>x[i]>>y[i];
			swap(x[i],y[i]);
			f[x[i]][y[i]]=true;//这里不能忘了倒水处也是有水的 
			dfs(x[i],y[i]);
		}
		for(int i=0;i<h;i++){
			for(int j=0;j<w;j++){
				if(f[i][j]){
					ans++;//计算有水的格子数量 
				}
			}
		}
		cout<<ans<<endl;//不能忘了换行 
	}
	return 0;
}

```



---

## 作者：HKHbest (赞：2)

题目和今年NOIPT1神似

但简单多了

看到 $w,h\le 20$ 的临接矩阵，不难想到搜索。

可以把题目所给的注水点放入队列中宽搜，每次取队首，遇到符合条件（即高度比队首低，相邻且在矩阵中，未访问过）的点就将其推入队尾并累计答案。

一个小坑点是，题目输入先列数后行数。而且输入注水点坐标时也是先列后行的，样例还查不出这个错。~~可能是出于日本特殊的阅读习惯。~~

```
#include<bits/stdc++.h>
using namespace std;
const int N=25,dx[]={-1,0,1,0},dy[]={0,-1,0,1};
int m,n,p,z[N][N],ans;
bool vis[N][N];
struct dian
{
	int x,y;
}d;
bool fw(int i,int j)//确定范围
{
	if(i>=1&&i<=n&&j>=1&&j<=m)
		return true;
	return false;
}
queue<dian> q;
void bfs()
{
	while(!q.empty())
	{
		dian cur=q.front();
		q.pop();
		int x=cur.x,y=cur.y,tx,ty;
		for(int i=0;i<=3;i++)//宽搜
		{
			tx=x+dx[i];
			ty=y+dy[i];
			if(fw(tx,ty)&&vis[tx][ty]==0&&z[x][y]>z[tx][ty])
			{
				ans++;
				vis[tx][ty]=true;
				dian to;
				to.x=tx;
				to.y=ty;
				q.push(to);
			}
		}
	}
}
void clear()
{
	memset(vis,0,sizeof(vis));
	memset(z,0,sizeof(z));//应该不用清这个
	ans=0;
}
int main()
{
	while(1)
	{
		scanf("%d%d%d",&m,&n,&p);
		if(m==0&&n==0&&p==0)
			break;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				scanf("%d",&z[i][j]);
			}
		}
		for(int i=1,x,y;i<=p;i++)
		{
			scanf("%d%d",&x,&y);
			x++;y++;//这里我把0-(n-1)的范围移至(1-n)了
			swap(x,y);
			if(vis[x][y]==0)
			{
				ans++;
				vis[x][y]=true;
				dian tmp;
				tmp.x=x;
				tmp.y=y;
				q.push(tmp);
			}
		}
		bfs();
		printf("%d\n",ans);
		clear();
	}
	return 0;
}
```


---

## 作者：Justinalx (赞：1)

#        **题解**

## ** 1.开始**

文章乍一看，~~老简单了~~。不就是搜索吗！！！
看评测机器怎么 ~~弄死你~~ 回复错误。。。。。

## ** 2.题目意思**
输入若干组输入，每组一个答案，直到 $w,h,p$ **全部**为零。输入一个矩阵。

**注意：题目是按先列后行来输入的,也就是说都是反的！！！** 

然后输入 $p$ 行起始点的位置。

## **3.思路**
1. 有些大佬用宽搜，完全没必要，我是这么觉得的（故意练习除外）。**因为数据范围**


2. 首先从起始点开始，向上向下向左向右四个方向进行搜索，如果相邻的格子低于当前格子的值，也搜索那个格子。同时那个格子定为“走过了”。

3. 最后在暴力枚举一边，把走过了的格子计数。输出答案

思路很简单

## **4.程序**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,i,j,x,ww,y,f[1100][1100],a[1100][1100],sum;
int sc(int x,int y){
	if (x<0||x>=m||y<0||y>=n) return 0;
                      //判断是否越界
	if (f[x][y]==1&&ww!=1) return 0;
	else if (f[x][y]==1&&ww==1) ww=0;
                      //重复不走，但第一次要走
	f[x][y]=1;    //设为“走过了”
	if (x+1<m){   //判断下一个要走的格子有没有越界
		if (a[x+1][y]<a[x][y]) sc(x+1,y);
                      //如果没有，再判断要走的格子的值有没有比当前格子小，下面也是一样的
	}
    if (x-1>=0){
    	if (a[x-1][y]<a[x][y]) sc(x-1,y);
	}
    if (y+1<n){
    	if (a[x][y+1]<a[x][y]) sc(x,y+1);
	}
    if (y-1>=0){
    	if (a[x][y-1]<a[x][y]) sc(x,y-1);
	}
	return 0;
}
int main() {
	scanf("%d%d%d",&n,&m,&k);
	while (n!=0||m!=0||k!=0) {
		memset(f,0,sizeof(f)); //别忘了每次清空
		for (i=0; i<m; i++)
			for (j=0; j<n; j++)
				scanf("%d",&a[i][j]);
                                //别忘了输入是反的！！！
		for (i=1; i<=k; i++) {
			scanf("%d%d",&y,&x);
			f[x][y]=1;
			ww=1;
            sc(x,y);  
		}
		sum=0;
		for (i=0;i<m;i++)
		   for (j=0;j<n;j++)
		       if (f[i][j]==1) sum++;
                         //最后记录走过的格子的数量，输出
		cout<<sum<<endl;
		scanf("%d%d%d",&n,&m,&k);
	}
}
```


---

## 作者：见贤思齐_Seakies (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT178)

------------
### 题意概述

有一个 $w$ 行 $h$ 列的网格，每个位置有一个高度，向其中一个位置注水，求水会覆盖几个位置（水只会向**绝对低于该位置**的位置流动）。

有多组数据。

------------
### 题目分析

**Flood Fill（洪水填充法）** 模板题（前面的题解似乎都没有提到这种算法）啊！

题面都和洪水填充有关，这种算法主要用于**求连通块**，本题就可以**把高度绝对小于该位置的且与他相连所有位置看做一个连通块**。

Flood Fill 是一种基于 BFS 的算法，**先将要注水的位置入队，每次取出队头元素，打标记，然后枚举四个方向，如果满足条件就入队，直到队列为空**。

**注意：本题中的行与列非常混乱**~~（我就被坑了好几次）~~，一定要小心，具体见代码。

------------
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii; // 用 pair 来维护队列中的坐标
int w, h, p, z[25][25], vis[25][25]; // vis 用来标记是否已经有水
int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0}; // 四个方向
queue<pii> q;
int main() {
	while (cin >> h >> w >> p && (w || h || p)) { // 注意先输 h，再输 w
		memset(vis, 0, sizeof(vis)); // 每组数据都要把标记清空
		int ans = 0; // ans 用来统计答案，每次也要清空
		for (int i = 0; i < w; i++) { // 坐标从 0 开始
			for (int j = 0; j < h; j++) {
				cin >> z[i][j];
			}
		}
		while (p--) {
			int x, y;
			cin >> y >> x; // 先输 y，再输 x
			if (!vis[x][y]) q.push(make_pair(x, y)); // 如果已经注水了，就不用再遍历了
			while (!q.empty()) {
				int ux = q.front().first, uy = q.front().second; // 取对头
				q.pop();
				if (vis[ux][uy]) continue; // 如果已经有水就不管它了
				vis[ux][uy] = 1; // 标记已经有水
				ans++; // 答案加一，我本来将这句加在了 if (vis[ux][uy]) continue; 这句前面，结果只过了两个点，原因是，如果放在前面会出现重复统计的情况
				for (int i = 0; i < 4; i++) { // 遍历四个方向
					int tx = ux + dx[i], ty = uy + dy[i];
					if (tx < 0 || tx >= w || ty < 0 || ty >= h) continue; // 如果出界了就不管它
					if (z[tx][ty] < z[ux][uy]) {
						q.push(make_pair(tx, ty));
                       				// 满足条件入队
					}
				}
			}
		}
        	/* 上面 p 的 while 循环也可以多源 BFS 的形式
            	for (int i = 1; i <= p; i++) {
			int x, y;
			cin >> y >> x;
			q.push(make_pair(x, y)); // 把每个注水的位置一起入队
		}
		while (!q.empty()) {
			int ux = q.front().first, uy = q.front().second;
			q.pop();
			if (vis[ux][uy]) continue;
			vis[ux][uy] = 1;
			ans++;
			for (int i = 0; i < 4; i++) {
				int tx = ux + dx[i], ty = uy + dy[i];
				if (tx < 0 || tx >= w || ty < 0 || ty >= h) continue;
				if (z[tx][ty] < z[ux][uy]) {
					q.push(make_pair(tx, ty));
				}
			}
		}
            	*/
                /* 统计答案也可以放到最后，不需要每出队一次就加一
                for (int i = 0; i < w; i++) {
                	for (int j = 0; j < h; j++) {
                    		if (vis[i][j]) ans++;
                            	// 如果该位置有水，答案加一
                    	}
                }
                */
		cout << ans << endl; // 输出答案
	}
	return 0;
} // 不要抄袭哦！
```
------------

### 题目推荐
<https://www.luogu.com.cn/problem/P1434>

<https://www.luogu.com.cn/problem/P1443>

<https://www.luogu.com.cn/problem/P1162>

都是比较简单的题，仅供参考


---

## 作者：COsm0s (赞：0)

###  题目简述

若干组输入，每组一个答案，直到 $w,h,p$ 全部为 $0$。输入一个网格。注意：AT题基本上行列是反着读的，所以要先输入 $w$，再输入 $h$。

然后输入 $p$ 行起始点的位置。（同样要反着读）

在这个网格上的每个格子都有对应的高度。水只能往低处流。

让你在 $p$ 个地点倒水，求水能流到的方格数量。

### 思路

+ 这道题毫无疑问是一道经典的搜索题，但是我们选择用 BFS 还是用 DFS 呢？

我们看数据范围：

$1≤w,h≤20$；

$0\leq p\leq w \times h$；

$0\leq Z_{i,j}\leq 100$；

如果把整个矩阵遍历一遍，$20\times 20\times 400$，即 $w\times h\times p$ 的数据 DFS 也可以轻松的跑一遍。既然可以用 DFS，那又何必用 BFS 呢。

+ 首先从起始点开始，四个方向进行搜索，如果扩展的格子低于当前格子的值，就搜索那个格子。同时标记那个格子，表示占领这个格子。

+ 最后枚举整个矩阵，把走过了的格子计数。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() {//快读 
	int k = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)) {
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)) {
		k = k * 10 + ch - 48;
		ch = getchar();
	}
	return k * m;
}
int w,h,p;
int z[50][50];
int x[405],y[405];
bool pre[25][25];
int di[5]= {0,-1,1,0,0};
int dj[5]= {0,0,0,-1,1};
//方向常量数组 
inline bool check(int x,int y,int dx,int dy) {
	if(dx>0&&dy>0&&dx<=h&&dy<=w&&z[dx][dy]<z[x][y]&&!pre[dx][dy])
		return 1;
	return 0;
}
//判断扩展格子是否合法 
inline void dfs(int x,int y) {
	for(int i=1; i<=4; i++) {
		int dx=x+di[i],dy=y+dj[i];
		if(check(x,y,dx,dy)) {//合法就继续搜 
			pre[dx][dy]=1;//打标记 
			dfs(dx,dy);
		}
	}
	return ;
}
//深搜 
int main() {
	w=read(),h=read(),p=read();
	while(!(w==0&&h==0&&p==0)) {//w,h,p不是0就继续读入 
		int ans=0;
		memset(pre,0,sizeof pre);
		//初始化 
		for(int i=1; i<=h; i++)
			for(int j=1; j<=w; j++)
				cin>>z[i][j];
		for(int i=1; i<=p; i++) {
			cin>>x[i]>>y[i];
			swap(x[i],y[i]);//一大坑点，需要反着读行列 
			++x[i],++y[i];//题目是以零开始的，个人习惯从一开始 
			pre[x[i]][y[i]]=1;
			dfs(x[i],y[i]);
		}
		for(int i=1; i<=h; i++) 
			for(int j=1; j<=w; j++) 
				if(pre[i][j]) 
					++ans;
		//统计 
		cout<<ans<<'\n';//别忘记换行 
		w=read(),h=read(),p=read();
	}
	return 0;
}
```



---

## 作者：duchengjun (赞：0)

# 题意

有一个 $w \times h$ 的网格，网格上的每个格子都有对应的高度。

让你在 $p$ 个地点倒水，求水扩散的方格数量。

水往低处流！！！

# 分析

$1≤w,h≤20$

数据不大，DFS 或 BFS 皆可。

每一个点都进行一次 DFS，把这个点可以到的所有点标记一下，最后统一遍历一下，求水扩散的方格数量。

每一个数据进行一次 BFS，直接求解即可。

**题目中的 $w$ 和 $h$ 其实是 $h$ 行 $w$ 列。**

**题目中的 $x$ 和 $y$ 其实是 $y$ 行 $x$ 列。**

# Code

## DFS

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=20+5;
int w,h,p;
int z[N][N];
int x,y;
int dir[4][2]={0,1,1,0,0,-1,-1,0};
struct P{
	int x,y;
};
queue<P>q;
bool vis[N][N];
void DFS(int x,int y){
	for(int i=0;i<4;i++){
		int nx=x+dir[i][0],ny=y+dir[i][1];
		if(nx>=1&&nx<=w&&ny>=1&&ny<=h&&!vis[nx][ny]&&z[x][y]>z[nx][ny]){
			vis[nx][ny]=true;
			DFS(nx,ny);
		}
	}
}
signed main(){
	while(true){
		cin>>h>>w>>p;
        if(w==0&&h==0&&p==0)break;
		memset(vis,false,sizeof(vis));
		for(int i=1;i<=w;i++)
			for(int j=1;j<=h;j++)
				cin>>z[i][j];
		for(int i=1;i<=p;i++){
			cin>>y>>x;
			x++,y++;
			vis[x][y]=true;
			DFS(x,y);
		}
		int ans=0;
		for(int i=1;i<=w;i++)
			for(int j=1;j<=h;j++)
				if(vis[i][j])
					ans++;
		cout<<ans<<endl;
	}
	return 0;
}

```
## BFS

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=20+5;
int w,h,p;
int z[N][N];
int x,y;
int dir[4][2]={0,1,1,0,0,-1,-1,0};
struct P{
	int x,y;
};
queue<P>q;
bool vis[N][N];
int BFS(){
	int ans=0;
	while(!q.empty()){
		P t=q.front();q.pop();
		ans++;
		int x=t.x,y=t.y;
		for(int i=0;i<4;i++){
			int nx=x+dir[i][0],ny=y+dir[i][1];
			if(nx>=1&&nx<=w&&ny>=1&&ny<=h&&!vis[nx][ny]&&z[x][y]>z[nx][ny]){
				vis[nx][ny]=true;
				q.push(P{nx,ny});
			}
		}
	}
	return ans;
}
signed main(){
	while(true){
		cin>>h>>w>>p;
        if(w==0&&h==0&&p==0)break;
		memset(vis,false,sizeof(vis));
		for(int i=1;i<=w;i++)
			for(int j=1;j<=h;j++)
				cin>>z[i][j];
		for(int i=1;i<=p;i++){
			cin>>y>>x;
			x++,y++;
			if(!vis[x][y]){
				vis[x][y]=true;
				q.push(P{x,y});
			}
		}
		cout<<BFS()<<endl;
	}
	return 0;
}

```


---

