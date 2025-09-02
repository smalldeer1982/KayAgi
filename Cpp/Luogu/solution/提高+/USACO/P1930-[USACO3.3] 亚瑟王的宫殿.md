# [USACO3.3] 亚瑟王的宫殿

## 题目描述

很久以前，亚瑟王和他的骑士习惯每年元旦去庆祝他们的友谊。为了纪念上述事件， 我们把这些故事看作是一个棋盘游戏。有一个国王和若干个骑士被放置在一个由许多方格 组成的棋盘上，没有两个骑士在同一个方格内。

这个例子是标准的 $8\times 8$ 棋盘。

![](https://cdn.luogu.com.cn/upload/image_hosting/bvjh9o2q.png)

国王可以移动到任何一个相邻的方格，从下图中黑子位置到下图中白子位置前提是他 不掉出棋盘之外。

![](https://cdn.luogu.com.cn/upload/image_hosting/joj1exif.png)

一个骑士可以从下图中黑子位置移动到下图中白子位置(走“日”字形） 但前提是他 不掉出棋盘之外。

![](https://cdn.luogu.com.cn/upload/image_hosting/vf9vuque.png)

在游戏中，玩家可在每个方格上放不止一个棋子，假定方格足够大，任何棋子都不会 阻碍到其他棋子正常行动。

玩家的任务就是把所有的棋子移动到同一个方格里——用最小的步数。为了完成这个 任务，他必须按照上面所说的规则去移动棋子。另外，玩家可以选择一个骑士跟国王从他们两个相遇的那个点开始一起行动，这时他们按照骑士的行动规则行动，其他的单独骑士则自己一直走到集中点。骑士和国王一起走的时候，只算一个人走的步数。

请计算他们集中在一起的最小步数，而且玩家必须自己找出这个集中点。当然，这些 棋子可以在棋盘的任何地方集合。


## 说明/提示

### 样例解释

他们集中在 $\tt B5$。

- 骑士 $1$：$\tt A3\to B5$（$1$ 步）。
- 骑士 $2$：$\tt A8\to C7\to B5$（$2$ 步）。
- 骑士 $3$：$\tt H1\to G3\to F5\to D4$，此时国王开始与这个骑士一起走，$\to \tt B5$（$4$ 步）
- 骑士 $4$：$\tt H8\to F7\to D6\to B5$（$3$ 步）。

$1+2+4+3=10$ 步。

题目翻译来自 NOCOW。

USACO Training Section 3.3

## 样例 #1

### 输入

```
8 8
D 4 
A 3 A 8 
H 1 H 8 
```

### 输出

```
10```

# 题解

## 作者：天泽龟 (赞：48)

##  [造出来一个数据结果hack了所有题解... 你们这是思想僵化的表现啊](https://www.luogu.org/discuss/show/101031)
 

 这篇题解分两块，先讲讲此题思路，再对于其他题解的错误点进行详细分析。



## 一.本题思路及细节处理

####  **0. 首先亚瑟王实在是太可爱了QwQ，吾王万岁！**
![](https://ss0.bdstatic.com/94oJfD_bAAcT8t7mm9GUKT-xh_/timg?image&quality=100&size=b4000_4000&sec=1550651121&di=9604902adbfc30f6fd9527700f93a09d&src=http://www.pujia8.com/static/pics/20170212120059_32.jpg)

~~看什么看，没见过亚瑟王Saber吗。~~

#### 1. 这题如果不讲数据范围，就会让人十分难以下手：

首先集合点是本题核心，所有操作都是基于集合点确定的情况下。但他不告诉你点在哪里。但一看数据范围，$r*c$最大约等于$1000$，于是不管三七二十一，先暴力枚举集合点再说。

#### 2. 集合点确定，如何计算答案？

根据题意我们可以知道：
	
    总路程=（n-1）个骑士到集合点的距离+有个骑士去接国王之间乱七八糟的距离
    
但是请注意，这里的距离并不是两点之间曼哈顿距离，而是通过日字形不断跳来跳去得到的。

~~那我们对于每一个点都进行BFS，看跳到集合点的最短路径是多少。~~ 以上方法肯定是超时的，那我们又会用到一个常见技巧：**在无向图中，起点到终点的最短路等于终点到起点的最短路。**

于是我们从枚举的这个集合点开始跑BFS，这样就可以把所有点的最短路类似洪水填充似的都求出来啦。又由于枚举集合点不定，存储时候可用**四维数组**。

#### 3.对于骑士接国王部分如何分析？

首先应该可以想到，骑士不可能总是刚好跳到国王那格子，若想最优国王大部分情况都会走一点距离的。。这也导致了不一定是最近的骑士去接国王。

但又很明显的是，骑士如果离国王越近，国王就可以走的越少，所以骑士跳到哪一格子最优也不知道。

~~于是就不会了~~ 

### 于是我们贪心地想，国王走的路应该不会超过骑士一次能超过的步数（2步），于是暴力枚举以国王为中心的5*5矩形确定接国王的点。

事实证明这样可以过，但是这个暴力翻遍题解也没有人详细证明，于是现在我们来hack他。

## 二.对于暴力枚举5*5矩形的$hack$

### 先上图：
![](https://cdn.luogu.com.cn/upload/pic/52315.png)

~~RT,左下是亚瑟王，中间那个是圆桌骑士高文（雾）~~

红格子是我们构造出来的集合点，旁边的红圈是其他骑士，他们距离红格都只有1步，所以肯定选择那个点为集合点。

注意到此时高文已经不在王的5*5范围内了，我们来把两次距离算一算。

#### 1. 我们来算一下现在的总距离
其他骑士总距离一共为5，高文到集合点距离为$d$（这样假设他离集合点很远也适用）

王到高文要走3步。所以一共为$d+3+5=d+8$步。

#### 2.我们让高文走一步，分析$5*5$方格内情况。

我们注意到，当高文在王的对角线上时，最优可以缩短一步，于是王只用2步到高文。

然而高文往前走一步，最劣的情况是必须原路返回才能到集合点，于是高文回集合点需要$d+2$步。

其他骑士不变，共$d+2+5+2=d+9$步。

于是便$hack$了，骑士与王相遇点未必在$5*5$方格内。

#### 3. ~~那是不是$7*7$方格就好了呢？~~

当然不是，由上可知，达到最劣情况满足以下条件均不能控制在某一方框内：
1. 接王的骑士往内走一步会使到集合点的距离+1(就是原路返回的情况)
2. 骑士处在王的对角线上

这里还要说说，可以想象出来，若不在对角线上则最优可以减少2步距离，那答案不变优也不会变劣。

#### 4. 那这题是不是没做头了？

题当然还是可以做，你可以枚举棋盘上每一个点来判断是否为王与骑士相遇点，然后暴力枚举骑士，再暴力枚举集合点，最劣是$O(R^3*C^3)$，但是不可能达到这么大。

当然，本题最难的部分并不是这里，如果嫌麻烦也不用想太复杂，枚举$5*5$过了就算了吧。。


## 三.一些小细节

1. 首先是读题。。行和列别搞混了。。

2. 枚举$5*5$方格别越界都是小事了

3. 洪水填充记忆化那里，应该入队时候就标记访问，不然在队列里时候还会增加一堆重复的。。

4. 赋初值时小一点，我开了$INT$_$MAX/3$还爆了负数。。

## 四.丑陋的代码
不具有观赏性

//1. 枚举集合点O(10^3)
//2. BFS算出各骑士到此点距离 

//3. 再枚举集合点。。 
//4. 枚举哪个骑士接（或都不接）国王最优。 
//5. 总距离=其他骑士到点的距离+
	//我到国王附近的距离+国王到附近的距离+国王附近到点距离；
```cpp

 
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

struct pp{
	int l,c;
	int d;
}kn[2000],ki;

int st,r,c;
int dx[8]={1,2,2,1,-1,-2,-2,-1};
int dy[8]={2,1,-1,-2,-2,-1,1,2};
bool v[50][30];
int ans=1000000000,sum,d[50][30][50][30];//d[a,b,c,d] -> (a,b) to (c,d)
queue<pp> q;

bool yuejie(int x,int y)
{
	return (x<=0||x>r||y<=0||y>c);
}

void bfs(int bx,int by)
{
	memset(v,0,sizeof(v));
	q.push((pp){bx,by,0}); v[bx][by]=1; d[bx][by][bx][by]=0;
	while (!q.empty())
	{
		
		int xx=q.front().l,yy=q.front().c;
		
		d[bx][by][xx][yy]=q.front().d; q.pop();
		
		for (int i=0;i<8;i++)
		{
			int x=xx+dx[i],y=yy+dy[i];
			if (!yuejie(x,y)&&!v[x][y]) v[x][y]=1,q.push((pp){x,y,d[bx][by][xx][yy]+1});
		}
	}
}

void print(int x,int y)
{
	for (int i=1;i<=r;i++,cout<<endl)
	for (int j=1;j<=c;j++) cout<<d[i][j][x][y]<<" ";
	cout<<endl;
}

int a(int x){return (x>0)?x:-x;}



int main()
{
	cin>>r>>c;
	memset(d,0x10f,sizeof(d));
	char cross; int line;
	while (cin>>cross>>line)
	{
		if (st==0) st=1,ki.l=line,ki.c=cross-'A'+1;
		else kn[st].l=line,kn[st++].c=cross-'A'+1;
	}
	st--;
	//1,2
	for (int i=1;i<=r;i++)
  	  for (int j=1;j<=c;j++) bfs(i,j);
  	  
  	
  	//3,4,5
  	for (int i=1;i<=r;i++)
  	for (int j=1;j<=c;j++)  //ji he point 
	{
		int sum=0;
//		print(i,j);
		for (int k=1;k<=st;k++) sum+=d[kn[k].l][kn[k].c][i][j];
		ans=min(sum+max(a(ki.l-i),a(ki.c-j)),ans);
		for (int k=1,summ=sum;k<=st;summ=sum,k++)  //knight who pick up the king
		{
			summ-=d[kn[k].l][kn[k].c][i][j];
			for (int ii=max(1,ki.l-3);ii<=min(r,ki.l+3);ii++)  //别越界了 
			  for (int jj=max(1,ki.c-3);jj<=min(c,ki.c+3);jj++)
			  ans=min(
			  	summ+d[kn[k].l][kn[k].c][ii][jj]+
			  	max(a(ii-ki.l),a(jj-ki.c))+d[ii][jj][i][j],ans);
		}
	}
	cout<<ans<<endl;
}
```


---

## 作者：lutongyu (赞：26)

Emmm…

为什么会有人需要贪心搜索王周围5x5呢？

依本菜鸡看，本题是Dijkstra + ^\*&(#(%&\*@($???!!!!!!

本菜鸡在USACO Training先AC了一遍，然后来洛谷TLE了两个点( °~° )

然后本菜鸡手动测了一下priority_queue的push和pop速度并且手打了一个heap把速度提到了priority_queue的2.5倍

然后……就没有然后了

![AC](https://cdn.luogu.com.cn/upload/pic/60816.png)

## 关键词

* Dijkstra
* 建图
* 拆点
* 优化
* TLE
* priority_queue
* heap

## 说明

### 本题解内N=RC，K表示骑士数量

## 建图

我们想要知道最小总距离。

### 先简化问题：如果骑士不能带王，那么

```
到pos最小总距离 = sum(每个骑士到pos最短距离) + 王到pos最小距离
```

而王到某个pos，假设是$(x, y)$，的最小距离是`max(abs(x - king.x), abs(y - king.y))`

解决骑士的问题，希望能够得到每一个骑士到每一个位置的最短路长度，首先想到可以使用**floyd（多源最短路径）**，但是效率是$O(N^3) = O(R^3\times C^3)$。R=30，C=26，所以最多运行474,552,000，**会TLE**，惨惨( °¬° )

于是我们对每一个可能的集合地从集合地作为源点做一下**BFS**，总效率$O(N^2)$。

**建图**：遍历棋盘每一个格子，对每一个格子枚举所有的骑士走法，如果不掉出棋盘就从该起点格子向这一步的终点格子建一条**有向边**，因为最终遍历到对面格子的时候还会加一条有向边回来，**凑成一条无向边**。

### 但是，骑士是能带王的，所以

```
到pos最小总距离 = sum(K-1个骑士到pos最短距离) + 某个骑士带王加上王到该骑士的最小总距离
```

大部分其他题解到这里就开始各种玄学贪心了( °~° )

其实这也可以建图。关键在于拆点，每个格子拆成两个点，表示两种状态：

* 状态一：走到这里的骑士**要去但还没有**接王
* 状态二：走到这里的骑士**不打算或者已经**接上王

因为我们不能分开处理王的走法，状态一到状态二增加的距离就是王从它的原始位置走到新位置的最短距离。这样建出来的图有不同的边权，不能使用BFS，最短路需要用**Dijkstra**，总效率$O(N^2log_2N)$。

**建图过程**：对所有状态一的点像之前一样建图，对所有状态二的点同样像之前一样建图，并在每一个格子$(x, y)$上从状态一的点到状态二的点建一条有向边，长度为`max(abs(x - king.x), abs(y - king.y))`。这样总结点数会加倍，但是算法效率依然够。

## 应用Dijkstra得到的数据

用ans记录最小答案，然后用每一个集合地得到的最小总距离更新它。

按照刚才的思路，应该有且仅有一个骑士带王（状态二），其他骑士都不带王（状态一）。

对于每一个集合地dijkstra完的最短距离数据要得到最小总距离，这时候暴力思路是遍历所有骑士，把所有剩下骑士原始位置状态一的距离都加起来，再加上当前遍历到的骑士的状态二距离，效率$O(K^2)$。由于是给每一个格子作为集合地求一遍，总效率是$O(NK^2)$，最坏总效率是$O(N^3)$，**TLE**。

但是注意状态一的距离数据在遍历到不同骑士的时候重复使用了。针对这一点，我用的**优化思路是$O(N)$求所有状态一距离的和，再$O(N)$求所有骑士从状态一到状态二最小的增量。二者相加就是当前集合地对应的最短总距离。**

## 调试

### 本菜鸡犯的错误：

* 各种编译错误
  * 特别的，`template struct`定义结构体不能在结构体里面定义比较性质的operator
* 死循环
* 输入时R和C弄反
* 最小增量在无骑士情况下的特判
* 各种其它智障WA
* USACO AC，洛谷TLE

### 针对USACO AC，洛谷TLE的调试：

我自测了程序的各部分用时。占大部分时间的是Dijkstra，而在Dijkstra里面最占时间的单步操作是priority_queue的push和pop，对于数据点#6占了差不多一秒。以下图片中的t单位是微秒，数据点是#6。

![time distribution](https://cdn.luogu.com.cn/upload/pic/60821.png)

于是我用以下代码测试了priority_queue的运行速度

```cpp
#include <cstdio>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
	int id, val;
	bool operator >(const Node other) const {
	return (val == other.val) ? (id > other.id) : val > other.val;
	}
} placeholderNode;

priority_queue<Node, vector<Node>, greater<Node> > q;

Node seq[1000005];

unsigned long long pushTime, popTime;

void test() {
	for (int i = 0; i < 1000000; i ++)
	seq[i] = (Node){rand() % 100000, rand() % 100000};
	unsigned long t1 = clock();
	for (int i = 0; i < 1000000; i ++)
	q.push(seq[i]);
	unsigned long t2 = clock();
	for (int i = 0; i < 1000000; i ++)
	q.pop();
	unsigned long t3 = clock();
	pushTime += t2 - t1;
	popTime += t3 - t2;
}

int main(int argc, char const *argv[]) {
	srand(time(0));
	int percent = 0;
	printf("\r%3d%%", percent); fflush(stdout);
	for (int i = 0; i < 1000; i ++) {
		test();
		if (percent < i / 10.0) {
			percent = int(i / 10.0);
			printf("\r%3d%%", percent); fflush(stdout);
		}
	}
	printf("\r100%%\n");
	printf("push: %lf; pop: %lf\n", pushTime / 1e9, popTime / 1e9);
	return 0;
}

```

单次push/pop平均用时结果如下（小数的单位是微秒）

![priority_queue test result](https://cdn.luogu.com.cn/upload/pic/60822.png)

说明pop占了大部分的运行时间。但是我并没有足够的时间给我的priority_queue去pop( °¬° )

**理论上priority_queue是可以提速的，因为它使用的是vector作为容器**

**于是我手打了一个使用数组的heap**并且对它进行了完全一样的测试，代码如下：

```cpp
#include <cstdio>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

struct Node {
	int id, val;
	bool operator >(const Node other) const {
	return (val == other.val) ? (id > other.id) : val > other.val;
	}
} seq[1000005];

Node heep[1000005];
int heepTot;

void pushHeap(Node x) {
	int id = (++ heepTot);
	while ((id >> 1) && heep[id >> 1] > x) {
		heep[id] = heep[id >> 1];
		id >>= 1;
	}
	heep[id] = x;
}

void popHeap() {
	Node cur = heep[heepTot --];
	int id = 1, id2;
	while (true) {
		if (((id << 1) <= heepTot && cur > heep[id << 1]) && ((id << 1 | 1) <= heepTot && cur > heep[id << 1 | 1])) {
			heep[id] = heep[id2 = (id << 1 | (heep[id << 1] > heep[id << 1 | 1]))];
			id = id2;
		} else if ((id << 1) <= heepTot && cur > heep[id << 1]) {
			heep[id] = heep[id << 1];
			id = (id << 1);
		} else if ((id << 1 | 1) <= heepTot && cur > heep[id << 1 | 1]) {
			heep[id] = heep[id << 1 | 1];
			id = (id << 1 | 1);
		} else {
			break;
		}
	}
	heep[id] = cur;
}

inline Node heapTop() {
	return heep[1];
}

inline bool heapEmpty() {
	return heepTot == 0;
}

void debugHeap() {
	char op[2];
	int x1, x2;
	bool f = true;
	Node cur;
	while (f) {
		scanf("%1s", op);
		switch (*op) {
			case 'a':
			scanf("%d%d", &x1, &x2);
			pushHeap((Node){x1, x2});
			break;
			case 'p':
			popHeap();
			break;
			case 't':
			cur = heapTop();
			printf("Node(%d, %d)\n", cur.id, cur.val);
			break;
			case 'h':
			for (int i = 1; i <= heepTot; i ++) printf("%d: Node(%d, %d)\n", i, heep[i].id, heep[i].val);
			break;
			case 'q':
			f = false;
			break;
			default:
			printf("Unknown operation.\n");
		}
	}
}

unsigned long long pushTime, popTime;

void test() {
	for (int i = 0; i < 1000000; i ++)
	seq[i] = (Node){rand() % 100000, rand() % 100000};
	unsigned long t1 = clock();
	for (int i = 0; i < 1000000; i ++)
	pushHeap(seq[i]);
	unsigned long t2 = clock();
	for (int i = 0; i < 1000000; i ++)
	popHeap();
	unsigned long t3 = clock();
	pushTime += t2 - t1;
	popTime += t3 - t2;
}

int main(int argc, char const *argv[]) {
	for (int i = 1; i < argc; i ++) {
		if (!strcmp(argv[i], "debug")) {
			test();
			return 0;
		}
	}
	srand(time(0));
	int percent = 0;
	printf("\r%3d%%", percent); fflush(stdout);
	for (int i = 0; i < 1000; i ++) {
		test();
		if (percent < i / 10.0) {
			percent = int(i / 10.0);
			printf("\r%3d%%", percent); fflush(stdout);
		}
	}
	printf("\r100%%\n");
	printf("push: %lf; pop: %lf\n", pushTime / 1e9, popTime / 1e9);
	return 0;
}

```

**priority_queue vs. myHeap**，测试结果如下

![priority_queue vs. myHeap](https://cdn.luogu.com.cn/upload/pic/60817.png)

push提速到原来的4.2倍，pop提速到原来的2.6倍

然后我把我自己的heap粘到本题代码里。

然后本菜鸡就AC了。

## 代码

USACO Training原题代码

```cpp
/*
 TASK: camelot
 LANG: C++
 ID: lutongy1
 */
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

//MARK: Global constants

const int MAXR = 30, MAXC = 35;
const int MAXK = MAXR * MAXC;
const int MAXN = MAXR * MAXC * 2;
const int MAXM = MAXN * 10;

const int knightMoves[8][2] = {
	{1, 2},
	{2, 1},
	{2, -1},
	{1, -2},
	{-1, -2},
	{-2, -1},
	{-2, 1},
	{-1, 2}
};

//MARK: Global variables

int X, Y, knightCnt;

int knights[MAXK], kingX, kingY;

inline bool setKnight(int id, int x, int y) {
	knights[id] = ((x << 5) | y);
	// fprintf(stdout, "setKnight(id: %d, x: %d, y: %d) => %s\n", id, x, y, (x < 0 || x >= 32 || y < 0 || y >= 32) ? "true" : "false");
	return (x < 0 || x >= 32 || y < 0 || y >= 32);
}

inline int knightX(int id) {
	// fprintf(stdout, "knightX(id: %d) => %d\n", id, (knights[id] >> 5) & 0x1f);
	return (knights[id] >> 5) & 0x1f;
}

inline int knightY(int id) {
	// fprintf(stdout, "knightY(id: %d) => %d\n", id, knights[id] & 0x1f);
	return knights[id] & 0x1f;
}

inline int kingDist(int x, int y) {
	// fprintf(stdout, "kingDist(x: %d, y: %d) => %d\n", x, y, max(abs(x), abs(y)));
	return max(abs(x - kingX), abs(y - kingY));
}

inline int ctoi(char c) {
	// fprintf(stdout, "ctoi(c: \'%c\') => %d\n", c, ((c >= 'A' && c <= 'Z') ? c - 'A' + 1 : 0));
	return (c >= 'A' && c <= 'Z') ? c - 'A' + 1 : 0;
}

inline int coordId(int x, int y, bool withKing = false) {
	// fprintf(stdout, "coordId(x: %d, y: %d, withKing: %s) => %d\n", x, y, withKing ? "true" : "false", ((y - 1) + (x - 1) * Y + (withKing ? (X * Y) : 0)));
	return (y - 1) + (x - 1) * Y + (withKing ? (X * Y) : 0);
}

inline int coordX(int id) {
	// fprintf(stdout, "coordX(id: %d) => %d\n", id, (id / Y) % X + 1);
	return (id / Y) % X + 1;
}

inline int coordY(int id) {
	// fprintf(stdout, "coordY(id: %d) => %d\n", id, id % Y + 1);
	return id % Y + 1;
}

inline bool coordWithKing(int id) {
	// fprintf(stdout, "coordWithKing(id: %d) => %s\n", id, (id / X / Y) ? "true" : "false");
	return id / X / Y;
}

inline bool isValidMove(int cid, int moveId, int *targid = NULL) {
	int x = coordX(cid) + knightMoves[moveId][0];
	int y = coordY(cid) + knightMoves[moveId][1];
	bool f = (x > 0 && x <= X && y > 0 && y <= Y);
	if (f && targid) *targid = coordId(x, y, coordWithKing(cid));
	// fprintf(stdout, "isValidMove(cid: %d, moveId: %d, targid: %p(=>%d)) => %s\n", cid, moveId, targid, targid ? *targid : -1, f ? "true" : "false");
	return f;
}

struct Edge {
	int v, c;
	Edge *next;
} *h[MAXN], pool[MAXM];
int edgeTot;

inline void addEdge(int u, int v, int c) {
	Edge *p = pool + (edgeTot ++);
	p->v = v; p->c = c; p->next = h[u];
	h[u] = p;
	// fprintf(stdout, "addEdge(u: %d, v: %d, c: %d) => void\n", u, v, c);
}

void buildMap() {
	int u, v, move;
	// Knight moves
	for (u = 0; u < X * Y * 2; u ++)
		for (move = 0; move < 8; move ++)
			if (isValidMove(u, move, &v))
				addEdge(u, v, 1); // Only forward, since backward will be added later
	// Take king
	for (u = 0, v = X * Y; u < X * Y; u ++, v ++)
		addEdge(u, v, kingDist(coordX(u), coordY(u)));
}

struct Node {
	int id, val;
	bool operator >(const Node other) const {
		return (val == other.val) ? (id > other.id) : val > other.val;
	}
} placeholderNode;

priority_queue<Node, vector<Node>, greater<Node> > q;

const int INF = 0x3f3f3f3f;

int dis[MAXN], pre[MAXN];
bool vis[MAXN];

void dijkstra(int src) {
	while (!q.empty()) q.pop();
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	memset(pre, -1, sizeof(pre));
	q.push((Node){src, dis[src] = 0});
	while (!q.empty()) {
		int u = q.top().id; q.pop();
		if (vis[u]) continue;
		vis[u] = true;
		for (Edge *p = h[u]; p; p = p->next) {
			if (dis[p->v] > dis[u] + p->c) {
				pre[p->v] = u;
				q.push((Node){p->v, dis[p->v] = dis[u] + p->c});
			}
		}
	}
}

//MARK: Debug

void printCoord(int id) {
	fprintf(stdout, "[%c%2d]", coordX(id) - 1 + 'A', coordY(id));
}

void printTrace(int src, int dest) {
	printCoord(src);
	while (src != dest && pre[src] >= 0) {
		int nxt = pre[src];
		if (src - nxt >= X * Y) {
			fprintf(stdout, " (king %d)", dis[src] - dis[nxt]);
		} else {
			fprintf(stdout, " > ");
			printCoord(nxt);
		}
		src = nxt;
	}
	fprintf(stdout, " (END)");
}

int camelot;
int ans, sum, minadd, minaddId, kx, ky;

void processDis() {
	sum = 0; minadd = INF;
	for (int i = 1; i <= knightCnt; i ++) {
		kx = knightX(i); ky = knightY(i);
		if (dis[coordId(kx, ky)] == INF) return;
		sum += dis[coordId(kx, ky)];
		if (minadd > dis[coordId(kx, ky, true)] - dis[coordId(kx, ky)]) {
			minadd = dis[coordId(kx, ky, true)] - dis[coordId(kx, ky)];
			minaddId = i;
		}
	}
	if (!knightCnt) minadd = 0;
	ans = min(ans, sum + minadd);
	/*
	fprintf(stdout, "\n");
	for (int i = 1; i <= 60; i ++) fprintf(stdout, "*");
	fprintf(stdout, "\n\n");
	fprintf(stdout, "Camelot = "); printCoord(camelot); fprintf(stdout, "\n");
	fprintf(stdout, "King starts from "); printCoord(coordId(kingX, kingY)); fprintf(stdout, "\n\n");
	for (int i = 1; i <= knightCnt; i ++) {
		fprintf(stdout, "Knight #%3d: ", i);
		kx = knightX(i); ky = knightY(i);
		printTrace(coordId(kx, ky, minaddId == i), camelot);
		fprintf(stdout, "\n\tadds %d to total distance.\n", dis[coordId(kx, ky, minaddId == i)]);
	}
	fprintf(stdout, "\nTotal distance: %8d\nAnswer:         %8d\n", sum + minadd, ans);
	fprintf(stdout, "\n");
	for (int i = 1; i <= 60; i ++) fprintf(stdout, "*");
	fprintf(stdout, "\n\n");
	*/
}

//MARK: IO

FILE *in, *out;

//MARK: Main

int main(int argc, char const *argv[]) {
	// Input
	fprintf(stdout, "Reading in...\n");
	in = fopen("camelot.in", "r");
	char s_cx[2];
	int cy;
	fscanf(in, "%d%d%s%d", &Y, &X, s_cx, &kingY);
	kingX = ctoi(s_cx[0]);
	while (fscanf(in, "%s%d", s_cx, &cy) != EOF)
		setKnight(++ knightCnt, ctoi(s_cx[0]), cy);
	fclose(in);
	// Calc
	fprintf(stdout, "Building map...\n");
	buildMap();
	fprintf(stdout, "Initialize variable \'ans\' to 0x%x\n", ans = INF);
	fprintf(stdout, "Iterating through tiles...\n");
	for (camelot = 0; camelot < X * Y; camelot ++) {
		dijkstra(camelot);
		processDis();
	}
	// Output
	fprintf(stdout, "Writing output...\n");
	out = fopen("camelot.out", "w");
	fprintf(out, "%d\n", ans);
	fclose(out);
	fprintf(stdout, "Complete!\n");
	return 0;
}

```

USACO Training带调试输出的代码（会输出每一个集合地的最优解，但是会严重超时，不建议用于提交）

 ```cpp
/*
 TASK: camelot
 LANG: C++
 ID: lutongy1
 */
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

//MARK: Global constants

const int MAXR = 30, MAXC = 35;
const int MAXK = MAXR * MAXC;
const int MAXN = MAXR * MAXC * 2;
const int MAXM = MAXN * 10;

const int knightMoves[8][2] = {
	{1, 2},
	{2, 1},
	{2, -1},
	{1, -2},
	{-1, -2},
	{-2, -1},
	{-2, 1},
	{-1, 2}
};

//MARK: Global variables

int X, Y, knightCnt;

int knights[MAXK], kingX, kingY;

inline bool setKnight(int id, int x, int y) {
	knights[id] = ((x << 5) | y);
	// fprintf(stdout, "setKnight(id: %d, x: %d, y: %d) => %s\n", id, x, y, (x < 0 || x >= 32 || y < 0 || y >= 32) ? "true" : "false");
	return (x < 0 || x >= 32 || y < 0 || y >= 32);
}

inline int knightX(int id) {
	// fprintf(stdout, "knightX(id: %d) => %d\n", id, (knights[id] >> 5) & 0x1f);
	return (knights[id] >> 5) & 0x1f;
}

inline int knightY(int id) {
	// fprintf(stdout, "knightY(id: %d) => %d\n", id, knights[id] & 0x1f);
	return knights[id] & 0x1f;
}

inline int kingDist(int x, int y) {
	// fprintf(stdout, "kingDist(x: %d, y: %d) => %d\n", x, y, max(abs(x), abs(y)));
	return max(abs(x - kingX), abs(y - kingY));
}

inline int ctoi(char c) {
	fprintf(stdout, "ctoi(c: \'%c\') => %d\n", c, ((c >= 'A' && c <= 'Z') ? c - 'A' + 1 : 0));
	return (c >= 'A' && c <= 'Z') ? c - 'A' + 1 : 0;
}

inline int coordId(int x, int y, bool withKing = false) {
	// fprintf(stdout, "coordId(x: %d, y: %d, withKing: %s) => %d\n", x, y, withKing ? "true" : "false", ((y - 1) + (x - 1) * Y + (withKing ? (X * Y) : 0)));
	return (y - 1) + (x - 1) * Y + (withKing ? (X * Y) : 0);
}

inline int coordX(int id) {
	// fprintf(stdout, "coordX(id: %d) => %d\n", id, (id / Y) % X + 1);
	return (id / Y) % X + 1;
}

inline int coordY(int id) {
	// fprintf(stdout, "coordY(id: %d) => %d\n", id, id % Y + 1);
	return id % Y + 1;
}

inline bool coordWithKing(int id) {
	// fprintf(stdout, "coordWithKing(id: %d) => %s\n", id, (id / X / Y) ? "true" : "false");
	return id / X / Y;
}

inline bool isValidMove(int cid, int moveId, int *targid = NULL) {
	int x = coordX(cid) + knightMoves[moveId][0];
	int y = coordY(cid) + knightMoves[moveId][1];
	bool f = (x > 0 && x <= X && y > 0 && y <= Y);
	if (f && targid) *targid = coordId(x, y, coordWithKing(cid));
	fprintf(stdout, "isValidMove(cid: %d, moveId: %d, targid: %p(=>%d)) => %s\n", cid, moveId, targid, targid ? *targid : -1, f ? "true" : "false");
	return f;
}

struct Edge {
	int v, c;
	Edge *next;
} *h[MAXN], pool[MAXM];
int edgeTot;

inline void addEdge(int u, int v, int c) {
	Edge *p = pool + (edgeTot ++);
	p->v = v; p->c = c; p->next = h[u];
	h[u] = p;
	fprintf(stdout, "addEdge(u: %d, v: %d, c: %d) => void\n", u, v, c);
}

void buildMap() {
	int u, v, move;
	// Knight moves
	for (u = 0; u < X * Y * 2; u ++)
		for (move = 0; move < 8; move ++)
			if (isValidMove(u, move, &v))
				addEdge(u, v, 1); // Only forward, since backward will be added later
	// Take king
	for (u = 0, v = X * Y; u < X * Y; u ++, v ++)
		addEdge(u, v, kingDist(coordX(u), coordY(u)));
}

struct Node {
	int id, val;
	bool operator >(const Node other) const {
		return (val == other.val) ? (id > other.id) : val > other.val;
	}
} placeholderNode;

priority_queue<Node, vector<Node>, greater<Node> > q;

const int INF = 0x3f3f3f3f;

int dis[MAXN], pre[MAXN];
bool vis[MAXN];

void dijkstra(int src) {
	while (!q.empty()) q.pop();
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	memset(pre, -1, sizeof(pre));
	q.push((Node){src, dis[src] = 0});
	while (!q.empty()) {
		int u = q.top().id; q.pop();
		if (vis[u]) continue;
		vis[u] = true;
		for (Edge *p = h[u]; p; p = p->next) {
			if (dis[p->v] > dis[u] + p->c) {
				pre[p->v] = u;
				q.push((Node){p->v, dis[p->v] = dis[u] + p->c});
			}
		}
	}
}

//MARK: Debug

void printCoord(int id) {
	fprintf(stdout, "[%c%2d]", coordX(id) - 1 + 'A', coordY(id));
}

void printTrace(int src, int dest) {
	printCoord(src);
	while (src != dest && pre[src] >= 0) {
		int nxt = pre[src];
		if (src - nxt >= X * Y) {
			fprintf(stdout, " (king %d)", dis[src] - dis[nxt]);
		} else {
			fprintf(stdout, " > ");
			printCoord(nxt);
		}
		src = nxt;
	}
	fprintf(stdout, " (END)");
}

int camelot;
int ans, sum, minadd, minaddId, kx, ky;

void processDis() {
	sum = 0; minadd = INF;
	for (int i = 1; i <= knightCnt; i ++) {
		kx = knightX(i); ky = knightY(i);
		if (dis[coordId(kx, ky)] == INF) return;
		sum += dis[coordId(kx, ky)];
		if (minadd > dis[coordId(kx, ky, true)] - dis[coordId(kx, ky)]) {
			minadd = dis[coordId(kx, ky, true)] - dis[coordId(kx, ky)];
			minaddId = i;
		}
	}
	if (!knightCnt) minadd = 0;
	ans = min(ans, sum + minadd);
	fprintf(stdout, "\n");
	for (int i = 1; i <= 60; i ++) fprintf(stdout, "*");
	fprintf(stdout, "\n\n");
	fprintf(stdout, "Camelot = "); printCoord(camelot); fprintf(stdout, "\n");
	fprintf(stdout, "King starts from "); printCoord(coordId(kingX, kingY)); fprintf(stdout, "\n\n");
	for (int i = 1; i <= knightCnt; i ++) {
		fprintf(stdout, "Knight #%3d: ", i);
		kx = knightX(i); ky = knightY(i);
		printTrace(coordId(kx, ky, minaddId == i), camelot);
		fprintf(stdout, "\n\tadds %d to total distance.\n", dis[coordId(kx, ky, minaddId == i)]);
	}
	fprintf(stdout, "\nTotal distance: %8d\nAnswer:         %8d\n", sum + minadd, ans);
	fprintf(stdout, "\n");
	for (int i = 1; i <= 60; i ++) fprintf(stdout, "*");
	fprintf(stdout, "\n\n");
}

//MARK: IO

FILE *in, *out;

//MARK: Main

int main(int argc, char const *argv[]) {
	// Input
	fprintf(stdout, "Reading in...\n");
	in = fopen("camelot.in", "r");
	char s_cx[2];
	int cy;
	fscanf(in, "%d%d%s%d", &Y, &X, s_cx, &kingY);
	kingX = ctoi(s_cx[0]);
	while (fscanf(in, "%s%d", s_cx, &cy) != EOF)
		setKnight(++ knightCnt, ctoi(s_cx[0]), cy);
	fclose(in);
	// Calc
	fprintf(stdout, "Building map...\n");
	buildMap();
	fprintf(stdout, "Initialize variable \'ans\' to 0x%x\n", ans = INF);
	fprintf(stdout, "Iterating through tiles...\n");
	for (camelot = 0; camelot < X * Y; camelot ++) {
		dijkstra(camelot);
		processDis();
	}
	// Output
	fprintf(stdout, "Writing output...\n");
	out = fopen("camelot.out", "w");
	fprintf(out, "%d\n", ans);
	fclose(out);
	fprintf(stdout, "Complete!\n");
	return 0;
}

```

洛谷代码（带有myHeap）

```cpp
/*
 TASK: camelot
 LANG: C++
 ID: lutongy1
 */
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <ctime>

using namespace std;

//MARK: Global constants

const int MAXR = 30, MAXC = 45;
const int MAXK = MAXR * MAXC;
const int MAXN = MAXR * MAXC * 2;
const int MAXM = MAXN * 10;

const int knightMoves[8][2] = {
	{1, 2},
	{2, 1},
	{2, -1},
	{1, -2},
	{-1, -2},
	{-2, -1},
	{-2, 1},
	{-1, 2}
};

//MARK: Global variables

int X, Y, knightCnt;

int knights[MAXK], kingX, kingY;

inline bool setKnight(int id, int x, int y) {
	knights[id] = ((x << 5) | y);
	// fprintf(stderr, "setKnight(id: %d, x: %d, y: %d) => %s\n", id, x, y, (x < 0 || x >= 32 || y < 0 || y >= 32) ? "true" : "false");
	return (x < 0 || x >= 32 || y < 0 || y >= 32);
}

inline int knightX(int id) {
	// fprintf(stderr, "knightX(id: %d) => %d\n", id, (knights[id] >> 5) & 0x1f);
	return (knights[id] >> 5) & 0x1f;
}

inline int knightY(int id) {
	// fprintf(stderr, "knightY(id: %d) => %d\n", id, knights[id] & 0x1f);
	return knights[id] & 0x1f;
}

inline int kingDist(int x, int y) {
	// fprintf(stderr, "kingDist(x: %d, y: %d) => %d\n", x, y, max(abs(x), abs(y)));
	return max(abs(x - kingX), abs(y - kingY));
}

inline int ctoi(char c) {
	// fprintf(stderr, "ctoi(c: \'%c\') => %d\n", c, ((c >= 'A' && c <= 'Z') ? c - 'A' + 1 : 0));
	return (c >= 'A' && c <= 'Z') ? c - 'A' + 1 : 0;
}

inline int coordId(int x, int y, bool withKing = false) {
	// fprintf(stderr, "coordId(x: %d, y: %d, withKing: %s) => %d\n", x, y, withKing ? "true" : "false", ((y - 1) + (x - 1) * Y + (withKing ? (X * Y) : 0)));
	return (y - 1) + (x - 1) * Y + (withKing ? (X * Y) : 0);
}

inline int coordX(int id) {
	// fprintf(stderr, "coordX(id: %d) => %d\n", id, (id / Y) % X + 1);
	return (id / Y) % X + 1;
}

inline int coordY(int id) {
	// fprintf(stderr, "coordY(id: %d) => %d\n", id, id % Y + 1);
	return id % Y + 1;
}

inline bool coordWithKing(int id) {
	// fprintf(stderr, "coordWithKing(id: %d) => %s\n", id, (id / X / Y) ? "true" : "false");
	return id / X / Y;
}

inline bool isValidMove(int cid, int moveId, int *targid = NULL) {
	int x = coordX(cid) + knightMoves[moveId][0];
	int y = coordY(cid) + knightMoves[moveId][1];
	bool f = (x > 0 && x <= X && y > 0 && y <= Y);
	if (f && targid) *targid = coordId(x, y, coordWithKing(cid));
	// fprintf(stderr, "isValidMove(cid: %d, moveId: %d, targid: %p(=>%d)) => %s\n", cid, moveId, targid, targid ? *targid : -1, f ? "true" : "false");
	return f;
}

struct Edge {
	int v, c;
	Edge *next;
} *h[MAXN], pool[MAXM];
int edgeTot;

inline void addEdge(int u, int v, int c) {
	Edge *p = pool + (edgeTot ++);
	p->v = v; p->c = c; p->next = h[u];
	h[u] = p;
	// fprintf(stderr, "addEdge(u: %d, v: %d, c: %d) => void\n", u, v, c);
}

void buildMap() {
	int u, v, move;
	// Knight moves
	for (u = 0; u < X * Y * 2; u ++)
		for (move = 0; move < 8; move ++)
			if (isValidMove(u, move, &v))
				addEdge(u, v, 1); // Only forward, since backward will be added later
	// Take king
	for (u = 0, v = X * Y; u < X * Y; u ++, v ++)
		addEdge(u, v, kingDist(coordX(u), coordY(u)));
}

struct Node {
	int id, val;
	bool operator >(const Node other) const {
		return (val == other.val) ? (id > other.id) : val > other.val;
	}
} placeholderNode;

Node heep[1000005];
int heepTot;

void pushHeap(Node x) {
	int id = (++ heepTot);
	while ((id >> 1) && heep[id >> 1] > x) {
		heep[id] = heep[id >> 1];
		id >>= 1;
	}
	heep[id] = x;
}

void popHeap() {
	Node cur = heep[heepTot --];
	int id = 1, id2;
	while (true) {
		if (((id << 1) <= heepTot && cur > heep[id << 1]) && ((id << 1 | 1) <= heepTot && cur > heep[id << 1 | 1])) {
			heep[id] = heep[id2 = (id << 1 | (heep[id << 1] > heep[id << 1 | 1]))];
			id = id2;
		} else if ((id << 1) <= heepTot && cur > heep[id << 1]) {
			heep[id] = heep[id << 1];
			id = (id << 1);
		} else if ((id << 1 | 1) <= heepTot && cur > heep[id << 1 | 1]) {
			heep[id] = heep[id << 1 | 1];
			id = (id << 1 | 1);
		} else {
			break;
		}
	}
	heep[id] = cur;
}

inline Node heapTop() {
	return heep[1];
}

inline bool heapEmpty() {
	return heepTot == 0;
}

const int INF = 0x3f3f3f3f;

int dis[MAXN], pre[MAXN];
bool vis[MAXN];

int dijkstraLoop1Count, dijkstraLoop2Count;
unsigned long qPushTime = 0;

void dijkstra(int src) {
	while (!heapEmpty()) popHeap();
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	// memset(pre, -1, sizeof(pre));
	// unsigned long tmp = clock();
	pushHeap((Node){src, dis[src] = 0});
	// qPushTime += clock() - tmp;
	while (!heapEmpty()) {
		dijkstraLoop1Count ++;
		int u = heapTop().id; popHeap();
		if (vis[u]) continue;
		vis[u] = true;
		for (Edge *p = h[u]; p; p = p->next) {
			dijkstraLoop2Count ++;
			if (dis[p->v] > dis[u] + p->c) {
				// pre[p->v] = u;
				// tmp = clock();
				pushHeap((Node){p->v, dis[p->v] = dis[u] + p->c});
				// qPushTime += clock() - tmp;
			}
		}
	}
}

//MARK: Debug

void printCoord(int id) {
	fprintf(stderr, "[%c%2d]", coordX(id) - 1 + 'A', coordY(id));
}

void printTrace(int src, int dest) {
	printCoord(src);
	while (src != dest && pre[src] >= 0) {
		int nxt = pre[src];
		if (src - nxt >= X * Y) {
			fprintf(stderr, " (king %d)", dis[src] - dis[nxt]);
		} else {
			fprintf(stderr, " > ");
			printCoord(nxt);
		}
		src = nxt;
	}
	fprintf(stderr, " (END)");
}

int camelot;
int ans, sum, minadd, minaddId, kx, ky;

void processDis() {
	sum = 0; minadd = INF;
	for (int i = 1; i <= knightCnt; i ++) {
		kx = knightX(i); ky = knightY(i);
		if (dis[coordId(kx, ky)] == INF) return;
		sum += dis[coordId(kx, ky)];
		if (minadd > dis[coordId(kx, ky, true)] - dis[coordId(kx, ky)]) {
			minadd = dis[coordId(kx, ky, true)] - dis[coordId(kx, ky)];
			// minaddId = i;
		}
	}
	if (!knightCnt) minadd = 0;
	ans = min(ans, sum + minadd);
	/*
	fprintf(stderr, "\n");
	for (int i = 1; i <= 60; i ++) fprintf(stderr, "*");
	fprintf(stderr, "\n\n");
	fprintf(stderr, "Camelot = "); printCoord(camelot); fprintf(stderr, "\n");
	fprintf(stderr, "King starts from "); printCoord(coordId(kingX, kingY)); fprintf(stderr, "\n\n");
	for (int i = 1; i <= knightCnt; i ++) {
		fprintf(stderr, "Knight #%3d: ", i);
		kx = knightX(i); ky = knightY(i);
		printTrace(coordId(kx, ky, minaddId == i), camelot);
		fprintf(stderr, "\n\tadds %d to total distance.\n", dis[coordId(kx, ky, minaddId == i)]);
	}
	fprintf(stderr, "\nTotal distance: %8d\nAnswer:         %8d\n", sum + minadd, ans);
	fprintf(stderr, "\n");
	for (int i = 1; i <= 60; i ++) fprintf(stderr, "*");
	fprintf(stderr, "\n\n");
	*/
}

//MARK: IO

FILE *in, *out;

//MARK: Main

int main(int argc, char const *argv[]) {
	// Input
	fprintf(stderr, "Reading in... t=%lu\n", clock());
	in = stdin;
	char s_cx[2];
	int cy;
	fscanf(in, "%d%d%s%d", &Y, &X, s_cx, &kingY);
	kingX = ctoi(s_cx[0]);
	while (fscanf(in, "%s%d", s_cx, &cy) != EOF)
		setKnight(++ knightCnt, ctoi(s_cx[0]), cy);
	// fclose(in);
	// Calc
	fprintf(stderr, "Building map... t=%lu\n", clock());
	buildMap();
	fprintf(stderr, "Initialize variable \'ans\' to 0x%x... t=%lu\n", ans = INF, clock());
	fprintf(stderr, "Iterating through tiles... t=%lu\n", clock());
	unsigned long dijTime = 0, procTime = 0, timeTmp;
	dijkstraLoop1Count = 0; dijkstraLoop2Count = 0;
	for (camelot = 0; camelot < X * Y; camelot ++) {
		timeTmp = clock();
		dijkstra(camelot);
		dijTime += clock() - timeTmp;
		timeTmp = clock();
		processDis();
		procTime += clock() - timeTmp;
	}
	fprintf(stderr, "dijkstra: %lu µs; processDis: %lu μs\n", dijTime, procTime);
	fprintf(stderr, "dijkstra avg loop times: { 1: %.2lf, 2: %.2lf }\n", (double) dijkstraLoop1Count / X / Y, (double) dijkstraLoop2Count / X / Y);
	// fprintf(stderr, "q.push: %lu µs\n", qPushTime);
	// Output
	fprintf(stderr, "Writing output... t=%lu\n", clock());
	out = stdout;
	fprintf(out, "%d\n", ans);
	// fclose(out);
	fprintf(stderr, "Complete! t=%lu\n", clock());
	return 0;
}

```


---

## 作者：Godのfather (赞：16)

## （〇）写在前面的话

在此之前，该题已经有很多题解，但它们大多是枚举国王周围$5\times 5$的范围（玄学贪心？），最后计算最小距离。

虽然能$AC$，但其实这种做法是不严谨的( 详见巨佬的[hack数据](https://www.luogu.com.cn/discuss/show/101031) )

然而将$5\times 5$的范围扩大至$R\times C$的范围后，时间复杂度过大。那么，这道题真的无解了吗？

蒟蒻的我用spfa在正确的结果和正确的时间复杂度内$AC$了此题(而且过了$hack$数据)。

## （一）解题思路

题目不再阐述。[题目传送门](https://www.luogu.com.cn/problem/P1930)

这道题求的是所有骑士以及国王到某集合点的最小距离(任意骑士与国王汇合后，可以带着国王一起走，并且只算一个人的距离)。

### Step1：关于集合点

集合点是哪一个？不知道。~~不知道就枚举~~

与其它题解无异，看到范围十分小的$R、C$后，毅然选择枚举集合点。

枚举后，相当于已经知道了集合点，求骑士和国王从原所在地到该点的最小距离和。

这个可以反过来看，也就是从集合点出发，求出骑士和国王从集合点到骑士和国王原所在地的距离的最小值。

显然，上述两者是等价的。因此，我们可以用最短路算法直接求出最小的距离之和。这里使用spfa。

### Step2：关于最短路

定义$dis(x, y, 0)$表示集合点到点$(x,y)$的最小距离(最少步数，不带国王)。

定义$dis(x, y, 1)$表示集合点到点$(x,y)$的最小距离(最少步数，此时在点$(x,y)$，骑士已经带上了(或者是正在带着)国王）

考虑如何转移。

显然，对于$dis(x,y,0)$这个状态，可以作两种转移:

1. 当前骑士没有带国王

可以转移出8个状态(即骑士走的八个"日"字)，设转移后的状态为$dis(x', y', 0)$。因为骑士转移到这个状态只需要一步，所以边权为$1$。

转移方程为$dis(x', y', 0) =\min\{dis(x, y, 0) +1\}$

2. 当前骑士带上了国王

可以转移出一个状态，设国王走到$(x,y)$需要的步数为$val$。转移后的状态为$dis(x,y,1)$。

转移方程为$dis(x,y,1)=\min\{dis(x,y,0)+val\}$

同样，$dis(x,y,1)$也可以是从其他的$dis(x',y',1)$转移过来。转移方程很简单。

### Step3：结果的处理

spfa跑完后，我们得到了$dis(x,y,z)$数组，但题目要求的是距离和的最小值。

简单，将最小值累加即可。等等，那么问题来了，哪位骑士带国王$???$

也就是说，我们需要找到一个骑士，累加他的$dis(x,y,1)$，同时累加其它骑士的$dis(x,y,0)$，使得总和最小。

容易证明，$dis(x,y,0)\leq dis(x,y,1)$

因此，我们只需要枚举每个$(x,y)$，求出$\min\{dis(x,y,1)-dis(x,y,0)\}$，然后加上所有$dis(x,y,0)$即可。

最差时间复杂的$\Theta (R^2C^2)$~~时间都花在枚举上了~~，稳稳地过，不需要卡常。

## （二）代码

~~我知道大家喜欢看这个~~

有注释哦。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxr = 45, maxc = 30, INF = 1e6 + 7;
int R, C, Map[maxr][maxc], Kingx, Kingy;
int X[8] = {-1, 1, 2, 2, 1, -1, -2, -2}, Y[8] = {2, 2, 1, -1, -2, -2, -1, 1};
struct node{
	int x, y;
	bool king;//记录是否带国王
};
queue< node > q;
int Abs(int x){//求绝对值 
	if(x < 0) return -x;
	if(x == 0) return 0;
	if(x > 0) return x;
}
int spfa(int x,int y){
	int dis[maxr][maxc][2] = {}; bool vis[maxr][maxc][2] = {};//初始化dis，vis数组(spfa常规操作) 
	for(int i=1; i<=R; i++)//初始化dis数组，同样是常规操作 
		for(int j=1; j<=C; j++)
		    dis[i][j][0] = dis[i][j][1] = INF;
	node t;
	if(x == Kingx and y == Kingy) dis[x][y][1] = 0, t.king = true;//如果集合点的位置是国王的位置(不用考虑国王的移动)，初始状态就是dis[x][y][1] 
	else dis[x][y][0] = 0, t.king = false;//如果集合点的位置不是国王的位置，需要考虑国王的移动，初始状态是dis[x][y][0]
	t.x = x, t.y = y;
	q.push(t);//入队，常规操作 
	vis[x][y][t.king] = true;//标记,常规操作 
	while(!q.empty()){//一下均为spfa常规操作
		int dx = q.front().x, dy = q.front().y;
		bool flag = q.front().king;
		q.pop();
		for(int i=0; i<8; i++){//不进行带国王的操作 
			int ex = dx + X[i], ey = dy + Y[i];
			if(ex < 1 or ey < 1 or ex > R or ey > C) continue;
			if(dis[ex][ey][flag] > dis[dx][dy][flag] + 1){
				dis[ex][ey][flag] = dis[dx][dy][flag] + 1;
				if(!vis[ex][ey][flag]){
					vis[ex][ey][flag] = true;
					node e; e.x = ex, e.y = ey, e.king = flag;
					q.push(e);
				}
			}
		}
		if(!flag){//在(dx, dy)这个点带上国王(让国王自己走到这个点) 
			int val = dis[dx][dy][flag] + max(Abs(dx-Kingx), Abs(dy-Kingy));
			//算出国王走到这个点的步数,国王可以走八个方向，不是曼哈顿距离，而是max(Abs(dx-Kingx), Abs(dy-Kingy),自行画图理解 
			if(dis[dx][dy][!flag] > val){
				dis[dx][dy][!flag] = val;
				if(!vis[dx][dy][!flag]){
					vis[dx][dy][!flag] = true;
					node e; e.x = dx, e.y = dy, e.king = !flag;
					q.push(e);
				}
			}
		}
		vis[dx][dy][flag] = false;
	}
	int minu = INF, cnt = 0;//最短路跑完后，算出最短的总距离
	//容易证明，骑士所在的点的状态dis[x][y][1]>=dis[x][y][0]，要使总距离最小，只需要找最小的(dis[x][y][1]-dis[x][y][0])，最后加上所有骑士的距离dis[x][y][0]即可 
	for(int i=1; i<=R; i++)
	    for(int j=1; j<=C; j++)
	    	if(Map[i][j] == 1) minu = min(minu, dis[i][j][1] - dis[i][j][0]), cnt += dis[i][j][0];
	return cnt+minu;
}
int main(){
	cin>>C>>R;//写到最后发现R,C打反了，不想改了，将就着看吧 
	char kingx;
	cin>>kingx>>Kingy;//读入 
	Kingx = kingx-'A'+1;//Kingx储存国王的横坐标，Kingy储存国王的纵坐标 
	char knightx; int knighty;
	while(cin>>knightx>>knighty){//读入 
		Map[knightx-'A'+1][knighty] = 1;//邻接矩阵标记国王的位置 
	}
	int ans = INF;//初始化 
	for(int i=1; i<=R; i++) 
		for(int j=1; j<=C; j++)
			ans = min(ans, spfa(i, j));//枚举集合点，spfa求最短距离 
	if(ans == INF) printf("0");
	else printf("%d", ans);
	return 0;
}
```

---

## 作者：zhangjianweivv (赞：13)

~~小蒟蒻A了这道题，开心地过来水一波题解~~

思路就是决定先暴力枚举集合点，再看怎么处理国王和骑士更优（也就是怎么把他运过去）（解决骑士要紧）

也就是暴力枚举每一个点，算出所有骑士到这里的距离（当然，这个最小距离还要考虑国王怎么接）然后min一下找到距离最小的点，然后把所有的步数也在这个过程中也累加出来 : )

不过一个一个去枚举太费时间了，但是我又不知道最短路怎么用到这上面；

另外要说的就是，骑士接国王这里也需要一点小技巧。因为骑士接国王最优的情况就是骑士走到以国王为中心5*5的范围内，然后让国王自己走到骑士那里去（如果骑士直接就可以去到国王所在的那个点那国王就不用走路了）。

有一个神奇而有用的思路就是开一个四维数组bk。bk[i][j][k][l]表示从第i行第j列那个点到第k行第l列的那个点的距离。

P.S.：我这里的bk用一个另外的函数进行预处理，用bfs。虽然反复调用bfs很费时间（~~但是貌似很好用~~）。。。

然后！依然是没有A的。因为有几个比较坑爹的数据，比如整个棋盘布满骑士等等很坑的数据点。。。洛谷的数据是没有官网强大的，因为官网还有几个比较坑的数据点。。。比如说下面这个：
```
2 2
A 1
B 2
```
emmm...如果想要代码真的绝对正确的话，可以拿去调试调试。。。

我是被这个数据坑到了，因为事先看了dalao的题解，发现不能斜着走，然后就打了abs(i-king.x)+abs(j-king.y)，但其实是max(abs(i-king.x),abs(j-king.y))。。。

啰嗦了一大堆，具体思路见代码：
```
/*
ID:zhangji78
LANG:C++
TASK:camelot
*/
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int dx[8]={-2,-1,-2,1,2,2,1,-1};//骑士遍历的方向
int dy[8]={-1,2,1,2,1,-1,-2,-2};
const int inf=99999999;//假装这是正无穷（手动滑稽）
struct node
{
    int x,y,s;//用于宽搜的list数组。x->行坐标，y->列坐标，s->到这儿
}list[12000];//需要用几步。
struct wz
{
    int x,y;
}king,knight[12000];
//玄学...明明数据最大也就是26*40，却一定要开到12000，我之前开1200都
//会RE...
int n,m,tj,head,tail;
bool kk[30][50];
int bk[50][30][50][30],all,bs;
//bk[i][j][k][l]表示(i,j)到(k,l)骑士走的距离...
void bfs(int x,int y)
{
//emmm...标准的bfs，如果不喜欢可以改成dfs，但是时间...呵呵...因为
//该函数是要反复调用的...建议用bfs...
    head=1;tail=2;
    list[head].x=x;list[head].y=y;
    bk[x][y][x][y]=0;//这是一个坑点
    memset(kk,false,sizeof(kk));kk[x][y]=true;
    while(head<tail)
    {
    	if(tail==n*m+1)break;
        for(int i=0;i<=7;i++)
        {
            int xx=list[head].x+dx[i],yy=list[head].y+dy[i];
            if(xx>=1&&xx<=n&&yy>=1&&yy<=m)
            {
                if(kk[xx][yy]==false)
                {
                    kk[xx][yy]=true;
                    list[tail].x=xx;list[tail].y=yy;
                    list[tail].s=list[head].s+1;
                    bk[x][y][xx][yy]=list[tail].s;
                    bk[xx][yy][x][y]=list[tail].s;
                    tail++;
                }
            }
        }
        head++;
    }
}
void build_bk()
{
	memset(bk,1,sizeof(bk));//本来想弄63的，后来炸了...
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)bfs(i,j);//反复调用，构建bk数组
	}
}
/*
这玩意儿本来是我之前想着先找集合点确定集合点再看怎么接皇帝的...
后来发现...是我太天真了...
但是还是把它保留着吧...留个纪念...（手动滑稽）
void find()
{
    int minn=inf,sum=0,xx,yy;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            for(int k=1;k<=tj;k++)sum+=bk[knight[k].x][knight[k].y][i][j];
            if(sum<minn)
            {
                minn=sum;
                xx=i;yy=j;
            }
            sum=0;
        }
    }
    for(int k=1;k<=tj;k++)all+=bk[knight[k].x][knight[k].y][xx][yy];
    edx=xx;edy=yy;
}
*/
int kn_ki()
{
    int minnn=inf;
    for(int edx=1;edx<=n;edx++)
    {
    	for(int edy=1;edy<=m;edy++)
    	{
        	//枚举集合点...不会超时...
    		int minn=inf;bool bkkk=false;
    		for(int s=1;s<=tj;s++)
			{
				all+=bk[knight[s].x][knight[s].y][edx][edy];
				if(bk[knight[s].x][knight[s].y][edx][edy]>=bk[0][0][0][0]){bkkk=true;break;}
			}
            //all统计到这个点一共要多少步
            //bkkk是看有没有骑士不能到这里，如果不能到的话就不能做
            //集合点
			if(bkkk==true)
			{
				all=0;
                //这步不能省，贼坑了...
				continue;
			}
		   	for(int s=1;s<=tj;s++)
		    {
		        int ss=inf;
		        for(int i=king.x-2;i<=king.x+2;i++)
		        {
		        	if(i>=1&&i<=n)
		        	{
			        	for(int j=king.y-2;j<=king.y+2;j++)
			            {
			            	if(j>=1&&j<=m)
			            	{
				            	int jl=max(abs(i-king.x),abs(j-king.y));
                                //一大坑点啊...
				                ss=min(ss,bk[knight[s].x][knight[s].y][i][j]+bk[i][j][edx][edy]+jl);
							}
			            }
					}
		        }
		        minn=min(minn,all-bk[knight[s].x][knight[s].y][edx][edy]+ss);
                //不算这个点原来到终点的距离，直接算它接国王的距离
		    }
		    all=0;
            //这步不能省...贼坑...
		    minnn=min(minnn,minn);
		}
	}
    return minnn;
}
int main()
{
    //freopen("camelot.in","r",stdin);
    //freopen("camelot.out","w",stdout);
    scanf("%d%d",&n,&m);
    getchar();char c;int xx,yy;bool bsk=false;
    while(cin>>c)//不能用scanf，会有玄学错误
    {
    	yy=c-'A'+1;
        scanf("%d",&xx);//这玩意儿也是坑点...之前输入的时候是一个字
        				//符一个字符地输入，但是两位数就输入不了了
	    if(bsk==false)king.x=xx,king.y=yy,bsk=true;//如果是第一个
		else
	    {
	        knight[++tj].x=xx;
	        knight[tj].y=yy;
	    }
    }
    if(tj==0)printf("0\n");//坑点*n！若没有骑士，就输出0！
    else
    {
	    build_bk();
	    printf("%d\n",kn_ki());
	}
    return 0;
}
```

本人小蒟蒻，求dalao轻喷...

最后感谢zsyz初一信息班的猴子、Z.W.Q.和Z.F.Y. dalao，是他们一直在帮我调试、想改进的方法、找错误、出数据，我能够A这个代码离不开这些dalao的帮助~

---

## 作者：_Andy_Lin_ (赞：7)

我的思路是这样的：

(1):枚举集合点（不用多说）

(2):设$dis_{x,y,z}$，表示骑士到集合点的步数，$x$,$y$代表坐标，$z$代表是否有国王，0代表没有，1代表有。用Dijkstra求dis数组。公式如下：（xx，yy代表骑士的8种走法，kx，ky代表国王的坐标）

$dis_{x,y,0}=\min\{dis_{x+xx,y+yy,0}\}+1$

$dis_{x,y,1}=\min(\min\{dis_{x+xx,y+yy,1}\}+1,dis_{x,y,0}+\max(abs(x-kx),abs(y-ky))$

初值：$dis_{x,y,0}=0$（x，y代表集合点）

其实题解区已经有一位巨佬用了这个思路。不过他用了SPFA。我这个蒟蒻写SPFA就心惊胆战，生怕被卡。所以我基本不用SPFA，都用Dijkstra。Heap+Dijkstra的算法应该算是比较慢了。不过吸个氧就可以过了。

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
int dis[41][27][2],R,C,ans=INF,kx,ky,k;
bool flag[41][27][2],knight[41][27];
char s[2];
struct data{
	int x,y,z;
}myd1,myd2;
bool operator <(data x,data y){
	return x.x<y.x;
}
priority_queue<pair<int,data> >heap;
const short dd[8][2]={{1,2},{2,1},{-1,2},{2,-1},{1,-2},{-2,1},{-1,-2},{-2,-1}};
inline int dijkstra(int x,int y){
	memset(flag,0,sizeof(flag));
	memset(dis,0x3f,sizeof(dis));
	while(!heap.empty())heap.pop();
	myd1.x=x,myd1.y=y;myd1.z=0;
	dis[x][y][0]=0;
	heap.push(make_pair(0,myd1));
	while(!heap.empty()){
		myd1=heap.top().second;heap.pop();
		if(flag[myd1.x][myd1.y][myd1.z])continue;
		flag[myd1.x][myd1.y][myd1.z]=1;
		for(int i=0;i<8;++i){
			myd2.x=myd1.x+dd[i][0],myd2.y=myd1.y+dd[i][1],myd2.z=myd1.z;
			if(myd2.x<1||myd2.x>R||myd2.y<1||myd2.y>C)continue;
			dis[myd2.x][myd2.y][myd2.z]=min(dis[myd1.x][myd1.y][myd1.z]+1,dis[myd2.x][myd2.y][myd2.z]);
			heap.push(make_pair(-dis[myd2.x][myd2.y][myd2.z],myd2));
		}
		if(!myd1.z){
			dis[myd1.x][myd1.y][1]=min(dis[myd1.x][myd1.y][0]+max(abs(kx-myd1.x),abs(ky-myd1.y)),dis[myd1.x][myd1.y][1]);
			myd1.z=1;
			heap.push(make_pair(-dis[myd1.x][myd1.y][1],myd1));
		}
	}
	int sum=0,now;
	for(int i=1;i<=R;++i){
		for(int j=1;j<=C;++j){
			if(knight[i][j]){
				if(dis[i][j][0]==INF)return INF;
				sum+=dis[i][j][0];
			}
		}
	}
	now=sum+max(abs(kx-x),abs(ky-y));
	for(int i=1;i<=R;++i){
		for(int j=1;j<=C;++j){
			if(knight[i][j])now=min(now,sum+dis[i][j][1]-dis[i][j][0]);
		}
	}
	return now;
}
int main(){
	scanf("%d%d",&R,&C);
	scanf("%s%d",s,&kx);
	ky=s[0]-'A'+1;
	while(~scanf("%s%d",s,&k)){
		knight[k][s[0]-'A'+1]=1;
	}
	for(int i=1;i<=R;++i){
		for(int j=1;j<=C;++j){
			ans=min(ans,dijkstra(i,j));
		}
	}
	printf("%d\n",ans);
	return 0;
}
```
若有些难看，请谅解

---

## 作者：karma (赞：5)

###坑点.

- 输入里国王与骑士的位置第一个是列,第二个是行.因为行有40行,列只有26列.

- 国王只能到与自身相邻的四个方格中,不能斜着走.

- 要特判没有骑士的情况

题中图似乎有误.我看其他AC的代码,似乎国王的步数直接用两点之间的哈密顿距离计算了,我有些不太明白.如果国王八个方向都可以走,那么算出来的答案会比正确答案小.求解答.

###处理方法:刚开始输入棋盘大小时将行与列互换.

###思路:因为国王走的比骑士慢,所以尽量让骑士去接国王.

###步骤:

1. 计算每个点之间以骑士走法的最短路.(如果不能到达则设为极大值)

2. 枚举每个点作为汇集点.分别计算总步数,最后取最小输出.

**总步数公式** : 每个骑士到汇集点的步数 减 将要去接国王的骑士到汇集点的步数 加 国王到"骑士接他的位置"的步数 加 接国王的骑士到"接国王的位置"的步数  加 "接国王的位置"到汇集点的步数= 总步数

###细节:

- 骑士接国王的位置经过证明在国王周围八个格子中或国王本身的位置.不用枚举所有地图上的点作为汇集点.

- 输入字符时建议用cin,用scanf会有玄学错误.

###代码如下(具体见注释):

```cpp
#include<cstdio>
#include<queue>
#include<iostream>
#include<cstring>
using namespace std;
#define maxr 50
#define maxc 50
inline int Min(int x,int y){return x<y?x:y;}
inline int Abs(int x){return x>=0?x:-x;}
int R,C,tot,dis[maxr][maxc][maxr][maxc],t,ans=1<<30;
//t为枚举每个点作为汇集点计算得到的总步数(假设骑士不去接国王)
//ans为最终的最小总步数 
int dir[][2]= {{2,1},{1,2},{-2,1},{-1,2},{-1,-2},{-2,-1},{2,-1},{1,-2}};
//骑士移动方法 
struct node{
    int x,y;
}king,knight[1505];
//king为国王的位置,knight为骑士的位置 
queue<node>q;//BFS所需要的队列(也可以手写) 
using namespace std;
void init(){
    memset(dis,0x3f,sizeof(dis));//初始为极大值 
    char c;
    scanf("%d%d",&C,&R);
    cin>>c>>king.y;
    king.x=c-'A'+1;
    while(cin>>c) {
        knight[++tot].x=c-'A'+1;
        scanf("%d",&knight[tot].y);
    }//读入
    //将字符转化为整数 并且 数组下标从1开始 
}
void bfs(int sx,int sy){//bfs(起始位置) 
    dis[sx][sy][sx][sy]=0;//从起始位置到起始位置所需步数为 0
    q.push((node){sx,sy});
    while(!q.empty()){
        node now=q.front();q.pop();
        for(int i=0;i<8;++i){
            int cx=now.x+dir[i][0],cy=now.y+dir[i][1];//骑士走法 
            if(cx>=1&&cx<=R&&cy>=1&&cy<=C&&dis[sx][sy][cx][cy]==1061109567){//未越界且访问过 
                dis[sx][sy][cx][cy]=dis[sx][sy][now.x][now.y]+1;//标记步数 
                q.push((node){cx,cy});
            }
        }
    }
}
void check(int mux,int muy,int fi,int ret){//参数:汇集点坐标,第几个骑士去接国王,之前的得到的步数总和 
    ret-=dis[knight[fi].x][knight[fi].y][mux][muy];//先减去该骑士到汇集点的距离 
    for(int i=-1;i<=1;++i)//在国王周围或国王本身的位置 
    for(int j=-1;j<=1;++j){
        int ex=king.x+i,ey=king.y+j;//枚举汇集点 
        if(ex>=1&&ex<=R&&ey>=1&&ey<=C){//为越界 
            ans=Min(ans,ret+dis[knight[fi].x][knight[fi].y][ex][ey]+dis[ex][ey][mux][muy]+Abs(ex-king.x)+Abs(ey-king.y));
        }//由计算公式更新ans 
    }
}
int main(){
    init();
    if(tot==0){printf("0");return 0;}//特判没有骑士的情况 
    for(int i=1;i<=R;++i)for(int j=1;j<=C;++j)bfs(i,j);//求出每个点到棋盘上任意一点的最短路 
    for(int i=1;i<=R;++i)
    for(int j=1;j<=C;++j){
        t=0;//清空为0 
        for(int k=1;k<=tot;++k)t+=dis[knight[k].x][knight[k].y][i][j];//先得到总和 
        for(int k=1;k<=tot;++k)check(i,j,k,t);//检查并更新ans 
    }
    printf("%d",ans);//输出 
    return 0;
}
```

---

## 作者：System32 (赞：4)

[这篇题解](https://www.luogu.com.cn/article/siq0rl96)里有这样一段话：

> 4. 那这题是不是没做头了？
> 
> 题当然还是可以做，你可以枚举棋盘上每一个点来判断是否为王与骑士相遇点，然后暴力枚举骑士，再暴力枚举集合点，最劣是 $O(R^3*C^3)$ ，但是不可能达到这么大。

但是实际上没有 $R \times C$ 这么多点（但是 $5 \times 5$ 和 $7 \times 7$ 很明显不够）。

![](https://cdn.luogu.com.cn/upload/image_hosting/2als1t68.png)

先考虑对角线的情况，图中红点是国王，黄点是骑士，绿色箭头是骑士的移动路线。

这段路线骑士走会产生 $4$ 的代价，但国王走只有 $3$ 的代价，由此可以得出上车点在对角线上时只能让国王走到上车点。

![](https://cdn.luogu.com.cn/upload/image_hosting/s531tt7q.png)

手玩一下这幅图（也可以写暴力来验证），可以得出结论：如果上车点在黄色点上，那么就一定会让国王走到上车点。

所以只需要把 $5 \times 5$ 的题解~~复制~~借鉴一下，把贪心范围加上国王所处的两条对角线就可以了。

最后时间复杂度为 $O((R + C) \times R^2 \times C^2)$，可以通过本题。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

struct node {
	int x, y;
	int d;
} pe[2010];

int r, c, dx[] = {1, 2, 2, 1, -1, -2, -2, -1},  dy[] = {2, 1, -1, -2, -2, -1, 1, 2}, cnt;
bool v[50][30];
int ans = 1145141919810ll, d[50][30][50][30];

void bfs(int a, int b) {
	queue<node> q;
	q.push({a, b, 0});
	v[a][b] = 1;
	d[a][b][a][b] = 0;
	while (!q.empty()) {
		int x = q.front().x, y = q.front().y;
		d[a][b][x][y] = q.front().d;
		q.pop();
		for (int i = 0; i < 8; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx >= 1 && nx <= r && ny >= 1 && ny <= c && !v[nx][ny]) {
				v[nx][ny] = 1;
				q.push({nx, ny, d[a][b][x][y] + 1});
			}
		}
	}
}

signed main() {
	cin >> r >> c;
	for (int i = 0; i <= r + 1; i++) {
		for (int j = 0; j <= c + 1; j++) {
			for (int a = 0; a <= r + 1; a++) {
				for (int b = 0; b <= c + 1; b++) {
					d[i][j][a][b] = 2e8;
				}
			}
		}
	}
	char t1;
	int t2;
	while (cin >> t1 >> t2) {
		pe[cnt].x = t2;
		pe[cnt].y = t1 - 'A' + 1;
		cnt++;
	}
	cnt--;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			memset(v, 0, sizeof(v));
			bfs(i, j);
		}
	}
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			int g = 0;
			for (int k = 1; k <= cnt; k++) {
				g += d[pe[k].x][pe[k].y][i][j];
			}
			ans = min(g + max(abs(pe[0].x - i), abs(pe[0].y - j)), ans);
			for (int k = 1; k <= cnt; k++) {
				int temp = g - d[pe[k].x][pe[k].y][i][j];
				for (int a = max(1ll, pe[0].x - 2); a <= min(r, pe[0].x + 2); a++) {
					for (int b = max(1ll, pe[0].y - 2); b <= min(c, pe[0].y + 2); b++) {
						ans = min(temp + d[pe[k].x][pe[k].y][a][b] + max(abs(a - pe[0].x), abs(b - pe[0].y)) + d[a][b][i][j], ans);
					}
				}
				int a = pe[0].x, b = pe[0].y;
				while (a > 0 && b > 0) {
					a--;
					b--;
					ans = min(temp + d[pe[k].x][pe[k].y][a][b] + max(abs(a - pe[0].x), abs(b - pe[0].y)) + d[a][b][i][j], ans);
				}
				a = pe[0].x, b = pe[0].y;
				while (a > 0 && b <= c) {
					a--;
					b++;
					ans = min(temp + d[pe[k].x][pe[k].y][a][b] + max(abs(a - pe[0].x), abs(b - pe[0].y)) + d[a][b][i][j], ans);
				}
				a = pe[0].x, b = pe[0].y;
				while (a <= r && b > 0) {
					a++;
					b--;
					ans = min(temp + d[pe[k].x][pe[k].y][a][b] + max(abs(a - pe[0].x), abs(b - pe[0].y)) + d[a][b][i][j], ans);
				}
				a = pe[0].x, b = pe[0].y;
				while (a <= r && b <= c) {
					a++;
					b++;
					ans = min(temp + d[pe[k].x][pe[k].y][a][b] + max(abs(a - pe[0].x), abs(b - pe[0].y)) + d[a][b][i][j], ans);
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Limit (赞：3)

这题主要是玄学输入+玄学理解+玄学时间复杂度+玄学定理呀QAQ...
至于玄学理解其他题解已经讲得很清楚了呀，主要还是让大家看看我的玄学代码呀QAQ....
```pascal
//先玄学理解呀
const z:array[1..8,1..2]of -2..2=((1,2),(1,-2),(-1,2),(-1,-2),(2,1),(2,-1),(-2,1),(-2,-1));
var i,j,k,ix,iy:longint;
    m,n,h,t,sum,q:longint;
    kingx,kingy:longint;
    x_ch:array[char]of longint;
    min,p:array[-1..100,-1..100]of longint;
    x,y,u:array[0..10000]of longint;
    main:longint=maxlongint;
    boo:array[-1..100,-1..100]of boolean;
    ans:array[-1..30,-1..50,-1..30,-1..50] of longint;
    s:string;
    ch:char;
function mine(m,n:longint):longint;//min
begin
  if m>n then exit(n) else exit(m);
end;
function max(m,n:longint):longint;//max
begin
  if m>n then exit(m) else exit(n);
end;
procedure find(x1,y1:longint);//以x1,y1为终点呀QAQ
var i,j,k,pd:longint;
begin
  for i:=-2 to 2 do//玄学定理，不知道是谁怎么的呀
  for j:=-2 to 2 do//接国王的位置一定在国王旁边2格内
  if boo[kingx+i,kingy+j] then
  begin
    pd:=0;
    for k:=1 to sum do
    inc(pd,ans[x1,y1,x[k],y[k]]);
    main:=mine(main,pd+max(abs(x1-kingx),abs(y1-kingy)));//当国王直接走到终点
    for k:=1 to sum do
    begin
      main:=mine(main,
      pd-ans[x1,y1,x[k],y[k]]{骑士直接去终点}+ans[kingx+i,kingy+j,x[k],y[k]]{骑士到接的位置}+
      ans[x1,y1,kingx+i,kingy+j]{从接的位置到终点}+max(abs(i),abs(j))){国王到接的位置};//第k个骑士去接国王呀
    end;
  end;
end;
begin
  readln(m,n);
  k:=m;
  m:=n;
  n:=k;
  for ch:='A' to 'Z' do x_ch[ch]:=ord(ch)-ord('A')+1;
  read(ch,k);kingx:=x_ch[ch];kingy:=k;//读入国王位置呀QAQ
  for ix:=1 to m do
  for iy:=1 to n do
  for i:=1 to m do
  for j:=1 to n do ans[ix,iy,i,j]:=123123123;//赋初值
  for ix:=1 to m do//用bfs计算每两个点之间的最短步数,四次居然不超呀，玄学时间复杂度....
  for iy:=1 to n do
  begin
    x[1]:=ix;
    y[1]:=iy;
    u[1]:=0;
    h:=1;
    t:=1;
    for i:=1 to m do
    for j:=1 to n do
    boo[i,j]:=true;
    boo[ix,iy]:=false;
    ans[ix,iy,ix,iy]:=0;
    repeat
      for i:=1 to 8 do
      if boo[x[t]+z[i,1],y[t]+z[i,2]] then
      begin
        inc(h);
        x[h]:=x[t]+z[i,1];
        y[h]:=y[t]+z[i,2];
        u[h]:=u[t]+1;
        ans[ix,iy,x[h],y[h]]:=u[h];//保存最优解呀
        boo[x[h],y[h]]:=false;
      end;
      inc(t);
    until t>h;
  end;
  while not eof do//玄学读入
  begin
    readln(s);//字符串，真麻烦...
    for i:=1 to length(s) do
    begin
      if (s[i] in ['A'..'Z']) then
      begin
        inc(sum);
        x[sum]:=x_ch[s[i]];
        k:=0;
        j:=i+2;
        while (s[j] in ['0'..'9']) and (j<=length(s))do
        begin
          k:=k*10+ord(s[j])-48;
          inc(j);
        end;
        y[sum]:=k;
      end;
    end;
  end;
  if sum=0 then begin write(0); exit; end;
  for i:=1 to m do
  for j:=1 to n do boo[i,j]:=true;
  for i:=1 to m do
  for j:=1 to n do
  begin
    find(i,j);//找最优解呀QAQ
  end;
  write(main);//输出
end.
```
这是一道玄学难题，难度挺高的，辛苦调了2个小时，，，

---

## 作者：封禁用户 (赞：3)

这道题目，应该是明显的$BFS$吧。。。

不过，我们要注意其实只要到以国王为中心的$5*5$的范围即可。

本人用了$4$维数组，请$dalao$们勿喷$QWQ$

下附代码：
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
int dx[8]={-2,-1,1,2,2,1,-1,-2},dy[8]={-1,-2,-2,-1,1,2,2,1};
int r,c,starth,startl,sb[2000][2],cnt;
int q[2000][3],head,tail;
int best[50][50][50][50];
int answer=0x3f3f3f3f;
bool flag;
char ch;
using namespace std;
void BFS(int sx,int sy)//bfs
{
    head=0;
    tail=1;
    q[1][0]=sx;
    q[1][1]=sy;
    q[1][2]=0;
    while (head<tail)
    {
        head++;
        for (int i=0;i<8;i++)
        {
            int nx=q[head][0]+dx[i];
            int ny=q[head][1]+dy[i];
            if (nx<=0||nx>r||ny<=0||ny>c) continue;
            if (best[sx][sy][nx][ny]>q[head][2]+1)
            {
                tail++;
                q[tail][0]=nx;
                q[tail][1]=ny;
                q[tail][2]=q[head][2]+1;
                best[sx][sy][nx][ny]=q[tail][2];
                best[nx][ny][sx][sy]=q[tail][2];
            }
        }
    }
}
int main()
{
    memset(best,0x3f3f3f3f,sizeof(best));
    scanf("%d%d",&c,&r);
    while (cin>>ch)
    {
        if (flag)
        {
            scanf("%d",&sb[++cnt][1]);
            sb[cnt][0]=ch-64;
        } else
        {
            scanf("%d",&startl);
            starth=ch-64;
            flag=1;
        }
    }
    for (int i=1;i<=r;i++)
      for (int j=1;j<=c;j++)
      {
        best[i][j][i][j]=0;
        BFS(i,j);
      }
    for (int i=1;i<=r;i++)
      for (int j=1;j<=c;j++)
      {
      	flag=1;
      	int s=0;
      	for (int k=1;k<=cnt;k++) 
      	  if (best[sb[k][0]][sb[k][1]][i][j]<0x3f3f3f3f)
            s+=best[sb[k][0]][sb[k][1]][i][j]; else
            {
            	flag=0;
            	break;
            }
        if (!flag) continue;
      	for (int k=1;k<=cnt;k++)
      	{
      		if (s+max(abs(starth-i),abs(startl-j))<answer)
      		  answer=s+max(abs(starth-i),abs(startl-j));
      		for (int ii=starth-2;ii<=starth+2;ii++)
      		  for (int jj=startl-2;jj<=startl+2;jj++)
      		    if (ii>0&&ii<=r&&jj>0&&jj<=c)
      		    {
      		    	if (best[sb[k][0]][sb[k][1]][i][j]==0x3f3f3f3f) 
      		    	{
      		    		flag=0;
      		    		break;
      		    	}
      		    	if (best[sb[k][0]][sb[k][1]][ii][jj]==0x3f3f3f3f)
      		    	{
      		    		flag=0;
      		    		break;
      		    	}
      		    	if (best[ii][jj][i][j]==0x3f3f3f3f)
      		    	{
      		    		flag=0;
      		    		break;
      		    	}
      		    	if (s-best[sb[k][0]][sb[k][1]][i][j]+best[sb[k][0]][sb[k][1]][ii][jj]+best[ii][jj][i][j]+max(abs(starth-ii),abs(startl-jj))<answer)
      		      answer=s-best[sb[k][0]][sb[k][1]][i][j]+best[sb[k][0]][sb[k][1]][ii][jj]+best[ii][jj][i][j]+max(abs(starth-ii),abs(startl-jj));
      		    }	  		    
      	}
      }
    if (answer==0x3f3f3f3f) answer=0;
    printf("%d\n",answer);
    return 0;
}```

---

## 作者：happy_dengziyue (赞：2)

### 1 思路

输入，设国王坐标为 $(sx,sy)$。

这道题主要是广度优先搜索。

首先，通过广度优先搜索，找出每对点的走“日”字形的最短路。设从 $(i,j)$ 走到 $(a,b)$ 需要 $dis[i][j][a][b]$ 的时间。

很明显，$dis[i][j][a][b]=dis[a][b][i][j]$，不过貌似它不重要。

事实上，这一段也可以用 `Floyd` 算法解决，但是速度会慢很多，光是这一项都可能超时。

然后，枚举每一个点为集合点。设它的坐标为 $(x,y)$。

每次枚举时，都计算出所有的骑士到这个点（忽略国王）所花费的时间，设它为 $sum$。

那么，如果骑士都不去接国王，则花费时间为：

$$sum+\operatorname{max}(|sx-x|,|sy-y|)$$

然后，我们设去接国王的骑士的坐标为 $(jx,jy)$，它在 $(nx,ny)$ 点接到了国王。

那么，此方案花费时间就是：

$$sum-dis[jx][jy][x][y]+dis[jx][jy][nx][ny]+\operatorname{max}(|sx-nx|,|sy-ny|)+dis[nx][ny][x][y]$$

取最小值即可。

另外，枚举接送点时，只需要枚举以骑士为中心的 $5\times5$ 的方格即可。

本篇代码已经通过了 @[天泽龟](/user/15984) 的 [hack 数据](https://www.luogu.com.cn/discuss/101031)。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define max_n 45//最大尺寸
#define inf 20000000//很大的数
int n;//行数（字母）
int m;//列数（数字）
int dis[max_n+2][max_n+2][max_n+2][max_n+2];//预处理的字母
struct W{//路径结构体
	int x,y,t;//坐标、时间
};
queue<W>q;//队列
bool vis[max_n+2][max_n+2];//访问情况
const int dx[8]={-2,-2,-1,1,2,2,1,-1};//方向数组
const int dy[8]={-1,1,2,2,1,-1,-2,-2};//方向数组
char s[2];//一个字符串
int x;//一个坐标
int sx,sy;//起点坐标
struct K{//骑士结构体
	int x,y;//坐标
}k[max_n*max_n+2];//骑士
int ki=0;//下标
int sum;//求和
int ans=inf;//答案
void askdis(const int sx,const int sy){
	memset(vis,0,sizeof(vis));
	dis[sx][sy][sx][sy]=0;
	vis[sx][sy]=true;
	q.push((W){sx,sy,0});
	register W f;//队首
	while(!q.empty()){
		f=q.front();
		q.pop();
		for(register int d=0,nx,ny;d<8;++d){
			nx=f.x+dx[d];
			ny=f.y+dy[d];
			if(nx<1||nx>n||ny<1||ny>m)continue;//注意不要越界
			if(vis[nx][ny])continue;
			dis[sx][sy][nx][ny]=f.t+1;
			vis[nx][ny]=true;
			q.push((W){nx,ny,f.t+1});
		}
	}
}
inline int absi(int a){
	return a>=0?a:-a;
}
inline int ma(int a,int b){
	return a>b?a:b;
}
inline int mi(int a,int b){
	return a<b?a:b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("P1930_1.in","r",stdin);
	freopen("P1930_1.out","w",stdout);
	#endif
	scanf("%d%d",&m,&n);//行和列别搞反了
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			for(int x=1;x<=n;++x){
				for(int y=1;y<=m;++y)dis[i][j][x][y]=inf;
			}
		}
	}
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=m;++j)askdis(i,j);
	}
	scanf("%s%d",s,&sy);
	sx=s[0]-'A'+1;
	while(scanf("%s%d",s,&x)!=EOF)k[++ki]=(K){s[0]-'A'+1,x};
	for(register int x=1;x<=n;++x){//枚举集合点
		for(register int y=1;y<=m;++y){
			sum=0;
			for(register int i=1;i<=ki;++i)sum+=dis[k[i].x][k[i].y][x][y];//都不接的时候骑士步数
			ans=mi(ans,sum+ma(absi(sx-x),absi(sy-y)));
			for(register int j=1;j<=ki;++j){//枚举接送骑士
				for(register int nx=ma(1,k[j].x-3);nx<=mi(k[j].x+3,n);++nx){//枚举接送点
					for(register int ny=ma(1,k[j].y-3);ny<=mi(k[j].y+3,m);++ny){
						ans=mi(ans,/*公式开始*/sum-dis[k[j].x][k[j].y][x][y]+dis[k[j].x][k[j].y][nx][ny]+ma(absi(sx-nx),absi(sy-ny))+dis[nx][ny][x][y]/*公式结束*/);
						/*右部公式
						=所有骑士到达集合点的距离（1）-接送骑士到集合点的距离（2）+接送骑士到接送点的距离（3）+国王到接送点的距离（4）+骑士从接送点到集合点的距离（5）
						=总距离
						*/
					}
				}
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/58957837)

By **dengziyue**

---

## 作者：GoAway (赞：1)

这一题有一点意思

一种可行的办法是：暴力枚举所有棋子最终汇合的点（O(NM)），然后再处理出这个终点到每个点的距离f[x][y]（BFS），再对于每个骑士，就知道单独的步数了。难点是国王，现在可以让每个骑士跳到终点去（由于已经算出位置，所以只要往距离-1的点跳就行），标记路上的点。再以国王为起点BFS，不难发现，对于第一个走到的骑士走过的点，国王直接上去就是当前的最优解。

具体有一些细节，详见代码吧

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std ;

const int maxn = 50 ;
int n, m, f[maxn][maxn], Kx, Ky, ans = 1<<29, stp[maxn][maxn] ; // f是到终点的距离，(Kx,Ky)是国王坐标, stp(step)是以国王为起点的距离
bool p[maxn][maxn] ; // 骑士路径上经过点的标记
const int go[8][2] = { {1,2}, {2,1}, {-1,2}, {2,-1}, {1,-2}, {-2,1}, {-2,-1}, {-1,-2} } ;
const bool dir[8][2] = { {1,0}, {0,1}, {-1,0}, {0,-1}, {1,1}, {-1,-1}, {1,-1}, {-1,1} } ;

struct node {
    int x, y ;
} ; //用于queue中

bool Judge ( int x, int y ) {
    if ( x < 1 || y < 1 || x > n || y > m ) return false ;
    if ( f[x][y] != -1 ) return false ; // 判断这个点是否已经走过
    return true ;
}
bool judge ( int x, int y ) {
    if ( x < 1 || y < 1 || x > n || y > m ) return false ;
    if ( p[x][y] ) return false ; // 判断这个点骑士是否已经跳过
    return true ;
}
bool pd ( int x, int y ) {
    if ( x < 1 || y < 1 || x > n || y > m ) return false ;
    if ( stp[x][y]!=-1 ) return false ; //判断这个点国王是否已经走过
    return true ;
}

queue<node> q ; // BFS用
vector<node> K ; // 存储骑士
int calc_king ( int rec = 1<<29 ) { //专门计算国王
    int i, j, u, v, x, y ;
    x = Kx, y = Ky ;
    memset ( stp, -1, sizeof(stp) ) ; //初始化
    while ( !q.empty() ) q.pop() ;
    q.push( (node){x,y} ) ;
    stp[x][y] = 0 ;
    while ( !q.empty() ) {
        x = q.front().x ; y = q.front().y ;
        q.pop() ;
        if ( p[x][y] ) rec = min ( rec, stp[x][y] ) ; //如果遇到骑士，就坐顺风车
        for ( i = 0 ; i < 8 ; i ++ ) {
            u = x+go[i][0] ;
            v = y+go[i][1] ;
            if ( !pd(u,v) ) continue ;
            stp[u][v] = stp[x][y]+1 ;
            if ( p[u][v] ) rec = min ( rec, stp[u][v] ) ; // 同
            else q.push( (node){u,v} ) ;
        }
    }
    return rec ;
}
void Jump ( int x, int y ) { //骑士往终点跳
    p[x][y] = 1 ;
    int i, j, u, v, xx, yy ;
    for ( i = 0 ; i < 8 ; i ++ ) {
        u = x+go[i][0] ;
        v = y+go[i][1] ;
        if ( !judge(u,v) ) continue ;
        if ( f[u][v]+1==f[x][y] ) Jump ( u, v ) ; // 注意，这里是每个满足的点都要跳，因为你不确定所有可行路径中那一条离国王最近
    } 
}
int BFS ( int x, int y, int rec = 0 ) { //处理出到终点的距离
    int i, j, u, v ;
    while ( !q.empty() ) q.pop() ;
    q.push ( (node){x,y} ) ;
    f[x][y] = 0 ;
    memset ( p, 0, sizeof(p) ) ;
    p[x][y] = 1 ;
    //printf ( "%c %d : \n", y+'A'-1, x ) ;
    while ( !q.empty() ) {
        x = q.front().x ; y = q.front().y ;
        q.pop() ;
        for ( i = 0 ; i < 8 ; i ++ ) {
            u = x+go[i][0] ;
            v = y+go[i][1] ;
            if ( !Judge(u,v) ) continue ;
            f[u][v] = f[x][y]+1 ;
            q.push( (node){u,v} ) ;
        }
    }
    for ( i = 0 ; i < K.size() ; i ++ ) {
        x = K[i].x, y = K[i].y ;
        if ( f[x][y] < 0 ) return (1<<29) ;
        rec += f[x][y] ;  // 单个骑士的步数
        if ( rec >= ans ) return rec ;
        Jump(x,y) ;
    }
    /*for ( i = 1 ; i <= n ; i ++, putchar('\n') ) 
        for ( j = 1 ; j <= m ; j ++ ) 
            printf ( "%d ", f[i][j] ) ;
    printf ( "all knights : %d\n\n", rec ) ;*/
    rec += calc_king() ;
    return rec ;
}

char c[5] ;
int main() {
    int i, j, k ;
    scanf ( "%d%d", &n, &m ) ;
    scanf ( "%s%d", c, &k ) ;
    Ky = c[0]-'A'+1 ; Kx = k ;
    while ( scanf ( "%s%d", c, &k ) != EOF )
        K.push_back( (node){k,c[0]-'A'+1} ) ;
    for ( i = 1 ; i <= n ; i ++ ) 
        for ( j = 1 ; j <= m ; j ++ ) {
            memset ( f, -1, sizeof(f) ) ;
            ans = min ( ans, BFS(i,j) ) ;
        }
    printf ( "%d\n", ans ) ;
    return 0 ;
}
```

---

## 作者：ReModer (赞：0)

最短步数 = 骑士所走的步数 + 国王所走的步数。

对于骑士走的步数，以集合点为源点bfs即可;  
对于国王走的步数，如果不在骑士可以走的点上，就让他找骑士或直接去集合点。

bfs中用了一个exist[i][j]数组，表示(i,j)处存在的棋子数；cntt则表示已经完成的骑士数量。显然当cntt为骑士总数量cnt时就可以完成bfs了。同时这里用来一个小剪枝，当前步数大于目前最优解就直接跳过。

标记骑士可以走过的点的方法是通过[[UVA1599] 理想路径](https://www.luogu.org/problemnew/show/UVA1599)学来的，以集合点为源点bfs完之后，处于dis[i][j]的骑士，下一步必然走到dis[i][j]-1的点上，当然，如果有多个dis[i][j]-1，那每一个都可以走，所以说是骑士**可以**走到的点。

国王找骑士的话，我直接让他去到了各骑士的起点。~~但是不知道为什么就是A过去了~~

暴力枚举集合点，bfs后更新答案即可。

代码：
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cmath>
#define M(x,y) make_pair((x),(y)) 
using namespace std;

const int maxr = 300;
const int maxc = 500;
const int maxn = 1e6 + 10;
const int dx[] = {-2,-1,1,2,2,1,-1,-2};
const int dy[] = {1,2,2,1,-1,-2,-2,-1};
pair<int,int> knight[maxn],king;
int dis[maxr][maxc];
int exist[maxr][maxc]; //标记格子上有多少棋子(其实只有0、1和2三种值)
bool vis[maxr][maxc],able[maxr][maxc]; //able[i][j]为真表示有骑士走这一格
int n,m,a,b,cnt,ans=9999;

void input();
bool inMap(int,int);
void bfs(int,int); 
void mark(int,int);
void solve();
void output();

int main(){
    input();
    solve();
    output();
    return 0;
}

void input(){
    scanf("%d%d",&n,&m); char t;
    cin >> t >> king.first; king.second = t - 'A' + 1;
    while (cin >> t >> knight[cnt].first) {
        knight[cnt].second = t - 'A' + 1,
        exist[knight[cnt].first][knight[cnt++].second]++;
    }
}

bool inMap(int x,int y){
    return x > 0 && x <= n && y > 0 && y <= m; 
}

void bfs(int sx, int sy){
    memset(dis,-1,sizeof(dis)); bool flag = 1;
    memset(able,0,sizeof(able));
    queue<pair<int,int> > q; int cntt = exist[sx][sy], p = 0;
    dis[sx][sy] = 0; q.push(M(sx,sy));
    
    while (!q.empty() && flag){ //小剪枝，如果现在已经有大于最优解的步数，剪掉
        int x = q.front().first;
        int y = q.front().second; q.pop();
        
        for (int i = 0; i < 8; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!inMap(nx,ny) || dis[nx][ny] > -1) continue;
            dis[nx][ny] = dis[x][y] + 1;
            cntt += exist[nx][ny];
            if (cntt == cnt || dis[nx][ny] > ans) 
                {flag = 0; break;} //搜完所有骑士 或 满足剪枝条件
            q.push(M(nx,ny));
        }
    } 
    
    if (cntt != cnt) return; //有骑士无法走到这一集合点，此情况无解
    
    int t = 9999;
    for (int i = 0; i < cnt; i++)
        mark(knight[i].first,knight[i].second); //标记骑士能走的点
    
    t = min(t,abs(king.first-sx) + abs(king.second-sy)); //国王直接走到集合点的步数
    for (int i = 0; i < cnt; i++){
        p += dis[knight[i].first][knight[i].second];
        t = min(abs(king.first-knight[i].first)+abs(king.second-knight[i].second),t); //国王走到骑士起点的位置
    }
    if (able[king.first][king.second]) t = 0; //如果骑士能走到国王所在位置，国王不需走动
    
    ans = min(ans,p+t); //更新答案
}

void mark(int x, int y){
    queue<pair<int,int> > q;
    q.push(M(x,y)); able[x][y] = 1;
    
    while (!q.empty()){
        int x = q.front().first;
        int y = q.front().second; q.pop();
        
        for (int i = 0; i < 8; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!inMap(nx,ny) || dis[x][y] - 1 != dis[nx][ny] || able[nx][ny]) 
                continue; //骑士下一步走的点到集合点的距离 必须是 这个点到集合点的距离 减一。
            able[nx][ny] = 1;
            q.push(M(nx,ny));
        }
    }
}

void solve(){
    //枚举集合点
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            bfs(i,j);
}

void output(){
    if (ans == 9999) cout << 0 << endl;
    else cout << ans << endl;
}
```


---

## 作者：QianhanOfficial (赞：0)

蒟蒻花了两天硬肛过这道题 心情~~偷税~~愉悦 期间心态崩过想学习题解 但发现题解里面只有四维数组解法 眼花缭乱 于是本蒟蒻打算自己写过这道题。  
我的主要思想是：  
## BFS
先一遍bfs求出每个骑士到达各个点的步数并相加，如果存在不能到达的点就设为-1(初始化的时候已经处理为-1)。注意特判没有骑士的情况。  
第二步处理出国王到各个点的步数。  
第三步枚举每个骑士接送国王，先从总步数的数组a中减去该骑士原先的步数，再将该骑士原本到达各点的最短步数与国王步数相加求出**接国王的最少步数**。  
第四步是以**接国王的最少步数**的位置为起点再次bfs，求出该点到各点的最少步数，然后把结果加上**接国王的最少步数**即可求出该骑士接国王后到达集合点的最少步数。  
但是要注意，接国王的最少步数有可能有多个位置。所以我们使用minx和miny两个数组保存位置坐标。再一个个枚举位置。  
本题解得以实现的原因是事先已经求出了到各点的最少步数，这样单独改变一个骑士和国王的步数并不会影响到全局 反而能够更加直观的求出最短步数。  
（英文部分是我写代码时候懒得调输入法的注释，觉得大概能够帮助理解就留着了。）
```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<iomanip>
#include<algorithm>
#define re register
using namespace std;

struct node//for bfs
{
    int x;
    int y;
    int cnt;
};

vector<node> q;//储存骑士坐标
queue<node> tmp;//bfs用临时队列

int r, c, kx, ky, minx[40 * 27], miny[40 * 27], ans = 2147483647;
int dx[16] = {1,  1, 2,  2, -1, -1, -2, -2, 1, 1,  1, 0,  0, -1, -1, -1};
int dy[16] = {2, -2, 1, -1,  2, -2,  1, -1, 0, 1, -1, 1, -1, -1,  1,  0};
int a[27][41], k[27][41], e[27][41], f[28][42];
bool vis[27][41];

void bfs(node s)
{
    int sx = s.x, sy = s.y;//起始坐标
    while(!tmp.empty()) tmp.pop();//别忘了清空队列
    tmp.push(s);
    if(a[sx][sy] < 0) a[sx][sy] = 0;//如果尚未出现骑士 更新。
    vis[sx][sy] = true;
    while(!tmp.empty())
    {
        int x = tmp.front().x, y = tmp.front().y, cnt = tmp.front().cnt;
        tmp.pop();
        for(re int i = 0; i < 8; ++i)//x:lie
        {
            int nx = x + dx[i], ny = y + dy[i];
            if(!vis[nx][ny] && nx >= 1 && nx <= c && ny >= 1 && ny <= r)
            {
                vis[nx][ny] = true;
                if(a[nx][ny] >= 0) a[nx][ny] += cnt + 1;//如果尚未出现骑士 更新。
                else a[nx][ny] = cnt + 1;//否则该位置步数加上该骑士步数
                tmp.push((node){nx, ny, cnt + 1});
            }
        }
    }
}

void kbfs(node s)//国王步数计算
{
    int sx = s.x, sy = s.y;
    while(!tmp.empty()) tmp.pop();
    tmp.push(s);
    vis[sx][sy] = true;
    while(!tmp.empty())
    {
        int x = tmp.front().x, y = tmp.front().y, cnt = tmp.front().cnt;
        tmp.pop();
        for(re int i = 8; i < 16; ++i)//x:lie
        {
            int nx = x + dx[i], ny = y + dy[i];
            if(!vis[nx][ny] && nx >= 1 && nx <= c && ny >= 1 && ny <= r)
            {
                vis[nx][ny] = true;
                k[nx][ny] = cnt + 1;
                tmp.push((node){nx, ny, cnt + 1});
            }
        }
    }
}

void find_min(node s)//找出接国王的最小步数
{
    memset(vis, false, sizeof(vis));//初始化vis
    int sx = s.x, sy = s.y;
    while(!tmp.empty()) tmp.pop();
    tmp.push(s);
    e[sx][sy] = k[sx][sy];//e现在用作储存接国王的最小步数
    vis[sx][sy] = true;
    while(!tmp.empty())
    {
        int x = tmp.front().x, y = tmp.front().y, cnt = tmp.front().cnt;
        tmp.pop();
        for(re int i = 0; i < 8; ++i)//x:lie
        {
            int nx = x + dx[i], ny = y + dy[i];
            if(!vis[nx][ny] && nx >= 1 && nx <= c && ny >= 1 && ny <= r)
            {
                vis[nx][ny] = true;
                e[nx][ny] = k[nx][ny] + cnt + 1;
                tmp.push((node){nx, ny, cnt + 1});
            }
        }
    }
}

void find_all(node s)//在最终的地图中求出最小值 此时以接国王的最小步数的位置为起点
{
    memset(vis, false, sizeof(vis));
    int sx = s.x, sy = s.y;
    while(!tmp.empty()) tmp.pop();
    tmp.push(s);
    vis[sx][sy] = true;
    while(!tmp.empty())
    {
        int x = tmp.front().x, y = tmp.front().y, cnt = tmp.front().cnt;
        tmp.pop();
        for(re int i = 0; i < 8; ++i)//x:lie
        {
            int nx = x + dx[i], ny = y + dy[i];
            if(!vis[nx][ny] && nx >= 1 && nx <= c && ny >= 1 && ny <= r)
            {
                vis[nx][ny] = true;
                e[nx][ny] += cnt + 1;
                tmp.push((node){nx, ny, cnt + 1});
            }
        }
    }
}

void change_origin(node s)//精髓 总步数减去当前骑士的步数
{
    memset(vis, false, sizeof(vis));
    int sx = s.x, sy = s.y;
    while(!tmp.empty()) tmp.pop();
    tmp.push(s);
    f[sx][sy] = e[sx][sy] = a[sx][sy];//这里的e和f是储存减去之后的步数
    vis[sx][sy] = true;
    while(!tmp.empty())
    {
        int x = tmp.front().x, y = tmp.front().y, cnt = tmp.front().cnt;
        tmp.pop();
        for(re int i = 0; i < 8; ++i)//x:lie
        {
            int nx = x + dx[i], ny = y + dy[i];
            if(!vis[nx][ny] && nx >= 1 && nx <= c && ny >= 1 && ny <= r)
            {
                vis[nx][ny] = true;
                f[nx][ny] = e[nx][ny] = a[nx][ny] - cnt - 1;
                tmp.push((node){nx, ny, cnt + 1});
            }
        }
    }
}

int main()
{
    //freopen("1930.txt", "r", stdin);
    cin >> r >> c;//r:hang c:lie
    for(re int i = 1; i <= c; ++i)
    	for(re int j = 1; j <= r; ++j)
    		a[i][j] = -1;
    char t;
    cin >> t >> ky;
    kx = t - 'A' + 1;
    while(cin >> t)//input
    {
        int x = t - 'A' + 1, y;
        cin >> y;
        q.push_back((node){x, y, 0});
    }
    
    if(q.empty())//special situation
    {
        printf("0");
        return 0;
    }
    
    kbfs((node){kx, ky, 0});//king's step
    
    for(re int mm = 0; mm < q.size(); ++mm)//storage all steps without king
    {
        memset(vis, false, sizeof(vis));
        bfs(q[mm]);
    }
    
    int minn, pos, tnum;
    
    for(re int mm = 0; mm < q.size(); ++mm)//every knight
    {
    	minn = 2147483647, pos = 0;//初始化
    	memset(minx, 0, sizeof(minx));
    	memset(miny, 0, sizeof(miny));
    	memset(e, -1, sizeof(e));
    	
        find_min(q[mm]);//find the min element of e, no need to judge "-1"
        for(re int i = 1; i <= c; ++i)
        	for(re int j = 1; j <= r; ++j)
        		if(e[i][j] >= 0) minn = min(minn, e[i][j]);//find min 只找骑士能够到达的地方
    	
    	for(re int i = 1; i <= c; ++i)
        	for(re int j = 1; j <= r; ++j)
        		if(e[i][j] == minn)
        			minx[++pos] = i, miny[pos] = j;//find min's position
        
        change_origin(q[mm]);//a[][] without 1 knight
        
        for(re int i = 1; i <= pos; ++i)//这里是对接国王的最小步数的不同的位置进行bfs
        {
        	tnum = 2147483647;//初始化
        	for(re int j = 1; j <= c; ++j)
        		for(re int l = 1; l <= r; ++l)
        			if(e[j][l] >= 0) e[j][l] = f[j][l];//f储存减去骑士步数以后的数组 因为e数组对于不同的位置被改变了 所以需要f数组恢复 只恢复能够到达的位置。
        	find_all((node){minx[i], miny[i], 0});//找出全局最小值
        	for(re int j = 1; j <= c; ++j)
            	for(re int l = 1; l <= r; ++l)
            		if(e[j][l] >= 0) tnum = min(tnum, e[j][l]);//find min 这里是最终结果
            tnum += minn;//别忘加上接国王的最小步数
            ans = min(ans, tnum);//更新ans
        }
    }
    
    cout << ans << endl;
    return 0;
}
```

---

## 作者：key_rA9 (赞：0)

此题，先bfs求出骑士从一点到另一点的最短步数，再枚举集合点，求出所有骑士到集合点的步数，接着找接国王的骑士，将每一次的结果比较。  
方法好想，看怎么实现。  
这个计算答案的公式：
```pascal
总步数=所有骑士到集合点步数+接国王所需步数-接国王的骑士原本步数
```
代码应该~~很详细~~说明了：
```cpp
#include<map>
#include<cmath>
#include<queue>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define N 0x7fffffff
using namespace std;
const int dx[10]={-2,-2,-1,-1, 1, 1, 2, 2};//行，骑士的行动(方向)
const int dy[10]={-1, 1,-2, 2,-2, 2,-1, 1};//列操作↑ 
struct node
{
    int x,y;//表示位置 
}gw,qs[1111],list[5555];//gw→国王;qs→骑士;list是宽搜用的队列 
int R,C,n,ans=N;//n是骑士个数，ans记录答案 
int f[50][30][50][30];//f[i][j][x][y]表示从(i,j)到(x,y)骑士的步数 
//int calc(int xx,int yy){return (xx-1)*C+yy;}
int d_gw(int _x,int _y){return max(abs(gw.x-_x),abs(gw.y-_y));}
//国王到(_x,_y)的步数 
void bfs(int _x,int _y)//起始点 
{
    int head=1,tail=2;bool v[50][30];//判重 
    memset(v,0,sizeof(v));v[_x][_y]=1;//这个点已经在list里 
    f[_x][_y][_x][_y]=0;//自己的距离0 
    list[1].x=_x,list[1].y=_y;//list第一项是起始点 
    while(head<tail)//宽搜 
    {
        int x=list[head].x,y=list[head].y;//取出队列里的点坐标 
        for(int t=0;t<8;t++)//枚举骑士八种方向 
        {
            int X=x+dx[t],Y=y+dy[t];//求出走后位置 
            if(X>0&&Y>0&&X<=R&&Y<=C)//不能超界 
            {
                if(f[_x][_y][X][Y]>f[_x][_y][x][y]+1)
                {//如果前一步的步数+1比当前起始点到这点的步数少 
                    f[_x][_y][X][Y]=f[_x][_y][x][y]+1;//就更新 
                    if(!v[X][Y])//如果不在队列里 
                    {
                        v[X][Y]=1;//加进队列 
                        list[tail].x=X,list[tail++].y=Y;
                    }//尾到下一项 
                }
            }
        }
        head++;//头指到list下一项 
    }
}
int main()
{
    char c[3];memset(f,63,sizeof(f));//一开始无穷大方便求最小 
    #define M f[0][0][0][0]//记录f原始值 
    scanf("%d%d",&R,&C);//行列没有反 
    scanf("%s%d",c,&gw.x);//数字是横坐标 
    gw.y=c[0]-'A'+1;//字母转成纵坐标 
    while(scanf("%s",c)!=EOF)//没有给出固定骑士个数 
    {
        qs[++n].y=c[0]-'A'+1;//骑士总数先+1再存 
        scanf("%d",&qs[n].x);
    }
    for(int i=1;i<=R;i++)
        for(int j=1;j<=C;j++)
            bfs(i,j);//宽搜预处理f数组 
    int x1=max(1,gw.x-2),x2=min(R,gw.x+2);//求出国王±2的范围 
    int y1=max(1,gw.y-2),y2=min(C,gw.y+2);//并控制不超边界 
    for(int i=1;i<=R;i++)
    {
        for(int j=1;j<=C;j++)//枚举集合点 
        {
            int s1=0,s2;bool flag=1;//s1是所有qs到集合点的步数，s2是接gw所用的步数 
            for(int k=1;k<=n;k++)//qs
            {
                if(f[qs[k].x][qs[k].y][i][j]>=M){flag=0;break;}//有骑士到不了集合点 
                s1+=f[qs[k].x][qs[k].y][i][j];//加上步数 
            }
            if(!flag)continue;//这点就不能集合 
            ans=min(ans,s1+d_gw(i,j));//先比较国王自己走的方案 
            for(int o=1;o<=n;o++)//枚举接国王的qs 
            {
                s2=N;
                for(int p=x1;p<=x2;p++)//接的点再国王周围±2才会是最优方案 
                    for(int q=y1;q<=y2;q++)//刚刚范围已经求了直接用 
                    {
                        if(f[qs[o].x][qs[o].y][p][q]>=M)continue;//同上，无法到达 
                        s2=min(s2,d_gw(p,q)+f[qs[o].x][qs[o].y][p][q]+f[p][q][i][j]);
                    }//接的步数=gw到接的点步数+qs到接的点+qs从接的点到集合点的步数;
                ans=min(ans,s1+s2-f[qs[o].x][qs[o].y][i][j]);//计算方法 
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
```
~~Eh。。。我因为看了某些说集合点再国王周围5```*```5的而被坑了许久~~

---

## 作者：tangyayan (赞：0)

第一篇题解祭。

终于A了。。（我真是一个小蒟蒻）
研究了我几个中午，原来就是把：
```cpp
max(abs(stx-edx),abs(sty-edy))
```
打成了：
```cpp
max(abs(stx-edx),abs(edx-edy))
```
然后又多此一举把x倒过来存。。。。。
~~我可能真的有点脑残~~

所以以后提醒各位，如果有时怎么做都对不了，那么你就找找是不是变量打错了啊之类的，真坑啊，花了我几个中午。。。。

其实这道题不是很难，只是你只是需要打很长的代码就是了。核心思路就是：定义一个f[i][j][k][t]，表示从（i，j）到（k，t）需要走的最短路线（骑士）。这个真的很重要，你只要把这个四维数组想到了，那么整道题也就差不多了。

接下来就是如何求出f数组了，这里就用一个bfs就可以搞定了。然后就是因为国王每次都是走附近的，所以这里有一个公式：
```cpp
max(abs(stx-edx),abs(sty-edy))
```
接着又是一个公式（也不是公式吧）：总路程=每个骑士到目标点的步数-接国王的骑士到目标点的步数+接国王的地点到目标点的步数+接国王的骑士到接国王的地点的步数+接国王的地点到国王的位置

最后就是通过证明可以发现：接国王的地点都是在国王的上下左右或者左上左下右上右下。这个也是至关重要，我刚开始不知道结果就用dfs。。。。。

就这样，注意一下细节，整道题就做完了！
```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#define tyy(stx,sty,edx,edy) max(abs((stx)-(edx)),abs((sty)-(edy)))
using namespace std;
int n,m,len=0;
bool b[50][50];
//h表示horseman，k表示king
int dhx[8]={2,2,1,1,-1,-1,-2,-2};
int dhy[8]={-1,1,-2,2,-2,2,-1,1};
int dkx[9]={0,-1,-1,-1,0,0,1,1,1};
int dky[9]={0,-1,0,1,-1,1,-1,0,1};
int f[50][41][30][41];
struct node
{
    int x,y;
}list[210000];
struct shop
{
    int x,y;
}aa[210000];
inline int bfs(int stx,int sty)
{
    int head,tail;
    memset(b,true,sizeof(b));b[stx][sty]=false;
    f[stx][sty][stx][sty]=0;
    head=1;tail=2;list[1].x=stx;list[1].y=sty;
    while(head<tail)
    {
        int x=list[head].x,y=list[head].y;
        for(int t=0;t<=7;++t)
        {
            int xx=x+dhx[t];
            int yy=y+dhy[t];
            if(xx>=1&&xx<=n&&yy>=1&&yy<=m)
            {
                if(f[stx][sty][xx][yy]>f[stx][sty][x][y]+1)
                {
                    if(b[xx][yy]==true)
                    {
						f[stx][sty][xx][yy]=f[stx][sty][x][y]+1;
						
                   		node tno;
                    	tno.x=xx;tno.y=yy;
                        b[xx][yy]=false;
                        list[tail]=tno;tail++;
                    }
                }
            }
        }
        head++;
    }
}
int main()
{
	//freopen("testdata (2).in","r",stdin);
    char t;
    memset(f,127,sizeof(f));
    int x,pd=0;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)bfs(i,j);//最开始就把f数组全部算出来
    /*for(int i=1;i<=5;i++)
    {
        cin>>t>>x;
        x=m-x+1;
        len++;aa[len].x=t-64;aa[len].y=x;
    }*/
    getchar();//这就是一种神奇的文本输入
    while(cin>>t)
    {
    	cin>>x;
        len++;aa[len].x=t-64;aa[len].y=x;
    }
    int sum=999999999,kx,ky;
    kx=aa[1].x;ky=aa[1].y;
    for(register int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            int ans=0,pd=0;
            for(int k=2;k<=len;k++)
            {
                if(f[aa[k].x][aa[k].y][i][j]>=2139062143){pd=1;break;}
                ans+=f[aa[k].x][aa[k].y][i][j];
            }
            if(pd==1){continue;}
            if(pd==0)
            {
                for(int k=2;k<=len;k++)
                {
                	int st=2139062143;
                    int ax,ay;
                    for(int tt=0;tt<=8;tt++)
                    {
                    	ax=kx+dkx[tt];ay=ky+dky[tt];
                    	if(f[aa[k].x][aa[k].y][ax][ay]>=2139062143)continue;//如果都到不了国王附近，那么就不用往下算了
                    	if(ax<=n&&ax>=1&&ay<=m&&ay>=1)
                        {
                        	int s=0;
                        	s+=f[ax][ay][i][j];
                        	s+=f[aa[k].x][aa[k].y][ax][ay];
							s+=tyy(ax,ay,kx,ky);
							st=min(st,s);
                        }
                    }
                    sum=min(ans-f[aa[k].x][aa[k].y][i][j]+st,sum);
                }
            }
        }
    }
    if(sum==999999999)printf("0");
    else printf("%d",sum);
    return 0;
}
```

麻烦管理员通过，我第一次的题解啊~~

---

## 作者：Celebrate (赞：0)

这一道题其实不难的，只是代码比较长而已：

（1）把棋盘上的点全部搜索一次，找出其实从这一个点到其他的点的最小步数，用思维数组记录；

（2）枚举所有的点，把这个店当作终点需要走的最小步数；

（3）在（2）里面先求不让骑士接国王的值，然后枚举所有的骑士，假设让这一个骑士去接国王的最小值。

注：因为骑士以一步可以走以自己为中心5X5的范围，让骑士

去接国王总是比让国王去找骑士用步数更少，所以只用搜索以

国王为中心5X5的范围就好了，表示骑士走到这个点去接国王的最小值

代码如下：

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int dx[8]={2,2,1,1,-1,-1,-2,-2};//骑士一步可以走的点，国王没有必要管 
const int dy[8]={-1,1,-2,2,-2,2,-1,1};
int n,m;
struct node
{
    int x,y;
};int len;//记录骑士和国王的坐标 
node a[2100];
node king;
int f[51][31][51][31];//骑士从点1到点2所需的最小值 
int minn=2147483647;
inline int find(int x1,int y1,int x2,int y2)//返回国王从点1到点2的最短距离 
{
    return max(abs(x1-x2),abs(y1-y2));//国王是可以斜着走的 
}
inline void bfs(int stx,int sty)//骑士以这个店为起点走到每一个点的最小值，遇到这种情况我建议都用最短路来做，深搜不好 
{
    int i,x,y,xx,yy,head,tail,listx[5100],listy[5100];//队列的x坐标和y坐标 
    bool v[51][31];
    memset(v,true,sizeof(v));v[stx][sty]=false;//记录这一个点是否在队列里面 
    head=tail=1;f[stx][sty][stx][sty]=0;//初始化自己到自己不用走 
    listx[1]=stx;listy[1]=sty;//队列1 
    while(head<=tail)
    {
        x=listx[head];y=listy[head];//记录一下，防止后面出现错误 
        for(i=0;i<=7;i++)
        {
            xx=x+dx[i];//往下走 
            yy=y+dy[i];
            if(xx>=1 && xx<=n && yy>=1 && yy<=m)//如果没有超出边界 
            {
                if(f[stx][sty][xx][yy]>f[stx][sty][x][y]+1)//如果这是更优解 
                {
                    f[stx][sty][xx][yy]=f[stx][sty][x][y]+1;
                    if(v[xx][yy]==true)//如果还没有在队列里面 
                    {
                        v[xx][yy]=false;tail++;//往下找 
                        listx[tail]=xx;listy[tail]=yy;
                    }
                }
            }
        }
        v[x][y]=true;//可以说是回溯把 
        head++;//记得把头+1 
    }
}
int main()
{
    //freopen("1.in","r",stdin);
    int i,j,k,t,ans,s,l,r;char st[11];
    scanf("%d%d",&n,&m);
    scanf("%s%d",st+1,&t);
    king.x=t;king.y=st[1]-'A'+1;//记录国王的坐标
	//这里有一个细节，就是x和y要反过来记录，因为c++里面是先行在列的，和数学有一些不同，这样是为了使for更加方便 
    while(scanf("%s%d",st+1,&t)!=EOF)//记得要这样输入 
    {
        len++;a[len].x=t;a[len].y=st[1]-'A'+1;//记录 
    }
    memset(f,127,sizeof(f));//把f初始化无限大 
    for(i=1;i<=n;i++) for(j=1;j<=m;j++) bfs(i,j);//搜索一次（1） 
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
        	//先找一遍骑士不接国王的方案 
            s=0;bool bk=true;
            for(k=1;k<=len;k++) 
            {
                s=s+f[a[k].x][a[k].y][i][j];
                if(f[a[k].x][a[k].y][i][j]>=f[0][0][0][0]){bk=false;break;}//如果有骑士无法到达终点，这种方案就不行 
            }
            if(bk==false) continue;
            minn=min(minn,s+find(king.x,king.y,i,j));//求最小值 
            for(k=1;k<=len;k++)//让这一个骑士去接国王 
            {
                ans=2147483647;
                for(l=king.x-2;l<=king.x+2;l++)//以国王为中心5*5的格子 
                {
                    if(l>=1 && l<=n)//判断边界 
                    {
                        for(r=king.y-2;r<=king.y+2;r++)
                        {
                            if(r>=1 && r<=m)
                            {
                                if(f[a[k].x][a[k].y][l][r]>=f[0][0][0][0]) continue;//如果走不到这一个点，就不要管了 
                                ans=min(ans,f[a[k].x][a[k].y][l][r]+f[l][r][i][j]+find(king.x,king.y,l,r));//表示骑士和国王走到这一个点 ，然后骑士再带国王走到终点（算一个人的步数） 
                            }
                        }
                    }
                }
                minn=min(minn,s-f[a[k].x][a[k].y][i][j]+ans);//记得减去骑士直接到终点的步数 
            }
        }
    }
    printf("%d\n",minn);//输出 
    return 0;
}
```

---

## 作者：Dispwnl (赞：0)

我因为看反了行和宽调了3个小时。。。

期间一直和题解对代码：怎么不对呢？。。。

带国王跑路时因为骑士跑得快，所以让骑士多跑（\_**你坐出租车时是你去追出租车再坐上吗**\_）

所以骑士跑到国王身旁，国王再向骑士移动，再一起跑路

然后就是bfs最短路

枚举每一个点

然后枚举国王身边的点

然后枚举一个骑士带国王跑

然后。。。

不枚举了，求最短距离

反正就是\_**###枚枚枚枚枚举举举举举**\_

看不懂的话看楼下吧

c++
```cpp
# include<iostream>
# include<cstdio>
# include<cstring>
# include<algorithm>
# include<cstdlib>
# define fo(i,a,b) for(int i=a;i<=b;i++)//装逼专用宏定义
using namespace std;
struct p{
    int x,y;
    int get[41][31];//每个骑士到其他点的最短路
}knight[1201];
struct q{
    int x,y;
}king;//国王位置
int n,m,col,where,num,tot=99999999;
char row;
int mv1[8]={1,-1,-1,1,2,-2,2,-2};
int mv2[8]={2,2,-2,-2,1,1,-1,-1};
int f[1000001][2];
int to[31][31][41][31];
bool use[41][31];
int max(int x,int y)
{
    return x>y?x:y;
}
int min(int x,int y)
{
    return x<y?x:y;
}
int abs(int x)
{
    return x<0?-x:x;
}
void bfs1(int x,int y)
{
    memset(f,0,sizeof(f));
    memset(use,0,sizeof(use));
    f[1][0]=x,f[1][1]=y;
    use[x][y]=1;
    int head=0,tail=1;
    while(head<tail)
    {
        head++;
        fo(i,0,7)
          {
              int xx=f[head][0]+mv1[i],yy=f[head][1]+mv2[i];
              if(!use[xx][yy]&&xx>=1&&xx<=n&&yy>=1&&yy<=m)
              {
                  use[xx][yy]=1;
                  f[++tail][0]=xx;
                  f[tail][1]=yy;
                  to[x][y][xx][yy]=to[x][y][f[head][0]][f[head][1]]+1;
            }
          }
    }
}
void find()
{
    fo(i,-2,2)
      fo(j,-2,2)
        {
            int u=king.x+i,v=king.y+j;
            if(u>=1&&u<=n&&v>=1&&v<=m)
            bfs1(u,v);
        }
    fo(i,1,n)
      fo(j,1,m)
        {
            int ride=0;
            fo(k,1,num)
              if(knight[k].get[i][j]==0x7f)
              {
                  ride=-1;
                  break;
              }
              else ride+=knight[k].get[i][j];
            if(ride!=-1)
            {
                fo(k,-2,2)
                  fo(l,-2,2)
                    {
                        int u=king.x+k,v=king.y+l;
                        if(u>=1&&u<=n&&v>=1&&v<=m)
                        {
                            if(abs(king.x-u)==abs(king.y-v))
                            where=abs(king.x-u);
                            else
                            where=abs(king.x-u)+abs(king.y-v);
                            fo(g,1,num)
                              tot=min(tot,ride-knight[g].get[i][j]+knight[g].get[u][v]+to[u][v][i][j]+where);
                        }
                    }
            }
        }
    printf("%d",tot);
}
void bfs(int x)
{
    memset(f,0,sizeof(f));
    memset(use,0,sizeof(use));
    f[1][0]=knight[x].x,f[1][1]=knight[x].y;
    knight[x].get[f[1][0]][f[1][1]]=0;
    use[f[1][0]][f[1][1]]=1;
    int head=0,tail=1;
    while(head<tail)
    {
        head++;
        fo(i,0,7)
          {
              int xx=f[head][0]+mv1[i],yy=f[head][1]+mv2[i];
              if(!use[xx][yy]&&xx>=1&&xx<=n&&yy>=1&&yy<=m)
              {
                  use[xx][yy]=1;
                  f[++tail][0]=xx;
                  f[tail][1]=yy;
                  knight[x].get[xx][yy]=knight[x].get[f[head][0]][f[head][1]]+1;
            }
          }
    }
}
void init()
{
    scanf("%d%d",&m,&n);//别搞反了。。。
    cin>>row>>col;
    king.x=row-64,king.y=col;
    memset(knight,0x7f,sizeof(knight));
    while(cin>>row>>col)
    {
        int x=row-64;
        knight[++num].x=x;
        knight[num].y=col;
    }
    fo(i,1,num)
      bfs(i);
    if(!num)
    {
        printf("0");//特判
        exit(0);
    }
    find();
}
int main()
{
    init();
    return 0;
}
```

---

## 作者：Jason_Yvan (赞：0)

首先可以O(n\*m)来暴力枚举每一个汇合点，bfs预处理一下骑士到这个汇合点的距离。

然后在可以用个bfs把所有骑士的路径标记一下，接着用国王来走bfs，走到的第一个骑士到过的位置就是那个骑士和国王汇合的点，然后他们两个就可以一起走了。

代码内有详细解释。

代码如下C++：

/*************************************************************************

    > Author: wzw-cnyali
    > Created Time: 2017/4/3 21:07:04
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
#define EREP(i, a) for(register int i = (be[a]); i != -1; i = nxt[i])
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
const int Size = 2000;
const int inf = 0x3f3f3f3f;
const int d1[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const int d2[8][2] = {{1, 2}, {2, 1}, {-1, 2}, {2, -1}, {1,    -2}, {-2, 1}, {-2, -1}, {-1, -2}};
struct node
{
    int x, y;
}king, knight[Size];
int cnt;
int n, m;
bool vis[100][100];
int dis[100][100];
bool judge(int x, int y)
{
    if(x < 1 || y < 1 || x > n || y > m) return 0;
    return 1;
}
void bfs(int x, int y)//预处理出每一个骑士到汇合点（x,y）的距离
{
    queue <node> Q;
    Q.push((node){x, y});
    mem(vis, 0);
    mem(dis, inf);
    dis[x][y] = 0;
    vis[x][y] = 1;
    while(!Q.empty())
    {
        node ls = Q.front();
        Q.pop();
        REP(i, 0, 7)
        {
            int tx = ls.x + d2[i][0];
            int ty = ls.y + d2[i][1];
            if(judge(tx, ty) && !vis[tx][ty])
            {
                chkmin(dis[tx][ty], dis[ls.x][ls.y] + 1);
                Q.push((node){tx, ty});
                vis[tx][ty] = 1;
            }
        }
    }
}
bool road[100][100];//骑士走的路
int work()
{
    //将骑士的路径标记出来
    queue <node> Q;
    mem(road, 0);
    REP(k, 1, cnt)
    {
        while(!Q.empty()) Q.pop();
        Q.push((node){knight[k].x, knight[k].y});
        road[knight[k].x][knight[k].y] = 1;
        while(!Q.empty())
        {
            node ls = Q.front();
            Q.pop();
            REP(i, 0, 7)
            {
                int tx = ls.x + d2[i][0];
                int ty = ls.y + d2[i][1];
                if(judge(tx, ty) && !road[tx][ty] && dis[tx][ty] == dis[ls.x][ls.y] - 1)
                {
                    road[tx][ty] = 1;
                    Q.push((node){tx, ty});
                    if(road[king.x][king.y]) return 0;
                }
            }
        }
    }
    //国王开始走
    while(!Q.empty()) Q.pop();
    Q.push((node){king.x, king.y});
    mem(vis, 0);
    mem(dis, inf);
    vis[king.x][king.y] = 1;
    dis[king.x][king.y] = 0;
    while(!Q.empty())
    {
        node ls = Q.front();
        Q.pop();
        REP(i, 0, 7)
        {
            int tx = ls.x + d1[i][0];
            int ty = ls.y + d1[i][1];
            if(judge(tx, ty) && !vis[tx][ty])
            {
                dis[tx][ty] = dis[ls.x][ls.y] + 1;
                vis[tx][ty] = 1;
                if(road[tx][ty]) return dis[tx][ty];//走到骑士走的路就和骑士一起走
                Q.push((node){tx, ty});
            }
        }
    }
    return 0;
}
char ch[5];
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    n = read(), m = read();
    int ls;
    scanf("%s%d", ch, &ls);
    king.x = ls;
    king.y = ch[0] - 'A' + 1;
    while(scanf("%s%d", ch, &ls) != EOF)
    {
        knight[++cnt].x = ls;
        knight[cnt].y = ch[0] - 'A' + 1;
    }
    int ans = inf;
    REP(i, 1, n)
    {
        REP(j, 1, m)
        {
            bfs(i, j);
            int sum = 0;
            REP(k, 1, cnt) sum += dis[knight[k].x][knight[k].y];
            sum += work();
            ans = min(ans, sum);
            if(ans == 0) { printf("0\n"); return 0; }
        }
    }
    printf("%d\n", ans);
    return 0;
}

```

---

## 作者：远航之曲 (赞：0)

本题就是一个求所有点对间的最短路然后处理的问题。最短路好求，难点在于有王，王可以自己一格一格地走到汇集点；也可以让某个骑士先跳到他所在的格子，再一起到汇集点；也可以先走几步，再让骑士跳到他所在的格子，再一起到汇集点。

d[i,j,x,y]表示点(i,j)到(x,y)的最短路长，可以用BFS求出。王的坐标为(kx,ky)，最终结果用ans储存。 基本思路是枚举一每个格子作为所有骑士的汇集点(i,j)，再枚举每个格子，以这个格子为王和某个骑士的相遇处(x,y)，再枚举每个骑士坐标(m,n)。 求出d[i,j,x,y]+d[x,y,m,n]+max(abs(kx-x),abs(ky-y))-d[i,j,m,n]的最小值，将汇集点到所有骑士的最短路和s加上这个值，与ans比较取小者。

枚举的时间复杂度为O(n^3)，超时不是一般地严重……于是开始优化。最优化剪枝是必要的，当某个汇集点到所有骑士的最短路s已经大与了ans时直接退出。尽管效率大大提高，但仍然严重超时。于是想一想，王和骑士的相遇点可能出现在哪些位置上？显然王走的比骑士要慢，那么应该尽量要让王少走，所以王需要先走的情况只可能是骑士无法到达的地方或者骑士到达需要绕一圈的情况。可以构想一下骑士在王附近时达到王的路径，就不难发现，相遇点只应该在王的附近很短的距离以内。估算一下，相遇点就在王的坐标加减1的范围内枚举就可以了，经过证明，这样做是正确的：

证明
性质1：假设国王和骑士在超过国王座标点一步范围外集合，集合点称为“原汇合点”，那么，当骑士由原汇合点向国王迈进一步，则总汇合步数减少一步。

性质2：可以保证这样做得到的解不大于在原汇合点汇合得到的解。因为“当骑士由原汇合点向国王迈进一步，则总汇合步数减少一步。”

意味着，骑士原路返回“原汇合点”的话，总汇合步数和原来相同。

具体见注释


        
```cpp
#include <cstdio>
#include <queue>
#include <cstring>
#include <cstdlib>
using namespace std;
typedef pair<int,int> Pair;
int dx[]={0,1,1,1,-1,-1,-1,0,0,0},tx[]={0,1,1,-1,-1,2,2,-2,-2};
int dy[]={0,0,1,-1,0,1,-1,0,1,-1},ty[]={0,2,-2,2,-2,1,-1,1,-1};
int d[40][40][40][40];
int dd[1000],vv[1000],dist[1000];
struct node
{
    int x,y;
}a[1000],b[10];
struct quenode
{
    int x,y,v;
    quenode(int a=0,int b=0,int c=0):
        x(a),y(b),v(c) {}
};
int n,m,tot;
char c;
//读入 骑士坐标存在a中，国王与其临近点存在b中 
void init()
{
    scanf("%d%d*c",&n,&m);
    //scanf("%d%d",&kx,&ky);
    tot=-1;
    while(~scanf("%c",&c))
    {
        if (c<65||c>90)
            continue;
        scanf("%d",&a[++tot].x);
        a[tot].y=c-'A'+1;
    }
    b[0].x=a[0].x,b[0].y=a[0].y;
    for (int i=1;i<=8;i++)
        b[i].x=b[0].x+dx[i],b[i].y=b[0].y+dy[i];
}
bool check(int x,int y)
{
    if (x<1 || y<1 || x>n || y>m)
        return 0;
    return 1;
}
//求出x，y到所有点的最短路 bfs 
void sovle(int x,int y)
{
    if (!check(x,y)) return;
    queue<quenode>que;
    quenode now=quenode(x,y,0);
    d[x][y][x][y]=0;
    int xx,yy;
    bool vis[40][40];
    memset(vis,0,sizeof vis);
    vis[x][y]=1;
    que.push(now);
    while(!que.empty())
    {
        now=que.front();
        que.pop();
        for (int i=1;i<=8;i++)
        {
            xx=now.x+tx[i];
            yy=now.y+ty[i];
            if (check(xx,yy) && !vis[xx][yy])
            {
                vis[xx][yy]=1;
                d[x][y][xx][yy]=now.v+1;
                que.push(quenode(xx,yy,now.v+1));
            }
        }
    }
}
void doit()
{
    int sum=0,maxcut=0,step,king,ans=0x3f3f3f3f;
    memset(dd,0x3f,sizeof dd);
    memset(d,-1,sizeof d);
    for (int i=1;i<=tot;i++)
        sovle(a[i].x,a[i].y);
    for (int i=0;i<=8;i++)
        sovle(b[i].x,b[i].y);
    //求最短路 
    for (int i=1;i<=tot;i++)
        for (int j=0;j<=8;j++)
        {
            step=d[a[i].x][a[i].y][b[j].x][b[j].y];
            if (step<0) continue;
            if (step<dd[i])
            {
                dd[i]=step+(j>0);
                vv[i]=j;
            }
        }
    //算出了所有骑士到国王+-1的最短距离,dd是距离,vv是这个点的在b中的下标 
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)//枚举所有的总聚集点
        {
            king=abs(i-b[0].x)+abs(j-b[0].y);//king存储国王到这个点的步数
            int k;
            for (k=1;k<=tot;k++)
            {
                dist[k]=d[a[k].x][a[k].y][i][j];//dist存储所有骑士到与总会聚点的距离
                if (dist[k]<0) break;
            }
            if (dist[k]<0) continue;//走不到 
            maxcut=0;//maxcut存储骑士接上国王能减少的最大距离
            for (int k=1;k<=tot;k++)
            {
                step=d[b[vv[k]].x][b[vv[k]].y][i][j];
                if(maxcut<dist[k]+king-(step+dd[k])) maxcut=dist[k]+king-(step+dd[k]);
            }
            sum=king;
            for  (k=1;k<=tot;k++)
                  sum+=dist[k];
            sum-=maxcut;
            if (ans>sum) ans=sum;
        } 
    printf("%d",ans);
}
int main()
{
    init();
    doit();
}
```

---

## 作者：姚文涛 (赞：0)

被这道BFS不带权图的最短路水题卡了三天。。。。。就这样弱成渣了。。。。。。。。


这道题其实思路很简单，先求出每个点到所有点的最短路，然后枚举集合点，枚举接国王的骑士，枚举接国王的点，算出需要的距离。


总距离=Min｛所有骑士到集合点的距离和-接国王的骑士到集合点的距离+国王到骑士接他的点的距离+骑士到接国王点的距离+其实从接国王的点走到集合点的距离｝（当然太朴素就铁定超时了）


然后开始处理各个细节。


首先求最短路，一开始脑子没动当然就想到用Dijkstra求（我有多沙茶。。。），当然O（v\*v^2）铁定要超时啊，所以用heap+Dijkstra做了一下。。。果然还是超时。。。这时候我终于缓过神来，这是无权图啊！求无权图的最短路就从每一个点开始走一遍BFS就出来了啊！。。。


然后是枚举的问题，朴素枚举当然O（n^3）超时，然后观察到这个图最大是30\*26，然后估计一下最远的骑士和国王，估算后发现接国王的点应该在国王周围5格内，（这题数据弱，2格内就可以AC了，或者2格是对的？）。然后就胡乱AC了。。。




```cpp
type
        re=record
                tot,x,y:longint;
        end;
const
        dx:array[1..8] of longint=(2,1,-1,-2,-2,-1,1,2);
        dy:array[1..8] of longint=(1,2,2,1,-1,-2,-2,-1);
var
        d:array[1..780] of re;
        f:array[1..40,1..26,1..40,1..26] of longint;
        a,mm:array[1..40,1..26] of longint;
        b:array[0..780,1..2] of longint;
        bz:array[1..40,1..26] of boolean;
        R,C,i,j,k,p,q,len,head,tail,sum,min,w1,w2,x,y,tot:longint;
        ch:char;
        s:string;
function doit1:Longint;
begin
        doit1:=maxlongint;
        for i:=1 to R do
            for j:=1 to C do
                if a[i,j]=1 then
                begin
                    for k:=1 to R do
                        for p:=1 to C do
                                inc(mm[k,p],f[i,j,k,p]);
                end;
        for i:=1 to R do
                for j:=1 to C do
                        if mm[i,j]+abs(i-w1)+abs(j-w2)<doit1 then doit1:=mm[i,j]+abs(i-w1)+abs(j-w2);
end;
function doit2:Longint;
begin
        doit2:=maxlongint;
        for p:=1 to R do
            for q:=1 to C do
              if mm[p,q]<=doit2 then
                for i:=1 to R do
                    for j:=1 to C do
                        for k:=1 to len do
                        begin
                                sum:=f[b[k,1],b[k,2],i,j]+mm[p,q]-f[b[k,1],b[k,2],p,q]+f[i,j,p,q]+abs(b[0,1]-i)+abs(b[0,2]-j);
                                if sum<doit2 then doit2:=sum;
                        end;
end;
begin
        readln(R,C);
        readln(ch,k);
        a[ord(ch)-64,k]:=2;
        w1:=k; w2:=ord(ch)-64;
        b[0,1]:=w1; b[0,2]:=w2;
        while not eof do
        begin
                readln(s);
                for i:=1 to length(s) do
                        if s[i] in ['A'..'Z'] then
                        begin
                                k:=i+2;
                                j:=0;
                                while (s[k] in ['0'..'9']) and (k<=length(s)) do
                                begin
                                        j:=j*10+ord(s[k])-48;
                                        inc(k);
                                end;
                                a[j,ord(s[i])-64]:=1;
                                inc(len);
                                b[len,1]:=j;
                                b[len,2]:=ord(s[i])-64;
                        end;
        end;                                                             //read data;
        fillchar(f,sizeof(f),5);
        for i:=1 to R do
                for j:=1 to C do
                begin
                        fillchar(bz,sizeof(bz),true);
                        head:=0;
                        tail:=1;
                        d[1].tot:=0;
                        d[1].x:=i;
                        d[1].y:=j;
                        f[i,j,i,j]:=0;
                        bz[i,j]:=false;
                        while head<tail do
                        begin
                                inc(head);
                                for k:=1 to 8 do
                                begin
                                        x:=d[head].x+dx[k]; y:=d[head].y+dy[k];
                                        if (x>0) and (x<=R) and (y>0) and (y<=C) and bz[x,y] then
                                        begin
                                                inc(tail);
                                                d[tail].tot:=d[head].tot+1;
                                                d[tail].x:=x;
                                                d[tail].y:=y;
                                                bz[x,y]:=false;
                                                f[i,j,x,y]:=d[tail].tot;
                                                inc(tot);
                                        end;
                                end;
                                if tot=r*c then break;
                        end;
                end;                                                    //bfs;
        min:=maxlongint;
        x:=doit1;
        y:=doit2;
        if x<min then min:=x;
        if y<min then min:=y;
        if (len=1) and (x<=2) and (y<=2) then writeln(1) else writeln(min);      //work;
end.
```

---

