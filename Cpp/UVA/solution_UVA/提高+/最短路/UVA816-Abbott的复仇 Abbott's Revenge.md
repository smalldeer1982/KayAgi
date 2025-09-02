# Abbott的复仇 Abbott's Revenge

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=10&page=show_problem&problem=757

[PDF](https://uva.onlinejudge.org/external/8/p816.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/815d09b7103ad071de9d9f7869315aa2585ea85b.png)

## 样例 #1

### 输入

```
SAMPLE
3 1 N 3 3
1 1 WL NR *
1 2 WLF NR ER *
1 3 NL ER *
2 1 SL WR NF *
2 2 SL WF ELF *
2 3 SFR EL *
0
NOSOLUTION
3 1 N 3 2
1 1 WL NR *
1 2 NL ER *
2 1 SL WR NFR *
2 2 SR EL *
0
END
Figure 1: An Example Walk-Through
Arrow Maz```

### 输出

```
SAMPLE
(3,1) (2,1) (1,1) (1,2) (2,2) (2,3) (1,3) (1,2) (1,1) (2,1)
(2,2) (1,2) (1,3) (2,3) (3,3)
NOSOLUTION
No Solution Possible```

# 题解

## 作者：AniYPc421 (赞：40)

相信各位认真研究本题后都能做得出来。

本人水平也就刚过初赛那种，~~过段时间的复赛估计够呛~~。前阵子翻刘汝佳大佬的书，发现这一道题目被要求必须掌握所有细节。

本人作为一只鶸，拿到这题基本什么都不会。看了看讲解，反复想了想题意，终于把所有的东西都搞懂了。

不多说废话了，下面开始讲解。



------------

### 题目大意：

有一个迷宫，给出起点和终点的坐标，每个坐标都有一些“规则”。

这些规则确定了你离开了这个坐标时的方向。格式以进入该坐标时的朝向为开头，后面跟着在这个状态下可以出去的路。

本题的朝向非常重要。没有了朝向就是一道广搜题目。

### 注意事项：

本题有一些注意的点。~~不注意它们，可能就跟我一样把这道题写了一天一夜。~~

1. 注意格式。本题可以输入多个迷宫。每个迷宫前有迷宫的**名字**。每个迷宫以 $\mathrm{0}$ 做结尾。输入结束后，以一串 $\mathrm{END}$ 做结尾。

2. 题目中隐含了**开始时只能向朝向的方向前进**这一条件。

3. 即使终点和起点在一起，也**不能**直接输出终点。需要想出办法在离开出发点后重新回到终点。

4. 输出格式要注意每个迷宫的标题顶格，但输出路径的每一行需要在开头空出**两个空格**，每个坐标之间要有**一个空格**的间隔。题目中还规定了每行输出 $\mathrm{10}$ 个坐标后换一行再进行输出。

5. 所给出的最大数组大小为 $9*9$。



------------

### 解题环节：

由于本人能力有限，没有办法独立写出题解。但阅读刘汝佳的书，自己理解后依葫芦画瓢，也写出了 AC。故在此与大家分享我的理解。

先说一个约定，我会把重要语句的用意作为注释放在代码上面的几行。

首先，读题后不难看出，这是一个求有效路径的问题，并且是一个求最短路的问题。在最短路问题中，很容易想到要用一个数组来存放从起点到当前这个点的最短路径。需要注意，本题的朝向可以影响到你的后续路径，因此我们创建一个三元数组来存放从开始到现在坐标的最短长度。

```cpp
const int MAXN = 10
//三个元素分别代表当前的坐标和在这个坐标时的朝向。
int d[MAXN][MAXN][4];
```

接下来我们要考虑如何接收数据。只有我们成功读取了数据，我们才能安安心心地去解题。因此写如下 $\operatorname{input}$ 函数：

```cpp
//接收数据的函数。
//返回值是 bool 类型是因为有多组数据。
//当我们返回 false 时就意味着输入结束。
bool input() {
	return true;
}
```

接下来考虑我们要接收什么数据。我们知道，每个迷宫首先输入的是起点和终点。为了操作得舒适一点，我们可以写一个节点类：

```cpp
//类中定义了节点的坐标 (r, c) 以及它的朝向。
//同时写了副本构造器并且重载了节点间的等于号，方便进行同类型间的赋值。
class Node {
public:
    int r;
    int c;
    int dir;
    Node (int r = 0, int c = 0, int dir = 0) : r(r), c(c), dir(dir) {}
    Node& operator = (const Node &d) {
        this->r = d.r;
        this->c = d.c;
        this->dir = d.dir;
        return *this;
    }
};
//三个节点分别表示：
//当前状态的 situation，起点 startNode 和终点 finalNode。
Node situation, startNode, finalNode;
```

我们要接收各个节点之间是否联通。因为目标坐标是否能到达只与当前坐标的规则有关。因此我们可以建立一个四元数组用来存放行走的可行性：

```cpp
//四个元素分别代表当前坐标和朝向以及此朝向能行走的方向。
bool has_edge[MAXN][MAXN][4][4];
```

除此之外，我们还要啥？对了，每个迷宫有自己的名字。为了节省空间，我们打算接收一个数据之后就对他求解，因此我们只需要一个 string 变量用来存储名字即可。

```cpp
std::string maze;
```
为了将字符统一化存储，我们可以写出对应的转化函数。

其中 $dirs$ 具体指我们进入坐标时的朝向，$turns$ 具体指我们可以相对往哪个方向走。
```cpp
//常用伎俩，和 dx[] = { ... } 差不多。
const char *dirs = "NESW";
const char *turns = "FLR";
//将字符统一化为整数，方便存储。
inline int dir_id(char c) { return strchr(dirs, c) - dirs; }
inline int turns_id(char c) { return strchr(turns, c) - turns; }
```

接下来就可以开始着手处理具体的读入流程了，具体步骤是先读入地图名，如果为 $\mathrm{END}$ 则退出。否则，按照顺序读取数据。下面是 $\operatorname{input}$ 函数，一些难理解的地方已经以注释形式标注在相应代码上方。
```cpp
bool input() {
    memset(has_edge, 0, sizeof(has_edge));
    char tmpdir;
    std::cin >> maze;
    //利用一个 maze 变量，既可以判断是否结束，又可以记录迷宫名。
    //正常情况下，判断到 END 后，便不再进行读写。
    if(maze == "END") return false;
    //输入开始和结束坐标
    std::cin >> startNode.r >> startNode.c >> tmpdir 
             >> finalNode.r >> finalNode.c;
    situation.dir = dir_id(tmpdir);
    //下面是由于防止解题过程中发现开始点和结束点一样。
    //此举可以防止在开始时就退出解题函数的循环。
    situation.r = startNode.r + dr[situation.dir];
    situation.c = startNode.c + dc[situation.dir];
    //读入各个边。
    int tmpr, tmpc;
    std::string tmps;
    while(std::cin >> tmpr, tmpr) {
        std::cin >> tmpc;
        while(std::cin >> tmps, tmps != "*") {
            for(int i = 1; i < tmps.length(); i++) {
            	//通过刚刚写的转换函数存储各个方向的通行性。
                has_edge[tmpr][tmpc][dir_id(tmps[0])][turns_id(tmps[i])] = true;
            }
        }
    }
    return true;
}
```
现在我们就把输入函数写完了。接下来便着手写起核心的解题步骤。

因为我们最终需要输出可行的路径，因此我们需要一个数组用来保存我们所经过的每一个坐标。
```cpp
//建立一个三元数组。
//下标分别对应在处于某个坐标某个方向。
//元素内容为处于此状态下，最短路的上一个节点坐标。
Node p[MAXN][MAXN][4];
```
接下来，我们要考虑关于迷宫之间跳转的问题。因为题目中给的下一个方向为 $\mathrm{FLR}$，因此我们需要用处于这个坐标时的朝向，来判断出下一个坐标的真实方向。题目中所给的 $\mathrm{FLR}$，是相对于 $dir$ 的相对方向，不便于我们思考。
因此，我们要写出将坐标，朝向和 $turn$ 的组合转为实际坐标的函数。

比较难理解，但这一部分还是很重要的。
```cpp
//惯用伎俩。
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

//将相对方向转化为实际坐标。
Node walk(const Node &n, int turn) {
    int dir = n.dir;
    //看上面我们写的转化函数。
    //我们可以依照 FLR，算出转过身之后的朝向。
    //当我们直行，dir 不变。
    //当我们要直行的时候，turn = 0。
    //当我们要左转的时候，turn = 1，dir 需要逆时针旋转一下。
    if(turn == 1) dir = (dir + 3) % 4;
    //当我们要右转的时候，turn = 2，dir 需要顺时针旋转一下。
    if(turn == 2) dir = (dir + 1) % 4;
    //转过来之后，我们就相当于直行了。
    //因此依据我们 dir 的转换函数。
    //我们上面的 dr 和 dc 数组只要按照 NESW，也即向上右下左的移动，
    //即可实现我们的目的。
    return Node(n.r + dr[dir], n.c + dc[dir], dir);
}
```
接下来写解题函数的主要部分。这里采用广搜进行路径搜索。一些难理解的代码注释已经给出。
```cpp
//防止访问越界。
inline bool ifInside(int r, int c) {
    return r > 0 && c > 0 && r < MAXN && c < MAXN;
}

void solve() {
    //不管究竟能不能找到路，相应迷宫的名字必定会被打印出来。
    std::cout << maze << std::endl;
    std::queue<Node> q;
    //可能有多组数据，因此每次解题前将最短路清空。
    memset(d, -1, sizeof(d));
    Node n = situation;
    //初始化，将初始点出去的点距离设为 0。
    //因为在绝大部分情况是入口和出口不在一起。
    //在这种情况下，出去之后就不能再回到入口。
    //如果在入口设置 0，那么很可能会陷入死循环。
    //具体原因可看后面代码。
    d[n.r][n.c][n.dir] = 0;
    q.push(n);
    while(!q.empty()) {
        n = q.front(); q.pop();
        //检测是否到终点。
        if(n.r == finalNode.r && n.c == finalNode.c) {
            printAns(n);
            return;
        }
        for(int i = 0; i < 3; i++) {
            //检测是否可以行走。
            if(has_edge[n.r][n.c][n.dir][i]) {
                Node v = walk(n, i);
                if(ifInside(v.r, v.c) && d[v.r][v.c][v.dir] == -1) {
                    //路径长度加 1。
                    d[v.r][v.c][v.dir] = d[n.r][n.c][n.dir] + 1;
                    //设置前面的节点，以便打印结果。
                    p[v.r][v.c][v.dir] = n;
                    q.push(v);
                }
            }
        }
    }
    //代表没有到过终点，因此输出没有解决方案。
    //需要注意缩进 2 个空格。
    std::cout << "  No Solution Possible" << std::endl;
    return;
}
```
解题解完了，我们还要想办法把它打印出来。具体细节在注释中给出。
```cpp
void printAns(Node &n) {
    //用一个 vector 数组从终点向起点遍历，记录路径。
    std::vector<Node> vecNodes;
    while(true) {
        vecNodes.push_back(n);
        //这就能解释为什么在起点走一步后的距离为 0。
        //发现走到起点后面一个点之后说明找到了，退出。
        if(!d[n.r][n.c][n.dir]) break;
        Node tmp = n;
        n = p[n.r][n.c][n.dir];
        //为啥要把遍历过的 p 清零？因为可能不止有一个迷宫。
        //其实不清零问题也不大。
        //但是为了保险一点，防止出现梦幻错误，清空不会有错的。
        p[tmp.r][tmp.c][tmp.dir] = Node();
    }
    //别忘了，这才找到起点后面一个点。我们把起点也加到数组中。
    vecNodes.push_back(startNode);
    //题目中给出的是每行 10 个坐标。如需求更改，在此修改即可。
    const int eachLineNums = 10;
    //cnt 代表当前输出的是第几个点。
    int cnt = 0;
    for(std::vector<Node>::iterator itVec = vecNodes.end() - 1; 
        itVec >= vecNodes.begin(); itVec--) {
        //如果不在行首，输出一个空格。
        if(cnt % eachLineNums) std::cout << " ";
        //否则就在行首，缩进两个空格。
        else std::cout << "  ";
        std::cout << "(" << (*itVec).r << "," << (*itVec).c << ")";
        //如果是在行尾，换行。
        if(!(++cnt % eachLineNums)) std::cout << std::endl;
    }
    //假如这一行还没打印满 10 个坐标，换个行。
    if(vecNodes.size() % 10) std::cout << std::endl;
    return;
}
```
马上整个程序就大功告成了，做最后一步吧：
```cpp
int main() {
    while(input()) { solve(); }
    return 0;
}
```
提交，即可 AC。


------------


完整代码已经分散在上面的文字当中。

预祝各位共同进步。如有问题，随时欢迎评论。


---

## 作者：hu1029282594 (赞：6)

题意：

给出一个箭头迷宫，在每个路口处，如果你从某个方向进入了该路口，那么路口的地面上在靠近你的方向会画有一组箭头，它们相对于你的方向可以是向左，向前，向右，或者是它们的任意组合。
当你从某一方向进入某个入口时，下一步只能在这个入口对应方向上标记的箭头中选一个方向继续行进。在起点时，可以选择任何方向。
给出起点和终点，求它们之间的最短路径
每条边的长度为1

这一题的关键是建图，建图之后**bfs**一遍就好了。


转成图模型：
状态->图中的点
状态转移->图中的边

状态表示：<当前位置的坐标，当前朝向>
按当前位置的箭头方向连边
边权：1
求任一起点到任一终点的最短路径
BFS

代码自己实现，别想偷懒！

---

## 作者：Yue_qiu (赞：4)

这题翻译有点问题，坑了我好久，在起点处你不能选择任意朝向，你只能以当前方向直走......

其他的就和最短路问题差不多了，bfs，过~

当然也有需要注意的地方，比如怎么表示状态，一般最短路问题中，到达一个点的状态都是(x,y)，第二次到该点时状态也是(x,y)两种状态能走的下一种状态都一样，所以直接舍弃第二次到达，但这个题中，第一次到达一个点时状态假设为(x,y,dir),第二次再到达时可能是(x,y,dir1),由于dir不同，所以他们能到达的下一种状态不一样，第二次到达时就不能舍弃，除非第二次到达时dir和第一次时一样;

还有一些细节，比如转向后状态的转换，每个朝向转向后的朝向改变都不一样，总共有12种情况，手写很麻烦，所以我们转换一种思路，用数组表示方向，0,1,2,3分别表示NESW,0,1,2分别表示FLR；
那么，F表示直行，方向不变，L表示左转，即dir-1，由于-1时会出现负数，所以我们用+3表示减一（4是一个周期），R表示右转，即+1，防止下标超过3，所以我们每次转向之后的dir=dir%4；

还有行走，每次行走都可以看做先转向，后直行，直行的话dir不变，所以我们直接用两个数组表示直行后坐标的变化，以dir做下标；

还有更多像输入输出那样的小细节，都扔在注释里了

剩下的解析都仍在注释里了，结合代码好理解；

顺便吹一下uDebug,用法也扔注释里了；

```cpp
#include<bits/stdc++.h>
using namespace std;
const char dirs[5]="NESW";          //将方向用数字表示0,1,2,3分别表示N,E,S,W 
const char turns[4]="FLR";          //将转向用数字表示0,1,2表示F,L,R 
const int dx[4]={-1,0,1,0};         //下标表示方向，坐标变化即是以当前方向直行的坐标变化 
const int dy[4]={0,1,0,-1};
inline int sdir(char c) {return strchr(dirs,c)-dirs;} //将dir由char转化为int 
inline int sturn(char t) {return strchr(turns,t)-turns;} //同上 
int bx,by,bdir,ex,ey,nbx,nby;           //bx=begin_x,by=begin_y,bdir=begin_dir,ex=end_x,ey=end_y,nbx=new_begin_x,nby=new_begin_y 在起点只能向前直走，所以需要搞一个新起点 
bool edge[10][10][4][3];                //edge[x][y][dir][turn] 表示能否从(x,y,dir)转向turn，即是否有边 
int step[10][10][4];                    //相同状态只走一次，需要一个bool组来表示是否走过，输出答案时又需要找到起点（步数step为0的点），所以直接用一个step数组来表示第一次到达某个状态时的步数，没到过就是-1 
struct node                             //三元组表状态 
{
	int x;
	int y;
	int dir;
	node(int x=0,int y=0,int dir=0)     //个人喜欢这样写构造函数，也可以简写为node(int x=0,int y=0,int dir=0):x(x),y(y),dir(dir) {} 
	{
		this->x=x;
		this->y=y;
		this->dir=dir;
	}
}father[10][10][4];                    //father数组表示每个状态的前驱状态，方便最好输出答案 
node walk(const node &n,int turn) 
{
	int dir=n.dir;
	if(turn==1) dir=(dir+3)%4;
	else if(turn==2) dir=(dir+1)%4;
	return node(n.x+dx[dir],n.y+dy[dir],dir);
}
inline bool isdir(const char &c) {return c=='W'||c=='N'||c=='E'||c=='S';} //方便输入时判断 
inline bool isturn(const char &c) {return c=='F'||c=='L'||c=='R';}
bool read()       //输入函数 
{
	string s;     //s方便判断数据是否结束 
	cin>>s;
	if(s=="END") return 0;
	memset(step,-1,sizeof(step));
	memset(edge,0,sizeof(edge));
	cout<<s<<endl<<" ";
	char tdir;
	scanf("%d %d %c %d %d",&bx,&by,&tdir,&ex,&ey);
	bdir=sdir(tdir);
	int tx,ty;
	while(scanf("%d %d",&tx,&ty)==2)
	{
		string s1;
		getline(cin,s1);
		for(int i=0;i<s1.size();++i)
		{
			if(isdir(s1[i]))
			{
				register int dir1=sdir(s1[i]);
				while(isturn(s1[++i]))
				{
					register int turn1=sturn(s1[i]);
					edge[tx][ty][dir1][turn1]=1;
				}
			}
		}
	}
	nbx=bx+dx[bdir]; //由起点转换为新起点 
	nby=by+dy[bdir];
	return 1;
}
void print_ans(node &n) //输出答案 
{
	vector<node> v; //这里也可以用stack来代替vector，但vector不容易崩 
	while(step[n.x][n.y][n.dir])
	{
		v.push_back(n);
		n=father[n.x][n.y][n.dir];
	}
	v.push_back(node(nbx,nby,bdir));//step为0时已经退出了循环，所以要手动把新起点加上 
	v.push_back(node(bx,by,bdir));//同理 
	int cnt=1;
	printf(" (%d,%d)",v.back().x,v.back().y);//手动输出第一个点，顺便吐槽一句uva的全字匹配 
	v.pop_back();
	while(!v.empty())
	{
		++cnt;
		if((cnt=cnt%10)==1)
		{
			printf("\n  (%d,%d)",v.back().x,v.back().y);
			v.pop_back();
		}
		else
		{
			printf(" (%d,%d)",v.back().x,v.back().y);
			v.pop_back();
		}
	}
	return;
}
void solve() //bfs求解 
{
	queue<node> q;
	node nbegin(nbx,nby,bdir);
	step[nbx][nby][bdir]=0;
	q.push(nbegin);
	while(!q.empty())
	{
		node tmp=q.front();q.pop();
		if(tmp.x==ex&&tmp.y==ey)
		{
			print_ans(tmp);
			cout<<endl;
			return;
		}
		for(int i=0;i<3;++i)
		{
			if(edge[tmp.x][tmp.y][tmp.dir][i])
			{
				node nn=walk(tmp,i);
				if(step[nn.x][nn.y][nn.dir]>-1) continue;
				q.push(nn);
				step[nn.x][nn.y][nn.dir]=step[tmp.x][tmp.y][tmp.dir]+1;
				father[nn.x][nn.y][nn.dir]=tmp;
			}
		}
	}
	cout<<" No Solution Possible"<<endl;
	return;
}
int main()
{
	//用uDebug的话要把输出存起来 freopen("out.txt","w",stdout) 
	while(read()) solve();
	return 0;
}
```


---

## 作者：尚君子 (赞：2)

本题在性质上和普通迷宫是一样的，但是由于“朝向”也起到了关键作用，所以需要用一个三元组$(r,c,dir)$表示“位于$(r,c)$，面朝$dir$”这个状态。假设入口的位置是$(r0,c0)$，朝向为$dir$，则初始状态并不是$(r0,c0,dir)$，而是$(r1,c1,dir)$。其中，$(r1,c1)$是$(r0,c0)$沿着方向$dir$走一步后的坐标。此处用$d[r][c][dir]$表示初始状态到$(r,c,dir)$的最短路长度，并且保存了状态$(r,c,dir)$在$BFS$树的父节点。

下面是代码
```cpp
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

struct Node {
  int r, c, dir; // 站在(r,c)，面朝方向dir(0~3分别表示N, E, S, W)
  Node(int r=0, int c=0, int dir=0):r(r),c(c),dir(dir) {}
};

const int maxn = 10;
const char* dirs = "NESW"; // 顺时针旋转
const char* turns = "FLR";

int has_edge[maxn][maxn][4][3];
int d[maxn][maxn][4];
Node p[maxn][maxn][4];
int r0, c0, dir, r1, c1, r2, c2;

int dir_id(char c) { return strchr(dirs, c) - dirs; }
int turn_id(char c) { return strchr(turns, c) - turns; }

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

Node walk(const Node& u, int turn) {
  int dir = u.dir;
  if(turn == 1) dir = (dir + 3) % 4; // 逆时针
  if(turn == 2) dir = (dir + 1) % 4; // 顺时针
  return Node(u.r + dr[dir], u.c + dc[dir], dir);
}

bool inside(int r, int c) {
  return r >= 1 && r <= 9 && c >= 1 && c <= 9;
}

bool read_case() {
  char s[99], s2[99];
  if(scanf("%s%d%d%s%d%d", s, &r0, &c0, s2, &r2, &c2) != 6) return false;
  printf("%s\n", s);

  dir = dir_id(s2[0]);
  r1 = r0 + dr[dir];
  c1 = c0 + dc[dir];

  memset(has_edge, 0, sizeof(has_edge));
  for(;;) {
    int r, c;
    scanf("%d", &r);
    if(r == 0) break;
    scanf("%d", &c);
    while(scanf("%s", s) == 1 && s[0] != '*') {
      for(int i = 1; i < strlen(s); i++)
        has_edge[r][c][dir_id(s[0])][turn_id(s[i])] = 1;
    }
  }
  return true;
}

void print_ans(Node u) {
  // 从目标结点逆序追溯到初始结点
  vector<Node> nodes;
  for(;;) {
    nodes.push_back(u);
    if(d[u.r][u.c][u.dir] == 0) break;
    u = p[u.r][u.c][u.dir];
  }
  nodes.push_back(Node(r0, c0, dir));

  // 打印解，每行10个
  int cnt = 0;
  for(int i = nodes.size()-1; i >= 0; i--) {
    if(cnt % 10 == 0) printf(" ");
    printf(" (%d,%d)", nodes[i].r, nodes[i].c);
    if(++cnt % 10 == 0) printf("\n");
  }
  if(nodes.size() % 10 != 0) printf("\n");
}

void solve() {
  queue<Node> q;
  memset(d, -1, sizeof(d));
  Node u(r1, c1, dir);
  d[u.r][u.c][u.dir] = 0;
  q.push(u);
  while(!q.empty()) {
    Node u = q.front(); q.pop();
    if(u.r == r2 && u.c == c2) { print_ans(u); return; }
    for(int i = 0; i < 3; i++) {
      Node v = walk(u, i);
      if(has_edge[u.r][u.c][u.dir][i] && inside(v.r, v.c) && d[v.r][v.c][v.dir] < 0) {
        d[v.r][v.c][v.dir] = d[u.r][u.c][u.dir] + 1;
        p[v.r][v.c][v.dir] = u;
        q.push(v);
      }
    }
  }
  printf("  No Solution Possible\n");
}

int main() {
  while(read_case()) {
    solve();
  }
  return 0;
}
```


---

## 作者：多米 (赞：2)

上面的那个题解怎么那么不诚实呢

太恶心了

于是我也（~~恶心~~）一下

发一个近似正确的代码

(~~此代码并非真实正确代码~~）

```
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int r,c,dir;// 站在 (r,c)，面朝的方向 dis(0~3分别表示 N,E,S,W)
	node(int r=0,int c=0,int dir=0):r(r),c(c),dir(dir){}
};
const int maxn=10;
const char* dirs="NESW";// 顺时针旋转 
const char* turns="FLR";
int has_edge[maxn][maxn][4][3];
int d[maxn][maxn][4];
node p[maxn][maxn][4];
int r0,c0,dir,r1,c1,r2,c2;
const int dr[4]={0,1,0,-1};
const int dc[4]={1,0,-1,0};
int dir_id(char c)
{
	return strchr(dirs,c)-dirs;
}
int turn_id(char c)
{
	return strchr(turns,c)-turns;
}
node walk(const node& u,int turn)
{
	int dir=u.dir;
	if(turn==1)dir=(dir+3)%4;// 逆时针 
	if(turn==2)dir=(dir+1)%4;// 顺时针 
	return node(u.r+dr[dir],u.c+dc[dir],dir);
}
bool inside(int r,int c)
{
	return r>=1&&r<=9&&c>=1&&c<=9;
}
void print_ans(node u)
{
	// 从目标节点逆序追溯到初始节点
	vector<node>nodes;
	while(1)
	{
		nodes.push_back(u);
		if(!d[u.r][u.c][u.dir])break;
		u=p[u.r][u.c][u.dir];
	}
	nodes.push_back(node(r0,c0,dir));
	// 打印解，每行 10个
	int cnt=0;
	for(int i=nodes.size()-1;i>=0;i--)
	{
		if(!cnt%10)printf(" ");
		printf(" (%d,%d)",nodes[i].r,nodes[i].c);
		if(++cnt%10==0)cout<<endl;
	}
	if(nodes.size()%10!=0)cout<<endl; 
}
bool read_case()
{
	char s[99],s2[99];
	if(scanf("%s%d%d%s%d%d",&s,&r0,&c0,&s2,&r2,&c2)!=6)return false;
	printf("%s\n",s);
	dir=dir_id(s2[0]);
	r1=r0+dr[dir];
	c1=c0+dc[dir];
	memset(has_edge,0,sizeof(has_edge));
	int r,c;
	while(1)
	{
		int r,c;
		cin>>r;
		if(!r)break;
		cin>>c;
		while(scanf("%s",&s)&&s[0]!='*')
			for(int i=1;i<strlen(s);i++)
				has_edge[r][c][dir_id(s[0])][turn_id(s[i])]=1;
	}
	return true;
}
void slove()
{
	queue<node>q;
	memset(d,-1,sizeof(d));
	node u(r1,c1,dir);
	d[u.r][u.c][u.dir]=0;
	q.push(u);
	while(!q.empty())
	{
		node u=q.front();
		q.pop();
		if(u.r==r2&&u.c==c2)
		{
			print_ans(u);
			return;
		}
		for(int i=0;i<3;i++)
		{
			node v=walk(u,i);
			if(has_edge[u.r][u.c][u.dir]&&inside(v.r,v.c)&&d[v.r][v.c][v.dir]<0)
			{
				d[v.r][v.c][v.dir]=d[u.r][u.c][u.dir]+1;
				p[v.r][v.c][v.dir]=u;
				q.push(v);
			}
		}
	}
	printf("  No Solution Possible\n");
}
int main()
{
	while(read_case())slove();
	return 0;
}
/*
SAMPLE
3 1 N 3 3
1 1 WL NR *
1 2 WLF NR ER *
1 3 NL ER *
2 1 SL WR NF *
2 2 SL WF ELF *
2 3 SFR EL *
0
NOSOLUTION
3 1 N 3 2
1 1 WL NR *
1 2 NL ER *
2 1 SL WR NFR *
2 2 SR EL *
0
END
Figure 1: An Example Walk-Through
Arrow Maz

SAMPLE
(3,1) (2,1) (1,1) (1,2) (2,2) (2,3) (1,3) (1,2) (1,1) (2,1)
(2,2) (1,2) (1,3) (2,3) (3,3)
NOSOLUTION
No Solution Possible
*/
```
不能给你们真正的好代码，因为如果你们抄袭了，我就白打了QWQ

这代码非常的长，如果需要正确代码，私信  多肉



---

## 作者：云浅知处 (赞：0)

如果没有「方向」这个要求，那直接 $\text{BFS}$ 即可并记录路径即可，就不说了qwq

那么限制「方向」之后怎么办呢？

其实也没什么区别qwq。

我们把每个点复制四个 分别表示「从 北/东/南/西 进入这个点时的状态」，用 $(x,y,f)$ 表示。

其中 $x,y$ 是坐标，$f$ 是 $\text{N/S/W/E}$ 中的一个，表示方向

这样我们就可以很方便地连边了。

比如 `1 3 NL ER`，我们就连上这几条边：

- $(1,3,\text{N})\to (1,2,\text{W})$（因为 $\text{North}$ 左转之后变成了 $\text{West}$，同时向西走一格相当于 $y$ 坐标 $-1$）
- $(1,3,\text{E})\to (2,3,\text{S})$（因为 $\text{East}$ 左转之后变成了 $\text{South}$，同时向南走一格相当于 $x$ 坐标 $+1$）

这样我们就只需要支持以下操作：

-  对每个方向，算出它 左转/右转 后的方向
- 对每个方向，算出朝这个方向走一步后的坐标

这两个操作都是容易实现的。

那么我们按照以上建图，然后对这个图 $\text{BFS}$ 即可。

最后只需要对每个 $f$ 查询起点到 $(\text{end}_x,\text{end}_y,f)$ 的最短路径即可。

不过注意到这题的每个点的 $x,y$ 坐标都在 $1\sim 9$ 范围内

因此，对于每个点 $(x,y,f)$，我们用一个数 $\overline{Fxy}$ 来表示它。

其中，$f=\text{N}$ 时 $F=0$，$f=\text{E}$ 时 $F=1$，依次类推。

例如，$(1,3,\text{E})$ 就是 $113$，$(2,3,\text{S})$ 就是 $223$，我们之前实际上就是连了一条边 $113\to 223$。

这样就可以很方便地对图进行操作啦！

最后这题格式非常离谱，而且翻译里面没说=\_=

实际上这题格式要求：

> 对每个 `Case`，
> - 先**顶格**输出 `Case :x`，$x$ 是 `Case` 编号
> - 然后后面每行**开头空两格**（这个在洛谷的样例里面没有qwq）
> - 接着**每行输出十个**经过的点然后换行
> - 两个点间**用空格隔开** 行末不能有多余空格
> - 无解要**先空两格**然后输出 `No Solution Possible`

对于样例，实际的输出是这样的：

```
SAMPLE
  (3,1) (2,1) (1,1) (1,2) (2,2) (2,3) (1,3) (1,2) (1,1) (2,1)
  (2,2) (1,2) (1,3) (2,3) (3,3)
NOSOLUTION
  No Solution Possible
```

------------

代码实现起来其实不难，我自己除去格式问题 WA 的三发也算是一遍过了（

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<queue>

#define int long long
const int MN=1e3+5;

using namespace std;

vector<int>G[MN];

int fwd(char ch){
    if(ch=='N')return 0;
    else if(ch=='E')return 1;
    else if(ch=='S')return 2;
    else if(ch=='W')return 3;
    else return 114514;
}

int turnch(char ch){
    if(ch=='L')return -1;
    else if(ch=='F')return 0;
    else if(ch=='R')return +1;
    else return 1919810;
}

int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};

int calc(int f,int x,int y){return f*100+x*10+y;}
int calcx(int val){return (val%100)/10;}
int calcy(int val){return val%10;}

bool add(int x,int y,string str){
    if(str=="*")return false;
    int len=str.length();
    int f=fwd(str[0]),u=calc(f,x,y);
    for(int i=1;i<len;i++){
        int newf=(turnch(str[i])+f+4)%4,xx=x+dx[newf],yy=y+dy[newf];
        int v=calc(newf,xx,yy);
        G[u].push_back(v);
    }
    return true;
}//连边

queue<int>q;
int dis[MN],pi[MN];
void bfs(int s){
    dis[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0,sz=G[u].size();i<sz;i++){
            int to=G[u][i];
            if(dis[to]!=-1)continue;
            dis[to]=dis[u]+1;
            pi[to]=u;//记录中途的路径
            q.push(to);
        }
    }
}//BFS

