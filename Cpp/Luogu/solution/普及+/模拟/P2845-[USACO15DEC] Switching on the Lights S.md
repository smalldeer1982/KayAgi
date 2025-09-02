# [USACO15DEC] Switching on the Lights S

## 题目背景

来源：usaco-2015-dec

Farm John 最近新建了一批巨大的牛棚。这些牛棚构成了一个 $N \times N$ 的矩形网络 $(1 < N < 100)$。

然而 Bessie 十分怕黑，他想计算可以把多少个牛棚的灯打开。

## 题目描述

有 $N \times N$ 个房间，组成了一张 $N \times N$ 的网格图，Bessie 一开始位于左上角 $(1,1)$，并且只能上下左右行走。


一开始，只有 $(1,1)$ 这个房间的灯是亮着的，Bessie 只能在亮着灯的房间里活动。


有另外 $M$ 条信息，每条信息包含四个数 $a,b,c,d$，表示房间 $(a,b)$ 里有房间 $(c,d)$ 的灯的开关。


请计算出最多有多少个房间的灯可以被打开。

## 说明/提示

Bessie 可以使用 $(1,1)$ 的开关打开 $(1,2),(1,3)$ 的灯，然后走到 $(1,3)$ 并打开 $(2,1)$ 的灯，走到 $(2,1)$ 并打开 $(2,2)$ 的灯。$(2,3)$ 的开关无法到达。因此可以点亮 $5$ 个房间。

## 样例 #1

### 输入

```
3 6
1 1 1 2
2 1 2 2
1 1 1 3
2 3 3 1
1 3 1 2
1 3 2 1
```

### 输出

```
5```

# 题解

## 作者：vani_prcups (赞：17)

标签里说的广搜实际上深搜也是可以做的……

代码的主要部分是深搜，visited数组用来标记到达过的点（没有这个会死循环），b数组用来标记可以到达（已经开灯）的点。

另外，为了防止暴力找边（100\*100），我很快乐的用了二维邻接表（话说我已经被链式向前星洗脑了，建表就用len、head数组和a数组。

