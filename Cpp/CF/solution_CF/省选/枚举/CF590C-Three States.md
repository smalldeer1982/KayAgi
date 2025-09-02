# Three States

## 题目描述

The famous global economic crisis is approaching rapidly, so the states of Berman, Berance and Bertaly formed an alliance and allowed the residents of all member states to freely pass through the territory of any of them. In addition, it was decided that a road between the states should be built to guarantee so that one could any point of any country can be reached from any point of any other State.

Since roads are always expensive, the governments of the states of the newly formed alliance asked you to help them assess the costs. To do this, you have been issued a map that can be represented as a rectangle table consisting of $ n $ rows and $ m $ columns. Any cell of the map either belongs to one of three states, or is an area where it is allowed to build a road, or is an area where the construction of the road is not allowed. A cell is called passable, if it belongs to one of the states, or the road was built in this cell. From any passable cells you can move up, down, right and left, if the cell that corresponds to the movement exists and is passable.

Your task is to construct a road inside a minimum number of cells, so that it would be possible to get from any cell of any state to any cell of any other state using only passable cells.

It is guaranteed that initially it is possible to reach any cell of any state from any cell of this state, moving only along its cells. It is also guaranteed that for any state there is at least one cell that belongs to it.

## 样例 #1

### 输入

```
4 5
11..2
#..22
#.323
.#333```

### 输出

```
2```

## 样例 #2

### 输入

```
1 5
1#2#3
```

### 输出

```
-1
```

# 题解

## 作者：AKPC (赞：10)

