# [USACO07FEB] Silver Lilypad Pond S

## 题目描述

为了让奶牛们娱乐和锻炼，Famer John 建造了一个美丽的池塘。这个长方形的池子被分成了 $M \times N$ 个方格（$1 \le M,N \le 30$）。一些格子是坚固得令人惊讶的莲花，还有一些格子是岩石，其余的只是美丽、纯净、湛蓝的水。

Bessie 正在练习芭蕾舞，她站在一朵莲花上，想跳到另一朵莲花上去，她只能从一朵莲花跳到另一朵莲花上，既不能跳到水里，也不能跳到岩石上。

Bessie 的舞步很像象棋中的马步：每次总是先横向移动一格，再纵向移动两格，或先纵向移动两格，再横向移动一格。最多时，Bessie 会有八个移动方向可供选择。

约翰一直在观看 Bessie 的芭蕾练习，发现她有时候不能跳到终点，因为中间缺了一些荷叶。

于是他想要添加几朵莲花来帮助 Bessie 完成任务。一贯节俭的 John 只想添加最少数量的莲花，当然，莲花不能放在石头上。

请帮助 John确定必须要添加的莲花的最少数量。在添加莲花最少的基础上，确定 Bessie 从起点跳到目标需要的最少步数。最后，确定满足添加的莲花数量最少时，步数最少的路径条数。

## 说明/提示

池塘分成四行八列，贝西的起点在第四行第一列，想去的终点在第三行第六列，池塘里一共有五朵莲花和一块石头。

最少要加两朵莲花，位置如 `x` 所示：

```
0 0 0 1 0 0 0 0    0 0 0 1 0 0 0 0 
0 x 0 0 0 2 0 1    0 0 0 0 0 2 0 1 
0 0 0 0 x 4 0 0    0 0 x 0 x 4 0 0 
3 0 0 0 0 0 1 0    3 0 0 0 0 0 1 0 
```

贝西至少要跳六步，两种不同的跳法如下：

```
0 0 0 C 0 0 0 0    0 0 0 C 0 0 0 0 
0 B 0 0 0 2 0 F    0 0 0 0 0 2 0 F 
0 0 0 0 D G 0 0    0 0 B 0 D G 0 0 
A 0 0 0 0 0 E 0    A 0 0 0 0 0 E 0  
```

## 样例 #1

### 输入

```
4 8 
0 0 0 1 0 0 0 0 
0 0 0 0 0 2 0 1 
0 0 0 0 0 4 0 0 
3 0 0 0 0 0 1 0 
```

### 输出

```
2
6
2```

# 题解

## 作者：温栀槿 (赞：11)

首先，想的是3遍BFS直接求解。

但是发现前两问很好求解，但是如果到第三个问题怎么跑出来都比答案大，

因为一个点可能被增加路径后到它下一个点，之前的路径数会被重复统计。

所以f[ax][ay]+=f[x][y]应该改为f[ax][ay]++，这样就保证每次只会多出一条新的路径。

注意细节实现，同时bfs时开inq[]数组（我的ch[]数组）记录是否在队内。

如果不加，那每个点会被访问多次，导致2个点TLE。

代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mp make_pair

const int N=35;

ll dp[N][N],dis[N][N],f[N][N];

int n,m;

int sum;

int sx,sy,tx,ty;

int vis[N][N]; 

int dx[10]={1,-1,2,-2,1,-1,2,-2},dy[10]={2,2,1,1,-2,-2,-1,-1};

bool fg=0,ch[N][N];

queue<pair<int,int> > q,q1,q2;

void bfs(){
    while(!q.empty()){
        int x=q.front().first;
        int y=q.front().second;
        ch[x][y]=0;
        q.pop();
    for(int i=0;i<=7;i++){
        int ax=x+dx[i],ay=y+dy[i];
        int sum=0;
        if(ax>n||ay>m) continue;
        if(ax<=0||ay<=0) continue;
        if(vis[ax][ay]==2) continue;
        if(dp[ax][ay]>dp[x][y]+vis[ax][ay]){
            dp[ax][ay]=dp[x][y]+vis[ax][ay];
            if(ax==tx&&ay==ty) continue;
            if(ch[ax][ay]) continue;
            q.push(mp(ax,ay));
            ch[ax][ay]=1;
        }
    }
    }
}


void bfs2(){
    while(!q1.empty()){
        int x=q1.front().first;
        int y=q1.front().second;
        ch[x][y]=0;
        q1.pop();
    for(int i=0;i<=7;i++){
        int ax=x+dx[i],ay=y+dy[i];
        int sum=0;
        if(ax>n||ay>m) continue;
        if(ax<=0||ay<=0) continue;
        if(vis[ax][ay]==2) continue;
        if(dp[ax][ay]!=dp[x][y]+vis[ax][ay]) continue;
        if(dis[x][y]+1>dis[ax][ay]) {
            continue;
        }
        dis[ax][ay]=dis[x][y]+1;
        if(ch[ax][ay]) continue;
        q1.push(mp(ax,ay));
        ch[ax][ay]=1;
//		f[ax][ay]+=f[x][y];
    }
}
}

