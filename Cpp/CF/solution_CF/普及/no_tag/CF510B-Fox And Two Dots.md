# Fox And Two Dots

## 题目描述

Fox Ciel is playing a mobile puzzle game called "Two Dots". The basic levels are played on a board of size $ n×m $ cells, like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF510B/5e941a17ee5b7737fe65a0c59f70935ca12f4283.png)Each cell contains a dot that has some color. We will use different uppercase Latin characters to express different colors.

The key of this game is to find a cycle that contain dots of same color. Consider 4 blue dots on the picture forming a circle as an example. Formally, we call a sequence of dots $ d_{1},d_{2},...,d_{k} $ a cycle if and only if it meets the following condition:

1. These $ k $ dots are different: if $ i≠j $ then $ d_{i} $ is different from $ d_{j} $ .
2. $ k $ is at least 4.
3. All dots belong to the same color.
4. For all $ 1<=i<=k-1 $ : $ d_{i} $ and $ d_{i+1} $ are adjacent. Also, $ d_{k} $ and $ d_{1} $ should also be adjacent. Cells $ x $ and $ y $ are called adjacent if they share an edge.

Determine if there exists a cycle on the field.

## 说明/提示

In first sample test all 'A' form a cycle.

In second sample there is no such cycle.

The third sample is displayed on the picture above ('Y' = Yellow, 'B' = Blue, 'R' = Red).

## 样例 #1

### 输入

```
3 4
AAAA
ABCA
AAAA
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3 4
AAAA
ABCA
AADA
```

### 输出

```
No
```

## 样例 #3

### 输入

```
4 4
YYYR
BYBY
BBBY
BBBY
```

### 输出

```
Yes
```

## 样例 #4

### 输入

```
7 6
AAAAAB
ABBBAB
ABAAAB
ABABBB
ABAAAB
ABBBAB
AAAAAB
```

### 输出

```
Yes
```

## 样例 #5

### 输入

```
2 13
ABCDEFGHIJKLM
NOPQRSTUVWXYZ
```

### 输出

```
No
```

# 题解

## 作者：genshy (赞：12)

# 这个题的大意就是问我们有没有颜色相同的环，且环中节点数大于等于4 。

在搜索时两个需要注意的点

 1. 当一个点在之前已经被搜过，就说明出现了环
 2. 不能访问他的上一个状态，否则就会出错。

