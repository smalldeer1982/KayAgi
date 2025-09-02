# Labyrinth

## 题目描述

## 题意描述
你正在玩一款电脑游戏。在其中一关，你位于一个 $n$ 行 $m$ 列的迷宫。每个格子要么是可以通过的空地，要么是障碍。迷宫的起点位于第 $r$ 行第 $c$ 列。你每一步可以向上、下、左、右中的一个方向移动一格，前提是那一格不是障碍。你无法越出迷宫的边界。

不幸的是，你的键盘快坏了，所以你只能向左移动不超过 $x$ 格，并且向右移动不超过 $y$ 格。因为上下键情况良好，所以对向上和向下的移动次数没有限制。

现在你想知道在满足上述条件的情况下，从起点出发，有多少格子可以到达（包括起点）？

## 样例 #1

### 输入

```
4 5
3 2
1 2
.....
.***.
...**
*....
```

### 输出

```
10
```

## 样例 #2

### 输入

```
4 4
2 2
0 1
....
..*.
....
....
```

### 输出

```
7
```

# 题解

## 作者：ImmortalWatcher (赞：28)

大家好，很高兴能为大家讲解我自己的思路，如果有什么说不太清楚的，请多多见谅，谢谢大家。
—————————————————————————————————————

好的，现在开始真正讲题，我们先读题。
# 题目大意
给你一个n*m的矩阵，让你把（r,c）当做起点去四处乱走，但是有一个规定，你可以随便往上往下走，但你往左走的次数不能超过x，往右走的次数不能超过y，也就是左走次数$\leq x$，右走次数$\leq y$。最后问你的是你最多能走多少个位置（起点也算）。

## 理解了题目大意，一切就好办了
# 思路
首先，只是一道经典宽搜题，我们可以直接从起点开始宽搜，每经过一个点，就把它标记一下，防止重复遍历，知道任何的点都不满足遍历条件或已经被遍历过以后结束宽搜，结果就是你遍历到的点的个数。
代码如下：

```cpp
#include<cstdio>
using namespace std;
int n,m,st,en,i,x,y,r,c,d[4000001][6],fx[5][3],xx,yy,ans;
char a[2001][2001];
bool bz[2001][2001];
int main()
{
    fx[1][1]=fx[3][2]=-1;fx[2][1]=fx[4][2]=1;
    scanf("%d%d",&n,&m);
    scanf("%d%d",&r,&c);
    scanf("%d%d",&x,&y);
    getchar();
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
            a[i][j]=getchar();
        getchar();
    }
    st=0;
    en=1;
    bz[r][c]=true;
    d[1][1]=r;
    d[1][2]=c;
    d[1][3]=1;
    d[1][4]=x;
    d[1][5]=y;
    ans=1;
    while (st<en)
    {
        st++;
        for (int i=1;i<=4;i++)
        {
            xx=d[st][1]+fx[i][1];
            yy=d[st][2]+fx[i][2];
            if (i==3&&d[st][4]-1<0) continue;
            if (i==4&&d[st][5]-1<0) continue;
            if (xx>0&&xx<=n&&yy>0&&yy<=m&&bz[xx][yy]==false&&a[xx][yy]=='.')
            {
                d[++en][1]=xx;
                d[en][2]=yy;
                d[en][3]=d[st][3]+1;
                if (i==3) d[en][4]=d[st][4]-1;
                else d[en][4]=d[st][4];
                if (i==4) d[en][5]=d[st][5]-1;
                else d[en][5]=d[st][5];
                ans++;
                bz[xx][yy]=true;
            }
        } 
    }
    printf("%d",ans);
    return 0;
} 
```

