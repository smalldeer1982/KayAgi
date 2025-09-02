# [USACO11NOV] Cow Beauty Pageant S

## 题目描述

听说最近流行表皮有三个斑点的奶牛，Farmer John 迅速购买了不少这样的奶牛。但流行趋势也在改变，最近改为流行只有一个斑点的奶牛了。

FJ 决定在他的奶牛上涂色，从而把三个斑点合并成一个。牛皮由一个 $N \times M$ 的矩阵来表示，像这样：

```plain
................
..XXXX....XXX...
...XXXX....XX...
.XXXX......XXX..
........XXXXX...
..XXX....XXX....
```

每个 `X` 表示斑点的一部分。如果两个 `X` 在竖直或水平方向上相邻，则它们属于同一个斑点（对角线相邻不算）。因此上面表示的是一头具有三个斑点的奶牛。

FJ 可以通过将一些 `.` 涂成 `X` 来改变牛身上的图案。他希望使用尽可能少的涂料将三个斑点合并为一个斑点。对于上图，下面是一种消耗涂料最少的方案（只涂了 4 个格子，新涂的格将用 `*` 表示）：

```plain
................
..XXXX....XXX...
...XXXX*...XX...
.XXXX..**..XXX..
...*....XXXXX...
..XXX....XXX....
```

现在请你帮 FJ 算出将三个斑点合并为一个斑点最少需要涂多少格子。

## 样例 #1

### 输入

```
6 16
................
..XXXX....XXX...
...XXXX....XX...
.XXXX......XXX..
........XXXXX...
..XXX....XXX....```

### 输出

```
4```

# 题解

## 作者：qzhwlzy (赞：22)