顺便提一句，我这种写法可以不回溯QAQ。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n,m,flag;
int cnt[210];
int dx[5] = {0,0,0,1,-1};
int dy[5] = {0,-1,1,0,0};
char map[55][55];
bool vis[55][55];
inline int read()
{
	int s = 0 ,w = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') w = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10+ch -'0'; ch = getchar();}
	return s * w;
}
bool check(int x,int y)//防越界
{
	if(x <= 0 || x > n || y <= 0 || y > m) return 0;
	return 1;
}
void dfs(int x,int y,char a,int fx,int fy)
{
	vis[x][y] = 1;//标记一下
	for(int i = 1; i <= 4; i++)
    {
		int xx = x + dx[i];
		int yy = y + dy[i];
		if(xx == fx && yy == fy) continue;//不能搜到他上一个状态
		if(vis[xx][yy] && map[xx][yy] == a ) flag = 1;//出现一个点在之前已经搜过就说明出现了环。
		if(check(xx,yy) && !vis[xx][yy] && map[xx][yy] == a)//继续搜颜色一样的且没有被访问过的
		{
	       dfs(xx,yy,a,x,y);	
		}
	}
	return ;
}
int main()
{
	n = read(); m = read();
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			cin>>map[i][j];
			cnt[map[i][j]-'0']++;//计算每种颜色的数量
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(!vis[i][j] && cnt[map[i][j]-'0'] >= 4) dfs(i,j,map[i][j],0,0);//判断这个点是否已经被搜过，且这个点颜色数量是否大于4
			if(flag == 1)//出现了环直接输出就ok了
			{
				cout<<"Yes"<<endl;
				return 0;
			}
		}
	}
	if(flag == 0)cout<<"No"<<endl;
	return 0;
}
```

最后提一句，其实这个题的难度没有那么大，很多同学可能都被他吓到了
QAQ

---

## 作者：Abyss_Bright (赞：5)

```
/*
一、一句话题意
一张你n，m的地图，然后跑图，看看是否有环。
什么是环？
就是走一圈能走到起点。
然后至少有四个点。
有输出Yes，没有输出No。
二、思路
思路已经非常清晰了。
我们直接把整个地图搜一遍，搜索时每次都搜相同的颜色。
如果搜到一个走过的点，那么就是一个环。 
我们可以用一个b来存储初始的颜色，防止它乱搜。 
三、代码
代码里有一些细节。
以下是AC代码： 
吐槽一下：
话说这为啥是道蓝题。
请大家不要被它吓到了。
*/
include<bits/stdc++.h>
#define itn int//防手滑大法。 
using namespace std;
const int dx[5]={-1,0,0,1};//移动数组就不说啦。 
const int dy[5]={0,1,-1,0};
int biaoji[52][52];//用作标记防止重复搜索。 
int n,m;
char b;//存上一个走的是哪个字母。 
int tot;//走的步数。 
char a[52][52];//存地图。 
void dfs(int x,int y,int qx,int qy,int sx,int sy)//现在所处位置x，y，起点位置qx，qy，上一次走的位置sx，sy。
{
	tot++;//步数++。 
	for(int i=0;i<4;i++)
	{
		int mx=x+dx[i];
		int my=y+dy[i];		
		if(sx==mx&&sy==my)//不能搜到它上一个走的位置。 
		continue;
		if(biaoji[mx][my]==1&&tot>=4&&a[mx][my]==a[qx][qy])//走的步数要大于4，而且是走了一圈再回到起点,一定注意要有第三个条件，保证走的是初始颜色。 
		{
			cout<<"Yes";//有就直接输出了，节约时间。 
			exit(0);//类似于return 0。 
		}
		if(mx<=0||my<=0||mx>n||my>m||biaoji[mx][my]==1||a[mx][my]!=a[qx][qy])//不能出界，不能走走过的位置，不能走不同颜色的位置。 
		continue;
		biaoji[mx][my]=1;//标记。 
		dfs(mx,my,qx,qy,x,y);//继续搜索。 
		tot--;//回溯。 
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(biaoji[i][j]==0)//不走走过的位置 
			{
				biaoji[i][j]=1;//标记 
				tot=0;//步数重置 
				b=a[i][j];//存储初始颜色 
				dfs(i,j,i,j,0,0);//开始搜索，上一次没有位置，故给0和0。 
			}
	cout<<"No";//如果里面没搜到，说明没有，直接不行。 
	return 0;
}
```



---

## 作者：black_trees (赞：4)

### 还是我一贯的风格，先解读题意
------

题目要求你去搜索给出的矩阵里是否有环。

那这算法不就很明显了吗？

首先，我们从每一个点开始搜，搜到不同字母 `continue` ,搜到相同字母继续递归搜索，并且标记当前位置的 $vis$ 为 `true`。

上面就是普通的联通块板子，给出代码实现：


```cpp
void dfs(int x,int y){
	for(register int i=1;i<=4;++i){
		int nx=x+dx[i];//新的x方向
		int ny=y+dy[i];//新的y方向
		if(nx<1||ny<1||nx>n||ny>m||vis[nx][ny]==true){
			continue;
		}//搜出去或是访问过，continue
		vis[nx][ny]=true;//标记
		dfs(nx,ny);//递归继续搜索
	}
}
```


但是要注意的一点是，我们为了判断它是环，采取的方法是判断搜不搜得到出发点。

但是，我们的方向数组是 $4$ 个方向的！所以我们还要判断这里是不是原来走过的位置。

做法很简单，用两个变量 $sx,sy$ 来记录走过的地方就可以了，如果$nx=sx$ 且 $sy=ny$ 那也 `continue ` 掉。

代码如下：

```cpp
int sx,sy;
void dfs(int x,int y){
	for(register int i=1;i<=4;++i){
		int nx=x+dx[i];
		int ny=y+dy[i];
		if(nx<1||ny<1||nx>n||ny>m||vis[nx][ny]==true){
			continue;
		}
		if(sx==nx&&sy==ny){
			continue;
		}
		sx=x;
		sy=y;//这里放在for循环里面，因为放在外面的话，递归的时候就会更新它们，那设置这两个变量就没有意义了。
		vis[nx][ny]=true;
		dfs(nx,ny);
	}
}
```

具体代码不放了，看懂了之后可以自己实现的，我只是提供一种思路。

管理大大求过QAQ。

-------

另外吐槽一句：这为什么是蓝题啊，不应该是黄题么？

---

## 作者：RuntimeErr (赞：2)

## 发现居然很少人用 BFS 写诶

先来说一下用 `BFS` 的优点，就是相比 `DFS` 来说不会存在爆栈的危险；缺点呢，就是比较难写（。

再来讲回题目，这是 [原题传送门](https://www.luogu.com.cn/problem/CF510B)
，一道显然的求连通块的题。

# $Description:$

给您一张 $n\times m$ 的矩阵，矩阵上的每一个点都有自己的颜色，让您求这些颜色构成的连通块是否有成环状的，环的长度必须 $\ge4$。

# $Solution:$

其实很简单，我们可以手摸一下，从一个连通块内的点开始，只要不往回走，搜到一个在连通块内且**遍历过**的点，这个点与开始的点之间的路径一定构成环，且环的长度一定 $\ge 4$。

那么我们就可以在 `BFS` 的队列中给每个点存以下信息：这个点本身的坐标，上一个点的坐标。

我们只要保证不往回走，搜到一个已经遍历到的点就可以退出 `BFS` 并输出 $Yes$ 了。

# $Code:$

```cpp
#include<cstdio>
#include<queue>
using namespace std;

const int N=55;
struct node{//每个点存本身的坐标和上一个点的坐标 
	int x,y,lx,ly;
};

int n,m;
char map[N][N];
bool vis[N][N],flag;
int f[4][2]={{-1,0},{0,-1},{0,1},{1,0}};//4个方向 
queue<node> q;

void bfs(int i,int j){
    q.push({i,j,-1,-1});
    while(!q.empty()){
        node tmp=q.front();q.pop();
        vis[tmp.x][tmp.y]=true;
        for(int k=0;k<4;++k){
            int xx=tmp.x+f[k][0],yy=tmp.y+f[k][1];
            if(xx<=0||xx>n||yy<=0||yy>m||(xx==tmp.lx&&yy==tmp.ly))continue;//越界或者走回去了就不搜 
            if(map[tmp.x][tmp.y]!=map[xx][yy])continue;//不在同一连通块也不搜 
            if(vis[xx][yy]){flag=true;break;}//找到一个已经遍历的点就可以退出 
            else q.push({xx,yy,tmp.x,tmp.y});
        }
        if(flag)break;
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            scanf(" %c",&map[i][j]);
        }
    }
    for(int i=1;i<=n;++i){//普通连通块做法 
        for(int j=1;j<=m;++j){
            if(!vis[i][j]){
                bfs(i,j);
                if(flag){
                    puts("Yes");
                    return 0;
                }
            }
        }
    }
    puts("No");
    return 0;
}
```


---

## 作者：xixiup (赞：2)

## 题目大意

给你一个矩阵，让你求出这个矩阵中是否有由同一个字母组成的环。

## 思路分享

这里我要提供一个跑的飞快又~~好写好想好调~~的思路：**并查集**。

我们可以思考，若两个相同的字母是相邻的，那么就判断，若不再同一个并查集中，就合并两个并查集，若在同一个并查集中，则证明有环，直接输出。

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=60;
int n,m,ma[maxn][maxn];
int fa[maxn*maxn];
int get_nu(int x,int y){//求点(x,y)的编号
	return (x-1)*m+y;
}
int find(int x){//并查集
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c=getchar();//输入
			while(c<'A'||c>'Z'){
				c=getchar();
			}
			ma[i][j]=c-'A'+1;
		}
	}
	for(int i=1;i<=n*m;i++){
		fa[i]=i;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(i>1&&ma[i][j]==ma[i-1][j]){判断上面的点
				int fx=find(get_nu(i,j)),fy=find(get_nu(i-1,j));
				if(fx==fy){
					puts("Yes");
					return 0;
				}
				fa[fx]=fy;
			}
			if(j>1&&ma[i][j]==ma[i][j-1]){//判断左边的点
				int fx=find(get_nu(i,j)),fy=find(get_nu(i,j-1));
				if(fx==fy){
					puts("Yes");
					return 0;
				}
				fa[fx]=fy;
			}
		}
	}
	puts("No");
	return 0;
}

```