#### 注：d[st][3]没用，我没事干打多了。
## 但是，只要你按照我这样的打法去交，你肯定会这样。
![](https://cdn.luogu.com.cn/upload/pic/57162.png)

# 为什么会这样？
别急，等我慢慢说。

其实，也许我们仔细想一想，我的程序是有漏洞的，比如说，一个点可能经过许多种路径到达，这些不同的路径的左走次数和右走次数又不同，所以就会导致我这考虑最先到达的，其实其他的到达方法也可能造成答案的不同。

所以当我们遇到同一个点被经过多次时，什么时候舍弃，什么时候继续留下这个状态呢？

我们可以记录一个点的最少左移次数和最少右移次数，当我们看见一个点被遍历多次时，就把这个路径的左移次数和右移次数与最少左移次数和右移次数比较，如果更优就更新，并继续往前遍历，如果其中有一个更优，就继续遍历，但不更新，至于都不优，那还要来干什么直接扔掉。

所以AC代码就是这样的，我认为（认为，不是肯定）我的程序应该是比其他人要短一些的，所以打起来也不会纳那么费劲。

```cpp
#include<cstdio>
using namespace std;
int i,j,en=1,ans=1,n,m,st,x,y,r,c,xx,yy,d[10000001][5]//宽搜状态，1表示第几行，2表示第几列，3表示左移次数，4表示右移次数，,bz[2001][2001]//左移次数,bz2[2001][2001];//右移次数
char a[2001][2001];
const int max=0x7FFFFFFF,fx[4][2]={-1,0,1,0,0,-1,0,1};
int main()
{
    scanf("%d%d%d%d%d%d\n",&n,&m,&r,&c,&x,&y);
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=m;j++)
            a[i][j]=getchar(),bz[i][j]=max,bz2[i][j]=max;//因为是要记录最少的次数，所以一开始就要附一个极大值
        getchar();
    }
    d[1][1]=r;
    d[1][2]=c;
    bz[r][c]=0;
    bz2[r][c]=0;//初始化
    while(st<en)
    {
        st++;
        for(i=0;i<4;i++)//四个方向走一走
        {
            int xx=d[st][1]+fx[i][0],yy=d[st][2]+fx[i][1],u=0,v=0;//将要走去的地点
            if(i==2) u++;
            if(i==3) v++;//这是直接看要不要加上左移或右移的步数
            if(u+d[st][3]>x||v+d[st][4]>y||xx<=0||xx>n||yy<=0||yy>m||a[xx][yy]!='.'||(bz[xx][yy]<=d[st][3]+u&&bz2[xx][yy]<=d[st][4]+v)) continue;//判断一下是不是需要舍弃的状态
            if(bz[xx][yy]>d[st][3]+u&&bz2[xx][yy]>d[st][4]+v)//都更优就更新
            {
            	if(bz[xx][yy]==max&&bz2[xx][yy]==max) ans++;//如果这个点还没走过，就把答案+1
            	bz[xx][yy]=d[st][3]+u;
				bz2[xx][yy]=d[st][4]+v;
        	}
            d[++en][1]=xx;
            d[en][2]=yy;
            d[en][3]=d[st][3]+u;
            d[en][4]=d[st][4]+v;//如果有其中一个更优，就继续往下走。
        }
    }
	printf("%d",ans);
    return 0;
} 
```
我的题解到此结束，希望大家能听懂，把这道题快快做对！！


---

## 作者：DDOSvoid (赞：21)

我们发现，无论 $(sx, sy)$ 以什么样的路径走到 $(x, y)$，向左和向右走的步数的差的都一样，均为 $sy-y$。定义向左走的步数为 $l$，向右走的步数是 $r$,上句话等价于 $l-r=sy-y$

所以我们只需要最小化其中一个值即可。假设我们最小化 $l$，那么整张图的边权只有 0 - 1，可以做 0 - 1 bfs

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define maxn 2010
using namespace std;

int n, m, sx, sy, X, Y;

int ma[maxn][maxn];

char c[maxn];

struct node{
	int x, y;	
	node(int _x = 0, int _y = 0){x = _x; y = _y;}
};

int dx[] = {0, -1, 1, 0, 0};
int dy[] = {0, 0, 0, 1, -1};

deque<node> Q; int dis[maxn][maxn];
void bfs(){ memset(dis, -1, sizeof dis);
	Q.push_front(node(sx, sy)); dis[sx][sy] = 0;
	while(!Q.empty()){
		node t = Q.front(); Q.pop_front();
		for(int i = 1; i <= 4; ++i){
			int x = t.x + dx[i], y = t.y + dy[i]; 
			if(x < 1 || x > n || y < 1 || y > m || ma[x][y]) continue;
			if(dis[x][y] != -1 && dis[x][y] <= dis[t.x][t.y] + (i == 4)) continue;
			dis[x][y] = dis[t.x][t.y] + (i == 4);
			if(i == 4) Q.push_back(node(x, y));
			else Q.push_front(node(x, y)); 
		}
	}
}

int ans;
int main(){
	scanf("%d%d%d%d%d%d", &n, &m, &sx, &sy, &X, &Y);
	for(int i = 1; i <= n; ++i){
		scanf("%s", c + 1);
		for(int j = 1; j <= m; ++j) if(c[j] == '*') ma[i][j] = 1;
	} bfs();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j){
			if(dis[i][j] == -1) continue;
			int a = dis[i][j], b = j - sy + a;
			if(a <= X && b <= Y) ++ans; 
		}
	cout << ans;
	return 0; 
}
```

---

## 作者：mot1ve (赞：11)

01bfs模板题 蒟蒻不会优化 直接爆搜 超不了时
这道题01bfs的大体思路就是维护一个双端队列，把向上和向下走看成边权为0，把向左和向右走看成边权为1，其实就是一个01边权的最短路问题。如果边权为0的话，从队头插入，如果边权为1的话，从队尾插入。保证每次出队的都是最小的。
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<deque>
#include<algorithm>
using namespace std;
int n,m,r,c,x,y;
char s[2010][2010];
bool vis[2010][2010];
int xx[4]={1,-1,0,-0};
int yy[4]={0,0,-1,1};
int ans;
struct node{
	int x,y,l,r;//x,y表示当前坐标，l,r分别表示还能向左和向右走的步数
};
int main()
{
	cin>>n>>m>>r>>c>>x>>y;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>s[i][j];
		}
	}
	deque<node> q;//双端队列
	q.push_back((node){r,c,x,y});
	while(!q.empty())
	{
		node p;
		p=q.front();
		q.pop_front();
		if(vis[p.x][p.y]==1||(p.l<0)||(p.r<0)) continue;
		vis[p.x][p.y]=1;
		ans++;
		for(int i=0;i<4;i++)
		{
			int dx=p.x+xx[i];
			int dy=p.y+yy[i];
			if(dx<=0||dx>n||dy<=0||dy>m||s[dx][dy]=='*'||vis[dx][dy]==1) continue;
			if(i==0||i==1)
			{
				q.push_front((node){dx,dy,p.l,p.r});
				continue;
			}
			if(i==2)
			{
				q.push_back((node){dx,dy,p.l-1,p.r});
				continue;
			}
			if(i==3)
			{
				q.push_back((node){dx,dy,p.l,p.r-1});
			}
		}
	}
	cout<<ans;
	return 0;
}

---

## 作者：ouuan (赞：11)

这题有向左最大步数和向右最大步数两个约束，所以很烦。能不能只有一个约束呢？这个时候往往要观察几个约束条件之间的关系。

**1.向左走的步数-向右走的步数=起点横坐标-终点横坐标**

有了这个式子，就可以用向左走的步数同时表示向右走的步数。

**2.向左走的步数越多，向右走的步数越多**

这个条件是可以由上面那个式子推来的，它的作用是保证了向左走的步数最少时一定是全局最优解。

所以整个问题被转化成了只用管向左步数的01最短路，用SPFA即可解决，计算答案时满足**向左步数<=向左最大步数&&向左步数+横坐标之差<=最大向右步数**就计入答案。

参考代码：

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<int,int> pii;

const int N=2010;
const int dir[4][2]={{0,-1},{0,1},{1,0},{-1,0}};

int n,m,r,c,x,y,dis[N][N],ans;
bool g[N][N],inq[N][N];
char s[N];
queue<pii> q;

int main()
{
	int i,j,tx,ty;
	pii t;
	
	memset(dis,0x3f,sizeof(dis));
	
	scanf("%d%d%d%d%d%d",&n,&m,&r,&c,&x,&y);
	
	for (i=1;i<=n;++i)
	{
		scanf("%s",s);
		for (j=1;j<=m;++j)
		{
			if (s[j-1]=='.')
			{
				g[i][j]=true;
			}
		}
	}
	
	dis[r][c]=0;
	
	q.push(pii(r,c));
	
	while (!q.empty())
	{
		t=q.front();
		q.pop();
		inq[t.first][t.second]=false;
		for (i=0;i<4;++i)
		{
			tx=t.first+dir[i][0];
			ty=t.second+dir[i][1];
			if (g[tx][ty]&&dis[tx][ty]>dis[t.first][t.second]+(i==0))
			{
				dis[tx][ty]=dis[t.first][t.second]+(i==0);
				if (!inq[tx][ty])
				{
				    inq[tx][ty]=true;
				    q.push(pii(tx,ty));
				}
			}
		} 
	}
	
	for (i=1;i<=n;++i)
	{
		for (j=1;j<=m;++j)
		{
			if (g[i][j]&&dis[i][j]<=x&&dis[i][j]+j-c<=y)
			{
				++ans;
			}
		}
	}
	
	printf("%d",ans);
	
	return 0;
}
```

