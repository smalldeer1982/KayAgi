# KOZE - Sheep

## 题目描述

$a$ 行 $b$ 列（$3 \leq a,b \leq250$）的矩阵中：

- 字符 `.` 表示空白字段。

- 字符 `#` 表示一个围栏。

- 字符 `k` 代表绵羊。

- 字符 `v` 代表狼。

狼和羊存活的规则为：
1. 如果一片区域中羊比狼多，全部狼会死掉，**否则**全部羊会死掉。

2. 如果一个地方可以不通过围栏走出矩阵，该地区羊和狼**都会存活**。

求最后能有几只羊与狼。

## 样例 #1

### 输入

```
\n8 8  \n.######.  \n#..k...#  \n#.####.#  \n#.#v.#.#  \n#.#.k#k#  \n#k.##..#  \n#.v..v.#  \n.######.```

### 输出

```
3 1```

# 题解

## 作者：xu222ux (赞：3)

# [KOZE - Sheep](https://www.luogu.com.cn/problem/SP12880)

先来给大家美化一下测试数据：


```cpp

8 8
.######.
#..k...#
#.####.#
#.#v.#.#
#.#.k#k#
#k.##..#
#.v..v.#
.######.
```

```cpp

3 1
```

## 思路

本题一看就知道是一道**搜索**题。我采用的是 **dfs**。

从 $(1,1)$ 开始扫迷宫，扫到一个新的连通块就 **dfs**。

**dfs** 记录此连通块的狼的个数和羊的个数，最后看一下谁赢了，加到答案中即可。

## code

```cpp
//马蜂不太好看，请谅解一下。
#include<bits/stdc++.h>
using namespace std;
int n,m;
int k,v;
bool flag[252][252];
char a[252][252];
void dfs(int x,int y){
	if(x<1||y<1|x>n||y>m||a[x][y]=='#'||flag[x][y])return ;
	if(a[x][y]=='k')k++;
	if(a[x][y]=='v')v++;
    flag[x][y]=true;
	dfs(x+1,y);
	dfs(x,y-1);
	dfs(x-1,y);
	dfs(x,y+1);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
    int ansk=0,ansv=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]!='#'&&!flag[i][j]){
				dfs(i,j);
				if(k>v)ansk+=k;
				else ansv+=v;
				k=v=0;
			}
		}
	}
	cout<<ansk<<' '<<ansv;
   return 0;
}
```


---

## 作者：guozhetao (赞：3)

