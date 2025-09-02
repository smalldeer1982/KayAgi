# Chessboard Billiard

## 题目描述

Let's imagine: there is a chess piece billiard ball. Its movements resemble the ones of a bishop chess piece. The only difference is that when a billiard ball hits the board's border, it can reflect from it and continue moving.

More formally, first one of four diagonal directions is chosen and the billiard ball moves in that direction. When it reaches the square located on the board's edge, the billiard ball reflects from it; it changes the direction of its movement by 90 degrees and continues moving. Specifically, having reached a corner square, the billiard ball is reflected twice and starts to move the opposite way. While it moves, the billiard ball can make an infinite number of reflections. At any square of its trajectory the billiard ball can stop and on that the move is considered completed.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF74C/2b32b43a6cf594e055f4f908960d44aaa5bece14.png)It is considered that one billiard ball $ a $ beats another billiard ball $ b $ if $ a $ can reach a point where $ b $ is located.

You are suggested to find the maximal number of billiard balls, that pairwise do not beat each other and that can be positioned on a chessboard $ n×m $ in size.

## 样例 #1

### 输入

```
3 4
```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3
```

### 输出

```
3```

# 题解

## 作者：Abeeel51 (赞：5)

真是一道大水题

简单考虑一下就是反弹是有规律的。

就像切一刀一样把重复部分切掉，翻个面，继续切。

直到是一个正方形的时候上面整个一排是都可以布满的。

然后就可以考虑到使用辗转相除，因为切除重复部分的过程就是一个辗转相除的过程。

接下来算几组样例，凑一下数，考虑一下就能出来式子：

$ans=\gcd(n-1,m-1)+1$

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int GCD(int a,int b){return b==0?a:GCD(b,a%b);}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    printf("%d\n",GCD(n-1,m-1)+1);
    return 0;
}
```

结束了！

---

## 作者：Air_Color5 (赞：4)

## 题目大意
给你一个 $n\times m$ 大小的棋盘。你可以往上面放一些“象”（就是说这些棋子都是斜着走的），这些象会朝着一个方向走（方向随便），碰到边缘就转 90° ，碰到角就转 180° ，在确保任何两个棋子都不能互相到达的情况下，求最多可以放置多少个象。
### 注意
这里所说的“不能互相到达”指的是在一个棋子不动的情况下，能否到达另一个棋子。

若两棋子的移动路线有重合，但是并不代表它们能互相到达。（即路线不完全重合，只是交叉）
## 解析
### 数据类型
当时我看到这道题之后，第一反应是二维数组。但是 $2\le n,m\le1000000$ ，所以显然二维数组是存不下的。那么，到底用什么存比较合适呢？我们在下面的分析中会讲到。

