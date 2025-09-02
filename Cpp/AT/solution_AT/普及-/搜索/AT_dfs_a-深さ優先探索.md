# 深さ優先探索

## 题目描述

[problemUrl]: https://atcoder.jp/contests/atc001/tasks/dfs_a

この問題は、講座用問題です。ページ下部に解説が掲載されています。

高橋君の住む街は長方形の形をしており、格子状の区画に区切られています。 長方形の各辺は東西及び南北に並行です。 各区画は道または塀のどちらかであり、高橋君は道を東西南北に移動できますが斜めには移動できません。 また、塀の区画は通ることができません。

高橋君が、塀を壊したりすることなく道を通って魚屋にたどり着けるかどうか判定してください。

## 说明/提示

### 解説

  **[深さ優先探索による塗りつぶし](https://www.slideshare.net/secret/lyag9AlTOMIY2J "深さ優先探索による塗りつぶし")**  from **[AtCoder Inc.](http://www.slideshare.net/chokudai)** 

### Sample Explanation 1

高橋君は、魚屋にたどり着くことができません。

## 样例 #1

### 输入

```
4 5
s####
....#
#####
#...g```

### 输出

```
No```

## 样例 #2

### 输入

```
4 4
...s
....
....
.g..```

### 输出

```
Yes```

## 样例 #3

### 输入

```
10 10
s.........
#########.
#.......#.
#..####.#.
##....#.#.
#####.#.#.
g.#.#.#.#.
#.#.#.#.#.
###.#.#.#.
#.....#...```

### 输出

```
No```

## 样例 #4

### 输入

```
10 10
s.........
#########.
#.......#.
#..####.#.
##....#.#.
#####.#.#.
g.#.#.#.#.
#.#.#.#.#.
#.#.#.#.#.
#.....#...```

### 输出

```
Yes```

## 样例 #5

### 输入

```
1 10
s..####..g```

### 输出

```
No```

# 题解

## 作者：hhhwg07 (赞：68)

这是一道 _相当标准_ 的搜索题目。具体思路是用一个“bool”型的二维数组来表示小区（true：可以走、false：不可走）。之后从家搜索，搜到鱼店就停止，若搜完还没有搜到则不行。


------------
先定义变量（注：这里g不能定成500x500或501x501具体原因会在dfs解释）
```cpp
bool g[502][502],check;//小区，总体可不可行
int n,m,sx,sy,ex,ey;//行，列，开始坐标，结束坐标
int dx[]={0,0,-1,1};//偏移量
int dy[]={1,-1,0,0};
```


------------
之后是关键
dfs:
```cpp
void dfs(int x,int y){
	if(check){//如果之前已经有正确情况就直接退出
		return ;
	}
	if(ex==x&&ey==y){//这是正确情况，将总体情况（check）赋值为true，之后退出
		check=true;
		return ;
	}
    /*!!!这就是为什么g要定成502x502，为的是防止越界！
    将小区外面围一圈false之后，妈妈就再也不会担心我越界了！
    毕竟是false，不会搜到，那么想要搜到再外面也不可能了。
    */
	int nowx,nowy;
	for(int i=0;i<4;i++){
		nowx=x+dx[i];nowy=y+dy[i];
		if(g[nowx][nowy]){
			g[x][y]=false;
			dfs(nowx,nowy);
            //这里不能将状态回归！
            //毕竟之前竟然到过这里那么这里的情况肯定已经全部搜我。我因为没有早些出坑，找了半天错就是不知道为啥TLE,:-(
		}
	}
}
```


------------
随便写写主函数
```cpp
int main(){
	//49-64行为输入
	cin>>n>>m;
	char c;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c;
			if(c!='#'){
				g[i][j]=true;
				if(c=='s'){
					sx=i;sy=j;
				}
				if(c=='g'){
					ex=i;ey=j;
				}
			}
		}
	}
	g[sx][sy]=false;
	dfs(sx,sy);//搜索一下
	if(check){//Perfect ending （英）、Fin parfait（法）、Der perfekte abschluss eines（德）。中文自己查:-)
		cout<<"Yes\n";
	}
	else{
		cout<<"No\n";
	}
	return 0;
} 
```
来个五星好评谢谢

---

## 作者：mcyqwq (赞：22)

### 看到之前的大佬们都没人写BFS的题解，我就来水一发吧

BFS(**广度优先搜索**，又称**宽度优先搜索**)是最简便的图的搜索算法之一，~~不会的大佬们可以去百度一下~~

BFS大部分情况下要用到**队列**~~（不会的大佬们也可以去问度娘）~~。

本题BFS核心思想：从初始节点开始，将初始节点入队，然后搜索每一个队中元素一步可以到达的另一个节点（不重复），这样每次搜索成为一次**扩展操作**，再将搜索到的这些节点加入队。这样循环操作，直到每一个节点都被访问过，即**队头指针和队尾指针相等**为止。

关于队列的实现：队头指针指向待扩展的节点，队尾指针指向新搜索到的节点，当所有节点都被扩展完毕，即队头指针和队尾指针相等时，退出循环，如果此时目标节点仍未被访问，说明**初始节点和目标节点不联通**，即**无法到达终点**。

值得一提的是：BFS在第一次搜索到目标节点时即可输出答案，无需继续进行后面的循环

参考代码：

```cpp
#include<iostream>
using namespace std;
const int dx[4]={1,0,-1,0},dy[4]={0,-1,0,1};    //方向数组，和DFS一样
int a[250001],b[250001],x,y,sx,sy,ex,ey,n,m,map[501][501];
char s[501][501];
bool check=false;    //是否已经搜索到终点的判断
int main()
{
    int i,j;
    cin>>n>>m;
    for(i=1;i<=n;i++)
    for(j=1;j<=m;j++)
    cin>>s[i][j];    //输入
    for(i=1;i<=n;i++)
    for(j=1;j<=m;j++)
    {
    	if(s[i][j]=='.') map[i][j]=0;
    	if(s[i][j]=='#') map[i][j]=1;
    	if(s[i][j]=='s'){sx=i; sy=j; map[i][j]=0;}
    	if(s[i][j]=='g'){ex=i; ey=j; map[i][j]=0;}
    }    //map[i][j]为1代表不可行，0代表可行，sx和sy是起点坐标，ex和ey是终点坐标
    int head=0,tail=1;
    map[sx][sy]=-1;
    a[tail]=sx;
    b[tail]=sy;    //初始化，a数组储存x坐标，b数组储存y坐标
    while(head!=tail)    //借助队列实现BFS，算法的主体
    {
        head++;    //队头指针指向待扩展节点
        for(i=0;i<4;i++)    //可向四个方向移动
        {
            x=a[head]+dx[i];
            y=b[head]+dy[i];    //搜索与此节点相连的四个点
            if(x<=n&&x>0&&y<=m&&y>0&&!map[x][y])    //边界和障碍物以及是否访问过的判断
            {
                //如果在地图内且不是障碍格且未被访问过
                tail++;    //队尾指针加1，指向新搜索到的节点
                a[tail]=x;
                b[tail]=y;    //将此节点入队
                map[x][y]=-1;    //标记为已被访问过（障碍格为1，已访问过的格为-1）
                if(x==ex&&y==ey)  //找到了终点
                {
                    cout<<"Yes"<<endl;
                    check=1;    //后面的操作无需继续进行，退出循环
                }
            }
        }
        if(check==true) break;    //退出循环
    }
    if(check==false) cout<<"No"<<endl;    //当所有可以走到的节点都被访问之后，仍找不到目标节点，输出No
    return 0;
}
```
**在最后顺带弱弱地问问管理员：这道题现在用的翻译好像是我做的,能不能在翻译后加上我的用户名QAQ**

---

## 作者：uiuili (赞：11)

本题可DFS或BFS求解；
```cpp
//DFS代码；
#include <iostream>
#include <string>
using namespace std;
int n,m;
int dir[4][2] = {{-1,0},{0,-1},{1,0},{0,1}}; //定义方向数组 ； 
string maze[1100];  //定义地图；
bool vis[1100][1100];  //定义标记数组， 记录当前点是否走过； 
bool in(int x,int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}   // 判断函数，判断当前点是否位于地图内； 
bool dfs(int x,int y) {
    if (maze[x][y] == 'g') {
        return true;
    } //判断是否到达；； 
    vis[x][y] = 1;  //标记当前点； 
    for (int i = 0; i < 4; i++) { // 向四个方向搜索； 
        int tx = x + dir[i][0];
        int ty = y + dir[i][1];
        if (in(tx,ty) && maze[tx][ty] != '#' && !vis[tx][ty]) { //在地图内、不是障碍物、未访问则可继续搜索； 
            if (dfs(tx,ty)) {
                return true; // 在(tx,ty)能到达，在(x,y)也能到达； 
            }
        }
    }
    //在此若加上： vis[x][y] = 0； 则会出现超时数据； 
    //若删除标记，则从其他点也可搜索至(x,y)； 
    //从(x,y)无法到达终点，则从其他点到达(x,y)之后也无法到达终点； 
    //故无需回溯； 
	return false;
}
int main () {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> maze[i];
    } // 输入地图； 
    int x,y;
    for (int i = 0; i < n; i++) { // 寻找起点； 
        for (int j = 0; j < m; j++) {
            if (maze[i][j] == 's') {
                x = i, y = j;
            }
        }
    }
    if (dfs(x,y)) {
        cout << "Yes";
    } else {
        cout << "No";
    }
    return 0;
}
```
亦可用BFS求解；
```cpp
#include <iostream>
#include <string>
#include <queue>
using namespace std;
int n,m;
string maze[110];
bool vis[110][110];
int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
bool in(int x,int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}
struct node{ //结构体内定义构造函数；
	int x,y;
	node(int xx,int yy) {
		x = xx;
	        y = yy;
	}
};
bool bfs(int sx,int sy) {
	queue<node> q; //定义队列；
	q.push(node(sx,sy));//当前点插入队列；
	vis[sx][sy] = true; //记录此点已插入；
	while(!q.empty()) {
		node now = q.front(); //非空时不断取出队首点；
		q.pop();
		for (int i = 0; i < 4; i++) { //辐散四周点；
			int tx = now.x + dir[i][0];
			int ty = now.y + dir[i][1];
			if (in(tx,ty) && maze[tx][ty] != '#' && !vis[tx][ty]) {
				if (maze[tx][ty] == 'g') {
					return true;
				} else {
					q.push(node(tx,ty));// 入队；
                                        vis[tx][ty] = true; //标记入队；
				}
			}
		}
	}
	return false;
}
int main () {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> maze[i];
	}
	int x,y;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (maze[i][j] == 's') {
			   x = i, y = j;	
			}
		}
	}
	if (bfs(x,y)) {
		cout << "Yes";
	} else {
		cout << "No";
	}
	return 0;
}
```
此题可作为学习深搜与广搜的基础理解题。
Wish you RP++;

---

## 作者：a2920353120 (赞：8)

> $ \color{gold}\text{第一篇题解如有不对之处请指出} $
>  ### *哇这道题的题目好像就说了是深搜诶*
 > 
 >  一道**深搜**的模板题
 > 
 >  思路如下：
 > 
 > ```记录起点，终点，从起点开始向上下左右四个方向拓展```
 > 
 > 如果没有**越界**且**没有被访问**过且**不是墙**就能走
 >
 > 搜索完了回来看看终点有没有被经过
 >
 > ### 代码实现
 
 > 深度优先搜索：
 >
 >用时: $991ms$ / 内存: $8064KB$
 
 ```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;

const int Movex[] = {0, 0, 1, -1};//移动方向数组 
const int Movey[] = {1, -1, 0, 0};
const int N = 500 + 10;//地图大小 
char Map[N][N];//存地图 
bool vis[N][N];//是否已经经过，避免死循环 
int n, m, sx, sy, ex, ey;
//n 和 m 是地图大小 sx和sy记录起点坐标 ex和ey记录终点坐标

inline void dfs(int x, int y) {//深搜核心代码 
	vis[x][y] = true;//标记已经访问过
	int prex, prey, i;
	for(i = 0 ; i < 4; i++) {//向4个方向拓展
		prex = x + Movex[i];
		prey = y + Movey[i];
		if(x == 0 || x > n || y == 0 || y > m) {//超出边界
			continue;//不能走
		}
		if(!vis[prex][prey] && Map[prex][prey] != '#') {
			//没有被访问且不是墙 
			dfs(prex, prey);//深搜
		}
	}
}

int main() {
	int i, j, k;
	cin >> n >> m;
	memset(vis, false, sizeof(vis));//初始化 
	for(i = 1; i <= n ; i++) 
	  for(j = 1; j <= m; j++) {
	  	cin >> Map[i][j];//读入地图 
		if(Map[i][j] == 's') {//如果是起点 
			sx = i;//记录起点 
			sy = j;
		}
		if(Map[i][j] == 'g') {//如果是终点 
			ex = i;//记录终点 
			ey = j;
		}
	}
	dfs(sx, sy);
	if(vis[ex][ey]) {//能到达终点
		cout << "Yes" << endl;
		return 0;
	}
	cout << "No" << endl;//不能到达终点
	return 0;
}
```
 

---

## 作者：judgejudge (赞：6)

# 深度优先搜索+奇怪的记忆化！！！
首先这道题肯定是利用搜索，那么我们怎样分析思路呢？？

**我们只要查找到不是#，就默认可以走到这里，该位置记为1，反之记为0.**

之后由于是按四个方向都可以走，就搜索四个方向。如果找到终点，就可以输出Yes。

下面说一下算法：
1. 我们先找到起始位置，从起始位置开始搜索。
1. 进入子函数，位置行记为row,列记为col。
1. 如果row和col都没有超出范围，并且可以走到这里且**未赋值**，赋值，搜索其上下左右

**我们之所以赋值，是因为这样可以用一点记忆化，没有必要重复搜索，耗费时间。**

下面奉上AC代码：
```cpp
#include <iostream>
using namespace std;
char c[10001][10001];
int f[10001][10001];
int n,m,l;
int dp(int row,int col){
	int i,j;
	if(row>0&&row<=n&&col>0&&col<=m){//如果没有超出范围
		if(c[row][col]!='#'&&f[row][col]==0){//认为可以到达并且没有记录
			f[row][col]=1;//记录
			if(c[row][col]=='g')l=1;//如果到达终点，认为输出Yes
			dp(row-1,col);
			dp(row+1,col);
			dp(row,col-1);
			dp(row,col+1);//搜索四个方向，其实找到终点完全可以跳出循环，这个留给没事的大佬去优化吧
		}
	}
	return f[row][col];
}
int main(){
	int i,j,k;
	int row,col;
	cin>>n>>m;
	for(i=1;i<=n;i++)
	for(j=1;j<=m;j++){
	    cin>>c[i][j];
	    if(c[i][j]=='s')row=i,col=j;//记录初始位置行和列
	}
	dp(row,col);//开始搜索
	if(l==1)cout<<"Yes"<<endl;
	else cout<<"No"<<endl;//判断是否查找到终点
	return 0;
}
```


---

## 作者：zztqwq (赞：5)

[题目链接](https://www.luogu.org/problem/AT1350)

看到各位大佬都用的dfs，于是本蒟蒻给各位广搜党献上一篇~~自我感觉良好的~~bfs题解~（码风清奇，请勿嫌弃）

[不懂广搜的请点这里~](https://baike.baidu.com/item/%E5%AE%BD%E5%BA%A6%E4%BC%98%E5%85%88%E6%90%9C%E7%B4%A2?fromtitle=%E5%B9%BF%E5%BA%A6%E4%BC%98%E5%85%88%E6%90%9C%E7%B4%A2&fromid=2148012)

code:

```cpp
#include<iostream>
#include<queue>//c++STL库里面的队列
using namespace std;
struct note
{
    int x,y;
    note(int a,int b)
    {
    	x=a;
    	y=b;
	}//构造函数 
};//定义一个储存坐标的结构体
int main()
{
    int i,j,n,m,book[505][505],a[505][505],startx,starty,p,q;//book数组用来记录坐标(i,j)有没有走过
    char x;
    queue<note> que;
    cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            cin>>x;
            if(x=='s') {startx=i;starty=j;a[i][j]=1;}
            else if(x=='g') {p=i;q=j;a[i][j]=1;}
            else if(x=='.') a[i][j]=1;
            else a[i][j]=0;
        }//如果坐标(i,j)可以走,则在数组a中储存为1,否则储存为0
    }
    book[startx][starty]=1;
    que.push(note(startx,starty));
    int k,next[4][2]={{0,1},{1,0},{0,-1},{-1,0}},tx,ty;//定义一个方向数组next
    bool flag=false;//定义一个bool类型的变量flag,如果到达了终点flag的值为true,否则为false
    while(!que.empty())//在队列不为空的时候循环
    {
        for(k=0;k<4;k++)
        {
            tx=que.front().x+next[k][0];
            ty=que.front().y+next[k][1];
            if(tx<1||tx>n||ty<1||ty>m) continue;//如果越界则跳过本次循环
            if(book[tx][ty]==0&&a[tx][ty]) {que.push(note(tx,ty));book[tx][ty]=1;}//如果可以走则将坐标(i,j)入队
            if(que.back().x==p&&que.back().y==q) {flag=true;break;}//如果到达终点则跳出循环
        }
        if(flag) break;
        que.pop(); //注意!!必须要que.pop()才能继续下一个点的扩展!!
    }
    if(flag) cout<<"Yes\n";
    else cout<<"No\n";
    return 0;//华华丽丽的结束
}
```

---

## 作者：Sea_Level (赞：3)

这题是一个很好的深搜练手题，个人认为也就是橙题吧。下面上思路：

### 思路：

把整个小区的地图存进一个字符数组里，再搜索能不能到达鱼店。

对搜索到的任意点a：

- a为‘#’，直接return掉；

- a为‘g’，将f（f为判断是否能到达鱼店的变量）赋值为1，return；

- a为‘.’，判断a的上下左右的店是否为‘.’或'g'，是则继续搜索，否则return;

上代码！

```cpp
#include<iostream>
using namespace std;
int n,m,dx[4]={1,-1,0,0},dy[4]={0,0,1,-1},ci=0,cj=0,jl[510][510],f=0;//dx和dy是用来辅助判断点的上下左右是否为‘.’或'g'，ci和cj记录点‘s’的位置，jl用于判断点的上下左右是否走过，f为帮助判断是否到能达鱼店的变量。
char s[510][510];
void dfs(int x,int y){//深搜函数
	if(s[x][y]=='g'){//如果到鱼店了
		f=1;
		return ;//不用再搜了
	}
	for(int i=0;i<4;i++){
		int xx=x+dx[i];
		int yy=y+dy[i];//搜索四个方向
		if(xx>0&&yy>0&&xx<=n&&yy<=m&&jl[xx][yy]==0&&(s[xx][yy]=='.'||s[xx][yy]=='g')){//是否越界和有没有走过和是否不是
			jl[xx][yy]=1;//让这个点变成走过的
			dfs(xx,yy);
            //此处不能状态回归！如果回归会TLE。因为如果之前到过这里那么就一定已经搜完了这个点的所有路径。如果回归就会多算很多次。我就是因为这个TLE了一次。
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>s[i][j];
			if(s[i][j]=='s'){//找点‘s’
				ci=i;
				cj=j;//记录它的位置
			}
		}
	}
	dfs(ci,cj);//搜索
	if(f==1){//如果可以到达鱼店
		cout<<"Yes"<<endl;
	}else{
		cout<<"No"<<endl;
	}
	return 0;//拜拜！
}
```


---

## 作者：时律 (赞：3)

既然这题那么水，那么为什么不建个图玩玩呢？

如果一个地方是点，那么就把它和上下左右四个不是墙的地方连起来。

接着就来一遍快乐深搜~~果然最后还是要用DFS~~判断起点和终点是否连起来即可

```
//自信建图！ 
#include<bits/stdc++.h>
using namespace std;
int x[300000][10];
int z[300000],h[300000];
char y[600][600];
int a,b,c,d,e,f;
void dfs(int s)
{
	if(s==e)
	{
		printf("Yes");
		exit(0);//直接退出程序
	}
	for(int i=1;i<=z[s];i++)
		if(h[x[s][i]]==0)
		{
			h[x[s][i]]=1;
			dfs(x[s][i]);
		}
	return;
}
int main()
{
	scanf("%d%d",&a,&b);
	for(int i=1;i<=a;i++)
		for(int j=1;j<=b;j++)
		{
			cin>>y[i][j];
			if(y[i][j]=='s') c=i,d=j,y[i][j]='.';
			if(y[i][j]=='g') e=i,f=j,y[i][j]='.';
		}
	e=(e-1)*b+f;
	for(int i=1;i<=a;i++)
		for(int j=1;j<=b;j++)
			if(y[i][j]=='.')
			{
				int u=(i-1)*b+j;//因为250的四次方会炸，所以就改用另一种方法
				if(i!=1 and y[i-1][j]=='.')//如果能联通那就把这个地方加在后面
					x[u][++z[u]]=u-b;
				if(i!=a and y[i+1][j]=='.')
					x[u][++z[u]]=u+b;
				if(j!=1 and y[i][j-1]=='.')
					x[u][++z[u]]=u-1;
				if(j!=b and y[i][j+1]=='.')
					x[u][++z[u]]=u+1;
			}
	h[(c-1)*b+d]=1;//哈希表先预先把起点设为已走过
	dfs((c-1)*b+d);//从起点开始搜
	printf("No");
}
```

~~一直在RE和WA，数组开小三次ab写错两次~~

~~我果然太菜了，连普通图都不会打，只好打个奇奇怪怪的东西维持生活~~

---

## 作者：beargeng是女孩子 (赞：3)

Code:
(注释见代码QAQ)
```
#include<bits/stdc++.h>
using namespace std;
int h,w;
char maze[500][500];
bool vis[500][500];
bool safe(int x,int y)//判断DFS到的位置是否在地图里面
{
	if(x<0||x>=h||y<0||y>=w) 
	return false;
	return true;
} 
void dfs(int x,int y)
{
    if(safe(x,y)==false)//在地图外,返回
        return;
    if(maze[x][y]=='#')//碰到墙了,返回
        return;
    if(vis[x][y])//这个点被走过了,返回
        return;
    vis[x][y]=true;//把vis置为true,表示走过
    dfs(x+1,y);
    dfs(x-1,y);
    dfs(x,y+1);
    dfs(x,y-1);
} 
int main()
{
    cin>>h>>w;
    int start_x,start_y,to_x,to_y;
    for(int i=0;i<h;i++) 
    {
        for(int j=0;j<w;j++) 
        {
            cin>>maze[i][j];
            if(maze[i][j]=='s')//人在这里,设置坐标
            {
                start_x=i;
                start_y=j;
            }
            if(maze[i][j]=='g')//终点在这里,设置坐标
            {
                to_x=i;
                to_y=j;
            }
        }
    }
    dfs(start_x,start_y);
    if(vis[to_x][to_y]) 
        cout<<"Yes"<<endl;
    else 
     cout<<"No"<<endl;
    return 0;
}
```


---

## 作者：lzxhdxx (赞：2)

# 题解AT1350 深さ優先探索

~~好像没有特别详细的bfs题解耶~~

### 题意简述 

输入一幅图，'s'为起点，'g'为终点，'.'为可以走的空地，'#'为障碍物，判断是否可以从起点到达终点，如果可以，输出Yes，否则输出No

### 思路：

分析题目，易得本题需要搜索算法。看到数据规模：n,m<500，我们确定应该需要广搜（根据之前巨魔写的题解，深搜也可以），确定了算法，我们来想搜索策略

bfs策略：我们从起点开始，不断向四周扩展不是'#'的新状态，到达终点就输出Yes，否则输出No

## 注意：
难道这样就行了吗？肯定不是的。

残忍的TLE告诉我们，此题必须剪枝！但是怎样剪枝呢？

很容易发现，我们每一步经过的点不需要再次经过（不然不就原地打转了吗），所以，我们加入vis数组来记录每个点是否经过过，经过了就不需要再来一次了

Code：

```cpp
#include <iostream>
#include <queue>

using namespace std;

int n, m, xs, ys, xe, ye, dx[5] = { 0,-1,1,0,0 }, dy[5] = { 0,0,0,-1,1 };//上下左右移动用dx,dy最好
char map[510][510];//地图
bool vis[510][510] = { false };//剪枝，当前点如果走过，那就不需要再走了，用vis数组记录当前点是否走过

bool bfs()//宽搜
{
	queue<pair<int, int> >Q;//宽搜用队列实现
	Q.push(make_pair(xs, ys));//压入出发点
	while (!Q.empty())//队列空代表已经扩展不出点了，可以退出
	{
		int nowx = Q.front().first, nowy = Q.front().second;//现在到达的点
		if (nowx == xe && nowy == ye) return true;//如果现在到达的点就是终点，返回true（代表可以到达）
		for (int i = 1; i <= 4; i++)
		{
			int newx = nowx + dx[i], newy = nowy + dy[i];//现在的x,y坐标分别加上dx[i],dy[i]，扩展出下一步的x,y坐标
			if (newx >= 1 && newy >= 1 && newx <= n && newy <= m && !vis[newx][newy] && map[newx][newy] != '#')//如果不越界且没有走过且不是障碍物，就可以走
			{
				Q.push(make_pair(newx, newy));//压入下一步的x,y坐标
				vis[newx][newy] = true;//标记新的点已经拓展过
			}
		}
		Q.pop();//把已经处理完的现在到达的点弹掉
	}
	return false;//如果到了最后还没有到达终点（即代码17行return true;），那就肯定是到不了，return false（代表不能到达终点）
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)//常规输入
		for (int j = 1; j <= m; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 's') xs = i, ys = j, vis[i][j] = true;//判断起点，起点可以直接设置成走过
			if (map[i][j] == 'g') xe = i, ye = j;//判断终点
		}
	if (bfs()) cout << "Yes" << endl;//如果能到达（true），输出Yes，否则输出No
	else cout << "No" << endl;
	return 0;
}
```
减少复制代码，创建美好洛谷！

感谢大家观看！求管理大大给过

---

## 作者：first_fan (赞：1)

##  本题的标题翻译过来就是
# 深度优先搜索(DFS)
### 这道题确实是一个锻炼dfs码力的极好模板
# 
# 废话不多说，上思路！
# 定义部分
```
#include<bits/stdc++.h>
using namespace std;
bool vis[510][510],flag=false;
char sub[510][510];
int fish[2],home[2];
int direx[]={1,0,-1,0};
int direy[]={0,1,0,-1};
int height,width;
int edx,edy,stx,sty;
```
# 
### vis用于回溯封路,flag则是判断能不能到达鱼店;
### 至于sub的功能就是表示出街区(suburb);
### 鱼店和家的坐标的记录本人比较清奇,用数组表示；
### direx和direy就是→↑←↓四个方向走的坐标偏移量；
### 最后定义的是地图尺寸，起始和结束坐标记录；
# 
# dfs部分
```
void dfs(int x,int y)
{
	vis[x][y]=true;
	if(x==edx&&y==edy)
	{
		flag=true;
		return;
	}
	for(int i=0;i<4;i++)
	{
		int x_now=x+direx[i];
		int y_now=y+direy[i];
		if(x_now>0&&y_now>0&&x_now<=height&&y_now<=width&&!vis[x_now][y_now]&&sub[x_now][y_now]=='.')
		{
			dfs(x_now,y_now);
		}
	}
	vis[x][y]=false;
}
```
# 
### 首先判断在此次深搜开始时是否到终点并记录情况；
### 然后再向四个方向搜索
##
## 划重点！！是否能走的判断:
### 1.将要搜索的目的地不会超出地图；
### 2.将要搜索的目的地没有被打标记；
### 3.这是一条路，不是一堵墙；
### 
### ~~没错！就只有这点判断标准！~~
#   _**不要忘了！！如果目的地走不通，要把来时的路的标记给删了！！不然没法掉头！！**_ 

# 下面进入主函数：
```
int main()
{
	cin>>height>>width;
	for(int i=1;i<=height;i++)
	{
		for(int j=1;j<=width;j++)
		{
			cin>>sub[i][j];
			if(sub[i][j]=='g')
			{
				edy=i;
				edx=j;
			}
			if(sub[i][j]=='s')
			{
				sty=i;
				stx=j;
			}
		}
	}
	dfs(stx,sty);
	if(flag)
	{
		cout<<"Yes";
	}
	else
	{
		cout<<"No";
	}
}
```
### 接下来的操作就相当简单了，按照题目说的做就行了
# 放下个人的代码
```
#include<bits/stdc++.h>
using namespace std;
bool vis[510][510],flag=false;
char sub[510][510];
int fish[2],home[2];
int direx[]={1,0,-1,0};
int direy[]={0,1,0,-1};
int height,width;
int edx,edy,stx,sty;
void dfs(int x,int y)
{
	vis[x][y]=true;
	if(x==edx&&y==edy)
	{
		flag=true;
		return;
	}
	for(int i=0;i<4;i++)
	{
		int x_now=x+direx[i];
		int y_now=y+direy[i];
		if(x_now>0&&y_now>0&&x_now<=height&&y_now<=width&&!vis[x_now][y_now]&&sub[x_now][y_now]=='.')
		{
			dfs(x_now,y_now);
		}
	}
	vis[x][y]=false;
}
int main()
{
	cin>>height>>width;
	for(int i=1;i<=height;i++)
	{
		for(int j=1;j<=width;j++)
		{
			cin>>sub[i][j];
			if(sub[i][j]=='g')
			{
				edy=i;
				edx=j;
			}
			if(sub[i][j]=='s')
			{
				sty=i;
				stx=j;
			}
		}
	}
	dfs(stx,sty);
	if(flag)
	{
		cout<<"Yes";
	}
	else
	{
		cout<<"No";
	}
}
```
# 不过！
# 这个代码会爆WA和TLE！
# 望巨佬斧正(剪枝也不能AC！)

---

## 作者：傅思维666 (赞：0)


## 题解：

应该算是深搜的常用应用——**地图遍历**的模板题。

地图遍历是本蒟蒻自己起的名字。代表一类比较常见的题目，类似于走迷宫，是对矩阵的一种遍历方式。这种题型基本就是使用搜索（深搜和广搜只是实现方式不一样，最终达到的目的是一样的）来解决。那么这篇题解就细致地讲一下做这种题的思路和深搜的基本实现方式。

首先深搜的定义大家应该都有所了解。但是这种定义方式是基于**树和图的深度优先遍历**的，比较容易被大家理解。所以应该有好多小伙伴都是像本蒟蒻一样蒙圈：这种题无图无树，和深搜有关系么？

这就需要一个思维转换：**构建搜索树**。

所谓搜索树，就是把乍一看没法用深搜解决的问题抽象成一棵树，不是说深搜是对树和图的深度优先遍历么？那我把这个问题变成一个图，不就解决了么？

那好，我们开始抽象：

一张地图，对于每一个点（就是矩阵的每一个坐标），它有四个选择可走：上下左右。那么，我们可以将其抽象成一个每个节点有四个子节点的图。（当然，边界节点和墙都是除外的）

有了这个思路，就可以进行深搜了。

思路如下：输入矩阵，标记起始点。

从起点开始深搜，利用方向数组和判断，搜索整个图，在可到达点打上标记。

如果终点带标记，就输出是，否则就是否。

满分代码：（一个不大不小的细节：注意字符的读入，这里用的是cin，用scanf不一定读得进来）

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int maxn=510;
int n,m;
char map[maxn][maxn];
bool v[maxn][maxn];
int dx[]={0,0,0,-1,1};
int dy[]={0,1,-1,0,0};
int a,b,c,d;
void dfs(int x,int y)
{
	v[x][y]=1;
	for(int i=1;i<=4;i++)
	{
		int xx=x+dx[i];
		int yy=y+dy[i];
		if(xx<1 || xx>n || yy<1 || yy>m || map[xx][yy]=='#' || v[xx][yy])
			continue;
		dfs(xx,yy);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>map[i][j];
			if(map[i][j]=='s')
				a=i,b=j;
			if(map[i][j]=='g')
				c=i,d=j;
		}
	dfs(a,b);
	if(v[c][d])
	{
		printf("Yes");
		return 0;
	}
	else
	{
		printf("No");
		return 0;
	}
}
```


---

## 作者：xiaohuang (赞：0)

[更好的阅读体验](https://xiaohuang888.github.io/2019/08/06/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8FAT1350%20%E6%B7%B1%E3%81%95%E5%84%AA%E5%85%88%E6%8E%A2%E7%B4%A2)

### Description in Chinese

高桥先生住的小区是长方形的，被划分成一个个格子。高桥先生想从家里去鱼店，高桥先生每次可以走到他上下左右四个格子中的其中一个，不能斜着走，也不能走出小区或穿墙。

地图语言解释：

- `s`：表示高桥先生的家（起始点）

- `g`：表示鱼店（终点）

- `.`：表示道路

- `#`：表示墙壁

### Solution

我们不妨采用深度优先搜索，先在地图上找出起始点，然后用灌水法（将起始点能到达的地方标记），我是直接修改地图的，最后再扫描一边地图，看看终点还在不在，如果在就表示还没标记过，也就是走不到，输出`No`，如果终点不存在，也就是被标记了，就说明可以到达，输出`Yes`。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

const int MAXN = 505;
int n, m, stx, sty;
char map[MAXN][MAXN];
inline void dfs(int x, int y) {
    if (x < 1 || y < 1 || x > n || y > m) return ;//如果超越了边界
    if (map[x + 1][y] != '#' && map[x + 1][y] != '!') {//向右
        map[x + 1][y] = '!';
        dfs(x + 1, y);
    }
    if (map[x][y + 1] != '#' && map[x][y + 1] != '!') {//向下
        map[x][y + 1] = '!';
        dfs(x, y + 1);
    }
    if (map[x - 1][y] != '#' && map[x - 1][y] != '!') {//向左
        map[x - 1][y] = '!';
        dfs(x - 1, y);
    }
    if (map[x][y - 1] != '#' && map[x][y - 1] != '!') {//向上
        map[x][y - 1] = '!';
        dfs(x, y - 1);
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> map[i][j];
            if (map[i][j] == 's') {
                stx = i; sty = j;//找出起始点并标记
            }
        }
    dfs(stx, sty);
    bool flag = 1;
    for (int i = 1; i <= n; i++) {//寻找终点有没有被标记过
        for (int j = 1; j <= m; j++)
            if (map[i][j] == 'g') {
                flag = 0;
                break;
            }
        if (!flag) break;
    }
    if (flag) printf("Yes\n"); else printf("No\n"); 
    return 0;
}
```

---

## 作者：Blue_Floyd (赞：0)

~~这题就是一个深度优先搜索。。。~~

**但是注意一个优化:不用回溯vis数组,因为经过此格的路线一定不可能走到目的地了！！！**

放下代码：
```cpp
#include<iostream>
using namespace std;
int x2,y2,x,y,n,m;
//这里的vis,map建议开成505,防止奇奇怪怪的溢出问题
bool vis[505][505];
char map[505][505];
int dx[10]= {0,1,-1,0,0},dy[10]= {0,0,0,1,-1}; //方向数组,用来描述高桥先生走后的位置
bool dfs(int nowx,int nowy) {
	if(nowx==x2&&nowy==y2) {
		//走到目的地---鱼店,结束搜索并返回结果（能走到鱼店所以结果为true）
		return true;
	}
	for(int i=1; i<=4; i++) { //循环4次来枚举上下左右移动
		int fx=nowx+dx[i];
		int fy=nowy+dy[i];//计算出高桥先生走后的位置
		if(fx<=n&&fx>=1&&fy<=m&&fy>=1&&map[fx][fy]!='#'&&!vis[fx][fy]) { //判断是否走出小区和走到的是否是墙墙和是否走过 
		    vis[fx][fy]=true;//vis用于判断这个格子是否被走过,不然会 (1,2)->(2,1)->(1,2)->(2,1)...然后陷入死递归 
			if(dfs(fx,fy)) {
				//开始走并判断如果可以走到,那么也返回结果为true
				//相当于当前位置可以走到就返回给上一位置,让它也知道它能走到,这样一层层返回至最开始的一层的算法就叫做回溯
				return true;
			}
			vis[fx][fy]=false;//回溯,令下一条路线可经过此格 
			//注释掉上面的语句可以优化(其实并不用令下一条路线能经过,因为经过此格的路线一定不可能走到目的地了),不然会TLE 
		}
	}
	return false;//无论如何都走不到目的地,返回false
}
int main() {
	cin>>n>>m;
	//找到起点和终点
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			cin>>map[i][j];
			//map记录地图
			if(map[i][j]=='s') {
				x=i;
				y=j;
			}
			if(map[i][j]=='g') {
				x2=i;
				y2=j;
			}
		}
	//开始dfs搜索，初始值设置为起点
	//如果dfs最终返回为true,则输出Yes,否则输出No
	vis[x][y]=true;//标记起点 
	if(dfs(x,y)==true)cout<<"Yes";
	else cout<<"No";
	return 0-0;
	//就这么愉快的A掉了本题~~
}
```

---

