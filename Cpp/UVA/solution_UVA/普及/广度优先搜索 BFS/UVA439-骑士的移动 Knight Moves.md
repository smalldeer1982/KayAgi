# 骑士的移动 Knight Moves

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=380

[PDF](https://uva.onlinejudge.org/external/4/p439.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA439/49281f2a839995de267463a506fc7b04652bcf4a.png)

## 样例 #1

### 输入

```
e2 e4
a1 b2
b2 c3
a1 h8
a1 h7
h8 a1
b1 c3
f6 f6```

### 输出

```
To get from e2 to e4 takes 2 knight moves.
To get from a1 to b2 takes 4 knight moves.
To get from b2 to c3 takes 2 knight moves.
To get from a1 to h8 takes 6 knight moves.
To get from a1 to h7 takes 5 knight moves.
To get from h8 to a1 takes 6 knight moves.
To get from b1 to c3 takes 1 knight moves.
To get from f6 to f6 takes 0 knight moves.```

# 题解

## 作者：Yae_Sakura (赞：15)

1.   题意：

 给定起始状态和结束状态，以及状态转换的规则，求最少的状态转换次数  

2. 解决：

 一般情况下，BFS 第一次遇到末状态时的深度即为“最少次数”，所以使用 BFS 求解

3.  优化：

 一般的 BFS 通常是从某一状态开始搜索，某节点第一次达到结束状态时停止，属于“单向”搜索（单调向某一方向拓展）  

 但在本题中给出了固定的起始状态和结束状态，这时可以使用 “ 双向BFS ” 进行优化，顾名思义——即从两个状态开始搜索，这时当两个搜索树第一次出现节点重合就得到了 “ 最少次数 ” 。

4. 解释：

 ① 搜索的停止：从起始状态和结束状态拓展出来的搜索树第一次出现节点重合时，起始点和结束点之间就有一条路径相连接，即求得解。
 
 ② 起到优化作用的原因：如果把 BFS 搜索树都看成一棵二叉树，那么高度为h的二叉树至多有$2^{h}$-$1$个节点。
 
 因为 “ 双向BFS ” 的两棵搜索树的节点必然会在$\frac{h}{2}$+$1$的深度重合，所以树的高度至多为$\frac{h}{2}$+$1$，则拓展节点数至多$2^{\frac{h}{2}+1}$+$2^{\frac{h}{2}}$-$3$。
 
 相比于前者$2^{h}$$-$2$，拓展节点数更少。

5.  代码实现：   

   通常使用两个队列分别储存从两个状态开始的搜索状态，用vis数组判断是否重合，用dis数组储存每个节点的深度，遇到解的时候直接调用dis数组以输出。  
   
   而搜索方式一般是：每次都选择节点个数少的那个队列拓展



```cpp
#include<queue>
//STL队列，更方便操作，不至于混淆指针
#include<cstdio>
#include<cstring>
using namespace std;
const int N=10;
char a[N],b[N];
int dx[N]={-1,-2,-2,-1,1,2,2,1};
int dy[N]={-2,-1,1,2,2,1,-1,-2};
struct horse{
    int x,y,t;//节点坐标、深度
}st,ed,tmp;
//st起始状态 ed结束状态 tmp临时转换状态
int dis[N][N],vis[N][N];
//dis节点的深度 vis节点的访问情况
inline int bfs()
{
    if(st.x==ed.x&&st.y==ed.y) return 0;
    queue<horse> q1;
    queue<horse> q2;
    vis[st.x][st.y]=1;
    vis[ed.x][ed.y]=2;
    //起始状态访问的节点记为1，结束状态的记为2
    //当某一状态的队列拓展节点时
    //若vis为0，则标记为自己队列的
    //若已被另一状态的队列标记，则意味着出现重合 
    q1.push(st);
    q2.push(ed);
    int fx,fy,xx,yy;
    while(true){
        if(q1.size()<q2.size()){
        //q.size() 该队列中节点的个数
            fx=q1.front().x;
            fy=q1.front().y;
            //当前q1的节点少，取q1的节点
            for(int i=0;i<8;i++){
                xx=fx+dx[i];yy=fy+dy[i];
                if(xx<1||xx>8||yy<1||yy>8) continue;
                if(vis[xx][yy]==0){
                    tmp.t=q1.front().t+1;
                    tmp.x=xx;tmp.y=yy;
                    q1.push(tmp);
                    vis[xx][yy]=1;
                    //没访问过，标记1表示q1
                    dis[xx][yy]=tmp.t;
                }
                else if(vis[xx][yy]==2)
                return dis[xx][yy]+q1.front().t+1;
                //q2曾访问过这，q1目前访问这，即重合
            }q1.pop();
        }
        else{
            fx=q2.front().x;
            fy=q2.front().y;
            //同样的，这里q2的节点少，取q2的队首
            for(int i=0;i<8;i++){
                xx=fx+dx[i];yy=fy+dy[i];
                if(xx<1||xx>8||yy<1||yy>8) continue;
                if(vis[xx][yy]==0){
                    tmp.t=q2.front().t+1;
                    tmp.x=xx;tmp.y=yy;
                    q2.push(tmp);
                    vis[xx][yy]=2;
                    dis[xx][yy]=tmp.t;
                }
                else if(vis[xx][yy]==1)
                return dis[xx][yy]+q2.front().t+1;
            }q2.pop();
        }
    }
}
int main(void)
{
    while(scanf("%s%s",a,b)!=EOF){
    	//"!=EOF"指输入不为空
        st.x=a[0]-'a'+1;st.y=a[1]-'0';
        ed.x=b[0]-'a'+1;ed.y=b[1]-'0';
        st.t=ed.t=0;
        memset(vis,0,sizeof(vis));
        memset(dis,0,sizeof(dis));
        //多组数据需清空数组
        printf("To get from %c%c to %c%c takes %d knight moves.\n",a[0],a[1],b[0],b[1],bfs());
    }
    return 0;
}
```

双端BFS系列题目：
[八数码难题](https://www.luogu.org/problemnew/show/P1379)，[魔板](https://www.luogu.org/problemnew/show/P2730)

（~~才不会告诉你会判重就能连A这两道蓝题~~）

---

## 作者：封禁用户 (赞：9)

### 前言

最近板子题刷多了……

[博客园食用qwq](https://www.cnblogs.com/CM-0728/p/13544509.html)

### 题意

一个 $8\times 8$ 的棋盘，问马从起点到终点的最短步数为多少。

### $\sf Solution$

要求最短路径嘛，显然 bfs 更优。

#### 读入

这个读入处理有点麻烦……

我们可以把表示行的字符转化为数字，即 `ch-'a'+1` 。

#### 搜索

将起点入队，每次获取队首元素并相应扩展，记录步数。

搜到的第一条路径就是最短路径，直接输出 step 。


### $\sf Code$
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
using namespace std;
struct node
{
	int x,y,step;
} o;
queue<node>q;
int dx[8]={-1,1,-1,1,-2,2,-2,2},
	dy[8]={-2,2,2,-2,-1,1,1,-1};//马的八个方向
bool vis[10][10];//标记数组
int sx,sy,ex,ey,xx,yy;
char ch;
string qx,qy;
int main()
{
	while(cin>>qx&&qx[0]!=EOF)
	{
		cin>>qy;
		sx=qx[0]-'a'+1,sy=qx[1]-'0';
		ex=qy[0]-'a'+1,ey=qy[1]-'0';//读入
		memset(vis,false,sizeof(vis));//初始化
		vis[sx][sy]=true;
		q.push((node){sx,sy,0});
		while(!q.empty())
		{
			o=q.front(),q.pop();
			if(o.x==ex&&o.y==ey)//找到路径
			{
				cout<<"To get from "<<qx<<" to "<<qy<<" takes "<<o.step<<" knight moves.\n";
				break;
			}
			for(int i=0;i<8;++i)//扩展
			{
				xx=o.x+dx[i],yy=o.y+dy[i];
				if(xx<=0||yy<=0||xx>8||yy>8)
					continue;
				if(vis[xx][yy])
					continue;//不符合要求的情况都排除
				vis[xx][yy]=true,q.push((node){xx,yy,o.step+1});
			}
		}
		while(!q.empty())
			q.pop();//别忘记清空队列
	}
	return 0;
}
```

---

## 作者：Walker_V (赞：8)

# UVA439 骑士的移动

之所以这道题我要写题解，是因为解题的过程中我采用了多种方法（不严谨的说，基本写完了搜索里的所有技巧）——BFS，IDA\* ，A\*，双向DFS。

这个过程很值得品味参考，于我来说也是一次不可多得的学习。

### BFS

这道题的BFS思路是比较显然的，代码实现上也不算特别难。

```cpp
#include<bits/stdc++.h>
#define Debug  printf("OK\n");

int f[10][10],dx[9]={0,-1,-2,-2,-1,1,2,2,1},dy[9]={0,2,1,-1,-2,-2,-1,1,2};
char op[5],ed[5];

struct node {
	int x,y;
}s,t;

namespace WalkerV {
	void Init() {
		memset(f,0,sizeof(f));
		return;
	}
	void Solve() {
		s=(node){op[0]-'a'+1,op[1]-'0'},t=(node){ed[0]-'a'+1,ed[1]-'0'};
		std::queue<node> q;
		q.push(s),f[s.x][s.y]=0;
		while(q.size()>0) {
			node k=q.front();
			q.pop();
			if(k.x==t.x&&k.y==t.y) {
				return;
			}
			for(int i=1;i<=8;i++) {
				if(k.x+dx[i]>=1&&k.x+dx[i]<=8&&k.y+dy[i]>=1&&k.y+dy[i]<=8&&!f[k.x+dx[i]][k.y+dy[i]]) {
					f[k.x+dx[i]][k.y+dy[i]]=f[k.x][k.y]+1;
					q.push((node){k.x+dx[i],k.y+dy[i]});
				}
			}
		}
		return;
	}

	void Print() {
		printf("To get from %s to %s takes %d knight moves.\n",op,ed,f[t.x][t.y]);
		memset(op,0,sizeof(op));
		memset(ed,0,sizeof(ed));
		return;
	}
}

int main()
{
	while(std::cin>>op>>ed) {
		WalkerV::Init();
		WalkerV::Solve();
		WalkerV::Print();
	}
	return 0;
}
```

### IDA\*

然后便是IDA\*。

如果你问我为什么不先写A\*，因为这份代码的重点是迭代加深，也就是ID(Iterative Deepening)。但单打一份迭代加深的DFS意义不大，所以就选择用IDA\*。而且从各种角度来说，IDA\*都比A\*要优秀一些。

但是这份代码应该说是几份代码我调得最痛苦的一份（大概前前后后修了三四个小时左右），最后的关键错误还是落在了估价函数上。

有必要说一下估价函数的设计：因为是马在棋盘上的移动，所以考虑曼哈顿距离。我们知道马每次移动的曼和顿距离为$3$，所以乐观估计应当是当前位置到终点的曼哈顿距离除以$3$并向上取整。

```cpp
#include<bits/stdc++.h>

int max_dep;
int f[10][10],dx[9]={0,-1,-2,-2,-1,1,2,2,1},dy[9]={0,2,1,-1,-2,-2,-1,1,2};
char op[5],ed[5];

struct node {
	int x,y;
}s,t;


namespace WalkerV {
	void Init() {
		max_dep=0;
		memset(f,0,sizeof(f));
		return;
	}

	double Estimate_Function(int x1,int y1,int x2,int y2) {
		return std::ceil((std::abs(x1-x2)+std::abs(y1-y2))/3.0);
	}

	bool IDDFS(int x,int y,int dep) {
		if(dep==max_dep) {
			if(x==t.x&&y==t.y) {
				f[x][y]=dep;
				return true;
			}
			else {
				return false;
			}
		}
		//printf("x:%d y:%d g(x):%d f(x):%.1f\n",x,y,dep,Estimate_Function(x,y,t.x,t.y));
		for(int i=1;i<=8;i++) {
			if(x+dx[i]>=1&&x+dx[i]<=8&&y+dy[i]>=1&&y+dy[i]<=8&&!f[x+dx[i]][y+dy[i]]) {
				//printf("move to %d %d, g:%d f:%.1f max_dep:%d\n",x+dx[i],y+dy[i],dep+1,Estimate_Function(x+dx[i],y+dy[i],t.x,t.y),max_dep);
				if(dep+1+Estimate_Function(x+dx[i],y+dy[i],t.x,t.y)>max_dep) { //g(x):dep+1 f(x):ceil(M_Dis/3)
					//printf("cut\n");
					continue;
				}
				if(IDDFS(x+dx[i],y+dy[i],dep+1)) {
					return true;
				}
			}
		}
		return false;
	}

	void Solve() {
		s=(node){op[0]-'a'+1,op[1]-'0'},t=(node){ed[0]-'a'+1,ed[1]-'0'};
		while(!IDDFS(s.x,s.y,0)) {
			memset(f,0,sizeof(f));
			max_dep++;
			//printf("max_dep:%d\n",max_dep);
		}
		return;
	}

	void Print() {
		printf("To get from %s to %s takes %d knight moves.\n",op,ed,f[t.x][t.y]);
		memset(op,0,sizeof(op));
		memset(ed,0,sizeof(ed));
		return;
	}

}

int main()
{
	while(std::cin>>op>>ed) {
		WalkerV::Init();
		WalkerV::Solve();
		WalkerV::Print();
	}
	return 0;
}
```

### A\*

在有了BFS和IDA\*的基础上，A\*就显得非常容易了。

估价函数的设计与IDA\*是一致的。

```cpp
#include<bits/stdc++.h>

int f[10][10],dx[9]={0,-1,-2,-2,-1,1,2,2,1},dy[9]={0,2,1,-1,-2,-2,-1,1,2};
char op[5],ed[5];

struct node {
	int x,y;
	double est;
	friend bool operator < (node a,node b) {
		return a.est>b.est;
	}
}s,t;

namespace WalkerV {
	void Init() {
		memset(f,0,sizeof(f));
		return;
	}
	
	double Estimate_Function(int x,int y) {
		return std::ceil((std::abs(x-t.x)+std::abs(y-t.y))/3.0);
	}

	void Solve() {
		s=(node){op[0]-'a'+1,op[1]-'0',0},t=(node){ed[0]-'a'+1,ed[1]-'0',0};
		s.est=Estimate_Function(s.x,s.y);
		std::priority_queue<node> q;
		q.push(s),f[s.x][s.y]=0;
		while(q.size()) {
			node k=q.top();
			q.pop();
			if(k.x==t.x&&k.y==t.y) {
				return;
			}
			for(int i=1;i<=8;i++) {
				if(k.x+dx[i]>=1&&k.x+dx[i]<=8&&k.y+dy[i]>=1&&k.y+dy[i]<=8&&!f[k.x+dx[i]][k.y+dy[i]]) {
					f[k.x+dx[i]][k.y+dy[i]]=f[k.x][k.y]+1;
					q.push((node){k.x+dx[i],k.y+dy[i],f[k.x+dx[i]][k.y+dy[i]]+Estimate_Function(k.x+dx[i],k.y+dy[i])});
				}
			}
		}
		return;
	}

	void Print() {
		printf("To get from %s to %s takes %d knight moves.\n",op,ed,f[t.x][t.y]);
		memset(op,0,sizeof(op));
		memset(ed,0,sizeof(ed));
		return;
	}
}

int main()
{
	while(std::cin>>op>>ed) {
		WalkerV::Init();
		WalkerV::Solve();
		WalkerV::Print();
	}
	return 0;
}
```

### 双向BFS

对于这题，由于我们已经知道搜索的初态和末态，所以既可以从初态搜到末态，也可以从末态搜到初态。

在此基础上，双向BFS的思路也就呼之欲出了——从初态和末态同时往中间搜索（具体实现应当是正反各搜一轮）。

由于我们使用的是BFS，所以在轮流搜索的时候但凡有一个状态被两边都搜索到了（也就是说第一个被两边都搜索到的状态），那么这个状态到初态和末态的路径和就是答案（正确性显然）。

此外，在代码中需要注意的有如下两点：

* 末态的初值应赋为$1$，因为在实际的移动中，是需要$1$步才能走到终点的。

* 起点和终点重合需要特判，不然程序就会处理为需要$2$步才能到（反复横跳一次）。

~~说句闲话，其实中间两个队列的实现那里，如果用**typedef**写会更好看一些，但是可读性会大大降低（逃~~

```cpp
#include<bits/stdc++.h>

int ans;
int f1[10][10],f2[10][10],dx[9]={0,-1,-2,-2,-1,1,2,2,1},dy[9]={0,2,1,-1,-2,-2,-1,1,2};
char op[5],ed[5];

struct node {
	int x,y;
}s,t;

namespace WalkerV {
	void Init() {
		memset(f1,0,sizeof(f1));
		memset(f2,0,sizeof(f2));
		return;
	}

	void Solve() {
		s=(node){op[0]-'a'+1,op[1]-'0'},t=(node){ed[0]-'a'+1,ed[1]-'0'};
		if(s.x==t.x&&s.y==t.y) {
			ans=0;
			return;
		}
		std::queue<node> q1,q2;
		q1.push(s),f1[s.x][s.y]=0;
		q2.push(t),f2[t.x][t.y]=1;
		while(q1.size()||q2.size()) {
			bool flag;
			node k;
			if(q1.size()<=q2.size()) { //edit q1
				k=q1.front();
				q1.pop();
				flag=true;
			}
			else { //edit q2
				k=q2.front();
				q2.pop();
				flag=false;
			}
			for(int i=1;i<=8;i++) {
				if(k.x+dx[i]>=1&&k.x+dx[i]<=8&&k.y+dy[i]>=1&&k.y+dy[i]<=8) {
					switch(flag) {
						case true:
							if(f2[k.x+dx[i]][k.y+dy[i]]) {
								ans=f1[k.x][k.y]+f2[k.x+dx[i]][k.y+dy[i]];
								return;
							}
							f1[k.x+dx[i]][k.y+dy[i]]=f1[k.x][k.y]+1;
							q1.push((node){k.x+dx[i],k.y+dy[i]});
							break;
						case false:
							if(f1[k.x+dx[i]][k.y+dy[i]]) {
								ans=f2[k.x][k.y]+f1[k.x+dx[i]][k.y+dy[i]];
								return;
							}
							f2[k.x+dx[i]][k.y+dy[i]]=f2[k.x][k.y]+1;
							q2.push((node){k.x+dx[i],k.y+dy[i]});
							break;
					}				
				}
			}
		}
		return;
	}

	void Print() {
		printf("To get from %s to %s takes %d knight moves.\n",op,ed,ans);
		memset(op,0,sizeof(op));
		memset(ed,0,sizeof(ed));
		return;
	}
}

int main()
{
	while(std::cin>>op>>ed) {
		WalkerV::Init();
		WalkerV::Solve();
		WalkerV::Print();
	}
	return 0;
}
```

---

### 说点别的

这次这道题码下来，还算是收获颇丰。谁会想到，一个学了两年多OI的人，直到这道题才算是摸透了上面四种算法（包括BFS）。

此外，在写代码的时候，感觉到(ID)A\*是真正优秀的算法。这不仅体现在它的运行时间上，而是说这种算法是最贴近人类行为的。作为人类，我们在解决问题中面临多种方式时，一定会略作估计并选取最优的方式进行尝试。可能这也是启发式算法被广泛运用到人工智能里的原因，毕竟我们人类定义的人工智能就是与人类智能所相似的机器。

---

## 作者：xbx787 (赞：7)

题目意思就是：给你一个国际象棋的棋盘，求一个马从a点走到b点的最小距离是多少。

这道题许多巨佬都用的是BFS，但是本蒟蒻认为这道题用 $A*$ 算法效率更高。

那么我们先介绍一下什么是 $A*$ 算法

- $A*$ 算法

是一种启发式搜索，启发式搜索就是在搜索时对每一个位置进行评估，得到最好的位置，再从这个位置进行搜索直到目标。这样可以省略大量无谓的搜索路径，提高了效率。
    
其实大家熟知的BFS算法就是 $A*$ 算法的一种特殊情况，因为BFS总是将当前节点能到达的所有节点全部存入队列中，因此不存在启发性。BFS的速度虽然很快，但是它搜到的不一定是最佳路径。
    
在这里我所说的启发性大家可以理解为是搜索的方向性，即搜索方向总是趋向于终点，而不是盲目搜索。
    
$A*$ 算法的另一种特例就是Dijikstra算法，因为它在搜索时虽然能找到最佳路径，但是在时间上就不如BFS快。$A*$则集两家之大成，既能快速搜索，又能得出最佳路径。

$A*$ 算法的特点： $A*$ 算法在理论上是时间最优的，但是也有缺点：它的空间增长是指数级别的。

$IDA*$ 算法：即迭代加深 $A*$ 算法，可以有效的解决 $A*$ 空间增长带来的问题，甚至可以不用到优先级队列。~~因为我不会~~ 所以不再赘述。

### 重要公式：$F=G+H$

其中 $F$ 为我们的启发式函数，$G$ 为从起点移动到当前方格的花费，$H$ 为估价函数。

![](https://s2.ax1x.com/2019/10/19/KnrNZD.png)

此图中，橙色为当前节点，绿色为起点，红色为终点，红箭头为 $G$ ，紫箭头为 $H$ 。

- 估价函数：

即为从当前节点移动到目标节点的预估费用：这个估计就是启发式的。在寻路问题和迷宫问题中，我们通常用曼哈顿（manhattan）估价函数预估费用。这一估价值我们通常用字母 $H$ 表示。

$H$ 值可以用不同的方法估算。我们这里使用的方法被称为曼哈顿方法，它计算从当前格到目标格之间的曼哈顿距离乘以 $10$ 。

需要注意的是，无论在当前格到终点的路径上是否有障碍物（蓝色格），我们都选择忽视。这是对剩余距离的一个估算，而非实际值，这也是这一方法被称为启发式的原因。

另外，因为我们寻找的是最短路，那么估价函数应取最小值，所以我们就要用优先队列来维护。当然不要忘了重载自定义节点的比较操作符。

掌握了上面的基础知识，我们就可以开始搜索了！

1. 首先，将起点压入优先队列，寻找起点周围所有可到达的方格，并把他们加入队列。将所有这些方格的“父方格”设为起点。

2. 从队列中弹出起点，并检查所有在队列中的节点，选取 $F$ 值最小的进行搜索。（详见代码）

3. 重复以上过程直到终点被加入队列。

在这一过程中，我们记录的父节点就可以成为寻找路径的依据（尽管本题中不需要）。

更详尽的搜索过程请看[这里](https://blog.csdn.net/cug_wx/article/details/17760061)

最后上我丑陋的代码：

```cpp
#include <bits/stdc++.h>
#define x1 xxx1
#define y1 yyy1 //防止神奇变量干扰编译 
#define x2 xxx2
#define y2 yyy2
using namespace std;
const int dir[8][2]={{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{-1,2},{1,-2},{-1,-2}};//走位数组 
int x1,y1,x2,y2,ans;
bool vis[8][8];
struct node{
	int x,y,step,g,h,f;
	bool operator < (const node & u)const{ //为优先队列重载运算符 
		return f>u.f;
	}
}k;
priority_queue<node>q;
bool check(node u){ //判是否出界 
	if(u.x<0 || u.y<0 || u.x>=8 || u.y>=8)return 0;
	return 1;	
}
int gujia(node u){ //估价函数 
	return (abs(u.x-x2)+abs(u.y-y2))*10;	
}
void astar(){ //A*算法 
	while(!q.empty()){
		node u=q.top(); q.pop();
		vis[u.x][u.y]=1;
		if(u.x==x2 && u.y==y2){
			ans=u.step; break;	
		}
		for (int i=0;i<8;i++){
			node v;
			v.x=u.x+dir[i][0],v.y=u.y+dir[i][1];
			if(check(v) && !vis[v.x][v.y]){ //计算当前点的位置与函数 
				v.g=u.g+23;
           //取23的原因是骑士每走一步都是2*1的，23=根号5乘以十再向上取整
				v.h=gujia(v);
				v.f=v.g+v.h;
				v.step=u.step+1;
				q.push(v);
			}
		}
	}
}
int main(){
	char c[10];
	while(gets(c)){
		x1=c[0]-'a',y1=c[1]-'1';
		x2=c[3]-'a',y2=c[4]-'1';
		memset(vis,0,sizeof vis);
		k.x=x1,k.y=y1,k.g=k.step=0,k.h=gujia(k),k.f=k.g+k.h;
		while(!q.empty())q.pop(); //多组数据须清空队列 
		q.push(k);
		astar();
		printf("To get from %c%c to %c%c takes %d knight moves.\n",c[0],c[1],c[3],c[4],ans);
	}
	return 0;
}

```
RP++ 希望不要初赛AFO

谢谢大家！！

---

## 作者：CreeperLordVader (赞：5)

常规BFS，输入我用的是数组
但是由于回车也会被读入所以被坑了好几次
在别人的帮助下才知道了这个问题
加个星号就好了
星号表示读入但不用于赋值（算是长姿势）
```cpp
#include<bits/stdc++.h>
using namespace std;
char k[6];
bool b[9][9];
struct node 
{
	int x,y,step=0;
}start,fa;
queue<node>q;
int endx,endy;
int dx[]={0,-1,1,2,2,-1,1,-2,-2};
int dy[]={0,-2,2,-1,1,2,-2,-1,1};
int main()
{
	while(scanf("%c%c%c%c%c%*c",&k[1],&k[2],&k[3],&k[4],&k[5])==5)
	{
		for(int i=1;i<=8;i++)
		for(int j=1;j<=8;j++)
		{
			b[i][j]=0;
		}
		start.x=k[1]-96;
		start.y=k[2]-48;
		endx=k[4]-96;
		endy=k[5]-48;
		//cout<<"f*ck"<<endl;
		b[start.x][start.y]=1;
		q.push(start);
		while(!q.empty())
		{
			fa=q.front();
			q.pop();
		    
			if(fa.x==endx&&fa.y==endy)
			{
				while(!q.empty())
				q.pop();
				printf("To get from %c%c to %c%c takes %d knight moves.\n",k[1],k[2],k[4],k[5],fa.step);
				break;
			}
			for(int i=1;i<=8;i++)
			{
				int nx=fa.x+dx[i];
				int ny=fa.y+dy[i];
				if(nx>0&&ny>0&&nx<=8&&ny<=8&&!b[nx][ny])
				{
					node son;
					son.x=nx;
					son.y=ny;
					son.step=fa.step+1;
					b[nx][ny]=1;
					q.push(son);
				}
			}
		}
		for(int i=1;i<=5;i++)
		{
			k[i]=0;
		}
	}
}
```

---

## 作者：meyi (赞：3)

这题就是一个bfs板子题，~~随手打个bfs就A了。~~

思路：（自己百度“宽度优先搜索”）

已有题解已经提供了用stl的queue的方法，这里再提供一种手写队列的方法。

上代码：
```cpp
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
struct node{
    int x,y,s;
    //x是横轴位置，y是纵轴位置，s是已走步数
    node(int a=0,int b=0,int c=0):x(a),y(b),s(c){}
    //构造函数
}q[101];
char m[3],n[3];
const int dx[8]={-2,-2,-1,-1,1,1,2,2},dy[8]={-1,1,-2,2,-2,2,-1,1};
int ex,ey,sx,sy;
bool f[11][11];
inline int bfs(){
    memset(f,false,sizeof f);
    //每次调用bfs函数时需要把判重数组f的所有元素赋值为0
    int h=0,t=0;
    //h是头指针，t是尾指针
    q[t++]=node(sx,sy,0);
    f[sx][sy]=true;
    while(h<t){
        node k=q[h++];
        if(k.x==ex&&k.y==ey)return k.s;
        for(register int i=0;i<8;++i){
            register int mx=k.x+dx[i],my=k.y+dy[i];
            if(mx>0&&mx<9&&my>0&&my<9&&!f[mx][my])f[mx][my]=true,q[t++]=node(mx,my,k.s+1);
        }
    }
    //bfs板子，不多解释
}
main(){
    while(~scanf("%s %s",n,m)){
        sx=n[0]-'a'+1,sy=n[1]^48,ex=m[0]-'a'+1,ey=m[1]^48;
        //输入，由于数据的特殊性选用字符串
        printf("To get from %s to %s takes %d knight moves.\n",n,m,bfs());
        //按照题目要求输出
    }
}
```

---

## 作者：xmdzz (赞：2)





| 不能走 |x-1,y-2  | 不能走 | x+1,y-2 | 不能走 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| x-2,y-1 |  不能走| 不能走 |不能走  | x+2,y-1 |
|不能走  | 不能走 |马 x,y | 不能走 |  不能走|
|  x-2,y+1|不能走  |  不能走|不能走  |  x+2,y+1|
|  不能走| x-1,y+2 | 不能走 |  x+1,y+2|  不能走|


1.采用bfs广度优先搜索,第一次搜到的目标点就是最短的.

2.广度优先时遍历时,遍历的不是邻接点,而是国际象棋中马可以走的八个方向.

3.为了方便记忆不用一维数组存储点的结构体,二是二维数组存储,会开心很多.

```cpp
//#pragma warning(disable:4996)
# include<iostream>
# include<queue>
# include<string>
# include<cstring>
using namespace std;
//暂存开始点到结束点
string A, B;
//暂存开始点到结束点的下标
int ax, ay, bx, by;
//定义了一个偏移量数组
int dir[8][2] = { {-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1} };
bool flag = 0;
//8*8的棋盘格,从1开始记录
typedef struct V {
	int x, y;
	bool vis;
	//cnt是所需步数
	int cnt;
}V;
V varr[9][9];
queue<V> Q;
void bfs(V v) {
	if (v.x == bx && v.y == by) {
		flag = 1;
		return;
	}
	V u;
	v.vis = 1;
	//将v入队
	Q.push(v);
	//如果队列不为空
	while (!Q.empty()) {
		u = Q.front();
		Q.pop();
		//从8个方向开始搜索,此处相当于邻接点
		for (int i = 0; i < 8; i++)
		{
			//搜索时依次给当前坐标添加偏移量
			int x2 = u.x + dir[i][0];
			int y2 = u.y + dir[i][1];
			//如果没有越界,并且没被访问过,并且还没有找到,步数加1
			if (x2 >= 1 && x2 <= 8 && y2 >= 1 && y2 <= 8 && !varr[x2][y2].vis && !flag)
			{
				Q.push(varr[x2][y2]);
				varr[x2][y2].vis = 1;
				//注意这里不能直接写u.cnt哦!u只是一个临时变量
				varr[x2][y2].cnt = varr[u.x][u.y].cnt + 1;
				if (x2 == bx && y2 == by) {
					flag = 1;
					return;
				}
			}
		}
	}
}
int main()
{
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++)
		{
			varr[i][j].x = i;
			varr[i][j].y = j;
		}
	}
	while (cin >> A >> B) {
		//flag归0
		flag = 0;
		//队列也要清空
		while (!Q.empty()) {
			Q.pop();
		}
		//清除点记录
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++)
			{
				varr[i][j].vis = 0;
				varr[i][j].cnt = 0;
			}
		}
		//字符转成坐标,a对应1
		ax = A[0] - 'a' + 1;
		ay = A[1] - '0';
		bx = B[0] - 'a' + 1;
		by = B[1] - '0';
		//从a处开始广度优先遍历,记录找到b时后的步数.
		bfs(varr[ax][ay]);

		//按格式输出步数
		cout << "To get from " << A << " to " << B << " takes " << varr[bx][by].cnt << " knight moves."<<endl;
	}
	//system("pause");
	return 0;//返回0
}
```


---

## 作者：zilingheimei (赞：1)

蒟蒻又来写题解了.

先看题目[UVA439 骑士的移动 Knight Moves](https://www.luogu.com.cn/problem/UVA439)
- 输入8*8的国际象棋棋盘上的2个格子，求马至少多少步从起点跳到终点。

熟悉的题目.


这题就是走马求最小步数.

注意这些点.
 
------------

 
**第一**: 题目让我们多个输入.

- 可以用while输入然后直接bfs：

```cpp
while(cin>>c1>>c2>>c3>>c4){
	bfs(c1,c2,c3,c4);
}
```

**第二**: 因为是用字母表示行所以要转换一下.

- 将字符减零加一 

```cpp
//函数进来时改了个名称
sx=c1-'a'+1;
sy=c2-'0';
fx=c3-'a'+1;
fy=c4-'0';
```


**第三**: 起点要特判.

- bfs开头先判断一下,就看看起点是不是与终点重合,如果重合就直接输出步数0:

```cpp
if(sx==fx&&sy==fy){
	cout<<"To get from "<<c1<<c2<<" to "<<c3<<c4<<" takes "<<0<<" knight moves."<<endl;
	return ;//因为在函数中
}
```

------------

然后就可以开始宽搜了.

- 1.先定个结构体还有行走的数组：

结构体里面包含:

1. 当前x位置.

2. 当前y位置.

3. 当前步数.

如下
```cpp
struct cxk{
	int x,y,step;
}q[1001000];//q就代表队列
int dx[8]={-2,-2,-1,-1,1,1,2,2};
int dy[8]={1,-1,-2,2,-2,2,-1,1};
```
- 2.然后初始化一下把q[1]变成起点：

**先将队列初始化.**

**然后记录起点*.*

```cpp
int f=1,t=1;
q[f].x=sx;
q[f].y=sy;
q[f].step=0;//实际可以不用
```

- 3.接下来是宽搜：

**先定义个当前步数时的各个变量为u下一步为v,方便后面直接赋值.**

**然后8个方向行走,下一步的步数加一.**

**看看下一步是不是终点,因为宽搜同时进行,先搜到的绝对最优解，直接输出.**

**不是终点就入队,因为前面定义了v，队列可以直接等于它**
```cpp
while(f<=t){
		cxk u,v;//定义个当前步数时的各个变量为u下一步为v
		u=q[f++];
		for(int i=0;i<8;i++){
			v.x=u.x+dx[i];
			v.y=u.y+dy[i];//移动
			v.step=u.step+1;
			if(v.x==fx&&v.y==fy){
				cout<<"To get from "<<c1<<c2<<" to "<<c3<<c4<<" takes "<<v.step<<" knight moves."<<endl;//注意输出别漏空格
				return ;
			}//搜到了
         //因为只要这个先搜到就说明是最优解
			else if(v.x>=1&&v.x<=8&&v.y>=1&&v.y<=8){
				q[++t]=v;//结构体可以直接赋
			}//入队
		}
	}