让我们来看一个稍微复杂一点的例子：
![一个 7 * 10 的棋盘](https://cdn.luogu.com.cn/upload/image_hosting/yyj5e6b5.png)

这是一个 $7\times10$ 的棋盘，我们用了红、蓝、黄、绿四种颜色标记出了图中存在的四条路线。因此，这个图里最多能放置 $4$ 个棋子。

可能各位已经发现了，如果观察这幅图的最后一行（或者第一行）的话，**边上的颜色数量已经足以代表整幅图的颜色数量**。也就是说，我们只需要看一条边就行了。而**那一条边的颜色数量即为答案**。如果再仔细观察的话，我们还会发现，边上颜色的出现是按照回文顺序排列的（红，蓝，黄，绿，黄，蓝，红……），这一点后面会用到。

（关于为什么只要数边上的颜色数量就行，我这里就不证明了，各位可以自己理解一下）

也就是说，我们用一个最多 $1000000$ 位的数组去存其中一行即可。
### 思路
有了刚才的分析，现在这道题目变得容易多了。那么我们该如何知道边上的点都是什么颜色的呢？

~~（由于我是萌新，还比较菜，所以没有想到什么能一步判断出来的方法）~~
我们不妨可以**模拟棋子的移动轨迹**，如果棋子到达了我们指定的那一条边，那么我们就可以知道棋子所在的格子的颜色了。每一个棋子在回到初始位置之后，就停止模拟。在模拟结束之后，将记录颜色的那个变量加一，即可代表换了一种颜色。

大致的思路已经想好了，然后就是开始和结束条件的细节问题了。在开始的时候，我们把所有棋子都**摆放在我们指定的那一条边上**，因为这样会比放在别的地方更方便一些。结束条件就是，因为最后一行（或者第一行）的颜色成回文状，所以**当我们准备放置棋子的那一格已经有棋子了，那么就说明这一行已经都被占满了**，数一下颜色数量，输出即可。
### 算法
在这道题目中，如果我们在模拟棋子运动的时候，用两个变量代表坐标，一格一格地移动的话，很明显在数据比较大的时候会 Time Limit Exceeded 的 ~~（我第一次提交就 TLE 了）~~ 所以我们在模拟的时候，要“一步到边”，通过一次计算就让棋子的坐标移动到一个不得不改变棋子运动方向的地方。我们可以设置两个变量 $dx$ 和 $dy$，代表横（纵）坐标的移动方向。如果变量为 $1$ ，则下一步棋子在横（纵）坐标上就往右（下）方向挪动，反之，即变量为 $-1$ ，向左（上）方向移动。另外，因为我们是斜着走的，所以两个坐标变量 $x$ , $y$ 改变的数字应该是一样的，因此这个数字要取横（纵）坐标上离边缘的距离的最小值。（不然另外一个坐标可能就越界了）
```cpp
int nx,ny;//横（纵）坐标上离边缘的距离
if(dx==1)nx=m-1-x;//如果在往右走
else nx=x;//反之，在往左走
if(dy==1)ny=n-1-y;//如果在往下走
else ny=y;//反之，在往上走
```
移动步数即取 $\min(nx,ny)$ 即可。
## AC代码
如果刚才的分析有点“纸上谈兵”的感觉的话，接下来我们在代码中配合理解。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000006],col,ans;
// n 和 m 就不多说了
//数组 a 就是选定的那条边（这里是最后一行）
// col 为 color ，即为标记的颜色
// ans 为答案
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;a[i]==0&&i<m;i++){
    //循环，直到数组被填满
		col++;//换下一个颜色
		a[i]=col;//放置棋子的初始点标记
		ans++;//答案+1,因为多了一种颜色
		int y=n-2,x=i,dy=-1,dx=1;
        //dy,dx为方向，y,x为坐标
        //因为在最后一行，只能往上走
        //所以y=n-1-1=n-2（为了离开初始位置）
		if(x==m-1)dx=-1;
        //我们假定所有棋子都往右上方走
        //因为之前定义的是 dy=-1,dx=1
        //但是如果刚好在右下角的话
        //就只能往左上方走
		x+=dx;//x也离开初始位置
		while(y!=n-1||x!=i){//如果没回到原点
			if(x==m-1||x==0)dx=-dx;
            //如果到了最左/最右边
            //反弹（左右方向交换）
			if(y==n-1||y==0){
            //如果到了最上/最下边
				dy=-dy；
            //反弹（上下方向交换）
				if(y==n-1)a[x]=col;
            //如果在最下面一行，做标记
			}
			int nx,ny;
            //横（纵）坐标上离边缘的距离
			if(dx==1)nx=m-1-x;
            //如果在往右走
			else nx=x;
            //反之，在往左走
			if(dy==1)ny=n-1-y;
            //如果在往下走
			else ny=y;
            //反之，在往上走
			x+=dx*min(nx,ny);
            //为什么是最小值见“算法”板块
            //x坐标移动
			y+=dy*min(nx,ny);
            //y坐标移动
		}
	}
	printf("%d",ans);
    //输出答案
	return 0;
}
```
代码仅供参考

---

## 作者：YingDragon_wjq (赞：4)

# [Chessboard Billiard ](https://www.luogu.com.cn/problem/CF74C) 参考题解

## 题目大意

可以在一个 $n\times m$ 的棋盘中连续放小球，小球可以在棋盘中沿 $45°$ 斜线运动，运动过程中触碰到边界后会反弹（具体方式见原题）。当一个小球又重复了同样的路径，它可以选择在任意的位置停止移动。

棋盘上允许放多个小球，放一个小球时，可以选择小球的初始移动方向（只能是 $45°$ 方向），等小球完成一个运动周期后，停止运动之后，就可以放下一个小球。**小球的移动轨迹不能经过之前已停止移动的小球所在的格子。**

求出棋盘中可以放的小球最大数量。

## 题目分析

我们先看下数据范围：

$2\le n,m\le 10^6$

是不是很吓人？我们甚至想把这个棋盘存下来都难（~~话说哪里来的这么大的棋盘啊~~）。但是我们“不难”发现，本题的所有操作其实都只和棋盘边上的格子有关。换句话说，只要棋盘的边上的格子都经过了，那么就没有符合条件的格子了。

为啥呢？

我们假设有两个球，$1$ 号球经过了某个边上的格子，如果 $2$ 号球也经过了这个格子，那么两个球一定会相撞。（**你可以仔细想想是不是这回事**）但是如果两个球都经过了一个不在边上的格子，它们就可能不会相撞。

那么我们就可以只枚举边上的格子了。

## 具体实现

虽然我们已经成功找到了方法，但是当你真正实施起来时，你会发现寸步难行（好吧，其实是我寸步难行）。

首先，为了方便调用，我把边上的格子坐标都存进了一个数组。以下便是标号函数：


```cpp
void start(){
	for(int i=1;i<=m;i++){
		a[++cnt].x=1;
		a[cnt].y=i;
	}
	for(int i=2;i<n;i++){
		a[++cnt].x=i;
		a[cnt].y=1;
		a[++cnt].x=i;
		a[cnt].y=m;
	}
	for(int i=1;i<=m;i++){
		a[++cnt].x=n;
		a[cnt].y=i;
	}
}
```



假设一个边上的格子坐标为 $x$ 和 $y$，那么就有以下寻找编号的函数：

```cpp
int get(int x,int y){
	if(x==1) return y;
	else if(x<n){
		if(y==1) return m+2*x-3;
		else if(y==m) return m+2*x-2;
	}
	else return 2*n+m-4+y;
}
```

我们再规定一下小球的状态：方向 $1$ 代表左上，方向 $2$ 代表右上，方向 $3$ 代表左下，方向 $4$ 代表右下。

最后我们再处理小球碰到边界时的状态切换以及坐标确定：

```cpp
int get_zb(int x,int y,int z){
	int xx=x,yy,ansx,ansy,edge;
	if(z==1){
		edge=min(x,y);
		yy=y-edge+1;
	}
	else if(z==2){
		edge=min(x,m-y+1);
		yy=y+edge-1;
	}
	else if(z==3){
		edge=min(n-x+1,y);
		yy=y-edge+1;
	}
	else{
		edge=min(n-x+1,m-y+1);
		yy=y+edge-1;
	}
	//复杂的移动
	ansy=yy;
	if(z==1||z==2) ansx=xx-edge+1;
	else ansx=xx+edge-1;
	return get(ansx,ansy);
}//移动结点
void dfs(int u,int z,bool pd){
	a[u].vis=1;
	if(u==tmp&&pd) return;
	int fx,zb=get_zb(a[u].x,a[u].y,z);
	if(zb==1) fx=4;
	else if(zb==m) fx=3;
	else if(zb==2*n+m-3) fx=2;
	else if(zb==2*n+2*m-4) fx=1;
	//繁琐的判断
	else{
		for(int i=1;i<=4;i++){
			if(a[zb].x+dx[i]<1||a[zb].x+dx[i]>n||a[zb].y+dy[i]<1||a[zb].y+dy[i]>m) continue;
			if(i==fan[z]) continue;
			fx=i;
		}
	}//180度旋转
	dfs(zb,fx,1);
}//判断反弹
```


## 完整 AC 代码


```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int n,m,cnt,ans,sx,sy,tmp;
int dx[5]={ 0,-1,-1, 1, 1};
int dy[5]={ 0,-1, 1,-1, 1};
//偏移数组
int fan[5]={0,4,3,2,1};//反弹后的方向
struct edge_node{
	int x,y;
	bool vis;
}a[4*N];

