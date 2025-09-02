# Connect

## 题目描述

Alice lives on a flat planet that can be modeled as a square grid of size $ n \times n $ , with rows and columns enumerated from $ 1 $ to $ n $ . We represent the cell at the intersection of row $ r $ and column $ c $ with ordered pair $ (r, c) $ . Each cell in the grid is either land or water.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1130C/b5659671b82592e81ced0ea1b88b58d8fa94b02e.png)An example planet with $ n = 5 $ . It also appears in the first sample test.Alice resides in land cell $ (r_1, c_1) $ . She wishes to travel to land cell $ (r_2, c_2) $ . At any moment, she may move to one of the cells adjacent to where she is—in one of the four directions (i.e., up, down, left, or right).

Unfortunately, Alice cannot swim, and there is no viable transportation means other than by foot (i.e., she can walk only on land). As a result, Alice's trip may be impossible.

To help Alice, you plan to create at most one tunnel between some two land cells. The tunnel will allow Alice to freely travel between the two endpoints. Indeed, creating a tunnel is a lot of effort: the cost of creating a tunnel between cells $ (r_s, c_s) $ and $ (r_t, c_t) $ is $ (r_s-r_t)^2 + (c_s-c_t)^2 $ .

For now, your task is to find the minimum possible cost of creating at most one tunnel so that Alice could travel from $ (r_1, c_1) $ to $ (r_2, c_2) $ . If no tunnel needs to be created, the cost is $ 0 $ .

## 说明/提示

In the first sample, a tunnel between cells $ (1, 4) $ and $ (4, 5) $ should be created. The cost of doing so is $ (1-4)^2 + (4-5)^2 = 10 $ , which is optimal. This way, Alice could walk from $ (1, 1) $ to $ (1, 4) $ , use the tunnel from $ (1, 4) $ to $ (4, 5) $ , and lastly walk from $ (4, 5) $ to $ (5, 5) $ .

In the second sample, clearly a tunnel between cells $ (1, 3) $ and $ (3, 1) $ needs to be created. The cost of doing so is $ (1-3)^2 + (3-1)^2 = 8 $ .

## 样例 #1

### 输入

```
5
1 1
5 5
00001
11111
00111
00110
00110
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3
1 3
3 1
010
101
010
```

### 输出

```
8
```

# 题解

## 作者：封禁用户 (赞：2)

~~这个蒟蒻又来水题解了 awa~~
### 写在前面的废话：

一看数据范围 ```1≤n≤50```

这就很棒！可以暴力！！！

------------

### 详细思路：
因为题目说**最多只能建一对传送门**，所以 bfs 出**所有起点能到达的点**，再 bfs 出**所有终点能到达的点**，最后暴力匹配取 min 值即可。

------------

### 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cctype>
#include<queue>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
template<typename T>
inline void in(T &x)//快读，不需要理解
{
	x=0;
	T f=1;
	char c=getchar();
	while(!isdigit(c)){if(!isspace(c))f=-1; c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48); c=getchar();}
	x*=f;
	return;
}
const int bx[]={-1,1,0,0};//控制移动的数组
const int by[]={0,0,-1,1};
int start_tot,end_tot;
struct go{
	int x,y;
}st[3000],en[3000];
//st数组用来记录所有起点能到达的点
//en数组用来记录所有终点能到达的点
queue<go> q;//STL大法好
int n,m[60][60];
bool vis[60][60];
inline int pay(int sx,int sy,int ex,int ey){return (sx-ex)*(sx-ex)+(sy-ey)*(sy-ey);}//建立传送门的费用
void bfs(bool f,int sx,int sy)//bfs
{
	vis[sx][sy]=1;//起点打上标记
	q.push((go){sx,sy});//起点入队
	if(f==0)//记录点
	{
		start_tot++;
		st[start_tot].x=sx;
		st[start_tot].y=sy;
	}
	else
	{
		end_tot++;
		en[end_tot].x=sx;
		en[end_tot].y=sy;
	}
	while(!q.empty())
	{
		int x=q.front().x;
		int y=q.front().y;
		q.pop();
		for(int i=0;i<4;i++)//四个方向
		{
			int xx=x+bx[i];//走一步
			int yy=y+by[i];
			if(xx>0&&xx<=n&&yy>0&&yy<=n&&!vis[xx][yy]&&m[xx][yy]==0)//没出地图 并且 没到过 并且 可以走
			{
				vis[xx][yy]=1;//打标记
				q.push((go){xx,yy});//入队
				if(f==0)//记录点
				{
					start_tot++;
					st[start_tot].x=xx;
					st[start_tot].y=yy;
				}
				else
				{
					end_tot++;
					en[end_tot].x=xx;
					en[end_tot].y=yy;
				}
			}
		}
	}
	return;
}
int sx,sy,ex,ey,ans=0x7fffffff;
int main()
{
	in(n);
	in(sx); in(sy);
	in(ex); in(ey);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%1d",&m[i][j]);//scanf特殊用法，不多做解释
	bfs(0,sx,sy);//bfs出所有起点能到达的点
	bfs(1,ex,ey);//bfs出所有终点能到达的点
	for(int i=1;i<=start_tot;i++)//暴力匹配
		for(int j=1;j<=end_tot;j++)
			ans=min(ans,pay(st[i].x,st[i].y,en[j].x,en[j].y));//取min值
	printf("%d",ans);//输出
	return 0;//完结撒花
}
```

---

## 作者：A_L_1_S_ (赞：2)

dfs找出初始点连接的点，找出目标点连接的点


------------
~~暴力~~找最小匹配即可qwq
```cpp
#include <iostream> 
#include <cstdio> 
#include <cstdlib> 
#include <cmath> 
#include <cctype> 
#include <iomanip> 
#include <algorithm> 
#include <climits> 
#include <cstring> 
#include <string> 
#include <set> 
#include <map> 
#include <queue> 
#include <stack> 
#include <vector> 
#include <list>
using namespace std;
int n ;
char mp[55][55];
int sx,sy,ex,ey;
int cnt1=0,cnt2=0;
int s[2555][2],e[2555][2];
bool pd[55][55];

