# Maze

## 题目描述

Pavel loves grid mazes. A grid maze is an $ n×m $ rectangle maze where each cell is either empty, or is a wall. You can go from one cell to another only if both cells are empty and have a common side.

Pavel drew a grid maze with all empty cells forming a connected area. That is, you can go from any empty cell to any other one. Pavel doesn't like it when his maze has too little walls. He wants to turn exactly $ k $ empty cells into walls so that all the remaining cells still formed a connected area. Help him.

## 样例 #1

### 输入

```
3 4 2
#..#
..#.
#...
```

### 输出

```
#.X#
X.#.
#...
```

## 样例 #2

### 输入

```
5 4 5
#...
#.#.
.#..
...#
.#.#
```

### 输出

```
#XXX
#X#.
X#..
...#
.#.#
```

# 题解

## 作者：Mistybranch (赞：22)

[传送门](https://www.luogu.com.cn/problem/CF377A)

题目大概意思是：给出一个 $n \times m$ 的迷宫，保证所有空位置都是联通的，输出一种将其中的 $k$ 个空格子变成障碍还能保证剩下的空位置联通的方法。

这道题一看联通就知道是 dfs 的题了，大概说一下思路：

- 这道题思路还是蛮新颖的，如果正面去将空格子变为障碍物，那么要考虑的情况会很多，所以我们用逆向思维，将所有 $\texttt{.}$ 变为 $\texttt{X}$。

```cpp
for (int i = 1; i <= n; i++) {
	for (int j = 1; j <= m; j++) {
		if (ma[i][j] == '.') {
			ma[i][j] = 'X';
		}
	} 
}
```

- 然后我们找出一个大小为原空格个数减去 $k$ 的全部为 $\texttt{X}$ 的联通块并还原为 $\texttt{.}$，这部分 dfs 即可，注意联通块大小要设为全局变量。

```cpp
void Search (int x, int y) {
	int curX, curY;
	
	if (k <= 0) {
		return ;
	}
	
	ma[x][y] = '.';
	k--;
	
	for (int i = 0; i < 4; i++) {
		curX = x + changeX[i];
		curY = y + changeY[i];
		
		if (1 <= curX && curX <= n && 1 <= curY && curY <= m && ma[curX][curY] == 'X' && k) {
			Search(curX, curY);
		}
	}
}
```

完整代码：

```cpp


#include <bits/stdc++.h>

using namespace std;

int n, m, k;
char ma[509][509];
int changeX[4] = {0, 0, 1, -1};
int changeY[4] = {1, -1, 0, 0};

void Search (int x, int y) {
	int curX, curY;
	
	if (k <= 0) {
		return ;
	}
	
	ma[x][y] = '.';
	k--;
	
	for (int i = 0; i < 4; i++) {
		curX = x + changeX[i];
		curY = y + changeY[i];
		
		if (1 <= curX && curX <= n && 1 <= curY && curY <= m && ma[curX][curY] == 'X' && k) {
			Search(curX, curY);
		}
	}
}

int main () {
	scanf("%d %d %d", &n, &m, &k);
	
	k *= -1;
	
	for (int i = 1; i <= n; i++) {
		scanf("%s", ma[i] + 1);
		
		for (int j = 1; j <= m; j++) {
			if (ma[i][j] == '.') {
				ma[i][j] = 'X';
				k++;
			}
		} 
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (ma[i][j] == 'X') {
				Search(i, j);
				
				for (int x = 1; x <= n; x++) {
					printf("%s\n", ma[x] + 1);
				}
				
				return 0;
			}
		}
	} 
	
	return 0;
}
```


---

## 作者：LRL65 (赞：21)

因为本题是我们老师最喜欢的一道dfs，所以我就来写一篇题解。


------------
### 第一种做法（常规做法）：
我们来看看样例：
```
#..#
..#.
#...
```
我们将点编上序号：
```
#AB#
CD#E
#FGH
```
然后我们从 $A$ 开始 dfs，将 dfs 的顺序（按照上下左右）用树来表示，表示如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/rmm2geft.png)

