# Robot Factory

## 题目描述

You have received data from a Bubble bot. You know your task is to make factory facilities, but before you even start, you need to know how big the factory is and how many rooms it has. When you look at the data you see that you have the dimensions of the construction, which is in rectangle shape: N x M.

Then in the next N lines you have M numbers. These numbers represent factory tiles and they can go from 0 to 15. Each of these numbers should be looked in its binary form. Because from each number you know on which side the tile has walls. For example number 10 in it's binary form is 1010, which means that it has a wall from the North side, it doesn't have a wall from the East, it has a wall on the South side and it doesn't have a wall on the West side. So it goes North, East, South, West.

It is guaranteed that the construction always has walls on it's edges. The input will be correct.

Your task is to print the size of the rooms from biggest to smallest.

## 样例 #1

### 输入

```
4 5
9 14 11 12 13
5 15 11 6 7
5 9 14 9 14
3 2 14 3 14```

### 输出

```
9 4 4 2 1```

# 题解

## 作者：GI录像机 (赞：3)

### 题目大意：
给出一个 $N$ 行 $M$ 列的矩阵，已知每个点的上下左右是否能通行，问有多少个互相不能到达的区块，从小到大排序输出。

### 思路：
我们可以先预处理出每个十进制数的上下左右是否有墙，然后对于每个未被访问的点进行DFS，DFS中记录共有几个点在这一个区块内，将数量加入堆，并把这些点都标记为已访问，再找下一个未被访问过的位置进行以上操作，直到所有点都被访问过。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, a[1010][1010], d[16][4];//d[i][j]表示数为i时j方向是否有墙
int dx[4] = {0, 1, 0, -1}, dy[4] = {-1, 0, 1, 0}, cnt;//方向数组
priority_queue<int>q;//STL
bool vis[1010][1010];
void dfs(int x, int y) {
	vis[x][y] = 1;
	cnt++;//累加，由于每个点至多被访问一次所以不存在重复
	for (int i = 0; i <= 3; i++) {
		int xx = x + dx[i], yy = y + dy[i];
		if (d[a[x][y]][i] || vis[xx][yy])continue;
		dfs(xx, yy);
	}
}
int main() {
	cin >> n >> m;
	memset(vis, false, sizeof(vis));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> a[i][j];
	//预处理d[i][j]
	for (int i = 1; i <= 15; i++) {
		int num = i;
		for (int j = 3; j >= 0; j--) {
			if (num - (1 << j) >= 0) {
				num -= (1 << j);
				d[i][j] = 1;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!vis[i][j]) {//寻找下一个未被访问过的点
				cnt = 0;//归零
				dfs(i, j);
				q.push(cnt);//入堆
			}
		}
	}
	while (!q.empty()) {//输出所有区块大小
		cout << q.top() << " ";
		q.pop();
	}
	return 0;
}
```


---

## 作者：tallnut (赞：2)

DFS 简单题。
# 思路
**采用 DFS 求连通块**。把整个矩阵扫一遍，如果这个元素还没有遍历过，就进行一次 DFS，在过程中一边累加这个房间的面积，一边打上已经访问的标记。用**位运算**判断能否向上下左右扩展。最后把所有房间的大小排个序即可。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/145198446)。
```
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1010;
int n,m,cnt;
int a[N][N];
bool visited[N][N];
//用于存储每个房间的大小
vector<int> v;
bool cmp(int a,int b) { return a > b; }
void dfs(int x,int y)
{
	cnt++;
	visited[x][y] = true;
	//向上扩展
	if (x > 1 && (!visited[x - 1][y]) && ((a[x][y] & 8) == 0)) dfs(x - 1,y);
	//向下扩展
	if (x < n && (!visited[x + 1][y]) && ((a[x][y] & 2) == 0)) dfs(x + 1,y);
	//向左扩展
	if (y > 1 && (!visited[x][y - 1]) && ((a[x][y] & 1) == 0)) dfs(x,y - 1);
	//向右扩展
	if (y < m && (!visited[x][y + 1]) && ((a[x][y] & 4) == 0)) dfs(x,y + 1);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= m;j++)
			cin >> a[i][j];
	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= m;j++)
			if (!visited[i][j])
			{
				cnt = 0;
				//dfs寻找整个房间的大小，并把他们全设为visited
				dfs(i,j);
				v.push_back(cnt);
			}
	sort(v.begin(),v.end(),cmp);
	for (int i = 0;i < v.size();i++)
		cout << v[i] << ' ';
}
```

---

## 作者：Rain_G (赞：1)

### 题目大意

给你一个 $n \times m$ 的矩阵，其中的每个数都代表着这个点与上下左右四个点是否联通，在输出各个联通块的大小。

### 输出
计算联通块大小时，计算连通块的数量，在进行排序，从大到小输出即可。

### 求联通块
输入这个矩阵的十进制后，先处理将其转为二进制，再记录能走到哪个点，用四个数组记录如 $s _ {i,j} = 1$ 代表可以往上走。而其他数组也代表着左右和下，用一个数组记录当前点是否走过，如果没访问过，跑一遍 DFS，计算每个联通块的大小，顺便记录哪个点访问过，避免重复访问。感觉自己的做法有很多优化的，思路这么简单都调了好久。

### 代码
```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int N = 1010;
const int M = 1e6 + 20;
int n, m, cnt = 1;
int a[N][N], ans[M];
bool vis[N][N];
int s[N][N], x[N][N], z[N][N], y[N][N];
int ddd[] = { 8, 4, 2, 1};
int dfs( int i, int j)
{
	if( vis[i][j] )
		return 0;
	vis[i][j] = true;
	int sum = 1;
	if( s[i][j] )
		sum += dfs( i - 1, j);
	if(  x[i][j] )
		sum += dfs( i + 1, j);
	if(  y[i][j] )
		sum += dfs( i, j + 1);
	if(  z[i][j] )
		sum += dfs( i, j - 1);
	return sum;
}
signed main()
{
	memset( vis, false, sizeof vis);
	scanf("%d%d", &n, &m);
	for( int i = 1; i <= n; i++)
		for( int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);
	for( int i = 1; i <= n; i++)
		for( int j = 1; j <= m; j++)
			for( int k = 0; k < 4; k++)
			//上右下左 
				if(!(a[i][j] & ddd[k]))//位运算 
				{
					if( k == 0 )
						s[i][j] = 1;
					if( k == 1)
						y[i][j] = 1;
					if(k == 2)
						x[i][j] = 1;
					if( k == 3)
						z[i][j] = 1;
				}
	for( int i = 1; i <= n; i++)
			for( int j = 1; j <= m; j++)
				if(!vis[i][j])
					ans[cnt++] = dfs( i, j);
	sort( ans + 1, ans + cnt + 1);
	for( int i = cnt; i >= 2; i--)
		printf("%d ", ans[i]);
	return 0;
}
```


---

## 作者：CommandSR (赞：1)

## 题意简化
给定 $N$ 行 $M$ 列的地图，地图中的值表示其上下左右能否通行，求最大连通块数量。

## 基本思路：DFS

### 处理二进制

本题中 $a_{i,j}$ 的值的四位二进制表示 $(i,j)$ 这个点上下左右能否通行，我们需要用一个数组存储每个值对应的允许通行情况。

可以采用常规方法对每个值求二进制，但是由于 $0 \leq a_{i,j} \leq 15$ 可以选择打表。

于是有了：
```cpp
string bin[16] =
{"0000", "0001", "0010", "0011",
 "0100", "0101", "0110","0111",
"1000", "1001", "1010", "1011",
 "1100", "1101", "1110", "1111"};

