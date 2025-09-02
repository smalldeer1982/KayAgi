# [ABC007C] 幅優先探索

## 题目描述

一个大小为 $n\times m$ 的迷宫，你可以往上下左右任意方向移动 $1$ 步，求最少需要多少步才能走出迷宫。

迷宫中 `.` 表示空地，`#` 表示墙壁，移动中只能穿过空地，不能穿墙。

## 说明/提示

对于 $100\%$ 的数据，$1\le n, m\le50$，$sy, gy\le n$，$sx,gx\le m$。

## 样例 #1

### 输入

```
7 8
2 2
4 5
########
#......#
#.######
#..#...#
#..##..#
##.....#
########```

### 输出

```
11```

## 样例 #2

### 输入

```
5 8
2 2
2 4
########
#.#....#
#.###..#
#......#
########```

### 输出

```
10```

## 样例 #3

### 输入

```
50 50
2 2
49 49
##################################################
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
#................................................#
##################################################```

### 输出

```
94```

# 题解

## 作者：BurningEnderDragon (赞：18)

**（前排提醒：如果你本地全过提交全错，不妨检查一下是否输出了换行）**

~~AtCoder特色~~

[题目链接：AT896 幅優先探索](https://www.luogu.com.cn/problem/AT896)

从题目上可以看出，这是一道非常简单的广度优先搜索（$BFS,\ Breadth\ First\ Search$）模板题。

广度优先搜索的基本思想是什么呢？假设所有可能出现的情况是一棵树，那么广度优先搜索就是从根结点开始，先搜索完根节点**所有的深度等于自身深度+1的子结点**，再搜索每个子结点的子结点，当一个点的所有深度等于自身深度+1的子结点都被搜索完后，才会搜索下一个结点的子结点。

而深度优先搜索（$DFS,\ Depth\ First\ Search$）则是从根结点开始，搜索根节点的第一个子结点，然后搜索这个子结点的第一个子结点……**直到搜索到叶节点后，再“回溯”**，搜索他的父节点的下一个子结点。

换句话说，以下面这棵树为例子，

广度优先搜索的搜索顺序是$A\rightarrow B\rightarrow C\rightarrow D\rightarrow E\rightarrow F\rightarrow G\rightarrow H\rightarrow I$

而深度优先搜索的搜索顺序则是$A\rightarrow B\rightarrow D\rightarrow E\rightarrow I\rightarrow C\rightarrow F\rightarrow G\rightarrow H$

![一棵树](https://cdn.luogu.com.cn/upload/image_hosting/q57bnw3u.png)

那么如何实现广度优先搜索算法呢？我们需要用到**队列**。开始搜索时先将根结点入队**并将根结点标记为已被搜索过**，然后开始循环，只要队列非空且没有到达终点，就将当前搜索到的结点的**符合条件且未被搜索过**的子结点入队。以下是伪代码：

```cpp
起点入队;
将起点标记为已被搜索过;
while(队列非空)
{
	if(到达终点)
	{
		输出结果;
		return 0; 
	}
	if(子结点符合条件且未被搜索过)
	{
		子结点入队; 
        将子结点标记为已被搜索过：
	}
	当前队首元素出队; 
}
```

还是以上面那棵树为例子，那么操作顺序就是：

$A$入队并标记$A\quad\rightarrow\quad$搜索$A\quad\rightarrow \quad B$、$C$入队并标记$B$、$C\quad\rightarrow\quad$搜索$B\quad\rightarrow \quad D$、$E$入队并标记$D$、$E\quad\rightarrow \quad$搜索$C\quad\rightarrow \quad F$、$G$、$H$入队并标记$F$、$G$、$H\quad\rightarrow\quad$搜索$D\quad\rightarrow \quad$搜索$E\quad\rightarrow \quad I$入队并标记$I\quad\rightarrow\quad$搜索$F\quad\rightarrow\quad$搜索$G\quad\rightarrow\quad$搜索$H$

由于STL中的队列常数较大，效率较低，所以我们可以尝试手写队列，这是我经常用的一种比较简单的队列写法（注意不同题目的队列写法不同）：


```cpp
int Head=0,Tail=0; //队列的头指针和尾指针
struct point
{
	int Y,X,Step;//Y和X为坐标，Step为到达该点需要的步数 
}Queue[1000];//空间可以稍微开大一些
inline void Push(int y,int x,int step)//入队操作 
{
	Queue[Tail].Y=y;//元素从队尾进入 
	Queue[Tail].X=x;
	Queue[Tail].Step=step;
	++Tail;//尾指针+1 
	if(Tail==1000)
	{
		Tail=0;//实现队列空间的重复利用：如果尾指针超过了队列的范围，则重新变为0。可以利用这个方法将链状的队列变为环状的队列 
	}
	return ;
}
inline void Pop()//出队操作 
{
	++Head;//头指针+1（因为如果队列的同一个位置被重复使用，后面入队的元素可以直接覆盖原有的元素，所以可以不必初始化该位置） 
	if(Head==1000)
	{
		Head=0;//同上 
	}
	return ;
}
inline bool Empty()//判断队列是否为空 
{
	return Head==Tail?1:0;//如果头指针=尾指针，说明队列为空 
}
```

入队和标记的操作可以封装成一个`BFS()`函数：

```cpp
/*R和C为题目给出的数据，Visited[][]是用来标记每个坐标是否已被搜索过的bool型数组*/
inline void BFS(int y,int x)
{
	if(y>=1&&y<=R&&x>=1&&x<=C&&Square[y][x]=='.'&&Visited[y][x]==0)//判断坐标是否越界、该坐标是否允许行走、该坐标是否被搜索过 
	{
		Push(y,x,SS+1);//该坐标入队 
		Visited[y][x]=1;//同时将该坐标标记为已被搜索过 
	}
	return ;
}
```



在这道迷宫问题中，每个结点的子结点就是每个方格的上下左右四个方格。则主函数中搜索部分的内容为：

```cpp
/*个人习惯，先对队首元素的表示方式进行预处理，方便代码的书写*/
#define YY Queue[Head].Y
#define XX Queue[Head].X
#define SS Queue[Head].Step
int main()
{
	/*起点入队，同时将起点标记为已被搜索过*/ 
	Push(sy,sx,0);
	Visited[sy][sx]=1;
	
	/*如果队列不空，就一直进行搜索*/
	while(!Empty())
	{
		/*判断当前队首坐标是否为终点，如果是则直接输出答案，结束程序*/
		if(YY==gy&&XX==gx)
		{
			cout<<SS<<endl;
			return 0;
		}
		/*搜索队首坐标的上下左右四个点*/ 
		BFS(YY-1,XX);//上 
		BFS(YY+1,XX);//下 
		BFS(YY,XX-1);//左 
		BFS(YY,XX+1);//右 
		
		Pop();//队首元素出队 
	}
	return 0;
}
```

附上完整AC代码（注意：如果用scanf读入字符，可能会错误地读入换行符）：

```cpp
#include <iostream>

using namespace std;

/*个人习惯，先对队首元素的表示方式进行预处理，方便代码的书写*/
#define YY Queue[Head].Y
#define XX Queue[Head].X
#define SS Queue[Head].Step

/*题目给出的数据*/
int R,C,sy,sx,gy,gx;
char Square[51][51];

/*还需要一个Visited数组来判断一个坐标是否已经被搜索过*/
bool Visited[51][51]={};

/*因为STL中的队列常数较大，所以可以自行手写队列（介绍一种简单的队列写法）*/
int Head=0,Tail=0; //队列的头指针和尾指针
struct point
{
	int Y,X,Step;//Y和X为坐标，Step为到达该点需要的步数 
}Queue[1000];//空间可以稍微开大一些
inline void Push(int y,int x,int step)//入队操作 
{
	Queue[Tail].Y=y;//元素从队尾进入 
	Queue[Tail].X=x;
	Queue[Tail].Step=step;
	++Tail;//尾指针+1 
	if(Tail==1000)
	{
		Tail=0;//实现队列空间的重复利用：如果尾指针超过了队列的范围，则重新变为0。可以利用这个方法将链状的队列变为环状的队列 
	}
	return ;
}
inline void Pop()//出队操作 
{
	++Head;//头指针+1（因为如果队列的同一个位置被重复使用，后面入队的元素可以直接覆盖原有的元素，所以可以不必初始化该位置） 
	if(Head==1000)
	{
		Head=0;//同上 
	}
	return ;
}
inline bool Empty()//判断队列是否为空 
{
	return Head==Tail?1:0;//如果头指针=尾指针，说明队列为空 
}

/*广度优先搜索函数*/
inline void BFS(int y,int x)
{
	if(y>=1&&y<=R&&x>=1&&x<=C&&Square[y][x]=='.'&&Visited[y][x]==0)//判断坐标是否越界、该坐标是否允许行走、该坐标是否被搜索过 
	{
		Push(y,x,SS+1);//该坐标入队 
		Visited[y][x]=1;//同时将该坐标标记为已被搜索过 
	}
	return ;
}

int main()
{
	/*这句话可以关闭iostream与stdio的同步流，从而提高cin和cout的效率*/
	ios::sync_with_stdio(0);
	
	/*输入数据*/ 
	cin>>R>>C>>sy>>sx>>gy>>gx;
	for(int i=1;i<=R;++i)
	{
		for(int j=1;j<=C;++j)
		{
			 cin>>Square[i][j];
		}
	}
	
	/*起点入队，同时将起点标记为已被搜索过*/ 
	Push(sy,sx,0);
	Visited[sy][sx]=1;
	
	/*如果队列不空，就一直进行搜索*/
	while(!Empty())
	{
		/*判断当前队首坐标是否为终点，如果是则直接输出答案，结束程序*/
		if(YY==gy&&XX==gx)
		{
			cout<<SS<<endl;
			return 0;
		}
		/*搜索队首坐标的上下左右四个点*/ 
		BFS(YY-1,XX);//上 
		BFS(YY+1,XX);//下 
		BFS(YY,XX-1);//左 
		BFS(YY,XX+1);//右 
		
		Pop();//队首元素出队 
	}
	return 0;
}
```

$BurningEnderDragon\quad 2021.02.02$

---

## 作者：哈哈哈哈。 (赞：8)

# 典型的BFS
应该算是一道模板题吧，直接搜索就可以了。然后注意处理一下标记，搜索过的位置应该改变标记（~~当然我个人比较喜欢模拟成直接拿墙堵的操作~~）

------------
因为是在迷宫中移动，所以考虑**模拟方向**：

------------
```cpp
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};//每个括号中对应一种移动状态;
```
------------
存储坐标，使用**结构体**，同时还可以存当前移动的步数：

------------
```cpp
struct ss{
	int x,y,ans;//对应X坐标，Y坐标，以及移动步数;
};
```
------------
因为是找最短的路径，所以当BFS搜索到的第一个**合法坐标**，就是**最少消耗步数**，即**最优解**：

------------
```cpp
	if(now.x==ex&&now.y==ey)
		{
			return now.ans;//直接返回当前的步数;
		}
```
------------

贴代码 **QAQ**：


------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int sx,sy,ex,ey;
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};//模拟方向;
struct ss{
	int x,y,ans;//方便存储;
};
char ch;
bool vis[1001][1001];//存图;
queue<ss> q;//队列方便后面搜索使用;
int bfs(int x,int y,int ans)
{
	
	ss s;//记录初始坐标
	s.x=x;
	s.y=y;
	s.ans=ans;
	q.push(s);//存入队列;
	while(!q.empty())
	{
	
		ss now=q.front();//取出队首;
		q.pop();//弹出队首;
		if(now.x==ex&&now.y==ey)
		{
			return now.ans;//满足条件就可以返回;
		}
		for(int i=0;i<4;i++)//处理方向;
		{
			int tx=now.x+dir[i][0];
			int ty=now.y+dir[i][1];
			int tans=now.ans+1;//步数+1;
			if(tx>=1&&ty>=1&&tx<=n&&ty<=m&&vis[tx][ty]==true)//无障碍以及不越界的情况;
			{
				ss s;//保存新状态;
				s.x=tx;
				s.y=ty;
				s.ans=tans;
				vis[tx][ty]=false;//一定要标记，不然就会炸掉，鬼知道我电脑死机了几次;
				q.push(s);
			}
		}
	}
}
int main()
{
	cin>>n>>m;
	cin>>sx>>sy;
	cin>>ex>>ey;
	memset(vis,true,sizeof(vis));//初始化操作;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>ch;
			if(ch=='#')  vis[i][j]=false;//处理为01矩阵就好了;
		}
	cout<<bfs(sx,sy,0)<<endl;
}
```
------------
**模板题**。~~不存在很难吧~~ 也要认真学啊。。。



---

## 作者：Kogenta (赞：8)


## 学会广搜的我好开心（好吧假了点）
广搜的理论其实也就是覆盖吧，搜到一个点更新一次数据，如下

```c++
void bfs(int x,int y){
	queue<point>M;//说广搜一般用队列，其实这个题目中队列配结构体会更香（我打的在下面）
	poi.x=x;
	poi.y=y;
	M.push(poi);//存好数据就推进队列里（注意，普通队列即可）
	while(!M.empty()){//如果队列都空了就不能再进行了（说明不能到达吧，没有深究……）
		top=M.front();//取队首
		int now_d/*现在所到的点离起点的距离*/=d[top.x][top.y];//更新数据为到达前一个点用的步数
		M.pop();
		for(int i=0;i<4;i++){//搜索的时候一一对应
			if(a[top.x+dx[i]][top.y+dy[i]]=='.'){
			    int x_=top.x+dx[i];
			    int y_=top.y+dy[i];
			    if(x_<1||x_>n||y_<1||y_>m) continue;
			    if(p[x_][y_]==0){
				    poi.x=x_;
                    poi.y=y_;
                    //cout<<"["<<now_d<<"] "<<x_<<" "<<y_<<endl;//（检查数据用的）
                    M.push(poi);
                    p[x_][y_]=1;
                    d[x_][y_]=now_d+1;//注意：该点另开计数器，搜到的话计数器就加1
                }//写过马的遍历都应该懂，没写的也可以套上去
            }
        }
	}
}
```

头文件啥的寄几加了哈，半完整代码如下：

```c++
char a[10002][10002];
int d[10002][10002]={0};
bool p[10002][10002];
struct point{
	int x;
	int y;
}poi,top;
int step=0;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};//四个方向必须一一对应
void bfs(int x,int y){
	queue<point>M;
	poi.x=x;
	poi.y=y;
	M.push(poi);
	while(!M.empty()){
		top=M.front();
		int now_d/*现在所到的点离起点的距离*/=d[top.x][top.y];
		M.pop();
		for(int i=0;i<4;i++){//搜索的时候一一对应
			if(a[top.x+dx[i]][top.y+dy[i]]=='.'){
			    int x_=top.x+dx[i];
			    int y_=top.y+dy[i];
			    if(x_<1||x_>n||y_<1||y_>m) continue;
			    if(p[x_][y_]==0){
				    poi.x=x_;
                    poi.y=y_;
                    //cout<<"["<<now_d<<"] "<<x_<<" "<<y_<<endl;//（检查数据用的）
                    M.push(poi);
                    p[x_][y_]=1;//标记已入队（不能重复计算，否则会炸……虽然我也没试过）
                    d[x_][y_]=now_d+1;
                }
            }
        }
	}
}
int main(){
	cin>>n>>m>>x1_>>y1_>>x2_>>y2_;
	for(int i=1;i<=n;i++){
		string str;
		cin>>str;//本人习惯用string拆分。有别的做法欢迎评论~
		for(int j=1;j<=m;j++){
			a[i][j]=str[j-1];
		}
	}
	p[x1_][y1_]=1;//先把初始点标记防止再搜一次
	bfs(x1_,y1_);
	cout<<d[x2_][y2_]<<endl;//目标点的次数输出（其实跟题目的图片推理原理类似……）
	return 0;
}
```

完美收场！

本人的第一篇题解，感谢大家观看~

---

## 作者：CrTsIr400 (赞：4)

啊这，双向bfs的题解就 $1$ 篇，我这里详细讲解一下吧awa。

双搜可以**大幅度地减少搜索范围和时间复杂度**，对于一些**给定起始状态和终止状态的题目**无比适合。

比如这道题目，给出了起始坐标和终止坐标。

那么我们即可新建两个队列，**一个队列 $q$ 存从起始点开始遍历、扩展的bfs搜索树，一个队列 $p$ 存从终点开始遍历、扩展的bfs搜索树。**

每次一次性扩展两个队列的头端，先扩展 $q$，再扩展 $p$ 。

扩展函数和普通的bfs大同小异，但是不同的地方在于**要开两个标记数组**，一个 $b[i][j]$ 存从起始点出发到 $(i,j)$ 点的距离，一个 $d[i][j]$ 存从终点出发到 $(i,j)$ 点的距离。

要是在 $q$ 队列里扩展中遇到了这个点没有在之前的 $q$ 队列里访问过，且不走出边界和这个地方不是墙，即可扩展；

但是在扩展时注意判断，如果这个 $(x,y)$ 点的 $d[x][y]$ 并不是 `inf` ，那么全部搜索结束，答案即为 $d[x][y]+b[x][y]-1$ ；

对于 $p$ 队列的扩展，也是同理。

伪代码如下：

```cpp
Q,P<-queue
d[maxn][maxm],b[maxn][maxm]<-int
DBFS(sx,sy,ex,ey)
 Q.push(sx,sy,0)
 P.push(ex,ey,0)
 while(Q不为空&&P不为空)
  extend(Q);
  extend(P);
  