[更好的阅读体验](https://www.luogu.com.cn/blog/guozhetao/solution-sp12880)

看到此题没有题解，我来水一发。
## 题意
（此题题意很重要，我就是看错题意调试了 7 天的）
$a$ 行 $b$ 列（$3 \leq a,b \leq250$）的矩阵中：

- 字符 `.` 表示空白字段。

- 字符 `#` 表示一个围栏。

- 字符 `k` 代表绵羊。

- 字符 `v` 代表狼。

狼和羊存活的规则为：
1. 如果一片区域中羊比狼多，全部狼会死掉，**否则**全部羊会死掉。

2. 如果一个地方可以不通过围栏走出矩阵，该地区羊和狼**都会存活**。
## 思路
先把能逃脱出去的用 BFS 打上标记，再依次 BFS 算出每个地区存活的狼和羊的数量，最后输出即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define x1 x.front()
#define y1 y.front()
using namespace std;
int main() {
	int a,b;
	scanf("%d%d",&a,&b);
	int kk,l = 0;
	char c[255][255];//存图
	bool d[255][255];//将图转化为bool形式
	for(int i = 1;i <= a;i++) {
		for(int j = 1;j <= b;j++) {
			d[i][j] = 1;
			cin>>c[i][j];
			if(c[i][j] == 'k') kk++;
			if(c[i][j] == 'v') l++;
			if(c[i][j] == '#') d[i][j] = 0;
		}
	}
    //BFS将能直接逃出去的打上标记
	for(int i = 1;i <= a;i++) {
		for(int j = 1;j <= b;j++) {
			if((i == 1 or j == 1) and d[i][j]) {
				queue<int>x,y;
				x.push(i),y.push(j);
				while(!x.empty()) {
					if(d[x1 + 1][y1] and x1 + 1 <= a) {
						d[x1 + 1][y1] = 0;
						x.push(x1 + 1),y.push(y1);
					}
					if(d[x1 - 1][y1] and x1 - 1 >= 1) {
						d[x1 - 1][y1] = 0;
						x.push(x1 - 1),y.push(y1);
					}
					if(d[x1][y1 + 1] and y1 + 1 <= b) {
						d[x1][y1 + 1] = 0;
						x.push(x1),y.push(y1 + 1);
					}
					if(d[x1][y1 - 1] and y1 - 1 >= 1) {
						d[x1][y1 - 1] = 0;
						x.push(x1),y.push(y1 - 1);
					}
					x.pop(),y.pop();
				}
			}
		}
	} 
	//BFS
	for(int i = 1;i <= a;i++) {
		for(int j = 1;j <= b;j++) {
			if(d[i][j]) {
				d[i][j] = 0;
				int e = 0,f = 0;
				queue<int>x,y;
				x.push(i),y.push(j);
				while(!x.empty()) {
					if(c[x1][y1] == 'k') e++;
					if(c[x1][y1] == 'v') f++;
					if(d[x1 + 1][y1] and x1 + 1 <= a) {
						d[x1 + 1][y1] = 0;
						x.push(x1 + 1),y.push(y1);
					}
					if(d[x1 - 1][y1] and x1 - 1 >= 1) {
						d[x1 - 1][y1] = 0;
						x.push(x1 - 1),y.push(y1);
					}
					if(d[x1][y1 + 1] and y1 + 1 <= b) {
						d[x1][y1 + 1] = 0;
						x.push(x1),y.push(y1 + 1);
					}
					if(d[x1][y1 - 1] and y1 - 1 >= 1) {
						d[x1][y1 - 1] = 0;
						x.push(x1),y.push(y1 - 1);
					}
					x.pop(),y.pop();
				}
				//进行判断
				if(e > f) l -= f;
				else kk -= e;
			}
		}
	}
    //输出
	printf("%d %d\n",kk,l);
}
```
------------
附上一组调试数据：




```cpp
7 7
#kvk##.
#####k#
#kvk#k#
#####v#
#vkv#v#
#####.#
kvkv###
```

```cpp
6 7
```
## Update
2022/12/21 更新题解中不完善的地方

---

## 作者：2022_37_yzyUUU (赞：2)

# SP12880
[题目传送门](https://www.luogu.com.cn/problem/SP12880)。

本题连通块板子题，每次搜索记录羊数和狼数，然后**处理**即可。

**处理的具体步骤**

因为羊数大于狼数，所以羊的总数加上本次羊数。

否则狼的总数加上本次狼数。
# AC Code
仅供理解，禁止抄袭。

```
#include<bits/stdc++,h>
using namespace std;
int n,m,k1,k2,ans1,ans2;
char s[251][251];
void bfs(int x,int y){
	if(x<=0||y<=0||x>n||y>m||s[x][y]=='#')return;
	if(s[x][y]=='k')k1++;
	if(s[x][y]=='v')k2++;
	s[x][y]='#';
	bfs(x+1,y);
	bfs(x,y+1);
	bfs(x-1,y);
	bfs(x,y-1);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>s[i][j];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i][j]!='#'){
				k1=k2=0;
				bfs(i,j);
				if(k1>k2)ans1+=k1;
				else ans2+=k2;		
			}
		}
	}
	cout<<ans1<<" "<<ans2;
   return 1;
}
```

---

## 作者：very_easy (赞：2)

这是一道很水的题目，但是本蒟蒻还是调了很久……

首先解释一下各个图形的意义：

`.` 表示空地，狼和羊都可以在上面行走。

`#` 表示栅栏，不可以经过。

`v` 表示狼。

`k` 表示羊。

题目中的样例没有换行我来改一下：

```
8 8 
.######.  
#..k...#  
#.####.#  
#.#v.#.#  
#.#.k#k#  
#k.##..#  
#.v..v.#  
.######.
```

```
3 1
```

# 思路

一道bfs的模板题，我们可以从头到尾将地图扫一遍，如果当前位置上是狼或羊并且还没被访问过，就以这个点为起点去进行 `bfs`，如果当前区域内的狼数量大于羊则羊**全部**死亡，否则狼**全部**死亡，**特别要注意的是如果狼和羊数量相同则狼和羊均不死亡**，还有如果能够离开整个地图狼与羊也不会死亡。

所以这题其实就是一个 `bfs` 模板加一些特判。

# 代码

