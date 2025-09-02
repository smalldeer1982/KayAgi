# [USACO20DEC] Replication G

## 题目描述

在网上观看太多机械 DIY 视频的后果就是，Farmer John 偶然在他的农场上制造了一个可以自我复制的机器人！

农场可以用一个 $N×N$ 的方阵表示（$3≤N≤1000$），其中每个方格是空的或有岩石，并且所有边界上的方格均有岩石。某些没有岩石的方格被指定为机器人可能的起始位置。

Farmer John 初始将机器人放置在可能的起始位置之一。在之后的每一个小时，机器人的所有副本会沿着相同的方向移动一格，向北、向南、向东或向西。每 $D$ 个小时（$1≤D≤10^9$）之后，机器人的每个副本会进行自我复制——在方格 $(x,y)$ 进行自我复制的机器人会在方格 $(x+1,y)$、$(x−1,y)$、$(x,y+1)$ 以及 $(x,y−1)$ 产生机器人的新的副本；原本的机器人仍然位于 $(x,y)$。一段时间过后，同一方格内可能会有多个机器人。

如果移动或复制会使得任何一个机器人撞到岩石，那么所有的机器人均立刻停止行动。注意这意味着所有机器人最终必然会停下，由于农场的边界都是岩石。

请帮助奶牛们求出可能在某个时刻含有机器人的空的方格数量。 

## 说明/提示

### 样例 1 解释：
在以下的图中，x 表示机器人。

可能含有机器人的位置为：

```
##########
#xxx.....#
#xxxx....#
#xxx.....#
##########
#xx..xxx.#
##########
##########
##########
##########
```
以下是一个可能的事件序列：

FJ 将机器人放在了左上的起始位置。
机器人向右移动一个单位。
机器人进行自我复制。
所有机器人向右移动一个单位。
再一次自我复制会导致存在机器人撞到岩石，所以该过程终止。
```
##########    ##########    ##########    ##########
#........#    #........#    #.x......#    #..x.....#
#x.......#    #.x......#    #xxx.....#    #.xxx....#
#........#    #........#    #.x......#    #..x.....#
########## -> ########## -> ########## -> ##########
#........#    #........#    #........#    #........#
##########    ##########    ##########    ##########
##########    ##########    ##########    ##########
##########    ##########    ##########    ##########
##########    ##########    ##########    ##########
```
### 样例 2 解释：

可能含有机器人的位置为：
```
##########
#x#.xxx..#
#x#xxxxx.#
#xxxxxxxx#
#x#xxxxx.#
#x#.xxx..#
##########
##########
##########
##########
```
### 样例 3 解释：
可能含有机器人的位置为：
```
##########
#xx#.....#
#xx#.....#
#xxx.....#
#xx#.....#
#x.#.....#
##########
##########
##########
##########
```
### 测试点性质：

 - 测试点 4-5 满足 $D=10^9$。
 - 测试点 6-8 满足 $D=1$。
 - 测试点 9-12 满足 $N≤100$。
 - 测试点 13-20 没有额外限制。

供题：Benjamin Qi 

## 样例 #1

### 输入

```
10 1
##########
#........#
#S.......#
#........#
##########
#S....S..#
##########
##########
##########
##########```

### 输出

```
15```

## 样例 #2

### 输入

```
10 2
##########
#.#......#
#.#......#
#S.......#
#.#......#
#.#......#
##########
##########
##########
##########```

### 输出

```
28```

## 样例 #3

### 输入

```
10 2
##########
#.S#.....#
#..#.....#
#S.......#
#..#.....#
#..#.....#
##########
##########
##########
##########```

### 输出

```
10```

# 题解

## 作者：ybwowen (赞：16)

**性质1**：在机器人不会碰到岩石的前提下，对于每一个点，我们尽量让初始的机器人直接经过这个点，而不是让副本覆盖到这个点。

证明：因为$D\ge1$，副本向外扩展的速度最多和初始的机器人移动的速度一样快。在合法的前提下，如果机器人能扩展到这个点，那么它一定能够经过这个点。

**性质2**：在使得经过的点最多的情况下，每个点最多只能经过一次。

证明：根据性质1，我们尽量让初始的机器人直接经过一个点。当我们第二次经过某个点时，相较于第一次到达时我们又多花费了一些时间，机器人要么在这段时间里进行复制，使得我们能够直接经过的点变少，要么虽然还没有复制，但是相较于第一次经过时离下一次复制的时间更近了。

上面两个性质是本题能够使用**BFS**求解的基础。

我们进行第一遍BFS，初始时向队列里加入每一个‘#’点，计算出每个点所能接受的机器人最多复制的次数，即每个点离它最近的‘#’的距离。

随后我们进行第二遍BFS，初始时向队列里加入每一个起点，尽可能的多经过点。

现在我们该统计答案了。我们如何快速计算出每个点？这也是本题最后一个难点。

对于每个目前我们已经经过的节点，我们将三元组$(x,y,t)$加入一个**优先队列**中，其中$x,y$是这个点的坐标，$t$是这个点最多能向外扩展多少步，优先队列按照$t$从大到小排序。每次我们取出优先队列的队头，然后向优先队列中加入$(x,y-1,t-1)$，$(x,y+1,t-1)$，$(x-1,y,t-1)$和$(x+1,y,t-1)$，并给这些点打上标记。最后我们统计所有被打上标记的点的个数，就是答案了。

为什么这么做是对的呢？考虑每一个点在上述过程中可能被扩展到多个合法的$t$值，显然$t$值最大的是最优的。通过$t$值从大到小排序，我们保证了每次的扩展都是最优的。