extend(Que)
 往四个方向枚举;
  x=新扩展出的x坐标,y=新扩展出的y坐标;
  if(合法)
   丢进新队列;
   if(在另一个队列所构成的搜索树里有相应的(x,y)坐标)
    答案=到了此搜索树里(x,y)坐标的层数+
         另一棵搜索树里(x,y)坐标的层数-1;
    退出所有扩展与DBFS;
 队列去头;
```

---

## 作者：zzhhtt (赞：4)

见没有bfs题解，本蒻蒟就发一篇。


```
#include <iostream>
using namespace std;
int a[105][105],n,m,x1,y1,x2,y2;//数组开105就够了
void dfs(int x,int y,int s)
{
    if(a[x][y]==-1)  return ;
    if(a[x][y]!=0&&a[x][y]<=s)  return ;
    a[x][y]=s;
    s+=1;
    //搜四个方向
    dfs(x+1,y,s);
    dfs(x-1,y,s);
    dfs(x,y+1,s);
    dfs(x,y-1,s);
}
int main()
{
    int i,j;
    char c;
    for(i=0;i<104;i++){
        for(j=0;j<104;j++){
          a[i][j]=-1;
        }
    }
    cin>>n>>m>>x1>>y1>>x2>>y2;
    for(i=1;i<=n;i++){
       for(j=1;j<=m;j++){
      	  cin>>c;
      	  if(c=='.')  a[i][j]=0;
      	  else  a[i][j]=-1;
       } 
    }
    //深搜
    dfs(x1,y1,0);
    //求最短路径
    cout<<a[x2][y2]<<endl;
    return 0;
}
```


---

## 作者：Dry_ice (赞：4)

直接切入正题（~~措不及防~~

## 思路
这题的可用算法有 $2$ 种，都是搜索。

### 广度优先搜索（BFS）
核心数据结构：队列。

由于本人不太爱写代码相对较长的广搜，所以今天主要介绍深搜。

### 深度优先搜索（DFS）
核心数据结构：栈

题目中说了，```.```表示空地，```#``` 表示墙壁即障碍，那么只要走在空地上就行，一步步地前进，总能到的。