void start(){
	for(int i=1;i<=m;i++){
		a[++cnt].x=1;
		a[cnt].y=i;
	}
	for(int i=2;i<n;i++){
		a[++cnt].x=i;
		a[cnt].y=1;
		a[++cnt].x=i;
		a[cnt].y=m;
	}
	for(int i=1;i<=m;i++){
		a[++cnt].x=n;
		a[cnt].y=i;
	}
}//初始化a数组的x,y
int get(int x,int y){
	if(x==1) return y;
	else if(x<n){
		if(y==1) return m+2*x-3;
		else if(y==m) return m+2*x-2;
	}
	else return 2*n+m-4+y;
}//根据x,y找编号
int get_zb(int x,int y,int z){
	int xx=x,yy,ansx,ansy,edge;
	//xx和yy是直角三角形的直角顶点坐标信息
	//ansx和ansy是所求顶点坐标信息
	//edge是等腰直角三角形腰长
	if(z==1){
		edge=min(x,y);
		yy=y-edge+1;
	}
	else if(z==2){
		edge=min(x,m-y+1);
		yy=y+edge-1;
	}
	else if(z==3){
		edge=min(n-x+1,y);
		yy=y-edge+1;
	}
	else{
		edge=min(n-x+1,m-y+1);
		yy=y+edge-1;
	}
	//移动判断
	ansy=yy;
	if(z==1||z==2) ansx=xx-edge+1;
	else ansx=xx+edge-1;
	return get(ansx,ansy);
}//移动结点
void dfs(int u,int z,bool pd){
	a[u].vis=1;
	if(u==tmp&&pd) return;
	int fx,zb=get_zb(a[u].x,a[u].y,z);
	if(zb==1) fx=4;
	else if(zb==m) fx=3;
	else if(zb==2*n+m-3) fx=2;
	else if(zb==2*n+2*m-4) fx=1;
	//繁琐的判断
	else{
		for(int i=1;i<=4;i++){
			if(a[zb].x+dx[i]<1||a[zb].x+dx[i]>n||a[zb].y+dy[i]<1||a[zb].y+dy[i]>m) continue;
			if(i==fan[z]) continue;
			fx=i;
		}
	}//180度旋转
	dfs(zb,fx,1);
}//判断反弹
void build(){
	for(int i=1;i<=cnt;i++){//遍历每个边上节点
		if(a[i].vis) continue;
		ans++;
		for(int j=1;j<=4;j++){
			if(a[i].x+dx[j]<1||a[i].x+dx[j]>n||a[i].y+dy[j]<1||a[i].y+dy[j]>m) continue;
			sx=a[i].x;
			sy=a[i].y;
			tmp=get(sx,sy);
			dfs(tmp,j,0);
		}
	}
}