```c++
#include<bits/stdc++.h>
using namespace std;
char mp[300][300];//地图 
bool vis[300][300];//记录每个位置是否被访问过 
int s,w,dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}},n,m;//dir数组是方向数组 
struct node{
	int x,y;
};
bool check(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m&&!vis[x][y]&&mp[x][y]!='#';
}
void bfs(int x,int y){
	queue<node> q;
	q.push({x,y});
	vis[x][y]=1;
	int a=0,b=0;//a记录羊,b记录狼 
	bool flag=1;
	while(!q.empty()){
		node t=q.front();
		q.pop();
		if(mp[t.x][t.y]=='k'){
			a++;//判断羊的情况 
		}
		if(mp[t.x][t.y]=='v'){
			b++;//判断狼的情况 
		}
		if(t.x==n||t.y==m||t.x==1||t.y==1){
			flag=0;//标记一下如果能走出地图的情况 
		}
		//模板 
		for(int i=0;i<4;i++){
			int dx=t.x+dir[i][0];
			int dy=t.y+dir[i][1];
			if(check(dx,dy)){
				q.push({dx,dy});
				vis[dx][dy]=1;
			}
		}
	}
	//如果能走出地图,狼和羊都不会死亡 
	if(!flag){
		w+=b,s+=a;
		return ;
	}
	if(a>b){
		w+=b;
	}
	if(b>a){
		s+=a;
	}
	//一定要特判！ 
	if(b==a){
		w+=b,s+=a;
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			//这里的()一定不能忘,因为&&的优先级>||,本蒟蒻因为这个问题调了好久 
			if(!vis[i][j]&&(mp[i][j]=='k'||mp[i][j]=='v')){
				bfs(i,j);
			}
		}
	}
	//直接输出就好了 
	cout<<w<<" "<<s;
	return 0;
}

```
~~顺便说一句，其实羊会功夫也没什么了不起，中国的熊猫也会。~~

---

## 作者：封禁用户 (赞：1)

~~又是一道新鲜的灰题~~

建议评级：橙

## 题意

在一个 $a \times b \quad (3 \leq a,b \leq 250)$ 的矩阵中：

- 字符 `.` 表示空白字段。

- 字符 `#` 表示一个围栏。

- 字符 `k` 代表绵羊。

- 字符 `v` 代表狼。

狼和羊存活的规则为：

1. 如果一片区域中羊比狼多，全部狼会死掉，否则全部羊会死掉。

2. 如果一个地方可以不通过围栏走出矩阵，该地区羊和狼都会存活。

## 思路

使用连通块算法，遍历每一个连通块中的羊和狼，如果当前区域内的狼数量大于羊则记录狼的数量，否则记录羊的数量，狼和羊数量相同则不进行记录。

另：顺便美化一下题目中的样例：

```
8 8 
.######. 
#..k...# 
#.####.# 
#.#v.#.# 
#.#.k#k# 
#k.##..# 
#.v..v.# 
.######.
```
```
3 1 
```

## $\color{#52C41A}\texttt{AC}$ 代码

```cpp
#include<iostream>
using namespace std;
int m,n,ans1,ans2,tmp1,tmp2;
char g[255][255];
bool vis[255][255];
int dx[]={-1,1,0,0},dy[]={0,0,-1,1};//方向数组 
void dfs(int x,int y){//dfs 板子
	int nx,ny,i;
	if(x<1||x>m||y<1||y>n) return;
	if(vis[x][y]) return;
	vis[x][y]=1;
	if(g[x][y]=='k') tmp1++;
	if(g[x][y]=='v') tmp2++; 
	for(i=0;i<4;i++){
		nx=x+dx[i];
		ny=y+dy[i];
		
		dfs(nx,ny);
	}
	return;
}
int main(){
	cin>>m>>n;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			cin>>g[i][j];
			if(g[i][j]=='#'){
				vis[i][j]=1;//预处理 
			} 
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(vis[i][j]==0){
				tmp1=0,tmp2=0;
				dfs(i,j);
				if(tmp1>tmp2) ans1+=tmp1;
				else ans2+=tmp2;
			}
		}
	}
	cout<<ans1<<' '<<ans2<<endl;
	return 0;
}
```

---

## 作者：Lavande (赞：1)

# 算法

这是一道很经典的模板题，只需要在搜索时加一些特判就可以了。

# 题目

