# Petya and Spiders

## 题目描述

给定一个 $n\times m$ 的棋盘，一开始每一个格子上有一只蜘蛛，你可以让每一只蜘蛛向上或下或左或右走一格，也可以让蜘蛛停在原地不动，但前提是不能走出棋盘，可以有多只蜘蛛在同一个格子中，问最多可以空出多少个格子？

## 说明/提示

在样例一中，只有一种解决方案：
```
s
```

在样例二中，可能的解决方案之一是：
```
rdl
rul
```

`s` 表示呆在原地不动，`l`、`r`、`u`、`d` 表示往上、下、左、右爪巴一格。

## 样例 #1

### 输入

```
1 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2 3
```

### 输出

```
4
```

# 题解

## 作者：pjykk (赞：5)

简单的状压 dp. 这里主要说一下一些小细节.

首先对题目进行简单转化, 就是问最少能用多少个四连通块覆盖 $n\times m$ 的棋盘.

注意到数据范围 $1\leq n\times m\leq40$, 故有 $\max(n,m)\leq6$, 这就成为了一个可以状压的范围.

状态转移方程也是比较简单的, 就是

$$f(i,s_1,s_2)=\min(f(i,s_1,s_2),f(i-1,s_2,s_3)+\text{popcount}(s_1))$$

其中 $f(i,s_1,s_2)$ 表示第 $i$ 行状态为 $s_1$, 第 $i-1$ 行状态为 $s_2$ 时, 保证铺满 $n\times(i-1)$ 的棋盘所需的最少的四连通块数.

实际上就这一行转移方程, 在实现的时候需要注意的细节非常多. 

首先是如何快速判断状态的合法性: 对于上面的状态转移方程, 我们充分利用位运算. 一个标准的错误是这样写:

$$(s_1|s_2|s_3|(s_2<<1)|(s_2>>1))==(1<<n)-1$$

注意左移操作可能会让位数超过 $n$, 因此我们要取出最后 $n$ 位进行判断.

$$((s_1|s_2|s_3|(s_2<<1)|(s_2>>1))\&((1<<n)-1))==(1<<n)-1$$

另外一定要注意运算的优先级, 不确定的就把括号都写上. 

还有一些细节:

1. 注意我们只保证了 $n\times(i-1)$ 的棋盘能被铺满, 这是为了方便转移. 因此最后统计答案时, 要进行判断保证第 $i$ 行也能被铺满.

2. 一定要做好初始化. 对于第一行有 $f(1,s,0)=\text{popcount}(s)$, 其它位置因为转移方程中是取 $\min$, 初始化为 $\inf$.

3. $\text{popcount}$ 可以用内置的函数 `__builtin_popcount`, 也可以自己手写一个, 也不会慢多少.


最后给出关键部分的代码:

```cpp
memset(f,0x7f,sizeof(f));
for(int s1=0;s1<(1<<n);s1++)f[1][s1][0]=ppcnt(s1);
for(int i=2;i<=m;i++)
	for(int s1=0;s1<(1<<n);s1++)
		for(int s2=0;s2<(1<<n);s2++)
			for(int s3=0;s3<(1<<n);s3++)
				if(((s1|s2|s3|(s2<<1)|(s2>>1))&((1<<n)-1))==(1<<n)-1)
					f[i][s1][s2]=min(f[i][s1][s2],f[i-1][s2][s3]+ppcnt(s1));
for(int s1=0;s1<(1<<n);s1++)
	for(int s2=0;s2<(1<<n);s2++)
		if(((s1|s2|(s1<<1)|(s1>>1))&((1<<n)-1))==(1<<n)-1)
			ans=min(ans,f[m][s1][s2]);
printf("%d\n",n*m-ans);
```

---

## 作者：liu_ruoyu (赞：4)

## 题意分析
一个 $n \times m$ 的棋盘，每个格子一开始有一只蜘蛛，每次蜘蛛可以向四联通方向走一格，或者停留在原地不动，最多有多少格子没有蜘蛛？
## 思考
众所周知，题目的数据范围限制了我们的解法，于是我们看到数据范围： $1≤n×m≤40$ ，进而推出 $\max(n,m)≤6$ ，有了这个推断后，我们有了第一个解法：直接暴力 DFS 。
但是，我们马上又会发现问题。每个点都有 5 种情况，这样显然会超时。这时，我们将思路放回到题目本身。既然要让空格最多，那么自然需要有蜘蛛的格子最少。即，我们需要尽可能多的蜘蛛聚集在尽可能少的格子上，我们把这样的格子叫做聚点，于是我们决定枚举聚点。