int main()
{
	cin>>n>>m;
	start();
	build();
	cout<<ans;
	return 0;
}//原创，勿抄！
```
 $\Large 我真是分类讨论肝帝！$

---

## 作者：ZLCT (赞：3)

# CF74C Chessboard Billiard
## 题目翻译
给定一个 $n\times m$ 的棋盘，现在要在依次在其中放置若干个球，放置的球会沿着某一个斜 $45$ 度的方向走，遇到墙壁则会反弹，当球走完一个循环以相同方向回到起点后，其可以停止在路径上任意一个位置。问最多能放置多少个球使其不发生碰撞。
## 巧妙的数学推理
与其出现在算法竞赛里，这个题不如出现在数学竞赛里。\
由于棋盘任意反转对于我们来说是一样的，也就是 $n\times m$ 的答案和 $m\times n$ 的答案是一样的。那么我们不妨设 $n\le m$。\
首先证明一个非常重要的引理：\
引理 $1$：从任意一个点向任意一个方向走都可以走到它本身。\
证明：假设我们的出发点是 $(x,y)$，方向是上右。\
由于横坐标和纵坐标互不影响，所以我们分开讨论，这里以横坐标为例。\
那么在走 $n-x$ 步后我们的横坐标就变成了 $n$，此后每 $n-1$ 步就从一侧墙壁走到另一侧墙壁了，那么要使横坐标为 $x$ 的话，我们可以走 $n-x+2k(n-1)+n-x-1$ 步或 $n-x+(2k+1)(n-1)+x-1$ 步，其中 $k$ 是非负整数。\
同理我们可以根据纵坐标算出我们可以走 $m-y+2k(m-1)+m-y-1$ 步或 $m-y+(2k+1)(m-1)+y-1$ 步。\
我们可以直接去设同余方程然后求解，但是过于麻烦了，所以我们采用抽屉原理进行解释。\
由于全部点加上方向至多有 $4\times n\times m$ 种状态，所以当走至多 $4\times n\times m$ 步后一定会走到一个之前走到的状态。\
我们再进行一步神奇的转换：由于球的运动轨迹满足反射定律，所以我们可以看成是一束光，那根据物理中光路可逆的知识，我们沿着反方向去走一定可以走回到起点，所以我们也不存在走到一个环内而起点不在环内。\
我们仔细研究一下题意，它既然要以相同的方向回到起点，那么我们可以想一下它上一步是从哪里来的。很明显一定是从初始方向的反方向沿着初始方向过来的。\
所以这就告诉我们：
引理 $2$：球一定是经过了至少一次上下和一次左右翻转，也就是至少碰了上下其中一个墙一次，也至少碰了左右其中一个墙一次。\
证明：假设没有碰上下墙，那么上下的运动方向不变，但是如果初始方向是下，球一定会从上方回来，如果初始方向是上，球一定会从下方回来，这代表运动方向改变，所以二者存在矛盾，假设不成立。左右的证明同理。\
这里再提出一个比较显然的引理：\
引理 $3$：一个路径上任意一个点出发都是等价的。\
证明：由于我们要求一条合法路径中间必须没有障碍物，又要形成一个回路，所以在回路上任意一个点出发都可以完整走完这条回路，而走完回路后题目又说可以任意位置停止，所以无论在回路上哪个点出发都是等价的。\
根据引理 $2,3$，我们不妨假设起点在左侧墙上的一点。\
为什么要假设在墙上呢？\
我们考虑在左侧墙上，可能的方向就从四种变成了两种，并且这两种方向是等价的（一个初始方向一个返回方向）。\
同理我们可以在右侧墙壁也找到至少一个这条路径经过的点。\
这里我们再证明一个引理：\
引理 $4$：没有两个点共用一条路径。\
证明：这一点也是比较显然的，因为如果两个点共用同一个路径，那么无论第一个点停在哪，第二个点都一定会撞上第一个点。\
引理 $2,3,4$ 的说明就告诉我们墙上的某一点，至多只有一个点经过。\
这样我们就确定了答案的一个上界，就是 $n$，注意这里已经假设 $n\le m$ 了。\
这里接着上面，我们再来证明一个引理：\
引理 $5$：最终不会有墙壁没有被走过。\
证明：假设有一个墙壁没有被走过，那么我们可以以这个点作为起点，并最终停在这个点，由于之前这个点没有被走过，所以我们也不影响其余点的操作。并且根据引理 $1$，我们一定能回来。\
所以我们的问题可以转化为把左墙壁都填满至多多少个球，由于我们无论初始向右下还是右上走都会从另一个方向回来，所以我们的问题就没有至多的限制。
### 一个可以通过的做法
那么这就是本题的第一种做法，枚举左墙的每一个点，如果非空则放一个球模拟走的过程，如果回到起点则停止。\
这样的复杂度可能看起来比较高，但是每碰到一个左墙壁我们就不会考虑它了，所以我们最多只会碰到 $n$ 次左墙壁，每次我们模拟走的过程又是直接 $O(1)$ 算出来的，所以总复杂度是 $O(n)$ 的。
### 继续改进
我们继续考虑一个球会走过几个墙壁。\
因为左右墙壁是对称的，所以我们这里只考虑左墙壁。\
我们把整个图形不断翻折，这样可以使我们不需要考虑反弹的情况。
![](https://cdn.luogu.com.cn/upload/image_hosting/8sk48dl5.png)\
此图展示了一个 $3\times 3$ 的矩形翻折后的一部分，如果设左上角为 $(0,0)$，向右和向下分别为 $x,y$ 轴的正方形，那么点 $(x,x)$ 表示走 $x$ 步后所到达的位置（横纵轴对应的数字/字母）。例如走 $4$ 步就到达了 $(A,1)$ 也就是起点。\
当然对于其余左墙壁上的点，只需要把对应的标号向下偏移一下，这里不做演示了。\
![](https://cdn.luogu.com.cn/upload/image_hosting/7jq8rb9l.png)\
如果觉得有点抽象不妨看这张图，这张图就是刚才那张图的展开，格子中的数字 $x$ 代表走 $x$ 步可以到达该点。\
那么我们注意到如果我们不返回而是直接顺着向右下走，那我们就不需要再分类讨论了。\
唯一的问题就是在交界处会出现原地踏步的情况，那我们只需要把表格交界处变成只出现一次就好了。于是就出现了第一张图的表格。\
你可能对第一张表格有个疑惑：这不是 $2\times 2$ 的吗？\
事实上思考一下，我们每次从左墙壁走到右墙壁，我们只需要走 $m-1$ 步，同理从上到下也只需要走 $n-1$ 步。\
那我们现在的问题就是找到第一个起点所在位置，也就是第一个 $(A,1)$ 点。\
我们设 $t$ 步后到达。\
首先看横坐标，由于去一次和回来一次后才到达 $A$，所以当 $t=p(2n-2)$ 时才可以满足横坐标为 $A$；同理纵坐标为 $1$ 时，必须满足 $t=q(2m-2)$。\
这不就是让我们求 $2n-2$ 和 $2m-2$ 的最小公倍数吗？\
所以 $t$ 就等于 $\operatorname{lcm}(2n-2,2m-2)$，提出一个 $2$ 就变成了 $t=2\times\operatorname{lcm}(n-1,m-1)$。\
那么此时经过了多少个左墙壁上的点呢？\
那一趟来回是 $2m-2$，相当于每 $2m-2$ 步就经过了一个点，所以一共经过了 $\frac{t}{2m-2}=\frac{2\times\operatorname{lcm}(n-1,m-1)}{2m-2}=\frac{\operatorname{lcm}(n-1,m-1)}{m-1}=\frac{\frac{(n-1)\times(m-1)}{\gcd(n-1,m-1)}}{m-1}=\frac{n-1}{\gcd(n-1,m-1)}$ 个点。\
那每一个左边的点都经过这么多点，一共能放几个点呢？\
由于上面的式子里是 $n-1$，所以我们先从左边拿出 $n-1$ 个点。\
那么放一个能经过 $\frac{n-1}{\gcd(n-1,m-1)}$ 个点，这 $n-1$ 个点就能放 $\frac{n-1}{\frac{n-1}{\gcd(n-1,m-1)}}=\gcd(n-1,m-1)$ 个点。\
但是剩下的一个点怎么办呢？\
还记得我们的引理 $5$ 的证明吗？\
没错，我们只需要使剩余的那个点在走过若干轮之后回到起点就不会干扰其余路径，所以最终答案就是 $\gcd(n-1,m-1)+1$。\
但是。。。这好像有些悖论的意思了，我们前面不是刚证明了每次都会经过 $\frac{n-1}{\gcd(n-1,m-1)}$ 个点，并且根据引理 $4$，这个点经过的 $\frac{n-1}{\gcd(n-1,m-1)}$ 个点不能再被用了吗？\
事实上这的确很神奇。\
其实你还可以举出一个很平凡的例子，任意一个 $n\times (n+1)$ 的矩形，根据我们的论证每个点都会经过左墙壁 $n-1$ 个点，然而若给棋盘黑白染色，你会发现很明显每个点至多经过 $\lceil{\frac{n}{2}}\rceil$ 个点。\
其中的原因就在于四个角。\
这四个角由于只能从初识射出去的方向回来，所以这就出现了违背上面的逻辑的情况，也就是按照上面的方式，我们有两条路径其实是相当于途中非起点的每个点经过了两遍的。\
所以这两条路径实际上加起来才只经过了 $\frac{n-1}{\gcd(n-1,m-1)}+1$ 个点（注意这里的 $+1$，因为两个起点没有被算两次）。\
所以我们的答案的 $+1$ 和剩下 $1$ 个点的处理不是和刚才那样来的，而是两条算重的路径拼起来的。\
那你可能还有一个问题：如果这两条路径都是同一个点出来的怎么办？\
我们知道矩形是对称的，所以这就说明左墙的左上角和左下角也一定在一条路径上。\
我们考虑这条路径多算了几个点，其实就是除了左上角和左下角的其余点。\
我们先不着急减去算重的部分，我们会发现这条路径对应的右墙上的点对称过来不正是右墙两个角出发的一条路径吗？\
而我们多算的左墙点的个数正好是右墙点的个数 $-1$，所以我们相当于用了 $\frac{n-1}{\gcd(n-1,m-1)}+1$ 个点放置了两个点。\
这样正好答案也是 $\gcd(n-1,m-1)+1$。

---

## 作者：tzc_wk (赞：3)

# 一道并查集的好题

如果两个小球可以到达，那么它们就可以到达同一个边界。故两个小球可达的边界位置不同等价于这两个小球不可达。

我们可以用并查集维护所有边界位置的关系，最终得到的不同连通分量的个数即为最多可以放置的小球数。

$ Code $:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int get(int x,int y){//给每个边界赋上的编号
	if(x==1)		return y;//上边界
	else if(x==n)	return 2*m+n-1-y;//下边界
	else if(y==1)	return 2*m+2*n-2-x;//左边界
	else if(y==m)	return m+x-1;//有边界
}
int f[4000005];
void init(){for(int i=1;i<=2*(n+m)-4;i++)	f[i]=i;}//初始化并查集
int find(int x){return (f[x]==x)?x:f[x]=find(f[x]);}
void link(int x,int y){if(find(x)!=find(y))	f[find(x)]=find(y);}
signed main(){
	cin>>n>>m;
	init();
	if(n<m)	swap(n,m);
	for(int i=1;i<=n;i++){
		if(i<=m)
			link(get(i,1),get(1,i)),link(get(i,m),get(1,m-i+1));
		else
			link(get(i,1),get(i-m+1,m)),link(get(i,m),get(i-m+1,1));
		if(i>=n-m+1)
			link(get(i,1),get(n,n-i+1)),link(get(i,m),get(n,m-n+i));
		else
			link(get(i,1),get(m+i-1,m)),link(get(i,m),get(m+i-1,1));
	}
	int ans=0;
	for(int i=1;i<=2*m+2*n-4;i++)	if(f[i]==i)	ans++;//数联通分量个数
	cout<<ans<<endl;
}
```