这又让我想起了《城南旧事》里描写骆驼的一句话啊：
> 看它从不着急，慢慢地走，慢慢地嚼，总会走到的，总会吃饱的。

#### 但是！当你提交代码，评测完毕之后，你会哭的。![/kel](https://cdn.luogu.com.cn/upload/pic/62226.png)

最终还是 ```Time Limit Exceeded``` 了！于是我们想到了剪枝、记忆化等等的优化操作。这里着重介绍这题的**最优性剪枝**思路。

如果我们搜到一个格子时，发现比前面的算出到达这个的最小步数还要多，那么显然这条路线较长了，不符合最优性，一刀砍掉。

那么为了记录到达一个格子的最优步数，需要开一个记忆化数组。
每次走到这个格子，就判断一下是否最优：如果比数组里的值更优，则替换数组中的值；如果比数组中的值还要差，那么不继续搜下去，直接 ```return```。

经过这样一番优化，就珂以 ```Accepted``` 了。

代码就不粘了，着重看懂思路。看懂思路后，这个较简单的 DFS 我觉得 ~~相对较弱的OIer（比如我~~ 应该也是珂以写出来的。

> 期待 AtCoder 早日能和 lg 接上端口。

欢迎大家在评论区讨论个人观点，提出这篇题解的改进建议！

---

## 作者：傅思维666 (赞：2)

# 洛谷 AT896 幅優先探索