```

- 然后这题代码就出来了.

**下面是完整代码.**


```cpp
#include<bits/stdc++.h>
using namespace std;
struct cxk{
	int x,y,step;
}q[1001000];//q就代表队列
int sx,sy,fx,fy;
char c1,c2,c3,c4;
int dx[8]={-2,-2,-1,-1,1,1,2,2};
int dy[8]={1,-1,-2,2,-2,2,-1,1};
void bfs(char c1,char c2,char c3,char c4){
//函数进来时改了个名称
	sx=c1-'a'+1;
	sy=c2-'0';
	fx=c3-'a'+1;
	fy=c4-'0';//将起点终点化为数字
	int f=1,t=1;
	q[f].x=sx;
	q[f].y=sy;
	q[f].step=0;//初始化
	if(sx==fx&&sy==fy){
		cout<<"To get from "<<c1<<c2<<" to "<<c3<<c4<<" takes "<<0<<" knight moves."<<endl;
		return ;//因为在函数中
	}
	while(f<=t){
		cxk u,v;//定义个当前步数时的各个变量为u下一步为v
		u=q[f++];
		for(int i=0;i<8;i++){
			v.x=u.x+dx[i];
			v.y=u.y+dy[i];//移动
			v.step=u.step+1;
			if(v.x==fx&&v.y==fy){
				cout<<"To get from "<<c1<<c2<<" to "<<c3<<c4<<" takes "<<v.step<<" knight moves."<<endl;//注意输出别漏空格
				return ;
			}//搜到了
         //因为只要这个先搜到就说明是最优解
			else if(v.x>=1&&v.x<=8&&v.y>=1&&v.y<=8){
				q[++t]=v;//结构体可以直接赋
			}//入队
		}
	}
}
int main(){
	while(cin>>c1>>c2>>c3>>c4){
		bfs(c1,c2,c3,c4);//读入加bfs
	}
	return 0;
}
```


------------

**ac率这么低,翻了一下原来是因为uva评测waiting.**



---

## 作者：lzxhdxx (赞：1)

# 本题dfs写法
目前还没有人写dfs，让我们这种dfs党怎么办呢？所以我们来水一发dfs代码

### 题意：
给定起点，终点和坐标偏移量，求最少需要多少步从起点走到到终点

### 方法：
此题我们应该使用dfs或bfs，此前已经有了多种做法，有双向bfs，常规bfs，启搜等等，这里我们来水一发dfs题解

### dfs思路：
从起点开始重复执行八个方向的搜索，搜到终点就更新答案。但是，这样很明显会TLE，所以我设置了**阈值**，阈值设成20就可以过~~全靠数据弱~~

这里提供两种方法：常规bfs&dfs

Code:
```cpp
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