### 前言
![](https://cdn.luogu.com.cn/upload/image_hosting/b7z54ne9.png)

然后花了一会时间学习了 `01bfs`，最后直接把这~~模拟~~题[切](https://www.luogu.com.cn/record/125293921)了，~~你以为我真想cos刻晴啊~~。
### 思路
前置知识就是 `01bfs`，讲这个之前你需要知道 `dijstra` 的实现。`01bfs` 就是在边权为 $0$ 或 $1$ 的时候进行最短路搜索，因为 `dijstra` 使用的优先队列插入需要 $\text O(\log n)$ 的时间复杂度，但是因为 `01bfs` 只处理两种边权，那么可以转换为双端队列维护 `dijstra` 的优先队列，$0$ 边权放入队列首，$1$ 放入队列尾。这也就相当于是 `dijstra` 的优化。

知道了这个前置知识之后就可以看题目了。首先在三个国家之中，是不用修道路的，在 `.` 部分需要花费 $1$ 个代价修道路，`#` 则是不可走的。显然在任意国的国土中是不用修道路的（包括 `123` 这种情况，这三个国家也都是联通的），我们可以将国土部分格子的连线边权设为 $0$，`.` 参与连线的部分边权为 $1$，`#` 不能走，遇到的时候就不搜索它就行了。

然后你设置边权之后会发现了，这很符合 `01bfs` 的条件。用 `01bfs` 来搜索三个国家到其他点的最小代价（经过 `.` 花费 $1$ 代价）。然后暴力搜索一个点，根据这个点，修路的长度就是这个点到三个国家的距离（如果搜索的点是 `.` 需要减二，不然会把这个点的路修三次），最后取个最小值输出即可（没有修路方案输出 $-1$）。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define mpr make_pair
inline int read(){
    int x=0;bool f=1;register char c=getchar();
    while(c<48||c>57){if(c=='-') f=0;c=getchar();}
    while(c>=48&&c<=57){x=x*10+(c^48);c=getchar();}
    return f?x:-x;
}
const int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
int n,m,a[1005][1005],f[4][1005][1005],minn=1e18;
bool t[4],tmp[1005][1005];
char ch[1005][1005];
void bfs(int ux,int uy,int sb){
	deque<pair<pair<int,int>,int> >que;
	que.push_front(mpr(mpr(ux,uy),0));
	memset(tmp,0,sizeof(tmp));
	while (!que.empty()){
		const int x=que.front().first.first,y=que.front().first.second,dep=que.front().second;
		que.pop_front(),f[sb][x][y]=dep;
//		cout<<x<<' '<<y<<' '<<dep<<' '<<sb<<'\n';
		for (int i=0;i<4;i++){
			const int cx=x+dx[i],cy=y+dy[i];
			if (cx<1||cy<1||cx>n||cy>m) continue;
			if (tmp[cx][cy]) continue;
			if (a[cx][cy]==0) que.push_back(mpr(mpr(cx,cy),dep+1)),tmp[cx][cy]=1;
			if (a[cx][cy]==1) que.push_front(mpr(mpr(cx,cy),dep)),tmp[cx][cy]=1;
		}
	}
}
signed main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			f[1][i][j]=f[2][i][j]=f[3][i][j]=1e18;
			cin>>ch[i][j];
			if (ch[i][j]=='1'||ch[i][j]=='2'||ch[i][j]=='3') a[i][j]=1;
			else if (ch[i][j]=='.') a[i][j]=0;
			else a[i][j]=-1;
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			if (ch[i][j]=='1'&&t[1]==0) bfs(i,j,1),t[1]=1;
			if (ch[i][j]=='2'&&t[2]==0) bfs(i,j,2),t[2]=1;
			if (ch[i][j]=='3'&&t[3]==0) bfs(i,j,3),t[3]=1;
		}
//	for (int xx=1;xx<=3;xx++){
//		for (int i=1;i<=n;i++){
//			for (int j=1;j<=m;j++) cout<<f[xx][i][j]<<' ';
//			cout<<'\n';
//		}
//		cout<<'\n';
//	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			if (ch[i][j]=='.') minn=min(minn,f[1][i][j]+f[2][i][j]+f[3][i][j]-2);
			else if (ch[i][j]!='#') minn=min(minn,f[1][i][j]+f[2][i][j]+f[3][i][j]);
		}
	if (minn<1e18) cout<<minn;
	else cout<<-1;
	return 0;
}
```


---

## 作者：SmallTownKid (赞：6)

边权只有 $0/1$ ，国家之间边权为 $0$ ，荒地之间边权为 $1$ ，石头不能走， $01BFS$ ，开双端队列。 $O(nm)$ 预处理出三个国家到图中每个点的最短距离，再 $O(nm)$ 枚举每个点算出答案。注意，如果枚举的这个点是荒地，这个点会被多加$2$ ，因为我们用 $BFS$ 算点权最短路时把终点也加上了。跑了三次最短路就多加了两次。
```
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
struct node{
	int x,y;
};
const int dx[5]={0,0,1,-1};
const int dy[5]={1,-1,0,0};
char ch[1010][1010];
int dis[1010][1010][5];//多一维
bool vis[1010][1010]; 
int n,m;
long long minn=0x3f3f3f3f3f3f3f3f;
void bfs(int s)
{
	deque<node> q;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(ch[i][j]-'0'==s)
			{
				dis[i][j][s]=0;
				q.push_back((node){i,j});
			}
		}
	}
	while(q.size())
	{
		node u=q.front();
		q.pop_front();
		int x=u.x;
		int y=u.y;
		for(int i=0;i<4;i++)
		{
			int xx=x+dx[i];
			int yy=y+dy[i];
			if(xx<1||xx>n||dis[x][y][s]+1>=dis[xx][yy][s]||yy<1||yy>m||ch[xx][yy]=='#')
			continue;
			if(ch[xx][yy]=='.')//标准01BFS
			{
				dis[xx][yy][s]=dis[x][y][s]+1;
				q.push_back((node){xx,yy});
			}
			else 
			{
				dis[xx][yy][s]=dis[x][y][s];
				q.push_front((node){xx,yy});
		    }
		}
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>ch[i][j];
		}
	}
	memset(dis,INF,sizeof(dis));
	bfs(1);
	bfs(2);
	bfs(3);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			long long cost=1ll*dis[i][j][1]+dis[i][j][2]+dis[i][j][3];
			if(ch[i][j]=='.')//如果是荒地的话会被多加两次 
			cost-=2;//如果是这个点在某个国家里，就不会被多加 
			minn=min(minn,cost);
		}
	}
	if(minn>=INF)
	cout<<"-1";
	else cout<<minn;
	return 0;
} 
```

---

## 作者：MyukiyoMekya (赞：5)

就这 4 种情况

```
1 - A - 2  |  1 - 2 - 3  |  1 - 3 - 2  |  2 - 1 - 3
    |      |             |             |
    3      |             |             |
