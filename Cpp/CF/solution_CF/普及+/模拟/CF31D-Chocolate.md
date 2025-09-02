# Chocolate

## 题目描述

Bob has a rectangular chocolate bar of the size $ W×H $ . He introduced a cartesian coordinate system so that the point $ (0,0) $ corresponds to the lower-left corner of the bar, and the point $ (W,H) $ corresponds to the upper-right corner. Bob decided to split the bar into pieces by breaking it. Each break is a segment parallel to one of the coordinate axes, which connects the edges of the bar. More formally, each break goes along the line $ x=x_{c} $ or $ y=y_{c} $ , where $ x_{c} $ and $ y_{c} $ are integers. It should divide one part of the bar into two non-empty parts. After Bob breaks some part into two parts, he breaks the resulting parts separately and independently from each other. Also he doesn't move the parts of the bar. Bob made $ n $ breaks and wrote them down in his notebook in arbitrary order. At the end he got $ n+1 $ parts. Now he wants to calculate their areas. Bob is lazy, so he asks you to do this task.

## 样例 #1

### 输入

```
2 2 2
1 0 1 2
0 1 1 1
```

### 输出

```
1 1 2 ```

## 样例 #2

### 输入

```
2 2 3
1 0 1 2
0 1 1 1
1 1 2 1
```

### 输出

```
1 1 1 1 ```

## 样例 #3

### 输入

```
2 4 2
0 1 2 1
0 3 2 3
```

### 输出

```
2 2 4 ```

# 题解

## 作者：CarroT1212 (赞：7)

翻了一下题解，似乎暂时没有不用搜索过掉这题的，那我就来一篇吧。

------------

注意题目的这句话：

> 保证切完以后不存在只被切了一部分的巧克力。即对于任意一部分巧克力内部不存在刀口。

换句话说就是，保证切完之后分成的每个部分的巧克力都是一个完整的矩形，且内部不存在刀口。

所以，这题用不着搜索。

我们可以把这块巧克力抽象成一个 $H \times W$ 的格阵，然后开两个二维数组 $a,b$，$a_{i,j}$ 表示第 $(i,j)$ 个格子的下方是否有刀口，$b_{i,j}$ 表示第 $(i,j)$ 个格子的右方是否有刀口。存的方法很简单，输入每一刀的时候分两种情况遍历一下就可以了，不细说。

然后我们开一个二维数组 $c$ 表示一个格子有没有被遍历过，再从左上到右下同时遍历这两个二维数组，每次到一个新的格子，我们就向一个格子一个格子地在 $b$ 中向右找最近的刀口，找到之后再一个格子一个格子地在 $a$ 中向下找最近的刀口，都找到了，就可以确定我们正在遍历的这个部分的长、宽和位置了，再然后记录一下答案，再把这个矩阵里的所有格子都标记为遍历过即可。

最后给答案排一下序输出就完事了。

由于 $n,W,H \le 100$，且“保证切完之后分成的每个部分的巧克力都是一个完整的矩形，且内部不存在刀口”，这个解法一定是正确的。

但是，如果题目里没有做这个保证的话，我们就只能用搜索算答案了，因为你遍历到的刀口不一定能把你正在遍历的部分分成两块。

------------

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rnt register long long
using namespace std;
const ll N=107;
ll n,m,t,tot;
ll hang[N][N],lie[N][N],ans[N*N],bkt[N][N];
int main() {
	cin>>n>>m>>t;
	while (t--) {
		ll r1,r2,r3,r4;
		cin>>r1>>r2>>r3>>r4;
		if (r1==r3) { //分两种情况，第一种是沿着行切
			for (rnt i=r2+1;i<=r4;i++) hang[r1][i]=1; //标记上文中的 a 数组
		}
		else if (r2==r4) { //第二种是沿着列切
			for (rnt i=r1+1;i<=r3;i++) lie[i][r2]=1; //标记上文中的 b 数组
		}
	}
	for (rnt i=1;i<=n;i++) {
		for (rnt j=1;j<=m;j++) {
			if (!bkt[i][j]) { //如果这个格子没被遍历过
				ll r1=i,r2=j,r3=1,r4=1; //r1,r2 为遍历时使用变量，r3,r4 记录这个部分的长和宽
				while (lie[r1][r2]==0&&r2<m) r2++,r4++; //向右找
				while (hang[r1][r2]==0&&r1<n) r1++,r3++; //向下找
				for (rnt u=i;u<=r1;u++) {
					for (rnt v=j;v<=r2;v++) bkt[u][v]=1; //这个部分的格子全部做标记
				}
				ans[++tot]=r3*r4;
			}
		}
	}
	sort(ans+1,ans+tot+1);
	for (rnt i=1;i<=tot;i++) cout<<ans[i]<<" ";
	return 0;
} 
```

---

## 作者：Tune_ (赞：4)

翻翻大佬们的题解，好像没有我这种方法的呢~

可以先标记是否联通，再洪水搜索。

可以用一个三维数组标记：

```
a[i][j][k]
k=1:上
k=2:右
k=3:下
k=4:左