void bfs3(){
    while(!q2.empty()){
        int x=q2.front().first;
        int y=q2.front().second;
        ch[x][y]=0;
        q2.pop();
    
    for(int i=0;i<=7;i++){
        int ax=x+dx[i],ay=y+dy[i];
        int sum=0;
        if(ax>n||ay>m) continue;
        if(ax<=0||ay<=0) continue;
        if(vis[ax][ay]==2) continue;
        if(dis[x][y]+1!=dis[ax][ay]) {
            continue;
        }
        if(dp[x][y]+vis[ax][ay]!=dp[ax][ay]) continue;
//		dis[ax][ay]=stp+1;
        f[ax][ay]+=f[x][y];
        if(ax==tx&&ay==ty) continue;
        if(ch[ax][ay]) continue;
        q2.push(mp(ax,ay));
        ch[ax][ay]=1;
    }
}
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int p;
            scanf("%d",&p);
            if(p==3) {
                sx=i,sy=j;
                vis[i][j]=0;
            }
            if(p==4){
                tx=i,ty=j;
                vis[i][j]=0;
            }
            if(p==1) vis[i][j]=0;
            if(p==0) vis[i][j]=1;
            if(p==2) vis[i][j]=2; 
        }
    }
    memset(dp,99,sizeof(dp));
    memset(dis,99,sizeof(dis));
    memset(ch,0,sizeof(ch));
//	cout<<dp[1][1];
    dp[sx][sy]=0;
    q.push(mp(sx,sy)); 
    bfs();
    if(dp[tx][ty]==dp[0][0]) {
        printf("-1\n");
        return 0;
    }
    else printf("%lld\n",dp[tx][ty]);
    dis[sx][sy]=0;
    memset(ch,0,sizeof(ch));
    q1.push(mp(sx,sy)); 
    bfs2();
    printf("%lld\n",dis[tx][ty]);
    f[sx][sy]=1;
    memset(ch,0,sizeof(ch));
    q2.push(mp(sx,sy));
    bfs3();
    printf("%lld\n",f[tx][ty]);
}
```



第二种就是在一遍bfs种直接处理答案，

考虑如果荷花数更优，直接把（x,y）的信息给(ax,ay)

如果荷花数相同，但步数更优，同上

如果两个都相同，f[ax][ay]+=f[x][y]（方案数）

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mp make_pair

const int N=35;

ll dp[N][N],dis[N][N],f[N][N];

int n,m;

int sum;

int sx,sy,tx,ty;

int vis[N][N]; 

int dx[10]={1,-1,2,-2,1,-1,2,-2},dy[10]={2,2,1,1,-2,-2,-1,-1};

bool fg=0,ch[N][N];

queue<pair<int,int> > q;

void bfs(int x,int y){
    while(!q.empty()){
        int x=q.front().first;
        int y=q.front().second;
        ch[x][y]=0;
        q.pop();
    for(int i=0;i<=7;i++){
        bool fg=0;
        int ax=x+dx[i],ay=y+dy[i];
        int sum=0;
        if(ax>n||ay>m) continue;
        if(ax<=0||ay<=0) continue;
        if(vis[ax][ay]==2) continue;
        if(dp[ax][ay]>dp[x][y]+vis[ax][ay]){
            dp[ax][ay]=dp[x][y]+vis[ax][ay];
            dis[ax][ay]=dis[x][y]+1;
            f[ax][ay]=f[x][y];
            if(ax==tx&&ay==ty) continue;
            fg=1;
        }
        else if(dp[ax][ay]==dp[x][y]+vis[ax][ay]&&dis[ax][ay]>dis[x][y]+1){
            dp[ax][ay]=dp[x][y]+vis[ax][ay];
            dis[ax][ay]=dis[x][y]+1;
            f[ax][ay]=f[x][y];
            if(ax==tx&&ay==ty) continue;
            fg=1;	
        }
        else if(dp[ax][ay]==dp[x][y]+vis[ax][ay]&&dis[ax][ay]==dis[x][y]+1){
            f[ax][ay]+=f[x][y];
            if(ax==tx&&ay==ty) continue;
            fg=1;
        }
        if(fg&&!ch[ax][ay]){
            q.push(mp(ax,ay));
            ch[ax][ay]=1;
        }
    } 
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int p;
            scanf("%d",&p);
            if(p==3) {
                sx=i,sy=j;
                vis[i][j]=0;
            }
            if(p==4){
                tx=i,ty=j;
                vis[i][j]=0;
            }
            if(p==1) vis[i][j]=0;
            if(p==0) vis[i][j]=1;
            if(p==2) vis[i][j]=2; 
        }
    }
    memset(dp,99,sizeof(dp));
    memset(dis,99,sizeof(dis));
//	cout<<dp[1][1];
    dp[sx][sy]=0;
    dis[sx][sy]=0;
    f[sx][sy]=1;
    q.push(mp(sx,sy));
    ch[sx][sy]=1;
    bfs(sx,sy);
    if(dp[tx][ty]==dp[0][0]) {
        printf("-1\n");
        return 0;
    }
    else printf("%lld\n",dp[tx][ty]);
    printf("%lld\n",dis[tx][ty]);
    printf("%lld\n",f[tx][ty]);
}
```