[洛谷传送门](https://www.luogu.com.cn/problem/AT896)

## 题目描述

たかはし君は迷路が好きです。今、上下左右に移動できる二次元盤面上の迷路を解こうとしています。盤面は以下のような形式で与えられます。

* まず、盤面のサイズと、迷路のスタート地点とゴール地点の座標が与えられる。
* 次に、それぞれのマスが通行可能な空きマス(`.`)か通行不可能な壁マス(`#`)かという情報を持った盤面が与えられる。盤面は壁マスで囲まれている。スタート地点とゴール地点は必ず空きマスであり、スタート地点からゴール地点へは、空きマスを辿って必ずたどり着ける。具体的には、入出力例を参考にすると良い。

今、彼は上記の迷路を解くのに必要な最小移動手数を求めたいと思っています。どうやって求めるかを調べていたところ、「幅優先探索」という手法が効率的であることを知りました。幅優先探索というのは以下の手法です。

* スタート地点から近い(たどり着くための最短手数が少ない)マスから順番に、たどり着く手数を以下のように確定していく。説明の例として図1の迷路を利用する。

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/AT896/66c8ec83823b44c669c3cebc0f8e22fe25426ff4.png) 図1. 説明に用いる盤面- 最初に、スタート地点は、スタート地点から手数0でたどり着ける(当然)ので、最短手数0で確定させる(図2)。

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/AT896/8593b32b646151ca3c053e351d9b252bd75be68a.png) 図2. 最短手数0でたどり着けるマスが確定(初期)- 次に、スタート地点の四近傍(上下左右)の空きマスについて、手数1で確定させる(図3)。

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/AT896/837a9e9cfc8e10b2c6991fc60d3e188cfbb80c4c.png) 図3. 最短手数1でたどり着けるマスが確定- 次に、手数1で確定したそれぞれのマスの4近傍を見て、まだ確定していない空きマスがあればそのマスを手数2で確定させる(図4)。

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/AT896/fa2a9223991451ee677d5aec6bf4aab529f8e328.png) 図4. 最短手数2でたどり着けるマスが確定- 次に、手数2で確定したそれぞれのマスの4近傍を見て、まだ確定していない空きマスがあればそのマスを手数3で確定させる(図5)。

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/AT896/8cf6275c928ac872f31b0d672e6c71b35c97f4af.png) 図5. 最短手数3でたどり着けるマスが確定- 次に、手数3で確定したそれぞれのマスの4近傍を見て、まだ確定していない空きマスがあればそのマスを手数4で確定させる(図6)。

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/AT896/abbfb834a753480fb25fb01f4f74a7d83fc59121.png) 図6. 最短手数4でたどり着けるマスが確定- 上記の手順を確定の更新が無くなるまで繰り返すと、スタート地点からたどり着ける全ての空きマスについて最短手数が確定する(図7)。スタートとゴールは必ず空きマスを辿ってたどり着けるという制約があるので、ゴール地点への最短手数も分かる。

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/AT896/766f0b1524ec5edf67ce3611317292c98d7a99e8.png) 図7. すべてのたどり着けるマスへの最短手数が確定さて、この処理をスマートに実装するためには、先入れ先出し(FIFO)のキュー(Queue)というデータ構造を用いると良いことが知られています。もちろん、使わなくても解くことは可能です。今回、よく分からなければ思いついた方法で解くことをおすすめします。先入れ先出しのキューとは以下のような機能を持つデータ構造です。

* 追加(Push): キューの末尾にデータを追加する。
* 取り出し(Pop): キューの先頭のデータを取り出す。

このデータ構造を使うと、先ほどの幅優先探索の説明における「マスの最短手数の確定」のタイミングでその確定マスをキューに追加し、追加操作が終わればPopを行い、取り出したマスの4近傍を調べるということを繰り返せば(つまり先に追加されたものから順番に処理していけば)、簡潔に処理ができることが分かります。

## 输入格式

入力は以下の形式で標準入力から与えられる。

```
 $ R\ C $ 
 $ sy\ sx $ 
 $ gy\ gx $ 
 $ c_{(1,1)}c_{(1,2)}\ …\ c_{(1,C)} $ 
 $ c_{(2,1)}c_{(2,2)}\ …\ c_{(2,C)} $ 
:
 $ c_{(R,1)}c_{(R,2)}\ …\ c_{(R,C)} $ 
```

* 11 行目には、行数 R(1≦R≦50)*R*(1≦*R*≦50) と列数 C(1≦C≦50)*C*(1≦*C*≦50) がそれぞれ空白区切りで与えられる。
* 22 行目には、スタート地点の座標 (sy,sx)(*s**y*,*s**x*) が空白区切りで与えられる。スタート地点が sy*s**y* 行 sx*s**x* 列にあることを意味する。 1≦sy≦R1≦*s**y*≦*R* かつ 1≦sx≦C1≦*s**x*≦*C* である。
* 33 行目には、ゴール地点の座標 (gy,gx)(*g**y*,*g**x*) が空白区切りで与えられる。ゴール地点が gy*g**y* 行 gx*g**x* 列にあることを意味する。 1≦gy≦R1≦*g**y*≦*R* かつ 1≦gx≦C1≦*g**x*≦*C* であり、 (gy,gx)≠(sy,sx)(*g**y*,*g**x*)=(*s**y*,*s**x*) であることが保障されている。
* 44 行目から R*R* 行、長さ C*C* の文字列が 11 行ずつ与えられる。各文字は `.` もしくは `#` のいずれかであり、 i*i* 回目 (1≦i≦R)(1≦*i*≦*R*) に与えられられる文字列のうち j*j* 文字目 (1≦j≦C)(1≦*j*≦*C*) について、その文字が `.` なら、マス (i,j)(*i*,*j*) が空きマスであり、`#` なら、マス (i,j)(*i*,*j*) が壁マスであることをあらわす。
* 盤面は壁マスで囲まれている。つまり、 i=1,i=R,j=1,j=C*i*=1,*i*=*R*,*j*=1,*j*=*C* のうちいずれか1つでも条件を満たすマス (i,j)(*i*,*j*) について、 c_{(i,j)}*c*(*i*,*j*) は `#`である。また、スタート地点とゴール地点は必ず空きマスであり、スタート地点からゴール地点へは、空きマスを辿って必ずたどり着ける。

## 输出格式

* スタート地点からゴール地点に移動する最小手数を 11 行に出力せよ。最後に改行を忘れないこと。

## 题意翻译

**题面描述：**给你一个能上下左右移动的迷宫，求最少需要多少步才能走出迷宫 。

**输入格式：**第一行两个正整数R，C，分别表示迷宫的行数和列数；

第二行两个正整数sy，sx，表示起点坐标(sy,sx)；

第三行两个正整数gy，gx，表示终点坐标(gy,gx)；

接下来的R行，每行为长度为C的字符串，字符串仅含两种字符，'.'与'#' , '.'表示空地，可以走；'#'表示墙壁，不能走。

**输出格式：**输出仅一行整数，表示最少需要多少步才能走出迷宫。（题目保证有解）

**数据范围：**R,C<=50; sy,gy<=R; sx,gx<=C 。

---

## 题解：

宽搜基础题目。

其实走地图这种题目，既可以拿宽搜解决，也可以拿深搜解决。但是这道题为什么优先考虑BFS呢？因为BFS的层次性可以方便地求解出最少步数这个信息。

至于宽搜的具体实现，不再赘述。其走向下一步和判断下一步可不可走的部分和深搜一致。只是使用队列这个结构来逐层拓展而已（明明说不赘述然而还是赘述了）

