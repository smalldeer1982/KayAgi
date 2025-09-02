# [USACO13OPEN] What's Up With Gravity S

## 题目描述

Captain Bovidian is on an adventure to rescue her crew member, Doctor Beefalo.  Like all great adventures, this story plays out in a two dimensional N by M grid (1 <= N, M <= 500), representing a side view of the captain's world.  Some grid cells are empty while others are blocked and cannot be traversed.

Unfortunately, Captain Bovidian cannot jump.  She must obey the following rules of physics while traversing her world.

1) If there is no cell directly underneath Captain Bovidian (that is, if she is at the edge of the grid), then she flies out into space and fails her mission.

2) If the cell directly underneath Captain Bovidian is empty, then she falls into that cell.

3) Otherwise:

a) Captain Bovidian may move left or right if the corresponding cell exists and is empty.

b) Or, Captain Bovidian may flip the direction of gravity.

When Captain Bovidian changes the direction of gravity, the cell that's 'underneath' her (as mentioned in rules 1 and 2) toggles between the cell with one higher row index and the cell with one lower row index (the first row in the input has index 1, and the last row has index N). Initially, the cells with one higher row index are underneath Captain Bovidian.

Doctor Beefalo is lost somewhere in this world.  Help Captain Bovidian arrive at her cell using the least number of gravity flips as possible.  If it is impossible to reach Doctor Beefalo, please output -1.


Bovidian 船长正在拯救她的船员，Beefalo 博士。

和所有伟大的冒险故事一样，这个故事也是发生在一个2D平面上的。囧

这个平面是M\*N的格子组成的网格，代表着船长的世界的一个侧视图。

有些格子是空的，另一些则是实心的，并且不能直接通过。

很不幸的是，船长跳不起来。她必须遵守这个世界的特殊物理法则。

1）如果船长的正下方没有方块（换句话说，即使她正在网格的边缘），那么她就会掉入宇宙中，同时意味着冒险失败。

2）如果船长的正下方的方块是空的，那么她就会掉到这个方块，

3）在不满足1）与2）的情况下，船长可以做一下的事情：

