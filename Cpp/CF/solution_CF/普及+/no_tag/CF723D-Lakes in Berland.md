# Lakes in Berland

## 题目描述

**【问题描述】** ldxxx已经填完了所有的坑，现在他要给土地浇水来保证幼苗的茁壮成长。然而他刚要浇水，就迎来了瓢泼大雨，由于土地渗透性不一，所以有的土地上存在积水，连在一起的积水就形成了一个小湖泊（只有四周被陆地完全包围的才算湖泊，只要和边界有交点就不算湖泊），这时cs告诉ldxxx说如果能将湖泊的数量缩小到一个值k的话，他的庄稼长得应该最茂盛。但是由于ldxxx很笨，不知道该怎么填，所以ldxxx把浇水的任务给了cs，由于这次是义务劳动，所以cs很懒，想填最少的水使得湖泊数量为k你需要告诉他把湖泊数降到**不大于k**至少需要填多少块，并且把填好后的土地积水情况给他打印出来。 注意：只有四周被陆地完全包围的才算湖泊，只要和边界有交点就不算湖泊。

题面翻译来自accoders

## 说明/提示

$1\le n,m\le50,0\le k\le50$

## 样例 #1

### 输入

```
5 4 1
****
*..*
****
**.*
..**
```

### 输出

```
1
****
*..*
****
****
..**
```

## 样例 #2

### 输入

```
3 3 0
***
*.*
***
```

### 输出

```
1
***
***
***
```

# 题解

## 作者：云雀酱 (赞：9)

# CF的一道典型搜索水题
## 1.题面翻译&&题意分析
**【问题描述】**
ldxxx已经填完了所有的坑，现在他要给土地浇水来保证幼苗的茁壮成长。然而他刚要浇水，就迎来了瓢泼大雨，由于土地渗透性不一，所以有的土地上存在积水，连在一起的积水就形成了一个小湖泊（只有四周被陆地完全包围的才算湖泊，只要和边界有交点就不算湖泊），这时cs告诉ldxxx说如果能将湖泊的数量缩小到一个值k的话，他的庄稼长得应该最茂盛。但是由于ldxxx很笨，不知道该怎么填，所以ldxxx把浇水的任务给了cs，由于这次是义务劳动，所以cs很懒，想填最少的水使得湖泊数量为k你需要告诉他把湖泊数降到不大于k至少需要填多少块，并且把填好后的土地积水情况给他打印出来。
注意：只有四周被陆地完全包围的才算湖泊，只要和边界有交点就不算湖泊。

//题面翻译来自accoders

**【输入格式】**
第一行三个用空格分离的正整数 n，m和k，代表土地的长和宽。
接下来 n 行，每行m个字符，**'*'代表陆地，'.'代表水。数据保证至少含有k个湖。**

**【输出格式】**
输出共n+1行。
第一行一个正整数，表示把湖泊数降到k以下至少需要填多少块。
接下来n行每行m个字符，**'*'代表陆地，'.'代表水。**
 _注：输入和输出 每行的字符之间不含空格。_ 

**【数据范围】**
( **1<=n,m<=50** **0<=k<=50** )



------------
### 通过分析题面可以得知，此题应为一个搜索+贪心的题，目标就是要求出至少填满几个湖，才能使得湖的数量不多于k。
## 2.正解步骤解析
### 因为我们需要填掉一些湖才能使得湖的总数不多于k，那么就有一种贪心思路，我们从最小的湖开始填，可以保证填的坑是最少的。