前两次BFS的复杂度是$O(n^2)$的，最后一次BFS中，每一个节点最多只会扩展一次。由于我们使用了一个有限队列，所以时间复杂度为$O(n^2 \log n)$。

总的时间复杂度为$O(n^2 \log n)$。

注意在本题中，是先扩展再复制，对于这种细节我们要进行相应的处理，具体见代码。



```c++
#include<bits/stdc++.h>
#define mp make_pair
#define F first
#define S second
#define pb push_back
#define lson k<<1
#define rson k<<1|1
//#define getchar nc
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const ll INF64 = 1e18;

inline char nc(){
	static char buf[100005],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	char ch=getchar(); int sum=0; int f=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) sum=(sum<<1)+(sum<<3)+(ch^48),ch=getchar();
	return f?-sum:sum;
}
const int maxn=1e3+5;
int n,d;
char a[maxn][maxn];
int nearest[maxn][maxn];
int v[maxn][maxn];
int ans[maxn][maxn];
int mark[maxn][maxn];
int vis[maxn][maxn];
const int dx[]={-1,0,1,0},dy[]={0,-1,0,1};
struct Node{
	int x,y,t;
};
queue<Node>q; 
inline bool in(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=n;
}
inline bool check(int x,int y,int t){
	return t/d<=nearest[x][y]-1;
}
inline void bfs1(){
	queue<pii>q; while(!q.empty()) q.pop();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]=='#') q.push(mp(i,j)),vis[i][j]=1;
	while(!q.empty()){
		int x=q.front().F,y=q.front().S; q.pop();
		for(int i=0;i<4;i++){
			int xx=x+dx[i],yy=y+dy[i];
			if(!in(xx,yy)||a[xx][yy]=='#'||vis[xx][yy]) continue;
			nearest[xx][yy]=nearest[x][y]+1;
			vis[xx][yy]=1; q.push(mp(xx,yy));
		}
	}
}
inline void bfs2(){
	queue<Node>q; while(!q.empty()) q.pop();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(a[i][j]=='S')
				q.push((Node){i,j,0}),v[i][j]=0;
		}	
	while(!q.empty()){
		int x=q.front().x,y=q.front().y,t=q.front().t; q.pop();
		if(t/d>=nearest[x][y]){
			mark[x][y]=1; continue;
		} 
		for(int i=0;i<4;i++){
			int xx=x+dx[i],yy=y+dy[i],tt=t+1;
			if(!in(xx,yy)||v[xx][yy]!=-1||a[xx][yy]=='#') continue;
			if(check(xx,yy,t)) v[xx][yy]=tt,q.push((Node){xx,yy,tt}); 
		}
	}
}
struct Point{
	int x,y,k;
	bool operator <(const Point &tmp)const{
		return tmp.k>k;
	}
};
inline void bfs3(){
	priority_queue<Point>q; while(!q.empty()) q.pop();
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(v[i][j]!=-1) q.push((Point){i,j,v[i][j]}),vis[i][j]=1;
	while(!q.empty()){
		int x=q.top().x,y=q.top().y,k=q.top().k; q.pop();
		if(!k) continue;
		for(int i=0;i<4;i++){
			int xx=x+dx[i],yy=y+dy[i];
			if(!in(xx,yy)||vis[xx][yy]||a[xx][yy]=='#') continue;
			vis[xx][yy]=1; q.push((Point){xx,yy,k-1});
		}
	}
}
int main(){
	n=read(); d=read();
	for(int i=1;i<=n;i++) scanf("%s",a[i]+1);
	bfs1();
	memset(v,-1,sizeof(v));	
	bfs2();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(v[i][j]!=-1){
				v[i][j]/=d;
				if(mark[i][j]) v[i][j]--;
			}
	bfs3();
	int res=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			res+=vis[i][j];
	printf("%d\n",res);
	return 0;
}
```



---

## 作者：xh39 (赞：13)

算法:①广度优先搜索(学习此算法前,还需先学习队列)。②堆。

请先学习上述2种方法,否则你将大概率看不懂本题解。

为方便,将岩石距离称作该点到达最近的岩石的距离,比如样例#1的岩石距离为
```cpp
##########
#11111111#
#12222221#
#11111111#
##########
#11111111#
##########
##########
##########
##########
```
求岩石距离相信大家都会,将所有的岩石都入队然后bfs,这里不详细讲。直接看代码。
```cpp
struct qwh2q3tg20{
	int x,y,step;
}shi[1000005];
int gox[105]={0,0,1,-1};
int goy[105]={1,-1,0,0};
//...
	memset(zyl,-1,sizeof(zyl));
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			cin>>A;
			if(A=='#'){ //如果是岩石,将其入队。记录其x,y。
				a[i][j]=1;
				shi[sr].x=i;
				shi[sr].y=j;
				shi[sr].step=0;
				zyl[i][j]=0;
				sr++;
			}
		}
	}
	while(sl<sr){ //求出岩石距离。
		ns=shi[sl].step+1;
		for(i=0;i<4;i++){ //枚举4个方向。
			nx=shi[sl].x+gox[i];
			ny=shi[sl].y+goy[i];
			if(zyl[nx][ny]<0&&nx>0&&ny>0&&nx<n&&ny<n){ //没走出边界并且没被搜过就入队。
				shi[sr].x=nx;
				shi[sr].y=ny;
				shi[sr].step=ns;
				zyl[nx][ny]=ns;
				sr++;
			}
		}
		sl++; //一定要记得将队首元素(即目前已经拓展完了的点)出队。
	}
```
然后,我们再用一轮新的广度优先搜索求**初始**机器人能到达哪里。

