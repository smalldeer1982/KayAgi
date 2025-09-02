# [ABC325C] Sensors

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc325/tasks/abc325_c

$ H $ 行 $ W $ 列のマス目の上に $ 0 $ 個以上のセンサが配置されています。上から $ i $ 行目、左から $ j $ 列目のマス目を $ (i,\ j) $ と表記します。   
 センサが配置されているマス目の情報は長さ $ W $ の文字列 $ S_1,\ S_2,\ \ldots,\ S_H $ によって与えられ、$ S_i $ の $ j $ 文字目が `#` のとき、またそのときに限り $ (i,\ j) $ にセンサが配置されています。  
 このセンサは上下左右斜めに隣接しているマス目に存在する他のセンサと連動し、一つのセンサとして動作します。 ただし、マス目 $ (x,\ y) $ と $ (x',\ y') $ が上下左右斜めに隣接しているとは、$ \max(|x-x'|,|y-y'|)\ =\ 1 $ であることを指します。  
 また、センサ $ A $ とセンサ $ B $ が連動し、センサ $ A $ とセンサ $ C $ が連動しているとき、センサ $ B $ とセンサ $ C $ も連動することに注意してください。

連動するセンサを一つのセンサと見なしたとき、このマス目の上にあるセンサの個数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ H,\ W\ \leq\ 1000 $
- $ H,\ W $ は整数
- $ S_i $ は各文字が `#` または `.` である長さ $ W $ の文字列
 
### Sample Explanation 1

連動しているセンサを一つのセンサと見なしたとき、 - $ (1,2),(1,3),(2,4),(3,5),(3,6) $ にあるセンサが連動したもの - $ (4,1) $ にあるセンサ - $ (4,3),(5,3) $ にあるセンサが連動したもの の $ 3 $ つのセンサが存在します。

## 样例 #1

### 输入

```
5 6
.##...
...#..
....##
#.#...
..#...```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3
#.#
.#.
#.#```

### 输出

```
1```

## 样例 #3

### 输入

```
4 2
..
..
..
..```

### 输出

```
0```

## 样例 #4

### 输入

```
5 47
.#..#..#####..#...#..#####..#...#...###...#####
.#.#...#.......#.#...#......##..#..#...#..#....
.##....#####....#....#####..#.#.#..#......#####
.#.#...#........#....#......#..##..#...#..#....
.#..#..#####....#....#####..#...#...###...#####```

### 输出

```
7```

# 题解

## 作者：xxr___ (赞：8)