在 $n$ 行 $m$ 列的地图中：

狼和羊的存活规则为：

1. 如果羊的数目超过狼的数目，羊就会干掉**所有**的狼，相反的话羊就会**全部**死亡。

2. 如果一个地方可以**不通过**围栏走出矩阵，该地区羊和狼都会**存活**。

# 思路

我们可以用**广搜**将地图从头到尾扫一遍，如果当前位置上是狼或羊并且还没被访问过，就对这个点进行搜索。随后再和上面的存活规则特判一遍就可以获得答案。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 305;

int w, s, n, m;
char mp[N][N];
bool vis[N][N];
int dir[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};

struct node{
	int x, y;
};

bool check(int x, int y){
	return x >= 1 && x <= n && y >= 1 && y <= m && !vis[x][y] && mp[x][y] != '#';
}

void bfs(int x, int y){
	queue<node> q;
	q.push({x, y});
	vis[x][y] = 1;
	int a = 0, b = 0;
	int f = 1;
	while(!q.empty()){
		node t = q.front();
		q.pop();
		if(mp[t.x][t.y] == 'k'){
			a ++;
		}
		if(mp[t.x][t.y] == 'v'){
			b ++;
		}
		if(t.x == n||t.y == m||t.x == 1||t.y == 1){
			f = 0;
		}
		for(int i = 0; i < 4; i ++){
			int dx = t.x + dir[i][0];
			int dy = t.y + dir[i][1];
			if(check(dx, dy)){
				q.push({dx, dy});
				vis[dx][dy] = 1;
			}
		}	
	}
	if(!f){
		w += b, s += a;
		return ;
	}
	if(a > b) w += b;
	if(b > a) s += a;
	if(b == a) w += b, s += a;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(false);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			cin >> mp[i][j];
		}
	}
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			if(!vis[i][j] && (mp[i][j] == 'k' || mp[i][j] == 'v')){
				bfs(i, j);
			}
		}
	}
	printf("%d %d", w, s);
	return 0;
}

```



---

## 作者：will1111 (赞：0)

# SP12880 题解

### 解题思路

题目要求将地图分为多个连通块解决，很容易想到搜索的方法。

计算答案需要羊和狼的数量，所以需要在搜索时记录羊和狼的数量。

如果可以走出边界，所有羊和狼都可以存活，所以要在搜索到边界时记录下来。

本篇题解采用 BFS，其实 DFS 也可以解决。

### 测试数据美化

```
8 8
.######.
#..k...#
#.####.#
#.#v.#.#
#.#.k#k#
#k.##..#
#.v..v.#
.######.
```

### 完整代码

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>

using namespace std;

void bfs(vector<vector<char>>&maze,vector<vector<bool>>&st,
		int&cnts,int&cntw,int n,int m,int x,int y) // BFS 函数
{
	int dx[]={1,-1,0,0};
	int dy[]={0,0,1,-1};
	queue<pair<int,int>>q;
	st[x][y]=false;
	q.emplace(x,y);
	int sh=0,wo=0; // 分别记录连通块中羊和狼的个数
	bool flag=false;
	while(!q.empty())
	{
		auto t=q.front();
		q.pop();
		if(maze[t.first][t.second]=='k') // 记录
		{
			sh++;
		}
		if(maze[t.first][t.second]=='v')
		{
			wo++;
		}
		for(int i=0;i<4;i++)
		{
			int tx=t.first+dx[i];
			int ty=t.second+dy[i];
			if(tx<=0||tx>n||ty<=0||ty>m) // 如果可以越界，记录下来
			{
				flag=true;
			}
			else if(st[tx][ty]&&maze[tx][ty]!='#') // 否则继续搜
			{
				st[tx][ty]=false;
				q.emplace(tx,ty);
			}
		}
	}
	if(flag) // 如果可以越界，则羊和狼都可以存活
	{
		cnts+=sh;
		cntw+=wo;
	}
	else
	{
		if(sh>wo) // 如果羊的个数大于狼的个数，则所有羊存活
		{
			cnts+=sh;
		}
		else // 否则所有狼存活
		{
			cntw+=wo;
		}
	}
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	vector<vector<char>>maze(n+1,vector<char>(m+1)); // 记录地图
	vector<vector<bool>>st(n+1,vector<bool>(m+1,true)); // 记录是否走过
	for(int i=1;i<=n;i++) // 读入
	{
		for(int j=1;j<=m;j++)
		{
			cin>>maze[i][j];
		}
	}
	int cnts=0,cntw=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(st[i][j]&&maze[i][j]!='#') // 如果该位置可以走且没有走过，对该点搜索
			{
				bfs(maze,st,cnts,cntw,n,m,i,j);
			}
		}
	}
	printf("%d %d",cnts,cntw); // 输出答案
	return 0;
}
```