当a[i][j][1]=1,就表示它上方被切了。
```
这是最简单的。

当然，也可以用二维数组，节省空间，这时就要用到位运算：

```
a[i][j]
+1:上
+2:右
+4:下
+8:左

当a[i][j]=9,就表示它上方和左边被切了。

在搜索过程中，可以用‘&’（与运算）来判断是否包含1、2、4、8。
```
具体操作方法，参考下面代码注释：

```
#include<bits/stdc++.h>
using namespace std;
int a[105][105]={0},b[105][105]={0},w,h,xs,ys,xf,yf,n,ans[10005],s=0;//a标记是否联通，b标记是否走过
void dfs(int x,int y)//发洪水啦~
{
	if(b[x][y])
		return;
	ans[s]++;
	b[x][y]=1;
	if(!(a[x][y]&1))//上
		if(x-1>=0)
			dfs(x-1,y);
	if(!(a[x][y]&2))//右
		if(y+1<h)
			dfs(x,y+1);
	if(!(a[x][y]&4))//下
		if(x+1<w)
			dfs(x+1,y);
	if(!(a[x][y]&8))//左
		if(y-1>=0)
			dfs(x,y-1);
}
int main()
{
	cin>>w>>h>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>xs>>ys>>xf>>yf;
		if(xs==xf)//横着切
		{
			if(ys>yf)//有可能反了
				swap(ys,yf);
			for(int j=ys;j<yf;j++)//标记不能走	
		 		a[xs][j]+=1,a[xs-1][j]+=4;	
		}
		if(ys==yf)//竖着切
		{
			if(xs>xf)
				swap(xs,xf);
		 	for(int j=xs;j<xf;j++)//标记不能走
		   		a[j][ys]+=8,a[j][ys-1]+=2;
		}
	}
	for(int i=0;i<w;i++)
	for(int j=0;j<h;j++)
	{
		if(b[i][j]==0)//如果是一块新的巧克力（没搜过的）
		{
			s++;
			dfs(i,j);
		}
	}
	sort(ans+1,ans+s+1);//记得排序~
	for(int i=1;i<=s;i++)
		cout<<ans[i]<<" ";
	return 0;//大功告成~
}
```

走过路过，点个赞鸭~(〃'▽'〃)~

---

## 作者：gary2005 (赞：4)

首先拿到这题我想到的总体思路就是先将一块巧克力划分成许多块然后用DFS算出每个联通块的面积。


------------

首先画一个3*3的巧克力

![undefined](https://cdn.luogu.com.cn/upload/pic/44511.png)

然后将他的线条也转换为方格

并且放入直角坐标系中
（横坐标为0~2*w，纵坐标为0~2*h）
![undefined](https://cdn.luogu.com.cn/upload/pic/44510.png)
现在按题目要求画一个2*2的巧克力，
并按照题目描述切好。（注：由于算上了棕色格子所以线条的坐标是原来的两倍，也就是从1 0 切到1 2变成从2 0切到2 4）
![undefined](https://cdn.luogu.com.cn/upload/pic/44509.png)
这个时候用1代表切割的线条用2代表线条再统计出0（巧克力）的联通块即可，（注：将统计过的巧克力0变为3，防止重复统计）

输出大概就是这样
![undefined](https://cdn.luogu.com.cn/upload/pic/44515.png)


------------

好了现在附上代码

```
#include<cstdio>
#include<algorithm>
using namespace std;
int w,h,n,startx,starty,finalx,finaly,walls[300][300]={0},tempans,ans[10010]={0};
void dfs(int x,int y){
	if(x<0||y<0||x>h+h||y>w+w) return;//边界 
	if(walls[x][y]==1||walls[x][y]==3) return;
	if(walls[x][y]==0)//空地 
	tempans++;
	walls[x][y]=3;//已经遍历 
	dfs(x+1,y);
	dfs(x,y+1);
	dfs(x-1,y);
	dfs(x,y-1);
	return;
}
int main(){
	scanf("%d %d %d",&h,&w,&n);
	for(int i=1;i<=n;i++){
		scanf("%d %d %d %d",&startx,&starty,&finalx,&finaly);
		startx+=startx;
		starty+=starty;
		finalx+=finalx;
		finaly+=finaly;
		if(startx==finalx){
			for(int i=starty;i<=finaly;i++)	walls[startx][i]=1;//walls 
		}
		else{
			for(int i=startx;i<=finalx;i++) {walls[i][starty]=1;//walls
			}
			
		}
	}
	for(int i=0;i<=h+h;i++){
		if(i%2==0)//偶数行
		{
			for(int j=0;j<=w+w;j++) if(walls[i][j]==0) walls[i][j]=2;
		 } 
		else{
			for(int j=0;j<=w+w;j++) if(walls[i][j]==0&&j%2==0) walls[i][j]=2;
		}
	}
	for(int i=0;i<=h+h;i++)
	for(int j=0;j<=w+w;j++){
		tempans=0;dfs(i,j);
		ans[tempans]++;
	} 
	for(int i=1;i<=w*h;i++) for(int j=1;j<=ans[i];j++) printf("%d ",i);
	return 0;
}
```


---

## 作者：CrTsIr400 (赞：2)

这道题看似复杂，但是可以把它**转化**成一个**矩阵**。

![](https://cdn.luogu.com.cn/upload/image_hosting/m851x0pi.png)

$(0,0)$ 是**原点**，然后别的点和**正常的二维数组**一样存储。

删除多块巧克力，可以枚举块数，再**删除单块**的**公共边**。

![](https://cdn.luogu.com.cn/upload/image_hosting/o57ona8g.png)

~~我从 $(0,2)$ **点**开始，大刀一挥，嘿，把上下两份劈开来了，一直到 $(3,2)$ **点**才抬起刀来（~~

其实就是我要从 $(0,2)$ **点**开始**删除**边一直到 $(3,2)$ **点**结束。

被删除**公共边**的，是从**起始横坐标 $+1$** 一直到**终点横坐标** 所分割开来在分割线两侧的**节点**。

竖着删除也一样，只要把 **横坐标** 三个字改成 **纵坐标** 就可以了。

~~不就**暴力枚举**每个**这条线段所经过的**节点吗（~~

接下来讨论如何**删除**。

![](https://cdn.luogu.com.cn/upload/image_hosting/ksypg0gz.png)

假设我要~~锯~~**删除**掉 $(1,2)$ 和 $(2,2)$ 之间的**公共边**，该如何处理？

我们可以先**预处理**出每个节点**上下左右有公共边的**附近节点。

![](https://cdn.luogu.com.cn/upload/image_hosting/bxne1ogf.png)

就像是这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/ksypg0gz.png)

如果要锯掉 $(1,2)$ 和 $(2,2)$ **之间的公共边**，该怎么锯呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/5sp8h05c.png)

不难。只需把 $(1,2)$ 节点的**底边去掉，** 把 $(2,2)$ 节点的**顶边去掉**，就可以完成单点删除了。

然后在删完所有边的图上**洪水填充**一下，把所有连通块的面积排一下序，就完成任务啦！

## **注意事项**：

- **不要把洪水填充的代码写错！**

- **要交换边的 $x$ 和 $y$ !**

- **要交换行列 $n$ 和 $m$ ！**

然后就可以放心AC啦！

## **部分代码：**

**洪水填充：**

```cpp
int dfs(int x,int y,int color)
{
	int sum=1;
	b[x][y]=color;
	if(x>1&&a[x][y].u&&!b[x-1][y])sum+=dfs(x-1,y,color);
	if(x<n&&a[x][y].d&&!b[x+1][y])sum+=dfs(x+1,y,color);
	if(y>1&&a[x][y].l&&!b[x][y-1])sum+=dfs(x,y-1,color);
	if(y<m&&a[x][y].r&&!b[x][y+1])sum+=dfs(x,y+1,color);
	return sum;
}
```

**删除单边：**

```cpp
void cut(int sx,int sy,int ex,int ey)
{
	if(sx>ex)swap(sx,ex);
	if(sy>ey)swap(sy,ey);
	if(sx==ex)
	Fu(i,1+sy,ey)
	{
		a[sx][i].d=0;
		a[sx+1][i].u=0;	
	}
	else
	Fu(i,1+sx,ex)
	{
		a[i][sy].r=0;
		a[i][sy+1].l=0;
	}
}
```

**预处理：**

```cpp
Fu(j,1,m)
{
	if(i>1)a[i][j].u=i-1;
	if(i<n)a[i][j].d=i+1;
	if(j>1)a[i][j].l=j-1;
	if(j<m)a[i][j].r=j+1;
}
```

---

## 作者：A_small_WA (赞：1)

## 一.题意简述：

理解起来变更不是很难，即有一个 $W\times H$ 的矩形，水平或竖直切 $n$ 刀，求切完以后每一块的面积。

## 二.具体思路：

发现两点：第一，切完以后的图形不一定是矩形（可能出现不规则的方块）。第二，切完之后的图形一定由多个连通块组成。

注意到第二点，于是想到用 dfs 去求每个连通块的面积，但由于图形由方格和边组成，因此不能直接 dfs，需要前置操作将每一条切割的边体现出来。

我们可以把切割的线条单独算一格，即 $2\times 3$ 的图就由
```
000
000
```
变成了：
```
0|0|0
-+-+-
0|0|0
```
这样，在 dfs 时就可以根据 $(x+1,y)$ 格有没有线来判断 $(x,y)$ 格与 $(x+2,y)$ 格是否连通了。（其实就是将坐标翻倍）

## 三.代码实现：

说了半天，上面的都是废话，这道题最难的地方在于处理坐标位置。因为我们提前对坐标做了处理，所以切割时就不是那么简单了，需要找到复杂的规律。

```
0,0   0,1   0,2