1号裸宽搜代码：

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<iostream>
using namespace std;
char mp[52][52];
int v[52][52];
int dx[]={0,0,0,-1,1};
int dy[]={0,1,-1,0,0};
int r,c,sx,sy,ex,ey;
struct node
{
	int x,y,dep;
}a;
queue<node> q;
int main()
{
	int r,c;
	scanf("%d%d%d%d%d%d",&r,&c,&sx,&sy,&ex,&ey);
	for(int i=1;i<=r;i++)
		scanf("%s",mp[i]+1);
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			if(mp[i][j]=='#')
				v[i][j]=1;
	a.x=sx;a.y=sy;a.dep=0;
	q.push(a);
	while(!q.empty())
	{
		node top=q.front();
		q.pop();
		if(top.x==ex&&top.y==ey)
		{
			printf("%d\n",top.dep);
			break;
		}
		for(int i=1;i<=4;i++)
		{
			int xx=top.x+dx[i];
			int yy=top.y+dy[i];
			if(xx<1||yy<1||xx>r||yy>c||v[xx][yy])
				continue;
			a.x=xx,a.y=yy,a.dep=top.dep+1;
			v[xx][yy]=1;
			q.push(a);
		}
	}
	return 0;
}
```

然后讲一下双向BFS。

双向BFS可以算作是BFS的一种优化。顾名思义就是从两个方向同时开始BFS，碰头即截止 。它适用于既给出起点，又给出终点的情况。非常适合本题。

双向BFS的思路是开两个队列来BFS，每次选取队列长度较小（也就是搜索树规模较小）的那个进行拓展，如果碰头，就直接统计答案。

2号双向BFS代码：

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<iostream>
using namespace std;
char mp[52][52];
int v1[52][52],v2[52][52];
int ans1[52][52],ans2[52][52];
int dx[]={0,0,0,-1,1};
int dy[]={0,1,-1,0,0};
int r,c,sx,sy,ex,ey;
struct node
{
	int x,y;
}a,b;
queue<node> q1;
queue<node> q2;
int main()
{
	scanf("%d%d%d%d%d%d",&r,&c,&sx,&sy,&ex,&ey);
	if(sx==ex&&sy==ey)
	{
		puts("0");
		return 0;
	}
	for(int i=1;i<=r;i++)
		scanf("%s",mp[i]+1);
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			if(mp[i][j]=='#')
				v1[i][j]=v2[i][j]=1;
	memset(ans1,127,sizeof(ans1));
	memset(ans2,127,sizeof(ans2));
	a.x=sx;a.y=sy;
	b.x=ex;b.y=ey;
	ans1[sx][sy]=0,ans2[ex][ey]=0;
	q1.push(a);
	q2.push(b);
	while(!q1.empty()&&!q2.empty())
	{
		if(q1.size()<q2.size())
		{
			node top=q1.front();
			q1.pop();
			for(int i=1;i<=4;i++)
			{
				int xx=top.x+dx[i];
				int yy=top.y+dy[i];
				if(xx<1||yy<1||xx>r||yy>c||v1[xx][yy])
					continue;
				a.x=xx,a.y=yy;
				v1[xx][yy]=1;
				ans1[xx][yy]=ans1[top.x][top.y]+1;
				q1.push(a);
				if(ans2[xx][yy]<=100000)
				{
					printf("%d\n",ans1[xx][yy]+ans2[xx][yy]);
					return 0;
				}
			}
		}
		else
		{
			node top=q2.front();
			q2.pop();
			for(int i=1;i<=4;i++)
			{
				int xx=top.x+dx[i];
				int yy=top.y+dy[i];
				if(xx<1||yy<1||xx>r||yy>c||v2[xx][yy])
					continue;
				a.x=xx,a.y=yy;
				v2[xx][yy]=1;
				ans2[xx][yy]=ans2[top.x][top.y]+1;
				q2.push(a);
				if(ans1[xx][yy]<=100000)
				{
					printf("%d\n",ans1[xx][yy]+ans2[xx][yy]);
					return 0;
				}
			}
		}
	}
	return 0;
}
```



---

## 作者：lzxhdxx (赞：2)

# 题解AT896 幅優先探索（bfs，dfs，双向bfs）
**这是一篇整合版代码！！**

看到前面的大佬们都用的是bfs和dfs，竟然没有双向bfs的代码，那我就写一写双向bfs，发一篇三种方法整合版的吧！

### 题意：
给定r*c的地图和起点、终点，求从起点到终点最少需要多少步（'#'是障碍物，不能走，'.'是平地，可以走）

### 思路：
我们看题目前给的一系列做题过程，发现题目给的思路是bfs，所以我们一定可以用bfs&双向bfs，但是我们仔细思考一下，这个题真的不可以用dfs吗？

我们看数据规模，$1≦R≦50,1≦C≦50$，我们可以发现此题数据小，其实完全可以用dfs，其优点在于编程复杂度低，缺点在于速度较慢（数据小可以忽略）

所以我们制定搜索策略：

1.双向bfs：从起点和终点同时bfs，**哪个方向的队列的新状态少就扩展哪个队列**，两个方向相遇就直接返回并输出**两个方向到达当前状态的步数和**

2.bfs：从起点开始搜索，层层递进，只搜索'.'，**到达终点就直接返回**并输出

3.dfs：从起点开始搜索，只搜索'.'，**到达终点就更新答案，最后输出**（不能直接返回）

根据搜索策略：我们得到以下代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

int r, c, sx, sy, ex, ey, dx[5] = { 0,-1,1,0,0 }, dy[5] = { 0,0,0,-1,1 }, cnt1[110][110] = { 0 }, cnt2[2][110][110] = { 0 };
char mp[110][110];
bool vis1[110][110] = { false }, vis2[2][110][110] = { false };
//前面所有的二维数组(除了mp)是给bfs&dfs用的，三维数组是给双向bfs用的
queue<pair<int, int> >Q, Que[2];//Q是bfs用的，Que是双向bfs用的

//Solution 1:双向bfs
int expand(int sub)//扩展新状态
{
	int nowx = Que[sub].front().first, nowy = Que[sub].front().second;//取出队头
	for (int i = 1; i <= 4; i++)
	{
		int newx = nowx + dx[i], newy = nowy + dy[i];//扩展新点
		if (newx >= 1 && newy >= 1 && newx <= r && newy <= c && !vis2[sub][newx][newy] && mp[newx][newy] != '#')//判断是否不越界，没走过而且不是障碍物
		{
			Que[sub].push(make_pair(newx, newy));//当前方向的队列压入新状态
			cnt2[sub][newx][newy] = cnt2[sub][nowx][nowy] + 1, vis2[sub][newx][newy] = true;//记录新状态的步数，标记为走过
			if (vis2[1 - sub][newx][newy]) return cnt2[1 - sub][newx][newy] + cnt2[sub][newx][newy];//如果另一层的新状态已经走过（即vis[1-sub][newx][newy]），那就直接返回两层的步数和
		}
	}
	Que[sub].pop();//弹出已经处理完的队列
	return 0;//返回0就是还没有
}