初始机器人能通过一个点必须其副本(即复制的机器人)也不能撞到岩石。

当第dis秒,机器人已经复制了dis÷d次。所以距离它dis÷d的格子都充满了机器人。(d为题目中给出的d,请查看题面)

如果此点的岩石距离等于dis÷d,那么肯定会有机器人撞到岩石,但注意题面说的是"每 d 个小时**之后**"才会复制。所以机器人可以走到该点,但走到后就不能再拓展了。具体见代码。

```cpp
//...
	memset(dis,-1,sizeof(dis));
	while(jl<jr){
		if(ji[jl].step/d>=zyl[ji[jl].x][ji[jl].y]){ //如果相等,那么说明在dis秒后会撞到岩石,所以不能继续拓展了,continue;
			jl++; //一定要注意将不能拓展的点出队,否则会卡死。
			continue;
		}
		ns=ji[jl].step+1;
		for(i=0;i<4;i++){
			nx=ji[jl].x+gox[i];
			ny=ji[jl].y+goy[i];
			if(dis[nx][ny]<0&&((ns-1)/d<zyl[nx][ny])&&!a[nx][ny]){ //没被走过&&复制的机器人能够到达&&不是岩石。
				ji[jr].x=nx;
				ji[jr].y=ny;
				ji[jr].step=ns;
				dis[nx][ny]=ns;
				jr++;
			}
		}
		jl++;
	}
```
最后,我们只求出了初始机器人到达的位置,怎么求副本呢?

我们可以求出机器人到达每个格子时复制了多少次,设复制次数为x,那么离该格子距离在x之内的格子全部都可以。所以将所有初始机器人走到的格子加入一个队列。

但是这个队列不再满足单调性了,所以不能直接bfs,于是我们想到了优先队列(用堆实现)。(改步骤有点类似于dijkstra)

在实现时,我们采用与前两个部分截然不同的方法:先将点的距离赋值为dis,然后不断减一,直到减到0。(相当于将边权视为-1)。

实现见代码。(建议这一部分一定看代码,因为实现有些困难)。

```cpp
	xyq t,top;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(dis[i][j]>=0){ //将所有初始机器人到达的点入队。
				t.x=i;
				t.y=j;
				t.di=min(dis[i][j]/d,zyl[i][j]-1); //算出复制次数。注意与zyl[i][j]-1取min,因为如果dis/d==zyl,那么说明此刻复制会撞到岩石,所以不能复制。那么就要减一。
				kkksc03.push(t);
				mark[i][j]=1;
				sum++;
			}
		}
	}
	while(!kkksc03.empty()){
		top=kkksc03.top();
		kkksc03.pop();
		if(!top.di){ //如果被减为0了,就不能再拓展了。
			continue;
		}
		ns=top.di-1; //不断减一。
		for(i=0;i<4;i++){
			nx=top.x+gox[i];
			ny=top.y+goy[i];
			if(!mark[nx][ny]&&!a[nx][ny]){ //没被走过。 
				mark[nx][ny]=1;
				t.x=nx;
				t.y=ny;
				t.di=ns;
				kkksc03.push(t);
				sum++; //表示有一个点可以到达。用sum统计
			}
		}
	}
	cout<<sum; //输出答案。
```
总结:

①输入并求出岩石距离。

②求出初始机器人机器人能到达的位置及其离```S```的距离。

③求出其它机器人可能在的位置,并统计答案,输出。