int num;
void print(int u){
    if(u==-1)return ;
    if(pi[u]!=-1)print(pi[u]);
    num++;
    cout<<"("<<calcx(u)<<","<<calcy(u)<<")";
    if(num%10!=0)cout<<" ";
    else cout<<"\n  ";
}

void solve(){
    memset(dis,-1,sizeof(dis));
    memset(pi,-1,sizeof(pi));
    while(!q.empty())q.pop();
    for(int i=0;i<MN;i++)G[i].clear();

    string Name;
    cin>>Name;
    if(Name=="END")exit(0);
    cout<<Name<<'\n';

    int opx,opy,edx,edy;
    char opd;
    cin>>opx>>opy>>opd>>edx>>edy;
    
    string str;
    int x,y;
    while(1){
        cin>>x;
        if(x==0)break;
        cin>>y>>str;
        while(add(x,y,str))cin>>str;
    }

    int f=fwd(opd);
    bfs(calc(f,dx[f]+opx,dy[f]+opy));
    
    int minto=114514,mindis=1919810;
    for(int i=0;i<4;i++){
        int node=calc(i,edx,edy);
        if(dis[node]<mindis&&dis[node]!=-1)mindis=dis[node],minto=node;
    }

    if(minto==114514&&mindis==1919810){puts("  No Solution Possible");return ;}

    num=1;
    cout<<"  ("<<opx<<","<<opy<<") ";
    print(pi[minto]);
    cout<<"("<<calcx(minto)<<","<<calcy(minto)<<")\n";
}
 