**代码（此解绝非正解）：**

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
struct node{
	int x,y;
};
int n,m;
int ans;
bool spider[100][100];
int dx[5]={1,-1,0,0,0};
int dy[5]={0,0,1,-1,0};
void dfs(int x){
	int xx,yy;
	bool flag=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(spider[i][j]){
				xx=i;yy=j;flag=1;//找到一个聚点
			}
		}
		if(flag)break;//如果已经找到过聚点
	}
	if(!flag){//统计答案
		ans=min(ans,x);
		return ;
	}
	if(x+1>=ans)return ;
	for(int i=0;i<5;i++){//可以从五个方向到达一个聚点（当然有本来就在聚点的）
			int nx=xx+dx[i];
			int ny=yy+dy[i];
			if(nx<1||nx>n||ny<1||ny>m)continue;
			queue<node>q;
			for(int k=0;k<5;k++){
				if(spider[nx+dx[k]][ny+dy[k]]){
					spider[nx+dx[k]][ny+dy[k]]=0;
					node tmp;
					tmp.x=nx+dx[k],tmp.y=ny+dy[k];
					q.push(tmp);
				}
			}
			dfs(x+1);
			while(!q.empty()){
				spider[q.front().x][q.front().y]=1;
				q.pop();
			}
	}
}
int main(){
	cin>>n>>m;
	ans=n*m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			spider[i][j]=1;
		}
	}
	dfs(0);
	cout<<n*m-ans<<"\n";//ans是最少的聚点数量
	return 0;
}
```
**完结撒花！**

---

## 作者：ywh666 (赞：4)



 ### 本题题意
 > 给你一个$n*m$（$n,m<=40$且$n.m<=40$）的棋盘，棋盘上每个格子都有一只蜘蛛，蜘蛛每一秒都会选择向上下左右爬行或不动，问最后至多有多少格子是空的

 ### 分析
 > 首先看到这道题可以将其转化为：在一个$n*m$的棋盘上放置棋子，一个棋子可以覆盖该点及其上下左右范围，问至少需要多少棋子能将这个棋盘全部覆盖，最后用棋盘大小减去这个棋子数便可。
 
 >既然这样就可以使用状压dp，设dp【i】【j】【k】为正在放置第i行，本行状态为j，且上一行状态为p，则dp[i][j][k]=min(dp[i][j][k],dp[i-1][k][p]+tot)(此时上行以确保全被覆盖)
 
 >还有一个问题是n,m<=40,如果2^40肯定爆，所以n>m时，要将n,m交换
 
 >细节见代码
 ```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,dp[45][260][260];/*行数，上行，本行 */
int main()
{
	scanf("%d%d",&n,&m);
	if(n==1&&m==1){puts("0");
	return 0;
	}
	if(n<m)swap(n,m);/*n大m小*/
	memset(dp,0x3f3f3f,sizeof(dp));
	for(int i=0;i<(1<<m);++i)
	{
		int tot=0,flag=0;
		int vis[15];
		memset(vis,0,sizeof(vis));
		for(int k=1;k<=m;++k)if(i&(1<<(k-1)))tot++,vis[k]=vis[k-1]=vis[k+1]=1;
		dp[1][0][i]=tot;
	}int ans=1061109567;
	for(int i=2;i<=n;++i)
	{
		for(int j=0;j<(1<<m);++j)/*当前行*/
		{
			for(int k=0;k<(1<<m);++k)/*当前一行*/
			{
				int tot=0;
				for(int p=1;p<=m;++p)
				{
					if(j&(1<<(p-1)))tot++;
				}
				for(int q=0;q<(1<<m);++q)
				{
					int vis2[10];
					memset(vis2,0,sizeof(vis2));
					for(int p=1;p<=m;++p)
				{
					if(q&(1<<(p-1)))vis2[p]=1;
				}
					for(int p=1;p<=m;++p)
				{
					if(j&(1<<(p-1)))vis2[p]=1;
				}
					for(int p=1;p<=m;++p)
				{
					if(k&(1<<(p-1)))vis2[p]=vis2[p-1]=vis2[p+1]=1;
				}
				int fflag=0;
				for(int p=1;p<=m;++p)
				{if(vis2[p]==0){fflag=1;break;
				}
				}
				if(fflag==1)continue;
				dp[i][k][j]=min(dp[i][k][j],dp[i-1][q][k]+tot);
				if(i==n){			
				int vis[10];
				memset(vis,0,sizeof(vis));
				for(int p=1;p<=m;++p)
				{
					if(j&(1<<(p-1)))vis[p-1]=vis[p]=vis[p+1]=1;
				}
				for(int p=1;p<=m;++p)
				{
					if(k&(1<<(p-1)))vis[p]=1;
				}
				int flag=0;
				for(int p=1;p<=m;++p){if(vis[p]==0){
				flag=1;break;}
				}if(flag==1)continue;
				ans=min(ans,dp[i][k][j]);}
				}
			}
		}
	}
	printf("%d\n",n*m-ans);
}
```

---

## 作者：ISTP (赞：3)

## Getting Start

本题解展现了 6k 写题十分钟 debug 两小时的心路历程。

细节很多，调不出来的战友们看看有没有踩到这些坑里去。

AC 代码在文末。

## 初步构思

[原题链接：https://www.luogu.com.cn/problem/CF111C](https://www.luogu.com.cn/problem/CF111C)

思路不难想，简单转化一下题面。

行动结束后每个格子内的蜘蛛会到某些格子聚成蛛群。由于蜘蛛只能向上下左右某个方向走一格或原地不动，所以可以视作一个蛛群收容了上下左右以及原地，也就是一个占地五格十字架范围的蜘蛛（不同蛛群的收容范围当然可以重叠，蜘蛛随便找一个蛛群待着）。

求空出的格子便转化为总个数减去至少需要形成几个蛛群，即**总个数减去铺满棋盘至少要放多少十字架**。

在棋盘里放十字架，数据比较小，可以考虑状压 dp。

设 $dp_{i,y,x}$ 表示当前放置到第 $i$ 行，上一行即第 $i - 1$ 行状态为 $y$，当前行状态为 $x$ 时，**铺满上一行**至少要放多少十字架。

注意状态的设计，之所以选择铺满上一行而不是当前行，是因为当前行是否被铺满可以被下一行也就是第 $i + 1$ 行影响到，那就得开四维的数组，一维行数三维上中下行的状态，药丸。

再考虑某一行的具体状态，在**填 $1$ 的数位表示 该格子为中心放了一个十字架**和 该格子已被覆盖 间选择了前者，因为方便转移，方法等会再提。

显然第 $i - 1$ 行也会被它的上一行的不同状态影响到，会使第 $i - 1$ 行覆盖到的格子不同。

那么设 $z$ 为上上一行即第 $i - 2$ 行的状态，对于第 $i$ 行遍历状态 $x,y,z$，则可以写出转移式

$$ dp_{i,y,x} = \min dp_{i - 1,z,y} + \operatorname{popcount(x)}$$

即从第一行到当前行的总花费由**上一行状态 $y$ 的花费加上当前行状态 $x$ 花费（放置十字架的个数）**得到。

转移当然有条件。要铺满的是上一行，上一行的每个十字架可以影响左中右三格范围，当前行的只能影响正上对着的一格。即 ```((((y << 1) | y | (y >> 1) | x)) == (1 << m) - 1)```

然而需要注意的是，**由于左移、右移会使 1 越界导致覆盖到棋盘外的状态不等于原来的状态（在 $m$ 位右边多出一些 1 来），需要与上 $m$ 位全 1**，即 ```((((y << 1) | y | (y >> 1) | x) & ((1 << m) - 1)) == (1 << m) - 1)```

（PS：处理位运算不要吝惜括号！血的教训！！）

然后第一行需要预处理，因为第一行不受上一行的影响。

然而 $1 \leq n,m \leq 40$ 意味着 $2^{40}$ 种状态，三维的 dp 空间要炸。再删一维吗？

观察数据范围 $n \times m \leq 40$，因为棋盘转个 90° 不影响答案，所以可以**强制令 $n \geq m$，使列数 $m$ 不大于 $6$**，此时状态缩减为 $2^{6}$ 种，可以存下。

测样例，发现 $n = 1,m = 1$ 的答案不对。因为此时只有一行，而第一行拿来预处理了，没算过铺满第一行的情况。

但是灵光一现，因为已经强制令 $n \geq m$，所以唯独 $n = 1,m = 1$ 时棋盘只有一行，给个特判就好了。

答案为最后一行满足其被铺满的状态的最小花费。

## 调试查错

长话短说。

```cpp
//Wrong Answer
cin >> n >> m;
if(n < m) swap(n, m);
if(n == 1){
	cout << 0;
	return 0;
}
memset(dp, 0x3f, sizeof dp);
for(int i = 0; i < (1 << m); i ++)
	for(int j = 0; j < (1 << m); j ++)
		dp[1][j][i] = __builtin_popcount(i);