---

## 作者：StarryWander (赞：7)

# 本题采用BFS。

这道题目与普通 BFS 裸题**大致相同**但是有一点区别，如下↓。

不幸的是，你的键盘快坏了，**所以你只能向左移动不超过 $x$ 格**，**并且向右移动不超过 $y$ 格**。因为上下键情况良好，所以对向上和向下的移动次数没有限制。

很自然地想到，可以在BFS的结构体里增加记录左右移动的步数的变量 $l,r$ 。

```cpp
struct node{
	int x,y,l,r;
};
```
然后我们就可以在每到达一个点的时候，判断左右步数是否超过限制。

## BUT
当我们这么去做的时候就会出现一个问题：一个点可能有**多种通达的方法**，但是，不同的通达方法也有不同的左右移动次数，第一次到达这个点的时候，可能**左右移动次数并不是最小的**，导致下一个点无法访问。

所以，我们需要取这些方法的最小值。

## 如何取最小值呢？
我们可以在 BFS 搜索的过程中做一些判断：

如果这个点来过，判断第二次来是否有更小的左右移动次数。

如果没来过，就照常访问。

判断的代码：

```cpp
if(x>=1&&x<=n&&y>=1&&y<=m){
	if(a[x][y]=='.'&&nl<=l&&nr<=r){
		q.push((node){x,y,nl,nr});
		p[x][y].l=nl;
		p[x][y].r=nr;
		a[x][y]='+';
		ans++;
	}
	else if(a[x][y]=='+'){
		if(nl<p[x][y].l&&nr<p[x][y].r){
			q.push((node){x,y,nl,nr});
			p[x][y].l=nl;
			p[x][y].r=nr;
		}
	}
}
```
## 这个时候我们就能愉快地BFS了！

# code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct node{
	int x,y,l,r;
};//状态结构体
int n,m,sx,sy,l,r,ans=1;
node off[4]={{0,1,0,1},{1,0,0,0},{0,-1,1,0},{-1,0,0,0}};//方向向量
char a[2005][2005];//地图
node p[2005][2005];//记录这个点左，右移动访问的次数
int main(){
	cin>>n>>m>>sx>>sy>>l>>r;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
  	//BFS：
	queue<node>q;
	q.push((node){sx,sy,0,0});
	a[sx][sy]='+'; 
	p[1][1].l=p[1][1].r=0;
	while(!q.empty()){
		node k=q.front();
		for(int i=0;i<4;i++){
			int x=k.x+off[i].x;
			int y=k.y+off[i].y;
			int nl=k.l+off[i].l;
			int nr=k.r+off[i].r;
			if(x>=1&&x<=n&&y>=1&&y<=m){
				if(a[x][y]=='.'&&nl<=l&&nr<=r){//没访问过的点访问
					q.push((node){x,y,nl,nr});
					p[x][y].l=nl;
					p[x][y].r=nr;
					a[x][y]='+';
					ans++;
				}
				else if(a[x][y]=='+'){//被访问过的点重新判断
					if(nl<p[x][y].l&&nr<p[x][y].r){
						q.push((node){x,y,nl,nr});
						p[x][y].l=nl;
						p[x][y].r=nr;
					}
				}
			}
		}
		q.pop();
	}
    cout<<ans;
	return 0;
}

