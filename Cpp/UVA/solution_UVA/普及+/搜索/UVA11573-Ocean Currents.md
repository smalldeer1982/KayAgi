# Ocean Currents

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2620

[PDF](https://uva.onlinejudge.org/external/115/p11573.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11573/d1e2b8169cdc10fcb6efb334ec4201d016849d2c.png)

## 样例 #1

### 输入

```
5 5
04125
03355
64734
72377
02062
3
4 2 4 2
4 5 1 4
5 3 3 4```

### 输出

```
0
2
1```

# 题解

## 作者：Karry5307 (赞：9)

### 题意

给定一片 $n\times m$ 海域的洋流地图，从某个地方顺着洋流走不消耗体力，否则消耗体力。有 $T$ 组询问，每组询问需要你回答从 $(x_1,y_1)$ 到 $(x_2,y_2)$ 最少消耗多少体力。

$\texttt{Data Range:}1\leq n,m\leq 10^3,1\leq T\leq 50$

### 题解

一个显然的想法是优先队列 $\texttt{bfs}$。

考虑到本题隐式图上边权只有 $0$ 和 $1$，于是使用 $\texttt{01bfs}$ 代替。

整个 $\texttt{01bfs}$ 的操作过程如下所示：

如果这次走的边权为 $0$ 则将新的决策扔进队首否则扔进队尾。

这里给出一个正确性证明（也就是说这样子做可以保证队列中的元素有序）：

考虑数学归纳法，假设从开始到现在队列是有序的，那么队尾的值一定不大于队首的值加一。

否则由于边权只有 $0$ 和 $1$ 可以推出矛盾。

那么就是说整个队列可以被分为队首的值的一段和队首的值加一的一段。

然后容易证明对队首增广之后的队列仍然有序。

而且初始队列是有序的，于是就证明了 $\texttt{01bfs}$ 的正确性。

于是就可以写代码了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=1051;
struct Node{
	ll x,y;
};
deque<Node>q;
ll n,m,qcnt,sx,sy,ex,ey;
string s;
ll cur[MAXN][MAXN],dist[MAXN][MAXN];
ll vx[8]={-1,-1,0,1,1,1,0,-1},vy[8]={0,1,1,1,0,-1,-1,-1};
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void bfs()
{
	ll x,y,nxtx,nxty;
	while(!q.empty())
	{
		q.pop_back();
	}
	q.push_back((Node){sx,sy}),dist[sx][sy]=0;
	if(sx==ex&&sy==ey)
	{
		return;
	}
	while(!q.empty())
	{
		x=q.front().x,y=q.front().y,q.pop_front();
		if(x==ex&&y==ey)
		{
			return;
		}
		for(register int i=0;i<8;i++)
		{
			nxtx=x+vx[i],nxty=y+vy[i];
			if(1<=nxtx&&nxtx<=n&&1<=nxty&&nxty<=m)
			{
				if(dist[nxtx][nxty]<=dist[x][y]+(cur[x][y]!=i))
				{
					continue;
				}
				dist[nxtx][nxty]=dist[x][y]+(cur[x][y]!=i);
				if(i==cur[x][y])
				{
					q.push_front((Node){nxtx,nxty});
				}
				else
				{
					q.push_back((Node){nxtx,nxty});
				}
			}
		}
	}
}
int main()
{
	n=read(),m=read();
	for(register int i=1;i<=n;i++)
	{
		cin>>s;
		for(register int j=1;j<=m;j++)
		{
			cur[i][j]=s[j-1]-'0';
		}
	}
	qcnt=read();
	for(register int i=0;i<qcnt;i++)
	{
		sx=read(),sy=read(),ex=read(),ey=read();
		memset(dist,0x3f,sizeof(dist)),bfs();
		printf("%d\n",dist[ex][ey]);
	}
}
```

---

## 作者：封禁用户 (赞：1)

## 思路

本题只有 $0$ 和 $1$ 两种边权，不难想到 01 bfs。

大致思路就是用一个双端队列，边权为 $0$ 就放到队首，否则就放到队尾。本质上就是一个 bfs + 贪心。

[好题推荐](https://www.luogu.com.cn/training/464316)

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1005;
int n,m;
int a[N][N],d[N][N];
bool vis[N][N];
int dx[]={-1,-1,0,1,1,1,0,-1},dy[]={0,1,1,1,0,-1,-1,-1};
struct Node{
	int x,y;
};
void bfs(int sx,int sy,int tx,int ty){
	deque<Node> dq;
	dq.push_back({sx,sy});
	d[sx][sy]=0;
	while(!dq.empty()){
		Node tmp=dq.front();
		dq.pop_front();
		if(tmp.x==tx&&tmp.y==ty) return ;
		if(vis[tmp.x][tmp.y]) continue;
		vis[tmp.x][tmp.y]=1;
		for(int i=0;i<8;++i){
			int xx=dx[i]+tmp.x;
			int yy=dy[i]+tmp.y;
			if(xx<1||xx>n||yy<1||yy>m) continue;
			int ee=(i!=a[tmp.x][tmp.y]);
			if(d[tmp.x][tmp.y]+ee>=d[xx][yy]) continue;
			d[xx][yy]=d[tmp.x][tmp.y]+ee;
			if(ee==0) dq.push_front({xx,yy});
            else dq.push_back({xx,yy});
		}
	}
	return ;
}
signed main(){
	char ee;
	int t;
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>ee;
			a[i][j]=(ee-'0');
		}
	}cin>>t;
	int sx,sy,tx,ty;
	while(t--){
		cin>>sx>>sy>>tx>>ty;
		memset(d,0x7f,sizeof(d));
		memset(vis,0,sizeof(vis));
		bfs(sx,sy,tx,ty);
		cout<<d[tx][ty]<<endl;
	}
    return 0;
}
```

---

## 作者：让风忽悠你 (赞：1)

## 题意

给出一个 $l \times c$ 的矩阵，矩阵中元素 $0\thicksim7$ 代表当前点指向方向分别为**以北开始顺时针的八个方向**，向所指方向移动不需要花费体力，否则花费一个体力。

现有 $n$ 组询问，对于每一组询问，你需要给出由 $(rs,cs)$ 到 $(rd,cd)$ 的最短体力消耗。

$1 \le l,r \le 10^3 $，$1 \le T \le 10$

## 做法

对于每个节点，花费只有 1 和 0 两种情况，再加上数据范围，很容易判断出是个 01-bfs。

按照题意判断花费即可，注意初始化。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#define N 1005

using namespace std;
// 北 东北 东 东南 南 西南 西 西北 
const int ax[]={-1,-1,0,1,1,1,0,-1},ay[]={0,1,1,1,0,-1,-1,-1};
// 方向 
int l,c,T;
int map[N][N],step[N][N];
bool vis[N][N];
struct node{
	int x,y;
};

int bfs(int sx,int sy,int ex,int ey){
	memset(step,0x7f,sizeof(step));
	memset(vis,0,sizeof(vis));
	// 初始化 
	deque <node> q;
	q.push_back((node){sx,sy});
	step[sx][sy]=0;
	while(!q.empty()){
        node f=q.front();
		q.pop_front();
        if(f.x==ex && f.y==ey) return step[f.x][f.y];
        for(int i=0;i<8;i++){
            int nx=f.x+ax[i],ny=f.y+ay[i];
            if(nx<1 || nx>l || ny<1 || ny>c) continue;
            int w=(i!=map[f.x][f.y]);
            if(step[nx][ny]<=step[f.x][f.y]+w) continue;
            step[nx][ny]=step[f.x][f.y]+w;
            if(w) q.push_back((node){nx,ny});
            else q.push_front((node){nx,ny});
        }
    }
} // 01-bfs 


int main(){
	scanf("%d%d",&l,&c);
	for(int i=1;i<=l;i++)
		for(int j=1;j<=c;j++)
			scanf("%1d",&map[i][j]);
	scanf("%d",&T);
	while(T--){
		int rs,cs,rd,cd;
		scanf("%d%d%d%d",&rs,&cs,&rd,&cd);
		printf("%d\n",bfs(rs,cs,rd,cd));
	}
	return 0;
}
```


---

## 作者：lxg_honoka (赞：1)

[UVA11573 Ocean Currents](https://www.luogu.org/problem/UVA11573)

0/1BFS的裸题

边权只有0或1，若边权为0，则加入队首；若边权为1，则加入队尾。

应该不难理解，边权为0则优先走，或者说因为bfs的队列是递增的

给出代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;

const int maxn = 1000 + 10;
const int xx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};      //注意与题目保持一致
const int yy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
char mp[maxn][maxn];
int dis[maxn][maxn];                                //起点到每个点的距离
int n, m;

struct node
{
    int x, y;
}s, t;

deque<node> q;

void bfs ()
{
    q.push_back((node){s.x, s.y});

    while (!q.empty())
    {
        int x = q.front().x, y = q.front().y;
        q.pop_front();

        if (x == t.x && y == t.y)
            break;

        for (int i = 0; i < 8; i++)
        {
            int dx = x + xx[i], dy = y + yy[i];
            int w = (mp[x][y] - '0' != i);          //如果方向一致，边权为1
            if (dx >= 1 && dx <= n && dy >= 1 && dy <= n && dis[dx][dy] > dis[x][y] + w)    
            //进行松弛操作，省去了vis数组
            {
                dis[dx][dy] = dis[x][y] + w;
                if (w)                              //边权为1，加入队尾
                    q.push_back((node){dx, dy});
                else                                //边权为0，加入队首
                    q.push_front((node){dx, dy});
            }
        }
    }
}

int main()
{
    int time;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i]+1);
/*
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            printf("%c", mp[i][j]);
            if (j == m)
                printf("\n");
        }
*/
    cin >> time;
    while (time--)
    {
        memset(dis, 0x3f, sizeof(dis));         //初始化
        cin >> s.x >> s.y >> t.x >> t.y;
        dis[s.x][s.y] = 0;
        bfs();
        printf("%d\n", dis[t.x][t.y]);
    }

    return 0;
}

```


---

## 作者：Bobi2014 (赞：0)

这是一道 ~~可爱~~ 的 01bfs 题目。

### 前置知识

- [01bfs](https://blog.csdn.net/Mr_dimple/article/details/116864052)

### 题面转化

有一个 $n \times m$ 的二维数组，存储对于每个点走哪个方向步数加上 $0$，其他方向步数加上 $1$，有 $Q$ 组询问，查询两点之间的步数。

### 思路

观察数据范围，发现是支持 $O(n \times m \times Q)$ 的时间复杂度的，所以我们可以对每次询问做一次 01bfs，如果方向不需要增加步数，那么丢到队列前面，否则丢到后面。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int n,m,Q,vis[N][N],dx[8] = {-1,-1,0,1,1,1,0,-1},dy[8] = {0,1,1,1,0,-1,-1,-1};
char g[N][N];
bool in[N][N];
deque<pair<int,int> > q;
pair<int,int> s,t;
void bfs(){ // 01bfs
    memset(vis,127,sizeof(vis));
    memset(in,false,sizeof(in));
    q.clear();
    vis[s.first][s.second] = 0;
    q.push_back(s);
    in[s.first][s.second] = true;
    while(q.empty() == false){
        pair<int,int> u = q.front();
        q.pop_front();
        in[u.first][u.second] = false;
        for(int i = 0;i < 8;i ++){
            int x = u.first + dx[i],y = u.second + dy[i];
            if(x >= 1 and x <= n and y >= 1 and y <= m){
                bool val = (i + '0' != g[u.first][u.second]);
                if(vis[x][y] > vis[u.first][u.second] + val){
                    vis[x][y] = vis[u.first][u.second] + val;
                    if(in[x][y] == false){
                        in[x][y] = true;
                        if(val == true){
                            q.push_back(make_pair(x,y));
                        }else{
                            q.push_front(make_pair(x,y));
                        }
                    }
                }
            }
        }
    }
    cout << vis[t.first][t.second] << "\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for(int i = 1;i <= n;i ++){
        for(int j = 1;j <= m;j ++){
            cin >> g[i][j];
        }
    }
    cin >> Q;
    while(Q --){
        cin >> s.first >> s.second >> t.first >> t.second;
        bfs();
    }
    return 0;
}
```

---

## 作者：Enderich (赞：0)

## 题目大意
有一片大小为 $n \times m$ 的海洋，每一片海域上有一个数字代表这片海域水流指向的方向。这个数字范围为 $0$ 到 $7$。

![](https://cdn.luogu.com.cn/upload/image_hosting/t3q3pah5.png)

$0$ 代表指向上，$1$ 代表右上，$2$ 代表向右，$3$ 代表右下，$4$ 代表向下，$5$ 代表左下，$6$ 向左，$7$ 代表左上。


当你在一片海域时，可以用 $0$ 个代价沿着这片海域的水流流动方向前进 $1$ 次，也可以用 $1$ 个代价任意方向前进，但不能越界。现在告诉你起点和终点的坐标，问你最少需要多少代价。

还是道多测。

## 思路
01BFS 板板题。

代价要么为 $0$ 要么为 $1$ 很容易想到 01BFS。

大致思路就是用双段队列，若代价为 $0$ 则压入队首，否则压入队尾。如果搜到终点直接结束就完了。

## code
```cpp
/*
ID: enderch1
PROG:
LANG: C++
*/
#include<bits/stdc++.h>
#define int long long
#define change_max(a,b) a=max(a,b)
#define change_min(a,b) a=min(a,b)
using namespace std;
const int MAXN=1005;
const int MINN=10;
int dist[MAXN][MAXN];
int d[MINN][MINN]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};//方向数组。
int a[MAXN][MAXN];
struct node
{
    int x,y;
    int dis;
};
int sx,sy,dx,dy;
int n,m,T;
void bfs()  
{
    deque<node>q;
    dist[sx][sy]=0;//标记。
    q.push_back({sx,sy,0});
    while(!q.empty())
    {
        node temp=q.front();
        q.pop_front();
        if(temp.x==dx&&temp.y==dy)
        {//判终点。
            printf("%lld\n",temp.dis);
            return ;
        }
        for(int i=0;i<8;i++)
        {
            int tempx=temp.x+d[i][0],tempy=temp.y+d[i][1];
            if(n<tempx||tempx<1||m<tempy||tempy<1) continue;//盘边界。
            bool check;
            if(i!=a[temp.x][temp.y]) check=true;
            else check=false;
            if(dist[tempx][tempy]>temp.dis+check)
            {
                dist[tempx][tempy]=temp.dis+check;
                if(!check) q.push_front({tempx,tempy,temp.dis+check});
                else q.push_back({tempx,tempy,temp.dis+check});//压入队列。
            }
        }
    }
}
int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {s=s*10+ch-'0';ch=getchar();}
    return s*w;
}
void solve()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            char ch;
            cin>>ch;
            a[i][j]=ch-'0';//输入的时候是字符。
        }
    }
    T=read();
    while(T--)
    {
        memset(dist,0x3f,sizeof(dist));//初始化。
        sx=read(),sy=read(),dx=read(),dy=read();
        bfs();
    }
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    solve();
	return 0;
}

```
## The End

---