```

### DFS 处理连通块

此题要求输出所有连通块大小，套上连通块 DFS 模板，这里不过多赘述。
```cpp
for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (!vis[i][j])
			{
				res = 0;
				dfs(i, j);
				ans[++cnt] = res;
			}
		}
	}
```
---

搜索时要注意预处理出的墙信息 $bin_{a_{x,y},i}$ 和方向数组 $dx_i$，$dy_i$ 中的 $i$ 要统一。

```cpp
void dfs(int x, int y)
{
	res ++ ;
	vis[x][y] = 1;
	for (int i = 0; i < 4; i++)
	{
		int xx = x + dx[i];
		int yy = y + dy[i];
		if (xx < 1 || xx > n || yy < 1 || yy > m) continue ;
		if (vis[xx][yy]) continue ;
		if (bin[a[x][y]][i] - '0' == 1) continue ;
		dfs(xx, yy);
	}
}
```

### 输出所有连通块大小

每次发现一个连通块将 $res$ 置 $0$ ，dfs 时每到一个块将 $res$ 自增，最后 $res$ 的值就是当前这个连通块的大小，将这个值记录到数组中。

最后输出时从大到小排序即可。

## AC Code

更多细节见注释。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a[1010][1010];
// 预处理 a[i][j] 对应的通行情况
string bin[16] =
{"0000", "0001", "0010", "0011",
	"0100", "0101", "0110","0111",
	"1000", "1001", "1010", "1011",
	"1100", "1101", "1110", "1111"};
int res = 0;
int ans[1000010], cnt = 0;
bool vis[1010][1010];
// 注意方向数组的方向和bin数组相对应的方向相同
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
void dfs(int x, int y)
{
	// 连通块大小++
	res ++ ;
	// 标记这个点走过
	vis[x][y] = 1;
	for (int i = 0; i < 4; i++)
	{
		int xx = x + dx[i];
		int yy = y + dy[i];
		if (xx < 1 || xx > n || yy < 1 || yy > m) continue ;
		if (vis[xx][yy]) continue ;
		// 该方向不可通行，不搜
		if (bin[a[x][y]][i] - '0' == 1) continue ;
		dfs(xx, yy);
	}
}
int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			cin >> a[i][j];
	}
	// 处理连通块 DFS 模板
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= m; j++)
	{
		if (!vis[i][j])
		{
			res = 0;
			dfs(i, j);
			ans[++cnt] = res;
			// 将每一个连通块大小加入数组
		}
	}	
	// 连通块大小排序
	sort(ans + 1, ans + 1 + cnt);
	// 降序输出
	for (int i = cnt; i >= 1; i--) cout << ans[i] << ' ';
	return 0;
}
```

