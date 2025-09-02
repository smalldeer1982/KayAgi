# Serial Time!

## 题目描述

The Cereal Guy's friend Serial Guy likes to watch soap operas. An episode is about to start, and he hasn't washed his plate yet. But he decided to at least put in under the tap to be filled with water. The plate can be represented by a parallelepiped $ k×n×m $ , that is, it has $ k $ layers (the first layer is the upper one), each of which is a rectangle $ n×m $ with empty squares ('.') and obstacles ('#'). The water can only be present in the empty squares. The tap is positioned above the square $ (x,y) $ of the first layer, it is guaranteed that this square is empty. Every minute a cubical unit of water falls into the plate. Find out in how many minutes the Serial Guy should unglue himself from the soap opera and turn the water off for it not to overfill the plate. That is, you should find the moment of time when the plate is absolutely full and is going to be overfilled in the next moment.

Note: the water fills all the area within reach (see sample 4). Water flows in each of the 6 directions, through faces of $ 1×1×1 $ cubes.

## 样例 #1

### 输入

```
1 1 1

.

1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 1 1

.

#

1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2 2 2

.#
##

..
..

1 1
```

### 输出

```
5
```

## 样例 #4

### 输入

```
3 2 2

#.
##

#.
.#

..
..

1 2
```

### 输出

```
7
```

## 样例 #5

### 输入

```
3 3 3

.#.
###
##.

.##
###
##.

...
...
...

1 1
```

### 输出

```
13
```

# 题解

## 作者：Tune_ (赞：4)

第一次看到这题，我蒙了。。。

仔细一看，这不就是洪水吗？只是加了一个层的参数而已。

PS：洪水算法，就是像发洪水一样，哪里有空往哪儿搜，直到所有的空都填满。

所以啊，这题其实是一道简单的搜索题，只是比起普通题来，多了一个参数，多了2个方向而已。

不多说，请看代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,k,ans=0;
int dx[6]={0,0,0,0,1,-1};//方向数组
int dy[6]={0,0,1,-1,0,0};
int dh[6]={1,-1,0,0,0,0}; 
char a[15][15][15];
void dfs(int h,int x,int y)//发洪水啦~
{
	ans++;//更新答案
	a[h][x][y]='#';//标记一下
	for(int i=0;i<6;i++)
	{
		int hh=h+dh[i],xx=x+dx[i],yy=y+dy[i];
		if(hh<=k&&hh>=1&&xx>=1&&xx<=n&&yy>=1&&yy<=m&&a[hh][xx][yy]=='.')//不能超界，且走得通
			dfs(hh,xx,yy);
	}
}
int main()
{
	cin>>k>>n>>m;
	for(int i=1;i<=k;i++)
	for(int j=1;j<=n;j++)
	for(int k=1;k<=m;k++)
		cin>>a[i][j][k];//输入
	int xs,ys;
	cin>>xs>>ys;
	dfs(1,xs,ys);//从起始点开始
	cout<<ans;//输出答案
	return 0;//拜了个拜~
}
```


---

## 作者：Fearliciz (赞：1)

翻译非常误导人，不建议看

#### 题目大意：

给出一个长为 $n$，宽为 $m$，高为 $k$ 的长方体，每个位置都有一个字符，`.`表示空位，`#`表示障碍，现在在最上一层的某一个空位有一个水龙头，水一次可以向前后左右上下移动（这很不科学），求要多少次使得整个长方体充满水（不包括障碍）。

值得提醒的是，一次只能向一个方向移动，而不是同时向六个方向移动。

#### 解题思路：

看了一下数据，明显可以直接暴力 $\texttt{dfs}$ 不过是一个三维的 $\texttt{dfs}$ 方向数组也要改成三维的。其他和标准 $\texttt{dfs}$ 一样。

这样代码就出来了。