int Two_Ways_Bfs()//双向广搜
{
	Que[0].push(make_pair(sx, sy)), Que[1].push(make_pair(ex, ey));//两个方向分别压入起点、终点
	cnt2[0][sx][sy] = 0, cnt2[1][ex][ey] = 0;//记录步数的数组两层分别标记起点、终点步数为0
	vis2[0][sx][sy] = true, vis2[1][ex][ey] = true;//记录是否走过的数组两层分别标记起点、终点为走过
	while (!Que[0].empty() && !Que[1].empty())//判断两个队列是否均不为空
	{
		if (Que[0].size() < Que[1].size())//哪个方向状态少就扩展哪个 { int tmp = expand(0); if (tmp) return tmp; }//如果返回的不是0就是相遇了，返回步数
		else { int tmp = expand(1); if (tmp) return tmp; }//同上
	}
	return -1;//不可能走到
}

//Solution 2:bfs
void bfs()//广搜
{
	Q.push(make_pair(sx, sy));//压入起点
	cnt1[sx][sy] = 0, vis1[sx][sy] = true;//起点步数记为0，标记为走过
	while (!Q.empty())//记录状态的队列不能为空
	{
		int nowx = Q.front().first, nowy = Q.front().second;//取出队头
		if (nowx == ex && nowy == ey) return;//到终点就返回
		for (int i = 1; i <= 4; i++)
		{//四个方向分别扩展
			int newx = nowx + dx[i], newy = nowy + dy[i];//扩展的新点
			if (newx >= 1 && newy >= 1 && newx <= r && newy <= c && !vis1[newx][newy] && mp[newx][newy] != '#')//如果不越界，没走过且不是障碍物就正常扩展
			{
				Q.push(make_pair(newx, newy));//压入新状态
				cnt1[newx][newy] = cnt1[nowx][nowy] + 1, vis1[newx][newy] = true;//记录新状态的步数，标记为走过
			}
		}
		Q.pop();//弹出已经处理完的当前点
	}
}

//Solution 3:dfs
void dfs(int x, int y, int stp)
{
	if (mp[x][y] != '#' && x >= 1 && y >= 1 && x <= r && y <= c && stp < cnt1[x][y])
	{//如果当前状态不越界，不是障碍物且当前的步数小于当前点的最小步数就继续dfs
		cnt1[x][y] = stp;//更新当前状态最小步数
		for (int i = 1; i <= 4; i++)//四个方向扩展
			dfs(x + dx[i], y + dy[i], stp + 1);//dfs下一个状态
	}
}

int main()
{
	memset(cnt1, 127 / 3, sizeof(cnt1));//初始化为一个很大的数
	ios::sync_with_stdio(false);//加快cin,cout
	cin >> r >> c >> sx >> sy >> ex >> ey;
	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++)//输入
			cin >> mp[i][j];
	if (sx == ex && sy == ey) return cout << 0 << endl, 0;//特判，如果起点就是终点就输出0并return 0;
	/*dfs(sx, sy, 0);//执行深搜
	bfs();//执行广搜
	cout << cnt1[ex][ey] << endl;//深搜和广搜输出cnt记录的终点最小步数*/
	cout << Two_Ways_Bfs() << endl;//双向广搜直接输出返回值
	return 0;
}
```

### 数据：

双向bfs：25ms /  384.00KB C++ 

bfs：25ms /  384.00KB C++ 

dfs：160ms /  384.00KB C++ 

PS：

1.代码长度因为是三种方法的总和（因为整合了），不具有参考价值，就不贴了

2.此题数据小，所以双向bfs和bfs时间一样~~有可能是我写假了~~，如果数据大就可以看出双向bfs的优势了

三种方法整合（1种全新方法），求管理大大给过

---

## 作者：Doqin07 (赞：1)

#### 简单题，直接无脑bfs即可
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace I_love{
    typedef long long ll;
    #define F(i,l,r) for (int i=l;i<=r;++i)
    #define REP(i,r,l) for (int i=r;i>=l;--i)
    #define mem(a,b) memset(a,b,sizeof(a));
    #define MP make_pair;
    #define PB push_back
    #define readI(x) x=RI();
    #define readInm(x,y) readI(x);readI(y);
    #define readIa(n,a) F(i,1,n)readI(a[i]);
    #define readIA(n,m,a) F(i,1,n)F(j,1,m)readI(a[i][j]);
    #define readL(x) x=RL();
    #define readLnm(x,y) readL(x);readL(y);
    #define readLa(n,a) F(i,1,n)readL(a[i]);
    #define readLA(n,m,a) F(i,1,n)F(j,1,m)readL(a[i][j]);
    const int maxn=1e5+5;
    const int N=1e3+5;
    const int maxm=1e6+5;
    const int INF=INT_MAX;
    const int mod=1e9+7;
    int RI(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){f=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
    ll RL(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){f=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
    // 以上为define
    // 正片开始qwq
    int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1}; //方向数组
    int n,m,sx,sy,ex,ey; 
    char a[N][N];bool vis[N][N];
    struct node{int x,y,t;};
    void input(){
        readInm(n,m);
        readInm(sx,sy);
        readInm(ex,ey);
        F(i,1,n){
            F(j,1,m){
                cin>>a[i][j];
            }
        }
        // 常规读入数据
    }
    void bfs(){
        mem(vis,0);
        // 清空vis标记数组，好习惯
        queue<node> q;
        q.push(node{sx,sy,0});
        vis[sx][sy]=1;
        // 一开始把起点的坐标传到队列中，并把vis数组设为1，表示被访问过
        while(!q.empty()){
            node u=q.front();q.pop();
            if(u.x==ex&&u.y==ey){
                printf("%d\n",u.t);
                return;
            }
            // 假如到达终点则输出
            F(i,0,3){
                int xx=u.x+dx[i],yy=u.y+dy[i];
                if(xx<1||yy<0||xx>n||yy>m)continue;// 若不在地图里面，超出地图边界，结束
                if(vis[xx][yy]||a[xx][yy]=='#')continue;// 若已被访问过或者不能走，结束
                q.push(node{xx,yy,u.t+1});
                vis[xx][yy]=1;
                // 状态更新
            }
        }
    }
    void run(){
        bfs();
    }
    void OI_Akame(){
        input();
        run();
    }
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
#endif
    I_love::OI_Akame();
    // I LOVE LUOGU!
    return 0;
}
```
--------
## ありがとうございます。
## 谢谢！求过!

---

## 作者：做梦想Peach (赞：1)