完整代码(注释都写在前面的代码了,所以没什么注释):
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
bool a[1005][1005],mark[1005][1005];
int zyl[1005][1005],dis[1005][1005]; //zyl:岩石距离。dis:机器人距离。 
struct dai_ma_shi_xian_ye_tai_nan_le_ba___tiao_le_wo_san_xiao_shi_________{
	int x,y,step;
}shi[1000005],ji[1000005];
int gox[105]={0,0,1,-1};
int goy[105]={1,-1,0,0};
struct xyq{
	int x,y,di,step;
	friend bool operator <(const xyq &s1,const xyq &s2){
		return s1.di<s2.di;
	}
};
priority_queue<xyq> kkksc03;
int main(){
	memset(zyl,-1,sizeof(zyl));
	memset(dis,-1,sizeof(dis));
	freopen("rep.in","r",stdin);
	freopen("rep.out","w",stdout);
	char A;
	int n,i,j,d,sl=0,sr=0,jl=0,jr=0,nx,ny,ns,sum=0,def;
	cin>>n>>d;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			cin>>A;
			if(A=='#'){
				a[i][j]=1;
				shi[sr].x=i;
				shi[sr].y=j;
				shi[sr].step=0;
				zyl[i][j]=0;
				sr++;
			}
			if(A=='S'){
				a[i][j]=1;
				ji[jr].x=i;
				ji[jr].y=j;
				ji[jr].step=0;
				dis[i][j]=0;
				jr++;
			}
		}
	}
	while(sl<sr){ //求出石头距离。
		ns=shi[sl].step+1; 
		for(i=0;i<4;i++){
			nx=shi[sl].x+gox[i];
			ny=shi[sl].y+goy[i];
			if(zyl[nx][ny]<0&&nx>0&&ny>0&&nx<n&&ny<n){
				shi[sr].x=nx;
				shi[sr].y=ny;
				shi[sr].step=ns;
				zyl[nx][ny]=ns;
				sr++;
			}
		}
		sl++;
	}
	while(jl<jr){ //求出机器人距离。
		if(ji[jl].step/d>=zyl[ji[jl].x][ji[jl].y]){
			jl++;
			continue;
		}
		ns=ji[jl].step+1;
		for(i=0;i<4;i++){
			nx=ji[jl].x+gox[i];
			ny=ji[jl].y+goy[i];
			if(dis[nx][ny]<0&&((ns-1)/d<zyl[nx][ny])&&!a[nx][ny]){ //没被走过&&复制的机器人能够到达&&不是墙。
				ji[jr].x=nx;
				ji[jr].y=ny;
				ji[jr].step=ns;
				dis[nx][ny]=ns;
				jr++;
			}
		}
		jl++;
	}
	xyq t,top;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(dis[i][j]>=0){
				t.x=i;
				t.y=j;
				t.di=min(dis[i][j]/d,zyl[i][j]-1);
				kkksc03.push(t);
				mark[i][j]=1;
				sum++;
			}
		}
	}
	while(!kkksc03.empty()){ //求出最终机器人在的位置并统计答案。
		top=kkksc03.top();
		kkksc03.pop();
		if(!top.di){
			continue;
		}
		ns=top.di-1;
		def=top.step+1;
		for(i=0;i<4;i++){
			nx=top.x+gox[i];
			ny=top.y+goy[i];
			if(!mark[nx][ny]&&!a[nx][ny]){ //没被走过。 
				mark[nx][ny]=1;
				t.x=nx;
				t.y=ny;
				t.di=ns;
				t.step=def;
				kkksc03.push(t);
				sum++;
			}
		}
	}
	cout<<sum;
	return 0;
}
```
题目简单,但代码长,细节多,易写错。

---

## 作者：MVP_Harry (赞：5)

提供一个$O(n^2)$的做法，其实就是三次BFS，参考了官方题解。

我们不难观察到，每次扩展出来的形状是一个“菱形”。更切确的说，如果一个菱形的中心在$(x, y)$，并扩展了$k$次，另一个点$(a, b)$属于这个菱形，当且仅当$|x-a| + |y - b| \le k.$我们将每个中心所能达到最大的$k$叫做它的半径。


这就给我们提供了一个思路 —— 用BFS找出哪些点是合法的“中心”。一个中心可以扩展$k$次，当且仅当离它最近的石头的距离大于$k$.

由此，我们可以用三个BFS来解决问题。

* 第一步，预处理出每个点离最近的石头的距离。我们将所有石头当成“源点”即可。

* 第二步，找出合适的“中心”。该怎么做呢？由于贪心，我们可以找出到达某个点的最短时间，再根据它与最近的石头的距离，判断它是否能成为顶点。

* 第三步，此时我们已经找到了合适的中心，在它们的“半径”之内的点显然都可以达到。然而，朴素的枚举需要$O(n^4)$，显然是不可接受的。我们再次采用BFS，源点就是那些中心，但这些中心并不是同时入队的，而是按照其半径递减的顺序入队。

如下是我的代码，注意开```long long```

```
#include<bits/stdc++.h>
#define ll long long
#define rep(i, m, n) for (ll i = m; i <= n; i++)
#define per(i, m, n) for (ll i = m; i >= n; i--)
#define pii pair<ll, ll>
#define pb push_back
#define mp make_pair
#define INF 0x3f3f3f3f
using namespace std;

const ll maxn = 1e3 + 5;

ll N, D;
ll dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
ll ans[maxn][maxn], dist_rock[maxn][maxn], dist_source[maxn][maxn];

vector<pii> rocks, starts, centers[maxn * maxn];

char grid[maxn][maxn];

ll check(ll x, ll y) {
    return 1 <= x && x <= N && 1 <= y && y <= N;
}

void BFS1() {
    memset(dist_rock, -1, sizeof dist_rock);
    queue<pii> q;
    for (auto p : rocks) {
        q.push(p);
        dist_rock[p.first][p.second] = 0;
    }
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        rep(i, 0, 3) {
            ll x = p.first + dx[i], y = p.second + dy[i];
            if (!check(x, y)) continue;
            if (dist_rock[x][y] != -1) continue;
            dist_rock[x][y] = dist_rock[p.first][p.second] + 1;
            q.push(mp(x, y));
        }
    }
}

void BFS2() {
    memset(dist_source, -1, sizeof dist_source);
    queue<pii> q;
    for (auto p : starts) {
        q.push(p);
        dist_source[p.first][p.second] = 0;
    }
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        ans[p.first][p.second] = 1;
        ll now_dist = dist_source[p.first][p.second];
        centers[dist_rock[p.first][p.second] - 1].push_back(p);
        if (now_dist >= D * dist_rock[p.first][p.second]) continue;
        rep(i, 0, 3) {
            ll x = p.first + dx[i], y = p.second + dy[i];
            if (!check(x, y) || dist_source[x][y] != -1 || grid[x][y] != '.') continue;
            ll to_dist = now_dist + 1;
            if (to_dist > D * dist_rock[x][y]) continue;
            dist_source[x][y] = to_dist;
            q.push(mp(x, y));
        }
    }
}