然后题目就可以转化为**删除几个节点，使得这个树并不会“断开来”**，那么我们肯定是**删除叶子节点，然后再删除变成叶子节点的节点**……这样就不会将这个树弄“断开来”了。本题的顺序就应该是：EHGFCDBA。然后我们发现**这其实就是按照 dfs 返回的顺序来删的**。

那么程序也就很简单了。如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int disx[5]={-1,1,0,0},disy[5]={0,0,-1,1},cnt=0;
int n,m,k;
char a[505][505];
bool vis[505][505];
void dfs(int x,int y) {
    vis[x][y]=1;
	for(int i=0;i<4;i++) {
		int dx=x+disx[i],dy=y+disy[i];
		if(dx<=n && dx>=1 && dy>=1 && dy<=m && a[dx][dy]=='.'&&vis[dx][dy]==0) {
			dfs(dx,dy);
			if(cnt<k)cnt++,a[dx][dy]='X';
		}
	}
}
int main() {
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++)
			if(a[i][j]=='.')  {
				dfs(i,j);
                if(cnt==k-1)a[i][j]='X';
				for(int i1=1;i1<=n;i1++)  {
					for(int j1=1;j1<=m;j1++)
						cout<<a[i1][j1];
					cout<<endl;
				}
                return 0;
			}
}
```



------------

### 第二种做法（偷懒做法）：

这种方法很容易想，既然要将 $k$ 个变成墙，那我们只要跑 dfs ，跑 $sum-k  $ ($sum$指所有空气的数量) ，然后输出就行了。

那么程序也很简单。如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int disx[5]={-1,1,0,0},disy[5]={0,0,-1,1},sum=0,cnt=0;
int n,m,k;
char a[505][505];
bool vis[505][505];
void dfs(int x,int y) {
    cnt++;
	for(int i=0;i<4;i++) {
		int dx=x+disx[i],dy=y+disy[i];
		if(dx<=n && dx>=1 && dy>=1 && dy<=m && a[dx][dy]=='.'&& vis[dx][dy]==0 && cnt<sum-k) {
            vis[dx][dy]=1;    
			dfs(dx,dy);
		}
	}
}
int main() {
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) {
			cin>>a[i][j];
            if(a[i][j]=='.')sum++;
        }
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++)
			if(a[i][j]=='.')  {
                vis[i][j]=1;
				dfs(i,j); 
				for(int i1=1;i1<=n;i1++)  {
					for(int j1=1;j1<=m;j1++)
						if(a[i1][j1]=='.'&&vis[i1][j1]==0)cout<<'X';
						else cout<<a[i1][j1];
					cout<<endl;
				}
                return 0;
			}
}
```



---

## 作者：JeffWang2019 (赞：4)