for(int i = 2; i <= n; i ++)
	for(int x = 0; x < (1 << m); x ++)
		for(int y = 0; y < (1 << m); y ++)
			for(int z = 0; z < (1 << m); z ++)
				if((((y << 1) | y | (y >> 1) | x) & ((1 << m) - 1)) == (1 << m) - 1)
					dp[i][y][x] = min(dp[i][y][x], dp[i - 1][z][y] + __builtin_popcount(x));
int ans = inf;
for(int x = 0; x < (1 << m); x ++)
	for(int y = 0; y < (1 << m); y ++)
		if((((y << 1) | y | (y >> 1) | x) & ((1 << m) - 1)) == (1 << m) - 1)
			ans = min(ans, dp[n][y][x]);
cout << n * m - ans;
```

以上是根据刚才思路写出的初版代码，WA on \#5.

- 写的时候懒得打条件直接把 dp 里的复制到最后找答案的循环了，但是 dp 里要求上一行被铺满，是用当前行影响上一行，找答案时上一行根据 dp 状态设计的条件已经铺满，此时需要最后一行也就是当前行被铺满，用上一行影响当前行。

```cpp
//Not Enough
if((((x << 1) | x | (x >> 1) | y) & ((1 << m) - 1)) == (1 << m) - 1)
	ans = min(ans, dp[n][y][x]);
```

修改后 WA on \#6.

- 上上一行的状态 $z$ 也有参与影响上一行 $y$ 是否被铺满。

```cpp
//Not Enough Neither
if((((y << 1) | y | (y >> 1) | x | z) & ((1 << m) - 1)) == (1 << m) - 1)
	dp[i][y][x] = min(dp[i][y][x], dp[i - 1][z][y] + __builtin_popcount(x));
```

修改后 WA on \#3.

- 第二行的 $z$，即第零行，不会影响第一行的状态，可以分类讨论也可以拎出来预处理，我选择后者。

```cpp
//That's OK
for(int x = 0; x < (1 << m); x ++)
	for(int y = 0; y < (1 << m); y ++)
		for(int z = 0; z < (1 << m); z ++)
			if((((y << 1) | y | (y >> 1) | x) & ((1 << m) - 1)) == (1 << m) - 1)
				dp[2][y][x] = min(dp[2][y][x], dp[1][z][y] + __builtin_popcount(x));