---

## 作者：闲鱼 (赞：1)

分析**碰到先前停止运动的弹球**的状态

可以肯定的是球一定是沿着先前的那颗球**四个方向中的某一个方向的运动周期轨迹上**的某一点沿着轨迹出发的（可能有点绕，~~反复咀嚼一下~~）

其实也就是触碰边界的位置一样（毕竟只会以45度反射角反弹）

考虑 _并查集_ 表示边界点与边界点的集合关系，如果从a点反弹会落到b点，就把a、b两点所在集合合并，最终统计集合数量即可
```cpp
#include <stdio.h>
using namespace std;
#define MAX 4000005
#define Swap(x, y) do{x ^= y; y ^= x; x ^= y;}while(0)
int n, m, pa[MAX];

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while('0' <= ch && ch <= '9'){x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
    return x * f;
}

inline int id(int x, int y) //边界标号 
{
    if(x == 1) return y;
    if(x == n) return 2 * m + n - y - 1;
    if(y == 1) return 2 * (m + n) - x - 2;
    if(y == m) return m + x - 1;
}

inline int Find(int x)
{
    int r = x;
    while(pa[r] != r) r = pa[r];
    while(pa[x] != r)
    {
        int y = pa[x];
        pa[x] = r;
        x = y;
    }
    return r;
}

inline void Merge(int a, int b)
{
    int ax = Find(a), bx = Find(b);
    if(ax != bx) pa[ax] = bx;
}

int main()
{
    int ans = 0;
    n = read(), m = read(); 
    for(register int i = 1;i <= 2 * (n + m) - 4;i++) pa[i] = i;
    if(n < m) Swap(n, m);
    for(register int i = 1;i <= n;i++)
    {
        if(i <= m) Merge(id(i, 1), id(1, i)), Merge(id(i, m), id(1, m - i + 1));
        else Merge(id(i, 1), id(i - m + 1, m)), Merge(id(i, m), id(i - m + 1, 1));
        if(i + m - 1 < n) Merge(id(i, 1), id(m + i - 1, m)), Merge(id(i, m), id(m + i - 1, 1));
        else Merge(id(i, 1), id(n, n - i + 1)), Merge(id(i, m), id(n, m - n + i));
    }
    for(register int i = 1;i <= 2 * (n + m) - 4;i++)
    {
        if(pa[i] == i) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
```