inline void find1(int x,int y){
	if(x<=0||y<=0||x>n||y>n||mp[x][y]=='1'||pd[x][y]==1)
		return ;
	cnt1++;
	s[cnt1][0]=x;
	s[cnt1][1]=y;
	pd[x][y]=1;
	find1(x+1,y);
	find1(x-1,y);
	find1(x,y+1);
	find1(x,y-1);
	return ;
}

inline void find2(int x,int y){
	if(x<=0||y<=0||x>n||y>n||mp[x][y]=='1'||pd[x][y]==1)
		return ;
	cnt2++;
	e[cnt2][0]=x;
	e[cnt2][1]=y;
	pd[x][y]=1;
	find2(x+1,y);
	find2(x-1,y);
	find2(x,y+1);
	find2(x,y-1);
	return ;
}

int main(){
	scanf("%d",&n);
	scanf("%d%d",&sx,&sy);
	scanf("%d%d",&ex,&ey);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char x ;
			cin >> x ;
			mp[i][j]=x ;
		}
	}
	memset(pd,0,sizeof(pd));
	find1(sx,sy);
	memset(pd,0,sizeof(pd));
	find2(ex,ey);
	int minn=9999999;
	for(int i=1;i<=cnt1;i++){
		for(int j=1;j<=cnt2;j++){
			//cout << s[i][0] << ' ' << s[i][1] << endl ;
			//cout << e[j][0] << ' ' << e[j][1] << endl ;
			int xx=pow(abs(s[i][0]-e[j][0]),2)+pow(abs(s[i][1]-e[j][1]),2);
			if(xx<minn)
				minn=xx;
		}
	}
	cout << minn << endl ;
	return 0 ;
}