```




---

## 作者：xukuan (赞：4)

一道黄题居然被评紫了……

直接BFS

我将上下移动的加入对头，左右移动的加入队尾，进行常规的BFS即可

### 最关键的证明：证明node中不存在(a.l>b.l&&a.r>b.r)或(a.l<b.l&&a.r<b.r)的情况

因为a.l-b.l==-(a.r-b.r)

即a.l-b.l==b.r-a.r

所以原命题成立


#### 用STL中的双端队列维护数组

入队时，向上或向下的在队头入队，向左或向右的在队尾入队

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll lx[4]={-1,1,0,0},
		 ly[4]={0,0,-1,1};
//0:向上
//1:向下
//2:向左
//3:向右

ll n,m,r,c,L,R,ans=1;//ans的初值为1，因为起点一定可以走到
char a[2010][2010];
bool b[2010][2010];
//b为false代表这个点没有被走过,为true代表走过
struct node{
	ll x,y,l,r;
    //x代表当前位置所在行
    //y代表当前位置所在列
    //l代表当前位置还能向左移动的次数
    //r代表当前位置还能向右移动的次数
};
deque<node> q;

int main(){
	scanf("%lld %lld",&n,&m);//矩阵的大小
	scanf("%lld %lld",&r,&c);//现在的位置
	scanf("%lld %lld",&L,&R);//可以向左或有移动的次数
	for(ll i=1; i<=n; i++){
		scanf("%s",a[i]+1);//输入点阵
	}
	
	memset(b,false,sizeof(b));//b没有被走过
	b[r][c]=true;//起点直接标记为被走过
	q.push_back(node{r,c,L,R});
	while(!q.empty()){
		node Next=q.front();//取出队头
        q.pop_front();//队头出队，因为后面的入队可能在队头入队，所以要先出队
		for(ll i=0; i<4; i++){//穷举4个方向
			ll x=Next.x+lx[i],y=Next.y+ly[i];//
			if(x>=1&&x<=n&&y>=1&&y<=m&&(a[x][y]=='.')&&(b[x][y]==false)){
            	//继续搜索的条件：
                //1.没有范围超限
                //2.这个点可以走
                //3.以前没有走过
				switch(i){
					case 0:
					case 1:{
                    //向上或向下走
						ans++;//计数器+1，下同
						b[x][y]=true;//改成走过
						q.push_front(node{x,y,Next.l,Next.r});//队头入队
						break;
					}
					case 2:{
                    //向左走
						if(Next.l){
							ans++;
							q.push_back(node{x,y,Next.l-1,Next.r});
							b[x][y]=true;
						}
						break;
					}
					case 3:{
                    //向右走
						if(Next.r){
							ans++;
							q.push_back(node{x,y,Next.l,Next.r-1});
							b[x][y]=true;
						}
						break;
					}
				}	
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：2)

先给个公式：
$$\boxed{r-l=s-e}$$
其中 $r$ ， $l$ 表示向左，右走的步数， $s$ ， $e$ 表示起点和终点的纵坐标。

可见当起点终点确定时，向左的步数越小，向右也越小，反之亦然。

考虑使用 bfs 。

先让起点坐标伴随左右步数（ $0$ ） 入队，每一次取出队首，如果坐标不合法或者有比它左右步数更小或者左右步数已超出最大范围就重新操作，不然向其四周扩展队列，直到队列空为止。

## $Code$

```cpp
#include<iostream>
#include<cstring>
#include<map>
#include<queue>
using namespace std;
const int MAXN=2e3+5;
char a[MAXN][MAXN];
int n,m,r,c,x,y;
struct node{
	int x,y,r,s;//坐标,step->x-1
}dp,dq;
queue <node> us;
int xx[MAXN][MAXN];
int dx[4]={-1,0,0,1},dy[4]={0,1,-1,0},dr[4]={0,0,1,0},ds[4]={0,1,0,0};
int ans=0;
int main(){
	cin>>n>>m>>r>>c>>x>>y;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			xx[i][j]=1e9;
		}
	dp.x=r,dp.y=c,dp.r=0,dp.s=0;
	us.push(dp);
	while(!us.empty()){
		dp=us.front();
		us.pop();
		if(xx[dp.x][dp.y]<=dp.r||dp.r>x||dp.s>y||a[dp.x][dp.y]!='.')
			continue;
		if(xx[dp.x][dp.y]==1e9)
			ans++;
		xx[dp.x][dp.y]=dp.r;
		for(int i=0;i<4;i++){
			dq.x=dp.x+dx[i];
			dq.y=dp.y+dy[i];
			dq.r=dp.r+dr[i];
			dq.s=dp.s+ds[i];
			us.push(dq);
		}
	}
	cout<<ans;
}
```


---

## 作者：FanYongchen (赞：2)

首先，直接看题目，初步发现这是一道bfs

### 1.上下可以随意移若干步

### 2.左右移动有一定限制

刚开始的我，打出了如下代码：

```cpp
#include <iostream>
#include <queue>
using namespace std;
struct Point
{
    int x;
    int y;
    int lstep;//向左走的步数 
    int rstep;//向右走的步数 
};
const int D[4][2] = { 0,1,1,0,0,-1,-1,0 };
int n, m;
int si, sj;
int lMax, rMax;//向左、向右最大可走步数 
char mp[2001][2001];
bool vis[2001][2001];//判断是否走过 
bool check(int i, int j, int l, int r)//判断这一步是否可走 
{
    return (i >= 0 && i < n&& j >= 0 && j < m&& l <= lMax && r <= rMax && !vis[i][j] && mp[i][j] != '*');
    //判断是否走出地图，左右移动步数是否满足要求以及是否走过这个点并且这个点可以走
}
int bfs(int i, int j)//广搜 
{
    queue<Point> q;
    q.push({ i,j,0,0 });
    Point tmp, p;
    int cnt = 1;//可到达的点的个数 
    vis[i][j] = true;//第一个点设为走过
    while (!q.empty())
    {
        tmp = q.front(), p = tmp;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            p = tmp;
            p.x += D[i][0], p.y += D[i][1];//移动
            if (i == 0) p.rstep++;//向右走 
            if (i == 2) p.lstep++;//向左走 
            if (check(p.x, p.y, p.lstep, p.rstep))//若这一步可走 
                q.push(p), vis[p.x][p.y] = true, cnt++;//将这个点入队,个数加一 
        }
    }
    return cnt;
}
int main()
{
    cin >> n >> m;
    cin >> si >> sj;
    cin >> lMax >> rMax;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> mp[i][j];
    si--, sj--;//我这里下标从0开始 
    cout << bfs(si, sj);
    return 0;
}
```
然后就会发现：

![](https://cdn.luogu.com.cn/upload/image_hosting/pv4gar1f.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这是为什么呢？

### 因为有时候走到同一个点，所用左右步数可能不同

所以当我们走到已走过的点，需要再一次判断当前左右已走的步数是否可以再走到其他点

若这个点 现在左移的次数 < 最小左移次数 

且 现在右移的次数 < 最小右移次数

则将这个点的最少移动次数更新。

若只有一个方向 < 最小次数，则不更新，但仍把它入队

AC代码如下：

```cpp
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
struct Point
{
    int x;
    int y;
    int lstep;//向左走的步数 
    int rstep;//向右走的步数 
};
const int D[4][2] = { 0,1,1,0,0,-1,-1,0 };
int n, m;
int si, sj;
int lMax, rMax;//向左、向右最大可走步数 
char mp[2001][2001];
bool vis[2001][2001];//判断是否走过 
int cnt[2001][2001][2];//走到这个点的最少左右移动次数，cnt[i][j][0]表示走到(i,j)向左走的步数，[1]代表向右
bool check(int i, int j, int l, int r)//判断这一步是否可走 
{
    return (i >= 0 && i < n&& j >= 0 && j < m&& l <= lMax && r <= rMax && !vis[i][j] && mp[i][j] != '*');
    //判断是否走出地图，左右移动步数是否满足要求以及是否走过这个点并且这个点可以走
}
int bfs(int i, int j)
{
    queue<Point> q;
    q.push({ i,j,0,0 });
    Point tmp, p;
    int ccnt = 1;//因为cnt[2001][2001][2]之前的统计次数的cnt冲突，因此把统计次数的重命名为ccnt
    vis[i][j] = true;//第一个点设为走过
    while (!q.empty())
    {
        tmp = q.front(), p = tmp;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            p = tmp;
            p.x += D[i][0], p.y += D[i][1];
            if (i == 0) p.rstep++;//左步数+1
            if (i == 2) p.lstep++;//右步数+1
            if (check(p.x, p.y, p.lstep, p.rstep))
                q.push(p), vis[p.x][p.y] = true, ccnt++, cnt[p.x][p.y][0] = p.lstep, cnt[p.x][p.y][1] = p.rstep;//我们第一次走到这个点
            else if (p.x >= 0 && p.y >= 0 && p.x < n && p.y < m && vis[p.x][p.y])//若已经走过这个点
            {
                if (p.lstep < cnt[p.x][p.y][0] && p.rstep < cnt[p.x][p.y][1])//左、右都小于最小值
                    q.push(p), cnt[p.x][p.y][0] = p.lstep, cnt[p.x][p.y][1] = p.rstep;//入队并更新
                if ((p.lstep < cnt[p.x][p.y][0] && p.rstep > cnt[p.x][p.y][1]) || (p.lstep > cnt[p.x][p.y][0] && p.rstep < cnt[p.x][p.y][1]))//其中一个小于最小值
                    q.push(p);//只需要入队
            }
        }
    }
    return ccnt;
}
int main()
{
    memset(cnt, 0x3f, sizeof(cnt));//先赋值为最大值
    cin >> n >> m;
    cin >> si >> sj;
    cin >> lMax >> rMax;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> mp[i][j];
    si--, sj--;//这里数组下标从0开始
    cout << bfs(si, sj);
    return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/cmbqfjxv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)