### 前言：
第一眼看到这个题，我想到油田那个题，大体思路就是有几个联通块，用深搜和广搜都可以。
#### 附加知识：
联通块的个数就是从前往后枚举广搜则将这个点入队，将其能到达的符合要求的点入队，被更改过的即为同一个连通块。
#### 广搜代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m; 
char ch[1005][1005];
int dx[]={1,-1,0,0,-1,1,1,-1};
int dy[]={0,0,1,-1,1,1,-1,-1}; 
void bfs(int x,int y){
	queue<pair<int,int> > q;	
	q.push({x,y});
	while(q.size()){
		auto v=q.front();q.pop();
		for(int i=0;i<8;i++){
			int xx=v.first+dx[i],yy=v.second+dy[i];
			if(ch[xx][yy]=='#'&&xx>0&&xx<=n&&yy>0&&yy<=m){
				ch[xx][yy]='.';
				q.push({xx,yy});
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>ch[i][j];
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(ch[i][j]=='#'){
				ans++;
				bfs(i,j);
			}
		}
	}
	cout<<ans;
	return 0;
}
```
#### 深搜代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m; 
char ch[1005][1005];
int dx[]={1,-1,0,0,-1,1,1,-1};
int dy[]={0,0,1,-1,1,1,-1,-1}; 
void dfs(int x,int y){
	ch[x][y]='.';
	for(int i=0;i<8;i++){
		int xx=dx[i]+x;
		int yy=dy[i]+y;
		if(ch[xx][yy]=='#')dfs(xx,yy);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>ch[i][j];
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(ch[i][j]=='#'){
				ans++;
				dfs(i,j);
			}
		}
	}
	cout<<ans;
	return 0;
}
```
## 感谢观看！

---

## 作者：SunSkydp (赞：3)

题意大概是给定一个网格图，其中一些为传感器，对角线、行、列相邻的传感器可以合并为一个传感器，求合并完后的传感器数量。

题意可以转化为求网格中连通块的数量，用 dfs 标记即可，我们给每个连通块一个编号，每到一个未标记的点开始 dfs，并标记新的连通块编号，向周围八个格子扩展。

最后看一下编号到第几号了就是有几个连通块了。
```cpp
#include <bits/stdc++.h>
#define _for(i, a, b) for(int i = (a); i<= (b); i++)
using namespace std;

int a[1005][1005], cnt, n, m;
char c[1005][1005];
int xy[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1},
{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
bool init(int x, int y) {
	return true;
}
void dfs(int x, int y) {
	for(int i = 0; i < 8; i++) {
		int xx = x + xy[i][0], yy = y + xy[i][1];
		if(init(xx, yy) && c[xx][yy] == '#' && !a[xx][yy]) {
			a[xx][yy] = cnt;
			dfs(xx, yy);
		}
	}
}
int main() {
	int n, m; scanf("%d %d", &n, &m);
	_for(i, 1, n) _for(j, 1, m) cin >> c[i][j];
	_for(i, 1, n) _for(j, 1, m) if(!a[i][j] && c[i][j] == '#') {
		a[i][j] = ++cnt;
		dfs(i, j);
	}
	cout << cnt << endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

一道搜索好题，用连通块算法就行

这道题一下子就让我想起了 [P1451](https://www.luogu.com.cn/problem/P1451)

`dfs`：

思路很简单，依次向八个方向搜索即可

`bfs`也行，~~只不过我懒得写了~~

代码：

```cpp
#include<iostream>
using namespace std;
int m,n,ans;
bool g[1005][1005];
void dfs(int x,int y){//深搜
	g[x][y]=0;//渲染
	if(g[x-1][y]==1) dfs(x-1,y);
	if(g[x+1][y]==1) dfs(x+1,y);
	if(g[x][y-1]==1) dfs(x,y-1);
	if(g[x][y+1]==1) dfs(x,y+1);
	if(g[x+1][y-1]==1) dfs(x+1,y-1);
	if(g[x+1][y+1]==1) dfs(x+1,y+1);
	if(g[x-1][y+1]==1) dfs(x-1,y+1);
	if(g[x-1][y-1]==1) dfs(x-1,y-1);
	
}
int main(){
	cin>>m>>n;
	char s;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			cin>>s;
			if(s=='#'){
				g[i][j]=1;
			}
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(g[i][j]==1){
				ans++;
				dfs(i,j);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：__Emerald__ (赞：1)

这道题跟数水塘大致一样，就是连通块的方向加了 $4$ 个斜向的。

我们深度优先搜索每个 `#`，每次搜索到 `#` 时变成 `.`（这个步骤是防止之后再次搜索到这个点），并且把答案加一（这个步骤在主函数里做），并且把这个点所在的连通块全部变成 `.`。

深搜代码如下：（为防抄袭，剩余部分就不放了）
```
int dx[8] = {-1,-1,0,1,1,1,0,-1},dy[8] = {0,1,1,1,0,-1,-1,-1};
void dfs(int x,int y){
	a[x][y] = '.';
	for (int i = 0;i < 8;i++){
		int px = x + dx[i],py = y + dy[i];
		if (px >= 1 && px <= n && py >= 1 && py <= m && a[px][py] == '#') dfs(px,py);
	}
}
```

---

## 作者：SiriusIV (赞：0)

# 算法

这道题是典型的深度优先搜索算法例题。

# 思路

在每一个 `#` 处进行搜索，将其所有联通的 `#` 换为 `.` 并将统计变量 $ans$ 增加 $1$。

# 代码

```cpp
 #include<bits/stdc++.h>
using namespace std;
char mp[2005][2050];
int n,m;
int dir[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};//坐标偏移量数组（八个方向）
void dfs(int x,int y)//深度优先搜索
{
    int fx,fy;
    for(int i=0;i<8;i++)//遍历八个方向
    {
    	fx=dir[i][0]+x;
    	fy=dir[i][1]+y;
    	if(fx>=1&&fx<=n&&fy>=1&&fy<=m&&mp[fx][fy]=='#')
    	{
            mp[fx][fy]='.';//替换联通的#
    		dfs(fx,fy);
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
			cin>>mp[i][j];
		}
	} 
    int ans=0;//统计变量记得初始化
    for(int i=1;i<=n;i++)
	{
        for(int j=1;j<=m;j++)
		{
            if(mp[i][j]=='#')//在每一个#处搜索
			{
                mp[i][j]='.';
                dfs(i,j);
                ans++;//统计变量加一
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：CheZiHe929 (赞：0)

# AT_abc325_c 题解

### 原题链接

[**Atcoder**](https://atcoder.jp/contests/abc325/tasks/abc325_c)

[**洛谷**](https://www.luogu.com.cn/problem/AT_abc325_c)

### 简要题意

给你一个 $h$ 行 $w$ 列的由 `#` 传感器和 `.` 空地组成的网格图。如果一个传感器 $A$ 是另一个传感器 $B$ 的周围八个格子（即设 $A$ 传感器的位置为 $(x_a,y_a)$，$B$ 传感器的位置为 $(x_b,y_b)$，那么需要满足 $\max(|x_a-x_b|,|y_a-y_b|) = 1$）时，这两个传感器就属于一个传感器。问最终该网格图中的传感器的数量。

$1 \leq h,w \leq 1000$。

### 简要思路

考虑到矩阵并不是很大，所以我们可以暴力搜索。针对于每一个传感器，如果它没有被遍历过，我们就以它为起始点不断向下进行搜索，并将搜索到的点标记上。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'

int dx[]={0,1,1,1,0,-1,-1,-1};
int dy[]={1,1,0,-1,-1,-1,0,1};//朝八个位置的偏移量

int h,w,ans;
char c[1005][1005];
bool f[1005][1005];//判断是否遍历过

bool check(int x,int y){//判断搜索到的这个点是否合法
	if(x>=1&&x<=h&&y>=1&&y<=w&&!f[x][y]&&c[x][y]=='#')return true;
	else return false;
}

void dfs(int x,int y){//朴素的搜索
	for(int i=0;i<8;i++){//枚举八个位置
		int xx=x+dx[i];
		int yy=y+dy[i];

		if(check(xx,yy)){
			f[xx][yy]=1;
			dfs(xx,yy);//满足条件继续往下搜索
		}
	}
	return;
}

signed main(){
	std::cin>>h>>w;
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			std::cin>>c[i][j];

	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			if(!f[i][j]&&c[i][j]=='#'){//遍历到了一个新的未遍历过的传感器的位置
				dfs(i,j);
				ans++;
			}

	std::cout<<ans<<endl;
	return 0;
}
```

### AC 记录

[**Atcoder**](https://atcoder.jp/contests/abc325/submissions/46881993)

[**洛谷**](https://www.luogu.com.cn/record/131272629)

**THE END.**

**THANK YOU.**

---

## 作者：jess1ca1o0g3 (赞：0)

这道题是非常典型的搜索题，而且是联通块。

我们可以用广度优先搜索来搜联通块，搜完一个传感器就将其置为 `.`。

整个题目的思路和 [P1451 求细胞数量](https://www.luogu.com.cn/problem/P1451) 完全一样，只需要把数组开到 $1000$ 就行。

[赛时 AC 代码](https://atcoder.jp/contests/abc325/submissions/46798524)

嫌麻烦的看这里：

（~~压了行~~）

```cpp
#include<iostream>
int dx[8]={-1,-1,-1,1,1,1,0,0},
dy[8]={-1,0,1,1,0,-1,1,-1},ans,n,m;
char l[1005][1005];
inline void bfs(int p,int q){
	int x,y,t=0,w=1,h[1005][3];
	l[p][q]='.';
	for(int i=0;i<8;i++){
		x=p+dx[i],y=q+dy[i];
		if(x>=0&&x<n&&y>=0&&y<m&&l[x][y]=='#') bfs(x,y);
	}
	
}
inline void init(){
	std::cin>>n>>m;
	for(int i=0;i<n;i++) for(int j=0;j<m;j++) std::cin>>l[i][j];
}
inline void work(){
	for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(l[i][j]=='#') bfs(i,j),ans++;
}
inline void print(){
	std::cout<<ans<<std::endl;
}
signed main(){
	init();
	work();
	print();
	return 0;
}
```

这里将广搜改成了递归的形式，更容易理解，也更好写。

（~~其实是我蒻~~）

---

## 作者：Dream_poetry (赞：0)

### 题目大意：
将 ```#``` 算为一个点，一个点和以它为中点的九宫格内的点算为一组，求出组的数量。

### 思路：
一看数据范围，是道模拟题~~这次 J 组 T3 大模拟我吐血~~。

我们编辑一个函数，每当找到一个点，直接通过**偏移量**，将它周围的点清理为 ```.```，继续向下搜索。

**注意继续往下处理时的量。**

然后，就是代码了：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
char c[10005][10995];
int dx[10]={-1,-1,-1,0,1,1,1,0};
int dy[10]={-1,0,1,1,1,0,-1,-1};
void cl(int x,int y){
	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			if (c[x+dx[i]][y+dy[j]]=='#'){
				c[x+dx[i]][y+dy[j]]='.';
				cl(x+dx[i],y+dy[j]);
			}
		}
	}
}

int ans;

signed main(){
	cin>>n>>m;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			cin>>c[i][j];
		}
	}	
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			if (c[i][j]=='#'){
				ans++;
				cl(i,j);
			}
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：aaron0919 (赞：0)

