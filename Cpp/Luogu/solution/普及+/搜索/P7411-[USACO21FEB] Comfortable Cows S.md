# [USACO21FEB] Comfortable Cows S

## 题目描述

Farmer Nhoj 的草地可以被看作是一个由正方形方格组成的巨大的二维方阵（想象一个巨大的棋盘）。初始时，草地上是空的。

Farmer Nhoj 将会逐一地将 $N$（$1\le N\le 10^5$）头奶牛加入到草地上。第 $i$ 头奶牛将会占据方格 $(x_i,y_i)$，不同于所有已经被其他奶牛占据的方格（$0\le x_i,y_i\le 1000$）。

一头奶牛被称为是「舒适的」，如果它水平或竖直方向上与恰好三头其他奶牛相邻。然而，太舒适的奶牛往往产奶量落后，所以 Farmer Nhoj 想要额外加入一些奶牛直到没有奶牛（包括新加入的奶牛）是舒适的。注意加入的奶牛的 $x$ 和 $y$ 坐标并不一定需要在范围 $0 \ldots 1000$ 内。

对于 $1 \ldots N$ 中的每个 $i$，输出当初始时草地上有奶牛 $1\ldots i$ 时，Farmer Nhoj 为使得没有奶牛舒适，需要加入的奶牛的最小数量。


## 说明/提示


对于 $i=4$，Farmer Nhoj 需要在 $(2,1)$ 加入一头奶牛使得位于 $(1,1)$ 的奶牛不再舒适。

对于 $i=9$，Farmer Nhoj 的最优方案是在 $(2,0)$、$(3,0)$、$(2,-1)$ 和 $(2,3)$ 加入奶牛。

供题：Benjamin Qi

## 样例 #1

### 输入

```
9
0 1
1 0
1 1
1 2
2 1
2 2
3 1
3 2
4 1```

### 输出

```
0
0
0
1
0
0
1
2
4```

# 题解

## 作者：_zy_ (赞：22)

## [题目传送门](https://www.luogu.com.cn/problem/P7411)

题目大意：对于前 $i$ 个奶牛，求加入最少的奶牛的数目使不存在舒适的牛，即有三个牛在他身边。

我们来动态的考虑，每加进一个点会对前 $i-1$ 个点的影响。

1. 产生具有舒适度的奶牛。

2. 将以前加入的奶牛覆盖。

于是我们就可以发现对于前$i$个奶牛, $ans$ 可由前  $i-1$ 个奶牛状态得到，并且发现如果存在舒适的奶牛，取笑他舒适的奶牛是必须要加的。

**加入的那个点很显然也是满足上述两种影响.**

- 存图的时候下标可能会超出边界，就考虑极限，让每个坐标的值加 $1000$.

- 不要忘记加上的点自身也可能会是舒适的奶牛，所以不要忘记递归该点。

### $summary$：