---

## 作者：dz_ice (赞：5)

看到题解中跑了三遍bfs，码量真的是十分惊人，而且有tle的风险。（~~不过本题的数据范围很水~~）其实可以简单一点，我的做法跑一遍bfs即可解决这个问题，把问题的三个答案压缩到一个$dis$数组里

```
long long dis[33][33][4];
```
$dis[i][j][1]$代表到点$(i,j)$需要添加的莲花的最少数目

$dis[i][j][2]$代表在添加莲花最少的基础上，到点$(i,j)$需要的最少步数

$dis[i][j][3]$代表在添加莲花最少的基础上，到点$(i,j)$步数等于最小步数的路径条数

那么考虑一下怎样bfs，每次从队列中取出一个点$x$，向八个方向分别扩展结点，设结点为$y$,如果越界或者扩展的点是岩石，那么毫不犹豫的continue。

接下来还要分两种情况考虑：

首先，如果通过$x$到达$y$添加的莲花数小于原来的莲花数，
##### 那么到$y$的最少步数要更新为到$x$的最少步数加一，路径条数也就更新为到$x$的路径条数。

其次，如果通过$x$到达$y$添加的莲花数等于原来的莲花数，并且还要与之前的最小步数相等
##### 那么只要把到$y$的路径条数加上到$x$的路径条数。

还要注意，因为方案数可能很大，所以要
# 开long long！！！

第一遍因为没开WA了一次（难受），下面直接上完整代码

```
#include<bits/stdc++.h>
using namespace std;
struct node
{
	long long x,y,num,sum;
} p;
long long n,m,a[33][33],dis[33][33][4],nx,ny;
int b1[8]= {1,1,-1,-1,2,2,-2,-2},b2[8]= {2,-2,2,-2,1,-1,1,-1};
queue<node>q;
int check(int tx,int ty) //弄个check函数，方便统计增加的莲花数量 
{
	if(a[tx][ty]==0)
		return 1;
	else
		return 0;
}
int main()
{
	cin>>n>>m;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
		{
			dis[i][j][1]=1e16,dis[i][j][2]=1e16; //输入的时候要初始化一下 
			cin>>a[i][j];
			if(a[i][j]==3)
			{
				p.x=i,p.y=j,p.num=0,p.sum=0,dis[i][j][1]=0,dis[i][j][2]=0,dis[i][j][3]=1;
				q.push(p);
			}
		}
	while(!q.empty()) 
	{
		p=q.front();
		q.pop();
		for(int i=0; i<8; i++) //核心部分 
		{
			nx=p.x+b1[i],ny=p.y+b2[i];
			if(a[nx][ny]==2||nx<=0||nx>n||ny<=0||ny>m)
				continue;
			if(p.sum+check(nx,ny)<dis[nx][ny][1])
			{
				dis[nx][ny][1]=p.sum+check(nx,ny),dis[nx][ny][2]=p.num+1,dis[nx][ny][3]=dis[p.x][p.y][3];
				node txt;
				txt.x=nx,txt.y=ny,txt.num=dis[nx][ny][2],txt.sum=dis[nx][ny][1];
				q.push(txt);
			}
			else if(p.sum+check(nx,ny)==dis[nx][ny][1]&&p.num+1==dis[nx][ny][2])
				dis[nx][ny][3]+=dis[p.x][p.y][3];
		}
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(a[i][j]==4)
			{
				if(dis[i][j][1]==1e16) //有可能到不了终点，记得特判 
					cout<<-1;
				else
					cout<<dis[i][j][1]<<endl<<dis[i][j][2]<<endl<<dis[i][j][3];
			}
	return 0;
}
```


---

## 作者：Gavin·Olivia (赞：4)

白银莲花池……~~又一题搜索好题~~。

~~然而我打的并不是搜索~~

最正常的思路当然是广搜啊。据我们老师所说有一个$dalao$学长在考场上怒打三遍$bfs$，当场$AC$。然而本人蒟蒻，只会打$SPFA$。在此也会讲讲学长的思路，如果有大佬感兴趣可以去尝试一下。

#### 三遍广搜思路

第一遍广搜，搜索从起点到终点最少要添加多少莲花，如果达不到，直接输$-1$。
第二遍，按照第一遍的搜索答案去搜索在添加最少莲花条件下的最少步数。
第三遍，根据一、二步的答案统计方案总数。

~~据说代码一百多行~~，不敢打不敢打。害怕.GIF

#### $SPFA$思路