### [传送#1](https://www.luogu.com.cn/problem/P2124)  
### [传送#2](https://www.luogu.com.cn/problem/P6131)
## 思路
解题过程主要可以分为2步：  
1. 读入，**将三个斑点依次编号**为1,2,3，方法有很多，如 $dfs$ 或 $bfs$ ，这里不细讲了。
![](https://cdn.luogu.com.cn/upload/image_hosting/mpxro6hg.png)
2. 关键步骤，我们知道，对于任意两个斑点，无非只有上图所示的两种情况，因此，我们需要分别计算两种情况改变的最小格子数（以下称为距离）。  
* 第一种，**将两个斑点连通至第三个斑点**，需要我们分别记录**每两个斑点之间的距离**，一共就**三种**情况。  
* 第二种，**将三个斑点连至一个不在斑点上的点**，我们就可以循环每一个不在斑点上的点，计算距离并求最小值。

## 计算过程
**依次循环每一个点**，如果是‘ $X$ ’，那么进行第一种操作；若为‘ $.$ ’，则进行第二种操作。
## 具体函数实现
* 曼哈顿距离  
	>曼哈顿距离(Manhattan distance or Manhattan length)或方格线距离是由十九世纪的赫尔曼·闵可夫斯基所创辞汇，为欧几里得几何度量空间的几何学之用语，用以标明两个点上在标准坐标系上的**绝对轴距之总和**。  
    由以上 $bdfs$ 的结果我们可以知道，本题显然要用曼哈顿距离函数，此函数实现并不难，就是两点的横纵坐标差值和（我的C++出 $bug$ 了，不能用 $abs$ 函数，故代码中自己写了函数且没有单独定义曼哈顿距离函数）。
* 第一种操作  
	第一种操作我写得比较暴力，直接循环每个点，如果不是同斑点的话，直接求它们的曼哈顿距离。
   ```cpp
   for(int k=1;k<=n;k++){
		for(int l=1;l<=m;l++){
			if(a[k][l]==0){
				continue;
			}
			if(a[k][l]!=a[i][j]&&dis[a[i][j]][a[k][l]]>abss(i-k)+abss(j-l)){
				dis[a[k][l]][a[i][j]]=min(dis[a[k][l]][a[i][j]],abss(i-k)+abss(j-l));
			}
		}
	}
   ```
* 第二种操作  
	第二种操作我单独写了函数，直接曼哈顿求某个不在任一斑点上的点到三个斑点的曼哈顿距离，总和最小即可。
    ```cpp
    int xx[4];
	xx[1]=xx[2]=xx[3]=999999;
	for(int p=1;p<=n;p++){
		for(int q=1;q<=m;q++){
			if(x[p][q]=='X'){
				xx[a[p][q]]=min(xx[a[p][q]],abss(i-p)+abss(j-q)-1);
			}
		}
	}	
	return xx[1]+xx[2]+xx[3]+1;
    ```
综上，大家可以看出我的代码的**时间复杂度非常高**~~，但是能卡过~~，建议自己找简单解法。
## 完整代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 55
using namespace std;
int n,m;
char x[maxn][maxn];
int a[maxn][maxn]={};
bool vis[maxn][maxn];
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
int f[5][5],tot=0;
int dis[4][4],elseans=99999;
int abss(int a){
	if(a<0){
		return -a;
	}
	return a;
}
void dfsset(int xx,int yy,int num){//dfsset函数设定斑点编号
	for(int i=0;i<4;i++){
		xx+=dx[i];
		yy+=dy[i];
		if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&x[xx][yy]!='.'&&!vis[xx][yy]){
			vis[xx][yy]=1;
			a[xx][yy]=num;
			dfsset(xx,yy,num);
		}
		xx-=dx[i];
		yy-=dy[i];
	}
}
int trypoint(int i,int j){//第二种操作
	int xx[4];
	xx[1]=xx[2]=xx[3]=999999;
	for(int p=1;p<=n;p++){
		for(int q=1;q<=m;q++){
			if(x[p][q]=='X'){
				xx[a[p][q]]=min(xx[a[p][q]],abss(i-p)+abss(j-q)-1);
			}
		}
	}	
	return xx[1]+xx[2]+xx[3]+1;
}
int main(){
//	freopen("pageant.in","r",stdin);
//	freopen("pageant.out","w",stdout);
	scanf("%d%d\n",&n,&m);
	for(int i=1;i<=n;i++){//读入
		for(int j=1;j<=m;j++){
			if(j==m&&i!=n){
				scanf("%1c\n",&x[i][j]);
			}else{
				scanf("%1c",&x[i][j]);
			}
		}
	}
	int num=0;
	for(int i=1;i<=n;i++){//设定斑点编号
		for(int j=1;j<=m;j++){
			if(x[i][j]=='.'){
				continue;
			}
			if(vis[i][j]==0){
				num++;
				a[i][j]=num;
				dfsset(i,j,num);
			}
		}
	}
	
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=n;i++){//循环查找
		for(int j=1;j<=m;j++){
			if(x[i][j]=='X'){
				for(int k=1;k<=n;k++){//第一种操作
					for(int l=1;l<=m;l++){
						if(a[k][l]==0){
							continue;
						}
						if(a[k][l]!=a[i][j]&&dis[a[i][j]][a[k][l]]>abss(i-k)+abss(j-l)){
							dis[a[k][l]][a[i][j]]=min(dis[a[k][l]][a[i][j]],abss(i-k)+abss(j-l));
						}
					}
				}
			}else{
				elseans=min(elseans,trypoint(i,j));//第二种操作
			}
		}
	}
	int anss=elseans;
	for(int i=1;i<=3;i++){//值得一提的是，这里要把dis[1][2]和dis[2][1]合并一下，不然7个点会变红哦
		for(int j=i+1;j<=3;j++){
			if(dis[i][j]!=0){
				dis[i][j]=min(dis[j][i],dis[i][j]);
			}
		}
	}
	anss=min(anss,min(dis[1][2]+dis[2][3]-2,min(dis[1][2]+dis[1][3]-2,dis[1][3]+dis[2][3]-2)));
	printf("%d",anss);
	return 0;
}
```

###### ~~写题解不易，点赞再走吧~~

---

## 作者：wssdl (赞：7)

## 题目描述

给你一个 $N\times M$ 的字符矩阵，每个点可能是 $X$ 和 $.$ ，用 $X$ 组成的称为一个斑点，我称为连通块， $.$ 我称为空点，求把所有连通块连起来最少需要使用多少个空点，其中， $1\le N,M\le 50$ 。

## 思路

题目保证了只有 $3$ 个连通块，其实就是斑点啦，而且数据范围小得感人，于是考虑 **搜索** ，由于读入的连通块都是用 $X$ 表示的，不好区分，所以我们先使用 **dfs** 把连通块按顺序标号成 $1,2,3$ 其余的点标为 $0$ ，存入 $ans$ 数组中，读入的矩阵会变成这样：

```cpp
0000000000000000
0011110000222000
0001111000022000
0111100000022200
0000000022222000
0033300002220000
```

然后我们枚举每个连通块，把从这个连通块到另外两个连通块所要走的 $.$ 点的个数加起来，再取个最小值就是可能的一种答案了，为什么说是可能的一种答案呢，我们看看这两种连通方法：

![](https://cdn.luogu.com.cn/upload/image_hosting/azfoxwwj.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/20x180u1.png)

图中，黑色为路径，白色为空点，其他颜色为不同的连通块。

这就说明了有两种不同的走法，第一种在上面讲了，第二种我们只用枚举每个空点，然后把这个空点分别走到 $3$ 个连通块时所经过的空点加起来，再从中取个最小值就实现了第二种走法。

输出两种走法的最小值。

注：两种走法都用 **bfs** 实现。

## 代码（内有注释）

```cpp
#include <bits/stdc++.h>
using namespace std;
//变量含义
const int N = 55;
int n, m;                   //读入的矩阵
int cnt;                    //是第几个连通块
int minx1 = 1e9;            //第一种走法的最小值
int minx2 = 1e9;            //第二种走法的最小值
int len1, len2;             //使用于第一种走法，分别是a1,a2数组的长度
int a1[N * N * 2];          //从该连通块到另外一个连通块所经过的空点数量
int a2[N * N * 2];          //同上
int ans[N][N];              //化为数字后的读入矩阵
int dx[4] = {0, 1, 0, -1};  //四个方向
int dy[4] = {1, 0, -1, 0};
char a[N][N];    //读入矩阵
bool vis[N][N];  //广搜时不能重复走
//深搜
void dfs(int x, int y) {  //求连通块
  for (int i = 0; i <= 3; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !ans[nx][ny] && a[nx][ny] == 'X') {
      ans[nx][ny] = cnt;
      dfs(nx, ny);
    }
  }
}
//广搜
struct Node {
  int x, y, s;
};
//第一种走法，求到另外一个连通块所经过的空点数量，是个模板啦
int bfs(int x, int y, int s, int k, int l) {  //x,y表示当前的下标，s是空点数量，k是目标点，l是不能走到的点
  queue<Node> q;
  memset(vis, 0, sizeof(vis));
  Node cur = {x, y, s};
  q.push(cur);
  vis[x][y] = 1;
  while (!q.empty()) {
    Node cur = q.front();
    q.pop();
    if (ans[cur.x][cur.y] == k) {
      return cur.s;
    }
    for (int i = 0; i <= 3; i++) {
      int nx = cur.x + dx[i];
      int ny = cur.y + dy[i];
      if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && ans[nx][ny] != l && !vis[nx][ny]) {
        vis[nx][ny] = 1;
        Node ne = {nx, ny, cur.s + 1};
        q.push(ne);
      }
    }
  }
  return -1;  //走不到
}
//第二种走法，和第一种差不多
int Bfs(int x, int y, int s, int k) {  //可以把上面的l给缩掉
  queue<Node> q;
  memset(vis, 0, sizeof(vis));
  Node cur = {x, y, s};
  q.push(cur);
  vis[x][y] = 1;
  while (!q.empty()) {
    Node cur = q.front();
    q.pop();
    if (ans[cur.x][cur.y] == k) {
      return cur.s;
    }
    for (int i = 0; i <= 3; i++) {
      int nx = cur.x + dx[i];
      int ny = cur.y + dy[i];
      if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !vis[nx][ny] && (a[nx][ny] == '.' || ans[nx][ny] == k)) {
        vis[nx][ny] = 1;
        Node ne = {nx, ny, cur.s + 1};
        q.push(ne);
      }
    }
  }
  return -1;  //无解
}
int main() {
  //读入
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }
  //把矩阵转换为数字
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i][j] == 'X' && !ans[i][j]) {
        cnt++;
        ans[i][j] = cnt;
        dfs(i, j);
      }
    }
  }
  //第一种走法
  for (int k = 1; k <= 3; k++) {  //只有3个连通块
    len1 = 0, len2 = 0;           //记得初始化
    memset(a1, 0, sizeof(a1));
    memset(a2, 0, sizeof(a2));
    //其余的两个连通块的值
    int k1, k2;
    if (k == 1) {
      k1 = 2, k2 = 3;
    } else if (k == 2) {
      k1 = 1, k2 = 3;
    } else {
      k1 = 1, k2 = 2;
    }
    //枚举改连通块里的每个点
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (ans[i][j] == k) {
          int tmp1 = bfs(i, j, 0, k1, k);  //到另一个连通块所经过的空点数量
          int tmp2 = bfs(i, j, 0, k2, k);  //同上
          if (tmp1 != -1) {                //必须有解
            a1[++len1] = tmp1 - 1;         //因为另外那个连通块的边界点会算上去，所以要减去
          }
          if (tmp2 != -1) {  //同上
            a2[++len2] = tmp2 - 1;
          }
        }
      }
    }
    //取最小值
    for (int i = 1; i <= len1; i++) {
      for (int j = 1; j <= len2; j++) {
        minx1 = min(minx1, a1[i] + a2[j]);  //要搭配找
      }
    }
  }
  //第二种走法
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i][j] != '#') {  //枚举空点
        int ans1, ans2, ans3;
        ans1 = Bfs(i, j, 0, 1);  //分别到3个连通块所经过的空点数量
        ans2 = Bfs(i, j, 0, 2);
        ans3 = Bfs(i, j, 0, 3);
        if (ans1 != -1 && ans2 != -1 && ans3 != -1) {      //必须都能走到
          minx2 = min(minx2, ans1 + ans2 + ans3 - 3 + 1);  //因为连通块的边界点会算上去，所以要减去，也要把枚举到的空点加上
        }
      }
    }
  }
  //输出
  cout << min(minx1, minx2);  //两种走法取最小
  return 0;
}
//用到了深搜广搜，这题还是很难的QWQ
//虽然很长，但第二个广搜是复制的QWQ
```


不懂得私信问我吧。

码字不易，希望审核通过 QWQ 。

---

## 作者：KK_lang (赞：3)

## 题目理解

有三个连通块，求最小改变多少个格子才能使得它们变成一个连通块。

~~简短吧！~~

## 思路指引

看到这道题，一下就瞄到了“连通块”三字，于是 ~~我高兴的手舞足蹈~~ 一下子就想到了“灌水法”。 ~~（不是灌水的那个灌水）~~

### 灌水部分程序

灌水，无非就是把一个连通块的所有格标记一下，以区分各个连通块与非连通块。

```cpp
void dfs(int x, int y)
{
	if (x > n || x < 1 || y > m || y < 1) return;
	if (s[x][y] == '.') return;
	if (id[x][y] > 0) return;
	id[x][y] = col;  // col 为当前连通块的编号，在主函数中有更新
	dfs(x + 1, y);
	dfs(x, y + 1);
	dfs(x - 1, y);
	dfs(x, y - 1);
}