```

---

## 作者：Hisaishi_Kanade (赞：1)

挺有意思的一道题。

### 一、题意

给出一个地图，为零表示陆地（能走），为一表示湖水（不能走）。

+ 陆地上移动
+ 建立价值为 $(x_1-x_2)^2+(y_1-y_2)^2$ 的传送门

### 二、思路

我们考虑两种获得最小花费的做法：

1. 直接从陆地上走过去
2. 到达某个点，然后传送到另一个点，最后到达终点

第一种方法很简单，是“染色问题”的模板。

然而第二种就要动脑筋了。

考虑到数据范围不大，所以我们这样做：

+ 从起点开始深搜，如果搜到终点直接走人。同时记录到达的点。
+ 从终点开始深搜，并且搜到一个点就和前面的点求 $dis$，并求最小。

总复杂度最坏也才 $O\left(N^2\right)$，绰绰有余。

### 三、代码

```cpp
#include <stdio.h>//scanf,printf
#include <iostream>//std::cin
#include <stdlib.h>//exit(0)
using std::cin;//本代码中等价于using namespace std;
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};//方向增量数组
bool v[101][101],v2[101][101];//访问标记数组
int l[10005],r[10005];//记录点
int cnt,n,fx,fy,sx,sy,ans(1<<30);//最大值
char ch;
void dfs(int x,int y){
	v[x][y]=true;//标记一下
	l[++cnt]=x;r[cnt]=y;//记录这个点
	if(x==fx&&y==fy){//到终点直接走人
		puts("0");
		exit(0);//其实可以用bool做，但是麻烦地多
	}
	for(int i=0;i<4;++i){
		x+=dx[i];y+=dy[i];//方向增量，个人习惯+=再-=
		if(1<=x&&x<=n&&1<=y&&y<=n&&!v[x][y])
			dfs(x,y);
		x-=dx[i];y-=dy[i];//变回来
	}
	return;
}
void dfs2(int x,int y){
	v2[x][y]=true;
	int dis;
	for(int i=1;i<=cnt;++i){
		dis=(x-l[i])*(x-l[i])+(y-r[i])*(y-r[i]);//算和之前cnt个搜到的点的最小距离
		if(dis<ans)
			ans=dis;//并更新
	}
	for(int i=0;i<4;++i){
		x+=dx[i];y+=dy[i];
		if(1<=x&&x<=n&&1<=y&&y<=n&&!v2[x][y])
			dfs2(x,y);
		x-=dx[i];y-=dy[i];
	}
	return;
}
int main(){
//	freopen("cost.in","r",stdin);
//	freopen("cost.out","w",stdout);
	int i,j;
	scanf("%d %d %d %d %d",&n,&sx,&sy,&fx,&fy);
	for(i=1;i<=n;++i)
		for(j=1;j<=n;++j){
			cin>>ch;//烦\r、\n之类的，不用cin要scanf("%s")，数据不大就偷个懒
			v2[i][j]=v[i][j]=ch=='1';//不能走就标记走过了
		}
	dfs(sx,sy);//从起点搜
	dfs2(fx,fy);//从终点搜
	printf("%d",ans);
	return 0;
}
```

---

## 作者：CalcMaster (赞：1)

看到这50的数据范围，一阵舒爽从心里传来。

可以暴力！！！

我的方法是：
预处理所有起始点能到达的点和所有终点可以到达的点。

再暴力枚举min值







```cpp
#include <bits/stdc++.h>
using namespace std;

struct node
{
	int x,y;	
};

vector <node> fr,to;

int ans;
int n;
int r1,r2,c1,c2;
char tmp[55][55],huan[2];
int mp[55][55];
int a[55][55];
bool vis[55][55];


void chufr(int i,int j)
{
	if(i<=0||j<=0||mp[i][j]==1||i>n||j>n||vis[i][j])return;
	if(mp[i][j]==0)
	{
		vis[i][j]=1;
		node ttt;
		ttt.x=i,ttt.y=j;
		fr.push_back(ttt);
		
		chufr(i+1,j);
	
		chufr(i,j+1);

		chufr(i-1,j);

		chufr(i,j-1);
	}
	else return;
}
void chuto(int i,int j)
{
	if(i<=0||j<=0||mp[i][j]==1||i>n||j>n||vis[i][j])return;
	if(mp[i][j]==0)
	{
		vis[i][j]=1;
		node ttt;
		ttt.x=i;ttt.y=j;
		to.push_back(ttt);
	
		chuto(i+1,j);

		chuto(i-1,j);

		chuto(i,j+1);

		chuto(i,j-1);
	}
	else return;
}