---

## 作者：Breath_of_the_Wild (赞：0)

这显然是一道搜索题，找连通块。用 BFS 或 DFS 均可。

循环每一个非墙节点，如果之前未被标记过，就从这里开始扩散到周围，寻找这个区域的连通块。

找的时候，先给它做上标记。如果是羊节点，羊的计数器增加 $1$；如果是狼节点，狼的计数器加 $1$。循环外面判断哪个计数器大，就给对应的答案加上计数器。

代码很简单，就给一个 BFS 吧。
```cpp
void BFS(int x,int y){
	if(x<1||y<1|x>n||y>m||a[x][y]=='#'||vis[x][y]==1){
		return;//出口
	}
	if(a[x][y]=='k') a1++;
	if(a[x][y]=='v') a2++;//标记，统计
	vis[x][y]=1;
	BFS(x,y+1);
	BFS(x+1,y);
	BFS(x,y-1);
	BFS(x-1,y);//向周围扩散
}//a1 为羊的个数，a2 为狼的个数

---

## 作者：zbzbzzb (赞：0)

简单题。

这题可以来枚举每一个连通块，就是先扫一遍数组，然后遇到一个没来过的不是障碍的点，然后从这个点开始 `DFS`，然后边记录狼和羊的数量，然后把它标记为来过，下次就不会再重复扫了。

然后判断狼和羊的数量，如果羊的数量**大于**狼，那么狼死了，将羊的数量加上，否则羊全死了，将狼的数量加上。

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1010][1010];
int n,m,ret1,ret2,cnt1,cnt2,vis[1010][1010];
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
void dfs(int x,int y){
	if(s[x][y]=='k'){//记录
		cnt1++;
	}if(s[x][y]=='v'){
		cnt2++;
	}for(int i=0;i<4;i++){
		int xx=x+dx[i],yy=y+dy[i];
		if(xx>=0&&xx<n&&yy>=0&&yy<m&&s[xx][yy]!='#'&&vis[xx][yy]==0){
			vis[xx][yy]=1;//标记，下次不来了
			dfs(xx,yy);
		}
	}
}int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%s",s[i]);
	}for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if((s[i][j]=='.'||s[i][j]=='k'||s[i][j]=='v')&&vis[i][j]==0){//如果之前没来过
				vis[i][j]=1;
				cnt1=cnt2=0;
				dfs(i,j);
				if(cnt1>cnt2){//判断更新留下来的羊和狼
					ret1+=cnt1;
				}else{
					ret2+=cnt2;
				}
			}
		}
	}printf("%d %d",ret1,ret2);
	return 0;
}

```

---

## 作者：Forever_LYD (赞：0)

模拟，也同样是一道模版。

```cpp
.
```
草，表示两者都可经过的区域。

```cpp
#
```
栅栏，表示两者都不可经过的区域。

那该怎么做？

先看题目数据，很小，显然考虑广搜或加剪枝优化。

我们能否先把整个图扫一遍，那么对于如果这个点没被扫过，并且它不是栅栏或草，就以该点为起点去进行一次广搜。如果在广搜范围内，狼的数量大于羊，羊没。如果羊的数量大于狼，狼没。那相等呢？都活着。同样的，如果栅栏没有包完整，也就是羊狼可以走出去，也都会活着。

所以说，广搜完统计数量再输出即可。

---

## 作者：fp0cy1tz6mn4rd_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP12880)

## 题意
- `.` 代表空地，相连的 `.` 为同一空地
- `#` 代表栅栏，分隔空地
- `k` 代表羊
- `v` 代表狼

如果同一空地上的羊的数量大于狼的数量，则羊会干掉狼，否则狼会吃掉羊。

**如果狼和羊数量相等则狼和羊均不死亡，能够离开整个地图的狼与羊也不会死亡。**
## 思路
`bfs` 扫每一片空地，记录狼和羊的数量。如果能走出地图就额外标记。扫完之后判断狼和羊的数量关系，再记录答案即可。

---