```

然后呢，再看数据范围，嚯！$N$ 和 $M$ 最高才为 $50$！ ~~令人振奋啊！~~

在此提醒各位，数据范围是思路确定的法宝，例如：$N$ 为 $20$ 一般可以用状态压缩动规等等。

大胆分析一下，上限 $50$ 的话最高可以到四次方，再加上这是二维问题，就可以联想到暴搜任两个点的下标。

到这里，基本已经确定思路了——灌水+暴搜+模拟。

灌水前文已经说过了，现在说说模拟是怎么个模拟法。

### 暴搜+模拟部分程序：

模拟可以分以下类：

第一类：两个点处在不同的连通块。这时我设了一个数组 $dis$，$dis_{i, j}$ 表示 $i$ 号连通块到 $j$ 号连通块的最近曼哈顿距离。

第二类：两个点一个在连通块，一个是非连通块点。此时设一个数组 $disP$，$disP_{i,x,y}$ 表示 $i$ 号连通块到（$x$，$y$）点的最近曼哈顿距离。

因此，我们可以推测出，答案有两种情况：

1、另两个连通块连另一个连通块。

```cpp
XXXX.....X
XXXXX***XX
X.......XX
*.....XXXX
XXX......X
XXXX......
```
2、三个连通块共同连一个非连通块点。

```cpp
XX...XX
XXX*XXX
...X...
XXXXXXX
```
所以暴搜模拟部分程序如下：（利用 $dis$ 与 $disP$ 数组记录当前距离，最后取最小值就行了）

```cpp
for (int i = 1; i <= n; i++)
	for (int j = 1; j <= m; j++)
		for (int x = 1; x <= n; x++)
			for (int y = 1; y <= m; y++)
			{
				if (id[i][j] > 0 && id[x][y] > 0 && id[i][j] != id[x][y])
					dis[id[i][j]][id[x][y]] = min(dis[id[i][j]][id[x][y]], abs(i - x) + abs(j - y));
				else if (id[i][j] == 0 && id[x][y] > 0)
					disP[id[x][y]][i][j] = min(disP[id[x][y]][i][j], abs(i - x) + abs(j - y));
				else continue;
			}
```

### 输出答案

答案可以有四种形式：$1$、$2$ 号连通块连 $3$ 号连通块；$1$、$3$ 号连通块连 $2$ 号连通块；$2$、$3$ 号连通块连 $1$ 号连通块；$1$、$2$、$3$ 号连通块连其它非连通块点

```cpp
int ans = min(dis[2][3] + dis[1][3], min(dis[1][2] + dis[1][3], dis[1][2] + dis[2][3])) - 2;
for (int i = 1; i <= n; i++)
	for (int j = 1; j <= m; j++)
		if (id[i][j] == 0)
			ans = min(ans, disP[1][i][j] + disP[2][i][j] + disP[3][i][j] - 2);
cout << ans << endl;
```

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int col = 0;
int n, m;
string s[55];
int id[55][55];
int dis[5][5];
int disP[5][55][55];

void dfs(int x, int y)
{
	if (x > n || x < 1 || y > m || y < 1) return;
	if (s[x][y] == '.') return;
	if (id[x][y] > 0) return;
	id[x][y] = col;
	dfs(x + 1, y);
	dfs(x, y + 1);
	dfs(x - 1, y);
	dfs(x, y - 1);
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> s[i];
		s[i] = " " + s[i];
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (id[i][j] == 0 && s[i][j] == 'X')
			{
				col++;
				dfs(i, j);
			}
	memset(dis, 999999, sizeof(dis));
	memset(disP, 999999, sizeof(disP));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int x = 1; x <= n; x++)
				for (int y = 1; y <= m; y++)
				{
					if (id[i][j] > 0 && id[x][y] > 0 && id[i][j] != id[x][y])
						dis[id[i][j]][id[x][y]] = min(dis[id[i][j]][id[x][y]], abs(i - x) + abs(j - y));
					else if (id[i][j] == 0 && id[x][y] > 0)
						disP[id[x][y]][i][j] = min(disP[id[x][y]][i][j], abs(i - x) + abs(j - y));
					else continue;
				}
	int ans = min(dis[2][3] + dis[1][3], min(dis[1][2] + dis[1][3], dis[1][2] + dis[2][3])) - 2;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (id[i][j] == 0)
				ans = min(ans, disP[1][i][j] + disP[2][i][j] + disP[3][i][j] - 2);
	cout << ans << endl;
	return 0;
}
```

## 后记


#### 生活中不缺能发的题解，只缺发现题的眼睛

---

## 作者：Engulf (赞：2)

题意：求将三个连通分量连成一个的最少步数。

首先先 bfs 求出三个连通分量，然后就是连接了。

连接这里非常坑，因为有两种情况：

1. 直接选其中的两个连接；
2. 选择一个点 $(x,y)$，三个连通分量都连到 $(x,y)$。

对于第 1 种情况，显然把连通分量缩点，再求个最小生成树即可。

第 2 种情况就直接暴力枚举 $(x,y)$ 计算代价。

坑点很多（特别是我很难想到情况 2）。

```cpp
// author: TMJYH09
// create time: 2022/05/14 22:11:06
#include <bits/stdc++.h>
using namespace std;

int n,m;
char a[55][55];

vector <pair<int,int>>scc[55];
int dfn;

void bfs(int x,int y){
    queue <pair<int,int>> q;
    ++dfn;scc[dfn].push_back({x,y});
    a[x][y]='.';q.push({x,y});
    int dir[][2]={1,0,0,1,-1,0,0,-1};
    while(!q.empty()){
        pair<int,int>f=q.front();q.pop();
        for(int i=0;i<4;i++){
            int nx=f.first+dir[i][0];
            int ny=f.second+dir[i][1];
            if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&a[nx][ny]=='X'){
                a[nx][ny]='.';q.push({nx,ny});
                scc[dfn].push_back({nx,ny});
            }
        }
    }
}

struct edge{
    int u,v,w;
}e[1005];
int cnt;
int fa[1005];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(a[i][j]=='X')bfs(i,j);
    auto min_dis = [](int x,int y)->int{
        int dis=0x3f3f3f3f;
        for(int i=0;i<scc[x].size();i++){
            for(int j=0;j<scc[y].size();j++){
                dis=min(dis,abs(scc[x][i].first-scc[y][j].first)+abs(scc[x][i].second-scc[y][j].second));
            }
        }
        return dis;
    };
    for(int i=1;i<=dfn;i++){
        for(int j=i+1;j<=dfn;j++){
            e[++cnt]={i,j,min_dis(i,j)};
        }
    }
    // for(int i=1;i<=cnt;i++){
    //     cout<<"e["<<i<<"].w: "<<e[i].w<<endl;
    // }
    sort(e+1,e+cnt+1,[](const edge& x,const edge& y){return x.w<y.w;});
    for(int i=1;i<=cnt;i++)fa[i]=i;
    int ans=0;
    for(int i=1;i<=cnt;i++){
        int u=find(e[i].u),v=find(e[i].v);
        if(u!=v){
            fa[u]=v;
            ans+=e[i].w;
        }
    }
    ans=ans-cnt+1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            scc[0].clear();scc[0].push_back({i,j});
            int _=min_dis(1,0)+min_dis(2,0)+min_dis(3,0);
            ans=min(ans,_-2);
        }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Exber (赞：2)

## 做法
广度优先搜索。

首先我们用三个 ```vector``` 来存三个斑点中每一个点的位置，这一步用求联通块的方法就能求解。

然后用三个变量 ```ans1```、```ans2``` 和 ```ans3``` 来存三个斑点两两之间的最短距离（即连接起来需要填充的格子数）。求解的方法也很简单。只要分别枚举两个连通块的点，取最小的曼哈顿距离再减一就行了。

最后特别要注意一种特殊情况，就是三个斑点汇集到地图上某一个点的情况。对于这种情况，需要枚举地图上的每一个点，求出三块斑点离这个点的距离再相加，还要再加上一（这个点本身），最后取最小值就行了。可以把这个距离使用变量 ```ans4``` 存起来。

最后就只剩下了两种情况，分别是两个斑点通过第三个斑点连接起来和三个斑点通过某一个点连接起来。第一种情况的答案显然是 $\min(ans1+ans2,ans1+ans3,ans2+ans3)$。而对于第二种情况，那么答案就更简单明了，直接是 $ans4$。最后在这两个答案之间取 $\min$ 输出就行了。

我个人觉得这道题应该评绿或蓝。

## AC 代码
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct node
{
	int x,y;
};

int n,m;
bool mp[55][55],vis[55][55];
vector<node> g[4];
int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
int cnt;

inline int mabs(int x) // 快速绝对值 
{
	return x<0?-x:x;
}

inline int dis(node a,node b) // 求曼哈顿距离减一的函数 
{
	return mabs(a.x-b.x)+mabs(a.y-b.y)-1;
}

inline void fillmap(int x,int y) // 连通块填充 
{
	vis[x][y]=true;
	queue<node> q;
	q.push((node){x,y});
	g[++cnt].push_back((node){x,y}); // 把起点存入 vector 
	while(!q.empty())
	{
		node now=q.front();
		q.pop();
		for(int i=0;i<4;i++)
		{
			int nx=now.x+dx[i],ny=now.y+dy[i];
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&mp[nx][ny]&&!vis[nx][ny])
			{
				vis[nx][ny]=true;
				q.push((node){nx,ny});
				g[cnt].push_back((node){nx,ny}); // 存入 vector 
			}
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			char ch;
			scanf(" %c",&ch);
			if(ch=='X')
			{
				mp[i][j]=true; // true 表示这里有点 
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(!vis[i][j]&&mp[i][j])
			{
				fillmap(i,j); // 发现一个新的连通块 
			}
		}
	}
	int len1=g[1].size(),len2=g[2].size(),len3=g[3].size();
	int ans1=1e8,ans2=1e8,ans3=1e8,ans4=1e8; // 对应上文
	// 求解 ans1、ans2 和 ans3 
	for(int i=0;i<len1;i++)
	{
		for(int j=0;j<len2;j++)
		{
			ans1=min(ans1,dis(g[1][i],g[2][j]));
		}
	}
	for(int i=0;i<len1;i++)
	{
		for(int j=0;j<len3;j++)
		{
			ans2=min(ans2,dis(g[1][i],g[3][j]));
		}
	}
	for(int i=0;i<len2;i++)
	{
		for(int j=0;j<len3;j++)
		{
			ans3=min(ans3,dis(g[2][i],g[3][j]));
		}
	} 
	// 求解 ans4 
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			// 对于每一个连通块求一下最短距离 
			int premin=1e8,preans=0;
			for(int k=0;k<len1;k++) 
			{
				premin=min(premin,dis((node){i,j},g[1][k]));
			}
			preans+=premin;
			premin=1e8;
			for(int k=0;k<len2;k++)
			{
				premin=min(premin,dis((node){i,j},g[2][k]));
			}
			preans+=premin;
			premin=1e8;
			for(int k=0;k<len3;k++)
			{
				premin=min(premin,dis((node){i,j},g[3][k]));
			}
			preans+=premin;
			ans4=min(ans4,preans+1); // 更新 
		}
	}
	printf("%d\n",min(min(ans1+ans2,min(ans1+ans3,ans2+ans3))/*第一种情况*/,ans4/*第二种情况*/)); // 输出答案 
	return 0;
}
```