这题和[AT1350](https://www.luogu.com.cn/problem/AT1350)几乎是一样的，这不过[AT1350](https://www.luogu.com.cn/problem/AT1350)不需要计算最短的路程。

最近学习了BFS，这就是一道裸的BFS。

不需要管那么长度题目描述，大概意思就是：给你一张地图，.表示可以走，#表示不可以走，给你两个点的坐标$A(X_1,Y_1),B(X_2,Y_2)$，求出$A$到$B$的最少步数。每次可以走上、下、左、又四个方向。

我们可以定义一个$dx$和$dy$来枚举四个方向，像这样：
```cpp
int dx[5]={0,0,-1,1},
	dy[5]={1,-1,0,0};
```
然后直接枚举所有可能达到的点就可以了。

看到大佬都是用STL里的queue或者是DFS，我就来补一篇手动模拟队列的题解吧。
 
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
int read () {
	int s=0,w=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') w=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
struct Node {
	int x;
	int y;
	int step;
}queue[1000010];
char c;
int dx[5]={0,0,-1,1},
	dy[5]={1,-1,0,0};//四个方向增量。
int n,m,X1,Y1,X2,Y2,i,j;
bool map[1010][1010],vis[1010][1010];//map表示地图，vis表示这个点是否被访问过。
void bfs () {
	int head=0,tail=1,nx,ny,i;//head头指针，tail尾指针，nx新的点的X坐标，ny新的点的Y坐标。
	queue[tail].x=X1;
	queue[tail].y=Y1;
	queue[tail].step=0;
	vis[X1][Y1]=true;//初始化。
	while (head<tail) {
		head++;
		for (i=0;i<4;i++) {
			nx=queue[head].x+dx[i];
			ny=queue[head].y+dy[i];//枚举。
			if (nx>=1&&nx<=n&&ny>=1&&ny<=m&&map[nx][ny]==true&&vis[nx][ny]==false) {//这个点既不能超出地图，也不能是不能访问的，也不能是已经被访问过的。
				tail++;
				queue[tail].x=nx;
				queue[tail].y=ny;
				queue[tail].step=queue[head].step+1;//保存。
				vis[nx][ny]=true;//记录下这个状态。
				if (nx==X2&&ny==Y2) {
					printf ("%d\n",queue[tail].step);
					return;//如果已经找到了，就直接return！
				}
			}
		}
	}
	return;//好习惯。
}
int main () {
	n=read(); 
	m=read();
	X1=read();
	Y1=read();
	X2=read();
	Y2=read();//X1，Y1，X2，Y2为起点和终点。
	for (i=1;i<=n;i++) 
		for (j=1;j<=m;j++) {
			cin>>c;
			if (c=='.') map[i][j]=true;
			if (c=='#') map[i][j]=false; //记录下这个地图。
		}
	map[X1][Y1]=false;//起点不可以再走，提前把它置为false。
	bfs ();
	return 0;
}
```
结束啦，![](https://cdn.luogu.com.cn/upload/image_hosting/eelk6mg4.png?x-oss-process=image/resize,m_lfit,h_170,w_225)！

---

## 作者：Otomachi_Una_ (赞：0)

标准的 BFS ，先让起点入队，每次取队首，如果队首已经是终点直接输出，不然进行四联通扩展队列。

## _Code_

```cpp
#include<iostream>
#include<queue>
using namespace std;
#define ll long long
const int MAXN=55;
char s[MAXN][MAXN];
struct node{
	int x,y,w=0;
}ds,de,dt;
bool g[MAXN][MAXN];//是否到过
queue <node> q;
int dx[5]={-1,0,0,1};
int dy[5]={0,1,-1,0};//四联通
int r,c;
int main(){
    cin>>r>>c>>ds.x>>ds.y>>de.x>>de.y;
    for(int i=1;i<=r;i++)
    	for(int j=1;j<=c;j++)
    		cin>>s[i][j];
    q.push(ds);
    while(!q.empty()){
    	ds=q.front();
    	q.pop();
    	if(s[ds.x][ds.y]!='.'||g[ds.x][ds.y])
    		continue;
    	if(ds.x==de.x&&ds.y==de.y){//找到终点
    		cout<<ds.w<<endl;//atcoder 特色
    		return 0;
    	}
    	for(int i=0;i<=3;i++){
    		dt.x=ds.x+dx[i];
    		dt.y=ds.y+dy[i];
    		dt.w=ds.w+1;
    		q.push(dt);
    	}
    	g[ds.x][ds.y]=1;
    }
}
```
后记：

很多 dalao 代码会比蒟蒻的长，但是蒟蒻的代码不经意间（没开 O2） 就可以拿到最优解了，其实写上一个快读运行会更快一点，这里给出 char 快读的参考代码：
```cpp
inline char read(){
    char r=getchar();
    while(r=='\n' /*||r==' '*/ )//因为此题输入字符阵中不含有空格，可以忽略。
        r=getchar();
    return r;
}
```


---

## 作者：1lgorithm (赞：0)

## 经典bfs题
这道题就是一道bfs,所以使用模板就可以了。

代码：

```cpp
#include<iostream>
#include<queue>
using namespace std;
int a[51][51],vis[51][51],ans[51][51];
char c;
int n,m,sx,sy,ex,ey;
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
void bfs(int sx,int sy,int ex,int ey){
	queue <int> quex,quey;
	vis[sx][sy]=1,ans[sx][sy]=0;
	quex.push(sx);
	quey.push(sy);
	while(quex.size()){
		int x=quex.front(),y=quey.front();
		if(x==ex&&y==ey){
			cout<<ans[x][y]<<endl;
			return ;
		}
		quex.pop(),quey.pop();
		for(int i=0;i<4;i++){
			int xx=x+dx[i];
			int yy=y+dy[i];
			if(xx<1||yy<1||xx>n||yy>m) continue;
			if(vis[xx][yy]==0&&a[xx][yy]==0){
				quex.push(xx);
				quey.push(yy);
				vis[xx][yy]=1;
				ans[xx][yy]=ans[x][y]+1;
			}
		}
	}
}
int main(){
	cin>>n>>m;
	cin>>sx>>sy>>ex>>ey;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c;
			if(c=='#') a[i][j]=1;
			if(c=='.') a[i][j]=0;
		}
	}
	bfs(sx,sy,ex,ey);
}
```


---

## 作者：Mr_WA的大号 (赞：0)

我们C++题解，变化无穷呀。小学生又来发题解了！

题号：AT896

算法：记忆化深度优先搜索

难度：★★★★

## 开课啦！

这一道题我们有两种思路，第一种是BFS，广度优先搜索（~~可我不会写~~）。另一种就是我们的记忆化深度优先搜索。

记忆化深度优先搜索，和深度优先搜索差不多的思路，只是每次都记下当前的最优解。

为什么不直接用深度优先搜索呢？以为我已经试过了，在题目的第三个样例中，它就会超时，也就是TLE。记忆化深度优先搜索可以大大的节省时间，所以我们应该选用记忆化深度优先搜索。

好了，现在上代码：
```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<string.h>
#include<algorithm>
using namespace std;
int n,m;
int x,y,xx,yy;
int a[60][60];
char ch;//定义变量
void dfs(int x1,int y1,int g)//记忆化深度优先搜索
{
	if(a[x1][y1]==-1)return ;//如果越界了，就返回
	if(a[x1][y1]!=0&&a[x1][y1]<=g)return ;//如果当前解不是最优解，返回
	a[x1][y1]=g;//否则就替换为最优解
	dfs(x1+1,y1,g+1);//递归
	dfs(x1-1,y1,g+1);
	dfs(x1,y1+1,g+1);
	dfs(x1,y1-1,g+1);
}
int main()
{
	cin>>n>>m>>x>>y>>xx>>yy;//输入
	for(int i=0; i<=51; i++)
		for(int j=0; j<=51; j++)
			a[i][j]=-1;//赋值
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
		{
			cin>>ch;//输入矩阵
			if(ch=='.')a[i][j]=0;//赋值
		}
	dfs(x,y,0);//开始搜索
	cout<<a[xx][yy]<<endl;//输出。AT切记要换行
	return 0;//结束
}
```
祝大家能顺利AC！

---

## 作者：Leonx (赞：0)

 	非常典型的BFS题，蒟蒻第一次投题解，求放过┭┮﹏┭┮ 仅用于学术交流，请勿抄袭，谢谢 O(∩_∩)O/ 思路很简单，套模板，搜就完了 本蒟蒻用数组模拟队列，不建议这样做，用STL更好，时空优异。 具体思路见代码ο(=•ω＜=)ρ⌒☆
    #include <iostream>
    using namespace std;   
    char map[51][51];//图 
    int n,m,sx,sy,mx,my;
    int xt[5]={0,1,-1,0,0};
    int yt[5]={0,0,0,-1,1};//用来表示四个方向
    int q[5000][3]; //队列用于记录走到每个位置的步数，坐标，
    //懒得算最多有多少元素，队列直接开大了
    int main()
    { 
    	cin>>n>>m>>sx>>sy>>mx>>my;

    	for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    		cin>>map[i][j];//读图

    	int x,y;
    	int t=0,w=1;//初始化队首，队尾

    	q[1][1]=sx；//记录开始点的x 
    	q[1][2]=sy;//记录开始点的y
    	q[1][3]=0;//将开始点步数设为0

    /*开始BFS*/
    do{
    		t++;//头指针++；此时对应的是开始点
			for(int i=1;i<=4;i++)
			{

			x=q[t][1]+xt[i];	
			y=q[t][2]+yt[i];
	//判断四个方向是否合法
		   		if(x>0&&y>0&&x<=n&&y<=m&&map[x][y]=='.')
				{

    				w++;//找到一个合法元素，元素进入队列，尾指针++
    				map[x][y]='#';//覆盖该点，避免再次被搜到
    				q[w][1]=x;
    				q[w][2]=y;//记录坐标
    				q[w][3]=q[t][3]+1;//加法原理，记录步数

    				if(x==mx&&y==my)//发现目标点
    				{
        //第一次找到就是最短的
        			cout<<q[w][3]<<endl;
        //这里要注意，是要有换行的，不然全WA，日语题目里是有的，中文没翻译出来（不要问我是怎么知道的）
        			return 0;//退出程序，完美结束运行
    				}
				}
 			} 	
		}while(t<w);//判断队列中是否还有剩余元素，有则继续搜
 	return 0;
	}

---

## 作者：LJC00111 (赞：0)

经典广搜题
```cpp
#include<bits/stdc++.h>
using namespace std;
struct point//结构体
{
    int x,y,step;
};
int n,m,f,e,sx,sy,ex,ey,step2=1000000;
char tmp[1000];
int g[100][100];//地图
point q[10000],u,v,tg;
bool used[100][100];//表示走过的地方
int main()
{
    memset(used,0,sizeof(used));//清零
    memset(g,0,sizeof(g));
    scanf("%d %d %d %d %d %d",&n,&m,&sx,&sy,&ex,&ey);
    g[sx][sy]=2,u.x=sx,u.y=sy,u.step=0,used[sx][sy]=1,q[f=e=1]=u;
    g[ex][ey]=3;tg.x=ex,tg.y=ey;
            
    gets(tmp);
    for(int i=1;i<=n;i++)
    {
        char c;
        for(int j=1;j<=m;j++)
    {
        scanf("%c",&c);//读入字符
        if(c=='.')g[i][j]=1;
        else if(c=='#')g[i][j]=0;
    }
    gets(tmp);
    }
    bool flag=0;
    while(f<=e)
    {
        u=q[f++];
        v.x=u.x+1,v.y=u.y,v.step=u.step+1;
        if(g[v.x][v.y]!=0&&used[v.x][v.y]==0&&v.step<=step2)//向四周搜
        {
            q[++e]=v,used[v.x][v.y]=1;
            if(v.x==tg.x&&v.y==tg.y)
            {
                flag=1;
                step2=min(v.step,step2);//取较小的
                break;
            }
        }
        v.x=u.x-1,v.y=u.y,v.step=u.step+1;
        if(g[v.x][v.y]!=0&&used[v.x][v.y]==0&&v.step<=step2)
        {
            q[++e]=v,used[v.x][v.y]=1;
            if(v.x==tg.x&&v.y==tg.y)
            {
                flag=1;
                step2=min(v.step,step2);
                break;
            }
        }
        v.x=u.x,v.y=u.y+1,v.step=u.step+1;
        if(g[v.x][v.y]!=0&&used[v.x][v.y]==0&&v.step<=step2)
        {
            q[++e]=v,used[v.x][v.y]=1;
            if(v.x==tg.x&&v.y==tg.y)
            {
                flag=1;
                step2=min(v.step,step2);
                break;
            }
        }
        v.x=u.x,v.y=u.y-1,v.step=u.step+1;
        if(g[v.x][v.y]!=0&&used[v.x][v.y]==0&&v.step<=step2)
        {
            q[++e]=v,used[v.x][v.y]=1;
            if(v.x==tg.x&&v.y==tg.y)
            {
                flag=1;
                step2=min(v.step,step2);
                break;
            }
        }
        }
        if(flag==1)cout<<step2<<endl;//输出
    return 0;
}
```

---

## 作者：infinities (赞：0)

一道dfs+bfs板子题，和[P3111](https://www.luogu.org/problem/P3111)，[P1747](https://www.luogu.org/problem/P1747)，[P1331](https://www.luogu.org/problem/P1331)，[P1135](https://www.luogu.org/problem/P1135)都差不多（5倍经验拿走不谢），套一下就好，由于dfs（depth-first-search）比较简单易懂,~~又是本人最熟练和熟悉的算法之一~~，所以推荐大家使用（95%以上的bfs题都可以用dfs+记忆化解决）

思路：

1. 从起点开始搜索，并记录步数，其中，如果现在的步数已经大于当前格子的到达步数的最小值，那么，剪枝，如果已经到达终点，剪枝

2. 输出到达终点的最少步数即可

~~大佬请自行忽略下两行的内容~~

另：使用cstring库里的memset函数可海星，作用是将整个数组全部赋初值，但是要注意memset里的16进制很奇怪，0x3f就是$10^9$左右的一个大数，所以使用方法就是：
```cpp
memset(a,0x3f,sizeof(a));//a为要操作的数组名
```

code:

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n,m,sx,sy,xx,yy,vis[101][101],r,c;
char a[101][101];
int xxx[6]={0,0,-1,1,0,0};
int yyy[6]={0,1,0,0,-1,0};
void dfs(int x,int y,int step){//用无返回值的void正合适
    if(step>=vis[x][y])return;//类似于记忆化的剪枝
    vis[x][y]=step;//更新
  //if(x==xx&&y==yy)return;
    for(int i=1;i<=5;i++){
        r=x+xxx[i],c=y+yyy[i];
        if(r<1||c<1||r>n||c>m||a[r][c]=='#')continue;//这是最关键的第三句，作用接近于剪枝
        dfs(r,c,step+1);
    }
}
int main(){
    memset(vis,0,sizeof(vis));//C++大法好
    cin>>n>>m>>sx>>sy>>xx>>yy;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    dfs(sx,sy,0);
    cout<<vis[xx][yy]<<"\n";//输出
    return 0;//exit(0);
}//做了几乎相当于空气的防伪>_<
```



---

