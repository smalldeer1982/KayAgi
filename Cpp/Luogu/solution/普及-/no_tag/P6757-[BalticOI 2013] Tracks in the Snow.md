# [BalticOI 2013] Tracks in the Snow

## 题目描述

有一个含 $H$ 行，$W$ 列的字符矩阵，初始全为 `.`。

有两种动物，狐狸和兔子，将会从左上角走到右下角，狐狸会留下 `F` 的痕迹，兔子会留下 `R` 的痕迹。

痕迹会相互覆盖。

走路规则如下：
- 可以往返走；
- 不可以走对角线；
- 不可以跳格子；
- 不可能有两只动物一起走。

现在您得到了这个被动物们走过的矩阵，请求出至少有几个动物走过了该矩阵。

## 说明/提示

#### 数据范围及限制
- 对于 $30$ 分的数据，保证答案 $\le 200$，$H,W\le 500$。
- 对于 $100\%$ 的数据，保证 $1\le H,W\le 4\times 10^3$，答案 $\ge 1$，读入的字符只会是 `.` 或 `R` 或 `F`。

#### 说明
本题译自 [Baltic Olympiad in Informatics 2013](https://boi.cses.fi/tasks.php) [Day 2](https://boi.cses.fi/files/boi2013_day2.pdf) T2 Tracks in the Snow。

## 样例 #1

### 输入

```
5 8
FFR.....
.FRRR...
.FFFFF..
..RRRFFR
.....FFF```

### 输出

```
2```

# 题解

## 作者：THM200000000 (赞：12)

# [P6757 Tracks in the Snow](https://www.luogu.com.cn/problem/P6757) 题解
## 题意
有两种小动物从一个矩阵的左上角开始~~到处乱逛~~，到右下角结束，**每一时刻仅有一只小动物在矩阵上**，狐狸走过的地方被标记为 `F`，兔子走过的地方被标记为 `R`，无小动物经过的点为 `.`，标记可被覆盖，先给出最后的矩阵，问**至少**有几只小动物经过。
## 思路
由于脚印可以覆盖，那么下一只小动物经过的地方上一只使可以随便踩的，故考虑**倒推**。为了使经过的小动物最少，在倒推过程中每只小动物必须将可以踩的地方都踩完，所以可以理解为是一个**不断扩散联通块**的过程。

同样可以证明，两种小动物**交替经过**（即不会出现连续两次经过同样的动物）时，实现给出矩阵所需的小动物最少。

## 实现
在经过上述分析之后，想要实现并不难，只需不断**洪水填充**不断**取反**和**扩张**，直到填完所有 `F` 和 `R` 即可，假设需要填充 $x$ 次才能结束，那么算法的复杂度为 $O(nmx)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define chg(x) (x == 'R'? 'F' : 'R') //宏定义，便于在填充时进行取反 
char a[4010][4010];
int n, m;
int filled; //记录每次填充的面积
int now; //记录当前填充的面积
int ans; //结果，即需要填充的次数
void dfs(int x, int y, char tp) { //洪水填充
	if(a[x][y] != tp) return ;
	if(x == 0 || x == n + 1 || y == 0 || y == m + 1) return ; //判边界
	a[x][y] = chg(tp); //取反
	++filled; //填充时记录一次
	dfs(x + 1, y, tp);
	dfs(x - 1, y, tp);
	dfs(x, y + 1, tp);
	dfs(x, y - 1, tp);
}
signed main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> a[i] + 1;
	do {
		now = filled;
		filled = 0;
		dfs(1, 1, a[1][1]);
		++ans;
	} while(filled > now); //验证是否与上一次重合，如果是，则跳出循环
	cout << ans - 1; //由于需要多花一次填充来判断是否结束，所以输出时应减一 
	return 0;
}
```
然而结果不尽人意，只有可怜的[ 55 分](https://www.luogu.com.cn/record/179478055)。

看到评测结果的 `TLE` 和 `MLE` 不难想到其实是因为大量得重复搜索导致的，由于本代码是不断洪水填充来达到扩张的，**根本目的是扩张**，那么原来搜过的地方就不用搜了。

How? 可在每次搜索时通过栈（或者队列，原理相似）来存储下次搜索的起点，再次搜索时就由这些位置开始（当然在栈中同属一个联通快的点只搜一次就行了，其他的点可以舍去）这样就可以大量地跳过搜过的区域了，复杂度 $O(nm)$。

由于计入下次搜的起点的时候约等于实在找联通快的**边界**，那么数组大小开到矩阵面积的一半（即 $8\times10^6$）即可。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define chg(x) (x == 'R'? 'F' : 'R') //宏定义，便于将足迹取反 
struct point {
	int x, y;
};
char a[4010][4010];
bool vis[4010][4010];
int n, m;
point nxt[80000010]; //以栈的形式记录当前下一次开始填充的位置
point now[80000010];           //记录当前开始填充的位置
int t; //充当nxt[]的栈顶指针
int l; //表示now[]的长度
char tp;
int ans; //结果，即需要填充的次数
void dfs(int x, int y) { //洪水填充
	if(a[x][y] == '.' || vis[x][y]) return ;
	if(a[x][y] == chg(tp)) {
		nxt[++t] = {x, y}; //存入下次开始填充的位置
		return ;
	}
	if(x == 0 || x == n + 1 || y == 0 || y == m + 1) return ;
	vis[x][y] = true; //标记
	dfs(x + 1, y);
	dfs(x - 1, y);
	dfs(x, y + 1);
	dfs(x, y - 1);
}
signed main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> a[i] + 1; //读入（废话
	t = 1;
	nxt[t] = {1, 1};
	tp = a[1][1]; //记录开始填充时对应的符号
	do {
		if(t) {
			l = t;
			for(int i = 1; i <= l; i++)
				now[i] = nxt[i]; //刷新填充起点
			t = 0;
			for(int i = 1; i <= l; i++) {
				if(!vis[now[i].x][now[i].y])
					dfs(now[i].x, now[i].y);
			}
			++ans;
		} else break;
		tp = chg(tp); //取反
	} while(t); //验证是否能继续搜
	cout << ans;
	return 0;
}
```
可见评测结果绿了不少，但是~~区区~~[ 92 分](https://www.luogu.com.cn/record/179470214)我们是绝对不能满意的。由于数组开的全是静态，所以 `MLE` 的罪魁祸首只能是**洪水填充**的过程，怎么处理呢？由于当我们存入下次搜索时的数据结构的栈，那么这事我不禁想起了当年学深搜用的~~幼儿园写法~~：**用栈来搜**（当然如果存的时候用的是队列那么广搜也是可以的）。这样可以大大减少递归时消耗的内存，那么这里不多解释，代码里见！

```cpp
#include<bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
using namespace std;
#define chg(x) (x == 'R'? 'F' : 'R') //宏定义，便于将足迹取反 
struct point { //定义结构体，便于入栈 
	int x, y;
};
char a[4010][4010]; //读入的矩阵
bool vis[4010][4010]; //用以标记搜过的位置（这应该不用过多解释吧）
int n, m; //矩阵长宽
point nxt[80000010]; //以栈的形式记录当前下一次开始填充的位置
point now[160000010]; //栈，用于DFS
int t; //充当nxt[]的栈顶指针
int l; //表示now[]的长度
int ans; //结果，即需要填充的次数
point tmp; //表示DFS过程中当前搜到的位置
void dfs(char tp) { //洪水填充
	while(l) {
		tmp = now[l--];
		if(a[tmp.x][tmp.y] == chg(tp)) {
			nxt[++t] = tmp; //存入下次开始填充的位置
			continue;
		}
		vis[tmp.x][tmp.y] = true; //标记
		if(a[tmp.x + 1][tmp.y] != '.' && !vis[tmp.x + 1][tmp.y] && tmp.x != n) //入栈
			now[++l] = {tmp.x + 1, tmp.y};
		if(a[tmp.x - 1][tmp.y] != '.' && !vis[tmp.x - 1][tmp.y] && tmp.x != 1)
			now[++l] = {tmp.x - 1, tmp.y};
		if(a[tmp.x][tmp.y + 1] != '.' && !vis[tmp.x][tmp.y + 1] && tmp.y != m)
			now[++l] = {tmp.x, tmp.y + 1};
		if(a[tmp.x][tmp.y - 1] != '.' && !vis[tmp.x][tmp.y - 1] && tmp.y != 1)
			now[++l] = {tmp.x, tmp.y - 1};
	}
}
signed main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> a[i] + 1; //读入（废话
	t = 1;
	nxt[t] = {1, 1}; //将搜索的起点压栈
	int tp = a[nxt[t].x][nxt[t].y]; //记录开始填充时对应的符号
	do {
		if(t) {
			l = t;
			for(; t; --t)
				now[t] = nxt[t]; //刷新填充起点
			for(int i = 1; i <= l; i++) {
				if(!vis[now[i].x][now[i].y]) //排除已经搜过但仍在栈中的情况
					dfs(tp);
			}
			++ans;
		} else break;
		tp = chg(tp); //取反
	} while(t); //验证是否能继续搜
	cout << ans;
	I AK IOI; //完美收场
}
```
结果：[$\huge\textrm {完美无瑕}$\
![](https://cdn.luogu.com.cn/upload/image_hosting/6d11yroc.png)](https://www.luogu.com.cn/record/179470536)

50 个点AC真的爽！

另外蒟蒻调代码调了三个多小时，题解写了也近一个小时，甚至最后的代码都是在回家路上的地铁上写的......可以......留个小小的赞吗`= )`。

---

## 作者：zfhzzzzzzzzzzz (赞：6)

# 题意
两种动物从矩阵左上走到右下，会留下两种脚印，脚印会覆盖，给出所有动物走完后脚印图，问至少有几只动物。

# 分析
因为要求动物只数尽量少，所以我们便理解为两种动物轮流走。不会有两只同种动物先后走。

首先确定哪种动物最后走。从左上角找联通块，那么这就是最后一只动物走的足迹。如样例1最后走的是狐狸。

为了保证答案最优，找到联通块之后，把它取反，代表最后一只动物覆盖了倒数第二只动物的足迹，再找联通块，找到了倒数第二只动物的足迹，以此类推。

如图：
```
FFR.....    
.FRRR...      
.FFFFF..
..RRRFFR      
.....FFF  
```

变为
```
RRR.....
.RRRR...
.RRRRR..
..RRRRRR
.....RRR
```


# Code

```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
	x=x*10+ch-'0';
	ch=getchar();
}
	return x*f;
}
void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
	return;
}
//以上快读快写
int dx[4]={0, 0,1,-1};
int dy[4]={1,-1,0, 0};//方向
int n,m,ans;
int a[4001][4001];
bool vis[4001][4001];
char c[4001];
queue<pair<int,int> >q[2];//q[0]:F q[1]:R

bool bfs(int s) {
	bool fl=0;
	while (!q[s].empty()) {
		int x=q[s].front().first, y=q[s].front().second;
		q[s].pop();
		for(int i=0;i<4;i++) {
			int fx=x+dx[i],fy=y+dy[i];
			if(fx>0&&fx<=n&&fy>0&&fy<=m&&a[fx][fy]&&!vis[fx][fy]){
				vis[fx][fy]=1;
				if(a[x][y]==a[fx][fy]) 
					q[s].push(make_pair(fx,fy));
				else{
					q[s^1].push(make_pair(fx,fy));
					fl=1;
				}
			}
		}
	}
	return fl;
}

int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);
		for (int j=1;j<=m;j++){//数字存图
			if(c[j]=='R') a[i][j]=1;
			else if (c[j]=='F') a[i][j]=2;
			else a[i][j]=0;
		}
	}
	q[0].push(make_pair(1,1));
	vis[1][1] = 1;
	for(int i=0;bfs(i);i^=1,ans++);
	write(ans+1);
}
```

---

## 作者：Starlight_Glimmer (赞：4)

[My Blog](https://www.cnblogs.com/lyttt/p/14038257.html)

[题目链接](https://www.luogu.com.cn/problem/P6757)

### 题目解析

啊咧，是一道卡时间卡空间的好题目（划掉

我们可以先找到最后那只小动物最多能走过的结点，就是和左上角相连的一整个四联通连通块。（以下所有连通块都是指四联通

然后发觉这个连通块就可以让所有的小动物随便走了，因为无论如何走，最后总会被最后一只小动物覆盖。

那么把和这个连通块相连的其它连通块相连，可以通过第一个连通块枢纽一下就可以相互到达的连通块之间可以由同一个小动物来走。

考场上刚开始想要用并查集来写，先$dfs$一次把所有连通块缩成一个点，然后再$dfs$连边，算这些点到左上角连通块代表的那个点的距离的最大值就是答案。

然而这样时间和空间都不够优秀~~（所以就自闭了~~，本来想拿个部分分结果我这个算法写错了不太调得出来就开始重新想。

我们发现这个过程其实是在不断扩展联通块的过程。

从最后一个小动物的足迹形成的连通块开始，往相邻的另外一种足迹扩展，表示第二只小动物，形成一个新的大连通块就是这两只小动物的足迹范围，然后同理再次扩展，直到把所有的点都合在一起，答案就是扩展次数$+1$（加上最开始的连通块

~~当时有点自暴自弃，没有想到这就是接近正解的想法呢。~~

于是就可以先$dfs$第一个连通块，相同的就继续搜，不同的就丢到队列里（这就是我们下一只小动物扩展的地方）。然后从队列里取结点开始搜，搜过的地方打上标记可以不用再搜，理论上是$O(n^2)$的时间复杂度。

然后你就可以得到$90pts$的好成绩（雾（事实上，我考试的时候编号写挂了，挂成了$60pts$，惨

因为我写的$dfs$，会占用栈空间导致本不富裕的空间限制雪上加霜。

所以可以写$bfs$来规避掉这一点。

------

另外贴一个听评讲时的另外一种理解思路：

当某只动物走过雪地后，左上角和右下角必定是这种动物的足迹，且这两点之间有一个这种足迹形成的连通块，不妨设是兔子$(R)$。

很明显，若只有$R$，那么只需要$1$只动物即可；如果存在$F$，那么至少也要$2$只动物。

考虑什么情况下会有更多只动物。

所有与起点相连通的$R$，全都可以最后一只兔子完成，而如果某个足迹$R$被$F$包围成圈而无法与起点连通，那么肯定需要提前有一只兔子先走到这里，再让一只狐狸覆盖掉周围的足迹，最后再让一只兔子走一遍，这样就需要$3$只动物了。

容易发现，这种情况还可能会嵌套，即$R$和$F$交替地形成圆圈包围住另一种足迹，每多一圈就需要多一只动物。

于是可以把问题转化为：相邻的同种足迹之间边权为$0$，异种足迹之间边权为$1$，求出起点到所有点的最短路径，最短路径的最大值$+1$即为最少需要的动物数量。

这种只有$0/1$边权的问题是一个比较经典的可以用双端队列来解决的问题，把边权为$0$的塞到前端，边权为$1$的塞到后端。当然，写两个队列分开放也可以，这个连通块扩展的过程一定是交替的。

~~（不知道为啥打小动物的时候全程想到调查土壤小动物的丰富度，虽然这是兔子和狐狸，生物杀我qwq~~



------

### ►Code View

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
#define N 4005
#define M 16000005
#define INF 0x3f3f3f3f
#define LL long long
int rd()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return f*x;
}
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
int n,m,ans;
char s[N][N];
bool vis[N][N];
queue<int>Q[2];
inline bool check(int i,int j)
{
	if(i<1||i>n||j<1||j>m||s[i][j]=='.'||vis[i][j]) return 0;
	return 1;
}
void bfs()
{
	int now;
	if(s[1][1]=='R') Q[0].push(1),now=0;
	else Q[1].push(1),now=1;
	while(!Q[now].empty())
	{
		while(!Q[now].empty())
		{
			int x=Q[now].front();Q[now].pop();
			int j=x%m,i=x/m+1;
			if(j==0) j=m,i--;
			if(vis[i][j]) continue;
			vis[i][j]=1;
			for(int k=0;k<4;k++)
			{
				int x=i+dx[k],y=j+dy[k];
				if(!check(x,y)) continue;
				if(s[x][y]==s[i][j]) Q[now].push((x-1)*m+y);
				else Q[now^1].push((x-1)*m+y);
			} 
		}
		now^=1;
		ans++;
		//这个队列清完了 扩展另外一种颜色 答案++ 
	}
}
int main()
{
	freopen("track.in","r",stdin);
	freopen("track.out","w",stdout);
	n=rd(),m=rd();
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	bfs();
	printf("%d\n",ans);
	return 0;
}



```

### ►Code View Ver.2 dfs MLE

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
#define N 4005
#define M 16000005
#define INF 0x3f3f3f3f
#define LL long long
int rd()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return f*x;
}
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
int n,m,tot;
char s[N][N];
bool id[N][N];
queue<pair<int,int> >Q;
inline bool check(int i,int j)
{
	if(i<1||i>n||j<1||j>m||s[i][j]=='.'||id[i][j]) return 0;
	return 1;
}
inline void dfs(int i,int j,int num)
{
	id[i][j]=1;
	for(register int k=0;k<4;k++)
	{
		int x=i+dx[k],y=j+dy[k];
		if(!check(x,y)) continue;
		if(s[x][y]==s[i][j])
		{
			id[x][y]=1;
			dfs(x,y,num);
		}
		else Q.push(make_pair((x-1)*m+y,num+1));
	}
}
int main()
{
	freopen("track.in","r",stdin);
	freopen("track.out","w",stdout);
	n=rd(),m=rd();
	for(register int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	dfs(1,1,1);
	int ans=1;
	while(!Q.empty())
	{
		pair<int,int> x=Q.front();Q.pop();
		int j=x.first%m,i=x.first/m+1;
		if(j==0) j=m,i--;//Cao 这里打掉了 惨挂30pts
		if(!id[i][j])
			dfs(i,j,x.second);
		ans=max(ans,x.second);
	}
	printf("%d\n",ans);
	return 0;
}
/*
5 8
FFR.....
.FRRR...
.FFFFF.. 
..RRRFFR 
.....FFF
*/
/*
把连通块从最开始的情况扩张
扩张多少次所有点在一个集合里
*/
```



---

## 作者：elainya_stars (赞：4)

# P6757 [BalticOI2013] Tracks in the Snow 题解

### [题目传送门](https://www.luogu.com.cn/problem/P6757)

~~啊咧，是一道卡时间卡空间的好题目~~

我们可以先找到最后那只小动物最多能走过的结点，就是和左上角相连的一整个四联通连通块。（以下所有连通块都是指四联通

然后发觉这个连通块就可以让所有的小动物随便走了，因为无论如何走，最后总会被最后一只小动物覆盖。

那么把和这个连通块相连的其它连通块相连，可以通过第一个连通块枢纽一下就可以相互到达的连通块之间可以由同一个小动物来走。

刚开始想要用并查集来写，先 dfs 一次把所有连通块缩成一个点，然后再 dfs 连边，算这些点到左上角连通块代表的那个点的距离的最大值就是答案。

然而这样时间和空间都不够优秀（所以就自闭了，本来想拿个部分分结果我这个算法写错了不太调得出来就开始重新想呜呜呜...）

## 正文

我们发现这个过程其实是在不断扩展联通块的过程。

从最后一个小动物的足迹形成的连通块开始，往相邻的另外一种足迹扩展，表示第二只小动物，形成一个新的大连通块就是这两只小动物的足迹范围，然后同理再次扩展，直到把所有的点都合在一起，答案就是扩展次数 $+1$（加上最开始的连通块

（当时有点自暴自弃，没有想到这就是接近正解的想法呢。）

于是就可以先 dfs 第一个连通块，相同的就继续搜，不同的就丢到队列里（这就是我们下一只小动物扩展的地方）。然后从队列里取结点开始搜，搜过的地方打上标记可以不用再搜，理论上是 $O(n^2)$ 的时间复杂度。

然后你就可以得到 $90$ 分的好成绩（雾

因为写 dfs 会占用栈空间导致本不富裕的空间限制雪上加霜，所以可以写 bfs 来规避掉这一点。

## 代码如下（好难写啊）

```cpp
#include<bits/stdc++.h>
using namespace std;

#define N 4005
#define M 16000005
#define INF 0x3f3f3f3f
#define LL long long

const int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
int n,m,ans;
char s[N][N];
bool vis[N][N];
queue<int> Q[2];

int read();
void bfs();
inline bool check(int,int);

int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	  scanf("%s",s[i]+1);
	bfs();
	printf("%d\n",ans);
	return 0;
}

int read() // 快读
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
		if(c=='-')
		  f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return f*x;
}

void bfs()
{
	int now;
	if(s[1][1]=='R')
	{
		Q[0].push(1);
		now=0;
	}
	else
	{
		Q[1].push(1);
		now=1;
	}
	while(!Q[now].empty())
	{
		while(!Q[now].empty())
		{
			int x=Q[now].front();
			Q[now].pop();
			int j=x%m,i=x/m+1;
			if(!j)
			  j=m,i--;
			if(vis[i][j])
			  continue;
			vis[i][j]=1;
			for(int k=0;k<4;k++)
			{
				int x=i+dx[k],y=j+dy[k];
				if(!check(x,y))
				  continue;
				if(s[x][y]==s[i][j])
				  Q[now].push((x-1)*m+y);
				else
				  Q[now^1].push((x-1)*m+y);
			} 
		}
		now^=1;
		ans++;
		// 这个队列清完了 扩展另外一种颜色 答案++ 
	}
	return ;
}

inline bool check(int i,int j)
{
	if(i<1 || i>n || j<1 || j>m || s[i][j]=='.' || vis[i][j])
	  return false;
	return true;
}
```
看到这里的哥哥姐姐们给个点赞再走喵~

---

## 作者：lucasincyber (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P6757)
## 思路
首先，我们可以发现，当前 $(1,1)$ 位置是什么脚印，那最后走的动物就是哪一个。而因为脚印会相互覆盖，且我们要求来的动物的最小值，所以每一种动物是交替来的。

这时候，问题就成了求连通块（由题意得，**连通** 的定义为四面连通）。每一次将连通块的脚印变成另一种动物的脚印。这样能持续多少次，就有几只动物来过。

这里求连通块可以使用广搜求解。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 4e3 + 5;

struct point
{
	int x, y;
};

int h, w, cnt, ans;
bool flag;
char mp[N][N];
bool vis[N][N];
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
queue<point> q[2]; // 分别记录两个脚印的队列

void bfs(int t) // 广搜
{
	int x = t & 1; // 哪一种动物（交替）
	q[x].push({1, 1});
	vis[1][1] = 1;
	while (q[x].size())
	{
		point u = q[x].front();
		q[x].pop();
		for (int i = 0; i < 4; i++)
		{
			int bx = u.x + dx[i], by = u.y + dy[i];
			if (bx <= 0 || bx > h || by <= 0 || by > w || mp[bx][by] == '.' || vis[bx][by]) continue;
			vis[bx][by] = 1;
			if (mp[bx][by] == mp[u.x][u.y]) q[x].push({bx, by});
			else // 还有没有其他动物来过
			{
				q[x ^ 1].push({bx, by});
				flag = 1;
			}
		}
	}
}

int main()
{
	scanf("%d%d", &h, &w);
	for (int i = 1; i <= h; i++)
		for (int j = 1; j <= w; j++)
			cin >> mp[i][j];
	flag = 1;
	while (flag)
	{
		flag = 0, cnt++;
		bfs(cnt);
		ans++;
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：too_later (赞：2)

[P6757 \[BalticOI2013\] Tracks in the Snow](https://www.luogu.com.cn/problem/P6757)

### 题意：

有一个矩形，初始都为 `'.'`。

现在有两个不懂事的小孩，轮流从左上角走到右下角。当且仅当对方走完了自己才能走完。

- 每次只能上下左右移动一个格子

- 可以往回走

每次走路都会留下脚印，第一个孩子的脚印为 `F`，第二个孩子脚印为 `R`。

当然，脚印会覆盖。

现在给出最终的脚印，求出他们至少走了几轮？（一个人从左上角到右下角就算一轮）

$1\le n,m\le 4000$。

### 思路：

最终这个图的起点和终点一定是最后那个人走的。

那么考虑最后一个人走的时候：

- 如果这个脚印是最后一个人踩过的，那么之前是 `F`, `R` 无所谓。

  这里的踩过指的是可以到达。因为就算是前人到过，那么和现在到。肯定是现在到总步数少。

- 如果这个脚印和最后一个人的相反，或者最后一个人到不了这个脚印，那么之前必须是另一个人走过的这个脚印。

那么，每次从起点出发，寻找连通块，不断扩展完全地图即可。

### Code:

```cpp
#include<bits/stdc++.h>
#define I inline
using namespace std;
const int N=4005;
int dx[5]={0,0,-1,1},dy[5]={1,-1,0,0};
int n,m,ans;
short a[N][N];
bool vis[N][N];
char c[N][N];
struct node{
	int x,y;
	node(int xx,int yy){
		x=xx,y=yy;
	}
};
I int bfs(){
	queue<node> q[2];
	bool now=a[1][1];
	q[now].push(node(1,1));
	while(!q[now].empty()){
		while(!q[now].empty()){
			node u=q[now].front();q[now].pop();
			if(vis[u.x][u.y])continue;vis[u.x][u.y]=1;
			for(int k=0;k<4;k++){
				int tx=u.x+dx[k],ty=u.y+dy[k];
				if(a[tx][ty]==(1^now)&&!vis[tx][ty])
					q[now^1].push(node(tx,ty));
				if(a[tx][ty]==now&&!vis[tx][ty])
					q[now].push(node(tx,ty));
			}
		}
		now^=1;ans++;
	}
	return ans;
}
int main(){
	scanf("%d%d",&n,&m);
	memset(a,-1,sizeof(a));
	for(int i=1;i<=n;i++){
		scanf("%s",c[i]+1);
		int len=strlen(c[i]+1);
		for(int j=1;j<=len;j++){
			if(c[i][j]=='.')a[i][j]=-1;
			if(c[i][j]=='F')a[i][j]=0;
			if(c[i][j]=='R')a[i][j]=1;
		}
	}
	printf("%d\n",bfs());
	return 0;
}
```

---

## 作者：Aragron_II (赞：2)

### [雪地足迹](https://www.luogu.com.cn/problem/P6757) 题解


------------

题意：

一个 $ n∗m $ 的雪地，有两种动物 $ R $ 和 $ F $ 会在雪地上留下 $ R $ 和 $ F $ 的脚印(只可以走到相邻格子，从 $ (1,1) $ 进入 $ (n,m) $出来，且会覆盖掉原先的脚印)。

求至少有多少只动物经过.



------------


其实这题就是用 $ BFS $ 求联通块的题目。

首先我们知道 $ (1,1) $ 所在的联通块必定是最后一只经过的动物，因为要求最少，所以我们优先选择整个联通块作为最后一只动物。

然后由这个联通块开始向外扩展另一种脚印的联通块，之后不停扩展直到扩完为止。



------------

####  注意： 

这道题卡的还挺紧的

![https://cdn.luogu.com.cn/upload/image_hosting/v1kguqyv.png](https://cdn.luogu.com.cn/upload/image_hosting/v1kguqyv.png)

正常解出来会出现  #11  个点会  T  ,导致只有99分，如果想得满分建议添加:

快读，手动 $ O2 $ 等，如：
```
#pragma GCC optimize ("O2")
%:pragma GCC optimize("Ofast")
%:pragma GCC optimize("inline")
```

最后上代码：
```
#include <bits/stdc++.h>
#pragma GCC optimize ("O2")
%:pragma GCC optimize("Ofast")
%:pragma GCC optimize("inline")
//优化代码
using namespace std;
char mp[4001][4001];
bool vis[4001][4001];
int n,m,c[4001][4001],ans;
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};
//方向数组
struct node {
	int x;
	int y;
};
template <typename T> inline void read(T &R) {
	T x = 0,flag = 1;
	char ch = getchar();
	while ( !isdigit(ch) ) { 
		if ( ch == '-' ) flag = -1;
		ch = getchar(); 
	}
	while ( isdigit(ch) )  { 
		x = ( x << 1 ) + ( x << 3 ) + ch - '0';
		ch = getchar(); 
	}
	R = flag * x;
}
//快读
inline void bfs() {
	//BFS求联通块
	queue < node > Q[2];
	bool now = 0;
	Q[now].push( ( node ) { 1,1 } );
	vis[1][1] = true;
	while ( Q[now].size() ) {
		while ( Q[now].size() ) {
			node x = Q[now].front();
			Q[now].pop();
			for ( register int i = 0; i < 4; i ++ ) {
				int lx = x.x+dx[i];
				int ly = x.y+dy[i];
				node y = (node) { lx, ly };
				if ( y.x<1 || y.y<1 || y.x>n || y.y>m ) 
					continue;
            //如果越界，直接进入下一轮循环
				if ( vis[y.x][y.y] || mp[y.x][y.y] == '.' ) 
					continue;
             //如果已经走过或没有动物走过，直接进入下一轮循环
				bool judge = ( mp[y.x][y.y] != mp[x.x][x.y] );
				vis[y.x][y.y] = true;
				c[y.x][y.y] = c[x.x][x.y] + judge;
				Q[now^w].push(y);
			}
		}
		now ^= 1;
	}
	return;
}
int main() {
	read (n); read (m);
	for ( register int i = 1 ; i <= n; i ++ ) 
		gets ( mp[i] + 1 ); //输入
	bfs(); 
	ans = 0;
	for ( register int i = 1; i <= n; i ++ ) 
		for ( register int j = 1;j <= m; j ++ )
			ans = max ( ans, c[i][j] );
	printf ( "%d", ans + 1 );
	return 0;
}
```


---

## 作者：__^浅笑.__ (赞：0)

正经题解。

**题目大意：**

有一个含 $H$ 行，$W$ 列的字符矩阵，初始全为 `.`。

有两种动物，狐狸和兔子，将会从左上角走到右下角，狐狸会留下 $F$ 的痕迹，兔子会留下 $R$ 的痕迹。

痕迹会相互覆盖。

走路规则如下：
- 可以往返走；
- 不可以走对角线；
- 不可以跳格子；


**特殊要求：**

- 不可能有两只动物一起走。

**思维逻辑**

可以使用 DFS 深度优先搜索来解决。

~~但是切记不要使用题解优先搜索！~~

- 边界条件判断：如果超出地图或者已经搜索过，或者不是留下的痕迹，当前脚印已经不是原来的，那么终止继续循环下去。
```c
if (x < 0 || x >= H || y < 0 || y >= W || vis[x][y] || mp[x][y]=='.' || mp[x][y] != awa) {
  return;
}
```

接下来进行递归。
- 首先标记当前地点已经走过。
```c
vis[x][y] = true;
```

- 然后 dfs 递归，依次枚举每一个位置。
```c
dfs(x + 1, y); // 下 
dfs(x - 1, y); // 上
dfs(x, y + 1); // 右 
dfs(x, y - 1); // 左
```

- 最后，整个 dfs 的函数就写完了，函数的参数如下展示一下。
```c
void dfs(int x, int y)
```

**Code：**
- 变量的定义部分：
```c
char mp[4005][4005];
bool vis[4005][4005];
int n,m;
```
- 主函数。

首先输入整个矩阵。
```c
cin >> n >> m;
for (int i = 0; i < n; ++i) {
  for (int j = 0; j < m; ++j) {
    cin >> mp[i][j];
    vis[i][j] = false;
  }
}
```
然后进行查找累加，这里就不分解了。
```c
int sum = 0;
for (int i = 0; i < n; ++i) {
  for (int j = 0; j < m; ++j) {
    if (!vis[i][j] && mp[i][j] != '.') {
      awa = mp[i][j];
      dfs(i, j);
      sum++;
    }
  }
}

    cout << sum << endl;
```

整体代码放在了[这里](https://www.luogu.com.cn/paste/0wwrwcds)

---

## 作者：hymcr05 (赞：0)

[博客体验更好哦](https://www.hymcr05.fun/2024/10/11/Tracks-in-the-Snow/)
## 题目大意

矩阵中的每个单元格可以是空的（用 `.` 表示），或者被狐狸（用 `F` 表示）或兔子（用 `R` 表示）覆盖。\
我们需要找出至少有多少只动物走过，这意味着我们需要计算不同动物痕迹的最小数量。

## 解题思路

我们可以**理解题目为两种动物轮流走**。

因为我们为了求动物只数尽量少，我们应该**先确定哪种动物最后走**（因为给出的是所有动物走完后的图像）。

**从左上角找联通块，那么这就是最后一只动物走的足迹**。如样例 1 最后走的是狐狸。

为了保证答案最优，**找到联通块之后，把它设置为另一个动物走过的印记**，代表最后一只动物覆盖了倒数第二只动物的足迹，再找联通块，直到找到了倒数第二只动物的足迹，以此类推。

**如下样例**

```
FFR.....    
.FRRR...      
.FFFFF..
..RRRFFR      
.....FFF
```

**处理后**

```
RRR.....
.RRRR...
.RRRRR..
..RRRRRR
.....RRR
```

不理解的可以看代码理解。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 4e3 + 10;
int n, m, ans, mp[N][N];
bool vis[N][N];
int dx[] = {0, 0, 0, -1, 1}, dy[] = {0, 1, -1, 0, 0};//方向数组。
queue<pair<int, int> > q[2];//开两个队列，分别表示 F 和 R。
bool bfs(int s) {
    bool fl = 0;
    while (!q[s].empty()) {
        int x = q[s].front().first, y = q[s].front().second;
        q[s].pop();//基本的 BFS 操作。
        for (int i = 1; i <= 4; i++) {
            int xx = x + dx[i], yy = y + dy[i];
            if (xx > 0 && xx <= n && yy > 0 && yy <= m && mp[xx][yy] &&
                !vis[xx][yy]) {
                vis[xx][yy] = 1;
                if (mp[x][y] == mp[xx][yy])//两个点一样。
                    q[s].push(make_pair(xx, yy));//直接推进去。
                else {//不一样
                    q[!s].push(make_pair(xx, yy));//取反。
                    fl = 1;//标记还找不找得到不同的脚印。
                }
            }
        }
    }
    return fl;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            mp[i][j] = (c == 'R' ? 1 : ((c == 'F') ? 2 : 0));  // 极品三目运算符， 转换为数字方便BFS。
        }
    q[0].push(make_pair(1, 1));
    vis[1][1] = 1;
    /*初始化*/
    for (int i = 0; bfs(i); i = !i, ans++);
    cout << ans + 1;//答案记得加一，BFS统计的是倒数第2个脚印。
    return 0;
}

```

---

## 作者：dsj2012 (赞：0)

# 简化题意
会有一些动物从一个矩阵的左上角到达右下角。动物走过后会留下脚印，脚印会覆盖。告诉动物走过之后的脚印图，问最少有多少只动物。
# 思路
首先题目要求我们的动物数量要尽可能的小。还有动物最多就只有两种，那么我们就可以轮流走两种动物。

我们的同一种动物是不能重复走的，例如假设有一只动物到达了一个点后，又有同一种类的动物再次到达。那么我们的第一只动物是可以走第二只动物达到的路线的。

这个时候我们其实只要一只动物，但是我们却用了两只动物。所以，我们的同一种类的动物不能重复走。如果可以重复走说明我们不需要第二只动物。

那么先走哪一种动物呢，很简单，脚印会覆盖那么左上角的脚印一定是最后走的这只动物。

然后我们就可以从后往前推，找到了那只动物的足迹找到这只动物前面的动物的足迹，以此逆推最后统计答案就可以了。
# code

```cpp
#include<bits/stdc++.h>
using namespace std;
int dx[4]={0 , 0 , 1 , -1};
int dy[4]={1 , -1 , 0 , 0};
int n,m,ans;
bool vis[4005][4005];
char a[4005][4005];
struct pi{
	int x,y;
};
queue<pi>q[10];
bool check(int x,int y){
	if(x >= 1 && x <= n && y >= 1 && y <= m && a[x][y] != '.' && !vis[x][y]){
		return true;
	}
	return false;
}
bool bfs(int s){
	bool f = 0;
	while(!q[s].empty()){
		pi u = q[s].front();
		q[s].pop();
		for(int i = 0 ; i < 4 ; i ++){
			int xx = u.x + dx[i];
			int yy = u.y + dy[i];
			if(check(xx,yy)){
				vis[xx][yy] = 1;
				if(a[u.x][u.y] == a[xx][yy]){
					q[s].push({xx , yy});
				}else{
					if(s == 0){
						q[1].push({xx , yy});
					}else{
						q[0].push({xx , yy});
					}
					f = 1;
				}
			}
		}
	}
	return f;
}

int main(){
	cin >> n >> m;
	for(int i = 1 ; i <= n ; i ++){
		for(int j = 1 ; j <= m ; j ++){
			cin >> a[i][j];
		}
	}
	q[0].push({1 , 1});
	vis[1][1] = 1;
	for(int i = 0 ; 1 ; i ^= 1){
		ans ++;
		if(!bfs(i)){
			break;
		}
	}
	cout << ans;
	return 0;
} 
```

---

## 作者：Chenxuhang_play (赞：0)

## 题目链接

<https://www.luogu.com.cn/problem/P6757>

~~话说为什么所有题解都会放传送门诶。~~

## 题目大意

有一个含 $H$ 行，$W$ 列的字符矩阵，初始全为 `.`。

你各有一只狐狸和兔子，可以让它们在矩阵中从左上角走到右下角，每个从左上到右下的过程称为一次行动。狐狸会留下 `F` 的痕迹，兔子会留下 `R` 的痕迹。后面出发的动物的痕迹会掩盖先出发的动物留下的痕迹。简单来说，不论原本的地上是 `.`、`F` 还是`R`，只要是狐狸，就会留下 `F` 的痕迹，反之，兔子会留下 `R` 的痕迹。

走路的规则如下：

1. 可以往返走；

2. 不可以走对角线；

3. 不可以跳格子；

4. 不可能有两只动物一起走。

对于1，2，3，总结起来就是当动物在 $(x,y)$ 时，在不出矩阵的情况下可以走到 $(x\pm1,y\pm1)$ 四个点，没有其他点可以走。

对于4而言，其想要表达的意思是，一只动物走完全程了，另一个动物才能出发，也就是说，任一时间，在矩阵中最多只会有1只的动物。

## 易错点&提示

好像在题目大意中已经说完了。

## 思路

看过其他题解的你相信也知道了，这道题就是不断取反的一个过程。每次取反是为了倒推最优的上一步。

（**附：** 假设第 $n$ 次行动是由兔子完成的，那么在考虑下一次行动时，我们就不应该再次派出兔子，因为第 $n+1$ 次兔子走出的痕迹，在第 $n$ 次行动的时候就可以由它来走出。所以说，为了尽量少的派出动物，我们应该交替的派出动物。）

所以，我们就按照这样的方式一路倒推。比方说我们看样例，右下角是 `F`，所以最后一次行动的动物就是狐狸。然后看到矩阵中有 `R`，说明肯定有兔子，那么根据交替派出动物的原则，我们应该在倒数第二次（假装你并不知道一共只有两只动物走过）派出一只兔子。把右下角连通的所有 `F` 全部取反为 `R`，这个时候整个矩阵都是 `R`。那么就可以说明，这张图只有两只动物轮流走过。

---

## 作者：Chillturtle (赞：0)

# 题意

有两种不同的动物，兔子和狐狸，在雪地上走。从左上走到右下，在雪地上留下了两种脚印（后面的脚印可以覆盖前面那的）。给你最后的图，问最少有几只动物经过了这片雪地。

# 思路

首先，考虑两种动物走的顺序。很明显，应该是交替行走的。这个很好证明：如果两个同种类的动物同时走，比如：兔子和兔子，那么前一只兔子走到的位置，后一只兔子也一定能走到。相当于后一只兔子的脚印会覆盖前一只的。所以一定不优。故这里，应该兔子和狐狸交替走。

然后，我们需要找到，最后一只动物的种类。这个也很容易，就是右下角（终点）的连通块是什么动物的脚印那么最后一只动物就是什么种类。这里用样例举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/njly6x82.png)

~~这个样例好像有点弱。~~

很明显我们能看出，从终点延伸出去的这个连通块的动物是狐狸。

好，我们知道了最后一只动物的种类之后需要保证答案最优应该怎么办？这里我们可以将上面找到的最后一个连通块取反：

![](https://cdn.luogu.com.cn/upload/image_hosting/k80pvlt4.png)

取反呢，就是为了表示当前这一层的脚印对于下一层的覆盖情况。从样例中，我们可以看出剩下的 R 变成了一整个连通块，所以这就是一只兔子能够走的。如果剩下的脚印中还有 F 那么就将和终点连通的 R 的连通块取反即可。后面的以此类推，直到图上只有一种脚印为止。

这里我们再举一组例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/rrtvp6ox.png)

这组例子就可以很清晰的看出上面的结论。当然最后的 F 需要再走一次才能消掉。

实现就是一个 DFS 求连通块，再加一个取反和 `check` 函数就可以了，这里就不放代码了（逃。

---