---

## 作者：Essinsop (赞：1)

题意是给定一张图，问图中是否有一个环。由于环中字母一定一样，想到 dfs 爆搜图中的连通块。

实际上,判断是否有一个环只需要看看该连通块中是否有一个走过的点再次被走到。

还要注意的是，不能走回头路，但因为判断环也需要用 $vis$ 数组，我们需要再记录上一步是怎么走到这一步的。

代码如下：

```
#include <bits/stdc++.h>
using namespace std;
int n, m;
bool vis[55][55], flag;
char mps[55][55];
int fx[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
bool check(int xx, int yy, char p) {
	return xx >= 1 && xx <= n && yy >= 1 && yy <= m && mps[xx][yy] == p;
}
void dfs(int x, int y, int k, char p) {//k是为了记录上一步怎么走到这一步来,为防止走回头路
	for(int i = 0;i <= 3;i++) {
		int xx = x + fx[i][0];
		int yy = y + fx[i][1];
		if((i == 0 && k == 1) || (i == 1 && k == 0) || (i == 2 && k == 3) || (i == 3 && k == 2)) continue;
		if(check(xx, yy, p)) {
			if(vis[xx][yy] == true) {//如果检测到环了直接返回即可
				flag = true;
				return;
			}
			vis[xx][yy] = true;
			dfs(xx, yy, i, p);
			if(flag) return;//已经有答案了,不需要再搜下去
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;i++) for(int j = 1;j <= m;j++) cin >> mps[i][j];
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= m;j++) {
			if(!vis[i][j]) dfs(i, j, -1, mps[i][j]);//逐个判断连通块中是否有环
			if(flag) {
				cout << "Yes" << endl;
				return 0;
			}
		}
	}
	cout << "No" << endl;
}
```