---

## 作者：⊱⋛赫宇⋚⊰ (赞：2)

[题目](https://www.luogu.com.cn/problem/P6131)

[double经验](https://www.luogu.com.cn/problem/P2124)

[博客](https://blog.csdn.net/yhhy666/article/details/109475772)

因为n,m都很小，并且有且只有三个联通块，所以我们可以用BFS直接灌水一遍，这样我们就可以统计出来那些处于那些联通块，然后求距离

求距离我们分成两种不同的情况

**1**.路径不相交的时候，那么他的距离就是 
_ans=min(ans, min(dis[1][2]+dis[2][3],min(dis[1][3]+dis[2][3],dis[1][2]+dis[1][3])));_  
有3种组合方法，取一个最小值就是答案，

**2**.然后就是路径会相交在一个点上面，我们先统计每个联通块的点到这个点的最小路径，然后所有路径就是 _ans=min(ans,dis2[1]+dis2[2]+dis2[3]+1);_ 
这个点到达其他三个联通块的代价+这个点的代价

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){res=(res<<1)+(res<<3)+(ch&15);ch=getchar();}
	return res*f;
}
int n,m,dis[55][55];
int dis2[55]; 
int ans=0x3f3f3f3f;
int vis[55][55],a[55][55];
char c[55][55];
struct d{
	int x;
	int y;
};
queue<d>q;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int num;
inline void bfs(int x,int y,int cnt)//bfs灌水找联通块
{
	d st;st.x=x;st.y=y;
	vis[x][y]=1;a[x][y]=cnt;
	q.push(st);
	while(!q.empty())
	{
	   d k;k=q.front();q.pop();
	   for(int i=0;i<4;i++)
	   {
	   	int xx=dx[i]+k.x;
	   	int yy=dy[i]+k.y;
	   	if(xx>=1&&xx<=n&&yy>=1&&yy<=m)
	   	{
	   		if(!vis[xx][yy]&&c[xx][yy]=='X')
	   		{
	   			vis[xx][yy]=1;
	   			a[xx][yy]=cnt;
	   			d ne;ne.x=xx;ne.y=yy;
	   			q.push(ne);
			}
		}
	   }	
	} 
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	cin>>c[i][j];
	
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	if(!vis[i][j]&&c[i][j]=='X')++num,bfs(i,j,num);
	
	dis[1][2]=dis[2][1]=dis[1][3]=dis[3][1]=dis[2][3]=dis[3][2]=0x3f3f3f3f;//三个不同方法先初始化为∞

	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		 memset(dis2,63,sizeof(dis2));
			for(int k=1;k<=n;k++)
			for(int z=1;z<=m;z++)
			{
				if(c[k][z]=='X')
				{
				  if(c[i][j]!='X')dis2[a[k][z]]=min(dis2[a[k][z]],abs(i-k)+abs(j-z)-1);//相交点的最小代价
				  else dis[a[i][j]][a[k][z]]=min(dis[a[i][j]][a[k][z]],abs(i-k)+abs(j-z)-1);//没有相交的代价
				}
			}
			if(c[i][j]!='X')ans=min(ans,dis2[1]+dis2[2]+dis2[3]+1);//打擂台取最小值
	}
//	cout<<dis[1][2]<<' '<<dis[1][3]<<' '<<dis[2][3]<<endl;
	ans=min(ans, min(dis[1][2]+dis[2][3],min(dis[1][3]+dis[2][3],dis[1][2]+dis[1][3])));
	cout<<ans;
	return 0;
}