#### Subtask1：我们需要一个dfs函数来统计出湖的信息（湖的大小，湖的位置与湖的数量）。
#### Subtask2：我们需要另一个dfs函数来暴力在图上填掉湖。
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=100;
int n,m,k,num=1,lake_total=0,ans=0,kk=1;
char graph[MAXN][MAXN];
bool mark[MAXN][MAXN],is=false;
int dx[6]={0,0,1,-1};
int dy[6]={1,-1,0,0};
//一个结构体，用来存储湖的大小及位置
struct st{
	int x,y,size;
}lake[MAXN*MAXN];
//dfs函数，用来统计湖的数量，大小及位置
void dfs(int x,int y){
	//如果这个湖有一部分在边界，那么直接标记它不是湖
	if(x==1||x==n||y==1||y==m) is=true;
	lake[num].size++;
	mark[x][y]=true;
	//四向数组搜索
	for(int i=0;i<=3;i++){
		int xx=x+dx[i],yy=y+dy[i];
		if(x<1||x>n||y<1||y>m) continue;
		if(mark[xx][yy]==false&&graph[xx][yy]=='.'){
			dfs(xx,yy);
		}
	}
}
//用来填湖输出的dfs2函数
void dfs2(int x,int y){
	graph[x][y]='*';
	for(int i=0;i<=3;i++){
		int xx=x+dx[i],yy=y+dy[i];
		if(x<1||x>n||y<1||y>m) continue;
		if(graph[xx][yy]=='.'){
			dfs2(xx,yy);
		}
	}
}
//结构体排序，重载运算符
bool operator < (const st &x,const st &y){
	return x.size<y.size;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%s",graph[i]+1);
	//暴力寻找湖
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			//如果当前点是湖，并且不是其他湖的一部分，开始搜索。
			if(graph[i][j]=='.'&&mark[i][j]==false){
				//标记边界“湖”的变量初始化
				is=false;
				dfs(i,j);
				//如果这个湖是边界‘湖’，我们重置湖的大小，跳过
				if(is==true){
					lake[num].size=0;
					continue;
				}
				//如果它是湖，我们就把它的位置与大小标记上
				lake[num].x=i;
				lake[num].y=j;
				lake_total++;
				num++;
			}
		}
	}
	//对湖的大小排序，开始贪心
	sort(lake+1,lake+1+lake_total);
	//不停的填湖，直到湖的个数不多于k个
	while(lake_total>k){
		lake_total--;
		ans+=lake[kk].size;
		dfs2(lake[kk].x,lake[kk].y);
		kk++;
	}
	//输出填掉的湖的大小总数
	printf("%d\n",ans);
	//输出填完的图
	for(int i=1;i<=n;i++){
		printf("%s\n",graph[i]+1);
	}
	return 0;
}
```
## 总的来说，还是一道较为基础的搜索题，很容易可以想到。
## 新人的第一篇题解，祝大家CSP2019考试成功！


---

## 作者：Tjaweiof (赞：1)

# CF723D 题解
由于填任意一个湖对后续操作没有影响，所以优先填最小的湖更优。所以我们 dfs 找出所有的湖，然后存进优先队列，最后直接填就行了。

暴力。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int nextstep[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
int n, m, k, tmp, ans, dx, dy;
char a[51][51];
bool vis[51][51], t[51][51];
vector <pair <int, int> > res[51][51];
priority_queue <pair <int, pair <int, int> > > q;
void dfs(int x, int y){
	vis[x][y] = true;
	res[dx][dy].push_back({x, y});
	for (int k = 0; k < 4; k++){
		int nx = x + nextstep[k][0], ny = y + nextstep[k][1];
		if (nx < 1 || nx > n || ny < 1 || ny > m){
			t[dx][dy] = false;
			continue;;
		}
		if (vis[nx][ny]){
			continue;
		}
		if (a[nx][ny] == '.'){
			dfs(nx, ny);
		}
	}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			cin >> a[i][j];
		}
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			if (a[i][j] == '.' && !vis[i][j]){
				dx = i;
				dy = j;
				t[i][j] = true;
				dfs(i, j);
				if (t[i][j]){
					q.push({-res[i][j].size(), {i, j}});
					tmp++;
				}
			}
		}
	}
	tmp -= k;
	while (tmp--){
		for (auto u : res[q.top().second.first][q.top().second.second]){
			a[u.first][u.second] = '*';
			ans++;
		}
		q.pop();
	}
	cout << ans << endl;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			cout << a[i][j];
		}
		cout << endl;
	}
	return 0;
}

```

---

## 作者：wuyixiang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF723D)

大意：至少需要将多少水地变成陆地，才能让水地的联通快数目 $\le k$。