---

## 作者：NSOI (赞：1)

~~这题应该是黄题~~

[题目传送门](https://www.luogu.com.cn/problem/CF510B)

## 分析

环是什么就不说了。

主要是判断它是否是环。

其实我们在访问每一个点的时候。

判断它的末端是否等于前端。

所以要存下来起点和上一次走过的点。

AC代码：
```c
#include<bits/stdc++.h>
using namespace std;
const int MAXN=55;
int dx[]={0,0,-1,1};//dx
int dy[]={1,-1,0,0};//dy
int vis[MAXN][MAXN];//标记数组
char mp[MAXN][MAXN];
int n,m;
int all;//记录环内有几个数 
void dfs(int x,int y/*当前走到哪*/,int ex,int ey/*起点*/,int sx,int sy){
	if(x<1||y<1||y>m||x>n)return ;//走出格要return 
	all++;
	for(int i=0;i<4;i++){//枚举dx,dy 
		int hx=x+dx[i],hy=y+dy[i];
		if(hx==sx&&hy==sy)continue ;
		if(vis[hx][hy]&&all>3&&mp[hx][hy]==mp[ex][ey]){
			printf("Yes");
			exit(0);//退出
		}
		if(vis[hx][hy]||mp[hx][hy]!=mp[ex][ey])continue;
		vis[hx][hy]=1;//标记走过
		dfs(hx,hy,ex,ey,x,y);
		all--;//回溯！！！
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)cin>>mp[i][j];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(vis[i][j]==0){//走过就跳过
				vis[i][j]=1;
				all=0;
				dfs(i,j,i,j,0,0); //dfs
			} 
		}
	}
	printf("No");//沒结果就No
    return 0;
}
```

---

## 作者：xyf007 (赞：1)

### 深搜所有可达的点，判断能否产生环即可
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
int n,m,dx[4]={1,0,-1,0},dy[4]={0,1,0,-1},tox,toy;
bool vis[51][51];
char a[51][51];
void dfs(int x,int y,char color,int step)
{
	if(step>=3&&((x==tox&&y==toy-1)||(x==tox&&y==toy+1)||(x==tox-1&&y==toy)||(x==tox+1&&y==toy)))
	{
		printf("Yes");
		exit(0);
	}
	vis[x][y]=1;
	for(int i=0;i<4;i++)
	{
		int tx=x+dx[i],ty=y+dy[i];
		if(tx<=0||tx>n||ty<=0||toy>m||vis[tx][ty]||a[tx][ty]!=color)
		{
			continue;
		}
		dfs(tx,ty,color,step+1);
	}
	vis[x][y]=0;
}
int main()
{
	scanf("%d%d\n",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			a[i][j]=getchar();
		}
		getchar();
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(!vis[i][j])
			{
				tox=i;
				toy=j;
				dfs(i,j,a[i][j],0);
			}
		}
	}
	printf("No");
	return 0;
}
```

---

## 作者：_lxy_ (赞：1)

### 题意
判断一个$n \times m $ 的棋盘上是否有环 $($颜色相同的环状连通块，且最少有4块$)$。
### 分析
用dfs搜一遍，如果是颜色相同的就继续搜，记录起点和转弯次数，如果转$4$次走回起点就输出`YES`，如果搜了一遍搜不到环，就输出`NO`。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=57;
int n,m,sx,sy;//sx,sy记录本次搜索起点的坐标
char a[MAXN][MAXN];
bool flag;
void dfs(int x,int y,int z,int turns) // x,y分别是当前点的行、列 z是当前的方向（1是下，2是上，3是右，4是左） turns记录转弯次数
{
    if(x<=0||y<=0||x>n||y>m) return;
    if(turns>4||flag) return;
    if(x==sx&&y==sy&&turns==3)
    {
        flag=true;
        return;
    }
    if(z==0) //出发点
    {
        if(a[x+1][y]==a[x][y]) dfs(x+1,y,1,0);
        if(a[x-1][y]==a[x][y]) dfs(x-1,y,2,0);
        if(a[x][y+1]==a[x][y]) dfs(x,y+1,3,0);
        if(a[x][y-1]==a[x][y]) dfs(x,y-1,4,0);
    }
    if(z==1) //从下面来的
    {
        if(a[x+1][y]==a[x][y]) dfs(x+1,y,1,turns);
        if(a[x][y+1]==a[x][y]) dfs(x,y+1,3,turns+1);
        if(a[x][y-1]==a[x][y]) dfs(x,y-1,4,turns+1);
    }
    if(z==2) //从上面来的
    {
        if(a[x-1][y]==a[x][y]) dfs(x-1,y,2,turns);
        if(a[x][y+1]==a[x][y]) dfs(x,y+1,3,turns+1);
        if(a[x][y-1]==a[x][y]) dfs(x,y-1,4,turns+1);
    }
    if(z==3) //从右边来的
    {
        if(a[x][y+1]==a[x][y]) dfs(x,y+1,3,turns);
        if(a[x-1][y]==a[x][y]) dfs(x-1,y,2,turns+1);
        if(a[x+1][y]==a[x][y]) dfs(x+1,y,1,turns+1);
    }
    if(z==4) //从左边来的
    {
        if(a[x][y-1]==a[x][y]) dfs(x,y-1,3,turns);
        if(a[x-1][y]==a[x][y]) dfs(x-1,y,2,turns+1);
        if(a[x+1][y]==a[x][y]) dfs(x+1,y,1,turns+1);
    }
}
int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n>>m;
    int i,j;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            cin>>a[i][j];
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            sx=i;sy=j;
            dfs(i,j,0,0);
            if(flag)
            {
                cout<<"Yes"<<endl;
                return 0;
            }
        }
    }
    cout<<"No"<<endl;
    return 0;
}
```