a) 如果左边(或右边）的方格是空的，那么她可以走到那个格子。

b船长可以翻转重力的方向

当船长改变翻转重力的方向时，我们就改变船长”下方“的定义。

”下方“的定义只能是两种

(A)比船长位置所在的方格的列编号更大的格子，

(B)比船长位置所在的方格的列编号更小的格子,

一开始的时候，“下方”的定义是比船长位置所在方格的列编号更大的格子。

Beefalo博士正迷失在这个世界中的某一处，请帮助船长从起点到达博士的地方。

如果可以到达，请输出最少需要的翻转重力的次数。


如果不可以到达，请输出-1


## 说明/提示

输出解释：

首先，船长在（4,2），接着她翻转重力，到达（2,2）

接着她向右走走到（2,4），接着她第二次翻转重力，到达（4,4）

然后她继续向右走到（4,5），最后在翻转一次重力，到达博士所在的（3,5）


## 样例 #1

### 输入

```
5 5
#####
#...#
#...D
#C...
##.##```

### 输出

```
3```

# 题解

## 作者：Adove (赞：8)

这题可以通过构建分层图的方式解决

构建两个图，分别是重力向上的和重力向下的

对于重力某种情况下可以反转重力的位置，在该位置向另一张图连权为1的单向边

对于某种重力状况下可以向左或向右的位置，向左或向右连0边

跑最短路，在终点的两种情况下取最短距离即可

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=1005;

int n,m,np,S,T;
int ln[MAXN*MAXN<<1],h[MAXN*MAXN<<1];
int q[MAXN*MAXN<<2];
bool vis[MAXN*MAXN<<1];
bool c[MAXN][MAXN];
struct rpg{
	int li,nx,ln;
}a[MAXN*MAXN<<2];

int get(int x,int y){return (x-1)*m+y;}
void add(int ls,int nx,int ln){a[++np]=(rpg){h[ls],nx,ln};h[ls]=np;}

void SPFA(int S)
{
	memset(ln,0x7f,sizeof(ln));
	int hd=1,tl=1;q[hd]=S;ln[S]=0;vis[S]=1;
	while(hd<=tl){
		int nw=q[hd++];vis[nw]=0;
		for(int i=h[nw];i;i=a[i].li){
			if(ln[a[i].nx]>ln[nw]+a[i].ln){
				ln[a[i].nx]=ln[nw]+a[i].ln;
				if(!vis[a[i].nx]){
					vis[a[i].nx]=1;
					q[++tl]=a[i].nx;
				}
			}
		}
	}return;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			char ch;cin>>ch;
			if(ch=='#'){c[i][j]=1;continue;}
			else if(ch=='C') S=get(i,j);
			else if(ch=='D') T=get(i,j);
		}
	}for(int i=2;i<n;++i){
		for(int j=1;j<=m;++j){
			if(!c[i][j]){
				if(!c[i+1][j]) add(get(i,j),get(i+1,j),0);
				if(!c[i-1][j]) add(get(i,j)+n*m,get(i-1,j)+n*m,0);
				if(c[i+1][j]){
					if(j<m&&!c[i][j+1]) add(get(i,j),get(i,j+1),0);
					if(j>1&&!c[i][j-1]) add(get(i,j),get(i,j-1),0);
				}if(c[i-1][j]){
					if(j<m&&!c[i][j+1]) add(get(i,j)+n*m,get(i,j+1)+n*m,0);
					if(j>1&&!c[i][j-1]) add(get(i,j)+n*m,get(i,j-1)+n*m,0);
				}
			}
		}
	}for(int i=1;i<=m;++i){
		if(!c[1][i]&&!c[2][i]) add(i,i+m,0);
		if(!c[n][i]&&!c[n-1][i])add(get(n,i)+n*m,get(n-1,i)+n*m,0);
	}for(int i=2;i<n;++i){
		for(int j=1;j<=m;++j){
			if(!c[i][j]){
				if(c[i+1][j]) add(get(i,j),get(i,j)+n*m,1);
				if(c[i-1][j]) add(get(i,j)+n*m,get(i,j),1);
			}
		}
	}SPFA(S);if(min(ln[T],ln[T+n*m])<2e9)
	printf("%d\n",min(ln[T],ln[T+n*m]));
	else puts("-1");
	return 0;
}
```

---

## 作者：羚羊WANG (赞：5)

相信大家看到这里的时候，各位题目意思都理解的清清楚楚，明明白白

通过观察，我们可以发现，博士是在两种重力环境下来回转换，反复横跳，而每次反复横跳的代价为$1$

我们可以在两个图上跑$SPFA$，用来求在同一重力标准下，某一个可以到达
的所有位置

最后，我们可以把两个图上面对应的点用长度为$1$的

在两个大图上跑$SPFA$,最后比较两个图医生位置的长度，输出最小值即可

```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 1010
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n,m;
int c[MAXN][MAXN];
int S,T;
struct node{
	int nxt;
	int to;
	int d;
}e[MAXN*MAXN<<2];
int cnt;
int head[MAXN*MAXN<<1];
int k[MAXN*MAXN<<1];
inline int getsum(int x,int y){
	return (x-1)*m+y;
}
inline void add(int u,int v,int w){
	++cnt;
	e[cnt].nxt=head[u];
	head[u]=cnt;
	e[cnt].to=v;
	e[cnt].d=w;
}
int ll[MAXN*MAXN<<1];
int q[MAXN*MAXN<<2];
int vis[MAXN*MAXN<<1];
inline void spfa(int x){
	memset(k,0x7f,sizeof(k));
	int hd=1;
	int tail=1;
	q[hd]=x;
	k[x]=0;
	vis[x]=1;
	while(hd<=tail)
		{
			int now;
			now=q[hd];
			hd++;
			vis[now]=0;
			for(register int i=head[now];i;i=e[i].nxt)
				{
					int y;
					y=e[i].to;
					if(k[y]>k[now]+e[i].d)
						{
							k[y]=k[now]+e[i].d;
							if(!vis[y])
								{
									vis[y]=1;
									++tail;
									q[tail]=y;
								}
						}
				}
		}
	return;
}
signed main(){
	n=read();
	m=read();
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=m;++j)
			{
				char ch;
				cin>>ch;
				if(ch=='C')	
					S=getsum(i,j);
				if(ch=='D')
					T=getsum(i,j);
				if(ch=='#')
					c[i][j]=1;
			}
	for(register int i=2;i<n;++i)
		for(register int j=1;j<=m;++j)
			{
				if(!c[i][j])
					{
						if(!c[i+1][j])
							add(getsum(i,j),getsum(i+1,j),0);
						if(!c[i-1][j])
							add(getsum(i,j)+n*m,getsum(i-1,j)+n*m,0);
						if(c[i+1][j])
							{
								if(j<m && !c[i][j+1])
									add(getsum(i,j),getsum(i,j+1),0);
								if(j>1 && !c[i][j-1])
									add(getsum(i,j),getsum(i,j-1),0);
							}
						if(c[i-1][j])
							{
								if(j<m && !c[i][j+1])
									add(getsum(i,j)+n*m,getsum(i,j+1)+n*m,0);
								if(j>1 && !c[i][j-1])
									add(getsum(i,j)+n*m,getsum(i,j-1)+n*m,0);
							}
					}
			}
	for(register int i=1;i<=m;++i)
		{
			if(!c[1][i] && !c[2][i])
				add(i,i+m,0);
			if(!c[n][i] && !c[n-1][i])
				add(getsum(n,i)+n*m,getsum(n-1,i)+n*m,0);
		}
	for(register int i=2;i<n;++i)
		for(register int j=1;j<=m;++j)
			{
				if(!c[i][j])
					{
						if(c[i+1][j])
							add(getsum(i,j),getsum(i,j)+n*m,1);
						if(c[i-1][j])
							add(getsum(i,j)+n*m,getsum(i,j),1);
					}
			}
	spfa(S);
	if(min(k[T],k[T+n*m])<2e9)
		write(min(k[T],k[T+n*m]));
	else
		write(-1);
	return 0;
}
```


---

## 作者：2002chenhan (赞：2)

坑点：如果在掉落过程中碰到了D，也算是到达了。

Bfs + N多细节

**Bfs切记最优状态一定要放在前面，优先处理，要不答案会是错的！**

设立一个vis数组表示这个点曾经有没有到过。若想到达某个点必须满足vis[x][y]==true和ma[x][y]!='#'，才能到达。

做好充分准备后，从起点出发，进行宽搜。

对于每个点的宽搜，一定要够彻底。意思就是从这个点出发不需要经过重力反转就能到达的点全部访问一遍，重力反转后能到达的那个点也加入队列。

这里要注意，因为bfs有一个特点，就是最小解一定在前面，因此要保持队列中t的值是递增状态。如果是在不进行重力反转时挨个点的访问，就会使距离最近的路径成为答案。

所以每一个点在左右走时一定要走完它。这包括从这个点往左右两边走。掉落之后，继续左右尝试。

而重力反转后的点则不能立刻进行如上的操作。

这样做的目的是保证把同t的点全部优先加入队列，在插入t+1的点。
为了避免连续两次的重力反转，我在重力反转到达的点的上面，封上了一个封印，也就是vis[x-d[down]][y]=false。



【代码】
```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxl=510;
const int d[]={-1,1};

