# [USACO05JAN] The Wedding Juicer G

## 题目描述

约翰的奶牛们找到了一份不错的兼职一设计冲压式榨汁机．榨汁机设计如下：

一个 $W \times H$ 的底座（$3\leq W,H \leq 300$），每一个 $1 \times 1$ 的方格上都放有一个高度为 $B$（$1 \leq B \leq 10^9$）的柱子，用来榨汁。假设柱子之间都被完美地粘合了，这样水不会顺着柱子与柱子之间的空隙流走。

但是约翰一直不知道，这么一个榨汁机，到底能装多少果汁？假设榨汁机周围没有任何东西，也就是说，边界上的水都会流走，有些榨汁机则根本不能装下任何的果汁。

## 样例 #1

### 输入

```
4 5
5 8 7 7
5 2 1 5
7 1 7 1
8 9 6 9
9 8 9 9```

### 输出

```
12```

# 题解

## 作者：☆木辛土申☆ (赞：13)

### 这里先讲一下FloodFill算法
(已了解的请自行跳过）

FloodFill算法就是一种用指定的颜色填充某个密闭区域的算法，一种分割图像的基本算法，就相当于于画图中的油漆桶，一倒泼一片的那种，可以用来单纯的“填颜色”，或者求连通块。我通常用BFS算法实现，当然也可以用DFS，看个人喜好啦。
P.S这里推荐一个讲的比较好的博客--->[泛洪算法](http://www.pianshen.com/article/172962944/).

### 现在看两道道例题啦
* [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
* [P1506 拯救oibh总部](https://www.luogu.com.cn/problem/P1506)

这两道题目都是基础的填色题，我们考虑向外面泼一格水，让水它自由的流，遇到障碍就停止，此时没有被水覆盖到的部分便是我们要求的答案。

但是我们现在有一个问题，那格水该怎么泼呢？


这里提供两种方法：
* 1.在读入数据的过程中特判边界点存入队列，这里以P1506为例：
```cpp
for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
		read(map[i][j]);
		if((i==1||j==1||i==n||j==m)&&map[i][j]=='0'){
			q.push(std::make_pair(i,j));
			vis[i][j]=true;
		}
	}
}//map是数组，不是std::map，个人不太喜欢使用万能头
```


* 2.拓宽边界，建立虚拟边界，将水泼在边界外与虚拟边界之间的一点，这里将越界条件改一下(需要数组从1开始存信息)：
```cpp
bool illegal(int x,int y){
	return x<1||x>n||y<1||y>n||vis[x][y];
}//这是原来的条件
bool illegal(int x,int y){
	return x<0||x>n+1||y<0||y>m+1||vis[x][y];
}//这是更改后的条件
```

这样使用时可直接调用bfs(0,0)或dfs(0,0)而不用特判边界点了。

边界特判处理完后，代码就很容易实现了。这里给出一种普遍实现：
```cpp
//方向常量数组
const int fx[]={};
const int fy[]={};
//这里{}内枚举可能的方向

struct Node{
//定义节点信息，如坐标信息
//定义构造函数（可选）
//定义比较函数（如本题）
}

//定义越界判断函数
bool illegal(int x,int y);

//定义队列

//搜索函数
bfs(int x,int y){
	while(队列不为空){
    	取出队首节点;
        	for()扩展节点并判断;
        		更新信息;
        		如果符合条件加入队列;
    }
}
	

int main(){
	bfs();
    输出答案;
    return 0;//一定别忘了
}
```
---
# 关于本题
本题本质上也是一个FloodFill，但实现上有略微不同。

仔细阅读，题意很简单，一个矩阵上的所有点上都有一个立方体柱，求这些立方体柱构成的容器最多能盛装多少液体。

## 首先我们可以想到一种朴素做法：
对每一个高度的平面进行一次FloodFill，但这样做时间复杂度太高，高度在10^9级别，再乘上平面单次FloodFill的O（n^2）n_max=300，显然tle了。

## 既然有了思路还可以改一下啦
我们对高度进行离散化，离散化后的水平面最多有300*300=90000个，每个平面进行一次FloodFill，加上离散化查找的复杂度，虽比第一种方法优秀许多，但仍然是妥妥的tle（实测能得53分，~~数据真是太水了。。。。~~（bushi））

## 接下来是正解啦（我先放代码了）
我想了好久才想出正解，我真是太蒻了。。（认真.jpg）
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<queue>

typedef long long LL;
const int SIZE=301;
const int fx[]={0,0,0,1,-1};
const int fy[]={0,1,-1,0,0}; 
int map[SIZE][SIZE],h,w;
bool vis[SIZE][SIZE];

struct Node {
	int x,y,z;//x是行，y是列，z是高度 
	Node(const int &key1,const int &key2,const int &key3):x(key1),y(key2),z(key3) {}
	inline bool operator <(const Node &in)const {
		return in.z<this->z;
	}
};

template<typename T>inline void read(T &res){
	res=0;char ch=getchar();bool neg=false;
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') neg=true;
	for(; isdigit(ch);ch=getchar()) res=(res<<1)+(res<<3)+(ch^48);
	if(neg) res=-res;
}

inline bool illegal(int x,int y){
	return x<1||x>h||y<1||y>w||vis[x][y];
}

std::priority_queue<Node> q;

inline void init(int w,int h){
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			read(map[i][j]);
			if(i==1||j==1||i==h||j==w){
				q.push(Node(i,j,map[i][j]));
				vis[i][j]=true;
			}
		}
	}
}

inline LL floodfill(){
	LL res=0;
	while(!q.empty()){
		int x=q.top().x;
		int y=q.top().y;
		int h=q.top().z;
		q.pop();
		for(int i=1;i<=4;i++){
			int xx=x+fx[i];
			int yy=y+fy[i];
			if(illegal(xx,yy)) continue;
			if(map[xx][yy]<h) res+=h-map[xx][yy],map[xx][yy]=h;
			q.push(Node(xx,yy,map[xx][yy]));
			vis[xx][yy]=true;
		}
	}
	return res;
}

signed main() {
	read(w),read(h),init(w,h);
	printf("%lld\n",floodfill());
	return 0;
}
```
代码相信大家看后都很好理解的，可为什么这样是对的呢。

这个问题的重点是**计算顺序**。如果我们每次选择边界上最低的点开始FloodFill则果汁一定不会洒出去，比它低的点显然可以盛到液体，而高的点会成为新的边界，于是我们用一个优先队列来维护，每次取高度最低的点进行扩展，就可以了。

 在这里感谢这篇博客[USACO 05Gold](http://blog.sina.com.cn/s/blog_b77f5cdf0101qq6t.html)给予了我思路，上面的思路十分直接，我真是太蒻了（强调）。
 
 相信之后一定会有写的比我好的多的题解，如果通过的话，这就是我的第一篇题解了。
 
 另外，欢迎大家来扩列啊(*^▽^*)。
    

---

## 作者：xiaoshumiao (赞：4)

维护一个优先队列，最开始时把最外面一圈的格子放进优先队列。

每次取出高度最小的格子（记作 $i$），向前后左右四个格子扩展。

如果扩展到的格子（记作 $j$）已经被访问过，跳过。

否则，若 $j$ 的高度比 $i$ 高，则无法装下果汁，将 $j$ 放入优先队列。

若 $j$ 的高度比 $i$ 矮，由于 $i$ 是已经是这些格子里最矮的格子了，所以这里能装下 $a_i-a_j$ 的果汁，并将 $j$ 的高度设为 $i$ 的高度后把 $j$ 放入优先队列。

代码：
```cpp
#include<cstdio>
#include<queue>
using namespace std;
const int N=310,dx[5]={0,1,-1,0,0},dy[5]={0,0,0,1,-1}; int a[N][N]; bool vis[N][N];
struct P {
  int x,y,s;
  bool operator <(const P &b) const { return s>b.s; }
};
int main() {
  int n,m,ans=0; priority_queue<P>q; scanf("%d %d",&m,&n);
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++) {
      scanf("%d",&a[i][j]);
      if(i==1||i==n||j==1||j==m) q.push((P){i,j,a[i][j]}),vis[i][j]=true;
	}
  while(!q.empty()) {
  	P p=q.top(); q.pop();
  	for(int i=1;i<=4;i++) {
  	  int x=p.x+dx[i],y=p.y+dy[i];
  	  if(x>=1&&x<=n&&y>=1&&y<=m&&!vis[x][y]) {
  	  	vis[x][y]=true;
  	  	if(p.s<=a[x][y]) q.push((P){x,y,a[x][y]});//j 比 i 高
  	  	else ans+=p.s-a[x][y],q.push((P){x,y,p.s});//j 比 i 矮
	  }
	}
  }
  printf("%d",ans);
  return 0;
}
```

---

## 作者：柠檬布丁吖 (赞：2)

题意：有一个给定大小的水桶，构成这个水桶底部是不同高度的柱子，求这个水桶可以装多少水。


-----------
$$

1

$$

分析样例：
```cpp
4 5
5 8 7 7
5 2 1 5
7 1 7 1
8 9 6 9
9 8 9 9
```

可以得到最终装水的结果：

```cpp
0 0 0 0
0 3 4 0
0 4 0 0
0 0 1 0
0 0 0 0
```

input:
```cpp
12
```

----------------------
$$
2
$$

第一时间想到的是搜索，数据非常合适。但是这个搜索就有点难以下手，怎么搜？从什么地方搜起？边界条件？

刚刚我们模拟样例的思路，**找最终围住当前水柱的围栏上的最小高度，然后做一次减法，最后统计结果。**

但是“找围栏”就会有点麻烦，那我们可以换种思路。

同样是从某个水柱开始扩展周围的高度，因为在水桶最外围的边界上不能装水，所以只用记录这些高度。

对每个点，找外界可以到达此点的最大高度，**选择最大高度最小且此高度未被使用过的点**，如果当前点比选择高度小，那么就可以加上这个组合的贡献。

---------------
$$

3

$$


既然需要对高度大小进行排序，我们很自然想到使用优先队列。

```cpp
struct _node{
	int v,x,y;
	bool operator > (const _node &a) const{return v>a.v;}
    //重载大于号，需要在优先队列中排序。
};
priority_queue<_node,vector<_node>,greater<_node> > q;
```
首先预处理边界上的点，加入队列设置为已访问。**队列存储需要对四周进行扩展的点。**

```cpp
vis[1][1]=vis[1][W]=vis[H][1]=vis[H][W]=true;
for(int i=2;i<H;i++){
	q.push((_node){g[i][1],i,1});
	q.push((_node){g[i][W],i,W});
	vis[i][1]=vis[i][W]=true;
}
for(int i=2;i<W;i++){
	q.push((_node){g[1][i],1,i});
	q.push((_node){g[H][i],H,i});
	vis[1][i]=vis[H][i]=true;
}
```


对于每个存入优先队列的元素，扩展其四个方向且未被使用的点。

```cpp
int dx[]={-1,0,1,0};
int dy[]={0,-1,0,1};
```

核心代码：

```cpp
while(!q.empty()) {
	int v=q.top().v,x=q.top().x,y=q.top().y;
	q.pop();
	for(int i=0; i<4; i++) {
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<1 || xx>H || yy<1 || yy>W || vis[xx][yy]) continue;
		vis[xx][yy]=1;
		if(g[xx][yy]<v) {
			ans+=v-g[xx][yy];
			g[xx][yy]=v;
		}
		q.push((_node) {
			g[xx][yy],xx,yy
		});
	}
}
```


--------------
$$

4

$$

code:

```cpp

