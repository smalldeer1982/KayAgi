# [COCI 2020/2021 #4] Patkice II

## 题目描述

Netflix 的经商人员想要制作一个有关三只鸭子之旅的系列改编。

在 COCI20/21 的第一轮中，鸭子们位于一个洋流的地图中，鸭子们一同出行。鸭子们的起始岛屿用 `o` 表示。鸭子们可以往四个方向进行旅行，分别是：西 $\to$ 东（`>`），东 $\to$ 西（`<`），北 $\to$ 南（`v`） 和南 $\to$ 北（`^`）。当鸭子们位于洋流的点上时，它们将会向洋流的方向移动一个单位。

平静的海面用 `.` 表示。如果洋流把鸭子们带到了平静的海面、到达地图之外或者回到起始小岛处，它们就会停止旅行。鸭子们想要前往的目的地岛屿用 `x` 表示。

为了让情节更加吸引人，Netflix 进行了改编：现在海面上可能会出现旋涡（鸭子们可能会困在其中）和可把鸭子带到地图之外的洋流。

因此，原先地图被迫改变。但在即将到来的截止期的情况下，导演犯了几个错误：鸭子们不能再通过洋流到达目的地岛屿。

Netflix 导演是非常重要的人，因此他们并不花时间思考情节漏洞。你的任务是替换地图中的几个字符，使得鸭子们能够从起始岛屿到达目的地岛屿。

因情节需要，字符 `o` 和 `x` 不能被修改。其他字符（`<>v^.`）分别表示洋流和平静的海面。你可以用 `<>v^.` 中的任意字符来替换原先地图中 `<>v^.` 的任意字符。

## 说明/提示

#### 数据规模与约定

**本题采用捆绑评测，自动开启 O2 优化。**

| Subtask | 分值 | 数据范围及约定 |
| :----------: | :----------: | :----------: |
| $1$ | $30$ | $3 \le r,s \le 20$ |
| $2$ | $80$ | 无 |

对于 $100\%$ 的数据，$3 \le r,s \le 2000$。

#### 评分方式

如果一个子任务中的所有数据中，第一行均正确，那么可以得到该子任务一半的分数。