int n,m;
char ma[maxl][maxl];
bool vis[maxl][maxl];//vis[x][y]==true则(x,y)可以走 

struct node
{
	int x,y,t;
	bool down;
}S,E;
queue<node> q;

node fall(node P)
{
	do
	{
		if(P.x==E.x&&P.y==E.y)
		{
			printf("%d\n",P.t);
			exit(0);
		}
		P.x+=d[P.down];
	}while(ma[P.x][P.y]!='#');
	P.x-=d[P.down];
	return P;
}

void dfs(int x,int y,int t,bool down,bool right)
{
	if(vis[x][y]==false||ma[x][y]=='#') return ;
	if(ma[x+d[down]][y]!='#')
	{
		node Tmp=fall((node){x,y,t,down});
		x=Tmp.x,y=Tmp.y;
		if((down&&x==n)||(!down&&x==1)||vis[x][y]==false)
		{
			vis[x][y]=false;
			return ;
		}
		vis[x][y]=false;
		q.push(Tmp);
		dfs(x,y-1,t,down,0);
		dfs(x,y+1,t,down,1);
	}
	else
	{
		vis[x][y]=false;
		if(x==E.x&&y==E.y) 
		{
			printf("%d\n",t);
			exit(0);
		}
		q.push((node){x,y,t,down});
		dfs(x,y+d[right],t,down,right);
	}
}

void bfs()
{
	q.push(S);
	while(!q.empty())
	{
		node P=q.front();q.pop();
		int x=P.x,y=P.y,t=P.t;
		bool down=P.down;
		
		dfs(x, y-1, t, down, 0);//左
		dfs(x, y+1, t, down, 1);//右
		
		down=P.down^1;//重力反转 
		x+=d[down];
		if(vis[x][y]==true&&ma[x][y]!='#')
		{
			node Tmp=fall((node){x,y,t+1,down});
			x=Tmp.x,y=Tmp.y;
			if((down&&x==n)||(!down&&x==1)||vis[x][y]==false)
			{
				vis[x][y]=false;
				continue;
			}
			vis[x][y]=false;
			q.push(Tmp);
			vis[x-d[down]][y]=false;
		}
	}
	printf("-1\n");
}