# [AT_abc325_c の题解](https://www.luogu.com.cn/problem/AT_abc325_c)

### 题目大意

求连通块个数。

### 理性分析

这题是个求连通块个数的题，我们可以通过 bfs 或 dfs 的方法求解。

bfs 的话搞一个队列，里面放未扩展的块，dfs 的话，只需要将整个连通块递归清除即可。

### 代码实现

我们可以写一个函数，来扩展一个连通块并递归清除，只用遍历整张图，每个点都跑一遍就出来了。

### code

[AC 记录](https://atcoder.jp/contests/abc325/submissions/46878242)

```cpp
#include <bits/stdc++.h>

const int N = 1005;
const int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
const int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};

char cmap[N][N];
int ans, n, m;

bool check(int x, int y)
{
	return x < 0 || y < 0 || x >= n || y >= m || cmap[x][y] == '.';
}

void dfs(int x, int y)
{
	cmap[x][y] = '.';
	for (int i = 0; i < 8; i++)
	{
		if (!check(x + dx[i], y + dy[i]))
		{
			dfs(x + dx[i], y + dy[i]);
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", cmap[i]);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (cmap[i][j] == '#')
			{
				dfs(i, j);
				ans++;
			}
		}
	}
	printf("%d", ans); // 抄代码不要脸！！！ /&_&\
}
```

---

## 作者：FL_sleake (赞：0)

### 题意简述

给定一个 $n \times m$ 的区域，若 $s_{i,j}$ 为 ```#```，则 $(i,j)$ 处有一个传感器。若一个传感器 $A$ 周围八个格子中有另一个传感器 $B$，称它们为相邻的。传感器的相邻关系可以传递。所有相邻的传感器视作一个，问有多少个传感器。 

### 解题思路

相当于求连通块的数量。注意一个传感器上下左右、左上、左下、右上、右下的传感器都视作联通的。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,vis[2010][2010],ans=0;
string s[200010];
int dx[20]={0,1,1,1,-1,-1,-1,0,0};
int dy[20]={0,0,1,-1,0,1,-1,1,-1};
void dfs(int x,int y){
	vis[x][y]=1;
	for(int i=1;i<=8;i++){
		int tx=x+dx[i],ty=y+dy[i];
		if(tx<1||ty<1||tx>n||ty>m) continue;
		if(!vis[tx][ty]&&s[tx][ty]=='#') dfs(tx,ty);
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>s[i],s[i]=" "+s[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i][j]=='#'&&!vis[i][j]) dfs(i,j),ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