signed main(void){

    while(1)solve();
 
    return 0;
}
```

---

## 作者：fjy666 (赞：0)

## 0x01 思路
较为显然的 bfs。  
但是这种迷宫的读入很难处理，考虑建立一个迷宫节点 Node 来储存。  
然后，走到一个格子的**方向**对之后的路径有决定性影响，  
所以在 bfs 时，走到一个格子的方向要分开讨论。  
有 $9\times 9$ 个格子，有 $4$ 种方向，需要 $9^2\times 4$ 的空间，开得下。  
时间复杂度：$\Theta(9^2\times4\times T)$，其中 $T$ 位数据组数。  
这题的细节很多，我一共写了 3.31KB，调了 1h。  
所以，为了防止你们重蹈覆辙，提供一个 debug 网站：  
<http://udebug.com/UVE/816>  
good luck!

## 0x02 代码

```cpp
//梦开始的地方
#include <algorithm>
#include <iostream>
#include <cassert>
#include <utility>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#define debug
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
using namespace std;
const int kN = 55,kD = 15;
char mazeName[kN]; 
struct maze{
	bool isExist;
	vector<char> Turn[4]; 
}maz[kD][kD];
int stX,stY,stD,edX,edY;
//                       N     E     S     W
const int mov[][2] = {{-1,0},{0,1},{1,0},{0,-1}};
int dirChr2Int(char d){
	int D;
    if(d == 'N')D = 0;
    if(d == 'E')D = 1;
    if(d == 'S')D = 2;
    if(d == 'W')D = 3;
    return D;
}
void initMaze(void){
	_rep(i,0,9)
		_rep(j,0,9){
			maz[i][j].isExist = false;
			maz[i][j].Turn[0].clear();
			maz[i][j].Turn[1].clear();
			maz[i][j].Turn[2].clear();
			maz[i][j].Turn[3].clear();
		}
	return;
}
char op[15];
void readMaze(void){
	char tmp__[5];
	scanf("%d%d%s%d%d",&stX,&stY,tmp__,&edX,&edY);
	stD = dirChr2Int(tmp__[0]);
    int x,y;
    while(scanf("%d",&x) == 1){
    	if(x == 0)break;
    	scanf("%d",&y);
    	maz[x][y].isExist = true;
    	while(scanf("%s",op) == 1){
    		if(strcmp(op,"*") == 0)break;
    		int tmp = dirChr2Int(op[0]);
    		char *p = &op[1];
    		while((*p) != '\0'){
    			maz[x][y].Turn[tmp].push_back(*p);
    			++p;
			}
		}
	} 
	return;
}
const int kBufL = 15000;
//81 * 4
struct node{int x,y,from,dir;};
node que[kBufL];
bool done[kD][kD][4];//suc
int head,tail;//suc
void push(node x){que[++tail] = x;}
node pop(void){return que[head++];}
int turn(int ori,char t){
	if(t == 'F')return ori;
	if(t == 'R')return (ori+1)&3;
	if(t == 'L')return (ori+3)&3;
	assert(false);
}
vector<pair<int,int> > ans;
void print(int id){
	ans.clear(); 
	ans.push_back(make_pair(edX,edY));
	node tmp = que[id];
	ans.push_back(make_pair(tmp.x,tmp.y));
	while(tmp.from != -1){
		tmp = que[tmp.from];
		ans.push_back(make_pair(tmp.x,tmp.y));
	}
	reverse(ans.begin(),ans.end());
	int cnt = 0;
	for(int i = 0;i < ans.size();++i){
		if(cnt % 10 == 0)printf("  (%d,%d)",ans.at(i).first,ans.at(i).second);
		else printf(" (%d,%d)",ans.at(i).first,ans.at(i).second);
		++cnt;
		if(cnt % 10 == 0)printf("\n");
	}
	if(cnt % 10 != 0)printf("\n");
} 
bool bfs(void){
	memset(done,false,sizeof(done));
	head = 1;tail = 0;
	node begin;
	begin.x = stX;begin.y = stY;begin.from = -1;begin.dir = stD;
	push(begin);
	while(tail >= head){
		node x = pop();
//		printf("Searching (%d,%d,%d)\n",x.x,x.y,x.dir);
		if(x.x < 1 || x.x > 9 || x.y < 1 || x.y > 9)continue;
		if(done[x.x][x.y][x.dir])continue;
		done[x.x][x.y][x.dir] = true;
		x.x += mov[x.dir][0];
		x.y += mov[x.dir][1];
		if(x.x == edX && x.y == edY){
			print(head - 1);
			return true;
		}
		if(maz[x.x][x.y].isExist == false)continue;
		node nx = x; 
		for(int i = 0; i < maz[x.x][x.y].Turn[x.dir].size(); ++i){
			nx.dir = turn(x.dir,maz[x.x][x.y].Turn[x.dir].at(i));
			nx.from = head - 1;
//			printf("	Extended (%d,%d,%d)\n",nx.x,nx.y,nx.dir);
			push(nx); 
		}
	}
	return false;
}
int main(){
	while(scanf("%s",mazeName) == 1){
		if(strcmp(mazeName,"END") == 0)break;
		printf("%s\n",mazeName);
		initMaze();
		readMaze();
		if(!bfs())
			puts("  No Solution Possible");
	}
    return 0;
}
```

---