void BFS3() {
    vector<pii> bfs_list, next_stage;
    per(i, N * N - 1, 0) {
        swap(bfs_list, next_stage);
        next_stage.clear();
        for (auto now : bfs_list) {
            rep(j, 0, 3) {
                ll x = now.first + dx[j], y = now.second + dy[j];
                if (!check(x, y) || ans[x][y] || grid[x][y] != '.') continue;
                ans[x][y] = 1;
                next_stage.push_back(mp(x, y));
            }
        }
        for (auto p : centers[i])
            next_stage.push_back(p);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> D;
    rep(i, 1, N) cin >> (grid[i] + 1);
    rep(i, 1, N) {
        rep(j, 1, N) {
            if (grid[i][j] == 'S') starts.push_back(mp(i, j));
            else if (grid[i][j] == '#') rocks.push_back(mp(i, j));
        }
    }

    BFS1();
    BFS2();
    BFS3();

    ll tot = 0;
    rep(i, 1, N) rep(j, 1, N) tot += ans[i][j];
    cout << tot << "\n";

    return 0;
}
```

---

## 作者：DYYqwq (赞：2)

谁能想到这玩意只需要 bfs？

首先我们~~注意力惊人~~注意到这个复制机器人就是个幌子。因为机器人扩展的速度最多就和原版机器人的移动速度打个平手（$d \geq 1$），本质上不被墙撞死的话，任何能扩展到的地方原版机器人都是能走到的。因此我们尽量让原版机器人疲于奔命，而不是让它躺平只靠扩展占领空地。

接着，很显然为了经历的点足够多，肯定不能重复走点。

于是我们直接想到 bfs 求解。

我们发现机器人的扩展必然导致机器人被墙撞死，于是我们可以用一个 bfs 处理一下一个机器人最多的扩展次数，当然就是处理它和最近的岩石的距离。

然后我们启动第二次 bfs，这次的任务是让原版机器人疯狂冲刺，让它经过的点最多。注意这里小心判断一下会不会撞死。然后记录一下这个机器人经过了什么点。

接着我们就需要统计答案了。我们考虑使用优先队列进行统计。我们在优先队列中打入 $(x,y,val)$ 表示当前点坐标是 $(x,y)$，还能向外扩展 $val$ 步。我们以 $val$ 作为第一关键字从大到小排序。这样扩展显然是最优的。至于如何扩展是很显然的：向优先队列中打入 $(x-1,y,val-1),(x+1,y,val-1),(x,y-1,val-1),(x,y+1,val-1)$。把这些点都在地图上标记出来最后加和就好了。

我们分析一下时间复杂度。前两次就是平凡的 $O(n^2)$ 的 bfs。第三次也很平凡，因为我们每个节点最多只扩展 $1$ 次，只不过我们使用了优先队列，于是总时间复杂度为 $O(n^2\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x , y , val;
	bool operator < (const node &qwq) const
	{
		return val < qwq.val;
	}
};
struct node2
{
	int x , y , val;
};
struct pr
{
	int x , y;
};
int n , d , dx[5] = {-1 , 0 , 0 , 1} , dy[5] = {0 , -1 , 1 , 0} , dis[1010][1010] , ans , vis2[1010][1010];
//string c[1010];
char c[1010][1010];
bool vis[1010][1010] , died[1010][1010];
queue<pr> q1;
queue<node2> q2;
priority_queue<node> q3;
void debug()
{
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= n ; j ++) printf("vis2[%d][%d]:%d died[%d][%d]:%d\n" , i , j , vis2[i][j] , i , j , died[i][j]);
}
bool in(int x , int y)
{
	return x >= 1 && x <= n && y >= 1 && y <= n;
}
bool alive(int x , int y , int val)
{
	return (val / d) <= dis[x][y] - 1;
}
void bfs_init()
{
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= n ; j ++) if(c[i][j] == '#') q1.push((pr){i , j}) , vis[i][j] = 1;
}
void bfs()
{
	while(!q1.empty())
	{
		int x = q1.front().x , y = q1.front().y;
		q1.pop();
		for(int i = 0 ; i < 4 ; i ++)
		{
			int nx = x + dx[i] , ny = y + dy[i];
			if(in(nx , ny) && (c[nx][ny] != '#') && !vis[nx][ny]) dis[nx][ny] = dis[x][y] + 1 , vis[nx][ny] = 1 , q1.push((pr){nx , ny});
		}
	}
}
void bfs2_init()
{
	memset(vis , 0 , sizeof(vis));
	memset(vis2 , -1 , sizeof(vis2));
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= n ; j ++) if(c[i][j] == 'S') q2.push((node2){i , j , 0}) , vis2[i][j] = 0;
}
void bfs2()
{
	while(!q2.empty())
	{
		int x = q2.front().x , y = q2.front().y , val = q2.front().val;
		q2.pop();
		if(val / d >= dis[x][y]) {died[x][y] = 1;continue;}
		for(int i = 0 ; i < 4 ; i ++)
		{
			int nx = x + dx[i] , ny = y + dy[i] , nval = val + 1;
			if(in(nx , ny) && (c[nx][ny] != '#') && !vis[nx][ny] && alive(nx , ny , val)) vis[nx][ny] = 1 , vis2[nx][ny] = nval , q2.push((node2){nx , ny , nval});
		}
	}
}
void bfs3_init()
{
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= n ; j ++) if(vis2[i][j] != -1) vis2[i][j] = vis2[i][j] / d - (died[i][j]);
	memset(vis , 0 , sizeof(vis));
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= n ; j ++) if(vis2[i][j] != -1) q3.push((node){i , j , vis2[i][j]}) , vis[i][j] = 1;
}
void bfs3()
{
	while(!q3.empty())
	{
		int x = q3.top().x , y = q3.top().y , val = q3.top().val;
		q3.pop();
		if(val == 0) continue;
		for(int i = 0 ; i < 4 ; i ++)
		{
			int nx = x + dx[i] , ny = y + dy[i];
			if(in(nx , ny) && (c[nx][ny] != '#') && !vis[nx][ny]) vis[nx][ny] = 1 , q3.push((node){nx , ny , val - 1});
		}
	}
}
void get_ans()
{
	for(int i = 1 ; i <= n ; i ++) for(int j = 1 ; j <= n ; j ++) ans += vis[i][j];
}
int main()
{
	scanf("%d%d" , &n , &d);
	for(int i = 1 ; i <= n ; i ++)
	{
		string s;
		cin >> s;
		s = '_' + s;
//		cin >> c[i];
//		c[i] = '_' + c[i];
		for(int j = 1 ; j <= n ; j ++) c[i][j] = s[j];
	}
	bfs_init();
	bfs();
	bfs2_init();
	bfs2();
//	debug();
	bfs3_init();
	bfs3();
	get_ans();
	printf("%d" , ans);
	return 0;
}
```

---

## 作者：ClearluvXL (赞：1)

# Replication 复制
## 题意解读
   本题的机器人复制怎么理解？请见下图 
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/ob55k8vm.png)
   
   由红色扩张到黄色再到绿色，我们发现，每个颜色的格子到原来的那一个机器人的曼哈顿距离都是一样的，并且都有 $dis\leq$ 扩张次数。那么，为避免将一整块的机器人移动,我们只需要记录中心的坐标，以及他的扩张次数，就能确定整个块的大小和范围。
   
   我们先预处理出每个空格子到最近的石头的距离，只需将石头当作源点，向外扩张即可，这个用个 BFS 轻松搞定。处理这个有什么用呢？如果我们走到了一个点，并知道最小步数（为什么是最小步数？因为步数最小就能保证扩张次数最小，也就是碰到石头的概率越小）我们就能判断走到这个点会不会停下来了。比如：下图红色点为将要到达的新的中心，黑色点为石头，扩张次数为5，而 $distrock[红色点]=5$ 所以此时就不会走出这一步。
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/9xpbkybd.png)
   
   那么我们就可以进行第二次 BFS，用于找出每个可能是中心的点以及他们的扩张次数。扩张次数就等于 $step\div d$。关键的一点：**我们是走出这一步后才加上这一步**。 什么意思呢？对于要扩张的那步，我们是先走出这一步，再进行扩张，所以再写代码时要特别注意。
   