[CF377A Maze](https://www.luogu.com.cn/problem/CF377A)

## 主要算法:bfs

思路:可以先把所有空地都设为新建的墙壁,再通过bfs恢复为空地.

## 详细方法

首先建立一个结构体 $node$ 来储存bfs过程中的每个点的坐标:

```cpp
struct node
{
    int x,y;//坐标
}st;//搜索起点,后面会用到
```

提到起点,有些人可能会问了,这个题没有指定起点,以哪里作为起点好呢?

嘿嘿,其实哪个点都行.因为此题没有唯一的答案,不用多虑.

同时,我们需要记录读入的地图中有多少空地,就是下面代码中的 $\_cnt$ 变量.

这样,我们在读入每个点的时候就能完成这项工作:

```cpp
    for(int i=1;i<=n;i++)//循环读入地图
    {
        for(int j=1;j<=m;j++)
        {
            cin>>c[i][j];
            if(c[i][j]=='.')//如果这是空地
            {
                c[i][j]='X';//先标记为新建的墙壁
                stx=i;
                sty=j;//标记为起点(随便哪个都行)
                _cnt++;//记录空地数
            }
        }
    }
    _cnt-=k;//减去k就是应该将新建墙壁恢复为空地的个数
```

然后通过bfs遍历整个图,将访问的合法点由新建墙壁恢复为空地.

需要注意的是,我们只需要将 $\_cnt$ 个新建墙壁恢复为空地,所以bfs的过程中也要建立一个变量 $cnt$ 来记录恢复为空地的个数.如果恢复得够了就直接结束bfs:

```cpp
            if(_cnt<=cnt)//这样表示恢复够了
            {
                return;
            }
```

bfs结束后,将最后的地图输出就可以了.

## 更多注释详见以下代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node
{
    int x,y;//坐标
}st;//搜索起点
queue<node>q;//bfs要用的队列
char c[505][505];
int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};//两个数组一起用就可以表示4个方向
int n,m,k,cnt=0,_cnt=0,stx,sty;
void bfs(int sx,int sy)//bfs
{
    c[sx][sy]='.';//先把起点标为空地
    st=(node){sx,sy};
    q.push(st);//起点入队
    cnt++;//起点变为空地,cnt就要自增一次,不能漏
    while(!q.empty())//只要队列不为空就一直循环
    {
        node ff=q.front();//取队头
        q.pop();
        int fx=ff.x,fy=ff.y;//记录当前的坐标
        for(int i=0;i<4;i++)//枚举4个方向
        {
            int xx=fx+dx[i],yy=fy+dy[i];//当前方向下的新坐标
            if(_cnt<=cnt)//这样就表示恢复够了
            {
                return;//直接结束
            }
            if(xx<1||yy<1||xx>n||yy>m||c[xx][yy]!='X')//不能出地图边界,也不能访问原先是墙或已经访问过的点(即已经恢复为空地的点)
            {
                continue;//尝试下一个方向
            }
            //到这里就是合法访问
            node gg=(node){xx,yy};
            q.push(gg);//将合法新点入队
            c[xx][yy]='.';//恢复为空地
            cnt++;//cnt自增
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)//循环读入地图
    {
        for(int j=1;j<=m;j++)
        {
            cin>>c[i][j];
            if(c[i][j]=='.')//如果这是空地
            {
                c[i][j]='X';//先标记为新建的墙壁
                stx=i;
                sty=j;//标记为起点(随便哪个都行)
                _cnt++;//记录空地数
            }
        }
    }
    _cnt-=k;//减去k就是应该将新建墙壁恢复为空地的个数
    bfs(stx,sty);//调用bfs算法
    //接下来就可以输出整个地图了
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            printf("%c",c[i][j]);
        }
        printf("\n");//输出千万条,格式第一条.换行不规范,爆零两行泪.
    }
    return 0;
}
```

**希望大家能听懂!**

**[篇末彩蛋](https://www.luogu.com.cn/blog/paiwyz314/)**

---

## 作者：vandijk (赞：4)

~~这题很难~~

首先，我们随便找一个点，bfs一下，找出依次遍历到的点，存储到一个vector里面。之后，我们再从后往前输出就行了，因为先输出后面的会对前面没有影响。

话不多说，上代码。

 _Code->_
 
 ```