从起点开始，向八个方向扩展，如果添加的莲花少，就更新，如果添加莲花一样多但步数更少，也更新，目标点方案数等于当前点方案数。特别地，如果添加莲花和步数一样多，目标点方案数加上当前点方案数。以上三种情况目标点皆需入队。为避免重复入队造成超时，开一个标记数组$used$，在点$(i,j)$入队是标记$used[i][j]$为真，出队后标记为假。对于不打标记的后果，详情请问某普及组$100$分大佬[@sinian](https://www.luogu.org/space/show?uid=23899)。（其实他是有打标记的，只不过根本没用过而已#滑稽）

题解配合代码食用，风味更佳哦~
```cpp
#define pa pair<int,int>
#include<bits/stdc++.h>
 using namespace std;
 int fx[8]={-2,-1,1,2,2,1,-1,-2};
 int fy[8]={1,2,2,1,-1,-2,-2,-1};
 int m,n,t,i,j,x,y,xx,yy,a,b,px,py,maps[40][40];
 int build[40][40],step[40][40];//最少添加莲花数和此条件下的最少步数
 long long c,cnt[40][40];//统计方案数组记得要开long long哦，否则会有一个点爆掉
 bool pd,used[40][40];//标记数组
 queue<pa> q;
 inline int read()
{
	int x=0,c; bool f=0;
	for(;(c=getchar())<'0'||c>'9';f|=c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	return f?-x:x;
}
 int main()
{
	m=read(); n=read();
	for(i=1;i<=m;i++) for(j=1;j<=n;j++)
	{
		t=read(); maps[i][j]=t; if(t==4) px=i,py=j;
		if(t==3) q.push(make_pair(i,j)),cnt[i][j]=1,used[i][j]=true;
		else build[i][j]=1e9,step[i][j]=1e9;
	}
	while(!q.empty())
	{
		x=q.front().first; y=q.front().second; q.pop(); used[x][y]=false;
		a=build[x][y]; b=step[x][y]; c=cnt[x][y];
		for(i=0;i<8;i++)
		{
			xx=x+fx[i]; yy=y+fy[i]; pd=false;
			if(xx>m||xx<1||yy>n||yy<1||maps[xx][yy]==2||a>build[xx][yy]) continue;
			if(maps[xx][yy])
			{
				if(a<build[xx][yy]||b+1<step[xx][yy])
				{
					build[xx][yy]=a; step[xx][yy]=b+1; cnt[xx][yy]=c; pd=true;
				}
				else if(b+1==step[xx][yy]) cnt[xx][yy]+=c,pd=true;
			}
			else if(a+1<build[xx][yy]||(a+1==build[xx][yy]&&b+1<step[xx][yy]))
				{
					build[xx][yy]=a+1; step[xx][yy]=b+1; cnt[xx][yy]=c; pd=true;
				}
				else if(a+1==build[xx][yy]&&b+1==step[xx][yy])
						cnt[xx][yy]+=c,pd=true;
			if(pd&&!used[xx][yy]&&(xx!=px||yy!=py))
			{
				q.push(make_pair(xx,yy)); used[xx][yy]=true;
			}
		}
	}
	if(build[px][py]==1e9) {printf("-1"); return 0;}
	printf("%d\n%d\n%lld",build[px][py],step[px][py],cnt[px][py]);
	return 0;
}
```

---

## 作者：Creeper_LKF (赞：3)

优先队列优化+常数优化，0ms

首先我们看到这道题肯定是bfs，然后众所周知，搜索的复杂度是O(玄学)的（虽然此题数据比较水）。

然后考虑在bfs外的附加任务（以下简称增加莲花数为莲花数）：

使增加莲花数最少；在此前提下路径最短；等路径等莲花数的方案数。

然而本蒟蒻被long long坑了：方案数贼大......

接下来是具体实现方案。

可以想到，我们平时裸bfs的队列里面的关键字（路径长度）会随着bfs而递增，所以我们一旦达到终点就可以终止bfs，然而这里我们有两个关键字，其中第一关键字是莲花数，第二关键字是路径长度。这说明我们的路径内第一关键字的递增特性被破坏，所有说我们需要调整一下队列来bfs。于是我们想：那岂不是直接按第一关键字排序不久行了？是的，就是这样。

然后于是第一任务与第二任务完成了，考虑第三任务：方案数。

考虑从[i1,j1]和[i2,j2]都可以跳到[i0,j0]（假设[i2,j2]先访问到了[i0,j0]）。现在假设[i0,j0]会是最终解的路径上的一个点。显然这里产生了两种方案到达[i0,j0]，而到达[i1,j1]或[i2,j2]不一定只有一种方式，于是我们将这两种方式相加......且慢！如果这两种方式有可能会有不是最终路径呢？那么如果[i1,j1]不是最终的解，也就是说从该点产生的到终点的路径不符合任务一或任务二，而我们发现[i0,j0]是原解上的路径，这说明什么？说明[i1,j1]->[i0,j0]不在解的路径上，所以[i1,j1]的莲花数或者是步数无法转移到[i0,j0]上来，也就是说step[1]+1!=step[0]（step[1]为步数[i1,j1]的简写）或lily[1]+(是否需要莲花)!=lily[0]（莲花数简写）。所以这就可以判断[i1,j1]的方案是否可以转移到[i0,j0]上。如果[i0,j0]都到不了呢？那么就会有两种情况筛掉：1.像[i1,j1]一样筛掉，2.最终无法成为到达终点的最优解而不会加入到答案中。

所以代码如下：

```cpp
#include<cstdio>
#include<cctype>
#include<queue>
#define MAXN 31
#define MAXC 100000
using namespace std;
inline int min(int a,int b){//最小值优化（此程序中没用）
    int c=(b-a)>>31;
    return (a&c)||(b&~c);
}
inline char get_char(){//快读
    static char buf[10000001],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
    int num=0;
    char c;
    while(isspace(c=get_char()));
    while(num=num*10+c-48,isdigit(c=get_char()));
    return num;
}
int m,n;
int matrix[MAXN][MAXN],step[MAXN][MAXN],adds[MAXN][MAXN];/原图，步数，增加莲花数
long long ans[MAXN][MAXN];//方案数
bool vis[MAXN][MAXN];//访问标记
struct P{
    int x,y,step,adds;
};
struct cmp{
    inline bool operator () (P x,P y){
        if(x.adds==y.adds) return x.step>y.step;//关键此排序
        return x.adds>y.adds;
    }
};
int main(){
    m=read(),n=read();
    int sx,sy,tx,ty;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            int &p=matrix[i][j];
            p=read();
            if(p==2) vis[i][j]=true;//可以在下面减去对岩石的判断
            if(p==3) sx=i,sy=j;
            if(p==4) tx=i,ty=j;
        }
    }
    priority_queue<P,vector<P>,cmp> mession;//优先队列优化，把增加莲花最小的放在队首
    int d[8][2]={{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1},{2,1}};
    // if(sx>tx) d={{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1},{2,1}};//本来想写搜索方向优化，然而又懒得写了
    // else d={{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1}};
    mession.push((P){sx,sy,0,0});
    vis[sx][sy]=true,ans[sx][sy]=1;
    P u;
    int temx,temy;
    while(!mession.empty()){
        u=mession.top(),mession.pop();
        if(u.x==tx&&u.y==ty){//直接输出
            printf("%d\n",u.adds);
            printf("%d\n",u.step);
            break;
        }
        for(int i=0;i<8;i++){
            temx=u.x+d[i][0],temy=u.y+d[i][1];
            if(temx<1||temx>m||temy<1||temy>n) continue;
            bool &p1=vis[temx][temy];//避免反复寻址
            int &p2=matrix[temx][temy],&p3=step[temx][temy],&p4=adds[temx][temy],tem1=u.adds;
            if(p1){
                if(step[u.x][u.y]+1==p3&&adds[u.x][u.y]+(!p2)==p4) ans[temx][temy]+=ans[u.x][u.y];
                continue;//两种情况：1.目标点没入队是岩石：直接continue，2.目标点已经出队了：那么step和adds一定更新不了答案，3.目标点在队中：不用再入队了
            }
            tem1+=(!p2),p1=true,p3=u.step+1,p4=tem1,ans[temx][temy]=ans[u.x][u.y];
            mession.push((P){temx,temy,u.step+1,tem1});
        }
    }
    if(u.x!=tx||u.y!=ty){//误解
        printf("-1");
        return 0;
    }
    printf("%lld",ans[u.x][u.y]);
    return 0;
}

```

---

## 作者：离子键Ionic_Bond (赞：2)

## ~~真鸡儿恶心~~
鬼知道我干了啥，一道广搜交了一页多。

我喝了口水，磕了磕杯盖，看完了这个题，心想：大水题，大水题，用优先队列维护个莲花数和步数不就行了，让它先入队，再排一下，多水，直接性水烂啊。

然后就有了下面这份代码，实质上是贪心中的贪心。

## 14Marks Code：
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
#include<cctype>
#include<iostream>
#include<queue>
#define ll long long

using namespace std;

int read(){
	char c=getchar();int x=0,f=1;
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
	return x*f;
}
ll m,n,th[40][40],sx,sy,ex,ey;
ll mv[2][8]={
	{1,2,-1,-2,1,2,-1,-2},
	{2,1,-2,-1,-2,-1,2,1}
};
bool vis[40][40][1601];
struct prq{
	ll x,y,st,nof;
	bool operator < (const prq &a)const{
		if(a.nof<nof)return 1;
		else if(a.nof==nof&&a.st<st)return 1;
		else return 0;
	}
};
priority_queue<prq>q;
void bfs(){
	q.push((prq){sx,sy,0,0});
	vis[sx][sy][0]=1;
	ll minst=1234567890123456ll,cnt=0,minnof=123456123456ll;
	while(!q.empty()){
		//printf("%d\n",q.size());
		prq d=q.top();
		q.pop();
		ll x=d.x,y=d.y,st=d.st,nof=d.nof;	
		//printf("(%lld %lld %lld %lld %lld)\n",x,y,st,nof,cnt);
		if(x==ex&&y==ey&&st>minst){
			printf("%lld\n%lld\n%lld\n",minnof,st,cnt);
			return; 
		}
		if(x==ex&&y==ey)minst=st,cnt++,minnof=min(nof,minnof);
		for(int i=0;i<8;i++){
			ll nx=x+mv[0][i],ny=y+mv[1][i];
			if(nx>m||ny>n||nx<1||ny<1||th[nx][ny]==2)continue;
			//if(vis[nx][ny][nof])continue;		
			if(th[nx][ny]==1){
				if(vis[nx][ny][nof])continue;
				q.push((prq){nx,ny,st+1,nof});
				vis[nx][ny][nof]=1;
			}
			if(th[nx][ny]==0){
				if(vis[nx][ny][nof+1])continue;
				q.push((prq){nx,ny,st+1,nof+1}),
				vis[nx][ny][nof+1]=1;
			}
		}
	}
	printf("-1\n");
}
int main(){
	scanf("%lld%lld",&m,&n);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			scanf("%lld",&th[i][j]);
			if(th[i][j]==3)sx=i,sy=j,th[i][j]=1;
			if(th[i][j]==4)ex=i,ey=j,th[i][j]=1;
		}
	}
	bfs();
}
```
直接WA飞了。

然后就有了一个叫Lemon_Water的人把这题的7分和14分交了一页。

于是我放弃了优先队列，直接朴素BFS，运用松弛操作更新三个参数。

本来以为数据这么毒瘤，会T飞

结果92分，WA了一个点。

## 92Marks Code
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
#include<cctype>
#include<iostream>
#include<queue>
#define ll long long
#define elif else if
using namespace std;

int read(){
	char c=getchar();int x=0,f=1;
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
	return x*f;
}
ll m,n,th[40][40],sx,sy,ex,ey,num[40][40],dis[40][40],nof[40][40];
ll mv[2][8]={
	{1,2,-1,-2,1,2,-1,-2},
	{2,1,-2,-1,-2,-1,2,1}
};
bool vis[40][40];
struct Q{
	ll x,y;
};
queue<Q>q;
void bfs(){
	q.push((Q){sx,sy});
	vis[sx][sy]=1;
	while(!q.empty()){
		Q a=q.front();
		q.pop();
		int x=a.x,y=a.y;
		for(int i=0;i<8;i++){
			bool ok=0;
			int nx=x+mv[0][i];
			int ny=y+mv[1][i];
			if(nx>m||ny>n||nx<1||ny<1||th[nx][ny]==2)continue;
			if(nof[nx][ny]>th[x][y]+nof[x][y]){
				nof[nx][ny]=nof[x][y]+th[x][y];
				dis[nx][ny]=dis[x][y]+1;
				num[nx][ny]=num[x][y];
				if(nx==ex&&ny==ey)continue;
				ok=1;				
			}
			elif(nof[nx][ny]==nof[x][y]+th[x][y]&&dis[nx][ny]>dis[x][y]+1){
				dis[nx][ny]=dis[x][y]+1;
				num[nx][ny]=num[x][y];
				if(nx==ex&ny==ey)continue;
				ok=1;
			}
			elif(nof[nx][ny]==nof[x][y]+th[x][y]&&dis[nx][ny]==dis[x][y]+1){
				num[nx][ny]+=num[x][y];
				if(nx==ex&&ny==ey)continue;
				ok=1;
			}
			if(!ok||vis[nx][ny])continue;
			else{
				q.push((Q){nx,ny});
				vis[nx][ny]=true;
			}
		}
	} 
}
int main(){
	scanf("%lld%lld",&m,&n);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			scanf("%lld",&th[i][j]);
			if(th[i][j]==3)sx=i,sy=j,th[i][j]=1;
			if(th[i][j]==4)ex=i,ey=j,th[i][j]=1;
			if(th[i][j]!=2)th[i][j]^=1;
		}
	}
	memset(dis,0x7f,sizeof(dis));
	memset(nof,0x7f,sizeof(nof));
	num[sx][sy]=1;
	dis[sx][sy]=0;
	nof[sx][sy]=0;
	bfs();
	if(nof[ex][ey]==nof[0][0]){
		printf("-1");
		return 0;
	}
	else printf("%lld\n%lld\n%lld",nof[ex][ey],dis[ex][ey],num[ex][ey]);
}
```
然后又开始疯狂调试