```cpp
#include<bits/stdc++.h>

using namespace std;

int k,n,m,ans;
char dis[15][15][15];
bool vis[15][15][15];
int dx[]={0,1,-1,0,0,0,0};
int dy[]={0,0,0,1,-1,0,0};
int dh[]={0,0,0,0,0,1,-1};

void dfs(int h,int x,int y,int step){
	ans++;
	vis[h][x][y]=1;
	for(int i=1;i<=6;i++){
		int xx=x+dx[i],yy=y+dy[i],hh=h+dh[i];
		if(hh<1||hh>k||yy<1||yy>m||xx<1||xx>n||
		vis[hh][xx][yy]==1||dis[hh][xx][yy]=='#') continue;
		dfs(hh,xx,yy,step+1);
	}
}

int main()
{
	int x,y;
	cin>>k>>n>>m;
	for(int kk=1;kk<=k;kk++){
		for(int nn=1;nn<=n;nn++)
			for(int mm=1;mm<=m;mm++)
				cin>>dis[kk][nn][mm];
		if(kk!=k) getchar();
	}
	cin>>x>>y;
	dfs(1,x,y,0);
	cout<<ans;
    return 0;
}

```


---

## 作者：HyGeoIceFairy (赞：1)

我来做做CF的题，好像是第一篇题解吧……


------------


## 本题思路：搜索


废话少说，直接上代码再讲

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
char p[11][11][11];//储存数据
int k,m,n,ans,x,y;
void dfs(int a,int b,int c)//搜索函数a,b,c分别代表高,长,宽(k,m,n)
{
	if(a<0||a>=k||b<0||b>=m||c<0||c>=n||p[a][b][c]=='#')//判断边界与阻碍
	{
		return;
	}
	p[a][b][c]='#';//更改状态
	++ans;//计数器加1
	dfs(a,b-1,c);
	dfs(a,b,c-1);
	dfs(a,b+1,c);
	dfs(a,b,c+1);
	dfs(a+1,b,c);
	dfs(a-1,b,c);//6个方向的搜索
	return;
}
int main()
{
	scanf("%d%d%d",&k,&m,&n);
	for(register int i=0;i<k;++i)
	{
		for(register int j=0;j<m;++j)
		{
			scanf("%s",p[i][j]);
		}
	}
	scanf("%d%d",&x,&y);//输入,这里注意,从0开始输入,所以处理边界与搜索时要当心
	dfs(0,x-1,y-1);//上面说的一个注意点
	printf("%d",ans);//输出
	return 0;//完美结束
}
```

后记:只有这种题对于我来说会做力,太蒻力

---

## 作者：天亮codekiller (赞：0)

## 作者注：
这题说的不好，应该是水能到达的点的个数，说时间容易给人以 $1$ 秒灌满 $6$ 个格子的错觉。
# 思路：
一个简单的广搜，不会的戳这里： [广搜简介](https://blog.csdn.net/acm147258369/article/details/88562558?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522163629438416780255265851%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=163629438416780255265851&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-88562558.first_rank_v2_pc_rank_v29&utm_term=%E5%B9%BF%E6%90%9C&spm=1018.2226.3001.4187) 

 只不过，这道题要将方向设成三维，别的就没什么了。

具体内容见注释。

提供 AC 代码（我知道你们最关心这个）：
```cpp
#include<cstdio>//建议不用万能头，提高效率 
#include<queue>//广搜必备的数据结构 
using namespace std;
int n,m,k;//k层数,n长,m宽 
int ans;
int sx,sy;//输入的第一层的x,y坐标 
int dx[6]={0,0,0,0,1,-1};//x方向 
int dy[6]={0,0,1,-1,0,0};//y方向 
int dh[6]={1,-1,0,0,0,0};//h方向 
char a[15][15][15];//记录地图 
char read(){//快读char 
	char ch=getchar();
	while(ch!='.'&&ch!='#')ch=getchar();//如果不是地图中出现的字符，则说明输入了换行或空格 
	return ch; 
}
signed main(){
	scanf("%d%d%d",&k,&n,&m);
	for(int a1=1;a1<=k;a1++)
		for(int a2=1;a2<=n;a2++)
			for(int a3=1;a3<=m;a3++)
				a[a1][a2][a3]=read();//用read读入，可以提高效率。 
	scanf("%d%d",&sx,&sy);
	queue<int> qx,qy,qh;
	qh.push(1);
	qx.push(sx);
	qy.push(sy);
	a[1][sx][sy]='#';//标记为访问过，防止重复 
	while(!qx.empty()){//广搜框架 
		int h=qh.front(),x=qx.front(),y=qy.front();
		qx.pop(),qy.pop(),qh.pop();//出队 
		++ans;//统计答案 
		for(int i=0;i<6;i++){
			int th=h+dh[i],tx=x+dx[i],ty=y+dy[i];
			if(th<=k&&th>=1&&tx>=1&&tx<=n&&ty>=1&&ty<=m&&a[th][tx][ty]=='.'){//不出界并且可以访问 
				qh.push(th);
				qx.push(tx);
				qy.push(ty);
				a[th][tx][ty]='#';//在这里标记，可避免TLE和MLE！！！（血泪的教训） 
			}
		}
	}
	printf("%d",ans);//输出答案 
	return 0;//不要用Ctrl+C+V，做诚信的人。 
}
//再见！ 
```
本蒟蒻的第一篇题解，希望对大家有用。

---

## 作者：WinterRain208 (赞：0)

题解 CF60B

### 题意

这题翻译背了很大的锅，导致我一时间没有看懂样例。。。

给你一个大小为 $n * m * k$ 大小的三维矩阵，给你两个数$x,y$，求坐标 $(1,x,y)$ 所在的三维矩阵连通块大小。

### 做法

暴搜即可，dfs或bfs随意，数据放的非常宽，从给定坐标开始，如果周围六个个格子中有能够到达的，就往那个格子搜。

对于每个能到达的格子，给计数器加一即可。

代码（大法师）：

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;
const int N=15+5;

int n,m,k,x,y,ans=0;
char a[N][N][N];

void dfs(int h,int x,int y){
	++ans;
	a[h][x][y]='#';
	if(a[h+1][x][y]=='.')dfs(h+1,x,y);
	if(a[h-1][x][y]=='.')dfs(h-1,x,y);
	if(a[h][x+1][y]=='.')dfs(h,x+1,y);
	if(a[h][x-1][y]=='.')dfs(h,x-1,y);
	if(a[h][x][y+1]=='.')dfs(h,x,y+1);
	if(a[h][x][y-1]=='.')dfs(h,x,y-1);
}

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	memset(a,'#',sizeof(a));
	cin>>n>>m>>k;
	F(i,1,n)F(j,1,m)F(s,1,k)cin>>a[i][j][s];
	cin>>x>>y;a[1][x][y]='.';
	dfs(1,x,y);
	cout<<ans<<endl;
	return 0;
}
```