本题启用非官方的自行编写的 [Special Judge](https://www.luogu.com.cn/paste/d4nbx1ua)，也可以在附件中下载。欢迎大家 hack（可私信或直接发帖）。

#### 说明

**本题分值按 COCI 原题设置，满分 $110$。**

**题目译自 [COCI2020-2021](https://hsin.hr/coci/) [CONTEST #4](https://hsin.hr/coci/contest4_tasks.pdf)  _T5 Patkice II_。**

## 样例 #1

### 输入

```
3 3
>vo
vv>
x>>```

### 输出

```
1
>vo
vv>
x<>```

## 样例 #2

### 输入

```
3 6
>>vv<<
^ovvx^
^<<>>^```

### 输出

```
2
>>vv<<
^o>>x^
^<<>>^```

## 样例 #3

### 输入

```
4 4
x.v.
.>.<
>.<.
.^.o```

### 输出

```
4
x<<.
.>^<
>.<^
.^.o```

# 题解

## 作者：WaltVBAlston (赞：7)

不得不说，这是一道**极为经典**的**广搜变形**题目，做完之后无论是 BFS 还是 pair 的使用都更加娴熟，收获颇丰。李煜东·《算法竞赛进阶指南》中在广搜变形这一章内有一道非常相似的题目。当时我以为自己会了，就没有多想。没想到今天遇到原题竟然还写错了好几次，作文以记之：

对于这道题目，第一眼看出来是 BFS 应该不难，但是这里有一个问题：由于各个状态被加入队列的时候所需要改变的次数是不同的（对于每个点），而 BFS 的要求是对于序列中的每一个元素，其第一关键字都应该是不递减的。

那么这个时候该怎么办呢？

- Solution1

使用 SPFA,Dijkstra 等最短路算法，通过多次更新/序列内排序等方法保证正确性。但这么做效率显然不高（至少增加一个   log，如果题目要求更严格那么显然是过不去的。

- Solution2

使用**双端队列**BFS，即每次加入新状态的时候判断代价是否需要增加，如果需要，就压进队头，不需要则压进队尾。可以证明，这样对于每一个点每次得到的最优状态一定比较劣状态更先取出。

至于输出修改后的地图，这个点也难了我一会儿。最后想到的办法是每次一个节点能够被更新就说明它的前驱被修改一定更优，所以我们用 pre 数组来记录每个点的前驱，最后从终点往起点扫一遍即可。

不得不说思维难度比较大，而且需要抽象思维。

题外话：我真的很佩服发明这种算法的人，我只能用优美这个词形容双端队列和 BFS 的结合，真的太优美了。

复杂度 $O(r*s)$

Code:

```
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pr;
#define mp make_pair
int n,m;
deque <pr> dq;
char sea[2005][2005];
int sx,sy,ex,ey,dis[2005][2005];
pr pre[2005][2005];
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
char dir[4]={'v','^','>','<'};
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>sea[i][j];
			if(sea[i][j]=='x')
				ex=i,ey=j;
			else if(sea[i][j]=='o')
				sx=i,sy=j;
		}
	memset(dis,0x3f,sizeof(dis));
	dq.push_back(mp(sx,sy));
	dis[sx][sy]=0;
	while(!dq.empty()){
		pr temp=dq.front();
		dq.pop_front();
		if(temp==mp(ex,ey)||dis[temp.first][temp.second]>=dis[ex][ey])
			continue;
		//cout<<temp.first<<" "<<temp.second<<endl;
		for(int i=0;i<4;i++){
			int tx=temp.first+dx[i],ty=temp.second+dy[i];
			if(tx<1||tx>n||ty<1||ty>m)
				continue; 
			int w=(sea[temp.first][temp.second]==dir[i]||sea[temp.first][temp.second]=='o')?0:1;
			if(dis[tx][ty]>dis[temp.first][temp.second]+w){
				dis[tx][ty]=dis[temp.first][temp.second]+w;
				pre[tx][ty]=temp;
				if(w==0)
					dq.push_front(mp(tx,ty));
				else
					dq.push_back(mp(tx,ty));
			}
		}
	}
	pr before=pre[ex][ey],now=mp(ex,ey);
	//cout<<before.first<<" "<<before.second<<" 114514"<<endl;
	while(before!=mp(sx,sy)){
		if(before.first==now.first+1)
			sea[before.first][before.second]='^';
		if(before.first==now.first-1)
			sea[before.first][before.second]='v';
		if(before.second==now.second+1)
			sea[before.first][before.second]='<';
		if(before.second==now.second-1)
			sea[before.first][before.second]='>';
		now=before;
		before=mp(pre[before.first][before.second].first,pre[before.first][before.second].second);
	}
	cout<<dis[ex][ey]<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			cout<<sea[i][j];
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Im3tsmh (赞：4)

转化一下题面，把这张地图视为一个 $n\times n$ 的矩阵，图上的每一个点就是矩阵上的一个元素。

这张图上，每一个点都只能往左，右，上，下四个方向走一个格子，所以最大边数就是点数 $\times 4$，因为有双向边，所以数组要再开 $2$ 倍空间。

把这个 $r\times s$ 的数组转化为点时，$(i,j)$ 可化为 $(i-1)\times s+j$，把图中已经可以走的两个点间连边权为 $0$，需要替换地图字符才能走的两点连边权为 $1$，然后在图上跑最短路即可求出需要进行改变的字符的最少数量。

记录 $path[]$ 找到鸭子游泳路径，通过路径修改图输出即可。在修改时记得点转化为数组元素时的取模问题，具体见代码。

```cpp
#include<bits/stdc++.h>
#define gc() getchar()
#define test printf("\nRunZeSAMA_ONTOP\n")
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-9;
const int N=2005;
const int M=N*N*4;
int r,s,start,posi,p,p1,wrz;
char ch[N][N];
int dis[N*N],path[N*N],u,v,w;
bool vis[N*N];
stack<int>st;
struct E{
	int to,nxt,w;
}e[M<<1];int star,head[N*N];
struct node{
	int dis,pos;
};
bool operator<(const node &a,const node &b)
{
	return a.dis>b.dis;
}
void add(int u,int v,int w)
{
	e[++star].w=w;
	e[star].to=v;
	e[star].nxt=head[u];
	head[u]=star;
}
priority_queue<node>q;
node now;
void dijkstra()
{
	while(!q.empty())
	{
		now=q.top();
		q.pop();
		u=now.pos;
		if(vis[u])continue;
		vis[u]=true;
		for(int i=head[u];i;i=e[i].nxt)
		{
			v=e[i].to;
			if(dis[v]>dis[u]+e[i].w)
			{
				path[v]=u;
				dis[v]=dis[u]+e[i].w;
				now={dis[v],v};
				q.push(now);
			}
		}
	}
}
int main(){
	scanf("%d%d",&r,&s);
	for(int i=1;i<=r;++i)
	{
		for(int j=1;j<=s;++j)
		{
			cin>>ch[i][j];
			if(ch[i][j]=='o')start=(i-1)*s+j;
			if(ch[i][j]=='x')posi=(i-1)*s+j;
		}
	}
	for(int i=1;i<=r;++i)
	{
		for(int j=1;j<=s;++j)
		{
			if(j>1)
			{
				if(ch[i][j]=='<'||ch[i][j]=='o')add((i-1)*s+j,(i-1)*s+j-1,0);
				else add((i-1)*s+j,(i-1)*s+j-1,1);
			}
			if(j<s)
			{	
				if(ch[i][j]=='>'||ch[i][j]=='o')add((i-1)*s+j,(i-1)*s+j+1,0);
				else add((i-1)*s+j,(i-1)*s+j+1,1);
			}
			if(i>1)
			{
				if(ch[i][j]=='^'||ch[i][j]=='o')add((i-1)*s+j,(i-1)*s+j-s,0);
				else add((i-1)*s+j,(i-1)*s+j-s,1);
			}
			if(i<r)
			{
				if(ch[i][j]=='v'||ch[i][j]=='o')add((i-1)*s+j,(i-1)*s+j+s,0);
				else add((i-1)*s+j,(i-1)*s+j+s,1);
			}
		}	
	}
	for(int i=1;i<=r*s;++i)if(i!=start)dis[i]=inf;
	q.push({dis[start],start});
	dijkstra();
	printf("%d\n",dis[posi]);
	//
	p=posi;
	while(path[p])
	{
		st.push(p);
		p=path[p];
	}
	p1=start;
	while(!st.empty())
	{
		p=st.top();
		st.pop();
		if(p1==start)
		{
			p1=p;
			continue;
		}
		wrz=p1%s;
		if(!wrz)wrz=s;
		if(p==p1+1)ch[(p1-1)/s+1][wrz]='>';
		if(p==p1-1)ch[(p1-1)/s+1][wrz]='<';
		if(p==p1+s)ch[(p1-1)/s+1][wrz]='v';
		if(p==p1-s)ch[(p1-1)/s+1][wrz]='^';
		p1=p;
	}
	for(int i=1;i<=r;++i)
	{
		for(int j=1;j<=s;++j)
		{
			cout<<ch[i][j];
		}
		cout<<endl;
	}
    return 0;
}
//freopen(".in","r",stdin);
//freopen(".out","w",stdout);

```


---

## 作者：lmgoat (赞：4)

# 思路
初看(~~考试时看~~)这道题，还以为是什么高级算法，结果教练说是个 BFS 。分析一下，确实如此。
## BFS
只需要 BFS + 最短路的 dis 比大小，搜索时的方向与原地图一致则代价不变，否则代价 + 1，用最短路的比大小方法即可算出需要进行改变的字符的最少数量。
## 输出方案
在搜索时记录下每个经过的点的方向，从终点反方向倒退到起点即可根据之前记录的方向得到方案。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pr;
inline int read() {
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)) {
		if(ch=='-')f=1;
		ch=getchar();
	}
	while(isdigit(ch)) {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f?-x:x;
}
int const N=2005;
int a[N][N],r,s,dis[N][N],pre[N][N];
int dir[4][2]= {{1,0},{-1,0},{0,1},{0,-1}};
char c[N];
pr start,end;
inline bool in(int x,int y) {
	return x>=1&&x<=r&&y>=1&&y<=s;
}
void bfs() { //BFS + 最短路
	memset(dis,0x3f,sizeof dis);
	deque<pr>q;
	q.push_back(start);
	dis[start.first][start.second]=0;
	while(!q.empty()) {
		pr tmp=q.front();
		q.pop_front();
		if(tmp==end||dis[tmp.first][tmp.second]>=dis[end.first][end.second])continue;
		for(int i=0; i<4; ++i) {
			int x=tmp.first+dir[i][0],y=tmp.second+dir[i][1];
			if(!in(x,y))continue;
			int w=(i==a[tmp.first][tmp.second]||tmp==start)?0:1;
			if(dis[x][y]>dis[tmp.first][tmp.second]+w) {
				dis[x][y]=dis[tmp.first][tmp.second]+w;
				pre[x][y]=i;
				if(!w) q.push_front(make_pair(x,y));
				else q.push_back(make_pair(x,y));
			}
		}
	}
	return;
}
void out() { //输出方案
	int x=end.first,y=end.second;
	while(1) {
		int nxt=pre[x][y]^1;
		int nx=x+dir[nxt][0],ny=y+dir[nxt][1];
		if(make_pair(nx,ny)==start) break;
		a[nx][ny]=pre[x][y];
		x=nx,y=ny;
	}
	for(int i=1; i<=r; ++i) {
		for(int j=1; j<=s; ++j) {
			if(make_pair(i,j)==start)putchar('o');
			else if(make_pair(i,j)==end)putchar('x');
			else if(a[i][j]==0)putchar('v');
			else if(a[i][j]==1)putchar('^');
			else if(a[i][j]==2)putchar('>');
			else if(a[i][j]==3)putchar('<');
			else if(a[i][j]==4)putchar('.');
		}
		putchar('\n');
	}
	return;
}
signed main() {
	r=read(),s=read();
	for(int i=1; i<=r; ++i) {
		scanf("%s",c+1);
		for(int j=1; j<=s; ++j) {
			if(c[j]=='o')start=make_pair(i,j);
			if(c[j]=='x')end=make_pair(i,j);
			if(c[j]=='>')a[i][j]=2;
			if(c[j]=='<')a[i][j]=3;
			if(c[j]=='^')a[i][j]=1;
			if(c[j]=='v')a[i][j]=0;
			if(c[j]=='.')a[i][j]=4;
		}
	}
	bfs();
	printf("%d\n",dis[end.first][end.second]);
	out();
	return  0;
}
```

---

## 作者：bloodstalk (赞：4)

广搜好题

## 题目大意
起点是 "o" , 终点是 "x" ，"^ v < >" 表示四种洋流，鸭子进入洋流后就可以沿着该方向移动距离， "." 是平静的海面，鸭子进入这里就会停止。问我们需要至少改变多少个字符才能使鸭子从起点走向终点，并且打印出改变字符后的地图。

## 思路

一般求最短路径的算法就是 BFS ，所以我们思考如何去使用 BFS ： 四个方向走，如果我们要走的方向和洋流方向一致，那么就不需要改变洋流方向，权值为 $0$ ； 如果我们要走的方向和洋流方向不一致，那么在走的过程中我们需要改变洋流方向，权值为 $1$。  

想到这一步，我们就可以考虑优先队列和双端队列了，因为权值为 $0$ 的情况一定是比权值为 $1$ 的情况更优的（这里我用的双端队列），所以把权值为 $0$ 的情况从队头插入，把权值为 $1$ 的情况从队尾插入。这样，更好的情况一定是在前面的。

这个题的另一个问题就在于如何打印出新的地图。为了解决这个问题，我们给一个数组来记录前驱，如果从这个地方走更优，我们就记录他的前驱。最后根据这个点和前驱点的位置关系来更改地图即可。

时间复杂度和空间复杂度都为 $O(r \times s)$ 。
## 代码实现
```
#include<bits/stdc++.h> 
#define end endd
#define map mapp
const int INF=2147483647;
using namespace std;

char map[2005][2005];
int r,s;
int startx,starty,endx,endy;
struct node
{
	int x,y;
}now,end,pre[2005][2005];/*pre数组记录前驱*/
int bu[2005][2005];/*bu数组记录到达某个点需要更改字符的个数*/

int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
char direct[4]={'v','>','^','<'};/*四个方向，要注意和洋流对应*/

deque <node> q;/*双端队列*/

void bfs(int x,int y)
{
	now.x=x,now.y=y;
	bu[x][y]=0;
	q.push_back(now);
	while(!q.empty())
	{ 
		now=q.front();	
		q.pop_front();
		if((now.x==endx && now.y == endy) || bu[now.x][now.y] >= bu[endx][endy]) continue;/*剪枝，如果到达终点了或者到达该点的步数已经超过了此刻到达终点的步数了，那么就不需要再往后做了*/
		for(int i=0;i<4;i++)
		{
			int xx=now.x+dx[i];
			int yy=now.y+dy[i];	
			if(xx<1 || xx>r || yy<1 || yy>s) continue;
			int step = (map[now.x][now.y]==direct[i] || map[now.x][now.y] == 'o') ? 0 : 1;/*如果是起点或者洋流方向与我们要走的方向一致，那么权值就是0，否则是1*/
			if(bu[xx][yy] > bu[now.x][now.y] + step)
			{
				bu[xx][yy] = bu[now.x][now.y] + step;/*能更新就更新*/
				pre[xx][yy]=now;/*记录前驱*/
				end.x=xx,end.y=yy;
				if(step == 0) q.push_front(end);/*如果权值是0，较优，从队头插入，否则从队尾插入*/
				else q.push_back(end);
			}
		}
	}
}

void change(int kx,int ky)
{
	int px=pre[kx][ky].x,py=pre[kx][ky].y;
	while(px!=startx || py!=starty)/*要注意是前驱不为起点，如果用错会修改掉起点的方向*/
	{
		if(px==kx+1) map[px][py]='^';/*更新地图*/
		if(px==kx-1) map[px][py]='v';
		if(py==ky+1) map[px][py]='<';
		if(py==ky-1) map[px][py]='>';
		kx=px,ky=py; 
		px=pre[kx][ky].x,py=pre[kx][ky].y;
	}
}

signed main()
{
	ios::sync_with_stdio(false);
	cin >> r >> s;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=s;j++)
		{
			bu[i][j]=INF;
			cin >> map[i][j];
			if(map[i][j] == 'o') startx=i,starty=j;
			if(map[i][j] == 'x') endx=i,endy=j;	/*记录起点终点位置*/
		}
	bfs(startx,starty);/*开始bfs*/
	cout<<bu[endx][endy]<<endl;
	change(endx,endy);/*更改地图*/
	for(int i=1;i<=r;i++)
	{
		for(int j=1;j<=s;j++)
			cout<< map[i][j];
		cout << endl;/*输出*/
	}
	return 0;
}
```


---

## 作者：Hasinon (赞：3)

（第二次发题解，做的不好请多谅解)  



## 题目大意
给一个由 " ^ < v > . o x " 7 种格子组成的图，起点是 "o"，终点是 "x"。
" ^ < v > "表示洋流，"."表示旋涡。 

鸭子从起点开始，往上下左右任意方向移动一格，如果移动到洋流上，就往洋流指向的方向走，如果移动到旋涡上，那就不再移动了。 

现在我们要改变最少的格子数，让鸭子能从起点移动到终点.（毕竟有可能移动到旋涡然后停住或者在洋流里无限循环）  

最后输出改变的最少格子数和改变后的图。

## 解题思路
所以我们可以用最短路去做这道题。  

如果不改变图，那么每个格子会有 0/1 条路通往其他格子。我们令这些路的权值为 0。  

但是我们可以改变某些格子的类型，所以每个格子就有 4 条路分别通往与它相邻的上下左右四个格子了。我们令新增的这些路的权值为 1。  
e.g:   
![例子x1](https://cdn.luogu.com.cn/upload/image_hosting/o6kb0u6o.png?x-oss-process=image/resize,m_lfit,h_170,w_225)



然后一遍 Dijkstra/SPFA。

## CODE:  
```cpp
#include<bits/stdc++.h>
#define ll long long
#define G getchar()
using namespace std;
struct node{
	ll x,y,num;
};
struct dui{
	ll x,y;
};
ll up[2005][2005];
char htu[2005][2005];
ll side[2005][2005][4];
ll mmap[2005][2005],dx[4]={0,-1,0,1},dy[4]={-1,0,1,0};
priority_queue <node> q; 
ll r,ss;
bool operator <(const node a,const node b)
{
	return a.num>b.num;
}
ll gt()
{
	ll k=0,t=1;
	char c=G;
	while(c<'0'||'9'<c)
	{
		if(c=='-') t=-1;
		c=G;
	}
	while('0'<=c&&c<='9')
	{
		k=k*10+c-'0';
		c=G;
	}
	return k*t;
}
void SPFA()
{
	while(q.size())
	{
		node t=q.top(); q.pop();
		for(int i=0; i<4; i++)
		{
			if(mmap[t.x+dx[i]][t.y+dy[i]]>mmap[t.x][t.y]+side[t.x][t.y][i]&&1<=t.x+dx[i]&&t.x+dx[i]<=r&&1<=t.y+dy[i]&&t.y+dy[i]<=ss)
			{
				up[t.x+dx[i]][t.y+dy[i]]=(i+2)%4;
				mmap[t.x+dx[i]][t.y+dy[i]]=mmap[t.x][t.y]+side[t.x][t.y][i];
				q.push((node){t.x+dx[i],t.y+dy[i],mmap[t.x+dx[i]][t.y+dy[i]]});
			}
		}
	}
}
int main()
{
	r=gt(),ss=gt();
	ll stx,sty,enx,eny;
	for(int i=1; i<=r; i++)
	{
		scanf("%s",htu[i]);
		for(int j=1; j<=ss; j++)
		{
			if(htu[i][j-1]=='<')
			{
				side[i][j][0]=0;
				side[i][j][1]=1;
				side[i][j][2]=1;
				side[i][j][3]=1;
			}
			if(htu[i][j-1]=='>')
			{
				side[i][j][0]=1;
				side[i][j][1]=1;
				side[i][j][2]=0;
				side[i][j][3]=1;
			}
			if(htu[i][j-1]=='^')
			{
				side[i][j][0]=1;
				side[i][j][1]=0;
				side[i][j][2]=1;
				side[i][j][3]=1;
			}
			if(htu[i][j-1]=='v')
			{
				side[i][j][0]=1;
				side[i][j][1]=1;
				side[i][j][2]=1;
				side[i][j][3]=0;
			}
			if(htu[i][j-1]=='o')
			{
				stx=i,sty=j;
				side[i][j][0]=0;
				side[i][j][1]=0;
				side[i][j][2]=0;
				side[i][j][3]=0;
			}
			if(htu[i][j-1]=='x')
			{
				enx=i,eny=j;
				side[i][j][0]=1e9;
				side[i][j][1]=1e9;
				side[i][j][2]=1e9;
				side[i][j][3]=1e9;
			}
			if(htu[i][j-1]=='.')
			{
				side[i][j][0]=1;
				side[i][j][1]=1;
				side[i][j][2]=1;
				side[i][j][3]=1;
			}
		}
	} 	
	memset(mmap,0x3f,sizeof(mmap));
	mmap[stx][sty]=0;
	q.push((node){stx,sty,0});
	SPFA();
	ll lx=enx,ly=eny;
	while(lx!=stx||ly!=sty)
	{
		ll llx=lx,lly=ly;
		lx=llx+dx[up[llx][lly]],ly=lly+dy[up[llx][lly]];
		if(up[llx][lly]==0) htu[lx][ly-1]='>';
		if(up[llx][lly]==1) htu[lx][ly-1]='v';
		if(up[llx][lly]==2) htu[lx][ly-1]='<';
		if(up[llx][lly]==3) htu[lx][ly-1]='^';
	}
	htu[stx][sty-1]='o';
	printf("%lld\n",mmap[enx][eny]);
	for(int i=1; i<=r; i++)
	{
		for(int j=0; j<ss; j++)
		{
			printf("%c",htu[i][j]) ;
		}
		printf("\n");
	} 	
	return 0;
}
```

---

## 作者：CuSO4_and_5H2O (赞：2)

## 写在前边

这个题目很锻炼图论和 BFS 以及转换的能力，是个好题！

有两种思路写这个题目，一个是最短路，一个是双端队列 BFS。

前者好理解也要写但是时间慢，后者比前者快，其实也是一个双端队列模板题，都是很简单的。

### 最短路模型思路

这个题目可以抽象成一个最短路模型。


题目中的洋流可以理解成从当前这一个点到洋流指向的点的价格是 $0$,而到其他方向的点的价格就是 $1$，对于 `.` 可以看做他到旁边任意一点的价格都是 $1$，然后用迪杰斯特拉求出最短路就行了！

写这个题目一定要注意把改变地图转换成**让他往哪个方向走**，这个样就成功避开题目描述的陷阱。

然后就是一个大难题，怎么把新的地图打印出来。

其实新的题目的其他符号不变，变得只有从起点到终点路径上的符号，那我们只用管最短路路径上的符号就可以了。在路径上上的所有的点的方向一定是指向终点的，也就是说，路径上的点的前驱一定指向当前点，那么就可以记录一下每个点的前驱然后把前驱的方向修改成指向当前的的方向就可以了，这一过程利用递归实现就可以。

明白了思路就很简单了，还不会的可以看看代码。


```
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=1e11+111;

int n,m,Map[3002][3002]; 
char ch;
int x,y,jx,jy;

struct wuy{
	int xx,yy,qz;
};
struct oo{
	bool operator()(wuy A,wuy B){
		return A.qz>B.qz;
	}
};
priority_queue<wuy,vector<wuy>,oo> Q;//建立小根堆 

struct node{
	int x,y;
}qq[3002][3002];//记录前驱的数组 

int vis[3002][3002],dis[3002][3002];

int fx[4]={0,0,-1,1},
	fy[4]={1,-1,0,0};//方向数组 

void digui(int xx,int yy)//递归修改前驱方向 
{
	if(xx==x && yy==y) return ;//如果找到起点就不要在修改了 
	for(int i=0;i<=3;i++)
		{
			int dx=qq[xx][yy].x+fx[i],
				dy=qq[xx][yy].y+fy[i];
			if(dx==xx && dy==yy)//如果这个方向指向当前点 
			{
				Map[qq[xx][yy].x][qq[xx][yy].y]=i;//修改 
				break ;
			}
		}
	digui(qq[xx][yy].x,qq[xx][yy].y);//递归 
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>ch;
			if(ch=='<') Map[i][j]=1;
			if(ch=='^') Map[i][j]=2;
			if(ch=='v') Map[i][j]=3;
			if(ch=='o') Map[i][j]=5;
			if(ch=='x') Map[i][j]=6;
			if(ch=='.') Map[i][j]=7;
			if(ch=='x') jx=i,jy=j; 
			if(ch=='o') x=i,y=j;//这里其实可以用map函数，会好写一点，但是时间复杂度太高，不敢用怕超时 
		}
		
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) dis[i][j]=N;
	dis[x][y]=0;
	Q.push(wuy{x,y,0});
	while(!Q.empty())//堆优化迪杰斯特拉 
	{
		int bhx=Q.top().xx,bhy=Q.top().yy;
		Q.pop();
		if(vis[bhx][bhy]==1) continue ;/
		vis[bhx][bhy]=1;
		for(int i=0;i<=3;i++)//各个方向都试一试 
		{
			int dx=bhx+fx[i],
				dy=bhy+fy[i];
			int dj=0;//到下个点的价格 
			if(i!=Map[bhx][bhy] && Map[bhx][bhy]!=5) dj++;
			if(dx<1 || dx>n || dy<1 || dy>m) continue ;//如果超出了边界就结束 
			if(dis[bhx][bhy]+dj<dis[dx][dy] && vis[dx][dy]==0)
			{
				dis[dx][dy]=dis[bhx][bhy]+dj;
				Q.push(wuy{dx,dy,dis[dx][dy]});
				qq[dx][dy].x=bhx,qq[dx][dy].y=bhy;//更新前驱 
			}
		}
	}
	digui(jx,jy);//修改地图 
	Map[x][y]=5;//因为我的代码会把起点修改所以再改回来 
	cout<<dis[jx][jy]<<endl;//输出最短路 
	for(int i=1;i<=n;i++)//打印地图 
	{
		for(int j=1;j<=m;j++)
		{
			if(Map[i][j]==0) cout<<'>';
			if(Map[i][j]==1) cout<<'<';
			if(Map[i][j]==2) cout<<'^';
			if(Map[i][j]==3) cout<<'v';
			if(Map[i][j]==5) cout<<'o';
			if(Map[i][j]==6) cout<<'x';
			if(Map[i][j]==7) cout<<'.';
			//这里其实可以用map函数，会好写一点，但是时间复杂度太高，不敢用怕超时 
		}
		cout<<endl;
	}
}
/*切勿抄袭，思路很简单代码看着长其实还是很简单的。*/
```

### 双端队列

双端队列就是指能从队头和队尾插入元素的队列，具体操作方法可以看看洛谷的单调队列模板题的题解，本文不赘述。

双端队列的应用场景就是有两个不同的权值，这样普通的 BFS 就无法满足需求（因为先到的不一定是最好的），所以就用双端队列把 $0$ 放在前边，$1$ 放在后边，然后就和普通 BFS 一样了，还是很简单的，具体实现看代码吧！这个思路比上个思路快很多。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=1e11+111;

int n,m,Map[3002][3002]; 
char ch;
int x,y,jx,jy;

deque<int> qx,qy,qd;
 
struct node{
	int x,y;
}qq[3002][3002];

int vis[3002][3002],dis[3002][3002];

int fx[4]={0,0,-1,1},
	fy[4]={1,-1,0,0};

void digui(int xx,int yy)
{
	if(xx==x && yy==y) return ;
	for(int i=0;i<=3;i++)
		{
			int dx=qq[xx][yy].x+fx[i],
				dy=qq[xx][yy].y+fy[i];
			if(dx==xx && dy==yy)
			{
				Map[qq[xx][yy].x][qq[xx][yy].y]=i;
				break ;
			}
		}
	digui(qq[xx][yy].x,qq[xx][yy].y);
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			dis[i][j]=N;
			cin>>ch;
			if(ch=='<') Map[i][j]=1;
			if(ch=='^') Map[i][j]=2;
			if(ch=='v') Map[i][j]=3;
			if(ch=='o') Map[i][j]=5;
			if(ch=='x') Map[i][j]=6;
			if(ch=='.') Map[i][j]=7;
			if(ch=='x') jx=i,jy=j; 
			if(ch=='o') x=i,y=j;
		}
	dis[x][y]=0;
	qx.push_back(x);
	qy.push_back(y);
	while(!qx.empty())
	{
		int dx=qx.front(),
			dy=qy.front(); 
		qx.pop_front();
		qy.pop_front();
		if(dis[dx][dy]>dis[jx][jy]) continue ;
		for(int i=0;i<4;i++)
		{
			int dj=0,
				nextx=dx+fx[i],
				nexty=dy+fy[i];
			if(nextx<1 || nexty<1 || nextx>n || nexty>m ) continue ;
			if(i!=Map[dx][dy] && Map[dx][dy]!=5) dj++;
			if(dis[nextx][nexty]>dis[dx][dy]+dj)
			{
			if(dj==0) qx.push_front(nextx),qy.push_front(nexty);
			else  qx.push_back(nextx),qy.push_back(nexty);
			qq[nextx][nexty].x=dx;
			qq[nextx][nexty].y=dy;
			dis[nextx][nexty]=dis[dx][dy]+dj;
			}
		}
	}
	
	digui(jx,jy);
	Map[x][y]=5;
	cout<<dis[jx][jy]<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(Map[i][j]==0) cout<<'>';
			if(Map[i][j]==1) cout<<'<';
			if(Map[i][j]==2) cout<<'^';
			if(Map[i][j]==3) cout<<'v';
			if(Map[i][j]==5) cout<<'o';
			if(Map[i][j]==6) cout<<'x';
			if(Map[i][j]==7) cout<<'.';
		}
		cout<<endl;
	}
}
```


---

## 作者：Nephren_Sakura (赞：2)

题目描述：[link](https://www.luogu.com.cn/problem/P7284)

很明显，这题属于一个 bfs，bfs 中相邻两点的权值要么是 $0$，要么是 $1$，容易想到是个双端队列 bfs 或优先队列 bfs。

我采用了双端队列 bfs 写法。

在本题中，如果从当前点到目标点的方向正好等于当前点洋流的方向，权值为 $0$，将目标点从队头入队。

否则权值为 $1$，将目标点从队尾入队。

记录路径的话，从当前点到目标点的过程中，将 $pre_{nx,ny}$ 设为 $(x,y)$，最后从 $(ex,ey)$ 往前替换。

注意：

1. 提前设置方向。

1. 初始时 $dis$ 数组设为极大值

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return x*f;
}
inline void put(int x){
	if(x<0){
		putchar('-');
		put(-x);
		return;
	}
    if (x > 9) put(x / 10);
    putchar(x % 10 + 48);
}
struct node{
	int x,y;
}pre[2005][2005];
int n=read(),m=read(),sx,sy,tx,ty,dis[2005][2005];
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
char fangxiang[4]={'^','>','v','<'};//记录方向
char a[2005][2005];
void bfs(int x,int y){
	deque<node> dq;
	dis[x][y]=0;
	dq.push_back(node{x,y});
	while(dq.empty()==false){
		node cur=dq.front();
		dq.pop_front();
		if((cur.x==tx&&cur.y==ty)||dis[cur.x][cur.y]>=dis[tx][ty])
			continue;
		for(int i=0; i<4; i++){
			int nx=cur.x+dx[i],ny=cur.y+dy[i];
				int w;
				if(a[cur.x][cur.y]==fangxiang[i]||(cur.x==sx&&cur.y==sy))
					w=0;
				else
					w=1;
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&dis[nx][ny]>dis[cur.x][cur.y]+w){
				pre[nx][ny].x=cur.x;
				pre[nx][ny].y=cur.y;
				dis[nx][ny]=min(dis[nx][ny],dis[cur.x][cur.y]+w);
				if(w==0)
					dq.push_front(node{nx,ny});//权值为0，从队头入队
				else
					dq.push_back(node{nx,ny});//权值为1，从队尾入队
			}
		}
	}
}
signed main(){
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++){
			dis[i][j]=1e18;//初始化为极大值
			cin>>a[i][j];
			if(a[i][j]=='o')
				sx=i,sy=j;
			if(a[i][j]=='x')
				tx=i,ty=j;
		}
	bfs(sx,sy);
	if(dis[tx][ty]!=1e18)
		cout<<dis[tx][ty]<<endl;
	else
		cout<<0<<endl;
	node now=node{tx,ty};
	while(now.x!=sx||now.y!=sy){
		node cur=pre[now.x][now.y];
		for(int i=0; i<4; i++)
			if(cur.x+dx[i]==now.x&&cur.y+dy[i]==now.y&&(cur.x!=sx||cur.y!=sy))
				a[cur.x][cur.y]=fangxiang[i];
		now=cur;
	}//修改地图
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++)
			cout<<a[i][j];
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：sansesantongshun (赞：1)

这道题是一道较为隐蔽的双向广搜题。

乍一看好像没有思路，但是仔细一想就会发现：

从一个格子走到另一个格子，如果从原点移动或顺着洋流移动，不用改变任何格子，相当于边权为 $0$ ，否则需要把洋流改变为走的方向，进行了 $1$ 次改变，相当于边权为 $1$ 。

这样这道题就是一道很明显的双向广搜题。

边权为 $0$ 的情况，把搜的点放到队首，否则放到队尾。

对于记录修改过的节点，需要开一个数组记录它的上一个节点，也需要记录一下上一个节点需要改成什么。

（为什么不能记录本节点改成什么，因为本节点改变方式有很多种，而与下一个点对应的改变方式只有一种）

搜完后从汇点回溯，把经过的点逐个修改，最后输出矩阵即可。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sx,sy,ex,ey,b[2005][2005],x,y,xx,yy,dx[4]={-1,1,0,0},dy[4]={0,0,-1,1},c[2005][2005][3];//b记录距离，c记录其它信息
bool z;
char a[2005][2005],fh[4]={'^','v','<','>'};//预处理方向
struct node
{
	int x,y,d;
} nd;
deque<node> d;//双端队列
int main()
{
	memset(b,-1,sizeof(b));
	cin>>n>>m;
	for (int i=1;i<=n;++i)
	for (int j=1;j<=m;++j)
	{
		cin>>a[i][j];
		if (a[i][j]=='o')
		{
			sx=i;
			sy=j;
		}
		else if (a[i][j]=='x')
		{
			ex=i;
			ey=j;
		}
	}
	b[sx][sy]=0;
	d.push_back((node){sx,sy,0});
	while (!d.empty())
	{
		nd=d.front();
		d.pop_front();
		x=nd.x;
		y=nd.y;
		if (nd.d==b[x][y])//剪枝，如果该节点已经有更优解，那么久没必要再搜下去了
		for (int i=0;i<4;++i)
		{
			xx=x+dx[i];
			yy=y+dy[i];
			z=a[x][y]!='o' && a[x][y]!=fh[i];//是否需要改变
			if (0<xx && xx<=n && 0<yy && yy<=m && a[xx][yy]!='o' && (b[xx][yy]==-1 || b[x][y]+z<b[xx][yy]))//没搜过或有更优解
			{
				b[xx][yy]=b[x][y]+z;
				c[xx][yy][0]=i;//上一个点要被改成什么
				c[xx][yy][1]=x;
				c[xx][yy][2]=y;//上一个点坐标
				if (z)
				d.push_back((node){xx,yy,b[xx][yy]});//边权为1放到队尾
				else
				d.push_front((node){xx,yy,b[xx][yy]});//边权为0放到对首
			}
		}
	}
	cout<<b[ex][ey];
	xx=ex;
	yy=ey;//汇点
	x=c[xx][yy][1];
	y=c[xx][yy][2];//上一个节点
	while (x!=sx || y!=sy)
	{
		a[x][y]=fh[c[xx][yy][0]];//修改
		xx=x;
		yy=y;
		x=c[xx][yy][1];
		y=c[xx][yy][2];//本节点和上一个节点各向上爬一步
	}
	for (int i=1;i<=n;++i)
	{
		cout<<'\n';
		for (int j=1;j<=m;++j)
		cout<<a[i][j];
	}//输出矩阵
}
```

---