#include<bits/stdc++.h>
#define int short
using namespace std;
inline int read() {
	int ret=0,f=1;
	char c=getchar();
	for(; c<'0'||c>'9'; c=getchar()) if(c=='-') f=-f;
	for(; c>='0'&&c<='9'; c=getchar()) ret=ret*10+c-'0';
	return ret*f;
}
int g[355][355];
int H,W;
struct _node {
	int v,x,y;
	bool operator > (const _node &a) const {
		return v>a.v;
	}
};
priority_queue<_node,vector<_node>,greater<_node> > q;
int dx[]= {-1,0,1,0};
int dy[]= {0,-1,0,1};
bool vis[355][355];

int test() {
	vis[1][1]=vis[1][W]=vis[H][1]=vis[H][W]=true;
	int ans=0;
	for(int i=2; i<H; i++) {
		q.push((_node) {
			g[i][1],i,1
		});
		q.push((_node) {
			g[i][W],i,W
		});
		vis[i][1]=vis[i][W]=true;
	}
	for(int i=2; i<W; i++) {
		q.push((_node) {
			g[1][i],1,i
		});
		q.push((_node) {
			g[H][i],H,i
		});
		vis[1][i]=vis[H][i]=true;
	}
	while(!q.empty()) {
		int v=q.top().v,x=q.top().x,y=q.top().y;
		q.pop();
		for(int i=0; i<4; i++) {
			int xx=x+dx[i],yy=y+dy[i];
			if(xx<1 || xx>H || yy<1 || yy>W || vis[xx][yy]) continue;
			vis[xx][yy]=1;
			if(g[xx][yy]<v) {
				ans+=v-g[xx][yy];
				g[xx][yy]=v;
			}
			q.push((_node) {
				g[xx][yy],xx,yy
			});
		}
	}
	return ans;
}