下了测试数据一看蒙了

什么叫**反复横跳？**(战术后仰

但是当我想到反复横跳这个词语时豁然开朗

**必须要再弹出队首元素时，将其$visit$值设为$false$,不然只能跳出去，不能跳回来，达不到反复横跳得到最优解的效果。**

## 100Marks 代码(与部分题解思路撞车)
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
#include<cctype>
#include<iostream>
#include<queue>
#define ll long long
#define elif else if
using namespace std;

int read(){
	char c=getchar();int x=0,f=1;
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
	return x*f;
}
ll m,n,th[40][40],sx,sy,ex,ey,num[40][40],dis[40][40],nof[40][40];
ll mv[2][8]={
	{1,2,-1,-2,1,2,-1,-2},
	{2,1,-2,-1,-2,-1,2,1}
};
bool vis[40][40];
struct Q{
	ll x,y;
};
queue<Q>q;
void bfs(){
	q.push((Q){sx,sy});
	vis[sx][sy]=1;
	while(!q.empty()){
		Q a=q.front();
		q.pop();
		int x=a.x,y=a.y;
		vis[x][y]=false;
		for(int i=0;i<8;i++){
			bool ok=0;
			int nx=x+mv[0][i];
			int ny=y+mv[1][i];
			if(nx>m||ny>n||nx<1||ny<1||th[nx][ny]==2)continue;
			if(nof[nx][ny]>th[x][y]+nof[x][y]){
				nof[nx][ny]=nof[x][y]+th[x][y];
				dis[nx][ny]=dis[x][y]+1;
				num[nx][ny]=num[x][y];
				if(nx==ex&&ny==ey)continue;
				ok=1;				
			}
			elif(nof[nx][ny]==nof[x][y]+th[x][y]&&dis[nx][ny]>dis[x][y]+1){
				dis[nx][ny]=dis[x][y]+1;
				num[nx][ny]=num[x][y];
				if(nx==ex&ny==ey)continue;
				ok=1;
			}
			elif(nof[nx][ny]==nof[x][y]+th[x][y]&&dis[nx][ny]==dis[x][y]+1){
				num[nx][ny]+=num[x][y];
				if(nx==ex&&ny==ey)continue;
				ok=1;
			}
			if(!ok||vis[nx][ny])continue;
			else{
				q.push((Q){nx,ny});
				vis[nx][ny]=true;
			}
		}
	}     
}
int main(){
	scanf("%lld%lld",&m,&n);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			scanf("%lld",&th[i][j]);
			if(th[i][j]==3)sx=i,sy=j,th[i][j]=1;
			if(th[i][j]==4)ex=i,ey=j,th[i][j]=1;
			if(th[i][j]!=2)th[i][j]^=1;
		}
	}
	memset(dis,0x7f,sizeof(dis));
	memset(nof,0x7f,sizeof(nof));
	num[sx][sy]=1;
	dis[sx][sy]=0;
	nof[sx][sy]=0;
	bfs();
	if(nof[ex][ey]==nof[0][0]){
		printf("-1");
		return 0;
	}
	else printf("%lld\n%lld\n%lld",nof[ex][ey],dis[ex][ey],num[ex][ey]);
    return ~~(0^0)*(0^0)//卖萌求过
}
```
注：思路与部分题解撞车，但还请管理员大度给过，写篇题解不容易呢，管理员也辛苦了~~（：。

---

## 作者：紫薯布丁 (赞：2)

**·矩阵上的点，可以将每个点的坐标转化成一个点，将其转化成一般图。**

```cpp
inline int id(int x,int y){
	return (x-1)*m+y;
}
```



·对于每个点，枚举其八个方向的点对其建边，**如果是荷叶，其边权为0，如果没有荷叶，边权为1。** 对于第一问直接跑spfa即可。

```cpp
inline void Add(int x,int y){
	if(a[x][y]==2) return ;
	for(int i=0;i<8;i++){
		int ux=x+dx[i],uy=y+dy[i];
		if(ux<1||uy<1||ux>n||uy>m) continue;
		if(a[ux][uy]==2) continue;
		add(id(x,y),id(ux,uy),(!a[ux][uy]));
	}
}
```





·对于第二问，我们可以记录一个step数组，记录最短路径上路径条数，利用step数组再次跑最短路。

枚举条件 

```cpp
if(dis[y]==dis[u]+z){
	if(step[y]>step[u]+1){
        .....
    }
}
```

·对于第三问，我们记录num数组在第二次最短路的过程中进行**最短路计数**即可



·注意方案数可能会爆int，要开long long



代码不放了

---

## 作者：zjc5 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P2411)

**思路：**

这道题肯定是用 bfs 来做。

可以开三个数组，分别表示：添加的莲花的最少数目，最少步数和路径条数。

只有在当前莲花数目最少，步数最少时才能累加。

bfs 的判重数组处理比较特殊，因为输出的三个数组是不断更新。因此，每遍历到一个点，就要把这个点变成 false。

最后提醒：方案数组记得开 **long long**。

代码 $56$ 行。

**CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node {int x,y;};
queue<node>q;
bool b[35][35];
long long ans[35][35];
int dis[35][35],pon[35][35];
int ex,ey;
int n,m,a[35][35],k[8][2]= {{1,-2},{1,2},{2,-1},{2,1},{-1,2},{-1,-2},{-2,1},{-2,-1}};
int main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			cin>>a[i][j];
			pon[i][j]=dis[i][j]=INT_MAX;
			if(a[i][j]==3) {
				q.push((node) {i,j});
				pon[i][j]=dis[i][j]=0;
				ans[i][j]=1;//初始方案数为1
				b[i][j]=true;
			}
			if(a[i][j]==4) ex=i,ey=j;
		}
	while(!q.empty()) {
		node t=q.front();
		q.pop();
		b[t.x][t.y]=false;
		for(int i=0; i<8; i++) {
			int h=t.x+k[i][0];
			int l=t.y+k[i][1];
			if(h>=1&&h<=n&&l>=1&&l<=m&&a[h][l]!=2) {
				int s=pon[t.x][t.y];
				if(a[h][l]==0) s++;
				if(s<pon[h][l]) { //添加的莲花比现在少
					pon[h][l]=s;
					dis[h][l]=dis[t.x][t.y]+1;
					ans[h][l]=ans[t.x][t.y];
				} else if(s==pon[h][l]) { //添加的莲花和现在一样
					if(dis[t.x][t.y]+1<dis[h][l]) { //步数比现在少
						dis[h][l]=dis[t.x][t.y]+1;
						ans[h][l]=ans[t.x][t.y];
					} else if(dis[t.x][t.y]+1==dis[h][l]) { //步数也和现在一样
						ans[h][l]+=ans[t.x][t.y];
					}
				}
				if(!b[h][l]) {
					b[h][l]=true;
					q.push((node) {h,l});
				}
			}
		}
	}
	if(pon[ex][ey]==INT_MAX) cout<<-1;
	else cout<<pon[ex][ey]<<"\n"<<dis[ex][ey]<<"\n"<<ans[ex][ey];
	return 0;
}

```