int main()
{
	scanf("%d%d",&n,&m);
//	memset(vis,false,sizeof(vis));
	memset(ma,'#',sizeof(ma));
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ma[i]+1);
		for(int j=1;j<=m;j++)
		{
			if(ma[i][j]=='.') vis[i][j]=true;
			else if(ma[i][j]=='C') S=(node){i,j,0,true},ma[i][j]='.',vis[i][j]=false;
			else if(ma[i][j]=='D') E=(node){i,j,0},ma[i][j]='.',vis[i][j]=true;
		}
	}
	
	S=fall(S);
	if(S.x==n)
	{
		printf("-1\n");
		exit(0);
	}
	vis[S.x][S.y]=false;
	bfs();
	return 0;
}
```

---

## 作者：曹老师 (赞：2)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco13open-wuwg.html)

~~做这道题把我给做颓废了，也做气了~~说实话，一开始我连题目都没弄明白，正好教练不在，而且就我一个人在机房，于是打算看题解把这道题的意思给看明白，但是题解看了半天，发现洛谷上三篇题解的脑洞真的无语，题解不好好写，一句话带过，但你最起码坐标系都不太一样得说一下吧，唉。题解里面的三篇废话了半天，都说的搜索但都没说明白，我们都知道考得搜索，你只做对了细节都不提的，写什么题解。

--以上纯属吐槽，无恶意，为我浪费了一下午的时间而感慨。--

这道题，最短路可做。建图就先不说了，然后就是类似搜索的spfa，在搜索之前，先判断一个条件，这就得回到题目中来，题目中说，不满足1和2的才做3，那么我们就应该判断一下是否满足1和2，我就是陷在这里面好长时间，（吐槽就不多吐槽了），如果都不满足，再做3。做3的时候，分三种，左，右，翻转重力。路径的长度，就是翻转的次数，所以最后最短路就是最少的翻转次数。

## Code ##

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int L = 505;
struct Node {
    int x , y , flag;
    Node(){}
    Node(int _x , int _y , int _flag) {x = _x ; y = _y ; flag = _flag;}
};
int n , m , Cx , Cy , Dx , Dy , map[L][L];
int d[L][L][2] , vis[L][L][2] , ans;
queue<Node>q;

void upd(Node u , Node v) {
    if(d[u.x][u.y][u.flag] < d[v.x][v.y][v.flag]) {
        d[v.x][v.y][v.flag] = d[u.x][u.y][u.flag] + (u.flag==v.flag?0:1);
        if(!vis[v.x][v.y][v.flag]) {
            vis[v.x][v.y][v.flag] = 1;
            q.push(v);		
        }	
    }	
}

int spfa() {
    memset(d , 0x3f , sizeof(d));
    memset(vis , 0 , sizeof(vis));
    q.push(Node(Cx , Cy , 1));
    vis[Cx][Cy][1] = 1;
    d[Cx][Cy][1] = 0;
    while(!q.empty()) {
        Node u = q.front();
        q.pop();
        vis[u.x][u.y][u.flag] = 0;
        int dx = (u.flag==1?1:-1);
        if(u.x + dx >= 1 && u.x + dx <= n) {
            if(!map[u.x+dx][u.y])
                upd(u , Node(u.x+dx,u.y,u.flag));
            else {
                if(u.y+1<=m && !map[u.x][u.y+1])
                    upd(u , Node(u.x,u.y+1,u.flag));
                if(u.y-1>=1 && !map[u.x][u.y-1])
                    upd(u , Node(u.x,u.y-1,u.flag));
                upd(u,Node(u.x,u.y,u.flag^1));
            }
        }
    }
    return min(d[Dx][Dy][0],d[Dx][Dy][1]);
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++) {
            char c;
            cin>>c;
            if(c == 'C')
                Cx = i , Cy = j;
            if(c == 'D')
                Dx = i , Dy = j;
            if(c == '#')
                map[i][j] = 1;
            else
                map[i][j] = 0;
        }
    ans = spfa();
    if(ans == 0x3f3f3f3f)
        printf("-1");
    else
        printf("%d",ans);
    return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P2208

---

## 作者：Sunset_ (赞：1)

思路和部分代码是借鉴的...
就是一个走迷宫，只不过特殊处理一下重力的相关过程
代码里边有注释，写的还蛮清晰的...
```c
#include<map>
#include<stack>
#include<cmath>
#include<queue>
#include<cstdio>
#include<vector> 
#include<cstring>
#include<iostream>
#include<algorithm>
using std::cin;
using std::cout;
void gkd()
{
	std::ios::sync_with_stdio(false);
	cout.tie(NULL);
}
char map[555][555];
bool vis[555][555][4];
struct node
{
	int x, y, g, sum;//当前坐标，当前重力状态:1为上 -1为下 
}now, top;
std::deque<node> q;
int n, m, x, y;
signed main()
{
	//gkd();
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
	{
		scanf("%s",map[i]+1);
		for(int j = 1; j <= m; j++)
		{
			if(map[i][j] == 'C')
				x = i, y = j;
		}
	}
	now.x = x, now.y = y, now.g = 1, now.sum = 0;
	q.push_back(now);
	while(!q.empty())
	{
		top = q.front();
		q.pop_front();
		now.x = top.x + top.g,
		now.y = top.y,
		now.g = top.g,
		now.sum = top.sum; 
		if(map[top.x][top.y] == 'D')
			return cout << top.sum, 0;
		if(top.x + top.g < 1 || top.x + top.g > n || top.y < 1 || top.y > m)
			continue;//越了上下边界 
		vis[top.x][top.y][top.g + 1] = 1;
		if(map[top.x  + top.g][top.y] == '#')//脚下（头上）能不能踩 
		{
			now.x = top.x, 
			now.y = top.y + 1, 
			now.g = top.g, 
			now.sum = top.sum;
			if(!vis[top.x][top.y + 1][top.g + 1] && map[top.x][top.y + 1] != '#')
				q.push_front(now);//判断当前的重力下右移 
			
			now.x = top.x, 
			now.y = top.y - 1, 
			now.g = top.g, 
			now.sum = top.sum;
			if(!vis[top.x][top.y - 1][top.g + 1] && map[top.x][top.y - 1] != '#')
				q.push_front(now);//判断当前重力下左移 
			
			now.x = top.x, 
			now.y = top.y, 
			now.g =- top.g, 
			now.sum = top.sum + 1;
			if(!vis[top.x][top.y][-top.g + 1])
				q.push_back(now);//翻转重力			
		} 
		else
			q.push_front(now);//如果脚下不是可以踩的格子，那么就继续下落或者上落	
	}
	cout << -1 << '\n';
}
```


---

## 作者：jiang_cheng (赞：0)

## 解题思路：
一道不错的 BFS。我们考虑到，每次只能先处理完同层状态，才能处理下层状态。

所以可以采用一个很新颖的做法。我们开两个队列，一个处理本层状态，一个处理下一层状态。扩展出来的同层状态放在第一个队列里，下层状态则放在第二个队列里。当第一个队列空了以后，就处理第二个队列并交换两个队列编号（交换编号的实现请看代码）。当两个队列都空了，就代表广搜已经结束。
## 附上代码：
```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