拒绝抄袭！

---

## 作者：DrDuck (赞：0)

# 基本思路 #
这道题的本质就是让我们用 DFS 求各个联通块的大小，不过格子与格子之间有墙。

那么怎么记录墙的位置呢？开一个三维数组，$ditu_{i,j,k}$ 表示在第 $i$ 行第 $j$ 列的瓷砖上，在 $k$ 方向上是否有墙，其中 $k = 0$ 代表上面， $k = 1$ 代表右边，$k = 2$ 代表下面， $k = 3$ 代表左边。然后对每个联通块跑一遍 DFS，如果撞到墙了就不走，统计联通块大小即可。
# CODE #

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, cnt;
int h[1024][1024];
bool ditu[1024][1024][4];
bool vis[1024][1024];
string p[16] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};//十进制转二进制
priority_queue<int> q;
void dfs(int a, int b)
{
	if (vis[a][b])
	{
		return;
	}
	vis[a][b] = true;
	cnt++;
	if (!ditu[a][b][0] && a - 1 > 0)
	{
		dfs(a - 1, b);
	}
	if (!ditu[a][b][1] && b + 1 <= m)
	{
		dfs(a, b + 1);
	}
	if (!ditu[a][b][2] && a + 1 <= n)
	{
		dfs(a + 1, b);
	}
	if (!ditu[a][b][3] && b - 1 > 0)
	{
		dfs(a, b - 1);
	}	
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> h[i][j];
			string s = p[h[i][j]];
			ditu[i][j][0] = s[0] - '0';
			ditu[i][j][1] = s[1] - '0';
			ditu[i][j][2] = s[2] - '0';
			ditu[i][j][3] = s[3] - '0';
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (!vis[i][j])
			{
				cnt = 0;
				dfs(i, j);
				q.push(cnt);
			}
		}
	}
	while (!q.empty())
	{
		cout << q.top() << " ";
		q.pop();
	}
	return 0;
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
一间房子，每一块瓷砖上都可能有上右下左四面墙，被墙隔着的地方都不能走，问这个房子里所有房间排序后的大小。