**动态加点，递归处理**

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define N 10010
using namespace std;
int re() {
	int p=0; char i=getchar();
	while(i<'0'||i>'9')	i=getchar();
	while(i>='0'&&i<='9')	p=p*10+i-'0',i=getchar();
	return p;
}
int n,m,cnt;
int map[N][N];
const int dx[]={0,0,0,1,-1};
const int dy[]={0,1,-1,0,0};
void dfs(int x,int y)
{
	int flag=0;
	int t_x,t_y;
	if(!map[x][y])	return ;		//牛都不是
	for(int i=1;i<=4;i++) {
		int xx=x+dx[i];
		int yy=y+dy[i];
		if(map[xx][yy]) flag++;
		else t_x=xx,t_y=yy;
	}
	if(flag!=3)	return ;		//牛不舒适，不用加点
	else {
		map[t_x][t_y]=1;
		cnt++;						//第一种影响
		for(int i=0;i<=4;i++)		//0是该点
			dfs(t_x+dx[i],t_y+dy[i]);
	}
}
int main()
{
	n=re();
	while(n--)
	{
		int x,y;
		x=re()+1000; y=re()+1000;	//防止数组超界
		if(map[x][y])	cnt--;		//第二种影响
		map[x][y]=1;
		for(int i=0;i<=4;i++)		//0是该点
		{
			int xx=x+dx[i];
			int yy=y+dy[i];
			dfs(xx,yy);
		}
		printf("%d\n",cnt);
	}
	return 0;
}
```

如有不妥，请不要吝啬您的评论 $qwq$.

~~题外话：为什么不是 $Farmer John$~~




---

## 作者：Sheng_Horizon (赞：13)

# [题目の传送](https://www.luogu.com.cn/problem/P7411)

# 题目大意

大概就是说，如果 一头牛 在 **上下左右** 四个方向中，**恰好**在三个方向有牛和它相邻，就称它为 “舒适的”。此时就需要在它唯一一个 没有相邻牛的方向上添加一头牛，使它 “不舒适”。

# 解析

## 开始之前

为了方便描述，我们称在输入中的牛为 “**主动添加**” 的牛，称为了打破其他牛的 “舒适” 而添加的牛为 “**被动添加**” 的牛

## 算法选用

如题，当需要被动添加一头牛的时候，这头牛也可能使自己以及自己四个方向的牛变得 “舒适”，然后又需要被动添加更多的牛使他们都 “不舒适”

于是，明显的，这道题要么用  _BFS_  要么用  _DFS_ 

>输出 $N$ 行，对于 $1 \ldots N$ 中的每个 $i$，输出一行，为 Farmer Nhoj 需要加入的奶牛数量。

同时，根据题目描述，需要动态地加牛，处理答案

## 一个性质

一头牛被被动添加后，不会因为之后添加了更多的牛而又变得不需要添加

**原因**：很明显,每一头被被动添加的牛都是基于 **在它之前**就 **已主动添加** 或 **已被动添加** 的牛的基础之上的，于是它们也做不到 “破坏” 它们的基础，因为如果没有它们的基础，它们就不可能存在。
    
基于这个性质，我们便无需在每次处理答案地时候都再次全局地遍历需要被动添加的牛。

我们只需在每次被动添加牛的时候给它打一个特殊标记，并使  _**被动添加牛数**_  加一。若某次输入操作（即主动添加牛）使一头牛从**被动**转为**主动**，则使 _**被动添加牛数**_ 减一即可。

## 一个细节

被额外添加的牛的坐标可能超出 $0\ldots1000$ 的范围，于是它们的坐标可能就成为了负数

很明显，数组并不喜欢负数下标

于是我们在输入时就需要将每一头牛的下标都加一个常数

那么到底需要加多少呢？

当然，随便加个 $1000$ 之类的不会错

但我就是想知道最少具体需要加多少

如题，想要使被动添加的牛尽可能地向范围外延申，我们需要尽可能地组成这样地图形：

```
* ~ *  ~:舒适地牛
  *    *:包围舒适的牛的牛
  
图形一
```

这样我们就需要被动添加一头牛以使所有牛都不舒适
```
  @    @:需要被额外添加的牛
* ~ *  ~:舒适的牛
  *    *:包围舒适的牛的牛

图形二
```

我们只有尽可能地组成图形一，才可以尽可能地使被动添加的牛尽可能地向区域外延申

```
      @        ¥:舒适的牛，但同时也是需要被额外添加的牛     
    @ ¥ @
  @ ¥ ¥ ¥ @
* ~ ~ ~ ~ ~ *  <= 图形一的组合
  * * * * *