1,0   1,1   1,2

2,0   2,1   2,2
```
如图，以样例一为例，先来看横切。由 $(1,0)\sim(1,2)$ 且的一刀在这个坐标系中对应的是 $(1,0),(1,1),(1,2)$。经过观察（需要再多举几个例子）可以发现，横切（即 $x0=x1$ 时），应将 $(x0\times2-1,y0),(x0\times2-1,y0+1),(x0\times2-1,y0+2)  \dots (x0\times2-1,y1)$ 这段方格做上标记，变为不通路。

同理，竖切（即 $y0=y1$ 时）应将 $(x0,y0\times2-1),(x0+1,y0\times2-1),(x0+2,y0\times2-1) \dots (x1,y0\times2-1)$ 这段方格做上标记，变为不通路。

代码：
```cpp
for(int i=1;i<=n;i++){
		cin>>xo>>yo>>xi>>yi;
		if(xo==xi){
			//横坐标相等，横着切。
			for(int j=min(yo,yi)*2;j<=max(yo,yi)*2-1;j++){
        //防止有开始坐标小于结束坐标的数据。
				a[xo*2-1][j]=-1;
			} 
		}else if(yo==yi){
			//反之，竖着切。 
			for(int j=min(xo,xi)*2;j<=max(xo,xi)*2-1;j++){
				a[j][yo*2-1]=-1;
			} 
		}
	}