---

## 作者：IronELement (赞：1)

先来说明一下题目的意思（原题目好像有点糊）：所谓向左移动不超过x格，指的是不能向左移动x次，即不能按超过x次“向左”键。向右y格同理。  
  
好像还没有题解，所以先把自己不是很优越的宽搜写出来。  
  
**BFS**  
~~Baidu First Search~~  
最朴素的宽度搜索大家应该都会了。朴素的宽度搜索有一个队列。  
（我们习惯定义一个结构体，包含横坐标，纵坐标和时间）  
```
struct data
{
	int x;
	int y;
	int t;
}q[100010];
```  
这题的瓶颈是向左和向右移动的次数有限制。那么为什么不把当前向左和向右移动的次数也写在这个结构体里呢？这样就可以直接在宽搜的时候判断，把不符合要求的情况截掉了。同时这题只需要求能遍历到的节点的个数，所以时间可以不加入结构体。  
最后写出来是这样的。  
```
struct data
{
	int x;
	int y;
	int l;
	int r;
}q[16000000];
```  
（队列的空间我开成了点数的四倍）  
可是相比朴素的宽度搜索，在遍历到同一个点的时候，两条不同的路径，向左和向右移动的次数也不同。这时候就会产生大量的位置相同但左右移动次数不同的状态。要想办法剪枝。  
举个例子：  
路径A到p点需要左移1次，右移1次，路径B到p点需要左移3次，右移2次。很明显，走路径B到达p点后，能再遍历到的节点数必定小于等于走路径A后能再遍历到的节点数。这时候就不需要再用路径B去更新p点了。  