```

我们看到，明显的，牛会组成一个直角等腰三角形（当然还有多出来的一排牛），而这个等腰直角三角形的最长边最长又是 $1000-0=1000$ 的（因为范围）。

明显的，以该直角等腰三角形的最长边为底的高 向外延伸得最远。求得该高最长为 $1000/2=500$ ，又因为每头牛的坐标都为整数(即为格点），所以这条高最多包含 $500+1=501$ 头牛

综上，至少给下标加 $501$
![](https://cdn.luogu.com.cn/upload/image_hosting/ugwyw3n2.png)


## 代码~~（终于该上代码了）~~
解析里没提到的几乎都在代码注释里了

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
typedef pair<int,int> PII;
const int N=1e5+10;
const int M=2200;//注意四个方向都有可能扩展501，所以M要加上两个501
short cow[M][M];
short cnt[M][M];
int dx[]={0,0,1,0,-1};//BFS包括5个方位
int dy[]={0,1,0,-1,0};//分别是自己、上、下、左、右
int n;
int ans;//被动更新牛数

void update(int a,int b){
	for(int i=1;i<=4;i++){
		if(cow[a+dx[i]][b+dy[i]]){
			cnt[a][b]++;
			cnt[a+dx[i]][b+dy[i]]++;//记录一头牛附近的牛的数量
		}
	}
}

void add_cow(int a,int b){//bfs
	queue<PII> que;
	for(int i=0;i<=4;i++){
		if (cnt[a+dx[i]][b+dy[i]]==3) que.push({a+dx[i],b+dy[i]});
	}
	while(!que.empty()){
		PII t=que.front();que.pop();
		int x=t.first,y=t.second;
		if(cnt[x][y]!=3) continue;
		int xx,yy;
		for(int i=1;i<=4;i++){
			if(!cow[x+dx[i]][y+dy[i]]){
				xx=x+dx[i];
				yy=y+dy[i];
				cow[xx][yy]=2;
				update(xx,yy);
				ans++;
				for(int i=0;i<=4;i++){
					if (cnt[xx+dx[i]][yy+dy[i]]==3) que.push({xx+dx[i],yy+dy[i]});
				}
				break;
			}
		}
	}
}

int main(){
	//freopen("test.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int a,b;scanf("%d%d",&a,&b);
		a+=510,b+=510;
		if(cow[a][b]==2){
			cow[a][b]=1;//如果曾经是被动添加的牛，现在变为主动添加了
			ans--;//那也无需再遍历了，直接将 被动添加牛数减一
		}else{
			cow[a][b]=1;
			update(a,b);
			add_cow(a,b);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

# 完结撒花
（~~终于把我的第一篇题解写完了~~，写的很烂）



---

## 作者：yeshubo_qwq (赞：5)

## [题面](https://www.luogu.com.cn/problem/P7411)

------------
## Solution
整体思路：每次添加一头奶牛，如果它的位置已经有一头我们添加的奶牛，我们添加的奶牛数量 $-1$，否则添加奶牛并进行dfs。

dfs思路：检查周围有没有舒适的奶牛，若有，我们添加一头奶牛（我们添加的奶牛数量 $+1$），使它变成不舒适的奶牛，直到找不到舒适的奶牛。

其他要点：因为题目中有一句话：**注意加入的奶牛的 $x$ 和 $y$ 坐标并不一定需要在范围 $0$ $\ldots$ $1000$ 内。** 所以，我们应该给横竖坐标增加 $1000$ 的偏移量，数组应该开到 $3000\times 3000$。


------------
## Code
开O2，用时 $123$ms，内存 $14.64$MB。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int tag[5][2]={{0,0},{-1,0},{1,0},{0,-1},{0,1}};//自己和四个不同方向
int n,i,x,y,ans,f[3010][3010];//f注意数组的范围
void dfs(int x,int y){
    int i,xx,yy;
	for(i=0;i<=4;i++){
		xx=x+tag[i][0];yy=y+tag[i][1];
		if(f[xx-1][yy]+f[xx+1][yy]+f[xx][yy-1]+f[xx][yy+1]==3&&f[xx][yy]==1){//判断是否是舒适的奶牛
			if(!f[xx-1][yy])xx--;
			else if(!f[xx+1][yy])xx++;
			else if(!f[xx][yy-1])yy--;
			else yy++;//寻找缺口，添加奶牛
			ans++;//自己添加的奶牛+1
			f[xx][yy]=1;//标记已有奶牛
			dfs(xx,yy);
		}
	}
}
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		x+=1000;y+=1000;//横竖坐标增加偏移量
		if(f[x][y]==1)ans--;//有一头自己添加的奶牛
		else f[x][y]=1,dfs(x,y);//添加奶牛，并进行dfs
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：feicheng (赞：5)

谷首A

## [Description](https://www.luogu.com.cn/problem/P7411)

坐标轴有 $k$ 个点，加入一些点使得没有点的周围有三个点（包括新加的点），最小化加点个数。

## Solution

### 模拟+贪心

只要周围有三个点，就加入一个点，然后我们知道，新加进来点之后，只会影响新点和新点四周的点，所以我们可以再检查四周的点是否满足条件即可。

至于如何检验：只要统计一下这个点四周有没有被标记就可以。

关于检验负数点：我的处理方法是给坐标加上一个数，避免出现负数。

## Code

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
inline int Read(){
	int s = 0 , w = 1;
	char ch = getchar();
	while(ch > '9' || ch < '0'){
		if(ch == '-') w = -1;
		ch = getchar();
	}	
	while(ch >= '0' && ch <= '9'){
		s = (s << 3) + (s << 1) + ch - '0';
		ch = getchar();
	}
	return s * w;
}
const int MAXN = 2e5 + 50;
int n,ans;
int x[MAXN],y[MAXN];
int s[5000][5000];
int mx[] = {0,1,0,-1};
int my[] = {1,0,-1,0};
bool check(int a,int b){
	if(!s[a][b]) return false;
	int tmp = 0;
	for(int d = 0 ; d < 4 ; d ++){
		if(s[a + mx[d]][b + my[d]]) tmp ++;
	}
	return tmp == 3;
}//检验四周是否有三个点
void mod(int a,int b){
	for(int d = 0 ; d < 4 ; d ++){
		int xx = a + mx[d] , yy = b + my[d];
		if(s[xx][yy] == 0){
			s[xx][yy] = 2;
			ans ++;
			if(check(xx,yy)) mod(xx,yy);
			for(int dd = 0 ; dd < 4 ; dd ++){
				if(check(xx + mx[dd],yy + my[dd])) mod(xx + mx[dd],yy + my[dd]);
			}//修改时如果导致新点满足条件，则还要修改新点
		}
	}
}
int main(){
	n = Read();
	for(int i = 1 ; i <= n ; i ++){
		x[i] = Read() + 1000, y[i] = Read() + 1000;
	}
	for(int i = 1 ; i <= n ; i ++){
		if(s[x[i]][y[i]] == 2) ans --;
		s[x[i]][y[i]] = 1;
		if(check(x[i],y[i])) mod(x[i],y[i]);
		for(int d = 0 ; d < 4 ; d ++){
			if(check(x[i] + mx[d],y[i] + my[d])) mod(x[i] + mx[d],y[i] + my[d]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：SUNCHAOYI (赞：3)

就是一个深搜的过程，每次一头牛加入进来，做以下操作：
1. 判断该位置是否已经有牛。若已经有牛，则说明之前的操作必须使该位置有牛才最优，因此此时可以将答案减去 $1$。

2. 判断该位置是否满足题意。

3. 判断该位置的四个相邻位置是否满足题意。

4. 若有新加牛，则需重复步骤 $2,3$，判断新加牛的位置。

对于判断是否满足题意，只需判断该点周围牛的个数是否为 $3$。

```cpp
bool check (int x,int y)
{
	if (!vis[{x,y}]) return 0;//若该点没有牛，则不用判断
	int sum = 0;
	for (int i = 0;i < 4;++i)
	{
		int newx = x + dx[i],newy = y + dy[i];
		if (vis[{newx,newy}]) ++sum;
	}
	if (sum == 3) return 1;//刚好为三个
	else return 0;
}
```

具体重复搜索的过程就是一个裸裸的 $\texttt{dfs}$，写的和其它大佬的差不多，就不展示了。

至于题目中的“注意加入的奶牛的 $x$ 和 $y$ 坐标并不一定需要在范围 $0 \ldots 1000$ 内。”，我是直接使用 `STL` 中 `map`，`map <pair <int,int>,bool> vis;` 来实现对负数的储存的。但是实测速度较慢，要吸氧才能过，因此较好的方法是对输入的坐标均加上一个较大的数，这样能够较好地避免新加的牛的坐标会出现负数的情况。

---

## 作者：Mars_Dingdang (赞：2)

一道看起来挺难，上手写却能写出来的题目。

## 题目描述
给定 $n$ 个点坐标 $(x_i, y_i), 0\le x,y\le 1000$，要求依次输出使得第 $1\sim i$ 个点满足每个点都不恰好与 $3$ 个点相邻，最少需要添加的点，且添加的点也必须满足，但坐标范围没有限制。

## 大体思路
受到题目中输出 $1\sim i$ 的情况，以及 $n\le 10^5$ 的提示，很容易想到基于第 $i-1$ 次的结果进行计算。

![](https://cdn.luogu.com.cn/upload/image_hosting/jjdgjxf2.png)

例如，这是题目样例 $i=9$ 时的结果，红色点为需要添加的点，一共四个。假设我给出第十个点的坐标正好是红色点之一，那么需要添加的牛的数量反而会减少一个。

否则，需要添加的牛的数量可能增加。由于添加的点周围也不能恰好与三个点相邻，可能需要再次添加，这就形成一个递归的过程，可以利用 dfs 实现。

具体地，我们用 $mp[x,y]$ 记录 $(x,y)$ 是否有牛（包括原有的和前一轮添加的），并用全局变量 $cnt$ 记录添加的牛的数量。当第 $i$ 轮在 $(x_i,y_i)$ 添加牛时，首先判断若 $mp[x_i,y_i]=1$ 则令 $cnt-1$；否则调用 dfs 函数对 $(x_i,y_i)$ 以及其上下左右一共五个点进行处理。

对于 $\operatorname{dfs}(x,y)$，若 $mp[x,y]=0$ 则表示这个位置没有牛，不受影响，直接返回；否则计算上下左右四个相邻点牛的数量 $res$。若 $res \neq 3$ 则无需处理，否则在空余位置 $(rx, ry)$ 放置牛，令 $mp[rx,ry]+1, cnt+1$。接着与一开始类似地调用 dfs 函数对 $(rx, ry)$ 以及其上下左右共五个点进行处理。

由于 dfs 时每个点被访问的次数都是常数次，且最多的点不超过 $2000^2$ 个，时间复杂度为 $O(2000^2)$；实际上由于访问的点基本都在边界，运行时效率远高于此。

此外，由于添加点的坐标可能小于零，需要给每个点横纵坐标加 $1001$。同时数组大小需要修改。

## 完整代码
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 4e3 + 5;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
ll n, cnt;
bool mp[maxn][maxn];
int dx[] = {0, 0, 0, 1, -1},
	dy[] = {0, 1, -1, 0, 0};
inline void dfs(int x, int y) {
	if(!mp[x][y]) return ;
	int res = 0;
	PII rest;
	rep(k, 1, 4) {
		int nx = x + dx[k], ny = y + dy[k];
		if(mp[nx][ny]) res ++; // 相邻牛的数量
		else rest = {nx, ny}; // 空余位置
	}
	if(res != 3) return;
	mp[x = rest.first][y = rest.second] = 1;
	cnt ++;
	rep(k, 0, 4) {
		int nx = x + dx[k], ny = y + dy[k];
		dfs(nx, ny);
	}
}
int main () {
	read(n);
	rep(i, 1, n) {
		int x, y;
		read(x); read(y);
		x += 1001, y += 1001;
		if(mp[x][y]) cnt --;
		mp[x][y] = 1;
		rep(k, 0, 4) { // 包括本身
			int nx = x + dx[k], ny = y + dy[k];
			dfs(nx, ny);
		}
		writeln(cnt);
	}
	return 0;
}
```