signed main(void) {

	W=read();
	H=read();
	for(int i=1; i<=H; i++) {
		for(int j=1; j<=W; j++) {
			g[i][j]=read();
		}
	}

	printf("%d",test());

	return 0;
}
```


---

## 作者：Engulf (赞：1)

一个点 $(x, y)$ 会被淹当且仅当它被比他高的一圈围了起来，设周围那圈的最小值是 $h$，这个点积水高度就是 $h - B_{x, y}$。

最基础的想法是固定一个高度 $H$，对全图进行 flood-fill，低于 $H$ 的更新答案，高于或等于 $H$ 的不管它。时间复杂度 $O(nmB_{\max})$，无法承受。

发现完全没有必要枚举这个 $H$，由于四周肯定不会被淹，每次从 $B$ 最小的那个开始 flood-fill，遇到比它小的并且没有被淹过的就更新答案，遇到比它大的就作为之后的 $H$。

发现问题变成了每次选最小的 $H$，并支持插入删除，考虑使用堆来维护这个东西。

时间复杂度 $O(nm\log(nm))$。

类似的题目：
- [P5930 [POI1999] 降水](https://www.luogu.com.cn/problem/P5930)
- [
SP212 WATER - Water among Cubes](https://www.luogu.com.cn/problem/SP212)

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 305;

int n, m;
int a[N][N];

bool inpq[N][N];
bool vis[N][N];

struct Node {
    int x, y;
    bool operator<(const Node &b) const {return a[x][y] > a[b.x][b.y];}
};

priority_queue<Node> pq;

ll ans;

void bfs(int sx, int sy) {
    queue<pii> q;
    q.push({sx, sy});
    vis[sx][sy] = 1;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        static int dir[][2] = {1, 0, 0, 1, -1, 0, 0, -1};
        for (int i = 0; i < 4; i++) {
            int nx = x + dir[i][0], ny = y + dir[i][1];
            if (nx < 1 || nx > n || ny < 1 || ny > m || vis[nx][ny]) continue;
            if (a[nx][ny] <= a[sx][sy]) {
                ans += a[sx][sy] - a[nx][ny];
                q.push({nx, ny});
                vis[nx][ny] = 1;
            }
            else if (!inpq[nx][ny]) {
                pq.push({nx, ny});
                inpq[nx][ny] = 1;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if (i == 1 || i == n || j == 1 || j == m)
                pq.push({i, j}), inpq[i][j] = 1;
        }

    while (!pq.empty()) {
        bfs(pq.top().x, pq.top().y);
        pq.pop();
    }

    cout << ans << "\n";
    return 0;
}
```