---

## 作者：Liuhy2996 (赞：0)

### 思路
枚举四条边上的点，若点重复，则整条路径重复。逆时针给边上点编号，用数组记录边上的点访问情况。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e6+10;
int n,m,x[N],y[N],ans,cnt,vis[N];
int chg(int x,int y){            //坐标转编号
	if(y==1) return x;
	if(x==n) return n-1+y;
	if(y==m) return 2*n+m-1-x;
	return 2*n+2*m-2-y;
}
void pt(int pos){               //放球
	int px=x[pos],py=y[pos],a=1,b=1;
	while(vis[chg(px,py)]<2){
		++vis[chg(px,py)];
		if(px+a>n||px+a<1) a=-a;
		if(py+b>m||py+b<1) b=-b;
		int k=1e9;
		if(a>0) k=min(k,n-px);
		else k=min(k,px-1);
		if(b>0) k=min(k,m-py);
		else k=min(k,py-1);
		px+=a*k,py+=b*k;
	}
}
int main(){
	cin>>n>>m;
	// 33行至37行为编号
	for(int i=1;i<=n;++i) x[++cnt]=i,y[cnt]=1;
	for(int i=2;i<=m;++i) x[++cnt]=n,y[cnt]=i;
	for(int i=n-1;i>0;--i) x[++cnt]=i,y[cnt]=1;
	for(int i=n-1;i>1;--i) x[++cnt]=1,y[cnt]=i; 
	for(int i=1;i<=n*2+m*2-4;++i)
		if(!vis[i]) pt(i),++ans;
	cout<<ans;
	return 0;
}
```

---

## 作者：Zikl (赞：0)

题目链接：[Chessboard Billiard](https://www.luogu.com.cn/problem/CF74C)

题解：

可以自己手动画画，我们不难发现，当 $n = m$ 时，答案即为 $n$。

为方便思考，当 $n \ne m$ 时，我们钦定 $n < m$，然后再画几个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/wx21a2wf.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/egxwt3ur.png)

当 $n = m$ 时，相当于给你 $n$ 个点（即可以看作 $m =1$）。当 $n \ne m$ 时，如图三所示，黄线相当于吞了 $m$ 的 $n - 1$ 个点（虽然黄线占了两个点，但它对答案有 1 的贡献），红线和蓝线同理。当吞到 $m < n$，又变成吞 $n$ 的 $m-1$ 个点（此时的 $m$ 已变化），这个变化，类似于翻一下矩形继续减。读者可以自己多画几个图（笔者画了很多图，但都很丑，所以就不放上来了）。

而当 $n$ 与 $m$ 其中一个为 $1$ 时，不能再吞。（因为这个时候相当于你已求出类似于 “当 $n = m$ 时，给你 $n$ 个点” 的情况）

然后输出 $n + m - 1$ 即可。（这样不用判断哪个是 $1$）

my code:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define go(i,x) for(int i=head[x];i;i=Next[i])
using namespace std;
int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
int n,m;
signed main(){
	n=read(),m=read();
    while(n>1&&m>1){
        if(n>m)
        n=n-(m-1);
        else m=m-(n-1);
    }
    printf("%d",n+m-1);
	return 0;
}
```
感谢观看。

---