```

第一种情况可能和后面的三种重合，导致计算出错误的答案，但是错误的答案显然不优，所以不用管。

算出 3 种连通块到每个点的距离，以及连通块两两之间的最短距离，算一下取个最小值就好了。

因为边权都是 1，bfs 就行。

注意这里距离转换为要填充的方块数，有些细节要注意。

$\texttt{Code}$

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define mem(x,y) memset(x,y,sizeof x)
#define ln std::puts("")
#define lsp std::putchar(32)
#define pb push_back
#define MP std::make_pair
const int MaxN=1050;
const int dir[4][2]={1,0,0,1,-1,0,0,-1};
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
template <class t>inline bool checkmin(t&x,t y){if(x>y){x=y;return 1;}return 0;}
char s[MaxN][MaxN];
#define fi first
#define se second
std::vector<std::pair<int,int> > a[3];
int dis[4][MaxN][MaxN];
int n,m;
inline void bfs(int opt)
{
	std::mem(dis[opt],0x28);
	std::queue<std::pair<int,int> > Q;
	for(auto i:a[opt])
		Q.push(i),dis[opt][i.fi][i.se]=0;
	while(!Q.empty())
	{
		reg std::pair<int,int> u=Q.front();Q.pop();
		for(int i=0;i<4;++i)
		{
			reg int nx=u.fi+dir[i][0],ny=u.se+dir[i][1];
			if(!nx||nx>n||!ny||ny>m||dis[opt][nx][ny]<6e8||s[nx][ny]=='#')
				continue;
			dis[opt][nx][ny]=dis[opt][u.fi][u.se]+1;
			Q.push(MP(nx,ny));
		}
	}
}
signed main(void)
{
	read(n,m);
	for(int i=1;i<=n;++i)
		std::scanf("%s",s[i]+1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(isdigit(s[i][j]))
				a[s[i][j]-'0'].pb(MP(i,j));
	for(int i=1;i<=3;++i)
		bfs(i);
	reg int ans=0x7f7f7f7f;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			checkmin(ans,dis[1][i][j]+dis[2][i][j]+dis[3][i][j]-2);
	reg int dis12,dis23,dis13;
	dis12=dis23=dis13=0x7f7f7f7f;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			checkmin(dis12,dis[1][i][j]+dis[2][i][j]-1),
			checkmin(dis23,dis[2][i][j]+dis[3][i][j]-1),
			checkmin(dis13,dis[1][i][j]+dis[3][i][j]-1);
	checkmin(ans,dis12+dis13);
	checkmin(ans,dis12+dis23);
	checkmin(ans,dis13+dis23);
	if(ans>6e8)
		std::puts("-1");
	else
		write(ans),ln;
	return 0;
}
```



---

## 作者：wxzzzz (赞：4)

### 思路

先 bfs 求出每个国家 $num$ 到每个点的距离，到本国领土的距离为 $0$。

然后最短铺路方案有几种情况：
	
- $1→2→3$ 或 $1→3→2$ 或 $2→1→3$（两两国家之间铺路）
    
- $1→x,2→x,3→x$（三条路径通往交汇点 $x$）