```


---

## 作者：swl3992 (赞：2)

本题解讲述纯暴力的 dfs + bfs 方法。

题意简化：一张图中有三个连通块，求把这三个连通块连到一起最少需要连多少个空白部分。

首先我们先预处理一下三个连通块，然后把一号连通块里所有结点全部存起来。

接着 bfs 将一号连通块里所有节点全部放入队列，然后往上下左右四个方向走。

如果找到了（二号、三号连通块都访问过了）就更新答案。

实例代码：

**注：本代码中由于是用如果找到比以前更优（要连的个数更少）且其他情况相同的话再次加入队列进行寻找，所以需要找到一个更新一个才能最优，并且需要用 $vis$ 表示当前最优**

**并且 $vis$ 要是四维的因为需要坐标、是否访问过二号连通块、是否访问过三号连通块**

```cpp
//由于评测机波动异常，可能需要开 O2 才能过
#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > test;
struct node
{
	int x,y,step,two,three;	//坐标，要连的部分（以下称为步数）
	vector<vector<int> > sheep;	//表示有没有连起来过，一定要用的原因为可能连完以后再次回来
	node(int x=-1,int y=-1,int step=0,int two=0,int three=0,vector<vector<int> > a=test5):x(x),y(y),step(step),two(two),three(three),sheep(a){}	//构造函数
};
int n,m;
char mp[60][60];	//地图
int num[60][60];	//通过坐标知道这是哪一个连通块（不是则为 0 )
int vis[60][60][2][2];	// vis 数组，意义上面已经说过
int X[]={1,-1,0,0};
int Y[]={0,0,1,-1};	
int cnt;	//当前处理哪一个连通块
int size1;	//用于第一个连通块结点的数目
node one[3000];
void dfs(int x,int y)	//寻找连通块
{
	vis[x][y][0][0]=true;	//注意：此处暂时借用 vis 数组，后面二维都为 0
	num[x][y]=cnt;	
	if(cnt==1)
	{
		one[size1++]=node(x,y);
	}
	for(int i=0;i<4;i++)
	{
		int xx=x+X[i];
		int yy=y+Y[i];
		if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&!vis[xx][yy][0][0]&&mp[xx][yy]=='X')
		{
			dfs(xx,yy);
		}
	}
}
int ans=2147483647;
int bfs()
{
	queue<node> q;
	for(int i=0;i<60;i++)
	{
		for(int j=0;j<60;j++)
		{
			for(int k=0;k<2;k++)
			{
				for(int l=0;l<2;l++)
				{
					vis[i][j][k][l]=65536;	//赋值为较大值，原因已经在“注：”处说明
				}
			}
		}
	}
	for(int i=0;i<size1;i++)	
	{	
		one[i].sheep=test;	//test 将在 main 中初始化，作用为为了上面结构体构造函数及此处使用，意为清零
		q.push(one[i]);
		vis[one[i].x][one[i].y][0][0]=0;	
	}
	while(!q.empty())
	{
		node f=q.front();
		q.pop();
		if(f.two&&f.three)
		{
			ans=min(ans,f.step);
			continue;
		}
		if(f.step>=ans)	//剪枝，如果还没满足条件但是已经比当前答案大则不可能
		{
			continue;
		}
		for(int i=0;i<4;i++)
		{
			int xx=f.x+X[i];
			int yy=f.y+Y[i];
			if(xx>=1&&xx<=n&&yy>=1&&yy<=m)
			{
				node temp=f;
				temp.x=xx;
				temp.y=yy;
				for(int j=0;j<4;j++)	//注意连接好了以后四周的都接上了
				{
					int XX=xx+X[j];
					int YY=yy+Y[j];
					if(XX>=1&&XX<=n&&YY>=1&&YY<=m)
					{
						if(num[XX][YY]==2)
						{
							temp.two=1;
						}
						if(num[XX][YY]==3)
						{
							temp.three=1;
						}
					}
				}
				if(num[xx][yy]==0&&temp.sheep[xx][yy]==0)	//空白并且没有连接过
				{
					temp.sheep[xx][yy]=1;
					temp.step++;
				}
				if(f.step>=vis[xx][yy][temp.two][temp.three])	//当前步数大于或等于最优步数，跳过
				{
					continue;
				}
				vis[xx][yy][temp.two][temp.three]=f.step;
				q.push(temp);
			}
		}
	}
	return ans;
}
void print(int x)
{
	if(x<0)
	{
		x=-x;
		putchar('-');
	}
	if(x>=10)
	{
		print(x/10);
	}
	putchar(x%10+'0');
}
int main()
{
	test.resize(60);	//作用是清零
	for(int i=0;i<60;i++)
	{
		test[i].resize(60);
	}
	for(int i=0;i<60;i++)
	{
		for(int j=0;j<60;j++)
		{
			test[i][j]=0;
		}
	}
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>mp[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(!vis[i][j][0][0]&&mp[i][j]=='X')
			{
				cnt++;
				dfs(i,j);
			}
		}
	}
	print(bfs());
	return 0;
}
```

如果有错误或笔误请私信我修改

---

## 作者：jr_linys (赞：1)

[题目传送门：P6131 [USACO11NOV]Cow Beauty Pageant S](https://www.luogu.com.cn/problem/P6131)
**广搜两种情况，可以把两种情况合并成一种。**
- - -
1.把 $3$ 个不同的斑点标上序号。

2.以每个斑点和非连通块的点当作起点跑一边广搜（```find_dot```），
在同一连斑点不耗时，深搜把在边缘的点放进队列（```ready```)。

3.找到满足与三个连通块的距离最小值时返回取 $\min$。以某个斑点为起点时，到自己的距离为 $0$。
- - -
代码：
```cpp
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

int n,m,dot_sum,xx[4]={0,0,1,-1},yy[4]={1,-1,0,0},a_b[4],cnt=1145141980;
bool q_b[52][52];
char map[52][52];

void check_dot(int x,int y){//把3个不同的斑点标上序号
    map[x][y]=dot_sum;
    for(int i=0;i<4;i++){
        int nx=x+xx[i],ny=y+yy[i];
        if(map[nx][ny]=='X') check_dot(nx,ny);
    }
}

bool vis[52][52];
struct dot{int x,y,st;};queue<dot> q;
void ready(int x,int y,int s,int st=0){//在同一连斑点不耗时,深搜把在边缘的点放进队列
    vis[x][y]=1;
    bool bo=1;
    for(int i=0;i<4;i++){
        int nx=x+xx[i],ny=y+yy[i];
        if(map[nx][ny]=='.' && bo) bo=0,q.push((dot){x,y,st});
        if(map[nx][ny]==s && !vis[nx][ny]) ready(nx,ny,s,st);
    }
}