分析：简单的模拟题。可以通过联通快标记与记录每一个满足条件的水地的面积，再将这些从小到大排序，取最前面的因为才能满足“最少”这一条件。最后遍历每一块地，如果这块地的标记编号在前面则进行转换，即水地变成陆地。

### AC Code:

```cpp
#include <iostream>
#include <algorithm> 
using namespace std;
int n,m,k,b[51][51],cnt,r,p,val,ans;
char a[51][51];
struct node
{
    int u,v;//结构体，u为编号，v为面积
}c[2501];
bool cmp(node f,node g)
{
    return f.v < g.v;
}
void dfs(int x,int y,int num)
{
    if(x > n || x < 1 || y > m || y < 1)//如果与边界相邻，则将它标记，代表不是水洼
    {
        r = 1;
        return ;
    }
    if(a[x][y] == '*' || b[x][y])return ;
    b[x][y] = num,val ++;
    dfs(x + 1,y,num);//四方向遍历
    dfs(x - 1,y,num);
    dfs(x,y + 1,num);
    dfs(x,y - 1,num);
}
int main()
{
    cin >> n >> m >> k;
    for(int i = 1;i <= n;i ++)
    {
        for(int j = 1;j <= m;j ++)cin >> a[i][j];
    }
    for(int i = 1;i <= n;i ++)
        for(int j = 1;j <= m;j ++)
        {
            if(a[i][j] == '.' && !b[i][j])
            {
                r = 0,val = 0;
                dfs(i,j,++cnt);
                if(r == 0)c[++p].u = cnt,c[p].v = val;//标记
            }
        }
    sort(c + 1,c + p + 1,cmp);//排序
    for(int i = 1;i <= p - k;i ++)ans += c[i].v;
    cout << ans << endl;
    for(int i = 1;i <= n;i ++)
    {
        for(int j = 1;j <= m;j ++)
        {
            int r = 0;
            for(int l = 1;l <= p - k;l ++)//如果前面p - k项有，则将它转换为陆地
                if(b[i][j] == c[l].u)r = 1;
            if(r == 1)cout << '*';
            else cout << a[i][j];
        }
        cout << endl;
    }
}

---

## 作者：Butterfly___qwq (赞：1)

题意就是给一个 $n \times m$ 的地图，其中边缘地区邻接着海，不能算一个湖，里面的每一个连通块都算一个湖，求最少填掉多少块小格子使得湖的数量变成 $k$ (起始湖数量大于等于 $k$)

先 DFS 求不邻接大海的连通块（这里如果用并查集求连通块就判断邻接大海就没有 DFS 这么简便），然后把每一块中 DFS 的起始点坐标和湖的面积组成结构体记录并按照湖的面积排序，再贪心地再写一个 DFS 填充面积小的湖。
```cpp
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define CLR(arr,val) memset(arr,val,sizeof(arr))
#define LC(x) (x<<1)
#define RC(x) ((x<<1)+1)
#define MID(x,y) ((x+y)>>1)
typedef pair<int,int> pii;
typedef long long LL;
const double PI=acos(-1.0);
const int N=55;
struct info
{
    int need;
    int x,y;
    bool operator<(const info &t)const
    {
        return need>t.need;
    }
};
priority_queue<info>Q;

char pos[N][N];
int vis[N][N];
int n,m;
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int is_lake,once;