---

## 作者：Widerg (赞：0)

广搜实现动态规划。从起始点开始搜索，只要不是石头的点都可以访问。对于网格中每一个点，维护三个参数：从起始点到当前点所要添加的莲花数lily，总起始点到前点的走过的点数skip，到当前点当前满足条件的路径条数cnt。初始化所有点skip=lily=无穷大，cnt=0。起始点skip=lily=0，cnt=1。

当位置i时，跳跃有8个方向，最多会访问8个点，对于每个点j，根据当前位置i更新其参数。分以下4种情况：

1.如果 i.lily < j.lily ，由i点更新点j所有参数，并把点j加入队列

1.j.lily <- i.lily 

2.j.skip <- i.skip 

3.j.cnt <- i.cnt 

2.如果 i.lily = j.lily 并且 i.skip < j.skip ，由i点更新点j的跳跃次数和路径条数，并把点j加入队列

1.j.skip <- i.skip 

2.j.cnt <- i.cnt 

3.如果 i.lily = j.lily 并且 i.skip = j.skip ，j的路径条数满足条件，增加量为i的路径条数，并把点j加入队列

1.j.cnt <- j.cnt + i.cnt 

4.如果不满足以上条件，不更新改点。

最终结果为目标点T的lily,skip,cnt。

```cpp
" #include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
FILE *in = fopen("silvlily.in", "r"), *out = fopen("silvlily.out", "w");
int m,n,d[50][50];
struct p {int x, y;};
```
class node
{
public:



            


```cpp
    int bestlily;
    int bestjump;
    long long nways;
    node() {bestlily=-1; bestjump=-1; nways=0;}
};
node grid[50][50];
bool inq[50][50];
#define QSIZE 10000
p q[QSIZE];
int qstart,qend;
void enq(int x, int y)
{
    if (!inq[x][y])
    {
        inq[x][y]=true;
        q[qend].x=x;
        q[qend].y=y;
        qend++; qend%=QSIZE;
    }
}
void updateq(int x, int y, int bl, int bj, long long pways)
{
    if (grid[x][y].bestlily==-1 || bl<grid[x][y].bestlily)
    {
        grid[x][y].bestlily=bl;
        grid[x][y].bestjump=bj;
        grid[x][y].nways=pways;
        enq(x,y); return;
    }
    if (grid[x][y].bestlily==bl && bj<grid[x][y].bestjump)
    {
        grid[x][y].bestlily=bl;
        grid[x][y].bestjump=bj;
        grid[x][y].nways=pways;
        enq(x,y); return;
    }
    if (grid[x][y].bestlily==bl && bj==grid[x][y].bestjump)
    {
        grid[x][y].nways+=pways;
        return;
    }
}
int dirs[8][2]={{1,2},{2,1},{-1,2},{-2,1},{-1,-2},{-2,-1},{1,-2},{2,-1}};
void processqhead(void)
{
    int x=q[qstart].x,y=q[qstart].y,nx,ny;
    for (int i=0;i<8;i++)
    {
        nx=x+dirs[i][0];
        ny=y+dirs[i][1];
        if (nx>=0 && ny>=0 && nx<m && ny<n)
        {
            if (d[nx][ny]!=2)
updateq(nx,ny,grid[x][y].bestlily+(d[nx][ny]==1?0:1),grid[x][y].bestjump+1,grid[x][y].nways);
        }
    }
    inq[x][y]=false;
    qstart++; qstart%=QSIZE;
}
int main(void)
{
    int i,j;
    p a,b;
    fscanf(in,"%i %i",&m,&n);
    for (i=0;i<m;i++) for (j=0;j<n;j++) fscanf(in,"%i",&d[i][j]);
    for (i=0;i<m;i++) for (j=0;j<n;j++)
    {
        if (d[i][j]==3) {d[i][j]=1; a.x=i;a.y=j;}
        if (d[i][j]==4) {d[i][j]=1; b.x=i;b.y=j;}
        inq[i][j]=false;
    }
    qstart=0; qend=0;
    updateq(a.x,a.y,0,0,1);
    while (qstart!=qend)
    {
        processqhead();
    }
    if (grid[b.x][b.y].bestlily==-1) fprintf(out,"-1\n");
    else
fprintf(out,"%i\n%i\n%lld\n",grid[b.x][b.y].bestlily,grid[b.x][b.y].bestjump,grid[b.x][b.y].nways);
    fclose(in); fclose(out); return 0;

```

---