```c++
 void bfs2(){	
	queue<node> q;
	memset(vis , 0 , sizeof vis);
	memset(st , -1 , sizeof st);
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= n ; j ++)
			if(c[i][j] == 'S'){
				q.push({i,j,0});
				st[i][j]=0;
			} 
			
	while(!q.empty()){
		auto [x,y,val]=q.front();	
		q.pop();
		if(val/d>=disrock[x][y]) {
			died[x][y]=1;
			//died表示能走到这，但是扩张之后会碰到石头，所以扩张次数-1
			continue;
		}
		for(int i = 0 ; i < 4 ; i ++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			int nval=val+1;
			if(!check(nx , ny)||c[nx][ny]== '#'||vis[nx][ny]||!alive(nx,ny,val)) continue;
			//alive里面传的是当前步数的原因就是当前还没有算这一步 
			vis[nx][ny]=1;
			st[nx][ny]=nval;//st此时为步数 
			q.push({nx,ny,nval});
		}
	}
}//end
 ```
 
 最后我们就只需要从每个中心向外扩张，就能得到所有机器人能够到达的点了。为了避免重复计算，我们以扩张次数为第一关键字，从大到小向外扩张。而扩张的过程无非就是 $[x,y,k]$ 转移到了 $[x-1,y,k-1]$，$[x,y-1,k-1]$，$[x+1,y,k-1]$，$[x,y+1,k-1]$ 这些点去了。这个也只需要一个 BFS 即可搞定。
   
## 总体代码实现
 细节偏多