char s1, s2, e1, e2;
int sx, sy, ex, ey, cnt[110][110] = { 0 }, dx[10] = { 0,1,2,2,1,-1,-2,-2,-1,0 }, dy[10] = { 0,2,1,-1,-2,-2,-1,1,2,0 }, minn = 64;
bool vis[110][110] = { false };

void dfs(int x, int y, int stp)//深搜
{
	if (x < 1 || y < 1 || x>8 || y>8 || stp > minn) return;//越界或步数超过当前最优解
	if (x == ex && y == ey) minn = min(minn, stp);//到达终点刷新答案
	else
		for (int i = 1; i <= 8; i++)
			dfs(x + dx[i], y + dy[i], stp + 1);//继续深搜
}

int bfs()//广搜
{
	queue<pair<int, int> >Q;//记录点的队列
	Q.push(make_pair(sx, sy));//插入起点
	vis[sx][sy] = true, cnt[sx][sy] = 0;//标记起点走过，步数为0
	while (!Q.empty())//循环直到队空
	{
		int nowx = Q.front().first, nowy = Q.front().second;//取出队头
		if (nowx == ex && nowy == ey) return cnt[nowx][nowy];//到达终点直接返回
		for (int i = 1; i <= 8; i++)
		{
			int newx = nowx + dx[i], newy = nowy + dy[i];//拓展点
			if (newx >= 1 && newy >= 1 && newx <= 8 && newy <= 8 && !vis[newx][newy])//不越界，没走过
			{
				Q.push(make_pair(newx, newy));//压入新点
				vis[newx][newy] = true, cnt[newx][newy] = cnt[nowx][nowy] + 1;//标记新点
			}
		}
		Q.pop();//弹队头
	}
	return -1;
}