#include <bits/stdc++.h>
using namespace std;
const int dx[]={1,-1,0,0};//上下左右
const int dy[]={0,0,1,-1};//上下左右
int n,m,k;
char c[510][510];
bool vis[510][510];
char tmp;
void bfs(int i,int j){//bfs
	queue<pair<int,int> > q;
	vector<pair<int,int> > v;//路径
	q.push(make_pair(i,j));
	vis[i][j]=1;
	while(!q.empty()){
		pair<int,int> p=q.front();
		q.pop();
		v.push_back(make_pair(p.first,p.second));
		for(int i=0;i<4;i++){
			int ax=p.first+dx[i];
			int ay=p.second+dy[i];
			if(ax>=0&&ax<n&&ay>=0&&ay<m&&!vis[ax][ay]&&c[ax][ay]=='.'){
				vis[ax][ay]=1;
				q.push(make_pair(ax,ay));
			}
		}
	}
	reverse(v.begin(),v.end());
	for(int i=0;i<k;i++){//替换
		c[v[i].first][v[i].second]='X';
	}
  //输出
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cout<<c[i][j];
		}
		cout<<endl;
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>c[i][j];
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(c[i][j]=='.'){
				bfs(i,j);
				return 0;
			}
		}
	}
	return 0;
}
```


---

## 作者：Loxilante (赞：3)

推荐一种比较船新~~偷懒~~的做法:

思路是这样的：

对于任意一张图，将所有' . '都改成' X '，因为输入是保证连通的，而你dfs的点也肯定是保证连通的，所以只用从1个点走p-k次(其中p是图中' X '(原来的' . ')的个数)，把走过的点打成' . '就行了。

上代码：
```cpp
#include<iostream>
using namespace std;
typedef long long ll;
int dx[] = {0, -1, 1, 0, 0}, dy[] = {0, 0, 0, -1, 1}, visit[510][510];
char w[510][510];
int n, m, k, p;
inline bool ok(int x, int y)
{
	return x >= 1 && x <= n && y >= 1 && y <= m && w[x][y] == 'X' && !visit[x][y]; 
}
inline void dfs(int x, int y)
{
	for(int i = 0; i < 5; ++i)
	{
		int px = x + dx[i], py = y + dy[i];
		if (ok(px, py) && p) --p, w[px][py] = '.', dfs(px, py);
	}
	visit[x][y] = 1;
}
int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m>>k;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
		{
			cin>>w[i][j];
			if (w[i][j] == '.') w[i][j] = 'X', p++; // p是'X'的个数 
		}
	p-=k; // 现在的p是要走的个数
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if (w[i][j] == 'X') // 随便找个点dfs 
				dfs(i, j);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
			cout<<w[i][j];
		cout<<'\n';
	}
	return 0;
}


```



------------
###### ~~谁抄谁爆零~~


---

## 作者：lzxhdxx (赞：3)

# CF377A Maze(bfs)
看到之前各位巨佬全都用了dfs，竟然一篇bfs题解也没有，那蒟蒻的我就补一篇bfs的题解吧

### 题意：
给出n*m的地图，**保证初始地图给出的'.'四联通（题眼）**，把其中的k个'.'改为'X'，要求不能破坏'.'的连通性

### 思路：
看到这样的题目，我们首先想到的肯定是搜索，但是我们应该选择bfs还是dfs？我们看数据规模，1≤n,m≤500，在这样的数据规模时，一般情况下dfs会超时，所以我们最好选择bfs（此题dfs也可以过~~肯定是因为数据弱~~）

搜索方法选好了，我们应该怎么保证剩余的'.'四联通呢？

在题意里，我特意加粗了一句话“**保证初始地图给出的'.'四联通**”，有了这句话，我们就很容易想到方法：

先把初始地图中所有的'.'改为'X'，然后我们用初始地图中的'.'的数量减去要求的'X'的数量得出cnt，这个cnt就是处理完以后应该有的'.'的数量，然后我们随便找一个'X'开始bfs，找到一个'X'就把它改为'.'，**因为搜索到的点都是联通的，所以我们更改的'.'肯定也都是联通的**，改完cnt个'X'后，剩余的'X'的数量就是k了，最后输出地图就可以了

Code：
```
#include <iostream>
#include <queue>

using namespace std;

const int MAX = 510;
int n, m, k, cnt = 0, cnt1 = 0, sx, sy, dx[5] = { 0,-1,1,0,0 }, dy[5] = { 0,0,0,-1,1 };
char c[MAX][MAX];
bool vis[MAX][MAX] = { false };