```c++
#include<bits/stdc++.h>
#define endl '\n'
#define fi first
#define se second
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=1010;

struct node{
	int x,y,val;
	bool operator < (const node &b) const{
		return val < b.val;
	}
};

int n , d;
int dx[5] = {-1 , 0 , 0 , 1};
int dy[5] = {0 , -1 , 1 , 0};
int disrock[N][N],ans,st[N][N];
char c[N][N];
bool vis[N][N],died[N][N];

bool check(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=n;
}//end

bool alive(int x,int y,int val){
	return (val/d) <= disrock[x][y]-1;
}//end

void bfs1(){
	memset(vis,0,sizeof vis);
	queue<pii> q;
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= n ; j ++) 
			if(c[i][j] == '#'){
				q.push({i , j});
				vis[i][j] = 1;
			} 
			
	while(!q.empty()){
		auto [x,y]=q.front();
		q.pop();
		for(int i = 0 ; i < 4 ; i ++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(!check(nx , ny)||c[nx][ny]=='#'||vis[nx][ny]) continue;
			disrock[nx][ny] = disrock[x][y] + 1;
			vis[nx][ny] = 1;
			q.push({nx , ny});
		}
	}
}//end

void bfs2(){	
	queue<node> q;
	memset(vis , 0 , sizeof vis);
	memset(st , -1 , sizeof st);
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= n ; j ++)
			if(c[i][j] == 'S'){
				q.push({i,j,0});
				st[i][j]=0;
			} 
			
	while(!q.empty()){
		auto [x,y,val]=q.front();	
		q.pop();
		if(val/d>=disrock[x][y]) {
			died[x][y]=1;
			//died表示能走到这，但是扩张之后会碰到石头，所以扩张次数-1
			continue;
		}
		for(int i = 0 ; i < 4 ; i ++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			int nval=val+1;
			if(!check(nx , ny)||c[nx][ny]== '#'||vis[nx][ny]||!alive(nx,ny,val)) continue;
			//alive里面传的是当前步数的原因就是当前还没有算这一步 
			vis[nx][ny]=1;
			st[nx][ny]=nval;//st此时为步数 
			q.push({nx,ny,nval});
		}
	}
}//end

void bfs3(){
	
	priority_queue<node> q;
	
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= n ; j ++) 
			if(st[i][j] != -1){
				st[i][j] = st[i][j] / d - (died[i][j]);
				//将st转化成扩张次数 
			} 

	memset(vis , 0 , sizeof(vis));
	
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= n ; j ++)
			if(st[i][j] != -1){
				q.push({i,j,st[i][j]});
				vis[i][j] = 1;
			} 
	
	while(!q.empty()){
		auto [x,y,val]=q.top();
		q.pop();
		if(val == 0) continue;
		for(int i = 0 ; i < 4 ; i ++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(!check(nx,ny)||c[nx][ny]== '#'||vis[nx][ny]) continue;
			vis[nx][ny] = 1;
			q.push({nx , ny , val - 1});
		}
	}
}//end

int main(){
	
//	freopen("replication.in","r",stdin);
//	freopen("replication.out","w",stdout);
	
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin>>n>>d;	
	for(int i = 1;i <= n;i++) cin>>c[i]+1;
	
	bfs1();
	bfs2();
	bfs3();
	
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) {
			if(vis[i][j]) ans++;
		}
	}
	
	cout<<ans<<endl;
	
	return 0;

}//end
```

---

## 作者：MolotovM (赞：1)

## 堆优化搜索
作为本juruo在这次USACO Gold切掉的唯一一道题

还是比较可做的

考虑将机器人位置认为在中心的机器人处

则可以把所有机器人看做“不断膨胀的球”

对于每个点预处理出可以容纳的球的大小即就是离最近的石头的距离

第一次BFS搜索，用一个小根堆维护到每个点的最早时间

第二次BFS搜索，用一个大根堆维护到每个点机器人可以展开的最多个数

统计可到达点即可

时间复杂度： ~~O(玄学)~~ O(可过)
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int Read(){
  	int s = 0 , w = 1;
	char ch = getchar();
	while(ch > '9' || ch < '0'){
		if(ch == '-') w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		s = (s << 1) + (s << 3) + ch - '0';
		ch = getchar();
	}
	return s * w;
}
const int MAXN = 1e3 + 50;
int s[MAXN][MAXN],ear[MAXN][MAXN],num[MAXN][MAXN];
int n,k;
int mx[4] = {1,0,-1,0};
int my[4] = {0,1,0,-1};
priority_queue<pair<int,pair<int,int> > >e,l; 
int main(){
	n = Read() , k = Read();
	memset(s,127,sizeof(s));
	memset(ear,127,sizeof(ear));
	for(int i = 1 ; i <= n ; i ++){
		for(int j = 1 ; j <= n ; j ++){
			char ch = getchar();
			while(ch != 'S' && ch != '#' && ch != '.') ch = getchar();
			if(ch == 'S'){
				e.push(make_pair(0,make_pair(i,j)));
				ear[i][j] = 0;
			}
			if(ch == '#') s[i][j] = 0;
		}
	}
	priority_queue<pair<int,pair<int,int> > >rock;
	for(int i = 1 ; i <= n ; i ++){
		for(int j = 1 ; j <= n ; j ++){
			if(!s[i][j]) rock.push(make_pair(0,make_pair(i,j)));
		}
	}
	while(!rock.empty()){
		int i = rock.top().second.first , j = rock.top().second.second;
		rock.pop();
		for(int d = 0 ; d < 4 ; d ++){
			if(i + mx[d] <= 0 || i + mx[d] > n || j + my[d] <= 0 || j + my[d] > n) continue;
			if(s[i + mx[d]][j + my[d]] > s[i][j] + 1){
				s[i + mx[d]][j + my[d]] = s[i][j] + 1;
				rock.push(make_pair(- (s[i][j] + 1),make_pair(i + mx[d],j + my[d])));
			}
		}
	}
	while(!e.empty()){
		int x = e.top().second.first , y = e.top().second.second;
		int t = - e.top().first;
		e.pop();
		if(t > ear[x][y]) continue;
		if(ear[x][y] / k >= s[x][y]) continue;
		for(int d = 0 ; d < 4 ; d ++){
			if(!s[x + mx[d]][y + my[d]]) continue;
 			if(x + mx[d] <= 0 || x + mx[d] > n || y + my[d] <= 0 || y + my[d] > n) continue;
			if(ear[x + mx[d]][y + my[d]] > t + 1){
				ear[x + mx[d]][y + my[d]] = t + 1;
				e.push(make_pair(- (t + 1),make_pair(x + mx[d],y + my[d])));
			}
		}
	}
	priority_queue<pair<int,pair<int,int> > >rb;
	for(int i = 1 ; i <= n ; i ++){
		for(int j = 1 ; j <= n ; j ++){
			if(ear[i][j] < 19260817){
				rb.push(make_pair(1 + min(s[i][j] - 1,ear[i][j] / k),make_pair(i,j)));
			}
		}
	}
	while(!rb.empty()){
		int x = rb.top().second.first , y = rb.top().second.second;
		int t = rb.top().first;
		rb.pop();
		if(t <= num[x][y]) continue;
		num[x][y] = t;
		for(int d = 0 ; d < 4 ; d ++){
			if(x + mx[d] <= 0 || x + mx[d] > n || y + my[d] <= 0 || y + my[d] > n) continue;
			if(num[x + mx[d]][y + my[d]] <= t - 1){
				rb.push(make_pair(t - 1,make_pair(x + mx[d],y + my[d])));
			}
		}
	}
	int ans = 0;
	for(int i = 1 ; i <= n ; i ++){
		for(int j = 1 ; j <= n ; j ++){
			ans += (0 != num[i][j]);
		}
	}
	cout << ans << endl;
	return 0;
}