**怎样剪枝**  
朴素的宽搜有一个visited数组，用于标记某个点是否遍历过。把这个数组魔改一下。
```
struct data2
{
	int l;
	int r;
}visited[2010][2010];
```
一开始所有位置的.l和.r的初始值都是无穷大。  
还是用上面路径A和路径B的例子。  
为了方便，这里把走路径A需要的左移次数表示为mlA，右移次数表示为mrA。同理，对于路径B有mlB，mrB。
假设第一次遍历到点p(x,y)是走路径A。这时候发现 visited[x][y].l>mlA而且visited[x][y].r>mrA。那么我们用路径A更新p(x,y)，即visited[x][y].l=mlA,visited[x][y].r=mrA。然后继续向下搜索。  
第二次走路径B再遍历到点p(x,y)，这时候visited[x][y].l<mlB而且visited[x][y].r<mrB，那么我们就不用路径B更新p(x,y)。也不再搜索下去。  

如果只是左移和右移次数的其中一个比当前的visited[x][y]优，那么不更新visited[x][y]，但是要继续搜索下去。  
```
....N...*
.******.*
..*****.*
*.*****.*
*.*****.*
```
比如上图。现在到达N处，继续向下搜索。如果走左边的路径，需要左移4次，右移1次。如果走右边的路径，需要左移0次，右移3次。也就是说，对于上面所说的最后一种情况，不同的左移次数和右移次数可能可以遍历到不同的点。因此需要继续搜索下去。  
  
**如何防止重复搜到一个点**  
这里指的重复搜到是在左移和右移次数相同的时候重复搜到一个点。  
```
N
.
.
.
.
```
例如这张图。N点在上下移动的时候，左移和右移次数没有变。有可能在两个点之间来回走。  
所以我们在判断是否继续搜下去的语句上面做一些改动。
```
if(visited[nex][ney].l<=ml&&visited[nex][ney].r<=mr)continue;
```
把原先的小于改成小于等于（这里的continue是跳过这次往下搜索的循环）。  
  
**丑代码和一些注释**
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <cstdlib>
#include <ctime>

#define oo 2147483647

using namespace std;

struct data
{
	int x;
	int y;
	int l;
	int r;
}q[16000000];

struct data2
{
	int l;
	int r;
}visited[2010][2010];

const int mx[4]={0,1,0,-1};
const int my[4]={1,0,-1,0};

int n,m,i,j,k,l,r,c,maxl,maxr,ans;
char map[2010][2010];