```

至此，大概是没有什么欠缺了。

## AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 41, maxs = (1 << 7), inf = 0x3f3f3f3f;
int n, m;
int cb[maxn][maxn];
int dp[maxn][maxs][maxs];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	if(n < m) swap(n, m);
	if(n == 1){
		cout << 0;
		return 0;
	}
	memset(dp, 0x3f, sizeof dp);
	for(int i = 0; i < (1 << m); i ++)
		for(int j = 0; j < (1 << m); j ++)
			dp[1][j][i] = __builtin_popcount(i);
	for(int x = 0; x < (1 << m); x ++)
		for(int y = 0; y < (1 << m); y ++)
			for(int z = 0; z < (1 << m); z ++)
				if((((y << 1) | y | (y >> 1) | x) & ((1 << m) - 1)) == (1 << m) - 1)
					dp[2][y][x] = min(dp[2][y][x], dp[1][z][y] + __builtin_popcount(x));
	for(int i = 3; i <= n; i ++){
		for(int x = 0; x < (1 << m); x ++)
			for(int y = 0; y < (1 << m); y ++)
				for(int z = 0; z < (1 << m); z ++)
					if((((y << 1) | y | (y >> 1) | x | z) & ((1 << m) - 1)) == (1 << m) - 1)
						dp[i][y][x] = min(dp[i][y][x], dp[i - 1][z][y] + __builtin_popcount(x));
	int ans = inf;
	for(int x = 0; x < (1 << m); x ++)
		for(int y = 0; y < (1 << m); y ++)
			if((((x << 1) | x | (x >> 1) | y) & ((1 << m) - 1)) == (1 << m) - 1)
				ans = min(ans, dp[n][y][x]);
	cout << n * m - ans;
	return 0;
}
```

完结撒花。祝你们切题顺利——

---

## 作者：The_foolishest_OIer (赞：2)

好玩的数学题。

可以发现 $\min(n,m) \le 6$，并且 $m \times n$ 或者 $n \times m$ 是等价的。

所以直接讨论 $n \le 6$ 即可。

先讨论什么样的格子可以合并成一个格子。

![](https://cdn.luogu.com.cn/upload/image_hosting/b8iuw18q.png)

还有两个和单独的，这里不画了。

当 $n=1$ 时，可以发现每三个合并可以省掉大约 $\frac{2}{3}$，最后如果有剩余，那就在耗掉一个格子。

当 $n=2$ 时，可以发现，我们一直拿“T”型的去填充是最优的，剩下的边角选一些实惠的合并就行。

当 $n=3$ 时，可以用一个“T”型，一个三条，一个十字组成一个很奇怪的东西，剩下的用其他填充即可，对 $m$ 模 $4$ 分讨。

当 $n=4$ 时，用四个“T”型构造一个 $4 \times 4$ 的方块，其余用其他填充即可，还是对 $m$ 模 $4$ 分讨。

然后发现 $m=10$ 的时候挂了，于是手玩一下得出以下构造：

![](https://cdn.luogu.com.cn/upload/image_hosting/6uvmdwng.png)

发现只需要 $10$ 个。

当 $n=5,6$ 时，$m$ 的取值数量很少，手玩即可。

```cpp
void solve(){
	cin >> n >> m;
	if (n > m) swap(n,m);
	int s = n * m;
	if (n == 1){
		if (m % 3 == 0) cout << s - m / 3 << endl;
		else cout << s - (m / 3 + 1) << endl;
	}else if (n == 2){
		if (m & 1) cout << s - (m + 1) / 2 << endl;
		else cout << s - (m / 2 + 1) << endl;
	}else if (n == 3){
		if (m % 4 == 0 || m % 4 == 1) cout << s - (m / 4 * 3) - 1 << endl;
		else cout << s - (m / 4 * 3) - (m % 4) << endl;
	}else if (n == 4){
		int ret = (m / 4) * 4;
		if (m % 4 == 1) ret += 2;
		else if (m % 4 == 2) ret += 3;
		else if (m % 4 == 3) ret += 3;
		if (m <= 9) cout << s - ret << endl;
		else cout << "30\n";
	}else if (n == 5){
		if (m == 5) cout << "18\n";
		else if (m == 6) cout << "22\n";
		else if (m == 7) cout << "26\n";
		else cout << "29\n";
	}else{
		cout << "26\n";
	}
}
```

---

## 作者：luckyqwq (赞：2)

# CF111C Petya and Spiders 题解

#### 大致思路：

我们可以看到 $n × m ≤ 40$，显然我们可以推算出 $\max(n, m) ≤ 6$，竟然只有 $6$，那我们搜索就行了。我们用 $x$ 记录目前的有蜘蛛位置的数量，也就是聚集点，用 STL 维护回溯即可。

#### 代码实现：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LLL __int128_t
#define LL long long
#define uint unsigned;
#define ull unsigned LL;
#define qi std::queue < int >;
#define vi std::vector < int >;
#define pii std::pair < int, int >;
#define lowbit(x) ((x) & -(x))
#define pq std::priority_queue
#define ve std::vector < pair < int, int> >
#define pr std::priority_queue < int, int >
#define pri std::priority_queue<pair<int,int> ,vector<pair<int,int> > ,greater<pair<int,int> > >
#define qcin std::ios::sync_with_stdio(0)
#define pb push_back
#define me(a, b) std::memset(a, b, sizeof(a))

const double TLS = 1;
const double eps = 1e-9;
const int inf = 1 << 29;
const int CPS = CLOCKS_PER_SEC;
const int INF = 1 << 30;//设置一个边界
const double TLC = TLS * 0.97 * CPS;
const int N = 2e4 + 10;
const int MOD = 1e8 + 7;
void print(int x) {
    if (!x)
        return;

    print(x / 10);
    std::putchar(x % 10 + '0');
}
int n, m, mp[50][50], res;
int sx[] = {-1, 1, 0, 0, 0};
int sy[] = {0, 0, -1, 1, 0};
bool f = 0;
void dfs(int x)
{
	int A, B;
	f = 0;//判断变量初始化 
	for (int i = 1;i <= n; ++ i)
	{
		for(int j = 1;j <= m; ++ j)
		{
			if(mp[i][j] == 1)//有蜘蛛 
			{
				A = i, B = j;
				f = 1;
				break;
			}
		}
		if(f) break;
	}
	if(!f)//无蜘蛛了 
	{
		res = min(res, x);//找保留最小值 
		return;
	}
	if(x >= res - 1) return;
	for(int i = 0;i < 5; ++ i)//遍历方向（偏移量） 
	{
		int nx = A + sx[i];
		int ny = B + sy[i];
		if(nx < 1 || nx > n || ny < 1 || ny > m) continue;//判边界 
		ve p;
		for(int j = 0;j < 5; ++j)//遍历目前点的五个方向 
		{
			int nnx = nx + sx[j];
			int nny = ny + sy[j];
			//if(nnx < 1 || nnx > n || nny < 1 || nny > m) continue;
			if(mp[nnx][nny] == 1)
			{
				mp[nnx][nny] = 0;
				p.pb(make_pair(nnx, nny));
			}
		}
		dfs(x + 1);//继续搜索 
		for(int j = 0;j < p.size(); ++ j)
		{
			mp[p[j].first][p[j].second] = 1;//利用pair回溯 
		}
	}
}

signed main(void) {
    cin >> n >> m;
    for(int i = 1;i <= n; ++ i)
    {
        for(int j = 1;j <= m; ++ j)
        {
            mp[i][j] = 1;//初始化 
        }
    }
    res = n * m;//保留全部 
    dfs(0);
    cout << n * m - res << "\n"; 
    return 0;
}
```

这样这道题目就完成啦！！！

---

## 作者：FL_sleake (赞：2)

居然没人用 dfs 做，本蒟蒻来~~水~~一发

## 解题思路

直接枚举每个点的五种状态（向左、向右、向上、向下、不动）显然会超时，于是我们可以考虑枚举**聚点**，即蜘蛛汇聚的点。

我们可以贪心地考虑，若点 $x$ 被选为聚点，则令其周围四个格子的蜘蛛都走到 $x$ 处一定是最优的。这是因为我们要使聚点的数量尽可能少，既然一个点已经被选为聚点就需要最大化它的价值。于是，dfs 的大致思路就出来了：找到一个当前还有蜘蛛的格子，它本身及它周围四个点都有可能是聚点，进行枚举。找到聚点后将其周围的点状态标记为没有蜘蛛，最后加上最优性剪枝即可。

## 代码示例

```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[110][110];
int ans=0x3f3f3f3f;
int dx[10]={0,1,-1,0,0,0};
int dy[10]={0,0,0,1,-1,0};
void dfs(int step){
	int xx,yy,flag=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==1){
				xx=i,yy=j,flag=1;
				break;
			}
		}
		if(flag) break;
	}
	if(flag==0){
		ans=min(ans,step);
		return;
	} 
	if(step+1>=ans) return;
	for(int i=1;i<=5;i++){
		int tx=xx+dx[i],ty=yy+dy[i];
		if(tx<=0||ty<=0||tx>=n+1||ty>=m+1) continue;
		vector<pair<int,int> > O;
		for(int j=1;j<=5;j++){
			if(a[tx+dx[j]][ty+dy[j]]==1){
				a[tx+dx[j]][ty+dy[j]]=0;
				O.push_back(make_pair(tx+dx[j],ty+dy[j]));
			}
		}
		dfs(step+1);
		for(int i=0;i<O.size();i++) a[O[i].first][O[i].second]=1;
	} 
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) a[i][j]=1;
	ans=n*m;
	dfs(0);
	cout<<n*m-ans<<endl;
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