inline bool check(int x,int y)
{
    return x>=0&&x<n&&y>=0&&y<m&&pos[x][y]=='.'&&!vis[x][y];
}
void dfs(int x,int y)
{
    vis[x][y]=1;
    ++once;
    if(x==0||y==0||x==n-1||y==m-1)
        is_lake=0;
    for (int i=0; i<4; ++i)
    {
        int xx=x+dir[i][0];
        int yy=y+dir[i][1];
        if(check(xx,yy))
            dfs(xx,yy);
    }
}
void kuosan(int x,int y)
{
    pos[x][y]='*';
    for (int i=0; i<4; ++i)
    {
        int xx=x+dir[i][0];
        int yy=y+dir[i][1];
        if(xx>=0&&xx<n&&yy>=0&&yy<m&&pos[xx][yy]=='.')
            kuosan(xx,yy);
    }
}
int main(void)
{
    int i,j,k;
    while (~scanf("%d%d%d",&n,&m,&k))
    {
        CLR(vis,0);
        for (i=0; i<n; ++i)
            scanf("%s",pos[i]);
        int sc=0;
        for (i=0; i<n; ++i)
        {
            for (j=0; j<m; ++j)
            {
                if(pos[i][j]=='.'&&!vis[i][j])
                {
                    is_lake=1;
                    once=0;
                    dfs(i,j);
                    if(is_lake)
                        Q.push((info){once,i,j}),++sc;
                }
            }
        }
        int r=0;
        info now;
        while (sc>k)
        {
            now=Q.top();
            Q.pop();
            kuosan(now.x,now.y);
            r+=now.need;
            --sc;
        }
        printf("%d\n",r);
        for (i=0; i<n; ++i)
            printf("%s\n",pos[i]);
    }
    return 0;
}
```

---

## 作者：优少 (赞：1)

**首先将边界的水用bfs处理掉**

**再将中间的每一个湖泊处理出来，存入一个结构体内，结构体里记录湖泊大小和开始点**

**将湖泊排序从小往大填满，并利用开始点进行bfs改变地图**

# 细节见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int vis[100][100],mapp[100][100];
int dx[5]={0,-1,0,1,0};
int dy[5]={0,0,1,0,-1},cnt;
struct SYM{
    int cc,sx,sy;
}lake[10000];
void bfs(int x,int y,int opt){
     queue<int> qx,qy;int siz=0;
     if(opt==1){                      //处理边界
        vis[x][y]=1;qx.push(x);qy.push(y);
        while(!qx.empty()){
              int xx=qx.front(),yy=qy.front();qx.pop();qy.pop();
              for(int i=1;i<=4;i++){
                  int nx=xx+dx[i],ny=yy+dy[i];
                  if(nx==0||ny==0||nx==n+1||ny==m+1) continue;
                  if(vis[nx][ny]) continue;
                  vis[nx][ny]=1;
                  qx.push(nx);qy.push(ny);
              }
        }
     }
     if(opt==0){                     //处理湖泊
        vis[x][y]=1;qx.push(x);qy.push(y);
        while(!qx.empty()){
              int xx=qx.front(),yy=qy.front();qx.pop();qy.pop();
              siz++;
              for(int i=1;i<=4;i++){
                  int nx=xx+dx[i],ny=yy+dy[i];
                  if(nx==0||ny==0||nx==n+1||ny==m+1) continue;
                  if(vis[nx][ny]) continue;
                  vis[nx][ny]=1;
                  qx.push(nx);qy.push(ny);
              }
        }
        lake[++cnt].cc=siz;lake[cnt].sx=x;lake[cnt].sy=y; //存入湖泊大小和开始点
     }
     if(opt==2){                //改变地图
        mapp[x][y]=1;qx.push(x);qy.push(y);
        while(!qx.empty()){
              int xx=qx.front(),yy=qy.front();qx.pop();qy.pop();
              siz++;
              for(int i=1;i<=4;i++){
                  int nx=xx+dx[i],ny=yy+dy[i];
                  if(nx==0||ny==0||nx==n+1||ny==m+1) continue;
                  if(mapp[nx][ny]) continue;
                  mapp[nx][ny]=1;
                  qx.push(nx);qy.push(ny);
              }
        }
     }
}
bool cmp(const SYM &a,const SYM &b){
     return a.cc>b.cc;
}
int main(){
	char c[1000];
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++){
        scanf("%s",c);
        for(int j=0;j<m;j++)
            mapp[i][j+1]=vis[i][j+1]=(c[j]=='*');
    }
    for(int i=1;i<=n;i++){                       //处理边界水
        if(mapp[i][1]==0&&vis[i][1]==0) bfs(i,1,1);
        if(mapp[i][m]==0&&vis[i][m]==0) bfs(i,m,1);
    }
    for(int i=1;i<=m;i++){
        if(mapp[1][i]==0&&vis[1][i]==0) bfs(1,i,1);
        if(mapp[n][i]==0&&vis[n][i]==0) bfs(n,i,1);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(!vis[i][j]) bfs(i,j,0);
    sort(lake+1,lake+cnt+1,cmp);                  //湖泊按大小排序
    int ans=0;
    while(cnt>k){                           //填湖泊
          ans+=lake[cnt].cc;
          bfs(lake[cnt].sx,lake[cnt].sy,2);       //改地图
          cnt--;
    }     
    printf("%d\n",ans);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mapp[i][j]==1) printf("*");
            else printf(".");
        }
        printf("\n");
    }
    return 0;
}
```