void bfs()//广搜
{
	queue<pair<int, int> >Q;//存点的队列
	Q.push(make_pair(sx, sy));//压入起点
	c[sx][sy] = '.', cnt++;//更改起点为'.'，更改的'X'数量（即cnt）+1
	while (!Q.empty())//循环直到队列空
	{
		int nowx = Q.front().first, nowy = Q.front().second;//取出队头
		for (int i = 1; i <= 4; i++)
		{
			int newx = nowx + dx[i], newy = nowy + dy[i];//扩展新点
			if (newx >= 1 && newy >= 1 && newx <= n && newy <= m && c[newx][newy] == 'X')
			{//如果新点没有越界且没有被扩展过
				if (cnt >= cnt1) return;//如果更改的'X'数量已经够了，直接返回
				Q.push(make_pair(newx, newy));//压入扩展的新点
				c[newx][newy] = '.', cnt++;//把新点更改为'.'，更改的'X'数量+1
			}
		}
		Q.pop();//弹队列
	}
}

int main()
{
	ios::sync_with_stdio(false);//加速cin,cout
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)//输入
		{
			cin >> c[i][j];
			if (c[i][j] == '.') c[i][j] = 'X', sx = i, sy = j, cnt1++;//把初始所有'.'都改成'X'，cnt1是原有的'.'的数量，sx、sy随便取一个起点坐标
		}
	cnt1 -= k;//求出应有的'.'的数量
	bfs();//开始广搜
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)//输出
			cout << c[i][j];
		cout << endl;
	}
	return 0;
}
```
数据：3.80s /  524.00KB /  1.06KB C++  ~~竟然比dfs慢难道我又写假了~~

新方法，求管理大大给过

---

## 作者：yzyjh (赞：2)

蒟蒻又来写题解了 awa

### 思路

我们找到一个点，然后dfs，把所有的儿子剪掉，这样就还会是一张连通图(DFS可以保证顺序）

上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,s;
char str[555][555]; 
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
bool vis[555][555];
vector<pair<int,int> > ord;
void dfs(int x,int y)
{
	if(vis[x][y]||str[x][y]=='#') return  ;
	vis[x][y]=1;
	ord.push_back(make_pair(x,y));//要按父节点到子节点的顺序压入
	for(int i=0;i<4;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<0||xx>=n||yy<0||yy>=m) continue;//越界情况
		dfs(xx,yy);//继续跑DFS
	}
}
int main() {
	cin>>n>>m>>s;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>str[i][j];
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(str[i][j]=='.')
			{
				dfs(i,j);
				reverse(ord.begin(),ord.end());//把顺序给调过来，这样就不会影响
				for(int k=0;k<s;k++)
				{
					str[ord[k].first][ord[k].second]='X';//把该变得变过来
				}
				for(int d=0;d<n;d++)//输出
				{
					for(int f=0;f<m;f++)
					{
						cout<<str[d][f]<<' ';
					}
					cout<<endl;
				}
				return 0;
			}
		}
	}
}
```



---

## 作者：TLMPEX (赞：2)

思路：很明显，这是道DFS题，可以枚举每一个点，看这个点是否符合边界条件，如果符合则标记这个点，表示走过在看下一个点，最后看k是否大于1，如果大于1了，则要把这个点置为‘X’了，如果要，则把这个点置为‘X’了，并把k减一

```c
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
bool vis[501][501];
char mp[501][501];
int n,m,k;
int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};//方向数组
void dfs(int x,int y)
{
	if(x<0||y<0||x>=n||y>=m||mp[x][y]!='.'||vis[x][y])
		return;//边界条件
	vis[x][y]=true;//标记
	for(int i=0;i<4;i++)
	{
		int fx=x+dx[i],fy=y+dy[i];//下一个点
		dfs(fx,fy);
	}
	if(k)//如果k还没有为0,则把这个点置为X并把k减一
	{
		mp[x][y]='X';
		k--;
	}
}
int main()
{
	cin>>n>>m>>k;
	for(int i=0;i<n;i++)
		scanf("%s",mp[i]);
	for(int i=0;i<n&&k;i++)
		for(int j=0;j<m&&k;j++)
			dfs(i,j);//枚举每一个点为X
	for(int i=0;i<n;i++)
		printf("%s\n",mp[i]);//输出地图
}
```


---

## 作者：小黑AWM (赞：2)