在所有情况中取最小值即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
int ans = 1e18, head, tail, t[4][4], dis[4][1005][1005];
struct node {
    int x, y;
} q[1005 * 1005 << 1];
char g[1005][1005];
void bfs(int num) {
    head = 0, tail = -1;
    memset(dis[num], 0x3f, sizeof dis[num]);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (g[i][j] - 48 == num)
                q[++tail] = {i, j}, dis[num][i][j] = 0;

    while (head <= tail) {
        int x = q[head].x, y = q[head++].y;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];

            if (dis[num][nx][ny] > 2e6 && nx >= 1 && nx <= n && ny >= 1 && ny <= m && g[nx][ny] != '#')
                dis[num][nx][ny] = dis[num][x][y] + 1, q[++tail] = {nx, ny};
        }
    }
}
int main() {
    memset(t, 0x3f, sizeof t);
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> g[i] + 1;

    for (int i = 1; i <= 3; i++)
        bfs(i);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (dis[1][i][j] <= 2e6 && dis[2][i][j] <= 2e6 && dis[3][i][j] <= 2e6)
                ans = min(ans, dis[1][i][j] + dis[2][i][j] + dis[3][i][j] - 2);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            t[1][2] = min(t[1][2], dis[1][i][j] + dis[2][i][j] - 1);
            t[1][3] = min(t[1][3], dis[1][i][j] + dis[3][i][j] - 1);
            t[2][3] = min(t[2][3], dis[2][i][j] + dis[3][i][j] - 1);
        }
    }

    ans = min(ans, t[1][2] + t[2][3]);
    ans = min(ans, t[1][3] + t[2][3]);
    ans = min(ans, t[1][3] + t[1][2]);

    if (ans > 2e6)
        cout << "-1";
    else
        cout << ans;

    return 0;
}
```

---

## 作者：封禁用户 (赞：3)

虽然是一道div1的C题，其实想通了就不难。对于每个洲，跑一次bfs,预处理出每个点的最短距离，然后枚举每个点作为中介点和以一个洲为中介点的情况，取最小值即可。
记得关注我的博客哦：https://www.luogu.org/blog/Noi2017/
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=10000000;
const int N=1005;
const int dx[]={0,-1,1,0},dy[]={-1,0,0,1};
int dis[N][N][4];
char mp[N][N];
vector<pair<int,int>> a[4];
queue<pair<pair<int,int>,int>> q;
int main()
{
	int n,m,x,y,kx,ky,kdis,ans,sum,d1_2=INF,d1_3=INF,d2_3=INF;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",mp[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=1;k<=3;k++)
				dis[i][j][k]=INF;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(mp[i][j]>='1'&&mp[i][j]<='3')
				a[mp[i][j]-'0'].push_back(make_pair(i,j));
	while(!q.empty())
		q.pop();
	for(int i=0;i<a[1].size();i++)
	{
		q.push(make_pair(make_pair(a[1][i].first,a[1][i].second),0));
		dis[a[1][i].first][a[1][i].second][1]=0;
	}
	while(!q.empty())
	{
		pair<pair<int,int>,int> k=q.front();
		q.pop();
		kx=k.first.first;
		ky=k.first.second;
		kdis=k.second;
		for(int i=0;i<4;i++)
		{
			x=kx+dx[i];
			y=ky+dy[i];
			if(x<1||x>n||y<1||y>m||mp[x][y]=='#')
				continue;
			if(kdis+1<dis[x][y][1])
			{
				dis[x][y][1]=kdis+1;
				q.push(make_pair(make_pair(x,y),kdis+1));
			}
		}
	}
	while(!q.empty())
		q.pop();
	for(int i=0;i<a[2].size();i++)
	{
		q.push(make_pair(make_pair(a[2][i].first,a[2][i].second),0));
		dis[a[2][i].first][a[2][i].second][2]=0;
	}
	while(!q.empty())
	{
		pair<pair<int,int>,int> k=q.front();
		q.pop();
		kx=k.first.first;
		ky=k.first.second;
		kdis=k.second;
		for(int i=0;i<4;i++)
		{
			x=kx+dx[i];
			y=ky+dy[i];
			if(x<1||x>n||y<1||y>m||mp[x][y]=='#')
				continue;
			if(kdis+1<dis[x][y][2])
			{
				dis[x][y][2]=kdis+1;
				q.push(make_pair(make_pair(x,y),kdis+1));
			}
		}
	}
	while(!q.empty())
		q.pop();
	for(int i=0;i<a[3].size();i++)
	{
		q.push(make_pair(make_pair(a[3][i].first,a[3][i].second),0));
		dis[a[3][i].first][a[3][i].second][3]=0;
	}
	while(!q.empty())
	{
		pair<pair<int,int>,int> k=q.front();
		q.pop();
		kx=k.first.first;
		ky=k.first.second;
		kdis=k.second;
		for(int i=0;i<4;i++)
		{
			x=kx+dx[i];
			y=ky+dy[i];
			if(x<1||x>n||y<1||y>m||mp[x][y]=='#')
				continue;
			if(kdis+1<dis[x][y][3])
			{
				dis[x][y][3]=kdis+1;
				q.push(make_pair(make_pair(x,y),kdis+1));
			}
		}
	}
	/*Debug
	for(int k=1;k<=3;k++)
	{
		printf("dis%d:\n",k);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
				if(dis[i][j][k]==0x3f3f3f3f)
					printf("X ");
				else
					printf("%d ",dis[i][j][k]);
			printf("\n");
		}
	}*/
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(mp[i][j]=='1')
			{
				d1_2=min(d1_2,dis[i][j][2]);
				d1_3=min(d1_3,dis[i][j][3]);
			}
			if(mp[i][j]=='2')
			{
				d1_2=min(d1_2,dis[i][j][1]);
				d2_3=min(d2_3,dis[i][j][3]);
			}
			if(mp[i][j]=='3')
			{
				d1_3=min(d1_3,dis[i][j][1]);
				d2_3=min(d2_3,dis[i][j][2]);
			}
		}
	}
	ans=min(min(d1_2+d1_3,d1_2+d2_3),d1_3+d2_3);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			sum=0;
			for(int k=1;k<=3;k++)
				sum+=dis[i][j][k];
			ans=min(ans,sum);
		}
	}
	printf("%d\n",ans>=INF?-1:ans-2);
	return 0;
}

```