int find_dot(int ss=0){
    while(!q.empty()){
        int x=q.front().x,y=q.front().y,st=q.front().st;q.pop();
        for(int i=0;i<4;i++){
            int nx=x+xx[i],ny=y+yy[i],mapp=map[nx][ny];
            if(!vis[nx][ny]){
                if(mapp=='.'){
                    vis[nx][ny]=1;
                    q.push((dot){nx,ny,st+1});
                } 
                if(mapp>0 && mapp<=3){
                    a_b[mapp]=st;
                    if(a_b[1]!=-1 && a_b[2]!=-1 && a_b[3]!=-1) return a_b[1]+a_b[2]+a_b[3];//找到满足与三个连通块的距离最小值时返回取min
                    ready(nx,ny,mapp,st);//在同一连斑点不耗时,深搜把在边缘的点放进队列
                }
            }
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",map[i]+1);

    //把3个不同的斑点标上序号
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(map[i][j]=='X') dot_sum++,check_dot(i,j);
    dot_sum=1;
    for(int i=1;i<=n;i++){//以每个斑点和非连通块的点当作起点跑一边广搜
        for(int j=1;j<=m;j++){
            while(!q.empty()) q.pop();

            if(map[i][j]==dot_sum){
                memset(vis,0,sizeof(vis));
                memset(a_b,-1,sizeof(a_b));
                ready(i,j,dot_sum);
                a_b[dot_sum]=0;//以某个斑点为起点时到自己距离设为0
                cnt=min(cnt,find_dot(dot_sum));
                dot_sum++;
            }
            if(map[i][j]=='.'){
                memset(vis,0,sizeof(vis));
                memset(a_b,-1,sizeof(a_b));
                q.push((dot){i,j,0});
                vis[i][j]=1;
                cnt=min(cnt,find_dot()+1);//找到满足与三个连通块的距离最小值时返回取min
            }
        }
    }

    printf("%d",cnt);
}
```

---

## 作者：Unordered_OIer (赞：1)

# P6131 题解
emm
有一道一模一样的题目，[P2124](https://www.luogu.com.cn/problem/P2124)  
## 前置结束，进入正题：
先简化一下问题：如果把**三块区域**变成**三个点**的话……  
应该怎么做？  
有什么**幺蛾子**？  
需要注意**哪些点**？  

解答：分成**两**类  
1. **直接**连接  
![1](https://cdn.luogu.com.cn/upload/image_hosting/ggiy3egh.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
2. 连接到**中间一点**，距离最短  
![2](https://cdn.luogu.com.cn/upload/image_hosting/wz04i9x2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


第一种非常简单，只需要暴力枚举就行；  
第二种就枚举每一个在里面的点，然后打擂台即可。  
于是，一个**简化**的问题就这样$over$了。

如果**点变成面**，有什么区别吗？  
本质上没有区别，只不过连接的点不一样了。  
那有什么难的？直接处理一下不就得了。

那么开始定义函数(本人比较喜欢用函数)：  
1. **$connect()$:表示一块连到另一块的最短距离。**
2. $dfs()$这个不用我说了吧

```cpp

// Copy right by ***
//
//
// Don't copy and paste
//
//
// If you copy and paste,it will be WA.
//
//
// Understand is the first.
// You can do it by yourself.
//
//
// Welcome to visit my blog.
//
// cpp code:

#include<bits/stdc++.h>
#define MXN 55
using namespace std;
//
char cow[MXN][MXN];
int N,M,spots[MXN][MXN][2],gu[3];
void dfs(int a,int b,int num){ // dfs() 
  if (a<0 || b<0 || a==N || b==M || cow[a][b]!='X') return;
   // 触犯边界 
  cow[a][b]='V'; // 省了开一个vis，反正不用输出具体情况 
   // 
   // 请勿这样做，比较危险，vis是最保险的 
  spots[num][gu[num]][0]=a;
  spots[num][gu[num]++][1]=b;
   // 记录每个连通块有哪些点
  dfs(a-1,b,num);
  dfs(a+1,b,num);
  dfs(a,b-1,num);
  dfs(a,b+1,num);
   // 然后对四个方向dfs 
}
int dist(int a1,int b1,int a2,int b2){return abs(a1-a2)+abs(b1-b2);}
 // 曼哈顿距离 
int connect(int a,int b){
  if (cow[a][b]=='V') return 1000; // INF
  int i,j,ans=0; // 
  for (i=0; i<3; i++){ // 枚举连通块 
    int mn=101; // INF
    for (j=0; j<gu[i]; j++){ // 枚举连通块中所有的点 
      int t=dist(spots[i][j][0],spots[i][j][1],a,b)-1;
       // 
      if (t<mn) mn=t; // 求最短距离，打擂台 
    }
    ans+=mn; // 加上答案 
  }
  return ans+1; // 加上一开始枚举的那个点 
}
int main(){
  scanf("%d%d",&N,&M);
  int i,j,k,mn=301,num_spots=0,dsr[3];
  for (i=0; i<N; i++) scanf("%s",cow[i]);
   // 
  for (i=0; i<N; i++)
    for (j=0; j<M; j++)
      if (cow[i][j]=='X') dfs(i,j,num_spots++); 
       // 如果这个点是'X'，就dfs 
  for (i=0; i<N; i++)
    for (j=0; j<M; j++){
      int t=connect(i,j);
      if (t<mn) mn=t;
       // 计算点(i,j)连接3个连通块的最短距离 
    }
   // 
  for (i=0; i<3; i++){
    dsr[i]=101;// INF
    for (j=0; j<gu[i]; j++)
      for (k=0; k<gu[(i+1)%3]; k++){
        int t=dist(spots[i][j][0],spots[i][j][1],spots[(i+1)%3][k][0],spots[(i+1)%3][k][1])-1;
        if (t<dsr[i]) dsr[i]=t;
      }
  }
   // 4
  for (i=0; i<3; i++)
    if (dsr[i]+dsr[(i+1)%3]<mn) mn=dsr[i]+dsr[(i+1)%3];
     // 
  printf("%d\n",mn); // print
  return 0;
}
```
友情提示：无脑照抄有坑  
[安利一下我的blog](https://www.luogu.com.cn/blog/291706/)

---

## 作者：yzy4090 (赞：0)

[原题链接](https://www.luogu.com.cn/problem/P6131)  

**题目大意：**  
本题给定一个大小为 $n\times m$ 的矩阵 $S$，其中恰好存在三个字符 $\tt X$ 组成的四连通块。现需要额外将一些地方修改为 $\tt X$，使得新的矩阵 $S'$ 中恰好存在一个字符 $\tt X$ 组成的四连通块。求最少需要改变的字符个数。  

**解题思路：**  
如图，设 $S$ 中三个四连通块为 $A,B,C$，则使得改变的字符个数最少的方案可以按有无“中转站”分为两种类型。  
![](https://cdn.luogu.com.cn/upload/image_hosting/t1vc8o9b.png)  
我们可以分别计算出两种类型中最少需要改变的字符个数，它们的最小值就是本题的答案。  

对于无“中转站”的类型，我们可以枚举两个位置的坐标，分别求出 $A,B$ 间，$B,C$ 间，$A,C$ 间的最小曼哈顿距离，此种类型的结果即为三个数两两相加的最小值减 $2$ 的值。  
对于有“中转站”的类型，我们可以分别对三个四连通块求出每个点与它的最小曼哈顿距离，然后遍历 $S$ 中所有位置，得到结果。设位置 $(i,j)$ 与三个四连通块 $A,B,C$ 的最小曼哈顿距离分别为 $a_{i,j},b_{i,j},c_{i,j}$，则此种类型的结果为  
$$\min_{1\leq i\leq n,1\leq j\leq m}({a_{i,j}+b_{i,j}+c_{i,j}-2)}$$  

**实现代码：**  
```cpp
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int ud[4]={-1,0,1,0},lr[4]={0,1,0,-1};
int n,m,pcnt,ansans,ans=0x7f7f7f7f,mp[55][55],tmp[55][55],vis[55][55][3];
char ahcr;
int abs(int a){return a>0?a:-a;}
void paint(int x,int y,int color){
	mp[x][y]=color;
	for(int i=0;i<4;i++){
		int ax=x+ud[i],ay=y+lr[i];
		if(ax<1||ay<1||ax>n||ay>m||mp[ax][ay]!=0)continue;
		paint(ax,ay,color);
	}
//使用深度优先搜索，先对自己染色，然后对没有染过色的邻居按照同种方法递归染色 
	return;
}
int man(int a,int b,int c,int d){return abs(a-c)+abs(b-d);}
//求曼哈顿距离，即横坐标的差的绝对值与纵坐标的差的绝对值的和 
class node{
	public:
		int fx,fy,tx,ty;
		int val(){return man(fx,fy,tx,ty);}
		node(){fx=fy=1,tx=ty=100;}
		void output(){printf("%d %d %d %d\n",fx,fy,tx,ty);}
}ab,bc,ac;
class node2{
	public:
		int x,y,tim;
		node2(){x=y=tim=0;}
		node2(int a,int b,int c){x=a,y=b,tim=c;}
};
void larger(int color,int lay){
	queue<node2>q;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(mp[i][j]==color)
				q.push(node2{i,j,0}); 
	while(!q.empty()){
		node2 now=q.front();q.pop();
		if(vis[now.x][now.y][lay]<=now.tim)continue;
		vis[now.x][now.y][lay]=now.tim;
//走到一个位置，若之前走到这个地方时的最小步数小于等于当前步数就中断操作，否则更新并继续操作 
		for(int i=0;i<4;i++){
			node2 tmp;tmp.x=now.x+ud[i],tmp.y=now.y+lr[i],tmp.tim=now.tim+1;
			if(tmp.x<1||tmp.y<1||tmp.x>n||tmp.y>m)continue;
			q.push(tmp);
		}
	}
//利用广度优先搜索，逐层扩展 
	return;
}
int main(){
	memset(mp,-1,sizeof mp);
	memset(vis,0x3f,sizeof vis);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>ahcr;
			if(ahcr=='X')mp[i][j]=0;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(mp[i][j]==0)
				paint(i,j,++pcnt);
//对四连通块进行编号 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=1;k<=n;k++)
				for(int l=1;l<=m;l++){
					if(mp[i][j]==1&&mp[k][l]==2&&man(i,j,k,l)<ab.val())
						ab.fx=i,ab.fy=j,ab.tx=k,ab.ty=l;
					if(mp[i][j]==2&&mp[k][l]==3&&man(i,j,k,l)<bc.val())
						bc.fx=i,bc.fy=j,bc.tx=k,bc.ty=l;
					if(mp[i][j]==1&&mp[k][l]==3&&man(i,j,k,l)<ac.val())
						ac.fx=i,ac.fy=j,ac.tx=k,ac.ty=l;
				}
//枚举两个位置的坐标，若比之前的最小值还要小就更新 
	ansans=min(ab.val()+ac.val()-2,min(ac.val()+bc.val()-2,bc.val()+ab.val()-2));
//得出类型一的结果 
	larger(1,0),larger(2,1),larger(3,2);
//计算每个位置对 A,B,C 的最小曼哈顿距离 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			ans=min(ans,vis[i][j][0]+vis[i][j][1]+vis[i][j][2]-2);
//遍历 S 中所有位置，得出类型二的结果 
	printf("%d",min(ans,ansans));
	return 0;
}
```



---

## 作者：ImposterAnYu (赞：0)

# 解析
首先，我们先对所有的 `X` 进行一个遍历，从而处理出每个 `X` 属于哪个连通块（斑点）。

接下来，我们分析一下应该如何连接这 $3$ 个斑点。

这题连接斑点的方法无非就两种：

1. 选择一个斑点，让另外两个斑点与其连接。

2. 选择一个 `.`，让三个斑点与其连接。

实现第一种方法很简单，只要枚举任意两个斑点里的一对点，计算它们的曼哈顿距离，取个最小值就行了。

至于第二种方法，我们则需要枚举每一个不组成斑点的点（即 `.`），再计算这个点到 $3$ 个斑点的最短距离即可。

这样一套计算下来，我们只需要在两种方法得到的答案中取最小值即可。时间复杂度 $O(n^2m^2)$，可以通过。
# AC code
```c++
#include<bits/stdc++.h>
#define int1 long long
#define p 55
using namespace std;
int1 n,m,i,j,k,l,a[p][p],b[p][p],c,s,d[2][4] = {{1,-1},{0,0,1,-1}},t,u,v,xx,yy;
char ch;
int1 read(){//丑陋无比的快读。 
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){//丑陋无比的快写。 
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 + 48);
  	return ;
}
void dfs(int1 x,int1 y){//遍历，看每个 X 分别属于哪个斑点。 
	b[x][y] = c;//b数组用来记录每个 X 分别属于第几个斑点。 
	for(int1 k = 0; k <= 3; k++){
		xx = x + d[0][k],yy = y + d[1][k];
		if(!b[xx][yy] && a[xx][yy]){//如果下一个点是 X 并且没有被遍历过， 
			dfs(xx,yy);//遍历。 
		}
	}
	return ;
}
int1 dis(int1 x,int1 y){//用于计算连接第 x 个斑点与第 y 个斑点需要涂的最少格子数。 
	int1 minn = 1145141919810;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= m; j++){
			for(k = 1; k <= n; k++){
				for(l = 1; l <= m; l++){
					if((b[i][j] == x && b[k][l] == y) || (b[i][j] == y && b[k][l] == x)){//如果这两个点分别属于第 x 个斑点和第 y 个斑点， 
						minn = min(minn,abs(i - k) + abs(j - l) - 1);//统计答案。 
					}
				}
			}
		}
	}
	return minn;
}
int main(){
	//freopen("pageant.in","r",stdin);
	//freopen("pageant.out","w",stdout);
  	n = read(),m = read();
  	for(i = 1; i <= n; i++){
	  	for(j = 1; j <= m; j++){
		  	ch = getchar();
		  	while(ch != 'X' && ch != '.'){
			  	ch = getchar();
			}
			a[i][j] = (ch == 'X');//a 数组用于记录这个点是 X 还是 . 。 
		}
	}
	for(i = 1; i <= n; i++){
	  	for(j = 1; j <= m; j++){
		  	if(!b[i][j] && a[i][j]){//如果这个点是 X 并且没有被遍历过， 
			  	c++;
			  	dfs(i,j);//遍历整个斑点。 
			}
		}
	}
	t = dis(1,2),u = dis(2,3),v = dis(1,3);//计算斑点之间的距离。 
	s = min(t + u,min(u,t) + v),c = 1145141919810;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= m; j++){
			if(!b[i][j]){//如果这个点是 . ， 
				int1 q[4] = {0,1145141919810,1145141919810,1145141919810}; 
				for(k = 1; k <= n; k++){//枚举其他的 X。 
					for(l = 1; l <= m; l++){
						if(b[k][l]){
							q[b[k][l]] = min(q[b[k][l]],abs(i - k) + abs(j - l) - 1);
						}
					}
				}
				c = min(c,q[1] + q[2] + q[3] + 1);//更新答案。 
			}
		}
	}
	print(min(s,c));//取两种方案中的最小值。 
  	return 0;
}
/*曾经把我代码卡掉的 hack 数据，如果 WA 了，可以自测一下。 
3 3
..X
.X.
X..
*/
```

---

## 作者：Jorisy (赞：0)

一道较为复杂的搜索题，这里提供一个较为~~繁琐~~的做法。

---

首先，我们有两种找答案的方法。一种是基于一个连通块找另一个连通块，一种是基于一个点连三个连通块。

对于第一种做法，我们可以先 dfs 对起点所处的连通块进行处理，然后再 bfs 找其他的一个连通块。最后这样处理两次。

对于第二种做法，我们可以将所有 `X` 点收集起来，然后枚举点然后求最小的曼哈顿距离和。

总复杂度 $O(n^2m^2)$。

AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int X[]={1,0,-1,0};
const int Y[]={0,1,0,-1};
int n,m,a[55][55],c[55][55],f[55][55],sx,sy,k,qx[500005],qy[500005],qdep[500005],ans;
pair<int,int>b[2505];

void dfs(int x,int y)
{
	b[++k]={x,y};//记录所有染色的坐标
	c[x][y]=1;
	a[x][y]=2;//标记
	for(int i=0;i<4;i++)
	{
		int x_=x+X[i],y_=y+Y[i];
		if(x_>0&&x_<=n&&y_>0&&y_<=m&&a[x_][y_]&&!c[x_][y_]) dfs(x_,y_);
	}
}

int bfs(int bx,int by)//找另一个连通块
{
	memset(f,0,sizeof(f));
	int h=1,t=1,res=INT_MAX;
	qx[h]=bx;
	qy[h]=by;
	qdep[h]=0;
	while(h<=t)
	{
		int x=qx[h],y=qy[h],dep=qdep[h++];
		if(x<1||y<1||x>n||y>m||f[x][y]||a[x][y]==2&&h!=2) continue;
		if(a[x][y]==1)
		{
			if(res>=dep)
			{
				res=dep;
				sx=x;
				sy=y;//便于执行第二次 dfs 和 bfs
			}
		}
		f[x][y]=1;
		for(int i=0;i<4;i++)
		{
			qx[++t]=x+X[i];
			qy[t]=y+Y[i];
			qdep[t]=dep+1;
		}
	}
	return --res;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			char c;
			cin>>c;
			a[i][j]=c=='X'?1:0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]==1)
			{
				sx=i;
				sy=j;
				goto p;
			}
		}
	}
	p:;
	dfs(sx,sy);
	int s=INT_MAX;
	for(int i=1;i<=k;i++)
	{
		memset(f,0,sizeof(f));
		s=min(s,bfs(b[i].first,b[i].second));
	}
	ans+=s;
	int nk=k;
	dfs(sx,sy);
	s=INT_MAX;
	for(int i=1;i<=k;i++)
	{
		memset(f,0,sizeof(f));
		s=min(s,bfs(b[i].first,b[i].second));
	}
	ans+=s;//执行两次
	int mk=k;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]==1) b[++k]={i,j};
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]) continue;//必须枚举非填充点
			s=0;
			int t=INT_MAX;
			for(int l=1;l<=nk;l++) t=min(t,abs(b[l].first-i)+abs(b[l].second-j));
			s+=t;
			t=INT_MAX;
			for(int l=nk+1;l<=mk;l++) t=min(t,abs(b[l].first-i)+abs(b[l].second-j));
			s+=t;
			t=INT_MAX;
			for(int l=mk+1;l<=k;l++) t=min(t,abs(b[l].first-i)+abs(b[l].second-j));
			//[1,nk] 为第一个连通块，[nk+1,mk] 为第二个连通块，[mk+1,k] 为第三个连通块
			ans=min(ans,s+t-2);//曼哈顿距离和会重复计算枚举的点，故减去二
		}
	}
	cout<<ans;
 	return 0;
}
```