```

处理完这部分操作后，剩下的 dfs 部分就简单了，注意这里通过不断往深处递归求出每一块的面积而不能只把连通块的个数数出来。

代码：
```cpp
int dfs(int x,int y,int bs){
	if(x<0||y<0||x>2*w-2||y>2*h-2) return bs;
  //判断边界
	a[x][y]=-1;
  //走过的路不能重复走，用-1标记
	bs++;
	if(a[x+1][y]!=-1&&a[x+2][y]!=-1){
		bs+=dfs(x+2,y,0);
	}
	if(a[x-1][y]!=-1&&a[x-2][y]!=-1){
		bs+=dfs(x-2,y,0);
	}
	if(a[x][y+1]!=-1&&a[x][y+2]!=-1){
		bs+=dfs(x,y+2,0);
	}
	if(a[x][y-1]!=-1&&a[x][y-2]!=-1){
		bs+=dfs(x,y-2,0);
	}
	return bs;
}
```

这里函数用 `int` 而不用 `void` 的原因是，更方便递推。

## 四.后记：

有几点感想：

1. Codeforces 给的样例是真抽象啊，让我抓不着头脑地 WA 在第四个测试点想了一个小时。于是，好心的我为你们提供一组测试数据：

输入：
```cpp
5 5 4
0 1 3 1
3 1 3 3
0 3 3 3
2 3 5 3
```
输出：
```
6 9 10
```
2. 这道题告诉我，在思维难度较大的时候，不要着急，可以拿笔把图画出来，规律自然就会推了。

3. 你知道吗，我开始时甚至切割时坐标没有 $\times2$。

4. 很难想象 dfs 是如何在 $W=H=100$ 的情况下通过的。

这是蒟蒻的第 $9$ 篇题解，支持一下孩子吧！

---

## 作者：Peaky (赞：0)

按照惯例，应该先有[传送门](https://www.luogu.com.cn/problem/CF31D)。
### 题目大意
简化一下题目。  
有一个 $W\times H$ 的矩形，通过 $n$ 次分割分成若干个矩形，问你这若干个矩形的面积。$(1\le W,H\le100)$

### 思路
四肢发达头脑简单的方法。  
对于每一次分割都统计一下哪两格被分开了，那么这两个将无法相互到达，再跑一遍找连通块，统计每一个连通块的大小。

### AC code
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=2e2+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
int w,h,n,ans[N],k,dx[]={1,0,-1,0},dy[]={0,1,0,-1};
bool visx[N][N][N],visy[N][N][N],fl[N][N];
void dfs(int x,int y){
	fl[x][y]=1;
	ans[k]++;
	for(int i=0;i<4;i++){
		int nx=x+dx[i],ny=y+dy[i];
		if(nx<1||ny<1||nx>w||ny>h||fl[nx][ny]||(x==nx&&visx[x][min(y,ny)][max(y,ny)])||(y==ny&&visy[y][min(x,nx)][max(x,nx)])) continue;
		dfs(nx,ny);
	}
}
int main(){
	cin>>w>>h>>n;
	for(int i=1;i<=n;i++){
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		if(x1==x2) for(int i=y1+1;i<=y2;i++) visy[i][x1][x1+1]=1;
		if(y1==y2) for(int i=x1+1;i<=x2;i++) visx[i][y1][y1+1]=1;
	}
	for(int i=1;i<=w;i++) for(int j=1;j<=h;j++) if(!fl[i][j]) k++,dfs(i,j);
	sort(ans+1,ans+k+1);
	for(int i=1;i<=k;i++) cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

bfs。

## 思路

总体来说：暴力删边，暴力搜索。

### 删边

首先不难发现：

（注意下面的图左上角的格子是 $(1,1)$，左上角的顶点是 $(0,0)$）

![](https://cdn.luogu.com.cn/upload/image_hosting/ulpjxvv8.png)

切掉一条横向边相当于把这条线上面的点和下面的点的连接切断了。

具体来说，我们假设这条线段的横坐标为 $x$，纵坐标区间为 $[l,r]$，那么对于任意正整数 $i\in[l+1,r]$，都要切断 $(x,i)$ 和 $(x+1,i)$ 的连接。

如果这条线段是纵向的，同理，设这条线段的纵坐标为 $y$，横坐标区间为 $[l,r]$，那么对于任意正整数 $i\in[l+1,r]$，都要切断 $(i,y)$ 和 $(i,y+1)$ 的连接。

那么问题转移到了如何实现删边上。

我们可以开一个数组 $g$（后文的代码中为 `go`），其中 $g_{i,j,k}$ 表示点 $(i,j)$ 向方向 $k$ 能否通行，$1$ 代表不行，$0$ 代表可以。$k\in[1,4]$，当 $k$ 等于以下值是方向分别是：

- $k=1$，向右。
- $k=2$，向左。
- $k=3$，向上。
- $k=4$，向下。

有了这个数组之后，不难发现切断横向边就是假设这条线段的横坐标为 $x$，纵坐标区间为 $[l,r]$，那么对于任意正整数 $i\in[l+1,r]$，都要使 $g_{x,i,4}=1$ 且 $g_{x+1,i,3}=1$。纵向同理。

然后暴力 bfs 即可。因为每个点至多遍历一次，所以是 $\operatorname{O}(n^2)$ 的。

```
#include<bits/stdc++.h>
using namespace std;
int n,m,q,go[505][505][5],vis[505][505],cnt,ans[250005],sum;
const int dx[5]={0,0,0,-1,1};
const int dy[5]={0,1,-1,0,0};
queue<int>q1,q2;
void bfs(int x,int y){
	q1.push(x);
	q2.push(y);
	vis[x][y]=1;
	while(!q1.empty()){
		x=q1.front();
		y=q2.front();
		sum++;
		q1.pop();
		q2.pop();
		for(int i=1;i<=4;i++){
			if(go[x][y][i])continue;
			int nx=x+dx[i],ny=y+dy[i];
			if(nx<=0||nx>n||ny<=0||ny>m)continue;
			if(vis[nx][ny])continue;
			vis[nx][ny]=1;
			q1.push(nx);
			q2.push(ny);
		}
	}
}
int main(){
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++){
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		if(x1==x2){
			for(int j=y1+1;j<=y2;j++){
				go[x1][j][4]=1;
				go[x1+1][j][3]=1;
			}
		}
		else{
			for(int j=x1+1;j<=x2;j++){
				go[j][y1][1]=1;
				go[j][y1+1][2]=1;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!vis[i][j]){
				bfs(i,j);
				ans[++cnt]=sum;
				sum=0;
			}
		}
	}
	sort(ans+1,ans+cnt+1);
	for(int i=1;i<=cnt;i++)if(ans[i]!=0)cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：Empty_Dream (赞：0)