---

## 作者：Juanzhang (赞：2)

**思路：**

- $bfs$预处理$+$枚举

可以发现，最后的答案无非就是以下两种情况：

![map1](https://cdn.luogu.com.cn/upload/pic/25390.png)

![map2](https://cdn.luogu.com.cn/upload/pic/25392.png)

于是，我们只需处理出每一点距三个国家的最短距离，枚举每一个点，分类讨论一下两种情况即可。

但是，我们又可以将两种情况合并：对于枚举的每一个点$map_{i,j}$，两种情况的答案都是$distance_{1,i,j}+distance_{2,i,j}+distance_{3,i,j}$，只不过第二种情况是点$map_{i,j}$位于某一国内。但是需注意第一种情况$map_{i,j}$会被记录三次，因此当$map_{i,j}$为$'.'$时要将答案减$2$。

注意$bfs$可以函数化。

**代码**

``` cpp
#include <bits/stdc++.h>
using namespace std;

#define fir first
#define sec second

typedef pair <int, int> pii;
const int maxn = 1010;
const int maxlen = 3e7 + 10;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
pii q[maxlen];
char a[maxn][maxn];
int n, m, l, r, dp[3][maxn][maxn];

bool pd(int x, int y) {
	return x > 0 && y > 0 && x <= n && y <= m;
}

bool out(int x, int y) {
	for (int i = 0; i < 4; i++) {
		int tx = x + dx[i], ty = y + dy[i];
		if (pd(tx, ty) && (a[tx][ty] == '.' || a[tx][ty] == '#')) {
			return 1;
		}
	}
	return 0;
}

void bfs(int clr) {
	l = 1.5e7 + 1, r = 1.5e7;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == clr + 49) {
				dp[clr][i][j] = 0;
				q[++r] = make_pair(i, j);
			}
		}
	}
	for (; l <= r; ) {
		pii u = q[l++];
		int dist = dp[clr][u.fir][u.sec];
		for (int i = 0; i < 4; i++) {
			pii v = make_pair(u.fir + dx[i], u.sec + dy[i]);
			if (pd(v.fir, v.sec) && a[v.fir][v.sec] != '#') {
				int cost = a[v.fir][v.sec] == '.';
				if (dist + cost < dp[clr][v.fir][v.sec]) {
					dp[clr][v.fir][v.sec] = dist + cost;
					if (cost) {
						q[++r] = v;
					} else {
						q[--l] = v;
					}
				}
			}
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int k = 0; k < 3; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				dp[k][i][j] = 1e8;
			}
		}
	}
	gets(a[0]);
	for (int i = 1; i <= n; i++) {
		gets(a[i] + 1);
	}
	for (int i = 0; i < 3; i++) {
		bfs(i);
	}
	int ans = 1e8;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			ans = min(ans, dp[0][i][j] + dp[1][i][j] + dp[2][i][j] - (a[i][j] == '.' ? 2 : 0));
		}
	}
	printf("%d", ans >= 1e8 ? -1 : ans);
	return 0;
}
```

---

## 作者：orz_z (赞：1)

可以发现图只有一种情况：即可以找到一点与三个联通块相连，使得答案最小。

那么对于每个点，`bfs` 计算它与三个联通块的距离之和，取最小值即可。

时间复杂度 $\mathcal O(nm \alpha)$。

---

## 作者：wizardMarshall (赞：0)

## 题意

有 $3$ 个国家的领土，在字符矩阵里表示为 `1`，`2` 与 `3`。同时还存在石头和荒地，询问需要将多少荒地开成路才能让三个国家联通。

同一个国家领土自身一定联通。

## 思路

感觉紫有点高了。

先处理出同一个国家到任何一个格子的最短路（标记为 $d_{i,j,k}$，表示国家 $k$ 到 $(i,j)$ 格子所需的最短路径），然后分类讨论。由于领土不是单一格子，因此可以采取类似多源最短路的做法。

一种情况是在国家间直接连边，比如找出国家 $1$ 和国家 $2$ 间的最短路，加上国家 $2$ 和国家 $3$ 间的最短路。大力判断即可。

还有一种情况是三个国家的路径交于同一点，这个也很简单，找到任意一个是荒地的 $(i,j)$，直接计算 $d_{i,j,1}+d_{i,j,2}+d_{i,j,3}$ 即可。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
char s[2005][2005];
int d[1005][1005][5];
int xx[5] = {1, -1, 0, 0};
int yy[5] = {0, 0, 1, -1};
int n, m;
int dd[5][5];//国家间的最短路
void dij(int id) {
	queue <pair <int, int> > q;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s[i][j] == '0' + id) {
				q.push({i, j});
				d[i][j][id] = 0;
			}
		}
	}
	while (!q.empty()) {
		pair <int, int> f = q.front();q.pop();
		if (s[f.first][f.second] >= '1' && s[f.first][f.second] <= '3') {
			dd[id][s[f.first][f.second] - '0'] = min(dd[id][s[f.first][f.second] - '0'], d[f.first][f.second][id]);
		}
		for (int k = 0; k < 4; k++) {
			int nowx = f.first + xx[k], nowy = f.second + yy[k];
			if (nowx >= 1 && nowx <= n && nowy >= 1 && nowy <= m) {
				if (s[f.first][f.second] != '#' && d[f.first][f.second][id] + 1 < d[nowx][nowy][id]) {
					d[nowx][nowy][id] = d[f.first][f.second][id] + 1;
					q.push({nowx, nowy});
				}
			}
		}
	}
	return;
}
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%s", s[i] + 1);
	}
	memset(dd, 127, sizeof(dd));
	memset(d, 127, sizeof(d));
	dij(1);dij(2);dij(3);
	int ans = 1e9;
	if (dd[1][2] < 1e9 && dd[2][3] < 1e9)ans = min(ans, dd[1][2] + dd[2][3] - 2);
	if (dd[1][3] < 1e9 && dd[3][2] < 1e9)ans = min(ans, dd[1][3] + dd[3][2] - 2);
	if (dd[2][1] < 1e9 && dd[1][3] < 1e9)ans = min(ans, dd[2][1] + dd[1][3] - 2);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s[i][j] == '.') {
				if (d[i][j][1] < 1e9 && d[i][j][2] < 1e9 && d[i][j][3] < 1e9) {
					ans = min(ans, d[i][j][1] + d[i][j][2] + d[i][j][3] - 2);
				}
			}
		}
	}
	if (ans >= 1e9)cout << -1;
	else cout << ans;
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
不是很难的题，感觉比上一道线段树的 $2200$ 简单。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
首先不难发现，这三个国家连通只有两种情况：
1. 三个国家都连到一个交汇点 $k$。
2. 三个国家互相连通。