看到这个题下面只有一篇题解，突然心痒想发题解。
Emmm第一篇题解，发现发题解是一个很好的 _巩固自己知识的习惯_  然而抄题解是个  _让自己知识虚化的习惯_ ?……

思路：随便找个'.'的点进行DFS，然后把DFS图中出度为零的点一个一个去掉，去到K个为止。

还有好像k==0要稍微特判一下，不知道为什么第一次RE……上CF看了数据发现是一张全是点的图……
~~（讲的很扯各位神犇轻喷）~~

AC代码：
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
struct node{
    int x,y,father,son;
}tree[250010];
int n,m,k,sx,sy,tot;
char temp;
int map[550][550];
void dfs(int x,int y,int father){
    if(k<=0)return;
    int id=tot++;
    tree[id].x=x;
    tree[id].y=y;
    tree[id].father=father;
    tree[id].son=0;
    map[x][y]=-1;
    if(map[x+1][y]==1&&k>0)
        tree[id].son++,dfs(x+1,y,id);
    if(map[x-1][y]==1&&k>0)
        tree[id].son++,dfs(x-1,y,id);
    if(map[x][y+1]==1&&k>0)
        tree[id].son++,dfs(x,y+1,id);
    if(map[x][y-1]==1&&k>0)
        tree[id].son++,dfs(x,y-1,id);
    if(tree[id].son==0&&k>0)
        map[x][y]=2,tree[father].son--,k--;
}
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            cin>>temp;
            if(temp=='#')map[i][j]=0;
            if(temp=='.')map[i][j]=1;
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(map[i][j]==1){sx=i;sy=j;break;}
    dfs(sx,sy,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            if(map[i][j]==0)cout<<'#';
            else if(map[i][j]==-1)cout<<'.';
            else if(map[i][j]==2)cout<<'X';
            else if(map[i][j]==1)cout<<'.';
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：SULAWESI (赞：1)

**这题就是一道DFS啊……**  ~~（虽然我卡了2个小时）~~

  此题要求去加上k堵墙，使剩下的区域是一个四连通块。刚看到题我第一个想的竟然是暴力？？？ 枚举每一个 'X' 的位置，来确定剩下的是不是连通块……

  然后我发现这并不行 ~~（废话）~~ ，然后开始想该怎么做，然后发现应该是找连通块，于是决定把全部空地初始化为 'X' ，然后把连通块上的空地都换成 '.' 。这样就简单了。
  
**上代码**

```cpp
#include<iostream>

using namespace std;

int cnt,count;
int go[4]={1,0,-1,0},go1[4]={0,1,0,-1}; // 循环压行…… 
char map[505][505];

void dfs(int x,int y)
{
	if(count==cnt) // 限定空地包含的地方，确保补上的墙的个数为k 
	{
		return;
	}
	map[x][y]='.'; // 把墙换成空地 
	count++; // 空地包含数目 
	for(int i=0;i<4;i++) // 循环压行，不喜欢一堆if…… 
	{
		int xx=x+go[i],yy=y+go1[i];
		if(map[xx][yy]=='X')
		{
			dfs(xx,yy); 
		}
	}
}

int main()
{
	int n,m,k,cnt1=0;
	cin>>n>>m>>k;
	for(int i=0;i<n;i++)
	{
		for(int o=0;o<m;o++)
		{
			cin>>map[i][o];
			if(map[i][o]=='#') 
			{
				cnt1++;
			}else if(map[i][o]=='.')
			{
				map[i][o]='X';
			}
		}
	}
	cnt=n*m-cnt1-k; // 算空地的个数 
	for(int i=0;i<n;i++)
	{
		for(int o=0;o<m;o++)
		{
			if(map[i][o]=='X')
			{
				dfs(i,o); // 随便找一个地方开始搜连通块 
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int o=0;o<m;o++)
		{
			cout<<map[i][o];
		}
		cout<<endl;
	}
	return 0; // 第一次交没加 return 0; 导致部分RE？？？ 
}
```

这题所有情况随便输出一种就行了……

我太蒻了……

---