## 题意

给你一个长 $W$ 宽 $H$ 的矩形，其中左下角为 $(0,0)$，右上角为 $(W,H)$。

之后给你一个 $n$ 表示切多少刀，每一刀给出起始坐标和结束坐标，**不一定从头切到尾**。

## 分析

先说一下，这里可以看作一个个方格连接起来，下面说的坐标是方格的，而每一刀的坐标是边上的，需要转换一下把边转到方格上。可以自行画图理解。

先来看每一刀，针对这个数据范围，可以直接去标记被切的那一列或行附近的方格不能朝这里走。具体的，定义一个三维数组 $vis1_{i,x,y}$，第一维表示方向，第二、三维表示坐标，如果为 $1$ 那么 $(x,y)$ 不能走 $i$ 方向（和方向数组对应）。

接下来核心部分，考虑到要求每一部分的大小，并且与棋盘图上的搜索类似，可以直接当连通块来做，具体不在此赘述。最后排序输出。

注意，一条边会导致两个方向不能走过来，$vis1$ 要在两个方向进行更新，注意两点坐标差异。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int w, h, n, cnt, len;
int x1, y1, x2, y2;
int vis[105][105], vis1[4][105][105];
vector<int> v;

void dfs(int x, int y){
	cnt++;
	vis[x][y] = 1;
	for (int i = 0; i < 4; i++){
		int nx = x + dx[i], ny = y + dy[i];
		if (nx > 0 && nx <= w && ny > 0 && ny <= h && vis[nx][ny] == 0 && vis1[i][x][y] == 0) dfs(nx, ny);
	}
}

int main(){
	scanf("%d%d%d", &w, &h, &n);
	for (int i = 1; i <= n; i++){
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (x1 == x2){//处理行
			for (int j = y1 + 1; j <= y2; j++) vis1[1][x1][j] = vis1[3][x1 + 1][j] = 1;//边转方格
		}
		else{//处理列
			for (int j = x1 + 1; j <= x2; j++) vis1[0][j][y1] = vis1[2][j][y1 + 1] = 1;
		}
	}
	for (int i = 1; i <= w; i++){
		for (int j = 1; j <= h; j++){
			if (vis[i][j] == 0){
				cnt = 0;//连通块大小
				dfs(i, j);//标记连通块
				v.push_back(cnt);
			}
		}
	} 
	sort(v.begin(), v.end());//排序输出
	for (int i = 0; i < v.size(); i++) printf("%d ", v[i]);
	return 0;
}
```

---