int main()
{
	while (cin >> s1 >> s2 >> e1 >> e2)//重复读入
	{
		memset(cnt, 0, sizeof(cnt));
		memset(vis, false, sizeof(vis));//别忘了初始化
		sx = s1 - 96, sy = s2 - 48, ex = e1 - 96, ey = e2 - 48;//利用ASCLL码记录起点终点
		minn = 20;//minn设成20就可以过
		dfs(sx, sy, 0);
		cout << "To get from " << s1 << s2 << " to " << e1 << e2 << " takes " << minn << " knight moves." << endl;//输出
		//cout << "To get from " << s1 << s2 << " to " << e1 << e2 << " takes " << bfs() << " knight moves." << endl;
	}
	return 0;
}
```
其实我经过多次尝试，阈值最小可以设置成6

### 数据：

bfs:10ms /  0B /  1.51KB C++ 

dfs:

阈值20:2.40s /  0B /  1.51KB C++

阈值7:320ms /  0B /  1.51KB C++ 

这是本题新方法，求管理大大给过

---

## 作者：syf2008 (赞：0)

~~我来水咕值了~~

题目应该都看得懂吧

就是[这题](http://ybt.ssoier.cn:8088/problem_show.php?pid=1330)的多组数据版

这题要用BFS（~~如果你要用DFS我也拦不住你，数据会教你做人~~）

上代码
```
#include <bits/stdc++.h>
using namespace std;
struct ss{int x,y,sum;};
int dx[]={1,1,2,2,-1,-1,-2,-2},dy[]={2,-2,1,-1,2,-2,1,-1};马的八个方向
int minn;
queue<ss>q;
bool v[10][10];
void bfs(int x,int y,int q1,int q2)//队列BFS
{
	int e1,e2;
	q.push((ss){x,y,0});
	while(!q.empty())
	{
		ss qq=q.front();
		q.pop();
		for(int i=0;i<8;i++)
		{
			e1=dx[i]+qq.x;
			e2=dy[i]+qq.y;
			if(e1>0&&e1<=8&&e2>0&&e2<=8&&!v[e1][e2])
			{
				if(e1==q1&&e2==q2)
				{while(!q.empty())q.pop();minn=qq.sum+1;return;}
				v[e1][e2]=1;
				q.push((ss){e1,e2,qq.sum+1});
			}
		}
	}
}
int main()
{
	string a;
	int xb,b,xd,d;
	while(getline(cin,a))
	{
		minn=1e9;
		memset(v,0,sizeof(v));
		xb=a[0]-'a'+1;
		b=a[1]-'0';
		v[xb][b]=1;
		xd=a[3]-'a'+1;
		d=a[4]-'0';//处理起点+终点
		if(xb==xd&&b==d)//特判起点=终点的情况（不要也没事）
		{
			printf("To get from %c%d to %c%d takes 0 knight moves.\n",(char)xb+'a'-1,b,(char)xd+'a'-1,d);
			continue;
		}
		bfs(xb,b,xd,d);
			printf("To get from %c%d to %c%d takes %d knight moves.\n",(char)xb+'a'-1,b,(char)xd+'a'-1,d,minn);
	}
}
```

---

## 作者：EuphoricStar (赞：0)

## 思路：BFS

~~（本题类似于 [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)）~~

本题比较简单，就直接上代码了：

```cpp
#include <bits/stdc++.h>
#define print(res) printf("To get from %c%c to %c%c takes %d knight moves.\n", bg[0], bg[1], en[0], en[1], res);
using namespace std;