其实就是在几个点四周建墙，求排序后的所有联通块大小。
## 大体思路
由于存墙是二进制存的，所以我们查有没有墙的时候右移之后与就可以，我们来做 DFS 找连通块，存下来大小之后排序输出就可以了，注意边界。

最大复杂度不超过 $O(NM)$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void write(long long x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9){
		write(x/10);
	}
	putchar(x%10+'0');
	return ;
}
int n=read(),m=read();
int a[1005][1005];
bool vis[1005][1005];
priority_queue<int> q;//自动排序就行 
int sum=1;
void dfs(int x,int y){
	if(x+1<=n&&!vis[x+1][y]&&!((a[x][y]>>1)&1)&&!((a[x+1][y]>>3)&1)){//向下走，当前点的下面和要走到点的上面不能有墙 
		sum++;
		vis[x+1][y]=1;
		dfs(x+1,y);
	}
	if(y+1<=m&&!vis[x][y+1]&&!((a[x][y]>>2)&1)&&!(a[x][y+1]&1)){//向右走，当前点的右面和要走到点的左面不能有墙 
		sum++;
		vis[x][y+1]=1;
		dfs(x,y+1);
	}
	if(x-1>=1&&!vis[x-1][y]&&!((a[x][y]>>3)&1)&&!((a[x-1][y]>>1)&1)){//向上走，当前点的上面和要走到点的下面不能有墙 
		sum++;
		vis[x-1][y]=1;
		dfs(x-1,y);
	}
	if(y-1>=1&&!vis[x][y-1]&&!(a[x][y]&1)&&!((a[x][y-1]>>2)&1)){//向左走，当前点的左面和要走到点的右面不能有墙 
		sum++;
		vis[x][y-1]=1;
		dfs(x,y-1);
	}
}
int main(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!vis[i][j]){//还没被查到过，不属于之前的任何一个连通块 
				vis[i][j]=1;
				dfs(i,j);
				q.push(sum);//深搜完之后把答案放进去 
				sum=1;//最小也不能小于1，毕竟还有当前这块 
			}
		}
	}
	while(!q.empty()){
		write(q.top());
		q.pop();
		putchar(' ');
	}
	return 0;
}
```

---

## 作者：__Creeper__ (赞：0)

### 思路

这题其实就是求连通块大小的问题。关键的是如何判断上下左右是否有墙，这里可以通过位运算按位与来判断。

比如一个数字 $10$，它的二进制表示为 $1010$。

那么 $10 \land 8$，即 $1010 \land 1000$ 的结果为 $8$。

同理：$10 \land 4$ 的结果为 $0$，$10 \land 2$ 的结果为 $2$，$10 \land 1$ 的结果为
$0$。

发现有什么规律？

我们得到：如果一个数 $a$ 的第 $i$ 位为 $1$（从右往左，从 $0$ 开始），那么 $a \land 2^i$ 的结果不为 $0$，否则为 $0$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1005, M = 1e7 + 5;
int n, m, k, cnt, a[N][N], ans[M];
int dx[10] = {-1, 0, 1, 0};
int dy[10] = {0, 1, 0, -1};
int b[10] = {8, 4, 2, 1}; 
bool vis[N][N];

void dfs ( int x, int y )
{
	vis[x][y] = 1;
	cnt++;
	for ( int i = 0; i < 4; i++ )
	{
		int nx = x + dx[i], ny = y + dy[i];
		if ( a[x][y] & b[i] ) continue; // 按位与判断
		if ( vis[nx][ny] || nx < 1 || ny < 1 || nx > n || ny > m ) continue;
		dfs ( nx, ny );
	}
}

int main()
{
	cin >> n >> m;
	for ( int i = 1; i <= n; i++ ) for ( int j = 1; j <= m; j++ ) cin >> a[i][j];
	for ( int i = 1; i <= n; i++ )
	{
		for ( int j = 1; j <= m; j++ )
		{
			if ( !vis[i][j] ) 
			{
				cnt = 0;
				dfs ( i, j );
				ans[++k] = cnt;
			}
		}
	}
	sort ( ans + 1, ans + k + 1 ); // 别忘了排序
	for ( int i = k; i >= 1; i-- ) cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：lhs_chris (赞：0)

[Robot Factory](https://codeforces.com/problemset/problem/1600/J)
# 思路
这题其实就是另类一点的连通块问题。每一步都要通过位运算判断可否前行。这题关键的是如何判断能否前向，其实通过与运算就可以解决这个问题。
# 代码
```cpp
#include<bits/stdc++.h>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#define ll long long
using namespace std;
const int N=1e5+10;
const int M=2023;
const int inf=0x3f3f3f3f;
int n,m;
int a[1145][1145];
int vis[1145][1145];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int dk[]={4,1,2,8};//判断是否可行
int h[N],num;
int ans;
bool cmp(int x,int y)
{
	return x>y;
}
void dfs(int x,int y)
{
	ans++;
	for(int i=0;i<4;i++)
	{
		int nx=x+dx[i];
		int ny=y+dy[i];
		int k=a[x][y]&dk[i];//0才可以通过
		if(nx>=1 and nx<=n and ny>=1 and ny<=m and vis[nx][ny]==0 and !k)
		{
			vis[nx][ny]=1;
			dfs(nx,ny);
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
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(vis[i][j]==0)
			{
				ans=0;
				vis[i][j]=1;
				dfs(i,j);
				num++;
				h[num]=ans;
			}
		}
	}
	sort(h+1,h+num+1,cmp);
	for(int i=1;i<=num;i++)
	{
		cout<<h[i]<<" ";
	}
	return 0;
}
```

---

## 作者：ForeverCC (赞：0)

### 提示

判断是否能上下左右走可以用位运算。

### 思路

记录每个点是否到达过，如果没到达过，记下这个连通块的大小。

这里介绍一下 `&` 这个位运算操作：

`&` 表示按位于操作。（就是在二进制下每一位逻辑与）

比如一个数字 `5`，它的二进制表示为 `0101`。

那么 `5&4`，即 `0101&0100` 的结果为 $4$。

而 `5&2`，即 `0101&0010` 的结果为 $0$。

发现有什么规律？

这里直接上结论：如果一个数 $x$ 的第 $i$ 位为 $1$，（从右往左，从 $0$ 开始）那么 $x$ `&` $2^i$ 的结果不为 $0$。

然后这个搜索就很简单了！

记得最后将答案排序。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[1005][1005],ans[10000005],cnt;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1},w[]={8,4,2,1};//分别是 2^3 2^2 2^1 2^0 代表第3,2,1,0位 
bool vis[1005][1005];
int dfs(int x,int y){
	if(vis[x][y]||x<1||y<1||x>n||y>m)return 0;
	vis[x][y]=1;
	int sum=1;
	for(int i=0;i<4;i++){
		if(a[x][y]&w[i])continue;//位运算判断 
		sum+=dfs(x+dx[i],y+dy[i]);
	}
	return sum;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!vis[i][j])
				ans[++cnt]=dfs(i,j);//记下这个连通块的大小 
	sort(ans+1,ans+cnt+1);//答案排序 
	for(int i=cnt;i>=1;i--)
		printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：Ninelife_Cat (赞：0)

### 题目大意

有一个 $n\times m$ 的网格，每个网格上是一个 $[0,15]$ 之间的整数，它的二进制形式满足以下条件：

- 以向上为正北方向。
- 如果它的第一位为 $1$，表示不能走到它北面的格子。
- 如果它的第二位为 $1$，表示不能走到它东面的格子。
- 如果它的第三位为 $1$，表示不能走到它南面的格子。
- 如果它的第四位为 $1$，表示不能走到它西面的格子。

（例如，数字 $10$ 的二进制形式是 $1010$，这意味着它不能走到它北面和南面的格子，但可以走到它东面和西面的格子）

请求出这个网格中所有连通块的大小，按降序输出。

### 思路

先存下每个点的二进制形式，然后遍历整个网格，把能相互到达的两个格子中间连一条无向边，就会得到一张图。

之后暴力遍历整张图，计算出每个连通块的大小就行了。


```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define ri register
#define pb push_back
#define int long long
#define reset(x,y) memset((x),(y),sizeof((x)))
using namespace std;
inline int read()
{
	ri int x=0,f=0;ri char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^'0'),c=getchar();
	return f?-x:x;
}
const int N=1e6+10;
int Head[N],Next[N<<1],To[N<<1],Cnt;
inline void Add(int x,int y) {Next[++Cnt]=Head[x];Head[x]=Cnt;To[Cnt]=y;}
int n,m,x,vis[N],flag[N][5],cnt;
vector<int> v;
inline void Dfs(int x)
{
	++cnt,vis[x]=1;
	for(ri int i=Head[x];i;i=Next[i])
		if(!vis[To[i]]) Dfs(To[i]);
}//dfs计算连通块大小 
signed main()
{
	n=read();m=read();reset(flag,-1);
	for(ri int i=1;i<=n;++i)
		for(ri int j=1;j<=m;++j)
			x=read(),
			flag[(i-1)*m+j][1]=x&8,
			flag[(i-1)*m+j][2]=x&4,
			flag[(i-1)*m+j][3]=x&2,
			flag[(i-1)*m+j][4]=x&1;//把一个点(x,y)转成一个数(x-1)*m+y储存,并分离二进制位 
	for(ri int i=1;i<=n;++i)
		for(ri int j=1;j<=m;++j)
		{
			if(!flag[(i-1)*m+j][1]&&!flag[(i-2)*m+j][3]) Add((i-1)*m+j,(i-2)*m+j),Add((i-2)*m+j,(i-1)*m+j);
			if(!flag[(i-1)*m+j][2]&&!flag[(i-1)*m+j+1][4]) Add((i-1)*m+j,(i-1)*m+j+1),Add((i-1)*m+j+1,(i-1)*m+j);
			if(!flag[(i-1)*m+j][3]&&!flag[i*m+j][1]) Add((i-1)*m+j,i*m+j),Add(i*m+j,(i-1)*m+j);
			if(!flag[(i-1)*m+j][4]&&!flag[(i-1)*m+j-1][2]) Add((i-1)*m+j,(i-1)*m+j-1),Add((i-1)*m+j-1,(i-1)*m+j);
		}//把能互相到达的点之间连边 
	for(ri int i=1;i<=n;++i)
		for(ri int j=1;j<=m;++j)
			if(!vis[(i-1)*m+j]) cnt=0,Dfs((i-1)*m+j),v.pb(cnt);
	sort(v.begin(),v.end());
	for(ri int i=(int)v.size()-1;~i;--i)
		cout<<v[i]<<" ";
	return 0;
}
```

---

## 作者：Jerrlee✅ (赞：0)

## 提示
> 把房间从大到小排序。

肯定会用到排序的。
## 思路
可以看出，给定的问题可以表示为图，其中节点是瓷砖，如果相邻瓷砖之间没有墙，则相邻瓷砖之间有边。因此，为了计算所有房间的大小，我们必须在图中找到所有连接的瓷砖及其相应的大小，这可以通过简单的 `DFS` 或 `BFS` 完成。在那之后，我们必须对大小进行排序，这可以通过 `sort` 快排来完成。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,G[1003][1003];
bool vis[1003][1003];
int derections[4]={8,4,2,1}; // 北，东，南，西
int movesx[4]={-1,0,1,0};
int movesy[4]={0,1,0,-1};
int dfs(int x,int y){
    if(vis[x][y]) return 0;
    vis[x][y]=1;
    int ans=0;
    for(int i=0;i<4;i++){
        if(G[x][y]&derections[i]) continue; // 此路不通
        int x1=x+movesx[i];
        int y1=y+movesy[i];
        if(vis[x1][y1]||(0>=x1||x1>n)||(0>=y1||y1>m)) continue;
        ans+=dfs(x1, y1)+1;
    }
    return ans;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) scanf("%d",&G[i][j]);
    memset(vis,0,sizeof(vis)); // 全标为 false ，小心出错（我 IDE 时就忘了）
    vector<int>ans;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++){
        if(vis[i][j]) continue;
        ans.push_back(1+dfs(i,j));
    }
    sort(ans.begin(),ans.end(),greater<int>());
    for(auto &a:ans) cout<<a<<' ';
}
```
[AC 记录（洛谷）](https://www.luogu.com.cn/record/59663419)

[AC 记录（CF）](http://codeforces.com/contest/1600/submission/131557228)

---