完结撒花。。。。


---

## 作者：ahawzlc (赞：0)

思路：~~暴力~~搜索

---

就和大多数迷宫类问题相似，只不过这个是三维的。

众所周知，迷宫问题的基本搜索形式就是标记当前点已走过，然后从当前点向能够扩展到的点递归。二维迷宫就是$dfs(x\pm1,y),dfs(x,y\pm1)$，三维就在原来基础上加上$z$，也就是$dfs(x\pm1,y,z),dfs(x,y\pm1,z),dfs(x,y,z\pm1)$。递归边界显然，就是不出地图和能走动。

为了方便，我们提前预处理出走的这六步，也就是下面代码中的```dx[],dy[],dz[]```。

Coding Time

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=15;
const int dx[7]={0,1,-1,0,0,0,0},dy[7]={0,0,0,1,-1,0,0},dz[7]={0,0,0,0,0,1,-1};//预处理出走的方向
char ch[N][N][N];
bool vis[N][N][N];
int n,m,k,u,v,t;
bool check(int x,int y,int z) {
	if(x<1||x>n||y<1||y>m||z<1||z>k) return 0;//超出边界
	if(vis[x][y][z]||ch[x][y][z]-'.') return 0;//此路不通
    //ch[x][y][z]-'.'等同于ch[x][y][z]!='.'
	return 1;
}
void dfs(int x,int y,int z) {
	++t;//统计答案
	vis[x][y][z]=1;//标记走过
	for(int i=1;i<=6;i++) {
		int xx=x+dx[i],yy=y+dy[i],zz=z+dz[i];//走一步
		if(check(xx,yy,zz)) dfs(xx,yy,zz);//可行的话搜索下一层
	}
	return;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);//读入优化
	cin>>k>>n>>m;
	for(int l=1;l<=k;l++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++) 
				cin>>ch[i][j][l];//读入地图
	cin>>u>>v;
	dfs(u,v,1);//开始搜索
	cout<<t;
	return 0;
}

```

---