---

## 作者：huhaoming2011 (赞：0)

# Lakes in Berland 题解

## 题目大意

给你一个由字符构成的大小为 $N \times M$ 的图，保证只由 `*` 和 `.` 组成。

然后让你保留 $k$ 个由 `.` 组成的连通块（删掉其他的由 `.` 组成的连通块）。

令删除的连通块的大小总和最小，并输出其和与删除后的图。

## 分析

以为很高级，但是细细品味，看一眼数据：$n$ 和 $m$ 均小于等于 $50$。

那么这道题开始有趣起来了（我们直接暴力搜索）。

## 正解

直接搜索（我用宽度优先搜索）出每个由 `.` 构成的连通块以及其大小，然后根据其大小为关键字排序（升序），最后依次把前 $cnt-k$ 个连通块覆盖成 `*`，加上其连通块大小就行了。

是不是很简单！

## 代码如下

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50 + 10;
struct node {
    int x, y, siz;
} a[MAXN * MAXN];
int n, m, k, cnt, bz[MAXN][MAXN];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
char g[MAXN][MAXN];
bool cmp(node x, node y)
{
    return x.siz < y.siz;
}
void bfs(int x, int y)
{
    int d[MAXN * MAXN][2];
    int hd = 0, tail = 1;
    d[1][0] = x;
    d[1][1] = y;
    a[++cnt].x = x;
    a[cnt].y = y;
    a[cnt].siz = 1;
    while(hd < tail)
    {
        hd++;
        for(int i = 0; i < 4; i++)
        {
            int xx = dx[i] + d[hd][0];
            int yy = dy[i] + d[hd][1];
            if(xx >= 1 and xx <= n and yy >= 1 and yy <= m and g[xx][yy] == '.' and !bz[xx][yy])
            {
                bz[xx][yy] = 1;
                d[++tail][0] = xx;
                d[tail][1] = yy;
                a[cnt].siz++;
            }
        }
    }
}
void bfs2(int x, int y)
{
    int d[MAXN * MAXN][2];
    int hd = 0, tail = 1;
    d[1][0] = x;
    d[1][1] = y;
    while(hd < tail)
    {
        hd++;
        for(int i = 0; i < 4; i++)
        {
            int xx = dx[i] + d[hd][0];
            int yy = dy[i] + d[hd][1];
            if(xx >= 1 and xx <= n and yy >= 1 and yy <= m and g[xx][yy] == '.')
            {
                // bz[xx][yy] = 1;
                d[++tail][0] = xx;
                d[tail][1] = yy;
                g[xx][yy] = '*';
            }
        }
    }
}
int main()
{
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1; i <= n; i++)
    {
        scanf("%s", g[i] + 1);
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(g[i][j] == '.' and !bz[i][j])
            {
                bz[i][j] = 1;
                bfs(i, j);
            }
        }
    }
    sort(a + 1, a + cnt + 1, cmp);
    int p = cnt - k, ans = 0;
    for(int i = 1; i <= p; i++)
    {
        g[a[i].x][a[i].y] = '*';
        bfs2(a[i].x, a[i].y);
        ans += a[i].siz;
    }
    printf("%d\n", ans);
    for(int i = 1; i <= n; i++)
    {
        printf("%s", g[i] + 1);
        puts("");
    }
    return 0;
}
```

谢谢观看！

---

## 作者：yangzichen1203 (赞：0)

# Problem

[题目链接](!https://www.luogu.com.cn/problem/CF723D)

给定一个 $n \times m$ 的矩阵，其中'$*$'代表陆地，'.'代表水。求把湖泊（只有四周被陆地完全包围的才算湖泊，只要和边界有交点就不算湖泊）降到 $k$ 个以下至少需要填多少块水（将‘.’转化为'$*$'）。

# Solution

先记录总共有几个池塘，然后从小到大排序池塘大小（贪心），最后一个一个把池塘数量填到 $k$ 个，同时记录出一共填掉多少块水，输出。

# Code
    
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 55
char a[MAXN][MAXN];
bool vis[MAXN][MAXN];
int n,m,k;
const int fx[4]={-1,0,0,1};
const int fy[4]={0,-1,1,0};
struct Node{
	int x,y,size;
}lake[MAXN*MAXN];
bool cmp(Node a,Node b){
	return a.size>b.size;
}
int cnt=1;
bool flag;
void dfs1(int x,int y){
	if(x==1||x==n||y==1||y==m) flag=1;
	lake[cnt].size++;
	vis[x][y]=1;
	for(int i=0;i<4;i++){
		int xx=x+fx[i],yy=y+fy[i];
		if(x<1||x>n||y<1||y>m) continue;
		if(!vis[xx][yy]&&a[xx][yy]=='.'){
			dfs1(xx,yy);
		}
	}
}
void dfs2(int x,int y){
	a[x][y]='*';
	for(int i=0;i<4;i++){
		int xx=x+fx[i],yy=y+fy[i];
		if(x<1||x>n||y<1||y>m) continue;
		if(a[xx][yy]=='.'){
			dfs2(xx,yy);
		}
	}
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='.'&&!vis[i][j]){
				flag=0;
				dfs1(i,j);
				if(flag){
					lake[cnt].size=0;
					continue;
				}
				lake[cnt].x=i;
				lake[cnt].y=j;
				cnt++;
			}
		}
	}
	sort(lake+1,lake+cnt,cmp);
	int ans=0;
	while(cnt>k){
		ans+=lake[cnt].size;
		dfs2(lake[cnt].x,lake[cnt].y);
		cnt--;
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cout<<a[i][j];
		}
		cout<<endl;
	}
	return 0;
}
```