---

## 作者：哈士奇憨憨 (赞：0)

## 题意
给定一个由空白和斑点组成的字符矩阵，斑点刚好组成三个四方向的连通块，求最少将多少个格子变成斑点，可以将三个连通块合并。
## 思路
思考合并连通块的方式，可以发现有两种合并的方法：

1. 两个连通块分别连接到另一个连通块上。
2. 选择一个汇合点，三个连通块分别连接到汇合点上。

如果合并时连接的路径有重叠，只会让答案变大会影响最优答案的求解，而最优答案必然为上述两种方法之一。

因此，我们可以先找到三个连通块，然后分别从三个连通块开始用宽度优先遍历扩张，计算出每个格子分别到三个连通块的距离，进一步就可以计算出连通块之间的距离，最后枚举进行求解即可。
## CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
const int kMaxN = 51, kD[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int a[kMaxN][kMaxN], d[kMaxN][kMaxN][3], l[3][3], q[kMaxN * kMaxN][2];
int n, m, o, h, t, ans = 1e9;
char c;
void R(int i, int x, int y, int l) {                                              // 扩展位置(x, y)的位置，类型i，距离l
  if (x < 1 || x > n || y < 1 || y > m || d[x][y][o] || !(i || a[x][y] == -1)) {  // 越界、重复或者字符不匹配
    return;
  }
  d[x][y][o] = l;  // 记录距离
  if (!i) {        // 是扩展斑点
    a[x][y] = o;   // 标记斑点
  }
  ++t, q[t][0] = x, q[t][1] = y;  // 将位置加入队列
}

void W(int x, int y) {                                  // 从(x, y)所在斑点开始遍历矩阵
  h = 0, t = -1;                                        // 初始化队列
  R(0, x, y, 1);                                        // 加入初始位置
  for (int i = 0; i <= t; i++) {                        // 按顺序处理位置
    for (int j = 0; j < 4; j++) {                       // 枚举方向
      R(0, q[i][0] + kD[j][0], q[i][1] + kD[j][1], 1);  // 扩展斑点
    }
  }
  for (; h <= t; h++) {                                                          // 按顺序处理位置
    for (int i = 0; i < 4; i++) {                                                // 枚举方向
      R(1, q[h][0] + kD[i][0], q[h][1] + kD[i][1], d[q[h][0]][q[h][1]][o] + 1);  // 扩展其他位置
    }
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> c;
      a[i][j] = (c == 'X') - 2;  // 字符转数字，空白-2、斑点-1
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {  // 枚举网格
      if (a[i][j] == -1) {          // 找到未处理的斑点
        W(i, j), o++;               // 从当前斑点进行宽度优先遍历，增加斑点数量
      }
    }
  }
  fill(l[0], l[0] + 9, 1e9);  // 初始化斑点之间的距离
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {                               // 枚举格子
      ans = min(ans, d[i][j][0] + d[i][j][1] + d[i][j][2] - 5);  // 三个斑点连接到该点，更新答案
      if (a[i][j] >= 0) {                                        // 当前格子是斑点
        for (int k = 0; k <= 2; k++) {                           // 枚举斑点
          l[a[i][j]][k] = min(l[a[i][j]][k], d[i][j][k] - 1);    // 更新斑点之间的距离
        }
      }
    }
  }
  for (int i = 0; i <= 2; i++) {                      // 枚举斑点
    ans = min(ans, l[i][0] + l[i][1] + l[i][2] - 2);  // 连接到该斑点，更新答案
  }
  cout << ans;
  return 0;
}