const int kMaxN = 501;
const int kD[2][2] = {{0, 1}, {0, -1}};

struct Node {
  int x, y, d;
};

int n, m, x1, y1, x2, y2;
char c[kMaxN][kMaxN];
int v[kMaxN][kMaxN];         //记录到达每个点要翻转的次数
bool b[kMaxN][kMaxN][2], z;  //标记数组
queue<Node> q[2];            //两个队列

void Record(int x, int y, int d) {  //点的坐标，翻转的次数
  if ((x <= 1 && (d % 2)) || (x >= n && !(d % 2)) || y < 1 || y > m || b[x][y][d % 2] || c[x][y] == '#') {
    return;
  }
  if (d % 2) {  //当前重力朝上
    while (1) {
      if (c[x][y] == 'D') {    //如果搜到终点
        b[x2][y2][d % 2] = 1;  //标记终点到达
        v[x2][y2] = d;         //记录翻转次数
        z = 1;                 //标记可以退出BFS，可以优化一点常数
        return;
      }
      if (x <= 1 || b[x][y][d % 2]) {  //坠入深渊或已经到达
        return;
      }
      if (c[x - 1][y] == '#') {  //上面不是空的
        break;
      }
      x--;  //像上落
    }
  } else {
    while (1) {
      if (c[x][y] == 'D') {    //如果搜到终点
        b[x2][y2][d % 2] = 1;  //标记终点到达
        v[x2][y2] = d;         //记录翻转次数
        z = 1;                 //标记可以退出BFS，可以优化一点常数
        return;
      }
      if (x >= n || b[x][y][d % 2]) {
        return;
      }
      if (c[x + 1][y] == '#') {  //下面不是空的
        break;
      }
      x++;  //往下落
    }
  }
  b[x][y][d % 2] = 1;        //标记
  v[x][y] = d;               //记录翻转次数
  q[d % 2].push({x, y, d});  //入队
}

