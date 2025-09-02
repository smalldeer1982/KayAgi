# [NWERC 2023] Klompendans

## 题目描述

在传统的荷兰木屐舞中，舞者需要遵循非常特定的动作序列。舞蹈在一个由方形瓷砖组成的方形网格上进行，开始时舞者站在网格左上角的瓷砖上。然后，舞者在两种舞蹈动作之间交替进行，在网格中从一个瓷砖移动到另一个瓷砖，可以持续任意长时间。第一次移动可以是任意一种类型，但之后必须严格交替进行这两种动作。

这两种移动方式类似于国际象棋中马的走法：
- 第一种移动类型：从当前瓷砖移动到一个距离当前瓷砖沿一个轴方向 $a$ 格、另一轴方向 $b$ 格的瓷砖。
- 第二种移动类型：从当前瓷砖移动到一个距离当前瓷砖沿一个轴方向 $c$ 格、另一轴方向 $d$ 格的瓷砖。

由于可以自由交换两个轴并选择每个轴上的移动方向，每种移动类型最多有 8 种执行方式。图 K.1 展示了一个示例舞蹈动作，其中 $(a,b) = (1,2)$，$(c,d) = (2,3)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/yu84dg31.png)

:::align{center}
图 K.1：样例输入 3 的图示，展示了一个从 $4 \times 4$ 网格左上角开始、在左下角结束的舞蹈，途中经过蓝色方格。总共有 $13$ 个可到达的方格。红色高亮的三个方格不能成为任何舞蹈表演的一部分。
:::

从左上角瓷砖开始，在跳木屐舞时可以到达多少个不同的瓷砖？不允许走出网格，并且不计算在移动过程中只是跨过的瓷砖。注意，需要计算在某种舞蹈表演中可以到达的所有瓷砖，但不一定是在同一次表演中到达。

## 样例 #1

### 输入

```
3
2 1
2 2```

### 输出

```
6```

## 样例 #2

### 输入

```
8
1 2
1 2```

### 输出

```
64```

## 样例 #3

### 输入

```
4
1 2
2 3```

### 输出

```
13```

## 样例 #4

### 输入

```
5
1 2
2 3```

### 输出

```
25```

## 样例 #5

### 输入

```
10
3 3
4 4```

### 输出

```
50```

# 题解

## 作者：Shuhang_JOKER1 (赞：4)

这题可以用 BFS 来做。

### 题目描述：

这是一个在 $n×n$ 网格上跳舞的问题。

舞者从左上角出发，有两种移动方式：第一种是走“$a$ 步和 $b$ 步”（可以任意组合方向和顺序），第二种是走“$c$ 步和 $d$ 步”。跳舞时必须交替使用这两种移动方式（第一次可以任选一种）。

问在不越出网格的前提下，舞者通过任意次移动后，最多能踩到多少个不同的格子。

### 题目分析：

题目的关键在于理解移动的交替规则和状态的表示。由于舞者必须在两种移动类型之间交替，因此下一步使用哪种移动类型是状态的一部分。

如果只记录位置，会遗漏“下一步该用哪种移动”的信息，从而导致错误。

例如，从某个位置出发，用类型 $1$ 能到达的位置和用类型 $2$ 能到达的位置可能完全不同。

因此，状态应定义为（行，列，下一步移动类型），其中移动类型为 $0$ 或 $1$。

此外，由于移动具有方向性和对称性，每种移动 $(p,q)$ 可以生成8个方向：$(±p, ±q)$ 和 $(±q, ±p)$。

舞者不能越界，因此每次移动后必须检查新位置是否在 $[0,n-1]$ 范围内。

### 题解：

我们可以采用广度优先搜索（BFS）来枚举所有可达状态。

从起点 $(0,0)$ 出发，由于第一次移动可以是任意类型，因此初始时将状态 $(0,0,0)$ 和 $(0,0,1)$ 都加入搜索队列，并标记 $(0,0)$ 为已访问。在搜索过程中，对于当前状态 $(r,c,t)$，根据 $t$ 选择对应的移动方式，枚举其 $8$ 个方向，计算新位置。

如果新位置在网格内，则将其标记为可达，并将新状态（新位置，下一步移动类型取反）加入队列，前提是该状态未被访问过。这样可以避免重复搜索，确保效率。

搜索结束后，统计所有被标记为可达的网格位置数量即可。由于每个状态最多被访问一次，且状态总数为 $O(n^2)$，每个状态最多扩展 $8$ 次，因此总时间复杂度为 $O(n^2)$，在 $n≤500$ 的范围内完全可行。

用 BFS 算法能够正确处理交替移动的约束，并完整覆盖所有可能的舞蹈路径，从而得到准确的可达瓷砖数。

### 代码：