bool check(int nex,int ney)
{
	return (nex<=0||nex>n||ney<=0||ney>m||map[nex][ney]=='*')?0:1;
}
//上面的check等价于if(条件)return 0;else return 1;
void BFS()
{
	int i,j,head=0,tail=0;
	head=1;
	q[head].x=r;
	q[head].y=c;
	q[head].l=0;
	q[head].r=0;//初始化
	while(tail<head)//蒟蒻写宽搜习惯把tail和head倒过来。。。请原谅！
	{
		tail++;
		int nx=q[tail].x,ny=q[tail].y;
		for(i=0;i<4;i++)
		{
			int nex=nx+mx[i],ney=ny+my[i];
			int ml=0,mr=0;
			if(i==0)mr++;
			if(i==2)ml++;
            //这里的ml和mx是这样扩展之后左移和右移次数的改变量
			if(ml+q[tail].l>maxl)continue;
			if(mr+q[tail].r>maxr)continue;
            //如果左右移动次数超过规定，那么不再扩展
			if(!check(nex,ney))continue;//检查x,y是否越界
			if(visited[nex][ney].l<=q[tail].l+ml&&visited[nex][ney].r<=q[tail].r+mr)continue;
            //上面所说的防止重复搜索和剪枝
			if(visited[nex][ney].l>q[tail].l+ml&&visited[nex][ney].r>q[tail].r+mr)
			{
				if(visited[nex][ney].l==oo&&visited[nex][ney].r==oo)ans++;//如果以前没有搜索到这个点，那么加入答案
				visited[nex][ney].l=q[tail].l+ml;
				visited[nex][ney].r=q[tail].r+mr;
			}
			head++;
			q[head].x=nex;
			q[head].y=ney;
			q[head].l=q[tail].l+ml;
			q[head].r=q[tail].r+mr;
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%d%d",&r,&c);
	scanf("%d%d",&maxl,&maxr);getchar();
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			map[i][j]=getchar();
			visited[i][j].l=oo;
			visited[i][j].r=oo;
		}
		getchar();
	}
	visited[r][c].l=0;
	visited[r][c].r=0;
	ans++;
	BFS();
	printf("%d",ans);
	return 0;
}
```

**蒟蒻写文，如果不当之处，请不留情面地打脸！**

---

## 作者：夏米亚丁 (赞：0)

**这是一道广搜题**

首先要明确移动方向，上下移动没有限制，向左不超过$x$次，向右不超过$y$次，所以要判断向左和向右是否合理，可以保存到达每个点，这个点还可以用多少个向左和向右键，那就需要一个双端队列了

```cpp
struct node{
	int x;//行 
	int y;//列 
	int l;//左有多少次 
	int r;//右有多少次 
}dq[N*N*2];//双端队列 
```
根据上下移动方向入队，如果向左或向右就队尾入队，向上向下移动就在对头入队,使用一个 $switch$
```cpp
#include<bits/stdc++.h>
#include<iostream>
using namespace std;
const int N=2010;
struct node{
	int x;
	int y;
	int l;
	int r;
}dq[N*N*2];
char g[N][N];//地图
bool vis[N][N];//标记访问数组
int head,tail,r,c,x,y,n,m,ans;
const int dx[]={-1,1,0,0};
const int dy[]={0,0,1,-1};//方向数组
void bfs(){
	head=N*N;
	tail=N*N;
	tail++;
	dq[tail].x=r-1;
	dq[tail].y=c-1;
	dq[tail].l=x;
	dq[tail].r=y;
	vis[r-1][c-1]=1;//将第一个点入队
	while(head!=tail){
		head ++;
		node t1=dq[head];
		for(int i=0;i<4;i++){
			node t2=t1;
			t2.x+=dx[i];
			t2.y+=dy[i];
			if(t2.x<0||t2.x>=n||t2.y<0||t2.y>=m||g[t2.x][t2.y]=='*'||vis[t2.x][t2.y]){
				continue;
			}
			switch(dy[i]){
				case 0://上下移动,对头入列
				ans++;
				dq[head]=t2;
				head--;
				vis[t2.x][t2.y]=1;
				break;
				case 1://向右移动,对尾入列
				if(!t2.r)break;
				ans++;
				tail++;
				dq[tail]=t2;
				dq[tail].r--;
				vis[t2.x][t2.y]=1;
				break;
				case -1://向左移动,对位入列
				if(!t2.l)break;
				ans++;
				tail++;
				dq[tail]=t2;
				dq[tail].l--;
				vis[t2.x][t2.y]=1;
				break;
			}
		}
	}
}
int main(){
	ans=1;
	cin>>n>>m>>r>>c>>x>>y; 
	for(int i=0;i<n;i++){
		cin>>g[i];
	}
	bfs();
	cout<<ans;
	return 0;
}
```


---

## 作者：fls233666 (赞：0)

初见这题，我认为这不就是一个带了左右移动次数限制的广度优先搜索题目吗？于是我直接写了一个普通的广搜代码交了上去。

正如我所想的，普通的广度优先搜索代码在第 40 个测试点挂了。

这是为什么呢？

我们来看一组测试数据：

	10 10
	10 4
	10 9
	...*******
	.*.*******
	.*.*******
	.*.*******
	.*.*******
	.*.*......
	.*.*.*****
	.*........
	.********.
	..........
    
手动模拟后，我们发现，如果按照一般的广度优先搜索的顺序拓展，会得到错误的答案。因为拓展的途中，两个拓展路径会重合在某一点。而其中能拓展更多格点的方案因为先到的劣的方案而被舍弃了。

发现问题后，我们考虑如何避免此情况。

一种可行的解决方案是，用另外一个二位数组，记录拓展到每个点时，能向左移动和向右移动的步数之和的最大值，以此来比较方案的优劣。当拓展到一个已经拓展过的点时，比较新的方案是否比之前到达这个点的方案更优，如果更优则拓展更优的方案。

当然也可以选择其它的方式来比较方案的优劣。具体的实现可以自行尝试。

下面是本人根据上述方法实现的代码：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;

const int mxn = 2020;

int n,m,r,c,nl,nr,hd,tl,cnt;
char mp[mxn][mxn];  //游戏地图存储
int flr[mxn][mxn];  //记录能左右移动步数之和，用于比较方案优劣
int dx[4]={-1,1,0,0};
int dy[4]={0,0,1,-1};
struct que_mode{
	int qx;
	int qy;
	int fl;  //能向左移动的步数
	int fr;  //能向右移动的步数
}que[mxn*mxn];

int main(){ 
	char cc;
	scanf("%d%d%d%d%d%d",&n,&m,&r,&c,&nl,&nr);
	for(rgt i=1;i<=n;i++){
		scanf("%c",&cc);
		for(rgt j=1;j<=m;j++){
			scanf("%c",&mp[i][j]);
		}
	}   //读入数据
    
	tl++;
	que[tl].qx=r;
	que[tl].qy=c;
	que[tl].fl=nl;
	que[tl].fr=nr;  //起点入队
	mp[r][c]='+';  //将走过的点用+标记
	flr[r][c]=nl+nr;
	cnt++;  //统计
    
	while(hd!=tl){
		hd++;
		for(rgt px,py,i=0;i<4;i++){
			px=que[hd].qx+dx[i];
			py=que[hd].qy+dy[i];
			if(px>0&&py>0&&px<=n&&py<=m&&mp[px][py]!='*'){
				if(mp[px][py]!='+'){  //拓展没有走过的点
                
					if(i==2){  //向右移动
						if(que[hd].fr>0){
							tl++;
							que[tl].qx=px;
							que[tl].qy=py;
							que[tl].fr=que[hd].fr-1;  //扣除相应步数
							que[tl].fl=que[hd].fl;
							mp[px][py]='+';
							flr[px][py]=que[tl].fl+que[tl].fr;
							cnt++;
						}
						continue;
					}
                    
					if(i==3){  //向左移动
						if(que[hd].fl>0){
							tl++;
							que[tl].qx=px;
							que[tl].qy=py;
							que[tl].fr=que[hd].fr;
							que[tl].fl=que[hd].fl-1;  //扣除相应步数
							mp[px][py]='+';
							flr[px][py]=que[tl].fl+que[tl].fr;
							cnt++;
						}
						continue;
					}
                    
             //其它情况正常入队
					tl++;
					que[tl].qx=px;
					que[tl].qy=py;
					que[tl].fr=que[hd].fr;
					que[tl].fl=que[hd].fl;
					mp[px][py]='+';
					flr[px][py]=que[tl].fl+que[tl].fr;
					cnt++;
                    
				}else {
					if(flr[px][py]<que[hd].fl+que[hd].fr){
                //遇到更优方案，拓展已经走过的点】
                
						if(i==2){  //向右移动
							if(que[hd].fr>0&&flr[px][py]<que[hd].fl+que[hd].fr-1){
								tl++;
								que[tl].qx=px;
								que[tl].qy=py;
								que[tl].fr=que[hd].fr-1;
								que[tl].fl=que[hd].fl;
								flr[px][py]=que[tl].fl+que[tl].fr;
							}
							continue;
						}
                        
						if(i==3){  //向左移动
							if(que[hd].fl>0&&flr[px][py]<que[hd].fl+que[hd].fr-1){
								tl++;
								que[tl].qx=px;
								que[tl].qy=py;
								que[tl].fr=que[hd].fr;
								que[tl].fl=que[hd].fl-1;
								flr[px][py]=que[tl].fl+que[tl].fr;
							}
							continue;
						}
                        
                //其它情况正常入队        
						tl++;
						que[tl].qx=px;
						que[tl].qy=py;
						que[tl].fr=que[hd].fr;
						que[tl].fl=que[hd].fl;
						flr[px][py]=que[tl].fl+que[tl].fr;
					}
				}
			}
		}
	}
	printf("%d\n",cnt);  //输出统计结果
	return 0;
}

```