struct point
{
    int x, y, step;
};
char bg[5], en[5];
bool vis[10][10]; // 标记每个点是否访问过
int dx[] = {2, 2, 1, 1, -1, -1, -2, -2}; // 方向
int dy[] = {1, -1, 2, -2, 2, -2, 1, -1};
queue<point> q;

int main()
{
    while (scanf("%s%s", bg, en) != EOF)
    {
        int ans;
        memset(vis, 0, sizeof(vis));
        // 解析开始点与终止点
        int sx = bg[0] - 'a' + 1, sy = bg[1] - '0';
        int ex = en[0] - 'a' + 1, ey = en[1] - '0';
        while (!q.empty()) q.pop(); // 清空队列
        q.push({sx, sy});
        while (!q.empty())
        {
            int curx = q.front().x, cury = q.front().y, step = q.front().step;
            // 如果到达终点则记录当前用的步数并退出循环
            if (curx == ex && cury == ey) { ans = step; break; }
            q.pop();
            for (int i = 0; i < 8; ++i)
            {
                int newx = curx + dx[i], newy = cury + dy[i];
                if (newx < 1 || newx > 8 || newy < 1 || newy > 8) continue; // 如果越界了就继续
                if (vis[newx][newy]) continue; // 如果该点没有访问过则将它添加到队列中
                q.push({newx, newy, step + 1});
                vis[newx][newy] = 1; // 将该点标记为访问过
            }
        }
        print(ans);
    }
    return 0;
}
```


---

## 作者：Celtic (赞：0)

题目大意：在$8\times 8$的棋盘上，给定起点、终点和$8$种行走方式，求从起点到终点的最少步数。

给定了起始状态和结束状态，求最少步数。显然是用$BFS$，为了节省时间，我选择了双向$BFS$。双向$BF$S即从起点向终点搜，从终点向起点搜，扩展各自的状态，直到出现两者扩展的状态重合。一个优化，每次选择结点少的扩展。

```cpp#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define eps 1e-20
#define re register
#define N 2001001
#define MAX 2001
using namespace std;
typedef long long ll;
typedef double db;
inline void read(re ll &ret)
{
    ret=0;re ll pd=0;re char c=getchar();
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	ret=pd?-ret:ret;
}
ll t,n,x,y,xx,yy;
ll dx[9]={0,-2,-2,-1,1,2,2,1,-1};
ll dy[9]={0,-1,1,2,2,1,-1,-2,-2};
bool vis[MAX][MAX];
char s1[N],s2[N];
struct node
{
	ll x,y,deep;
	node(re ll a,re ll b,re ll c)
	{
		x=a;
		y=b;
		deep=c;
	}
};
int main()
{
	while(~scanf("%s",s1+1))
	{
		for(re int i=1;i<=8;i++)
			for(re int j=1;j<=8;j++)
				vis[i][j]=false;
		x=s1[1]-'a'+1;
		y=(s1[2]&15);
		scanf("%s",s2+1);
		xx=s2[1]-'a'+1;
		yy=(s2[2]&15);
		queue<node>q;
		re node tmp=node(x,y,0);
		q.push(tmp);
		while(!q.empty())
		{
			tmp=q.front();
			q.pop();
	//		cout<<tmp.x<<" "<<tmp.y<<endl;
			if(tmp.x==xx&&tmp.y==yy)
			{
				printf("To get from ");
				putchar(s1[1]);
				putchar(s1[2]);
				printf(" to ");
				putchar(s2[1]);
				putchar(s2[2]);
				printf(" takes %lld knight moves.\n",tmp.deep);
				break;
			}
			for(re int i=1;i<=8;i++)
			{
				if(tmp.x+dx[i]<=0||tmp.x+dx[i]>8||tmp.y+dy[i]<=0||tmp.y+dy[i]>8||vis[tmp.x+dx[i]][tmp.y+dy[i]])
					continue;
				vis[tmp.x+dx[i]][tmp.y+dy[i]]=true;
				q.push(node(tmp.x+dx[i],tmp.y+dy[i],tmp.deep+1));
			}
				
		}
	}
    exit(0);
}
```


---

## 作者：火箭升空 (赞：0)

## 1.题目大意
在8*8的棋盘上， 给定了起点、终点和8种行走方式， 求从起点到终点的最少步数。

## 2.解题思路
这题一看就是BFS，为了节省时间，我就用了双向BFS。

即从起点到终点，从终点到起点同时搜，扩展各自的状态， 直至状态相同（重合）
## 3.优化
- 若起点和终点相同，直接输出0
- 每次选择结点较少的来扩展

## 4.代码实现

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <vector>
//#define int long long
#define MAXN 305
using namespace std;
struct Node{
	int x, y;
}q[2][MAXN * MAXN];
int l[2], r[2], ans, n, T;
int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};//8个方向 
int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int step[2][MAXN][MAXN], vis[2][MAXN][MAXN];//vis[]用于标记， step[]记录步数 
void init() { //初始化 
	memset(vis, 0, sizeof(vis));
	memset(q, 0, sizeof(q));
	memset(step, 0, sizeof(step));
}
bool check(int k) {
	int x = q[k][l[k]].x, y = q[k][l[k]].y;
	int d = step[k][x][y], tx, ty;
	for (int i = 0; i < 8; i++){
		tx = x + dx[i], ty = y + dy[i];
		if (tx >= 0 && tx <= n && ty >= 0 && ty <= n && !vis[k][tx][ty]) {
			vis[k][tx][ty] = 1;
			q[k][++r[k]].x = tx;
			q[k][r[k]].y = ty;
			step[k][tx][ty] = d + 1;
			if (vis[1 - k][tx][ty]) { //如果重合，就返回真 
				ans = step[k][tx][ty] + step[1 - k][tx][ty];
				return true;
			}
		}
	}
	return false;
}
void bfs() {
	if (q[0][1].x == q[1][1].x && q[0][1].y == q[1][1].y) {
		ans = 0;
		return;
	}
	vis[0][q[0][1].x][q[0][1].y] = 1;
	vis[1][q[1][1].x][q[1][1].y] = 1;
	l[0] = r[0] = l[1] = r[1] = 1;
	while (l[0] <= r[0] && l[1] <= r[1]) {
		if (r[0] - l[0] < r[1] - l[1]) { //优化：选择结点少的扩展 
			if (check(0)) return;
			l[0]++;
		}
		else {
			if (check(1)) return;
			l[1]++;
		}
	}
}
signed main(){
	char x1, x2, y1, y2;
	while (cin >> x1) {
		init();
		n = 7;
		cin >> y1;
		cin >> x2 >> y2;
		q[0][1].x = x1 - 'a';//记录起点
		q[0][1].y = y1 - '1';
		q[1][1].x = x2 - 'a';//记录终点 
		q[1][1].y = y2 - '1';
		bfs();
		cout << "To get from " << x1 << y1 << " to " << x2 << y2 << " takes " << ans << " knight moves." << endl;
	}
	return 0;
}


```
 _**有一个基本一样的题[SP12323 NAKANJ - Minimum Knight moves !!!](https://www.luogu.com.cn/problem/SP12323)**_ 

------------

### 求求管理员大佬给通过啦qwq

---