---

## 作者：nahidaa (赞：0)

## [传送门](https://www.luogu.com.cn/problem/P6063)

## 题解：

我们需要发现从外向内搜，每次找到外圈的高度最小的点向内遍历。

证明：每次找到外圈的高度最小的点向内遍历 可以保证内部的果汁不会向外流出去，并且高度是合法的高度中最大的。

那么我们只需要将 `x=1||x=n||y=1||y=m` 的点先加入优先队列，然后运用搜索逐个访问即可。

## 代码（内附解释）：

```cpp
#include<bits/stdc++.h>
#define _ 305 
#define ll long long
using namespace std;
ll n,m,a[_][_],wx[]={0,1,0,-1},wy[]={1,0,-1,0},x,y,z,xx,yy,ans;
bool o[_][_];
priority_queue<pair<int,pair<int,int> > >i;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>m>>n;
    for(int g=1;g<=n;++g){
        for(int h=1;h<=m;++h){
            cin>>a[g][h];
            if(g==1||g==n||h==1||h==m){
                i.push(make_pair(-a[g][h],make_pair(g,h)));//加入优先队列
                o[g][h]=1;//记录已经访问
            }
        }
    }
    while(i.size()){
        x=i.top().second.first,y=i.top().second.second,z=-i.top().first;
        i.pop();//记得在这里先弹出，否则队列变化之后再加入可能把新加入的弹出！！！警钟敲烂，否则本题只有7分
        for(int g=0;g<4;++g){
            xx=x+wx[g],yy=y+wy[g];
            if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&!o[xx][yy]){
                o[xx][yy]=1;
                if(a[xx][yy]<z){
                    ans+=z-a[xx][yy];
                    a[xx][yy]=z;
                }//计算该点最多能放多少的果汁并计入答案
                i.push(make_pair(-a[xx][yy],make_pair(xx,yy)));//加入优先队列
            }
        }
    }
    cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：EclipSilvia (赞：0)

给定 $N\times M$ 的一个矩阵表示某一格的高度，求最多能放多少单位的水（水会漫延）。想到 BFS，想到从边界向中间 BFS。但是究竟该怎么控制呢？主要是有一种情况难以考虑：假设边界的最低点是 $5$，但是中间有一个凸起，中间一圈都是 $7$，那么中间的中间最多可以盛 $7$ 单位。我们可以先把边界上的点全都加入优先队列，同时维护一个小根堆。整个堆的意义是：已堆中元素为边界去盛水。然后我们找到堆首元素并向四个方向拓展。使用优先队列处理边界队列中的砖块始终表示当前的边界没对手是最爱的砖块。先把边界上所有的砖块放进优先队列，然后开始处理。从对手的最矮的砖块 $j$ 开始，把 $j$ 弹出队列，然后检查它的邻居砖块：比 $j$ 高的标记为新边界并加入队列；比 $j$ 矮的统计出水量，修改高度，再标记为新边界，加入队列。

1. 如果某个点比当前的点高，那么可以把他也加入优先队列中。
2. 如果某个点比当前的点低，那么我就可以多盛 $h-h'$ 单位的水。为什么呢？因为当前堆首已经满足是整个边界中的最小值了。这样一点水不可能从任何其他边界出去。更新答案后，再把拓展出去的点的高度标为当前的高度 $h$ 并加入优先队列（这个点以后可能还能盛水）。

直到队列为空，我们已经拓展了所有可能的点了。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){int a=0,b=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') b=-1;ch=getchar();}while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}return a*b;}
struct node
{
  int x,y,h;
  friend bool operator < (const node &a,const node &b)
  {
    return  a.h > b.h;
  }
}tmp;
const int dx[4] = {0,0,-1,1};
const int dy[4]={1,-1,0,0};
priority_queue<node>q;
int n,m,ans,a[305][305];
bool vis[305][305];
signed main()
{
    m = read(),n = read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) a[i][j] = read();
  	for(int i = 1;i <= m;i ++)
    {
		q.push((node){1,i,a[1][i]});
		q.push((node){n,i,a[n][i]});
		vis[1][i] = vis[n][i] = true;
  	}
  	for(int i = 2;i < n;i ++)
    {
		q.push((node){i,1,a[i][1]});
		q.push((node){i,m,a[i][m]});
		vis[i][1] = vis[i][m] = true;
  	}
	while(!q.empty())
  	{
    	tmp = q.top();
		q.pop();
		int x = tmp.x,y = tmp.y;
    	for(int i=0;i<=3;i++)
    	{
     		int xx = x + dx[i],yy = y + dy[i];
    		if(xx < 1||xx > n||yy < 1||yy > m|| vis[xx][yy]) continue;
    		vis[xx][yy] = true;
      		if(a[xx][yy] >= tmp.h)
		  	{
				q.push((node){xx,yy,a[xx][yy]});
      		}
			else
	  		{
				ans += tmp.h - a[xx][yy];
				q.push((node){xx,yy,tmp.h});
    		}
  		}
	}
  printf("%d",ans);
  return 0;
}
```