---

## 作者：NDFS (赞：2)

观察题目可以发现性质：一个奶牛被放入草坪后只会对周围四个奶牛产生影响。

利用这个性质，每次加入奶牛，判断这个奶牛和上下左右这五个位置有没有舒适的奶牛，有就把缺的位置补上，又相当于加入一个奶牛，利用递归一层层判断下去即可。但是有时已加入的奶牛会被数据再次加入，判断有没有加入过再统计答案。因为数组下标不能是负数，所以所有奶牛下标都要加上一个常数，大概 $1000$ 或 $2000$。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,a[5005][5005],x,y,sum=0;
void pd(int,int);//也可以只写一个函数把判断和加点合在一起
void add(int x,int y)//加点
{
	if(a[x][y]==0)sum++;
	a[x][y]=1,pd(x,y),pd(x-1,y),pd(x,y-1),pd(x+1,y),pd(x,y+1);
}
void pd(int x,int y)//判断
{
	if(!a[x][y])return;
	if(a[x-1][y]&&a[x][y-1]&&a[x+1][y]&&!a[x][y+1])add(x,y+1);
	else if(a[x-1][y]&&a[x][y-1]&&!a[x+1][y]&&a[x][y+1])add(x+1,y);
	else if(a[x-1][y]&&!a[x][y-1]&&a[x+1][y]&&a[x][y+1])add(x,y-1);
	else if(!a[x-1][y]&&a[x][y-1]&&a[x+1][y]&&a[x][y+1])add(x-1,y);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y),x+=2000,y+=2000;
		if(a[x][y])sum--;//已加入过不用统计
		a[x][y]=1;
		pd(x,y),pd(x-1,y),pd(x,y-1),pd(x+1,y),pd(x,y+1);
		printf("%d\n",sum);
	}
	return 0;
}
```

---

## 作者：约瑟夫用脑玩 (赞：2)

好像不会分析有多少头奶牛，相信大概可能还会有人不清楚而问同样的问题（？

开始的想法是分析一头奶牛带来的贡献，如果加入一头奶牛可能对周围四头奶牛都造成 $1$ 的贡献。

当一头牛被贡献了 $3$ 时就会加入一个新的奶牛，但是考虑这个新的奶牛，他最多可能对除了造出它的奶牛的另外三个方向各造成 $1$ 的贡献。

这样分析就卡出问题了，一头被加入的牛可能造成 $3$ 的贡献，但 $3$ 的贡献就可以再造一头牛了。

这样从感性上是说不通的，因为它造成的 $3$ 的贡献是分散的，而你很难将这个贡献集中起来，集中的时候应该还会有代价导致不能无限膨胀。

考虑是否有可能无限扩展，如下图中 $X$ 为被加入的点。

```
  A