有一个很重要的操作，就是当点亮一间房时，如果这间房旁边有已到达的点，就直接深搜这间被点亮的房间（相当于完成之前那间房没有完成的任务）。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
inline int getint()
{
    int s=0,w=1;
    char ch=getchar();
    while (ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
    if (ch=='-')w=-w,ch=getchar();
    while (ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return s*w;
}
using namespace std;
struct node
{
    int tx,ty,nt;
}a[200005];
int n,m,head[105][105],len,b[105][105],v[105][105],c;
void dfs(int x,int y)
{
    if (x<1||x>n||y<1||y>n)return;
    v[x][y]=1;
    for (int i=head[x][y];i!=0;i=a[i].nt)
    if (b[a[i].tx][a[i].ty]==0)
    {
        b[a[i].tx][a[i].ty]=1;
        c++;
        if (v[a[i].tx+1][a[i].ty]==1||v[a[i].tx][a[i].ty+1]==1||v[a[i].tx-1][a[i].ty]==1||v[a[i].tx][a[i].ty-1]==1)dfs(a[i].tx,a[i].ty);
    }
    if (v[x+1][y]==0&&b[x+1][y]==1)dfs(x+1,y);
    if (v[x][y+1]==0&&b[x][y+1]==1)dfs(x,y+1);
    if (v[x-1][y]==0&&b[x-1][y]==1)dfs(x-1,y);
    if (v[x][y-1]==0&&b[x][y-1]==1)dfs(x,y-1);
}
int main()
{
    n=getint();
    m=getint();
    int fx,fy,tx,ty;
    for (int i=1;i<=m;i++)
    {
        fx=getint();
        fy=getint();
        tx=getint();
        ty=getint();
        a[++len].tx=tx;
        a[len].ty=ty;
        a[len].nt=head[fx][fy];
        head[fx][fy]=len;
    }
    b[1][1]=1;
    c=1;
    dfs(1,1);
    printf("%d",c);
}
```

---

## 作者：BoAn (赞：11)

### • 基本思路
很明显，这是一篇 BFS 的题，但 BFS 能解决的 DFS 也可以。

从 $(1,1)$ 房间开始，上下左右搜，把当前房间能打开的灯都打开，然后继续搜。

但是我们来看一下下面这个样例：
```cpp
3 4
1 1 1 2
1 2 2 1
2 1 1 3
1 3 3 1
```
我们可以模拟到，当 $(2,1)$ 打开 $(1,3)$ 之后，$(2,1)$ 周围没有开着灯的房间，DFS 就结束了，我们没法再回到 $(1,3)$ 打开 $(3,1)$，所以按照这个思路，最后会输出 $4$，但答案是 $5$。
```cpp
1 1 1
1 0 0
X 0 0
```
很多 dalao 都表示应该往回搜，但本蒟蒻不是很懂其原理，实际上我们可以反复 DFS，期间 $mark$ 不清零，然后将这一次的结果和上一次结果比较，如果相同就证明没有漏网之鱼，可以直接输出；不相同就更新为这一次结果，然后继续执行以上操作。

同样的样例，在第二次 DFS 搜到 $(1,3)$ 的时候，就可以打开 $(3,1)$，同理，如果有 $(4,1)$ 就进行第三次 DFS。


------------
### • 具体代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,k,x,y,a,b,ans,ans1;
//ans记录能打开灯的房间数量 
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
bool mark[101][101],z[101][101];
//mark[i][j]表示(i,j)房间的电灯状态
//z[i][j]表示(i,j)房间是否走过 
struct l{
	int x[10001],y[10001],top;
}m[101][101];
//x[i]和y[i]分别表示当前房间第i个能控制的房间坐标
//top表示当前房间能控制的房间数量
void dfs(int x,int y){
	for(int i=1;i<=m[x][y].top;i++)
		mark[m[x][y].x[i]][m[x][y].y[i]]=1;
        //将当前房间能打开的都打开 
	for(int i=0;i<4;i++)
		if(x+dx[i]>=1&&x+dx[i]<=n&&y+dy[i]>=1&&y+dy[i]<=n&&mark[x+dx[i]][y+dy[i]]&&!z[x+dx[i]][y+dy[i]]){
			z[x+dx[i]][y+dy[i]]=1;
			dfs(x+dx[i],y+dy[i]);
		}
}
int main(){
	mark[1][1]=1,z[1][1]=1;
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		cin>>x>>y>>a>>b;
		m[x][y].x[++m[x][y].top]=a,m[x][y].y[m[x][y].top]=b;
		//记录(x,y)房间能控制的房间坐标
	}
	dfs(1,1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(mark[i][j])ans++;
			//统计所有开着灯的房间数量 
	while(ans!=ans1){
		ans1=ans;//ans1存储上一次DFS的值 
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				z[i][j]=0;
		dfs(1,1); 
		ans=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(mark[i][j])ans++;
					//更新ans的值 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：JMercury (赞：11)

做这个题让我想起来一个题[P2446 [SDOI2010]大陆争霸](https://www.luogu.org/problemnew/show/P2446)。然后就用差不多的方法把这题过了~~（其实算法和spfa并没有关系吧）~~

将可以到的点按照扩展到的顺序不重复的加入一个队列，每一次进行两个操作。

1.将这个点可以扩展到的点加入队列

```cpp
for(int i=0;i<4;i++)
{
	int vx=u.x+dx[i],vy=u.y+dy[i];
	///这个点在图内、没加入过队列、而且灯开了，那么加入队列
	if(Inside(vx,vy) && !vis[vx][vy] && MAP[vx][vy]) 
    q.push((P){vx,vy}),vis[vx][vy]=true; 
}
```

2.将他所管理的房间的灯打开，并检查他所管理的房间现在能不能进入
```cpp
for(int i=0;i<Lamp[u.x][u.y].size();i++)
{
	P v=Lamp[u.x][u.y][i];
	if(vis[v.x][v.y] || MAP[v.x][v.y]) continue; ///如果进入了队列或者灯已经开了，那就不考虑了
	MAP[v.x][v.y]=true;ans++; ///打开灯，答案加1
    for(int i=0;i<4;i++)
    if(vis[v.x+dx[i]][v.y+dy[i]]) ///对于他所管理的房间，如果这个房间四周有房间可以走到，那么这个房间也可以被走到，加入队列
    {
		q.push((P){v.x,v.y}),vis[v.x][v.y]=true;
		break;
	}
}
```

附上完整AC代码

```cpp
#include<bits/stdc++.h>
const int maxn=110;
using namespace std;

int n,m,ans;
struct P
{
    int x,y;
};
bool MAP[maxn][maxn],vis[maxn][maxn]; ///MAP记录是否开灯，vis记录是否加入了队列
vector<P> Lamp[maxn][maxn]; ///记录每个房间所管理的房间
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};

bool Inside(int x,int y)
{
    return x>=1 && x<=n && y>=1 && y<=n;
}

void spfa()
{
    queue<P> q;q.push((P){1,1});vis[1][1]=true;MAP[1][1]=true;ans++;
    while(!q.empty())
    {
        P u=q.front();q.pop();
        for(int i=0;i<4;i++)
        {
            int vx=u.x+dx[i],vy=u.y+dy[i];
            if(!Inside(vx,vy) || vis[vx][vy]) continue;
            if(MAP[vx][vy]) q.push((P){vx,vy}),vis[vx][vy]=true;
        }
        for(int i=0;i<Lamp[u.x][u.y].size();i++)
        {
            P v=Lamp[u.x][u.y][i];
            if(vis[v.x][v.y] || MAP[v.x][v.y]) continue;
            MAP[v.x][v.y]=true;ans++;
            for(int i=0;i<4;i++)
            if(vis[v.x+dx[i]][v.y+dy[i]])
            {
	            q.push((P){v.x,v.y}),vis[v.x][v.y]=true;
                break;
            }
        }
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,x1,Y1,x2,y2;i<=m;i++)
    {
        scanf("%d%d%d%d",&x1,&Y1,&x2,&y2);
        Lamp[x1][Y1].push_back((P){x2,y2});
    }
    spfa();
    printf("%d",ans);
    return 0;
}
```

---

## 作者：bobxie (赞：6)

### 不得不说，这是一道很神奇的题目，至少对本蒟蒻来说是这样的    
现在来分析一下题目，题目要求我们求出咱家农夫约翰能开多少个房间的灯，然而约翰还是那个怕黑的约翰，房间是黑的就不去了。。。（比我还胆小）   
这种类似于走迷宫的题目，我们第一时间想到的当然是搜索，并且，对于这种题目，我们会发现，如果用dfs，搜索树的深度可能会很深（有些dalao一优化，就跟啥都没有似的）。我们来考虑用bfs。            
#### 首先，bfs走迷宫当然是上下左右求之遍，但我们会注意到，我们搜到这个房间时，这个房间的灯可能还没有开，可是这不代表之后会不会开。
#### 我们再仔细想想，不难想到在房间之间连边这种做法。定义如果房间(x1,y1)有房间(x2,y2)的灯的开关，则连一条从(x1,y1)指向(x2,y2)的边。这样我们在跑bfs时就只要在走完正常操作（上下左右）以后再把该点能连到的点（没有访问过）也加入队列就好了。
##### 统计能点亮多少个房间的灯这种事情怎么写都好，这里就不唠叨了
`bobxie温馨提示：注意题目要我们求的是能开多少个房间的灯，而不是能走到多少个房间。（来自本蒟蒻的亲身体验）`
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn=200;
struct data
{
    int nxt,to1,to2;
}e[400010];
int head[maxn][maxn],tot;
void add(int x1,int y1,int x2,int y2)
{
    e[++tot]=(data){head[x1][y1],x2,y2};
    head[x1][y1]=tot;
}
struct note
{
    int x,y;
};
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
int used[maxn][maxn],n,m,mp[maxn][maxn];
int bfs()
{
    int cnt=1;
    queue<note> Q;
    Q.push((note){1,1});
    mp[1][1]=used[1][1]=1;
    while (!Q.empty())
    {
        note top=Q.front();
        Q.pop();
        for (int i=0;i<4;++i)
        {
            int xx=top.x+dx[i],yy=top.y+dy[i];
            if (xx<1||yy<1||xx>n||yy>n||used[xx][yy]) continue;
            if (!mp[xx][yy]) continue;
            used[xx][yy]=1;
            Q.push((note){xx,yy});
        }
        for (int i=head[top.x][top.y];i;i=e[i].nxt)
        {
            int xx=e[i].to1,yy=e[i].to2;
            if (!mp[xx][yy])
            {
            	cnt++;
            	mp[xx][yy]=1;
                if (!used[xx][yy]&&(used[xx-1][yy]||used[xx+1][yy]||used[xx][yy+1]||used[xx][yy-1]))
                {
                    Q.push((note){xx,yy});
                    used[xx][yy]=1;
                }
            }
        }
    }
    return cnt;
}
int main()
{
//	freopen("xie.in","r",stdin);
//	freopen("xie.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;++i)
    {
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        add(a,b,c,d);
    }
    printf("%d\n",bfs());
//    fclose(stdin);
//    fclose(stdout);
    return 0;
}
```
### 无耻宣扬博客[bobxie](https://www.luogu.org/blog/UnacceptedBlog/)

---

## 作者：chenxuanting (赞：3)

## 题外话

完成总时长：6个月（断断续续的）

终于A了 ~~我太难了~~

**好了切入正题**

## 思路

1. 使用BFS ~~写DFS写挂了~~

2. 用vector存储在某个房间能开的灯

3. 用vis数组判断是否访问过，状态分0,1 共两种

4. 用light数组判断是否开了灯，状态分0,1,2 共三种。其中0表示未开灯，1表示开灯且这个房间访问过，2表示开灯但没访问过

**注：这里为什么开灯没访问过呢?因为你只是开灯了，但是如果你到达不了也没用**

5. **使用快读**读入数据 ~~要不然我这个乌龟程序会被卡住~~

6. 使用正常BFS

7. 最后用for循环扫描全图中 light[x][y]!=0 的房间计入总数

8. 输出答案

## 下面是最容易忽略的点 

**题目：求的是能打开多少灯而不是能到多少个房间**

~~易不易错我不知道 反正我是错了~~

## 代码部分

```
#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int n,m;
struct node
{
	int x,y;
};
vector<node> a[105][105];
int vis[105][105],light[105][105];
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int ans;
void read(int &x)
{
	int fh=1;
	char s;
	x=0;
	s=getchar();
	if(s<'0'||s>'9'){
		if(s=='-'){
			fh=-1;
		} 
	}else{
		x=int(s-'0');
	}
	while(s=getchar()){
		if(s>='0'&&s<='9'){
			x*=10;
			x+=(int)(s-'0');
		}else{
			break;
		}
	}
	x*=fh;
}
void bfs()
{
	queue<node> q;
	q.push((node){1,1});
	while(!q.empty()){
		node cur=q.front();
		q.pop();
		if(light[cur.x][cur.y]==2){
			int tf=0;
			for(int i=0;i<4;i++){
				int nowx=cur.x+dx[i];
			    int nowy=cur.y+dy[i];
			    if(vis[nowx][nowy]==1){
			    	tf=1;
			    	break;
				}
			}
			if(tf==0){
				continue;
			}
			vis[cur.x][cur.y]=1;
		}
		light[cur.x][cur.y]=1;
		for(int i=0;i<a[cur.x][cur.y].size();i++){
			node now=a[cur.x][cur.y][i];
			if(vis[now.x][now.y]==1){
				continue;
			}
			light[now.x][now.y]=2;
			q.push(now);
		}
		for(int i=0;i<4;i++){
			int nowx=cur.x+dx[i];
			int nowy=cur.y+dy[i];
			if(nowx>n||nowy>n||vis[nowx][nowy]==1||light[nowx][nowy]==0){
				continue;
			}
			light[nowx][nowy]=1;
			vis[nowx][nowy]=1;
			q.push((node){nowx,nowy});
		}
	}
}
int main()
{
	read(n);
	read(m);
	light[1][1]=1;
	for(int i=1;i<=m;i++){
		int x1,x2,y1,y2;
		read(x1);
		read(x2);
		read(y1);
		read(y2);
		a[x1][x2].push_back((node){y1,y2});
	}
	bfs();
	for(int i=1;i<=n;i++){
		for(int i1=1;i1<=n;i1++){
			if(light[i][i1]!=0){
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

## 注释

1. 注意要开始把light[1][1]初始化为1

2. 注意vis数组更改为1的顺序，如果是上下左右走的时候要更改为1，如果只是打开灯就不用了

3. 关于打开的灯后面会被打开的问题

```
if(light[cur.x][cur.y]==2){
			int tf=0;
			for(int i=0;i<4;i++){
				int nowx=cur.x+dx[i];
			    int nowy=cur.y+dy[i];
			    if(vis[nowx][nowy]==1){
			    	tf=1;
			    	break;
				}
			}
			if(tf==0){
				continue;
			}
			vis[cur.x][cur.y]=1;
		}
```

这个是在判断他这个房间周围是否有访问过的

有的话那么这个现在被开灯的房间就可以被访问

然后他可以打开在他这个房间内可以打开的灯

4. 关于打开的灯入队的问题

直接放入队列中，判断是否能访问就是第三项了

## 后记

莫抄袭，没了AC记录，空悲切

如果有疑问可以向我提出

**不保证我的代码是完全正确的，如有问题请帮我改一下**

---

## 作者：WCG2025 (赞：3)

还有一个月就退役了，在退役之前再写一篇题解吧



------------
 
这道题很明显是一道广搜的板子题，但是分析一下题目，有三个难点：

1.题目问的是最多能打开灯的房间数，而不是最多能走到的房间数。

2.对于使房间开灯的处理存在一些困难。

3.bessie可以往回走，即可以回溯

解决:

  广搜遍历，运用哈希处理开灯房间，并在开灯时判断开灯房间能否遍历到。
  
  
  如何哈希处理？
  
```cpp
inline void adde(int x,int y,int x1,int y1)
{
 	int s1=x*101+y;
	int s2=x1*101+y1;
    	edge[++cnt].v=s2;
    	edge[cnt].next=head[s1];
    	head[s1]=cnt;
}
```
运用链式前向星的思想来存储下两个映射关系

如何解密？

```cpp
for(int i=head[u.x*101+u.y];i;i=edge[i].next)
{
	int v=edge[i].v;
	l[v/101][v-(v/101)*101]=1;
	check(v/101,v-(v/101)*101);
}	
```
利用计算机除法取整的特性，就还原了这一信息（巧妙至极）

当然，也得益于这道题数据n<100的特性，仅提供一个思路，不保证使用于其他题目

完整代码

```cpp
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<climits>
#include<queue>
#include<map>
#define inf 1e18
#define int long long
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch<='9'&&ch>='0')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int n,m;
struct node
{
	int x;
	int y;
};
bool vis[105][105];
int l[105][105];
int dx[]={0,0,0,-1,1};
int dy[]={0,-1,1,0,0};
queue<node> q;
int ans;
int cnt;
struct nope
{
	int v;
	int next;
}edge[200005];
int head[12000];
inline void adde(int x,int y,int x1,int y1)
{
 	int s1=x*101+y;
	int s2=x1*101+y1;
    	edge[++cnt].v=s2;
    	edge[cnt].next=head[s1];
    	head[s1]=cnt;
}
inline void check(int x,int y)//这一个函数用于判断刚把灯打开的点是否能够遍历到
{//存在这样一种情况 当前开灯的点能够走到，但与其相邻的点已经遍历过
	if(vis[x][y])//就用这个函数去判断这个刚打开灯的点能否入队
	return ;
	for(int i=1;i<=4;i++)
	{
		int nx=dx[i]+x;
		int ny=dy[i]+y;
		if(vis[nx][ny]==1&&l[nx][ny]==1&&nx>=1&&nx<=n&&ny>=1&&ny<=n)
		{//如果相邻点能够走到，那么这个点就能够入队
			node n;
			n.x=x;
			n.y=y;
			q.push(n);
			vis[x][y]=1;
			break;
		}
	}
}
signed main()
{
//	freopen("testdata.in","r",stdin);
//	freopen("1.out","w",stdout);
	n=read();
	m=read();
	while(m--)
	{
		int a,b,c,d;
		a=read();
		b=read();
		c=read();
		d=read();
		adde(a,b,c,d);
	}
	l[1][1]=1;
	vis[1][1]=1;
	node s;
	s.x=1;
	s.y=1;
	q.push(s);
	while(!q.empty())
	{
		node u=q.front();
		q.pop();
		for(int i=head[u.x*101+u.y];i;i=edge[i].next)
		{
			int v=edge[i].v;
			l[v/101][v-(v/101)*101]=1;
			check(v/101,v-(v/101)*101);
		}		
		for(int i=1;i<=4;i++)//广搜模板
		{
			int nx=dx[i]+u.x;
			int ny=dy[i]+u.y;
			if(vis[nx][ny]==0&&l[nx][ny]==1&&nx>=1&&nx<=n&&ny>=1&&ny<=n)
			{
				node n;
				n.x=nx;
				n.y=ny;
				q.push(n);
				vis[nx][ny]=1;
			}
		}
	}
	for(int i=1;i<=n;i++)//N方遍历查询已经开灯的点
	for(int j=1;j<=n;j++)
	if(l[i][j]==1)
	++ans;
	cout<<ans;
	return 0;
}
```


---

## 作者：zylll (赞：3)

被此题卡了许久。。终于A了。还是我太菜了。。。

对于储存暴力选用**二维vector+pair**。

考虑使用广搜。

对于队列中的点，如果周围存在已经被点亮但还未入过队，则将其入队。

然后再尝试扩充这个点，如果能将其他灯点亮，统计答案；然后再判断这个新被点亮的灯周围如果有被点亮的灯，则代表可以通过其他周围的灯到达这里，则入队。

之前WA了好几次的原因就是没考虑到最后一种情况。尝试修复bug但似乎写法不太优秀。

可能语言表达有点过于生硬，不过代码还是很好了解哒

代码：

```c
#include <cstdio>
#include <iostream>
#include <cctype>
#include <cstring>
#include <vector>
#include <algorithm>
static const int MAXN=150;
static const int dirx[10]={0,1,0,-1};
static const int diry[10]={1,0,-1,0};
using namespace std;
vector<pair<int,int> > vec[MAXN][MAXN];
struct node{
    int x,y;
}q[100050];
int head,tail,ans,n,m,x1,y1,x2,y2;
bool vis[MAXN][MAXN],in[MAXN][MAXN];
inline int read(){
    int x=0;bool sign=false;
    char alpha=0;
    while(!isdigit(alpha)) sign|=alpha=='-',alpha=getchar();
    while(isdigit(alpha)) x=(x<<1)+(x<<3)+(alpha^48),alpha=getchar();
    return sign?-x:x;
}
inline bool check(int x,int y){return (x<1||x>n||y<1||y>n)?true:false;}
inline bool check1(int x,int y){
	for(int i=0;i<4;i++) if(in[x+dirx[i]][y+diry[i]]) return true;
	return false;
}
inline void bfs(){
	q[head]=(node){1,1};
	in[1][1]=1;vis[1][1]=1;
	ans=1;
	while(head<=tail){
		node now=q[head];head++;
		for(int i=0;i<4;i++){
			int dx=now.x+dirx[i],dy=now.y+diry[i];
			if(check(dx,dy)||in[dx][dy]) continue;
			if(vis[dx][dy]) in[dx][dy]=1,q[++tail]=(node){dx,dy};
		}	
		for(vector<pair<int,int> >::iterator it=vec[now.x][now.y].begin();it!=vec[now.x][now.y].end();it++){
			int nx=(*it).first,ny=(*it).second;
			if(in[nx][ny]||vis[nx][ny]) continue;
			vis[nx][ny]=1;ans++;
			if(check1(nx,ny)) in[nx][ny]=1,q[++tail]=(node){nx,ny};
		}
	}
}
int main(){
    n=read();m=read();
    for(int i=1;i<=m;i++){
        x1=read();y1=read();x2=read();y2=read();
        vec[x1][y1].push_back(make_pair(x2,y2));
    }
    bfs();
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：XG_Zepto (赞：3)

这道题调了一天终于在@DOFY dalao的帮助下A掉了

不过我的代码好像比DOFY的更优一些

### 用时和内存

![](https://cdn.luogu.com.cn/upload/pic/12603.png)

评测记录：

https://www.luogu.org/record/show?rid=5194011

### 思路

这道题如果使用常规BFS，当我们打开队首房间中的开关，有可能点亮与已经出队房间相邻的房间的灯，但由于已经出队，不可访问，就会WA掉。

所以我们考虑这种算法：

我们将所有可访问和点亮的房间都扔进队列，对于队首，如果相邻的房间有的已经被tag数据标记可访问，那么将其也标记可访问。

然后，寻找队首元素可点亮的房间，找到尚未被点亮（**av**ailable），尚未被标记为可访问并且尚未被点亮的房间，那么将其入队、点亮、标记为已访问，并且将答案sum加上这个房间。

最后，我们考虑将与队首元素相邻但未标记为可访问、已访问但是已经被点亮的房间加入队尾，并将其标记为已访问。

### 时间复杂度

由于每个房间最多可被与其相邻的房间四次入队，并且我们的算法遍历了所有的开关，时间复杂度最大为 \*O(n)=4n^2+m\*

### 丑陋的代码

注意看注释，有问题请留言。(。・`ω´・)

~~注意不要复制代码，会有奇奇怪怪的错误~~


    
    
    
```cpp
    #include <bits/stdc++.h>
    using namespace std;
    int num,n,m,head[200001],q[200001],sum,dir[4];
    bool av[200001],visited[200001],tag[200001];
    //sum储存答案，q为队列，dir为四个方向，av为available的缩写qwq
    struct Edge{
        int t,next;
    }l[200001];
    void addedge(int f,int t){
        l[++num].next=head[f];
        l[num].t=t;
        head[f]=num;
    }
    //使用前向星存图
    bool check(int b,int a){
        if (b%n==0&&a-1==b) return 0;
        if (b%n==1&&a+1==b) return 0;
        if (a<1) return 0;
        if (a>n*n) return 0;
        return 1;
    }
    //由于进行了降维打击（压维），这里我们使用一个函数检验从b到a的行动是否有效
    void bfs(int startx,int starty){
        int h=1,t=1;
        int sn=startx+(starty-1)*n;
        av[sn]=1;
        q[h]=sn;
        visited[sn]=1;
        tag[sn]=1;
            while (h<=t){
            if (tag[q[h]+n]&&check(q[h],q[h]+n)||tag[q[h]-n]&&check(q[h],q[h]-n)||tag[q[h]+1]&&check(q[h],q[h]+1)||tag[q[h]-1]&&check(q[h],q[h]-1)){
                tag[q[h]]=1;
                //标记为可访问
                for (int k=head[q[h]];k;k=l[k].next)
                if (!tag[l[k].t]&&!av[l[k].t]&&!visited[l[k].t])
                av[l[k].t]=1,q[++t]=l[k].t,visited[l[k].t]=1,sum++;
                //前向星遍历
                for (int i=0;i<4;i++){
                 int nn=q[h]+dir[i];
                //生成上下左右四个房间的编号
                if (!check(q[h],nn)) continue;
                //检查是否相邻
                if (!tag[nn]&&!visited[nn]&&av[nn])
                q[++t]=nn,visited[nn]=1;
                //将相邻房间入队}
        }
        visited[q[h]]=0;
        h++;
        }
    }
    int main(){
        scanf("%d%d",&n,&m);
        dir[0]=1，dir[1]=-1，dir[2]=n，dir[3]=-1*n;
        //四个方向的编号生成
        int x1,x2,y1,y2;
        for (long long i=1;i<=m;i++) head[i]=-1;
        for (int i=1;i<=m;i++){
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            int a=(x1-1)*n+y1;
            int b=(x2-1)*n+y2;
            //降维
            addedge(a,b);
        }
        bfs(1,1);
        printf("%d",sum);
        return 0;
}
```

---

## 作者：Twilight_ (赞：2)

形成的思路：广搜遍历可以到达的点，并打开相应的灯。

难点：如果一条路走下去，会导致有现在打开灯的房间在之前被当做‘不能到达’而舍去。


所以我们使用三条队列：q,q1,q2。

q中记录能够到达且灯已经打开的房间，常规bfs即可。

q1中记录能够到达但灯没有打开的房间。

q2充当临时容器。


当遍历完q中元素之后，我们再遍历q1，将能够进队的元素进队；

不能进队的元素先寄存在q2中，之后再塞回q1。


注意：要用数组记录一个点是否进过队，避免重复搜索一样的点。


AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 115
int mx[6]={0,0,0,1,-1};
int my[6]={0,1,-1,0,0};
int ans,vis[maxn][maxn],mark1[maxn][maxn],l[maxn][maxn],cnp=1,head[maxn][maxn],n,m;
struct node
{
    int x,y;
};
queue<node>q1,q2,q;
struct edge
{
    int x,y,tx,ty,last;
}E[2000000];
void add(int x,int y,int x1,int y1)
{
    E[cnp].last=head[x][y];
    E[cnp].tx=x1,E[cnp].ty=y1;
    head[x][y]=cnp++;
}
void search()
{
    while(!q.empty())
    {
        node tem=q.front();
        q.pop();
        for(int i=head[tem.x][tem.y];i;i=E[i].last)
        {
            int x=E[i].tx,y=E[i].ty;
            if(!l[x][y])l[x][y]=1,ans++;
        }
        for(int i=1;i<=4;i++)
        {
            int x=tem.x+mx[i],y=tem.y+my[i];
            node pre;pre.x=x,pre.y=y;
            if(x<1||x>n||y<1||y>n)continue;
            if(!l[x][y])
            {
                if(!mark1[x][y]){q1.push(pre);mark1[x][y]=1;}
            }
            else if(!vis[pre.x][pre.y]){q.push(pre);vis[pre.x][pre.y]=1;}
        }
    }
    while(!q1.empty())
    {
        node tem=q1.front();
        q1.pop();
        if(!vis[tem.x][tem.y]&&l[tem.x][tem.y])q.push(tem);
        else q2.push(tem);
    }
    while(!q2.empty())
    {
        node tem=q2.front();
        q2.pop(),q1.push(tem);
    }
    if(!q.empty())search();
}
int read()
{
    int x=0;
    char c;
    c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x;
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++)
    {
        int x=read(),y=read(),x1=read(),y1=read();
        add(x,y,x1,y1);
    }
    l[1][1]=1;
    node st;st.x=1,st.y=1;
    vis[1][1]=1;
    q.push(st);
    search();
    printf("%d",ans+1);
    return 0;
}
```

---

## 作者：dph754132771 (赞：2)

/\*
过法：加了补丁的BFS

思路：BFS节点入列（可以把没开灯的房间视为墙，开了灯的视为路，这就变成了地图会变化的迷宫问题）

比正常的迷宫问题多了一个特点就是现在到达的地方可能会打开之前可能到达的（但没开灯）房间

所以，每次开灯的时候加上补丁——搜索开灯房间的四个方向上是否有可行房间

为什么这个方法是对的呢？ 假设现在我们走到了某点，打开了某些灯，那么情况无非两种

1 被打开的房间现在可行 2 被打开的房间现在不可行

而第1种情况又分两种情况，1 被打开的房间连接当前搜索房间 2 被打开的房间连接之前的某个可行房间

正常的BFS可以解决 1-1以及2的情况 所以补丁的作用就是解决1-2的情况。。。

接下来上代码。。。。

减少代码复制，创造和谐洛谷（代码只供看不懂思路的人方便理解，或者给实在打不出代码的人帮助）

\*/
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
struct asd{
    int x,y;
}to[200005],q[200005];//坐标类型，邻接表to及队列 
int qr,ql;//队列 
int n,m,x1,x2,y1,y2,ans;//只是输入用与输出用 
int head[105][105],next[200005];//邻接表 
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};//四个方向 
bool v[105][105],l[105][105];
//v-坐标是否开过开关，同时也是坐标是否可行，以及是否入列  l-坐标是否开灯 
int main(){
    scanf("%d%d",&n,&m);
    memset(head,-1,sizeof(head));
    for (int i=0;i<m;i++){
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        next[i]=head[x1][y1];
        head[x1][y1]=i;
        to[i].x=x2;
        to[i].y=y2;
    }
    memset(v,false,sizeof(v));
    memset(l,false,sizeof(l));
    v[1][1]=true;
    l[1][1]=true;
    q[qr].x=1;
    q[qr].y=1;
    qr++;//输入，初始化，邻接表构成 
    while (ql<qr){
        int x,y,k;
        x=q[ql].x;
        y=q[ql].y;
        ql++;
        k=head[x][y];//记录队头，以及当前节点邻接表表头 
        while (k!=-1){
            l[to[k].x][to[k].y]=true;//开灯 
            for (int i=0;i<=3;i++)
                if (v[to[k].x+dx[i]][to[k].y+dy[i]]&&to[k].y+dy[i]>0&&to[k].y+dy[i]<=n&&to[k].x+dx[i]>0&&to[k].x+dx[i]<=n&&!v[to[k].x][to[k].y]){
                    //判断是否出界，被开灯的房间的四个方向是否可行 当前被开灯房间是否入列 
                    q[qr].x=to[k].x;
                    q[qr].y=to[k].y;
                    v[to[k].x][to[k].y]=true;
                    qr++;//入列，标记 
                }
            k=next[k];
```
}//开灯完毕
```cpp
        for (int i=0;i<=3;i++)
            if (l[x+dx[i]][y+dy[i]]&&!v[x+dx[i]][y+dy[i]]&&y+dy[i]>0&&y+dy[i]<=n&&x+dx[i]>0&&x+dx[i]<=n){
                //判断当前搜索节点四个方向的房间是否开灯，并且是否还未入列以及是否出界 
                q[qr].x=x+dx[i];
                q[qr].y=y+dy[i];
                qr++;
                v[x+dx[i]][y+dy[i]]=true;//入列，标记 
            }
    }//BFS完毕 
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (l[i][j]) ans++;
    printf("%d",ans);//计算开灯的房间，输出 
    return 0;
}
```

---

## 作者：LDlornd (赞：1)

调了两三天终于A了这一题，~~请允许我先哭一会儿~~。。。

在此将这一题的解题思路和在做这一题时的心路历程与大家分享一下。

初看这道题，感觉就是一道搜索题，于是乎，立马有思路了：不断对原图进行搜索（BFS），碰到了房间就把该房间可以打开的灯全部打开，直到某一次搜索过后**我们没有打开任何一盏灯为止**。

这个思路是没有问题的，然而~~常识告诉我们~~，这样做肯定会TLE，于是先考虑如何去优化这一个搜索的过程：

1. 冷静分析，发现从第二次搜索开始，我们在搜索过程中事实上是搜到了一些重复的房间的，然而，很明显，因为我们曾经进到过这一个房间，并且将其能够打开的灯都打开了，所以再搜索这个房间是没有意义的。这就暗示我们：是不是可以通过某些操作来使得第二次搜索只会搜到有意义的房间呢？我们发现，一个房间是有意义的，当且仅当这个房间的灯被打开了并且我们曾经没有进到过这个房间里去。因此我们考虑使用一个数组（队列）记录在我当前这一次搜索中，打开了灯却不能走到的房间，然后下一次搜索的时候就只在这个队列里面进行搜索，这样，我们就可以保证每一个被打开了灯的房间只访问了一次。

1. 于是，现在要解决的问题就是：何时停止搜索？我一开始写的是和最开始一样，这次搜索没有开过任何一盏灯时就结束，于是后来我调我wa了的程序调了一整天才发现这个错误。我们在优化时，把那些被打开了灯的房间记录下来是因为怕目前这个房间不能走到，而在我第一次搜索完，打开了更多的灯之后，有可能这个房间就能够走到了。而如果一个房间从原本的不可走到变成可以走到，说不定又会使得另一个房间由不可走到变成可走到。所以我们在面对一个房间，首先应该判断它在目前能不能够走到，如果可以走到，就打开它可以打开房间的灯。所以，搜索的终止条件应该是：**在这一次搜索中，队列中的房间，没有任何一个房间可以被走到**。这样就可以保证不漏解了。

1. 到这里，事实上就已经可以在时限内得出答案了。但仔细思考过后，我们发现事实上还可以对目前的解法做一个小小的优化——**降维**。二维数组与一维数组的经验告诉我们，降维可以使得运算的时间更短一些。于是怎么降维呢？

我们发现：对于一个二维的地图，我们是用一个有序实数对（i，j）来表示这个地图上的一个点，而事实上我们也可以将这个地图上的点从上到下，从左到右使用1~n^2中的的数来表示这个地图上的每一个点

例如：

![luogu](https://cdn.luogu.com.cn/upload/pic/12738.png)

其中：黑框内为地图。

现在我们来说说在新的一维地图内如何进行搜索：

假设我们现在在map[i][j] (map[k])这个点

首先看看在二维地图中，我们搜索是向上、下、左、右走一步，分别对应

**map【i-1】【j】,map【i+1】【j】,map【i】【j-1】,map【i】【j+1】；**

而对于一维的地图，由于我们可以通过k=(i-1)\*n+j这样的计算方式来将（i，j）映射成1~n^2里的每一个数，因此向上、下、左、右走就分别变对应：

**map【k-n】,map【k+n】,map【k-1】,map【k+1】;**

而这会导致一个bug，在k+1或k-1的时候：**有可能跨行**，如对于上面这个图，对于6这个点不加任何判断像上面这样遍历有可能会走到7这个点，而这样的操作是非法的，因此我们在遍历时就要加上一个特判（check函数），这样的话，应该就差不多没问题了吧。

到此为止：目前我能想到的优化就是这些了，于是，就上代码吧：、

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
using namespace std;
const int MAXN=10001;//最多的点数 
int n,m,xx,yy,sp,ep,ans=1; 
int to[4];//方向数组 
int dl1[MAXN],head1=1,tail1=1; //BFS时用到的队列 
int dl2[MAXN],head2=1,tail2=1; //储存打开了灯目前却不能到达的房间的队列 
bool light_up[MAXN],vis[MAXN]; //灯是否已打开   是否这个点已经被访问过 
int indl[MAXN];                //每个点在哪个队列种（或是不在队列中） 
struct edge
{
    int v;
    edge *NEXT;
    edge() {v=0;NEXT=NULL;}
}*con[MAXN];                        //采用图的方式去存可以打开的灯的信息 
inline void ins(int start,int end)  //新的关系（加一条边） 
{
    edge *p=new(edge);
    p->v=end;
    p->NEXT=con[start];
    con[start]=p;
}
inline bool check(int nowplace)          //判断点是否能够到达 
{
    for(int i=0;i<4;++i)
    {
        int place=nowplace+to[i];
        if(place<1||place>n*n) continue;
        if(place%n==0&&to[i]==-1) continue;   //防bug 
        if(place%n==1&&to[i]==1) continue;    //防bug 
        if(vis[place]) return true;
    }
    return false;
}
inline void bfs()
{
    bool flag=false;      //判断是不是要再一次遍历 
    head2=tail2=1;   //另一个队列的初始化 
    while(head1<tail1)
    {
        int nv=dl1[head1++];indl[nv]=0;         //队首元素出队 
        if(check(nv)==false&&vis[nv]==false)    //判断目前这个房间能否被到达，或是本来就被到达过（主要是为了统一 1 这个点） 
            {dl2[tail2++]=nv;continue;}
        vis[nv]=true;flag=true;               //队列中有房间可以到达，可能会产生新的变化。 
        for(edge *p=con[nv];p;p=p->NEXT)
        {
            int vv=p->v;
            if(light_up[vv]==false)
                {light_up[vv]=true;++ans;}     //点亮关着灯的房间的灯 
            if(check(vv))                            //如果这个点能够被到达 
                if(indl[vv]==0&&vis[vv]==false)        
                    {dl1[tail1++]=vv;indl[vv]=1;}    //放到遍历的队列中去 
                else continue;
            else if(indl[vv]==0&&vis[vv]==false)      
                    {dl2[tail2++]=vv;indl[vv]=2;}    //如果不能到达，放到另外一个队列中去，待会再搜一次 
        }               //注意：在入队时只能取不在队列且未被访问过的房间，不然会导致重复搜索，甚至无限递归 
    }
    if(flag)        //如果有房间可以被到达 
    {
        for(int i=head2;i<=tail2;++i)
            dl1[i]=dl2[i];
        head1=head2;tail1=tail2;      //上三行主要是懒得写两个函数于是用队列2覆盖队列1 
        bfs();               //继续搜索 
    }
}
inline int read()   //日常读入优化 
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    return x*f;
}
int main()
{
    memset(indl,0,sizeof(indl));
    memset(light_up,0,sizeof(light_up));
    memset(vis,0,sizeof(vis));
    n=read();m=read();
    to[0]=-1*n;to[1]=1;to[2]=n;to[3]=-1;
    while(m--)
    {
        sp=(((xx=read())-1)*n+(yy=read()));  //降维操作 
        ep=(((xx=read())-1)*n+(yy=read()));     //降维操作 
        ins(sp,ep);
    }
    dl1[tail1++]=1;indl[1]=1;
    vis[1]=true;light_up[1]=true;      //以上为各种初始化 
    bfs();
    printf("%d",ans);
    return 0;
}
```
希望对大家能够有帮助，如果有什么问题，欢迎在评论区提出。


---

## 作者：xun薰 (赞：1)

我来一个最普通的搜索，没有什么技巧。

一开始做考虑少了，发现bfs遍历完队列首的元素并删去

后，可能走到其他地方又把之前的队列首周围的点亮了

就过不去了。那我就想能不能不把队列元素那么早删掉呢？

可能和骗分差不多吧，多把图遍历几遍就过了。

就是裸的搜索+骗分【逃

但是正解还是要学的

代码



    





```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#define N 102
using namespace std;
int n,m,ans=1,js;
int vis[N][N],b[N][N],ok[N][N];
int mx[4]={0,1,-1,0},
    my[4]={1,0,0,-1};
struct node{
    int x,y;
};
struct T{
    int x,y;
};
queue<T>q;
vector<node>a[N][N];
void bfs(){
    T c;c.x=1;c.y=1;q.push(c);
    vis[1][1]=true;b[1][1]=true;
    while(!q.empty()){
        T now=q.front();q.pop();js++;
        if(js==n*n*100)return; //遍历了这么多遍应该灯应该都开了吧。 
        int xx=now.x,yy=now.y;
        for(int i=0;i<a[xx][yy].size();i++){
            node g=a[xx][yy][i];
            if(b[g.x][g.y]==0)ans++;
            b[g.x][g.y]=true;
        }
        for(int i=0;i<4;i++){
            int nx=xx+mx[i],ny=yy+my[i];
            if(nx<1||nx>n||ny<1||ny>n||vis[nx][ny]||b[nx][ny]==0) continue;
            vis[nx][ny]=true;
            T tmp;tmp.x=nx;tmp.y=ny;
            q.push(tmp); 
        }
        q.push(now);
    } 
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int x,y,nx,ny;
        scanf("%d%d%d%d",&x,&y,&nx,&ny);
        node t;t.x=nx;t.y=ny;
        a[x][y].push_back(t); 
    } 
    bfs();
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Dirt、 (赞：0)

本题的难点是：

开关打开的灯所在的点可以到达，但是相邻的点已经被访问导致难以加入队列。

我们用$canv[i][j]$表示点$(i,j)$是否可以到达。

对于当前的队头，它周围的点一定可以到达。

当某盏灯被打开时，如果这个位置可以到达，就将它加入队列（相当于回到那里继续走）。

坑：所求的是能打开的灯数量而非能到达的点数量~~我之前就因为这个WA了~~

上代码~
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<queue>
#include<string>
#include<vector>
#include<map>
#define ll long long
using namespace std;
const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};
struct Button
{
	int x,y;
};//结构体存坐标 
vector<Button> edge[103][103];//vector+结构体暴力存图 
int n,m,ans=1;//(1,1)一定可以到达 
bool light[103][103],v[103][103],canv[103][103];
//light表示灯是否亮着，v表示是否已经访问过，canv表示是否可以到达 
int read()
{
	int x=0;bool f=true;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=false;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f?x:-x;
}
bool in(int x,int y)
{
	return x>=1&&x<=n&&y>=1&&y<=n;
}//判断是否在图内 
void bfs()
{
	queue<Button> q;
	int nx,ny;
	q.push((Button){1,1});
	v[1][1]=light[1][1]=canv[1][1]=true;
	while(!q.empty())
	{
		Button k=q.front();
		q.pop();
		nx=k.x,ny=k.y;
		for(int i=0;i<4;i++)
		{
			int xx=nx+dx[i],yy=ny+dy[i];
			if(!in(xx,yy)||v[xx][yy]) continue;
			canv[xx][yy]=true;//当前格子的相邻格一定能到达 
		}
		for(int i=0;i<edge[nx][ny].size();i++)
		{
			int xx=edge[nx][ny][i].x,yy=edge[nx][ny][i].y;
			if(!light[xx][yy]) ans++;//如果之前没有被打开就让答案+1 
			light[xx][yy]=true;
			if(!v[xx][yy]&&canv[xx][yy])
			{	
				q.push((Button){xx,yy});
				v[xx][yy]=true;
			}//之前没有访问过并且可以访问就加入队列 
		}
		for(int i=0;i<4;i++)
		{
			int xx=nx+dx[i],yy=ny+dy[i];
			if(!in(xx,yy)||v[xx][yy]) continue;
			if(light[xx][yy])//灯打开就加入队列 
			{
				q.push((Button){xx,yy});
				v[xx][yy]=true;
			}
		}
	}
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read(),z=read(),w=read();
		edge[x][y].push_back((Button){z,w});
		//类似邻接表，存下每个点上的开关 
	}
	bfs();
	printf("%d",ans);
	return 0;
}
```

---

## 作者：lshhhhhh (赞：0)

###**方法：如果一个房间灯亮了，那么它的旁边四个房间的可以走到，如果一个房间既可以走到里面的灯又打开，那么这个房间一定可以进去，那么里面的灯也可以打开**

###**最简单的方法，通俗易懂，伪代码如下**

```cpp
###**for(int i=1;i<=m;i++)**
###**{**
###**if(x[p[i].a][p[i].b]==1 && y[p[i].a][p[i].b]==1)**
###**{**
###**if(x[p[i].c][p[i].d]==0)k=1;**
###**x[p[i].c][p[i].d]=1;**
###**y[p[i].a-1][p[i].b]=1;**
###**y[p[i].a+1][p[i].b]=1;**
###**y[p[i].a][p[i].b-1]=1;**
###**y[p[i].a][p[i].b+1]=1;**
###**}**
###**if(x[p[i].c][p[i].d]==1 && y[p[i].c][p[i].d]==1)**
###**{**
###**y[p[i].c-1][p[i].d]=1;**
###**y[p[i].c+1][p[i].d]=1;**
###**y[p[i].c][p[i].d-1]=1;**
###**y[p[i].c][p[i].d+1]=1;**
###**}**
###**}**
###**if(k==0)break;**
###**}**
###**for(int i=1;i<=n;i++)**
###**{**
###**for(int j=1;j<=n;j++)**
###**{**
###**if(x[i][j]==1)ans++;**
###**}**
###**}**

```

---