---

## 作者：XL4453 (赞：0)

~~这题恶评吧。~~

------------
### 题目分析：

题目就是要求一个四联通的环，可以发现，任意一个四联通的环都至少有四个点，所以题目中的另一个条件——点数大于或等于四，可以直接不用判断。

然后考虑如何求出这样的一个环，可以用普通的 DFS 算法，直接对于每一种颜色跑一遍就可以了。

具体的，记录当前节点是由哪一个节点拓展过来的，访问时避开，若再次访问到已访问节点就说明出现了环。

复杂度：$O(nm)$，瓶颈在于读入。

------------
### 代码：

```cpp
#include<cstdio>
using namespace std;
char a[55][55];
int n,m,l,r,v[55][55];
int dx[5]={0,0,1,-1},dy[5]={1,-1,0,0};
bool dfs(int x,int y,int fx,int fy){
	if(v[x][y]==1)return 1;
	v[x][y]=1;
	for(int i=0;i<=3;i++)
	if((x+dx[i]!=fx||y+dy[i]!=fy)&&a[x][y]==a[x+dx[i]][y+dy[i]]){
		if(dfs(x+dx[i],y+dy[i],x,y))return 1;
	}
	return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		a[i][j]=getchar();
		while(a[i][j]=='\n'||a[i][j]==' ')a[i][j]=getchar();
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	if(!v[i][j])
	if(dfs(i,j,i,j)){
		printf("Yes");
		return 0;
	}
	printf("No");
	return 0;
}
```