# 题意
每个蜘蛛跑去周围的一个避难所（或者自己所在地就是避难所），设定最少的避难所。

# 思路
由于 $\min(n,m)\le 6$ ，考虑状压，因为 $n,m$ 可以交换。

最开始想直接 $f(i,S)$ 搞定，发现不行。因为这一行要用到下一行的信息。

所以我们改一改状态，告诉下面一行：我需要一个避难所！改成三进制的状压。

$f(i,S)$ 的 $S$ 用 $0$ 表示避难所、用 $1$ 表示 __无家可归的蜘蛛__ 、用 $2$ 表示已经找到避难所的蜘蛛。转移的时候，枚举下一行的避难所情况，求出新状态。复杂度应该是 $\mathcal O(6^n nm)$ 的。

两行状压好像是 $\mathcal O(8^n nm)$ 的？~~分类讨论好像是O(1)的？~~

# 代码
```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long int_;
inline int readint() {
	int a = 0; char c = getchar(), f = 1;
	for(; c<'0' or c>'9'; c=getchar())
		if(c == '-') f = -f;
	for(; '0'<=c and c<='9'; c=getchar())
		a = (a<<3)+(a<<1)+(c^48);
	return a*f;
}
void writeint(int_ x){
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) writeint(x/10);
	putchar((x%10)^48);
}
# define MB template < typename T >
MB void getMax(T &a,const T &b){ if(a < b) a = b; }
MB void getMin(T &a,const T &b){ if(b < a) a = b; }

const int MaxN = 3*3*3*3*3*3;
const int infty = (1<<30)-1;
// 0:有蜘蛛 1:蜘蛛不知何处去 2:蜘蛛已知何处去
int dp[41][MaxN];

int main(){
	int n = readint(), m = readint();
	if(n > m) swap(n,m);
	int ALL = 1;
	for(int i=0; i<n; ++i)
		ALL *= 3;
	for(int j=0; j<=m; ++j)
	for(int i=0; i<ALL; ++i)
		dp[j][i] = -infty;
	dp[0][ALL-1] = 0;
	for(int j=1; j<=m; ++j)
	for(int i=0; i<(1<<n); ++i)
	for(int k=0; k<ALL; ++k){
		int cnt = 0, I = 0;
		for(int p=0,base=1; p<n; ++p,base*=3){
			if(!(i>>p&1)) continue;
			if(p+1 < n && !(i>>1>>p&1))
				I += base*2;
			else if(p && !(i<<1>>p&1))
				I += base*2;
			else if((k/base)%3 == 0)
				I += base*2;
			else I += base;
			if((k/base)%3 == 1)
				cnt = -infty;
			else ++ cnt;
		}
		getMax(dp[j][I],dp[j-1][k]+cnt);
	}
	int ans = 0;
	for(int i=0; i<ALL; ++i){
		bool ok = true;
		for(int j=0,I=i; j<n; ++j,I/=3)
			if(I%3 == 1) ok = false;
		if(ok) getMax(ans,dp[m][i]);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：李柯欣 (赞：1)

题目传送门：[CF111C](https://www.luogu.com.cn/problem/CF111C)。

[更好的阅读感受](https://www.luogu.com.cn/blog/likexin/solution-cf111c)？

### 题目大意：

其实就是用最少的小十字架密铺一个 $n \times m$ 的方格图。

### 思路：

因为 $1\le n\times m \le 40$，意味着 $\min (n,m) \le6$。

于是想到状压。

很容易想到 $dp_{x,i}$ 表示第 $x$ 行被全部覆盖，在 $i$ 的二进制为 $1$ 的地方放了一个十字架的中心时所用了多少个小十字架。

转移方程是：

$$dp_{x,i}=\min (dp_{x-1,j}+tot)$$

其中 $tot$ 表示 $i$ 的二进制中有多少个 $1$。

但是这样是错的，因为在转移到下一行时，这一行不一定要铺满，可以由下一行来补。

而在上面的 dp 转移方程中，我们跳过了这一行没有铺满的情况，所以错了。

于是改进 dp 方程，多加一维。

$dp_{x,i,j}$ 表示第 $x-1$ 行被全部覆盖，第 $x$ 行在 $i$ 的二进制为 $1$ 的地方放了一个十字架的中心，第 $x-1$ 行在 $j$ 的二进制为 $1$ 的地方放了一个十字架的中心时所用了多少个小十字架。

注意到这次的转移方程和上次的很像。

但是我们这次的限制变为了 **第 $x-1$ 行被全部覆盖**

转移方程是：

$$dp_{x,i,j}=\min (dp_{x-1,j,k}+tot)$$

可谓是转移方程几乎没有变，但是性质却大大不同了。

### 代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<vector>
#include<bitset>
#include<string>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<deque>
#include<queue>
#include<stack>
#include<list>
#include<map>
#include<set>
#define int long long
using namespace std;
int n,m;
int k;
int dp[41][1<<7][1<<7];
bool check(int x){
	for(int i=0;i<n;i++){//判断是否铺满。
		if(x&(1<<i)) continue;
		return 1;
	}
	return 0;
}
signed main(){
	memset(dp,0x3f,sizeof(dp));
	cin>>n>>m;
	if(n>m) swap(n,m);
	for(int h=1;h<=m;h++){
		for(int i=0;i<(1<<n);i++){
			int tot=0;
			for(int j=0;j<n;j++) if(i&(1<<j)) tot++;
			dp[1][i][0]=tot;
		}
	}
	for(int h=2;h<=m;h++){
		for(int i=0;i<(1<<n);i++){
			int tot=0;
			for(int j=0;j<n;j++) if(i&(1<<j)) tot++;
			for(int j=0;j<(1<<n);j++){
				for(int k=0;k<(1<<n);k++){
					if(check(k|i|(j<<1)|j|(j>>1))) continue;//要满足上一行铺满。
					dp[h][i][j]=min(dp[h][i][j],dp[h-1][j][k]+tot);
				}
			}
		}
	}
	int ans=0x3f3f3f3f;
	for(int i=0;i<(1<<n);i++){
		for(int j=0;j<(1<<n);j++){
			if(check(i|(i<<1)|(i>>1)|j)) continue;//统计答案时最后一行要铺满。
			ans=min(ans,dp[m][i][j]);
		}
	}
	cout<<n*m-ans;//输出的是 n * m 减去这个最小值。
	return 0;
}
```