```

---

## 作者：yzh_Error404 (赞：0)

[双倍经验！](https://www.luogu.com.cn/problem/P2124)

做法： $bfs$ 判联通块 + $O(n^4)$ 暴力模拟

首先， $n$ 和 $m$ 范围极小，我们可以考虑搜索~~乱搞~~。

先要确定每一个 `X` 属于哪一个联通块,用 $bfs$ 即可实现。

之后，我们可以枚举出每两个点，分四种情况来讨论 $a$ 与 $b$ 的关系。（设它们为 $a$ 和 $b$）

下面 $dis$ 代表每两个联通块之间的最小距离， $dis$_$n$ 代表 $a$ 到每个联通块的距离， $bel$ 代表当前点属于哪个联通块， $dist(a,b)$ 为 $a$，$b$ 两点之间的距离。

1. $a$ 和 $b$ 均为 `X`
  
   则 $a$ 与 $b$ 之间的距离与 $a$，$b$ 两点属于的联通块距离取较小值。
   
   即为 `dis[bel[a.x][a.y]][bel[b.x][b.y]]=min(dis[bel[a.x][a.y]][bel[b.x][b.y]],dist(a,b))` 。
   
2. $a$ 和 $b$ 均为 `.`
   
   所以 $a$ 的答案和 $b$ 没什么关系，跳过即可。
   
3. $a$ 为 `X`，$b$ 为 `.`

   所以 $a$ 与 $b$ 还是没有关系，继续跳过。
   
4. $a$ 为 `.`，$b$ 为 `X`

   则 $a$ 到 $b$ 之间的距离与 $a$ 到   $b$ 属于的联通块的距离取较小值。
   
   即为 `dis_n[bel[b.x][b.y]]=min(dis_n[bel[b.x][b.y]],dist(a,b))` 。
   
关于上面情况2,4为什么要跳过，因为 $a$ 和 $b$ 是可以交换的，这两种情况等到后面一定会考虑到。
 
每枚举一个 $a$ ，我们都要考虑 $a$ 作为三个联通块交叉的点的总长度，即为 `dis_n[1]+dis_n[2]+dis_n[3]` 。

最后，考虑交叉点在联通块中的情况，枚举取最小值即可。

注意，在输出的时候答案要减 $2$ ,因为交叉点算了三次。

代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=55;
struct node
{
	int x,y;
};
int n,m;
char ma[MAXN][MAXN];
int bel[MAXN][MAXN];
int fx[5]={0,-1,1,0,0};
int fy[5]={0,0,0,-1,1};
int dis[MAXN][MAXN],dis_n[MAXN];
inline int dist(node x,node y)//上文所述的距离函数
{
	return abs(x.x-y.x)+abs(x.y-y.y);
}
inline void bfs(int x,int y,int col)//bfs判联通块
{
	queue<node>q;
	q.push((node){x,y});
	bel[x][y]=col;
	while(!q.empty())
	{
		node top=q.front();
		q.pop();
		for(register int i=1;i<=4;i++)
		{
			int nx=top.x+fx[i],ny=top.y+fy[i];
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&ma[nx][ny]=='X'&&bel[nx][ny]==0)
			{
				bel[nx][ny]=col;
				q.push((node){nx,ny});
			}
		}
	}
}
int main()
{
	memset(dis,0x7f,sizeof(dis));
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=m;j++)
		{
			cin>>ma[i][j];
			if(ma[i][j]=='.')bel[i][j]=-1;
		}
	int now=0;
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=m;j++)
			if(ma[i][j]=='X'&&!bel[i][j])bfs(i,j,++now);
	int ans=0x3f3f3f3f;
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=m;j++)
		{
			node a;
			a.x=i,a.y=j;
			memset(dis_n,0x3f,sizeof(dis_n));
			for(register int k=1;k<=n;k++)
				for(register int l=1;l<=m;l++)
				{
					node b;
					b.x=k,b.y=l;
					if(ma[a.x][a.y]=='X'&&ma[b.x][b.y]=='X')
						dis[bel[a.x][a.y]][bel[b.x][b.y]]=min(dis[bel[a.x][a.y]][bel[b.x][b.y]],dist(a,b));//情况1
					if(ma[a.x][a.y]=='.'&&ma[b.x][b.y]=='X')
						dis_n[bel[b.x][b.y]]=min(dis_n[bel[b.x][b.y]],dist(a,b));//情况3
				}
			if(ma[a.x][a.y]!='X')ans=min(ans,dis_n[1]+dis_n[2]+dis_n[3]);//a为交叉点
		}
	ans=min(ans,min(dis[1][2]+dis[2][3],min(dis[1][3]+dis[2][3],dis[1][2]+dis[1][3])));//统计答案
	printf("%d",ans-2);
	return 0;
}
```

---