考虑先处理出 $f_{k,i,j}$ 表示 $k$ 号国家走到格子 $i,j$ 的最小代价。

如果处理出了这个东西，再跑一个简单的朴素 dp 即可。

接着来考虑怎么处理这个玩意。

考虑建图，如果数字直接走边权显然为 $0$，走到了 `.` 边权则为 $1$。

接着再跑一个最短路就行了。

但是注意时间复杂度，不难发现炸飞了。

考虑这个最短路的特殊之处，边权只有 $0/1$，这里便要引入一个强大的东西：**$01$ bfs**。

其实也就是堆优化的 dij 了，不过根本没必要用堆，直接把 $0$ 的扔前面去，$1$ 的扔后面去，就手动堆优化了。

最后再跑一遍 dp 即可。

**注意：初值不要太大当心溢出。**
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1010,INF=0x3f3f3f3f3f3f3f3f;
int n,m,ans=INF,t[4],mp[N][N],f[4][N][N];char s[N][N];
int dxy[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='#'||c=='.'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void bfs(int x,int y,int c)
{
    deque<pair<pair<int,int>,int>>q;q.push_back({{x,y},0});memset(mp,0,sizeof mp);
    while(!q.empty())
    {
        auto [j,ss]=q.front();auto [x,y]=j;q.pop_front();f[c][x][y]=ss;
        for(int i=0,dx,dy;i<4;i++)
        {
            dx=x+dxy[i][0],dy=y+dxy[i][1];
            if(dx<1||dy<1||dx>n||dy>m||mp[dx][dy]) continue;
            if(s[dx][dy]=='#') continue;mp[dx][dy]=1;
            if(s[dx][dy]=='.') q.push_back({{dx,dy},ss+1});
            else q.push_front({{dx,dy},ss}),mp[dx][dy]=1;
        }
    }
}
signed main()
{
    n=read(),m=read();for(int i=1;i<=n;i++) rd(s[i],m=0);memset(f,20,sizeof f);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(s[i][j]=='1'&&!t[1]) t[1]=1,bfs(i,j,1);
            if(s[i][j]=='2'&&!t[2]) t[2]=1,bfs(i,j,2);
            if(s[i][j]=='3'&&!t[3]) t[3]=1,bfs(i,j,3);
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(s[i][j]=='.') ans=min(ans,f[1][i][j]+f[2][i][j]+f[3][i][j]-2);
            else if(s[i][j]!='#') ans=min(ans,f[1][i][j]+f[2][i][j]+f[3][i][j]);
    print(ans>1000000?-1:ans);
    genshin:;flush();return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

比较基本的图论。

## 思路

肯定不能跑多元最短路。

于是换着来做 bfs，将每个国家的城市先全部压入 bfs 的队列中，然后按照距离跑一遍即可，这样得到的就是每个国家距离国外每个城市的距离。

考虑如何计算，有一个结论是最短路径上有一个点使得其到三个国家路径没有重复点。考虑感性证明一下。

类似归纳证明，随意在路径中选出一点，证明将它移动后可以得到一个满足要求的点。

如果该点满足要求，证明完毕（边界）。

否则，如果该点周围存在 $1$ 条连出去的边使得该方向有 $2/3$ 个城市，将它往此方向移一格。

然后归纳可得到该点。

然后我们就可以枚举这个点然后计算他到三个国家的距离了。

这样交上去会 WA，思考一下问题所在。

我们发现很有可能答案是一个国家连一个，这个国家连另一个，而对面两个国家中没有直接边到达。

这种情况计算两国最近距离即可。

总复杂度 $O(nm)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int f[4][1005][1005],n,m;
char c[1005][1005];
vector<pair<int,int>> vc[4];
int dist[4][4];
void bfs(int now){
	memset(f[now],-1,sizeof(f[now]));
	queue<pair<int,int>> q;
	for(auto v:vc[now]) f[now][v.first][v.second]=0,q.push(v);
	while(!q.empty()){
		auto fr=q.front();
		q.pop();
		int x=fr.first,y=fr.second;
		if(x>1) if(c[x-1][y]!='#') if(f[now][x-1][y]==-1) f[now][x-1][y]=f[now][x][y]+1,q.push(make_pair(x-1,y));
		if(x<n) if(c[x+1][y]!='#') if(f[now][x+1][y]==-1) f[now][x+1][y]=f[now][x][y]+1,q.push(make_pair(x+1,y));
		if(y>1) if(c[x][y-1]!='#') if(f[now][x][y-1]==-1) f[now][x][y-1]=f[now][x][y]+1,q.push(make_pair(x,y-1));
		if(y<m) if(c[x][y+1]!='#') if(f[now][x][y+1]==-1) f[now][x][y+1]=f[now][x][y]+1,q.push(make_pair(x,y+1));
	}
	for(int k=1;k<=3;k++) for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(c[i][j]-'0'==k&&f[now][i][j]!=-1) dist[now][k]=min(dist[now][k],f[now][i][j]);
}
signed main(){
	memset(dist,1,sizeof(dist));
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c[i][j];
			if(isdigit(c[i][j])){
				vc[c[i][j]-'0'].push_back(make_pair(i,j)); 
			}
		} 
	}
	bfs(1),bfs(2),bfs(3);
	int minv=1e9;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(f[1][i][j]!=-1&&f[2][i][j]!=-1&&f[3][i][j]!=-1){
				minv=min(minv,f[1][i][j]+f[2][i][j]+f[3][i][j]-2);
			}
		}
	}
	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			for(int k=1;k<=3;k++){
				if(i!=j&&j!=k&&k!=i){
					minv=min(minv,dist[i][j]+dist[i][k]-2);
				}
			}
		}
	}
	cout<<(minv==1e9?-1:minv); 
	return 0;
}
```

---

## 作者：_Give_up_ (赞：0)

## 思路
我们把每个国家看作一个集合。

已知最后他们联通，那么这就意味着他们到达某一点联通的代价是最小的。因此我们枚举所有点，找到最小值。

事实上，最后答案的连通块上面的点都是最小的，他们没有区别。
## Code
```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