1AAA5
62X49
 738
```

发现 $X$ 对 $2,3,4$ 都造成了贡献，但是你想利用 $4$ 的贡献，如果不是往 $5$ 的方向扩展，那么肯定是用 $4$ 增殖的 $8$ 来转移贡献。

但是想造出 $8$ 就得在 $X$ 的外面，也就是 $4,5$ 中间 $9$ 的方向必定有额外代价。

如果是用 $4$ 来往 $5$ 的方向贡献，同理分析 $2$ 发现无法将其贡献直接转移到 $7$ 导致其贡献无法使用。

所以无限扩展是不可能的，而这样分析后也发现了，不管是主动加入造成的 $4$ 的代价还是被动加入的 $3$ 的代价，它们造成的都是对三面以上的方向的贡献，我们至多能共同利用其两个方向，而另一个方向就难以兼顾。

所以我并未分析出这类问题准确的界限，如果有会证明的或是看到了证明的请务必告诉我。

但就这道题而言，我们跳出这个分析也是可以找到它的界限的。

因为对于主动加入的牛的范围是限制在 $[0,1000]$ 的而被动加入的牛至多形成形如三角形的形状，故这道题最多有 $2000000$ 头奶牛，显然在可接受范围内。

于是我们直接暴力加牛并暴力扩展即可。

---

## 作者：LiuQJun_1119 (赞：1)

这道题算是道简单的模拟题？

用 mp 数组记录每个格子四周的奶牛数，找舒适的奶牛，在它四周的空位放奶牛就可以了。

注意放的奶牛也可能成为舒适的奶牛，所以要一直递归下去，直到没有舒适的奶牛为止。
```
#include<bits/stdc++.h>
using namespace std;
const int N=5005,dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
int n,x,y,mp[N+10][N+10],ans;
bool bz[N+5][N+5];
void fin(int x,int y);
void addcow(int x,int y){//加奶牛
	if(bz[x][y]){
		ans--;
		return;
	}
	bz[x][y]=true;
	for(int i=0;i<4;i++){
		int xx=x+dx[i],yy=y+dy[i];
		mp[xx][yy]++;//更新地图
	}
	if(mp[x][y]==3){
		ans++;
		fin(x,y);//找四周没有奶牛的地方
	}
	for(int i=0;i<4;i++){
		int xx=x+dx[i],yy=y+dy[i];
		if(bz[xx][yy]&&mp[xx][yy]==3){//找舒适的奶牛
			ans++;
			fin(xx,yy);
		}
	}
    //因为当前位置加了奶牛，只有四周和当前位置会更新，所以只用判断这几个位置有没有舒适的奶牛
}
void fin(int x,int y){
	for(int i=0;i<4;i++){
		int xx=x+dx[i],yy=y+dy[i];
		if(!bz[xx][yy]){
			addcow(xx,yy);//加奶牛使在(x,y)的奶牛不舒适
			return;
		}
	}
}
int main(){
	scanf("%d",&n);
	while(n--){
		scanf("%d%d",&x,&y);
		x+=520,y+=520;//防止越界
		addcow(x,y);
		printf("%d\n",ans);//输出
	}
}
```

---

## 作者：_Aghost (赞：1)

### 题目大意
从前往后依次加奶牛，如果有一个奶牛周围有三个奶牛，那么就需要把周围那个没有奶牛的位置填上。
### 注意事项
- 因为填了这个奶牛可能造成其他奶牛从不舒适变为舒适，所以需要一个$DFS$的过程。
-  注意加入的奶牛的 $xx$ 和 $yy$ 坐标并不一定需要在范围$0-1000$内，那么坐标可能出现负数，只需要给每个坐标都加上一个数即可。
- 如果加奶牛时发现这个位置上已经有了奶牛，那么就说明这个奶牛是之前新加的，加了这个奶牛之后之前的也没有必要加，所以让$ans$--。
- 对于判断一个位置是不是舒适的，前提是这个位置必须要有奶牛。


```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N =1e5+10;
int dx[5]={0,1,-1,0,0};
int dy[5]={0,0,0,1,-1};
int n,x[N],y[N],ans;
bool v[3010][3010];
bool pan(int x,int y)
{
	int k=0;
	if(!v[x][y]) return false;
	for(int i=1;i<=4;i++)
	{
		int fx=x+dx[i];
		int fy=y+dy[i];
		if(v[fx][fy]) k++;
	}
	if(k==3) return true;
	return false;
}
void dfs(int x,int y)
{
	for(int i=1;i<=4;i++)
	{
		int xx=x+dx[i];
		int yy=y+dy[i];
		if(!v[xx][yy]){
			ans++;
			v[xx][yy]=true;
			if(pan(xx,yy))
			dfs(xx,yy);
			for(int j=1;j<=4;j++)
			{
				int jx=xx+dx[j];
				int jy=yy+dy[j];
				if(pan(jx,jy)==true&&v[jx][jy])
				dfs(jx,jy);
			}
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
	scanf("%d%d",&x[i],&y[i]);
	x[i]+=510;
	y[i]+=510;
	}
	for(int i=1;i<=n;i++)
	{
		if(v[x[i]][y[i]])
		{
			ans--;
			printf("%d\n",ans);
			continue;
		}
		v[x[i]][y[i]]=true;
		if(pan(x[i],y[i])==true)
		dfs(x[i],y[i]);
		for(int j=1;j<=4;j++)
		{
			int fx=x[i]+dx[j];
			int fy=y[i]+dy[j];
			if(pan(fx,fy)==true)
			dfs(fx,fy);
		}
		printf("%d\n",ans);
	}
}
/*
9
0 1
1 0
1 1
1 2
2 1
2 2
3 1
3 2
4 1*/
```


---