```


---

## 作者：Thunder_S (赞：0)

[不一样的体验。](https://www.cnblogs.com/Livingston/p/15167015.html)

## Solution

首先我们可以求出每个点距离最近的岩石的距离，来判断能否走到这个点。

同时因为机器人可以放置在任何一个起始位置，所以对于每个不是岩石或者起始点的点，可以求出它到最近的起始点的距离，来表示初始机器人走到那个点的时间。

但走的时候要注意，只有**能走到**才能走。

就是说如果到达这个点的时候，副本机器人撞到岩石了，那么这个点就不能继续往下扩展了。

那么什么情况下是无法到达呢？

现在我们已经知道了当前点距离最近的起点的距离，那么就可以算出产生出来的副本距离当前点的曼哈顿距离，也就是 $\lfloor \dfrac{dis_{x,y}}{d}\rfloor$。

用这个去跟当前距离最近岩石的距离比较一下，如果大于等于距离最近岩石的距离，就说明副本机器人撞岩石了，就不用从这个点继续扩展了。

上面的两个都可以用 $\text{bfs}$ 来处理。

那么现在对于初始机器人可以直接走到的位置都已经处理出来了（即 $dis_{i,j}\ge 0$ 的位置），我们离解决这题只剩下求出副本机器人到的位置数量。

注：首先避免重复，可以把算过的位置打上标记。

这里我们考虑将 $\text{bfs}$ 的方式调转一下，对于初始机器人能到达的位置，从这个位置往外扩展来走到副本机器人能走到的位置。

而这个向外走的距离，要么是到达此点时复制机器人的次数，或者是到最近的岩石距离减去 1，代表着岩石与当前位置之间的空位。

但此时的队列并不一定满足单调，所以要将队列转成优先队列来模拟大根堆。

## Code

```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#define N 1005
using namespace std;
struct node
{
	int x,y,dis;
};
struct node1
{
	int x,y,dis;
	friend bool operator <(const node1 &X,const node1 &Y) {return X.dis<Y.dis;}
};
queue<node> q_rock,q_robot;
priority_queue<node1> getans;
int n,d,ans,fx[5]={0,1,-1,0,0},fy[5]={0,0,0,1,-1},a[N][N],torock[N][N],frorobot[N][N];
bool bj[N][N];
char s[N];
int main()
{
	memset(torock,-1,sizeof(torock));
	memset(frorobot,-1,sizeof(frorobot));
	scanf("%d%d",&n,&d);
	for (int i=1;i<=n;++i)
	{
		scanf("%s",s+1);
		for (int j=1;j<=n;++j)
		{
			if (s[j]=='#')
			{
				a[i][j]=1;
				node x;
				x.x=i;x.y=j;x.dis=0;
				q_rock.push(x);
				torock[i][j]=0;
			}
			if (s[j]=='S')
			{
				a[i][j]=1;
				node x;
				x.x=i;x.y=j;x.dis=0;
				q_robot.push(x);
				frorobot[i][j]=0;
			}
		}
	}
	while (!q_rock.empty())
	{
		node u=q_rock.front();q_rock.pop();
		for (int i=1;i<=4;++i)
		{
			int xx=u.x+fx[i],yy=u.y+fy[i];
			if (torock[xx][yy]<0&&xx>=1&&yy>=1&&xx<=n&&yy<=n)
			{
				torock[xx][yy]=u.dis+1;
				node x;
				x.x=xx;x.y=yy;x.dis=u.dis+1;
				q_rock.push(x);
			}
		}
	}
	while (!q_robot.empty())
	{
		node u=q_robot.front();q_robot.pop();
		if (u.dis/d>=torock[u.x][u.y]) continue;
		for (int i=1;i<=4;++i)
		{
			int xx=u.x+fx[i],yy=u.y+fy[i];
			if (frorobot[xx][yy]<0&&u.dis/d<torock[xx][yy]&&!a[xx][yy])
			{
				frorobot[xx][yy]=u.dis+1;
				node x;
				x.x=xx;x.y=yy;x.dis=u.dis+1;
				q_robot.push(x);
			}
		}
	}
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
			if (frorobot[i][j]>=0)
			{
				node1 x;
				x.x=i;x.y=j;x.dis=min(frorobot[i][j]/d,torock[i][j]-1);
				getans.push(x);
				bj[i][j]=true;
				++ans;
			}
	while (!getans.empty())
	{
		node1 u=getans.top();getans.pop();
		if (!u.dis) continue;
		for (int i=1;i<=4;++i)
		{
			int xx=u.x+fx[i],yy=u.y+fy[i];
			if (!bj[xx][yy]&&!a[xx][yy])
			{
				bj[xx][yy]=true;
				node1 x;
				x.x=xx;x.y=yy;x.dis=u.dis-1;
				getans.push(x);
				++ans;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```



---