- $vis$ 数组：一个二维 bool 数组，用于记录网格中的每一个格子是否在某一次合法的舞蹈序列中被踩到过。只要舞者在任何一次移动后到达了某个格子 $(r,c)$，无论他是通过哪种移动类型到达的，$vis[r][c]$ 就会被标记为 true。这个数组最终用来统计总共可以到达多少个不同的格子，是生成答案的直接依据。
- $g$ 数组：是一个三维 bool 数组，用于在广度优先搜索（BFS）过程中避免重复访问相同的状态。这里的“状态”不仅包括位置 $(r,c)$，还包括下一步要使用的移动类型 $t$（$0$ 或 $1$）。因此，$g[r][c][t]$ 记录的是“当前位于 $(r,c)$ 且下一步要使用类型 $t$ 的移动”这个状态是否已经被处理过。因为从同一个位置出发，使用不同的移动类型会到达完全不同的新位置，所以必须将移动类型作为状态的一部分。$g$ 数组保证了每个唯一的状态只被处理一次，防止 BFS 进入无限循环，是保证算法效率和正确性的关键。
- 队列 $q$：存储待处理的“状态”。这里的“状态”指的是舞者在网格中的位置 $(r,c)$ 以及下一步要使用的移动类型 $t$（$0$ 或 $1$）。队列 $q$ 保存了所有已经发现但还没有被用来尝试下一步移动的状态。
  
cpp：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,d;
bool vis[505][505],g[505][505][2];//vis 和 g 数组 
queue<pair<pair<int,int>,int> > q;//队列 q
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> a >> b >> c >> d;//输入
    pair<int,int> d1[8]={{a,b},{a,-b},{-a,b},{-a,-b},{b,a},{b,-a},{-b,a},{-b,-a}};
	pair<int,int> d2[8]={{c,d},{c,-d},{-c,d},{-c,-d},{d,c},{d,-c},{-d,c},{-d,-c}};//两组十六个可能位置变化
    vis[0][0] = true;
    q.push({{0, 0}, 0});
    q.push({{0, 0}, 1});
    g[0][0][0] = true;
    g[0][0][1] = true;
    while (!q.empty()) {//循环
        auto x = q.front(); 
		q.pop();
        int r=x.first.first,c=x.first.second,t=x.second;//新的位置和状态
        if(t==0){//状态为 0
	        int nxt = 1 - t; 
	        for(int i=0;i<8;i++) {
	            int nr = r + d1[i].first;
	            int nc = c + d1[i].second;
	            if (nr < 0 || nr >= n || nc < 0 || nc >= n)//边界条件
					continue;
	            vis[nr][nc] = true;
	            if (!g[nr][nc][nxt]) {
	                g[nr][nc][nxt] = true;
	                q.push({{nr, nc}, nxt});//入队
	            }
	        }
        }else{//状态为 1
	        int nxt = 1 - t; 
	        for(int i=0;i<8;i++) {
	            int nr = r + d2[i].first;
	            int nc = c + d2[i].second;
	            if (nr < 0 || nr >= n || nc < 0 || nc >= n)//边界条件
					continue;
	            vis[nr][nc] = true;
	            if (!g[nr][nc][nxt]) {
	                g[nr][nc][nxt] = true;
	                q.push({{nr, nc}, nxt});//入队
	            }
	        }
		}
    }
    int ans = 0;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            if (vis[i][j]) 
                ans++;//判断计数
    cout << ans << endl;//输出答案
    return 0;
}
```

---

## 作者：ziyaojia (赞：2)

这道题我们可以用 BFS 来求解。首先我们用一个三维数组来表示他走到了这里且当前走到这的舞步的值，再在每次走到一个地方时将那个地方的值赋值为 1，接着遍历一遍整个数组，只要走到了那里就答案加 1，最后输出答案就好了。

### [AC](https://www.luogu.com.cn/record/230738094) Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int dx[5] = {0,1,1,-1,-1};
const int dy[5] = {0,1,-1,1,-1};
int n,a,b,c,d,ans;
int vis[501][501][2];
struct node
{
    int x,y;
    bool flag;
};
queue<node> q;
void bfs()
{
    q.push({1,1,0});
    q.push({1,1,1});
    vis[1][1][0] = 1;
    vis[1][1][1] = 1;
    while(!q.empty())
    {
        node tmp = q.front();
        q.pop();
        for(int i = 1;i <= 4;i++)
        {
            int nx = tmp.x;
            int ny = tmp.y;
            if(tmp.flag)
            {
                nx += a * dx[i];
                ny += b * dy[i];
            }
            else 
            {
                nx += c * dx[i];
                ny += d * dy[i];
            }
            if(nx < 1||ny < 1||nx > n||ny > n)continue;
            if(!vis[nx][ny][!tmp.flag])
            {
                q.push({nx,ny,!tmp.flag});
                vis[nx][ny][!tmp.flag] = 1;
            }
        }
        for(int i = 1;i <= 4;i++)
        {
            int nx = tmp.x;
            int ny = tmp.y;
            if(tmp.flag)
            {
                nx += b * dx[i];
                ny += a * dy[i];
            }
            else 
            {
                nx += d * dx[i];
                ny += c * dy[i];
            }
            if(nx < 1||ny < 1||nx > n||ny > n)continue;
            if(!vis[nx][ny][!tmp.flag])
            {
                q.push({nx,ny,!tmp.flag});
                vis[nx][ny][!tmp.flag] = 1;
            }
        }
        //vis[tmp.x][tmp.y] = 0;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> n >> a >> b >> c >> d;
    bfs();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            if(vis[i][j][1]||vis[i][j][0])
               ans++;
    cout << ans;
    return 0;
}
```