---

## 作者：little_sun (赞：0)

# 题解 CF1063B 【Labyrinth】

### [安利博客](https://www.cnblogs.com/little-sun0331/p/10004515.html)

完了我发现我做CF的题大部分思路都和别人不一样qwq

这道题其实很水，不至于到紫题

我们只要bfs一下，向四个方向搜索，剪下枝，就A了（好像还跑的蛮快？）

是一道锻炼代码能力的好题

**Code：**

```cpp
#include <bits/stdc++.h>

#define check(x, y) (x >= 0 && x < n && y >= 0 && y < m)//判断是否越界

const int MaxN = 2010;
const int dx[] = {0, 1, -1, 0}, dy[] = {-1, 0, 0, 1};//bfs方向数组

struct p
{
    int x, y;
    int cntx, cnty;
};

int ans;

int n, m, x, y, limx, limy;

std::string s[MaxN];

int vis[MaxN][MaxN];

int disx[MaxN][MaxN], disy[MaxN][MaxN];

void bfs(int x, int y)
{
    memset(disx, 0x3f, sizeof(disx));
    memset(disy, 0x3f, sizeof(disy) );
    std::queue<p> q;
    q.push((p){x, y, 0, 0});
    disx[x][y] = disy[x][y] = 0;
    while (!q.empty())
    {
        p tmp = q.front();
        q.pop();
        x = tmp.x, y = tmp.y;
        for (int i = 0; i <= 3; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (!check(nx, ny) || s[nx][ny] == '*')//当前位置是否合法
                continue;
            int cntx = tmp.cntx + bool(dy[i] == -1), cnty = tmp.cnty + bool(dy[i] == 1);//计算向左/右走步数
            if (cntx < std::min(disx[nx][ny], limx + 1) || cnty < std::min(disy[nx][ny], limy + 1))//判断，剪枝
            {
                disx[nx][ny] = cntx;
                disy[nx][ny] = cnty;//更新向左/右走步数
                q.push((p){nx, ny, cntx, cnty});

            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    scanf("%d%d", &x, &y), --x, --y;
    scanf("%d%d", &limx, &limy);
    for (int i = 0; i < n; i++)
        std::cin >> s[i];
    bfs(x, y);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (disx[i][j] <= limx && disy[i][j] <= limy)
                ++ans;//统计答案
    printf("%d\n", ans);
    return 0;
}
```

---