void Work() {
  Record(x1, y1, 0);                                              //起点入队
  for (int i = 0; (!q[0].empty() || !q[1].empty()) && !z; i++) {  //翻转次数，队列交换编号可通过i%2实现
    while (!q[i % 2].empty()) {
      Node u = q[i % 2].front();
      q[i % 2].pop();
      for (int j = 0; j < 2; j++) {  //处理同层状态
        Record(u.x + kD[j][0], u.y + kD[j][1], u.d);
      }
      if (i % 2) {                      //处理下层状态
        Record(u.x + 1, u.y, u.d + 1);  //翻转重力
      } else {
        Record(u.x - 1, u.y, u.d + 1);  //翻转重力
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  //freopen("gravity.in", "r", stdin);
  //freopen("gravity.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> c[i][j];
      if (c[i][j] == 'C') {  //记录起点
        x1 = i, y1 = j;
      }
      if (c[i][j] == 'D') {  //记录终点
        x2 = i, y2 = j;
      }
    }
  }
  Work();
  cout << ((b[x2][y2][1]) || (b[x2][y2][0]) ? v[x2][y2] : -1);  //判断终点是否到达
  return 0;
}
```


---

## 作者：俺是小程 (赞：0)

### 双端队列 + Hash判重广搜 ###

首先看到这么复杂的地图第一反应就是广搜了,,,
我觉得难点主要在 

 1. 每次扩展的时候花费不一定增大(也就是说如果使用普通队列是不满足单调性的, 答案可能会偏大)
 2. 判重.

第二点如果想偷懒可以直接用set搞定, 如果追求速度的话可以手写Hash函数.   
至于第一点嘛,,,我看有的人是用SPFA (@曹老师), 有的人是每次把当前相同花费的状态扩展完.  
如果扩展完的话, 不仅代码会变长, 而且细节繁琐. 所以在这里我使用了双端队列(`deque`) 来处理.  
对于当前状态扩展来的状态, 变化了重力的push_back, 其余的push_front, 这样就能解决队列单调性的问题了.

```cpp
#include <set>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> P;
const int MAXN = 5e2 + 10;

int N, M;
char mp[MAXN][MAXN];

struct state
{
    int x, y, val;
    bool g;//false->down, true-up;

    inline int Hash(){return ((x * 500 + y) << 1) | g;}
    inline int fall(){return x + (g ? -1 : 1);}
    inline bool out(){return !(1 <= x && x <= N && 1 <= y && y <= M);}

    void expand(vector<state> &cur){
        if(mp[fall()][y] != '#') {
            cur.push_back((state){fall(), y, val, g});
            return;
        }
        if(mp[x][y + 1] != '#') cur.push_back((state){x, y + 1, val, g});
        if(mp[x][y - 1] != '#') cur.push_back((state){x, y - 1, val, g});
        cur.push_back((state){x, y, val + 1, g ^ 1});
    }
};

bool vis[600000];
deque<state> q;
int bfs(){
    P s, t;
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= M; j++){
            if(mp[i][j] == 'C') s = P(i, j);
            if(mp[i][j] == 'D') t = P(i, j);
        }
    q.push_back((state){s.first, s.second, 0, false});

    while(!q.empty()){
        state u = q.front(); q.pop_front();
        if(u.out()) continue;

        vector<state> nxt; u.expand(nxt);
        for(vector<state>::iterator it = nxt.begin(); it != nxt.end(); ++it){
            if(P(it->x, it->y) == t) return it->val;
            if(vis[it->Hash()]) continue;
            
            vis[it->Hash()] = true;
            if(it->val > u.val) q.push_back(*it);
            else q.push_front(*it);
        }
    }
    return -1;
}

int main()
{
    // freopen("p2208.in", "r", stdin);
    cin>>N>>M;
    for(int i = 1; i <= N; i++){
        scanf(" ");
        for(int j = 1; j <= M; j++)
            mp[i][j] = getchar();
    }
    cout<<bfs()<<endl;
    return 0;
}
```

---