---

## 作者：Zhao114 (赞：1)

# 题目大意
给定**两种**移动类型和一个边长为 $n$ 的正方形，每种类型有 $8$ 种移动方式（类似于象棋中的马），但两种移动类型**必须交替使用**。从左上角的格子开始移动，第一次移动类型**随意**，问共能走到多少个格子。
# 解题思路
发现数据范围中 $n \le 500$，考虑使用 DFS，其中除了当前坐标之外还需要记录**当前应该用的移动类型**。

由于有两种移动类型，且必须交替使用，所以搜到一个格子后将其标记，且不再搜索的方法可能会**漏掉**一些移动方式。

如：当前使用第一种移动类型找到格子 $(1,2)$ 后将其标记并不再搜索。这样就会将用第二种移动类型找到这个格子并继续搜索的方式漏掉。

因此我们可以在用于标记的数组上额外加一维（如：`book[510][510][2]`）用于表示走到此格时所用的移动类型，以此来防止漏掉一些移动方式。为了做到**不重复统计**，只有标记数组中该格两种移动类型**均标记为未走过**时才能让答案增加。

由于我们要找的是**总共可以走到的格子的个数**，因此已经用过两种移动类型走到此格之后，任何对这个格子的再次搜索都是**不必要**的（因为此格的所有移动方式都已经被找到了），因此搜索完成后标记数组不必归零。

由于第一次移动类型随意，所以我们需要两次 DFS。时间复杂度为 $O(n^2)$。可以快速通过。
# 代码
```cpp
#include <iostream>
using namespace std;
long long dx[2][8][2],book[510][510][2],ans = 1,n;
void dfs(long long x,long long y,long long d){
	long long i,nx,ny;
	for(i = 0;i < 8;i++){
		nx = x + dx[d][i][0];
		ny = y + dx[d][i][1];
		if(nx <= 0 || ny <= 0 || nx > n || ny > n){
			continue;//判断是否越界
		}
		if(book[nx][ny][d] == 1){
			continue;//当标记数组中此格此种移动类型走过时就不再走了
		}
		if(book[nx][ny][!d] == 0){
			ans++;//当标记数组中此格两种移动类型均未走过时才可以使答案增加
		}
		book[nx][ny][d] = 1;
		dfs(nx,ny,!d);
	}
}//DFS函数
int main(){
	long long a,b,c,d;
	cin>>n>>a>>b>>c>>d;
  //对移动类型进行初始化
	dx[0][0][0] = a;
	dx[0][0][1] = b;
	dx[0][1][0] = a;
	dx[0][1][1] = -b;
	dx[0][2][0] = -a;
	dx[0][2][1] = b;
	dx[0][3][0] = -a;
	dx[0][3][1] = -b;
	dx[0][4][0] = b;
	dx[0][4][1] = a;
	dx[0][5][0] = b;
	dx[0][5][1] = -a;
	dx[0][6][0] = -b;
	dx[0][6][1] = a;
	dx[0][7][0] = -b;
	dx[0][7][1] = -a;
 //上半部分为第一种移动类型的初始化，下半部分为第二种移动类型的初始化
	dx[1][0][0] = c;
	dx[1][0][1] = d;
	dx[1][1][0] = c;
	dx[1][1][1] = -d;
	dx[1][2][0] = -c;
	dx[1][2][1] = d;
	dx[1][3][0] = -c;
	dx[1][3][1] = -d;
	dx[1][4][0] = d;
	dx[1][4][1] = c;
	dx[1][5][0] = d;
	dx[1][5][1] = -c;
	dx[1][6][0] = -d;
	dx[1][6][1] = c;
	dx[1][7][0] = -d;
	dx[1][7][1] = -c;
	book[1][1][0] = 1;
	dfs(1,1,0);
	book[1][1][1] = 1;
	dfs(1,1,1);//由于第一次移动方式随意，所以需要两次DFS
	cout<<ans;
}
```

---

## 作者：inscape (赞：1)

~~非常好搜索，使我小脑旋转~~

## 思路

十分显然的一道搜索，我们使用 DFS 进行解决 ~~（BFS？dog 都不用）~~。

设计状态 `dfs(x,y,f)` 表示当前走到了 $(x,y)$ 的位置，使用的是第 $f$ 种移动方式（$f$ 为 bool 类型变量）。

随后用 $4$ 个数组分别记录当 $f=0$ 与 $f=1$ 时 $x,y$ 的移动方式，代码如下：

```cpp
ax[1]=ax[2]=a,ax[3]=ax[4]=a,ax[5]=ax[6]=b,ax[7]=ax[8]=-b;
ay[1]=ay[3]=b,ay[2]=ay[4]=b,ay[5]=ay[7]=a,ay[6]=ay[8]=-a;
bx[1]=bx[2]=c,bx[3]=bx[4]=c,bx[5]=bx[6]=d,bx[7]=bx[8]=-d;
by[1]=by[3]=d,by[2]=by[4]=d,by[5]=by[7]=c,by[6]=by[8]=-c;
```