[AC 记录](https://www.luogu.com.cn/record/86640366)。

额，由于 CF 爬虫特性，所以真实的提交记录是 [这个](https://www.luogu.com.cn/record/86640320)。（ RE 是因为我上次数组没有开够）

---

## 作者：Beacon_wolf (赞：0)

## 题目简化
求在一个地图上放置障碍物的最小数量，使得所有空白格子都能被覆盖到。

## 题目思路
搜索。

首先遍历棋盘找到第一个没有蜘蛛的格子，如果找不到这样的格子，则更新最优解为当前留空格子数量 $x$。

对于没有蜘蛛的格子，尝试在其周围放置蜘蛛，调用搜索函数，更新留空格子数量 $x$，直到所有格子都被蜘蛛占满或者当前留空格子数量 $\ge$ 最优解（也就是说一定是最优解法）时终止。

在尝试放置蜘蛛后，恢复棋盘。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,best,dx[5] = {0,1,0,-1,0},dy[5] = {-1,0,1,0,0},a[45][45];
///判断坐标是否在棋盘范围内
bool ok(int x,int y){
	return x >= 0 && x < n && y >= 0 && y < m;
}
void dfs(int x){
	vector<pair<int,int> > tmp;
	int xx = -1,yy = -1;
	//寻找没有蜘蛛的格子
	for(int i = 0;i < n;i++){
		for(int j = 0;j < m;j++){
			if(!a[i][j]){
				xx = i,yy = j;
				break;
			}
		}
		if(xx != -1) break;
	}
	//没有找到
	if(xx == -1){
		best = x;
		return;
	}
	if(x + 1 >= best) return;
	for(int i = 0;i < 5;i++){
		//尝试在空格子周围放置蜘蛛
		int x1 = xx + dx[i];
		int y1 = yy + dy[i];
		if(ok(x1,y1)){
			tmp.clear();
			for(int j = 0;j < 5;j++){
				//遍历当前位置(x1, y1)周围的五个点
				int x2 = x1 + dx[j];
				int y2 = y1 + dy[j];
				if(ok(x2,y2) && !a[x2][y2]){ //判断该点是否在棋盘范围内且没有蜘蛛
					tmp.push_back(make_pair(x2,y2)); //保存当前可以放置蜘蛛的位置
					a[x2][y2] = 1; //将蜘蛛标记为已占据
				}
			}
			dfs(x + 1); //搜索下一个没有蜘蛛的位置
			for(int j = 0;j < tmp.size();j++) a[tmp[j].first][tmp[j].second] = 0; //恢复之前放置蜘蛛后的状态
		}
	}
}
int main()
{
	cin >> n >> m;
	best = n * m;
	dfs(0);
	cout << n * m - best;
	return 0;
}
```

---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF111C)

# 题解

首先我们可以将题目转化：在一个 $n\times m$ 的矩阵中，设立尽可能少的特殊点使得整个矩阵全部被覆盖，其中每个特殊点可以覆盖的区域为它自己以及上下左右的格子

意识到 $n,m$ 互相交换，对于答案不影响，那么我们钦定 $n$ 是较大的那个

由 $1\le m\le n \le 40$ 且 $1\le n\times m\le 40$，显然有 $m\le 6$

先分析每一列的覆盖，有三个部分

1. 它会被本来就在这一列上的特殊点覆盖，每个特殊点可以覆盖它自己所处的格子和上下的格子；
2. 它会被左边一列（前提是要有）的特殊点覆盖对应的一个格子；
3. 它会被右边一列（前提是要有）的特殊点覆盖对应的一个格子；

那么，我们有比较暴力的做法：设 $f[i][j][k][l]$ 为我们推到了第 $i$ 列，前一列的特殊点状态为 $j$，后一列状态为 $l$，自己本身这一列状态为 $k$ 的将 $1$ 到 $i$ 列全部格子覆盖完时，能剩下的最多的格子数，那么显然有
$$
f[i][j][k][l]=\max\{f[i-1][t][j][k]+\text{count}(k)\}
$$
且必须保证 $t,j,k$ 可以将 $i-1$ 这一列覆盖完，且 $j,k,l$ 可以将 $i$ 这一列覆盖完，显然有 $1\le t,j,k,l\le 2^6$，复杂度大概在 $\mathcal O(2^6\times 2^6\times 2^6\times n\times 2^6\times 2^6)$ 左右，其中状态有 $2^6\times 2^6\times 2^6\times n$ 而转移是 $\mathcal O(2^6\times 2^6)$，因为我们要枚举 $t,l$

如果按照极限情况，时间复杂度在 $\mathcal O(42949672960)$ 左右，可以称得上很完美的自闭了......

考虑如何进行优化？我们的状态设计，是暴力地记录了第 $i$ 列，以及 $i-1$ 和 $i+1$ 列的放置情况，而在转移中，我们重复考虑了 $t,j,k$ 能否将 $i-1$ 列覆盖完，为什么说重复，因为我们 $f[i-1][...]$ 定义上保证将 $1$ 到 $i-1$ 列全部覆盖完，但是我们在转移中又重复判断，因而说是重复考虑。

考虑对这种重复考虑的情况进行优化，我们实际上只需要记录两列，即 $i$ 和 $i-1$ 列的情况，定义 $f[i][j][k]$ 为推到第 $i$ 列，第 $i-1$ 列放置情况为 $j$，第 $i$ 列放置情况为 $k$ 时能剩下的最多的格子，那么有转移
$$
f[i][j][k]=\max\{f[i-1][t][j]+\text{count}(k)\}
$$
需要保证 $t,j,k$ 可以将第 $i$ 列覆盖完。

这样，我们就省掉重复考虑的情况，时间复杂度 $\mathcal O(2^6\times 2^6\times n\times 2^6)$，极限情况下为 $\mathcal O(10485760)$

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13442266.html
```



---

## 作者：gary2005 (赞：0)

就两篇题解，竟然没有状压的

其实n*m<=40所以min(n,m)<=6

也可以理解为每行最多六个，完全不需要担心超限问题，岂不美哉

其实我们要抓住题目中 移动一次的线索 也就是一个点如果没有蜘蛛了 那么它的上下左右必定有至少一个蜘蛛（如果不超界的话）。

这样我们就只需要枚举三行是否合法就行了

设dp[i][j][k]表示扫描到深度为i状态为j ，i+1状态为k的最多空格

循环l表示i-1行状态

所以dp[i][j][k]=max(dp[i-1][l][j]+j所包含的空格）

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[45][127][127];	int n,m;
int get(int num){
    int ans=0;
    for(int i=1;i<=m;i++){
        ans+=((num&1)==0);
        num>>=1;
    }
//	cout<<num<<" "<<ans<<endl;
    return ans;
    
}
bool check(int j,int k,int l){
    int a,b,c,d,e;
    for(int i=1;i<=m;i++){
    	a=(j&(1<<(i-1)));
    	b=(k&(1<<(i-1)));
    	c=(l&(1<<(i-1)));
    	if(i!=1){
    		d=(k&(1<<(i-2)));	
    	}
    	else{
    		d=0;
    	}
    	if(i!=m){
    		e=(k&(1<<i));
    	}
    	else{
    		e=0;
    	}
    	if(!(a||b||c||d||e)) return false;
    }
    return true;
}
int main(){
    cin>>n>>m;
    if(m>n) swap(m,n);
    int top=(1<<m)-1;
    for(int i=0;i<=top;i++)
        for(int j=0;j<=top;j++)
            dp[0][i][j]=-0x3f3f3f3f;
    for(int i=0;i<=top;i++) dp[0][0][i]=0;
    for(int dep=1;dep<=n;dep++){
        for(int k=0;k<=top;k++){//last
            for(int i=0;i<=top;i++){//now
                for(int j=0;j<=top;j++){//next
                    if(check(k,i,j))
                    dp[dep][i][j]=max(dp[dep][i][j],dp[dep-1][k][i]+get(i));
                }
            } 
        } 
    }
    int maxans=0;
    for (int i=0;i<=top;i++)
    	maxans = max(maxans,dp[n][i][0]);
    
    printf("%d\n",maxans);
    return 0;
} 
```
那有个问题，也是我开始遇到的

只判断i是否合法那么上面的不管了？

其实将dp初始值 为负无穷也就是初始全为不可行，那么如果dep-1层有答案，也就是dep-1层有答案，也就check过dep-1行以此类推，dep-2行也check过了。

---

## 作者：wyl_AC (赞：0)

## 题目转化
这道题很妙，典型的状态压缩DP

由于每个蜘蛛都可以去到**上下左右**的方块里，我们就将这些收容了蜘蛛的方块称之为**蛛穴**，你会发现空方块的个数就是**总数减去蛛穴的个数**。这个反向思维感觉在dp中很常见。那么我们就可以将题目转化为求蛛穴**覆盖全地图**的**最小个数**，每个蛛穴可以覆盖上下左右四个方块。

## DP方程
影响一个方块的行数最多只有上中下三行

假设本行为第i行，状态为k1（2进制表示），上一行为k2,再上一行为k3,我们可以用形如

**dp[ i ][ k1 ][ k2 ]=min(dp[ i ][ k1 ][ k2 ],dp[ i - 1 ][ k2 ][ k3 ])**

的方程进行转化（需要保证i-1行成立）。

注意n*m<=40，所以n和m中小的那个不可能大于6，所以记得交换n,m。

求答案时注意要判断最后一行是否成立

## 代码
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<map>
#include<cmath>
using namespace std;
#define M 5005
#define N 25
#define Mod 1000000007
#define LL long long
#define pai pair<LL,LL>
void read(LL &x) {
    x = 0;
    LL f = 1;
    char c=getchar();
    while (c<'0'||c>'9'){
        if(c=='-')
            f=-f;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x << 1)+(x << 3)+c - '0';
        c=getchar();
    }
    x*=f;
    return;
}
LL fs(LL x){
	return x<0?-x:x;
}
void print(LL x){
	if(x<10){
		putchar(x+'0');
		return ;
	}
	print(x/10);
	putchar(x%10+'0');
	return ;
}
void write(LL x){
	if(x<0){
		putchar('-');
		x=fs(x);
	}
	print(x);
	return ;
}
LL mint(LL x,LL y){
	return x<y?x:y;
}
LL maxt(LL x,LL y){
	return x>y?x:y;
}
LL n,m;
LL dp[45][128][128];
int main(){
	read(n),read(m);
	if(n<m)
		swap(n,m);
	LL ans=0x3f3f3f3f3f3f3f;
	memset(dp,0x3f,sizeof(dp));
	for(int p=0;p<(1<<m);p++){
		dp[1][p][0]=0;
		for(int k=0;k<m;k++)
			if(p&(1<<k))
				dp[1][p][0]++;
		if(n==1){
			bool flag=0;
			for(int k=0;k<m;k++)
				if(!(p&(1<<k)||(k>0&&p&(1<<k-1))||(k<m-1&&p&(1<<k+1))))
					flag=1;
			if(!flag)
				ans=mint(ans,dp[1][p][0]);
		}
	}
	for(int i=2;i<=n;i++)
		for(int k3=0;k3<(1<<m);k3++)
			for(int k2=0;k2<(1<<m);k2++){
				for(int k1=0;k1<(1<<m);k1++){
					LL tmp=0;
					for(int k=0;k<m;k++)
						if(k1&(1<<k))
							tmp++;
					bool f=0;
					for(int k=0;k<m;k++)
						if(!(k1&(1<<k)||k2&(1<<k)||k3&(1<<k)||(k>0&&(k2&(1<<k-1)))||(k<m-1&&(k2&(1<<k+1))))){
							f=1;
							break;
						}
					if(!f)		
						dp[i][k1][k2]=mint(dp[i][k1][k2],dp[i-1][k2][k3]+tmp);								
					else
						continue;
					if(i==n){
						bool flag=0;
						for(int k=0;k<m;k++)
							if(!(k1&(1<<k)||k2&(1<<k)||(k>0&&(k1&(1<<k-1)))||(k<m-1&&(k1&(1<<k+1))))){
								flag=1;
								break;
							}
						if(!flag)	
							ans=mint(ans,dp[i][k1][k2]);
					}
				}
			}
	printf("%lld",n*m-ans);
}
```


---