int main()
{
	scanf("%d",&n);
	scanf("%d%d",&r1,&c1);
	scanf("%d%d",&r2,&c2);
	gets(huan);
	memset(mp,-1,sizeof(mp));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%c",&tmp[i][j]);
			if(tmp[i][j]=='0')mp[i][j]=0;
			else mp[i][j]=1;
		}
		gets(huan);//璇绘崲琛?
	}
	memset(vis,0,sizeof(vis));
	chufr(r1,c1);
	memset(vis,0,sizeof(vis));
	chuto(r2,c2);
	int sizfr=fr.size();
	int sizto=to.size();
	ans=99999999;
	for(int i=0;i<sizfr;i++)
	{
		for(int j=0;j<sizto;j++)
		{
			int d1=(fr[i].x-to[j].x);
			int d2=(fr[i].y-to[j].y);
			if(d1*d1+d2*d2<=ans)
				ans=d1*d1+d2*d2;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：xyf007 (赞：1)

### 深搜所有可达的点，枚举每一种情况的价格即可
---
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
int n,a[51][51],r1,c1,r2,c2,len1,len2,dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
std::pair<int,int>a1[2501],a2[2501];
bool vis[51][51];
void dfs1(int x,int y)
{
	vis[x][y]=1;
	a1[++len1]=std::make_pair(x,y);
	for(int i=0;i<4;i++)
	{
		int tox=x+dx[i],toy=y+dy[i];
		if(!vis[tox][toy]&&!a[tox][toy]&&tox>0&&tox<=n&&toy>0&&toy<=n)
		{
			dfs1(tox,toy);
		}
	}
}
void dfs2(int x,int y)
{
	vis[x][y]=1;
	a2[++len2]=std::make_pair(x,y);
	for(int i=0;i<4;i++)
	{
		int tox=x+dx[i],toy=y+dy[i];
		if(!vis[tox][toy]&&!a[tox][toy]&&tox>0&&tox<=n&&toy>0&&toy<=n)
		{
			dfs2(tox,toy);
		}
	}
}
long long calc(std::pair<int,int>x,std::pair<int,int>y)
{
	return (x.first-y.first)*(x.first-y.first)+(x.second-y.second)*(x.second-y.second);
}
void checkmin(long long &x,long long y)
{
	if(x>y)
	{
		x=y;
	}
}
int main()
{
	scanf("%d%d%d%d%d\n",&n,&r1,&c1,&r2,&c2);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			char c=getchar();
			a[i][j]=c-'0';
		}
		getchar();
	}
	dfs1(r1,c1);
	dfs2(r2,c2);
	long long ans=1e18;
	for(int i=1;i<=len1;i++)
	{
		for(int j=1;j<=len2;j++)
		{
			checkmin(ans,calc(a1[i],a2[j]));
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Jerrywang09 (赞：0)

# 先说几句

难度适合。简单暴力。

# 解题思路

对于起始位置和终止位置，找出其分别所属的连通分量。

对这两个连通分量里的位置排序。如果相等，就说明起点和终点属于同一个连通分量。不需要挖隧道。直接输出 $0$。

否则，就对这两个连通分量里的点进行一个 $O(n^2)$ 的双重循环暴力查找。

# 奉上代码

千万不要抄，小心棕名！

```cpp
// 1130C Connect
#include <bits/stdc++.h>
#define var long long
#define SIZE 55
using namespace std;

char a[SIZE][SIZE];
int n;
bool vis1[SIZE][SIZE]={0};
bool vis2[SIZE][SIZE]={0};
vector<pair<int, int>> b;
vector<pair<int, int>> c;

const int dx[]={-1, 1,  0, 0};
const int dy[]={ 0, 0, -1, 1};

void dfs1(int i, int j)
{
	if(i<0 || i>=n || j<0 || j>=n)
		return;
	if(vis1[i][j])
		return;
	if(a[i][j]=='1')
		return;
	vis1[i][j]=1;
	b.push_back({i, j});
	for(int k=0; k<4; k++)
	{
		int ni=i+dx[k];
		int nj=j+dy[k];
		dfs1(ni, nj);
	}
}

void dfs2(int i, int j)
{
	if(i<0 || i>=n || j<0 || j>=n)
		return;
	if(vis2[i][j])
		return;
	if(a[i][j]=='1')
		return;
	vis2[i][j]=1;
	c.push_back({i, j});
	for(int k=0; k<4; k++)
	{
		int ni=i+dx[k];
		int nj=j+dy[k];
		dfs2(ni, nj);
	}
}

inline int hamintonDistance(pair<int, int> a, pair<int, int> b)
{
	return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
}

int main()
{
	cin>>n;
	int si, sj; cin>>si>>sj; si--; sj--;
	int ei, ej; cin>>ei>>ej; ei--; ej--;
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			cin>>a[i][j];
			
	dfs1(si, sj);
	dfs2(ei, ej);
	
	sort(b.begin(), b.end());
	sort(c.begin(), c.end());
	
	/*
	for(auto x:b)
		cout<<x.first<<" "<<x.second<<endl;
	cout<<endl;
	for(auto x:c)
		cout<<x.first<<" "<<x.second<<endl;
	cout<<endl;
	*/
	
	if(b==c)
	{
		cout<<0;
		return 0;
	}
	
	int Min=INT_MAX;	
	for(auto x:b)
		for(auto y:c)
		{
			int dist=hamintonDistance(x, y);
			if(dist<Min) Min=dist;
		}
	cout<<Min;

    return 0;
}
```

---