然后再使用一个**三维**数组 `vis` 存储访问标记，避免出现无限循环的情况。那么为什么要开三维呢？前两维很好理解，用于存储 $x,y$ 的情况，第三维我们用于存储**以不同移动类型到达同一位置**的情况，不然会导致计数不完全。[我是例子](https://www.luogu.com.cn/record/231029742)。

但是在我们开三维的情况下，会导致同一位置多次计数，这时候我们就要请出 —— `map`！

`map` 是存储键值对的一种容器，并且**其中每个键值都是唯一的**，这就导致它能很好的处理去重这一任务。

[更多关于 map 的介绍](https://www.runoob.com/cplusplus/cpp-libs-map.html)

但是，`map` 自带的键值又是一维的，不能很好的应对这种坐标系的问题，这时候我们就可以使用 `pair` 了，`pair` 的用处是将两个值组合成一个值。

[更多关于 pair 的介绍](https://blog.csdn.net/sevenjoin/article/details/81937695)

剩下的就看代码里的注释吧。

## $Code$

```cpp
#include<bits/stdc++.h> // 万能头,其中包含大量STL,包含map和pair在内
using namespace std;
int ax[9],ay[9],bx[9],by[9]; // 用于存储两种不同的移动方式
int n,a,b,c,d;
bool vis[510][510][2]; // 存储遍历情况，第三维用于存储以不同移动类型到达同一位置的情况
map<pair<int,int>,bool> ans; // 使用map记录答案并去重
void dfs(int x,int y,bool f){ // x,y表示现在到达的坐标,f表示使用的移动方式
	if(vis[x][y][f]) return; // 如果遍历过，那么retun
	vis[x][y][f]=true; // 如果没有，记录为遍历过
	ans[{x,y}]=1; // 将当前格子的信息记录到map里
	for(int i=1;i<=8;i++){ // 前往下一个格子
		int nx,ny; // 下一个格子的坐标
		if(f){ // 若是第一种移动方式
			nx=x+ax[i];
			ny=y+ay[i];
			if(nx<=n&&nx>=1&&ny>=1&&ny<=n) dfs(nx,ny,0); // 判断出界
		}
		else{ // 若是第二种移动方式
			nx=x+bx[i];
			ny=y+by[i];
			if(nx<=n&&nx>=1&&ny>=1&&ny<=n) dfs(nx,ny,1);
		}
	}
}
int main(){
	std::ios::sync_with_stdio(false); // 关闭同步流,提速
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	cin>>n>>a>>b>>c>>d; // 题目要求的输入
	ax[1]=ax[2]=a,ax[3]=ax[4]=-a,ax[5]=ax[6]=b,ax[7]=ax[8]=-b; // 第一种移动方式的x坐标变化
	ay[1]=ay[3]=b,ay[2]=ay[4]=-b,ay[5]=ay[7]=a,ay[6]=ay[8]=-a; // 第一种移动方式的y坐标变化
	bx[1]=bx[2]=c,bx[3]=bx[4]=-c,bx[5]=bx[6]=d,bx[7]=bx[8]=-d; // 第二种移动方式的x坐标变化
	by[1]=by[3]=d,by[2]=by[4]=-d,by[5]=by[7]=c,by[6]=by[8]=-c; // 第二种移动方式的y坐标变化
	dfs(1,1,0); // 第一次搜索，搜索以第二种移动方式开始的情况
	memset(vis,0,sizeof(vis)); // 清空vis数组,避免有些格子没有走到的情况
	dfs(1,1,1); // 第二次搜索，搜索以第一种移动方式开始的情况
	cout<<ans.size(); // 最后输出map里存储的数字数量,也就是问题的答案
	return 0; // 完结撒花!
}
```

[AC 记录](https://www.luogu.com.cn/record/231030202)，祝你们好运（滑稽

---

## 作者：Gongyujie123 (赞：1)

## [P13710 [NWERC 2023] Klompendans](https://www.luogu.com.cn/problem/P13710) 题解
### 1. 思路分析
一道搜索题，选择 dfs。

首先，我们定义 dfs 函数为 `dfs(int x, int y, int u)`，其中 $x, y$ 表示当前在 $(x, y)$ 瓷砖，$u$ 表示下一步进行第 $u$ 种移动类型。再定义一个三维 bool 数组 $t$，$t_{x, y, u}$ 表示在 $(x, y)$ 上有没有执行过第 $u$ 种移动。

对于 dfs 里面，我们把 $t_{x, y, u}$ 设为 $1$，然后先枚举 4 个方向，再交换两个轴，再枚举 4 个方向。如果 $u = 1$，就按照第一种移动，还要再判断是否越界或 $t_{tx, ty, 2} = 1$（因为如果在 $(tx, ty)$ 上执行过第 2 种移动，就不用再执行了），又因为要交替，所以下一次就是第二种移动，即 `dfs(tx, ty, 2)`（$tx$ 和 $ty$ 表示移动完的的位置）；如果 $u = 2$，也是同理，即 `dfs(tx, ty, 1)`。

对于主函数里，我们注意到首次可以是任意一种类型，所以要执行 `dfs(1, 1, 1)` 和 `dfs(1, 1, 2)`，最后统计答案，就是求 $n \times n$ 的方格里有多少对 $(i, j)$ 满足 $t_{i, j, 1} = 1$ 或 $t_{i, j, 2} = 1$。
### 2. AC 代码
[AC 记录](https://www.luogu.com.cn/record/231385889)。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
bool t[602][602][3];
int n, a, b, c, d;
int xx[] = {1, 1, -1, -1}, yy[] = {-1, 1, 1, -1};
void dfs(int x, int y, int u) {
	t[x][y][u] = 1;
	for (int i = 0; i < 4; i++) {
		if (u == 2) {
			int tx = x + xx[i] * a, ty = y + yy[i] * b;
			if (tx >= 1 && tx <= n && ty >= 1 && ty <= n && !t[tx][ty][1]) {
				dfs(tx, ty, 1);
			}
			tx = x + xx[i] * b, ty = y + yy[i] * a;
			if (tx >= 1 && tx <= n && ty >= 1 && ty <= n && !t[tx][ty][1]) {
				dfs(tx, ty, 1);
			}
		}
		if (u == 1) {
			int tx = x + xx[i] * c, ty = y + yy[i] * d;
			if (tx >= 1 && tx <= n && ty >= 1 && ty <= n && !t[tx][ty][2]) {
				dfs(tx, ty, 2);
			}
			tx = x + xx[i] * d, ty = y + yy[i] * c;
			if (tx >= 1 && tx <= n && ty >= 1 && ty <= n && !t[tx][ty][2]) {
				dfs(tx, ty, 2);
			}
		}
	}
}
signed main() {
	cin >> n >> a >> b >> c >> d;
	dfs(1, 1, 1);
	dfs(1, 1, 2);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (t[i][j][1] || t[i][j][2]) ans++;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：HP_Serenity (赞：1)

### 题目要素
在大小为 $n \times n$ 的网格上，从左上角 $(1,1)$ 出发，交替执行两种“类骑士”移动（类似象棋中的马走日）：第一种移动 $(a,b)$，第二种移动 $(c,d)$。每次移动可以沿坐标轴的正负方向进行，但不能越界。求所有可达的格子数量。
### 解法思路
采用 BFS 模拟移动过程，记录每个格子在两种移动类型下的可达性。具体步骤：
1. 初始化队列，起点 $(1,1)$ 可通过两种移动的起点状态加入队列。
2. 交替扩展队列中的状态：
- 若当前状态是通过第一种移动到达的，则下一步尝试所有可能的第二种移动；
- 反之，尝试第一种移动。

使用二维数组标记可达的格子，最后统计总数。
### 关键点
状态设计：记录当前位置 $(x,y)$ 和当前移动类型 $t$，避免重复访问。移动时检查是否在网格范围内。次切换移动类型，确保严格交替。时间复杂度为 $O(n^2)$，因每个格子最多被两种状态各访问一次。

---

## 作者：Loyal_Soldier (赞：1)

### 思路

这题，很明显是一个广搜。

设当前是第一种移动方法，则有以下 $8$ 种移动方法：

- $x$ 坐标增加 $a$，$y$ 坐标增加 $b$。
- $x$ 坐标增加 $a$，$y$ 坐标减少 $b$。
- $x$ 坐标减少 $a$，$y$ 坐标增加 $b$。
- $x$ 坐标减少 $a$，$y$ 坐标减少 $b$。
- $x$ 坐标增加 $b$，$y$ 坐标增加 $a$。
- $x$ 坐标增加 $b$，$y$ 坐标减少 $a$。
- $x$ 坐标减少 $b$，$y$ 坐标增加 $a$。
- $x$ 坐标减少 $b$，$y$ 坐标减少 $a$。

第二种移动方法同理。

最后统计答案就行了，其他地方跟普通广搜差不多，具体实现见代码。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int N = 510;
int n, a[N], b[N];
bool vis[N][N][3];//vis 数组表示坐标 (i,j) 移动方法为 type 时是否走过
int ans;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> a[1] >> b[1] >> a[2] >> b[2];
	queue <array <int, 3> > que;
	vis[1][1][1] = vis[1][1][2] = true;//初始化
	que.push({1, 1, 1});
	que.push({1, 1, 2});//将初始信息加入队列
	while(!que.empty())
	{
		array <int, 3> x = que.front();//x[0] 为 x 坐标，x[1] 为 y 坐标，x[2] 为移动类型
		que.pop();
		if(x[2] == 1)
		{
			int type = x[2];
			int qwq[10] = {a[type], a[type], -a[type], -a[type], b[type], b[type], -b[type], -b[type]};
			int awa[10] = {b[type], -b[type], b[type], -b[type], a[type], -a[type], a[type], -a[type]};//8 种移动方法
			for(int i = 0;i < 8;i ++)
			{
				int nx = x[0] + qwq[i], ny = x[1] + awa[i];
				if(nx >= 1 && nx <= n && ny >= 1 && ny <= n && vis[nx][ny][2] == false) que.push({nx, ny, 2}), vis[nx][ny][2] = true;//判断是否合法，合法则加入队列并标记
			}
		}
		else//同上
		{
			int type = x[2];
			int qwq[10] = {a[type], a[type], -a[type], -a[type], b[type], b[type], -b[type], -b[type]};
			int awa[10] = {b[type], -b[type], b[type], -b[type], a[type], -a[type], a[type], -a[type]};
			for(int i = 0;i < 8;i ++)
			{
				int nx = x[0] + qwq[i], ny = x[1] + awa[i];
				if(nx >= 1 && nx <= n && ny >= 1 && ny <= n && vis[nx][ny][1] == false) que.push({nx, ny, 1}), vis[nx][ny][1] = true;
			}
		}
	}
	for(int i = 1;i <= 500;i ++)
		for(int j = 1;j <= 500;j ++)
			if(vis[i][j][1] || vis[i][j][2]) ans ++;//统计答案
	cout << ans;
	return 0;
} 
```

---

## 作者：dyxcj (赞：0)

# [P13710](https://www.luogu.com.cn/problem/P13710)
# 前言
谁懂 $83$ 个数据点的[压迫感](https://www.luogu.com.cn/record/230999262)。
# 正文
## 题意
给你 $a$ 与 $b$ 与 $c$ 与 $d$ 四个值，设你在 $(x,y)$ 点，你可以到达 $(x-a,y-b),(x-a,y+b),(x+a,y-b),(x+a,y+b),(x-c,y-d),(x-c,y+d),(x+c,y-d),(x+c,y+d),(x-b,y-a),(x-b,y+a),(x+b,y-a),(x+b,y+a),(x-d,y-c),(x-d,y+c),(x+d,y-c),(x+d,y+c)$ 这 $16$ 个方向，且要求交替进行，问你最多可以走到哪些格子。\
不想看？再简单点：\
有四个值，分为两组，$(a,b)$ 与 $(c,d)$。其中值的顺序可以调换，但一个组的元素不能到另一个组去，你目前在 $(x,y)$ 这里，你可以选择一个组的元素（形如 $(a,c)$ 等方法是不合法的），再将 $(x,y)$ 增加或减少一个增量（其中元素可以调换，及 $(x-b,y-a)$ 是合法的）,且选择的组要交替进行（上一次选 $(a,b)$ 这一次必须选 $(c,d)$ 反过来亦是），问你最多可以走到哪些格子。\
再来看注意事项：\
你起始点为 $(1,1)$ 不限终点，你开始可以任意选择一种走法（在起始点），你可以走两次（及你第一步选择组 $1$ 加上第一步选择组 $2$ 的和），你不能走出界。
## 思路
复杂的题面但简单的 dfs 题。\
容易想到维护数组 $v_{i,j,k}$ 表示在第 $(i,j)$ 格，上一步类型为 $k$。\
代码实现也不难，只要加上记忆化搜索就可以过，也不是该题解的重点。\
再详细一点，当进入到 $(i,j)$ 时，判断 $v_{i,j,k}$ 是否有无被赋值，有就返回，没有就继续向下搜并赋值。
## 优化
发现要写至少 $16$ 个判断语句（把人写死），考虑减少判断。\
发现如果定义两个值 $e$ 与 $f$（因为 $(a,b)$ 与 $(c,d)$ 本质上只有值不同），根据 $k$ 的值来判断该给 $(e,f)$ 怎样赋值。\
继续来看一个性质：$0\oplus 1=1$ 与 $1\oplus 1=0$，所以传参时可以写成 `k^1` 这样的形式（前提是这是 bool 类型）。\
所以我们将代码的判断语句减到了 $9$ 条（判断给 $(e,f)$ 怎样赋值需要一条）。
# 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,d,sum,x;
bool v[505][505][5],w[505][505];
void dfs(int x,int y,bool z){
    if(v[x][y][z])return;
    sum+=w[x][y]^1;
    v[x][y][z]=1;
    w[x][y]=1;
    int e,f;
    if(z)e=a,f=b;
    else e=c,f=d;
    if(x-e>=1&&y-f>=1)dfs(x-e,y-f,z^1);
    if(x-e>=1&&y+f<=n)dfs(x-e,y+f,z^1);
    if(x+e<=n&&y-f>=1)dfs(x+e,y-f,z^1);
    if(x+e<=n&&y+f<=n)dfs(x+e,y+f,z^1);
    if(x-f>=1&&y-e>=1)dfs(x-f,y-e,z^1);
    if(x-f>=1&&y+e<=n)dfs(x-f,y+e,z^1);
    if(x+f<=n&&y-e>=1)dfs(x+f,y-e,z^1);
    if(x+f<=n&&y+e<=n)dfs(x+f,y+e,z^1);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>a>>b>>c>>d;
    dfs(1,1,1),dfs(1,1,0);
    cout<<sum;
    return 0;
}
```

# 说明
$w$ 数组是判断该格子是否是第一次访问，以方便我们正常计数。\
有不懂的欢迎提问。

---

## 作者：zifeiwoye (赞：0)

# P13710 [NWERC 2023] Klompendans 题解
[题目传送门](https://www.luogu.com.cn/problem/P13710)
## 题目大意
这道题目描述了一个荷兰木屐舞的移动规则问题。舞者在一个 $n\times n$ 的方形网格上跳舞，从左上角 $(1,1)$ 开始，交替使用两种特定的移动方式在网格中移动。要求计算从起点出发，通过这两种交替的移动方式能够到达多少个不同的格子。

## 解题思路

### 问题分析
这是一个典型的图论中的可达性问题，需要使用搜索算法来解决。由于移动方式必须交替进行，我们需要记录当前使用的是哪种移动方式。

### 算法选择
采用广度优先搜索来探索所有可达的格子。广度优先搜索适合解决最短路径和可达性问题，且能保证找到所有可能的路径。

### 关键点
- 使用三维数组记录每个格子是否可以通过某种移动序列到达。
- 交替使用两种移动方式。
- 考虑所有 $8$ 种可能的移动方向（包括正负方向）。
- 确保移动不超出网格边界。

由于n的范围是 $3$ 到 $500$，使用广度优先搜索的时间复杂度是可接受的。

## 代码实现分析

### 数据结构
- 使用三维布尔数组 $v_{x,y,t}$ 记录格子 $(x,y)$ 是否可以通过移动类型 $t$ 到达。
- 使用队列实现广度优先搜索。

### 主要流程
- 初始化时将起点加入队列，标记两种移动类型都可到达起点。
- 从队列中取出当前状态，根据移动类型生成所有可能的下一步。
- 检查新位置是否合法且未被访问过，若合法则标记并加入队列。
- 最后统计所有被标记过的格子数量。

### 细节处理
- 移动方向数组包含了所有 $8$ 种可能的组合。
- 边界检查确保不越界。

- 时间复杂度： $O({n}^{2})$ ，因为最多需要访问每个格子两次（两种移动类型）。
- 空间复杂度： $O({n}^{2})$ ，用于存储访问标记。

## AC Code  
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,a,b,c,d;
bool v[505][505][2];
int ans=0;

struct P{int x,y,t;};

int main(){
    cin>>n>>a>>b>>c>>d;
    queue<P> q;
    q.push({1,1,0});
    q.push({1,1,1});
    v[1][1][0]=v[1][1][1]=1;
    while(!q.empty()){
        P p=q.front();q.pop();
        ans+=(p.x==1&&p.y==1)?1:0;
        if(p.t==0){
            int dx[]={a,a,-a,-a,b,b,-b,-b};
            int dy[]={b,-b,b,-b,a,-a,a,-a};
            for(int i=0;i<8;i++){
                int nx=p.x+dx[i],ny=p.y+dy[i];
                if(nx>0&&ny>0&&nx<=n&&ny<=n&&!v[nx][ny][1]){
                    v[nx][ny][1]=1;
                    q.push({nx,ny,1});
                }
            }
        }else{
            int dx[]={c,c,-c,-c,d,d,-d,-d};
            int dy[]={d,-d,d,-d,c,-c,c,-c};
            for(int i=0;i<8;i++){
                int nx=p.x+dx[i],ny=p.y+dy[i];
                if(nx>0&&ny>0&&nx<=n&&ny<=n&&!v[nx][ny][0]){
                    v[nx][ny][0]=1;
                    q.push({nx,ny,0});
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(v[i][j][0]||v[i][j][1]) ans++;
    cout<<ans-2<<endl;
    return 0;
}

``````

---

## 作者：signed_long_long (赞：0)

# 题意简述

在一个 $n\times n$ 的网格里，你有两种移动方式：

1. 横着（或竖着）移动 $a$ 格，竖着（或横着）移动 $b$ 格

1. 横着（或竖着）移动 $c$ 格，竖着（或横着）移动 $d$ 格

你必须交替执行这两种操作，求你从 $(1,1)$ 能达到的方格数量。

# 题目解法

可以使用 BFS 来搜索，但是为了交替执行这两种操作，要升一维，记录上次执行的操作编号。此外，注意还可以横着移动 $b$ 格，竖着移动 $a$ 格。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a,b,c,d;
const int N=505;
bool vis[N][N][2];
int dx[]={1,-1,1,-1},dy[]={-1,1,1,-1};
struct node{int x,y,z;};
queue<node>q;
int main(){
    cin>>n>>a>>b>>c>>d;
    memset(vis,0,sizeof vis);
    q.push({1,1,0});//入队
    q.push({1,1,1});
    while(!q.empty()){
        int x=q.front().x,y=q.front().y,z=q.front().z;
        q.pop();
        if(vis[x][y][z]) continue;
        vis[x][y][z]=true;
        if(z==1){
            for(int i=0;i<4;i++){//横 a 竖 b
                int nx=x+dx[i]*a,ny=y+dy[i]*b;
                if(nx>=1 and nx<=n and ny>=1 and ny<=n){
                    q.push({nx,ny,0});
                }
            }
            for(int i=0;i<4;i++){//横 b 竖 a
                int nx=x+dx[i]*b,ny=y+dy[i]*a;
                if(nx>=1 and nx<=n and ny>=1 and ny<=n){
                    q.push({nx,ny,0});
                }
            }
        }else{
            for(int i=0;i<4;i++){//横 c 竖 d
                int nx=x+dx[i]*c,ny=y+dy[i]*d;
                if(nx>=1 and nx<=n and ny>=1 and ny<=n){
                    q.push({nx,ny,1});
                }
            }
            for(int i=0;i<4;i++){//横 d 竖 c
                int nx=x+dx[i]*d,ny=y+dy[i]*c;
                if(nx>=1 and nx<=n and ny>=1 and ny<=n){
                    q.push({nx,ny,1});
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) ans+=(vis[i][j][0] or vis[i][j][1]);
    cout<<ans;
    return 0;
}
```

---

## 作者：_Hzq_ (赞：0)

### 题解：P13710 \[NWERC 2023] Klompendans

#### 题意分析

::::info[题目翻译]
#### 题目描述

在传统的荷兰木屐舞中，舞者需要遵循非常特定的动作序列。舞蹈在一个由方形瓷砖组成的方形网格上进行，开始时舞者站在网格左上角的瓷砖上。然后，舞者在两种舞蹈动作之间交替进行，在网格中从一个瓷砖移动到另一个瓷砖，可以持续任意长时间。第一次移动可以是任意一种类型，但之后必须严格交替进行这两种动作。

这两种移动方式类似于国际象棋中马的走法：

- 第一种移动类型：从当前瓷砖移动到一个距离当前瓷砖沿一个轴方向 a 格、另一轴方向 b 格的瓷砖。
- 第二种移动类型：从当前瓷砖移动到一个距离当前瓷砖沿一个轴方向 c 格、另一轴方向 d 格的瓷砖。

由于可以自由交换两个轴并选择每个轴上的移动方向，每种移动类型最多有 8 种执行方式。图 K.1 展示了一个示例舞蹈动作，其中 (a,b) = (1,2)，(c,d) = (2,3)。

![](https://cdn.luogu.com.cn/upload/image_hosting/yu84dg31.png)

:::align{center}
图 K.1：样例输入 3 的图示，展示了一个从 4×4 网格左上角开始、在左下角结束的舞蹈，途中经过蓝色方格。总共有 13 个可到达的方格。红色高亮的三个方格不能成为任何舞蹈表演的一部分。
:::

从左上角瓷砖开始，在跳木屐舞时可以到达多少个不同的瓷砖？不允许走出网格，并且不计算在移动过程中只是跨过的瓷砖。注意，需要计算在某种舞蹈表演中可以到达的所有瓷砖，但不一定是在同一次表演中到达。

#### 输入格式

输入包括：

- 一行一个整数 n（$3\leq n\leq 500$），表示方形的边长。
- 一行两个整数 a 和 b（$1\leq a, b < n$），描述第一种舞蹈移动。
- 一行两个整数 c 和 d（$1\leq c, d < n$），描述第二种舞蹈移动。

#### 输出格式

输出使用这些舞蹈移动可以到达的瓷砖数量。

注：本翻译由 deepseek-R1 提供
::::

题目中提到存在两种移动方式，类似象棋中马的走法，只是把走的距离换成了 $a$ 与 $b$、$c$ 与 $d$ 两种。\
那我们很容易就能想到用 bfs。

:::info[什么是 bfs]
bfs 全称为广度优先搜索，简称广搜或宽搜，其搜索方式类似于树中的层次遍历，优先遍历相同深度的节点，主要使用的数据结构是队列。
:::

在这里，我们使用一个 $bz$ 数组来标记一个点上次被访问时的移动方式，为什么不记录是否访问过呢？因为以两种方式到达同一点后可去的点是不同的，单纯记录是否访问过会导致后面的部分路线会被截断。

### Code

```cpp line-numbers
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,d,res=1;
int bz[507][507];
int main()
{
	cin >> n >> a >> b  >> c >> d;
	int i,j,k,next_x[3][9]={{0},{0,-a,-b,b,a,a,b,-b,-a},{0,-c,-d,d,c,c,d,-d,-c}},next_y[3][9]={{0},{0,b,a,a,b,-b,-a,-a,-b},{0,d,c,c,d,-d,-c,-c,-d}};
	queue<pair<pair<int,int>,int> > q;
	bz[1][1]=1;
	q.push({{1,1},1});
	q.push({{1,1},2});
	while(!q.empty())
	{
		int x=q.front().first.first,y=q.front().first.second,way=q.front().second,nx,ny,nway=way%2+1;
		q.pop();
		for(i=1;i<=8;i++)
		{
			nx=x+next_x[nway][i];
			ny=y+next_y[nway][i];
			if(nx<=0||nx>n||ny<=0||ny>n) continue;
			if(bz[nx][ny]==3||bz[nx][ny]==nway) continue;//以同种方式到达此点就跳过，防止重复搜索
			if(bz[nx][ny]==0)
			{
				res++;
			}
			bz[nx][ny]+=nway;
			q.push({{nx,ny},nway});
		}
	}
	cout << res << endl;
	return 0;
}
```

---