---

## 作者：L7_56 (赞：0)

### 首先看题
这题主要是要找环

对于一个环，要求至少有四个点

在搜索的过程中，只要搜到了一个已经走过的点，那么一定可以形成一个闭合的环

但是如果是搜到了来的那个点，如图
![](https://cdn.luogu.com.cn/upload/image_hosting/rjhezjdc.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

就会判断成环

所以在搜索中还需要加上两个变量描述来的坐标

而至少有四个点的要求，因为是在二维平面中，且只能上下左右移动，所以当按照上面的方法判断成环以后，至少会有四个点
![](https://cdn.luogu.com.cn/upload/image_hosting/f17ihfb0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

就像这样

对环的判断解决以后就很简单了，只要依次枚举地图中没有访问过的点并搜索颜色相同的点的环，找到就输出就可以了
## 代码
```cpp
#include<iostream>
#include<cstdio>

using namespace std;

char mp[60][60];
int num[26];
bool vis[60][60],flag;
int n,m;
int xx[]={1,0,-1,0};
int yy[]={0,1,0,-1};

void dfs(int x,int y,int fx,int fy);
//x,y是当前点的位置,fx,fy是来的点的位置

int main()
{
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;++i)
	 for(int j=1;j<=m;++j){
	 	cin>>mp[i][j];
	 	num[mp[i][j]-'A']++;
		//num数组记录每种字母的个数，如果小于4一定无法形成环
	 }
	 	
	 
	for(int i=1;i<=n;++i)
	 for(int j=1;j<=m;++j)
	 if(num[mp[i][j]-'A']>=4&&!vis[i][j]){
	 	vis[i][j]=1;
	 	dfs(i,j,i,j);//第一个点相当于从自己来
	 	if(flag) break;//找到就可以直接退出
	 }
	if(flag) printf("Yes");
	else printf("No");
	return 0;
}

void dfs(int x,int y,int fx,int fy){
	if(x<1||x>n||y<1||y>m) return;
	//越界判定
	vis[x][y]=1;//标记
	for(int k=0;k<4;++k){
		int cx=x+xx[k];
		int cy=y+yy[k];
		if(cx==fx&&cy==fy) continue;//不往回走
		
		if(mp[cx][cy]==mp[x][y]) {
			if(!vis[cx][cy]){
				dfs(cx,cy,x,y);
				if(flag) return;
			}//继续拓展环
			else {
				flag=1;return;
                //找到了
			}
		}
	}
}
```

---

## 作者：Paris_Bentley (赞：0)

第一篇题解。

做完题目想看题解有木有能优化的部分，发现还木有伙伴用BFS,答案是广搜一丢丢变化。

就是如果访问到某个点，就利用vis标记有访问过，每次搜索的时候不搜索上一步的那个点，这样如果之后访问到的某个点之前已经访问过，就一定是另一个方向可以到达的点，也就是可以成环。

这样就要入队时做一个小的标记，不仅需要保留这一点的位置x和y，我还用了两个变量a和b保留当前入队这一项是从哪个方向来的，也就是上一步加的dx和dy。

有个小位置需要注意，举个例子，比如上一个点是向右扩展入队，那么a和b分别是0和1,代表上一个点的坐标横轴+0，纵轴+1。所以这个点就不可以向左拓展，所以，dx和dy中+0和-1的一项不需要拓展入队。

看不懂的伙伴可以看下面的代码注释，或者留言哦~


PS：可能还有可以简化的位置，但是数据量不大，bfs也不需要剪枝，下列代码可以AC，所以就没进一步修改。
```cpp
#include <bits/stdc++.h>
using namespace std;
struct heng
{
	int x,y,a,b;//x,y坐标，a,b来的方向 
}; 
int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0};
queue<heng> q;
bool vis[55][55];//是否拜访过这个点 
int n,m;
char c[55][55];
int main()
{
	scanf("%d%d",&n,&m);
	getchar();
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=m;j++)
		{
			c[i][j]=getchar();
		} 
		getchar();
	}
	for(register int i=1;i<=n;i++) 
	{
		for (register int j=1;j<=m;j++)//以每个点为起点，找是否存在环 
		{
			char nowc=c[i][j];//当前位置字母 
			memset(vis,false,sizeof(vis));//清空vis数组 
			q=queue<heng>();//清空队列 
			heng hehe;
			hehe.x=i;hehe.y=j;
			hehe.a=0;hehe.b=0; //保证初始点的每个dx和dy不会CONTINUE
			q.push(hehe);
			//cout<<i<<" "<<j<<endl;
			vis[i][j]=true;
			while (q.size())
			{
				int xx,yy,aa,bb;
				xx=q.front().x;
				yy=q.front().y;
				aa=q.front().a;
				bb=q.front().b;
				if(aa!=0)aa=-aa;//从来的方向推导出反方向 
				if(bb!=0)bb=-bb;
				q.pop();
				for (int ii=0;ii<4;ii++)//四个方向 
				{
					int xxx,yyy;//下一点位置 
					xxx=xx+dx[ii];
					yyy=yy+dy[ii];
					if(aa==dx[ii]&&bb==dy[ii]) continue;//上一步来的方向不去。 
					if(xxx>=1&&xxx<=n&&yyy>=1&&yyy<=m)//数据合法 
					{
						if(nowc!=c[xxx][yyy]) continue; //字母不同跳过 
						if(vis[xxx][yyy])//相同且走过，不是来的方向，成环 
						{
							cout<<"Yes\n" ;
							exit(0);
						}
						else //是新点入队 
						{
							heng xin;
							xin.x=xxx;
							xin.y=yyy;
							xin.a=dx[ii];
							xin.b=dy[ii];
							q.push(xin); 
							vis[xxx][yyy]=true;
						}
					}
				}
			}
			
		}
	}
	cout<<"No\n";
	return 0;
 } 
 
```


---