const int N=3e7+10;
const int mod=1e9+7;
char s[1010][1010];
int n,m,dis[1010][1010][4],dx[]={-1,0,1,0},dy[]={0,1,0,-1};

void bfs(int x)
{
    queue<pll> q;
    int i,j;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            if(s[i][j]=='0'+x)
            {
                q.push({i,j});
                dis[i][j][x]=0;
            }
        }
    }
    while(q.size())
    {
        auto t=q.front();
        q.pop();
        int i;
        for(i=0;i<4;i++)
        {
            int a=t.first+dx[i];
            int b=t.second+dy[i];
            if(a>=1&&a<=n&&b>=1&&b<=m)
            {
                if(s[a][b]=='#') continue;
                int v=(s[a][b]=='.');
                if(dis[a][b][x]>dis[t.first][t.second][x]+v)
                {
                    dis[a][b][x]=dis[t.first][t.second][x]+v;
                    q.push({a,b});
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    int i,j;
    memset(dis,0x3f,sizeof dis);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            cin>>s[i][j];
    bfs(1);
    bfs(2);
    bfs(3);
    ll ans=1e18;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            if(s[i][j]=='#') continue;
            ll tmp=0;
            for(int k=1;k<=3;k++)
                tmp+=dis[i][j][k];
            if(s[i][j]=='.') tmp-=2;
            ans=min(ans,tmp);
        }
    }
    if(ans>1e9) cout<<-1<<endl;
    else cout<<ans<<endl;
    return 0;
}
```



---