---

## 作者：ybc2025chenyuyang (赞：0)

# P6063 [USACO05JAN] The Wedding Juicer G
这道题我的思路就是用泛洪算法来实现。
## 思路
我们可以把这个底座看成一个不规则的大水桶，其中有很多局部能够储水，每个储水的局部，其水面不能高于这个局部边界上最矮的柱子。

最简单的算法是逐个检查柱子，统计周边的局部储水情况。但这样比较复杂。为了简化逻辑，采用从四周堵中央的办法。

我们从边界开始，找到边界上最矮的砖块 $j$，检查他的邻居柱子 $k$：第一，如果 $B_{j}\leq B_{k}$，$k$ 上不能储水，将 $k$ 标记为新的边界；第二，如果 $B_{j}>  B_{k}$，该柱子可以储水，储水容量增加 $B_{j}-B_{k}$，把 $k$ 高度的改为 $j$ 的高度，然后也把 $k$ 标记为新的边界。删除 $j$，后续不再处理。每次检查新边界，处理其中最矮的；逐步缩小边界，直到所有柱子被检查过。

那么我们怎么打代码呢？

## 编码

编码时用优先队列处理边界，队列中的柱子始终表示当前的边界，队首是最矮的柱子。先把边界上的所有柱子放进优先队列，然后开始处理队列。从队首的最矮柱子 $j$ 开始，把 $j$ 弹出队列然后检查它的邻居柱子：比 $j$ 高的标记为新的边界，并且加入队列；反之，统计储水量，修改高度，标记为新边界，加入队列，队列为空时计算结束。

这道题就是这么简单。。。

求管理员大大通过。

---