[AC记录](!https://www.luogu.com.cn/record/125656205)

---

## 作者：Tx_Lcy (赞：0)

好久没做到这么水的绿题了...
## 思路
从图中是水的点出发灌水，同时记录这个块的大小及编号，**注意要判掉不合法的情况**。再把这些块的大小扔进一个结构体里，然后排序（按连通块大小），取前 $q-k$ 个连通块染成陆地，并使累加器加上这些连通块的大小。

时间复杂度 $O(n^2)$，可以通过此题。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=5e1+5;
int n,m,tag,a[N][N],vis[N*N],ans,anc,tagen;
string s[N];
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
struct node{int x,y;}qa[N*N];
inline bool cmp(node a,node b){return a.x<b.x;}
inline void dfs(int x,int y,int tagg){
	if (tag) return;
	a[x][y]=tagg;++tagen;
	for (int i=0;i<4;++i){
		int tx=x+dx[i];
		int ty=y+dy[i];
		if (a[tx][ty]==1 || a[tx][ty]==tagg) continue;
		if (tx<1 || tx>n || ty<1 || ty>m){tag=1;return;}
	    dfs(tx,ty,tagg);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int k;cin>>n>>m>>k;
	for (int i=1;i<=n;++i){
		cin>>s[i];
		s[i]=" "+s[i];
		for (int j=1;j<=m;++j)
		    a[i][j]=(s[i][j]=='*');
	}
	int cnt=1,q=0;
	for (int i=1;i<=n;++i)
	    for (int j=1;j<=m;++j)
	        if (a[i][j]==0){
	        	tag=0,++cnt,
	        	tagen=0;
	        	dfs(i,j,cnt);
	        	if (!tag){
	        		qa[++q].x=tagen,qa[q].y=cnt;
				}
			}
	sort(qa+1,qa+q+1,cmp);
	for (int i=1;i<=(q-k);++i) vis[qa[i].y]=1,ans+=qa[i].x;
	cout<<ans<<'\n';
	for (int i=1;i<=n;++i){
	    for (int j=1;j<=m;++j)
	        if (vis[a[i][j]]) cout<<'*';
	        else cout<<s[i][j];
	    cout<<'\n';
	}
	return 0;
}
```


---

